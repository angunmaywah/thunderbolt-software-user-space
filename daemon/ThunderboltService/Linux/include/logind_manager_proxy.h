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

#ifndef LOGINDPROXY_H_
#define LOGINDPROXY_H_
#include <functional>
#include <dbus-c++/dbus.h>

/**
 * this is dbus proxy for logind, used to catch the reboot and the sleep events
 */
class LogindManagerProxy :
   public DBus::InterfaceProxy,
   public DBus::ObjectProxy{
public:
	LogindManagerProxy(DBus::Connection &connection,
			std::function<void()> shutdown_cb,
			std::function<void()> sleep_cb) :
      DBus::InterfaceProxy("org.freedesktop.login1.Manager"),
      DBus::ObjectProxy(connection,
    		  "/org/freedesktop/login1",
    		  "org.freedesktop.login1"),
    		  _shutdown_cb(shutdown_cb),
    		  _sleep_cb(sleep_cb){
	   connect_signal(LogindManagerProxy, PrepareForShutdown, PrepareForShutdownCb);
	   connect_signal(LogindManagerProxy, PrepareForSleep, PrepareForSleepCb);
   };
private:
  //registering shutdown callback, will be called when is system is about
  //to reboot/shutdown
  void PrepareForShutdownCb(const DBus::SignalMessage &sig)
  {
	  if(_shutdown_cb)
		  _shutdown_cb();
  }
  //registering shutdown callback, will be called when is system is about
  //to enter sleep mode
  void PrepareForSleepCb(const DBus::SignalMessage &sig)
    {
	  if(_sleep_cb)
		  _sleep_cb();
    }
private:
  //shutdown callback that will be executed when system is going down
  std::function<void()> _shutdown_cb;
  //sleep callback that will be executed when system is entering sx
  std::function<void()> _sleep_cb;
};
#endif
