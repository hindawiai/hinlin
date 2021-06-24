<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASMARM_SIGCONTEXT_H
#घोषणा _ASMARM_SIGCONTEXT_H

/*
 * Signal context काष्ठाure - contains all info to करो with the state
 * beक्रमe the संकेत handler was invoked.  Note: only add new entries
 * to the end of the काष्ठाure.
 */
काष्ठा sigcontext अणु
	अचिन्हित दीर्घ trap_no;
	अचिन्हित दीर्घ error_code;
	अचिन्हित दीर्घ oldmask;
	अचिन्हित दीर्घ arm_r0;
	अचिन्हित दीर्घ arm_r1;
	अचिन्हित दीर्घ arm_r2;
	अचिन्हित दीर्घ arm_r3;
	अचिन्हित दीर्घ arm_r4;
	अचिन्हित दीर्घ arm_r5;
	अचिन्हित दीर्घ arm_r6;
	अचिन्हित दीर्घ arm_r7;
	अचिन्हित दीर्घ arm_r8;
	अचिन्हित दीर्घ arm_r9;
	अचिन्हित दीर्घ arm_r10;
	अचिन्हित दीर्घ arm_fp;
	अचिन्हित दीर्घ arm_ip;
	अचिन्हित दीर्घ arm_sp;
	अचिन्हित दीर्घ arm_lr;
	अचिन्हित दीर्घ arm_pc;
	अचिन्हित दीर्घ arm_cpsr;
	अचिन्हित दीर्घ fault_address;
पूर्ण;


#पूर्ण_अगर
