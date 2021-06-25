<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_X_TABLES_H
#घोषणा _UAPI_X_TABLES_H
#समावेश <linux/स्थिर.h>
#समावेश <linux/types.h>

#घोषणा XT_FUNCTION_MAXNAMELEN 30
#घोषणा XT_EXTENSION_MAXNAMELEN 29
#घोषणा XT_TABLE_MAXNAMELEN 32

काष्ठा xt_entry_match अणु
	जोड़ अणु
		काष्ठा अणु
			__u16 match_size;

			/* Used by userspace */
			अक्षर name[XT_EXTENSION_MAXNAMELEN];
			__u8 revision;
		पूर्ण user;
		काष्ठा अणु
			__u16 match_size;

			/* Used inside the kernel */
			काष्ठा xt_match *match;
		पूर्ण kernel;

		/* Total length */
		__u16 match_size;
	पूर्ण u;

	अचिन्हित अक्षर data[0];
पूर्ण;

काष्ठा xt_entry_target अणु
	जोड़ अणु
		काष्ठा अणु
			__u16 target_size;

			/* Used by userspace */
			अक्षर name[XT_EXTENSION_MAXNAMELEN];
			__u8 revision;
		पूर्ण user;
		काष्ठा अणु
			__u16 target_size;

			/* Used inside the kernel */
			काष्ठा xt_target *target;
		पूर्ण kernel;

		/* Total length */
		__u16 target_size;
	पूर्ण u;

	अचिन्हित अक्षर data[0];
पूर्ण;

#घोषणा XT_TARGET_INIT(__name, __size)					       \
अणु									       \
	.target.u.user = अणु						       \
		.target_size	= XT_ALIGN(__size),			       \
		.name		= __name,				       \
	पूर्ण,								       \
पूर्ण

काष्ठा xt_standard_target अणु
	काष्ठा xt_entry_target target;
	पूर्णांक verdict;
पूर्ण;

काष्ठा xt_error_target अणु
	काष्ठा xt_entry_target target;
	अक्षर errorname[XT_FUNCTION_MAXNAMELEN];
पूर्ण;

/* The argument to IPT_SO_GET_REVISION_*.  Returns highest revision
 * kernel supports, अगर >= revision. */
काष्ठा xt_get_revision अणु
	अक्षर name[XT_EXTENSION_MAXNAMELEN];
	__u8 revision;
पूर्ण;

/* CONTINUE verdict क्रम tarमाला_लो */
#घोषणा XT_CONTINUE 0xFFFFFFFF

/* For standard target */
#घोषणा XT_RETURN (-NF_REPEAT - 1)

/* this is a dummy काष्ठाure to find out the alignment requirement क्रम a काष्ठा
 * containing all the fundamental data types that are used in ipt_entry,
 * ip6t_entry and arpt_entry.  This sucks, and it is a hack.  It will be my
 * personal pleasure to हटाओ it -HW
 */
काष्ठा _xt_align अणु
	__u8 u8;
	__u16 u16;
	__u32 u32;
	__u64 u64;
पूर्ण;

#घोषणा XT_ALIGN(s) __ALIGN_KERNEL((s), __alignof__(काष्ठा _xt_align))

/* Standard वापस verdict, or करो jump. */
#घोषणा XT_STANDARD_TARGET ""
/* Error verdict. */
#घोषणा XT_ERROR_TARGET "ERROR"

#घोषणा SET_COUNTER(c,b,p) करो अणु (c).bcnt = (b); (c).pcnt = (p); पूर्ण जबतक(0)
#घोषणा ADD_COUNTER(c,b,p) करो अणु (c).bcnt += (b); (c).pcnt += (p); पूर्ण जबतक(0)

काष्ठा xt_counters अणु
	__u64 pcnt, bcnt;			/* Packet and byte counters */
पूर्ण;

/* The argument to IPT_SO_ADD_COUNTERS. */
काष्ठा xt_counters_info अणु
	/* Which table. */
	अक्षर name[XT_TABLE_MAXNAMELEN];

	अचिन्हित पूर्णांक num_counters;

	/* The counters (actually `number' of these). */
	काष्ठा xt_counters counters[0];
पूर्ण;

#घोषणा XT_INV_PROTO		0x40	/* Invert the sense of PROTO. */

#अगर_अघोषित __KERNEL__
/* fn वापसs 0 to जारी iteration */
#घोषणा XT_MATCH_ITERATE(type, e, fn, args...)			\
(अणु								\
	अचिन्हित पूर्णांक __i;					\
	पूर्णांक __ret = 0;						\
	काष्ठा xt_entry_match *__m;				\
								\
	क्रम (__i = माप(type);				\
	     __i < (e)->target_offset;				\
	     __i += __m->u.match_size) अणु			\
		__m = (व्योम *)e + __i;				\
								\
		__ret = fn(__m , ## args);			\
		अगर (__ret != 0)					\
			अवरोध;					\
	पूर्ण							\
	__ret;							\
पूर्ण)

/* fn वापसs 0 to जारी iteration */
#घोषणा XT_ENTRY_ITERATE_CONTINUE(type, entries, size, n, fn, args...) \
(अणु								\
	अचिन्हित पूर्णांक __i, __n;					\
	पूर्णांक __ret = 0;						\
	type *__entry;						\
								\
	क्रम (__i = 0, __n = 0; __i < (size);			\
	     __i += __entry->next_offset, __n++) अणु 		\
		__entry = (व्योम *)(entries) + __i;		\
		अगर (__n < n)					\
			जारी;				\
								\
		__ret = fn(__entry , ## args);			\
		अगर (__ret != 0)					\
			अवरोध;					\
	पूर्ण							\
	__ret;							\
पूर्ण)

/* fn वापसs 0 to जारी iteration */
#घोषणा XT_ENTRY_ITERATE(type, entries, size, fn, args...) \
	XT_ENTRY_ITERATE_CONTINUE(type, entries, size, 0, fn, args)

#पूर्ण_अगर /* !__KERNEL__ */

/* pos is normally a काष्ठा ipt_entry/ip6t_entry/etc. */
#घोषणा xt_entry_क्रमeach(pos, ehead, esize) \
	क्रम ((pos) = (typeof(pos))(ehead); \
	     (pos) < (typeof(pos))((अक्षर *)(ehead) + (esize)); \
	     (pos) = (typeof(pos))((अक्षर *)(pos) + (pos)->next_offset))

/* can only be xt_entry_match, so no use of typeof here */
#घोषणा xt_ematch_क्रमeach(pos, entry) \
	क्रम ((pos) = (काष्ठा xt_entry_match *)entry->elems; \
	     (pos) < (काष्ठा xt_entry_match *)((अक्षर *)(entry) + \
	             (entry)->target_offset); \
	     (pos) = (काष्ठा xt_entry_match *)((अक्षर *)(pos) + \
	             (pos)->u.match_size))


#पूर्ण_अगर /* _UAPI_X_TABLES_H */
