<शैली गुरु>
/*
 * Copyright (c) 2014 Chelsio, Inc. All rights reserved.
 * Copyright (c) 2014 Intel Corporation. All rights reserved.
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

#समावेश "iwpm_util.h"

#घोषणा IWPM_MAPINFO_HASH_SIZE	512
#घोषणा IWPM_MAPINFO_HASH_MASK	(IWPM_MAPINFO_HASH_SIZE - 1)
#घोषणा IWPM_REMINFO_HASH_SIZE	64
#घोषणा IWPM_REMINFO_HASH_MASK	(IWPM_REMINFO_HASH_SIZE - 1)
#घोषणा IWPM_MSG_SIZE		512

अटल LIST_HEAD(iwpm_nlmsg_req_list);
अटल DEFINE_SPINLOCK(iwpm_nlmsg_req_lock);

अटल काष्ठा hlist_head *iwpm_hash_bucket;
अटल DEFINE_SPINLOCK(iwpm_mapinfo_lock);

अटल काष्ठा hlist_head *iwpm_reminfo_bucket;
अटल DEFINE_SPINLOCK(iwpm_reminfo_lock);

अटल DEFINE_MUTEX(iwpm_admin_lock);
अटल काष्ठा iwpm_admin_data iwpm_admin;

/**
 * iwpm_init - Allocate resources क्रम the iwarp port mapper
 * @nl_client: The index of the netlink client
 *
 * Should be called when network पूर्णांकerface goes up.
 */
पूर्णांक iwpm_init(u8 nl_client)
अणु
	पूर्णांक ret = 0;
	mutex_lock(&iwpm_admin_lock);
	अगर (atomic_पढ़ो(&iwpm_admin.refcount) == 0) अणु
		iwpm_hash_bucket = kसुस्मृति(IWPM_MAPINFO_HASH_SIZE,
					   माप(काष्ठा hlist_head),
					   GFP_KERNEL);
		अगर (!iwpm_hash_bucket) अणु
			ret = -ENOMEM;
			जाओ init_निकास;
		पूर्ण
		iwpm_reminfo_bucket = kसुस्मृति(IWPM_REMINFO_HASH_SIZE,
					      माप(काष्ठा hlist_head),
					      GFP_KERNEL);
		अगर (!iwpm_reminfo_bucket) अणु
			kमुक्त(iwpm_hash_bucket);
			ret = -ENOMEM;
			जाओ init_निकास;
		पूर्ण
	पूर्ण
	atomic_inc(&iwpm_admin.refcount);
init_निकास:
	mutex_unlock(&iwpm_admin_lock);
	अगर (!ret) अणु
		iwpm_set_valid(nl_client, 1);
		iwpm_set_registration(nl_client, IWPM_REG_UNDEF);
		pr_debug("%s: Mapinfo and reminfo tables are created\n",
				__func__);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम मुक्त_hash_bucket(व्योम);
अटल व्योम मुक्त_reminfo_bucket(व्योम);

/**
 * iwpm_निकास - Deallocate resources क्रम the iwarp port mapper
 * @nl_client: The index of the netlink client
 *
 * Should be called when network पूर्णांकerface goes करोwn.
 */
पूर्णांक iwpm_निकास(u8 nl_client)
अणु

	अगर (!iwpm_valid_client(nl_client))
		वापस -EINVAL;
	mutex_lock(&iwpm_admin_lock);
	अगर (atomic_पढ़ो(&iwpm_admin.refcount) == 0) अणु
		mutex_unlock(&iwpm_admin_lock);
		pr_err("%s Incorrect usage - negative refcount\n", __func__);
		वापस -EINVAL;
	पूर्ण
	अगर (atomic_dec_and_test(&iwpm_admin.refcount)) अणु
		मुक्त_hash_bucket();
		मुक्त_reminfo_bucket();
		pr_debug("%s: Resources are destroyed\n", __func__);
	पूर्ण
	mutex_unlock(&iwpm_admin_lock);
	iwpm_set_valid(nl_client, 0);
	iwpm_set_registration(nl_client, IWPM_REG_UNDEF);
	वापस 0;
पूर्ण

अटल काष्ठा hlist_head *get_mapinfo_hash_bucket(काष्ठा sockaddr_storage *,
					       काष्ठा sockaddr_storage *);

