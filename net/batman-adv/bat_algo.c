<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner, Simon Wunderlich
 */

#समावेश "main.h"

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/netlink.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/माला.स>
#समावेश <net/genetlink.h>
#समावेश <net/netlink.h>
#समावेश <uapi/linux/baपंचांगan_adv.h>

#समावेश "bat_algo.h"
#समावेश "netlink.h"

अक्षर batadv_routing_algo[20] = "BATMAN_IV";
अटल काष्ठा hlist_head batadv_algo_list;

/**
 * batadv_algo_init() - Initialize baपंचांगan-adv algorithm management data
 *  काष्ठाures
 */
व्योम batadv_algo_init(व्योम)
अणु
	INIT_HLIST_HEAD(&batadv_algo_list);
पूर्ण

/**
 * batadv_algo_get() - Search क्रम algorithm with specअगरic name
 * @name: algorithm name to find
 *
 * Return: Poपूर्णांकer to batadv_algo_ops on success, शून्य otherwise
 */
काष्ठा batadv_algo_ops *batadv_algo_get(स्थिर अक्षर *name)
अणु
	काष्ठा batadv_algo_ops *bat_algo_ops = शून्य, *bat_algo_ops_पंचांगp;

	hlist_क्रम_each_entry(bat_algo_ops_पंचांगp, &batadv_algo_list, list) अणु
		अगर (म_भेद(bat_algo_ops_पंचांगp->name, name) != 0)
			जारी;

		bat_algo_ops = bat_algo_ops_पंचांगp;
		अवरोध;
	पूर्ण

	वापस bat_algo_ops;
पूर्ण

/**
 * batadv_algo_रेजिस्टर() - Register callbacks क्रम a mesh algorithm
 * @bat_algo_ops: mesh algorithm callbacks to add
 *
 * Return: 0 on success or negative error number in हाल of failure
 */
पूर्णांक batadv_algo_रेजिस्टर(काष्ठा batadv_algo_ops *bat_algo_ops)
अणु
	काष्ठा batadv_algo_ops *bat_algo_ops_पंचांगp;

	bat_algo_ops_पंचांगp = batadv_algo_get(bat_algo_ops->name);
	अगर (bat_algo_ops_पंचांगp) अणु
		pr_info("Trying to register already registered routing algorithm: %s\n",
			bat_algo_ops->name);
		वापस -EEXIST;
	पूर्ण

	/* all algorithms must implement all ops (क्रम now) */
	अगर (!bat_algo_ops->अगरace.enable ||
	    !bat_algo_ops->अगरace.disable ||
	    !bat_algo_ops->अगरace.update_mac ||
	    !bat_algo_ops->अगरace.primary_set ||
	    !bat_algo_ops->neigh.cmp ||
	    !bat_algo_ops->neigh.is_similar_or_better) अणु
		pr_info("Routing algo '%s' does not implement required ops\n",
			bat_algo_ops->name);
		वापस -EINVAL;
	पूर्ण

	INIT_HLIST_NODE(&bat_algo_ops->list);
	hlist_add_head(&bat_algo_ops->list, &batadv_algo_list);

	वापस 0;
पूर्ण

/**
 * batadv_algo_select() - Select algorithm of soft पूर्णांकerface
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @name: name of the algorithm to select
 *
 * The algorithm callbacks क्रम the soft पूर्णांकerface will be set when the algorithm
 * with the correct name was found. Any previous selected algorithm will not be
 * deinitialized and the new selected algorithm will also not be initialized.
 * It is thereक्रमe not allowed to call batadv_algo_select outside the creation
 * function of the soft पूर्णांकerface.
 *
 * Return: 0 on success or negative error number in हाल of failure
 */
पूर्णांक batadv_algo_select(काष्ठा batadv_priv *bat_priv, स्थिर अक्षर *name)
अणु
	काष्ठा batadv_algo_ops *bat_algo_ops;

	bat_algo_ops = batadv_algo_get(name);
	अगर (!bat_algo_ops)
		वापस -EINVAL;

	bat_priv->algo_ops = bat_algo_ops;

	वापस 0;
पूर्ण

अटल पूर्णांक batadv_param_set_ra(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	काष्ठा batadv_algo_ops *bat_algo_ops;
	अक्षर *algo_name = (अक्षर *)val;
	माप_प्रकार name_len = म_माप(algo_name);

	अगर (name_len > 0 && algo_name[name_len - 1] == '\n')
		algo_name[name_len - 1] = '\0';

	bat_algo_ops = batadv_algo_get(algo_name);
	अगर (!bat_algo_ops) अणु
		pr_err("Routing algorithm '%s' is not supported\n", algo_name);
		वापस -EINVAL;
	पूर्ण

	वापस param_set_copystring(algo_name, kp);
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops batadv_param_ops_ra = अणु
	.set = batadv_param_set_ra,
	.get = param_get_string,
पूर्ण;

अटल काष्ठा kparam_string batadv_param_string_ra = अणु
	.maxlen = माप(batadv_routing_algo),
	.string = batadv_routing_algo,
पूर्ण;

module_param_cb(routing_algo, &batadv_param_ops_ra, &batadv_param_string_ra,
		0644);

/**
 * batadv_algo_dump_entry() - fill in inक्रमmation about one supported routing
 *  algorithm
 * @msg: netlink message to be sent back
 * @portid: Port to reply to
 * @seq: Sequence number of message
 * @bat_algo_ops: Algorithm to be dumped
 *
 * Return: Error number, or 0 on success
 */
अटल पूर्णांक batadv_algo_dump_entry(काष्ठा sk_buff *msg, u32 portid, u32 seq,
				  काष्ठा batadv_algo_ops *bat_algo_ops)
अणु
	व्योम *hdr;

	hdr = genlmsg_put(msg, portid, seq, &batadv_netlink_family,
			  NLM_F_MULTI, BATADV_CMD_GET_ROUTING_ALGOS);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (nla_put_string(msg, BATADV_ATTR_ALGO_NAME, bat_algo_ops->name))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	वापस 0;

 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

/**
 * batadv_algo_dump() - fill in inक्रमmation about supported routing
 *  algorithms
 * @msg: netlink message to be sent back
 * @cb: Parameters to the netlink request
 *
 * Return: Length of reply message.
 */
पूर्णांक batadv_algo_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb)
अणु
	पूर्णांक portid = NETLINK_CB(cb->skb).portid;
	काष्ठा batadv_algo_ops *bat_algo_ops;
	पूर्णांक skip = cb->args[0];
	पूर्णांक i = 0;

	hlist_क्रम_each_entry(bat_algo_ops, &batadv_algo_list, list) अणु
		अगर (i++ < skip)
			जारी;

		अगर (batadv_algo_dump_entry(msg, portid, cb->nlh->nlmsg_seq,
					   bat_algo_ops)) अणु
			i--;
			अवरोध;
		पूर्ण
	पूर्ण

	cb->args[0] = i;

	वापस msg->len;
पूर्ण
