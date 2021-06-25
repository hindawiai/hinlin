<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)

/*
 * BTF-to-C type converter.
 *
 * Copyright (c) 2019 Facebook
 */

#समावेश <stdbool.h>
#समावेश <मानकघोष.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/btf.h>
#समावेश <linux/kernel.h>
#समावेश "btf.h"
#समावेश "hashmap.h"
#समावेश "libbpf.h"
#समावेश "libbpf_internal.h"

अटल स्थिर अक्षर PREFIXES[] = "\t\t\t\t\t\t\t\t\t\t\t\t\t";
अटल स्थिर माप_प्रकार PREFIX_CNT = माप(PREFIXES) - 1;

अटल स्थिर अक्षर *pfx(पूर्णांक lvl)
अणु
	वापस lvl >= PREFIX_CNT ? PREFIXES : &PREFIXES[PREFIX_CNT - lvl];
पूर्ण

क्रमागत btf_dump_type_order_state अणु
	NOT_ORDERED,
	ORDERING,
	ORDERED,
पूर्ण;

क्रमागत btf_dump_type_emit_state अणु
	NOT_EMITTED,
	EMITTING,
	EMITTED,
पूर्ण;

/* per-type auxiliary state */
काष्ठा btf_dump_type_aux_state अणु
	/* topological sorting state */
	क्रमागत btf_dump_type_order_state order_state: 2;
	/* emitting state used to determine the need क्रम क्रमward declaration */
	क्रमागत btf_dump_type_emit_state emit_state: 2;
	/* whether क्रमward declaration was alपढ़ोy emitted */
	__u8 fwd_emitted: 1;
	/* whether unique non-duplicate name was alपढ़ोy asचिन्हित */
	__u8 name_resolved: 1;
	/* whether type is referenced from any other type */
	__u8 referenced: 1;
पूर्ण;

काष्ठा btf_dump अणु
	स्थिर काष्ठा btf *btf;
	स्थिर काष्ठा btf_ext *btf_ext;
	btf_dump_म_लिखो_fn_t म_लिखो_fn;
	काष्ठा btf_dump_opts opts;
	पूर्णांक ptr_sz;
	bool strip_mods;
	पूर्णांक last_id;

	/* per-type auxiliary state */
	काष्ठा btf_dump_type_aux_state *type_states;
	माप_प्रकार type_states_cap;
	/* per-type optional cached unique name, must be मुक्तd, अगर present */
	स्थिर अक्षर **cached_names;
	माप_प्रकार cached_names_cap;

	/* topo-sorted list of dependent type definitions */
	__u32 *emit_queue;
	पूर्णांक emit_queue_cap;
	पूर्णांक emit_queue_cnt;

	/*
	 * stack of type declarations (e.g., chain of modअगरiers, arrays,
	 * funcs, etc)
	 */
	__u32 *decl_stack;
	पूर्णांक decl_stack_cap;
	पूर्णांक decl_stack_cnt;

	/* maps काष्ठा/जोड़/क्रमागत name to a number of name occurrences */
	काष्ठा hashmap *type_names;
	/*
	 * maps प्रकार identअगरiers and क्रमागत value names to a number of such
	 * name occurrences
	 */
	काष्ठा hashmap *ident_names;
पूर्ण;

अटल माप_प्रकार str_hash_fn(स्थिर व्योम *key, व्योम *ctx)
अणु
	वापस str_hash(key);
पूर्ण

अटल bool str_equal_fn(स्थिर व्योम *a, स्थिर व्योम *b, व्योम *ctx)
अणु
	वापस म_भेद(a, b) == 0;
पूर्ण

अटल स्थिर अक्षर *btf_name_of(स्थिर काष्ठा btf_dump *d, __u32 name_off)
अणु
	वापस btf__name_by_offset(d->btf, name_off);
पूर्ण

अटल व्योम btf_dump_म_लिखो(स्थिर काष्ठा btf_dump *d, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	d->म_लिखो_fn(d->opts.ctx, fmt, args);
	बहु_पूर्ण(args);
पूर्ण

अटल पूर्णांक btf_dump_mark_referenced(काष्ठा btf_dump *d);
अटल पूर्णांक btf_dump_resize(काष्ठा btf_dump *d);

काष्ठा btf_dump *btf_dump__new(स्थिर काष्ठा btf *btf,
			       स्थिर काष्ठा btf_ext *btf_ext,
			       स्थिर काष्ठा btf_dump_opts *opts,
			       btf_dump_म_लिखो_fn_t म_लिखो_fn)
अणु
	काष्ठा btf_dump *d;
	पूर्णांक err;

	d = सुस्मृति(1, माप(काष्ठा btf_dump));
	अगर (!d)
		वापस ERR_PTR(-ENOMEM);

	d->btf = btf;
	d->btf_ext = btf_ext;
	d->म_लिखो_fn = म_लिखो_fn;
	d->opts.ctx = opts ? opts->ctx : शून्य;
	d->ptr_sz = btf__poपूर्णांकer_size(btf) ? : माप(व्योम *);

	d->type_names = hashmap__new(str_hash_fn, str_equal_fn, शून्य);
	अगर (IS_ERR(d->type_names)) अणु
		err = PTR_ERR(d->type_names);
		d->type_names = शून्य;
		जाओ err;
	पूर्ण
	d->ident_names = hashmap__new(str_hash_fn, str_equal_fn, शून्य);
	अगर (IS_ERR(d->ident_names)) अणु
		err = PTR_ERR(d->ident_names);
		d->ident_names = शून्य;
		जाओ err;
	पूर्ण

	err = btf_dump_resize(d);
	अगर (err)
		जाओ err;

	वापस d;
err:
	btf_dump__मुक्त(d);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक btf_dump_resize(काष्ठा btf_dump *d)
अणु
	पूर्णांक err, last_id = btf__get_nr_types(d->btf);

	अगर (last_id <= d->last_id)
		वापस 0;

	अगर (libbpf_ensure_mem((व्योम **)&d->type_states, &d->type_states_cap,
			      माप(*d->type_states), last_id + 1))
		वापस -ENOMEM;
	अगर (libbpf_ensure_mem((व्योम **)&d->cached_names, &d->cached_names_cap,
			      माप(*d->cached_names), last_id + 1))
		वापस -ENOMEM;

	अगर (d->last_id == 0) अणु
		/* VOID is special */
		d->type_states[0].order_state = ORDERED;
		d->type_states[0].emit_state = EMITTED;
	पूर्ण

	/* eagerly determine referenced types क्रम anon क्रमागतs */
	err = btf_dump_mark_referenced(d);
	अगर (err)
		वापस err;

	d->last_id = last_id;
	वापस 0;
पूर्ण

व्योम btf_dump__मुक्त(काष्ठा btf_dump *d)
अणु
	पूर्णांक i;

	अगर (IS_ERR_OR_शून्य(d))
		वापस;

	मुक्त(d->type_states);
	अगर (d->cached_names) अणु
		/* any set cached name is owned by us and should be मुक्तd */
		क्रम (i = 0; i <= d->last_id; i++) अणु
			अगर (d->cached_names[i])
				मुक्त((व्योम *)d->cached_names[i]);
		पूर्ण
	पूर्ण
	मुक्त(d->cached_names);
	मुक्त(d->emit_queue);
	मुक्त(d->decl_stack);
	hashmap__मुक्त(d->type_names);
	hashmap__मुक्त(d->ident_names);

	मुक्त(d);
पूर्ण

अटल पूर्णांक btf_dump_order_type(काष्ठा btf_dump *d, __u32 id, bool through_ptr);
अटल व्योम btf_dump_emit_type(काष्ठा btf_dump *d, __u32 id, __u32 cont_id);

/*
 * Dump BTF type in a compilable C syntax, including all the necessary
 * dependent types, necessary क्रम compilation. If some of the dependent types
 * were alपढ़ोy emitted as part of previous btf_dump__dump_type() invocation
 * क्रम another type, they won't be emitted again. This API allows callers to
 * filter out BTF types according to user-defined criterias and emitted only
 * minimal subset of types, necessary to compile everything. Full काष्ठा/जोड़
 * definitions will still be emitted, even अगर the only usage is through
 * poपूर्णांकer and could be satisfied with just a क्रमward declaration.
 *
 * Dumping is करोne in two high-level passes:
 *   1. Topologically sort type definitions to satisfy C rules of compilation.
 *   2. Emit type definitions in C syntax.
 *
 * Returns 0 on success; <0, otherwise.
 */
पूर्णांक btf_dump__dump_type(काष्ठा btf_dump *d, __u32 id)
अणु
	पूर्णांक err, i;

	अगर (id > btf__get_nr_types(d->btf))
		वापस -EINVAL;

	err = btf_dump_resize(d);
	अगर (err)
		वापस err;

	d->emit_queue_cnt = 0;
	err = btf_dump_order_type(d, id, false);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i < d->emit_queue_cnt; i++)
		btf_dump_emit_type(d, d->emit_queue[i], 0 /*top-level*/);

	वापस 0;
