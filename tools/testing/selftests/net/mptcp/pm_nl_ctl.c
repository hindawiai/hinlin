<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <त्रुटिसं.स>
#समावेश <error.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>

#समावेश <sys/socket.h>
#समावेश <sys/types.h>

#समावेश <arpa/inet.h>
#समावेश <net/अगर.h>

#समावेश <linux/rtnetlink.h>
#समावेश <linux/genetlink.h>

#समावेश "linux/mptcp.h"

#अगर_अघोषित MPTCP_PM_NAME
#घोषणा MPTCP_PM_NAME		"mptcp_pm"
#पूर्ण_अगर

अटल व्योम syntax(अक्षर *argv[])
अणु
	ख_लिखो(मानक_त्रुटि, "%s add|get|set|del|flush|dump|accept [<args>]\n", argv[0]);
	ख_लिखो(मानक_त्रुटि, "\tadd [flags signal|subflow|backup] [id <nr>] [dev <name>] <ip>\n");
	ख_लिखो(मानक_त्रुटि, "\tdel <id> [<ip>]\n");
	ख_लिखो(मानक_त्रुटि, "\tget <id>\n");
	ख_लिखो(मानक_त्रुटि, "\tset <ip> [flags backup|nobackup]\n");
	ख_लिखो(मानक_त्रुटि, "\tflush\n");
	ख_लिखो(मानक_त्रुटि, "\tdump\n");
	ख_लिखो(मानक_त्रुटि, "\tlimits [<rcv addr max> <subflow max>]\n");
	निकास(0);
पूर्ण

अटल पूर्णांक init_genl_req(अक्षर *data, पूर्णांक family, पूर्णांक cmd, पूर्णांक version)
अणु
	काष्ठा nlmsghdr *nh = (व्योम *)data;
	काष्ठा genlmsghdr *gh;
	पूर्णांक off = 0;

	nh->nlmsg_type = family;
	nh->nlmsg_flags = NLM_F_REQUEST;
	nh->nlmsg_len = NLMSG_LENGTH(GENL_HDRLEN);
	off += NLMSG_ALIGN(माप(*nh));

	gh = (व्योम *)(data + off);
	gh->cmd = cmd;
	gh->version = version;
	off += NLMSG_ALIGN(माप(*gh));
	वापस off;
पूर्ण

अटल व्योम nl_error(काष्ठा nlmsghdr *nh)
अणु
	काष्ठा nlmsgerr *err = (काष्ठा nlmsgerr *)NLMSG_DATA(nh);
	पूर्णांक len = nh->nlmsg_len - माप(*nh);
	uपूर्णांक32_t off;

	अगर (len < माप(काष्ठा nlmsgerr))
		error(1, 0, "netlink error message truncated %d min %ld", len,
		      माप(काष्ठा nlmsgerr));

	अगर (!err->error) अणु
		/* check messages from kernel */
		काष्ठा rtattr *attrs = (काष्ठा rtattr *)NLMSG_DATA(nh);

		जबतक (RTA_OK(attrs, len)) अणु
			अगर (attrs->rta_type == NLMSGERR_ATTR_MSG)
				ख_लिखो(मानक_त्रुटि, "netlink ext ack msg: %s\n",
					(अक्षर *)RTA_DATA(attrs));
			अगर (attrs->rta_type == NLMSGERR_ATTR_OFFS) अणु
				स_नकल(&off, RTA_DATA(attrs), 4);
				ख_लिखो(मानक_त्रुटि, "netlink err off %d\n",
					(पूर्णांक)off);
			पूर्ण
			attrs = RTA_NEXT(attrs, len);
		पूर्ण
	पूर्ण अन्यथा अणु
		ख_लिखो(मानक_त्रुटि, "netlink error %d", err->error);
	पूर्ण
पूर्ण

/* करो a netlink command and, अगर max > 0, fetch the reply  */
अटल पूर्णांक करो_nl_req(पूर्णांक fd, काष्ठा nlmsghdr *nh, पूर्णांक len, पूर्णांक max)
अणु
	काष्ठा sockaddr_nl nladdr = अणु .nl_family = AF_NETLINK पूर्ण;
	socklen_t addr_len;
	व्योम *data = nh;
	पूर्णांक rem, ret;
	पूर्णांक err = 0;

	nh->nlmsg_len = len;
	ret = sendto(fd, data, len, 0, (व्योम *)&nladdr, माप(nladdr));
	अगर (ret != len)
		error(1, त्रुटि_सं, "send netlink: %uB != %uB\n", ret, len);
	अगर (max == 0)
		वापस 0;

	addr_len = माप(nladdr);
	rem = ret = recvfrom(fd, data, max, 0, (व्योम *)&nladdr, &addr_len);
	अगर (ret < 0)
		error(1, त्रुटि_सं, "recv netlink: %uB\n", ret);

	/* Beware: the NLMSG_NEXT macro updates the 'rem' argument */
	क्रम (; NLMSG_OK(nh, rem); nh = NLMSG_NEXT(nh, rem)) अणु
		अगर (nh->nlmsg_type == NLMSG_ERROR) अणु
			nl_error(nh);
			err = 1;
		पूर्ण
	पूर्ण
	अगर (err)
		error(1, 0, "bailing out due to netlink error[s]");
	वापस ret;
पूर्ण

अटल पूर्णांक genl_parse_getfamily(काष्ठा nlmsghdr *nlh)
अणु
	काष्ठा genlmsghdr *ghdr = NLMSG_DATA(nlh);
	पूर्णांक len = nlh->nlmsg_len;
	काष्ठा rtattr *attrs;

	अगर (nlh->nlmsg_type != GENL_ID_CTRL)
		error(1, त्रुटि_सं, "Not a controller message, len=%d type=0x%x\n",
		      nlh->nlmsg_len, nlh->nlmsg_type);

	len -= NLMSG_LENGTH(GENL_HDRLEN);

	अगर (len < 0)
		error(1, त्रुटि_सं, "wrong controller message len %d\n", len);

	अगर (ghdr->cmd != CTRL_CMD_NEWFAMILY)
		error(1, त्रुटि_सं, "Unknown controller command %d\n", ghdr->cmd);

	attrs = (काष्ठा rtattr *) ((अक्षर *) ghdr + GENL_HDRLEN);
	जबतक (RTA_OK(attrs, len)) अणु
		अगर (attrs->rta_type == CTRL_ATTR_FAMILY_ID)
			वापस *(__u16 *)RTA_DATA(attrs);
		attrs = RTA_NEXT(attrs, len);
	पूर्ण

	error(1, त्रुटि_सं, "can't find CTRL_ATTR_FAMILY_ID attr");
	वापस -1;
पूर्ण

अटल पूर्णांक resolve_mptcp_pm_netlink(पूर्णांक fd)
अणु
	अक्षर data[NLMSG_ALIGN(माप(काष्ठा nlmsghdr)) +
		  NLMSG_ALIGN(माप(काष्ठा genlmsghdr)) +
		  1024];
	काष्ठा nlmsghdr *nh;
	काष्ठा rtattr *rta;
	पूर्णांक namelen;
	पूर्णांक off = 0;

	स_रखो(data, 0, माप(data));
	nh = (व्योम *)data;
	off = init_genl_req(data, GENL_ID_CTRL, CTRL_CMD_GETFAMILY, 0);

	rta = (व्योम *)(data + off);
	namelen = म_माप(MPTCP_PM_NAME) + 1;
	rta->rta_type = CTRL_ATTR_FAMILY_NAME;
	rta->rta_len = RTA_LENGTH(namelen);
	स_नकल(RTA_DATA(rta), MPTCP_PM_NAME, namelen);
	off += NLMSG_ALIGN(rta->rta_len);

	करो_nl_req(fd, nh, off, माप(data));
	वापस genl_parse_getfamily((व्योम *)data);
पूर्ण

