/*------------------------------------------------------------------------------

    Copyright (c) 2004 Media Development Loan Fund
 
    This file is part of the LiveSupport project.
    http://livesupport.campware.org/
    To report bugs, send an e-mail to bugs@campware.org
 
    LiveSupport is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
  
    LiveSupport is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 
    You should have received a copy of the GNU General Public License
    along with LiveSupport; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 
 
    Author   : $Author: maroy $
    Version  : $Revision: 1.2 $
    Location : $Source: /home/paul/cvs2svn-livesupport/newcvsrepo/livesupport/products/scheduler/src/UploadPlaylistMethod.h,v $

------------------------------------------------------------------------------*/
#ifndef UploadPlaylistMetohd_h
#define UploadPlaylistMethod_h

#ifndef __cplusplus
#error This is a C++ include file
#endif


/* ============================================================ include files */

#ifdef HAVE_CONFIG_H
#include "configure.h"
#endif

#include <stdexcept>
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <XmlRpcServerMethod.h>
#include <XmlRpcValue.h>

#include "LiveSupport/Core/Ptr.h"
#include "LiveSupport/Core/UniqueId.h"


namespace LiveSupport {
namespace Scheduler {

using namespace LiveSupport;
using namespace LiveSupport::Core;

/* ================================================================ constants */


/* =================================================================== macros */


/* =============================================================== data types */

/**
 *  An XML-RPC method object to accept a playlist for upload,
 *  and schedule it in the scheduler.
 *
 *  The name of the method when called through XML-RPC is "uploadPlaylist".
 *  The expected parameter is an XML-RPC structure, with the following
 *  member:
 *  <ul>
 *      <li>playlistId - int, the id of the playlist to upload</li>
 *      <li>playtime - the time when the playlist should be scheduled,
 *                     an ISO 8601 DateTime field</li>
 *  </ul>
 *
 *  @author  $Author: maroy $
 *  @version $Revision: 1.2 $
 */
class UploadPlaylistMethod : public XmlRpc::XmlRpcServerMethod
{
    private:
        /**
         *  The name of this method, as it will be registered into the
         *  XML-RPC server.
         */
        static const std::string        methodName;

        /**
         *  The name of the playlist id member in the XML-RPC parameter
         *  structure.
         */
        static const std::string        playlistIdName;

        /**
         *  The name of the playtime member in the XML-RPC parameter
         *  structure.
         */
        static const std::string        playtimeName;

        /**
         *  Extract the playlist id from the XML-RPC parameters.
         *
         *  @param xmlRpcValue the XML-RPC parameter to extract from.
         *  @return a UniqueId that was found in the XML-RPC parameter.
         *  @exception std::invalid_argument if there was no UniqueId
         *             in xmlRpcValue
         */
        Ptr<UniqueId>::Ref
        extractPlaylistId(XmlRpc::XmlRpcValue & xmlRpcValue)
                                                throw (std::invalid_argument);

        /**
         *  Extract the playtime from the XML-RPC parameters.
         *
         *  @param xmlRpcValue the XML-RPC parameter to extract from.
         *  @return the playing time, as stored in the XML-RPC parameter
         *  @exception std::invalid_argument if there was no playtime
         *             in xmlRpcValue
         */
        Ptr<boost::posix_time::ptime>::Ref
        extractPlayschedule(XmlRpc::XmlRpcValue & xmlRpcValue)
                                                throw (std::invalid_argument);


    public:
        /**
         *  A default constructor, for testing purposes.
         */
        UploadPlaylistMethod(void)                      throw ()
                            : XmlRpc::XmlRpcServerMethod(methodName)
        {
        }

        /**
         *  Constuctor that registers the method with the server right away.
         *
         *  @param xmlRpcServer the XML-RPC server to register with.
         */
        UploadPlaylistMethod(
                    Ptr<XmlRpc::XmlRpcServer>::Ref xmlRpcServer)
                                                                    throw ();

        /**
         *  Execute the upload playlist command on the Scheduler daemon.
         *
         *  @param parameters XML-RPC function call parameters
         *  @param returnValue the return value of the call (out parameter)
         */
        void
        execute( XmlRpc::XmlRpcValue  & parameters,
                 XmlRpc::XmlRpcValue  & returnValue)            throw ();
};


/* ================================================= external data structures */


/* ====================================================== function prototypes */


} // namespace Scheduler
} // namespace LiveSupport

#endif // UploadPlaylistMetohd_h

