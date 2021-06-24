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

#समावेश <linux/मानकघोष.स>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/kbuild.h>
#समावेश <linux/suspend.h>

#समावेश <यंत्र/thपढ़ो_info.h>
#समावेश <यंत्र/suspend.h>

पूर्णांक मुख्य(व्योम)
अणु
	/* offsets पूर्णांकo the thपढ़ो_info काष्ठा */
	DEFINE(TI_TASK,		दुरत्व(काष्ठा thपढ़ो_info, task));
	DEFINE(TI_FLAGS,	दुरत्व(काष्ठा thपढ़ो_info, flags));
	DEFINE(TI_CPU,		दुरत्व(काष्ठा thपढ़ो_info, cpu));
	DEFINE(TI_PRE_COUNT,	दुरत्व(काष्ठा thपढ़ो_info, preempt_count));
	DEFINE(TI_SIZE,		माप(काष्ठा thपढ़ो_info));

#अगर_घोषित CONFIG_HIBERNATION
	DEFINE(PBE_ADDRESS, दुरत्व(काष्ठा pbe, address));
	DEFINE(PBE_ORIG_ADDRESS, दुरत्व(काष्ठा pbe, orig_address));
	DEFINE(PBE_NEXT, दुरत्व(काष्ठा pbe, next));
	DEFINE(SWSUSP_ARCH_REGS_SIZE, माप(काष्ठा swsusp_arch_regs));
#पूर्ण_अगर

	DEFINE(SH_SLEEP_MODE, दुरत्व(काष्ठा sh_sleep_data, mode));
	DEFINE(SH_SLEEP_SF_PRE, दुरत्व(काष्ठा sh_sleep_data, sf_pre));
	DEFINE(SH_SLEEP_SF_POST, दुरत्व(काष्ठा sh_sleep_data, sf_post));
	DEFINE(SH_SLEEP_RESUME, दुरत्व(काष्ठा sh_sleep_data, resume));
	DEFINE(SH_SLEEP_VBR, दुरत्व(काष्ठा sh_sleep_data, vbr));
	DEFINE(SH_SLEEP_SPC, दुरत्व(काष्ठा sh_sleep_data, spc));
	DEFINE(SH_SLEEP_SR, दुरत्व(काष्ठा sh_sleep_data, sr));
	DEFINE(SH_SLEEP_SP, दुरत्व(काष्ठा sh_sleep_data, sp));
	DEFINE(SH_SLEEP_BASE_ADDR, दुरत्व(काष्ठा sh_sleep_data, addr));
	DEFINE(SH_SLEEP_BASE_DATA, दुरत्व(काष्ठा sh_sleep_data, data));
	DEFINE(SH_SLEEP_REG_STBCR, दुरत्व(काष्ठा sh_sleep_regs, stbcr));
	DEFINE(SH_SLEEP_REG_BAR, दुरत्व(काष्ठा sh_sleep_regs, bar));
	DEFINE(SH_SLEEP_REG_PTEH, दुरत्व(काष्ठा sh_sleep_regs, pteh));
	DEFINE(SH_SLEEP_REG_PTEL, दुरत्व(काष्ठा sh_sleep_regs, ptel));
	DEFINE(SH_SLEEP_REG_TTB, दुरत्व(काष्ठा sh_sleep_regs, ttb));
	DEFINE(SH_SLEEP_REG_TEA, दुरत्व(काष्ठा sh_sleep_regs, tea));
	DEFINE(SH_SLEEP_REG_MMUCR, दुरत्व(काष्ठा sh_sleep_regs, mmucr));
	DEFINE(SH_SLEEP_REG_PTEA, दुरत्व(काष्ठा sh_sleep_regs, ptea));
	DEFINE(SH_SLEEP_REG_PASCR, दुरत्व(काष्ठा sh_sleep_regs, pascr));
	DEFINE(SH_SLEEP_REG_IRMCR, दुरत्व(काष्ठा sh_sleep_regs, irmcr));
	DEFINE(SH_SLEEP_REG_CCR, दुरत्व(काष्ठा sh_sleep_regs, ccr));
	DEFINE(SH_SLEEP_REG_RAMCR, दुरत्व(काष्ठा sh_sleep_regs, ramcr));
	वापस 0;
पूर्ण
