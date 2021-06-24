<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित GCC_COMMON_H_INCLUDED
#घोषणा GCC_COMMON_H_INCLUDED

#समावेश "bversion.h"
#अगर BUILDING_GCC_VERSION >= 6000
#समावेश "gcc-plugin.h"
#अन्यथा
#समावेश "plugin.h"
#पूर्ण_अगर
#समावेश "plugin-version.h"
#समावेश "config.h"
#समावेश "system.h"
#समावेश "coretypes.h"
#समावेश "tm.h"
#समावेश "line-map.h"
#समावेश "input.h"
#समावेश "tree.h"

#समावेश "tree-inline.h"
#समावेश "version.h"
#समावेश "rtl.h"
#समावेश "tm_p.h"
#समावेश "flags.h"
#समावेश "hard-reg-set.h"
#समावेश "output.h"
#समावेश "except.h"
#समावेश "function.h"
#समावेश "toplev.h"
#अगर BUILDING_GCC_VERSION >= 5000
#समावेश "expr.h"
#पूर्ण_अगर
#समावेश "basic-block.h"
#समावेश "intl.h"
#समावेश "ggc.h"
#समावेश "timevar.h"

#अगर BUILDING_GCC_VERSION < 10000
#समावेश "params.h"
#पूर्ण_अगर

#अगर BUILDING_GCC_VERSION <= 4009
#समावेश "pointer-set.h"
#अन्यथा
#समावेश "hash-map.h"
#पूर्ण_अगर

#अगर BUILDING_GCC_VERSION >= 7000
#समावेश "memmodel.h"
#पूर्ण_अगर
#समावेश "emit-rtl.h"
#समावेश "debug.h"
#समावेश "target.h"
#समावेश "langhooks.h"
#समावेश "cfgloop.h"
#समावेश "cgraph.h"
#समावेश "opts.h"
#समावेश "tree-pretty-print.h"
#समावेश "gimple-pretty-print.h"
#समावेश "c-family/c-common.h"
#समावेश "tree-cfgcleanup.h"
#समावेश "tree-ssa-operands.h"
#समावेश "tree-into-ssa.h"
#समावेश "is-a.h"
#समावेश "diagnostic.h"
#समावेश "tree-dump.h"
#समावेश "tree-pass.h"
#समावेश "pass_manager.h"
#समावेश "predict.h"
#समावेश "ipa-utils.h"

#अगर BUILDING_GCC_VERSION >= 8000
#समावेश "stringpool.h"
#पूर्ण_अगर

#समावेश "attribs.h"
#समावेश "varasm.h"
#समावेश "stor-layout.h"
#समावेश "internal-fn.h"
#समावेश "gimple-expr.h"
#समावेश "gimple-fold.h"
#समावेश "context.h"
#समावेश "tree-ssa-alias.h"
#समावेश "tree-ssa.h"
#समावेश "stringpool.h"
#अगर BUILDING_GCC_VERSION >= 7000
#समावेश "tree-vrp.h"
#पूर्ण_अगर
#समावेश "tree-ssanames.h"
#समावेश "print-tree.h"
#समावेश "tree-eh.h"
#समावेश "stmt.h"
#समावेश "gimplify.h"
#समावेश "gimple.h"
#समावेश "tree-ssa-operands.h"
#समावेश "tree-phinodes.h"
#समावेश "tree-cfg.h"
#समावेश "gimple-iterator.h"
#समावेश "gimple-ssa.h"
#समावेश "ssa-iterators.h"

#अगर BUILDING_GCC_VERSION >= 5000
#समावेश "builtins.h"
#पूर्ण_अगर

/* missing from basic_block.h... */
व्योम debug_करोminance_info(क्रमागत cdi_direction dir);
व्योम debug_करोminance_tree(क्रमागत cdi_direction dir, basic_block root);

#अगर_अघोषित __unused
#घोषणा __unused __attribute__((__unused__))
#पूर्ण_अगर
#अगर_अघोषित __visible
#घोषणा __visible __attribute__((visibility("default")))
#पूर्ण_अगर

