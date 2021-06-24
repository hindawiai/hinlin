<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * File:	mca_यंत्र.h
 * Purpose:	Machine check handling specअगरic defines
 *
 * Copyright (C) 1999 Silicon Graphics, Inc.
 * Copyright (C) Vijay Chander <vijay@engr.sgi.com>
 * Copyright (C) Srinivasa Thirumalaअक्षर <sprasad@engr.sgi.com>
 * Copyright (C) 2000 Hewlett-Packard Co.
 * Copyright (C) 2000 David Mosberger-Tang <davidm@hpl.hp.com>
 * Copyright (C) 2002 Intel Corp.
 * Copyright (C) 2002 Jenna Hall <jenna.s.hall@पूर्णांकel.com>
 * Copyright (C) 2005 Silicon Graphics, Inc
 * Copyright (C) 2005 Keith Owens <kaos@sgi.com>
 */
#अगर_अघोषित _ASM_IA64_MCA_ASM_H
#घोषणा _ASM_IA64_MCA_ASM_H

#समावेश <यंत्र/percpu.h>

#घोषणा PSR_IC		13
#घोषणा PSR_I		14
#घोषणा	PSR_DT		17
#घोषणा PSR_RT		27
#घोषणा PSR_MC		35
#घोषणा PSR_IT		36
#घोषणा PSR_BN		44

/*
 * This macro converts a inकाष्ठाion भव address to a physical address
 * Right now क्रम simulation purposes the भव addresses are
 * direct mapped to physical addresses.
 *	1. Lop off bits 61 thru 63 in the भव address
 */
#घोषणा INST_VA_TO_PA(addr)							\
	dep	addr	= 0, addr, 61, 3
/*
 * This macro converts a data भव address to a physical address
 * Right now क्रम simulation purposes the भव addresses are
 * direct mapped to physical addresses.
 *	1. Lop off bits 61 thru 63 in the भव address
 */
#घोषणा DATA_VA_TO_PA(addr)							\
	tpa	addr	= addr
/*
 * This macro converts a data physical address to a भव address
 * Right now क्रम simulation purposes the भव addresses are
 * direct mapped to physical addresses.
 *	1. Put 0x7 in bits 61 thru 63.
 */
#घोषणा DATA_PA_TO_VA(addr,temp)							\
	mov	temp	= 0x7	;;							\
	dep	addr	= temp, addr, 61, 3

#घोषणा GET_THIS_PADDR(reg, var)		\
	mov	reg = IA64_KR(PER_CPU_DATA);;	\
        addl	reg = THIS_CPU(var), reg

/*
 * This macro jumps to the inकाष्ठाion at the given भव address
 * and starts execution in physical mode with all the address
 * translations turned off.
 *	1.	Save the current psr
 *	2.	Make sure that all the upper 32 bits are off
 *
 *	3.	Clear the पूर्णांकerrupt enable and पूर्णांकerrupt state collection bits
 *		in the psr beक्रमe updating the ipsr and iip.
 *
 *	4.	Turn off the inकाष्ठाion, data and rse translation bits of the psr
 *		and store the new value पूर्णांकo ipsr
 *		Also make sure that the पूर्णांकerrupts are disabled.
 *		Ensure that we are in little endian mode.
 *		[psr.अणुrt, it, dt, i, beपूर्ण = 0]
 *
 *	5.	Get the physical address corresponding to the भव address
 *		of the next inकाष्ठाion bundle and put it in iip.
 *		(Using magic numbers 24 and 40 in the deposपूर्णांक inकाष्ठाion since
 *		 the IA64_SDK code directly maps to lower 24bits as physical address
 *		 from a भव address).
 *
 *	6.	Do an rfi to move the values from ipsr to psr and iip to ip.
 */
#घोषणा  PHYSICAL_MODE_ENTER(temp1, temp2, start_addr, old_psr)				\
	mov	old_psr = psr;								\
	;;										\
	dep	old_psr = 0, old_psr, 32, 32;						\
											\
	mov	ar.rsc = 0 ;								\
	;;										\
	srlz.d;										\
	mov	temp2 = ar.bspstore;							\
	;;										\
	DATA_VA_TO_PA(temp2);								\
	;;										\
	mov	temp1 = ar.rnat;							\
	;;										\
	mov	ar.bspstore = temp2;							\
	;;										\
	mov	ar.rnat = temp1;							\
	mov	temp1 = psr;								\
	mov	temp2 = psr;								\
	;;										\
											\
	dep	temp2 = 0, temp2, PSR_IC, 2;						\
	;;										\
	mov	psr.l = temp2;								\
	;;										\
	srlz.d;										\
	dep	temp1 = 0, temp1, 32, 32;						\
	;;										\
	dep	temp1 = 0, temp1, PSR_IT, 1;						\
	;;										\
	dep	temp1 = 0, temp1, PSR_DT, 1;						\
	;;										\
	dep	temp1 = 0, temp1, PSR_RT, 1;						\
	;;										\
	dep	temp1 = 0, temp1, PSR_I, 1;						\
	;;										\
	dep	temp1 = 0, temp1, PSR_IC, 1;						\
	;;										\
	dep	temp1 = -1, temp1, PSR_MC, 1;						\
	;;										\
	mov	cr.ipsr = temp1;							\
	;;										\
	LOAD_PHYSICAL(p0, temp2, start_addr);						\
	;;										\
	mov	cr.iip = temp2;								\
	mov	cr.अगरs = r0;								\
	DATA_VA_TO_PA(sp);								\
	DATA_VA_TO_PA(gp);								\
	;;										\
	srlz.i;										\
	;;										\
	nop	1;									\
	nop	2;									\
	nop	1;									\
	nop	2;									\
	rfi;										\
	;;

