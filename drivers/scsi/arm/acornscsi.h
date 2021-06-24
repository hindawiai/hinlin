<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/drivers/acorn/scsi/acornscsi.h
 *
 *  Copyright (C) 1997 Russell King
 *
 *  Acorn SCSI driver
 */
#अगर_अघोषित ACORNSCSI_H
#घोषणा ACORNSCSI_H

/* SBIC रेजिस्टरs */
#घोषणा SBIC_OWNID		0
#घोषणा OWNID_FS1		(1<<7)
#घोषणा OWNID_FS2		(1<<6)
#घोषणा OWNID_EHP		(1<<4)
#घोषणा OWNID_EAF		(1<<3)

#घोषणा SBIC_CTRL		1
#घोषणा CTRL_DMAMODE		(1<<7)
#घोषणा CTRL_DMADBAMODE		(1<<6)
#घोषणा CTRL_DMABURST		(1<<5)
#घोषणा CTRL_DMAPOLLED		0
#घोषणा CTRL_HHP		(1<<4)
#घोषणा CTRL_EDI		(1<<3)
#घोषणा CTRL_IDI		(1<<2)
#घोषणा CTRL_HA			(1<<1)
#घोषणा CTRL_HSP		(1<<0)

#घोषणा SBIC_TIMEOUT		2
#घोषणा SBIC_TOTSECTS		3
#घोषणा SBIC_TOTHEADS		4
#घोषणा SBIC_TOTCYLH		5
#घोषणा SBIC_TOTCYLL		6
#घोषणा SBIC_LOGADDRH		7
#घोषणा SBIC_LOGADDRM2		8
#घोषणा SBIC_LOGADDRM1		9
#घोषणा SBIC_LOGADDRL		10
#घोषणा SBIC_SECTORNUM		11
#घोषणा SBIC_HEADNUM		12
#घोषणा SBIC_CYLH		13
#घोषणा SBIC_CYLL		14
#घोषणा SBIC_TARGETLUN		15
#घोषणा TARGETLUN_TLV		(1<<7)
#घोषणा TARGETLUN_DOK		(1<<6)

#घोषणा SBIC_CMNDPHASE		16
#घोषणा SBIC_SYNCHTRANSFER	17
#घोषणा SYNCHTRANSFER_OF0	0x00
#घोषणा SYNCHTRANSFER_OF1	0x01
#घोषणा SYNCHTRANSFER_OF2	0x02
#घोषणा SYNCHTRANSFER_OF3	0x03
#घोषणा SYNCHTRANSFER_OF4	0x04
#घोषणा SYNCHTRANSFER_OF5	0x05
#घोषणा SYNCHTRANSFER_OF6	0x06
#घोषणा SYNCHTRANSFER_OF7	0x07
#घोषणा SYNCHTRANSFER_OF8	0x08
#घोषणा SYNCHTRANSFER_OF9	0x09
#घोषणा SYNCHTRANSFER_OF10	0x0A
#घोषणा SYNCHTRANSFER_OF11	0x0B
#घोषणा SYNCHTRANSFER_OF12	0x0C
#घोषणा SYNCHTRANSFER_8DBA	0x00
#घोषणा SYNCHTRANSFER_2DBA	0x20
#घोषणा SYNCHTRANSFER_3DBA	0x30
#घोषणा SYNCHTRANSFER_4DBA	0x40
#घोषणा SYNCHTRANSFER_5DBA	0x50
#घोषणा SYNCHTRANSFER_6DBA	0x60
#घोषणा SYNCHTRANSFER_7DBA	0x70

#घोषणा SBIC_TRANSCNTH		18
#घोषणा SBIC_TRANSCNTM		19
#घोषणा SBIC_TRANSCNTL		20
#घोषणा SBIC_DESTID		21
#घोषणा DESTID_SCC		(1<<7)
#घोषणा DESTID_DPD		(1<<6)

#घोषणा SBIC_SOURCEID		22
#घोषणा SOURCEID_ER		(1<<7)
#घोषणा SOURCEID_ES		(1<<6)
#घोषणा SOURCEID_DSP		(1<<5)
#घोषणा SOURCEID_SIV		(1<<4)

