<शैली गुरु>
/*
 * Defines क्रम the TJSYS JMR-TX3927
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2000-2001 Toshiba Corporation
 */
#अगर_अघोषित __ASM_TXX9_JMR3927_H
#घोषणा __ASM_TXX9_JMR3927_H

#समावेश <यंत्र/txx9/tx3927.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/txx9irq.h>

/* CS */
#घोषणा JMR3927_ROMCE0	0x1fc00000	/* 4M */
#घोषणा JMR3927_ROMCE1	0x1e000000	/* 4M */
#घोषणा JMR3927_ROMCE2	0x14000000	/* 16M */
#घोषणा JMR3927_ROMCE3	0x10000000	/* 64M */
#घोषणा JMR3927_ROMCE5	0x1d000000	/* 4M */
#घोषणा JMR3927_SDCS0	0x00000000	/* 32M */
#घोषणा JMR3927_SDCS1	0x02000000	/* 32M */
/* PCI Direct Mappings */

#घोषणा JMR3927_PCIMEM	0x08000000
#घोषणा JMR3927_PCIMEM_SIZE	0x08000000	/* 128M */
#घोषणा JMR3927_PCIIO	0x15000000
#घोषणा JMR3927_PCIIO_SIZE	0x01000000	/* 16M */

#घोषणा JMR3927_SDRAM_SIZE	0x02000000	/* 32M */
#घोषणा JMR3927_PORT_BASE	KSEG1

/* Address map (भव address) */
#घोषणा JMR3927_ROM0_BASE	(KSEG1 + JMR3927_ROMCE0)
#घोषणा JMR3927_ROM1_BASE	(KSEG1 + JMR3927_ROMCE1)
#घोषणा JMR3927_IOC_BASE	(KSEG1 + JMR3927_ROMCE2)
#घोषणा JMR3927_PCIMEM_BASE	(KSEG1 + JMR3927_PCIMEM)
#घोषणा JMR3927_PCIIO_BASE	(KSEG1 + JMR3927_PCIIO)

#घोषणा JMR3927_IOC_REV_ADDR	(JMR3927_IOC_BASE + 0x00000000)
#घोषणा JMR3927_IOC_NVRAMB_ADDR (JMR3927_IOC_BASE + 0x00010000)
#घोषणा JMR3927_IOC_LED_ADDR	(JMR3927_IOC_BASE + 0x00020000)
#घोषणा JMR3927_IOC_DIPSW_ADDR	(JMR3927_IOC_BASE + 0x00030000)
#घोषणा JMR3927_IOC_BREV_ADDR	(JMR3927_IOC_BASE + 0x00040000)
#घोषणा JMR3927_IOC_DTR_ADDR	(JMR3927_IOC_BASE + 0x00050000)
#घोषणा JMR3927_IOC_INTS1_ADDR	(JMR3927_IOC_BASE + 0x00080000)
#घोषणा JMR3927_IOC_INTS2_ADDR	(JMR3927_IOC_BASE + 0x00090000)
#घोषणा JMR3927_IOC_INTM_ADDR	(JMR3927_IOC_BASE + 0x000a0000)
#घोषणा JMR3927_IOC_INTP_ADDR	(JMR3927_IOC_BASE + 0x000b0000)
#घोषणा JMR3927_IOC_RESET_ADDR	(JMR3927_IOC_BASE + 0x000f0000)

/* Flash ROM */
#घोषणा JMR3927_FLASH_BASE	(JMR3927_ROM0_BASE)
#घोषणा JMR3927_FLASH_SIZE	0x00400000

/* bits क्रम IOC_REV/IOC_BREV (high byte) */
#घोषणा JMR3927_IDT_MASK	0xfc
#घोषणा JMR3927_REV_MASK	0x03
#घोषणा JMR3927_IOC_IDT		0xe0

