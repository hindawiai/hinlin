<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vSMPowered(पंचांग) प्रणालीs specअगरic initialization
 * Copyright (C) 2005 ScaleMP Inc.
 *
 * Ravikiran Thirumalai <kiran@scalemp.com>,
 * Shai Fultheim <shai@scalemp.com>
 * Paravirt ops पूर्णांकegration: Glauber de Oliveira Costa <gcosta@redhat.com>,
 *			     Ravikiran Thirumalai <kiran@scalemp.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/pci_regs.h>
#समावेश <linux/smp.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/pci-direct.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/paravirt.h>
#समावेश <यंत्र/setup.h>

#घोषणा TOPOLOGY_REGISTER_OFFSET 0x10

#अगर_घोषित CONFIG_PCI
अटल व्योम __init set_vsmp_ctl(व्योम)
अणु
	व्योम __iomem *address;
	अचिन्हित पूर्णांक cap, ctl, cfg;

	/* set vSMP magic bits to indicate vSMP capable kernel */
	cfg = पढ़ो_pci_config(0, 0x1f, 0, PCI_BASE_ADDRESS_0);
	address = early_ioremap(cfg, 8);
	cap = पढ़ोl(address);
	ctl = पढ़ोl(address + 4);
	prपूर्णांकk(KERN_INFO "vSMP CTL: capabilities:0x%08x  control:0x%08x\n",
	       cap, ctl);

	/* If possible, let the vSMP foundation route the पूर्णांकerrupt optimally */
#अगर_घोषित CONFIG_SMP
	अगर (cap & ctl & BIT(8)) अणु
		ctl &= ~BIT(8);

#अगर_घोषित CONFIG_PROC_FS
		/* Don't let users change irq affinity via procfs */
		no_irq_affinity = 1;
#पूर्ण_अगर
	पूर्ण
#पूर्ण_अगर

	ग_लिखोl(ctl, address + 4);
	ctl = पढ़ोl(address + 4);
	pr_info("vSMP CTL: control set to:0x%08x\n", ctl);

	early_iounmap(address, 8);
पूर्ण
अटल पूर्णांक is_vsmp = -1;

अटल व्योम __init detect_vsmp_box(व्योम)
अणु
	is_vsmp = 0;

	अगर (!early_pci_allowed())
		वापस;

	/* Check अगर we are running on a ScaleMP vSMPowered box */
	अगर (पढ़ो_pci_config(0, 0x1f, 0, PCI_VENDOR_ID) ==
	     (PCI_VENDOR_ID_SCALEMP | (PCI_DEVICE_ID_SCALEMP_VSMP_CTL << 16)))
		is_vsmp = 1;
पूर्ण

अटल पूर्णांक is_vsmp_box(व्योम)
अणु
	अगर (is_vsmp != -1)
		वापस is_vsmp;
	अन्यथा अणु
		WARN_ON_ONCE(1);
		वापस 0;
	पूर्ण
पूर्ण

#अन्यथा
अटल व्योम __init detect_vsmp_box(व्योम)
अणु
पूर्ण
अटल पूर्णांक is_vsmp_box(व्योम)
अणु
	वापस 0;
पूर्ण
अटल व्योम __init set_vsmp_ctl(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम __init vsmp_cap_cpus(व्योम)
अणु
#अगर !defined(CONFIG_X86_VSMP) && defined(CONFIG_SMP) && defined(CONFIG_PCI)
	व्योम __iomem *address;
	अचिन्हित पूर्णांक cfg, topology, node_shअगरt, maxcpus;

	/*
	 * CONFIG_X86_VSMP is not configured, so limit the number CPUs to the
	 * ones present in the first board, unless explicitly overridden by
	 * setup_max_cpus
	 */
	अगर (setup_max_cpus != NR_CPUS)
		वापस;

	/* Read the vSMP Foundation topology रेजिस्टर */
	cfg = पढ़ो_pci_config(0, 0x1f, 0, PCI_BASE_ADDRESS_0);
	address = early_ioremap(cfg + TOPOLOGY_REGISTER_OFFSET, 4);
	अगर (WARN_ON(!address))
		वापस;

	topology = पढ़ोl(address);
	node_shअगरt = (topology >> 16) & 0x7;
	अगर (!node_shअगरt)
		/* The value 0 should be decoded as 8 */
		node_shअगरt = 8;
	maxcpus = (topology & ((1 << node_shअगरt) - 1)) + 1;

	pr_info("vSMP CTL: Capping CPUs to %d (CONFIG_X86_VSMP is unset)\n",
		maxcpus);
	setup_max_cpus = maxcpus;
	early_iounmap(address, 4);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक apicid_phys_pkg_id(पूर्णांक initial_apic_id, पूर्णांक index_msb)
अणु
	वापस hard_smp_processor_id() >> index_msb;
पूर्ण

अटल व्योम vsmp_apic_post_init(व्योम)
अणु
	/* need to update phys_pkg_id */
	apic->phys_pkg_id = apicid_phys_pkg_id;
पूर्ण

व्योम __init vsmp_init(व्योम)
अणु
	detect_vsmp_box();
	अगर (!is_vsmp_box())
		वापस;

	x86_platक्रमm.apic_post_init = vsmp_apic_post_init;

	vsmp_cap_cpus();

	set_vsmp_ctl();
	वापस;
पूर्ण
