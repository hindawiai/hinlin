<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MPC85xx setup and early boot code plus other अक्रमom bits.
 *
 * Maपूर्णांकained by Kumar Gala (see MAINTAINERS क्रम contact inक्रमmation)
 *
 * Copyright 2005 Freescale Semiconductor Inc.
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
#समावेश <mm/mmu_decl.h>
#समावेश <यंत्र/udbg.h>

#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>

#अगर_घोषित CONFIG_CPM2
#समावेश <यंत्र/cpm2.h>
#समावेश <sysdev/cpm2_pic.h>
#पूर्ण_अगर

#समावेश "mpc85xx.h"

अटल व्योम __init mpc85xx_ads_pic_init(व्योम)
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
#अगर_घोषित CONFIG_CPM2
काष्ठा cpm_pin अणु
	पूर्णांक port, pin, flags;
पूर्ण;

अटल स्थिर काष्ठा cpm_pin mpc8560_ads_pins[] = अणु
	/* SCC1 */
	अणु3, 29, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु3, 30, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु3, 31, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,

	/* SCC2 */
	अणु2, 12, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2, 13, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु3, 26, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु3, 27, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु3, 28, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,

	/* FCC2 */
	अणु1, 18, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 19, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 20, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 21, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 22, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 23, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 24, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 25, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 26, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 27, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 28, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 29, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु1, 30, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 31, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2, 18, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण, /* CLK14 */
	अणु2, 19, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण, /* CLK13 */

	/* FCC3 */
	अणु1, 4, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 5, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 6, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 8, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 9, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 10, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 11, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 12, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 13, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 14, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 15, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 16, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु1, 17, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु2, 16, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण, /* CLK16 */
	अणु2, 17, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण, /* CLK15 */
	अणु2, 27, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
पूर्ण;

अटल व्योम __init init_ioports(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mpc8560_ads_pins); i++) अणु
		स्थिर काष्ठा cpm_pin *pin = &mpc8560_ads_pins[i];
		cpm2_set_pin(pin->port, pin->pin, pin->flags);
	पूर्ण

	cpm2_clk_setup(CPM_CLK_SCC1, CPM_BRG1, CPM_CLK_RX);
	cpm2_clk_setup(CPM_CLK_SCC1, CPM_BRG1, CPM_CLK_TX);
	cpm2_clk_setup(CPM_CLK_SCC2, CPM_BRG2, CPM_CLK_RX);
	cpm2_clk_setup(CPM_CLK_SCC2, CPM_BRG2, CPM_CLK_TX);
	cpm2_clk_setup(CPM_CLK_FCC2, CPM_CLK13, CPM_CLK_RX);
	cpm2_clk_setup(CPM_CLK_FCC2, CPM_CLK14, CPM_CLK_TX);
	cpm2_clk_setup(CPM_CLK_FCC3, CPM_CLK15, CPM_CLK_RX);
	cpm2_clk_setup(CPM_CLK_FCC3, CPM_CLK16, CPM_CLK_TX);
पूर्ण
#पूर्ण_अगर

अटल व्योम __init mpc85xx_ads_setup_arch(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("mpc85xx_ads_setup_arch()", 0);

#अगर_घोषित CONFIG_CPM2
	cpm2_reset();
	init_ioports();
#पूर्ण_अगर

	fsl_pci_assign_primary();
पूर्ण

अटल व्योम mpc85xx_ads_show_cpuinfo(काष्ठा seq_file *m)
अणु
	uपूर्णांक pvid, svid, phid1;

	pvid = mfspr(SPRN_PVR);
	svid = mfspr(SPRN_SVR);

	seq_म_लिखो(m, "Vendor\t\t: Freescale Semiconductor\n");
	seq_म_लिखो(m, "PVR\t\t: 0x%x\n", pvid);
	seq_म_लिखो(m, "SVR\t\t: 0x%x\n", svid);

	/* Display cpu Pll setting */
	phid1 = mfspr(SPRN_HID1);
	seq_म_लिखो(m, "PLL setting\t: 0x%x\n", ((phid1 >> 24) & 0x3f));
पूर्ण

machine_arch_initcall(mpc85xx_ads, mpc85xx_common_publish_devices);

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init mpc85xx_ads_probe(व्योम)
अणु
	वापस of_machine_is_compatible("MPC85xxADS");
पूर्ण

define_machine(mpc85xx_ads) अणु
	.name			= "MPC85xx ADS",
	.probe			= mpc85xx_ads_probe,
	.setup_arch		= mpc85xx_ads_setup_arch,
	.init_IRQ		= mpc85xx_ads_pic_init,
	.show_cpuinfo		= mpc85xx_ads_show_cpuinfo,
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
