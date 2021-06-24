<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Simple Reset Controller Driver
 *
 * Copyright (C) 2017 Pengutronix, Philipp Zabel <kernel@pengutronix.de>
 *
 * Based on Allwinner SoCs Reset Controller driver
 *
 * Copyright 2013 Maxime Ripard
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/reset/reset-simple.h>
#समावेश <linux/spinlock.h>

अटल अंतरभूत काष्ठा reset_simple_data *
to_reset_simple_data(काष्ठा reset_controller_dev *rcdev)
अणु
	वापस container_of(rcdev, काष्ठा reset_simple_data, rcdev);
पूर्ण

अटल पूर्णांक reset_simple_update(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ id, bool निश्चित)
अणु
	काष्ठा reset_simple_data *data = to_reset_simple_data(rcdev);
	पूर्णांक reg_width = माप(u32);
	पूर्णांक bank = id / (reg_width * BITS_PER_BYTE);
	पूर्णांक offset = id % (reg_width * BITS_PER_BYTE);
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(&data->lock, flags);

	reg = पढ़ोl(data->membase + (bank * reg_width));
	अगर (निश्चित ^ data->active_low)
		reg |= BIT(offset);
	अन्यथा
		reg &= ~BIT(offset);
	ग_लिखोl(reg, data->membase + (bank * reg_width));

	spin_unlock_irqrestore(&data->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक reset_simple_निश्चित(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ id)
अणु
	वापस reset_simple_update(rcdev, id, true);
पूर्ण

अटल पूर्णांक reset_simple_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				 अचिन्हित दीर्घ id)
अणु
	वापस reset_simple_update(rcdev, id, false);
पूर्ण

अटल पूर्णांक reset_simple_reset(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id)
अणु
	काष्ठा reset_simple_data *data = to_reset_simple_data(rcdev);
	पूर्णांक ret;

	अगर (!data->reset_us)
		वापस -ENOTSUPP;

	ret = reset_simple_निश्चित(rcdev, id);
	अगर (ret)
		वापस ret;

	usleep_range(data->reset_us, data->reset_us * 2);

	वापस reset_simple_deनिश्चित(rcdev, id);
पूर्ण

अटल पूर्णांक reset_simple_status(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ id)
अणु
	काष्ठा reset_simple_data *data = to_reset_simple_data(rcdev);
	पूर्णांक reg_width = माप(u32);
	पूर्णांक bank = id / (reg_width * BITS_PER_BYTE);
	पूर्णांक offset = id % (reg_width * BITS_PER_BYTE);
	u32 reg;

	reg = पढ़ोl(data->membase + (bank * reg_width));

	वापस !(reg & BIT(offset)) ^ !data->status_active_low;
पूर्ण

स्थिर काष्ठा reset_control_ops reset_simple_ops = अणु
	.निश्चित		= reset_simple_निश्चित,
	.deनिश्चित	= reset_simple_deनिश्चित,
	.reset		= reset_simple_reset,
	.status		= reset_simple_status,
पूर्ण;
EXPORT_SYMBOL_GPL(reset_simple_ops);

/**
 * काष्ठा reset_simple_devdata - simple reset controller properties
 * @reg_offset: offset between base address and first reset रेजिस्टर.
 * @nr_resets: number of resets. If not set, शेष to resource size in bits.
 * @active_low: अगर true, bits are cleared to निश्चित the reset. Otherwise, bits
 *              are set to निश्चित the reset.
 * @status_active_low: अगर true, bits पढ़ो back as cleared जबतक the reset is
 *                     निश्चितed. Otherwise, bits पढ़ो back as set जबतक the
 *                     reset is निश्चितed.
 */
काष्ठा reset_simple_devdata अणु
	u32 reg_offset;
	u32 nr_resets;
	bool active_low;
	bool status_active_low;
पूर्ण;

#घोषणा SOCFPGA_NR_BANKS	8

अटल स्थिर काष्ठा reset_simple_devdata reset_simple_socfpga = अणु
	.reg_offset = 0x20,
	.nr_resets = SOCFPGA_NR_BANKS * 32,
	.status_active_low = true,
पूर्ण;

अटल स्थिर काष्ठा reset_simple_devdata reset_simple_active_low = अणु
	.active_low = true,
	.status_active_low = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id reset_simple_dt_ids[] = अणु
	अणु .compatible = "altr,stratix10-rst-mgr",
		.data = &reset_simple_socfpga पूर्ण,
	अणु .compatible = "st,stm32-rcc", पूर्ण,
	अणु .compatible = "allwinner,sun6i-a31-clock-reset",
		.data = &reset_simple_active_low पूर्ण,
	अणु .compatible = "zte,zx296718-reset",
		.data = &reset_simple_active_low पूर्ण,
	अणु .compatible = "aspeed,ast2400-lpc-reset" पूर्ण,
	अणु .compatible = "aspeed,ast2500-lpc-reset" पूर्ण,
	अणु .compatible = "bitmain,bm1880-reset",
		.data = &reset_simple_active_low पूर्ण,
	अणु .compatible = "brcm,bcm4908-misc-pcie-reset",
		.data = &reset_simple_active_low पूर्ण,
	अणु .compatible = "snps,dw-high-reset" पूर्ण,
	अणु .compatible = "snps,dw-low-reset",
		.data = &reset_simple_active_low पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल पूर्णांक reset_simple_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा reset_simple_devdata *devdata;
	काष्ठा reset_simple_data *data;
	व्योम __iomem *membase;
	काष्ठा resource *res;
	u32 reg_offset = 0;

	devdata = of_device_get_match_data(dev);

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	membase = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(membase))
		वापस PTR_ERR(membase);

	spin_lock_init(&data->lock);
	data->membase = membase;
	data->rcdev.owner = THIS_MODULE;
	data->rcdev.nr_resets = resource_size(res) * BITS_PER_BYTE;
	data->rcdev.ops = &reset_simple_ops;
	data->rcdev.of_node = dev->of_node;

	अगर (devdata) अणु
		reg_offset = devdata->reg_offset;
		अगर (devdata->nr_resets)
			data->rcdev.nr_resets = devdata->nr_resets;
		data->active_low = devdata->active_low;
		data->status_active_low = devdata->status_active_low;
	पूर्ण

	data->membase += reg_offset;

	वापस devm_reset_controller_रेजिस्टर(dev, &data->rcdev);
पूर्ण

अटल काष्ठा platक्रमm_driver reset_simple_driver = अणु
	.probe	= reset_simple_probe,
	.driver = अणु
		.name		= "simple-reset",
		.of_match_table	= reset_simple_dt_ids,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(reset_simple_driver);
