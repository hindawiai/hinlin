<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/cpu.h>
#समावेश <यंत्र/nospec-branch.h>

अटल पूर्णांक __init nobp_setup_early(अक्षर *str)
अणु
	bool enabled;
	पूर्णांक rc;

	rc = kstrtobool(str, &enabled);
	अगर (rc)
		वापस rc;
	अगर (enabled && test_facility(82)) अणु
		/*
		 * The user explicitely requested nobp=1, enable it and
		 * disable the expoline support.
		 */
		__set_facility(82, S390_lowcore.alt_stfle_fac_list);
		अगर (IS_ENABLED(CONFIG_EXPOLINE))
			nospec_disable = 1;
	पूर्ण अन्यथा अणु
		__clear_facility(82, S390_lowcore.alt_stfle_fac_list);
	पूर्ण
	वापस 0;
पूर्ण
early_param("nobp", nobp_setup_early);

अटल पूर्णांक __init nospec_setup_early(अक्षर *str)
अणु
	__clear_facility(82, S390_lowcore.alt_stfle_fac_list);
	वापस 0;
पूर्ण
early_param("nospec", nospec_setup_early);

अटल पूर्णांक __init nospec_report(व्योम)
अणु
	अगर (test_facility(156))
		pr_info("Spectre V2 mitigation: etokens\n");
	अगर (__is_defined(CC_USING_EXPOLINE) && !nospec_disable)
		pr_info("Spectre V2 mitigation: execute trampolines\n");
	अगर (__test_facility(82, S390_lowcore.alt_stfle_fac_list))
		pr_info("Spectre V2 mitigation: limited branch prediction\n");
	वापस 0;
पूर्ण
arch_initcall(nospec_report);

#अगर_घोषित CONFIG_EXPOLINE

पूर्णांक nospec_disable = IS_ENABLED(CONFIG_EXPOLINE_OFF);

अटल पूर्णांक __init nospectre_v2_setup_early(अक्षर *str)
अणु
	nospec_disable = 1;
	वापस 0;
पूर्ण
early_param("nospectre_v2", nospectre_v2_setup_early);

व्योम __init nospec_स्वतः_detect(व्योम)
अणु
	अगर (test_facility(156) || cpu_mitigations_off()) अणु
		/*
		 * The machine supports etokens.
		 * Disable expolines and disable nobp.
		 */
		अगर (__is_defined(CC_USING_EXPOLINE))
			nospec_disable = 1;
		__clear_facility(82, S390_lowcore.alt_stfle_fac_list);
	पूर्ण अन्यथा अगर (__is_defined(CC_USING_EXPOLINE)) अणु
		/*
		 * The kernel has been compiled with expolines.
		 * Keep expolines enabled and disable nobp.
		 */
		nospec_disable = 0;
		__clear_facility(82, S390_lowcore.alt_stfle_fac_list);
	पूर्ण
	/*
	 * If the kernel has not been compiled with expolines the
	 * nobp setting decides what is करोne, this depends on the
	 * CONFIG_KERNEL_NP option and the nobp/nospec parameters.
	 */
पूर्ण

अटल पूर्णांक __init spectre_v2_setup_early(अक्षर *str)
अणु
	अगर (str && !म_भेदन(str, "on", 2)) अणु
		nospec_disable = 0;
		__clear_facility(82, S390_lowcore.alt_stfle_fac_list);
	पूर्ण
	अगर (str && !म_भेदन(str, "off", 3))
		nospec_disable = 1;
	अगर (str && !म_भेदन(str, "auto", 4))
		nospec_स्वतः_detect();
	वापस 0;
पूर्ण
early_param("spectre_v2", spectre_v2_setup_early);

अटल व्योम __init_or_module __nospec_revert(s32 *start, s32 *end)
अणु
	क्रमागत अणु BRCL_EXPOLINE, BRASL_EXPOLINE पूर्ण type;
	u8 *instr, *thunk, *br;
	u8 insnbuf[6];
	s32 *epo;

	/* Second part of the inकाष्ठाion replace is always a nop */
	क्रम (epo = start; epo < end; epo++) अणु
		instr = (u8 *) epo + *epo;
		अगर (instr[0] == 0xc0 && (instr[1] & 0x0f) == 0x04)
			type = BRCL_EXPOLINE;	/* brcl inकाष्ठाion */
		अन्यथा अगर (instr[0] == 0xc0 && (instr[1] & 0x0f) == 0x05)
			type = BRASL_EXPOLINE;	/* brasl inकाष्ठाion */
		अन्यथा
			जारी;
		thunk = instr + (*(पूर्णांक *)(instr + 2)) * 2;
		अगर (thunk[0] == 0xc6 && thunk[1] == 0x00)
			/* exrl %r0,<target-br> */
			br = thunk + (*(पूर्णांक *)(thunk + 2)) * 2;
		अन्यथा अगर (thunk[0] == 0xc0 && (thunk[1] & 0x0f) == 0x00 &&
			 thunk[6] == 0x44 && thunk[7] == 0x00 &&
			 (thunk[8] & 0x0f) == 0x00 && thunk[9] == 0x00 &&
			 (thunk[1] & 0xf0) == (thunk[8] & 0xf0))
			/* larl %rx,<target br> + ex %r0,0(%rx) */
			br = thunk + (*(पूर्णांक *)(thunk + 2)) * 2;
		अन्यथा
			जारी;
		/* Check क्रम unconditional branch 0x07f? or 0x47f???? */
		अगर ((br[0] & 0xbf) != 0x07 || (br[1] & 0xf0) != 0xf0)
			जारी;

		स_नकल(insnbuf + 2, (अक्षर[]) अणु 0x47, 0x00, 0x07, 0x00 पूर्ण, 4);
		चयन (type) अणु
		हाल BRCL_EXPOLINE:
			insnbuf[0] = br[0];
			insnbuf[1] = (instr[1] & 0xf0) | (br[1] & 0x0f);
			अगर (br[0] == 0x47) अणु
				/* brcl to b, replace with bc + nopr */
				insnbuf[2] = br[2];
				insnbuf[3] = br[3];
			पूर्ण अन्यथा अणु
				/* brcl to br, replace with bcr + nop */
			पूर्ण
			अवरोध;
		हाल BRASL_EXPOLINE:
			insnbuf[1] = (instr[1] & 0xf0) | (br[1] & 0x0f);
			अगर (br[0] == 0x47) अणु
				/* brasl to b, replace with bas + nopr */
				insnbuf[0] = 0x4d;
				insnbuf[2] = br[2];
				insnbuf[3] = br[3];
			पूर्ण अन्यथा अणु
				/* brasl to br, replace with basr + nop */
				insnbuf[0] = 0x0d;
			पूर्ण
			अवरोध;
		पूर्ण

		s390_kernel_ग_लिखो(instr, insnbuf, 6);
	पूर्ण
पूर्ण

व्योम __init_or_module nospec_revert(s32 *start, s32 *end)
अणु
	अगर (nospec_disable)
		__nospec_revert(start, end);
पूर्ण

बाह्य s32 __nospec_call_start[], __nospec_call_end[];
बाह्य s32 __nospec_वापस_start[], __nospec_वापस_end[];
व्योम __init nospec_init_branches(व्योम)
अणु
	nospec_revert(__nospec_call_start, __nospec_call_end);
	nospec_revert(__nospec_वापस_start, __nospec_वापस_end);
पूर्ण

#पूर्ण_अगर /* CONFIG_EXPOLINE */
