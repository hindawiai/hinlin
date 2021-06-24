<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Allwinner sunXi SoCs Security ID support.
 *
 * Copyright (c) 2013 Oliver Schinagl <oliver@schinagl.nl>
 * Copyright (C) 2014 Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/अक्रमom.h>

/* Registers and special values क्रम करोing रेजिस्टर-based SID पढ़ोout on H3 */
#घोषणा SUN8I_SID_PRCTL		0x40
#घोषणा SUN8I_SID_RDKEY		0x60

#घोषणा SUN8I_SID_OFFSET_MASK	0x1FF
#घोषणा SUN8I_SID_OFFSET_SHIFT	16
#घोषणा SUN8I_SID_OP_LOCK	(0xAC << 8)
#घोषणा SUN8I_SID_READ		BIT(1)

काष्ठा sunxi_sid_cfg अणु
	u32	value_offset;
	u32	size;
	bool	need_रेजिस्टर_पढ़ोout;
पूर्ण;

काष्ठा sunxi_sid अणु
	व्योम __iomem		*base;
	u32			value_offset;
पूर्ण;

अटल पूर्णांक sunxi_sid_पढ़ो(व्योम *context, अचिन्हित पूर्णांक offset,
			  व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा sunxi_sid *sid = context;

	स_नकल_fromio(val, sid->base + sid->value_offset + offset, bytes);

	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_sid_रेजिस्टर_पढ़ोout(स्थिर काष्ठा sunxi_sid *sid,
				      स्थिर अचिन्हित पूर्णांक offset,
				      u32 *out)
अणु
	u32 reg_val;
	पूर्णांक ret;

	/* Set word, lock access, and set पढ़ो command */
	reg_val = (offset & SUN8I_SID_OFFSET_MASK)
		  << SUN8I_SID_OFFSET_SHIFT;
	reg_val |= SUN8I_SID_OP_LOCK | SUN8I_SID_READ;
	ग_लिखोl(reg_val, sid->base + SUN8I_SID_PRCTL);

	ret = पढ़ोl_poll_समयout(sid->base + SUN8I_SID_PRCTL, reg_val,
				 !(reg_val & SUN8I_SID_READ), 100, 250000);
	अगर (ret)
		वापस ret;

	अगर (out)
		*out = पढ़ोl(sid->base + SUN8I_SID_RDKEY);

	ग_लिखोl(0, sid->base + SUN8I_SID_PRCTL);

	वापस 0;
पूर्ण

/*
 * On Allwinner H3, the value on the 0x200 offset of the SID controller seems
 * to be not reliable at all.
 * Read by the रेजिस्टरs instead.
 */
अटल पूर्णांक sun8i_sid_पढ़ो_by_reg(व्योम *context, अचिन्हित पूर्णांक offset,
				 व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा sunxi_sid *sid = context;
	u32 word;
	पूर्णांक ret;

	/* .stride = 4 so offset is guaranteed to be aligned */
	जबतक (bytes >= 4) अणु
		ret = sun8i_sid_रेजिस्टर_पढ़ोout(sid, offset, val);
		अगर (ret)
			वापस ret;

		val += 4;
		offset += 4;
		bytes -= 4;
	पूर्ण

	अगर (!bytes)
		वापस 0;

	/* Handle any trailing bytes */
	ret = sun8i_sid_रेजिस्टर_पढ़ोout(sid, offset, &word);
	अगर (ret)
		वापस ret;

	स_नकल(val, &word, bytes);

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_sid_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	काष्ठा nvmem_config *nvmem_cfg;
	काष्ठा nvmem_device *nvmem;
	काष्ठा sunxi_sid *sid;
	पूर्णांक size;
	अक्षर *अक्रमomness;
	स्थिर काष्ठा sunxi_sid_cfg *cfg;

	sid = devm_kzalloc(dev, माप(*sid), GFP_KERNEL);
	अगर (!sid)
		वापस -ENOMEM;

	cfg = of_device_get_match_data(dev);
	अगर (!cfg)
		वापस -EINVAL;
	sid->value_offset = cfg->value_offset;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	sid->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(sid->base))
		वापस PTR_ERR(sid->base);

	size = cfg->size;

	nvmem_cfg = devm_kzalloc(dev, माप(*nvmem_cfg), GFP_KERNEL);
	अगर (!nvmem_cfg)
		वापस -ENOMEM;

	nvmem_cfg->dev = dev;
	nvmem_cfg->name = "sunxi-sid";
	nvmem_cfg->पढ़ो_only = true;
	nvmem_cfg->size = cfg->size;
	nvmem_cfg->word_size = 1;
	nvmem_cfg->stride = 4;
	nvmem_cfg->priv = sid;
	अगर (cfg->need_रेजिस्टर_पढ़ोout)
		nvmem_cfg->reg_पढ़ो = sun8i_sid_पढ़ो_by_reg;
	अन्यथा
		nvmem_cfg->reg_पढ़ो = sunxi_sid_पढ़ो;

	nvmem = devm_nvmem_रेजिस्टर(dev, nvmem_cfg);
	अगर (IS_ERR(nvmem))
		वापस PTR_ERR(nvmem);

	अक्रमomness = kzalloc(size, GFP_KERNEL);
	अगर (!अक्रमomness)
		वापस -ENOMEM;

	nvmem_cfg->reg_पढ़ो(sid, 0, अक्रमomness, size);
	add_device_अक्रमomness(अक्रमomness, size);
	kमुक्त(अक्रमomness);

	platक्रमm_set_drvdata(pdev, nvmem);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sunxi_sid_cfg sun4i_a10_cfg = अणु
	.size = 0x10,
पूर्ण;

अटल स्थिर काष्ठा sunxi_sid_cfg sun7i_a20_cfg = अणु
	.size = 0x200,
पूर्ण;

अटल स्थिर काष्ठा sunxi_sid_cfg sun8i_h3_cfg = अणु
	.value_offset = 0x200,
	.size = 0x100,
	.need_रेजिस्टर_पढ़ोout = true,
पूर्ण;

अटल स्थिर काष्ठा sunxi_sid_cfg sun50i_a64_cfg = अणु
	.value_offset = 0x200,
	.size = 0x100,
	.need_रेजिस्टर_पढ़ोout = true,
पूर्ण;

अटल स्थिर काष्ठा sunxi_sid_cfg sun50i_h6_cfg = अणु
	.value_offset = 0x200,
	.size = 0x200,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sunxi_sid_of_match[] = अणु
	अणु .compatible = "allwinner,sun4i-a10-sid", .data = &sun4i_a10_cfg पूर्ण,
	अणु .compatible = "allwinner,sun7i-a20-sid", .data = &sun7i_a20_cfg पूर्ण,
	अणु .compatible = "allwinner,sun8i-a83t-sid", .data = &sun50i_a64_cfg पूर्ण,
	अणु .compatible = "allwinner,sun8i-h3-sid", .data = &sun8i_h3_cfg पूर्ण,
	अणु .compatible = "allwinner,sun50i-a64-sid", .data = &sun50i_a64_cfg पूर्ण,
	अणु .compatible = "allwinner,sun50i-h5-sid", .data = &sun50i_a64_cfg पूर्ण,
	अणु .compatible = "allwinner,sun50i-h6-sid", .data = &sun50i_h6_cfg पूर्ण,
	अणु/* sentinel */पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sunxi_sid_of_match);

अटल काष्ठा platक्रमm_driver sunxi_sid_driver = अणु
	.probe = sunxi_sid_probe,
	.driver = अणु
		.name = "eeprom-sunxi-sid",
		.of_match_table = sunxi_sid_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sunxi_sid_driver);

MODULE_AUTHOR("Oliver Schinagl <oliver@schinagl.nl>");
MODULE_DESCRIPTION("Allwinner sunxi security id driver");
MODULE_LICENSE("GPL");
