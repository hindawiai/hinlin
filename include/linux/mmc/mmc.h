<शैली गुरु>
/*
 * Header क्रम MultiMediaCard (MMC)
 *
 * Copyright 2002 Hewlett-Packard Company
 *
 * Use consistent with the GNU GPL is permitted,
 * provided that this copyright notice is
 * preserved in its entirety in all copies and derived works.
 *
 * HEWLETT-PACKARD COMPANY MAKES NO WARRANTIES, EXPRESSED OR IMPLIED,
 * AS TO THE USEFULNESS OR CORRECTNESS OF THIS CODE OR ITS
 * FITNESS FOR ANY PARTICULAR PURPOSE.
 *
 * Many thanks to Alessandro Rubini and Jonathan Corbet!
 *
 * Based strongly on code by:
 *
 * Author: Yong-iL Joh <tolkien@mizi.com>
 *
 * Author:  Andrew Christian
 *          15 May 2002
 */

#अगर_अघोषित LINUX_MMC_MMC_H
#घोषणा LINUX_MMC_MMC_H

#समावेश <linux/types.h>

/* Standard MMC commands (4.1)           type  argument     response */
   /* class 1 */
#घोषणा MMC_GO_IDLE_STATE         0   /* bc                          */
#घोषणा MMC_SEND_OP_COND          1   /* bcr  [31:0] OCR         R3  */
#घोषणा MMC_ALL_SEND_CID          2   /* bcr                     R2  */
#घोषणा MMC_SET_RELATIVE_ADDR     3   /* ac   [31:16] RCA        R1  */
#घोषणा MMC_SET_DSR               4   /* bc   [31:16] RCA            */
#घोषणा MMC_SLEEP_AWAKE		  5   /* ac   [31:16] RCA 15:flg R1b */
#घोषणा MMC_SWITCH                6   /* ac   [31:0] See below   R1b */
#घोषणा MMC_SELECT_CARD           7   /* ac   [31:16] RCA        R1  */
#घोषणा MMC_SEND_EXT_CSD          8   /* adtc                    R1  */
#घोषणा MMC_SEND_CSD              9   /* ac   [31:16] RCA        R2  */
#घोषणा MMC_SEND_CID             10   /* ac   [31:16] RCA        R2  */
#घोषणा MMC_READ_DAT_UNTIL_STOP  11   /* adtc [31:0] dadr        R1  */
#घोषणा MMC_STOP_TRANSMISSION    12   /* ac                      R1b */
#घोषणा MMC_SEND_STATUS          13   /* ac   [31:16] RCA        R1  */
#घोषणा MMC_BUS_TEST_R           14   /* adtc                    R1  */
#घोषणा MMC_GO_INACTIVE_STATE    15   /* ac   [31:16] RCA            */
#घोषणा MMC_BUS_TEST_W           19   /* adtc                    R1  */
#घोषणा MMC_SPI_READ_OCR         58   /* spi                  spi_R3 */
#घोषणा MMC_SPI_CRC_ON_OFF       59   /* spi  [0:0] flag      spi_R1 */

  /* class 2 */
#घोषणा MMC_SET_BLOCKLEN         16   /* ac   [31:0] block len   R1  */
#घोषणा MMC_READ_SINGLE_BLOCK    17   /* adtc [31:0] data addr   R1  */
#घोषणा MMC_READ_MULTIPLE_BLOCK  18   /* adtc [31:0] data addr   R1  */
#घोषणा MMC_SEND_TUNING_BLOCK    19   /* adtc                    R1  */
#घोषणा MMC_SEND_TUNING_BLOCK_HS200	21	/* adtc R1  */

  /* class 3 */
#घोषणा MMC_WRITE_DAT_UNTIL_STOP 20   /* adtc [31:0] data addr   R1  */

  /* class 4 */
#घोषणा MMC_SET_BLOCK_COUNT      23   /* adtc [31:0] data addr   R1  */
#घोषणा MMC_WRITE_BLOCK          24   /* adtc [31:0] data addr   R1  */
#घोषणा MMC_WRITE_MULTIPLE_BLOCK 25   /* adtc                    R1  */
#घोषणा MMC_PROGRAM_CID          26   /* adtc                    R1  */
#घोषणा MMC_PROGRAM_CSD          27   /* adtc                    R1  */

  /* class 6 */
