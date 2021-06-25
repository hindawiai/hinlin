<शैली गुरु>
/*
 * Copyright 2012-2016 by the PaX Team <pageexec@मुक्तmail.hu>
 * Copyright 2016 by Emese Revfy <re.emese@gmail.com>
 * Licensed under the GPL v2
 *
 * Note: the choice of the license means that the compilation process is
 *       NOT 'eligible' as defined by gcc's library exception to the GPL v3,
 *       but क्रम the kernel it करोesn't matter since it doesn't link against
 *       any of the gcc libraries
 *
 * This gcc plugin helps generate a little bit of entropy from program state,
 * used throughout the upसमय of the kernel. Here is an instrumentation example:
 *
 * beक्रमe:
 * व्योम __latent_entropy test(पूर्णांक argc, अक्षर *argv[])
 * अणु
 *	अगर (argc <= 1)
 *		म_लिखो("%s: no command arguments :(\n", *argv);
 *	अन्यथा
 *		म_लिखो("%s: %d command arguments!\n", *argv, args - 1);
 * पूर्ण
 *
 * after:
 * व्योम __latent_entropy test(पूर्णांक argc, अक्षर *argv[])
 * अणु
 *	// latent_entropy_execute() 1.
 *	अचिन्हित दीर्घ local_entropy;
 *	// init_local_entropy() 1.
 *	व्योम *local_entropy_frameaddr;
 *	// init_local_entropy() 3.
 *	अचिन्हित दीर्घ पंचांगp_latent_entropy;
 *
 *	// init_local_entropy() 2.
 *	local_entropy_frameaddr = __builtin_frame_address(0);
 *	local_entropy = (अचिन्हित दीर्घ) local_entropy_frameaddr;
 *
 *	// init_local_entropy() 4.
 *	पंचांगp_latent_entropy = latent_entropy;
 *	// init_local_entropy() 5.
 *	local_entropy ^= पंचांगp_latent_entropy;
 *
 *	// latent_entropy_execute() 3.
 *	अगर (argc <= 1) अणु
 *		// perturb_local_entropy()
 *		local_entropy += 4623067384293424948;
 *		म_लिखो("%s: no command arguments :(\n", *argv);
 *		// perturb_local_entropy()
 *	पूर्ण अन्यथा अणु
 *		local_entropy ^= 3896280633962944730;
 *		म_लिखो("%s: %d command arguments!\n", *argv, args - 1);
 *	पूर्ण
 *
 *	// latent_entropy_execute() 4.
 *	पंचांगp_latent_entropy = rol(पंचांगp_latent_entropy, local_entropy);
 *	latent_entropy = पंचांगp_latent_entropy;
 * पूर्ण
 *
 * TODO:
 * - add ipa pass to identअगरy not explicitly marked candidate functions
 * - mix in more program state (function arguments/वापस values,
 *   loop variables, etc)
 * - more instrumentation control via attribute parameters
 *
 * BUGS:
 * - none known
 *
 * Options:
 * -fplugin-arg-latent_entropy_plugin-disable
 *
 * Attribute: __attribute__((latent_entropy))
 *  The latent_entropy gcc attribute can be only on functions and variables.
 *  If it is on a function then the plugin will instrument it. If the attribute
 *  is on a variable then the plugin will initialize it with a अक्रमom value.
 *  The variable must be an पूर्णांकeger, an पूर्णांकeger array type or a काष्ठाure
 *  with पूर्णांकeger fields.
 */

#समावेश "gcc-common.h"

__visible पूर्णांक plugin_is_GPL_compatible;

अटल GTY(()) tree latent_entropy_decl;

अटल काष्ठा plugin_info latent_entropy_plugin_info = अणु
	.version	= "201606141920vanilla",
	.help		= "disable\tturn off latent entropy instrumentation\n",
पूर्ण;

अटल अचिन्हित HOST_WIDE_INT seed;
/*
 * get_अक्रमom_seed() (this is a GCC function) generates the seed.
 * This is a simple अक्रमom generator without any cryptographic security because
 * the entropy करोesn't come from here.
 */
