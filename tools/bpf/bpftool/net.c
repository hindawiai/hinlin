<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
// Copyright (C) 2018 Facebook

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <समय.स>
#समावेश <unistd.h>
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>
#समावेश <net/अगर.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/socket.h>
#समावेश <linux/tc_act/tc_bpf.h>
#समावेश <sys/socket.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>

#समावेश "bpf/nlattr.h"
#समावेश "main.h"
#समावेश "netlink_dumper.h"

#अगर_अघोषित SOL_NETLINK
#घोषणा SOL_NETLINK 270
#पूर्ण_अगर

काष्ठा ip_devname_अगरindex अणु
	अक्षर	devname[64];
	पूर्णांक	अगरindex;
पूर्ण;

काष्ठा bpf_netdev_t अणु
	काष्ठा ip_devname_अगरindex *devices;
	पूर्णांक	used_len;
	पूर्णांक	array_len;
	पूर्णांक	filter_idx;
पूर्ण;

काष्ठा tc_kind_handle अणु
	अक्षर	kind[64];
	पूर्णांक	handle;
पूर्ण;

काष्ठा bpf_tcinfo_t अणु
	काष्ठा tc_kind_handle	*handle_array;
	पूर्णांक			used_len;
	पूर्णांक			array_len;
	bool			is_qdisc;
पूर्ण;

काष्ठा bpf_filter_t अणु
	स्थिर अक्षर	*kind;
	स्थिर अक्षर	*devname;
	पूर्णांक		अगरindex;
पूर्ण;

काष्ठा bpf_attach_info अणु
	__u32 flow_dissector_id;
पूर्ण;

क्रमागत net_attach_type अणु
	NET_ATTACH_TYPE_XDP,
	NET_ATTACH_TYPE_XDP_GENERIC,
	NET_ATTACH_TYPE_XDP_DRIVER,
	NET_ATTACH_TYPE_XDP_OFFLOAD,
पूर्ण;

अटल स्थिर अक्षर * स्थिर attach_type_strings[] = अणु
	[NET_ATTACH_TYPE_XDP]		= "xdp",
	[NET_ATTACH_TYPE_XDP_GENERIC]	= "xdpgeneric",
	[NET_ATTACH_TYPE_XDP_DRIVER]	= "xdpdrv",
	[NET_ATTACH_TYPE_XDP_OFFLOAD]	= "xdpoffload",
पूर्ण;

स्थिर माप_प्रकार net_attach_type_size = ARRAY_SIZE(attach_type_strings);

अटल क्रमागत net_attach_type parse_attach_type(स्थिर अक्षर *str)
अणु
	क्रमागत net_attach_type type;

	क्रम (type = 0; type < net_attach_type_size; type++) अणु
		अगर (attach_type_strings[type] &&
		    is_prefix(str, attach_type_strings[type]))
			वापस type;
	पूर्ण

	वापस net_attach_type_size;
पूर्ण

प्रकार पूर्णांक (*dump_nlmsg_t)(व्योम *cookie, व्योम *msg, काष्ठा nlattr **tb);

प्रकार पूर्णांक (*__dump_nlmsg_t)(काष्ठा nlmsghdr *nlmsg, dump_nlmsg_t, व्योम *cookie);

अटल पूर्णांक netlink_खोलो(__u32 *nl_pid)
अणु
	काष्ठा sockaddr_nl sa;
	socklen_t addrlen;
	पूर्णांक one = 1, ret;
	पूर्णांक sock;

	स_रखो(&sa, 0, माप(sa));
	sa.nl_family = AF_NETLINK;

	sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
	अगर (sock < 0)
		वापस -त्रुटि_सं;

	अगर (setsockopt(sock, SOL_NETLINK, NETLINK_EXT_ACK,
		       &one, माप(one)) < 0) अणु
		p_err("Netlink error reporting not supported");
	पूर्ण

	अगर (bind(sock, (काष्ठा sockaddr *)&sa, माप(sa)) < 0) अणु
		ret = -त्रुटि_सं;
		जाओ cleanup;
	पूर्ण

	addrlen = माप(sa);
	अगर (माला_लोockname(sock, (काष्ठा sockaddr *)&sa, &addrlen) < 0) अणु
		ret = -त्रुटि_सं;
		जाओ cleanup;
	पूर्ण

	अगर (addrlen != माप(sa)) अणु
		ret = -LIBBPF_ERRNO__INTERNAL;
		जाओ cleanup;
	पूर्ण

	*nl_pid = sa.nl_pid;
	वापस sock;