/* bits क्रम IOC_INTS1/IOC_INTS2/IOC_INTM/IOC_INTP (high byte) */
#घोषणा JMR3927_IOC_INTB_PCIA	0
#घोषणा JMR3927_IOC_INTB_PCIB	1
#घोषणा JMR3927_IOC_INTB_PCIC	2
#घोषणा JMR3927_IOC_INTB_PCID	3
#घोषणा JMR3927_IOC_INTB_MODEM	4
#घोषणा JMR3927_IOC_INTB_INT6	5
#घोषणा JMR3927_IOC_INTB_INT7	6
#घोषणा JMR3927_IOC_INTB_SOFT	7
#घोषणा JMR3927_IOC_INTF_PCIA	(1 << JMR3927_IOC_INTF_PCIA)
#घोषणा JMR3927_IOC_INTF_PCIB	(1 << JMR3927_IOC_INTB_PCIB)
#घोषणा JMR3927_IOC_INTF_PCIC	(1 << JMR3927_IOC_INTB_PCIC)
#घोषणा JMR3927_IOC_INTF_PCID	(1 << JMR3927_IOC_INTB_PCID)
#घोषणा JMR3927_IOC_INTF_MODEM	(1 << JMR3927_IOC_INTB_MODEM)
#घोषणा JMR3927_IOC_INTF_INT6	(1 << JMR3927_IOC_INTB_INT6)
#घोषणा JMR3927_IOC_INTF_INT7	(1 << JMR3927_IOC_INTB_INT7)
#घोषणा JMR3927_IOC_INTF_SOFT	(1 << JMR3927_IOC_INTB_SOFT)

/* bits क्रम IOC_RESET (high byte) */
#घोषणा JMR3927_IOC_RESET_CPU	1
#घोषणा JMR3927_IOC_RESET_PCI	2

#अगर defined(__BIG_ENDIAN)
#घोषणा jmr3927_ioc_reg_out(d, a)	((*(अस्थिर अचिन्हित अक्षर *)(a)) = (d))
#घोषणा jmr3927_ioc_reg_in(a)		(*(अस्थिर अचिन्हित अक्षर *)(a))
#या_अगर defined(__LITTLE_ENDIAN)
#घोषणा jmr3927_ioc_reg_out(d, a)	((*(अस्थिर अचिन्हित अक्षर *)((a)^1)) = (d))
#घोषणा jmr3927_ioc_reg_in(a)		(*(अस्थिर अचिन्हित अक्षर *)((a)^1))
#अन्यथा
#त्रुटि "No Endian"
#पूर्ण_अगर

/* LED macro */
#घोषणा jmr3927_led_set(n/*0-16*/)	jmr3927_ioc_reg_out(~(n), JMR3927_IOC_LED_ADDR)

#घोषणा jmr3927_led_and_set(n/*0-16*/)	jmr3927_ioc_reg_out((~(n)) & jmr3927_ioc_reg_in(JMR3927_IOC_LED_ADDR), JMR3927_IOC_LED_ADDR)

/* DIPSW4 macro */
#घोषणा jmr3927_dipsw1()	(gpio_get_value(11) == 0)
#घोषणा jmr3927_dipsw2()	(gpio_get_value(10) == 0)
#घोषणा jmr3927_dipsw3()	((jmr3927_ioc_reg_in(JMR3927_IOC_DIPSW_ADDR) & 2) == 0)
#घोषणा jmr3927_dipsw4()	((jmr3927_ioc_reg_in(JMR3927_IOC_DIPSW_ADDR) & 1) == 0)

/*
 * IRQ mappings
 */

/* These are the भव IRQ numbers, we भागide all IRQ's पूर्णांकo
 * 'spaces', the 'space' determines where and how to enable/disable
 * that particular IRQ on an JMR machine.  Add new 'spaces' as new
 * IRQ hardware is supported.
 */
#घोषणा JMR3927_NR_IRQ_IRC	16	/* On-Chip IRC */
#घोषणा JMR3927_NR_IRQ_IOC	8	/* PCI/MODEM/INT[6:7] */

#घोषणा JMR3927_IRQ_IRC TXX9_IRQ_BASE
#घोषणा JMR3927_IRQ_IOC (JMR3927_IRQ_IRC + JMR3927_NR_IRQ_IRC)
#घोषणा JMR3927_IRQ_END (JMR3927_IRQ_IOC + JMR3927_NR_IRQ_IOC)

