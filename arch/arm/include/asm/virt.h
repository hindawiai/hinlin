<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2012 Linaro Limited.
 */

#अगर_अघोषित VIRT_H
#घोषणा VIRT_H

#समावेश <यंत्र/ptrace.h>

/*
 * Flag indicating that the kernel was not entered in the same mode on every
 * CPU.  The zImage loader stashes this value in an SPSR, so we need an
 * architecturally defined flag bit here.
 */
#घोषणा BOOT_CPU_MODE_MISMATCH	PSR_N_BIT

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/cacheflush.h>

#अगर_घोषित CONFIG_ARM_VIRT_EXT
/*
 * __boot_cpu_mode records what mode the primary CPU was booted in.
 * A correctly-implemented bootloader must start all CPUs in the same mode:
 * अगर it fails to करो this, the flag BOOT_CPU_MODE_MISMATCH is set to indicate
 * that some CPU(s) were booted in a dअगरferent mode.
 *
 * This allows the kernel to flag an error when the secondaries have come up.
 */
बाह्य पूर्णांक __boot_cpu_mode;

अटल अंतरभूत व्योम sync_boot_mode(व्योम)
अणु
	/*
	 * As secondaries ग_लिखो to __boot_cpu_mode with caches disabled, we
	 * must flush the corresponding cache entries to ensure the visibility
	 * of their ग_लिखोs.
	 */
	sync_cache_r(&__boot_cpu_mode);
पूर्ण

#अन्यथा
#घोषणा __boot_cpu_mode	(SVC_MODE)
#घोषणा sync_boot_mode()
#पूर्ण_अगर

#अगर_अघोषित ZIMAGE
व्योम hyp_mode_check(व्योम);

/* Reports the availability of HYP mode */
अटल अंतरभूत bool is_hyp_mode_available(व्योम)
अणु
	वापस ((__boot_cpu_mode & MODE_MASK) == HYP_MODE &&
		!(__boot_cpu_mode & BOOT_CPU_MODE_MISMATCH));
पूर्ण

/* Check अगर the bootloader has booted CPUs in dअगरferent modes */
अटल अंतरभूत bool is_hyp_mode_mismatched(व्योम)
अणु
	वापस !!(__boot_cpu_mode & BOOT_CPU_MODE_MISMATCH);
पूर्ण

अटल अंतरभूत bool is_kernel_in_hyp_mode(व्योम)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर

#अन्यथा

/* Only assembly code should need those */

#घोषणा HVC_SET_VECTORS 0
#घोषणा HVC_SOFT_RESTART 1

#पूर्ण_अगर /* __ASSEMBLY__ */

#घोषणा HVC_STUB_ERR	0xbadca11

#पूर्ण_अगर /* ! VIRT_H */
