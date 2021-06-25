<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2018-2020 Broadcom */

#समावेश <linux/device.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>

#घोषणा BRCM_RESCAL_START	0x0
#घोषणा  BRCM_RESCAL_START_BIT	BIT(0)
#घोषणा BRCM_RESCAL_CTRL	0x4
#घोषणा BRCM_RESCAL_STATUS	0x8
#घोषणा  BRCM_RESCAL_STATUS_BIT	BIT(0)

काष्ठा brcm_rescal_reset अणु
	व्योम __iomem *base;
	काष्ठा device *dev;
	काष्ठा reset_controller_dev rcdev;
पूर्ण;

अटल पूर्णांक brcm_rescal_reset_set(काष्ठा reset_controller_dev *rcdev,
				 अचिन्हित दीर्घ id)
अणु
	काष्ठा brcm_rescal_reset *data =
		container_of(rcdev, काष्ठा brcm_rescal_reset, rcdev);
	व्योम __iomem *base = data->base;
	u32 reg;
	पूर्णांक ret;

	reg = पढ़ोl(base + BRCM_RESCAL_START);
	ग_लिखोl(reg | BRCM_RESCAL_START_BIT, base + BRCM_RESCAL_START);
	reg = पढ़ोl(base + BRCM_RESCAL_START);
	अगर (!(reg & BRCM_RESCAL_START_BIT)) अणु
		dev_err(data->dev, "failed to start SATA/PCIe rescal\n");
		वापस -EIO;
	पूर्ण

	ret = पढ़ोl_poll_समयout(base + BRCM_RESCAL_STATUS, reg,
				 !(reg & BRCM_RESCAL_STATUS_BIT), 100, 1000);
	अगर (ret) अणु
		dev_err(data->dev, "time out on SATA/PCIe rescal\n");
		वापस ret;
	पूर्ण

	reg = पढ़ोl(base + BRCM_RESCAL_START);
	ग_लिखोl(reg & ~BRCM_RESCAL_START_BIT, base + BRCM_RESCAL_START);

	dev_dbg(data->dev, "SATA/PCIe rescal success\n");

	वापस 0;
पूर्ण

अटल पूर्णांक brcm_rescal_reset_xlate(काष्ठा reset_controller_dev *rcdev,
				   स्थिर काष्ठा of_phandle_args *reset_spec)
अणु
	/* This is needed अगर #reset-cells == 0. */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reset_control_ops brcm_rescal_reset_ops = अणु
	.reset = brcm_rescal_reset_set,
पूर्ण;

अटल पूर्णांक brcm_rescal_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा brcm_rescal_reset *data;
	काष्ठा resource *res;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	data->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(data->base))
		वापस PTR_ERR(data->base);

	data->rcdev.owner = THIS_MODULE;
	data->rcdev.nr_resets = 1;
	data->rcdev.ops = &brcm_rescal_reset_ops;
	data->rcdev.of_node = pdev->dev.of_node;
	data->rcdev.of_xlate = brcm_rescal_reset_xlate;
	data->dev = &pdev->dev;

	वापस devm_reset_controller_रेजिस्टर(&pdev->dev, &data->rcdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id brcm_rescal_reset_of_match[] = अणु
	अणु .compatible = "brcm,bcm7216-pcie-sata-rescal" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, brcm_rescal_reset_of_match);

अटल काष्ठा platक्रमm_driver brcm_rescal_reset_driver = अणु
	.probe = brcm_rescal_reset_probe,
	.driver = अणु
		.name	= "brcm-rescal-reset",
		.of_match_table	= brcm_rescal_reset_of_match,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(brcm_rescal_reset_driver);

MODULE_AUTHOR("Broadcom");
MODULE_DESCRIPTION("Broadcom SATA/PCIe rescal reset controller");
MODULE_LICENSE("GPL v2");
