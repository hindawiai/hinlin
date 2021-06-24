<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Rabin Vincent <rabin.vincent@stericsson.com> क्रम ST-Ericsson
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/sys_soc.h>

#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/mach/map.h>

/**
 * काष्ठा dbx500_asic_id - fields of the ASIC ID
 * @process: the manufacturing process, 0x40 is 40 nm 0x00 is "standard"
 * @partnumber: hithereto 0x8500 क्रम DB8500
 * @revision: version code in the series
 */
काष्ठा dbx500_asic_id अणु
	u16	partnumber;
	u8	revision;
	u8	process;
पूर्ण;

अटल काष्ठा dbx500_asic_id dbx500_id;

अटल अचिन्हित पूर्णांक __init ux500_पढ़ो_asicid(phys_addr_t addr)
अणु
	व्योम __iomem *virt = ioremap(addr, 4);
	अचिन्हित पूर्णांक asicid;

	अगर (!virt)
		वापस 0;

	asicid = पढ़ोl(virt);
	iounmap(virt);

	वापस asicid;
पूर्ण

अटल व्योम ux500_prपूर्णांक_soc_info(अचिन्हित पूर्णांक asicid)
अणु
	अचिन्हित पूर्णांक rev = dbx500_id.revision;

	pr_info("DB%4x ", dbx500_id.partnumber);

	अगर (rev == 0x01)
		pr_cont("Early Drop");
	अन्यथा अगर (rev >= 0xA0)
		pr_cont("v%d.%d" , (rev >> 4) - 0xA + 1, rev & 0xf);
	अन्यथा
		pr_cont("Unknown");

	pr_cont(" [%#010x]\n", asicid);
पूर्ण

अटल अचिन्हित पूर्णांक partnumber(अचिन्हित पूर्णांक asicid)
अणु
	वापस (asicid >> 8) & 0xffff;
पूर्ण

/*
 * SOC		MIDR		ASICID ADDRESS		ASICID VALUE
 * DB8500ed	0x410fc090	0x9001FFF4		0x00850001
 * DB8500v1	0x411fc091	0x9001FFF4		0x008500A0
 * DB8500v1.1	0x411fc091	0x9001FFF4		0x008500A1
 * DB8500v2	0x412fc091	0x9001DBF4		0x008500B0
 * DB8520v2.2	0x412fc091	0x9001DBF4		0x008500B2
 * DB5500v1	0x412fc091	0x9001FFF4		0x005500A0
 * DB9540	0x413fc090	0xFFFFDBF4		0x009540xx
 */

अटल व्योम __init ux500_setup_id(व्योम)
अणु
	अचिन्हित पूर्णांक cpuid = पढ़ो_cpuid_id();
	अचिन्हित पूर्णांक asicid = 0;
	phys_addr_t addr = 0;

	चयन (cpuid) अणु
	हाल 0x410fc090: /* DB8500ed */
	हाल 0x411fc091: /* DB8500v1 */
		addr = 0x9001FFF4;
		अवरोध;

	हाल 0x412fc091: /* DB8520 / DB8500v2 / DB5500v1 */
		asicid = ux500_पढ़ो_asicid(0x9001DBF4);
		अगर (partnumber(asicid) == 0x8500 ||
		    partnumber(asicid) == 0x8520)
			/* DB8500v2 */
			अवरोध;

		/* DB5500v1 */
		addr = 0x9001FFF4;
		अवरोध;

	हाल 0x413fc090: /* DB9540 */
		addr = 0xFFFFDBF4;
		अवरोध;
	पूर्ण

	अगर (addr)
		asicid = ux500_पढ़ो_asicid(addr);

	अगर (!asicid) अणु
		pr_err("Unable to identify SoC\n");
		BUG();
	पूर्ण

	dbx500_id.process = asicid >> 24;
	dbx500_id.partnumber = partnumber(asicid);
	dbx500_id.revision = asicid & 0xff;

	ux500_prपूर्णांक_soc_info(asicid);
