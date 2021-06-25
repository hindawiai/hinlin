<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2017 Facebook
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <निश्चित.स>
#समावेश <sys/समय.स>

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

#समावेश "cgroup_helpers.h"
#समावेश "bpf_rlimit.h"

#घोषणा DEV_CGROUP_PROG "./dev_cgroup.o"

#घोषणा TEST_CGROUP "/test-bpf-based-device-cgroup/"

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_object *obj;
	पूर्णांक error = निकास_त्रुटि;
	पूर्णांक prog_fd, cgroup_fd;
	__u32 prog_cnt;

	अगर (bpf_prog_load(DEV_CGROUP_PROG, BPF_PROG_TYPE_CGROUP_DEVICE,
			  &obj, &prog_fd)) अणु
		म_लिखो("Failed to load DEV_CGROUP program\n");
		जाओ out;
	पूर्ण

	cgroup_fd = cgroup_setup_and_join(TEST_CGROUP);
	अगर (cgroup_fd < 0) अणु
		म_लिखो("Failed to create test cgroup\n");
		जाओ out;
	पूर्ण

	/* Attach bpf program */
	अगर (bpf_prog_attach(prog_fd, cgroup_fd, BPF_CGROUP_DEVICE, 0)) अणु
		म_लिखो("Failed to attach DEV_CGROUP program");
		जाओ err;
	पूर्ण

	अगर (bpf_prog_query(cgroup_fd, BPF_CGROUP_DEVICE, 0, शून्य, शून्य,
			   &prog_cnt)) अणु
		म_लिखो("Failed to query attached programs");
		जाओ err;
	पूर्ण

	/* All operations with /dev/zero and and /dev/uअक्रमom are allowed,
	 * everything अन्यथा is क्रमbidden.
	 */
	निश्चित(प्रणाली("rm -f /tmp/test_dev_cgroup_null") == 0);
	निश्चित(प्रणाली("mknod /tmp/test_dev_cgroup_null c 1 3"));
	निश्चित(प्रणाली("rm -f /tmp/test_dev_cgroup_null") == 0);

	/* /dev/zero is whitelisted */
	निश्चित(प्रणाली("rm -f /tmp/test_dev_cgroup_zero") == 0);
	निश्चित(प्रणाली("mknod /tmp/test_dev_cgroup_zero c 1 5") == 0);
	निश्चित(प्रणाली("rm -f /tmp/test_dev_cgroup_zero") == 0);

	निश्चित(प्रणाली("dd if=/dev/urandom of=/dev/zero count=64") == 0);

	/* src is allowed, target is क्रमbidden */
	निश्चित(प्रणाली("dd if=/dev/urandom of=/dev/full count=64"));

	/* src is क्रमbidden, target is allowed */
	निश्चित(प्रणाली("dd if=/dev/random of=/dev/zero count=64"));

	error = 0;
	म_लिखो("test_dev_cgroup:PASS\n");

err:
	cleanup_cgroup_environment();

out:
	वापस error;
पूर्ण
