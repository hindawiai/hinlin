<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MPC86xx HPCN board specअगरic routines
 *
 * Recode: ZHANG WEI <wei.zhang@मुक्तscale.com>
 * Initial author: Xianghua Xiao <x.xiao@मुक्तscale.com>
 *
 * Copyright 2006 Freescale Semiconductor Inc.
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/delay.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/prom.h>
#समावेश <mm/mmu_decl.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/swiotlb.h>

#समावेश <यंत्र/mpic.h>

#समावेश <sysdev/fsl_pci.h>
#समावेश <sysdev/fsl_soc.h>

#समावेश "mpc86xx.h"

#अघोषित DEBUG

#अगर_घोषित DEBUG
#घोषणा DBG(fmt...) करो अणु prपूर्णांकk(KERN_ERR fmt); पूर्ण जबतक(0)
#अन्यथा
#घोषणा DBG(fmt...) करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI
बाह्य पूर्णांक uli_exclude_device(काष्ठा pci_controller *hose,
				u_अक्षर bus, u_अक्षर devfn);

अटल पूर्णांक mpc86xx_exclude_device(काष्ठा pci_controller *hose,
				   u_अक्षर bus, u_अक्षर devfn)
अणु
	अगर (hose->dn == fsl_pci_primary)
		वापस uli_exclude_device(hose, bus, devfn);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI */


अटल व्योम __init
mpc86xx_hpcn_setup_arch(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("mpc86xx_hpcn_setup_arch()", 0);

#अगर_घोषित CONFIG_PCI
	ppc_md.pci_exclude_device = mpc86xx_exclude_device;
#पूर्ण_अगर

	prपूर्णांकk("MPC86xx HPCN board from Freescale Semiconductor\n");

#अगर_घोषित CONFIG_SMP
	mpc86xx_smp_init();
#पूर्ण_अगर

	fsl_pci_assign_primary();

	swiotlb_detect_4g();
पूर्ण


अटल व्योम
mpc86xx_hpcn_show_cpuinfo(काष्ठा seq_file *m)
अणु
	uपूर्णांक svid = mfspr(SPRN_SVR);

	seq_म_लिखो(m, "Vendor\t\t: Freescale Semiconductor\n");

	seq_म_लिखो(m, "SVR\t\t: 0x%x\n", svid);
पूर्ण


/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init mpc86xx_hpcn_probe(व्योम)
अणु
	अगर (of_machine_is_compatible("fsl,mpc8641hpcn"))
		वापस 1;	/* Looks good */

	/* Be nice and करोn't give silent boot death.  Delete this in 2.6.27 */
	अगर (of_machine_is_compatible("mpc86xx")) अणु
		pr_warn("WARNING: your dts/dtb is old. You must update before the next kernel release.\n");
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_bus_ids[] __initस्थिर = अणु
	अणु .compatible = "fsl,srio", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init declare_of_platक्रमm_devices(व्योम)
अणु
	mpc86xx_common_publish_devices();
	of_platक्रमm_bus_probe(शून्य, of_bus_ids, शून्य);

	वापस 0;
पूर्ण
machine_arch_initcall(mpc86xx_hpcn, declare_of_platक्रमm_devices);

define_machine(mpc86xx_hpcn) अणु
	.name			= "MPC86xx HPCN",
	.probe			= mpc86xx_hpcn_probe,
	.setup_arch		= mpc86xx_hpcn_setup_arch,
	.init_IRQ		= mpc86xx_init_irq,
	.show_cpuinfo		= mpc86xx_hpcn_show_cpuinfo,
	.get_irq		= mpic_get_irq,
	.समय_init		= mpc86xx_समय_init,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
#पूर्ण_अगर
पूर्ण;