अटल अचिन्हित HOST_WIDE_INT get_अक्रमom_स्थिर(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित HOST_WIDE_INT ret = 0;

	क्रम (i = 0; i < 8 * माप(ret); i++) अणु
		ret = (ret << 1) | (seed & 1);
		seed >>= 1;
		अगर (ret & 1)
			seed ^= 0xD800000000000000ULL;
	पूर्ण

	वापस ret;
पूर्ण

अटल tree tree_get_अक्रमom_स्थिर(tree type)
अणु
	अचिन्हित दीर्घ दीर्घ mask;

	mask = 1ULL << (TREE_INT_CST_LOW(TYPE_SIZE(type)) - 1);
	mask = 2 * (mask - 1) + 1;

	अगर (TYPE_UNSIGNED(type))
		वापस build_पूर्णांक_cstu(type, mask & get_अक्रमom_स्थिर());
	वापस build_पूर्णांक_cst(type, mask & get_अक्रमom_स्थिर());
पूर्ण

अटल tree handle_latent_entropy_attribute(tree *node, tree name,
						tree args __unused,
						पूर्णांक flags __unused,
						bool *no_add_attrs)
अणु
	tree type;
	vec<स्थिरructor_elt, va_gc> *vals;

	चयन (TREE_CODE(*node)) अणु
	शेष:
		*no_add_attrs = true;
		error("%qE attribute only applies to functions and variables",
			name);
		अवरोध;

	हाल VAR_DECL:
		अगर (DECL_INITIAL(*node)) अणु
			*no_add_attrs = true;
			error("variable %qD with %qE attribute must not be initialized",
				*node, name);
			अवरोध;
		पूर्ण

		अगर (!TREE_STATIC(*node)) अणु
			*no_add_attrs = true;
			error("variable %qD with %qE attribute must not be local",
				*node, name);
			अवरोध;
		पूर्ण

		type = TREE_TYPE(*node);
		चयन (TREE_CODE(type)) अणु
		शेष:
			*no_add_attrs = true;
			error("variable %qD with %qE attribute must be an integer or a fixed length integer array type or a fixed sized structure with integer fields",
				*node, name);
			अवरोध;

		हाल RECORD_TYPE: अणु
			tree fld, lst = TYPE_FIELDS(type);
			अचिन्हित पूर्णांक nelt = 0;

			क्रम (fld = lst; fld; nelt++, fld = TREE_CHAIN(fld)) अणु
				tree fieldtype;

				fieldtype = TREE_TYPE(fld);
				अगर (TREE_CODE(fieldtype) == INTEGER_TYPE)
					जारी;

				*no_add_attrs = true;
				error("structure variable %qD with %qE attribute has a non-integer field %qE",
					*node, name, fld);
				अवरोध;
			पूर्ण

			अगर (fld)
				अवरोध;

			vec_alloc(vals, nelt);

			क्रम (fld = lst; fld; fld = TREE_CHAIN(fld)) अणु
				tree अक्रमom_स्थिर, fld_t = TREE_TYPE(fld);

				अक्रमom_स्थिर = tree_get_अक्रमom_स्थिर(fld_t);
				CONSTRUCTOR_APPEND_ELT(vals, fld, अक्रमom_स्थिर);
			पूर्ण

			/* Initialize the fields with अक्रमom स्थिरants */
			DECL_INITIAL(*node) = build_स्थिरructor(type, vals);
			अवरोध;
		पूर्ण

		/* Initialize the variable with a अक्रमom स्थिरant */
		हाल INTEGER_TYPE:
			DECL_INITIAL(*node) = tree_get_अक्रमom_स्थिर(type);
			अवरोध;

		हाल ARRAY_TYPE: अणु
			tree elt_type, array_size, elt_size;
			अचिन्हित पूर्णांक i, nelt;
			HOST_WIDE_INT array_size_पूर्णांक, elt_size_पूर्णांक;

			elt_type = TREE_TYPE(type);
			elt_size = TYPE_SIZE_UNIT(TREE_TYPE(type));
			array_size = TYPE_SIZE_UNIT(type);

			अगर (TREE_CODE(elt_type) != INTEGER_TYPE || !array_size
				|| TREE_CODE(array_size) != INTEGER_CST) अणु
				*no_add_attrs = true;
				error("array variable %qD with %qE attribute must be a fixed length integer array type",
					*node, name);
				अवरोध;
			पूर्ण

			array_size_पूर्णांक = TREE_INT_CST_LOW(array_size);
			elt_size_पूर्णांक = TREE_INT_CST_LOW(elt_size);
			nelt = array_size_पूर्णांक / elt_size_पूर्णांक;

			vec_alloc(vals, nelt);

			क्रम (i = 0; i < nelt; i++) अणु
				tree cst = size_पूर्णांक(i);
				tree अक्रम_cst = tree_get_अक्रमom_स्थिर(elt_type);

				CONSTRUCTOR_APPEND_ELT(vals, cst, अक्रम_cst);
			पूर्ण

			/*
			 * Initialize the elements of the array with अक्रमom
			 * स्थिरants
			 */
			DECL_INITIAL(*node) = build_स्थिरructor(type, vals);
			अवरोध;
		पूर्ण
		पूर्ण
		अवरोध;

	हाल FUNCTION_DECL:
		अवरोध;
	पूर्ण

	वापस शून्य_TREE;
पूर्ण

अटल काष्ठा attribute_spec latent_entropy_attr = अणु पूर्ण;

अटल व्योम रेजिस्टर_attributes(व्योम *event_data __unused, व्योम *data __unused)
अणु
	latent_entropy_attr.name		= "latent_entropy";
	latent_entropy_attr.decl_required	= true;
	latent_entropy_attr.handler		= handle_latent_entropy_attribute;

	रेजिस्टर_attribute(&latent_entropy_attr);
पूर्ण

अटल bool latent_entropy_gate(व्योम)
अणु
	tree list;

	/* करोn't bother with noवापस functions क्रम now */
	अगर (TREE_THIS_VOLATILE(current_function_decl))
		वापस false;

	/* gcc-4.5 करोesn't discover some trivial noवापस functions */
	अगर (EDGE_COUNT(EXIT_BLOCK_PTR_FOR_FN(cfun)->preds) == 0)
		वापस false;

	list = DECL_ATTRIBUTES(current_function_decl);
	वापस lookup_attribute("latent_entropy", list) != शून्य_TREE;
पूर्ण

अटल tree create_var(tree type, स्थिर अक्षर *name)
अणु
	tree var;

	var = create_पंचांगp_var(type, name);
	add_referenced_var(var);
	mark_sym_क्रम_renaming(var);
	वापस var;
पूर्ण

/*
 * Set up the next operation and its स्थिरant opeअक्रम to use in the latent
 * entropy PRNG. When RHS is specअगरied, the request is क्रम perturbing the
 * local latent entropy variable, otherwise it is क्रम perturbing the global
 * latent entropy variable where the two opeअक्रमs are alपढ़ोy given by the
 * local and global latent entropy variables themselves.
 *
 * The operation is one of add/xor/rol when instrumenting the local entropy
 * variable and one of add/xor when perturbing the global entropy variable.
 * Rotation is not used क्रम the latter हाल because it would transmit less
 * entropy to the global variable than the other two operations.
 */
अटल क्रमागत tree_code get_op(tree *rhs)
अणु
	अटल क्रमागत tree_code op;
	अचिन्हित HOST_WIDE_INT अक्रमom_स्थिर;

	अक्रमom_स्थिर = get_अक्रमom_स्थिर();

	चयन (op) अणु
	हाल BIT_XOR_EXPR:
		op = PLUS_EXPR;
		अवरोध;

	हाल PLUS_EXPR:
		अगर (rhs) अणु
			op = LROTATE_EXPR;
			/*
			 * This code limits the value of अक्रमom_स्थिर to
			 * the size of a दीर्घ क्रम the rotation
			 */
			अक्रमom_स्थिर %= TYPE_PRECISION(दीर्घ_अचिन्हित_type_node);
			अवरोध;
		पूर्ण

	हाल LROTATE_EXPR:
	शेष:
		op = BIT_XOR_EXPR;
		अवरोध;
	पूर्ण
	अगर (rhs)
		*rhs = build_पूर्णांक_cstu(दीर्घ_अचिन्हित_type_node, अक्रमom_स्थिर);
	वापस op;
पूर्ण

अटल gimple create_assign(क्रमागत tree_code code, tree lhs, tree op1,
				tree op2)
अणु
	वापस gimple_build_assign_with_ops(code, lhs, op1, op2);
पूर्ण

अटल व्योम perturb_local_entropy(basic_block bb, tree local_entropy)
अणु
	gimple_sपंचांगt_iterator gsi;
	gimple assign;
	tree rhs;
	क्रमागत tree_code op;

	op = get_op(&rhs);
	assign = create_assign(op, local_entropy, local_entropy, rhs);
	gsi = gsi_after_labels(bb);
	gsi_insert_beक्रमe(&gsi, assign, GSI_NEW_STMT);
	update_sपंचांगt(assign);
पूर्ण

अटल व्योम __perturb_latent_entropy(gimple_sपंचांगt_iterator *gsi,
					tree local_entropy)
अणु
	gimple assign;
	tree temp;
	क्रमागत tree_code op;

	/* 1. create temporary copy of latent_entropy */
	temp = create_var(दीर्घ_अचिन्हित_type_node, "temp_latent_entropy");

	/* 2. पढ़ो... */
	add_referenced_var(latent_entropy_decl);
	mark_sym_क्रम_renaming(latent_entropy_decl);
	assign = gimple_build_assign(temp, latent_entropy_decl);
	gsi_insert_beक्रमe(gsi, assign, GSI_NEW_STMT);
	update_sपंचांगt(assign);

	/* 3. ...modअगरy... */
	op = get_op(शून्य);
	assign = create_assign(op, temp, temp, local_entropy);
	gsi_insert_after(gsi, assign, GSI_NEW_STMT);
	update_sपंचांगt(assign);

	/* 4. ...ग_लिखो latent_entropy */
	assign = gimple_build_assign(latent_entropy_decl, temp);
	gsi_insert_after(gsi, assign, GSI_NEW_STMT);
	update_sपंचांगt(assign);
पूर्ण

अटल bool handle_tail_calls(basic_block bb, tree local_entropy)
अणु
	gimple_sपंचांगt_iterator gsi;

	क्रम (gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi)) अणु
		gcall *call;
		gimple sपंचांगt = gsi_sपंचांगt(gsi);

		अगर (!is_gimple_call(sपंचांगt))
			जारी;

		call = as_a_gcall(sपंचांगt);
		अगर (!gimple_call_tail_p(call))
			जारी;

		__perturb_latent_entropy(&gsi, local_entropy);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम perturb_latent_entropy(tree local_entropy)
