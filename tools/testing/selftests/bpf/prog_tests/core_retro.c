<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Facebook
#घोषणा _GNU_SOURCE
#समावेश <test_progs.h>
#समावेश "test_core_retro.skel.h"

व्योम test_core_retro(व्योम)
अणु
	पूर्णांक err, zero = 0, res, duration = 0, my_pid = getpid();
	काष्ठा test_core_retro *skel;

	/* load program */
	skel = test_core_retro__खोलो_and_load();
	अगर (CHECK(!skel, "skel_load", "skeleton open/load failed\n"))
		जाओ out_बंद;

	err = bpf_map_update_elem(bpf_map__fd(skel->maps.exp_tgid_map), &zero, &my_pid, 0);
	अगर (CHECK(err, "map_update", "failed to set expected PID: %d\n", त्रुटि_सं))
		जाओ out_बंद;

	/* attach probe */
	err = test_core_retro__attach(skel);
	अगर (CHECK(err, "attach_kprobe", "err %d\n", err))
		जाओ out_बंद;

	/* trigger */
	usleep(1);

	err = bpf_map_lookup_elem(bpf_map__fd(skel->maps.results), &zero, &res);
	अगर (CHECK(err, "map_lookup", "failed to lookup result: %d\n", त्रुटि_सं))
		जाओ out_बंद;

	CHECK(res != my_pid, "pid_check", "got %d != exp %d\n", res, my_pid);

out_बंद:
	test_core_retro__destroy(skel);
पूर्ण
