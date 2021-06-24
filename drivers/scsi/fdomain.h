<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#घोषणा FDOMAIN_REGION_SIZE	0x10
#घोषणा FDOMAIN_BIOS_SIZE	0x2000

क्रमागत अणु
	in_arbitration	= 0x02,
	in_selection	= 0x04,
	in_other	= 0x08,
	disconnect	= 0x10,
	पातed		= 0x20,
	sent_ident	= 0x40,
पूर्ण;

/* (@) = not present on TMC1800, (#) = not present on TMC1800 and TMC18C50 */
#घोषणा REG_SCSI_DATA		0	/* R/W: SCSI Data (with ACK) */
#घोषणा REG_BSTAT		1	/* R: SCSI Bus Status */
#घोषणा		BSTAT_BSY	BIT(0)	 /* Busy */
#घोषणा		BSTAT_MSG	BIT(1)	 /* Message */
#घोषणा		BSTAT_IO	BIT(2)	 /* Input/Output */
#घोषणा		BSTAT_CMD	BIT(3)	 /* Command/Data */
#घोषणा		BSTAT_REQ	BIT(4)	 /* Request and Not Ack */
#घोषणा		BSTAT_SEL	BIT(5)	 /* Select */
#घोषणा		BSTAT_ACK	BIT(6)	 /* Acknowledge and Request */
#घोषणा		BSTAT_ATN	BIT(7)	 /* Attention */
#घोषणा REG_BCTL		1	/* W: SCSI Bus Control */
#घोषणा		BCTL_RST	BIT(0)	 /* Bus Reset */
#घोषणा		BCTL_SEL	BIT(1)	 /* Select */
#घोषणा		BCTL_BSY	BIT(2)	 /* Busy */
#घोषणा		BCTL_ATN	BIT(3)	 /* Attention */
#घोषणा		BCTL_IO		BIT(4)	 /* Input/Output */
#घोषणा		BCTL_CMD	BIT(5)	 /* Command/Data */
#घोषणा		BCTL_MSG	BIT(6)	 /* Message */
#घोषणा		BCTL_BUSEN	BIT(7)	 /* Enable bus drivers */
#घोषणा REG_ASTAT		2	/* R: Adapter Status 1 */
#घोषणा		ASTAT_IRQ	BIT(0)	 /* Interrupt active */
#घोषणा		ASTAT_ARB	BIT(1)	 /* Arbitration complete */
#घोषणा		ASTAT_PARERR	BIT(2)	 /* Parity error */
#घोषणा		ASTAT_RST	BIT(3)	 /* SCSI reset occurred */
#घोषणा		ASTAT_FIFOसूची	BIT(4)	 /* FIFO direction */
#घोषणा		ASTAT_FIFOEN	BIT(5)	 /* FIFO enabled */
#घोषणा		ASTAT_PAREN	BIT(6)	 /* Parity enabled */
#घोषणा		ASTAT_BUSEN	BIT(7)	 /* Bus drivers enabled */
#घोषणा REG_ICTL		2	/* W: Interrupt Control */
#घोषणा		ICTL_FIFO_MASK	0x0f	 /* FIFO threshold, 1/16 FIFO size */
#घोषणा		ICTL_FIFO	BIT(4)	 /* Int. on FIFO count */
#घोषणा		ICTL_ARB	BIT(5)	 /* Int. on Arbitration complete */
#घोषणा		ICTL_SEL	BIT(6)	 /* Int. on SCSI Select */
#घोषणा		ICTL_REQ	BIT(7)	 /* Int. on SCSI Request */
#घोषणा REG_FSTAT		3	/* R: Adapter Status 2 (FIFO) - (@) */
#घोषणा		FSTAT_ONOTEMPTY	BIT(0)	 /* Output FIFO not empty */
#घोषणा		FSTAT_INOTEMPTY	BIT(1)	 /* Input FIFO not empty */
#घोषणा		FSTAT_NOTEMPTY	BIT(2)	 /* Main FIFO not empty */
#घोषणा		FSTAT_NOTFULL	BIT(3)	 /* Main FIFO not full */
#घोषणा REG_MCTL		3	/* W: SCSI Data Mode Control */
#घोषणा		MCTL_ACK_MASK	0x0f	 /* Acknowledge period */
#घोषणा		MCTL_ACTDEASS	BIT(4)	 /* Active deनिश्चित of REQ and ACK */
#घोषणा		MCTL_TARGET	BIT(5)	 /* Enable target mode */
#घोषणा		MCTL_FASTSYNC	BIT(6)	 /* Enable Fast Synchronous */
#घोषणा		MCTL_SYNC	BIT(7)	 /* Enable Synchronous */
#घोषणा REG_INTCOND		4	/* R: Interrupt Condition - (@) */
#घोषणा		IRQ_FIFO	BIT(1)	 /* FIFO पूर्णांकerrupt */
#घोषणा		IRQ_REQ		BIT(2)	 /* SCSI Request पूर्णांकerrupt */
#घोषणा		IRQ_SEL		BIT(3)	 /* SCSI Select पूर्णांकerrupt */
#घोषणा		IRQ_ARB		BIT(4)	 /* SCSI Arbitration पूर्णांकerrupt */
#घोषणा		IRQ_RST		BIT(5)	 /* SCSI Reset पूर्णांकerrupt */
#घोषणा		IRQ_FORCED	BIT(6)	 /* Forced पूर्णांकerrupt */
#घोषणा		IRQ_TIMEOUT	BIT(7)	 /* Bus समयout */
#घोषणा REG_ACTL		4	/* W: Adapter Control 1 */
#घोषणा		ACTL_RESET	BIT(0)	 /* Reset FIFO, parity, reset पूर्णांक. */
#घोषणा		ACTL_FIRQ	BIT(1)	 /* Set Forced पूर्णांकerrupt */
#घोषणा		ACTL_ARB	BIT(2)	 /* Initiate Bus Arbitration */
#घोषणा		ACTL_PAREN	BIT(3)	 /* Enable SCSI Parity */
#घोषणा		ACTL_IRQEN	BIT(4)	 /* Enable पूर्णांकerrupts */
#घोषणा		ACTL_CLRFIRQ	BIT(5)	 /* Clear Forced पूर्णांकerrupt */
#घोषणा		ACTL_FIFOWR	BIT(6)	 /* FIFO Direction (1=ग_लिखो) */
#घोषणा		ACTL_FIFOEN	BIT(7)	 /* Enable FIFO */
#घोषणा REG_ID_LSB		5	/* R: ID Code (LSB) */
#घोषणा REG_ACTL2		5	/* Adapter Control 2 - (@) */
#घोषणा		ACTL2_RAMOVRLY	BIT(0)	 /* Enable RAM overlay */
#घोषणा		ACTL2_SLEEP	BIT(7)	 /* Sleep mode */
#घोषणा REG_ID_MSB		6	/* R: ID Code (MSB) */
#घोषणा REG_LOOPBACK		7	/* R/W: Loopback */
#घोषणा REG_SCSI_DATA_NOACK	8	/* R/W: SCSI Data (no ACK) */
#घोषणा REG_ASTAT3		9	/* R: Adapter Status 3 */
#घोषणा		ASTAT3_ACTDEASS	BIT(0)	 /* Active deनिश्चित enabled */
#घोषणा		ASTAT3_RAMOVRLY	BIT(1)	 /* RAM overlay enabled */
#घोषणा		ASTAT3_TARGERR	BIT(2)	 /* Target error */
#घोषणा		ASTAT3_IRQEN	BIT(3)	 /* Interrupts enabled */
#घोषणा		ASTAT3_IRQMASK	0xf0	 /* Enabled पूर्णांकerrupts mask */
#घोषणा REG_CFG1		10	/* R: Configuration Register 1 */
#घोषणा		CFG1_BUS	BIT(0)	 /* 0 = ISA */
#घोषणा		CFG1_IRQ_MASK	0x0e	 /* IRQ jumpers */
#घोषणा		CFG1_IO_MASK	0x30	 /* I/O base jumpers */
#घोषणा		CFG1_BIOS_MASK	0xc0	 /* BIOS base jumpers */
#घोषणा REG_CFG2		11	/* R/W: Configuration Register 2 (@) */
#घोषणा		CFG2_ROMDIS	BIT(0)	 /* ROM disabled */
#घोषणा		CFG2_RAMDIS	BIT(1)	 /* RAM disabled */
#घोषणा		CFG2_IRQEDGE	BIT(2)	 /* Edge-triggered पूर्णांकerrupts */
#घोषणा		CFG2_NOWS	BIT(3)	 /* No रुको states */
#घोषणा		CFG2_32BIT	BIT(7)	 /* 32-bit mode */
#घोषणा REG_FIFO		12	/* R/W: FIFO */
#घोषणा REG_FIFO_COUNT		14	/* R: FIFO Data Count */

#अगर_घोषित CONFIG_PM_SLEEP
अटल स्थिर काष्ठा dev_pm_ops __maybe_unused fकरोमुख्य_pm_ops;
#घोषणा FDOMAIN_PM_OPS	(&fकरोमुख्य_pm_ops)
#अन्यथा
#घोषणा FDOMAIN_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

काष्ठा Scsi_Host *fकरोमुख्य_create(पूर्णांक base, पूर्णांक irq, पूर्णांक this_id,
				 काष्ठा device *dev);
पूर्णांक fकरोमुख्य_destroy(काष्ठा Scsi_Host *sh);
