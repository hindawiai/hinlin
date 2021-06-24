<शैली गुरु>
/*
 * Copyright (c) 2017 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 *
 * SPDX-License-Identअगरier: GPL-2.0+
 */

#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/sys_soc.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>

#घोषणा AO_SEC_SD_CFG8		0xe0
#घोषणा AO_SEC_SOCINFO_OFFSET	AO_SEC_SD_CFG8

#घोषणा SOCINFO_MAJOR	GENMASK(31, 24)
#घोषणा SOCINFO_PACK	GENMASK(23, 16)
#घोषणा SOCINFO_MINOR	GENMASK(15, 8)
#घोषणा SOCINFO_MISC	GENMASK(7, 0)

अटल स्थिर काष्ठा meson_gx_soc_id अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक id;
पूर्ण soc_ids[] = अणु
	अणु "GXBB", 0x1f पूर्ण,
	अणु "GXTVBB", 0x20 पूर्ण,
	अणु "GXL", 0x21 पूर्ण,
	अणु "GXM", 0x22 पूर्ण,
	अणु "TXL", 0x23 पूर्ण,
	अणु "TXLX", 0x24 पूर्ण,
	अणु "AXG", 0x25 पूर्ण,
	अणु "GXLX", 0x26 पूर्ण,
	अणु "TXHD", 0x27 पूर्ण,
	अणु "G12A", 0x28 पूर्ण,
	अणु "G12B", 0x29 पूर्ण,
	अणु "SM1", 0x2b पूर्ण,
	अणु "A1", 0x2c पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा meson_gx_package_id अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक major_id;
	अचिन्हित पूर्णांक pack_id;
	अचिन्हित पूर्णांक pack_mask;
पूर्ण soc_packages[] = अणु
	अणु "S905", 0x1f, 0, 0x20 पूर्ण, /* pack_id != 0x20 */
	अणु "S905H", 0x1f, 0x3, 0xf पूर्ण, /* pack_id & 0xf == 0x3 */
	अणु "S905M", 0x1f, 0x20, 0xf0 पूर्ण, /* pack_id == 0x20 */
	अणु "S905D", 0x21, 0, 0xf0 पूर्ण,
	अणु "S905X", 0x21, 0x80, 0xf0 पूर्ण,
	अणु "S905W", 0x21, 0xa0, 0xf0 पूर्ण,
	अणु "S905L", 0x21, 0xc0, 0xf0 पूर्ण,
	अणु "S905M2", 0x21, 0xe0, 0xf0 पूर्ण,
	अणु "S805X", 0x21, 0x30, 0xf0 पूर्ण,
	अणु "S805Y", 0x21, 0xb0, 0xf0 पूर्ण,
	अणु "S912", 0x22, 0, 0x0 पूर्ण, /* Only S912 is known क्रम GXM */
	अणु "962X", 0x24, 0x10, 0xf0 पूर्ण,
	अणु "962E", 0x24, 0x20, 0xf0 पूर्ण,
	अणु "A113X", 0x25, 0x37, 0xff पूर्ण,
	अणु "A113D", 0x25, 0x22, 0xff पूर्ण,
	अणु "S905D2", 0x28, 0x10, 0xf0 पूर्ण,
	अणु "S905X2", 0x28, 0x40, 0xf0 पूर्ण,
	अणु "A311D", 0x29, 0x10, 0xf0 पूर्ण,
	अणु "S922X", 0x29, 0x40, 0xf0 पूर्ण,
	अणु "S905D3", 0x2b, 0x4, 0xf5 पूर्ण,
	अणु "S905X3", 0x2b, 0x5, 0xf5 पूर्ण,
	अणु "S905X3", 0x2b, 0x10, 0x3f पूर्ण,
	अणु "S905D3", 0x2b, 0x30, 0x3f पूर्ण,
	अणु "A113L", 0x2c, 0x0, 0xf8 पूर्ण,
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक socinfo_to_major(u32 socinfo)
अणु
	वापस FIELD_GET(SOCINFO_MAJOR, socinfo);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक socinfo_to_minor(u32 socinfo)
अणु
	वापस FIELD_GET(SOCINFO_MINOR, socinfo);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक socinfo_to_pack(u32 socinfo)
अणु
	वापस FIELD_GET(SOCINFO_PACK, socinfo);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक socinfo_to_misc(u32 socinfo)
