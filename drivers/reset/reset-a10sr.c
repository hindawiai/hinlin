<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright Intel Corporation (C) 2017. All Rights Reserved
 *
 * Reset driver क्रम Altera Arria10 MAX5 System Resource Chip
 *
 * Adapted from reset-socfpga.c
 */

#समावेश <linux/err.h>
#समावेश <linux/mfd/altera-a10sr.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>

#समावेश <dt-bindings/reset/altr,rst-mgr-a10sr.h>

काष्ठा a10sr_reset अणु
	काष्ठा reset_controller_dev     rcdev;
	काष्ठा regmap *regmap;
पूर्ण;

अटल अंतरभूत काष्ठा a10sr_reset *to_a10sr_rst(काष्ठा reset_controller_dev *rc)
अणु
	वापस container_of(rc, काष्ठा a10sr_reset, rcdev);
पूर्ण

अटल अंतरभूत पूर्णांक a10sr_reset_shअगरt(अचिन्हित दीर्घ id)
अणु
	चयन (id) अणु
	हाल A10SR_RESET_ENET_HPS:
		वापस 1;
	हाल A10SR_RESET_PCIE:
	हाल A10SR_RESET_खाता:
	हाल A10SR_RESET_BQSPI:
	हाल A10SR_RESET_USB:
		वापस id + 11;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक a10sr_reset_update(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id, bool निश्चित)
अणु
	काष्ठा a10sr_reset *a10r = to_a10sr_rst(rcdev);
	पूर्णांक offset = a10sr_reset_shअगरt(id);
	u8 mask = ALTR_A10SR_REG_BIT_MASK(offset);
	पूर्णांक index = ALTR_A10SR_HPS_RST_REG + ALTR_A10SR_REG_OFFSET(offset);

	वापस regmap_update_bits(a10r->regmap, index, mask, निश्चित ? 0 : mask);
पूर्ण

अटल पूर्णांक a10sr_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id)
अणु
	वापस a10sr_reset_update(rcdev, id, true);
पूर्ण

अटल पूर्णांक a10sr_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id)
अणु
	वापस a10sr_reset_update(rcdev, id, false);
पूर्ण

अटल पूर्णांक a10sr_reset_status(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id)
अणु
	पूर्णांक ret;
	काष्ठा a10sr_reset *a10r = to_a10sr_rst(rcdev);
	पूर्णांक offset = a10sr_reset_shअगरt(id);
	u8 mask = ALTR_A10SR_REG_BIT_MASK(offset);
	पूर्णांक index = ALTR_A10SR_HPS_RST_REG + ALTR_A10SR_REG_OFFSET(offset);
	अचिन्हित पूर्णांक value;

	ret = regmap_पढ़ो(a10r->regmap, index, &value);
	अगर (ret < 0)
		वापस ret;

	वापस !!(value & mask);
पूर्ण

अटल स्थिर काष्ठा reset_control_ops a10sr_reset_ops = अणु
	.निश्चित		= a10sr_reset_निश्चित,
	.deनिश्चित	= a10sr_reset_deनिश्चित,
	.status		= a10sr_reset_status,
पूर्ण;

अटल पूर्णांक a10sr_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा altr_a10sr *a10sr = dev_get_drvdata(pdev->dev.parent);
	काष्ठा a10sr_reset *a10r;

	a10r = devm_kzalloc(&pdev->dev, माप(काष्ठा a10sr_reset),
			    GFP_KERNEL);
	अगर (!a10r)
		वापस -ENOMEM;

	a10r->rcdev.owner = THIS_MODULE;
	a10r->rcdev.nr_resets = A10SR_RESET_NUM;
	a10r->rcdev.ops = &a10sr_reset_ops;
	a10r->rcdev.of_node = pdev->dev.of_node;
	a10r->regmap = a10sr->regmap;

	platक्रमm_set_drvdata(pdev, a10r);

	वापस devm_reset_controller_रेजिस्टर(&pdev->dev, &a10r->rcdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id a10sr_reset_of_match[] = अणु
	अणु .compatible = "altr,a10sr-reset" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, a10sr_reset_of_match);

अटल काष्ठा platक्रमm_driver a10sr_reset_driver = अणु
	.probe	= a10sr_reset_probe,
	.driver = अणु
		.name		= "altr_a10sr_reset",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(a10sr_reset_driver);

MODULE_AUTHOR("Thor Thayer <thor.thayer@linux.intel.com>");
MODULE_DESCRIPTION("Altera Arria10 System Resource Reset Controller Driver");
MODULE_LICENSE("GPL v2");
