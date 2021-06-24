<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Nomadik RNG support
 *  Copyright 2009 Alessandro Rubini
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>

अटल काष्ठा clk *rng_clk;

अटल पूर्णांक nmk_rng_पढ़ो(काष्ठा hwrng *rng, व्योम *data, माप_प्रकार max, bool रुको)
अणु
	व्योम __iomem *base = (व्योम __iomem *)rng->priv;

	/*
	 * The रेजिस्टर is 32 bits and gives 16 अक्रमom bits (low half).
	 * A subsequent पढ़ो will delay the core क्रम 400ns, so we just पढ़ो
	 * once and accept the very unlikely very small delay, even अगर रुको==0.
	 */
	*(u16 *)data = __raw_पढ़ोl(base + 8) & 0xffff;
	वापस 2;
पूर्ण

/* we have at most one RNG per machine, granted */
अटल काष्ठा hwrng nmk_rng = अणु
	.name		= "nomadik",
	.पढ़ो		= nmk_rng_पढ़ो,
पूर्ण;

अटल पूर्णांक nmk_rng_probe(काष्ठा amba_device *dev, स्थिर काष्ठा amba_id *id)
अणु
	व्योम __iomem *base;
	पूर्णांक ret;

	rng_clk = devm_clk_get(&dev->dev, शून्य);
	अगर (IS_ERR(rng_clk)) अणु
		dev_err(&dev->dev, "could not get rng clock\n");
		ret = PTR_ERR(rng_clk);
		वापस ret;
	पूर्ण

	clk_prepare_enable(rng_clk);

	ret = amba_request_regions(dev, dev->dev.init_name);
	अगर (ret)
		जाओ out_clk;
	ret = -ENOMEM;
	base = devm_ioremap(&dev->dev, dev->res.start,
			    resource_size(&dev->res));
	अगर (!base)
		जाओ out_release;
	nmk_rng.priv = (अचिन्हित दीर्घ)base;
	ret = devm_hwrng_रेजिस्टर(&dev->dev, &nmk_rng);
	अगर (ret)
		जाओ out_release;
	वापस 0;

out_release:
	amba_release_regions(dev);
out_clk:
	clk_disable(rng_clk);
	वापस ret;
पूर्ण

अटल व्योम nmk_rng_हटाओ(काष्ठा amba_device *dev)
अणु
	amba_release_regions(dev);
	clk_disable(rng_clk);
पूर्ण

अटल स्थिर काष्ठा amba_id nmk_rng_ids[] = अणु
	अणु
		.id	= 0x000805e1,
		.mask	= 0x000fffff, /* top bits are rev and cfg: accept all */
	पूर्ण,
	अणु0, 0पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(amba, nmk_rng_ids);

अटल काष्ठा amba_driver nmk_rng_driver = अणु
	.drv = अणु
		.owner = THIS_MODULE,
		.name = "rng",
		पूर्ण,
	.probe = nmk_rng_probe,
	.हटाओ = nmk_rng_हटाओ,
	.id_table = nmk_rng_ids,
पूर्ण;

module_amba_driver(nmk_rng_driver);

MODULE_LICENSE("GPL");
