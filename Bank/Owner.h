#include <string>
//define an owner class that can be used to create a bank account, allows for an additional layer of encapsulation
class Owner{
    private:
        std::string firstName;
        std::string lastName;
        int SSN;

    public:
        //setters and getters
        void setFirstName(const std::string firstName){this->firstName = firstName;}
        std::string getFirstName() { return firstName;}

        void setLastName(const std::string lastName){this->lastName =lastName;}
        std::string getLastName() { return lastName;}
        
        void setSSN(int SSN){this->SSN =SSN;}
        int getSSN() { return SSN;}

        //constructor
        Owner(std::string firstName, std::string lastName, int SSN){
            this->firstName = firstName;
            this->lastName = lastName;
            this->SSN=SSN;}
        Owner() : firstName(""), lastName(""), SSN(0) {}


};