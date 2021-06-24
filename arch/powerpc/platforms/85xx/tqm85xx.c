<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Based on MPC8560 ADS and arch/ppc tqm85xx ports
 *
 * Maपूर्णांकained by Kumar Gala (see MAINTAINERS क्रम contact inक्रमmation)
 *
 * Copyright 2008 Freescale Semiconductor Inc.
 *
 * Copyright (c) 2005-2006 DENX Software Engineering
 * Stefan Roese <sr@denx.de>
 *
 * Based on original work by
 * 	Kumar Gala <kumar.gala@मुक्तscale.com>
 *      Copyright 2004 Freescale Semiconductor Inc.
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

अटल व्योम __init tqm85xx_pic_init(व्योम)
अणु
	काष्ठा mpic *mpic = mpic_alloc(शून्य, 0,
			MPIC_BIG_ENDIAN,
			0, 256, " OpenPIC  ");
	BUG_ON(mpic == शून्य);
	mpic_init(mpic);

	mpc85xx_cpm2_pic_init();
पूर्ण

/*
 * Setup the architecture
 */
अटल व्योम __init tqm85xx_setup_arch(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("tqm85xx_setup_arch()", 0);

#अगर_घोषित CONFIG_CPM2
	cpm2_reset();
#पूर्ण_अगर

	fsl_pci_assign_primary();
पूर्ण

अटल व्योम tqm85xx_show_cpuinfo(काष्ठा seq_file *m)
अणु
	uपूर्णांक pvid, svid, phid1;

	pvid = mfspr(SPRN_PVR);
	svid = mfspr(SPRN_SVR);

	seq_म_लिखो(m, "Vendor\t\t: TQ Components\n");
	seq_म_लिखो(m, "PVR\t\t: 0x%x\n", pvid);
	seq_म_लिखो(m, "SVR\t\t: 0x%x\n", svid);

	/* Display cpu Pll setting */
	phid1 = mfspr(SPRN_HID1);
	seq_म_लिखो(m, "PLL setting\t: 0x%x\n", ((phid1 >> 24) & 0x3f));
पूर्ण

अटल व्योम tqm85xx_ti1520_fixup(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित पूर्णांक val;

	/* Do not करो the fixup on other platक्रमms! */
	अगर (!machine_is(tqm85xx))
		वापस;

	dev_info(&pdev->dev, "Using TI 1520 fixup on TQM85xx\n");

	/*
	 * Enable P2CCLK bit in प्रणाली control रेजिस्टर
	 * to enable CLOCK output to घातer chip
	 */
	pci_पढ़ो_config_dword(pdev, 0x80, &val);
	pci_ग_लिखो_config_dword(pdev, 0x80, val | (1 << 27));

पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_1520,
		tqm85xx_ti1520_fixup);

machine_arch_initcall(tqm85xx, mpc85xx_common_publish_devices);

अटल स्थिर अक्षर * स्थिर board[] __initस्थिर = अणु
	"tqc,tqm8540",
	"tqc,tqm8541",
	"tqc,tqm8548",
	"tqc,tqm8555",
	"tqc,tqm8560",
	शून्य
पूर्ण;

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init tqm85xx_probe(व्योम)
अणु
	वापस of_device_compatible_match(of_root, board);
पूर्ण

define_machine(tqm85xx) अणु
	.name			= "TQM85xx",
	.probe			= tqm85xx_probe,
	.setup_arch		= tqm85xx_setup_arch,
	.init_IRQ		= tqm85xx_pic_init,
	.show_cpuinfo		= tqm85xx_show_cpuinfo,
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
