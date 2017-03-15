
/*
1.cl.exe文件是Visual C\C++的编译器，它将程序源代码文件编译为obj文件。


2.rc.exe文件是资源编译器。工程项目中的．rc文件中包含了对程序中所使用资源（菜单、图标等）的描述。
rc.exe将．rc格式的文件编译为.res文件，供链接器链接到可执行文件中。


3.link.exe是Windows平台的链接器，它将cl.exe编译生成的obj文件，资源编译器生成的.res文件，以及lib目录下的lib文件等链接成可执行的exe文件、dll文件等。

在程序编译完成后，生成的文件是以obj为扩展名的对象文件，link.exe是将对象文件和库链接起来以创建可执行程序文件或动态链接库文件的工具。


link.exe的输入文件包括obj文件、lib文件、exp文件、def文件、res文件、txt文件、ilk文件。输出文件是exe文件、dll文件、sys文件等可执行程序文件。


其他工具

1．BSCMAKE．EXE
生成一个信息文件(．bsc)，用于浏览程序中的符号（类、函数、数据、宏和类型）信息。
可以在集成开发环境的浏览窗口中查看这些信息（.bsc文件也可以在IDE中生成）。


2． LIB．EXE
用于生成COFF格式的lib库文件，可用于创建导出文件和引用导出定义的导入库，在为其他开发人员提供开发接口时非常有用。


3． EDITBIN.EXE
可用于编辑COFF格式的二进制文件。


4．DUMPBIN.EXE
可显示COFF二进制文件的有关信息，比如符号表等。
比如，使用dumpbin.exe分析第1章的start.exe。选择“工具”→“Visual Studio命令提示”切换到start.exe所在的目录，运行：
在bin_info.txt中包含了可执行文件中非常丰富的信息，包括文件头信息、节信息等。


5． NMAKE.EXE
程序维护实用工具，读取和执行生成文件。将在3.3节中详细
介绍nmake的使用。


6． ERRLOOK．EXE
错误查找工具，与GetLastError API函数配合使用，在程序调试时起到了很多的作用，用于分析Windows API的调用错误。
如图3 - 1所示，在Visual Studio IDE中，可以通过菜单“工具”→“错误查找”来使用。

*/