<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2013, Michael Ellerman, IBM Corp.
 */

#अगर_अघोषित _SELFTESTS_POWERPC_SUBUNIT_H
#घोषणा _SELFTESTS_POWERPC_SUBUNIT_H

अटल अंतरभूत व्योम test_start(अक्षर *name)
अणु
	म_लिखो("test: %s\n", name);
पूर्ण

अटल अंतरभूत व्योम test_failure_detail(अक्षर *name, अक्षर *detail)
अणु
	म_लिखो("failure: %s [%s]\n", name, detail);
पूर्ण

अटल अंतरभूत व्योम test_failure(अक्षर *name)
अणु
	म_लिखो("failure: %s\n", name);
पूर्ण

अटल अंतरभूत व्योम test_error(अक्षर *name)
अणु
	म_लिखो("error: %s\n", name);
पूर्ण

अटल अंतरभूत व्योम test_skip(अक्षर *name)
अणु
	म_लिखो("skip: %s\n", name);
पूर्ण

अटल अंतरभूत व्योम test_success(अक्षर *name)
अणु
	म_लिखो("success: %s\n", name);
पूर्ण

अटल अंतरभूत व्योम test_finish(अक्षर *name, पूर्णांक status)
अणु
	अगर (status)
		test_failure(name);
	अन्यथा
		test_success(name);
पूर्ण

अटल अंतरभूत व्योम test_set_git_version(अक्षर *value)
अणु
	म_लिखो("tags: git_version:%s\n", value);
पूर्ण

#पूर्ण_अगर /* _SELFTESTS_POWERPC_SUBUNIT_H */