#घोषणा DECL_NAME_POINTER(node) IDENTIFIER_POINTER(DECL_NAME(node))
#घोषणा DECL_NAME_LENGTH(node) IDENTIFIER_LENGTH(DECL_NAME(node))
#घोषणा TYPE_NAME_POINTER(node) IDENTIFIER_POINTER(TYPE_NAME(node))
#घोषणा TYPE_NAME_LENGTH(node) IDENTIFIER_LENGTH(TYPE_NAME(node))

/* should come from c-tree.h अगर only it were installed क्रम gcc 4.5... */
#घोषणा C_TYPE_FIELDS_READONLY(TYPE) TREE_LANG_FLAG_1(TYPE)

अटल अंतरभूत tree build_स्थिर_अक्षर_string(पूर्णांक len, स्थिर अक्षर *str)
अणु
	tree cstr, elem, index, type;

	cstr = build_string(len, str);
	elem = build_type_variant(अक्षर_type_node, 1, 0);
	index = build_index_type(size_पूर्णांक(len - 1));
	type = build_array_type(elem, index);
	TREE_TYPE(cstr) = type;
	TREE_CONSTANT(cstr) = 1;
	TREE_READONLY(cstr) = 1;
	TREE_STATIC(cstr) = 1;
	वापस cstr;
पूर्ण

#घोषणा PASS_INFO(NAME, REF, ID, POS)		\
काष्ठा रेजिस्टर_pass_info NAME##_pass_info = अणु	\
	.pass = make_##NAME##_pass(),		\
	.reference_pass_name = REF,		\
	.ref_pass_instance_number = ID,		\
	.pos_op = POS,				\
पूर्ण

#घोषणा add_referenced_var(var)
#घोषणा mark_sym_क्रम_renaming(var)
#घोषणा varpool_mark_needed_node(node)
#घोषणा create_var_ann(var)
#घोषणा TODO_dump_func 0
#घोषणा TODO_dump_cgraph 0

#अगर BUILDING_GCC_VERSION <= 4009
#घोषणा TODO_verअगरy_il 0
#घोषणा AVAIL_INTERPOSABLE AVAIL_OVERWRITABLE

#घोषणा section_name_prefix LTO_SECTION_NAME_PREFIX
#घोषणा fatal_error(loc, gmsgid, ...) fatal_error((gmsgid), __VA_ARGS__)

rtx emit_move_insn(rtx x, rtx y);

प्रकार काष्ठा rtx_def rtx_insn;

अटल अंतरभूत स्थिर अक्षर *get_decl_section_name(स्थिर_tree decl)
अणु
	अगर (DECL_SECTION_NAME(decl) == शून्य_TREE)
		वापस शून्य;

	वापस TREE_STRING_POINTER(DECL_SECTION_NAME(decl));
पूर्ण

अटल अंतरभूत व्योम set_decl_section_name(tree node, स्थिर अक्षर *value)
अणु
	अगर (value)
		DECL_SECTION_NAME(node) = build_string(म_माप(value) + 1, value);
	अन्यथा
		DECL_SECTION_NAME(node) = शून्य;
पूर्ण
#पूर्ण_अगर

#अगर BUILDING_GCC_VERSION == 4009
प्रकार काष्ठा gimple_statement_यंत्र gयंत्र;
प्रकार काष्ठा gimple_statement_base gassign;
प्रकार काष्ठा gimple_statement_call gcall;
प्रकार काष्ठा gimple_statement_base gcond;
प्रकार काष्ठा gimple_statement_base gdebug;
प्रकार काष्ठा gimple_statement_base gजाओ;
प्रकार काष्ठा gimple_statement_phi gphi;
प्रकार काष्ठा gimple_statement_base gवापस;

अटल अंतरभूत gयंत्र *as_a_gयंत्र(gimple sपंचांगt)
अणु
	वापस as_a<gयंत्र>(sपंचांगt);
पूर्ण

अटल अंतरभूत स्थिर gयंत्र *as_a_स्थिर_gयंत्र(स्थिर_gimple sपंचांगt)
अणु
	वापस as_a<स्थिर gयंत्र>(sपंचांगt);
पूर्ण

अटल अंतरभूत gassign *as_a_gassign(gimple sपंचांगt)
अणु
	वापस sपंचांगt;
