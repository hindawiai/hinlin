<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * NXP LPC18xx/43xx OTP memory NVMEM driver
 *
 * Copyright (c) 2016 Joachim Eastwood <manabian@gmail.com>
 *
 * Based on the imx ocotp driver,
 * Copyright (c) 2015 Pengutronix, Philipp Zabel <p.zabel@pengutronix.de>
 *
 * TODO: add support क्रम writing OTP रेजिस्टर via API in boot ROM.
 */

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

/*
 * LPC18xx OTP memory contains 4 banks with 4 32-bit words. Bank 0 starts
 * at offset 0 from the base.
 *
 * Bank 0 contains the part ID क्रम Flashless devices and is reseverd क्रम
 * devices with Flash.
 * Bank 1/2 is generale purpose or AES key storage क्रम secure devices.
 * Bank 3 contains control data, USB ID and generale purpose words.
 */
#घोषणा LPC18XX_OTP_NUM_BANKS		4
#घोषणा LPC18XX_OTP_WORDS_PER_BANK	4
#घोषणा LPC18XX_OTP_WORD_SIZE		माप(u32)
#घोषणा LPC18XX_OTP_SIZE		(LPC18XX_OTP_NUM_BANKS * \
					 LPC18XX_OTP_WORDS_PER_BANK * \
					 LPC18XX_OTP_WORD_SIZE)

काष्ठा lpc18xx_otp अणु
	व्योम __iomem *base;
पूर्ण;

अटल पूर्णांक lpc18xx_otp_पढ़ो(व्योम *context, अचिन्हित पूर्णांक offset,
			    व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा lpc18xx_otp *otp = context;
	अचिन्हित पूर्णांक count = bytes >> 2;
	u32 index = offset >> 2;
	u32 *buf = val;
	पूर्णांक i;

	अगर (count > (LPC18XX_OTP_SIZE - index))
		count = LPC18XX_OTP_SIZE - index;

	क्रम (i = index; i < (index + count); i++)
		*buf++ = पढ़ोl(otp->base + i * LPC18XX_OTP_WORD_SIZE);

	वापस 0;
पूर्ण

अटल काष्ठा nvmem_config lpc18xx_otp_nvmem_config = अणु
	.name = "lpc18xx-otp",
	.पढ़ो_only = true,
	.word_size = LPC18XX_OTP_WORD_SIZE,
	.stride = LPC18XX_OTP_WORD_SIZE,
	.reg_पढ़ो = lpc18xx_otp_पढ़ो,
पूर्ण;

अटल पूर्णांक lpc18xx_otp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nvmem_device *nvmem;
	काष्ठा lpc18xx_otp *otp;
	काष्ठा resource *res;

	otp = devm_kzalloc(&pdev->dev, माप(*otp), GFP_KERNEL);
	अगर (!otp)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	otp->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(otp->base))
		वापस PTR_ERR(otp->base);

	lpc18xx_otp_nvmem_config.size = LPC18XX_OTP_SIZE;
	lpc18xx_otp_nvmem_config.dev = &pdev->dev;
	lpc18xx_otp_nvmem_config.priv = otp;

	nvmem = devm_nvmem_रेजिस्टर(&pdev->dev, &lpc18xx_otp_nvmem_config);

	वापस PTR_ERR_OR_ZERO(nvmem);
पूर्ण

अटल स्थिर काष्ठा of_device_id lpc18xx_otp_dt_ids[] = अणु
	अणु .compatible = "nxp,lpc1850-otp" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, lpc18xx_otp_dt_ids);

अटल काष्ठा platक्रमm_driver lpc18xx_otp_driver = अणु
	.probe	= lpc18xx_otp_probe,
	.driver = अणु
		.name	= "lpc18xx_otp",
		.of_match_table = lpc18xx_otp_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(lpc18xx_otp_driver);

MODULE_AUTHOR("Joachim Eastwoood <manabian@gmail.com>");
MODULE_DESCRIPTION("NXP LPC18xx OTP NVMEM driver");
MODULE_LICENSE("GPL v2");
