#include "resource.h"
#include"BForm.h"          //图形界面通用模块基本包含文件
#include"mdlOpenSaveDlg.h" //支持打开/另存为对话框
#include"mdlFileSys.h"     //支持文件操作（如判定文件存在）
#include"mdlPathDlg.h"     //支持浏览文件夹对话框
#include"mdlShellExec.h"   //支持运行外部程序

CBForm form1(ID_form1);

//测试一个文件是否存在，若存在返回true，如不存在返回false并给出提示szPromptIfNotExist
bool TestFileExist(TCHAR * szFile,TCHAR * szPromptIfNotExist)
{
	//FMFileExist是通用模块mdlFileSys中的函数
	if(FMFileExist(szFile)==1)
		return true;
	else 
	{
		MsgBox(StrAppend(szFile,TEXT("\r\n"),szPromptIfNotExist),TEXT("文件不存在"),mb_OK,mb_IconExclamation);
		return false;
	}
}

////向文件中以SVM数据格式写入一批样本特征值（正样本和负样本）
////hFile是已经用EFOpen打开的文件的句柄，将写入此文件
////idCboControl是一个控件ID，表示写入哪些样本？控件中的内容是样本的类别标签
////成功返回true，失败返回false
//bool OutputDataFile(HANDLE hFile,unsigned int idCboControl,int iPosiNega)
//{
//	//写入样本数据到文件
//	CBAdoRecordset rsSam,rs;
//	TCHAR *szSql=NULL;
//	bool blRet=false;
//	long lRet=0;
//	int iFeatureIndex=0;//写入文件时的特征编号
//
//	//获得所有样本的SampleID=>rsSam
//	if(iPosiNega>0)
//		form1.Control(ID_lblStatusSVM).TextSet(TEXT("获得阳性样本..."));
//	else
//		form1.Control(ID_lblStatusSVM).TextSet(TEXT("获得阴性样本..."));
//	szSql=StrAppend(TEXT("SELECT * FROM Samples WHERE ClassLabel='"),form1.Control(idCboControl).Text(),TEXT("' ORDER BY SampleID"));
//	blRet=rsSam.Open(szSql);
//	if(!blRet) return false;
//	//对每个样本，获得其部分特征值，所要获得的特征其ID在UseFeatures表中
//	while(!rsSam.EOFRs())
//	{
//		//显示提示信息，样本显示样本ID和样本文件名（去除路径部分）
//		form1.Control(ID_lblStatusSVM).TextSet(TEXT("写入样本特征值"));
//		form1.Control(ID_lblStatusSVM).TextAdd(rsSam.GetField(TEXT("SampleID")));
//		form1.Control(ID_lblStatusSVM).TextAdd(TEXT(" - "));
//		form1.Control(ID_lblStatusSVM).TextAdd(FMTrimFileName(rsSam.GetField(TEXT("ImageFile"))));
//		//在文件中写入标签和空格：阳性样本标签1，阴性-1
//		//EF_LineSeed_None 表示写入此内容后，不自动换行
//		lRet=EFPrint(hFile,Str(iPosiNega),EF_LineSeed_None);
//		if(lRet<0) return false;//写入失败
//		lRet=EFPrint(hFile,TEXT(" "),EF_LineSeed_None);
//		if(lRet<0) return false;//写入失败
//		//对样本ID为rsSam.GetField(TEXT("SampleID"))的样本，获得其部分特征值=>rs
//		szSql=StrAppend(TEXT("SELECT * FROM Features,UseFeatures WHERE "),TEXT("Features.FeatureID=UseFeatures.FeatureID AND "),
//			TEXT("SampleID="),rsSam.GetField(TEXT("SampleID")),TEXT(" ORDER BY Features.FeatureID"));
//		blRet=rs.Open(szSql);
//		if(!blRet) return false;
//		//循环所有特征值，以SVM的格式写入文件
//		iFeatureIndex=0;
//		while(!rs.EOFRs())
//		{
//			//在文件中写入“特征编号和特征值以及空格”
//			//EF_LineSeed_None表示写入此内容后，不自动换行
//			lRet=EFPrint(hFile,Str(++iFeatureIndex),EF_LineSeed_None);
//			if(lRet<0) return false;//写入失败
//			lRet=EFPrint(hFile,TEXT(":"),EF_LineSeed_None);
//			if(lRet<0) return false;//写入失败
//			lRet=EFPrint(hFile,rs.GetField(TEXT("FeatureValue")),EF_LineSeed_None);
//			if(lRet<0) return false;//写入失败
//			lRet=EFPrint(hFile,TEXT(" "),EF_LineSeed_None);//写入空格
//			if(lRet<0) return false;//写入失败
//			rs.MoveNext();
//		}
//			lRet=EFPrint(hFile,TEXT(""));//写入空串，参数3省略，则自动换行
//			if(lRet<0) return false;//写入失败
//			rsSam.MoveNext();
//	}
//	rsSam.Close();
//	if(iPosiNega>0)
//		form1.Control(ID_lblStatusSVM).TextSet(TEXT("阳性样本输入完成。"));
//	else
//		form1.Control(ID_lblStatusSVM).TextSet(TEXT("阴性样本输入完成。"));
//	return true;
//}

