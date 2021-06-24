<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Intel IOP32X and IOP33X रेजिस्टर definitions
 *
 * Author: Rory Bolt <rorybolt@pacbell.net>
 * Copyright (C) 2002 Rory Bolt
 * Copyright (C) 2004 Intel Corp.
 */

#अगर_अघोषित __IOP3XX_H
#घोषणा __IOP3XX_H

/*
 * Peripherals that are shared between the iop32x and iop33x but
 * located at dअगरferent addresses.
 */
#घोषणा IOP3XX_TIMER_REG(reg)	(IOP3XX_PERIPHERAL_VIRT_BASE + 0x07e0 + (reg))

#समावेश "iop3xx.h"

/* ATU Parameters
 * set up a 1:1 bus to physical ram relationship
 * w/ physical ram on top of pci in the memory map
 */
#घोषणा IOP32X_MAX_RAM_SIZE            0x40000000UL
#घोषणा IOP3XX_MAX_RAM_SIZE            IOP32X_MAX_RAM_SIZE
#घोषणा IOP3XX_PCI_LOWER_MEM_BA        0x80000000

/*
 * IOP3XX GPIO handling
 */
#घोषणा IOP3XX_GPIO_LINE(x)	(x)

#अगर_अघोषित __ASSEMBLY__
बाह्य पूर्णांक init_atu;
बाह्य पूर्णांक iop3xx_get_init_atu(व्योम);
#पूर्ण_अगर


/*
 * IOP3XX processor रेजिस्टरs
 */
#घोषणा IOP3XX_PERIPHERAL_PHYS_BASE	0xffffe000
#घोषणा IOP3XX_PERIPHERAL_VIRT_BASE	0xfedfe000
#घोषणा IOP3XX_PERIPHERAL_SIZE		0x00002000
#घोषणा IOP3XX_PERIPHERAL_UPPER_PA (IOP3XX_PERIPHERAL_PHYS_BASE +\
					IOP3XX_PERIPHERAL_SIZE - 1)
#घोषणा IOP3XX_PERIPHERAL_UPPER_VA (IOP3XX_PERIPHERAL_VIRT_BASE +\
					IOP3XX_PERIPHERAL_SIZE - 1)
#घोषणा IOP3XX_PMMR_PHYS_TO_VIRT(addr) (u32) ((u32) (addr) -\
					(IOP3XX_PERIPHERAL_PHYS_BASE\
					- IOP3XX_PERIPHERAL_VIRT_BASE))
#घोषणा IOP3XX_REG_ADDR(reg)		(IOP3XX_PERIPHERAL_VIRT_BASE + (reg))

