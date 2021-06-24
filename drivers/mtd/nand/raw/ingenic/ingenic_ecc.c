<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * JZ47xx ECC common code
 *
 * Copyright (c) 2015 Imagination Technologies
 * Author: Alex Smith <alex.smith@imgtec.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "ingenic_ecc.h"

/**
 * ingenic_ecc_calculate() - calculate ECC क्रम a data buffer
 * @ecc: ECC device.
 * @params: ECC parameters.
 * @buf: input buffer with raw data.
 * @ecc_code: output buffer with ECC.
 *
 * Return: 0 on success, -ETIMEDOUT अगर समयd out जबतक रुकोing क्रम ECC
 * controller.
 */
पूर्णांक ingenic_ecc_calculate(काष्ठा ingenic_ecc *ecc,
			  काष्ठा ingenic_ecc_params *params,
			  स्थिर u8 *buf, u8 *ecc_code)
अणु
	वापस ecc->ops->calculate(ecc, params, buf, ecc_code);
पूर्ण

/**
 * ingenic_ecc_correct() - detect and correct bit errors
 * @ecc: ECC device.
 * @params: ECC parameters.
 * @buf: raw data पढ़ो from the chip.
 * @ecc_code: ECC पढ़ो from the chip.
 *
 * Given the raw data and the ECC पढ़ो from the न_अंकD device, detects and
 * corrects errors in the data.
 *
 * Return: the number of bit errors corrected, -EBADMSG अगर there are too many
 * errors to correct or -ETIMEDOUT अगर we समयd out रुकोing क्रम the controller.
 */
पूर्णांक ingenic_ecc_correct(काष्ठा ingenic_ecc *ecc,
			काष्ठा ingenic_ecc_params *params,
			u8 *buf, u8 *ecc_code)
अणु
	वापस ecc->ops->correct(ecc, params, buf, ecc_code);
पूर्ण

/**
 * ingenic_ecc_get() - get the ECC controller device
 * @np: ECC device tree node.
 *
 * Gets the ECC controller device from the specअगरied device tree node. The
 * device must be released with ingenic_ecc_release() when it is no दीर्घer being
 * used.
 *
 * Return: a poपूर्णांकer to ingenic_ecc, errors are encoded पूर्णांकo the poपूर्णांकer.
 * PTR_ERR(-EPROBE_DEFER) अगर the device hasn't been initialised yet.
 */
अटल काष्ठा ingenic_ecc *ingenic_ecc_get(काष्ठा device_node *np)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा ingenic_ecc *ecc;

	pdev = of_find_device_by_node(np);
	अगर (!pdev || !platक्रमm_get_drvdata(pdev))
		वापस ERR_PTR(-EPROBE_DEFER);

	ecc = platक्रमm_get_drvdata(pdev);
	clk_prepare_enable(ecc->clk);

	वापस ecc;
पूर्ण

/**
 * of_ingenic_ecc_get() - get the ECC controller from a DT node
 * @of_node: the node that contains an ecc-engine property.
 *
 * Get the ecc-engine property from the given device tree
 * node and pass it to ingenic_ecc_get to करो the work.
 *
 * Return: a poपूर्णांकer to ingenic_ecc, errors are encoded पूर्णांकo the poपूर्णांकer.
 * PTR_ERR(-EPROBE_DEFER) अगर the device hasn't been initialised yet.
 */
काष्ठा ingenic_ecc *of_ingenic_ecc_get(काष्ठा device_node *of_node)
अणु
	काष्ठा ingenic_ecc *ecc = शून्य;
	काष्ठा device_node *np;

	np = of_parse_phandle(of_node, "ecc-engine", 0);

	/*
	 * If the ecc-engine property is not found, check क्रम the deprecated
	 * ingenic,bch-controller property
	 */
	अगर (!np)
		np = of_parse_phandle(of_node, "ingenic,bch-controller", 0);

	अगर (np) अणु
		ecc = ingenic_ecc_get(np);
		of_node_put(np);
	पूर्ण
	वापस ecc;
पूर्ण

/**
 * ingenic_ecc_release() - release the ECC controller device
 * @ecc: ECC device.
 */
व्योम ingenic_ecc_release(काष्ठा ingenic_ecc *ecc)
अणु
	clk_disable_unprepare(ecc->clk);
	put_device(ecc->dev);
पूर्ण

पूर्णांक ingenic_ecc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ingenic_ecc *ecc;

	ecc = devm_kzalloc(dev, माप(*ecc), GFP_KERNEL);
	अगर (!ecc)
		वापस -ENOMEM;

	ecc->ops = device_get_match_data(dev);
	अगर (!ecc->ops)
		वापस -EINVAL;

	ecc->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ecc->base))
		वापस PTR_ERR(ecc->base);

	ecc->ops->disable(ecc);

	ecc->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(ecc->clk)) अणु
		dev_err(dev, "failed to get clock: %ld\n", PTR_ERR(ecc->clk));
		वापस PTR_ERR(ecc->clk);
	पूर्ण

	mutex_init(&ecc->lock);

	ecc->dev = dev;
	platक्रमm_set_drvdata(pdev, ecc);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ingenic_ecc_probe);
