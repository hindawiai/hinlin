<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas SoC Identअगरication
 *
 * Copyright (C) 2014-2016 Glider bvba
 */

#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/sys_soc.h>


काष्ठा renesas_family अणु
	स्थिर अक्षर name[16];
	u32 reg;			/* CCCR or PRR, अगर not in DT */
पूर्ण;

अटल स्थिर काष्ठा renesas_family fam_rcar_gen1 __initस्थिर __maybe_unused = अणु
	.name	= "R-Car Gen1",
	.reg	= 0xff000044,		/* PRR (Product Register) */
पूर्ण;

अटल स्थिर काष्ठा renesas_family fam_rcar_gen2 __initस्थिर __maybe_unused = अणु
	.name	= "R-Car Gen2",
	.reg	= 0xff000044,		/* PRR (Product Register) */
पूर्ण;

अटल स्थिर काष्ठा renesas_family fam_rcar_gen3 __initस्थिर __maybe_unused = अणु
	.name	= "R-Car Gen3",
	.reg	= 0xfff00044,		/* PRR (Product Register) */
पूर्ण;

अटल स्थिर काष्ठा renesas_family fam_rmobile __initस्थिर __maybe_unused = अणु
	.name	= "R-Mobile",
	.reg	= 0xe600101c,		/* CCCR (Common Chip Code Register) */
पूर्ण;

अटल स्थिर काष्ठा renesas_family fam_rza1 __initस्थिर __maybe_unused = अणु
	.name	= "RZ/A1",
पूर्ण;

अटल स्थिर काष्ठा renesas_family fam_rza2 __initस्थिर __maybe_unused = अणु
	.name	= "RZ/A2",
पूर्ण;

अटल स्थिर काष्ठा renesas_family fam_rzg1 __initस्थिर __maybe_unused = अणु
	.name	= "RZ/G1",
	.reg	= 0xff000044,		/* PRR (Product Register) */
पूर्ण;

अटल स्थिर काष्ठा renesas_family fam_rzg2 __initस्थिर __maybe_unused = अणु
	.name	= "RZ/G2",
	.reg	= 0xfff00044,		/* PRR (Product Register) */
पूर्ण;

अटल स्थिर काष्ठा renesas_family fam_shmobile __initस्थिर __maybe_unused = अणु
	.name	= "SH-Mobile",
	.reg	= 0xe600101c,		/* CCCR (Common Chip Code Register) */
पूर्ण;


काष्ठा renesas_soc अणु
	स्थिर काष्ठा renesas_family *family;
	u8 id;
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rz_a1h __initस्थिर __maybe_unused = अणु
	.family	= &fam_rza1,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rz_a2m __initस्थिर __maybe_unused = अणु
	.family	= &fam_rza2,
	.id	= 0x3b,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rmobile_ape6 __initस्थिर __maybe_unused = अणु
	.family	= &fam_rmobile,
	.id	= 0x3f,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rmobile_a1 __initस्थिर __maybe_unused = अणु
	.family	= &fam_rmobile,
	.id	= 0x40,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rz_g1h __initस्थिर __maybe_unused = अणु
	.family	= &fam_rzg1,
	.id	= 0x45,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rz_g1m __initस्थिर __maybe_unused = अणु
	.family	= &fam_rzg1,
	.id	= 0x47,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rz_g1n __initस्थिर __maybe_unused = अणु
	.family	= &fam_rzg1,
	.id	= 0x4b,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rz_g1e __initस्थिर __maybe_unused = अणु
	.family	= &fam_rzg1,
	.id	= 0x4c,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rz_g1c __initस्थिर __maybe_unused = अणु
	.family	= &fam_rzg1,
	.id	= 0x53,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rz_g2m __initस्थिर __maybe_unused = अणु
	.family	= &fam_rzg2,
	.id	= 0x52,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rz_g2n __initस्थिर __maybe_unused = अणु
	.family = &fam_rzg2,
	.id     = 0x55,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rz_g2e __initस्थिर __maybe_unused = अणु
	.family	= &fam_rzg2,
	.id	= 0x57,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rz_g2h __initस्थिर __maybe_unused = अणु
	.family	= &fam_rzg2,
	.id	= 0x4f,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rcar_m1a __initस्थिर __maybe_unused = अणु
	.family	= &fam_rcar_gen1,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rcar_h1 __initस्थिर __maybe_unused = अणु
	.family	= &fam_rcar_gen1,
	.id	= 0x3b,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rcar_h2 __initस्थिर __maybe_unused = अणु
	.family	= &fam_rcar_gen2,
	.id	= 0x45,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rcar_m2_w __initस्थिर __maybe_unused = अणु
	.family	= &fam_rcar_gen2,
	.id	= 0x47,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rcar_v2h __initस्थिर __maybe_unused = अणु
	.family	= &fam_rcar_gen2,
	.id	= 0x4a,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rcar_m2_n __initस्थिर __maybe_unused = अणु
	.family	= &fam_rcar_gen2,
	.id	= 0x4b,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rcar_e2 __initस्थिर __maybe_unused = अणु
	.family	= &fam_rcar_gen2,
	.id	= 0x4c,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rcar_h3 __initस्थिर __maybe_unused = अणु
	.family	= &fam_rcar_gen3,
	.id	= 0x4f,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rcar_m3_w __initस्थिर __maybe_unused = अणु
	.family	= &fam_rcar_gen3,
	.id	= 0x52,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rcar_m3_n __initस्थिर __maybe_unused = अणु
	.family = &fam_rcar_gen3,
	.id     = 0x55,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rcar_v3m __initस्थिर __maybe_unused = अणु
	.family	= &fam_rcar_gen3,
	.id	= 0x54,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rcar_v3h __initस्थिर __maybe_unused = अणु
	.family	= &fam_rcar_gen3,
	.id	= 0x56,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rcar_e3 __initस्थिर __maybe_unused = अणु
	.family	= &fam_rcar_gen3,
	.id	= 0x57,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rcar_d3 __initस्थिर __maybe_unused = अणु
	.family	= &fam_rcar_gen3,
	.id	= 0x58,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_rcar_v3u __initस्थिर __maybe_unused = अणु
	.family	= &fam_rcar_gen3,
	.id	= 0x59,
