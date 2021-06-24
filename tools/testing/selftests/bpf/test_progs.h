<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <निश्चित.स>
#समावेश <मानककोष.स>
#समावेश <मानकतर्क.स>
#समावेश <समय.स>
#समावेश <संकेत.स>

#समावेश <linux/types.h>
प्रकार __u16 __sum16;
#समावेश <arpa/inet.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_packet.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/filter.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/socket.h>
#समावेश <linux/unistd.h>

#समावेश <sys/ioctl.h>
#समावेश <sys/रुको.h>
#समावेश <sys/types.h>
#समावेश <sys/समय.स>
#समावेश <fcntl.h>
#समावेश <pthपढ़ो.h>
#समावेश <linux/bpf.h>
#समावेश <linux/err.h>
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

#समावेश "test_iptunnel_common.h"
#समावेश "bpf_util.h"
#समावेश <bpf/bpf_endian.h>
#समावेश "trace_helpers.h"
#समावेश "testing_helpers.h"
#समावेश "flow_dissector_load.h"

क्रमागत verbosity अणु
	VERBOSE_NONE,
	VERBOSE_NORMAL,
	VERBOSE_VERY,
	VERBOSE_SUPER,
पूर्ण;

काष्ठा str_set अणु
	स्थिर अक्षर **strs;
	पूर्णांक cnt;
पूर्ण;

काष्ठा test_selector अणु
	काष्ठा str_set whitelist;
	काष्ठा str_set blacklist;
	bool *num_set;
	पूर्णांक num_set_len;
पूर्ण;

काष्ठा test_env अणु
	काष्ठा test_selector test_selector;
	काष्ठा test_selector subtest_selector;
	bool verअगरier_stats;
	क्रमागत verbosity verbosity;

	bool jit_enabled;
	bool has_tesपंचांगod;
	bool get_test_cnt;
	bool list_test_names;

	काष्ठा prog_test_def *test;
	खाता *मानक_निकास;
	खाता *मानक_त्रुटि;
	अक्षर *log_buf;
	माप_प्रकार log_cnt;
	पूर्णांक nr_cpus;

	पूर्णांक succ_cnt; /* successful tests */
	पूर्णांक sub_succ_cnt; /* successful sub-tests */
	पूर्णांक fail_cnt; /* total failed tests + sub-tests */
	पूर्णांक skip_cnt; /* skipped tests */

	पूर्णांक saved_netns_fd;
पूर्ण;

बाह्य काष्ठा test_env env;

बाह्य व्योम test__क्रमce_log();
बाह्य bool test__start_subtest(स्थिर अक्षर *name);
बाह्य व्योम test__skip(व्योम);
बाह्य व्योम test__fail(व्योम);
बाह्य पूर्णांक test__join_cgroup(स्थिर अक्षर *path);

#घोषणा PRINT_FAIL(क्रमmat...)                                                  \
	(अणु                                                                     \
		test__fail();                                                  \
		ख_लिखो(मानक_निकास, "%s:FAIL:%d ", __func__, __LINE__);            \
		ख_लिखो(मानक_निकास, ##क्रमmat);                                     \
	पूर्ण)

#घोषणा _CHECK(condition, tag, duration, क्रमmat...) (अणु			\
	पूर्णांक __ret = !!(condition);					\
	पूर्णांक __save_त्रुटि_सं = त्रुटि_सं;					\
	अगर (__ret) अणु							\
		test__fail();						\
		ख_लिखो(मानक_निकास, "%s:FAIL:%s ", __func__, tag);		\
		ख_लिखो(मानक_निकास, ##क्रमmat);				\
	पूर्ण अन्यथा अणु							\
		ख_लिखो(मानक_निकास, "%s:PASS:%s %d nsec\n",			\
		       __func__, tag, duration);			\
	पूर्ण								\
	त्रुटि_सं = __save_त्रुटि_सं;						\
	__ret;								\
पूर्ण)

#घोषणा CHECK_FAIL(condition) (अणु					\
	पूर्णांक __ret = !!(condition);					\
	पूर्णांक __save_त्रुटि_सं = त्रुटि_सं;					\
	अगर (__ret) अणु							\
		test__fail();						\
		ख_लिखो(मानक_निकास, "%s:FAIL:%d\n", __func__, __LINE__);	\
	पूर्ण								\
	त्रुटि_सं = __save_त्रुटि_सं;						\
	__ret;								\
पूर्ण)

#घोषणा CHECK(condition, tag, क्रमmat...) \
	_CHECK(condition, tag, duration, क्रमmat)
#घोषणा CHECK_ATTR(condition, tag, क्रमmat...) \
	_CHECK(condition, tag, tattr.duration, क्रमmat)

#घोषणा ASSERT_TRUE(actual, name) (अणु					\
	अटल पूर्णांक duration = 0;					\
	bool ___ok = (actual);						\
	CHECK(!___ok, (name), "unexpected %s: got FALSE\n", (name));	\
	___ok;								\
पूर्ण)

#घोषणा ASSERT_FALSE(actual, name) (अणु					\
	अटल पूर्णांक duration = 0;					\
	bool ___ok = !(actual);						\
	CHECK(!___ok, (name), "unexpected %s: got TRUE\n", (name));	\
	___ok;								\
पूर्ण)

#घोषणा ASSERT_EQ(actual, expected, name) (अणु				\
	अटल पूर्णांक duration = 0;					\
	typeof(actual) ___act = (actual);				\
	typeof(expected) ___exp = (expected);				\
	bool ___ok = ___act == ___exp;					\
	CHECK(!___ok, (name),						\
	      "unexpected %s: actual %lld != expected %lld\n",		\
	      (name), (दीर्घ दीर्घ)(___act), (दीर्घ दीर्घ)(___exp));	\
	___ok;								\
पूर्ण)

#घोषणा ASSERT_NEQ(actual, expected, name) (अणु				\
	अटल पूर्णांक duration = 0;					\
	typeof(actual) ___act = (actual);				\
	typeof(expected) ___exp = (expected);				\
	bool ___ok = ___act != ___exp;					\
	CHECK(!___ok, (name),						\
	      "unexpected %s: actual %lld == expected %lld\n",		\
	      (name), (दीर्घ दीर्घ)(___act), (दीर्घ दीर्घ)(___exp));	\
	___ok;								\
पूर्ण)

#घोषणा ASSERT_LT(actual, expected, name) (अणु				\
	अटल पूर्णांक duration = 0;					\
	typeof(actual) ___act = (actual);				\
	typeof(expected) ___exp = (expected);				\
	bool ___ok = ___act < ___exp;					\
	CHECK(!___ok, (name),						\
	      "unexpected %s: actual %lld >= expected %lld\n",		\
	      (name), (दीर्घ दीर्घ)(___act), (दीर्घ दीर्घ)(___exp));	\
	___ok;								\
पूर्ण)

#घोषणा ASSERT_LE(actual, expected, name) (अणु				\
	अटल पूर्णांक duration = 0;					\
	typeof(actual) ___act = (actual);				\
	typeof(expected) ___exp = (expected);				\
	bool ___ok = ___act <= ___exp;					\
	CHECK(!___ok, (name),						\
	      "unexpected %s: actual %lld > expected %lld\n",		\
	      (name), (दीर्घ दीर्घ)(___act), (दीर्घ दीर्घ)(___exp));	\
	___ok;								\
पूर्ण)

#घोषणा ASSERT_GT(actual, expected, name) (अणु				\
	अटल पूर्णांक duration = 0;					\
	typeof(actual) ___act = (actual);				\
	typeof(expected) ___exp = (expected);				\
	bool ___ok = ___act > ___exp;					\
	CHECK(!___ok, (name),						\
	      "unexpected %s: actual %lld <= expected %lld\n",		\
	      (name), (दीर्घ दीर्घ)(___act), (दीर्घ दीर्घ)(___exp));	\
	___ok;								\
पूर्ण)

