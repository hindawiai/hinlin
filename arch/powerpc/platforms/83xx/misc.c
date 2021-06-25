<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * misc setup functions क्रम MPC83xx
 *
 * Maपूर्णांकainer: Kumar Gala <galak@kernel.crashing.org>
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/ipic.h>
#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>

#समावेश <mm/mmu_decl.h>

#समावेश "mpc83xx.h"

अटल __be32 __iomem *restart_reg_base;

अटल पूर्णांक __init mpc83xx_restart_init(व्योम)
अणु
	/* map reset restart_reg_baseister space */
	restart_reg_base = ioremap(get_immrbase() + 0x900, 0xff);

	वापस 0;
पूर्ण

arch_initcall(mpc83xx_restart_init);

व्योम __noवापस mpc83xx_restart(अक्षर *cmd)
अणु
#घोषणा RST_OFFSET	0x00000900
#घोषणा RST_PROT_REG	0x00000018
#घोषणा RST_CTRL_REG	0x0000001c

	local_irq_disable();

	अगर (restart_reg_base) अणु
		/* enable software reset "RSTE" */
		out_be32(restart_reg_base + (RST_PROT_REG >> 2), 0x52535445);

		/* set software hard reset */
		out_be32(restart_reg_base + (RST_CTRL_REG >> 2), 0x2);
	पूर्ण अन्यथा अणु
		prपूर्णांकk (KERN_EMERG "Error: Restart registers not mapped, spinning!\n");
	पूर्ण

	क्रम (;;) ;
पूर्ण

दीर्घ __init mpc83xx_समय_init(व्योम)
अणु
#घोषणा SPCR_OFFSET	0x00000110
#घोषणा SPCR_TBEN	0x00400000
	__be32 __iomem *spcr = ioremap(get_immrbase() + SPCR_OFFSET, 4);
	__be32 पंचांगp;

	पंचांगp = in_be32(spcr);
	out_be32(spcr, पंचांगp | SPCR_TBEN);

	iounmap(spcr);

	वापस 0;
पूर्ण

व्योम __init mpc83xx_ipic_init_IRQ(व्योम)
अणु
	काष्ठा device_node *np;

	/* looking क्रम fsl,pq2pro-pic which is asl compatible with fsl,ipic */
	np = of_find_compatible_node(शून्य, शून्य, "fsl,ipic");
	अगर (!np)
		np = of_find_node_by_type(शून्य, "ipic");
	अगर (!np)
		वापस;

	ipic_init(np, 0);

	of_node_put(np);

	/* Initialize the शेष पूर्णांकerrupt mapping priorities,
	 * in हाल the boot rom changed something on us.
	 */
	ipic_set_शेष_priority();
पूर्ण

अटल स्थिर काष्ठा of_device_id of_bus_ids[] __initस्थिर = अणु
	अणु .type = "soc", पूर्ण,
	अणु .compatible = "soc", पूर्ण,
	अणु .compatible = "simple-bus" पूर्ण,
	अणु .compatible = "gianfar" पूर्ण,
	अणु .compatible = "gpio-leds", पूर्ण,
	अणु .type = "qe", पूर्ण,
	अणु .compatible = "fsl,qe", पूर्ण,
	अणुपूर्ण,
पूर्ण;

पूर्णांक __init mpc83xx_declare_of_platक्रमm_devices(व्योम)
अणु
	of_platक्रमm_bus_probe(शून्य, of_bus_ids, शून्य);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PCI
व्योम __init mpc83xx_setup_pci(व्योम)
अणु
	काष्ठा device_node *np;

	क्रम_each_compatible_node(np, "pci", "fsl,mpc8349-pci")
		mpc83xx_add_bridge(np);
	क्रम_each_compatible_node(np, "pci", "fsl,mpc8314-pcie")
		mpc83xx_add_bridge(np);
पूर्ण
#पूर्ण_अगर

व्योम __init mpc83xx_setup_arch(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("mpc83xx_setup_arch()", 0);

	अगर (!__map_without_bats) अणु
		phys_addr_t immrbase = get_immrbase();
		पूर्णांक immrsize = IS_ALIGNED(immrbase, SZ_2M) ? SZ_2M : SZ_1M;
		अचिन्हित दीर्घ va = fix_to_virt(FIX_IMMR_BASE);

		setbat(-1, va, immrbase, immrsize, PAGE_KERNEL_NCG);
		update_bats();
	पूर्ण
पूर्ण

पूर्णांक machine_check_83xx(काष्ठा pt_regs *regs)
अणु
	u32 mask = 1 << (31 - IPIC_MCP_WDT);

	अगर (!(regs->msr & SRR1_MCE_MCP) || !(ipic_get_mcp_status() & mask))
		वापस machine_check_generic(regs);
	ipic_clear_mcp_status(mask);

	अगर (debugger_fault_handler(regs))
		वापस 1;

	die("Watchdog NMI Reset", regs, 0);

	वापस 1;
पूर्ण
