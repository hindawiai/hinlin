<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2002-2004 H. Peter Anvin - All Rights Reserved
 *
 * ----------------------------------------------------------------------- */

/*
 * raid6/x86.h
 *
 * Definitions common to x86 and x86-64 RAID-6 code only
 */

#अगर_अघोषित LINUX_RAID_RAID6X86_H
#घोषणा LINUX_RAID_RAID6X86_H

#अगर (defined(__i386__) || defined(__x86_64__)) && !defined(__arch_um__)

#अगर_घोषित __KERNEL__ /* Real code */

#समावेश <यंत्र/fpu/api.h>

#अन्यथा /* Dummy code क्रम user space testing */

अटल अंतरभूत व्योम kernel_fpu_begin(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम kernel_fpu_end(व्योम)
अणु
पूर्ण

#घोषणा __aligned(x) __attribute__((aligned(x)))

#घोषणा X86_FEATURE_MMX		(0*32+23) /* Mulसमयdia Extensions */
#घोषणा X86_FEATURE_FXSR	(0*32+24) /* FXSAVE and FXRSTOR inकाष्ठाions
					   * (fast save and restore) */
#घोषणा X86_FEATURE_XMM		(0*32+25) /* Streaming SIMD Extensions */
#घोषणा X86_FEATURE_XMM2	(0*32+26) /* Streaming SIMD Extensions-2 */
#घोषणा X86_FEATURE_XMM3	(4*32+ 0) /* "pni" SSE-3 */
#घोषणा X86_FEATURE_SSSE3	(4*32+ 9) /* Supplemental SSE-3 */
#घोषणा X86_FEATURE_AVX	(4*32+28) /* Advanced Vector Extensions */
#घोषणा X86_FEATURE_AVX2        (9*32+ 5) /* AVX2 inकाष्ठाions */
#घोषणा X86_FEATURE_AVX512F     (9*32+16) /* AVX-512 Foundation */
#घोषणा X86_FEATURE_AVX512DQ    (9*32+17) /* AVX-512 DQ (Double/Quad granular)
					   * Inकाष्ठाions
					   */
#घोषणा X86_FEATURE_AVX512BW    (9*32+30) /* AVX-512 BW (Byte/Word granular)
					   * Inकाष्ठाions
					   */
#घोषणा X86_FEATURE_AVX512VL    (9*32+31) /* AVX-512 VL (128/256 Vector Length)
					   * Extensions
					   */
#घोषणा X86_FEATURE_MMXEXT	(1*32+22) /* AMD MMX extensions */

/* Should work well enough on modern CPUs क्रम testing */
अटल अंतरभूत पूर्णांक boot_cpu_has(पूर्णांक flag)
अणु
	u32 eax, ebx, ecx, edx;

	eax = (flag & 0x100) ? 7 :
		(flag & 0x20) ? 0x80000001 : 1;
	ecx = 0;

	यंत्र अस्थिर("cpuid"
		     : "+a" (eax), "=b" (ebx), "=d" (edx), "+c" (ecx));

	वापस ((flag & 0x100 ? ebx :
		(flag & 0x80) ? ecx : edx) >> (flag & 31)) & 1;
पूर्ण

#पूर्ण_अगर /* ndef __KERNEL__ */

#पूर्ण_अगर
#पूर्ण_अगर