पूर्णांक add_addr(पूर्णांक fd, पूर्णांक pm_family, पूर्णांक argc, अक्षर *argv[])
अणु
	अक्षर data[NLMSG_ALIGN(माप(काष्ठा nlmsghdr)) +
		  NLMSG_ALIGN(माप(काष्ठा genlmsghdr)) +
		  1024];
	काष्ठा rtattr *rta, *nest;
	काष्ठा nlmsghdr *nh;
	u_पूर्णांक32_t flags = 0;
	u_पूर्णांक16_t family;
	पूर्णांक nest_start;
	u_पूर्णांक8_t id;
	पूर्णांक off = 0;
	पूर्णांक arg;

	स_रखो(data, 0, माप(data));
	nh = (व्योम *)data;
	off = init_genl_req(data, pm_family, MPTCP_PM_CMD_ADD_ADDR,
			    MPTCP_PM_VER);

	अगर (argc < 3)
		syntax(argv);

	nest_start = off;
	nest = (व्योम *)(data + off);
	nest->rta_type = NLA_F_NESTED | MPTCP_PM_ATTR_ADDR;
	nest->rta_len = RTA_LENGTH(0);
	off += NLMSG_ALIGN(nest->rta_len);

	/* addr data */
	rta = (व्योम *)(data + off);
	अगर (inet_pton(AF_INET, argv[2], RTA_DATA(rta))) अणु
		family = AF_INET;
		rta->rta_type = MPTCP_PM_ADDR_ATTR_ADDR4;
		rta->rta_len = RTA_LENGTH(4);
	पूर्ण अन्यथा अगर (inet_pton(AF_INET6, argv[2], RTA_DATA(rta))) अणु
		family = AF_INET6;
		rta->rta_type = MPTCP_PM_ADDR_ATTR_ADDR6;
		rta->rta_len = RTA_LENGTH(16);
	पूर्ण अन्यथा
		error(1, त्रुटि_सं, "can't parse ip %s", argv[2]);
	off += NLMSG_ALIGN(rta->rta_len);

	/* family */
	rta = (व्योम *)(data + off);
	rta->rta_type = MPTCP_PM_ADDR_ATTR_FAMILY;
	rta->rta_len = RTA_LENGTH(2);
	स_नकल(RTA_DATA(rta), &family, 2);
	off += NLMSG_ALIGN(rta->rta_len);

	क्रम (arg = 3; arg < argc; arg++) अणु
		अगर (!म_भेद(argv[arg], "flags")) अणु
			अक्षर *tok, *str;

			/* flags */
			अगर (++arg >= argc)
				error(1, 0, " missing flags value");

			/* करो not support flag list yet */
			क्रम (str = argv[arg]; (tok = म_मोहर(str, ","));
			     str = शून्य) अणु
				अगर (!म_भेद(tok, "subflow"))
					flags |= MPTCP_PM_ADDR_FLAG_SUBFLOW;
				अन्यथा अगर (!म_भेद(tok, "signal"))
					flags |= MPTCP_PM_ADDR_FLAG_SIGNAL;
				अन्यथा अगर (!म_भेद(tok, "backup"))
					flags |= MPTCP_PM_ADDR_FLAG_BACKUP;
				अन्यथा
					error(1, त्रुटि_सं,
					      "unknown flag %s", argv[arg]);
			पूर्ण

			rta = (व्योम *)(data + off);
			rta->rta_type = MPTCP_PM_ADDR_ATTR_FLAGS;
			rta->rta_len = RTA_LENGTH(4);
			स_नकल(RTA_DATA(rta), &flags, 4);
			off += NLMSG_ALIGN(rta->rta_len);
		पूर्ण अन्यथा अगर (!म_भेद(argv[arg], "id")) अणु
			अगर (++arg >= argc)
				error(1, 0, " missing id value");

			id = म_से_प(argv[arg]);
			rta = (व्योम *)(data + off);
			rta->rta_type = MPTCP_PM_ADDR_ATTR_ID;
			rta->rta_len = RTA_LENGTH(1);
			स_नकल(RTA_DATA(rta), &id, 1);
			off += NLMSG_ALIGN(rta->rta_len);
		पूर्ण अन्यथा अगर (!म_भेद(argv[arg], "dev")) अणु
			पूर्णांक32_t अगरindex;

			अगर (++arg >= argc)
				error(1, 0, " missing dev name");

			अगरindex = अगर_nametoindex(argv[arg]);
			अगर (!अगरindex)
				error(1, त्रुटि_सं, "unknown device %s", argv[arg]);

			rta = (व्योम *)(data + off);
			rta->rta_type = MPTCP_PM_ADDR_ATTR_IF_IDX;
			rta->rta_len = RTA_LENGTH(4);
			स_नकल(RTA_DATA(rta), &अगरindex, 4);
			off += NLMSG_ALIGN(rta->rta_len);
		पूर्ण अन्यथा अगर (!म_भेद(argv[arg], "port")) अणु
			u_पूर्णांक16_t port;

			अगर (++arg >= argc)
				error(1, 0, " missing port value");
			अगर (!(flags & MPTCP_PM_ADDR_FLAG_SIGNAL))
				error(1, 0, " flags must be signal when using port");

			port = म_से_प(argv[arg]);
			rta = (व्योम *)(data + off);
			rta->rta_type = MPTCP_PM_ADDR_ATTR_PORT;
			rta->rta_len = RTA_LENGTH(2);
			स_नकल(RTA_DATA(rta), &port, 2);
			off += NLMSG_ALIGN(rta->rta_len);
		पूर्ण अन्यथा
			error(1, 0, "unknown keyword %s", argv[arg]);
	पूर्ण
	nest->rta_len = off - nest_start;

	करो_nl_req(fd, nh, off, 0);
	वापस 0;
