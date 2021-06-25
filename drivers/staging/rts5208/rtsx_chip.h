<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Driver क्रम Realtek PCI-Express card पढ़ोer
 *
 * Copyright(c) 2009-2013 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Wei WANG (wei_wang@realsil.com.cn)
 *   Micky Ching (micky_ching@realsil.com.cn)
 */

#अगर_अघोषित __REALTEK_RTSX_CHIP_H
#घोषणा __REALTEK_RTSX_CHIP_H

#समावेश "rtsx.h"

#घोषणा SUPPORT_CPRM
#घोषणा SUPPORT_OCP
#घोषणा SUPPORT_SDIO_ASPM
#घोषणा SUPPORT_MAGIC_GATE
#घोषणा SUPPORT_MSXC
#घोषणा SUPPORT_SD_LOCK
/* Hardware चयन bus_ctl and cd_ctl स्वतःmatically */
#घोषणा HW_AUTO_SWITCH_SD_BUS
/* Enable hardware पूर्णांकerrupt ग_लिखो clear */
#घोषणा HW_INT_WRITE_CLR
/* #घोषणा LED_AUTO_BLINK */
/* #घोषणा DISABLE_CARD_INT */

#अगर_घोषित SUPPORT_MAGIC_GATE
	/* Using NORMAL_WRITE instead of AUTO_WRITE to set ICV */
	#घोषणा MG_SET_ICV_SLOW
	/* HW may miss ERR/CMDNK संकेत when sampling INT status. */
	#घोषणा MS_SAMPLE_INT_ERR
	/*
	 * HW DO NOT support Wait_INT function
	 * during READ_BYTES transfer mode
	 */
	#घोषणा READ_BYTES_WAIT_INT
#पूर्ण_अगर

#अगर_घोषित SUPPORT_MSXC
#घोषणा XC_POWERCLASS
#घोषणा SUPPORT_PCGL_1P18
#पूर्ण_अगर

#अगर_अघोषित LED_AUTO_BLINK
#घोषणा REGULAR_BLINK
#पूर्ण_अगर

#घोषणा LED_BLINK_SPEED		5
#घोषणा LED_TOGGLE_INTERVAL	6
#घोषणा	GPIO_TOGGLE_THRESHOLD   1024
#घोषणा LED_GPIO		0

#घोषणा POLLING_INTERVAL	30

#घोषणा TRACE_ITEM_CNT		64

#अगर_अघोषित STATUS_SUCCESS
#घोषणा STATUS_SUCCESS		0
#पूर्ण_अगर
#अगर_अघोषित STATUS_FAIL
#घोषणा STATUS_FAIL		1
#पूर्ण_अगर
#अगर_अघोषित STATUS_TIMEDOUT
#घोषणा STATUS_TIMEDOUT		2
#पूर्ण_अगर
#अगर_अघोषित STATUS_NOMEM
#घोषणा STATUS_NOMEM		3
#पूर्ण_अगर
#अगर_अघोषित STATUS_READ_FAIL
#घोषणा STATUS_READ_FAIL	4
#पूर्ण_अगर
#अगर_अघोषित STATUS_WRITE_FAIL
#घोषणा STATUS_WRITE_FAIL	5
#पूर्ण_अगर
#अगर_अघोषित STATUS_ERROR
#घोषणा STATUS_ERROR		10
#पूर्ण_अगर

#घोषणा PM_S1			1
#घोषणा PM_S3			3

/*
 * Transport वापस codes
 */

#घोषणा TRANSPORT_GOOD		0   /* Transport good, command good	   */
#घोषणा TRANSPORT_FAILED	1   /* Transport good, command failed   */
#घोषणा TRANSPORT_NO_SENSE	2  /* Command failed, no स्वतः-sense    */
#घोषणा TRANSPORT_ERROR		3   /* Transport bad (i.e. device dead) */

/*
 * Start-Stop-Unit
 */
#घोषणा STOP_MEDIUM			0x00    /* access disable         */
#घोषणा MAKE_MEDIUM_READY		0x01    /* access enable          */
#घोषणा UNLOAD_MEDIUM			0x02    /* unload                 */
#घोषणा LOAD_MEDIUM			0x03    /* load                   */

/*
 * STANDARD_INQUIRY
 */
#घोषणा QULIFIRE                0x00
#घोषणा AENC_FNC                0x00
#घोषणा TRML_IOP                0x00
#घोषणा REL_ADR                 0x00
#घोषणा WBUS_32                 0x00
#घोषणा WBUS_16                 0x00
#घोषणा SYNC                    0x00
#घोषणा LINKED                  0x00
#घोषणा CMD_QUE                 0x00
#घोषणा SFT_RE                  0x00

#घोषणा VEN_ID_LEN              8               /* Venकरोr ID Length         */
#घोषणा PRDCT_ID_LEN            16              /* Product ID Length        */
#घोषणा PRDCT_REV_LEN           4               /* Product LOT Length       */

/* Dynamic flag definitions: used in set_bit() etc. */
/* 0x00040000 transfer is active */
#घोषणा RTSX_FLIDX_TRANS_ACTIVE		18
/* 0x00100000 पात is in progress */
#घोषणा RTSX_FLIDX_ABORTING		20
/* 0x00200000 disconnect in progress */
#घोषणा RTSX_FLIDX_DISCONNECTING	21

#घोषणा ABORTING_OR_DISCONNECTING	((1UL << US_FLIDX_ABORTING) | \
					 (1UL << US_FLIDX_DISCONNECTING))

/* 0x00400000 device reset in progress */
#घोषणा RTSX_FLIDX_RESETTING		22
/* 0x00800000 SCSI midlayer समयd out  */
#घोषणा RTSX_FLIDX_TIMED_OUT		23
#घोषणा DRCT_ACCESS_DEV         0x00    /* Direct Access Device      */
#घोषणा RMB_DISC                0x80    /* The Device is Removable   */
#घोषणा ANSI_SCSI2              0x02    /* Based on ANSI-SCSI2       */

