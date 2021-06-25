<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2020 NXP
 */

#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/sys_soc.h>

#समावेश <soc/imx/cpu.h>
#समावेश <soc/imx/revision.h>

#घोषणा IIM_UID		0x820

#घोषणा OCOTP_UID_H	0x420
#घोषणा OCOTP_UID_L	0x410

#घोषणा OCOTP_ULP_UID_1		0x4b0
#घोषणा OCOTP_ULP_UID_2		0x4c0
#घोषणा OCOTP_ULP_UID_3		0x4d0
#घोषणा OCOTP_ULP_UID_4		0x4e0

अटल पूर्णांक __init imx_soc_device_init(व्योम)
अणु
	काष्ठा soc_device_attribute *soc_dev_attr;
	स्थिर अक्षर *ocotp_compat = शून्य;
	काष्ठा soc_device *soc_dev;
	काष्ठा device_node *root;
	काष्ठा regmap *ocotp = शून्य;
	स्थिर अक्षर *soc_id;
	u64 soc_uid = 0;
	u32 val;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (of_machine_is_compatible("fsl,ls1021a"))
		वापस 0;

	soc_dev_attr = kzalloc(माप(*soc_dev_attr), GFP_KERNEL);
	अगर (!soc_dev_attr)
		वापस -ENOMEM;

	soc_dev_attr->family = "Freescale i.MX";

	root = of_find_node_by_path("/");
	ret = of_property_पढ़ो_string(root, "model", &soc_dev_attr->machine);
	of_node_put(root);
	अगर (ret)
		जाओ मुक्त_soc;

	चयन (__mxc_cpu_type) अणु
	हाल MXC_CPU_MX1:
		soc_id = "i.MX1";
		अवरोध;
	हाल MXC_CPU_MX21:
		soc_id = "i.MX21";
		अवरोध;
	हाल MXC_CPU_MX25:
		soc_id = "i.MX25";
		अवरोध;
	हाल MXC_CPU_MX27:
		soc_id = "i.MX27";
		अवरोध;
	हाल MXC_CPU_MX31:
		soc_id = "i.MX31";
		अवरोध;
	हाल MXC_CPU_MX35:
		soc_id = "i.MX35";
		अवरोध;
	हाल MXC_CPU_MX51:
		ocotp_compat = "fsl,imx51-iim";
		soc_id = "i.MX51";
		अवरोध;
	हाल MXC_CPU_MX53:
		ocotp_compat = "fsl,imx53-iim";
		soc_id = "i.MX53";
		अवरोध;
	हाल MXC_CPU_IMX6SL:
		ocotp_compat = "fsl,imx6sl-ocotp";
		soc_id = "i.MX6SL";
		अवरोध;
	हाल MXC_CPU_IMX6DL:
		ocotp_compat = "fsl,imx6q-ocotp";
		soc_id = "i.MX6DL";
		अवरोध;
	हाल MXC_CPU_IMX6SX:
		ocotp_compat = "fsl,imx6sx-ocotp";
		soc_id = "i.MX6SX";
		अवरोध;
	हाल MXC_CPU_IMX6Q:
		ocotp_compat = "fsl,imx6q-ocotp";
		soc_id = "i.MX6Q";
		अवरोध;
	हाल MXC_CPU_IMX6UL:
		ocotp_compat = "fsl,imx6ul-ocotp";
		soc_id = "i.MX6UL";
		अवरोध;
	हाल MXC_CPU_IMX6ULL:
		ocotp_compat = "fsl,imx6ull-ocotp";
		soc_id = "i.MX6ULL";
		अवरोध;
	हाल MXC_CPU_IMX6ULZ:
		ocotp_compat = "fsl,imx6ull-ocotp";
		soc_id = "i.MX6ULZ";
		अवरोध;
	हाल MXC_CPU_IMX6SLL:
		ocotp_compat = "fsl,imx6sll-ocotp";
		soc_id = "i.MX6SLL";
		अवरोध;
	हाल MXC_CPU_IMX7D:
		ocotp_compat = "fsl,imx7d-ocotp";
		soc_id = "i.MX7D";
		अवरोध;
	हाल MXC_CPU_IMX7ULP:
		ocotp_compat = "fsl,imx7ulp-ocotp";
		soc_id = "i.MX7ULP";
		अवरोध;
	हाल MXC_CPU_VF500:
		ocotp_compat = "fsl,vf610-ocotp";
		soc_id = "VF500";
		अवरोध;
	हाल MXC_CPU_VF510:
		ocotp_compat = "fsl,vf610-ocotp";
		soc_id = "VF510";
		अवरोध;
	हाल MXC_CPU_VF600:
		ocotp_compat = "fsl,vf610-ocotp";
		soc_id = "VF600";
		अवरोध;
	हाल MXC_CPU_VF610:
		ocotp_compat = "fsl,vf610-ocotp";
		soc_id = "VF610";
		अवरोध;
	शेष:
		soc_id = "Unknown";
	पूर्ण
	soc_dev_attr->soc_id = soc_id;

	अगर (ocotp_compat) अणु
		ocotp = syscon_regmap_lookup_by_compatible(ocotp_compat);
		अगर (IS_ERR(ocotp))
			pr_err("%s: failed to find %s regmap!\n", __func__, ocotp_compat);
	पूर्ण

	अगर (!IS_ERR_OR_शून्य(ocotp)) अणु
		अगर (__mxc_cpu_type == MXC_CPU_IMX7ULP) अणु
			regmap_पढ़ो(ocotp, OCOTP_ULP_UID_4, &val);
			soc_uid = val & 0xffff;
			regmap_पढ़ो(ocotp, OCOTP_ULP_UID_3, &val);
			soc_uid <<= 16;
			soc_uid |= val & 0xffff;
			regmap_पढ़ो(ocotp, OCOTP_ULP_UID_2, &val);
			soc_uid <<= 16;
			soc_uid |= val & 0xffff;
			regmap_पढ़ो(ocotp, OCOTP_ULP_UID_1, &val);
			soc_uid <<= 16;
			soc_uid |= val & 0xffff;
		पूर्ण अन्यथा अगर (__mxc_cpu_type == MXC_CPU_MX51 ||
			   __mxc_cpu_type == MXC_CPU_MX53) अणु
			क्रम (i=0; i < 8; i++) अणु
				regmap_पढ़ो(ocotp, IIM_UID + i*4, &val);
				soc_uid <<= 8;
				soc_uid |= (val & 0xff);
			पूर्ण
		पूर्ण अन्यथा अणु
			regmap_पढ़ो(ocotp, OCOTP_UID_H, &val);
			soc_uid = val;
			regmap_पढ़ो(ocotp, OCOTP_UID_L, &val);
			soc_uid <<= 32;
			soc_uid |= val;
		पूर्ण
	पूर्ण

	soc_dev_attr->revision = kaप्र_लिखो(GFP_KERNEL, "%d.%d",
					   (imx_get_soc_revision() >> 4) & 0xf,
					   imx_get_soc_revision() & 0xf);
	अगर (!soc_dev_attr->revision) अणु
		ret = -ENOMEM;
		जाओ मुक्त_soc;
	पूर्ण

	soc_dev_attr->serial_number = kaप्र_लिखो(GFP_KERNEL, "%016llX", soc_uid);
	अगर (!soc_dev_attr->serial_number) अणु
		ret = -ENOMEM;
		जाओ मुक्त_rev;
	पूर्ण

	soc_dev = soc_device_रेजिस्टर(soc_dev_attr);
	अगर (IS_ERR(soc_dev)) अणु
		ret = PTR_ERR(soc_dev);
		जाओ मुक्त_serial_number;
	पूर्ण

	वापस 0;

मुक्त_serial_number:
	kमुक्त(soc_dev_attr->serial_number);
मुक्त_rev:
	kमुक्त(soc_dev_attr->revision);
मुक्त_soc:
	kमुक्त(soc_dev_attr);
	वापस ret;
पूर्ण
device_initcall(imx_soc_device_init);
