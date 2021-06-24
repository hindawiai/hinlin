<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश "gcc-common.h"

__visible पूर्णांक plugin_is_GPL_compatible;

अटल अचिन्हित पूर्णांक sp_mask, canary_offset;

अटल अचिन्हित पूर्णांक arm_pertask_ssp_rtl_execute(व्योम)
अणु
	rtx_insn *insn;

	क्रम (insn = get_insns(); insn; insn = NEXT_INSN(insn)) अणु
		स्थिर अक्षर *sym;
		rtx body;
		rtx mask, masked_sp;

		/*
		 * Find a SET insn involving a SYMBOL_REF to __stack_chk_guard
		 */
		अगर (!INSN_P(insn))
			जारी;
		body = PATTERN(insn);
		अगर (GET_CODE(body) != SET ||
		    GET_CODE(SET_SRC(body)) != SYMBOL_REF)
			जारी;
		sym = XSTR(SET_SRC(body), 0);
		अगर (म_भेद(sym, "__stack_chk_guard"))
			जारी;

		/*
		 * Replace the source of the SET insn with an expression that
		 * produces the address of the copy of the stack canary value
		 * stored in काष्ठा thपढ़ो_info
		 */
		mask = GEN_INT(sext_hwi(sp_mask, GET_MODE_PRECISION(Pmode)));
		masked_sp = gen_reg_rtx(Pmode);

		emit_insn_beक्रमe(gen_rtx_set(masked_sp,
					     gen_rtx_AND(Pmode,
							 stack_poपूर्णांकer_rtx,
							 mask)),
				 insn);

		SET_SRC(body) = gen_rtx_PLUS(Pmode, masked_sp,
					     GEN_INT(canary_offset));
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा PASS_NAME arm_pertask_ssp_rtl

#घोषणा NO_GATE
#समावेश "gcc-generate-rtl-pass.h"

#अगर BUILDING_GCC_VERSION >= 9000
अटल bool no(व्योम)
अणु
	वापस false;
पूर्ण

अटल व्योम arm_pertask_ssp_start_unit(व्योम *gcc_data, व्योम *user_data)
अणु
	targeपंचांग.have_stack_protect_combined_set = no;
	targeपंचांग.have_stack_protect_combined_test = no;
पूर्ण
#पूर्ण_अगर

__visible पूर्णांक plugin_init(काष्ठा plugin_name_args *plugin_info,
			  काष्ठा plugin_gcc_version *version)
अणु
	स्थिर अक्षर * स्थिर plugin_name = plugin_info->base_name;
	स्थिर पूर्णांक argc = plugin_info->argc;
	स्थिर काष्ठा plugin_argument *argv = plugin_info->argv;
	पूर्णांक tso = 0;
	पूर्णांक i;

	अगर (!plugin_शेष_version_check(version, &gcc_version)) अणु
		error(G_("incompatible gcc/plugin versions"));
		वापस 1;
	पूर्ण

	क्रम (i = 0; i < argc; ++i) अणु
		अगर (!म_भेद(argv[i].key, "disable"))
			वापस 0;

		/* all reमुख्यing options require a value */
		अगर (!argv[i].value) अणु
			error(G_("no value supplied for option '-fplugin-arg-%s-%s'"),
			      plugin_name, argv[i].key);
			वापस 1;
		पूर्ण

		अगर (!म_भेद(argv[i].key, "tso")) अणु
			tso = म_से_प(argv[i].value);
			जारी;
		पूर्ण

		अगर (!म_भेद(argv[i].key, "offset")) अणु
			canary_offset = म_से_प(argv[i].value);
			जारी;
		पूर्ण
		error(G_("unknown option '-fplugin-arg-%s-%s'"),
		      plugin_name, argv[i].key);
		वापस 1;
	पूर्ण

	/* create the mask that produces the base of the stack */
	sp_mask = ~((1U << (12 + tso)) - 1);

	PASS_INFO(arm_pertask_ssp_rtl, "expand", 1, PASS_POS_INSERT_AFTER);

	रेजिस्टर_callback(plugin_info->base_name, PLUGIN_PASS_MANAGER_SETUP,
			  शून्य, &arm_pertask_ssp_rtl_pass_info);

#अगर BUILDING_GCC_VERSION >= 9000
	रेजिस्टर_callback(plugin_info->base_name, PLUGIN_START_UNIT,
			  arm_pertask_ssp_start_unit, शून्य);
#पूर्ण_अगर

	वापस 0;
पूर्ण
