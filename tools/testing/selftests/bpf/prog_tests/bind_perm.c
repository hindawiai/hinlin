<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश "bind_perm.skel.h"

#समावेश <sys/types.h>
#समावेश <sys/socket.h>
#समावेश <sys/capability.h>

अटल पूर्णांक duration;

व्योम try_bind(पूर्णांक family, पूर्णांक port, पूर्णांक expected_त्रुटि_सं)
अणु
	काष्ठा sockaddr_storage addr = अणुपूर्ण;
	काष्ठा sockaddr_in6 *sin6;
	काष्ठा sockaddr_in *sin;
	पूर्णांक fd = -1;

	fd = socket(family, SOCK_STREAM, 0);
	अगर (CHECK(fd < 0, "fd", "errno %d", त्रुटि_सं))
		जाओ बंद_socket;

	अगर (family == AF_INET) अणु
		sin = (काष्ठा sockaddr_in *)&addr;
		sin->sin_family = family;
		sin->sin_port = htons(port);
	पूर्ण अन्यथा अणु
		sin6 = (काष्ठा sockaddr_in6 *)&addr;
		sin6->sin6_family = family;
		sin6->sin6_port = htons(port);
	पूर्ण

	त्रुटि_सं = 0;
	bind(fd, (काष्ठा sockaddr *)&addr, माप(addr));
	ASSERT_EQ(त्रुटि_सं, expected_त्रुटि_सं, "bind");

बंद_socket:
	अगर (fd >= 0)
		बंद(fd);
पूर्ण

bool cap_net_bind_service(cap_flag_value_t flag)
अणु
	स्थिर cap_value_t cap_net_bind_service = CAP_NET_BIND_SERVICE;
	cap_flag_value_t original_value;
	bool was_effective = false;
	cap_t caps;

	caps = cap_get_proc();
	अगर (CHECK(!caps, "cap_get_proc", "errno %d", त्रुटि_सं))
		जाओ मुक्त_caps;

	अगर (CHECK(cap_get_flag(caps, CAP_NET_BIND_SERVICE, CAP_EFFECTIVE,
			       &original_value),
		  "cap_get_flag", "errno %d", त्रुटि_सं))
		जाओ मुक्त_caps;

	was_effective = (original_value == CAP_SET);

	अगर (CHECK(cap_set_flag(caps, CAP_EFFECTIVE, 1, &cap_net_bind_service,
			       flag),
		  "cap_set_flag", "errno %d", त्रुटि_सं))
		जाओ मुक्त_caps;

	अगर (CHECK(cap_set_proc(caps), "cap_set_proc", "errno %d", त्रुटि_सं))
		जाओ मुक्त_caps;

मुक्त_caps:
	CHECK(cap_मुक्त(caps), "cap_free", "errno %d", त्रुटि_सं);
	वापस was_effective;
पूर्ण

व्योम test_bind_perm(व्योम)
अणु
	bool cap_was_effective;
	काष्ठा bind_perm *skel;
	पूर्णांक cgroup_fd;

	cgroup_fd = test__join_cgroup("/bind_perm");
	अगर (CHECK(cgroup_fd < 0, "cg-join", "errno %d", त्रुटि_सं))
		वापस;

	skel = bind_perm__खोलो_and_load();
	अगर (!ASSERT_OK_PTR(skel, "skel"))
		जाओ बंद_cgroup_fd;

	skel->links.bind_v4_prog = bpf_program__attach_cgroup(skel->progs.bind_v4_prog, cgroup_fd);
	अगर (!ASSERT_OK_PTR(skel, "bind_v4_prog"))
		जाओ बंद_skeleton;

	skel->links.bind_v6_prog = bpf_program__attach_cgroup(skel->progs.bind_v6_prog, cgroup_fd);
	अगर (!ASSERT_OK_PTR(skel, "bind_v6_prog"))
		जाओ बंद_skeleton;

	cap_was_effective = cap_net_bind_service(CAP_CLEAR);

	try_bind(AF_INET, 110, EACCES);
	try_bind(AF_INET6, 110, EACCES);

	try_bind(AF_INET, 111, 0);
	try_bind(AF_INET6, 111, 0);

	अगर (cap_was_effective)
		cap_net_bind_service(CAP_SET);

बंद_skeleton:
	bind_perm__destroy(skel);
बंद_cgroup_fd:
	बंद(cgroup_fd);
पूर्ण