/**
 * iwpm_create_mapinfo - Store local and mapped IPv4/IPv6 address
 *                       info in a hash table
 * @local_sockaddr: Local ip/tcp address
 * @mapped_sockaddr: Mapped local ip/tcp address
 * @nl_client: The index of the netlink client
 * @map_flags: IWPM mapping flags
 */
पूर्णांक iwpm_create_mapinfo(काष्ठा sockaddr_storage *local_sockaddr,
			काष्ठा sockaddr_storage *mapped_sockaddr,
			u8 nl_client, u32 map_flags)
अणु
	काष्ठा hlist_head *hash_bucket_head = शून्य;
	काष्ठा iwpm_mapping_info *map_info;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EINVAL;

	अगर (!iwpm_valid_client(nl_client))
		वापस ret;
	map_info = kzalloc(माप(काष्ठा iwpm_mapping_info), GFP_KERNEL);
	अगर (!map_info)
		वापस -ENOMEM;

	स_नकल(&map_info->local_sockaddr, local_sockaddr,
	       माप(काष्ठा sockaddr_storage));
	स_नकल(&map_info->mapped_sockaddr, mapped_sockaddr,
	       माप(काष्ठा sockaddr_storage));
	map_info->nl_client = nl_client;
	map_info->map_flags = map_flags;

	spin_lock_irqsave(&iwpm_mapinfo_lock, flags);
	अगर (iwpm_hash_bucket) अणु
		hash_bucket_head = get_mapinfo_hash_bucket(
					&map_info->local_sockaddr,
					&map_info->mapped_sockaddr);
		अगर (hash_bucket_head) अणु
			hlist_add_head(&map_info->hlist_node, hash_bucket_head);
			ret = 0;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&iwpm_mapinfo_lock, flags);

	अगर (!hash_bucket_head)
		kमुक्त(map_info);
	वापस ret;
पूर्ण

/**
 * iwpm_हटाओ_mapinfo - Remove local and mapped IPv4/IPv6 address
 *                       info from the hash table
 * @local_sockaddr: Local ip/tcp address
 * @mapped_local_addr: Mapped local ip/tcp address
 *
 * Returns err code अगर mapping info is not found in the hash table,
 * otherwise वापसs 0
 */
पूर्णांक iwpm_हटाओ_mapinfo(काष्ठा sockaddr_storage *local_sockaddr,
			काष्ठा sockaddr_storage *mapped_local_addr)
अणु
	काष्ठा hlist_node *पंचांगp_hlist_node;
	काष्ठा hlist_head *hash_bucket_head;
	काष्ठा iwpm_mapping_info *map_info = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EINVAL;

	spin_lock_irqsave(&iwpm_mapinfo_lock, flags);
	अगर (iwpm_hash_bucket) अणु
		hash_bucket_head = get_mapinfo_hash_bucket(
					local_sockaddr,
					mapped_local_addr);
		अगर (!hash_bucket_head)
			जाओ हटाओ_mapinfo_निकास;

		hlist_क्रम_each_entry_safe(map_info, पंचांगp_hlist_node,
					hash_bucket_head, hlist_node) अणु

			अगर (!iwpm_compare_sockaddr(&map_info->mapped_sockaddr,
						mapped_local_addr)) अणु

				hlist_del_init(&map_info->hlist_node);
				kमुक्त(map_info);
				ret = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
हटाओ_mapinfo_निकास:
	spin_unlock_irqrestore(&iwpm_mapinfo_lock, flags);
	वापस ret;
पूर्ण

अटल व्योम मुक्त_hash_bucket(व्योम)
अणु
	काष्ठा hlist_node *पंचांगp_hlist_node;
	काष्ठा iwpm_mapping_info *map_info;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	/* हटाओ all the mapinfo data from the list */
	spin_lock_irqsave(&iwpm_mapinfo_lock, flags);
	क्रम (i = 0; i < IWPM_MAPINFO_HASH_SIZE; i++) अणु
		hlist_क्रम_each_entry_safe(map_info, पंचांगp_hlist_node,
			&iwpm_hash_bucket[i], hlist_node) अणु

				hlist_del_init(&map_info->hlist_node);
				kमुक्त(map_info);
			पूर्ण
	पूर्ण
	/* मुक्त the hash list */
	kमुक्त(iwpm_hash_bucket);
	iwpm_hash_bucket = शून्य;
	spin_unlock_irqrestore(&iwpm_mapinfo_lock, flags);
