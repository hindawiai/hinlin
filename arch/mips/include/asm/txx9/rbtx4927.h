<शैली गुरु>
/*
 * Author: MontaVista Software, Inc.
 *	   source@mvista.com
 *
 * Copyright 2001-2002 MontaVista Software Inc.
 *
 *  This program is मुक्त software; you can redistribute it and/or modअगरy it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 2 of the License, or (at your
 *  option) any later version.
 *
 *  THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */
#अगर_अघोषित __ASM_TXX9_RBTX4927_H
#घोषणा __ASM_TXX9_RBTX4927_H

#समावेश <यंत्र/txx9/tx4927.h>

#घोषणा RBTX4927_PCIMEM		0x08000000
#घोषणा RBTX4927_PCIMEM_SIZE	0x08000000
#घोषणा RBTX4927_PCIIO		0x16000000
#घोषणा RBTX4927_PCIIO_SIZE	0x01000000

#घोषणा RBTX4927_LED_ADDR	(IO_BASE + TXX9_CE(2) + 0x00001000)
#घोषणा RBTX4927_IMASK_ADDR	(IO_BASE + TXX9_CE(2) + 0x00002000)
#घोषणा RBTX4927_IMSTAT_ADDR	(IO_BASE + TXX9_CE(2) + 0x00002006)
#घोषणा RBTX4927_SOFTINT_ADDR	(IO_BASE + TXX9_CE(2) + 0x00003000)
#घोषणा RBTX4927_SOFTRESET_ADDR (IO_BASE + TXX9_CE(2) + 0x0000f000)
#घोषणा RBTX4927_SOFTRESETLOCK_ADDR	(IO_BASE + TXX9_CE(2) + 0x0000f002)
#घोषणा RBTX4927_PCIRESET_ADDR	(IO_BASE + TXX9_CE(2) + 0x0000f006)
#घोषणा RBTX4927_BRAMRTC_BASE	(IO_BASE + TXX9_CE(2) + 0x00010000)
#घोषणा RBTX4927_ETHER_BASE	(IO_BASE + TXX9_CE(2) + 0x00020000)

/* Ethernet port address */
#घोषणा RBTX4927_ETHER_ADDR	(RBTX4927_ETHER_BASE + 0x280)

#घोषणा rbtx4927_imask_addr	((__u8 __iomem *)RBTX4927_IMASK_ADDR)
#घोषणा rbtx4927_imstat_addr	((__u8 __iomem *)RBTX4927_IMSTAT_ADDR)
#घोषणा rbtx4927_softपूर्णांक_addr	((__u8 __iomem *)RBTX4927_SOFTINT_ADDR)
#घोषणा rbtx4927_softreset_addr ((__u8 __iomem *)RBTX4927_SOFTRESET_ADDR)
#घोषणा rbtx4927_softresetlock_addr	\
				((__u8 __iomem *)RBTX4927_SOFTRESETLOCK_ADDR)
#घोषणा rbtx4927_pcireset_addr	((__u8 __iomem *)RBTX4927_PCIRESET_ADDR)

/* bits क्रम ISTAT/IMASK/IMSTAT */
#घोषणा RBTX4927_INTB_PCID	0
#घोषणा RBTX4927_INTB_PCIC	1
#घोषणा RBTX4927_INTB_PCIB	2
#घोषणा RBTX4927_INTB_PCIA	3
#घोषणा RBTX4927_INTF_PCID	(1 << RBTX4927_INTB_PCID)
#घोषणा RBTX4927_INTF_PCIC	(1 << RBTX4927_INTB_PCIC)
#घोषणा RBTX4927_INTF_PCIB	(1 << RBTX4927_INTB_PCIB)
#घोषणा RBTX4927_INTF_PCIA	(1 << RBTX4927_INTB_PCIA)

#घोषणा RBTX4927_NR_IRQ_IOC	8	/* IOC */

#घोषणा RBTX4927_IRQ_IOC	(TXX9_IRQ_BASE + TX4927_NUM_IR)
#घोषणा RBTX4927_IRQ_IOC_PCID	(RBTX4927_IRQ_IOC + RBTX4927_INTB_PCID)
#घोषणा RBTX4927_IRQ_IOC_PCIC	(RBTX4927_IRQ_IOC + RBTX4927_INTB_PCIC)
#घोषणा RBTX4927_IRQ_IOC_PCIB	(RBTX4927_IRQ_IOC + RBTX4927_INTB_PCIB)
#घोषणा RBTX4927_IRQ_IOC_PCIA	(RBTX4927_IRQ_IOC + RBTX4927_INTB_PCIA)

#घोषणा RBTX4927_IRQ_IOCINT	(TXX9_IRQ_BASE + TX4927_IR_INT(1))

#अगर_घोषित CONFIG_PCI
#घोषणा RBTX4927_ISA_IO_OFFSET RBTX4927_PCIIO
#अन्यथा
#घोषणा RBTX4927_ISA_IO_OFFSET 0
#पूर्ण_अगर

#घोषणा RBTX4927_RTL_8019_BASE (RBTX4927_ETHER_ADDR - mips_io_port_base)
#घोषणा RBTX4927_RTL_8019_IRQ  (TXX9_IRQ_BASE + TX4927_IR_INT(3))

व्योम rbtx4927_prom_init(व्योम);
व्योम rbtx4927_irq_setup(व्योम);
काष्ठा pci_dev;
पूर्णांक rbtx4927_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin);

#पूर्ण_अगर /* __ASM_TXX9_RBTX4927_H */
