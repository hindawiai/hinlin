<शैली गुरु>
/* SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause) */
#अगर_अघोषित __BPF_CORE_READ_H__
#घोषणा __BPF_CORE_READ_H__

/*
 * क्रमागत bpf_field_info_kind is passed as a second argument पूर्णांकo
 * __builtin_preserve_field_info() built-in to get a specअगरic aspect of
 * a field, captured as a first argument. __builtin_preserve_field_info(field,
 * info_kind) वापसs __u32 पूर्णांकeger and produces BTF field relocation, which
 * is understood and processed by libbpf during BPF object loading. See
 * selftests/bpf क्रम examples.
 */
क्रमागत bpf_field_info_kind अणु
	BPF_FIELD_BYTE_OFFSET = 0,	/* field byte offset */
	BPF_FIELD_BYTE_SIZE = 1,
	BPF_FIELD_EXISTS = 2,		/* field existence in target kernel */
	BPF_FIELD_SIGNED = 3,
	BPF_FIELD_LSHIFT_U64 = 4,
	BPF_FIELD_RSHIFT_U64 = 5,
पूर्ण;

/* second argument to __builtin_btf_type_id() built-in */
क्रमागत bpf_type_id_kind अणु
	BPF_TYPE_ID_LOCAL = 0,		/* BTF type ID in local program */
	BPF_TYPE_ID_TARGET = 1,		/* BTF type ID in target kernel */
पूर्ण;

/* second argument to __builtin_preserve_type_info() built-in */
क्रमागत bpf_type_info_kind अणु
	BPF_TYPE_EXISTS = 0,		/* type existence in target kernel */
	BPF_TYPE_SIZE = 1,		/* type size in target kernel */
पूर्ण;

/* second argument to __builtin_preserve_क्रमागत_value() built-in */
क्रमागत bpf_क्रमागत_value_kind अणु
	BPF_ENUMVAL_EXISTS = 0,		/* क्रमागत value existence in kernel */
	BPF_ENUMVAL_VALUE = 1,		/* क्रमागत value value relocation */
पूर्ण;

#घोषणा __CORE_RELO(src, field, info)					      \
	__builtin_preserve_field_info((src)->field, BPF_FIELD_##info)

#अगर __BYTE_ORDER == __LITTLE_ENDIAN
#घोषणा __CORE_BITFIELD_PROBE_READ(dst, src, fld)			      \
	bpf_probe_पढ़ो_kernel(						      \
			(व्योम *)dst,				      \
			__CORE_RELO(src, fld, BYTE_SIZE),		      \
			(स्थिर व्योम *)src + __CORE_RELO(src, fld, BYTE_OFFSET))
#अन्यथा
/* semantics of LSHIFT_64 assumes loading values पूर्णांकo low-ordered bytes, so
 * क्रम big-endian we need to adjust destination poपूर्णांकer accordingly, based on
 * field byte size
 */
#घोषणा __CORE_BITFIELD_PROBE_READ(dst, src, fld)			      \
	bpf_probe_पढ़ो_kernel(						      \
			(व्योम *)dst + (8 - __CORE_RELO(src, fld, BYTE_SIZE)), \
			__CORE_RELO(src, fld, BYTE_SIZE),		      \
			(स्थिर व्योम *)src + __CORE_RELO(src, fld, BYTE_OFFSET))
#पूर्ण_अगर

/*
 * Extract bitfield, identअगरied by s->field, and वापस its value as u64.
 * All this is करोne in relocatable manner, so bitfield changes such as
 * चिन्हितness, bit size, offset changes, this will be handled स्वतःmatically.
 * This version of macro is using bpf_probe_पढ़ो_kernel() to पढ़ो underlying
 * पूर्णांकeger storage. Macro functions as an expression and its वापस type is
 * bpf_probe_पढ़ो_kernel()'s वापस value: 0, on success, <0 on error.
 */
#घोषणा BPF_CORE_READ_BITFIELD_PROBED(s, field) (अणु			      \
	अचिन्हित दीर्घ दीर्घ val = 0;					      \
									      \
	__CORE_BITFIELD_PROBE_READ(&val, s, field);			      \
	val <<= __CORE_RELO(s, field, LSHIFT_U64);			      \
	अगर (__CORE_RELO(s, field, SIGNED))				      \
		val = ((दीर्घ दीर्घ)val) >> __CORE_RELO(s, field, RSHIFT_U64);  \
	अन्यथा								      \
		val = val >> __CORE_RELO(s, field, RSHIFT_U64);		      \
	val;								      \
पूर्ण)

/*
 * Extract bitfield, identअगरied by s->field, and वापस its value as u64.
 * This version of macro is using direct memory पढ़ोs and should be used from
 * BPF program types that support such functionality (e.g., typed raw
 * tracepoपूर्णांकs).
 */
#घोषणा BPF_CORE_READ_BITFIELD(s, field) (अणु				      \
	स्थिर व्योम *p = (स्थिर व्योम *)s + __CORE_RELO(s, field, BYTE_OFFSET); \
	अचिन्हित दीर्घ दीर्घ val;						      \
									      \
	/* This is a so-called barrier_var() operation that makes specअगरied   \
	 * variable "a black box" क्रम optimizing compiler.		      \
	 * It क्रमces compiler to perक्रमm BYTE_OFFSET relocation on p and use  \
	 * its calculated value in the चयन below, instead of applying      \
	 * the same relocation 4 बार क्रम each inभागidual memory load.       \
	 */								      \
	यंत्र अस्थिर("" : "=r"(p) : "0"(p));				      \
									      \
	चयन (__CORE_RELO(s, field, BYTE_SIZE)) अणु			      \
	हाल 1: val = *(स्थिर अचिन्हित अक्षर *)p; अवरोध;			      \
	हाल 2: val = *(स्थिर अचिन्हित लघु *)p; अवरोध;		      \
	हाल 4: val = *(स्थिर अचिन्हित पूर्णांक *)p; अवरोध;			      \
	हाल 8: val = *(स्थिर अचिन्हित दीर्घ दीर्घ *)p; अवरोध;		      \
	पूर्ण								      \
	val <<= __CORE_RELO(s, field, LSHIFT_U64);			      \
	अगर (__CORE_RELO(s, field, SIGNED))				      \
		val = ((दीर्घ दीर्घ)val) >> __CORE_RELO(s, field, RSHIFT_U64);  \
	अन्यथा								      \
		val = val >> __CORE_RELO(s, field, RSHIFT_U64);		      \
	val;								      \
पूर्ण)

/*
 * Convenience macro to check that field actually exists in target kernel's.
 * Returns:
 *    1, अगर matching field is present in target kernel;
 *    0, अगर no matching field found.
 */
#घोषणा bpf_core_field_exists(field)					    \
	__builtin_preserve_field_info(field, BPF_FIELD_EXISTS)

/*
 * Convenience macro to get the byte size of a field. Works क्रम पूर्णांकegers,
 * काष्ठा/जोड़s, poपूर्णांकers, arrays, and क्रमागतs.
 */
#घोषणा bpf_core_field_size(field)					    \
	__builtin_preserve_field_info(field, BPF_FIELD_BYTE_SIZE)

/*
 * Convenience macro to get BTF type ID of a specअगरied type, using a local BTF
 * inक्रमmation. Return 32-bit अचिन्हित पूर्णांकeger with type ID from program's own
 * BTF. Always succeeds.
 */
#घोषणा bpf_core_type_id_local(type)					    \
	__builtin_btf_type_id(*(typeof(type) *)0, BPF_TYPE_ID_LOCAL)

/*
 * Convenience macro to get BTF type ID of a target kernel's type that matches
 * specअगरied local type.
 * Returns:
 *    - valid 32-bit अचिन्हित type ID in kernel BTF;
 *    - 0, अगर no matching type was found in a target kernel BTF.
 */
#घोषणा bpf_core_type_id_kernel(type)					    \
	__builtin_btf_type_id(*(typeof(type) *)0, BPF_TYPE_ID_TARGET)

/*
 * Convenience macro to check that provided named type
 * (काष्ठा/जोड़/क्रमागत/प्रकार) exists in a target kernel.
 * Returns:
 *    1, अगर such type is present in target kernel's BTF;
 *    0, अगर no matching type is found.
 */
#घोषणा bpf_core_type_exists(type)					    \
	__builtin_preserve_type_info(*(typeof(type) *)0, BPF_TYPE_EXISTS)

/*
 * Convenience macro to get the byte size of a provided named type
 * (काष्ठा/जोड़/क्रमागत/प्रकार) in a target kernel.
 * Returns:
 *    >= 0 size (in bytes), अगर type is present in target kernel's BTF;
 *    0, अगर no matching type is found.
 */
