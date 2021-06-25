<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Tests क्रम attaching, detaching, and replacing flow_dissector BPF program.
 */

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <sched.h>
#समावेश <stdbool.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf.h>

#समावेश "test_progs.h"

अटल पूर्णांक init_net = -1;

अटल __u32 query_attached_prog_id(पूर्णांक netns)
अणु
	__u32 prog_ids[1] = अणुपूर्ण;
	__u32 prog_cnt = ARRAY_SIZE(prog_ids);
	पूर्णांक err;

	err = bpf_prog_query(netns, BPF_FLOW_DISSECTOR, 0, शून्य,
			     prog_ids, &prog_cnt);
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("bpf_prog_query");
		वापस 0;
	पूर्ण

	वापस prog_cnt == 1 ? prog_ids[0] : 0;
पूर्ण

अटल bool prog_is_attached(पूर्णांक netns)
अणु
	वापस query_attached_prog_id(netns) > 0;
पूर्ण

अटल पूर्णांक load_prog(क्रमागत bpf_prog_type type)
अणु
	काष्ठा bpf_insn prog[] = अणु
		BPF_MOV64_IMM(BPF_REG_0, BPF_OK),
		BPF_EXIT_INSN(),
	पूर्ण;
	पूर्णांक fd;

	fd = bpf_load_program(type, prog, ARRAY_SIZE(prog), "GPL", 0, शून्य, 0);
	अगर (CHECK_FAIL(fd < 0))
		लिखो_त्रुटि("bpf_load_program");

	वापस fd;
पूर्ण

अटल __u32 query_prog_id(पूर्णांक prog)
अणु
	काष्ठा bpf_prog_info info = अणुपूर्ण;
	__u32 info_len = माप(info);
	पूर्णांक err;

	err = bpf_obj_get_info_by_fd(prog, &info, &info_len);
	अगर (CHECK_FAIL(err || info_len != माप(info))) अणु
		लिखो_त्रुटि("bpf_obj_get_info_by_fd");
		वापस 0;
	पूर्ण

	वापस info.id;
पूर्ण

अटल पूर्णांक unshare_net(पूर्णांक old_net)
अणु
	पूर्णांक err, new_net;

	err = unshare(CLONE_NEWNET);
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("unshare(CLONE_NEWNET)");
		वापस -1;
	पूर्ण
	new_net = खोलो("/proc/self/ns/net", O_RDONLY);
	अगर (CHECK_FAIL(new_net < 0)) अणु
		लिखो_त्रुटि("open(/proc/self/ns/net)");
		setns(old_net, CLONE_NEWNET);
		वापस -1;
	पूर्ण
	वापस new_net;
पूर्ण

अटल व्योम test_prog_attach_prog_attach(पूर्णांक netns, पूर्णांक prog1, पूर्णांक prog2)
अणु
	पूर्णांक err;

	err = bpf_prog_attach(prog1, 0, BPF_FLOW_DISSECTOR, 0);
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("bpf_prog_attach(prog1)");
		वापस;
	पूर्ण
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog1));

	/* Expect success when attaching a dअगरferent program */
	err = bpf_prog_attach(prog2, 0, BPF_FLOW_DISSECTOR, 0);
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("bpf_prog_attach(prog2) #1");
		जाओ out_detach;
	पूर्ण
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog2));

	/* Expect failure when attaching the same program twice */
	err = bpf_prog_attach(prog2, 0, BPF_FLOW_DISSECTOR, 0);
	अगर (CHECK_FAIL(!err || त्रुटि_सं != EINVAL))
		लिखो_त्रुटि("bpf_prog_attach(prog2) #2");
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog2));

out_detach:
	err = bpf_prog_detach2(prog2, 0, BPF_FLOW_DISSECTOR);
	अगर (CHECK_FAIL(err))
		लिखो_त्रुटि("bpf_prog_detach");
	CHECK_FAIL(prog_is_attached(netns));
पूर्ण

