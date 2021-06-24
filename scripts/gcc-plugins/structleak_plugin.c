<शैली गुरु>
/*
 * Copyright 2013-2017 by PaX Team <pageexec@मुक्तmail.hu>
 * Licensed under the GPL v2
 *
 * Note: the choice of the license means that the compilation process is
 *       NOT 'eligible' as defined by gcc's library exception to the GPL v3,
 *       but क्रम the kernel it करोesn't matter since it doesn't link against
 *       any of the gcc libraries
 *
 * gcc plugin to क्रमcibly initialize certain local variables that could
 * otherwise leak kernel stack to userland अगर they aren't properly initialized
 * by later code
 *
 * Homepage: https://pax.grsecurity.net/
 *
 * Options:
 * -fplugin-arg-काष्ठाleak_plugin-disable
 * -fplugin-arg-काष्ठाleak_plugin-verbose
 * -fplugin-arg-काष्ठाleak_plugin-byref
 * -fplugin-arg-काष्ठाleak_plugin-byref-all
 *
 * Usage:
 * $ # क्रम 4.5/4.6/C based 4.7
 * $ gcc -I`gcc -prपूर्णांक-file-name=plugin`/include -I`gcc -prपूर्णांक-file-name=plugin`/include/c-family -fPIC -shared -O2 -o काष्ठाleak_plugin.so काष्ठाleak_plugin.c
 * $ # क्रम C++ based 4.7/4.8+
 * $ g++ -I`g++ -prपूर्णांक-file-name=plugin`/include -I`g++ -prपूर्णांक-file-name=plugin`/include/c-family -fPIC -shared -O2 -o काष्ठाleak_plugin.so काष्ठाleak_plugin.c
 * $ gcc -fplugin=./काष्ठाleak_plugin.so test.c -O2
 *
 * TODO: eliminate redundant initializers
 */

#समावेश "gcc-common.h"

/* unused C type flag in all versions 4.5-6 */
#घोषणा TYPE_USERSPACE(TYPE) TYPE_LANG_FLAG_5(TYPE)

__visible पूर्णांक plugin_is_GPL_compatible;

अटल काष्ठा plugin_info काष्ठाleak_plugin_info = अणु
	.version	= "20190125vanilla",
	.help		= "disable\tdo not activate plugin\n"
			  "byref\tinit structs passed by reference\n"
			  "byref-all\tinit anything passed by reference\n"
			  "verbose\tprint all initialized variables\n",
पूर्ण;

#घोषणा BYREF_STRUCT	1
#घोषणा BYREF_ALL	2

अटल bool verbose;
अटल पूर्णांक byref;

अटल tree handle_user_attribute(tree *node, tree name, tree args, पूर्णांक flags, bool *no_add_attrs)
अणु
	*no_add_attrs = true;

	/* check क्रम types? क्रम now accept everything linux has to offer */
	अगर (TREE_CODE(*node) != FIELD_DECL)
		वापस शून्य_TREE;

	*no_add_attrs = false;
	वापस शून्य_TREE;
पूर्ण

अटल काष्ठा attribute_spec user_attr = अणु पूर्ण;

अटल व्योम रेजिस्टर_attributes(व्योम *event_data, व्योम *data)
अणु
	user_attr.name			= "user";
	user_attr.handler		= handle_user_attribute;
	user_attr.affects_type_identity	= true;

	रेजिस्टर_attribute(&user_attr);
पूर्ण

अटल tree get_field_type(tree field)
अणु
	वापस strip_array_types(TREE_TYPE(field));
पूर्ण

अटल bool is_userspace_type(tree type)
अणु
	tree field;

	क्रम (field = TYPE_FIELDS(type); field; field = TREE_CHAIN(field)) अणु
		tree fieldtype = get_field_type(field);
		क्रमागत tree_code code = TREE_CODE(fieldtype);

		अगर (code == RECORD_TYPE || code == UNION_TYPE)
			अगर (is_userspace_type(fieldtype))
				वापस true;

		अगर (lookup_attribute("user", DECL_ATTRIBUTES(field)))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम finish_type(व्योम *event_data, व्योम *data)
अणु
	tree type = (tree)event_data;

	अगर (type == शून्य_TREE || type == error_mark_node)
		वापस;

#अगर BUILDING_GCC_VERSION >= 5000
	अगर (TREE_CODE(type) == ENUMERAL_TYPE)
		वापस;
#पूर्ण_अगर

	अगर (TYPE_USERSPACE(type))
		वापस;

	अगर (is_userspace_type(type))
		TYPE_USERSPACE(type) = 1;
पूर्ण