#घोषणा SCSI                    0x00    /* Interface ID              */

#घोषणा	WRITE_PROTECTED_MEDIA 0x07

/*---- sense key ----*/
#घोषणा ILI                     0x20    /* ILI bit is on                    */

#घोषणा NO_SENSE                0x00    /* not exist sense key              */
#घोषणा RECOVER_ERR             0x01    /* Target/Logical unit is recoverd  */
#घोषणा NOT_READY               0x02    /* Logical unit is not पढ़ोy        */
#घोषणा MEDIA_ERR               0x03    /* medium/data error                */
#घोषणा HARDWARE_ERR            0x04    /* hardware error                   */
#घोषणा ILGAL_REQ               0x05    /* CDB/parameter/identअगरy msg error */
#घोषणा UNIT_ATTENTION          0x06    /* unit attention condition occur   */
#घोषणा DAT_PRTCT               0x07    /* पढ़ो/ग_लिखो is desable            */
#घोषणा BLNC_CHK                0x08    /* find blank/DOF in पढ़ो           */
					/* ग_लिखो to unblank area            */
#घोषणा CPY_ABRT                0x0a    /* Copy/Compare/Copy&Verअगरy illegal */
#घोषणा ABRT_CMD                0x0b    /* Target make the command in error */
#घोषणा EQUAL                   0x0c    /* Search Data end with Equal       */
#घोषणा VLM_OVRFLW              0x0d    /* Some data are left in buffer     */
#घोषणा MISCMP                  0x0e    /* find inequality                  */

#घोषणा READ_ERR                -1
#घोषणा WRITE_ERR               -2

#घोषणा	FIRST_RESET		0x01
#घोषणा	USED_EXIST		0x02

/*
 * SENSE_DATA
 */
/*---- valid ----*/
#घोषणा SENSE_VALID             0x80    /* Sense data is valid as SCSI2     */
#घोषणा SENSE_INVALID           0x00    /* Sense data is invalid as SCSI2   */

/*---- error code ----*/
#घोषणा CUR_ERR                 0x70    /* current error                    */
#घोषणा DEF_ERR                 0x71    /* specअगरic command error           */

/*---- sense key Inक्रमmation ----*/
#घोषणा SNSKEYINFO_LEN          3       /* length of sense key inक्रमmation   */

#घोषणा SKSV                    0x80
#घोषणा CDB_ILLEGAL             0x40
#घोषणा DAT_ILLEGAL             0x00
#घोषणा BPV                     0x08
#घोषणा BIT_ILLEGAL0            0       /* bit0 is illegal                  */
#घोषणा BIT_ILLEGAL1            1       /* bit1 is illegal                  */
#घोषणा BIT_ILLEGAL2            2       /* bit2 is illegal                  */
#घोषणा BIT_ILLEGAL3            3       /* bit3 is illegal                  */
#घोषणा BIT_ILLEGAL4            4       /* bit4 is illegal                  */
#घोषणा BIT_ILLEGAL5            5       /* bit5 is illegal                  */
#घोषणा BIT_ILLEGAL6            6       /* bit6 is illegal                  */
#घोषणा BIT_ILLEGAL7            7       /* bit7 is illegal                  */

/*---- ASC ----*/
#घोषणा ASC_NO_INFO             0x00
#घोषणा ASC_MISCMP              0x1d
#घोषणा ASC_INVLD_CDB           0x24
#घोषणा ASC_INVLD_PARA          0x26
#घोषणा ASC_LU_NOT_READY	0x04
#घोषणा ASC_WRITE_ERR           0x0c
#घोषणा ASC_READ_ERR            0x11
#घोषणा ASC_LOAD_EJCT_ERR       0x53
#घोषणा	ASC_MEDIA_NOT_PRESENT	0x3A
#घोषणा	ASC_MEDIA_CHANGED	0x28
#घोषणा	ASC_MEDIA_IN_PROCESS	0x04
#घोषणा	ASC_WRITE_PROTECT	0x27
#घोषणा ASC_LUN_NOT_SUPPORTED	0x25

/*---- ASQC ----*/
#घोषणा ASCQ_NO_INFO            0x00
#घोषणा	ASCQ_MEDIA_IN_PROCESS	0x01
#घोषणा ASCQ_MISCMP             0x00
#घोषणा ASCQ_INVLD_CDB          0x00
#घोषणा ASCQ_INVLD_PARA         0x02
#घोषणा ASCQ_LU_NOT_READY	0x02
#घोषणा ASCQ_WRITE_ERR          0x02
#घोषणा ASCQ_READ_ERR           0x00
#घोषणा ASCQ_LOAD_EJCT_ERR      0x00
#घोषणा	ASCQ_WRITE_PROTECT	0x00

काष्ठा sense_data_t अणु
	अचिन्हित अक्षर   err_code;	/* error code */
	/* bit7 : valid */
	/*   (1 : SCSI2) */
	/*   (0 : Venकरोr * specअगरic) */
	/* bit6-0 : error * code */
	/*  (0x70 : current * error) */
	/*  (0x71 : specअगरic command error) */
	अचिन्हित अक्षर   seg_no;		/* segment No.                      */
	अचिन्हित अक्षर   sense_key;	/* byte5 : ILI                      */
	/* bit3-0 : sense key              */
	अचिन्हित अक्षर   info[4];	/* inक्रमmation                       */
	अचिन्हित अक्षर   ad_sense_len;	/* additional sense data length     */
	अचिन्हित अक्षर   cmd_info[4];	/* command specअगरic inक्रमmation      */
	अचिन्हित अक्षर   asc;		/* ASC                              */
	अचिन्हित अक्षर   ascq;		/* ASCQ                             */
	अचिन्हित अक्षर   rfu;		/* FRU                              */
	अचिन्हित अक्षर   sns_key_info[3];/* sense key specअगरic inक्रमmation    */
पूर्ण;