अटल व्योम test_link_create_link_create(पूर्णांक netns, पूर्णांक prog1, पूर्णांक prog2)
अणु
	DECLARE_LIBBPF_OPTS(bpf_link_create_opts, opts);
	पूर्णांक link1, link2;

	link1 = bpf_link_create(prog1, netns, BPF_FLOW_DISSECTOR, &opts);
	अगर (CHECK_FAIL(link < 0)) अणु
		लिखो_त्रुटि("bpf_link_create(prog1)");
		वापस;
	पूर्ण
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog1));

	/* Expect failure creating link when another link exists */
	त्रुटि_सं = 0;
	link2 = bpf_link_create(prog2, netns, BPF_FLOW_DISSECTOR, &opts);
	अगर (CHECK_FAIL(link2 != -1 || त्रुटि_सं != E2BIG))
		लिखो_त्रुटि("bpf_prog_attach(prog2) expected E2BIG");
	अगर (link2 != -1)
		बंद(link2);
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog1));

	बंद(link1);
	CHECK_FAIL(prog_is_attached(netns));
पूर्ण

अटल व्योम test_prog_attach_link_create(पूर्णांक netns, पूर्णांक prog1, पूर्णांक prog2)
अणु
	DECLARE_LIBBPF_OPTS(bpf_link_create_opts, opts);
	पूर्णांक err, link;

	err = bpf_prog_attach(prog1, 0, BPF_FLOW_DISSECTOR, 0);
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("bpf_prog_attach(prog1)");
		वापस;
	पूर्ण
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog1));

	/* Expect failure creating link when prog attached */
	त्रुटि_सं = 0;
	link = bpf_link_create(prog2, netns, BPF_FLOW_DISSECTOR, &opts);
	अगर (CHECK_FAIL(link != -1 || त्रुटि_सं != EEXIST))
		लिखो_त्रुटि("bpf_link_create(prog2) expected EEXIST");
	अगर (link != -1)
		बंद(link);
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog1));

	err = bpf_prog_detach2(prog1, 0, BPF_FLOW_DISSECTOR);
	अगर (CHECK_FAIL(err))
		लिखो_त्रुटि("bpf_prog_detach");
	CHECK_FAIL(prog_is_attached(netns));
पूर्ण

अटल व्योम test_link_create_prog_attach(पूर्णांक netns, पूर्णांक prog1, पूर्णांक prog2)
अणु
	DECLARE_LIBBPF_OPTS(bpf_link_create_opts, opts);
	पूर्णांक err, link;

	link = bpf_link_create(prog1, netns, BPF_FLOW_DISSECTOR, &opts);
	अगर (CHECK_FAIL(link < 0)) अणु
		लिखो_त्रुटि("bpf_link_create(prog1)");
		वापस;
	पूर्ण
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog1));

	/* Expect failure attaching prog when link exists */
	त्रुटि_सं = 0;
	err = bpf_prog_attach(prog2, 0, BPF_FLOW_DISSECTOR, 0);
	अगर (CHECK_FAIL(!err || त्रुटि_सं != EEXIST))
		लिखो_त्रुटि("bpf_prog_attach(prog2) expected EEXIST");
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog1));

	बंद(link);
	CHECK_FAIL(prog_is_attached(netns));
पूर्ण

अटल व्योम test_link_create_prog_detach(पूर्णांक netns, पूर्णांक prog1, पूर्णांक prog2)
अणु
	DECLARE_LIBBPF_OPTS(bpf_link_create_opts, opts);
	पूर्णांक err, link;

	link = bpf_link_create(prog1, netns, BPF_FLOW_DISSECTOR, &opts);
	अगर (CHECK_FAIL(link < 0)) अणु
		लिखो_त्रुटि("bpf_link_create(prog1)");
		वापस;
	पूर्ण
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog1));

	/* Expect failure detaching prog when link exists */
	त्रुटि_सं = 0;
	err = bpf_prog_detach2(prog1, 0, BPF_FLOW_DISSECTOR);
	अगर (CHECK_FAIL(!err || त्रुटि_सं != EINVAL))
		लिखो_त्रुटि("bpf_prog_detach expected EINVAL");
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog1));

	बंद(link);
	CHECK_FAIL(prog_is_attached(netns));
पूर्ण

अटल व्योम test_prog_attach_detach_query(पूर्णांक netns, पूर्णांक prog1, पूर्णांक prog2)
अणु
	पूर्णांक err;

	err = bpf_prog_attach(prog1, 0, BPF_FLOW_DISSECTOR, 0);
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("bpf_prog_attach(prog1)");
		वापस;
	पूर्ण
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog1));

	err = bpf_prog_detach2(prog1, 0, BPF_FLOW_DISSECTOR);
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("bpf_prog_detach");
		वापस;
	पूर्ण

	/* Expect no prog attached after successful detach */
	CHECK_FAIL(prog_is_attached(netns));
पूर्ण

