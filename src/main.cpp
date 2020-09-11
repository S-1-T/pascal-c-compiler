#include "yacc/p2c.tab.h"
#include "yacc/semantic_analyser.h"
#include "codes/codes_generator.h"

#include <string>
#include <iostream>

#define COMPILE_TO_BIN true

using namespace std;

extern Program *root;

int main(int argc, char *argv[])
{
    string fileName;
    string noExtendedNameFileName;

    // 处理文件名
    if (argc != 2)
    {
        cout << "输入参数无效" << endl;
        exit(1);
    }
    fileName = argv[1];
    int pos = fileName.find('.');
    if (pos == -1)
    {
        cout << "无效的文件" << endl;
        exit(1);
    }
    noExtendedNameFileName = fileName.substr(0, pos);
    freopen(argv[1], "r", stdin);

    // 开始编译功能
    cout << "开始编译" << endl;

    if (lexical_and_syntax_analyse())
        exit(1);
    cout << "词法 & 语法分析成功" << endl;

    if (!semantic_analyse(root))
        exit(2);
    cout << "语义分析成功" << endl;

    generate_codes(root, noExtendedNameFileName);
    cout << "代码生成成功" << endl;

    // 生成二进制代码
    if (COMPILE_TO_BIN)
    {
        string gcc_job = "gcc -o " + noExtendedNameFileName + " " + noExtendedNameFileName + ".c";
        cout << "开始可执行文件编译：" + gcc_job << endl;
        system(gcc_job.data());
        cout << "编译结束" << endl;
        cout << "可执行文件：\'" + noExtendedNameFileName + "\'" << endl;
    }

    return 0;
}