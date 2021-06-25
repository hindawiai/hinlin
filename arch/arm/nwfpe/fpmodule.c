<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/*
    NetWinder Floating Poपूर्णांक Emulator
    (c) Rebel.com, 1998-1999
    (c) Philip Blundell, 1998-1999

    Direct questions, comments to Scott Bambrough <scottb@netwinder.org>

*/

#समावेश "fpa11.h"

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>

/* XXX */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/init.h>

#समावेश <यंत्र/thपढ़ो_notअगरy.h>

#समावेश "softfloat.h"
#समावेश "fpopcode.h"
#समावेश "fpmodule.h"
#समावेश "fpa11.inl"

/* kernel symbols required क्रम संकेत handling */
#अगर_घोषित CONFIG_FPE_NWFPE_XP
#घोषणा NWFPE_BITS "extended"
#अन्यथा
#घोषणा NWFPE_BITS "double"
#पूर्ण_अगर

#अगर_घोषित MODULE
व्योम fp_send_sig(अचिन्हित दीर्घ sig, काष्ठा task_काष्ठा *p, पूर्णांक priv);
#अन्यथा
#घोषणा fp_send_sig	send_sig
#घोषणा kern_fp_enter	fp_enter

बाह्य अक्षर fpe_type[];
#पूर्ण_अगर

अटल पूर्णांक nwfpe_notअगरy(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ cmd, व्योम *v)
अणु
	काष्ठा thपढ़ो_info *thपढ़ो = v;

	अगर (cmd == THREAD_NOTIFY_FLUSH)
		nwfpe_init_fpa(&thपढ़ो->fpstate);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block nwfpe_notअगरier_block = अणु
	.notअगरier_call = nwfpe_notअगरy,
पूर्ण;

/* kernel function prototypes required */
व्योम fp_setup(व्योम);

/* बाह्यal declarations क्रम saved kernel symbols */
बाह्य व्योम (*kern_fp_enter)(व्योम);

/* Original value of fp_enter from kernel beक्रमe patched by fpe_init. */
अटल व्योम (*orig_fp_enter)(व्योम);

/* क्रमward declarations */
बाह्य व्योम nwfpe_enter(व्योम);

अटल पूर्णांक __init fpe_init(व्योम)
अणु
	अगर (माप(FPA11) > माप(जोड़ fp_state)) अणु
		pr_err("nwfpe: bad structure size\n");
		वापस -EINVAL;
	पूर्ण

	अगर (माप(FPREG) != 12) अणु
		pr_err("nwfpe: bad register size\n");
		वापस -EINVAL;
	पूर्ण
	अगर (fpe_type[0] && म_भेद(fpe_type, "nwfpe"))
		वापस 0;

	/* Display title, version and copyright inक्रमmation. */
	pr_info("NetWinder Floating Point Emulator V0.97 ("
	        NWFPE_BITS " precision)\n");

	thपढ़ो_रेजिस्टर_notअगरier(&nwfpe_notअगरier_block);

	/* Save poपूर्णांकer to the old FP handler and then patch ourselves in */
	orig_fp_enter = kern_fp_enter;
	kern_fp_enter = nwfpe_enter;

	वापस 0;
पूर्ण

अटल व्योम __निकास fpe_निकास(व्योम)
अणु
	thपढ़ो_unरेजिस्टर_notअगरier(&nwfpe_notअगरier_block);
	/* Restore the values we saved earlier. */
	kern_fp_enter = orig_fp_enter;
पूर्ण

/*
ScottB:  November 4, 1998

Moved this function out of softभग्न-specialize पूर्णांकo fpmodule.c.
This effectively isolates all the changes required क्रम पूर्णांकegrating with the
Linux kernel पूर्णांकo fpmodule.c.  Porting to NetBSD should only require modअगरying
fpmodule.c to पूर्णांकegrate with the NetBSD kernel (I hope!).

[1/1/99: Not quite true any more unक्रमtunately.  There is Linux-specअगरic
code to access data in user space in some other source files at the 
moment (grep क्रम get_user / put_user calls).  --philb]

This function is called by the SoftFloat routines to उठाओ a भग्नing
poपूर्णांक exception.  We check the trap enable byte in the FPSR, and उठाओ
a संक_भ_त्रुटि exception अगर necessary.  If not the relevant bits in the 
cumulative exceptions flag byte are set and we वापस.
*/

#अगर_घोषित CONFIG_DEBUG_USER
/* By शेष, ignore inexact errors as there are far too many of them to log */
अटल पूर्णांक debug = ~BIT_IXC;
#पूर्ण_अगर

व्योम भग्न_उठाओ(चिन्हित अक्षर flags)
अणु
	रेजिस्टर अचिन्हित पूर्णांक fpsr, cumulativeTraps;

#अगर_घोषित CONFIG_DEBUG_USER
	अगर (flags & debug)
 		prपूर्णांकk(KERN_DEBUG
		       "NWFPE: %s[%d] takes exception %08x at %ps from %08lx\n",
		       current->comm, current->pid, flags,
		       __builtin_वापस_address(0), GET_USERREG()->ARM_pc);
#पूर्ण_अगर

	/* Read fpsr and initialize the cumulativeTraps.  */
	fpsr = पढ़ोFPSR();
	cumulativeTraps = 0;

	/* For each type of exception, the cumulative trap exception bit is only
	   set अगर the corresponding trap enable bit is not set.  */
	अगर ((!(fpsr & BIT_IXE)) && (flags & BIT_IXC))
		cumulativeTraps |= BIT_IXC;
	अगर ((!(fpsr & BIT_UFE)) && (flags & BIT_UFC))
		cumulativeTraps |= BIT_UFC;
	अगर ((!(fpsr & BIT_OFE)) && (flags & BIT_OFC))
		cumulativeTraps |= BIT_OFC;
	अगर ((!(fpsr & BIT_DZE)) && (flags & BIT_DZC))
		cumulativeTraps |= BIT_DZC;
	अगर ((!(fpsr & BIT_IOE)) && (flags & BIT_IOC))
		cumulativeTraps |= BIT_IOC;

	/* Set the cumulative exceptions flags.  */
	अगर (cumulativeTraps)
		ग_लिखोFPSR(fpsr | cumulativeTraps);

	/* Raise an exception अगर necessary.  */
	अगर (fpsr & (flags << 16))
		fp_send_sig(संक_भ_त्रुटि, current, 1);
पूर्ण

module_init(fpe_init);
module_निकास(fpe_निकास);

MODULE_AUTHOR("Scott Bambrough <scottb@rebel.com>");
MODULE_DESCRIPTION("NWFPE floating point emulator (" NWFPE_BITS " precision)");
MODULE_LICENSE("GPL");

#अगर_घोषित CONFIG_DEBUG_USER
module_param(debug, पूर्णांक, 0644);
#पूर्ण_अगर
