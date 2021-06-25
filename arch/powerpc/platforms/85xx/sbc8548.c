<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Wind River SBC8548 setup and early boot code.
 *
 * Copyright 2007 Wind River Systems Inc.
 *
 * By Paul Gorपंचांगaker (see MAINTAINERS क्रम contact inक्रमmation)
 *
 * Based largely on the MPC8548CDS support - Copyright 2005 Freescale Inc.
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/reboot.h>
#समावेश <linux/pci.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/major.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/initrd.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fsl_devices.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/page.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/ipic.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/irq.h>
#समावेश <mm/mmu_decl.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/mpic.h>

#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>

#समावेश "mpc85xx.h"

अटल पूर्णांक sbc_rev;

अटल व्योम __init sbc8548_pic_init(व्योम)
अणु
	काष्ठा mpic *mpic = mpic_alloc(शून्य, 0, MPIC_BIG_ENDIAN,
			0, 256, " OpenPIC  ");
	BUG_ON(mpic == शून्य);
	mpic_init(mpic);
पूर्ण

/* Extract the HW Rev from the EPLD on the board */
अटल पूर्णांक __init sbc8548_hw_rev(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा resource res;
	अचिन्हित पूर्णांक *rev;
	पूर्णांक board_rev = 0;

	np = of_find_compatible_node(शून्य, शून्य, "hw-rev");
	अगर (np == शून्य) अणु
		prपूर्णांकk("No HW-REV found in DTB.\n");
		वापस -ENODEV;
	पूर्ण

	of_address_to_resource(np, 0, &res);
	of_node_put(np);

	rev = ioremap(res.start,माप(अचिन्हित पूर्णांक));
	board_rev = (*rev) >> 28;
	iounmap(rev);

	वापस board_rev;
पूर्ण

/*
 * Setup the architecture
 */
अटल व्योम __init sbc8548_setup_arch(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("sbc8548_setup_arch()", 0);

	fsl_pci_assign_primary();

	sbc_rev = sbc8548_hw_rev();
पूर्ण

अटल व्योम sbc8548_show_cpuinfo(काष्ठा seq_file *m)
अणु
	uपूर्णांक pvid, svid, phid1;

	pvid = mfspr(SPRN_PVR);
	svid = mfspr(SPRN_SVR);

	seq_म_लिखो(m, "Vendor\t\t: Wind River\n");
	seq_म_लिखो(m, "Machine\t\t: SBC8548 v%d\n", sbc_rev);
	seq_म_लिखो(m, "PVR\t\t: 0x%x\n", pvid);
	seq_म_लिखो(m, "SVR\t\t: 0x%x\n", svid);

	/* Display cpu Pll setting */
	phid1 = mfspr(SPRN_HID1);
	seq_म_लिखो(m, "PLL setting\t: 0x%x\n", ((phid1 >> 24) & 0x3f));
पूर्ण

machine_arch_initcall(sbc8548, mpc85xx_common_publish_devices);

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init sbc8548_probe(व्योम)
अणु
	वापस of_machine_is_compatible("SBC8548");
पूर्ण

define_machine(sbc8548) अणु
	.name		= "SBC8548",
	.probe		= sbc8548_probe,
	.setup_arch	= sbc8548_setup_arch,
	.init_IRQ	= sbc8548_pic_init,
	.show_cpuinfo	= sbc8548_show_cpuinfo,
	.get_irq	= mpic_get_irq,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
	.calibrate_decr = generic_calibrate_decr,
	.progress	= udbg_progress,
पूर्ण;
