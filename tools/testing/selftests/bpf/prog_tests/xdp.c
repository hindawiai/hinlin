<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश <network_helpers.h>

व्योम test_xdp(व्योम)
अणु
	काष्ठा vip key4 = अणु.protocol = 6, .family = AF_INETपूर्ण;
	काष्ठा vip key6 = अणु.protocol = 6, .family = AF_INET6पूर्ण;
	काष्ठा iptnl_info value4 = अणु.family = AF_INETपूर्ण;
	काष्ठा iptnl_info value6 = अणु.family = AF_INET6पूर्ण;
	स्थिर अक्षर *file = "./test_xdp.o";
	काष्ठा bpf_object *obj;
	अक्षर buf[128];
	काष्ठा ipv6hdr *iph6 = (व्योम *)buf + माप(काष्ठा ethhdr);
	काष्ठा iphdr *iph = (व्योम *)buf + माप(काष्ठा ethhdr);
	__u32 duration, retval, size;
	पूर्णांक err, prog_fd, map_fd;

	err = bpf_prog_load(file, BPF_PROG_TYPE_XDP, &obj, &prog_fd);
	अगर (CHECK_FAIL(err))
		वापस;

	map_fd = bpf_find_map(__func__, obj, "vip2tnl");
	अगर (map_fd < 0)
		जाओ out;
	bpf_map_update_elem(map_fd, &key4, &value4, 0);
	bpf_map_update_elem(map_fd, &key6, &value6, 0);

	err = bpf_prog_test_run(prog_fd, 1, &pkt_v4, माप(pkt_v4),
				buf, &size, &retval, &duration);

	CHECK(err || retval != XDP_TX || size != 74 ||
	      iph->protocol != IPPROTO_IPIP, "ipv4",
	      "err %d errno %d retval %d size %d\n",
	      err, त्रुटि_सं, retval, size);

	err = bpf_prog_test_run(prog_fd, 1, &pkt_v6, माप(pkt_v6),
				buf, &size, &retval, &duration);
	CHECK(err || retval != XDP_TX || size != 114 ||
	      iph6->nexthdr != IPPROTO_IPV6, "ipv6",
	      "err %d errno %d retval %d size %d\n",
	      err, त्रुटि_सं, retval, size);
out:
	bpf_object__बंद(obj);
पूर्ण