#घोषणा SBIC_SSR		23
#घोषणा SBIC_CMND		24
#घोषणा CMND_RESET		0x00
#घोषणा CMND_ABORT		0x01
#घोषणा CMND_ASSERTATN		0x02
#घोषणा CMND_NEGATEACK		0x03
#घोषणा CMND_DISCONNECT		0x04
#घोषणा CMND_RESELECT		0x05
#घोषणा CMND_SELWITHATN		0x06
#घोषणा CMND_SELECT		0x07
#घोषणा CMND_SELECTATNTRANSFER	0x08
#घोषणा CMND_SELECTTRANSFER	0x09
#घोषणा CMND_RESELECTRXDATA	0x0A
#घोषणा CMND_RESELECTTXDATA	0x0B
#घोषणा CMND_WAITFORSELRECV	0x0C
#घोषणा CMND_SENDSTATCMD	0x0D
#घोषणा CMND_SENDDISCONNECT	0x0E
#घोषणा CMND_SETIDI		0x0F
#घोषणा CMND_RECEIVECMD		0x10
#घोषणा CMND_RECEIVEDTA		0x11
#घोषणा CMND_RECEIVEMSG		0x12
#घोषणा CMND_RECEIVEUSP		0x13
#घोषणा CMND_SENDCMD		0x14
#घोषणा CMND_SENDDATA		0x15
#घोषणा CMND_SENDMSG		0x16
#घोषणा CMND_SENDUSP		0x17
#घोषणा CMND_TRANSLATEADDR	0x18
#घोषणा CMND_XFERINFO		0x20
#घोषणा CMND_SBT		(1<<7)

#घोषणा SBIC_DATA		25
#घोषणा SBIC_ASR		26
#घोषणा ASR_INT			(1<<7)
#घोषणा ASR_LCI			(1<<6)
#घोषणा ASR_BSY			(1<<5)
#घोषणा ASR_CIP			(1<<4)
#घोषणा ASR_PE			(1<<1)
#घोषणा ASR_DBR			(1<<0)

/* DMAC रेजिस्टरs */
#घोषणा DMAC_INIT		0x00
#घोषणा INIT_8BIT		(1)

#घोषणा DMAC_CHANNEL		0x80
#घोषणा CHANNEL_0		0x00
#घोषणा CHANNEL_1		0x01
#घोषणा CHANNEL_2		0x02
#घोषणा CHANNEL_3		0x03

#घोषणा DMAC_TXCNTLO		0x01
#घोषणा DMAC_TXCNTHI		0x81
#घोषणा DMAC_TXADRLO		0x02
#घोषणा DMAC_TXADRMD		0x82
#घोषणा DMAC_TXADRHI		0x03

#घोषणा DMAC_DEVCON0		0x04
#घोषणा DEVCON0_AKL		(1<<7)
#घोषणा DEVCON0_RQL		(1<<6)
#घोषणा DEVCON0_EXW		(1<<5)
#घोषणा DEVCON0_ROT		(1<<4)
#घोषणा DEVCON0_CMP		(1<<3)
#घोषणा DEVCON0_DDMA		(1<<2)
#घोषणा DEVCON0_AHLD		(1<<1)
#घोषणा DEVCON0_MTM		(1<<0)

#घोषणा DMAC_DEVCON1		0x84
#घोषणा DEVCON1_WEV		(1<<1)
#घोषणा DEVCON1_BHLD		(1<<0)

#घोषणा DMAC_MODECON		0x05
#घोषणा MODECON_WOED		0x01
#घोषणा MODECON_VERIFY		0x00
#घोषणा MODECON_READ		0x04
#घोषणा MODECON_WRITE		0x08
#घोषणा MODECON_AUTOINIT	0x10
#घोषणा MODECON_ADDRसूची		0x20
#घोषणा MODECON_DEMAND		0x00
#घोषणा MODECON_SINGLE		0x40
#घोषणा MODECON_BLOCK		0x80
#घोषणा MODECON_CASCADE		0xC0

#घोषणा DMAC_STATUS		0x85
#घोषणा STATUS_TC0		(1<<0)
#घोषणा STATUS_RQ0		(1<<4)