अटल व्योम test_link_create_बंद_query(पूर्णांक netns, पूर्णांक prog1, पूर्णांक prog2)
अणु
	DECLARE_LIBBPF_OPTS(bpf_link_create_opts, opts);
	पूर्णांक link;

	link = bpf_link_create(prog1, netns, BPF_FLOW_DISSECTOR, &opts);
	अगर (CHECK_FAIL(link < 0)) अणु
		लिखो_त्रुटि("bpf_link_create(prog1)");
		वापस;
	पूर्ण
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog1));

	बंद(link);
	/* Expect no prog attached after closing last link FD */
	CHECK_FAIL(prog_is_attached(netns));
पूर्ण

अटल व्योम test_link_update_no_old_prog(पूर्णांक netns, पूर्णांक prog1, पूर्णांक prog2)
अणु
	DECLARE_LIBBPF_OPTS(bpf_link_create_opts, create_opts);
	DECLARE_LIBBPF_OPTS(bpf_link_update_opts, update_opts);
	पूर्णांक err, link;

	link = bpf_link_create(prog1, netns, BPF_FLOW_DISSECTOR, &create_opts);
	अगर (CHECK_FAIL(link < 0)) अणु
		लिखो_त्रुटि("bpf_link_create(prog1)");
		वापस;
	पूर्ण
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog1));

	/* Expect success replacing the prog when old prog not specअगरied */
	update_opts.flags = 0;
	update_opts.old_prog_fd = 0;
	err = bpf_link_update(link, prog2, &update_opts);
	अगर (CHECK_FAIL(err))
		लिखो_त्रुटि("bpf_link_update");
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog2));

	बंद(link);
	CHECK_FAIL(prog_is_attached(netns));
पूर्ण

अटल व्योम test_link_update_replace_old_prog(पूर्णांक netns, पूर्णांक prog1, पूर्णांक prog2)
अणु
	DECLARE_LIBBPF_OPTS(bpf_link_create_opts, create_opts);
	DECLARE_LIBBPF_OPTS(bpf_link_update_opts, update_opts);
	पूर्णांक err, link;

	link = bpf_link_create(prog1, netns, BPF_FLOW_DISSECTOR, &create_opts);
	अगर (CHECK_FAIL(link < 0)) अणु
		लिखो_त्रुटि("bpf_link_create(prog1)");
		वापस;
	पूर्ण
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog1));

	/* Expect success F_REPLACE and old prog specअगरied to succeed */
	update_opts.flags = BPF_F_REPLACE;
	update_opts.old_prog_fd = prog1;
	err = bpf_link_update(link, prog2, &update_opts);
	अगर (CHECK_FAIL(err))
		लिखो_त्रुटि("bpf_link_update");
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog2));

	बंद(link);
	CHECK_FAIL(prog_is_attached(netns));
पूर्ण

अटल व्योम test_link_update_same_prog(पूर्णांक netns, पूर्णांक prog1, पूर्णांक prog2)
अणु
	DECLARE_LIBBPF_OPTS(bpf_link_create_opts, create_opts);
	DECLARE_LIBBPF_OPTS(bpf_link_update_opts, update_opts);
	पूर्णांक err, link;

	link = bpf_link_create(prog1, netns, BPF_FLOW_DISSECTOR, &create_opts);
	अगर (CHECK_FAIL(link < 0)) अणु
		लिखो_त्रुटि("bpf_link_create(prog1)");
		वापस;
	पूर्ण
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog1));

	/* Expect success updating the prog with the same one */
	update_opts.flags = 0;
	update_opts.old_prog_fd = 0;
	err = bpf_link_update(link, prog1, &update_opts);
	अगर (CHECK_FAIL(err))
		लिखो_त्रुटि("bpf_link_update");
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog1));

	बंद(link);
	CHECK_FAIL(prog_is_attached(netns));
पूर्ण