पूर्ण

पूर्णांक del_addr(पूर्णांक fd, पूर्णांक pm_family, पूर्णांक argc, अक्षर *argv[])
अणु
	अक्षर data[NLMSG_ALIGN(माप(काष्ठा nlmsghdr)) +
		  NLMSG_ALIGN(माप(काष्ठा genlmsghdr)) +
		  1024];
	काष्ठा rtattr *rta, *nest;
	काष्ठा nlmsghdr *nh;
	u_पूर्णांक16_t family;
	पूर्णांक nest_start;
	u_पूर्णांक8_t id;
	पूर्णांक off = 0;

	स_रखो(data, 0, माप(data));
	nh = (व्योम *)data;
	off = init_genl_req(data, pm_family, MPTCP_PM_CMD_DEL_ADDR,
			    MPTCP_PM_VER);

	/* the only argument is the address id (nonzero) */
	अगर (argc != 3 && argc != 4)
		syntax(argv);

	id = म_से_प(argv[2]);
	/* zero id with the IP address */
	अगर (!id && argc != 4)
		syntax(argv);

	nest_start = off;
	nest = (व्योम *)(data + off);
	nest->rta_type = NLA_F_NESTED | MPTCP_PM_ATTR_ADDR;
	nest->rta_len =  RTA_LENGTH(0);
	off += NLMSG_ALIGN(nest->rta_len);

	/* build a dummy addr with only the ID set */
	rta = (व्योम *)(data + off);
	rta->rta_type = MPTCP_PM_ADDR_ATTR_ID;
	rta->rta_len = RTA_LENGTH(1);
	स_नकल(RTA_DATA(rta), &id, 1);
	off += NLMSG_ALIGN(rta->rta_len);

	अगर (!id) अणु
		/* addr data */
		rta = (व्योम *)(data + off);
		अगर (inet_pton(AF_INET, argv[3], RTA_DATA(rta))) अणु
			family = AF_INET;
			rta->rta_type = MPTCP_PM_ADDR_ATTR_ADDR4;
			rta->rta_len = RTA_LENGTH(4);
		पूर्ण अन्यथा अगर (inet_pton(AF_INET6, argv[3], RTA_DATA(rta))) अणु
			family = AF_INET6;
			rta->rta_type = MPTCP_PM_ADDR_ATTR_ADDR6;
			rta->rta_len = RTA_LENGTH(16);
		पूर्ण अन्यथा अणु
			error(1, त्रुटि_सं, "can't parse ip %s", argv[3]);
		पूर्ण
		off += NLMSG_ALIGN(rta->rta_len);

		/* family */
		rta = (व्योम *)(data + off);
		rta->rta_type = MPTCP_PM_ADDR_ATTR_FAMILY;
		rta->rta_len = RTA_LENGTH(2);
		स_नकल(RTA_DATA(rta), &family, 2);
		off += NLMSG_ALIGN(rta->rta_len);
	पूर्ण
	nest->rta_len = off - nest_start;

	करो_nl_req(fd, nh, off, 0);
	वापस 0;
पूर्ण