#घोषणा DMAC_TEMPLO		0x06
#घोषणा DMAC_TEMPHI		0x86
#घोषणा DMAC_REQREG		0x07
#घोषणा DMAC_MASKREG		0x87
#घोषणा MASKREG_M0		0x01
#घोषणा MASKREG_M1		0x02
#घोषणा MASKREG_M2		0x04
#घोषणा MASKREG_M3		0x08

/* miscellaneous पूर्णांकernal variables */

#घोषणा MASK_ON		(MASKREG_M3|MASKREG_M2|MASKREG_M1|MASKREG_M0)
#घोषणा MASK_OFF	(MASKREG_M3|MASKREG_M2|MASKREG_M1)

/*
 * SCSI driver phases
 */
प्रकार क्रमागत अणु
    PHASE_IDLE,					/* we're not planning on करोing anything	 */
    PHASE_CONNECTING,				/* connecting to a target		 */
    PHASE_CONNECTED,				/* connected to a target		 */
    PHASE_MSGOUT,				/* message out to device		 */
    PHASE_RECONNECTED,				/* reconnected				 */
    PHASE_COMMANDPAUSED,			/* command partly sent			 */
    PHASE_COMMAND,				/* command all sent			 */
    PHASE_DATAOUT,				/* data out to device			 */
    PHASE_DATAIN,				/* data in from device			 */
    PHASE_STATUSIN,				/* status in from device		 */
    PHASE_MSGIN,				/* message in from device		 */
    PHASE_DONE,					/* finished				 */
    PHASE_ABORTED,				/* पातed				 */
    PHASE_DISCONNECT,				/* disconnecting			 */
पूर्ण phase_t;

/*
 * After पूर्णांकerrupt, what to करो now
 */
प्रकार क्रमागत अणु
    INTR_IDLE,					/* not expecting another IRQ		 */
    INTR_NEXT_COMMAND,				/* start next command			 */
    INTR_PROCESSING,				/* पूर्णांकerrupt routine still processing	 */
पूर्ण पूर्णांकr_ret_t;

/*
 * DMA direction
 */
प्रकार क्रमागत अणु
    DMA_OUT,					/* DMA from memory to chip		*/
    DMA_IN					/* DMA from chip to memory		*/
पूर्ण dmadir_t;

/*
 * Synchronous transfer state
 */
प्रकार क्रमागत अणु					/* Synchronous transfer state		*/
    SYNC_ASYNCHRONOUS,				/* करोn't negotiate synchronous transfers*/
    SYNC_NEGOCIATE,				/* start negotiation			*/
    SYNC_SENT_REQUEST,				/* sent SDTR message			*/
    SYNC_COMPLETED,				/* received SDTR reply			*/
पूर्ण syncxfer_t;

/*
 * Command type
 */
प्रकार क्रमागत अणु					/* command type				*/
    CMD_READ,					/* READ_6, READ_10, READ_12		*/
    CMD_WRITE,					/* WRITE_6, WRITE_10, WRITE_12		*/
    CMD_MISC,					/* Others				*/
पूर्ण cmdtype_t;

/*
 * Data phase direction
 */
प्रकार क्रमागत अणु					/* Data direction			*/
    DATAसूची_IN,					/* Data in phase expected		*/
    DATAसूची_OUT					/* Data out phase expected		*/
पूर्ण datadir_t;

#समावेश "queue.h"
#समावेश "msgqueue.h"

#घोषणा STATUS_BUFFER_SIZE	32
/*
 * This is used to dump the previous states of the SBIC
 */
काष्ठा status_entry अणु
	अचिन्हित दीर्घ	when;
	अचिन्हित अक्षर	ssr;
	अचिन्हित अक्षर	ph;
	अचिन्हित अक्षर	irq;
	अचिन्हित अक्षर	unused;
पूर्ण;

#घोषणा ADD_STATUS(_q,_ssr,_ph,_irq) \
(अणु									\
	host->status[(_q)][host->status_ptr[(_q)]].when = jअगरfies;	\
	host->status[(_q)][host->status_ptr[(_q)]].ssr  = (_ssr);	\
	host->status[(_q)][host->status_ptr[(_q)]].ph   = (_ph);	\
	host->status[(_q)][host->status_ptr[(_q)]].irq  = (_irq);	\
	host->status_ptr[(_q)] = (host->status_ptr[(_q)] + 1) & (STATUS_BUFFER_SIZE - 1); \
पूर्ण)

