<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2017 Cavium, Inc.
 */
#समावेश <linux/bpf.h>
#समावेश <linux/netlink.h>
#समावेश <linux/rtnetlink.h>
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/socket.h>
#समावेश <unistd.h>
#समावेश <bpf/bpf.h>
#समावेश <arpa/inet.h>
#समावेश <fcntl.h>
#समावेश <poll.h>
#समावेश <net/अगर.h>
#समावेश <netdb.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/syscall.h>
#समावेश "bpf_util.h"
#समावेश <bpf/libbpf.h>
#समावेश <sys/resource.h>
#समावेश <libgen.h>

पूर्णांक sock, sock_arp, flags = XDP_FLAGS_UPDATE_IF_NOEXIST;
अटल पूर्णांक total_अगरindex;
अटल पूर्णांक *अगरindex_list;
अटल __u32 *prog_id_list;
अक्षर buf[8192];
अटल पूर्णांक lpm_map_fd;
अटल पूर्णांक rxcnt_map_fd;
अटल पूर्णांक arp_table_map_fd;
अटल पूर्णांक exact_match_map_fd;
अटल पूर्णांक tx_port_map_fd;

अटल पूर्णांक get_route_table(पूर्णांक rपंचांग_family);
अटल व्योम पूर्णांक_निकास(पूर्णांक sig)
अणु
	__u32 prog_id = 0;
	पूर्णांक i = 0;

	क्रम (i = 0; i < total_अगरindex; i++) अणु
		अगर (bpf_get_link_xdp_id(अगरindex_list[i], &prog_id, flags)) अणु
			म_लिखो("bpf_get_link_xdp_id on iface %d failed\n",
			       अगरindex_list[i]);
			निकास(1);
		पूर्ण
		अगर (prog_id_list[i] == prog_id)
			bpf_set_link_xdp_fd(अगरindex_list[i], -1, flags);
		अन्यथा अगर (!prog_id)
			म_लिखो("couldn't find a prog id on iface %d\n",
			       अगरindex_list[i]);
		अन्यथा
			म_लिखो("program on iface %d changed, not removing\n",
			       अगरindex_list[i]);
		prog_id = 0;
	पूर्ण
	निकास(0);
पूर्ण

अटल व्योम बंद_and_निकास(पूर्णांक sig)
अणु
	बंद(sock);
	बंद(sock_arp);

	पूर्णांक_निकास(0);
पूर्ण

/* Get the mac address of the पूर्णांकerface given पूर्णांकerface name */
अटल __be64 geपंचांगac(अक्षर *अगरace)
अणु
	काष्ठा अगरreq अगरr;
	__be64 mac = 0;
	पूर्णांक fd, i;

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	अगरr.अगरr_addr.sa_family = AF_INET;
	म_नकलन(अगरr.अगरr_name, अगरace, IFNAMSIZ - 1);
	अगर (ioctl(fd, SIOCGIFHWADDR, &अगरr) < 0) अणु
		म_लिखो("ioctl failed leaving....\n");
		वापस -1;
	पूर्ण
	क्रम (i = 0; i < 6 ; i++)
		*((__u8 *)&mac + i) = (__u8)अगरr.अगरr_hwaddr.sa_data[i];
	बंद(fd);
	वापस mac;
पूर्ण

अटल पूर्णांक recv_msg(काष्ठा sockaddr_nl sock_addr, पूर्णांक sock)
अणु
	काष्ठा nlmsghdr *nh;
	पूर्णांक len, nll = 0;
	अक्षर *buf_ptr;

	buf_ptr = buf;
	जबतक (1) अणु
		len = recv(sock, buf_ptr, माप(buf) - nll, 0);
		अगर (len < 0)
			वापस len;

		nh = (काष्ठा nlmsghdr *)buf_ptr;

		अगर (nh->nlmsg_type == NLMSG_DONE)
			अवरोध;
		buf_ptr += len;
		nll += len;
		अगर ((sock_addr.nl_groups & RTMGRP_NEIGH) == RTMGRP_NEIGH)
			अवरोध;

		अगर ((sock_addr.nl_groups & RTMGRP_IPV4_ROUTE) == RTMGRP_IPV4_ROUTE)
			अवरोध;
	पूर्ण
	वापस nll;
पूर्ण

/* Function to parse the route entry वापसed by netlink
 * Updates the route entry related map entries
 */
