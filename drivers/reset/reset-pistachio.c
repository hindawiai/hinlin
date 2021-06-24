<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Pistachio SoC Reset Controller driver
 *
 * Copyright (C) 2015 Imagination Technologies Ltd.
 *
 * Author: Damien Horsley <Damien.Horsley@imgtec.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/syscon.h>

#समावेश <dt-bindings/reset/pistachio-resets.h>

#घोषणा	PISTACHIO_SOFT_RESET		0

काष्ठा pistachio_reset_data अणु
	काष्ठा reset_controller_dev	rcdev;
	काष्ठा regmap			*periph_regs;
पूर्ण;

अटल अंतरभूत पूर्णांक pistachio_reset_shअगरt(अचिन्हित दीर्घ id)
अणु
	चयन (id) अणु
	हाल PISTACHIO_RESET_I2C0:
	हाल PISTACHIO_RESET_I2C1:
	हाल PISTACHIO_RESET_I2C2:
	हाल PISTACHIO_RESET_I2C3:
	हाल PISTACHIO_RESET_I2S_IN:
	हाल PISTACHIO_RESET_PRL_OUT:
	हाल PISTACHIO_RESET_SPDIF_OUT:
	हाल PISTACHIO_RESET_SPI:
	हाल PISTACHIO_RESET_PWM_PDM:
	हाल PISTACHIO_RESET_UART0:
	हाल PISTACHIO_RESET_UART1:
	हाल PISTACHIO_RESET_QSPI:
	हाल PISTACHIO_RESET_MDC:
	हाल PISTACHIO_RESET_SDHOST:
	हाल PISTACHIO_RESET_ETHERNET:
	हाल PISTACHIO_RESET_IR:
	हाल PISTACHIO_RESET_HASH:
	हाल PISTACHIO_RESET_TIMER:
		वापस id;
	हाल PISTACHIO_RESET_I2S_OUT:
	हाल PISTACHIO_RESET_SPDIF_IN:
	हाल PISTACHIO_RESET_EVT:
		वापस id + 6;
	हाल PISTACHIO_RESET_USB_H:
	हाल PISTACHIO_RESET_USB_PR:
	हाल PISTACHIO_RESET_USB_PHY_PR:
	हाल PISTACHIO_RESET_USB_PHY_PON:
		वापस id + 7;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक pistachio_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
				  अचिन्हित दीर्घ id)
अणु
	काष्ठा pistachio_reset_data *rd;
	u32 mask;
	पूर्णांक shअगरt;

	rd = container_of(rcdev, काष्ठा pistachio_reset_data, rcdev);
	shअगरt = pistachio_reset_shअगरt(id);
	अगर (shअगरt < 0)
		वापस shअगरt;
	mask = BIT(shअगरt);

	वापस regmap_update_bits(rd->periph_regs, PISTACHIO_SOFT_RESET,
				  mask, mask);
पूर्ण

अटल पूर्णांक pistachio_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				    अचिन्हित दीर्घ id)
अणु
	काष्ठा pistachio_reset_data *rd;
	u32 mask;
	पूर्णांक shअगरt;

	rd = container_of(rcdev, काष्ठा pistachio_reset_data, rcdev);
	shअगरt = pistachio_reset_shअगरt(id);
	अगर (shअगरt < 0)
		वापस shअगरt;
	mask = BIT(shअगरt);

	वापस regmap_update_bits(rd->periph_regs, PISTACHIO_SOFT_RESET,
				  mask, 0);
पूर्ण

अटल स्थिर काष्ठा reset_control_ops pistachio_reset_ops = अणु
	.निश्चित		= pistachio_reset_निश्चित,
	.deनिश्चित	= pistachio_reset_deनिश्चित,
पूर्ण;

अटल पूर्णांक pistachio_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pistachio_reset_data *rd;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = pdev->dev.of_node;

	rd = devm_kzalloc(dev, माप(*rd), GFP_KERNEL);
	अगर (!rd)
		वापस -ENOMEM;

	rd->periph_regs = syscon_node_to_regmap(np->parent);
	अगर (IS_ERR(rd->periph_regs))
		वापस PTR_ERR(rd->periph_regs);

	rd->rcdev.owner = THIS_MODULE;
	rd->rcdev.nr_resets = PISTACHIO_RESET_MAX + 1;
	rd->rcdev.ops = &pistachio_reset_ops;
	rd->rcdev.of_node = np;

	वापस devm_reset_controller_रेजिस्टर(dev, &rd->rcdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id pistachio_reset_dt_ids[] = अणु
	 अणु .compatible = "img,pistachio-reset", पूर्ण,
	 अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver pistachio_reset_driver = अणु
	.probe	= pistachio_reset_probe,
	.driver = अणु
		.name		= "pistachio-reset",
		.of_match_table	= pistachio_reset_dt_ids,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(pistachio_reset_driver);
