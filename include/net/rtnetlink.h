<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_RTNETLINK_H
#घोषणा __NET_RTNETLINK_H

#समावेश <linux/rtnetlink.h>
#समावेश <net/netlink.h>

प्रकार पूर्णांक (*rtnl_करोit_func)(काष्ठा sk_buff *, काष्ठा nlmsghdr *,
			      काष्ठा netlink_ext_ack *);
प्रकार पूर्णांक (*rtnl_dumpit_func)(काष्ठा sk_buff *, काष्ठा netlink_callback *);

क्रमागत rtnl_link_flags अणु
	RTNL_FLAG_DOIT_UNLOCKED = 1,
पूर्ण;

व्योम rtnl_रेजिस्टर(पूर्णांक protocol, पूर्णांक msgtype,
		   rtnl_करोit_func, rtnl_dumpit_func, अचिन्हित पूर्णांक flags);
पूर्णांक rtnl_रेजिस्टर_module(काष्ठा module *owner, पूर्णांक protocol, पूर्णांक msgtype,
			 rtnl_करोit_func, rtnl_dumpit_func, अचिन्हित पूर्णांक flags);
पूर्णांक rtnl_unरेजिस्टर(पूर्णांक protocol, पूर्णांक msgtype);
व्योम rtnl_unरेजिस्टर_all(पूर्णांक protocol);

अटल अंतरभूत पूर्णांक rtnl_msg_family(स्थिर काष्ठा nlmsghdr *nlh)
अणु
	अगर (nlmsg_len(nlh) >= माप(काष्ठा rtgenmsg))
		वापस ((काष्ठा rtgenmsg *) nlmsg_data(nlh))->rtgen_family;
	अन्यथा
		वापस AF_UNSPEC;
पूर्ण

/**
 *	काष्ठा rtnl_link_ops - rtnetlink link operations
 *
 *	@list: Used पूर्णांकernally
 *	@kind: Identअगरier
 *	@netns_refund: Physical device, move to init_net on netns निकास
 *	@maxtype: Highest device specअगरic netlink attribute number
 *	@policy: Netlink policy क्रम device specअगरic attribute validation
 *	@validate: Optional validation function क्रम netlink/changelink parameters
 *	@priv_size: माप net_device निजी space
 *	@setup: net_device setup function
 *	@newlink: Function क्रम configuring and रेजिस्टरing a new device
 *	@changelink: Function क्रम changing parameters of an existing device
 *	@dellink: Function to हटाओ a device
 *	@get_size: Function to calculate required room क्रम dumping device
 *		   specअगरic netlink attributes
 *	@fill_info: Function to dump device specअगरic netlink attributes
 *	@get_xstats_size: Function to calculate required room क्रम dumping device
 *			  specअगरic statistics
 *	@fill_xstats: Function to dump device specअगरic statistics
 *	@get_num_tx_queues: Function to determine number of transmit queues
 *			    to create when creating a new device.
 *	@get_num_rx_queues: Function to determine number of receive queues
 *			    to create when creating a new device.
 *	@get_link_net: Function to get the i/o netns of the device
 *	@get_linkxstats_size: Function to calculate the required room क्रम
 *			      dumping device-specअगरic extended link stats
 *	@fill_linkxstats: Function to dump device-specअगरic extended link stats
 */
काष्ठा rtnl_link_ops अणु
	काष्ठा list_head	list;

	स्थिर अक्षर		*kind;

	माप_प्रकार			priv_size;
	व्योम			(*setup)(काष्ठा net_device *dev);

	bool			netns_refund;
	अचिन्हित पूर्णांक		maxtype;
	स्थिर काष्ठा nla_policy	*policy;
	पूर्णांक			(*validate)(काष्ठा nlattr *tb[],
					    काष्ठा nlattr *data[],
					    काष्ठा netlink_ext_ack *extack);

	पूर्णांक			(*newlink)(काष्ठा net *src_net,
					   काष्ठा net_device *dev,
					   काष्ठा nlattr *tb[],
					   काष्ठा nlattr *data[],
					   काष्ठा netlink_ext_ack *extack);
	पूर्णांक			(*changelink)(काष्ठा net_device *dev,
					      काष्ठा nlattr *tb[],
					      काष्ठा nlattr *data[],
					      काष्ठा netlink_ext_ack *extack);
	व्योम			(*dellink)(काष्ठा net_device *dev,
					   काष्ठा list_head *head);

	माप_प्रकार			(*get_size)(स्थिर काष्ठा net_device *dev);
	पूर्णांक			(*fill_info)(काष्ठा sk_buff *skb,
					     स्थिर काष्ठा net_device *dev);

	माप_प्रकार			(*get_xstats_size)(स्थिर काष्ठा net_device *dev);
	पूर्णांक			(*fill_xstats)(काष्ठा sk_buff *skb,
					       स्थिर काष्ठा net_device *dev);
	अचिन्हित पूर्णांक		(*get_num_tx_queues)(व्योम);
	अचिन्हित पूर्णांक		(*get_num_rx_queues)(व्योम);

	अचिन्हित पूर्णांक		slave_maxtype;
	स्थिर काष्ठा nla_policy	*slave_policy;
	पूर्णांक			(*slave_changelink)(काष्ठा net_device *dev,
						    काष्ठा net_device *slave_dev,
						    काष्ठा nlattr *tb[],
						    काष्ठा nlattr *data[],
						    काष्ठा netlink_ext_ack *extack);
	माप_प्रकार			(*get_slave_size)(स्थिर काष्ठा net_device *dev,
						  स्थिर काष्ठा net_device *slave_dev);
	पूर्णांक			(*fill_slave_info)(काष्ठा sk_buff *skb,
						   स्थिर काष्ठा net_device *dev,
						   स्थिर काष्ठा net_device *slave_dev);
	काष्ठा net		*(*get_link_net)(स्थिर काष्ठा net_device *dev);
	माप_प्रकार			(*get_linkxstats_size)(स्थिर काष्ठा net_device *dev,
						       पूर्णांक attr);
	पूर्णांक			(*fill_linkxstats)(काष्ठा sk_buff *skb,
						   स्थिर काष्ठा net_device *dev,
						   पूर्णांक *prividx, पूर्णांक attr);
