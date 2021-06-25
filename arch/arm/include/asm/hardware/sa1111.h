<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arch/arm/include/यंत्र/hardware/sa1111.h
 *
 * Copyright (C) 2000 John G Dorsey <john+@cs.cmu.edu>
 *
 * This file contains definitions क्रम the SA-1111 Companion Chip.
 * (Structure and naming borrowed from SA-1101.h, by Peter Danielsson.)
 *
 * Macro that calculates real address क्रम रेजिस्टरs in the SA-1111
 */

#अगर_अघोषित _ASM_ARCH_SA1111
#घोषणा _ASM_ARCH_SA1111

#समावेश <mach/bitfield.h>

/*
 * Don't ask the (SAC) DMA engines to move less than this amount.
 */

#घोषणा SA1111_SAC_DMA_MIN_XFER	(0x800)

/*
 * System Bus Interface (SBI)
 *
 * Registers
 *    SKCR	Control Register
 *    SMCR	Shared Memory Controller Register
 *    SKID	ID Register
 */
#घोषणा SA1111_SKCR	0x0000
#घोषणा SA1111_SMCR	0x0004
#घोषणा SA1111_SKID	0x0008

#घोषणा SKCR_PLL_BYPASS	(1<<0)
#घोषणा SKCR_RCLKEN	(1<<1)
#घोषणा SKCR_SLEEP	(1<<2)
#घोषणा SKCR_DOZE	(1<<3)
#घोषणा SKCR_VCO_OFF	(1<<4)
#घोषणा SKCR_SCANTSTEN	(1<<5)
#घोषणा SKCR_CLKTSTEN	(1<<6)
#घोषणा SKCR_RDYEN	(1<<7)
#घोषणा SKCR_SELAC	(1<<8)
#घोषणा SKCR_OPPC	(1<<9)
#घोषणा SKCR_PLLTSTEN	(1<<10)
#घोषणा SKCR_USBIOTSTEN	(1<<11)
/*
 * Don't believe the specs!  Take them, throw them outside.  Leave them
 * there क्रम a week.  Spit on them.  Walk on them.  Stamp on them.
 * Pour gasoline over them and finally burn them.  Now think about coding.
 *  - The October 1999 errata (278260-007) says its bit 13, 1 to enable.
 *  - The Feb 2001 errata (278260-010) says that the previous errata
 *    (278260-009) is wrong, and its bit actually 12, fixed in spec
 *    278242-003.
 *  - The SA1111 manual (278242) says bit 12, but 0 to enable.
 *  - Reality is bit 13, 1 to enable.
 *      -- rmk
 */
#घोषणा SKCR_OE_EN	(1<<13)

#घोषणा SMCR_DTIM	(1<<0)
#घोषणा SMCR_MBGE	(1<<1)
#घोषणा SMCR_DRAC_0	(1<<2)
#घोषणा SMCR_DRAC_1	(1<<3)
#घोषणा SMCR_DRAC_2	(1<<4)
#घोषणा SMCR_DRAC	Fld(3, 2)
#घोषणा SMCR_CLAT	(1<<5)

#घोषणा SKID_SIREV_MASK	(0x000000f0)
#घोषणा SKID_MTREV_MASK (0x0000000f)
#घोषणा SKID_ID_MASK	(0xffffff00)
#घोषणा SKID_SA1111_ID	(0x690cc200)

/*
 * System Controller
 *
 * Registers
 *    SKPCR	Power Control Register
 *    SKCDR	Clock Divider Register
 *    SKAUD	Audio Clock Divider Register
 *    SKPMC	PS/2 Mouse Clock Divider Register
 *    SKPTC	PS/2 Track Pad Clock Divider Register
 *    SKPEN0	PWM0 Enable Register
 *    SKPWM0	PWM0 Clock Register
 *    SKPEN1	PWM1 Enable Register
 *    SKPWM1	PWM1 Clock Register
 */
#घोषणा SA1111_SKPCR	0x0200
#घोषणा SA1111_SKCDR	0x0204
#घोषणा SA1111_SKAUD	0x0208
#घोषणा SA1111_SKPMC	0x020c
#घोषणा SA1111_SKPTC	0x0210
#घोषणा SA1111_SKPEN0	0x0214
#घोषणा SA1111_SKPWM0	0x0218
#घोषणा SA1111_SKPEN1	0x021c
#घोषणा SA1111_SKPWM1	0x0220

