<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Copyright 2019 IBM Corp. */

#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/sys_soc.h>

अटल काष्ठा अणु
	स्थिर अक्षर *name;
	स्थिर u32 id;
पूर्ण स्थिर rev_table[] = अणु
	/* AST2400 */
	अणु "AST2400", 0x02000303 पूर्ण,
	अणु "AST1400", 0x02010103 पूर्ण,
	अणु "AST1250", 0x02010303 पूर्ण,
	/* AST2500 */
	अणु "AST2500", 0x04000303 पूर्ण,
	अणु "AST2510", 0x04000103 पूर्ण,
	अणु "AST2520", 0x04000203 पूर्ण,
	अणु "AST2530", 0x04000403 पूर्ण,
	/* AST2600 */
	अणु "AST2600", 0x05000303 पूर्ण,
	अणु "AST2620", 0x05010203 पूर्ण,
	अणु "AST2605", 0x05030103 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *siliconid_to_name(u32 siliconid)
अणु
	अचिन्हित पूर्णांक id = siliconid & 0xff00ffff;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0 ; i < ARRAY_SIZE(rev_table) ; ++i) अणु
		अगर (rev_table[i].id == id)
			वापस rev_table[i].name;
	पूर्ण

	वापस "Unknown";
पूर्ण

अटल स्थिर अक्षर *siliconid_to_rev(u32 siliconid)
अणु
	अचिन्हित पूर्णांक rev = (siliconid >> 16) & 0xff;
	अचिन्हित पूर्णांक gen = (siliconid >> 24) & 0xff;

	अगर (gen < 0x5) अणु
		/* AST2500 and below */
		चयन (rev) अणु
		हाल 0:
			वापस "A0";
		हाल 1:
			वापस "A1";
		हाल 3:
			वापस "A2";
		पूर्ण
	पूर्ण अन्यथा अणु
		/* AST2600 */
		चयन (rev) अणु
		हाल 0:
			वापस "A0";
		हाल 1:
			वापस "A1";
		हाल 2:
			वापस "A2";
		हाल 3:
			वापस "A3";
		पूर्ण
	पूर्ण

	वापस "??";
पूर्ण

अटल पूर्णांक __init aspeed_socinfo_init(व्योम)
अणु
	काष्ठा soc_device_attribute *attrs;
	काष्ठा soc_device *soc_dev;
	काष्ठा device_node *np;
	व्योम __iomem *reg;
	bool has_chipid = false;
	u32 siliconid;
	u32 chipid[2];
	स्थिर अक्षर *machine = शून्य;

	np = of_find_compatible_node(शून्य, शून्य, "aspeed,silicon-id");
	अगर (!of_device_is_available(np)) अणु
		of_node_put(np);
		वापस -ENODEV;
	पूर्ण

	reg = of_iomap(np, 0);
	अगर (!reg) अणु
		of_node_put(np);
		वापस -ENODEV;
	पूर्ण
	siliconid = पढ़ोl(reg);
	iounmap(reg);

	/* This is optional, the ast2400 करोes not have it */
	reg = of_iomap(np, 1);
	अगर (reg) अणु
		has_chipid = true;
		chipid[0] = पढ़ोl(reg);
		chipid[1] = पढ़ोl(reg + 4);
		iounmap(reg);
	पूर्ण
	of_node_put(np);

	attrs = kzalloc(माप(*attrs), GFP_KERNEL);
	अगर (!attrs)
		वापस -ENODEV;

	/*
	 * Machine: Romulus BMC
	 * Family: AST2500
	 * Revision: A1
	 * SoC ID: raw silicon revision id
	 * Serial Number: 64-bit chipid
	 */

	np = of_find_node_by_path("/");
	of_property_पढ़ो_string(np, "model", &machine);
	अगर (machine)
		attrs->machine = kstrdup(machine, GFP_KERNEL);
	of_node_put(np);

	attrs->family = siliconid_to_name(siliconid);
	attrs->revision = siliconid_to_rev(siliconid);
	attrs->soc_id = kaप्र_लिखो(GFP_KERNEL, "%08x", siliconid);

	अगर (has_chipid)
		attrs->serial_number = kaप्र_लिखो(GFP_KERNEL, "%08x%08x",
						 chipid[1], chipid[0]);

	soc_dev = soc_device_रेजिस्टर(attrs);
	अगर (IS_ERR(soc_dev)) अणु
		kमुक्त(attrs->soc_id);
		kमुक्त(attrs->serial_number);
		kमुक्त(attrs);
		वापस PTR_ERR(soc_dev);
	पूर्ण

	pr_info("ASPEED %s rev %s (%s)\n",
			attrs->family,
			attrs->revision,
			attrs->soc_id);

	वापस 0;
पूर्ण
early_initcall(aspeed_socinfo_init);
