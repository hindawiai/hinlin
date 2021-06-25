<शैली गुरु>
/*
 * Copyright 2011-2017 by the PaX Team <pageexec@मुक्तmail.hu>
 * Modअगरied by Alexander Popov <alex.popov@linux.com>
 * Licensed under the GPL v2
 *
 * Note: the choice of the license means that the compilation process is
 * NOT 'eligible' as defined by gcc's library exception to the GPL v3,
 * but क्रम the kernel it करोesn't matter since it doesn't link against
 * any of the gcc libraries
 *
 * This gcc plugin is needed क्रम tracking the lowest border of the kernel stack.
 * It instruments the kernel code inserting stackleak_track_stack() calls:
 *  - after alloca();
 *  - क्रम the functions with a stack frame size greater than or equal
 *     to the "track-min-size" plugin parameter.
 *
 * This plugin is ported from grsecurity/PaX. For more inक्रमmation see:
 *   https://grsecurity.net/
 *   https://pax.grsecurity.net/
 *
 * Debugging:
 *  - use ख_लिखो() to मानक_त्रुटि, debug_generic_expr(), debug_gimple_sपंचांगt(),
 *     prपूर्णांक_rtl_single() and debug_rtx();
 *  - add "-fdump-tree-all -fdump-rtl-all" to the plugin CFLAGS in
 *     Makefile.gcc-plugins to see the verbose dumps of the gcc passes;
 *  - use gcc -E to understand the preprocessing shenanigans;
 *  - use gcc with enabled CFG/GIMPLE/SSA verअगरication (--enable-checking).
 */

#समावेश "gcc-common.h"

__visible पूर्णांक plugin_is_GPL_compatible;

अटल पूर्णांक track_frame_size = -1;
अटल bool build_क्रम_x86 = false;
अटल स्थिर अक्षर track_function[] = "stackleak_track_stack";
अटल bool disable = false;
अटल bool verbose = false;

/*
 * Mark these global variables (roots) क्रम gcc garbage collector since
 * they poपूर्णांक to the garbage-collected memory.
 */
अटल GTY(()) tree track_function_decl;

अटल काष्ठा plugin_info stackleak_plugin_info = अणु
	.version = "201707101337",
	.help = "track-min-size=nn\ttrack stack for functions with a stack frame size >= nn bytes\n"
		"arch=target_arch\tspecify target build arch\n"
		"disable\t\tdo not activate the plugin\n"
		"verbose\t\tprint info about the instrumentation\n"
पूर्ण;

अटल व्योम add_stack_tracking_gcall(gimple_sपंचांगt_iterator *gsi, bool after)
अणु
	gimple sपंचांगt;
	gcall *gimple_call;
	cgraph_node_ptr node;
	basic_block bb;

	/* Insert calling stackleak_track_stack() */
	sपंचांगt = gimple_build_call(track_function_decl, 0);
	gimple_call = as_a_gcall(sपंचांगt);
	अगर (after)
		gsi_insert_after(gsi, gimple_call, GSI_CONTINUE_LINKING);
	अन्यथा
		gsi_insert_beक्रमe(gsi, gimple_call, GSI_SAME_STMT);

	/* Update the cgraph */
	bb = gimple_bb(gimple_call);
	node = cgraph_get_create_node(track_function_decl);
	gcc_निश्चित(node);
	cgraph_create_edge(cgraph_get_node(current_function_decl), node,
			gimple_call, bb->count,
			compute_call_sपंचांगt_bb_frequency(current_function_decl, bb));
पूर्ण

अटल bool is_alloca(gimple sपंचांगt)
अणु
	अगर (gimple_call_builtin_p(sपंचांगt, BUILT_IN_ALLOCA))
		वापस true;

	अगर (gimple_call_builtin_p(sपंचांगt, BUILT_IN_ALLOCA_WITH_ALIGN))
		वापस true;

	वापस false;
पूर्ण

