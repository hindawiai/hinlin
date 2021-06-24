<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2009-2013, The Linux Foundation. All rights reserved.
 * Copyright (c) 2010, Google Inc.
 *
 * Original authors: Code Aurora Forum
 *
 * Author: Dima Zavin <dima@android.com>
 *  - Largely rewritten from original to not be an i2c driver.
 */

#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/ssbi.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

/* SSBI 2.0 controller रेजिस्टरs */
#घोषणा SSBI2_CMD			0x0008
#घोषणा SSBI2_RD			0x0010
#घोषणा SSBI2_STATUS			0x0014
#घोषणा SSBI2_MODE2			0x001C

/* SSBI_CMD fields */
#घोषणा SSBI_CMD_RDWRN			(1 << 24)

/* SSBI_STATUS fields */
#घोषणा SSBI_STATUS_RD_READY		(1 << 2)
#घोषणा SSBI_STATUS_READY		(1 << 1)
#घोषणा SSBI_STATUS_MCHN_BUSY		(1 << 0)

/* SSBI_MODE2 fields */
#घोषणा SSBI_MODE2_REG_ADDR_15_8_SHFT	0x04
#घोषणा SSBI_MODE2_REG_ADDR_15_8_MASK	(0x7f << SSBI_MODE2_REG_ADDR_15_8_SHFT)

#घोषणा SET_SSBI_MODE2_REG_ADDR_15_8(MD, AD) \
	(((MD) & 0x0F) | ((((AD) >> 8) << SSBI_MODE2_REG_ADDR_15_8_SHFT) & \
	SSBI_MODE2_REG_ADDR_15_8_MASK))

/* SSBI PMIC Arbiter command रेजिस्टरs */
#घोषणा SSBI_PA_CMD			0x0000
#घोषणा SSBI_PA_RD_STATUS		0x0004

/* SSBI_PA_CMD fields */
#घोषणा SSBI_PA_CMD_RDWRN		(1 << 24)
#घोषणा SSBI_PA_CMD_ADDR_MASK		0x7fff /* REG_ADDR_7_0, REG_ADDR_8_14*/

/* SSBI_PA_RD_STATUS fields */
#घोषणा SSBI_PA_RD_STATUS_TRANS_DONE	(1 << 27)
#घोषणा SSBI_PA_RD_STATUS_TRANS_DENIED	(1 << 26)

#घोषणा SSBI_TIMEOUT_US			100

क्रमागत ssbi_controller_type अणु
	MSM_SBI_CTRL_SSBI = 0,
	MSM_SBI_CTRL_SSBI2,
	MSM_SBI_CTRL_PMIC_ARBITER,
पूर्ण;

काष्ठा ssbi अणु
	काष्ठा device		*slave;
	व्योम __iomem		*base;
	spinlock_t		lock;
	क्रमागत ssbi_controller_type controller_type;
	पूर्णांक (*पढ़ो)(काष्ठा ssbi *, u16 addr, u8 *buf, पूर्णांक len);
	पूर्णांक (*ग_लिखो)(काष्ठा ssbi *, u16 addr, स्थिर u8 *buf, पूर्णांक len);
पूर्ण;

अटल अंतरभूत u32 ssbi_पढ़ोl(काष्ठा ssbi *ssbi, u32 reg)
अणु
	वापस पढ़ोl(ssbi->base + reg);
पूर्ण

अटल अंतरभूत व्योम ssbi_ग_लिखोl(काष्ठा ssbi *ssbi, u32 val, u32 reg)
अणु
	ग_लिखोl(val, ssbi->base + reg);
पूर्ण

/*
 * Via निजी exchange with one of the original authors, the hardware
 * should generally finish a transaction in about 5us.  The worst
 * हाल, is when using the arbiter and both other CPUs have just
 * started trying to use the SSBI bus will result in a समय of about
 * 20us.  It should never take दीर्घer than this.
 *
 * As such, this रुको merely spins, with a udelay.
 */
