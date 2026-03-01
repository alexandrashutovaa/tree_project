#ifndef _ZERO_H_
#define _ZERO_H_

#include "cell.hpp"
#include <vector>

class rootcell : public cell {

private:
    float energy;
    float water; 

public:
    rootcell(Coords coords);
    virtual ~rootcell();
    
    void tick();
    void spread();
    
    bool SpendRequest(float neededE, float neededW);
    void getResource(char type, float amount);
    
    //�� � ��� �������� ������� � ���� ���������, ����� �������� ��� ��������� ����� ���� �����
};

#endif