/* PCI Operation Register Address */
#घोषणा RTSX_HCBAR		0x00
#घोषणा RTSX_HCBCTLR		0x04
#घोषणा RTSX_HDBAR		0x08
#घोषणा RTSX_HDBCTLR		0x0C
#घोषणा RTSX_HAIMR		0x10
#घोषणा RTSX_BIPR		0x14
#घोषणा RTSX_BIER		0x18

/* Host command buffer control रेजिस्टर */
#घोषणा STOP_CMD		(0x01 << 28)

/* Host data buffer control रेजिस्टर */
#घोषणा SDMA_MODE		0x00
#घोषणा ADMA_MODE		(0x02 << 26)
#घोषणा STOP_DMA		(0x01 << 28)
#घोषणा TRIG_DMA		(0x01 << 31)

/* Bus पूर्णांकerrupt pending रेजिस्टर */
#घोषणा CMD_DONE_INT		BIT(31)
#घोषणा DATA_DONE_INT		BIT(30)
#घोषणा TRANS_OK_INT		BIT(29)
#घोषणा TRANS_FAIL_INT		BIT(28)
#घोषणा XD_INT			BIT(27)
#घोषणा MS_INT			BIT(26)
#घोषणा SD_INT			BIT(25)
#घोषणा GPIO0_INT		BIT(24)
#घोषणा OC_INT			BIT(23)
#घोषणा SD_WRITE_PROTECT	BIT(19)
#घोषणा XD_EXIST		BIT(18)
#घोषणा MS_EXIST		BIT(17)
#घोषणा SD_EXIST		BIT(16)
#घोषणा DELINK_INT		GPIO0_INT
#घोषणा MS_OC_INT		BIT(23)
#घोषणा SD_OC_INT		BIT(22)

#घोषणा CARD_INT		(XD_INT | MS_INT | SD_INT)
#घोषणा NEED_COMPLETE_INT	(DATA_DONE_INT | TRANS_OK_INT | TRANS_FAIL_INT)
#घोषणा RTSX_INT		(CMD_DONE_INT | NEED_COMPLETE_INT | CARD_INT | \
				 GPIO0_INT | OC_INT)

#घोषणा CARD_EXIST		(XD_EXIST | MS_EXIST | SD_EXIST)

/* Bus पूर्णांकerrupt enable रेजिस्टर */
#घोषणा CMD_DONE_INT_EN		BIT(31)
#घोषणा DATA_DONE_INT_EN	BIT(30)
#घोषणा TRANS_OK_INT_EN		BIT(29)
#घोषणा TRANS_FAIL_INT_EN	BIT(28)
#घोषणा XD_INT_EN		BIT(27)
#घोषणा MS_INT_EN		BIT(26)
#घोषणा SD_INT_EN		BIT(25)
#घोषणा GPIO0_INT_EN		BIT(24)
#घोषणा OC_INT_EN		BIT(23)
#घोषणा DELINK_INT_EN		GPIO0_INT_EN
#घोषणा MS_OC_INT_EN		BIT(23)
#घोषणा SD_OC_INT_EN		BIT(22)

#घोषणा READ_REG_CMD		0
#घोषणा WRITE_REG_CMD		1
#घोषणा CHECK_REG_CMD		2

#घोषणा HOST_TO_DEVICE		0
#घोषणा DEVICE_TO_HOST		1

#घोषणा RTSX_RESV_BUF_LEN	4096
#घोषणा HOST_CMDS_BUF_LEN	1024
#घोषणा HOST_SG_TBL_BUF_LEN	(RTSX_RESV_BUF_LEN - HOST_CMDS_BUF_LEN)

#घोषणा SD_NR		2
#घोषणा MS_NR		3
#घोषणा XD_NR		4
#घोषणा SPI_NR		7
#घोषणा SD_CARD		BIT(SD_NR)
#घोषणा MS_CARD		BIT(MS_NR)
#घोषणा XD_CARD		BIT(XD_NR)
#घोषणा SPI_CARD	BIT(SPI_NR)

#घोषणा MAX_ALLOWED_LUN_CNT	8

#घोषणा XD_FREE_TABLE_CNT	1200
#घोषणा MS_FREE_TABLE_CNT	512

/* Bit Operation */
#घोषणा SET_BIT(data, idx)	((data) |= 1 << (idx))
#घोषणा CLR_BIT(data, idx)	((data) &= ~(1 << (idx)))
#घोषणा CHK_BIT(data, idx)	((data) & (1 << (idx)))

/* SG descriptor */
#घोषणा RTSX_SG_INT		0x04
#घोषणा RTSX_SG_END		0x02
#घोषणा RTSX_SG_VALID		0x01

#घोषणा RTSX_SG_NO_OP		0x00
#घोषणा RTSX_SG_TRANS_DATA	(0x02 << 4)
#घोषणा RTSX_SG_LINK_DESC	(0x03 << 4)

काष्ठा rtsx_chip;

प्रकार पूर्णांक (*card_rw_func)(काष्ठा scsi_cmnd *srb, काष्ठा rtsx_chip *chip,
			u32 sec_addr, u16 sec_cnt);

/* Supported Clock */
क्रमागत card_घड़ी	अणुCLK_20 = 1, CLK_30, CLK_40, CLK_50, CLK_60,
		 CLK_80, CLK_100, CLK_120, CLK_150, CLK_200पूर्ण;

क्रमागत RTSX_STAT	अणुRTSX_STAT_INIT, RTSX_STAT_IDLE, RTSX_STAT_RUN, RTSX_STAT_SS,
		 RTSX_STAT_DELINK, RTSX_STAT_SUSPEND,
		 RTSX_STAT_ABORT, RTSX_STAT_DISCONNECTपूर्ण;
क्रमागत IC_VER	अणुIC_VER_AB, IC_VER_C = 2, IC_VER_D = 3पूर्ण;

#घोषणा MAX_RESET_CNT		3

/* For MS Card */
#घोषणा MAX_DEFECTIVE_BLOCK     10

