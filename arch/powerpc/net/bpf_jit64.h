<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * bpf_jit64.h: BPF JIT compiler क्रम PPC64
 *
 * Copyright 2016 Naveen N. Rao <naveen.n.rao@linux.vnet.ibm.com>
 *		  IBM Corporation
 */
#अगर_अघोषित _BPF_JIT64_H
#घोषणा _BPF_JIT64_H

#समावेश "bpf_jit.h"

/*
 * Stack layout:
 * Ensure the top half (upto local_पंचांगp_var) stays consistent
 * with our redzone usage.
 *
 *		[	prev sp		] <-------------
 *		[   nv gpr save area	] 6*8		|
 *		[    tail_call_cnt	] 8		|
 *		[    local_पंचांगp_var	] 8		|
 * fp (r31) -->	[   ebpf stack space	] upto 512	|
 *		[     frame header	] 32/112	|
 * sp (r1) --->	[    stack poपूर्णांकer	] --------------
 */

/* क्रम gpr non अस्थिर रेजिस्टरs BPG_REG_6 to 10 */
#घोषणा BPF_PPC_STACK_SAVE	(6*8)
/* क्रम bpf JIT code पूर्णांकernal usage */
#घोषणा BPF_PPC_STACK_LOCALS	16
/* stack frame excluding BPF stack, ensure this is quadword aligned */
#घोषणा BPF_PPC_STACKFRAME	(STACK_FRAME_MIN_SIZE + \
				 BPF_PPC_STACK_LOCALS + BPF_PPC_STACK_SAVE)

#अगर_अघोषित __ASSEMBLY__

/* BPF रेजिस्टर usage */
#घोषणा TMP_REG_1	(MAX_BPF_JIT_REG + 0)
#घोषणा TMP_REG_2	(MAX_BPF_JIT_REG + 1)

/* BPF to ppc रेजिस्टर mappings */
स्थिर पूर्णांक b2p[MAX_BPF_JIT_REG + 2] = अणु
	/* function वापस value */
	[BPF_REG_0] = 8,
	/* function arguments */
	[BPF_REG_1] = 3,
	[BPF_REG_2] = 4,
	[BPF_REG_3] = 5,
	[BPF_REG_4] = 6,
	[BPF_REG_5] = 7,
	/* non अस्थिर रेजिस्टरs */
	[BPF_REG_6] = 27,
	[BPF_REG_7] = 28,
	[BPF_REG_8] = 29,
	[BPF_REG_9] = 30,
	/* frame poपूर्णांकer aka BPF_REG_10 */
	[BPF_REG_FP] = 31,
	/* eBPF jit पूर्णांकernal रेजिस्टरs */
	[BPF_REG_AX] = 2,
	[TMP_REG_1] = 9,
	[TMP_REG_2] = 10
पूर्ण;

/* PPC NVR range -- update this अगर we ever use NVRs below r27 */
#घोषणा BPF_PPC_NVR_MIN		27

/*
 * WARNING: These can use TMP_REG_2 अगर the offset is not at word boundary,
 * so ensure that it isn't in use alपढ़ोy.
 */
#घोषणा PPC_BPF_LL(r, base, i) करो अणु					      \
				अगर ((i) % 4) अणु				      \
					EMIT(PPC_RAW_LI(b2p[TMP_REG_2], (i)));\
					EMIT(PPC_RAW_LDX(r, base,	      \
							b2p[TMP_REG_2]));     \
				पूर्ण अन्यथा					      \
					EMIT(PPC_RAW_LD(r, base, i));	      \
				पूर्ण जबतक(0)
#घोषणा PPC_BPF_STL(r, base, i) करो अणु					      \
				अगर ((i) % 4) अणु				      \
					EMIT(PPC_RAW_LI(b2p[TMP_REG_2], (i)));\
					EMIT(PPC_RAW_STDX(r, base,	      \
							b2p[TMP_REG_2]));     \
				पूर्ण अन्यथा					      \
					EMIT(PPC_RAW_STD(r, base, i));	      \
				पूर्ण जबतक(0)
#घोषणा PPC_BPF_STLU(r, base, i) करो अणु EMIT(PPC_RAW_STDU(r, base, i)); पूर्ण जबतक(0)

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर
