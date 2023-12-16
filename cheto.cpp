#include <iostream>
#include <format>
#include <chrono>
#include "GTN.h"

using namespace std;
using namespace chrono;

void menu()
{
    cout << "1. Add pipeline" << endl;
    cout << "2. Add KC" << endl;
    cout << "3. Check elements" << endl;
    cout << "4. Change the pipeline" << endl;
    cout << "5. Change the KC" << endl;
    cout << "6. Save" << endl;
    cout << "7. Download" << endl;
    cout << "8. Add connection" << endl;
    cout << "9. Remove connection" << endl;
    cout << "10. Display connection" << endl;
    cout << "11. Show connections" << endl;
    cout << "12. Clrea graph" << endl;
    cout << "13. Sort connections" << endl;
    cout << "0. Close" << endl;
}

int main()
{
    redirect_output_wrapper cerr_out(cerr);
    string time = "now";
    // string time = std::format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
    ofstream logfile("log_" + time);
    if (logfile)
        cerr_out.redirect(logfile);

    GTN GTN;
    bool flag = true;
    while (flag)
    {
        menu();
        switch (input_value<int>(0, 15))
        {
        case 1:
        {
            GTN.add_pipe();
            break;
        }
        case 2:
        {
            GTN.add_KC();
            break;
        }
        case 3:
        {
            GTN.display_objects();
            break;
        }
        case 4:
        {
            GTN.change_pipe();
            break;
        }
        case 5:
        {
            GTN.change_KC();
            break;
        }
        case 6:
        {
            GTN.save_data();
            break;
        }
        case 7:
        {
            GTN.download_data();
            break;
        }
        case 8:
        {
            GTN.addConnection();
            break;
        }
        case 9:
        {
            GTN.removeConnection();
            break;
        }
        case 10:
        {
            GTN.displayConnections();
            break;
        }
        case 11:
        {
            GTN.DisplayGraph();
            break;
        }
        case 12:
        {
            GTN.FullClearGraph();
            break;
        }
        case 13:
        {
            GTN.topologicalSort();
            break;
        }
        case 0:
        {
            flag = false;
            break;
        }
        default:
        {
            cout << "please, enter suggested numbers" << endl;
            break;
        }
        }
    }
    cerr << 0;
    return 0;
}

// Логирование
