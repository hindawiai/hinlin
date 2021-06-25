<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _RDMA_NETLINK_H
#घोषणा _RDMA_NETLINK_H

#समावेश <linux/netlink.h>
#समावेश <uapi/rdma/rdma_netlink.h>

क्रमागत अणु
	RDMA_NLDEV_ATTR_EMPTY_STRING = 1,
	RDMA_NLDEV_ATTR_ENTRY_STRLEN = 16,
	RDMA_NLDEV_ATTR_CHARDEV_TYPE_SIZE = 32,
पूर्ण;

काष्ठा rdma_nl_cbs अणु
	पूर्णांक (*करोit)(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		    काष्ठा netlink_ext_ack *extack);
	पूर्णांक (*dump)(काष्ठा sk_buff *skb, काष्ठा netlink_callback *nlcb);
	u8 flags;
पूर्ण;

क्रमागत rdma_nl_flags अणु
	/* Require CAP_NET_ADMIN */
	RDMA_NL_ADMIN_PERM	= 1 << 0,
पूर्ण;

/* Define this module as providing netlink services क्रम NETLINK_RDMA, with
 * index _index.  Since the client indexes were setup in a uapi header as an
 * क्रमागत and we करो no want to change that, the user must supply the expanded
 * स्थिरant as well and the compiler checks they are the same.
 */
#घोषणा MODULE_ALIAS_RDMA_NETLINK(_index, _val)                                \
	अटल अंतरभूत व्योम __chk_##_index(व्योम)                                \
	अणु                                                                      \
		BUILD_BUG_ON(_index != _val);                                  \
	पूर्ण                                                                      \
	MODULE_ALIAS("rdma-netlink-subsys-" __stringअगरy(_val))

/**
 * Register client in RDMA netlink.
 * @index: Index of the added client
 * @cb_table: A table क्रम op->callback
 */
व्योम rdma_nl_रेजिस्टर(अचिन्हित पूर्णांक index,
		      स्थिर काष्ठा rdma_nl_cbs cb_table[]);

/**
 * Remove a client from IB netlink.
 * @index: Index of the हटाओd IB client.
 */
व्योम rdma_nl_unरेजिस्टर(अचिन्हित पूर्णांक index);

/**
 * Put a new message in a supplied skb.
 * @skb: The netlink skb.
 * @nlh: Poपूर्णांकer to put the header of the new netlink message.
 * @seq: The message sequence number.
 * @len: The requested message length to allocate.
 * @client: Calling IB netlink client.
 * @op: message content op.
 * Returns the allocated buffer on success and शून्य on failure.
 */
व्योम *ibnl_put_msg(काष्ठा sk_buff *skb, काष्ठा nlmsghdr **nlh, पूर्णांक seq,
		   पूर्णांक len, पूर्णांक client, पूर्णांक op, पूर्णांक flags);
/**
 * Put a new attribute in a supplied skb.
 * @skb: The netlink skb.
 * @nlh: Header of the netlink message to append the attribute to.
 * @len: The length of the attribute data.
 * @data: The attribute data to put.
 * @type: The attribute type.
 * Returns the 0 and a negative error code on failure.
 */
पूर्णांक ibnl_put_attr(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		  पूर्णांक len, व्योम *data, पूर्णांक type);

/**
 * Send the supplied skb to a specअगरic userspace PID.
 * @net: Net namespace in which to send the skb
 * @skb: The netlink skb
 * @pid: Userspace netlink process ID
 * Returns 0 on success or a negative error code.
 */
पूर्णांक rdma_nl_unicast(काष्ठा net *net, काष्ठा sk_buff *skb, u32 pid);

/**
 * Send, with रुको/1 retry, the supplied skb to a specअगरic userspace PID.
 * @net: Net namespace in which to send the skb
 * @skb: The netlink skb
 * @pid: Userspace netlink process ID
 * Returns 0 on success or a negative error code.
 */
पूर्णांक rdma_nl_unicast_रुको(काष्ठा net *net, काष्ठा sk_buff *skb, __u32 pid);

/**
 * Send the supplied skb to a netlink group.
 * @net: Net namespace in which to send the skb
 * @skb: The netlink skb
 * @group: Netlink group ID
 * @flags: allocation flags
 * Returns 0 on success or a negative error code.
 */
पूर्णांक rdma_nl_multicast(काष्ठा net *net, काष्ठा sk_buff *skb,
		      अचिन्हित पूर्णांक group, gfp_t flags);

/**
 * Check अगर there are any listeners to the netlink group
 * @group: the netlink group ID
 * Returns true on success or false अगर no listeners.
 */
bool rdma_nl_chk_listeners(अचिन्हित पूर्णांक group);

काष्ठा rdma_link_ops अणु
	काष्ठा list_head list;
	स्थिर अक्षर *type;
	पूर्णांक (*newlink)(स्थिर अक्षर *ibdev_name, काष्ठा net_device *ndev);
पूर्ण;

व्योम rdma_link_रेजिस्टर(काष्ठा rdma_link_ops *ops);
व्योम rdma_link_unरेजिस्टर(काष्ठा rdma_link_ops *ops);

#घोषणा MODULE_ALIAS_RDMA_LINK(type) MODULE_ALIAS("rdma-link-" type)
#घोषणा MODULE_ALIAS_RDMA_CLIENT(type) MODULE_ALIAS("rdma-client-" type)

#पूर्ण_अगर /* _RDMA_NETLINK_H */
