/*******************************************************************************
 *
 * Intel Thunderbolt(TM) daemon
 * Copyright(c) 2014 - 2015 Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * The full GNU General Public License is included in this distribution in
 * the file called "COPYING".
 *
 * Contact Information:
 * Intel Thunderbolt Mailing List <thunderbolt-software@lists.01.org>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 ******************************************************************************/

#pragma once

#include <future>
#include "defines.h"
#include "IControllerCommandSender.h"

/* Generic macros for dealing with netlink sockets. Might be duplicated
 * elsewhere. It is recommended that commercial grade applications use
 * libnl or libnetlink and use the interfaces provided by the library
 */
class LinuxControllerCommandSender: public IControllerCommandSender
{
public:
   LinuxControllerCommandSender();

   void GetDriverInformation(const controlleriD& Cid, std::wstring& oVersionString, std::wstring& oInstanceName, uint8_t& oDmaPort, uint32_t& nvmOffset);
   void SendTbtWmiApproveP2P(const IP2PDevice& Device) const;
   void SendDriverCommand(const controlleriD& cID, SW_TO_FW_INMAILCMD_CODE cmd) const;
   void SendTbtWmiMessageToFW(const controlleriD& Cid, uint8_t* message, size_t messageSize, PDF_VALUE pdf) const;
private:
   static void OnEvent(uint32_t controller_id,PDF_VALUE pdf,const std::vector<uint8_t>& data);
};
