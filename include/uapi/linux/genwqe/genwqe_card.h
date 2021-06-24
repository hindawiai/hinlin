<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __GENWQE_CARD_H__
#घोषणा __GENWQE_CARD_H__

/**
 * IBM Accelerator Family 'GenWQE'
 *
 * (C) Copyright IBM Corp. 2013
 *
 * Author: Frank Haverkamp <haver@linux.vnet.ibm.com>
 * Author: Joerg-Stephan Vogt <jsvogt@de.ibm.com>
 * Author: Michael Jung <mijung@gmx.net>
 * Author: Michael Ruettger <michael@ibmra.de>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License (version 2 only)
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License क्रम more details.
 */

/*
 * User-space API क्रम the GenWQE card. For debugging and test purposes
 * the रेजिस्टर addresses are included here too.
 */

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

/* Basename of sysfs, debugfs and /dev पूर्णांकerfaces */
#घोषणा GENWQE_DEVNAME			"genwqe"

#घोषणा GENWQE_TYPE_ALTERA_230		0x00 /* GenWQE4 Stratix-IV-230 */
#घोषणा GENWQE_TYPE_ALTERA_530		0x01 /* GenWQE4 Stratix-IV-530 */
#घोषणा GENWQE_TYPE_ALTERA_A4		0x02 /* GenWQE5 A4 Stratix-V-A4 */
#घोषणा GENWQE_TYPE_ALTERA_A7		0x03 /* GenWQE5 A7 Stratix-V-A7 */

/* MMIO Unit offsets: Each UnitID occupies a defined address range */
#घोषणा GENWQE_UID_OFFS(uid)		((uid) << 24)
#घोषणा GENWQE_SLU_OFFS			GENWQE_UID_OFFS(0)
#घोषणा GENWQE_HSU_OFFS			GENWQE_UID_OFFS(1)
#घोषणा GENWQE_APP_OFFS			GENWQE_UID_OFFS(2)
#घोषणा GENWQE_MAX_UNITS		3

/* Common offsets per UnitID */
#घोषणा IO_EXTENDED_ERROR_POINTER	0x00000048
#घोषणा IO_ERROR_INJECT_SELECTOR	0x00000060
#घोषणा IO_EXTENDED_DIAG_SELECTOR	0x00000070
#घोषणा IO_EXTENDED_DIAG_READ_MBX	0x00000078
#घोषणा IO_EXTENDED_DIAG_MAP(ring)	(0x00000500 | ((ring) << 3))

#घोषणा GENWQE_EXTENDED_DIAG_SELECTOR(ring, trace) (((ring) << 8) | (trace))

/* UnitID 0: Service Layer Unit (SLU) */

/* SLU: Unit Configuration Register */
#घोषणा IO_SLU_UNITCFG			0x00000000
#घोषणा IO_SLU_UNITCFG_TYPE_MASK	0x000000000ff00000 /* 27:20 */

/* SLU: Fault Isolation Register (FIR) (ac_slu_fir) */
#घोषणा IO_SLU_FIR			0x00000008 /* पढ़ो only, wr direct */
#घोषणा IO_SLU_FIR_CLR			0x00000010 /* पढ़ो and clear */

/* SLU: First Error Capture Register (FEC/WOF) */
#घोषणा IO_SLU_FEC			0x00000018

#घोषणा IO_SLU_ERR_ACT_MASK		0x00000020
#घोषणा IO_SLU_ERR_ATTN_MASK		0x00000028
#घोषणा IO_SLU_FIRX1_ACT_MASK		0x00000030
#घोषणा IO_SLU_FIRX0_ACT_MASK		0x00000038
#घोषणा IO_SLU_SEC_LEM_DEBUG_OVR	0x00000040
#घोषणा IO_SLU_EXTENDED_ERR_PTR		0x00000048
#घोषणा IO_SLU_COMMON_CONFIG		0x00000060

#घोषणा IO_SLU_FLASH_FIR		0x00000108
#घोषणा IO_SLU_SLC_FIR			0x00000110
#घोषणा IO_SLU_RIU_TRAP			0x00000280
#घोषणा IO_SLU_FLASH_FEC		0x00000308
#घोषणा IO_SLU_SLC_FEC			0x00000310

/*
 * The  Virtual Function's Access is from offset 0x00010000
 * The Physical Function's Access is from offset 0x00050000
 * Single Shared Registers exists only at offset 0x00060000
 *
 * SLC: Queue Virtual Winकरोw Winकरोw क्रम accessing पूर्णांकo a specअगरic VF
 * queue. When accessing the 0x10000 space using the 0x50000 address
 * segment, the value indicated here is used to specअगरy which VF
 * रेजिस्टर is decoded. This रेजिस्टर, and the 0x50000 रेजिस्टर space
 * can only be accessed by the PF. Example, अगर this रेजिस्टर is set to
 * 0x2, then a पढ़ो from 0x50000 is the same as a पढ़ो from 0x10000
 * from VF=2.
 */

/* SLC: Queue Segment */
#घोषणा IO_SLC_QUEUE_SEGMENT		0x00010000
#घोषणा IO_SLC_VF_QUEUE_SEGMENT		0x00050000

/* SLC: Queue Offset */
#घोषणा IO_SLC_QUEUE_OFFSET		0x00010008
#घोषणा IO_SLC_VF_QUEUE_OFFSET		0x00050008

/* SLC: Queue Configuration */
#घोषणा IO_SLC_QUEUE_CONFIG		0x00010010
#घोषणा IO_SLC_VF_QUEUE_CONFIG		0x00050010

/* SLC: Job Timout/Only accessible क्रम the PF */
#घोषणा IO_SLC_APPJOB_TIMEOUT		0x00010018
#घोषणा IO_SLC_VF_APPJOB_TIMEOUT	0x00050018
#घोषणा TIMEOUT_250MS			0x0000000f
#घोषणा HEARTBEAT_DISABLE		0x0000ff00

/* SLC: Queue InitSequence Register */
#घोषणा	IO_SLC_QUEUE_INITSQN		0x00010020
#घोषणा	IO_SLC_VF_QUEUE_INITSQN		0x00050020

/* SLC: Queue Wrap */
#घोषणा IO_SLC_QUEUE_WRAP		0x00010028
#घोषणा IO_SLC_VF_QUEUE_WRAP		0x00050028

/* SLC: Queue Status */
#घोषणा IO_SLC_QUEUE_STATUS		0x00010100
#घोषणा IO_SLC_VF_QUEUE_STATUS		0x00050100

/* SLC: Queue Working Time */
#घोषणा IO_SLC_QUEUE_WTIME		0x00010030
#घोषणा IO_SLC_VF_QUEUE_WTIME		0x00050030

/* SLC: Queue Error Counts */
#घोषणा IO_SLC_QUEUE_ERRCNTS		0x00010038
#घोषणा IO_SLC_VF_QUEUE_ERRCNTS		0x00050038

/* SLC: Queue Loast Response Word */
#घोषणा IO_SLC_QUEUE_LRW		0x00010040
#घोषणा IO_SLC_VF_QUEUE_LRW		0x00050040

/* SLC: Freerunning Timer */
#घोषणा IO_SLC_FREE_RUNNING_TIMER	0x00010108
#घोषणा IO_SLC_VF_FREE_RUNNING_TIMER	0x00050108

/* SLC: Queue Virtual Access Region */
#घोषणा IO_PF_SLC_VIRTUAL_REGION	0x00050000

/* SLC: Queue Virtual Winकरोw */
#घोषणा IO_PF_SLC_VIRTUAL_WINDOW	0x00060000

/* SLC: DDCB Application Job Pending [n] (n=0:63) */
#घोषणा IO_PF_SLC_JOBPEND(n)		(0x00061000 + 8*(n))
#घोषणा IO_SLC_JOBPEND(n)		IO_PF_SLC_JOBPEND(n)

/* SLC: Parser Trap RAM [n] (n=0:31) */
#घोषणा IO_SLU_SLC_PARSE_TRAP(n)	(0x00011000 + 8*(n))

/* SLC: Dispatcher Trap RAM [n] (n=0:31) */
#घोषणा IO_SLU_SLC_DISP_TRAP(n)	(0x00011200 + 8*(n))

/* Global Fault Isolation Register (GFIR) */
#घोषणा IO_SLC_CFGREG_GFIR		0x00020000
#घोषणा GFIR_ERR_TRIGGER		0x0000ffff

/* SLU: Soft Reset Register */
#घोषणा IO_SLC_CFGREG_SOFTRESET		0x00020018

/* SLU: Misc Debug Register */
#घोषणा IO_SLC_MISC_DEBUG		0x00020060
#घोषणा IO_SLC_MISC_DEBUG_CLR		0x00020068
#घोषणा IO_SLC_MISC_DEBUG_SET		0x00020070

/* Temperature Sensor Reading */
#घोषणा IO_SLU_TEMPERATURE_SENSOR	0x00030000
#घोषणा IO_SLU_TEMPERATURE_CONFIG	0x00030008

/* Voltage Margining Control */
#घोषणा IO_SLU_VOLTAGE_CONTROL		0x00030080
#घोषणा IO_SLU_VOLTAGE_NOMINAL		0x00000000
#घोषणा IO_SLU_VOLTAGE_DOWN5		0x00000006
#घोषणा IO_SLU_VOLTAGE_UP5		0x00000007

/* Direct LED Control Register */
#घोषणा IO_SLU_LEDCONTROL		0x00030100

/* SLU: Flashbus Direct Access -A5 */
#घोषणा IO_SLU_FLASH_सूचीECTACCESS	0x00040010

/* SLU: Flashbus Direct Access2 -A5 */
#घोषणा IO_SLU_FLASH_सूचीECTACCESS2	0x00040020

/* SLU: Flashbus Command Interface -A5 */
#घोषणा IO_SLU_FLASH_CMDINTF		0x00040030

/* SLU: BitStream Loaded */
#घोषणा IO_SLU_BITSTREAM		0x00040040

/* This Register has a चयन which will change the CAs to UR */
#घोषणा IO_HSU_ERR_BEHAVIOR		0x01001010

#घोषणा IO_SLC2_SQB_TRAP		0x00062000
#घोषणा IO_SLC2_QUEUE_MANAGER_TRAP	0x00062008
#घोषणा IO_SLC2_FLS_MASTER_TRAP		0x00062010

/* UnitID 1: HSU Registers */
#घोषणा IO_HSU_UNITCFG			0x01000000
#घोषणा IO_HSU_FIR			0x01000008
#घोषणा IO_HSU_FIR_CLR			0x01000010
#घोषणा IO_HSU_FEC			0x01000018
#घोषणा IO_HSU_ERR_ACT_MASK		0x01000020
#घोषणा IO_HSU_ERR_ATTN_MASK		0x01000028
#घोषणा IO_HSU_FIRX1_ACT_MASK		0x01000030
#घोषणा IO_HSU_FIRX0_ACT_MASK		0x01000038
#घोषणा IO_HSU_SEC_LEM_DEBUG_OVR	0x01000040
#घोषणा IO_HSU_EXTENDED_ERR_PTR		0x01000048
#घोषणा IO_HSU_COMMON_CONFIG		0x01000060

/* UnitID 2: Application Unit (APP) */
#घोषणा IO_APP_UNITCFG			0x02000000
#घोषणा IO_APP_FIR			0x02000008
#घोषणा IO_APP_FIR_CLR			0x02000010
#घोषणा IO_APP_FEC			0x02000018
#घोषणा IO_APP_ERR_ACT_MASK		0x02000020
#घोषणा IO_APP_ERR_ATTN_MASK		0x02000028
#घोषणा IO_APP_FIRX1_ACT_MASK		0x02000030
#घोषणा IO_APP_FIRX0_ACT_MASK		0x02000038
#घोषणा IO_APP_SEC_LEM_DEBUG_OVR	0x02000040
#घोषणा IO_APP_EXTENDED_ERR_PTR		0x02000048
#घोषणा IO_APP_COMMON_CONFIG		0x02000060

