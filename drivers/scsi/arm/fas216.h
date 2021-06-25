<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/drivers/acorn/scsi/fas216.h
 *
 *  Copyright (C) 1997-2000 Russell King
 *
 *  FAS216 generic driver
 */
#अगर_अघोषित FAS216_H
#घोषणा FAS216_H

#समावेश <scsi/scsi_eh.h>

#समावेश "queue.h"
#समावेश "msgqueue.h"

/* FAS रेजिस्टर definitions */

/* transfer count low */
#घोषणा REG_CTCL		(0)
#घोषणा REG_STCL		(0)

/* transfer count medium */
#घोषणा REG_CTCM		(1)
#घोषणा REG_STCM		(1)

/* fअगरo data */
#घोषणा REG_FF			(2)

/* command */
#घोषणा REG_CMD			(3)
#घोषणा CMD_NOP			0x00
#घोषणा CMD_FLUSHFIFO		0x01
#घोषणा CMD_RESETCHIP		0x02
#घोषणा CMD_RESETSCSI		0x03

#घोषणा CMD_TRANSFERINFO	0x10
#घोषणा CMD_INITCMDCOMPLETE	0x11
#घोषणा CMD_MSGACCEPTED		0x12
#घोषणा CMD_PADBYTES		0x18
#घोषणा CMD_SETATN		0x1a
#घोषणा CMD_RSETATN		0x1b

#घोषणा CMD_SELECTWOATN		0x41
#घोषणा CMD_SELECTATN		0x42
#घोषणा CMD_SELECTATNSTOP	0x43
#घोषणा CMD_ENABLESEL		0x44
#घोषणा CMD_DISABLESEL		0x45
#घोषणा CMD_SELECTATN3		0x46
#घोषणा CMD_RESEL3		0x47

#घोषणा CMD_WITHDMA		0x80

/* status रेजिस्टर (पढ़ो) */
#घोषणा REG_STAT		(4)
#घोषणा STAT_IO			(1 << 0)			/* IO phase		*/
#घोषणा STAT_CD			(1 << 1)			/* CD phase		*/
#घोषणा STAT_MSG		(1 << 2)			/* MSG phase		*/
#घोषणा STAT_TRANSFERDONE	(1 << 3)			/* Transfer completed	*/
#घोषणा STAT_TRANSFERCNTZ	(1 << 4)			/* Transfer counter is zero */
#घोषणा STAT_PARITYERROR	(1 << 5)			/* Parity error		*/
#घोषणा STAT_REALBAD		(1 << 6)			/* Something bad	*/
#घोषणा STAT_INT		(1 << 7)			/* Interrupt		*/

#घोषणा STAT_BUSMASK		(STAT_MSG|STAT_CD|STAT_IO)
#घोषणा STAT_DATAOUT		(0)				/* Data out		*/
#घोषणा STAT_DATAIN		(STAT_IO)			/* Data in		*/
#घोषणा STAT_COMMAND		(STAT_CD)			/* Command out		*/
#घोषणा STAT_STATUS		(STAT_CD|STAT_IO)		/* Status In		*/
#घोषणा STAT_MESGOUT		(STAT_MSG|STAT_CD)		/* Message out		*/
#घोषणा STAT_MESGIN		(STAT_MSG|STAT_CD|STAT_IO)	/* Message In		*/

/* bus ID क्रम select / reselect */
#घोषणा REG_SDID		(4)
#घोषणा BUSID(target)		((target) & 7)

/* Interrupt status रेजिस्टर (पढ़ो) */
#घोषणा REG_INST		(5)
#घोषणा INST_SELWOATN		(1 << 0)			/* Select w/o ATN	*/
#घोषणा INST_SELATN		(1 << 1)			/* Select w/ATN		*/
#घोषणा INST_RESELECTED		(1 << 2)			/* Reselected		*/
#घोषणा INST_FUNCDONE		(1 << 3)			/* Function करोne	*/
#घोषणा INST_BUSSERVICE		(1 << 4)			/* Bus service		*/
#घोषणा INST_DISCONNECT		(1 << 5)			/* Disconnect		*/
#घोषणा INST_ILLEGALCMD		(1 << 6)			/* Illegal command	*/
#घोषणा INST_BUSRESET		(1 << 7)			/* SCSI Bus reset	*/

