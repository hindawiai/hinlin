<शैली गुरु>
/*
 * Board setup routines क्रम the Emerson KSI8560
 *
 * Author: Alexandr Smirnov <यंत्रirnov@ru.mvista.com>
 *
 * Based on mpc85xx_ads.c मुख्यtained by Kumar Gala
 *
 * 2008 (c) MontaVista, Software, Inc.  This file is licensed under
 * the terms of the GNU General Public License version 2.  This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 *
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
#समावेश <यंत्र/prom.h>

#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>

#समावेश <यंत्र/cpm2.h>
#समावेश <sysdev/cpm2_pic.h>

#समावेश "mpc85xx.h"

#घोषणा KSI8560_CPLD_HVR		0x04 /* Hardware Version Register */
#घोषणा KSI8560_CPLD_PVR		0x08 /* PLD Version Register */
#घोषणा KSI8560_CPLD_RCR1		0x30 /* Reset Command Register 1 */

#घोषणा KSI8560_CPLD_RCR1_CPUHR		0x80 /* CPU Hard Reset */

अटल व्योम __iomem *cpld_base = शून्य;

अटल व्योम __noवापस machine_restart(अक्षर *cmd)
अणु
	अगर (cpld_base)
		out_8(cpld_base + KSI8560_CPLD_RCR1, KSI8560_CPLD_RCR1_CPUHR);
	अन्यथा
		prपूर्णांकk(KERN_ERR "Can't find CPLD base, hang forever\n");

	क्रम (;;);
पूर्ण

अटल व्योम __init ksi8560_pic_init(व्योम)
अणु
	काष्ठा mpic *mpic = mpic_alloc(शून्य, 0, MPIC_BIG_ENDIAN,
			0, 256, " OpenPIC  ");
	BUG_ON(mpic == शून्य);
	mpic_init(mpic);

	mpc85xx_cpm2_pic_init();
पूर्ण

#अगर_घोषित CONFIG_CPM2
/*
 * Setup I/O ports
 */
काष्ठा cpm_pin अणु
	पूर्णांक port, pin, flags;
पूर्ण;

अटल काष्ठा cpm_pin __initdata ksi8560_pins[] = अणु
	/* SCC1 */
	अणु3, 29, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु3, 30, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु3, 31, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,

	/* SCC2 */
	अणु3, 26, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु3, 27, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु3, 28, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,

	/* FCC1 */
	अणु0, 14, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु0, 15, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु0, 16, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु0, 17, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु0, 18, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु0, 19, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु0, 20, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु0, 21, CPM_PIN_OUTPUT | CPM_PIN_PRIMARYपूर्ण,
	अणु0, 26, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु0, 27, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु0, 28, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु0, 29, CPM_PIN_OUTPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु0, 30, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु0, 31, CPM_PIN_INPUT | CPM_PIN_SECONDARYपूर्ण,
	अणु2, 23, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण, /* CLK9 */
	अणु2, 22, CPM_PIN_INPUT | CPM_PIN_PRIMARYपूर्ण, /* CLK10 */

पूर्ण;

अटल व्योम __init init_ioports(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ksi8560_pins); i++) अणु
		काष्ठा cpm_pin *pin = &ksi8560_pins[i];
		cpm2_set_pin(pin->port, pin->pin, pin->flags);
	पूर्ण

	cpm2_clk_setup(CPM_CLK_SCC1, CPM_BRG1, CPM_CLK_RX);
	cpm2_clk_setup(CPM_CLK_SCC1, CPM_BRG1, CPM_CLK_TX);
	cpm2_clk_setup(CPM_CLK_SCC2, CPM_BRG2, CPM_CLK_RX);
	cpm2_clk_setup(CPM_CLK_SCC2, CPM_BRG2, CPM_CLK_TX);
	cpm2_clk_setup(CPM_CLK_FCC1, CPM_CLK9, CPM_CLK_RX);
	cpm2_clk_setup(CPM_CLK_FCC1, CPM_CLK10, CPM_CLK_TX);
पूर्ण
#पूर्ण_अगर

/*
 * Setup the architecture
 */
अटल व्योम __init ksi8560_setup_arch(व्योम)
अणु
	काष्ठा device_node *cpld;

	cpld = of_find_compatible_node(शून्य, शून्य, "emerson,KSI8560-cpld");
	अगर (cpld)
		cpld_base = of_iomap(cpld, 0);
	अन्यथा
		prपूर्णांकk(KERN_ERR "Can't find CPLD in device tree\n");

	अगर (ppc_md.progress)
		ppc_md.progress("ksi8560_setup_arch()", 0);

#अगर_घोषित CONFIG_CPM2
	cpm2_reset();
	init_ioports();
#पूर्ण_अगर
पूर्ण

अटल व्योम ksi8560_show_cpuinfo(काष्ठा seq_file *m)
अणु
	uपूर्णांक pvid, svid, phid1;

	pvid = mfspr(SPRN_PVR);
	svid = mfspr(SPRN_SVR);

	seq_म_लिखो(m, "Vendor\t\t: Emerson Network Power\n");
	seq_म_लिखो(m, "Board\t\t: KSI8560\n");

	अगर (cpld_base) अणु
		seq_म_लिखो(m, "Hardware rev\t: %d\n",
					in_8(cpld_base + KSI8560_CPLD_HVR));
		seq_म_लिखो(m, "CPLD rev\t: %d\n",
					in_8(cpld_base + KSI8560_CPLD_PVR));
	पूर्ण अन्यथा
		seq_म_लिखो(m, "Unknown Hardware and CPLD revs\n");

	seq_म_लिखो(m, "PVR\t\t: 0x%x\n", pvid);
	seq_म_लिखो(m, "SVR\t\t: 0x%x\n", svid);

	/* Display cpu Pll setting */
	phid1 = mfspr(SPRN_HID1);
	seq_म_लिखो(m, "PLL setting\t: 0x%x\n", ((phid1 >> 24) & 0x3f));
पूर्ण

machine_device_initcall(ksi8560, mpc85xx_common_publish_devices);

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init ksi8560_probe(व्योम)
अणु
	वापस of_machine_is_compatible("emerson,KSI8560");
पूर्ण

define_machine(ksi8560) अणु
	.name			= "KSI8560",
	.probe			= ksi8560_probe,
	.setup_arch		= ksi8560_setup_arch,
	.init_IRQ		= ksi8560_pic_init,
	.show_cpuinfo		= ksi8560_show_cpuinfo,
	.get_irq		= mpic_get_irq,
	.restart		= machine_restart,
	.calibrate_decr		= generic_calibrate_decr,
पूर्ण;
