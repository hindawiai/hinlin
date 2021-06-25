<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 STMicroelectronics
 *
 * Power off Restart driver, used in STMicroelectronics devices.
 *
 * Author: Christophe Kerello <christophe.kerello@st.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/reboot.h>
#समावेश <linux/regmap.h>

काष्ठा reset_syscfg अणु
	काष्ठा regmap *regmap;
	/* syscfg used क्रम reset */
	अचिन्हित पूर्णांक offset_rst;
	अचिन्हित पूर्णांक mask_rst;
	/* syscfg used क्रम unmask the reset */
	अचिन्हित पूर्णांक offset_rst_msk;
	अचिन्हित पूर्णांक mask_rst_msk;
पूर्ण;

/* STiH407 */
#घोषणा STIH407_SYSCFG_4000	0x0
#घोषणा STIH407_SYSCFG_4008	0x20

अटल काष्ठा reset_syscfg stih407_reset = अणु
	.offset_rst = STIH407_SYSCFG_4000,
	.mask_rst = BIT(0),
	.offset_rst_msk = STIH407_SYSCFG_4008,
	.mask_rst_msk = BIT(0)
पूर्ण;


अटल काष्ठा reset_syscfg *st_restart_syscfg;

अटल पूर्णांक st_restart(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ mode,
		      व्योम *cmd)
अणु
	/* reset syscfg updated */
	regmap_update_bits(st_restart_syscfg->regmap,
			   st_restart_syscfg->offset_rst,
			   st_restart_syscfg->mask_rst,
			   0);

	/* unmask the reset */
	regmap_update_bits(st_restart_syscfg->regmap,
			   st_restart_syscfg->offset_rst_msk,
			   st_restart_syscfg->mask_rst_msk,
			   0);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block st_restart_nb = अणु
	.notअगरier_call = st_restart,
	.priority = 192,
पूर्ण;

अटल स्थिर काष्ठा of_device_id st_reset_of_match[] = अणु
	अणु
		.compatible = "st,stih407-restart",
		.data = (व्योम *)&stih407_reset,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक st_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device *dev = &pdev->dev;

	match = of_match_device(st_reset_of_match, dev);
	अगर (!match)
		वापस -ENODEV;

	st_restart_syscfg = (काष्ठा reset_syscfg *)match->data;

	st_restart_syscfg->regmap =
		syscon_regmap_lookup_by_phandle(np, "st,syscfg");
	अगर (IS_ERR(st_restart_syscfg->regmap)) अणु
		dev_err(dev, "No syscfg phandle specified\n");
		वापस PTR_ERR(st_restart_syscfg->regmap);
	पूर्ण

	वापस रेजिस्टर_restart_handler(&st_restart_nb);
पूर्ण

अटल काष्ठा platक्रमm_driver st_reset_driver = अणु
	.probe = st_reset_probe,
	.driver = अणु
		.name = "st_reset",
		.of_match_table = st_reset_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init st_reset_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&st_reset_driver);
पूर्ण

device_initcall(st_reset_init);

MODULE_AUTHOR("Christophe Kerello <christophe.kerello@st.com>");
MODULE_DESCRIPTION("STMicroelectronics Power off Restart driver");
MODULE_LICENSE("GPL v2");