अटल व्योम test_link_update_invalid_opts(पूर्णांक netns, पूर्णांक prog1, पूर्णांक prog2)
अणु
	DECLARE_LIBBPF_OPTS(bpf_link_create_opts, create_opts);
	DECLARE_LIBBPF_OPTS(bpf_link_update_opts, update_opts);
	पूर्णांक err, link;

	link = bpf_link_create(prog1, netns, BPF_FLOW_DISSECTOR, &create_opts);
	अगर (CHECK_FAIL(link < 0)) अणु
		लिखो_त्रुटि("bpf_link_create(prog1)");
		वापस;
	पूर्ण
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog1));

	/* Expect update to fail w/ old prog FD but w/o F_REPLACE*/
	त्रुटि_सं = 0;
	update_opts.flags = 0;
	update_opts.old_prog_fd = prog1;
	err = bpf_link_update(link, prog2, &update_opts);
	अगर (CHECK_FAIL(!err || त्रुटि_सं != EINVAL)) अणु
		लिखो_त्रुटि("bpf_link_update expected EINVAL");
		जाओ out_बंद;
	पूर्ण
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog1));

	/* Expect update to fail on old prog FD mismatch */
	त्रुटि_सं = 0;
	update_opts.flags = BPF_F_REPLACE;
	update_opts.old_prog_fd = prog2;
	err = bpf_link_update(link, prog2, &update_opts);
	अगर (CHECK_FAIL(!err || त्रुटि_सं != EPERM)) अणु
		लिखो_त्रुटि("bpf_link_update expected EPERM");
		जाओ out_बंद;
	पूर्ण
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog1));

	/* Expect update to fail क्रम invalid old prog FD */
	त्रुटि_सं = 0;
	update_opts.flags = BPF_F_REPLACE;
	update_opts.old_prog_fd = -1;
	err = bpf_link_update(link, prog2, &update_opts);
	अगर (CHECK_FAIL(!err || त्रुटि_सं != EBADF)) अणु
		लिखो_त्रुटि("bpf_link_update expected EBADF");
		जाओ out_बंद;
	पूर्ण
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog1));

	/* Expect update to fail with invalid flags */
	त्रुटि_सं = 0;
	update_opts.flags = BPF_F_ALLOW_MULTI;
	update_opts.old_prog_fd = 0;
	err = bpf_link_update(link, prog2, &update_opts);
	अगर (CHECK_FAIL(!err || त्रुटि_सं != EINVAL))
		लिखो_त्रुटि("bpf_link_update expected EINVAL");
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog1));

out_बंद:
	बंद(link);
	CHECK_FAIL(prog_is_attached(netns));
पूर्ण

अटल व्योम test_link_update_invalid_prog(पूर्णांक netns, पूर्णांक prog1, पूर्णांक prog2)
अणु
	DECLARE_LIBBPF_OPTS(bpf_link_create_opts, create_opts);
	DECLARE_LIBBPF_OPTS(bpf_link_update_opts, update_opts);
	पूर्णांक err, link, prog3;

	link = bpf_link_create(prog1, netns, BPF_FLOW_DISSECTOR, &create_opts);
	अगर (CHECK_FAIL(link < 0)) अणु
		लिखो_त्रुटि("bpf_link_create(prog1)");
		वापस;
	पूर्ण
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog1));

	/* Expect failure when new prog FD is not valid */
	त्रुटि_सं = 0;
	update_opts.flags = 0;
	update_opts.old_prog_fd = 0;
	err = bpf_link_update(link, -1, &update_opts);
	अगर (CHECK_FAIL(!err || त्रुटि_सं != EBADF)) अणु
		लिखो_त्रुटि("bpf_link_update expected EINVAL");
		जाओ out_बंद_link;
	पूर्ण
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog1));

	prog3 = load_prog(BPF_PROG_TYPE_SOCKET_FILTER);
	अगर (prog3 < 0)
		जाओ out_बंद_link;

	/* Expect failure when new prog FD type करोesn't match */
	त्रुटि_सं = 0;
	update_opts.flags = 0;
	update_opts.old_prog_fd = 0;
	err = bpf_link_update(link, prog3, &update_opts);
	अगर (CHECK_FAIL(!err || त्रुटि_सं != EINVAL))
		लिखो_त्रुटि("bpf_link_update expected EINVAL");
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog1));

	बंद(prog3);
out_बंद_link:
	बंद(link);
	CHECK_FAIL(prog_is_attached(netns));
पूर्ण

