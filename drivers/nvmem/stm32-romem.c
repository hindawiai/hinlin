<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * STM32 Factory-programmed memory पढ़ो access driver
 *
 * Copyright (C) 2017, STMicroelectronics - All Rights Reserved
 * Author: Fabrice Gasnier <fabrice.gasnier@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/arm-smccc.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/of_device.h>

/* BSEC secure service access from non-secure */
#घोषणा STM32_SMC_BSEC			0x82001003
#घोषणा STM32_SMC_READ_SHADOW		0x01
#घोषणा STM32_SMC_PROG_OTP		0x02
#घोषणा STM32_SMC_WRITE_SHADOW		0x03
#घोषणा STM32_SMC_READ_OTP		0x04

/* shaकरोw रेजिस्टरs offest */
#घोषणा STM32MP15_BSEC_DATA0		0x200

/* 32 (x 32-bits) lower shaकरोw रेजिस्टरs */
#घोषणा STM32MP15_BSEC_NUM_LOWER	32

काष्ठा sपंचांग32_romem_cfg अणु
	पूर्णांक size;
पूर्ण;

काष्ठा sपंचांग32_romem_priv अणु
	व्योम __iomem *base;
	काष्ठा nvmem_config cfg;
पूर्ण;

अटल पूर्णांक sपंचांग32_romem_पढ़ो(व्योम *context, अचिन्हित पूर्णांक offset, व्योम *buf,
			    माप_प्रकार bytes)
अणु
	काष्ठा sपंचांग32_romem_priv *priv = context;
	u8 *buf8 = buf;
	पूर्णांक i;

	क्रम (i = offset; i < offset + bytes; i++)
		*buf8++ = पढ़ोb_relaxed(priv->base + i);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_bsec_smc(u8 op, u32 otp, u32 data, u32 *result)
अणु
#अगर IS_ENABLED(CONFIG_HAVE_ARM_SMCCC)
	काष्ठा arm_smccc_res res;

	arm_smccc_smc(STM32_SMC_BSEC, op, otp, data, 0, 0, 0, 0, &res);
	अगर (res.a0)
		वापस -EIO;

	अगर (result)
		*result = (u32)res.a1;

	वापस 0;
#अन्यथा
	वापस -ENXIO;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक sपंचांग32_bsec_पढ़ो(व्योम *context, अचिन्हित पूर्णांक offset, व्योम *buf,
			   माप_प्रकार bytes)
अणु
	काष्ठा sपंचांग32_romem_priv *priv = context;
	काष्ठा device *dev = priv->cfg.dev;
	u32 roffset, rbytes, val;
	u8 *buf8 = buf, *val8 = (u8 *)&val;
	पूर्णांक i, j = 0, ret, skip_bytes, size;

	/* Round unaligned access to 32-bits */
	roffset = roundकरोwn(offset, 4);
	skip_bytes = offset & 0x3;
	rbytes = roundup(bytes + skip_bytes, 4);

	अगर (roffset + rbytes > priv->cfg.size)
		वापस -EINVAL;

	क्रम (i = roffset; (i < roffset + rbytes); i += 4) अणु
		u32 otp = i >> 2;

		अगर (otp < STM32MP15_BSEC_NUM_LOWER) अणु
			/* पढ़ो lower data from shaकरोw रेजिस्टरs */
			val = पढ़ोl_relaxed(
				priv->base + STM32MP15_BSEC_DATA0 + i);
		पूर्ण अन्यथा अणु
			ret = sपंचांग32_bsec_smc(STM32_SMC_READ_SHADOW, otp, 0,
					     &val);
			अगर (ret) अणु
				dev_err(dev, "Can't read data%d (%d)\n", otp,
					ret);
				वापस ret;
			पूर्ण
		पूर्ण
		/* skip first bytes in हाल of unaligned पढ़ो */
		अगर (skip_bytes)
			size = min(bytes, (माप_प्रकार)(4 - skip_bytes));
		अन्यथा
			size = min(bytes, (माप_प्रकार)4);
		स_नकल(&buf8[j], &val8[skip_bytes], size);
		bytes -= size;
		j += size;
		skip_bytes = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_bsec_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक offset, व्योम *buf,
			    माप_प्रकार bytes)
अणु
	काष्ठा sपंचांग32_romem_priv *priv = context;
	काष्ठा device *dev = priv->cfg.dev;
	u32 *buf32 = buf;
	पूर्णांक ret, i;

	/* Allow only writing complete 32-bits aligned words */
	अगर ((bytes % 4) || (offset % 4))
		वापस -EINVAL;

	क्रम (i = offset; i < offset + bytes; i += 4) अणु
		ret = sपंचांग32_bsec_smc(STM32_SMC_PROG_OTP, i >> 2, *buf32++,
				     शून्य);
		अगर (ret) अणु
			dev_err(dev, "Can't write data%d (%d)\n", i >> 2, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_romem_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा sपंचांग32_romem_cfg *cfg;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sपंचांग32_romem_priv *priv;
	काष्ठा resource *res;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	priv->cfg.name = "stm32-romem";
	priv->cfg.word_size = 1;
	priv->cfg.stride = 1;
	priv->cfg.dev = dev;
	priv->cfg.priv = priv;
	priv->cfg.owner = THIS_MODULE;

	cfg = (स्थिर काष्ठा sपंचांग32_romem_cfg *)
		of_match_device(dev->driver->of_match_table, dev)->data;
	अगर (!cfg) अणु
		priv->cfg.पढ़ो_only = true;
		priv->cfg.size = resource_size(res);
		priv->cfg.reg_पढ़ो = sपंचांग32_romem_पढ़ो;
	पूर्ण अन्यथा अणु
		priv->cfg.size = cfg->size;
		priv->cfg.reg_पढ़ो = sपंचांग32_bsec_पढ़ो;
		priv->cfg.reg_ग_लिखो = sपंचांग32_bsec_ग_लिखो;
	पूर्ण

	वापस PTR_ERR_OR_ZERO(devm_nvmem_रेजिस्टर(dev, &priv->cfg));
पूर्ण

अटल स्थिर काष्ठा sपंचांग32_romem_cfg sपंचांग32mp15_bsec_cfg = अणु
	.size = 384, /* 96 x 32-bits data words */
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32_romem_of_match[] = अणु
	अणु .compatible = "st,stm32f4-otp", पूर्ण, अणु
		.compatible = "st,stm32mp15-bsec",
		.data = (व्योम *)&sपंचांग32mp15_bsec_cfg,
	पूर्ण, अणु
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_romem_of_match);

अटल काष्ठा platक्रमm_driver sपंचांग32_romem_driver = अणु
	.probe = sपंचांग32_romem_probe,
	.driver = अणु
		.name = "stm32-romem",
		.of_match_table = of_match_ptr(sपंचांग32_romem_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sपंचांग32_romem_driver);

MODULE_AUTHOR("Fabrice Gasnier <fabrice.gasnier@st.com>");
MODULE_DESCRIPTION("STMicroelectronics STM32 RO-MEM");
MODULE_ALIAS("platform:nvmem-stm32-romem");
MODULE_LICENSE("GPL v2");
