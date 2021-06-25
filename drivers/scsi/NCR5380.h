<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* 
 * NCR 5380 defines
 *
 * Copyright 1993, Drew Eckhardt
 *	Visionary Computing
 *	(Unix consulting and custom programming)
 * 	drew@coloraकरो.edu
 *      +1 (303) 666-5836
 *
 * For more inक्रमmation, please consult 
 *
 * NCR 5380 Family
 * SCSI Protocol Controller
 * Databook
 * NCR Microelectronics
 * 1635 Aeroplaza Drive
 * Coloraकरो Springs, CO 80916
 * 1+ (719) 578-3400
 * 1+ (800) 334-5454
 */

#अगर_अघोषित NCR5380_H
#घोषणा NCR5380_H

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/workqueue.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_transport_spi.h>

#घोषणा न_संशोधन_ARBITRATION	0x1
#घोषणा न_संशोधन_AUTOSENSE	0x2
#घोषणा न_संशोधन_DMA		0x4
#घोषणा न_संशोधन_HANDSHAKE	0x8
#घोषणा न_संशोधन_INFORMATION	0x10
#घोषणा न_संशोधन_INIT		0x20
#घोषणा न_संशोधन_INTR		0x40
#घोषणा न_संशोधन_LINKED		0x80
#घोषणा न_संशोधन_MAIN		0x100
#घोषणा न_संशोधन_NO_DATAOUT	0x200
#घोषणा न_संशोधन_NO_WRITE		0x400
#घोषणा न_संशोधन_PIO		0x800
#घोषणा न_संशोधन_PSEUDO_DMA	0x1000
#घोषणा न_संशोधन_QUEUES		0x2000
#घोषणा न_संशोधन_RESELECTION	0x4000
#घोषणा न_संशोधन_SELECTION	0x8000
#घोषणा न_संशोधन_USLEEP		0x10000
#घोषणा न_संशोधन_LAST_BYTE_SENT	0x20000
#घोषणा न_संशोधन_RESTART_SELECT	0x40000
#घोषणा न_संशोधन_EXTENDED		0x80000
#घोषणा न_संशोधन_C400_PREAD	0x100000
#घोषणा न_संशोधन_C400_PWRITE	0x200000
#घोषणा न_संशोधन_LISTS		0x400000
#घोषणा न_संशोधन_ABORT		0x800000
#घोषणा न_संशोधन_TAGS		0x1000000
#घोषणा न_संशोधन_MERGING		0x2000000

#घोषणा न_संशोधन_ANY		0xFFFFFFFFUL

/* 
 * The contents of the OUTPUT DATA रेजिस्टर are निश्चितed on the bus when
 * either arbitration is occurring or the phase-indicating संकेतs (
 * IO, CD, MSG) in the TARGET COMMAND रेजिस्टर and the ASSERT DATA
 * bit in the INITIATOR COMMAND रेजिस्टर is set.
 */

#घोषणा OUTPUT_DATA_REG         0	/* wo DATA lines on SCSI bus */
#घोषणा CURRENT_SCSI_DATA_REG   0	/* ro same */

#घोषणा INITIATOR_COMMAND_REG	1	/* rw */
#घोषणा ICR_ASSERT_RST		0x80	/* rw Set to निश्चित RST  */
#घोषणा ICR_ARBITRATION_PROGRESS 0x40	/* ro Indicates arbitration complete */
#घोषणा ICR_TRI_STATE		0x40	/* wo Set to tri-state drivers */
#घोषणा ICR_ARBITRATION_LOST	0x20	/* ro Indicates arbitration lost */
#घोषणा ICR_DIFF_ENABLE		0x20	/* wo Set to enable dअगरf. drivers */
#घोषणा ICR_ASSERT_ACK		0x10	/* rw ini Set to निश्चित ACK */
#घोषणा ICR_ASSERT_BSY		0x08	/* rw Set to निश्चित BSY */
#घोषणा ICR_ASSERT_SEL 		0x04	/* rw Set to निश्चित SEL */
#घोषणा ICR_ASSERT_ATN		0x02	/* rw Set to निश्चित ATN */
#घोषणा ICR_ASSERT_DATA		0x01	/* rw SCSI_DATA_REG is निश्चितed */

#घोषणा ICR_BASE		0

#घोषणा MODE_REG		2
/*
 * Note : BLOCK_DMA code will keep DRQ निश्चितed क्रम the duration of the 
 * transfer, causing the chip to hog the bus.  You probably करोn't want 
 * this.
 */
