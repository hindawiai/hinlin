<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#समावेश <linux/hardirq.h>

/*
 * may_use_simd - whether it is allowable at this समय to issue SIMD
 *                inकाष्ठाions or access the SIMD रेजिस्टर file
 *
 * As architectures typically करोn't preserve the SIMD रेजिस्टर file when
 * taking an पूर्णांकerrupt, !in_पूर्णांकerrupt() should be a reasonable शेष.
 */
अटल __must_check अंतरभूत bool may_use_simd(व्योम)
अणु
	वापस !in_पूर्णांकerrupt();
पूर्ण
