<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश <uapi/linux/अगर_link.h>
#समावेश <test_progs.h>
#समावेश "test_xdp_link.skel.h"

#घोषणा IFINDEX_LO 1

व्योम test_xdp_link(व्योम)
अणु
	__u32 duration = 0, id1, id2, id0 = 0, prog_fd1, prog_fd2, err;
	DECLARE_LIBBPF_OPTS(bpf_xdp_set_link_opts, opts, .old_fd = -1);
	काष्ठा test_xdp_link *skel1 = शून्य, *skel2 = शून्य;
	काष्ठा bpf_link_info link_info;
	काष्ठा bpf_prog_info prog_info;
	काष्ठा bpf_link *link;
	__u32 link_info_len = माप(link_info);
	__u32 prog_info_len = माप(prog_info);

	skel1 = test_xdp_link__खोलो_and_load();
	अगर (CHECK(!skel1, "skel_load", "skeleton open and load failed\n"))
		जाओ cleanup;
	prog_fd1 = bpf_program__fd(skel1->progs.xdp_handler);

	skel2 = test_xdp_link__खोलो_and_load();
	अगर (CHECK(!skel2, "skel_load", "skeleton open and load failed\n"))
		जाओ cleanup;
	prog_fd2 = bpf_program__fd(skel2->progs.xdp_handler);

	स_रखो(&prog_info, 0, माप(prog_info));
	err = bpf_obj_get_info_by_fd(prog_fd1, &prog_info, &prog_info_len);
	अगर (CHECK(err, "fd_info1", "failed %d\n", -त्रुटि_सं))
		जाओ cleanup;
	id1 = prog_info.id;

	स_रखो(&prog_info, 0, माप(prog_info));
	err = bpf_obj_get_info_by_fd(prog_fd2, &prog_info, &prog_info_len);
	अगर (CHECK(err, "fd_info2", "failed %d\n", -त्रुटि_सं))
		जाओ cleanup;
	id2 = prog_info.id;

	/* set initial prog attachment */
	err = bpf_set_link_xdp_fd_opts(IFINDEX_LO, prog_fd1, XDP_FLAGS_REPLACE, &opts);
	अगर (CHECK(err, "fd_attach", "initial prog attach failed: %d\n", err))
		जाओ cleanup;

	/* validate prog ID */
	err = bpf_get_link_xdp_id(IFINDEX_LO, &id0, 0);
	CHECK(err || id0 != id1, "id1_check",
	      "loaded prog id %u != id1 %u, err %d", id0, id1, err);

	/* BPF link is not allowed to replace prog attachment */
	link = bpf_program__attach_xdp(skel1->progs.xdp_handler, IFINDEX_LO);
	अगर (CHECK(!IS_ERR(link), "link_attach_fail", "unexpected success\n")) अणु
		bpf_link__destroy(link);
		/* best-efक्रमt detach prog */
		opts.old_fd = prog_fd1;
		bpf_set_link_xdp_fd_opts(IFINDEX_LO, -1, XDP_FLAGS_REPLACE, &opts);
		जाओ cleanup;
	पूर्ण

	/* detach BPF program */
	opts.old_fd = prog_fd1;
	err = bpf_set_link_xdp_fd_opts(IFINDEX_LO, -1, XDP_FLAGS_REPLACE, &opts);
	अगर (CHECK(err, "prog_detach", "failed %d\n", err))
		जाओ cleanup;

	/* now BPF link should attach successfully */
	link = bpf_program__attach_xdp(skel1->progs.xdp_handler, IFINDEX_LO);
	अगर (CHECK(IS_ERR(link), "link_attach", "failed: %ld\n", PTR_ERR(link)))
		जाओ cleanup;
	skel1->links.xdp_handler = link;

	/* validate prog ID */
	err = bpf_get_link_xdp_id(IFINDEX_LO, &id0, 0);
	अगर (CHECK(err || id0 != id1, "id1_check",
		  "loaded prog id %u != id1 %u, err %d", id0, id1, err))
		जाओ cleanup;

	/* BPF prog attach is not allowed to replace BPF link */
	opts.old_fd = prog_fd1;
	err = bpf_set_link_xdp_fd_opts(IFINDEX_LO, prog_fd2, XDP_FLAGS_REPLACE, &opts);
	अगर (CHECK(!err, "prog_attach_fail", "unexpected success\n"))
		जाओ cleanup;

	/* Can't क्रमce-update when BPF link is active */
	err = bpf_set_link_xdp_fd(IFINDEX_LO, prog_fd2, 0);
	अगर (CHECK(!err, "prog_update_fail", "unexpected success\n"))
		जाओ cleanup;

	/* Can't क्रमce-detach when BPF link is active */
	err = bpf_set_link_xdp_fd(IFINDEX_LO, -1, 0);
	अगर (CHECK(!err, "prog_detach_fail", "unexpected success\n"))
		जाओ cleanup;

	/* BPF link is not allowed to replace another BPF link */
	link = bpf_program__attach_xdp(skel2->progs.xdp_handler, IFINDEX_LO);
	अगर (CHECK(!IS_ERR(link), "link_attach_fail", "unexpected success\n")) अणु
		bpf_link__destroy(link);
		जाओ cleanup;
	पूर्ण

	bpf_link__destroy(skel1->links.xdp_handler);
	skel1->links.xdp_handler = शून्य;

	/* new link attach should succeed */
	link = bpf_program__attach_xdp(skel2->progs.xdp_handler, IFINDEX_LO);
	अगर (CHECK(IS_ERR(link), "link_attach", "failed: %ld\n", PTR_ERR(link)))
		जाओ cleanup;
	skel2->links.xdp_handler = link;

	err = bpf_get_link_xdp_id(IFINDEX_LO, &id0, 0);
	अगर (CHECK(err || id0 != id2, "id2_check",
		  "loaded prog id %u != id2 %u, err %d", id0, id1, err))
		जाओ cleanup;

	/* updating program under active BPF link works as expected */
	err = bpf_link__update_program(link, skel1->progs.xdp_handler);
	अगर (CHECK(err, "link_upd", "failed: %d\n", err))
		जाओ cleanup;

	स_रखो(&link_info, 0, माप(link_info));
	err = bpf_obj_get_info_by_fd(bpf_link__fd(link), &link_info, &link_info_len);
	अगर (CHECK(err, "link_info", "failed: %d\n", err))
		जाओ cleanup;

	CHECK(link_info.type != BPF_LINK_TYPE_XDP, "link_type",
	      "got %u != exp %u\n", link_info.type, BPF_LINK_TYPE_XDP);
	CHECK(link_info.prog_id != id1, "link_prog_id",
	      "got %u != exp %u\n", link_info.prog_id, id1);
	CHECK(link_info.xdp.अगरindex != IFINDEX_LO, "link_ifindex",
	      "got %u != exp %u\n", link_info.xdp.अगरindex, IFINDEX_LO);

	err = bpf_link__detach(link);
	अगर (CHECK(err, "link_detach", "failed %d\n", err))
		जाओ cleanup;

	स_रखो(&link_info, 0, माप(link_info));
	err = bpf_obj_get_info_by_fd(bpf_link__fd(link), &link_info, &link_info_len);
	अगर (CHECK(err, "link_info", "failed: %d\n", err))
		जाओ cleanup;
	CHECK(link_info.prog_id != id1, "link_prog_id",
	      "got %u != exp %u\n", link_info.prog_id, id1);
	/* अगरindex should be zeroed out */
	CHECK(link_info.xdp.अगरindex != 0, "link_ifindex",
	      "got %u != exp %u\n", link_info.xdp.अगरindex, 0);

cleanup:
	test_xdp_link__destroy(skel1);
	test_xdp_link__destroy(skel2);
पूर्ण