अटल व्योम पढ़ो_route(काष्ठा nlmsghdr *nh, पूर्णांक nll)
अणु
	अक्षर dsts[24], gws[24], अगरs[16], dsts_len[24], metrics[24];
	काष्ठा bpf_lpm_trie_key *prefix_key;
	काष्ठा rtattr *rt_attr;
	काष्ठा rपंचांगsg *rt_msg;
	पूर्णांक rपंचांग_family;
	पूर्णांक rtl;
	पूर्णांक i;
	काष्ठा route_table अणु
		पूर्णांक  dst_len, अगरace, metric;
		अक्षर *अगरace_name;
		__be32 dst, gw;
		__be64 mac;
	पूर्ण route;
	काष्ठा arp_table अणु
		__be64 mac;
		__be32 dst;
	पूर्ण;

	काष्ठा direct_map अणु
		काष्ठा arp_table arp;
		पूर्णांक अगरindex;
		__be64 mac;
	पूर्ण direct_entry;

	अगर (nh->nlmsg_type == RTM_DELROUTE)
		म_लिखो("DELETING Route entry\n");
	अन्यथा अगर (nh->nlmsg_type == RTM_GETROUTE)
		म_लिखो("READING Route entry\n");
	अन्यथा अगर (nh->nlmsg_type == RTM_NEWROUTE)
		म_लिखो("NEW Route entry\n");
	अन्यथा
		म_लिखो("%d\n", nh->nlmsg_type);

	स_रखो(&route, 0, माप(route));
	म_लिखो("Destination\t\tGateway\t\tGenmask\t\tMetric\t\tIface\n");
	क्रम (; NLMSG_OK(nh, nll); nh = NLMSG_NEXT(nh, nll)) अणु
		rt_msg = (काष्ठा rपंचांगsg *)NLMSG_DATA(nh);
		rपंचांग_family = rt_msg->rपंचांग_family;
		अगर (rपंचांग_family == AF_INET)
			अगर (rt_msg->rपंचांग_table != RT_TABLE_MAIN)
				जारी;
		rt_attr = (काष्ठा rtattr *)RTM_RTA(rt_msg);
		rtl = RTM_PAYLOAD(nh);

		क्रम (; RTA_OK(rt_attr, rtl); rt_attr = RTA_NEXT(rt_attr, rtl)) अणु
			चयन (rt_attr->rta_type) अणु
			हाल NDA_DST:
				प्र_लिखो(dsts, "%u",
					(*((__be32 *)RTA_DATA(rt_attr))));
				अवरोध;
			हाल RTA_GATEWAY:
				प्र_लिखो(gws, "%u",
					*((__be32 *)RTA_DATA(rt_attr)));
				अवरोध;
			हाल RTA_OIF:
				प्र_लिखो(अगरs, "%u",
					*((पूर्णांक *)RTA_DATA(rt_attr)));
				अवरोध;
			हाल RTA_METRICS:
				प्र_लिखो(metrics, "%u",
					*((पूर्णांक *)RTA_DATA(rt_attr)));
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
		प्र_लिखो(dsts_len, "%d", rt_msg->rपंचांग_dst_len);
		route.dst = म_से_प(dsts);
		route.dst_len = म_से_प(dsts_len);
		route.gw = म_से_प(gws);
		route.अगरace = म_से_प(अगरs);
		route.metric = म_से_प(metrics);
		route.अगरace_name = alloca(माप(अक्षर *) * IFNAMSIZ);
		route.अगरace_name = अगर_indextoname(route.अगरace, route.अगरace_name);
		route.mac = geपंचांगac(route.अगरace_name);
		अगर (route.mac == -1)
			पूर्णांक_निकास(0);
		निश्चित(bpf_map_update_elem(tx_port_map_fd,
					   &route.अगरace, &route.अगरace, 0) == 0);
		अगर (rपंचांग_family == AF_INET) अणु
			काष्ठा trie_value अणु
				__u8 prefix[4];
				__be64 value;
				पूर्णांक अगरindex;
				पूर्णांक metric;
				__be32 gw;
			पूर्ण *prefix_value;

			prefix_key = alloca(माप(*prefix_key) + 3);
			prefix_value = alloca(माप(*prefix_value));

			prefix_key->prefixlen = 32;
			prefix_key->prefixlen = route.dst_len;
			direct_entry.mac = route.mac & 0xffffffffffff;
			direct_entry.अगरindex = route.अगरace;
			direct_entry.arp.mac = 0;
			direct_entry.arp.dst = 0;
			अगर (route.dst_len == 32) अणु
				अगर (nh->nlmsg_type == RTM_DELROUTE) अणु
					निश्चित(bpf_map_delete_elem(exact_match_map_fd,
								   &route.dst) == 0);
				पूर्ण अन्यथा अणु
					अगर (bpf_map_lookup_elem(arp_table_map_fd,
								&route.dst,
								&direct_entry.arp.mac) == 0)
						direct_entry.arp.dst = route.dst;
					निश्चित(bpf_map_update_elem(exact_match_map_fd,
								   &route.dst,
								   &direct_entry, 0) == 0);
				पूर्ण
			पूर्ण
			क्रम (i = 0; i < 4; i++)
				prefix_key->data[i] = (route.dst >> i * 8) & 0xff;

			म_लिखो("%3d.%d.%d.%d\t\t%3x\t\t%d\t\t%d\t\t%s\n",
			       (पूर्णांक)prefix_key->data[0],
			       (पूर्णांक)prefix_key->data[1],
			       (पूर्णांक)prefix_key->data[2],
			       (पूर्णांक)prefix_key->data[3],
			       route.gw, route.dst_len,
			       route.metric,
			       route.अगरace_name);
			अगर (bpf_map_lookup_elem(lpm_map_fd, prefix_key,
						prefix_value) < 0) अणु
				क्रम (i = 0; i < 4; i++)
					prefix_value->prefix[i] = prefix_key->data[i];
				prefix_value->value = route.mac & 0xffffffffffff;
				prefix_value->अगरindex = route.अगरace;
				prefix_value->gw = route.gw;
				prefix_value->metric = route.metric;

				निश्चित(bpf_map_update_elem(lpm_map_fd,
							   prefix_key,
							   prefix_value, 0
							   ) == 0);
			पूर्ण अन्यथा अणु
				अगर (nh->nlmsg_type == RTM_DELROUTE) अणु
					म_लिखो("deleting entry\n");
					म_लिखो("prefix key=%d.%d.%d.%d/%d",
					       prefix_key->data[0],
					       prefix_key->data[1],
					       prefix_key->data[2],
					       prefix_key->data[3],
					       prefix_key->prefixlen);
					निश्चित(bpf_map_delete_elem(lpm_map_fd,
								   prefix_key
								   ) == 0);
					/* Reपढ़ोing the route table to check अगर
					 * there is an entry with the same
					 * prefix but a dअगरferent metric as the
					 * deleted enty.
					 */
					get_route_table(AF_INET);
				पूर्ण अन्यथा अगर (prefix_key->data[0] ==
					   prefix_value->prefix[0] &&
					   prefix_key->data[1] ==
					   prefix_value->prefix[1] &&
					   prefix_key->data[2] ==
					   prefix_value->prefix[2] &&
					   prefix_key->data[3] ==
					   prefix_value->prefix[3] &&
					   route.metric >= prefix_value->metric) अणु
					जारी;
				पूर्ण अन्यथा अणु
					क्रम (i = 0; i < 4; i++)
						prefix_value->prefix[i] =
							prefix_key->data[i];
					prefix_value->value =
						route.mac & 0xffffffffffff;
					prefix_value->अगरindex = route.अगरace;
					prefix_value->gw = route.gw;
					prefix_value->metric = route.metric;
					निश्चित(bpf_map_update_elem(lpm_map_fd,
								   prefix_key,
								   prefix_value,
								   0) == 0);
				पूर्ण
			पूर्ण
		पूर्ण
		स_रखो(&route, 0, माप(route));
		स_रखो(dsts, 0, माप(dsts));
		स_रखो(dsts_len, 0, माप(dsts_len));
		स_रखो(gws, 0, माप(gws));
		स_रखो(अगरs, 0, माप(अगरs));
		स_रखो(&route, 0, माप(route));
	पूर्ण
