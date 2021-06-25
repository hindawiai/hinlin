<शैली गुरु>
#अगर_अघोषित _LINUX_CONST_H
#घोषणा _LINUX_CONST_H

#समावेश <vdso/स्थिर.h>

/*
 * This वापसs a स्थिरant expression जबतक determining अगर an argument is
 * a स्थिरant expression, most importantly without evaluating the argument.
 * Glory to Martin Uecker <Martin.Uecker@med.uni-goettingen.de>
 */
#घोषणा __is_स्थिरexpr(x) \
	(माप(पूर्णांक) == माप(*(8 ? ((व्योम *)((दीर्घ)(x) * 0l)) : (पूर्णांक *)8)))

#पूर्ण_अगर /* _LINUX_CONST_H */
