#include "resource.h"
#include"BForm.h"          //ͼ�ν���ͨ��ģ����������ļ�
#include"mdlOpenSaveDlg.h" //֧�ִ�/���Ϊ�Ի���
#include"mdlFileSys.h"     //֧���ļ����������ж��ļ����ڣ�
#include"mdlPathDlg.h"     //֧������ļ��жԻ���
#include"mdlShellExec.h"   //֧�������ⲿ����

CBForm form1(ID_form1);

//����һ���ļ��Ƿ���ڣ������ڷ���true���粻���ڷ���false��������ʾszPromptIfNotExist
bool TestFileExist(TCHAR * szFile,TCHAR * szPromptIfNotExist)
{
	//FMFileExist��ͨ��ģ��mdlFileSys�еĺ���
	if(FMFileExist(szFile)==1)
		return true;
	else 
	{
		MsgBox(StrAppend(szFile,TEXT("\r\n"),szPromptIfNotExist),TEXT("�ļ�������"),mb_OK,mb_IconExclamation);
		return false;
	}
}

////���ļ�����SVM���ݸ�ʽд��һ����������ֵ���������͸�������
////hFile���Ѿ���EFOpen�򿪵��ļ��ľ������д����ļ�
////idCboControl��һ���ؼ�ID����ʾд����Щ�������ؼ��е�����������������ǩ
////�ɹ�����true��ʧ�ܷ���false
//bool OutputDataFile(HANDLE hFile,unsigned int idCboControl,int iPosiNega)
//{
//	//д���������ݵ��ļ�
//	CBAdoRecordset rsSam,rs;
//	TCHAR *szSql=NULL;
//	bool blRet=false;
//	long lRet=0;
//	int iFeatureIndex=0;//д���ļ�ʱ���������
//
//	//�������������SampleID=>rsSam
//	if(iPosiNega>0)
//		form1.Control(ID_lblStatusSVM).TextSet(TEXT("�����������..."));
//	else
//		form1.Control(ID_lblStatusSVM).TextSet(TEXT("�����������..."));
//	szSql=StrAppend(TEXT("SELECT * FROM Samples WHERE ClassLabel='"),form1.Control(idCboControl).Text(),TEXT("' ORDER BY SampleID"));
//	blRet=rsSam.Open(szSql);
//	if(!blRet) return false;
//	//��ÿ������������䲿������ֵ����Ҫ��õ�������ID��UseFeatures����
//	while(!rsSam.EOFRs())
//	{
//		//��ʾ��ʾ��Ϣ��������ʾ����ID�������ļ�����ȥ��·�����֣�
//		form1.Control(ID_lblStatusSVM).TextSet(TEXT("д����������ֵ"));
//		form1.Control(ID_lblStatusSVM).TextAdd(rsSam.GetField(TEXT("SampleID")));
//		form1.Control(ID_lblStatusSVM).TextAdd(TEXT(" - "));
//		form1.Control(ID_lblStatusSVM).TextAdd(FMTrimFileName(rsSam.GetField(TEXT("ImageFile"))));
//		//���ļ���д���ǩ�Ϳո�����������ǩ1������-1
//		//EF_LineSeed_None ��ʾд������ݺ󣬲��Զ�����
//		lRet=EFPrint(hFile,Str(iPosiNega),EF_LineSeed_None);
//		if(lRet<0) return false;//д��ʧ��
//		lRet=EFPrint(hFile,TEXT(" "),EF_LineSeed_None);
//		if(lRet<0) return false;//д��ʧ��
//		//������IDΪrsSam.GetField(TEXT("SampleID"))������������䲿������ֵ=>rs
//		szSql=StrAppend(TEXT("SELECT * FROM Features,UseFeatures WHERE "),TEXT("Features.FeatureID=UseFeatures.FeatureID AND "),
//			TEXT("SampleID="),rsSam.GetField(TEXT("SampleID")),TEXT(" ORDER BY Features.FeatureID"));
//		blRet=rs.Open(szSql);
//		if(!blRet) return false;
//		//ѭ����������ֵ����SVM�ĸ�ʽд���ļ�
//		iFeatureIndex=0;
//		while(!rs.EOFRs())
//		{
//			//���ļ���д�롰������ź�����ֵ�Լ��ո�
//			//EF_LineSeed_None��ʾд������ݺ󣬲��Զ�����
//			lRet=EFPrint(hFile,Str(++iFeatureIndex),EF_LineSeed_None);
//			if(lRet<0) return false;//д��ʧ��
//			lRet=EFPrint(hFile,TEXT(":"),EF_LineSeed_None);
//			if(lRet<0) return false;//д��ʧ��
//			lRet=EFPrint(hFile,rs.GetField(TEXT("FeatureValue")),EF_LineSeed_None);
//			if(lRet<0) return false;//д��ʧ��
//			lRet=EFPrint(hFile,TEXT(" "),EF_LineSeed_None);//д��ո�
//			if(lRet<0) return false;//д��ʧ��
//			rs.MoveNext();
//		}
//			lRet=EFPrint(hFile,TEXT(""));//д��մ�������3ʡ�ԣ����Զ�����
//			if(lRet<0) return false;//д��ʧ��
//			rsSam.MoveNext();
//	}
//	rsSam.Close();
//	if(iPosiNega>0)
//		form1.Control(ID_lblStatusSVM).TextSet(TEXT("��������������ɡ�"));
//	else
//		form1.Control(ID_lblStatusSVM).TextSet(TEXT("��������������ɡ�"));
//	return true;
//}

