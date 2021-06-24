<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश "udp_limit.skel.h"

#समावेश <sys/types.h>
#समावेश <sys/socket.h>

अटल पूर्णांक duration;

व्योम test_udp_limit(व्योम)
अणु
	काष्ठा udp_limit *skel;
	पूर्णांक fd1 = -1, fd2 = -1;
	पूर्णांक cgroup_fd;

	cgroup_fd = test__join_cgroup("/udp_limit");
	अगर (CHECK(cgroup_fd < 0, "cg-join", "errno %d", त्रुटि_सं))
		वापस;

	skel = udp_limit__खोलो_and_load();
	अगर (CHECK(!skel, "skel-load", "errno %d", त्रुटि_सं))
		जाओ बंद_cgroup_fd;

	skel->links.sock = bpf_program__attach_cgroup(skel->progs.sock, cgroup_fd);
	skel->links.sock_release = bpf_program__attach_cgroup(skel->progs.sock_release, cgroup_fd);
	अगर (CHECK(IS_ERR(skel->links.sock) || IS_ERR(skel->links.sock_release),
		  "cg-attach", "sock %ld sock_release %ld",
		  PTR_ERR(skel->links.sock),
		  PTR_ERR(skel->links.sock_release)))
		जाओ बंद_skeleton;

	/* BPF program enक्रमces a single UDP socket per cgroup,
	 * verअगरy that.
	 */
	fd1 = socket(AF_INET, SOCK_DGRAM, 0);
	अगर (CHECK(fd1 < 0, "fd1", "errno %d", त्रुटि_सं))
		जाओ बंद_skeleton;

	fd2 = socket(AF_INET, SOCK_DGRAM, 0);
	अगर (CHECK(fd2 >= 0, "fd2", "errno %d", त्रुटि_सं))
		जाओ बंद_skeleton;

	/* We can reखोलो again after बंद. */
	बंद(fd1);
	fd1 = -1;

	fd1 = socket(AF_INET, SOCK_DGRAM, 0);
	अगर (CHECK(fd1 < 0, "fd1-again", "errno %d", त्रुटि_सं))
		जाओ बंद_skeleton;

	/* Make sure the program was invoked the expected
	 * number of बार:
	 * - खोलो fd1           - BPF_CGROUP_INET_SOCK_CREATE
	 * - attempt to खोलोfd2 - BPF_CGROUP_INET_SOCK_CREATE
	 * - बंद fd1          - BPF_CGROUP_INET_SOCK_RELEASE
	 * - खोलो fd1 again     - BPF_CGROUP_INET_SOCK_CREATE
	 */
	अगर (CHECK(skel->bss->invocations != 4, "bss-invocations",
		  "invocations=%d", skel->bss->invocations))
		जाओ बंद_skeleton;

	/* We should still have a single socket in use */
	अगर (CHECK(skel->bss->in_use != 1, "bss-in_use",
		  "in_use=%d", skel->bss->in_use))
		जाओ बंद_skeleton;

बंद_skeleton:
	अगर (fd1 >= 0)
		बंद(fd1);
	अगर (fd2 >= 0)
		बंद(fd2);
	udp_limit__destroy(skel);
बंद_cgroup_fd:
	बंद(cgroup_fd);
पूर्ण