/* Address Translation Unit  */
#घोषणा IOP3XX_ATUVID		(अस्थिर u16 *)IOP3XX_REG_ADDR(0x0100)
#घोषणा IOP3XX_ATUDID		(अस्थिर u16 *)IOP3XX_REG_ADDR(0x0102)
#घोषणा IOP3XX_ATUCMD		(अस्थिर u16 *)IOP3XX_REG_ADDR(0x0104)
#घोषणा IOP3XX_ATUSR		(अस्थिर u16 *)IOP3XX_REG_ADDR(0x0106)
#घोषणा IOP3XX_ATURID		(अस्थिर u8  *)IOP3XX_REG_ADDR(0x0108)
#घोषणा IOP3XX_ATUCCR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0109)
#घोषणा IOP3XX_ATUCLSR		(अस्थिर u8  *)IOP3XX_REG_ADDR(0x010c)
#घोषणा IOP3XX_ATULT		(अस्थिर u8  *)IOP3XX_REG_ADDR(0x010d)
#घोषणा IOP3XX_ATUHTR		(अस्थिर u8  *)IOP3XX_REG_ADDR(0x010e)
#घोषणा IOP3XX_ATUBIST		(अस्थिर u8  *)IOP3XX_REG_ADDR(0x010f)
#घोषणा IOP3XX_IABAR0		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0110)
#घोषणा IOP3XX_IAUBAR0		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0114)
#घोषणा IOP3XX_IABAR1		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0118)
#घोषणा IOP3XX_IAUBAR1		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x011c)
#घोषणा IOP3XX_IABAR2		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0120)
#घोषणा IOP3XX_IAUBAR2		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0124)
#घोषणा IOP3XX_ASVIR		(अस्थिर u16 *)IOP3XX_REG_ADDR(0x012c)
#घोषणा IOP3XX_ASIR		(अस्थिर u16 *)IOP3XX_REG_ADDR(0x012e)
#घोषणा IOP3XX_ERBAR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0130)
#घोषणा IOP3XX_ATUILR		(अस्थिर u8  *)IOP3XX_REG_ADDR(0x013c)
#घोषणा IOP3XX_ATUIPR		(अस्थिर u8  *)IOP3XX_REG_ADDR(0x013d)
#घोषणा IOP3XX_ATUMGNT		(अस्थिर u8  *)IOP3XX_REG_ADDR(0x013e)
#घोषणा IOP3XX_ATUMLAT		(अस्थिर u8  *)IOP3XX_REG_ADDR(0x013f)
#घोषणा IOP3XX_IALR0		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0140)
#घोषणा IOP3XX_IATVR0		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0144)
#घोषणा IOP3XX_ERLR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0148)
#घोषणा IOP3XX_ERTVR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x014c)
#घोषणा IOP3XX_IALR1		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0150)
#घोषणा IOP3XX_IALR2		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0154)
#घोषणा IOP3XX_IATVR2		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0158)
#घोषणा IOP3XX_OIOWTVR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x015c)
#घोषणा IOP3XX_OMWTVR0		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0160)
#घोषणा IOP3XX_OUMWTVR0		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0164)
#घोषणा IOP3XX_OMWTVR1		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0168)
#घोषणा IOP3XX_OUMWTVR1		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x016c)
#घोषणा IOP3XX_OUDWTVR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0178)
#घोषणा IOP3XX_ATUCR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0180)
#घोषणा IOP3XX_PCSR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0184)
#घोषणा IOP3XX_ATUISR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0188)
#घोषणा IOP3XX_ATUIMR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x018c)
#घोषणा IOP3XX_IABAR3		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0190)
#घोषणा IOP3XX_IAUBAR3		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0194)
#घोषणा IOP3XX_IALR3		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0198)
#घोषणा IOP3XX_IATVR3		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x019c)
#घोषणा IOP3XX_OCCAR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x01a4)
#घोषणा IOP3XX_OCCDR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x01ac)
#घोषणा IOP3XX_PDSCR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x01bc)
#घोषणा IOP3XX_PMCAPID		(अस्थिर u8  *)IOP3XX_REG_ADDR(0x01c0)
#घोषणा IOP3XX_PMNEXT		(अस्थिर u8  *)IOP3XX_REG_ADDR(0x01c1)
#घोषणा IOP3XX_APMCR		(अस्थिर u16 *)IOP3XX_REG_ADDR(0x01c2)
#घोषणा IOP3XX_APMCSR		(अस्थिर u16 *)IOP3XX_REG_ADDR(0x01c4)
#घोषणा IOP3XX_PCIXCAPID	(अस्थिर u8  *)IOP3XX_REG_ADDR(0x01e0)
#घोषणा IOP3XX_PCIXNEXT		(अस्थिर u8  *)IOP3XX_REG_ADDR(0x01e1)
#घोषणा IOP3XX_PCIXCMD		(अस्थिर u16 *)IOP3XX_REG_ADDR(0x01e2)
#घोषणा IOP3XX_PCIXSR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x01e4)
#घोषणा IOP3XX_PCIIRSR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x01ec)
#घोषणा IOP3XX_PCSR_OUT_Q_BUSY (1 << 15)
#घोषणा IOP3XX_PCSR_IN_Q_BUSY	(1 << 14)
#घोषणा IOP3XX_ATUCR_OUT_EN	(1 << 1)

#घोषणा IOP3XX_INIT_ATU_DEFAULT 0
#घोषणा IOP3XX_INIT_ATU_DISABLE -1
#घोषणा IOP3XX_INIT_ATU_ENABLE	 1

/* Messaging Unit  */
#घोषणा IOP3XX_IMR0		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0310)
#घोषणा IOP3XX_IMR1		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0314)
#घोषणा IOP3XX_OMR0		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0318)
#घोषणा IOP3XX_OMR1		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x031c)
#घोषणा IOP3XX_IDR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0320)
#घोषणा IOP3XX_IISR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0324)
#घोषणा IOP3XX_IIMR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0328)
#घोषणा IOP3XX_ODR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x032c)
#घोषणा IOP3XX_OISR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0330)
#घोषणा IOP3XX_OIMR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0334)
#घोषणा IOP3XX_MUCR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0350)
#घोषणा IOP3XX_QBAR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0354)
#घोषणा IOP3XX_IFHPR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0360)
#घोषणा IOP3XX_IFTPR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0364)
#घोषणा IOP3XX_IPHPR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0368)
#घोषणा IOP3XX_IPTPR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x036c)
#घोषणा IOP3XX_OFHPR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0370)
#घोषणा IOP3XX_OFTPR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0374)
#घोषणा IOP3XX_OPHPR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0378)
#घोषणा IOP3XX_OPTPR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x037c)
#घोषणा IOP3XX_IAR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0380)

