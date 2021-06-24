<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2012-2015 Altera Corporation
 */
#समावेश <linux/irqchip.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/reboot.h>
#समावेश <linux/reset/socfpga.h>

#समावेश <यंत्र/hardware/cache-l2x0.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/cacheflush.h>

#समावेश "core.h"

व्योम __iomem *sys_manager_base_addr;
व्योम __iomem *rst_manager_base_addr;
व्योम __iomem *sdr_ctl_base_addr;
अचिन्हित दीर्घ socfpga_cpu1start_addr;

अटल व्योम __init socfpga_sysmgr_init(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, "altr,sys-mgr");

	अगर (of_property_पढ़ो_u32(np, "cpu1-start-addr",
			(u32 *) &socfpga_cpu1start_addr))
		pr_err("SMP: Need cpu1-start-addr in device tree.\n");

	/* Ensure that socfpga_cpu1start_addr is visible to other CPUs */
	smp_wmb();
	sync_cache_w(&socfpga_cpu1start_addr);

	sys_manager_base_addr = of_iomap(np, 0);

	np = of_find_compatible_node(शून्य, शून्य, "altr,rst-mgr");
	rst_manager_base_addr = of_iomap(np, 0);

	np = of_find_compatible_node(शून्य, शून्य, "altr,sdr-ctl");
	sdr_ctl_base_addr = of_iomap(np, 0);
पूर्ण

अटल व्योम __init socfpga_init_irq(व्योम)
अणु
	irqchip_init();
	socfpga_sysmgr_init();
	अगर (IS_ENABLED(CONFIG_EDAC_ALTERA_L2C))
		socfpga_init_l2_ecc();

	अगर (IS_ENABLED(CONFIG_EDAC_ALTERA_OCRAM))
		socfpga_init_ocram_ecc();
	socfpga_reset_init();
पूर्ण

अटल व्योम __init socfpga_arria10_init_irq(व्योम)
अणु
	irqchip_init();
	socfpga_sysmgr_init();
	अगर (IS_ENABLED(CONFIG_EDAC_ALTERA_L2C))
		socfpga_init_arria10_l2_ecc();
	अगर (IS_ENABLED(CONFIG_EDAC_ALTERA_OCRAM))
		socfpga_init_arria10_ocram_ecc();
	socfpga_reset_init();
पूर्ण

अटल व्योम socfpga_cyclone5_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	u32 temp;

	temp = पढ़ोl(rst_manager_base_addr + SOCFPGA_RSTMGR_CTRL);

	अगर (mode == REBOOT_WARM)
		temp |= RSTMGR_CTRL_SWWARMRSTREQ;
	अन्यथा
		temp |= RSTMGR_CTRL_SWCOLDRSTREQ;
	ग_लिखोl(temp, rst_manager_base_addr + SOCFPGA_RSTMGR_CTRL);
पूर्ण

अटल व्योम socfpga_arria10_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	u32 temp;

	temp = पढ़ोl(rst_manager_base_addr + SOCFPGA_A10_RSTMGR_CTRL);

	अगर (mode == REBOOT_WARM)
		temp |= RSTMGR_CTRL_SWWARMRSTREQ;
	अन्यथा
		temp |= RSTMGR_CTRL_SWCOLDRSTREQ;
	ग_लिखोl(temp, rst_manager_base_addr + SOCFPGA_A10_RSTMGR_CTRL);
पूर्ण

अटल स्थिर अक्षर *altera_dt_match[] = अणु
	"altr,socfpga",
	शून्य
पूर्ण;

DT_MACHINE_START(SOCFPGA, "Altera SOCFPGA")
	.l2c_aux_val	= 0,
	.l2c_aux_mask	= ~0,
	.init_irq	= socfpga_init_irq,
	.restart	= socfpga_cyclone5_restart,
	.dt_compat	= altera_dt_match,
MACHINE_END

अटल स्थिर अक्षर *altera_a10_dt_match[] = अणु
	"altr,socfpga-arria10",
	शून्य
पूर्ण;

DT_MACHINE_START(SOCFPGA_A10, "Altera SOCFPGA Arria10")
	.l2c_aux_val	= 0,
	.l2c_aux_mask	= ~0,
	.init_irq	= socfpga_arria10_init_irq,
	.restart	= socfpga_arria10_restart,
	.dt_compat	= altera_a10_dt_match,
MACHINE_END
