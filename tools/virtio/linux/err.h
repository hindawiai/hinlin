<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ERR_H
#घोषणा ERR_H
#घोषणा MAX_ERRNO	4095

#घोषणा IS_ERR_VALUE(x) unlikely((x) >= (अचिन्हित दीर्घ)-MAX_ERRNO)

अटल अंतरभूत व्योम * __must_check ERR_PTR(दीर्घ error)
अणु
	वापस (व्योम *) error;
पूर्ण

अटल अंतरभूत दीर्घ __must_check PTR_ERR(स्थिर व्योम *ptr)
अणु
	वापस (दीर्घ) ptr;
पूर्ण

अटल अंतरभूत दीर्घ __must_check IS_ERR(स्थिर व्योम *ptr)
अणु
	वापस IS_ERR_VALUE((अचिन्हित दीर्घ)ptr);
पूर्ण

अटल अंतरभूत दीर्घ __must_check IS_ERR_OR_शून्य(स्थिर व्योम *ptr)
अणु
	वापस !ptr || IS_ERR_VALUE((अचिन्हित दीर्घ)ptr);
पूर्ण
#पूर्ण_अगर /* ERR_H */
