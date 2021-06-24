<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2018 Facebook */

#समावेश <मानककोष.स>
#समावेश <memory.h>
#समावेश <unistd.h>
#समावेश <linux/bpf.h>
#समावेश <linux/rtnetlink.h>
#समावेश <sys/socket.h>
#समावेश <त्रुटिसं.स>
#समावेश <समय.स>

#समावेश "bpf.h"
#समावेश "libbpf.h"
#समावेश "libbpf_internal.h"
#समावेश "nlattr.h"

#अगर_अघोषित SOL_NETLINK
#घोषणा SOL_NETLINK 270
#पूर्ण_अगर

प्रकार पूर्णांक (*libbpf_dump_nlmsg_t)(व्योम *cookie, व्योम *msg, काष्ठा nlattr **tb);

प्रकार पूर्णांक (*__dump_nlmsg_t)(काष्ठा nlmsghdr *nlmsg, libbpf_dump_nlmsg_t,
			      व्योम *cookie);

काष्ठा xdp_id_md अणु
	पूर्णांक अगरindex;
	__u32 flags;
	काष्ठा xdp_link_info info;
पूर्ण;

अटल पूर्णांक libbpf_netlink_खोलो(__u32 *nl_pid)
अणु
	काष्ठा sockaddr_nl sa;
	socklen_t addrlen;
	पूर्णांक one = 1, ret;
	पूर्णांक sock;

	स_रखो(&sa, 0, माप(sa));
	sa.nl_family = AF_NETLINK;

	sock = socket(AF_NETLINK, SOCK_RAW | SOCK_CLOEXEC, NETLINK_ROUTE);
	अगर (sock < 0)
		वापस -त्रुटि_सं;

	अगर (setsockopt(sock, SOL_NETLINK, NETLINK_EXT_ACK,
		       &one, माप(one)) < 0) अणु
		pr_warn("Netlink error reporting not supported\n");
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

