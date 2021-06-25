<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  S390 version
 *    Copyright IBM Corp. 1999, 2000
 *    Author(s): Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)
 */
#अगर_अघोषित _S390_PTRACE_H
#घोषणा _S390_PTRACE_H

#समावेश <linux/bits.h>
#समावेश <uapi/यंत्र/ptrace.h>

#घोषणा PIF_SYSCALL		0	/* inside a प्रणाली call */
#घोषणा PIF_SYSCALL_RESTART	1	/* restart the current प्रणाली call */
#घोषणा PIF_SYSCALL_RET_SET	2	/* वापस value was set via ptrace */
#घोषणा PIF_GUEST_FAULT		3	/* indicates program check in sie64a */

#घोषणा _PIF_SYSCALL		BIT(PIF_SYSCALL)
#घोषणा _PIF_SYSCALL_RESTART	BIT(PIF_SYSCALL_RESTART)
#घोषणा _PIF_SYSCALL_RET_SET	BIT(PIF_SYSCALL_RET_SET)
#घोषणा _PIF_GUEST_FAULT	BIT(PIF_GUEST_FAULT)

#अगर_अघोषित __ASSEMBLY__

#घोषणा PSW_KERNEL_BITS	(PSW_DEFAULT_KEY | PSW_MASK_BASE | PSW_ASC_HOME | \
			 PSW_MASK_EA | PSW_MASK_BA)
#घोषणा PSW_USER_BITS	(PSW_MASK_DAT | PSW_MASK_IO | PSW_MASK_EXT | \
			 PSW_DEFAULT_KEY | PSW_MASK_BASE | PSW_MASK_MCHECK | \
			 PSW_MASK_PSTATE | PSW_ASC_PRIMARY)

काष्ठा psw_bits अणु
	अचिन्हित दीर्घ	     :	1;
	अचिन्हित दीर्घ per    :	1; /* PER-Mask */
	अचिन्हित दीर्घ	     :	3;
	अचिन्हित दीर्घ dat    :	1; /* DAT Mode */
	अचिन्हित दीर्घ io     :	1; /* Input/Output Mask */
	अचिन्हित दीर्घ ext    :	1; /* External Mask */
	अचिन्हित दीर्घ key    :	4; /* PSW Key */
	अचिन्हित दीर्घ	     :	1;
	अचिन्हित दीर्घ mcheck :	1; /* Machine-Check Mask */
	अचिन्हित दीर्घ रुको   :	1; /* Wait State */
	अचिन्हित दीर्घ pstate :	1; /* Problem State */
	अचिन्हित दीर्घ as     :	2; /* Address Space Control */
	अचिन्हित दीर्घ cc     :	2; /* Condition Code */
	अचिन्हित दीर्घ pm     :	4; /* Program Mask */
	अचिन्हित दीर्घ ri     :	1; /* Runसमय Instrumentation */
	अचिन्हित दीर्घ	     :	6;
	अचिन्हित दीर्घ eaba   :	2; /* Addressing Mode */
	अचिन्हित दीर्घ	     : 31;
	अचिन्हित दीर्घ ia     : 64; /* Inकाष्ठाion Address */
पूर्ण;

क्रमागत अणु
	PSW_BITS_AMODE_24BIT = 0,
	PSW_BITS_AMODE_31BIT = 1,
	PSW_BITS_AMODE_64BIT = 3
पूर्ण;

क्रमागत अणु
	PSW_BITS_AS_PRIMARY	= 0,
	PSW_BITS_AS_ACCREG	= 1,
	PSW_BITS_AS_SECONDARY	= 2,
	PSW_BITS_AS_HOME	= 3
पूर्ण;

#घोषणा psw_bits(__psw) (*(अणु			\
	typecheck(psw_t, __psw);		\
	&(*(काष्ठा psw_bits *)(&(__psw)));	\
पूर्ण))

#घोषणा PGM_INT_CODE_MASK	0x7f
#घोषणा PGM_INT_CODE_PER	0x80

/*
 * The pt_regs काष्ठा defines the way the रेजिस्टरs are stored on
 * the stack during a प्रणाली call.
 */
काष्ठा pt_regs 
अणु
	जोड़ अणु
		user_pt_regs user_regs;
		काष्ठा अणु
			अचिन्हित दीर्घ args[1];
			psw_t psw;
			अचिन्हित दीर्घ gprs[NUM_GPRS];
		पूर्ण;
	पूर्ण;
	अचिन्हित दीर्घ orig_gpr2;
	अचिन्हित पूर्णांक पूर्णांक_code;
	अचिन्हित पूर्णांक पूर्णांक_parm;
	अचिन्हित दीर्घ पूर्णांक_parm_दीर्घ;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ cr1;