/* Timeout रेजिस्टर (ग_लिखो) */
#घोषणा REG_STIM		(5)

/* Sequence step रेजिस्टर (पढ़ो) */
#घोषणा REG_IS			(6)
#घोषणा IS_BITS			0x07
#घोषणा IS_SELARB		0x00				/* Select & Arb ok	*/
#घोषणा IS_MSGBYTESENT		0x01				/* One byte message sent*/
#घोषणा IS_NOTCOMMAND		0x02				/* Not in command state	*/
#घोषणा IS_EARLYPHASE		0x03				/* Early phase change	*/
#घोषणा IS_COMPLETE		0x04				/* Command ok		*/
#घोषणा IS_SOF			0x08				/* Sync off flag	*/

/* Transfer period step (ग_लिखो) */
#घोषणा REG_STP			(6)

/* Synchronous Offset (ग_लिखो) */
#घोषणा REG_SOF			(7)

/* Fअगरo state रेजिस्टर (पढ़ो) */
#घोषणा REG_CFIS		(7)
#घोषणा CFIS_CF			0x1f				/* Num bytes in FIFO	*/
#घोषणा CFIS_IS			0xe0				/* Step			*/

/* config रेजिस्टर 1 */
#घोषणा REG_CNTL1		(8)
#घोषणा CNTL1_CID		(7 << 0)			/* Chip ID			*/
#घोषणा CNTL1_STE		(1 << 3)			/* Self test enable		*/
#घोषणा CNTL1_PERE		(1 << 4)			/* Parity enable reporting en.	*/
#घोषणा CNTL1_PTE		(1 << 5)			/* Parity test enable		*/
#घोषणा CNTL1_DISR		(1 << 6)			/* Disable Irq on SCSI reset	*/
#घोषणा CNTL1_ETM		(1 << 7)			/* Extended Timing Mode		*/

/* Clock conversion factor (पढ़ो) */
#घोषणा REG_CLKF		(9)
#घोषणा CLKF_F37MHZ		0x00				/* 35.01 - 40 MHz		*/
#घोषणा CLKF_F10MHZ		0x02				/* 10 MHz			*/
#घोषणा CLKF_F12MHZ		0x03				/* 10.01 - 15 MHz		*/
#घोषणा CLKF_F17MHZ		0x04				/* 15.01 - 20 MHz		*/
#घोषणा CLKF_F22MHZ		0x05				/* 20.01 - 25 MHz		*/
#घोषणा CLKF_F27MHZ		0x06				/* 25.01 - 30 MHz		*/
#घोषणा CLKF_F32MHZ		0x07				/* 30.01 - 35 MHz		*/

/* Chip test रेजिस्टर (ग_लिखो) */
#घोषणा REG_FTM			(10)
#घोषणा TEST_FTM		0x01				/* Force target mode		*/
#घोषणा TEST_FIM		0x02				/* Force initiator mode		*/
#घोषणा TEST_FHI		0x04				/* Force high impedance mode	*/

/* Configuration रेजिस्टर 2 (पढ़ो/ग_लिखो) */
#घोषणा REG_CNTL2		(11)
#घोषणा CNTL2_PGDP		(1 << 0)			/* Pass Th/Generate Data Parity	*/
#घोषणा CNTL2_PGRP		(1 << 1)			/* Pass Th/Generate Reg Parity	*/
#घोषणा CNTL2_ACDPE		(1 << 2)			/* Abort on Cmd/Data Parity Err	*/
#घोषणा CNTL2_S2FE		(1 << 3)			/* SCSI2 Features Enable	*/
#घोषणा CNTL2_TSDR		(1 << 4)			/* Tristate DREQ		*/
#घोषणा CNTL2_SBO		(1 << 5)			/* Select Byte Order		*/
#घोषणा CNTL2_ENF		(1 << 6)			/* Enable features		*/
#घोषणा CNTL2_DAE		(1 << 7)			/* Data Alignment Enable	*/