#घोषणा MMC_SET_WRITE_PROT       28   /* ac   [31:0] data addr   R1b */
#घोषणा MMC_CLR_WRITE_PROT       29   /* ac   [31:0] data addr   R1b */
#घोषणा MMC_SEND_WRITE_PROT      30   /* adtc [31:0] wpdata addr R1  */

  /* class 5 */
#घोषणा MMC_ERASE_GROUP_START    35   /* ac   [31:0] data addr   R1  */
#घोषणा MMC_ERASE_GROUP_END      36   /* ac   [31:0] data addr   R1  */
#घोषणा MMC_ERASE                38   /* ac                      R1b */

  /* class 9 */
#घोषणा MMC_FAST_IO              39   /* ac   <Complex>          R4  */
#घोषणा MMC_GO_IRQ_STATE         40   /* bcr                     R5  */

  /* class 7 */
#घोषणा MMC_LOCK_UNLOCK          42   /* adtc                    R1b */

  /* class 8 */
#घोषणा MMC_APP_CMD              55   /* ac   [31:16] RCA        R1  */
#घोषणा MMC_GEN_CMD              56   /* adtc [0] RD/WR          R1  */

  /* class 11 */
#घोषणा MMC_QUE_TASK_PARAMS      44   /* ac   [20:16] task id    R1  */
#घोषणा MMC_QUE_TASK_ADDR        45   /* ac   [31:0] data addr   R1  */
#घोषणा MMC_EXECUTE_READ_TASK    46   /* adtc [20:16] task id    R1  */
#घोषणा MMC_EXECUTE_WRITE_TASK   47   /* adtc [20:16] task id    R1  */
#घोषणा MMC_CMDQ_TASK_MGMT       48   /* ac   [20:16] task id    R1b */

अटल अंतरभूत bool mmc_op_multi(u32 opcode)
अणु
	वापस opcode == MMC_WRITE_MULTIPLE_BLOCK ||
	       opcode == MMC_READ_MULTIPLE_BLOCK;
पूर्ण

/*
 * MMC_SWITCH argument क्रमmat:
 *
 *	[31:26] Always 0
 *	[25:24] Access Mode
 *	[23:16] Location of target Byte in EXT_CSD
 *	[15:08] Value Byte
 *	[07:03] Always 0
 *	[02:00] Command Set
 */

/*
  MMC status in R1, क्रम native mode (SPI bits are dअगरferent)
  Type
	e : error bit
	s : status bit
	r : detected and set क्रम the actual command response
	x : detected and set during command execution. the host must poll
            the card by sending status command in order to पढ़ो these bits.
  Clear condition
	a : according to the card state
	b : always related to the previous command. Reception of
            a valid command will clear it (with a delay of one command)
	c : clear by पढ़ो
 */

#घोषणा R1_OUT_OF_RANGE		(1 << 31)	/* er, c */
#घोषणा R1_ADDRESS_ERROR	(1 << 30)	/* erx, c */
#घोषणा R1_BLOCK_LEN_ERROR	(1 << 29)	/* er, c */
#घोषणा R1_ERASE_SEQ_ERROR      (1 << 28)	/* er, c */
#घोषणा R1_ERASE_PARAM		(1 << 27)	/* ex, c */
#घोषणा R1_WP_VIOLATION		(1 << 26)	/* erx, c */
#घोषणा R1_CARD_IS_LOCKED	(1 << 25)	/* sx, a */
#घोषणा R1_LOCK_UNLOCK_FAILED	(1 << 24)	/* erx, c */
#घोषणा R1_COM_CRC_ERROR	(1 << 23)	/* er, b */
#घोषणा R1_ILLEGAL_COMMAND	(1 << 22)	/* er, b */
#घोषणा R1_CARD_ECC_FAILED	(1 << 21)	/* ex, c */
#घोषणा R1_CC_ERROR		(1 << 20)	/* erx, c */
#घोषणा R1_ERROR		(1 << 19)	/* erx, c */
#घोषणा R1_UNDERRUN		(1 << 18)	/* ex, c */
#घोषणा R1_OVERRUN		(1 << 17)	/* ex, c */
#घोषणा R1_CID_CSD_OVERWRITE	(1 << 16)	/* erx, c, CID/CSD overग_लिखो */
#घोषणा R1_WP_ERASE_SKIP	(1 << 15)	/* sx, c */
#घोषणा R1_CARD_ECC_DISABLED	(1 << 14)	/* sx, a */
#घोषणा R1_ERASE_RESET		(1 << 13)	/* sr, c */
#घोषणा R1_STATUS(x)            (x & 0xFFF9A000)
#घोषणा R1_CURRENT_STATE(x)	((x & 0x00001E00) >> 9)	/* sx, b (4 bits) */
#घोषणा R1_READY_FOR_DATA	(1 << 8)	/* sx, a */
#घोषणा R1_SWITCH_ERROR		(1 << 7)	/* sx, c */
#घोषणा R1_EXCEPTION_EVENT	(1 << 6)	/* sr, a */
#घोषणा R1_APP_CMD		(1 << 5)	/* sr, c */

