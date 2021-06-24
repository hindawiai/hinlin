<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_UNALIGNED_GENERIC_H
#घोषणा _LINUX_UNALIGNED_GENERIC_H

#समावेश <linux/types.h>

/*
 * Cause a link-समय error अगर we try an unaligned access other than
 * 1,2,4 or 8 bytes दीर्घ
 */
बाह्य व्योम __bad_unaligned_access_size(व्योम);

#घोषणा __get_unaligned_le(ptr) ((__क्रमce typeof(*(ptr)))(अणु			\
	__builtin_choose_expr(माप(*(ptr)) == 1, *(ptr),			\
	__builtin_choose_expr(माप(*(ptr)) == 2, get_unaligned_le16((ptr)),	\
	__builtin_choose_expr(माप(*(ptr)) == 4, get_unaligned_le32((ptr)),	\
	__builtin_choose_expr(माप(*(ptr)) == 8, get_unaligned_le64((ptr)),	\
	__bad_unaligned_access_size()))));					\
	पूर्ण))

#घोषणा __get_unaligned_be(ptr) ((__क्रमce typeof(*(ptr)))(अणु			\
	__builtin_choose_expr(माप(*(ptr)) == 1, *(ptr),			\
	__builtin_choose_expr(माप(*(ptr)) == 2, get_unaligned_be16((ptr)),	\
	__builtin_choose_expr(माप(*(ptr)) == 4, get_unaligned_be32((ptr)),	\
	__builtin_choose_expr(माप(*(ptr)) == 8, get_unaligned_be64((ptr)),	\
	__bad_unaligned_access_size()))));					\
	पूर्ण))

#घोषणा __put_unaligned_le(val, ptr) (अणु					\
	व्योम *__gu_p = (ptr);						\
	चयन (माप(*(ptr))) अणु					\
	हाल 1:								\
		*(u8 *)__gu_p = (__क्रमce u8)(val);			\
		अवरोध;							\
	हाल 2:								\
		put_unaligned_le16((__क्रमce u16)(val), __gu_p);		\
		अवरोध;							\
	हाल 4:								\
		put_unaligned_le32((__क्रमce u32)(val), __gu_p);		\
		अवरोध;							\
	हाल 8:								\
		put_unaligned_le64((__क्रमce u64)(val), __gu_p);		\
		अवरोध;							\
	शेष:							\
		__bad_unaligned_access_size();				\
		अवरोध;							\
	पूर्ण								\
	(व्योम)0; पूर्ण)

#घोषणा __put_unaligned_be(val, ptr) (अणु					\
	व्योम *__gu_p = (ptr);						\
	चयन (माप(*(ptr))) अणु					\
	हाल 1:								\
		*(u8 *)__gu_p = (__क्रमce u8)(val);			\
		अवरोध;							\
	हाल 2:								\
		put_unaligned_be16((__क्रमce u16)(val), __gu_p);		\
		अवरोध;							\
	हाल 4:								\
		put_unaligned_be32((__क्रमce u32)(val), __gu_p);		\
		अवरोध;							\
	हाल 8:								\
		put_unaligned_be64((__क्रमce u64)(val), __gu_p);		\
		अवरोध;							\
	शेष:							\
		__bad_unaligned_access_size();				\
		अवरोध;							\
	पूर्ण								\
	(व्योम)0; पूर्ण)

अटल अंतरभूत u32 __get_unaligned_be24(स्थिर u8 *p)
अणु
	वापस p[0] << 16 | p[1] << 8 | p[2];
पूर्ण

अटल अंतरभूत u32 get_unaligned_be24(स्थिर व्योम *p)
अणु
	वापस __get_unaligned_be24(p);
पूर्ण

अटल अंतरभूत u32 __get_unaligned_le24(स्थिर u8 *p)
अणु
	वापस p[0] | p[1] << 8 | p[2] << 16;
पूर्ण

अटल अंतरभूत u32 get_unaligned_le24(स्थिर व्योम *p)
अणु
	वापस __get_unaligned_le24(p);
पूर्ण

अटल अंतरभूत व्योम __put_unaligned_be24(स्थिर u32 val, u8 *p)
अणु
	*p++ = val >> 16;
	*p++ = val >> 8;
	*p++ = val;
पूर्ण

अटल अंतरभूत व्योम put_unaligned_be24(स्थिर u32 val, व्योम *p)
अणु
	__put_unaligned_be24(val, p);
पूर्ण

अटल अंतरभूत व्योम __put_unaligned_le24(स्थिर u32 val, u8 *p)
अणु
	*p++ = val;
	*p++ = val >> 8;
	*p++ = val >> 16;
पूर्ण

अटल अंतरभूत व्योम put_unaligned_le24(स्थिर u32 val, व्योम *p)
अणु
	__put_unaligned_le24(val, p);
पूर्ण

#पूर्ण_अगर /* _LINUX_UNALIGNED_GENERIC_H */