cleanup:
	बंद(sock);
	वापस ret;
पूर्ण

अटल पूर्णांक netlink_recv(पूर्णांक sock, __u32 nl_pid, __u32 seq,
			    __dump_nlmsg_t _fn, dump_nlmsg_t fn,
			    व्योम *cookie)
अणु
	bool multipart = true;
	काष्ठा nlmsgerr *err;
	काष्ठा nlmsghdr *nh;
	अक्षर buf[4096];
	पूर्णांक len, ret;

	जबतक (multipart) अणु
		multipart = false;
		len = recv(sock, buf, माप(buf), 0);
		अगर (len < 0) अणु
			ret = -त्रुटि_सं;
			जाओ करोne;
		पूर्ण

		अगर (len == 0)
			अवरोध;

		क्रम (nh = (काष्ठा nlmsghdr *)buf; NLMSG_OK(nh, (अचिन्हित पूर्णांक)len);
		     nh = NLMSG_NEXT(nh, len)) अणु
			अगर (nh->nlmsg_pid != nl_pid) अणु
				ret = -LIBBPF_ERRNO__WRNGPID;
				जाओ करोne;
			पूर्ण
			अगर (nh->nlmsg_seq != seq) अणु
				ret = -LIBBPF_ERRNO__INVSEQ;
				जाओ करोne;
			पूर्ण
			अगर (nh->nlmsg_flags & NLM_F_MULTI)
				multipart = true;
			चयन (nh->nlmsg_type) अणु
			हाल NLMSG_ERROR:
				err = (काष्ठा nlmsgerr *)NLMSG_DATA(nh);
				अगर (!err->error)
					जारी;
				ret = err->error;
				libbpf_nla_dump_errormsg(nh);
				जाओ करोne;
			हाल NLMSG_DONE:
				वापस 0;
			शेष:
				अवरोध;
			पूर्ण
			अगर (_fn) अणु
				ret = _fn(nh, fn, cookie);
				अगर (ret)
					वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण
	ret = 0;
करोne:
	वापस ret;
पूर्ण

अटल पूर्णांक __dump_class_nlmsg(काष्ठा nlmsghdr *nlh,
			      dump_nlmsg_t dump_class_nlmsg,
			      व्योम *cookie)
अणु
	काष्ठा nlattr *tb[TCA_MAX + 1], *attr;
	काष्ठा tcmsg *t = NLMSG_DATA(nlh);
	पूर्णांक len;

	len = nlh->nlmsg_len - NLMSG_LENGTH(माप(*t));
	attr = (काष्ठा nlattr *) ((व्योम *) t + NLMSG_ALIGN(माप(*t)));
	अगर (libbpf_nla_parse(tb, TCA_MAX, attr, len, शून्य) != 0)
		वापस -LIBBPF_ERRNO__NLPARSE;

	वापस dump_class_nlmsg(cookie, t, tb);
पूर्ण

अटल पूर्णांक netlink_get_class(पूर्णांक sock, अचिन्हित पूर्णांक nl_pid, पूर्णांक अगरindex,
			     dump_nlmsg_t dump_class_nlmsg, व्योम *cookie)
अणु
	काष्ठा अणु
		काष्ठा nlmsghdr nlh;
		काष्ठा tcmsg t;
	पूर्ण req = अणु
		.nlh.nlmsg_len = NLMSG_LENGTH(माप(काष्ठा tcmsg)),
		.nlh.nlmsg_type = RTM_GETTCLASS,
		.nlh.nlmsg_flags = NLM_F_DUMP | NLM_F_REQUEST,
		.t.tcm_family = AF_UNSPEC,
		.t.tcm_अगरindex = अगरindex,
	पूर्ण;
	पूर्णांक seq = समय(शून्य);

	req.nlh.nlmsg_seq = seq;
	अगर (send(sock, &req, req.nlh.nlmsg_len, 0) < 0)
		वापस -त्रुटि_सं;

	वापस netlink_recv(sock, nl_pid, seq, __dump_class_nlmsg,
			    dump_class_nlmsg, cookie);
