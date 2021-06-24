<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* DSA driver क्रम:
 * Vitesse VSC7385 SparX-G5 5+1-port Integrated Gigabit Ethernet Switch
 * Vitesse VSC7388 SparX-G8 8-port Integrated Gigabit Ethernet Switch
 * Vitesse VSC7395 SparX-G5e 5+1-port Integrated Gigabit Ethernet Switch
 * Vitesse VSC7398 SparX-G8e 8-port Integrated Gigabit Ethernet Switch
 *
 * This driver takes control of the चयन chip connected over CPU-attached
 * address bus and configures it to route packages around when connected to
 * a CPU port.
 *
 * Copyright (C) 2019 Pawel Dembicki <paweldembicki@gmail.com>
 * Based on vitesse-vsc-spi.c by:
 * Copyright (C) 2018 Linus Wallej <linus.walleij@linaro.org>
 * Includes portions of code from the firmware uploader by:
 * Copyright (C) 2009 Gabor Juhos <juhosg@खोलोwrt.org>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "vitesse-vsc73xx.h"

#घोषणा VSC73XX_CMD_PLATFORM_BLOCK_SHIFT		14
#घोषणा VSC73XX_CMD_PLATFORM_BLOCK_MASK			0x7
#घोषणा VSC73XX_CMD_PLATFORM_SUBBLOCK_SHIFT		10
#घोषणा VSC73XX_CMD_PLATFORM_SUBBLOCK_MASK		0xf
#घोषणा VSC73XX_CMD_PLATFORM_REGISTER_SHIFT		2

/*
 * काष्ठा vsc73xx_platक्रमm - VSC73xx Platक्रमm state container
 */
काष्ठा vsc73xx_platक्रमm अणु
	काष्ठा platक्रमm_device	*pdev;
	व्योम __iomem		*base_addr;
	काष्ठा vsc73xx		vsc;
पूर्ण;

अटल स्थिर काष्ठा vsc73xx_ops vsc73xx_platक्रमm_ops;

अटल u32 vsc73xx_make_addr(u8 block, u8 subblock, u8 reg)
अणु
	u32 ret;

	ret = (block & VSC73XX_CMD_PLATFORM_BLOCK_MASK)
	    << VSC73XX_CMD_PLATFORM_BLOCK_SHIFT;
	ret |= (subblock & VSC73XX_CMD_PLATFORM_SUBBLOCK_MASK)
	    << VSC73XX_CMD_PLATFORM_SUBBLOCK_SHIFT;
	ret |= reg << VSC73XX_CMD_PLATFORM_REGISTER_SHIFT;

	वापस ret;
पूर्ण

अटल पूर्णांक vsc73xx_platक्रमm_पढ़ो(काष्ठा vsc73xx *vsc, u8 block, u8 subblock,
				 u8 reg, u32 *val)
अणु
	काष्ठा vsc73xx_platक्रमm *vsc_platक्रमm = vsc->priv;
	u32 offset;

	अगर (!vsc73xx_is_addr_valid(block, subblock))
		वापस -EINVAL;

	offset = vsc73xx_make_addr(block, subblock, reg);
	/* By शेष vsc73xx running in big-endian mode.
	 * (See "Register Addressing" section 5.5.3 in the VSC7385 manual.)
	 */
	*val = ioपढ़ो32be(vsc_platक्रमm->base_addr + offset);

	वापस 0;
पूर्ण

अटल पूर्णांक vsc73xx_platक्रमm_ग_लिखो(काष्ठा vsc73xx *vsc, u8 block, u8 subblock,
				  u8 reg, u32 val)
अणु
	काष्ठा vsc73xx_platक्रमm *vsc_platक्रमm = vsc->priv;
	u32 offset;

	अगर (!vsc73xx_is_addr_valid(block, subblock))
		वापस -EINVAL;

	offset = vsc73xx_make_addr(block, subblock, reg);
	ioग_लिखो32be(val, vsc_platक्रमm->base_addr + offset);

	वापस 0;
पूर्ण

अटल पूर्णांक vsc73xx_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा vsc73xx_platक्रमm *vsc_platक्रमm;
	पूर्णांक ret;

	vsc_platक्रमm = devm_kzalloc(dev, माप(*vsc_platक्रमm), GFP_KERNEL);
	अगर (!vsc_platक्रमm)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, vsc_platक्रमm);
	vsc_platक्रमm->pdev = pdev;
	vsc_platक्रमm->vsc.dev = dev;
	vsc_platक्रमm->vsc.priv = vsc_platक्रमm;
	vsc_platक्रमm->vsc.ops = &vsc73xx_platक्रमm_ops;

	/* obtain I/O memory space */
	vsc_platक्रमm->base_addr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(vsc_platक्रमm->base_addr)) अणु
		dev_err(&pdev->dev, "cannot request I/O memory space\n");
		ret = -ENXIO;
		वापस ret;
	पूर्ण

	वापस vsc73xx_probe(&vsc_platक्रमm->vsc);
पूर्ण

अटल पूर्णांक vsc73xx_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vsc73xx_platक्रमm *vsc_platक्रमm = platक्रमm_get_drvdata(pdev);

	वापस vsc73xx_हटाओ(&vsc_platक्रमm->vsc);
पूर्ण

अटल स्थिर काष्ठा vsc73xx_ops vsc73xx_platक्रमm_ops = अणु
	.पढ़ो = vsc73xx_platक्रमm_पढ़ो,
	.ग_लिखो = vsc73xx_platक्रमm_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा of_device_id vsc73xx_of_match[] = अणु
	अणु
		.compatible = "vitesse,vsc7385",
	पूर्ण,
	अणु
		.compatible = "vitesse,vsc7388",
	पूर्ण,
	अणु
		.compatible = "vitesse,vsc7395",
	पूर्ण,
	अणु
		.compatible = "vitesse,vsc7398",
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, vsc73xx_of_match);

अटल काष्ठा platक्रमm_driver vsc73xx_platक्रमm_driver = अणु
	.probe = vsc73xx_platक्रमm_probe,
	.हटाओ = vsc73xx_platक्रमm_हटाओ,
	.driver = अणु
		.name = "vsc73xx-platform",
		.of_match_table = vsc73xx_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(vsc73xx_platक्रमm_driver);

MODULE_AUTHOR("Pawel Dembicki <paweldembicki@gmail.com>");
MODULE_DESCRIPTION("Vitesse VSC7385/7388/7395/7398 Platform driver");
MODULE_LICENSE("GPL v2");