////生成SVM数据文件，文件名为szFile
////cmdTrain_Click和cmdGenModel_Click运行之前均要调用
//bool GenSVMDataFile(TCHAR * szFile)
//{
//	检验数据
//	/*bool blRet;*/
//	if(* szFile==TEXT('\0'))
//	{
//		MsgBox(TEXT("请输入特征文件的文件名和保存位置！"),TEXT("未指定特征文件"),mb_OK,mb_IconExclamation);
//		return false;
//	}
//	TCHAR * szClassLabel=form1.Control(ID_cboPosi).Text();
//	if(* szClassLabel==TEXT('\0'))
//	{
//		MsgBox(TEXT("请选择阳性样本的类别标签！"),TEXT("未选择阳性样本类别标签"),mb_OK,mb_IconExclamation);
//		return false;
//	}
//	szClassLabel=form1.Control(ID_cboNega).Text();
//	if(* szClassLabel==TEXT('\0'))
//	{
//		MsgBox(TEXT("请选择阴性样本的类别标签！"),TEXT("未选择阴性样本类别标签"),mb_OK,mb_IconExclamation);
//		return false;
//	}
//
//	生成SVM格式所要求的输入数据文件，文件名：szFile
//	打开文件szFile
//	HANDLE hFile=EFOpen(szFile,EF_OpStyle_Output);
//	if(hFile==INVALID_HANDLE_VALUE) return false;//打开文件失败
//	//写入阳性样本数据到文件
//	blRet=OutputDataFile(hFile,ID_cboPosi,1);
//	if(!blRet)
//	{
//		MsgBox(TEXT("写入阳性样本特征值到文件失败！"),TEXT("写入阳性样本失败"),mb_OK,mb_IconExclamation);
//		return false;
//	}
//	//写入阴性样本数据到文件
//	blRet=OutputDataFile(hFile,ID_cboNega,-1);
//	if(!blRet)
//	{
//		MsgBox(TEXT("写入阴性样本特征值到文件失败！"),TEXT("写入阴性样本失败"),mb_OK,mb_IconExclamation);
//		return false;
//	}
//	EFClose(hFile);//关闭文件
//	return true;
//}

bool RunBat(TCHAR * szPath,TCHAR * szBatFileName,TCHAR * szCmdLine)
{
	//构造批处理文件名含全路径=>szBatFile
	TCHAR * szBatFile=StrAppend(FMAddBackSlash(szPath),szBatFileName);//向批处理文件中写入命令行szCmdLine
	HANDLE hFileBat=EFOpen(szBatFile,EF_OpStyle_Output);
	if(hFileBat==INVALID_HANDLE_VALUE)
	{
		MsgBox(StrAppend(TEXT("无法创建批处理文件：\r\n"),szBatFile),TEXT("无法创建批处理文件"),mb_OK,mb_IconExclamation);
		return false;
	}
	EFPrint(hFileBat,szCmdLine);//写入命令行
	EFClose(hFileBat);//关闭批处理文件
	//运行批处理文件并等待运行结束
	//如在运行时不希望弹出黑屏运行窗口，或使黑屏窗口最大化、最小化、正常显示等
	//则请继续为SERunWaitTerminate设置第3个参数
	SERunWaitTerminate(szBatFile,true);

	//删除批处理文件
	//FMDeleteFiles是通用模块mdlFileSys中的函数
	FMDeleteFiles(szBatFile,true,true,false);
	return true;
}