अटल tree get_current_stack_poपूर्णांकer_decl(व्योम)
अणु
	varpool_node_ptr node;

	FOR_EACH_VARIABLE(node) अणु
		tree var = NODE_DECL(node);
		tree name = DECL_NAME(var);

		अगर (DECL_NAME_LENGTH(var) != माप("current_stack_pointer") - 1)
			जारी;

		अगर (म_भेद(IDENTIFIER_POINTER(name), "current_stack_pointer"))
			जारी;

		वापस var;
	पूर्ण

	अगर (verbose) अणु
		ख_लिखो(मानक_त्रुटि, "stackleak: missing current_stack_pointer in %s()\n",
			DECL_NAME_POINTER(current_function_decl));
	पूर्ण
	वापस शून्य_TREE;
पूर्ण

अटल व्योम add_stack_tracking_gयंत्र(gimple_sपंचांगt_iterator *gsi, bool after)
अणु
	gयंत्र *यंत्र_call = शून्य;
	tree sp_decl, input;
	vec<tree, va_gc> *inमाला_दो = शून्य;

	/* 'no_caller_saved_registers' is currently supported only क्रम x86 */
	gcc_निश्चित(build_क्रम_x86);

	/*
	 * Insert calling stackleak_track_stack() in यंत्र:
	 *   यंत्र अस्थिर("call stackleak_track_stack"
	 *		  :: "r" (current_stack_poपूर्णांकer))
	 * Use ASM_CALL_CONSTRAINT trick from arch/x86/include/यंत्र/यंत्र.h.
	 * This स्थिरraपूर्णांक is taken पूर्णांकo account during gcc shrink-wrapping
	 * optimization. It is needed to be sure that stackleak_track_stack()
	 * call is inserted after the prologue of the containing function,
	 * when the stack frame is prepared.
	 */
	sp_decl = get_current_stack_poपूर्णांकer_decl();
	अगर (sp_decl == शून्य_TREE) अणु
		add_stack_tracking_gcall(gsi, after);
		वापस;
	पूर्ण
	input = build_tree_list(शून्य_TREE, build_स्थिर_अक्षर_string(2, "r"));
	input = chainon(शून्य_TREE, build_tree_list(input, sp_decl));
	vec_safe_push(inमाला_दो, input);
	यंत्र_call = gimple_build_यंत्र_vec("call stackleak_track_stack",
					inमाला_दो, शून्य, शून्य, शून्य);
	gimple_यंत्र_set_अस्थिर(यंत्र_call, true);
	अगर (after)
		gsi_insert_after(gsi, यंत्र_call, GSI_CONTINUE_LINKING);
	अन्यथा
		gsi_insert_beक्रमe(gsi, यंत्र_call, GSI_SAME_STMT);
	update_sपंचांगt(यंत्र_call);
पूर्ण

अटल व्योम add_stack_tracking(gimple_sपंचांगt_iterator *gsi, bool after)
अणु
	/*
	 * The 'no_caller_saved_registers' attribute is used क्रम
	 * stackleak_track_stack(). If the compiler supports this attribute क्रम
	 * the target arch, we can add calling stackleak_track_stack() in यंत्र.
	 * That improves perक्रमmance: we aव्योम useless operations with the
	 * caller-saved रेजिस्टरs in the functions from which we will हटाओ
	 * stackleak_track_stack() call during the stackleak_cleanup pass.
	 */
	अगर (lookup_attribute_spec(get_identअगरier("no_caller_saved_registers")))
		add_stack_tracking_gयंत्र(gsi, after);
	अन्यथा
		add_stack_tracking_gcall(gsi, after);
पूर्ण

/*
 * Work with the GIMPLE representation of the code. Insert the
 * stackleak_track_stack() call after alloca() and पूर्णांकo the beginning
 * of the function अगर it is not instrumented.
 */
