<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __ASM_SH_CPU_FEATURES_H
#घोषणा __ASM_SH_CPU_FEATURES_H

/*
 * Processor flags
 *
 * Note: When adding a new flag, keep cpu_flags[] in
 * arch/sh/kernel/setup.c in sync so symbolic name
 * mapping of the processor flags has a chance of being
 * reasonably accurate.
 *
 * These flags are also available through the ELF
 * auxiliary vector as AT_HWCAP.
 */
#घोषणा CPU_HAS_FPU		0x0001	/* Hardware FPU support */
#घोषणा CPU_HAS_P2_FLUSH_BUG	0x0002	/* Need to flush the cache in P2 area */
#घोषणा CPU_HAS_MMU_PAGE_ASSOC	0x0004	/* SH3: TLB way selection bit support */
#घोषणा CPU_HAS_DSP		0x0008	/* SH-DSP: DSP support */
#घोषणा CPU_HAS_PERF_COUNTER	0x0010	/* Hardware perक्रमmance counters */
#घोषणा CPU_HAS_PTEA		0x0020	/* PTEA रेजिस्टर */
#घोषणा CPU_HAS_LLSC		0x0040	/* movli.l/movco.l */
#घोषणा CPU_HAS_L2_CACHE	0x0080	/* Secondary cache / URAM */
#घोषणा CPU_HAS_OP32		0x0100	/* 32-bit inकाष्ठाion support */
#घोषणा CPU_HAS_PTEAEX		0x0200	/* PTE ASID Extension support */
#घोषणा CPU_HAS_CAS_L		0x0400	/* cas.l atomic compare-and-swap */

#पूर्ण_अगर /* __ASM_SH_CPU_FEATURES_H */
