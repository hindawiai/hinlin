<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Landlock test helpers
 *
 * Copyright तऊ 2017-2020 Mickaथ+l Salaथञn <mic@digikod.net>
 * Copyright तऊ 2019-2020 ANSSI
 * Copyright तऊ 2021 Microsoft Corporation
 */

#समावेश <त्रुटिसं.स>
#समावेश <linux/landlock.h>
#समावेश <sys/capability.h>
#समावेश <sys/syscall.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>

#समावेश "../kselftest_harness.h"

#अगर_अघोषित ARRAY_SIZE
#घोषणा ARRAY_SIZE(x) (माप(x) / माप((x)[0]))
#पूर्ण_अगर

/*
 * TEST_F_FORK() is useful when a test drop privileges but the corresponding
 * FIXTURE_TEARDOWN() requires them (e.g. to हटाओ files from a directory
 * where ग_लिखो actions are denied).  For convenience, FIXTURE_TEARDOWN() is
 * also called when the test failed, but not when FIXTURE_SETUP() failed.  For
 * this to be possible, we must not call पात() but instead निकास smoothly
 * (hence the step prपूर्णांक).
 */
#घोषणा TEST_F_FORK(fixture_name, test_name) \
	अटल व्योम fixture_name##_##test_name##_child( \
		काष्ठा __test_metadata *_metadata, \
		FIXTURE_DATA(fixture_name) *self, \
		स्थिर FIXTURE_VARIANT(fixture_name) *variant); \
	TEST_F(fixture_name, test_name) \
	अणु \
		पूर्णांक status; \
		स्थिर pid_t child = विभाजन(); \
		अगर (child < 0) \
			पात(); \
		अगर (child == 0) अणु \
			_metadata->no_prपूर्णांक = 1; \
			fixture_name##_##test_name##_child(_metadata, self, variant); \
			अगर (_metadata->skip) \
				_निकास(255); \
			अगर (_metadata->passed) \
				_निकास(0); \
			_निकास(_metadata->step); \
		पूर्ण \
		अगर (child != रुकोpid(child, &status, 0)) \
			पात(); \
		अगर (WIFSIGNALED(status) || !WIFEXITED(status)) अणु \
			_metadata->passed = 0; \
			_metadata->step = 1; \
			वापस; \
		पूर्ण \
		चयन (WEXITSTATUS(status)) अणु \
		हाल 0: \
			_metadata->passed = 1; \
			अवरोध; \
		हाल 255: \
			_metadata->passed = 1; \
			_metadata->skip = 1; \
			अवरोध; \
		शेष: \
			_metadata->passed = 0; \
			_metadata->step = WEXITSTATUS(status); \
			अवरोध; \
		पूर्ण \
	पूर्ण \
	अटल व्योम fixture_name##_##test_name##_child( \
		काष्ठा __test_metadata __attribute__((unused)) *_metadata, \
		FIXTURE_DATA(fixture_name) __attribute__((unused)) *self, \
		स्थिर FIXTURE_VARIANT(fixture_name) \
			__attribute__((unused)) *variant)

#अगर_अघोषित landlock_create_ruleset
अटल अंतरभूत पूर्णांक landlock_create_ruleset(
		स्थिर काष्ठा landlock_ruleset_attr *स्थिर attr,
		स्थिर माप_प्रकार size, स्थिर __u32 flags)
अणु
	वापस syscall(__NR_landlock_create_ruleset, attr, size, flags);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित landlock_add_rule
अटल अंतरभूत पूर्णांक landlock_add_rule(स्थिर पूर्णांक ruleset_fd,
		स्थिर क्रमागत landlock_rule_type rule_type,
		स्थिर व्योम *स्थिर rule_attr, स्थिर __u32 flags)
अणु
	वापस syscall(__NR_landlock_add_rule, ruleset_fd, rule_type,
			rule_attr, flags);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित landlock_restrict_self