पूर्ण

अटल स्थिर अक्षर * __init ux500_get_machine(व्योम)
अणु
	वापस kaप्र_लिखो(GFP_KERNEL, "DB%4x", dbx500_id.partnumber);
पूर्ण

अटल स्थिर अक्षर * __init ux500_get_family(व्योम)
अणु
	वापस kaप्र_लिखो(GFP_KERNEL, "ux500");
पूर्ण

अटल स्थिर अक्षर * __init ux500_get_revision(व्योम)
अणु
	अचिन्हित पूर्णांक rev = dbx500_id.revision;

	अगर (rev == 0x01)
		वापस kaप्र_लिखो(GFP_KERNEL, "%s", "ED");
	अन्यथा अगर (rev >= 0xA0)
		वापस kaप्र_लिखो(GFP_KERNEL, "%d.%d",
				 (rev >> 4) - 0xA + 1, rev & 0xf);

	वापस kaप्र_लिखो(GFP_KERNEL, "%s", "Unknown");
पूर्ण

अटल sमाप_प्रकार
process_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अगर (dbx500_id.process == 0x00)
		वापस प्र_लिखो(buf, "Standard\n");

	वापस प्र_लिखो(buf, "%02xnm\n", dbx500_id.process);
पूर्ण

अटल DEVICE_ATTR_RO(process);

अटल काष्ठा attribute *ux500_soc_attrs[] = अणु
	&dev_attr_process.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(ux500_soc);

अटल स्थिर अक्षर *db8500_पढ़ो_soc_id(काष्ठा device_node *backupram)
अणु
	व्योम __iomem *base;
	व्योम __iomem *uid;
	स्थिर अक्षर *retstr;

	base = of_iomap(backupram, 0);
	अगर (!base)
		वापस शून्य;
	uid = base + 0x1fc0;

	/* Throw these device-specअगरic numbers पूर्णांकo the entropy pool */
	add_device_अक्रमomness(uid, 0x14);
	retstr = kaप्र_लिखो(GFP_KERNEL, "%08x%08x%08x%08x%08x",
			 पढ़ोl((u32 *)uid+0),
			 पढ़ोl((u32 *)uid+1), पढ़ोl((u32 *)uid+2),
			 पढ़ोl((u32 *)uid+3), पढ़ोl((u32 *)uid+4));
	iounmap(base);
	वापस retstr;
पूर्ण

अटल व्योम __init soc_info_populate(काष्ठा soc_device_attribute *soc_dev_attr,
				     काष्ठा device_node *backupram)
अणु
	soc_dev_attr->soc_id   = db8500_पढ़ो_soc_id(backupram);
	soc_dev_attr->machine  = ux500_get_machine();
	soc_dev_attr->family   = ux500_get_family();
	soc_dev_attr->revision = ux500_get_revision();
	soc_dev_attr->custom_attr_group = ux500_soc_groups[0];
पूर्ण

अटल पूर्णांक __init ux500_soc_device_init(व्योम)
अणु
	काष्ठा soc_device *soc_dev;
	काष्ठा soc_device_attribute *soc_dev_attr;
	काष्ठा device_node *backupram;

	backupram = of_find_compatible_node(शून्य, शून्य, "ste,dbx500-backupram");
	अगर (!backupram)
		वापस 0;

	ux500_setup_id();

	soc_dev_attr = kzalloc(माप(*soc_dev_attr), GFP_KERNEL);
	अगर (!soc_dev_attr) अणु
		of_node_put(backupram);
		वापस -ENOMEM;
	पूर्ण

	soc_info_populate(soc_dev_attr, backupram);
	of_node_put(backupram);

	soc_dev = soc_device_रेजिस्टर(soc_dev_attr);
	अगर (IS_ERR(soc_dev)) अणु
	        kमुक्त(soc_dev_attr);
		वापस PTR_ERR(soc_dev);
	पूर्ण

	वापस 0;
पूर्ण
subsys_initcall(ux500_soc_device_init);
