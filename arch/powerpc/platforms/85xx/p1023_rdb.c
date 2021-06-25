<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2010-2011, 2013 Freescale Semiconductor, Inc.
 *
 * Author: Roy Zang <tie-fei.zang@मुक्तscale.com>
 *
 * Description:
 * P1023 RDB Board Setup
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/fsl_devices.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <mm/mmu_decl.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/mpic.h>
#समावेश "smp.h"

#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>

#समावेश "mpc85xx.h"

/* ************************************************************************
 *
 * Setup the architecture
 *
 */
अटल व्योम __init mpc85xx_rdb_setup_arch(व्योम)
अणु
	काष्ठा device_node *np;

	अगर (ppc_md.progress)
		ppc_md.progress("p1023_rdb_setup_arch()", 0);

	/* Map BCSR area */
	np = of_find_node_by_name(शून्य, "bcsr");
	अगर (np != शून्य) अणु
		अटल u8 __iomem *bcsr_regs;

		bcsr_regs = of_iomap(np, 0);
		of_node_put(np);

		अगर (!bcsr_regs) अणु
			prपूर्णांकk(KERN_ERR
			       "BCSR: Failed to map bcsr register space\n");
			वापस;
		पूर्ण अन्यथा अणु
#घोषणा BCSR15_I2C_BUS0_SEG_CLR		0x07
#घोषणा BCSR15_I2C_BUS0_SEG2		0x02
/*
 * Note: Accessing exclusively i2c devices.
 *
 * The i2c controller selects initially ID EEPROM in the u-boot;
 * but अगर menu configuration selects RTC support in the kernel,
 * the i2c controller चयनes to select RTC chip in the kernel.
 */
#अगर_घोषित CONFIG_RTC_CLASS
			/* Enable RTC chip on the segment #2 of i2c */
			clrbits8(&bcsr_regs[15], BCSR15_I2C_BUS0_SEG_CLR);
			setbits8(&bcsr_regs[15], BCSR15_I2C_BUS0_SEG2);
#पूर्ण_अगर

			iounmap(bcsr_regs);
		पूर्ण
	पूर्ण

	mpc85xx_smp_init();

	fsl_pci_assign_primary();
पूर्ण

machine_arch_initcall(p1023_rdb, mpc85xx_common_publish_devices);

अटल व्योम __init mpc85xx_rdb_pic_init(व्योम)
अणु
	काष्ठा mpic *mpic = mpic_alloc(शून्य, 0, MPIC_BIG_ENDIAN |
		MPIC_SINGLE_DEST_CPU,
		0, 256, " OpenPIC  ");

	BUG_ON(mpic == शून्य);

	mpic_init(mpic);
पूर्ण

अटल पूर्णांक __init p1023_rdb_probe(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,P1023RDB");

पूर्ण

define_machine(p1023_rdb) अणु
	.name			= "P1023 RDB",
	.probe			= p1023_rdb_probe,
	.setup_arch		= mpc85xx_rdb_setup_arch,
	.init_IRQ		= mpc85xx_rdb_pic_init,
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
पूर्ण;
