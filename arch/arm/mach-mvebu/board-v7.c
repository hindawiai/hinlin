<शैली गुरु>
/*
 * Device Tree support क्रम Armada 370 and XP platक्रमms.
 *
 * Copyright (C) 2012 Marvell
 *
 * Lior Amsalem <alior@marvell.com>
 * Gregory CLEMENT <gregory.clement@मुक्त-electrons.com>
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/पन.स>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mbus.h>
#समावेश <linux/slab.h>
#समावेश <linux/irqchip.h>
#समावेश <यंत्र/hardware/cache-l2x0.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश <यंत्र/smp_scu.h>
#समावेश "armada-370-xp.h"
#समावेश "common.h"
#समावेश "coherency.h"
#समावेश "mvebu-soc-id.h"

अटल व्योम __iomem *scu_base;

/*
 * Enables the SCU when available. Obviously, this is only useful on
 * Cortex-A based SOCs, not on PJ4B based ones.
 */
अटल व्योम __init mvebu_scu_enable(व्योम)
अणु
	काष्ठा device_node *np =
		of_find_compatible_node(शून्य, शून्य, "arm,cortex-a9-scu");
	अगर (np) अणु
		scu_base = of_iomap(np, 0);
		scu_enable(scu_base);
		of_node_put(np);
	पूर्ण
पूर्ण

व्योम __iomem *mvebu_get_scu_base(व्योम)
अणु
	वापस scu_base;
पूर्ण

/*
 * When वापसing from suspend, the platक्रमm goes through the
 * bootloader, which executes its DDR3 training code. This code has
 * the unक्रमtunate idea of using the first 10 KB of each DRAM bank to
 * exercise the RAM and calculate the optimal timings. Thereक्रमe, this
 * area of RAM is overwritten, and shouldn't be used by the kernel अगर
 * suspend/resume is supported.
 */

#अगर_घोषित CONFIG_SUSPEND
#घोषणा MVEBU_DDR_TRAINING_AREA_SZ (10 * SZ_1K)
अटल पूर्णांक __init mvebu_scan_mem(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
				 पूर्णांक depth, व्योम *data)
अणु
	स्थिर अक्षर *type = of_get_flat_dt_prop(node, "device_type", शून्य);
	स्थिर __be32 *reg, *endp;
	पूर्णांक l;

	अगर (type == शून्य || म_भेद(type, "memory"))
		वापस 0;

	reg = of_get_flat_dt_prop(node, "linux,usable-memory", &l);
	अगर (reg == शून्य)
		reg = of_get_flat_dt_prop(node, "reg", &l);
	अगर (reg == शून्य)
		वापस 0;

	endp = reg + (l / माप(__be32));
	जबतक ((endp - reg) >= (dt_root_addr_cells + dt_root_size_cells)) अणु
		u64 base, size;

		base = dt_mem_next_cell(dt_root_addr_cells, &reg);
		size = dt_mem_next_cell(dt_root_size_cells, &reg);

		memblock_reserve(base, MVEBU_DDR_TRAINING_AREA_SZ);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __init mvebu_memblock_reserve(व्योम)
अणु
	of_scan_flat_dt(mvebu_scan_mem, शून्य);
पूर्ण
#अन्यथा
अटल व्योम __init mvebu_memblock_reserve(व्योम) अणुपूर्ण
#पूर्ण_अगर

अटल व्योम __init mvebu_init_irq(व्योम)
अणु
	irqchip_init();
	mvebu_scu_enable();
	coherency_init();
	BUG_ON(mvebu_mbus_dt_init(coherency_available()));
पूर्ण

अटल व्योम __init i2c_quirk(व्योम)
अणु
	काष्ठा device_node *np;
	u32 dev, rev;

	/*
	 * Only revisons more recent than A0 support the offload
	 * mechanism. We can निकास only अगर we are sure that we can
	 * get the SoC revision and it is more recent than A0.
	 */
	अगर (mvebu_get_soc_id(&dev, &rev) == 0 && rev > MV78XX0_A0_REV)
		वापस;

	क्रम_each_compatible_node(np, शून्य, "marvell,mv78230-i2c") अणु
		काष्ठा property *new_compat;

		new_compat = kzalloc(माप(*new_compat), GFP_KERNEL);

		new_compat->name = kstrdup("compatible", GFP_KERNEL);
		new_compat->length = माप("marvell,mv78230-a0-i2c");
		new_compat->value = kstrdup("marvell,mv78230-a0-i2c",
						GFP_KERNEL);

		of_update_property(np, new_compat);
	पूर्ण
पूर्ण

अटल व्योम __init mvebu_dt_init(व्योम)
अणु
	अगर (of_machine_is_compatible("marvell,armadaxp"))
		i2c_quirk();
पूर्ण

अटल व्योम __init armada_370_xp_dt_fixup(व्योम)
अणु
#अगर_घोषित CONFIG_SMP
	smp_set_ops(smp_ops(armada_xp_smp_ops));
#पूर्ण_अगर
पूर्ण

अटल स्थिर अक्षर * स्थिर armada_370_xp_dt_compat[] __initस्थिर = अणु
	"marvell,armada-370-xp",
	शून्य,
पूर्ण;

DT_MACHINE_START(ARMADA_370_XP_DT, "Marvell Armada 370/XP (Device Tree)")
	.l2c_aux_val	= 0,
	.l2c_aux_mask	= ~0,
	.init_machine	= mvebu_dt_init,
	.init_irq       = mvebu_init_irq,
	.restart	= mvebu_restart,
	.reserve        = mvebu_memblock_reserve,
	.dt_compat	= armada_370_xp_dt_compat,
	.dt_fixup	= armada_370_xp_dt_fixup,
MACHINE_END

अटल स्थिर अक्षर * स्थिर armada_375_dt_compat[] __initस्थिर = अणु
	"marvell,armada375",
	शून्य,
पूर्ण;

DT_MACHINE_START(ARMADA_375_DT, "Marvell Armada 375 (Device Tree)")
	.l2c_aux_val	= 0,
	.l2c_aux_mask	= ~0,
	.init_irq       = mvebu_init_irq,
	.init_machine	= mvebu_dt_init,
	.restart	= mvebu_restart,
	.dt_compat	= armada_375_dt_compat,
MACHINE_END

अटल स्थिर अक्षर * स्थिर armada_38x_dt_compat[] __initस्थिर = अणु
	"marvell,armada380",
	"marvell,armada385",
	शून्य,
पूर्ण;

DT_MACHINE_START(ARMADA_38X_DT, "Marvell Armada 380/385 (Device Tree)")
	.l2c_aux_val	= 0,
	.l2c_aux_mask	= ~0,
	.init_irq       = mvebu_init_irq,
	.restart	= mvebu_restart,
	.dt_compat	= armada_38x_dt_compat,
MACHINE_END

अटल स्थिर अक्षर * स्थिर armada_39x_dt_compat[] __initस्थिर = अणु
	"marvell,armada390",
	"marvell,armada398",
	शून्य,
पूर्ण;

DT_MACHINE_START(ARMADA_39X_DT, "Marvell Armada 39x (Device Tree)")
	.l2c_aux_val	= 0,
	.l2c_aux_mask	= ~0,
	.init_irq       = mvebu_init_irq,
	.restart	= mvebu_restart,
	.dt_compat	= armada_39x_dt_compat,
MACHINE_END