#घोषणा MR_BLOCK_DMA_MODE	0x80	/* rw block mode DMA */
#घोषणा MR_TARGET		0x40	/* rw target mode */
#घोषणा MR_ENABLE_PAR_CHECK	0x20	/* rw enable parity checking */
#घोषणा MR_ENABLE_PAR_INTR	0x10	/* rw enable bad parity पूर्णांकerrupt */
#घोषणा MR_ENABLE_EOP_INTR	0x08	/* rw enable eop पूर्णांकerrupt */
#घोषणा MR_MONITOR_BSY		0x04	/* rw enable पूर्णांक on unexpected bsy fail */
#घोषणा MR_DMA_MODE		0x02	/* rw DMA / pseuकरो DMA mode */
#घोषणा MR_ARBITRATE		0x01	/* rw start arbitration */

#घोषणा MR_BASE			0

#घोषणा TARGET_COMMAND_REG	3
#घोषणा TCR_LAST_BYTE_SENT	0x80	/* ro DMA करोne */
#घोषणा TCR_ASSERT_REQ		0x08	/* tgt rw निश्चित REQ */
#घोषणा TCR_ASSERT_MSG		0x04	/* tgt rw निश्चित MSG */
#घोषणा TCR_ASSERT_CD		0x02	/* tgt rw निश्चित CD */
#घोषणा TCR_ASSERT_IO		0x01	/* tgt rw निश्चित IO */

#घोषणा STATUS_REG		4	/* ro */
/*
 * Note : a set bit indicates an active संकेत, driven by us or another 
 * device.
 */
#घोषणा SR_RST			0x80
#घोषणा SR_BSY			0x40
#घोषणा SR_REQ			0x20
#घोषणा SR_MSG			0x10
#घोषणा SR_CD			0x08
#घोषणा SR_IO			0x04
#घोषणा SR_SEL			0x02
#घोषणा SR_DBP			0x01

/*
 * Setting a bit in this रेजिस्टर will cause an पूर्णांकerrupt to be generated when 
 * BSY is false and SEL true and this bit is निश्चितed  on the bus.
 */
#घोषणा SELECT_ENABLE_REG	4	/* wo */

#घोषणा BUS_AND_STATUS_REG	5	/* ro */
#घोषणा BASR_END_DMA_TRANSFER	0x80	/* ro set on end of transfer */
#घोषणा BASR_DRQ		0x40	/* ro mirror of DRQ pin */
#घोषणा BASR_PARITY_ERROR	0x20	/* ro parity error detected */
#घोषणा BASR_IRQ		0x10	/* ro mirror of IRQ pin */
#घोषणा BASR_PHASE_MATCH	0x08	/* ro Set when MSG CD IO match TCR */
#घोषणा BASR_BUSY_ERROR		0x04	/* ro Unexpected change to inactive state */
#घोषणा BASR_ATN 		0x02	/* ro BUS status */
#घोषणा BASR_ACK		0x01	/* ro BUS status */

/* Write any value to this रेजिस्टर to start a DMA send */
#घोषणा START_DMA_SEND_REG	5	/* wo */

/* 
 * Used in DMA transfer mode, data is latched from the SCSI bus on
 * the falling edge of REQ (ini) or ACK (tgt)
 */
#घोषणा INPUT_DATA_REG			6	/* ro */

/* Write any value to this रेजिस्टर to start a DMA receive */
#घोषणा START_DMA_TARGET_RECEIVE_REG	6	/* wo */

/* Read this रेजिस्टर to clear पूर्णांकerrupt conditions */
#घोषणा RESET_PARITY_INTERRUPT_REG	7	/* ro */

/* Write any value to this रेजिस्टर to start an ini mode DMA receive */
#घोषणा START_DMA_INITIATOR_RECEIVE_REG 7	/* wo */

/* NCR 53C400(A) Control Status Register bits: */
#घोषणा CSR_RESET              0x80	/* wo  Resets 53c400 */
#घोषणा CSR_53C80_REG          0x80	/* ro  5380 रेजिस्टरs busy */
#घोषणा CSR_TRANS_सूची          0x40	/* rw  Data transfer direction */
#घोषणा CSR_SCSI_BUFF_INTR     0x20	/* rw  Enable पूर्णांक on transfer पढ़ोy */
#घोषणा CSR_53C80_INTR         0x10	/* rw  Enable 53c80 पूर्णांकerrupts */
#घोषणा CSR_SHARED_INTR        0x08	/* rw  Interrupt sharing */
#घोषणा CSR_HOST_BUF_NOT_RDY   0x04	/* ro  Is Host buffer पढ़ोy */
#घोषणा CSR_SCSI_BUF_RDY       0x02	/* ro  SCSI buffer पढ़ो */
#घोषणा CSR_GATED_53C80_IRQ    0x01	/* ro  Last block xferred */

