<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * alternative runसमय patching
 * inspired by the ARM64 and x86 version
 *
 * Copyright (C) 2021 Sअगरive.
 */

#समावेश <linux/init.h>
#समावेश <linux/cpu.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/venकरोrid_list.h>
#समावेश <यंत्र/sbi.h>
#समावेश <यंत्र/csr.h>

अटल काष्ठा cpu_manufacturer_info_t अणु
	अचिन्हित दीर्घ venकरोr_id;
	अचिन्हित दीर्घ arch_id;
	अचिन्हित दीर्घ imp_id;
पूर्ण cpu_mfr_info;

अटल व्योम (*venकरोr_patch_func)(काष्ठा alt_entry *begin, काष्ठा alt_entry *end,
				 अचिन्हित दीर्घ archid, अचिन्हित दीर्घ impid);

अटल अंतरभूत व्योम __init riscv_fill_cpu_mfr_info(व्योम)
अणु
#अगर_घोषित CONFIG_RISCV_M_MODE
	cpu_mfr_info.venकरोr_id = csr_पढ़ो(CSR_MVENDORID);
	cpu_mfr_info.arch_id = csr_पढ़ो(CSR_MARCHID);
	cpu_mfr_info.imp_id = csr_पढ़ो(CSR_MIMPID);
#अन्यथा
	cpu_mfr_info.venकरोr_id = sbi_get_mvenकरोrid();
	cpu_mfr_info.arch_id = sbi_get_marchid();
	cpu_mfr_info.imp_id = sbi_get_mimpid();
#पूर्ण_अगर
पूर्ण

अटल व्योम __init init_alternative(व्योम)
अणु
	riscv_fill_cpu_mfr_info();

	चयन (cpu_mfr_info.venकरोr_id) अणु
#अगर_घोषित CONFIG_ERRATA_SIFIVE
	हाल SIFIVE_VENDOR_ID:
		venकरोr_patch_func = sअगरive_errata_patch_func;
		अवरोध;
#पूर्ण_अगर
	शेष:
		venकरोr_patch_func = शून्य;
	पूर्ण
पूर्ण

/*
 * This is called very early in the boot process (directly after we run
 * a feature detect on the boot CPU). No need to worry about other CPUs
 * here.
 */
व्योम __init apply_boot_alternatives(व्योम)
अणु
	/* If called on non-boot cpu things could go wrong */
	WARN_ON(smp_processor_id() != 0);

	init_alternative();

	अगर (!venकरोr_patch_func)
		वापस;

	venकरोr_patch_func((काष्ठा alt_entry *)__alt_start,
			  (काष्ठा alt_entry *)__alt_end,
			  cpu_mfr_info.arch_id, cpu_mfr_info.imp_id);
पूर्ण