पूर्ण

/*
 * Mark all types that are referenced from any other type. This is used to
 * determine top-level anonymous क्रमागतs that need to be emitted as an
 * independent type declarations.
 * Anonymous क्रमागतs come in two flavors: either embedded in a काष्ठा's field
 * definition, in which हाल they have to be declared अंतरभूत as part of field
 * type declaration; or as a top-level anonymous क्रमागत, typically used क्रम
 * declaring global स्थिरants. It's impossible to distinguish between two
 * without knowning whether given क्रमागत type was referenced from other type:
 * top-level anonymous क्रमागत won't be referenced by anything, जबतक embedded
 * one will.
 */
अटल पूर्णांक btf_dump_mark_referenced(काष्ठा btf_dump *d)
अणु
	पूर्णांक i, j, n = btf__get_nr_types(d->btf);
	स्थिर काष्ठा btf_type *t;
	__u16 vlen;

	क्रम (i = d->last_id + 1; i <= n; i++) अणु
		t = btf__type_by_id(d->btf, i);
		vlen = btf_vlen(t);

		चयन (btf_kind(t)) अणु
		हाल BTF_KIND_INT:
		हाल BTF_KIND_ENUM:
		हाल BTF_KIND_FWD:
		हाल BTF_KIND_FLOAT:
			अवरोध;

		हाल BTF_KIND_VOLATILE:
		हाल BTF_KIND_CONST:
		हाल BTF_KIND_RESTRICT:
		हाल BTF_KIND_PTR:
		हाल BTF_KIND_TYPEDEF:
		हाल BTF_KIND_FUNC:
		हाल BTF_KIND_VAR:
			d->type_states[t->type].referenced = 1;
			अवरोध;

		हाल BTF_KIND_ARRAY: अणु
			स्थिर काष्ठा btf_array *a = btf_array(t);

			d->type_states[a->index_type].referenced = 1;
			d->type_states[a->type].referenced = 1;
			अवरोध;
		पूर्ण
		हाल BTF_KIND_STRUCT:
		हाल BTF_KIND_UNION: अणु
			स्थिर काष्ठा btf_member *m = btf_members(t);

			क्रम (j = 0; j < vlen; j++, m++)
				d->type_states[m->type].referenced = 1;
			अवरोध;
		पूर्ण
		हाल BTF_KIND_FUNC_PROTO: अणु
			स्थिर काष्ठा btf_param *p = btf_params(t);

			क्रम (j = 0; j < vlen; j++, p++)
				d->type_states[p->type].referenced = 1;
			अवरोध;
		पूर्ण
		हाल BTF_KIND_DATASEC: अणु
			स्थिर काष्ठा btf_var_secinfo *v = btf_var_secinfos(t);

			क्रम (j = 0; j < vlen; j++, v++)
				d->type_states[v->type].referenced = 1;
			अवरोध;
		पूर्ण
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक btf_dump_add_emit_queue_id(काष्ठा btf_dump *d, __u32 id)
अणु
	__u32 *new_queue;
	माप_प्रकार new_cap;

	अगर (d->emit_queue_cnt >= d->emit_queue_cap) अणु
		new_cap = max(16, d->emit_queue_cap * 3 / 2);
		new_queue = libbpf_पुनः_स्मृतिarray(d->emit_queue, new_cap, माप(new_queue[0]));
		अगर (!new_queue)
			वापस -ENOMEM;
		d->emit_queue = new_queue;
		d->emit_queue_cap = new_cap;
	पूर्ण

	d->emit_queue[d->emit_queue_cnt++] = id;
	वापस 0;
पूर्ण

/*
 * Determine order of emitting dependent types and specअगरied type to satisfy
 * C compilation rules.  This is करोne through topological sorting with an
 * additional complication which comes from C rules. The मुख्य idea क्रम C is
 * that अगर some type is "embedded" पूर्णांकo a काष्ठा/जोड़, it's size needs to be
 * known at the समय of definition of containing type. E.g., क्रम:
 *
 *	काष्ठा A अणुपूर्ण;
 *	काष्ठा B अणु काष्ठा A x; पूर्ण
 *
 * काष्ठा A *HAS* to be defined beक्रमe काष्ठा B, because it's "embedded",
 * i.e., it is part of काष्ठा B layout. But in the following हाल:
 *
 *	काष्ठा A;
 *	काष्ठा B अणु काष्ठा A *x; पूर्ण
 *	काष्ठा A अणुपूर्ण;
 *
 * it's enough to just have a क्रमward declaration of काष्ठा A at the समय of
 * काष्ठा B definition, as काष्ठा B has a poपूर्णांकer to काष्ठा A, so the size of
 * field x is known without knowing काष्ठा A size: it's माप(व्योम *).
 *
 * Unक्रमtunately, there are some trickier हालs we need to handle, e.g.:
 *
 *	काष्ठा A अणुपूर्ण; // अगर this was क्रमward-declaration: compilation error
 *	काष्ठा B अणु
 *		काष्ठा अणु // anonymous काष्ठा
 *			काष्ठा A y;
 *		पूर्ण *x;
 *	पूर्ण;
 *
 * In this हाल, काष्ठा B's field x is a pointer, so it's size is known
 * regardless of the size of (anonymous) काष्ठा it poपूर्णांकs to. But because this
 * काष्ठा is anonymous and thus defined अंतरभूत inside काष्ठा B, *and* it
 * embeds काष्ठा A, compiler requires full definition of काष्ठा A to be known
 * beक्रमe काष्ठा B can be defined. This creates a transitive dependency
 * between काष्ठा A and काष्ठा B. If काष्ठा A was क्रमward-declared beक्रमe
 * काष्ठा B definition and fully defined after काष्ठा B definition, that would
 * trigger compilation error.
 *
 * All this means that जबतक we are करोing topological sorting on BTF type
 * graph, we need to determine relationships between dअगरferent types (graph
 * nodes):
 *   - weak link (relationship) between X and Y, अगर Y *CAN* be
 *   क्रमward-declared at the poपूर्णांक of X definition;
 *   - strong link, अगर Y *HAS* to be fully-defined beक्रमe X can be defined.
 *
 * The rule is as follows. Given a chain of BTF types from X to Y, अगर there is
 * BTF_KIND_PTR type in the chain and at least one non-anonymous type
 * Z (excluding X, including Y), then link is weak. Otherwise, it's strong.
 * Weak/strong relationship is determined recursively during DFS traversal and
 * is वापसed as a result from btf_dump_order_type().
 *
 * btf_dump_order_type() is trying to aव्योम unnecessary क्रमward declarations,
 * but it is not guaranteeing that no extraneous क्रमward declarations will be
 * emitted.
 *
 * To aव्योम extra work, algorithm marks some of BTF types as ORDERED, when
 * it's करोne with them, but not क्रम all (e.g., VOLATILE, CONST, RESTRICT,
 * ARRAY, FUNC_PROTO), as weak/strong semantics क्रम those depends on the
 * entire graph path, so depending where from one came to that BTF type, it
 * might cause weak or strong ordering. For types like STRUCT/UNION/INT/ENUM,
 * once they are processed, there is no need to करो it again, so they are
 * marked as ORDERED. We can mark PTR as ORDERED as well, as it semi-क्रमces
 * weak link, unless subsequent referenced STRUCT/UNION/ENUM is anonymous. But
 * in any हाल, once those are processed, no need to करो it again, as the
 * result won't change.
 *
 * Returns:
 *   - 1, अगर type is part of strong link (so there is strong topological
 *   ordering requirements);
 *   - 0, अगर type is part of weak link (so can be satisfied through क्रमward
 *   declaration);
 *   - <0, on error (e.g., unsatisfiable type loop detected).
 */
