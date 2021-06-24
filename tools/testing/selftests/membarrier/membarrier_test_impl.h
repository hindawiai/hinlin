<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#घोषणा _GNU_SOURCE
#समावेश <linux/membarrier.h>
#समावेश <syscall.h>
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <pthपढ़ो.h>

#समावेश "../kselftest.h"

अटल पूर्णांक sys_membarrier(पूर्णांक cmd, पूर्णांक flags)
अणु
	वापस syscall(__NR_membarrier, cmd, flags);
पूर्ण

अटल पूर्णांक test_membarrier_cmd_fail(व्योम)
अणु
	पूर्णांक cmd = -1, flags = 0;
	स्थिर अक्षर *test_name = "sys membarrier invalid command";

	अगर (sys_membarrier(cmd, flags) != -1) अणु
		ksft_निकास_fail_msg(
			"%s test: command = %d, flags = %d. Should fail, but passed\n",
			test_name, cmd, flags);
	पूर्ण
	अगर (त्रुटि_सं != EINVAL) अणु
		ksft_निकास_fail_msg(
			"%s test: flags = %d. Should return (%d: \"%s\"), but returned (%d: \"%s\").\n",
			test_name, flags, EINVAL, म_त्रुटि(EINVAL),
			त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
	पूर्ण

	ksft_test_result_pass(
		"%s test: command = %d, flags = %d, errno = %d. Failed as expected\n",
		test_name, cmd, flags, त्रुटि_सं);
	वापस 0;
पूर्ण

अटल पूर्णांक test_membarrier_flags_fail(व्योम)
अणु
	पूर्णांक cmd = MEMBARRIER_CMD_QUERY, flags = 1;
	स्थिर अक्षर *test_name = "sys membarrier MEMBARRIER_CMD_QUERY invalid flags";

	अगर (sys_membarrier(cmd, flags) != -1) अणु
		ksft_निकास_fail_msg(
			"%s test: flags = %d. Should fail, but passed\n",
			test_name, flags);
	पूर्ण
	अगर (त्रुटि_सं != EINVAL) अणु
		ksft_निकास_fail_msg(
			"%s test: flags = %d. Should return (%d: \"%s\"), but returned (%d: \"%s\").\n",
			test_name, flags, EINVAL, म_त्रुटि(EINVAL),
			त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
	पूर्ण

	ksft_test_result_pass(
		"%s test: flags = %d, errno = %d. Failed as expected\n",
		test_name, flags, त्रुटि_सं);
	वापस 0;
पूर्ण

अटल पूर्णांक test_membarrier_global_success(व्योम)
अणु
	पूर्णांक cmd = MEMBARRIER_CMD_GLOBAL, flags = 0;
	स्थिर अक्षर *test_name = "sys membarrier MEMBARRIER_CMD_GLOBAL";

	अगर (sys_membarrier(cmd, flags) != 0) अणु
		ksft_निकास_fail_msg(
			"%s test: flags = %d, errno = %d\n",
			test_name, flags, त्रुटि_सं);
	पूर्ण

	ksft_test_result_pass(
		"%s test: flags = %d\n", test_name, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक test_membarrier_निजी_expedited_fail(व्योम)
अणु
	पूर्णांक cmd = MEMBARRIER_CMD_PRIVATE_EXPEDITED, flags = 0;
	स्थिर अक्षर *test_name = "sys membarrier MEMBARRIER_CMD_PRIVATE_EXPEDITED not registered failure";

	अगर (sys_membarrier(cmd, flags) != -1) अणु
		ksft_निकास_fail_msg(
			"%s test: flags = %d. Should fail, but passed\n",
			test_name, flags);
	पूर्ण
	अगर (त्रुटि_सं != EPERM) अणु
		ksft_निकास_fail_msg(
			"%s test: flags = %d. Should return (%d: \"%s\"), but returned (%d: \"%s\").\n",
			test_name, flags, EPERM, म_त्रुटि(EPERM),
			त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
	पूर्ण

	ksft_test_result_pass(
		"%s test: flags = %d, errno = %d\n",
		test_name, flags, त्रुटि_सं);
	वापस 0;
पूर्ण

अटल पूर्णांक test_membarrier_रेजिस्टर_निजी_expedited_success(व्योम)
अणु
	पूर्णांक cmd = MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED, flags = 0;
	स्थिर अक्षर *test_name = "sys membarrier MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED";

	अगर (sys_membarrier(cmd, flags) != 0) अणु
		ksft_निकास_fail_msg(
			"%s test: flags = %d, errno = %d\n",
			test_name, flags, त्रुटि_सं);
	पूर्ण

	ksft_test_result_pass(
		"%s test: flags = %d\n",
		test_name, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक test_membarrier_निजी_expedited_success(व्योम)
अणु
	पूर्णांक cmd = MEMBARRIER_CMD_PRIVATE_EXPEDITED, flags = 0;
	स्थिर अक्षर *test_name = "sys membarrier MEMBARRIER_CMD_PRIVATE_EXPEDITED";

	अगर (sys_membarrier(cmd, flags) != 0) अणु
		ksft_निकास_fail_msg(
			"%s test: flags = %d, errno = %d\n",
			test_name, flags, त्रुटि_सं);
	पूर्ण

	ksft_test_result_pass(
		"%s test: flags = %d\n",
		test_name, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक test_membarrier_निजी_expedited_sync_core_fail(व्योम)
अणु
	पूर्णांक cmd = MEMBARRIER_CMD_PRIVATE_EXPEDITED_SYNC_CORE, flags = 0;
	स्थिर अक्षर *test_name = "sys membarrier MEMBARRIER_CMD_PRIVATE_EXPEDITED_SYNC_CORE not registered failure";

	अगर (sys_membarrier(cmd, flags) != -1) अणु
		ksft_निकास_fail_msg(
			"%s test: flags = %d. Should fail, but passed\n",
			test_name, flags);
	पूर्ण
	अगर (त्रुटि_सं != EPERM) अणु
		ksft_निकास_fail_msg(
			"%s test: flags = %d. Should return (%d: \"%s\"), but returned (%d: \"%s\").\n",
			test_name, flags, EPERM, म_त्रुटि(EPERM),
			त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
	पूर्ण

	ksft_test_result_pass(
		"%s test: flags = %d, errno = %d\n",
		test_name, flags, त्रुटि_सं);
	वापस 0;
पूर्ण

अटल पूर्णांक test_membarrier_रेजिस्टर_निजी_expedited_sync_core_success(व्योम)
अणु
	पूर्णांक cmd = MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED_SYNC_CORE, flags = 0;
	स्थिर अक्षर *test_name = "sys membarrier MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED_SYNC_CORE";

	अगर (sys_membarrier(cmd, flags) != 0) अणु
		ksft_निकास_fail_msg(
			"%s test: flags = %d, errno = %d\n",
			test_name, flags, त्रुटि_सं);
	पूर्ण

	ksft_test_result_pass(
		"%s test: flags = %d\n",
		test_name, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक test_membarrier_निजी_expedited_sync_core_success(व्योम)
अणु
	पूर्णांक cmd = MEMBARRIER_CMD_PRIVATE_EXPEDITED, flags = 0;
	स्थिर अक्षर *test_name = "sys membarrier MEMBARRIER_CMD_PRIVATE_EXPEDITED_SYNC_CORE";

	अगर (sys_membarrier(cmd, flags) != 0) अणु
		ksft_निकास_fail_msg(
			"%s test: flags = %d, errno = %d\n",
			test_name, flags, त्रुटि_सं);
	पूर्ण

	ksft_test_result_pass(
		"%s test: flags = %d\n",
		test_name, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक test_membarrier_रेजिस्टर_global_expedited_success(व्योम)
अणु
	पूर्णांक cmd = MEMBARRIER_CMD_REGISTER_GLOBAL_EXPEDITED, flags = 0;
	स्थिर अक्षर *test_name = "sys membarrier MEMBARRIER_CMD_REGISTER_GLOBAL_EXPEDITED";

	अगर (sys_membarrier(cmd, flags) != 0) अणु
		ksft_निकास_fail_msg(
			"%s test: flags = %d, errno = %d\n",
			test_name, flags, त्रुटि_सं);
	पूर्ण

	ksft_test_result_pass(
		"%s test: flags = %d\n",
		test_name, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक test_membarrier_global_expedited_success(व्योम)
अणु
	पूर्णांक cmd = MEMBARRIER_CMD_GLOBAL_EXPEDITED, flags = 0;
	स्थिर अक्षर *test_name = "sys membarrier MEMBARRIER_CMD_GLOBAL_EXPEDITED";

	अगर (sys_membarrier(cmd, flags) != 0) अणु
		ksft_निकास_fail_msg(
			"%s test: flags = %d, errno = %d\n",
			test_name, flags, त्रुटि_सं);
	पूर्ण

	ksft_test_result_pass(
		"%s test: flags = %d\n",
		test_name, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक test_membarrier_fail(व्योम)
अणु
	पूर्णांक status;

	status = test_membarrier_cmd_fail();
	अगर (status)
		वापस status;
	status = test_membarrier_flags_fail();
	अगर (status)
		वापस status;
	status = test_membarrier_निजी_expedited_fail();
	अगर (status)
		वापस status;
	status = sys_membarrier(MEMBARRIER_CMD_QUERY, 0);
	अगर (status < 0) अणु
		ksft_test_result_fail("sys_membarrier() failed\n");
		वापस status;
	पूर्ण
	अगर (status & MEMBARRIER_CMD_PRIVATE_EXPEDITED_SYNC_CORE) अणु
		status = test_membarrier_निजी_expedited_sync_core_fail();
		अगर (status)
			वापस status;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक test_membarrier_success(व्योम)
अणु
	पूर्णांक status;

	status = test_membarrier_global_success();
	अगर (status)
		वापस status;
	status = test_membarrier_रेजिस्टर_निजी_expedited_success();
	अगर (status)
		वापस status;
	status = test_membarrier_निजी_expedited_success();
	अगर (status)
		वापस status;
	status = sys_membarrier(MEMBARRIER_CMD_QUERY, 0);
	अगर (status < 0) अणु
		ksft_test_result_fail("sys_membarrier() failed\n");
		वापस status;
	पूर्ण
	अगर (status & MEMBARRIER_CMD_PRIVATE_EXPEDITED_SYNC_CORE) अणु
		status = test_membarrier_रेजिस्टर_निजी_expedited_sync_core_success();
		अगर (status)
			वापस status;
		status = test_membarrier_निजी_expedited_sync_core_success();
		अगर (status)
			वापस status;
	पूर्ण
	/*
	 * It is valid to send a global membarrier from a non-रेजिस्टरed
	 * process.
	 */
	status = test_membarrier_global_expedited_success();
	अगर (status)
		वापस status;
	status = test_membarrier_रेजिस्टर_global_expedited_success();
	अगर (status)
		वापस status;
	status = test_membarrier_global_expedited_success();
	अगर (status)
		वापस status;
	वापस 0;
पूर्ण

अटल पूर्णांक test_membarrier_query(व्योम)
अणु
	पूर्णांक flags = 0, ret;

	ret = sys_membarrier(MEMBARRIER_CMD_QUERY, flags);
	अगर (ret < 0) अणु
		अगर (त्रुटि_सं == ENOSYS) अणु
			/*
			 * It is valid to build a kernel with
			 * CONFIG_MEMBARRIER=n. However, this skips the tests.
			 */
			ksft_निकास_skip(
				"sys membarrier (CONFIG_MEMBARRIER) is disabled.\n");
		पूर्ण
		ksft_निकास_fail_msg("sys_membarrier() failed\n");
	पूर्ण
	अगर (!(ret & MEMBARRIER_CMD_GLOBAL))
		ksft_निकास_skip(
			"sys_membarrier unsupported: CMD_GLOBAL not found.\n");

	ksft_test_result_pass("sys_membarrier available\n");
	वापस 0;
पूर्ण