/* Configuration रेजिस्टर 3 (पढ़ो/ग_लिखो) */
#घोषणा REG_CNTL3		(12)
#घोषणा CNTL3_BS8		(1 << 0)			/* Burst size 8			*/
#घोषणा CNTL3_MDM		(1 << 1)			/* Modअगरy DMA mode		*/
#घोषणा CNTL3_LBTM		(1 << 2)			/* Last Byte Transfer mode	*/
#घोषणा CNTL3_FASTCLK		(1 << 3)			/* Fast SCSI घड़ीing		*/
#घोषणा CNTL3_FASTSCSI		(1 << 4)			/* Fast SCSI			*/
#घोषणा CNTL3_G2CB		(1 << 5)			/* Group2 SCSI support		*/
#घोषणा CNTL3_QTAG		(1 << 6)			/* Enable 3 byte msgs		*/
#घोषणा CNTL3_ADIDCHK		(1 << 7)			/* Additional ID check		*/

/* High transfer count (पढ़ो/ग_लिखो) */
#घोषणा REG_CTCH		(14)
#घोषणा REG_STCH		(14)

/* ID रेजिस्टर (पढ़ो only) */
#घोषणा REG_ID			(14)

/* Data alignment */
#घोषणा REG_DAL			(15)

प्रकार क्रमागत अणु
	PHASE_IDLE,					/* we're not planning on करोing anything	*/
	PHASE_SELECTION,				/* selecting a device			*/
	PHASE_SELSTEPS,					/* selection with command steps		*/
	PHASE_COMMAND,					/* command sent				*/
	PHASE_MESSAGESENT,				/* selected, and we're sending cmd	*/
	PHASE_DATAOUT,					/* data out to device			*/
	PHASE_DATAIN,					/* data in from device			*/
	PHASE_MSGIN,					/* message in from device		*/
	PHASE_MSGIN_DISCONNECT,				/* disconnecting from bus		*/
	PHASE_MSGOUT,					/* after message out phase		*/
	PHASE_MSGOUT_EXPECT,				/* expecting message out		*/
	PHASE_STATUS,					/* status from device			*/
	PHASE_DONE					/* Command complete			*/
पूर्ण phase_t;

प्रकार क्रमागत अणु
	DMA_OUT,					/* DMA from memory to chip		*/
	DMA_IN						/* DMA from chip to memory		*/
पूर्ण fasdmadir_t;

प्रकार क्रमागत अणु
	fasdma_none,					/* No dma				*/
	fasdma_pio,					/* PIO mode				*/
	fasdma_pseuकरो,					/* Pseuकरो DMA				*/
	fasdma_real_block,				/* Real DMA, on block by block basis	*/
	fasdma_real_all					/* Real DMA, on request by request	*/
पूर्ण fasdmatype_t;

प्रकार क्रमागत अणु
	neg_रुको,					/* Negotiate with device		*/
	neg_inprogress,					/* Negotiation sent			*/
	neg_complete,					/* Negotiation complete			*/
	neg_targcomplete,				/* Target completed negotiation		*/
	neg_invalid					/* Negotiation not supported		*/
पूर्ण neg_t;

#घोषणा MAGIC	0x441296bdUL
#घोषणा NR_MSGS	8