#घोषणा R1_STATE_IDLE	0
#घोषणा R1_STATE_READY	1
#घोषणा R1_STATE_IDENT	2
#घोषणा R1_STATE_STBY	3
#घोषणा R1_STATE_TRAN	4
#घोषणा R1_STATE_DATA	5
#घोषणा R1_STATE_RCV	6
#घोषणा R1_STATE_PRG	7
#घोषणा R1_STATE_DIS	8

अटल अंतरभूत bool mmc_पढ़ोy_क्रम_data(u32 status)
अणु
	/*
	 * Some cards mishandle the status bits, so make sure to check both the
	 * busy indication and the card state.
	 */
	वापस status & R1_READY_FOR_DATA &&
	       R1_CURRENT_STATE(status) == R1_STATE_TRAN;
पूर्ण

/*
 * MMC/SD in SPI mode reports R1 status always, and R2 क्रम SEND_STATUS
 * R1 is the low order byte; R2 is the next highest byte, when present.
 */
#घोषणा R1_SPI_IDLE		(1 << 0)
#घोषणा R1_SPI_ERASE_RESET	(1 << 1)
#घोषणा R1_SPI_ILLEGAL_COMMAND	(1 << 2)
#घोषणा R1_SPI_COM_CRC		(1 << 3)
#घोषणा R1_SPI_ERASE_SEQ	(1 << 4)
#घोषणा R1_SPI_ADDRESS		(1 << 5)
#घोषणा R1_SPI_PARAMETER	(1 << 6)
/* R1 bit 7 is always zero */
#घोषणा R2_SPI_CARD_LOCKED	(1 << 8)
#घोषणा R2_SPI_WP_ERASE_SKIP	(1 << 9)	/* or lock/unlock fail */
#घोषणा R2_SPI_LOCK_UNLOCK_FAIL	R2_SPI_WP_ERASE_SKIP
#घोषणा R2_SPI_ERROR		(1 << 10)
#घोषणा R2_SPI_CC_ERROR		(1 << 11)
#घोषणा R2_SPI_CARD_ECC_ERROR	(1 << 12)
#घोषणा R2_SPI_WP_VIOLATION	(1 << 13)
#घोषणा R2_SPI_ERASE_PARAM	(1 << 14)
#घोषणा R2_SPI_OUT_OF_RANGE	(1 << 15)	/* or CSD overग_लिखो */
#घोषणा R2_SPI_CSD_OVERWRITE	R2_SPI_OUT_OF_RANGE

/*
 * OCR bits are mostly in host.h
 */
#घोषणा MMC_CARD_BUSY	0x80000000	/* Card Power up status bit */

/*
 * Card Command Classes (CCC)
 */
#घोषणा CCC_BASIC		(1<<0)	/* (0) Basic protocol functions */
					/* (CMD0,1,2,3,4,7,9,10,12,13,15) */
					/* (and क्रम SPI, CMD58,59) */
#घोषणा CCC_STREAM_READ		(1<<1)	/* (1) Stream पढ़ो commands */
					/* (CMD11) */
#घोषणा CCC_BLOCK_READ		(1<<2)	/* (2) Block पढ़ो commands */
					/* (CMD16,17,18) */
#घोषणा CCC_STREAM_WRITE	(1<<3)	/* (3) Stream ग_लिखो commands */
					/* (CMD20) */
#घोषणा CCC_BLOCK_WRITE		(1<<4)	/* (4) Block ग_लिखो commands */
					/* (CMD16,24,25,26,27) */
#घोषणा CCC_ERASE		(1<<5)	/* (5) Ability to erase blocks */
					/* (CMD32,33,34,35,36,37,38,39) */
#घोषणा CCC_WRITE_PROT		(1<<6)	/* (6) Able to ग_लिखो protect blocks */
					/* (CMD28,29,30) */
#घोषणा CCC_LOCK_CARD		(1<<7)	/* (7) Able to lock करोwn card */
					/* (CMD16,CMD42) */
#घोषणा CCC_APP_SPEC		(1<<8)	/* (8) Application specअगरic */
					/* (CMD55,56,57,ACMD*) */
#घोषणा CCC_IO_MODE		(1<<9)	/* (9) I/O mode */
					/* (CMD5,39,40,52,53) */
#घोषणा CCC_SWITCH		(1<<10)	/* (10) High speed चयन */
					/* (CMD6,34,35,36,37,50) */
					/* (11) Reserved */
					/* (CMD?) */

/*
 * CSD field definitions
 */

#घोषणा CSD_STRUCT_VER_1_0  0           /* Valid क्रम प्रणाली specअगरication 1.0 - 1.2 */
#घोषणा CSD_STRUCT_VER_1_1  1           /* Valid क्रम प्रणाली specअगरication 1.4 - 2.2 */
#घोषणा CSD_STRUCT_VER_1_2  2           /* Valid क्रम प्रणाली specअगरication 3.1 - 3.2 - 3.31 - 4.0 - 4.1 */
#घोषणा CSD_STRUCT_EXT_CSD  3           /* Version is coded in CSD_STRUCTURE in EXT_CSD */

#घोषणा CSD_SPEC_VER_0      0           /* Implements प्रणाली specअगरication 1.0 - 1.2 */
#घोषणा CSD_SPEC_VER_1      1           /* Implements प्रणाली specअगरication 1.4 */
#घोषणा CSD_SPEC_VER_2      2           /* Implements प्रणाली specअगरication 2.0 - 2.2 */
#घोषणा CSD_SPEC_VER_3      3           /* Implements प्रणाली specअगरication 3.1 - 3.2 - 3.31 */
#घोषणा CSD_SPEC_VER_4      4           /* Implements प्रणाली specअगरication 4.0 - 4.1 */

/*
 * EXT_CSD fields
 */

#घोषणा EXT_CSD_CMDQ_MODE_EN		15	/* R/W */
#घोषणा EXT_CSD_FLUSH_CACHE		32      /* W */
#घोषणा EXT_CSD_CACHE_CTRL		33      /* R/W */
#घोषणा EXT_CSD_POWER_OFF_NOTIFICATION	34	/* R/W */
#घोषणा EXT_CSD_PACKED_FAILURE_INDEX	35	/* RO */
#घोषणा EXT_CSD_PACKED_CMD_STATUS	36	/* RO */
#घोषणा EXT_CSD_EXP_EVENTS_STATUS	54	/* RO, 2 bytes */
#घोषणा EXT_CSD_EXP_EVENTS_CTRL		56	/* R/W, 2 bytes */
#घोषणा EXT_CSD_DATA_SECTOR_SIZE	61	/* R */
#घोषणा EXT_CSD_GP_SIZE_MULT		143	/* R/W */
#घोषणा EXT_CSD_PARTITION_SETTING_COMPLETED 155	/* R/W */
#घोषणा EXT_CSD_PARTITION_ATTRIBUTE	156	/* R/W */
#घोषणा EXT_CSD_PARTITION_SUPPORT	160	/* RO */
#घोषणा EXT_CSD_HPI_MGMT		161	/* R/W */
#घोषणा EXT_CSD_RST_N_FUNCTION		162	/* R/W */
#घोषणा EXT_CSD_BKOPS_EN		163	/* R/W */
#घोषणा EXT_CSD_BKOPS_START		164	/* W */
#घोषणा EXT_CSD_SANITIZE_START		165     /* W */
#घोषणा EXT_CSD_WR_REL_PARAM		166	/* RO */
#घोषणा EXT_CSD_RPMB_MULT		168	/* RO */
#घोषणा EXT_CSD_FW_CONFIG		169	/* R/W */
#घोषणा EXT_CSD_BOOT_WP			173	/* R/W */
#घोषणा EXT_CSD_ERASE_GROUP_DEF		175	/* R/W */
#घोषणा EXT_CSD_PART_CONFIG		179	/* R/W */
#घोषणा EXT_CSD_ERASED_MEM_CONT		181	/* RO */
#घोषणा EXT_CSD_BUS_WIDTH		183	/* R/W */
#घोषणा EXT_CSD_STROBE_SUPPORT		184	/* RO */
#घोषणा EXT_CSD_HS_TIMING		185	/* R/W */
#घोषणा EXT_CSD_POWER_CLASS		187	/* R/W */
#घोषणा EXT_CSD_REV			192	/* RO */
#घोषणा EXT_CSD_STRUCTURE		194	/* RO */
#घोषणा EXT_CSD_CARD_TYPE		196	/* RO */
#घोषणा EXT_CSD_DRIVER_STRENGTH		197	/* RO */
#घोषणा EXT_CSD_OUT_OF_INTERRUPT_TIME	198	/* RO */
#घोषणा EXT_CSD_PART_SWITCH_TIME        199     /* RO */
#घोषणा EXT_CSD_PWR_CL_52_195		200	/* RO */
#घोषणा EXT_CSD_PWR_CL_26_195		201	/* RO */
#घोषणा EXT_CSD_PWR_CL_52_360		202	/* RO */
#घोषणा EXT_CSD_PWR_CL_26_360		203	/* RO */
#घोषणा EXT_CSD_SEC_CNT			212	/* RO, 4 bytes */
#घोषणा EXT_CSD_S_A_TIMEOUT		217	/* RO */
#घोषणा EXT_CSD_REL_WR_SEC_C		222	/* RO */
#घोषणा EXT_CSD_HC_WP_GRP_SIZE		221	/* RO */
#घोषणा EXT_CSD_ERASE_TIMEOUT_MULT	223	/* RO */
#घोषणा EXT_CSD_HC_ERASE_GRP_SIZE	224	/* RO */
#घोषणा EXT_CSD_BOOT_MULT		226	/* RO */
#घोषणा EXT_CSD_SEC_TRIM_MULT		229	/* RO */
#घोषणा EXT_CSD_SEC_ERASE_MULT		230	/* RO */
#घोषणा EXT_CSD_SEC_FEATURE_SUPPORT	231	/* RO */
#घोषणा EXT_CSD_TRIM_MULT		232	/* RO */
#घोषणा EXT_CSD_PWR_CL_200_195		236	/* RO */
#घोषणा EXT_CSD_PWR_CL_200_360		237	/* RO */
#घोषणा EXT_CSD_PWR_CL_DDR_52_195	238	/* RO */
#घोषणा EXT_CSD_PWR_CL_DDR_52_360	239	/* RO */
#घोषणा EXT_CSD_BKOPS_STATUS		246	/* RO */
#घोषणा EXT_CSD_POWER_OFF_LONG_TIME	247	/* RO */
#घोषणा EXT_CSD_GENERIC_CMD6_TIME	248	/* RO */
#घोषणा EXT_CSD_CACHE_SIZE		249	/* RO, 4 bytes */
#घोषणा EXT_CSD_PWR_CL_DDR_200_360	253	/* RO */
#घोषणा EXT_CSD_FIRMWARE_VERSION	254	/* RO, 8 bytes */
#घोषणा EXT_CSD_PRE_EOL_INFO		267	/* RO */
#घोषणा EXT_CSD_DEVICE_LIFE_TIME_EST_TYP_A	268	/* RO */
#घोषणा EXT_CSD_DEVICE_LIFE_TIME_EST_TYP_B	269	/* RO */
#घोषणा EXT_CSD_CMDQ_DEPTH		307	/* RO */
#घोषणा EXT_CSD_CMDQ_SUPPORT		308	/* RO */
#घोषणा EXT_CSD_SUPPORTED_MODE		493	/* RO */
#घोषणा EXT_CSD_TAG_UNIT_SIZE		498	/* RO */
#घोषणा EXT_CSD_DATA_TAG_SUPPORT	499	/* RO */
#घोषणा EXT_CSD_MAX_PACKED_WRITES	500	/* RO */
#घोषणा EXT_CSD_MAX_PACKED_READS	501	/* RO */
#घोषणा EXT_CSD_BKOPS_SUPPORT		502	/* RO */
#घोषणा EXT_CSD_HPI_FEATURES		503	/* RO */

