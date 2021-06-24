<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *  S390 version
 *    Copyright IBM Corp. 1999, 2000
 */

#अगर_अघोषित _ASM_S390_SIGCONTEXT_H
#घोषणा _ASM_S390_SIGCONTEXT_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>

#घोषणा __NUM_GPRS		16
#घोषणा __NUM_FPRS		16
#घोषणा __NUM_ACRS		16
#घोषणा __NUM_VXRS		32
#घोषणा __NUM_VXRS_LOW		16
#घोषणा __NUM_VXRS_HIGH		16

#अगर_अघोषित __s390x__

/* Has to be at least _NSIG_WORDS from यंत्र/संकेत.स */
#घोषणा _SIGCONTEXT_NSIG	64
#घोषणा _SIGCONTEXT_NSIG_BPW	32
/* Size of stack frame allocated when calling संकेत handler. */
#घोषणा __SIGNAL_FRAMESIZE	96

#अन्यथा /* __s390x__ */

/* Has to be at least _NSIG_WORDS from यंत्र/संकेत.स */
#घोषणा _SIGCONTEXT_NSIG	64
#घोषणा _SIGCONTEXT_NSIG_BPW	64 
/* Size of stack frame allocated when calling संकेत handler. */
#घोषणा __SIGNAL_FRAMESIZE	160

#पूर्ण_अगर /* __s390x__ */

#घोषणा _SIGCONTEXT_NSIG_WORDS	(_SIGCONTEXT_NSIG / _SIGCONTEXT_NSIG_BPW)
#घोषणा _SIGMASK_COPY_SIZE	(माप(अचिन्हित दीर्घ)*_SIGCONTEXT_NSIG_WORDS)

प्रकार काष्ठा 
अणु
        अचिन्हित दीर्घ mask;
        अचिन्हित दीर्घ addr;
पूर्ण __attribute__ ((aligned(8))) _psw_t;

प्रकार काष्ठा
अणु
	_psw_t psw;
	अचिन्हित दीर्घ gprs[__NUM_GPRS];
	अचिन्हित पूर्णांक  acrs[__NUM_ACRS];
पूर्ण _s390_regs_common;

प्रकार काष्ठा
अणु
	अचिन्हित पूर्णांक fpc;
	अचिन्हित पूर्णांक pad;
	द्विगुन   fprs[__NUM_FPRS];
पूर्ण _s390_fp_regs;

प्रकार काष्ठा
अणु
	_s390_regs_common regs;
	_s390_fp_regs     fpregs;
पूर्ण _sigregs;

प्रकार काष्ठा
अणु
#अगर_अघोषित __s390x__
	अचिन्हित दीर्घ gprs_high[__NUM_GPRS];
#पूर्ण_अगर
	अचिन्हित दीर्घ दीर्घ vxrs_low[__NUM_VXRS_LOW];
	__vector128 vxrs_high[__NUM_VXRS_HIGH];
	अचिन्हित अक्षर __reserved[128];
पूर्ण _sigregs_ext;

काष्ठा sigcontext
अणु
	अचिन्हित दीर्घ	oldmask[_SIGCONTEXT_NSIG_WORDS];
	_sigregs        __user *sregs;
पूर्ण;


#पूर्ण_अगर