#घोषणा IO_APP_DEBUG_REG_01		0x02010000
#घोषणा IO_APP_DEBUG_REG_02		0x02010008
#घोषणा IO_APP_DEBUG_REG_03		0x02010010
#घोषणा IO_APP_DEBUG_REG_04		0x02010018
#घोषणा IO_APP_DEBUG_REG_05		0x02010020
#घोषणा IO_APP_DEBUG_REG_06		0x02010028
#घोषणा IO_APP_DEBUG_REG_07		0x02010030
#घोषणा IO_APP_DEBUG_REG_08		0x02010038
#घोषणा IO_APP_DEBUG_REG_09		0x02010040
#घोषणा IO_APP_DEBUG_REG_10		0x02010048
#घोषणा IO_APP_DEBUG_REG_11		0x02010050
#घोषणा IO_APP_DEBUG_REG_12		0x02010058
#घोषणा IO_APP_DEBUG_REG_13		0x02010060
#घोषणा IO_APP_DEBUG_REG_14		0x02010068
#घोषणा IO_APP_DEBUG_REG_15		0x02010070
#घोषणा IO_APP_DEBUG_REG_16		0x02010078
#घोषणा IO_APP_DEBUG_REG_17		0x02010080
#घोषणा IO_APP_DEBUG_REG_18		0x02010088

/* Read/ग_लिखो from/to रेजिस्टरs */
काष्ठा genwqe_reg_io अणु
	__u64 num;		/* रेजिस्टर offset/address */
	__u64 val64;
पूर्ण;

/*
 * All रेजिस्टरs of our card will वापस values not equal this values.
 * If we see IO_ILLEGAL_VALUE on any of our MMIO रेजिस्टर पढ़ोs, the
 * card can be considered as unusable. It will need recovery.
 */
#घोषणा IO_ILLEGAL_VALUE		0xffffffffffffffffull

/*
 * Generic DDCB execution पूर्णांकerface.
 *
 * This पूर्णांकerface is a first prototype resulting from discussions we
 * had with other teams which wanted to use the Genwqe card. It allows
 * to issue a DDCB request in a generic way. The request will block
 * until it finishes or समय out with error.
 *
 * Some DDCBs require DMA addresses to be specअगरied in the ASIV
 * block. The पूर्णांकerface provies the capability to let the kernel
 * driver know where those addresses are by specअगरying the ATS field,
 * such that it can replace the user-space addresses with appropriate
 * DMA addresses or DMA addresses of a scatter gather list which is
 * dynamically created.
 *
 * Our hardware will refuse DDCB execution अगर the ATS field is not as
 * expected. That means the DDCB execution engine in the chip knows
 * where it expects DMA addresses within the ASIV part of the DDCB and
 * will check that against the ATS field definition. Any invalid or
 * unknown ATS content will lead to DDCB refusal.
 */

/* Genwqe chip Units */
#घोषणा DDCB_ACFUNC_SLU			0x00  /* chip service layer unit */
#घोषणा DDCB_ACFUNC_APP			0x01  /* chip application */

/* DDCB वापस codes (RETC) */
#घोषणा DDCB_RETC_IDLE			0x0000 /* Unexecuted/DDCB created */
#घोषणा DDCB_RETC_PENDING		0x0101 /* Pending Execution */
#घोषणा DDCB_RETC_COMPLETE		0x0102 /* Cmd complete. No error */
#घोषणा DDCB_RETC_FAULT			0x0104 /* App Err, recoverable */
#घोषणा DDCB_RETC_ERROR			0x0108 /* App Err, non-recoverable */
#घोषणा DDCB_RETC_FORCED_ERROR		0x01ff /* overwritten by driver  */

