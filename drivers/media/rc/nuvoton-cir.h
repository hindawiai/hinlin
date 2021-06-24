<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम Nuvoton Technology Corporation w83667hg/w83677hg-i CIR
 *
 * Copyright (C) 2010 Jarod Wilson <jarod@redhat.com>
 * Copyright (C) 2009 Nuvoton PS Team
 *
 * Special thanks to Nuvoton क्रम providing hardware, spec sheets and
 * sample code upon which portions of this driver are based. Indirect
 * thanks also to Maxim Levitsky, whose ene_ir driver this driver is
 * modeled after.
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/ioctl.h>

/* platक्रमm driver name to रेजिस्टर */
#घोषणा NVT_DRIVER_NAME "nuvoton-cir"

/* debugging module parameter */
अटल पूर्णांक debug;


#घोषणा nvt_dbg(text, ...) \
	अगर (debug) \
		prपूर्णांकk(KERN_DEBUG \
			KBUILD_MODNAME ": " text "\n" , ## __VA_ARGS__)

#घोषणा nvt_dbg_verbose(text, ...) \
	अगर (debug > 1) \
		prपूर्णांकk(KERN_DEBUG \
			KBUILD_MODNAME ": " text "\n" , ## __VA_ARGS__)

#घोषणा nvt_dbg_wake(text, ...) \
	अगर (debug > 2) \
		prपूर्णांकk(KERN_DEBUG \
			KBUILD_MODNAME ": " text "\n" , ## __VA_ARGS__)


#घोषणा RX_BUF_LEN 32

#घोषणा SIO_ID_MASK 0xfff0

क्रमागत nvt_chip_ver अणु
	NVT_UNKNOWN	= 0,
	NVT_W83667HG	= 0xa510,
	NVT_6775F	= 0xb470,
	NVT_6776F	= 0xc330,
	NVT_6779D	= 0xc560,
	NVT_INVALID	= 0xffff,
पूर्ण;

काष्ठा nvt_chip अणु
	स्थिर अक्षर *name;
	क्रमागत nvt_chip_ver chip_ver;
पूर्ण;

काष्ठा nvt_dev अणु
	काष्ठा rc_dev *rdev;

	spinlock_t lock;

	/* क्रम rx */
	u8 buf[RX_BUF_LEN];
	अचिन्हित पूर्णांक pkts;

	/* EFER Config रेजिस्टर index/data pair */
	u32 cr_efir;
	u32 cr_efdr;

	/* hardware I/O settings */
	अचिन्हित दीर्घ cir_addr;
	अचिन्हित दीर्घ cir_wake_addr;
	पूर्णांक cir_irq;

	क्रमागत nvt_chip_ver chip_ver;
	/* hardware id */
	u8 chip_major;
	u8 chip_minor;

	/* carrier period = 1 / frequency */
	u32 carrier;
पूर्ण;

/* buffer packet स्थिरants */
#घोषणा BUF_PULSE_BIT	0x80
#घोषणा BUF_LEN_MASK	0x7f
#घोषणा BUF_REPEAT_BYTE	0x70
#घोषणा BUF_REPEAT_MASK	0xf0

/* CIR settings */

/* total length of CIR and CIR WAKE */
#घोषणा CIR_IOREG_LENGTH	0x0f

/* RX limit length, 8 high bits क्रम SLCH, 8 low bits क्रम SLCL */
#घोषणा CIR_RX_LIMIT_COUNT  (IR_DEFAULT_TIMEOUT / SAMPLE_PERIOD)

/* CIR Regs */
#घोषणा CIR_IRCON	0x00
#घोषणा CIR_IRSTS	0x01
#घोषणा CIR_IREN	0x02
#घोषणा CIR_RXFCONT	0x03
#घोषणा CIR_CP		0x04
#घोषणा CIR_CC		0x05
#घोषणा CIR_SLCH	0x06
#घोषणा CIR_SLCL	0x07
#घोषणा CIR_FIFOCON	0x08
#घोषणा CIR_IRFIFOSTS	0x09
#घोषणा CIR_SRXFIFO	0x0a
#घोषणा CIR_TXFCONT	0x0b
#घोषणा CIR_STXFIFO	0x0c
#घोषणा CIR_FCCH	0x0d
#घोषणा CIR_FCCL	0x0e
#घोषणा CIR_IRFSM	0x0f

/* CIR IRCON settings */
#घोषणा CIR_IRCON_RECV	 0x80
#घोषणा CIR_IRCON_WIREN	 0x40
#घोषणा CIR_IRCON_TXEN	 0x20
#घोषणा CIR_IRCON_RXEN	 0x10
#घोषणा CIR_IRCON_WRXINV 0x08
#घोषणा CIR_IRCON_RXINV	 0x04

#घोषणा CIR_IRCON_SAMPLE_PERIOD_SEL_1	0x00
#घोषणा CIR_IRCON_SAMPLE_PERIOD_SEL_25	0x01
#घोषणा CIR_IRCON_SAMPLE_PERIOD_SEL_50	0x02
#घोषणा CIR_IRCON_SAMPLE_PERIOD_SEL_100	0x03

/* FIXME: make this a runसमय option */
/* select sample period as 50us */
#घोषणा CIR_IRCON_SAMPLE_PERIOD_SEL	CIR_IRCON_SAMPLE_PERIOD_SEL_50

/* CIR IRSTS settings */
#घोषणा CIR_IRSTS_RDR	0x80
#घोषणा CIR_IRSTS_RTR	0x40
#घोषणा CIR_IRSTS_PE	0x20
#घोषणा CIR_IRSTS_RFO	0x10
#घोषणा CIR_IRSTS_TE	0x08
#घोषणा CIR_IRSTS_TTR	0x04
#घोषणा CIR_IRSTS_TFU	0x02
#घोषणा CIR_IRSTS_GH	0x01

/* CIR IREN settings */
#घोषणा CIR_IREN_RDR	0x80
#घोषणा CIR_IREN_RTR	0x40
#घोषणा CIR_IREN_PE	0x20
#घोषणा CIR_IREN_RFO	0x10
#घोषणा CIR_IREN_TE	0x08
#घोषणा CIR_IREN_TTR	0x04
#घोषणा CIR_IREN_TFU	0x02
#घोषणा CIR_IREN_GH	0x01

/* CIR FIFOCON settings */
#घोषणा CIR_FIFOCON_TXFIFOCLR		0x80

#घोषणा CIR_FIFOCON_TX_TRIGGER_LEV_31	0x00
#घोषणा CIR_FIFOCON_TX_TRIGGER_LEV_24	0x10
#घोषणा CIR_FIFOCON_TX_TRIGGER_LEV_16	0x20
#घोषणा CIR_FIFOCON_TX_TRIGGER_LEV_8	0x30

/* FIXME: make this a runसमय option */
/* select TX trigger level as 16 */
#घोषणा CIR_FIFOCON_TX_TRIGGER_LEV	CIR_FIFOCON_TX_TRIGGER_LEV_16

#घोषणा CIR_FIFOCON_RXFIFOCLR		0x08

#घोषणा CIR_FIFOCON_RX_TRIGGER_LEV_1	0x00
#घोषणा CIR_FIFOCON_RX_TRIGGER_LEV_8	0x01
#घोषणा CIR_FIFOCON_RX_TRIGGER_LEV_16	0x02
#घोषणा CIR_FIFOCON_RX_TRIGGER_LEV_24	0x03

/* FIXME: make this a runसमय option */
/* select RX trigger level as 24 */
#घोषणा CIR_FIFOCON_RX_TRIGGER_LEV	CIR_FIFOCON_RX_TRIGGER_LEV_24

/* CIR IRFIFOSTS settings */
#घोषणा CIR_IRFIFOSTS_IR_PENDING	0x80
#घोषणा CIR_IRFIFOSTS_RX_GS		0x40
#घोषणा CIR_IRFIFOSTS_RX_FTA		0x20
#घोषणा CIR_IRFIFOSTS_RX_EMPTY		0x10
#घोषणा CIR_IRFIFOSTS_RX_FULL		0x08
#घोषणा CIR_IRFIFOSTS_TX_FTA		0x04
#घोषणा CIR_IRFIFOSTS_TX_EMPTY		0x02
#घोषणा CIR_IRFIFOSTS_TX_FULL		0x01


/* CIR WAKE UP Regs */
#घोषणा CIR_WAKE_IRCON			0x00
#घोषणा CIR_WAKE_IRSTS			0x01
#घोषणा CIR_WAKE_IREN			0x02
#घोषणा CIR_WAKE_FIFO_CMP_DEEP		0x03
#घोषणा CIR_WAKE_FIFO_CMP_TOL		0x04
#घोषणा CIR_WAKE_FIFO_COUNT		0x05
#घोषणा CIR_WAKE_SLCH			0x06
#घोषणा CIR_WAKE_SLCL			0x07
#घोषणा CIR_WAKE_FIFOCON		0x08
#घोषणा CIR_WAKE_SRXFSTS		0x09
#घोषणा CIR_WAKE_SAMPLE_RX_FIFO		0x0a
#घोषणा CIR_WAKE_WR_FIFO_DATA		0x0b
#घोषणा CIR_WAKE_RD_FIFO_ONLY		0x0c
#घोषणा CIR_WAKE_RD_FIFO_ONLY_IDX	0x0d
#घोषणा CIR_WAKE_FIFO_IGNORE		0x0e
#घोषणा CIR_WAKE_IRFSM			0x0f

/* CIR WAKE UP IRCON settings */
#घोषणा CIR_WAKE_IRCON_DEC_RST		0x80
#घोषणा CIR_WAKE_IRCON_MODE1		0x40
#घोषणा CIR_WAKE_IRCON_MODE0		0x20
#घोषणा CIR_WAKE_IRCON_RXEN		0x10
#घोषणा CIR_WAKE_IRCON_R		0x08
#घोषणा CIR_WAKE_IRCON_RXINV		0x04

/* FIXME/jarod: make this a runसमय option */
/* select a same sample period like cir रेजिस्टर */
#घोषणा CIR_WAKE_IRCON_SAMPLE_PERIOD_SEL	CIR_IRCON_SAMPLE_PERIOD_SEL_50

/* CIR WAKE IRSTS Bits */
#घोषणा CIR_WAKE_IRSTS_RDR		0x80
#घोषणा CIR_WAKE_IRSTS_RTR		0x40
#घोषणा CIR_WAKE_IRSTS_PE		0x20
#घोषणा CIR_WAKE_IRSTS_RFO		0x10
#घोषणा CIR_WAKE_IRSTS_GH		0x08
#घोषणा CIR_WAKE_IRSTS_IR_PENDING	0x01

/* CIR WAKE UP IREN Bits */
#घोषणा CIR_WAKE_IREN_RDR		0x80
#घोषणा CIR_WAKE_IREN_RTR		0x40
#घोषणा CIR_WAKE_IREN_PE		0x20
#घोषणा CIR_WAKE_IREN_RFO		0x10
#घोषणा CIR_WAKE_IREN_GH		0x08

/* CIR WAKE FIFOCON settings */
#घोषणा CIR_WAKE_FIFOCON_RXFIFOCLR	0x08

#घोषणा CIR_WAKE_FIFOCON_RX_TRIGGER_LEV_67	0x00
#घोषणा CIR_WAKE_FIFOCON_RX_TRIGGER_LEV_66	0x01
#घोषणा CIR_WAKE_FIFOCON_RX_TRIGGER_LEV_65	0x02
#घोषणा CIR_WAKE_FIFOCON_RX_TRIGGER_LEV_64	0x03

/* FIXME: make this a runसमय option */
/* select WAKE UP RX trigger level as 67 */
#घोषणा CIR_WAKE_FIFOCON_RX_TRIGGER_LEV	CIR_WAKE_FIFOCON_RX_TRIGGER_LEV_67

/* CIR WAKE SRXFSTS settings */
#घोषणा CIR_WAKE_IRFIFOSTS_RX_GS	0x80
#घोषणा CIR_WAKE_IRFIFOSTS_RX_FTA	0x40
#घोषणा CIR_WAKE_IRFIFOSTS_RX_EMPTY	0x20
#घोषणा CIR_WAKE_IRFIFOSTS_RX_FULL	0x10

/*
 * The CIR Wake FIFO buffer is 67 bytes दीर्घ, but the stock remote wakes
 * the प्रणाली comparing only 65 bytes (fails with this set to 67)
 */
#घोषणा CIR_WAKE_FIFO_CMP_BYTES		65
/* CIR Wake byte comparison tolerance */
#घोषणा CIR_WAKE_CMP_TOLERANCE		5

/*
 * Extended Function Enable Registers:
 *  Extended Function Index Register
 *  Extended Function Data Register
 */
#घोषणा CR_EFIR			0x2e
#घोषणा CR_EFDR			0x2f

/* Possible alternate EFER values, depends on how the chip is wired */
#घोषणा CR_EFIR2		0x4e
#घोषणा CR_EFDR2		0x4f

/* Extended Function Mode enable/disable magic values */
#घोषणा EFER_EFM_ENABLE		0x87
#घोषणा EFER_EFM_DISABLE	0xaa

/* Config regs we need to care about */
#घोषणा CR_SOFTWARE_RESET	0x02
#घोषणा CR_LOGICAL_DEV_SEL	0x07
#घोषणा CR_CHIP_ID_HI		0x20
#घोषणा CR_CHIP_ID_LO		0x21
#घोषणा CR_DEV_POWER_DOWN	0x22 /* bit 2 is CIR घातer, शेष घातer on */
#घोषणा CR_OUTPUT_PIN_SEL	0x27
#घोषणा CR_MULTIFUNC_PIN_SEL	0x2c
#घोषणा CR_LOGICAL_DEV_EN	0x30 /* valid क्रम all logical devices */
/* next three regs valid क्रम both the CIR and CIR_WAKE logical devices */
#घोषणा CR_CIR_BASE_ADDR_HI	0x60
#घोषणा CR_CIR_BASE_ADDR_LO	0x61
#घोषणा CR_CIR_IRQ_RSRC		0x70
/* next three regs valid only क्रम ACPI logical dev */
#घोषणा CR_ACPI_CIR_WAKE	0xe0
#घोषणा CR_ACPI_IRQ_EVENTS	0xf6
#घोषणा CR_ACPI_IRQ_EVENTS2	0xf7

/* Logical devices that we need to care about */
#घोषणा LOGICAL_DEV_LPT		0x01
#घोषणा LOGICAL_DEV_CIR		0x06
#घोषणा LOGICAL_DEV_ACPI	0x0a
#घोषणा LOGICAL_DEV_CIR_WAKE	0x0e

#घोषणा LOGICAL_DEV_DISABLE	0x00
#घोषणा LOGICAL_DEV_ENABLE	0x01

#घोषणा CIR_WAKE_ENABLE_BIT	0x08
#घोषणा PME_INTR_CIR_PASS_BIT	0x08

/* w83677hg CIR pin config */
#घोषणा OUTPUT_PIN_SEL_MASK	0xbc
#घोषणा OUTPUT_ENABLE_CIR	0x01 /* Pin95=CIRRX, Pin96=CIRTX1 */
#घोषणा OUTPUT_ENABLE_CIRWB	0x40 /* enable wide-band sensor */

/* w83667hg CIR pin config */
#घोषणा MULTIFUNC_PIN_SEL_MASK	0x1f
#घोषणा MULTIFUNC_ENABLE_CIR	0x80 /* Pin75=CIRRX, Pin76=CIRTX1 */
#घोषणा MULTIFUNC_ENABLE_CIRWB	0x20 /* enable wide-band sensor */

/* MCE CIR संकेत length, related on sample period */

/* MCE CIR controller संकेत length: about 43ms
 * 43ms / 50us (sample period) * 0.85 (inaccuracy)
 */
#घोषणा CONTROLLER_BUF_LEN_MIN 830

/* MCE CIR keyboard संकेत length: about 26ms
 * 26ms / 50us (sample period) * 0.85 (inaccuracy)
 */
#घोषणा KEYBOARD_BUF_LEN_MAX 650
#घोषणा KEYBOARD_BUF_LEN_MIN 610

/* MCE CIR mouse संकेत length: about 24ms
 * 24ms / 50us (sample period) * 0.85 (inaccuracy)
 */
#घोषणा MOUSE_BUF_LEN_MIN 565

#घोषणा CIR_SAMPLE_PERIOD 50
#घोषणा CIR_SAMPLE_LOW_INACCURACY 0.85

/* MAX silence समय that driver will sent to lirc */
#घोषणा MAX_SILENCE_TIME 60000

#अगर CIR_IRCON_SAMPLE_PERIOD_SEL == CIR_IRCON_SAMPLE_PERIOD_SEL_100
#घोषणा SAMPLE_PERIOD 100

#या_अगर CIR_IRCON_SAMPLE_PERIOD_SEL == CIR_IRCON_SAMPLE_PERIOD_SEL_50
#घोषणा SAMPLE_PERIOD 50

#या_अगर CIR_IRCON_SAMPLE_PERIOD_SEL == CIR_IRCON_SAMPLE_PERIOD_SEL_25
#घोषणा SAMPLE_PERIOD 25

#अन्यथा
#घोषणा SAMPLE_PERIOD 1
#पूर्ण_अगर

/* as VISTA MCE definition, valid carrier value */
#घोषणा MAX_CARRIER 60000
#घोषणा MIN_CARRIER 30000

/* max wakeup sequence length */
#घोषणा WAKEUP_MAX_SIZE 65