#घोषणा SKPCR_UCLKEN	(1<<0)
#घोषणा SKPCR_ACCLKEN	(1<<1)
#घोषणा SKPCR_I2SCLKEN	(1<<2)
#घोषणा SKPCR_L3CLKEN	(1<<3)
#घोषणा SKPCR_SCLKEN	(1<<4)
#घोषणा SKPCR_PMCLKEN	(1<<5)
#घोषणा SKPCR_PTCLKEN	(1<<6)
#घोषणा SKPCR_DCLKEN	(1<<7)
#घोषणा SKPCR_PWMCLKEN	(1<<8)

/* USB Host controller */
#घोषणा SA1111_USB		0x0400

/*
 * Serial Audio Controller
 *
 * Registers
 *    SACR0             Serial Audio Common Control Register
 *    SACR1             Serial Audio Alternate Mode (I2C/MSB) Control Register
 *    SACR2             Serial Audio AC-link Control Register
 *    SASR0             Serial Audio I2S/MSB Interface & FIFO Status Register
 *    SASR1             Serial Audio AC-link Interface & FIFO Status Register
 *    SASCR             Serial Audio Status Clear Register
 *    L3_CAR            L3 Control Bus Address Register
 *    L3_CDR            L3 Control Bus Data Register
 *    ACCAR             AC-link Command Address Register
 *    ACCDR             AC-link Command Data Register
 *    ACSAR             AC-link Status Address Register
 *    ACSDR             AC-link Status Data Register
 *    SADTCS            Serial Audio DMA Transmit Control/Status Register
 *    SADTSA            Serial Audio DMA Transmit Buffer Start Address A
 *    SADTCA            Serial Audio DMA Transmit Buffer Count Register A
 *    SADTSB            Serial Audio DMA Transmit Buffer Start Address B
 *    SADTCB            Serial Audio DMA Transmit Buffer Count Register B
 *    SADRCS            Serial Audio DMA Receive Control/Status Register
 *    SADRSA            Serial Audio DMA Receive Buffer Start Address A
 *    SADRCA            Serial Audio DMA Receive Buffer Count Register A
 *    SADRSB            Serial Audio DMA Receive Buffer Start Address B
 *    SADRCB            Serial Audio DMA Receive Buffer Count Register B
 *    SAITR             Serial Audio Interrupt Test Register
 *    SADR              Serial Audio Data Register (16 x 32-bit)
 */

#घोषणा SA1111_SERAUDIO		0x0600

/*
 * These are offsets from the above base.
 */
#घोषणा SA1111_SACR0		0x00
#घोषणा SA1111_SACR1		0x04
#घोषणा SA1111_SACR2		0x08
#घोषणा SA1111_SASR0		0x0c
#घोषणा SA1111_SASR1		0x10
#घोषणा SA1111_SASCR		0x18
#घोषणा SA1111_L3_CAR		0x1c
#घोषणा SA1111_L3_CDR		0x20
#घोषणा SA1111_ACCAR		0x24
#घोषणा SA1111_ACCDR		0x28
#घोषणा SA1111_ACSAR		0x2c
#घोषणा SA1111_ACSDR		0x30
#घोषणा SA1111_SADTCS		0x34
#घोषणा SA1111_SADTSA		0x38
#घोषणा SA1111_SADTCA		0x3c
#घोषणा SA1111_SADTSB		0x40
#घोषणा SA1111_SADTCB		0x44
#घोषणा SA1111_SADRCS		0x48
#घोषणा SA1111_SADRSA		0x4c
#घोषणा SA1111_SADRCA		0x50
#घोषणा SA1111_SADRSB		0x54
#घोषणा SA1111_SADRCB		0x58
#घोषणा SA1111_SAITR		0x5c
#घोषणा SA1111_SADR		0x80

#अगर_अघोषित CONFIG_ARCH_PXA

#घोषणा SACR0_ENB	(1<<0)
#घोषणा SACR0_BCKD	(1<<2)
#घोषणा SACR0_RST	(1<<3)

#घोषणा SACR1_AMSL	(1<<0)
#घोषणा SACR1_L3EN	(1<<1)
#घोषणा SACR1_L3MB	(1<<2)
#घोषणा SACR1_DREC	(1<<3)
#घोषणा SACR1_DRPL	(1<<4)
#घोषणा SACR1_ENLBF	(1<<5)

