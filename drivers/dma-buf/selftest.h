<शैली गुरु>
// SPDX-License-Identअगरier: MIT

/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __SELFTEST_H__
#घोषणा __SELFTEST_H__

#समावेश <linux/compiler.h>

#घोषणा selftest(name, func) पूर्णांक func(व्योम);
#समावेश "selftests.h"
#अघोषित selftest

काष्ठा subtest अणु
	पूर्णांक (*func)(व्योम *data);
	स्थिर अक्षर *name;
पूर्ण;

पूर्णांक __subtests(स्थिर अक्षर *caller,
	       स्थिर काष्ठा subtest *st,
	       पूर्णांक count,
	       व्योम *data);
#घोषणा subtests(T, data) \
	__subtests(__func__, T, ARRAY_SIZE(T), data)

#घोषणा SUBTEST(x) अणु x, #x पूर्ण

#पूर्ण_अगर /* __SELFTEST_H__ */
