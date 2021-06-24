<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Broadcom STB generic reset controller क्रम SW_INIT style reset controller
 *
 * Author: Florian Fainelli <f.fainelli@gmail.com>
 * Copyright (C) 2018 Broadcom
 */
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/types.h>

काष्ठा brcmstb_reset अणु
	व्योम __iomem *base;
	काष्ठा reset_controller_dev rcdev;
पूर्ण;

#घोषणा SW_INIT_SET		0x00
#घोषणा SW_INIT_CLEAR		0x04
#घोषणा SW_INIT_STATUS		0x08

#घोषणा SW_INIT_BIT(id)		BIT((id) & 0x1f)
#घोषणा SW_INIT_BANK(id)	((id) >> 5)

/* A full bank contains extra रेजिस्टरs that we are not utilizing but still
 * qualअगरy as a single bank.
 */
#घोषणा SW_INIT_BANK_SIZE	0x18

अटल अंतरभूत
काष्ठा brcmstb_reset *to_brcmstb(काष्ठा reset_controller_dev *rcdev)
अणु
	वापस container_of(rcdev, काष्ठा brcmstb_reset, rcdev);
पूर्ण

अटल पूर्णांक brcmstb_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id)
अणु
	अचिन्हित पूर्णांक off = SW_INIT_BANK(id) * SW_INIT_BANK_SIZE;
	काष्ठा brcmstb_reset *priv = to_brcmstb(rcdev);

	ग_लिखोl_relaxed(SW_INIT_BIT(id), priv->base + off + SW_INIT_SET);

	वापस 0;
पूर्ण

अटल पूर्णांक brcmstb_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				  अचिन्हित दीर्घ id)
अणु
	अचिन्हित पूर्णांक off = SW_INIT_BANK(id) * SW_INIT_BANK_SIZE;
	काष्ठा brcmstb_reset *priv = to_brcmstb(rcdev);

	ग_लिखोl_relaxed(SW_INIT_BIT(id), priv->base + off + SW_INIT_CLEAR);
	/* Maximum reset delay after de-निश्चितing a line and seeing block
	 * operation is typically 14us क्रम the worst हाल, build some slack
	 * here.
	 */
	usleep_range(100, 200);

	वापस 0;
पूर्ण

अटल पूर्णांक brcmstb_reset_status(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id)
अणु
	अचिन्हित पूर्णांक off = SW_INIT_BANK(id) * SW_INIT_BANK_SIZE;
	काष्ठा brcmstb_reset *priv = to_brcmstb(rcdev);

	वापस पढ़ोl_relaxed(priv->base + off + SW_INIT_STATUS) &
			     SW_INIT_BIT(id);
पूर्ण

अटल स्थिर काष्ठा reset_control_ops brcmstb_reset_ops = अणु
	.निश्चित	= brcmstb_reset_निश्चित,
	.deनिश्चित = brcmstb_reset_deनिश्चित,
	.status = brcmstb_reset_status,
पूर्ण;

अटल पूर्णांक brcmstb_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *kdev = &pdev->dev;
	काष्ठा brcmstb_reset *priv;
	काष्ठा resource *res;

	priv = devm_kzalloc(kdev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(kdev, res);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	dev_set_drvdata(kdev, priv);

	priv->rcdev.owner = THIS_MODULE;
	priv->rcdev.nr_resets = DIV_ROUND_DOWN_ULL(resource_size(res),
						   SW_INIT_BANK_SIZE) * 32;
	priv->rcdev.ops = &brcmstb_reset_ops;
	priv->rcdev.of_node = kdev->of_node;
	/* Use शेषs: 1 cell and simple xlate function */

	वापस devm_reset_controller_रेजिस्टर(kdev, &priv->rcdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id brcmstb_reset_of_match[] = अणु
	अणु .compatible = "brcm,brcmstb-reset" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver brcmstb_reset_driver = अणु
	.probe	= brcmstb_reset_probe,
	.driver	= अणु
		.name = "brcmstb-reset",
		.of_match_table = brcmstb_reset_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(brcmstb_reset_driver);

MODULE_AUTHOR("Broadcom");
MODULE_DESCRIPTION("Broadcom STB reset controller");
MODULE_LICENSE("GPL");
