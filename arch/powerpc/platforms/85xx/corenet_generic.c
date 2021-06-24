<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Corenet based SoC DS Setup
 *
 * Maपूर्णांकained by Kumar Gala (see MAINTAINERS क्रम contact inक्रमmation)
 *
 * Copyright 2009-2011 Freescale Semiconductor Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <mm/mmu_decl.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/ehv_pic.h>
#समावेश <यंत्र/swiotlb.h>

#समावेश <linux/of_platक्रमm.h>
#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>
#समावेश "smp.h"
#समावेश "mpc85xx.h"

व्योम __init corenet_gen_pic_init(व्योम)
अणु
	काष्ठा mpic *mpic;
	अचिन्हित पूर्णांक flags = MPIC_BIG_ENDIAN | MPIC_SINGLE_DEST_CPU |
		MPIC_NO_RESET;

	अगर (ppc_md.get_irq == mpic_get_coreपूर्णांक_irq)
		flags |= MPIC_ENABLE_COREINT;

	mpic = mpic_alloc(शून्य, 0, flags, 0, 512, " OpenPIC  ");
	BUG_ON(mpic == शून्य);

	mpic_init(mpic);
पूर्ण

/*
 * Setup the architecture
 */
व्योम __init corenet_gen_setup_arch(व्योम)
अणु
	mpc85xx_smp_init();

	swiotlb_detect_4g();

	pr_info("%s board\n", ppc_md.name);
पूर्ण

अटल स्थिर काष्ठा of_device_id of_device_ids[] = अणु
	अणु
		.compatible	= "simple-bus"
	पूर्ण,
	अणु
		.compatible	= "mdio-mux-gpio"
	पूर्ण,
	अणु
		.compatible	= "fsl,fpga-ngpixis"
	पूर्ण,
	अणु
		.compatible	= "fsl,fpga-qixis"
	पूर्ण,
	अणु
		.compatible	= "fsl,srio",
	पूर्ण,
	अणु
		.compatible	= "fsl,p4080-pcie",
	पूर्ण,
	अणु
		.compatible	= "fsl,qoriq-pcie-v2.2",
	पूर्ण,
	अणु
		.compatible	= "fsl,qoriq-pcie-v2.3",
	पूर्ण,
	अणु
		.compatible	= "fsl,qoriq-pcie-v2.4",
	पूर्ण,
	अणु
		.compatible	= "fsl,qoriq-pcie-v3.0",
	पूर्ण,
	अणु
		.compatible	= "fsl,qe",
	पूर्ण,
	/* The following two are क्रम the Freescale hypervisor */
	अणु
		.name		= "hypervisor",
	पूर्ण,
	अणु
		.name		= "handles",
	पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक __init corenet_gen_publish_devices(व्योम)
अणु
	वापस of_platक्रमm_bus_probe(शून्य, of_device_ids, शून्य);
पूर्ण
machine_arch_initcall(corenet_generic, corenet_gen_publish_devices);

अटल स्थिर अक्षर * स्थिर boards[] __initस्थिर = अणु
	"fsl,P2041RDB",
	"fsl,P3041DS",
	"fsl,OCA4080",
	"fsl,P4080DS",
	"fsl,P5020DS",
	"fsl,P5040DS",
	"fsl,T2080QDS",
	"fsl,T2080RDB",
	"fsl,T2081QDS",
	"fsl,T4240QDS",
	"fsl,T4240RDB",
	"fsl,B4860QDS",
	"fsl,B4420QDS",
	"fsl,B4220QDS",
	"fsl,T1023RDB",
	"fsl,T1024QDS",
	"fsl,T1024RDB",
	"fsl,T1040D4RDB",
	"fsl,T1042D4RDB",
	"fsl,T1040QDS",
	"fsl,T1042QDS",
	"fsl,T1040RDB",
	"fsl,T1042RDB",
	"fsl,T1042RDB_PI",
	"keymile,kmcent2",
	"keymile,kmcoge4",
	"varisys,CYRUS",
	शून्य
पूर्ण;

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init corenet_generic_probe(व्योम)
अणु
	अक्षर hv_compat[24];
	पूर्णांक i;
#अगर_घोषित CONFIG_SMP
	बाह्य काष्ठा smp_ops_t smp_85xx_ops;
#पूर्ण_अगर

	अगर (of_device_compatible_match(of_root, boards))
		वापस 1;

	/* Check अगर we're running under the Freescale hypervisor */
	क्रम (i = 0; boards[i]; i++) अणु
		snम_लिखो(hv_compat, माप(hv_compat), "%s-hv", boards[i]);
		अगर (of_machine_is_compatible(hv_compat)) अणु
			ppc_md.init_IRQ = ehv_pic_init;

			ppc_md.get_irq = ehv_pic_get_irq;
			ppc_md.restart = fsl_hv_restart;
			pm_घातer_off = fsl_hv_halt;
			ppc_md.halt = fsl_hv_halt;
#अगर_घोषित CONFIG_SMP
			/*
			 * Disable the समयbase sync operations because we
			 * can't ग_लिखो to the समयbase रेजिस्टरs under the
			 * hypervisor.
			 */
			smp_85xx_ops.give_समयbase = शून्य;
			smp_85xx_ops.take_समयbase = शून्य;
#पूर्ण_अगर
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

define_machine(corenet_generic) अणु
	.name			= "CoreNet Generic",
	.probe			= corenet_generic_probe,
	.setup_arch		= corenet_gen_setup_arch,
	.init_IRQ		= corenet_gen_pic_init,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
/*
 * Core reset may cause issues अगर using the proxy mode of MPIC.
 * So, use the mixed mode of MPIC अगर enabling CPU hotplug.
 *
 * Likewise, problems have been seen with kexec when coreपूर्णांक is enabled.
 */
#अगर defined(CONFIG_HOTPLUG_CPU) || defined(CONFIG_KEXEC_CORE)
	.get_irq		= mpic_get_irq,
#अन्यथा
	.get_irq		= mpic_get_coreपूर्णांक_irq,
#पूर्ण_अगर
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
#अगर_घोषित CONFIG_PPC64
	.घातer_save		= book3e_idle,
#अन्यथा
	.घातer_save		= e500_idle,
#पूर्ण_अगर
पूर्ण;
