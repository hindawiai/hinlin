<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/*
 * Microsemi MIPS SoC reset driver
 *
 * License: Dual MIT/GPL
 * Copyright (c) 2017 Microsemi Corporation
 */
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/notअगरier.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/regmap.h>

काष्ठा reset_props अणु
	स्थिर अक्षर *syscon;
	u32 protect_reg;
	u32 vcore_protect;
	u32 अगर_si_owner_bit;
पूर्ण;

काष्ठा ocelot_reset_context अणु
	व्योम __iomem *base;
	काष्ठा regmap *cpu_ctrl;
	स्थिर काष्ठा reset_props *props;
	काष्ठा notअगरier_block restart_handler;
पूर्ण;

#घोषणा BIT_OFF_INVALID				32

#घोषणा SOFT_CHIP_RST BIT(0)

#घोषणा ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL	0x24
#घोषणा IF_SI_OWNER_MASK			GENMASK(1, 0)
#घोषणा IF_SI_OWNER_SISL			0
#घोषणा IF_SI_OWNER_SIBM			1
#घोषणा IF_SI_OWNER_SIMC			2

अटल पूर्णांक ocelot_restart_handle(काष्ठा notअगरier_block *this,
				 अचिन्हित दीर्घ mode, व्योम *cmd)
अणु
	काष्ठा ocelot_reset_context *ctx = container_of(this, काष्ठा
							ocelot_reset_context,
							restart_handler);
	u32 अगर_si_owner_bit = ctx->props->अगर_si_owner_bit;

	/* Make sure the core is not रक्षित from reset */
	regmap_update_bits(ctx->cpu_ctrl, ctx->props->protect_reg,
			   ctx->props->vcore_protect, 0);

	/* Make the SI back to boot mode */
	अगर (अगर_si_owner_bit != BIT_OFF_INVALID)
		regmap_update_bits(ctx->cpu_ctrl,
				   ICPU_CFG_CPU_SYSTEM_CTRL_GENERAL_CTRL,
				   IF_SI_OWNER_MASK << अगर_si_owner_bit,
				   IF_SI_OWNER_SIBM << अगर_si_owner_bit);

	pr_emerg("Resetting SoC\n");

	ग_लिखोl(SOFT_CHIP_RST, ctx->base);

	pr_emerg("Unable to restart system\n");
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक ocelot_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ocelot_reset_context *ctx;
	काष्ठा resource *res;

	काष्ठा device *dev = &pdev->dev;
	पूर्णांक err;

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ctx->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(ctx->base))
		वापस PTR_ERR(ctx->base);

	ctx->props = device_get_match_data(dev);

	ctx->cpu_ctrl = syscon_regmap_lookup_by_compatible(ctx->props->syscon);
	अगर (IS_ERR(ctx->cpu_ctrl)) अणु
		dev_err(dev, "No syscon map: %s\n", ctx->props->syscon);
		वापस PTR_ERR(ctx->cpu_ctrl);
	पूर्ण

	ctx->restart_handler.notअगरier_call = ocelot_restart_handle;
	ctx->restart_handler.priority = 192;
	err = रेजिस्टर_restart_handler(&ctx->restart_handler);
	अगर (err)
		dev_err(dev, "can't register restart notifier (err=%d)\n", err);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा reset_props reset_props_jaguar2 = अणु
	.syscon		 = "mscc,ocelot-cpu-syscon",
	.protect_reg     = 0x20,
	.vcore_protect   = BIT(2),
	.अगर_si_owner_bit = 6,
पूर्ण;

अटल स्थिर काष्ठा reset_props reset_props_luton = अणु
	.syscon		 = "mscc,ocelot-cpu-syscon",
	.protect_reg     = 0x20,
	.vcore_protect   = BIT(2),
	.अगर_si_owner_bit = BIT_OFF_INVALID, /* n/a */
पूर्ण;

अटल स्थिर काष्ठा reset_props reset_props_ocelot = अणु
	.syscon		 = "mscc,ocelot-cpu-syscon",
	.protect_reg     = 0x20,
	.vcore_protect   = BIT(2),
	.अगर_si_owner_bit = 4,
पूर्ण;

अटल स्थिर काष्ठा reset_props reset_props_sparx5 = अणु
	.syscon		 = "microchip,sparx5-cpu-syscon",
	.protect_reg     = 0x84,
	.vcore_protect   = BIT(10),
	.अगर_si_owner_bit = 6,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ocelot_reset_of_match[] = अणु
	अणु
		.compatible = "mscc,jaguar2-chip-reset",
		.data = &reset_props_jaguar2
	पूर्ण, अणु
		.compatible = "mscc,luton-chip-reset",
		.data = &reset_props_luton
	पूर्ण, अणु
		.compatible = "mscc,ocelot-chip-reset",
		.data = &reset_props_ocelot
	पूर्ण, अणु
		.compatible = "microchip,sparx5-chip-reset",
		.data = &reset_props_sparx5
	पूर्ण,
	अणु /*sentinel*/ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver ocelot_reset_driver = अणु
	.probe = ocelot_reset_probe,
	.driver = अणु
		.name = "ocelot-chip-reset",
		.of_match_table = ocelot_reset_of_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(ocelot_reset_driver);