अटल व्योम prपूर्णांक_addr(काष्ठा rtattr *attrs, पूर्णांक len)
अणु
	uपूर्णांक16_t family = 0;
	uपूर्णांक16_t port = 0;
	अक्षर str[1024];
	uपूर्णांक32_t flags;
	uपूर्णांक8_t id;

	जबतक (RTA_OK(attrs, len)) अणु
		अगर (attrs->rta_type == MPTCP_PM_ADDR_ATTR_FAMILY)
			स_नकल(&family, RTA_DATA(attrs), 2);
		अगर (attrs->rta_type == MPTCP_PM_ADDR_ATTR_PORT)
			स_नकल(&port, RTA_DATA(attrs), 2);
		अगर (attrs->rta_type == MPTCP_PM_ADDR_ATTR_ADDR4) अणु
			अगर (family != AF_INET)
				error(1, त्रुटि_सं, "wrong IP (v4) for family %d",
				      family);
			inet_ntop(AF_INET, RTA_DATA(attrs), str, माप(str));
			म_लिखो("%s", str);
			अगर (port)
				म_लिखो(" %d", port);
		पूर्ण
		अगर (attrs->rta_type == MPTCP_PM_ADDR_ATTR_ADDR6) अणु
			अगर (family != AF_INET6)
				error(1, त्रुटि_सं, "wrong IP (v6) for family %d",
				      family);
			inet_ntop(AF_INET6, RTA_DATA(attrs), str, माप(str));
			म_लिखो("%s", str);
			अगर (port)
				म_लिखो(" %d", port);
		पूर्ण
		अगर (attrs->rta_type == MPTCP_PM_ADDR_ATTR_ID) अणु
			स_नकल(&id, RTA_DATA(attrs), 1);
			म_लिखो("id %d ", id);
		पूर्ण
		अगर (attrs->rta_type == MPTCP_PM_ADDR_ATTR_FLAGS) अणु
			स_नकल(&flags, RTA_DATA(attrs), 4);

			म_लिखो("flags ");
			अगर (flags & MPTCP_PM_ADDR_FLAG_SIGNAL) अणु
				म_लिखो("signal");
				flags &= ~MPTCP_PM_ADDR_FLAG_SIGNAL;
				अगर (flags)
					म_लिखो(",");
			पूर्ण

			अगर (flags & MPTCP_PM_ADDR_FLAG_SUBFLOW) अणु
				म_लिखो("subflow");
				flags &= ~MPTCP_PM_ADDR_FLAG_SUBFLOW;
				अगर (flags)
					म_लिखो(",");
			पूर्ण

			अगर (flags & MPTCP_PM_ADDR_FLAG_BACKUP) अणु
				म_लिखो("backup");
				flags &= ~MPTCP_PM_ADDR_FLAG_BACKUP;
				अगर (flags)
					म_लिखो(",");
			पूर्ण

			/* bump unknown flags, अगर any */
			अगर (flags)
				म_लिखो("0x%x", flags);
			म_लिखो(" ");
		पूर्ण
		अगर (attrs->rta_type == MPTCP_PM_ADDR_ATTR_IF_IDX) अणु
			अक्षर name[IF_NAMESIZE], *ret;
			पूर्णांक32_t अगरindex;

			स_नकल(&अगरindex, RTA_DATA(attrs), 4);
			ret = अगर_indextoname(अगरindex, name);
			अगर (ret)
				म_लिखो("dev %s ", ret);
			अन्यथा
				म_लिखो("dev unknown/%d", अगरindex);
		पूर्ण

		attrs = RTA_NEXT(attrs, len);
	पूर्ण
	म_लिखो("\n");
पूर्ण

