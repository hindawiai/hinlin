<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/अक्षर/hw_अक्रमom/समयriomem-rng.c
 *
 * Copyright (C) 2009 Alexander Clouter <alex@digriz.org.uk>
 *
 * Derived from drivers/अक्षर/hw_अक्रमom/omap-rng.c
 *   Copyright 2005 (c) MontaVista Software, Inc.
 *   Author: Deepak Saxena <dsaxena@plनिकासy.net>
 *
 * Overview:
 *   This driver is useful क्रम platक्रमms that have an IO range that provides
 *   periodic अक्रमom data from a single IO memory address.  All the platक्रमm
 *   has to करो is provide the address and 'wait time' that new data becomes
 *   available.
 *
 * TODO: add support क्रम पढ़ोing sizes other than 32bits and masking
 */

#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/पन.स>
#समावेश <linux/kसमय.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/समयriomem-rng.h>

काष्ठा समयriomem_rng_निजी अणु
	व्योम __iomem		*io_base;
	kसमय_प्रकार			period;
	अचिन्हित पूर्णांक		present:1;

	काष्ठा hrसमयr		समयr;
	काष्ठा completion	completion;

	काष्ठा hwrng		rng_ops;
पूर्ण;

अटल पूर्णांक समयriomem_rng_पढ़ो(काष्ठा hwrng *hwrng, व्योम *data,
				माप_प्रकार max, bool रुको)
अणु
	काष्ठा समयriomem_rng_निजी *priv =
		container_of(hwrng, काष्ठा समयriomem_rng_निजी, rng_ops);
	पूर्णांक retval = 0;
	पूर्णांक period_us = kसमय_प्रकारo_us(priv->period);

	/*
	 * There may not have been enough समय क्रम new data to be generated
	 * since the last request.  If the caller करोesn't want to रुको, let them
	 * bail out.  Otherwise, रुको क्रम the completion.  If the new data has
	 * alपढ़ोy been generated, the completion should alपढ़ोy be available.
	 */
	अगर (!रुको && !priv->present)
		वापस 0;

	रुको_क्रम_completion(&priv->completion);

	करो अणु
		/*
		 * After the first पढ़ो, all additional पढ़ोs will need to रुको
		 * क्रम the RNG to generate new data.  Since the period can have
		 * a wide range of values (1us to 1s have been observed), allow
		 * क्रम 1% tolerance in the sleep समय rather than a fixed value.
		 */
		अगर (retval > 0)
			usleep_range(period_us,
					period_us + max(1, period_us / 100));

		*(u32 *)data = पढ़ोl(priv->io_base);
		retval += माप(u32);
		data += माप(u32);
		max -= माप(u32);
	पूर्ण जबतक (रुको && max > माप(u32));

	/*
	 * Block any new callers until the RNG has had समय to generate new
	 * data.
	 */
	priv->present = 0;
	reinit_completion(&priv->completion);
	hrसमयr_क्रमward_now(&priv->समयr, priv->period);
	hrसमयr_restart(&priv->समयr);

	वापस retval;
पूर्ण

अटल क्रमागत hrसमयr_restart समयriomem_rng_trigger(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा समयriomem_rng_निजी *priv
		= container_of(समयr, काष्ठा समयriomem_rng_निजी, समयr);

	priv->present = 1;
	complete(&priv->completion);

	वापस HRTIMER_NORESTART;
पूर्ण

अटल पूर्णांक समयriomem_rng_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा समयriomem_rng_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा समयriomem_rng_निजी *priv;
	काष्ठा resource *res;
	पूर्णांक err = 0;
	पूर्णांक period;

	अगर (!pdev->dev.of_node && !pdata) अणु
		dev_err(&pdev->dev, "timeriomem_rng_data is missing\n");
		वापस -EINVAL;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENXIO;

	अगर (res->start % 4 != 0 || resource_size(res) < 4) अणु
		dev_err(&pdev->dev,
			"address must be at least four bytes wide and 32-bit aligned\n");
		वापस -EINVAL;
	पूर्ण

	/* Allocate memory क्रम the device काष्ठाure (and zero it) */
	priv = devm_kzalloc(&pdev->dev,
			माप(काष्ठा समयriomem_rng_निजी), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, priv);

	अगर (pdev->dev.of_node) अणु
		पूर्णांक i;

		अगर (!of_property_पढ़ो_u32(pdev->dev.of_node,
						"period", &i))
			period = i;
		अन्यथा अणु
			dev_err(&pdev->dev, "missing period\n");
			वापस -EINVAL;
		पूर्ण

		अगर (!of_property_पढ़ो_u32(pdev->dev.of_node,
						"quality", &i))
			priv->rng_ops.quality = i;
		अन्यथा
			priv->rng_ops.quality = 0;
	पूर्ण अन्यथा अणु
		period = pdata->period;
		priv->rng_ops.quality = pdata->quality;
	पूर्ण

	priv->period = ns_to_kसमय(period * NSEC_PER_USEC);
	init_completion(&priv->completion);
	hrसमयr_init(&priv->समयr, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
	priv->समयr.function = समयriomem_rng_trigger;

	priv->rng_ops.name = dev_name(&pdev->dev);
	priv->rng_ops.पढ़ो = समयriomem_rng_पढ़ो;

	priv->io_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(priv->io_base)) अणु
		वापस PTR_ERR(priv->io_base);
	पूर्ण

	/* Assume अक्रमom data is alपढ़ोy available. */
	priv->present = 1;
	complete(&priv->completion);

	err = devm_hwrng_रेजिस्टर(&pdev->dev, &priv->rng_ops);
	अगर (err) अणु
		dev_err(&pdev->dev, "problem registering\n");
		वापस err;
	पूर्ण

	dev_info(&pdev->dev, "32bits from 0x%p @ %dus\n",
			priv->io_base, period);

	वापस 0;
पूर्ण

अटल पूर्णांक समयriomem_rng_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा समयriomem_rng_निजी *priv = platक्रमm_get_drvdata(pdev);

	hrसमयr_cancel(&priv->समयr);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id समयriomem_rng_match[] = अणु
	अणु .compatible = "timeriomem_rng" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, समयriomem_rng_match);

अटल काष्ठा platक्रमm_driver समयriomem_rng_driver = अणु
	.driver = अणु
		.name		= "timeriomem_rng",
		.of_match_table	= समयriomem_rng_match,
	पूर्ण,
	.probe		= समयriomem_rng_probe,
	.हटाओ		= समयriomem_rng_हटाओ,
पूर्ण;

module_platक्रमm_driver(समयriomem_rng_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexander Clouter <alex@digriz.org.uk>");
MODULE_DESCRIPTION("Timer IOMEM H/W RNG driver");
