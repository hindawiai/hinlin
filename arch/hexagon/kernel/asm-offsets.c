<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 1996 David S. Miller
 * Copyright (C) 1997, 1998, 1999, 2000, 2001, 2002, 2003 Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 * Kevin Kissell, kevink@mips.com and Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 2000 MIPS Technologies, Inc.
 *
 * Copyright (c) 2010-2012, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/compat.h>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kbuild.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/processor.h>

/*  This file is used to produce यंत्र/linkerscript स्थिरants from header
    files typically used in c.  Specअगरically, it generates यंत्र-offsets.h  */

पूर्णांक मुख्य(व्योम)
अणु
	COMMENT("This is a comment.");
	/*  might get these from somewhere अन्यथा.  */
	DEFINE(_PAGE_SIZE, PAGE_SIZE);
	DEFINE(_PAGE_SHIFT, PAGE_SHIFT);
	BLANK();

	COMMENT("Hexagon pt_regs definitions");
	OFFSET(_PT_SYSCALL_NR, pt_regs, syscall_nr);
	OFFSET(_PT_GPUGP, pt_regs, gpugp);
	OFFSET(_PT_CS1CS0, pt_regs, cs1cs0);
	OFFSET(_PT_R3130, pt_regs, r3130);
	OFFSET(_PT_R2928, pt_regs, r2928);
	OFFSET(_PT_R2726, pt_regs, r2726);
	OFFSET(_PT_R2524, pt_regs, r2524);
	OFFSET(_PT_R2322, pt_regs, r2322);
	OFFSET(_PT_R2120, pt_regs, r2120);
	OFFSET(_PT_R1918, pt_regs, r1918);
	OFFSET(_PT_R1716, pt_regs, r1716);
	OFFSET(_PT_R1514, pt_regs, r1514);
	OFFSET(_PT_R1312, pt_regs, r1312);
	OFFSET(_PT_R1110, pt_regs, r1110);
	OFFSET(_PT_R0908, pt_regs, r0908);
	OFFSET(_PT_R0706, pt_regs, r0706);
	OFFSET(_PT_R0504, pt_regs, r0504);
	OFFSET(_PT_R0302, pt_regs, r0302);
	OFFSET(_PT_R0100, pt_regs, r0100);
	OFFSET(_PT_LC0SA0, pt_regs, lc0sa0);
	OFFSET(_PT_LC1SA1, pt_regs, lc1sa1);
	OFFSET(_PT_M1M0, pt_regs, m1m0);
	OFFSET(_PT_PREDSUSR, pt_regs, predsusr);
	OFFSET(_PT_EVREC, pt_regs, hvmer);
	OFFSET(_PT_ER_VMEL, pt_regs, hvmer.vmel);
	OFFSET(_PT_ER_VMEST, pt_regs, hvmer.vmest);
	OFFSET(_PT_ER_VMPSP, pt_regs, hvmer.vmpsp);
	OFFSET(_PT_ER_VMBADVA, pt_regs, hvmer.vmbadva);
	DEFINE(_PT_REGS_SIZE, माप(काष्ठा pt_regs));
	BLANK();

	COMMENT("Hexagon thread_info definitions");
	OFFSET(_THREAD_INFO_FLAGS, thपढ़ो_info, flags);
	OFFSET(_THREAD_INFO_PT_REGS, thपढ़ो_info, regs);
	OFFSET(_THREAD_INFO_SP, thपढ़ो_info, sp);
	DEFINE(_THREAD_SIZE, THREAD_SIZE);
	BLANK();

	COMMENT("Hexagon hexagon_switch_stack definitions");
	OFFSET(_SWITCH_R1716, hexagon_चयन_stack, r1716);
	OFFSET(_SWITCH_R1918, hexagon_चयन_stack, r1918);
	OFFSET(_SWITCH_R2120, hexagon_चयन_stack, r2120);
	OFFSET(_SWITCH_R2322, hexagon_चयन_stack, r2322);

	OFFSET(_SWITCH_R2524, hexagon_चयन_stack, r2524);
	OFFSET(_SWITCH_R2726, hexagon_चयन_stack, r2726);
	OFFSET(_SWITCH_FP, hexagon_चयन_stack, fp);
	OFFSET(_SWITCH_LR, hexagon_चयन_stack, lr);
	DEFINE(_SWITCH_STACK_SIZE, माप(काष्ठा hexagon_चयन_stack));
	BLANK();

	COMMENT("Hexagon task_struct definitions");
	OFFSET(_TASK_THREAD_INFO, task_काष्ठा, stack);
	OFFSET(_TASK_STRUCT_THREAD, task_काष्ठा, thपढ़ो);

	COMMENT("Hexagon thread_struct definitions");
	OFFSET(_THREAD_STRUCT_SWITCH_SP, thपढ़ो_काष्ठा, चयन_sp);

	वापस 0;
पूर्ण
