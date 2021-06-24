<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Early cpufeature override framework
 *
 * Copyright (C) 2020 Google LLC
 * Author: Marc Zyngier <maz@kernel.org>
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/kernel.h>
#समावेश <linux/libfdt.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/setup.h>

#घोषणा FTR_DESC_NAME_LEN	20
#घोषणा FTR_DESC_FIELD_LEN	10
#घोषणा FTR_ALIAS_NAME_LEN	30
#घोषणा FTR_ALIAS_OPTION_LEN	80

काष्ठा ftr_set_desc अणु
	अक्षर 				name[FTR_DESC_NAME_LEN];
	काष्ठा arm64_ftr_override	*override;
	काष्ठा अणु
		अक्षर			name[FTR_DESC_FIELD_LEN];
		u8			shअगरt;
		bool			(*filter)(u64 val);
	पूर्ण 				fields[];
पूर्ण;

अटल bool __init mmfr1_vh_filter(u64 val)
अणु
	/*
	 * If we ever reach this poपूर्णांक जबतक running VHE, we're
	 * guaranteed to be on one of these funky, VHE-stuck CPUs. If
	 * the user was trying to क्रमce nVHE on us, proceed with
	 * attitude adjusपंचांगent.
	 */
	वापस !(is_kernel_in_hyp_mode() && val == 0);
पूर्ण

अटल स्थिर काष्ठा ftr_set_desc mmfr1 __initस्थिर = अणु
	.name		= "id_aa64mmfr1",
	.override	= &id_aa64mmfr1_override,
	.fields		= अणु
		अणु "vh", ID_AA64MMFR1_VHE_SHIFT, mmfr1_vh_filter पूर्ण,
		अणुपूर्ण
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ftr_set_desc pfr1 __initस्थिर = अणु
	.name		= "id_aa64pfr1",
	.override	= &id_aa64pfr1_override,
	.fields		= अणु
	        अणु "bt", ID_AA64PFR1_BT_SHIFT पूर्ण,
		अणुपूर्ण
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ftr_set_desc isar1 __initस्थिर = अणु
	.name		= "id_aa64isar1",
	.override	= &id_aa64isar1_override,
	.fields		= अणु
	        अणु "gpi", ID_AA64ISAR1_GPI_SHIFT पूर्ण,
	        अणु "gpa", ID_AA64ISAR1_GPA_SHIFT पूर्ण,
	        अणु "api", ID_AA64ISAR1_API_SHIFT पूर्ण,
	        अणु "apa", ID_AA64ISAR1_APA_SHIFT पूर्ण,
		अणुपूर्ण
	पूर्ण,
पूर्ण;

बाह्य काष्ठा arm64_ftr_override kaslr_feature_override;

अटल स्थिर काष्ठा ftr_set_desc kaslr __initस्थिर = अणु
	.name		= "kaslr",
#अगर_घोषित CONFIG_RANDOMIZE_BASE
	.override	= &kaslr_feature_override,
#पूर्ण_अगर
	.fields		= अणु
		अणु "disabled", 0 पूर्ण,
		अणुपूर्ण
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ftr_set_desc * स्थिर regs[] __initस्थिर = अणु
	&mmfr1,
	&pfr1,
	&isar1,
	&kaslr,
पूर्ण;

अटल स्थिर काष्ठा अणु
	अक्षर	alias[FTR_ALIAS_NAME_LEN];
	अक्षर	feature[FTR_ALIAS_OPTION_LEN];
पूर्ण aliases[] __initस्थिर = अणु
	अणु "kvm-arm.mode=nvhe",		"id_aa64mmfr1.vh=0" पूर्ण,
	अणु "kvm-arm.mode=protected",	"id_aa64mmfr1.vh=0" पूर्ण,
	अणु "arm64.nobti",		"id_aa64pfr1.bt=0" पूर्ण,
	अणु "arm64.nopauth",
	  "id_aa64isar1.gpi=0 id_aa64isar1.gpa=0 "
	  "id_aa64isar1.api=0 id_aa64isar1.apa=0"	   पूर्ण,
	अणु "nokaslr",			"kaslr.disabled=1" पूर्ण,
पूर्ण;

