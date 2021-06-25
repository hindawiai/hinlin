<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1 */
/*
 * Copyright (C) 2010 Red Hat Inc, Steven Rostedt <srostedt@redhat.com>
 *
 */
#अगर_अघोषित __UTIL_H
#घोषणा __UTIL_H

#समावेश <प्रकार.स>

/* Can be overridden */
व्योम warning(स्थिर अक्षर *fmt, ...);
व्योम pr_stat(स्थिर अक्षर *fmt, ...);
व्योम vpr_stat(स्थिर अक्षर *fmt, बहु_सूची ap);

/* Always available */
व्योम __warning(स्थिर अक्षर *fmt, ...);
व्योम __pr_stat(स्थिर अक्षर *fmt, ...);

व्योम __vwarning(स्थिर अक्षर *fmt, ...);
व्योम __vpr_stat(स्थिर अक्षर *fmt, ...);

#घोषणा min(x, y) (अणु				\
	typeof(x) _min1 = (x);			\
	typeof(y) _min2 = (y);			\
	(व्योम) (&_min1 == &_min2);		\
	_min1 < _min2 ? _min1 : _min2; पूर्ण)

अटल अंतरभूत अक्षर *strim(अक्षर *string)
अणु
	अक्षर *ret;

	अगर (!string)
		वापस शून्य;
	जबतक (*string) अणु
		अगर (!है_खाली(*string))
			अवरोध;
		string++;
	पूर्ण
	ret = string;

	string = ret + म_माप(ret) - 1;
	जबतक (string > ret) अणु
		अगर (!है_खाली(*string))
			अवरोध;
		string--;
	पूर्ण
	string[1] = 0;

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक has_text(स्थिर अक्षर *text)
अणु
	अगर (!text)
		वापस 0;

	जबतक (*text) अणु
		अगर (!है_खाली(*text))
			वापस 1;
		text++;
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर
