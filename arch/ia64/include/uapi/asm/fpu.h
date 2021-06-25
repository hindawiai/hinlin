<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_IA64_FPU_H
#घोषणा _ASM_IA64_FPU_H

/*
 * Copyright (C) 1998, 1999, 2002, 2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */

#समावेश <linux/types.h>

/* भग्नing poपूर्णांक status रेजिस्टर: */
#घोषणा FPSR_TRAP_VD	(1 << 0)	/* invalid op trap disabled */
#घोषणा FPSR_TRAP_DD	(1 << 1)	/* denormal trap disabled */
#घोषणा FPSR_TRAP_ZD	(1 << 2)	/* zero-भागide trap disabled */
#घोषणा FPSR_TRAP_OD	(1 << 3)	/* overflow trap disabled */
#घोषणा FPSR_TRAP_UD	(1 << 4)	/* underflow trap disabled */
#घोषणा FPSR_TRAP_ID	(1 << 5)	/* inexact trap disabled */
#घोषणा FPSR_S0(x)	((x) <<  6)
#घोषणा FPSR_S1(x)	((x) << 19)
#घोषणा FPSR_S2(x)	(__IA64_UL(x) << 32)
#घोषणा FPSR_S3(x)	(__IA64_UL(x) << 45)

/* भग्नing-poपूर्णांक status field controls: */
#घोषणा FPSF_FTZ	(1 << 0)		/* flush-to-zero */
#घोषणा FPSF_WRE	(1 << 1)		/* widest-range exponent */
#घोषणा FPSF_PC(x)	(((x) & 0x3) << 2)	/* precision control */
#घोषणा FPSF_RC(x)	(((x) & 0x3) << 4)	/* rounding control */
#घोषणा FPSF_TD		(1 << 6)		/* trap disabled */

/* भग्नing-poपूर्णांक status field flags: */
#घोषणा FPSF_V		(1 <<  7)		/* invalid operation flag */
#घोषणा FPSF_D		(1 <<  8)		/* denormal/unnormal opeअक्रम flag */
#घोषणा FPSF_Z		(1 <<  9)		/* zero भागide (IEEE) flag */
#घोषणा FPSF_O		(1 << 10)		/* overflow (IEEE) flag */
#घोषणा FPSF_U		(1 << 11)		/* underflow (IEEE) flag */
#घोषणा FPSF_I		(1 << 12)		/* inexact (IEEE) flag) */

/* भग्नing-poपूर्णांक rounding control: */
#घोषणा FPRC_NEAREST	0x0
#घोषणा FPRC_NEGINF	0x1
#घोषणा FPRC_POSINF	0x2
#घोषणा FPRC_TRUNC	0x3

#घोषणा FPSF_DEFAULT	(FPSF_PC (0x3) | FPSF_RC (FPRC_NEAREST))

/* This शेष value is the same as HP-UX uses.  Don't change it
   without a very good reason.  */
#घोषणा FPSR_DEFAULT	(FPSR_TRAP_VD | FPSR_TRAP_DD | FPSR_TRAP_ZD	\
			 | FPSR_TRAP_OD | FPSR_TRAP_UD | FPSR_TRAP_ID	\
			 | FPSR_S0 (FPSF_DEFAULT)			\
			 | FPSR_S1 (FPSF_DEFAULT | FPSF_TD | FPSF_WRE)	\
			 | FPSR_S2 (FPSF_DEFAULT | FPSF_TD)		\
			 | FPSR_S3 (FPSF_DEFAULT | FPSF_TD))

# अगरndef __ASSEMBLY__

काष्ठा ia64_fpreg अणु
	जोड़ अणु
		अचिन्हित दीर्घ bits[2];
		दीर्घ द्विगुन __dummy;	/* क्रमce 16-byte alignment */
	पूर्ण u;
पूर्ण;

# endअगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_IA64_FPU_H */