अणु
	edge_iterator ei;
	edge e, last_bb_e;
	basic_block last_bb;

	gcc_निश्चित(single_pred_p(EXIT_BLOCK_PTR_FOR_FN(cfun)));
	last_bb_e = single_pred_edge(EXIT_BLOCK_PTR_FOR_FN(cfun));

	FOR_EACH_EDGE(e, ei, last_bb_e->src->preds) अणु
		अगर (ENTRY_BLOCK_PTR_FOR_FN(cfun) == e->src)
			जारी;
		अगर (EXIT_BLOCK_PTR_FOR_FN(cfun) == e->src)
			जारी;

		handle_tail_calls(e->src, local_entropy);
	पूर्ण

	last_bb = single_pred(EXIT_BLOCK_PTR_FOR_FN(cfun));
	अगर (!handle_tail_calls(last_bb, local_entropy)) अणु
		gimple_sपंचांगt_iterator gsi = gsi_last_bb(last_bb);

		__perturb_latent_entropy(&gsi, local_entropy);
	पूर्ण
पूर्ण

अटल व्योम init_local_entropy(basic_block bb, tree local_entropy)
अणु
	gimple assign, call;
	tree frame_addr, अक्रम_स्थिर, पंचांगp, fndecl, udi_frame_addr;
	क्रमागत tree_code op;
	अचिन्हित HOST_WIDE_INT अक्रम_cst;
	gimple_sपंचांगt_iterator gsi = gsi_after_labels(bb);

	/* 1. create local_entropy_frameaddr */
	frame_addr = create_var(ptr_type_node, "local_entropy_frameaddr");

	/* 2. local_entropy_frameaddr = __builtin_frame_address() */
	fndecl = builtin_decl_implicit(BUILT_IN_FRAME_ADDRESS);
	call = gimple_build_call(fndecl, 1, पूर्णांकeger_zero_node);
	gimple_call_set_lhs(call, frame_addr);
	gsi_insert_beक्रमe(&gsi, call, GSI_NEW_STMT);
	update_sपंचांगt(call);

	udi_frame_addr = fold_convert(दीर्घ_अचिन्हित_type_node, frame_addr);
	assign = gimple_build_assign(local_entropy, udi_frame_addr);
	gsi_insert_after(&gsi, assign, GSI_NEW_STMT);
	update_sपंचांगt(assign);

	/* 3. create temporary copy of latent_entropy */
	पंचांगp = create_var(दीर्घ_अचिन्हित_type_node, "temp_latent_entropy");

	/* 4. पढ़ो the global entropy variable पूर्णांकo local entropy */
	add_referenced_var(latent_entropy_decl);
	mark_sym_क्रम_renaming(latent_entropy_decl);
	assign = gimple_build_assign(पंचांगp, latent_entropy_decl);
	gsi_insert_after(&gsi, assign, GSI_NEW_STMT);
	update_sपंचांगt(assign);

	/* 5. mix local_entropy_frameaddr पूर्णांकo local entropy */
	assign = create_assign(BIT_XOR_EXPR, local_entropy, local_entropy, पंचांगp);
	gsi_insert_after(&gsi, assign, GSI_NEW_STMT);
	update_sपंचांगt(assign);

	अक्रम_cst = get_अक्रमom_स्थिर();
	अक्रम_स्थिर = build_पूर्णांक_cstu(दीर्घ_अचिन्हित_type_node, अक्रम_cst);
	op = get_op(शून्य);
	assign = create_assign(op, local_entropy, local_entropy, अक्रम_स्थिर);
	gsi_insert_after(&gsi, assign, GSI_NEW_STMT);
	update_sपंचांगt(assign);
पूर्ण

अटल bool create_latent_entropy_decl(व्योम)
अणु
	varpool_node_ptr node;

	अगर (latent_entropy_decl != शून्य_TREE)
		वापस true;

	FOR_EACH_VARIABLE(node) अणु
		tree name, var = NODE_DECL(node);

		अगर (DECL_NAME_LENGTH(var) < माप("latent_entropy") - 1)
			जारी;

		name = DECL_NAME(var);
		अगर (म_भेद(IDENTIFIER_POINTER(name), "latent_entropy"))
			जारी;

		latent_entropy_decl = var;
		अवरोध;
	पूर्ण

	वापस latent_entropy_decl != शून्य_TREE;
पूर्ण

अटल अचिन्हित पूर्णांक latent_entropy_execute(व्योम)
अणु
	basic_block bb;
	tree local_entropy;

	अगर (!create_latent_entropy_decl())
		वापस 0;

	/* prepare क्रम step 2 below */
	gcc_निश्चित(single_succ_p(ENTRY_BLOCK_PTR_FOR_FN(cfun)));
	bb = single_succ(ENTRY_BLOCK_PTR_FOR_FN(cfun));
	अगर (!single_pred_p(bb)) अणु
		split_edge(single_succ_edge(ENTRY_BLOCK_PTR_FOR_FN(cfun)));
		gcc_निश्चित(single_succ_p(ENTRY_BLOCK_PTR_FOR_FN(cfun)));
		bb = single_succ(ENTRY_BLOCK_PTR_FOR_FN(cfun));
	पूर्ण

	/* 1. create the local entropy variable */
	local_entropy = create_var(दीर्घ_अचिन्हित_type_node, "local_entropy");

	/* 2. initialize the local entropy variable */
	init_local_entropy(bb, local_entropy);

	bb = bb->next_bb;

	/*
	 * 3. instrument each BB with an operation on the
	 *    local entropy variable
	 */
	जबतक (bb != EXIT_BLOCK_PTR_FOR_FN(cfun)) अणु
		perturb_local_entropy(bb, local_entropy);
		bb = bb->next_bb;
	पूर्ण

	/* 4. mix local entropy पूर्णांकo the global entropy variable */
	perturb_latent_entropy(local_entropy);
	वापस 0;
