<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SIGUTIL_H
#घोषणा _SIGUTIL_H

पूर्णांक save_fpu_state(काष्ठा pt_regs *regs, __siginfo_fpu_t __user *fpu);
पूर्णांक restore_fpu_state(काष्ठा pt_regs *regs, __siginfo_fpu_t __user *fpu);
पूर्णांक save_rwin_state(पूर्णांक wsaved, __siginfo_rwin_t __user *rwin);
पूर्णांक restore_rwin_state(__siginfo_rwin_t __user *rp);

#पूर्ण_अगर /* _SIGUTIL_H */
