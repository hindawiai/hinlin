<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MACH_SDK7786_FPGA_H
#घोषणा __MACH_SDK7786_FPGA_H

#समावेश <linux/पन.स>
#समावेश <linux/types.h>
#समावेश <linux/bitops.h>

#घोषणा SRSTR		0x000
#घोषणा  SRSTR_MAGIC	0x1971	/* Fixed magical पढ़ो value */

#घोषणा INTASR		0x010
#घोषणा INTAMR		0x020
#घोषणा MODSWR		0x030
#घोषणा INTTESTR	0x040
#घोषणा SYSSR		0x050
#घोषणा NRGPR		0x060

#घोषणा NMISR		0x070
#घोषणा  NMISR_MAN_NMI	BIT(0)
#घोषणा  NMISR_AUX_NMI	BIT(1)
#घोषणा  NMISR_MASK	(NMISR_MAN_NMI | NMISR_AUX_NMI)

#घोषणा NMIMR		0x080
#घोषणा  NMIMR_MAN_NMIM	BIT(0)	/* Manual NMI mask */
#घोषणा  NMIMR_AUX_NMIM	BIT(1)	/* Auxiliary NMI mask */
#घोषणा  NMIMR_MASK	(NMIMR_MAN_NMIM | NMIMR_AUX_NMIM)

#घोषणा INTBSR		0x090
#घोषणा INTBMR		0x0a0
#घोषणा USRLEDR		0x0b0
#घोषणा MAPSWR		0x0c0
#घोषणा FPGAVR		0x0d0
#घोषणा FPGADR		0x0e0
#घोषणा PCBRR		0x0f0
#घोषणा RSR		0x100
#घोषणा EXTASR		0x110
#घोषणा SPCAR		0x120
#घोषणा INTMSR		0x130

#घोषणा PCIECR		0x140
#घोषणा  PCIECR_PCIEMUX1	BIT(15)
#घोषणा  PCIECR_PCIEMUX0	BIT(14)
#घोषणा  PCIECR_PRST4		BIT(12) /* slot 4 card present */
#घोषणा  PCIECR_PRST3		BIT(11) /* slot 3 card present */
#घोषणा  PCIECR_PRST2		BIT(10) /* slot 2 card present */
#घोषणा  PCIECR_PRST1		BIT(9)  /* slot 1 card present */
#घोषणा  PCIECR_CLKEN		BIT(4)	/* oscillator enable */

#घोषणा FAER		0x150
#घोषणा USRGPIR		0x160

/* 0x170 reserved */

#घोषणा LCLASR			0x180
#घोषणा  LCLASR_FRAMEN		BIT(15)

#घोषणा  LCLASR_FPGA_SEL_SHIFT	12
#घोषणा  LCLASR_न_अंकD_SEL_SHIFT	8
#घोषणा  LCLASR_NORB_SEL_SHIFT	4
#घोषणा  LCLASR_NORA_SEL_SHIFT	0

#घोषणा  LCLASR_AREA_MASK	0x7

#घोषणा  LCLASR_FPGA_SEL_MASK	(LCLASR_AREA_MASK << LCLASR_FPGA_SEL_SHIFT)
#घोषणा  LCLASR_न_अंकD_SEL_MASK	(LCLASR_AREA_MASK << LCLASR_न_अंकD_SEL_SHIFT)
#घोषणा  LCLASR_NORB_SEL_MASK	(LCLASR_AREA_MASK << LCLASR_NORB_SEL_SHIFT)
#घोषणा  LCLASR_NORA_SEL_MASK	(LCLASR_AREA_MASK << LCLASR_NORA_SEL_SHIFT)

#घोषणा SBCR		0x190
#घोषणा  SCBR_I2CMEN	BIT(0)	/* FPGA I2C master enable */
#घोषणा  SCBR_I2CCEN	BIT(1)	/* CPU I2C master enable */

#घोषणा PWRCR		0x1a0
#घोषणा  PWRCR_SCISEL0	BIT(0)
#घोषणा  PWRCR_SCISEL1	BIT(1)
#घोषणा  PWRCR_SCIEN	BIT(2)	/* Serial port enable */
#घोषणा  PWRCR_PDWNACK	BIT(5)	/* Power करोwn acknowledge */
#घोषणा  PWRCR_PDWNREQ	BIT(7)	/* Power करोwn request */
#घोषणा  PWRCR_INT2	BIT(11)	/* INT2 connection to घातer manager */
#घोषणा  PWRCR_BUPINIT	BIT(13)	/* DDR backup initialize */
#घोषणा  PWRCR_BKPRST	BIT(15) /* Backup घातer reset */

#घोषणा SPCBR		0x1b0
#घोषणा SPICR		0x1c0
#घोषणा SPIDR		0x1d0
#घोषणा I2CCR		0x1e0
#घोषणा I2CDR		0x1f0
#घोषणा FPGACR		0x200
#घोषणा IASELR1		0x210
#घोषणा IASELR2		0x220
#घोषणा IASELR3		0x230
#घोषणा IASELR4		0x240
#घोषणा IASELR5		0x250
#घोषणा IASELR6		0x260
#घोषणा IASELR7		0x270
#घोषणा IASELR8		0x280
#घोषणा IASELR9		0x290
#घोषणा IASELR10	0x2a0
#घोषणा IASELR11	0x2b0
#घोषणा IASELR12	0x2c0
#घोषणा IASELR13	0x2d0
#घोषणा IASELR14	0x2e0
#घोषणा IASELR15	0x2f0
/* 0x300 reserved */
#घोषणा IBSELR1		0x310
#घोषणा IBSELR2		0x320
#घोषणा IBSELR3		0x330
#घोषणा IBSELR4		0x340
#घोषणा IBSELR5		0x350
#घोषणा IBSELR6		0x360
#घोषणा IBSELR7		0x370
#घोषणा IBSELR8		0x380
#घोषणा IBSELR9		0x390
#घोषणा IBSELR10	0x3a0
#घोषणा IBSELR11	0x3b0
#घोषणा IBSELR12	0x3c0
#घोषणा IBSELR13	0x3d0
#घोषणा IBSELR14	0x3e0
#घोषणा IBSELR15	0x3f0
#घोषणा USRACR		0x400
#घोषणा BEEPR		0x410
#घोषणा USRLCDR		0x420
#घोषणा SMBCR		0x430
#घोषणा SMBDR		0x440
#घोषणा USBCR		0x450
#घोषणा AMSR		0x460
#घोषणा ACCR		0x470
#घोषणा SDIFCR		0x480

/* arch/sh/boards/mach-sdk7786/fpga.c */
बाह्य व्योम __iomem *sdk7786_fpga_base;
बाह्य व्योम sdk7786_fpga_init(व्योम);

/* arch/sh/boards/mach-sdk7786/nmi.c */
बाह्य व्योम sdk7786_nmi_init(व्योम);

#घोषणा SDK7786_FPGA_REGADDR(reg)	(sdk7786_fpga_base + (reg))

/*
 * A convenience wrapper from रेजिस्टर offset to पूर्णांकernal I2C address,
 * when the FPGA is in I2C slave mode.
 */
#घोषणा SDK7786_FPGA_I2CADDR(reg)	((reg) >> 3)

अटल अंतरभूत u16 fpga_पढ़ो_reg(अचिन्हित पूर्णांक reg)
अणु
	वापस ioपढ़ो16(sdk7786_fpga_base + reg);
पूर्ण

अटल अंतरभूत व्योम fpga_ग_लिखो_reg(u16 val, अचिन्हित पूर्णांक reg)
अणु
	ioग_लिखो16(val, sdk7786_fpga_base + reg);
पूर्ण

#पूर्ण_अगर /* __MACH_SDK7786_FPGA_H */