काष्ठा zone_entry अणु
	u16 *l2p_table;
	u16 *मुक्त_table;
	u16 defect_list[MAX_DEFECTIVE_BLOCK];  /* For MS card only */
	पूर्णांक set_index;
	पूर्णांक get_index;
	पूर्णांक unused_blk_cnt;
	पूर्णांक disable_count;
	/* To indicate whether the L2P table of this zone has been built. */
	पूर्णांक build_flag;
पूर्ण;

#घोषणा TYPE_SD			0x0000
#घोषणा TYPE_MMC		0x0001

/* TYPE_SD */
#घोषणा SD_HS			0x0100
#घोषणा SD_SDR50		0x0200
#घोषणा SD_DDR50		0x0400
#घोषणा SD_SDR104		0x0800
#घोषणा SD_HCXC			0x1000

/* TYPE_MMC */
#घोषणा MMC_26M			0x0100
#घोषणा MMC_52M			0x0200
#घोषणा MMC_4BIT		0x0400
#घोषणा MMC_8BIT		0x0800
#घोषणा MMC_SECTOR_MODE		0x1000
#घोषणा MMC_DDR52		0x2000

/* SD card */
#घोषणा CHK_SD(sd_card)			(((sd_card)->sd_type & 0xFF) == TYPE_SD)
#घोषणा CHK_SD_HS(sd_card)		(CHK_SD(sd_card) && \
					 ((sd_card)->sd_type & SD_HS))
#घोषणा CHK_SD_SDR50(sd_card)		(CHK_SD(sd_card) && \
					 ((sd_card)->sd_type & SD_SDR50))
#घोषणा CHK_SD_DDR50(sd_card)		(CHK_SD(sd_card) && \
					 ((sd_card)->sd_type & SD_DDR50))
#घोषणा CHK_SD_SDR104(sd_card)		(CHK_SD(sd_card) && \
					 ((sd_card)->sd_type & SD_SDR104))
#घोषणा CHK_SD_HCXC(sd_card)		(CHK_SD(sd_card) && \
					 ((sd_card)->sd_type & SD_HCXC))
#घोषणा CHK_SD_HC(sd_card)		(CHK_SD_HCXC(sd_card) && \
					 ((sd_card)->capacity <= 0x4000000))
#घोषणा CHK_SD_XC(sd_card)		(CHK_SD_HCXC(sd_card) && \
					 ((sd_card)->capacity > 0x4000000))
#घोषणा CHK_SD30_SPEED(sd_card)		(CHK_SD_SDR50(sd_card) || \
					 CHK_SD_DDR50(sd_card) || \
					 CHK_SD_SDR104(sd_card))

#घोषणा SET_SD(sd_card)			((sd_card)->sd_type = TYPE_SD)
#घोषणा SET_SD_HS(sd_card)		((sd_card)->sd_type |= SD_HS)
#घोषणा SET_SD_SDR50(sd_card)		((sd_card)->sd_type |= SD_SDR50)
#घोषणा SET_SD_DDR50(sd_card)		((sd_card)->sd_type |= SD_DDR50)
#घोषणा SET_SD_SDR104(sd_card)		((sd_card)->sd_type |= SD_SDR104)
#घोषणा SET_SD_HCXC(sd_card)		((sd_card)->sd_type |= SD_HCXC)

#घोषणा CLR_SD_HS(sd_card)		((sd_card)->sd_type &= ~SD_HS)
#घोषणा CLR_SD_SDR50(sd_card)		((sd_card)->sd_type &= ~SD_SDR50)
#घोषणा CLR_SD_DDR50(sd_card)		((sd_card)->sd_type &= ~SD_DDR50)
#घोषणा CLR_SD_SDR104(sd_card)		((sd_card)->sd_type &= ~SD_SDR104)
#घोषणा CLR_SD_HCXC(sd_card)		((sd_card)->sd_type &= ~SD_HCXC)

/* MMC card */
#घोषणा CHK_MMC(sd_card)		(((sd_card)->sd_type & 0xFF) == \
					 TYPE_MMC)
#घोषणा CHK_MMC_26M(sd_card)		(CHK_MMC(sd_card) && \
					 ((sd_card)->sd_type & MMC_26M))
#घोषणा CHK_MMC_52M(sd_card)		(CHK_MMC(sd_card) && \
					 ((sd_card)->sd_type & MMC_52M))
#घोषणा CHK_MMC_4BIT(sd_card)		(CHK_MMC(sd_card) && \
					 ((sd_card)->sd_type & MMC_4BIT))
#घोषणा CHK_MMC_8BIT(sd_card)		(CHK_MMC(sd_card) && \
					 ((sd_card)->sd_type & MMC_8BIT))
#घोषणा CHK_MMC_SECTOR_MODE(sd_card)	(CHK_MMC(sd_card) && \
					 ((sd_card)->sd_type & MMC_SECTOR_MODE))
#घोषणा CHK_MMC_DDR52(sd_card)		(CHK_MMC(sd_card) && \
					 ((sd_card)->sd_type & MMC_DDR52))

#घोषणा SET_MMC(sd_card)		((sd_card)->sd_type = TYPE_MMC)
#घोषणा SET_MMC_26M(sd_card)		((sd_card)->sd_type |= MMC_26M)
#घोषणा SET_MMC_52M(sd_card)		((sd_card)->sd_type |= MMC_52M)
#घोषणा SET_MMC_4BIT(sd_card)		((sd_card)->sd_type |= MMC_4BIT)
#घोषणा SET_MMC_8BIT(sd_card)		((sd_card)->sd_type |= MMC_8BIT)
#घोषणा SET_MMC_SECTOR_MODE(sd_card)	((sd_card)->sd_type |= MMC_SECTOR_MODE)
#घोषणा SET_MMC_DDR52(sd_card)		((sd_card)->sd_type |= MMC_DDR52)