अटल पूर्णांक btf_dump_order_type(काष्ठा btf_dump *d, __u32 id, bool through_ptr)
अणु
	/*
	 * Order state is used to detect strong link cycles, but only क्रम BTF
	 * kinds that are or could be an independent definition (i.e.,
	 * stand-alone fwd decl, क्रमागत, प्रकार, काष्ठा, जोड़). Ptrs, arrays,
	 * func_protos, modअगरiers are just means to get to these definitions.
	 * Int/व्योम करोn't need definitions, they are assumed to be always
	 * properly defined.  We also ignore datasec, var, and funcs क्रम now.
	 * So क्रम all non-defining kinds, we never even set ordering state,
	 * क्रम defining kinds we set ORDERING and subsequently ORDERED अगर it
	 * क्रमms a strong link.
	 */
	काष्ठा btf_dump_type_aux_state *tstate = &d->type_states[id];
	स्थिर काष्ठा btf_type *t;
	__u16 vlen;
	पूर्णांक err, i;

	/* वापस true, letting प्रकारs know that it's ok to be emitted */
	अगर (tstate->order_state == ORDERED)
		वापस 1;

	t = btf__type_by_id(d->btf, id);

	अगर (tstate->order_state == ORDERING) अणु
		/* type loop, but resolvable through fwd declaration */
		अगर (btf_is_composite(t) && through_ptr && t->name_off != 0)
			वापस 0;
		pr_warn("unsatisfiable type cycle, id:[%u]\n", id);
		वापस -ELOOP;
	पूर्ण

	चयन (btf_kind(t)) अणु
	हाल BTF_KIND_INT:
	हाल BTF_KIND_FLOAT:
		tstate->order_state = ORDERED;
		वापस 0;

	हाल BTF_KIND_PTR:
		err = btf_dump_order_type(d, t->type, true);
		tstate->order_state = ORDERED;
		वापस err;

	हाल BTF_KIND_ARRAY:
		वापस btf_dump_order_type(d, btf_array(t)->type, false);

	हाल BTF_KIND_STRUCT:
	हाल BTF_KIND_UNION: अणु
		स्थिर काष्ठा btf_member *m = btf_members(t);
		/*
		 * काष्ठा/जोड़ is part of strong link, only अगर it's embedded
		 * (so no ptr in a path) or it's anonymous (so has to be
		 * defined अंतरभूत, even अगर declared through ptr)
		 */
		अगर (through_ptr && t->name_off != 0)
			वापस 0;

		tstate->order_state = ORDERING;

		vlen = btf_vlen(t);
		क्रम (i = 0; i < vlen; i++, m++) अणु
			err = btf_dump_order_type(d, m->type, false);
			अगर (err < 0)
				वापस err;
		पूर्ण

		अगर (t->name_off != 0) अणु
			err = btf_dump_add_emit_queue_id(d, id);
			अगर (err < 0)
				वापस err;
		पूर्ण

		tstate->order_state = ORDERED;
		वापस 1;
	पूर्ण
	हाल BTF_KIND_ENUM:
	हाल BTF_KIND_FWD:
		/*
		 * non-anonymous or non-referenced क्रमागतs are top-level
		 * declarations and should be emitted. Same logic can be
		 * applied to FWDs, it won't hurt anyways.
		 */
		अगर (t->name_off != 0 || !tstate->referenced) अणु
			err = btf_dump_add_emit_queue_id(d, id);
			अगर (err)
				वापस err;
		पूर्ण
		tstate->order_state = ORDERED;
		वापस 1;

	हाल BTF_KIND_TYPEDEF: अणु
		पूर्णांक is_strong;

		is_strong = btf_dump_order_type(d, t->type, through_ptr);
		अगर (is_strong < 0)
			वापस is_strong;

		/* प्रकार is similar to काष्ठा/जोड़ w.r.t. fwd-decls */
		अगर (through_ptr && !is_strong)
			वापस 0;

		/* प्रकार is always a named definition */
		err = btf_dump_add_emit_queue_id(d, id);
		अगर (err)
			वापस err;

		d->type_states[id].order_state = ORDERED;
		वापस 1;
	पूर्ण
	हाल BTF_KIND_VOLATILE:
	हाल BTF_KIND_CONST:
	हाल BTF_KIND_RESTRICT:
		वापस btf_dump_order_type(d, t->type, through_ptr);

	हाल BTF_KIND_FUNC_PROTO: अणु
		स्थिर काष्ठा btf_param *p = btf_params(t);
		bool is_strong;

		err = btf_dump_order_type(d, t->type, through_ptr);
		अगर (err < 0)
			वापस err;
		is_strong = err > 0;

		vlen = btf_vlen(t);
		क्रम (i = 0; i < vlen; i++, p++) अणु
			err = btf_dump_order_type(d, p->type, through_ptr);
			अगर (err < 0)
				वापस err;
			अगर (err > 0)
				is_strong = true;
		पूर्ण
		वापस is_strong;
	पूर्ण
	हाल BTF_KIND_FUNC:
	हाल BTF_KIND_VAR:
	हाल BTF_KIND_DATASEC:
		d->type_states[id].order_state = ORDERED;
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम btf_dump_emit_missing_aliases(काष्ठा btf_dump *d, __u32 id,
					  स्थिर काष्ठा btf_type *t);

अटल व्योम btf_dump_emit_काष्ठा_fwd(काष्ठा btf_dump *d, __u32 id,
				     स्थिर काष्ठा btf_type *t);
अटल व्योम btf_dump_emit_काष्ठा_def(काष्ठा btf_dump *d, __u32 id,
				     स्थिर काष्ठा btf_type *t, पूर्णांक lvl);

