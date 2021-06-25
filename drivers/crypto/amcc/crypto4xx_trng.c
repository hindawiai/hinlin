<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic PowerPC 44x RNG driver
 *
 * Copyright 2011 IBM Corporation
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पन.स>

#समावेश "crypto4xx_core.h"
#समावेश "crypto4xx_trng.h"
#समावेश "crypto4xx_reg_def.h"

#घोषणा PPC4XX_TRNG_CTRL	0x0008
#घोषणा PPC4XX_TRNG_CTRL_DALM	0x20
#घोषणा PPC4XX_TRNG_STAT	0x0004
#घोषणा PPC4XX_TRNG_STAT_B	0x1
#घोषणा PPC4XX_TRNG_DATA	0x0000

अटल पूर्णांक ppc4xx_trng_data_present(काष्ठा hwrng *rng, पूर्णांक रुको)
अणु
	काष्ठा crypto4xx_device *dev = (व्योम *)rng->priv;
	पूर्णांक busy, i, present = 0;

	क्रम (i = 0; i < 20; i++) अणु
		busy = (in_le32(dev->trng_base + PPC4XX_TRNG_STAT) &
			PPC4XX_TRNG_STAT_B);
		अगर (!busy || !रुको) अणु
			present = 1;
			अवरोध;
		पूर्ण
		udelay(10);
	पूर्ण
	वापस present;
पूर्ण

अटल पूर्णांक ppc4xx_trng_data_पढ़ो(काष्ठा hwrng *rng, u32 *data)
अणु
	काष्ठा crypto4xx_device *dev = (व्योम *)rng->priv;
	*data = in_le32(dev->trng_base + PPC4XX_TRNG_DATA);
	वापस 4;
पूर्ण

अटल व्योम ppc4xx_trng_enable(काष्ठा crypto4xx_device *dev, bool enable)
अणु
	u32 device_ctrl;

	device_ctrl = पढ़ोl(dev->ce_base + CRYPTO4XX_DEVICE_CTRL);
	अगर (enable)
		device_ctrl |= PPC4XX_TRNG_EN;
	अन्यथा
		device_ctrl &= ~PPC4XX_TRNG_EN;
	ग_लिखोl(device_ctrl, dev->ce_base + CRYPTO4XX_DEVICE_CTRL);
पूर्ण

अटल स्थिर काष्ठा of_device_id ppc4xx_trng_match[] = अणु
	अणु .compatible = "ppc4xx-rng", पूर्ण,
	अणु .compatible = "amcc,ppc460ex-rng", पूर्ण,
	अणु .compatible = "amcc,ppc440epx-rng", पूर्ण,
	अणुपूर्ण,
पूर्ण;

व्योम ppc4xx_trng_probe(काष्ठा crypto4xx_core_device *core_dev)
अणु
	काष्ठा crypto4xx_device *dev = core_dev->dev;
	काष्ठा device_node *trng = शून्य;
	काष्ठा hwrng *rng = शून्य;
	पूर्णांक err;

	/* Find the TRNG device node and map it */
	trng = of_find_matching_node(शून्य, ppc4xx_trng_match);
	अगर (!trng || !of_device_is_available(trng)) अणु
		of_node_put(trng);
		वापस;
	पूर्ण

	dev->trng_base = of_iomap(trng, 0);
	of_node_put(trng);
	अगर (!dev->trng_base)
		जाओ err_out;

	rng = kzalloc(माप(*rng), GFP_KERNEL);
	अगर (!rng)
		जाओ err_out;

	rng->name = KBUILD_MODNAME;
	rng->data_present = ppc4xx_trng_data_present;
	rng->data_पढ़ो = ppc4xx_trng_data_पढ़ो;
	rng->priv = (अचिन्हित दीर्घ) dev;
	core_dev->trng = rng;
	ppc4xx_trng_enable(dev, true);
	out_le32(dev->trng_base + PPC4XX_TRNG_CTRL, PPC4XX_TRNG_CTRL_DALM);
	err = devm_hwrng_रेजिस्टर(core_dev->device, core_dev->trng);
	अगर (err) अणु
		ppc4xx_trng_enable(dev, false);
		dev_err(core_dev->device, "failed to register hwrng (%d).\n",
			err);
		जाओ err_out;
	पूर्ण
	वापस;

err_out:
	iounmap(dev->trng_base);
	kमुक्त(rng);
	dev->trng_base = शून्य;
	core_dev->trng = शून्य;
पूर्ण

व्योम ppc4xx_trng_हटाओ(काष्ठा crypto4xx_core_device *core_dev)
अणु
	अगर (core_dev && core_dev->trng) अणु
		काष्ठा crypto4xx_device *dev = core_dev->dev;

		devm_hwrng_unरेजिस्टर(core_dev->device, core_dev->trng);
		ppc4xx_trng_enable(dev, false);
		iounmap(dev->trng_base);
		kमुक्त(core_dev->trng);
	पूर्ण
पूर्ण

MODULE_ALIAS("ppc4xx_rng");
