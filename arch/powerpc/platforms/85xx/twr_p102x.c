<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2010-2011, 2013 Freescale Semiconductor, Inc.
 *
 * Author: Michael Johnston <michael.johnston@मुक्तscale.com>
 *
 * Description:
 * TWR-P102x Board Setup
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fsl/guts.h>
#समावेश <linux/pci.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/mpic.h>
#समावेश <soc/fsl/qe/qe.h>

#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>
#समावेश "smp.h"

#समावेश "mpc85xx.h"

अटल व्योम __init twr_p1025_pic_init(व्योम)
अणु
	काष्ठा mpic *mpic;

	mpic = mpic_alloc(शून्य, 0, MPIC_BIG_ENDIAN |
			MPIC_SINGLE_DEST_CPU,
			0, 256, " OpenPIC  ");

	BUG_ON(mpic == शून्य);
	mpic_init(mpic);
पूर्ण

/* ************************************************************************
 *
 * Setup the architecture
 *
 */
अटल व्योम __init twr_p1025_setup_arch(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("twr_p1025_setup_arch()", 0);

	mpc85xx_smp_init();

	fsl_pci_assign_primary();

#अगर_घोषित CONFIG_QUICC_ENGINE
	mpc85xx_qe_par_io_init();

#अगर IS_ENABLED(CONFIG_UCC_GETH) || IS_ENABLED(CONFIG_SERIAL_QE)
	अगर (machine_is(twr_p1025)) अणु
		काष्ठा ccsr_guts __iomem *guts;
		काष्ठा device_node *np;

		np = of_find_compatible_node(शून्य, शून्य, "fsl,p1021-guts");
		अगर (np) अणु
			guts = of_iomap(np, 0);
			अगर (!guts)
				pr_err("twr_p1025: could not map global utilities register\n");
			अन्यथा अणु
			/* P1025 has pins muxed क्रम QE and other functions. To
			 * enable QE UEC mode, we need to set bit QE0 क्रम UCC1
			 * in Eth mode, QE0 and QE3 क्रम UCC5 in Eth mode, QE9
			 * and QE12 क्रम QE MII management संकेतs in PMUXCR
			 * रेजिस्टर.
			 * Set QE mux bits in PMUXCR */
			setbits32(&guts->pmuxcr, MPC85xx_PMUXCR_QE(0) |
					MPC85xx_PMUXCR_QE(3) |
					MPC85xx_PMUXCR_QE(9) |
					MPC85xx_PMUXCR_QE(12));
			iounmap(guts);

#अगर IS_ENABLED(CONFIG_SERIAL_QE)
			/* On P1025TWR board, the UCC7 acted as UART port.
			 * However, The UCC7's CTS pin is low level in शेष,
			 * it will impact the transmission in full duplex
			 * communication. So disable the Flow control pin PA18.
			 * The UCC7 UART just can use RXD and TXD pins.
			 */
			par_io_config_pin(0, 18, 0, 0, 0, 0);
#पूर्ण_अगर
			/* Drive PB29 to CPLD low - CPLD will then change
			 * muxing from LBC to QE */
			par_io_config_pin(1, 29, 1, 0, 0, 0);
			par_io_data_set(1, 29, 0);
			पूर्ण
			of_node_put(np);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर	/* CONFIG_QUICC_ENGINE */

	pr_info("TWR-P1025 board from Freescale Semiconductor\n");
पूर्ण

machine_arch_initcall(twr_p1025, mpc85xx_common_publish_devices);

अटल पूर्णांक __init twr_p1025_probe(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,TWR-P1025");
पूर्ण

define_machine(twr_p1025) अणु
	.name			= "TWR-P1025",
	.probe			= twr_p1025_probe,
	.setup_arch		= twr_p1025_setup_arch,
	.init_IRQ		= twr_p1025_pic_init,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
#पूर्ण_अगर
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
