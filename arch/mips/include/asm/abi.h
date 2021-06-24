<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2005, 06 by Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 2005 MIPS Technologies, Inc.
 */
#अगर_अघोषित _ASM_ABI_H
#घोषणा _ASM_ABI_H

#समावेश <linux/संकेत_types.h>

#समावेश <यंत्र/संकेत.स>
#समावेश <यंत्र/siginfo.h>
#समावेश <यंत्र/vdso.h>

काष्ठा mips_abi अणु
	पूर्णांक (* स्थिर setup_frame)(व्योम *sig_वापस, काष्ठा kसंकेत *ksig,
				  काष्ठा pt_regs *regs, sigset_t *set);
	पूर्णांक (* स्थिर setup_rt_frame)(व्योम *sig_वापस, काष्ठा kसंकेत *ksig,
				     काष्ठा pt_regs *regs, sigset_t *set);
	स्थिर अचिन्हित दीर्घ	restart;

	अचिन्हित	off_sc_fpregs;
	अचिन्हित	off_sc_fpc_csr;
	अचिन्हित	off_sc_used_math;

	काष्ठा mips_vdso_image *vdso;
पूर्ण;

#पूर्ण_अगर /* _ASM_ABI_H */
