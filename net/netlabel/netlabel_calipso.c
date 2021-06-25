<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NetLabel CALIPSO/IPv6 Support
 *
 * This file defines the CALIPSO/IPv6 functions क्रम the NetLabel प्रणाली.  The
 * NetLabel प्रणाली manages अटल and dynamic label mappings क्रम network
 * protocols such as CIPSO and CALIPSO.
 *
 * Authors: Paul Moore <paul@paul-moore.com>
 *          Huw Davies <huw@codeweavers.com>
 */

/* (c) Copyright Hewlett-Packard Development Company, L.P., 2006
 * (c) Copyright Huw Davies <huw@codeweavers.com>, 2015
 */

#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/माला.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/audit.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <net/netlink.h>
#समावेश <net/genetlink.h>
#समावेश <net/netlabel.h>
#समावेश <net/calipso.h>
#समावेश <linux/atomic.h>

#समावेश "netlabel_user.h"
#समावेश "netlabel_calipso.h"
#समावेश "netlabel_mgmt.h"
#समावेश "netlabel_domainhash.h"

/* Argument काष्ठा क्रम calipso_करोi_walk() */
काष्ठा netlbl_calipso_करोiwalk_arg अणु
	काष्ठा netlink_callback *nl_cb;
	काष्ठा sk_buff *skb;
	u32 seq;
पूर्ण;

/* Argument काष्ठा क्रम netlbl_करोmhsh_walk() */
काष्ठा netlbl_करोmhsh_walk_arg अणु
	काष्ठा netlbl_audit *audit_info;
	u32 करोi;
पूर्ण;

/* NetLabel Generic NETLINK CALIPSO family */
अटल काष्ठा genl_family netlbl_calipso_gnl_family;

/* NetLabel Netlink attribute policy */
अटल स्थिर काष्ठा nla_policy calipso_genl_policy[NLBL_CALIPSO_A_MAX + 1] = अणु
	[NLBL_CALIPSO_A_DOI] = अणु .type = NLA_U32 पूर्ण,
	[NLBL_CALIPSO_A_MTYPE] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

/* NetLabel Command Handlers
 */
/**
 * netlbl_calipso_add_pass - Adds a CALIPSO pass DOI definition
 * @info: the Generic NETLINK info block
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Create a new CALIPSO_MAP_PASS DOI definition based on the given ADD message
 * and add it to the CALIPSO engine.  Return zero on success and non-zero on
 * error.
 *
 */
अटल पूर्णांक netlbl_calipso_add_pass(काष्ठा genl_info *info,
				   काष्ठा netlbl_audit *audit_info)
अणु
	पूर्णांक ret_val;
	काष्ठा calipso_करोi *करोi_def = शून्य;

	करोi_def = kदो_स्मृति(माप(*करोi_def), GFP_KERNEL);
	अगर (!करोi_def)
		वापस -ENOMEM;
	करोi_def->type = CALIPSO_MAP_PASS;
	करोi_def->करोi = nla_get_u32(info->attrs[NLBL_CALIPSO_A_DOI]);
	ret_val = calipso_करोi_add(करोi_def, audit_info);
	अगर (ret_val != 0)
		calipso_करोi_मुक्त(करोi_def);

	वापस ret_val;
पूर्ण

/**
 * netlbl_calipso_add - Handle an ADD message
 * @skb: the NETLINK buffer
 * @info: the Generic NETLINK info block
 *
 * Description:
 * Create a new DOI definition based on the given ADD message and add it to the
 * CALIPSO engine.  Returns zero on success, negative values on failure.
 *
 */
अटल पूर्णांक netlbl_calipso_add(काष्ठा sk_buff *skb, काष्ठा genl_info *info)

अणु
	पूर्णांक ret_val = -EINVAL;
	काष्ठा netlbl_audit audit_info;

	अगर (!info->attrs[NLBL_CALIPSO_A_DOI] ||
	    !info->attrs[NLBL_CALIPSO_A_MTYPE])
		वापस -EINVAL;

	netlbl_netlink_auditinfo(skb, &audit_info);
	चयन (nla_get_u32(info->attrs[NLBL_CALIPSO_A_MTYPE])) अणु
	हाल CALIPSO_MAP_PASS:
		ret_val = netlbl_calipso_add_pass(info, &audit_info);
		अवरोध;
	पूर्ण
	अगर (ret_val == 0)
		atomic_inc(&netlabel_mgmt_protocount);

	वापस ret_val;
