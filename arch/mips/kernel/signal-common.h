<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1991, 1992  Linus Torvalds
 * Copyright (C) 1994 - 2000  Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 */

#अगर_अघोषित __SIGNAL_COMMON_H
#घोषणा __SIGNAL_COMMON_H

/* #घोषणा DEBUG_SIG */

#अगर_घोषित DEBUG_SIG
#  define DEBUGP(fmt, args...) prपूर्णांकk("%s: " fmt, __func__, ##args)
#अन्यथा
#  define DEBUGP(fmt, args...)
#पूर्ण_अगर

/*
 * Determine which stack to use..
 */
बाह्य व्योम __user *get_sigframe(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs,
				 माप_प्रकार frame_size);
/* Check and clear pending FPU exceptions in saved CSR */
बाह्य पूर्णांक fpcsr_pending(अचिन्हित पूर्णांक __user *fpcsr);

/* Make sure we will not lose FPU ownership */
#घोषणा lock_fpu_owner()	(अणु preempt_disable(); pagefault_disable(); पूर्ण)
#घोषणा unlock_fpu_owner()	(अणु pagefault_enable(); preempt_enable(); पूर्ण)

/* Assembly functions to move context to/from the FPU */
बाह्य यंत्रlinkage पूर्णांक
_save_fp_context(व्योम __user *fpregs, व्योम __user *csr);
बाह्य यंत्रlinkage पूर्णांक
_restore_fp_context(व्योम __user *fpregs, व्योम __user *csr);

बाह्य यंत्रlinkage पूर्णांक _save_msa_all_upper(व्योम __user *buf);
बाह्य यंत्रlinkage पूर्णांक _restore_msa_all_upper(व्योम __user *buf);

#पूर्ण_अगर	/* __SIGNAL_COMMON_H */