////����SVM�����ļ����ļ���ΪszFile
////cmdTrain_Click��cmdGenModel_Click����֮ǰ��Ҫ����
//bool GenSVMDataFile(TCHAR * szFile)
//{
//	��������
//	/*bool blRet;*/
//	if(* szFile==TEXT('\0'))
//	{
//		MsgBox(TEXT("�����������ļ����ļ����ͱ���λ�ã�"),TEXT("δָ�������ļ�"),mb_OK,mb_IconExclamation);
//		return false;
//	}
//	TCHAR * szClassLabel=form1.Control(ID_cboPosi).Text();
//	if(* szClassLabel==TEXT('\0'))
//	{
//		MsgBox(TEXT("��ѡ����������������ǩ��"),TEXT("δѡ��������������ǩ"),mb_OK,mb_IconExclamation);
//		return false;
//	}
//	szClassLabel=form1.Control(ID_cboNega).Text();
//	if(* szClassLabel==TEXT('\0'))
//	{
//		MsgBox(TEXT("��ѡ����������������ǩ��"),TEXT("δѡ��������������ǩ"),mb_OK,mb_IconExclamation);
//		return false;
//	}
//
//	����SVM��ʽ��Ҫ������������ļ����ļ�����szFile
//	���ļ�szFile
//	HANDLE hFile=EFOpen(szFile,EF_OpStyle_Output);
//	if(hFile==INVALID_HANDLE_VALUE) return false;//���ļ�ʧ��
//	//д�������������ݵ��ļ�
//	blRet=OutputDataFile(hFile,ID_cboPosi,1);
//	if(!blRet)
//	{
//		MsgBox(TEXT("д��������������ֵ���ļ�ʧ�ܣ�"),TEXT("д����������ʧ��"),mb_OK,mb_IconExclamation);
//		return false;
//	}
//	//д�������������ݵ��ļ�
//	blRet=OutputDataFile(hFile,ID_cboNega,-1);
//	if(!blRet)
//	{
//		MsgBox(TEXT("д��������������ֵ���ļ�ʧ�ܣ�"),TEXT("д����������ʧ��"),mb_OK,mb_IconExclamation);
//		return false;
//	}
//	EFClose(hFile);//�ر��ļ�
//	return true;
//}

