#include <iostream>
#include <unordered_map>
using namespace std;

int mainMenu()
{
    cout << ("Enter an action:\n");
    cout << ("1. Add a user\n");
    cout << ("2. List all users\n");
    cout << ("3. Manage a user's passwords\n");
    cout << ("4. Delete a user\n");
    cout << ("5. Exit\n");
    int n;
    cin >> n;
    cin.ignore(1000, '\n'); // Clear any leftover characters in the input buffer
    return n;
}

int subMenu(string user_name)
{
    cout << "Managing passwords for " + user_name + ":\n";
    cout << "1. Store an encrypted password\n";
    cout << "2. List all sites and passwords\n";
    cout << "3. Retrieve an unencrypted password\n";
    cout << "4. Delete a site\n";
    cout << "5. Exit\n";
    int n;
    cin >> n;
    return n;
}

// Function to encrypt or decrypt a password
string xorEncryptDecrypt(const string &input, const string &key)
{
    string output = input;
    for (size_t i = 0; i < input.size(); ++i)
    {
        output[i] ^= key[i % key.size()]; // XOR each character with the key
    }
    return output;
}

int main()
{

    unordered_map<string, unordered_map<string, string> > outer_dict; //"In C++, you generally don't need to explicitly initialize an std::unordered_map the way you might in Java because C++ automatically initializes it as an empty map when you create it." -ChatGPT

    int userInput;
    bool outer_loop = true;
    while (outer_loop)
    {
        userInput = mainMenu();
        switch (userInput)
        {
        case 1:
        {
            string userName;
            cout << "You have chosen adding a user.\n";
            cout << "Please input the username you want to add:\n";
            cin >> userName;
            if (outer_dict.find(userName) == outer_dict.end())
            {
                unordered_map<string, string> inner_dict;
                outer_dict[userName] = inner_dict;
                cout << "Username added successfully!\n";
            }
            else
            {
                cout << userName + " already being stored by the password manager.\n";
            }
            break;
        }

        case 2:
        {
            if (outer_dict.empty())
            {
                cout << "There are no usernames currently in the password manager!\n";
                break;
            }
            cout << "Below is the list of all stored usernames: \n";
            for (const auto &kv_pair : outer_dict)
            {
                cout << kv_pair.first + "\n";
            }
            break;
        }

        case 3:
        {
            string userName;
            cout << "You have chosen managing a user's passwords.\n";
            cout << "Please input the username whose passwords you want to manage:\n";
            cin >> userName;
            if (outer_dict.find(userName) == outer_dict.end())
            {
                cout << userName + " not found\n";
                break;
            }
            int userInput2;
            bool inner_loop = true;
            while (inner_loop)
            {
                userInput2 = subMenu(userName);
                switch(userInput2)
                {
                case 1:
                {
                    string siteName;
                    string sitePassword;
                    cout << "You have chosen adding an encrypted password for a website.\n";
                    cout << "Please input the website whose password you want to add:\n";
                    cin >> siteName;
                    cout << "Please input the password for this website:\n";
                    cin >> sitePassword;
                    string encryptionKey = "starman123";
                    string encryptedPassword = xorEncryptDecrypt(sitePassword, encryptionKey);
                    outer_dict[userName][siteName] = encryptedPassword;
                    cout << "Your password has been encrypted and stored!\n";
                    break;
                }
                case 2:
                {
                    if (outer_dict[userName].empty())
                    {
                        cout << "There are no website passwords currently stored for this user.\n";
                        break;
                    }
                    cout << "Below is the list of all stored websites, along with their encrypted passwords:\n";
                    unordered_map<string, string> inner_dict = outer_dict[userName];
                    for (const auto &kv_pair : inner_dict)
                    {
                        cout << kv_pair.first + " " + kv_pair.second + " \n";
                    }
                    break;
                }
                case 3:
                {
                    unordered_map<string, string> inner_dict = outer_dict[userName];
                    string siteName;
                    cout << "Please input the website whose encrypted password you want to retrieve:\n";
                    cin >> siteName;
                    if (inner_dict.find(siteName) == inner_dict.end())
                    {
                        cout << "This website's password is not currently stored for this user.\n";
                        break;
                    }
                    cout << "Password displayed is below:\n";
                    string encryptionKey = "starman123";
                    string unencrypted_password = xorEncryptDecrypt(inner_dict[siteName], encryptionKey);
                    cout << "Website name: " + siteName + "\n Password:" + unencrypted_password + "\n";
                    break;
                }
                case 4:
                {
                    string siteName;
                    cout << "Please input the website you want to delete:\n";
                    cin >> siteName;
                    if (outer_dict[userName].find(siteName) == outer_dict[userName].end())
                    {
                        cout << "This website is not currently stored for this user.\n";
                        break;
                    }
                    outer_dict[userName].erase(siteName);
                    cout << "Site " + siteName + " has been erased for user " + userName + ".\n";
                    break;
                }
                case 5:
                {
                    inner_loop = false;
                    break;
                }
                default:
                {
                    cout << "Please enter a valid input!\n";
                    break;
                }
                }
            }
            break;
        }
        case 4:
        {
            string userName;
            cout << "You have chosen deleting a user.\n";
            cout << "Please input the username you want to delete:\n";
            cin >> userName;
            if (outer_dict.find(userName) == outer_dict.end())
            {
                cout << userName + " not found\n";
            }
            else
            {
                outer_dict.erase(userName);
                cout << "Username deleted successfully!\n";
            }
            break;
        }
        case 5:
        {
            outer_loop = false;
            break;
        }
        default:
        {
            cout << "Please enter a valid input!\n";
            break;
        }
        }
    }
    return 0;
}
