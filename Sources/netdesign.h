//------------------------------- netdesign.h  --------------------------------

/***************************************************************************
                            -  Description
                             -------------------
    Begin                : 19 March, 2013
    Copyright            : (C) 2013 by Simo
    E-Mail               : simo@furrydolphin.net
    Version              : 1.2.0

    ************************************************************************

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

#ifndef SDNET_H
#define SDNET_H

#include "defs.h"

typedef unsigned int NMuint;

/*
        Name: SDNetMatch

	Type: Namespace

	Member Methods:
                        PiDesigner: Returns impedances for Pi Network
                        LNetDesigner: Designs the high or low input impedance L networks.
                        TNetDesigner: Designs the T Network.
                        SeriesNetDesigner: Designs a series inductor, low impedance L network

       Note: These functions return multiple values by reference, and return either 1
             (success) or 0 (failure) of sanity checks.
*/

namespace NetDesign
{
    NMuint PiDesigner(double, double, double, double&, double&, double&);
    NMuint LNetDesigner(double, double, double&, double&, double&, const NMuint);
    NMuint CapDivDesigner(double, double, double, double&, double&, double&);
    NMuint TNetDesigner(double, double, double, double&, double&, double&);
    NMuint SeriesNetDesigner(double, double, double, double &, double&,
			     double&, double&, const NMuint);
}

#endif

//------------------------------- netdesign.h  --------------------------------
