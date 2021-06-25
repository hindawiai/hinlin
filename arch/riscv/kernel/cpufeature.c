<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copied from arch/arm64/kernel/cpufeature.c
 *
 * Copyright (C) 2015 ARM Ltd.
 * Copyright (C) 2017 SiFive
 */

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/of.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/hwcap.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/चयन_to.h>

अचिन्हित दीर्घ elf_hwcap __पढ़ो_mostly;

/* Host ISA biपंचांगap */
अटल DECLARE_BITMAP(riscv_isa, RISCV_ISA_EXT_MAX) __पढ़ो_mostly;

#अगर_घोषित CONFIG_FPU
bool has_fpu __पढ़ो_mostly;
#पूर्ण_अगर

/**
 * riscv_isa_extension_base() - Get base extension word
 *
 * @isa_biपंचांगap: ISA biपंचांगap to use
 * Return: base extension word as अचिन्हित दीर्घ value
 *
 * NOTE: If isa_biपंचांगap is शून्य then Host ISA biपंचांगap will be used.
 */
अचिन्हित दीर्घ riscv_isa_extension_base(स्थिर अचिन्हित दीर्घ *isa_biपंचांगap)
अणु
	अगर (!isa_biपंचांगap)
		वापस riscv_isa[0];
	वापस isa_biपंचांगap[0];
पूर्ण
EXPORT_SYMBOL_GPL(riscv_isa_extension_base);

/**
 * __riscv_isa_extension_available() - Check whether given extension
 * is available or not
 *
 * @isa_biपंचांगap: ISA biपंचांगap to use
 * @bit: bit position of the desired extension
 * Return: true or false
 *
 * NOTE: If isa_biपंचांगap is शून्य then Host ISA biपंचांगap will be used.
 */
bool __riscv_isa_extension_available(स्थिर अचिन्हित दीर्घ *isa_biपंचांगap, पूर्णांक bit)
अणु
	स्थिर अचिन्हित दीर्घ *bmap = (isa_biपंचांगap) ? isa_biपंचांगap : riscv_isa;

	अगर (bit >= RISCV_ISA_EXT_MAX)
		वापस false;

	वापस test_bit(bit, bmap) ? true : false;
पूर्ण
EXPORT_SYMBOL_GPL(__riscv_isa_extension_available);

व्योम riscv_fill_hwcap(व्योम)
अणु
	काष्ठा device_node *node;
	स्थिर अक्षर *isa;
	अक्षर prपूर्णांक_str[BITS_PER_LONG + 1];
	माप_प्रकार i, j, isa_len;
	अटल अचिन्हित दीर्घ isa2hwcap[256] = अणु0पूर्ण;

	isa2hwcap['i'] = isa2hwcap['I'] = COMPAT_HWCAP_ISA_I;
	isa2hwcap['m'] = isa2hwcap['M'] = COMPAT_HWCAP_ISA_M;
	isa2hwcap['a'] = isa2hwcap['A'] = COMPAT_HWCAP_ISA_A;
	isa2hwcap['f'] = isa2hwcap['F'] = COMPAT_HWCAP_ISA_F;
	isa2hwcap['d'] = isa2hwcap['D'] = COMPAT_HWCAP_ISA_D;
	isa2hwcap['c'] = isa2hwcap['C'] = COMPAT_HWCAP_ISA_C;

	elf_hwcap = 0;

	biपंचांगap_zero(riscv_isa, RISCV_ISA_EXT_MAX);

	क्रम_each_of_cpu_node(node) अणु
		अचिन्हित दीर्घ this_hwcap = 0;
		अचिन्हित दीर्घ this_isa = 0;

		अगर (riscv_of_processor_hartid(node) < 0)
			जारी;

		अगर (of_property_पढ़ो_string(node, "riscv,isa", &isa)) अणु
			pr_warn("Unable to find \"riscv,isa\" devicetree entry\n");
			जारी;
		पूर्ण

		i = 0;
		isa_len = म_माप(isa);
#अगर IS_ENABLED(CONFIG_32BIT)
		अगर (!म_भेदन(isa, "rv32", 4))
			i += 4;
#या_अगर IS_ENABLED(CONFIG_64BIT)
		अगर (!म_भेदन(isa, "rv64", 4))
			i += 4;
#पूर्ण_अगर
		क्रम (; i < isa_len; ++i) अणु
			this_hwcap |= isa2hwcap[(अचिन्हित अक्षर)(isa[i])];
			/*
			 * TODO: X, Y and Z extension parsing क्रम Host ISA
			 * biपंचांगap will be added in-future.
			 */
			अगर ('a' <= isa[i] && isa[i] < 'x')
				this_isa |= (1UL << (isa[i] - 'a'));
		पूर्ण

		/*
		 * All "okay" hart should have same isa. Set HWCAP based on
		 * common capabilities of every "okay" hart, in हाल they करोn't
		 * have.
		 */
		अगर (elf_hwcap)
			elf_hwcap &= this_hwcap;
		अन्यथा
			elf_hwcap = this_hwcap;

		अगर (riscv_isa[0])
			riscv_isa[0] &= this_isa;
		अन्यथा
			riscv_isa[0] = this_isa;
	पूर्ण

	/* We करोn't support प्रणालीs with F but without D, so mask those out
	 * here. */
	अगर ((elf_hwcap & COMPAT_HWCAP_ISA_F) && !(elf_hwcap & COMPAT_HWCAP_ISA_D)) अणु
		pr_info("This kernel does not support systems with F but not D\n");
		elf_hwcap &= ~COMPAT_HWCAP_ISA_F;
	पूर्ण

	स_रखो(prपूर्णांक_str, 0, माप(prपूर्णांक_str));
	क्रम (i = 0, j = 0; i < BITS_PER_LONG; i++)
		अगर (riscv_isa[0] & BIT_MASK(i))
			prपूर्णांक_str[j++] = (अक्षर)('a' + i);
	pr_info("riscv: ISA extensions %s\n", prपूर्णांक_str);

	स_रखो(prपूर्णांक_str, 0, माप(prपूर्णांक_str));
	क्रम (i = 0, j = 0; i < BITS_PER_LONG; i++)
		अगर (elf_hwcap & BIT_MASK(i))
			prपूर्णांक_str[j++] = (अक्षर)('a' + i);
	pr_info("riscv: ELF capabilities %s\n", prपूर्णांक_str);

#अगर_घोषित CONFIG_FPU
	अगर (elf_hwcap & (COMPAT_HWCAP_ISA_F | COMPAT_HWCAP_ISA_D))
		has_fpu = true;
#पूर्ण_अगर
पूर्ण
