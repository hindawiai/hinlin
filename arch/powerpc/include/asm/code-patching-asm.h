<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright 2018, Michael Ellerman, IBM Corporation.
 */
#अगर_अघोषित _ASM_POWERPC_CODE_PATCHING_ASM_H
#घोषणा _ASM_POWERPC_CODE_PATCHING_ASM_H

/* Define a "site" that can be patched */
.macro patch_site label name
	.pushsection ".rodata"
	.balign 4
	.global \नame
\नame:
	.4byte	\label - .
	.popsection
.endm

#पूर्ण_अगर /* _ASM_POWERPC_CODE_PATCHING_ASM_H */