/*
 * EXT_CSD field definitions
 */

#घोषणा EXT_CSD_WR_REL_PARAM_EN		(1<<2)
#घोषणा EXT_CSD_WR_REL_PARAM_EN_RPMB_REL_WR	(1<<4)

#घोषणा EXT_CSD_BOOT_WP_B_PWR_WP_DIS	(0x40)
#घोषणा EXT_CSD_BOOT_WP_B_PERM_WP_DIS	(0x10)
#घोषणा EXT_CSD_BOOT_WP_B_PERM_WP_EN	(0x04)
#घोषणा EXT_CSD_BOOT_WP_B_PWR_WP_EN	(0x01)

#घोषणा EXT_CSD_PART_CONFIG_ACC_MASK	(0x7)
#घोषणा EXT_CSD_PART_CONFIG_ACC_BOOT0	(0x1)
#घोषणा EXT_CSD_PART_CONFIG_ACC_RPMB	(0x3)
#घोषणा EXT_CSD_PART_CONFIG_ACC_GP0	(0x4)

#घोषणा EXT_CSD_PART_SETTING_COMPLETED	(0x1)
#घोषणा EXT_CSD_PART_SUPPORT_PART_EN	(0x1)

#घोषणा EXT_CSD_CMD_SET_NORMAL		(1<<0)
#घोषणा EXT_CSD_CMD_SET_SECURE		(1<<1)
#घोषणा EXT_CSD_CMD_SET_CPSECURE	(1<<2)

#घोषणा EXT_CSD_CARD_TYPE_HS_26	(1<<0)	/* Card can run at 26MHz */
#घोषणा EXT_CSD_CARD_TYPE_HS_52	(1<<1)	/* Card can run at 52MHz */
#घोषणा EXT_CSD_CARD_TYPE_HS	(EXT_CSD_CARD_TYPE_HS_26 | \
				 EXT_CSD_CARD_TYPE_HS_52)
#घोषणा EXT_CSD_CARD_TYPE_DDR_1_8V  (1<<2)   /* Card can run at 52MHz */
					     /* DDR mode @1.8V or 3V I/O */
#घोषणा EXT_CSD_CARD_TYPE_DDR_1_2V  (1<<3)   /* Card can run at 52MHz */
					     /* DDR mode @1.2V I/O */
#घोषणा EXT_CSD_CARD_TYPE_DDR_52       (EXT_CSD_CARD_TYPE_DDR_1_8V  \
					| EXT_CSD_CARD_TYPE_DDR_1_2V)
#घोषणा EXT_CSD_CARD_TYPE_HS200_1_8V	(1<<4)	/* Card can run at 200MHz */
#घोषणा EXT_CSD_CARD_TYPE_HS200_1_2V	(1<<5)	/* Card can run at 200MHz */
						/* SDR mode @1.2V I/O */
#घोषणा EXT_CSD_CARD_TYPE_HS200		(EXT_CSD_CARD_TYPE_HS200_1_8V | \
					 EXT_CSD_CARD_TYPE_HS200_1_2V)
#घोषणा EXT_CSD_CARD_TYPE_HS400_1_8V	(1<<6)	/* Card can run at 200MHz DDR, 1.8V */
#घोषणा EXT_CSD_CARD_TYPE_HS400_1_2V	(1<<7)	/* Card can run at 200MHz DDR, 1.2V */
#घोषणा EXT_CSD_CARD_TYPE_HS400		(EXT_CSD_CARD_TYPE_HS400_1_8V | \
					 EXT_CSD_CARD_TYPE_HS400_1_2V)
#घोषणा EXT_CSD_CARD_TYPE_HS400ES	(1<<8)	/* Card can run at HS400ES */

#घोषणा EXT_CSD_BUS_WIDTH_1	0	/* Card is in 1 bit mode */
#घोषणा EXT_CSD_BUS_WIDTH_4	1	/* Card is in 4 bit mode */
#घोषणा EXT_CSD_BUS_WIDTH_8	2	/* Card is in 8 bit mode */
#घोषणा EXT_CSD_DDR_BUS_WIDTH_4	5	/* Card is in 4 bit DDR mode */
#घोषणा EXT_CSD_DDR_BUS_WIDTH_8	6	/* Card is in 8 bit DDR mode */
#घोषणा EXT_CSD_BUS_WIDTH_STROBE BIT(7)	/* Enhanced strobe mode */

