<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68K_SEGMENT_H
#घोषणा _M68K_SEGMENT_H

/* define स्थिरants */
/* Address spaces (FC0-FC2) */
#घोषणा USER_DATA     (1)
#अगर_अघोषित __USER_DS
#घोषणा __USER_DS     (USER_DATA)
#पूर्ण_अगर
#घोषणा USER_PROGRAM  (2)
#घोषणा SUPER_DATA    (5)
#अगर_अघोषित __KERNEL_DS
#घोषणा __KERNEL_DS   (SUPER_DATA)
#पूर्ण_अगर
#घोषणा SUPER_PROGRAM (6)
#घोषणा CPU_SPACE     (7)

#अगर_अघोषित __ASSEMBLY__

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ seg;
पूर्ण mm_segment_t;

#घोषणा MAKE_MM_SEG(s)	((mm_segment_t) अणु (s) पूर्ण)

#अगर_घोषित CONFIG_CPU_HAS_ADDRESS_SPACES
/*
 * Get/set the SFC/DFC रेजिस्टरs क्रम MOVES inकाष्ठाions
 */
#घोषणा USER_DS		MAKE_MM_SEG(__USER_DS)
#घोषणा KERNEL_DS	MAKE_MM_SEG(__KERNEL_DS)

अटल अंतरभूत mm_segment_t get_fs(व्योम)
अणु
	mm_segment_t _v;
	__यंत्र__ ("movec %/dfc,%0":"=r" (_v.seg):);
	वापस _v;
पूर्ण

अटल अंतरभूत व्योम set_fs(mm_segment_t val)
अणु
	__यंत्र__ __अस्थिर__ ("movec %0,%/sfc\n\t"
			      "movec %0,%/dfc\n\t"
			      : /* no outमाला_दो */ : "r" (val.seg) : "memory");
पूर्ण

#अन्यथा
#घोषणा USER_DS		MAKE_MM_SEG(TASK_SIZE)
#घोषणा KERNEL_DS	MAKE_MM_SEG(0xFFFFFFFF)
#घोषणा get_fs()	(current_thपढ़ो_info()->addr_limit)
#घोषणा set_fs(x)	(current_thपढ़ो_info()->addr_limit = (x))
#पूर्ण_अगर

#घोषणा uaccess_kernel()	(get_fs().seg == KERNEL_DS.seg)

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _M68K_SEGMENT_H */
