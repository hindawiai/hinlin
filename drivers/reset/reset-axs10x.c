<शैली गुरु>
/*
 * Copyright (C) 2017 Synopsys.
 *
 * Synopsys AXS10x reset driver.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>

#घोषणा to_axs10x_rst(p)	container_of((p), काष्ठा axs10x_rst, rcdev)

#घोषणा AXS10X_MAX_RESETS	32

काष्ठा axs10x_rst अणु
	व्योम __iomem			*regs_rst;
	spinlock_t			lock;
	काष्ठा reset_controller_dev	rcdev;
पूर्ण;

अटल पूर्णांक axs10x_reset_reset(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id)
अणु
	काष्ठा axs10x_rst *rst = to_axs10x_rst(rcdev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rst->lock, flags);
	ग_लिखोl(BIT(id), rst->regs_rst);
	spin_unlock_irqrestore(&rst->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reset_control_ops axs10x_reset_ops = अणु
	.reset	= axs10x_reset_reset,
पूर्ण;

अटल पूर्णांक axs10x_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा axs10x_rst *rst;
	काष्ठा resource *mem;

	rst = devm_kzalloc(&pdev->dev, माप(*rst), GFP_KERNEL);
	अगर (!rst)
		वापस -ENOMEM;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	rst->regs_rst = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(rst->regs_rst))
		वापस PTR_ERR(rst->regs_rst);

	spin_lock_init(&rst->lock);

	rst->rcdev.owner = THIS_MODULE;
	rst->rcdev.ops = &axs10x_reset_ops;
	rst->rcdev.of_node = pdev->dev.of_node;
	rst->rcdev.nr_resets = AXS10X_MAX_RESETS;

	वापस devm_reset_controller_रेजिस्टर(&pdev->dev, &rst->rcdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id axs10x_reset_dt_match[] = अणु
	अणु .compatible = "snps,axs10x-reset" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver axs10x_reset_driver = अणु
	.probe	= axs10x_reset_probe,
	.driver	= अणु
		.name = "axs10x-reset",
		.of_match_table = axs10x_reset_dt_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(axs10x_reset_driver);

MODULE_AUTHOR("Eugeniy Paltsev <Eugeniy.Paltsev@synopsys.com>");
MODULE_DESCRIPTION("Synopsys AXS10x reset driver");
MODULE_LICENSE("GPL v2");
