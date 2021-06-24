<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_ERR_H
#घोषणा _LINUX_ERR_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/त्रुटिसं.स>

/*
 * Kernel poपूर्णांकers have redundant inक्रमmation, so we can use a
 * scheme where we can वापस either an error code or a normal
 * poपूर्णांकer with the same वापस value.
 *
 * This should be a per-architecture thing, to allow dअगरferent
 * error and poपूर्णांकer decisions.
 */
#घोषणा MAX_ERRNO	4095

#अगर_अघोषित __ASSEMBLY__

#घोषणा IS_ERR_VALUE(x) unlikely((अचिन्हित दीर्घ)(व्योम *)(x) >= (अचिन्हित दीर्घ)-MAX_ERRNO)

अटल अंतरभूत व्योम * __must_check ERR_PTR(दीर्घ error)
अणु
	वापस (व्योम *) error;
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

अटल अंतरभूत पूर्णांक __must_check PTR_ERR_OR_ZERO(__क्रमce स्थिर व्योम *ptr)
अणु
	अगर (IS_ERR(ptr))
		वापस PTR_ERR(ptr);
	अन्यथा
		वापस 0;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_ERR_H */
