<शैली गुरु>
/*
 * Copyright (c) 2017 Martin Blumenstingl <martin.blumenstingl@googlemail.com>
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

#घोषणा MESON_SOCINFO_MAJOR_VER_MESON6		0x16
#घोषणा MESON_SOCINFO_MAJOR_VER_MESON8		0x19
#घोषणा MESON_SOCINFO_MAJOR_VER_MESON8B		0x1b

#घोषणा MESON_MX_ASSIST_HW_REV			0x14c

#घोषणा MESON_MX_ANALOG_TOP_METAL_REVISION	0x0

#घोषणा MESON_MX_BOOTROM_MISC_VER		0x4

अटल स्थिर अक्षर *meson_mx_socinfo_revision(अचिन्हित पूर्णांक major_ver,
					     अचिन्हित पूर्णांक misc_ver,
					     अचिन्हित पूर्णांक metal_rev)
अणु
	अचिन्हित पूर्णांक minor_ver;

	चयन (major_ver) अणु
	हाल MESON_SOCINFO_MAJOR_VER_MESON6:
		minor_ver = 0xa;
		अवरोध;

	हाल MESON_SOCINFO_MAJOR_VER_MESON8:
		अगर (metal_rev == 0x11111112)
			major_ver = 0x1d;

		अगर (metal_rev == 0x11111111 || metal_rev == 0x11111112)
			minor_ver = 0xa;
		अन्यथा अगर (metal_rev == 0x11111113)
			minor_ver = 0xb;
		अन्यथा अगर (metal_rev == 0x11111133)
			minor_ver = 0xc;
		अन्यथा
			minor_ver = 0xd;

		अवरोध;

	हाल MESON_SOCINFO_MAJOR_VER_MESON8B:
		अगर (metal_rev == 0x11111111)
			minor_ver = 0xa;
		अन्यथा
			minor_ver = 0xb;

		अवरोध;

	शेष:
		minor_ver = 0x0;
		अवरोध;
	पूर्ण

	वापस kaप्र_लिखो(GFP_KERNEL, "Rev%X (%x - 0:%X)", minor_ver, major_ver,
			 misc_ver);
पूर्ण

अटल स्थिर अक्षर *meson_mx_socinfo_soc_id(अचिन्हित पूर्णांक major_ver,
					   अचिन्हित पूर्णांक metal_rev)
अणु
	स्थिर अक्षर *soc_id;

	चयन (major_ver) अणु
	हाल MESON_SOCINFO_MAJOR_VER_MESON6:
		soc_id = "Meson6 (AML8726-MX)";
		अवरोध;

	हाल MESON_SOCINFO_MAJOR_VER_MESON8:
		अगर (metal_rev == 0x11111112)
			soc_id = "Meson8m2 (S812)";
		अन्यथा
			soc_id = "Meson8 (S802)";

		अवरोध;

	हाल MESON_SOCINFO_MAJOR_VER_MESON8B:
		soc_id = "Meson8b (S805)";
		अवरोध;

	शेष:
		soc_id = "Unknown";
		अवरोध;
	पूर्ण

	वापस kstrdup_स्थिर(soc_id, GFP_KERNEL);
पूर्ण

अटल स्थिर काष्ठा of_device_id meson_mx_socinfo_analog_top_ids[] = अणु
	अणु .compatible = "amlogic,meson8-analog-top", पूर्ण,
	अणु .compatible = "amlogic,meson8b-analog-top", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक __init meson_mx_socinfo_init(व्योम)
अणु
	काष्ठा soc_device_attribute *soc_dev_attr;
	काष्ठा soc_device *soc_dev;
	काष्ठा device_node *np;
	काष्ठा regmap *assist_regmap, *bootrom_regmap, *analog_top_regmap;
	अचिन्हित पूर्णांक major_ver, misc_ver, metal_rev = 0;
	पूर्णांक ret;

	assist_regmap =
		syscon_regmap_lookup_by_compatible("amlogic,meson-mx-assist");
	अगर (IS_ERR(assist_regmap))
		वापस PTR_ERR(assist_regmap);

	bootrom_regmap =
		syscon_regmap_lookup_by_compatible("amlogic,meson-mx-bootrom");
	अगर (IS_ERR(bootrom_regmap))
		वापस PTR_ERR(bootrom_regmap);

	np = of_find_matching_node(शून्य, meson_mx_socinfo_analog_top_ids);
	अगर (np) अणु
		analog_top_regmap = syscon_node_to_regmap(np);
		अगर (IS_ERR(analog_top_regmap))
			वापस PTR_ERR(analog_top_regmap);

		ret = regmap_पढ़ो(analog_top_regmap,
				  MESON_MX_ANALOG_TOP_METAL_REVISION,
				  &metal_rev);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(assist_regmap, MESON_MX_ASSIST_HW_REV, &major_ver);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(bootrom_regmap, MESON_MX_BOOTROM_MISC_VER,
			  &misc_ver);
	अगर (ret < 0)
		वापस ret;

	soc_dev_attr = kzalloc(माप(*soc_dev_attr), GFP_KERNEL);
	अगर (!soc_dev_attr)
		वापस -ENODEV;

	soc_dev_attr->family = "Amlogic Meson";

	np = of_find_node_by_path("/");
	of_property_पढ़ो_string(np, "model", &soc_dev_attr->machine);
	of_node_put(np);

	soc_dev_attr->revision = meson_mx_socinfo_revision(major_ver, misc_ver,
							   metal_rev);
	soc_dev_attr->soc_id = meson_mx_socinfo_soc_id(major_ver, metal_rev);

	soc_dev = soc_device_रेजिस्टर(soc_dev_attr);
	अगर (IS_ERR(soc_dev)) अणु
		kमुक्त_स्थिर(soc_dev_attr->revision);
		kमुक्त_स्थिर(soc_dev_attr->soc_id);
		kमुक्त(soc_dev_attr);
		वापस PTR_ERR(soc_dev);
	पूर्ण

	dev_info(soc_device_to_device(soc_dev), "Amlogic %s %s detected\n",
		 soc_dev_attr->soc_id, soc_dev_attr->revision);

	वापस 0;
पूर्ण
device_initcall(meson_mx_socinfo_init);
