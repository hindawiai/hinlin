<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/cpu.h>

#समावेश <linux/jump_label.h>
#समावेश <linux/memory.h>

#समावेश <यंत्र/cacheflush.h>

व्योम arch_jump_label_transक्रमm(काष्ठा jump_entry *entry,
			       क्रमागत jump_label_type type)
अणु
	u32 *insn = (u32 *) (अचिन्हित दीर्घ) entry->code;
	u32 val;

	अगर (type == JUMP_LABEL_JMP) अणु
		s32 off = (s32)entry->target - (s32)entry->code;
		bool use_v9_branch = false;

		BUG_ON(off & 3);

#अगर_घोषित CONFIG_SPARC64
		अगर (off <= 0xfffff && off >= -0x100000)
			use_v9_branch = true;
#पूर्ण_अगर
		अगर (use_v9_branch) अणु
			/* WDISP19 - target is . + immed << 2 */
			/* ba,pt %xcc, . + off */
			val = 0x10680000 | (((u32) off >> 2) & 0x7ffff);
		पूर्ण अन्यथा अणु
			/* WDISP22 - target is . + immed << 2 */
			BUG_ON(off > 0x7fffff);
			BUG_ON(off < -0x800000);
			/* ba . + off */
			val = 0x10800000 | (((u32) off >> 2) & 0x3fffff);
		पूर्ण
	पूर्ण अन्यथा अणु
		val = 0x01000000;
	पूर्ण

	mutex_lock(&text_mutex);
	*insn = val;
	flushi(insn);
	mutex_unlock(&text_mutex);
पूर्ण
