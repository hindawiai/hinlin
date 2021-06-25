<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MPC85xx RDB Board Setup
 *
 * Copyright 2009,2012-2013 Freescale Semiconductor Inc.
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/delay.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/fsl/guts.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <mm/mmu_decl.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/mpic.h>
#समावेश <soc/fsl/qe/qe.h>

#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>
#समावेश "smp.h"

#समावेश "mpc85xx.h"

#अघोषित DEBUG

#अगर_घोषित DEBUG
#घोषणा DBG(fmt, args...) prपूर्णांकk(KERN_ERR "%s: " fmt, __func__, ## args)
#अन्यथा
#घोषणा DBG(fmt, args...)
#पूर्ण_अगर


व्योम __init mpc85xx_rdb_pic_init(व्योम)
अणु
	काष्ठा mpic *mpic;

	अगर (of_machine_is_compatible("fsl,MPC85XXRDB-CAMP")) अणु
		mpic = mpic_alloc(शून्य, 0, MPIC_NO_RESET |
			MPIC_BIG_ENDIAN |
			MPIC_SINGLE_DEST_CPU,
			0, 256, " OpenPIC  ");
	पूर्ण अन्यथा अणु
		mpic = mpic_alloc(शून्य, 0,
		  MPIC_BIG_ENDIAN |
		  MPIC_SINGLE_DEST_CPU,
		  0, 256, " OpenPIC  ");
	पूर्ण

	BUG_ON(mpic == शून्य);
	mpic_init(mpic);
पूर्ण

/*
 * Setup the architecture
 */
