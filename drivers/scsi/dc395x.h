<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/************************************************************************/
/*									*/
/*	dc395x.h							*/
/*									*/
/*	Device Driver क्रम Tekram DC395(U/UW/F), DC315(U)		*/
/*	PCI SCSI Bus Master Host Adapter				*/
/*	(SCSI chip set used Tekram ASIC TRM-S1040)			*/
/*									*/
/************************************************************************/
#अगर_अघोषित DC395x_H
#घोषणा DC395x_H

/************************************************************************/
/*									*/
/*	Initial values							*/
/*									*/
/************************************************************************/
#घोषणा DC395x_MAX_CMD_QUEUE		32
/* #घोषणा DC395x_MAX_QTAGS		32 */
#घोषणा DC395x_MAX_QTAGS		16
#घोषणा DC395x_MAX_SCSI_ID		16
#घोषणा DC395x_MAX_CMD_PER_LUN		DC395x_MAX_QTAGS
#घोषणा DC395x_MAX_SG_TABLESIZE		64	/* HW limitation			*/
#घोषणा DC395x_MAX_SG_LISTENTRY		64	/* Must be equal or lower to previous	*/
						/* item					*/
#घोषणा DC395x_MAX_SRB_CNT		63
/* #घोषणा DC395x_MAX_CAN_QUEUE		7 * DC395x_MAX_QTAGS */
#घोषणा DC395x_MAX_CAN_QUEUE		DC395x_MAX_SRB_CNT
#घोषणा DC395x_END_SCAN			2
#घोषणा DC395x_SEL_TIMEOUT		153	/* 250 ms selection समयout (@ 40 MHz)	*/
#घोषणा DC395x_MAX_RETRIES		3

#अगर 0
#घोषणा SYNC_FIRST
#पूर्ण_अगर

#घोषणा NORM_REC_LVL			0

/************************************************************************/
/*									*/
/*	Various definitions						*/
/*									*/
/************************************************************************/
#घोषणा BIT31				0x80000000
#घोषणा BIT30				0x40000000
#घोषणा BIT29				0x20000000
#घोषणा BIT28				0x10000000
#घोषणा BIT27				0x08000000
#घोषणा BIT26				0x04000000
#घोषणा BIT25				0x02000000
#घोषणा BIT24				0x01000000
#घोषणा BIT23				0x00800000
#घोषणा BIT22				0x00400000
#घोषणा BIT21				0x00200000
#घोषणा BIT20				0x00100000
#घोषणा BIT19				0x00080000
#घोषणा BIT18				0x00040000
#घोषणा BIT17				0x00020000
#घोषणा BIT16				0x00010000
#घोषणा BIT15				0x00008000
#घोषणा BIT14				0x00004000
#घोषणा BIT13				0x00002000
#घोषणा BIT12				0x00001000
#घोषणा BIT11				0x00000800
#घोषणा BIT10				0x00000400
#घोषणा BIT9				0x00000200
#घोषणा BIT8				0x00000100
#घोषणा BIT7				0x00000080
#घोषणा BIT6				0x00000040
#घोषणा BIT5				0x00000020
#घोषणा BIT4				0x00000010
#घोषणा BIT3				0x00000008
#घोषणा BIT2				0x00000004
#घोषणा BIT1				0x00000002
#घोषणा BIT0				0x00000001

/* UnitCtrlFlag */
#घोषणा UNIT_ALLOCATED			BIT0
#घोषणा UNIT_INFO_CHANGED		BIT1
#घोषणा FORMATING_MEDIA			BIT2
#घोषणा UNIT_RETRY			BIT3

/* UnitFlags */
#घोषणा DASD_SUPPORT			BIT0
#घोषणा SCSI_SUPPORT			BIT1
#घोषणा ASPI_SUPPORT			BIT2

/* SRBState machine definition */
#घोषणा SRB_FREE			0x0000
#घोषणा SRB_WAIT			0x0001
#घोषणा SRB_READY			0x0002
#घोषणा SRB_MSGOUT			0x0004	/* arbitration+msg_out 1st byte		*/
#घोषणा SRB_MSGIN			0x0008
#घोषणा SRB_EXTEND_MSGIN		0x0010
#घोषणा SRB_COMMAND			0x0020
#घोषणा SRB_START_			0x0040	/* arbitration+msg_out+command_out	*/
#घोषणा SRB_DISCONNECT			0x0080
#घोषणा SRB_DATA_XFER			0x0100
#घोषणा SRB_XFERPAD			0x0200
#घोषणा SRB_STATUS			0x0400
#घोषणा SRB_COMPLETED			0x0800
#घोषणा SRB_ABORT_SENT			0x1000
#घोषणा SRB_DO_SYNC_NEGO		0x2000
#घोषणा SRB_DO_WIDE_NEGO		0x4000
#घोषणा SRB_UNEXPECT_RESEL		0x8000