पूर्ण;

अटल स्थिर काष्ठा renesas_soc soc_shmobile_ag5 __initस्थिर __maybe_unused = अणु
	.family	= &fam_shmobile,
	.id	= 0x37,
पूर्ण;


अटल स्थिर काष्ठा of_device_id renesas_socs[] __initस्थिर = अणु
#अगर_घोषित CONFIG_ARCH_R7S72100
	अणु .compatible = "renesas,r7s72100",	.data = &soc_rz_a1h पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R7S9210
	अणु .compatible = "renesas,r7s9210",	.data = &soc_rz_a2m पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A73A4
	अणु .compatible = "renesas,r8a73a4",	.data = &soc_rmobile_ape6 पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A7740
	अणु .compatible = "renesas,r8a7740",	.data = &soc_rmobile_a1 पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A7742
	अणु .compatible = "renesas,r8a7742",	.data = &soc_rz_g1h पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A7743
	अणु .compatible = "renesas,r8a7743",	.data = &soc_rz_g1m पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A7744
	अणु .compatible = "renesas,r8a7744",	.data = &soc_rz_g1n पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A7745
	अणु .compatible = "renesas,r8a7745",	.data = &soc_rz_g1e पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A77470
	अणु .compatible = "renesas,r8a77470",	.data = &soc_rz_g1c पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A774A1
	अणु .compatible = "renesas,r8a774a1",	.data = &soc_rz_g2m पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A774B1
	अणु .compatible = "renesas,r8a774b1",	.data = &soc_rz_g2n पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A774C0
	अणु .compatible = "renesas,r8a774c0",	.data = &soc_rz_g2e पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A774E1
	अणु .compatible = "renesas,r8a774e1",	.data = &soc_rz_g2h पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A7778
	अणु .compatible = "renesas,r8a7778",	.data = &soc_rcar_m1a पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A7779
	अणु .compatible = "renesas,r8a7779",	.data = &soc_rcar_h1 पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A7790
	अणु .compatible = "renesas,r8a7790",	.data = &soc_rcar_h2 पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A7791
	अणु .compatible = "renesas,r8a7791",	.data = &soc_rcar_m2_w पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A7792
	अणु .compatible = "renesas,r8a7792",	.data = &soc_rcar_v2h पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A7793
	अणु .compatible = "renesas,r8a7793",	.data = &soc_rcar_m2_n पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A7794
	अणु .compatible = "renesas,r8a7794",	.data = &soc_rcar_e2 पूर्ण,