#घोषणा CSR_BASE CSR_53C80_INTR

/* Note : PHASE_* macros are based on the values of the STATUS रेजिस्टर */
#घोषणा PHASE_MASK 	(SR_MSG | SR_CD | SR_IO)

#घोषणा PHASE_DATAOUT		0
#घोषणा PHASE_DATAIN		SR_IO
#घोषणा PHASE_CMDOUT		SR_CD
#घोषणा PHASE_STATIN		(SR_CD | SR_IO)
#घोषणा PHASE_MSGOUT		(SR_MSG | SR_CD)
#घोषणा PHASE_MSGIN		(SR_MSG | SR_CD | SR_IO)
#घोषणा PHASE_UNKNOWN		0xff

/* 
 * Convert status रेजिस्टर phase to something we can use to set phase in 
 * the target रेजिस्टर so we can get phase mismatch पूर्णांकerrupts on DMA 
 * transfers.
 */

#घोषणा PHASE_SR_TO_TCR(phase) ((phase) >> 2)

#अगर_अघोषित NO_IRQ
#घोषणा NO_IRQ		0
#पूर्ण_अगर

#घोषणा FLAG_DMA_FIXUP			1	/* Use DMA errata workarounds */
#घोषणा FLAG_NO_PSEUDO_DMA		8	/* Inhibit DMA */
#घोषणा FLAG_LATE_DMA_SETUP		32	/* Setup NCR beक्रमe DMA H/W */
#घोषणा FLAG_TOSHIBA_DELAY		128	/* Allow क्रम borken CD-ROMs */

काष्ठा NCR5380_hostdata अणु
	NCR5380_implementation_fields;		/* Board-specअगरic data */
	u8 __iomem *io;				/* Remapped 5380 address */
	u8 __iomem *pdma_io;			/* Remapped PDMA address */
	अचिन्हित दीर्घ poll_loops;		/* Register polling limit */
	spinlock_t lock;			/* Protects this काष्ठा */
	काष्ठा scsi_cmnd *connected;		/* Currently connected cmnd */
	काष्ठा list_head disconnected;		/* Waiting क्रम reconnect */
	काष्ठा Scsi_Host *host;			/* SCSI host backpoपूर्णांकer */
	काष्ठा workqueue_काष्ठा *work_q;	/* SCSI host work queue */
	काष्ठा work_काष्ठा मुख्य_task;		/* Work item क्रम मुख्य loop */
	पूर्णांक flags;				/* Board-specअगरic quirks */
	पूर्णांक dma_len;				/* Requested length of DMA */
	पूर्णांक पढ़ो_overruns;	/* Transfer size reduction क्रम DMA erratum */
	अचिन्हित दीर्घ io_port;			/* Device IO port */
	अचिन्हित दीर्घ base;			/* Device base address */
	काष्ठा list_head unissued;		/* Waiting to be issued */
	काष्ठा scsi_cmnd *selecting;		/* Cmnd to be connected */
	काष्ठा list_head स्वतःsense;		/* Priority cmnd queue */
	काष्ठा scsi_cmnd *sensing;		/* Cmnd needing स्वतःsense */
	काष्ठा scsi_eh_save ses;		/* Cmnd state saved क्रम EH */
	अचिन्हित अक्षर busy[8];			/* Index = target, bit = lun */
	अचिन्हित अक्षर id_mask;			/* 1 << Host ID */
	अचिन्हित अक्षर id_higher_mask;		/* All bits above id_mask */
	अचिन्हित अक्षर last_message;		/* Last Message Out */
	अचिन्हित दीर्घ region_size;		/* Size of address/port range */
	अक्षर info[168];				/* Host banner message */
पूर्ण;

काष्ठा NCR5380_cmd अणु
	काष्ठा list_head list;
पूर्ण;

#घोषणा NCR5380_CMD_SIZE		(माप(काष्ठा NCR5380_cmd))

#घोषणा NCR5380_PIO_CHUNK_SIZE		256

/* Time limit (ms) to poll रेजिस्टरs when IRQs are disabled, e.g. during PDMA */
#घोषणा NCR5380_REG_POLL_TIME		10

अटल अंतरभूत काष्ठा scsi_cmnd *NCR5380_to_scmd(काष्ठा NCR5380_cmd *ncmd_ptr)
अणु
	वापस ((काष्ठा scsi_cmnd *)ncmd_ptr) - 1;
पूर्ण

#अगर_अघोषित न_संशोधन
#घोषणा न_संशोधन (0)
#पूर्ण_अगर