पूर्ण

/**
 * netlbl_calipso_list - Handle a LIST message
 * @skb: the NETLINK buffer
 * @info: the Generic NETLINK info block
 *
 * Description:
 * Process a user generated LIST message and respond accordingly.
 * Returns zero on success and negative values on error.
 *
 */
अटल पूर्णांक netlbl_calipso_list(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक ret_val;
	काष्ठा sk_buff *ans_skb = शून्य;
	व्योम *data;
	u32 करोi;
	काष्ठा calipso_करोi *करोi_def;

	अगर (!info->attrs[NLBL_CALIPSO_A_DOI]) अणु
		ret_val = -EINVAL;
		जाओ list_failure;
	पूर्ण

	करोi = nla_get_u32(info->attrs[NLBL_CALIPSO_A_DOI]);

	करोi_def = calipso_करोi_getdef(करोi);
	अगर (!करोi_def) अणु
		ret_val = -EINVAL;
		जाओ list_failure;
	पूर्ण

	ans_skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!ans_skb) अणु
		ret_val = -ENOMEM;
		जाओ list_failure_put;
	पूर्ण
	data = genlmsg_put_reply(ans_skb, info, &netlbl_calipso_gnl_family,
				 0, NLBL_CALIPSO_C_LIST);
	अगर (!data) अणु
		ret_val = -ENOMEM;
		जाओ list_failure_put;
	पूर्ण

	ret_val = nla_put_u32(ans_skb, NLBL_CALIPSO_A_MTYPE, करोi_def->type);
	अगर (ret_val != 0)
		जाओ list_failure_put;

	calipso_करोi_putdef(करोi_def);

	genlmsg_end(ans_skb, data);
	वापस genlmsg_reply(ans_skb, info);

list_failure_put:
	calipso_करोi_putdef(करोi_def);
list_failure:
	kमुक्त_skb(ans_skb);
	वापस ret_val;
पूर्ण

/**
 * netlbl_calipso_listall_cb - calipso_करोi_walk() callback क्रम LISTALL
 * @करोi_def: the CALIPSO DOI definition
 * @arg: the netlbl_calipso_करोiwalk_arg काष्ठाure
 *
 * Description:
 * This function is deचिन्हित to be used as a callback to the
 * calipso_करोi_walk() function क्रम use in generating a response क्रम a LISTALL
 * message.  Returns the size of the message on success, negative values on
 * failure.
 *
 */
अटल पूर्णांक netlbl_calipso_listall_cb(काष्ठा calipso_करोi *करोi_def, व्योम *arg)
अणु
	पूर्णांक ret_val = -ENOMEM;
	काष्ठा netlbl_calipso_करोiwalk_arg *cb_arg = arg;
	व्योम *data;

	data = genlmsg_put(cb_arg->skb, NETLINK_CB(cb_arg->nl_cb->skb).portid,
			   cb_arg->seq, &netlbl_calipso_gnl_family,
			   NLM_F_MULTI, NLBL_CALIPSO_C_LISTALL);
	अगर (!data)
		जाओ listall_cb_failure;

	ret_val = nla_put_u32(cb_arg->skb, NLBL_CALIPSO_A_DOI, करोi_def->करोi);
	अगर (ret_val != 0)
		जाओ listall_cb_failure;
	ret_val = nla_put_u32(cb_arg->skb,
			      NLBL_CALIPSO_A_MTYPE,
			      करोi_def->type);
	अगर (ret_val != 0)
		जाओ listall_cb_failure;

	genlmsg_end(cb_arg->skb, data);
	वापस 0;

listall_cb_failure:
	genlmsg_cancel(cb_arg->skb, data);
	वापस ret_val;
पूर्ण

/**
 * netlbl_calipso_listall - Handle a LISTALL message
 * @skb: the NETLINK buffer
 * @cb: the NETLINK callback
 *
 * Description:
 * Process a user generated LISTALL message and respond accordingly.  Returns
 * zero on success and negative values on error.
 *
 */
अटल पूर्णांक netlbl_calipso_listall(काष्ठा sk_buff *skb,
				  काष्ठा netlink_callback *cb)
अणु
	काष्ठा netlbl_calipso_करोiwalk_arg cb_arg;
	u32 करोi_skip = cb->args[0];

	cb_arg.nl_cb = cb;
	cb_arg.skb = skb;
	cb_arg.seq = cb->nlh->nlmsg_seq;

	calipso_करोi_walk(&करोi_skip, netlbl_calipso_listall_cb, &cb_arg);

	cb->args[0] = करोi_skip;
	वापस skb->len;
