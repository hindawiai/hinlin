<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2016-2017 Linaro Ltd.
 * Copyright (c) 2016-2017 HiSilicon Technologies Co., Ltd.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset-controller.h>

काष्ठा hi3660_reset_controller अणु
	काष्ठा reset_controller_dev rst;
	काष्ठा regmap *map;
पूर्ण;

#घोषणा to_hi3660_reset_controller(_rst) \
	container_of(_rst, काष्ठा hi3660_reset_controller, rst)

अटल पूर्णांक hi3660_reset_program_hw(काष्ठा reset_controller_dev *rcdev,
				   अचिन्हित दीर्घ idx, bool निश्चित)
अणु
	काष्ठा hi3660_reset_controller *rc = to_hi3660_reset_controller(rcdev);
	अचिन्हित पूर्णांक offset = idx >> 8;
	अचिन्हित पूर्णांक mask = BIT(idx & 0x1f);

	अगर (निश्चित)
		वापस regmap_ग_लिखो(rc->map, offset, mask);
	अन्यथा
		वापस regmap_ग_लिखो(rc->map, offset + 4, mask);
पूर्ण

अटल पूर्णांक hi3660_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ idx)
अणु
	वापस hi3660_reset_program_hw(rcdev, idx, true);
पूर्ण

अटल पूर्णांक hi3660_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				 अचिन्हित दीर्घ idx)
अणु
	वापस hi3660_reset_program_hw(rcdev, idx, false);
पूर्ण

अटल पूर्णांक hi3660_reset_dev(काष्ठा reset_controller_dev *rcdev,
			    अचिन्हित दीर्घ idx)
अणु
	पूर्णांक err;

	err = hi3660_reset_निश्चित(rcdev, idx);
	अगर (err)
		वापस err;

	वापस hi3660_reset_deनिश्चित(rcdev, idx);
पूर्ण

अटल स्थिर काष्ठा reset_control_ops hi3660_reset_ops = अणु
	.reset    = hi3660_reset_dev,
	.निश्चित   = hi3660_reset_निश्चित,
	.deनिश्चित = hi3660_reset_deनिश्चित,
पूर्ण;

अटल पूर्णांक hi3660_reset_xlate(काष्ठा reset_controller_dev *rcdev,
			      स्थिर काष्ठा of_phandle_args *reset_spec)
अणु
	अचिन्हित पूर्णांक offset, bit;

	offset = reset_spec->args[0];
	bit = reset_spec->args[1];

	वापस (offset << 8) | bit;
पूर्ण

अटल पूर्णांक hi3660_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hi3660_reset_controller *rc;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;

	rc = devm_kzalloc(dev, माप(*rc), GFP_KERNEL);
	अगर (!rc)
		वापस -ENOMEM;

	rc->map = syscon_regmap_lookup_by_phandle(np, "hisilicon,rst-syscon");
	अगर (rc->map == ERR_PTR(-ENODEV)) अणु
		/* fall back to the deprecated compatible */
		rc->map = syscon_regmap_lookup_by_phandle(np,
							  "hisi,rst-syscon");
	पूर्ण
	अगर (IS_ERR(rc->map)) अणु
		dev_err(dev, "failed to get hisilicon,rst-syscon\n");
		वापस PTR_ERR(rc->map);
	पूर्ण

	rc->rst.ops = &hi3660_reset_ops,
	rc->rst.of_node = np;
	rc->rst.of_reset_n_cells = 2;
	rc->rst.of_xlate = hi3660_reset_xlate;

	वापस reset_controller_रेजिस्टर(&rc->rst);
पूर्ण

अटल स्थिर काष्ठा of_device_id hi3660_reset_match[] = अणु
	अणु .compatible = "hisilicon,hi3660-reset", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hi3660_reset_match);

अटल काष्ठा platक्रमm_driver hi3660_reset_driver = अणु
	.probe = hi3660_reset_probe,
	.driver = अणु
		.name = "hi3660-reset",
		.of_match_table = hi3660_reset_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init hi3660_reset_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&hi3660_reset_driver);
पूर्ण
arch_initcall(hi3660_reset_init);

MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:hi3660-reset");
MODULE_DESCRIPTION("HiSilicon Hi3660 Reset Driver");
