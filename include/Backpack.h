#ifndef BACKPACK_H
#define BACKPACK_H
#include <iostream>

class Backpack
{
    public:
        Backpack();
        virtual ~Backpack();
        void addnum(int , int); //id,num
        int getlvl(int); //id
        void changeselect(int);
        int getselected();

    protected:

    private:
        int* characternum;
        int* characterlvl;
        int selected;
};

#endif // BACKPACK_H
