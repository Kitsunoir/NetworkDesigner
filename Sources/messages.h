//--------------------------------- textincl.h ---------------------------------

/***************************************************************************
                            -  Description
                             -------------------
    Begin                : 26 January, 2012
    Copyright            : (C) 2012 by Simo
    E-Mail               : simo@furrydolphin.net
    Version              : 1.2.0
 **************************************************************************/

/***************************************************************************
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

#ifndef TEXTS_H
#define TEXTS_H

#define HELP_ERROR \
"Can't open a web browser on this system."\
"\nEither you don't have one (highly unlikely, but possible)"\
"\nOr it's on some non-standard path, or it's broken, or"\
"\nthe permissions are set incorrectly."\
"\n"\
"\nPossibly your browser path config file is corrupt, missing, or moved from"\
"\nits proper location. Make sure its still good and/or located properly"

#define IMG_FILE_ERROR \
"Failed to open the circuit diagram image: %s"\
"\nPrepairing text only output. Check your"\
"\n\"Diagrams\" directory for missing/corrupted files."

#define OPEN_ERROR \
"Couldn't open the help file"\
"\nLost, deleted, or corrupted?"

#define NEW_SAVE_WARN \
"You haven't saved your current project yet!"\
"\nStart a new one anyway?"

#define EXIT_SAVE_WARN \
"You haven't saved your current project yet!"\
"\nQuit NetworkDesigner anyway?"

#define PI_NET_DSC \
"\nThe conventional PI Network serves"\
"\nwell for most FET, VFET, and, of course,"\
"\nvacuum tube circuits. Has good, third-order"\
"\nsuppression, the input capacitance serves to"\
"\nreduce high order harmonics, and works well"\
"\n as an antenna tuner."

#define L_HIZ_DSC \
"\nSecond order L-Network that matches a load"\
"\nresistance that's lower than the source"\
"\nresistance. Most often seen with VT circuits,"\
"\nit also works quite well in series with a PI"\
"\nnetwork where good harmonic suppression is"\
"\nrequired. Two forms presented here with different"\
"\nparallel elements."

#define L_LOZ_DSC \
"\nSecond order L-Network that matches a load"\
"\nresistance greater than the source resistance"\
"\n(a situation often found in solid state"\
"\napplications). Also sometimes encountered in"\
"\nreceiver applications. It also has two forms"\
"\nwith different parallel elements."

#define TWOCAP_L_DSC \
"\nL-Network adapted to use with BJT circuits."\
"\nthese two forms are used where R-load > Rsource"\
"\nthey have the advantages of series inductance"\
"\nto help speed up BJTs. They also allow for a"\
"\nchoice of Q-factor, unlike the simpler L-networks"\
"\nwhere circuit Q is entirely dependent on the"\
"\nimpedance transformation ratio.\n"\
"\nNote: Most frequently used with low Q-Factors for"\
"\nimpedance matching rather than harmonic suppression."

#define CAPDIV_DSC \
"\nCapacitive divider network. This network"\
"\nelectronically duplicates the action of a"\
"\ntapped coil. Useful when two-terminal"\
"\ninductors are on hand. Also useful in those"\
"\nsituations where a coil tap would be less"\
"\nthan a single turn. Also provides ease of"\
"\nadjusting the network in operational testing"\
"\nFor this project, it is assumed that the source"\
"\nimpedance will be smaller than the load resistance"\
"\nOf course, it is certainly OK to actually use the"\
"\nnetwork \"backwards\"."

#define T_NET_DSC \
"\nThis network has theadvantages of being able"\
"\nto match widely varying resistances, and with"\
"\na large range of Q Factors."\
"\nThis particular network will work regardless of"\
"\nwhether the source resistance is larger, smaller, or"\
"\nequal to the load resistance."\
"\nProvides third-order filtering for superior"\
"\nharmonic suppression. This configuration is"\
"\nreputed to be the best all-around matching"\
"\nnetwork."

#define NETENTRY_ERROR \
"Missing entry(ies) detected."\
"\nCheck your entries"

#define XCENTRY_ERR \
"The source capacitive reactance is"\
"\nrequired for this design."

#define CAPDIV_Q_ERR \
"The capacitor divider network requires"\
"\na certain minimum Q-Factor. Increase Q"\
"\b or decrease the BW."

#define LCSERIES_ERR \
"You have entered one or more values for"\
"\nthe series output C network that render"\
"\nthe design impossible. (Usually making"\
"\nRsrc greater than Rload.) you may need a"\
"\ndifferent topology."\
"\nCheck entries for errors."

#define LCSHUNT_ERR \
"You have entered one or more values for the"\
"\nparallel output C network that render the"\
"\ndesign impossible. Check entries for errors"\
"\nor select a different topology/"

#define TNET_ERR \
"You have entered one or more values that render"\
"\nthe design impossible. Either Rload is too small"\
"\n or the BW too large."

#define PINET_ERR \
"The Pi Network requires a minimum Q-Factor, *and* can"\
"\nmatch a larger impedance to a smaller one. (You can,"\
"\nhowever, use it \"backwards\" if you need to match to"\
"\na larger load impedance.)"

#define HIZ_L_ERR \
"Load resistance is too small."\
"\nConsider a Lo-Z design instead"

#define LOZ_L_ERR \
"Load resistance is too large."\
"\nConsider the Hi-Z design instead"

#define PASSIVE_BPF_ERR \
"One or more required values not entered."\
"\nCheck your entries"

#endif

//--------------------------------- textincl.h ---------------------------------
