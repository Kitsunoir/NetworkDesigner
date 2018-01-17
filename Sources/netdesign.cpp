//-------------------------------- netdesign.cpp -------------------------------

/***************************************************************************
                            -  Description
                             -------------------
    Begin                : 28 January, 2012
    Copyright            : (C) 2003 by Simo
    E-Mail               : simo@furrydolphin.net
    Version              : 1.2.0
 ***************************************************************************

 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *                                                                         *
 *   If software can be free, why can't dolphins?                          *
 *                                                                         *
 ***************************************************************************/

#include <math.h>

#ifdef INSTR
#include <stdio.h>
#endif

#include "netdesign.h"

NMuint NetDesign::PiDesigner(double aRi, double aRl, double aQdes,
			     double &aB1, double &aB3, double &aX2)
{

    double Q1, Rv;

#ifdef INSTR
  printf("\nIn Function NetDesign::PiDesigner\nInput Values");
  printf("\nRi= %f", aRi);
  printf("\nRl= %f", aRl);
  printf("\nQdes= %f", aQdes);
#endif

    if (aRi < aRl)
    {
        aB1= 0;
        aB3= 0;
        aX2= 0;

#ifdef INSTR
  printf("\nError Code 1");
#endif
        return 1;
    }

    Rv=  aRi/(1 + POW2(aQdes));
    Q1=  pow((aRl/Rv -1), 0.5);
    aB1= Q1/aRl;
    aB3= aQdes/aRi;
    aX2= Rv * (Q1 + aQdes);

#ifdef INSTR
  printf("\nRv= %f (Intermediate Value)", Rv);
  printf("\nQ1= %f (Intermediate Value)", Q1);
  printf("\nB1= %f", aB1);
  printf("\nX2= %f", aX2);
  printf("\nB3= %f", aB3);
  printf("Leaving function NetDesign::PiDesigner");
#endif

    return 0;
}

//------------------------------------------------------------------------------

NMuint NetDesign::LNetDesigner(double aRi, double aRl, double &aX1, double &aX2,
			       double &aQl, const NMuint IDCode)
{
#ifdef INSTR
  printf("\nEntering Function: NetDesign::LNetDesigner\nInput Values");
  printf("\naRi= %f", aRi);
  printf("\naRl= %f", aRl);
  printf("\nIDCode= %i", IDCode);
#endif

    switch(IDCode)
    {
        case L_HIZ_I:

        case L_HIZ_II:

#ifdef INSTR
  printf("\nIn case L_HIGH_Z:");
  printf("\nRi= %f", aRi);
  printf("\naRl= %f", aRl);
#endif
	    if (aRi < 2*aRl)
	    {
		aX1= 0;
		aX2= 0;
		aQl= 0;
#ifdef INSTR
  printf("\nError Code: 1");
#endif
		return 1;
	    }

	    aQl= pow((aRi/aRl - 1), 0.5);
	    aX1= aRl * aQl;
	    aX2= aX1 * (1 + pow(aQl, -2));
	    break;

        case L_LOZ_I:

        case L_LOZ_II:

#ifdef INSTR
  printf("\nIn case L_LOW_Z:");
  printf("\nRi= %f", aRi);
  printf("\nRl= %f", aRl);
#endif

            if (aRl < 2*aRi)
	    {
		aX1= 0;
		aX2= 0;
		aQl= 0;
#ifdef INSTR
  printf("\nError Code: 2");
#endif
		return 2;
	    }

            aQl= pow((aRl/aRi - 1), 0.5);
            aX1= aRl/aQl;
	    aX2= aX1/(1 + pow(aQl, -2));
	    break;
    }

#ifdef INSTR
  printf("\nX1= %f", aX1);
  printf("\nX2= %f", aX2);
  printf("\nQl= %f", aQl);
  printf("\nLeaving Function: NetDesign::LNetDesigner\n");
#endif

    return 0;
}

//------------------------------------------------------------------------------

