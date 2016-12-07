/********************************************************************************
 * Thunderbolt(TM) FW update library
 * This library is distributed under the following BSD-style license:
 *
 * Copyright(c) 2016 Intel Corporation.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Intel Corporation nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ********************************************************************************/

#include "log.h"
#include <stdarg.h>

namespace tbt
{

namespace log_internal
{

int g_logLevel = LOG_DEBUG;

int GetLogLevel()
{
   return g_logLevel;
}

void LogImpl(int level, const char* zFmt, ...)
{
   if (level <= GetLogLevel())
   {
      va_list ap;
      va_start(ap, zFmt);
      vsyslog(level, zFmt, ap);
      va_end(ap);
   }
}

const char* LevelToStr(int level)
{
   switch (level)
   {
   case LOG_EMERG:
      return "EMG";
   case LOG_ALERT:
      return "ALT";
   case LOG_CRIT:
      return "CRT";
   case LOG_ERR:
      return "ERR";
   case LOG_WARNING:
      return "WRN";
   case LOG_NOTICE:
      return "NTC";
   case LOG_INFO:
      return "INF";

   case LOG_DEBUG:
   default:
      return "DBG";
   }
}

} // namespace log_internal

void SetLogLevel(int level)
{
   log_internal::g_logLevel = level;
}

} // namespace tbt