अटल पूर्णांक ssbi_रुको_mask(काष्ठा ssbi *ssbi, u32 set_mask, u32 clr_mask)
अणु
	u32 समयout = SSBI_TIMEOUT_US;
	u32 val;

	जबतक (समयout--) अणु
		val = ssbi_पढ़ोl(ssbi, SSBI2_STATUS);
		अगर (((val & set_mask) == set_mask) && ((val & clr_mask) == 0))
			वापस 0;
		udelay(1);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक
ssbi_पढ़ो_bytes(काष्ठा ssbi *ssbi, u16 addr, u8 *buf, पूर्णांक len)
अणु
	u32 cmd = SSBI_CMD_RDWRN | ((addr & 0xff) << 16);
	पूर्णांक ret = 0;

	अगर (ssbi->controller_type == MSM_SBI_CTRL_SSBI2) अणु
		u32 mode2 = ssbi_पढ़ोl(ssbi, SSBI2_MODE2);
		mode2 = SET_SSBI_MODE2_REG_ADDR_15_8(mode2, addr);
		ssbi_ग_लिखोl(ssbi, mode2, SSBI2_MODE2);
	पूर्ण

	जबतक (len) अणु
		ret = ssbi_रुको_mask(ssbi, SSBI_STATUS_READY, 0);
		अगर (ret)
			जाओ err;

		ssbi_ग_लिखोl(ssbi, cmd, SSBI2_CMD);
		ret = ssbi_रुको_mask(ssbi, SSBI_STATUS_RD_READY, 0);
		अगर (ret)
			जाओ err;
		*buf++ = ssbi_पढ़ोl(ssbi, SSBI2_RD) & 0xff;
		len--;
	पूर्ण

err:
	वापस ret;
पूर्ण

अटल पूर्णांक
ssbi_ग_लिखो_bytes(काष्ठा ssbi *ssbi, u16 addr, स्थिर u8 *buf, पूर्णांक len)
अणु
	पूर्णांक ret = 0;

	अगर (ssbi->controller_type == MSM_SBI_CTRL_SSBI2) अणु
		u32 mode2 = ssbi_पढ़ोl(ssbi, SSBI2_MODE2);
		mode2 = SET_SSBI_MODE2_REG_ADDR_15_8(mode2, addr);
		ssbi_ग_लिखोl(ssbi, mode2, SSBI2_MODE2);
	पूर्ण

	जबतक (len) अणु
		ret = ssbi_रुको_mask(ssbi, SSBI_STATUS_READY, 0);
		अगर (ret)
			जाओ err;

		ssbi_ग_लिखोl(ssbi, ((addr & 0xff) << 16) | *buf, SSBI2_CMD);
		ret = ssbi_रुको_mask(ssbi, 0, SSBI_STATUS_MCHN_BUSY);
		अगर (ret)
			जाओ err;
		buf++;
		len--;
	पूर्ण

err:
	वापस ret;
पूर्ण

/*
 * See ssbi_रुको_mask क्रम an explanation of the समय and the
 * busyरुको.
 */
अटल अंतरभूत पूर्णांक
ssbi_pa_transfer(काष्ठा ssbi *ssbi, u32 cmd, u8 *data)
अणु
	u32 समयout = SSBI_TIMEOUT_US;
	u32 rd_status = 0;

	ssbi_ग_लिखोl(ssbi, cmd, SSBI_PA_CMD);

	जबतक (समयout--) अणु
		rd_status = ssbi_पढ़ोl(ssbi, SSBI_PA_RD_STATUS);

		अगर (rd_status & SSBI_PA_RD_STATUS_TRANS_DENIED)
			वापस -EPERM;

		अगर (rd_status & SSBI_PA_RD_STATUS_TRANS_DONE) अणु
			अगर (data)
				*data = rd_status & 0xff;
			वापस 0;
		पूर्ण
		udelay(1);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक
ssbi_pa_पढ़ो_bytes(काष्ठा ssbi *ssbi, u16 addr, u8 *buf, पूर्णांक len)
अणु
	u32 cmd;
	पूर्णांक ret = 0;

	cmd = SSBI_PA_CMD_RDWRN | (addr & SSBI_PA_CMD_ADDR_MASK) << 8;

	जबतक (len) अणु
		ret = ssbi_pa_transfer(ssbi, cmd, buf);
		अगर (ret)
			जाओ err;
		buf++;
		len--;
	पूर्ण

