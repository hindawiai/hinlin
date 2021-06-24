<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Aपंचांगel
 *
 * Alexandre Belloni <alexandre.belloni@मुक्त-electrons.com
 * Boris Brezillon <boris.brezillon@मुक्त-electrons.com
 */

#घोषणा pr_fmt(fmt)	"AT91: " fmt

#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>
#समावेश <linux/sys_soc.h>

#समावेश "soc.h"

#घोषणा AT91_DBGU_CIDR			0x40
#घोषणा AT91_DBGU_EXID			0x44
#घोषणा AT91_CHIPID_CIDR		0x00
#घोषणा AT91_CHIPID_EXID		0x04
#घोषणा AT91_CIDR_VERSION(x, m)		((x) & (m))
#घोषणा AT91_CIDR_VERSION_MASK		GENMASK(4, 0)
#घोषणा AT91_CIDR_VERSION_MASK_SAMA7G5	GENMASK(3, 0)
#घोषणा AT91_CIDR_EXT			BIT(31)
#घोषणा AT91_CIDR_MATCH_MASK		GENMASK(30, 5)
#घोषणा AT91_CIDR_MASK_SAMA7G5		GENMASK(27, 5)

अटल स्थिर काष्ठा at91_soc socs[] __initस्थिर = अणु
#अगर_घोषित CONFIG_SOC_AT91RM9200
	AT91_SOC(AT91RM9200_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, 0, "at91rm9200 BGA", "at91rm9200"),
#पूर्ण_अगर
#अगर_घोषित CONFIG_SOC_AT91SAM9
	AT91_SOC(AT91SAM9260_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, 0, "at91sam9260", शून्य),
	AT91_SOC(AT91SAM9261_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, 0, "at91sam9261", शून्य),
	AT91_SOC(AT91SAM9263_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, 0, "at91sam9263", शून्य),
	AT91_SOC(AT91SAM9G20_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, 0, "at91sam9g20", शून्य),
	AT91_SOC(AT91SAM9RL64_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, 0, "at91sam9rl64", शून्य),
	AT91_SOC(AT91SAM9G45_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, AT91SAM9M11_EXID_MATCH,
		 "at91sam9m11", "at91sam9g45"),
	AT91_SOC(AT91SAM9G45_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, AT91SAM9M10_EXID_MATCH,
		 "at91sam9m10", "at91sam9g45"),
	AT91_SOC(AT91SAM9G45_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, AT91SAM9G46_EXID_MATCH,
		 "at91sam9g46", "at91sam9g45"),
	AT91_SOC(AT91SAM9G45_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, AT91SAM9G45_EXID_MATCH,
		 "at91sam9g45", "at91sam9g45"),
	AT91_SOC(AT91SAM9X5_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, AT91SAM9G15_EXID_MATCH,
		 "at91sam9g15", "at91sam9x5"),
	AT91_SOC(AT91SAM9X5_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, AT91SAM9G35_EXID_MATCH,
		 "at91sam9g35", "at91sam9x5"),
	AT91_SOC(AT91SAM9X5_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, AT91SAM9X35_EXID_MATCH,
		 "at91sam9x35", "at91sam9x5"),
	AT91_SOC(AT91SAM9X5_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, AT91SAM9G25_EXID_MATCH,
		 "at91sam9g25", "at91sam9x5"),
	AT91_SOC(AT91SAM9X5_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, AT91SAM9X25_EXID_MATCH,
		 "at91sam9x25", "at91sam9x5"),
	AT91_SOC(AT91SAM9N12_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, AT91SAM9CN12_EXID_MATCH,
		 "at91sam9cn12", "at91sam9n12"),
	AT91_SOC(AT91SAM9N12_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, AT91SAM9N12_EXID_MATCH,
		 "at91sam9n12", "at91sam9n12"),
	AT91_SOC(AT91SAM9N12_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, AT91SAM9CN11_EXID_MATCH,
		 "at91sam9cn11", "at91sam9n12"),
	AT91_SOC(AT91SAM9XE128_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, 0, "at91sam9xe128", "at91sam9xe128"),
	AT91_SOC(AT91SAM9XE256_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, 0, "at91sam9xe256", "at91sam9xe256"),
	AT91_SOC(AT91SAM9XE512_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, 0, "at91sam9xe512", "at91sam9xe512"),
#पूर्ण_अगर
#अगर_घोषित CONFIG_SOC_SAM9X60
	AT91_SOC(SAM9X60_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAM9X60_EXID_MATCH,
		 "sam9x60", "sam9x60"),
	AT91_SOC(SAM9X60_CIDR_MATCH, SAM9X60_D5M_EXID_MATCH,
		 AT91_CIDR_VERSION_MASK, SAM9X60_EXID_MATCH,
		 "sam9x60 64MiB DDR2 SiP", "sam9x60"),
	AT91_SOC(SAM9X60_CIDR_MATCH, SAM9X60_D1G_EXID_MATCH,
		 AT91_CIDR_VERSION_MASK, SAM9X60_EXID_MATCH,
		 "sam9x60 128MiB DDR2 SiP", "sam9x60"),
	AT91_SOC(SAM9X60_CIDR_MATCH, SAM9X60_D6K_EXID_MATCH,
		 AT91_CIDR_VERSION_MASK, SAM9X60_EXID_MATCH,
		 "sam9x60 8MiB SDRAM SiP", "sam9x60"),
#पूर्ण_अगर
#अगर_घोषित CONFIG_SOC_SAMA5
	AT91_SOC(SAMA5D2_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D21CU_EXID_MATCH,
		 "sama5d21", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D22CU_EXID_MATCH,
		 "sama5d22", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D225C_D1M_EXID_MATCH,
		 "sama5d225c 16MiB SiP", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D23CU_EXID_MATCH,
		 "sama5d23", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D24CX_EXID_MATCH,
		 "sama5d24", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D24CU_EXID_MATCH,
		 "sama5d24", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D26CU_EXID_MATCH,
		 "sama5d26", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D27CU_EXID_MATCH,
		 "sama5d27", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D27CN_EXID_MATCH,
		 "sama5d27", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D27C_D1G_EXID_MATCH,
		 "sama5d27c 128MiB SiP", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D27C_D5M_EXID_MATCH,
		 "sama5d27c 64MiB SiP", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D27C_LD1G_EXID_MATCH,
		 "sama5d27c 128MiB LPDDR2 SiP", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D27C_LD2G_EXID_MATCH,
		 "sama5d27c 256MiB LPDDR2 SiP", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D28CU_EXID_MATCH,
		 "sama5d28", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D28CN_EXID_MATCH,
		 "sama5d28", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D28C_D1G_EXID_MATCH,
		 "sama5d28c 128MiB SiP", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D28C_LD1G_EXID_MATCH,
		 "sama5d28c 128MiB LPDDR2 SiP", "sama5d2"),
	AT91_SOC(SAMA5D2_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D28C_LD2G_EXID_MATCH,
		 "sama5d28c 256MiB LPDDR2 SiP", "sama5d2"),
	AT91_SOC(SAMA5D3_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D31_EXID_MATCH,
		 "sama5d31", "sama5d3"),
	AT91_SOC(SAMA5D3_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D33_EXID_MATCH,
		 "sama5d33", "sama5d3"),
	AT91_SOC(SAMA5D3_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D34_EXID_MATCH,
		 "sama5d34", "sama5d3"),
	AT91_SOC(SAMA5D3_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D35_EXID_MATCH,
		 "sama5d35", "sama5d3"),
	AT91_SOC(SAMA5D3_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D36_EXID_MATCH,
		 "sama5d36", "sama5d3"),
	AT91_SOC(SAMA5D4_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D41_EXID_MATCH,
		 "sama5d41", "sama5d4"),
	AT91_SOC(SAMA5D4_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D42_EXID_MATCH,
		 "sama5d42", "sama5d4"),
	AT91_SOC(SAMA5D4_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D43_EXID_MATCH,
		 "sama5d43", "sama5d4"),
	AT91_SOC(SAMA5D4_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMA5D44_EXID_MATCH,
		 "sama5d44", "sama5d4"),
#पूर्ण_अगर
#अगर_घोषित CONFIG_SOC_SAMV7
	AT91_SOC(SAME70Q21_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAME70Q21_EXID_MATCH,
		 "same70q21", "same7"),
	AT91_SOC(SAME70Q20_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAME70Q20_EXID_MATCH,
		 "same70q20", "same7"),
	AT91_SOC(SAME70Q19_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAME70Q19_EXID_MATCH,
		 "same70q19", "same7"),
	AT91_SOC(SAMS70Q21_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMS70Q21_EXID_MATCH,
		 "sams70q21", "sams7"),
	AT91_SOC(SAMS70Q20_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMS70Q20_EXID_MATCH,
		 "sams70q20", "sams7"),
	AT91_SOC(SAMS70Q19_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMS70Q19_EXID_MATCH,
		 "sams70q19", "sams7"),
	AT91_SOC(SAMV71Q21_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMV71Q21_EXID_MATCH,
		 "samv71q21", "samv7"),
	AT91_SOC(SAMV71Q20_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMV71Q20_EXID_MATCH,
		 "samv71q20", "samv7"),
	AT91_SOC(SAMV71Q19_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMV71Q19_EXID_MATCH,
		 "samv71q19", "samv7"),
	AT91_SOC(SAMV70Q20_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMV70Q20_EXID_MATCH,
		 "samv70q20", "samv7"),
	AT91_SOC(SAMV70Q19_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK, SAMV70Q19_EXID_MATCH,
		 "samv70q19", "samv7"),
#पूर्ण_अगर
#अगर_घोषित CONFIG_SOC_SAMA7
	AT91_SOC(SAMA7G5_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK_SAMA7G5, SAMA7G51_EXID_MATCH,
		 "sama7g51", "sama7g5"),
	AT91_SOC(SAMA7G5_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK_SAMA7G5, SAMA7G52_EXID_MATCH,
		 "sama7g52", "sama7g5"),
	AT91_SOC(SAMA7G5_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK_SAMA7G5, SAMA7G53_EXID_MATCH,
		 "sama7g53", "sama7g5"),
	AT91_SOC(SAMA7G5_CIDR_MATCH, AT91_CIDR_MATCH_MASK,
		 AT91_CIDR_VERSION_MASK_SAMA7G5, SAMA7G54_EXID_MATCH,
		 "sama7g54", "sama7g5"),
#पूर्ण_अगर
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल पूर्णांक __init at91_get_cidr_exid_from_dbgu(u32 *cidr, u32 *exid)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *regs;

	np = of_find_compatible_node(शून्य, शून्य, "atmel,at91rm9200-dbgu");
	अगर (!np)
		np = of_find_compatible_node(शून्य, शून्य,
					     "atmel,at91sam9260-dbgu");
	अगर (!np)
		वापस -ENODEV;

	regs = of_iomap(np, 0);
	of_node_put(np);

	अगर (!regs) अणु
		pr_warn("Could not map DBGU iomem range");
		वापस -ENXIO;
	पूर्ण

	*cidr = पढ़ोl(regs + AT91_DBGU_CIDR);
	*exid = पढ़ोl(regs + AT91_DBGU_EXID);

	iounmap(regs);

	वापस 0;
पूर्ण

