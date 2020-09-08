#include "p2c.tab.h"
#include "semantic_analyser.h"
#include "codes_generator.h"

#include <string>
#include <iostream>

#define COMPILE_TO_BIN true

using namespace std;

extern Program *root;

int main(int argc, char *argv[]) {
    string fileName;
    string noExtendedNameFileName;

    // 处理文件名
    if (argc != 2) {
        cout << "Invalid arguments input" << endl;
        exit(1);
    }
    fileName = argv[1];
    int pos = fileName.find('.');
    if (pos == -1) {
        cout << "Invalid file name" << endl;
        exit(1);
    }
    noExtendedNameFileName = fileName.substr(0, pos);
    freopen(argv[1], "r", stdin);

    // 开始编译功能
    cout << "开始编译" << endl;

    if (lexical_and_syntax_analyse())
        exit(1);
    cout << "词法&语法分析成功" << endl;


    if (!semantic_analyse(root))
        exit(2);
    cout << "语义分析成功" << endl;


    generate_codes(root, noExtendedNameFileName);
    cout << "代码生成成功" << endl;

    // 生成二进制代码
    if (COMPILE_TO_BIN) {
        string gcc_job = "gcc -o ";
        gcc_job += noExtendedNameFileName;
        gcc_job += " ";
        gcc_job += noExtendedNameFileName;
        gcc_job += ".c";
        cout << "   GCC PART 1: Doing gcc Compile!\n     "+ gcc_job << endl;
        system(gcc_job.data());
        cout << "GCC\t->\tgcc Compile Done!" << endl;
        cout << "二进制代码文件：\'" + noExtendedNameFileName + "\'"<< endl;
    }

    return 0;
}