<शैली गुरु>
/*
 * Copyright (C) 2004 Fujitsu Siemens Computers GmbH
 * Licensed under the GPL
 *
 * Author: Boकरो Stroesser <bstroesser@fujitsu-siemens.com>
 */

#अगर_अघोषित __ASM_LDT_H
#घोषणा __ASM_LDT_H

#समावेश <linux/mutex.h>
#समावेश <यंत्र/ldt.h>

बाह्य व्योम ldt_host_info(व्योम);

#घोषणा LDT_PAGES_MAX \
	((LDT_ENTRIES * LDT_ENTRY_SIZE)/PAGE_SIZE)
#घोषणा LDT_ENTRIES_PER_PAGE \
	(PAGE_SIZE/LDT_ENTRY_SIZE)
#घोषणा LDT_सूचीECT_ENTRIES \
	((LDT_PAGES_MAX*माप(व्योम *))/LDT_ENTRY_SIZE)

काष्ठा ldt_entry अणु
	__u32 a;
	__u32 b;
पूर्ण;

प्रकार काष्ठा uml_ldt अणु
	पूर्णांक entry_count;
	काष्ठा mutex lock;
	जोड़ अणु
		काष्ठा ldt_entry * pages[LDT_PAGES_MAX];
		काष्ठा ldt_entry entries[LDT_सूचीECT_ENTRIES];
	पूर्ण u;
पूर्ण uml_ldt_t;

#घोषणा LDT_entry_a(info) \
	((((info)->base_addr & 0x0000ffff) << 16) | ((info)->limit & 0x0ffff))

#घोषणा LDT_entry_b(info) \
	(((info)->base_addr & 0xff000000) | \
	(((info)->base_addr & 0x00ff0000) >> 16) | \
	((info)->limit & 0xf0000) | \
	(((info)->पढ़ो_exec_only ^ 1) << 9) | \
	((info)->contents << 10) | \
	(((info)->seg_not_present ^ 1) << 15) | \
	((info)->seg_32bit << 22) | \
	((info)->limit_in_pages << 23) | \
	((info)->useable << 20) | \
	0x7000)

#घोषणा _LDT_empty(info) (\
	(info)->base_addr	== 0	&& \
	(info)->limit		== 0	&& \
	(info)->contents	== 0	&& \
	(info)->पढ़ो_exec_only	== 1	&& \
	(info)->seg_32bit	== 0	&& \
	(info)->limit_in_pages	== 0	&& \
	(info)->seg_not_present	== 1	&& \
	(info)->useable		== 0	)

#अगर_घोषित CONFIG_X86_64
#घोषणा LDT_empty(info) (_LDT_empty(info) && ((info)->lm == 0))
#अन्यथा
#घोषणा LDT_empty(info) (_LDT_empty(info))
#पूर्ण_अगर

काष्ठा uml_arch_mm_context अणु
	uml_ldt_t ldt;
पूर्ण;

#पूर्ण_अगर
