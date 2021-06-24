<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TEST_MAPS_H
#घोषणा _TEST_MAPS_H

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>

#घोषणा CHECK(condition, tag, क्रमmat...) (अणु				\
	पूर्णांक __ret = !!(condition);					\
	अगर (__ret) अणु							\
		म_लिखो("%s(%d):FAIL:%s ", __func__, __LINE__, tag);	\
		म_लिखो(क्रमmat);						\
		निकास(-1);						\
	पूर्ण								\
पूर्ण)

#पूर्ण_अगर
