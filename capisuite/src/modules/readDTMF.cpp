/*  @file readDTMF.cpp
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

#include "../backend/connection.h"
#include "readDTMF.h"

ReadDTMF::ReadDTMF(Connection *conn, int timeout, int min_digits, int max_digits)
	:CallModule(conn, timeout, false),min_digits(min_digits),max_digits(max_digits)
{
	if (conn->getState()!=Connection::UP)
		throw CapiWrongState("Disconnection occured.","ReadDTMF::ReadDTMF()");
	digit_count=conn->getDTMF().size();
}

void
ReadDTMF::mainLoop() throw (CapiWrongState)
{
	if (!max_digits || (digit_count < max_digits)) {
		do {
			finish=false;
			CallModule::mainLoop();
		} while (!abort && (digit_count<min_digits));
	}
}

void
ReadDTMF::gotDTMF()
{
	digit_count=conn->getDTMF().size();
	if (max_digits && (digit_count >= max_digits))
		finish=true;        
	else
		exit_time=getTime()+timeout;
}

/*  History

$Log: readDTMF.cpp,v $
Revision 1.1  2003/02/19 08:19:53  gernot
Initial revision

Revision 1.7  2003/01/19 16:50:27  ghillie
- removed severity in exceptions. No FATAL-automatic-exit any more.
  Removed many FATAL conditions, other ones are exiting now by themselves

Revision 1.6  2002/12/06 13:13:06  ghillie
- use Connection::getState() insted of Connection::isUp()

Revision 1.5  2002/12/05 15:56:24  ghillie
- added checks for connection state to throw exception if connection is down

Revision 1.4  2002/12/02 21:03:46  ghillie
assured that while loop is entered even if digit_count>=min_digits

Revision 1.3  2002/11/29 10:28:33  ghillie
- updated comments, use doxygen format now
- removed unnecessary attribute again

Revision 1.2  2002/11/25 21:01:55  ghillie
- simplified timeout handling (end point is changed now, no new iteration of mainLoop for every DTMF signal)

Revision 1.1  2002/11/25 11:42:07  ghillie
initial checkin

*/