अटल व्योम initialize(tree var)
अणु
	basic_block bb;
	gimple_sपंचांगt_iterator gsi;
	tree initializer;
	gimple init_sपंचांगt;
	tree type;

	/* this is the original entry bb beक्रमe the क्रमced split */
	bb = single_succ(ENTRY_BLOCK_PTR_FOR_FN(cfun));

	/* first check अगर variable is alपढ़ोy initialized, warn otherwise */
	क्रम (gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi)) अणु
		gimple sपंचांगt = gsi_sपंचांगt(gsi);
		tree rhs1;

		/* we're looking क्रम an assignment of a single rhs... */
		अगर (!gimple_assign_single_p(sपंचांगt))
			जारी;
		rhs1 = gimple_assign_rhs1(sपंचांगt);
		/* ... of a non-clobbering expression... */
		अगर (TREE_CLOBBER_P(rhs1))
			जारी;
		/* ... to our variable... */
		अगर (gimple_get_lhs(sपंचांगt) != var)
			जारी;
		/* अगर it's an initializer then we're good */
		अगर (TREE_CODE(rhs1) == CONSTRUCTOR)
			वापस;
	पूर्ण

	/* these aren't the 0days you're looking क्रम */
	अगर (verbose)
		inक्रमm(DECL_SOURCE_LOCATION(var),
			"%s variable will be forcibly initialized",
			(byref && TREE_ADDRESSABLE(var)) ? "byref"
							 : "userspace");

	/* build the initializer expression */
	type = TREE_TYPE(var);
	अगर (AGGREGATE_TYPE_P(type))
		initializer = build_स्थिरructor(type, शून्य);
	अन्यथा
		initializer = fold_convert(type, पूर्णांकeger_zero_node);

	/* build the initializer sपंचांगt */
	init_sपंचांगt = gimple_build_assign(var, initializer);
	gsi = gsi_after_labels(single_succ(ENTRY_BLOCK_PTR_FOR_FN(cfun)));
	gsi_insert_beक्रमe(&gsi, init_sपंचांगt, GSI_NEW_STMT);
	update_sपंचांगt(init_sपंचांगt);
पूर्ण

अटल अचिन्हित पूर्णांक काष्ठाleak_execute(व्योम)
अणु
	basic_block bb;
	tree var;
	अचिन्हित पूर्णांक i;

	/* split the first bb where we can put the क्रमced initializers */
	gcc_निश्चित(single_succ_p(ENTRY_BLOCK_PTR_FOR_FN(cfun)));
	bb = single_succ(ENTRY_BLOCK_PTR_FOR_FN(cfun));
	अगर (!single_pred_p(bb)) अणु
		split_edge(single_succ_edge(ENTRY_BLOCK_PTR_FOR_FN(cfun)));
		gcc_निश्चित(single_succ_p(ENTRY_BLOCK_PTR_FOR_FN(cfun)));
	पूर्ण

	/* क्रमागतerate all local variables and क्रमcibly initialize our tarमाला_लो */
	FOR_EACH_LOCAL_DECL(cfun, i, var) अणु
		tree type = TREE_TYPE(var);

		gcc_निश्चित(DECL_P(var));
		अगर (!स्वतः_var_in_fn_p(var, current_function_decl))
			जारी;

		/* only care about काष्ठाure types unless byref-all */
		अगर (byref != BYREF_ALL && TREE_CODE(type) != RECORD_TYPE && TREE_CODE(type) != UNION_TYPE)
			जारी;

		/* अगर the type is of पूर्णांकerest, examine the variable */
		अगर (TYPE_USERSPACE(type) ||
		    (byref && TREE_ADDRESSABLE(var)))
			initialize(var);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा PASS_NAME काष्ठाleak
#घोषणा NO_GATE
#घोषणा PROPERTIES_REQUIRED PROP_cfg
#घोषणा TODO_FLAGS_FINISH TODO_verअगरy_il | TODO_verअगरy_ssa | TODO_verअगरy_sपंचांगts | TODO_dump_func | TODO_हटाओ_unused_locals | TODO_update_ssa | TODO_ggc_collect | TODO_verअगरy_flow
#समावेश "gcc-generate-gimple-pass.h"

__visible पूर्णांक plugin_init(काष्ठा plugin_name_args *plugin_info, काष्ठा plugin_gcc_version *version)
अणु
	पूर्णांक i;
	स्थिर अक्षर * स्थिर plugin_name = plugin_info->base_name;
	स्थिर पूर्णांक argc = plugin_info->argc;
	स्थिर काष्ठा plugin_argument * स्थिर argv = plugin_info->argv;
	bool enable = true;

	PASS_INFO(काष्ठाleak, "early_optimizations", 1, PASS_POS_INSERT_BEFORE);

	अगर (!plugin_शेष_version_check(version, &gcc_version)) अणु
		error(G_("incompatible gcc/plugin versions"));
		वापस 1;
	पूर्ण

	अगर (म_भेदन(lang_hooks.name, "GNU C", 5) && !म_भेदन(lang_hooks.name, "GNU C+", 6)) अणु
		inक्रमm(UNKNOWN_LOCATION, G_("%s supports C only, not %s"), plugin_name, lang_hooks.name);
		enable = false;
	पूर्ण

	क्रम (i = 0; i < argc; ++i) अणु
		अगर (!म_भेद(argv[i].key, "disable")) अणु
			enable = false;
			जारी;
		पूर्ण
		अगर (!म_भेद(argv[i].key, "verbose")) अणु
			verbose = true;
			जारी;
		पूर्ण
		अगर (!म_भेद(argv[i].key, "byref")) अणु
			byref = BYREF_STRUCT;
			जारी;
		पूर्ण
		अगर (!म_भेद(argv[i].key, "byref-all")) अणु
			byref = BYREF_ALL;
			जारी;
		पूर्ण
		error(G_("unknown option '-fplugin-arg-%s-%s'"), plugin_name, argv[i].key);
	पूर्ण

	रेजिस्टर_callback(plugin_name, PLUGIN_INFO, शून्य, &काष्ठाleak_plugin_info);
	अगर (enable) अणु
		रेजिस्टर_callback(plugin_name, PLUGIN_PASS_MANAGER_SETUP, शून्य, &काष्ठाleak_pass_info);
		रेजिस्टर_callback(plugin_name, PLUGIN_FINISH_TYPE, finish_type, शून्य);
	पूर्ण
	रेजिस्टर_callback(plugin_name, PLUGIN_ATTRIBUTES, रेजिस्टर_attributes, शून्य);

	वापस 0;
पूर्ण