पूर्ण

अटल व्योम latent_entropy_start_unit(व्योम *gcc_data __unused,
					व्योम *user_data __unused)
अणु
	tree type, id;
	पूर्णांक quals;

	seed = get_अक्रमom_seed(false);

	अगर (in_lto_p)
		वापस;

	/* बाह्य अस्थिर अचिन्हित दीर्घ latent_entropy */
	quals = TYPE_QUALS(दीर्घ_अचिन्हित_type_node) | TYPE_QUAL_VOLATILE;
	type = build_qualअगरied_type(दीर्घ_अचिन्हित_type_node, quals);
	id = get_identअगरier("latent_entropy");
	latent_entropy_decl = build_decl(UNKNOWN_LOCATION, VAR_DECL, id, type);

	TREE_STATIC(latent_entropy_decl) = 1;
	TREE_PUBLIC(latent_entropy_decl) = 1;
	TREE_USED(latent_entropy_decl) = 1;
	DECL_PRESERVE_P(latent_entropy_decl) = 1;
	TREE_THIS_VOLATILE(latent_entropy_decl) = 1;
	DECL_EXTERNAL(latent_entropy_decl) = 1;
	DECL_ARTIFICIAL(latent_entropy_decl) = 1;
	lang_hooks.decls.pushdecl(latent_entropy_decl);
