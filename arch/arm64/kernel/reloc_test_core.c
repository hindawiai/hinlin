<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 Linaro, Ltd. <ard.biesheuvel@linaro.org>
 */

#समावेश <linux/module.h>

पूर्णांक sym64_rel;

#घोषणा SYM64_ABS_VAL		0xffff880000cccccc
#घोषणा SYM32_ABS_VAL		0xf800cccc
#घोषणा SYM16_ABS_VAL		0xf8cc

#घोषणा __SET_ABS(name, val)	यंत्र(".globl " #name "; .set "#name ", " #val)
#घोषणा SET_ABS(name, val)	__SET_ABS(name, val)

SET_ABS(sym64_असल, SYM64_ABS_VAL);
SET_ABS(sym32_असल, SYM32_ABS_VAL);
SET_ABS(sym16_असल, SYM16_ABS_VAL);

यंत्रlinkage u64 असलolute_data64(व्योम);
यंत्रlinkage u64 असलolute_data32(व्योम);
यंत्रlinkage u64 असलolute_data16(व्योम);
यंत्रlinkage u64 चिन्हित_movw(व्योम);
यंत्रlinkage u64 अचिन्हित_movw(व्योम);
यंत्रlinkage u64 relative_adrp(व्योम);
यंत्रlinkage u64 relative_adrp_far(व्योम);
यंत्रlinkage u64 relative_adr(व्योम);
यंत्रlinkage u64 relative_data64(व्योम);
यंत्रlinkage u64 relative_data32(व्योम);
यंत्रlinkage u64 relative_data16(व्योम);

अटल काष्ठा अणु
	अक्षर	name[32];
	u64	(*f)(व्योम);
	u64	expect;
पूर्ण स्थिर funcs[] = अणु
	अणु "R_AARCH64_ABS64",		असलolute_data64, UL(SYM64_ABS_VAL) पूर्ण,
	अणु "R_AARCH64_ABS32",		असलolute_data32, UL(SYM32_ABS_VAL) पूर्ण,
	अणु "R_AARCH64_ABS16",		असलolute_data16, UL(SYM16_ABS_VAL) पूर्ण,
	अणु "R_AARCH64_MOVW_SABS_Gn",	चिन्हित_movw, UL(SYM64_ABS_VAL) पूर्ण,
	अणु "R_AARCH64_MOVW_UABS_Gn",	अचिन्हित_movw, UL(SYM64_ABS_VAL) पूर्ण,
	अणु "R_AARCH64_ADR_PREL_PG_HI21",	relative_adrp, (u64)&sym64_rel पूर्ण,
	अणु "R_AARCH64_ADR_PREL_PG_HI21",	relative_adrp_far, (u64)&memstart_addr पूर्ण,
	अणु "R_AARCH64_ADR_PREL_LO21",	relative_adr, (u64)&sym64_rel पूर्ण,
	अणु "R_AARCH64_PREL64",		relative_data64, (u64)&sym64_rel पूर्ण,
	अणु "R_AARCH64_PREL32",		relative_data32, (u64)&sym64_rel पूर्ण,
	अणु "R_AARCH64_PREL16",		relative_data16, (u64)&sym64_rel पूर्ण,
पूर्ण;

अटल पूर्णांक reloc_test_init(व्योम)
अणु
	पूर्णांक i;

	pr_info("Relocation test:\n");
	pr_info("-------------------------------------------------------\n");

	क्रम (i = 0; i < ARRAY_SIZE(funcs); i++) अणु
		u64 ret = funcs[i].f();

		pr_info("%-31s 0x%016llx %s\n", funcs[i].name, ret,
			ret == funcs[i].expect ? "pass" : "fail");
		अगर (ret != funcs[i].expect)
			pr_err("Relocation failed, expected 0x%016llx, not 0x%016llx\n",
			       funcs[i].expect, ret);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम reloc_test_निकास(व्योम)
अणु
पूर्ण

module_init(reloc_test_init);
module_निकास(reloc_test_निकास);

MODULE_LICENSE("GPL v2");