#घोषणा SACR2_TS3V	(1<<0)
#घोषणा SACR2_TS4V	(1<<1)
#घोषणा SACR2_WKUP	(1<<2)
#घोषणा SACR2_DREC	(1<<3)
#घोषणा SACR2_DRPL	(1<<4)
#घोषणा SACR2_ENLBF	(1<<5)
#घोषणा SACR2_RESET	(1<<6)

#घोषणा SASR0_TNF	(1<<0)
#घोषणा SASR0_RNE	(1<<1)
#घोषणा SASR0_BSY	(1<<2)
#घोषणा SASR0_TFS	(1<<3)
#घोषणा SASR0_RFS	(1<<4)
#घोषणा SASR0_TUR	(1<<5)
#घोषणा SASR0_ROR	(1<<6)
#घोषणा SASR0_L3WD	(1<<16)
#घोषणा SASR0_L3RD	(1<<17)

#घोषणा SASR1_TNF	(1<<0)
#घोषणा SASR1_RNE	(1<<1)
#घोषणा SASR1_BSY	(1<<2)
#घोषणा SASR1_TFS	(1<<3)
#घोषणा SASR1_RFS	(1<<4)
#घोषणा SASR1_TUR	(1<<5)
#घोषणा SASR1_ROR	(1<<6)
#घोषणा SASR1_CADT	(1<<16)
#घोषणा SASR1_SADR	(1<<17)
#घोषणा SASR1_RSTO	(1<<18)
#घोषणा SASR1_CLPM	(1<<19)
#घोषणा SASR1_CRDY	(1<<20)
#घोषणा SASR1_RS3V	(1<<21)
#घोषणा SASR1_RS4V	(1<<22)

#घोषणा SASCR_TUR	(1<<5)
#घोषणा SASCR_ROR	(1<<6)
#घोषणा SASCR_DTS	(1<<16)
#घोषणा SASCR_RDD	(1<<17)
#घोषणा SASCR_STO	(1<<18)

#घोषणा SADTCS_TDEN	(1<<0)
#घोषणा SADTCS_TDIE	(1<<1)
#घोषणा SADTCS_TDBDA	(1<<3)
#घोषणा SADTCS_TDSTA	(1<<4)
#घोषणा SADTCS_TDBDB	(1<<5)
#घोषणा SADTCS_TDSTB	(1<<6)
#घोषणा SADTCS_TBIU	(1<<7)

#घोषणा SADRCS_RDEN	(1<<0)
#घोषणा SADRCS_RDIE	(1<<1)
#घोषणा SADRCS_RDBDA	(1<<3)
#घोषणा SADRCS_RDSTA	(1<<4)
#घोषणा SADRCS_RDBDB	(1<<5)
#घोषणा SADRCS_RDSTB	(1<<6)
#घोषणा SADRCS_RBIU	(1<<7)

#घोषणा SAD_CS_DEN	(1<<0)
#घोषणा SAD_CS_DIE	(1<<1)	/* Not functional on metal 1 */
#घोषणा SAD_CS_DBDA	(1<<3)	/* Not functional on metal 1 */
#घोषणा SAD_CS_DSTA	(1<<4)
#घोषणा SAD_CS_DBDB	(1<<5)	/* Not functional on metal 1 */
#घोषणा SAD_CS_DSTB	(1<<6)
#घोषणा SAD_CS_BIU	(1<<7)	/* Not functional on metal 1 */

#घोषणा SAITR_TFS	(1<<0)
#घोषणा SAITR_RFS	(1<<1)
#घोषणा SAITR_TUR	(1<<2)
#घोषणा SAITR_ROR	(1<<3)
#घोषणा SAITR_CADT	(1<<4)
#घोषणा SAITR_SADR	(1<<5)
#घोषणा SAITR_RSTO	(1<<6)
#घोषणा SAITR_TDBDA	(1<<8)
#घोषणा SAITR_TDBDB	(1<<9)
#घोषणा SAITR_RDBDA	(1<<10)
#घोषणा SAITR_RDBDB	(1<<11)

#पूर्ण_अगर  /* !CONFIG_ARCH_PXA */

