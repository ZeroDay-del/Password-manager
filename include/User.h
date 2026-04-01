#ifndef USER_H
#define USER_H
#include <string>

using namespace std;
class User
{
    public:
        // constructor
        User(string u, string p, string w);

        // functions
        void display();
        string getUsername();
        string publish();
        virtual ~User();


    private:
        string website;
        string password;
        string username;
};

#endif // USER_H
