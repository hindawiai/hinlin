<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Common PowerQUICC II code.
 *
 * Author: Scott Wood <scottwood@मुक्तscale.com>
 * Copyright (c) 2007 Freescale Semiconductor
 *
 * Based on code by Vitaly Bordug <vbordug@ru.mvista.com>
 * pq2_restart fix by Wade Farnsworth <wfarnsworth@mvista.com>
 * Copyright (c) 2006 MontaVista Software, Inc.
 */

#समावेश <linux/kprobes.h>

#समावेश <यंत्र/cpm2.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/pci-bridge.h>

#समावेश <platक्रमms/82xx/pq2.h>

#घोषणा RMR_CSRE 0x00000001

व्योम __noवापस pq2_restart(अक्षर *cmd)
अणु
	local_irq_disable();
	setbits32(&cpm2_immr->im_clkrst.car_rmr, RMR_CSRE);

	/* Clear the ME,EE,IR & DR bits in MSR to cause checkstop */
	mपंचांगsr(mfmsr() & ~(MSR_ME | MSR_EE | MSR_IR | MSR_DR));
	in_8(&cpm2_immr->im_clkrst.res[0]);

	panic("Restart failed\n");
पूर्ण
NOKPROBE_SYMBOL(pq2_restart)

#अगर_घोषित CONFIG_PCI
अटल पूर्णांक pq2_pci_exclude_device(काष्ठा pci_controller *hose,
                                  u_अक्षर bus, u8 devfn)
अणु
	अगर (bus == 0 && PCI_SLOT(devfn) == 0)
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	अन्यथा
		वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल व्योम __init pq2_pci_add_bridge(काष्ठा device_node *np)
अणु
	काष्ठा pci_controller *hose;
	काष्ठा resource r;

	अगर (of_address_to_resource(np, 0, &r) || r.end - r.start < 0x10b)
		जाओ err;

	pci_add_flags(PCI_REASSIGN_ALL_BUS);

	hose = pcibios_alloc_controller(np);
	अगर (!hose)
		वापस;

	hose->dn = np;

	setup_indirect_pci(hose, r.start + 0x100, r.start + 0x104, 0);
	pci_process_bridge_OF_ranges(hose, np, 1);

	वापस;

err:
	prपूर्णांकk(KERN_ERR "No valid PCI reg property in device tree\n");
पूर्ण

व्योम __init pq2_init_pci(व्योम)
अणु
	काष्ठा device_node *np;

	ppc_md.pci_exclude_device = pq2_pci_exclude_device;

	क्रम_each_compatible_node(np, शून्य, "fsl,pq2-pci")
		pq2_pci_add_bridge(np);
पूर्ण
#पूर्ण_अगर
