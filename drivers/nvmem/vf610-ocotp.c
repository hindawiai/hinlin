<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Toradex AG.
 *
 * Author: Sanchayan Maity <sanchayan.maity@toradex.com>
 *
 * Based on the barebox ocotp driver,
 * Copyright (c) 2010 Baruch Siach <baruch@tkos.co.il>
 *	Orex Computed Radiography
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

/* OCOTP Register Offsets */
#घोषणा OCOTP_CTRL_REG				0x00
#घोषणा OCOTP_CTRL_SET				0x04
#घोषणा OCOTP_CTRL_CLR				0x08
#घोषणा OCOTP_TIMING				0x10
#घोषणा OCOTP_DATA				0x20
#घोषणा OCOTP_READ_CTRL_REG			0x30
#घोषणा OCOTP_READ_FUSE_DATA			0x40

/* OCOTP Register bits and masks */
#घोषणा OCOTP_CTRL_WR_UNLOCK			16
#घोषणा OCOTP_CTRL_WR_UNLOCK_KEY		0x3E77
#घोषणा OCOTP_CTRL_WR_UNLOCK_MASK		GENMASK(31, 16)
#घोषणा OCOTP_CTRL_ADDR				0
#घोषणा OCOTP_CTRL_ADDR_MASK			GENMASK(6, 0)
#घोषणा OCOTP_CTRL_RELOAD_SHADOWS		BIT(10)
#घोषणा OCOTP_CTRL_ERR				BIT(9)
#घोषणा OCOTP_CTRL_BUSY				BIT(8)

#घोषणा OCOTP_TIMING_STROBE_READ		16
#घोषणा OCOTP_TIMING_STROBE_READ_MASK		GENMASK(21, 16)
#घोषणा OCOTP_TIMING_RELAX			12
#घोषणा OCOTP_TIMING_RELAX_MASK			GENMASK(15, 12)
#घोषणा OCOTP_TIMING_STROBE_PROG		0
#घोषणा OCOTP_TIMING_STROBE_PROG_MASK		GENMASK(11, 0)

#घोषणा OCOTP_READ_CTRL_READ_FUSE		0x1

#घोषणा VF610_OCOTP_TIMEOUT			100000

#घोषणा BF(value, field)		(((value) << field) & field##_MASK)

#घोषणा DEF_RELAX				20

अटल स्थिर पूर्णांक base_to_fuse_addr_mappings[][2] = अणु
	अणु0x400, 0x00पूर्ण,
	अणु0x410, 0x01पूर्ण,
	अणु0x420, 0x02पूर्ण,
	अणु0x450, 0x05पूर्ण,
	अणु0x4F0, 0x0Fपूर्ण,
	अणु0x600, 0x20पूर्ण,
	अणु0x610, 0x21पूर्ण,
	अणु0x620, 0x22पूर्ण,
	अणु0x630, 0x23पूर्ण,
	अणु0x640, 0x24पूर्ण,
	अणु0x650, 0x25पूर्ण,
	अणु0x660, 0x26पूर्ण,
	अणु0x670, 0x27पूर्ण,
	अणु0x6F0, 0x2Fपूर्ण,
	अणु0x880, 0x38पूर्ण,
	अणु0x890, 0x39पूर्ण,
	अणु0x8A0, 0x3Aपूर्ण,
	अणु0x8B0, 0x3Bपूर्ण,
	अणु0x8C0, 0x3Cपूर्ण,
	अणु0x8D0, 0x3Dपूर्ण,
	अणु0x8E0, 0x3Eपूर्ण,
	अणु0x8F0, 0x3Fपूर्ण,
	अणु0xC80, 0x78पूर्ण,
	अणु0xC90, 0x79पूर्ण,
	अणु0xCA0, 0x7Aपूर्ण,
	अणु0xCB0, 0x7Bपूर्ण,
	अणु0xCC0, 0x7Cपूर्ण,
	अणु0xCD0, 0x7Dपूर्ण,
	अणु0xCE0, 0x7Eपूर्ण,
	अणु0xCF0, 0x7Fपूर्ण,
पूर्ण;

काष्ठा vf610_ocotp अणु
	व्योम __iomem *base;
	काष्ठा clk *clk;
	काष्ठा device *dev;
	काष्ठा nvmem_device *nvmem;
	पूर्णांक timing;
पूर्ण;

अटल पूर्णांक vf610_ocotp_रुको_busy(व्योम __iomem *base)
अणु
	पूर्णांक समयout = VF610_OCOTP_TIMEOUT;

	जबतक ((पढ़ोl(base) & OCOTP_CTRL_BUSY) && --समयout)
		udelay(10);

	अगर (!समयout) अणु
		ग_लिखोl(OCOTP_CTRL_ERR, base + OCOTP_CTRL_CLR);
		वापस -ETIMEDOUT;
	पूर्ण

	udelay(10);

	वापस 0;
पूर्ण