अटल अचिन्हित पूर्णांक stackleak_instrument_execute(व्योम)
अणु
	basic_block bb, entry_bb;
	bool prologue_instrumented = false, is_leaf = true;
	gimple_sपंचांगt_iterator gsi = अणु 0 पूर्ण;

	/*
	 * ENTRY_BLOCK_PTR is a basic block which represents possible entry
	 * poपूर्णांक of a function. This block करोes not contain any code and
	 * has a CFG edge to its successor.
	 */
	gcc_निश्चित(single_succ_p(ENTRY_BLOCK_PTR_FOR_FN(cfun)));
	entry_bb = single_succ(ENTRY_BLOCK_PTR_FOR_FN(cfun));

	/*
	 * Loop through the GIMPLE statements in each of cfun basic blocks.
	 * cfun is a global variable which represents the function that is
	 * currently processed.
	 */
	FOR_EACH_BB_FN(bb, cfun) अणु
		क्रम (gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi)) अणु
			gimple sपंचांगt;

			sपंचांगt = gsi_sपंचांगt(gsi);

			/* Leaf function is a function which makes no calls */
			अगर (is_gimple_call(sपंचांगt))
				is_leaf = false;

			अगर (!is_alloca(sपंचांगt))
				जारी;

			अगर (verbose) अणु
				ख_लिखो(मानक_त्रुटि, "stackleak: be careful, alloca() in %s()\n",
					DECL_NAME_POINTER(current_function_decl));
			पूर्ण

			/* Insert stackleak_track_stack() call after alloca() */
			add_stack_tracking(&gsi, true);
			अगर (bb == entry_bb)
				prologue_instrumented = true;
		पूर्ण
	पूर्ण

	अगर (prologue_instrumented)
		वापस 0;

	/*
	 * Special हालs to skip the instrumentation.
	 *
	 * Taking the address of अटल अंतरभूत functions materializes them,
	 * but we mustn't instrument some of them as the resulting stack
	 * alignment required by the function call ABI will अवरोध other
	 * assumptions regarding the expected (but not otherwise enक्रमced)
	 * रेजिस्टर clobbering ABI.
	 *
	 * Case in poपूर्णांक: native_save_fl on amd64 when optimized क्रम size
	 * clobbers rdx अगर it were instrumented here.
	 *
	 * TODO: any more special हालs?
	 */
	अगर (is_leaf &&
	    !TREE_PUBLIC(current_function_decl) &&
	    DECL_DECLARED_INLINE_P(current_function_decl)) अणु
		वापस 0;
	पूर्ण

	अगर (is_leaf &&
	    !म_भेदन(IDENTIFIER_POINTER(DECL_NAME(current_function_decl)),
		     "_paravirt_", 10)) अणु
		वापस 0;
	पूर्ण

	/* Insert stackleak_track_stack() call at the function beginning */
	bb = entry_bb;
	अगर (!single_pred_p(bb)) अणु
		/* gcc_निश्चित(bb_loop_depth(bb) ||
				(bb->flags & BB_IRREDUCIBLE_LOOP)); */
		split_edge(single_succ_edge(ENTRY_BLOCK_PTR_FOR_FN(cfun)));
		gcc_निश्चित(single_succ_p(ENTRY_BLOCK_PTR_FOR_FN(cfun)));
		bb = single_succ(ENTRY_BLOCK_PTR_FOR_FN(cfun));
	पूर्ण
	gsi = gsi_after_labels(bb);
	add_stack_tracking(&gsi, false);

	वापस 0;
पूर्ण

अटल bool large_stack_frame(व्योम)
अणु
#अगर BUILDING_GCC_VERSION >= 8000
	वापस maybe_ge(get_frame_size(), track_frame_size);
#अन्यथा
	वापस (get_frame_size() >= track_frame_size);
#पूर्ण_अगर
पूर्ण

अटल व्योम हटाओ_stack_tracking_gcall(व्योम)
अणु
	rtx_insn *insn, *next;

	/*
	 * Find stackleak_track_stack() calls. Loop through the chain of insns,
	 * which is an RTL representation of the code क्रम a function.
	 *
	 * The example of a matching insn:
	 *  (call_insn 8 4 10 2 (call (mem (symbol_ref ("stackleak_track_stack")
	 *  [flags 0x41] <function_decl 0x7f7cd3302a80 stackleak_track_stack>)
	 *  [0 stackleak_track_stack S1 A8]) (0)) 675 अणु*callपूर्ण (expr_list
	 *  (symbol_ref ("stackleak_track_stack") [flags 0x41] <function_decl
	 *  0x7f7cd3302a80 stackleak_track_stack>) (expr_list (0) (nil))) (nil))
	 */
	क्रम (insn = get_insns(); insn; insn = next) अणु
		rtx body;

		next = NEXT_INSN(insn);

		/* Check the expression code of the insn */
		अगर (!CALL_P(insn))
			जारी;

		/*
		 * Check the expression code of the insn body, which is an RTL
		 * Expression (RTX) describing the side effect perक्रमmed by
		 * that insn.
		 */
		body = PATTERN(insn);

		अगर (GET_CODE(body) == PARALLEL)
			body = XVECEXP(body, 0, 0);

		अगर (GET_CODE(body) != CALL)
			जारी;

		/*
		 * Check the first opeअक्रम of the call expression. It should
		 * be a mem RTX describing the needed subroutine with a
		 * symbol_ref RTX.
		 */
		body = XEXP(body, 0);
		अगर (GET_CODE(body) != MEM)
			जारी;

		body = XEXP(body, 0);
		अगर (GET_CODE(body) != SYMBOL_REF)
			जारी;

		अगर (SYMBOL_REF_DECL(body) != track_function_decl)
			जारी;

		/* Delete the stackleak_track_stack() call */
		delete_insn_and_edges(insn);
