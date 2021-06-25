<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_SEGMENT_H
#घोषणा __ASM_SH_SEGMENT_H

#अगर_अघोषित __ASSEMBLY__

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ seg;
पूर्ण mm_segment_t;

#घोषणा MAKE_MM_SEG(s)	((mm_segment_t) अणु (s) पूर्ण)

/*
 * The fs value determines whether argument validity checking should be
 * perक्रमmed or not.  If get_fs() == USER_DS, checking is perक्रमmed, with
 * get_fs() == KERNEL_DS, checking is bypassed.
 *
 * For historical reasons, these macros are grossly misnamed.
 */
#घोषणा KERNEL_DS	MAKE_MM_SEG(0xFFFFFFFFUL)
#अगर_घोषित CONFIG_MMU
#घोषणा USER_DS		MAKE_MM_SEG(PAGE_OFFSET)
#अन्यथा
#घोषणा USER_DS		KERNEL_DS
#पूर्ण_अगर

#घोषणा uaccess_kernel() (get_fs().seg == KERNEL_DS.seg)

#घोषणा get_fs()	(current_thपढ़ो_info()->addr_limit)
#घोषणा set_fs(x)	(current_thपढ़ो_info()->addr_limit = (x))

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __ASM_SH_SEGMENT_H */
