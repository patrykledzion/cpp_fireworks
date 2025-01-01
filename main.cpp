#include <iostream>
#include "Program.h"

int main()
{
    Program* program = new Program();
    program->Init();
    while (true)
    {
        program->Update();
        program->Draw();
    }
}
 