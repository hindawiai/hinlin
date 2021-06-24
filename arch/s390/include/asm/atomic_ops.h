<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Low level function क्रम atomic operations
 *
 * Copyright IBM Corp. 1999, 2016
 */

#अगर_अघोषित __ARCH_S390_ATOMIC_OPS__
#घोषणा __ARCH_S390_ATOMIC_OPS__

अटल अंतरभूत पूर्णांक __atomic_पढ़ो(स्थिर atomic_t *v)
अणु
	पूर्णांक c;

	यंत्र अस्थिर(
		"	l	%0,%1\n"
		: "=d" (c) : "R" (v->counter));
	वापस c;
पूर्ण

अटल अंतरभूत व्योम __atomic_set(atomic_t *v, पूर्णांक i)
अणु
	यंत्र अस्थिर(
		"	st	%1,%0\n"
		: "=R" (v->counter) : "d" (i));
पूर्ण

अटल अंतरभूत s64 __atomic64_पढ़ो(स्थिर atomic64_t *v)
अणु
	s64 c;

	यंत्र अस्थिर(
		"	lg	%0,%1\n"
		: "=d" (c) : "RT" (v->counter));
	वापस c;
पूर्ण

अटल अंतरभूत व्योम __atomic64_set(atomic64_t *v, s64 i)
अणु
	यंत्र अस्थिर(
		"	stg	%1,%0\n"
		: "=RT" (v->counter) : "d" (i));
पूर्ण

#अगर_घोषित CONFIG_HAVE_MARCH_Z196_FEATURES

#घोषणा __ATOMIC_OP(op_name, op_type, op_string, op_barrier)		\
अटल अंतरभूत op_type op_name(op_type val, op_type *ptr)		\
अणु									\
	op_type old;							\
									\
	यंत्र अस्थिर(							\
		op_string "	%[old],%[val],%[ptr]\n"			\
		op_barrier						\
		: [old] "=d" (old), [ptr] "+QS" (*ptr)			\
		: [val] "d" (val) : "cc", "memory");			\
	वापस old;							\
पूर्ण									\

