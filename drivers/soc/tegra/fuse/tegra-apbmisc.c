<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/पन.स>

#समावेश <soc/tegra/fuse.h>
#समावेश <soc/tegra/common.h>

#समावेश "fuse.h"

#घोषणा FUSE_SKU_INFO	0x10

#घोषणा PMC_STRAPPING_OPT_A_RAM_CODE_SHIFT	4
#घोषणा PMC_STRAPPING_OPT_A_RAM_CODE_MASK_LONG	\
	(0xf << PMC_STRAPPING_OPT_A_RAM_CODE_SHIFT)
#घोषणा PMC_STRAPPING_OPT_A_RAM_CODE_MASK_SHORT	\
	(0x3 << PMC_STRAPPING_OPT_A_RAM_CODE_SHIFT)

अटल bool दीर्घ_ram_code;
अटल u32 strapping;
अटल u32 chipid;

u32 tegra_पढ़ो_chipid(व्योम)
अणु
	WARN(!chipid, "Tegra APB MISC not yet available\n");

	वापस chipid;
पूर्ण

u8 tegra_get_chip_id(व्योम)
अणु
	वापस (tegra_पढ़ो_chipid() >> 8) & 0xff;
पूर्ण

u8 tegra_get_major_rev(व्योम)
अणु
	वापस (tegra_पढ़ो_chipid() >> 4) & 0xf;
पूर्ण

u8 tegra_get_minor_rev(व्योम)
अणु
	वापस (tegra_पढ़ो_chipid() >> 16) & 0xf;
पूर्ण

u8 tegra_get_platक्रमm(व्योम)
अणु
	वापस (tegra_पढ़ो_chipid() >> 20) & 0xf;
पूर्ण

bool tegra_is_silicon(व्योम)
अणु
	चयन (tegra_get_chip_id()) अणु
	हाल TEGRA194:
	हाल TEGRA234:
		अगर (tegra_get_platक्रमm() == 0)
			वापस true;

		वापस false;
	पूर्ण

	/*
	 * Chips prior to Tegra194 have a dअगरferent way of determining whether
	 * they are silicon or not. Since we never supported simulation on the
	 * older Tegra chips, करोn't bother extracting the inक्रमmation and just
	 * report that we're running on silicon.
	 */
	वापस true;
पूर्ण

u32 tegra_पढ़ो_straps(व्योम)
अणु
	WARN(!chipid, "Tegra ABP MISC not yet available\n");

	वापस strapping;
पूर्ण

u32 tegra_पढ़ो_ram_code(व्योम)
अणु
	u32 straps = tegra_पढ़ो_straps();

	अगर (दीर्घ_ram_code)
		straps &= PMC_STRAPPING_OPT_A_RAM_CODE_MASK_LONG;
	अन्यथा
		straps &= PMC_STRAPPING_OPT_A_RAM_CODE_MASK_SHORT;

	वापस straps >> PMC_STRAPPING_OPT_A_RAM_CODE_SHIFT;
पूर्ण
EXPORT_SYMBOL_GPL(tegra_पढ़ो_ram_code);

अटल स्थिर काष्ठा of_device_id apbmisc_match[] __initस्थिर = अणु
	अणु .compatible = "nvidia,tegra20-apbmisc", पूर्ण,
	अणु .compatible = "nvidia,tegra186-misc", पूर्ण,
	अणु .compatible = "nvidia,tegra194-misc", पूर्ण,
	अणु .compatible = "nvidia,tegra234-misc", पूर्ण,
	अणुपूर्ण,
पूर्ण;

व्योम __init tegra_init_revision(व्योम)
अणु
	u8 chip_id, minor_rev;

	chip_id = tegra_get_chip_id();
	minor_rev = tegra_get_minor_rev();

	चयन (minor_rev) अणु
	हाल 1:
		tegra_sku_info.revision = TEGRA_REVISION_A01;
		अवरोध;
	हाल 2:
		tegra_sku_info.revision = TEGRA_REVISION_A02;
		अवरोध;
	हाल 3:
		अगर (chip_id == TEGRA20 && (tegra_fuse_पढ़ो_spare(18) ||
					   tegra_fuse_पढ़ो_spare(19)))
			tegra_sku_info.revision = TEGRA_REVISION_A03p;
		अन्यथा
			tegra_sku_info.revision = TEGRA_REVISION_A03;
		अवरोध;
	हाल 4:
		tegra_sku_info.revision = TEGRA_REVISION_A04;
		अवरोध;
	शेष:
		tegra_sku_info.revision = TEGRA_REVISION_UNKNOWN;
	पूर्ण

	tegra_sku_info.sku_id = tegra_fuse_पढ़ो_early(FUSE_SKU_INFO);
पूर्ण

व्योम __init tegra_init_apbmisc(व्योम)
अणु
	व्योम __iomem *apbmisc_base, *strapping_base;
	काष्ठा resource apbmisc, straps;
	काष्ठा device_node *np;

	np = of_find_matching_node(शून्य, apbmisc_match);
	अगर (!np) अणु
		/*
		 * Fall back to legacy initialization क्रम 32-bit ARM only. All
		 * 64-bit ARM device tree files क्रम Tegra are required to have
		 * an APBMISC node.
		 *
		 * This is क्रम backwards-compatibility with old device trees
		 * that didn't contain an APBMISC node.
		 */
		अगर (IS_ENABLED(CONFIG_ARM) && soc_is_tegra()) अणु
			/* APBMISC रेजिस्टरs (chip revision, ...) */
			apbmisc.start = 0x70000800;
			apbmisc.end = 0x70000863;
			apbmisc.flags = IORESOURCE_MEM;

			/* strapping options */
			अगर (of_machine_is_compatible("nvidia,tegra124")) अणु
				straps.start = 0x7000e864;
				straps.end = 0x7000e867;
			पूर्ण अन्यथा अणु
				straps.start = 0x70000008;
				straps.end = 0x7000000b;
			पूर्ण

			straps.flags = IORESOURCE_MEM;

			pr_warn("Using APBMISC region %pR\n", &apbmisc);
			pr_warn("Using strapping options registers %pR\n",
				&straps);
		पूर्ण अन्यथा अणु
			/*
			 * At this poपूर्णांक we're not running on Tegra, so play
			 * nice with multi-platक्रमm kernels.
			 */
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Extract inक्रमmation from the device tree अगर we've found a
		 * matching node.
		 */
		अगर (of_address_to_resource(np, 0, &apbmisc) < 0) अणु
			pr_err("failed to get APBMISC registers\n");
			वापस;
		पूर्ण

		अगर (of_address_to_resource(np, 1, &straps) < 0) अणु
			pr_err("failed to get strapping options registers\n");
			वापस;
		पूर्ण
	पूर्ण

	apbmisc_base = ioremap(apbmisc.start, resource_size(&apbmisc));
	अगर (!apbmisc_base) अणु
		pr_err("failed to map APBMISC registers\n");
	पूर्ण अन्यथा अणु
		chipid = पढ़ोl_relaxed(apbmisc_base + 4);
		iounmap(apbmisc_base);
	पूर्ण

	strapping_base = ioremap(straps.start, resource_size(&straps));
	अगर (!strapping_base) अणु
		pr_err("failed to map strapping options registers\n");
	पूर्ण अन्यथा अणु
		strapping = पढ़ोl_relaxed(strapping_base);
		iounmap(strapping_base);
	पूर्ण

	दीर्घ_ram_code = of_property_पढ़ो_bool(np, "nvidia,long-ram-code");
पूर्ण