पूर्ण

अटल पूर्णांक __dump_qdisc_nlmsg(काष्ठा nlmsghdr *nlh,
			      dump_nlmsg_t dump_qdisc_nlmsg,
			      व्योम *cookie)
अणु
	काष्ठा nlattr *tb[TCA_MAX + 1], *attr;
	काष्ठा tcmsg *t = NLMSG_DATA(nlh);
	पूर्णांक len;

	len = nlh->nlmsg_len - NLMSG_LENGTH(माप(*t));
	attr = (काष्ठा nlattr *) ((व्योम *) t + NLMSG_ALIGN(माप(*t)));
	अगर (libbpf_nla_parse(tb, TCA_MAX, attr, len, शून्य) != 0)
		वापस -LIBBPF_ERRNO__NLPARSE;

	वापस dump_qdisc_nlmsg(cookie, t, tb);
पूर्ण

अटल पूर्णांक netlink_get_qdisc(पूर्णांक sock, अचिन्हित पूर्णांक nl_pid, पूर्णांक अगरindex,
			     dump_nlmsg_t dump_qdisc_nlmsg, व्योम *cookie)
अणु
	काष्ठा अणु
		काष्ठा nlmsghdr nlh;
		काष्ठा tcmsg t;
	पूर्ण req = अणु
		.nlh.nlmsg_len = NLMSG_LENGTH(माप(काष्ठा tcmsg)),
		.nlh.nlmsg_type = RTM_GETQDISC,
		.nlh.nlmsg_flags = NLM_F_DUMP | NLM_F_REQUEST,
		.t.tcm_family = AF_UNSPEC,
		.t.tcm_अगरindex = अगरindex,
	पूर्ण;
	पूर्णांक seq = समय(शून्य);

	req.nlh.nlmsg_seq = seq;
	अगर (send(sock, &req, req.nlh.nlmsg_len, 0) < 0)
		वापस -त्रुटि_सं;

	वापस netlink_recv(sock, nl_pid, seq, __dump_qdisc_nlmsg,
			    dump_qdisc_nlmsg, cookie);
पूर्ण

अटल पूर्णांक __dump_filter_nlmsg(काष्ठा nlmsghdr *nlh,
			       dump_nlmsg_t dump_filter_nlmsg,
			       व्योम *cookie)
अणु
	काष्ठा nlattr *tb[TCA_MAX + 1], *attr;
	काष्ठा tcmsg *t = NLMSG_DATA(nlh);
	पूर्णांक len;

	len = nlh->nlmsg_len - NLMSG_LENGTH(माप(*t));
	attr = (काष्ठा nlattr *) ((व्योम *) t + NLMSG_ALIGN(माप(*t)));
	अगर (libbpf_nla_parse(tb, TCA_MAX, attr, len, शून्य) != 0)
		वापस -LIBBPF_ERRNO__NLPARSE;

	वापस dump_filter_nlmsg(cookie, t, tb);
पूर्ण

अटल पूर्णांक netlink_get_filter(पूर्णांक sock, अचिन्हित पूर्णांक nl_pid, पूर्णांक अगरindex, पूर्णांक handle,
			      dump_nlmsg_t dump_filter_nlmsg, व्योम *cookie)
अणु
	काष्ठा अणु
		काष्ठा nlmsghdr nlh;
		काष्ठा tcmsg t;
	पूर्ण req = अणु
		.nlh.nlmsg_len = NLMSG_LENGTH(माप(काष्ठा tcmsg)),
		.nlh.nlmsg_type = RTM_GETTFILTER,
		.nlh.nlmsg_flags = NLM_F_DUMP | NLM_F_REQUEST,
		.t.tcm_family = AF_UNSPEC,
		.t.tcm_अगरindex = अगरindex,
		.t.tcm_parent = handle,
	पूर्ण;
	पूर्णांक seq = समय(शून्य);

	req.nlh.nlmsg_seq = seq;
	अगर (send(sock, &req, req.nlh.nlmsg_len, 0) < 0)
		वापस -त्रुटि_सं;

	वापस netlink_recv(sock, nl_pid, seq, __dump_filter_nlmsg,
			    dump_filter_nlmsg, cookie);
पूर्ण

अटल पूर्णांक __dump_link_nlmsg(काष्ठा nlmsghdr *nlh,
			     dump_nlmsg_t dump_link_nlmsg, व्योम *cookie)
