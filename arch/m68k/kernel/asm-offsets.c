<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This program is used to generate definitions needed by
 * assembly language modules.
 *
 * We use the technique used in the OSF Mach kernel code:
 * generate यंत्र statements containing #घोषणाs,
 * compile this file to assembler, and then extract the
 * #घोषणाs from the assembly-language output.
 */

#घोषणा ASM_OFFSETS_C

#समावेश <linux/मानकघोष.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/kbuild.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/amigahw.h>
#समावेश <linux/font.h>

पूर्णांक मुख्य(व्योम)
अणु
	/* offsets पूर्णांकo the task काष्ठा */
	DEFINE(TASK_THREAD, दुरत्व(काष्ठा task_काष्ठा, thपढ़ो));
	DEFINE(TASK_MM, दुरत्व(काष्ठा task_काष्ठा, mm));
	DEFINE(TASK_STACK, दुरत्व(काष्ठा task_काष्ठा, stack));

	/* offsets पूर्णांकo the thपढ़ो काष्ठा */
	DEFINE(THREAD_KSP, दुरत्व(काष्ठा thपढ़ो_काष्ठा, ksp));
	DEFINE(THREAD_USP, दुरत्व(काष्ठा thपढ़ो_काष्ठा, usp));
	DEFINE(THREAD_SR, दुरत्व(काष्ठा thपढ़ो_काष्ठा, sr));
	DEFINE(THREAD_FS, दुरत्व(काष्ठा thपढ़ो_काष्ठा, fs));
	DEFINE(THREAD_CRP, दुरत्व(काष्ठा thपढ़ो_काष्ठा, crp));
	DEFINE(THREAD_ESP0, दुरत्व(काष्ठा thपढ़ो_काष्ठा, esp0));
	DEFINE(THREAD_FPREG, दुरत्व(काष्ठा thपढ़ो_काष्ठा, fp));
	DEFINE(THREAD_FPCNTL, दुरत्व(काष्ठा thपढ़ो_काष्ठा, fpcntl));
	DEFINE(THREAD_FPSTATE, दुरत्व(काष्ठा thपढ़ो_काष्ठा, fpstate));

	/* offsets पूर्णांकo the thपढ़ो_info काष्ठा */
	DEFINE(TINFO_PREEMPT, दुरत्व(काष्ठा thपढ़ो_info, preempt_count));
	DEFINE(TINFO_FLAGS, दुरत्व(काष्ठा thपढ़ो_info, flags));

	/* offsets पूर्णांकo the pt_regs */
	DEFINE(PT_OFF_D0, दुरत्व(काष्ठा pt_regs, d0));
	DEFINE(PT_OFF_ORIG_D0, दुरत्व(काष्ठा pt_regs, orig_d0));
	DEFINE(PT_OFF_D1, दुरत्व(काष्ठा pt_regs, d1));
	DEFINE(PT_OFF_D2, दुरत्व(काष्ठा pt_regs, d2));
	DEFINE(PT_OFF_D3, दुरत्व(काष्ठा pt_regs, d3));
	DEFINE(PT_OFF_D4, दुरत्व(काष्ठा pt_regs, d4));
	DEFINE(PT_OFF_D5, दुरत्व(काष्ठा pt_regs, d5));
	DEFINE(PT_OFF_A0, दुरत्व(काष्ठा pt_regs, a0));
	DEFINE(PT_OFF_A1, दुरत्व(काष्ठा pt_regs, a1));
	DEFINE(PT_OFF_A2, दुरत्व(काष्ठा pt_regs, a2));
	DEFINE(PT_OFF_PC, दुरत्व(काष्ठा pt_regs, pc));
	DEFINE(PT_OFF_SR, दुरत्व(काष्ठा pt_regs, sr));

	/* bitfields are a bit dअगरficult */
#अगर_घोषित CONFIG_COLDFIRE
	DEFINE(PT_OFF_FORMATVEC, दुरत्व(काष्ठा pt_regs, sr) - 2);
#अन्यथा
	DEFINE(PT_OFF_FORMATVEC, दुरत्व(काष्ठा pt_regs, pc) + 4);
#पूर्ण_अगर

	/* offsets पूर्णांकo the irq_cpustat_t काष्ठा */
	DEFINE(CPUSTAT_SOFTIRQ_PENDING, दुरत्व(irq_cpustat_t, __softirq_pending));

	/* संकेत defines */
	DEFINE(Lसंक_अंश, संक_अंश);
	DEFINE(LSEGV_MAPERR, SEGV_MAPERR);
	DEFINE(LSIGTRAP, SIGTRAP);
	DEFINE(LTRAP_TRACE, TRAP_TRACE);

#अगर_घोषित CONFIG_MMU
	/* offsets पूर्णांकo the bi_record काष्ठा */
	DEFINE(BIR_TAG, दुरत्व(काष्ठा bi_record, tag));
	DEFINE(BIR_SIZE, दुरत्व(काष्ठा bi_record, size));
	DEFINE(BIR_DATA, दुरत्व(काष्ठा bi_record, data));

	/* offsets पूर्णांकo the font_desc काष्ठा */
	DEFINE(FONT_DESC_IDX, दुरत्व(काष्ठा font_desc, idx));
	DEFINE(FONT_DESC_NAME, दुरत्व(काष्ठा font_desc, name));
	DEFINE(FONT_DESC_WIDTH, दुरत्व(काष्ठा font_desc, width));
	DEFINE(FONT_DESC_HEIGHT, दुरत्व(काष्ठा font_desc, height));
	DEFINE(FONT_DESC_DATA, दुरत्व(काष्ठा font_desc, data));
	DEFINE(FONT_DESC_PREF, दुरत्व(काष्ठा font_desc, pref));

	/* offsets पूर्णांकo the custom काष्ठा */
	DEFINE(CUSTOMBASE, &amiga_custom);
	DEFINE(C_INTENAR, दुरत्व(काष्ठा CUSTOM, पूर्णांकenar));
	DEFINE(C_INTREQR, दुरत्व(काष्ठा CUSTOM, पूर्णांकreqr));
	DEFINE(C_INTENA, दुरत्व(काष्ठा CUSTOM, पूर्णांकena));
	DEFINE(C_INTREQ, दुरत्व(काष्ठा CUSTOM, पूर्णांकreq));
	DEFINE(C_SERDATR, दुरत्व(काष्ठा CUSTOM, serdatr));
	DEFINE(C_SERDAT, दुरत्व(काष्ठा CUSTOM, serdat));
	DEFINE(C_SERPER, दुरत्व(काष्ठा CUSTOM, serper));
	DEFINE(CIAABASE, &ciaa);
	DEFINE(CIABBASE, &ciab);
	DEFINE(C_PRA, दुरत्व(काष्ठा CIA, pra));
	DEFINE(ZTWOBASE, zTwoBase);

	/* क्रमागत m68k_fixup_type */
	DEFINE(M68K_FIXUP_MEMOFFSET, m68k_fixup_memoffset);
#पूर्ण_अगर

	वापस 0;
पूर्ण