पूर्ण

अटल अंतरभूत स्थिर gassign *as_a_स्थिर_gassign(स्थिर_gimple sपंचांगt)
अणु
	वापस sपंचांगt;
पूर्ण

अटल अंतरभूत gcall *as_a_gcall(gimple sपंचांगt)
अणु
	वापस as_a<gcall>(sपंचांगt);
पूर्ण

अटल अंतरभूत स्थिर gcall *as_a_स्थिर_gcall(स्थिर_gimple sपंचांगt)
अणु
	वापस as_a<स्थिर gcall>(sपंचांगt);
पूर्ण

अटल अंतरभूत gcond *as_a_gcond(gimple sपंचांगt)
अणु
	वापस sपंचांगt;
पूर्ण

अटल अंतरभूत स्थिर gcond *as_a_स्थिर_gcond(स्थिर_gimple sपंचांगt)
अणु
	वापस sपंचांगt;
पूर्ण

अटल अंतरभूत gdebug *as_a_gdebug(gimple sपंचांगt)
अणु
	वापस sपंचांगt;
पूर्ण

अटल अंतरभूत स्थिर gdebug *as_a_स्थिर_gdebug(स्थिर_gimple sपंचांगt)
अणु
	वापस sपंचांगt;
पूर्ण

अटल अंतरभूत gजाओ *as_a_gजाओ(gimple sपंचांगt)
अणु
	वापस sपंचांगt;
पूर्ण

अटल अंतरभूत स्थिर gजाओ *as_a_स्थिर_gजाओ(स्थिर_gimple sपंचांगt)
अणु
	वापस sपंचांगt;
पूर्ण

अटल अंतरभूत gphi *as_a_gphi(gimple sपंचांगt)
अणु
	वापस as_a<gphi>(sपंचांगt);
पूर्ण

अटल अंतरभूत स्थिर gphi *as_a_स्थिर_gphi(स्थिर_gimple sपंचांगt)
अणु
	वापस as_a<स्थिर gphi>(sपंचांगt);
पूर्ण

अटल अंतरभूत gवापस *as_a_gवापस(gimple sपंचांगt)
अणु
	वापस sपंचांगt;
पूर्ण

अटल अंतरभूत स्थिर gवापस *as_a_स्थिर_gवापस(स्थिर_gimple sपंचांगt)
अणु
	वापस sपंचांगt;
पूर्ण
#पूर्ण_अगर

#घोषणा TODO_ggc_collect 0
#घोषणा NODE_SYMBOL(node) (node)
#घोषणा NODE_DECL(node) (node)->decl
#घोषणा cgraph_node_name(node) (node)->name()
#घोषणा NODE_IMPLICIT_ALIAS(node) (node)->cpp_implicit_alias

अटल अंतरभूत opt_pass *get_pass_क्रम_id(पूर्णांक id)
अणु
	वापस g->get_passes()->get_pass_क्रम_id(id);
पूर्ण

#अगर BUILDING_GCC_VERSION >= 5000 && BUILDING_GCC_VERSION < 6000
/* gimple related */
ढाँचा <>
ढाँचा <>
अंतरभूत bool is_a_helper<स्थिर gassign *>::test(स्थिर_gimple gs)
अणु
	वापस gs->code == GIMPLE_ASSIGN;
पूर्ण
#पूर्ण_अगर

#अगर BUILDING_GCC_VERSION >= 5000
#घोषणा TODO_verअगरy_ssa TODO_verअगरy_il
#घोषणा TODO_verअगरy_flow TODO_verअगरy_il
#घोषणा TODO_verअगरy_sपंचांगts TODO_verअगरy_il
#घोषणा TODO_verअगरy_rtl_sharing TODO_verअगरy_il

#घोषणा INSN_DELETED_P(insn) (insn)->deleted()

अटल अंतरभूत स्थिर अक्षर *get_decl_section_name(स्थिर_tree decl)
अणु
	वापस DECL_SECTION_NAME(decl);
पूर्ण