NMuint NetDesign::CapDivDesigner(double aRi, double aRl, double aQnom, double &aXC1,
				 double &aXC2, double &aXL)
{
    double Rv, Qmin;

#ifdef INSTR
  printf("\nIn Function: NetDesign::CapDivDesigner\nInput Values");
  printf("\naRi= %f", aRi);
  printf("\naRl= %f", aRl);
  printf("\naBW= %f", aQnom);
#endif

    if (aRi < aRl*2)
    {
        aXC1= 0;
        aXC2= 0;
        aXL=  0;

#ifdef INSTR
  printf("\nError Code 1");
#endif
      return 1;
  }

    Qmin= pow((aRi/aRl -1), 0.5);

    if (aQnom < Qmin)
    {
	aXC1= 0;
	aXC2= 0;
	aXL=  0;
	return 2;
    }

    Rv=   aRl * (1 + POW2(aQnom));
    aXL=  aRi/aQnom;
    aXC2= aRl * pow((Rv/aRi - 1), -0.5);
    aXC1= ((aRl*aQnom)/(1 + POW2(aQnom))) * (1 - (aRl/(aQnom * aXC2)));

#ifdef INSTR
  printf("\nQmin= %f (Intermediate Value)", Qmin);
  printf("\nRv= %f (Intermediate Value)", Rv);
  printf("\nXC1= %f", aXC1);
  printf("\nXC2= %f", aXC2);
  printf("\nXL= %f", aXL);
  printf("\nLeaving function NetDesigner::CapDivDesigner");
#endif

    return 0;
}

//------------------------------------------------------------------------------

NMuint NetDesign::TNetDesigner(double aRi, double aRl, double aQdes,
			       double &aX1, double &aB2, double &aX3)
{
    double Q2, Rv;

#ifdef INSTR
  printf("\nEntering function NetDesigner\nInput Values:");
  printf("\naRi= %f", aRi);
  printf("\naRl= %f", aRl);
  printf("\nQdes= %f", aQdes);
#endif

    if (aRi < aRl)
    {
	aX1= 0;
	aB2= 0;
	aX3= 0;
#ifdef INSTR
  printf("\nError Code 1");
#endif
	return 1;
    }

    Rv=  aRl * (1 + POW2(aQdes));
    Q2=  pow((Rv/aRi - 1), 0.5);
    aX1= aQdes * aRl;
    aB2= (aQdes + Q2)/Rv;
    aX3= Q2/aRi;

    return 0;
}

//------------------------------------------------------------------------------

NMuint NetDesign::
SeriesNetDesigner(double aRi, double aRl, double aQi, double &aQload, double &aXC1,
		  double &aXC2, double &aXL, const NMuint IDCode)
{
    double Rv;

#ifdef INSTR
  printf("\nEntering function NetDesigner::SeriesNetDesigner");
#endif

    if (aRi > aRl)
    {
	aXC1= 0;
	aXC2= 0;
	aXL=  0;

#ifdef INSTR
  printf("\nError Code 1");
#endif
	return 1;
    }

    Rv=    aRi * (1 + POW2(aQi));
    aQload= pow((Rv/aRl -1), 0.5);

#ifdef INSTR
  printf("\nInput Values");
  printf("\nRi= %f", aRi);
  printf("\nRl= %f", aRl);
  printf("\nQi= %f", aQi);
  printf("\nRv= %f", Rv);
  printf("\naQload= %f", aQload);
#endif

    switch (IDCode)
    {
        case TWOCAP_L_I:

	    aXL= aRi * aQi;
	    aXC2= aQload * aRl;
	    aXC1= aRl/(aQi - aQload);

#ifdef INSTR
  printf("\nIn case TWOCAP_L_I:");
  printf("\nXL= %f", aXL);
  printf("\nXC2= %f", aXC2);
  printf("\nXC1= %f", aXC1);
#endif
	    break;

        case TWOCAP_L_II:

	    aXC1= aQi * aRi;
	    aXC2= aRl * pow((aRi/(aRl-aRi)), 0.5);
	    aXL=  aXC1 + (aRi*aRl/aXC2);

#ifdef INSTR
  printf("\nIn case TWOCAP_L_II:");
  printf("\nXC1= %f", aXC1);
  printf("\nXC2= %f", aXC2);
  printf("\nXL= %f", aXL);
#endif
	    break;
    }

#ifdef INSTR
  printf("\nLeaving function NetDesigner::SeriesNetDesigner");
#endif

    return 0;
}

//-------------------------------- netdesign.cpp -------------------------------