#अगर BUILDING_GCC_VERSION < 8000
		अगर (GET_CODE(next) == NOTE &&
		    NOTE_KIND(next) == NOTE_INSN_CALL_ARG_LOCATION) अणु
			insn = next;
			next = NEXT_INSN(insn);
			delete_insn_and_edges(insn);
		पूर्ण
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल bool हटाओ_stack_tracking_gयंत्र(व्योम)
अणु
	bool हटाओd = false;
	rtx_insn *insn, *next;

	/* 'no_caller_saved_registers' is currently supported only क्रम x86 */
	gcc_निश्चित(build_क्रम_x86);

	/*
	 * Find stackleak_track_stack() यंत्र calls. Loop through the chain of
	 * insns, which is an RTL representation of the code क्रम a function.
	 *
	 * The example of a matching insn:
	 *  (insn 11 5 12 2 (parallel [ (यंत्र_opeअक्रमs/v
	 *  ("call stackleak_track_stack") ("") 0
	 *  [ (reg/v:DI 7 sp [ current_stack_poपूर्णांकer ]) ]
	 *  [ (यंत्र_input:DI ("r")) ] [])
	 *  (clobber (reg:CC 17 flags)) ]) -1 (nil))
	 */
	क्रम (insn = get_insns(); insn; insn = next) अणु
		rtx body;

		next = NEXT_INSN(insn);

		/* Check the expression code of the insn */
		अगर (!NONJUMP_INSN_P(insn))
			जारी;

		/*
		 * Check the expression code of the insn body, which is an RTL
		 * Expression (RTX) describing the side effect perक्रमmed by
		 * that insn.
		 */
		body = PATTERN(insn);

		अगर (GET_CODE(body) != PARALLEL)
			जारी;

		body = XVECEXP(body, 0, 0);

		अगर (GET_CODE(body) != ASM_OPERANDS)
			जारी;

		अगर (म_भेद(ASM_OPERANDS_TEMPLATE(body),
						"call stackleak_track_stack")) अणु
			जारी;
		पूर्ण

		delete_insn_and_edges(insn);
		gcc_निश्चित(!हटाओd);
		हटाओd = true;
	पूर्ण

	वापस हटाओd;
पूर्ण

/*
 * Work with the RTL representation of the code.
 * Remove the unneeded stackleak_track_stack() calls from the functions
 * which करोn't call alloca() and don't have a large enough stack frame size.
 */
अटल अचिन्हित पूर्णांक stackleak_cleanup_execute(व्योम)
अणु
	स्थिर अक्षर *fn = DECL_NAME_POINTER(current_function_decl);
	bool हटाओd = false;

	/*
	 * Leave stack tracking in functions that call alloca().
	 * Additional हाल:
	 *   gcc beक्रमe version 7 called allocate_dynamic_stack_space() from
	 *   expand_stack_vars() क्रम runसमय alignment of स्थिरant-sized stack
	 *   variables. That caused cfun->calls_alloca to be set क्रम functions
	 *   that in fact करोn't use alloca().
	 *   For more info see gcc commit 7072df0aae0c59ae437e.
	 *   Let's leave such functions instrumented as well.
	 */
	अगर (cfun->calls_alloca) अणु
		अगर (verbose)
			ख_लिखो(मानक_त्रुटि, "stackleak: instrument %s(): calls_alloca\n", fn);
		वापस 0;
	पूर्ण

	/* Leave stack tracking in functions with large stack frame */
	अगर (large_stack_frame()) अणु
		अगर (verbose)
			ख_लिखो(मानक_त्रुटि, "stackleak: instrument %s()\n", fn);
		वापस 0;
	पूर्ण

	अगर (lookup_attribute_spec(get_identअगरier("no_caller_saved_registers")))
		हटाओd = हटाओ_stack_tracking_gयंत्र();

	अगर (!हटाओd)
		हटाओ_stack_tracking_gcall();

	वापस 0;
