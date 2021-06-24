<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _H8300_SEGMENT_H
#घोषणा _H8300_SEGMENT_H

/* define स्थिरants */
#घोषणा USER_DATA     (1)
#अगर_अघोषित __USER_DS
#घोषणा __USER_DS     (USER_DATA)
#पूर्ण_अगर
#घोषणा USER_PROGRAM  (2)
#घोषणा SUPER_DATA    (3)
#अगर_अघोषित __KERNEL_DS
#घोषणा __KERNEL_DS   (SUPER_DATA)
#पूर्ण_अगर
#घोषणा SUPER_PROGRAM (4)

#अगर_अघोषित __ASSEMBLY__

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ seg;
पूर्ण mm_segment_t;

#घोषणा MAKE_MM_SEG(s)	((mm_segment_t) अणु (s) पूर्ण)
#घोषणा USER_DS		MAKE_MM_SEG(__USER_DS)
#घोषणा KERNEL_DS	MAKE_MM_SEG(__KERNEL_DS)

/*
 * Get/set the SFC/DFC रेजिस्टरs क्रम MOVES inकाष्ठाions
 */

अटल अंतरभूत mm_segment_t get_fs(व्योम)
अणु
	वापस USER_DS;
पूर्ण

#घोषणा uaccess_kernel()	(get_fs().seg == KERNEL_DS.seg)

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _H8300_SEGMENT_H */