#घोषणा FASCAP_DMA		(1 << 0)
#घोषणा FASCAP_PSEUDODMA	(1 << 1)

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ		magic_start;
	spinlock_t		host_lock;
	काष्ठा Scsi_Host	*host;			/* host					*/
	काष्ठा scsi_cmnd	*SCpnt;			/* currently processing command		*/
	काष्ठा scsi_cmnd	*origSCpnt;		/* original connecting command		*/
	काष्ठा scsi_cmnd	*reqSCpnt;		/* request sense command		*/
	काष्ठा scsi_cmnd	*rstSCpnt;		/* reset command			*/
	काष्ठा scsi_cmnd	*pending_SCpnt[8];	/* per-device pending commands		*/
	पूर्णांक			next_pending;		/* next pending device			*/

	/*
	 * Error recovery
	 */
	रुको_queue_head_t	eh_रुको;
	काष्ठा समयr_list	eh_समयr;
	अचिन्हित पूर्णांक		rst_dev_status;
	अचिन्हित पूर्णांक		rst_bus_status;

	/* driver inक्रमmation */
	काष्ठा अणु
		phase_t		phase;			/* current phase			*/
		व्योम __iomem	*io_base;		/* iomem base of FAS216			*/
		अचिन्हित पूर्णांक	io_shअगरt;		/* shअगरt to adjust reg offsets by	*/
		अचिन्हित अक्षर	cfg[4];			/* configuration रेजिस्टरs		*/
		स्थिर अक्षर	*type;			/* chip type				*/
		अचिन्हित पूर्णांक	irq;			/* पूर्णांकerrupt				*/
		पूर्णांक		dma;			/* dma channel				*/

		काष्ठा scsi_poपूर्णांकer	SCp;			/* current commands data poपूर्णांकer	*/

		MsgQueue_t	msgs;			/* message queue क्रम connected device	*/

		अचिन्हित पूर्णांक	async_stp;		/* Async transfer STP value		*/
		अचिन्हित अक्षर	msgin_fअगरo;		/* bytes in fअगरo at समय of message in	*/
		अचिन्हित अक्षर	message[256];		/* last message received from device	*/

		अचिन्हित अक्षर	disconnectable:1;	/* this command can be disconnected	*/
		अचिन्हित अक्षर	पातing:1;		/* पातing command			*/
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
		अचिन्हित पूर्णांक	bus_resets;
		अचिन्हित पूर्णांक	host_resets;
	पूर्ण stats;

	/* configuration inक्रमmation */
	काष्ठा अणु
		अचिन्हित अक्षर	घड़ीrate;		/* घड़ी rate of FAS device (MHz)	*/
		अचिन्हित अक्षर	select_समयout;		/* समयout (R5)				*/
		अचिन्हित अक्षर	sync_max_depth;		/* Synchronous xfer max fअगरo depth	*/
		अचिन्हित अक्षर	wide_max_size;		/* Maximum wide transfer size		*/
		अचिन्हित अक्षर	cntl3;			/* Control Reg 3			*/
		अचिन्हित पूर्णांक	asyncperiod;		/* Async transfer period (ns)		*/
		अचिन्हित पूर्णांक	capabilities;		/* driver capabilities			*/
		अचिन्हित पूर्णांक	disconnect_ok:1;	/* Disconnects allowed?			*/
	पूर्ण अगरcfg;

	/* queue handling */
	काष्ठा अणु
	    	Queue_t		issue;			/* issue queue				*/
    		Queue_t		disconnected;		/* disconnected command queue		*/
	पूर्ण queues;

	/* per-device info */
	काष्ठा fas216_device अणु
		अचिन्हित अक्षर	disconnect_ok:1;	/* device can disconnect		*/
		अचिन्हित अक्षर	parity_enabled:1;	/* parity checking enabled		*/
		अचिन्हित अक्षर	parity_check:1;		/* need to check parity checking	*/
		अचिन्हित अक्षर	period;			/* sync xfer period in (*4ns)		*/
		अचिन्हित अक्षर	stp;			/* synchronous transfer period		*/
		अचिन्हित अक्षर	sof;			/* synchronous offset रेजिस्टर		*/
		अचिन्हित अक्षर	wide_xfer;		/* currently negociated wide transfer	*/
		neg_t		sync_state;		/* synchronous transfer mode		*/
		neg_t		wide_state;		/* wide transfer mode			*/
	पूर्ण device[8];
	अचिन्हित दीर्घ	busyluns[64/माप(अचिन्हित दीर्घ)];/* array of bits indicating LUNs busy	*/

	/* dma */
	काष्ठा अणु
		fasdmatype_t	transfer_type;		/* current type of DMA transfer		*/
		fasdmatype_t	(*setup) (काष्ठा Scsi_Host *host, काष्ठा scsi_poपूर्णांकer *SCp, fasdmadir_t direction, fasdmatype_t min_dma);
		व्योम		(*pseuकरो)(काष्ठा Scsi_Host *host, काष्ठा scsi_poपूर्णांकer *SCp, fasdmadir_t direction, पूर्णांक transfer);
		व्योम		(*stop)  (काष्ठा Scsi_Host *host, काष्ठा scsi_poपूर्णांकer *SCp);
	पूर्ण dma;

	/* miscellaneous */
	पूर्णांक			पूर्णांकernal_करोne;		/* flag to indicate request करोne */
	काष्ठा scsi_eh_save	ses;		/* holds request sense restore info */
	अचिन्हित दीर्घ		magic_end;
पूर्ण FAS216_Info;

/* Function: पूर्णांक fas216_init (काष्ठा Scsi_Host *instance)
 * Purpose : initialise FAS/NCR/AMD SCSI काष्ठाures.
 * Params  : instance - a driver-specअगरic filled-out काष्ठाure
 * Returns : 0 on success
 */
