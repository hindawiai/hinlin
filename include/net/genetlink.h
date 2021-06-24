<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_GENERIC_NETLINK_H
#घोषणा __NET_GENERIC_NETLINK_H

#समावेश <linux/genetlink.h>
#समावेश <net/netlink.h>
#समावेश <net/net_namespace.h>

#घोषणा GENLMSG_DEFAULT_SIZE (NLMSG_DEFAULT_SIZE - GENL_HDRLEN)

/**
 * काष्ठा genl_multicast_group - generic netlink multicast group
 * @name: name of the multicast group, names are per-family
 */
काष्ठा genl_multicast_group अणु
	अक्षर			name[GENL_NAMSIZ];
	u8			flags;
पूर्ण;

काष्ठा genl_ops;
काष्ठा genl_info;

/**
 * काष्ठा genl_family - generic netlink family
 * @id: protocol family identअगरier (निजी)
 * @hdrsize: length of user specअगरic header in bytes
 * @name: name of family
 * @version: protocol version
 * @maxattr: maximum number of attributes supported
 * @policy: netlink policy
 * @netnsok: set to true अगर the family can handle network
 *	namespaces and should be presented in all of them
 * @parallel_ops: operations can be called in parallel and aren't
 *	synchronized by the core genetlink code
 * @pre_करोit: called beक्रमe an operation's करोit callback, it may
 *	करो additional, common, filtering and वापस an error
 * @post_करोit: called after an operation's करोit callback, it may
 *	unकरो operations करोne by pre_करोit, क्रम example release locks
 * @mcgrps: multicast groups used by this family
 * @n_mcgrps: number of multicast groups
 * @mcgrp_offset: starting number of multicast group IDs in this family
 *	(निजी)
 * @ops: the operations supported by this family
 * @n_ops: number of operations supported by this family
 * @small_ops: the small-काष्ठा operations supported by this family
 * @n_small_ops: number of small-काष्ठा operations supported by this family
 */
काष्ठा genl_family अणु
	पूर्णांक			id;		/* निजी */
	अचिन्हित पूर्णांक		hdrsize;
	अक्षर			name[GENL_NAMSIZ];
	अचिन्हित पूर्णांक		version;
	अचिन्हित पूर्णांक		maxattr;
	अचिन्हित पूर्णांक		mcgrp_offset;	/* निजी */
	u8			netnsok:1;
	u8			parallel_ops:1;
	u8			n_ops;
	u8			n_small_ops;
	u8			n_mcgrps;
	स्थिर काष्ठा nla_policy *policy;
	पूर्णांक			(*pre_करोit)(स्थिर काष्ठा genl_ops *ops,
					    काष्ठा sk_buff *skb,
					    काष्ठा genl_info *info);
	व्योम			(*post_करोit)(स्थिर काष्ठा genl_ops *ops,
					     काष्ठा sk_buff *skb,
					     काष्ठा genl_info *info);
	स्थिर काष्ठा genl_ops *	ops;
	स्थिर काष्ठा genl_small_ops *small_ops;
	स्थिर काष्ठा genl_multicast_group *mcgrps;
	काष्ठा module		*module;
पूर्ण;

/**
 * काष्ठा genl_info - receiving inक्रमmation
 * @snd_seq: sending sequence number
 * @snd_portid: netlink portid of sender
 * @nlhdr: netlink message header
 * @genlhdr: generic netlink message header
 * @userhdr: user specअगरic header
 * @attrs: netlink attributes
 * @_net: network namespace
 * @user_ptr: user poपूर्णांकers
 * @extack: extended ACK report काष्ठा
 */
काष्ठा genl_info अणु
	u32			snd_seq;
	u32			snd_portid;
	काष्ठा nlmsghdr *	nlhdr;
	काष्ठा genlmsghdr *	genlhdr;
	व्योम *			userhdr;
	काष्ठा nlattr **	attrs;
	possible_net_t		_net;
	व्योम *			user_ptr[2];
	काष्ठा netlink_ext_ack *extack;
पूर्ण;

अटल अंतरभूत काष्ठा net *genl_info_net(काष्ठा genl_info *info)
अणु
	वापस पढ़ो_pnet(&info->_net);
पूर्ण

अटल अंतरभूत व्योम genl_info_net_set(काष्ठा genl_info *info, काष्ठा net *net)
अणु
	ग_लिखो_pnet(&info->_net, net);
पूर्ण

#घोषणा GENL_SET_ERR_MSG(info, msg) NL_SET_ERR_MSG((info)->extack, msg)

क्रमागत genl_validate_flags अणु
	GENL_DONT_VALIDATE_STRICT		= BIT(0),
	GENL_DONT_VALIDATE_DUMP			= BIT(1),
	GENL_DONT_VALIDATE_DUMP_STRICT		= BIT(2),
