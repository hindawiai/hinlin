<शैली गुरु>
/*
 * B53 रेजिस्टर access through memory mapped रेजिस्टरs
 *
 * Copyright (C) 2012-2013 Jonas Gorski <jogo@खोलोwrt.org>
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <linux/bits.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/b53.h>

#समावेश "b53_priv.h"

काष्ठा b53_mmap_priv अणु
	व्योम __iomem *regs;
पूर्ण;

अटल पूर्णांक b53_mmap_पढ़ो8(काष्ठा b53_device *dev, u8 page, u8 reg, u8 *val)
अणु
	काष्ठा b53_mmap_priv *priv = dev->priv;
	व्योम __iomem *regs = priv->regs;

	*val = पढ़ोb(regs + (page << 8) + reg);

	वापस 0;
पूर्ण

अटल पूर्णांक b53_mmap_पढ़ो16(काष्ठा b53_device *dev, u8 page, u8 reg, u16 *val)
अणु
	काष्ठा b53_mmap_priv *priv = dev->priv;
	व्योम __iomem *regs = priv->regs;

	अगर (WARN_ON(reg % 2))
		वापस -EINVAL;

	अगर (dev->pdata && dev->pdata->big_endian)
		*val = ioपढ़ो16be(regs + (page << 8) + reg);
	अन्यथा
		*val = पढ़ोw(regs + (page << 8) + reg);

	वापस 0;
पूर्ण

अटल पूर्णांक b53_mmap_पढ़ो32(काष्ठा b53_device *dev, u8 page, u8 reg, u32 *val)
अणु
	काष्ठा b53_mmap_priv *priv = dev->priv;
	व्योम __iomem *regs = priv->regs;

	अगर (WARN_ON(reg % 4))
		वापस -EINVAL;

	अगर (dev->pdata && dev->pdata->big_endian)
		*val = ioपढ़ो32be(regs + (page << 8) + reg);
	अन्यथा
		*val = पढ़ोl(regs + (page << 8) + reg);

	वापस 0;
पूर्ण

अटल पूर्णांक b53_mmap_पढ़ो48(काष्ठा b53_device *dev, u8 page, u8 reg, u64 *val)
अणु
	काष्ठा b53_mmap_priv *priv = dev->priv;
	व्योम __iomem *regs = priv->regs;

	अगर (WARN_ON(reg % 2))
		वापस -EINVAL;

	अगर (reg % 4) अणु
		u16 lo;
		u32 hi;

		अगर (dev->pdata && dev->pdata->big_endian) अणु
			lo = ioपढ़ो16be(regs + (page << 8) + reg);
			hi = ioपढ़ो32be(regs + (page << 8) + reg + 2);
		पूर्ण अन्यथा अणु
			lo = पढ़ोw(regs + (page << 8) + reg);
			hi = पढ़ोl(regs + (page << 8) + reg + 2);
		पूर्ण

		*val = ((u64)hi << 16) | lo;
	पूर्ण अन्यथा अणु
		u32 lo;
		u16 hi;

		अगर (dev->pdata && dev->pdata->big_endian) अणु
			lo = ioपढ़ो32be(regs + (page << 8) + reg);
			hi = ioपढ़ो16be(regs + (page << 8) + reg + 4);
		पूर्ण अन्यथा अणु
			lo = पढ़ोl(regs + (page << 8) + reg);
			hi = पढ़ोw(regs + (page << 8) + reg + 4);
		पूर्ण

		*val = ((u64)hi << 32) | lo;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक b53_mmap_पढ़ो64(काष्ठा b53_device *dev, u8 page, u8 reg, u64 *val)
अणु
	काष्ठा b53_mmap_priv *priv = dev->priv;
	व्योम __iomem *regs = priv->regs;
	u32 hi, lo;

	अगर (WARN_ON(reg % 4))
		वापस -EINVAL;

	अगर (dev->pdata && dev->pdata->big_endian) अणु
		lo = ioपढ़ो32be(regs + (page << 8) + reg);
		hi = ioपढ़ो32be(regs + (page << 8) + reg + 4);
	पूर्ण अन्यथा अणु
		lo = पढ़ोl(regs + (page << 8) + reg);
		hi = पढ़ोl(regs + (page << 8) + reg + 4);
	पूर्ण

	*val = ((u64)hi << 32) | lo;

	वापस 0;
पूर्ण

अटल पूर्णांक b53_mmap_ग_लिखो8(काष्ठा b53_device *dev, u8 page, u8 reg, u8 value)
अणु
	काष्ठा b53_mmap_priv *priv = dev->priv;
	व्योम __iomem *regs = priv->regs;

	ग_लिखोb(value, regs + (page << 8) + reg);

	वापस 0;
पूर्ण

अटल पूर्णांक b53_mmap_ग_लिखो16(काष्ठा b53_device *dev, u8 page, u8 reg,
			    u16 value)
अणु
	काष्ठा b53_mmap_priv *priv = dev->priv;
	व्योम __iomem *regs = priv->regs;

	अगर (WARN_ON(reg % 2))
		वापस -EINVAL;

	अगर (dev->pdata && dev->pdata->big_endian)
		ioग_लिखो16be(value, regs + (page << 8) + reg);
	अन्यथा
		ग_लिखोw(value, regs + (page << 8) + reg);

	वापस 0;
पूर्ण

अटल पूर्णांक b53_mmap_ग_लिखो32(काष्ठा b53_device *dev, u8 page, u8 reg,
			    u32 value)
अणु
	काष्ठा b53_mmap_priv *priv = dev->priv;
	व्योम __iomem *regs = priv->regs;

	अगर (WARN_ON(reg % 4))
		वापस -EINVAL;

	अगर (dev->pdata && dev->pdata->big_endian)
		ioग_लिखो32be(value, regs + (page << 8) + reg);
	अन्यथा
		ग_लिखोl(value, regs + (page << 8) + reg);

	वापस 0;
पूर्ण

अटल पूर्णांक b53_mmap_ग_लिखो48(काष्ठा b53_device *dev, u8 page, u8 reg,
			    u64 value)
अणु
	अगर (WARN_ON(reg % 2))
		वापस -EINVAL;

	अगर (reg % 4) अणु
		u32 hi = (u32)(value >> 16);
		u16 lo = (u16)value;

		b53_mmap_ग_लिखो16(dev, page, reg, lo);
		b53_mmap_ग_लिखो32(dev, page, reg + 2, hi);
	पूर्ण अन्यथा अणु
		u16 hi = (u16)(value >> 32);
		u32 lo = (u32)value;

		b53_mmap_ग_लिखो32(dev, page, reg, lo);
		b53_mmap_ग_लिखो16(dev, page, reg + 4, hi);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक b53_mmap_ग_लिखो64(काष्ठा b53_device *dev, u8 page, u8 reg,
			    u64 value)
अणु
	u32 hi, lo;

	hi = upper_32_bits(value);
	lo = lower_32_bits(value);

	अगर (WARN_ON(reg % 4))
		वापस -EINVAL;

	b53_mmap_ग_लिखो32(dev, page, reg, lo);
	b53_mmap_ग_लिखो32(dev, page, reg + 4, hi);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा b53_io_ops b53_mmap_ops = अणु
	.पढ़ो8 = b53_mmap_पढ़ो8,
	.पढ़ो16 = b53_mmap_पढ़ो16,
	.पढ़ो32 = b53_mmap_पढ़ो32,
	.पढ़ो48 = b53_mmap_पढ़ो48,
	.पढ़ो64 = b53_mmap_पढ़ो64,
	.ग_लिखो8 = b53_mmap_ग_लिखो8,
	.ग_लिखो16 = b53_mmap_ग_लिखो16,
	.ग_लिखो32 = b53_mmap_ग_लिखो32,
	.ग_लिखो48 = b53_mmap_ग_लिखो48,
	.ग_लिखो64 = b53_mmap_ग_लिखो64,
पूर्ण;

अटल पूर्णांक b53_mmap_probe_of(काष्ठा platक्रमm_device *pdev,
			     काष्ठा b53_platक्रमm_data **ppdata)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *of_ports, *of_port;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा b53_platक्रमm_data *pdata;
	व्योम __iomem *mem;

	mem = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mem))
		वापस PTR_ERR(mem);

	pdata = devm_kzalloc(dev, माप(काष्ठा b53_platक्रमm_data),
			     GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	pdata->regs = mem;
	pdata->chip_id = BCM63XX_DEVICE_ID;
	pdata->big_endian = of_property_पढ़ो_bool(np, "big-endian");

	of_ports = of_get_child_by_name(np, "ports");
	अगर (!of_ports) अणु
		dev_err(dev, "no ports child node found\n");
		वापस -EINVAL;
	पूर्ण

	क्रम_each_available_child_of_node(of_ports, of_port) अणु
		u32 reg;

		अगर (of_property_पढ़ो_u32(of_port, "reg", &reg))
			जारी;

		अगर (reg < B53_CPU_PORT)
			pdata->enabled_ports |= BIT(reg);
	पूर्ण

	of_node_put(of_ports);
	*ppdata = pdata;

	वापस 0;
पूर्ण

अटल पूर्णांक b53_mmap_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा b53_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा b53_mmap_priv *priv;
	काष्ठा b53_device *dev;
	पूर्णांक ret;

	अगर (!pdata && np) अणु
		ret = b53_mmap_probe_of(pdev, &pdata);
		अगर (ret) अणु
			dev_err(&pdev->dev, "OF probe error\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (!pdata)
		वापस -EINVAL;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->regs = pdata->regs;

	dev = b53_चयन_alloc(&pdev->dev, &b53_mmap_ops, priv);
	अगर (!dev)
		वापस -ENOMEM;

	dev->pdata = pdata;

	platक्रमm_set_drvdata(pdev, dev);

	वापस b53_चयन_रेजिस्टर(dev);
पूर्ण

अटल पूर्णांक b53_mmap_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा b53_device *dev = platक्रमm_get_drvdata(pdev);

	अगर (dev)
		b53_चयन_हटाओ(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id b53_mmap_of_table[] = अणु
	अणु .compatible = "brcm,bcm3384-switch" पूर्ण,
	अणु .compatible = "brcm,bcm6328-switch" पूर्ण,
	अणु .compatible = "brcm,bcm6368-switch" पूर्ण,
	अणु .compatible = "brcm,bcm63xx-switch" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, b53_mmap_of_table);

अटल काष्ठा platक्रमm_driver b53_mmap_driver = अणु
	.probe = b53_mmap_probe,
	.हटाओ = b53_mmap_हटाओ,
	.driver = अणु
		.name = "b53-switch",
		.of_match_table = b53_mmap_of_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(b53_mmap_driver);
MODULE_AUTHOR("Jonas Gorski <jogo@openwrt.org>");
MODULE_DESCRIPTION("B53 MMAP access driver");
MODULE_LICENSE("Dual BSD/GPL");
