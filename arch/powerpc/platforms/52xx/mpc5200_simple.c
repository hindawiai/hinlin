<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Support क्रम 'mpc5200-simple-platform' compatible boards.
 *
 * Written by Marian Balakowicz <m8@semihalf.com>
 * Copyright (C) 2007 Semihalf
 *
 * Description:
 * This code implements support क्रम a simple MPC52xx based boards which
 * करो not need a custom platक्रमm specअगरic setup. Such boards are
 * supported assuming the following:
 *
 * - GPIO pins are configured by the firmware,
 * - CDM configuration (घड़ीing) is setup correctly by firmware,
 * - अगर the 'fsl,has-wdt' property is present in one of the
 *   gpt nodes, then it is safe to use such gpt to reset the board,
 * - PCI is supported अगर enabled in the kernel configuration
 *   and अगर there is a PCI bus node defined in the device tree.
 *
 * Boards that are compatible with this generic platक्रमm support
 * are listed in a 'board' table.
 */

#अघोषित DEBUG
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/mpc52xx.h>

/*
 * Setup the architecture
 */
अटल व्योम __init mpc5200_simple_setup_arch(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("mpc5200_simple_setup_arch()", 0);

	/* Map important रेजिस्टरs from the पूर्णांकernal memory map */
	mpc52xx_map_common_devices();

	/* Some mpc5200 & mpc5200b related configuration */
	mpc5200_setup_xlb_arbiter();
पूर्ण

/* list of the supported boards */
अटल स्थिर अक्षर *board[] __initdata = अणु
	"anonymous,a3m071",
	"anonymous,a4m072",
	"anon,charon",
	"ifm,o2d",
	"intercontrol,digsy-mtc",
	"manroland,mucmc52",
	"manroland,uc101",
	"phytec,pcm030",
	"phytec,pcm032",
	"promess,motionpro",
	"schindler,cm5200",
	"tqc,tqm5200",
	शून्य
पूर्ण;

/*
 * Called very early, MMU is off, device-tree isn't unflattened
 */
अटल पूर्णांक __init mpc5200_simple_probe(व्योम)
अणु
	वापस of_device_compatible_match(of_root, board);
पूर्ण

define_machine(mpc5200_simple_platक्रमm) अणु
	.name		= "mpc5200-simple-platform",
	.probe		= mpc5200_simple_probe,
	.setup_arch	= mpc5200_simple_setup_arch,
	.discover_phbs	= mpc52xx_setup_pci,
	.init		= mpc52xx_declare_of_platक्रमm_devices,
	.init_IRQ	= mpc52xx_init_irq,
	.get_irq	= mpc52xx_get_irq,
	.restart	= mpc52xx_restart,
	.calibrate_decr	= generic_calibrate_decr,
पूर्ण;
