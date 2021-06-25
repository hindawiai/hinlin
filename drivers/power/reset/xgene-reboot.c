<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AppliedMicro X-Gene SoC Reboot Driver
 *
 * Copyright (c) 2013, Applied Micro Circuits Corporation
 * Author: Feng Kan <fkan@apm.com>
 * Author: Loc Ho <lho@apm.com>
 *
 * This driver provides प्रणाली reboot functionality क्रम APM X-Gene SoC.
 * For प्रणाली shutकरोwn, this is board specअगरy. If a board designer
 * implements GPIO shutकरोwn, use the gpio-घातeroff.c driver.
 */
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/slab.h>

काष्ठा xgene_reboot_context अणु
	काष्ठा device *dev;
	व्योम *csr;
	u32 mask;
	काष्ठा notअगरier_block restart_handler;
पूर्ण;

अटल पूर्णांक xgene_restart_handler(काष्ठा notअगरier_block *this,
				 अचिन्हित दीर्घ mode, व्योम *cmd)
अणु
	काष्ठा xgene_reboot_context *ctx =
		container_of(this, काष्ठा xgene_reboot_context,
			     restart_handler);

	/* Issue the reboot */
	ग_लिखोl(ctx->mask, ctx->csr);

	mdelay(1000);

	dev_emerg(ctx->dev, "Unable to restart system\n");

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक xgene_reboot_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xgene_reboot_context *ctx;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक err;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->csr = of_iomap(dev->of_node, 0);
	अगर (!ctx->csr) अणु
		dev_err(dev, "can not map resource\n");
		वापस -ENODEV;
	पूर्ण

	अगर (of_property_पढ़ो_u32(dev->of_node, "mask", &ctx->mask))
		ctx->mask = 0xFFFFFFFF;

	ctx->dev = dev;
	ctx->restart_handler.notअगरier_call = xgene_restart_handler;
	ctx->restart_handler.priority = 128;
	err = रेजिस्टर_restart_handler(&ctx->restart_handler);
	अगर (err) अणु
		iounmap(ctx->csr);
		dev_err(dev, "cannot register restart handler (err=%d)\n", err);
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id xgene_reboot_of_match[] = अणु
	अणु .compatible = "apm,xgene-reboot" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver xgene_reboot_driver = अणु
	.probe = xgene_reboot_probe,
	.driver = अणु
		.name = "xgene-reboot",
		.of_match_table = xgene_reboot_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init xgene_reboot_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&xgene_reboot_driver);
पूर्ण
device_initcall(xgene_reboot_init);