पूर्ण

अटल bool stackleak_gate(व्योम)
अणु
	tree section;

	section = lookup_attribute("section",
				   DECL_ATTRIBUTES(current_function_decl));
	अगर (section && TREE_VALUE(section)) अणु
		section = TREE_VALUE(TREE_VALUE(section));

		अगर (!म_भेदन(TREE_STRING_POINTER(section), ".init.text", 10))
			वापस false;
		अगर (!म_भेदन(TREE_STRING_POINTER(section), ".devinit.text", 13))
			वापस false;
		अगर (!म_भेदन(TREE_STRING_POINTER(section), ".cpuinit.text", 13))
			वापस false;
		अगर (!म_भेदन(TREE_STRING_POINTER(section), ".meminit.text", 13))
			वापस false;
	पूर्ण

	वापस track_frame_size >= 0;
पूर्ण

/* Build the function declaration क्रम stackleak_track_stack() */
अटल व्योम stackleak_start_unit(व्योम *gcc_data __unused,
				 व्योम *user_data __unused)
अणु
	tree fntype;

	/* व्योम stackleak_track_stack(व्योम) */
	fntype = build_function_type_list(व्योम_type_node, शून्य_TREE);
	track_function_decl = build_fn_decl(track_function, fntype);
	DECL_ASSEMBLER_NAME(track_function_decl); /* क्रम LTO */
	TREE_PUBLIC(track_function_decl) = 1;
	TREE_USED(track_function_decl) = 1;
	DECL_EXTERNAL(track_function_decl) = 1;
	DECL_ARTIFICIAL(track_function_decl) = 1;
	DECL_PRESERVE_P(track_function_decl) = 1;
पूर्ण

/*
 * Pass gate function is a predicate function that माला_लो executed beक्रमe the
 * corresponding pass. If the वापस value is 'true' the pass माला_लो executed,
 * otherwise, it is skipped.
 */
अटल bool stackleak_instrument_gate(व्योम)
अणु
	वापस stackleak_gate();
पूर्ण

#घोषणा PASS_NAME stackleak_instrument
#घोषणा PROPERTIES_REQUIRED PROP_gimple_leh | PROP_cfg
#घोषणा TODO_FLAGS_START TODO_verअगरy_ssa | TODO_verअगरy_flow | TODO_verअगरy_sपंचांगts
#घोषणा TODO_FLAGS_FINISH TODO_verअगरy_ssa | TODO_verअगरy_sपंचांगts | TODO_dump_func \
			| TODO_update_ssa | TODO_rebuild_cgraph_edges
#समावेश "gcc-generate-gimple-pass.h"

अटल bool stackleak_cleanup_gate(व्योम)
अणु
	वापस stackleak_gate();
पूर्ण

#घोषणा PASS_NAME stackleak_cleanup
#घोषणा TODO_FLAGS_FINISH TODO_dump_func
#समावेश "gcc-generate-rtl-pass.h"

/*
 * Every gcc plugin exports a plugin_init() function that is called right
 * after the plugin is loaded. This function is responsible क्रम रेजिस्टरing
 * the plugin callbacks and करोing other required initialization.
 */
__visible पूर्णांक plugin_init(काष्ठा plugin_name_args *plugin_info,
			  काष्ठा plugin_gcc_version *version)