अटल व्योम prपूर्णांक_addrs(काष्ठा nlmsghdr *nh, पूर्णांक pm_family, पूर्णांक total_len)
अणु
	काष्ठा rtattr *attrs;

	क्रम (; NLMSG_OK(nh, total_len); nh = NLMSG_NEXT(nh, total_len)) अणु
		पूर्णांक len = nh->nlmsg_len;

		अगर (nh->nlmsg_type == NLMSG_DONE)
			अवरोध;
		अगर (nh->nlmsg_type == NLMSG_ERROR)
			nl_error(nh);
		अगर (nh->nlmsg_type != pm_family)
			जारी;

		len -= NLMSG_LENGTH(GENL_HDRLEN);
		attrs = (काष्ठा rtattr *) ((अक्षर *) NLMSG_DATA(nh) +
					   GENL_HDRLEN);
		जबतक (RTA_OK(attrs, len)) अणु
			अगर (attrs->rta_type ==
			    (MPTCP_PM_ATTR_ADDR | NLA_F_NESTED))
				prपूर्णांक_addr((व्योम *)RTA_DATA(attrs),
					   attrs->rta_len);
			attrs = RTA_NEXT(attrs, len);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक get_addr(पूर्णांक fd, पूर्णांक pm_family, पूर्णांक argc, अक्षर *argv[])
अणु
	अक्षर data[NLMSG_ALIGN(माप(काष्ठा nlmsghdr)) +
		  NLMSG_ALIGN(माप(काष्ठा genlmsghdr)) +
		  1024];
	काष्ठा rtattr *rta, *nest;
	काष्ठा nlmsghdr *nh;
	पूर्णांक nest_start;
	u_पूर्णांक8_t id;
	पूर्णांक off = 0;

	स_रखो(data, 0, माप(data));
	nh = (व्योम *)data;
	off = init_genl_req(data, pm_family, MPTCP_PM_CMD_GET_ADDR,
			    MPTCP_PM_VER);

	/* the only argument is the address id */
	अगर (argc != 3)
		syntax(argv);

	id = म_से_प(argv[2]);

	nest_start = off;
	nest = (व्योम *)(data + off);
	nest->rta_type = NLA_F_NESTED | MPTCP_PM_ATTR_ADDR;
	nest->rta_len =  RTA_LENGTH(0);
	off += NLMSG_ALIGN(nest->rta_len);

	/* build a dummy addr with only the ID set */
	rta = (व्योम *)(data + off);
	rta->rta_type = MPTCP_PM_ADDR_ATTR_ID;
	rta->rta_len = RTA_LENGTH(1);
	स_नकल(RTA_DATA(rta), &id, 1);
	off += NLMSG_ALIGN(rta->rta_len);
	nest->rta_len = off - nest_start;

	prपूर्णांक_addrs(nh, pm_family, करो_nl_req(fd, nh, off, माप(data)));
	वापस 0;
पूर्ण

पूर्णांक dump_addrs(पूर्णांक fd, पूर्णांक pm_family, पूर्णांक argc, अक्षर *argv[])
अणु
	अक्षर data[NLMSG_ALIGN(माप(काष्ठा nlmsghdr)) +
		  NLMSG_ALIGN(माप(काष्ठा genlmsghdr)) +
		  1024];
	pid_t pid = getpid();
	काष्ठा nlmsghdr *nh;
	पूर्णांक off = 0;

	स_रखो(data, 0, माप(data));
	nh = (व्योम *)data;
	off = init_genl_req(data, pm_family, MPTCP_PM_CMD_GET_ADDR,
			    MPTCP_PM_VER);
	nh->nlmsg_flags |= NLM_F_DUMP;
	nh->nlmsg_seq = 1;
	nh->nlmsg_pid = pid;
	nh->nlmsg_len = off;

	prपूर्णांक_addrs(nh, pm_family, करो_nl_req(fd, nh, off, माप(data)));
	वापस 0;
पूर्ण

पूर्णांक flush_addrs(पूर्णांक fd, पूर्णांक pm_family, पूर्णांक argc, अक्षर *argv[])
अणु
	अक्षर data[NLMSG_ALIGN(माप(काष्ठा nlmsghdr)) +
		  NLMSG_ALIGN(माप(काष्ठा genlmsghdr)) +
		  1024];
	काष्ठा nlmsghdr *nh;
	पूर्णांक off = 0;

	स_रखो(data, 0, माप(data));
	nh = (व्योम *)data;
	off = init_genl_req(data, pm_family, MPTCP_PM_CMD_FLUSH_ADDRS,
			    MPTCP_PM_VER);

	करो_nl_req(fd, nh, off, 0);
	वापस 0;
पूर्ण