err:
	वापस ret;
पूर्ण

अटल पूर्णांक
ssbi_pa_ग_लिखो_bytes(काष्ठा ssbi *ssbi, u16 addr, स्थिर u8 *buf, पूर्णांक len)
अणु
	u32 cmd;
	पूर्णांक ret = 0;

	जबतक (len) अणु
		cmd = (addr & SSBI_PA_CMD_ADDR_MASK) << 8 | *buf;
		ret = ssbi_pa_transfer(ssbi, cmd, शून्य);
		अगर (ret)
			जाओ err;
		buf++;
		len--;
	पूर्ण

err:
	वापस ret;
पूर्ण

पूर्णांक ssbi_पढ़ो(काष्ठा device *dev, u16 addr, u8 *buf, पूर्णांक len)
अणु
	काष्ठा ssbi *ssbi = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&ssbi->lock, flags);
	ret = ssbi->पढ़ो(ssbi, addr, buf, len);
	spin_unlock_irqrestore(&ssbi->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ssbi_पढ़ो);

पूर्णांक ssbi_ग_लिखो(काष्ठा device *dev, u16 addr, स्थिर u8 *buf, पूर्णांक len)
अणु
	काष्ठा ssbi *ssbi = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&ssbi->lock, flags);
	ret = ssbi->ग_लिखो(ssbi, addr, buf, len);
	spin_unlock_irqrestore(&ssbi->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ssbi_ग_लिखो);

अटल पूर्णांक ssbi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा resource *mem_res;
	काष्ठा ssbi *ssbi;
	स्थिर अक्षर *type;

	ssbi = devm_kzalloc(&pdev->dev, माप(*ssbi), GFP_KERNEL);
	अगर (!ssbi)
		वापस -ENOMEM;

	mem_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ssbi->base = devm_ioremap_resource(&pdev->dev, mem_res);
	अगर (IS_ERR(ssbi->base))
		वापस PTR_ERR(ssbi->base);

	platक्रमm_set_drvdata(pdev, ssbi);

	type = of_get_property(np, "qcom,controller-type", शून्य);
	अगर (type == शून्य) अणु
		dev_err(&pdev->dev, "Missing qcom,controller-type property\n");
		वापस -EINVAL;
	पूर्ण
	dev_info(&pdev->dev, "SSBI controller type: '%s'\n", type);
	अगर (म_भेद(type, "ssbi") == 0)
		ssbi->controller_type = MSM_SBI_CTRL_SSBI;
	अन्यथा अगर (म_भेद(type, "ssbi2") == 0)
		ssbi->controller_type = MSM_SBI_CTRL_SSBI2;
	अन्यथा अगर (म_भेद(type, "pmic-arbiter") == 0)
		ssbi->controller_type = MSM_SBI_CTRL_PMIC_ARBITER;
	अन्यथा अणु
		dev_err(&pdev->dev, "Unknown qcom,controller-type\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ssbi->controller_type == MSM_SBI_CTRL_PMIC_ARBITER) अणु
		ssbi->पढ़ो = ssbi_pa_पढ़ो_bytes;
		ssbi->ग_लिखो = ssbi_pa_ग_लिखो_bytes;
	पूर्ण अन्यथा अणु
		ssbi->पढ़ो = ssbi_पढ़ो_bytes;
		ssbi->ग_लिखो = ssbi_ग_लिखो_bytes;
	पूर्ण

	spin_lock_init(&ssbi->lock);

	वापस devm_of_platक्रमm_populate(&pdev->dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id ssbi_match_table[] = अणु
	अणु .compatible = "qcom,ssbi" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ssbi_match_table);

अटल काष्ठा platक्रमm_driver ssbi_driver = अणु
	.probe		= ssbi_probe,
	.driver		= अणु
		.name	= "ssbi",
		.of_match_table = ssbi_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ssbi_driver);

MODULE_LICENSE("GPL v2");
MODULE_VERSION("1.0");
MODULE_ALIAS("platform:ssbi");
MODULE_AUTHOR("Dima Zavin <dima@android.com>");
