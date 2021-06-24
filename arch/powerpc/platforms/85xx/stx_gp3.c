<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Based on MPC8560 ADS and arch/ppc stx_gp3 ports
 *
 * Maपूर्णांकained by Kumar Gala (see MAINTAINERS क्रम contact inक्रमmation)
 *
 * Copyright 2008 Freescale Semiconductor Inc.
 *
 * Dan Malek <dan@embeddededge.com>
 * Copyright 2004 Embedded Edge, LLC
 *
 * Copied from mpc8560_ads.c
 * Copyright 2002, 2003 Motorola Inc.
 *
 * Ported to 2.6, Matt Porter <mporter@kernel.crashing.org>
 * Copyright 2004-2005 MontaVista Software, Inc.
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
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/prom.h>
#समावेश <mm/mmu_decl.h>
#समावेश <यंत्र/udbg.h>

#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>

#समावेश "mpc85xx.h"

#अगर_घोषित CONFIG_CPM2
#समावेश <यंत्र/cpm2.h>
#पूर्ण_अगर /* CONFIG_CPM2 */

अटल व्योम __init stx_gp3_pic_init(व्योम)
अणु
	काष्ठा mpic *mpic = mpic_alloc(शून्य, 0, MPIC_BIG_ENDIAN,
			0, 256, " OpenPIC  ");
	BUG_ON(mpic == शून्य);
	mpic_init(mpic);

	mpc85xx_cpm2_pic_init();
पूर्ण

/*
 * Setup the architecture
 */
अटल व्योम __init stx_gp3_setup_arch(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("stx_gp3_setup_arch()", 0);

	fsl_pci_assign_primary();

#अगर_घोषित CONFIG_CPM2
	cpm2_reset();
#पूर्ण_अगर
पूर्ण

अटल व्योम stx_gp3_show_cpuinfo(काष्ठा seq_file *m)
अणु
	uपूर्णांक pvid, svid, phid1;

	pvid = mfspr(SPRN_PVR);
	svid = mfspr(SPRN_SVR);

	seq_म_लिखो(m, "Vendor\t\t: RPC Electronics STx\n");
	seq_म_लिखो(m, "PVR\t\t: 0x%x\n", pvid);
	seq_म_लिखो(m, "SVR\t\t: 0x%x\n", svid);

	/* Display cpu Pll setting */
	phid1 = mfspr(SPRN_HID1);
	seq_म_लिखो(m, "PLL setting\t: 0x%x\n", ((phid1 >> 24) & 0x3f));
पूर्ण

machine_arch_initcall(stx_gp3, mpc85xx_common_publish_devices);

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init stx_gp3_probe(व्योम)
अणु
	वापस of_machine_is_compatible("stx,gp3-8560");
पूर्ण

define_machine(stx_gp3) अणु
	.name			= "STX GP3",
	.probe			= stx_gp3_probe,
	.setup_arch		= stx_gp3_setup_arch,
	.init_IRQ		= stx_gp3_pic_init,
	.show_cpuinfo		= stx_gp3_show_cpuinfo,
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