अटल व्योम btf_dump_emit_क्रमागत_fwd(काष्ठा btf_dump *d, __u32 id,
				   स्थिर काष्ठा btf_type *t);
अटल व्योम btf_dump_emit_क्रमागत_def(काष्ठा btf_dump *d, __u32 id,
				   स्थिर काष्ठा btf_type *t, पूर्णांक lvl);

अटल व्योम btf_dump_emit_fwd_def(काष्ठा btf_dump *d, __u32 id,
				  स्थिर काष्ठा btf_type *t);

अटल व्योम btf_dump_emit_प्रकार_def(काष्ठा btf_dump *d, __u32 id,
				      स्थिर काष्ठा btf_type *t, पूर्णांक lvl);

/* a local view पूर्णांकo a shared stack */
काष्ठा id_stack अणु
	स्थिर __u32 *ids;
	पूर्णांक cnt;
पूर्ण;

अटल व्योम btf_dump_emit_type_decl(काष्ठा btf_dump *d, __u32 id,
				    स्थिर अक्षर *fname, पूर्णांक lvl);
अटल व्योम btf_dump_emit_type_chain(काष्ठा btf_dump *d,
				     काष्ठा id_stack *decl_stack,
				     स्थिर अक्षर *fname, पूर्णांक lvl);

अटल स्थिर अक्षर *btf_dump_type_name(काष्ठा btf_dump *d, __u32 id);
अटल स्थिर अक्षर *btf_dump_ident_name(काष्ठा btf_dump *d, __u32 id);
अटल माप_प्रकार btf_dump_name_dups(काष्ठा btf_dump *d, काष्ठा hashmap *name_map,
				 स्थिर अक्षर *orig_name);

अटल bool btf_dump_is_blacklisted(काष्ठा btf_dump *d, __u32 id)
अणु
	स्थिर काष्ठा btf_type *t = btf__type_by_id(d->btf, id);

	/* __builtin_बहु_सूची is a compiler built-in, which causes compilation
	 * errors, when compiling w/ dअगरferent compiler, then used to compile
	 * original code (e.g., GCC to compile kernel, Clang to use generated
	 * C header from BTF). As it is built-in, it should be alपढ़ोy defined
	 * properly पूर्णांकernally in compiler.
	 */
	अगर (t->name_off == 0)
		वापस false;
	वापस म_भेद(btf_name_of(d, t->name_off), "__builtin_va_list") == 0;
पूर्ण

/*
 * Emit C-syntax definitions of types from chains of BTF types.
 *
 * High-level handling of determining necessary क्रमward declarations are handled
 * by btf_dump_emit_type() itself, but all nitty-gritty details of emitting type
 * declarations/definitions in C syntax  are handled by a combo of
 * btf_dump_emit_type_decl()/btf_dump_emit_type_chain() w/ delegation to
 * corresponding btf_dump_emit_*_अणुdef,fwdपूर्ण() functions.
 *
 * We also keep track of "containing struct/union type ID" to determine when
 * we reference it from inside and thus can aव्योम emitting unnecessary क्रमward
 * declaration.
 *
 * This algorithm is deचिन्हित in such a way, that even अगर some error occurs
 * (either technical, e.g., out of memory, or logical, i.e., malक्रमmed BTF
 * that करोesn't comply to C rules completely), algorithm will try to proceed
 * and produce as much meaningful output as possible.
 */
अटल व्योम btf_dump_emit_type(काष्ठा btf_dump *d, __u32 id, __u32 cont_id)
अणु
	काष्ठा btf_dump_type_aux_state *tstate = &d->type_states[id];
	bool top_level_def = cont_id == 0;
	स्थिर काष्ठा btf_type *t;
	__u16 kind;

	अगर (tstate->emit_state == EMITTED)
		वापस;

	t = btf__type_by_id(d->btf, id);
	kind = btf_kind(t);

	अगर (tstate->emit_state == EMITTING) अणु
		अगर (tstate->fwd_emitted)
			वापस;

		चयन (kind) अणु
		हाल BTF_KIND_STRUCT:
		हाल BTF_KIND_UNION:
			/*
			 * अगर we are referencing a काष्ठा/जोड़ that we are
			 * part of - then no need क्रम fwd declaration
			 */
			अगर (id == cont_id)
				वापस;
			अगर (t->name_off == 0) अणु
				pr_warn("anonymous struct/union loop, id:[%u]\n",
					id);
				वापस;
			पूर्ण
			btf_dump_emit_काष्ठा_fwd(d, id, t);
			btf_dump_म_लिखो(d, ";\n\n");
			tstate->fwd_emitted = 1;
			अवरोध;
		हाल BTF_KIND_TYPEDEF:
			/*
			 * क्रम प्रकार fwd_emitted means प्रकार definition
			 * was emitted, but it can be used only क्रम "weak"
			 * references through poपूर्णांकer only, not क्रम embedding
			 */
			अगर (!btf_dump_is_blacklisted(d, id)) अणु
				btf_dump_emit_प्रकार_def(d, id, t, 0);
				btf_dump_म_लिखो(d, ";\n\n");
			पूर्ण
			tstate->fwd_emitted = 1;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		वापस;
	पूर्ण

	चयन (kind) अणु
	हाल BTF_KIND_INT:
		/* Emit type alias definitions अगर necessary */
		btf_dump_emit_missing_aliases(d, id, t);

		tstate->emit_state = EMITTED;
		अवरोध;
	हाल BTF_KIND_ENUM:
		अगर (top_level_def) अणु
			btf_dump_emit_क्रमागत_def(d, id, t, 0);
			btf_dump_म_लिखो(d, ";\n\n");
		पूर्ण
		tstate->emit_state = EMITTED;
		अवरोध;
	हाल BTF_KIND_PTR:
	हाल BTF_KIND_VOLATILE:
	हाल BTF_KIND_CONST:
	हाल BTF_KIND_RESTRICT:
		btf_dump_emit_type(d, t->type, cont_id);
		अवरोध;
	हाल BTF_KIND_ARRAY:
		btf_dump_emit_type(d, btf_array(t)->type, cont_id);
		अवरोध;
	हाल BTF_KIND_FWD:
		btf_dump_emit_fwd_def(d, id, t);
		btf_dump_म_लिखो(d, ";\n\n");
		tstate->emit_state = EMITTED;
		अवरोध;
	हाल BTF_KIND_TYPEDEF:
		tstate->emit_state = EMITTING;
		btf_dump_emit_type(d, t->type, id);
		/*
		 * प्रकार can server as both definition and क्रमward
		 * declaration; at this stage someone depends on
		 * प्रकार as a क्रमward declaration (refers to it
		 * through poपूर्णांकer), so unless we alपढ़ोy did it,
		 * emit प्रकार as a क्रमward declaration
		 */
		अगर (!tstate->fwd_emitted && !btf_dump_is_blacklisted(d, id)) अणु
			btf_dump_emit_प्रकार_def(d, id, t, 0);
			btf_dump_म_लिखो(d, ";\n\n");
		पूर्ण
		tstate->emit_state = EMITTED;
		अवरोध;
	हाल BTF_KIND_STRUCT:
	हाल BTF_KIND_UNION:
		tstate->emit_state = EMITTING;
		/* अगर it's a top-level काष्ठा/जोड़ definition or काष्ठा/जोड़
		 * is anonymous, then in C we'll be emitting all fields and
		 * their types (as opposed to just `काष्ठा X`), so we need to
		 * make sure that all types, referenced from काष्ठा/जोड़
		 * members have necessary क्रमward-declarations, where
		 * applicable
		 */
		अगर (top_level_def || t->name_off == 0) अणु
			स्थिर काष्ठा btf_member *m = btf_members(t);
			__u16 vlen = btf_vlen(t);
			पूर्णांक i, new_cont_id;

			new_cont_id = t->name_off == 0 ? cont_id : id;
			क्रम (i = 0; i < vlen; i++, m++)
				btf_dump_emit_type(d, m->type, new_cont_id);
		पूर्ण अन्यथा अगर (!tstate->fwd_emitted && id != cont_id) अणु
			btf_dump_emit_काष्ठा_fwd(d, id, t);
			btf_dump_म_लिखो(d, ";\n\n");
			tstate->fwd_emitted = 1;
		पूर्ण

		अगर (top_level_def) अणु
			btf_dump_emit_काष्ठा_def(d, id, t, 0);
			btf_dump_म_लिखो(d, ";\n\n");
			tstate->emit_state = EMITTED;
		पूर्ण अन्यथा अणु
			tstate->emit_state = NOT_EMITTED;
		पूर्ण
		अवरोध;
	हाल BTF_KIND_FUNC_PROTO: अणु
		स्थिर काष्ठा btf_param *p = btf_params(t);
		__u16 vlen = btf_vlen(t);
		पूर्णांक i;

		btf_dump_emit_type(d, t->type, cont_id);
		क्रम (i = 0; i < vlen; i++, p++)
			btf_dump_emit_type(d, p->type, cont_id);

		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल bool btf_is_काष्ठा_packed(स्थिर काष्ठा btf *btf, __u32 id,
				 स्थिर काष्ठा btf_type *t)