/************************************************************************/
/*									*/
/*	ACB Config							*/
/*									*/
/************************************************************************/
#घोषणा HCC_WIDE_CARD			0x20
#घोषणा HCC_SCSI_RESET			0x10
#घोषणा HCC_PARITY			0x08
#घोषणा HCC_AUTOTERM			0x04
#घोषणा HCC_LOW8TERM			0x02
#घोषणा HCC_UP8TERM			0x01

/* ACBFlag */
#घोषणा RESET_DEV			BIT0
#घोषणा RESET_DETECT			BIT1
#घोषणा RESET_DONE			BIT2

/* DCBFlag */
#घोषणा ABORT_DEV_			BIT0

/* SRBstatus */
#घोषणा SRB_OK				BIT0
#घोषणा ABORTION			BIT1
#घोषणा OVER_RUN			BIT2
#घोषणा UNDER_RUN			BIT3
#घोषणा PARITY_ERROR			BIT4
#घोषणा SRB_ERROR			BIT5

/* SRBFlag */
#घोषणा DATAOUT				BIT7
#घोषणा DATAIN				BIT6
#घोषणा RESIDUAL_VALID			BIT5
#घोषणा ENABLE_TIMER			BIT4
#घोषणा RESET_DEV0			BIT2
#घोषणा ABORT_DEV			BIT1
#घोषणा AUTO_REQSENSE			BIT0

/* Adapter status */
#घोषणा H_STATUS_GOOD			0
#घोषणा H_SEL_TIMEOUT			0x11
#घोषणा H_OVER_UNDER_RUN		0x12
#घोषणा H_UNEXP_BUS_FREE		0x13
#घोषणा H_TARGET_PHASE_F		0x14
#घोषणा H_INVALID_CCB_OP		0x16
#घोषणा H_LINK_CCB_BAD			0x17
#घोषणा H_BAD_TARGET_सूची		0x18
#घोषणा H_DUPLICATE_CCB			0x19
#घोषणा H_BAD_CCB_OR_SG			0x1A
#घोषणा H_ABORT				0x0FF

/* SCSI BUS Status byte codes */
#घोषणा SCSI_STAT_UNEXP_BUS_F		0xFD	/* Unexpect Bus Free			*/
#घोषणा SCSI_STAT_BUS_RST_DETECT	0xFE	/* Scsi Bus Reset detected		*/
#घोषणा SCSI_STAT_SEL_TIMEOUT		0xFF	/* Selection Time out			*/

/* Sync_Mode */
#घोषणा SYNC_WIDE_TAG_ATNT_DISABLE	0
#घोषणा SYNC_NEGO_ENABLE		BIT0
#घोषणा SYNC_NEGO_DONE			BIT1
#घोषणा WIDE_NEGO_ENABLE		BIT2
#घोषणा WIDE_NEGO_DONE			BIT3
#घोषणा WIDE_NEGO_STATE			BIT4
#घोषणा EN_TAG_QUEUEING			BIT5
#घोषणा EN_ATN_STOP			BIT6

#घोषणा SYNC_NEGO_OFFSET		15

/* cmd->result */
#घोषणा STATUS_MASK_			0xFF
#घोषणा MSG_MASK			0xFF00
#घोषणा RETURN_MASK			0xFF0000

/************************************************************************/
/*									*/
/*	Inquiry Data क्रमmat						*/
/*									*/
/************************************************************************/
काष्ठा ScsiInqData
अणु						/* INQ					*/
	u8 DevType;				/* Periph Qualअगरier & Periph Dev Type	*/
	u8 RMB_TypeMod;				/* rem media bit & Dev Type Modअगरier	*/
	u8 Vers;				/* ISO, ECMA, & ANSI versions		*/
	u8 RDF;					/* AEN, TRMIOP, & response data क्रमmat	*/
	u8 AddLen;				/* length of additional data		*/
	u8 Res1;				/* reserved				*/
	u8 Res2;				/* reserved				*/
	u8 Flags;				/* RelADr, Wbus32, Wbus16, Sync, etc.	*/
	u8 VenकरोrID[8];				/* Venकरोr Identअगरication		*/
	u8 ProductID[16];			/* Product Identअगरication		*/
	u8 ProductRev[4];			/* Product Revision			*/
पूर्ण;

						/* Inquiry byte 0 masks			*/