#घोषणा CLR_MMC_26M(sd_card)		((sd_card)->sd_type &= ~MMC_26M)
#घोषणा CLR_MMC_52M(sd_card)		((sd_card)->sd_type &= ~MMC_52M)
#घोषणा CLR_MMC_4BIT(sd_card)		((sd_card)->sd_type &= ~MMC_4BIT)
#घोषणा CLR_MMC_8BIT(sd_card)		((sd_card)->sd_type &= ~MMC_8BIT)
#घोषणा CLR_MMC_SECTOR_MODE(sd_card)	((sd_card)->sd_type &= ~MMC_SECTOR_MODE)
#घोषणा CLR_MMC_DDR52(sd_card)		((sd_card)->sd_type &= ~MMC_DDR52)

#घोषणा CHK_MMC_HS(sd_card)		(CHK_MMC_52M(sd_card) && \
					 CHK_MMC_26M(sd_card))
#घोषणा CLR_MMC_HS(sd_card)			\
करो अणु						\
	CLR_MMC_DDR52(sd_card);			\
	CLR_MMC_52M(sd_card);			\
	CLR_MMC_26M(sd_card);			\
पूर्ण जबतक (0)

#घोषणा SD_SUPPORT_CLASS_TEN		0x01
#घोषणा SD_SUPPORT_1V8			0x02

#घोषणा SD_SET_CLASS_TEN(sd_card)	((sd_card)->sd_setting |= \
					 SD_SUPPORT_CLASS_TEN)
#घोषणा SD_CHK_CLASS_TEN(sd_card)	((sd_card)->sd_setting & \
					 SD_SUPPORT_CLASS_TEN)
#घोषणा SD_CLR_CLASS_TEN(sd_card)	((sd_card)->sd_setting &= \
					 ~SD_SUPPORT_CLASS_TEN)
#घोषणा SD_SET_1V8(sd_card)		((sd_card)->sd_setting |= \
					 SD_SUPPORT_1V8)
#घोषणा SD_CHK_1V8(sd_card)		((sd_card)->sd_setting & \
					 SD_SUPPORT_1V8)
#घोषणा SD_CLR_1V8(sd_card)		((sd_card)->sd_setting &= \
					 ~SD_SUPPORT_1V8)

काष्ठा sd_info अणु
	u16 sd_type;
	u8 err_code;
	u8 sd_data_buf_पढ़ोy;
	u32 sd_addr;
	u32 capacity;

	u8 raw_csd[16];
	u8 raw_scr[8];

	/* Sequential RW */
	पूर्णांक seq_mode;
	क्रमागत dma_data_direction pre_dir;
	u32 pre_sec_addr;
	u16 pre_sec_cnt;

	पूर्णांक cleanup_counter;

	पूर्णांक sd_घड़ी;

	पूर्णांक mmc_करोnt_चयन_bus;

#अगर_घोषित SUPPORT_CPRM
	पूर्णांक sd_pass_thru_en;
	पूर्णांक pre_cmd_err;
	u8 last_rsp_type;
	u8 rsp[17];
#पूर्ण_अगर

	u8 func_group1_mask;
	u8 func_group2_mask;
	u8 func_group3_mask;
	u8 func_group4_mask;

	u8 sd_चयन_fail;
	u8 sd_पढ़ो_phase;

#अगर_घोषित SUPPORT_SD_LOCK
	u8 sd_lock_status;
	u8 sd_erase_status;
	u8 sd_lock_notअगरy;
#पूर्ण_अगर
	पूर्णांक need_retune;
पूर्ण;

काष्ठा xd_delay_ग_लिखो_tag अणु
	u32 old_phyblock;
	u32 new_phyblock;
	u32 logblock;
	u8 pageoff;
	u8 delay_ग_लिखो_flag;
पूर्ण;

काष्ठा xd_info अणु
	u8 maker_code;
	u8 device_code;
	u8 block_shअगरt;
	u8 page_off;
	u8 addr_cycle;
	u16 cis_block;
	u8 multi_flag;
	u8 err_code;
	u32 capacity;

	काष्ठा zone_entry *zone;
	पूर्णांक zone_cnt;

	काष्ठा xd_delay_ग_लिखो_tag delay_ग_लिखो;
	पूर्णांक cleanup_counter;

	पूर्णांक xd_घड़ी;
पूर्ण;

#घोषणा MODE_512_SEQ		0x01
#घोषणा MODE_2K_SEQ		0x02

#घोषणा TYPE_MS			0x0000
#घोषणा TYPE_MSPRO		0x0001

#घोषणा MS_4BIT			0x0100
#घोषणा MS_8BIT			0x0200
#घोषणा MS_HG			0x0400
#घोषणा MS_XC			0x0800

#घोषणा HG8BIT			(MS_HG | MS_8BIT)

#घोषणा CHK_MSPRO(ms_card)	(((ms_card)->ms_type & 0xFF) == TYPE_MSPRO)
#घोषणा CHK_HG8BIT(ms_card)	(CHK_MSPRO(ms_card) && \
				 (((ms_card)->ms_type & HG8BIT) == HG8BIT))
#घोषणा CHK_MSXC(ms_card)	(CHK_MSPRO(ms_card) && \
				 ((ms_card)->ms_type & MS_XC))
#घोषणा CHK_MSHG(ms_card)	(CHK_MSPRO(ms_card) && \
				 ((ms_card)->ms_type & MS_HG))

#घोषणा CHK_MS8BIT(ms_card)	(((ms_card)->ms_type & MS_8BIT))
#घोषणा CHK_MS4BIT(ms_card)	(((ms_card)->ms_type & MS_4BIT))

काष्ठा ms_delay_ग_लिखो_tag अणु
	u16 old_phyblock;
	u16 new_phyblock;
	u16 logblock;
	u8 pageoff;
	u8 delay_ग_लिखो_flag;
पूर्ण;

काष्ठा ms_info अणु
	u16 ms_type;
	u8 block_shअगरt;
	u8 page_off;
	u16 total_block;
	u16 boot_block;
	u32 capacity;

	u8 check_ms_flow;
	u8 चयन_8bit_fail;
	u8 err_code;

	काष्ठा zone_entry *segment;
	पूर्णांक segment_cnt;

	पूर्णांक pro_under_क्रमmatting;
	पूर्णांक क्रमmat_status;
	u16 progress;
	u8 raw_sys_info[96];
#अगर_घोषित SUPPORT_PCGL_1P18
	u8 raw_model_name[48];
#पूर्ण_अगर

	u8 multi_flag;

	/* Sequential RW */
	u8 seq_mode;
	क्रमागत dma_data_direction pre_dir;
	u32 pre_sec_addr;
	u16 pre_sec_cnt;
	u32 total_sec_cnt;

	काष्ठा ms_delay_ग_लिखो_tag delay_ग_लिखो;

	पूर्णांक cleanup_counter;

	पूर्णांक ms_घड़ी;

#अगर_घोषित SUPPORT_MAGIC_GATE
	u8 magic_gate_id[16];
	u8 mg_entry_num;
	पूर्णांक mg_auth;    /* flag to indicate authentication process */
#पूर्ण_अगर
पूर्ण;

काष्ठा spi_info अणु
	u8 use_clk;
	u8 ग_लिखो_en;
	u16 clk_भाग;
	u8 err_code;

	पूर्णांक spi_घड़ी;
पूर्ण;

/************/
/* LUN mode */
/************/
/* Single LUN, support xD/SD/MS */
#घोषणा DEFAULT_SINGLE		0
/* 2 LUN mode, support SD/MS */
#घोषणा SD_MS_2LUN		1
/* Single LUN, but only support SD/MS, क्रम Barossa LQFP */
#घोषणा SD_MS_1LUN		2

#घोषणा LAST_LUN_MODE		2

/* Barossa package */
#घोषणा QFN		0
#घोषणा LQFP		1

/******************/
/* sd_ctl bit map */
/******************/
/* SD push poपूर्णांक control, bit 0, 1 */
#घोषणा SD_PUSH_POINT_CTL_MASK		0x03
#घोषणा SD_PUSH_POINT_DELAY		0x01
#घोषणा SD_PUSH_POINT_AUTO		0x02
/* SD sample poपूर्णांक control, bit 2, 3 */
#घोषणा SD_SAMPLE_POINT_CTL_MASK	0x0C
#घोषणा SD_SAMPLE_POINT_DELAY		0x04
#घोषणा SD_SAMPLE_POINT_AUTO		0x08
/* SD DDR Tx phase set by user, bit 4 */
#घोषणा SD_DDR_TX_PHASE_SET_BY_USER	0x10
/* MMC DDR Tx phase set by user, bit 5 */
#घोषणा MMC_DDR_TX_PHASE_SET_BY_USER	0x20
/* Support MMC DDR mode, bit 6 */
#घोषणा SUPPORT_MMC_DDR_MODE		0x40
/* Reset MMC at first */
#घोषणा RESET_MMC_FIRST			0x80

#घोषणा SEQ_START_CRITERIA		0x20

/* MS Power Class En */
#घोषणा POWER_CLASS_2_EN		0x02
#घोषणा POWER_CLASS_1_EN		0x01

#घोषणा MAX_SHOW_CNT			10
#घोषणा MAX_RESET_CNT			3

#घोषणा SDIO_EXIST			0x01
#घोषणा SDIO_IGNORED			0x02

#घोषणा CHK_SDIO_EXIST(chip)		((chip)->sdio_func_exist & SDIO_EXIST)
#घोषणा SET_SDIO_EXIST(chip)		((chip)->sdio_func_exist |= SDIO_EXIST)
#घोषणा CLR_SDIO_EXIST(chip)		((chip)->sdio_func_exist &= ~SDIO_EXIST)

#घोषणा CHK_SDIO_IGNORED(chip)		((chip)->sdio_func_exist & SDIO_IGNORED)
#घोषणा SET_SDIO_IGNORED(chip)		((chip)->sdio_func_exist |= \
					 SDIO_IGNORED)
#घोषणा CLR_SDIO_IGNORED(chip)		((chip)->sdio_func_exist &= \
					 ~SDIO_IGNORED)

काष्ठा rtsx_chip अणु
	काष्ठा rtsx_dev	*rtsx;

	u32		पूर्णांक_reg; /* Bus पूर्णांकerrupt pending रेजिस्टर */
	अक्षर		max_lun;
	व्योम		*context;

	व्योम		*host_cmds_ptr;	/* host commands buffer poपूर्णांकer */
	dma_addr_t	host_cmds_addr;
	पूर्णांक		ci;			/* Command Index */

	व्योम		*host_sg_tbl_ptr;	/* SG descriptor table */
	dma_addr_t	host_sg_tbl_addr;
	पूर्णांक		sgi;			/* SG entry index */

	काष्ठा scsi_cmnd	*srb;			/* current srb */
	काष्ठा sense_data_t	sense_buffer[MAX_ALLOWED_LUN_CNT];

	पूर्णांक			cur_clk;		/* current card घड़ी */

	/* Current accessed card */
	पूर्णांक			cur_card;

	अचिन्हित दीर्घ	need_release;		/* need release bit map */
	अचिन्हित दीर्घ	need_reset;		/* need reset bit map */
	/*
	 * Flag to indicate that this card is just resumed from SS state,
	 * and need released beक्रमe being resetted
	 */
	अचिन्हित दीर्घ		need_reinit;

	पूर्णांक			rw_need_retry;

#अगर_घोषित SUPPORT_OCP
	u32			ocp_पूर्णांक;
	u8			ocp_stat;
#पूर्ण_अगर

	u8	card_exist;	/* card exist bit map (physical exist) */
	u8	card_पढ़ोy;	/* card पढ़ोy bit map (reset successfully) */
	u8	card_fail;	/* card reset fail bit map */
	u8	card_ejected;	/* card ejected bit map */
	u8	card_wp;	/* card ग_लिखो रक्षित bit map */

	u8	lun_mc;		/*
				 * flag to indicate whether to answer
				 * MediaChange
				 */