/* DMA Controller  */
#घोषणा IOP3XX_DMA_PHYS_BASE(chan) (IOP3XX_PERIPHERAL_PHYS_BASE + \
					(0x400 + (chan << 6)))
#घोषणा IOP3XX_DMA_UPPER_PA(chan)  (IOP3XX_DMA_PHYS_BASE(chan) + 0x27)

/* Peripheral bus पूर्णांकerface  */
#घोषणा IOP3XX_PBCR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0680)
#घोषणा IOP3XX_PBISR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0684)
#घोषणा IOP3XX_PBBAR0		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0688)
#घोषणा IOP3XX_PBLR0		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x068c)
#घोषणा IOP3XX_PBBAR1		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0690)
#घोषणा IOP3XX_PBLR1		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0694)
#घोषणा IOP3XX_PBBAR2		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0698)
#घोषणा IOP3XX_PBLR2		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x069c)
#घोषणा IOP3XX_PBBAR3		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x06a0)
#घोषणा IOP3XX_PBLR3		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x06a4)
#घोषणा IOP3XX_PBBAR4		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x06a8)
#घोषणा IOP3XX_PBLR4		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x06ac)
#घोषणा IOP3XX_PBBAR5		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x06b0)
#घोषणा IOP3XX_PBLR5		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x06b4)
#घोषणा IOP3XX_PMBR0		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x06c0)
#घोषणा IOP3XX_PMBR1		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x06e0)
#घोषणा IOP3XX_PMBR2		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x06e4)

/* Peripheral perक्रमmance monitoring unit  */
#घोषणा IOP3XX_GTMR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0700)
#घोषणा IOP3XX_ESR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0704)
#घोषणा IOP3XX_EMISR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0708)
#घोषणा IOP3XX_GTSR		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0710)
/* PERCR0 DOESN'T EXIST - index from 1! */
#घोषणा IOP3XX_PERCR0		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x0710)

/* Timers  */
#घोषणा IOP3XX_TU_TMR0		(अस्थिर u32 *)IOP3XX_TIMER_REG(0x0000)
#घोषणा IOP3XX_TU_TMR1		(अस्थिर u32 *)IOP3XX_TIMER_REG(0x0004)
#घोषणा IOP3XX_TU_TCR0		(अस्थिर u32 *)IOP3XX_TIMER_REG(0x0008)
#घोषणा IOP3XX_TU_TCR1		(अस्थिर u32 *)IOP3XX_TIMER_REG(0x000c)
#घोषणा IOP3XX_TU_TRR0		(अस्थिर u32 *)IOP3XX_TIMER_REG(0x0010)
#घोषणा IOP3XX_TU_TRR1		(अस्थिर u32 *)IOP3XX_TIMER_REG(0x0014)
#घोषणा IOP3XX_TU_TISR		(अस्थिर u32 *)IOP3XX_TIMER_REG(0x0018)
#घोषणा IOP3XX_TU_WDTCR		(अस्थिर u32 *)IOP3XX_TIMER_REG(0x001c)
#घोषणा IOP_TMR_EN	    0x02
#घोषणा IOP_TMR_RELOAD	    0x04
#घोषणा IOP_TMR_PRIVILEGED 0x08
#घोषणा IOP_TMR_RATIO_1_1  0x00

/* Watchकरोg समयr definitions */
#घोषणा IOP_WDTCR_EN_ARM        0x1e1e1e1e
#घोषणा IOP_WDTCR_EN            0xe1e1e1e1
/* iop3xx करोes not support stopping the watchकरोg, so we just re-arm */
#घोषणा IOP_WDTCR_DIS_ARM	(IOP_WDTCR_EN_ARM)
#घोषणा IOP_WDTCR_DIS		(IOP_WDTCR_EN)

/* Application accelerator unit  */
#घोषणा IOP3XX_AAU_PHYS_BASE (IOP3XX_PERIPHERAL_PHYS_BASE + 0x800)
#घोषणा IOP3XX_AAU_UPPER_PA (IOP3XX_AAU_PHYS_BASE + 0xa7)

/* I2C bus पूर्णांकerface unit  */
#घोषणा IOP3XX_ICR0		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x1680)
#घोषणा IOP3XX_ISR0		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x1684)
#घोषणा IOP3XX_ISAR0		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x1688)
#घोषणा IOP3XX_IDBR0		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x168c)
#घोषणा IOP3XX_IBMR0		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x1694)
#घोषणा IOP3XX_ICR1		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x16a0)
#घोषणा IOP3XX_ISR1		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x16a4)
#घोषणा IOP3XX_ISAR1		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x16a8)
#घोषणा IOP3XX_IDBR1		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x16ac)
#घोषणा IOP3XX_IBMR1		(अस्थिर u32 *)IOP3XX_REG_ADDR(0x16b4)