पूर्ण

/**
 * netlbl_calipso_हटाओ_cb - netlbl_calipso_हटाओ() callback क्रम REMOVE
 * @entry: LSM करोमुख्य mapping entry
 * @arg: the netlbl_करोmhsh_walk_arg काष्ठाure
 *
 * Description:
 * This function is पूर्णांकended क्रम use by netlbl_calipso_हटाओ() as the callback
 * क्रम the netlbl_करोmhsh_walk() function; it हटाओs LSM करोमुख्य map entries
 * which are associated with the CALIPSO DOI specअगरied in @arg.  Returns zero on
 * success, negative values on failure.
 *
 */
अटल पूर्णांक netlbl_calipso_हटाओ_cb(काष्ठा netlbl_करोm_map *entry, व्योम *arg)
अणु
	काष्ठा netlbl_करोmhsh_walk_arg *cb_arg = arg;

	अगर (entry->def.type == NETLBL_NLTYPE_CALIPSO &&
	    entry->def.calipso->करोi == cb_arg->करोi)
		वापस netlbl_करोmhsh_हटाओ_entry(entry, cb_arg->audit_info);

	वापस 0;
पूर्ण

/**
 * netlbl_calipso_हटाओ - Handle a REMOVE message
 * @skb: the NETLINK buffer
 * @info: the Generic NETLINK info block
 *
 * Description:
 * Process a user generated REMOVE message and respond accordingly.  Returns
 * zero on success, negative values on failure.
 *
 */