अणु
	स्थिर काष्ठा btf_member *m;
	पूर्णांक align, i, bit_sz;
	__u16 vlen;

	align = btf__align_of(btf, id);
	/* size of a non-packed काष्ठा has to be a multiple of its alignment*/
	अगर (align && t->size % align)
		वापस true;

	m = btf_members(t);
	vlen = btf_vlen(t);
	/* all non-bitfield fields have to be naturally aligned */
	क्रम (i = 0; i < vlen; i++, m++) अणु
		align = btf__align_of(btf, m->type);
		bit_sz = btf_member_bitfield_size(t, i);
		अगर (align && bit_sz == 0 && m->offset % (8 * align) != 0)
			वापस true;
	पूर्ण

	/*
	 * अगर original काष्ठा was marked as packed, but its layout is
	 * naturally aligned, we'll detect that it's not packed
	 */
	वापस false;
पूर्ण

अटल पूर्णांक chip_away_bits(पूर्णांक total, पूर्णांक at_most)
अणु
	वापस total % at_most ? : at_most;
पूर्ण

अटल व्योम btf_dump_emit_bit_padding(स्थिर काष्ठा btf_dump *d,
				      पूर्णांक cur_off, पूर्णांक m_off, पूर्णांक m_bit_sz,
				      पूर्णांक align, पूर्णांक lvl)
अणु
	पूर्णांक off_dअगरf = m_off - cur_off;
	पूर्णांक ptr_bits = d->ptr_sz * 8;

	अगर (off_dअगरf <= 0)
		/* no gap */
		वापस;
	अगर (m_bit_sz == 0 && off_dअगरf < align * 8)
		/* natural padding will take care of a gap */
		वापस;

	जबतक (off_dअगरf > 0) अणु
		स्थिर अक्षर *pad_type;
		पूर्णांक pad_bits;

		अगर (ptr_bits > 32 && off_dअगरf > 32) अणु
			pad_type = "long";
			pad_bits = chip_away_bits(off_dअगरf, ptr_bits);
		पूर्ण अन्यथा अगर (off_dअगरf > 16) अणु
			pad_type = "int";
			pad_bits = chip_away_bits(off_dअगरf, 32);
		पूर्ण अन्यथा अगर (off_dअगरf > 8) अणु
			pad_type = "short";
			pad_bits = chip_away_bits(off_dअगरf, 16);
		पूर्ण अन्यथा अणु
			pad_type = "char";
			pad_bits = chip_away_bits(off_dअगरf, 8);
		पूर्ण
		btf_dump_म_लिखो(d, "\n%s%s: %d;", pfx(lvl), pad_type, pad_bits);
		off_dअगरf -= pad_bits;
	पूर्ण
पूर्ण

अटल व्योम btf_dump_emit_काष्ठा_fwd(काष्ठा btf_dump *d, __u32 id,
				     स्थिर काष्ठा btf_type *t)
अणु
	btf_dump_म_लिखो(d, "%s %s",
			btf_is_काष्ठा(t) ? "struct" : "union",
			btf_dump_type_name(d, id));
पूर्ण

अटल व्योम btf_dump_emit_काष्ठा_def(काष्ठा btf_dump *d,
				     __u32 id,
				     स्थिर काष्ठा btf_type *t,
				     पूर्णांक lvl)
अणु
	स्थिर काष्ठा btf_member *m = btf_members(t);
	bool is_काष्ठा = btf_is_काष्ठा(t);
	पूर्णांक align, i, packed, off = 0;
	__u16 vlen = btf_vlen(t);

	packed = is_काष्ठा ? btf_is_काष्ठा_packed(d->btf, id, t) : 0;

	btf_dump_म_लिखो(d, "%s%s%s {",
			is_काष्ठा ? "struct" : "union",
			t->name_off ? " " : "",
			btf_dump_type_name(d, id));

	क्रम (i = 0; i < vlen; i++, m++) अणु
		स्थिर अक्षर *fname;
		पूर्णांक m_off, m_sz;

		fname = btf_name_of(d, m->name_off);
		m_sz = btf_member_bitfield_size(t, i);
		m_off = btf_member_bit_offset(t, i);
		align = packed ? 1 : btf__align_of(d->btf, m->type);

		btf_dump_emit_bit_padding(d, off, m_off, m_sz, align, lvl + 1);
		btf_dump_म_लिखो(d, "\n%s", pfx(lvl + 1));
		btf_dump_emit_type_decl(d, m->type, fname, lvl + 1);

		अगर (m_sz) अणु
			btf_dump_म_लिखो(d, ": %d", m_sz);
			off = m_off + m_sz;
		पूर्ण अन्यथा अणु
			m_sz = max((__s64)0, btf__resolve_size(d->btf, m->type));
			off = m_off + m_sz * 8;
		पूर्ण
		btf_dump_म_लिखो(d, ";");
	पूर्ण

	/* pad at the end, अगर necessary */
	अगर (is_काष्ठा) अणु
		align = packed ? 1 : btf__align_of(d->btf, id);
		btf_dump_emit_bit_padding(d, off, t->size * 8, 0, align,
					  lvl + 1);
	पूर्ण

	अगर (vlen)
		btf_dump_म_लिखो(d, "\n");
	btf_dump_म_लिखो(d, "%s}", pfx(lvl));
	अगर (packed)
		btf_dump_म_लिखो(d, " __attribute__((packed))");
पूर्ण