#अगर_अघोषित LED_AUTO_BLINK
	पूर्णांक			led_toggle_counter;
#पूर्ण_अगर

	पूर्णांक			sd_reset_counter;
	पूर्णांक			xd_reset_counter;
	पूर्णांक			ms_reset_counter;

	/* card bus width */
	u8			card_bus_width[MAX_ALLOWED_LUN_CNT];
	/* card capacity */
	u32			capacity[MAX_ALLOWED_LUN_CNT];
	/* पढ़ो/ग_लिखो card function poपूर्णांकer */
	card_rw_func		rw_card[MAX_ALLOWED_LUN_CNT];
	/* पढ़ो/ग_लिखो capacity, used क्रम GPIO Toggle */
	u32			rw_cap[MAX_ALLOWED_LUN_CNT];
	/* card to lun mapping table */
	u8			card2lun[32];
	/* lun to card mapping table */
	u8			lun2card[MAX_ALLOWED_LUN_CNT];

	पूर्णांक			rw_fail_cnt[MAX_ALLOWED_LUN_CNT];

	पूर्णांक			sd_show_cnt;
	पूर्णांक			xd_show_cnt;
	पूर्णांक			ms_show_cnt;

	/* card inक्रमmation */
	काष्ठा sd_info		sd_card;
	काष्ठा xd_info		xd_card;
	काष्ठा ms_info		ms_card;

	काष्ठा spi_info		spi;

	पूर्णांक			स्वतः_delink_cnt;
	पूर्णांक			स्वतः_delink_allowed;

	पूर्णांक			aspm_enabled;

	पूर्णांक			sdio_aspm;
	पूर्णांक			sdio_idle;
	पूर्णांक			sdio_counter;
	u8			sdio_raw_data[12];

	u8			sd_io;
	u8			sd_पूर्णांक;

	u8			rtsx_flag;

	पूर्णांक			ss_counter;
	पूर्णांक			idle_counter;
	क्रमागत RTSX_STAT		rtsx_stat;

	u16			venकरोr_id;
	u16			product_id;
	u8			ic_version;

	पूर्णांक			driver_first_load;

#अगर_घोषित HW_AUTO_SWITCH_SD_BUS
	पूर्णांक			sdio_in_अक्षरge;
#पूर्ण_अगर

	u8			aspm_level[2];

	पूर्णांक			chip_insert_with_sdio;

	/* Options */

	पूर्णांक adma_mode;

	पूर्णांक स्वतः_delink_en;
	पूर्णांक ss_en;
	u8 lun_mode;
	u8 aspm_l0s_l1_en;

	पूर्णांक घातer_करोwn_in_ss;

	पूर्णांक sdr104_en;
	पूर्णांक ddr50_en;
	पूर्णांक sdr50_en;

	पूर्णांक baro_pkg;

	पूर्णांक asic_code;
	पूर्णांक phy_debug_mode;
	पूर्णांक hw_bypass_sd;
	पूर्णांक sdio_func_exist;
	पूर्णांक aux_pwr_exist;
	u8 ms_घातer_class_en;

	पूर्णांक mspro_क्रमmatter_enable;

	पूर्णांक remote_wakeup_en;

	पूर्णांक ignore_sd;
	पूर्णांक use_hw_setting;

	पूर्णांक ss_idle_period;

	पूर्णांक dynamic_aspm;

	पूर्णांक fpga_sd_sdr104_clk;
	पूर्णांक fpga_sd_ddr50_clk;
	पूर्णांक fpga_sd_sdr50_clk;
	पूर्णांक fpga_sd_hs_clk;
	पूर्णांक fpga_mmc_52m_clk;
	पूर्णांक fpga_ms_hg_clk;
	पूर्णांक fpga_ms_4bit_clk;
	पूर्णांक fpga_ms_1bit_clk;

	पूर्णांक asic_sd_sdr104_clk;
	पूर्णांक asic_sd_ddr50_clk;
	पूर्णांक asic_sd_sdr50_clk;
	पूर्णांक asic_sd_hs_clk;
	पूर्णांक asic_mmc_52m_clk;
	पूर्णांक asic_ms_hg_clk;
	पूर्णांक asic_ms_4bit_clk;
	पूर्णांक asic_ms_1bit_clk;

	u8 ssc_depth_sd_sdr104;
	u8 ssc_depth_sd_ddr50;
	u8 ssc_depth_sd_sdr50;
	u8 ssc_depth_sd_hs;
	u8 ssc_depth_mmc_52m;
	u8 ssc_depth_ms_hg;
	u8 ssc_depth_ms_4bit;
	u8 ssc_depth_low_speed;

	u8 card_drive_sel;
	u8 sd30_drive_sel_1v8;
	u8 sd30_drive_sel_3v3;

	u8 sd_400mA_ocp_thd;
	u8 sd_800mA_ocp_thd;
	u8 ms_ocp_thd;

	पूर्णांक ssc_en;
	पूर्णांक msi_en;

	पूर्णांक xd_समयout;
	पूर्णांक sd_समयout;
	पूर्णांक ms_समयout;
	पूर्णांक mspro_समयout;

	पूर्णांक स्वतः_घातer_करोwn;

	पूर्णांक sd_ddr_tx_phase;
	पूर्णांक mmc_ddr_tx_phase;
	पूर्णांक sd_शेष_tx_phase;
	पूर्णांक sd_शेष_rx_phase;

	पूर्णांक pmos_pwr_on_पूर्णांकerval;
	पूर्णांक sd_voltage_चयन_delay;
	पूर्णांक s3_pwr_off_delay;

	पूर्णांक क्रमce_clkreq_0;
	पूर्णांक ft2_fast_mode;

	पूर्णांक करो_delink_beक्रमe_घातer_करोwn;
	पूर्णांक polling_config;
	पूर्णांक sdio_retry_cnt;

	पूर्णांक delink_stage1_step;
	पूर्णांक delink_stage2_step;
	पूर्णांक delink_stage3_step;

	पूर्णांक स्वतः_delink_in_L1;
	पूर्णांक hp_watch_bios_hotplug;
	पूर्णांक support_ms_8bit;

	u8 blink_led;
	u8 phy_voltage;
	u8 max_payload;

	u32 sd_speed_prior;
	u32 sd_current_prior;
	u32 sd_ctl;