अणु
	काष्ठा nlattr *tb[IFLA_MAX + 1], *attr;
	काष्ठा अगरinfomsg *अगरi = NLMSG_DATA(nlh);
	पूर्णांक len;

	len = nlh->nlmsg_len - NLMSG_LENGTH(माप(*अगरi));
	attr = (काष्ठा nlattr *) ((व्योम *) अगरi + NLMSG_ALIGN(माप(*अगरi)));
	अगर (libbpf_nla_parse(tb, IFLA_MAX, attr, len, शून्य) != 0)
		वापस -LIBBPF_ERRNO__NLPARSE;

	वापस dump_link_nlmsg(cookie, अगरi, tb);
पूर्ण

अटल पूर्णांक netlink_get_link(पूर्णांक sock, अचिन्हित पूर्णांक nl_pid,
			    dump_nlmsg_t dump_link_nlmsg, व्योम *cookie)
अणु
	काष्ठा अणु
		काष्ठा nlmsghdr nlh;
		काष्ठा अगरinfomsg अगरm;
	पूर्ण req = अणु
		.nlh.nlmsg_len = NLMSG_LENGTH(माप(काष्ठा अगरinfomsg)),
		.nlh.nlmsg_type = RTM_GETLINK,
		.nlh.nlmsg_flags = NLM_F_DUMP | NLM_F_REQUEST,
		.अगरm.अगरi_family = AF_PACKET,
	पूर्ण;
	पूर्णांक seq = समय(शून्य);

	req.nlh.nlmsg_seq = seq;
	अगर (send(sock, &req, req.nlh.nlmsg_len, 0) < 0)
		वापस -त्रुटि_सं;

	वापस netlink_recv(sock, nl_pid, seq, __dump_link_nlmsg,
			    dump_link_nlmsg, cookie);
पूर्ण

अटल पूर्णांक dump_link_nlmsg(व्योम *cookie, व्योम *msg, काष्ठा nlattr **tb)
अणु
	काष्ठा bpf_netdev_t *netinfo = cookie;
	काष्ठा अगरinfomsg *अगरinfo = msg;

	अगर (netinfo->filter_idx > 0 && netinfo->filter_idx != अगरinfo->अगरi_index)
		वापस 0;

	अगर (netinfo->used_len == netinfo->array_len) अणु
		netinfo->devices = पुनः_स्मृति(netinfo->devices,
			(netinfo->array_len + 16) *
			माप(काष्ठा ip_devname_अगरindex));
		अगर (!netinfo->devices)
			वापस -ENOMEM;

		netinfo->array_len += 16;
	पूर्ण
	netinfo->devices[netinfo->used_len].अगरindex = अगरinfo->अगरi_index;
	snम_लिखो(netinfo->devices[netinfo->used_len].devname,
		 माप(netinfo->devices[netinfo->used_len].devname),
		 "%s",
		 tb[IFLA_IFNAME]
			 ? libbpf_nla_getattr_str(tb[IFLA_IFNAME])
			 : "");
	netinfo->used_len++;

	वापस करो_xdp_dump(अगरinfo, tb);
पूर्ण

अटल पूर्णांक dump_class_qdisc_nlmsg(व्योम *cookie, व्योम *msg, काष्ठा nlattr **tb)
अणु
	काष्ठा bpf_tcinfo_t *tcinfo = cookie;
	काष्ठा tcmsg *info = msg;

	अगर (tcinfo->is_qdisc) अणु
		/* skip clsact qdisc */
		अगर (tb[TCA_KIND] &&
		    म_भेद(libbpf_nla_data(tb[TCA_KIND]), "clsact") == 0)
			वापस 0;
		अगर (info->tcm_handle == 0)
			वापस 0;
	पूर्ण

	अगर (tcinfo->used_len == tcinfo->array_len) अणु
		tcinfo->handle_array = पुनः_स्मृति(tcinfo->handle_array,
			(tcinfo->array_len + 16) * माप(काष्ठा tc_kind_handle));
		अगर (!tcinfo->handle_array)
			वापस -ENOMEM;

		tcinfo->array_len += 16;
	पूर्ण
	tcinfo->handle_array[tcinfo->used_len].handle = info->tcm_handle;
	snम_लिखो(tcinfo->handle_array[tcinfo->used_len].kind,
		 माप(tcinfo->handle_array[tcinfo->used_len].kind),
		 "%s",
		 tb[TCA_KIND]
			 ? libbpf_nla_getattr_str(tb[TCA_KIND])
			 : "unknown");
	tcinfo->used_len++;

	वापस 0;