#घोषणा DDCB_RETC_UNEXEC		0x0110 /* Unexe/Removed from queue */
#घोषणा DDCB_RETC_TERM			0x0120 /* Terminated */
#घोषणा DDCB_RETC_RES0			0x0140 /* Reserved */
#घोषणा DDCB_RETC_RES1			0x0180 /* Reserved */

/* DDCB Command Options (CMDOPT) */
#घोषणा DDCB_OPT_ECHO_FORCE_NO		0x0000 /* ECHO DDCB */
#घोषणा DDCB_OPT_ECHO_FORCE_102		0x0001 /* क्रमce वापस code */
#घोषणा DDCB_OPT_ECHO_FORCE_104		0x0002
#घोषणा DDCB_OPT_ECHO_FORCE_108		0x0003

#घोषणा DDCB_OPT_ECHO_FORCE_110		0x0004 /* only on PF ! */
#घोषणा DDCB_OPT_ECHO_FORCE_120		0x0005
#घोषणा DDCB_OPT_ECHO_FORCE_140		0x0006
#घोषणा DDCB_OPT_ECHO_FORCE_180		0x0007

#घोषणा DDCB_OPT_ECHO_COPY_NONE		(0 << 5)
#घोषणा DDCB_OPT_ECHO_COPY_ALL		(1 << 5)

/* Definitions of Service Layer Commands */
#घोषणा SLCMD_ECHO_SYNC			0x00 /* PF/VF */
#घोषणा SLCMD_MOVE_FLASH		0x06 /* PF only */
#घोषणा SLCMD_MOVE_FLASH_FLAGS_MODE	0x03 /* bit 0 and 1 used क्रम mode */
#घोषणा SLCMD_MOVE_FLASH_FLAGS_DLOAD	0	/* mode: करोwnload  */
#घोषणा SLCMD_MOVE_FLASH_FLAGS_EMUL	1	/* mode: emulation */
#घोषणा SLCMD_MOVE_FLASH_FLAGS_UPLOAD	2	/* mode: upload	   */
#घोषणा SLCMD_MOVE_FLASH_FLAGS_VERIFY	3	/* mode: verअगरy	   */
#घोषणा SLCMD_MOVE_FLASH_FLAG_NOTAP	(1 << 2)/* just dump DDCB and निकास */
#घोषणा SLCMD_MOVE_FLASH_FLAG_POLL	(1 << 3)/* रुको क्रम RETC >= 0102   */
#घोषणा SLCMD_MOVE_FLASH_FLAG_PARTITION	(1 << 4)
#घोषणा SLCMD_MOVE_FLASH_FLAG_ERASE	(1 << 5)

क्रमागत genwqe_card_state अणु
	GENWQE_CARD_UNUSED = 0,
	GENWQE_CARD_USED = 1,
	GENWQE_CARD_FATAL_ERROR = 2,
	GENWQE_CARD_RELOAD_BITSTREAM = 3,
	GENWQE_CARD_STATE_MAX,
पूर्ण;

/* common काष्ठा क्रम chip image exchange */
काष्ठा genwqe_bitstream अणु
	__u64 data_addr;		/* poपूर्णांकer to image data */
	__u32 size;			/* size of image file */
	__u32 crc;			/* crc of this image */
	__u64 target_addr;		/* starting address in Flash */
	__u32 partition;		/* '0', '1', or 'v' */
	__u32 uid;			/* 1=host/x=dram */

	__u64 slu_id;			/* inक्रमmational/sim: SluID */
	__u64 app_id;			/* inक्रमmational/sim: AppID */

	__u16 retc;			/* वापसed from processing */
	__u16 attn;			/* attention code from processing */
	__u32 progress;			/* progress code from processing */
पूर्ण;

