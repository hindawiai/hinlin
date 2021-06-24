<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Pistachio platक्रमm setup
 *
 * Copyright (C) 2014 Google, Inc.
 * Copyright (C) 2016 Imagination Technologies
 */

#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_fdt.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/fw/fw.h>
#समावेश <यंत्र/mips-boards/generic.h>
#समावेश <यंत्र/mips-cps.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/smp-ops.h>
#समावेश <यंत्र/traps.h>

/*
 * Core revision रेजिस्टर decoding
 * Bits 23 to 20: Major rev
 * Bits 15 to 8: Minor rev
 * Bits 7 to 0: Maपूर्णांकenance rev
 */
#घोषणा PISTACHIO_CORE_REV_REG	0xB81483D0
#घोषणा PISTACHIO_CORE_REV_A1	0x00100006
#घोषणा PISTACHIO_CORE_REV_B0	0x00100106

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	u32 core_rev;
	स्थिर अक्षर *sys_type;

	core_rev = __raw_पढ़ोl((स्थिर व्योम *)PISTACHIO_CORE_REV_REG);

	चयन (core_rev) अणु
	हाल PISTACHIO_CORE_REV_B0:
		sys_type = "IMG Pistachio SoC (B0)";
		अवरोध;

	हाल PISTACHIO_CORE_REV_A1:
		sys_type = "IMG Pistachio SoC (A1)";
		अवरोध;

	शेष:
		sys_type = "IMG Pistachio SoC";
		अवरोध;
	पूर्ण

	वापस sys_type;
पूर्ण

व्योम __init *plat_get_fdt(व्योम)
अणु
	अगर (fw_arg0 != -2)
		panic("Device-tree not present");
	वापस (व्योम *)fw_arg1;
पूर्ण

व्योम __init plat_mem_setup(व्योम)
अणु
	__dt_setup_arch(plat_get_fdt());
पूर्ण

#घोषणा DEFAULT_CPC_BASE_ADDR	0x1bde0000
#घोषणा DEFAULT_CDMM_BASE_ADDR	0x1bdd0000

phys_addr_t mips_cpc_शेष_phys_base(व्योम)
अणु
	वापस DEFAULT_CPC_BASE_ADDR;
पूर्ण

phys_addr_t mips_cdmm_phys_base(व्योम)
अणु
	वापस DEFAULT_CDMM_BASE_ADDR;
पूर्ण

अटल व्योम __init mips_nmi_setup(व्योम)
अणु
	व्योम *base;

	base = cpu_has_veic ?
		(व्योम *)(CAC_BASE + 0xa80) :
		(व्योम *)(CAC_BASE + 0x380);
	स_नकल(base, except_vec_nmi, 0x80);
	flush_icache_range((अचिन्हित दीर्घ)base,
			   (अचिन्हित दीर्घ)base + 0x80);
पूर्ण

अटल व्योम __init mips_ejtag_setup(व्योम)
अणु
	व्योम *base;
	बाह्य अक्षर except_vec_ejtag_debug[];

	base = cpu_has_veic ?
		(व्योम *)(CAC_BASE + 0xa00) :
		(व्योम *)(CAC_BASE + 0x300);
	स_नकल(base, except_vec_ejtag_debug, 0x80);
	flush_icache_range((अचिन्हित दीर्घ)base,
			   (अचिन्हित दीर्घ)base + 0x80);
पूर्ण

व्योम __init prom_init(व्योम)
अणु
	board_nmi_handler_setup = mips_nmi_setup;
	board_ejtag_handler_setup = mips_ejtag_setup;

	mips_cm_probe();
	mips_cpc_probe();
	रेजिस्टर_cps_smp_ops();

	pr_info("SoC Type: %s\n", get_प्रणाली_type());
पूर्ण

व्योम __init device_tree_init(व्योम)
अणु
	अगर (!initial_boot_params)
		वापस;

	unflatten_and_copy_device_tree();
पूर्ण
