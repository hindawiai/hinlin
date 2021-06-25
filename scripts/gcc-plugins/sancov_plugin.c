<शैली गुरु>
/*
 * Copyright 2011-2016 by Emese Revfy <re.emese@gmail.com>
 * Licensed under the GPL v2, or (at your option) v3
 *
 * Homepage:
 * https://github.com/ephox-gcc-plugins/sancov
 *
 * This plugin inserts a __sanitizer_cov_trace_pc() call at the start of basic blocks.
 * It supports all gcc versions with plugin support (from gcc-4.5 on).
 * It is based on the commit "Add fuzzing coverage support" by Dmitry Vyukov <dvyukov@google.com>.
 *
 * You can पढ़ो about it more here:
 *  https://gcc.gnu.org/viewcvs/gcc?limit_changes=0&view=revision&revision=231296
 *  https://lwn.net/Articles/674854/
 *  https://github.com/google/syzkaller
 *  https://lwn.net/Articles/677764/
 *
 * Usage:
 * make run
 */

#समावेश "gcc-common.h"

__visible पूर्णांक plugin_is_GPL_compatible;

tree sancov_fndecl;

अटल काष्ठा plugin_info sancov_plugin_info = अणु
	.version	= "20160402",
	.help		= "sancov plugin\n",
पूर्ण;

अटल अचिन्हित पूर्णांक sancov_execute(व्योम)
अणु
	basic_block bb;

	/* Remove this line when this plugin and kcov will be in the kernel.
	अगर (!म_भेद(DECL_NAME_POINTER(current_function_decl), DECL_NAME_POINTER(sancov_fndecl)))
		वापस 0;
	*/

	FOR_EACH_BB_FN(bb, cfun) अणु
		स्थिर_gimple sपंचांगt;
		gcall *gcall;
		gimple_sपंचांगt_iterator gsi = gsi_after_labels(bb);

		अगर (gsi_end_p(gsi))
			जारी;

		sपंचांगt = gsi_sपंचांगt(gsi);
		gcall = as_a_gcall(gimple_build_call(sancov_fndecl, 0));
		gimple_set_location(gcall, gimple_location(sपंचांगt));
		gsi_insert_beक्रमe(&gsi, gcall, GSI_SAME_STMT);
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा PASS_NAME sancov

#घोषणा NO_GATE
#घोषणा TODO_FLAGS_FINISH TODO_dump_func | TODO_verअगरy_sपंचांगts | TODO_update_ssa_no_phi | TODO_verअगरy_flow

#समावेश "gcc-generate-gimple-pass.h"

अटल व्योम sancov_start_unit(व्योम __unused *gcc_data, व्योम __unused *user_data)
अणु
	tree leaf_attr, nothrow_attr;
	tree BT_FN_VOID = build_function_type_list(व्योम_type_node, शून्य_TREE);

	sancov_fndecl = build_fn_decl("__sanitizer_cov_trace_pc", BT_FN_VOID);

	DECL_ASSEMBLER_NAME(sancov_fndecl);
	TREE_PUBLIC(sancov_fndecl) = 1;
	DECL_EXTERNAL(sancov_fndecl) = 1;
	DECL_ARTIFICIAL(sancov_fndecl) = 1;
	DECL_PRESERVE_P(sancov_fndecl) = 1;
	DECL_UNINLINABLE(sancov_fndecl) = 1;
	TREE_USED(sancov_fndecl) = 1;

	nothrow_attr = tree_cons(get_identअगरier("nothrow"), शून्य, शून्य);
	decl_attributes(&sancov_fndecl, nothrow_attr, 0);
	gcc_निश्चित(TREE_NOTHROW(sancov_fndecl));
	leaf_attr = tree_cons(get_identअगरier("leaf"), शून्य, शून्य);
	decl_attributes(&sancov_fndecl, leaf_attr, 0);
पूर्ण

__visible पूर्णांक plugin_init(काष्ठा plugin_name_args *plugin_info, काष्ठा plugin_gcc_version *version)
अणु
	पूर्णांक i;
	स्थिर अक्षर * स्थिर plugin_name = plugin_info->base_name;
	स्थिर पूर्णांक argc = plugin_info->argc;
	स्थिर काष्ठा plugin_argument * स्थिर argv = plugin_info->argv;
	bool enable = true;

	अटल स्थिर काष्ठा ggc_root_tab gt_ggc_r_gt_sancov[] = अणु
		अणु
			.base = &sancov_fndecl,
			.nelt = 1,
			.stride = माप(sancov_fndecl),
			.cb = &gt_ggc_mx_tree_node,
			.pchw = &gt_pch_nx_tree_node
		पूर्ण,
		LAST_GGC_ROOT_TAB
	पूर्ण;

	/* BBs can be split afterwards?? */
	PASS_INFO(sancov, "asan", 0, PASS_POS_INSERT_BEFORE);

	अगर (!plugin_शेष_version_check(version, &gcc_version)) अणु
		error(G_("incompatible gcc/plugin versions"));
		वापस 1;
	पूर्ण

	क्रम (i = 0; i < argc; ++i) अणु
		अगर (!म_भेद(argv[i].key, "no-sancov")) अणु
			enable = false;
			जारी;
		पूर्ण
		error(G_("unknown option '-fplugin-arg-%s-%s'"), plugin_name, argv[i].key);
	पूर्ण

	रेजिस्टर_callback(plugin_name, PLUGIN_INFO, शून्य, &sancov_plugin_info);

	अगर (!enable)
		वापस 0;

#अगर BUILDING_GCC_VERSION < 6000
	रेजिस्टर_callback(plugin_name, PLUGIN_START_UNIT, &sancov_start_unit, शून्य);
	रेजिस्टर_callback(plugin_name, PLUGIN_REGISTER_GGC_ROOTS, शून्य, (व्योम *)&gt_ggc_r_gt_sancov);
	रेजिस्टर_callback(plugin_name, PLUGIN_PASS_MANAGER_SETUP, शून्य, &sancov_pass_info);
#पूर्ण_अगर

	वापस 0;
पूर्ण