पूर्ण;

पूर्णांक __rtnl_link_रेजिस्टर(काष्ठा rtnl_link_ops *ops);
व्योम __rtnl_link_unरेजिस्टर(काष्ठा rtnl_link_ops *ops);

पूर्णांक rtnl_link_रेजिस्टर(काष्ठा rtnl_link_ops *ops);
व्योम rtnl_link_unरेजिस्टर(काष्ठा rtnl_link_ops *ops);

/**
 * 	काष्ठा rtnl_af_ops - rtnetlink address family operations
 *
 *	@list: Used पूर्णांकernally
 * 	@family: Address family
 * 	@fill_link_af: Function to fill IFLA_AF_SPEC with address family
 * 		       specअगरic netlink attributes.
 * 	@get_link_af_size: Function to calculate size of address family specअगरic
 * 			   netlink attributes.
 *	@validate_link_af: Validate a IFLA_AF_SPEC attribute, must check attr
 *			   क्रम invalid configuration settings.
 * 	@set_link_af: Function to parse a IFLA_AF_SPEC attribute and modअगरy
 *		      net_device accordingly.
 */
काष्ठा rtnl_af_ops अणु
	काष्ठा list_head	list;
	पूर्णांक			family;

	पूर्णांक			(*fill_link_af)(काष्ठा sk_buff *skb,
						स्थिर काष्ठा net_device *dev,
						u32 ext_filter_mask);
	माप_प्रकार			(*get_link_af_size)(स्थिर काष्ठा net_device *dev,
						    u32 ext_filter_mask);

	पूर्णांक			(*validate_link_af)(स्थिर काष्ठा net_device *dev,
						    स्थिर काष्ठा nlattr *attr);
	पूर्णांक			(*set_link_af)(काष्ठा net_device *dev,
					       स्थिर काष्ठा nlattr *attr,
					       काष्ठा netlink_ext_ack *extack);
	पूर्णांक			(*fill_stats_af)(काष्ठा sk_buff *skb,
						 स्थिर काष्ठा net_device *dev);
	माप_प्रकार			(*get_stats_af_size)(स्थिर काष्ठा net_device *dev);
पूर्ण;

व्योम rtnl_af_रेजिस्टर(काष्ठा rtnl_af_ops *ops);
व्योम rtnl_af_unरेजिस्टर(काष्ठा rtnl_af_ops *ops);

काष्ठा net *rtnl_link_get_net(काष्ठा net *src_net, काष्ठा nlattr *tb[]);
काष्ठा net_device *rtnl_create_link(काष्ठा net *net, स्थिर अक्षर *अगरname,
				    अचिन्हित अक्षर name_assign_type,
				    स्थिर काष्ठा rtnl_link_ops *ops,
				    काष्ठा nlattr *tb[],
				    काष्ठा netlink_ext_ack *extack);
पूर्णांक rtnl_delete_link(काष्ठा net_device *dev);
पूर्णांक rtnl_configure_link(काष्ठा net_device *dev, स्थिर काष्ठा अगरinfomsg *अगरm);

पूर्णांक rtnl_nla_parse_अगरla(काष्ठा nlattr **tb, स्थिर काष्ठा nlattr *head, पूर्णांक len,
			काष्ठा netlink_ext_ack *exterr);
काष्ठा net *rtnl_get_net_ns_capable(काष्ठा sock *sk, पूर्णांक netnsid);

#घोषणा MODULE_ALIAS_RTNL_LINK(kind) MODULE_ALIAS("rtnl-link-" kind)

#पूर्ण_अगर
