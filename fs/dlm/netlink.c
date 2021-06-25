<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2007 Red Hat, Inc.  All rights reserved.
 */

#समावेश <net/genetlink.h>
#समावेश <linux/dlm.h>
#समावेश <linux/dlm_netlink.h>
#समावेश <linux/gfp.h>

#समावेश "dlm_internal.h"

अटल uपूर्णांक32_t dlm_nl_seqnum;
अटल uपूर्णांक32_t listener_nlportid;

अटल काष्ठा genl_family family;

अटल पूर्णांक prepare_data(u8 cmd, काष्ठा sk_buff **skbp, माप_प्रकार size)
अणु
	काष्ठा sk_buff *skb;
	व्योम *data;

	skb = genlmsg_new(size, GFP_NOFS);
	अगर (!skb)
		वापस -ENOMEM;

	/* add the message headers */
	data = genlmsg_put(skb, 0, dlm_nl_seqnum++, &family, 0, cmd);
	अगर (!data) अणु
		nlmsg_मुक्त(skb);
		वापस -EINVAL;
	पूर्ण

	*skbp = skb;
	वापस 0;
पूर्ण

अटल काष्ठा dlm_lock_data *mk_data(काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *ret;

	ret = nla_reserve(skb, DLM_TYPE_LOCK, माप(काष्ठा dlm_lock_data));
	अगर (!ret)
		वापस शून्य;
	वापस nla_data(ret);
पूर्ण

अटल पूर्णांक send_data(काष्ठा sk_buff *skb)
अणु
	काष्ठा genlmsghdr *genlhdr = nlmsg_data((काष्ठा nlmsghdr *)skb->data);
	व्योम *data = genlmsg_data(genlhdr);

	genlmsg_end(skb, data);

	वापस genlmsg_unicast(&init_net, skb, listener_nlportid);
पूर्ण

अटल पूर्णांक user_cmd(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	listener_nlportid = info->snd_portid;
	prपूर्णांकk("user_cmd nlpid %u\n", listener_nlportid);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा genl_small_ops dlm_nl_ops[] = अणु
	अणु
		.cmd	= DLM_CMD_HELLO,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit	= user_cmd,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family family __ro_after_init = अणु
	.name		= DLM_GENL_NAME,
	.version	= DLM_GENL_VERSION,
	.small_ops	= dlm_nl_ops,
	.n_small_ops	= ARRAY_SIZE(dlm_nl_ops),
	.module		= THIS_MODULE,
पूर्ण;

पूर्णांक __init dlm_netlink_init(व्योम)
अणु
	वापस genl_रेजिस्टर_family(&family);
पूर्ण

व्योम dlm_netlink_निकास(व्योम)
अणु
	genl_unरेजिस्टर_family(&family);
पूर्ण

अटल व्योम fill_data(काष्ठा dlm_lock_data *data, काष्ठा dlm_lkb *lkb)
अणु
	काष्ठा dlm_rsb *r = lkb->lkb_resource;

	स_रखो(data, 0, माप(काष्ठा dlm_lock_data));

	data->version = DLM_LOCK_DATA_VERSION;
	data->nodeid = lkb->lkb_nodeid;
	data->ownpid = lkb->lkb_ownpid;
	data->id = lkb->lkb_id;
	data->remid = lkb->lkb_remid;
	data->status = lkb->lkb_status;
	data->grmode = lkb->lkb_grmode;
	data->rqmode = lkb->lkb_rqmode;
	अगर (lkb->lkb_ua)
		data->xid = lkb->lkb_ua->xid;
	अगर (r) अणु
		data->lockspace_id = r->res_ls->ls_global_id;
		data->resource_namelen = r->res_length;
		स_नकल(data->resource_name, r->res_name, r->res_length);
	पूर्ण
पूर्ण

व्योम dlm_समयout_warn(काष्ठा dlm_lkb *lkb)
अणु
	काष्ठा sk_buff *send_skb;
	काष्ठा dlm_lock_data *data;
	माप_प्रकार size;
	पूर्णांक rv;

	size = nla_total_size(माप(काष्ठा dlm_lock_data)) +
	       nla_total_size(0); /* why this? */

	rv = prepare_data(DLM_CMD_TIMEOUT, &send_skb, size);
	अगर (rv < 0)
		वापस;

	data = mk_data(send_skb);
	अगर (!data) अणु
		nlmsg_मुक्त(send_skb);
		वापस;
	पूर्ण

	fill_data(data, lkb);

	send_data(send_skb);
पूर्ण

