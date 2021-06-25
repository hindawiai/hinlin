<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PTRACE32_H
#घोषणा _PTRACE32_H

#समावेश <यंत्र/ptrace.h>    /* needed क्रम NUM_CR_WORDS */
#समावेश "compat_linux.h"  /* needed क्रम psw_compat_t */

काष्ठा compat_per_काष्ठा_kernel अणु
	__u32 cr9;		/* PER control bits */
	__u32 cr10;		/* PER starting address */
	__u32 cr11;		/* PER ending address */
	__u32 bits;		/* Obsolete software bits */
	__u32 starting_addr;	/* User specअगरied start address */
	__u32 ending_addr;	/* User specअगरied end address */
	__u16 perc_aपंचांगid;	/* PER trap ATMID */
	__u32 address;		/* PER trap inकाष्ठाion address */
	__u8  access_id;	/* PER trap access identअगरication */
पूर्ण;

काष्ठा compat_user_regs_काष्ठा
अणु
	psw_compat_t psw;
	u32 gprs[NUM_GPRS];
	u32 acrs[NUM_ACRS];
	u32 orig_gpr2;
	/* nb: there's a 4-byte hole here */
	s390_fp_regs fp_regs;
	/*
	 * These per रेजिस्टरs are in here so that gdb can modअगरy them
	 * itself as there is no "official" ptrace पूर्णांकerface क्रम hardware
	 * watchpoपूर्णांकs. This is the way पूर्णांकel करोes it.
	 */
	काष्ठा compat_per_काष्ठा_kernel per_info;
	u32  ieee_inकाष्ठाion_poपूर्णांकer;	/* obsolete, always 0 */
पूर्ण;

काष्ठा compat_user अणु
	/* We start with the रेजिस्टरs, to mimic the way that "memory"
	   is वापसed from the ptrace(3,...) function.  */
	काष्ठा compat_user_regs_काष्ठा regs;
	/* The rest of this junk is to help gdb figure out what goes where */
	u32 u_tsize;		/* Text segment size (pages). */
	u32 u_dsize;	        /* Data segment size (pages). */
	u32 u_ssize;	        /* Stack segment size (pages). */
	u32 start_code;         /* Starting भव address of text. */
	u32 start_stack;	/* Starting भव address of stack area.
				   This is actually the bottom of the stack,
				   the top of the stack is always found in the
				   esp रेजिस्टर.  */
	s32 संकेत;     	 /* Signal that caused the core dump. */
	u32 u_ar0;               /* Used by gdb to help find the values क्रम */
	                         /* the रेजिस्टरs. */
	u32 magic;		 /* To uniquely identअगरy a core file */
	अक्षर u_comm[32];	 /* User command that was responsible */
पूर्ण;

प्रकार काष्ठा
अणु
	__u32   len;
	__u32   kernel_addr;
	__u32   process_addr;
पूर्ण compat_ptrace_area;

#पूर्ण_अगर /* _PTRACE32_H */
