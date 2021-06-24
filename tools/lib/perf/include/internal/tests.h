<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LIBPERF_INTERNAL_TESTS_H
#घोषणा __LIBPERF_INTERNAL_TESTS_H

#समावेश <मानकपन.स>
#समावेश <unistd.h>

पूर्णांक tests_failed;
पूर्णांक tests_verbose;

अटल अंतरभूत पूर्णांक get_verbose(अक्षर **argv, पूर्णांक argc)
अणु
	पूर्णांक c;
	पूर्णांक verbose = 0;

	जबतक ((c = getopt(argc, argv, "v")) != -1) अणु
		चयन (c)
		अणु
		हाल 'v':
			verbose = 1;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस verbose;
पूर्ण

#घोषणा __T_START					\
करो अणु							\
	tests_verbose = get_verbose(argv, argc);	\
	ख_लिखो(मानक_निकास, "- running %s...", __खाता__);	\
	ख_साफ(शून्य);					\
	tests_failed = 0;				\
पूर्ण जबतक (0)

#घोषणा __T_END								\
करो अणु									\
	अगर (tests_failed)						\
		ख_लिखो(मानक_निकास, "  FAILED (%d)\n", tests_failed);	\
	अन्यथा								\
		ख_लिखो(मानक_निकास, "OK\n");				\
पूर्ण जबतक (0)

#घोषणा __T(text, cond)                                                          \
करो अणु                                                                             \
	अगर (!(cond)) अणु                                                           \
		ख_लिखो(मानक_त्रुटि, "FAILED %s:%d %s\n", __खाता__, __LINE__, text);  \
		tests_failed++;                                                  \
		वापस -1;                                                       \
	पूर्ण                                                                        \
पूर्ण जबतक (0)

#घोषणा __T_VERBOSE(...)						\
करो अणु									\
	अगर (tests_verbose) अणु						\
		अगर (tests_verbose == 1) अणु				\
			ख_अक्षर_दो('\n', मानक_त्रुटि);				\
			tests_verbose++;				\
		पूर्ण							\
		ख_लिखो(मानक_त्रुटि, ##__VA_ARGS__);				\
	पूर्ण								\
पूर्ण जबतक (0)

#पूर्ण_अगर /* __LIBPERF_INTERNAL_TESTS_H */
