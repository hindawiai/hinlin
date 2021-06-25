<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/******************************************************************************
 * arch/ia64/include/यंत्र/native/inst.h
 *
 * Copyright (c) 2008 Isaku Yamahata <yamahata at valinux co jp>
 *                    VA Linux Systems Japan K.K.
 */

#घोषणा DO_SAVE_MIN		IA64_NATIVE_DO_SAVE_MIN

#घोषणा MOV_FROM_IFA(reg)	\
	mov reg = cr.अगरa

#घोषणा MOV_FROM_ITIR(reg)	\
	mov reg = cr.itir

#घोषणा MOV_FROM_ISR(reg)	\
	mov reg = cr.isr

#घोषणा MOV_FROM_IHA(reg)	\
	mov reg = cr.iha

#घोषणा MOV_FROM_IPSR(pred, reg)	\
(pred)	mov reg = cr.ipsr

#घोषणा MOV_FROM_IIM(reg)	\
	mov reg = cr.iim

#घोषणा MOV_FROM_IIP(reg)	\
	mov reg = cr.iip

#घोषणा MOV_FROM_IVR(reg, clob)	\
	mov reg = cr.ivr

#घोषणा MOV_FROM_PSR(pred, reg, clob)	\
(pred)	mov reg = psr

#घोषणा MOV_FROM_ITC(pred, pred_clob, reg, clob)	\
(pred)	mov reg = ar.itc

#घोषणा MOV_TO_IFA(reg, clob)	\
	mov cr.अगरa = reg

#घोषणा MOV_TO_ITIR(pred, reg, clob)	\
(pred)	mov cr.itir = reg

#घोषणा MOV_TO_IHA(pred, reg, clob)	\
(pred)	mov cr.iha = reg

#घोषणा MOV_TO_IPSR(pred, reg, clob)		\
(pred)	mov cr.ipsr = reg

#घोषणा MOV_TO_IFS(pred, reg, clob)	\
(pred)	mov cr.अगरs = reg

#घोषणा MOV_TO_IIP(reg, clob)	\
	mov cr.iip = reg

#घोषणा MOV_TO_KR(kr, reg, clob0, clob1)	\
	mov IA64_KR(kr) = reg

#घोषणा ITC_I(pred, reg, clob)	\
(pred)	itc.i reg

#घोषणा ITC_D(pred, reg, clob)	\
(pred)	itc.d reg

#घोषणा ITC_I_AND_D(pred_i, pred_d, reg, clob)	\
(pred_i) itc.i reg;				\
(pred_d) itc.d reg

#घोषणा THASH(pred, reg0, reg1, clob)		\
(pred)	thash reg0 = reg1

#घोषणा SSM_PSR_IC_AND_DEFAULT_BITS_AND_SRLZ_I(clob0, clob1)		\
	ssm psr.ic | PSR_DEFAULT_BITS					\
	;;								\
	srlz.i /* guarantee that पूर्णांकerruption collectin is on */	\
	;;

#घोषणा SSM_PSR_IC_AND_SRLZ_D(clob0, clob1)	\
	ssm psr.ic				\
	;;					\
	srlz.d

#घोषणा RSM_PSR_IC(clob)	\
	rsm psr.ic

#घोषणा SSM_PSR_I(pred, pred_clob, clob)	\
(pred)	ssm psr.i

#घोषणा RSM_PSR_I(pred, clob0, clob1)	\
(pred)	rsm psr.i

#घोषणा RSM_PSR_I_IC(clob0, clob1, clob2)	\
	rsm psr.i | psr.ic

#घोषणा RSM_PSR_DT		\
	rsm psr.dt

#घोषणा RSM_PSR_BE_I(clob0, clob1)	\
	rsm psr.be | psr.i

#घोषणा SSM_PSR_DT_AND_SRLZ_I	\
	ssm psr.dt		\
	;;			\
	srlz.i

#घोषणा BSW_0(clob0, clob1, clob2)	\
	bsw.0

#घोषणा BSW_1(clob0, clob1)	\
	bsw.1

#घोषणा COVER	\
	cover

#घोषणा RFI	\
	rfi
