#ifndef BASEMOVINGOBJECT_H
#define BASEMOVINGOBJECT_H


class BaseMovingObject
{
    public:
        BaseMovingObject();
        virtual ~BaseMovingObject();

        int Getcx() { return cx; }
        void Setcx(int val) { cx = val; }
        int Getcy() { return cy; }
        void Setcy(int val) { cy = val; }
        int Getvcx() { return vcx; }
        void Setvcx(int val) { vcx = val; }
        int Getvcy() { return vcy; }
        void Setvcy(int val) { vcy = val; }

        void move();

    protected:

    private:
        int cx;
        int cy;
        int vcx;
        int vcy;
        int objWidth;
        int objHeight;
};

#endif // BASEMOVINGOBJECT_H
