/** @file readDTMF.h
    @brief Contains ReadDTMF - Call Module for waiting for DTMF signals

    @author Gernot Hillier <gernot@hillier.de>
    $Revision: 1.1 $
*/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef READDTMF_H
#define READDTMF_H

#include "callmodule.h"

class Connection;

/** @brief Call Module for waiting for DTMF signals

    This module allows the user to specify how much DTMF digits he wants to read and how long to
    wait for them. It doesn't do the actual read, just waits for the given conditions to be fulfilled.

    To use it, create an object and call mainLoop(). After mainLoop() finished, call Connection::getDTMF() to read
    the received signals.

    @author Gernot Hillier

*/
class ReadDTMF: public CallModule
{
	public:
 		/** @brief Constructor. Create Object and read the current digit count from Connection.

   		    @param conn reference to Connection object
		    @param timeout timeout in seconds after which reading is terminated (only terminates when min_digits are reached!), restarts after each digit
		    @param min_digits minimum number of digits which must be read in ANY case without respect to timout. Only set to value >0 if you're sure the user will input a digit.
		    @param max_digits maximum number of digits to read, we abort immediately if this number is reached (0=infinite, only timeout counts)
		*/
		ReadDTMF(Connection *conn, int timeout, int min_digits, int max_digits);

 		/** @brief mainLoop: Waits until the given conditions (see constructor) have been fulfilled
                                                                         
		    The module will finish if one of these conditions are true:

                    - max_digits is fulfilled
		    - timeout was reached AND min_digits is fulfilled
		    
		    @throw CapiWrongState Thrown if disconnection is recognized
  		*/
		void mainLoop() throw (CapiWrongState);

		/** @brief finish if max_digits is reached, otherwise restart timeout when DTMF signal is received
  		*/
		void gotDTMF();

	private:  
		int digit_count, ///< save the current number of digits in receive buffer
		    min_digits, ///< save min_digits parameter
		    max_digits; ///< save max_digits parameter
};

#endif

/* History

$Log: readDTMF.h,v $
Revision 1.1  2003/02/19 08:19:53  gernot
Initial revision

Revision 1.2  2002/11/29 10:28:34  ghillie
- updated comments, use doxygen format now
- removed unnecessary attribute again

Revision 1.1  2002/11/25 11:42:07  ghillie
initial checkin

*/
