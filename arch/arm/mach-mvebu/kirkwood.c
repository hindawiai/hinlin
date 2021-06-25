<शैली गुरु>
/*
 * Copyright 2012 (C), Jason Cooper <jason@lakedaemon.net>
 *
 * arch/arm/mach-mvebu/kirkwood.c
 *
 * Flattened Device Tree board initialization
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/mbus.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_net.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/hardware/cache-feroceon-l2.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश "kirkwood.h"
#समावेश "kirkwood-pm.h"
#समावेश "common.h"

अटल काष्ठा resource kirkwood_cpufreq_resources[] = अणु
	[0] = अणु
		.start  = CPU_CONTROL_PHYS,
		.end    = CPU_CONTROL_PHYS + 3,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device kirkwood_cpufreq_device = अणु
	.name		= "kirkwood-cpufreq",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(kirkwood_cpufreq_resources),
	.resource	= kirkwood_cpufreq_resources,
पूर्ण;

अटल व्योम __init kirkwood_cpufreq_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&kirkwood_cpufreq_device);
पूर्ण

अटल काष्ठा resource kirkwood_cpuidle_resource[] = अणु
	अणु
		.flags	= IORESOURCE_MEM,
		.start	= DDR_OPERATION_BASE,
		.end	= DDR_OPERATION_BASE + 3,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device kirkwood_cpuidle = अणु
	.name		= "kirkwood_cpuidle",
	.id		= -1,
	.resource	= kirkwood_cpuidle_resource,
	.num_resources	= 1,
पूर्ण;

अटल व्योम __init kirkwood_cpuidle_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&kirkwood_cpuidle);
पूर्ण

#घोषणा MV643XX_ETH_MAC_ADDR_LOW	0x0414
#घोषणा MV643XX_ETH_MAC_ADDR_HIGH	0x0418

अटल व्योम __init kirkwood_dt_eth_fixup(व्योम)
अणु
	काष्ठा device_node *np;

	/*
	 * The ethernet पूर्णांकerfaces क्रमget the MAC address asचिन्हित by u-boot
	 * अगर the घड़ीs are turned off. Usually, u-boot on kirkwood boards
	 * has no DT support to properly set local-mac-address property.
	 * As a workaround, we get the MAC address from mv643xx_eth रेजिस्टरs
	 * and update the port device node अगर no valid MAC address is set.
	 */
	क्रम_each_compatible_node(np, शून्य, "marvell,kirkwood-eth-port") अणु
		काष्ठा device_node *pnp = of_get_parent(np);
		काष्ठा clk *clk;
		काष्ठा property *pmac;
		u8 पंचांगpmac[ETH_ALEN];
		व्योम __iomem *io;
		u8 *macaddr;
		u32 reg;

		अगर (!pnp)
			जारी;

		/* skip disabled nodes or nodes with valid MAC address*/
		अगर (!of_device_is_available(pnp) ||
		    !of_get_mac_address(np, पंचांगpmac))
			जाओ eth_fixup_skip;

		clk = of_clk_get(pnp, 0);
		अगर (IS_ERR(clk))
			जाओ eth_fixup_skip;

		io = of_iomap(pnp, 0);
		अगर (!io)
			जाओ eth_fixup_no_map;

		/* ensure port घड़ी is not gated to not hang CPU */
		clk_prepare_enable(clk);

		/* store MAC address रेजिस्टर contents in local-mac-address */
		pmac = kzalloc(माप(*pmac) + 6, GFP_KERNEL);
		अगर (!pmac)
			जाओ eth_fixup_no_mem;

		pmac->value = pmac + 1;
		pmac->length = 6;
		pmac->name = kstrdup("local-mac-address", GFP_KERNEL);
		अगर (!pmac->name) अणु
			kमुक्त(pmac);
			जाओ eth_fixup_no_mem;
		पूर्ण

		macaddr = pmac->value;
		reg = पढ़ोl(io + MV643XX_ETH_MAC_ADDR_HIGH);
		macaddr[0] = (reg >> 24) & 0xff;
		macaddr[1] = (reg >> 16) & 0xff;
		macaddr[2] = (reg >> 8) & 0xff;
		macaddr[3] = reg & 0xff;

		reg = पढ़ोl(io + MV643XX_ETH_MAC_ADDR_LOW);
		macaddr[4] = (reg >> 8) & 0xff;
		macaddr[5] = reg & 0xff;

		of_update_property(np, pmac);

eth_fixup_no_mem:
		iounmap(io);
		clk_disable_unprepare(clk);
eth_fixup_no_map:
		clk_put(clk);
eth_fixup_skip:
		of_node_put(pnp);
	पूर्ण
पूर्ण

/*
 * Disable propagation of mbus errors to the CPU local bus, as this
 * causes mbus errors (which can occur क्रम example क्रम PCI पातs) to
 * throw CPU पातs, which we're not set up to deal with.
 */
अटल व्योम kirkwood_disable_mbus_error_propagation(व्योम)
अणु
	व्योम __iomem *cpu_config;

	cpu_config = ioremap(CPU_CONFIG_PHYS, 4);
	ग_लिखोl(पढ़ोl(cpu_config) & ~CPU_CONFIG_ERROR_PROP, cpu_config);
पूर्ण

अटल काष्ठा of_dev_auxdata auxdata[] __initdata = अणु
	OF_DEV_AUXDATA("marvell,kirkwood-audio", 0xf10a0000,
		       "mvebu-audio", शून्य),
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल व्योम __init kirkwood_dt_init(व्योम)
अणु
	kirkwood_disable_mbus_error_propagation();

	BUG_ON(mvebu_mbus_dt_init(false));

#अगर_घोषित CONFIG_CACHE_FEROCEON_L2
	feroceon_of_init();
#पूर्ण_अगर
	kirkwood_cpufreq_init();
	kirkwood_cpuidle_init();

	kirkwood_pm_init();
	kirkwood_dt_eth_fixup();

	of_platक्रमm_शेष_populate(शून्य, auxdata, शून्य);
पूर्ण

अटल स्थिर अक्षर * स्थिर kirkwood_dt_board_compat[] __initस्थिर = अणु
	"marvell,kirkwood",
	शून्य
पूर्ण;

DT_MACHINE_START(KIRKWOOD_DT, "Marvell Kirkwood (Flattened Device Tree)")
	/* Maपूर्णांकainer: Jason Cooper <jason@lakedaemon.net> */
	.init_machine	= kirkwood_dt_init,
	.restart	= mvebu_restart,
	.dt_compat	= kirkwood_dt_board_compat,
MACHINE_END