पूर्ण

#घोषणा PASS_NAME latent_entropy
#घोषणा PROPERTIES_REQUIRED PROP_gimple_leh | PROP_cfg
#घोषणा TODO_FLAGS_FINISH TODO_verअगरy_ssa | TODO_verअगरy_sपंचांगts | TODO_dump_func \
	| TODO_update_ssa
#समावेश "gcc-generate-gimple-pass.h"

__visible पूर्णांक plugin_init(काष्ठा plugin_name_args *plugin_info,
			  काष्ठा plugin_gcc_version *version)
अणु
	bool enabled = true;
	स्थिर अक्षर * स्थिर plugin_name = plugin_info->base_name;
	स्थिर पूर्णांक argc = plugin_info->argc;
	स्थिर काष्ठा plugin_argument * स्थिर argv = plugin_info->argv;
	पूर्णांक i;

	अटल स्थिर काष्ठा ggc_root_tab gt_ggc_r_gt_latent_entropy[] = अणु
		अणु
			.base = &latent_entropy_decl,
			.nelt = 1,
			.stride = माप(latent_entropy_decl),
			.cb = &gt_ggc_mx_tree_node,
			.pchw = &gt_pch_nx_tree_node
		पूर्ण,
		LAST_GGC_ROOT_TAB
	पूर्ण;

	PASS_INFO(latent_entropy, "optimized", 1, PASS_POS_INSERT_BEFORE);

	अगर (!plugin_शेष_version_check(version, &gcc_version)) अणु
		error(G_("incompatible gcc/plugin versions"));
		वापस 1;
	पूर्ण

	क्रम (i = 0; i < argc; ++i) अणु
		अगर (!(म_भेद(argv[i].key, "disable"))) अणु
			enabled = false;
			जारी;
		पूर्ण
		error(G_("unknown option '-fplugin-arg-%s-%s'"), plugin_name, argv[i].key);
	पूर्ण

	रेजिस्टर_callback(plugin_name, PLUGIN_INFO, शून्य,
				&latent_entropy_plugin_info);
	अगर (enabled) अणु
		रेजिस्टर_callback(plugin_name, PLUGIN_START_UNIT,
					&latent_entropy_start_unit, शून्य);
		रेजिस्टर_callback(plugin_name, PLUGIN_REGISTER_GGC_ROOTS,
				  शून्य, (व्योम *)&gt_ggc_r_gt_latent_entropy);
		रेजिस्टर_callback(plugin_name, PLUGIN_PASS_MANAGER_SETUP, शून्य,
					&latent_entropy_pass_info);
	पूर्ण
	रेजिस्टर_callback(plugin_name, PLUGIN_ATTRIBUTES, रेजिस्टर_attributes,
				शून्य);

	वापस 0;
पूर्ण