पूर्ण;

/*
 * Program event recording (PER) रेजिस्टर set.
 */
काष्ठा per_regs अणु
	अचिन्हित दीर्घ control;		/* PER control bits */
	अचिन्हित दीर्घ start;		/* PER starting address */
	अचिन्हित दीर्घ end;		/* PER ending address */
पूर्ण;

/*
 * PER event contains inक्रमmation about the cause of the last PER exception.
 */
काष्ठा per_event अणु
	अचिन्हित लघु cause;		/* PER code, ATMID and AI */
	अचिन्हित दीर्घ address;		/* PER address */
	अचिन्हित अक्षर paid;		/* PER access identअगरication */
पूर्ण;

/*
 * Simplअगरied per_info काष्ठाure used to decode the ptrace user space ABI.
 */
काष्ठा per_काष्ठा_kernel अणु
	अचिन्हित दीर्घ cr9;		/* PER control bits */
	अचिन्हित दीर्घ cr10;		/* PER starting address */
	अचिन्हित दीर्घ cr11;		/* PER ending address */
	अचिन्हित दीर्घ bits;		/* Obsolete software bits */
	अचिन्हित दीर्घ starting_addr;	/* User specअगरied start address */
	अचिन्हित दीर्घ ending_addr;	/* User specअगरied end address */
	अचिन्हित लघु perc_aपंचांगid;	/* PER trap ATMID */
	अचिन्हित दीर्घ address;		/* PER trap inकाष्ठाion address */
	अचिन्हित अक्षर access_id;	/* PER trap access identअगरication */
पूर्ण;

#घोषणा PER_EVENT_MASK			0xEB000000UL

#घोषणा PER_EVENT_BRANCH		0x80000000UL
#घोषणा PER_EVENT_IFETCH		0x40000000UL
#घोषणा PER_EVENT_STORE			0x20000000UL
#घोषणा PER_EVENT_STORE_REAL		0x08000000UL
#घोषणा PER_EVENT_TRANSACTION_END	0x02000000UL
#घोषणा PER_EVENT_शून्यIFICATION		0x01000000UL

#घोषणा PER_CONTROL_MASK		0x00e00000UL

#घोषणा PER_CONTROL_BRANCH_ADDRESS	0x00800000UL
#घोषणा PER_CONTROL_SUSPENSION		0x00400000UL
#घोषणा PER_CONTROL_ALTERATION		0x00200000UL

अटल अंतरभूत व्योम set_pt_regs_flag(काष्ठा pt_regs *regs, पूर्णांक flag)
अणु
	regs->flags |= (1UL << flag);
पूर्ण

अटल अंतरभूत व्योम clear_pt_regs_flag(काष्ठा pt_regs *regs, पूर्णांक flag)
अणु
	regs->flags &= ~(1UL << flag);
पूर्ण

अटल अंतरभूत पूर्णांक test_pt_regs_flag(काष्ठा pt_regs *regs, पूर्णांक flag)
अणु
	वापस !!(regs->flags & (1UL << flag));
पूर्ण

/*
 * These are defined as per linux/ptrace.h, which see.
 */
#घोषणा arch_has_single_step()	(1)
#घोषणा arch_has_block_step()	(1)

#घोषणा user_mode(regs) (((regs)->psw.mask & PSW_MASK_PSTATE) != 0)
#घोषणा inकाष्ठाion_poपूर्णांकer(regs) ((regs)->psw.addr)
#घोषणा user_stack_poपूर्णांकer(regs)((regs)->gprs[15])
#घोषणा profile_pc(regs) inकाष्ठाion_poपूर्णांकer(regs)

अटल अंतरभूत दीर्घ regs_वापस_value(काष्ठा pt_regs *regs)
अणु
	वापस regs->gprs[2];
पूर्ण

अटल अंतरभूत व्योम inकाष्ठाion_poपूर्णांकer_set(काष्ठा pt_regs *regs,
					   अचिन्हित दीर्घ val)
अणु
	regs->psw.addr = val;
पूर्ण

पूर्णांक regs_query_रेजिस्टर_offset(स्थिर अक्षर *name);
स्थिर अक्षर *regs_query_रेजिस्टर_name(अचिन्हित पूर्णांक offset);
अचिन्हित दीर्घ regs_get_रेजिस्टर(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक offset);
अचिन्हित दीर्घ regs_get_kernel_stack_nth(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक n);

अटल अंतरभूत अचिन्हित दीर्घ kernel_stack_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	वापस regs->gprs[15];
पूर्ण

अटल अंतरभूत व्योम regs_set_वापस_value(काष्ठा pt_regs *regs, अचिन्हित दीर्घ rc)
अणु
	regs->gprs[2] = rc;
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _S390_PTRACE_H */
