<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __TOOLS_LINUX_ERR_H
#घोषणा __TOOLS_LINUX_ERR_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/त्रुटिसं.स>

/*
 * Original kernel header comment:
 *
 * Kernel poपूर्णांकers have redundant inक्रमmation, so we can use a
 * scheme where we can वापस either an error code or a normal
 * poपूर्णांकer with the same वापस value.
 *
 * This should be a per-architecture thing, to allow dअगरferent
 * error and poपूर्णांकer decisions.
 *
 * Userspace note:
 * The same principle works क्रम userspace, because 'error' poपूर्णांकers
 * fall करोwn to the unused hole far from user space, as described
 * in Documentation/x86/x86_64/mm.rst क्रम x86_64 arch:
 *
 * 0000000000000000 - 00007fffffffffff (=47 bits) user space, dअगरferent per mm hole caused by [48:63] sign extension
 * ffffffffffe00000 - ffffffffffffffff (=2 MB) unused hole
 *
 * It should be the same हाल क्रम other architectures, because
 * this code is used in generic kernel code.
 */
#घोषणा MAX_ERRNO	4095

#घोषणा IS_ERR_VALUE(x) unlikely((x) >= (अचिन्हित दीर्घ)-MAX_ERRNO)

अटल अंतरभूत व्योम * __must_check ERR_PTR(दीर्घ error_)
अणु
	वापस (व्योम *) error_;
पूर्ण

अटल अंतरभूत दीर्घ __must_check PTR_ERR(__क्रमce स्थिर व्योम *ptr)
अणु
	वापस (दीर्घ) ptr;
पूर्ण

अटल अंतरभूत bool __must_check IS_ERR(__क्रमce स्थिर व्योम *ptr)
अणु
	वापस IS_ERR_VALUE((अचिन्हित दीर्घ)ptr);
पूर्ण

अटल अंतरभूत bool __must_check IS_ERR_OR_शून्य(__क्रमce स्थिर व्योम *ptr)
अणु
	वापस unlikely(!ptr) || IS_ERR_VALUE((अचिन्हित दीर्घ)ptr);
पूर्ण

अटल अंतरभूत पूर्णांक __must_check PTR_ERR_OR_ZERO(__क्रमce स्थिर व्योम *ptr)
अणु
	अगर (IS_ERR(ptr))
		वापस PTR_ERR(ptr);
	अन्यथा
		वापस 0;
पूर्ण

/**
 * ERR_CAST - Explicitly cast an error-valued poपूर्णांकer to another poपूर्णांकer type
 * @ptr: The poपूर्णांकer to cast.
 *
 * Explicitly cast an error-valued poपूर्णांकer to another poपूर्णांकer type in such a
 * way as to make it clear that's what's going on.
 */
अटल अंतरभूत व्योम * __must_check ERR_CAST(__क्रमce स्थिर व्योम *ptr)
अणु
	/* cast away the स्थिर */
	वापस (व्योम *) ptr;
पूर्ण
#पूर्ण_अगर /* _LINUX_ERR_H */