अटल स्थिर अक्षर *missing_base_types[][2] = अणु
	/*
	 * GCC emits प्रकारs to its पूर्णांकernal __PolyX_t types when compiling Arm
	 * SIMD पूर्णांकrinsics. Alias them to standard base types.
	 */
	अणु "__Poly8_t",		"unsigned char" पूर्ण,
	अणु "__Poly16_t",		"unsigned short" पूर्ण,
	अणु "__Poly64_t",		"unsigned long long" पूर्ण,
	अणु "__Poly128_t",	"unsigned __int128" पूर्ण,
पूर्ण;

अटल व्योम btf_dump_emit_missing_aliases(काष्ठा btf_dump *d, __u32 id,
					  स्थिर काष्ठा btf_type *t)
अणु
	स्थिर अक्षर *name = btf_dump_type_name(d, id);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(missing_base_types); i++) अणु
		अगर (म_भेद(name, missing_base_types[i][0]) == 0) अणु
			btf_dump_म_लिखो(d, "typedef %s %s;\n\n",
					missing_base_types[i][1], name);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम btf_dump_emit_क्रमागत_fwd(काष्ठा btf_dump *d, __u32 id,
				   स्थिर काष्ठा btf_type *t)
अणु
	btf_dump_म_लिखो(d, "enum %s", btf_dump_type_name(d, id));
पूर्ण

अटल व्योम btf_dump_emit_क्रमागत_def(काष्ठा btf_dump *d, __u32 id,
				   स्थिर काष्ठा btf_type *t,
				   पूर्णांक lvl)
अणु
	स्थिर काष्ठा btf_क्रमागत *v = btf_क्रमागत(t);
	__u16 vlen = btf_vlen(t);
	स्थिर अक्षर *name;
	माप_प्रकार dup_cnt;
	पूर्णांक i;

	btf_dump_म_लिखो(d, "enum%s%s",
			t->name_off ? " " : "",
			btf_dump_type_name(d, id));

	अगर (vlen) अणु
		btf_dump_म_लिखो(d, " {");
		क्रम (i = 0; i < vlen; i++, v++) अणु
			name = btf_name_of(d, v->name_off);
			/* क्रमागतerators share namespace with प्रकार idents */
			dup_cnt = btf_dump_name_dups(d, d->ident_names, name);
			अगर (dup_cnt > 1) अणु
				btf_dump_म_लिखो(d, "\n%s%s___%zu = %u,",
						pfx(lvl + 1), name, dup_cnt,
						(__u32)v->val);
			पूर्ण अन्यथा अणु
				btf_dump_म_लिखो(d, "\n%s%s = %u,",
						pfx(lvl + 1), name,
						(__u32)v->val);
			पूर्ण
		पूर्ण
		btf_dump_म_लिखो(d, "\n%s}", pfx(lvl));
	पूर्ण
पूर्ण

अटल व्योम btf_dump_emit_fwd_def(काष्ठा btf_dump *d, __u32 id,
				  स्थिर काष्ठा btf_type *t)
अणु
	स्थिर अक्षर *name = btf_dump_type_name(d, id);

	अगर (btf_kflag(t))
		btf_dump_म_लिखो(d, "union %s", name);
	अन्यथा
		btf_dump_म_लिखो(d, "struct %s", name);
पूर्ण

अटल व्योम btf_dump_emit_प्रकार_def(काष्ठा btf_dump *d, __u32 id,
				     स्थिर काष्ठा btf_type *t, पूर्णांक lvl)
अणु
	स्थिर अक्षर *name = btf_dump_ident_name(d, id);

	/*
	 * Old GCC versions are emitting invalid प्रकार क्रम __gnuc_बहु_सूची
	 * poपूर्णांकing to VOID. This generates warnings from btf_dump() and
	 * results in uncompilable header file, so we are fixing it up here
	 * with valid प्रकार पूर्णांकo __builtin_बहु_सूची.
	 */
	अगर (t->type == 0 && म_भेद(name, "__gnuc_va_list") == 0) अणु
		btf_dump_म_लिखो(d, "typedef __builtin_va_list __gnuc_va_list");
		वापस;
	पूर्ण

	btf_dump_म_लिखो(d, "typedef ");
	btf_dump_emit_type_decl(d, t->type, name, lvl);
पूर्ण

अटल पूर्णांक btf_dump_push_decl_stack_id(काष्ठा btf_dump *d, __u32 id)
अणु
	__u32 *new_stack;
	माप_प्रकार new_cap;

	अगर (d->decl_stack_cnt >= d->decl_stack_cap) अणु
		new_cap = max(16, d->decl_stack_cap * 3 / 2);
		new_stack = libbpf_पुनः_स्मृतिarray(d->decl_stack, new_cap, माप(new_stack[0]));
		अगर (!new_stack)
			वापस -ENOMEM;
		d->decl_stack = new_stack;
		d->decl_stack_cap = new_cap;
	पूर्ण

	d->decl_stack[d->decl_stack_cnt++] = id;

	वापस 0;
पूर्ण

/*
 * Emit type declaration (e.g., field type declaration in a काष्ठा or argument
 * declaration in function prototype) in correct C syntax.
 *
 * For most types it's trivial, but there are few quirky type declaration
 * हालs worth mentioning:
 *   - function prototypes (especially nesting of function prototypes);
 *   - arrays;
 *   - स्थिर/अस्थिर/restrict क्रम poपूर्णांकers vs other types.
 *
 * For a good discussion of *PARSING* C syntax (as a human), see
 * Peter van der Linden's "Expert C Programming: Deep C Secrets",
 * Ch.3 "Unscrambling Declarations in C".
 *
 * It won't help with BTF to C conversion much, though, as it's an opposite
 * problem. So we came up with this algorithm in reverse to van der Linden's
 * parsing algorithm. It goes from काष्ठाured BTF representation of type
 * declaration to a valid compilable C syntax.
 *
 * For instance, consider this C प्रकार:
 *	प्रकार स्थिर पूर्णांक * स्थिर * arr[10] arr_t;
 * It will be represented in BTF with this chain of BTF types:
 *	[प्रकार] -> [array] -> [ptr] -> [स्थिर] -> [ptr] -> [स्थिर] -> [पूर्णांक]
 *
 * Notice how [स्थिर] modअगरier always goes beक्रमe type it modअगरies in BTF type
 * graph, but in C syntax, स्थिर/अस्थिर/restrict modअगरiers are written to
 * the right of poपूर्णांकers, but to the left of other types. There are also other
 * quirks, like function poपूर्णांकers, arrays of them, functions वापसing other
 * functions, etc.
 *
 * We handle that by pushing all the types to a stack, until we hit "terminal"
 * type (पूर्णांक/क्रमागत/काष्ठा/जोड़/fwd). Then depending on the kind of a type on
 * top of a stack, modअगरiers are handled dअगरferently. Array/function poपूर्णांकers
 * have also wildly dअगरferent syntax and how nesting of them are करोne. See
 * code क्रम authoritative definition.
 *
 * To aव्योम allocating new stack क्रम each independent chain of BTF types, we
 * share one bigger stack, with each chain working only on its own local view
 * of a stack frame. Some care is required to "pop" stack frames after
 * processing type declaration chain.
 */
पूर्णांक btf_dump__emit_type_decl(काष्ठा btf_dump *d, __u32 id,
			     स्थिर काष्ठा btf_dump_emit_type_decl_opts *opts)
