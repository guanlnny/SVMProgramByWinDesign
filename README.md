# SVMProgramByWinDesign
This project is an application of SVM binary classification model in biology, and SVM was visualized by windows programming.
----------------------------------------------------------------------------------------------------------------------------
###工具：
visual studio 2010+
Libsvm

----------------------------------------------------------------------------------------------------------------------------
###Soure资源包介绍：
#Libsvm：台湾大学林智仁教授开发的svm简易软件包，其中包含有可以黑屏调用的归一化操作机svm-scale，训练机svm-train，测试机svm-predict。

#data：MEROPS - the Peptidase Database, https://www.ebi.ac.uk/merops/, Source>data文件夹中给出了训练集train.txt和测试集test.txt，
train.txt中有2104个样本，每个样本包含102个特征值，test.txt中有200个样本，每个样本同样包含102个特征值；
本svm版本仅支持txt读取数据集，数据集均要求指定的svm数据格式，即第一列为标签值1或-1，后续列为特征值，每列以空格间隔，具体参照给出的样例train.txt、test.txt。

#exe：Source>exe文件夹是一个可以直接使用的SVM窗体程序，在该文件夹下双击SVM.exe运行即可。

#results：Source>results给出了data样例中train.txt的训练结果training_result文件、训练模型trainmodel文件，以及test.txt的测试结果testout文件；
其中，训练测试均采用线性核svm（即t=0），五折交叉验证方法。
![image](https://user-images.githubusercontent.com/74043204/130211492-a9843a37-708e-4a68-83e4-08347844d164.png)

#Source源码：visual studio新建一个工程，将Source文件夹下的cpp文件添加至源文件，h文件添加至头文件，main.ico（窗口运行程序图标）和template.rc（Dialog设计）添加至资源文件；
最后将Libsvm文件夹中的svm-scale、svm-train、svm-predict三个文件复制到新建工程的本地文件夹中，工程即可编译成功。

----------------------------------------------------------------------------------------------------------------------------
###最后，欢迎在遵守License的前提下，在此源码基础上进行再创作。