अटल पूर्णांक vf610_ocotp_calculate_timing(काष्ठा vf610_ocotp *ocotp_dev)
अणु
	u32 clk_rate;
	u32 relax, strobe_पढ़ो, strobe_prog;
	u32 timing;

	clk_rate = clk_get_rate(ocotp_dev->clk);

	/* Refer section OTP पढ़ो/ग_लिखो timing parameters in TRM */
	relax = clk_rate / (1000000000 / DEF_RELAX) - 1;
	strobe_prog = clk_rate / (1000000000 / 10000) + 2 * (DEF_RELAX + 1) - 1;
	strobe_पढ़ो = clk_rate / (1000000000 / 40) + 2 * (DEF_RELAX + 1) - 1;

	timing = BF(relax, OCOTP_TIMING_RELAX);
	timing |= BF(strobe_पढ़ो, OCOTP_TIMING_STROBE_READ);
	timing |= BF(strobe_prog, OCOTP_TIMING_STROBE_PROG);

	वापस timing;
पूर्ण

अटल पूर्णांक vf610_get_fuse_address(पूर्णांक base_addr_offset)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(base_to_fuse_addr_mappings); i++) अणु
		अगर (base_to_fuse_addr_mappings[i][0] == base_addr_offset)
			वापस base_to_fuse_addr_mappings[i][1];
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vf610_ocotp_पढ़ो(व्योम *context, अचिन्हित पूर्णांक offset,
			व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा vf610_ocotp *ocotp = context;
	व्योम __iomem *base = ocotp->base;
	u32 reg, *buf = val;
	पूर्णांक fuse_addr;
	पूर्णांक ret;

	जबतक (bytes > 0) अणु
		fuse_addr = vf610_get_fuse_address(offset);
		अगर (fuse_addr > 0) अणु
			ग_लिखोl(ocotp->timing, base + OCOTP_TIMING);
			ret = vf610_ocotp_रुको_busy(base + OCOTP_CTRL_REG);
			अगर (ret)
				वापस ret;

			reg = पढ़ोl(base + OCOTP_CTRL_REG);
			reg &= ~OCOTP_CTRL_ADDR_MASK;
			reg &= ~OCOTP_CTRL_WR_UNLOCK_MASK;
			reg |= BF(fuse_addr, OCOTP_CTRL_ADDR);
			ग_लिखोl(reg, base + OCOTP_CTRL_REG);

			ग_लिखोl(OCOTP_READ_CTRL_READ_FUSE,
				base + OCOTP_READ_CTRL_REG);
			ret = vf610_ocotp_रुको_busy(base + OCOTP_CTRL_REG);
			अगर (ret)
				वापस ret;

			अगर (पढ़ोl(base) & OCOTP_CTRL_ERR) अणु
				dev_dbg(ocotp->dev, "Error reading from fuse address %x\n",
					fuse_addr);
				ग_लिखोl(OCOTP_CTRL_ERR, base + OCOTP_CTRL_CLR);
			पूर्ण

			/*
			 * In हाल of error, we करो not पात and expect to पढ़ो
			 * 0xBADABADA as mentioned by the TRM. We just पढ़ो this
			 * value and वापस.
			 */
			*buf = पढ़ोl(base + OCOTP_READ_FUSE_DATA);
		पूर्ण अन्यथा अणु
			*buf = 0;
		पूर्ण

		buf++;
		bytes -= 4;
		offset += 4;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा nvmem_config ocotp_config = अणु
	.name = "ocotp",
	.stride = 4,
	.word_size = 4,
	.reg_पढ़ो = vf610_ocotp_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ocotp_of_match[] = अणु
	अणु .compatible = "fsl,vf610-ocotp", पूर्ण,
	अणु/* sentinel */पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ocotp_of_match);

अटल पूर्णांक vf610_ocotp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	काष्ठा vf610_ocotp *ocotp_dev;

	ocotp_dev = devm_kzalloc(dev, माप(काष्ठा vf610_ocotp), GFP_KERNEL);
	अगर (!ocotp_dev)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ocotp_dev->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(ocotp_dev->base))
		वापस PTR_ERR(ocotp_dev->base);

	ocotp_dev->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(ocotp_dev->clk)) अणु
		dev_err(dev, "failed getting clock, err = %ld\n",
			PTR_ERR(ocotp_dev->clk));
		वापस PTR_ERR(ocotp_dev->clk);
	पूर्ण
	ocotp_dev->dev = dev;
	ocotp_dev->timing = vf610_ocotp_calculate_timing(ocotp_dev);

	ocotp_config.size = resource_size(res);
	ocotp_config.priv = ocotp_dev;
	ocotp_config.dev = dev;

	ocotp_dev->nvmem = devm_nvmem_रेजिस्टर(dev, &ocotp_config);

	वापस PTR_ERR_OR_ZERO(ocotp_dev->nvmem);
पूर्ण

अटल काष्ठा platक्रमm_driver vf610_ocotp_driver = अणु
	.probe = vf610_ocotp_probe,
	.driver = अणु
		.name = "vf610-ocotp",
		.of_match_table = ocotp_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(vf610_ocotp_driver);
MODULE_AUTHOR("Sanchayan Maity <sanchayan.maity@toradex.com>");
MODULE_DESCRIPTION("Vybrid OCOTP driver");
MODULE_LICENSE("GPL v2");
