<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __UM_SEGMENT_H
#घोषणा __UM_SEGMENT_H

बाह्य पूर्णांक host_gdt_entry_tls_min;

#घोषणा GDT_ENTRY_TLS_ENTRIES 3
#घोषणा GDT_ENTRY_TLS_MIN host_gdt_entry_tls_min
#घोषणा GDT_ENTRY_TLS_MAX (GDT_ENTRY_TLS_MIN + GDT_ENTRY_TLS_ENTRIES - 1)

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ seg;
पूर्ण mm_segment_t;

#घोषणा MAKE_MM_SEG(s)	((mm_segment_t) अणु (s) पूर्ण)
#घोषणा KERNEL_DS	MAKE_MM_SEG(~0UL)
#घोषणा USER_DS		MAKE_MM_SEG(TASK_SIZE)

#पूर्ण_अगर
