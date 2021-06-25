<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __TIMENS_H__
#घोषणा __TIMENS_H__

#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <stdbool.h>

#समावेश "../kselftest.h"

#अगर_अघोषित CLONE_NEWTIME
# define CLONE_NEWTIME	0x00000080
#पूर्ण_अगर

अटल पूर्णांक config_posix_समयrs = true;
अटल पूर्णांक config_alarm_समयrs = true;

अटल अंतरभूत व्योम check_supported_समयrs(व्योम)
अणु
	काष्ठा बारpec ts;

	अगर (समयr_create(-1, 0, 0) == -1 && त्रुटि_सं == ENOSYS)
		config_posix_समयrs = false;

	अगर (घड़ी_समय_लो(CLOCK_BOOTTIME_ALARM, &ts) == -1 && त्रुटि_सं == EINVAL)
		config_alarm_समयrs = false;
पूर्ण

अटल अंतरभूत bool check_skip(पूर्णांक घड़ीid)
अणु
	अगर (!config_alarm_समयrs && घड़ीid == CLOCK_BOOTTIME_ALARM) अणु
		ksft_test_result_skip("CLOCK_BOOTTIME_ALARM isn't supported\n");
		वापस true;
	पूर्ण

	अगर (config_posix_समयrs)
		वापस false;

	चयन (घड़ीid) अणु
	/* Only these घड़ीs are supported without CONFIG_POSIX_TIMERS. */
	हाल CLOCK_BOOTTIME:
	हाल CLOCK_MONOTONIC:
	हाल CLOCK_REALTIME:
		वापस false;
	शेष:
		ksft_test_result_skip("Posix Clocks & timers are not supported\n");
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक unshare_समयns(व्योम)
अणु
	अगर (unshare(CLONE_NEWTIME)) अणु
		अगर (त्रुटि_सं == EPERM)
			ksft_निकास_skip("need to run as root\n");
		वापस pr_लिखो_त्रुटि("Can't unshare() timens");
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक _समय_रखो(घड़ीid_t clk_id, समय_प्रकार offset)
अणु
	पूर्णांक fd, len;
	अक्षर buf[4096];

	अगर (clk_id == CLOCK_MONOTONIC_COARSE || clk_id == CLOCK_MONOTONIC_RAW)
		clk_id = CLOCK_MONOTONIC;

	len = snम_लिखो(buf, माप(buf), "%d %ld 0", clk_id, offset);

	fd = खोलो("/proc/self/timens_offsets", O_WRONLY);
	अगर (fd < 0)
		वापस pr_लिखो_त्रुटि("/proc/self/timens_offsets");

	अगर (ग_लिखो(fd, buf, len) != len)
		वापस pr_लिखो_त्रुटि("/proc/self/timens_offsets");

	बंद(fd);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक _समय_लो(घड़ीid_t clk_id, काष्ठा बारpec *res, bool raw_syscall)
अणु
	पूर्णांक err;

	अगर (!raw_syscall) अणु
		अगर (घड़ी_समय_लो(clk_id, res)) अणु
			pr_लिखो_त्रुटि("clock_gettime(%d)", (पूर्णांक)clk_id);
			वापस -1;
		पूर्ण
		वापस 0;
	पूर्ण

	err = syscall(SYS_घड़ी_समय_लो, clk_id, res);
	अगर (err)
		pr_लिखो_त्रुटि("syscall(SYS_clock_gettime(%d))", (पूर्णांक)clk_id);

	वापस err;
पूर्ण

अटल अंतरभूत व्योम nscheck(व्योम)
अणु
	अगर (access("/proc/self/ns/time", F_OK) < 0)
		ksft_निकास_skip("Time namespaces are not supported\n");
पूर्ण

#पूर्ण_अगर
