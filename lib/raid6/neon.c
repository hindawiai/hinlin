<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/lib/raid6/neon.c - RAID6 syndrome calculation using ARM NEON पूर्णांकrinsics
 *
 * Copyright (C) 2013 Linaro Ltd <ard.biesheuvel@linaro.org>
 */

#समावेश <linux/raid/pq.h>

#अगर_घोषित __KERNEL__
#समावेश <यंत्र/neon.h>
#अन्यथा
#घोषणा kernel_neon_begin()
#घोषणा kernel_neon_end()
#घोषणा cpu_has_neon()		(1)
#पूर्ण_अगर

/*
 * There are 2 reasons these wrappers are kept in a separate compilation unit
 * from the actual implementations in neonN.c (generated from neon.uc by
 * unroll.awk):
 * - the actual implementations use NEON पूर्णांकrinsics, and the GCC support header
 *   (arm_neon.h) is not fully compatible (type wise) with the kernel;
 * - the neonN.c files are compiled with -mfpu=neon and optimization enabled,
 *   and we have to make sure that we never use *any* NEON/VFP inकाष्ठाions
 *   outside a kernel_neon_begin()/kernel_neon_end() pair.
 */

#घोषणा RAID6_NEON_WRAPPER(_n)						\
	अटल व्योम raid6_neon ## _n ## _gen_syndrome(पूर्णांक disks,	\
					माप_प्रकार bytes, व्योम **ptrs)	\
	अणु								\
		व्योम raid6_neon ## _n  ## _gen_syndrome_real(पूर्णांक,	\
						अचिन्हित दीर्घ, व्योम**);	\
		kernel_neon_begin();					\
		raid6_neon ## _n ## _gen_syndrome_real(disks,		\
					(अचिन्हित दीर्घ)bytes, ptrs);	\
		kernel_neon_end();					\
	पूर्ण								\
	अटल व्योम raid6_neon ## _n ## _xor_syndrome(पूर्णांक disks,	\
					पूर्णांक start, पूर्णांक stop, 		\
					माप_प्रकार bytes, व्योम **ptrs)	\
	अणु								\
		व्योम raid6_neon ## _n  ## _xor_syndrome_real(पूर्णांक,	\
				पूर्णांक, पूर्णांक, अचिन्हित दीर्घ, व्योम**);	\
		kernel_neon_begin();					\
		raid6_neon ## _n ## _xor_syndrome_real(disks,		\
			start, stop, (अचिन्हित दीर्घ)bytes, ptrs);	\
		kernel_neon_end();					\
	पूर्ण								\
	काष्ठा raid6_calls स्थिर raid6_neonx ## _n = अणु			\
		raid6_neon ## _n ## _gen_syndrome,			\
		raid6_neon ## _n ## _xor_syndrome,			\
		raid6_have_neon,					\
		"neonx" #_n,						\
		0							\
	पूर्ण

अटल पूर्णांक raid6_have_neon(व्योम)
अणु
	वापस cpu_has_neon();
पूर्ण

RAID6_NEON_WRAPPER(1);
RAID6_NEON_WRAPPER(2);
RAID6_NEON_WRAPPER(4);
RAID6_NEON_WRAPPER(8);