//运行SVM（自动包含归一化处理）并等待程序结束
//szFile为数据文件的文件名，szModelFile为要生成的model文件的文件名
//szModelFile!=NULL时，将生成model文件，此时不做n-折交叉验证；szModelFile==NULL时，做n-折交叉验证
bool RunSVM(TCHAR * szFile,TCHAR *szModelFile)
{
	//校验可执行文件是否存在
	//pApp->Path返回本程序所在文件夹
	//用FMAddBackSlash函数在文件夹字符串最后加"\"
	TCHAR * szSVMExeScale=FMAddBackSlash(pApp->Path());
	szSVMExeScale=StrAppend(szSVMExeScale,TEXT("svm-scale.exe"));
	if(!TestFileExist(szSVMExeScale,TEXT("归一化可执行文件不存在，无法运行支持向量机程序！"))) return false;
	TCHAR * szSVMExeTrain=FMAddBackSlash(pApp->Path());
	szSVMExeTrain=StrAppend(szSVMExeTrain,TEXT("svm-train.exe"));
	if(!TestFileExist(szSVMExeTrain,TEXT("SVM训练可执行文件不存在，无法运行支持向量机程序！"))) return false;

	//准备文件名
	TCHAR * szPath=NULL,* szExp=NULL;//szFile的路径部分、扩展名部分
	//将数据文件的文件名部分（不含路径不含扩展名）=>szFileNameOnly
	//路径部分=>szPath，扩展名部分=>szExp
	//FMTrimFileName是通用模块mdlFileSys中的函数
	TCHAR * szFileNameOnly=FMTrimFileName(szFile,true,true,&szPath,&szExp);

	//调用归一化程序归一化数据
	//svm-scale szFile>szFile
	//文件名中加scale拼接构造出归一化后的文件名=>szFileScale
	//如：C:\\data.txt变为C:\\data.scale.txt
	TCHAR * szFileScale=StrAppend(szPath,TEXT("\\"),szFileNameOnly,TEXT(".scale."),szExp);
	//如果szFileScale已存在，删除此文件
	FMDeleteFiles(szFileScale,true,true,false);
	if(FMFileExist(szFileScale)==1)//删除后检查，如果文件仍然存在，说明未删除成功
	{
		MsgBox(StrAppend(szFileScale,TEXT("\r\n"),TEXT("不能删除之前残留的归一化数据结果文件！")),TEXT("无法更新归一化结果文件"),mb_OK,mb_IconExclamation);
		return false;
	}

	//文件名中加scale.param拼接构造出归一化后的文件名=>szFileScaleParam
	//如：C:\\data.txt变为C:\\data.scale.param.txt
	TCHAR * szFileScaleParam=StrAppend(szPath,TEXT("\\"),szFileNameOnly,TEXT(".scale.param."),szExp);
	//如果szFileScaleParam已存在，删除此文件
	FMDeleteFiles(szFileScaleParam,true,true,false);
	if(FMFileExist(szFileScaleParam)==1)//删除后检查，如果文件仍然存在，说明未删除成功
	{
		MsgBox(StrAppend(szFileScaleParam,TEXT("\r\n"),TEXT("不能删除之前残留的归一化参数文件！")),TEXT("无法更新归一化参数文件"),mb_OK,mb_IconExclamation);
		return false;
	}
	//生成归一化的命令行，\"转义表示普通引号；注意空格
	TCHAR * szCmdLine=NULL;
	szCmdLine=StrAppend(TEXT("\""),szSVMExeScale,TEXT("\" -s "));
	szCmdLine=StrAppend(szCmdLine,TEXT("\""),szFileScaleParam,TEXT("\" "));
	szCmdLine=StrAppend(szCmdLine,TEXT("\""),szFile,TEXT("\""),TEXT("> \""),szFileScale,TEXT("\""));
	//通过批处理文件的方式，运行此命令行，并等待运行结束
	//批处理文件设为同一目录下的svmscale.bat(文件名设置为其他名也可)
	RunBat(szPath,TEXT("svmscale.bat"),szCmdLine);

	//检查结果文件szFileScale是否已生成
	if(!TestFileExist(szFileScale,TEXT("数据归一化失败！未能生成归一化数据的结果文件。"))) return false;
	//调用SVM训练模型
	//svm-train -v 5 -t 0 szFileScale
	//svm-train -t 0 szFileScale szFileModel


	//准备SVM训练的命令行。\"转义表示普通引号；注意空格
	szCmdLine=StrAppend(TEXT("\""),szSVMExeTrain,TEXT("\" "));
	//向命令行中写入 -t 参数：选择核函数
	szCmdLine=StrAppend(szCmdLine,TEXT(" -t "),Str(form1.Control(ID_cboKernels).ListIndex()-1));
	//若不生成model文件，则执行n-折交叉验证：向命令行中写入 -v 参数
	if(szModelFile==NULL)
		szCmdLine=StrAppend(szCmdLine,TEXT(" -v "),form1.Control(ID_cboFold).Text());
	////向命令行中写入其他参数
	//szCmdLine=StrAppend(szCmdLine,TEXT(" "),form1.Control(ID_txtParams).Text(),TEXT("  "));
	//向命令行中写入数据文件文件名：szFileScale
	szCmdLine=StrAppend(szCmdLine,TEXT(" \""),szFileScale,TEXT("\" "));
	//若生成model文件，向命令行中写入model文件的文件名
	if(szModelFile)
		szCmdLine=StrAppend(szCmdLine,TEXT(" \""),szModelFile,TEXT("\""));
	//通过批处理文件的方式，运行此命令行，并等待运行结束
	//批处理文件设为同一目录下的svmscale.bat
	RunBat(szPath,TEXT("svmtrain.bat"),szCmdLine);

	//显示结果
	TCHAR * szFileResult=NULL;
	if(szModelFile==NULL)
	{
		//不生成model文件：检查训练结果文件是否已生成szFileResult
		//例如：data.scale.txt(t=0).training_result
		szFileResult=StrAppend(szFileScale,TEXT("(t="),Str(form1.Control(ID_cboKernels).ListIndex()-1),TEXT(").training_result"));
		if(!TestFileExist(szFileResult,TEXT("SVM训练失败！未能生成训练结果文件。"))) return false;
		//结果文件已生成，调用记事本程序（notepad）打开结果文件
		//SEShellRun函数是mdlShellExec通用模块中的函数
		SEShellRun(StrAppend(TEXT("NotePad.exe  \""),szFileResult,TEXT(" \"")),true);
	}
	else 
	{
		//检查model文件是否已生成
		if(!TestFileExist(szModelFile,TEXT("model文件生成失败！未能生成model结果文件。"))) return false;

		MsgBox(StrAppend(TEXT("model文件已生成："),szModelFile),TEXT("训练完成"),mb_OK,mb_IconInformation);
	}
	return true;
} 

void form1_Load()
{   //form1加载时要执行的功能

	//向控件ID_cboKernels（核函数）中添加选项
	CBControl cboKernels(ID_cboKernels);
	cboKernels.AddItem(TEXT("线性核(Linear,t=0)"));
	cboKernels.AddItem(TEXT("多项式核(Polynomial,t=1)"));
	cboKernels.AddItem(TEXT("高斯径向基核(Radial Basis Function,t=2)"));
	cboKernels.AddItem(TEXT("二层神经网络核(Sigmoid,t=3)"));
	cboKernels.ListIndexSet(4);//默认选第4个条目（Sigmoid核）

	//向控件ID_cboFold（交叉验证）中添加选项
	CBControl cboFold(ID_cboFold);
	cboFold.AddItem(TEXT("2"));
	cboFold.AddItem(TEXT("3"));
	cboFold.AddItem(TEXT("4"));
	cboFold.AddItem(TEXT("5"));
	cboFold.AddItem(TEXT("6"));
	cboFold.AddItem(TEXT("8"));
	cboFold.AddItem(TEXT("10"));
	cboFold.TextSet(TEXT("5"));//默认5折交叉验证
}

void cmdBrowDataFile_Click()
{
	LPTSTR file;
	OsdSetFilter(TEXT("文本文件(*.txt)|*.txt"));
	file=OsdOpenDlg(form1.hWnd(),TEXT("请选择一个文本文件"));
	if(*file) form1.Control(ID_cboDataFile).TextSet(file);
}

void cmdTrain_Click()
{
	//生成SVM数据集文件
	TCHAR * szFile=form1.Control(ID_cboDataFile).Text();
	/*if(!GenSVMDataFile(szFile)) return;*/

	//调用以下函数：首先归一化数据，然后调用SVM训练，并给出训练结果
	//第2个参数为NULL表示做n-折交叉验证，不生成model文件
	RunSVM(szFile,NULL);
}

void cmdGenModel_Click()
{
	//浏览选择model文件要保存到的位置和文件名
	OsdSetFilter(TEXT("文本文件(*.txt)|*.txt"));
	TCHAR * file=OsdSaveDlg(form1.hWnd(),0,TEXT("请指定要保存的model文件"));
	if(* file==TEXT('\0')) return;
	//生成SVM数据集文件
	TCHAR * szFile=form1.Control(ID_cboDataFile).Text();
	/*if(!GenSVMDataFile(szFile)) return;*/
	//调用以下函数：首先归一化数据，然后调用SVM训练，并给出训练结果
	//第2个参数不为NULL表示不做n-折交叉验证，要生成model文件
	RunSVM(szFile,file);
}

int main()
{
	form1.EventAdd(0,eForm_Load,form1_Load);
	form1.EventAdd(ID_cmdBrowDataFile,eCommandButton_Click,cmdBrowDataFile_Click);
	form1.EventAdd(ID_cmdTrain,eCommandButton_Click,cmdTrain_Click);
	form1.EventAdd(ID_cmdGenModel,eCommandButton_Click,cmdGenModel_Click);

	form1.IconSet(IDI_ICON1);

	form1.Show();

	return 0;
}