अटल अंतरभूत पूर्णांक landlock_restrict_self(स्थिर पूर्णांक ruleset_fd,
		स्थिर __u32 flags)
अणु
	वापस syscall(__NR_landlock_restrict_self, ruleset_fd, flags);
पूर्ण
#पूर्ण_अगर

अटल व्योम _init_caps(काष्ठा __test_metadata *स्थिर _metadata, bool drop_all)
अणु
	cap_t cap_p;
	/* Only these three capabilities are useful क्रम the tests. */
	स्थिर cap_value_t caps[] = अणु
		CAP_DAC_OVERRIDE,
		CAP_MKNOD,
		CAP_SYS_ADMIN,
		CAP_SYS_CHROOT,
	पूर्ण;

	cap_p = cap_get_proc();
	EXPECT_NE(शून्य, cap_p) अणु
		TH_LOG("Failed to cap_get_proc: %s", म_त्रुटि(त्रुटि_सं));
	पूर्ण
	EXPECT_NE(-1, cap_clear(cap_p)) अणु
		TH_LOG("Failed to cap_clear: %s", म_त्रुटि(त्रुटि_सं));
	पूर्ण
	अगर (!drop_all) अणु
		EXPECT_NE(-1, cap_set_flag(cap_p, CAP_PERMITTED,
					ARRAY_SIZE(caps), caps, CAP_SET)) अणु
			TH_LOG("Failed to cap_set_flag: %s", म_त्रुटि(त्रुटि_सं));
		पूर्ण
	पूर्ण
	EXPECT_NE(-1, cap_set_proc(cap_p)) अणु
		TH_LOG("Failed to cap_set_proc: %s", म_त्रुटि(त्रुटि_सं));
	पूर्ण
	EXPECT_NE(-1, cap_मुक्त(cap_p)) अणु
		TH_LOG("Failed to cap_free: %s", म_त्रुटि(त्रुटि_सं));
	पूर्ण
पूर्ण

/* We cannot put such helpers in a library because of kselftest_harness.h . */
__attribute__((__unused__))
अटल व्योम disable_caps(काष्ठा __test_metadata *स्थिर _metadata)
अणु
	_init_caps(_metadata, false);
पूर्ण

__attribute__((__unused__))
अटल व्योम drop_caps(काष्ठा __test_metadata *स्थिर _metadata)
अणु
	_init_caps(_metadata, true);
पूर्ण

अटल व्योम _effective_cap(काष्ठा __test_metadata *स्थिर _metadata,
		स्थिर cap_value_t caps, स्थिर cap_flag_value_t value)
अणु
	cap_t cap_p;

	cap_p = cap_get_proc();
	EXPECT_NE(शून्य, cap_p) अणु
		TH_LOG("Failed to cap_get_proc: %s", म_त्रुटि(त्रुटि_सं));
	पूर्ण
	EXPECT_NE(-1, cap_set_flag(cap_p, CAP_EFFECTIVE, 1, &caps, value)) अणु
		TH_LOG("Failed to cap_set_flag: %s", म_त्रुटि(त्रुटि_सं));
	पूर्ण
	EXPECT_NE(-1, cap_set_proc(cap_p)) अणु
		TH_LOG("Failed to cap_set_proc: %s", म_त्रुटि(त्रुटि_सं));
	पूर्ण
	EXPECT_NE(-1, cap_मुक्त(cap_p)) अणु
		TH_LOG("Failed to cap_free: %s", म_त्रुटि(त्रुटि_सं));
	पूर्ण
पूर्ण

__attribute__((__unused__))
अटल व्योम set_cap(काष्ठा __test_metadata *स्थिर _metadata,
		स्थिर cap_value_t caps)
अणु
	_effective_cap(_metadata, caps, CAP_SET);
पूर्ण

__attribute__((__unused__))
अटल व्योम clear_cap(काष्ठा __test_metadata *स्थिर _metadata,
		स्थिर cap_value_t caps)
अणु
	_effective_cap(_metadata, caps, CAP_CLEAR);
पूर्ण