अटल व्योम __init mpc85xx_rdb_setup_arch(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("mpc85xx_rdb_setup_arch()", 0);

	mpc85xx_smp_init();

	fsl_pci_assign_primary();

#अगर_घोषित CONFIG_QUICC_ENGINE
	mpc85xx_qe_par_io_init();
#अगर defined(CONFIG_UCC_GETH) || defined(CONFIG_SERIAL_QE)
	अगर (machine_is(p1025_rdb)) अणु
		काष्ठा device_node *np;

		काष्ठा ccsr_guts __iomem *guts;

		np = of_find_node_by_name(शून्य, "global-utilities");
		अगर (np) अणु
			guts = of_iomap(np, 0);
			अगर (!guts) अणु

				pr_err("mpc85xx-rdb: could not map global utilities register\n");

			पूर्ण अन्यथा अणु
			/* P1025 has pins muxed क्रम QE and other functions. To
			* enable QE UEC mode, we need to set bit QE0 क्रम UCC1
			* in Eth mode, QE0 and QE3 क्रम UCC5 in Eth mode, QE9
			* and QE12 क्रम QE MII management singals in PMUXCR
			* रेजिस्टर.
			*/
				setbits32(&guts->pmuxcr, MPC85xx_PMUXCR_QE(0) |
						MPC85xx_PMUXCR_QE(3) |
						MPC85xx_PMUXCR_QE(9) |
						MPC85xx_PMUXCR_QE(12));
				iounmap(guts);
			पूर्ण
			of_node_put(np);
		पूर्ण

	पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर	/* CONFIG_QUICC_ENGINE */

	prपूर्णांकk(KERN_INFO "MPC85xx RDB board from Freescale Semiconductor\n");
पूर्ण

machine_arch_initcall(p2020_rdb, mpc85xx_common_publish_devices);
machine_arch_initcall(p2020_rdb_pc, mpc85xx_common_publish_devices);
machine_arch_initcall(p1020_mbg_pc, mpc85xx_common_publish_devices);
machine_arch_initcall(p1020_rdb, mpc85xx_common_publish_devices);
machine_arch_initcall(p1020_rdb_pc, mpc85xx_common_publish_devices);
machine_arch_initcall(p1020_rdb_pd, mpc85xx_common_publish_devices);
machine_arch_initcall(p1020_uपंचांग_pc, mpc85xx_common_publish_devices);
machine_arch_initcall(p1021_rdb_pc, mpc85xx_common_publish_devices);
machine_arch_initcall(p1025_rdb, mpc85xx_common_publish_devices);
machine_arch_initcall(p1024_rdb, mpc85xx_common_publish_devices);

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init p2020_rdb_probe(व्योम)
अणु
	अगर (of_machine_is_compatible("fsl,P2020RDB"))
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक __init p1020_rdb_probe(व्योम)
अणु
	अगर (of_machine_is_compatible("fsl,P1020RDB"))
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक __init p1020_rdb_pc_probe(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,P1020RDB-PC");
पूर्ण

अटल पूर्णांक __init p1020_rdb_pd_probe(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,P1020RDB-PD");
पूर्ण

अटल पूर्णांक __init p1021_rdb_pc_probe(व्योम)
अणु
	अगर (of_machine_is_compatible("fsl,P1021RDB-PC"))
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक __init p2020_rdb_pc_probe(व्योम)
अणु
	अगर (of_machine_is_compatible("fsl,P2020RDB-PC"))
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक __init p1025_rdb_probe(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,P1025RDB");
पूर्ण

अटल पूर्णांक __init p1020_mbg_pc_probe(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,P1020MBG-PC");
पूर्ण

अटल पूर्णांक __init p1020_uपंचांग_pc_probe(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,P1020UTM-PC");
पूर्ण

अटल पूर्णांक __init p1024_rdb_probe(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,P1024RDB");
पूर्ण

define_machine(p2020_rdb) अणु
	.name			= "P2020 RDB",
	.probe			= p2020_rdb_probe,
	.setup_arch		= mpc85xx_rdb_setup_arch,
	.init_IRQ		= mpc85xx_rdb_pic_init,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;

define_machine(p1020_rdb) अणु
	.name			= "P1020 RDB",
	.probe			= p1020_rdb_probe,
	.setup_arch		= mpc85xx_rdb_setup_arch,
	.init_IRQ		= mpc85xx_rdb_pic_init,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;

define_machine(p1021_rdb_pc) अणु
	.name			= "P1021 RDB-PC",
	.probe			= p1021_rdb_pc_probe,
	.setup_arch		= mpc85xx_rdb_setup_arch,
	.init_IRQ		= mpc85xx_rdb_pic_init,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;

define_machine(p2020_rdb_pc) अणु
	.name			= "P2020RDB-PC",
	.probe			= p2020_rdb_pc_probe,
	.setup_arch		= mpc85xx_rdb_setup_arch,
	.init_IRQ		= mpc85xx_rdb_pic_init,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;

define_machine(p1025_rdb) अणु
	.name			= "P1025 RDB",
	.probe			= p1025_rdb_probe,
	.setup_arch		= mpc85xx_rdb_setup_arch,
	.init_IRQ		= mpc85xx_rdb_pic_init,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;

define_machine(p1020_mbg_pc) अणु
	.name			= "P1020 MBG-PC",
	.probe			= p1020_mbg_pc_probe,
	.setup_arch		= mpc85xx_rdb_setup_arch,
	.init_IRQ		= mpc85xx_rdb_pic_init,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;

define_machine(p1020_uपंचांग_pc) अणु
	.name			= "P1020 UTM-PC",
	.probe			= p1020_uपंचांग_pc_probe,
	.setup_arch		= mpc85xx_rdb_setup_arch,
	.init_IRQ		= mpc85xx_rdb_pic_init,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;

define_machine(p1020_rdb_pc) अणु
	.name			= "P1020RDB-PC",
	.probe			= p1020_rdb_pc_probe,
	.setup_arch		= mpc85xx_rdb_setup_arch,
	.init_IRQ		= mpc85xx_rdb_pic_init,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;

define_machine(p1020_rdb_pd) अणु
	.name			= "P1020RDB-PD",
	.probe			= p1020_rdb_pd_probe,
	.setup_arch		= mpc85xx_rdb_setup_arch,
	.init_IRQ		= mpc85xx_rdb_pic_init,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;

define_machine(p1024_rdb) अणु
	.name			= "P1024 RDB",
	.probe			= p1024_rdb_probe,
	.setup_arch		= mpc85xx_rdb_setup_arch,
	.init_IRQ		= mpc85xx_rdb_pic_init,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