#घोषणा SCSI_DEVTYPE			0x1F	/* Peripheral Device Type		*/
#घोषणा SCSI_PERIPHQUAL			0xE0	/* Peripheral Qualअगरier			*/
						/* Inquiry byte 1 mask			*/
#घोषणा SCSI_REMOVABLE_MEDIA		0x80	/* Removable Media bit (1=removable)	*/
						/* Peripheral Device Type definitions	*/
						/* See include/scsi/scsi.h		*/
#घोषणा TYPE_NODEV		SCSI_DEVTYPE	/* Unknown or no device type		*/
#अगर_अघोषित TYPE_PRINTER				/*					*/
# define TYPE_PRINTER			0x02	/* Prपूर्णांकer device			*/
#पूर्ण_अगर						/*					*/
#अगर_अघोषित TYPE_COMM				/*					*/
# define TYPE_COMM			0x09	/* Communications device		*/
#पूर्ण_अगर

/************************************************************************/
/*									*/
/*	Inquiry flag definitions (Inq data byte 7)			*/
/*									*/
/************************************************************************/
#घोषणा SCSI_INQ_RELADR			0x80	/* device supports relative addressing	*/
#घोषणा SCSI_INQ_WBUS32			0x40	/* device supports 32 bit data xfers	*/
#घोषणा SCSI_INQ_WBUS16			0x20	/* device supports 16 bit data xfers	*/
#घोषणा SCSI_INQ_SYNC			0x10	/* device supports synchronous xfer	*/
#घोषणा SCSI_INQ_LINKED			0x08	/* device supports linked commands	*/
#घोषणा SCSI_INQ_CMDQUEUE		0x02	/* device supports command queueing	*/
#घोषणा SCSI_INQ_SFTRE			0x01	/* device supports soft resets		*/

#घोषणा ENABLE_CE			1
#घोषणा DISABLE_CE			0
#घोषणा EEPROM_READ			0x80

/************************************************************************/
/*									*/
/*	The PCI configuration रेजिस्टर offset क्रम TRM_S1040		*/
/*									*/
/************************************************************************/
#घोषणा TRM_S1040_ID			0x00	/* Venकरोr and Device ID			*/
#घोषणा TRM_S1040_COMMAND		0x04	/* PCI command रेजिस्टर			*/
#घोषणा TRM_S1040_IOBASE		0x10	/* I/O Space base address		*/
#घोषणा TRM_S1040_ROMBASE		0x30	/* Expansion ROM Base Address		*/
#घोषणा TRM_S1040_INTLINE		0x3C	/* Interrupt line			*/

/************************************************************************/
/*									*/
/*	The SCSI रेजिस्टर offset क्रम TRM_S1040				*/
/*									*/
/************************************************************************/
#घोषणा TRM_S1040_SCSI_STATUS		0x80	/* SCSI Status (R)			*/
#घोषणा COMMANDPHASEDONE		0x2000	/* SCSI command phase करोne		*/
#घोषणा SCSIXFERDONE			0x0800	/* SCSI SCSI transfer करोne		*/
#घोषणा SCSIXFERCNT_2_ZERO		0x0100	/* SCSI SCSI transfer count to zero	*/
#घोषणा SCSIINTERRUPT			0x0080	/* SCSI पूर्णांकerrupt pending		*/
#घोषणा COMMANDABORT			0x0040	/* SCSI command पात			*/
#घोषणा SEQUENCERACTIVE			0x0020	/* SCSI sequencer active		*/
#घोषणा PHASEMISMATCH			0x0010	/* SCSI phase mismatch			*/
#घोषणा PARITYERROR			0x0008	/* SCSI parity error			*/

#घोषणा PHASEMASK			0x0007	/* Phase MSG/CD/IO			*/
#घोषणा PH_DATA_OUT			0x00	/* Data out phase			*/
#घोषणा PH_DATA_IN			0x01	/* Data in phase			*/
#घोषणा PH_COMMAND			0x02	/* Command phase			*/
#घोषणा PH_STATUS			0x03	/* Status phase				*/
#घोषणा PH_BUS_FREE			0x05	/* Invalid phase used as bus मुक्त	*/
#घोषणा PH_MSG_OUT			0x06	/* Message out phase			*/
#घोषणा PH_MSG_IN			0x07	/* Message in phase			*/

#घोषणा TRM_S1040_SCSI_CONTROL		0x80	/* SCSI Control (W)			*/
#घोषणा DO_CLRATN			0x0400	/* Clear ATN				*/
#घोषणा DO_SETATN			0x0200	/* Set ATN				*/
#घोषणा DO_CMDABORT			0x0100	/* Abort SCSI command			*/
#घोषणा DO_RSTMODULE			0x0010	/* Reset SCSI chip			*/
#घोषणा DO_RSTSCSI			0x0008	/* Reset SCSI bus			*/
#घोषणा DO_CLRFIFO			0x0004	/* Clear SCSI transfer FIFO		*/
#घोषणा DO_DATALATCH			0x0002	/* Enable SCSI bus data input (latched)	*/
/* #घोषणा DO_DATALATCH			0x0000 */	/* KG: DISable SCSI bus data latch	*/
#घोषणा DO_HWRESELECT			0x0001	/* Enable hardware reselection		*/

#घोषणा TRM_S1040_SCSI_FIFOCNT		0x82	/* SCSI FIFO Counter 5bits(R)		*/
#घोषणा TRM_S1040_SCSI_SIGNAL		0x83	/* SCSI low level संकेत (R/W)		*/

#घोषणा TRM_S1040_SCSI_INTSTATUS	0x84	/* SCSI Interrupt Status (R)		*/
#घोषणा INT_SCAM			0x80	/* SCAM selection पूर्णांकerrupt		*/
#घोषणा INT_SELECT			0x40	/* Selection पूर्णांकerrupt			*/
#घोषणा INT_SELTIMEOUT			0x20	/* Selection समयout पूर्णांकerrupt		*/
#घोषणा INT_DISCONNECT			0x10	/* Bus disconnected पूर्णांकerrupt		*/
#घोषणा INT_RESELECTED			0x08	/* Reselected पूर्णांकerrupt			*/
#घोषणा INT_SCSIRESET			0x04	/* SCSI reset detected पूर्णांकerrupt	*/
#घोषणा INT_BUSSERVICE			0x02	/* Bus service पूर्णांकerrupt		*/
#घोषणा INT_CMDDONE			0x01	/* SCSI command करोne पूर्णांकerrupt		*/

#घोषणा TRM_S1040_SCSI_OFFSET		0x84	/* SCSI Offset Count (W)		*/

/************************************************************************/
/*									*/
/*	Bit		Name		Definition			*/
/*	---------	-------------	----------------------------	*/
/*	07-05	0	RSVD		Reversed. Always 0.		*/
/*	04	0	OFFSET4		Reversed क्रम LVDS. Always 0.	*/
/*	03-00	0	OFFSET[03:00]	Offset number from 0 to 15	*/
/*									*/
/************************************************************************/

#घोषणा TRM_S1040_SCSI_SYNC		0x85	/* SCSI Synchronous Control (R/W)	*/
#घोषणा LVDS_SYNC			0x20	/* Enable LVDS synchronous		*/
#घोषणा WIDE_SYNC			0x10	/* Enable WIDE synchronous		*/
#घोषणा ALT_SYNC			0x08	/* Enable Fast-20 alternate synchronous	*/

/************************************************************************/
/*									*/
/*	SYNCM	7    6    5    4    3       2       1       0		*/
/*	Name	RSVD RSVD LVDS WIDE ALTPERD PERIOD2 PERIOD1 PERIOD0	*/
/*	Default	0    0    0    0    0       0       0       0		*/
/*									*/
/*	Bit		Name		Definition			*/
/*	---------	-------------	---------------------------	*/
/*	07-06	0	RSVD		Reversed. Always पढ़ो 0		*/
/*	05	0	LVDS		Reversed. Always पढ़ो 0		*/
/*	04	0	WIDE/WSCSI	Enable wide (16-bits) SCSI	*/
/*					transfer.			*/
/*	03	0	ALTPERD/ALTPD	Alternate (Sync./Period) mode.	*/
/*									*/
/*			@@ When this bit is set,			*/
/*			   the synchronous period bits 2:0		*/
/*			   in the Synchronous Mode रेजिस्टर		*/
/*			   are used to transfer data			*/
/*			   at the Fast-20 rate.				*/
/*			@@ When this bit is unset,			*/
/*			   the synchronous period bits 2:0		*/
/*			   in the Synchronous Mode Register		*/
/*			   are used to transfer data			*/
/*			   at the Fast-10 rate (or Fast-40 w/ LVDS).	*/
/*									*/
/*	02-00	0	PERIOD[2:0]/	Synchronous SCSI Transfer Rate.	*/
/*			SXPD[02:00]	These 3 bits specअगरy		*/
/*					the Synchronous SCSI Transfer	*/
/*					Rate क्रम Fast-20 and Fast-10.	*/
/*					These bits are also reset	*/
/*					by a SCSI Bus reset.		*/
/*									*/
/*	For Fast-10 bit ALTPD = 0 and LVDS = 0				*/
/*	and bit2,bit1,bit0 is defined as follows :			*/
/*									*/
/*	000	100ns, 10.0 MHz						*/
/*	001	150ns,  6.6 MHz						*/
/*	010	200ns,  5.0 MHz						*/
/*	011	250ns,  4.0 MHz						*/
/*	100	300ns,  3.3 MHz						*/
/*	101	350ns,  2.8 MHz						*/
/*	110	400ns,  2.5 MHz						*/
/*	111	450ns,  2.2 MHz						*/
/*									*/
/*	For Fast-20 bit ALTPD = 1 and LVDS = 0				*/
/*	and bit2,bit1,bit0 is defined as follows :			*/
/*									*/
/*	000	 50ns, 20.0 MHz						*/
/*	001	 75ns, 13.3 MHz						*/
/*	010	100ns, 10.0 MHz						*/
/*	011	125ns,  8.0 MHz						*/
/*	100	150ns,  6.6 MHz						*/
/*	101	175ns,  5.7 MHz						*/
/*	110	200ns,  5.0 MHz						*/
/*	111	250ns,  4.0 MHz   KG: Maybe 225ns, 4.4 MHz		*/
/*									*/
/*	For Fast-40 bit ALTPD = 0 and LVDS = 1				*/
/*	and bit2,bit1,bit0 is defined as follows :			*/
/*									*/
/*	000	 25ns, 40.0 MHz						*/
/*	001	 50ns, 20.0 MHz						*/
/*	010	 75ns, 13.3 MHz						*/
/*	011	100ns, 10.0 MHz						*/
/*	100	125ns,  8.0 MHz						*/
/*	101	150ns,  6.6 MHz						*/
/*	110	175ns,  5.7 MHz						*/
/*	111	200ns,  5.0 MHz						*/
/*									*/
/************************************************************************/

#घोषणा TRM_S1040_SCSI_TARGETID		0x86	/* SCSI Target ID (R/W)			*/
#घोषणा TRM_S1040_SCSI_IDMSG		0x87	/* SCSI Identअगरy Message (R)		*/
#घोषणा TRM_S1040_SCSI_HOSTID		0x87	/* SCSI Host ID (W)			*/
#घोषणा TRM_S1040_SCSI_COUNTER		0x88	/* SCSI Transfer Counter 24bits(R/W)	*/

#घोषणा TRM_S1040_SCSI_INTEN		0x8C	/* SCSI Interrupt Enable (R/W)		*/
#घोषणा EN_SCAM				0x80	/* Enable SCAM selection पूर्णांकerrupt	*/
#घोषणा EN_SELECT			0x40	/* Enable selection पूर्णांकerrupt		*/
#घोषणा EN_SELTIMEOUT			0x20	/* Enable selection समयout पूर्णांकerrupt	*/
#घोषणा EN_DISCONNECT			0x10	/* Enable bus disconnected पूर्णांकerrupt	*/
#घोषणा EN_RESELECTED			0x08	/* Enable reselected पूर्णांकerrupt		*/
#घोषणा EN_SCSIRESET			0x04	/* Enable SCSI reset detected पूर्णांकerrupt	*/
#घोषणा EN_BUSSERVICE			0x02	/* Enable bus service पूर्णांकerrupt		*/
#घोषणा EN_CMDDONE			0x01	/* Enable SCSI command करोne पूर्णांकerrupt	*/

#घोषणा TRM_S1040_SCSI_CONFIG0		0x8D	/* SCSI Configuration 0 (R/W)		*/
#घोषणा PHASELATCH			0x40	/* Enable phase latch			*/
#घोषणा INITIATOR			0x20	/* Enable initiator mode		*/
#घोषणा PARITYCHECK			0x10	/* Enable parity check			*/
#घोषणा BLOCKRST			0x01	/* Disable SCSI reset1			*/

#घोषणा TRM_S1040_SCSI_CONFIG1		0x8E	/* SCSI Configuration 1 (R/W)		*/
#घोषणा ACTIVE_NEGPLUS			0x10	/* Enhance active negation		*/
#घोषणा FILTER_DISABLE			0x08	/* Disable SCSI data filter		*/
#घोषणा FAST_FILTER			0x04	/* ?					*/
#घोषणा ACTIVE_NEG			0x02	/* Enable active negation		*/

#घोषणा TRM_S1040_SCSI_CONFIG2		0x8F	/* SCSI Configuration 2 (R/W)		*/
#घोषणा CFG2_WIDEFIFO			0x02	/*					*/