पूर्ण

/* Function to पढ़ो the existing route table  when the process is launched*/
अटल पूर्णांक get_route_table(पूर्णांक rपंचांग_family)
अणु
	काष्ठा sockaddr_nl sa;
	काष्ठा nlmsghdr *nh;
	पूर्णांक sock, seq = 0;
	काष्ठा msghdr msg;
	काष्ठा iovec iov;
	पूर्णांक ret = 0;
	पूर्णांक nll;

	काष्ठा अणु
		काष्ठा nlmsghdr nl;
		काष्ठा rपंचांगsg rt;
		अक्षर buf[8192];
	पूर्ण req;

	sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
	अगर (sock < 0) अणु
		म_लिखो("open netlink socket: %s\n", म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण
	स_रखो(&sa, 0, माप(sa));
	sa.nl_family = AF_NETLINK;
	अगर (bind(sock, (काष्ठा sockaddr *)&sa, माप(sa)) < 0) अणु
		म_लिखो("bind to netlink: %s\n", म_त्रुटि(त्रुटि_सं));
		ret = -1;
		जाओ cleanup;
	पूर्ण
	स_रखो(&req, 0, माप(req));
	req.nl.nlmsg_len = NLMSG_LENGTH(माप(काष्ठा rपंचांगsg));
	req.nl.nlmsg_flags = NLM_F_REQUEST | NLM_F_DUMP;
	req.nl.nlmsg_type = RTM_GETROUTE;

	req.rt.rपंचांग_family = rपंचांग_family;
	req.rt.rपंचांग_table = RT_TABLE_MAIN;
	req.nl.nlmsg_pid = 0;
	req.nl.nlmsg_seq = ++seq;
	स_रखो(&msg, 0, माप(msg));
	iov.iov_base = (व्योम *)&req.nl;
	iov.iov_len = req.nl.nlmsg_len;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	ret = sendmsg(sock, &msg, 0);
	अगर (ret < 0) अणु
		म_लिखो("send to netlink: %s\n", म_त्रुटि(त्रुटि_सं));
		ret = -1;
		जाओ cleanup;
	पूर्ण
	स_रखो(buf, 0, माप(buf));
	nll = recv_msg(sa, sock);
	अगर (nll < 0) अणु
		म_लिखो("recv from netlink: %s\n", म_त्रुटि(nll));
		ret = -1;
		जाओ cleanup;
	पूर्ण
	nh = (काष्ठा nlmsghdr *)buf;
	पढ़ो_route(nh, nll);
cleanup:
	बंद(sock);
	वापस ret;
पूर्ण

/* Function to parse the arp entry वापसed by netlink
 * Updates the arp entry related map entries
 */
अटल व्योम पढ़ो_arp(काष्ठा nlmsghdr *nh, पूर्णांक nll)
अणु
	काष्ठा rtattr *rt_attr;
	अक्षर dsts[24], mac[24];
	काष्ठा ndmsg *rt_msg;
	पूर्णांक rtl, ndm_family;

	काष्ठा arp_table अणु
		__be64 mac;
		__be32 dst;
	पूर्ण arp_entry;
	काष्ठा direct_map अणु
		काष्ठा arp_table arp;
		पूर्णांक अगरindex;
		__be64 mac;
	पूर्ण direct_entry;

	अगर (nh->nlmsg_type == RTM_GETNEIGH)
		म_लिखो("READING arp entry\n");
	म_लिखो("Address\tHwAddress\n");
	क्रम (; NLMSG_OK(nh, nll); nh = NLMSG_NEXT(nh, nll)) अणु
		rt_msg = (काष्ठा ndmsg *)NLMSG_DATA(nh);
		rt_attr = (काष्ठा rtattr *)RTM_RTA(rt_msg);
		ndm_family = rt_msg->ndm_family;
		rtl = RTM_PAYLOAD(nh);
		क्रम (; RTA_OK(rt_attr, rtl); rt_attr = RTA_NEXT(rt_attr, rtl)) अणु
			चयन (rt_attr->rta_type) अणु
			हाल NDA_DST:
				प्र_लिखो(dsts, "%u",
					*((__be32 *)RTA_DATA(rt_attr)));
				अवरोध;
			हाल NDA_LLADDR:
				प्र_लिखो(mac, "%lld",
					*((__be64 *)RTA_DATA(rt_attr)));
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
		arp_entry.dst = म_से_प(dsts);
		arp_entry.mac = म_से_द(mac);
		म_लिखो("%x\t\t%llx\n", arp_entry.dst, arp_entry.mac);
		अगर (ndm_family == AF_INET) अणु
			अगर (bpf_map_lookup_elem(exact_match_map_fd,
						&arp_entry.dst,
						&direct_entry) == 0) अणु
				अगर (nh->nlmsg_type == RTM_DELNEIGH) अणु
					direct_entry.arp.dst = 0;
					direct_entry.arp.mac = 0;
				पूर्ण अन्यथा अगर (nh->nlmsg_type == RTM_NEWNEIGH) अणु
					direct_entry.arp.dst = arp_entry.dst;
					direct_entry.arp.mac = arp_entry.mac;
				पूर्ण
				निश्चित(bpf_map_update_elem(exact_match_map_fd,
							   &arp_entry.dst,
							   &direct_entry, 0
							   ) == 0);
				स_रखो(&direct_entry, 0, माप(direct_entry));
			पूर्ण
			अगर (nh->nlmsg_type == RTM_DELNEIGH) अणु
				निश्चित(bpf_map_delete_elem(arp_table_map_fd,
							   &arp_entry.dst) == 0);
			पूर्ण अन्यथा अगर (nh->nlmsg_type == RTM_NEWNEIGH) अणु
				निश्चित(bpf_map_update_elem(arp_table_map_fd,
							   &arp_entry.dst,
							   &arp_entry.mac, 0
							   ) == 0);
			पूर्ण
		पूर्ण
		स_रखो(&arp_entry, 0, माप(arp_entry));
		स_रखो(dsts, 0, माप(dsts));
	पूर्ण
पूर्ण

/* Function to पढ़ो the existing arp table  when the process is launched*/
अटल पूर्णांक get_arp_table(पूर्णांक rपंचांग_family)
अणु
	काष्ठा sockaddr_nl sa;
	काष्ठा nlmsghdr *nh;
	पूर्णांक sock, seq = 0;
	काष्ठा msghdr msg;
	काष्ठा iovec iov;
	पूर्णांक ret = 0;
	पूर्णांक nll;
	काष्ठा अणु
		काष्ठा nlmsghdr nl;
		काष्ठा ndmsg rt;
		अक्षर buf[8192];
	पूर्ण req;

	sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
	अगर (sock < 0) अणु
		म_लिखो("open netlink socket: %s\n", म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण
	स_रखो(&sa, 0, माप(sa));
	sa.nl_family = AF_NETLINK;
	अगर (bind(sock, (काष्ठा sockaddr *)&sa, माप(sa)) < 0) अणु
		म_लिखो("bind to netlink: %s\n", म_त्रुटि(त्रुटि_सं));
		ret = -1;
		जाओ cleanup;
	पूर्ण
	स_रखो(&req, 0, माप(req));
	req.nl.nlmsg_len = NLMSG_LENGTH(माप(काष्ठा rपंचांगsg));
	req.nl.nlmsg_flags = NLM_F_REQUEST | NLM_F_DUMP;
	req.nl.nlmsg_type = RTM_GETNEIGH;
	req.rt.ndm_state = NUD_REACHABLE;
	req.rt.ndm_family = rपंचांग_family;
	req.nl.nlmsg_pid = 0;
	req.nl.nlmsg_seq = ++seq;
	स_रखो(&msg, 0, माप(msg));
	iov.iov_base = (व्योम *)&req.nl;
	iov.iov_len = req.nl.nlmsg_len;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	ret = sendmsg(sock, &msg, 0);
	अगर (ret < 0) अणु
		म_लिखो("send to netlink: %s\n", म_त्रुटि(त्रुटि_सं));
		ret = -1;
		जाओ cleanup;
	पूर्ण
	स_रखो(buf, 0, माप(buf));
	nll = recv_msg(sa, sock);
	अगर (nll < 0) अणु
		म_लिखो("recv from netlink: %s\n", म_त्रुटि(nll));
		ret = -1;
		जाओ cleanup;
	पूर्ण
	nh = (काष्ठा nlmsghdr *)buf;
	पढ़ो_arp(nh, nll);
cleanup:
	बंद(sock);
	वापस ret;
पूर्ण

/* Function to keep track and update changes in route and arp table
 * Give regular statistics of packets क्रमwarded
 */
अटल पूर्णांक monitor_route(व्योम)
अणु
	अचिन्हित पूर्णांक nr_cpus = bpf_num_possible_cpus();
	स्थिर अचिन्हित पूर्णांक nr_keys = 256;
	काष्ठा pollfd fds_route, fds_arp;
	__u64 prev[nr_keys][nr_cpus];
	काष्ठा sockaddr_nl la, lr;
	__u64 values[nr_cpus];
	काष्ठा nlmsghdr *nh;
	पूर्णांक nll, ret = 0;
	पूर्णांक पूर्णांकerval = 5;
	__u32 key;
	पूर्णांक i;

	sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
	अगर (sock < 0) अणु
		म_लिखो("open netlink socket: %s\n", म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	fcntl(sock, F_SETFL, O_NONBLOCK);
	स_रखो(&lr, 0, माप(lr));
	lr.nl_family = AF_NETLINK;
	lr.nl_groups = RTMGRP_IPV6_ROUTE | RTMGRP_IPV4_ROUTE | RTMGRP_NOTIFY;
	अगर (bind(sock, (काष्ठा sockaddr *)&lr, माप(lr)) < 0) अणु
		म_लिखो("bind to netlink: %s\n", म_त्रुटि(त्रुटि_सं));
		ret = -1;
		जाओ cleanup;
	पूर्ण
	fds_route.fd = sock;
	fds_route.events = POLL_IN;

	sock_arp = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
	अगर (sock_arp < 0) अणु
		म_लिखो("open netlink socket: %s\n", म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	fcntl(sock_arp, F_SETFL, O_NONBLOCK);
	स_रखो(&la, 0, माप(la));
	la.nl_family = AF_NETLINK;
	la.nl_groups = RTMGRP_NEIGH | RTMGRP_NOTIFY;
	अगर (bind(sock_arp, (काष्ठा sockaddr *)&la, माप(la)) < 0) अणु
		म_लिखो("bind to netlink: %s\n", म_त्रुटि(त्रुटि_सं));
		ret = -1;
		जाओ cleanup;
	पूर्ण
	fds_arp.fd = sock_arp;
	fds_arp.events = POLL_IN;

	स_रखो(prev, 0, माप(prev));
	करो अणु
		संकेत(संक_विघ्न, बंद_and_निकास);
		संकेत(संक_इति, बंद_and_निकास);

		sleep(पूर्णांकerval);
		क्रम (key = 0; key < nr_keys; key++) अणु
			__u64 sum = 0;

			निश्चित(bpf_map_lookup_elem(rxcnt_map_fd,
						   &key, values) == 0);
			क्रम (i = 0; i < nr_cpus; i++)
				sum += (values[i] - prev[key][i]);
			अगर (sum)
				म_लिखो("proto %u: %10llu pkt/s\n",
				       key, sum / पूर्णांकerval);
			स_नकल(prev[key], values, माप(values));
		पूर्ण

		स_रखो(buf, 0, माप(buf));
		अगर (poll(&fds_route, 1, 3) == POLL_IN) अणु
			nll = recv_msg(lr, sock);
			अगर (nll < 0) अणु
				म_लिखो("recv from netlink: %s\n", म_त्रुटि(nll));
				ret = -1;
				जाओ cleanup;
			पूर्ण

			nh = (काष्ठा nlmsghdr *)buf;
			म_लिखो("Routing table updated.\n");
			पढ़ो_route(nh, nll);
		पूर्ण
		स_रखो(buf, 0, माप(buf));
		अगर (poll(&fds_arp, 1, 3) == POLL_IN) अणु
			nll = recv_msg(la, sock_arp);
			अगर (nll < 0) अणु
				म_लिखो("recv from netlink: %s\n", म_त्रुटि(nll));
				ret = -1;
				जाओ cleanup;
			पूर्ण

			nh = (काष्ठा nlmsghdr *)buf;
			पढ़ो_arp(nh, nll);
		पूर्ण

	पूर्ण जबतक (1);
cleanup:
	बंद(sock);
	वापस ret;
पूर्ण

अटल व्योम usage(स्थिर अक्षर *prog)
अणु
	ख_लिखो(मानक_त्रुटि,
		"%s: %s [OPTS] interface name list\n\n"
		"OPTS:\n"
		"    -S    use skb-mode\n"
		"    -F    force loading prog\n",
		__func__, prog);
पूर्ण

पूर्णांक मुख्य(पूर्णांक ac, अक्षर **argv)
अणु
	काष्ठा bpf_prog_load_attr prog_load_attr = अणु
		.prog_type	= BPF_PROG_TYPE_XDP,
	पूर्ण;
	काष्ठा bpf_prog_info info = अणुपूर्ण;
	__u32 info_len = माप(info);
	स्थिर अक्षर *optstr = "SF";
	काष्ठा bpf_object *obj;
	अक्षर filename[256];
	अक्षर **अगरname_list;
	पूर्णांक prog_fd, opt;
	पूर्णांक err, i = 1;

	snम_लिखो(filename, माप(filename), "%s_kern.o", argv[0]);
	prog_load_attr.file = filename;

	total_अगरindex = ac - 1;
	अगरname_list = (argv + 1);

	जबतक ((opt = getopt(ac, argv, optstr)) != -1) अणु
		चयन (opt) अणु
		हाल 'S':
			flags |= XDP_FLAGS_SKB_MODE;
			total_अगरindex--;
			अगरname_list++;
			अवरोध;
		हाल 'F':
			flags &= ~XDP_FLAGS_UPDATE_IF_NOEXIST;
			total_अगरindex--;
			अगरname_list++;
			अवरोध;
		शेष:
			usage(basename(argv[0]));
			वापस 1;
		पूर्ण
	पूर्ण

	अगर (!(flags & XDP_FLAGS_SKB_MODE))
		flags |= XDP_FLAGS_DRV_MODE;

	अगर (optind == ac) अणु
		usage(basename(argv[0]));
		वापस 1;
	पूर्ण

	अगर (bpf_prog_load_xattr(&prog_load_attr, &obj, &prog_fd))
		वापस 1;

	म_लिखो("\n**************loading bpf file*********************\n\n\n");
	अगर (!prog_fd) अणु
		म_लिखो("bpf_prog_load_xattr: %s\n", म_त्रुटि(त्रुटि_सं));
		वापस 1;
	पूर्ण

	lpm_map_fd = bpf_object__find_map_fd_by_name(obj, "lpm_map");
	rxcnt_map_fd = bpf_object__find_map_fd_by_name(obj, "rxcnt");
	arp_table_map_fd = bpf_object__find_map_fd_by_name(obj, "arp_table");
	exact_match_map_fd = bpf_object__find_map_fd_by_name(obj,
							     "exact_match");
	tx_port_map_fd = bpf_object__find_map_fd_by_name(obj, "tx_port");
	अगर (lpm_map_fd < 0 || rxcnt_map_fd < 0 || arp_table_map_fd < 0 ||
	    exact_match_map_fd < 0 || tx_port_map_fd < 0) अणु
		म_लिखो("bpf_object__find_map_fd_by_name failed\n");
		वापस 1;
	पूर्ण

	अगरindex_list = (पूर्णांक *)सुस्मृति(total_अगरindex, माप(पूर्णांक *));
	क्रम (i = 0; i < total_अगरindex; i++) अणु
		अगरindex_list[i] = अगर_nametoindex(अगरname_list[i]);
		अगर (!अगरindex_list[i]) अणु
			म_लिखो("Couldn't translate interface name: %s",
			       म_त्रुटि(त्रुटि_सं));
			वापस 1;
		पूर्ण
	पूर्ण
	prog_id_list = (__u32 *)सुस्मृति(total_अगरindex, माप(__u32 *));
	क्रम (i = 0; i < total_अगरindex; i++) अणु
		अगर (bpf_set_link_xdp_fd(अगरindex_list[i], prog_fd, flags) < 0) अणु
			म_लिखो("link set xdp fd failed\n");
			पूर्णांक recovery_index = i;

			क्रम (i = 0; i < recovery_index; i++)
				bpf_set_link_xdp_fd(अगरindex_list[i], -1, flags);

			वापस 1;
		पूर्ण
		err = bpf_obj_get_info_by_fd(prog_fd, &info, &info_len);
		अगर (err) अणु
			म_लिखो("can't get prog info - %s\n", म_त्रुटि(त्रुटि_सं));
			वापस err;
		पूर्ण
		prog_id_list[i] = info.id;
		स_रखो(&info, 0, माप(info));
		म_लिखो("Attached to %d\n", अगरindex_list[i]);
	पूर्ण
	संकेत(संक_विघ्न, पूर्णांक_निकास);
	संकेत(संक_इति, पूर्णांक_निकास);

	म_लिखो("*******************ROUTE TABLE*************************\n\n\n");
	get_route_table(AF_INET);
	म_लिखो("*******************ARP TABLE***************************\n\n\n");
	get_arp_table(AF_INET);
	अगर (monitor_route() < 0) अणु
		म_लिखो("Error in receiving route update");
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण
