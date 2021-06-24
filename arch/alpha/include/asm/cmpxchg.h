<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ALPHA_CMPXCHG_H
#घोषणा _ALPHA_CMPXCHG_H

/*
 * Atomic exchange routines.
 */

#घोषणा ____xchg(type, args...)		__xchg ## type ## _local(args)
#घोषणा ____cmpxchg(type, args...)	__cmpxchg ## type ## _local(args)
#समावेश <यंत्र/xchg.h>

#घोषणा xchg_local(ptr, x)						\
(अणु									\
	__typeof__(*(ptr)) _x_ = (x);					\
	(__typeof__(*(ptr))) __xchg_local((ptr), (अचिन्हित दीर्घ)_x_,	\
				       माप(*(ptr)));			\
पूर्ण)

#घोषणा cmpxchg_local(ptr, o, n)					\
(अणु									\
	__typeof__(*(ptr)) _o_ = (o);					\
	__typeof__(*(ptr)) _n_ = (n);					\
	(__typeof__(*(ptr))) __cmpxchg_local((ptr), (अचिन्हित दीर्घ)_o_,	\
					  (अचिन्हित दीर्घ)_n_,		\
					  माप(*(ptr)));		\
पूर्ण)

#घोषणा cmpxchg64_local(ptr, o, n)					\
(अणु									\
	BUILD_BUG_ON(माप(*(ptr)) != 8);				\
	cmpxchg_local((ptr), (o), (n));					\
पूर्ण)

#अघोषित ____xchg
#अघोषित ____cmpxchg
#घोषणा ____xchg(type, args...)		__xchg ##type(args)
#घोषणा ____cmpxchg(type, args...)	__cmpxchg ##type(args)
#समावेश <यंत्र/xchg.h>

/*
 * The leading and the trailing memory barriers guarantee that these
 * operations are fully ordered.
 */
#घोषणा xchg(ptr, x)							\
(अणु									\
	__typeof__(*(ptr)) __ret;					\
	__typeof__(*(ptr)) _x_ = (x);					\
	smp_mb();							\
	__ret = (__typeof__(*(ptr)))					\
		__xchg((ptr), (अचिन्हित दीर्घ)_x_, माप(*(ptr)));	\
	smp_mb();							\
	__ret;								\
पूर्ण)

#घोषणा cmpxchg(ptr, o, n)						\
(अणु									\
	__typeof__(*(ptr)) __ret;					\
	__typeof__(*(ptr)) _o_ = (o);					\
	__typeof__(*(ptr)) _n_ = (n);					\
	smp_mb();							\
	__ret = (__typeof__(*(ptr))) __cmpxchg((ptr),			\
		(अचिन्हित दीर्घ)_o_, (अचिन्हित दीर्घ)_n_, माप(*(ptr)));\
	smp_mb();							\
	__ret;								\
पूर्ण)

#घोषणा cmpxchg64(ptr, o, n)						\
(अणु									\
	BUILD_BUG_ON(माप(*(ptr)) != 8);				\
	cmpxchg((ptr), (o), (n));					\
पूर्ण)

#अघोषित ____cmpxchg

#पूर्ण_अगर /* _ALPHA_CMPXCHG_H */
