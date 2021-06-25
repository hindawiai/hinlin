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
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
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

#समावेश "iwpm_util.h"

अटल स्थिर अक्षर iwpm_ulib_name[IWPM_ULIBNAME_SIZE] = "iWarpPortMapperUser";
u16 iwpm_ulib_version = IWPM_UABI_VERSION_MIN;
अटल पूर्णांक iwpm_user_pid = IWPM_PID_UNDEFINED;
अटल atomic_t echo_nlmsg_seq;

/**
 * iwpm_valid_pid - Check अगर the userspace iwarp port mapper pid is valid
 *
 * Returns true अगर the pid is greater than zero, otherwise वापसs false
 */
पूर्णांक iwpm_valid_pid(व्योम)
अणु
	वापस iwpm_user_pid > 0;
पूर्ण

/**
 * iwpm_रेजिस्टर_pid - Send a netlink query to userspace
 *                     to get the iwarp port mapper pid
 * @pm_msg: Contains driver info to send to the userspace port mapper
 * @nl_client: The index of the netlink client
 *
 * nlmsg attributes:
 *	[IWPM_NLA_REG_PID_SEQ]
 *	[IWPM_NLA_REG_IF_NAME]
 *	[IWPM_NLA_REG_IBDEV_NAME]
 *	[IWPM_NLA_REG_ULIB_NAME]
 */
पूर्णांक iwpm_रेजिस्टर_pid(काष्ठा iwpm_dev_data *pm_msg, u8 nl_client)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा iwpm_nlmsg_request *nlmsg_request = शून्य;
	काष्ठा nlmsghdr *nlh;
	u32 msg_seq;
	स्थिर अक्षर *err_str = "";
	पूर्णांक ret = -EINVAL;

	अगर (!iwpm_valid_client(nl_client)) अणु
		err_str = "Invalid port mapper client";
		जाओ pid_query_error;
	पूर्ण
	अगर (iwpm_check_registration(nl_client, IWPM_REG_VALID) ||
			iwpm_user_pid == IWPM_PID_UNAVAILABLE)
		वापस 0;
	skb = iwpm_create_nlmsg(RDMA_NL_IWPM_REG_PID, &nlh, nl_client);
	अगर (!skb) अणु
		err_str = "Unable to create a nlmsg";
		जाओ pid_query_error;
	पूर्ण
	nlh->nlmsg_seq = iwpm_get_nlmsg_seq();
	nlmsg_request = iwpm_get_nlmsg_request(nlh->nlmsg_seq, nl_client, GFP_KERNEL);
	अगर (!nlmsg_request) अणु
		err_str = "Unable to allocate netlink request";
		जाओ pid_query_error;
	पूर्ण
	msg_seq = atomic_पढ़ो(&echo_nlmsg_seq);

	/* fill in the pid request message */
	err_str = "Unable to put attribute of the nlmsg";
	ret = ibnl_put_attr(skb, nlh, माप(u32), &msg_seq, IWPM_NLA_REG_PID_SEQ);
	अगर (ret)
		जाओ pid_query_error;
	ret = ibnl_put_attr(skb, nlh, IFNAMSIZ,
			    pm_msg->अगर_name, IWPM_NLA_REG_IF_NAME);
	अगर (ret)
		जाओ pid_query_error;
	ret = ibnl_put_attr(skb, nlh, IWPM_DEVNAME_SIZE,
				pm_msg->dev_name, IWPM_NLA_REG_IBDEV_NAME);
	अगर (ret)
		जाओ pid_query_error;
	ret = ibnl_put_attr(skb, nlh, IWPM_ULIBNAME_SIZE,
				(अक्षर *)iwpm_ulib_name, IWPM_NLA_REG_ULIB_NAME);
	अगर (ret)
		जाओ pid_query_error;

	nlmsg_end(skb, nlh);

	pr_debug("%s: Multicasting a nlmsg (dev = %s ifname = %s iwpm = %s)\n",
		__func__, pm_msg->dev_name, pm_msg->अगर_name, iwpm_ulib_name);

	ret = rdma_nl_multicast(&init_net, skb, RDMA_NL_GROUP_IWPM, GFP_KERNEL);
	अगर (ret) अणु
		skb = शून्य; /* skb is मुक्तd in the netlink send-op handling */
		iwpm_user_pid = IWPM_PID_UNAVAILABLE;
		err_str = "Unable to send a nlmsg";
		जाओ pid_query_error;
	पूर्ण
	nlmsg_request->req_buffer = pm_msg;
	ret = iwpm_रुको_complete_req(nlmsg_request);
	वापस ret;
pid_query_error:
	pr_info("%s: %s (client = %d)\n", __func__, err_str, nl_client);
	dev_kमुक्त_skb(skb);
	अगर (nlmsg_request)
		iwpm_मुक्त_nlmsg_request(&nlmsg_request->kref);
	वापस ret;
पूर्ण

/**
 * iwpm_add_mapping - Send a netlink add mapping request to
 *                    the userspace port mapper
 * @pm_msg: Contains the local ip/tcp address info to send
 * @nl_client: The index of the netlink client
 *
 * nlmsg attributes:
 *	[IWPM_NLA_MANAGE_MAPPING_SEQ]
 *	[IWPM_NLA_MANAGE_ADDR]
 *	[IWPM_NLA_MANAGE_FLAGS]
 *
 * If the request is successful, the pm_msg stores
 * the port mapper response (mapped address info)
 */
