<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_UNALIGNED_MEMMOVE_H
#घोषणा _LINUX_UNALIGNED_MEMMOVE_H

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>

/* Use स_हटाओ here, so gcc करोes not insert a __builtin_स_नकल. */

अटल अंतरभूत u16 __get_unaligned_स_हटाओ16(स्थिर व्योम *p)
अणु
	u16 पंचांगp;
	स_हटाओ(&पंचांगp, p, 2);
	वापस पंचांगp;
पूर्ण

अटल अंतरभूत u32 __get_unaligned_स_हटाओ32(स्थिर व्योम *p)
अणु
	u32 पंचांगp;
	स_हटाओ(&पंचांगp, p, 4);
	वापस पंचांगp;
पूर्ण

अटल अंतरभूत u64 __get_unaligned_स_हटाओ64(स्थिर व्योम *p)
अणु
	u64 पंचांगp;
	स_हटाओ(&पंचांगp, p, 8);
	वापस पंचांगp;
पूर्ण

अटल अंतरभूत व्योम __put_unaligned_स_हटाओ16(u16 val, व्योम *p)
अणु
	स_हटाओ(p, &val, 2);
पूर्ण

अटल अंतरभूत व्योम __put_unaligned_स_हटाओ32(u32 val, व्योम *p)
अणु
	स_हटाओ(p, &val, 4);
पूर्ण

अटल अंतरभूत व्योम __put_unaligned_स_हटाओ64(u64 val, व्योम *p)
अणु
	स_हटाओ(p, &val, 8);
पूर्ण

#पूर्ण_अगर /* _LINUX_UNALIGNED_MEMMOVE_H */
