<शैली गुरु>
/*
 * Copyright (c) 2014 Intel Corporation. All rights reserved.
 * Copyright (c) 2014 Chelsio, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer in the करोcumentation and/or other materials
 *	  provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#अगर_अघोषित _IWPM_UTIL_H
#घोषणा _IWPM_UTIL_H

#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>
#समावेश <linux/jhash.h>
#समावेश <linux/kref.h>
#समावेश <net/netlink.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <rdma/iw_porपंचांगap.h>
#समावेश <rdma/rdma_netlink.h>


#घोषणा IWPM_NL_RETRANS		3
#घोषणा IWPM_NL_TIMEOUT		(10*HZ)
#घोषणा IWPM_MAPINFO_SKB_COUNT	20

#घोषणा IWPM_PID_UNDEFINED     -1
#घोषणा IWPM_PID_UNAVAILABLE   -2

#घोषणा IWPM_REG_UNDEF          0x01
#घोषणा IWPM_REG_VALID          0x02
#घोषणा IWPM_REG_INCOMPL        0x04

काष्ठा iwpm_nlmsg_request अणु
	काष्ठा list_head    inprocess_list;
	__u32               nlmsg_seq;
	व्योम                *req_buffer;
	u8	            nl_client;
	u8                  request_करोne;
	u16                 err_code;
	काष्ठा semaphore    sem;
	काष्ठा kref         kref;
पूर्ण;

काष्ठा iwpm_mapping_info अणु
	काष्ठा hlist_node hlist_node;
	काष्ठा sockaddr_storage local_sockaddr;
	काष्ठा sockaddr_storage mapped_sockaddr;
	u8     nl_client;
	u32    map_flags;
पूर्ण;

काष्ठा iwpm_remote_info अणु
	काष्ठा hlist_node hlist_node;
	काष्ठा sockaddr_storage remote_sockaddr;
	काष्ठा sockaddr_storage mapped_loc_sockaddr;
	काष्ठा sockaddr_storage mapped_rem_sockaddr;
	u8     nl_client;
पूर्ण;

काष्ठा iwpm_admin_data अणु
	atomic_t refcount;
	atomic_t nlmsg_seq;
	पूर्णांक      client_list[RDMA_NL_NUM_CLIENTS];
	u32      reg_list[RDMA_NL_NUM_CLIENTS];
पूर्ण;

/**
 * iwpm_get_nlmsg_request - Allocate and initialize netlink message request
 * @nlmsg_seq: Sequence number of the netlink message
 * @nl_client: The index of the netlink client
 * @gfp: Indicates how the memory क्रम the request should be allocated
 *
 * Returns the newly allocated netlink request object अगर successful,
 * otherwise वापसs शून्य
 */
काष्ठा iwpm_nlmsg_request *iwpm_get_nlmsg_request(__u32 nlmsg_seq,
						u8 nl_client, gfp_t gfp);

/**
 * iwpm_मुक्त_nlmsg_request - Deallocate netlink message request
 * @kref: Holds reference of netlink message request
 */
व्योम iwpm_मुक्त_nlmsg_request(काष्ठा kref *kref);

/**
 * iwpm_find_nlmsg_request - Find netlink message request in the request list
 * @echo_seq: Sequence number of the netlink request to find
 *
 * Returns the found netlink message request,
 * अगर not found, वापसs शून्य
 */
काष्ठा iwpm_nlmsg_request *iwpm_find_nlmsg_request(__u32 echo_seq);

/**
 * iwpm_रुको_complete_req - Block जबतक servicing the netlink request
 * @nlmsg_request: Netlink message request to service
 *
 * Wakes up, after the request is completed or expired
 * Returns 0 अगर the request is complete without error
 */
पूर्णांक iwpm_रुको_complete_req(काष्ठा iwpm_nlmsg_request *nlmsg_request);

/**
 * iwpm_get_nlmsg_seq - Get the sequence number क्रम a netlink
 *			message to send to the port mapper
 *
 * Returns the sequence number क्रम the netlink message.
 */
पूर्णांक iwpm_get_nlmsg_seq(व्योम);

/**
 * iwpm_add_remote_info - Add remote address info of the connecting peer
 *                    to the remote info hash table
 * @reminfo: The remote info to be added
 */
व्योम iwpm_add_remote_info(काष्ठा iwpm_remote_info *reminfo);

/**
 * iwpm_valid_client - Check अगर the port mapper client is valid
 * @nl_client: The index of the netlink client
 *
 * Valid clients need to call iwpm_init() beक्रमe using
 * the port mapper
 */
पूर्णांक iwpm_valid_client(u8 nl_client);

/**
 * iwpm_set_valid - Set the port mapper client to valid or not
 * @nl_client: The index of the netlink client
 * @valid: 1 अगर valid or 0 अगर invalid
 */
व्योम iwpm_set_valid(u8 nl_client, पूर्णांक valid);

/**
 * iwpm_check_registration - Check अगर the client registration
 *			      matches the given one
 * @nl_client: The index of the netlink client
 * @reg: The given registration type to compare with
 *
 * Call iwpm_रेजिस्टर_pid() to रेजिस्टर a client
 * Returns true अगर the client registration matches reg,
 * otherwise वापसs false
 */
u32 iwpm_check_registration(u8 nl_client, u32 reg);

/**
 * iwpm_set_registration - Set the client registration
 * @nl_client: The index of the netlink client
 * @reg: Registration type to set
 */
व्योम iwpm_set_registration(u8 nl_client, u32 reg);

/**
 * iwpm_get_registration
 * @nl_client: The index of the netlink client
 *
 * Returns the client registration type
 */
u32 iwpm_get_registration(u8 nl_client);

/**
 * iwpm_send_mapinfo - Send local and mapped IPv4/IPv6 address info of
 *                     a client to the user space port mapper
 * @nl_client: The index of the netlink client
 * @iwpm_pid: The pid of the user space port mapper
 *
 * If successful, वापसs the number of sent mapping info records
 */
पूर्णांक iwpm_send_mapinfo(u8 nl_client, पूर्णांक iwpm_pid);

/**
 * iwpm_mapinfo_available - Check अगर any mapping info records is available
 *		            in the hash table
 *
 * Returns 1 अगर mapping inक्रमmation is available, otherwise वापसs 0
 */
पूर्णांक iwpm_mapinfo_available(व्योम);

/**
 * iwpm_compare_sockaddr - Compare two sockaddr storage काष्ठाs
 * @a_sockaddr: first sockaddr to compare
 * @b_sockaddr: second sockaddr to compare
 *
 * Return: 0 अगर they are holding the same ip/tcp address info,
 * otherwise वापसs 1
 */
पूर्णांक iwpm_compare_sockaddr(काष्ठा sockaddr_storage *a_sockaddr,
			काष्ठा sockaddr_storage *b_sockaddr);

/**
 * iwpm_validate_nlmsg_attr - Check क्रम शून्य netlink attributes
 * @nltb: Holds address of each netlink message attributes
 * @nla_count: Number of netlink message attributes
 *
 * Returns error अगर any of the nla_count attributes is शून्य
 */
अटल अंतरभूत पूर्णांक iwpm_validate_nlmsg_attr(काष्ठा nlattr *nltb[],
					   पूर्णांक nla_count)
अणु
	पूर्णांक i;
	क्रम (i = 1; i < nla_count; i++) अणु
		अगर (!nltb[i])
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * iwpm_create_nlmsg - Allocate skb and क्रमm a netlink message
 * @nl_op: Netlink message opcode
 * @nlh: Holds address of the netlink message header in skb
 * @nl_client: The index of the netlink client
 *
 * Returns the newly allcated skb, or शून्य अगर the tailroom of the skb
 * is insufficient to store the message header and payload
 */
काष्ठा sk_buff *iwpm_create_nlmsg(u32 nl_op, काष्ठा nlmsghdr **nlh,
					पूर्णांक nl_client);

/**
 * iwpm_parse_nlmsg - Validate and parse the received netlink message
 * @cb: Netlink callback काष्ठाure
 * @policy_max: Maximum attribute type to be expected
 * @nlmsg_policy: Validation policy
 * @nltb: Array to store policy_max parsed elements
 * @msg_type: Type of netlink message
 *
 * Returns 0 on success or a negative error code
 */
पूर्णांक iwpm_parse_nlmsg(काष्ठा netlink_callback *cb, पूर्णांक policy_max,
				स्थिर काष्ठा nla_policy *nlmsg_policy,
				काष्ठा nlattr *nltb[], स्थिर अक्षर *msg_type);

/**
 * iwpm_prपूर्णांक_sockaddr - Prपूर्णांक IPv4/IPv6 address and TCP port
 * @sockaddr: Socket address to prपूर्णांक
 * @msg: Message to prपूर्णांक
 */
व्योम iwpm_prपूर्णांक_sockaddr(काष्ठा sockaddr_storage *sockaddr, अक्षर *msg);

/**
 * iwpm_send_hello - Send hello response to iwpmd
 *
 * @nl_client: The index of the netlink client
 * @iwpm_pid: The pid of the user space port mapper
 * @abi_version: The kernel's abi_version
 *
 * Returns 0 on success or a negative error code
 */
पूर्णांक iwpm_send_hello(u8 nl_client, पूर्णांक iwpm_pid, u16 abi_version);
बाह्य u16 iwpm_ulib_version;
#पूर्ण_अगर