/* symtab/cgraph related */
#घोषणा debug_cgraph_node(node) (node)->debug()
#घोषणा cgraph_get_node(decl) cgraph_node::get(decl)
#घोषणा cgraph_get_create_node(decl) cgraph_node::get_create(decl)
#घोषणा cgraph_create_node(decl) cgraph_node::create(decl)
#घोषणा cgraph_n_nodes symtab->cgraph_count
#घोषणा cgraph_max_uid symtab->cgraph_max_uid
#घोषणा varpool_get_node(decl) varpool_node::get(decl)
#घोषणा dump_varpool_node(file, node) (node)->dump(file)

#अगर BUILDING_GCC_VERSION >= 8000
#घोषणा cgraph_create_edge(caller, callee, call_sपंचांगt, count, freq) \
	(caller)->create_edge((callee), (call_sपंचांगt), (count))

#घोषणा cgraph_create_edge_including_clones(caller, callee,	\
		old_call_sपंचांगt, call_sपंचांगt, count, freq, reason)	\
	(caller)->create_edge_including_clones((callee),	\
		(old_call_sपंचांगt), (call_sपंचांगt), (count), (reason))
#अन्यथा
#घोषणा cgraph_create_edge(caller, callee, call_sपंचांगt, count, freq) \
	(caller)->create_edge((callee), (call_sपंचांगt), (count), (freq))

#घोषणा cgraph_create_edge_including_clones(caller, callee,	\
		old_call_sपंचांगt, call_sपंचांगt, count, freq, reason)	\
	(caller)->create_edge_including_clones((callee),	\
		(old_call_sपंचांगt), (call_sपंचांगt), (count), (freq), (reason))
#पूर्ण_अगर

प्रकार काष्ठा cgraph_node *cgraph_node_ptr;
प्रकार काष्ठा cgraph_edge *cgraph_edge_p;
प्रकार काष्ठा varpool_node *varpool_node_ptr;

अटल अंतरभूत व्योम change_decl_assembler_name(tree decl, tree name)
अणु
	symtab->change_decl_assembler_name(decl, name);
पूर्ण

अटल अंतरभूत व्योम varpool_finalize_decl(tree decl)
अणु
	varpool_node::finalize_decl(decl);
पूर्ण

अटल अंतरभूत व्योम varpool_add_new_variable(tree decl)
अणु
	varpool_node::add(decl);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक rebuild_cgraph_edges(व्योम)
अणु
	वापस cgraph_edge::rebuild_edges();
पूर्ण

अटल अंतरभूत cgraph_node_ptr cgraph_function_node(cgraph_node_ptr node, क्रमागत availability *availability)
अणु
	वापस node->function_symbol(availability);
पूर्ण

अटल अंतरभूत cgraph_node_ptr cgraph_function_or_thunk_node(cgraph_node_ptr node, क्रमागत availability *availability = शून्य)
अणु
	वापस node->ultimate_alias_target(availability);
पूर्ण

अटल अंतरभूत bool cgraph_only_called_directly_p(cgraph_node_ptr node)
अणु
	वापस node->only_called_directly_p();
पूर्ण

अटल अंतरभूत क्रमागत availability cgraph_function_body_availability(cgraph_node_ptr node)
अणु
	वापस node->get_availability();
पूर्ण

अटल अंतरभूत cgraph_node_ptr cgraph_alias_target(cgraph_node_ptr node)
अणु
	वापस node->get_alias_target();
पूर्ण

अटल अंतरभूत bool cgraph_क्रम_node_and_aliases(cgraph_node_ptr node, bool (*callback)(cgraph_node_ptr, व्योम *), व्योम *data, bool include_overwritable)
अणु
	वापस node->call_क्रम_symbol_thunks_and_aliases(callback, data, include_overwritable);
पूर्ण

अटल अंतरभूत काष्ठा cgraph_node_hook_list *cgraph_add_function_insertion_hook(cgraph_node_hook hook, व्योम *data)
अणु
	वापस symtab->add_cgraph_insertion_hook(hook, data);
पूर्ण

अटल अंतरभूत व्योम cgraph_हटाओ_function_insertion_hook(काष्ठा cgraph_node_hook_list *entry)
अणु
	symtab->हटाओ_cgraph_insertion_hook(entry);