/* Issuing a specअगरic DDCB command */
#घोषणा DDCB_LENGTH			256 /* क्रम debug data */
#घोषणा DDCB_ASIV_LENGTH		104 /* len of the DDCB ASIV array */
#घोषणा DDCB_ASIV_LENGTH_ATS		96  /* ASIV in ATS architecture */
#घोषणा DDCB_ASV_LENGTH			64  /* len of the DDCB ASV array  */
#घोषणा DDCB_FIXUPS			12  /* maximum number of fixups */

काष्ठा genwqe_debug_data अणु
	अक्षर driver_version[64];
	__u64 slu_unitcfg;
	__u64 app_unitcfg;

	__u8  ddcb_beक्रमe[DDCB_LENGTH];
	__u8  ddcb_prev[DDCB_LENGTH];
	__u8  ddcb_finished[DDCB_LENGTH];
पूर्ण;

/*
 * Address Translation Specअगरication (ATS) definitions
 *
 * Each 4 bit within the ATS 64-bit word specअगरy the required address
 * translation at the defined offset.
 *
 * 63 LSB
 *         6666.5555.5555.5544.4444.4443.3333.3333 ... 11
 *         3210.9876.5432.1098.7654.3210.9876.5432 ... 1098.7654.3210
 *
 * offset: 0x00 0x08 0x10 0x18 0x20 0x28 0x30 0x38 ... 0x68 0x70 0x78
 *         res  res  res  res  ASIV ...
 * The first 4 entries in the ATS word are reserved. The following nibbles
 * each describe at an 8 byte offset the क्रमmat of the required data.
 */
#घोषणा ATS_TYPE_DATA			0x0ull /* data  */
#घोषणा ATS_TYPE_FLAT_RD		0x4ull /* flat buffer पढ़ो only */
#घोषणा ATS_TYPE_FLAT_RDWR		0x5ull /* flat buffer पढ़ो/ग_लिखो */
#घोषणा ATS_TYPE_SGL_RD			0x6ull /* sgl पढ़ो only */
#घोषणा ATS_TYPE_SGL_RDWR		0x7ull /* sgl पढ़ो/ग_लिखो */

#घोषणा ATS_SET_FLAGS(_काष्ठा, _field, _flags)				\
	(((_flags) & 0xf) << (44 - (4 * (दुरत्व(_काष्ठा, _field) / 8))))

#घोषणा ATS_GET_FLAGS(_ats, _byte_offs)					\
	(((_ats)	  >> (44 - (4 * ((_byte_offs) / 8)))) & 0xf)

/**
 * काष्ठा genwqe_ddcb_cmd - User parameter क्रम generic DDCB commands
 *
 * On the way पूर्णांकo the kernel the driver will पढ़ो the whole data
 * काष्ठाure. On the way out the driver will not copy the ASIV data
 * back to user-space.
 */
काष्ठा genwqe_ddcb_cmd अणु
	/* START of data copied to/from driver */
	__u64 next_addr;		/* chaining genwqe_ddcb_cmd */
	__u64 flags;			/* reserved */

	__u8  acfunc;			/* accelerators functional unit */
	__u8  cmd;			/* command to execute */
	__u8  asiv_length;		/* used parameter length */
	__u8  asv_length;		/* length of valid वापस values  */
	__u16 cmकरोpts;			/* command options */
	__u16 retc;			/* वापस code from processing    */

	__u16 attn;			/* attention code from processing */
	__u16 vcrc;			/* variant crc16 */
	__u32 progress;			/* progress code from processing  */

	__u64 deque_ts;			/* dequeue समय stamp */
	__u64 cmplt_ts;			/* completion समय stamp */
	__u64 disp_ts;			/* SW processing start */

	/* move to end and aव्योम copy-back */
	__u64 ddata_addr;		/* collect debug data */

	/* command specअगरic values */
	__u8  asv[DDCB_ASV_LENGTH];

	/* END of data copied from driver */
	जोड़ अणु
		काष्ठा अणु
			__u64 ats;
			__u8  asiv[DDCB_ASIV_LENGTH_ATS];
		पूर्ण;
		/* used क्रम flash update to keep it backward compatible */
		__u8 __asiv[DDCB_ASIV_LENGTH];
	पूर्ण;
	/* END of data copied to driver */
