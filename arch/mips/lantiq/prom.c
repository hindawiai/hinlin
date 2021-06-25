<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2010 John Crispin <john@phrozen.org>
 */

#समावेश <linux/export.h>
#समावेश <linux/clk.h>
#समावेश <linux/memblock.h>
#समावेश <linux/of_fdt.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/prom.h>

#समावेश <lantiq.h>

#समावेश "prom.h"
#समावेश "clk.h"

/* access to the ebu needs to be locked between dअगरferent drivers */
DEFINE_SPINLOCK(ebu_lock);
EXPORT_SYMBOL_GPL(ebu_lock);

/*
 * This is needed by the VPE loader code, just set it to 0 and assume
 * that the firmware hardcodes this value to something useful.
 */
अचिन्हित दीर्घ physical_memsize = 0L;

/*
 * this काष्ठा is filled by the soc specअगरic detection code and holds
 * inक्रमmation about the specअगरic soc type, revision and name
 */
अटल काष्ठा ltq_soc_info soc_info;

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	वापस soc_info.sys_type;
पूर्ण

पूर्णांक ltq_soc_type(व्योम)
अणु
	वापस soc_info.type;
पूर्ण

अटल व्योम __init prom_init_cmdline(व्योम)
अणु
	पूर्णांक argc = fw_arg0;
	अक्षर **argv = (अक्षर **) KSEG1ADDR(fw_arg1);
	पूर्णांक i;

	arcs_cmdline[0] = '\0';

	क्रम (i = 0; i < argc; i++) अणु
		अक्षर *p = (अक्षर *) KSEG1ADDR(argv[i]);

		अगर (CPHYSADDR(p) && *p) अणु
			strlcat(arcs_cmdline, p, माप(arcs_cmdline));
			strlcat(arcs_cmdline, " ", माप(arcs_cmdline));
		पूर्ण
	पूर्ण
पूर्ण

व्योम __init plat_mem_setup(व्योम)
अणु
	व्योम *dtb;

	ioport_resource.start = IOPORT_RESOURCE_START;
	ioport_resource.end = IOPORT_RESOURCE_END;
	iomem_resource.start = IOMEM_RESOURCE_START;
	iomem_resource.end = IOMEM_RESOURCE_END;

	set_io_port_base((अचिन्हित दीर्घ) KSEG1);

	dtb = get_fdt();
	अगर (dtb == शून्य)
		panic("no dtb found");

	/*
	 * Load the devicetree. This causes the chosen node to be
	 * parsed resulting in our memory appearing
	 */
	__dt_setup_arch(dtb);
पूर्ण

व्योम __init device_tree_init(व्योम)
अणु
	unflatten_and_copy_device_tree();
पूर्ण

व्योम __init prom_init(व्योम)
अणु
	/* call the soc specअगरic detetcion code and get it to fill soc_info */
	ltq_soc_detect(&soc_info);
	snम_लिखो(soc_info.sys_type, LTQ_SYS_TYPE_LEN - 1, "%s rev %s",
		soc_info.name, soc_info.rev_type);
	soc_info.sys_type[LTQ_SYS_TYPE_LEN - 1] = '\0';
	pr_info("SoC: %s\n", soc_info.sys_type);
	prom_init_cmdline();

#अगर defined(CONFIG_MIPS_MT_SMP)
	अगर (रेजिस्टर_vsmp_smp_ops())
		panic("failed to register_vsmp_smp_ops()");
#पूर्ण_अगर
पूर्ण