#घोषणा bpf_core_type_size(type)					    \
	__builtin_preserve_type_info(*(typeof(type) *)0, BPF_TYPE_SIZE)

/*
 * Convenience macro to check that provided क्रमागतerator value is defined in
 * a target kernel.
 * Returns:
 *    1, अगर specअगरied क्रमागत type and its क्रमागतerator value are present in target
 *    kernel's BTF;
 *    0, अगर no matching क्रमागत and/or क्रमागत value within that क्रमागत is found.
 */
#घोषणा bpf_core_क्रमागत_value_exists(क्रमागत_type, क्रमागत_value)		    \
	__builtin_preserve_क्रमागत_value(*(typeof(क्रमागत_type) *)क्रमागत_value, BPF_ENUMVAL_EXISTS)

/*
 * Convenience macro to get the पूर्णांकeger value of an क्रमागतerator value in
 * a target kernel.
 * Returns:
 *    64-bit value, अगर specअगरied क्रमागत type and its क्रमागतerator value are
 *    present in target kernel's BTF;
 *    0, अगर no matching क्रमागत and/or क्रमागत value within that क्रमागत is found.
 */
#घोषणा bpf_core_क्रमागत_value(क्रमागत_type, क्रमागत_value)			    \
	__builtin_preserve_क्रमागत_value(*(typeof(क्रमागत_type) *)क्रमागत_value, BPF_ENUMVAL_VALUE)

/*
 * bpf_core_पढ़ो() असलtracts away bpf_probe_पढ़ो_kernel() call and captures
 * offset relocation क्रम source address using __builtin_preserve_access_index()
 * built-in, provided by Clang.
 *
 * __builtin_preserve_access_index() takes as an argument an expression of
 * taking an address of a field within काष्ठा/जोड़. It makes compiler emit
 * a relocation, which records BTF type ID describing root काष्ठा/जोड़ and an
 * accessor string which describes exact embedded field that was used to take
 * an address. See detailed description of this relocation क्रमmat and
 * semantics in comments to काष्ठा bpf_field_reloc in libbpf_पूर्णांकernal.h.
 *
 * This relocation allows libbpf to adjust BPF inकाष्ठाion to use correct
 * actual field offset, based on target kernel BTF type that matches original
 * (local) BTF, used to record relocation.
 */
#घोषणा bpf_core_पढ़ो(dst, sz, src)					    \
	bpf_probe_पढ़ो_kernel(dst, sz, (स्थिर व्योम *)__builtin_preserve_access_index(src))

/* NOTE: see comments क्रम BPF_CORE_READ_USER() about the proper types use. */
#घोषणा bpf_core_पढ़ो_user(dst, sz, src)				    \
	bpf_probe_पढ़ो_user(dst, sz, (स्थिर व्योम *)__builtin_preserve_access_index(src))
/*
 * bpf_core_पढ़ो_str() is a thin wrapper around bpf_probe_पढ़ो_str()
 * additionally emitting BPF CO-RE field relocation क्रम specअगरied source
 * argument.
 */
#घोषणा bpf_core_पढ़ो_str(dst, sz, src)					    \
	bpf_probe_पढ़ो_kernel_str(dst, sz, (स्थिर व्योम *)__builtin_preserve_access_index(src))

/* NOTE: see comments क्रम BPF_CORE_READ_USER() about the proper types use. */
#घोषणा bpf_core_पढ़ो_user_str(dst, sz, src)				    \
	bpf_probe_पढ़ो_user_str(dst, sz, (स्थिर व्योम *)__builtin_preserve_access_index(src))

#घोषणा ___concat(a, b) a ## b
#घोषणा ___apply(fn, n) ___concat(fn, n)
#घोषणा ___nth(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, __11, N, ...) N

/*
 * वापस number of provided arguments; used क्रम चयन-based variadic macro
 * definitions (see ___last, ___arrow, etc below)
 */
#घोषणा ___narg(...) ___nth(_, ##__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
/*
 * वापस 0 अगर no arguments are passed, N - otherwise; used क्रम
 * recursively-defined macros to specअगरy termination (0) हाल, and generic
 * (N) हाल (e.g., ___पढ़ो_ptrs, ___core_पढ़ो)
 */
#घोषणा ___empty(...) ___nth(_, ##__VA_ARGS__, N, N, N, N, N, N, N, N, N, N, 0)

