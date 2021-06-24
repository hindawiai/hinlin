<शैली गुरु>
/*
 *  linux/arch/h8300/kernel/ptrace_h8s.c
 *    ptrace cpu depend helper functions
 *
 *  Yoshinori Sato <ysato@users.sourceक्रमge.jp>
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file COPYING in the मुख्य directory of
 * this archive क्रम more details.
 */

#समावेश <linux/linkage.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <यंत्र/ptrace.h>

#घोषणा CCR_MASK  0x6f
#घोषणा EXR_TRACE 0x80

/* disable singlestep */
व्योम user_disable_single_step(काष्ठा task_काष्ठा *child)
अणु
	अचिन्हित अक्षर exr;

	exr = h8300_get_reg(child, PT_EXR);
	exr &= ~EXR_TRACE;
	h8300_put_reg(child, PT_EXR, exr);
पूर्ण

/* enable singlestep */
व्योम user_enable_single_step(काष्ठा task_काष्ठा *child)
अणु
	अचिन्हित अक्षर exr;

	exr = h8300_get_reg(child, PT_EXR);
	exr |= EXR_TRACE;
	h8300_put_reg(child, PT_EXR, exr);
पूर्ण

यंत्रlinkage व्योम trace_trap(अचिन्हित दीर्घ bp)
अणु
	(व्योम)bp;
	क्रमce_sig(SIGTRAP);
पूर्ण
