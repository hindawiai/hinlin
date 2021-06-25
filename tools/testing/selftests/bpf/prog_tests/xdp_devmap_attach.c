<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <uapi/linux/bpf.h>
#समावेश <linux/अगर_link.h>
#समावेश <test_progs.h>

#समावेश "test_xdp_devmap_helpers.skel.h"
#समावेश "test_xdp_with_devmap_helpers.skel.h"

#घोषणा IFINDEX_LO 1

व्योम test_xdp_with_devmap_helpers(व्योम)
अणु
	काष्ठा test_xdp_with_devmap_helpers *skel;
	काष्ठा bpf_prog_info info = अणुपूर्ण;
	काष्ठा bpf_devmap_val val = अणु
		.अगरindex = IFINDEX_LO,
	पूर्ण;
	__u32 len = माप(info);
	__u32 duration = 0, idx = 0;
	पूर्णांक err, dm_fd, map_fd;


	skel = test_xdp_with_devmap_helpers__खोलो_and_load();
	अगर (CHECK_FAIL(!skel)) अणु
		लिखो_त्रुटि("test_xdp_with_devmap_helpers__open_and_load");
		वापस;
	पूर्ण

	/* can not attach program with DEVMAPs that allow programs
	 * as xdp generic
	 */
	dm_fd = bpf_program__fd(skel->progs.xdp_redir_prog);
	err = bpf_set_link_xdp_fd(IFINDEX_LO, dm_fd, XDP_FLAGS_SKB_MODE);
	CHECK(err == 0, "Generic attach of program with 8-byte devmap",
	      "should have failed\n");

	dm_fd = bpf_program__fd(skel->progs.xdp_dummy_dm);
	map_fd = bpf_map__fd(skel->maps.dm_ports);
	err = bpf_obj_get_info_by_fd(dm_fd, &info, &len);
	अगर (CHECK_FAIL(err))
		जाओ out_बंद;

	val.bpf_prog.fd = dm_fd;
	err = bpf_map_update_elem(map_fd, &idx, &val, 0);
	CHECK(err, "Add program to devmap entry",
	      "err %d errno %d\n", err, त्रुटि_सं);

	err = bpf_map_lookup_elem(map_fd, &idx, &val);
	CHECK(err, "Read devmap entry", "err %d errno %d\n", err, त्रुटि_सं);
	CHECK(info.id != val.bpf_prog.id, "Expected program id in devmap entry",
	      "expected %u read %u\n", info.id, val.bpf_prog.id);

	/* can not attach BPF_XDP_DEVMAP program to a device */
	err = bpf_set_link_xdp_fd(IFINDEX_LO, dm_fd, XDP_FLAGS_SKB_MODE);
	CHECK(err == 0, "Attach of BPF_XDP_DEVMAP program",
	      "should have failed\n");

	val.अगरindex = 1;
	val.bpf_prog.fd = bpf_program__fd(skel->progs.xdp_dummy_prog);
	err = bpf_map_update_elem(map_fd, &idx, &val, 0);
	CHECK(err == 0, "Add non-BPF_XDP_DEVMAP program to devmap entry",
	      "should have failed\n");

out_बंद:
	test_xdp_with_devmap_helpers__destroy(skel);
पूर्ण

व्योम test_neg_xdp_devmap_helpers(व्योम)
अणु
	काष्ठा test_xdp_devmap_helpers *skel;
	__u32 duration = 0;

	skel = test_xdp_devmap_helpers__खोलो_and_load();
	अगर (CHECK(skel,
		  "Load of XDP program accessing egress ifindex without attach type",
		  "should have failed\n")) अणु
		test_xdp_devmap_helpers__destroy(skel);
	पूर्ण
पूर्ण


व्योम test_xdp_devmap_attach(व्योम)
अणु
	अगर (test__start_subtest("DEVMAP with programs in entries"))
		test_xdp_with_devmap_helpers();

	अगर (test__start_subtest("Verifier check of DEVMAP programs"))
		test_neg_xdp_devmap_helpers();
पूर्ण
