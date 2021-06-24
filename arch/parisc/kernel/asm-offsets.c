<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* 
 * Generate definitions needed by assembly language modules.
 * This code generates raw यंत्र output which is post-processed to extract
 * and क्रमmat the required data.
 *
 *    Copyright (C) 2000-2001 John Marvin <jsm at parisc-linux.org>
 *    Copyright (C) 2000 David Huggins-Daines <dhd with pobox.org>
 *    Copyright (C) 2000 Sam Creasey <sammy@sammy.net>
 *    Copyright (C) 2000 Grant Grundler <grundler with parisc-linux.org>
 *    Copyright (C) 2001 Paul Bame <bame at parisc-linux.org>
 *    Copyright (C) 2001 Riअक्षरd Hirst <rhirst at parisc-linux.org>
 *    Copyright (C) 2002 Ranकरोlph Chung <tausq with parisc-linux.org>
 *    Copyright (C) 2003 James Bottomley <jejb at parisc-linux.org>
 */

#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/kbuild.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/pdc.h>
#समावेश <linux/uaccess.h>

#अगर_घोषित CONFIG_64BIT
#घोषणा FRAME_SIZE	128
#अन्यथा
#घोषणा FRAME_SIZE	64
#पूर्ण_अगर
#घोषणा FRAME_ALIGN	64

/* Add FRAME_SIZE to the size x and align it to y. All definitions
 * that use align_frame will include space क्रम a frame.
 */
#घोषणा align_frame(x,y) (((x)+FRAME_SIZE+(y)-1) - (((x)+(y)-1)%(y)))