अटल पूर्णांक __init find_field(स्थिर अक्षर *cmdline,
			     स्थिर काष्ठा ftr_set_desc *reg, पूर्णांक f, u64 *v)
अणु
	अक्षर opt[FTR_DESC_NAME_LEN + FTR_DESC_FIELD_LEN + 2];
	पूर्णांक len;

	len = snम_लिखो(opt, ARRAY_SIZE(opt), "%s.%s=",
		       reg->name, reg->fields[f].name);

	अगर (!parameqn(cmdline, opt, len))
		वापस -1;

	वापस kstrtou64(cmdline + len, 0, v);
पूर्ण

अटल व्योम __init match_options(स्थिर अक्षर *cmdline)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(regs); i++) अणु
		पूर्णांक f;

		अगर (!regs[i]->override)
			जारी;

		क्रम (f = 0; म_माप(regs[i]->fields[f].name); f++) अणु
			u64 shअगरt = regs[i]->fields[f].shअगरt;
			u64 mask = 0xfUL << shअगरt;
			u64 v;

			अगर (find_field(cmdline, regs[i], f, &v))
				जारी;

			/*
			 * If an override माला_लो filtered out, advertise
			 * it by setting the value to 0xf, but
			 * clearing the mask... Yes, this is fragile.
			 */
			अगर (regs[i]->fields[f].filter &&
			    !regs[i]->fields[f].filter(v)) अणु
				regs[i]->override->val  |= mask;
				regs[i]->override->mask &= ~mask;
				जारी;
			पूर्ण

			regs[i]->override->val  &= ~mask;
			regs[i]->override->val  |= (v << shअगरt) & mask;
			regs[i]->override->mask |= mask;

			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल __init व्योम __parse_cmdline(स्थिर अक्षर *cmdline, bool parse_aliases)
अणु
	करो अणु
		अक्षर buf[256];
		माप_प्रकार len;
		पूर्णांक i;

		cmdline = skip_spaces(cmdline);

		क्रम (len = 0; cmdline[len] && !है_खाली(cmdline[len]); len++);
		अगर (!len)
			वापस;

		len = min(len, ARRAY_SIZE(buf) - 1);
		म_नकलन(buf, cmdline, len);
		buf[len] = 0;

		अगर (म_भेद(buf, "--") == 0)
			वापस;

		cmdline += len;

		match_options(buf);

		क्रम (i = 0; parse_aliases && i < ARRAY_SIZE(aliases); i++)
			अगर (parameq(buf, aliases[i].alias))
				__parse_cmdline(aliases[i].feature, false);
	पूर्ण जबतक (1);
पूर्ण

अटल __init स्थिर u8 *get_bootargs_cmdline(व्योम)
अणु
	स्थिर u8 *prop;
	व्योम *fdt;
	पूर्णांक node;

	fdt = get_early_fdt_ptr();
	अगर (!fdt)
		वापस शून्य;

	node = fdt_path_offset(fdt, "/chosen");
	अगर (node < 0)
		वापस शून्य;

	prop = fdt_getprop(fdt, node, "bootargs", शून्य);
	अगर (!prop)
		वापस शून्य;

	वापस म_माप(prop) ? prop : शून्य;
पूर्ण

अटल __init व्योम parse_cmdline(व्योम)
अणु
	स्थिर u8 *prop = get_bootargs_cmdline();

	अगर (IS_ENABLED(CONFIG_CMDLINE_FORCE) || !prop)
		__parse_cmdline(CONFIG_CMDLINE, true);

	अगर (!IS_ENABLED(CONFIG_CMDLINE_FORCE) && prop)
		__parse_cmdline(prop, true);
पूर्ण

/* Keep checkers quiet */
व्योम init_feature_override(व्योम);

यंत्रlinkage व्योम __init init_feature_override(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(regs); i++) अणु
		अगर (regs[i]->override) अणु
			regs[i]->override->val  = 0;
			regs[i]->override->mask = 0;
		पूर्ण
	पूर्ण

	parse_cmdline();

	क्रम (i = 0; i < ARRAY_SIZE(regs); i++) अणु
		अगर (regs[i]->override)
			__flush_dcache_area(regs[i]->override,
					    माप(*regs[i]->override));
	पूर्ण
पूर्ण
