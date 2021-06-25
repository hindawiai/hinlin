<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
// Copyright (C) 2005-2017 Andes Technology Corporation

#अगर_अघोषित _ASMNDS32_SIGCONTEXT_H
#घोषणा _ASMNDS32_SIGCONTEXT_H

/*
 * Signal context काष्ठाure - contains all info to करो with the state
 * beक्रमe the संकेत handler was invoked.  Note: only add new entries
 * to the end of the काष्ठाure.
 */
काष्ठा fpu_काष्ठा अणु
	अचिन्हित दीर्घ दीर्घ fd_regs[32];
	अचिन्हित दीर्घ fpcsr;
	/*
	 * When CONFIG_SUPPORT_DENORMAL_ARITHMETIC is defined, kernel prevents
	 * hardware from treating the denormalized output as an underflow हाल
	 * and rounding it to a normal number. Hence kernel enables the UDF and
	 * IEX trap in the fpcsr रेजिस्टर to step in the calculation.
	 * However, the UDF and IEX trap enable bit in $fpcsr also lose
	 * their use.
	 *
	 * UDF_IEX_trap replaces the feature of UDF and IEX trap enable bit in
	 * $fpcsr to control the trap of underflow and inexact. The bit filed
	 * of UDF_IEX_trap is the same as $fpcsr, 10th bit is used to enable UDF
	 * exception trapping and 11th bit is used to enable IEX exception
	 * trapping.
	 *
	 * UDF_IEX_trap is only modअगरied through fp_udfiex_crtl syscall.
	 * Thereक्रमe, UDF_IEX_trap needn't be saved and restored in each
	 * context चयन.
	 */
	अचिन्हित दीर्घ UDF_IEX_trap;
पूर्ण;

काष्ठा zol_काष्ठा अणु
	अचिन्हित दीर्घ nds32_lc;	/* $LC */
	अचिन्हित दीर्घ nds32_le;	/* $LE */
	अचिन्हित दीर्घ nds32_lb;	/* $LB */
पूर्ण;

काष्ठा sigcontext अणु
	अचिन्हित दीर्घ trap_no;
	अचिन्हित दीर्घ error_code;
	अचिन्हित दीर्घ oldmask;
	अचिन्हित दीर्घ nds32_r0;
	अचिन्हित दीर्घ nds32_r1;
	अचिन्हित दीर्घ nds32_r2;
	अचिन्हित दीर्घ nds32_r3;
	अचिन्हित दीर्घ nds32_r4;
	अचिन्हित दीर्घ nds32_r5;
	अचिन्हित दीर्घ nds32_r6;
	अचिन्हित दीर्घ nds32_r7;
	अचिन्हित दीर्घ nds32_r8;
	अचिन्हित दीर्घ nds32_r9;
	अचिन्हित दीर्घ nds32_r10;
	अचिन्हित दीर्घ nds32_r11;
	अचिन्हित दीर्घ nds32_r12;
	अचिन्हित दीर्घ nds32_r13;
	अचिन्हित दीर्घ nds32_r14;
	अचिन्हित दीर्घ nds32_r15;
	अचिन्हित दीर्घ nds32_r16;
	अचिन्हित दीर्घ nds32_r17;
	अचिन्हित दीर्घ nds32_r18;
	अचिन्हित दीर्घ nds32_r19;
	अचिन्हित दीर्घ nds32_r20;
	अचिन्हित दीर्घ nds32_r21;
	अचिन्हित दीर्घ nds32_r22;
	अचिन्हित दीर्घ nds32_r23;
	अचिन्हित दीर्घ nds32_r24;
	अचिन्हित दीर्घ nds32_r25;
	अचिन्हित दीर्घ nds32_fp;	/* $r28 */
	अचिन्हित दीर्घ nds32_gp;	/* $r29 */
	अचिन्हित दीर्घ nds32_lp;	/* $r30 */
	अचिन्हित दीर्घ nds32_sp;	/* $r31 */
	अचिन्हित दीर्घ nds32_ipc;
	अचिन्हित दीर्घ fault_address;
	अचिन्हित दीर्घ used_math_flag;
	/* FPU Registers */
	काष्ठा fpu_काष्ठा fpu;
	काष्ठा zol_काष्ठा zol;
पूर्ण;

#पूर्ण_अगर