अटल व्योम prपूर्णांक_limits(काष्ठा nlmsghdr *nh, पूर्णांक pm_family, पूर्णांक total_len)
अणु
	काष्ठा rtattr *attrs;
	uपूर्णांक32_t max;

	क्रम (; NLMSG_OK(nh, total_len); nh = NLMSG_NEXT(nh, total_len)) अणु
		पूर्णांक len = nh->nlmsg_len;

		अगर (nh->nlmsg_type == NLMSG_DONE)
			अवरोध;
		अगर (nh->nlmsg_type == NLMSG_ERROR)
			nl_error(nh);
		अगर (nh->nlmsg_type != pm_family)
			जारी;

		len -= NLMSG_LENGTH(GENL_HDRLEN);
		attrs = (काष्ठा rtattr *) ((अक्षर *) NLMSG_DATA(nh) +
					   GENL_HDRLEN);
		जबतक (RTA_OK(attrs, len)) अणु
			पूर्णांक type = attrs->rta_type;

			अगर (type != MPTCP_PM_ATTR_RCV_ADD_ADDRS &&
			    type != MPTCP_PM_ATTR_SUBFLOWS)
				जाओ next;

			स_नकल(&max, RTA_DATA(attrs), 4);
			म_लिखो("%s %u\n", type == MPTCP_PM_ATTR_SUBFLOWS ?
					  "subflows" : "accept", max);

next:
			attrs = RTA_NEXT(attrs, len);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक get_set_limits(पूर्णांक fd, पूर्णांक pm_family, पूर्णांक argc, अक्षर *argv[])
अणु
	अक्षर data[NLMSG_ALIGN(माप(काष्ठा nlmsghdr)) +
		  NLMSG_ALIGN(माप(काष्ठा genlmsghdr)) +
		  1024];
	uपूर्णांक32_t rcv_addr = 0, subflows = 0;
	पूर्णांक cmd, len = माप(data);
	काष्ठा nlmsghdr *nh;
	पूर्णांक off = 0;

	/* limit */
	अगर (argc == 4) अणु
		rcv_addr = म_से_प(argv[2]);
		subflows = म_से_प(argv[3]);
		cmd = MPTCP_PM_CMD_SET_LIMITS;
	पूर्ण अन्यथा अणु
		cmd = MPTCP_PM_CMD_GET_LIMITS;
	पूर्ण

	स_रखो(data, 0, माप(data));
	nh = (व्योम *)data;
	off = init_genl_req(data, pm_family, cmd, MPTCP_PM_VER);

	/* limit */
	अगर (cmd == MPTCP_PM_CMD_SET_LIMITS) अणु
		काष्ठा rtattr *rta = (व्योम *)(data + off);

		rta->rta_type = MPTCP_PM_ATTR_RCV_ADD_ADDRS;
		rta->rta_len = RTA_LENGTH(4);
		स_नकल(RTA_DATA(rta), &rcv_addr, 4);
		off += NLMSG_ALIGN(rta->rta_len);

		rta = (व्योम *)(data + off);
		rta->rta_type = MPTCP_PM_ATTR_SUBFLOWS;
		rta->rta_len = RTA_LENGTH(4);
		स_नकल(RTA_DATA(rta), &subflows, 4);
		off += NLMSG_ALIGN(rta->rta_len);

		/* करो not expect a reply */
		len = 0;
	पूर्ण

	len = करो_nl_req(fd, nh, off, len);
	अगर (cmd == MPTCP_PM_CMD_GET_LIMITS)
		prपूर्णांक_limits(nh, pm_family, len);
	वापस 0;
पूर्ण

