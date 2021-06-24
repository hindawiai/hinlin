<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * KUnit API allowing dynamic analysis tools to पूर्णांकeract with KUnit tests
 *
 * Copyright (C) 2020, Google LLC.
 * Author: Uriel Guajarकरो <urielguajarकरो@google.com>
 */

#अगर_अघोषित _KUNIT_TEST_BUG_H
#घोषणा _KUNIT_TEST_BUG_H

#घोषणा kunit_fail_current_test(fmt, ...) \
	__kunit_fail_current_test(__खाता__, __LINE__, fmt, ##__VA_ARGS__)

#अगर IS_BUILTIN(CONFIG_KUNIT)

बाह्य __म_लिखो(3, 4) व्योम __kunit_fail_current_test(स्थिर अक्षर *file, पूर्णांक line,
						    स्थिर अक्षर *fmt, ...);

#अन्यथा

अटल अंतरभूत __म_लिखो(3, 4) व्योम __kunit_fail_current_test(स्थिर अक्षर *file, पूर्णांक line,
							    स्थिर अक्षर *fmt, ...)
अणु
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* _KUNIT_TEST_BUG_H */