पूर्ण

अटल व्योम मुक्त_reminfo_bucket(व्योम)
अणु
	काष्ठा hlist_node *पंचांगp_hlist_node;
	काष्ठा iwpm_remote_info *rem_info;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	/* हटाओ all the remote info from the list */
	spin_lock_irqsave(&iwpm_reminfo_lock, flags);
	क्रम (i = 0; i < IWPM_REMINFO_HASH_SIZE; i++) अणु
		hlist_क्रम_each_entry_safe(rem_info, पंचांगp_hlist_node,
			&iwpm_reminfo_bucket[i], hlist_node) अणु

				hlist_del_init(&rem_info->hlist_node);
				kमुक्त(rem_info);
			पूर्ण
	पूर्ण
	/* मुक्त the hash list */
	kमुक्त(iwpm_reminfo_bucket);
	iwpm_reminfo_bucket = शून्य;
	spin_unlock_irqrestore(&iwpm_reminfo_lock, flags);
पूर्ण

अटल काष्ठा hlist_head *get_reminfo_hash_bucket(काष्ठा sockaddr_storage *,
						काष्ठा sockaddr_storage *);

व्योम iwpm_add_remote_info(काष्ठा iwpm_remote_info *rem_info)
अणु
	काष्ठा hlist_head *hash_bucket_head;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&iwpm_reminfo_lock, flags);
	अगर (iwpm_reminfo_bucket) अणु
		hash_bucket_head = get_reminfo_hash_bucket(
					&rem_info->mapped_loc_sockaddr,
					&rem_info->mapped_rem_sockaddr);
		अगर (hash_bucket_head)
			hlist_add_head(&rem_info->hlist_node, hash_bucket_head);
	पूर्ण
	spin_unlock_irqrestore(&iwpm_reminfo_lock, flags);
पूर्ण

/**
 * iwpm_get_remote_info - Get the remote connecting peer address info
 *
 * @mapped_loc_addr: Mapped local address of the listening peer
 * @mapped_rem_addr: Mapped remote address of the connecting peer
 * @remote_addr: To store the remote address of the connecting peer
 * @nl_client: The index of the netlink client
 *
 * The remote address info is retrieved and provided to the client in
 * the remote_addr. After that it is हटाओd from the hash table
 */
पूर्णांक iwpm_get_remote_info(काष्ठा sockaddr_storage *mapped_loc_addr,
			 काष्ठा sockaddr_storage *mapped_rem_addr,
			 काष्ठा sockaddr_storage *remote_addr,
			 u8 nl_client)
अणु
	काष्ठा hlist_node *पंचांगp_hlist_node;
	काष्ठा hlist_head *hash_bucket_head;
	काष्ठा iwpm_remote_info *rem_info = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EINVAL;

	अगर (!iwpm_valid_client(nl_client)) अणु
		pr_info("%s: Invalid client = %d\n", __func__, nl_client);
		वापस ret;
	पूर्ण
	spin_lock_irqsave(&iwpm_reminfo_lock, flags);
	अगर (iwpm_reminfo_bucket) अणु
		hash_bucket_head = get_reminfo_hash_bucket(
					mapped_loc_addr,
					mapped_rem_addr);
		अगर (!hash_bucket_head)
			जाओ get_remote_info_निकास;
		hlist_क्रम_each_entry_safe(rem_info, पंचांगp_hlist_node,
					hash_bucket_head, hlist_node) अणु

			अगर (!iwpm_compare_sockaddr(&rem_info->mapped_loc_sockaddr,
				mapped_loc_addr) &&
				!iwpm_compare_sockaddr(&rem_info->mapped_rem_sockaddr,
				mapped_rem_addr)) अणु

				स_नकल(remote_addr, &rem_info->remote_sockaddr,
					माप(काष्ठा sockaddr_storage));
				iwpm_prपूर्णांक_sockaddr(remote_addr,
						"get_remote_info: Remote sockaddr:");

				hlist_del_init(&rem_info->hlist_node);
				kमुक्त(rem_info);
				ret = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
get_remote_info_निकास:
	spin_unlock_irqrestore(&iwpm_reminfo_lock, flags);
	वापस ret;
पूर्ण

काष्ठा iwpm_nlmsg_request *iwpm_get_nlmsg_request(__u32 nlmsg_seq,
					u8 nl_client, gfp_t gfp)
अणु
	काष्ठा iwpm_nlmsg_request *nlmsg_request = शून्य;
	अचिन्हित दीर्घ flags;

	nlmsg_request = kzalloc(माप(काष्ठा iwpm_nlmsg_request), gfp);
	अगर (!nlmsg_request)
		वापस शून्य;

	spin_lock_irqsave(&iwpm_nlmsg_req_lock, flags);
	list_add_tail(&nlmsg_request->inprocess_list, &iwpm_nlmsg_req_list);
	spin_unlock_irqrestore(&iwpm_nlmsg_req_lock, flags);

	kref_init(&nlmsg_request->kref);
	kref_get(&nlmsg_request->kref);
	nlmsg_request->nlmsg_seq = nlmsg_seq;
	nlmsg_request->nl_client = nl_client;
	nlmsg_request->request_करोne = 0;
	nlmsg_request->err_code = 0;
	sema_init(&nlmsg_request->sem, 1);
	करोwn(&nlmsg_request->sem);
	वापस nlmsg_request;
पूर्ण

व्योम iwpm_मुक्त_nlmsg_request(काष्ठा kref *kref)
अणु
	काष्ठा iwpm_nlmsg_request *nlmsg_request;
	अचिन्हित दीर्घ flags;

	nlmsg_request = container_of(kref, काष्ठा iwpm_nlmsg_request, kref);

	spin_lock_irqsave(&iwpm_nlmsg_req_lock, flags);
	list_del_init(&nlmsg_request->inprocess_list);
	spin_unlock_irqrestore(&iwpm_nlmsg_req_lock, flags);

	अगर (!nlmsg_request->request_करोne)
		pr_debug("%s Freeing incomplete nlmsg request (seq = %u).\n",
			__func__, nlmsg_request->nlmsg_seq);
	kमुक्त(nlmsg_request);
पूर्ण

काष्ठा iwpm_nlmsg_request *iwpm_find_nlmsg_request(__u32 echo_seq)
अणु
	काष्ठा iwpm_nlmsg_request *nlmsg_request;
	काष्ठा iwpm_nlmsg_request *found_request = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&iwpm_nlmsg_req_lock, flags);
	list_क्रम_each_entry(nlmsg_request, &iwpm_nlmsg_req_list,
			    inprocess_list) अणु
		अगर (nlmsg_request->nlmsg_seq == echo_seq) अणु
			found_request = nlmsg_request;
			kref_get(&nlmsg_request->kref);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&iwpm_nlmsg_req_lock, flags);
	वापस found_request;
पूर्ण

पूर्णांक iwpm_रुको_complete_req(काष्ठा iwpm_nlmsg_request *nlmsg_request)
अणु
	पूर्णांक ret;

	ret = करोwn_समयout(&nlmsg_request->sem, IWPM_NL_TIMEOUT);
	अगर (ret) अणु
		ret = -EINVAL;
		pr_info("%s: Timeout %d sec for netlink request (seq = %u)\n",
			__func__, (IWPM_NL_TIMEOUT/HZ), nlmsg_request->nlmsg_seq);
	पूर्ण अन्यथा अणु
		ret = nlmsg_request->err_code;
	पूर्ण
	kref_put(&nlmsg_request->kref, iwpm_मुक्त_nlmsg_request);
	वापस ret;
पूर्ण

पूर्णांक iwpm_get_nlmsg_seq(व्योम)
अणु
	वापस atomic_inc_वापस(&iwpm_admin.nlmsg_seq);
पूर्ण

पूर्णांक iwpm_valid_client(u8 nl_client)
अणु
	वापस iwpm_admin.client_list[nl_client];
पूर्ण

व्योम iwpm_set_valid(u8 nl_client, पूर्णांक valid)
अणु
	iwpm_admin.client_list[nl_client] = valid;
पूर्ण

/* valid client */
u32 iwpm_get_registration(u8 nl_client)
अणु
	वापस iwpm_admin.reg_list[nl_client];
पूर्ण

/* valid client */
व्योम iwpm_set_registration(u8 nl_client, u32 reg)
अणु
	iwpm_admin.reg_list[nl_client] = reg;
पूर्ण

/* valid client */
u32 iwpm_check_registration(u8 nl_client, u32 reg)
अणु
	वापस (iwpm_get_registration(nl_client) & reg);
पूर्ण

पूर्णांक iwpm_compare_sockaddr(काष्ठा sockaddr_storage *a_sockaddr,
				काष्ठा sockaddr_storage *b_sockaddr)
अणु
	अगर (a_sockaddr->ss_family != b_sockaddr->ss_family)
		वापस 1;
	अगर (a_sockaddr->ss_family == AF_INET) अणु
		काष्ठा sockaddr_in *a4_sockaddr =
			(काष्ठा sockaddr_in *)a_sockaddr;
		काष्ठा sockaddr_in *b4_sockaddr =
			(काष्ठा sockaddr_in *)b_sockaddr;
		अगर (!स_भेद(&a4_sockaddr->sin_addr,
			&b4_sockaddr->sin_addr, माप(काष्ठा in_addr))
			&& a4_sockaddr->sin_port == b4_sockaddr->sin_port)
				वापस 0;

	पूर्ण अन्यथा अगर (a_sockaddr->ss_family == AF_INET6) अणु
		काष्ठा sockaddr_in6 *a6_sockaddr =
			(काष्ठा sockaddr_in6 *)a_sockaddr;
		काष्ठा sockaddr_in6 *b6_sockaddr =
			(काष्ठा sockaddr_in6 *)b_sockaddr;
		अगर (!स_भेद(&a6_sockaddr->sin6_addr,
			&b6_sockaddr->sin6_addr, माप(काष्ठा in6_addr))
			&& a6_sockaddr->sin6_port == b6_sockaddr->sin6_port)
				वापस 0;

	पूर्ण अन्यथा अणु
		pr_err("%s: Invalid sockaddr family\n", __func__);
	पूर्ण
	वापस 1;
पूर्ण

काष्ठा sk_buff *iwpm_create_nlmsg(u32 nl_op, काष्ठा nlmsghdr **nlh,
						पूर्णांक nl_client)
अणु
	काष्ठा sk_buff *skb = शून्य;

	skb = dev_alloc_skb(IWPM_MSG_SIZE);
	अगर (!skb)
		जाओ create_nlmsg_निकास;

	अगर (!(ibnl_put_msg(skb, nlh, 0, 0, nl_client, nl_op,
			   NLM_F_REQUEST))) अणु
		pr_warn("%s: Unable to put the nlmsg header\n", __func__);
		dev_kमुक्त_skb(skb);
		skb = शून्य;
	पूर्ण
create_nlmsg_निकास:
	वापस skb;
पूर्ण

पूर्णांक iwpm_parse_nlmsg(काष्ठा netlink_callback *cb, पूर्णांक policy_max,
				   स्थिर काष्ठा nla_policy *nlmsg_policy,
				   काष्ठा nlattr *nltb[], स्थिर अक्षर *msg_type)
अणु
	पूर्णांक nlh_len = 0;
	पूर्णांक ret;
	स्थिर अक्षर *err_str = "";

	ret = nlmsg_validate_deprecated(cb->nlh, nlh_len, policy_max - 1,
					nlmsg_policy, शून्य);
	अगर (ret) अणु
		err_str = "Invalid attribute";
		जाओ parse_nlmsg_error;
	पूर्ण
	ret = nlmsg_parse_deprecated(cb->nlh, nlh_len, nltb, policy_max - 1,
				     nlmsg_policy, शून्य);
	अगर (ret) अणु
		err_str = "Unable to parse the nlmsg";
		जाओ parse_nlmsg_error;
	पूर्ण
	ret = iwpm_validate_nlmsg_attr(nltb, policy_max);
	अगर (ret) अणु
		err_str = "Invalid NULL attribute";
		जाओ parse_nlmsg_error;
	पूर्ण
	वापस 0;
parse_nlmsg_error:
	pr_warn("%s: %s (msg type %s ret = %d)\n",
			__func__, err_str, msg_type, ret);
	वापस ret;
पूर्ण

व्योम iwpm_prपूर्णांक_sockaddr(काष्ठा sockaddr_storage *sockaddr, अक्षर *msg)
अणु
	काष्ठा sockaddr_in6 *sockaddr_v6;
	काष्ठा sockaddr_in *sockaddr_v4;

	चयन (sockaddr->ss_family) अणु
	हाल AF_INET:
		sockaddr_v4 = (काष्ठा sockaddr_in *)sockaddr;
		pr_debug("%s IPV4 %pI4: %u(0x%04X)\n",
			msg, &sockaddr_v4->sin_addr,
			ntohs(sockaddr_v4->sin_port),
			ntohs(sockaddr_v4->sin_port));
		अवरोध;
	हाल AF_INET6:
		sockaddr_v6 = (काष्ठा sockaddr_in6 *)sockaddr;
		pr_debug("%s IPV6 %pI6: %u(0x%04X)\n",
			msg, &sockaddr_v6->sin6_addr,
			ntohs(sockaddr_v6->sin6_port),
			ntohs(sockaddr_v6->sin6_port));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल u32 iwpm_ipv6_jhash(काष्ठा sockaddr_in6 *ipv6_sockaddr)
अणु
	u32 ipv6_hash = jhash(&ipv6_sockaddr->sin6_addr, माप(काष्ठा in6_addr), 0);
	u32 hash = jhash_2words(ipv6_hash, (__क्रमce u32) ipv6_sockaddr->sin6_port, 0);
	वापस hash;
पूर्ण

अटल u32 iwpm_ipv4_jhash(काष्ठा sockaddr_in *ipv4_sockaddr)
अणु
	u32 ipv4_hash = jhash(&ipv4_sockaddr->sin_addr, माप(काष्ठा in_addr), 0);
	u32 hash = jhash_2words(ipv4_hash, (__क्रमce u32) ipv4_sockaddr->sin_port, 0);
	वापस hash;
पूर्ण

अटल पूर्णांक get_hash_bucket(काष्ठा sockaddr_storage *a_sockaddr,
				काष्ठा sockaddr_storage *b_sockaddr, u32 *hash)
अणु
	u32 a_hash, b_hash;

	अगर (a_sockaddr->ss_family == AF_INET) अणु
		a_hash = iwpm_ipv4_jhash((काष्ठा sockaddr_in *) a_sockaddr);
		b_hash = iwpm_ipv4_jhash((काष्ठा sockaddr_in *) b_sockaddr);

	पूर्ण अन्यथा अगर (a_sockaddr->ss_family == AF_INET6) अणु
		a_hash = iwpm_ipv6_jhash((काष्ठा sockaddr_in6 *) a_sockaddr);
		b_hash = iwpm_ipv6_jhash((काष्ठा sockaddr_in6 *) b_sockaddr);
	पूर्ण अन्यथा अणु
		pr_err("%s: Invalid sockaddr family\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (a_hash == b_hash) /* अगर port mapper isn't available */
		*hash = a_hash;
	अन्यथा
		*hash = jhash_2words(a_hash, b_hash, 0);
	वापस 0;
पूर्ण

अटल काष्ठा hlist_head *get_mapinfo_hash_bucket(काष्ठा sockaddr_storage
				*local_sockaddr, काष्ठा sockaddr_storage
				*mapped_sockaddr)
अणु
	u32 hash;
	पूर्णांक ret;

	ret = get_hash_bucket(local_sockaddr, mapped_sockaddr, &hash);
	अगर (ret)
		वापस शून्य;
	वापस &iwpm_hash_bucket[hash & IWPM_MAPINFO_HASH_MASK];
पूर्ण

अटल काष्ठा hlist_head *get_reminfo_hash_bucket(काष्ठा sockaddr_storage
				*mapped_loc_sockaddr, काष्ठा sockaddr_storage
				*mapped_rem_sockaddr)
अणु
	u32 hash;
	पूर्णांक ret;

	ret = get_hash_bucket(mapped_loc_sockaddr, mapped_rem_sockaddr, &hash);
	अगर (ret)
		वापस शून्य;
	वापस &iwpm_reminfo_bucket[hash & IWPM_REMINFO_HASH_MASK];
पूर्ण

अटल पूर्णांक send_mapinfo_num(u32 mapping_num, u8 nl_client, पूर्णांक iwpm_pid)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा nlmsghdr *nlh;
	u32 msg_seq;
	स्थिर अक्षर *err_str = "";
	पूर्णांक ret = -EINVAL;

	skb = iwpm_create_nlmsg(RDMA_NL_IWPM_MAPINFO_NUM, &nlh, nl_client);
	अगर (!skb) अणु
		err_str = "Unable to create a nlmsg";
		जाओ mapinfo_num_error;
	पूर्ण
	nlh->nlmsg_seq = iwpm_get_nlmsg_seq();
	msg_seq = 0;
	err_str = "Unable to put attribute of mapinfo number nlmsg";
	ret = ibnl_put_attr(skb, nlh, माप(u32), &msg_seq, IWPM_NLA_MAPINFO_SEQ);
	अगर (ret)
		जाओ mapinfo_num_error;
	ret = ibnl_put_attr(skb, nlh, माप(u32),
				&mapping_num, IWPM_NLA_MAPINFO_SEND_NUM);
	अगर (ret)
		जाओ mapinfo_num_error;

	nlmsg_end(skb, nlh);

	ret = rdma_nl_unicast(&init_net, skb, iwpm_pid);
	अगर (ret) अणु
		skb = शून्य;
		err_str = "Unable to send a nlmsg";
		जाओ mapinfo_num_error;
	पूर्ण
	pr_debug("%s: Sent mapping number = %d\n", __func__, mapping_num);
	वापस 0;
mapinfo_num_error:
	pr_info("%s: %s\n", __func__, err_str);
	dev_kमुक्त_skb(skb);
	वापस ret;
पूर्ण

अटल पूर्णांक send_nlmsg_करोne(काष्ठा sk_buff *skb, u8 nl_client, पूर्णांक iwpm_pid)
अणु
	काष्ठा nlmsghdr *nlh = शून्य;
	पूर्णांक ret = 0;

	अगर (!skb)
		वापस ret;
	अगर (!(ibnl_put_msg(skb, &nlh, 0, 0, nl_client,
			   RDMA_NL_IWPM_MAPINFO, NLM_F_MULTI))) अणु
		pr_warn("%s Unable to put NLMSG_DONE\n", __func__);
		dev_kमुक्त_skb(skb);
		वापस -ENOMEM;
	पूर्ण
	nlh->nlmsg_type = NLMSG_DONE;
	ret = rdma_nl_unicast(&init_net, skb, iwpm_pid);
	अगर (ret)
		pr_warn("%s Unable to send a nlmsg\n", __func__);
	वापस ret;
पूर्ण

पूर्णांक iwpm_send_mapinfo(u8 nl_client, पूर्णांक iwpm_pid)
अणु
	काष्ठा iwpm_mapping_info *map_info;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा nlmsghdr *nlh;
	पूर्णांक skb_num = 0, mapping_num = 0;
	पूर्णांक i = 0, nlmsg_bytes = 0;
	अचिन्हित दीर्घ flags;
	स्थिर अक्षर *err_str = "";
	पूर्णांक ret;

	skb = dev_alloc_skb(NLMSG_GOODSIZE);
	अगर (!skb) अणु
		ret = -ENOMEM;
		err_str = "Unable to allocate skb";
		जाओ send_mapping_info_निकास;
	पूर्ण
	skb_num++;
	spin_lock_irqsave(&iwpm_mapinfo_lock, flags);
	ret = -EINVAL;
	क्रम (i = 0; i < IWPM_MAPINFO_HASH_SIZE; i++) अणु
		hlist_क्रम_each_entry(map_info, &iwpm_hash_bucket[i],
				     hlist_node) अणु
			अगर (map_info->nl_client != nl_client)
				जारी;
			nlh = शून्य;
			अगर (!(ibnl_put_msg(skb, &nlh, 0, 0, nl_client,
					RDMA_NL_IWPM_MAPINFO, NLM_F_MULTI))) अणु
				ret = -ENOMEM;
				err_str = "Unable to put the nlmsg header";
				जाओ send_mapping_info_unlock;
			पूर्ण
			err_str = "Unable to put attribute of the nlmsg";
			ret = ibnl_put_attr(skb, nlh,
					माप(काष्ठा sockaddr_storage),
					&map_info->local_sockaddr,
					IWPM_NLA_MAPINFO_LOCAL_ADDR);
			अगर (ret)
				जाओ send_mapping_info_unlock;

			ret = ibnl_put_attr(skb, nlh,
					माप(काष्ठा sockaddr_storage),
					&map_info->mapped_sockaddr,
					IWPM_NLA_MAPINFO_MAPPED_ADDR);
			अगर (ret)
				जाओ send_mapping_info_unlock;

			अगर (iwpm_ulib_version > IWPM_UABI_VERSION_MIN) अणु
				ret = ibnl_put_attr(skb, nlh, माप(u32),
						&map_info->map_flags,
						IWPM_NLA_MAPINFO_FLAGS);
				अगर (ret)
					जाओ send_mapping_info_unlock;
			पूर्ण

			nlmsg_end(skb, nlh);

			iwpm_prपूर्णांक_sockaddr(&map_info->local_sockaddr,
				"send_mapping_info: Local sockaddr:");
			iwpm_prपूर्णांक_sockaddr(&map_info->mapped_sockaddr,
				"send_mapping_info: Mapped local sockaddr:");
			mapping_num++;
			nlmsg_bytes += nlh->nlmsg_len;

			/* check अगर all mappings can fit in one skb */
			अगर (NLMSG_GOODSIZE - nlmsg_bytes < nlh->nlmsg_len * 2) अणु
				/* and leave room क्रम NLMSG_DONE */
				nlmsg_bytes = 0;
				skb_num++;
				spin_unlock_irqrestore(&iwpm_mapinfo_lock,
						       flags);
				/* send the skb */
				ret = send_nlmsg_करोne(skb, nl_client, iwpm_pid);
				skb = शून्य;
				अगर (ret) अणु
					err_str = "Unable to send map info";
					जाओ send_mapping_info_निकास;
				पूर्ण
				अगर (skb_num == IWPM_MAPINFO_SKB_COUNT) अणु
					ret = -ENOMEM;
					err_str = "Insufficient skbs for map info";
					जाओ send_mapping_info_निकास;
				पूर्ण
				skb = dev_alloc_skb(NLMSG_GOODSIZE);
				अगर (!skb) अणु
					ret = -ENOMEM;
					err_str = "Unable to allocate skb";
					जाओ send_mapping_info_निकास;
				पूर्ण
				spin_lock_irqsave(&iwpm_mapinfo_lock, flags);
			पूर्ण
		पूर्ण
	पूर्ण
send_mapping_info_unlock:
	spin_unlock_irqrestore(&iwpm_mapinfo_lock, flags);
send_mapping_info_निकास:
	अगर (ret) अणु
		pr_warn("%s: %s (ret = %d)\n", __func__, err_str, ret);
		dev_kमुक्त_skb(skb);
		वापस ret;
	पूर्ण
	send_nlmsg_करोne(skb, nl_client, iwpm_pid);
	वापस send_mapinfo_num(mapping_num, nl_client, iwpm_pid);
पूर्ण

पूर्णांक iwpm_mapinfo_available(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक full_bucket = 0, i = 0;

	spin_lock_irqsave(&iwpm_mapinfo_lock, flags);
	अगर (iwpm_hash_bucket) अणु
		क्रम (i = 0; i < IWPM_MAPINFO_HASH_SIZE; i++) अणु
			अगर (!hlist_empty(&iwpm_hash_bucket[i])) अणु
				full_bucket = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&iwpm_mapinfo_lock, flags);
	वापस full_bucket;
पूर्ण

पूर्णांक iwpm_send_hello(u8 nl_client, पूर्णांक iwpm_pid, u16 abi_version)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा nlmsghdr *nlh;
	स्थिर अक्षर *err_str = "";
	पूर्णांक ret = -EINVAL;

	skb = iwpm_create_nlmsg(RDMA_NL_IWPM_HELLO, &nlh, nl_client);
	अगर (!skb) अणु
		err_str = "Unable to create a nlmsg";
		जाओ hello_num_error;
	पूर्ण
	nlh->nlmsg_seq = iwpm_get_nlmsg_seq();
	err_str = "Unable to put attribute of abi_version into nlmsg";
	ret = ibnl_put_attr(skb, nlh, माप(u16), &abi_version,
			    IWPM_NLA_HELLO_ABI_VERSION);
	अगर (ret)
		जाओ hello_num_error;
	nlmsg_end(skb, nlh);

	ret = rdma_nl_unicast(&init_net, skb, iwpm_pid);
	अगर (ret) अणु
		skb = शून्य;
		err_str = "Unable to send a nlmsg";
		जाओ hello_num_error;
	पूर्ण
	pr_debug("%s: Sent hello abi_version = %u\n", __func__, abi_version);
	वापस 0;
hello_num_error:
	pr_info("%s: %s\n", __func__, err_str);
	dev_kमुक्त_skb(skb);
	वापस ret;
पूर्ण
