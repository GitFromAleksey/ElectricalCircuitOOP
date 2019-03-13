/*
 * engine.cpp
 *
 *  Created on: 13 мар. 2019 г.
 *      Author: user1
 */

#include "stddef.h"
#include <vector>

class Engine
{
public:
    Engine()
    {
        std::cout << "Create engine" << std::endl;

        Tengine = cTengine_begin;
        Tenv = cTengine_begin;

        I = cI;
        t_overheat = ct_overheat;
        Hm = cHm;
        Hn = cHn;
        Hc = cHc;

        a = 0.0;
        V_heat = 0.0;
        Vc = 0.0;
        M = 0;
        C = 0;
    }
    ~Engine(){}

    // вычисление ускорения
    float Calc_a()
    {
        return a = M/I;
    }

    // вычисление скорости нагрева
    float Calc_Vheat()
    {
        return V_heat = M*Hm + N*N*Hn;
    }

    // вычисление скорости охлаждения
    float Calc_Vc()
    {
        return Vc = C * (Tenv - Tengine);
    }

    void Set_Vector_M_V_Depend(std::vector<float> &m, std::vector<float> &v)
    {
        vM = m;
        vV = v;
    }

private:
    // начальные условия
    const float cTengine_begin = 25;
    const float cI = 1.0;
    const float ct_overheat = 110;
    const float cHm = 1.0;
    const float cHn = 1.0;
    const float cHc = 1.0;

    // задаваемые параметры
    float I; // момент инерции, кг*м2
    float t_overheat; // температура перегрева, градусы цельсия
    float Hm; // коэф.скорости нагрева от крутящего момента, [град/(H*m*сек)]
    float Hn; // коэф. скорости нарева от частоты вращения [C*сек/рад2]
    float Hc; // коэф. скорости охлаждения от температуры двигателя [1/сек]
    std::vector<float> vM; // зависимость момента от скорости вращения
    std::vector<float> vV; // зависимость момента от скорости вращения

    float C; // коэф. зав. охлаждения от температуры двигателя и среды

    // вычисляемые параметры
    float Tengine; // температура двигателя, град цельсия
    float Tenv; // температура окруж среды, град цельсия
    float a; // ускоение коленвала [Н/(кг*м)]
    float V_heat; // скорость нагрева двигателя [град/сек]
    float Vc; // скорость охлаждения двигателя [град/сек]
    float M; // текущий момент двигателя, Н*м
    float N; // обороты двигателя, 1/сек
};