#घोषणा JMR3927_IRQ_IRC_INT0	(JMR3927_IRQ_IRC + TX3927_IR_INT0)
#घोषणा JMR3927_IRQ_IRC_INT1	(JMR3927_IRQ_IRC + TX3927_IR_INT1)
#घोषणा JMR3927_IRQ_IRC_INT2	(JMR3927_IRQ_IRC + TX3927_IR_INT2)
#घोषणा JMR3927_IRQ_IRC_INT3	(JMR3927_IRQ_IRC + TX3927_IR_INT3)
#घोषणा JMR3927_IRQ_IRC_INT4	(JMR3927_IRQ_IRC + TX3927_IR_INT4)
#घोषणा JMR3927_IRQ_IRC_INT5	(JMR3927_IRQ_IRC + TX3927_IR_INT5)
#घोषणा JMR3927_IRQ_IRC_SIO0	(JMR3927_IRQ_IRC + TX3927_IR_SIO0)
#घोषणा JMR3927_IRQ_IRC_SIO1	(JMR3927_IRQ_IRC + TX3927_IR_SIO1)
#घोषणा JMR3927_IRQ_IRC_SIO(ch) (JMR3927_IRQ_IRC + TX3927_IR_SIO(ch))
#घोषणा JMR3927_IRQ_IRC_DMA	(JMR3927_IRQ_IRC + TX3927_IR_DMA)
#घोषणा JMR3927_IRQ_IRC_PIO	(JMR3927_IRQ_IRC + TX3927_IR_PIO)
#घोषणा JMR3927_IRQ_IRC_PCI	(JMR3927_IRQ_IRC + TX3927_IR_PCI)
#घोषणा JMR3927_IRQ_IRC_TMR(ch) (JMR3927_IRQ_IRC + TX3927_IR_TMR(ch))
#घोषणा JMR3927_IRQ_IOC_PCIA	(JMR3927_IRQ_IOC + JMR3927_IOC_INTB_PCIA)
#घोषणा JMR3927_IRQ_IOC_PCIB	(JMR3927_IRQ_IOC + JMR3927_IOC_INTB_PCIB)
#घोषणा JMR3927_IRQ_IOC_PCIC	(JMR3927_IRQ_IOC + JMR3927_IOC_INTB_PCIC)
#घोषणा JMR3927_IRQ_IOC_PCID	(JMR3927_IRQ_IOC + JMR3927_IOC_INTB_PCID)
#घोषणा JMR3927_IRQ_IOC_MODEM	(JMR3927_IRQ_IOC + JMR3927_IOC_INTB_MODEM)
#घोषणा JMR3927_IRQ_IOC_INT6	(JMR3927_IRQ_IOC + JMR3927_IOC_INTB_INT6)
#घोषणा JMR3927_IRQ_IOC_INT7	(JMR3927_IRQ_IOC + JMR3927_IOC_INTB_INT7)
#घोषणा JMR3927_IRQ_IOC_SOFT	(JMR3927_IRQ_IOC + JMR3927_IOC_INTB_SOFT)

/* IOC (PCI, MODEM) */
#घोषणा JMR3927_IRQ_IOCINT	JMR3927_IRQ_IRC_INT1
/* TC35815 100M Ether (JMR-TX3912:JPW4:2-3 Short) */
#घोषणा JMR3927_IRQ_ETHER0	JMR3927_IRQ_IRC_INT3

/* Clocks */
#घोषणा JMR3927_CORECLK 132710400	/* 132.7MHz */

/*
 * TX3927 Pin Configuration:
 *
 *	PCFG bits		Avail			Dead
 *	SELSIO[1:0]:11		RXD[1:0], TXD[1:0]	PIO[6:3]
 *	SELSIOC[0]:1		CTS[0], RTS[0]		INT[5:4]
 *	SELSIOC[1]:0,SELDSF:0,	GSDAO[0],GPCST[3]	CTS[1], RTS[1],DSF,
 *	  GDBGE*					  PIO[2:1]
 *	SELDMA[2]:1		DMAREQ[2],DMAACK[2]	PIO[13:12]
 *	SELTMR[2:0]:000					TIMER[1:0]
 *	SELCS:0,SELDMA[1]:0	PIO[11;10]		SDCS_CE[7:6],
 *							  DMAREQ[1],DMAACK[1]
 *	SELDMA[0]:1		DMAREQ[0],DMAACK[0]	PIO[9:8]
 *	SELDMA[3]:1		DMAREQ[3],DMAACK[3]	PIO[15:14]
 *	SELDONE:1		DMADONE			PIO[7]
 *
 * Usable pins are:
 *	RXD[1;0],TXD[1:0],CTS[0],RTS[0],
 *	DMAREQ[0,2,3],DMAACK[0,2,3],DMADONE,PIO[0,10,11]
 *	INT[3:0]
 */

व्योम jmr3927_prom_init(व्योम);
व्योम jmr3927_irq_setup(व्योम);
काष्ठा pci_dev;
पूर्णांक jmr3927_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin);

#पूर्ण_अगर /* __ASM_TXX9_JMR3927_H */
