<शैली गुरु>
/*
 * Copyright (C) 2017 Synopsys.
 *
 * Synopsys HSDK Development platक्रमm reset driver.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#घोषणा to_hsdk_rst(p)	container_of((p), काष्ठा hsdk_rst, rcdev)

काष्ठा hsdk_rst अणु
	व्योम __iomem			*regs_ctl;
	व्योम __iomem			*regs_rst;
	spinlock_t			lock;
	काष्ठा reset_controller_dev	rcdev;
पूर्ण;

अटल स्थिर u32 rst_map[] = अणु
	BIT(16), /* APB_RST  */
	BIT(17), /* AXI_RST  */
	BIT(18), /* ETH_RST  */
	BIT(19), /* USB_RST  */
	BIT(20), /* SDIO_RST */
	BIT(21), /* HDMI_RST */
	BIT(22), /* GFX_RST  */
	BIT(25), /* DMAC_RST */
	BIT(31), /* EBI_RST  */
पूर्ण;

#घोषणा HSDK_MAX_RESETS			ARRAY_SIZE(rst_map)

#घोषणा CGU_SYS_RST_CTRL		0x0
#घोषणा CGU_IP_SW_RESET			0x0
#घोषणा CGU_IP_SW_RESET_DELAY_SHIFT	16
#घोषणा CGU_IP_SW_RESET_DELAY_MASK	GENMASK(31, CGU_IP_SW_RESET_DELAY_SHIFT)
#घोषणा CGU_IP_SW_RESET_DELAY		0
#घोषणा CGU_IP_SW_RESET_RESET		BIT(0)
#घोषणा SW_RESET_TIMEOUT		10000

अटल व्योम hsdk_reset_config(काष्ठा hsdk_rst *rst, अचिन्हित दीर्घ id)
अणु
	ग_लिखोl(rst_map[id], rst->regs_ctl + CGU_SYS_RST_CTRL);
पूर्ण

अटल पूर्णांक hsdk_reset_करो(काष्ठा hsdk_rst *rst)
अणु
	u32 reg;

	reg = पढ़ोl(rst->regs_rst + CGU_IP_SW_RESET);
	reg &= ~CGU_IP_SW_RESET_DELAY_MASK;
	reg |= CGU_IP_SW_RESET_DELAY << CGU_IP_SW_RESET_DELAY_SHIFT;
	reg |= CGU_IP_SW_RESET_RESET;
	ग_लिखोl(reg, rst->regs_rst + CGU_IP_SW_RESET);

	/* रुको till reset bit is back to 0 */
	वापस पढ़ोl_poll_समयout_atomic(rst->regs_rst + CGU_IP_SW_RESET, reg,
		!(reg & CGU_IP_SW_RESET_RESET), 5, SW_RESET_TIMEOUT);
पूर्ण

अटल पूर्णांक hsdk_reset_reset(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id)
अणु
	काष्ठा hsdk_rst *rst = to_hsdk_rst(rcdev);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&rst->lock, flags);
	hsdk_reset_config(rst, id);
	ret = hsdk_reset_करो(rst);
	spin_unlock_irqrestore(&rst->lock, flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा reset_control_ops hsdk_reset_ops = अणु
	.reset	= hsdk_reset_reset,
	.deनिश्चित = hsdk_reset_reset,
पूर्ण;

अटल पूर्णांक hsdk_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hsdk_rst *rst;
	काष्ठा resource *mem;

	rst = devm_kzalloc(&pdev->dev, माप(*rst), GFP_KERNEL);
	अगर (!rst)
		वापस -ENOMEM;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	rst->regs_ctl = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(rst->regs_ctl))
		वापस PTR_ERR(rst->regs_ctl);

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	rst->regs_rst = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(rst->regs_rst))
		वापस PTR_ERR(rst->regs_rst);

	spin_lock_init(&rst->lock);

	rst->rcdev.owner = THIS_MODULE;
	rst->rcdev.ops = &hsdk_reset_ops;
	rst->rcdev.of_node = pdev->dev.of_node;
	rst->rcdev.nr_resets = HSDK_MAX_RESETS;
	rst->rcdev.of_reset_n_cells = 1;

	वापस reset_controller_रेजिस्टर(&rst->rcdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id hsdk_reset_dt_match[] = अणु
	अणु .compatible = "snps,hsdk-reset" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver hsdk_reset_driver = अणु
	.probe	= hsdk_reset_probe,
	.driver	= अणु
		.name = "hsdk-reset",
		.of_match_table = hsdk_reset_dt_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(hsdk_reset_driver);

MODULE_AUTHOR("Eugeniy Paltsev <Eugeniy.Paltsev@synopsys.com>");
MODULE_DESCRIPTION("Synopsys HSDK SDP reset driver");
MODULE_LICENSE("GPL v2");
