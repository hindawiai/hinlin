<शैली गुरु>
/*
 * Definitions क्रम TX4937/TX4938
 *
 * 2003-2005 (c) MontaVista Software, Inc. This file is licensed under the
 * terms of the GNU General Public License version 2. This program is
 * licensed "as is" without any warranty of any kind, whether express
 * or implied.
 *
 * Support क्रम TX4938 in 2.6 - Manish Lachwani (mlachwani@mvista.com)
 */
#अगर_अघोषित __ASM_TXX9_RBTX4938_H
#घोषणा __ASM_TXX9_RBTX4938_H

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/txx9irq.h>
#समावेश <यंत्र/txx9/tx4938.h>

/* Address map */
#घोषणा RBTX4938_FPGA_REG_ADDR	(IO_BASE + TXX9_CE(2) + 0x00000000)
#घोषणा RBTX4938_FPGA_REV_ADDR	(IO_BASE + TXX9_CE(2) + 0x00000002)
#घोषणा RBTX4938_CONFIG1_ADDR	(IO_BASE + TXX9_CE(2) + 0x00000004)
#घोषणा RBTX4938_CONFIG2_ADDR	(IO_BASE + TXX9_CE(2) + 0x00000006)
#घोषणा RBTX4938_CONFIG3_ADDR	(IO_BASE + TXX9_CE(2) + 0x00000008)
#घोषणा RBTX4938_LED_ADDR	(IO_BASE + TXX9_CE(2) + 0x00001000)
#घोषणा RBTX4938_DIPSW_ADDR	(IO_BASE + TXX9_CE(2) + 0x00001002)
#घोषणा RBTX4938_BDIPSW_ADDR	(IO_BASE + TXX9_CE(2) + 0x00001004)
#घोषणा RBTX4938_IMASK_ADDR	(IO_BASE + TXX9_CE(2) + 0x00002000)
#घोषणा RBTX4938_IMASK2_ADDR	(IO_BASE + TXX9_CE(2) + 0x00002002)
#घोषणा RBTX4938_INTPOL_ADDR	(IO_BASE + TXX9_CE(2) + 0x00002004)
#घोषणा RBTX4938_ISTAT_ADDR	(IO_BASE + TXX9_CE(2) + 0x00002006)
#घोषणा RBTX4938_ISTAT2_ADDR	(IO_BASE + TXX9_CE(2) + 0x00002008)
#घोषणा RBTX4938_IMSTAT_ADDR	(IO_BASE + TXX9_CE(2) + 0x0000200a)
#घोषणा RBTX4938_IMSTAT2_ADDR	(IO_BASE + TXX9_CE(2) + 0x0000200c)
#घोषणा RBTX4938_SOFTINT_ADDR	(IO_BASE + TXX9_CE(2) + 0x00003000)
#घोषणा RBTX4938_PIOSEL_ADDR	(IO_BASE + TXX9_CE(2) + 0x00005000)
#घोषणा RBTX4938_SPICS_ADDR	(IO_BASE + TXX9_CE(2) + 0x00005002)
#घोषणा RBTX4938_SFPWR_ADDR	(IO_BASE + TXX9_CE(2) + 0x00005008)
#घोषणा RBTX4938_SFVOL_ADDR	(IO_BASE + TXX9_CE(2) + 0x0000500a)
#घोषणा RBTX4938_SOFTRESET_ADDR (IO_BASE + TXX9_CE(2) + 0x00007000)
#घोषणा RBTX4938_SOFTRESETLOCK_ADDR	(IO_BASE + TXX9_CE(2) + 0x00007002)
#घोषणा RBTX4938_PCIRESET_ADDR	(IO_BASE + TXX9_CE(2) + 0x00007004)
#घोषणा RBTX4938_ETHER_BASE	(IO_BASE + TXX9_CE(2) + 0x00020000)

/* Ethernet port address (Jumperless Mode (W12:Open)) */
#घोषणा RBTX4938_ETHER_ADDR	(RBTX4938_ETHER_BASE + 0x280)