/*
 * This macro jumps to the inकाष्ठाion at the given भव address
 * and starts execution in भव mode with all the address
 * translations turned on.
 *	1.	Get the old saved psr
 *
 *	2.	Clear the पूर्णांकerrupt state collection bit in the current psr.
 *
 *	3.	Set the inकाष्ठाion translation bit back in the old psr
 *		Note we have to करो this since we are right now saving only the
 *		lower 32-bits of old psr.(Also the old psr has the data and
 *		rse translation bits on)
 *
 *	4.	Set ipsr to this old_psr with "it" bit set and "bn" = 1.
 *
 *	5.	Reset the current thपढ़ो poपूर्णांकer (r13).
 *
 *	6.	Set iip to the भव address of the next inकाष्ठाion bundle.
 *
 *	7.	Do an rfi to move ipsr to psr and iip to ip.
 */

#घोषणा VIRTUAL_MODE_ENTER(temp1, temp2, start_addr, old_psr)	\
	mov	temp2 = psr;					\
	;;							\
	mov	old_psr = temp2;				\
	;;							\
	dep	temp2 = 0, temp2, PSR_IC, 2;			\
	;;							\
	mov	psr.l = temp2;					\
	mov	ar.rsc = 0;					\
	;;							\
	srlz.d;							\
	mov	r13 = ar.k6;					\
	mov	temp2 = ar.bspstore;				\
	;;							\
	DATA_PA_TO_VA(temp2,temp1);				\
	;;							\
	mov	temp1 = ar.rnat;				\
	;;							\
	mov	ar.bspstore = temp2;				\
	;;							\
	mov	ar.rnat = temp1;				\
	;;							\
	mov	temp1 = old_psr;				\
	;;							\
	mov	temp2 = 1;					\
	;;							\
	dep	temp1 = temp2, temp1, PSR_IC, 1;		\
	;;							\
	dep	temp1 = temp2, temp1, PSR_IT, 1;		\
	;;							\
	dep	temp1 = temp2, temp1, PSR_DT, 1;		\
	;;							\
	dep	temp1 = temp2, temp1, PSR_RT, 1;		\
	;;							\
	dep	temp1 = temp2, temp1, PSR_BN, 1;		\
	;;							\
								\
	mov     cr.ipsr = temp1;				\
	movl	temp2 = start_addr;				\
	;;							\
	mov	cr.iip = temp2;					\
	movl	gp = __gp					\
	;;							\
	DATA_PA_TO_VA(sp, temp1);				\
	srlz.i;							\
	;;							\
	nop	1;						\
	nop	2;						\
	nop	1;						\
	rfi							\
	;;

/*
 * The MCA and INIT stacks in काष्ठा ia64_mca_cpu look like normal kernel
 * stacks, except that the SAL/OS state and a चयन_stack are stored near the
 * top of the MCA/INIT stack.  To support concurrent entry to MCA or INIT, as
 * well as MCA over INIT, each event needs its own SAL/OS state.  All entries
 * are 16 byte aligned.
 *
 *      +---------------------------+
 *      |          pt_regs          |
 *      +---------------------------+
 *      |        चयन_stack       |
 *      +---------------------------+
 *      |        SAL/OS state       |
 *      +---------------------------+
 *      |    16 byte scratch area   |
 *      +---------------------------+ <-------- SP at start of C MCA handler
 *      |           .....           |
 *      +---------------------------+
 *      | RBS क्रम MCA/INIT handler  |
 *      +---------------------------+
 *      | काष्ठा task क्रम MCA/INIT  |
 *      +---------------------------+ <-------- Bottom of MCA/INIT stack
 */

#घोषणा ALIGN16(x)			((x)&~15)
#घोषणा MCA_PT_REGS_OFFSET		ALIGN16(KERNEL_STACK_SIZE-IA64_PT_REGS_SIZE)
#घोषणा MCA_SWITCH_STACK_OFFSET		ALIGN16(MCA_PT_REGS_OFFSET-IA64_SWITCH_STACK_SIZE)
#घोषणा MCA_SOS_OFFSET			ALIGN16(MCA_SWITCH_STACK_OFFSET-IA64_SAL_OS_STATE_SIZE)
#घोषणा MCA_SP_OFFSET			ALIGN16(MCA_SOS_OFFSET-16)

#पूर्ण_अगर /* _ASM_IA64_MCA_ASM_H */
