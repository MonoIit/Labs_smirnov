#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct pipeline 
{
    string Name;
    int Lenght;
    int Diameter;
    bool Status;
};

struct KC
{
    string Name;
    int Amount;
    int Working_amount;
    double Efficiency;
};



int check_int(string a) {
    cout << a << endl;
    int b;
    cin >> b;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "try again" << endl;
        cin >> b;
    }
    return b;
}

double check_double(string a) {
    cout << a << endl;
    double b;
    cin >> b;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "try again" << endl;
        cin >> b;
    }
    return b;
}

bool check_bool(string a) {
    cout << a << endl;
    string b;
    cin >> b;
    bool flag = true;
    while (flag) {
        if (b == "repairing") {
            return 0;
        } else if (b == "working") {
            return 1;
        } else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Enter 'working' or 'repairing'" << endl;
            cin >> b;
        }
    }
}



KC get_data(KC m) {
    cout << "Enter manufactory name\n";
    cin >> m.Name;
    m.Amount = check_int("Enter amount of manufactories");
    m.Working_amount = check_int("Enter amoun of working manufactories");
    m.Efficiency = check_double("Enter the value of 'efficiency'"); 
    return m;
}

void display_data(const KC& m) {
    cout << "Your KC:" << endl;
    cout << "Name: " << m.Name << endl;
    cout << "Amount of manufactories: " << m.Amount << endl;
    cout << "Amount of working manufactories: " << m.Working_amount << endl;
    cout << "The value of 'efficiency': " << m.Efficiency << endl;
}

KC add_KC(KC m) {
    m = get_data(m);
    display_data(m);
    return m;
}



pipeline getData(pipeline& p) {
    cout << "Enter pipeline name\n";
    cin >> p.Name;
    p.Lenght = check_int("Enter pipeline lenght");
    p.Diameter = check_int("Enter pipeline d");
    p.Status = check_bool("Enter pipeline status (repairing/working)");
    return p;
}

void displayData(const pipeline& p) {
    cout << "Your pipeline:" << endl;
    cout << "Name: " << p.Name << endl;
    cout << "Lenght: " << p.Lenght << endl;
    cout << "Diameter: " << p.Diameter << endl;
    cout << "Status: ";
    if (p.Status == 1) {
        cout << "working" << endl;
    } else if (p.Status == 0) {
        cout << "repairing" << endl;
    } else {
        cout << "unknown" << endl;
    }
}

pipeline add_pipeline(pipeline p) { 
    p = getData(p);
    displayData(p);
    return p;
}

/*что конкретно должно изменятся в 4 и 5 пункте*/
/*Добавить проверку на то, что число рабающих цехов меньше, чем их колличество*/
void menu() {
    cout << "1. Add pipeline" << endl;
    cout << "2. Add ceh" << endl;
    cout << "3. Check all elements" << endl;
    cout << "4. Change the pipeline" << endl;
    cout << "5. Change the ceh" << endl;
    cout << "6. Save" << endl;
    cout << "7. Download" << endl;
    cout << "0. Close" << endl;
}

void save(pipeline p, KC m) {
    ofstream out;
    out.open("datas.txt");
    out << p.Name << " ";
    out << p.Lenght << " ";
    out << p.Diameter << " ";
    out << p.Status << " ";
    out << m.Name << " ";
    out << m.Amount << " ";
    out << m.Working_amount << " ";
    out << m.Efficiency << " ";
    out.close();
}

void download(pipeline& p, KC& m) {
    std::ifstream in("datas.txt");
    if (in.is_open())
    {
        string name1, name2;
        int a, b, c, d;
        double x;
        bool f;
        in >> name1 >> a >> b >> f >> name2 >> c >> d >> x;
        p.Name = name1;
        p.Lenght = a;
        p.Diameter = b;
        p.Status = (f == 1) ? "working" : "repairing";
        m.Name = name2;
        m.Amount = c;
        m.Working_amount = d;
        m.Efficiency = x;
    }
    in.close();
}



int main() {
    bool flag = true;
    bool current_pipeline = false;
    bool current_KC = false;
    menu();
    KC KC_1;
    pipeline pipeline_1;
    while (flag) {
        int n;
        cin >> n;
        switch (n)
        {
        case 1:
            pipeline_1 = add_pipeline(pipeline_1);
            current_pipeline = true;
            menu();
            break;
        case 2:
            KC_1 = add_KC(KC_1);
            current_KC = true;
            menu();
            break;
        case 3:
            if (current_pipeline == 1) {
                displayData(pipeline_1);
            } else {
                cout << "no pipelines\n";
            }
            if (current_KC == 1) {
                display_data(KC_1);
            } else {
                cout << "no KCs\n";
            }
            menu();
            break;
        case 4:
            /*code*/
            break;
        case 5:
            /*code*/
            break;
        case 6:
            save(pipeline_1, KC_1);
            menu();
            break;
        case 7:
            download(pipeline_1, KC_1);
            displayData(pipeline_1);
            display_data(KC_1);
            menu();
            break;
        case 0:
            flag = false;
            break;    
        default:
            cout << "please, enter offered numbers" << endl;
            menu();
            break;
        }
    }
    return 0;
}









