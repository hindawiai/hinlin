<शैली गुरु>
/*
 * Copyright 2001 MontaVista Software Inc.
 * Author: MontaVista Software, Inc.
 *              ahennessy@mvista.com
 *
 * Copyright (C) 2000-2001 Toshiba Corporation
 * Copyright (C) 2004 by Ralf Baechle (ralf@linux-mips.org)
 *
 * Based on arch/mips/ddb5xxx/ddb5477/pci_ops.c
 *
 *     Define the pci_ops क्रम TX3927.
 *
 * Much of the code is derived from the original DDB5074 port by
 * Geert Uytterhoeven <geert@linux-m68k.org>
 *
 *  This program is मुक्त software; you can redistribute  it and/or modअगरy it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/txx9irq.h>
#समावेश <यंत्र/txx9/pci.h>
#समावेश <यंत्र/txx9/tx3927.h>

अटल पूर्णांक mkaddr(काष्ठा pci_bus *bus, अचिन्हित अक्षर devfn, अचिन्हित अक्षर where)
अणु
	अगर (bus->parent == शून्य &&
	    devfn >= PCI_DEVFN(TX3927_PCIC_MAX_DEVNU, 0))
		वापस -1;
	tx3927_pcicptr->ica =
		((bus->number & 0xff) << 0x10) |
		((devfn & 0xff) << 0x08) |
		(where & 0xfc) | (bus->parent ? 1 : 0);

	/* clear M_ABORT and Disable M_ABORT Int. */
	tx3927_pcicptr->pcistat |= PCI_STATUS_REC_MASTER_ABORT;
	tx3927_pcicptr->pcistatim &= ~PCI_STATUS_REC_MASTER_ABORT;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक check_पात(व्योम)
अणु
	अगर (tx3927_pcicptr->pcistat & PCI_STATUS_REC_MASTER_ABORT) अणु
		tx3927_pcicptr->pcistat |= PCI_STATUS_REC_MASTER_ABORT;
		tx3927_pcicptr->pcistatim |= PCI_STATUS_REC_MASTER_ABORT;
		/* flush ग_लिखो buffer */
		iob();
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक tx3927_pci_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
	पूर्णांक where, पूर्णांक size, u32 * val)
अणु
	अगर (mkaddr(bus, devfn, where)) अणु
		*val = 0xffffffff;
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	चयन (size) अणु
	हाल 1:
		*val = *(अस्थिर u8 *) ((अचिन्हित दीर्घ) & tx3927_pcicptr->icd | (where & 3));
		अवरोध;

	हाल 2:
		*val = le16_to_cpu(*(अस्थिर u16 *) ((अचिन्हित दीर्घ) & tx3927_pcicptr->icd | (where & 3)));
		अवरोध;

	हाल 4:
		*val = le32_to_cpu(tx3927_pcicptr->icd);
		अवरोध;
	पूर्ण

	वापस check_पात();
पूर्ण

अटल पूर्णांक tx3927_pci_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
	पूर्णांक where, पूर्णांक size, u32 val)
अणु
	अगर (mkaddr(bus, devfn, where))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	चयन (size) अणु
	हाल 1:
		*(अस्थिर u8 *) ((अचिन्हित दीर्घ) & tx3927_pcicptr->icd | (where & 3)) = val;
		अवरोध;

	हाल 2:
		*(अस्थिर u16 *) ((अचिन्हित दीर्घ) & tx3927_pcicptr->icd | (where & 2)) =
	    cpu_to_le16(val);
		अवरोध;

	हाल 4:
		tx3927_pcicptr->icd = cpu_to_le32(val);
	पूर्ण

	वापस check_पात();
पूर्ण

अटल काष्ठा pci_ops tx3927_pci_ops = अणु
	.पढ़ो = tx3927_pci_पढ़ो_config,
	.ग_लिखो = tx3927_pci_ग_लिखो_config,
पूर्ण;

व्योम __init tx3927_pcic_setup(काष्ठा pci_controller *channel,
			      अचिन्हित दीर्घ sdram_size, पूर्णांक extarb)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ io_base =
		channel->io_resource->start + mips_io_port_base - IO_BASE;
	अचिन्हित दीर्घ io_size =
		channel->io_resource->end - channel->io_resource->start;
	अचिन्हित दीर्घ io_pciaddr =
		channel->io_resource->start - channel->io_offset;
	अचिन्हित दीर्घ mem_base =
		channel->mem_resource->start;
	अचिन्हित दीर्घ mem_size =
		channel->mem_resource->end - channel->mem_resource->start;
	अचिन्हित दीर्घ mem_pciaddr =
		channel->mem_resource->start - channel->mem_offset;

	prपूर्णांकk(KERN_INFO "TX3927 PCIC -- DID:%04x VID:%04x RID:%02x Arbiter:%s",
	       tx3927_pcicptr->did, tx3927_pcicptr->vid,
	       tx3927_pcicptr->rid,
	       extarb ? "External" : "Internal");
	channel->pci_ops = &tx3927_pci_ops;

	local_irq_save(flags);
	/* Disable External PCI Config. Access */
	tx3927_pcicptr->lbc = TX3927_PCIC_LBC_EPCAD;