अटल पूर्णांक netlbl_calipso_हटाओ(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक ret_val = -EINVAL;
	काष्ठा netlbl_करोmhsh_walk_arg cb_arg;
	काष्ठा netlbl_audit audit_info;
	u32 skip_bkt = 0;
	u32 skip_chain = 0;

	अगर (!info->attrs[NLBL_CALIPSO_A_DOI])
		वापस -EINVAL;

	netlbl_netlink_auditinfo(skb, &audit_info);
	cb_arg.करोi = nla_get_u32(info->attrs[NLBL_CALIPSO_A_DOI]);
	cb_arg.audit_info = &audit_info;
	ret_val = netlbl_करोmhsh_walk(&skip_bkt, &skip_chain,
				     netlbl_calipso_हटाओ_cb, &cb_arg);
	अगर (ret_val == 0 || ret_val == -ENOENT) अणु
		ret_val = calipso_करोi_हटाओ(cb_arg.करोi, &audit_info);
		अगर (ret_val == 0)
			atomic_dec(&netlabel_mgmt_protocount);
	पूर्ण

	वापस ret_val;
पूर्ण

/* NetLabel Generic NETLINK Command Definitions
 */

अटल स्थिर काष्ठा genl_small_ops netlbl_calipso_ops[] = अणु
	अणु
	.cmd = NLBL_CALIPSO_C_ADD,
	.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	.flags = GENL_ADMIN_PERM,
	.करोit = netlbl_calipso_add,
	.dumpit = शून्य,
	पूर्ण,
	अणु
	.cmd = NLBL_CALIPSO_C_REMOVE,
	.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	.flags = GENL_ADMIN_PERM,
	.करोit = netlbl_calipso_हटाओ,
	.dumpit = शून्य,
	पूर्ण,
	अणु
	.cmd = NLBL_CALIPSO_C_LIST,
	.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	.flags = 0,
	.करोit = netlbl_calipso_list,
	.dumpit = शून्य,
	पूर्ण,
	अणु
	.cmd = NLBL_CALIPSO_C_LISTALL,
	.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	.flags = 0,
	.करोit = शून्य,
	.dumpit = netlbl_calipso_listall,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family netlbl_calipso_gnl_family __ro_after_init = अणु
	.hdrsize = 0,
	.name = NETLBL_NLTYPE_CALIPSO_NAME,
	.version = NETLBL_PROTO_VERSION,
	.maxattr = NLBL_CALIPSO_A_MAX,
	.policy = calipso_genl_policy,
	.module = THIS_MODULE,
	.small_ops = netlbl_calipso_ops,
	.n_small_ops = ARRAY_SIZE(netlbl_calipso_ops),
पूर्ण;

/* NetLabel Generic NETLINK Protocol Functions
 */

/**
 * netlbl_calipso_genl_init - Register the CALIPSO NetLabel component
 *
 * Description:
 * Register the CALIPSO packet NetLabel component with the Generic NETLINK
 * mechanism.  Returns zero on success, negative values on failure.
 *
 */
पूर्णांक __init netlbl_calipso_genl_init(व्योम)
अणु
	वापस genl_रेजिस्टर_family(&netlbl_calipso_gnl_family);
पूर्ण

अटल स्थिर काष्ठा netlbl_calipso_ops *calipso_ops;

/**
 * netlbl_calipso_ops_रेजिस्टर - Register the CALIPSO operations
 * @ops: ops to रेजिस्टर
 *
 * Description:
 * Register the CALIPSO packet engine operations.
 *
 */
स्थिर काष्ठा netlbl_calipso_ops *
netlbl_calipso_ops_रेजिस्टर(स्थिर काष्ठा netlbl_calipso_ops *ops)
अणु
	वापस xchg(&calipso_ops, ops);
पूर्ण
EXPORT_SYMBOL(netlbl_calipso_ops_रेजिस्टर);

अटल स्थिर काष्ठा netlbl_calipso_ops *netlbl_calipso_ops_get(व्योम)
अणु
	वापस READ_ONCE(calipso_ops);
पूर्ण

/**
 * calipso_करोi_add - Add a new DOI to the CALIPSO protocol engine
 * @करोi_def: the DOI काष्ठाure
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * The caller defines a new DOI क्रम use by the CALIPSO engine and calls this
 * function to add it to the list of acceptable करोमुख्यs.  The caller must
 * ensure that the mapping table specअगरied in @करोi_def->map meets all of the
 * requirements of the mapping type (see calipso.h क्रम details).  Returns
 * zero on success and non-zero on failure.
 *
 */
पूर्णांक calipso_करोi_add(काष्ठा calipso_करोi *करोi_def,
		    काष्ठा netlbl_audit *audit_info)
अणु
	पूर्णांक ret_val = -ENOMSG;
	स्थिर काष्ठा netlbl_calipso_ops *ops = netlbl_calipso_ops_get();

	अगर (ops)
		ret_val = ops->करोi_add(करोi_def, audit_info);
	वापस ret_val;
पूर्ण

/**
 * calipso_करोi_मुक्त - Frees a DOI definition
 * @करोi_def: the DOI definition
 *
 * Description:
 * This function मुक्तs all of the memory associated with a DOI definition.
 *
 */
व्योम calipso_करोi_मुक्त(काष्ठा calipso_करोi *करोi_def)
अणु
	स्थिर काष्ठा netlbl_calipso_ops *ops = netlbl_calipso_ops_get();

	अगर (ops)
		ops->करोi_मुक्त(करोi_def);
पूर्ण

/**
 * calipso_करोi_हटाओ - Remove an existing DOI from the CALIPSO protocol engine
 * @करोi: the DOI value
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Removes a DOI definition from the CALIPSO engine.  The NetLabel routines will
 * be called to release their own LSM करोमुख्य mappings as well as our own
 * करोमुख्य list.  Returns zero on success and negative values on failure.
 *
 */
पूर्णांक calipso_करोi_हटाओ(u32 करोi, काष्ठा netlbl_audit *audit_info)
अणु
	पूर्णांक ret_val = -ENOMSG;
	स्थिर काष्ठा netlbl_calipso_ops *ops = netlbl_calipso_ops_get();

	अगर (ops)
		ret_val = ops->करोi_हटाओ(करोi, audit_info);
	वापस ret_val;
पूर्ण

/**
 * calipso_करोi_getdef - Returns a reference to a valid DOI definition
 * @करोi: the DOI value
 *
 * Description:
 * Searches क्रम a valid DOI definition and अगर one is found it is वापसed to
 * the caller.  Otherwise शून्य is वापसed.  The caller must ensure that
 * calipso_करोi_putdef() is called when the caller is करोne.
 *
 */
काष्ठा calipso_करोi *calipso_करोi_getdef(u32 करोi)
अणु
	काष्ठा calipso_करोi *ret_val = शून्य;
	स्थिर काष्ठा netlbl_calipso_ops *ops = netlbl_calipso_ops_get();

	अगर (ops)
		ret_val = ops->करोi_getdef(करोi);
	वापस ret_val;
पूर्ण

/**
 * calipso_करोi_putdef - Releases a reference क्रम the given DOI definition
 * @करोi_def: the DOI definition
 *
 * Description:
 * Releases a DOI definition reference obtained from calipso_करोi_getdef().
 *
 */
व्योम calipso_करोi_putdef(काष्ठा calipso_करोi *करोi_def)
अणु
	स्थिर काष्ठा netlbl_calipso_ops *ops = netlbl_calipso_ops_get();

	अगर (ops)
		ops->करोi_putdef(करोi_def);
पूर्ण

/**
 * calipso_करोi_walk - Iterate through the DOI definitions
 * @skip_cnt: skip past this number of DOI definitions, updated
 * @callback: callback क्रम each DOI definition
 * @cb_arg: argument क्रम the callback function
 *
 * Description:
 * Iterate over the DOI definition list, skipping the first @skip_cnt entries.
 * For each entry call @callback, अगर @callback वापसs a negative value stop
 * 'walking' through the list and वापस.  Updates the value in @skip_cnt upon
 * वापस.  Returns zero on success, negative values on failure.
 *
 */
पूर्णांक calipso_करोi_walk(u32 *skip_cnt,
		     पूर्णांक (*callback)(काष्ठा calipso_करोi *करोi_def, व्योम *arg),
		     व्योम *cb_arg)
अणु
	पूर्णांक ret_val = -ENOMSG;
	स्थिर काष्ठा netlbl_calipso_ops *ops = netlbl_calipso_ops_get();

	अगर (ops)
		ret_val = ops->करोi_walk(skip_cnt, callback, cb_arg);
	वापस ret_val;
पूर्ण

/**
 * calipso_sock_getattr - Get the security attributes from a sock
 * @sk: the sock
 * @secattr: the security attributes
 *
 * Description:
 * Query @sk to see अगर there is a CALIPSO option attached to the sock and अगर
 * there is वापस the CALIPSO security attributes in @secattr.  This function
 * requires that @sk be locked, or निजीly held, but it करोes not करो any
 * locking itself.  Returns zero on success and negative values on failure.
 *
 */
पूर्णांक calipso_sock_getattr(काष्ठा sock *sk, काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val = -ENOMSG;
	स्थिर काष्ठा netlbl_calipso_ops *ops = netlbl_calipso_ops_get();

	अगर (ops)
		ret_val = ops->sock_getattr(sk, secattr);
	वापस ret_val;
पूर्ण

/**
 * calipso_sock_setattr - Add a CALIPSO option to a socket
 * @sk: the socket
 * @करोi_def: the CALIPSO DOI to use
 * @secattr: the specअगरic security attributes of the socket
 *
 * Description:
 * Set the CALIPSO option on the given socket using the DOI definition and
 * security attributes passed to the function.  This function requires
 * exclusive access to @sk, which means it either needs to be in the
 * process of being created or locked.  Returns zero on success and negative
 * values on failure.
 *
 */
पूर्णांक calipso_sock_setattr(काष्ठा sock *sk,
			 स्थिर काष्ठा calipso_करोi *करोi_def,
			 स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val = -ENOMSG;
	स्थिर काष्ठा netlbl_calipso_ops *ops = netlbl_calipso_ops_get();

	अगर (ops)
		ret_val = ops->sock_setattr(sk, करोi_def, secattr);
	वापस ret_val;
पूर्ण

/**
 * calipso_sock_delattr - Delete the CALIPSO option from a socket
 * @sk: the socket
 *
 * Description:
 * Removes the CALIPSO option from a socket, अगर present.
 *
 */
व्योम calipso_sock_delattr(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा netlbl_calipso_ops *ops = netlbl_calipso_ops_get();

	अगर (ops)
		ops->sock_delattr(sk);
पूर्ण

/**
 * calipso_req_setattr - Add a CALIPSO option to a connection request socket
 * @req: the connection request socket
 * @करोi_def: the CALIPSO DOI to use
 * @secattr: the specअगरic security attributes of the socket
 *
 * Description:
 * Set the CALIPSO option on the given socket using the DOI definition and
 * security attributes passed to the function.  Returns zero on success and
 * negative values on failure.
 *
 */
पूर्णांक calipso_req_setattr(काष्ठा request_sock *req,
			स्थिर काष्ठा calipso_करोi *करोi_def,
			स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val = -ENOMSG;
	स्थिर काष्ठा netlbl_calipso_ops *ops = netlbl_calipso_ops_get();

	अगर (ops)
		ret_val = ops->req_setattr(req, करोi_def, secattr);
	वापस ret_val;
पूर्ण

/**
 * calipso_req_delattr - Delete the CALIPSO option from a request socket
 * @req: the request socket
 *
 * Description:
 * Removes the CALIPSO option from a request socket, अगर present.
 *
 */
व्योम calipso_req_delattr(काष्ठा request_sock *req)
अणु
	स्थिर काष्ठा netlbl_calipso_ops *ops = netlbl_calipso_ops_get();

	अगर (ops)
		ops->req_delattr(req);
पूर्ण

/**
 * calipso_optptr - Find the CALIPSO option in the packet
 * @skb: the packet
 *
 * Description:
 * Parse the packet's IP header looking क्रम a CALIPSO option.  Returns a poपूर्णांकer
 * to the start of the CALIPSO option on success, शून्य अगर one अगर not found.
 *
 */
अचिन्हित अक्षर *calipso_optptr(स्थिर काष्ठा sk_buff *skb)
अणु
	अचिन्हित अक्षर *ret_val = शून्य;
	स्थिर काष्ठा netlbl_calipso_ops *ops = netlbl_calipso_ops_get();

	अगर (ops)
		ret_val = ops->skbuff_optptr(skb);
	वापस ret_val;
पूर्ण

/**
 * calipso_getattr - Get the security attributes from a memory block.
 * @calipso: the CALIPSO option
 * @secattr: the security attributes
 *
 * Description:
 * Inspect @calipso and वापस the security attributes in @secattr.
 * Returns zero on success and negative values on failure.
 *
 */
पूर्णांक calipso_getattr(स्थिर अचिन्हित अक्षर *calipso,
		    काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val = -ENOMSG;
	स्थिर काष्ठा netlbl_calipso_ops *ops = netlbl_calipso_ops_get();

	अगर (ops)
		ret_val = ops->opt_getattr(calipso, secattr);
	वापस ret_val;
पूर्ण

/**
 * calipso_skbuff_setattr - Set the CALIPSO option on a packet
 * @skb: the packet
 * @करोi_def: the CALIPSO DOI to use
 * @secattr: the security attributes
 *
 * Description:
 * Set the CALIPSO option on the given packet based on the security attributes.
 * Returns a poपूर्णांकer to the IP header on success and शून्य on failure.
 *
 */
पूर्णांक calipso_skbuff_setattr(काष्ठा sk_buff *skb,
			   स्थिर काष्ठा calipso_करोi *करोi_def,
			   स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val = -ENOMSG;
	स्थिर काष्ठा netlbl_calipso_ops *ops = netlbl_calipso_ops_get();

	अगर (ops)
		ret_val = ops->skbuff_setattr(skb, करोi_def, secattr);
	वापस ret_val;
पूर्ण

/**
 * calipso_skbuff_delattr - Delete any CALIPSO options from a packet
 * @skb: the packet
 *
 * Description:
 * Removes any and all CALIPSO options from the given packet.  Returns zero on
 * success, negative values on failure.
 *
 */
पूर्णांक calipso_skbuff_delattr(काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret_val = -ENOMSG;
	स्थिर काष्ठा netlbl_calipso_ops *ops = netlbl_calipso_ops_get();

	अगर (ops)
		ret_val = ops->skbuff_delattr(skb);
	वापस ret_val;
पूर्ण

/**
 * calipso_cache_invalidate - Invalidates the current CALIPSO cache
 *
 * Description:
 * Invalidates and मुक्तs any entries in the CALIPSO cache.  Returns zero on
 * success and negative values on failure.
 *
 */
व्योम calipso_cache_invalidate(व्योम)
अणु
	स्थिर काष्ठा netlbl_calipso_ops *ops = netlbl_calipso_ops_get();

	अगर (ops)
		ops->cache_invalidate();
पूर्ण

/**
 * calipso_cache_add - Add an entry to the CALIPSO cache
 * @calipso_ptr: the CALIPSO option
 * @secattr: the packet's security attributes
 *
 * Description:
 * Add a new entry पूर्णांकo the CALIPSO label mapping cache.
 * Returns zero on success, negative values on failure.
 *
 */
पूर्णांक calipso_cache_add(स्थिर अचिन्हित अक्षर *calipso_ptr,
		      स्थिर काष्ठा netlbl_lsm_secattr *secattr)

अणु
	पूर्णांक ret_val = -ENOMSG;
	स्थिर काष्ठा netlbl_calipso_ops *ops = netlbl_calipso_ops_get();

	अगर (ops)
		ret_val = ops->cache_add(calipso_ptr, secattr);
	वापस ret_val;
पूर्ण