#घोषणा __ATOMIC_OPS(op_name, op_type, op_string)			\
	__ATOMIC_OP(op_name, op_type, op_string, "\n")			\
	__ATOMIC_OP(op_name##_barrier, op_type, op_string, "bcr 14,0\n")

__ATOMIC_OPS(__atomic_add, पूर्णांक, "laa")
__ATOMIC_OPS(__atomic_and, पूर्णांक, "lan")
__ATOMIC_OPS(__atomic_or,  पूर्णांक, "lao")
__ATOMIC_OPS(__atomic_xor, पूर्णांक, "lax")

__ATOMIC_OPS(__atomic64_add, दीर्घ, "laag")
__ATOMIC_OPS(__atomic64_and, दीर्घ, "lang")
__ATOMIC_OPS(__atomic64_or,  दीर्घ, "laog")
__ATOMIC_OPS(__atomic64_xor, दीर्घ, "laxg")

#अघोषित __ATOMIC_OPS
#अघोषित __ATOMIC_OP

#घोषणा __ATOMIC_CONST_OP(op_name, op_type, op_string, op_barrier)	\
अटल __always_अंतरभूत व्योम op_name(op_type val, op_type *ptr)		\
अणु									\
	यंत्र अस्थिर(							\
		op_string "	%[ptr],%[val]\n"			\
		op_barrier						\
		: [ptr] "+QS" (*ptr) : [val] "i" (val) : "cc", "memory");\
पूर्ण

#घोषणा __ATOMIC_CONST_OPS(op_name, op_type, op_string)			\
	__ATOMIC_CONST_OP(op_name, op_type, op_string, "\n")		\
	__ATOMIC_CONST_OP(op_name##_barrier, op_type, op_string, "bcr 14,0\n")

__ATOMIC_CONST_OPS(__atomic_add_स्थिर, पूर्णांक, "asi")
__ATOMIC_CONST_OPS(__atomic64_add_स्थिर, दीर्घ, "agsi")

#अघोषित __ATOMIC_CONST_OPS
#अघोषित __ATOMIC_CONST_OP

#अन्यथा /* CONFIG_HAVE_MARCH_Z196_FEATURES */

#घोषणा __ATOMIC_OP(op_name, op_string)					\
अटल अंतरभूत पूर्णांक op_name(पूर्णांक val, पूर्णांक *ptr)				\
अणु									\
	पूर्णांक old, new;							\
									\
	यंत्र अस्थिर(							\
		"0:	lr	%[new],%[old]\n"			\
		op_string "	%[new],%[val]\n"			\
		"	cs	%[old],%[new],%[ptr]\n"			\
		"	jl	0b"					\
		: [old] "=d" (old), [new] "=&d" (new), [ptr] "+Q" (*ptr)\
		: [val] "d" (val), "0" (*ptr) : "cc", "memory");	\
	वापस old;							\
पूर्ण

#घोषणा __ATOMIC_OPS(op_name, op_string)				\
	__ATOMIC_OP(op_name, op_string)					\
	__ATOMIC_OP(op_name##_barrier, op_string)

__ATOMIC_OPS(__atomic_add, "ar")
__ATOMIC_OPS(__atomic_and, "nr")
__ATOMIC_OPS(__atomic_or,  "or")
__ATOMIC_OPS(__atomic_xor, "xr")

#अघोषित __ATOMIC_OPS

#घोषणा __ATOMIC64_OP(op_name, op_string)				\
अटल अंतरभूत दीर्घ op_name(दीर्घ val, दीर्घ *ptr)				\
अणु									\
	दीर्घ old, new;							\
									\
	यंत्र अस्थिर(							\
		"0:	lgr	%[new],%[old]\n"			\
		op_string "	%[new],%[val]\n"			\
		"	csg	%[old],%[new],%[ptr]\n"			\
		"	jl	0b"					\
		: [old] "=d" (old), [new] "=&d" (new), [ptr] "+QS" (*ptr)\
		: [val] "d" (val), "0" (*ptr) : "cc", "memory");	\
	वापस old;							\
पूर्ण

#घोषणा __ATOMIC64_OPS(op_name, op_string)				\
	__ATOMIC64_OP(op_name, op_string)				\
	__ATOMIC64_OP(op_name##_barrier, op_string)

__ATOMIC64_OPS(__atomic64_add, "agr")
__ATOMIC64_OPS(__atomic64_and, "ngr")
__ATOMIC64_OPS(__atomic64_or,  "ogr")
__ATOMIC64_OPS(__atomic64_xor, "xgr")

#अघोषित __ATOMIC64_OPS

#घोषणा __atomic_add_स्थिर(val, ptr)		__atomic_add(val, ptr)
#घोषणा __atomic_add_स्थिर_barrier(val, ptr)	__atomic_add(val, ptr)
#घोषणा __atomic64_add_स्थिर(val, ptr)		__atomic64_add(val, ptr)
#घोषणा __atomic64_add_स्थिर_barrier(val, ptr)	__atomic64_add(val, ptr)

#पूर्ण_अगर /* CONFIG_HAVE_MARCH_Z196_FEATURES */

अटल अंतरभूत पूर्णांक __atomic_cmpxchg(पूर्णांक *ptr, पूर्णांक old, पूर्णांक new)
अणु
	यंत्र अस्थिर(
		"	cs	%[old],%[new],%[ptr]"
		: [old] "+d" (old), [ptr] "+Q" (*ptr)
		: [new] "d" (new)
		: "cc", "memory");
	वापस old;
पूर्ण

अटल अंतरभूत bool __atomic_cmpxchg_bool(पूर्णांक *ptr, पूर्णांक old, पूर्णांक new)
अणु
	पूर्णांक old_expected = old;

	यंत्र अस्थिर(
		"	cs	%[old],%[new],%[ptr]"
		: [old] "+d" (old), [ptr] "+Q" (*ptr)
		: [new] "d" (new)
		: "cc", "memory");
	वापस old == old_expected;
पूर्ण

अटल अंतरभूत दीर्घ __atomic64_cmpxchg(दीर्घ *ptr, दीर्घ old, दीर्घ new)
अणु
	यंत्र अस्थिर(
		"	csg	%[old],%[new],%[ptr]"
		: [old] "+d" (old), [ptr] "+QS" (*ptr)
		: [new] "d" (new)
		: "cc", "memory");
	वापस old;
पूर्ण

अटल अंतरभूत bool __atomic64_cmpxchg_bool(दीर्घ *ptr, दीर्घ old, दीर्घ new)
अणु
	दीर्घ old_expected = old;

	यंत्र अस्थिर(
		"	csg	%[old],%[new],%[ptr]"
		: [old] "+d" (old), [ptr] "+QS" (*ptr)
		: [new] "d" (new)
		: "cc", "memory");
	वापस old == old_expected;
पूर्ण

#पूर्ण_अगर /* __ARCH_S390_ATOMIC_OPS__  */
