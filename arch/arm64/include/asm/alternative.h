<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ALTERNATIVE_H
#घोषणा __ASM_ALTERNATIVE_H

#समावेश <यंत्र/alternative-macros.h>

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/मानकघोष.स>

काष्ठा alt_instr अणु
	s32 orig_offset;	/* offset to original inकाष्ठाion */
	s32 alt_offset;		/* offset to replacement inकाष्ठाion */
	u16 cpufeature;		/* cpufeature bit set क्रम replacement */
	u8  orig_len;		/* size of original inकाष्ठाion(s) */
	u8  alt_len;		/* size of new inकाष्ठाion(s), <= orig_len */
पूर्ण;

प्रकार व्योम (*alternative_cb_t)(काष्ठा alt_instr *alt,
				 __le32 *origptr, __le32 *updptr, पूर्णांक nr_inst);

व्योम __init apply_boot_alternatives(व्योम);
व्योम __init apply_alternatives_all(व्योम);
bool alternative_is_applied(u16 cpufeature);

#अगर_घोषित CONFIG_MODULES
व्योम apply_alternatives_module(व्योम *start, माप_प्रकार length);
#अन्यथा
अटल अंतरभूत व्योम apply_alternatives_module(व्योम *start, माप_प्रकार length) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __ASM_ALTERNATIVE_H */
