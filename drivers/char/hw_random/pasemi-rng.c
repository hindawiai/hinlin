<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2006-2007 PA Semi, Inc
 *
 * Maपूर्णांकained by: Olof Johansson <olof@lixom.net>
 *
 * Driver क्रम the PWRficient onchip rng
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पन.स>

#घोषणा SDCRNG_CTL_REG			0x00
#घोषणा   SDCRNG_CTL_FVLD_M		0x0000f000
#घोषणा   SDCRNG_CTL_FVLD_S		12
#घोषणा   SDCRNG_CTL_KSZ		0x00000800
#घोषणा   SDCRNG_CTL_RSRC_CRG		0x00000010
#घोषणा   SDCRNG_CTL_RSRC_RRG		0x00000000
#घोषणा   SDCRNG_CTL_CE			0x00000004
#घोषणा   SDCRNG_CTL_RE			0x00000002
#घोषणा   SDCRNG_CTL_DR			0x00000001
#घोषणा   SDCRNG_CTL_SELECT_RRG_RNG	(SDCRNG_CTL_RE | SDCRNG_CTL_RSRC_RRG)
#घोषणा   SDCRNG_CTL_SELECT_CRG_RNG	(SDCRNG_CTL_CE | SDCRNG_CTL_RSRC_CRG)
#घोषणा SDCRNG_VAL_REG			0x20

#घोषणा MODULE_NAME "pasemi_rng"

अटल पूर्णांक pasemi_rng_data_present(काष्ठा hwrng *rng, पूर्णांक रुको)
अणु
	व्योम __iomem *rng_regs = (व्योम __iomem *)rng->priv;
	पूर्णांक data, i;

	क्रम (i = 0; i < 20; i++) अणु
		data = (in_le32(rng_regs + SDCRNG_CTL_REG)
			& SDCRNG_CTL_FVLD_M) ? 1 : 0;
		अगर (data || !रुको)
			अवरोध;
		udelay(10);
	पूर्ण
	वापस data;
पूर्ण

अटल पूर्णांक pasemi_rng_data_पढ़ो(काष्ठा hwrng *rng, u32 *data)
अणु
	व्योम __iomem *rng_regs = (व्योम __iomem *)rng->priv;
	*data = in_le32(rng_regs + SDCRNG_VAL_REG);
	वापस 4;
पूर्ण

अटल पूर्णांक pasemi_rng_init(काष्ठा hwrng *rng)
अणु
	व्योम __iomem *rng_regs = (व्योम __iomem *)rng->priv;
	u32 ctl;

	ctl = SDCRNG_CTL_DR | SDCRNG_CTL_SELECT_RRG_RNG | SDCRNG_CTL_KSZ;
	out_le32(rng_regs + SDCRNG_CTL_REG, ctl);
	out_le32(rng_regs + SDCRNG_CTL_REG, ctl & ~SDCRNG_CTL_DR);

	वापस 0;
पूर्ण

अटल व्योम pasemi_rng_cleanup(काष्ठा hwrng *rng)
अणु
	व्योम __iomem *rng_regs = (व्योम __iomem *)rng->priv;
	u32 ctl;

	ctl = SDCRNG_CTL_RE | SDCRNG_CTL_CE;
	out_le32(rng_regs + SDCRNG_CTL_REG,
		 in_le32(rng_regs + SDCRNG_CTL_REG) & ~ctl);
पूर्ण

अटल काष्ठा hwrng pasemi_rng = अणु
	.name		= MODULE_NAME,
	.init		= pasemi_rng_init,
	.cleanup	= pasemi_rng_cleanup,
	.data_present	= pasemi_rng_data_present,
	.data_पढ़ो	= pasemi_rng_data_पढ़ो,
पूर्ण;

अटल पूर्णांक rng_probe(काष्ठा platक्रमm_device *pdev)
अणु
	व्योम __iomem *rng_regs;

	rng_regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(rng_regs))
		वापस PTR_ERR(rng_regs);

	pasemi_rng.priv = (अचिन्हित दीर्घ)rng_regs;

	pr_info("Registering PA Semi RNG\n");
	वापस devm_hwrng_रेजिस्टर(&pdev->dev, &pasemi_rng);
पूर्ण

अटल स्थिर काष्ठा of_device_id rng_match[] = अणु
	अणु .compatible      = "1682m-rng", पूर्ण,
	अणु .compatible      = "pasemi,pwrficient-rng", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rng_match);

अटल काष्ठा platक्रमm_driver rng_driver = अणु
	.driver = अणु
		.name = "pasemi-rng",
		.of_match_table = rng_match,
	पूर्ण,
	.probe		= rng_probe,
पूर्ण;

module_platक्रमm_driver(rng_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Egor Martovetsky <egor@pasemi.com>");
MODULE_DESCRIPTION("H/W RNG driver for PA Semi processor");
