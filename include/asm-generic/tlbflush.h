<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_TLBFLUSH_H
#घोषणा __ASM_GENERIC_TLBFLUSH_H
/*
 * This is a dummy tlbflush implementation that can be used on all
 * nommu architectures.
 * If you have an MMU, you need to ग_लिखो your own functions.
 */
#अगर_घोषित CONFIG_MMU
#त्रुटि need to implement an architecture specअगरic यंत्र/tlbflush.h
#पूर्ण_अगर

#समावेश <linux/bug.h>

अटल अंतरभूत व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	BUG();
पूर्ण


#पूर्ण_अगर /* __ASM_GENERIC_TLBFLUSH_H */