पूर्णांक iwpm_add_mapping(काष्ठा iwpm_sa_data *pm_msg, u8 nl_client)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा iwpm_nlmsg_request *nlmsg_request = शून्य;
	काष्ठा nlmsghdr *nlh;
	u32 msg_seq;
	स्थिर अक्षर *err_str = "";
	पूर्णांक ret = -EINVAL;

	अगर (!iwpm_valid_client(nl_client)) अणु
		err_str = "Invalid port mapper client";
		जाओ add_mapping_error;
	पूर्ण
	अगर (!iwpm_valid_pid())
		वापस 0;
	अगर (!iwpm_check_registration(nl_client, IWPM_REG_VALID)) अणु
		err_str = "Unregistered port mapper client";
		जाओ add_mapping_error;
	पूर्ण
	skb = iwpm_create_nlmsg(RDMA_NL_IWPM_ADD_MAPPING, &nlh, nl_client);
	अगर (!skb) अणु
		err_str = "Unable to create a nlmsg";
		जाओ add_mapping_error;
	पूर्ण
	nlh->nlmsg_seq = iwpm_get_nlmsg_seq();
	nlmsg_request = iwpm_get_nlmsg_request(nlh->nlmsg_seq, nl_client, GFP_KERNEL);
	अगर (!nlmsg_request) अणु
		err_str = "Unable to allocate netlink request";
		जाओ add_mapping_error;
	पूर्ण
	msg_seq = atomic_पढ़ो(&echo_nlmsg_seq);
	/* fill in the add mapping message */
	err_str = "Unable to put attribute of the nlmsg";
	ret = ibnl_put_attr(skb, nlh, माप(u32), &msg_seq,
				IWPM_NLA_MANAGE_MAPPING_SEQ);
	अगर (ret)
		जाओ add_mapping_error;
	ret = ibnl_put_attr(skb, nlh, माप(काष्ठा sockaddr_storage),
				&pm_msg->loc_addr, IWPM_NLA_MANAGE_ADDR);
	अगर (ret)
		जाओ add_mapping_error;

	/* If flags are required and we're not V4, then वापस a quiet error */
	अगर (pm_msg->flags && iwpm_ulib_version == IWPM_UABI_VERSION_MIN) अणु
		ret = -EINVAL;
		जाओ add_mapping_error_nowarn;
	पूर्ण
	अगर (iwpm_ulib_version > IWPM_UABI_VERSION_MIN) अणु
		ret = ibnl_put_attr(skb, nlh, माप(u32), &pm_msg->flags,
				IWPM_NLA_MANAGE_FLAGS);
		अगर (ret)
			जाओ add_mapping_error;
	पूर्ण

	nlmsg_end(skb, nlh);
	nlmsg_request->req_buffer = pm_msg;

	ret = rdma_nl_unicast_रुको(&init_net, skb, iwpm_user_pid);
	अगर (ret) अणु
		skb = शून्य; /* skb is मुक्तd in the netlink send-op handling */
		iwpm_user_pid = IWPM_PID_UNDEFINED;
		err_str = "Unable to send a nlmsg";
		जाओ add_mapping_error;
	पूर्ण
	ret = iwpm_रुको_complete_req(nlmsg_request);
	वापस ret;
add_mapping_error:
	pr_info("%s: %s (client = %d)\n", __func__, err_str, nl_client);
add_mapping_error_nowarn:
	dev_kमुक्त_skb(skb);
	अगर (nlmsg_request)
		iwpm_मुक्त_nlmsg_request(&nlmsg_request->kref);
	वापस ret;
पूर्ण

/**
 * iwpm_add_and_query_mapping - Process the port mapper response to
 *                              iwpm_add_and_query_mapping request
 * @pm_msg: Contains the local ip/tcp address info to send
 * @nl_client: The index of the netlink client
 *
 * nlmsg attributes:
 *	[IWPM_NLA_QUERY_MAPPING_SEQ]
 *	[IWPM_NLA_QUERY_LOCAL_ADDR]
 *	[IWPM_NLA_QUERY_REMOTE_ADDR]
 *	[IWPM_NLA_QUERY_FLAGS]
 */
