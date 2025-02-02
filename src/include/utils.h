/*************************************************************************
 * Copyright (c) 2016-2020, NVIDIA CORPORATION. All rights reserved.
 *
 * See LICENSE.txt for license information
 ************************************************************************/

#ifndef NCCL_UTILS_H_
#define NCCL_UTILS_H_

#include "nccl.h"
#include <stdint.h>

int ncclCudaCompCap();

// PCI Bus ID <-> int64 conversion functions
ncclResult_t int64ToBusId(int64_t id, char* busId);
ncclResult_t busIdToInt64(const char* busId, int64_t* id);

ncclResult_t getBusId(int cudaDev, int64_t *busId);

ncclResult_t getHostName(char* hostname, int maxlen, const char delim);
uint64_t getHash(const char* string, int n);
uint64_t getHostHash();
uint64_t getPidHash();

struct netIf {
  char prefix[64];
  int port;
};

int parseStringList(const char* string, struct netIf* ifList, int maxList);
bool matchIfList(const char* string, int port, struct netIf* ifList, int listSize, bool matchExact);

static long log2i(long n) {
 long l = 0;
 while (n>>=1) l++;
 return l;
}

static uint32_t cal_sport(uint32_t lqpn, uint32_t rqpn) {
  lqpn ^= lqpn >> 16;
  lqpn = lqpn & 0xFFFF;
  rqpn ^= rqpn >> 16;
  rqpn = rqpn & 0xFFFF;
  return (lqpn ^ rqpn) | 0xC000;
}

#endif