/* bits क्रम ISTAT/IMASK/IMSTAT */
#घोषणा RBTX4938_INTB_PCID	0
#घोषणा RBTX4938_INTB_PCIC	1
#घोषणा RBTX4938_INTB_PCIB	2
#घोषणा RBTX4938_INTB_PCIA	3
#घोषणा RBTX4938_INTB_RTC	4
#घोषणा RBTX4938_INTB_ATA	5
#घोषणा RBTX4938_INTB_MODEM	6
#घोषणा RBTX4938_INTB_SWINT	7
#घोषणा RBTX4938_INTF_PCID	(1 << RBTX4938_INTB_PCID)
#घोषणा RBTX4938_INTF_PCIC	(1 << RBTX4938_INTB_PCIC)
#घोषणा RBTX4938_INTF_PCIB	(1 << RBTX4938_INTB_PCIB)
#घोषणा RBTX4938_INTF_PCIA	(1 << RBTX4938_INTB_PCIA)
#घोषणा RBTX4938_INTF_RTC	(1 << RBTX4938_INTB_RTC)
#घोषणा RBTX4938_INTF_ATA	(1 << RBTX4938_INTB_ATA)
#घोषणा RBTX4938_INTF_MODEM	(1 << RBTX4938_INTB_MODEM)
#घोषणा RBTX4938_INTF_SWINT	(1 << RBTX4938_INTB_SWINT)

#घोषणा rbtx4938_fpga_rev_addr	((__u8 __iomem *)RBTX4938_FPGA_REV_ADDR)
#घोषणा rbtx4938_led_addr	((__u8 __iomem *)RBTX4938_LED_ADDR)
#घोषणा rbtx4938_dipsw_addr	((__u8 __iomem *)RBTX4938_DIPSW_ADDR)
#घोषणा rbtx4938_bdipsw_addr	((__u8 __iomem *)RBTX4938_BDIPSW_ADDR)
#घोषणा rbtx4938_imask_addr	((__u8 __iomem *)RBTX4938_IMASK_ADDR)
#घोषणा rbtx4938_imask2_addr	((__u8 __iomem *)RBTX4938_IMASK2_ADDR)
#घोषणा rbtx4938_पूर्णांकpol_addr	((__u8 __iomem *)RBTX4938_INTPOL_ADDR)
#घोषणा rbtx4938_istat_addr	((__u8 __iomem *)RBTX4938_ISTAT_ADDR)
#घोषणा rbtx4938_istat2_addr	((__u8 __iomem *)RBTX4938_ISTAT2_ADDR)
#घोषणा rbtx4938_imstat_addr	((__u8 __iomem *)RBTX4938_IMSTAT_ADDR)
#घोषणा rbtx4938_imstat2_addr	((__u8 __iomem *)RBTX4938_IMSTAT2_ADDR)
#घोषणा rbtx4938_softपूर्णांक_addr	((__u8 __iomem *)RBTX4938_SOFTINT_ADDR)
#घोषणा rbtx4938_piosel_addr	((__u8 __iomem *)RBTX4938_PIOSEL_ADDR)
#घोषणा rbtx4938_spics_addr	((__u8 __iomem *)RBTX4938_SPICS_ADDR)
#घोषणा rbtx4938_sfpwr_addr	((__u8 __iomem *)RBTX4938_SFPWR_ADDR)
#घोषणा rbtx4938_sfvol_addr	((__u8 __iomem *)RBTX4938_SFVOL_ADDR)
#घोषणा rbtx4938_softreset_addr ((__u8 __iomem *)RBTX4938_SOFTRESET_ADDR)
#घोषणा rbtx4938_softresetlock_addr	\
				((__u8 __iomem *)RBTX4938_SOFTRESETLOCK_ADDR)
#घोषणा rbtx4938_pcireset_addr	((__u8 __iomem *)RBTX4938_PCIRESET_ADDR)

/*
 * IRQ mappings
 */

#घोषणा RBTX4938_SOFT_INT0	0	/* not used */
#घोषणा RBTX4938_SOFT_INT1	1	/* not used */
#घोषणा RBTX4938_IRC_INT	2
#घोषणा RBTX4938_TIMER_INT	7

/* These are the भव IRQ numbers, we भागide all IRQ's पूर्णांकo
 * 'spaces', the 'space' determines where and how to enable/disable
 * that particular IRQ on an RBTX4938 machine.	Add new 'spaces' as new
 * IRQ hardware is supported.
 */
#घोषणा RBTX4938_NR_IRQ_IOC	8

#घोषणा RBTX4938_IRQ_IRC	TXX9_IRQ_BASE
#घोषणा RBTX4938_IRQ_IOC	(TXX9_IRQ_BASE + TX4938_NUM_IR)
#घोषणा RBTX4938_IRQ_END	(RBTX4938_IRQ_IOC + RBTX4938_NR_IRQ_IOC)