bool RunBat(TCHAR * szPath,TCHAR * szBatFileName,TCHAR * szCmdLine)
{
	//�����������ļ�����ȫ·��=>szBatFile
	TCHAR * szBatFile=StrAppend(FMAddBackSlash(szPath),szBatFileName);//���������ļ���д��������szCmdLine
	HANDLE hFileBat=EFOpen(szBatFile,EF_OpStyle_Output);
	if(hFileBat==INVALID_HANDLE_VALUE)
	{
		MsgBox(StrAppend(TEXT("�޷������������ļ���\r\n"),szBatFile),TEXT("�޷������������ļ�"),mb_OK,mb_IconExclamation);
		return false;
	}
	EFPrint(hFileBat,szCmdLine);//д��������
	EFClose(hFileBat);//�ر��������ļ�
	//�����������ļ����ȴ����н���
	//��������ʱ��ϣ�������������д��ڣ���ʹ����������󻯡���С����������ʾ��
	//�������ΪSERunWaitTerminate���õ�3������
	SERunWaitTerminate(szBatFile,true);

	//ɾ���������ļ�
	//FMDeleteFiles��ͨ��ģ��mdlFileSys�еĺ���
	FMDeleteFiles(szBatFile,true,true,false);
	return true;
}

//����SVM���Զ�������һ���������ȴ��������
//szFileΪ�����ļ����ļ�����szModelFileΪҪ���ɵ�model�ļ����ļ���
//szModelFile!=NULLʱ��������model�ļ�����ʱ����n-�۽�����֤��szModelFile==NULLʱ����n-�۽�����֤
bool RunSVM(TCHAR * szFile,TCHAR *szModelFile)
{
	//У���ִ���ļ��Ƿ����
	//pApp->Path���ر����������ļ���
	//��FMAddBackSlash�������ļ����ַ�������"\"
	TCHAR * szSVMExeScale=FMAddBackSlash(pApp->Path());
	szSVMExeScale=StrAppend(szSVMExeScale,TEXT("svm-scale.exe"));
	if(!TestFileExist(szSVMExeScale,TEXT("��һ����ִ���ļ������ڣ��޷�����֧������������"))) return false;
	TCHAR * szSVMExeTrain=FMAddBackSlash(pApp->Path());
	szSVMExeTrain=StrAppend(szSVMExeTrain,TEXT("svm-train.exe"));
	if(!TestFileExist(szSVMExeTrain,TEXT("SVMѵ����ִ���ļ������ڣ��޷�����֧������������"))) return false;

	//׼���ļ���
	TCHAR * szPath=NULL,* szExp=NULL;//szFile��·�����֡���չ������
	//�������ļ����ļ������֣�����·��������չ����=>szFileNameOnly
	//·������=>szPath����չ������=>szExp
	//FMTrimFileName��ͨ��ģ��mdlFileSys�еĺ���
	TCHAR * szFileNameOnly=FMTrimFileName(szFile,true,true,&szPath,&szExp);

	//���ù�һ�������һ������
	//svm-scale szFile>szFile
	//�ļ����м�scaleƴ�ӹ������һ������ļ���=>szFileScale
	//�磺C:\\data.txt��ΪC:\\data.scale.txt
	TCHAR * szFileScale=StrAppend(szPath,TEXT("\\"),szFileNameOnly,TEXT(".scale."),szExp);
	//���szFileScale�Ѵ��ڣ�ɾ�����ļ�
	FMDeleteFiles(szFileScale,true,true,false);
	if(FMFileExist(szFileScale)==1)//ɾ�����飬����ļ���Ȼ���ڣ�˵��δɾ���ɹ�
	{
		MsgBox(StrAppend(szFileScale,TEXT("\r\n"),TEXT("����ɾ��֮ǰ�����Ĺ�һ�����ݽ���ļ���")),TEXT("�޷����¹�һ������ļ�"),mb_OK,mb_IconExclamation);
		return false;
	}

	//�ļ����м�scale.paramƴ�ӹ������һ������ļ���=>szFileScaleParam
	//�磺C:\\data.txt��ΪC:\\data.scale.param.txt
	TCHAR * szFileScaleParam=StrAppend(szPath,TEXT("\\"),szFileNameOnly,TEXT(".scale.param."),szExp);
	//���szFileScaleParam�Ѵ��ڣ�ɾ�����ļ�
	FMDeleteFiles(szFileScaleParam,true,true,false);
	if(FMFileExist(szFileScaleParam)==1)//ɾ�����飬����ļ���Ȼ���ڣ�˵��δɾ���ɹ�
	{
		MsgBox(StrAppend(szFileScaleParam,TEXT("\r\n"),TEXT("����ɾ��֮ǰ�����Ĺ�һ�������ļ���")),TEXT("�޷����¹�һ�������ļ�"),mb_OK,mb_IconExclamation);
		return false;
	}
	//���ɹ�һ���������У�\"ת���ʾ��ͨ���ţ�ע��ո�
	TCHAR * szCmdLine=NULL;
	szCmdLine=StrAppend(TEXT("\""),szSVMExeScale,TEXT("\" -s "));
	szCmdLine=StrAppend(szCmdLine,TEXT("\""),szFileScaleParam,TEXT("\" "));
	szCmdLine=StrAppend(szCmdLine,TEXT("\""),szFile,TEXT("\""),TEXT("> \""),szFileScale,TEXT("\""));
	//ͨ���������ļ��ķ�ʽ�����д������У����ȴ����н���
	//�������ļ���ΪͬһĿ¼�µ�svmscale.bat(�ļ�������Ϊ������Ҳ��)
	RunBat(szPath,TEXT("svmscale.bat"),szCmdLine);

	//������ļ�szFileScale�Ƿ�������
	if(!TestFileExist(szFileScale,TEXT("���ݹ�һ��ʧ�ܣ�δ�����ɹ�һ�����ݵĽ���ļ���"))) return false;
	//����SVMѵ��ģ��
	//svm-train -v 5 -t 0 szFileScale
	//svm-train -t 0 szFileScale szFileModel


	//׼��SVMѵ���������С�\"ת���ʾ��ͨ���ţ�ע��ո�
	szCmdLine=StrAppend(TEXT("\""),szSVMExeTrain,TEXT("\" "));
	//����������д�� -t ������ѡ��˺���
	szCmdLine=StrAppend(szCmdLine,TEXT(" -t "),Str(form1.Control(ID_cboKernels).ListIndex()-1));
	//��������model�ļ�����ִ��n-�۽�����֤������������д�� -v ����
	if(szModelFile==NULL)
		szCmdLine=StrAppend(szCmdLine,TEXT(" -v "),form1.Control(ID_cboFold).Text());
	////����������д����������
	//szCmdLine=StrAppend(szCmdLine,TEXT(" "),form1.Control(ID_txtParams).Text(),TEXT("  "));
	//����������д�������ļ��ļ�����szFileScale
	szCmdLine=StrAppend(szCmdLine,TEXT(" \""),szFileScale,TEXT("\" "));
	//������model�ļ�������������д��model�ļ����ļ���
	if(szModelFile)
		szCmdLine=StrAppend(szCmdLine,TEXT(" \""),szModelFile,TEXT("\""));
	//ͨ���������ļ��ķ�ʽ�����д������У����ȴ����н���
	//�������ļ���ΪͬһĿ¼�µ�svmscale.bat
	RunBat(szPath,TEXT("svmtrain.bat"),szCmdLine);

	//��ʾ���
	TCHAR * szFileResult=NULL;
	if(szModelFile==NULL)
	{
		//������model�ļ������ѵ������ļ��Ƿ�������szFileResult
		//���磺data.scale.txt(t=0).training_result
		szFileResult=StrAppend(szFileScale,TEXT("(t="),Str(form1.Control(ID_cboKernels).ListIndex()-1),TEXT(").training_result"));
		if(!TestFileExist(szFileResult,TEXT("SVMѵ��ʧ�ܣ�δ������ѵ������ļ���"))) return false;
		//����ļ������ɣ����ü��±�����notepad���򿪽���ļ�
		//SEShellRun������mdlShellExecͨ��ģ���еĺ���
		SEShellRun(StrAppend(TEXT("NotePad.exe  \""),szFileResult,TEXT(" \"")),true);
	}
	else 
	{
		//���model�ļ��Ƿ�������
		if(!TestFileExist(szModelFile,TEXT("model�ļ�����ʧ�ܣ�δ������model����ļ���"))) return false;

		MsgBox(StrAppend(TEXT("model�ļ������ɣ�"),szModelFile),TEXT("ѵ�����"),mb_OK,mb_IconInformation);
	}
	return true;
} 