/*
 * General-Purpose I/O Interface
 *
 * Registers
 *    PA_DDR		GPIO Block A Data Direction
 *    PA_DRR/PA_DWR	GPIO Block A Data Value Register (पढ़ो/ग_लिखो)
 *    PA_SDR		GPIO Block A Sleep Direction
 *    PA_SSR		GPIO Block A Sleep State
 *    PB_DDR		GPIO Block B Data Direction
 *    PB_DRR/PB_DWR	GPIO Block B Data Value Register (पढ़ो/ग_लिखो)
 *    PB_SDR		GPIO Block B Sleep Direction
 *    PB_SSR		GPIO Block B Sleep State
 *    PC_DDR		GPIO Block C Data Direction
 *    PC_DRR/PC_DWR	GPIO Block C Data Value Register (पढ़ो/ग_लिखो)
 *    PC_SDR		GPIO Block C Sleep Direction
 *    PC_SSR		GPIO Block C Sleep State
 */

#घोषणा SA1111_GPIO	0x1000

#घोषणा SA1111_GPIO_PADDR	(0x000)
#घोषणा SA1111_GPIO_PADRR	(0x004)
#घोषणा SA1111_GPIO_PADWR	(0x004)
#घोषणा SA1111_GPIO_PASDR	(0x008)
#घोषणा SA1111_GPIO_PASSR	(0x00c)
#घोषणा SA1111_GPIO_PBDDR	(0x010)
#घोषणा SA1111_GPIO_PBDRR	(0x014)
#घोषणा SA1111_GPIO_PBDWR	(0x014)
#घोषणा SA1111_GPIO_PBSDR	(0x018)
#घोषणा SA1111_GPIO_PBSSR	(0x01c)
#घोषणा SA1111_GPIO_PCDDR	(0x020)
#घोषणा SA1111_GPIO_PCDRR	(0x024)
#घोषणा SA1111_GPIO_PCDWR	(0x024)
#घोषणा SA1111_GPIO_PCSDR	(0x028)
#घोषणा SA1111_GPIO_PCSSR	(0x02c)

#घोषणा GPIO_A0		(1 << 0)
#घोषणा GPIO_A1		(1 << 1)
#घोषणा GPIO_A2		(1 << 2)
#घोषणा GPIO_A3		(1 << 3)

#घोषणा GPIO_B0		(1 << 8)
#घोषणा GPIO_B1		(1 << 9)
#घोषणा GPIO_B2		(1 << 10)
#घोषणा GPIO_B3		(1 << 11)
#घोषणा GPIO_B4		(1 << 12)
#घोषणा GPIO_B5		(1 << 13)
#घोषणा GPIO_B6		(1 << 14)
#घोषणा GPIO_B7		(1 << 15)

#घोषणा GPIO_C0		(1 << 16)
#घोषणा GPIO_C1		(1 << 17)
#घोषणा GPIO_C2		(1 << 18)
#घोषणा GPIO_C3		(1 << 19)
#घोषणा GPIO_C4		(1 << 20)
#घोषणा GPIO_C5		(1 << 21)
#घोषणा GPIO_C6		(1 << 22)
#घोषणा GPIO_C7		(1 << 23)

/*
 * Interrupt Controller
 *
 * Registers
 *    INTTEST0		Test रेजिस्टर 0
 *    INTTEST1		Test रेजिस्टर 1
 *    INTEN0		Interrupt Enable रेजिस्टर 0
 *    INTEN1		Interrupt Enable रेजिस्टर 1
 *    INTPOL0		Interrupt Polarity selection 0
 *    INTPOL1		Interrupt Polarity selection 1
 *    INTTSTSEL		Interrupt source selection
 *    INTSTATCLR0	Interrupt Status/Clear 0
 *    INTSTATCLR1	Interrupt Status/Clear 1
 *    INTSET0		Interrupt source set 0
 *    INTSET1		Interrupt source set 1
 *    WAKE_EN0		Wake-up source enable 0
 *    WAKE_EN1		Wake-up source enable 1
 *    WAKE_POL0		Wake-up polarity selection 0
 *    WAKE_POL1		Wake-up polarity selection 1
 */
#घोषणा SA1111_INTC		0x1600

/*
 * These are offsets from the above base.
 */
#घोषणा SA1111_INTTEST0		0x0000
#घोषणा SA1111_INTTEST1		0x0004
#घोषणा SA1111_INTEN0		0x0008
#घोषणा SA1111_INTEN1		0x000c
#घोषणा SA1111_INTPOL0		0x0010
#घोषणा SA1111_INTPOL1		0x0014
#घोषणा SA1111_INTTSTSEL	0x0018
#घोषणा SA1111_INTSTATCLR0	0x001c
#घोषणा SA1111_INTSTATCLR1	0x0020
#घोषणा SA1111_INTSET0		0x0024
#घोषणा SA1111_INTSET1		0x0028
#घोषणा SA1111_WAKEEN0		0x002c
#घोषणा SA1111_WAKEEN1		0x0030
#घोषणा SA1111_WAKEPOL0		0x0034
#घोषणा SA1111_WAKEPOL1		0x0038

