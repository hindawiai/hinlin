<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Rockchip eFuse Driver
 *
 * Copyright (c) 2015 Rockchip Electronics Co. Ltd.
 * Author: Caesar Wang <wxt@rock-chips.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा RK3288_A_SHIFT		6
#घोषणा RK3288_A_MASK		0x3ff
#घोषणा RK3288_PGENB		BIT(3)
#घोषणा RK3288_LOAD		BIT(2)
#घोषणा RK3288_STROBE		BIT(1)
#घोषणा RK3288_CSB		BIT(0)

#घोषणा RK3328_SECURE_SIZES	96
#घोषणा RK3328_INT_STATUS	0x0018
#घोषणा RK3328_DOUT		0x0020
#घोषणा RK3328_AUTO_CTRL	0x0024
#घोषणा RK3328_INT_FINISH	BIT(0)
#घोषणा RK3328_AUTO_ENB		BIT(0)
#घोषणा RK3328_AUTO_RD		BIT(1)

#घोषणा RK3399_A_SHIFT		16
#घोषणा RK3399_A_MASK		0x3ff
#घोषणा RK3399_NBYTES		4
#घोषणा RK3399_STROBSFTSEL	BIT(9)
#घोषणा RK3399_RSB		BIT(7)
#घोषणा RK3399_PD		BIT(5)
#घोषणा RK3399_PGENB		BIT(3)
#घोषणा RK3399_LOAD		BIT(2)
#घोषणा RK3399_STROBE		BIT(1)
#घोषणा RK3399_CSB		BIT(0)

#घोषणा REG_EFUSE_CTRL		0x0000
#घोषणा REG_EFUSE_DOUT		0x0004

काष्ठा rockchip_efuse_chip अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा clk *clk;
पूर्ण;

