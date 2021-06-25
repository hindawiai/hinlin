<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2021 Sअगरive.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/bug.h>
#समावेश <यंत्र/patch.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/venकरोrid_list.h>
#समावेश <यंत्र/errata_list.h>

काष्ठा errata_info_t अणु
	अक्षर name[ERRATA_STRING_LENGTH_MAX];
	bool (*check_func)(अचिन्हित दीर्घ  arch_id, अचिन्हित दीर्घ impid);
पूर्ण;

अटल bool errata_cip_453_check_func(अचिन्हित दीर्घ  arch_id, अचिन्हित दीर्घ impid)
अणु
	/*
	 * Affected cores:
	 * Architecture ID: 0x8000000000000007
	 * Implement ID: 0x20181004 <= impid <= 0x20191105
	 */
	अगर (arch_id != 0x8000000000000007 ||
	    (impid < 0x20181004 || impid > 0x20191105))
		वापस false;
	वापस true;
पूर्ण

अटल bool errata_cip_1200_check_func(अचिन्हित दीर्घ  arch_id, अचिन्हित दीर्घ impid)
अणु
	/*
	 * Affected cores:
	 * Architecture ID: 0x8000000000000007 or 0x1
	 * Implement ID: mimpid[23:0] <= 0x200630 and mimpid != 0x01200626
	 */
	अगर (arch_id != 0x8000000000000007 && arch_id != 0x1)
		वापस false;
	अगर ((impid & 0xffffff) > 0x200630 || impid == 0x1200626)
		वापस false;
	वापस true;
पूर्ण

अटल काष्ठा errata_info_t errata_list[ERRATA_SIFIVE_NUMBER] = अणु
	अणु
		.name = "cip-453",
		.check_func = errata_cip_453_check_func
	पूर्ण,
	अणु
		.name = "cip-1200",
		.check_func = errata_cip_1200_check_func
	पूर्ण,
पूर्ण;

अटल u32 __init sअगरive_errata_probe(अचिन्हित दीर्घ archid, अचिन्हित दीर्घ impid)
अणु
	पूर्णांक idx;
	u32 cpu_req_errata = 0;

	क्रम (idx = 0; idx < ERRATA_SIFIVE_NUMBER; idx++)
		अगर (errata_list[idx].check_func(archid, impid))
			cpu_req_errata |= (1U << idx);

	वापस cpu_req_errata;
पूर्ण

अटल व्योम __init warn_miss_errata(u32 miss_errata)
अणु
	पूर्णांक i;

	pr_warn("----------------------------------------------------------------\n");
	pr_warn("WARNING: Missing the following errata may cause potential issues\n");
	क्रम (i = 0; i < ERRATA_SIFIVE_NUMBER; i++)
		अगर (miss_errata & 0x1 << i)
			pr_warn("\tSiFive Errata[%d]:%s\n", i, errata_list[i].name);
	pr_warn("Please enable the corresponding Kconfig to apply them\n");
	pr_warn("----------------------------------------------------------------\n");
पूर्ण

व्योम __init sअगरive_errata_patch_func(काष्ठा alt_entry *begin, काष्ठा alt_entry *end,
				     अचिन्हित दीर्घ archid, अचिन्हित दीर्घ impid)
अणु
	काष्ठा alt_entry *alt;
	u32 cpu_req_errata = sअगरive_errata_probe(archid, impid);
	u32 cpu_apply_errata = 0;
	u32 पंचांगp;

	क्रम (alt = begin; alt < end; alt++) अणु
		अगर (alt->venकरोr_id != SIFIVE_VENDOR_ID)
			जारी;
		अगर (alt->errata_id >= ERRATA_SIFIVE_NUMBER) अणु
			WARN(1, "This errata id:%d is not in kernel errata list", alt->errata_id);
			जारी;
		पूर्ण

		पंचांगp = (1U << alt->errata_id);
		अगर (cpu_req_errata & पंचांगp) अणु
			patch_text_nosync(alt->old_ptr, alt->alt_ptr, alt->alt_len);
			cpu_apply_errata |= पंचांगp;
		पूर्ण
	पूर्ण
	अगर (cpu_apply_errata != cpu_req_errata)
		warn_miss_errata(cpu_req_errata - cpu_apply_errata);
पूर्ण
