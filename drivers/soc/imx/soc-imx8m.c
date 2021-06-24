<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 NXP.
 */

#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/sys_soc.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/arm-smccc.h>
#समावेश <linux/of.h>

#घोषणा REV_B1				0x21

#घोषणा IMX8MQ_SW_INFO_B1		0x40
#घोषणा IMX8MQ_SW_MAGIC_B1		0xff0055aa

#घोषणा IMX_SIP_GET_SOC_INFO		0xc2000006

#घोषणा OCOTP_UID_LOW			0x410
#घोषणा OCOTP_UID_HIGH			0x420

#घोषणा IMX8MP_OCOTP_UID_OFFSET		0x10

/* Same as ANADIG_DIGPROG_IMX7D */
#घोषणा ANADIG_DIGPROG_IMX8MM	0x800

काष्ठा imx8_soc_data अणु
	अक्षर *name;
	u32 (*soc_revision)(काष्ठा device *dev);
पूर्ण;

अटल u64 soc_uid;

#अगर_घोषित CONFIG_HAVE_ARM_SMCCC
अटल u32 imx8mq_soc_revision_from_atf(व्योम)
अणु
	काष्ठा arm_smccc_res res;

	arm_smccc_smc(IMX_SIP_GET_SOC_INFO, 0, 0, 0, 0, 0, 0, 0, &res);

	अगर (res.a0 == SMCCC_RET_NOT_SUPPORTED)
		वापस 0;
	अन्यथा
		वापस res.a0 & 0xff;
पूर्ण
#अन्यथा
अटल अंतरभूत u32 imx8mq_soc_revision_from_atf(व्योम) अणु वापस 0; पूर्ण;
#पूर्ण_अगर

अटल u32 __init imx8mq_soc_revision(काष्ठा device *dev)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *ocotp_base;
	u32 magic;
	u32 rev;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,imx8mq-ocotp");
	अगर (!np)
		वापस 0;

	ocotp_base = of_iomap(np, 0);
	WARN_ON(!ocotp_base);

	/*
	 * SOC revision on older imx8mq is not available in fuses so query
	 * the value from ATF instead.
	 */
	rev = imx8mq_soc_revision_from_atf();
	अगर (!rev) अणु
		magic = पढ़ोl_relaxed(ocotp_base + IMX8MQ_SW_INFO_B1);
		अगर (magic == IMX8MQ_SW_MAGIC_B1)
			rev = REV_B1;
	पूर्ण

	अगर (dev) अणु
		पूर्णांक ret;

		ret = nvmem_cell_पढ़ो_u64(dev, "soc_unique_id", &soc_uid);
		अगर (ret) अणु
			iounmap(ocotp_base);
			of_node_put(np);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		soc_uid = पढ़ोl_relaxed(ocotp_base + OCOTP_UID_HIGH);
		soc_uid <<= 32;
		soc_uid |= पढ़ोl_relaxed(ocotp_base + OCOTP_UID_LOW);
	पूर्ण

	iounmap(ocotp_base);
	of_node_put(np);

	वापस rev;
पूर्ण

अटल व्योम __init imx8mm_soc_uid(व्योम)
अणु
	व्योम __iomem *ocotp_base;
	काष्ठा device_node *np;
	u32 offset = of_machine_is_compatible("fsl,imx8mp") ?
		     IMX8MP_OCOTP_UID_OFFSET : 0;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,imx8mm-ocotp");
	अगर (!np)
		वापस;

	ocotp_base = of_iomap(np, 0);
	WARN_ON(!ocotp_base);

	soc_uid = पढ़ोl_relaxed(ocotp_base + OCOTP_UID_HIGH + offset);
	soc_uid <<= 32;
	soc_uid |= पढ़ोl_relaxed(ocotp_base + OCOTP_UID_LOW + offset);

	iounmap(ocotp_base);
	of_node_put(np);
पूर्ण

अटल u32 __init imx8mm_soc_revision(काष्ठा device *dev)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *anatop_base;
	u32 rev;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,imx8mm-anatop");
	अगर (!np)
		वापस 0;

	anatop_base = of_iomap(np, 0);
	WARN_ON(!anatop_base);

	rev = पढ़ोl_relaxed(anatop_base + ANADIG_DIGPROG_IMX8MM);

	iounmap(anatop_base);
	of_node_put(np);

	अगर (dev) अणु
		पूर्णांक ret;

		ret = nvmem_cell_पढ़ो_u64(dev, "soc_unique_id", &soc_uid);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		imx8mm_soc_uid();
	पूर्ण

	वापस rev;
पूर्ण

अटल स्थिर काष्ठा imx8_soc_data imx8mq_soc_data = अणु
	.name = "i.MX8MQ",
	.soc_revision = imx8mq_soc_revision,
पूर्ण;

