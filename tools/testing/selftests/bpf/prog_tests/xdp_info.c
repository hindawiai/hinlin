<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/अगर_link.h>
#समावेश <test_progs.h>

#घोषणा IFINDEX_LO 1

व्योम test_xdp_info(व्योम)
अणु
	__u32 len = माप(काष्ठा bpf_prog_info), duration = 0, prog_id;
	स्थिर अक्षर *file = "./xdp_dummy.o";
	काष्ठा bpf_prog_info info = अणुपूर्ण;
	काष्ठा bpf_object *obj;
	पूर्णांक err, prog_fd;

	/* Get prog_id क्रम XDP_ATTACHED_NONE mode */

	err = bpf_get_link_xdp_id(IFINDEX_LO, &prog_id, 0);
	अगर (CHECK(err, "get_xdp_none", "errno=%d\n", त्रुटि_सं))
		वापस;
	अगर (CHECK(prog_id, "prog_id_none", "unexpected prog_id=%u\n", prog_id))
		वापस;

	err = bpf_get_link_xdp_id(IFINDEX_LO, &prog_id, XDP_FLAGS_SKB_MODE);
	अगर (CHECK(err, "get_xdp_none_skb", "errno=%d\n", त्रुटि_सं))
		वापस;
	अगर (CHECK(prog_id, "prog_id_none_skb", "unexpected prog_id=%u\n",
		  prog_id))
		वापस;

	/* Setup prog */

	err = bpf_prog_load(file, BPF_PROG_TYPE_XDP, &obj, &prog_fd);
	अगर (CHECK_FAIL(err))
		वापस;

	err = bpf_obj_get_info_by_fd(prog_fd, &info, &len);
	अगर (CHECK(err, "get_prog_info", "errno=%d\n", त्रुटि_सं))
		जाओ out_बंद;

	err = bpf_set_link_xdp_fd(IFINDEX_LO, prog_fd, XDP_FLAGS_SKB_MODE);
	अगर (CHECK(err, "set_xdp_skb", "errno=%d\n", त्रुटि_सं))
		जाओ out_बंद;

	/* Get prog_id क्रम single prog mode */

	err = bpf_get_link_xdp_id(IFINDEX_LO, &prog_id, 0);
	अगर (CHECK(err, "get_xdp", "errno=%d\n", त्रुटि_सं))
		जाओ out;
	अगर (CHECK(prog_id != info.id, "prog_id", "prog_id not available\n"))
		जाओ out;

	err = bpf_get_link_xdp_id(IFINDEX_LO, &prog_id, XDP_FLAGS_SKB_MODE);
	अगर (CHECK(err, "get_xdp_skb", "errno=%d\n", त्रुटि_सं))
		जाओ out;
	अगर (CHECK(prog_id != info.id, "prog_id_skb", "prog_id not available\n"))
		जाओ out;

	err = bpf_get_link_xdp_id(IFINDEX_LO, &prog_id, XDP_FLAGS_DRV_MODE);
	अगर (CHECK(err, "get_xdp_drv", "errno=%d\n", त्रुटि_सं))
		जाओ out;
	अगर (CHECK(prog_id, "prog_id_drv", "unexpected prog_id=%u\n", prog_id))
		जाओ out;

out:
	bpf_set_link_xdp_fd(IFINDEX_LO, -1, 0);
out_बंद:
	bpf_object__बंद(obj);
पूर्ण