#घोषणा TRM_S1040_SCSI_COMMAND		0x90	/* SCSI Command (R/W)			*/
#घोषणा SCMD_COMP			0x12	/* Command complete			*/
#घोषणा SCMD_SEL_ATN			0x60	/* Selection with ATN			*/
#घोषणा SCMD_SEL_ATN3			0x64	/* Selection with ATN3			*/
#घोषणा SCMD_SEL_ATNSTOP		0xB8	/* Selection with ATN and Stop		*/
#घोषणा SCMD_FIFO_OUT			0xC0	/* SCSI FIFO transfer out		*/
#घोषणा SCMD_DMA_OUT			0xC1	/* SCSI DMA transfer out		*/
#घोषणा SCMD_FIFO_IN			0xC2	/* SCSI FIFO transfer in		*/
#घोषणा SCMD_DMA_IN			0xC3	/* SCSI DMA transfer in			*/
#घोषणा SCMD_MSGACCEPT			0xD8	/* Message accept			*/

/************************************************************************/
/*									*/
/*	Code	Command Description					*/
/*	----	----------------------------------------		*/
/*	02	Enable reselection with FIFO				*/
/*	40	Select without ATN with FIFO				*/
/*	60	Select with ATN with FIFO				*/
/*	64	Select with ATN3 with FIFO				*/
/*	A0	Select with ATN and stop with FIFO			*/
/*	C0	Transfer inक्रमmation out with FIFO			*/
/*	C1	Transfer inक्रमmation out with DMA			*/
/*	C2	Transfer inक्रमmation in with FIFO			*/
/*	C3	Transfer inक्रमmation in with DMA			*/
/*	12	Initiator command complete with FIFO			*/
/*	50	Initiator transfer inक्रमmation out sequence without ATN	*/
/*		with FIFO						*/
/*	70	Initiator transfer inक्रमmation out sequence with ATN	*/
/*		with FIFO						*/
/*	74	Initiator transfer inक्रमmation out sequence with ATN3	*/
/*		with FIFO						*/
/*	52	Initiator transfer inक्रमmation in sequence without ATN	*/
/*		with FIFO						*/
/*	72	Initiator transfer inक्रमmation in sequence with ATN	*/
/*		with FIFO						*/
/*	76	Initiator transfer inक्रमmation in sequence with ATN3	*/
/*		with FIFO						*/
/*	90	Initiator transfer inक्रमmation out command complete	*/
/*		with FIFO						*/
/*	92	Initiator transfer inक्रमmation in command complete	*/
/*		with FIFO						*/
/*	D2	Enable selection					*/
/*	08	Reselection						*/
/*	48	Disconnect command with FIFO				*/
/*	88	Terminate command with FIFO				*/
/*	C8	Target command complete with FIFO			*/
/*	18	SCAM Arbitration/ Selection				*/
/*	5A	Enable reselection					*/
/*	98	Select without ATN with FIFO				*/
/*	B8	Select with ATN with FIFO				*/
/*	D8	Message Accepted					*/
/*	58	NOP							*/
/*									*/
/************************************************************************/

#घोषणा TRM_S1040_SCSI_TIMEOUT		0x91	/* SCSI Time Out Value (R/W)		*/
#घोषणा TRM_S1040_SCSI_FIFO		0x98	/* SCSI FIFO (R/W)			*/

#घोषणा TRM_S1040_SCSI_TCR0		0x9C	/* SCSI Target Control 0 (R/W)		*/
#घोषणा TCR0_WIDE_NEGO_DONE		0x8000	/* Wide nego करोne			*/
#घोषणा TCR0_SYNC_NEGO_DONE		0x4000	/* Synchronous nego करोne		*/
#घोषणा TCR0_ENABLE_LVDS		0x2000	/* Enable LVDS synchronous		*/
#घोषणा TCR0_ENABLE_WIDE		0x1000	/* Enable WIDE synchronous		*/
#घोषणा TCR0_ENABLE_ALT			0x0800	/* Enable alternate synchronous		*/
#घोषणा TCR0_PERIOD_MASK		0x0700	/* Transfer rate			*/

#घोषणा TCR0_DO_WIDE_NEGO		0x0080	/* Do wide NEGO				*/
#घोषणा TCR0_DO_SYNC_NEGO		0x0040	/* Do sync NEGO				*/
#घोषणा TCR0_DISCONNECT_EN		0x0020	/* Disconnection enable			*/
#घोषणा TCR0_OFFSET_MASK		0x001F	/* Offset number			*/

