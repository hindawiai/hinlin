<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <uapi/linux/bpf.h>
#समावेश <linux/अगर_link.h>
#समावेश <test_progs.h>

#समावेश "test_xdp_with_cpumap_helpers.skel.h"

#घोषणा IFINDEX_LO	1

व्योम test_xdp_with_cpumap_helpers(व्योम)
अणु
	काष्ठा test_xdp_with_cpumap_helpers *skel;
	काष्ठा bpf_prog_info info = अणुपूर्ण;
	काष्ठा bpf_cpumap_val val = अणु
		.qsize = 192,
	पूर्ण;
	__u32 duration = 0, idx = 0;
	__u32 len = माप(info);
	पूर्णांक err, prog_fd, map_fd;

	skel = test_xdp_with_cpumap_helpers__खोलो_and_load();
	अगर (CHECK_FAIL(!skel)) अणु
		लिखो_त्रुटि("test_xdp_with_cpumap_helpers__open_and_load");
		वापस;
	पूर्ण

	/* can not attach program with cpumaps that allow programs
	 * as xdp generic
	 */
	prog_fd = bpf_program__fd(skel->progs.xdp_redir_prog);
	err = bpf_set_link_xdp_fd(IFINDEX_LO, prog_fd, XDP_FLAGS_SKB_MODE);
	CHECK(err == 0, "Generic attach of program with 8-byte CPUMAP",
	      "should have failed\n");

	prog_fd = bpf_program__fd(skel->progs.xdp_dummy_cm);
	map_fd = bpf_map__fd(skel->maps.cpu_map);
	err = bpf_obj_get_info_by_fd(prog_fd, &info, &len);
	अगर (CHECK_FAIL(err))
		जाओ out_बंद;

	val.bpf_prog.fd = prog_fd;
	err = bpf_map_update_elem(map_fd, &idx, &val, 0);
	CHECK(err, "Add program to cpumap entry", "err %d errno %d\n",
	      err, त्रुटि_सं);

	err = bpf_map_lookup_elem(map_fd, &idx, &val);
	CHECK(err, "Read cpumap entry", "err %d errno %d\n", err, त्रुटि_सं);
	CHECK(info.id != val.bpf_prog.id, "Expected program id in cpumap entry",
	      "expected %u read %u\n", info.id, val.bpf_prog.id);

	/* can not attach BPF_XDP_CPUMAP program to a device */
	err = bpf_set_link_xdp_fd(IFINDEX_LO, prog_fd, XDP_FLAGS_SKB_MODE);
	CHECK(err == 0, "Attach of BPF_XDP_CPUMAP program",
	      "should have failed\n");

	val.qsize = 192;
	val.bpf_prog.fd = bpf_program__fd(skel->progs.xdp_dummy_prog);
	err = bpf_map_update_elem(map_fd, &idx, &val, 0);
	CHECK(err == 0, "Add non-BPF_XDP_CPUMAP program to cpumap entry",
	      "should have failed\n");

out_बंद:
	test_xdp_with_cpumap_helpers__destroy(skel);
पूर्ण

व्योम test_xdp_cpumap_attach(व्योम)
अणु
	अगर (test__start_subtest("cpumap_with_progs"))
		test_xdp_with_cpumap_helpers();
पूर्ण