अटल व्योम test_link_update_netns_gone(पूर्णांक netns, पूर्णांक prog1, पूर्णांक prog2)
अणु
	DECLARE_LIBBPF_OPTS(bpf_link_create_opts, create_opts);
	DECLARE_LIBBPF_OPTS(bpf_link_update_opts, update_opts);
	पूर्णांक err, link, old_net;

	old_net = netns;
	netns = unshare_net(old_net);
	अगर (netns < 0)
		वापस;

	link = bpf_link_create(prog1, netns, BPF_FLOW_DISSECTOR, &create_opts);
	अगर (CHECK_FAIL(link < 0)) अणु
		लिखो_त्रुटि("bpf_link_create(prog1)");
		वापस;
	पूर्ण
	CHECK_FAIL(query_attached_prog_id(netns) != query_prog_id(prog1));

	बंद(netns);
	err = setns(old_net, CLONE_NEWNET);
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("setns(CLONE_NEWNET)");
		बंद(link);
		वापस;
	पूर्ण

	/* Expect failure when netns destroyed */
	त्रुटि_सं = 0;
	update_opts.flags = 0;
	update_opts.old_prog_fd = 0;
	err = bpf_link_update(link, prog2, &update_opts);
	अगर (CHECK_FAIL(!err || त्रुटि_सं != ENOLINK))
		लिखो_त्रुटि("bpf_link_update");

	बंद(link);
पूर्ण

अटल व्योम test_link_get_info(पूर्णांक netns, पूर्णांक prog1, पूर्णांक prog2)
अणु
	DECLARE_LIBBPF_OPTS(bpf_link_create_opts, create_opts);
	DECLARE_LIBBPF_OPTS(bpf_link_update_opts, update_opts);
	काष्ठा bpf_link_info info = अणुपूर्ण;
	काष्ठा stat netns_stat = अणुपूर्ण;
	__u32 info_len, link_id;
	पूर्णांक err, link, old_net;

	old_net = netns;
	netns = unshare_net(old_net);
	अगर (netns < 0)
		वापस;

	err = ख_स्थिति(netns, &netns_stat);
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("stat(netns)");
		जाओ out_resetns;
	पूर्ण

	link = bpf_link_create(prog1, netns, BPF_FLOW_DISSECTOR, &create_opts);
	अगर (CHECK_FAIL(link < 0)) अणु
		लिखो_त्रुटि("bpf_link_create(prog1)");
		जाओ out_resetns;
	पूर्ण

	info_len = माप(info);
	err = bpf_obj_get_info_by_fd(link, &info, &info_len);
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("bpf_obj_get_info");
		जाओ out_unlink;
	पूर्ण
	CHECK_FAIL(info_len != माप(info));

	/* Expect link info to be sane and match prog and netns details */
	CHECK_FAIL(info.type != BPF_LINK_TYPE_NETNS);
	CHECK_FAIL(info.id == 0);
	CHECK_FAIL(info.prog_id != query_prog_id(prog1));
	CHECK_FAIL(info.netns.netns_ino != netns_stat.st_ino);
	CHECK_FAIL(info.netns.attach_type != BPF_FLOW_DISSECTOR);

	update_opts.flags = 0;
	update_opts.old_prog_fd = 0;
	err = bpf_link_update(link, prog2, &update_opts);
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("bpf_link_update(prog2)");
		जाओ out_unlink;
	पूर्ण

	link_id = info.id;
	info_len = माप(info);
	err = bpf_obj_get_info_by_fd(link, &info, &info_len);
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("bpf_obj_get_info");
		जाओ out_unlink;
	पूर्ण
	CHECK_FAIL(info_len != माप(info));

	/* Expect no info change after update except in prog id */
	CHECK_FAIL(info.type != BPF_LINK_TYPE_NETNS);
	CHECK_FAIL(info.id != link_id);
	CHECK_FAIL(info.prog_id != query_prog_id(prog2));
	CHECK_FAIL(info.netns.netns_ino != netns_stat.st_ino);
	CHECK_FAIL(info.netns.attach_type != BPF_FLOW_DISSECTOR);

	/* Leave netns link is attached to and बंद last FD to it */
	err = setns(old_net, CLONE_NEWNET);
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("setns(NEWNET)");
		जाओ out_unlink;
	पूर्ण
	बंद(netns);
	old_net = -1;
	netns = -1;

	info_len = माप(info);
	err = bpf_obj_get_info_by_fd(link, &info, &info_len);
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("bpf_obj_get_info");
		जाओ out_unlink;
	पूर्ण
	CHECK_FAIL(info_len != माप(info));

	/* Expect netns_ino to change to 0 */
	CHECK_FAIL(info.type != BPF_LINK_TYPE_NETNS);
	CHECK_FAIL(info.id != link_id);
	CHECK_FAIL(info.prog_id != query_prog_id(prog2));
	CHECK_FAIL(info.netns.netns_ino != 0);
	CHECK_FAIL(info.netns.attach_type != BPF_FLOW_DISSECTOR);