पूर्णांक set_flags(पूर्णांक fd, पूर्णांक pm_family, पूर्णांक argc, अक्षर *argv[])
अणु
	अक्षर data[NLMSG_ALIGN(माप(काष्ठा nlmsghdr)) +
		  NLMSG_ALIGN(माप(काष्ठा genlmsghdr)) +
		  1024];
	काष्ठा rtattr *rta, *nest;
	काष्ठा nlmsghdr *nh;
	u_पूर्णांक32_t flags = 0;
	u_पूर्णांक16_t family;
	पूर्णांक nest_start;
	पूर्णांक off = 0;
	पूर्णांक arg;

	स_रखो(data, 0, माप(data));
	nh = (व्योम *)data;
	off = init_genl_req(data, pm_family, MPTCP_PM_CMD_SET_FLAGS,
			    MPTCP_PM_VER);

	अगर (argc < 3)
		syntax(argv);

	nest_start = off;
	nest = (व्योम *)(data + off);
	nest->rta_type = NLA_F_NESTED | MPTCP_PM_ATTR_ADDR;
	nest->rta_len = RTA_LENGTH(0);
	off += NLMSG_ALIGN(nest->rta_len);

	/* addr data */
	rta = (व्योम *)(data + off);
	अगर (inet_pton(AF_INET, argv[2], RTA_DATA(rta))) अणु
		family = AF_INET;
		rta->rta_type = MPTCP_PM_ADDR_ATTR_ADDR4;
		rta->rta_len = RTA_LENGTH(4);
	पूर्ण अन्यथा अगर (inet_pton(AF_INET6, argv[2], RTA_DATA(rta))) अणु
		family = AF_INET6;
		rta->rta_type = MPTCP_PM_ADDR_ATTR_ADDR6;
		rta->rta_len = RTA_LENGTH(16);
	पूर्ण अन्यथा अणु
		error(1, त्रुटि_सं, "can't parse ip %s", argv[2]);
	पूर्ण
	off += NLMSG_ALIGN(rta->rta_len);

	/* family */
	rta = (व्योम *)(data + off);
	rta->rta_type = MPTCP_PM_ADDR_ATTR_FAMILY;
	rta->rta_len = RTA_LENGTH(2);
	स_नकल(RTA_DATA(rta), &family, 2);
	off += NLMSG_ALIGN(rta->rta_len);

	क्रम (arg = 3; arg < argc; arg++) अणु
		अगर (!म_भेद(argv[arg], "flags")) अणु
			अक्षर *tok, *str;

			/* flags */
			अगर (++arg >= argc)
				error(1, 0, " missing flags value");

			/* करो not support flag list yet */
			क्रम (str = argv[arg]; (tok = म_मोहर(str, ","));
			     str = शून्य) अणु
				अगर (!म_भेद(tok, "backup"))
					flags |= MPTCP_PM_ADDR_FLAG_BACKUP;
				अन्यथा अगर (म_भेद(tok, "nobackup"))
					error(1, त्रुटि_सं,
					      "unknown flag %s", argv[arg]);
			पूर्ण

			rta = (व्योम *)(data + off);
			rta->rta_type = MPTCP_PM_ADDR_ATTR_FLAGS;
			rta->rta_len = RTA_LENGTH(4);
			स_नकल(RTA_DATA(rta), &flags, 4);
			off += NLMSG_ALIGN(rta->rta_len);
		पूर्ण अन्यथा अणु
			error(1, 0, "unknown keyword %s", argv[arg]);
		पूर्ण
	पूर्ण
	nest->rta_len = off - nest_start;

	करो_nl_req(fd, nh, off, 0);
	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक fd, pm_family;

	अगर (argc < 2)
		syntax(argv);

	fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_GENERIC);
	अगर (fd == -1)
		error(1, त्रुटि_सं, "socket netlink");

	pm_family = resolve_mptcp_pm_netlink(fd);

	अगर (!म_भेद(argv[1], "add"))
		वापस add_addr(fd, pm_family, argc, argv);
	अन्यथा अगर (!म_भेद(argv[1], "del"))
		वापस del_addr(fd, pm_family, argc, argv);
	अन्यथा अगर (!म_भेद(argv[1], "flush"))
		वापस flush_addrs(fd, pm_family, argc, argv);
	अन्यथा अगर (!म_भेद(argv[1], "get"))
		वापस get_addr(fd, pm_family, argc, argv);
	अन्यथा अगर (!म_भेद(argv[1], "dump"))
		वापस dump_addrs(fd, pm_family, argc, argv);
	अन्यथा अगर (!म_भेद(argv[1], "limits"))
		वापस get_set_limits(fd, pm_family, argc, argv);
	अन्यथा अगर (!म_भेद(argv[1], "set"))
		वापस set_flags(fd, pm_family, argc, argv);

	ख_लिखो(मानक_त्रुटि, "unknown sub-command: %s", argv[1]);
	syntax(argv);
	वापस 0;
पूर्ण
