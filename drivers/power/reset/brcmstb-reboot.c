<शैली गुरु>
/*
 * Copyright (C) 2013 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/reboot.h>
#समावेश <linux/regmap.h>
#समावेश <linux/smp.h>
#समावेश <linux/mfd/syscon.h>

#घोषणा RESET_SOURCE_ENABLE_REG 1
#घोषणा SW_MASTER_RESET_REG 2

अटल काष्ठा regmap *regmap;
अटल u32 rst_src_en;
अटल u32 sw_mstr_rst;

काष्ठा reset_reg_mask अणु
	u32 rst_src_en_mask;
	u32 sw_mstr_rst_mask;
पूर्ण;

अटल स्थिर काष्ठा reset_reg_mask *reset_masks;

अटल पूर्णांक brcmstb_restart_handler(काष्ठा notअगरier_block *this,
				   अचिन्हित दीर्घ mode, व्योम *cmd)
अणु
	पूर्णांक rc;
	u32 पंचांगp;

	rc = regmap_ग_लिखो(regmap, rst_src_en, reset_masks->rst_src_en_mask);
	अगर (rc) अणु
		pr_err("failed to write rst_src_en (%d)\n", rc);
		वापस NOTIFY_DONE;
	पूर्ण

	rc = regmap_पढ़ो(regmap, rst_src_en, &पंचांगp);
	अगर (rc) अणु
		pr_err("failed to read rst_src_en (%d)\n", rc);
		वापस NOTIFY_DONE;
	पूर्ण

	rc = regmap_ग_लिखो(regmap, sw_mstr_rst, reset_masks->sw_mstr_rst_mask);
	अगर (rc) अणु
		pr_err("failed to write sw_mstr_rst (%d)\n", rc);
		वापस NOTIFY_DONE;
	पूर्ण

	rc = regmap_पढ़ो(regmap, sw_mstr_rst, &पंचांगp);
	अगर (rc) अणु
		pr_err("failed to read sw_mstr_rst (%d)\n", rc);
		वापस NOTIFY_DONE;
	पूर्ण

	जबतक (1)
		;

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block brcmstb_restart_nb = अणु
	.notअगरier_call = brcmstb_restart_handler,
	.priority = 128,
पूर्ण;

अटल स्थिर काष्ठा reset_reg_mask reset_bits_40nm = अणु
	.rst_src_en_mask = BIT(0),
	.sw_mstr_rst_mask = BIT(0),
पूर्ण;

अटल स्थिर काष्ठा reset_reg_mask reset_bits_65nm = अणु
	.rst_src_en_mask = BIT(3),
	.sw_mstr_rst_mask = BIT(31),
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_match[] = अणु
	अणु .compatible = "brcm,brcmstb-reboot", .data = &reset_bits_40nm पूर्ण,
	अणु .compatible = "brcm,bcm7038-reboot", .data = &reset_bits_65nm पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक brcmstb_reboot_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक rc;
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *of_id;

	of_id = of_match_node(of_match, np);
	अगर (!of_id) अणु
		pr_err("failed to look up compatible string\n");
		वापस -EINVAL;
	पूर्ण
	reset_masks = of_id->data;

	regmap = syscon_regmap_lookup_by_phandle(np, "syscon");
	अगर (IS_ERR(regmap)) अणु
		pr_err("failed to get syscon phandle\n");
		वापस -EINVAL;
	पूर्ण

	rc = of_property_पढ़ो_u32_index(np, "syscon", RESET_SOURCE_ENABLE_REG,
					&rst_src_en);
	अगर (rc) अणु
		pr_err("can't get rst_src_en offset (%d)\n", rc);
		वापस -EINVAL;
	पूर्ण

	rc = of_property_पढ़ो_u32_index(np, "syscon", SW_MASTER_RESET_REG,
					&sw_mstr_rst);
	अगर (rc) अणु
		pr_err("can't get sw_mstr_rst offset (%d)\n", rc);
		वापस -EINVAL;
	पूर्ण

	rc = रेजिस्टर_restart_handler(&brcmstb_restart_nb);
	अगर (rc)
		dev_err(&pdev->dev,
			"cannot register restart handler (err=%d)\n", rc);

	वापस rc;
पूर्ण

अटल काष्ठा platक्रमm_driver brcmstb_reboot_driver = अणु
	.probe = brcmstb_reboot_probe,
	.driver = अणु
		.name = "brcmstb-reboot",
		.of_match_table = of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init brcmstb_reboot_init(व्योम)
अणु
	वापस platक्रमm_driver_probe(&brcmstb_reboot_driver,
					brcmstb_reboot_probe);
पूर्ण
subsys_initcall(brcmstb_reboot_init);