अटल पूर्णांक __init at91_get_cidr_exid_from_chipid(u32 *cidr, u32 *exid)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *regs;
	अटल स्थिर काष्ठा of_device_id chipids[] = अणु
		अणु .compatible = "atmel,sama5d2-chipid" पूर्ण,
		अणु .compatible = "microchip,sama7g5-chipid" पूर्ण,
		अणु पूर्ण,
	पूर्ण;

	np = of_find_matching_node(शून्य, chipids);
	अगर (!np)
		वापस -ENODEV;

	regs = of_iomap(np, 0);
	of_node_put(np);

	अगर (!regs) अणु
		pr_warn("Could not map DBGU iomem range");
		वापस -ENXIO;
	पूर्ण

	*cidr = पढ़ोl(regs + AT91_CHIPID_CIDR);
	*exid = पढ़ोl(regs + AT91_CHIPID_EXID);

	iounmap(regs);

	वापस 0;
पूर्ण

काष्ठा soc_device * __init at91_soc_init(स्थिर काष्ठा at91_soc *socs)
अणु
	काष्ठा soc_device_attribute *soc_dev_attr;
	स्थिर काष्ठा at91_soc *soc;
	काष्ठा soc_device *soc_dev;
	u32 cidr, exid;
	पूर्णांक ret;

	/*
	 * With SAMA5D2 and later SoCs, CIDR and EXID रेजिस्टरs are no more
	 * in the dbgu device but in the chipid device whose purpose is only
	 * to expose these two रेजिस्टरs.
	 */
	ret = at91_get_cidr_exid_from_dbgu(&cidr, &exid);
	अगर (ret)
		ret = at91_get_cidr_exid_from_chipid(&cidr, &exid);
	अगर (ret) अणु
		अगर (ret == -ENODEV)
			pr_warn("Could not find identification node");
		वापस शून्य;
	पूर्ण

	क्रम (soc = socs; soc->name; soc++) अणु
		अगर (soc->cidr_match != (cidr & soc->cidr_mask))
			जारी;

		अगर (!(cidr & AT91_CIDR_EXT) || soc->exid_match == exid)
			अवरोध;
	पूर्ण

	अगर (!soc->name) अणु
		pr_warn("Could not find matching SoC description\n");
		वापस शून्य;
	पूर्ण

	soc_dev_attr = kzalloc(माप(*soc_dev_attr), GFP_KERNEL);
	अगर (!soc_dev_attr)
		वापस शून्य;

	soc_dev_attr->family = soc->family;
	soc_dev_attr->soc_id = soc->name;
	soc_dev_attr->revision = kaप्र_लिखो(GFP_KERNEL, "%X",
					   AT91_CIDR_VERSION(cidr, soc->version_mask));
	soc_dev = soc_device_रेजिस्टर(soc_dev_attr);
	अगर (IS_ERR(soc_dev)) अणु
		kमुक्त(soc_dev_attr->revision);
		kमुक्त(soc_dev_attr);
		pr_warn("Could not register SoC device\n");
		वापस शून्य;
	पूर्ण

	अगर (soc->family)
		pr_info("Detected SoC family: %s\n", soc->family);
	pr_info("Detected SoC: %s, revision %X\n", soc->name,
		AT91_CIDR_VERSION(cidr, soc->version_mask));

	वापस soc_dev;
पूर्ण

अटल स्थिर काष्ठा of_device_id at91_soc_allowed_list[] __initस्थिर = अणु
	अणु .compatible = "atmel,at91rm9200", पूर्ण,
	अणु .compatible = "atmel,at91sam9", पूर्ण,
	अणु .compatible = "atmel,sama5", पूर्ण,
	अणु .compatible = "atmel,samv7", पूर्ण,
	अणु .compatible = "microchip,sama7g5", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक __init aपंचांगel_soc_device_init(व्योम)
अणु
	काष्ठा device_node *np = of_find_node_by_path("/");

	अगर (!of_match_node(at91_soc_allowed_list, np))
		वापस 0;

	at91_soc_init(socs);

	वापस 0;
पूर्ण
subsys_initcall(aपंचांगel_soc_device_init);
