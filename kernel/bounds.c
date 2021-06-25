<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generate definitions needed by the preprocessor.
 * This code generates raw यंत्र output which is post-processed
 * to extract and क्रमmat the required data.
 */

#घोषणा __GENERATING_BOUNDS_H
/* Include headers that define the क्रमागत स्थिरants of पूर्णांकerest */
#समावेश <linux/page-flags.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/kbuild.h>
#समावेश <linux/log2.h>
#समावेश <linux/spinlock_types.h>

पूर्णांक मुख्य(व्योम)
अणु
	/* The क्रमागत स्थिरants to put पूर्णांकo include/generated/bounds.h */
	DEFINE(NR_PAGEFLAGS, __NR_PAGEFLAGS);
	DEFINE(MAX_NR_ZONES, __MAX_NR_ZONES);
#अगर_घोषित CONFIG_SMP
	DEFINE(NR_CPUS_BITS, ilog2(CONFIG_NR_CPUS));
#पूर्ण_अगर
	DEFINE(SPINLOCK_SIZE, माप(spinlock_t));
	/* End of स्थिरants */

	वापस 0;
पूर्ण
