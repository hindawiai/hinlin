<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित CCISS_DEFS_H
#घोषणा CCISS_DEFS_H

#समावेश <linux/types.h>

/* general boundary definitions */
#घोषणा SENSEINFOBYTES          32 /* note that this value may vary
				      between host implementations */

/* Command Status value */
#घोषणा CMD_SUCCESS             0x0000
#घोषणा CMD_TARGET_STATUS       0x0001
#घोषणा CMD_DATA_UNDERRUN       0x0002
#घोषणा CMD_DATA_OVERRUN        0x0003
#घोषणा CMD_INVALID             0x0004
#घोषणा CMD_PROTOCOL_ERR        0x0005
#घोषणा CMD_HARDWARE_ERR        0x0006
#घोषणा CMD_CONNECTION_LOST     0x0007
#घोषणा CMD_ABORTED             0x0008
#घोषणा CMD_ABORT_FAILED        0x0009
#घोषणा CMD_UNSOLICITED_ABORT   0x000A
#घोषणा CMD_TIMEOUT             0x000B
#घोषणा CMD_UNABORTABLE		0x000C

/* transfer direction */
#घोषणा XFER_NONE               0x00
#घोषणा XFER_WRITE              0x01
#घोषणा XFER_READ               0x02
#घोषणा XFER_RSVD               0x03

/* task attribute */
#घोषणा ATTR_UNTAGGED           0x00
#घोषणा ATTR_SIMPLE             0x04
#घोषणा ATTR_HEADOFQUEUE        0x05
#घोषणा ATTR_ORDERED            0x06
#घोषणा ATTR_ACA                0x07

/* cdb type */
#घोषणा TYPE_CMD				0x00
#घोषणा TYPE_MSG				0x01

/* Type defs used in the following काष्ठाs */
#घोषणा BYTE __u8
#घोषणा WORD __u16
#घोषणा HWORD __u16
#घोषणा DWORD __u32

#घोषणा CISS_MAX_LUN	1024

#घोषणा LEVEL2LUN   1 /* index पूर्णांकo Target(x) काष्ठाure, due to byte swapping */
#घोषणा LEVEL3LUN   0

#आशय pack(1)

/* Command List Structure */
प्रकार जोड़ _SCSI3Addr_काष्ठा अणु
   काष्ठा अणु
    BYTE Dev;
    BYTE Bus:6;
    BYTE Mode:2;        /* b00 */
  पूर्ण PeripDev;
   काष्ठा अणु
    BYTE DevLSB;
    BYTE DevMSB:6;
    BYTE Mode:2;        /* b01 */
  पूर्ण LogDev;
   काष्ठा अणु
    BYTE Dev:5;
    BYTE Bus:3;
    BYTE Targ:6;
    BYTE Mode:2;        /* b10 */
  पूर्ण LogUnit;
पूर्ण SCSI3Addr_काष्ठा;

प्रकार काष्ठा _PhysDevAddr_काष्ठा अणु
  DWORD             TargetId:24;
  DWORD             Bus:6;
  DWORD             Mode:2;
  SCSI3Addr_काष्ठा  Target[2]; /* 2 level target device addr */
पूर्ण PhysDevAddr_काष्ठा;

प्रकार काष्ठा _LogDevAddr_काष्ठा अणु
  DWORD            VolId:30;
  DWORD            Mode:2;
  BYTE             reserved[4];
पूर्ण LogDevAddr_काष्ठा;

प्रकार जोड़ _LUNAddr_काष्ठा अणु
  BYTE               LunAddrBytes[8];
  SCSI3Addr_काष्ठा   SCSI3Lun[4];
  PhysDevAddr_काष्ठा PhysDev;
  LogDevAddr_काष्ठा  LogDev;
पूर्ण LUNAddr_काष्ठा;

प्रकार काष्ठा _RequestBlock_काष्ठा अणु
  BYTE   CDBLen;
  काष्ठा अणु
    BYTE Type:3;
    BYTE Attribute:3;
    BYTE Direction:2;
  पूर्ण Type;
  HWORD  Timeout;
  BYTE   CDB[16];
पूर्ण RequestBlock_काष्ठा;

प्रकार जोड़ _MoreErrInfo_काष्ठाअणु
  काष्ठा अणु
    BYTE  Reserved[3];
    BYTE  Type;
    DWORD ErrorInfo;
  पूर्ण Common_Info;
  काष्ठाअणु
    BYTE  Reserved[2];
    BYTE  offense_size; /* size of offending entry */
    BYTE  offense_num;  /* byte # of offense 0-base */
    DWORD offense_value;
  पूर्ण Invalid_Cmd;
पूर्ण MoreErrInfo_काष्ठा;
प्रकार काष्ठा _ErrorInfo_काष्ठा अणु
  BYTE               ScsiStatus;
  BYTE               SenseLen;
  HWORD              CommandStatus;
  DWORD              ResidualCnt;
  MoreErrInfo_काष्ठा MoreErrInfo;
  BYTE               SenseInfo[SENSEINFOBYTES];
पूर्ण ErrorInfo_काष्ठा;

#आशय pack()

#पूर्ण_अगर /* CCISS_DEFS_H */