अटल स्थिर काष्ठा imx8_soc_data imx8mm_soc_data = अणु
	.name = "i.MX8MM",
	.soc_revision = imx8mm_soc_revision,
पूर्ण;

अटल स्थिर काष्ठा imx8_soc_data imx8mn_soc_data = अणु
	.name = "i.MX8MN",
	.soc_revision = imx8mm_soc_revision,
पूर्ण;

अटल स्थिर काष्ठा imx8_soc_data imx8mp_soc_data = अणु
	.name = "i.MX8MP",
	.soc_revision = imx8mm_soc_revision,
पूर्ण;

अटल __maybe_unused स्थिर काष्ठा of_device_id imx8_machine_match[] = अणु
	अणु .compatible = "fsl,imx8mq", .data = &imx8mq_soc_data, पूर्ण,
	अणु .compatible = "fsl,imx8mm", .data = &imx8mm_soc_data, पूर्ण,
	अणु .compatible = "fsl,imx8mn", .data = &imx8mn_soc_data, पूर्ण,
	अणु .compatible = "fsl,imx8mp", .data = &imx8mp_soc_data, पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल __maybe_unused स्थिर काष्ठा of_device_id imx8_soc_match[] = अणु
	अणु .compatible = "fsl,imx8mq-soc", .data = &imx8mq_soc_data, पूर्ण,
	अणु .compatible = "fsl,imx8mm-soc", .data = &imx8mm_soc_data, पूर्ण,
	अणु .compatible = "fsl,imx8mn-soc", .data = &imx8mn_soc_data, पूर्ण,
	अणु .compatible = "fsl,imx8mp-soc", .data = &imx8mp_soc_data, पूर्ण,
	अणु पूर्ण
पूर्ण;

#घोषणा imx8_revision(soc_rev) \
	soc_rev ? \
	kaप्र_लिखो(GFP_KERNEL, "%d.%d", (soc_rev >> 4) & 0xf,  soc_rev & 0xf) : \
	"unknown"

अटल पूर्णांक imx8_soc_info(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा soc_device_attribute *soc_dev_attr;
	काष्ठा soc_device *soc_dev;
	स्थिर काष्ठा of_device_id *id;
	u32 soc_rev = 0;
	स्थिर काष्ठा imx8_soc_data *data;
	पूर्णांक ret;

	soc_dev_attr = kzalloc(माप(*soc_dev_attr), GFP_KERNEL);
	अगर (!soc_dev_attr)
		वापस -ENOMEM;

	soc_dev_attr->family = "Freescale i.MX";

	ret = of_property_पढ़ो_string(of_root, "model", &soc_dev_attr->machine);
	अगर (ret)
		जाओ मुक्त_soc;

	अगर (pdev)
		id = of_match_node(imx8_soc_match, pdev->dev.of_node);
	अन्यथा
		id = of_match_node(imx8_machine_match, of_root);
	अगर (!id) अणु
		ret = -ENODEV;
		जाओ मुक्त_soc;
	पूर्ण

	data = id->data;
	अगर (data) अणु
		soc_dev_attr->soc_id = data->name;
		अगर (data->soc_revision) अणु
			अगर (pdev) अणु
				soc_rev = data->soc_revision(&pdev->dev);
				ret = soc_rev;
				अगर (ret < 0)
					जाओ मुक्त_soc;
			पूर्ण अन्यथा अणु
				soc_rev = data->soc_revision(शून्य);
			पूर्ण
		पूर्ण
	पूर्ण

	soc_dev_attr->revision = imx8_revision(soc_rev);
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

	pr_info("SoC: %s revision %s\n", soc_dev_attr->soc_id,
		soc_dev_attr->revision);

	अगर (IS_ENABLED(CONFIG_ARM_IMX_CPUFREQ_DT))
		platक्रमm_device_रेजिस्टर_simple("imx-cpufreq-dt", -1, शून्य, 0);

	वापस 0;

मुक्त_serial_number:
	kमुक्त(soc_dev_attr->serial_number);
मुक्त_rev:
	अगर (म_भेद(soc_dev_attr->revision, "unknown"))
		kमुक्त(soc_dev_attr->revision);
मुक्त_soc:
	kमुक्त(soc_dev_attr);
	वापस ret;
पूर्ण

/* Retain device_initcall is क्रम backward compatibility with DTS. */
अटल पूर्णांक __init imx8_soc_init(व्योम)
अणु
	अगर (of_find_matching_node_and_match(शून्य, imx8_soc_match, शून्य))
		वापस 0;

	वापस imx8_soc_info(शून्य);
पूर्ण
device_initcall(imx8_soc_init);

अटल काष्ठा platक्रमm_driver imx8_soc_info_driver = अणु
	.probe = imx8_soc_info,
	.driver = अणु
		.name = "imx8_soc_info",
		.of_match_table = imx8_soc_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(imx8_soc_info_driver);
MODULE_LICENSE("GPL v2");