#घोषणा RBTX4938_IRQ_IRC_ECCERR (RBTX4938_IRQ_IRC + TX4938_IR_ECCERR)
#घोषणा RBTX4938_IRQ_IRC_WTOERR (RBTX4938_IRQ_IRC + TX4938_IR_WTOERR)
#घोषणा RBTX4938_IRQ_IRC_INT(n) (RBTX4938_IRQ_IRC + TX4938_IR_INT(n))
#घोषणा RBTX4938_IRQ_IRC_SIO(n) (RBTX4938_IRQ_IRC + TX4938_IR_SIO(n))
#घोषणा RBTX4938_IRQ_IRC_DMA(ch, n)	(RBTX4938_IRQ_IRC + TX4938_IR_DMA(ch, n))
#घोषणा RBTX4938_IRQ_IRC_PIO	(RBTX4938_IRQ_IRC + TX4938_IR_PIO)
#घोषणा RBTX4938_IRQ_IRC_PDMAC	(RBTX4938_IRQ_IRC + TX4938_IR_PDMAC)
#घोषणा RBTX4938_IRQ_IRC_PCIC	(RBTX4938_IRQ_IRC + TX4938_IR_PCIC)
#घोषणा RBTX4938_IRQ_IRC_TMR(n) (RBTX4938_IRQ_IRC + TX4938_IR_TMR(n))
#घोषणा RBTX4938_IRQ_IRC_NDFMC	(RBTX4938_IRQ_IRC + TX4938_IR_NDFMC)
#घोषणा RBTX4938_IRQ_IRC_PCIERR (RBTX4938_IRQ_IRC + TX4938_IR_PCIERR)
#घोषणा RBTX4938_IRQ_IRC_PCIPME (RBTX4938_IRQ_IRC + TX4938_IR_PCIPME)
#घोषणा RBTX4938_IRQ_IRC_ACLC	(RBTX4938_IRQ_IRC + TX4938_IR_ACLC)
#घोषणा RBTX4938_IRQ_IRC_ACLCPME	(RBTX4938_IRQ_IRC + TX4938_IR_ACLCPME)
#घोषणा RBTX4938_IRQ_IRC_PCIC1	(RBTX4938_IRQ_IRC + TX4938_IR_PCIC1)
#घोषणा RBTX4938_IRQ_IRC_SPI	(RBTX4938_IRQ_IRC + TX4938_IR_SPI)
#घोषणा RBTX4938_IRQ_IOC_PCID	(RBTX4938_IRQ_IOC + RBTX4938_INTB_PCID)
#घोषणा RBTX4938_IRQ_IOC_PCIC	(RBTX4938_IRQ_IOC + RBTX4938_INTB_PCIC)
#घोषणा RBTX4938_IRQ_IOC_PCIB	(RBTX4938_IRQ_IOC + RBTX4938_INTB_PCIB)
#घोषणा RBTX4938_IRQ_IOC_PCIA	(RBTX4938_IRQ_IOC + RBTX4938_INTB_PCIA)
#घोषणा RBTX4938_IRQ_IOC_RTC	(RBTX4938_IRQ_IOC + RBTX4938_INTB_RTC)
#घोषणा RBTX4938_IRQ_IOC_ATA	(RBTX4938_IRQ_IOC + RBTX4938_INTB_ATA)
#घोषणा RBTX4938_IRQ_IOC_MODEM	(RBTX4938_IRQ_IOC + RBTX4938_INTB_MODEM)
#घोषणा RBTX4938_IRQ_IOC_SWINT	(RBTX4938_IRQ_IOC + RBTX4938_INTB_SWINT)


/* IOC (PCI, etc) */
#घोषणा RBTX4938_IRQ_IOCINT	(TXX9_IRQ_BASE + TX4938_IR_INT(0))
/* Onboard 10M Ether */
#घोषणा RBTX4938_IRQ_ETHER	(TXX9_IRQ_BASE + TX4938_IR_INT(1))

#घोषणा RBTX4938_RTL_8019_BASE (RBTX4938_ETHER_ADDR - mips_io_port_base)
#घोषणा RBTX4938_RTL_8019_IRQ  (RBTX4938_IRQ_ETHER)

व्योम rbtx4938_prom_init(व्योम);
व्योम rbtx4938_irq_setup(व्योम);
काष्ठा pci_dev;
पूर्णांक rbtx4938_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin);

#पूर्ण_अगर /* __ASM_TXX9_RBTX4938_H */