अणु
	वापस FIELD_GET(SOCINFO_MISC, socinfo);
पूर्ण

अटल स्थिर अक्षर *socinfo_to_package_id(u32 socinfo)
अणु
	अचिन्हित पूर्णांक pack = socinfo_to_pack(socinfo);
	अचिन्हित पूर्णांक major = socinfo_to_major(socinfo);
	पूर्णांक i;

	क्रम (i = 0 ; i < ARRAY_SIZE(soc_packages) ; ++i) अणु
		अगर (soc_packages[i].major_id == major &&
		    soc_packages[i].pack_id ==
				(pack & soc_packages[i].pack_mask))
			वापस soc_packages[i].name;
	पूर्ण

	वापस "Unknown";
पूर्ण

अटल स्थिर अक्षर *socinfo_to_soc_id(u32 socinfo)
अणु
	अचिन्हित पूर्णांक id = socinfo_to_major(socinfo);
	पूर्णांक i;

	क्रम (i = 0 ; i < ARRAY_SIZE(soc_ids) ; ++i) अणु
		अगर (soc_ids[i].id == id)
			वापस soc_ids[i].name;
	पूर्ण

	वापस "Unknown";
पूर्ण

अटल पूर्णांक __init meson_gx_socinfo_init(व्योम)
अणु
	काष्ठा soc_device_attribute *soc_dev_attr;
	काष्ठा soc_device *soc_dev;
	काष्ठा device_node *np;
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक socinfo;
	काष्ठा device *dev;
	पूर्णांक ret;

	/* look up क्रम chipid node */
	np = of_find_compatible_node(शून्य, शून्य, "amlogic,meson-gx-ao-secure");
	अगर (!np)
		वापस -ENODEV;

	/* check अगर पूर्णांकerface is enabled */
	अगर (!of_device_is_available(np)) अणु
		of_node_put(np);
		वापस -ENODEV;
	पूर्ण

	/* check अगर chip-id is available */
	अगर (!of_property_पढ़ो_bool(np, "amlogic,has-chip-id")) अणु
		of_node_put(np);
		वापस -ENODEV;
	पूर्ण

	/* node should be a syscon */
	regmap = syscon_node_to_regmap(np);
	of_node_put(np);
	अगर (IS_ERR(regmap)) अणु
		pr_err("%s: failed to get regmap\n", __func__);
		वापस -ENODEV;
	पूर्ण

	ret = regmap_पढ़ो(regmap, AO_SEC_SOCINFO_OFFSET, &socinfo);
	अगर (ret < 0)
		वापस ret;

	अगर (!socinfo) अणु
		pr_err("%s: invalid chipid value\n", __func__);
		वापस -EINVAL;
	पूर्ण

	soc_dev_attr = kzalloc(माप(*soc_dev_attr), GFP_KERNEL);
	अगर (!soc_dev_attr)
		वापस -ENODEV;

	soc_dev_attr->family = "Amlogic Meson";

	np = of_find_node_by_path("/");
	of_property_पढ़ो_string(np, "model", &soc_dev_attr->machine);
	of_node_put(np);

	soc_dev_attr->revision = kaप्र_लिखो(GFP_KERNEL, "%x:%x - %x:%x",
					   socinfo_to_major(socinfo),
					   socinfo_to_minor(socinfo),
					   socinfo_to_pack(socinfo),
					   socinfo_to_misc(socinfo));
	soc_dev_attr->soc_id = kaप्र_लिखो(GFP_KERNEL, "%s (%s)",
					 socinfo_to_soc_id(socinfo),
					 socinfo_to_package_id(socinfo));

	soc_dev = soc_device_रेजिस्टर(soc_dev_attr);
	अगर (IS_ERR(soc_dev)) अणु
		kमुक्त(soc_dev_attr->revision);
		kमुक्त_स्थिर(soc_dev_attr->soc_id);
		kमुक्त(soc_dev_attr);
		वापस PTR_ERR(soc_dev);
	पूर्ण
	dev = soc_device_to_device(soc_dev);

	dev_info(dev, "Amlogic Meson %s Revision %x:%x (%x:%x) Detected\n",
			soc_dev_attr->soc_id,
			socinfo_to_major(socinfo),
			socinfo_to_minor(socinfo),
			socinfo_to_pack(socinfo),
			socinfo_to_misc(socinfo));

	वापस 0;
पूर्ण
device_initcall(meson_gx_socinfo_init);
