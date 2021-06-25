<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Generic Syscon Reboot Driver
 *
 * Copyright (c) 2013, Applied Micro Circuits Corporation
 * Author: Feng Kan <fkan@apm.com>
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

काष्ठा syscon_reboot_context अणु
	काष्ठा regmap *map;
	u32 offset;
	u32 value;
	u32 mask;
	काष्ठा notअगरier_block restart_handler;
पूर्ण;

अटल पूर्णांक syscon_restart_handle(काष्ठा notअगरier_block *this,
					अचिन्हित दीर्घ mode, व्योम *cmd)
अणु
	काष्ठा syscon_reboot_context *ctx =
			container_of(this, काष्ठा syscon_reboot_context,
					restart_handler);

	/* Issue the reboot */
	regmap_update_bits(ctx->map, ctx->offset, ctx->mask, ctx->value);

	mdelay(1000);

	pr_emerg("Unable to restart system\n");
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक syscon_reboot_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा syscon_reboot_context *ctx;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक mask_err, value_err;
	पूर्णांक err;

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->map = syscon_regmap_lookup_by_phandle(dev->of_node, "regmap");
	अगर (IS_ERR(ctx->map)) अणु
		ctx->map = syscon_node_to_regmap(dev->parent->of_node);
		अगर (IS_ERR(ctx->map))
			वापस PTR_ERR(ctx->map);
	पूर्ण

	अगर (of_property_पढ़ो_u32(pdev->dev.of_node, "offset", &ctx->offset))
		वापस -EINVAL;

	value_err = of_property_पढ़ो_u32(pdev->dev.of_node, "value", &ctx->value);
	mask_err = of_property_पढ़ो_u32(pdev->dev.of_node, "mask", &ctx->mask);
	अगर (value_err && mask_err) अणु
		dev_err(dev, "unable to read 'value' and 'mask'");
		वापस -EINVAL;
	पूर्ण

	अगर (value_err) अणु
		/* support old binding */
		ctx->value = ctx->mask;
		ctx->mask = 0xFFFFFFFF;
	पूर्ण अन्यथा अगर (mask_err) अणु
		/* support value without mask*/
		ctx->mask = 0xFFFFFFFF;
	पूर्ण

	ctx->restart_handler.notअगरier_call = syscon_restart_handle;
	ctx->restart_handler.priority = 192;
	err = रेजिस्टर_restart_handler(&ctx->restart_handler);
	अगर (err)
		dev_err(dev, "can't register restart notifier (err=%d)\n", err);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id syscon_reboot_of_match[] = अणु
	अणु .compatible = "syscon-reboot" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver syscon_reboot_driver = अणु
	.probe = syscon_reboot_probe,
	.driver = अणु
		.name = "syscon-reboot",
		.of_match_table = syscon_reboot_of_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(syscon_reboot_driver);