#पूर्ण_अगर
#अगर defined(CONFIG_ARCH_R8A77950) || defined(CONFIG_ARCH_R8A77951)
	अणु .compatible = "renesas,r8a7795",	.data = &soc_rcar_h3 पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A77960
	अणु .compatible = "renesas,r8a7796",	.data = &soc_rcar_m3_w पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A77961
	अणु .compatible = "renesas,r8a77961",	.data = &soc_rcar_m3_w पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A77965
	अणु .compatible = "renesas,r8a77965",	.data = &soc_rcar_m3_n पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A77970
	अणु .compatible = "renesas,r8a77970",	.data = &soc_rcar_v3m पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A77980
	अणु .compatible = "renesas,r8a77980",	.data = &soc_rcar_v3h पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A77990
	अणु .compatible = "renesas,r8a77990",	.data = &soc_rcar_e3 पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A77995
	अणु .compatible = "renesas,r8a77995",	.data = &soc_rcar_d3 पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_R8A779A0
	अणु .compatible = "renesas,r8a779a0",	.data = &soc_rcar_v3u पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_SH73A0
	अणु .compatible = "renesas,sh73a0",	.data = &soc_shmobile_ag5 पूर्ण,
#पूर्ण_अगर
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक __init renesas_soc_init(व्योम)
अणु
	काष्ठा soc_device_attribute *soc_dev_attr;
	स्थिर काष्ठा renesas_family *family;
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा renesas_soc *soc;
	व्योम __iomem *chipid = शून्य;
	काष्ठा soc_device *soc_dev;
	काष्ठा device_node *np;
	अचिन्हित पूर्णांक product, eshi = 0, eslo;

	match = of_match_node(renesas_socs, of_root);
	अगर (!match)
		वापस -ENODEV;

	soc = match->data;
	family = soc->family;

	np = of_find_compatible_node(शून्य, शून्य, "renesas,bsid");
	अगर (np) अणु
		chipid = of_iomap(np, 0);
		of_node_put(np);

		अगर (chipid) अणु
			product = पढ़ोl(chipid);
			iounmap(chipid);

			अगर (soc->id && ((product >> 16) & 0xff) != soc->id) अणु
				pr_warn("SoC mismatch (product = 0x%x)\n",
					product);
				वापस -ENODEV;
			पूर्ण
		पूर्ण

		/*
		 * TODO: Upper 4 bits of BSID are क्रम chip version, but the
		 * क्रमmat is not known at this समय so we करोn't know how to
		 * specअगरy eshi and eslo
		 */

		जाओ करोne;
	पूर्ण

	/* Try PRR first, then hardcoded fallback */
	np = of_find_compatible_node(शून्य, शून्य, "renesas,prr");
	अगर (np) अणु
		chipid = of_iomap(np, 0);
		of_node_put(np);
	पूर्ण अन्यथा अगर (soc->id && family->reg) अणु
		chipid = ioremap(family->reg, 4);
	पूर्ण
	अगर (chipid) अणु
		product = पढ़ोl(chipid);
		iounmap(chipid);
		/* R-Car M3-W ES1.1 incorrectly identअगरies as ES2.0 */
		अगर ((product & 0x7fff) == 0x5210)
			product ^= 0x11;
		/* R-Car M3-W ES1.3 incorrectly identअगरies as ES2.1 */
		अगर ((product & 0x7fff) == 0x5211)
			product ^= 0x12;
		अगर (soc->id && ((product >> 8) & 0xff) != soc->id) अणु
			pr_warn("SoC mismatch (product = 0x%x)\n", product);
			वापस -ENODEV;
		पूर्ण
		eshi = ((product >> 4) & 0x0f) + 1;
		eslo = product & 0xf;
	पूर्ण

करोne:
	soc_dev_attr = kzalloc(माप(*soc_dev_attr), GFP_KERNEL);
	अगर (!soc_dev_attr)
		वापस -ENOMEM;

	np = of_find_node_by_path("/");
	of_property_पढ़ो_string(np, "model", &soc_dev_attr->machine);
	of_node_put(np);

	soc_dev_attr->family = kstrdup_स्थिर(family->name, GFP_KERNEL);
	soc_dev_attr->soc_id = kstrdup_स्थिर(म_अक्षर(match->compatible, ',') + 1,
					     GFP_KERNEL);
	अगर (eshi)
		soc_dev_attr->revision = kaप्र_लिखो(GFP_KERNEL, "ES%u.%u", eshi,
						   eslo);

	pr_info("Detected Renesas %s %s %s\n", soc_dev_attr->family,
		soc_dev_attr->soc_id, soc_dev_attr->revision ?: "");

	soc_dev = soc_device_रेजिस्टर(soc_dev_attr);
	अगर (IS_ERR(soc_dev)) अणु
		kमुक्त(soc_dev_attr->revision);
		kमुक्त_स्थिर(soc_dev_attr->soc_id);
		kमुक्त_स्थिर(soc_dev_attr->family);
		kमुक्त(soc_dev_attr);
		वापस PTR_ERR(soc_dev);
	पूर्ण

	वापस 0;
पूर्ण
early_initcall(renesas_soc_init);