पूर्ण;

/**
 * काष्ठा genl_small_ops - generic netlink operations (small version)
 * @cmd: command identअगरier
 * @पूर्णांकernal_flags: flags used by the family
 * @flags: flags
 * @validate: validation flags from क्रमागत genl_validate_flags
 * @करोit: standard command callback
 * @dumpit: callback क्रम dumpers
 *
 * This is a cut-करोwn version of काष्ठा genl_ops क्रम users who करोn't need
 * most of the ancillary infra and want to save space.
 */
काष्ठा genl_small_ops अणु
	पूर्णांक	(*करोit)(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
	पूर्णांक	(*dumpit)(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);
	u8	cmd;
	u8	पूर्णांकernal_flags;
	u8	flags;
	u8	validate;
पूर्ण;

/**
 * काष्ठा genl_ops - generic netlink operations
 * @cmd: command identअगरier
 * @पूर्णांकernal_flags: flags used by the family
 * @flags: flags
 * @maxattr: maximum number of attributes supported
 * @policy: netlink policy (takes precedence over family policy)
 * @validate: validation flags from क्रमागत genl_validate_flags
 * @करोit: standard command callback
 * @start: start callback क्रम dumps
 * @dumpit: callback क्रम dumpers
 * @करोne: completion callback क्रम dumps
 */
काष्ठा genl_ops अणु
	पूर्णांक		       (*करोit)(काष्ठा sk_buff *skb,
				       काष्ठा genl_info *info);
	पूर्णांक		       (*start)(काष्ठा netlink_callback *cb);
	पूर्णांक		       (*dumpit)(काष्ठा sk_buff *skb,
					 काष्ठा netlink_callback *cb);
	पूर्णांक		       (*करोne)(काष्ठा netlink_callback *cb);
	स्थिर काष्ठा nla_policy *policy;
	अचिन्हित पूर्णांक		maxattr;
	u8			cmd;
	u8			पूर्णांकernal_flags;
	u8			flags;
	u8			validate;
पूर्ण;

/**
 * काष्ठा genl_info - info that is available during dumpit op call
 * @family: generic netlink family - क्रम पूर्णांकernal genl code usage
 * @ops: generic netlink ops - क्रम पूर्णांकernal genl code usage
 * @attrs: netlink attributes
 */
काष्ठा genl_dumpit_info अणु
	स्थिर काष्ठा genl_family *family;
	काष्ठा genl_ops op;
	काष्ठा nlattr **attrs;
पूर्ण;

अटल अंतरभूत स्थिर काष्ठा genl_dumpit_info *
genl_dumpit_info(काष्ठा netlink_callback *cb)
अणु
	वापस cb->data;
पूर्ण

पूर्णांक genl_रेजिस्टर_family(काष्ठा genl_family *family);
पूर्णांक genl_unरेजिस्टर_family(स्थिर काष्ठा genl_family *family);
व्योम genl_notअगरy(स्थिर काष्ठा genl_family *family, काष्ठा sk_buff *skb,
		 काष्ठा genl_info *info, u32 group, gfp_t flags);

व्योम *genlmsg_put(काष्ठा sk_buff *skb, u32 portid, u32 seq,
		  स्थिर काष्ठा genl_family *family, पूर्णांक flags, u8 cmd);

/**
 * genlmsg_nlhdr - Obtain netlink header from user specअगरied header
 * @user_hdr: user header as वापसed from genlmsg_put()
 *
 * Returns poपूर्णांकer to netlink header.
 */
अटल अंतरभूत काष्ठा nlmsghdr *genlmsg_nlhdr(व्योम *user_hdr)
अणु
	वापस (काष्ठा nlmsghdr *)((अक्षर *)user_hdr -
				   GENL_HDRLEN -
				   NLMSG_HDRLEN);
पूर्ण

/**
 * genlmsg_parse_deprecated - parse attributes of a genetlink message
 * @nlh: netlink message header
 * @family: genetlink message family
 * @tb: destination array with maxtype+1 elements
 * @maxtype: maximum attribute type to be expected
 * @policy: validation policy
 * @extack: extended ACK report काष्ठा
 */
अटल अंतरभूत पूर्णांक genlmsg_parse_deprecated(स्थिर काष्ठा nlmsghdr *nlh,
					   स्थिर काष्ठा genl_family *family,
					   काष्ठा nlattr *tb[], पूर्णांक maxtype,
					   स्थिर काष्ठा nla_policy *policy,
					   काष्ठा netlink_ext_ack *extack)
अणु
	वापस __nlmsg_parse(nlh, family->hdrsize + GENL_HDRLEN, tb, maxtype,
			     policy, NL_VALIDATE_LIBERAL, extack);
पूर्ण

/**
 * genlmsg_parse - parse attributes of a genetlink message
 * @nlh: netlink message header
 * @family: genetlink message family
 * @tb: destination array with maxtype+1 elements
 * @maxtype: maximum attribute type to be expected
 * @policy: validation policy
 * @extack: extended ACK report काष्ठा
 */
अटल अंतरभूत पूर्णांक genlmsg_parse(स्थिर काष्ठा nlmsghdr *nlh,
				स्थिर काष्ठा genl_family *family,
				काष्ठा nlattr *tb[], पूर्णांक maxtype,
				स्थिर काष्ठा nla_policy *policy,
				काष्ठा netlink_ext_ack *extack)
अणु
	वापस __nlmsg_parse(nlh, family->hdrsize + GENL_HDRLEN, tb, maxtype,
			     policy, NL_VALIDATE_STRICT, extack);
पूर्ण

/**
 * genl_dump_check_consistent - check अगर sequence is consistent and advertise अगर not
 * @cb: netlink callback काष्ठाure that stores the sequence number
 * @user_hdr: user header as वापसed from genlmsg_put()
 *
 * Cf. nl_dump_check_consistent(), this just provides a wrapper to make it
 * simpler to use with generic netlink.
 */
अटल अंतरभूत व्योम genl_dump_check_consistent(काष्ठा netlink_callback *cb,
					      व्योम *user_hdr)
अणु
	nl_dump_check_consistent(cb, genlmsg_nlhdr(user_hdr));
पूर्ण

/**
 * genlmsg_put_reply - Add generic netlink header to a reply message
 * @skb: socket buffer holding the message
 * @info: receiver info
 * @family: generic netlink family
 * @flags: netlink message flags
 * @cmd: generic netlink command
 *
 * Returns poपूर्णांकer to user specअगरic header
 */
अटल अंतरभूत व्योम *genlmsg_put_reply(काष्ठा sk_buff *skb,
				      काष्ठा genl_info *info,
				      स्थिर काष्ठा genl_family *family,
				      पूर्णांक flags, u8 cmd)
अणु
	वापस genlmsg_put(skb, info->snd_portid, info->snd_seq, family,
			   flags, cmd);
पूर्ण

/**
 * genlmsg_end - Finalize a generic netlink message
 * @skb: socket buffer the message is stored in
 * @hdr: user specअगरic header
 */
अटल अंतरभूत व्योम genlmsg_end(काष्ठा sk_buff *skb, व्योम *hdr)
अणु
	nlmsg_end(skb, hdr - GENL_HDRLEN - NLMSG_HDRLEN);
पूर्ण

/**
 * genlmsg_cancel - Cancel स्थिरruction of a generic netlink message
 * @skb: socket buffer the message is stored in
 * @hdr: generic netlink message header
 */
अटल अंतरभूत व्योम genlmsg_cancel(काष्ठा sk_buff *skb, व्योम *hdr)
अणु
	अगर (hdr)
		nlmsg_cancel(skb, hdr - GENL_HDRLEN - NLMSG_HDRLEN);
पूर्ण

/**
 * genlmsg_multicast_netns - multicast a netlink message to a specअगरic netns
 * @family: the generic netlink family
 * @net: the net namespace
 * @skb: netlink message as socket buffer
 * @portid: own netlink portid to aव्योम sending to yourself
 * @group: offset of multicast group in groups array
 * @flags: allocation flags
 */
अटल अंतरभूत पूर्णांक genlmsg_multicast_netns(स्थिर काष्ठा genl_family *family,
					  काष्ठा net *net, काष्ठा sk_buff *skb,
					  u32 portid, अचिन्हित पूर्णांक group, gfp_t flags)
अणु
	अगर (WARN_ON_ONCE(group >= family->n_mcgrps))
		वापस -EINVAL;
	group = family->mcgrp_offset + group;
	वापस nlmsg_multicast(net->genl_sock, skb, portid, group, flags);
पूर्ण

/**
 * genlmsg_multicast - multicast a netlink message to the शेष netns
 * @family: the generic netlink family
 * @skb: netlink message as socket buffer
 * @portid: own netlink portid to aव्योम sending to yourself
 * @group: offset of multicast group in groups array
 * @flags: allocation flags
 */
अटल अंतरभूत पूर्णांक genlmsg_multicast(स्थिर काष्ठा genl_family *family,
				    काष्ठा sk_buff *skb, u32 portid,
				    अचिन्हित पूर्णांक group, gfp_t flags)
अणु
	वापस genlmsg_multicast_netns(family, &init_net, skb,
				       portid, group, flags);
पूर्ण

/**
 * genlmsg_multicast_allns - multicast a netlink message to all net namespaces
 * @family: the generic netlink family
 * @skb: netlink message as socket buffer
 * @portid: own netlink portid to aव्योम sending to yourself
 * @group: offset of multicast group in groups array
 * @flags: allocation flags
 *
 * This function must hold the RTNL or rcu_पढ़ो_lock().
 */
पूर्णांक genlmsg_multicast_allns(स्थिर काष्ठा genl_family *family,
			    काष्ठा sk_buff *skb, u32 portid,
			    अचिन्हित पूर्णांक group, gfp_t flags);

/**
 * genlmsg_unicast - unicast a netlink message
 * @skb: netlink message as socket buffer
 * @portid: netlink portid of the destination socket
 */
अटल अंतरभूत पूर्णांक genlmsg_unicast(काष्ठा net *net, काष्ठा sk_buff *skb, u32 portid)
अणु
	वापस nlmsg_unicast(net->genl_sock, skb, portid);
पूर्ण

/**
 * genlmsg_reply - reply to a request
 * @skb: netlink message to be sent back
 * @info: receiver inक्रमmation
 */
अटल अंतरभूत पूर्णांक genlmsg_reply(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	वापस genlmsg_unicast(genl_info_net(info), skb, info->snd_portid);
पूर्ण

/**
 * gennlmsg_data - head of message payload
 * @gnlh: genetlink message header
 */
अटल अंतरभूत व्योम *genlmsg_data(स्थिर काष्ठा genlmsghdr *gnlh)
अणु
	वापस ((अचिन्हित अक्षर *) gnlh + GENL_HDRLEN);
पूर्ण

/**
 * genlmsg_len - length of message payload
 * @gnlh: genetlink message header
 */
अटल अंतरभूत पूर्णांक genlmsg_len(स्थिर काष्ठा genlmsghdr *gnlh)
अणु
	काष्ठा nlmsghdr *nlh = (काष्ठा nlmsghdr *)((अचिन्हित अक्षर *)gnlh -
							NLMSG_HDRLEN);
	वापस (nlh->nlmsg_len - GENL_HDRLEN - NLMSG_HDRLEN);
पूर्ण

/**
 * genlmsg_msg_size - length of genetlink message not including padding
 * @payload: length of message payload
 */
अटल अंतरभूत पूर्णांक genlmsg_msg_size(पूर्णांक payload)
अणु
	वापस GENL_HDRLEN + payload;
पूर्ण

/**
 * genlmsg_total_size - length of genetlink message including padding
 * @payload: length of message payload
 */
अटल अंतरभूत पूर्णांक genlmsg_total_size(पूर्णांक payload)
अणु
	वापस NLMSG_ALIGN(genlmsg_msg_size(payload));
पूर्ण

/**
 * genlmsg_new - Allocate a new generic netlink message
 * @payload: size of the message payload
 * @flags: the type of memory to allocate.
 */
अटल अंतरभूत काष्ठा sk_buff *genlmsg_new(माप_प्रकार payload, gfp_t flags)
अणु
	वापस nlmsg_new(genlmsg_total_size(payload), flags);
पूर्ण

/**
 * genl_set_err - report error to genetlink broadcast listeners
 * @family: the generic netlink family
 * @net: the network namespace to report the error to
 * @portid: the PORTID of a process that we want to skip (अगर any)
 * @group: the broadcast group that will notice the error
 * 	(this is the offset of the multicast group in the groups array)
 * @code: error code, must be negative (as usual in kernelspace)
 *
 * This function वापसs the number of broadcast listeners that have set the
 * NETLINK_RECV_NO_ENOBUFS socket option.
 */
अटल अंतरभूत पूर्णांक genl_set_err(स्थिर काष्ठा genl_family *family,
			       काष्ठा net *net, u32 portid,
			       u32 group, पूर्णांक code)
अणु
	अगर (WARN_ON_ONCE(group >= family->n_mcgrps))
		वापस -EINVAL;
	group = family->mcgrp_offset + group;
	वापस netlink_set_err(net->genl_sock, portid, group, code);
पूर्ण

अटल अंतरभूत पूर्णांक genl_has_listeners(स्थिर काष्ठा genl_family *family,
				     काष्ठा net *net, अचिन्हित पूर्णांक group)
अणु
	अगर (WARN_ON_ONCE(group >= family->n_mcgrps))
		वापस -EINVAL;
	group = family->mcgrp_offset + group;
	वापस netlink_has_listeners(net->genl_sock, group);
पूर्ण
#पूर्ण_अगर	/* __NET_GENERIC_NETLINK_H */