पूर्ण

अटल पूर्णांक dump_filter_nlmsg(व्योम *cookie, व्योम *msg, काष्ठा nlattr **tb)
अणु
	स्थिर काष्ठा bpf_filter_t *filter_info = cookie;

	वापस करो_filter_dump((काष्ठा tcmsg *)msg, tb, filter_info->kind,
			      filter_info->devname, filter_info->अगरindex);
पूर्ण

अटल पूर्णांक show_dev_tc_bpf(पूर्णांक sock, अचिन्हित पूर्णांक nl_pid,
			   काष्ठा ip_devname_अगरindex *dev)
अणु
	काष्ठा bpf_filter_t filter_info;
	काष्ठा bpf_tcinfo_t tcinfo;
	पूर्णांक i, handle, ret = 0;

	tcinfo.handle_array = शून्य;
	tcinfo.used_len = 0;
	tcinfo.array_len = 0;

	tcinfo.is_qdisc = false;
	ret = netlink_get_class(sock, nl_pid, dev->अगरindex,
				dump_class_qdisc_nlmsg, &tcinfo);
	अगर (ret)
		जाओ out;

	tcinfo.is_qdisc = true;
	ret = netlink_get_qdisc(sock, nl_pid, dev->अगरindex,
				dump_class_qdisc_nlmsg, &tcinfo);
	अगर (ret)
		जाओ out;

	filter_info.devname = dev->devname;
	filter_info.अगरindex = dev->अगरindex;
	क्रम (i = 0; i < tcinfo.used_len; i++) अणु
		filter_info.kind = tcinfo.handle_array[i].kind;
		ret = netlink_get_filter(sock, nl_pid, dev->अगरindex,
					 tcinfo.handle_array[i].handle,
					 dump_filter_nlmsg, &filter_info);
		अगर (ret)
			जाओ out;
	पूर्ण

	/* root, ingress and egress handle */
	handle = TC_H_ROOT;
	filter_info.kind = "root";
	ret = netlink_get_filter(sock, nl_pid, dev->अगरindex, handle,
				 dump_filter_nlmsg, &filter_info);
	अगर (ret)
		जाओ out;

	handle = TC_H_MAKE(TC_H_CLSACT, TC_H_MIN_INGRESS);
	filter_info.kind = "clsact/ingress";
	ret = netlink_get_filter(sock, nl_pid, dev->अगरindex, handle,
				 dump_filter_nlmsg, &filter_info);
	अगर (ret)
		जाओ out;

	handle = TC_H_MAKE(TC_H_CLSACT, TC_H_MIN_EGRESS);
	filter_info.kind = "clsact/egress";
	ret = netlink_get_filter(sock, nl_pid, dev->अगरindex, handle,
				 dump_filter_nlmsg, &filter_info);
	अगर (ret)
		जाओ out;

out:
	मुक्त(tcinfo.handle_array);
	वापस 0;
पूर्ण