#अगर_घोषित __BIG_ENDIAN
	tx3927_pcicptr->lbc |= TX3927_PCIC_LBC_IBSE |
		TX3927_PCIC_LBC_TIBSE |
		TX3927_PCIC_LBC_TMFBSE | TX3927_PCIC_LBC_MSDSE;
#पूर्ण_अगर
	/* LB->PCI mappings */
	tx3927_pcicptr->iomas = ~(io_size - 1);
	tx3927_pcicptr->ilbioma = io_base;
	tx3927_pcicptr->ipbioma = io_pciaddr;
	tx3927_pcicptr->mmas = ~(mem_size - 1);
	tx3927_pcicptr->ilbmma = mem_base;
	tx3927_pcicptr->ipbmma = mem_pciaddr;
	/* PCI->LB mappings */
	tx3927_pcicptr->iobas = 0xffffffff;
	tx3927_pcicptr->ioba = 0;
	tx3927_pcicptr->tlbioma = 0;
	tx3927_pcicptr->mbas = ~(sdram_size - 1);
	tx3927_pcicptr->mba = 0;
	tx3927_pcicptr->tlbmma = 0;
	/* Enable Direct mapping Address Space Decoder */
	tx3927_pcicptr->lbc |= TX3927_PCIC_LBC_ILMDE | TX3927_PCIC_LBC_ILIDE;

	/* Clear All Local Bus Status */
	tx3927_pcicptr->lbstat = TX3927_PCIC_LBIM_ALL;
	/* Enable All Local Bus Interrupts */
	tx3927_pcicptr->lbim = TX3927_PCIC_LBIM_ALL;
	/* Clear All PCI Status Error */
	tx3927_pcicptr->pcistat = TX3927_PCIC_PCISTATIM_ALL;
	/* Enable All PCI Status Error Interrupts */
	tx3927_pcicptr->pcistatim = TX3927_PCIC_PCISTATIM_ALL;

	/* PCIC Int => IRC IRQ10 */
	tx3927_pcicptr->il = TX3927_IR_PCI;
	/* Target Control (per errata) */
	tx3927_pcicptr->tc = TX3927_PCIC_TC_OF8E | TX3927_PCIC_TC_IF8E;

	/* Enable Bus Arbiter */
	अगर (!extarb)
		tx3927_pcicptr->pbapmc = TX3927_PCIC_PBAPMC_PBAEN;

	tx3927_pcicptr->pcicmd = PCI_COMMAND_MASTER |
		PCI_COMMAND_MEMORY |
		PCI_COMMAND_IO |
		PCI_COMMAND_PARITY | PCI_COMMAND_SERR;
	local_irq_restore(flags);
पूर्ण

अटल irqवापस_t tx3927_pcierr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pt_regs *regs = get_irq_regs();

	अगर (txx9_pci_err_action != TXX9_PCI_ERR_IGNORE) अणु
		prपूर्णांकk(KERN_WARNING "PCI error interrupt at 0x%08lx.\n",
		       regs->cp0_epc);
		prपूर्णांकk(KERN_WARNING "pcistat:%02x, lbstat:%04lx\n",
		       tx3927_pcicptr->pcistat, tx3927_pcicptr->lbstat);
	पूर्ण
	अगर (txx9_pci_err_action != TXX9_PCI_ERR_PANIC) अणु
		/* clear all pci errors */
		tx3927_pcicptr->pcistat |= TX3927_PCIC_PCISTATIM_ALL;
		tx3927_pcicptr->istat = TX3927_PCIC_IIM_ALL;
		tx3927_pcicptr->tstat = TX3927_PCIC_TIM_ALL;
		tx3927_pcicptr->lbstat = TX3927_PCIC_LBIM_ALL;
		वापस IRQ_HANDLED;
	पूर्ण
	console_verbose();
	panic("PCI error.");
पूर्ण

व्योम __init tx3927_setup_pcierr_irq(व्योम)
अणु
	अगर (request_irq(TXX9_IRQ_BASE + TX3927_IR_PCI,
			tx3927_pcierr_पूर्णांकerrupt,
			0, "PCI error",
			(व्योम *)TX3927_PCIC_REG))
		prपूर्णांकk(KERN_WARNING "Failed to request irq for PCIERR\n");
पूर्ण