पूर्णांक मुख्य(व्योम)
अणु
	DEFINE(TASK_THREAD_INFO, दुरत्व(काष्ठा task_काष्ठा, stack));
	DEFINE(TASK_STATE, दुरत्व(काष्ठा task_काष्ठा, state));
	DEFINE(TASK_FLAGS, दुरत्व(काष्ठा task_काष्ठा, flags));
	DEFINE(TASK_SIGPENDING, दुरत्व(काष्ठा task_काष्ठा, pending));
	DEFINE(TASK_PTRACE, दुरत्व(काष्ठा task_काष्ठा, ptrace));
	DEFINE(TASK_MM, दुरत्व(काष्ठा task_काष्ठा, mm));
	DEFINE(TASK_PERSONALITY, दुरत्व(काष्ठा task_काष्ठा, personality));
	DEFINE(TASK_PID, दुरत्व(काष्ठा task_काष्ठा, pid));
	BLANK();
	DEFINE(TASK_REGS, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs));
	DEFINE(TASK_PT_PSW, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[ 0]));
	DEFINE(TASK_PT_GR1, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[ 1]));
	DEFINE(TASK_PT_GR2, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[ 2]));
	DEFINE(TASK_PT_GR3, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[ 3]));
	DEFINE(TASK_PT_GR4, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[ 4]));
	DEFINE(TASK_PT_GR5, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[ 5]));
	DEFINE(TASK_PT_GR6, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[ 6]));
	DEFINE(TASK_PT_GR7, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[ 7]));
	DEFINE(TASK_PT_GR8, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[ 8]));
	DEFINE(TASK_PT_GR9, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[ 9]));
	DEFINE(TASK_PT_GR10, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[10]));
	DEFINE(TASK_PT_GR11, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[11]));
	DEFINE(TASK_PT_GR12, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[12]));
	DEFINE(TASK_PT_GR13, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[13]));
	DEFINE(TASK_PT_GR14, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[14]));
	DEFINE(TASK_PT_GR15, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[15]));
	DEFINE(TASK_PT_GR16, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[16]));
	DEFINE(TASK_PT_GR17, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[17]));
	DEFINE(TASK_PT_GR18, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[18]));
	DEFINE(TASK_PT_GR19, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[19]));
	DEFINE(TASK_PT_GR20, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[20]));
	DEFINE(TASK_PT_GR21, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[21]));
	DEFINE(TASK_PT_GR22, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[22]));
	DEFINE(TASK_PT_GR23, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[23]));
	DEFINE(TASK_PT_GR24, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[24]));
	DEFINE(TASK_PT_GR25, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[25]));
	DEFINE(TASK_PT_GR26, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[26]));
	DEFINE(TASK_PT_GR27, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[27]));
	DEFINE(TASK_PT_GR28, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[28]));
	DEFINE(TASK_PT_GR29, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[29]));
	DEFINE(TASK_PT_GR30, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[30]));
	DEFINE(TASK_PT_GR31, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.gr[31]));
	DEFINE(TASK_PT_FR0, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[ 0]));
	DEFINE(TASK_PT_FR1, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[ 1]));
	DEFINE(TASK_PT_FR2, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[ 2]));
	DEFINE(TASK_PT_FR3, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[ 3]));
	DEFINE(TASK_PT_FR4, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[ 4]));
	DEFINE(TASK_PT_FR5, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[ 5]));
	DEFINE(TASK_PT_FR6, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[ 6]));
	DEFINE(TASK_PT_FR7, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[ 7]));
	DEFINE(TASK_PT_FR8, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[ 8]));
	DEFINE(TASK_PT_FR9, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[ 9]));
	DEFINE(TASK_PT_FR10, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[10]));
	DEFINE(TASK_PT_FR11, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[11]));
	DEFINE(TASK_PT_FR12, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[12]));
	DEFINE(TASK_PT_FR13, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[13]));
	DEFINE(TASK_PT_FR14, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[14]));
	DEFINE(TASK_PT_FR15, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[15]));
	DEFINE(TASK_PT_FR16, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[16]));
	DEFINE(TASK_PT_FR17, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[17]));
	DEFINE(TASK_PT_FR18, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[18]));
	DEFINE(TASK_PT_FR19, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[19]));
	DEFINE(TASK_PT_FR20, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[20]));
	DEFINE(TASK_PT_FR21, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[21]));
	DEFINE(TASK_PT_FR22, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[22]));
	DEFINE(TASK_PT_FR23, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[23]));
	DEFINE(TASK_PT_FR24, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[24]));
	DEFINE(TASK_PT_FR25, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[25]));
	DEFINE(TASK_PT_FR26, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[26]));
	DEFINE(TASK_PT_FR27, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[27]));
	DEFINE(TASK_PT_FR28, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[28]));
	DEFINE(TASK_PT_FR29, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[29]));
	DEFINE(TASK_PT_FR30, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[30]));
	DEFINE(TASK_PT_FR31, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.fr[31]));
	DEFINE(TASK_PT_SR0, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.sr[ 0]));
	DEFINE(TASK_PT_SR1, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.sr[ 1]));
	DEFINE(TASK_PT_SR2, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.sr[ 2]));
	DEFINE(TASK_PT_SR3, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.sr[ 3]));
	DEFINE(TASK_PT_SR4, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.sr[ 4]));
	DEFINE(TASK_PT_SR5, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.sr[ 5]));
	DEFINE(TASK_PT_SR6, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.sr[ 6]));
	DEFINE(TASK_PT_SR7, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.sr[ 7]));
	DEFINE(TASK_PT_IASQ0, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.iasq[0]));
	DEFINE(TASK_PT_IASQ1, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.iasq[1]));
	DEFINE(TASK_PT_IAOQ0, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.iaoq[0]));
	DEFINE(TASK_PT_IAOQ1, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.iaoq[1]));
	DEFINE(TASK_PT_CR27, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.cr27));
	DEFINE(TASK_PT_ORIG_R28, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.orig_r28));
	DEFINE(TASK_PT_KSP, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.ksp));
	DEFINE(TASK_PT_KPC, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.kpc));
	DEFINE(TASK_PT_SAR, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.sar));
	DEFINE(TASK_PT_IIR, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.iir));
	DEFINE(TASK_PT_ISR, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.isr));
	DEFINE(TASK_PT_IOR, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो.regs.ior));
	BLANK();
	DEFINE(TASK_SZ, माप(काष्ठा task_काष्ठा));
	/* TASK_SZ_ALGN includes space क्रम a stack frame. */
	DEFINE(TASK_SZ_ALGN, align_frame(माप(काष्ठा task_काष्ठा), FRAME_ALIGN));
	BLANK();
	DEFINE(PT_PSW, दुरत्व(काष्ठा pt_regs, gr[ 0]));
	DEFINE(PT_GR1, दुरत्व(काष्ठा pt_regs, gr[ 1]));
	DEFINE(PT_GR2, दुरत्व(काष्ठा pt_regs, gr[ 2]));
	DEFINE(PT_GR3, दुरत्व(काष्ठा pt_regs, gr[ 3]));
	DEFINE(PT_GR4, दुरत्व(काष्ठा pt_regs, gr[ 4]));
	DEFINE(PT_GR5, दुरत्व(काष्ठा pt_regs, gr[ 5]));
	DEFINE(PT_GR6, दुरत्व(काष्ठा pt_regs, gr[ 6]));
	DEFINE(PT_GR7, दुरत्व(काष्ठा pt_regs, gr[ 7]));
	DEFINE(PT_GR8, दुरत्व(काष्ठा pt_regs, gr[ 8]));
	DEFINE(PT_GR9, दुरत्व(काष्ठा pt_regs, gr[ 9]));
	DEFINE(PT_GR10, दुरत्व(काष्ठा pt_regs, gr[10]));
	DEFINE(PT_GR11, दुरत्व(काष्ठा pt_regs, gr[11]));
	DEFINE(PT_GR12, दुरत्व(काष्ठा pt_regs, gr[12]));
	DEFINE(PT_GR13, दुरत्व(काष्ठा pt_regs, gr[13]));
	DEFINE(PT_GR14, दुरत्व(काष्ठा pt_regs, gr[14]));
	DEFINE(PT_GR15, दुरत्व(काष्ठा pt_regs, gr[15]));
	DEFINE(PT_GR16, दुरत्व(काष्ठा pt_regs, gr[16]));
	DEFINE(PT_GR17, दुरत्व(काष्ठा pt_regs, gr[17]));
	DEFINE(PT_GR18, दुरत्व(काष्ठा pt_regs, gr[18]));
	DEFINE(PT_GR19, दुरत्व(काष्ठा pt_regs, gr[19]));
	DEFINE(PT_GR20, दुरत्व(काष्ठा pt_regs, gr[20]));
	DEFINE(PT_GR21, दुरत्व(काष्ठा pt_regs, gr[21]));
	DEFINE(PT_GR22, दुरत्व(काष्ठा pt_regs, gr[22]));
	DEFINE(PT_GR23, दुरत्व(काष्ठा pt_regs, gr[23]));
	DEFINE(PT_GR24, दुरत्व(काष्ठा pt_regs, gr[24]));
	DEFINE(PT_GR25, दुरत्व(काष्ठा pt_regs, gr[25]));
	DEFINE(PT_GR26, दुरत्व(काष्ठा pt_regs, gr[26]));
	DEFINE(PT_GR27, दुरत्व(काष्ठा pt_regs, gr[27]));
	DEFINE(PT_GR28, दुरत्व(काष्ठा pt_regs, gr[28]));
	DEFINE(PT_GR29, दुरत्व(काष्ठा pt_regs, gr[29]));
	DEFINE(PT_GR30, दुरत्व(काष्ठा pt_regs, gr[30]));
	DEFINE(PT_GR31, दुरत्व(काष्ठा pt_regs, gr[31]));
	DEFINE(PT_FR0, दुरत्व(काष्ठा pt_regs, fr[ 0]));
	DEFINE(PT_FR1, दुरत्व(काष्ठा pt_regs, fr[ 1]));
	DEFINE(PT_FR2, दुरत्व(काष्ठा pt_regs, fr[ 2]));
	DEFINE(PT_FR3, दुरत्व(काष्ठा pt_regs, fr[ 3]));
	DEFINE(PT_FR4, दुरत्व(काष्ठा pt_regs, fr[ 4]));
	DEFINE(PT_FR5, दुरत्व(काष्ठा pt_regs, fr[ 5]));
	DEFINE(PT_FR6, दुरत्व(काष्ठा pt_regs, fr[ 6]));
	DEFINE(PT_FR7, दुरत्व(काष्ठा pt_regs, fr[ 7]));
	DEFINE(PT_FR8, दुरत्व(काष्ठा pt_regs, fr[ 8]));
	DEFINE(PT_FR9, दुरत्व(काष्ठा pt_regs, fr[ 9]));
	DEFINE(PT_FR10, दुरत्व(काष्ठा pt_regs, fr[10]));
	DEFINE(PT_FR11, दुरत्व(काष्ठा pt_regs, fr[11]));
	DEFINE(PT_FR12, दुरत्व(काष्ठा pt_regs, fr[12]));
	DEFINE(PT_FR13, दुरत्व(काष्ठा pt_regs, fr[13]));
	DEFINE(PT_FR14, दुरत्व(काष्ठा pt_regs, fr[14]));
	DEFINE(PT_FR15, दुरत्व(काष्ठा pt_regs, fr[15]));
	DEFINE(PT_FR16, दुरत्व(काष्ठा pt_regs, fr[16]));
	DEFINE(PT_FR17, दुरत्व(काष्ठा pt_regs, fr[17]));
	DEFINE(PT_FR18, दुरत्व(काष्ठा pt_regs, fr[18]));
	DEFINE(PT_FR19, दुरत्व(काष्ठा pt_regs, fr[19]));
	DEFINE(PT_FR20, दुरत्व(काष्ठा pt_regs, fr[20]));
	DEFINE(PT_FR21, दुरत्व(काष्ठा pt_regs, fr[21]));
	DEFINE(PT_FR22, दुरत्व(काष्ठा pt_regs, fr[22]));
	DEFINE(PT_FR23, दुरत्व(काष्ठा pt_regs, fr[23]));
	DEFINE(PT_FR24, दुरत्व(काष्ठा pt_regs, fr[24]));
	DEFINE(PT_FR25, दुरत्व(काष्ठा pt_regs, fr[25]));
	DEFINE(PT_FR26, दुरत्व(काष्ठा pt_regs, fr[26]));
	DEFINE(PT_FR27, दुरत्व(काष्ठा pt_regs, fr[27]));
	DEFINE(PT_FR28, दुरत्व(काष्ठा pt_regs, fr[28]));
	DEFINE(PT_FR29, दुरत्व(काष्ठा pt_regs, fr[29]));
	DEFINE(PT_FR30, दुरत्व(काष्ठा pt_regs, fr[30]));
	DEFINE(PT_FR31, दुरत्व(काष्ठा pt_regs, fr[31]));
	DEFINE(PT_SR0, दुरत्व(काष्ठा pt_regs, sr[ 0]));
	DEFINE(PT_SR1, दुरत्व(काष्ठा pt_regs, sr[ 1]));
	DEFINE(PT_SR2, दुरत्व(काष्ठा pt_regs, sr[ 2]));
	DEFINE(PT_SR3, दुरत्व(काष्ठा pt_regs, sr[ 3]));
	DEFINE(PT_SR4, दुरत्व(काष्ठा pt_regs, sr[ 4]));
	DEFINE(PT_SR5, दुरत्व(काष्ठा pt_regs, sr[ 5]));
	DEFINE(PT_SR6, दुरत्व(काष्ठा pt_regs, sr[ 6]));
	DEFINE(PT_SR7, दुरत्व(काष्ठा pt_regs, sr[ 7]));
	DEFINE(PT_IASQ0, दुरत्व(काष्ठा pt_regs, iasq[0]));
	DEFINE(PT_IASQ1, दुरत्व(काष्ठा pt_regs, iasq[1]));
	DEFINE(PT_IAOQ0, दुरत्व(काष्ठा pt_regs, iaoq[0]));
	DEFINE(PT_IAOQ1, दुरत्व(काष्ठा pt_regs, iaoq[1]));
	DEFINE(PT_CR27, दुरत्व(काष्ठा pt_regs, cr27));
	DEFINE(PT_ORIG_R28, दुरत्व(काष्ठा pt_regs, orig_r28));
	DEFINE(PT_KSP, दुरत्व(काष्ठा pt_regs, ksp));
	DEFINE(PT_KPC, दुरत्व(काष्ठा pt_regs, kpc));
	DEFINE(PT_SAR, दुरत्व(काष्ठा pt_regs, sar));
	DEFINE(PT_IIR, दुरत्व(काष्ठा pt_regs, iir));
	DEFINE(PT_ISR, दुरत्व(काष्ठा pt_regs, isr));
	DEFINE(PT_IOR, दुरत्व(काष्ठा pt_regs, ior));
	DEFINE(PT_SIZE, माप(काष्ठा pt_regs));
	/* PT_SZ_ALGN includes space क्रम a stack frame. */
	DEFINE(PT_SZ_ALGN, align_frame(माप(काष्ठा pt_regs), FRAME_ALIGN));
	BLANK();
	DEFINE(TI_TASK, दुरत्व(काष्ठा thपढ़ो_info, task));
	DEFINE(TI_FLAGS, दुरत्व(काष्ठा thपढ़ो_info, flags));
	DEFINE(TI_CPU, दुरत्व(काष्ठा thपढ़ो_info, cpu));
	DEFINE(TI_SEGMENT, दुरत्व(काष्ठा thपढ़ो_info, addr_limit));
	DEFINE(TI_PRE_COUNT, दुरत्व(काष्ठा thपढ़ो_info, preempt_count));
	DEFINE(THREAD_SZ, माप(काष्ठा thपढ़ो_info));
	/* THREAD_SZ_ALGN includes space क्रम a stack frame. */
	DEFINE(THREAD_SZ_ALGN, align_frame(माप(काष्ठा thपढ़ो_info), FRAME_ALIGN));
	BLANK();
	DEFINE(ICACHE_BASE, दुरत्व(काष्ठा pdc_cache_info, ic_base));
	DEFINE(ICACHE_STRIDE, दुरत्व(काष्ठा pdc_cache_info, ic_stride));
	DEFINE(ICACHE_COUNT, दुरत्व(काष्ठा pdc_cache_info, ic_count));
	DEFINE(ICACHE_LOOP, दुरत्व(काष्ठा pdc_cache_info, ic_loop));
	DEFINE(DCACHE_BASE, दुरत्व(काष्ठा pdc_cache_info, dc_base));
	DEFINE(DCACHE_STRIDE, दुरत्व(काष्ठा pdc_cache_info, dc_stride));
	DEFINE(DCACHE_COUNT, दुरत्व(काष्ठा pdc_cache_info, dc_count));
	DEFINE(DCACHE_LOOP, दुरत्व(काष्ठा pdc_cache_info, dc_loop));
	DEFINE(ITLB_SID_BASE, दुरत्व(काष्ठा pdc_cache_info, it_sp_base));
	DEFINE(ITLB_SID_STRIDE, दुरत्व(काष्ठा pdc_cache_info, it_sp_stride));
	DEFINE(ITLB_SID_COUNT, दुरत्व(काष्ठा pdc_cache_info, it_sp_count));
	DEFINE(ITLB_OFF_BASE, दुरत्व(काष्ठा pdc_cache_info, it_off_base));
	DEFINE(ITLB_OFF_STRIDE, दुरत्व(काष्ठा pdc_cache_info, it_off_stride));
	DEFINE(ITLB_OFF_COUNT, दुरत्व(काष्ठा pdc_cache_info, it_off_count));
	DEFINE(ITLB_LOOP, दुरत्व(काष्ठा pdc_cache_info, it_loop));
	DEFINE(DTLB_SID_BASE, दुरत्व(काष्ठा pdc_cache_info, dt_sp_base));
	DEFINE(DTLB_SID_STRIDE, दुरत्व(काष्ठा pdc_cache_info, dt_sp_stride));
	DEFINE(DTLB_SID_COUNT, दुरत्व(काष्ठा pdc_cache_info, dt_sp_count));
	DEFINE(DTLB_OFF_BASE, दुरत्व(काष्ठा pdc_cache_info, dt_off_base));
	DEFINE(DTLB_OFF_STRIDE, दुरत्व(काष्ठा pdc_cache_info, dt_off_stride));
	DEFINE(DTLB_OFF_COUNT, दुरत्व(काष्ठा pdc_cache_info, dt_off_count));
	DEFINE(DTLB_LOOP, दुरत्व(काष्ठा pdc_cache_info, dt_loop));
	BLANK();
	DEFINE(TIF_BLOCKSTEP_PA_BIT, 31-TIF_BLOCKSTEP);
	DEFINE(TIF_SINGLESTEP_PA_BIT, 31-TIF_SINGLESTEP);
	BLANK();
	DEFINE(ASM_PMD_SHIFT, PMD_SHIFT);
	DEFINE(ASM_PGसूची_SHIFT, PGसूची_SHIFT);
	DEFINE(ASM_BITS_PER_PGD, BITS_PER_PGD);
	DEFINE(ASM_BITS_PER_PMD, BITS_PER_PMD);
	DEFINE(ASM_BITS_PER_PTE, BITS_PER_PTE);
	DEFINE(ASM_PMD_ENTRY, ((PAGE_OFFSET & PMD_MASK) >> PMD_SHIFT));
	DEFINE(ASM_PGD_ENTRY, PAGE_OFFSET >> PGसूची_SHIFT);
	DEFINE(ASM_PGD_ENTRY_SIZE, PGD_ENTRY_SIZE);
	DEFINE(ASM_PMD_ENTRY_SIZE, PMD_ENTRY_SIZE);
	DEFINE(ASM_PTE_ENTRY_SIZE, PTE_ENTRY_SIZE);
	DEFINE(ASM_PFN_PTE_SHIFT, PFN_PTE_SHIFT);
	DEFINE(ASM_PT_INITIAL, PT_INITIAL);
	BLANK();
	/* HUGEPAGE_SIZE is only used in vmlinux.lds.S to align kernel text
	 * and kernel data on physical huge pages */
#अगर_घोषित CONFIG_HUGETLB_PAGE
	DEFINE(HUGEPAGE_SIZE, 1UL << REAL_HPAGE_SHIFT);
#अन्यथा
	DEFINE(HUGEPAGE_SIZE, PAGE_SIZE);
#पूर्ण_अगर
	BLANK();
	DEFINE(ASM_PDC_RESULT_SIZE, NUM_PDC_RESULT * माप(अचिन्हित दीर्घ));
	BLANK();
	वापस 0;
पूर्ण