पूर्ण

अटल अंतरभूत काष्ठा cgraph_node_hook_list *cgraph_add_node_removal_hook(cgraph_node_hook hook, व्योम *data)
अणु
	वापस symtab->add_cgraph_removal_hook(hook, data);
पूर्ण

अटल अंतरभूत व्योम cgraph_हटाओ_node_removal_hook(काष्ठा cgraph_node_hook_list *entry)
अणु
	symtab->हटाओ_cgraph_removal_hook(entry);
पूर्ण

अटल अंतरभूत काष्ठा cgraph_2node_hook_list *cgraph_add_node_duplication_hook(cgraph_2node_hook hook, व्योम *data)
अणु
	वापस symtab->add_cgraph_duplication_hook(hook, data);
पूर्ण

अटल अंतरभूत व्योम cgraph_हटाओ_node_duplication_hook(काष्ठा cgraph_2node_hook_list *entry)
अणु
	symtab->हटाओ_cgraph_duplication_hook(entry);
पूर्ण

अटल अंतरभूत व्योम cgraph_call_node_duplication_hooks(cgraph_node_ptr node, cgraph_node_ptr node2)
अणु
	symtab->call_cgraph_duplication_hooks(node, node2);
पूर्ण

अटल अंतरभूत व्योम cgraph_call_edge_duplication_hooks(cgraph_edge *cs1, cgraph_edge *cs2)
अणु
	symtab->call_edge_duplication_hooks(cs1, cs2);
पूर्ण

#अगर BUILDING_GCC_VERSION >= 6000
प्रकार gimple *gimple_ptr;
प्रकार स्थिर gimple *स्थिर_gimple_ptr;
#घोषणा gimple gimple_ptr
#घोषणा स्थिर_gimple स्थिर_gimple_ptr
#अघोषित CONST_CAST_GIMPLE
#घोषणा CONST_CAST_GIMPLE(X) CONST_CAST(gimple, (X))
#पूर्ण_अगर

/* gimple related */
अटल अंतरभूत gimple gimple_build_assign_with_ops(क्रमागत tree_code subcode, tree lhs, tree op1, tree op2 MEM_STAT_DECL)
अणु
	वापस gimple_build_assign(lhs, subcode, op1, op2 PASS_MEM_STAT);
पूर्ण

#अगर BUILDING_GCC_VERSION < 10000
ढाँचा <>
ढाँचा <>
अंतरभूत bool is_a_helper<स्थिर gजाओ *>::test(स्थिर_gimple gs)
अणु
	वापस gs->code == GIMPLE_GOTO;
पूर्ण

ढाँचा <>
ढाँचा <>
अंतरभूत bool is_a_helper<स्थिर gवापस *>::test(स्थिर_gimple gs)
अणु
	वापस gs->code == GIMPLE_RETURN;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत gयंत्र *as_a_gयंत्र(gimple sपंचांगt)
अणु
	वापस as_a<gयंत्र *>(sपंचांगt);
पूर्ण

अटल अंतरभूत स्थिर gयंत्र *as_a_स्थिर_gयंत्र(स्थिर_gimple sपंचांगt)
अणु
	वापस as_a<स्थिर gयंत्र *>(sपंचांगt);
पूर्ण

अटल अंतरभूत gassign *as_a_gassign(gimple sपंचांगt)
अणु
	वापस as_a<gassign *>(sपंचांगt);
पूर्ण

अटल अंतरभूत स्थिर gassign *as_a_स्थिर_gassign(स्थिर_gimple sपंचांगt)
अणु
	वापस as_a<स्थिर gassign *>(sपंचांगt);
पूर्ण

अटल अंतरभूत gcall *as_a_gcall(gimple sपंचांगt)
अणु
	वापस as_a<gcall *>(sपंचांगt);
पूर्ण

अटल अंतरभूत स्थिर gcall *as_a_स्थिर_gcall(स्थिर_gimple sपंचांगt)
अणु
	वापस as_a<स्थिर gcall *>(sपंचांगt);
पूर्ण

अटल अंतरभूत gजाओ *as_a_gजाओ(gimple sपंचांगt)
अणु
	वापस as_a<gजाओ *>(sपंचांगt);
