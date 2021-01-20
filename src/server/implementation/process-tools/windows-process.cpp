/*
 * (C) Copyright 2020 Kurento (https://www.kurento.org/)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

// The Windows specific code was developed for MSYS2 on Windows.
// Note: MSYS2 simulates partially the proc-filesystem
//       in the shell, but it is not available when KMS
//       is being executed natively without the MSYS2 environment.
//       Hence, one cannot use the Linux implementation for
//       information retrieval.
#include "windows-process.hpp"

#include <fstream>
#include <sstream>
#include <string>

#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <iostream>
#include <thread>

// ----------------------------------------------------------------------------

unsigned long
cpuCount ()
{
  unsigned long count = std::thread::hardware_concurrency();

  if (count > 0) {
    return count;
  }

  return 1;
}

// ----------------------------------------------------------------------------

/**
 * Converts the values inside the struct to a ULARGE_INTEGER.
 *
 * @param name a struct of type \c FILETIME with time information
 * @return the time information converted to a ULARGE_INTEGER (unsigned long long)
 */
#define FILETIME_TO_ULARGE_INTEGER(name) ULARGE_INTEGER ui ## name = { 0 }; \
  (ui ## name).LowPart = (ft ## name).dwLowDateTime; \
  (ui ## name).HighPart = (ft ## name).dwHighDateTime;

/**
 * Stores system and process times in the provided parameter.
 *
 * The function calculates the system and process ticks based
 * on information retrieved from \c GetSystemTimes() and \c GetProcessTimes()
 * of the Windows API.
 *
 * @param cpustat Pointer to store the tick information. The function
 *                does nothing, if this is NULL.
 */
static void fillCpuStat (struct cpustat_t *cpustat)
{
  FILETIME ftSysIdle      = { 0 };
  FILETIME ftSysKernel    = { 0 };
  FILETIME ftSysUser      = { 0 };
  FILETIME ftProcCreation = { 0 };
  FILETIME ftProcExit     = { 0 };
  FILETIME ftProcKernel   = { 0 };
  FILETIME ftProcUser     = { 0 };

  if (cpustat &&
      GetSystemTimes (&ftSysIdle, &ftSysKernel, &ftSysUser) &&
      GetProcessTimes (GetCurrentProcess(), &ftProcCreation, &ftProcExit,
                       &ftProcKernel, &ftProcUser) ) {
    // Note: kernel time includes idle time, based on GetSystemTimes() dcoumentation
    FILETIME_TO_ULARGE_INTEGER (SysKernel)
    FILETIME_TO_ULARGE_INTEGER (SysUser)
    FILETIME_TO_ULARGE_INTEGER (ProcKernel)
    FILETIME_TO_ULARGE_INTEGER (ProcUser)

    cpustat->systemTicks  = uiSysKernel.QuadPart + uiSysUser.QuadPart;
    cpustat->processTicks = uiProcKernel.QuadPart + uiProcUser.QuadPart;
  }
}

// ----------------------------------------------------------------------------

void
cpuPercentBegin (struct cpustat_t *cpustat)
{
  fillCpuStat (cpustat);
}

// ----------------------------------------------------------------------------

float cpuPercentEnd (const struct cpustat_t *cpustat)
{
  struct cpustat_t stat2 = { 0 };
  fillCpuStat (&stat2);

  if (stat2.systemTicks > cpustat->systemTicks) {
    return 100.0f * (stat2.processTicks - cpustat->processTicks) /
           (stat2.systemTicks - cpustat->systemTicks);
  }

  return 0.0f;
}

// ----------------------------------------------------------------------------

long int memoryUse ()
{
  PROCESS_MEMORY_COUNTERS memCounter;

  if (GetProcessMemoryInfo (GetCurrentProcess(), &memCounter,
                            sizeof (memCounter) ) ) {
    return memCounter.WorkingSetSize / 1024;
  }

  return 0;
}