/* PS/2 Trackpad and Mouse Interfaces */
#घोषणा SA1111_KBD		0x0a00
#घोषणा SA1111_MSE		0x0c00

/* PCMCIA Interface */
#घोषणा SA1111_PCMCIA		0x1600





बाह्य काष्ठा bus_type sa1111_bus_type;

#घोषणा SA1111_DEVID_SBI	(1 << 0)
#घोषणा SA1111_DEVID_SK		(1 << 1)
#घोषणा SA1111_DEVID_USB	(1 << 2)
#घोषणा SA1111_DEVID_SAC	(1 << 3)
#घोषणा SA1111_DEVID_SSP	(1 << 4)
#घोषणा SA1111_DEVID_PS2	(3 << 5)
#घोषणा SA1111_DEVID_PS2_KBD	(1 << 5)
#घोषणा SA1111_DEVID_PS2_MSE	(1 << 6)
#घोषणा SA1111_DEVID_GPIO	(1 << 7)
#घोषणा SA1111_DEVID_INT	(1 << 8)
#घोषणा SA1111_DEVID_PCMCIA	(1 << 9)

काष्ठा sa1111_dev अणु
	काष्ठा device	dev;
	अचिन्हित पूर्णांक	devid;
	काष्ठा resource	res;
	व्योम __iomem	*mapbase;
	अचिन्हित पूर्णांक	skpcr_mask;
	अचिन्हित पूर्णांक	hwirq[6];
	u64		dma_mask;
पूर्ण;

#घोषणा to_sa1111_device(x)	container_of(x, काष्ठा sa1111_dev, dev)

#घोषणा sa1111_get_drvdata(d)	dev_get_drvdata(&(d)->dev)
#घोषणा sa1111_set_drvdata(d,p)	dev_set_drvdata(&(d)->dev, p)

काष्ठा sa1111_driver अणु
	काष्ठा device_driver	drv;
	अचिन्हित पूर्णांक		devid;
	पूर्णांक (*probe)(काष्ठा sa1111_dev *);
	व्योम (*हटाओ)(काष्ठा sa1111_dev *);
पूर्ण;

#घोषणा SA1111_DRV(_d)	container_of((_d), काष्ठा sa1111_driver, drv)

#घोषणा SA1111_DRIVER_NAME(_sadev) ((_sadev)->dev.driver->name)

/*
 * These frob the SKPCR रेजिस्टर, and call platक्रमm specअगरic
 * enable/disable functions.
 */
पूर्णांक sa1111_enable_device(काष्ठा sa1111_dev *);
व्योम sa1111_disable_device(काष्ठा sa1111_dev *);

पूर्णांक sa1111_get_irq(काष्ठा sa1111_dev *, अचिन्हित num);

अचिन्हित पूर्णांक sa1111_pll_घड़ी(काष्ठा sa1111_dev *);

#घोषणा SA1111_AUDIO_ACLINK	0
#घोषणा SA1111_AUDIO_I2S	1

व्योम sa1111_select_audio_mode(काष्ठा sa1111_dev *sadev, पूर्णांक mode);
पूर्णांक sa1111_set_audio_rate(काष्ठा sa1111_dev *sadev, पूर्णांक rate);
पूर्णांक sa1111_get_audio_rate(काष्ठा sa1111_dev *sadev);

पूर्णांक sa1111_check_dma_bug(dma_addr_t addr);

पूर्णांक sa1111_driver_रेजिस्टर(काष्ठा sa1111_driver *);
व्योम sa1111_driver_unरेजिस्टर(काष्ठा sa1111_driver *);

काष्ठा sa1111_platक्रमm_data अणु
	पूर्णांक	irq_base;	/* base क्रम cascaded on-chip IRQs */
	अचिन्हित disable_devs;
	व्योम	*data;
	पूर्णांक	(*enable)(व्योम *, अचिन्हित);
	व्योम	(*disable)(व्योम *, अचिन्हित);
पूर्ण;

#पूर्ण_अगर  /* _ASM_ARCH_SA1111 */