पूर्ण

अटल अंतरभूत स्थिर gजाओ *as_a_स्थिर_gजाओ(स्थिर_gimple sपंचांगt)
अणु
	वापस as_a<स्थिर gजाओ *>(sपंचांगt);
पूर्ण

अटल अंतरभूत gphi *as_a_gphi(gimple sपंचांगt)
अणु
	वापस as_a<gphi *>(sपंचांगt);
पूर्ण

अटल अंतरभूत स्थिर gphi *as_a_स्थिर_gphi(स्थिर_gimple sपंचांगt)
अणु
	वापस as_a<स्थिर gphi *>(sपंचांगt);
पूर्ण

अटल अंतरभूत gवापस *as_a_gवापस(gimple sपंचांगt)
अणु
	वापस as_a<gवापस *>(sपंचांगt);
पूर्ण

अटल अंतरभूत स्थिर gवापस *as_a_स्थिर_gवापस(स्थिर_gimple sपंचांगt)
अणु
	वापस as_a<स्थिर gवापस *>(sपंचांगt);
पूर्ण

/* IPA/LTO related */
#घोषणा ipa_ref_list_referring_iterate(L, I, P)	\
	(L)->referring.iterate((I), &(P))
#घोषणा ipa_ref_list_reference_iterate(L, I, P)	\
	(L)->reference.iterate((I), &(P))

अटल अंतरभूत cgraph_node_ptr ipa_ref_referring_node(काष्ठा ipa_ref *ref)
अणु
	वापस dyn_cast<cgraph_node_ptr>(ref->referring);
पूर्ण

अटल अंतरभूत व्योम ipa_हटाओ_sपंचांगt_references(symtab_node *referring_node, gimple sपंचांगt)
अणु
	referring_node->हटाओ_sपंचांगt_references(sपंचांगt);
पूर्ण
#पूर्ण_अगर

#अगर BUILDING_GCC_VERSION < 6000
#घोषणा get_inner_reference(exp, pbitsize, pbitpos, poffset, pmode, pअचिन्हितp, preversep, pअस्थिरp, keep_aligning)	\
	get_inner_reference(exp, pbitsize, pbitpos, poffset, pmode, pअचिन्हितp, pअस्थिरp, keep_aligning)
#घोषणा gen_rtx_set(ARG0, ARG1) gen_rtx_SET(VOIDmode, (ARG0), (ARG1))
#पूर्ण_अगर

#अगर BUILDING_GCC_VERSION >= 6000
#घोषणा gen_rtx_set(ARG0, ARG1) gen_rtx_SET((ARG0), (ARG1))
#पूर्ण_अगर

#अगर_घोषित __cplusplus
अटल अंतरभूत व्योम debug_tree(स्थिर_tree t)
अणु
	debug_tree(CONST_CAST_TREE(t));
पूर्ण

अटल अंतरभूत व्योम debug_gimple_sपंचांगt(स्थिर_gimple s)
अणु
	debug_gimple_sपंचांगt(CONST_CAST_GIMPLE(s));
पूर्ण
#अन्यथा
#घोषणा debug_tree(t) debug_tree(CONST_CAST_TREE(t))
#घोषणा debug_gimple_sपंचांगt(s) debug_gimple_sपंचांगt(CONST_CAST_GIMPLE(s))
#पूर्ण_अगर

#अगर BUILDING_GCC_VERSION >= 7000
#घोषणा get_inner_reference(exp, pbitsize, pbitpos, poffset, pmode, pअचिन्हितp, preversep, pअस्थिरp, keep_aligning)	\
	get_inner_reference(exp, pbitsize, pbitpos, poffset, pmode, pअचिन्हितp, preversep, pअस्थिरp)
#पूर्ण_अगर

#अगर BUILDING_GCC_VERSION < 7000
#घोषणा SET_DECL_ALIGN(decl, align)	DECL_ALIGN(decl) = (align)
#घोषणा SET_DECL_MODE(decl, mode)	DECL_MODE(decl) = (mode)
#पूर्ण_अगर

#पूर्ण_अगर