पूर्णांक iwpm_add_and_query_mapping(काष्ठा iwpm_sa_data *pm_msg, u8 nl_client)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा iwpm_nlmsg_request *nlmsg_request = शून्य;
	काष्ठा nlmsghdr *nlh;
	u32 msg_seq;
	स्थिर अक्षर *err_str = "";
	पूर्णांक ret = -EINVAL;

	अगर (!iwpm_valid_client(nl_client)) अणु
		err_str = "Invalid port mapper client";
		जाओ query_mapping_error;
	पूर्ण
	अगर (!iwpm_valid_pid())
		वापस 0;
	अगर (!iwpm_check_registration(nl_client, IWPM_REG_VALID)) अणु
		err_str = "Unregistered port mapper client";
		जाओ query_mapping_error;
	पूर्ण
	ret = -ENOMEM;
	skb = iwpm_create_nlmsg(RDMA_NL_IWPM_QUERY_MAPPING, &nlh, nl_client);
	अगर (!skb) अणु
		err_str = "Unable to create a nlmsg";
		जाओ query_mapping_error;
	पूर्ण
	nlh->nlmsg_seq = iwpm_get_nlmsg_seq();
	nlmsg_request = iwpm_get_nlmsg_request(nlh->nlmsg_seq,
				nl_client, GFP_KERNEL);
	अगर (!nlmsg_request) अणु
		err_str = "Unable to allocate netlink request";
		जाओ query_mapping_error;
	पूर्ण
	msg_seq = atomic_पढ़ो(&echo_nlmsg_seq);

	/* fill in the query message */
	err_str = "Unable to put attribute of the nlmsg";
	ret = ibnl_put_attr(skb, nlh, माप(u32), &msg_seq,
				IWPM_NLA_QUERY_MAPPING_SEQ);
	अगर (ret)
		जाओ query_mapping_error;
	ret = ibnl_put_attr(skb, nlh, माप(काष्ठा sockaddr_storage),
				&pm_msg->loc_addr, IWPM_NLA_QUERY_LOCAL_ADDR);
	अगर (ret)
		जाओ query_mapping_error;
	ret = ibnl_put_attr(skb, nlh, माप(काष्ठा sockaddr_storage),
				&pm_msg->rem_addr, IWPM_NLA_QUERY_REMOTE_ADDR);
	अगर (ret)
		जाओ query_mapping_error;

	/* If flags are required and we're not V4, then वापस a quite error */
	अगर (pm_msg->flags && iwpm_ulib_version == IWPM_UABI_VERSION_MIN) अणु
		ret = -EINVAL;
		जाओ query_mapping_error_nowarn;
	पूर्ण
	अगर (iwpm_ulib_version > IWPM_UABI_VERSION_MIN) अणु
		ret = ibnl_put_attr(skb, nlh, माप(u32), &pm_msg->flags,
				IWPM_NLA_QUERY_FLAGS);
		अगर (ret)
			जाओ query_mapping_error;
	पूर्ण

	nlmsg_end(skb, nlh);
	nlmsg_request->req_buffer = pm_msg;

	ret = rdma_nl_unicast_रुको(&init_net, skb, iwpm_user_pid);
	अगर (ret) अणु
		skb = शून्य; /* skb is मुक्तd in the netlink send-op handling */
		err_str = "Unable to send a nlmsg";
		जाओ query_mapping_error;
	पूर्ण
	ret = iwpm_रुको_complete_req(nlmsg_request);
	वापस ret;
query_mapping_error:
	pr_info("%s: %s (client = %d)\n", __func__, err_str, nl_client);
query_mapping_error_nowarn:
	dev_kमुक्त_skb(skb);
	अगर (nlmsg_request)
		iwpm_मुक्त_nlmsg_request(&nlmsg_request->kref);
	वापस ret;
पूर्ण

/**
 * iwpm_हटाओ_mapping - Send a netlink हटाओ mapping request
 *                       to the userspace port mapper
 *
 * @local_addr: Local ip/tcp address to हटाओ
 * @nl_client: The index of the netlink client
 *
 * nlmsg attributes:
 *	[IWPM_NLA_MANAGE_MAPPING_SEQ]
 *	[IWPM_NLA_MANAGE_ADDR]
 */
पूर्णांक iwpm_हटाओ_mapping(काष्ठा sockaddr_storage *local_addr, u8 nl_client)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा nlmsghdr *nlh;
	u32 msg_seq;
	स्थिर अक्षर *err_str = "";
	पूर्णांक ret = -EINVAL;

	अगर (!iwpm_valid_client(nl_client)) अणु
		err_str = "Invalid port mapper client";
		जाओ हटाओ_mapping_error;
	पूर्ण
	अगर (!iwpm_valid_pid())
		वापस 0;
	अगर (iwpm_check_registration(nl_client, IWPM_REG_UNDEF)) अणु
		err_str = "Unregistered port mapper client";
		जाओ हटाओ_mapping_error;
	पूर्ण
	skb = iwpm_create_nlmsg(RDMA_NL_IWPM_REMOVE_MAPPING, &nlh, nl_client);
	अगर (!skb) अणु
		ret = -ENOMEM;
		err_str = "Unable to create a nlmsg";
		जाओ हटाओ_mapping_error;
	पूर्ण
	msg_seq = atomic_पढ़ो(&echo_nlmsg_seq);
	nlh->nlmsg_seq = iwpm_get_nlmsg_seq();
	err_str = "Unable to put attribute of the nlmsg";
	ret = ibnl_put_attr(skb, nlh, माप(u32), &msg_seq,
				IWPM_NLA_MANAGE_MAPPING_SEQ);
	अगर (ret)
		जाओ हटाओ_mapping_error;
	ret = ibnl_put_attr(skb, nlh, माप(काष्ठा sockaddr_storage),
				local_addr, IWPM_NLA_MANAGE_ADDR);
	अगर (ret)
		जाओ हटाओ_mapping_error;

	nlmsg_end(skb, nlh);

	ret = rdma_nl_unicast_रुको(&init_net, skb, iwpm_user_pid);
	अगर (ret) अणु
		skb = शून्य; /* skb is मुक्तd in the netlink send-op handling */
		iwpm_user_pid = IWPM_PID_UNDEFINED;
		err_str = "Unable to send a nlmsg";
		जाओ हटाओ_mapping_error;
	पूर्ण
	iwpm_prपूर्णांक_sockaddr(local_addr,
			"remove_mapping: Local sockaddr:");
	वापस 0;
हटाओ_mapping_error:
	pr_info("%s: %s (client = %d)\n", __func__, err_str, nl_client);
	अगर (skb)
		dev_kमुक्त_skb_any(skb);
	वापस ret;
पूर्ण

/* netlink attribute policy क्रम the received response to रेजिस्टर pid request */
अटल स्थिर काष्ठा nla_policy resp_reg_policy[IWPM_NLA_RREG_PID_MAX] = अणु
	[IWPM_NLA_RREG_PID_SEQ]     = अणु .type = NLA_U32 पूर्ण,
	[IWPM_NLA_RREG_IBDEV_NAME]  = अणु .type = NLA_STRING,
					.len = IWPM_DEVNAME_SIZE - 1 पूर्ण,
	[IWPM_NLA_RREG_ULIB_NAME]   = अणु .type = NLA_STRING,
					.len = IWPM_ULIBNAME_SIZE - 1 पूर्ण,
	[IWPM_NLA_RREG_ULIB_VER]    = अणु .type = NLA_U16 पूर्ण,
	[IWPM_NLA_RREG_PID_ERR]     = अणु .type = NLA_U16 पूर्ण
पूर्ण;

/**
 * iwpm_रेजिस्टर_pid_cb - Process the port mapper response to
 *                        iwpm_रेजिस्टर_pid query
 * @skb: The socket buffer
 * @cb: Contains the received message (payload and netlink header)
 *
 * If successful, the function receives the userspace port mapper pid
 * which is used in future communication with the port mapper
 */
पूर्णांक iwpm_रेजिस्टर_pid_cb(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा iwpm_nlmsg_request *nlmsg_request = शून्य;
	काष्ठा nlattr *nltb[IWPM_NLA_RREG_PID_MAX];
	काष्ठा iwpm_dev_data *pm_msg;
	अक्षर *dev_name, *iwpm_name;
	u32 msg_seq;
	u8 nl_client;
	u16 iwpm_version;
	स्थिर अक्षर *msg_type = "Register Pid response";

	अगर (iwpm_parse_nlmsg(cb, IWPM_NLA_RREG_PID_MAX,
				resp_reg_policy, nltb, msg_type))
		वापस -EINVAL;

	msg_seq = nla_get_u32(nltb[IWPM_NLA_RREG_PID_SEQ]);
	nlmsg_request = iwpm_find_nlmsg_request(msg_seq);
	अगर (!nlmsg_request) अणु
		pr_info("%s: Could not find a matching request (seq = %u)\n",
				 __func__, msg_seq);
		वापस -EINVAL;
	पूर्ण
	pm_msg = nlmsg_request->req_buffer;
	nl_client = nlmsg_request->nl_client;
	dev_name = (अक्षर *)nla_data(nltb[IWPM_NLA_RREG_IBDEV_NAME]);
	iwpm_name = (अक्षर *)nla_data(nltb[IWPM_NLA_RREG_ULIB_NAME]);
	iwpm_version = nla_get_u16(nltb[IWPM_NLA_RREG_ULIB_VER]);

	/* check device name, ulib name and version */
	अगर (म_भेद(pm_msg->dev_name, dev_name) ||
			म_भेद(iwpm_ulib_name, iwpm_name) ||
			iwpm_version < IWPM_UABI_VERSION_MIN) अणु

		pr_info("%s: Incorrect info (dev = %s name = %s version = %d)\n",
				__func__, dev_name, iwpm_name, iwpm_version);
		nlmsg_request->err_code = IWPM_USER_LIB_INFO_ERR;
		जाओ रेजिस्टर_pid_response_निकास;
	पूर्ण
	iwpm_user_pid = cb->nlh->nlmsg_pid;
	iwpm_ulib_version = iwpm_version;
	अगर (iwpm_ulib_version < IWPM_UABI_VERSION)
		pr_warn_once("%s: Down level iwpmd/pid %u.  Continuing...",
			__func__, iwpm_user_pid);
	atomic_set(&echo_nlmsg_seq, cb->nlh->nlmsg_seq);
	pr_debug("%s: iWarp Port Mapper (pid = %d) is available!\n",
			__func__, iwpm_user_pid);
	अगर (iwpm_valid_client(nl_client))
		iwpm_set_registration(nl_client, IWPM_REG_VALID);
रेजिस्टर_pid_response_निकास:
	nlmsg_request->request_करोne = 1;
	/* always क्रम found nlmsg_request */
	kref_put(&nlmsg_request->kref, iwpm_मुक्त_nlmsg_request);
	barrier();
	up(&nlmsg_request->sem);
	वापस 0;
पूर्ण

/* netlink attribute policy क्रम the received response to add mapping request */
अटल स्थिर काष्ठा nla_policy resp_add_policy[IWPM_NLA_RMANAGE_MAPPING_MAX] = अणु
	[IWPM_NLA_RMANAGE_MAPPING_SEQ]     = अणु .type = NLA_U32 पूर्ण,
	[IWPM_NLA_RMANAGE_ADDR]            = अणु
				.len = माप(काष्ठा sockaddr_storage) पूर्ण,
	[IWPM_NLA_RMANAGE_MAPPED_LOC_ADDR] = अणु
				.len = माप(काष्ठा sockaddr_storage) पूर्ण,
	[IWPM_NLA_RMANAGE_MAPPING_ERR]	   = अणु .type = NLA_U16 पूर्ण
पूर्ण;

/**
 * iwpm_add_mapping_cb - Process the port mapper response to
 *                       iwpm_add_mapping request
 * @skb: The socket buffer
 * @cb: Contains the received message (payload and netlink header)
 */
पूर्णांक iwpm_add_mapping_cb(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा iwpm_sa_data *pm_msg;
	काष्ठा iwpm_nlmsg_request *nlmsg_request = शून्य;
	काष्ठा nlattr *nltb[IWPM_NLA_RMANAGE_MAPPING_MAX];
	काष्ठा sockaddr_storage *local_sockaddr;
	काष्ठा sockaddr_storage *mapped_sockaddr;
	स्थिर अक्षर *msg_type;
	u32 msg_seq;

	msg_type = "Add Mapping response";
	अगर (iwpm_parse_nlmsg(cb, IWPM_NLA_RMANAGE_MAPPING_MAX,
				resp_add_policy, nltb, msg_type))
		वापस -EINVAL;

	atomic_set(&echo_nlmsg_seq, cb->nlh->nlmsg_seq);

	msg_seq = nla_get_u32(nltb[IWPM_NLA_RMANAGE_MAPPING_SEQ]);
	nlmsg_request = iwpm_find_nlmsg_request(msg_seq);
	अगर (!nlmsg_request) अणु
		pr_info("%s: Could not find a matching request (seq = %u)\n",
				 __func__, msg_seq);
		वापस -EINVAL;
	पूर्ण
	pm_msg = nlmsg_request->req_buffer;
	local_sockaddr = (काष्ठा sockaddr_storage *)
			nla_data(nltb[IWPM_NLA_RMANAGE_ADDR]);
	mapped_sockaddr = (काष्ठा sockaddr_storage *)
			nla_data(nltb[IWPM_NLA_RMANAGE_MAPPED_LOC_ADDR]);

	अगर (iwpm_compare_sockaddr(local_sockaddr, &pm_msg->loc_addr)) अणु
		nlmsg_request->err_code = IWPM_USER_LIB_INFO_ERR;
		जाओ add_mapping_response_निकास;
	पूर्ण
	अगर (mapped_sockaddr->ss_family != local_sockaddr->ss_family) अणु
		pr_info("%s: Sockaddr family doesn't match the requested one\n",
				__func__);
		nlmsg_request->err_code = IWPM_USER_LIB_INFO_ERR;
		जाओ add_mapping_response_निकास;
	पूर्ण
	स_नकल(&pm_msg->mapped_loc_addr, mapped_sockaddr,
			माप(*mapped_sockaddr));
	iwpm_prपूर्णांक_sockaddr(&pm_msg->loc_addr,
			"add_mapping: Local sockaddr:");
	iwpm_prपूर्णांक_sockaddr(&pm_msg->mapped_loc_addr,
			"add_mapping: Mapped local sockaddr:");

add_mapping_response_निकास:
	nlmsg_request->request_करोne = 1;
	/* always क्रम found request */
	kref_put(&nlmsg_request->kref, iwpm_मुक्त_nlmsg_request);
	barrier();
	up(&nlmsg_request->sem);
	वापस 0;
पूर्ण

/* netlink attribute policy क्रम the response to add and query mapping request
 * and response with remote address info
 */
अटल स्थिर काष्ठा nla_policy resp_query_policy[IWPM_NLA_RQUERY_MAPPING_MAX] = अणु
	[IWPM_NLA_RQUERY_MAPPING_SEQ]     = अणु .type = NLA_U32 पूर्ण,
	[IWPM_NLA_RQUERY_LOCAL_ADDR]      = अणु
				.len = माप(काष्ठा sockaddr_storage) पूर्ण,
	[IWPM_NLA_RQUERY_REMOTE_ADDR]     = अणु
				.len = माप(काष्ठा sockaddr_storage) पूर्ण,
	[IWPM_NLA_RQUERY_MAPPED_LOC_ADDR] = अणु
				.len = माप(काष्ठा sockaddr_storage) पूर्ण,
	[IWPM_NLA_RQUERY_MAPPED_REM_ADDR] = अणु
				.len = माप(काष्ठा sockaddr_storage) पूर्ण,
	[IWPM_NLA_RQUERY_MAPPING_ERR]	  = अणु .type = NLA_U16 पूर्ण
पूर्ण;

/**
 * iwpm_add_and_query_mapping_cb - Process the port mapper response to
 *                                 iwpm_add_and_query_mapping request
 * @skb: The socket buffer
 * @cb: Contains the received message (payload and netlink header)
 */
पूर्णांक iwpm_add_and_query_mapping_cb(काष्ठा sk_buff *skb,
				काष्ठा netlink_callback *cb)
अणु
	काष्ठा iwpm_sa_data *pm_msg;
	काष्ठा iwpm_nlmsg_request *nlmsg_request = शून्य;
	काष्ठा nlattr *nltb[IWPM_NLA_RQUERY_MAPPING_MAX];
	काष्ठा sockaddr_storage *local_sockaddr, *remote_sockaddr;
	काष्ठा sockaddr_storage *mapped_loc_sockaddr, *mapped_rem_sockaddr;
	स्थिर अक्षर *msg_type;
	u32 msg_seq;
	u16 err_code;

	msg_type = "Query Mapping response";
	अगर (iwpm_parse_nlmsg(cb, IWPM_NLA_RQUERY_MAPPING_MAX,
				resp_query_policy, nltb, msg_type))
		वापस -EINVAL;
	atomic_set(&echo_nlmsg_seq, cb->nlh->nlmsg_seq);

	msg_seq = nla_get_u32(nltb[IWPM_NLA_RQUERY_MAPPING_SEQ]);
	nlmsg_request = iwpm_find_nlmsg_request(msg_seq);
	अगर (!nlmsg_request) अणु
		pr_info("%s: Could not find a matching request (seq = %u)\n",
				 __func__, msg_seq);
		वापस -EINVAL;
	पूर्ण
	pm_msg = nlmsg_request->req_buffer;
	local_sockaddr = (काष्ठा sockaddr_storage *)
			nla_data(nltb[IWPM_NLA_RQUERY_LOCAL_ADDR]);
	remote_sockaddr = (काष्ठा sockaddr_storage *)
			nla_data(nltb[IWPM_NLA_RQUERY_REMOTE_ADDR]);
	mapped_loc_sockaddr = (काष्ठा sockaddr_storage *)
			nla_data(nltb[IWPM_NLA_RQUERY_MAPPED_LOC_ADDR]);
	mapped_rem_sockaddr = (काष्ठा sockaddr_storage *)
			nla_data(nltb[IWPM_NLA_RQUERY_MAPPED_REM_ADDR]);

	err_code = nla_get_u16(nltb[IWPM_NLA_RQUERY_MAPPING_ERR]);
	अगर (err_code == IWPM_REMOTE_QUERY_REJECT) अणु
		pr_info("%s: Received a Reject (pid = %u, echo seq = %u)\n",
			__func__, cb->nlh->nlmsg_pid, msg_seq);
		nlmsg_request->err_code = IWPM_REMOTE_QUERY_REJECT;
	पूर्ण
	अगर (iwpm_compare_sockaddr(local_sockaddr, &pm_msg->loc_addr) ||
		iwpm_compare_sockaddr(remote_sockaddr, &pm_msg->rem_addr)) अणु
		pr_info("%s: Incorrect local sockaddr\n", __func__);
		nlmsg_request->err_code = IWPM_USER_LIB_INFO_ERR;
		जाओ query_mapping_response_निकास;
	पूर्ण
	अगर (mapped_loc_sockaddr->ss_family != local_sockaddr->ss_family ||
		mapped_rem_sockaddr->ss_family != remote_sockaddr->ss_family) अणु
		pr_info("%s: Sockaddr family doesn't match the requested one\n",
				__func__);
		nlmsg_request->err_code = IWPM_USER_LIB_INFO_ERR;
		जाओ query_mapping_response_निकास;
	पूर्ण
	स_नकल(&pm_msg->mapped_loc_addr, mapped_loc_sockaddr,
			माप(*mapped_loc_sockaddr));
	स_नकल(&pm_msg->mapped_rem_addr, mapped_rem_sockaddr,
			माप(*mapped_rem_sockaddr));

	iwpm_prपूर्णांक_sockaddr(&pm_msg->loc_addr,
			"query_mapping: Local sockaddr:");
	iwpm_prपूर्णांक_sockaddr(&pm_msg->mapped_loc_addr,
			"query_mapping: Mapped local sockaddr:");
	iwpm_prपूर्णांक_sockaddr(&pm_msg->rem_addr,
			"query_mapping: Remote sockaddr:");
	iwpm_prपूर्णांक_sockaddr(&pm_msg->mapped_rem_addr,
			"query_mapping: Mapped remote sockaddr:");
query_mapping_response_निकास:
	nlmsg_request->request_करोne = 1;
	/* always क्रम found request */
	kref_put(&nlmsg_request->kref, iwpm_मुक्त_nlmsg_request);
	barrier();
	up(&nlmsg_request->sem);
	वापस 0;
पूर्ण

/**
 * iwpm_remote_info_cb - Process remote connecting peer address info, which
 *                       the port mapper has received from the connecting peer
 * @skb: The socket buffer
 * @cb: Contains the received message (payload and netlink header)
 *
 * Stores the IPv4/IPv6 address info in a hash table
 */
पूर्णांक iwpm_remote_info_cb(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा nlattr *nltb[IWPM_NLA_RQUERY_MAPPING_MAX];
	काष्ठा sockaddr_storage *local_sockaddr, *remote_sockaddr;
	काष्ठा sockaddr_storage *mapped_loc_sockaddr, *mapped_rem_sockaddr;
	काष्ठा iwpm_remote_info *rem_info;
	स्थिर अक्षर *msg_type;
	u8 nl_client;
	पूर्णांक ret = -EINVAL;

	msg_type = "Remote Mapping info";
	अगर (iwpm_parse_nlmsg(cb, IWPM_NLA_RQUERY_MAPPING_MAX,
				resp_query_policy, nltb, msg_type))
		वापस ret;

	nl_client = RDMA_NL_GET_CLIENT(cb->nlh->nlmsg_type);
	अगर (!iwpm_valid_client(nl_client)) अणु
		pr_info("%s: Invalid port mapper client = %d\n",
				__func__, nl_client);
		वापस ret;
	पूर्ण
	atomic_set(&echo_nlmsg_seq, cb->nlh->nlmsg_seq);

	local_sockaddr = (काष्ठा sockaddr_storage *)
			nla_data(nltb[IWPM_NLA_RQUERY_LOCAL_ADDR]);
	remote_sockaddr = (काष्ठा sockaddr_storage *)
			nla_data(nltb[IWPM_NLA_RQUERY_REMOTE_ADDR]);
	mapped_loc_sockaddr = (काष्ठा sockaddr_storage *)
			nla_data(nltb[IWPM_NLA_RQUERY_MAPPED_LOC_ADDR]);
	mapped_rem_sockaddr = (काष्ठा sockaddr_storage *)
			nla_data(nltb[IWPM_NLA_RQUERY_MAPPED_REM_ADDR]);

	अगर (mapped_loc_sockaddr->ss_family != local_sockaddr->ss_family ||
		mapped_rem_sockaddr->ss_family != remote_sockaddr->ss_family) अणु
		pr_info("%s: Sockaddr family doesn't match the requested one\n",
				__func__);
		वापस ret;
	पूर्ण
	rem_info = kzalloc(माप(काष्ठा iwpm_remote_info), GFP_ATOMIC);
	अगर (!rem_info) अणु
		ret = -ENOMEM;
		वापस ret;
	पूर्ण
	स_नकल(&rem_info->mapped_loc_sockaddr, mapped_loc_sockaddr,
	       माप(काष्ठा sockaddr_storage));
	स_नकल(&rem_info->remote_sockaddr, remote_sockaddr,
	       माप(काष्ठा sockaddr_storage));
	स_नकल(&rem_info->mapped_rem_sockaddr, mapped_rem_sockaddr,
	       माप(काष्ठा sockaddr_storage));
	rem_info->nl_client = nl_client;

	iwpm_add_remote_info(rem_info);

	iwpm_prपूर्णांक_sockaddr(local_sockaddr,
			"remote_info: Local sockaddr:");
	iwpm_prपूर्णांक_sockaddr(mapped_loc_sockaddr,
			"remote_info: Mapped local sockaddr:");
	iwpm_prपूर्णांक_sockaddr(remote_sockaddr,
			"remote_info: Remote sockaddr:");
	iwpm_prपूर्णांक_sockaddr(mapped_rem_sockaddr,
			"remote_info: Mapped remote sockaddr:");
	वापस ret;
पूर्ण

/* netlink attribute policy क्रम the received request क्रम mapping info */
अटल स्थिर काष्ठा nla_policy resp_mapinfo_policy[IWPM_NLA_MAPINFO_REQ_MAX] = अणु
	[IWPM_NLA_MAPINFO_ULIB_NAME] = अणु .type = NLA_STRING,
					.len = IWPM_ULIBNAME_SIZE - 1 पूर्ण,
	[IWPM_NLA_MAPINFO_ULIB_VER]  = अणु .type = NLA_U16 पूर्ण
पूर्ण;

/**
 * iwpm_mapping_info_cb - Process a notअगरication that the userspace
 *                        port mapper daemon is started
 * @skb: The socket buffer
 * @cb: Contains the received message (payload and netlink header)
 *
 * Using the received port mapper pid, send all the local mapping
 * info records to the userspace port mapper
 */
पूर्णांक iwpm_mapping_info_cb(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा nlattr *nltb[IWPM_NLA_MAPINFO_REQ_MAX];
	स्थिर अक्षर *msg_type = "Mapping Info response";
	u8 nl_client;
	अक्षर *iwpm_name;
	u16 iwpm_version;
	पूर्णांक ret = -EINVAL;

	अगर (iwpm_parse_nlmsg(cb, IWPM_NLA_MAPINFO_REQ_MAX,
				resp_mapinfo_policy, nltb, msg_type)) अणु
		pr_info("%s: Unable to parse nlmsg\n", __func__);
		वापस ret;
	पूर्ण
	iwpm_name = (अक्षर *)nla_data(nltb[IWPM_NLA_MAPINFO_ULIB_NAME]);
	iwpm_version = nla_get_u16(nltb[IWPM_NLA_MAPINFO_ULIB_VER]);
	अगर (म_भेद(iwpm_ulib_name, iwpm_name) ||
			iwpm_version < IWPM_UABI_VERSION_MIN) अणु
		pr_info("%s: Invalid port mapper name = %s version = %d\n",
				__func__, iwpm_name, iwpm_version);
		वापस ret;
	पूर्ण
	nl_client = RDMA_NL_GET_CLIENT(cb->nlh->nlmsg_type);
	अगर (!iwpm_valid_client(nl_client)) अणु
		pr_info("%s: Invalid port mapper client = %d\n",
				__func__, nl_client);
		वापस ret;
	पूर्ण
	iwpm_set_registration(nl_client, IWPM_REG_INCOMPL);
	atomic_set(&echo_nlmsg_seq, cb->nlh->nlmsg_seq);
	iwpm_user_pid = cb->nlh->nlmsg_pid;

	अगर (iwpm_ulib_version < IWPM_UABI_VERSION)
		pr_warn_once("%s: Down level iwpmd/pid %u.  Continuing...",
			__func__, iwpm_user_pid);

	अगर (!iwpm_mapinfo_available())
		वापस 0;
	pr_debug("%s: iWarp Port Mapper (pid = %d) is available!\n",
		 __func__, iwpm_user_pid);
	ret = iwpm_send_mapinfo(nl_client, iwpm_user_pid);
	वापस ret;
पूर्ण

/* netlink attribute policy क्रम the received mapping info ack */
अटल स्थिर काष्ठा nla_policy ack_mapinfo_policy[IWPM_NLA_MAPINFO_NUM_MAX] = अणु
	[IWPM_NLA_MAPINFO_SEQ]    =   अणु .type = NLA_U32 पूर्ण,
	[IWPM_NLA_MAPINFO_SEND_NUM] = अणु .type = NLA_U32 पूर्ण,
	[IWPM_NLA_MAPINFO_ACK_NUM] =  अणु .type = NLA_U32 पूर्ण
पूर्ण;

/**
 * iwpm_ack_mapping_info_cb - Process the port mapper ack क्रम
 *                            the provided local mapping info records
 * @skb: The socket buffer
 * @cb: Contains the received message (payload and netlink header)
 */
पूर्णांक iwpm_ack_mapping_info_cb(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा nlattr *nltb[IWPM_NLA_MAPINFO_NUM_MAX];
	u32 mapinfo_send, mapinfo_ack;
	स्थिर अक्षर *msg_type = "Mapping Info Ack";

	अगर (iwpm_parse_nlmsg(cb, IWPM_NLA_MAPINFO_NUM_MAX,
				ack_mapinfo_policy, nltb, msg_type))
		वापस -EINVAL;
	mapinfo_send = nla_get_u32(nltb[IWPM_NLA_MAPINFO_SEND_NUM]);
	mapinfo_ack = nla_get_u32(nltb[IWPM_NLA_MAPINFO_ACK_NUM]);
	अगर (mapinfo_ack != mapinfo_send)
		pr_info("%s: Invalid mapinfo number (sent = %u ack-ed = %u)\n",
			__func__, mapinfo_send, mapinfo_ack);
	atomic_set(&echo_nlmsg_seq, cb->nlh->nlmsg_seq);
	वापस 0;
पूर्ण

/* netlink attribute policy क्रम the received port mapper error message */
अटल स्थिर काष्ठा nla_policy map_error_policy[IWPM_NLA_ERR_MAX] = अणु
	[IWPM_NLA_ERR_SEQ]        = अणु .type = NLA_U32 पूर्ण,
	[IWPM_NLA_ERR_CODE]       = अणु .type = NLA_U16 पूर्ण,
पूर्ण;

/**
 * iwpm_mapping_error_cb - Process port mapper notअगरication क्रम error
 *
 * @skb: The socket buffer
 * @cb: Contains the received message (payload and netlink header)
 */
पूर्णांक iwpm_mapping_error_cb(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा iwpm_nlmsg_request *nlmsg_request = शून्य;
	पूर्णांक nl_client = RDMA_NL_GET_CLIENT(cb->nlh->nlmsg_type);
	काष्ठा nlattr *nltb[IWPM_NLA_ERR_MAX];
	u32 msg_seq;
	u16 err_code;
	स्थिर अक्षर *msg_type = "Mapping Error Msg";

	अगर (iwpm_parse_nlmsg(cb, IWPM_NLA_ERR_MAX,
				map_error_policy, nltb, msg_type))
		वापस -EINVAL;

	msg_seq = nla_get_u32(nltb[IWPM_NLA_ERR_SEQ]);
	err_code = nla_get_u16(nltb[IWPM_NLA_ERR_CODE]);
	pr_info("%s: Received msg seq = %u err code = %u client = %d\n",
				__func__, msg_seq, err_code, nl_client);
	/* look क्रम nlmsg_request */
	nlmsg_request = iwpm_find_nlmsg_request(msg_seq);
	अगर (!nlmsg_request) अणु
		/* not all errors have associated requests */
		pr_debug("Could not find matching req (seq = %u)\n", msg_seq);
		वापस 0;
	पूर्ण
	atomic_set(&echo_nlmsg_seq, cb->nlh->nlmsg_seq);
	nlmsg_request->err_code = err_code;
	nlmsg_request->request_करोne = 1;
	/* always क्रम found request */
	kref_put(&nlmsg_request->kref, iwpm_मुक्त_nlmsg_request);
	barrier();
	up(&nlmsg_request->sem);
	वापस 0;
पूर्ण

/* netlink attribute policy क्रम the received hello request */
अटल स्थिर काष्ठा nla_policy hello_policy[IWPM_NLA_HELLO_MAX] = अणु
	[IWPM_NLA_HELLO_ABI_VERSION]     = अणु .type = NLA_U16 पूर्ण
पूर्ण;

/**
 * iwpm_hello_cb - Process a hello message from iwpmd
 *
 * @skb: The socket buffer
 * @cb: Contains the received message (payload and netlink header)
 *
 * Using the received port mapper pid, send the kernel's abi_version
 * after adjusting it to support the iwpmd version.
 */
पूर्णांक iwpm_hello_cb(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा nlattr *nltb[IWPM_NLA_HELLO_MAX];
	स्थिर अक्षर *msg_type = "Hello request";
	u8 nl_client;
	u16 abi_version;
	पूर्णांक ret = -EINVAL;

	अगर (iwpm_parse_nlmsg(cb, IWPM_NLA_HELLO_MAX, hello_policy, nltb,
			     msg_type)) अणु
		pr_info("%s: Unable to parse nlmsg\n", __func__);
		वापस ret;
	पूर्ण
	abi_version = nla_get_u16(nltb[IWPM_NLA_HELLO_ABI_VERSION]);
	nl_client = RDMA_NL_GET_CLIENT(cb->nlh->nlmsg_type);
	अगर (!iwpm_valid_client(nl_client)) अणु
		pr_info("%s: Invalid port mapper client = %d\n",
				__func__, nl_client);
		वापस ret;
	पूर्ण
	iwpm_set_registration(nl_client, IWPM_REG_INCOMPL);
	atomic_set(&echo_nlmsg_seq, cb->nlh->nlmsg_seq);
	iwpm_ulib_version = min_t(u16, IWPM_UABI_VERSION, abi_version);
	pr_debug("Using ABI version %u\n", iwpm_ulib_version);
	iwpm_user_pid = cb->nlh->nlmsg_pid;
	ret = iwpm_send_hello(nl_client, iwpm_user_pid, iwpm_ulib_version);
	वापस ret;
पूर्ण