#घोषणा ___last1(x) x
#घोषणा ___last2(a, x) x
#घोषणा ___last3(a, b, x) x
#घोषणा ___last4(a, b, c, x) x
#घोषणा ___last5(a, b, c, d, x) x
#घोषणा ___last6(a, b, c, d, e, x) x
#घोषणा ___last7(a, b, c, d, e, f, x) x
#घोषणा ___last8(a, b, c, d, e, f, g, x) x
#घोषणा ___last9(a, b, c, d, e, f, g, h, x) x
#घोषणा ___last10(a, b, c, d, e, f, g, h, i, x) x
#घोषणा ___last(...) ___apply(___last, ___narg(__VA_ARGS__))(__VA_ARGS__)

#घोषणा ___nolast2(a, _) a
#घोषणा ___nolast3(a, b, _) a, b
#घोषणा ___nolast4(a, b, c, _) a, b, c
#घोषणा ___nolast5(a, b, c, d, _) a, b, c, d
#घोषणा ___nolast6(a, b, c, d, e, _) a, b, c, d, e
#घोषणा ___nolast7(a, b, c, d, e, f, _) a, b, c, d, e, f
#घोषणा ___nolast8(a, b, c, d, e, f, g, _) a, b, c, d, e, f, g
#घोषणा ___nolast9(a, b, c, d, e, f, g, h, _) a, b, c, d, e, f, g, h
#घोषणा ___nolast10(a, b, c, d, e, f, g, h, i, _) a, b, c, d, e, f, g, h, i
#घोषणा ___nolast(...) ___apply(___nolast, ___narg(__VA_ARGS__))(__VA_ARGS__)

#घोषणा ___arrow1(a) a
#घोषणा ___arrow2(a, b) a->b
#घोषणा ___arrow3(a, b, c) a->b->c
#घोषणा ___arrow4(a, b, c, d) a->b->c->d
#घोषणा ___arrow5(a, b, c, d, e) a->b->c->d->e
#घोषणा ___arrow6(a, b, c, d, e, f) a->b->c->d->e->f
#घोषणा ___arrow7(a, b, c, d, e, f, g) a->b->c->d->e->f->g
#घोषणा ___arrow8(a, b, c, d, e, f, g, h) a->b->c->d->e->f->g->h
#घोषणा ___arrow9(a, b, c, d, e, f, g, h, i) a->b->c->d->e->f->g->h->i
#घोषणा ___arrow10(a, b, c, d, e, f, g, h, i, j) a->b->c->d->e->f->g->h->i->j
#घोषणा ___arrow(...) ___apply(___arrow, ___narg(__VA_ARGS__))(__VA_ARGS__)

#घोषणा ___type(...) typeof(___arrow(__VA_ARGS__))

#घोषणा ___पढ़ो(पढ़ो_fn, dst, src_type, src, accessor)			    \
	पढ़ो_fn((व्योम *)(dst), माप(*(dst)), &((src_type)(src))->accessor)

/* "recursively" पढ़ो a sequence of inner poपूर्णांकers using local __t var */
#घोषणा ___rd_first(fn, src, a) ___पढ़ो(fn, &__t, ___type(src), src, a);
#घोषणा ___rd_last(fn, ...)						    \
	___पढ़ो(fn, &__t, ___type(___nolast(__VA_ARGS__)), __t, ___last(__VA_ARGS__));
#घोषणा ___rd_p1(fn, ...) स्थिर व्योम *__t; ___rd_first(fn, __VA_ARGS__)
#घोषणा ___rd_p2(fn, ...) ___rd_p1(fn, ___nolast(__VA_ARGS__)) ___rd_last(fn, __VA_ARGS__)
#घोषणा ___rd_p3(fn, ...) ___rd_p2(fn, ___nolast(__VA_ARGS__)) ___rd_last(fn, __VA_ARGS__)
#घोषणा ___rd_p4(fn, ...) ___rd_p3(fn, ___nolast(__VA_ARGS__)) ___rd_last(fn, __VA_ARGS__)
#घोषणा ___rd_p5(fn, ...) ___rd_p4(fn, ___nolast(__VA_ARGS__)) ___rd_last(fn, __VA_ARGS__)
#घोषणा ___rd_p6(fn, ...) ___rd_p5(fn, ___nolast(__VA_ARGS__)) ___rd_last(fn, __VA_ARGS__)
#घोषणा ___rd_p7(fn, ...) ___rd_p6(fn, ___nolast(__VA_ARGS__)) ___rd_last(fn, __VA_ARGS__)
#घोषणा ___rd_p8(fn, ...) ___rd_p7(fn, ___nolast(__VA_ARGS__)) ___rd_last(fn, __VA_ARGS__)
#घोषणा ___rd_p9(fn, ...) ___rd_p8(fn, ___nolast(__VA_ARGS__)) ___rd_last(fn, __VA_ARGS__)
#घोषणा ___पढ़ो_ptrs(fn, src, ...)					    \
	___apply(___rd_p, ___narg(__VA_ARGS__))(fn, src, __VA_ARGS__)

