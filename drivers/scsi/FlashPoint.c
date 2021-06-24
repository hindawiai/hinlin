<शैली गुरु>
/*

  FlashPoपूर्णांक.c -- FlashPoपूर्णांक SCCB Manager क्रम Linux

  This file contains the FlashPoपूर्णांक SCCB Manager from BusLogic's FlashPoपूर्णांक
  Driver Developer's Kit, with minor modअगरications by Leonard N. Zubkoff क्रम
  Linux compatibility.  It was provided by BusLogic in the क्रमm of 16 separate
  source files, which would have unnecessarily cluttered the scsi directory, so
  the inभागidual files have been combined पूर्णांकo this single file.

  Copyright 1995-1996 by Mylex Corporation.  All Rights Reserved

  This file is available under both the GNU General Public License
  and a BSD-style copyright; see LICENSE.FlashPoपूर्णांक क्रम details.

*/


#अगर_घोषित CONFIG_SCSI_FLASHPOINT

#घोषणा MAX_CARDS	8
#अघोषित BUSTYPE_PCI

#घोषणा CRCMASK	0xA001

#घोषणा FAILURE         0xFFFFFFFFL

काष्ठा sccb;
प्रकार व्योम (*CALL_BK_FN) (काष्ठा sccb *);

काष्ठा sccb_mgr_info अणु
	u32 si_baseaddr;
	अचिन्हित अक्षर si_present;
	अचिन्हित अक्षर si_पूर्णांकvect;
	अचिन्हित अक्षर si_id;
	अचिन्हित अक्षर si_lun;
	u16 si_fw_revision;
	u16 si_per_targ_init_sync;
	u16 si_per_targ_fast_nego;
	u16 si_per_targ_ultra_nego;
	u16 si_per_targ_no_disc;
	u16 si_per_targ_wide_nego;
	u16 si_flags;
	अचिन्हित अक्षर si_card_family;
	अचिन्हित अक्षर si_bustype;
	अचिन्हित अक्षर si_card_model[3];
	अचिन्हित अक्षर si_relative_cardnum;
	अचिन्हित अक्षर si_reserved[4];
	u32 si_OS_reserved;
	अचिन्हित अक्षर si_XlatInfo[4];
	u32 si_reserved2[5];
	u32 si_secondary_range;
पूर्ण;

#घोषणा SCSI_PARITY_ENA		  0x0001
#घोषणा LOW_BYTE_TERM		  0x0010
#घोषणा HIGH_BYTE_TERM		  0x0020
#घोषणा BUSTYPE_PCI	  0x3

#घोषणा SUPPORT_16TAR_32LUN	  0x0002
#घोषणा SOFT_RESET		  0x0004
#घोषणा EXTENDED_TRANSLATION	  0x0008
#घोषणा POST_ALL_UNDERRRUNS	  0x0040
#घोषणा FLAG_SCAM_ENABLED	  0x0080
#घोषणा FLAG_SCAM_LEVEL2	  0x0100

#घोषणा HARPOON_FAMILY        0x02

/* SCCB काष्ठा used क्रम both SCCB and UCB manager compiles! 
 * The UCB Manager treats the SCCB as it's 'native hardware structure' 
 */

/*#आशय pack(1)*/
काष्ठा sccb अणु
	अचिन्हित अक्षर OperationCode;
	अचिन्हित अक्षर ControlByte;
	अचिन्हित अक्षर CdbLength;
	अचिन्हित अक्षर RequestSenseLength;
	u32 DataLength;
	व्योम *DataPoपूर्णांकer;
	अचिन्हित अक्षर CcbRes[2];
	अचिन्हित अक्षर HostStatus;
	अचिन्हित अक्षर TargetStatus;
	अचिन्हित अक्षर TargID;
	अचिन्हित अक्षर Lun;
	अचिन्हित अक्षर Cdb[12];
	अचिन्हित अक्षर CcbRes1;
	अचिन्हित अक्षर Reserved1;
	u32 Reserved2;
	u32 SensePoपूर्णांकer;

	CALL_BK_FN SccbCallback;	/* VOID (*SccbCallback)(); */
	u32 SccbIOPort;			/* Identअगरies board base port */
	अचिन्हित अक्षर SccbStatus;
	अचिन्हित अक्षर SCCBRes2;
	u16 SccbOSFlags;

	u32 Sccb_XferCnt;	/* actual transfer count */
	u32 Sccb_ATC;
	u32 SccbVirtDataPtr;	/* भव addr क्रम OS/2 */
	u32 Sccb_res1;
	u16 Sccb_MGRFlags;
	u16 Sccb_sgseg;
	अचिन्हित अक्षर Sccb_scsimsg;	/* identअगरy msg क्रम selection */
	अचिन्हित अक्षर Sccb_tag;
	अचिन्हित अक्षर Sccb_scsistat;
	अचिन्हित अक्षर Sccb_idmsg;	/* image of last msg in */
	काष्ठा sccb *Sccb_क्रमwardlink;
	काष्ठा sccb *Sccb_backlink;
	u32 Sccb_savedATC;
	अचिन्हित अक्षर Save_Cdb[6];
	अचिन्हित अक्षर Save_CdbLen;
	अचिन्हित अक्षर Sccb_XferState;
	u32 Sccb_SGoffset;
पूर्ण;

#आशय pack()

#घोषणा SCATTER_GATHER_COMMAND    0x02
#घोषणा RESIDUAL_COMMAND          0x03
#घोषणा RESIDUAL_SG_COMMAND       0x04
#घोषणा RESET_COMMAND             0x81

#घोषणा F_USE_CMD_Q              0x20	/*Inidcates TAGGED command. */
#घोषणा TAG_TYPE_MASK            0xC0	/*Type of tag msg to send. */
#घोषणा SCCB_DATA_XFER_OUT       0x10	/* Write */
#घोषणा SCCB_DATA_XFER_IN        0x08	/* Read */

#घोषणा NO_AUTO_REQUEST_SENSE    0x01	/* No Request Sense Buffer */

#घोषणा BUS_FREE_ST     0
#घोषणा SELECT_ST       1
#घोषणा SELECT_BDR_ST   2	/* Select w\ Bus Device Reset */
#घोषणा SELECT_SN_ST    3	/* Select w\ Sync Nego */
#घोषणा SELECT_WN_ST    4	/* Select w\ Wide Data Nego */
#घोषणा SELECT_Q_ST     5	/* Select w\ Tagged Q'ing */
#घोषणा COMMAND_ST      6
#घोषणा DATA_OUT_ST     7
#घोषणा DATA_IN_ST      8
#घोषणा DISCONNECT_ST   9
#घोषणा ABORT_ST        11

#घोषणा F_HOST_XFER_सूची                0x01
#घोषणा F_ALL_XFERRED                  0x02
#घोषणा F_SG_XFER                      0x04
#घोषणा F_AUTO_SENSE                   0x08
#घोषणा F_ODD_BALL_CNT                 0x10
#घोषणा F_NO_DATA_YET                  0x80

#घोषणा F_STATUSLOADED                 0x01
#घोषणा F_DEV_SELECTED                 0x04

#घोषणा SCCB_COMPLETE               0x00	/* SCCB completed without error */
#घोषणा SCCB_DATA_UNDER_RUN         0x0C
#घोषणा SCCB_SELECTION_TIMEOUT      0x11	/* Set SCSI selection समयd out */
#घोषणा SCCB_DATA_OVER_RUN          0x12
#घोषणा SCCB_PHASE_SEQUENCE_FAIL    0x14	/* Target bus phase sequence failure */

#घोषणा SCCB_GROSS_FW_ERR           0x27	/* Major problem! */
#घोषणा SCCB_BM_ERR                 0x30	/* BusMaster error. */
#घोषणा SCCB_PARITY_ERR             0x34	/* SCSI parity error */

#घोषणा SCCB_IN_PROCESS            0x00
#घोषणा SCCB_SUCCESS               0x01
#घोषणा SCCB_ABORT                 0x02
#घोषणा SCCB_ERROR                 0x04

#घोषणा  ORION_FW_REV      3110

#घोषणा QUEUE_DEPTH     254+1	/*1 क्रम Normal disconnect 32 क्रम Q'ing. */

#घोषणा	MAX_MB_CARDS	4	/* Max. no of cards suppoerted on Mother Board */

#घोषणा MAX_SCSI_TAR    16
#घोषणा MAX_LUN         32
#घोषणा LUN_MASK			0x1f

#घोषणा SG_BUF_CNT      16	/*Number of prefetched elements. */

#घोषणा SG_ELEMENT_SIZE 8	/*Eight byte per element. */

#घोषणा RD_HARPOON(ioport)          inb((u32)ioport)
#घोषणा RDW_HARPOON(ioport)         inw((u32)ioport)
#घोषणा RD_HARP32(ioport,offset,data) (data = inl((u32)(ioport + offset)))
#घोषणा WR_HARPOON(ioport,val)      outb((u8) val, (u32)ioport)
#घोषणा WRW_HARPOON(ioport,val)       outw((u16)val, (u32)ioport)
#घोषणा WR_HARP32(ioport,offset,data)  outl(data, (u32)(ioport + offset))

#घोषणा  TAR_SYNC_MASK     (BIT(7)+BIT(6))
#घोषणा  SYNC_TRYING               BIT(6)
#घोषणा  SYNC_SUPPORTED    (BIT(7)+BIT(6))

#घोषणा  TAR_WIDE_MASK     (BIT(5)+BIT(4))
#घोषणा  WIDE_ENABLED              BIT(4)
#घोषणा  WIDE_NEGOCIATED   BIT(5)

#घोषणा  TAR_TAG_Q_MASK    (BIT(3)+BIT(2))
#घोषणा  TAG_Q_TRYING              BIT(2)
#घोषणा  TAG_Q_REJECT      BIT(3)

#घोषणा  TAR_ALLOW_DISC    BIT(0)

#घोषणा  EE_SYNC_MASK      (BIT(0)+BIT(1))
#घोषणा  EE_SYNC_5MB       BIT(0)
#घोषणा  EE_SYNC_10MB      BIT(1)
#घोषणा  EE_SYNC_20MB      (BIT(0)+BIT(1))

#घोषणा  EE_WIDE_SCSI      BIT(7)

काष्ठा sccb_mgr_tar_info अणु

	काष्ठा sccb *TarSelQ_Head;
	काष्ठा sccb *TarSelQ_Tail;
	अचिन्हित अक्षर TarLUN_CA;	/*Contingent Allgiance */
	अचिन्हित अक्षर TarTagQ_Cnt;
	अचिन्हित अक्षर TarSelQ_Cnt;
	अचिन्हित अक्षर TarStatus;
	अचिन्हित अक्षर TarEEValue;
	अचिन्हित अक्षर TarSyncCtrl;
	अचिन्हित अक्षर TarReserved[2];	/* क्रम alignment */
	अचिन्हित अक्षर LunDiscQ_Idx[MAX_LUN];
	अचिन्हित अक्षर TarLUNBusy[MAX_LUN];
पूर्ण;

काष्ठा nvram_info अणु
	अचिन्हित अक्षर niModel;		/* Model No. of card */
	अचिन्हित अक्षर niCardNo;		/* Card no. */
	u32 niBaseAddr;			/* Port Address of card */
	अचिन्हित अक्षर niSysConf;	/* Adapter Configuration byte -
					   Byte 16 of eeprom map */
	अचिन्हित अक्षर niScsiConf;	/* SCSI Configuration byte -
					   Byte 17 of eeprom map */
	अचिन्हित अक्षर niScamConf;	/* SCAM Configuration byte -
					   Byte 20 of eeprom map */
	अचिन्हित अक्षर niAdapId;		/* Host Adapter ID -
					   Byte 24 of eerpom map */
	अचिन्हित अक्षर niSyncTbl[MAX_SCSI_TAR / 2];	/* Sync/Wide byte
							   of tarमाला_लो */
	अचिन्हित अक्षर niScamTbl[MAX_SCSI_TAR][4];	/* Compressed Scam name
							   string of Tarमाला_लो */
पूर्ण;

#घोषणा	MODEL_LT		1
#घोषणा	MODEL_DL		2
#घोषणा	MODEL_LW		3
#घोषणा	MODEL_DW		4

काष्ठा sccb_card अणु
	काष्ठा sccb *currentSCCB;
	काष्ठा sccb_mgr_info *cardInfo;

	u32 ioPort;

	अचिन्हित लघु cmdCounter;
	अचिन्हित अक्षर discQCount;
	अचिन्हित अक्षर tagQ_Lst;
	अचिन्हित अक्षर cardIndex;
	अचिन्हित अक्षर scanIndex;
	अचिन्हित अक्षर globalFlags;
	अचिन्हित अक्षर ourId;
	काष्ठा nvram_info *pNvRamInfo;
	काष्ठा sccb *discQ_Tbl[QUEUE_DEPTH];

पूर्ण;

#घोषणा F_TAG_STARTED		0x01
#घोषणा F_CONLUN_IO			0x02
#घोषणा F_DO_RENEGO			0x04
#घोषणा F_NO_FILTER			0x08
#घोषणा F_GREEN_PC			0x10
#घोषणा F_HOST_XFER_ACT		0x20
#घोषणा F_NEW_SCCB_CMD		0x40
#घोषणा F_UPDATE_EEPROM		0x80

#घोषणा  ID_STRING_LENGTH  32
#घोषणा  TYPE_CODE0        0x63	/*Level2 Mstr (bits 7-6),  */

#घोषणा  SLV_TYPE_CODE0    0xA3	/*Priority Bit set (bits 7-6),  */

#घोषणा  ASSIGN_ID   0x00
#घोषणा  SET_P_FLAG  0x01
#घोषणा  CFG_CMPLT   0x03
#घोषणा  DOM_MSTR    0x0F
#घोषणा  SYNC_PTRN   0x1F

#घोषणा  ID_0_7      0x18
#घोषणा  ID_8_F      0x11
#घोषणा  MISC_CODE   0x14
#घोषणा  CLR_P_FLAG  0x18

#घोषणा  INIT_SELTD  0x01
#घोषणा  LEVEL2_TAR  0x02

क्रमागत scam_id_st अणु ID0, ID1, ID2, ID3, ID4, ID5, ID6, ID7, ID8, ID9, ID10, ID11,
	    ID12,
	ID13, ID14, ID15, ID_UNUSED, ID_UNASSIGNED, ID_ASSIGNED, LEGACY,
	CLR_PRIORITY, NO_ID_AVAIL
पूर्ण;

प्रकार काष्ठा SCCBscam_info अणु

	अचिन्हित अक्षर id_string[ID_STRING_LENGTH];
	क्रमागत scam_id_st state;

पूर्ण SCCBSCAM_INFO;

#घोषणा  SCSI_REQUEST_SENSE      0x03
#घोषणा  SCSI_READ               0x08
#घोषणा  SCSI_WRITE              0x0A
#घोषणा  SCSI_START_STOP_UNIT    0x1B
#घोषणा  SCSI_READ_EXTENDED      0x28
#घोषणा  SCSI_WRITE_EXTENDED     0x2A
#घोषणा  SCSI_WRITE_AND_VERIFY   0x2E

#घोषणा  SSGOOD                  0x00
#घोषणा  SSCHECK                 0x02
#घोषणा  SSQ_FULL                0x28

#घोषणा  SMCMD_COMP              0x00
#घोषणा  SMEXT                   0x01
#घोषणा  SMSAVE_DATA_PTR         0x02
#घोषणा  SMREST_DATA_PTR         0x03
#घोषणा  SMDISC                  0x04
#घोषणा  SMABORT                 0x06
#घोषणा  SMREJECT                0x07
#घोषणा  SMNO_OP                 0x08
#घोषणा  SMPARITY                0x09
#घोषणा  SMDEV_RESET             0x0C
#घोषणा	SMABORT_TAG					0x0D
#घोषणा	SMINIT_RECOVERY			0x0F
#घोषणा	SMREL_RECOVERY				0x10

#घोषणा  SMIDENT                 0x80
#घोषणा  DISC_PRIV               0x40

#घोषणा  SMSYNC                  0x01
#घोषणा  SMWDTR                  0x03
#घोषणा  SM8BIT                  0x00
#घोषणा  SM16BIT                 0x01
#घोषणा  SMIGNORWR               0x23	/* Ignore Wide Residue */

#घोषणा  SIX_BYTE_CMD            0x06
#घोषणा  TWELVE_BYTE_CMD         0x0C

#घोषणा  ASYNC                   0x00
#घोषणा  MAX_OFFSET              0x0F	/* Maxbyteoffset क्रम Sync Xfers */

#घोषणा  EEPROM_WD_CNT     256

#घोषणा  EEPROM_CHECK_SUM  0
#घोषणा  FW_SIGNATURE      2
#घोषणा  MODEL_NUMB_0      4
#घोषणा  MODEL_NUMB_2      6
#घोषणा  MODEL_NUMB_4      8
#घोषणा  SYSTEM_CONFIG     16
#घोषणा  SCSI_CONFIG       17
#घोषणा  BIOS_CONFIG       18
#घोषणा  SCAM_CONFIG       20
#घोषणा  ADAPTER_SCSI_ID   24

#घोषणा  IGNORE_B_SCAN     32
#घोषणा  SEND_START_ENA    34
#घोषणा  DEVICE_ENABLE     36

#घोषणा  SYNC_RATE_TBL     38
#घोषणा  SYNC_RATE_TBL01   38
#घोषणा  SYNC_RATE_TBL23   40
#घोषणा  SYNC_RATE_TBL45   42
#घोषणा  SYNC_RATE_TBL67   44
#घोषणा  SYNC_RATE_TBL89   46
#घोषणा  SYNC_RATE_TBLab   48
#घोषणा  SYNC_RATE_TBLcd   50
#घोषणा  SYNC_RATE_TBLef   52

#घोषणा  EE_SCAMBASE      256

#घोषणा  SCAM_ENABLED   BIT(2)
#घोषणा  SCAM_LEVEL2    BIT(3)

#घोषणा	RENEGO_ENA		BIT(10)
#घोषणा	CONNIO_ENA		BIT(11)
#घोषणा  GREEN_PC_ENA   BIT(12)

#घोषणा  AUTO_RATE_00   00
#घोषणा  AUTO_RATE_05   01
#घोषणा  AUTO_RATE_10   02
#घोषणा  AUTO_RATE_20   03

#घोषणा  WIDE_NEGO_BIT     BIT(7)
#घोषणा  DISC_ENABLE_BIT   BIT(6)

#घोषणा  hp_venकरोr_id_0       0x00	/* LSB */
#घोषणा  ORION_VEND_0   0x4B

#घोषणा  hp_venकरोr_id_1       0x01	/* MSB */
#घोषणा  ORION_VEND_1   0x10

#घोषणा  hp_device_id_0       0x02	/* LSB */
#घोषणा  ORION_DEV_0    0x30

#घोषणा  hp_device_id_1       0x03	/* MSB */
#घोषणा  ORION_DEV_1    0x81

	/* Sub Venकरोr ID and Sub Device ID only available in
	   Harpoon Version 2 and higher */

#घोषणा  hp_sub_device_id_0   0x06	/* LSB */

#घोषणा  hp_semaphore         0x0C
#घोषणा SCCB_MGR_ACTIVE    BIT(0)
#घोषणा TICKLE_ME          BIT(1)
#घोषणा SCCB_MGR_PRESENT   BIT(3)
#घोषणा BIOS_IN_USE        BIT(4)

#घोषणा  hp_sys_ctrl          0x0F

#घोषणा  STOP_CLK          BIT(0)	/*Turn off BusMaster Clock */
#घोषणा  DRVR_RST          BIT(1)	/*Firmware Reset to 80C15 chip */
#घोषणा  HALT_MACH         BIT(3)	/*Halt State Machine      */
#घोषणा  HARD_ABORT        BIT(4)	/*Hard Abort              */

#घोषणा  hp_host_blk_cnt      0x13

#घोषणा  XFER_BLK64        0x06	/*     1 1 0 64 byte per block */

#घोषणा  BM_THRESHOLD      0x40	/* PCI mode can only xfer 16 bytes */

#घोषणा  hp_पूर्णांक_mask          0x17

#घोषणा  INT_CMD_COMPL     BIT(0)	/* DMA command complete   */
#घोषणा  INT_EXT_STATUS    BIT(1)	/* Extended Status Set    */

#घोषणा  hp_xfer_cnt_lo       0x18
#घोषणा  hp_xfer_cnt_hi       0x1A
#घोषणा  hp_xfer_cmd          0x1B

#घोषणा  XFER_HOST_DMA     0x00	/*     0 0 0 Transfer Host -> DMA */
#घोषणा  XFER_DMA_HOST     0x01	/*     0 0 1 Transfer DMA  -> Host */

#घोषणा  XFER_HOST_AUTO    0x00	/*     0 0 Auto Transfer Size   */

#घोषणा  XFER_DMA_8BIT     0x20	/*     0 1 8 BIT  Transfer Size */

#घोषणा  DISABLE_INT       BIT(7)	/*Do not पूर्णांकerrupt at end of cmd. */

#घोषणा  HOST_WRT_CMD      ((DISABLE_INT + XFER_HOST_DMA + XFER_HOST_AUTO + XFER_DMA_8BIT))
#घोषणा  HOST_RD_CMD       ((DISABLE_INT + XFER_DMA_HOST + XFER_HOST_AUTO + XFER_DMA_8BIT))

#घोषणा  hp_host_addr_lo      0x1C
#घोषणा  hp_host_addr_hmi     0x1E

#घोषणा  hp_ee_ctrl           0x22

#घोषणा  EXT_ARB_ACK       BIT(7)
#घोषणा  SCSI_TERM_ENA_H   BIT(6)	/* SCSI high byte terminator */
#घोषणा  SEE_MS            BIT(5)
#घोषणा  SEE_CS            BIT(3)
#घोषणा  SEE_CLK           BIT(2)
#घोषणा  SEE_DO            BIT(1)
#घोषणा  SEE_DI            BIT(0)

#घोषणा  EE_READ           0x06
#घोषणा  EE_WRITE          0x05
#घोषणा  EWEN              0x04
#घोषणा  EWEN_ADDR         0x03C0
#घोषणा  EWDS              0x04
#घोषणा  EWDS_ADDR         0x0000

#घोषणा  hp_bm_ctrl           0x26

#घोषणा  SCSI_TERM_ENA_L   BIT(0)	/*Enable/Disable बाह्यal terminators */
#घोषणा  FLUSH_XFER_CNTR   BIT(1)	/*Flush transfer counter */
#घोषणा  FORCE1_XFER       BIT(5)	/*Always xfer one byte in byte mode */
#घोषणा  FAST_SINGLE       BIT(6)	/*?? */

#घोषणा  BMCTRL_DEFAULT    (FORCE1_XFER|FAST_SINGLE|SCSI_TERM_ENA_L)

#घोषणा  hp_sg_addr           0x28
#घोषणा  hp_page_ctrl         0x29

#घोषणा  SCATTER_EN        BIT(0)
#घोषणा  SGRAM_ARAM        BIT(1)
#घोषणा  G_INT_DISABLE     BIT(3)	/* Enable/Disable all Interrupts */
#घोषणा  NARROW_SCSI_CARD  BIT(4)	/* NARROW/WIDE SCSI config pin */

#घोषणा  hp_pci_stat_cfg      0x2D

#घोषणा  REC_MASTER_ABORT  BIT(5)	/*received Master पात */

#घोषणा  hp_rev_num           0x33

#घोषणा  hp_stack_data        0x34
#घोषणा  hp_stack_addr        0x35

#घोषणा  hp_ext_status        0x36

#घोषणा  BM_FORCE_OFF      BIT(0)	/*Bus Master is क्रमced to get off */
#घोषणा  PCI_TGT_ABORT     BIT(0)	/*PCI bus master transaction पातed */
#घोषणा  PCI_DEV_TMOUT     BIT(1)	/*PCI Device Time out */
#घोषणा  CMD_ABORTED       BIT(4)	/*Command पातed */
#घोषणा  BM_PARITY_ERR     BIT(5)	/*parity error on data received   */
#घोषणा  PIO_OVERRUN       BIT(6)	/*Slave data overrun */
#घोषणा  BM_CMD_BUSY       BIT(7)	/*Bus master transfer command busy */
#घोषणा  BAD_EXT_STATUS    (BM_FORCE_OFF | PCI_DEV_TMOUT | CMD_ABORTED | \
                                  BM_PARITY_ERR | PIO_OVERRUN)

#घोषणा  hp_पूर्णांक_status        0x37

#घोषणा  EXT_STATUS_ON     BIT(1)	/*Extended status is valid */
#घोषणा  SCSI_INTERRUPT    BIT(2)	/*Global indication of a SCSI पूर्णांक. */
#घोषणा  INT_ASSERTED      BIT(5)	/* */

#घोषणा  hp_fअगरo_cnt          0x38

#घोषणा  hp_पूर्णांकena		 0x40

#घोषणा  RESET		 BIT(7)
#घोषणा  PROG_HLT		 BIT(6)
#घोषणा  PARITY		 BIT(5)
#घोषणा  FIFO		 BIT(4)
#घोषणा  SEL		 BIT(3)
#घोषणा  SCAM_SEL		 BIT(2)
#घोषणा  RSEL		 BIT(1)
#घोषणा  TIMEOUT		 BIT(0)
#घोषणा  BUS_FREE		 BIT(15)
#घोषणा  XFER_CNT_0	 BIT(14)
#घोषणा  PHASE		 BIT(13)
#घोषणा  IUNKWN		 BIT(12)
#घोषणा  ICMD_COMP	 BIT(11)
#घोषणा  ITICKLE		 BIT(10)
#घोषणा  IDO_STRT		 BIT(9)
#घोषणा  ITAR_DISC	 BIT(8)
#घोषणा  AUTO_INT		 (BIT(12)+BIT(11)+BIT(10)+BIT(9)+BIT(8))
#घोषणा  CLR_ALL_INT	 0xFFFF
#घोषणा  CLR_ALL_INT_1	 0xFF00

#घोषणा  hp_पूर्णांकstat		 0x42

#घोषणा  hp_scsisig           0x44

#घोषणा  SCSI_SEL          BIT(7)
#घोषणा  SCSI_BSY          BIT(6)
#घोषणा  SCSI_REQ          BIT(5)
#घोषणा  SCSI_ACK          BIT(4)
#घोषणा  SCSI_ATN          BIT(3)
#घोषणा  SCSI_CD           BIT(2)
#घोषणा  SCSI_MSG          BIT(1)
#घोषणा  SCSI_IOBIT        BIT(0)

#घोषणा  S_SCSI_PHZ        (BIT(2)+BIT(1)+BIT(0))
#घोषणा  S_MSGO_PH         (BIT(2)+BIT(1)       )
#घोषणा  S_MSGI_PH         (BIT(2)+BIT(1)+BIT(0))
#घोषणा  S_DATAI_PH        (              BIT(0))
#घोषणा  S_DATAO_PH        0x00
#घोषणा  S_ILL_PH          (       BIT(1)       )

#घोषणा  hp_scsictrl_0        0x45

#घोषणा  SEL_TAR           BIT(6)
#घोषणा  ENA_ATN           BIT(4)
#घोषणा  ENA_RESEL         BIT(2)
#घोषणा  SCSI_RST          BIT(1)
#घोषणा  ENA_SCAM_SEL      BIT(0)

#घोषणा  hp_portctrl_0        0x46

#घोषणा  SCSI_PORT         BIT(7)
#घोषणा  SCSI_INBIT        BIT(6)
#घोषणा  DMA_PORT          BIT(5)
#घोषणा  DMA_RD            BIT(4)
#घोषणा  HOST_PORT         BIT(3)
#घोषणा  HOST_WRT          BIT(2)
#घोषणा  SCSI_BUS_EN       BIT(1)
#घोषणा  START_TO          BIT(0)

#घोषणा  hp_scsireset         0x47

#घोषणा  SCSI_INI          BIT(6)
#घोषणा  SCAM_EN           BIT(5)
#घोषणा  DMA_RESET         BIT(3)
#घोषणा  HPSCSI_RESET      BIT(2)
#घोषणा  PROG_RESET        BIT(1)
#घोषणा  FIFO_CLR          BIT(0)

#घोषणा  hp_xfercnt_0         0x48
#घोषणा  hp_xfercnt_2         0x4A

#घोषणा  hp_fअगरodata_0        0x4C
#घोषणा  hp_addstat           0x4E

#घोषणा  SCAM_TIMER        BIT(7)
#घोषणा  SCSI_MODE8        BIT(3)
#घोषणा  SCSI_PAR_ERR      BIT(0)

#घोषणा  hp_prgmcnt_0         0x4F

#घोषणा  hp_selfid_0          0x50
#घोषणा  hp_selfid_1          0x51
#घोषणा  hp_arb_id            0x52

#घोषणा  hp_select_id         0x53

#घोषणा  hp_synctarg_base     0x54
#घोषणा  hp_synctarg_12       0x54
#घोषणा  hp_synctarg_13       0x55
#घोषणा  hp_synctarg_14       0x56
#घोषणा  hp_synctarg_15       0x57

#घोषणा  hp_synctarg_8        0x58
#घोषणा  hp_synctarg_9        0x59
#घोषणा  hp_synctarg_10       0x5A
#घोषणा  hp_synctarg_11       0x5B

#घोषणा  hp_synctarg_4        0x5C
#घोषणा  hp_synctarg_5        0x5D
#घोषणा  hp_synctarg_6        0x5E
#घोषणा  hp_synctarg_7        0x5F

#घोषणा  hp_synctarg_0        0x60
#घोषणा  hp_synctarg_1        0x61
#घोषणा  hp_synctarg_2        0x62
#घोषणा  hp_synctarg_3        0x63

#घोषणा  NARROW_SCSI       BIT(4)
#घोषणा  DEFAULT_OFFSET    0x0F

#घोषणा  hp_स्वतःstart_0       0x64
#घोषणा  hp_स्वतःstart_1       0x65
#घोषणा  hp_स्वतःstart_3       0x67

#घोषणा  AUTO_IMMED    BIT(5)
#घोषणा  SELECT   BIT(6)
#घोषणा  END_DATA (BIT(7)+BIT(6))

#घोषणा  hp_gp_reg_0          0x68
#घोषणा  hp_gp_reg_1          0x69
#घोषणा  hp_gp_reg_3          0x6B

#घोषणा  hp_selसमयout        0x6C

#घोषणा  TO_4ms            0x67	/* 3.9959ms */

#घोषणा  TO_5ms            0x03	/* 4.9152ms */
#घोषणा  TO_10ms           0x07	/* 11.xxxms */
#घोषणा  TO_250ms          0x99	/* 250.68ms */
#घोषणा  TO_290ms          0xB1	/* 289.99ms */

#घोषणा  hp_clkctrl_0         0x6D

#घोषणा  PWR_DWN           BIT(6)
#घोषणा  ACTdeनिश्चित       BIT(4)
#घोषणा  CLK_40MHZ         (BIT(1) + BIT(0))

#घोषणा  CLKCTRL_DEFAULT   (ACTdeनिश्चित | CLK_40MHZ)

#घोषणा  hp_fअगरoपढ़ो          0x6E
#घोषणा  hp_fअगरoग_लिखो         0x6F

#घोषणा  hp_offsetctr         0x70
#घोषणा  hp_xferstat          0x71

#घोषणा  FIFO_EMPTY        BIT(6)

#घोषणा  hp_portctrl_1        0x72

#घोषणा  CHK_SCSI_P        BIT(3)
#घोषणा  HOST_MODE8        BIT(0)

#घोषणा  hp_xfer_pad          0x73

#घोषणा  ID_UNLOCK         BIT(3)

#घोषणा  hp_scsidata_0        0x74
#घोषणा  hp_scsidata_1        0x75

#घोषणा  hp_aramBase          0x80
#घोषणा  BIOS_DATA_OFFSET     0x60
#घोषणा  BIOS_RELATIVE_CARD   0x64

#घोषणा  AR3      (BIT(9) + BIT(8))
#घोषणा  SDATA    BIT(10)

#घोषणा  CRD_OP   BIT(11)	/* Cmp Reg. w/ Data */

#घोषणा  CRR_OP   BIT(12)	/* Cmp Reg. w. Reg. */

#घोषणा  CPE_OP   (BIT(14)+BIT(11))	/* Cmp SCSI phs & Branch EQ */

#घोषणा  CPN_OP   (BIT(14)+BIT(12))	/* Cmp SCSI phs & Branch NOT EQ */

#घोषणा  ADATA_OUT   0x00
#घोषणा  ADATA_IN    BIT(8)
#घोषणा  ACOMMAND    BIT(10)
#घोषणा  ASTATUS     (BIT(10)+BIT(8))
#घोषणा  AMSG_OUT    (BIT(10)+BIT(9))
#घोषणा  AMSG_IN     (BIT(10)+BIT(9)+BIT(8))

#घोषणा  BRH_OP   BIT(13)	/* Branch */

#घोषणा  ALWAYS   0x00
#घोषणा  EQUAL    BIT(8)
#घोषणा  NOT_EQ   BIT(9)

#घोषणा  TCB_OP   (BIT(13)+BIT(11))	/* Test condition & branch */

#घोषणा  FIFO_0      BIT(10)

#घोषणा  MPM_OP   BIT(15)	/* Match phase and move data */

#घोषणा  MRR_OP   BIT(14)	/* Move DReg. to Reg. */

#घोषणा  S_IDREG  (BIT(2)+BIT(1)+BIT(0))

#घोषणा  D_AR0    0x00
#घोषणा  D_AR1    BIT(0)
#घोषणा  D_BUCKET (BIT(2) + BIT(1) + BIT(0))

#घोषणा  RAT_OP      (BIT(14)+BIT(13)+BIT(11))

#घोषणा  SSI_OP      (BIT(15)+BIT(11))

#घोषणा  SSI_ITAR_DISC	(ITAR_DISC >> 8)
#घोषणा  SSI_IDO_STRT	(IDO_STRT >> 8)

#घोषणा  SSI_ICMD_COMP	(ICMD_COMP >> 8)
#घोषणा  SSI_ITICKLE	(ITICKLE >> 8)

#घोषणा  SSI_IUNKWN	(IUNKWN >> 8)
#घोषणा  SSI_INO_CC	(IUNKWN >> 8)
#घोषणा  SSI_IRFAIL	(IUNKWN >> 8)

#घोषणा  NP    0x10		/*Next Phase */
#घोषणा  NTCMD 0x02		/*Non- Tagged Command start */
#घोषणा  CMDPZ 0x04		/*Command phase */
#घोषणा  DINT  0x12		/*Data Out/In पूर्णांकerrupt */
#घोषणा  DI    0x13		/*Data Out */
#घोषणा  DC    0x19		/*Disconnect Message */
#घोषणा  ST    0x1D		/*Status Phase */
#घोषणा  UNKNWN 0x24		/*Unknown bus action */
#घोषणा  CC    0x25		/*Command Completion failure */
#घोषणा  TICK  0x26		/*New target reselected us. */
#घोषणा  SELCHK 0x28		/*Select & Check SCSI ID latch reg */

#घोषणा  ID_MSG_STRT    hp_aramBase + 0x00
#घोषणा  NON_TAG_ID_MSG hp_aramBase + 0x06
#घोषणा  CMD_STRT       hp_aramBase + 0x08
#घोषणा  SYNC_MSGS      hp_aramBase + 0x08

#घोषणा  TAG_STRT          0x00
#घोषणा  DISCONNECT_START  0x10/2
#घोषणा  END_DATA_START    0x14/2
#घोषणा  CMD_ONLY_STRT     CMDPZ/2
#घोषणा  SELCHK_STRT     SELCHK/2

#घोषणा GET_XFER_CNT(port, xfercnt) अणुRD_HARP32(port,hp_xfercnt_0,xfercnt); xfercnt &= 0xFFFFFF;पूर्ण
/* #घोषणा GET_XFER_CNT(port, xfercnt) (xfercnt = RD_HARPOON(port+hp_xfercnt_2), \
                                 xfercnt <<= 16,\
                                 xfercnt |= RDW_HARPOON((अचिन्हित लघु)(port+hp_xfercnt_0)))
 */
#घोषणा HP_SETUP_ADDR_CNT(port,addr,count) (WRW_HARPOON((port+hp_host_addr_lo), (अचिन्हित लघु)(addr & 0x0000FFFFL)),\
         addr >>= 16,\
         WRW_HARPOON((port+hp_host_addr_hmi), (अचिन्हित लघु)(addr & 0x0000FFFFL)),\
         WR_HARP32(port,hp_xfercnt_0,count),\
         WRW_HARPOON((port+hp_xfer_cnt_lo), (अचिन्हित लघु)(count & 0x0000FFFFL)),\
         count >>= 16,\
         WR_HARPOON(port+hp_xfer_cnt_hi, (count & 0xFF)))

#घोषणा ACCEPT_MSG(port) अणुजबतक(RD_HARPOON(port+hp_scsisig) & SCSI_REQ)अणुपूर्ण\
                          WR_HARPOON(port+hp_scsisig, S_ILL_PH);पूर्ण

#घोषणा ACCEPT_MSG_ATN(port) अणुजबतक(RD_HARPOON(port+hp_scsisig) & SCSI_REQ)अणुपूर्ण\
                          WR_HARPOON(port+hp_scsisig, (S_ILL_PH|SCSI_ATN));पूर्ण

#घोषणा DISABLE_AUTO(port) (WR_HARPOON(port+hp_scsireset, PROG_RESET),\
                        WR_HARPOON(port+hp_scsireset, 0x00))

#घोषणा ARAM_ACCESS(p_port) (WR_HARPOON(p_port+hp_page_ctrl, \
                             (RD_HARPOON(p_port+hp_page_ctrl) | SGRAM_ARAM)))

#घोषणा SGRAM_ACCESS(p_port) (WR_HARPOON(p_port+hp_page_ctrl, \
                             (RD_HARPOON(p_port+hp_page_ctrl) & ~SGRAM_ARAM)))

#घोषणा MDISABLE_INT(p_port) (WR_HARPOON(p_port+hp_page_ctrl, \
                             (RD_HARPOON(p_port+hp_page_ctrl) | G_INT_DISABLE)))

#घोषणा MENABLE_INT(p_port) (WR_HARPOON(p_port+hp_page_ctrl, \
                             (RD_HARPOON(p_port+hp_page_ctrl) & ~G_INT_DISABLE)))

अटल अचिन्हित अक्षर FPT_sisyncn(u32 port, अचिन्हित अक्षर p_card,
				 अचिन्हित अक्षर syncFlag);
अटल व्योम FPT_ssel(u32 port, अचिन्हित अक्षर p_card);
अटल व्योम FPT_sres(u32 port, अचिन्हित अक्षर p_card,
		     काष्ठा sccb_card *pCurrCard);
अटल व्योम FPT_shandem(u32 port, अचिन्हित अक्षर p_card,
			काष्ठा sccb *pCurrSCCB);
अटल व्योम FPT_stsyncn(u32 port, अचिन्हित अक्षर p_card);
अटल व्योम FPT_sisyncr(u32 port, अचिन्हित अक्षर sync_pulse,
			अचिन्हित अक्षर offset);
अटल व्योम FPT_sssyncv(u32 p_port, अचिन्हित अक्षर p_id,
			अचिन्हित अक्षर p_sync_value,
			काष्ठा sccb_mgr_tar_info *currTar_Info);
अटल व्योम FPT_sresb(u32 port, अचिन्हित अक्षर p_card);
अटल व्योम FPT_sxfrp(u32 p_port, अचिन्हित अक्षर p_card);
अटल व्योम FPT_schkdd(u32 port, अचिन्हित अक्षर p_card);
अटल अचिन्हित अक्षर FPT_RdStack(u32 port, अचिन्हित अक्षर index);
अटल व्योम FPT_WrStack(u32 portBase, अचिन्हित अक्षर index,
			अचिन्हित अक्षर data);
अटल अचिन्हित अक्षर FPT_ChkIfChipInitialized(u32 ioPort);

अटल व्योम FPT_SendMsg(u32 port, अचिन्हित अक्षर message);
अटल व्योम FPT_queueFlushTargSccb(अचिन्हित अक्षर p_card, अचिन्हित अक्षर thisTarg,
				   अचिन्हित अक्षर error_code);

अटल व्योम FPT_sinits(काष्ठा sccb *p_sccb, अचिन्हित अक्षर p_card);
अटल व्योम FPT_RNVRamData(काष्ठा nvram_info *pNvRamInfo);

अटल अचिन्हित अक्षर FPT_siwidn(u32 port, अचिन्हित अक्षर p_card);
अटल व्योम FPT_stwidn(u32 port, अचिन्हित अक्षर p_card);
अटल व्योम FPT_siwidr(u32 port, अचिन्हित अक्षर width);

अटल व्योम FPT_queueSelectFail(काष्ठा sccb_card *pCurrCard,
				अचिन्हित अक्षर p_card);
अटल व्योम FPT_queueDisconnect(काष्ठा sccb *p_SCCB, अचिन्हित अक्षर p_card);
अटल व्योम FPT_queueCmdComplete(काष्ठा sccb_card *pCurrCard,
				 काष्ठा sccb *p_SCCB, अचिन्हित अक्षर p_card);
अटल व्योम FPT_queueSearchSelect(काष्ठा sccb_card *pCurrCard,
				  अचिन्हित अक्षर p_card);
अटल व्योम FPT_queueFlushSccb(अचिन्हित अक्षर p_card, अचिन्हित अक्षर error_code);
अटल व्योम FPT_queueAddSccb(काष्ठा sccb *p_SCCB, अचिन्हित अक्षर card);
अटल अचिन्हित अक्षर FPT_queueFindSccb(काष्ठा sccb *p_SCCB,
				       अचिन्हित अक्षर p_card);
अटल व्योम FPT_utilUpdateResidual(काष्ठा sccb *p_SCCB);
अटल अचिन्हित लघु FPT_CalcCrc16(अचिन्हित अक्षर buffer[]);
अटल अचिन्हित अक्षर FPT_CalcLrc(अचिन्हित अक्षर buffer[]);

अटल व्योम FPT_Wait1Second(u32 p_port);
अटल व्योम FPT_Wait(u32 p_port, अचिन्हित अक्षर p_delay);
अटल व्योम FPT_utilEEWriteOnOff(u32 p_port, अचिन्हित अक्षर p_mode);
अटल व्योम FPT_utilEEWrite(u32 p_port, अचिन्हित लघु ee_data,
			    अचिन्हित लघु ee_addr);
अटल अचिन्हित लघु FPT_utilEERead(u32 p_port,
				     अचिन्हित लघु ee_addr);
अटल अचिन्हित लघु FPT_utilEEReadOrg(u32 p_port,
					अचिन्हित लघु ee_addr);
अटल व्योम FPT_utilEESendCmdAddr(u32 p_port, अचिन्हित अक्षर ee_cmd,
				  अचिन्हित लघु ee_addr);

अटल व्योम FPT_phaseDataOut(u32 port, अचिन्हित अक्षर p_card);
अटल व्योम FPT_phaseDataIn(u32 port, अचिन्हित अक्षर p_card);
अटल व्योम FPT_phaseCommand(u32 port, अचिन्हित अक्षर p_card);
अटल व्योम FPT_phaseStatus(u32 port, अचिन्हित अक्षर p_card);
अटल व्योम FPT_phaseMsgOut(u32 port, अचिन्हित अक्षर p_card);
अटल व्योम FPT_phaseMsgIn(u32 port, अचिन्हित अक्षर p_card);
अटल व्योम FPT_phaseIllegal(u32 port, अचिन्हित अक्षर p_card);

अटल व्योम FPT_phaseDecode(u32 port, अचिन्हित अक्षर p_card);
अटल व्योम FPT_phaseChkFअगरo(u32 port, अचिन्हित अक्षर p_card);
अटल व्योम FPT_phaseBusFree(u32 p_port, अचिन्हित अक्षर p_card);

अटल व्योम FPT_XbowInit(u32 port, अचिन्हित अक्षर scamFlg);
अटल व्योम FPT_BusMasterInit(u32 p_port);
अटल व्योम FPT_DiagEEPROM(u32 p_port);

अटल व्योम FPT_dataXferProcessor(u32 port,
				  काष्ठा sccb_card *pCurrCard);
अटल व्योम FPT_busMstrSGDataXferStart(u32 port,
				       काष्ठा sccb *pCurrSCCB);
अटल व्योम FPT_busMstrDataXferStart(u32 port,
				     काष्ठा sccb *pCurrSCCB);
अटल व्योम FPT_hostDataXferAbort(u32 port, अचिन्हित अक्षर p_card,
				  काष्ठा sccb *pCurrSCCB);
अटल व्योम FPT_hostDataXferRestart(काष्ठा sccb *currSCCB);

अटल अचिन्हित अक्षर FPT_SccbMgr_bad_isr(u32 p_port,
					 अचिन्हित अक्षर p_card,
					 काष्ठा sccb_card *pCurrCard,
					 अचिन्हित लघु p_पूर्णांक);

अटल व्योम FPT_SccbMgrTableInitAll(व्योम);
अटल व्योम FPT_SccbMgrTableInitCard(काष्ठा sccb_card *pCurrCard,
				     अचिन्हित अक्षर p_card);
अटल व्योम FPT_SccbMgrTableInitTarget(अचिन्हित अक्षर p_card,
				       अचिन्हित अक्षर target);

अटल व्योम FPT_scini(अचिन्हित अक्षर p_card, अचिन्हित अक्षर p_our_id,
		      अचिन्हित अक्षर p_घातer_up);

अटल पूर्णांक FPT_scarb(u32 p_port, अचिन्हित अक्षर p_sel_type);
अटल व्योम FPT_scbusf(u32 p_port);
अटल व्योम FPT_scsel(u32 p_port);
अटल व्योम FPT_scasid(अचिन्हित अक्षर p_card, u32 p_port);
अटल अचिन्हित अक्षर FPT_scxferc(u32 p_port, अचिन्हित अक्षर p_data);
अटल अचिन्हित अक्षर FPT_scsendi(u32 p_port,
				 अचिन्हित अक्षर p_id_string[]);
अटल अचिन्हित अक्षर FPT_sciso(u32 p_port,
			       अचिन्हित अक्षर p_id_string[]);
अटल व्योम FPT_scwirod(u32 p_port, अचिन्हित अक्षर p_data_bit);
अटल व्योम FPT_scwiros(u32 p_port, अचिन्हित अक्षर p_data_bit);
अटल अचिन्हित अक्षर FPT_scvalq(अचिन्हित अक्षर p_quपूर्णांकet);
अटल अचिन्हित अक्षर FPT_scsell(u32 p_port, अचिन्हित अक्षर targ_id);
अटल व्योम FPT_scwtsel(u32 p_port);
अटल व्योम FPT_inisci(अचिन्हित अक्षर p_card, u32 p_port,
		       अचिन्हित अक्षर p_our_id);
अटल व्योम FPT_scsavdi(अचिन्हित अक्षर p_card, u32 p_port);
अटल अचिन्हित अक्षर FPT_scmachid(अचिन्हित अक्षर p_card,
				  अचिन्हित अक्षर p_id_string[]);

अटल व्योम FPT_स्वतःCmdCmplt(u32 p_port, अचिन्हित अक्षर p_card);
अटल व्योम FPT_स्वतःLoadDefaultMap(u32 p_port);

अटल काष्ठा sccb_mgr_tar_info FPT_sccbMgrTbl[MAX_CARDS][MAX_SCSI_TAR] =
    अणु अणुअणु0पूर्णपूर्ण पूर्ण;
अटल काष्ठा sccb_card FPT_BL_Card[MAX_CARDS] = अणु अणु0पूर्ण पूर्ण;
अटल SCCBSCAM_INFO FPT_scamInfo[MAX_SCSI_TAR] = अणु अणुअणु0पूर्णपूर्ण पूर्ण;
अटल काष्ठा nvram_info FPT_nvRamInfo[MAX_MB_CARDS] = अणु अणु0पूर्ण पूर्ण;

अटल अचिन्हित अक्षर FPT_mbCards = 0;
अटल अचिन्हित अक्षर FPT_scamHAString[] =
    अणु 0x63, 0x07, 'B', 'U', 'S', 'L', 'O', 'G', 'I', 'C',
	' ', 'B', 'T', '-', '9', '3', '0',
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
पूर्ण;

अटल अचिन्हित लघु FPT_शेष_पूर्णांकena = 0;

अटल व्योम (*FPT_s_PhaseTbl[8]) (u32, अचिन्हित अक्षर) = अणु
0पूर्ण;

/*---------------------------------------------------------------------
 *
 * Function: FlashPoपूर्णांक_ProbeHostAdapter
 *
 * Description: Setup and/or Search क्रम cards and वापस info to caller.
 *
 *---------------------------------------------------------------------*/

अटल पूर्णांक FlashPoपूर्णांक_ProbeHostAdapter(काष्ठा sccb_mgr_info *pCardInfo)
अणु
	अटल अचिन्हित अक्षर first_समय = 1;

	अचिन्हित अक्षर i, j, id, ScamFlg;
	अचिन्हित लघु temp, temp2, temp3, temp4, temp5, temp6;
	u32 ioport;
	काष्ठा nvram_info *pCurrNvRam;

	ioport = pCardInfo->si_baseaddr;

	अगर (RD_HARPOON(ioport + hp_venकरोr_id_0) != ORION_VEND_0)
		वापस (पूर्णांक)FAILURE;

	अगर ((RD_HARPOON(ioport + hp_venकरोr_id_1) != ORION_VEND_1))
		वापस (पूर्णांक)FAILURE;

	अगर ((RD_HARPOON(ioport + hp_device_id_0) != ORION_DEV_0))
		वापस (पूर्णांक)FAILURE;

	अगर ((RD_HARPOON(ioport + hp_device_id_1) != ORION_DEV_1))
		वापस (पूर्णांक)FAILURE;

	अगर (RD_HARPOON(ioport + hp_rev_num) != 0x0f) अणु

/* For new Harpoon then check क्रम sub_device ID LSB
   the bits(0-3) must be all ZERO क्रम compatible with
   current version of SCCBMgr, अन्यथा skip this Harpoon
	device. */

		अगर (RD_HARPOON(ioport + hp_sub_device_id_0) & 0x0f)
			वापस (पूर्णांक)FAILURE;
	पूर्ण

	अगर (first_समय) अणु
		FPT_SccbMgrTableInitAll();
		first_समय = 0;
		FPT_mbCards = 0;
	पूर्ण

	अगर (FPT_RdStack(ioport, 0) != 0x00) अणु
		अगर (FPT_ChkIfChipInitialized(ioport) == 0) अणु
			pCurrNvRam = शून्य;
			WR_HARPOON(ioport + hp_semaphore, 0x00);
			FPT_XbowInit(ioport, 0);	/*Must Init the SCSI beक्रमe attempting */
			FPT_DiagEEPROM(ioport);
		पूर्ण अन्यथा अणु
			अगर (FPT_mbCards < MAX_MB_CARDS) अणु
				pCurrNvRam = &FPT_nvRamInfo[FPT_mbCards];
				FPT_mbCards++;
				pCurrNvRam->niBaseAddr = ioport;
				FPT_RNVRamData(pCurrNvRam);
			पूर्ण अन्यथा
				वापस (पूर्णांक)FAILURE;
		पूर्ण
	पूर्ण अन्यथा
		pCurrNvRam = शून्य;

	WR_HARPOON(ioport + hp_clkctrl_0, CLKCTRL_DEFAULT);
	WR_HARPOON(ioport + hp_sys_ctrl, 0x00);

	अगर (pCurrNvRam)
		pCardInfo->si_id = pCurrNvRam->niAdapId;
	अन्यथा
		pCardInfo->si_id =
		    (अचिन्हित
		     अक्षर)(FPT_utilEERead(ioport,
					  (ADAPTER_SCSI_ID /
					   2)) & (अचिन्हित अक्षर)0x0FF);

	pCardInfo->si_lun = 0x00;
	pCardInfo->si_fw_revision = ORION_FW_REV;
	temp2 = 0x0000;
	temp3 = 0x0000;
	temp4 = 0x0000;
	temp5 = 0x0000;
	temp6 = 0x0000;

	क्रम (id = 0; id < (16 / 2); id++) अणु

		अगर (pCurrNvRam) अणु
			temp = (अचिन्हित लघु)pCurrNvRam->niSyncTbl[id];
			temp = ((temp & 0x03) + ((temp << 4) & 0xc0)) +
			    (((temp << 4) & 0x0300) + ((temp << 8) & 0xc000));
		पूर्ण अन्यथा
			temp =
			    FPT_utilEERead(ioport,
					   (अचिन्हित लघु)((SYNC_RATE_TBL / 2)
							    + id));

		क्रम (i = 0; i < 2; temp >>= 8, i++) अणु

			temp2 >>= 1;
			temp3 >>= 1;
			temp4 >>= 1;
			temp5 >>= 1;
			temp6 >>= 1;
			चयन (temp & 0x3) अणु
			हाल AUTO_RATE_20:	/* Synchronous, 20 mega-transfers/second */
				temp6 |= 0x8000;
				fallthrough;
			हाल AUTO_RATE_10:	/* Synchronous, 10 mega-transfers/second */
				temp5 |= 0x8000;
				fallthrough;
			हाल AUTO_RATE_05:	/* Synchronous, 5 mega-transfers/second */
				temp2 |= 0x8000;
				fallthrough;
			हाल AUTO_RATE_00:	/* Asynchronous */
				अवरोध;
			पूर्ण

			अगर (temp & DISC_ENABLE_BIT)
				temp3 |= 0x8000;

			अगर (temp & WIDE_NEGO_BIT)
				temp4 |= 0x8000;

		पूर्ण
	पूर्ण

	pCardInfo->si_per_targ_init_sync = temp2;
	pCardInfo->si_per_targ_no_disc = temp3;
	pCardInfo->si_per_targ_wide_nego = temp4;
	pCardInfo->si_per_targ_fast_nego = temp5;
	pCardInfo->si_per_targ_ultra_nego = temp6;

	अगर (pCurrNvRam)
		i = pCurrNvRam->niSysConf;
	अन्यथा
		i = (अचिन्हित
		     अक्षर)(FPT_utilEERead(ioport, (SYSTEM_CONFIG / 2)));

	अगर (pCurrNvRam)
		ScamFlg = pCurrNvRam->niScamConf;
	अन्यथा
		ScamFlg =
		    (अचिन्हित अक्षर)FPT_utilEERead(ioport, SCAM_CONFIG / 2);

	pCardInfo->si_flags = 0x0000;

	अगर (i & 0x01)
		pCardInfo->si_flags |= SCSI_PARITY_ENA;

	अगर (!(i & 0x02))
		pCardInfo->si_flags |= SOFT_RESET;

	अगर (i & 0x10)
		pCardInfo->si_flags |= EXTENDED_TRANSLATION;

	अगर (ScamFlg & SCAM_ENABLED)
		pCardInfo->si_flags |= FLAG_SCAM_ENABLED;

	अगर (ScamFlg & SCAM_LEVEL2)
		pCardInfo->si_flags |= FLAG_SCAM_LEVEL2;

	j = (RD_HARPOON(ioport + hp_bm_ctrl) & ~SCSI_TERM_ENA_L);
	अगर (i & 0x04) अणु
		j |= SCSI_TERM_ENA_L;
	पूर्ण
	WR_HARPOON(ioport + hp_bm_ctrl, j);

	j = (RD_HARPOON(ioport + hp_ee_ctrl) & ~SCSI_TERM_ENA_H);
	अगर (i & 0x08) अणु
		j |= SCSI_TERM_ENA_H;
	पूर्ण
	WR_HARPOON(ioport + hp_ee_ctrl, j);

	अगर (!(RD_HARPOON(ioport + hp_page_ctrl) & NARROW_SCSI_CARD))

		pCardInfo->si_flags |= SUPPORT_16TAR_32LUN;

	pCardInfo->si_card_family = HARPOON_FAMILY;
	pCardInfo->si_bustype = BUSTYPE_PCI;

	अगर (pCurrNvRam) अणु
		pCardInfo->si_card_model[0] = '9';
		चयन (pCurrNvRam->niModel & 0x0f) अणु
		हाल MODEL_LT:
			pCardInfo->si_card_model[1] = '3';
			pCardInfo->si_card_model[2] = '0';
			अवरोध;
		हाल MODEL_LW:
			pCardInfo->si_card_model[1] = '5';
			pCardInfo->si_card_model[2] = '0';
			अवरोध;
		हाल MODEL_DL:
			pCardInfo->si_card_model[1] = '3';
			pCardInfo->si_card_model[2] = '2';
			अवरोध;
		हाल MODEL_DW:
			pCardInfo->si_card_model[1] = '5';
			pCardInfo->si_card_model[2] = '2';
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		temp = FPT_utilEERead(ioport, (MODEL_NUMB_0 / 2));
		pCardInfo->si_card_model[0] = (अचिन्हित अक्षर)(temp >> 8);
		temp = FPT_utilEERead(ioport, (MODEL_NUMB_2 / 2));

		pCardInfo->si_card_model[1] = (अचिन्हित अक्षर)(temp & 0x00FF);
		pCardInfo->si_card_model[2] = (अचिन्हित अक्षर)(temp >> 8);
	पूर्ण

	अगर (pCardInfo->si_card_model[1] == '3') अणु
		अगर (RD_HARPOON(ioport + hp_ee_ctrl) & BIT(7))
			pCardInfo->si_flags |= LOW_BYTE_TERM;
	पूर्ण अन्यथा अगर (pCardInfo->si_card_model[2] == '0') अणु
		temp = RD_HARPOON(ioport + hp_xfer_pad);
		WR_HARPOON(ioport + hp_xfer_pad, (temp & ~BIT(4)));
		अगर (RD_HARPOON(ioport + hp_ee_ctrl) & BIT(7))
			pCardInfo->si_flags |= LOW_BYTE_TERM;
		WR_HARPOON(ioport + hp_xfer_pad, (temp | BIT(4)));
		अगर (RD_HARPOON(ioport + hp_ee_ctrl) & BIT(7))
			pCardInfo->si_flags |= HIGH_BYTE_TERM;
		WR_HARPOON(ioport + hp_xfer_pad, temp);
	पूर्ण अन्यथा अणु
		temp = RD_HARPOON(ioport + hp_ee_ctrl);
		temp2 = RD_HARPOON(ioport + hp_xfer_pad);
		WR_HARPOON(ioport + hp_ee_ctrl, (temp | SEE_CS));
		WR_HARPOON(ioport + hp_xfer_pad, (temp2 | BIT(4)));
		temp3 = 0;
		क्रम (i = 0; i < 8; i++) अणु
			temp3 <<= 1;
			अगर (!(RD_HARPOON(ioport + hp_ee_ctrl) & BIT(7)))
				temp3 |= 1;
			WR_HARPOON(ioport + hp_xfer_pad, (temp2 & ~BIT(4)));
			WR_HARPOON(ioport + hp_xfer_pad, (temp2 | BIT(4)));
		पूर्ण
		WR_HARPOON(ioport + hp_ee_ctrl, temp);
		WR_HARPOON(ioport + hp_xfer_pad, temp2);
		अगर (!(temp3 & BIT(7)))
			pCardInfo->si_flags |= LOW_BYTE_TERM;
		अगर (!(temp3 & BIT(6)))
			pCardInfo->si_flags |= HIGH_BYTE_TERM;
	पूर्ण

	ARAM_ACCESS(ioport);

	क्रम (i = 0; i < 4; i++) अणु

		pCardInfo->si_XlatInfo[i] =
		    RD_HARPOON(ioport + hp_aramBase + BIOS_DATA_OFFSET + i);
	पूर्ण

	/* वापस with -1 अगर no sort, अन्यथा वापस with
	   logical card number sorted by BIOS (zero-based) */

	pCardInfo->si_relative_cardnum =
	    (अचिन्हित
	     अक्षर)(RD_HARPOON(ioport + hp_aramBase + BIOS_RELATIVE_CARD) - 1);

	SGRAM_ACCESS(ioport);

	FPT_s_PhaseTbl[0] = FPT_phaseDataOut;
	FPT_s_PhaseTbl[1] = FPT_phaseDataIn;
	FPT_s_PhaseTbl[2] = FPT_phaseIllegal;
	FPT_s_PhaseTbl[3] = FPT_phaseIllegal;
	FPT_s_PhaseTbl[4] = FPT_phaseCommand;
	FPT_s_PhaseTbl[5] = FPT_phaseStatus;
	FPT_s_PhaseTbl[6] = FPT_phaseMsgOut;
	FPT_s_PhaseTbl[7] = FPT_phaseMsgIn;

	pCardInfo->si_present = 0x01;

	वापस 0;
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FlashPoपूर्णांक_HardwareResetHostAdapter
 *
 * Description: Setup adapter क्रम normal operation (hard reset).
 *
 *---------------------------------------------------------------------*/

अटल व्योम *FlashPoपूर्णांक_HardwareResetHostAdapter(काष्ठा sccb_mgr_info
							 *pCardInfo)
अणु
	काष्ठा sccb_card *CurrCard = शून्य;
	काष्ठा nvram_info *pCurrNvRam;
	अचिन्हित अक्षर i, j, thisCard, ScamFlg;
	अचिन्हित लघु temp, sync_bit_map, id;
	u32 ioport;

	ioport = pCardInfo->si_baseaddr;

	क्रम (thisCard = 0; thisCard <= MAX_CARDS; thisCard++) अणु

		अगर (thisCard == MAX_CARDS)
			वापस (व्योम *)FAILURE;

		अगर (FPT_BL_Card[thisCard].ioPort == ioport) अणु

			CurrCard = &FPT_BL_Card[thisCard];
			FPT_SccbMgrTableInitCard(CurrCard, thisCard);
			अवरोध;
		पूर्ण

		अन्यथा अगर (FPT_BL_Card[thisCard].ioPort == 0x00) अणु

			FPT_BL_Card[thisCard].ioPort = ioport;
			CurrCard = &FPT_BL_Card[thisCard];

			अगर (FPT_mbCards)
				क्रम (i = 0; i < FPT_mbCards; i++) अणु
					अगर (CurrCard->ioPort ==
					    FPT_nvRamInfo[i].niBaseAddr)
						CurrCard->pNvRamInfo =
						    &FPT_nvRamInfo[i];
				पूर्ण
			FPT_SccbMgrTableInitCard(CurrCard, thisCard);
			CurrCard->cardIndex = thisCard;
			CurrCard->cardInfo = pCardInfo;

			अवरोध;
		पूर्ण
	पूर्ण

	pCurrNvRam = CurrCard->pNvRamInfo;

	अगर (pCurrNvRam) अणु
		ScamFlg = pCurrNvRam->niScamConf;
	पूर्ण अन्यथा अणु
		ScamFlg =
		    (अचिन्हित अक्षर)FPT_utilEERead(ioport, SCAM_CONFIG / 2);
	पूर्ण

	FPT_BusMasterInit(ioport);
	FPT_XbowInit(ioport, ScamFlg);

	FPT_स्वतःLoadDefaultMap(ioport);

	क्रम (i = 0, id = 0x01; i != pCardInfo->si_id; i++, id <<= 1) अणु
	पूर्ण

	WR_HARPOON(ioport + hp_selfid_0, id);
	WR_HARPOON(ioport + hp_selfid_1, 0x00);
	WR_HARPOON(ioport + hp_arb_id, pCardInfo->si_id);
	CurrCard->ourId = pCardInfo->si_id;

	i = (अचिन्हित अक्षर)pCardInfo->si_flags;
	अगर (i & SCSI_PARITY_ENA)
		WR_HARPOON(ioport + hp_portctrl_1, (HOST_MODE8 | CHK_SCSI_P));

	j = (RD_HARPOON(ioport + hp_bm_ctrl) & ~SCSI_TERM_ENA_L);
	अगर (i & LOW_BYTE_TERM)
		j |= SCSI_TERM_ENA_L;
	WR_HARPOON(ioport + hp_bm_ctrl, j);

	j = (RD_HARPOON(ioport + hp_ee_ctrl) & ~SCSI_TERM_ENA_H);
	अगर (i & HIGH_BYTE_TERM)
		j |= SCSI_TERM_ENA_H;
	WR_HARPOON(ioport + hp_ee_ctrl, j);

	अगर (!(pCardInfo->si_flags & SOFT_RESET)) अणु

		FPT_sresb(ioport, thisCard);

		FPT_scini(thisCard, pCardInfo->si_id, 0);
	पूर्ण

	अगर (pCardInfo->si_flags & POST_ALL_UNDERRRUNS)
		CurrCard->globalFlags |= F_NO_FILTER;

	अगर (pCurrNvRam) अणु
		अगर (pCurrNvRam->niSysConf & 0x10)
			CurrCard->globalFlags |= F_GREEN_PC;
	पूर्ण अन्यथा अणु
		अगर (FPT_utilEERead(ioport, (SYSTEM_CONFIG / 2)) & GREEN_PC_ENA)
			CurrCard->globalFlags |= F_GREEN_PC;
	पूर्ण

	/* Set global flag to indicate Re-Negotiation to be करोne on all
	   ckeck condition */
	अगर (pCurrNvRam) अणु
		अगर (pCurrNvRam->niScsiConf & 0x04)
			CurrCard->globalFlags |= F_DO_RENEGO;
	पूर्ण अन्यथा अणु
		अगर (FPT_utilEERead(ioport, (SCSI_CONFIG / 2)) & RENEGO_ENA)
			CurrCard->globalFlags |= F_DO_RENEGO;
	पूर्ण

	अगर (pCurrNvRam) अणु
		अगर (pCurrNvRam->niScsiConf & 0x08)
			CurrCard->globalFlags |= F_CONLUN_IO;
	पूर्ण अन्यथा अणु
		अगर (FPT_utilEERead(ioport, (SCSI_CONFIG / 2)) & CONNIO_ENA)
			CurrCard->globalFlags |= F_CONLUN_IO;
	पूर्ण

	temp = pCardInfo->si_per_targ_no_disc;

	क्रम (i = 0, id = 1; i < MAX_SCSI_TAR; i++, id <<= 1) अणु

		अगर (temp & id)
			FPT_sccbMgrTbl[thisCard][i].TarStatus |= TAR_ALLOW_DISC;
	पूर्ण

	sync_bit_map = 0x0001;

	क्रम (id = 0; id < (MAX_SCSI_TAR / 2); id++) अणु

		अगर (pCurrNvRam) अणु
			temp = (अचिन्हित लघु)pCurrNvRam->niSyncTbl[id];
			temp = ((temp & 0x03) + ((temp << 4) & 0xc0)) +
			    (((temp << 4) & 0x0300) + ((temp << 8) & 0xc000));
		पूर्ण अन्यथा
			temp =
			    FPT_utilEERead(ioport,
					   (अचिन्हित लघु)((SYNC_RATE_TBL / 2)
							    + id));

		क्रम (i = 0; i < 2; temp >>= 8, i++) अणु

			अगर (pCardInfo->si_per_targ_init_sync & sync_bit_map) अणु

				FPT_sccbMgrTbl[thisCard][id * 2 +
							 i].TarEEValue =
				    (अचिन्हित अक्षर)temp;
			पूर्ण

			अन्यथा अणु
				FPT_sccbMgrTbl[thisCard][id * 2 +
							 i].TarStatus |=
				    SYNC_SUPPORTED;
				FPT_sccbMgrTbl[thisCard][id * 2 +
							 i].TarEEValue =
				    (अचिन्हित अक्षर)(temp & ~EE_SYNC_MASK);
			पूर्ण

/*         अगर ((pCardInfo->si_per_targ_wide_nego & sync_bit_map) ||
            (id*2+i >= 8))अणु
*/
			अगर (pCardInfo->si_per_targ_wide_nego & sync_bit_map) अणु

				FPT_sccbMgrTbl[thisCard][id * 2 +
							 i].TarEEValue |=
				    EE_WIDE_SCSI;

			पूर्ण

			अन्यथा अणु	/* NARROW SCSI */
				FPT_sccbMgrTbl[thisCard][id * 2 +
							 i].TarStatus |=
				    WIDE_NEGOCIATED;
			पूर्ण

			sync_bit_map <<= 1;

		पूर्ण
	पूर्ण

	WR_HARPOON((ioport + hp_semaphore),
		   (अचिन्हित अक्षर)(RD_HARPOON((ioport + hp_semaphore)) |
				   SCCB_MGR_PRESENT));

	वापस (व्योम *)CurrCard;
पूर्ण

अटल व्योम FlashPoपूर्णांक_ReleaseHostAdapter(व्योम *pCurrCard)
अणु
	अचिन्हित अक्षर i;
	u32 portBase;
	u32 regOffset;
	u32 scamData;
	u32 *pScamTbl;
	काष्ठा nvram_info *pCurrNvRam;

	pCurrNvRam = ((काष्ठा sccb_card *)pCurrCard)->pNvRamInfo;

	अगर (pCurrNvRam) अणु
		FPT_WrStack(pCurrNvRam->niBaseAddr, 0, pCurrNvRam->niModel);
		FPT_WrStack(pCurrNvRam->niBaseAddr, 1, pCurrNvRam->niSysConf);
		FPT_WrStack(pCurrNvRam->niBaseAddr, 2, pCurrNvRam->niScsiConf);
		FPT_WrStack(pCurrNvRam->niBaseAddr, 3, pCurrNvRam->niScamConf);
		FPT_WrStack(pCurrNvRam->niBaseAddr, 4, pCurrNvRam->niAdapId);

		क्रम (i = 0; i < MAX_SCSI_TAR / 2; i++)
			FPT_WrStack(pCurrNvRam->niBaseAddr,
				    (अचिन्हित अक्षर)(i + 5),
				    pCurrNvRam->niSyncTbl[i]);

		portBase = pCurrNvRam->niBaseAddr;

		क्रम (i = 0; i < MAX_SCSI_TAR; i++) अणु
			regOffset = hp_aramBase + 64 + i * 4;
			pScamTbl = (u32 *)&pCurrNvRam->niScamTbl[i];
			scamData = *pScamTbl;
			WR_HARP32(portBase, regOffset, scamData);
		पूर्ण

	पूर्ण अन्यथा अणु
		FPT_WrStack(((काष्ठा sccb_card *)pCurrCard)->ioPort, 0, 0);
	पूर्ण
पूर्ण

अटल व्योम FPT_RNVRamData(काष्ठा nvram_info *pNvRamInfo)
अणु
	अचिन्हित अक्षर i;
	u32 portBase;
	u32 regOffset;
	u32 scamData;
	u32 *pScamTbl;

	pNvRamInfo->niModel = FPT_RdStack(pNvRamInfo->niBaseAddr, 0);
	pNvRamInfo->niSysConf = FPT_RdStack(pNvRamInfo->niBaseAddr, 1);
	pNvRamInfo->niScsiConf = FPT_RdStack(pNvRamInfo->niBaseAddr, 2);
	pNvRamInfo->niScamConf = FPT_RdStack(pNvRamInfo->niBaseAddr, 3);
	pNvRamInfo->niAdapId = FPT_RdStack(pNvRamInfo->niBaseAddr, 4);

	क्रम (i = 0; i < MAX_SCSI_TAR / 2; i++)
		pNvRamInfo->niSyncTbl[i] =
		    FPT_RdStack(pNvRamInfo->niBaseAddr, (अचिन्हित अक्षर)(i + 5));

	portBase = pNvRamInfo->niBaseAddr;

	क्रम (i = 0; i < MAX_SCSI_TAR; i++) अणु
		regOffset = hp_aramBase + 64 + i * 4;
		RD_HARP32(portBase, regOffset, scamData);
		pScamTbl = (u32 *)&pNvRamInfo->niScamTbl[i];
		*pScamTbl = scamData;
	पूर्ण

पूर्ण

अटल अचिन्हित अक्षर FPT_RdStack(u32 portBase, अचिन्हित अक्षर index)
अणु
	WR_HARPOON(portBase + hp_stack_addr, index);
	वापस RD_HARPOON(portBase + hp_stack_data);
पूर्ण

अटल व्योम FPT_WrStack(u32 portBase, अचिन्हित अक्षर index, अचिन्हित अक्षर data)
अणु
	WR_HARPOON(portBase + hp_stack_addr, index);
	WR_HARPOON(portBase + hp_stack_data, data);
पूर्ण

अटल अचिन्हित अक्षर FPT_ChkIfChipInitialized(u32 ioPort)
अणु
	अगर ((RD_HARPOON(ioPort + hp_arb_id) & 0x0f) != FPT_RdStack(ioPort, 4))
		वापस 0;
	अगर ((RD_HARPOON(ioPort + hp_clkctrl_0) & CLKCTRL_DEFAULT)
	    != CLKCTRL_DEFAULT)
		वापस 0;
	अगर ((RD_HARPOON(ioPort + hp_selसमयout) == TO_250ms) ||
	    (RD_HARPOON(ioPort + hp_selसमयout) == TO_290ms))
		वापस 1;
	वापस 0;

पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FlashPoपूर्णांक_StartCCB
 *
 * Description: Start a command poपूर्णांकed to by p_Sccb. When the
 *              command is completed it will be वापसed via the
 *              callback function.
 *
 *---------------------------------------------------------------------*/
अटल व्योम FlashPoपूर्णांक_StartCCB(व्योम *curr_card, काष्ठा sccb *p_Sccb)
अणु
	u32 ioport;
	अचिन्हित अक्षर thisCard, lun;
	काष्ठा sccb *pSaveSccb;
	CALL_BK_FN callback;
	काष्ठा sccb_card *pCurrCard = curr_card;

	thisCard = pCurrCard->cardIndex;
	ioport = pCurrCard->ioPort;

	अगर ((p_Sccb->TargID >= MAX_SCSI_TAR) || (p_Sccb->Lun >= MAX_LUN)) अणु

		p_Sccb->HostStatus = SCCB_COMPLETE;
		p_Sccb->SccbStatus = SCCB_ERROR;
		callback = (CALL_BK_FN) p_Sccb->SccbCallback;
		अगर (callback)
			callback(p_Sccb);

		वापस;
	पूर्ण

	FPT_sinits(p_Sccb, thisCard);

	अगर (!pCurrCard->cmdCounter) अणु
		WR_HARPOON(ioport + hp_semaphore,
			   (RD_HARPOON(ioport + hp_semaphore)
			    | SCCB_MGR_ACTIVE));

		अगर (pCurrCard->globalFlags & F_GREEN_PC) अणु
			WR_HARPOON(ioport + hp_clkctrl_0, CLKCTRL_DEFAULT);
			WR_HARPOON(ioport + hp_sys_ctrl, 0x00);
		पूर्ण
	पूर्ण

	pCurrCard->cmdCounter++;

	अगर (RD_HARPOON(ioport + hp_semaphore) & BIOS_IN_USE) अणु

		WR_HARPOON(ioport + hp_semaphore,
			   (RD_HARPOON(ioport + hp_semaphore)
			    | TICKLE_ME));
		अगर (p_Sccb->OperationCode == RESET_COMMAND) अणु
			pSaveSccb =
			    pCurrCard->currentSCCB;
			pCurrCard->currentSCCB = p_Sccb;
			FPT_queueSelectFail(&FPT_BL_Card[thisCard], thisCard);
			pCurrCard->currentSCCB =
			    pSaveSccb;
		पूर्ण अन्यथा अणु
			FPT_queueAddSccb(p_Sccb, thisCard);
		पूर्ण
	पूर्ण

	अन्यथा अगर ((RD_HARPOON(ioport + hp_page_ctrl) & G_INT_DISABLE)) अणु

		अगर (p_Sccb->OperationCode == RESET_COMMAND) अणु
			pSaveSccb =
			    pCurrCard->currentSCCB;
			pCurrCard->currentSCCB = p_Sccb;
			FPT_queueSelectFail(&FPT_BL_Card[thisCard], thisCard);
			pCurrCard->currentSCCB =
			    pSaveSccb;
		पूर्ण अन्यथा अणु
			FPT_queueAddSccb(p_Sccb, thisCard);
		पूर्ण
	पूर्ण

	अन्यथा अणु

		MDISABLE_INT(ioport);

		अगर ((pCurrCard->globalFlags & F_CONLUN_IO) &&
		    ((FPT_sccbMgrTbl[thisCard][p_Sccb->TargID].
		      TarStatus & TAR_TAG_Q_MASK) != TAG_Q_TRYING))
			lun = p_Sccb->Lun;
		अन्यथा
			lun = 0;
		अगर ((pCurrCard->currentSCCB == शून्य) &&
		    (FPT_sccbMgrTbl[thisCard][p_Sccb->TargID].TarSelQ_Cnt == 0)
		    && (FPT_sccbMgrTbl[thisCard][p_Sccb->TargID].TarLUNBusy[lun]
			== 0)) अणु

			pCurrCard->currentSCCB = p_Sccb;
			FPT_ssel(p_Sccb->SccbIOPort, thisCard);
		पूर्ण

		अन्यथा अणु

			अगर (p_Sccb->OperationCode == RESET_COMMAND) अणु
				pSaveSccb = pCurrCard->currentSCCB;
				pCurrCard->currentSCCB = p_Sccb;
				FPT_queueSelectFail(&FPT_BL_Card[thisCard],
						    thisCard);
				pCurrCard->currentSCCB = pSaveSccb;
			पूर्ण अन्यथा अणु
				FPT_queueAddSccb(p_Sccb, thisCard);
			पूर्ण
		पूर्ण

		MENABLE_INT(ioport);
	पूर्ण

पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FlashPoपूर्णांक_AbortCCB
 *
 * Description: Abort the command poपूर्णांकed to by p_Sccb.  When the
 *              command is completed it will be वापसed via the
 *              callback function.
 *
 *---------------------------------------------------------------------*/
अटल पूर्णांक FlashPoपूर्णांक_AbortCCB(व्योम *pCurrCard, काष्ठा sccb *p_Sccb)
अणु
	u32 ioport;

	अचिन्हित अक्षर thisCard;
	CALL_BK_FN callback;
	काष्ठा sccb *pSaveSCCB;
	काष्ठा sccb_mgr_tar_info *currTar_Info;

	ioport = ((काष्ठा sccb_card *)pCurrCard)->ioPort;

	thisCard = ((काष्ठा sccb_card *)pCurrCard)->cardIndex;

	अगर (!(RD_HARPOON(ioport + hp_page_ctrl) & G_INT_DISABLE)) अणु

		अगर (FPT_queueFindSccb(p_Sccb, thisCard)) अणु

			((काष्ठा sccb_card *)pCurrCard)->cmdCounter--;

			अगर (!((काष्ठा sccb_card *)pCurrCard)->cmdCounter)
				WR_HARPOON(ioport + hp_semaphore,
					   (RD_HARPOON(ioport + hp_semaphore)
					    & (अचिन्हित
					       अक्षर)(~(SCCB_MGR_ACTIVE |
						       TICKLE_ME))));

			p_Sccb->SccbStatus = SCCB_ABORT;
			callback = p_Sccb->SccbCallback;
			callback(p_Sccb);

			वापस 0;
		पूर्ण

		अन्यथा अणु
			अगर (((काष्ठा sccb_card *)pCurrCard)->currentSCCB ==
			    p_Sccb) अणु
				p_Sccb->SccbStatus = SCCB_ABORT;
				वापस 0;

			पूर्ण

			अन्यथा अणु
				अगर (p_Sccb->Sccb_tag) अणु
					MDISABLE_INT(ioport);
					अगर (((काष्ठा sccb_card *)pCurrCard)->
					    discQ_Tbl[p_Sccb->Sccb_tag] ==
					    p_Sccb) अणु
						p_Sccb->SccbStatus = SCCB_ABORT;
						p_Sccb->Sccb_scsistat =
						    ABORT_ST;
						p_Sccb->Sccb_scsimsg =
						    SMABORT_TAG;

						अगर (((काष्ठा sccb_card *)
						     pCurrCard)->currentSCCB ==
						    शून्य) अणु
							((काष्ठा sccb_card *)
							 pCurrCard)->
					currentSCCB = p_Sccb;
							FPT_ssel(ioport,
								 thisCard);
						पूर्ण अन्यथा अणु
							pSaveSCCB =
							    ((काष्ठा sccb_card
							      *)pCurrCard)->
							    currentSCCB;
							((काष्ठा sccb_card *)
							 pCurrCard)->
					currentSCCB = p_Sccb;
							FPT_queueSelectFail((काष्ठा sccb_card *)pCurrCard, thisCard);
							((काष्ठा sccb_card *)
							 pCurrCard)->
					currentSCCB = pSaveSCCB;
						पूर्ण
					पूर्ण
					MENABLE_INT(ioport);
					वापस 0;
				पूर्ण अन्यथा अणु
					currTar_Info =
					    &FPT_sccbMgrTbl[thisCard][p_Sccb->
								      TargID];

					अगर (FPT_BL_Card[thisCard].
					    discQ_Tbl[currTar_Info->
						      LunDiscQ_Idx[p_Sccb->Lun]]
					    == p_Sccb) अणु
						p_Sccb->SccbStatus = SCCB_ABORT;
						वापस 0;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FlashPoपूर्णांक_InterruptPending
 *
 * Description: Do a quick check to determine अगर there is a pending
 *              पूर्णांकerrupt क्रम this card and disable the IRQ Pin अगर so.
 *
 *---------------------------------------------------------------------*/
अटल अचिन्हित अक्षर FlashPoपूर्णांक_InterruptPending(व्योम *pCurrCard)
अणु
	u32 ioport;

	ioport = ((काष्ठा sccb_card *)pCurrCard)->ioPort;

	अगर (RD_HARPOON(ioport + hp_पूर्णांक_status) & INT_ASSERTED) अणु
		वापस 1;
	पूर्ण

	अन्यथा

		वापस 0;
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FlashPoपूर्णांक_HandleInterrupt
 *
 * Description: This is our entry poपूर्णांक when an पूर्णांकerrupt is generated
 *              by the card and the upper level driver passes it on to
 *              us.
 *
 *---------------------------------------------------------------------*/
अटल पूर्णांक FlashPoपूर्णांक_HandleInterrupt(व्योम *pcard)
अणु
	काष्ठा sccb *currSCCB;
	अचिन्हित अक्षर thisCard, result, bm_status, bm_पूर्णांक_st;
	अचिन्हित लघु hp_पूर्णांक;
	अचिन्हित अक्षर i, target;
	काष्ठा sccb_card *pCurrCard = pcard;
	u32 ioport;

	thisCard = pCurrCard->cardIndex;
	ioport = pCurrCard->ioPort;

	MDISABLE_INT(ioport);

	अगर ((bm_पूर्णांक_st = RD_HARPOON(ioport + hp_पूर्णांक_status)) & EXT_STATUS_ON)
		bm_status = RD_HARPOON(ioport + hp_ext_status) &
					(अचिन्हित अक्षर)BAD_EXT_STATUS;
	अन्यथा
		bm_status = 0;

	WR_HARPOON(ioport + hp_पूर्णांक_mask, (INT_CMD_COMPL | SCSI_INTERRUPT));

	जबतक ((hp_पूर्णांक = RDW_HARPOON((ioport + hp_पूर्णांकstat)) &
				FPT_शेष_पूर्णांकena) | bm_status) अणु

		currSCCB = pCurrCard->currentSCCB;

		अगर (hp_पूर्णांक & (FIFO | TIMEOUT | RESET | SCAM_SEL) || bm_status) अणु
			result =
			    FPT_SccbMgr_bad_isr(ioport, thisCard, pCurrCard,
						hp_पूर्णांक);
			WRW_HARPOON((ioport + hp_पूर्णांकstat),
				    (FIFO | TIMEOUT | RESET | SCAM_SEL));
			bm_status = 0;

			अगर (result) अणु

				MENABLE_INT(ioport);
				वापस result;
			पूर्ण
		पूर्ण

		अन्यथा अगर (hp_पूर्णांक & ICMD_COMP) अणु

			अगर (!(hp_पूर्णांक & BUS_FREE)) अणु
				/* Wait क्रम the BusFree beक्रमe starting a new command.  We
				   must also check क्रम being reselected since the BusFree
				   may not show up अगर another device reselects us in 1.5us or
				   less.  SRR Wednesday, 3/8/1995.
				 */
				जबतक (!
				       (RDW_HARPOON((ioport + hp_पूर्णांकstat)) &
					(BUS_FREE | RSEL))) ;
			पूर्ण

			अगर (pCurrCard->globalFlags & F_HOST_XFER_ACT)

				FPT_phaseChkFअगरo(ioport, thisCard);

/*         WRW_HARPOON((ioport+hp_पूर्णांकstat),
            (BUS_FREE | ICMD_COMP | ITAR_DISC | XFER_CNT_0));
         */

			WRW_HARPOON((ioport + hp_पूर्णांकstat), CLR_ALL_INT_1);

			FPT_स्वतःCmdCmplt(ioport, thisCard);

		पूर्ण

		अन्यथा अगर (hp_पूर्णांक & ITAR_DISC) अणु

			अगर (pCurrCard->globalFlags & F_HOST_XFER_ACT)
				FPT_phaseChkFअगरo(ioport, thisCard);

			अगर (RD_HARPOON(ioport + hp_gp_reg_1) ==
					SMSAVE_DATA_PTR) अणु

				WR_HARPOON(ioport + hp_gp_reg_1, 0x00);
				currSCCB->Sccb_XferState |= F_NO_DATA_YET;

				currSCCB->Sccb_savedATC = currSCCB->Sccb_ATC;
			पूर्ण

			currSCCB->Sccb_scsistat = DISCONNECT_ST;
			FPT_queueDisconnect(currSCCB, thisCard);

			/* Wait क्रम the BusFree beक्रमe starting a new command.  We
			   must also check क्रम being reselected since the BusFree
			   may not show up अगर another device reselects us in 1.5us or
			   less.  SRR Wednesday, 3/8/1995.
			 */
			जबतक (!
			       (RDW_HARPOON((ioport + hp_पूर्णांकstat)) &
				(BUS_FREE | RSEL))
			       && !((RDW_HARPOON((ioport + hp_पूर्णांकstat)) & PHASE)
				    && RD_HARPOON((ioport + hp_scsisig)) ==
				    (SCSI_BSY | SCSI_REQ | SCSI_CD | SCSI_MSG |
				     SCSI_IOBIT))) ;

			/*
			   The additional loop निकास condition above detects a timing problem
			   with the revision D/E harpoon chips.  The caller should reset the
			   host adapter to recover when 0xFE is वापसed.
			 */
			अगर (!
			    (RDW_HARPOON((ioport + hp_पूर्णांकstat)) &
			     (BUS_FREE | RSEL))) अणु
				MENABLE_INT(ioport);
				वापस 0xFE;
			पूर्ण

			WRW_HARPOON((ioport + hp_पूर्णांकstat),
				    (BUS_FREE | ITAR_DISC));

			pCurrCard->globalFlags |= F_NEW_SCCB_CMD;

		पूर्ण

		अन्यथा अगर (hp_पूर्णांक & RSEL) अणु

			WRW_HARPOON((ioport + hp_पूर्णांकstat),
				    (PROG_HLT | RSEL | PHASE | BUS_FREE));

			अगर (RDW_HARPOON((ioport + hp_पूर्णांकstat)) & ITAR_DISC) अणु
				अगर (pCurrCard->globalFlags & F_HOST_XFER_ACT)
					FPT_phaseChkFअगरo(ioport, thisCard);

				अगर (RD_HARPOON(ioport + hp_gp_reg_1) ==
				    SMSAVE_DATA_PTR) अणु
					WR_HARPOON(ioport + hp_gp_reg_1, 0x00);
					currSCCB->Sccb_XferState |=
					    F_NO_DATA_YET;
					currSCCB->Sccb_savedATC =
					    currSCCB->Sccb_ATC;
				पूर्ण

				WRW_HARPOON((ioport + hp_पूर्णांकstat),
					    (BUS_FREE | ITAR_DISC));
				currSCCB->Sccb_scsistat = DISCONNECT_ST;
				FPT_queueDisconnect(currSCCB, thisCard);
			पूर्ण

			FPT_sres(ioport, thisCard, pCurrCard);
			FPT_phaseDecode(ioport, thisCard);

		पूर्ण

		अन्यथा अगर ((hp_पूर्णांक & IDO_STRT) && (!(hp_पूर्णांक & BUS_FREE))) अणु

			WRW_HARPOON((ioport + hp_पूर्णांकstat),
				    (IDO_STRT | XFER_CNT_0));
			FPT_phaseDecode(ioport, thisCard);

		पूर्ण

		अन्यथा अगर ((hp_पूर्णांक & IUNKWN) || (hp_पूर्णांक & PROG_HLT)) अणु
			WRW_HARPOON((ioport + hp_पूर्णांकstat),
				    (PHASE | IUNKWN | PROG_HLT));
			अगर ((RD_HARPOON(ioport + hp_prgmcnt_0) & (अचिन्हित अक्षर)
			     0x3f) < (अचिन्हित अक्षर)SELCHK) अणु
				FPT_phaseDecode(ioport, thisCard);
			पूर्ण अन्यथा अणु
				/* Harpoon problem some SCSI target device respond to selection
				   with लघु BUSY pulse (<400ns) this will make the Harpoon is not able
				   to latch the correct Target ID पूर्णांकo reg. x53.
				   The work around require to correct this reg. But when ग_लिखो to this
				   reg. (0x53) also increment the FIFO ग_लिखो addr reg (0x6f), thus we
				   need to पढ़ो this reg first then restore it later. After update to 0x53 */

				i = (अचिन्हित
				     अक्षर)(RD_HARPOON(ioport + hp_fअगरoग_लिखो));
				target =
				    (अचिन्हित
				     अक्षर)(RD_HARPOON(ioport + hp_gp_reg_3));
				WR_HARPOON(ioport + hp_xfer_pad,
					   (अचिन्हित अक्षर)ID_UNLOCK);
				WR_HARPOON(ioport + hp_select_id,
					   (अचिन्हित अक्षर)(target | target <<
							   4));
				WR_HARPOON(ioport + hp_xfer_pad,
					   (अचिन्हित अक्षर)0x00);
				WR_HARPOON(ioport + hp_fअगरoग_लिखो, i);
				WR_HARPOON(ioport + hp_स्वतःstart_3,
					   (AUTO_IMMED + TAG_STRT));
			पूर्ण
		पूर्ण

		अन्यथा अगर (hp_पूर्णांक & XFER_CNT_0) अणु

			WRW_HARPOON((ioport + hp_पूर्णांकstat), XFER_CNT_0);

			FPT_schkdd(ioport, thisCard);

		पूर्ण

		अन्यथा अगर (hp_पूर्णांक & BUS_FREE) अणु

			WRW_HARPOON((ioport + hp_पूर्णांकstat), BUS_FREE);

			अगर (pCurrCard->globalFlags & F_HOST_XFER_ACT) अणु

				FPT_hostDataXferAbort(ioport, thisCard,
						      currSCCB);
			पूर्ण

			FPT_phaseBusFree(ioport, thisCard);
		पूर्ण

		अन्यथा अगर (hp_पूर्णांक & ITICKLE) अणु

			WRW_HARPOON((ioport + hp_पूर्णांकstat), ITICKLE);
			pCurrCard->globalFlags |= F_NEW_SCCB_CMD;
		पूर्ण

		अगर (((काष्ठा sccb_card *)pCurrCard)->
		    globalFlags & F_NEW_SCCB_CMD) अणु

			pCurrCard->globalFlags &= ~F_NEW_SCCB_CMD;

			अगर (pCurrCard->currentSCCB == शून्य)
				FPT_queueSearchSelect(pCurrCard, thisCard);

			अगर (pCurrCard->currentSCCB != शून्य) अणु
				pCurrCard->globalFlags &= ~F_NEW_SCCB_CMD;
				FPT_ssel(ioport, thisCard);
			पूर्ण

			अवरोध;

		पूर्ण

	पूर्ण			/*end जबतक */

	MENABLE_INT(ioport);

	वापस 0;
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Sccb_bad_isr
 *
 * Description: Some type of पूर्णांकerrupt has occurred which is slightly
 *              out of the ordinary.  We will now decode it fully, in
 *              this routine.  This is broken up in an attempt to save
 *              processing समय.
 *
 *---------------------------------------------------------------------*/
अटल अचिन्हित अक्षर FPT_SccbMgr_bad_isr(u32 p_port, अचिन्हित अक्षर p_card,
					 काष्ठा sccb_card *pCurrCard,
					 अचिन्हित लघु p_पूर्णांक)
अणु
	अचिन्हित अक्षर temp, ScamFlg;
	काष्ठा sccb_mgr_tar_info *currTar_Info;
	काष्ठा nvram_info *pCurrNvRam;

	अगर (RD_HARPOON(p_port + hp_ext_status) &
	    (BM_FORCE_OFF | PCI_DEV_TMOUT | BM_PARITY_ERR | PIO_OVERRUN)) अणु

		अगर (pCurrCard->globalFlags & F_HOST_XFER_ACT) अणु

			FPT_hostDataXferAbort(p_port, p_card,
					      pCurrCard->currentSCCB);
		पूर्ण

		अगर (RD_HARPOON(p_port + hp_pci_stat_cfg) & REC_MASTER_ABORT)
		अणु
			WR_HARPOON(p_port + hp_pci_stat_cfg,
				   (RD_HARPOON(p_port + hp_pci_stat_cfg) &
				    ~REC_MASTER_ABORT));

			WR_HARPOON(p_port + hp_host_blk_cnt, 0x00);

		पूर्ण

		अगर (pCurrCard->currentSCCB != शून्य) अणु

			अगर (!pCurrCard->currentSCCB->HostStatus)
				pCurrCard->currentSCCB->HostStatus =
				    SCCB_BM_ERR;

			FPT_sxfrp(p_port, p_card);

			temp = (अचिन्हित अक्षर)(RD_HARPOON(p_port + hp_ee_ctrl) &
					       (EXT_ARB_ACK | SCSI_TERM_ENA_H));
			WR_HARPOON(p_port + hp_ee_ctrl,
				   ((अचिन्हित अक्षर)temp | SEE_MS | SEE_CS));
			WR_HARPOON(p_port + hp_ee_ctrl, temp);

			अगर (!
			    (RDW_HARPOON((p_port + hp_पूर्णांकstat)) &
			     (BUS_FREE | RESET))) अणु
				FPT_phaseDecode(p_port, p_card);
			पूर्ण
		पूर्ण
	पूर्ण

	अन्यथा अगर (p_पूर्णांक & RESET) अणु

		WR_HARPOON(p_port + hp_clkctrl_0, CLKCTRL_DEFAULT);
		WR_HARPOON(p_port + hp_sys_ctrl, 0x00);
		अगर (pCurrCard->currentSCCB != शून्य) अणु

			अगर (pCurrCard->globalFlags & F_HOST_XFER_ACT)

				FPT_hostDataXferAbort(p_port, p_card,
						      pCurrCard->currentSCCB);
		पूर्ण

		DISABLE_AUTO(p_port);

		FPT_sresb(p_port, p_card);

		जबतक (RD_HARPOON(p_port + hp_scsictrl_0) & SCSI_RST) अणु
		पूर्ण

		pCurrNvRam = pCurrCard->pNvRamInfo;
		अगर (pCurrNvRam) अणु
			ScamFlg = pCurrNvRam->niScamConf;
		पूर्ण अन्यथा अणु
			ScamFlg =
			    (अचिन्हित अक्षर)FPT_utilEERead(p_port,
							  SCAM_CONFIG / 2);
		पूर्ण

		FPT_XbowInit(p_port, ScamFlg);

		FPT_scini(p_card, pCurrCard->ourId, 0);

		वापस 0xFF;
	पूर्ण

	अन्यथा अगर (p_पूर्णांक & FIFO) अणु

		WRW_HARPOON((p_port + hp_पूर्णांकstat), FIFO);

		अगर (pCurrCard->currentSCCB != शून्य)
			FPT_sxfrp(p_port, p_card);
	पूर्ण

	अन्यथा अगर (p_पूर्णांक & TIMEOUT) अणु

		DISABLE_AUTO(p_port);

		WRW_HARPOON((p_port + hp_पूर्णांकstat),
			    (PROG_HLT | TIMEOUT | SEL | BUS_FREE | PHASE |
			     IUNKWN));

		pCurrCard->currentSCCB->HostStatus = SCCB_SELECTION_TIMEOUT;

		currTar_Info =
		    &FPT_sccbMgrTbl[p_card][pCurrCard->currentSCCB->TargID];
		अगर ((pCurrCard->globalFlags & F_CONLUN_IO)
		    && ((currTar_Info->TarStatus & TAR_TAG_Q_MASK) !=
			TAG_Q_TRYING))
			currTar_Info->TarLUNBusy[pCurrCard->currentSCCB->Lun] =
			    0;
		अन्यथा
			currTar_Info->TarLUNBusy[0] = 0;

		अगर (currTar_Info->TarEEValue & EE_SYNC_MASK) अणु
			currTar_Info->TarSyncCtrl = 0;
			currTar_Info->TarStatus &= ~TAR_SYNC_MASK;
		पूर्ण

		अगर (currTar_Info->TarEEValue & EE_WIDE_SCSI) अणु
			currTar_Info->TarStatus &= ~TAR_WIDE_MASK;
		पूर्ण

		FPT_sssyncv(p_port, pCurrCard->currentSCCB->TargID, NARROW_SCSI,
			    currTar_Info);

		FPT_queueCmdComplete(pCurrCard, pCurrCard->currentSCCB, p_card);

	पूर्ण

	अन्यथा अगर (p_पूर्णांक & SCAM_SEL) अणु

		FPT_scarb(p_port, LEVEL2_TAR);
		FPT_scsel(p_port);
		FPT_scasid(p_card, p_port);

		FPT_scbusf(p_port);

		WRW_HARPOON((p_port + hp_पूर्णांकstat), SCAM_SEL);
	पूर्ण

	वापस 0x00;
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: SccbMgrTableInit
 *
 * Description: Initialize all Sccb manager data काष्ठाures.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_SccbMgrTableInitAll(व्योम)
अणु
	अचिन्हित अक्षर thisCard;

	क्रम (thisCard = 0; thisCard < MAX_CARDS; thisCard++) अणु
		FPT_SccbMgrTableInitCard(&FPT_BL_Card[thisCard], thisCard);

		FPT_BL_Card[thisCard].ioPort = 0x00;
		FPT_BL_Card[thisCard].cardInfo = शून्य;
		FPT_BL_Card[thisCard].cardIndex = 0xFF;
		FPT_BL_Card[thisCard].ourId = 0x00;
		FPT_BL_Card[thisCard].pNvRamInfo = शून्य;
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: SccbMgrTableInit
 *
 * Description: Initialize all Sccb manager data काष्ठाures.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_SccbMgrTableInitCard(काष्ठा sccb_card *pCurrCard,
				     अचिन्हित अक्षर p_card)
अणु
	अचिन्हित अक्षर scsiID, qtag;

	क्रम (qtag = 0; qtag < QUEUE_DEPTH; qtag++) अणु
		FPT_BL_Card[p_card].discQ_Tbl[qtag] = शून्य;
	पूर्ण

	क्रम (scsiID = 0; scsiID < MAX_SCSI_TAR; scsiID++) अणु
		FPT_sccbMgrTbl[p_card][scsiID].TarStatus = 0;
		FPT_sccbMgrTbl[p_card][scsiID].TarEEValue = 0;
		FPT_SccbMgrTableInitTarget(p_card, scsiID);
	पूर्ण

	pCurrCard->scanIndex = 0x00;
	pCurrCard->currentSCCB = शून्य;
	pCurrCard->globalFlags = 0x00;
	pCurrCard->cmdCounter = 0x00;
	pCurrCard->tagQ_Lst = 0x01;
	pCurrCard->discQCount = 0;

पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: SccbMgrTableInit
 *
 * Description: Initialize all Sccb manager data काष्ठाures.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_SccbMgrTableInitTarget(अचिन्हित अक्षर p_card,
				       अचिन्हित अक्षर target)
अणु

	अचिन्हित अक्षर lun, qtag;
	काष्ठा sccb_mgr_tar_info *currTar_Info;

	currTar_Info = &FPT_sccbMgrTbl[p_card][target];

	currTar_Info->TarSelQ_Cnt = 0;
	currTar_Info->TarSyncCtrl = 0;

	currTar_Info->TarSelQ_Head = शून्य;
	currTar_Info->TarSelQ_Tail = शून्य;
	currTar_Info->TarTagQ_Cnt = 0;
	currTar_Info->TarLUN_CA = 0;

	क्रम (lun = 0; lun < MAX_LUN; lun++) अणु
		currTar_Info->TarLUNBusy[lun] = 0;
		currTar_Info->LunDiscQ_Idx[lun] = 0;
	पूर्ण

	क्रम (qtag = 0; qtag < QUEUE_DEPTH; qtag++) अणु
		अगर (FPT_BL_Card[p_card].discQ_Tbl[qtag] != शून्य) अणु
			अगर (FPT_BL_Card[p_card].discQ_Tbl[qtag]->TargID ==
			    target) अणु
				FPT_BL_Card[p_card].discQ_Tbl[qtag] = शून्य;
				FPT_BL_Card[p_card].discQCount--;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: sfeपंचांग
 *
 * Description: Read in a message byte from the SCSI bus, and check
 *              क्रम a parity error.
 *
 *---------------------------------------------------------------------*/

अटल अचिन्हित अक्षर FPT_sfm(u32 port, काष्ठा sccb *pCurrSCCB)
अणु
	अचिन्हित अक्षर message;
	अचिन्हित लघु TimeOutLoop;

	TimeOutLoop = 0;
	जबतक ((!(RD_HARPOON(port + hp_scsisig) & SCSI_REQ)) &&
	       (TimeOutLoop++ < 20000)) अणु
	पूर्ण

	WR_HARPOON(port + hp_portctrl_0, SCSI_PORT);

	message = RD_HARPOON(port + hp_scsidata_0);

	WR_HARPOON(port + hp_scsisig, SCSI_ACK + S_MSGI_PH);

	अगर (TimeOutLoop > 20000)
		message = 0x00;	/* क्रमce message byte = 0 अगर Time Out on Req */

	अगर ((RDW_HARPOON((port + hp_पूर्णांकstat)) & PARITY) &&
	    (RD_HARPOON(port + hp_addstat) & SCSI_PAR_ERR)) अणु
		WR_HARPOON(port + hp_scsisig, (SCSI_ACK + S_ILL_PH));
		WR_HARPOON(port + hp_xferstat, 0);
		WR_HARPOON(port + hp_fअगरoपढ़ो, 0);
		WR_HARPOON(port + hp_fअगरoग_लिखो, 0);
		अगर (pCurrSCCB != शून्य) अणु
			pCurrSCCB->Sccb_scsimsg = SMPARITY;
		पूर्ण
		message = 0x00;
		करो अणु
			ACCEPT_MSG_ATN(port);
			TimeOutLoop = 0;
			जबतक ((!(RD_HARPOON(port + hp_scsisig) & SCSI_REQ)) &&
			       (TimeOutLoop++ < 20000)) अणु
			पूर्ण
			अगर (TimeOutLoop > 20000) अणु
				WRW_HARPOON((port + hp_पूर्णांकstat), PARITY);
				वापस message;
			पूर्ण
			अगर ((RD_HARPOON(port + hp_scsisig) & S_SCSI_PHZ) !=
			    S_MSGI_PH) अणु
				WRW_HARPOON((port + hp_पूर्णांकstat), PARITY);
				वापस message;
			पूर्ण
			WR_HARPOON(port + hp_portctrl_0, SCSI_PORT);

			RD_HARPOON(port + hp_scsidata_0);

			WR_HARPOON(port + hp_scsisig, (SCSI_ACK + S_ILL_PH));

		पूर्ण जबतक (1);

	पूर्ण
	WR_HARPOON(port + hp_scsisig, (SCSI_ACK + S_ILL_PH));
	WR_HARPOON(port + hp_xferstat, 0);
	WR_HARPOON(port + hp_fअगरoपढ़ो, 0);
	WR_HARPOON(port + hp_fअगरoग_लिखो, 0);
	वापस message;
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_ssel
 *
 * Description: Load up स्वतःmation and select target device.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_ssel(u32 port, अचिन्हित अक्षर p_card)
अणु

	अचिन्हित अक्षर स्वतः_loaded, i, target, *theCCB;

	u32 cdb_reg;
	काष्ठा sccb_card *CurrCard;
	काष्ठा sccb *currSCCB;
	काष्ठा sccb_mgr_tar_info *currTar_Info;
	अचिन्हित अक्षर lastTag, lun;

	CurrCard = &FPT_BL_Card[p_card];
	currSCCB = CurrCard->currentSCCB;
	target = currSCCB->TargID;
	currTar_Info = &FPT_sccbMgrTbl[p_card][target];
	lastTag = CurrCard->tagQ_Lst;

	ARAM_ACCESS(port);

	अगर ((currTar_Info->TarStatus & TAR_TAG_Q_MASK) == TAG_Q_REJECT)
		currSCCB->ControlByte &= ~F_USE_CMD_Q;

	अगर (((CurrCard->globalFlags & F_CONLUN_IO) &&
	     ((currTar_Info->TarStatus & TAR_TAG_Q_MASK) != TAG_Q_TRYING)))

		lun = currSCCB->Lun;
	अन्यथा
		lun = 0;

	अगर (CurrCard->globalFlags & F_TAG_STARTED) अणु
		अगर (!(currSCCB->ControlByte & F_USE_CMD_Q)) अणु
			अगर ((currTar_Info->TarLUN_CA == 0)
			    && ((currTar_Info->TarStatus & TAR_TAG_Q_MASK)
				== TAG_Q_TRYING)) अणु

				अगर (currTar_Info->TarTagQ_Cnt != 0) अणु
					currTar_Info->TarLUNBusy[lun] = 1;
					FPT_queueSelectFail(CurrCard, p_card);
					SGRAM_ACCESS(port);
					वापस;
				पूर्ण

				अन्यथा अणु
					currTar_Info->TarLUNBusy[lun] = 1;
				पूर्ण

			पूर्ण
			/*End non-tagged */
			अन्यथा अणु
				currTar_Info->TarLUNBusy[lun] = 1;
			पूर्ण

		पूर्ण
		/*!Use cmd Q Tagged */
		अन्यथा अणु
			अगर (currTar_Info->TarLUN_CA == 1) अणु
				FPT_queueSelectFail(CurrCard, p_card);
				SGRAM_ACCESS(port);
				वापस;
			पूर्ण

			currTar_Info->TarLUNBusy[lun] = 1;

		पूर्ण		/*अन्यथा use cmd Q tagged */

	पूर्ण
	/*अगर glob tagged started */
	अन्यथा अणु
		currTar_Info->TarLUNBusy[lun] = 1;
	पूर्ण

	अगर ((((CurrCard->globalFlags & F_CONLUN_IO) &&
	      ((currTar_Info->TarStatus & TAR_TAG_Q_MASK) != TAG_Q_TRYING))
	     || (!(currSCCB->ControlByte & F_USE_CMD_Q)))) अणु
		अगर (CurrCard->discQCount >= QUEUE_DEPTH) अणु
			currTar_Info->TarLUNBusy[lun] = 1;
			FPT_queueSelectFail(CurrCard, p_card);
			SGRAM_ACCESS(port);
			वापस;
		पूर्ण
		क्रम (i = 1; i < QUEUE_DEPTH; i++) अणु
			अगर (++lastTag >= QUEUE_DEPTH)
				lastTag = 1;
			अगर (CurrCard->discQ_Tbl[lastTag] == शून्य) अणु
				CurrCard->tagQ_Lst = lastTag;
				currTar_Info->LunDiscQ_Idx[lun] = lastTag;
				CurrCard->discQ_Tbl[lastTag] = currSCCB;
				CurrCard->discQCount++;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == QUEUE_DEPTH) अणु
			currTar_Info->TarLUNBusy[lun] = 1;
			FPT_queueSelectFail(CurrCard, p_card);
			SGRAM_ACCESS(port);
			वापस;
		पूर्ण
	पूर्ण

	स्वतः_loaded = 0;

	WR_HARPOON(port + hp_select_id, target);
	WR_HARPOON(port + hp_gp_reg_3, target);	/* Use by new स्वतःmation logic */

	अगर (currSCCB->OperationCode == RESET_COMMAND) अणु
		WRW_HARPOON((port + ID_MSG_STRT), (MPM_OP + AMSG_OUT +
						   (currSCCB->
						    Sccb_idmsg & ~DISC_PRIV)));

		WRW_HARPOON((port + ID_MSG_STRT + 2), BRH_OP + ALWAYS + NP);

		currSCCB->Sccb_scsimsg = SMDEV_RESET;

		WR_HARPOON(port + hp_स्वतःstart_3, (SELECT + SELCHK_STRT));
		स्वतः_loaded = 1;
		currSCCB->Sccb_scsistat = SELECT_BDR_ST;

		अगर (currTar_Info->TarEEValue & EE_SYNC_MASK) अणु
			currTar_Info->TarSyncCtrl = 0;
			currTar_Info->TarStatus &= ~TAR_SYNC_MASK;
		पूर्ण

		अगर (currTar_Info->TarEEValue & EE_WIDE_SCSI) अणु
			currTar_Info->TarStatus &= ~TAR_WIDE_MASK;
		पूर्ण

		FPT_sssyncv(port, target, NARROW_SCSI, currTar_Info);
		FPT_SccbMgrTableInitTarget(p_card, target);

	पूर्ण

	अन्यथा अगर (currSCCB->Sccb_scsistat == ABORT_ST) अणु
		WRW_HARPOON((port + ID_MSG_STRT), (MPM_OP + AMSG_OUT +
						   (currSCCB->
						    Sccb_idmsg & ~DISC_PRIV)));

		WRW_HARPOON((port + ID_MSG_STRT + 2), BRH_OP + ALWAYS + CMDPZ);

		WRW_HARPOON((port + SYNC_MSGS + 0), (MPM_OP + AMSG_OUT +
						     (((अचिन्हित
							अक्षर)(currSCCB->
							      ControlByte &
							      TAG_TYPE_MASK)
						       >> 6) | (अचिन्हित अक्षर)
						      0x20)));
		WRW_HARPOON((port + SYNC_MSGS + 2),
			    (MPM_OP + AMSG_OUT + currSCCB->Sccb_tag));
		WRW_HARPOON((port + SYNC_MSGS + 4), (BRH_OP + ALWAYS + NP));

		WR_HARPOON(port + hp_स्वतःstart_3, (SELECT + SELCHK_STRT));
		स्वतः_loaded = 1;

	पूर्ण

	अन्यथा अगर (!(currTar_Info->TarStatus & WIDE_NEGOCIATED)) अणु
		स्वतः_loaded = FPT_siwidn(port, p_card);
		currSCCB->Sccb_scsistat = SELECT_WN_ST;
	पूर्ण

	अन्यथा अगर (!((currTar_Info->TarStatus & TAR_SYNC_MASK)
		   == SYNC_SUPPORTED)) अणु
		स्वतः_loaded = FPT_sisyncn(port, p_card, 0);
		currSCCB->Sccb_scsistat = SELECT_SN_ST;
	पूर्ण

	अगर (!स्वतः_loaded) अणु

		अगर (currSCCB->ControlByte & F_USE_CMD_Q) अणु

			CurrCard->globalFlags |= F_TAG_STARTED;

			अगर ((currTar_Info->TarStatus & TAR_TAG_Q_MASK)
			    == TAG_Q_REJECT) अणु
				currSCCB->ControlByte &= ~F_USE_CMD_Q;

				/* Fix up the start inकाष्ठाion with a jump to
				   Non-Tag-CMD handling */
				WRW_HARPOON((port + ID_MSG_STRT),
					    BRH_OP + ALWAYS + NTCMD);

				WRW_HARPOON((port + NON_TAG_ID_MSG),
					    (MPM_OP + AMSG_OUT +
					     currSCCB->Sccb_idmsg));

				WR_HARPOON(port + hp_स्वतःstart_3,
					   (SELECT + SELCHK_STRT));

				/* Setup our STATE so we know what happened when
				   the wheels fall off. */
				currSCCB->Sccb_scsistat = SELECT_ST;

				currTar_Info->TarLUNBusy[lun] = 1;
			पूर्ण

			अन्यथा अणु
				WRW_HARPOON((port + ID_MSG_STRT),
					    (MPM_OP + AMSG_OUT +
					     currSCCB->Sccb_idmsg));

				WRW_HARPOON((port + ID_MSG_STRT + 2),
					    (MPM_OP + AMSG_OUT +
					     (((अचिन्हित अक्षर)(currSCCB->
							       ControlByte &
							       TAG_TYPE_MASK)
					       >> 6) | (अचिन्हित अक्षर)0x20)));

				क्रम (i = 1; i < QUEUE_DEPTH; i++) अणु
					अगर (++lastTag >= QUEUE_DEPTH)
						lastTag = 1;
					अगर (CurrCard->discQ_Tbl[lastTag] ==
					    शून्य) अणु
						WRW_HARPOON((port +
							     ID_MSG_STRT + 6),
							    (MPM_OP + AMSG_OUT +
							     lastTag));
						CurrCard->tagQ_Lst = lastTag;
						currSCCB->Sccb_tag = lastTag;
						CurrCard->discQ_Tbl[lastTag] =
						    currSCCB;
						CurrCard->discQCount++;
						अवरोध;
					पूर्ण
				पूर्ण

				अगर (i == QUEUE_DEPTH) अणु
					currTar_Info->TarLUNBusy[lun] = 1;
					FPT_queueSelectFail(CurrCard, p_card);
					SGRAM_ACCESS(port);
					वापस;
				पूर्ण

				currSCCB->Sccb_scsistat = SELECT_Q_ST;

				WR_HARPOON(port + hp_स्वतःstart_3,
					   (SELECT + SELCHK_STRT));
			पूर्ण
		पूर्ण

		अन्यथा अणु

			WRW_HARPOON((port + ID_MSG_STRT),
				    BRH_OP + ALWAYS + NTCMD);

			WRW_HARPOON((port + NON_TAG_ID_MSG),
				    (MPM_OP + AMSG_OUT + currSCCB->Sccb_idmsg));

			currSCCB->Sccb_scsistat = SELECT_ST;

			WR_HARPOON(port + hp_स्वतःstart_3,
				   (SELECT + SELCHK_STRT));
		पूर्ण

		theCCB = (अचिन्हित अक्षर *)&currSCCB->Cdb[0];

		cdb_reg = port + CMD_STRT;

		क्रम (i = 0; i < currSCCB->CdbLength; i++) अणु
			WRW_HARPOON(cdb_reg, (MPM_OP + ACOMMAND + *theCCB));
			cdb_reg += 2;
			theCCB++;
		पूर्ण

		अगर (currSCCB->CdbLength != TWELVE_BYTE_CMD)
			WRW_HARPOON(cdb_reg, (BRH_OP + ALWAYS + NP));

	पूर्ण
	/* स्वतः_loaded */
	WRW_HARPOON((port + hp_fअगरoपढ़ो), (अचिन्हित लघु)0x00);
	WR_HARPOON(port + hp_xferstat, 0x00);

	WRW_HARPOON((port + hp_पूर्णांकstat), (PROG_HLT | TIMEOUT | SEL | BUS_FREE));

	WR_HARPOON(port + hp_portctrl_0, (SCSI_PORT));

	अगर (!(currSCCB->Sccb_MGRFlags & F_DEV_SELECTED)) अणु
		WR_HARPOON(port + hp_scsictrl_0,
			   (SEL_TAR | ENA_ATN | ENA_RESEL | ENA_SCAM_SEL));
	पूर्ण अन्यथा अणु

/*      स्वतः_loaded =  (RD_HARPOON(port+hp_स्वतःstart_3) & (अचिन्हित अक्षर)0x1F);
      स्वतः_loaded |= AUTO_IMMED; */
		स्वतः_loaded = AUTO_IMMED;

		DISABLE_AUTO(port);

		WR_HARPOON(port + hp_स्वतःstart_3, स्वतः_loaded);
	पूर्ण

	SGRAM_ACCESS(port);
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_sres
 *
 * Description: Hookup the correct CCB and handle the incoming messages.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_sres(u32 port, अचिन्हित अक्षर p_card,
		     काष्ठा sccb_card *pCurrCard)
अणु

	अचिन्हित अक्षर our_target, message, lun = 0, tag, msgRetryCount;

	काष्ठा sccb_mgr_tar_info *currTar_Info;
	काष्ठा sccb *currSCCB;

	अगर (pCurrCard->currentSCCB != शून्य) अणु
		currTar_Info =
		    &FPT_sccbMgrTbl[p_card][pCurrCard->currentSCCB->TargID];
		DISABLE_AUTO(port);

		WR_HARPOON((port + hp_scsictrl_0), (ENA_RESEL | ENA_SCAM_SEL));

		currSCCB = pCurrCard->currentSCCB;
		अगर (currSCCB->Sccb_scsistat == SELECT_WN_ST) अणु
			currTar_Info->TarStatus &= ~TAR_WIDE_MASK;
			currSCCB->Sccb_scsistat = BUS_FREE_ST;
		पूर्ण
		अगर (currSCCB->Sccb_scsistat == SELECT_SN_ST) अणु
			currTar_Info->TarStatus &= ~TAR_SYNC_MASK;
			currSCCB->Sccb_scsistat = BUS_FREE_ST;
		पूर्ण
		अगर (((pCurrCard->globalFlags & F_CONLUN_IO) &&
		     ((currTar_Info->TarStatus & TAR_TAG_Q_MASK) !=
		      TAG_Q_TRYING))) अणु
			currTar_Info->TarLUNBusy[currSCCB->Lun] = 0;
			अगर (currSCCB->Sccb_scsistat != ABORT_ST) अणु
				pCurrCard->discQCount--;
				pCurrCard->discQ_Tbl[currTar_Info->
						     LunDiscQ_Idx[currSCCB->
								  Lun]]
				    = शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			currTar_Info->TarLUNBusy[0] = 0;
			अगर (currSCCB->Sccb_tag) अणु
				अगर (currSCCB->Sccb_scsistat != ABORT_ST) अणु
					pCurrCard->discQCount--;
					pCurrCard->discQ_Tbl[currSCCB->
							     Sccb_tag] = शून्य;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (currSCCB->Sccb_scsistat != ABORT_ST) अणु
					pCurrCard->discQCount--;
					pCurrCard->discQ_Tbl[currTar_Info->
							     LunDiscQ_Idx[0]] =
					    शून्य;
				पूर्ण
			पूर्ण
		पूर्ण

		FPT_queueSelectFail(&FPT_BL_Card[p_card], p_card);
	पूर्ण

	WRW_HARPOON((port + hp_fअगरoपढ़ो), (अचिन्हित लघु)0x00);

	our_target = (अचिन्हित अक्षर)(RD_HARPOON(port + hp_select_id) >> 4);
	currTar_Info = &FPT_sccbMgrTbl[p_card][our_target];

	msgRetryCount = 0;
	करो अणु

		currTar_Info = &FPT_sccbMgrTbl[p_card][our_target];
		tag = 0;

		जबतक (!(RD_HARPOON(port + hp_scsisig) & SCSI_REQ)) अणु
			अगर (!(RD_HARPOON(port + hp_scsisig) & SCSI_BSY)) अणु

				WRW_HARPOON((port + hp_पूर्णांकstat), PHASE);
				वापस;
			पूर्ण
		पूर्ण

		WRW_HARPOON((port + hp_पूर्णांकstat), PHASE);
		अगर ((RD_HARPOON(port + hp_scsisig) & S_SCSI_PHZ) == S_MSGI_PH) अणु

			message = FPT_sfm(port, pCurrCard->currentSCCB);
			अगर (message) अणु

				अगर (message <= (0x80 | LUN_MASK)) अणु
					lun = message & (अचिन्हित अक्षर)LUN_MASK;

					अगर ((currTar_Info->
					     TarStatus & TAR_TAG_Q_MASK) ==
					    TAG_Q_TRYING) अणु
						अगर (currTar_Info->TarTagQ_Cnt !=
						    0) अणु

							अगर (!
							    (currTar_Info->
							     TarLUN_CA)) अणु
								ACCEPT_MSG(port);	/*Release the ACK क्रम ID msg. */

								message =
								    FPT_sfm
								    (port,
								     pCurrCard->
								     currentSCCB);
								अगर (message) अणु
									ACCEPT_MSG
									    (port);
								पूर्ण

								अन्यथा
									message
									    = 0;

								अगर (message !=
								    0) अणु
									tag =
									    FPT_sfm
									    (port,
									     pCurrCard->
									     currentSCCB);

									अगर (!
									    (tag))
										message
										    =
										    0;
								पूर्ण

							पूर्ण
							/*C.A. exists! */
						पूर्ण
						/*End Q cnt != 0 */
					पूर्ण
					/*End Tag cmds supported! */
				पूर्ण
				/*End valid ID message.  */
				अन्यथा अणु

					ACCEPT_MSG_ATN(port);
				पूर्ण

			पूर्ण
			/* End good id message. */
			अन्यथा अणु

				message = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			ACCEPT_MSG_ATN(port);

			जबतक (!
			       (RDW_HARPOON((port + hp_पूर्णांकstat)) &
				(PHASE | RESET))
			       && !(RD_HARPOON(port + hp_scsisig) & SCSI_REQ)
			       && (RD_HARPOON(port + hp_scsisig) & SCSI_BSY)) ;

			वापस;
		पूर्ण

		अगर (message == 0) अणु
			msgRetryCount++;
			अगर (msgRetryCount == 1) अणु
				FPT_SendMsg(port, SMPARITY);
			पूर्ण अन्यथा अणु
				FPT_SendMsg(port, SMDEV_RESET);

				FPT_sssyncv(port, our_target, NARROW_SCSI,
					    currTar_Info);

				अगर (FPT_sccbMgrTbl[p_card][our_target].
				    TarEEValue & EE_SYNC_MASK) अणु

					FPT_sccbMgrTbl[p_card][our_target].
					    TarStatus &= ~TAR_SYNC_MASK;

				पूर्ण

				अगर (FPT_sccbMgrTbl[p_card][our_target].
				    TarEEValue & EE_WIDE_SCSI) अणु

					FPT_sccbMgrTbl[p_card][our_target].
					    TarStatus &= ~TAR_WIDE_MASK;
				पूर्ण

				FPT_queueFlushTargSccb(p_card, our_target,
						       SCCB_COMPLETE);
				FPT_SccbMgrTableInitTarget(p_card, our_target);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (message == 0);

	अगर (((pCurrCard->globalFlags & F_CONLUN_IO) &&
	     ((currTar_Info->TarStatus & TAR_TAG_Q_MASK) != TAG_Q_TRYING))) अणु
		currTar_Info->TarLUNBusy[lun] = 1;
		pCurrCard->currentSCCB =
		    pCurrCard->discQ_Tbl[currTar_Info->LunDiscQ_Idx[lun]];
		अगर (pCurrCard->currentSCCB != शून्य) अणु
			ACCEPT_MSG(port);
		पूर्ण अन्यथा अणु
			ACCEPT_MSG_ATN(port);
		पूर्ण
	पूर्ण अन्यथा अणु
		currTar_Info->TarLUNBusy[0] = 1;

		अगर (tag) अणु
			अगर (pCurrCard->discQ_Tbl[tag] != शून्य) अणु
				pCurrCard->currentSCCB =
				    pCurrCard->discQ_Tbl[tag];
				currTar_Info->TarTagQ_Cnt--;
				ACCEPT_MSG(port);
			पूर्ण अन्यथा अणु
				ACCEPT_MSG_ATN(port);
			पूर्ण
		पूर्ण अन्यथा अणु
			pCurrCard->currentSCCB =
			    pCurrCard->discQ_Tbl[currTar_Info->LunDiscQ_Idx[0]];
			अगर (pCurrCard->currentSCCB != शून्य) अणु
				ACCEPT_MSG(port);
			पूर्ण अन्यथा अणु
				ACCEPT_MSG_ATN(port);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (pCurrCard->currentSCCB != शून्य) अणु
		अगर (pCurrCard->currentSCCB->Sccb_scsistat == ABORT_ST) अणु
			/* During Abort Tag command, the target could have got re-selected
			   and completed the command. Check the select Q and हटाओ the CCB
			   अगर it is in the Select Q */
			FPT_queueFindSccb(pCurrCard->currentSCCB, p_card);
		पूर्ण
	पूर्ण

	जबतक (!(RDW_HARPOON((port + hp_पूर्णांकstat)) & (PHASE | RESET)) &&
	       !(RD_HARPOON(port + hp_scsisig) & SCSI_REQ) &&
	       (RD_HARPOON(port + hp_scsisig) & SCSI_BSY)) ;
पूर्ण

अटल व्योम FPT_SendMsg(u32 port, अचिन्हित अक्षर message)
अणु
	जबतक (!(RD_HARPOON(port + hp_scsisig) & SCSI_REQ)) अणु
		अगर (!(RD_HARPOON(port + hp_scsisig) & SCSI_BSY)) अणु

			WRW_HARPOON((port + hp_पूर्णांकstat), PHASE);
			वापस;
		पूर्ण
	पूर्ण

	WRW_HARPOON((port + hp_पूर्णांकstat), PHASE);
	अगर ((RD_HARPOON(port + hp_scsisig) & S_SCSI_PHZ) == S_MSGO_PH) अणु
		WRW_HARPOON((port + hp_पूर्णांकstat),
			    (BUS_FREE | PHASE | XFER_CNT_0));

		WR_HARPOON(port + hp_portctrl_0, SCSI_BUS_EN);

		WR_HARPOON(port + hp_scsidata_0, message);

		WR_HARPOON(port + hp_scsisig, (SCSI_ACK + S_ILL_PH));

		ACCEPT_MSG(port);

		WR_HARPOON(port + hp_portctrl_0, 0x00);

		अगर ((message == SMABORT) || (message == SMDEV_RESET) ||
		    (message == SMABORT_TAG)) अणु
			जबतक (!
			       (RDW_HARPOON((port + hp_पूर्णांकstat)) &
				(BUS_FREE | PHASE))) अणु
			पूर्ण

			अगर (RDW_HARPOON((port + hp_पूर्णांकstat)) & BUS_FREE) अणु
				WRW_HARPOON((port + hp_पूर्णांकstat), BUS_FREE);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_sdecm
 *
 * Description: Determine the proper response to the message from the
 *              target device.
 *
 *---------------------------------------------------------------------*/
अटल व्योम FPT_sdecm(अचिन्हित अक्षर message, u32 port, अचिन्हित अक्षर p_card)
अणु
	काष्ठा sccb *currSCCB;
	काष्ठा sccb_card *CurrCard;
	काष्ठा sccb_mgr_tar_info *currTar_Info;

	CurrCard = &FPT_BL_Card[p_card];
	currSCCB = CurrCard->currentSCCB;

	currTar_Info = &FPT_sccbMgrTbl[p_card][currSCCB->TargID];

	अगर (message == SMREST_DATA_PTR) अणु
		अगर (!(currSCCB->Sccb_XferState & F_NO_DATA_YET)) अणु
			currSCCB->Sccb_ATC = currSCCB->Sccb_savedATC;

			FPT_hostDataXferRestart(currSCCB);
		पूर्ण

		ACCEPT_MSG(port);
		WR_HARPOON(port + hp_स्वतःstart_1,
			   (AUTO_IMMED + DISCONNECT_START));
	पूर्ण

	अन्यथा अगर (message == SMCMD_COMP) अणु

		अगर (currSCCB->Sccb_scsistat == SELECT_Q_ST) अणु
			currTar_Info->TarStatus &=
			    ~(अचिन्हित अक्षर)TAR_TAG_Q_MASK;
			currTar_Info->TarStatus |= (अचिन्हित अक्षर)TAG_Q_REJECT;
		पूर्ण

		ACCEPT_MSG(port);

	पूर्ण

	अन्यथा अगर ((message == SMNO_OP) || (message >= SMIDENT)
		 || (message == SMINIT_RECOVERY) || (message == SMREL_RECOVERY)) अणु

		ACCEPT_MSG(port);
		WR_HARPOON(port + hp_स्वतःstart_1,
			   (AUTO_IMMED + DISCONNECT_START));
	पूर्ण

	अन्यथा अगर (message == SMREJECT) अणु

		अगर ((currSCCB->Sccb_scsistat == SELECT_SN_ST) ||
		    (currSCCB->Sccb_scsistat == SELECT_WN_ST) ||
		    ((currTar_Info->TarStatus & TAR_SYNC_MASK) == SYNC_TRYING)
		    || ((currTar_Info->TarStatus & TAR_TAG_Q_MASK) ==
			TAG_Q_TRYING))
		अणु
			WRW_HARPOON((port + hp_पूर्णांकstat), BUS_FREE);

			ACCEPT_MSG(port);

			जबतक ((!(RD_HARPOON(port + hp_scsisig) & SCSI_REQ)) &&
			       (!(RDW_HARPOON((port + hp_पूर्णांकstat)) & BUS_FREE)))
			अणु
			पूर्ण

			अगर (currSCCB->Lun == 0x00) अणु
				अगर (currSCCB->Sccb_scsistat == SELECT_SN_ST) अणु

					currTar_Info->TarStatus |=
					    (अचिन्हित अक्षर)SYNC_SUPPORTED;

					currTar_Info->TarEEValue &=
					    ~EE_SYNC_MASK;
				पूर्ण

				अन्यथा अगर (currSCCB->Sccb_scsistat ==
					  SELECT_WN_ST) अणु

					currTar_Info->TarStatus =
					    (currTar_Info->
					     TarStatus & ~WIDE_ENABLED) |
					    WIDE_NEGOCIATED;

					currTar_Info->TarEEValue &=
					    ~EE_WIDE_SCSI;

				पूर्ण

				अन्यथा अगर ((currTar_Info->
					  TarStatus & TAR_TAG_Q_MASK) ==
					 TAG_Q_TRYING) अणु
					currTar_Info->TarStatus =
					    (currTar_Info->
					     TarStatus & ~(अचिन्हित अक्षर)
					     TAR_TAG_Q_MASK) | TAG_Q_REJECT;

					currSCCB->ControlByte &= ~F_USE_CMD_Q;
					CurrCard->discQCount--;
					CurrCard->discQ_Tbl[currSCCB->
							    Sccb_tag] = शून्य;
					currSCCB->Sccb_tag = 0x00;

				पूर्ण
			पूर्ण

			अगर (RDW_HARPOON((port + hp_पूर्णांकstat)) & BUS_FREE) अणु

				अगर (currSCCB->Lun == 0x00) अणु
					WRW_HARPOON((port + hp_पूर्णांकstat),
						    BUS_FREE);
					CurrCard->globalFlags |= F_NEW_SCCB_CMD;
				पूर्ण
			पूर्ण

			अन्यथा अणु

				अगर ((CurrCard->globalFlags & F_CONLUN_IO) &&
				    ((currTar_Info->
				      TarStatus & TAR_TAG_Q_MASK) !=
				     TAG_Q_TRYING))
					currTar_Info->TarLUNBusy[currSCCB->
								 Lun] = 1;
				अन्यथा
					currTar_Info->TarLUNBusy[0] = 1;

				currSCCB->ControlByte &=
				    ~(अचिन्हित अक्षर)F_USE_CMD_Q;

				WR_HARPOON(port + hp_स्वतःstart_1,
					   (AUTO_IMMED + DISCONNECT_START));

			पूर्ण
		पूर्ण

		अन्यथा अणु
			ACCEPT_MSG(port);

			जबतक ((!(RD_HARPOON(port + hp_scsisig) & SCSI_REQ)) &&
			       (!(RDW_HARPOON((port + hp_पूर्णांकstat)) & BUS_FREE)))
			अणु
			पूर्ण

			अगर (!(RDW_HARPOON((port + hp_पूर्णांकstat)) & BUS_FREE)) अणु
				WR_HARPOON(port + hp_स्वतःstart_1,
					   (AUTO_IMMED + DISCONNECT_START));
			पूर्ण
		पूर्ण
	पूर्ण

	अन्यथा अगर (message == SMEXT) अणु

		ACCEPT_MSG(port);
		FPT_shandem(port, p_card, currSCCB);
	पूर्ण

	अन्यथा अगर (message == SMIGNORWR) अणु

		ACCEPT_MSG(port);	/* ACK the RESIDUE MSG */

		message = FPT_sfm(port, currSCCB);

		अगर (currSCCB->Sccb_scsimsg != SMPARITY)
			ACCEPT_MSG(port);
		WR_HARPOON(port + hp_स्वतःstart_1,
			   (AUTO_IMMED + DISCONNECT_START));
	पूर्ण

	अन्यथा अणु

		currSCCB->HostStatus = SCCB_PHASE_SEQUENCE_FAIL;
		currSCCB->Sccb_scsimsg = SMREJECT;

		ACCEPT_MSG_ATN(port);
		WR_HARPOON(port + hp_स्वतःstart_1,
			   (AUTO_IMMED + DISCONNECT_START));
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_shandem
 *
 * Description: Decide what to करो with the extended message.
 *
 *---------------------------------------------------------------------*/
अटल व्योम FPT_shandem(u32 port, अचिन्हित अक्षर p_card, काष्ठा sccb *pCurrSCCB)
अणु
	अचिन्हित अक्षर length, message;

	length = FPT_sfm(port, pCurrSCCB);
	अगर (length) अणु

		ACCEPT_MSG(port);
		message = FPT_sfm(port, pCurrSCCB);
		अगर (message) अणु

			अगर (message == SMSYNC) अणु

				अगर (length == 0x03) अणु

					ACCEPT_MSG(port);
					FPT_stsyncn(port, p_card);
				पूर्ण अन्यथा अणु

					pCurrSCCB->Sccb_scsimsg = SMREJECT;
					ACCEPT_MSG_ATN(port);
				पूर्ण
			पूर्ण अन्यथा अगर (message == SMWDTR) अणु

				अगर (length == 0x02) अणु

					ACCEPT_MSG(port);
					FPT_stwidn(port, p_card);
				पूर्ण अन्यथा अणु

					pCurrSCCB->Sccb_scsimsg = SMREJECT;
					ACCEPT_MSG_ATN(port);

					WR_HARPOON(port + hp_स्वतःstart_1,
						   (AUTO_IMMED +
						    DISCONNECT_START));
				पूर्ण
			पूर्ण अन्यथा अणु

				pCurrSCCB->Sccb_scsimsg = SMREJECT;
				ACCEPT_MSG_ATN(port);

				WR_HARPOON(port + hp_स्वतःstart_1,
					   (AUTO_IMMED + DISCONNECT_START));
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (pCurrSCCB->Sccb_scsimsg != SMPARITY)
				ACCEPT_MSG(port);
			WR_HARPOON(port + hp_स्वतःstart_1,
				   (AUTO_IMMED + DISCONNECT_START));
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (pCurrSCCB->Sccb_scsimsg == SMPARITY)
			WR_HARPOON(port + hp_स्वतःstart_1,
				   (AUTO_IMMED + DISCONNECT_START));
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_sisyncn
 *
 * Description: Read in a message byte from the SCSI bus, and check
 *              क्रम a parity error.
 *
 *---------------------------------------------------------------------*/

अटल अचिन्हित अक्षर FPT_sisyncn(u32 port, अचिन्हित अक्षर p_card,
				 अचिन्हित अक्षर syncFlag)
अणु
	काष्ठा sccb *currSCCB;
	काष्ठा sccb_mgr_tar_info *currTar_Info;

	currSCCB = FPT_BL_Card[p_card].currentSCCB;
	currTar_Info = &FPT_sccbMgrTbl[p_card][currSCCB->TargID];

	अगर (!((currTar_Info->TarStatus & TAR_SYNC_MASK) == SYNC_TRYING)) अणु

		WRW_HARPOON((port + ID_MSG_STRT),
			    (MPM_OP + AMSG_OUT +
			     (currSCCB->
			      Sccb_idmsg & ~(अचिन्हित अक्षर)DISC_PRIV)));

		WRW_HARPOON((port + ID_MSG_STRT + 2), BRH_OP + ALWAYS + CMDPZ);

		WRW_HARPOON((port + SYNC_MSGS + 0),
			    (MPM_OP + AMSG_OUT + SMEXT));
		WRW_HARPOON((port + SYNC_MSGS + 2), (MPM_OP + AMSG_OUT + 0x03));
		WRW_HARPOON((port + SYNC_MSGS + 4),
			    (MPM_OP + AMSG_OUT + SMSYNC));

		अगर ((currTar_Info->TarEEValue & EE_SYNC_MASK) == EE_SYNC_20MB)

			WRW_HARPOON((port + SYNC_MSGS + 6),
				    (MPM_OP + AMSG_OUT + 12));

		अन्यथा अगर ((currTar_Info->TarEEValue & EE_SYNC_MASK) ==
			 EE_SYNC_10MB)

			WRW_HARPOON((port + SYNC_MSGS + 6),
				    (MPM_OP + AMSG_OUT + 25));

		अन्यथा अगर ((currTar_Info->TarEEValue & EE_SYNC_MASK) ==
			 EE_SYNC_5MB)

			WRW_HARPOON((port + SYNC_MSGS + 6),
				    (MPM_OP + AMSG_OUT + 50));

		अन्यथा
			WRW_HARPOON((port + SYNC_MSGS + 6),
				    (MPM_OP + AMSG_OUT + 00));

		WRW_HARPOON((port + SYNC_MSGS + 8), (RAT_OP));
		WRW_HARPOON((port + SYNC_MSGS + 10),
			    (MPM_OP + AMSG_OUT + DEFAULT_OFFSET));
		WRW_HARPOON((port + SYNC_MSGS + 12), (BRH_OP + ALWAYS + NP));

		अगर (syncFlag == 0) अणु
			WR_HARPOON(port + hp_स्वतःstart_3,
				   (SELECT + SELCHK_STRT));
			currTar_Info->TarStatus =
			    ((currTar_Info->
			      TarStatus & ~(अचिन्हित अक्षर)TAR_SYNC_MASK) |
			     (अचिन्हित अक्षर)SYNC_TRYING);
		पूर्ण अन्यथा अणु
			WR_HARPOON(port + hp_स्वतःstart_3,
				   (AUTO_IMMED + CMD_ONLY_STRT));
		पूर्ण

		वापस 1;
	पूर्ण

	अन्यथा अणु

		currTar_Info->TarStatus |= (अचिन्हित अक्षर)SYNC_SUPPORTED;
		currTar_Info->TarEEValue &= ~EE_SYNC_MASK;
		वापस 0;
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_stsyncn
 *
 * Description: The has sent us a Sync Nego message so handle it as
 *              necessary.
 *
 *---------------------------------------------------------------------*/
अटल व्योम FPT_stsyncn(u32 port, अचिन्हित अक्षर p_card)
अणु
	अचिन्हित अक्षर sync_msg, offset, sync_reg, our_sync_msg;
	काष्ठा sccb *currSCCB;
	काष्ठा sccb_mgr_tar_info *currTar_Info;

	currSCCB = FPT_BL_Card[p_card].currentSCCB;
	currTar_Info = &FPT_sccbMgrTbl[p_card][currSCCB->TargID];

	sync_msg = FPT_sfm(port, currSCCB);

	अगर ((sync_msg == 0x00) && (currSCCB->Sccb_scsimsg == SMPARITY)) अणु
		WR_HARPOON(port + hp_स्वतःstart_1,
			   (AUTO_IMMED + DISCONNECT_START));
		वापस;
	पूर्ण

	ACCEPT_MSG(port);

	offset = FPT_sfm(port, currSCCB);

	अगर ((offset == 0x00) && (currSCCB->Sccb_scsimsg == SMPARITY)) अणु
		WR_HARPOON(port + hp_स्वतःstart_1,
			   (AUTO_IMMED + DISCONNECT_START));
		वापस;
	पूर्ण

	अगर ((currTar_Info->TarEEValue & EE_SYNC_MASK) == EE_SYNC_20MB)

		our_sync_msg = 12;	/* Setup our Message to 20mb/s */

	अन्यथा अगर ((currTar_Info->TarEEValue & EE_SYNC_MASK) == EE_SYNC_10MB)

		our_sync_msg = 25;	/* Setup our Message to 10mb/s */

	अन्यथा अगर ((currTar_Info->TarEEValue & EE_SYNC_MASK) == EE_SYNC_5MB)

		our_sync_msg = 50;	/* Setup our Message to 5mb/s */
	अन्यथा

		our_sync_msg = 0;	/* Message = Async */

	अगर (sync_msg < our_sync_msg) अणु
		sync_msg = our_sync_msg;	/*अगर faster, then set to max. */
	पूर्ण

	अगर (offset == ASYNC)
		sync_msg = ASYNC;

	अगर (offset > MAX_OFFSET)
		offset = MAX_OFFSET;

	sync_reg = 0x00;

	अगर (sync_msg > 12)

		sync_reg = 0x20;	/* Use 10MB/s */

	अगर (sync_msg > 25)

		sync_reg = 0x40;	/* Use 6.6MB/s */

	अगर (sync_msg > 38)

		sync_reg = 0x60;	/* Use 5MB/s */

	अगर (sync_msg > 50)

		sync_reg = 0x80;	/* Use 4MB/s */

	अगर (sync_msg > 62)

		sync_reg = 0xA0;	/* Use 3.33MB/s */

	अगर (sync_msg > 75)

		sync_reg = 0xC0;	/* Use 2.85MB/s */

	अगर (sync_msg > 87)

		sync_reg = 0xE0;	/* Use 2.5MB/s */

	अगर (sync_msg > 100) अणु

		sync_reg = 0x00;	/* Use ASYNC */
		offset = 0x00;
	पूर्ण

	अगर (currTar_Info->TarStatus & WIDE_ENABLED)

		sync_reg |= offset;

	अन्यथा

		sync_reg |= (offset | NARROW_SCSI);

	FPT_sssyncv(port, currSCCB->TargID, sync_reg, currTar_Info);

	अगर (currSCCB->Sccb_scsistat == SELECT_SN_ST) अणु

		ACCEPT_MSG(port);

		currTar_Info->TarStatus = ((currTar_Info->TarStatus &
					    ~(अचिन्हित अक्षर)TAR_SYNC_MASK) |
					   (अचिन्हित अक्षर)SYNC_SUPPORTED);

		WR_HARPOON(port + hp_स्वतःstart_1,
			   (AUTO_IMMED + DISCONNECT_START));
	पूर्ण

	अन्यथा अणु

		ACCEPT_MSG_ATN(port);

		FPT_sisyncr(port, sync_msg, offset);

		currTar_Info->TarStatus = ((currTar_Info->TarStatus &
					    ~(अचिन्हित अक्षर)TAR_SYNC_MASK) |
					   (अचिन्हित अक्षर)SYNC_SUPPORTED);
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_sisyncr
 *
 * Description: Answer the tarमाला_लो sync message.
 *
 *---------------------------------------------------------------------*/
अटल व्योम FPT_sisyncr(u32 port, अचिन्हित अक्षर sync_pulse,
			अचिन्हित अक्षर offset)
अणु
	ARAM_ACCESS(port);
	WRW_HARPOON((port + SYNC_MSGS + 0), (MPM_OP + AMSG_OUT + SMEXT));
	WRW_HARPOON((port + SYNC_MSGS + 2), (MPM_OP + AMSG_OUT + 0x03));
	WRW_HARPOON((port + SYNC_MSGS + 4), (MPM_OP + AMSG_OUT + SMSYNC));
	WRW_HARPOON((port + SYNC_MSGS + 6), (MPM_OP + AMSG_OUT + sync_pulse));
	WRW_HARPOON((port + SYNC_MSGS + 8), (RAT_OP));
	WRW_HARPOON((port + SYNC_MSGS + 10), (MPM_OP + AMSG_OUT + offset));
	WRW_HARPOON((port + SYNC_MSGS + 12), (BRH_OP + ALWAYS + NP));
	SGRAM_ACCESS(port);

	WR_HARPOON(port + hp_portctrl_0, SCSI_PORT);
	WRW_HARPOON((port + hp_पूर्णांकstat), CLR_ALL_INT_1);

	WR_HARPOON(port + hp_स्वतःstart_3, (AUTO_IMMED + CMD_ONLY_STRT));

	जबतक (!(RDW_HARPOON((port + hp_पूर्णांकstat)) & (BUS_FREE | AUTO_INT))) अणु
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_siwidn
 *
 * Description: Read in a message byte from the SCSI bus, and check
 *              क्रम a parity error.
 *
 *---------------------------------------------------------------------*/

अटल अचिन्हित अक्षर FPT_siwidn(u32 port, अचिन्हित अक्षर p_card)
अणु
	काष्ठा sccb *currSCCB;
	काष्ठा sccb_mgr_tar_info *currTar_Info;

	currSCCB = FPT_BL_Card[p_card].currentSCCB;
	currTar_Info = &FPT_sccbMgrTbl[p_card][currSCCB->TargID];

	अगर (!((currTar_Info->TarStatus & TAR_WIDE_MASK) == WIDE_NEGOCIATED)) अणु

		WRW_HARPOON((port + ID_MSG_STRT),
			    (MPM_OP + AMSG_OUT +
			     (currSCCB->
			      Sccb_idmsg & ~(अचिन्हित अक्षर)DISC_PRIV)));

		WRW_HARPOON((port + ID_MSG_STRT + 2), BRH_OP + ALWAYS + CMDPZ);

		WRW_HARPOON((port + SYNC_MSGS + 0),
			    (MPM_OP + AMSG_OUT + SMEXT));
		WRW_HARPOON((port + SYNC_MSGS + 2), (MPM_OP + AMSG_OUT + 0x02));
		WRW_HARPOON((port + SYNC_MSGS + 4),
			    (MPM_OP + AMSG_OUT + SMWDTR));
		WRW_HARPOON((port + SYNC_MSGS + 6), (RAT_OP));
		WRW_HARPOON((port + SYNC_MSGS + 8),
			    (MPM_OP + AMSG_OUT + SM16BIT));
		WRW_HARPOON((port + SYNC_MSGS + 10), (BRH_OP + ALWAYS + NP));

		WR_HARPOON(port + hp_स्वतःstart_3, (SELECT + SELCHK_STRT));

		currTar_Info->TarStatus = ((currTar_Info->TarStatus &
					    ~(अचिन्हित अक्षर)TAR_WIDE_MASK) |
					   (अचिन्हित अक्षर)WIDE_ENABLED);

		वापस 1;
	पूर्ण

	अन्यथा अणु

		currTar_Info->TarStatus = ((currTar_Info->TarStatus &
					    ~(अचिन्हित अक्षर)TAR_WIDE_MASK) |
					   WIDE_NEGOCIATED);

		currTar_Info->TarEEValue &= ~EE_WIDE_SCSI;
		वापस 0;
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_stwidn
 *
 * Description: The has sent us a Wide Nego message so handle it as
 *              necessary.
 *
 *---------------------------------------------------------------------*/
अटल व्योम FPT_stwidn(u32 port, अचिन्हित अक्षर p_card)
अणु
	अचिन्हित अक्षर width;
	काष्ठा sccb *currSCCB;
	काष्ठा sccb_mgr_tar_info *currTar_Info;

	currSCCB = FPT_BL_Card[p_card].currentSCCB;
	currTar_Info = &FPT_sccbMgrTbl[p_card][currSCCB->TargID];

	width = FPT_sfm(port, currSCCB);

	अगर ((width == 0x00) && (currSCCB->Sccb_scsimsg == SMPARITY)) अणु
		WR_HARPOON(port + hp_स्वतःstart_1,
			   (AUTO_IMMED + DISCONNECT_START));
		वापस;
	पूर्ण

	अगर (!(currTar_Info->TarEEValue & EE_WIDE_SCSI))
		width = 0;

	अगर (width) अणु
		currTar_Info->TarStatus |= WIDE_ENABLED;
		width = 0;
	पूर्ण अन्यथा अणु
		width = NARROW_SCSI;
		currTar_Info->TarStatus &= ~WIDE_ENABLED;
	पूर्ण

	FPT_sssyncv(port, currSCCB->TargID, width, currTar_Info);

	अगर (currSCCB->Sccb_scsistat == SELECT_WN_ST) अणु

		currTar_Info->TarStatus |= WIDE_NEGOCIATED;

		अगर (!
		    ((currTar_Info->TarStatus & TAR_SYNC_MASK) ==
		     SYNC_SUPPORTED)) अणु
			ACCEPT_MSG_ATN(port);
			ARAM_ACCESS(port);
			FPT_sisyncn(port, p_card, 1);
			currSCCB->Sccb_scsistat = SELECT_SN_ST;
			SGRAM_ACCESS(port);
		पूर्ण अन्यथा अणु
			ACCEPT_MSG(port);
			WR_HARPOON(port + hp_स्वतःstart_1,
				   (AUTO_IMMED + DISCONNECT_START));
		पूर्ण
	पूर्ण

	अन्यथा अणु

		ACCEPT_MSG_ATN(port);

		अगर (currTar_Info->TarEEValue & EE_WIDE_SCSI)
			width = SM16BIT;
		अन्यथा
			width = SM8BIT;

		FPT_siwidr(port, width);

		currTar_Info->TarStatus |= (WIDE_NEGOCIATED | WIDE_ENABLED);
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_siwidr
 *
 * Description: Answer the tarमाला_लो Wide nego message.
 *
 *---------------------------------------------------------------------*/
अटल व्योम FPT_siwidr(u32 port, अचिन्हित अक्षर width)
अणु
	ARAM_ACCESS(port);
	WRW_HARPOON((port + SYNC_MSGS + 0), (MPM_OP + AMSG_OUT + SMEXT));
	WRW_HARPOON((port + SYNC_MSGS + 2), (MPM_OP + AMSG_OUT + 0x02));
	WRW_HARPOON((port + SYNC_MSGS + 4), (MPM_OP + AMSG_OUT + SMWDTR));
	WRW_HARPOON((port + SYNC_MSGS + 6), (RAT_OP));
	WRW_HARPOON((port + SYNC_MSGS + 8), (MPM_OP + AMSG_OUT + width));
	WRW_HARPOON((port + SYNC_MSGS + 10), (BRH_OP + ALWAYS + NP));
	SGRAM_ACCESS(port);

	WR_HARPOON(port + hp_portctrl_0, SCSI_PORT);
	WRW_HARPOON((port + hp_पूर्णांकstat), CLR_ALL_INT_1);

	WR_HARPOON(port + hp_स्वतःstart_3, (AUTO_IMMED + CMD_ONLY_STRT));

	जबतक (!(RDW_HARPOON((port + hp_पूर्णांकstat)) & (BUS_FREE | AUTO_INT))) अणु
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_sssyncv
 *
 * Description: Write the desired value to the Sync Register क्रम the
 *              ID specअगरied.
 *
 *---------------------------------------------------------------------*/
अटल व्योम FPT_sssyncv(u32 p_port, अचिन्हित अक्षर p_id,
			अचिन्हित अक्षर p_sync_value,
			काष्ठा sccb_mgr_tar_info *currTar_Info)
अणु
	अचिन्हित अक्षर index;

	index = p_id;

	चयन (index) अणु

	हाल 0:
		index = 12;	/* hp_synctarg_0 */
		अवरोध;
	हाल 1:
		index = 13;	/* hp_synctarg_1 */
		अवरोध;
	हाल 2:
		index = 14;	/* hp_synctarg_2 */
		अवरोध;
	हाल 3:
		index = 15;	/* hp_synctarg_3 */
		अवरोध;
	हाल 4:
		index = 8;	/* hp_synctarg_4 */
		अवरोध;
	हाल 5:
		index = 9;	/* hp_synctarg_5 */
		अवरोध;
	हाल 6:
		index = 10;	/* hp_synctarg_6 */
		अवरोध;
	हाल 7:
		index = 11;	/* hp_synctarg_7 */
		अवरोध;
	हाल 8:
		index = 4;	/* hp_synctarg_8 */
		अवरोध;
	हाल 9:
		index = 5;	/* hp_synctarg_9 */
		अवरोध;
	हाल 10:
		index = 6;	/* hp_synctarg_10 */
		अवरोध;
	हाल 11:
		index = 7;	/* hp_synctarg_11 */
		अवरोध;
	हाल 12:
		index = 0;	/* hp_synctarg_12 */
		अवरोध;
	हाल 13:
		index = 1;	/* hp_synctarg_13 */
		अवरोध;
	हाल 14:
		index = 2;	/* hp_synctarg_14 */
		अवरोध;
	हाल 15:
		index = 3;	/* hp_synctarg_15 */

	पूर्ण

	WR_HARPOON(p_port + hp_synctarg_base + index, p_sync_value);

	currTar_Info->TarSyncCtrl = p_sync_value;
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_sresb
 *
 * Description: Reset the desired card's SCSI bus.
 *
 *---------------------------------------------------------------------*/
अटल व्योम FPT_sresb(u32 port, अचिन्हित अक्षर p_card)
अणु
	अचिन्हित अक्षर scsiID, i;

	काष्ठा sccb_mgr_tar_info *currTar_Info;

	WR_HARPOON(port + hp_page_ctrl,
		   (RD_HARPOON(port + hp_page_ctrl) | G_INT_DISABLE));
	WRW_HARPOON((port + hp_पूर्णांकstat), CLR_ALL_INT);

	WR_HARPOON(port + hp_scsictrl_0, SCSI_RST);

	scsiID = RD_HARPOON(port + hp_selसमयout);
	WR_HARPOON(port + hp_selसमयout, TO_5ms);
	WRW_HARPOON((port + hp_पूर्णांकstat), TIMEOUT);

	WR_HARPOON(port + hp_portctrl_0, (SCSI_PORT | START_TO));

	जबतक (!(RDW_HARPOON((port + hp_पूर्णांकstat)) & TIMEOUT)) अणु
	पूर्ण

	WR_HARPOON(port + hp_selसमयout, scsiID);

	WR_HARPOON(port + hp_scsictrl_0, ENA_SCAM_SEL);

	FPT_Wait(port, TO_5ms);

	WRW_HARPOON((port + hp_पूर्णांकstat), CLR_ALL_INT);

	WR_HARPOON(port + hp_पूर्णांक_mask, (RD_HARPOON(port + hp_पूर्णांक_mask) | 0x00));

	क्रम (scsiID = 0; scsiID < MAX_SCSI_TAR; scsiID++) अणु
		currTar_Info = &FPT_sccbMgrTbl[p_card][scsiID];

		अगर (currTar_Info->TarEEValue & EE_SYNC_MASK) अणु
			currTar_Info->TarSyncCtrl = 0;
			currTar_Info->TarStatus &= ~TAR_SYNC_MASK;
		पूर्ण

		अगर (currTar_Info->TarEEValue & EE_WIDE_SCSI) अणु
			currTar_Info->TarStatus &= ~TAR_WIDE_MASK;
		पूर्ण

		FPT_sssyncv(port, scsiID, NARROW_SCSI, currTar_Info);

		FPT_SccbMgrTableInitTarget(p_card, scsiID);
	पूर्ण

	FPT_BL_Card[p_card].scanIndex = 0x00;
	FPT_BL_Card[p_card].currentSCCB = शून्य;
	FPT_BL_Card[p_card].globalFlags &= ~(F_TAG_STARTED | F_HOST_XFER_ACT
					     | F_NEW_SCCB_CMD);
	FPT_BL_Card[p_card].cmdCounter = 0x00;
	FPT_BL_Card[p_card].discQCount = 0x00;
	FPT_BL_Card[p_card].tagQ_Lst = 0x01;

	क्रम (i = 0; i < QUEUE_DEPTH; i++)
		FPT_BL_Card[p_card].discQ_Tbl[i] = शून्य;

	WR_HARPOON(port + hp_page_ctrl,
		   (RD_HARPOON(port + hp_page_ctrl) & ~G_INT_DISABLE));

पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_ssenss
 *
 * Description: Setup क्रम the Auto Sense command.
 *
 *---------------------------------------------------------------------*/
अटल व्योम FPT_ssenss(काष्ठा sccb_card *pCurrCard)
अणु
	अचिन्हित अक्षर i;
	काष्ठा sccb *currSCCB;

	currSCCB = pCurrCard->currentSCCB;

	currSCCB->Save_CdbLen = currSCCB->CdbLength;

	क्रम (i = 0; i < 6; i++) अणु

		currSCCB->Save_Cdb[i] = currSCCB->Cdb[i];
	पूर्ण

	currSCCB->CdbLength = SIX_BYTE_CMD;
	currSCCB->Cdb[0] = SCSI_REQUEST_SENSE;
	currSCCB->Cdb[1] = currSCCB->Cdb[1] & (अचिन्हित अक्षर)0xE0;	/*Keep LUN. */
	currSCCB->Cdb[2] = 0x00;
	currSCCB->Cdb[3] = 0x00;
	currSCCB->Cdb[4] = currSCCB->RequestSenseLength;
	currSCCB->Cdb[5] = 0x00;

	currSCCB->Sccb_XferCnt = (u32)currSCCB->RequestSenseLength;

	currSCCB->Sccb_ATC = 0x00;

	currSCCB->Sccb_XferState |= F_AUTO_SENSE;

	currSCCB->Sccb_XferState &= ~F_SG_XFER;

	currSCCB->Sccb_idmsg = currSCCB->Sccb_idmsg & ~(अचिन्हित अक्षर)DISC_PRIV;

	currSCCB->ControlByte = 0x00;

	currSCCB->Sccb_MGRFlags &= F_STATUSLOADED;
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_sxfrp
 *
 * Description: Transfer data पूर्णांकo the bit bucket until the device
 *              decides to चयन phase.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_sxfrp(u32 p_port, अचिन्हित अक्षर p_card)
अणु
	अचिन्हित अक्षर curr_phz;

	DISABLE_AUTO(p_port);

	अगर (FPT_BL_Card[p_card].globalFlags & F_HOST_XFER_ACT) अणु

		FPT_hostDataXferAbort(p_port, p_card,
				      FPT_BL_Card[p_card].currentSCCB);

	पूर्ण

	/* If the Automation handled the end of the transfer then करो not
	   match the phase or we will get out of sync with the ISR.       */

	अगर (RDW_HARPOON((p_port + hp_पूर्णांकstat)) &
	    (BUS_FREE | XFER_CNT_0 | AUTO_INT))
		वापस;

	WR_HARPOON(p_port + hp_xfercnt_0, 0x00);

	curr_phz = RD_HARPOON(p_port + hp_scsisig) & (अचिन्हित अक्षर)S_SCSI_PHZ;

	WRW_HARPOON((p_port + hp_पूर्णांकstat), XFER_CNT_0);

	WR_HARPOON(p_port + hp_scsisig, curr_phz);

	जबतक (!(RDW_HARPOON((p_port + hp_पूर्णांकstat)) & (BUS_FREE | RESET)) &&
	       (curr_phz ==
		(RD_HARPOON(p_port + hp_scsisig) & (अचिन्हित अक्षर)S_SCSI_PHZ)))
	अणु
		अगर (curr_phz & (अचिन्हित अक्षर)SCSI_IOBIT) अणु
			WR_HARPOON(p_port + hp_portctrl_0,
				   (SCSI_PORT | HOST_PORT | SCSI_INBIT));

			अगर (!(RD_HARPOON(p_port + hp_xferstat) & FIFO_EMPTY)) अणु
				RD_HARPOON(p_port + hp_fअगरodata_0);
			पूर्ण
		पूर्ण अन्यथा अणु
			WR_HARPOON(p_port + hp_portctrl_0,
				   (SCSI_PORT | HOST_PORT | HOST_WRT));
			अगर (RD_HARPOON(p_port + hp_xferstat) & FIFO_EMPTY) अणु
				WR_HARPOON(p_port + hp_fअगरodata_0, 0xFA);
			पूर्ण
		पूर्ण
	पूर्ण			/* End of While loop क्रम padding data I/O phase */

	जबतक (!(RDW_HARPOON((p_port + hp_पूर्णांकstat)) & (BUS_FREE | RESET))) अणु
		अगर (RD_HARPOON(p_port + hp_scsisig) & SCSI_REQ)
			अवरोध;
	पूर्ण

	WR_HARPOON(p_port + hp_portctrl_0,
		   (SCSI_PORT | HOST_PORT | SCSI_INBIT));
	जबतक (!(RD_HARPOON(p_port + hp_xferstat) & FIFO_EMPTY)) अणु
		RD_HARPOON(p_port + hp_fअगरodata_0);
	पूर्ण

	अगर (!(RDW_HARPOON((p_port + hp_पूर्णांकstat)) & (BUS_FREE | RESET))) अणु
		WR_HARPOON(p_port + hp_स्वतःstart_0,
			   (AUTO_IMMED + DISCONNECT_START));
		जबतक (!(RDW_HARPOON((p_port + hp_पूर्णांकstat)) & AUTO_INT)) अणु
		पूर्ण

		अगर (RDW_HARPOON((p_port + hp_पूर्णांकstat)) &
		    (ICMD_COMP | ITAR_DISC))
			जबतक (!
			       (RDW_HARPOON((p_port + hp_पूर्णांकstat)) &
				(BUS_FREE | RSEL))) ;
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_schkdd
 *
 * Description: Make sure data has been flushed from both FIFOs and पात
 *              the operations अगर necessary.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_schkdd(u32 port, अचिन्हित अक्षर p_card)
अणु
	अचिन्हित लघु TimeOutLoop;
	अचिन्हित अक्षर sPhase;

	काष्ठा sccb *currSCCB;

	currSCCB = FPT_BL_Card[p_card].currentSCCB;

	अगर ((currSCCB->Sccb_scsistat != DATA_OUT_ST) &&
	    (currSCCB->Sccb_scsistat != DATA_IN_ST)) अणु
		वापस;
	पूर्ण

	अगर (currSCCB->Sccb_XferState & F_ODD_BALL_CNT) अणु

		currSCCB->Sccb_ATC += (currSCCB->Sccb_XferCnt - 1);

		currSCCB->Sccb_XferCnt = 1;

		currSCCB->Sccb_XferState &= ~F_ODD_BALL_CNT;
		WRW_HARPOON((port + hp_fअगरoपढ़ो), (अचिन्हित लघु)0x00);
		WR_HARPOON(port + hp_xferstat, 0x00);
	पूर्ण

	अन्यथा अणु

		currSCCB->Sccb_ATC += currSCCB->Sccb_XferCnt;

		currSCCB->Sccb_XferCnt = 0;
	पूर्ण

	अगर ((RDW_HARPOON((port + hp_पूर्णांकstat)) & PARITY) &&
	    (currSCCB->HostStatus == SCCB_COMPLETE)) अणु

		currSCCB->HostStatus = SCCB_PARITY_ERR;
		WRW_HARPOON((port + hp_पूर्णांकstat), PARITY);
	पूर्ण

	FPT_hostDataXferAbort(port, p_card, currSCCB);

	जबतक (RD_HARPOON(port + hp_scsisig) & SCSI_ACK) अणु
	पूर्ण

	TimeOutLoop = 0;

	जबतक (RD_HARPOON(port + hp_xferstat) & FIFO_EMPTY) अणु
		अगर (RDW_HARPOON((port + hp_पूर्णांकstat)) & BUS_FREE) अणु
			वापस;
		पूर्ण
		अगर (RD_HARPOON(port + hp_offsetctr) & (अचिन्हित अक्षर)0x1F) अणु
			अवरोध;
		पूर्ण
		अगर (RDW_HARPOON((port + hp_पूर्णांकstat)) & RESET) अणु
			वापस;
		पूर्ण
		अगर ((RD_HARPOON(port + hp_scsisig) & SCSI_REQ)
		    || (TimeOutLoop++ > 0x3000))
			अवरोध;
	पूर्ण

	sPhase = RD_HARPOON(port + hp_scsisig) & (SCSI_BSY | S_SCSI_PHZ);
	अगर ((!(RD_HARPOON(port + hp_xferstat) & FIFO_EMPTY)) ||
	    (RD_HARPOON(port + hp_offsetctr) & (अचिन्हित अक्षर)0x1F) ||
	    (sPhase == (SCSI_BSY | S_DATAO_PH)) ||
	    (sPhase == (SCSI_BSY | S_DATAI_PH))) अणु

		WR_HARPOON(port + hp_portctrl_0, SCSI_PORT);

		अगर (!(currSCCB->Sccb_XferState & F_ALL_XFERRED)) अणु
			अगर (currSCCB->Sccb_XferState & F_HOST_XFER_सूची) अणु
				FPT_phaseDataIn(port, p_card);
			पूर्ण

			अन्यथा अणु
				FPT_phaseDataOut(port, p_card);
			पूर्ण
		पूर्ण अन्यथा अणु
			FPT_sxfrp(port, p_card);
			अगर (!(RDW_HARPOON((port + hp_पूर्णांकstat)) &
			      (BUS_FREE | ICMD_COMP | ITAR_DISC | RESET))) अणु
				WRW_HARPOON((port + hp_पूर्णांकstat), AUTO_INT);
				FPT_phaseDecode(port, p_card);
			पूर्ण
		पूर्ण

	पूर्ण

	अन्यथा अणु
		WR_HARPOON(port + hp_portctrl_0, 0x00);
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_sinits
 *
 * Description: Setup SCCB manager fields in this SCCB.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_sinits(काष्ठा sccb *p_sccb, अचिन्हित अक्षर p_card)
अणु
	काष्ठा sccb_mgr_tar_info *currTar_Info;

	अगर ((p_sccb->TargID >= MAX_SCSI_TAR) || (p_sccb->Lun >= MAX_LUN)) अणु
		वापस;
	पूर्ण
	currTar_Info = &FPT_sccbMgrTbl[p_card][p_sccb->TargID];

	p_sccb->Sccb_XferState = 0x00;
	p_sccb->Sccb_XferCnt = p_sccb->DataLength;

	अगर ((p_sccb->OperationCode == SCATTER_GATHER_COMMAND) ||
	    (p_sccb->OperationCode == RESIDUAL_SG_COMMAND)) अणु

		p_sccb->Sccb_SGoffset = 0;
		p_sccb->Sccb_XferState = F_SG_XFER;
		p_sccb->Sccb_XferCnt = 0x00;
	पूर्ण

	अगर (p_sccb->DataLength == 0x00)

		p_sccb->Sccb_XferState |= F_ALL_XFERRED;

	अगर (p_sccb->ControlByte & F_USE_CMD_Q) अणु
		अगर ((currTar_Info->TarStatus & TAR_TAG_Q_MASK) == TAG_Q_REJECT)
			p_sccb->ControlByte &= ~F_USE_CMD_Q;

		अन्यथा
			currTar_Info->TarStatus |= TAG_Q_TRYING;
	पूर्ण

/*      For !single SCSI device in प्रणाली  & device allow Disconnect
	or command is tag_q type then send Cmd with Disconnect Enable
	अन्यथा send Cmd with Disconnect Disable */

/*
   अगर (((!(FPT_BL_Card[p_card].globalFlags & F_SINGLE_DEVICE)) &&
      (currTar_Info->TarStatus & TAR_ALLOW_DISC)) ||
      (currTar_Info->TarStatus & TAG_Q_TRYING)) अणु
*/
	अगर ((currTar_Info->TarStatus & TAR_ALLOW_DISC) ||
	    (currTar_Info->TarStatus & TAG_Q_TRYING)) अणु
		p_sccb->Sccb_idmsg =
		    (अचिन्हित अक्षर)(SMIDENT | DISC_PRIV) | p_sccb->Lun;
	पूर्ण

	अन्यथा अणु

		p_sccb->Sccb_idmsg = (अचिन्हित अक्षर)SMIDENT | p_sccb->Lun;
	पूर्ण

	p_sccb->HostStatus = 0x00;
	p_sccb->TargetStatus = 0x00;
	p_sccb->Sccb_tag = 0x00;
	p_sccb->Sccb_MGRFlags = 0x00;
	p_sccb->Sccb_sgseg = 0x00;
	p_sccb->Sccb_ATC = 0x00;
	p_sccb->Sccb_savedATC = 0x00;
/*
   p_sccb->SccbVirtDataPtr    = 0x00;
   p_sccb->Sccb_क्रमwardlink   = शून्य;
   p_sccb->Sccb_backlink      = शून्य;
 */
	p_sccb->Sccb_scsistat = BUS_FREE_ST;
	p_sccb->SccbStatus = SCCB_IN_PROCESS;
	p_sccb->Sccb_scsimsg = SMNO_OP;

पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Phase Decode
 *
 * Description: Determine the phase and call the appropriate function.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_phaseDecode(u32 p_port, अचिन्हित अक्षर p_card)
अणु
	अचिन्हित अक्षर phase_ref;
	व्योम (*phase) (u32, अचिन्हित अक्षर);

	DISABLE_AUTO(p_port);

	phase_ref =
	    (अचिन्हित अक्षर)(RD_HARPOON(p_port + hp_scsisig) & S_SCSI_PHZ);

	phase = FPT_s_PhaseTbl[phase_ref];

	(*phase) (p_port, p_card);	/* Call the correct phase func */
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Data Out Phase
 *
 * Description: Start up both the BusMaster and Xbow.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_phaseDataOut(u32 port, अचिन्हित अक्षर p_card)
अणु

	काष्ठा sccb *currSCCB;

	currSCCB = FPT_BL_Card[p_card].currentSCCB;
	अगर (currSCCB == शून्य) अणु
		वापस;		/* Exit अगर No SCCB record */
	पूर्ण

	currSCCB->Sccb_scsistat = DATA_OUT_ST;
	currSCCB->Sccb_XferState &= ~(F_HOST_XFER_सूची | F_NO_DATA_YET);

	WR_HARPOON(port + hp_portctrl_0, SCSI_PORT);

	WRW_HARPOON((port + hp_पूर्णांकstat), XFER_CNT_0);

	WR_HARPOON(port + hp_स्वतःstart_0, (END_DATA + END_DATA_START));

	FPT_dataXferProcessor(port, &FPT_BL_Card[p_card]);

	अगर (currSCCB->Sccb_XferCnt == 0) अणु

		अगर ((currSCCB->ControlByte & SCCB_DATA_XFER_OUT) &&
		    (currSCCB->HostStatus == SCCB_COMPLETE))
			currSCCB->HostStatus = SCCB_DATA_OVER_RUN;

		FPT_sxfrp(port, p_card);
		अगर (!(RDW_HARPOON((port + hp_पूर्णांकstat)) & (BUS_FREE | RESET)))
			FPT_phaseDecode(port, p_card);
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Data In Phase
 *
 * Description: Startup the BusMaster and the XBOW.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_phaseDataIn(u32 port, अचिन्हित अक्षर p_card)
अणु

	काष्ठा sccb *currSCCB;

	currSCCB = FPT_BL_Card[p_card].currentSCCB;

	अगर (currSCCB == शून्य) अणु
		वापस;		/* Exit अगर No SCCB record */
	पूर्ण

	currSCCB->Sccb_scsistat = DATA_IN_ST;
	currSCCB->Sccb_XferState |= F_HOST_XFER_सूची;
	currSCCB->Sccb_XferState &= ~F_NO_DATA_YET;

	WR_HARPOON(port + hp_portctrl_0, SCSI_PORT);

	WRW_HARPOON((port + hp_पूर्णांकstat), XFER_CNT_0);

	WR_HARPOON(port + hp_स्वतःstart_0, (END_DATA + END_DATA_START));

	FPT_dataXferProcessor(port, &FPT_BL_Card[p_card]);

	अगर (currSCCB->Sccb_XferCnt == 0) अणु

		अगर ((currSCCB->ControlByte & SCCB_DATA_XFER_IN) &&
		    (currSCCB->HostStatus == SCCB_COMPLETE))
			currSCCB->HostStatus = SCCB_DATA_OVER_RUN;

		FPT_sxfrp(port, p_card);
		अगर (!(RDW_HARPOON((port + hp_पूर्णांकstat)) & (BUS_FREE | RESET)))
			FPT_phaseDecode(port, p_card);

	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Command Phase
 *
 * Description: Load the CDB पूर्णांकo the स्वतःmation and start it up.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_phaseCommand(u32 p_port, अचिन्हित अक्षर p_card)
अणु
	काष्ठा sccb *currSCCB;
	u32 cdb_reg;
	अचिन्हित अक्षर i;

	currSCCB = FPT_BL_Card[p_card].currentSCCB;

	अगर (currSCCB->OperationCode == RESET_COMMAND) अणु

		currSCCB->HostStatus = SCCB_PHASE_SEQUENCE_FAIL;
		currSCCB->CdbLength = SIX_BYTE_CMD;
	पूर्ण

	WR_HARPOON(p_port + hp_scsisig, 0x00);

	ARAM_ACCESS(p_port);

	cdb_reg = p_port + CMD_STRT;

	क्रम (i = 0; i < currSCCB->CdbLength; i++) अणु

		अगर (currSCCB->OperationCode == RESET_COMMAND)

			WRW_HARPOON(cdb_reg, (MPM_OP + ACOMMAND + 0x00));

		अन्यथा
			WRW_HARPOON(cdb_reg,
				    (MPM_OP + ACOMMAND + currSCCB->Cdb[i]));
		cdb_reg += 2;
	पूर्ण

	अगर (currSCCB->CdbLength != TWELVE_BYTE_CMD)
		WRW_HARPOON(cdb_reg, (BRH_OP + ALWAYS + NP));

	WR_HARPOON(p_port + hp_portctrl_0, (SCSI_PORT));

	currSCCB->Sccb_scsistat = COMMAND_ST;

	WR_HARPOON(p_port + hp_स्वतःstart_3, (AUTO_IMMED | CMD_ONLY_STRT));
	SGRAM_ACCESS(p_port);
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Status phase
 *
 * Description: Bring in the status and command complete message bytes
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_phaseStatus(u32 port, अचिन्हित अक्षर p_card)
अणु
	/* Start-up the स्वतःmation to finish off this command and let the
	   isr handle the पूर्णांकerrupt क्रम command complete when it comes in.
	   We could रुको here क्रम the पूर्णांकerrupt to be generated?
	 */

	WR_HARPOON(port + hp_scsisig, 0x00);

	WR_HARPOON(port + hp_स्वतःstart_0, (AUTO_IMMED + END_DATA_START));
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Phase Message Out
 *
 * Description: Send out our message (अगर we have one) and handle whatever
 *              अन्यथा is involed.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_phaseMsgOut(u32 port, अचिन्हित अक्षर p_card)
अणु
	अचिन्हित अक्षर message, scsiID;
	काष्ठा sccb *currSCCB;
	काष्ठा sccb_mgr_tar_info *currTar_Info;

	currSCCB = FPT_BL_Card[p_card].currentSCCB;

	अगर (currSCCB != शून्य) अणु

		message = currSCCB->Sccb_scsimsg;
		scsiID = currSCCB->TargID;

		अगर (message == SMDEV_RESET) अणु

			currTar_Info = &FPT_sccbMgrTbl[p_card][scsiID];
			currTar_Info->TarSyncCtrl = 0;
			FPT_sssyncv(port, scsiID, NARROW_SCSI, currTar_Info);

			अगर (FPT_sccbMgrTbl[p_card][scsiID].
			    TarEEValue & EE_SYNC_MASK) अणु

				FPT_sccbMgrTbl[p_card][scsiID].TarStatus &=
				    ~TAR_SYNC_MASK;

			पूर्ण

			अगर (FPT_sccbMgrTbl[p_card][scsiID].
			    TarEEValue & EE_WIDE_SCSI) अणु

				FPT_sccbMgrTbl[p_card][scsiID].TarStatus &=
				    ~TAR_WIDE_MASK;
			पूर्ण

			FPT_queueFlushSccb(p_card, SCCB_COMPLETE);
			FPT_SccbMgrTableInitTarget(p_card, scsiID);
		पूर्ण अन्यथा अगर (currSCCB->Sccb_scsistat == ABORT_ST) अणु
			currSCCB->HostStatus = SCCB_COMPLETE;
			अगर (FPT_BL_Card[p_card].discQ_Tbl[currSCCB->Sccb_tag] !=
			    शून्य) अणु
				FPT_BL_Card[p_card].discQ_Tbl[currSCCB->
							      Sccb_tag] = शून्य;
				FPT_sccbMgrTbl[p_card][scsiID].TarTagQ_Cnt--;
			पूर्ण

		पूर्ण

		अन्यथा अगर (currSCCB->Sccb_scsistat < COMMAND_ST) अणु

			अगर (message == SMNO_OP) अणु
				currSCCB->Sccb_MGRFlags |= F_DEV_SELECTED;

				FPT_ssel(port, p_card);
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु

			अगर (message == SMABORT)

				FPT_queueFlushSccb(p_card, SCCB_COMPLETE);
		पूर्ण

	पूर्ण अन्यथा अणु
		message = SMABORT;
	पूर्ण

	WRW_HARPOON((port + hp_पूर्णांकstat), (BUS_FREE | PHASE | XFER_CNT_0));

	WR_HARPOON(port + hp_portctrl_0, SCSI_BUS_EN);

	WR_HARPOON(port + hp_scsidata_0, message);

	WR_HARPOON(port + hp_scsisig, (SCSI_ACK + S_ILL_PH));

	ACCEPT_MSG(port);

	WR_HARPOON(port + hp_portctrl_0, 0x00);

	अगर ((message == SMABORT) || (message == SMDEV_RESET) ||
	    (message == SMABORT_TAG)) अणु

		जबतक (!(RDW_HARPOON((port + hp_पूर्णांकstat)) & (BUS_FREE | PHASE))) अणु
		पूर्ण

		अगर (RDW_HARPOON((port + hp_पूर्णांकstat)) & BUS_FREE) अणु
			WRW_HARPOON((port + hp_पूर्णांकstat), BUS_FREE);

			अगर (currSCCB != शून्य) अणु

				अगर ((FPT_BL_Card[p_card].
				     globalFlags & F_CONLUN_IO)
				    &&
				    ((FPT_sccbMgrTbl[p_card][currSCCB->TargID].
				      TarStatus & TAR_TAG_Q_MASK) !=
				     TAG_Q_TRYING))
					FPT_sccbMgrTbl[p_card][currSCCB->
							       TargID].
					    TarLUNBusy[currSCCB->Lun] = 0;
				अन्यथा
					FPT_sccbMgrTbl[p_card][currSCCB->
							       TargID].
					    TarLUNBusy[0] = 0;

				FPT_queueCmdComplete(&FPT_BL_Card[p_card],
						     currSCCB, p_card);
			पूर्ण

			अन्यथा अणु
				FPT_BL_Card[p_card].globalFlags |=
				    F_NEW_SCCB_CMD;
			पूर्ण
		पूर्ण

		अन्यथा अणु

			FPT_sxfrp(port, p_card);
		पूर्ण
	पूर्ण

	अन्यथा अणु

		अगर (message == SMPARITY) अणु
			currSCCB->Sccb_scsimsg = SMNO_OP;
			WR_HARPOON(port + hp_स्वतःstart_1,
				   (AUTO_IMMED + DISCONNECT_START));
		पूर्ण अन्यथा अणु
			FPT_sxfrp(port, p_card);
		पूर्ण
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Message In phase
 *
 * Description: Bring in the message and determine what to करो with it.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_phaseMsgIn(u32 port, अचिन्हित अक्षर p_card)
अणु
	अचिन्हित अक्षर message;
	काष्ठा sccb *currSCCB;

	currSCCB = FPT_BL_Card[p_card].currentSCCB;

	अगर (FPT_BL_Card[p_card].globalFlags & F_HOST_XFER_ACT) अणु

		FPT_phaseChkFअगरo(port, p_card);
	पूर्ण

	message = RD_HARPOON(port + hp_scsidata_0);
	अगर ((message == SMDISC) || (message == SMSAVE_DATA_PTR)) अणु

		WR_HARPOON(port + hp_स्वतःstart_1,
			   (AUTO_IMMED + END_DATA_START));

	पूर्ण

	अन्यथा अणु

		message = FPT_sfm(port, currSCCB);
		अगर (message) अणु

			FPT_sdecm(message, port, p_card);

		पूर्ण अन्यथा अणु
			अगर (currSCCB->Sccb_scsimsg != SMPARITY)
				ACCEPT_MSG(port);
			WR_HARPOON(port + hp_स्वतःstart_1,
				   (AUTO_IMMED + DISCONNECT_START));
		पूर्ण
	पूर्ण

पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Illegal phase
 *
 * Description: Target चयनed to some illegal phase, so all we can करो
 *              is report an error back to the host (अगर that is possible)
 *              and send an ABORT message to the misbehaving target.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_phaseIllegal(u32 port, अचिन्हित अक्षर p_card)
अणु
	काष्ठा sccb *currSCCB;

	currSCCB = FPT_BL_Card[p_card].currentSCCB;

	WR_HARPOON(port + hp_scsisig, RD_HARPOON(port + hp_scsisig));
	अगर (currSCCB != शून्य) अणु

		currSCCB->HostStatus = SCCB_PHASE_SEQUENCE_FAIL;
		currSCCB->Sccb_scsistat = ABORT_ST;
		currSCCB->Sccb_scsimsg = SMABORT;
	पूर्ण

	ACCEPT_MSG_ATN(port);
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Phase Check FIFO
 *
 * Description: Make sure data has been flushed from both FIFOs and पात
 *              the operations अगर necessary.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_phaseChkFअगरo(u32 port, अचिन्हित अक्षर p_card)
अणु
	u32 xfercnt;
	काष्ठा sccb *currSCCB;

	currSCCB = FPT_BL_Card[p_card].currentSCCB;

	अगर (currSCCB->Sccb_scsistat == DATA_IN_ST) अणु

		जबतक ((!(RD_HARPOON(port + hp_xferstat) & FIFO_EMPTY)) &&
		       (RD_HARPOON(port + hp_ext_status) & BM_CMD_BUSY)) अणु
		पूर्ण

		अगर (!(RD_HARPOON(port + hp_xferstat) & FIFO_EMPTY)) अणु
			currSCCB->Sccb_ATC += currSCCB->Sccb_XferCnt;

			currSCCB->Sccb_XferCnt = 0;

			अगर ((RDW_HARPOON((port + hp_पूर्णांकstat)) & PARITY) &&
			    (currSCCB->HostStatus == SCCB_COMPLETE)) अणु
				currSCCB->HostStatus = SCCB_PARITY_ERR;
				WRW_HARPOON((port + hp_पूर्णांकstat), PARITY);
			पूर्ण

			FPT_hostDataXferAbort(port, p_card, currSCCB);

			FPT_dataXferProcessor(port, &FPT_BL_Card[p_card]);

			जबतक ((!(RD_HARPOON(port + hp_xferstat) & FIFO_EMPTY))
			       && (RD_HARPOON(port + hp_ext_status) &
				   BM_CMD_BUSY)) अणु
			पूर्ण

		पूर्ण
	पूर्ण

	/*End Data In specअगरic code. */
	GET_XFER_CNT(port, xfercnt);

	WR_HARPOON(port + hp_xfercnt_0, 0x00);

	WR_HARPOON(port + hp_portctrl_0, 0x00);

	currSCCB->Sccb_ATC += (currSCCB->Sccb_XferCnt - xfercnt);

	currSCCB->Sccb_XferCnt = xfercnt;

	अगर ((RDW_HARPOON((port + hp_पूर्णांकstat)) & PARITY) &&
	    (currSCCB->HostStatus == SCCB_COMPLETE)) अणु

		currSCCB->HostStatus = SCCB_PARITY_ERR;
		WRW_HARPOON((port + hp_पूर्णांकstat), PARITY);
	पूर्ण

	FPT_hostDataXferAbort(port, p_card, currSCCB);

	WR_HARPOON(port + hp_fअगरoग_लिखो, 0x00);
	WR_HARPOON(port + hp_fअगरoपढ़ो, 0x00);
	WR_HARPOON(port + hp_xferstat, 0x00);

	WRW_HARPOON((port + hp_पूर्णांकstat), XFER_CNT_0);
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Phase Bus Free
 *
 * Description: We just went bus मुक्त so figure out अगर it was
 *              because of command complete or from a disconnect.
 *
 *---------------------------------------------------------------------*/
अटल व्योम FPT_phaseBusFree(u32 port, अचिन्हित अक्षर p_card)
अणु
	काष्ठा sccb *currSCCB;

	currSCCB = FPT_BL_Card[p_card].currentSCCB;

	अगर (currSCCB != शून्य) अणु

		DISABLE_AUTO(port);

		अगर (currSCCB->OperationCode == RESET_COMMAND) अणु

			अगर ((FPT_BL_Card[p_card].globalFlags & F_CONLUN_IO) &&
			    ((FPT_sccbMgrTbl[p_card][currSCCB->TargID].
			      TarStatus & TAR_TAG_Q_MASK) != TAG_Q_TRYING))
				FPT_sccbMgrTbl[p_card][currSCCB->TargID].
				    TarLUNBusy[currSCCB->Lun] = 0;
			अन्यथा
				FPT_sccbMgrTbl[p_card][currSCCB->TargID].
				    TarLUNBusy[0] = 0;

			FPT_queueCmdComplete(&FPT_BL_Card[p_card], currSCCB,
					     p_card);

			FPT_queueSearchSelect(&FPT_BL_Card[p_card], p_card);

		पूर्ण

		अन्यथा अगर (currSCCB->Sccb_scsistat == SELECT_SN_ST) अणु
			FPT_sccbMgrTbl[p_card][currSCCB->TargID].TarStatus |=
			    (अचिन्हित अक्षर)SYNC_SUPPORTED;
			FPT_sccbMgrTbl[p_card][currSCCB->TargID].TarEEValue &=
			    ~EE_SYNC_MASK;
		पूर्ण

		अन्यथा अगर (currSCCB->Sccb_scsistat == SELECT_WN_ST) अणु
			FPT_sccbMgrTbl[p_card][currSCCB->TargID].TarStatus =
			    (FPT_sccbMgrTbl[p_card][currSCCB->TargID].
			     TarStatus & ~WIDE_ENABLED) | WIDE_NEGOCIATED;

			FPT_sccbMgrTbl[p_card][currSCCB->TargID].TarEEValue &=
			    ~EE_WIDE_SCSI;
		पूर्ण

		अन्यथा अगर (currSCCB->Sccb_scsistat == SELECT_Q_ST) अणु
			/* Make sure this is not a phony BUS_FREE.  If we were
			   reselected or अगर BUSY is NOT on then this is a
			   valid BUS FREE.  SRR Wednesday, 5/10/1995.     */

			अगर ((!(RD_HARPOON(port + hp_scsisig) & SCSI_BSY)) ||
			    (RDW_HARPOON((port + hp_पूर्णांकstat)) & RSEL)) अणु
				FPT_sccbMgrTbl[p_card][currSCCB->TargID].
				    TarStatus &= ~TAR_TAG_Q_MASK;
				FPT_sccbMgrTbl[p_card][currSCCB->TargID].
				    TarStatus |= TAG_Q_REJECT;
			पूर्ण

			अन्यथा अणु
				वापस;
			पूर्ण
		पूर्ण

		अन्यथा अणु

			currSCCB->Sccb_scsistat = BUS_FREE_ST;

			अगर (!currSCCB->HostStatus) अणु
				currSCCB->HostStatus = SCCB_PHASE_SEQUENCE_FAIL;
			पूर्ण

			अगर ((FPT_BL_Card[p_card].globalFlags & F_CONLUN_IO) &&
			    ((FPT_sccbMgrTbl[p_card][currSCCB->TargID].
			      TarStatus & TAR_TAG_Q_MASK) != TAG_Q_TRYING))
				FPT_sccbMgrTbl[p_card][currSCCB->TargID].
				    TarLUNBusy[currSCCB->Lun] = 0;
			अन्यथा
				FPT_sccbMgrTbl[p_card][currSCCB->TargID].
				    TarLUNBusy[0] = 0;

			FPT_queueCmdComplete(&FPT_BL_Card[p_card], currSCCB,
					     p_card);
			वापस;
		पूर्ण

		FPT_BL_Card[p_card].globalFlags |= F_NEW_SCCB_CMD;

	पूर्ण			/*end अगर !=null */
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Auto Load Default Map
 *
 * Description: Load the Automation RAM with the शेष map values.
 *
 *---------------------------------------------------------------------*/
अटल व्योम FPT_स्वतःLoadDefaultMap(u32 p_port)
अणु
	u32 map_addr;

	ARAM_ACCESS(p_port);
	map_addr = p_port + hp_aramBase;

	WRW_HARPOON(map_addr, (MPM_OP + AMSG_OUT + 0xC0));	/*ID MESSAGE */
	map_addr += 2;
	WRW_HARPOON(map_addr, (MPM_OP + AMSG_OUT + 0x20));	/*SIMPLE TAG QUEUEING MSG */
	map_addr += 2;
	WRW_HARPOON(map_addr, RAT_OP);	/*RESET ATTENTION */
	map_addr += 2;
	WRW_HARPOON(map_addr, (MPM_OP + AMSG_OUT + 0x00));	/*TAG ID MSG */
	map_addr += 2;
	WRW_HARPOON(map_addr, (MPM_OP + ACOMMAND + 0x00));	/*CDB BYTE 0 */
	map_addr += 2;
	WRW_HARPOON(map_addr, (MPM_OP + ACOMMAND + 0x00));	/*CDB BYTE 1 */
	map_addr += 2;
	WRW_HARPOON(map_addr, (MPM_OP + ACOMMAND + 0x00));	/*CDB BYTE 2 */
	map_addr += 2;
	WRW_HARPOON(map_addr, (MPM_OP + ACOMMAND + 0x00));	/*CDB BYTE 3 */
	map_addr += 2;
	WRW_HARPOON(map_addr, (MPM_OP + ACOMMAND + 0x00));	/*CDB BYTE 4 */
	map_addr += 2;
	WRW_HARPOON(map_addr, (MPM_OP + ACOMMAND + 0x00));	/*CDB BYTE 5 */
	map_addr += 2;
	WRW_HARPOON(map_addr, (MPM_OP + ACOMMAND + 0x00));	/*CDB BYTE 6 */
	map_addr += 2;
	WRW_HARPOON(map_addr, (MPM_OP + ACOMMAND + 0x00));	/*CDB BYTE 7 */
	map_addr += 2;
	WRW_HARPOON(map_addr, (MPM_OP + ACOMMAND + 0x00));	/*CDB BYTE 8 */
	map_addr += 2;
	WRW_HARPOON(map_addr, (MPM_OP + ACOMMAND + 0x00));	/*CDB BYTE 9 */
	map_addr += 2;
	WRW_HARPOON(map_addr, (MPM_OP + ACOMMAND + 0x00));	/*CDB BYTE 10 */
	map_addr += 2;
	WRW_HARPOON(map_addr, (MPM_OP + ACOMMAND + 0x00));	/*CDB BYTE 11 */
	map_addr += 2;
	WRW_HARPOON(map_addr, (CPE_OP + ADATA_OUT + DINT));	/*JUMP IF DATA OUT */
	map_addr += 2;
	WRW_HARPOON(map_addr, (TCB_OP + FIFO_0 + DI));	/*JUMP IF NO DATA IN FIFO */
	map_addr += 2;		/*This means AYNC DATA IN */
	WRW_HARPOON(map_addr, (SSI_OP + SSI_IDO_STRT));	/*STOP AND INTERRUPT */
	map_addr += 2;
	WRW_HARPOON(map_addr, (CPE_OP + ADATA_IN + DINT));	/*JUMP IF NOT DATA IN PHZ */
	map_addr += 2;
	WRW_HARPOON(map_addr, (CPN_OP + AMSG_IN + ST));	/*IF NOT MSG IN CHECK 4 DATA IN */
	map_addr += 2;
	WRW_HARPOON(map_addr, (CRD_OP + SDATA + 0x02));	/*SAVE DATA PTR MSG? */
	map_addr += 2;
	WRW_HARPOON(map_addr, (BRH_OP + NOT_EQ + DC));	/*GO CHECK FOR DISCONNECT MSG */
	map_addr += 2;
	WRW_HARPOON(map_addr, (MRR_OP + SDATA + D_AR1));	/*SAVE DATA PTRS MSG */
	map_addr += 2;
	WRW_HARPOON(map_addr, (CPN_OP + AMSG_IN + ST));	/*IF NOT MSG IN CHECK DATA IN */
	map_addr += 2;
	WRW_HARPOON(map_addr, (CRD_OP + SDATA + 0x04));	/*DISCONNECT MSG? */
	map_addr += 2;
	WRW_HARPOON(map_addr, (BRH_OP + NOT_EQ + UNKNWN));	/*UKNKNOWN MSG */
	map_addr += 2;
	WRW_HARPOON(map_addr, (MRR_OP + SDATA + D_BUCKET));	/*XFER DISCONNECT MSG */
	map_addr += 2;
	WRW_HARPOON(map_addr, (SSI_OP + SSI_ITAR_DISC));	/*STOP AND INTERRUPT */
	map_addr += 2;
	WRW_HARPOON(map_addr, (CPN_OP + ASTATUS + UNKNWN));	/*JUMP IF NOT STATUS PHZ. */
	map_addr += 2;
	WRW_HARPOON(map_addr, (MRR_OP + SDATA + D_AR0));	/*GET STATUS BYTE */
	map_addr += 2;
	WRW_HARPOON(map_addr, (CPN_OP + AMSG_IN + CC));	/*ERROR IF NOT MSG IN PHZ */
	map_addr += 2;
	WRW_HARPOON(map_addr, (CRD_OP + SDATA + 0x00));	/*CHECK FOR CMD COMPLETE MSG. */
	map_addr += 2;
	WRW_HARPOON(map_addr, (BRH_OP + NOT_EQ + CC));	/*ERROR IF NOT CMD COMPLETE MSG. */
	map_addr += 2;
	WRW_HARPOON(map_addr, (MRR_OP + SDATA + D_BUCKET));	/*GET CMD COMPLETE MSG */
	map_addr += 2;
	WRW_HARPOON(map_addr, (SSI_OP + SSI_ICMD_COMP));	/*END OF COMMAND */
	map_addr += 2;

	WRW_HARPOON(map_addr, (SSI_OP + SSI_IUNKWN));	/*RECEIVED UNKNOWN MSG BYTE */
	map_addr += 2;
	WRW_HARPOON(map_addr, (SSI_OP + SSI_INO_CC));	/*NO COMMAND COMPLETE AFTER STATUS */
	map_addr += 2;
	WRW_HARPOON(map_addr, (SSI_OP + SSI_ITICKLE));	/*BIOS Tickled the Mgr */
	map_addr += 2;
	WRW_HARPOON(map_addr, (SSI_OP + SSI_IRFAIL));	/*EXPECTED ID/TAG MESSAGES AND */
	map_addr += 2;		/* DIDN'T GET ONE */
	WRW_HARPOON(map_addr, (CRR_OP + AR3 + S_IDREG));	/* comp SCSI SEL ID & AR3 */
	map_addr += 2;
	WRW_HARPOON(map_addr, (BRH_OP + EQUAL + 0x00));	/*SEL ID OK then Conti. */
	map_addr += 2;
	WRW_HARPOON(map_addr, (SSI_OP + SSI_INO_CC));	/*NO COMMAND COMPLETE AFTER STATUS */

	SGRAM_ACCESS(p_port);
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Auto Command Complete
 *
 * Description: Post command back to host and find another command
 *              to execute.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_स्वतःCmdCmplt(u32 p_port, अचिन्हित अक्षर p_card)
अणु
	काष्ठा sccb *currSCCB;
	अचिन्हित अक्षर status_byte;

	currSCCB = FPT_BL_Card[p_card].currentSCCB;

	status_byte = RD_HARPOON(p_port + hp_gp_reg_0);

	FPT_sccbMgrTbl[p_card][currSCCB->TargID].TarLUN_CA = 0;

	अगर (status_byte != SSGOOD) अणु

		अगर (status_byte == SSQ_FULL) अणु

			अगर (((FPT_BL_Card[p_card].globalFlags & F_CONLUN_IO) &&
			     ((FPT_sccbMgrTbl[p_card][currSCCB->TargID].
			       TarStatus & TAR_TAG_Q_MASK) != TAG_Q_TRYING))) अणु
				FPT_sccbMgrTbl[p_card][currSCCB->TargID].
				    TarLUNBusy[currSCCB->Lun] = 1;
				अगर (FPT_BL_Card[p_card].discQCount != 0)
					FPT_BL_Card[p_card].discQCount--;
				FPT_BL_Card[p_card].
				    discQ_Tbl[FPT_sccbMgrTbl[p_card]
					      [currSCCB->TargID].
					      LunDiscQ_Idx[currSCCB->Lun]] =
				    शून्य;
			पूर्ण अन्यथा अणु
				FPT_sccbMgrTbl[p_card][currSCCB->TargID].
				    TarLUNBusy[0] = 1;
				अगर (currSCCB->Sccb_tag) अणु
					अगर (FPT_BL_Card[p_card].discQCount != 0)
						FPT_BL_Card[p_card].
						    discQCount--;
					FPT_BL_Card[p_card].discQ_Tbl[currSCCB->
								      Sccb_tag]
					    = शून्य;
				पूर्ण अन्यथा अणु
					अगर (FPT_BL_Card[p_card].discQCount != 0)
						FPT_BL_Card[p_card].
						    discQCount--;
					FPT_BL_Card[p_card].
					    discQ_Tbl[FPT_sccbMgrTbl[p_card]
						      [currSCCB->TargID].
						      LunDiscQ_Idx[0]] = शून्य;
				पूर्ण
			पूर्ण

			currSCCB->Sccb_MGRFlags |= F_STATUSLOADED;

			FPT_queueSelectFail(&FPT_BL_Card[p_card], p_card);

			वापस;
		पूर्ण

		अगर (currSCCB->Sccb_scsistat == SELECT_SN_ST) अणु
			FPT_sccbMgrTbl[p_card][currSCCB->TargID].TarStatus |=
			    (अचिन्हित अक्षर)SYNC_SUPPORTED;

			FPT_sccbMgrTbl[p_card][currSCCB->TargID].TarEEValue &=
			    ~EE_SYNC_MASK;
			FPT_BL_Card[p_card].globalFlags |= F_NEW_SCCB_CMD;

			अगर (((FPT_BL_Card[p_card].globalFlags & F_CONLUN_IO) &&
			     ((FPT_sccbMgrTbl[p_card][currSCCB->TargID].
			       TarStatus & TAR_TAG_Q_MASK) != TAG_Q_TRYING))) अणु
				FPT_sccbMgrTbl[p_card][currSCCB->TargID].
				    TarLUNBusy[currSCCB->Lun] = 1;
				अगर (FPT_BL_Card[p_card].discQCount != 0)
					FPT_BL_Card[p_card].discQCount--;
				FPT_BL_Card[p_card].
				    discQ_Tbl[FPT_sccbMgrTbl[p_card]
					      [currSCCB->TargID].
					      LunDiscQ_Idx[currSCCB->Lun]] =
				    शून्य;
			पूर्ण अन्यथा अणु
				FPT_sccbMgrTbl[p_card][currSCCB->TargID].
				    TarLUNBusy[0] = 1;
				अगर (currSCCB->Sccb_tag) अणु
					अगर (FPT_BL_Card[p_card].discQCount != 0)
						FPT_BL_Card[p_card].
						    discQCount--;
					FPT_BL_Card[p_card].discQ_Tbl[currSCCB->
								      Sccb_tag]
					    = शून्य;
				पूर्ण अन्यथा अणु
					अगर (FPT_BL_Card[p_card].discQCount != 0)
						FPT_BL_Card[p_card].
						    discQCount--;
					FPT_BL_Card[p_card].
					    discQ_Tbl[FPT_sccbMgrTbl[p_card]
						      [currSCCB->TargID].
						      LunDiscQ_Idx[0]] = शून्य;
				पूर्ण
			पूर्ण
			वापस;

		पूर्ण

		अगर (currSCCB->Sccb_scsistat == SELECT_WN_ST) अणु

			FPT_sccbMgrTbl[p_card][currSCCB->TargID].TarStatus =
			    (FPT_sccbMgrTbl[p_card][currSCCB->TargID].
			     TarStatus & ~WIDE_ENABLED) | WIDE_NEGOCIATED;

			FPT_sccbMgrTbl[p_card][currSCCB->TargID].TarEEValue &=
			    ~EE_WIDE_SCSI;
			FPT_BL_Card[p_card].globalFlags |= F_NEW_SCCB_CMD;

			अगर (((FPT_BL_Card[p_card].globalFlags & F_CONLUN_IO) &&
			     ((FPT_sccbMgrTbl[p_card][currSCCB->TargID].
			       TarStatus & TAR_TAG_Q_MASK) != TAG_Q_TRYING))) अणु
				FPT_sccbMgrTbl[p_card][currSCCB->TargID].
				    TarLUNBusy[currSCCB->Lun] = 1;
				अगर (FPT_BL_Card[p_card].discQCount != 0)
					FPT_BL_Card[p_card].discQCount--;
				FPT_BL_Card[p_card].
				    discQ_Tbl[FPT_sccbMgrTbl[p_card]
					      [currSCCB->TargID].
					      LunDiscQ_Idx[currSCCB->Lun]] =
				    शून्य;
			पूर्ण अन्यथा अणु
				FPT_sccbMgrTbl[p_card][currSCCB->TargID].
				    TarLUNBusy[0] = 1;
				अगर (currSCCB->Sccb_tag) अणु
					अगर (FPT_BL_Card[p_card].discQCount != 0)
						FPT_BL_Card[p_card].
						    discQCount--;
					FPT_BL_Card[p_card].discQ_Tbl[currSCCB->
								      Sccb_tag]
					    = शून्य;
				पूर्ण अन्यथा अणु
					अगर (FPT_BL_Card[p_card].discQCount != 0)
						FPT_BL_Card[p_card].
						    discQCount--;
					FPT_BL_Card[p_card].
					    discQ_Tbl[FPT_sccbMgrTbl[p_card]
						      [currSCCB->TargID].
						      LunDiscQ_Idx[0]] = शून्य;
				पूर्ण
			पूर्ण
			वापस;

		पूर्ण

		अगर (status_byte == SSCHECK) अणु
			अगर (FPT_BL_Card[p_card].globalFlags & F_DO_RENEGO) अणु
				अगर (FPT_sccbMgrTbl[p_card][currSCCB->TargID].
				    TarEEValue & EE_SYNC_MASK) अणु
					FPT_sccbMgrTbl[p_card][currSCCB->
							       TargID].
					    TarStatus &= ~TAR_SYNC_MASK;
				पूर्ण
				अगर (FPT_sccbMgrTbl[p_card][currSCCB->TargID].
				    TarEEValue & EE_WIDE_SCSI) अणु
					FPT_sccbMgrTbl[p_card][currSCCB->
							       TargID].
					    TarStatus &= ~TAR_WIDE_MASK;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (!(currSCCB->Sccb_XferState & F_AUTO_SENSE)) अणु

			currSCCB->SccbStatus = SCCB_ERROR;
			currSCCB->TargetStatus = status_byte;

			अगर (status_byte == SSCHECK) अणु

				FPT_sccbMgrTbl[p_card][currSCCB->TargID].
				    TarLUN_CA = 1;

				अगर (currSCCB->RequestSenseLength !=
				    NO_AUTO_REQUEST_SENSE) अणु

					अगर (currSCCB->RequestSenseLength == 0)
						currSCCB->RequestSenseLength =
						    14;

					FPT_ssenss(&FPT_BL_Card[p_card]);
					FPT_BL_Card[p_card].globalFlags |=
					    F_NEW_SCCB_CMD;

					अगर (((FPT_BL_Card[p_card].
					      globalFlags & F_CONLUN_IO)
					     &&
					     ((FPT_sccbMgrTbl[p_card]
					       [currSCCB->TargID].
					       TarStatus & TAR_TAG_Q_MASK) !=
					      TAG_Q_TRYING))) अणु
						FPT_sccbMgrTbl[p_card]
						    [currSCCB->TargID].
						    TarLUNBusy[currSCCB->Lun] =
						    1;
						अगर (FPT_BL_Card[p_card].
						    discQCount != 0)
							FPT_BL_Card[p_card].
							    discQCount--;
						FPT_BL_Card[p_card].
						    discQ_Tbl[FPT_sccbMgrTbl
							      [p_card]
							      [currSCCB->
							       TargID].
							      LunDiscQ_Idx
							      [currSCCB->Lun]] =
						    शून्य;
					पूर्ण अन्यथा अणु
						FPT_sccbMgrTbl[p_card]
						    [currSCCB->TargID].
						    TarLUNBusy[0] = 1;
						अगर (currSCCB->Sccb_tag) अणु
							अगर (FPT_BL_Card[p_card].
							    discQCount != 0)
								FPT_BL_Card
								    [p_card].
								    discQCount--;
							FPT_BL_Card[p_card].
							    discQ_Tbl[currSCCB->
								      Sccb_tag]
							    = शून्य;
						पूर्ण अन्यथा अणु
							अगर (FPT_BL_Card[p_card].
							    discQCount != 0)
								FPT_BL_Card
								    [p_card].
								    discQCount--;
							FPT_BL_Card[p_card].
							    discQ_Tbl
							    [FPT_sccbMgrTbl
							     [p_card][currSCCB->
								      TargID].
							     LunDiscQ_Idx[0]] =
							    शून्य;
						पूर्ण
					पूर्ण
					वापस;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर ((FPT_BL_Card[p_card].globalFlags & F_CONLUN_IO) &&
	    ((FPT_sccbMgrTbl[p_card][currSCCB->TargID].
	      TarStatus & TAR_TAG_Q_MASK) != TAG_Q_TRYING))
		FPT_sccbMgrTbl[p_card][currSCCB->TargID].TarLUNBusy[currSCCB->
								    Lun] = 0;
	अन्यथा
		FPT_sccbMgrTbl[p_card][currSCCB->TargID].TarLUNBusy[0] = 0;

	FPT_queueCmdComplete(&FPT_BL_Card[p_card], currSCCB, p_card);
पूर्ण

#घोषणा SHORT_WAIT   0x0000000F
#घोषणा LONG_WAIT    0x0000FFFFL

/*---------------------------------------------------------------------
 *
 * Function: Data Transfer Processor
 *
 * Description: This routine perक्रमms two tasks.
 *              (1) Start data transfer by calling HOST_DATA_XFER_START
 *              function.  Once data transfer is started, (2) Depends
 *              on the type of data transfer mode Scatter/Gather mode
 *              or NON Scatter/Gather mode.  In NON Scatter/Gather mode,
 *              this routine checks Sccb_MGRFlag (F_HOST_XFER_ACT bit) क्रम
 *              data transfer करोne.  In Scatter/Gather mode, this routine
 *              checks bus master command complete and dual rank busy
 *              bit to keep chaining SC transfer command.  Similarly,
 *              in Scatter/Gather mode, it checks Sccb_MGRFlag
 *              (F_HOST_XFER_ACT bit) क्रम data transfer करोne.
 *              
 *---------------------------------------------------------------------*/

अटल व्योम FPT_dataXferProcessor(u32 port, काष्ठा sccb_card *pCurrCard)
अणु
	काष्ठा sccb *currSCCB;

	currSCCB = pCurrCard->currentSCCB;

	अगर (currSCCB->Sccb_XferState & F_SG_XFER) अणु
		अगर (pCurrCard->globalFlags & F_HOST_XFER_ACT)
		अणु
			currSCCB->Sccb_sgseg += (अचिन्हित अक्षर)SG_BUF_CNT;
			currSCCB->Sccb_SGoffset = 0x00;
		पूर्ण
		pCurrCard->globalFlags |= F_HOST_XFER_ACT;

		FPT_busMstrSGDataXferStart(port, currSCCB);
	पूर्ण

	अन्यथा अणु
		अगर (!(pCurrCard->globalFlags & F_HOST_XFER_ACT)) अणु
			pCurrCard->globalFlags |= F_HOST_XFER_ACT;

			FPT_busMstrDataXferStart(port, currSCCB);
		पूर्ण
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: BusMaster Scatter Gather Data Transfer Start
 *
 * Description:
 *
 *---------------------------------------------------------------------*/
अटल व्योम FPT_busMstrSGDataXferStart(u32 p_port, काष्ठा sccb *pcurrSCCB)
अणु
	u32 count, addr, पंचांगpSGCnt;
	अचिन्हित पूर्णांक sg_index;
	अचिन्हित अक्षर sg_count, i;
	u32 reg_offset;
	काष्ठा blogic_sg_seg *segp;

	अगर (pcurrSCCB->Sccb_XferState & F_HOST_XFER_सूची)
		count = ((u32)HOST_RD_CMD) << 24;
	अन्यथा
		count = ((u32)HOST_WRT_CMD) << 24;

	sg_count = 0;
	पंचांगpSGCnt = 0;
	sg_index = pcurrSCCB->Sccb_sgseg;
	reg_offset = hp_aramBase;

	i = (अचिन्हित अक्षर)(RD_HARPOON(p_port + hp_page_ctrl) &
			    ~(SGRAM_ARAM | SCATTER_EN));

	WR_HARPOON(p_port + hp_page_ctrl, i);

	जबतक ((sg_count < (अचिन्हित अक्षर)SG_BUF_CNT) &&
			((sg_index * (अचिन्हित पूर्णांक)SG_ELEMENT_SIZE) <
			pcurrSCCB->DataLength)) अणु

		segp = (काष्ठा blogic_sg_seg *)(pcurrSCCB->DataPoपूर्णांकer) +
				sg_index;
		पंचांगpSGCnt += segp->segbytes;
		count |= segp->segbytes;
		addr = segp->segdata;

		अगर ((!sg_count) && (pcurrSCCB->Sccb_SGoffset)) अणु
			addr +=
			    ((count & 0x00FFFFFFL) - pcurrSCCB->Sccb_SGoffset);
			count =
			    (count & 0xFF000000L) | pcurrSCCB->Sccb_SGoffset;
			पंचांगpSGCnt = count & 0x00FFFFFFL;
		पूर्ण

		WR_HARP32(p_port, reg_offset, addr);
		reg_offset += 4;

		WR_HARP32(p_port, reg_offset, count);
		reg_offset += 4;

		count &= 0xFF000000L;
		sg_index++;
		sg_count++;

	पूर्ण			/*End While */

	pcurrSCCB->Sccb_XferCnt = पंचांगpSGCnt;

	WR_HARPOON(p_port + hp_sg_addr, (sg_count << 4));

	अगर (pcurrSCCB->Sccb_XferState & F_HOST_XFER_सूची) अणु

		WR_HARP32(p_port, hp_xfercnt_0, पंचांगpSGCnt);

		WR_HARPOON(p_port + hp_portctrl_0,
			   (DMA_PORT | SCSI_PORT | SCSI_INBIT));
		WR_HARPOON(p_port + hp_scsisig, S_DATAI_PH);
	पूर्ण

	अन्यथा अणु

		अगर ((!(RD_HARPOON(p_port + hp_synctarg_0) & NARROW_SCSI)) &&
		    (पंचांगpSGCnt & 0x000000001)) अणु

			pcurrSCCB->Sccb_XferState |= F_ODD_BALL_CNT;
			पंचांगpSGCnt--;
		पूर्ण

		WR_HARP32(p_port, hp_xfercnt_0, पंचांगpSGCnt);

		WR_HARPOON(p_port + hp_portctrl_0,
			   (SCSI_PORT | DMA_PORT | DMA_RD));
		WR_HARPOON(p_port + hp_scsisig, S_DATAO_PH);
	पूर्ण

	WR_HARPOON(p_port + hp_page_ctrl, (अचिन्हित अक्षर)(i | SCATTER_EN));

पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: BusMaster Data Transfer Start
 *
 * Description: 
 *
 *---------------------------------------------------------------------*/
अटल व्योम FPT_busMstrDataXferStart(u32 p_port, काष्ठा sccb *pcurrSCCB)
अणु
	u32 addr, count;

	अगर (!(pcurrSCCB->Sccb_XferState & F_AUTO_SENSE)) अणु

		count = pcurrSCCB->Sccb_XferCnt;

		addr = (u32)(अचिन्हित दीर्घ)pcurrSCCB->DataPoपूर्णांकer + pcurrSCCB->Sccb_ATC;
	पूर्ण

	अन्यथा अणु
		addr = pcurrSCCB->SensePoपूर्णांकer;
		count = pcurrSCCB->RequestSenseLength;

	पूर्ण

	HP_SETUP_ADDR_CNT(p_port, addr, count);

	अगर (pcurrSCCB->Sccb_XferState & F_HOST_XFER_सूची) अणु

		WR_HARPOON(p_port + hp_portctrl_0,
			   (DMA_PORT | SCSI_PORT | SCSI_INBIT));
		WR_HARPOON(p_port + hp_scsisig, S_DATAI_PH);

		WR_HARPOON(p_port + hp_xfer_cmd,
			   (XFER_DMA_HOST | XFER_HOST_AUTO | XFER_DMA_8BIT));
	पूर्ण

	अन्यथा अणु

		WR_HARPOON(p_port + hp_portctrl_0,
			   (SCSI_PORT | DMA_PORT | DMA_RD));
		WR_HARPOON(p_port + hp_scsisig, S_DATAO_PH);

		WR_HARPOON(p_port + hp_xfer_cmd,
			   (XFER_HOST_DMA | XFER_HOST_AUTO | XFER_DMA_8BIT));

	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: BusMaster Timeout Handler
 *
 * Description: This function is called after a bus master command busy समय
 *               out is detected.  This routines issue halt state machine
 *               with a software समय out क्रम command busy.  If command busy
 *               is still निश्चितed at the end of the समय out, it issues
 *               hard पात with another software समय out.  It hard पात
 *               command busy is also समय out, it'll just give up.
 *
 *---------------------------------------------------------------------*/
अटल अचिन्हित अक्षर FPT_busMstrTimeOut(u32 p_port)
अणु
	अचिन्हित दीर्घ समयout;

	समयout = LONG_WAIT;

	WR_HARPOON(p_port + hp_sys_ctrl, HALT_MACH);

	जबतक ((!(RD_HARPOON(p_port + hp_ext_status) & CMD_ABORTED))
	       && समयout--) अणु
	पूर्ण

	अगर (RD_HARPOON(p_port + hp_ext_status) & BM_CMD_BUSY) अणु
		WR_HARPOON(p_port + hp_sys_ctrl, HARD_ABORT);

		समयout = LONG_WAIT;
		जबतक ((RD_HARPOON(p_port + hp_ext_status) & BM_CMD_BUSY)
		       && समयout--) अणु
		पूर्ण
	पूर्ण

	RD_HARPOON(p_port + hp_पूर्णांक_status);	/*Clear command complete */

	अगर (RD_HARPOON(p_port + hp_ext_status) & BM_CMD_BUSY) अणु
		वापस 1;
	पूर्ण

	अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Host Data Transfer Abort
 *
 * Description: Abort any in progress transfer.
 *
 *---------------------------------------------------------------------*/
अटल व्योम FPT_hostDataXferAbort(u32 port, अचिन्हित अक्षर p_card,
				  काष्ठा sccb *pCurrSCCB)
अणु

	अचिन्हित दीर्घ समयout;
	अचिन्हित दीर्घ reमुख्य_cnt;
	u32 sg_ptr;
	काष्ठा blogic_sg_seg *segp;

	FPT_BL_Card[p_card].globalFlags &= ~F_HOST_XFER_ACT;

	अगर (pCurrSCCB->Sccb_XferState & F_AUTO_SENSE) अणु

		अगर (!(RD_HARPOON(port + hp_पूर्णांक_status) & INT_CMD_COMPL)) अणु

			WR_HARPOON(port + hp_bm_ctrl,
				   (RD_HARPOON(port + hp_bm_ctrl) |
				    FLUSH_XFER_CNTR));
			समयout = LONG_WAIT;

			जबतक ((RD_HARPOON(port + hp_ext_status) & BM_CMD_BUSY)
			       && समयout--) अणु
			पूर्ण

			WR_HARPOON(port + hp_bm_ctrl,
				   (RD_HARPOON(port + hp_bm_ctrl) &
				    ~FLUSH_XFER_CNTR));

			अगर (RD_HARPOON(port + hp_ext_status) & BM_CMD_BUSY) अणु

				अगर (FPT_busMstrTimeOut(port)) अणु

					अगर (pCurrSCCB->HostStatus == 0x00)

						pCurrSCCB->HostStatus =
						    SCCB_BM_ERR;

				पूर्ण

				अगर (RD_HARPOON(port + hp_पूर्णांक_status) &
				    INT_EXT_STATUS)

					अगर (RD_HARPOON(port + hp_ext_status) &
					    BAD_EXT_STATUS)

						अगर (pCurrSCCB->HostStatus ==
						    0x00)
						अणु
							pCurrSCCB->HostStatus =
							    SCCB_BM_ERR;
						पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अन्यथा अगर (pCurrSCCB->Sccb_XferCnt) अणु

		अगर (pCurrSCCB->Sccb_XferState & F_SG_XFER) अणु

			WR_HARPOON(port + hp_page_ctrl,
				   (RD_HARPOON(port + hp_page_ctrl) &
				    ~SCATTER_EN));

			WR_HARPOON(port + hp_sg_addr, 0x00);

			sg_ptr = pCurrSCCB->Sccb_sgseg + SG_BUF_CNT;

			अगर (sg_ptr >
			    (अचिन्हित पूर्णांक)(pCurrSCCB->DataLength /
					   SG_ELEMENT_SIZE)) अणु

				sg_ptr = (u32)(pCurrSCCB->DataLength /
							SG_ELEMENT_SIZE);
			पूर्ण

			reमुख्य_cnt = pCurrSCCB->Sccb_XferCnt;

			जबतक (reमुख्य_cnt < 0x01000000L) अणु

				sg_ptr--;
				segp = (काष्ठा blogic_sg_seg *)(pCurrSCCB->
						DataPoपूर्णांकer) + (sg_ptr * 2);
				अगर (reमुख्य_cnt > (अचिन्हित दीर्घ)segp->segbytes)
					reमुख्य_cnt -=
						(अचिन्हित दीर्घ)segp->segbytes;
				अन्यथा
					अवरोध;
			पूर्ण

			अगर (reमुख्य_cnt < 0x01000000L) अणु

				pCurrSCCB->Sccb_SGoffset = reमुख्य_cnt;

				pCurrSCCB->Sccb_sgseg = (अचिन्हित लघु)sg_ptr;

				अगर ((अचिन्हित दीर्घ)(sg_ptr * SG_ELEMENT_SIZE) ==
				    pCurrSCCB->DataLength && (reमुख्य_cnt == 0))

					pCurrSCCB->Sccb_XferState |=
					    F_ALL_XFERRED;
			पूर्ण

			अन्यथा अणु

				अगर (pCurrSCCB->HostStatus == 0x00) अणु

					pCurrSCCB->HostStatus =
					    SCCB_GROSS_FW_ERR;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (!(pCurrSCCB->Sccb_XferState & F_HOST_XFER_सूची)) अणु

			अगर (RD_HARPOON(port + hp_ext_status) & BM_CMD_BUSY) अणु

				FPT_busMstrTimeOut(port);
			पूर्ण

			अन्यथा अणु

				अगर (RD_HARPOON(port + hp_पूर्णांक_status) &
				    INT_EXT_STATUS) अणु

					अगर (RD_HARPOON(port + hp_ext_status) &
					    BAD_EXT_STATUS) अणु

						अगर (pCurrSCCB->HostStatus ==
						    0x00) अणु

							pCurrSCCB->HostStatus =
							    SCCB_BM_ERR;
						पूर्ण
					पूर्ण
				पूर्ण

			पूर्ण
		पूर्ण

		अन्यथा अणु

			अगर ((RD_HARPOON(port + hp_fअगरo_cnt)) >= BM_THRESHOLD) अणु

				समयout = SHORT_WAIT;

				जबतक ((RD_HARPOON(port + hp_ext_status) &
					BM_CMD_BUSY)
				       && ((RD_HARPOON(port + hp_fअगरo_cnt)) >=
					   BM_THRESHOLD) && समयout--) अणु
				पूर्ण
			पूर्ण

			अगर (RD_HARPOON(port + hp_ext_status) & BM_CMD_BUSY) अणु

				WR_HARPOON(port + hp_bm_ctrl,
					   (RD_HARPOON(port + hp_bm_ctrl) |
					    FLUSH_XFER_CNTR));

				समयout = LONG_WAIT;

				जबतक ((RD_HARPOON(port + hp_ext_status) &
					BM_CMD_BUSY) && समयout--) अणु
				पूर्ण

				WR_HARPOON(port + hp_bm_ctrl,
					   (RD_HARPOON(port + hp_bm_ctrl) &
					    ~FLUSH_XFER_CNTR));

				अगर (RD_HARPOON(port + hp_ext_status) &
				    BM_CMD_BUSY) अणु

					अगर (pCurrSCCB->HostStatus == 0x00) अणु

						pCurrSCCB->HostStatus =
						    SCCB_BM_ERR;
					पूर्ण

					FPT_busMstrTimeOut(port);
				पूर्ण
			पूर्ण

			अगर (RD_HARPOON(port + hp_पूर्णांक_status) & INT_EXT_STATUS) अणु

				अगर (RD_HARPOON(port + hp_ext_status) &
				    BAD_EXT_STATUS) अणु

					अगर (pCurrSCCB->HostStatus == 0x00) अणु

						pCurrSCCB->HostStatus =
						    SCCB_BM_ERR;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण

	पूर्ण

	अन्यथा अणु

		अगर (RD_HARPOON(port + hp_ext_status) & BM_CMD_BUSY) अणु

			समयout = LONG_WAIT;

			जबतक ((RD_HARPOON(port + hp_ext_status) & BM_CMD_BUSY)
			       && समयout--) अणु
			पूर्ण

			अगर (RD_HARPOON(port + hp_ext_status) & BM_CMD_BUSY) अणु

				अगर (pCurrSCCB->HostStatus == 0x00) अणु

					pCurrSCCB->HostStatus = SCCB_BM_ERR;
				पूर्ण

				FPT_busMstrTimeOut(port);
			पूर्ण
		पूर्ण

		अगर (RD_HARPOON(port + hp_पूर्णांक_status) & INT_EXT_STATUS) अणु

			अगर (RD_HARPOON(port + hp_ext_status) & BAD_EXT_STATUS) अणु

				अगर (pCurrSCCB->HostStatus == 0x00) अणु

					pCurrSCCB->HostStatus = SCCB_BM_ERR;
				पूर्ण
			पूर्ण

		पूर्ण

		अगर (pCurrSCCB->Sccb_XferState & F_SG_XFER) अणु

			WR_HARPOON(port + hp_page_ctrl,
				   (RD_HARPOON(port + hp_page_ctrl) &
				    ~SCATTER_EN));

			WR_HARPOON(port + hp_sg_addr, 0x00);

			pCurrSCCB->Sccb_sgseg += SG_BUF_CNT;

			pCurrSCCB->Sccb_SGoffset = 0x00;

			अगर ((u32)(pCurrSCCB->Sccb_sgseg * SG_ELEMENT_SIZE) >=
					pCurrSCCB->DataLength) अणु

				pCurrSCCB->Sccb_XferState |= F_ALL_XFERRED;
				pCurrSCCB->Sccb_sgseg =
				    (अचिन्हित लघु)(pCurrSCCB->DataLength /
						     SG_ELEMENT_SIZE);
			पूर्ण
		पूर्ण

		अन्यथा अणु
			अगर (!(pCurrSCCB->Sccb_XferState & F_AUTO_SENSE))
				pCurrSCCB->Sccb_XferState |= F_ALL_XFERRED;
		पूर्ण
	पूर्ण

	WR_HARPOON(port + hp_पूर्णांक_mask, (INT_CMD_COMPL | SCSI_INTERRUPT));
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Host Data Transfer Restart
 *
 * Description: Reset the available count due to a restore data
 *              poपूर्णांकers message.
 *
 *---------------------------------------------------------------------*/
अटल व्योम FPT_hostDataXferRestart(काष्ठा sccb *currSCCB)
अणु
	अचिन्हित दीर्घ data_count;
	अचिन्हित पूर्णांक sg_index;
	काष्ठा blogic_sg_seg *segp;

	अगर (currSCCB->Sccb_XferState & F_SG_XFER) अणु

		currSCCB->Sccb_XferCnt = 0;

		sg_index = 0xffff;	/*Index by दीर्घ words पूर्णांकo sg list. */
		data_count = 0;		/*Running count of SG xfer counts. */


		जबतक (data_count < currSCCB->Sccb_ATC) अणु

			sg_index++;
			segp = (काष्ठा blogic_sg_seg *)(currSCCB->DataPoपूर्णांकer) +
						(sg_index * 2);
			data_count += segp->segbytes;
		पूर्ण

		अगर (data_count == currSCCB->Sccb_ATC) अणु

			currSCCB->Sccb_SGoffset = 0;
			sg_index++;
		पूर्ण

		अन्यथा अणु
			currSCCB->Sccb_SGoffset =
			    data_count - currSCCB->Sccb_ATC;
		पूर्ण

		currSCCB->Sccb_sgseg = (अचिन्हित लघु)sg_index;
	पूर्ण

	अन्यथा अणु
		currSCCB->Sccb_XferCnt =
		    currSCCB->DataLength - currSCCB->Sccb_ATC;
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_scini
 *
 * Description: Setup all data काष्ठाures necessary क्रम SCAM selection.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_scini(अचिन्हित अक्षर p_card, अचिन्हित अक्षर p_our_id,
		      अचिन्हित अक्षर p_घातer_up)
अणु

	अचिन्हित अक्षर loser, asचिन्हित_id;
	u32 p_port;

	अचिन्हित अक्षर i, k, ScamFlg;
	काष्ठा sccb_card *currCard;
	काष्ठा nvram_info *pCurrNvRam;

	currCard = &FPT_BL_Card[p_card];
	p_port = currCard->ioPort;
	pCurrNvRam = currCard->pNvRamInfo;

	अगर (pCurrNvRam) अणु
		ScamFlg = pCurrNvRam->niScamConf;
		i = pCurrNvRam->niSysConf;
	पूर्ण अन्यथा अणु
		ScamFlg =
		    (अचिन्हित अक्षर)FPT_utilEERead(p_port, SCAM_CONFIG / 2);
		i = (अचिन्हित
		     अक्षर)(FPT_utilEERead(p_port, (SYSTEM_CONFIG / 2)));
	पूर्ण
	अगर (!(i & 0x02))	/* check अगर reset bus in AutoSCSI parameter set */
		वापस;

	FPT_inisci(p_card, p_port, p_our_id);

	/* Force to रुको 1 sec after SCSI bus reset. Some SCAM device FW
	   too slow to वापस to SCAM selection */

	/* अगर (p_घातer_up)
	   FPT_Wait1Second(p_port);
	   अन्यथा
	   FPT_Wait(p_port, TO_250ms); */

	FPT_Wait1Second(p_port);

	अगर ((ScamFlg & SCAM_ENABLED) && (ScamFlg & SCAM_LEVEL2)) अणु
		जबतक (!(FPT_scarb(p_port, INIT_SELTD))) अणु
		पूर्ण

		FPT_scsel(p_port);

		करो अणु
			FPT_scxferc(p_port, SYNC_PTRN);
			FPT_scxferc(p_port, DOM_MSTR);
			loser =
			    FPT_scsendi(p_port,
					&FPT_scamInfo[p_our_id].id_string[0]);
		पूर्ण जबतक (loser == 0xFF);

		FPT_scbusf(p_port);

		अगर ((p_घातer_up) && (!loser)) अणु
			FPT_sresb(p_port, p_card);
			FPT_Wait(p_port, TO_250ms);

			जबतक (!(FPT_scarb(p_port, INIT_SELTD))) अणु
			पूर्ण

			FPT_scsel(p_port);

			करो अणु
				FPT_scxferc(p_port, SYNC_PTRN);
				FPT_scxferc(p_port, DOM_MSTR);
				loser =
				    FPT_scsendi(p_port,
						&FPT_scamInfo[p_our_id].
						id_string[0]);
			पूर्ण जबतक (loser == 0xFF);

			FPT_scbusf(p_port);
		पूर्ण
	पूर्ण

	अन्यथा अणु
		loser = 0;
	पूर्ण

	अगर (!loser) अणु

		FPT_scamInfo[p_our_id].state = ID_ASSIGNED;

		अगर (ScamFlg & SCAM_ENABLED) अणु

			क्रम (i = 0; i < MAX_SCSI_TAR; i++) अणु
				अगर ((FPT_scamInfo[i].state == ID_UNASSIGNED) ||
				    (FPT_scamInfo[i].state == ID_UNUSED)) अणु
					अगर (FPT_scsell(p_port, i)) अणु
						FPT_scamInfo[i].state = LEGACY;
						अगर ((FPT_scamInfo[i].
						     id_string[0] != 0xFF)
						    || (FPT_scamInfo[i].
							id_string[1] != 0xFA)) अणु

							FPT_scamInfo[i].
							    id_string[0] = 0xFF;
							FPT_scamInfo[i].
							    id_string[1] = 0xFA;
							अगर (pCurrNvRam == शून्य)
								currCard->
								    globalFlags
								    |=
								    F_UPDATE_EEPROM;
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण

			FPT_sresb(p_port, p_card);
			FPT_Wait1Second(p_port);
			जबतक (!(FPT_scarb(p_port, INIT_SELTD))) अणु
			पूर्ण
			FPT_scsel(p_port);
			FPT_scasid(p_card, p_port);
		पूर्ण

	पूर्ण

	अन्यथा अगर ((loser) && (ScamFlg & SCAM_ENABLED)) अणु
		FPT_scamInfo[p_our_id].id_string[0] = SLV_TYPE_CODE0;
		asचिन्हित_id = 0;
		FPT_scwtsel(p_port);

		करो अणु
			जबतक (FPT_scxferc(p_port, 0x00) != SYNC_PTRN) अणु
			पूर्ण

			i = FPT_scxferc(p_port, 0x00);
			अगर (i == ASSIGN_ID) अणु
				अगर (!
				    (FPT_scsendi
				     (p_port,
				      &FPT_scamInfo[p_our_id].id_string[0]))) अणु
					i = FPT_scxferc(p_port, 0x00);
					अगर (FPT_scvalq(i)) अणु
						k = FPT_scxferc(p_port, 0x00);

						अगर (FPT_scvalq(k)) अणु
							currCard->ourId =
							    ((अचिन्हित अक्षर)(i
									     <<
									     3)
							     +
							     (k &
							      (अचिन्हित अक्षर)7))
							    & (अचिन्हित अक्षर)
							    0x3F;
							FPT_inisci(p_card,
								   p_port,
								   p_our_id);
							FPT_scamInfo[currCard->
								     ourId].
							    state = ID_ASSIGNED;
							FPT_scamInfo[currCard->
								     ourId].
							    id_string[0]
							    = SLV_TYPE_CODE0;
							asचिन्हित_id = 1;
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण

			अन्यथा अगर (i == SET_P_FLAG) अणु
				अगर (!(FPT_scsendi(p_port,
						  &FPT_scamInfo[p_our_id].
						  id_string[0])))
					FPT_scamInfo[p_our_id].id_string[0] |=
					    0x80;
			पूर्ण
		पूर्ण जबतक (!asचिन्हित_id);

		जबतक (FPT_scxferc(p_port, 0x00) != CFG_CMPLT) अणु
		पूर्ण
	पूर्ण

	अगर (ScamFlg & SCAM_ENABLED) अणु
		FPT_scbusf(p_port);
		अगर (currCard->globalFlags & F_UPDATE_EEPROM) अणु
			FPT_scsavdi(p_card, p_port);
			currCard->globalFlags &= ~F_UPDATE_EEPROM;
		पूर्ण
	पूर्ण

/*
   क्रम (i=0,k=0; i < MAX_SCSI_TAR; i++)
      अणु
      अगर ((FPT_scamInfo[i].state == ID_ASSIGNED) ||
         (FPT_scamInfo[i].state == LEGACY))
         k++;
      पूर्ण

   अगर (k==2)
      currCard->globalFlags |= F_SINGLE_DEVICE;
   अन्यथा
      currCard->globalFlags &= ~F_SINGLE_DEVICE;
*/
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_scarb
 *
 * Description: Gain control of the bus and रुको SCAM select समय (250ms)
 *
 *---------------------------------------------------------------------*/

अटल पूर्णांक FPT_scarb(u32 p_port, अचिन्हित अक्षर p_sel_type)
अणु
	अगर (p_sel_type == INIT_SELTD) अणु

		जबतक (RD_HARPOON(p_port + hp_scsisig) & (SCSI_SEL | SCSI_BSY)) अणु
		पूर्ण

		अगर (RD_HARPOON(p_port + hp_scsisig) & SCSI_SEL)
			वापस 0;

		अगर (RD_HARPOON(p_port + hp_scsidata_0) != 00)
			वापस 0;

		WR_HARPOON(p_port + hp_scsisig,
			   (RD_HARPOON(p_port + hp_scsisig) | SCSI_BSY));

		अगर (RD_HARPOON(p_port + hp_scsisig) & SCSI_SEL) अणु

			WR_HARPOON(p_port + hp_scsisig,
				   (RD_HARPOON(p_port + hp_scsisig) &
				    ~SCSI_BSY));
			वापस 0;
		पूर्ण

		WR_HARPOON(p_port + hp_scsisig,
			   (RD_HARPOON(p_port + hp_scsisig) | SCSI_SEL));

		अगर (RD_HARPOON(p_port + hp_scsidata_0) != 00) अणु

			WR_HARPOON(p_port + hp_scsisig,
				   (RD_HARPOON(p_port + hp_scsisig) &
				    ~(SCSI_BSY | SCSI_SEL)));
			वापस 0;
		पूर्ण
	पूर्ण

	WR_HARPOON(p_port + hp_clkctrl_0, (RD_HARPOON(p_port + hp_clkctrl_0)
					   & ~ACTdeनिश्चित));
	WR_HARPOON(p_port + hp_scsireset, SCAM_EN);
	WR_HARPOON(p_port + hp_scsidata_0, 0x00);
	WR_HARPOON(p_port + hp_scsidata_1, 0x00);
	WR_HARPOON(p_port + hp_portctrl_0, SCSI_BUS_EN);

	WR_HARPOON(p_port + hp_scsisig,
		   (RD_HARPOON(p_port + hp_scsisig) | SCSI_MSG));

	WR_HARPOON(p_port + hp_scsisig, (RD_HARPOON(p_port + hp_scsisig)
					 & ~SCSI_BSY));

	FPT_Wait(p_port, TO_250ms);

	वापस 1;
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_scbusf
 *
 * Description: Release the SCSI bus and disable SCAM selection.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_scbusf(u32 p_port)
अणु
	WR_HARPOON(p_port + hp_page_ctrl,
		   (RD_HARPOON(p_port + hp_page_ctrl) | G_INT_DISABLE));

	WR_HARPOON(p_port + hp_scsidata_0, 0x00);

	WR_HARPOON(p_port + hp_portctrl_0, (RD_HARPOON(p_port + hp_portctrl_0)
					    & ~SCSI_BUS_EN));

	WR_HARPOON(p_port + hp_scsisig, 0x00);

	WR_HARPOON(p_port + hp_scsireset, (RD_HARPOON(p_port + hp_scsireset)
					   & ~SCAM_EN));

	WR_HARPOON(p_port + hp_clkctrl_0, (RD_HARPOON(p_port + hp_clkctrl_0)
					   | ACTdeनिश्चित));

	WRW_HARPOON((p_port + hp_पूर्णांकstat), (BUS_FREE | AUTO_INT | SCAM_SEL));

	WR_HARPOON(p_port + hp_page_ctrl,
		   (RD_HARPOON(p_port + hp_page_ctrl) & ~G_INT_DISABLE));
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_scasid
 *
 * Description: Assign an ID to all the SCAM devices.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_scasid(अचिन्हित अक्षर p_card, u32 p_port)
अणु
	अचिन्हित अक्षर temp_id_string[ID_STRING_LENGTH];

	अचिन्हित अक्षर i, k, scam_id;
	अचिन्हित अक्षर crcBytes[3];
	काष्ठा nvram_info *pCurrNvRam;
	अचिन्हित लघु *pCrcBytes;

	pCurrNvRam = FPT_BL_Card[p_card].pNvRamInfo;

	i = 0;

	जबतक (!i) अणु

		क्रम (k = 0; k < ID_STRING_LENGTH; k++) अणु
			temp_id_string[k] = (अचिन्हित अक्षर)0x00;
		पूर्ण

		FPT_scxferc(p_port, SYNC_PTRN);
		FPT_scxferc(p_port, ASSIGN_ID);

		अगर (!(FPT_sciso(p_port, &temp_id_string[0]))) अणु
			अगर (pCurrNvRam) अणु
				pCrcBytes = (अचिन्हित लघु *)&crcBytes[0];
				*pCrcBytes = FPT_CalcCrc16(&temp_id_string[0]);
				crcBytes[2] = FPT_CalcLrc(&temp_id_string[0]);
				temp_id_string[1] = crcBytes[2];
				temp_id_string[2] = crcBytes[0];
				temp_id_string[3] = crcBytes[1];
				क्रम (k = 4; k < ID_STRING_LENGTH; k++)
					temp_id_string[k] = (अचिन्हित अक्षर)0x00;
			पूर्ण
			i = FPT_scmachid(p_card, temp_id_string);

			अगर (i == CLR_PRIORITY) अणु
				FPT_scxferc(p_port, MISC_CODE);
				FPT_scxferc(p_port, CLR_P_FLAG);
				i = 0;	/*Not the last ID yet. */
			पूर्ण

			अन्यथा अगर (i != NO_ID_AVAIL) अणु
				अगर (i < 8)
					FPT_scxferc(p_port, ID_0_7);
				अन्यथा
					FPT_scxferc(p_port, ID_8_F);

				scam_id = (i & (अचिन्हित अक्षर)0x07);

				क्रम (k = 1; k < 0x08; k <<= 1)
					अगर (!(k & i))
						scam_id += 0x08;	/*Count number of zeros in DB0-3. */

				FPT_scxferc(p_port, scam_id);

				i = 0;	/*Not the last ID yet. */
			पूर्ण
		पूर्ण

		अन्यथा अणु
			i = 1;
		पूर्ण

	पूर्ण			/*End जबतक */

	FPT_scxferc(p_port, SYNC_PTRN);
	FPT_scxferc(p_port, CFG_CMPLT);
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_scsel
 *
 * Description: Select all the SCAM devices.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_scsel(u32 p_port)
अणु

	WR_HARPOON(p_port + hp_scsisig, SCSI_SEL);
	FPT_scwiros(p_port, SCSI_MSG);

	WR_HARPOON(p_port + hp_scsisig, (SCSI_SEL | SCSI_BSY));

	WR_HARPOON(p_port + hp_scsisig,
		   (SCSI_SEL | SCSI_BSY | SCSI_IOBIT | SCSI_CD));
	WR_HARPOON(p_port + hp_scsidata_0,
		   (अचिन्हित अक्षर)(RD_HARPOON(p_port + hp_scsidata_0) |
				   (अचिन्हित अक्षर)(BIT(7) + BIT(6))));

	WR_HARPOON(p_port + hp_scsisig, (SCSI_BSY | SCSI_IOBIT | SCSI_CD));
	FPT_scwiros(p_port, SCSI_SEL);

	WR_HARPOON(p_port + hp_scsidata_0,
		   (अचिन्हित अक्षर)(RD_HARPOON(p_port + hp_scsidata_0) &
				   ~(अचिन्हित अक्षर)BIT(6)));
	FPT_scwirod(p_port, BIT(6));

	WR_HARPOON(p_port + hp_scsisig,
		   (SCSI_SEL | SCSI_BSY | SCSI_IOBIT | SCSI_CD));
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_scxferc
 *
 * Description: Handshake the p_data (DB4-0) across the bus.
 *
 *---------------------------------------------------------------------*/

अटल अचिन्हित अक्षर FPT_scxferc(u32 p_port, अचिन्हित अक्षर p_data)
अणु
	अचिन्हित अक्षर curr_data, ret_data;

	curr_data = p_data | BIT(7) | BIT(5);	/*Start with DB7 & DB5 निश्चितed. */

	WR_HARPOON(p_port + hp_scsidata_0, curr_data);

	curr_data &= ~BIT(7);

	WR_HARPOON(p_port + hp_scsidata_0, curr_data);

	FPT_scwirod(p_port, BIT(7));	/*Wait क्रम DB7 to be released. */
	जबतक (!(RD_HARPOON(p_port + hp_scsidata_0) & BIT(5))) ;

	ret_data = (RD_HARPOON(p_port + hp_scsidata_0) & (अचिन्हित अक्षर)0x1F);

	curr_data |= BIT(6);

	WR_HARPOON(p_port + hp_scsidata_0, curr_data);

	curr_data &= ~BIT(5);

	WR_HARPOON(p_port + hp_scsidata_0, curr_data);

	FPT_scwirod(p_port, BIT(5));	/*Wait क्रम DB5 to be released. */

	curr_data &= ~(BIT(4) | BIT(3) | BIT(2) | BIT(1) | BIT(0));	/*Release data bits */
	curr_data |= BIT(7);

	WR_HARPOON(p_port + hp_scsidata_0, curr_data);

	curr_data &= ~BIT(6);

	WR_HARPOON(p_port + hp_scsidata_0, curr_data);

	FPT_scwirod(p_port, BIT(6));	/*Wait क्रम DB6 to be released. */

	वापस ret_data;
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_scsendi
 *
 * Description: Transfer our Identअगरication string to determine अगर we
 *              will be the करोminant master.
 *
 *---------------------------------------------------------------------*/

अटल अचिन्हित अक्षर FPT_scsendi(u32 p_port, अचिन्हित अक्षर p_id_string[])
अणु
	अचिन्हित अक्षर ret_data, byte_cnt, bit_cnt, defer;

	defer = 0;

	क्रम (byte_cnt = 0; byte_cnt < ID_STRING_LENGTH; byte_cnt++) अणु

		क्रम (bit_cnt = 0x80; bit_cnt != 0; bit_cnt >>= 1) अणु

			अगर (defer)
				ret_data = FPT_scxferc(p_port, 00);

			अन्यथा अगर (p_id_string[byte_cnt] & bit_cnt)

				ret_data = FPT_scxferc(p_port, 02);

			अन्यथा अणु

				ret_data = FPT_scxferc(p_port, 01);
				अगर (ret_data & 02)
					defer = 1;
			पूर्ण

			अगर ((ret_data & 0x1C) == 0x10)
				वापस 0x00;	/*End of isolation stage, we won! */

			अगर (ret_data & 0x1C)
				वापस 0xFF;

			अगर ((defer) && (!(ret_data & 0x1F)))
				वापस 0x01;	/*End of isolation stage, we lost. */

		पूर्ण		/*bit loop */

	पूर्ण			/*byte loop */

	अगर (defer)
		वापस 0x01;	/*We lost */
	अन्यथा
		वापस 0;	/*We WON! Yeeessss! */
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_sciso
 *
 * Description: Transfer the Identअगरication string.
 *
 *---------------------------------------------------------------------*/

अटल अचिन्हित अक्षर FPT_sciso(u32 p_port, अचिन्हित अक्षर p_id_string[])
अणु
	अचिन्हित अक्षर ret_data, the_data, byte_cnt, bit_cnt;

	the_data = 0;

	क्रम (byte_cnt = 0; byte_cnt < ID_STRING_LENGTH; byte_cnt++) अणु

		क्रम (bit_cnt = 0; bit_cnt < 8; bit_cnt++) अणु

			ret_data = FPT_scxferc(p_port, 0);

			अगर (ret_data & 0xFC)
				वापस 0xFF;

			अन्यथा अणु

				the_data <<= 1;
				अगर (ret_data & BIT(1)) अणु
					the_data |= 1;
				पूर्ण
			पूर्ण

			अगर ((ret_data & 0x1F) == 0) अणु
/*
				अगर(bit_cnt != 0 || bit_cnt != 8)
				अणु
					byte_cnt = 0;
					bit_cnt = 0;
					FPT_scxferc(p_port, SYNC_PTRN);
					FPT_scxferc(p_port, ASSIGN_ID);
					जारी;
				पूर्ण
*/
				अगर (byte_cnt)
					वापस 0x00;
				अन्यथा
					वापस 0xFF;
			पूर्ण

		पूर्ण		/*bit loop */

		p_id_string[byte_cnt] = the_data;

	पूर्ण			/*byte loop */

	वापस 0;
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_scwirod
 *
 * Description: Sample the SCSI data bus making sure the संकेत has been
 *              deनिश्चितed क्रम the correct number of consecutive samples.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_scwirod(u32 p_port, अचिन्हित अक्षर p_data_bit)
अणु
	अचिन्हित अक्षर i;

	i = 0;
	जबतक (i < MAX_SCSI_TAR) अणु

		अगर (RD_HARPOON(p_port + hp_scsidata_0) & p_data_bit)

			i = 0;

		अन्यथा

			i++;

	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_scwiros
 *
 * Description: Sample the SCSI Signal lines making sure the संकेत has been
 *              deनिश्चितed क्रम the correct number of consecutive samples.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_scwiros(u32 p_port, अचिन्हित अक्षर p_data_bit)
अणु
	अचिन्हित अक्षर i;

	i = 0;
	जबतक (i < MAX_SCSI_TAR) अणु

		अगर (RD_HARPOON(p_port + hp_scsisig) & p_data_bit)

			i = 0;

		अन्यथा

			i++;

	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_scvalq
 *
 * Description: Make sure we received a valid data byte.
 *
 *---------------------------------------------------------------------*/

अटल अचिन्हित अक्षर FPT_scvalq(अचिन्हित अक्षर p_quपूर्णांकet)
अणु
	अचिन्हित अक्षर count;

	क्रम (count = 1; count < 0x08; count <<= 1) अणु
		अगर (!(p_quपूर्णांकet & count))
			p_quपूर्णांकet -= 0x80;
	पूर्ण

	अगर (p_quपूर्णांकet & 0x18)
		वापस 0;

	अन्यथा
		वापस 1;
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_scsell
 *
 * Description: Select the specअगरied device ID using a selection समयout
 *              less than 4ms.  If somebody responds then it is a legacy
 *              drive and this ID must be marked as such.
 *
 *---------------------------------------------------------------------*/

अटल अचिन्हित अक्षर FPT_scsell(u32 p_port, अचिन्हित अक्षर targ_id)
अणु
	अचिन्हित दीर्घ i;

	WR_HARPOON(p_port + hp_page_ctrl,
		   (RD_HARPOON(p_port + hp_page_ctrl) | G_INT_DISABLE));

	ARAM_ACCESS(p_port);

	WR_HARPOON(p_port + hp_addstat,
		   (RD_HARPOON(p_port + hp_addstat) | SCAM_TIMER));
	WR_HARPOON(p_port + hp_selसमयout, TO_4ms);

	क्रम (i = p_port + CMD_STRT; i < p_port + CMD_STRT + 12; i += 2) अणु
		WRW_HARPOON(i, (MPM_OP + ACOMMAND));
	पूर्ण
	WRW_HARPOON(i, (BRH_OP + ALWAYS + NP));

	WRW_HARPOON((p_port + hp_पूर्णांकstat),
		    (RESET | TIMEOUT | SEL | BUS_FREE | AUTO_INT));

	WR_HARPOON(p_port + hp_select_id, targ_id);

	WR_HARPOON(p_port + hp_portctrl_0, SCSI_PORT);
	WR_HARPOON(p_port + hp_स्वतःstart_3, (SELECT | CMD_ONLY_STRT));
	WR_HARPOON(p_port + hp_scsictrl_0, (SEL_TAR | ENA_RESEL));

	जबतक (!(RDW_HARPOON((p_port + hp_पूर्णांकstat)) &
		 (RESET | PROG_HLT | TIMEOUT | AUTO_INT))) अणु
	पूर्ण

	अगर (RDW_HARPOON((p_port + hp_पूर्णांकstat)) & RESET)
		FPT_Wait(p_port, TO_250ms);

	DISABLE_AUTO(p_port);

	WR_HARPOON(p_port + hp_addstat,
		   (RD_HARPOON(p_port + hp_addstat) & ~SCAM_TIMER));
	WR_HARPOON(p_port + hp_selसमयout, TO_290ms);

	SGRAM_ACCESS(p_port);

	अगर (RDW_HARPOON((p_port + hp_पूर्णांकstat)) & (RESET | TIMEOUT)) अणु

		WRW_HARPOON((p_port + hp_पूर्णांकstat),
			    (RESET | TIMEOUT | SEL | BUS_FREE | PHASE));

		WR_HARPOON(p_port + hp_page_ctrl,
			   (RD_HARPOON(p_port + hp_page_ctrl) &
			    ~G_INT_DISABLE));

		वापस 0;	/*No legacy device */
	पूर्ण

	अन्यथा अणु

		जबतक (!(RDW_HARPOON((p_port + hp_पूर्णांकstat)) & BUS_FREE)) अणु
			अगर (RD_HARPOON(p_port + hp_scsisig) & SCSI_REQ) अणु
				WR_HARPOON(p_port + hp_scsisig,
					   (SCSI_ACK + S_ILL_PH));
				ACCEPT_MSG(p_port);
			पूर्ण
		पूर्ण

		WRW_HARPOON((p_port + hp_पूर्णांकstat), CLR_ALL_INT_1);

		WR_HARPOON(p_port + hp_page_ctrl,
			   (RD_HARPOON(p_port + hp_page_ctrl) &
			    ~G_INT_DISABLE));

		वापस 1;	/*Found one of them oldies! */
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_scwtsel
 *
 * Description: Wait to be selected by another SCAM initiator.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_scwtsel(u32 p_port)
अणु
	जबतक (!(RDW_HARPOON((p_port + hp_पूर्णांकstat)) & SCAM_SEL)) अणु
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_inisci
 *
 * Description: Setup the data Structure with the info from the EEPROM.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_inisci(अचिन्हित अक्षर p_card, u32 p_port, अचिन्हित अक्षर p_our_id)
अणु
	अचिन्हित अक्षर i, k, max_id;
	अचिन्हित लघु ee_data;
	काष्ठा nvram_info *pCurrNvRam;

	pCurrNvRam = FPT_BL_Card[p_card].pNvRamInfo;

	अगर (RD_HARPOON(p_port + hp_page_ctrl) & NARROW_SCSI_CARD)
		max_id = 0x08;

	अन्यथा
		max_id = 0x10;

	अगर (pCurrNvRam) अणु
		क्रम (i = 0; i < max_id; i++) अणु

			क्रम (k = 0; k < 4; k++)
				FPT_scamInfo[i].id_string[k] =
				    pCurrNvRam->niScamTbl[i][k];
			क्रम (k = 4; k < ID_STRING_LENGTH; k++)
				FPT_scamInfo[i].id_string[k] =
				    (अचिन्हित अक्षर)0x00;

			अगर (FPT_scamInfo[i].id_string[0] == 0x00)
				FPT_scamInfo[i].state = ID_UNUSED;	/*Default to unused ID. */
			अन्यथा
				FPT_scamInfo[i].state = ID_UNASSIGNED;	/*Default to unasचिन्हित ID. */

		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < max_id; i++) अणु
			क्रम (k = 0; k < ID_STRING_LENGTH; k += 2) अणु
				ee_data =
				    FPT_utilEERead(p_port,
						   (अचिन्हित
						    लघु)((EE_SCAMBASE / 2) +
							   (अचिन्हित लघु)(i *
									    ((अचिन्हित लघु)ID_STRING_LENGTH / 2)) + (अचिन्हित लघु)(k / 2)));
				FPT_scamInfo[i].id_string[k] =
				    (अचिन्हित अक्षर)ee_data;
				ee_data >>= 8;
				FPT_scamInfo[i].id_string[k + 1] =
				    (अचिन्हित अक्षर)ee_data;
			पूर्ण

			अगर ((FPT_scamInfo[i].id_string[0] == 0x00) ||
			    (FPT_scamInfo[i].id_string[0] == 0xFF))

				FPT_scamInfo[i].state = ID_UNUSED;	/*Default to unused ID. */

			अन्यथा
				FPT_scamInfo[i].state = ID_UNASSIGNED;	/*Default to unasचिन्हित ID. */

		पूर्ण
	पूर्ण
	क्रम (k = 0; k < ID_STRING_LENGTH; k++)
		FPT_scamInfo[p_our_id].id_string[k] = FPT_scamHAString[k];

पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_scmachid
 *
 * Description: Match the Device ID string with our values stored in
 *              the EEPROM.
 *
 *---------------------------------------------------------------------*/

अटल अचिन्हित अक्षर FPT_scmachid(अचिन्हित अक्षर p_card,
				  अचिन्हित अक्षर p_id_string[])
अणु

	अचिन्हित अक्षर i, k, match;

	क्रम (i = 0; i < MAX_SCSI_TAR; i++) अणु

		match = 1;

		क्रम (k = 0; k < ID_STRING_LENGTH; k++) अणु
			अगर (p_id_string[k] != FPT_scamInfo[i].id_string[k])
				match = 0;
		पूर्ण

		अगर (match) अणु
			FPT_scamInfo[i].state = ID_ASSIGNED;
			वापस i;
		पूर्ण

	पूर्ण

	अगर (p_id_string[0] & BIT(5))
		i = 8;
	अन्यथा
		i = MAX_SCSI_TAR;

	अगर (((p_id_string[0] & 0x06) == 0x02)
	    || ((p_id_string[0] & 0x06) == 0x04))
		match = p_id_string[1] & (अचिन्हित अक्षर)0x1F;
	अन्यथा
		match = 7;

	जबतक (i > 0) अणु
		i--;

		अगर (FPT_scamInfo[match].state == ID_UNUSED) अणु
			क्रम (k = 0; k < ID_STRING_LENGTH; k++) अणु
				FPT_scamInfo[match].id_string[k] =
				    p_id_string[k];
			पूर्ण

			FPT_scamInfo[match].state = ID_ASSIGNED;

			अगर (FPT_BL_Card[p_card].pNvRamInfo == शून्य)
				FPT_BL_Card[p_card].globalFlags |=
				    F_UPDATE_EEPROM;
			वापस match;

		पूर्ण

		match--;

		अगर (match == 0xFF) अणु
			अगर (p_id_string[0] & BIT(5))
				match = 7;
			अन्यथा
				match = MAX_SCSI_TAR - 1;
		पूर्ण
	पूर्ण

	अगर (p_id_string[0] & BIT(7)) अणु
		वापस CLR_PRIORITY;
	पूर्ण

	अगर (p_id_string[0] & BIT(5))
		i = 8;
	अन्यथा
		i = MAX_SCSI_TAR;

	अगर (((p_id_string[0] & 0x06) == 0x02)
	    || ((p_id_string[0] & 0x06) == 0x04))
		match = p_id_string[1] & (अचिन्हित अक्षर)0x1F;
	अन्यथा
		match = 7;

	जबतक (i > 0) अणु

		i--;

		अगर (FPT_scamInfo[match].state == ID_UNASSIGNED) अणु
			क्रम (k = 0; k < ID_STRING_LENGTH; k++) अणु
				FPT_scamInfo[match].id_string[k] =
				    p_id_string[k];
			पूर्ण

			FPT_scamInfo[match].id_string[0] |= BIT(7);
			FPT_scamInfo[match].state = ID_ASSIGNED;
			अगर (FPT_BL_Card[p_card].pNvRamInfo == शून्य)
				FPT_BL_Card[p_card].globalFlags |=
				    F_UPDATE_EEPROM;
			वापस match;

		पूर्ण

		match--;

		अगर (match == 0xFF) अणु
			अगर (p_id_string[0] & BIT(5))
				match = 7;
			अन्यथा
				match = MAX_SCSI_TAR - 1;
		पूर्ण
	पूर्ण

	वापस NO_ID_AVAIL;
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_scsavdi
 *
 * Description: Save off the device SCAM ID strings.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_scsavdi(अचिन्हित अक्षर p_card, u32 p_port)
अणु
	अचिन्हित अक्षर i, k, max_id;
	अचिन्हित लघु ee_data, sum_data;

	sum_data = 0x0000;

	क्रम (i = 1; i < EE_SCAMBASE / 2; i++) अणु
		sum_data += FPT_utilEERead(p_port, i);
	पूर्ण

	FPT_utilEEWriteOnOff(p_port, 1);	/* Enable ग_लिखो access to the EEPROM */

	अगर (RD_HARPOON(p_port + hp_page_ctrl) & NARROW_SCSI_CARD)
		max_id = 0x08;

	अन्यथा
		max_id = 0x10;

	क्रम (i = 0; i < max_id; i++) अणु

		क्रम (k = 0; k < ID_STRING_LENGTH; k += 2) अणु
			ee_data = FPT_scamInfo[i].id_string[k + 1];
			ee_data <<= 8;
			ee_data |= FPT_scamInfo[i].id_string[k];
			sum_data += ee_data;
			FPT_utilEEWrite(p_port, ee_data,
					(अचिन्हित लघु)((EE_SCAMBASE / 2) +
							 (अचिन्हित लघु)(i *
									  ((अचिन्हित लघु)ID_STRING_LENGTH / 2)) + (अचिन्हित लघु)(k / 2)));
		पूर्ण
	पूर्ण

	FPT_utilEEWrite(p_port, sum_data, EEPROM_CHECK_SUM / 2);
	FPT_utilEEWriteOnOff(p_port, 0);	/* Turn off ग_लिखो access */
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_XbowInit
 *
 * Description: Setup the Xbow क्रम normal operation.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_XbowInit(u32 port, अचिन्हित अक्षर ScamFlg)
अणु
	अचिन्हित अक्षर i;

	i = RD_HARPOON(port + hp_page_ctrl);
	WR_HARPOON(port + hp_page_ctrl, (अचिन्हित अक्षर)(i | G_INT_DISABLE));

	WR_HARPOON(port + hp_scsireset, 0x00);
	WR_HARPOON(port + hp_portctrl_1, HOST_MODE8);

	WR_HARPOON(port + hp_scsireset, (DMA_RESET | HPSCSI_RESET | PROG_RESET |
					 FIFO_CLR));

	WR_HARPOON(port + hp_scsireset, SCSI_INI);

	WR_HARPOON(port + hp_clkctrl_0, CLKCTRL_DEFAULT);

	WR_HARPOON(port + hp_scsisig, 0x00);	/*  Clear any संकेतs we might */
	WR_HARPOON(port + hp_scsictrl_0, ENA_SCAM_SEL);

	WRW_HARPOON((port + hp_पूर्णांकstat), CLR_ALL_INT);

	FPT_शेष_पूर्णांकena = RESET | RSEL | PROG_HLT | TIMEOUT |
	    BUS_FREE | XFER_CNT_0 | AUTO_INT;

	अगर ((ScamFlg & SCAM_ENABLED) && (ScamFlg & SCAM_LEVEL2))
		FPT_शेष_पूर्णांकena |= SCAM_SEL;

	WRW_HARPOON((port + hp_पूर्णांकena), FPT_शेष_पूर्णांकena);

	WR_HARPOON(port + hp_selसमयout, TO_290ms);

	/* Turn on SCSI_MODE8 क्रम narrow cards to fix the
	   strapping issue with the DUAL CHANNEL card */
	अगर (RD_HARPOON(port + hp_page_ctrl) & NARROW_SCSI_CARD)
		WR_HARPOON(port + hp_addstat, SCSI_MODE8);

	WR_HARPOON(port + hp_page_ctrl, i);

पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_BusMasterInit
 *
 * Description: Initialize the BusMaster क्रम normal operations.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_BusMasterInit(u32 p_port)
अणु

	WR_HARPOON(p_port + hp_sys_ctrl, DRVR_RST);
	WR_HARPOON(p_port + hp_sys_ctrl, 0x00);

	WR_HARPOON(p_port + hp_host_blk_cnt, XFER_BLK64);

	WR_HARPOON(p_port + hp_bm_ctrl, (BMCTRL_DEFAULT));

	WR_HARPOON(p_port + hp_ee_ctrl, (SCSI_TERM_ENA_H));

	RD_HARPOON(p_port + hp_पूर्णांक_status);	/*Clear पूर्णांकerrupts. */
	WR_HARPOON(p_port + hp_पूर्णांक_mask, (INT_CMD_COMPL | SCSI_INTERRUPT));
	WR_HARPOON(p_port + hp_page_ctrl, (RD_HARPOON(p_port + hp_page_ctrl) &
					   ~SCATTER_EN));
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_DiagEEPROM
 *
 * Description: Verfiy checksum and 'Key' and initialize the EEPROM अगर
 *              necessary.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_DiagEEPROM(u32 p_port)
अणु
	अचिन्हित लघु index, temp, max_wd_cnt;

	अगर (RD_HARPOON(p_port + hp_page_ctrl) & NARROW_SCSI_CARD)
		max_wd_cnt = EEPROM_WD_CNT;
	अन्यथा
		max_wd_cnt = EEPROM_WD_CNT * 2;

	temp = FPT_utilEERead(p_port, FW_SIGNATURE / 2);

	अगर (temp == 0x4641) अणु

		क्रम (index = 2; index < max_wd_cnt; index++) अणु

			temp += FPT_utilEERead(p_port, index);

		पूर्ण

		अगर (temp == FPT_utilEERead(p_port, EEPROM_CHECK_SUM / 2)) अणु

			वापस;	/*EEPROM is Okay so वापस now! */
		पूर्ण
	पूर्ण

	FPT_utilEEWriteOnOff(p_port, (अचिन्हित अक्षर)1);

	क्रम (index = 0; index < max_wd_cnt; index++) अणु

		FPT_utilEEWrite(p_port, 0x0000, index);
	पूर्ण

	temp = 0;

	FPT_utilEEWrite(p_port, 0x4641, FW_SIGNATURE / 2);
	temp += 0x4641;
	FPT_utilEEWrite(p_port, 0x3920, MODEL_NUMB_0 / 2);
	temp += 0x3920;
	FPT_utilEEWrite(p_port, 0x3033, MODEL_NUMB_2 / 2);
	temp += 0x3033;
	FPT_utilEEWrite(p_port, 0x2020, MODEL_NUMB_4 / 2);
	temp += 0x2020;
	FPT_utilEEWrite(p_port, 0x70D3, SYSTEM_CONFIG / 2);
	temp += 0x70D3;
	FPT_utilEEWrite(p_port, 0x0010, BIOS_CONFIG / 2);
	temp += 0x0010;
	FPT_utilEEWrite(p_port, 0x0003, SCAM_CONFIG / 2);
	temp += 0x0003;
	FPT_utilEEWrite(p_port, 0x0007, ADAPTER_SCSI_ID / 2);
	temp += 0x0007;

	FPT_utilEEWrite(p_port, 0x0000, IGNORE_B_SCAN / 2);
	temp += 0x0000;
	FPT_utilEEWrite(p_port, 0x0000, SEND_START_ENA / 2);
	temp += 0x0000;
	FPT_utilEEWrite(p_port, 0x0000, DEVICE_ENABLE / 2);
	temp += 0x0000;

	FPT_utilEEWrite(p_port, 0x4242, SYNC_RATE_TBL01 / 2);
	temp += 0x4242;
	FPT_utilEEWrite(p_port, 0x4242, SYNC_RATE_TBL23 / 2);
	temp += 0x4242;
	FPT_utilEEWrite(p_port, 0x4242, SYNC_RATE_TBL45 / 2);
	temp += 0x4242;
	FPT_utilEEWrite(p_port, 0x4242, SYNC_RATE_TBL67 / 2);
	temp += 0x4242;
	FPT_utilEEWrite(p_port, 0x4242, SYNC_RATE_TBL89 / 2);
	temp += 0x4242;
	FPT_utilEEWrite(p_port, 0x4242, SYNC_RATE_TBLab / 2);
	temp += 0x4242;
	FPT_utilEEWrite(p_port, 0x4242, SYNC_RATE_TBLcd / 2);
	temp += 0x4242;
	FPT_utilEEWrite(p_port, 0x4242, SYNC_RATE_TBLef / 2);
	temp += 0x4242;

	FPT_utilEEWrite(p_port, 0x6C46, 64 / 2);	/*PRODUCT ID */
	temp += 0x6C46;
	FPT_utilEEWrite(p_port, 0x7361, 66 / 2);	/* FlashPoपूर्णांक LT   */
	temp += 0x7361;
	FPT_utilEEWrite(p_port, 0x5068, 68 / 2);
	temp += 0x5068;
	FPT_utilEEWrite(p_port, 0x696F, 70 / 2);
	temp += 0x696F;
	FPT_utilEEWrite(p_port, 0x746E, 72 / 2);
	temp += 0x746E;
	FPT_utilEEWrite(p_port, 0x4C20, 74 / 2);
	temp += 0x4C20;
	FPT_utilEEWrite(p_port, 0x2054, 76 / 2);
	temp += 0x2054;
	FPT_utilEEWrite(p_port, 0x2020, 78 / 2);
	temp += 0x2020;

	index = ((EE_SCAMBASE / 2) + (7 * 16));
	FPT_utilEEWrite(p_port, (0x0700 + TYPE_CODE0), index);
	temp += (0x0700 + TYPE_CODE0);
	index++;
	FPT_utilEEWrite(p_port, 0x5542, index);	/*Venकरोr ID code */
	temp += 0x5542;		/* BUSLOGIC      */
	index++;
	FPT_utilEEWrite(p_port, 0x4C53, index);
	temp += 0x4C53;
	index++;
	FPT_utilEEWrite(p_port, 0x474F, index);
	temp += 0x474F;
	index++;
	FPT_utilEEWrite(p_port, 0x4349, index);
	temp += 0x4349;
	index++;
	FPT_utilEEWrite(p_port, 0x5442, index);	/*Venकरोr unique code */
	temp += 0x5442;		/* BT- 930           */
	index++;
	FPT_utilEEWrite(p_port, 0x202D, index);
	temp += 0x202D;
	index++;
	FPT_utilEEWrite(p_port, 0x3339, index);
	temp += 0x3339;
	index++;		/*Serial #          */
	FPT_utilEEWrite(p_port, 0x2030, index);	/* 01234567         */
	temp += 0x2030;
	index++;
	FPT_utilEEWrite(p_port, 0x5453, index);
	temp += 0x5453;
	index++;
	FPT_utilEEWrite(p_port, 0x5645, index);
	temp += 0x5645;
	index++;
	FPT_utilEEWrite(p_port, 0x2045, index);
	temp += 0x2045;
	index++;
	FPT_utilEEWrite(p_port, 0x202F, index);
	temp += 0x202F;
	index++;
	FPT_utilEEWrite(p_port, 0x4F4A, index);
	temp += 0x4F4A;
	index++;
	FPT_utilEEWrite(p_port, 0x204E, index);
	temp += 0x204E;
	index++;
	FPT_utilEEWrite(p_port, 0x3539, index);
	temp += 0x3539;

	FPT_utilEEWrite(p_port, temp, EEPROM_CHECK_SUM / 2);

	FPT_utilEEWriteOnOff(p_port, (अचिन्हित अक्षर)0);

पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Queue Search Select
 *
 * Description: Try to find a new command to execute.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_queueSearchSelect(काष्ठा sccb_card *pCurrCard,
				  अचिन्हित अक्षर p_card)
अणु
	अचिन्हित अक्षर scan_ptr, lun;
	काष्ठा sccb_mgr_tar_info *currTar_Info;
	काष्ठा sccb *pOldSccb;

	scan_ptr = pCurrCard->scanIndex;
	करो अणु
		currTar_Info = &FPT_sccbMgrTbl[p_card][scan_ptr];
		अगर ((pCurrCard->globalFlags & F_CONLUN_IO) &&
		    ((currTar_Info->TarStatus & TAR_TAG_Q_MASK) !=
		     TAG_Q_TRYING)) अणु
			अगर (currTar_Info->TarSelQ_Cnt != 0) अणु

				scan_ptr++;
				अगर (scan_ptr == MAX_SCSI_TAR)
					scan_ptr = 0;

				क्रम (lun = 0; lun < MAX_LUN; lun++) अणु
					अगर (currTar_Info->TarLUNBusy[lun] == 0) अणु

						pCurrCard->currentSCCB =
						    currTar_Info->TarSelQ_Head;
						pOldSccb = शून्य;

						जबतक ((pCurrCard->
							currentSCCB != शून्य)
						       && (lun !=
							   pCurrCard->
							   currentSCCB->Lun)) अणु
							pOldSccb =
							    pCurrCard->
							    currentSCCB;
							pCurrCard->currentSCCB =
							    (काष्ठा sccb
							     *)(pCurrCard->
								currentSCCB)->
							    Sccb_क्रमwardlink;
						पूर्ण
						अगर (pCurrCard->currentSCCB ==
						    शून्य)
							जारी;
						अगर (pOldSccb != शून्य) अणु
							pOldSccb->
							    Sccb_क्रमwardlink =
							    (काष्ठा sccb
							     *)(pCurrCard->
								currentSCCB)->
							    Sccb_क्रमwardlink;
							pOldSccb->
							    Sccb_backlink =
							    (काष्ठा sccb
							     *)(pCurrCard->
								currentSCCB)->
							    Sccb_backlink;
							currTar_Info->
							    TarSelQ_Cnt--;
						पूर्ण अन्यथा अणु
							currTar_Info->
							    TarSelQ_Head =
							    (काष्ठा sccb
							     *)(pCurrCard->
								currentSCCB)->
							    Sccb_क्रमwardlink;

							अगर (currTar_Info->
							    TarSelQ_Head ==
							    शून्य) अणु
								currTar_Info->
								    TarSelQ_Tail
								    = शून्य;
								currTar_Info->
								    TarSelQ_Cnt
								    = 0;
							पूर्ण अन्यथा अणु
								currTar_Info->
								    TarSelQ_Cnt--;
								currTar_Info->
								    TarSelQ_Head->
								    Sccb_backlink
								    =
								    (काष्ठा sccb
								     *)शून्य;
							पूर्ण
						पूर्ण
						pCurrCard->scanIndex = scan_ptr;

						pCurrCard->globalFlags |=
						    F_NEW_SCCB_CMD;

						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण

			अन्यथा अणु
				scan_ptr++;
				अगर (scan_ptr == MAX_SCSI_TAR) अणु
					scan_ptr = 0;
				पूर्ण
			पूर्ण

		पूर्ण अन्यथा अणु
			अगर ((currTar_Info->TarSelQ_Cnt != 0) &&
			    (currTar_Info->TarLUNBusy[0] == 0)) अणु

				pCurrCard->currentSCCB =
				    currTar_Info->TarSelQ_Head;

				currTar_Info->TarSelQ_Head =
				    (काष्ठा sccb *)(pCurrCard->currentSCCB)->
				    Sccb_क्रमwardlink;

				अगर (currTar_Info->TarSelQ_Head == शून्य) अणु
					currTar_Info->TarSelQ_Tail = शून्य;
					currTar_Info->TarSelQ_Cnt = 0;
				पूर्ण अन्यथा अणु
					currTar_Info->TarSelQ_Cnt--;
					currTar_Info->TarSelQ_Head->
					    Sccb_backlink = (काष्ठा sccb *)शून्य;
				पूर्ण

				scan_ptr++;
				अगर (scan_ptr == MAX_SCSI_TAR)
					scan_ptr = 0;

				pCurrCard->scanIndex = scan_ptr;

				pCurrCard->globalFlags |= F_NEW_SCCB_CMD;

				अवरोध;
			पूर्ण

			अन्यथा अणु
				scan_ptr++;
				अगर (scan_ptr == MAX_SCSI_TAR) अणु
					scan_ptr = 0;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण जबतक (scan_ptr != pCurrCard->scanIndex);
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Queue Select Fail
 *
 * Description: Add the current SCCB to the head of the Queue.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_queueSelectFail(काष्ठा sccb_card *pCurrCard,
				अचिन्हित अक्षर p_card)
अणु
	अचिन्हित अक्षर thisTarg;
	काष्ठा sccb_mgr_tar_info *currTar_Info;

	अगर (pCurrCard->currentSCCB != शून्य) अणु
		thisTarg =
		    (अचिन्हित अक्षर)(((काष्ठा sccb *)(pCurrCard->currentSCCB))->
				    TargID);
		currTar_Info = &FPT_sccbMgrTbl[p_card][thisTarg];

		pCurrCard->currentSCCB->Sccb_backlink = (काष्ठा sccb *)शून्य;

		pCurrCard->currentSCCB->Sccb_क्रमwardlink =
		    currTar_Info->TarSelQ_Head;

		अगर (currTar_Info->TarSelQ_Cnt == 0) अणु
			currTar_Info->TarSelQ_Tail = pCurrCard->currentSCCB;
		पूर्ण

		अन्यथा अणु
			currTar_Info->TarSelQ_Head->Sccb_backlink =
			    pCurrCard->currentSCCB;
		पूर्ण

		currTar_Info->TarSelQ_Head = pCurrCard->currentSCCB;

		pCurrCard->currentSCCB = शून्य;
		currTar_Info->TarSelQ_Cnt++;
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Queue Command Complete
 *
 * Description: Call the callback function with the current SCCB.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_queueCmdComplete(काष्ठा sccb_card *pCurrCard,
				 काष्ठा sccb *p_sccb, अचिन्हित अक्षर p_card)
अणु

	अचिन्हित अक्षर i, SCSIcmd;
	CALL_BK_FN callback;
	काष्ठा sccb_mgr_tar_info *currTar_Info;

	SCSIcmd = p_sccb->Cdb[0];

	अगर (!(p_sccb->Sccb_XferState & F_ALL_XFERRED)) अणु

		अगर ((p_sccb->
		     ControlByte & (SCCB_DATA_XFER_OUT | SCCB_DATA_XFER_IN))
		    && (p_sccb->HostStatus == SCCB_COMPLETE)
		    && (p_sccb->TargetStatus != SSCHECK))

			अगर ((SCSIcmd == SCSI_READ) ||
			    (SCSIcmd == SCSI_WRITE) ||
			    (SCSIcmd == SCSI_READ_EXTENDED) ||
			    (SCSIcmd == SCSI_WRITE_EXTENDED) ||
			    (SCSIcmd == SCSI_WRITE_AND_VERIFY) ||
			    (SCSIcmd == SCSI_START_STOP_UNIT) ||
			    (pCurrCard->globalFlags & F_NO_FILTER)
			    )
				p_sccb->HostStatus = SCCB_DATA_UNDER_RUN;
	पूर्ण

	अगर (p_sccb->SccbStatus == SCCB_IN_PROCESS) अणु
		अगर (p_sccb->HostStatus || p_sccb->TargetStatus)
			p_sccb->SccbStatus = SCCB_ERROR;
		अन्यथा
			p_sccb->SccbStatus = SCCB_SUCCESS;
	पूर्ण

	अगर (p_sccb->Sccb_XferState & F_AUTO_SENSE) अणु

		p_sccb->CdbLength = p_sccb->Save_CdbLen;
		क्रम (i = 0; i < 6; i++) अणु
			p_sccb->Cdb[i] = p_sccb->Save_Cdb[i];
		पूर्ण
	पूर्ण

	अगर ((p_sccb->OperationCode == RESIDUAL_SG_COMMAND) ||
	    (p_sccb->OperationCode == RESIDUAL_COMMAND)) अणु

		FPT_utilUpdateResidual(p_sccb);
	पूर्ण

	pCurrCard->cmdCounter--;
	अगर (!pCurrCard->cmdCounter) अणु

		अगर (pCurrCard->globalFlags & F_GREEN_PC) अणु
			WR_HARPOON(pCurrCard->ioPort + hp_clkctrl_0,
				   (PWR_DWN | CLKCTRL_DEFAULT));
			WR_HARPOON(pCurrCard->ioPort + hp_sys_ctrl, STOP_CLK);
		पूर्ण

		WR_HARPOON(pCurrCard->ioPort + hp_semaphore,
			   (RD_HARPOON(pCurrCard->ioPort + hp_semaphore) &
			    ~SCCB_MGR_ACTIVE));

	पूर्ण

	अगर (pCurrCard->discQCount != 0) अणु
		currTar_Info = &FPT_sccbMgrTbl[p_card][p_sccb->TargID];
		अगर (((pCurrCard->globalFlags & F_CONLUN_IO) &&
		     ((currTar_Info->TarStatus & TAR_TAG_Q_MASK) !=
		      TAG_Q_TRYING))) अणु
			pCurrCard->discQCount--;
			pCurrCard->discQ_Tbl[currTar_Info->
					     LunDiscQ_Idx[p_sccb->Lun]] = शून्य;
		पूर्ण अन्यथा अणु
			अगर (p_sccb->Sccb_tag) अणु
				pCurrCard->discQCount--;
				pCurrCard->discQ_Tbl[p_sccb->Sccb_tag] = शून्य;
			पूर्ण अन्यथा अणु
				pCurrCard->discQCount--;
				pCurrCard->discQ_Tbl[currTar_Info->
						     LunDiscQ_Idx[0]] = शून्य;
			पूर्ण
		पूर्ण

	पूर्ण

	callback = (CALL_BK_FN) p_sccb->SccbCallback;
	callback(p_sccb);
	pCurrCard->globalFlags |= F_NEW_SCCB_CMD;
	pCurrCard->currentSCCB = शून्य;
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Queue Disconnect
 *
 * Description: Add SCCB to our disconnect array.
 *
 *---------------------------------------------------------------------*/
अटल व्योम FPT_queueDisconnect(काष्ठा sccb *p_sccb, अचिन्हित अक्षर p_card)
अणु
	काष्ठा sccb_mgr_tar_info *currTar_Info;

	currTar_Info = &FPT_sccbMgrTbl[p_card][p_sccb->TargID];

	अगर (((FPT_BL_Card[p_card].globalFlags & F_CONLUN_IO) &&
	     ((currTar_Info->TarStatus & TAR_TAG_Q_MASK) != TAG_Q_TRYING))) अणु
		FPT_BL_Card[p_card].discQ_Tbl[currTar_Info->
					      LunDiscQ_Idx[p_sccb->Lun]] =
		    p_sccb;
	पूर्ण अन्यथा अणु
		अगर (p_sccb->Sccb_tag) अणु
			FPT_BL_Card[p_card].discQ_Tbl[p_sccb->Sccb_tag] =
			    p_sccb;
			FPT_sccbMgrTbl[p_card][p_sccb->TargID].TarLUNBusy[0] =
			    0;
			FPT_sccbMgrTbl[p_card][p_sccb->TargID].TarTagQ_Cnt++;
		पूर्ण अन्यथा अणु
			FPT_BL_Card[p_card].discQ_Tbl[currTar_Info->
						      LunDiscQ_Idx[0]] = p_sccb;
		पूर्ण
	पूर्ण
	FPT_BL_Card[p_card].currentSCCB = शून्य;
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Queue Flush SCCB
 *
 * Description: Flush all SCCB's back to the host driver क्रम this target.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_queueFlushSccb(अचिन्हित अक्षर p_card, अचिन्हित अक्षर error_code)
अणु
	अचिन्हित अक्षर qtag, thisTarg;
	काष्ठा sccb *currSCCB;
	काष्ठा sccb_mgr_tar_info *currTar_Info;

	currSCCB = FPT_BL_Card[p_card].currentSCCB;
	अगर (currSCCB != शून्य) अणु
		thisTarg = (अचिन्हित अक्षर)currSCCB->TargID;
		currTar_Info = &FPT_sccbMgrTbl[p_card][thisTarg];

		क्रम (qtag = 0; qtag < QUEUE_DEPTH; qtag++) अणु

			अगर (FPT_BL_Card[p_card].discQ_Tbl[qtag] &&
			    (FPT_BL_Card[p_card].discQ_Tbl[qtag]->TargID ==
			     thisTarg)) अणु

				FPT_BL_Card[p_card].discQ_Tbl[qtag]->
				    HostStatus = (अचिन्हित अक्षर)error_code;

				FPT_queueCmdComplete(&FPT_BL_Card[p_card],
						     FPT_BL_Card[p_card].
						     discQ_Tbl[qtag], p_card);

				FPT_BL_Card[p_card].discQ_Tbl[qtag] = शून्य;
				currTar_Info->TarTagQ_Cnt--;

			पूर्ण
		पूर्ण
	पूर्ण

पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Queue Flush Target SCCB
 *
 * Description: Flush all SCCB's back to the host driver क्रम this target.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_queueFlushTargSccb(अचिन्हित अक्षर p_card, अचिन्हित अक्षर thisTarg,
				   अचिन्हित अक्षर error_code)
अणु
	अचिन्हित अक्षर qtag;
	काष्ठा sccb_mgr_tar_info *currTar_Info;

	currTar_Info = &FPT_sccbMgrTbl[p_card][thisTarg];

	क्रम (qtag = 0; qtag < QUEUE_DEPTH; qtag++) अणु

		अगर (FPT_BL_Card[p_card].discQ_Tbl[qtag] &&
		    (FPT_BL_Card[p_card].discQ_Tbl[qtag]->TargID == thisTarg)) अणु

			FPT_BL_Card[p_card].discQ_Tbl[qtag]->HostStatus =
			    (अचिन्हित अक्षर)error_code;

			FPT_queueCmdComplete(&FPT_BL_Card[p_card],
					     FPT_BL_Card[p_card].
					     discQ_Tbl[qtag], p_card);

			FPT_BL_Card[p_card].discQ_Tbl[qtag] = शून्य;
			currTar_Info->TarTagQ_Cnt--;

		पूर्ण
	पूर्ण

पूर्ण

अटल व्योम FPT_queueAddSccb(काष्ठा sccb *p_SCCB, अचिन्हित अक्षर p_card)
अणु
	काष्ठा sccb_mgr_tar_info *currTar_Info;
	currTar_Info = &FPT_sccbMgrTbl[p_card][p_SCCB->TargID];

	p_SCCB->Sccb_क्रमwardlink = शून्य;

	p_SCCB->Sccb_backlink = currTar_Info->TarSelQ_Tail;

	अगर (currTar_Info->TarSelQ_Cnt == 0) अणु

		currTar_Info->TarSelQ_Head = p_SCCB;
	पूर्ण

	अन्यथा अणु

		currTar_Info->TarSelQ_Tail->Sccb_क्रमwardlink = p_SCCB;
	पूर्ण

	currTar_Info->TarSelQ_Tail = p_SCCB;
	currTar_Info->TarSelQ_Cnt++;
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Queue Find SCCB
 *
 * Description: Search the target select Queue क्रम this SCCB, and
 *              हटाओ it अगर found.
 *
 *---------------------------------------------------------------------*/

अटल अचिन्हित अक्षर FPT_queueFindSccb(काष्ठा sccb *p_SCCB,
				       अचिन्हित अक्षर p_card)
अणु
	काष्ठा sccb *q_ptr;
	काष्ठा sccb_mgr_tar_info *currTar_Info;

	currTar_Info = &FPT_sccbMgrTbl[p_card][p_SCCB->TargID];

	q_ptr = currTar_Info->TarSelQ_Head;

	जबतक (q_ptr != शून्य) अणु

		अगर (q_ptr == p_SCCB) अणु

			अगर (currTar_Info->TarSelQ_Head == q_ptr) अणु

				currTar_Info->TarSelQ_Head =
				    q_ptr->Sccb_क्रमwardlink;
			पूर्ण

			अगर (currTar_Info->TarSelQ_Tail == q_ptr) अणु

				currTar_Info->TarSelQ_Tail =
				    q_ptr->Sccb_backlink;
			पूर्ण

			अगर (q_ptr->Sccb_क्रमwardlink != शून्य) अणु
				q_ptr->Sccb_क्रमwardlink->Sccb_backlink =
				    q_ptr->Sccb_backlink;
			पूर्ण

			अगर (q_ptr->Sccb_backlink != शून्य) अणु
				q_ptr->Sccb_backlink->Sccb_क्रमwardlink =
				    q_ptr->Sccb_क्रमwardlink;
			पूर्ण

			currTar_Info->TarSelQ_Cnt--;

			वापस 1;
		पूर्ण

		अन्यथा अणु
			q_ptr = q_ptr->Sccb_क्रमwardlink;
		पूर्ण
	पूर्ण

	वापस 0;

पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Utility Update Residual Count
 *
 * Description: Update the XferCnt to the reमुख्यing byte count.
 *              If we transferred all the data then just ग_लिखो zero.
 *              If Non-SG transfer then report Total Cnt - Actual Transfer
 *              Cnt.  For SG transfers add the count fields of all
 *              reमुख्यing SG elements, as well as any partial reमुख्यing
 *              element.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_utilUpdateResidual(काष्ठा sccb *p_SCCB)
अणु
	अचिन्हित दीर्घ partial_cnt;
	अचिन्हित पूर्णांक sg_index;
	काष्ठा blogic_sg_seg *segp;

	अगर (p_SCCB->Sccb_XferState & F_ALL_XFERRED) अणु

		p_SCCB->DataLength = 0x0000;
	पूर्ण

	अन्यथा अगर (p_SCCB->Sccb_XferState & F_SG_XFER) अणु

		partial_cnt = 0x0000;

		sg_index = p_SCCB->Sccb_sgseg;


		अगर (p_SCCB->Sccb_SGoffset) अणु

			partial_cnt = p_SCCB->Sccb_SGoffset;
			sg_index++;
		पूर्ण

		जबतक (((अचिन्हित दीर्घ)sg_index *
			(अचिन्हित दीर्घ)SG_ELEMENT_SIZE) < p_SCCB->DataLength) अणु
			segp = (काष्ठा blogic_sg_seg *)(p_SCCB->DataPoपूर्णांकer) +
					(sg_index * 2);
			partial_cnt += segp->segbytes;
			sg_index++;
		पूर्ण

		p_SCCB->DataLength = partial_cnt;
	पूर्ण

	अन्यथा अणु

		p_SCCB->DataLength -= p_SCCB->Sccb_ATC;
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Wait 1 Second
 *
 * Description: Wait क्रम 1 second.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_Wait1Second(u32 p_port)
अणु
	अचिन्हित अक्षर i;

	क्रम (i = 0; i < 4; i++) अणु

		FPT_Wait(p_port, TO_250ms);

		अगर ((RD_HARPOON(p_port + hp_scsictrl_0) & SCSI_RST))
			अवरोध;

		अगर ((RDW_HARPOON((p_port + hp_पूर्णांकstat)) & SCAM_SEL))
			अवरोध;
	पूर्ण
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: FPT_Wait
 *
 * Description: Wait the desired delay.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_Wait(u32 p_port, अचिन्हित अक्षर p_delay)
अणु
	अचिन्हित अक्षर old_समयr;
	अचिन्हित अक्षर green_flag;

	old_समयr = RD_HARPOON(p_port + hp_selसमयout);

	green_flag = RD_HARPOON(p_port + hp_clkctrl_0);
	WR_HARPOON(p_port + hp_clkctrl_0, CLKCTRL_DEFAULT);

	WR_HARPOON(p_port + hp_selसमयout, p_delay);
	WRW_HARPOON((p_port + hp_पूर्णांकstat), TIMEOUT);
	WRW_HARPOON((p_port + hp_पूर्णांकena), (FPT_शेष_पूर्णांकena & ~TIMEOUT));

	WR_HARPOON(p_port + hp_portctrl_0,
		   (RD_HARPOON(p_port + hp_portctrl_0) | START_TO));

	जबतक (!(RDW_HARPOON((p_port + hp_पूर्णांकstat)) & TIMEOUT)) अणु

		अगर ((RD_HARPOON(p_port + hp_scsictrl_0) & SCSI_RST))
			अवरोध;

		अगर ((RDW_HARPOON((p_port + hp_पूर्णांकstat)) & SCAM_SEL))
			अवरोध;
	पूर्ण

	WR_HARPOON(p_port + hp_portctrl_0,
		   (RD_HARPOON(p_port + hp_portctrl_0) & ~START_TO));

	WRW_HARPOON((p_port + hp_पूर्णांकstat), TIMEOUT);
	WRW_HARPOON((p_port + hp_पूर्णांकena), FPT_शेष_पूर्णांकena);

	WR_HARPOON(p_port + hp_clkctrl_0, green_flag);

	WR_HARPOON(p_port + hp_selसमयout, old_समयr);
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Enable/Disable Write to EEPROM
 *
 * Description: The EEPROM must first be enabled क्रम ग_लिखोs
 *              A total of 9 घड़ीs are needed.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_utilEEWriteOnOff(u32 p_port, अचिन्हित अक्षर p_mode)
अणु
	अचिन्हित अक्षर ee_value;

	ee_value =
	    (अचिन्हित अक्षर)(RD_HARPOON(p_port + hp_ee_ctrl) &
			    (EXT_ARB_ACK | SCSI_TERM_ENA_H));

	अगर (p_mode)

		FPT_utilEESendCmdAddr(p_port, EWEN, EWEN_ADDR);

	अन्यथा

		FPT_utilEESendCmdAddr(p_port, EWDS, EWDS_ADDR);

	WR_HARPOON(p_port + hp_ee_ctrl, (ee_value | SEE_MS));	/*Turn off CS */
	WR_HARPOON(p_port + hp_ee_ctrl, ee_value);	/*Turn off Master Select */
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Write EEPROM
 *
 * Description: Write a word to the EEPROM at the specअगरied
 *              address.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_utilEEWrite(u32 p_port, अचिन्हित लघु ee_data,
			    अचिन्हित लघु ee_addr)
अणु

	अचिन्हित अक्षर ee_value;
	अचिन्हित लघु i;

	ee_value =
	    (अचिन्हित
	     अक्षर)((RD_HARPOON(p_port + hp_ee_ctrl) &
		    (EXT_ARB_ACK | SCSI_TERM_ENA_H)) | (SEE_MS | SEE_CS));

	FPT_utilEESendCmdAddr(p_port, EE_WRITE, ee_addr);

	ee_value |= (SEE_MS + SEE_CS);

	क्रम (i = 0x8000; i != 0; i >>= 1) अणु

		अगर (i & ee_data)
			ee_value |= SEE_DO;
		अन्यथा
			ee_value &= ~SEE_DO;

		WR_HARPOON(p_port + hp_ee_ctrl, ee_value);
		WR_HARPOON(p_port + hp_ee_ctrl, ee_value);
		ee_value |= SEE_CLK;	/* Clock  data! */
		WR_HARPOON(p_port + hp_ee_ctrl, ee_value);
		WR_HARPOON(p_port + hp_ee_ctrl, ee_value);
		ee_value &= ~SEE_CLK;
		WR_HARPOON(p_port + hp_ee_ctrl, ee_value);
		WR_HARPOON(p_port + hp_ee_ctrl, ee_value);
	पूर्ण
	ee_value &= (EXT_ARB_ACK | SCSI_TERM_ENA_H);
	WR_HARPOON(p_port + hp_ee_ctrl, (ee_value | SEE_MS));

	FPT_Wait(p_port, TO_10ms);

	WR_HARPOON(p_port + hp_ee_ctrl, (ee_value | SEE_MS | SEE_CS));	/* Set CS to EEPROM */
	WR_HARPOON(p_port + hp_ee_ctrl, (ee_value | SEE_MS));	/* Turn off CS */
	WR_HARPOON(p_port + hp_ee_ctrl, ee_value);	/* Turn off Master Select */
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Read EEPROM
 *
 * Description: Read a word from the EEPROM at the desired
 *              address.
 *
 *---------------------------------------------------------------------*/

अटल अचिन्हित लघु FPT_utilEERead(u32 p_port,
				     अचिन्हित लघु ee_addr)
अणु
	अचिन्हित लघु i, ee_data1, ee_data2;

	i = 0;
	ee_data1 = FPT_utilEEReadOrg(p_port, ee_addr);
	करो अणु
		ee_data2 = FPT_utilEEReadOrg(p_port, ee_addr);

		अगर (ee_data1 == ee_data2)
			वापस ee_data1;

		ee_data1 = ee_data2;
		i++;

	पूर्ण जबतक (i < 4);

	वापस ee_data1;
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Read EEPROM Original 
 *
 * Description: Read a word from the EEPROM at the desired
 *              address.
 *
 *---------------------------------------------------------------------*/

अटल अचिन्हित लघु FPT_utilEEReadOrg(u32 p_port, अचिन्हित लघु ee_addr)
अणु

	अचिन्हित अक्षर ee_value;
	अचिन्हित लघु i, ee_data;

	ee_value =
	    (अचिन्हित
	     अक्षर)((RD_HARPOON(p_port + hp_ee_ctrl) &
		    (EXT_ARB_ACK | SCSI_TERM_ENA_H)) | (SEE_MS | SEE_CS));

	FPT_utilEESendCmdAddr(p_port, EE_READ, ee_addr);

	ee_value |= (SEE_MS + SEE_CS);
	ee_data = 0;

	क्रम (i = 1; i <= 16; i++) अणु

		ee_value |= SEE_CLK;	/* Clock  data! */
		WR_HARPOON(p_port + hp_ee_ctrl, ee_value);
		WR_HARPOON(p_port + hp_ee_ctrl, ee_value);
		ee_value &= ~SEE_CLK;
		WR_HARPOON(p_port + hp_ee_ctrl, ee_value);
		WR_HARPOON(p_port + hp_ee_ctrl, ee_value);

		ee_data <<= 1;

		अगर (RD_HARPOON(p_port + hp_ee_ctrl) & SEE_DI)
			ee_data |= 1;
	पूर्ण

	ee_value &= ~(SEE_MS + SEE_CS);
	WR_HARPOON(p_port + hp_ee_ctrl, (ee_value | SEE_MS));	/*Turn off CS */
	WR_HARPOON(p_port + hp_ee_ctrl, ee_value);	/*Turn off Master Select */

	वापस ee_data;
पूर्ण

/*---------------------------------------------------------------------
 *
 * Function: Send EE command and Address to the EEPROM
 *
 * Description: Transfers the correct command and sends the address
 *              to the eeprom.
 *
 *---------------------------------------------------------------------*/

अटल व्योम FPT_utilEESendCmdAddr(u32 p_port, अचिन्हित अक्षर ee_cmd,
				  अचिन्हित लघु ee_addr)
अणु
	अचिन्हित अक्षर ee_value;
	अचिन्हित अक्षर narrow_flg;

	अचिन्हित लघु i;

	narrow_flg =
	    (अचिन्हित अक्षर)(RD_HARPOON(p_port + hp_page_ctrl) &
			    NARROW_SCSI_CARD);

	ee_value = SEE_MS;
	WR_HARPOON(p_port + hp_ee_ctrl, ee_value);

	ee_value |= SEE_CS;	/* Set CS to EEPROM */
	WR_HARPOON(p_port + hp_ee_ctrl, ee_value);

	क्रम (i = 0x04; i != 0; i >>= 1) अणु

		अगर (i & ee_cmd)
			ee_value |= SEE_DO;
		अन्यथा
			ee_value &= ~SEE_DO;

		WR_HARPOON(p_port + hp_ee_ctrl, ee_value);
		WR_HARPOON(p_port + hp_ee_ctrl, ee_value);
		ee_value |= SEE_CLK;	/* Clock  data! */
		WR_HARPOON(p_port + hp_ee_ctrl, ee_value);
		WR_HARPOON(p_port + hp_ee_ctrl, ee_value);
		ee_value &= ~SEE_CLK;
		WR_HARPOON(p_port + hp_ee_ctrl, ee_value);
		WR_HARPOON(p_port + hp_ee_ctrl, ee_value);
	पूर्ण

	अगर (narrow_flg)
		i = 0x0080;

	अन्यथा
		i = 0x0200;

	जबतक (i != 0) अणु

		अगर (i & ee_addr)
			ee_value |= SEE_DO;
		अन्यथा
			ee_value &= ~SEE_DO;

		WR_HARPOON(p_port + hp_ee_ctrl, ee_value);
		WR_HARPOON(p_port + hp_ee_ctrl, ee_value);
		ee_value |= SEE_CLK;	/* Clock  data! */
		WR_HARPOON(p_port + hp_ee_ctrl, ee_value);
		WR_HARPOON(p_port + hp_ee_ctrl, ee_value);
		ee_value &= ~SEE_CLK;
		WR_HARPOON(p_port + hp_ee_ctrl, ee_value);
		WR_HARPOON(p_port + hp_ee_ctrl, ee_value);

		i >>= 1;
	पूर्ण
पूर्ण

अटल अचिन्हित लघु FPT_CalcCrc16(अचिन्हित अक्षर buffer[])
अणु
	अचिन्हित लघु crc = 0;
	पूर्णांक i, j;
	अचिन्हित लघु ch;
	क्रम (i = 0; i < ID_STRING_LENGTH; i++) अणु
		ch = (अचिन्हित लघु)buffer[i];
		क्रम (j = 0; j < 8; j++) अणु
			अगर ((crc ^ ch) & 1)
				crc = (crc >> 1) ^ CRCMASK;
			अन्यथा
				crc >>= 1;
			ch >>= 1;
		पूर्ण
	पूर्ण
	वापस crc;
पूर्ण

अटल अचिन्हित अक्षर FPT_CalcLrc(अचिन्हित अक्षर buffer[])
अणु
	पूर्णांक i;
	अचिन्हित अक्षर lrc;
	lrc = 0;
	क्रम (i = 0; i < ID_STRING_LENGTH; i++)
		lrc ^= buffer[i];
	वापस lrc;
पूर्ण

/*
  The following अंतरभूत definitions aव्योम type conflicts.
*/

अटल अंतरभूत अचिन्हित अक्षर
FlashPoपूर्णांक__ProbeHostAdapter(काष्ठा fpoपूर्णांक_info *FlashPoपूर्णांकInfo)
अणु
	वापस FlashPoपूर्णांक_ProbeHostAdapter((काष्ठा sccb_mgr_info *)
					   FlashPoपूर्णांकInfo);
पूर्ण

अटल अंतरभूत व्योम *
FlashPoपूर्णांक__HardwareResetHostAdapter(काष्ठा fpoपूर्णांक_info *FlashPoपूर्णांकInfo)
अणु
	वापस FlashPoपूर्णांक_HardwareResetHostAdapter((काष्ठा sccb_mgr_info *)
						   FlashPoपूर्णांकInfo);
पूर्ण

अटल अंतरभूत व्योम
FlashPoपूर्णांक__ReleaseHostAdapter(व्योम *CardHandle)
अणु
	FlashPoपूर्णांक_ReleaseHostAdapter(CardHandle);
पूर्ण

अटल अंतरभूत व्योम
FlashPoपूर्णांक__StartCCB(व्योम *CardHandle, काष्ठा blogic_ccb *CCB)
अणु
	FlashPoपूर्णांक_StartCCB(CardHandle, (काष्ठा sccb *)CCB);
पूर्ण

अटल अंतरभूत व्योम
FlashPoपूर्णांक__AbortCCB(व्योम *CardHandle, काष्ठा blogic_ccb *CCB)
अणु
	FlashPoपूर्णांक_AbortCCB(CardHandle, (काष्ठा sccb *)CCB);
पूर्ण

अटल अंतरभूत bool
FlashPoपूर्णांक__InterruptPending(व्योम *CardHandle)
अणु
	वापस FlashPoपूर्णांक_InterruptPending(CardHandle);
पूर्ण

अटल अंतरभूत पूर्णांक
FlashPoपूर्णांक__HandleInterrupt(व्योम *CardHandle)
अणु
	वापस FlashPoपूर्णांक_HandleInterrupt(CardHandle);
पूर्ण

#घोषणा FlashPoपूर्णांक_ProbeHostAdapter	    FlashPoपूर्णांक__ProbeHostAdapter
#घोषणा FlashPoपूर्णांक_HardwareResetHostAdapter FlashPoपूर्णांक__HardwareResetHostAdapter
#घोषणा FlashPoपूर्णांक_ReleaseHostAdapter	    FlashPoपूर्णांक__ReleaseHostAdapter
#घोषणा FlashPoपूर्णांक_StartCCB		    FlashPoपूर्णांक__StartCCB
#घोषणा FlashPoपूर्णांक_AbortCCB		    FlashPoपूर्णांक__AbortCCB
#घोषणा FlashPoपूर्णांक_InterruptPending	    FlashPoपूर्णांक__InterruptPending
#घोषणा FlashPoपूर्णांक_HandleInterrupt	    FlashPoपूर्णांक__HandleInterrupt

#अन्यथा				/* !CONFIG_SCSI_FLASHPOINT */

/*
  Define prototypes क्रम the FlashPoपूर्णांक SCCB Manager Functions.
*/

बाह्य अचिन्हित अक्षर FlashPoपूर्णांक_ProbeHostAdapter(काष्ठा fpoपूर्णांक_info *);
बाह्य व्योम *FlashPoपूर्णांक_HardwareResetHostAdapter(काष्ठा fpoपूर्णांक_info *);
बाह्य व्योम FlashPoपूर्णांक_StartCCB(व्योम *, काष्ठा blogic_ccb *);
बाह्य पूर्णांक FlashPoपूर्णांक_AbortCCB(व्योम *, काष्ठा blogic_ccb *);
बाह्य bool FlashPoपूर्णांक_InterruptPending(व्योम *);
बाह्य पूर्णांक FlashPoपूर्णांक_HandleInterrupt(व्योम *);
बाह्य व्योम FlashPoपूर्णांक_ReleaseHostAdapter(व्योम *);

#पूर्ण_अगर				/* CONFIG_SCSI_FLASHPOINT */
