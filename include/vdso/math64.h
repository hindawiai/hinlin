<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __VDSO_MATH64_H
#घोषणा __VDSO_MATH64_H

अटल __always_अंतरभूत u32
__iter_भाग_u64_rem(u64 भागidend, u32 भागisor, u64 *reमुख्यder)
अणु
	u32 ret = 0;

	जबतक (भागidend >= भागisor) अणु
		/* The following यंत्र() prevents the compiler from
		   optimising this loop पूर्णांकo a modulo operation.  */
		यंत्र("" : "+rm"(भागidend));

		भागidend -= भागisor;
		ret++;
	पूर्ण

	*reमुख्यder = भागidend;

	वापस ret;
पूर्ण

#पूर्ण_अगर /* __VDSO_MATH64_H */