#घोषणा TRM_S1040_SCSI_TCR1		0x9E	/* SCSI Target Control 1 (R/W)		*/
#घोषणा MAXTAG_MASK			0x7F00	/* Maximum tags (127)			*/
#घोषणा NON_TAG_BUSY			0x0080	/* Non tag command active		*/
#घोषणा ACTTAG_MASK			0x007F	/* Active tags				*/

/************************************************************************/
/*									*/
/*	The DMA रेजिस्टर offset क्रम TRM_S1040				*/
/*									*/
/************************************************************************/
#घोषणा TRM_S1040_DMA_COMMAND		0xA0	/* DMA Command (R/W)			*/
#घोषणा DMACMD_SG			0x02	/* Enable HW S/G support		*/
#घोषणा DMACMD_सूची			0x01	/* 1 = पढ़ो from SCSI ग_लिखो to Host	*/
#घोषणा XFERDATAIN_SG			0x0103	/* Transfer data in  w/  SG		*/
#घोषणा XFERDATAOUT_SG			0x0102	/* Transfer data out w/  SG		*/
#घोषणा XFERDATAIN			0x0101	/* Transfer data in  w/o SG		*/
#घोषणा XFERDATAOUT			0x0100	/* Transfer data out w/o SG		*/

#घोषणा TRM_S1040_DMA_FIFOCNT		0xA1	/* DMA FIFO Counter (R)			*/

#घोषणा TRM_S1040_DMA_CONTROL		0xA1	/* DMA Control (W)			*/
#घोषणा DMARESETMODULE			0x10	/* Reset PCI/DMA module			*/
#घोषणा STOPDMAXFER			0x08	/* Stop  DMA transfer			*/
#घोषणा ABORTXFER			0x04	/* Abort DMA transfer			*/
#घोषणा CLRXFIFO			0x02	/* Clear DMA transfer FIFO		*/
#घोषणा STARTDMAXFER			0x01	/* Start DMA transfer			*/

#घोषणा TRM_S1040_DMA_FIFOSTAT		0xA2	/* DMA FIFO Status (R)			*/

#घोषणा TRM_S1040_DMA_STATUS		0xA3	/* DMA Interrupt Status (R/W)		*/
#घोषणा XFERPENDING			0x80	/* Transfer pending			*/
#घोषणा SCSIBUSY			0x40	/* SCSI busy				*/
#घोषणा GLOBALINT			0x20	/* DMA_INTEN bit 0-4 set		*/
#घोषणा FORCEDMACOMP			0x10	/* Force DMA transfer complete		*/
#घोषणा DMAXFERERROR			0x08	/* DMA transfer error			*/
#घोषणा DMAXFERABORT			0x04	/* DMA transfer पात			*/
#घोषणा DMAXFERCOMP			0x02	/* Bus Master XFER Complete status	*/
#घोषणा SCSICOMP			0x01	/* SCSI complete पूर्णांकerrupt		*/

#घोषणा TRM_S1040_DMA_INTEN		0xA4	/* DMA Interrupt Enable (R/W)		*/
#घोषणा EN_FORCEDMACOMP			0x10	/* Force DMA transfer complete		*/
#घोषणा EN_DMAXFERERROR			0x08	/* DMA transfer error			*/
#घोषणा EN_DMAXFERABORT			0x04	/* DMA transfer पात			*/
#घोषणा EN_DMAXFERCOMP			0x02	/* Bus Master XFER Complete status	*/
#घोषणा EN_SCSIINTR			0x01	/* Enable SCSI complete पूर्णांकerrupt	*/

#घोषणा TRM_S1040_DMA_CONFIG		0xA6	/* DMA Configuration (R/W)		*/
#घोषणा DMA_ENHANCE			0x8000	/* Enable DMA enhance feature (SG?)	*/
#घोषणा DMA_PCI_DUAL_ADDR		0x4000	/*					*/
#घोषणा DMA_CFG_RES			0x2000	/* Always 1				*/
#घोषणा DMA_AUTO_CLR_FIFO		0x1000	/* DISable DMA स्वतः clear FIFO		*/
#घोषणा DMA_MEM_MULTI_READ		0x0800	/*					*/
#घोषणा DMA_MEM_WRITE_INVAL		0x0400	/* Memory ग_लिखो and invalidate		*/
#घोषणा DMA_FIFO_CTRL			0x0300	/* Control FIFO operation with DMA	*/
#घोषणा DMA_FIFO_HALF_HALF		0x0200	/* Keep half filled on both पढ़ो/ग_लिखो	*/

#घोषणा TRM_S1040_DMA_XCNT		0xA8	/* DMA Transfer Counter (R/W), 24bits	*/
#घोषणा TRM_S1040_DMA_CXCNT		0xAC	/* DMA Current Transfer Counter (R)	*/
#घोषणा TRM_S1040_DMA_XLOWADDR		0xB0	/* DMA Transfer Physical Low Address	*/
#घोषणा TRM_S1040_DMA_XHIGHADDR		0xB4	/* DMA Transfer Physical High Address	*/

/************************************************************************/
/*									*/
/*	The general रेजिस्टर offset क्रम TRM_S1040			*/
/*									*/
/************************************************************************/
#घोषणा TRM_S1040_GEN_CONTROL		0xD4	/* Global Control			*/
#घोषणा CTRL_LED			0x80	/* Control onboard LED			*/
#घोषणा EN_EEPROM			0x10	/* Enable EEPROM programming		*/
#घोषणा DIS_TERM			0x08	/* Disable onboard termination		*/
#घोषणा AUTOTERM			0x04	/* Enable Auto SCSI terminator		*/
#घोषणा LOW8TERM			0x02	/* Enable Lower 8 bit SCSI terminator	*/
#घोषणा UP8TERM				0x01	/* Enable Upper 8 bit SCSI terminator	*/

#घोषणा TRM_S1040_GEN_STATUS		0xD5	/* Global Status			*/
#घोषणा GTIMEOUT			0x80	/* Global समयr reach 0			*/
#घोषणा EXT68HIGH			0x40	/* Higher 8 bit connected बाह्यally	*/
#घोषणा INT68HIGH			0x20	/* Higher 8 bit connected पूर्णांकernally	*/
#घोषणा CON5068				0x10	/* External 50/68 pin connected (low)	*/
#घोषणा CON68				0x08	/* Internal 68 pin connected (low)	*/
#घोषणा CON50				0x04	/* Internal 50 pin connected (low!)	*/
#घोषणा WIDESCSI			0x02	/* Wide SCSI card			*/
#घोषणा STATUS_LOAD_DEFAULT		0x01	/*					*/

#घोषणा TRM_S1040_GEN_NVRAM		0xD6	/* Serial NON-VOLATILE RAM port		*/
#घोषणा NVR_BITOUT			0x08	/* Serial data out			*/
#घोषणा NVR_BITIN			0x04	/* Serial data in			*/
#घोषणा NVR_CLOCK			0x02	/* Serial घड़ी				*/
#घोषणा NVR_SELECT			0x01	/* Serial select			*/

#घोषणा TRM_S1040_GEN_EDATA		0xD7	/* Parallel EEPROM data port		*/
#घोषणा TRM_S1040_GEN_EADDRESS		0xD8	/* Parallel EEPROM address		*/
#घोषणा TRM_S1040_GEN_TIMER		0xDB	/* Global समयr				*/

/************************************************************************/
/*									*/
/*	NvmTarCfg0: Target configuration byte 0 :..pDCB->DevMode	*/
/*									*/
/************************************************************************/
#घोषणा NTC_DO_WIDE_NEGO		0x20	/* Wide negotiate			*/
#घोषणा NTC_DO_TAG_QUEUEING		0x10	/* Enable SCSI tag queuing		*/
#घोषणा NTC_DO_SEND_START		0x08	/* Send start command SPINUP		*/
#घोषणा NTC_DO_DISCONNECT		0x04	/* Enable SCSI disconnect		*/
#घोषणा NTC_DO_SYNC_NEGO		0x02	/* Sync negotiation			*/
#घोषणा NTC_DO_PARITY_CHK		0x01	/* (it should define at NAC)		*/
						/* Parity check enable			*/

/************************************************************************/
/*									*/
/*	Nvram Initiater bits definition					*/
/*									*/
/************************************************************************/
#अगर 0
#घोषणा MORE2_DRV			BIT0
#घोषणा GREATER_1G			BIT1
#घोषणा RST_SCSI_BUS			BIT2
#घोषणा ACTIVE_NEGATION			BIT3
#घोषणा NO_SEEK				BIT4
#घोषणा LUN_CHECK			BIT5
#पूर्ण_अगर

/************************************************************************/
/*									*/
/*	Nvram Adapter Cfg bits definition				*/
/*									*/
/************************************************************************/
#घोषणा NAC_SCANLUN			0x20	/* Include LUN as BIOS device		*/
#घोषणा NAC_POWERON_SCSI_RESET		0x04	/* Power on reset enable		*/
#घोषणा NAC_GREATER_1G			0x02	/* > 1G support enable			*/
#घोषणा NAC_GT2DRIVES			0x01	/* Support more than 2 drives		*/
/* #घोषणा NAC_DO_PARITY_CHK		0x08 */	/* Parity check enable			*/

#पूर्ण_अगर
