#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <string>
#include <chrono>
#include <thread>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define YELLOW  "\033[33m"      /* Yellow */

void enableANSIColors() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }
#endif
}

string generateMAC() {
    string chars = "0123456789ABCDEF";
    string mac = "00:1A:79:";
    mac += chars[rand() % 16];  // 4th byte, first hex digit
    mac += chars[rand() % 16];  // 4th byte, second hex digit
    mac += ':';
    mac += chars[rand() % 16];  // 5th byte, first hex digit
    mac += chars[rand() % 16];  // 5th byte, second hex digit
    mac += ':';
    mac += chars[rand() % 16];  // 6th byte, first hex digit
    mac += chars[rand() % 16];  // 6th byte, second hex digit
    return mac;
}

void generateMACs(int mode, const string& custom, int number) {
    string filename = "MacAddresses.txt";
    ofstream fout(filename);
    if (!fout) {
        cerr << RED << "Error opening file: " << filename << RESET << endl;
        return;
    }
    auto start = chrono::steady_clock::now();
    set<string> generatedMACs;
    string chars = "0123456789ABCDEF";

    for (int i = 0; i < number; ++i) {
        string mac;
        if (mode == 1) {
            mac = generateMAC();
        } else if (mode == 2) {
            string customMAC = custom;
            for (size_t pos = 0; pos < customMAC.size(); ++pos) {
                if (customMAC[pos] == '*') {
                    customMAC[pos] = chars[rand() % 16];
                }
            }
            mac = customMAC;
        }
        generatedMACs.insert(mac);
    }
    for (const auto& mac : generatedMACs) {
        fout << mac << endl;
    }
    fout.close();
    int duplicatesRemoved = number - generatedMACs.size();
    cout << GREEN << "[*] Removing duplicates..." << RESET << endl;
    cout << GREEN << "[*] Removed " << duplicatesRemoved << " duplicate(s)." << RESET << endl;
    cout << GREEN << "[*] Finished! Results have been saved in " << filename << RESET << endl;
    auto end = chrono::steady_clock::now();
    cout << GREEN << "[*] Finished in "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() / 1000.0
         << " seconds!" << RESET << endl;
}
void printBanner() {
    cout << CYAN << R"(
       ███╗   ███╗ █████╗  ██████╗     ██████╗ ███████╗███╗   ██╗███████╗██████╗  █████╗ ████████╗ ██████╗ ██████╗ 
       ████╗ ████║██╔══██╗██╔════╝    ██╔════╝ ██╔════╝████╗  ██║██╔════╝██╔══██╗██╔══██╗╚══██╔══╝██╔═══██╗██╔══██╗
       ██╔████╔██║███████║██║         ██║  ███╗█████╗  ██╔██╗ ██║█████╗  ██████╔╝███████║   ██║   ██║   ██║██████╔╝
       ██║╚██╔╝██║██╔══██║██║         ██║   ██║██╔══╝  ██║╚██╗██║██╔══╝  ██╔══██╗██╔══██║   ██║   ██║   ██║██╔══██╗
       ██║ ╚═╝ ██║██║  ██║╚██████╗    ╚██████╔╝███████╗██║ ╚████║███████╗██║  ██║██║  ██║   ██║   ╚██████╔╝██║  ██║
       ╚═╝     ╚═╝╚═╝  ╚═╝ ╚═════╝     ╚═════╝ ╚══════╝╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝
       The Fastest MAC Generator in C++ 
       https://github.com/Chainski/MAC-Generator  	
    )" << RESET << endl;
}
void setUTF8Console() {
    system("mode con cols=122 lines=40");  
    system("chcp 65001 > nul"); 
    system("cls");              
}
void typeWriterEffect(const string& text, int delayMilliseconds) {
    for (char c : text) {
        cout << YELLOW << c << RESET << flush;  
        this_thread::sleep_for(chrono::milliseconds(delayMilliseconds));  
    }
    cout << endl;  
}
int main() {
    srand(time(0));  
    setUTF8Console();  
    printBanner();  
    enableANSIColors();
	typeWriterEffect("[*] This program will generate random MAC addresses select a mode from the options below to continue\n", 11);
    int mode;
    cout << BLUE << "Select Mode:" << RESET << endl;
    cout << BLUE << "1. Default: 00:1A:79:**:**:**" << RESET << endl;
    cout << BLUE << "2. Custom (Example: 00:1A:79:*8:1B:**)" << RESET << endl;
    cout << BLUE << "> " << RESET;
    cin >> mode;
    string custom;
    if (mode == 2) {
        cout << YELLOW << "[*] Enter custom mode: " << RESET;
        cin.ignore();
        getline(cin, custom);
    }
    int number;
    cout << YELLOW << "[*] Enter the amount of MACs to generate: " << RESET;
    cin >> number;
    generateMACs(mode, custom, number);
    cout << "[*] Press ENTER to close." << endl;
    cin.ignore();
    cin.get();
    return 0;
}