अटल पूर्णांक query_flow_dissector(काष्ठा bpf_attach_info *attach_info)
अणु
	__u32 attach_flags;
	__u32 prog_ids[1];
	__u32 prog_cnt;
	पूर्णांक err;
	पूर्णांक fd;

	fd = खोलो("/proc/self/ns/net", O_RDONLY);
	अगर (fd < 0) अणु
		p_err("can't open /proc/self/ns/net: %s",
		      म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण
	prog_cnt = ARRAY_SIZE(prog_ids);
	err = bpf_prog_query(fd, BPF_FLOW_DISSECTOR, 0,
			     &attach_flags, prog_ids, &prog_cnt);
	बंद(fd);
	अगर (err) अणु
		अगर (त्रुटि_सं == EINVAL) अणु
			/* Older kernel's don't support querying
			 * flow dissector programs.
			 */
			त्रुटि_सं = 0;
			वापस 0;
		पूर्ण
		p_err("can't query prog: %s", म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	अगर (prog_cnt == 1)
		attach_info->flow_dissector_id = prog_ids[0];

	वापस 0;
पूर्ण

अटल पूर्णांक net_parse_dev(पूर्णांक *argc, अक्षर ***argv)
अणु
	पूर्णांक अगरindex;

	अगर (is_prefix(**argv, "dev")) अणु
		NEXT_ARGP();

		अगरindex = अगर_nametoindex(**argv);
		अगर (!अगरindex)
			p_err("invalid devname %s", **argv);

		NEXT_ARGP();
	पूर्ण अन्यथा अणु
		p_err("expected 'dev', got: '%s'?", **argv);
		वापस -1;
	पूर्ण

	वापस अगरindex;
पूर्ण

अटल पूर्णांक करो_attach_detach_xdp(पूर्णांक progfd, क्रमागत net_attach_type attach_type,
				पूर्णांक अगरindex, bool overग_लिखो)
अणु
	__u32 flags = 0;

	अगर (!overग_लिखो)
		flags = XDP_FLAGS_UPDATE_IF_NOEXIST;
	अगर (attach_type == NET_ATTACH_TYPE_XDP_GENERIC)
		flags |= XDP_FLAGS_SKB_MODE;
	अगर (attach_type == NET_ATTACH_TYPE_XDP_DRIVER)
		flags |= XDP_FLAGS_DRV_MODE;
	अगर (attach_type == NET_ATTACH_TYPE_XDP_OFFLOAD)
		flags |= XDP_FLAGS_HW_MODE;

	वापस bpf_set_link_xdp_fd(अगरindex, progfd, flags);
पूर्ण

अटल पूर्णांक करो_attach(पूर्णांक argc, अक्षर **argv)
अणु
	क्रमागत net_attach_type attach_type;
	पूर्णांक progfd, अगरindex, err = 0;
	bool overग_लिखो = false;

	/* parse attach args */
	अगर (!REQ_ARGS(5))
		वापस -EINVAL;

	attach_type = parse_attach_type(*argv);
	अगर (attach_type == net_attach_type_size) अणु
		p_err("invalid net attach/detach type: %s", *argv);
		वापस -EINVAL;
	पूर्ण
	NEXT_ARG();

	progfd = prog_parse_fd(&argc, &argv);
	अगर (progfd < 0)
		वापस -EINVAL;

	अगरindex = net_parse_dev(&argc, &argv);
	अगर (अगरindex < 1) अणु
		err = -EINVAL;
		जाओ cleanup;
	पूर्ण

	अगर (argc) अणु
		अगर (is_prefix(*argv, "overwrite")) अणु
			overग_लिखो = true;
		पूर्ण अन्यथा अणु
			p_err("expected 'overwrite', got: '%s'?", *argv);
			err = -EINVAL;
			जाओ cleanup;
		पूर्ण
	पूर्ण

	/* attach xdp prog */
	अगर (is_prefix("xdp", attach_type_strings[attach_type]))
		err = करो_attach_detach_xdp(progfd, attach_type, अगरindex,
					   overग_लिखो);
	अगर (err) अणु
		p_err("interface %s attach failed: %s",
		      attach_type_strings[attach_type], म_त्रुटि(-err));
		जाओ cleanup;
	पूर्ण

	अगर (json_output)
		jsonw_null(json_wtr);
cleanup:
	बंद(progfd);
	वापस err;
पूर्ण

अटल पूर्णांक करो_detach(पूर्णांक argc, अक्षर **argv)
अणु
	क्रमागत net_attach_type attach_type;
	पूर्णांक progfd, अगरindex, err = 0;

	/* parse detach args */
	अगर (!REQ_ARGS(3))
		वापस -EINVAL;

	attach_type = parse_attach_type(*argv);
	अगर (attach_type == net_attach_type_size) अणु
		p_err("invalid net attach/detach type: %s", *argv);
		वापस -EINVAL;
	पूर्ण
	NEXT_ARG();

	अगरindex = net_parse_dev(&argc, &argv);
	अगर (अगरindex < 1)
		वापस -EINVAL;

	/* detach xdp prog */
	progfd = -1;
	अगर (is_prefix("xdp", attach_type_strings[attach_type]))
		err = करो_attach_detach_xdp(progfd, attach_type, अगरindex, शून्य);

	अगर (err < 0) अणु
		p_err("interface %s detach failed: %s",
		      attach_type_strings[attach_type], म_त्रुटि(-err));
		वापस err;
	पूर्ण

	अगर (json_output)
		jsonw_null(json_wtr);

	वापस 0;
पूर्ण

अटल पूर्णांक करो_show(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_attach_info attach_info = अणुपूर्ण;
	पूर्णांक i, sock, ret, filter_idx = -1;
	काष्ठा bpf_netdev_t dev_array;
	अचिन्हित पूर्णांक nl_pid = 0;
	अक्षर err_buf[256];

	अगर (argc == 2) अणु
		filter_idx = net_parse_dev(&argc, &argv);
		अगर (filter_idx < 1)
			वापस -1;
	पूर्ण अन्यथा अगर (argc != 0) अणु
		usage();
	पूर्ण

	ret = query_flow_dissector(&attach_info);
	अगर (ret)
		वापस -1;

	sock = netlink_खोलो(&nl_pid);
	अगर (sock < 0) अणु
		ख_लिखो(मानक_त्रुटि, "failed to open netlink sock\n");
		वापस -1;
	पूर्ण

	dev_array.devices = शून्य;
	dev_array.used_len = 0;
	dev_array.array_len = 0;
	dev_array.filter_idx = filter_idx;

	अगर (json_output)
		jsonw_start_array(json_wtr);
	NET_START_OBJECT;
	NET_START_ARRAY("xdp", "%s:\n");
	ret = netlink_get_link(sock, nl_pid, dump_link_nlmsg, &dev_array);
	NET_END_ARRAY("\n");

	अगर (!ret) अणु
		NET_START_ARRAY("tc", "%s:\n");
		क्रम (i = 0; i < dev_array.used_len; i++) अणु
			ret = show_dev_tc_bpf(sock, nl_pid,
					      &dev_array.devices[i]);
			अगर (ret)
				अवरोध;
		पूर्ण
		NET_END_ARRAY("\n");
	पूर्ण

	NET_START_ARRAY("flow_dissector", "%s:\n");
	अगर (attach_info.flow_dissector_id > 0)
		NET_DUMP_UINT("id", "id %u", attach_info.flow_dissector_id);
	NET_END_ARRAY("\n");

	NET_END_OBJECT;
	अगर (json_output)
		jsonw_end_array(json_wtr);

	अगर (ret) अणु
		अगर (json_output)
			jsonw_null(json_wtr);
		libbpf_म_त्रुटि(ret, err_buf, माप(err_buf));
		ख_लिखो(मानक_त्रुटि, "Error: %s\n", err_buf);
	पूर्ण
	मुक्त(dev_array.devices);
	बंद(sock);
	वापस ret;
पूर्ण

अटल पूर्णांक करो_help(पूर्णांक argc, अक्षर **argv)
अणु
	अगर (json_output) अणु
		jsonw_null(json_wtr);
		वापस 0;
	पूर्ण

	ख_लिखो(मानक_त्रुटि,
		"Usage: %1$s %2$s { show | list } [dev <devname>]\n"
		"       %1$s %2$s attach ATTACH_TYPE PROG dev <devname> [ overwrite ]\n"
		"       %1$s %2$s detach ATTACH_TYPE dev <devname>\n"
		"       %1$s %2$s help\n"
		"\n"
		"       " HELP_SPEC_PROGRAM "\n"
		"       ATTACH_TYPE := { xdp | xdpgeneric | xdpdrv | xdpoffload }\n"
		"\n"
		"Note: Only xdp and tc attachments are supported now.\n"
		"      For progs attached to cgroups, use \"bpftool cgroup\"\n"
		"      to dump program attachments. For program types\n"
		"      sk_{filter,skb,msg,reuseport} and lwt/seg6, please\n"
		"      consult iproute2.\n"
		"",
		bin_name, argv[-2]);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cmd cmds[] = अणु
	अणु "show",	करो_show पूर्ण,
	अणु "list",	करो_show पूर्ण,
	अणु "attach",	करो_attach पूर्ण,
	अणु "detach",	करो_detach पूर्ण,
	अणु "help",	करो_help पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

पूर्णांक करो_net(पूर्णांक argc, अक्षर **argv)
अणु
	वापस cmd_select(cmds, argc, argv, करो_help);
पूर्ण