/*
 * IOP3XX I/O and Mem space regions क्रम PCI स्वतःconfiguration
 */
#घोषणा IOP3XX_PCI_LOWER_MEM_PA	0x80000000
#घोषणा IOP3XX_PCI_MEM_WINDOW_SIZE	0x08000000

#घोषणा IOP3XX_PCI_LOWER_IO_PA		0x90000000
#घोषणा IOP3XX_PCI_LOWER_IO_BA		0x00000000

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>
#समावेश <linux/reboot.h>

व्योम iop3xx_map_io(व्योम);
व्योम iop_init_cp6_handler(व्योम);
व्योम iop_init_समय(अचिन्हित दीर्घ tickrate);
व्योम iop3xx_restart(क्रमागत reboot_mode, स्थिर अक्षर *);

अटल अंतरभूत u32 पढ़ो_पंचांगr0(व्योम)
अणु
	u32 val;
	यंत्र अस्थिर("mrc p6, 0, %0, c0, c1, 0" : "=r" (val));
	वापस val;
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_पंचांगr0(u32 val)
अणु
	यंत्र अस्थिर("mcr p6, 0, %0, c0, c1, 0" : : "r" (val));
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_पंचांगr1(u32 val)
अणु
	यंत्र अस्थिर("mcr p6, 0, %0, c1, c1, 0" : : "r" (val));
पूर्ण

अटल अंतरभूत u32 पढ़ो_tcr0(व्योम)
अणु
	u32 val;
	यंत्र अस्थिर("mrc p6, 0, %0, c2, c1, 0" : "=r" (val));
	वापस val;
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_tcr0(u32 val)
अणु
	यंत्र अस्थिर("mcr p6, 0, %0, c2, c1, 0" : : "r" (val));
पूर्ण

अटल अंतरभूत u32 पढ़ो_tcr1(व्योम)
अणु
	u32 val;
	यंत्र अस्थिर("mrc p6, 0, %0, c3, c1, 0" : "=r" (val));
	वापस val;
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_tcr1(u32 val)
अणु
	यंत्र अस्थिर("mcr p6, 0, %0, c3, c1, 0" : : "r" (val));
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_trr0(u32 val)
अणु
	यंत्र अस्थिर("mcr p6, 0, %0, c4, c1, 0" : : "r" (val));
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_trr1(u32 val)
अणु
	यंत्र अस्थिर("mcr p6, 0, %0, c5, c1, 0" : : "r" (val));
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_tisr(u32 val)
अणु
	यंत्र अस्थिर("mcr p6, 0, %0, c6, c1, 0" : : "r" (val));
पूर्ण

अटल अंतरभूत u32 पढ़ो_wdtcr(व्योम)
अणु
	u32 val;
	यंत्र अस्थिर("mrc p6, 0, %0, c7, c1, 0":"=r" (val));
	वापस val;
पूर्ण
अटल अंतरभूत व्योम ग_लिखो_wdtcr(u32 val)
अणु
	यंत्र अस्थिर("mcr p6, 0, %0, c7, c1, 0"::"r" (val));
पूर्ण

बाह्य अचिन्हित दीर्घ get_iop_tick_rate(व्योम);

/* only iop13xx has these रेजिस्टरs, we define these to present a
 * common रेजिस्टर पूर्णांकerface क्रम the iop_wdt driver.
 */
#घोषणा IOP_RCSR_WDT	(0)
अटल अंतरभूत u32 पढ़ो_rcsr(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम ग_लिखो_wdtsr(u32 val)
अणु
	करो अणु पूर्ण जबतक (0);
पूर्ण

बाह्य काष्ठा platक्रमm_device iop3xx_dma_0_channel;
बाह्य काष्ठा platक्रमm_device iop3xx_dma_1_channel;
बाह्य काष्ठा platक्रमm_device iop3xx_aau_channel;
बाह्य काष्ठा platक्रमm_device iop3xx_i2c0_device;
बाह्य काष्ठा platक्रमm_device iop3xx_i2c1_device;
बाह्य काष्ठा gpiod_lookup_table iop3xx_i2c0_gpio_lookup;
बाह्य काष्ठा gpiod_lookup_table iop3xx_i2c1_gpio_lookup;

#पूर्ण_अगर


#पूर्ण_अगर
