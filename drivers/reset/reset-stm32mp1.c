<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics 2018 - All Rights Reserved
 * Author: Gabriel Fernandez <gabriel.fernandez@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>

#घोषणा CLR_OFFSET 0x4

काष्ठा sपंचांग32_reset_data अणु
	काष्ठा reset_controller_dev	rcdev;
	व्योम __iomem			*membase;
पूर्ण;

अटल अंतरभूत काष्ठा sपंचांग32_reset_data *
to_sपंचांग32_reset_data(काष्ठा reset_controller_dev *rcdev)
अणु
	वापस container_of(rcdev, काष्ठा sपंचांग32_reset_data, rcdev);
पूर्ण

अटल पूर्णांक sपंचांग32_reset_update(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id, bool निश्चित)
अणु
	काष्ठा sपंचांग32_reset_data *data = to_sपंचांग32_reset_data(rcdev);
	पूर्णांक reg_width = माप(u32);
	पूर्णांक bank = id / (reg_width * BITS_PER_BYTE);
	पूर्णांक offset = id % (reg_width * BITS_PER_BYTE);
	व्योम __iomem *addr;

	addr = data->membase + (bank * reg_width);
	अगर (!निश्चित)
		addr += CLR_OFFSET;

	ग_लिखोl(BIT(offset), addr);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id)
अणु
	वापस sपंचांग32_reset_update(rcdev, id, true);
पूर्ण

अटल पूर्णांक sपंचांग32_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id)
अणु
	वापस sपंचांग32_reset_update(rcdev, id, false);
पूर्ण

अटल पूर्णांक sपंचांग32_reset_status(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id)
अणु
	काष्ठा sपंचांग32_reset_data *data = to_sपंचांग32_reset_data(rcdev);
	पूर्णांक reg_width = माप(u32);
	पूर्णांक bank = id / (reg_width * BITS_PER_BYTE);
	पूर्णांक offset = id % (reg_width * BITS_PER_BYTE);
	u32 reg;

	reg = पढ़ोl(data->membase + (bank * reg_width));

	वापस !!(reg & BIT(offset));
पूर्ण

अटल स्थिर काष्ठा reset_control_ops sपंचांग32_reset_ops = अणु
	.निश्चित		= sपंचांग32_reset_निश्चित,
	.deनिश्चित	= sपंचांग32_reset_deनिश्चित,
	.status		= sपंचांग32_reset_status,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32_reset_dt_ids[] = अणु
	अणु .compatible = "st,stm32mp1-rcc"पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल पूर्णांक sपंचांग32_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sपंचांग32_reset_data *data;
	व्योम __iomem *membase;
	काष्ठा resource *res;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	membase = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(membase))
		वापस PTR_ERR(membase);

	data->membase = membase;
	data->rcdev.owner = THIS_MODULE;
	data->rcdev.nr_resets = resource_size(res) * BITS_PER_BYTE;
	data->rcdev.ops = &sपंचांग32_reset_ops;
	data->rcdev.of_node = dev->of_node;

	वापस devm_reset_controller_रेजिस्टर(dev, &data->rcdev);
पूर्ण

अटल काष्ठा platक्रमm_driver sपंचांग32_reset_driver = अणु
	.probe	= sपंचांग32_reset_probe,
	.driver = अणु
		.name		= "stm32mp1-reset",
		.of_match_table	= sपंचांग32_reset_dt_ids,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(sपंचांग32_reset_driver);