बाह्य पूर्णांक fas216_init (काष्ठा Scsi_Host *instance);

/* Function: पूर्णांक fas216_add (काष्ठा Scsi_Host *instance, काष्ठा device *dev)
 * Purpose : initialise FAS/NCR/AMD SCSI ic.
 * Params  : instance - a driver-specअगरic filled-out काष्ठाure
 * Returns : 0 on success
 */
बाह्य पूर्णांक fas216_add (काष्ठा Scsi_Host *instance, काष्ठा device *dev);

/* Function: पूर्णांक fas216_queue_command(काष्ठा Scsi_Host *h, काष्ठा scsi_cmnd *SCpnt)
 * Purpose : queue a command क्रम adapter to process.
 * Params  : h - host adapter
 *	   : SCpnt - Command to queue
 * Returns : 0 - success, अन्यथा error
 */
बाह्य पूर्णांक fas216_queue_command(काष्ठा Scsi_Host *h, काष्ठा scsi_cmnd *SCpnt);

/* Function: पूर्णांक fas216_noqueue_command(काष्ठा Scsi_Host *h, काष्ठा scsi_cmnd *SCpnt)
 * Purpose : queue a command क्रम adapter to process, and process it to completion.
 * Params  : h - host adapter
 *	   : SCpnt - Command to queue
 * Returns : 0 - success, अन्यथा error
 */
बाह्य पूर्णांक fas216_noqueue_command(काष्ठा Scsi_Host *, काष्ठा scsi_cmnd *);

/* Function: irqवापस_t fas216_पूर्णांकr (FAS216_Info *info)
 * Purpose : handle पूर्णांकerrupts from the पूर्णांकerface to progress a command
 * Params  : info - पूर्णांकerface to service
 */
बाह्य irqवापस_t fas216_पूर्णांकr (FAS216_Info *info);

बाह्य व्योम fas216_हटाओ (काष्ठा Scsi_Host *instance);

/* Function: व्योम fas216_release (काष्ठा Scsi_Host *instance)
 * Purpose : release all resources and put everything to bed क्रम FAS/NCR/AMD SCSI ic.
 * Params  : instance - a driver-specअगरic filled-out काष्ठाure
 * Returns : 0 on success
 */
बाह्य व्योम fas216_release (काष्ठा Scsi_Host *instance);

बाह्य व्योम fas216_prपूर्णांक_host(FAS216_Info *info, काष्ठा seq_file *m);
बाह्य व्योम fas216_prपूर्णांक_stats(FAS216_Info *info, काष्ठा seq_file *m);
बाह्य व्योम fas216_prपूर्णांक_devices(FAS216_Info *info, काष्ठा seq_file *m);

/* Function: पूर्णांक fas216_eh_पात(काष्ठा scsi_cmnd *SCpnt)
 * Purpose : पात this command
 * Params  : SCpnt - command to पात
 * Returns : FAILED अगर unable to पात
 */
बाह्य पूर्णांक fas216_eh_पात(काष्ठा scsi_cmnd *SCpnt);

/* Function: पूर्णांक fas216_eh_device_reset(काष्ठा scsi_cmnd *SCpnt)
 * Purpose : Reset the device associated with this command
 * Params  : SCpnt - command specअगरing device to reset
 * Returns : FAILED अगर unable to reset
 */
बाह्य पूर्णांक fas216_eh_device_reset(काष्ठा scsi_cmnd *SCpnt);

/* Function: पूर्णांक fas216_eh_bus_reset(काष्ठा scsi_cmnd *SCpnt)
 * Purpose : Reset the complete bus associated with this command
 * Params  : SCpnt - command specअगरing bus to reset
 * Returns : FAILED अगर unable to reset
 */
बाह्य पूर्णांक fas216_eh_bus_reset(काष्ठा scsi_cmnd *SCpnt);

/* Function: पूर्णांक fas216_eh_host_reset(काष्ठा scsi_cmnd *SCpnt)
 * Purpose : Reset the host associated with this command
 * Params  : SCpnt - command specअगरing host to reset
 * Returns : FAILED अगर unable to reset
 */
बाह्य पूर्णांक fas216_eh_host_reset(काष्ठा scsi_cmnd *SCpnt);

#पूर्ण_अगर /* FAS216_H */