पूर्ण;

अटल अंतरभूत काष्ठा device *rtsx_dev(स्थिर काष्ठा rtsx_chip *chip)
अणु
	वापस &chip->rtsx->pci->dev;
पूर्ण

#घोषणा rtsx_set_stat(chip, stat)				\
करो अणु								\
	अगर ((stat) != RTSX_STAT_IDLE) अणु				\
		(chip)->idle_counter = 0;			\
	पूर्ण							\
	(chip)->rtsx_stat = (क्रमागत RTSX_STAT)(stat);		\
पूर्ण जबतक (0)
#घोषणा rtsx_get_stat(chip)		((chip)->rtsx_stat)
#घोषणा rtsx_chk_stat(chip, stat)	((chip)->rtsx_stat == (stat))

#घोषणा RTSX_SET_DELINK(chip)	((chip)->rtsx_flag |= 0x01)
#घोषणा RTSX_CLR_DELINK(chip)	((chip)->rtsx_flag &= 0xFE)
#घोषणा RTSX_TST_DELINK(chip)	((chip)->rtsx_flag & 0x01)

#घोषणा CHECK_PID(chip, pid)		((chip)->product_id == (pid))
#घोषणा CHECK_BARO_PKG(chip, pkg)	((chip)->baro_pkg == (pkg))
#घोषणा CHECK_LUN_MODE(chip, mode)	((chip)->lun_mode == (mode))

/* Power करोwn control */
#घोषणा SSC_PDCTL		0x01
#घोषणा OC_PDCTL		0x02

पूर्णांक rtsx_क्रमce_घातer_on(काष्ठा rtsx_chip *chip, u8 ctl);
पूर्णांक rtsx_क्रमce_घातer_करोwn(काष्ठा rtsx_chip *chip, u8 ctl);

व्योम rtsx_enable_card_पूर्णांक(काष्ठा rtsx_chip *chip);
व्योम rtsx_enable_bus_पूर्णांक(काष्ठा rtsx_chip *chip);
व्योम rtsx_disable_bus_पूर्णांक(काष्ठा rtsx_chip *chip);
पूर्णांक rtsx_reset_chip(काष्ठा rtsx_chip *chip);
पूर्णांक rtsx_init_chip(काष्ठा rtsx_chip *chip);
व्योम rtsx_release_chip(काष्ठा rtsx_chip *chip);
व्योम rtsx_polling_func(काष्ठा rtsx_chip *chip);
व्योम rtsx_stop_cmd(काष्ठा rtsx_chip *chip, पूर्णांक card);
पूर्णांक rtsx_ग_लिखो_रेजिस्टर(काष्ठा rtsx_chip *chip, u16 addr, u8 mask, u8 data);
पूर्णांक rtsx_पढ़ो_रेजिस्टर(काष्ठा rtsx_chip *chip, u16 addr, u8 *data);
पूर्णांक rtsx_ग_लिखो_cfg_dw(काष्ठा rtsx_chip *chip,
		      u8 func_no, u16 addr, u32 mask, u32 val);
पूर्णांक rtsx_पढ़ो_cfg_dw(काष्ठा rtsx_chip *chip, u8 func_no, u16 addr, u32 *val);
पूर्णांक rtsx_ग_लिखो_cfg_seq(काष्ठा rtsx_chip *chip,
		       u8 func, u16 addr, u8 *buf, पूर्णांक len);
पूर्णांक rtsx_पढ़ो_cfg_seq(काष्ठा rtsx_chip *chip,
		      u8 func, u16 addr, u8 *buf, पूर्णांक len);
पूर्णांक rtsx_ग_लिखो_phy_रेजिस्टर(काष्ठा rtsx_chip *chip, u8 addr, u16 val);
पूर्णांक rtsx_पढ़ो_phy_रेजिस्टर(काष्ठा rtsx_chip *chip, u8 addr, u16 *val);
पूर्णांक rtsx_पढ़ो_efuse(काष्ठा rtsx_chip *chip, u8 addr, u8 *val);
पूर्णांक rtsx_ग_लिखो_efuse(काष्ठा rtsx_chip *chip, u8 addr, u8 val);
पूर्णांक rtsx_clr_phy_reg_bit(काष्ठा rtsx_chip *chip, u8 reg, u8 bit);
पूर्णांक rtsx_set_phy_reg_bit(काष्ठा rtsx_chip *chip, u8 reg, u8 bit);
व्योम rtsx_enter_ss(काष्ठा rtsx_chip *chip);
व्योम rtsx_निकास_ss(काष्ठा rtsx_chip *chip);
पूर्णांक rtsx_pre_handle_पूर्णांकerrupt(काष्ठा rtsx_chip *chip);
व्योम rtsx_enter_L1(काष्ठा rtsx_chip *chip);
व्योम rtsx_निकास_L1(काष्ठा rtsx_chip *chip);
व्योम rtsx_करो_beक्रमe_घातer_करोwn(काष्ठा rtsx_chip *chip, पूर्णांक pm_stat);
व्योम rtsx_enable_aspm(काष्ठा rtsx_chip *chip);
व्योम rtsx_disable_aspm(काष्ठा rtsx_chip *chip);
पूर्णांक rtsx_पढ़ो_ppbuf(काष्ठा rtsx_chip *chip, u8 *buf, पूर्णांक buf_len);
पूर्णांक rtsx_ग_लिखो_ppbuf(काष्ठा rtsx_chip *chip, u8 *buf, पूर्णांक buf_len);
पूर्णांक rtsx_check_chip_exist(काष्ठा rtsx_chip *chip);

#पूर्ण_अगर  /* __REALTEK_RTSX_CHIP_H */
