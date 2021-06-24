<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Register definitions क्रम the Hexagon architecture
 */


#अगर_अघोषित _ASM_REGISTERS_H
#घोषणा _ASM_REGISTERS_H

#अगर_अघोषित __ASSEMBLY__

/*  See kernel/entry.S क्रम further करोcumentation.  */

/*
 * Entry code copies the event record out of guest रेजिस्टरs पूर्णांकo
 * this काष्ठाure (which is on the stack).
 */

काष्ठा hvm_event_record अणु
	अचिन्हित दीर्घ vmel;     /* Event Linkage (वापस address) */
	अचिन्हित दीर्घ vmest;    /* Event context - pre-event SSR values */
	अचिन्हित दीर्घ vmpsp;    /* Previous stack poपूर्णांकer */
	अचिन्हित दीर्घ vmbadva;  /* Bad भव address क्रम addressing events */
पूर्ण;

काष्ठा pt_regs अणु
	दीर्घ restart_r0;        /* R0 checkpoपूर्णांक क्रम syscall restart */
	दीर्घ syscall_nr;        /* Only used in प्रणाली calls */
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ usr;
			अचिन्हित दीर्घ preds;
		पूर्ण;
		दीर्घ दीर्घ पूर्णांक predsusr;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ m0;
			अचिन्हित दीर्घ m1;
		पूर्ण;
		दीर्घ दीर्घ पूर्णांक m1m0;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ sa1;
			अचिन्हित दीर्घ lc1;
		पूर्ण;
		दीर्घ दीर्घ पूर्णांक lc1sa1;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ sa0;
			अचिन्हित दीर्घ lc0;
		पूर्ण;
		दीर्घ दीर्घ पूर्णांक lc0sa0;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ ugp;
			अचिन्हित दीर्घ gp;
		पूर्ण;
		दीर्घ दीर्घ पूर्णांक gpugp;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ cs0;
			अचिन्हित दीर्घ cs1;
		पूर्ण;
		दीर्घ दीर्घ पूर्णांक cs1cs0;
	पूर्ण;
	/*
	* Be extremely careful with rearranging these, अगर at all.  Some code
	* assumes the 32 रेजिस्टरs exist exactly like this in memory;
	* e.g. kernel/ptrace.c
	* e.g. kernel/संकेत.c (restore_sigcontext)
	*/
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ r00;
			अचिन्हित दीर्घ r01;
		पूर्ण;
		दीर्घ दीर्घ पूर्णांक r0100;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ r02;
			अचिन्हित दीर्घ r03;
		पूर्ण;
		दीर्घ दीर्घ पूर्णांक r0302;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ r04;
			अचिन्हित दीर्घ r05;
		पूर्ण;
		दीर्घ दीर्घ पूर्णांक r0504;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ r06;
			अचिन्हित दीर्घ r07;
		पूर्ण;
		दीर्घ दीर्घ पूर्णांक r0706;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ r08;
			अचिन्हित दीर्घ r09;
		पूर्ण;
		दीर्घ दीर्घ पूर्णांक r0908;
	पूर्ण;
	जोड़ अणु
	       काष्ठा अणु
			अचिन्हित दीर्घ r10;
			अचिन्हित दीर्घ r11;
	       पूर्ण;
	       दीर्घ दीर्घ पूर्णांक r1110;
	पूर्ण;
	जोड़ अणु
	       काष्ठा अणु
			अचिन्हित दीर्घ r12;
			अचिन्हित दीर्घ r13;
	       पूर्ण;
	       दीर्घ दीर्घ पूर्णांक r1312;
	पूर्ण;
	जोड़ अणु
	       काष्ठा अणु
			अचिन्हित दीर्घ r14;
			अचिन्हित दीर्घ r15;
	       पूर्ण;
	       दीर्घ दीर्घ पूर्णांक r1514;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ r16;
			अचिन्हित दीर्घ r17;
		पूर्ण;
		दीर्घ दीर्घ पूर्णांक r1716;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ r18;
			अचिन्हित दीर्घ r19;
		पूर्ण;
		दीर्घ दीर्घ पूर्णांक r1918;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ r20;
			अचिन्हित दीर्घ r21;
		पूर्ण;
		दीर्घ दीर्घ पूर्णांक r2120;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ r22;
			अचिन्हित दीर्घ r23;
		पूर्ण;
		दीर्घ दीर्घ पूर्णांक r2322;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ r24;
			अचिन्हित दीर्घ r25;
		पूर्ण;
		दीर्घ दीर्घ पूर्णांक r2524;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ r26;
			अचिन्हित दीर्घ r27;
		पूर्ण;
		दीर्घ दीर्घ पूर्णांक r2726;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ r28;
			अचिन्हित दीर्घ r29;
	       पूर्ण;
	       दीर्घ दीर्घ पूर्णांक r2928;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ r30;
			अचिन्हित दीर्घ r31;
		पूर्ण;
		दीर्घ दीर्घ पूर्णांक r3130;
	पूर्ण;
	/* VM dispatch pushes event record onto stack - we can build on it */
	काष्ठा hvm_event_record hvmer;
पूर्ण;

/* Defines to conveniently access the values  */

/*
 * As of the VM spec 0.5, these रेजिस्टरs are now set/retrieved via a
 * VM call.  On the in-bound side, we just fetch the values
 * at the entry poपूर्णांकs and stuff them पूर्णांकo the old record in pt_regs.
 * However, on the outbound side, probably at VM rte, we set the
 * रेजिस्टरs back.
 */

#घोषणा pt_elr(regs) ((regs)->hvmer.vmel)
#घोषणा pt_set_elr(regs, val) ((regs)->hvmer.vmel = (val))
#घोषणा pt_cause(regs) ((regs)->hvmer.vmest & (HVM_VMEST_CAUSE_MSK))
#घोषणा user_mode(regs) \
	(((regs)->hvmer.vmest & (HVM_VMEST_UM_MSK << HVM_VMEST_UM_SFT)) != 0)
#घोषणा पूर्णांकs_enabled(regs) \
	(((regs)->hvmer.vmest & (HVM_VMEST_IE_MSK << HVM_VMEST_IE_SFT)) != 0)
#घोषणा pt_psp(regs) ((regs)->hvmer.vmpsp)
#घोषणा pt_badva(regs) ((regs)->hvmer.vmbadva)

#घोषणा pt_set_singlestep(regs) ((regs)->hvmer.vmest |= (1<<HVM_VMEST_SS_SFT))
#घोषणा pt_clr_singlestep(regs) ((regs)->hvmer.vmest &= ~(1<<HVM_VMEST_SS_SFT))

#घोषणा pt_set_rte_sp(regs, sp) करो अणु\
	pt_psp(regs) = (regs)->r29 = (sp);\
	पूर्ण जबतक (0)

#घोषणा pt_set_kmode(regs) \
	(regs)->hvmer.vmest = (HVM_VMEST_IE_MSK << HVM_VMEST_IE_SFT)

#घोषणा pt_set_usermode(regs) \
	(regs)->hvmer.vmest = (HVM_VMEST_UM_MSK << HVM_VMEST_UM_SFT) \
			    | (HVM_VMEST_IE_MSK << HVM_VMEST_IE_SFT)

#पूर्ण_अगर  /*  अगरndef __ASSEMBLY  */

#पूर्ण_अगर