void form1_Load()
{   //form1����ʱҪִ�еĹ���

	//��ؼ�ID_cboKernels���˺����������ѡ��
	CBControl cboKernels(ID_cboKernels);
	cboKernels.AddItem(TEXT("���Ժ�(Linear,t=0)"));
	cboKernels.AddItem(TEXT("����ʽ��(Polynomial,t=1)"));
	cboKernels.AddItem(TEXT("��˹�������(Radial Basis Function,t=2)"));
	cboKernels.AddItem(TEXT("�����������(Sigmoid,t=3)"));
	cboKernels.ListIndexSet(4);//Ĭ��ѡ��4����Ŀ��Sigmoid�ˣ�

	//��ؼ�ID_cboFold��������֤�������ѡ��
	CBControl cboFold(ID_cboFold);
	cboFold.AddItem(TEXT("2"));
	cboFold.AddItem(TEXT("3"));
	cboFold.AddItem(TEXT("4"));
	cboFold.AddItem(TEXT("5"));
	cboFold.AddItem(TEXT("6"));
	cboFold.AddItem(TEXT("8"));
	cboFold.AddItem(TEXT("10"));
	cboFold.TextSet(TEXT("5"));//Ĭ��5�۽�����֤
}

void cmdBrowDataFile_Click()
{
	LPTSTR file;
	OsdSetFilter(TEXT("�ı��ļ�(*.txt)|*.txt"));
	file=OsdOpenDlg(form1.hWnd(),TEXT("��ѡ��һ���ı��ļ�"));
	if(*file) form1.Control(ID_cboDataFile).TextSet(file);
}

void cmdTrain_Click()
{
	//����SVM���ݼ��ļ�
	TCHAR * szFile=form1.Control(ID_cboDataFile).Text();
	/*if(!GenSVMDataFile(szFile)) return;*/

	//�������º��������ȹ�һ�����ݣ�Ȼ�����SVMѵ����������ѵ�����
	//��2������ΪNULL��ʾ��n-�۽�����֤��������model�ļ�
	RunSVM(szFile,NULL);
}

void cmdGenModel_Click()
{
	//���ѡ��model�ļ�Ҫ���浽��λ�ú��ļ���
	OsdSetFilter(TEXT("�ı��ļ�(*.txt)|*.txt"));
	TCHAR * file=OsdSaveDlg(form1.hWnd(),0,TEXT("��ָ��Ҫ�����model�ļ�"));
	if(* file==TEXT('\0')) return;
	//����SVM���ݼ��ļ�
	TCHAR * szFile=form1.Control(ID_cboDataFile).Text();
	/*if(!GenSVMDataFile(szFile)) return;*/
	//�������º��������ȹ�һ�����ݣ�Ȼ�����SVMѵ����������ѵ�����
	//��2��������ΪNULL��ʾ����n-�۽�����֤��Ҫ����model�ļ�
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