#घोषणा dprपूर्णांकk(flg, fmt, ...) \
	करो अणु अगर ((न_संशोधन) & (flg)) \
		prपूर्णांकk(KERN_DEBUG fmt, ## __VA_ARGS__); पूर्ण जबतक (0)

#घोषणा dsprपूर्णांकk(flg, host, fmt, ...) \
	करो अणु अगर ((न_संशोधन) & (flg)) \
		shost_prपूर्णांकk(KERN_DEBUG, host, fmt, ## __VA_ARGS__); \
	पूर्ण जबतक (0)

#अगर न_संशोधन
#घोषणा NCR5380_dprपूर्णांक(flg, arg) \
	करो अणु अगर ((न_संशोधन) & (flg)) NCR5380_prपूर्णांक(arg); पूर्ण जबतक (0)
#घोषणा NCR5380_dprपूर्णांक_phase(flg, arg) \
	करो अणु अगर ((न_संशोधन) & (flg)) NCR5380_prपूर्णांक_phase(arg); पूर्ण जबतक (0)
अटल व्योम NCR5380_prपूर्णांक_phase(काष्ठा Scsi_Host *instance);
अटल व्योम NCR5380_prपूर्णांक(काष्ठा Scsi_Host *instance);
#अन्यथा
#घोषणा NCR5380_dprपूर्णांक(flg, arg)       करो अणुपूर्ण जबतक (0)
#घोषणा NCR5380_dprपूर्णांक_phase(flg, arg) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

अटल पूर्णांक NCR5380_init(काष्ठा Scsi_Host *instance, पूर्णांक flags);
अटल पूर्णांक NCR5380_maybe_reset_bus(काष्ठा Scsi_Host *);
अटल व्योम NCR5380_निकास(काष्ठा Scsi_Host *instance);
अटल व्योम NCR5380_inक्रमmation_transfer(काष्ठा Scsi_Host *instance);
अटल irqवापस_t NCR5380_पूर्णांकr(पूर्णांक irq, व्योम *dev_id);
अटल व्योम NCR5380_मुख्य(काष्ठा work_काष्ठा *work);
अटल स्थिर अक्षर *NCR5380_info(काष्ठा Scsi_Host *instance);
अटल व्योम NCR5380_reselect(काष्ठा Scsi_Host *instance);
अटल bool NCR5380_select(काष्ठा Scsi_Host *, काष्ठा scsi_cmnd *);
अटल पूर्णांक NCR5380_transfer_dma(काष्ठा Scsi_Host *instance, अचिन्हित अक्षर *phase, पूर्णांक *count, अचिन्हित अक्षर **data);
अटल पूर्णांक NCR5380_transfer_pio(काष्ठा Scsi_Host *instance, अचिन्हित अक्षर *phase, पूर्णांक *count, अचिन्हित अक्षर **data,
				अचिन्हित पूर्णांक can_sleep);
अटल पूर्णांक NCR5380_poll_politely2(काष्ठा NCR5380_hostdata *,
                                  अचिन्हित पूर्णांक, u8, u8,
                                  अचिन्हित पूर्णांक, u8, u8, अचिन्हित दीर्घ);

अटल अंतरभूत पूर्णांक NCR5380_poll_politely(काष्ठा NCR5380_hostdata *hostdata,
                                        अचिन्हित पूर्णांक reg, u8 bit, u8 val,
                                        अचिन्हित दीर्घ रुको)
अणु
	अगर ((NCR5380_पढ़ो(reg) & bit) == val)
		वापस 0;

	वापस NCR5380_poll_politely2(hostdata, reg, bit, val,
						reg, bit, val, रुको);
पूर्ण

अटल पूर्णांक NCR5380_dma_xfer_len(काष्ठा NCR5380_hostdata *,
                                काष्ठा scsi_cmnd *);
अटल पूर्णांक NCR5380_dma_send_setup(काष्ठा NCR5380_hostdata *,
                                  अचिन्हित अक्षर *, पूर्णांक);
अटल पूर्णांक NCR5380_dma_recv_setup(काष्ठा NCR5380_hostdata *,
                                  अचिन्हित अक्षर *, पूर्णांक);
अटल पूर्णांक NCR5380_dma_residual(काष्ठा NCR5380_hostdata *);

अटल अंतरभूत पूर्णांक NCR5380_dma_xfer_none(काष्ठा NCR5380_hostdata *hostdata,
                                        काष्ठा scsi_cmnd *cmd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक NCR5380_dma_setup_none(काष्ठा NCR5380_hostdata *hostdata,
                                         अचिन्हित अक्षर *data, पूर्णांक count)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक NCR5380_dma_residual_none(काष्ठा NCR5380_hostdata *hostdata)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर				/* NCR5380_H */
