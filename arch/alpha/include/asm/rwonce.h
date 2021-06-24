<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2019 Google LLC.
 */
#अगर_अघोषित __ASM_RWONCE_H
#घोषणा __ASM_RWONCE_H

#अगर_घोषित CONFIG_SMP

#समावेश <यंत्र/barrier.h>

/*
 * Alpha is apparently daft enough to reorder address-dependent loads
 * on some CPU implementations. Knock some common sense पूर्णांकo it with
 * a memory barrier in READ_ONCE().
 *
 * For the curious, more inक्रमmation about this unusual reordering is
 * available in chapter 15 of the "perfbook":
 *
 *  https://kernel.org/pub/linux/kernel/people/paulmck/perfbook/perfbook.hपंचांगl
 *
 */
#घोषणा __READ_ONCE(x)							\
(अणु									\
	__unqual_scalar_typeof(x) __x =					\
		(*(अस्थिर typeof(__x) *)(&(x)));			\
	mb();								\
	(typeof(x))__x;							\
पूर्ण)

#पूर्ण_अगर /* CONFIG_SMP */

#समावेश <यंत्र-generic/rwonce.h>

#पूर्ण_अगर /* __ASM_RWONCE_H */