#घोषणा ___core_पढ़ो0(fn, fn_ptr, dst, src, a)				    \
	___पढ़ो(fn, dst, ___type(src), src, a);
#घोषणा ___core_पढ़ोN(fn, fn_ptr, dst, src, ...)			    \
	___पढ़ो_ptrs(fn_ptr, src, ___nolast(__VA_ARGS__))		    \
	___पढ़ो(fn, dst, ___type(src, ___nolast(__VA_ARGS__)), __t,	    \
		___last(__VA_ARGS__));
#घोषणा ___core_पढ़ो(fn, fn_ptr, dst, src, a, ...)			    \
	___apply(___core_पढ़ो, ___empty(__VA_ARGS__))(fn, fn_ptr, dst,	    \
						      src, a, ##__VA_ARGS__)

/*
 * BPF_CORE_READ_INTO() is a more perक्रमmance-conscious variant of
 * BPF_CORE_READ(), in which final field is पढ़ो पूर्णांकo user-provided storage.
 * See BPF_CORE_READ() below क्रम more details on general usage.
 */
#घोषणा BPF_CORE_READ_INTO(dst, src, a, ...) (अणु				    \
	___core_पढ़ो(bpf_core_पढ़ो, bpf_core_पढ़ो,			    \
		     dst, (src), a, ##__VA_ARGS__)			    \
पूर्ण)

/*
 * Variant of BPF_CORE_READ_INTO() क्रम पढ़ोing from user-space memory.
 *
 * NOTE: see comments क्रम BPF_CORE_READ_USER() about the proper types use.
 */
#घोषणा BPF_CORE_READ_USER_INTO(dst, src, a, ...) (अणु			    \
	___core_पढ़ो(bpf_core_पढ़ो_user, bpf_core_पढ़ो_user,		    \
		     dst, (src), a, ##__VA_ARGS__)			    \
पूर्ण)

/* Non-CO-RE variant of BPF_CORE_READ_INTO() */
#घोषणा BPF_PROBE_READ_INTO(dst, src, a, ...) (अणु			    \
	___core_पढ़ो(bpf_probe_पढ़ो, bpf_probe_पढ़ो,			    \
		     dst, (src), a, ##__VA_ARGS__)			    \
पूर्ण)

/* Non-CO-RE variant of BPF_CORE_READ_USER_INTO().
 *
 * As no CO-RE relocations are emitted, source types can be arbitrary and are
 * not restricted to kernel types only.
 */
#घोषणा BPF_PROBE_READ_USER_INTO(dst, src, a, ...) (अणु			    \
	___core_पढ़ो(bpf_probe_पढ़ो_user, bpf_probe_पढ़ो_user,		    \
		     dst, (src), a, ##__VA_ARGS__)			    \
पूर्ण)

/*
 * BPF_CORE_READ_STR_INTO() करोes same "pointer chasing" as
 * BPF_CORE_READ() क्रम पूर्णांकermediate poपूर्णांकers, but then executes (and वापसs
 * corresponding error code) bpf_core_पढ़ो_str() क्रम final string पढ़ो.
 */
#घोषणा BPF_CORE_READ_STR_INTO(dst, src, a, ...) (अणु			    \
	___core_पढ़ो(bpf_core_पढ़ो_str, bpf_core_पढ़ो,			    \
		     dst, (src), a, ##__VA_ARGS__)			    \
पूर्ण)

/*
 * Variant of BPF_CORE_READ_STR_INTO() क्रम पढ़ोing from user-space memory.
 *
 * NOTE: see comments क्रम BPF_CORE_READ_USER() about the proper types use.
 */
#घोषणा BPF_CORE_READ_USER_STR_INTO(dst, src, a, ...) (अणु		    \
	___core_पढ़ो(bpf_core_पढ़ो_user_str, bpf_core_पढ़ो_user,	    \
		     dst, (src), a, ##__VA_ARGS__)			    \
पूर्ण)

/* Non-CO-RE variant of BPF_CORE_READ_STR_INTO() */
#घोषणा BPF_PROBE_READ_STR_INTO(dst, src, a, ...) (अणु			    \
	___core_पढ़ो(bpf_probe_पढ़ो_str, bpf_probe_पढ़ो,		    \
		     dst, (src), a, ##__VA_ARGS__)			    \
पूर्ण)

/*
 * Non-CO-RE variant of BPF_CORE_READ_USER_STR_INTO().
 *
 * As no CO-RE relocations are emitted, source types can be arbitrary and are
 * not restricted to kernel types only.
 */
#घोषणा BPF_PROBE_READ_USER_STR_INTO(dst, src, a, ...) (अणु		    \
	___core_पढ़ो(bpf_probe_पढ़ो_user_str, bpf_probe_पढ़ो_user,	    \
		     dst, (src), a, ##__VA_ARGS__)			    \
पूर्ण)

/*
 * BPF_CORE_READ() is used to simplअगरy BPF CO-RE relocatable पढ़ो, especially
 * when there are few poपूर्णांकer chasing steps.
 * E.g., what in non-BPF world (or in BPF w/ BCC) would be something like:
 *	पूर्णांक x = s->a.b.c->d.e->f->g;
 * can be succinctly achieved using BPF_CORE_READ as:
 *	पूर्णांक x = BPF_CORE_READ(s, a.b.c, d.e, f, g);
 *
 * BPF_CORE_READ will decompose above statement पूर्णांकo 4 bpf_core_पढ़ो (BPF
 * CO-RE relocatable bpf_probe_पढ़ो_kernel() wrapper) calls, logically
 * equivalent to:
 * 1. स्थिर व्योम *__t = s->a.b.c;
 * 2. __t = __t->d.e;
 * 3. __t = __t->f;
 * 4. वापस __t->g;
 *
 * Equivalence is logical, because there is a heavy type casting/preservation
 * involved, as well as all the पढ़ोs are happening through
 * bpf_probe_पढ़ो_kernel() calls using __builtin_preserve_access_index() to
 * emit CO-RE relocations.
 *
 * N.B. Only up to 9 "field accessors" are supported, which should be more
 * than enough क्रम any practical purpose.
 */
#घोषणा BPF_CORE_READ(src, a, ...) (अणु					    \
	___type((src), a, ##__VA_ARGS__) __r;				    \
	BPF_CORE_READ_INTO(&__r, (src), a, ##__VA_ARGS__);		    \
	__r;								    \
पूर्ण)

/*
 * Variant of BPF_CORE_READ() क्रम पढ़ोing from user-space memory.
 *
 * NOTE: all the source types involved are still *kernel types* and need to
 * exist in kernel (or kernel module) BTF, otherwise CO-RE relocation will
 * fail. Custom user types are not relocatable with CO-RE.
 * The typical situation in which BPF_CORE_READ_USER() might be used is to
 * पढ़ो kernel UAPI types from the user-space memory passed in as a syscall
 * input argument.
 */
#घोषणा BPF_CORE_READ_USER(src, a, ...) (अणु				    \
	___type((src), a, ##__VA_ARGS__) __r;				    \
	BPF_CORE_READ_USER_INTO(&__r, (src), a, ##__VA_ARGS__);		    \
	__r;								    \
पूर्ण)

/* Non-CO-RE variant of BPF_CORE_READ() */
#घोषणा BPF_PROBE_READ(src, a, ...) (अणु					    \
	___type((src), a, ##__VA_ARGS__) __r;				    \
	BPF_PROBE_READ_INTO(&__r, (src), a, ##__VA_ARGS__);		    \
	__r;								    \
पूर्ण)

/*
 * Non-CO-RE variant of BPF_CORE_READ_USER().
 *
 * As no CO-RE relocations are emitted, source types can be arbitrary and are
 * not restricted to kernel types only.
 */
#घोषणा BPF_PROBE_READ_USER(src, a, ...) (अणु				    \
	___type((src), a, ##__VA_ARGS__) __r;				    \
	BPF_PROBE_READ_USER_INTO(&__r, (src), a, ##__VA_ARGS__);	    \
	__r;								    \
पूर्ण)

#पूर्ण_अगर

