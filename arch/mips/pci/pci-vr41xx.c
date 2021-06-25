<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  pci-vr41xx.c, PCI Control Unit routines क्रम the NEC VR4100 series.
 *
 *  Copyright (C) 2001-2003 MontaVista Software Inc.
 *    Author: Yoichi Yuasa <source@mvista.com>
 *  Copyright (C) 2004-2008  Yoichi Yuasa <yuasa@linux-mips.org>
 *  Copyright (C) 2004 by Ralf Baechle (ralf@linux-mips.org)
 */
/*
 * Changes:
 *  MontaVista Software Inc. <source@mvista.com>
 *  - New creation, NEC VR4122 and VR4131 are supported.
 */
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/vr41xx/pci.h>
#समावेश <यंत्र/vr41xx/vr41xx.h>

#समावेश "pci-vr41xx.h"

बाह्य काष्ठा pci_ops vr41xx_pci_ops;

अटल व्योम __iomem *pciu_base;

#घोषणा pciu_पढ़ो(offset)		पढ़ोl(pciu_base + (offset))
#घोषणा pciu_ग_लिखो(offset, value)	ग_लिखोl((value), pciu_base + (offset))

अटल काष्ठा pci_master_address_conversion pci_master_memory1 = अणु
	.bus_base_address	= PCI_MASTER_MEM1_BUS_BASE_ADDRESS,
	.address_mask		= PCI_MASTER_MEM1_ADDRESS_MASK,
	.pci_base_address	= PCI_MASTER_MEM1_PCI_BASE_ADDRESS,
पूर्ण;

अटल काष्ठा pci_target_address_conversion pci_target_memory1 = अणु
	.address_mask		= PCI_TARGET_MEM1_ADDRESS_MASK,
	.bus_base_address	= PCI_TARGET_MEM1_BUS_BASE_ADDRESS,
पूर्ण;

अटल काष्ठा pci_master_address_conversion pci_master_io = अणु
	.bus_base_address	= PCI_MASTER_IO_BUS_BASE_ADDRESS,
	.address_mask		= PCI_MASTER_IO_ADDRESS_MASK,
	.pci_base_address	= PCI_MASTER_IO_PCI_BASE_ADDRESS,
पूर्ण;

अटल काष्ठा pci_mailbox_address pci_mailbox = अणु
	.base_address		= PCI_MAILBOX_BASE_ADDRESS,
पूर्ण;

अटल काष्ठा pci_target_address_winकरोw pci_target_winकरोw1 = अणु
	.base_address		= PCI_TARGET_WINDOW1_BASE_ADDRESS,
पूर्ण;

अटल काष्ठा resource pci_mem_resource = अणु
	.name	= "PCI Memory resources",
	.start	= PCI_MEM_RESOURCE_START,
	.end	= PCI_MEM_RESOURCE_END,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा resource pci_io_resource = अणु
	.name	= "PCI I/O resources",
	.start	= PCI_IO_RESOURCE_START,
	.end	= PCI_IO_RESOURCE_END,
	.flags	= IORESOURCE_IO,
पूर्ण;

अटल काष्ठा pci_controller_unit_setup vr41xx_pci_controller_unit_setup = अणु
	.master_memory1				= &pci_master_memory1,
	.target_memory1				= &pci_target_memory1,
	.master_io				= &pci_master_io,
	.exclusive_access			= CANNOT_LOCK_FROM_DEVICE,
	.रुको_समय_limit_from_irdy_to_trdy	= 0,
	.mailbox				= &pci_mailbox,
	.target_winकरोw1				= &pci_target_winकरोw1,
	.master_latency_समयr			= 0x80,
	.retry_limit				= 0,
	.arbiter_priority_control		= PCI_ARBITRATION_MODE_FAIR,
	.take_away_gnt_mode			= PCI_TAKE_AWAY_GNT_DISABLE,
पूर्ण;

अटल काष्ठा pci_controller vr41xx_pci_controller = अणु
	.pci_ops	= &vr41xx_pci_ops,
	.mem_resource	= &pci_mem_resource,
	.io_resource	= &pci_io_resource,
पूर्ण;

व्योम __init vr41xx_pciu_setup(काष्ठा pci_controller_unit_setup *setup)
अणु
	vr41xx_pci_controller_unit_setup = *setup;
पूर्ण