अटल पूर्णांक rockchip_rk3288_efuse_पढ़ो(व्योम *context, अचिन्हित पूर्णांक offset,
				      व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा rockchip_efuse_chip *efuse = context;
	u8 *buf = val;
	पूर्णांक ret;

	ret = clk_prepare_enable(efuse->clk);
	अगर (ret < 0) अणु
		dev_err(efuse->dev, "failed to prepare/enable efuse clk\n");
		वापस ret;
	पूर्ण

	ग_लिखोl(RK3288_LOAD | RK3288_PGENB, efuse->base + REG_EFUSE_CTRL);
	udelay(1);
	जबतक (bytes--) अणु
		ग_लिखोl(पढ़ोl(efuse->base + REG_EFUSE_CTRL) &
			     (~(RK3288_A_MASK << RK3288_A_SHIFT)),
			     efuse->base + REG_EFUSE_CTRL);
		ग_लिखोl(पढ़ोl(efuse->base + REG_EFUSE_CTRL) |
			     ((offset++ & RK3288_A_MASK) << RK3288_A_SHIFT),
			     efuse->base + REG_EFUSE_CTRL);
		udelay(1);
		ग_लिखोl(पढ़ोl(efuse->base + REG_EFUSE_CTRL) |
			     RK3288_STROBE, efuse->base + REG_EFUSE_CTRL);
		udelay(1);
		*buf++ = पढ़ोb(efuse->base + REG_EFUSE_DOUT);
		ग_लिखोl(पढ़ोl(efuse->base + REG_EFUSE_CTRL) &
		       (~RK3288_STROBE), efuse->base + REG_EFUSE_CTRL);
		udelay(1);
	पूर्ण

	/* Switch to standby mode */
	ग_लिखोl(RK3288_PGENB | RK3288_CSB, efuse->base + REG_EFUSE_CTRL);

	clk_disable_unprepare(efuse->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_rk3328_efuse_पढ़ो(व्योम *context, अचिन्हित पूर्णांक offset,
				      व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा rockchip_efuse_chip *efuse = context;
	अचिन्हित पूर्णांक addr_start, addr_end, addr_offset, addr_len;
	u32 out_value, status;
	u8 *buf;
	पूर्णांक ret, i = 0;

	ret = clk_prepare_enable(efuse->clk);
	अगर (ret < 0) अणु
		dev_err(efuse->dev, "failed to prepare/enable efuse clk\n");
		वापस ret;
	पूर्ण

	/* 128 Byte efuse, 96 Byte क्रम secure, 32 Byte क्रम non-secure */
	offset += RK3328_SECURE_SIZES;
	addr_start = roundकरोwn(offset, RK3399_NBYTES) / RK3399_NBYTES;
	addr_end = roundup(offset + bytes, RK3399_NBYTES) / RK3399_NBYTES;
	addr_offset = offset % RK3399_NBYTES;
	addr_len = addr_end - addr_start;

	buf = kzalloc(array3_size(addr_len, RK3399_NBYTES, माप(*buf)),
		      GFP_KERNEL);
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ nomem;
	पूर्ण

	जबतक (addr_len--) अणु
		ग_लिखोl(RK3328_AUTO_RD | RK3328_AUTO_ENB |
		       ((addr_start++ & RK3399_A_MASK) << RK3399_A_SHIFT),
		       efuse->base + RK3328_AUTO_CTRL);
		udelay(4);
		status = पढ़ोl(efuse->base + RK3328_INT_STATUS);
		अगर (!(status & RK3328_INT_FINISH)) अणु
			ret = -EIO;
			जाओ err;
		पूर्ण
		out_value = पढ़ोl(efuse->base + RK3328_DOUT);
		ग_लिखोl(RK3328_INT_FINISH, efuse->base + RK3328_INT_STATUS);

		स_नकल(&buf[i], &out_value, RK3399_NBYTES);
		i += RK3399_NBYTES;
	पूर्ण

	स_नकल(val, buf + addr_offset, bytes);
err:
	kमुक्त(buf);
nomem:
	clk_disable_unprepare(efuse->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_rk3399_efuse_पढ़ो(व्योम *context, अचिन्हित पूर्णांक offset,
				      व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा rockchip_efuse_chip *efuse = context;
	अचिन्हित पूर्णांक addr_start, addr_end, addr_offset, addr_len;
	u32 out_value;
	u8 *buf;
	पूर्णांक ret, i = 0;

	ret = clk_prepare_enable(efuse->clk);
	अगर (ret < 0) अणु
		dev_err(efuse->dev, "failed to prepare/enable efuse clk\n");
		वापस ret;
	पूर्ण

	addr_start = roundकरोwn(offset, RK3399_NBYTES) / RK3399_NBYTES;
	addr_end = roundup(offset + bytes, RK3399_NBYTES) / RK3399_NBYTES;
	addr_offset = offset % RK3399_NBYTES;
	addr_len = addr_end - addr_start;

	buf = kzalloc(array3_size(addr_len, RK3399_NBYTES, माप(*buf)),
		      GFP_KERNEL);
	अगर (!buf) अणु
		clk_disable_unprepare(efuse->clk);
		वापस -ENOMEM;
	पूर्ण

	ग_लिखोl(RK3399_LOAD | RK3399_PGENB | RK3399_STROBSFTSEL | RK3399_RSB,
	       efuse->base + REG_EFUSE_CTRL);
	udelay(1);
	जबतक (addr_len--) अणु
		ग_लिखोl(पढ़ोl(efuse->base + REG_EFUSE_CTRL) | RK3399_STROBE |
		       ((addr_start++ & RK3399_A_MASK) << RK3399_A_SHIFT),
		       efuse->base + REG_EFUSE_CTRL);
		udelay(1);
		out_value = पढ़ोl(efuse->base + REG_EFUSE_DOUT);
		ग_लिखोl(पढ़ोl(efuse->base + REG_EFUSE_CTRL) & (~RK3399_STROBE),
		       efuse->base + REG_EFUSE_CTRL);
		udelay(1);

		स_नकल(&buf[i], &out_value, RK3399_NBYTES);
		i += RK3399_NBYTES;
	पूर्ण

	/* Switch to standby mode */
	ग_लिखोl(RK3399_PD | RK3399_CSB, efuse->base + REG_EFUSE_CTRL);

	स_नकल(val, buf + addr_offset, bytes);

	kमुक्त(buf);

	clk_disable_unprepare(efuse->clk);

	वापस 0;
पूर्ण

अटल काष्ठा nvmem_config econfig = अणु
	.name = "rockchip-efuse",
	.stride = 1,
	.word_size = 1,
	.पढ़ो_only = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rockchip_efuse_match[] = अणु
	/* deprecated but kept around क्रम dts binding compatibility */
	अणु
		.compatible = "rockchip,rockchip-efuse",
		.data = (व्योम *)&rockchip_rk3288_efuse_पढ़ो,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3066a-efuse",
		.data = (व्योम *)&rockchip_rk3288_efuse_पढ़ो,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3188-efuse",
		.data = (व्योम *)&rockchip_rk3288_efuse_पढ़ो,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3228-efuse",
		.data = (व्योम *)&rockchip_rk3288_efuse_पढ़ो,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3288-efuse",
		.data = (व्योम *)&rockchip_rk3288_efuse_पढ़ो,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3368-efuse",
		.data = (व्योम *)&rockchip_rk3288_efuse_पढ़ो,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3328-efuse",
		.data = (व्योम *)&rockchip_rk3328_efuse_पढ़ो,
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3399-efuse",
		.data = (व्योम *)&rockchip_rk3399_efuse_पढ़ो,
	पूर्ण,
	अणु /* sentinel */पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rockchip_efuse_match);

अटल पूर्णांक rockchip_efuse_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा nvmem_device *nvmem;
	काष्ठा rockchip_efuse_chip *efuse;
	स्थिर व्योम *data;
	काष्ठा device *dev = &pdev->dev;

	data = of_device_get_match_data(dev);
	अगर (!data) अणु
		dev_err(dev, "failed to get match data\n");
		वापस -EINVAL;
	पूर्ण

	efuse = devm_kzalloc(dev, माप(काष्ठा rockchip_efuse_chip),
			     GFP_KERNEL);
	अगर (!efuse)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	efuse->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(efuse->base))
		वापस PTR_ERR(efuse->base);

	efuse->clk = devm_clk_get(dev, "pclk_efuse");
	अगर (IS_ERR(efuse->clk))
		वापस PTR_ERR(efuse->clk);

	efuse->dev = dev;
	अगर (of_property_पढ़ो_u32(dev->of_node, "rockchip,efuse-size",
				 &econfig.size))
		econfig.size = resource_size(res);
	econfig.reg_पढ़ो = data;
	econfig.priv = efuse;
	econfig.dev = efuse->dev;
	nvmem = devm_nvmem_रेजिस्टर(dev, &econfig);

	वापस PTR_ERR_OR_ZERO(nvmem);
पूर्ण

अटल काष्ठा platक्रमm_driver rockchip_efuse_driver = अणु
	.probe = rockchip_efuse_probe,
	.driver = अणु
		.name = "rockchip-efuse",
		.of_match_table = rockchip_efuse_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rockchip_efuse_driver);
MODULE_DESCRIPTION("rockchip_efuse driver");
MODULE_LICENSE("GPL v2");