out_unlink:
	बंद(link);
out_resetns:
	अगर (old_net != -1)
		setns(old_net, CLONE_NEWNET);
	अगर (netns != -1)
		बंद(netns);
पूर्ण

अटल व्योम run_tests(पूर्णांक netns)
अणु
	काष्ठा test अणु
		स्थिर अक्षर *test_name;
		व्योम (*test_func)(पूर्णांक netns, पूर्णांक prog1, पूर्णांक prog2);
	पूर्ण tests[] = अणु
		अणु "prog attach, prog attach",
		  test_prog_attach_prog_attach पूर्ण,
		अणु "link create, link create",
		  test_link_create_link_create पूर्ण,
		अणु "prog attach, link create",
		  test_prog_attach_link_create पूर्ण,
		अणु "link create, prog attach",
		  test_link_create_prog_attach पूर्ण,
		अणु "link create, prog detach",
		  test_link_create_prog_detach पूर्ण,
		अणु "prog attach, detach, query",
		  test_prog_attach_detach_query पूर्ण,
		अणु "link create, close, query",
		  test_link_create_बंद_query पूर्ण,
		अणु "link update no old prog",
		  test_link_update_no_old_prog पूर्ण,
		अणु "link update with replace old prog",
		  test_link_update_replace_old_prog पूर्ण,
		अणु "link update with same prog",
		  test_link_update_same_prog पूर्ण,
		अणु "link update invalid opts",
		  test_link_update_invalid_opts पूर्ण,
		अणु "link update invalid prog",
		  test_link_update_invalid_prog पूर्ण,
		अणु "link update netns gone",
		  test_link_update_netns_gone पूर्ण,
		अणु "link get info",
		  test_link_get_info पूर्ण,
	पूर्ण;
	पूर्णांक i, progs[2] = अणु -1, -1 पूर्ण;
	अक्षर test_name[80];

	क्रम (i = 0; i < ARRAY_SIZE(progs); i++) अणु
		progs[i] = load_prog(BPF_PROG_TYPE_FLOW_DISSECTOR);
		अगर (progs[i] < 0)
			जाओ out_बंद;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(tests); i++) अणु
		snम_लिखो(test_name, माप(test_name),
			 "flow dissector %s%s",
			 tests[i].test_name,
			 netns == init_net ? " (init_net)" : "");
		अगर (test__start_subtest(test_name))
			tests[i].test_func(netns, progs[0], progs[1]);
	पूर्ण
out_बंद:
	क्रम (i = 0; i < ARRAY_SIZE(progs); i++) अणु
		अगर (progs[i] != -1)
			CHECK_FAIL(बंद(progs[i]));
	पूर्ण
पूर्ण

व्योम test_flow_dissector_reattach(व्योम)
अणु
	पूर्णांक err, new_net, saved_net;

	saved_net = खोलो("/proc/self/ns/net", O_RDONLY);
	अगर (CHECK_FAIL(saved_net < 0)) अणु
		लिखो_त्रुटि("open(/proc/self/ns/net");
		वापस;
	पूर्ण

	init_net = खोलो("/proc/1/ns/net", O_RDONLY);
	अगर (CHECK_FAIL(init_net < 0)) अणु
		लिखो_त्रुटि("open(/proc/1/ns/net)");
		जाओ out_बंद;
	पूर्ण

	err = setns(init_net, CLONE_NEWNET);
	अगर (CHECK_FAIL(err)) अणु
		लिखो_त्रुटि("setns(/proc/1/ns/net)");
		जाओ out_बंद;
	पूर्ण

	अगर (prog_is_attached(init_net)) अणु
		test__skip();
		म_लिखो("Can't test with flow dissector attached to init_net\n");
		जाओ out_setns;
	पूर्ण

	/* First run tests in root network namespace */
	run_tests(init_net);

	/* Then repeat tests in a non-root namespace */
	new_net = unshare_net(init_net);
	अगर (new_net < 0)
		जाओ out_setns;
	run_tests(new_net);
	बंद(new_net);

out_setns:
	/* Move back to netns we started in. */
	err = setns(saved_net, CLONE_NEWNET);
	अगर (CHECK_FAIL(err))
		लिखो_त्रुटि("setns(/proc/self/ns/net)");

out_बंद:
	बंद(init_net);
	बंद(saved_net);
पूर्ण
