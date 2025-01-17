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
  u32 Length;
  u8 Revision;
  u8 Checksum;
  char OEMID[6];
  char OEMTableID[8];
  u32 OEMRevision;
  u32 CreatorID;
  u32 CreatorRevision;
};

struct RSDT {
  struct ACPISDTHeader header;
  u32 SDT_pointers[];
};

struct lame_address_struct
{
  u8 AddressSpace;
  u8 BitWidth;
  u8 BitOffset;
  u8 AccessSize;
  u64 Address;
};

struct FADT
{
    struct   ACPISDTHeader h;
    u32 FirmwareCtrl;
    u32 Dsdt;

    // field used in ACPI 1.0; no longer in use, for compatibility only
    u8  Reserved;

    u8  PreferredPowerManagementProfile;
    u16 SCI_Interrupt;
    u32 SMI_CommandPort;
    u8  AcpiEnable;
    u8  AcpiDisable;
    u8  S4BIOS_REQ;
    u8  PSTATE_Control;
    u32 PM1aEventBlock;
    u32 PM1bEventBlock;
    u32 PM1aControlBlock;
    u32 PM1bControlBlock;
    u32 PM2ControlBlock;
    u32 PMTimerBlock;
    u32 GPE0Block;
    u32 GPE1Block;
    u8  PM1EventLength;
    u8  PM1ControlLength;
    u8  PM2ControlLength;
    u8  PMTimerLength;
    u8  GPE0Length;
    u8  GPE1Length;
    u8  GPE1Base;
    u8  CStateControl;
    u16 WorstC2Latency;
    u16 WorstC3Latency;
    u16 FlushSize;
    u16 FlushStride;
    u8  DutyOffset;
    u8  DutyWidth;
    u8  DayAlarm;
    u8  MonthAlarm;
    u8  Century;

    // reserved in ACPI 1.0; used since ACPI 2.0+
    u16 BootArchitectureFlags;

    u8  Reserved2;
    u32 Flags;

    // 12 byte structure; see below for details
    struct lame_address_struct ResetReg;

    u8  ResetValue;
    u8  Reserved3[3];
  
    // 64bit pointers - Available on ACPI 2.0+
    uint64_t                X_FirmwareControl;
    uint64_t                X_Dsdt;

    struct lame_address_struct X_PM1aEventBlock;
    struct lame_address_struct X_PM1bEventBlock;
    struct lame_address_struct X_PM1aControlBlock;
    struct lame_address_struct X_PM1bControlBlock;
    struct lame_address_struct X_PM2ControlBlock;
    struct lame_address_struct X_PMTimerBlock;
    struct lame_address_struct X_GPE0Block;
    struct lame_address_struct X_GPE1Block;
};
bool enable_acpi_mode();
extern void outb(u8, u8);
extern u8 inw(u8);
#endif