पूर्ण;

#घोषणा GENWQE_IOC_CODE	    0xa5

/* Access functions */
#घोषणा GENWQE_READ_REG64   _IOR(GENWQE_IOC_CODE, 30, काष्ठा genwqe_reg_io)
#घोषणा GENWQE_WRITE_REG64  _IOW(GENWQE_IOC_CODE, 31, काष्ठा genwqe_reg_io)
#घोषणा GENWQE_READ_REG32   _IOR(GENWQE_IOC_CODE, 32, काष्ठा genwqe_reg_io)
#घोषणा GENWQE_WRITE_REG32  _IOW(GENWQE_IOC_CODE, 33, काष्ठा genwqe_reg_io)
#घोषणा GENWQE_READ_REG16   _IOR(GENWQE_IOC_CODE, 34, काष्ठा genwqe_reg_io)
#घोषणा GENWQE_WRITE_REG16  _IOW(GENWQE_IOC_CODE, 35, काष्ठा genwqe_reg_io)

#घोषणा GENWQE_GET_CARD_STATE _IOR(GENWQE_IOC_CODE, 36,	क्रमागत genwqe_card_state)

/**
 * काष्ठा genwqe_mem - Memory pinning/unpinning inक्रमmation
 * @addr:          भव user space address
 * @size:          size of the area pin/dma-map/unmap
 * direction:      0: पढ़ो/1: पढ़ो and ग_लिखो
 *
 * Aव्योम pinning and unpinning of memory pages dynamically. Instead
 * the idea is to pin the whole buffer space required क्रम DDCB
 * opertionas in advance. The driver will reuse this pinning and the
 * memory associated with it to setup the sglists क्रम the DDCB
 * requests without the need to allocate and मुक्त memory or map and
 * unmap to get the DMA addresses.
 *
 * The inverse operation needs to be called after the pinning is not
 * needed anymore. The pinnings अन्यथा the pinnings will get हटाओd
 * after the device is बंदd. Note that pinnings will required
 * memory.
 */
काष्ठा genwqe_mem अणु
	__u64 addr;
	__u64 size;
	__u64 direction;
	__u64 flags;
पूर्ण;

#घोषणा GENWQE_PIN_MEM	      _IOWR(GENWQE_IOC_CODE, 40, काष्ठा genwqe_mem)
#घोषणा GENWQE_UNPIN_MEM      _IOWR(GENWQE_IOC_CODE, 41, काष्ठा genwqe_mem)

/*
 * Generic synchronous DDCB execution पूर्णांकerface.
 * Synchronously execute a DDCB.
 *
 * Return: 0 on success or negative error code.
 *         -EINVAL: Invalid parameters (ASIV_LEN, ASV_LEN, illegal fixups
 *                  no mappings found/could not create mappings
 *         -EFAULT: illegal addresses in fixups, purging failed
 *         -EBADMSG: enqueing failed, retc != DDCB_RETC_COMPLETE
 */
#घोषणा GENWQE_EXECUTE_DDCB					\
	_IOWR(GENWQE_IOC_CODE, 50, काष्ठा genwqe_ddcb_cmd)

#घोषणा GENWQE_EXECUTE_RAW_DDCB					\
	_IOWR(GENWQE_IOC_CODE, 51, काष्ठा genwqe_ddcb_cmd)

/* Service Layer functions (PF only) */
#घोषणा GENWQE_SLU_UPDATE  _IOWR(GENWQE_IOC_CODE, 80, काष्ठा genwqe_bitstream)
#घोषणा GENWQE_SLU_READ	   _IOWR(GENWQE_IOC_CODE, 81, काष्ठा genwqe_bitstream)

#पूर्ण_अगर	/* __GENWQE_CARD_H__ */
