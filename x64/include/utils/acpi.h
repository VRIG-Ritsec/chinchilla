#ifndef __ACPI_H
#define __ACPI_H

#include "utils/types.h"
#include "utils/assert.h"
#include "utils/string.h"
#include "utils/printf.h"

struct RSDP_t {
 char Signature[8];
 u8 Checksum;
 char OEMID[6];
 u8 Revision;
 u32 RsdtAddress;
} __attribute__ ((packed));

struct XSDP_t {
 char Signature[8];
 u8 Checksum;
 char OEMID[6];
 u8 Revision;
 u32 RsdtAddress;      // deprecated since version 2.0

 u32 Length;
 u64 XsdtAddress;
 u8 ExtendedChecksum;
 u8 reserved[3];
} __attribute__ ((packed));

struct ACPISDTHeader {
  char Signature[4];
  uint32_t Length;
  uint8_t Revision;
  uint8_t Checksum;
  char OEMID[6];
  char OEMTableID[8];
  uint32_t OEMRevision;
  uint32_t CreatorID;
  uint32_t CreatorRevision;
};

struct RSDT {
  struct ACPISDTHeader header;
  u32 SDT_pointers[];
};


u64 find_rsdp();
u64 find_fadt();

#endif