#घोषणा EXT_CSD_TIMING_BC	0	/* Backwards compatility */
#घोषणा EXT_CSD_TIMING_HS	1	/* High speed */
#घोषणा EXT_CSD_TIMING_HS200	2	/* HS200 */
#घोषणा EXT_CSD_TIMING_HS400	3	/* HS400 */
#घोषणा EXT_CSD_DRV_STR_SHIFT	4	/* Driver Strength shअगरt */

#घोषणा EXT_CSD_SEC_ER_EN	BIT(0)
#घोषणा EXT_CSD_SEC_BD_BLK_EN	BIT(2)
#घोषणा EXT_CSD_SEC_GB_CL_EN	BIT(4)
#घोषणा EXT_CSD_SEC_SANITIZE	BIT(6)  /* v4.5 only */

#घोषणा EXT_CSD_RST_N_EN_MASK	0x3
#घोषणा EXT_CSD_RST_N_ENABLED	1	/* RST_n is enabled on card */

#घोषणा EXT_CSD_NO_POWER_NOTIFICATION	0
#घोषणा EXT_CSD_POWER_ON		1
#घोषणा EXT_CSD_POWER_OFF_SHORT		2
#घोषणा EXT_CSD_POWER_OFF_LONG		3

#घोषणा EXT_CSD_PWR_CL_8BIT_MASK	0xF0	/* 8 bit PWR CLS */
#घोषणा EXT_CSD_PWR_CL_4BIT_MASK	0x0F	/* 8 bit PWR CLS */
#घोषणा EXT_CSD_PWR_CL_8BIT_SHIFT	4
#घोषणा EXT_CSD_PWR_CL_4BIT_SHIFT	0

#घोषणा EXT_CSD_PACKED_EVENT_EN	BIT(3)

/*
 * EXCEPTION_EVENT_STATUS field
 */
#घोषणा EXT_CSD_URGENT_BKOPS		BIT(0)
#घोषणा EXT_CSD_DYNCAP_NEEDED		BIT(1)
#घोषणा EXT_CSD_SYSPOOL_EXHAUSTED	BIT(2)
#घोषणा EXT_CSD_PACKED_FAILURE		BIT(3)

#घोषणा EXT_CSD_PACKED_GENERIC_ERROR	BIT(0)
#घोषणा EXT_CSD_PACKED_INDEXED_ERROR	BIT(1)

/*
 * BKOPS status level
 */
#घोषणा EXT_CSD_BKOPS_LEVEL_2		0x2

/*
 * BKOPS modes
 */
#घोषणा EXT_CSD_MANUAL_BKOPS_MASK	0x01
#घोषणा EXT_CSD_AUTO_BKOPS_MASK		0x02

/*
 * Command Queue
 */
#घोषणा EXT_CSD_CMDQ_MODE_ENABLED	BIT(0)
#घोषणा EXT_CSD_CMDQ_DEPTH_MASK		GENMASK(4, 0)
#घोषणा EXT_CSD_CMDQ_SUPPORTED		BIT(0)

/*
 * MMC_SWITCH access modes
 */
#घोषणा MMC_SWITCH_MODE_CMD_SET		0x00	/* Change the command set */
#घोषणा MMC_SWITCH_MODE_SET_BITS	0x01	/* Set bits which are 1 in value */
#घोषणा MMC_SWITCH_MODE_CLEAR_BITS	0x02	/* Clear bits which are 1 in value */
#घोषणा MMC_SWITCH_MODE_WRITE_BYTE	0x03	/* Set target to value */

/*
 * Erase/trim/discard
 */
#घोषणा MMC_ERASE_ARG			0x00000000
#घोषणा MMC_SECURE_ERASE_ARG		0x80000000
#घोषणा MMC_TRIM_ARG			0x00000001
#घोषणा MMC_DISCARD_ARG			0x00000003
#घोषणा MMC_SECURE_TRIM1_ARG		0x80000001
#घोषणा MMC_SECURE_TRIM2_ARG		0x80008000
#घोषणा MMC_SECURE_ARGS			0x80000000
#घोषणा MMC_TRIM_ARGS			0x00008001

#घोषणा mmc_driver_type_mask(n)		(1 << (n))

#पूर्ण_अगर /* LINUX_MMC_MMC_H */