#घोषणा ASSERT_GE(actual, expected, name) (अणु				\
	अटल पूर्णांक duration = 0;					\
	typeof(actual) ___act = (actual);				\
	typeof(expected) ___exp = (expected);				\
	bool ___ok = ___act >= ___exp;					\
	CHECK(!___ok, (name),						\
	      "unexpected %s: actual %lld < expected %lld\n",		\
	      (name), (दीर्घ दीर्घ)(___act), (दीर्घ दीर्घ)(___exp));	\
	___ok;								\
पूर्ण)

#घोषणा ASSERT_STREQ(actual, expected, name) (अणु				\
	अटल पूर्णांक duration = 0;					\
	स्थिर अक्षर *___act = actual;					\
	स्थिर अक्षर *___exp = expected;					\
	bool ___ok = म_भेद(___act, ___exp) == 0;			\
	CHECK(!___ok, (name),						\
	      "unexpected %s: actual '%s' != expected '%s'\n",		\
	      (name), ___act, ___exp);					\
	___ok;								\
पूर्ण)

#घोषणा ASSERT_OK(res, name) (अणु						\
	अटल पूर्णांक duration = 0;					\
	दीर्घ दीर्घ ___res = (res);					\
	bool ___ok = ___res == 0;					\
	CHECK(!___ok, (name), "unexpected error: %lld (errno %d)\n",	\
	      ___res, त्रुटि_सं);						\
	___ok;								\
पूर्ण)

#घोषणा ASSERT_ERR(res, name) (अणु					\
	अटल पूर्णांक duration = 0;					\
	दीर्घ दीर्घ ___res = (res);					\
	bool ___ok = ___res < 0;					\
	CHECK(!___ok, (name), "unexpected success: %lld\n", ___res);	\
	___ok;								\
पूर्ण)

#घोषणा ASSERT_शून्य(ptr, name) (अणु					\
	अटल पूर्णांक duration = 0;					\
	स्थिर व्योम *___res = (ptr);					\
	bool ___ok = !___res;						\
	CHECK(!___ok, (name), "unexpected pointer: %p\n", ___res);	\
	___ok;								\
पूर्ण)

#घोषणा ASSERT_OK_PTR(ptr, name) (अणु					\
	अटल पूर्णांक duration = 0;					\
	स्थिर व्योम *___res = (ptr);					\
	bool ___ok = !IS_ERR_OR_शून्य(___res);				\
	CHECK(!___ok, (name),						\
	      "unexpected error: %ld\n", PTR_ERR(___res));		\
	___ok;								\
पूर्ण)

#घोषणा ASSERT_ERR_PTR(ptr, name) (अणु					\
	अटल पूर्णांक duration = 0;					\
	स्थिर व्योम *___res = (ptr);					\
	bool ___ok = IS_ERR(___res);					\
	CHECK(!___ok, (name), "unexpected pointer: %p\n", ___res);	\
	___ok;								\
पूर्ण)

अटल अंतरभूत __u64 ptr_to_u64(स्थिर व्योम *ptr)
अणु
	वापस (__u64) (अचिन्हित दीर्घ) ptr;
पूर्ण

अटल अंतरभूत व्योम *u64_to_ptr(__u64 ptr)
अणु
	वापस (व्योम *) (अचिन्हित दीर्घ) ptr;
पूर्ण

पूर्णांक bpf_find_map(स्थिर अक्षर *test, काष्ठा bpf_object *obj, स्थिर अक्षर *name);
पूर्णांक compare_map_keys(पूर्णांक map1_fd, पूर्णांक map2_fd);
पूर्णांक compare_stack_ips(पूर्णांक smap_fd, पूर्णांक amap_fd, पूर्णांक stack_trace_len);
पूर्णांक extract_build_id(अक्षर *build_id, माप_प्रकार size);
पूर्णांक kern_sync_rcu(व्योम);

#अगर_घोषित __x86_64__
#घोषणा SYS_न_अंकOSLEEP_KPROBE_NAME "__x64_sys_nanosleep"
#या_अगर defined(__s390x__)
#घोषणा SYS_न_अंकOSLEEP_KPROBE_NAME "__s390x_sys_nanosleep"
#अन्यथा
#घोषणा SYS_न_अंकOSLEEP_KPROBE_NAME "sys_nanosleep"
#पूर्ण_अगर
