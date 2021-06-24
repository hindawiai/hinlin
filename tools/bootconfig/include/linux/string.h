<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SKC_LINUX_STRING_H
#घोषणा _SKC_LINUX_STRING_H

#समावेश <माला.स>

/* Copied from lib/string.c */
अटल अंतरभूत अक्षर *skip_spaces(स्थिर अक्षर *str)
अणु
	जबतक (है_खाली(*str))
		++str;
	वापस (अक्षर *)str;
पूर्ण

अटल अंतरभूत अक्षर *strim(अक्षर *s)
अणु
	माप_प्रकार size;
	अक्षर *end;

	size = म_माप(s);
	अगर (!size)
		वापस s;

	end = s + size - 1;
	जबतक (end >= s && है_खाली(*end))
		end--;
	*(end + 1) = '\0';

	वापस skip_spaces(s);
पूर्ण

#पूर्ण_अगर
