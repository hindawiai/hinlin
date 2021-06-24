<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Special GIC quirks क्रम the ARM RealView
 * Copyright (C) 2015 Linus Walleij
 */
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/bitops.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/arm-gic.h>

#घोषणा REALVIEW_SYS_LOCK_OFFSET	0x20
#घोषणा REALVIEW_SYS_PLD_CTRL1		0x74
#घोषणा REALVIEW_EB_REVB_SYS_PLD_CTRL1	0xD8
#घोषणा VERSATILE_LOCK_VAL		0xA05F
#घोषणा PLD_INTMODE_MASK		BIT(22)|BIT(23)|BIT(24)
#घोषणा PLD_INTMODE_LEGACY		0x0
#घोषणा PLD_INTMODE_NEW_DCC		BIT(22)
#घोषणा PLD_INTMODE_NEW_NO_DCC		BIT(23)
#घोषणा PLD_INTMODE_FIQ_ENABLE		BIT(24)

/* For some reason RealView EB Rev B moved this रेजिस्टर */
अटल स्थिर काष्ठा of_device_id syscon_pldset_of_match[] = अणु
	अणु
		.compatible = "arm,realview-eb11mp-revb-syscon",
		.data = (व्योम *)REALVIEW_EB_REVB_SYS_PLD_CTRL1,
	पूर्ण,
	अणु
		.compatible = "arm,realview-eb11mp-revc-syscon",
		.data = (व्योम *)REALVIEW_SYS_PLD_CTRL1,
	पूर्ण,
	अणु
		.compatible = "arm,realview-eb-syscon",
		.data = (व्योम *)REALVIEW_SYS_PLD_CTRL1,
	पूर्ण,
	अणु
		.compatible = "arm,realview-pb11mp-syscon",
		.data = (व्योम *)REALVIEW_SYS_PLD_CTRL1,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init
realview_gic_of_init(काष्ठा device_node *node, काष्ठा device_node *parent)
अणु
	काष्ठा regmap *map;
	काष्ठा device_node *np;
	स्थिर काष्ठा of_device_id *gic_id;
	u32 pld1_ctrl;

	np = of_find_matching_node_and_match(शून्य, syscon_pldset_of_match,
					     &gic_id);
	अगर (!np)
		वापस -ENODEV;
	pld1_ctrl = (u32)gic_id->data;

	/* The PB11MPCore GIC needs to be configured in the syscon */
	map = syscon_node_to_regmap(np);
	अगर (!IS_ERR(map)) अणु
		/* new irq mode with no DCC */
		regmap_ग_लिखो(map, REALVIEW_SYS_LOCK_OFFSET,
			     VERSATILE_LOCK_VAL);
		regmap_update_bits(map, pld1_ctrl,
				   PLD_INTMODE_NEW_NO_DCC,
				   PLD_INTMODE_MASK);
		regmap_ग_लिखो(map, REALVIEW_SYS_LOCK_OFFSET, 0x0000);
		pr_info("RealView GIC: set up interrupt controller to NEW mode, no DCC\n");
	पूर्ण अन्यथा अणु
		pr_err("RealView GIC setup: could not find syscon\n");
		वापस -ENODEV;
	पूर्ण
	वापस gic_of_init(node, parent);
पूर्ण
IRQCHIP_DECLARE(armtc11mp_gic, "arm,tc11mp-gic", realview_gic_of_init);
IRQCHIP_DECLARE(armeb11mp_gic, "arm,eb11mp-gic", realview_gic_of_init);