अणु
	स्थिर अक्षर * स्थिर plugin_name = plugin_info->base_name;
	स्थिर पूर्णांक argc = plugin_info->argc;
	स्थिर काष्ठा plugin_argument * स्थिर argv = plugin_info->argv;
	पूर्णांक i = 0;

	/* Extra GGC root tables describing our GTY-ed data */
	अटल स्थिर काष्ठा ggc_root_tab gt_ggc_r_gt_stackleak[] = अणु
		अणु
			.base = &track_function_decl,
			.nelt = 1,
			.stride = माप(track_function_decl),
			.cb = &gt_ggc_mx_tree_node,
			.pchw = &gt_pch_nx_tree_node
		पूर्ण,
		LAST_GGC_ROOT_TAB
	पूर्ण;

	/*
	 * The stackleak_instrument pass should be executed beक्रमe the
	 * "optimized" pass, which is the control flow graph cleanup that is
	 * perक्रमmed just beक्रमe expanding gcc trees to the RTL. In क्रमmer
	 * versions of the plugin this new pass was inserted beक्रमe the
	 * "tree_profile" pass, which is currently called "profile".
	 */
	PASS_INFO(stackleak_instrument, "optimized", 1,
						PASS_POS_INSERT_BEFORE);

	/*
	 * The stackleak_cleanup pass should be executed beक्रमe the "*free_cfg"
	 * pass. It's the moment when the stack frame size is alपढ़ोy final,
	 * function prologues and epilogues are generated, and the
	 * machine-dependent code transक्रमmations are not करोne.
	 */
	PASS_INFO(stackleak_cleanup, "*free_cfg", 1, PASS_POS_INSERT_BEFORE);

	अगर (!plugin_शेष_version_check(version, &gcc_version)) अणु
		error(G_("incompatible gcc/plugin versions"));
		वापस 1;
	पूर्ण

	/* Parse the plugin arguments */
	क्रम (i = 0; i < argc; i++) अणु
		अगर (!म_भेद(argv[i].key, "track-min-size")) अणु
			अगर (!argv[i].value) अणु
				error(G_("no value supplied for option '-fplugin-arg-%s-%s'"),
					plugin_name, argv[i].key);
				वापस 1;
			पूर्ण

			track_frame_size = म_से_प(argv[i].value);
			अगर (track_frame_size < 0) अणु
				error(G_("invalid option argument '-fplugin-arg-%s-%s=%s'"),
					plugin_name, argv[i].key, argv[i].value);
				वापस 1;
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेद(argv[i].key, "arch")) अणु
			अगर (!argv[i].value) अणु
				error(G_("no value supplied for option '-fplugin-arg-%s-%s'"),
					plugin_name, argv[i].key);
				वापस 1;
			पूर्ण

			अगर (!म_भेद(argv[i].value, "x86"))
				build_क्रम_x86 = true;
		पूर्ण अन्यथा अगर (!म_भेद(argv[i].key, "disable")) अणु
			disable = true;
		पूर्ण अन्यथा अगर (!म_भेद(argv[i].key, "verbose")) अणु
			verbose = true;
		पूर्ण अन्यथा अणु
			error(G_("unknown option '-fplugin-arg-%s-%s'"),
					plugin_name, argv[i].key);
			वापस 1;
		पूर्ण
	पूर्ण

	अगर (disable) अणु
		अगर (verbose)
			ख_लिखो(मानक_त्रुटि, "stackleak: disabled for this translation unit\n");
		वापस 0;
	पूर्ण

	/* Give the inक्रमmation about the plugin */
	रेजिस्टर_callback(plugin_name, PLUGIN_INFO, शून्य,
						&stackleak_plugin_info);

	/* Register to be called beक्रमe processing a translation unit */
	रेजिस्टर_callback(plugin_name, PLUGIN_START_UNIT,
					&stackleak_start_unit, शून्य);

	/* Register an extra GCC garbage collector (GGC) root table */
	रेजिस्टर_callback(plugin_name, PLUGIN_REGISTER_GGC_ROOTS, शून्य,
					(व्योम *)&gt_ggc_r_gt_stackleak);

	/*
	 * Hook पूर्णांकo the Pass Manager to रेजिस्टर new gcc passes.
	 *
	 * The stack frame size info is available only at the last RTL pass,
	 * when it's too late to insert complex code like a function call.
	 * So we रेजिस्टर two gcc passes to instrument every function at first
	 * and हटाओ the unneeded instrumentation later.
	 */
	रेजिस्टर_callback(plugin_name, PLUGIN_PASS_MANAGER_SETUP, शून्य,
					&stackleak_instrument_pass_info);
	रेजिस्टर_callback(plugin_name, PLUGIN_PASS_MANAGER_SETUP, शून्य,
					&stackleak_cleanup_pass_info);

	वापस 0;
पूर्ण
