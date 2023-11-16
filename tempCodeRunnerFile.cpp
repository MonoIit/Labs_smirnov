
    cout << "1. delete" << endl;
                cout << "2. change" << endl;
                
                switch (input_value<int>(1, 2)) {
                case 1: {
                    for (int j : IDS) {
                        pipes.erase(j);
                    } 
                    break;
                }
                case 2: {
                    for (int j : IDS) {
                        pipes[j].change();
                    } 
                    break;
                }
                }