अटल पूर्णांक __init vr41xx_pciu_init(व्योम)
अणु
	काष्ठा pci_controller_unit_setup *setup;
	काष्ठा pci_master_address_conversion *master;
	काष्ठा pci_target_address_conversion *target;
	काष्ठा pci_mailbox_address *mailbox;
	काष्ठा pci_target_address_winकरोw *winकरोw;
	अचिन्हित दीर्घ vtघड़ी, pci_घड़ी_max;
	uपूर्णांक32_t val;

	setup = &vr41xx_pci_controller_unit_setup;

	अगर (request_mem_region(PCIU_BASE, PCIU_SIZE, "PCIU") == शून्य)
		वापस -EBUSY;

	pciu_base = ioremap(PCIU_BASE, PCIU_SIZE);
	अगर (pciu_base == शून्य) अणु
		release_mem_region(PCIU_BASE, PCIU_SIZE);
		वापस -EBUSY;
	पूर्ण

	/* Disable PCI पूर्णांकerrupt */
	vr41xx_disable_pciपूर्णांक();

	/* Supply VTClock to PCIU */
	vr41xx_supply_घड़ी(PCIU_CLOCK);

	/* Dummy ग_लिखो, रुकोing क्रम supply of VTClock. */
	vr41xx_disable_pciपूर्णांक();

	/* Select PCI घड़ी */
	अगर (setup->pci_घड़ी_max != 0)
		pci_घड़ी_max = setup->pci_घड़ी_max;
	अन्यथा
		pci_घड़ी_max = PCI_CLOCK_MAX;
	vtघड़ी = vr41xx_get_vtघड़ी_frequency();
	अगर (vtघड़ी < pci_घड़ी_max)
		pciu_ग_लिखो(PCICLKSELREG, EQUAL_VTCLOCK);
	अन्यथा अगर ((vtघड़ी / 2) < pci_घड़ी_max)
		pciu_ग_लिखो(PCICLKSELREG, HALF_VTCLOCK);
	अन्यथा अगर (current_cpu_data.processor_id >= PRID_VR4131_REV2_1 &&
		 (vtघड़ी / 3) < pci_घड़ी_max)
		pciu_ग_लिखो(PCICLKSELREG, ONE_THIRD_VTCLOCK);
	अन्यथा अगर ((vtघड़ी / 4) < pci_घड़ी_max)
		pciu_ग_लिखो(PCICLKSELREG, QUARTER_VTCLOCK);
	अन्यथा अणु
		prपूर्णांकk(KERN_ERR "PCI Clock is over 33MHz.\n");
		iounmap(pciu_base);
		वापस -EINVAL;
	पूर्ण

	/* Supply PCI घड़ी by PCI bus */
	vr41xx_supply_घड़ी(PCI_CLOCK);

	अगर (setup->master_memory1 != शून्य) अणु
		master = setup->master_memory1;
		val = IBA(master->bus_base_address) |
		      MASTER_MSK(master->address_mask) |
		      WINEN |
		      PCIA(master->pci_base_address);
		pciu_ग_लिखो(PCIMMAW1REG, val);
	पूर्ण अन्यथा अणु
		val = pciu_पढ़ो(PCIMMAW1REG);
		val &= ~WINEN;
		pciu_ग_लिखो(PCIMMAW1REG, val);
	पूर्ण

	अगर (setup->master_memory2 != शून्य) अणु
		master = setup->master_memory2;
		val = IBA(master->bus_base_address) |
		      MASTER_MSK(master->address_mask) |
		      WINEN |
		      PCIA(master->pci_base_address);
		pciu_ग_लिखो(PCIMMAW2REG, val);
	पूर्ण अन्यथा अणु
		val = pciu_पढ़ो(PCIMMAW2REG);
		val &= ~WINEN;
		pciu_ग_लिखो(PCIMMAW2REG, val);
	पूर्ण

	अगर (setup->target_memory1 != शून्य) अणु
		target = setup->target_memory1;
		val = TARGET_MSK(target->address_mask) |
		      WINEN |
		      ITA(target->bus_base_address);
		pciu_ग_लिखो(PCITAW1REG, val);
	पूर्ण अन्यथा अणु
		val = pciu_पढ़ो(PCITAW1REG);
		val &= ~WINEN;
		pciu_ग_लिखो(PCITAW1REG, val);
	पूर्ण

	अगर (setup->target_memory2 != शून्य) अणु
		target = setup->target_memory2;
		val = TARGET_MSK(target->address_mask) |
		      WINEN |
		      ITA(target->bus_base_address);
		pciu_ग_लिखो(PCITAW2REG, val);
	पूर्ण अन्यथा अणु
		val = pciu_पढ़ो(PCITAW2REG);
		val &= ~WINEN;
		pciu_ग_लिखो(PCITAW2REG, val);
	पूर्ण

	अगर (setup->master_io != शून्य) अणु
		master = setup->master_io;
		val = IBA(master->bus_base_address) |
		      MASTER_MSK(master->address_mask) |
		      WINEN |
		      PCIIA(master->pci_base_address);
		pciu_ग_लिखो(PCIMIOAWREG, val);
	पूर्ण अन्यथा अणु
		val = pciu_पढ़ो(PCIMIOAWREG);
		val &= ~WINEN;
		pciu_ग_लिखो(PCIMIOAWREG, val);
	पूर्ण

	अगर (setup->exclusive_access == CANNOT_LOCK_FROM_DEVICE)
		pciu_ग_लिखो(PCIEXACCREG, UNLOCK);
	अन्यथा
		pciu_ग_लिखो(PCIEXACCREG, 0);

	अगर (current_cpu_type() == CPU_VR4122)
		pciu_ग_लिखो(PCITRDYVREG, TRDYV(setup->रुको_समय_limit_from_irdy_to_trdy));

	pciu_ग_लिखो(LATTIMEREG, MLTIM(setup->master_latency_समयr));

	अगर (setup->mailbox != शून्य) अणु
		mailbox = setup->mailbox;
		val = MBADD(mailbox->base_address) | TYPE_32BITSPACE |
		      MSI_MEMORY | PREF_APPROVAL;
		pciu_ग_लिखो(MAILBAREG, val);
	पूर्ण

	अगर (setup->target_winकरोw1) अणु
		winकरोw = setup->target_winकरोw1;
		val = PMBA(winकरोw->base_address) | TYPE_32BITSPACE |
		      MSI_MEMORY | PREF_APPROVAL;
		pciu_ग_लिखो(PCIMBA1REG, val);
	पूर्ण

	अगर (setup->target_winकरोw2) अणु
		winकरोw = setup->target_winकरोw2;
		val = PMBA(winकरोw->base_address) | TYPE_32BITSPACE |
		      MSI_MEMORY | PREF_APPROVAL;
		pciu_ग_लिखो(PCIMBA2REG, val);
	पूर्ण

	val = pciu_पढ़ो(RETVALREG);
	val &= ~RTYVAL_MASK;
	val |= RTYVAL(setup->retry_limit);
	pciu_ग_लिखो(RETVALREG, val);

	val = pciu_पढ़ो(PCIAPCNTREG);
	val &= ~(TKYGNT | PAPC);

	चयन (setup->arbiter_priority_control) अणु
	हाल PCI_ARBITRATION_MODE_ALTERNATE_0:
		val |= PAPC_ALTERNATE_0;
		अवरोध;
	हाल PCI_ARBITRATION_MODE_ALTERNATE_B:
		val |= PAPC_ALTERNATE_B;
		अवरोध;
	शेष:
		val |= PAPC_FAIR;
		अवरोध;
	पूर्ण

	अगर (setup->take_away_gnt_mode == PCI_TAKE_AWAY_GNT_ENABLE)
		val |= TKYGNT_ENABLE;

	pciu_ग_लिखो(PCIAPCNTREG, val);

	pciu_ग_लिखो(COMMANDREG, PCI_COMMAND_IO | PCI_COMMAND_MEMORY |
			       PCI_COMMAND_MASTER | PCI_COMMAND_PARITY |
			       PCI_COMMAND_SERR);

	/* Clear bus error */
	pciu_पढ़ो(BUSERRADREG);

	pciu_ग_लिखो(PCIENREG, PCIU_CONFIG_DONE);

	अगर (setup->mem_resource != शून्य)
		vr41xx_pci_controller.mem_resource = setup->mem_resource;

	अगर (setup->io_resource != शून्य) अणु
		vr41xx_pci_controller.io_resource = setup->io_resource;
	पूर्ण अन्यथा अणु
		set_io_port_base(IO_PORT_BASE);
		ioport_resource.start = IO_PORT_RESOURCE_START;
		ioport_resource.end = IO_PORT_RESOURCE_END;
	पूर्ण

	अगर (setup->master_io) अणु
		व्योम __iomem *io_map_base;
		काष्ठा resource *res = vr41xx_pci_controller.io_resource;
		master = setup->master_io;
		io_map_base = ioremap(master->bus_base_address,
				      resource_size(res));
		अगर (!io_map_base) अणु
			iounmap(pciu_base);
			वापस -EBUSY;
		पूर्ण

		vr41xx_pci_controller.io_map_base = (अचिन्हित दीर्घ)io_map_base;
	पूर्ण

	रेजिस्टर_pci_controller(&vr41xx_pci_controller);

	वापस 0;
पूर्ण

arch_initcall(vr41xx_pciu_init);