अटल पूर्णांक bpf_netlink_recv(पूर्णांक sock, __u32 nl_pid, पूर्णांक seq,
			    __dump_nlmsg_t _fn, libbpf_dump_nlmsg_t fn,
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

		क्रम (nh = (काष्ठा nlmsghdr *)buf; NLMSG_OK(nh, len);
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

अटल पूर्णांक __bpf_set_link_xdp_fd_replace(पूर्णांक अगरindex, पूर्णांक fd, पूर्णांक old_fd,
					 __u32 flags)
अणु
	पूर्णांक sock, seq = 0, ret;
	काष्ठा nlattr *nla, *nla_xdp;
	काष्ठा अणु
		काष्ठा nlmsghdr  nh;
		काष्ठा अगरinfomsg अगरinfo;
		अक्षर             attrbuf[64];
	पूर्ण req;
	__u32 nl_pid = 0;

	sock = libbpf_netlink_खोलो(&nl_pid);
	अगर (sock < 0)
		वापस sock;

	स_रखो(&req, 0, माप(req));
	req.nh.nlmsg_len = NLMSG_LENGTH(माप(काष्ठा अगरinfomsg));
	req.nh.nlmsg_flags = NLM_F_REQUEST | NLM_F_ACK;
	req.nh.nlmsg_type = RTM_SETLINK;
	req.nh.nlmsg_pid = 0;
	req.nh.nlmsg_seq = ++seq;
	req.अगरinfo.अगरi_family = AF_UNSPEC;
	req.अगरinfo.अगरi_index = अगरindex;

	/* started nested attribute क्रम XDP */
	nla = (काष्ठा nlattr *)(((अक्षर *)&req)
				+ NLMSG_ALIGN(req.nh.nlmsg_len));
	nla->nla_type = NLA_F_NESTED | IFLA_XDP;
	nla->nla_len = NLA_HDRLEN;

	/* add XDP fd */
	nla_xdp = (काष्ठा nlattr *)((अक्षर *)nla + nla->nla_len);
	nla_xdp->nla_type = IFLA_XDP_FD;
	nla_xdp->nla_len = NLA_HDRLEN + माप(पूर्णांक);
	स_नकल((अक्षर *)nla_xdp + NLA_HDRLEN, &fd, माप(fd));
	nla->nla_len += nla_xdp->nla_len;

	/* अगर user passed in any flags, add those too */
	अगर (flags) अणु
		nla_xdp = (काष्ठा nlattr *)((अक्षर *)nla + nla->nla_len);
		nla_xdp->nla_type = IFLA_XDP_FLAGS;
		nla_xdp->nla_len = NLA_HDRLEN + माप(flags);
		स_नकल((अक्षर *)nla_xdp + NLA_HDRLEN, &flags, माप(flags));
		nla->nla_len += nla_xdp->nla_len;
	पूर्ण

	अगर (flags & XDP_FLAGS_REPLACE) अणु
		nla_xdp = (काष्ठा nlattr *)((अक्षर *)nla + nla->nla_len);
		nla_xdp->nla_type = IFLA_XDP_EXPECTED_FD;
		nla_xdp->nla_len = NLA_HDRLEN + माप(old_fd);
		स_नकल((अक्षर *)nla_xdp + NLA_HDRLEN, &old_fd, माप(old_fd));
		nla->nla_len += nla_xdp->nla_len;
	पूर्ण

	req.nh.nlmsg_len += NLA_ALIGN(nla->nla_len);

	अगर (send(sock, &req, req.nh.nlmsg_len, 0) < 0) अणु
		ret = -त्रुटि_सं;
		जाओ cleanup;
	पूर्ण
	ret = bpf_netlink_recv(sock, nl_pid, seq, शून्य, शून्य, शून्य);

cleanup:
	बंद(sock);
	वापस ret;
पूर्ण

पूर्णांक bpf_set_link_xdp_fd_opts(पूर्णांक अगरindex, पूर्णांक fd, __u32 flags,
			     स्थिर काष्ठा bpf_xdp_set_link_opts *opts)
अणु
	पूर्णांक old_fd = -1;

	अगर (!OPTS_VALID(opts, bpf_xdp_set_link_opts))
		वापस -EINVAL;

	अगर (OPTS_HAS(opts, old_fd)) अणु
		old_fd = OPTS_GET(opts, old_fd, -1);
		flags |= XDP_FLAGS_REPLACE;
	पूर्ण

	वापस __bpf_set_link_xdp_fd_replace(अगरindex, fd,
					     old_fd,
					     flags);
पूर्ण

पूर्णांक bpf_set_link_xdp_fd(पूर्णांक अगरindex, पूर्णांक fd, __u32 flags)
अणु
	वापस __bpf_set_link_xdp_fd_replace(अगरindex, fd, 0, flags);
पूर्ण

अटल पूर्णांक __dump_link_nlmsg(काष्ठा nlmsghdr *nlh,
			     libbpf_dump_nlmsg_t dump_link_nlmsg, व्योम *cookie)
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

अटल पूर्णांक get_xdp_info(व्योम *cookie, व्योम *msg, काष्ठा nlattr **tb)
अणु
	काष्ठा nlattr *xdp_tb[IFLA_XDP_MAX + 1];
	काष्ठा xdp_id_md *xdp_id = cookie;
	काष्ठा अगरinfomsg *अगरinfo = msg;
	पूर्णांक ret;

	अगर (xdp_id->अगरindex && xdp_id->अगरindex != अगरinfo->अगरi_index)
		वापस 0;

	अगर (!tb[IFLA_XDP])
		वापस 0;

	ret = libbpf_nla_parse_nested(xdp_tb, IFLA_XDP_MAX, tb[IFLA_XDP], शून्य);
	अगर (ret)
		वापस ret;

	अगर (!xdp_tb[IFLA_XDP_ATTACHED])
		वापस 0;

	xdp_id->info.attach_mode = libbpf_nla_getattr_u8(
		xdp_tb[IFLA_XDP_ATTACHED]);

	अगर (xdp_id->info.attach_mode == XDP_ATTACHED_NONE)
		वापस 0;

	अगर (xdp_tb[IFLA_XDP_PROG_ID])
		xdp_id->info.prog_id = libbpf_nla_getattr_u32(
			xdp_tb[IFLA_XDP_PROG_ID]);

	अगर (xdp_tb[IFLA_XDP_SKB_PROG_ID])
		xdp_id->info.skb_prog_id = libbpf_nla_getattr_u32(
			xdp_tb[IFLA_XDP_SKB_PROG_ID]);

	अगर (xdp_tb[IFLA_XDP_DRV_PROG_ID])
		xdp_id->info.drv_prog_id = libbpf_nla_getattr_u32(
			xdp_tb[IFLA_XDP_DRV_PROG_ID]);

	अगर (xdp_tb[IFLA_XDP_HW_PROG_ID])
		xdp_id->info.hw_prog_id = libbpf_nla_getattr_u32(
			xdp_tb[IFLA_XDP_HW_PROG_ID]);

	वापस 0;
पूर्ण

अटल पूर्णांक libbpf_nl_get_link(पूर्णांक sock, अचिन्हित पूर्णांक nl_pid,
			      libbpf_dump_nlmsg_t dump_link_nlmsg, व्योम *cookie);

पूर्णांक bpf_get_link_xdp_info(पूर्णांक अगरindex, काष्ठा xdp_link_info *info,
			  माप_प्रकार info_size, __u32 flags)
अणु
	काष्ठा xdp_id_md xdp_id = अणुपूर्ण;
	पूर्णांक sock, ret;
	__u32 nl_pid = 0;
	__u32 mask;

	अगर (flags & ~XDP_FLAGS_MASK || !info_size)
		वापस -EINVAL;

	/* Check whether the single अणुHW,DRV,SKBपूर्ण mode is set */
	flags &= (XDP_FLAGS_SKB_MODE | XDP_FLAGS_DRV_MODE | XDP_FLAGS_HW_MODE);
	mask = flags - 1;
	अगर (flags && flags & mask)
		वापस -EINVAL;

	sock = libbpf_netlink_खोलो(&nl_pid);
	अगर (sock < 0)
		वापस sock;

	xdp_id.अगरindex = अगरindex;
	xdp_id.flags = flags;

	ret = libbpf_nl_get_link(sock, nl_pid, get_xdp_info, &xdp_id);
	अगर (!ret) अणु
		माप_प्रकार sz = min(info_size, माप(xdp_id.info));

		स_नकल(info, &xdp_id.info, sz);
		स_रखो((व्योम *) info + sz, 0, info_size - sz);
	पूर्ण

	बंद(sock);
	वापस ret;
पूर्ण

अटल __u32 get_xdp_id(काष्ठा xdp_link_info *info, __u32 flags)
अणु
	flags &= XDP_FLAGS_MODES;

	अगर (info->attach_mode != XDP_ATTACHED_MULTI && !flags)
		वापस info->prog_id;
	अगर (flags & XDP_FLAGS_DRV_MODE)
		वापस info->drv_prog_id;
	अगर (flags & XDP_FLAGS_HW_MODE)
		वापस info->hw_prog_id;
	अगर (flags & XDP_FLAGS_SKB_MODE)
		वापस info->skb_prog_id;

	वापस 0;
पूर्ण

पूर्णांक bpf_get_link_xdp_id(पूर्णांक अगरindex, __u32 *prog_id, __u32 flags)
अणु
	काष्ठा xdp_link_info info;
	पूर्णांक ret;

	ret = bpf_get_link_xdp_info(अगरindex, &info, माप(info), flags);
	अगर (!ret)
		*prog_id = get_xdp_id(&info, flags);

	वापस ret;
पूर्ण

पूर्णांक libbpf_nl_get_link(पूर्णांक sock, अचिन्हित पूर्णांक nl_pid,
		       libbpf_dump_nlmsg_t dump_link_nlmsg, व्योम *cookie)
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

	वापस bpf_netlink_recv(sock, nl_pid, seq, __dump_link_nlmsg,
				dump_link_nlmsg, cookie);
पूर्ण