/*
 * AcornSCSI host specअगरic data
 */
प्रकार काष्ठा acornscsi_hostdata अणु
    /* miscellaneous */
    काष्ठा Scsi_Host	*host;			/* host					*/
    काष्ठा scsi_cmnd	*SCpnt;			/* currently processing command		*/
    काष्ठा scsi_cmnd	*origSCpnt;		/* original connecting command		*/
    व्योम __iomem	*base;			/* memc base address 			*/
    व्योम __iomem	*fast;			/* fast ioc base address		*/

    /* driver inक्रमmation */
    काष्ठा अणु
	अचिन्हित पूर्णांक	irq;			/* पूर्णांकerrupt				*/
	phase_t		phase;			/* current phase			*/

	काष्ठा अणु
	    अचिन्हित अक्षर	target;		/* reconnected target			*/
	    अचिन्हित अक्षर	lun;		/* reconnected lun			*/
	    अचिन्हित अक्षर	tag;		/* reconnected tag			*/
	पूर्ण reconnected;

	काष्ठा scsi_poपूर्णांकer	SCp;			/* current commands data poपूर्णांकer	*/

	MsgQueue_t	msgs;

	अचिन्हित लघु	last_message;		/* last message to be sent		*/
	अचिन्हित अक्षर	disconnectable:1;	/* this command can be disconnected	*/
    पूर्ण scsi;

    /* statistics inक्रमmation */
    काष्ठा अणु
	अचिन्हित पूर्णांक	queues;
	अचिन्हित पूर्णांक	हटाओs;
	अचिन्हित पूर्णांक	fins;
	अचिन्हित पूर्णांक	पढ़ोs;
	अचिन्हित पूर्णांक	ग_लिखोs;
	अचिन्हित पूर्णांक	miscs;
	अचिन्हित पूर्णांक	disconnects;
	अचिन्हित पूर्णांक	पातs;
	अचिन्हित पूर्णांक	resets;
    पूर्ण stats;

    /* queue handling */
    काष्ठा अणु
	Queue_t		issue;			/* issue queue				*/
	Queue_t		disconnected;		/* disconnected command queue		*/
    पूर्ण queues;

    /* per-device info */
    काष्ठा अणु
	अचिन्हित अक्षर	sync_xfer;		/* synchronous transfer (SBIC value)	*/
	syncxfer_t	sync_state;		/* sync xfer negotiation state		*/
	अचिन्हित अक्षर	disconnect_ok:1;	/* device can disconnect		*/
    पूर्ण device[8];
    अचिन्हित दीर्घ	busyluns[64 / माप(अचिन्हित दीर्घ)];/* array of bits indicating LUNs busy	*/

    /* DMA info */
    काष्ठा अणु
	अचिन्हित पूर्णांक	मुक्त_addr;		/* next मुक्त address			*/
	अचिन्हित पूर्णांक	start_addr;		/* start address of current transfer	*/
	dmadir_t	direction;		/* dma direction			*/
	अचिन्हित पूर्णांक	transferred;		/* number of bytes transferred		*/
	अचिन्हित पूर्णांक	xfer_start;		/* scheduled DMA transfer start		*/
	अचिन्हित पूर्णांक	xfer_length;		/* scheduled DMA transfer length	*/
	अक्षर		*xfer_ptr;		/* poपूर्णांकer to area			*/
	अचिन्हित अक्षर	xfer_required:1;	/* set अगर we need to transfer something	*/
	अचिन्हित अक्षर	xfer_setup:1;		/* set अगर DMA is setup			*/
	अचिन्हित अक्षर	xfer_करोne:1;		/* set अगर DMA reached end of BH list	*/
    पूर्ण dma;

    /* card info */
    काष्ठा अणु
	अचिन्हित अक्षर	page_reg;		/* current setting of page reg		*/
    पूर्ण card;

    अचिन्हित अक्षर status_ptr[9];
    काष्ठा status_entry status[9][STATUS_BUFFER_SIZE];
पूर्ण AS_Host;

#पूर्ण_अगर /* ACORNSCSI_H */
