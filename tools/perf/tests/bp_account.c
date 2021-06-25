<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Powerpc needs __SANE_USERSPACE_TYPES__ beक्रमe <linux/types.h> to select
 * 'int-ll64.h' and aव्योम compile warnings when prपूर्णांकing __u64 with %llu.
 */
#घोषणा __SANE_USERSPACE_TYPES__

#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>
#समावेश <fcntl.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>

#समावेश "tests.h"
#समावेश "debug.h"
#समावेश "event.h"
#समावेश "../perf-sys.h"
#समावेश "cloexec.h"

अटल अस्थिर दीर्घ the_var;

अटल noअंतरभूत पूर्णांक test_function(व्योम)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक __event(bool is_x, व्योम *addr, काष्ठा perf_event_attr *attr)
अणु
	पूर्णांक fd;

	स_रखो(attr, 0, माप(काष्ठा perf_event_attr));
	attr->type = PERF_TYPE_BREAKPOINT;
	attr->size = माप(काष्ठा perf_event_attr);

	attr->config = 0;
	attr->bp_type = is_x ? HW_BREAKPOINT_X : HW_BREAKPOINT_W;
	attr->bp_addr = (अचिन्हित दीर्घ) addr;
	attr->bp_len = माप(दीर्घ);

	attr->sample_period = 1;
	attr->sample_type = PERF_SAMPLE_IP;

	attr->exclude_kernel = 1;
	attr->exclude_hv = 1;

	fd = sys_perf_event_खोलो(attr, -1, 0, -1,
				 perf_event_खोलो_cloexec_flag());
	अगर (fd < 0) अणु
		pr_debug("failed opening event %llx\n", attr->config);
		वापस TEST_FAIL;
	पूर्ण

	वापस fd;
पूर्ण

अटल पूर्णांक wp_event(व्योम *addr, काष्ठा perf_event_attr *attr)
अणु
	वापस __event(false, addr, attr);
पूर्ण

अटल पूर्णांक bp_event(व्योम *addr, काष्ठा perf_event_attr *attr)
अणु
	वापस __event(true, addr, attr);
पूर्ण

अटल पूर्णांक bp_accounting(पूर्णांक wp_cnt, पूर्णांक share)
अणु
	काष्ठा perf_event_attr attr, attr_mod, attr_new;
	पूर्णांक i, fd[wp_cnt], fd_wp, ret;

	क्रम (i = 0; i < wp_cnt; i++) अणु
		fd[i] = wp_event((व्योम *)&the_var, &attr);
		TEST_ASSERT_VAL("failed to create wp\n", fd[i] != -1);
		pr_debug("wp %d created\n", i);
	पूर्ण

	attr_mod = attr;
	attr_mod.bp_type = HW_BREAKPOINT_X;
	attr_mod.bp_addr = (अचिन्हित दीर्घ) test_function;

	ret = ioctl(fd[0], PERF_EVENT_IOC_MODIFY_ATTRIBUTES, &attr_mod);
	TEST_ASSERT_VAL("failed to modify wp\n", ret == 0);

	pr_debug("wp 0 modified to bp\n");

	अगर (!share) अणु
		fd_wp = wp_event((व्योम *)&the_var, &attr_new);
		TEST_ASSERT_VAL("failed to create max wp\n", fd_wp != -1);
		pr_debug("wp max created\n");
	पूर्ण

	क्रम (i = 0; i < wp_cnt; i++)
		बंद(fd[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक detect_cnt(bool is_x)
अणु
	काष्ठा perf_event_attr attr;
	व्योम *addr = is_x ? (व्योम *)test_function : (व्योम *)&the_var;
	पूर्णांक fd[100], cnt = 0, i;

	जबतक (1) अणु
		अगर (cnt == 100) अणु
			pr_debug("way too many debug registers, fix the test\n");
			वापस 0;
		पूर्ण
		fd[cnt] = __event(is_x, addr, &attr);

		अगर (fd[cnt] < 0)
			अवरोध;
		cnt++;
	पूर्ण

	क्रम (i = 0; i < cnt; i++)
		बंद(fd[i]);

	वापस cnt;
पूर्ण

अटल पूर्णांक detect_ioctl(व्योम)
अणु
	काष्ठा perf_event_attr attr;
	पूर्णांक fd, ret = 1;

	fd = wp_event((व्योम *) &the_var, &attr);
	अगर (fd > 0) अणु
		ret = ioctl(fd, PERF_EVENT_IOC_MODIFY_ATTRIBUTES, &attr);
		बंद(fd);
	पूर्ण

	वापस ret ? 0 : 1;
पूर्ण

अटल पूर्णांक detect_share(पूर्णांक wp_cnt, पूर्णांक bp_cnt)
अणु
	काष्ठा perf_event_attr attr;
	पूर्णांक i, fd[wp_cnt + bp_cnt], ret;

	क्रम (i = 0; i < wp_cnt; i++) अणु
		fd[i] = wp_event((व्योम *)&the_var, &attr);
		TEST_ASSERT_VAL("failed to create wp\n", fd[i] != -1);
	पूर्ण

	क्रम (; i < (bp_cnt + wp_cnt); i++) अणु
		fd[i] = bp_event((व्योम *)test_function, &attr);
		अगर (fd[i] == -1)
			अवरोध;
	पूर्ण

	ret = i != (bp_cnt + wp_cnt);

	जबतक (i--)
		बंद(fd[i]);

	वापस ret;
पूर्ण

/*
 * This test करोes following:
 *   - detects the number of watch/अवरोध-poपूर्णांकs,
 *     skip test अगर any is missing
 *   - detects PERF_EVENT_IOC_MODIFY_ATTRIBUTES ioctl,
 *     skip test अगर it's missing
 *   - detects अगर watchpoपूर्णांकs and अवरोधpoपूर्णांकs share
 *     same slots
 *   - create all possible watchpoपूर्णांकs on cpu 0
 *   - change one of it to अवरोधpoपूर्णांक
 *   - in हाल wp and bp करो not share slots,
 *     we create another watchpoपूर्णांक to ensure
 *     the slot accounting is correct
 */
पूर्णांक test__bp_accounting(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	पूर्णांक has_ioctl = detect_ioctl();
	पूर्णांक wp_cnt = detect_cnt(false);
	पूर्णांक bp_cnt = detect_cnt(true);
	पूर्णांक share  = detect_share(wp_cnt, bp_cnt);

	pr_debug("watchpoints count %d, breakpoints count %d, has_ioctl %d, share %d\n",
		 wp_cnt, bp_cnt, has_ioctl, share);

	अगर (!wp_cnt || !bp_cnt || !has_ioctl)
		वापस TEST_SKIP;

	वापस bp_accounting(wp_cnt, share);
पूर्ण

bool test__bp_account_is_supported(व्योम)
अणु
	/*
	 * PowerPC and S390 करो not support creation of inकाष्ठाion
	 * अवरोधpoपूर्णांकs using the perf_event पूर्णांकerface.
	 *
	 * Just disable the test क्रम these architectures until these
	 * issues are resolved.
	 */
#अगर defined(__घातerpc__) || defined(__s390x__)
	वापस false;
#अन्यथा
	वापस true;
#पूर्ण_अगर
पूर्ण