अणु
	स्थिर अक्षर *fname;
	पूर्णांक lvl, err;

	अगर (!OPTS_VALID(opts, btf_dump_emit_type_decl_opts))
		वापस -EINVAL;

	err = btf_dump_resize(d);
	अगर (err)
		वापस -EINVAL;

	fname = OPTS_GET(opts, field_name, "");
	lvl = OPTS_GET(opts, indent_level, 0);
	d->strip_mods = OPTS_GET(opts, strip_mods, false);
	btf_dump_emit_type_decl(d, id, fname, lvl);
	d->strip_mods = false;
	वापस 0;
पूर्ण

अटल व्योम btf_dump_emit_type_decl(काष्ठा btf_dump *d, __u32 id,
				    स्थिर अक्षर *fname, पूर्णांक lvl)
अणु
	काष्ठा id_stack decl_stack;
	स्थिर काष्ठा btf_type *t;
	पूर्णांक err, stack_start;

	stack_start = d->decl_stack_cnt;
	क्रम (;;) अणु
		t = btf__type_by_id(d->btf, id);
		अगर (d->strip_mods && btf_is_mod(t))
			जाओ skip_mod;

		err = btf_dump_push_decl_stack_id(d, id);
		अगर (err < 0) अणु
			/*
			 * अगर we करोn't have enough memory क्रम entire type decl
			 * chain, restore stack, emit warning, and try to
			 * proceed nevertheless
			 */
			pr_warn("not enough memory for decl stack:%d", err);
			d->decl_stack_cnt = stack_start;
			वापस;
		पूर्ण
skip_mod:
		/* VOID */
		अगर (id == 0)
			अवरोध;

		चयन (btf_kind(t)) अणु
		हाल BTF_KIND_PTR:
		हाल BTF_KIND_VOLATILE:
		हाल BTF_KIND_CONST:
		हाल BTF_KIND_RESTRICT:
		हाल BTF_KIND_FUNC_PROTO:
			id = t->type;
			अवरोध;
		हाल BTF_KIND_ARRAY:
			id = btf_array(t)->type;
			अवरोध;
		हाल BTF_KIND_INT:
		हाल BTF_KIND_ENUM:
		हाल BTF_KIND_FWD:
		हाल BTF_KIND_STRUCT:
		हाल BTF_KIND_UNION:
		हाल BTF_KIND_TYPEDEF:
		हाल BTF_KIND_FLOAT:
			जाओ करोne;
		शेष:
			pr_warn("unexpected type in decl chain, kind:%u, id:[%u]\n",
				btf_kind(t), id);
			जाओ करोne;
		पूर्ण
	पूर्ण
करोne:
	/*
	 * We might be inside a chain of declarations (e.g., array of function
	 * poपूर्णांकers वापसing anonymous (so अंतरभूतd) काष्ठाs, having another
	 * array field). Each of those needs its own "stack frame" to handle
	 * emitting of declarations. Those stack frames are non-overlapping
	 * portions of shared btf_dump->decl_stack. To make it a bit nicer to
	 * handle this set of nested stacks, we create a view corresponding to
	 * our own "stack frame" and work with it as an independent stack.
	 * We'll need to clean up after emit_type_chain() वापसs, though.
	 */
	decl_stack.ids = d->decl_stack + stack_start;
	decl_stack.cnt = d->decl_stack_cnt - stack_start;
	btf_dump_emit_type_chain(d, &decl_stack, fname, lvl);
	/*
	 * emit_type_chain() guarantees that it will pop its entire decl_stack
	 * frame beक्रमe वापसing. But it works with a पढ़ो-only view पूर्णांकo
	 * decl_stack, so it करोesn't actually pop anything from the
	 * perspective of shared btf_dump->decl_stack, per se. We need to
	 * reset decl_stack state to how it was beक्रमe us to aव्योम it growing
	 * all the समय.
	 */
	d->decl_stack_cnt = stack_start;
पूर्ण

अटल व्योम btf_dump_emit_mods(काष्ठा btf_dump *d, काष्ठा id_stack *decl_stack)
अणु
	स्थिर काष्ठा btf_type *t;
	__u32 id;

	जबतक (decl_stack->cnt) अणु
		id = decl_stack->ids[decl_stack->cnt - 1];
		t = btf__type_by_id(d->btf, id);

		चयन (btf_kind(t)) अणु
		हाल BTF_KIND_VOLATILE:
			btf_dump_म_लिखो(d, "volatile ");
			अवरोध;
		हाल BTF_KIND_CONST:
			btf_dump_म_लिखो(d, "const ");
			अवरोध;
		हाल BTF_KIND_RESTRICT:
			btf_dump_म_लिखो(d, "restrict ");
			अवरोध;
		शेष:
			वापस;
		पूर्ण
		decl_stack->cnt--;
	पूर्ण
पूर्ण

अटल व्योम btf_dump_drop_mods(काष्ठा btf_dump *d, काष्ठा id_stack *decl_stack)
अणु
	स्थिर काष्ठा btf_type *t;
	__u32 id;

	जबतक (decl_stack->cnt) अणु
		id = decl_stack->ids[decl_stack->cnt - 1];
		t = btf__type_by_id(d->btf, id);
		अगर (!btf_is_mod(t))
			वापस;
		decl_stack->cnt--;
	पूर्ण
पूर्ण

अटल व्योम btf_dump_emit_name(स्थिर काष्ठा btf_dump *d,
			       स्थिर अक्षर *name, bool last_was_ptr)
अणु
	bool separate = name[0] && !last_was_ptr;

	btf_dump_म_लिखो(d, "%s%s", separate ? " " : "", name);
पूर्ण

अटल व्योम btf_dump_emit_type_chain(काष्ठा btf_dump *d,
				     काष्ठा id_stack *decls,
				     स्थिर अक्षर *fname, पूर्णांक lvl)
अणु
	/*
	 * last_was_ptr is used to determine अगर we need to separate poपूर्णांकer
	 * asterisk (*) from previous part of type signature with space, so
	 * that we get `पूर्णांक ***`, instead of `पूर्णांक * * *`. We शेष to true
	 * क्रम हालs where we have single poपूर्णांकer in a chain. E.g., in ptr ->
	 * func_proto हाल. func_proto will start a new emit_type_chain call
	 * with just ptr, which should be emitted as (*) or (*<fname>), so we
	 * करोn't want to prepend space क्रम that last poपूर्णांकer.
	 */
	bool last_was_ptr = true;
	स्थिर काष्ठा btf_type *t;
	स्थिर अक्षर *name;
	__u16 kind;
	__u32 id;

	जबतक (decls->cnt) अणु
		id = decls->ids[--decls->cnt];
		अगर (id == 0) अणु
			/* VOID is a special snowflake */
			btf_dump_emit_mods(d, decls);
			btf_dump_म_लिखो(d, "void");
			last_was_ptr = false;
			जारी;
		पूर्ण

		t = btf__type_by_id(d->btf, id);
		kind = btf_kind(t);

		चयन (kind) अणु
		हाल BTF_KIND_INT:
		हाल BTF_KIND_FLOAT:
			btf_dump_emit_mods(d, decls);
			name = btf_name_of(d, t->name_off);
			btf_dump_म_लिखो(d, "%s", name);
			अवरोध;
		हाल BTF_KIND_STRUCT:
		हाल BTF_KIND_UNION:
			btf_dump_emit_mods(d, decls);
			/* अंतरभूत anonymous काष्ठा/जोड़ */
			अगर (t->name_off == 0)
				btf_dump_emit_काष्ठा_def(d, id, t, lvl);
			अन्यथा
				btf_dump_emit_काष्ठा_fwd(d, id, t);
			अवरोध;
		हाल BTF_KIND_ENUM:
			btf_dump_emit_mods(d, decls);
			/* अंतरभूत anonymous क्रमागत */
			अगर (t->name_off == 0)
				btf_dump_emit_क्रमागत_def(d, id, t, lvl);
			अन्यथा
				btf_dump_emit_क्रमागत_fwd(d, id, t);
			अवरोध;
		हाल BTF_KIND_FWD:
			btf_dump_emit_mods(d, decls);
			btf_dump_emit_fwd_def(d, id, t);
			अवरोध;
		हाल BTF_KIND_TYPEDEF:
			btf_dump_emit_mods(d, decls);
			btf_dump_म_लिखो(d, "%s", btf_dump_ident_name(d, id));
			अवरोध;
		हाल BTF_KIND_PTR:
			btf_dump_म_लिखो(d, "%s", last_was_ptr ? "*" : " *");
			अवरोध;
		हाल BTF_KIND_VOLATILE:
			btf_dump_म_लिखो(d, " volatile");
			अवरोध;
		हाल BTF_KIND_CONST:
			btf_dump_म_लिखो(d, " const");
			अवरोध;
		हाल BTF_KIND_RESTRICT:
			btf_dump_म_लिखो(d, " restrict");
			अवरोध;
		हाल BTF_KIND_ARRAY: अणु
			स्थिर काष्ठा btf_array *a = btf_array(t);
			स्थिर काष्ठा btf_type *next_t;
			__u32 next_id;
			bool multidim;
			/*
			 * GCC has a bug
			 * (https://gcc.gnu.org/bugzilla/show_bug.cgi?id=8354)
			 * which causes it to emit extra स्थिर/अस्थिर
			 * modअगरiers क्रम an array, अगर array's element type has
			 * स्थिर/अस्थिर modअगरiers. Clang करोesn't करो that.
			 * In general, it करोesn't seem very meaningful to have
			 * a स्थिर/अस्थिर modअगरier क्रम array, so we are
			 * going to silently skip them here.
			 */
			btf_dump_drop_mods(d, decls);

			अगर (decls->cnt == 0) अणु
				btf_dump_emit_name(d, fname, last_was_ptr);
				btf_dump_म_लिखो(d, "[%u]", a->nelems);
				वापस;
			पूर्ण

			next_id = decls->ids[decls->cnt - 1];
			next_t = btf__type_by_id(d->btf, next_id);
			multidim = btf_is_array(next_t);
			/* we need space अगर we have named non-poपूर्णांकer */
			अगर (fname[0] && !last_was_ptr)
				btf_dump_म_लिखो(d, " ");
			/* no parentheses क्रम multi-dimensional array */
			अगर (!multidim)
				btf_dump_म_लिखो(d, "(");
			btf_dump_emit_type_chain(d, decls, fname, lvl);
			अगर (!multidim)
				btf_dump_म_लिखो(d, ")");
			btf_dump_म_लिखो(d, "[%u]", a->nelems);
			वापस;
		पूर्ण
		हाल BTF_KIND_FUNC_PROTO: अणु
			स्थिर काष्ठा btf_param *p = btf_params(t);
			__u16 vlen = btf_vlen(t);
			पूर्णांक i;

			/*
			 * GCC emits extra अस्थिर qualअगरier क्रम
			 * __attribute__((noवापस)) function poपूर्णांकers. Clang
			 * करोesn't do it. It's a GCC quirk क्रम backwards
			 * compatibility with code written क्रम GCC <2.5. So,
			 * similarly to extra qualअगरiers क्रम array, just drop
			 * them, instead of handling them.
			 */
			btf_dump_drop_mods(d, decls);
			अगर (decls->cnt) अणु
				btf_dump_म_लिखो(d, " (");
				btf_dump_emit_type_chain(d, decls, fname, lvl);
				btf_dump_म_लिखो(d, ")");
			पूर्ण अन्यथा अणु
				btf_dump_emit_name(d, fname, last_was_ptr);
			पूर्ण
			btf_dump_म_लिखो(d, "(");
			/*
			 * Clang क्रम BPF target generates func_proto with no
			 * args as a func_proto with a single व्योम arg (e.g.,
			 * `पूर्णांक (*f)(व्योम)` vs just `पूर्णांक (*f)()`). We are
			 * going to pretend there are no args क्रम such हाल.
			 */
			अगर (vlen == 1 && p->type == 0) अणु
				btf_dump_म_लिखो(d, ")");
				वापस;
			पूर्ण

			क्रम (i = 0; i < vlen; i++, p++) अणु
				अगर (i > 0)
					btf_dump_म_लिखो(d, ", ");

				/* last arg of type व्योम is vararg */
				अगर (i == vlen - 1 && p->type == 0) अणु
					btf_dump_म_लिखो(d, "...");
					अवरोध;
				पूर्ण

				name = btf_name_of(d, p->name_off);
				btf_dump_emit_type_decl(d, p->type, name, lvl);
			पूर्ण

			btf_dump_म_लिखो(d, ")");
			वापस;
		पूर्ण
		शेष:
			pr_warn("unexpected type in decl chain, kind:%u, id:[%u]\n",
				kind, id);
			वापस;
		पूर्ण

		last_was_ptr = kind == BTF_KIND_PTR;
	पूर्ण

	btf_dump_emit_name(d, fname, last_was_ptr);
पूर्ण

/* वापस number of duplicates (occurrences) of a given name */
अटल माप_प्रकार btf_dump_name_dups(काष्ठा btf_dump *d, काष्ठा hashmap *name_map,
				 स्थिर अक्षर *orig_name)
अणु
	माप_प्रकार dup_cnt = 0;

	hashmap__find(name_map, orig_name, (व्योम **)&dup_cnt);
	dup_cnt++;
	hashmap__set(name_map, orig_name, (व्योम *)dup_cnt, शून्य, शून्य);

	वापस dup_cnt;
पूर्ण

अटल स्थिर अक्षर *btf_dump_resolve_name(काष्ठा btf_dump *d, __u32 id,
					 काष्ठा hashmap *name_map)
अणु
	काष्ठा btf_dump_type_aux_state *s = &d->type_states[id];
	स्थिर काष्ठा btf_type *t = btf__type_by_id(d->btf, id);
	स्थिर अक्षर *orig_name = btf_name_of(d, t->name_off);
	स्थिर अक्षर **cached_name = &d->cached_names[id];
	माप_प्रकार dup_cnt;

	अगर (t->name_off == 0)
		वापस "";

	अगर (s->name_resolved)
		वापस *cached_name ? *cached_name : orig_name;

	dup_cnt = btf_dump_name_dups(d, name_map, orig_name);
	अगर (dup_cnt > 1) अणु
		स्थिर माप_प्रकार max_len = 256;
		अक्षर new_name[max_len];

		snम_लिखो(new_name, max_len, "%s___%zu", orig_name, dup_cnt);
		*cached_name = strdup(new_name);
	पूर्ण

	s->name_resolved = 1;
	वापस *cached_name ? *cached_name : orig_name;
पूर्ण

अटल स्थिर अक्षर *btf_dump_type_name(काष्ठा btf_dump *d, __u32 id)
अणु
	वापस btf_dump_resolve_name(d, id, d->type_names);
पूर्ण

अटल स्थिर अक्षर *btf_dump_ident_name(काष्ठा btf_dump *d, __u32 id)
अणु
	वापस btf_dump_resolve_name(d, id, d->ident_names);
पूर्ण
