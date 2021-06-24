<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
   drbd_nl.c

   This file is part of DRBD by Philipp Reisner and Lars Ellenberg.

   Copyright (C) 2001-2008, LINBIT Inक्रमmation Technologies GmbH.
   Copyright (C) 1999-2008, Philipp Reisner <philipp.reisner@linbit.com>.
   Copyright (C) 2002-2008, Lars Ellenberg <lars.ellenberg@linbit.com>.


 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/drbd.h>
#समावेश <linux/in.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/slab.h>
#समावेश <linux/blkpg.h>
#समावेश <linux/cpumask.h>
#समावेश "drbd_int.h"
#समावेश "drbd_protocol.h"
#समावेश "drbd_req.h"
#समावेश "drbd_state_change.h"
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/drbd_सीमा.स>
#समावेश <linux/kthपढ़ो.h>

#समावेश <net/genetlink.h>

/* .करोit */
// पूर्णांक drbd_adm_create_resource(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
// पूर्णांक drbd_adm_delete_resource(काष्ठा sk_buff *skb, काष्ठा genl_info *info);

पूर्णांक drbd_adm_new_minor(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक drbd_adm_del_minor(काष्ठा sk_buff *skb, काष्ठा genl_info *info);

पूर्णांक drbd_adm_new_resource(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक drbd_adm_del_resource(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक drbd_adm_करोwn(काष्ठा sk_buff *skb, काष्ठा genl_info *info);

पूर्णांक drbd_adm_set_role(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक drbd_adm_attach(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक drbd_adm_disk_opts(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक drbd_adm_detach(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक drbd_adm_connect(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक drbd_adm_net_opts(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक drbd_adm_resize(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक drbd_adm_start_ov(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक drbd_adm_new_c_uuid(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक drbd_adm_disconnect(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक drbd_adm_invalidate(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक drbd_adm_invalidate_peer(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक drbd_adm_छोड़ो_sync(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक drbd_adm_resume_sync(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक drbd_adm_suspend_io(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक drbd_adm_resume_io(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक drbd_adm_outdate(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक drbd_adm_resource_opts(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक drbd_adm_get_status(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक drbd_adm_get_समयout_type(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
/* .dumpit */
पूर्णांक drbd_adm_get_status_all(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);
पूर्णांक drbd_adm_dump_resources(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);
पूर्णांक drbd_adm_dump_devices(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);
पूर्णांक drbd_adm_dump_devices_करोne(काष्ठा netlink_callback *cb);
पूर्णांक drbd_adm_dump_connections(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);
पूर्णांक drbd_adm_dump_connections_करोne(काष्ठा netlink_callback *cb);
पूर्णांक drbd_adm_dump_peer_devices(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);
पूर्णांक drbd_adm_dump_peer_devices_करोne(काष्ठा netlink_callback *cb);
पूर्णांक drbd_adm_get_initial_state(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);

#समावेश <linux/drbd_genl_api.h>
#समावेश "drbd_nla.h"
#समावेश <linux/genl_magic_func.h>

अटल atomic_t drbd_genl_seq = ATOMIC_INIT(2); /* two. */
अटल atomic_t notअगरy_genl_seq = ATOMIC_INIT(2); /* two. */

DEFINE_MUTEX(notअगरication_mutex);

/* used blkdev_get_by_path, to claim our meta data device(s) */
अटल अक्षर *drbd_m_holder = "Hands off! this is DRBD's meta data device.";

अटल व्योम drbd_adm_send_reply(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	genlmsg_end(skb, genlmsg_data(nlmsg_data(nlmsg_hdr(skb))));
	अगर (genlmsg_reply(skb, info))
		pr_err("error sending genl reply\n");
पूर्ण

/* Used on a fresh "drbd_adm_prepare"d reply_skb, this cannot fail: The only
 * reason it could fail was no space in skb, and there are 4k available. */
अटल पूर्णांक drbd_msg_put_info(काष्ठा sk_buff *skb, स्थिर अक्षर *info)
अणु
	काष्ठा nlattr *nla;
	पूर्णांक err = -EMSGSIZE;

	अगर (!info || !info[0])
		वापस 0;

	nla = nla_nest_start_noflag(skb, DRBD_NLA_CFG_REPLY);
	अगर (!nla)
		वापस err;

	err = nla_put_string(skb, T_info_text, info);
	अगर (err) अणु
		nla_nest_cancel(skb, nla);
		वापस err;
	पूर्ण अन्यथा
		nla_nest_end(skb, nla);
	वापस 0;
पूर्ण

__म_लिखो(2, 3)
अटल पूर्णांक drbd_msg_प्र_लिखो_info(काष्ठा sk_buff *skb, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	काष्ठा nlattr *nla, *txt;
	पूर्णांक err = -EMSGSIZE;
	पूर्णांक len;

	nla = nla_nest_start_noflag(skb, DRBD_NLA_CFG_REPLY);
	अगर (!nla)
		वापस err;

	txt = nla_reserve(skb, T_info_text, 256);
	अगर (!txt) अणु
		nla_nest_cancel(skb, nla);
		वापस err;
	पूर्ण
	बहु_शुरू(args, fmt);
	len = vscnम_लिखो(nla_data(txt), 256, fmt, args);
	बहु_पूर्ण(args);

	/* maybe: retry with larger reserve, अगर truncated */
	txt->nla_len = nla_attr_size(len+1);
	nlmsg_trim(skb, (अक्षर*)txt + NLA_ALIGN(txt->nla_len));
	nla_nest_end(skb, nla);

	वापस 0;
पूर्ण

/* This would be a good candidate क्रम a "pre_doit" hook,
 * and per-family निजी info->poपूर्णांकers.
 * But we need to stay compatible with older kernels.
 * If it वापसs successfully, adm_ctx members are valid.
 *
 * At this poपूर्णांक, we still rely on the global genl_lock().
 * If we want to aव्योम that, and allow "genl_family.parallel_ops", we may need
 * to add additional synchronization against object deकाष्ठाion/modअगरication.
 */
#घोषणा DRBD_ADM_NEED_MINOR	1
#घोषणा DRBD_ADM_NEED_RESOURCE	2
#घोषणा DRBD_ADM_NEED_CONNECTION 4
अटल पूर्णांक drbd_adm_prepare(काष्ठा drbd_config_context *adm_ctx,
	काष्ठा sk_buff *skb, काष्ठा genl_info *info, अचिन्हित flags)
अणु
	काष्ठा drbd_genlmsghdr *d_in = info->userhdr;
	स्थिर u8 cmd = info->genlhdr->cmd;
	पूर्णांक err;

	स_रखो(adm_ctx, 0, माप(*adm_ctx));

	/* genl_rcv_msg only checks क्रम CAP_NET_ADMIN on "GENL_ADMIN_PERM" :( */
	अगर (cmd != DRBD_ADM_GET_STATUS && !capable(CAP_NET_ADMIN))
	       वापस -EPERM;

	adm_ctx->reply_skb = genlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!adm_ctx->reply_skb) अणु
		err = -ENOMEM;
		जाओ fail;
	पूर्ण

	adm_ctx->reply_dh = genlmsg_put_reply(adm_ctx->reply_skb,
					info, &drbd_genl_family, 0, cmd);
	/* put of a few bytes पूर्णांकo a fresh skb of >= 4k will always succeed.
	 * but anyways */
	अगर (!adm_ctx->reply_dh) अणु
		err = -ENOMEM;
		जाओ fail;
	पूर्ण

	adm_ctx->reply_dh->minor = d_in->minor;
	adm_ctx->reply_dh->ret_code = NO_ERROR;

	adm_ctx->volume = VOLUME_UNSPECIFIED;
	अगर (info->attrs[DRBD_NLA_CFG_CONTEXT]) अणु
		काष्ठा nlattr *nla;
		/* parse and validate only */
		err = drbd_cfg_context_from_attrs(शून्य, info);
		अगर (err)
			जाओ fail;

		/* It was present, and valid,
		 * copy it over to the reply skb. */
		err = nla_put_nohdr(adm_ctx->reply_skb,
				info->attrs[DRBD_NLA_CFG_CONTEXT]->nla_len,
				info->attrs[DRBD_NLA_CFG_CONTEXT]);
		अगर (err)
			जाओ fail;

		/* and assign stuff to the adm_ctx */
		nla = nested_attr_tb[__nla_type(T_ctx_volume)];
		अगर (nla)
			adm_ctx->volume = nla_get_u32(nla);
		nla = nested_attr_tb[__nla_type(T_ctx_resource_name)];
		अगर (nla)
			adm_ctx->resource_name = nla_data(nla);
		adm_ctx->my_addr = nested_attr_tb[__nla_type(T_ctx_my_addr)];
		adm_ctx->peer_addr = nested_attr_tb[__nla_type(T_ctx_peer_addr)];
		अगर ((adm_ctx->my_addr &&
		     nla_len(adm_ctx->my_addr) > माप(adm_ctx->connection->my_addr)) ||
		    (adm_ctx->peer_addr &&
		     nla_len(adm_ctx->peer_addr) > माप(adm_ctx->connection->peer_addr))) अणु
			err = -EINVAL;
			जाओ fail;
		पूर्ण
	पूर्ण

	adm_ctx->minor = d_in->minor;
	adm_ctx->device = minor_to_device(d_in->minor);

	/* We are रक्षित by the global genl_lock().
	 * But we may explicitly drop it/retake it in drbd_adm_set_role(),
	 * so make sure this object stays around. */
	अगर (adm_ctx->device)
		kref_get(&adm_ctx->device->kref);

	अगर (adm_ctx->resource_name) अणु
		adm_ctx->resource = drbd_find_resource(adm_ctx->resource_name);
	पूर्ण

	अगर (!adm_ctx->device && (flags & DRBD_ADM_NEED_MINOR)) अणु
		drbd_msg_put_info(adm_ctx->reply_skb, "unknown minor");
		वापस ERR_MINOR_INVALID;
	पूर्ण
	अगर (!adm_ctx->resource && (flags & DRBD_ADM_NEED_RESOURCE)) अणु
		drbd_msg_put_info(adm_ctx->reply_skb, "unknown resource");
		अगर (adm_ctx->resource_name)
			वापस ERR_RES_NOT_KNOWN;
		वापस ERR_INVALID_REQUEST;
	पूर्ण

	अगर (flags & DRBD_ADM_NEED_CONNECTION) अणु
		अगर (adm_ctx->resource) अणु
			drbd_msg_put_info(adm_ctx->reply_skb, "no resource name expected");
			वापस ERR_INVALID_REQUEST;
		पूर्ण
		अगर (adm_ctx->device) अणु
			drbd_msg_put_info(adm_ctx->reply_skb, "no minor number expected");
			वापस ERR_INVALID_REQUEST;
		पूर्ण
		अगर (adm_ctx->my_addr && adm_ctx->peer_addr)
			adm_ctx->connection = conn_get_by_addrs(nla_data(adm_ctx->my_addr),
							  nla_len(adm_ctx->my_addr),
							  nla_data(adm_ctx->peer_addr),
							  nla_len(adm_ctx->peer_addr));
		अगर (!adm_ctx->connection) अणु
			drbd_msg_put_info(adm_ctx->reply_skb, "unknown connection");
			वापस ERR_INVALID_REQUEST;
		पूर्ण
	पूर्ण

	/* some more paranoia, अगर the request was over-determined */
	अगर (adm_ctx->device && adm_ctx->resource &&
	    adm_ctx->device->resource != adm_ctx->resource) अणु
		pr_warn("request: minor=%u, resource=%s; but that minor belongs to resource %s\n",
			adm_ctx->minor, adm_ctx->resource->name,
			adm_ctx->device->resource->name);
		drbd_msg_put_info(adm_ctx->reply_skb, "minor exists in different resource");
		वापस ERR_INVALID_REQUEST;
	पूर्ण
	अगर (adm_ctx->device &&
	    adm_ctx->volume != VOLUME_UNSPECIFIED &&
	    adm_ctx->volume != adm_ctx->device->vnr) अणु
		pr_warn("request: minor=%u, volume=%u; but that minor is volume %u in %s\n",
			adm_ctx->minor, adm_ctx->volume,
			adm_ctx->device->vnr, adm_ctx->device->resource->name);
		drbd_msg_put_info(adm_ctx->reply_skb, "minor exists as different volume");
		वापस ERR_INVALID_REQUEST;
	पूर्ण

	/* still, provide adm_ctx->resource always, अगर possible. */
	अगर (!adm_ctx->resource) अणु
		adm_ctx->resource = adm_ctx->device ? adm_ctx->device->resource
			: adm_ctx->connection ? adm_ctx->connection->resource : शून्य;
		अगर (adm_ctx->resource)
			kref_get(&adm_ctx->resource->kref);
	पूर्ण

	वापस NO_ERROR;

fail:
	nlmsg_मुक्त(adm_ctx->reply_skb);
	adm_ctx->reply_skb = शून्य;
	वापस err;
पूर्ण

अटल पूर्णांक drbd_adm_finish(काष्ठा drbd_config_context *adm_ctx,
	काष्ठा genl_info *info, पूर्णांक retcode)
अणु
	अगर (adm_ctx->device) अणु
		kref_put(&adm_ctx->device->kref, drbd_destroy_device);
		adm_ctx->device = शून्य;
	पूर्ण
	अगर (adm_ctx->connection) अणु
		kref_put(&adm_ctx->connection->kref, &drbd_destroy_connection);
		adm_ctx->connection = शून्य;
	पूर्ण
	अगर (adm_ctx->resource) अणु
		kref_put(&adm_ctx->resource->kref, drbd_destroy_resource);
		adm_ctx->resource = शून्य;
	पूर्ण

	अगर (!adm_ctx->reply_skb)
		वापस -ENOMEM;

	adm_ctx->reply_dh->ret_code = retcode;
	drbd_adm_send_reply(adm_ctx->reply_skb, info);
	वापस 0;
पूर्ण

अटल व्योम setup_khelper_env(काष्ठा drbd_connection *connection, अक्षर **envp)
अणु
	अक्षर *afs;

	/* FIXME: A future version will not allow this हाल. */
	अगर (connection->my_addr_len == 0 || connection->peer_addr_len == 0)
		वापस;

	चयन (((काष्ठा sockaddr *)&connection->peer_addr)->sa_family) अणु
	हाल AF_INET6:
		afs = "ipv6";
		snम_लिखो(envp[4], 60, "DRBD_PEER_ADDRESS=%pI6",
			 &((काष्ठा sockaddr_in6 *)&connection->peer_addr)->sin6_addr);
		अवरोध;
	हाल AF_INET:
		afs = "ipv4";
		snम_लिखो(envp[4], 60, "DRBD_PEER_ADDRESS=%pI4",
			 &((काष्ठा sockaddr_in *)&connection->peer_addr)->sin_addr);
		अवरोध;
	शेष:
		afs = "ssocks";
		snम_लिखो(envp[4], 60, "DRBD_PEER_ADDRESS=%pI4",
			 &((काष्ठा sockaddr_in *)&connection->peer_addr)->sin_addr);
	पूर्ण
	snम_लिखो(envp[3], 20, "DRBD_PEER_AF=%s", afs);
पूर्ण

पूर्णांक drbd_khelper(काष्ठा drbd_device *device, अक्षर *cmd)
अणु
	अक्षर *envp[] = अणु "HOME=/",
			"TERM=linux",
			"PATH=/sbin:/usr/sbin:/bin:/usr/bin",
			 (अक्षर[20]) अणु पूर्ण, /* address family */
			 (अक्षर[60]) अणु पूर्ण, /* address */
			शून्य पूर्ण;
	अक्षर mb[14];
	अक्षर *argv[] = अणुdrbd_usermode_helper, cmd, mb, शून्य पूर्ण;
	काष्ठा drbd_connection *connection = first_peer_device(device)->connection;
	काष्ठा sib_info sib;
	पूर्णांक ret;

	अगर (current == connection->worker.task)
		set_bit(CALLBACK_PENDING, &connection->flags);

	snम_लिखो(mb, 14, "minor-%d", device_to_minor(device));
	setup_khelper_env(connection, envp);

	/* The helper may take some समय.
	 * ग_लिखो out any unsynced meta data changes now */
	drbd_md_sync(device);

	drbd_info(device, "helper command: %s %s %s\n", drbd_usermode_helper, cmd, mb);
	sib.sib_reason = SIB_HELPER_PRE;
	sib.helper_name = cmd;
	drbd_bcast_event(device, &sib);
	notअगरy_helper(NOTIFY_CALL, device, connection, cmd, 0);
	ret = call_usermodehelper(drbd_usermode_helper, argv, envp, UMH_WAIT_PROC);
	अगर (ret)
		drbd_warn(device, "helper command: %s %s %s exit code %u (0x%x)\n",
				drbd_usermode_helper, cmd, mb,
				(ret >> 8) & 0xff, ret);
	अन्यथा
		drbd_info(device, "helper command: %s %s %s exit code %u (0x%x)\n",
				drbd_usermode_helper, cmd, mb,
				(ret >> 8) & 0xff, ret);
	sib.sib_reason = SIB_HELPER_POST;
	sib.helper_निकास_code = ret;
	drbd_bcast_event(device, &sib);
	notअगरy_helper(NOTIFY_RESPONSE, device, connection, cmd, ret);

	अगर (current == connection->worker.task)
		clear_bit(CALLBACK_PENDING, &connection->flags);

	अगर (ret < 0) /* Ignore any ERRNOs we got. */
		ret = 0;

	वापस ret;
पूर्ण

क्रमागत drbd_peer_state conn_khelper(काष्ठा drbd_connection *connection, अक्षर *cmd)
अणु
	अक्षर *envp[] = अणु "HOME=/",
			"TERM=linux",
			"PATH=/sbin:/usr/sbin:/bin:/usr/bin",
			 (अक्षर[20]) अणु पूर्ण, /* address family */
			 (अक्षर[60]) अणु पूर्ण, /* address */
			शून्य पूर्ण;
	अक्षर *resource_name = connection->resource->name;
	अक्षर *argv[] = अणुdrbd_usermode_helper, cmd, resource_name, शून्य पूर्ण;
	पूर्णांक ret;

	setup_khelper_env(connection, envp);
	conn_md_sync(connection);

	drbd_info(connection, "helper command: %s %s %s\n", drbd_usermode_helper, cmd, resource_name);
	/* TODO: conn_bcast_event() ?? */
	notअगरy_helper(NOTIFY_CALL, शून्य, connection, cmd, 0);

	ret = call_usermodehelper(drbd_usermode_helper, argv, envp, UMH_WAIT_PROC);
	अगर (ret)
		drbd_warn(connection, "helper command: %s %s %s exit code %u (0x%x)\n",
			  drbd_usermode_helper, cmd, resource_name,
			  (ret >> 8) & 0xff, ret);
	अन्यथा
		drbd_info(connection, "helper command: %s %s %s exit code %u (0x%x)\n",
			  drbd_usermode_helper, cmd, resource_name,
			  (ret >> 8) & 0xff, ret);
	/* TODO: conn_bcast_event() ?? */
	notअगरy_helper(NOTIFY_RESPONSE, शून्य, connection, cmd, ret);

	अगर (ret < 0) /* Ignore any ERRNOs we got. */
		ret = 0;

	वापस ret;
पूर्ण

अटल क्रमागत drbd_fencing_p highest_fencing_policy(काष्ठा drbd_connection *connection)
अणु
	क्रमागत drbd_fencing_p fp = FP_NOT_AVAIL;
	काष्ठा drbd_peer_device *peer_device;
	पूर्णांक vnr;

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr) अणु
		काष्ठा drbd_device *device = peer_device->device;
		अगर (get_ldev_अगर_state(device, D_CONSISTENT)) अणु
			काष्ठा disk_conf *disk_conf =
				rcu_dereference(peer_device->device->ldev->disk_conf);
			fp = max_t(क्रमागत drbd_fencing_p, fp, disk_conf->fencing);
			put_ldev(device);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस fp;
पूर्ण

अटल bool resource_is_supended(काष्ठा drbd_resource *resource)
अणु
	वापस resource->susp || resource->susp_fen || resource->susp_nod;
पूर्ण

bool conn_try_outdate_peer(काष्ठा drbd_connection *connection)
अणु
	काष्ठा drbd_resource * स्थिर resource = connection->resource;
	अचिन्हित पूर्णांक connect_cnt;
	जोड़ drbd_state mask = अणु पूर्ण;
	जोड़ drbd_state val = अणु पूर्ण;
	क्रमागत drbd_fencing_p fp;
	अक्षर *ex_to_string;
	पूर्णांक r;

	spin_lock_irq(&resource->req_lock);
	अगर (connection->cstate >= C_WF_REPORT_PARAMS) अणु
		drbd_err(connection, "Expected cstate < C_WF_REPORT_PARAMS\n");
		spin_unlock_irq(&resource->req_lock);
		वापस false;
	पूर्ण

	connect_cnt = connection->connect_cnt;
	spin_unlock_irq(&resource->req_lock);

	fp = highest_fencing_policy(connection);
	चयन (fp) अणु
	हाल FP_NOT_AVAIL:
		drbd_warn(connection, "Not fencing peer, I'm not even Consistent myself.\n");
		spin_lock_irq(&resource->req_lock);
		अगर (connection->cstate < C_WF_REPORT_PARAMS) अणु
			_conn_request_state(connection,
					    (जोड़ drbd_state) अणु अणु .susp_fen = 1 पूर्ण पूर्ण,
					    (जोड़ drbd_state) अणु अणु .susp_fen = 0 पूर्ण पूर्ण,
					    CS_VERBOSE | CS_HARD | CS_DC_SUSP);
			/* We are no दीर्घer suspended due to the fencing policy.
			 * We may still be suspended due to the on-no-data-accessible policy.
			 * If that was OND_IO_ERROR, fail pending requests. */
			अगर (!resource_is_supended(resource))
				_tl_restart(connection, CONNECTION_LOST_WHILE_PENDING);
		पूर्ण
		/* Else: in हाल we raced with a connection handshake,
		 * let the handshake figure out अगर we maybe can RESEND,
		 * and करो not resume/fail pending requests here.
		 * Worst हाल is we stay suspended क्रम now, which may be
		 * resolved by either re-establishing the replication link, or
		 * the next link failure, or eventually the administrator.  */
		spin_unlock_irq(&resource->req_lock);
		वापस false;

	हाल FP_DONT_CARE:
		वापस true;
	शेष: ;
	पूर्ण

	r = conn_khelper(connection, "fence-peer");

	चयन ((r>>8) & 0xff) अणु
	हाल P_INCONSISTENT: /* peer is inconsistent */
		ex_to_string = "peer is inconsistent or worse";
		mask.pdsk = D_MASK;
		val.pdsk = D_INCONSISTENT;
		अवरोध;
	हाल P_OUTDATED: /* peer got outdated, or was alपढ़ोy outdated */
		ex_to_string = "peer was fenced";
		mask.pdsk = D_MASK;
		val.pdsk = D_OUTDATED;
		अवरोध;
	हाल P_DOWN: /* peer was करोwn */
		अगर (conn_highest_disk(connection) == D_UP_TO_DATE) अणु
			/* we will(have) create(d) a new UUID anyways... */
			ex_to_string = "peer is unreachable, assumed to be dead";
			mask.pdsk = D_MASK;
			val.pdsk = D_OUTDATED;
		पूर्ण अन्यथा अणु
			ex_to_string = "peer unreachable, doing nothing since disk != UpToDate";
		पूर्ण
		अवरोध;
	हाल P_PRIMARY: /* Peer is primary, voluntarily outdate myself.
		 * This is useful when an unconnected R_SECONDARY is asked to
		 * become R_PRIMARY, but finds the other peer being active. */
		ex_to_string = "peer is active";
		drbd_warn(connection, "Peer is primary, outdating myself.\n");
		mask.disk = D_MASK;
		val.disk = D_OUTDATED;
		अवरोध;
	हाल P_FENCING:
		/* THINK: करो we need to handle this
		 * like हाल 4, or more like हाल 5? */
		अगर (fp != FP_STONITH)
			drbd_err(connection, "fence-peer() = 7 && fencing != Stonith !!!\n");
		ex_to_string = "peer was stonithed";
		mask.pdsk = D_MASK;
		val.pdsk = D_OUTDATED;
		अवरोध;
	शेष:
		/* The script is broken ... */
		drbd_err(connection, "fence-peer helper broken, returned %d\n", (r>>8)&0xff);
		वापस false; /* Eventually leave IO frozen */
	पूर्ण

	drbd_info(connection, "fence-peer helper returned %d (%s)\n",
		  (r>>8) & 0xff, ex_to_string);

	/* Not using
	   conn_request_state(connection, mask, val, CS_VERBOSE);
	   here, because we might were able to re-establish the connection in the
	   meanसमय. */
	spin_lock_irq(&resource->req_lock);
	अगर (connection->cstate < C_WF_REPORT_PARAMS && !test_bit(STATE_SENT, &connection->flags)) अणु
		अगर (connection->connect_cnt != connect_cnt)
			/* In हाल the connection was established and droped
			   जबतक the fence-peer handler was running, ignore it */
			drbd_info(connection, "Ignoring fence-peer exit code\n");
		अन्यथा
			_conn_request_state(connection, mask, val, CS_VERBOSE);
	पूर्ण
	spin_unlock_irq(&resource->req_lock);

	वापस conn_highest_pdsk(connection) <= D_OUTDATED;
पूर्ण

अटल पूर्णांक _try_outdate_peer_async(व्योम *data)
अणु
	काष्ठा drbd_connection *connection = (काष्ठा drbd_connection *)data;

	conn_try_outdate_peer(connection);

	kref_put(&connection->kref, drbd_destroy_connection);
	वापस 0;
पूर्ण

व्योम conn_try_outdate_peer_async(काष्ठा drbd_connection *connection)
अणु
	काष्ठा task_काष्ठा *opa;

	kref_get(&connection->kref);
	/* We may have just sent a संकेत to this thपढ़ो
	 * to get it out of some blocking network function.
	 * Clear संकेतs; otherwise kthपढ़ो_run(), which पूर्णांकernally uses
	 * रुको_on_completion_समाप्तable(), will mistake our pending संकेत
	 * क्रम a new fatal संकेत and fail. */
	flush_संकेतs(current);
	opa = kthपढ़ो_run(_try_outdate_peer_async, connection, "drbd_async_h");
	अगर (IS_ERR(opa)) अणु
		drbd_err(connection, "out of mem, failed to invoke fence-peer helper\n");
		kref_put(&connection->kref, drbd_destroy_connection);
	पूर्ण
पूर्ण

क्रमागत drbd_state_rv
drbd_set_role(काष्ठा drbd_device *स्थिर device, क्रमागत drbd_role new_role, पूर्णांक क्रमce)
अणु
	काष्ठा drbd_peer_device *स्थिर peer_device = first_peer_device(device);
	काष्ठा drbd_connection *स्थिर connection = peer_device ? peer_device->connection : शून्य;
	स्थिर पूर्णांक max_tries = 4;
	क्रमागत drbd_state_rv rv = SS_UNKNOWN_ERROR;
	काष्ठा net_conf *nc;
	पूर्णांक try = 0;
	पूर्णांक क्रमced = 0;
	जोड़ drbd_state mask, val;

	अगर (new_role == R_PRIMARY) अणु
		काष्ठा drbd_connection *connection;

		/* Detect dead peers as soon as possible.  */

		rcu_पढ़ो_lock();
		क्रम_each_connection(connection, device->resource)
			request_ping(connection);
		rcu_पढ़ो_unlock();
	पूर्ण

	mutex_lock(device->state_mutex);

	mask.i = 0; mask.role = R_MASK;
	val.i  = 0; val.role  = new_role;

	जबतक (try++ < max_tries) अणु
		rv = _drbd_request_state_holding_state_mutex(device, mask, val, CS_WAIT_COMPLETE);

		/* in हाल we first succeeded to outdate,
		 * but now suddenly could establish a connection */
		अगर (rv == SS_CW_FAILED_BY_PEER && mask.pdsk != 0) अणु
			val.pdsk = 0;
			mask.pdsk = 0;
			जारी;
		पूर्ण

		अगर (rv == SS_NO_UP_TO_DATE_DISK && क्रमce &&
		    (device->state.disk < D_UP_TO_DATE &&
		     device->state.disk >= D_INCONSISTENT)) अणु
			mask.disk = D_MASK;
			val.disk  = D_UP_TO_DATE;
			क्रमced = 1;
			जारी;
		पूर्ण

		अगर (rv == SS_NO_UP_TO_DATE_DISK &&
		    device->state.disk == D_CONSISTENT && mask.pdsk == 0) अणु
			D_ASSERT(device, device->state.pdsk == D_UNKNOWN);

			अगर (conn_try_outdate_peer(connection)) अणु
				val.disk = D_UP_TO_DATE;
				mask.disk = D_MASK;
			पूर्ण
			जारी;
		पूर्ण

		अगर (rv == SS_NOTHING_TO_DO)
			जाओ out;
		अगर (rv == SS_PRIMARY_NOP && mask.pdsk == 0) अणु
			अगर (!conn_try_outdate_peer(connection) && क्रमce) अणु
				drbd_warn(device, "Forced into split brain situation!\n");
				mask.pdsk = D_MASK;
				val.pdsk  = D_OUTDATED;

			पूर्ण
			जारी;
		पूर्ण
		अगर (rv == SS_TWO_PRIMARIES) अणु
			/* Maybe the peer is detected as dead very soon...
			   retry at most once more in this हाल. */
			अगर (try < max_tries) अणु
				पूर्णांक समयo;
				try = max_tries - 1;
				rcu_पढ़ो_lock();
				nc = rcu_dereference(connection->net_conf);
				समयo = nc ? (nc->ping_समयo + 1) * HZ / 10 : 1;
				rcu_पढ़ो_unlock();
				schedule_समयout_पूर्णांकerruptible(समयo);
			पूर्ण
			जारी;
		पूर्ण
		अगर (rv < SS_SUCCESS) अणु
			rv = _drbd_request_state(device, mask, val,
						CS_VERBOSE + CS_WAIT_COMPLETE);
			अगर (rv < SS_SUCCESS)
				जाओ out;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (rv < SS_SUCCESS)
		जाओ out;

	अगर (क्रमced)
		drbd_warn(device, "Forced to consider local data as UpToDate!\n");

	/* Wait until nothing is on the fly :) */
	रुको_event(device->misc_रुको, atomic_पढ़ो(&device->ap_pending_cnt) == 0);

	/* FIXME also रुको क्रम all pending P_BARRIER_ACK? */

	अगर (new_role == R_SECONDARY) अणु
		अगर (get_ldev(device)) अणु
			device->ldev->md.uuid[UI_CURRENT] &= ~(u64)1;
			put_ldev(device);
		पूर्ण
	पूर्ण अन्यथा अणु
		mutex_lock(&device->resource->conf_update);
		nc = connection->net_conf;
		अगर (nc)
			nc->discard_my_data = 0; /* without copy; single bit op is atomic */
		mutex_unlock(&device->resource->conf_update);

		अगर (get_ldev(device)) अणु
			अगर (((device->state.conn < C_CONNECTED ||
			       device->state.pdsk <= D_FAILED)
			      && device->ldev->md.uuid[UI_BITMAP] == 0) || क्रमced)
				drbd_uuid_new_current(device);

			device->ldev->md.uuid[UI_CURRENT] |=  (u64)1;
			put_ldev(device);
		पूर्ण
	पूर्ण

	/* ग_लिखोout of activity log covered areas of the biपंचांगap
	 * to stable storage करोne in after state change alपढ़ोy */

	अगर (device->state.conn >= C_WF_REPORT_PARAMS) अणु
		/* अगर this was क्रमced, we should consider sync */
		अगर (क्रमced)
			drbd_send_uuids(peer_device);
		drbd_send_current_state(peer_device);
	पूर्ण

	drbd_md_sync(device);
	set_disk_ro(device->vdisk, new_role == R_SECONDARY);
	kobject_uevent(&disk_to_dev(device->vdisk)->kobj, KOBJ_CHANGE);
out:
	mutex_unlock(device->state_mutex);
	वापस rv;
पूर्ण

अटल स्थिर अक्षर *from_attrs_err_to_txt(पूर्णांक err)
अणु
	वापस	err == -ENOMSG ? "required attribute missing" :
		err == -EOPNOTSUPP ? "unknown mandatory attribute" :
		err == -EEXIST ? "can not change invariant setting" :
		"invalid attribute value";
पूर्ण

पूर्णांक drbd_adm_set_role(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा drbd_config_context adm_ctx;
	काष्ठा set_role_parms parms;
	पूर्णांक err;
	क्रमागत drbd_ret_code retcode;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_MINOR);
	अगर (!adm_ctx.reply_skb)
		वापस retcode;
	अगर (retcode != NO_ERROR)
		जाओ out;

	स_रखो(&parms, 0, माप(parms));
	अगर (info->attrs[DRBD_NLA_SET_ROLE_PARMS]) अणु
		err = set_role_parms_from_attrs(&parms, info);
		अगर (err) अणु
			retcode = ERR_MANDATORY_TAG;
			drbd_msg_put_info(adm_ctx.reply_skb, from_attrs_err_to_txt(err));
			जाओ out;
		पूर्ण
	पूर्ण
	genl_unlock();
	mutex_lock(&adm_ctx.resource->adm_mutex);

	अगर (info->genlhdr->cmd == DRBD_ADM_PRIMARY)
		retcode = (क्रमागत drbd_ret_code)drbd_set_role(adm_ctx.device,
						R_PRIMARY, parms.assume_uptodate);
	अन्यथा
		retcode = (क्रमागत drbd_ret_code)drbd_set_role(adm_ctx.device,
						R_SECONDARY, 0);

	mutex_unlock(&adm_ctx.resource->adm_mutex);
	genl_lock();
out:
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;
पूर्ण

/* Initializes the md.*_offset members, so we are able to find
 * the on disk meta data.
 *
 * We currently have two possible layouts:
 * बाह्यal:
 *   |----------- md_size_sect ------------------|
 *   [ 4k superblock ][ activity log ][  Biपंचांगap  ]
 *   | al_offset == 8 |
 *   | bm_offset = al_offset + X      |
 *  ==> biपंचांगap sectors = md_size_sect - bm_offset
 *
 * पूर्णांकernal:
 *            |----------- md_size_sect ------------------|
 * [data.....][  Biपंचांगap  ][ activity log ][ 4k superblock ]
 *                        | al_offset < 0 |
 *            | bm_offset = al_offset - Y |
 *  ==> biपंचांगap sectors = Y = al_offset - bm_offset
 *
 *  Activity log size used to be fixed 32kB,
 *  but is about to become configurable.
 */
अटल व्योम drbd_md_set_sector_offsets(काष्ठा drbd_device *device,
				       काष्ठा drbd_backing_dev *bdev)
अणु
	sector_t md_size_sect = 0;
	अचिन्हित पूर्णांक al_size_sect = bdev->md.al_size_4k * 8;

	bdev->md.md_offset = drbd_md_ss(bdev);

	चयन (bdev->md.meta_dev_idx) अणु
	शेष:
		/* v07 style fixed size indexed meta data */
		bdev->md.md_size_sect = MD_128MB_SECT;
		bdev->md.al_offset = MD_4kB_SECT;
		bdev->md.bm_offset = MD_4kB_SECT + al_size_sect;
		अवरोध;
	हाल DRBD_MD_INDEX_FLEX_EXT:
		/* just occupy the full device; unit: sectors */
		bdev->md.md_size_sect = drbd_get_capacity(bdev->md_bdev);
		bdev->md.al_offset = MD_4kB_SECT;
		bdev->md.bm_offset = MD_4kB_SECT + al_size_sect;
		अवरोध;
	हाल DRBD_MD_INDEX_INTERNAL:
	हाल DRBD_MD_INDEX_FLEX_INT:
		/* al size is still fixed */
		bdev->md.al_offset = -al_size_sect;
		/* we need (slightly less than) ~ this much biपंचांगap sectors: */
		md_size_sect = drbd_get_capacity(bdev->backing_bdev);
		md_size_sect = ALIGN(md_size_sect, BM_SECT_PER_EXT);
		md_size_sect = BM_SECT_TO_EXT(md_size_sect);
		md_size_sect = ALIGN(md_size_sect, 8);

		/* plus the "drbd meta data super block",
		 * and the activity log; */
		md_size_sect += MD_4kB_SECT + al_size_sect;

		bdev->md.md_size_sect = md_size_sect;
		/* biपंचांगap offset is adjusted by 'super' block size */
		bdev->md.bm_offset   = -md_size_sect + MD_4kB_SECT;
		अवरोध;
	पूर्ण
पूर्ण

/* input size is expected to be in KB */
अक्षर *ppsize(अक्षर *buf, अचिन्हित दीर्घ दीर्घ size)
अणु
	/* Needs 9 bytes at max including trailing NUL:
	 * -1ULL ==> "16384 EB" */
	अटल अक्षर units[] = अणु 'K', 'M', 'G', 'T', 'P', 'E' पूर्ण;
	पूर्णांक base = 0;
	जबतक (size >= 10000 && base < माप(units)-1) अणु
		/* shअगरt + round */
		size = (size >> 10) + !!(size & (1<<9));
		base++;
	पूर्ण
	प्र_लिखो(buf, "%u %cB", (अचिन्हित)size, units[base]);

	वापस buf;
पूर्ण

/* there is still a theoretical deadlock when called from receiver
 * on an D_INCONSISTENT R_PRIMARY:
 *  remote READ करोes inc_ap_bio, receiver would need to receive answer
 *  packet from remote to dec_ap_bio again.
 *  receiver receive_sizes(), comes here,
 *  रुकोs क्रम ap_bio_cnt == 0. -> deadlock.
 * but this cannot happen, actually, because:
 *  R_PRIMARY D_INCONSISTENT, and peer's disk is unreachable
 *  (not connected, or bad/no disk on peer):
 *  see drbd_fail_request_early, ap_bio_cnt is zero.
 *  R_PRIMARY D_INCONSISTENT, and C_SYNC_TARGET:
 *  peer may not initiate a resize.
 */
/* Note these are not to be confused with
 * drbd_adm_suspend_io/drbd_adm_resume_io,
 * which are (sub) state changes triggered by admin (drbdsetup),
 * and can be दीर्घ lived.
 * This changes an device->flag, is triggered by drbd पूर्णांकernals,
 * and should be लघु-lived. */
/* It needs to be a counter, since multiple thपढ़ोs might
   independently suspend and resume IO. */
व्योम drbd_suspend_io(काष्ठा drbd_device *device)
अणु
	atomic_inc(&device->suspend_cnt);
	अगर (drbd_suspended(device))
		वापस;
	रुको_event(device->misc_रुको, !atomic_पढ़ो(&device->ap_bio_cnt));
पूर्ण

व्योम drbd_resume_io(काष्ठा drbd_device *device)
अणु
	अगर (atomic_dec_and_test(&device->suspend_cnt))
		wake_up(&device->misc_रुको);
पूर्ण

/*
 * drbd_determine_dev_size() -  Sets the right device size obeying all स्थिरraपूर्णांकs
 * @device:	DRBD device.
 *
 * Returns 0 on success, negative वापस values indicate errors.
 * You should call drbd_md_sync() after calling this function.
 */
क्रमागत determine_dev_size
drbd_determine_dev_size(काष्ठा drbd_device *device, क्रमागत dds_flags flags, काष्ठा resize_parms *rs) __must_hold(local)
अणु
	काष्ठा md_offsets_and_sizes अणु
		u64 last_agreed_sect;
		u64 md_offset;
		s32 al_offset;
		s32 bm_offset;
		u32 md_size_sect;

		u32 al_stripes;
		u32 al_stripe_size_4k;
	पूर्ण prev;
	sector_t u_size, size;
	काष्ठा drbd_md *md = &device->ldev->md;
	व्योम *buffer;

	पूर्णांक md_moved, la_size_changed;
	क्रमागत determine_dev_size rv = DS_UNCHANGED;

	/* We may change the on-disk offsets of our meta data below.  Lock out
	 * anything that may cause meta data IO, to aव्योम acting on incomplete
	 * layout changes or scribbling over meta data that is in the process
	 * of being moved.
	 *
	 * Move is not exactly correct, btw, currently we have all our meta
	 * data in core memory, to "move" it we just ग_लिखो it all out, there
	 * are no पढ़ोs. */
	drbd_suspend_io(device);
	buffer = drbd_md_get_buffer(device, __func__); /* Lock meta-data IO */
	अगर (!buffer) अणु
		drbd_resume_io(device);
		वापस DS_ERROR;
	पूर्ण

	/* remember current offset and sizes */
	prev.last_agreed_sect = md->la_size_sect;
	prev.md_offset = md->md_offset;
	prev.al_offset = md->al_offset;
	prev.bm_offset = md->bm_offset;
	prev.md_size_sect = md->md_size_sect;
	prev.al_stripes = md->al_stripes;
	prev.al_stripe_size_4k = md->al_stripe_size_4k;

	अगर (rs) अणु
		/* rs is non शून्य अगर we should change the AL layout only */
		md->al_stripes = rs->al_stripes;
		md->al_stripe_size_4k = rs->al_stripe_size / 4;
		md->al_size_4k = (u64)rs->al_stripes * rs->al_stripe_size / 4;
	पूर्ण

	drbd_md_set_sector_offsets(device, device->ldev);

	rcu_पढ़ो_lock();
	u_size = rcu_dereference(device->ldev->disk_conf)->disk_size;
	rcu_पढ़ो_unlock();
	size = drbd_new_dev_size(device, device->ldev, u_size, flags & DDSF_FORCED);

	अगर (size < prev.last_agreed_sect) अणु
		अगर (rs && u_size == 0) अणु
			/* Remove "rs &&" later. This check should always be active, but
			   right now the receiver expects the permissive behavior */
			drbd_warn(device, "Implicit shrink not allowed. "
				 "Use --size=%llus for explicit shrink.\n",
				 (अचिन्हित दीर्घ दीर्घ)size);
			rv = DS_ERROR_SHRINK;
		पूर्ण
		अगर (u_size > size)
			rv = DS_ERROR_SPACE_MD;
		अगर (rv != DS_UNCHANGED)
			जाओ err_out;
	पूर्ण

	अगर (get_capacity(device->vdisk) != size ||
	    drbd_bm_capacity(device) != size) अणु
		पूर्णांक err;
		err = drbd_bm_resize(device, size, !(flags & DDSF_NO_RESYNC));
		अगर (unlikely(err)) अणु
			/* currently there is only one error: ENOMEM! */
			size = drbd_bm_capacity(device);
			अगर (size == 0) अणु
				drbd_err(device, "OUT OF MEMORY! "
				    "Could not allocate bitmap!\n");
			पूर्ण अन्यथा अणु
				drbd_err(device, "BM resizing failed. "
				    "Leaving size unchanged\n");
			पूर्ण
			rv = DS_ERROR;
		पूर्ण
		/* racy, see comments above. */
		drbd_set_my_capacity(device, size);
		md->la_size_sect = size;
	पूर्ण
	अगर (rv <= DS_ERROR)
		जाओ err_out;

	la_size_changed = (prev.last_agreed_sect != md->la_size_sect);

	md_moved = prev.md_offset    != md->md_offset
		|| prev.md_size_sect != md->md_size_sect;

	अगर (la_size_changed || md_moved || rs) अणु
		u32 prev_flags;

		/* We करो some synchronous IO below, which may take some समय.
		 * Clear the समयr, to aव्योम scary "timer expired!" messages,
		 * "Superblock" is written out at least twice below, anyways. */
		del_समयr(&device->md_sync_समयr);

		/* We won't change the "al-extents" setting, we just may need
		 * to move the on-disk location of the activity log ringbuffer.
		 * Lock क्रम transaction is good enough, it may well be "dirty"
		 * or even "starving". */
		रुको_event(device->al_रुको, lc_try_lock_क्रम_transaction(device->act_log));

		/* mark current on-disk biपंचांगap and activity log as unreliable */
		prev_flags = md->flags;
		md->flags |= MDF_FULL_SYNC | MDF_AL_DISABLED;
		drbd_md_ग_लिखो(device, buffer);

		drbd_al_initialize(device, buffer);

		drbd_info(device, "Writing the whole bitmap, %s\n",
			 la_size_changed && md_moved ? "size changed and md moved" :
			 la_size_changed ? "size changed" : "md moved");
		/* next line implicitly करोes drbd_suspend_io()+drbd_resume_io() */
		drbd_biपंचांगap_io(device, md_moved ? &drbd_bm_ग_लिखो_all : &drbd_bm_ग_लिखो,
			       "size changed", BM_LOCKED_MASK);

		/* on-disk biपंचांगap and activity log is authoritative again
		 * (unless there was an IO error meanजबतक...) */
		md->flags = prev_flags;
		drbd_md_ग_लिखो(device, buffer);

		अगर (rs)
			drbd_info(device, "Changed AL layout to al-stripes = %d, al-stripe-size-kB = %d\n",
				  md->al_stripes, md->al_stripe_size_4k * 4);
	पूर्ण

	अगर (size > prev.last_agreed_sect)
		rv = prev.last_agreed_sect ? DS_GREW : DS_GREW_FROM_ZERO;
	अगर (size < prev.last_agreed_sect)
		rv = DS_SHRUNK;

	अगर (0) अणु
	err_out:
		/* restore previous offset and sizes */
		md->la_size_sect = prev.last_agreed_sect;
		md->md_offset = prev.md_offset;
		md->al_offset = prev.al_offset;
		md->bm_offset = prev.bm_offset;
		md->md_size_sect = prev.md_size_sect;
		md->al_stripes = prev.al_stripes;
		md->al_stripe_size_4k = prev.al_stripe_size_4k;
		md->al_size_4k = (u64)prev.al_stripes * prev.al_stripe_size_4k;
	पूर्ण
	lc_unlock(device->act_log);
	wake_up(&device->al_रुको);
	drbd_md_put_buffer(device);
	drbd_resume_io(device);

	वापस rv;
पूर्ण

sector_t
drbd_new_dev_size(काष्ठा drbd_device *device, काष्ठा drbd_backing_dev *bdev,
		  sector_t u_size, पूर्णांक assume_peer_has_space)
अणु
	sector_t p_size = device->p_size;   /* partner's disk size. */
	sector_t la_size_sect = bdev->md.la_size_sect; /* last agreed size. */
	sector_t m_size; /* my size */
	sector_t size = 0;

	m_size = drbd_get_max_capacity(bdev);

	अगर (device->state.conn < C_CONNECTED && assume_peer_has_space) अणु
		drbd_warn(device, "Resize while not connected was forced by the user!\n");
		p_size = m_size;
	पूर्ण

	अगर (p_size && m_size) अणु
		size = min_t(sector_t, p_size, m_size);
	पूर्ण अन्यथा अणु
		अगर (la_size_sect) अणु
			size = la_size_sect;
			अगर (m_size && m_size < size)
				size = m_size;
			अगर (p_size && p_size < size)
				size = p_size;
		पूर्ण अन्यथा अणु
			अगर (m_size)
				size = m_size;
			अगर (p_size)
				size = p_size;
		पूर्ण
	पूर्ण

	अगर (size == 0)
		drbd_err(device, "Both nodes diskless!\n");

	अगर (u_size) अणु
		अगर (u_size > size)
			drbd_err(device, "Requested disk size is too big (%lu > %lu)\n",
			    (अचिन्हित दीर्घ)u_size>>1, (अचिन्हित दीर्घ)size>>1);
		अन्यथा
			size = u_size;
	पूर्ण

	वापस size;
पूर्ण

/*
 * drbd_check_al_size() - Ensures that the AL is of the right size
 * @device:	DRBD device.
 *
 * Returns -EBUSY अगर current al lru is still used, -ENOMEM when allocation
 * failed, and 0 on success. You should call drbd_md_sync() after you called
 * this function.
 */
अटल पूर्णांक drbd_check_al_size(काष्ठा drbd_device *device, काष्ठा disk_conf *dc)
अणु
	काष्ठा lru_cache *n, *t;
	काष्ठा lc_element *e;
	अचिन्हित पूर्णांक in_use;
	पूर्णांक i;

	अगर (device->act_log &&
	    device->act_log->nr_elements == dc->al_extents)
		वापस 0;

	in_use = 0;
	t = device->act_log;
	n = lc_create("act_log", drbd_al_ext_cache, AL_UPDATES_PER_TRANSACTION,
		dc->al_extents, माप(काष्ठा lc_element), 0);

	अगर (n == शून्य) अणु
		drbd_err(device, "Cannot allocate act_log lru!\n");
		वापस -ENOMEM;
	पूर्ण
	spin_lock_irq(&device->al_lock);
	अगर (t) अणु
		क्रम (i = 0; i < t->nr_elements; i++) अणु
			e = lc_element_by_index(t, i);
			अगर (e->refcnt)
				drbd_err(device, "refcnt(%d)==%d\n",
				    e->lc_number, e->refcnt);
			in_use += e->refcnt;
		पूर्ण
	पूर्ण
	अगर (!in_use)
		device->act_log = n;
	spin_unlock_irq(&device->al_lock);
	अगर (in_use) अणु
		drbd_err(device, "Activity log still in use!\n");
		lc_destroy(n);
		वापस -EBUSY;
	पूर्ण अन्यथा अणु
		lc_destroy(t);
	पूर्ण
	drbd_md_mark_dirty(device); /* we changed device->act_log->nr_elemens */
	वापस 0;
पूर्ण

अटल व्योम blk_queue_discard_granularity(काष्ठा request_queue *q, अचिन्हित पूर्णांक granularity)
अणु
	q->limits.discard_granularity = granularity;
पूर्ण

अटल अचिन्हित पूर्णांक drbd_max_discard_sectors(काष्ठा drbd_connection *connection)
अणु
	/* when we पूर्णांकroduced REQ_WRITE_SAME support, we also bumped
	 * our maximum supported batch bio size used क्रम discards. */
	अगर (connection->agreed_features & DRBD_FF_WSAME)
		वापस DRBD_MAX_BBIO_SECTORS;
	/* beक्रमe, with DRBD <= 8.4.6, we only allowed up to one AL_EXTENT_SIZE. */
	वापस AL_EXTENT_SIZE >> 9;
पूर्ण

अटल व्योम decide_on_discard_support(काष्ठा drbd_device *device,
			काष्ठा request_queue *q,
			काष्ठा request_queue *b,
			bool discard_zeroes_अगर_aligned)
अणु
	/* q = drbd device queue (device->rq_queue)
	 * b = backing device queue (device->ldev->backing_bdev->bd_disk->queue),
	 *     or शून्य अगर diskless
	 */
	काष्ठा drbd_connection *connection = first_peer_device(device)->connection;
	bool can_करो = b ? blk_queue_discard(b) : true;

	अगर (can_करो && connection->cstate >= C_CONNECTED && !(connection->agreed_features & DRBD_FF_TRIM)) अणु
		can_करो = false;
		drbd_info(connection, "peer DRBD too old, does not support TRIM: disabling discards\n");
	पूर्ण
	अगर (can_करो) अणु
		/* We करोn't care क्रम the granularity, really.
		 * Stacking limits below should fix it क्रम the local
		 * device.  Whether or not it is a suitable granularity
		 * on the remote device is not our problem, really. If
		 * you care, you need to use devices with similar
		 * topology on all peers. */
		blk_queue_discard_granularity(q, 512);
		q->limits.max_discard_sectors = drbd_max_discard_sectors(connection);
		blk_queue_flag_set(QUEUE_FLAG_DISCARD, q);
		q->limits.max_ग_लिखो_zeroes_sectors = drbd_max_discard_sectors(connection);
	पूर्ण अन्यथा अणु
		blk_queue_flag_clear(QUEUE_FLAG_DISCARD, q);
		blk_queue_discard_granularity(q, 0);
		q->limits.max_discard_sectors = 0;
		q->limits.max_ग_लिखो_zeroes_sectors = 0;
	पूर्ण
पूर्ण

अटल व्योम fixup_discard_अगर_not_supported(काष्ठा request_queue *q)
अणु
	/* To aव्योम confusion, अगर this queue करोes not support discard, clear
	 * max_discard_sectors, which is what lsblk -D reports to the user.
	 * Older kernels got this wrong in "stack limits".
	 * */
	अगर (!blk_queue_discard(q)) अणु
		blk_queue_max_discard_sectors(q, 0);
		blk_queue_discard_granularity(q, 0);
	पूर्ण
पूर्ण

अटल व्योम fixup_ग_लिखो_zeroes(काष्ठा drbd_device *device, काष्ठा request_queue *q)
अणु
	/* Fixup max_ग_लिखो_zeroes_sectors after blk_stack_limits():
	 * अगर we can handle "zeroes" efficiently on the protocol,
	 * we want to करो that, even अगर our backend करोes not announce
	 * max_ग_लिखो_zeroes_sectors itself. */
	काष्ठा drbd_connection *connection = first_peer_device(device)->connection;
	/* If the peer announces WZEROES support, use it.  Otherwise, rather
	 * send explicit zeroes than rely on some discard-zeroes-data magic. */
	अगर (connection->agreed_features & DRBD_FF_WZEROES)
		q->limits.max_ग_लिखो_zeroes_sectors = DRBD_MAX_BBIO_SECTORS;
	अन्यथा
		q->limits.max_ग_लिखो_zeroes_sectors = 0;
पूर्ण

अटल व्योम decide_on_ग_लिखो_same_support(काष्ठा drbd_device *device,
			काष्ठा request_queue *q,
			काष्ठा request_queue *b, काष्ठा o_qlim *o,
			bool disable_ग_लिखो_same)
अणु
	काष्ठा drbd_peer_device *peer_device = first_peer_device(device);
	काष्ठा drbd_connection *connection = peer_device->connection;
	bool can_करो = b ? b->limits.max_ग_लिखो_same_sectors : true;

	अगर (can_करो && disable_ग_लिखो_same) अणु
		can_करो = false;
		drbd_info(peer_device, "WRITE_SAME disabled by config\n");
	पूर्ण

	अगर (can_करो && connection->cstate >= C_CONNECTED && !(connection->agreed_features & DRBD_FF_WSAME)) अणु
		can_करो = false;
		drbd_info(peer_device, "peer does not support WRITE_SAME\n");
	पूर्ण

	अगर (o) अणु
		/* logical block size; queue_logical_block_size(शून्य) is 512 */
		अचिन्हित पूर्णांक peer_lbs = be32_to_cpu(o->logical_block_size);
		अचिन्हित पूर्णांक me_lbs_b = queue_logical_block_size(b);
		अचिन्हित पूर्णांक me_lbs = queue_logical_block_size(q);

		अगर (me_lbs_b != me_lbs) अणु
			drbd_warn(device,
				"logical block size of local backend does not match (drbd:%u, backend:%u); was this a late attach?\n",
				me_lbs, me_lbs_b);
			/* rather disable ग_लिखो same than trigger some BUG_ON later in the scsi layer. */
			can_करो = false;
		पूर्ण
		अगर (me_lbs_b != peer_lbs) अणु
			drbd_warn(peer_device, "logical block sizes do not match (me:%u, peer:%u); this may cause problems.\n",
				me_lbs, peer_lbs);
			अगर (can_करो) अणु
				drbd_dbg(peer_device, "logical block size mismatch: WRITE_SAME disabled.\n");
				can_करो = false;
			पूर्ण
			me_lbs = max(me_lbs, me_lbs_b);
			/* We cannot change the logical block size of an in-use queue.
			 * We can only hope that access happens to be properly aligned.
			 * If not, the peer will likely produce an IO error, and detach. */
			अगर (peer_lbs > me_lbs) अणु
				अगर (device->state.role != R_PRIMARY) अणु
					blk_queue_logical_block_size(q, peer_lbs);
					drbd_warn(peer_device, "logical block size set to %u\n", peer_lbs);
				पूर्ण अन्यथा अणु
					drbd_warn(peer_device,
						"current Primary must NOT adjust logical block size (%u -> %u); hope for the best.\n",
						me_lbs, peer_lbs);
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (can_करो && !o->ग_लिखो_same_capable) अणु
			/* If we पूर्णांकroduce an खोलो-coded ग_लिखो-same loop on the receiving side,
			 * the peer would present itself as "capable". */
			drbd_dbg(peer_device, "WRITE_SAME disabled (peer device not capable)\n");
			can_करो = false;
		पूर्ण
	पूर्ण

	blk_queue_max_ग_लिखो_same_sectors(q, can_करो ? DRBD_MAX_BBIO_SECTORS : 0);
पूर्ण

अटल व्योम drbd_setup_queue_param(काष्ठा drbd_device *device, काष्ठा drbd_backing_dev *bdev,
				   अचिन्हित पूर्णांक max_bio_size, काष्ठा o_qlim *o)
अणु
	काष्ठा request_queue * स्थिर q = device->rq_queue;
	अचिन्हित पूर्णांक max_hw_sectors = max_bio_size >> 9;
	अचिन्हित पूर्णांक max_segments = 0;
	काष्ठा request_queue *b = शून्य;
	काष्ठा disk_conf *dc;
	bool discard_zeroes_अगर_aligned = true;
	bool disable_ग_लिखो_same = false;

	अगर (bdev) अणु
		b = bdev->backing_bdev->bd_disk->queue;

		max_hw_sectors = min(queue_max_hw_sectors(b), max_bio_size >> 9);
		rcu_पढ़ो_lock();
		dc = rcu_dereference(device->ldev->disk_conf);
		max_segments = dc->max_bio_bvecs;
		discard_zeroes_अगर_aligned = dc->discard_zeroes_अगर_aligned;
		disable_ग_लिखो_same = dc->disable_ग_लिखो_same;
		rcu_पढ़ो_unlock();

		blk_set_stacking_limits(&q->limits);
	पूर्ण

	blk_queue_max_hw_sectors(q, max_hw_sectors);
	/* This is the workaround क्रम "bio would need to, but cannot, be split" */
	blk_queue_max_segments(q, max_segments ? max_segments : BLK_MAX_SEGMENTS);
	blk_queue_segment_boundary(q, PAGE_SIZE-1);
	decide_on_discard_support(device, q, b, discard_zeroes_अगर_aligned);
	decide_on_ग_लिखो_same_support(device, q, b, o, disable_ग_लिखो_same);

	अगर (b) अणु
		blk_stack_limits(&q->limits, &b->limits, 0);
		blk_queue_update_पढ़ोahead(q);
	पूर्ण
	fixup_discard_अगर_not_supported(q);
	fixup_ग_लिखो_zeroes(device, q);
पूर्ण

व्योम drbd_reconsider_queue_parameters(काष्ठा drbd_device *device, काष्ठा drbd_backing_dev *bdev, काष्ठा o_qlim *o)
अणु
	अचिन्हित पूर्णांक now, new, local, peer;

	now = queue_max_hw_sectors(device->rq_queue) << 9;
	local = device->local_max_bio_size; /* Eventually last known value, from अस्थिर memory */
	peer = device->peer_max_bio_size; /* Eventually last known value, from meta data */

	अगर (bdev) अणु
		local = queue_max_hw_sectors(bdev->backing_bdev->bd_disk->queue) << 9;
		device->local_max_bio_size = local;
	पूर्ण
	local = min(local, DRBD_MAX_BIO_SIZE);

	/* We may ignore peer limits अगर the peer is modern enough.
	   Because new from 8.3.8 onwards the peer can use multiple
	   BIOs क्रम a single peer_request */
	अगर (device->state.conn >= C_WF_REPORT_PARAMS) अणु
		अगर (first_peer_device(device)->connection->agreed_pro_version < 94)
			peer = min(device->peer_max_bio_size, DRBD_MAX_SIZE_H80_PACKET);
			/* Correct old drbd (up to 8.3.7) अगर it believes it can करो more than 32KiB */
		अन्यथा अगर (first_peer_device(device)->connection->agreed_pro_version == 94)
			peer = DRBD_MAX_SIZE_H80_PACKET;
		अन्यथा अगर (first_peer_device(device)->connection->agreed_pro_version < 100)
			peer = DRBD_MAX_BIO_SIZE_P95;  /* drbd 8.3.8 onwards, beक्रमe 8.4.0 */
		अन्यथा
			peer = DRBD_MAX_BIO_SIZE;

		/* We may later detach and re-attach on a disconnected Primary.
		 * Aव्योम this setting to jump back in that हाल.
		 * We want to store what we know the peer DRBD can handle,
		 * not what the peer IO backend can handle. */
		अगर (peer > device->peer_max_bio_size)
			device->peer_max_bio_size = peer;
	पूर्ण
	new = min(local, peer);

	अगर (device->state.role == R_PRIMARY && new < now)
		drbd_err(device, "ASSERT FAILED new < now; (%u < %u)\n", new, now);

	अगर (new != now)
		drbd_info(device, "max BIO size = %u\n", new);

	drbd_setup_queue_param(device, bdev, new, o);
पूर्ण

/* Starts the worker thपढ़ो */
अटल व्योम conn_reconfig_start(काष्ठा drbd_connection *connection)
अणु
	drbd_thपढ़ो_start(&connection->worker);
	drbd_flush_workqueue(&connection->sender_work);
पूर्ण

/* अगर still unconfigured, stops worker again. */
अटल व्योम conn_reconfig_करोne(काष्ठा drbd_connection *connection)
अणु
	bool stop_thपढ़ोs;
	spin_lock_irq(&connection->resource->req_lock);
	stop_thपढ़ोs = conn_all_vols_unconf(connection) &&
		connection->cstate == C_STANDALONE;
	spin_unlock_irq(&connection->resource->req_lock);
	अगर (stop_thपढ़ोs) अणु
		/* ack_receiver thपढ़ो and ack_sender workqueue are implicitly
		 * stopped by receiver in conn_disconnect() */
		drbd_thपढ़ो_stop(&connection->receiver);
		drbd_thपढ़ो_stop(&connection->worker);
	पूर्ण
पूर्ण

/* Make sure IO is suspended beक्रमe calling this function(). */
अटल व्योम drbd_suspend_al(काष्ठा drbd_device *device)
अणु
	पूर्णांक s = 0;

	अगर (!lc_try_lock(device->act_log)) अणु
		drbd_warn(device, "Failed to lock al in drbd_suspend_al()\n");
		वापस;
	पूर्ण

	drbd_al_shrink(device);
	spin_lock_irq(&device->resource->req_lock);
	अगर (device->state.conn < C_CONNECTED)
		s = !test_and_set_bit(AL_SUSPENDED, &device->flags);
	spin_unlock_irq(&device->resource->req_lock);
	lc_unlock(device->act_log);

	अगर (s)
		drbd_info(device, "Suspended AL updates\n");
पूर्ण


अटल bool should_set_शेषs(काष्ठा genl_info *info)
अणु
	अचिन्हित flags = ((काष्ठा drbd_genlmsghdr*)info->userhdr)->flags;
	वापस 0 != (flags & DRBD_GENL_F_SET_DEFAULTS);
पूर्ण

अटल अचिन्हित पूर्णांक drbd_al_extents_max(काष्ठा drbd_backing_dev *bdev)
अणु
	/* This is limited by 16 bit "slot" numbers,
	 * and by available on-disk context storage.
	 *
	 * Also (u16)~0 is special (denotes a "free" extent).
	 *
	 * One transaction occupies one 4kB on-disk block,
	 * we have n such blocks in the on disk ring buffer,
	 * the "current" transaction may fail (n-1),
	 * and there is 919 slot numbers context inक्रमmation per transaction.
	 *
	 * 72 transaction blocks amounts to more than 2**16 context slots,
	 * so cap there first.
	 */
	स्थिर अचिन्हित पूर्णांक max_al_nr = DRBD_AL_EXTENTS_MAX;
	स्थिर अचिन्हित पूर्णांक sufficient_on_disk =
		(max_al_nr + AL_CONTEXT_PER_TRANSACTION -1)
		/AL_CONTEXT_PER_TRANSACTION;

	अचिन्हित पूर्णांक al_size_4k = bdev->md.al_size_4k;

	अगर (al_size_4k > sufficient_on_disk)
		वापस max_al_nr;

	वापस (al_size_4k - 1) * AL_CONTEXT_PER_TRANSACTION;
पूर्ण

अटल bool ग_लिखो_ordering_changed(काष्ठा disk_conf *a, काष्ठा disk_conf *b)
अणु
	वापस	a->disk_barrier != b->disk_barrier ||
		a->disk_flushes != b->disk_flushes ||
		a->disk_drain != b->disk_drain;
पूर्ण

अटल व्योम sanitize_disk_conf(काष्ठा drbd_device *device, काष्ठा disk_conf *disk_conf,
			       काष्ठा drbd_backing_dev *nbc)
अणु
	काष्ठा request_queue * स्थिर q = nbc->backing_bdev->bd_disk->queue;

	अगर (disk_conf->al_extents < DRBD_AL_EXTENTS_MIN)
		disk_conf->al_extents = DRBD_AL_EXTENTS_MIN;
	अगर (disk_conf->al_extents > drbd_al_extents_max(nbc))
		disk_conf->al_extents = drbd_al_extents_max(nbc);

	अगर (!blk_queue_discard(q)) अणु
		अगर (disk_conf->rs_discard_granularity) अणु
			disk_conf->rs_discard_granularity = 0; /* disable feature */
			drbd_info(device, "rs_discard_granularity feature disabled\n");
		पूर्ण
	पूर्ण

	अगर (disk_conf->rs_discard_granularity) अणु
		पूर्णांक orig_value = disk_conf->rs_discard_granularity;
		पूर्णांक reमुख्यder;

		अगर (q->limits.discard_granularity > disk_conf->rs_discard_granularity)
			disk_conf->rs_discard_granularity = q->limits.discard_granularity;

		reमुख्यder = disk_conf->rs_discard_granularity % q->limits.discard_granularity;
		disk_conf->rs_discard_granularity += reमुख्यder;

		अगर (disk_conf->rs_discard_granularity > q->limits.max_discard_sectors << 9)
			disk_conf->rs_discard_granularity = q->limits.max_discard_sectors << 9;

		अगर (disk_conf->rs_discard_granularity != orig_value)
			drbd_info(device, "rs_discard_granularity changed to %d\n",
				  disk_conf->rs_discard_granularity);
	पूर्ण
पूर्ण

अटल पूर्णांक disk_opts_check_al_size(काष्ठा drbd_device *device, काष्ठा disk_conf *dc)
अणु
	पूर्णांक err = -EBUSY;

	अगर (device->act_log &&
	    device->act_log->nr_elements == dc->al_extents)
		वापस 0;

	drbd_suspend_io(device);
	/* If IO completion is currently blocked, we would likely रुको
	 * "forever" क्रम the activity log to become unused. So we करोn't. */
	अगर (atomic_पढ़ो(&device->ap_bio_cnt))
		जाओ out;

	रुको_event(device->al_रुको, lc_try_lock(device->act_log));
	drbd_al_shrink(device);
	err = drbd_check_al_size(device, dc);
	lc_unlock(device->act_log);
	wake_up(&device->al_रुको);
out:
	drbd_resume_io(device);
	वापस err;
पूर्ण

पूर्णांक drbd_adm_disk_opts(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा drbd_config_context adm_ctx;
	क्रमागत drbd_ret_code retcode;
	काष्ठा drbd_device *device;
	काष्ठा disk_conf *new_disk_conf, *old_disk_conf;
	काष्ठा fअगरo_buffer *old_plan = शून्य, *new_plan = शून्य;
	पूर्णांक err;
	अचिन्हित पूर्णांक fअगरo_size;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_MINOR);
	अगर (!adm_ctx.reply_skb)
		वापस retcode;
	अगर (retcode != NO_ERROR)
		जाओ finish;

	device = adm_ctx.device;
	mutex_lock(&adm_ctx.resource->adm_mutex);

	/* we also need a disk
	 * to change the options on */
	अगर (!get_ldev(device)) अणु
		retcode = ERR_NO_DISK;
		जाओ out;
	पूर्ण

	new_disk_conf = kदो_स्मृति(माप(काष्ठा disk_conf), GFP_KERNEL);
	अगर (!new_disk_conf) अणु
		retcode = ERR_NOMEM;
		जाओ fail;
	पूर्ण

	mutex_lock(&device->resource->conf_update);
	old_disk_conf = device->ldev->disk_conf;
	*new_disk_conf = *old_disk_conf;
	अगर (should_set_शेषs(info))
		set_disk_conf_शेषs(new_disk_conf);

	err = disk_conf_from_attrs_क्रम_change(new_disk_conf, info);
	अगर (err && err != -ENOMSG) अणु
		retcode = ERR_MANDATORY_TAG;
		drbd_msg_put_info(adm_ctx.reply_skb, from_attrs_err_to_txt(err));
		जाओ fail_unlock;
	पूर्ण

	अगर (!expect(new_disk_conf->resync_rate >= 1))
		new_disk_conf->resync_rate = 1;

	sanitize_disk_conf(device, new_disk_conf, device->ldev);

	अगर (new_disk_conf->c_plan_ahead > DRBD_C_PLAN_AHEAD_MAX)
		new_disk_conf->c_plan_ahead = DRBD_C_PLAN_AHEAD_MAX;

	fअगरo_size = (new_disk_conf->c_plan_ahead * 10 * SLEEP_TIME) / HZ;
	अगर (fअगरo_size != device->rs_plan_s->size) अणु
		new_plan = fअगरo_alloc(fअगरo_size);
		अगर (!new_plan) अणु
			drbd_err(device, "kmalloc of fifo_buffer failed");
			retcode = ERR_NOMEM;
			जाओ fail_unlock;
		पूर्ण
	पूर्ण

	err = disk_opts_check_al_size(device, new_disk_conf);
	अगर (err) अणु
		/* Could be just "busy". Ignore?
		 * Introduce dedicated error code? */
		drbd_msg_put_info(adm_ctx.reply_skb,
			"Try again without changing current al-extents setting");
		retcode = ERR_NOMEM;
		जाओ fail_unlock;
	पूर्ण

	lock_all_resources();
	retcode = drbd_resync_after_valid(device, new_disk_conf->resync_after);
	अगर (retcode == NO_ERROR) अणु
		rcu_assign_poपूर्णांकer(device->ldev->disk_conf, new_disk_conf);
		drbd_resync_after_changed(device);
	पूर्ण
	unlock_all_resources();

	अगर (retcode != NO_ERROR)
		जाओ fail_unlock;

	अगर (new_plan) अणु
		old_plan = device->rs_plan_s;
		rcu_assign_poपूर्णांकer(device->rs_plan_s, new_plan);
	पूर्ण

	mutex_unlock(&device->resource->conf_update);

	अगर (new_disk_conf->al_updates)
		device->ldev->md.flags &= ~MDF_AL_DISABLED;
	अन्यथा
		device->ldev->md.flags |= MDF_AL_DISABLED;

	अगर (new_disk_conf->md_flushes)
		clear_bit(MD_NO_FUA, &device->flags);
	अन्यथा
		set_bit(MD_NO_FUA, &device->flags);

	अगर (ग_लिखो_ordering_changed(old_disk_conf, new_disk_conf))
		drbd_bump_ग_लिखो_ordering(device->resource, शून्य, WO_BDEV_FLUSH);

	अगर (old_disk_conf->discard_zeroes_अगर_aligned != new_disk_conf->discard_zeroes_अगर_aligned
	||  old_disk_conf->disable_ग_लिखो_same != new_disk_conf->disable_ग_लिखो_same)
		drbd_reconsider_queue_parameters(device, device->ldev, शून्य);

	drbd_md_sync(device);

	अगर (device->state.conn >= C_CONNECTED) अणु
		काष्ठा drbd_peer_device *peer_device;

		क्रम_each_peer_device(peer_device, device)
			drbd_send_sync_param(peer_device);
	पूर्ण

	synchronize_rcu();
	kमुक्त(old_disk_conf);
	kमुक्त(old_plan);
	mod_समयr(&device->request_समयr, jअगरfies + HZ);
	जाओ success;

fail_unlock:
	mutex_unlock(&device->resource->conf_update);
 fail:
	kमुक्त(new_disk_conf);
	kमुक्त(new_plan);
success:
	put_ldev(device);
 out:
	mutex_unlock(&adm_ctx.resource->adm_mutex);
 finish:
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;
पूर्ण

अटल काष्ठा block_device *खोलो_backing_dev(काष्ठा drbd_device *device,
		स्थिर अक्षर *bdev_path, व्योम *claim_ptr, bool करो_bd_link)
अणु
	काष्ठा block_device *bdev;
	पूर्णांक err = 0;

	bdev = blkdev_get_by_path(bdev_path,
				  FMODE_READ | FMODE_WRITE | FMODE_EXCL, claim_ptr);
	अगर (IS_ERR(bdev)) अणु
		drbd_err(device, "open(\"%s\") failed with %ld\n",
				bdev_path, PTR_ERR(bdev));
		वापस bdev;
	पूर्ण

	अगर (!करो_bd_link)
		वापस bdev;

	err = bd_link_disk_holder(bdev, device->vdisk);
	अगर (err) अणु
		blkdev_put(bdev, FMODE_READ | FMODE_WRITE | FMODE_EXCL);
		drbd_err(device, "bd_link_disk_holder(\"%s\", ...) failed with %d\n",
				bdev_path, err);
		bdev = ERR_PTR(err);
	पूर्ण
	वापस bdev;
पूर्ण

अटल पूर्णांक खोलो_backing_devices(काष्ठा drbd_device *device,
		काष्ठा disk_conf *new_disk_conf,
		काष्ठा drbd_backing_dev *nbc)
अणु
	काष्ठा block_device *bdev;

	bdev = खोलो_backing_dev(device, new_disk_conf->backing_dev, device, true);
	अगर (IS_ERR(bdev))
		वापस ERR_OPEN_DISK;
	nbc->backing_bdev = bdev;

	/*
	 * meta_dev_idx >= 0: बाह्यal fixed size, possibly multiple
	 * drbd sharing one meta device.  TODO in that हाल, paranoia
	 * check that [md_bdev, meta_dev_idx] is not yet used by some
	 * other drbd minor!  (अगर you use drbd.conf + drbdadm, that
	 * should check it क्रम you alपढ़ोy; but अगर you करोn't, or
	 * someone fooled it, we need to द्विगुन check here)
	 */
	bdev = खोलो_backing_dev(device, new_disk_conf->meta_dev,
		/* claim ptr: device, अगर claimed exclusively; shared drbd_m_holder,
		 * अगर potentially shared with other drbd minors */
			(new_disk_conf->meta_dev_idx < 0) ? (व्योम*)device : (व्योम*)drbd_m_holder,
		/* aव्योम द्विगुन bd_claim_by_disk() क्रम the same (source,target) tuple,
		 * as would happen with पूर्णांकernal metadata. */
			(new_disk_conf->meta_dev_idx != DRBD_MD_INDEX_FLEX_INT &&
			 new_disk_conf->meta_dev_idx != DRBD_MD_INDEX_INTERNAL));
	अगर (IS_ERR(bdev))
		वापस ERR_OPEN_MD_DISK;
	nbc->md_bdev = bdev;
	वापस NO_ERROR;
पूर्ण

अटल व्योम बंद_backing_dev(काष्ठा drbd_device *device, काष्ठा block_device *bdev,
	bool करो_bd_unlink)
अणु
	अगर (!bdev)
		वापस;
	अगर (करो_bd_unlink)
		bd_unlink_disk_holder(bdev, device->vdisk);
	blkdev_put(bdev, FMODE_READ | FMODE_WRITE | FMODE_EXCL);
पूर्ण

व्योम drbd_backing_dev_मुक्त(काष्ठा drbd_device *device, काष्ठा drbd_backing_dev *ldev)
अणु
	अगर (ldev == शून्य)
		वापस;

	बंद_backing_dev(device, ldev->md_bdev, ldev->md_bdev != ldev->backing_bdev);
	बंद_backing_dev(device, ldev->backing_bdev, true);

	kमुक्त(ldev->disk_conf);
	kमुक्त(ldev);
पूर्ण

पूर्णांक drbd_adm_attach(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा drbd_config_context adm_ctx;
	काष्ठा drbd_device *device;
	काष्ठा drbd_peer_device *peer_device;
	काष्ठा drbd_connection *connection;
	पूर्णांक err;
	क्रमागत drbd_ret_code retcode;
	क्रमागत determine_dev_size dd;
	sector_t max_possible_sectors;
	sector_t min_md_device_sectors;
	काष्ठा drbd_backing_dev *nbc = शून्य; /* new_backing_conf */
	काष्ठा disk_conf *new_disk_conf = शून्य;
	काष्ठा lru_cache *resync_lru = शून्य;
	काष्ठा fअगरo_buffer *new_plan = शून्य;
	जोड़ drbd_state ns, os;
	क्रमागत drbd_state_rv rv;
	काष्ठा net_conf *nc;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_MINOR);
	अगर (!adm_ctx.reply_skb)
		वापस retcode;
	अगर (retcode != NO_ERROR)
		जाओ finish;

	device = adm_ctx.device;
	mutex_lock(&adm_ctx.resource->adm_mutex);
	peer_device = first_peer_device(device);
	connection = peer_device->connection;
	conn_reconfig_start(connection);

	/* अगर you want to reconfigure, please tear करोwn first */
	अगर (device->state.disk > D_DISKLESS) अणु
		retcode = ERR_DISK_CONFIGURED;
		जाओ fail;
	पूर्ण
	/* It may just now have detached because of IO error.  Make sure
	 * drbd_ldev_destroy is करोne alपढ़ोy, we may end up here very fast,
	 * e.g. अगर someone calls attach from the on-io-error handler,
	 * to realize a "hot spare" feature (not that I'd recommend that) */
	रुको_event(device->misc_रुको, !test_bit(GOING_DISKLESS, &device->flags));

	/* make sure there is no leftover from previous क्रमce-detach attempts */
	clear_bit(FORCE_DETACH, &device->flags);
	clear_bit(WAS_IO_ERROR, &device->flags);
	clear_bit(WAS_READ_ERROR, &device->flags);

	/* and no leftover from previously पातed resync or verअगरy, either */
	device->rs_total = 0;
	device->rs_failed = 0;
	atomic_set(&device->rs_pending_cnt, 0);

	/* allocation not in the IO path, drbdsetup context */
	nbc = kzalloc(माप(काष्ठा drbd_backing_dev), GFP_KERNEL);
	अगर (!nbc) अणु
		retcode = ERR_NOMEM;
		जाओ fail;
	पूर्ण
	spin_lock_init(&nbc->md.uuid_lock);

	new_disk_conf = kzalloc(माप(काष्ठा disk_conf), GFP_KERNEL);
	अगर (!new_disk_conf) अणु
		retcode = ERR_NOMEM;
		जाओ fail;
	पूर्ण
	nbc->disk_conf = new_disk_conf;

	set_disk_conf_शेषs(new_disk_conf);
	err = disk_conf_from_attrs(new_disk_conf, info);
	अगर (err) अणु
		retcode = ERR_MANDATORY_TAG;
		drbd_msg_put_info(adm_ctx.reply_skb, from_attrs_err_to_txt(err));
		जाओ fail;
	पूर्ण

	अगर (new_disk_conf->c_plan_ahead > DRBD_C_PLAN_AHEAD_MAX)
		new_disk_conf->c_plan_ahead = DRBD_C_PLAN_AHEAD_MAX;

	new_plan = fअगरo_alloc((new_disk_conf->c_plan_ahead * 10 * SLEEP_TIME) / HZ);
	अगर (!new_plan) अणु
		retcode = ERR_NOMEM;
		जाओ fail;
	पूर्ण

	अगर (new_disk_conf->meta_dev_idx < DRBD_MD_INDEX_FLEX_INT) अणु
		retcode = ERR_MD_IDX_INVALID;
		जाओ fail;
	पूर्ण

	rcu_पढ़ो_lock();
	nc = rcu_dereference(connection->net_conf);
	अगर (nc) अणु
		अगर (new_disk_conf->fencing == FP_STONITH && nc->wire_protocol == DRBD_PROT_A) अणु
			rcu_पढ़ो_unlock();
			retcode = ERR_STONITH_AND_PROT_A;
			जाओ fail;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	retcode = खोलो_backing_devices(device, new_disk_conf, nbc);
	अगर (retcode != NO_ERROR)
		जाओ fail;

	अगर ((nbc->backing_bdev == nbc->md_bdev) !=
	    (new_disk_conf->meta_dev_idx == DRBD_MD_INDEX_INTERNAL ||
	     new_disk_conf->meta_dev_idx == DRBD_MD_INDEX_FLEX_INT)) अणु
		retcode = ERR_MD_IDX_INVALID;
		जाओ fail;
	पूर्ण

	resync_lru = lc_create("resync", drbd_bm_ext_cache,
			1, 61, माप(काष्ठा bm_extent),
			दुरत्व(काष्ठा bm_extent, lce));
	अगर (!resync_lru) अणु
		retcode = ERR_NOMEM;
		जाओ fail;
	पूर्ण

	/* Read our meta data super block early.
	 * This also sets other on-disk offsets. */
	retcode = drbd_md_पढ़ो(device, nbc);
	अगर (retcode != NO_ERROR)
		जाओ fail;

	sanitize_disk_conf(device, new_disk_conf, nbc);

	अगर (drbd_get_max_capacity(nbc) < new_disk_conf->disk_size) अणु
		drbd_err(device, "max capacity %llu smaller than disk size %llu\n",
			(अचिन्हित दीर्घ दीर्घ) drbd_get_max_capacity(nbc),
			(अचिन्हित दीर्घ दीर्घ) new_disk_conf->disk_size);
		retcode = ERR_DISK_TOO_SMALL;
		जाओ fail;
	पूर्ण

	अगर (new_disk_conf->meta_dev_idx < 0) अणु
		max_possible_sectors = DRBD_MAX_SECTORS_FLEX;
		/* at least one MB, otherwise it करोes not make sense */
		min_md_device_sectors = (2<<10);
	पूर्ण अन्यथा अणु
		max_possible_sectors = DRBD_MAX_SECTORS;
		min_md_device_sectors = MD_128MB_SECT * (new_disk_conf->meta_dev_idx + 1);
	पूर्ण

	अगर (drbd_get_capacity(nbc->md_bdev) < min_md_device_sectors) अणु
		retcode = ERR_MD_DISK_TOO_SMALL;
		drbd_warn(device, "refusing attach: md-device too small, "
		     "at least %llu sectors needed for this meta-disk type\n",
		     (अचिन्हित दीर्घ दीर्घ) min_md_device_sectors);
		जाओ fail;
	पूर्ण

	/* Make sure the new disk is big enough
	 * (we may currently be R_PRIMARY with no local disk...) */
	अगर (drbd_get_max_capacity(nbc) < get_capacity(device->vdisk)) अणु
		retcode = ERR_DISK_TOO_SMALL;
		जाओ fail;
	पूर्ण

	nbc->known_size = drbd_get_capacity(nbc->backing_bdev);

	अगर (nbc->known_size > max_possible_sectors) अणु
		drbd_warn(device, "==> truncating very big lower level device "
			"to currently maximum possible %llu sectors <==\n",
			(अचिन्हित दीर्घ दीर्घ) max_possible_sectors);
		अगर (new_disk_conf->meta_dev_idx >= 0)
			drbd_warn(device, "==>> using internal or flexible "
				      "meta data may help <<==\n");
	पूर्ण

	drbd_suspend_io(device);
	/* also रुको क्रम the last barrier ack. */
	/* FIXME see also https://daiquiri.linbit/cgi-bin/bugzilla/show_bug.cgi?id=171
	 * We need a way to either ignore barrier acks क्रम barriers sent beक्रमe a device
	 * was attached, or a way to रुको क्रम all pending barrier acks to come in.
	 * As barriers are counted per resource,
	 * we'd need to suspend io on all devices of a resource.
	 */
	रुको_event(device->misc_रुको, !atomic_पढ़ो(&device->ap_pending_cnt) || drbd_suspended(device));
	/* and क्रम any other previously queued work */
	drbd_flush_workqueue(&connection->sender_work);

	rv = _drbd_request_state(device, NS(disk, D_ATTACHING), CS_VERBOSE);
	retcode = (क्रमागत drbd_ret_code)rv;
	drbd_resume_io(device);
	अगर (rv < SS_SUCCESS)
		जाओ fail;

	अगर (!get_ldev_अगर_state(device, D_ATTACHING))
		जाओ क्रमce_diskless;

	अगर (!device->biपंचांगap) अणु
		अगर (drbd_bm_init(device)) अणु
			retcode = ERR_NOMEM;
			जाओ क्रमce_diskless_dec;
		पूर्ण
	पूर्ण

	अगर (device->state.pdsk != D_UP_TO_DATE && device->ed_uuid &&
	    (device->state.role == R_PRIMARY || device->state.peer == R_PRIMARY) &&
            (device->ed_uuid & ~((u64)1)) != (nbc->md.uuid[UI_CURRENT] & ~((u64)1))) अणु
		drbd_err(device, "Can only attach to data with current UUID=%016llX\n",
		    (अचिन्हित दीर्घ दीर्घ)device->ed_uuid);
		retcode = ERR_DATA_NOT_CURRENT;
		जाओ क्रमce_diskless_dec;
	पूर्ण

	/* Since we are diskless, fix the activity log first... */
	अगर (drbd_check_al_size(device, new_disk_conf)) अणु
		retcode = ERR_NOMEM;
		जाओ क्रमce_diskless_dec;
	पूर्ण

	/* Prevent shrinking of consistent devices ! */
	अणु
	अचिन्हित दीर्घ दीर्घ nsz = drbd_new_dev_size(device, nbc, nbc->disk_conf->disk_size, 0);
	अचिन्हित दीर्घ दीर्घ eff = nbc->md.la_size_sect;
	अगर (drbd_md_test_flag(nbc, MDF_CONSISTENT) && nsz < eff) अणु
		अगर (nsz == nbc->disk_conf->disk_size) अणु
			drbd_warn(device, "truncating a consistent device during attach (%llu < %llu)\n", nsz, eff);
		पूर्ण अन्यथा अणु
			drbd_warn(device, "refusing to truncate a consistent device (%llu < %llu)\n", nsz, eff);
			drbd_msg_प्र_लिखो_info(adm_ctx.reply_skb,
				"To-be-attached device has last effective > current size, and is consistent\n"
				"(%llu > %llu sectors). Refusing to attach.", eff, nsz);
			retcode = ERR_IMPLICIT_SHRINK;
			जाओ क्रमce_diskless_dec;
		पूर्ण
	पूर्ण
	पूर्ण

	lock_all_resources();
	retcode = drbd_resync_after_valid(device, new_disk_conf->resync_after);
	अगर (retcode != NO_ERROR) अणु
		unlock_all_resources();
		जाओ क्रमce_diskless_dec;
	पूर्ण

	/* Reset the "barriers don't work" bits here, then क्रमce meta data to
	 * be written, to ensure we determine अगर barriers are supported. */
	अगर (new_disk_conf->md_flushes)
		clear_bit(MD_NO_FUA, &device->flags);
	अन्यथा
		set_bit(MD_NO_FUA, &device->flags);

	/* Poपूर्णांक of no वापस reached.
	 * Devices and memory are no दीर्घer released by error cleanup below.
	 * now device takes over responsibility, and the state engine should
	 * clean it up somewhere.  */
	D_ASSERT(device, device->ldev == शून्य);
	device->ldev = nbc;
	device->resync = resync_lru;
	device->rs_plan_s = new_plan;
	nbc = शून्य;
	resync_lru = शून्य;
	new_disk_conf = शून्य;
	new_plan = शून्य;

	drbd_resync_after_changed(device);
	drbd_bump_ग_लिखो_ordering(device->resource, device->ldev, WO_BDEV_FLUSH);
	unlock_all_resources();

	अगर (drbd_md_test_flag(device->ldev, MDF_CRASHED_PRIMARY))
		set_bit(CRASHED_PRIMARY, &device->flags);
	अन्यथा
		clear_bit(CRASHED_PRIMARY, &device->flags);

	अगर (drbd_md_test_flag(device->ldev, MDF_PRIMARY_IND) &&
	    !(device->state.role == R_PRIMARY && device->resource->susp_nod))
		set_bit(CRASHED_PRIMARY, &device->flags);

	device->send_cnt = 0;
	device->recv_cnt = 0;
	device->पढ़ो_cnt = 0;
	device->writ_cnt = 0;

	drbd_reconsider_queue_parameters(device, device->ldev, शून्य);

	/* If I am currently not R_PRIMARY,
	 * but meta data primary indicator is set,
	 * I just now recover from a hard crash,
	 * and have been R_PRIMARY beक्रमe that crash.
	 *
	 * Now, अगर I had no connection beक्रमe that crash
	 * (have been degraded R_PRIMARY), chances are that
	 * I won't find my peer now either.
	 *
	 * In that हाल, and _only_ in that हाल,
	 * we use the degr-wfc-समयout instead of the शेष,
	 * so we can स्वतःmatically recover from a crash of a
	 * degraded but active "cluster" after a certain समयout.
	 */
	clear_bit(USE_DEGR_WFC_T, &device->flags);
	अगर (device->state.role != R_PRIMARY &&
	     drbd_md_test_flag(device->ldev, MDF_PRIMARY_IND) &&
	    !drbd_md_test_flag(device->ldev, MDF_CONNECTED_IND))
		set_bit(USE_DEGR_WFC_T, &device->flags);

	dd = drbd_determine_dev_size(device, 0, शून्य);
	अगर (dd <= DS_ERROR) अणु
		retcode = ERR_NOMEM_BITMAP;
		जाओ क्रमce_diskless_dec;
	पूर्ण अन्यथा अगर (dd == DS_GREW)
		set_bit(RESYNC_AFTER_NEG, &device->flags);

	अगर (drbd_md_test_flag(device->ldev, MDF_FULL_SYNC) ||
	    (test_bit(CRASHED_PRIMARY, &device->flags) &&
	     drbd_md_test_flag(device->ldev, MDF_AL_DISABLED))) अणु
		drbd_info(device, "Assuming that all blocks are out of sync "
		     "(aka FullSync)\n");
		अगर (drbd_biपंचांगap_io(device, &drbd_bmio_set_n_ग_लिखो,
			"set_n_write from attaching", BM_LOCKED_MASK)) अणु
			retcode = ERR_IO_MD_DISK;
			जाओ क्रमce_diskless_dec;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (drbd_biपंचांगap_io(device, &drbd_bm_पढ़ो,
			"read from attaching", BM_LOCKED_MASK)) अणु
			retcode = ERR_IO_MD_DISK;
			जाओ क्रमce_diskless_dec;
		पूर्ण
	पूर्ण

	अगर (_drbd_bm_total_weight(device) == drbd_bm_bits(device))
		drbd_suspend_al(device); /* IO is still suspended here... */

	spin_lock_irq(&device->resource->req_lock);
	os = drbd_पढ़ो_state(device);
	ns = os;
	/* If MDF_CONSISTENT is not set go पूर्णांकo inconsistent state,
	   otherwise investigate MDF_WasUpToDate...
	   If MDF_WAS_UP_TO_DATE is not set go पूर्णांकo D_OUTDATED disk state,
	   otherwise पूर्णांकo D_CONSISTENT state.
	*/
	अगर (drbd_md_test_flag(device->ldev, MDF_CONSISTENT)) अणु
		अगर (drbd_md_test_flag(device->ldev, MDF_WAS_UP_TO_DATE))
			ns.disk = D_CONSISTENT;
		अन्यथा
			ns.disk = D_OUTDATED;
	पूर्ण अन्यथा अणु
		ns.disk = D_INCONSISTENT;
	पूर्ण

	अगर (drbd_md_test_flag(device->ldev, MDF_PEER_OUT_DATED))
		ns.pdsk = D_OUTDATED;

	rcu_पढ़ो_lock();
	अगर (ns.disk == D_CONSISTENT &&
	    (ns.pdsk == D_OUTDATED || rcu_dereference(device->ldev->disk_conf)->fencing == FP_DONT_CARE))
		ns.disk = D_UP_TO_DATE;

	/* All tests on MDF_PRIMARY_IND, MDF_CONNECTED_IND,
	   MDF_CONSISTENT and MDF_WAS_UP_TO_DATE must happen beक्रमe
	   this poपूर्णांक, because drbd_request_state() modअगरies these
	   flags. */

	अगर (rcu_dereference(device->ldev->disk_conf)->al_updates)
		device->ldev->md.flags &= ~MDF_AL_DISABLED;
	अन्यथा
		device->ldev->md.flags |= MDF_AL_DISABLED;

	rcu_पढ़ो_unlock();

	/* In हाल we are C_CONNECTED postpone any decision on the new disk
	   state after the negotiation phase. */
	अगर (device->state.conn == C_CONNECTED) अणु
		device->new_state_पंचांगp.i = ns.i;
		ns.i = os.i;
		ns.disk = D_NEGOTIATING;

		/* We expect to receive up-to-date UUIDs soon.
		   To aव्योम a race in receive_state, मुक्त p_uuid जबतक
		   holding req_lock. I.e. atomic with the state change */
		kमुक्त(device->p_uuid);
		device->p_uuid = शून्य;
	पूर्ण

	rv = _drbd_set_state(device, ns, CS_VERBOSE, शून्य);
	spin_unlock_irq(&device->resource->req_lock);

	अगर (rv < SS_SUCCESS)
		जाओ क्रमce_diskless_dec;

	mod_समयr(&device->request_समयr, jअगरfies + HZ);

	अगर (device->state.role == R_PRIMARY)
		device->ldev->md.uuid[UI_CURRENT] |=  (u64)1;
	अन्यथा
		device->ldev->md.uuid[UI_CURRENT] &= ~(u64)1;

	drbd_md_mark_dirty(device);
	drbd_md_sync(device);

	kobject_uevent(&disk_to_dev(device->vdisk)->kobj, KOBJ_CHANGE);
	put_ldev(device);
	conn_reconfig_करोne(connection);
	mutex_unlock(&adm_ctx.resource->adm_mutex);
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;

 क्रमce_diskless_dec:
	put_ldev(device);
 क्रमce_diskless:
	drbd_क्रमce_state(device, NS(disk, D_DISKLESS));
	drbd_md_sync(device);
 fail:
	conn_reconfig_करोne(connection);
	अगर (nbc) अणु
		बंद_backing_dev(device, nbc->md_bdev, nbc->md_bdev != nbc->backing_bdev);
		बंद_backing_dev(device, nbc->backing_bdev, true);
		kमुक्त(nbc);
	पूर्ण
	kमुक्त(new_disk_conf);
	lc_destroy(resync_lru);
	kमुक्त(new_plan);
	mutex_unlock(&adm_ctx.resource->adm_mutex);
 finish:
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;
पूर्ण

अटल पूर्णांक adm_detach(काष्ठा drbd_device *device, पूर्णांक क्रमce)
अणु
	अगर (क्रमce) अणु
		set_bit(FORCE_DETACH, &device->flags);
		drbd_क्रमce_state(device, NS(disk, D_FAILED));
		वापस SS_SUCCESS;
	पूर्ण

	वापस drbd_request_detach_पूर्णांकerruptible(device);
पूर्ण

/* Detaching the disk is a process in multiple stages.  First we need to lock
 * out application IO, in-flight IO, IO stuck in drbd_al_begin_io.
 * Then we transition to D_DISKLESS, and रुको क्रम put_ldev() to वापस all
 * पूर्णांकernal references as well.
 * Only then we have finally detached. */
पूर्णांक drbd_adm_detach(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा drbd_config_context adm_ctx;
	क्रमागत drbd_ret_code retcode;
	काष्ठा detach_parms parms = अणु पूर्ण;
	पूर्णांक err;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_MINOR);
	अगर (!adm_ctx.reply_skb)
		वापस retcode;
	अगर (retcode != NO_ERROR)
		जाओ out;

	अगर (info->attrs[DRBD_NLA_DETACH_PARMS]) अणु
		err = detach_parms_from_attrs(&parms, info);
		अगर (err) अणु
			retcode = ERR_MANDATORY_TAG;
			drbd_msg_put_info(adm_ctx.reply_skb, from_attrs_err_to_txt(err));
			जाओ out;
		पूर्ण
	पूर्ण

	mutex_lock(&adm_ctx.resource->adm_mutex);
	retcode = adm_detach(adm_ctx.device, parms.क्रमce_detach);
	mutex_unlock(&adm_ctx.resource->adm_mutex);
out:
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;
पूर्ण

अटल bool conn_resync_running(काष्ठा drbd_connection *connection)
अणु
	काष्ठा drbd_peer_device *peer_device;
	bool rv = false;
	पूर्णांक vnr;

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr) अणु
		काष्ठा drbd_device *device = peer_device->device;
		अगर (device->state.conn == C_SYNC_SOURCE ||
		    device->state.conn == C_SYNC_TARGET ||
		    device->state.conn == C_PAUSED_SYNC_S ||
		    device->state.conn == C_PAUSED_SYNC_T) अणु
			rv = true;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस rv;
पूर्ण

अटल bool conn_ov_running(काष्ठा drbd_connection *connection)
अणु
	काष्ठा drbd_peer_device *peer_device;
	bool rv = false;
	पूर्णांक vnr;

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr) अणु
		काष्ठा drbd_device *device = peer_device->device;
		अगर (device->state.conn == C_VERIFY_S ||
		    device->state.conn == C_VERIFY_T) अणु
			rv = true;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस rv;
पूर्ण

अटल क्रमागत drbd_ret_code
_check_net_options(काष्ठा drbd_connection *connection, काष्ठा net_conf *old_net_conf, काष्ठा net_conf *new_net_conf)
अणु
	काष्ठा drbd_peer_device *peer_device;
	पूर्णांक i;

	अगर (old_net_conf && connection->cstate == C_WF_REPORT_PARAMS && connection->agreed_pro_version < 100) अणु
		अगर (new_net_conf->wire_protocol != old_net_conf->wire_protocol)
			वापस ERR_NEED_APV_100;

		अगर (new_net_conf->two_primaries != old_net_conf->two_primaries)
			वापस ERR_NEED_APV_100;

		अगर (म_भेद(new_net_conf->पूर्णांकegrity_alg, old_net_conf->पूर्णांकegrity_alg))
			वापस ERR_NEED_APV_100;
	पूर्ण

	अगर (!new_net_conf->two_primaries &&
	    conn_highest_role(connection) == R_PRIMARY &&
	    conn_highest_peer(connection) == R_PRIMARY)
		वापस ERR_NEED_ALLOW_TWO_PRI;

	अगर (new_net_conf->two_primaries &&
	    (new_net_conf->wire_protocol != DRBD_PROT_C))
		वापस ERR_NOT_PROTO_C;

	idr_क्रम_each_entry(&connection->peer_devices, peer_device, i) अणु
		काष्ठा drbd_device *device = peer_device->device;
		अगर (get_ldev(device)) अणु
			क्रमागत drbd_fencing_p fp = rcu_dereference(device->ldev->disk_conf)->fencing;
			put_ldev(device);
			अगर (new_net_conf->wire_protocol == DRBD_PROT_A && fp == FP_STONITH)
				वापस ERR_STONITH_AND_PROT_A;
		पूर्ण
		अगर (device->state.role == R_PRIMARY && new_net_conf->discard_my_data)
			वापस ERR_DISCARD_IMPOSSIBLE;
	पूर्ण

	अगर (new_net_conf->on_congestion != OC_BLOCK && new_net_conf->wire_protocol != DRBD_PROT_A)
		वापस ERR_CONG_NOT_PROTO_A;

	वापस NO_ERROR;
पूर्ण

अटल क्रमागत drbd_ret_code
check_net_options(काष्ठा drbd_connection *connection, काष्ठा net_conf *new_net_conf)
अणु
	क्रमागत drbd_ret_code rv;
	काष्ठा drbd_peer_device *peer_device;
	पूर्णांक i;

	rcu_पढ़ो_lock();
	rv = _check_net_options(connection, rcu_dereference(connection->net_conf), new_net_conf);
	rcu_पढ़ो_unlock();

	/* connection->peer_devices रक्षित by genl_lock() here */
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, i) अणु
		काष्ठा drbd_device *device = peer_device->device;
		अगर (!device->biपंचांगap) अणु
			अगर (drbd_bm_init(device))
				वापस ERR_NOMEM;
		पूर्ण
	पूर्ण

	वापस rv;
पूर्ण

काष्ठा crypto अणु
	काष्ठा crypto_shash *verअगरy_tfm;
	काष्ठा crypto_shash *csums_tfm;
	काष्ठा crypto_shash *cram_hmac_tfm;
	काष्ठा crypto_shash *पूर्णांकegrity_tfm;
पूर्ण;

अटल पूर्णांक
alloc_shash(काष्ठा crypto_shash **tfm, अक्षर *tfm_name, पूर्णांक err_alg)
अणु
	अगर (!tfm_name[0])
		वापस NO_ERROR;

	*tfm = crypto_alloc_shash(tfm_name, 0, 0);
	अगर (IS_ERR(*tfm)) अणु
		*tfm = शून्य;
		वापस err_alg;
	पूर्ण

	वापस NO_ERROR;
पूर्ण

अटल क्रमागत drbd_ret_code
alloc_crypto(काष्ठा crypto *crypto, काष्ठा net_conf *new_net_conf)
अणु
	अक्षर hmac_name[CRYPTO_MAX_ALG_NAME];
	क्रमागत drbd_ret_code rv;

	rv = alloc_shash(&crypto->csums_tfm, new_net_conf->csums_alg,
			 ERR_CSUMS_ALG);
	अगर (rv != NO_ERROR)
		वापस rv;
	rv = alloc_shash(&crypto->verअगरy_tfm, new_net_conf->verअगरy_alg,
			 ERR_VERIFY_ALG);
	अगर (rv != NO_ERROR)
		वापस rv;
	rv = alloc_shash(&crypto->पूर्णांकegrity_tfm, new_net_conf->पूर्णांकegrity_alg,
			 ERR_INTEGRITY_ALG);
	अगर (rv != NO_ERROR)
		वापस rv;
	अगर (new_net_conf->cram_hmac_alg[0] != 0) अणु
		snम_लिखो(hmac_name, CRYPTO_MAX_ALG_NAME, "hmac(%s)",
			 new_net_conf->cram_hmac_alg);

		rv = alloc_shash(&crypto->cram_hmac_tfm, hmac_name,
				 ERR_AUTH_ALG);
	पूर्ण

	वापस rv;
पूर्ण

अटल व्योम मुक्त_crypto(काष्ठा crypto *crypto)
अणु
	crypto_मुक्त_shash(crypto->cram_hmac_tfm);
	crypto_मुक्त_shash(crypto->पूर्णांकegrity_tfm);
	crypto_मुक्त_shash(crypto->csums_tfm);
	crypto_मुक्त_shash(crypto->verअगरy_tfm);
पूर्ण

पूर्णांक drbd_adm_net_opts(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा drbd_config_context adm_ctx;
	क्रमागत drbd_ret_code retcode;
	काष्ठा drbd_connection *connection;
	काष्ठा net_conf *old_net_conf, *new_net_conf = शून्य;
	पूर्णांक err;
	पूर्णांक ovr; /* online verअगरy running */
	पूर्णांक rsr; /* re-sync running */
	काष्ठा crypto crypto = अणु पूर्ण;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_CONNECTION);
	अगर (!adm_ctx.reply_skb)
		वापस retcode;
	अगर (retcode != NO_ERROR)
		जाओ finish;

	connection = adm_ctx.connection;
	mutex_lock(&adm_ctx.resource->adm_mutex);

	new_net_conf = kzalloc(माप(काष्ठा net_conf), GFP_KERNEL);
	अगर (!new_net_conf) अणु
		retcode = ERR_NOMEM;
		जाओ out;
	पूर्ण

	conn_reconfig_start(connection);

	mutex_lock(&connection->data.mutex);
	mutex_lock(&connection->resource->conf_update);
	old_net_conf = connection->net_conf;

	अगर (!old_net_conf) अणु
		drbd_msg_put_info(adm_ctx.reply_skb, "net conf missing, try connect");
		retcode = ERR_INVALID_REQUEST;
		जाओ fail;
	पूर्ण

	*new_net_conf = *old_net_conf;
	अगर (should_set_शेषs(info))
		set_net_conf_शेषs(new_net_conf);

	err = net_conf_from_attrs_क्रम_change(new_net_conf, info);
	अगर (err && err != -ENOMSG) अणु
		retcode = ERR_MANDATORY_TAG;
		drbd_msg_put_info(adm_ctx.reply_skb, from_attrs_err_to_txt(err));
		जाओ fail;
	पूर्ण

	retcode = check_net_options(connection, new_net_conf);
	अगर (retcode != NO_ERROR)
		जाओ fail;

	/* re-sync running */
	rsr = conn_resync_running(connection);
	अगर (rsr && म_भेद(new_net_conf->csums_alg, old_net_conf->csums_alg)) अणु
		retcode = ERR_CSUMS_RESYNC_RUNNING;
		जाओ fail;
	पूर्ण

	/* online verअगरy running */
	ovr = conn_ov_running(connection);
	अगर (ovr && म_भेद(new_net_conf->verअगरy_alg, old_net_conf->verअगरy_alg)) अणु
		retcode = ERR_VERIFY_RUNNING;
		जाओ fail;
	पूर्ण

	retcode = alloc_crypto(&crypto, new_net_conf);
	अगर (retcode != NO_ERROR)
		जाओ fail;

	rcu_assign_poपूर्णांकer(connection->net_conf, new_net_conf);

	अगर (!rsr) अणु
		crypto_मुक्त_shash(connection->csums_tfm);
		connection->csums_tfm = crypto.csums_tfm;
		crypto.csums_tfm = शून्य;
	पूर्ण
	अगर (!ovr) अणु
		crypto_मुक्त_shash(connection->verअगरy_tfm);
		connection->verअगरy_tfm = crypto.verअगरy_tfm;
		crypto.verअगरy_tfm = शून्य;
	पूर्ण

	crypto_मुक्त_shash(connection->पूर्णांकegrity_tfm);
	connection->पूर्णांकegrity_tfm = crypto.पूर्णांकegrity_tfm;
	अगर (connection->cstate >= C_WF_REPORT_PARAMS && connection->agreed_pro_version >= 100)
		/* Do this without trying to take connection->data.mutex again.  */
		__drbd_send_protocol(connection, P_PROTOCOL_UPDATE);

	crypto_मुक्त_shash(connection->cram_hmac_tfm);
	connection->cram_hmac_tfm = crypto.cram_hmac_tfm;

	mutex_unlock(&connection->resource->conf_update);
	mutex_unlock(&connection->data.mutex);
	synchronize_rcu();
	kमुक्त(old_net_conf);

	अगर (connection->cstate >= C_WF_REPORT_PARAMS) अणु
		काष्ठा drbd_peer_device *peer_device;
		पूर्णांक vnr;

		idr_क्रम_each_entry(&connection->peer_devices, peer_device, vnr)
			drbd_send_sync_param(peer_device);
	पूर्ण

	जाओ करोne;

 fail:
	mutex_unlock(&connection->resource->conf_update);
	mutex_unlock(&connection->data.mutex);
	मुक्त_crypto(&crypto);
	kमुक्त(new_net_conf);
 करोne:
	conn_reconfig_करोne(connection);
 out:
	mutex_unlock(&adm_ctx.resource->adm_mutex);
 finish:
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;
पूर्ण

अटल व्योम connection_to_info(काष्ठा connection_info *info,
			       काष्ठा drbd_connection *connection)
अणु
	info->conn_connection_state = connection->cstate;
	info->conn_role = conn_highest_peer(connection);
पूर्ण

अटल व्योम peer_device_to_info(काष्ठा peer_device_info *info,
				काष्ठा drbd_peer_device *peer_device)
अणु
	काष्ठा drbd_device *device = peer_device->device;

	info->peer_repl_state =
		max_t(क्रमागत drbd_conns, C_WF_REPORT_PARAMS, device->state.conn);
	info->peer_disk_state = device->state.pdsk;
	info->peer_resync_susp_user = device->state.user_isp;
	info->peer_resync_susp_peer = device->state.peer_isp;
	info->peer_resync_susp_dependency = device->state.aftr_isp;
पूर्ण

पूर्णांक drbd_adm_connect(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा connection_info connection_info;
	क्रमागत drbd_notअगरication_type flags;
	अचिन्हित पूर्णांक peer_devices = 0;
	काष्ठा drbd_config_context adm_ctx;
	काष्ठा drbd_peer_device *peer_device;
	काष्ठा net_conf *old_net_conf, *new_net_conf = शून्य;
	काष्ठा crypto crypto = अणु पूर्ण;
	काष्ठा drbd_resource *resource;
	काष्ठा drbd_connection *connection;
	क्रमागत drbd_ret_code retcode;
	पूर्णांक i;
	पूर्णांक err;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_RESOURCE);

	अगर (!adm_ctx.reply_skb)
		वापस retcode;
	अगर (retcode != NO_ERROR)
		जाओ out;
	अगर (!(adm_ctx.my_addr && adm_ctx.peer_addr)) अणु
		drbd_msg_put_info(adm_ctx.reply_skb, "connection endpoint(s) missing");
		retcode = ERR_INVALID_REQUEST;
		जाओ out;
	पूर्ण

	/* No need क्रम _rcu here. All reconfiguration is
	 * strictly serialized on genl_lock(). We are रक्षित against
	 * concurrent reconfiguration/addition/deletion */
	क्रम_each_resource(resource, &drbd_resources) अणु
		क्रम_each_connection(connection, resource) अणु
			अगर (nla_len(adm_ctx.my_addr) == connection->my_addr_len &&
			    !स_भेद(nla_data(adm_ctx.my_addr), &connection->my_addr,
				    connection->my_addr_len)) अणु
				retcode = ERR_LOCAL_ADDR;
				जाओ out;
			पूर्ण

			अगर (nla_len(adm_ctx.peer_addr) == connection->peer_addr_len &&
			    !स_भेद(nla_data(adm_ctx.peer_addr), &connection->peer_addr,
				    connection->peer_addr_len)) अणु
				retcode = ERR_PEER_ADDR;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_lock(&adm_ctx.resource->adm_mutex);
	connection = first_connection(adm_ctx.resource);
	conn_reconfig_start(connection);

	अगर (connection->cstate > C_STANDALONE) अणु
		retcode = ERR_NET_CONFIGURED;
		जाओ fail;
	पूर्ण

	/* allocation not in the IO path, drbdsetup / netlink process context */
	new_net_conf = kzalloc(माप(*new_net_conf), GFP_KERNEL);
	अगर (!new_net_conf) अणु
		retcode = ERR_NOMEM;
		जाओ fail;
	पूर्ण

	set_net_conf_शेषs(new_net_conf);

	err = net_conf_from_attrs(new_net_conf, info);
	अगर (err && err != -ENOMSG) अणु
		retcode = ERR_MANDATORY_TAG;
		drbd_msg_put_info(adm_ctx.reply_skb, from_attrs_err_to_txt(err));
		जाओ fail;
	पूर्ण

	retcode = check_net_options(connection, new_net_conf);
	अगर (retcode != NO_ERROR)
		जाओ fail;

	retcode = alloc_crypto(&crypto, new_net_conf);
	अगर (retcode != NO_ERROR)
		जाओ fail;

	((अक्षर *)new_net_conf->shared_secret)[SHARED_SECRET_MAX-1] = 0;

	drbd_flush_workqueue(&connection->sender_work);

	mutex_lock(&adm_ctx.resource->conf_update);
	old_net_conf = connection->net_conf;
	अगर (old_net_conf) अणु
		retcode = ERR_NET_CONFIGURED;
		mutex_unlock(&adm_ctx.resource->conf_update);
		जाओ fail;
	पूर्ण
	rcu_assign_poपूर्णांकer(connection->net_conf, new_net_conf);

	conn_मुक्त_crypto(connection);
	connection->cram_hmac_tfm = crypto.cram_hmac_tfm;
	connection->पूर्णांकegrity_tfm = crypto.पूर्णांकegrity_tfm;
	connection->csums_tfm = crypto.csums_tfm;
	connection->verअगरy_tfm = crypto.verअगरy_tfm;

	connection->my_addr_len = nla_len(adm_ctx.my_addr);
	स_नकल(&connection->my_addr, nla_data(adm_ctx.my_addr), connection->my_addr_len);
	connection->peer_addr_len = nla_len(adm_ctx.peer_addr);
	स_नकल(&connection->peer_addr, nla_data(adm_ctx.peer_addr), connection->peer_addr_len);

	idr_क्रम_each_entry(&connection->peer_devices, peer_device, i) अणु
		peer_devices++;
	पूर्ण

	connection_to_info(&connection_info, connection);
	flags = (peer_devices--) ? NOTIFY_CONTINUES : 0;
	mutex_lock(&notअगरication_mutex);
	notअगरy_connection_state(शून्य, 0, connection, &connection_info, NOTIFY_CREATE | flags);
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, i) अणु
		काष्ठा peer_device_info peer_device_info;

		peer_device_to_info(&peer_device_info, peer_device);
		flags = (peer_devices--) ? NOTIFY_CONTINUES : 0;
		notअगरy_peer_device_state(शून्य, 0, peer_device, &peer_device_info, NOTIFY_CREATE | flags);
	पूर्ण
	mutex_unlock(&notअगरication_mutex);
	mutex_unlock(&adm_ctx.resource->conf_update);

	rcu_पढ़ो_lock();
	idr_क्रम_each_entry(&connection->peer_devices, peer_device, i) अणु
		काष्ठा drbd_device *device = peer_device->device;
		device->send_cnt = 0;
		device->recv_cnt = 0;
	पूर्ण
	rcu_पढ़ो_unlock();

	retcode = (क्रमागत drbd_ret_code)conn_request_state(connection,
					NS(conn, C_UNCONNECTED), CS_VERBOSE);

	conn_reconfig_करोne(connection);
	mutex_unlock(&adm_ctx.resource->adm_mutex);
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;

fail:
	मुक्त_crypto(&crypto);
	kमुक्त(new_net_conf);

	conn_reconfig_करोne(connection);
	mutex_unlock(&adm_ctx.resource->adm_mutex);
out:
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;
पूर्ण

अटल क्रमागत drbd_state_rv conn_try_disconnect(काष्ठा drbd_connection *connection, bool क्रमce)
अणु
	क्रमागत drbd_conns cstate;
	क्रमागत drbd_state_rv rv;

repeat:
	rv = conn_request_state(connection, NS(conn, C_DISCONNECTING),
			क्रमce ? CS_HARD : 0);

	चयन (rv) अणु
	हाल SS_NOTHING_TO_DO:
		अवरोध;
	हाल SS_ALREADY_STANDALONE:
		वापस SS_SUCCESS;
	हाल SS_PRIMARY_NOP:
		/* Our state checking code wants to see the peer outdated. */
		rv = conn_request_state(connection, NS2(conn, C_DISCONNECTING, pdsk, D_OUTDATED), 0);

		अगर (rv == SS_OUTDATE_WO_CONN) /* lost connection beक्रमe graceful disconnect succeeded */
			rv = conn_request_state(connection, NS(conn, C_DISCONNECTING), CS_VERBOSE);

		अवरोध;
	हाल SS_CW_FAILED_BY_PEER:
		spin_lock_irq(&connection->resource->req_lock);
		cstate = connection->cstate;
		spin_unlock_irq(&connection->resource->req_lock);
		अगर (cstate <= C_WF_CONNECTION)
			जाओ repeat;
		/* The peer probably wants to see us outdated. */
		rv = conn_request_state(connection, NS2(conn, C_DISCONNECTING,
							disk, D_OUTDATED), 0);
		अगर (rv == SS_IS_DISKLESS || rv == SS_LOWER_THAN_OUTDATED) अणु
			rv = conn_request_state(connection, NS(conn, C_DISCONNECTING),
					CS_HARD);
		पूर्ण
		अवरोध;
	शेष:;
		/* no special handling necessary */
	पूर्ण

	अगर (rv >= SS_SUCCESS) अणु
		क्रमागत drbd_state_rv rv2;
		/* No one अन्यथा can reconfigure the network जबतक I am here.
		 * The state handling only uses drbd_thपढ़ो_stop_noरुको(),
		 * we want to really रुको here until the receiver is no more.
		 */
		drbd_thपढ़ो_stop(&connection->receiver);

		/* Race अवरोधer.  This additional state change request may be
		 * necessary, अगर this was a क्रमced disconnect during a receiver
		 * restart.  We may have "killed" the receiver thपढ़ो just
		 * after drbd_receiver() वापसed.  Typically, we should be
		 * C_STANDALONE alपढ़ोy, now, and this becomes a no-op.
		 */
		rv2 = conn_request_state(connection, NS(conn, C_STANDALONE),
				CS_VERBOSE | CS_HARD);
		अगर (rv2 < SS_SUCCESS)
			drbd_err(connection,
				"unexpected rv2=%d in conn_try_disconnect()\n",
				rv2);
		/* Unlike in DRBD 9, the state engine has generated
		 * NOTIFY_DESTROY events beक्रमe clearing connection->net_conf. */
	पूर्ण
	वापस rv;
पूर्ण

पूर्णांक drbd_adm_disconnect(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा drbd_config_context adm_ctx;
	काष्ठा disconnect_parms parms;
	काष्ठा drbd_connection *connection;
	क्रमागत drbd_state_rv rv;
	क्रमागत drbd_ret_code retcode;
	पूर्णांक err;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_CONNECTION);
	अगर (!adm_ctx.reply_skb)
		वापस retcode;
	अगर (retcode != NO_ERROR)
		जाओ fail;

	connection = adm_ctx.connection;
	स_रखो(&parms, 0, माप(parms));
	अगर (info->attrs[DRBD_NLA_DISCONNECT_PARMS]) अणु
		err = disconnect_parms_from_attrs(&parms, info);
		अगर (err) अणु
			retcode = ERR_MANDATORY_TAG;
			drbd_msg_put_info(adm_ctx.reply_skb, from_attrs_err_to_txt(err));
			जाओ fail;
		पूर्ण
	पूर्ण

	mutex_lock(&adm_ctx.resource->adm_mutex);
	rv = conn_try_disconnect(connection, parms.क्रमce_disconnect);
	अगर (rv < SS_SUCCESS)
		retcode = (क्रमागत drbd_ret_code)rv;
	अन्यथा
		retcode = NO_ERROR;
	mutex_unlock(&adm_ctx.resource->adm_mutex);
 fail:
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;
पूर्ण

व्योम resync_after_online_grow(काष्ठा drbd_device *device)
अणु
	पूर्णांक iass; /* I am sync source */

	drbd_info(device, "Resync of new storage after online grow\n");
	अगर (device->state.role != device->state.peer)
		iass = (device->state.role == R_PRIMARY);
	अन्यथा
		iass = test_bit(RESOLVE_CONFLICTS, &first_peer_device(device)->connection->flags);

	अगर (iass)
		drbd_start_resync(device, C_SYNC_SOURCE);
	अन्यथा
		_drbd_request_state(device, NS(conn, C_WF_SYNC_UUID), CS_VERBOSE + CS_SERIALIZE);
पूर्ण

पूर्णांक drbd_adm_resize(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा drbd_config_context adm_ctx;
	काष्ठा disk_conf *old_disk_conf, *new_disk_conf = शून्य;
	काष्ठा resize_parms rs;
	काष्ठा drbd_device *device;
	क्रमागत drbd_ret_code retcode;
	क्रमागत determine_dev_size dd;
	bool change_al_layout = false;
	क्रमागत dds_flags ddsf;
	sector_t u_size;
	पूर्णांक err;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_MINOR);
	अगर (!adm_ctx.reply_skb)
		वापस retcode;
	अगर (retcode != NO_ERROR)
		जाओ finish;

	mutex_lock(&adm_ctx.resource->adm_mutex);
	device = adm_ctx.device;
	अगर (!get_ldev(device)) अणु
		retcode = ERR_NO_DISK;
		जाओ fail;
	पूर्ण

	स_रखो(&rs, 0, माप(काष्ठा resize_parms));
	rs.al_stripes = device->ldev->md.al_stripes;
	rs.al_stripe_size = device->ldev->md.al_stripe_size_4k * 4;
	अगर (info->attrs[DRBD_NLA_RESIZE_PARMS]) अणु
		err = resize_parms_from_attrs(&rs, info);
		अगर (err) अणु
			retcode = ERR_MANDATORY_TAG;
			drbd_msg_put_info(adm_ctx.reply_skb, from_attrs_err_to_txt(err));
			जाओ fail_ldev;
		पूर्ण
	पूर्ण

	अगर (device->state.conn > C_CONNECTED) अणु
		retcode = ERR_RESIZE_RESYNC;
		जाओ fail_ldev;
	पूर्ण

	अगर (device->state.role == R_SECONDARY &&
	    device->state.peer == R_SECONDARY) अणु
		retcode = ERR_NO_PRIMARY;
		जाओ fail_ldev;
	पूर्ण

	अगर (rs.no_resync && first_peer_device(device)->connection->agreed_pro_version < 93) अणु
		retcode = ERR_NEED_APV_93;
		जाओ fail_ldev;
	पूर्ण

	rcu_पढ़ो_lock();
	u_size = rcu_dereference(device->ldev->disk_conf)->disk_size;
	rcu_पढ़ो_unlock();
	अगर (u_size != (sector_t)rs.resize_size) अणु
		new_disk_conf = kदो_स्मृति(माप(काष्ठा disk_conf), GFP_KERNEL);
		अगर (!new_disk_conf) अणु
			retcode = ERR_NOMEM;
			जाओ fail_ldev;
		पूर्ण
	पूर्ण

	अगर (device->ldev->md.al_stripes != rs.al_stripes ||
	    device->ldev->md.al_stripe_size_4k != rs.al_stripe_size / 4) अणु
		u32 al_size_k = rs.al_stripes * rs.al_stripe_size;

		अगर (al_size_k > (16 * 1024 * 1024)) अणु
			retcode = ERR_MD_LAYOUT_TOO_BIG;
			जाओ fail_ldev;
		पूर्ण

		अगर (al_size_k < MD_32kB_SECT/2) अणु
			retcode = ERR_MD_LAYOUT_TOO_SMALL;
			जाओ fail_ldev;
		पूर्ण

		अगर (device->state.conn != C_CONNECTED && !rs.resize_क्रमce) अणु
			retcode = ERR_MD_LAYOUT_CONNECTED;
			जाओ fail_ldev;
		पूर्ण

		change_al_layout = true;
	पूर्ण

	अगर (device->ldev->known_size != drbd_get_capacity(device->ldev->backing_bdev))
		device->ldev->known_size = drbd_get_capacity(device->ldev->backing_bdev);

	अगर (new_disk_conf) अणु
		mutex_lock(&device->resource->conf_update);
		old_disk_conf = device->ldev->disk_conf;
		*new_disk_conf = *old_disk_conf;
		new_disk_conf->disk_size = (sector_t)rs.resize_size;
		rcu_assign_poपूर्णांकer(device->ldev->disk_conf, new_disk_conf);
		mutex_unlock(&device->resource->conf_update);
		synchronize_rcu();
		kमुक्त(old_disk_conf);
		new_disk_conf = शून्य;
	पूर्ण

	ddsf = (rs.resize_क्रमce ? DDSF_FORCED : 0) | (rs.no_resync ? DDSF_NO_RESYNC : 0);
	dd = drbd_determine_dev_size(device, ddsf, change_al_layout ? &rs : शून्य);
	drbd_md_sync(device);
	put_ldev(device);
	अगर (dd == DS_ERROR) अणु
		retcode = ERR_NOMEM_BITMAP;
		जाओ fail;
	पूर्ण अन्यथा अगर (dd == DS_ERROR_SPACE_MD) अणु
		retcode = ERR_MD_LAYOUT_NO_FIT;
		जाओ fail;
	पूर्ण अन्यथा अगर (dd == DS_ERROR_SHRINK) अणु
		retcode = ERR_IMPLICIT_SHRINK;
		जाओ fail;
	पूर्ण

	अगर (device->state.conn == C_CONNECTED) अणु
		अगर (dd == DS_GREW)
			set_bit(RESIZE_PENDING, &device->flags);

		drbd_send_uuids(first_peer_device(device));
		drbd_send_sizes(first_peer_device(device), 1, ddsf);
	पूर्ण

 fail:
	mutex_unlock(&adm_ctx.resource->adm_mutex);
 finish:
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;

 fail_ldev:
	put_ldev(device);
	kमुक्त(new_disk_conf);
	जाओ fail;
पूर्ण

पूर्णांक drbd_adm_resource_opts(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा drbd_config_context adm_ctx;
	क्रमागत drbd_ret_code retcode;
	काष्ठा res_opts res_opts;
	पूर्णांक err;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_RESOURCE);
	अगर (!adm_ctx.reply_skb)
		वापस retcode;
	अगर (retcode != NO_ERROR)
		जाओ fail;

	res_opts = adm_ctx.resource->res_opts;
	अगर (should_set_शेषs(info))
		set_res_opts_शेषs(&res_opts);

	err = res_opts_from_attrs(&res_opts, info);
	अगर (err && err != -ENOMSG) अणु
		retcode = ERR_MANDATORY_TAG;
		drbd_msg_put_info(adm_ctx.reply_skb, from_attrs_err_to_txt(err));
		जाओ fail;
	पूर्ण

	mutex_lock(&adm_ctx.resource->adm_mutex);
	err = set_resource_options(adm_ctx.resource, &res_opts);
	अगर (err) अणु
		retcode = ERR_INVALID_REQUEST;
		अगर (err == -ENOMEM)
			retcode = ERR_NOMEM;
	पूर्ण
	mutex_unlock(&adm_ctx.resource->adm_mutex);

fail:
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;
पूर्ण

पूर्णांक drbd_adm_invalidate(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा drbd_config_context adm_ctx;
	काष्ठा drbd_device *device;
	पूर्णांक retcode; /* क्रमागत drbd_ret_code rsp. क्रमागत drbd_state_rv */

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_MINOR);
	अगर (!adm_ctx.reply_skb)
		वापस retcode;
	अगर (retcode != NO_ERROR)
		जाओ out;

	device = adm_ctx.device;
	अगर (!get_ldev(device)) अणु
		retcode = ERR_NO_DISK;
		जाओ out;
	पूर्ण

	mutex_lock(&adm_ctx.resource->adm_mutex);

	/* If there is still biपंचांगap IO pending, probably because of a previous
	 * resync just being finished, रुको क्रम it beक्रमe requesting a new resync.
	 * Also रुको क्रम it's after_state_ch(). */
	drbd_suspend_io(device);
	रुको_event(device->misc_रुको, !test_bit(BITMAP_IO, &device->flags));
	drbd_flush_workqueue(&first_peer_device(device)->connection->sender_work);

	/* If we happen to be C_STANDALONE R_SECONDARY, just change to
	 * D_INCONSISTENT, and set all bits in the biपंचांगap.  Otherwise,
	 * try to start a resync handshake as sync target क्रम full sync.
	 */
	अगर (device->state.conn == C_STANDALONE && device->state.role == R_SECONDARY) अणु
		retcode = drbd_request_state(device, NS(disk, D_INCONSISTENT));
		अगर (retcode >= SS_SUCCESS) अणु
			अगर (drbd_biपंचांगap_io(device, &drbd_bmio_set_n_ग_लिखो,
				"set_n_write from invalidate", BM_LOCKED_MASK))
				retcode = ERR_IO_MD_DISK;
		पूर्ण
	पूर्ण अन्यथा
		retcode = drbd_request_state(device, NS(conn, C_STARTING_SYNC_T));
	drbd_resume_io(device);
	mutex_unlock(&adm_ctx.resource->adm_mutex);
	put_ldev(device);
out:
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;
पूर्ण

अटल पूर्णांक drbd_adm_simple_request_state(काष्ठा sk_buff *skb, काष्ठा genl_info *info,
		जोड़ drbd_state mask, जोड़ drbd_state val)
अणु
	काष्ठा drbd_config_context adm_ctx;
	क्रमागत drbd_ret_code retcode;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_MINOR);
	अगर (!adm_ctx.reply_skb)
		वापस retcode;
	अगर (retcode != NO_ERROR)
		जाओ out;

	mutex_lock(&adm_ctx.resource->adm_mutex);
	retcode = drbd_request_state(adm_ctx.device, mask, val);
	mutex_unlock(&adm_ctx.resource->adm_mutex);
out:
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;
पूर्ण

अटल पूर्णांक drbd_bmio_set_susp_al(काष्ठा drbd_device *device) __must_hold(local)
अणु
	पूर्णांक rv;

	rv = drbd_bmio_set_n_ग_लिखो(device);
	drbd_suspend_al(device);
	वापस rv;
पूर्ण

पूर्णांक drbd_adm_invalidate_peer(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा drbd_config_context adm_ctx;
	पूर्णांक retcode; /* drbd_ret_code, drbd_state_rv */
	काष्ठा drbd_device *device;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_MINOR);
	अगर (!adm_ctx.reply_skb)
		वापस retcode;
	अगर (retcode != NO_ERROR)
		जाओ out;

	device = adm_ctx.device;
	अगर (!get_ldev(device)) अणु
		retcode = ERR_NO_DISK;
		जाओ out;
	पूर्ण

	mutex_lock(&adm_ctx.resource->adm_mutex);

	/* If there is still biपंचांगap IO pending, probably because of a previous
	 * resync just being finished, रुको क्रम it beक्रमe requesting a new resync.
	 * Also रुको क्रम it's after_state_ch(). */
	drbd_suspend_io(device);
	रुको_event(device->misc_रुको, !test_bit(BITMAP_IO, &device->flags));
	drbd_flush_workqueue(&first_peer_device(device)->connection->sender_work);

	/* If we happen to be C_STANDALONE R_PRIMARY, just set all bits
	 * in the biपंचांगap.  Otherwise, try to start a resync handshake
	 * as sync source क्रम full sync.
	 */
	अगर (device->state.conn == C_STANDALONE && device->state.role == R_PRIMARY) अणु
		/* The peer will get a resync upon connect anyways. Just make that
		   पूर्णांकo a full resync. */
		retcode = drbd_request_state(device, NS(pdsk, D_INCONSISTENT));
		अगर (retcode >= SS_SUCCESS) अणु
			अगर (drbd_biपंचांगap_io(device, &drbd_bmio_set_susp_al,
				"set_n_write from invalidate_peer",
				BM_LOCKED_SET_ALLOWED))
				retcode = ERR_IO_MD_DISK;
		पूर्ण
	पूर्ण अन्यथा
		retcode = drbd_request_state(device, NS(conn, C_STARTING_SYNC_S));
	drbd_resume_io(device);
	mutex_unlock(&adm_ctx.resource->adm_mutex);
	put_ldev(device);
out:
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;
पूर्ण

पूर्णांक drbd_adm_छोड़ो_sync(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा drbd_config_context adm_ctx;
	क्रमागत drbd_ret_code retcode;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_MINOR);
	अगर (!adm_ctx.reply_skb)
		वापस retcode;
	अगर (retcode != NO_ERROR)
		जाओ out;

	mutex_lock(&adm_ctx.resource->adm_mutex);
	अगर (drbd_request_state(adm_ctx.device, NS(user_isp, 1)) == SS_NOTHING_TO_DO)
		retcode = ERR_PAUSE_IS_SET;
	mutex_unlock(&adm_ctx.resource->adm_mutex);
out:
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;
पूर्ण

पूर्णांक drbd_adm_resume_sync(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा drbd_config_context adm_ctx;
	जोड़ drbd_dev_state s;
	क्रमागत drbd_ret_code retcode;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_MINOR);
	अगर (!adm_ctx.reply_skb)
		वापस retcode;
	अगर (retcode != NO_ERROR)
		जाओ out;

	mutex_lock(&adm_ctx.resource->adm_mutex);
	अगर (drbd_request_state(adm_ctx.device, NS(user_isp, 0)) == SS_NOTHING_TO_DO) अणु
		s = adm_ctx.device->state;
		अगर (s.conn == C_PAUSED_SYNC_S || s.conn == C_PAUSED_SYNC_T) अणु
			retcode = s.aftr_isp ? ERR_PIC_AFTER_DEP :
				  s.peer_isp ? ERR_PIC_PEER_DEP : ERR_PAUSE_IS_CLEAR;
		पूर्ण अन्यथा अणु
			retcode = ERR_PAUSE_IS_CLEAR;
		पूर्ण
	पूर्ण
	mutex_unlock(&adm_ctx.resource->adm_mutex);
out:
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;
पूर्ण

पूर्णांक drbd_adm_suspend_io(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	वापस drbd_adm_simple_request_state(skb, info, NS(susp, 1));
पूर्ण

पूर्णांक drbd_adm_resume_io(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा drbd_config_context adm_ctx;
	काष्ठा drbd_device *device;
	पूर्णांक retcode; /* क्रमागत drbd_ret_code rsp. क्रमागत drbd_state_rv */

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_MINOR);
	अगर (!adm_ctx.reply_skb)
		वापस retcode;
	अगर (retcode != NO_ERROR)
		जाओ out;

	mutex_lock(&adm_ctx.resource->adm_mutex);
	device = adm_ctx.device;
	अगर (test_bit(NEW_CUR_UUID, &device->flags)) अणु
		अगर (get_ldev_अगर_state(device, D_ATTACHING)) अणु
			drbd_uuid_new_current(device);
			put_ldev(device);
		पूर्ण अन्यथा अणु
			/* This is effectively a multi-stage "forced down".
			 * The NEW_CUR_UUID bit is supposedly only set, अगर we
			 * lost the replication connection, and are configured
			 * to मुक्तze IO and रुको क्रम some fence-peer handler.
			 * So we still करोn't have a replication connection.
			 * And now we करोn't have a local disk either.  After
			 * resume, we will fail all pending and new IO, because
			 * we करोn't have any data anymore.  Which means we will
			 * eventually be able to terminate all users of this
			 * device, and then take it करोwn.  By bumping the
			 * "effective" data uuid, we make sure that you really
			 * need to tear करोwn beक्रमe you reconfigure, we will
			 * the refuse to re-connect or re-attach (because no
			 * matching real data uuid exists).
			 */
			u64 val;
			get_अक्रमom_bytes(&val, माप(u64));
			drbd_set_ed_uuid(device, val);
			drbd_warn(device, "Resumed without access to data; please tear down before attempting to re-configure.\n");
		पूर्ण
		clear_bit(NEW_CUR_UUID, &device->flags);
	पूर्ण
	drbd_suspend_io(device);
	retcode = drbd_request_state(device, NS3(susp, 0, susp_nod, 0, susp_fen, 0));
	अगर (retcode == SS_SUCCESS) अणु
		अगर (device->state.conn < C_CONNECTED)
			tl_clear(first_peer_device(device)->connection);
		अगर (device->state.disk == D_DISKLESS || device->state.disk == D_FAILED)
			tl_restart(first_peer_device(device)->connection, FAIL_FROZEN_DISK_IO);
	पूर्ण
	drbd_resume_io(device);
	mutex_unlock(&adm_ctx.resource->adm_mutex);
out:
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;
पूर्ण

पूर्णांक drbd_adm_outdate(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	वापस drbd_adm_simple_request_state(skb, info, NS(disk, D_OUTDATED));
पूर्ण

अटल पूर्णांक nla_put_drbd_cfg_context(काष्ठा sk_buff *skb,
				    काष्ठा drbd_resource *resource,
				    काष्ठा drbd_connection *connection,
				    काष्ठा drbd_device *device)
अणु
	काष्ठा nlattr *nla;
	nla = nla_nest_start_noflag(skb, DRBD_NLA_CFG_CONTEXT);
	अगर (!nla)
		जाओ nla_put_failure;
	अगर (device &&
	    nla_put_u32(skb, T_ctx_volume, device->vnr))
		जाओ nla_put_failure;
	अगर (nla_put_string(skb, T_ctx_resource_name, resource->name))
		जाओ nla_put_failure;
	अगर (connection) अणु
		अगर (connection->my_addr_len &&
		    nla_put(skb, T_ctx_my_addr, connection->my_addr_len, &connection->my_addr))
			जाओ nla_put_failure;
		अगर (connection->peer_addr_len &&
		    nla_put(skb, T_ctx_peer_addr, connection->peer_addr_len, &connection->peer_addr))
			जाओ nla_put_failure;
	पूर्ण
	nla_nest_end(skb, nla);
	वापस 0;

nla_put_failure:
	अगर (nla)
		nla_nest_cancel(skb, nla);
	वापस -EMSGSIZE;
पूर्ण

/*
 * The generic netlink dump callbacks are called outside the genl_lock(), so
 * they cannot use the simple attribute parsing code which uses global
 * attribute tables.
 */
अटल काष्ठा nlattr *find_cfg_context_attr(स्थिर काष्ठा nlmsghdr *nlh, पूर्णांक attr)
अणु
	स्थिर अचिन्हित hdrlen = GENL_HDRLEN + GENL_MAGIC_FAMILY_HDRSZ;
	स्थिर पूर्णांक maxtype = ARRAY_SIZE(drbd_cfg_context_nl_policy) - 1;
	काष्ठा nlattr *nla;

	nla = nla_find(nlmsg_attrdata(nlh, hdrlen), nlmsg_attrlen(nlh, hdrlen),
		       DRBD_NLA_CFG_CONTEXT);
	अगर (!nla)
		वापस शून्य;
	वापस drbd_nla_find_nested(maxtype, nla, __nla_type(attr));
पूर्ण

अटल व्योम resource_to_info(काष्ठा resource_info *, काष्ठा drbd_resource *);

पूर्णांक drbd_adm_dump_resources(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा drbd_genlmsghdr *dh;
	काष्ठा drbd_resource *resource;
	काष्ठा resource_info resource_info;
	काष्ठा resource_statistics resource_statistics;
	पूर्णांक err;

	rcu_पढ़ो_lock();
	अगर (cb->args[0]) अणु
		क्रम_each_resource_rcu(resource, &drbd_resources)
			अगर (resource == (काष्ठा drbd_resource *)cb->args[0])
				जाओ found_resource;
		err = 0;  /* resource was probably deleted */
		जाओ out;
	पूर्ण
	resource = list_entry(&drbd_resources,
			      काष्ठा drbd_resource, resources);

found_resource:
	list_क्रम_each_entry_जारी_rcu(resource, &drbd_resources, resources) अणु
		जाओ put_result;
	पूर्ण
	err = 0;
	जाओ out;

put_result:
	dh = genlmsg_put(skb, NETLINK_CB(cb->skb).portid,
			cb->nlh->nlmsg_seq, &drbd_genl_family,
			NLM_F_MULTI, DRBD_ADM_GET_RESOURCES);
	err = -ENOMEM;
	अगर (!dh)
		जाओ out;
	dh->minor = -1U;
	dh->ret_code = NO_ERROR;
	err = nla_put_drbd_cfg_context(skb, resource, शून्य, शून्य);
	अगर (err)
		जाओ out;
	err = res_opts_to_skb(skb, &resource->res_opts, !capable(CAP_SYS_ADMIN));
	अगर (err)
		जाओ out;
	resource_to_info(&resource_info, resource);
	err = resource_info_to_skb(skb, &resource_info, !capable(CAP_SYS_ADMIN));
	अगर (err)
		जाओ out;
	resource_statistics.res_stat_ग_लिखो_ordering = resource->ग_लिखो_ordering;
	err = resource_statistics_to_skb(skb, &resource_statistics, !capable(CAP_SYS_ADMIN));
	अगर (err)
		जाओ out;
	cb->args[0] = (दीर्घ)resource;
	genlmsg_end(skb, dh);
	err = 0;

out:
	rcu_पढ़ो_unlock();
	अगर (err)
		वापस err;
	वापस skb->len;
पूर्ण

अटल व्योम device_to_statistics(काष्ठा device_statistics *s,
				 काष्ठा drbd_device *device)
अणु
	स_रखो(s, 0, माप(*s));
	s->dev_upper_blocked = !may_inc_ap_bio(device);
	अगर (get_ldev(device)) अणु
		काष्ठा drbd_md *md = &device->ldev->md;
		u64 *history_uuids = (u64 *)s->history_uuids;
		पूर्णांक n;

		spin_lock_irq(&md->uuid_lock);
		s->dev_current_uuid = md->uuid[UI_CURRENT];
		BUILD_BUG_ON(माप(s->history_uuids) < UI_HISTORY_END - UI_HISTORY_START + 1);
		क्रम (n = 0; n < UI_HISTORY_END - UI_HISTORY_START + 1; n++)
			history_uuids[n] = md->uuid[UI_HISTORY_START + n];
		क्रम (; n < HISTORY_UUIDS; n++)
			history_uuids[n] = 0;
		s->history_uuids_len = HISTORY_UUIDS;
		spin_unlock_irq(&md->uuid_lock);

		s->dev_disk_flags = md->flags;
		put_ldev(device);
	पूर्ण
	s->dev_size = get_capacity(device->vdisk);
	s->dev_पढ़ो = device->पढ़ो_cnt;
	s->dev_ग_लिखो = device->writ_cnt;
	s->dev_al_ग_लिखोs = device->al_writ_cnt;
	s->dev_bm_ग_लिखोs = device->bm_writ_cnt;
	s->dev_upper_pending = atomic_पढ़ो(&device->ap_bio_cnt);
	s->dev_lower_pending = atomic_पढ़ो(&device->local_cnt);
	s->dev_al_suspended = test_bit(AL_SUSPENDED, &device->flags);
	s->dev_exposed_data_uuid = device->ed_uuid;
पूर्ण

अटल पूर्णांक put_resource_in_arg0(काष्ठा netlink_callback *cb, पूर्णांक holder_nr)
अणु
	अगर (cb->args[0]) अणु
		काष्ठा drbd_resource *resource =
			(काष्ठा drbd_resource *)cb->args[0];
		kref_put(&resource->kref, drbd_destroy_resource);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक drbd_adm_dump_devices_करोne(काष्ठा netlink_callback *cb) अणु
	वापस put_resource_in_arg0(cb, 7);
पूर्ण

अटल व्योम device_to_info(काष्ठा device_info *, काष्ठा drbd_device *);

पूर्णांक drbd_adm_dump_devices(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा nlattr *resource_filter;
	काष्ठा drbd_resource *resource;
	काष्ठा drbd_device *device;
	पूर्णांक minor, err, retcode;
	काष्ठा drbd_genlmsghdr *dh;
	काष्ठा device_info device_info;
	काष्ठा device_statistics device_statistics;
	काष्ठा idr *idr_to_search;

	resource = (काष्ठा drbd_resource *)cb->args[0];
	अगर (!cb->args[0] && !cb->args[1]) अणु
		resource_filter = find_cfg_context_attr(cb->nlh, T_ctx_resource_name);
		अगर (resource_filter) अणु
			retcode = ERR_RES_NOT_KNOWN;
			resource = drbd_find_resource(nla_data(resource_filter));
			अगर (!resource)
				जाओ put_result;
			cb->args[0] = (दीर्घ)resource;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_lock();
	minor = cb->args[1];
	idr_to_search = resource ? &resource->devices : &drbd_devices;
	device = idr_get_next(idr_to_search, &minor);
	अगर (!device) अणु
		err = 0;
		जाओ out;
	पूर्ण
	idr_क्रम_each_entry_जारी(idr_to_search, device, minor) अणु
		retcode = NO_ERROR;
		जाओ put_result;  /* only one iteration */
	पूर्ण
	err = 0;
	जाओ out;  /* no more devices */

put_result:
	dh = genlmsg_put(skb, NETLINK_CB(cb->skb).portid,
			cb->nlh->nlmsg_seq, &drbd_genl_family,
			NLM_F_MULTI, DRBD_ADM_GET_DEVICES);
	err = -ENOMEM;
	अगर (!dh)
		जाओ out;
	dh->ret_code = retcode;
	dh->minor = -1U;
	अगर (retcode == NO_ERROR) अणु
		dh->minor = device->minor;
		err = nla_put_drbd_cfg_context(skb, device->resource, शून्य, device);
		अगर (err)
			जाओ out;
		अगर (get_ldev(device)) अणु
			काष्ठा disk_conf *disk_conf =
				rcu_dereference(device->ldev->disk_conf);

			err = disk_conf_to_skb(skb, disk_conf, !capable(CAP_SYS_ADMIN));
			put_ldev(device);
			अगर (err)
				जाओ out;
		पूर्ण
		device_to_info(&device_info, device);
		err = device_info_to_skb(skb, &device_info, !capable(CAP_SYS_ADMIN));
		अगर (err)
			जाओ out;

		device_to_statistics(&device_statistics, device);
		err = device_statistics_to_skb(skb, &device_statistics, !capable(CAP_SYS_ADMIN));
		अगर (err)
			जाओ out;
		cb->args[1] = minor + 1;
	पूर्ण
	genlmsg_end(skb, dh);
	err = 0;

out:
	rcu_पढ़ो_unlock();
	अगर (err)
		वापस err;
	वापस skb->len;
पूर्ण

पूर्णांक drbd_adm_dump_connections_करोne(काष्ठा netlink_callback *cb)
अणु
	वापस put_resource_in_arg0(cb, 6);
पूर्ण

क्रमागत अणु SINGLE_RESOURCE, ITERATE_RESOURCES पूर्ण;

पूर्णांक drbd_adm_dump_connections(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा nlattr *resource_filter;
	काष्ठा drbd_resource *resource = शून्य, *next_resource;
	काष्ठा drbd_connection *connection;
	पूर्णांक err = 0, retcode;
	काष्ठा drbd_genlmsghdr *dh;
	काष्ठा connection_info connection_info;
	काष्ठा connection_statistics connection_statistics;

	rcu_पढ़ो_lock();
	resource = (काष्ठा drbd_resource *)cb->args[0];
	अगर (!cb->args[0]) अणु
		resource_filter = find_cfg_context_attr(cb->nlh, T_ctx_resource_name);
		अगर (resource_filter) अणु
			retcode = ERR_RES_NOT_KNOWN;
			resource = drbd_find_resource(nla_data(resource_filter));
			अगर (!resource)
				जाओ put_result;
			cb->args[0] = (दीर्घ)resource;
			cb->args[1] = SINGLE_RESOURCE;
		पूर्ण
	पूर्ण
	अगर (!resource) अणु
		अगर (list_empty(&drbd_resources))
			जाओ out;
		resource = list_first_entry(&drbd_resources, काष्ठा drbd_resource, resources);
		kref_get(&resource->kref);
		cb->args[0] = (दीर्घ)resource;
		cb->args[1] = ITERATE_RESOURCES;
	पूर्ण

    next_resource:
	rcu_पढ़ो_unlock();
	mutex_lock(&resource->conf_update);
	rcu_पढ़ो_lock();
	अगर (cb->args[2]) अणु
		क्रम_each_connection_rcu(connection, resource)
			अगर (connection == (काष्ठा drbd_connection *)cb->args[2])
				जाओ found_connection;
		/* connection was probably deleted */
		जाओ no_more_connections;
	पूर्ण
	connection = list_entry(&resource->connections, काष्ठा drbd_connection, connections);

found_connection:
	list_क्रम_each_entry_जारी_rcu(connection, &resource->connections, connections) अणु
		अगर (!has_net_conf(connection))
			जारी;
		retcode = NO_ERROR;
		जाओ put_result;  /* only one iteration */
	पूर्ण

no_more_connections:
	अगर (cb->args[1] == ITERATE_RESOURCES) अणु
		क्रम_each_resource_rcu(next_resource, &drbd_resources) अणु
			अगर (next_resource == resource)
				जाओ found_resource;
		पूर्ण
		/* resource was probably deleted */
	पूर्ण
	जाओ out;

found_resource:
	list_क्रम_each_entry_जारी_rcu(next_resource, &drbd_resources, resources) अणु
		mutex_unlock(&resource->conf_update);
		kref_put(&resource->kref, drbd_destroy_resource);
		resource = next_resource;
		kref_get(&resource->kref);
		cb->args[0] = (दीर्घ)resource;
		cb->args[2] = 0;
		जाओ next_resource;
	पूर्ण
	जाओ out;  /* no more resources */

put_result:
	dh = genlmsg_put(skb, NETLINK_CB(cb->skb).portid,
			cb->nlh->nlmsg_seq, &drbd_genl_family,
			NLM_F_MULTI, DRBD_ADM_GET_CONNECTIONS);
	err = -ENOMEM;
	अगर (!dh)
		जाओ out;
	dh->ret_code = retcode;
	dh->minor = -1U;
	अगर (retcode == NO_ERROR) अणु
		काष्ठा net_conf *net_conf;

		err = nla_put_drbd_cfg_context(skb, resource, connection, शून्य);
		अगर (err)
			जाओ out;
		net_conf = rcu_dereference(connection->net_conf);
		अगर (net_conf) अणु
			err = net_conf_to_skb(skb, net_conf, !capable(CAP_SYS_ADMIN));
			अगर (err)
				जाओ out;
		पूर्ण
		connection_to_info(&connection_info, connection);
		err = connection_info_to_skb(skb, &connection_info, !capable(CAP_SYS_ADMIN));
		अगर (err)
			जाओ out;
		connection_statistics.conn_congested = test_bit(NET_CONGESTED, &connection->flags);
		err = connection_statistics_to_skb(skb, &connection_statistics, !capable(CAP_SYS_ADMIN));
		अगर (err)
			जाओ out;
		cb->args[2] = (दीर्घ)connection;
	पूर्ण
	genlmsg_end(skb, dh);
	err = 0;

out:
	rcu_पढ़ो_unlock();
	अगर (resource)
		mutex_unlock(&resource->conf_update);
	अगर (err)
		वापस err;
	वापस skb->len;
पूर्ण

क्रमागत mdf_peer_flag अणु
	MDF_PEER_CONNECTED =	1 << 0,
	MDF_PEER_OUTDATED =	1 << 1,
	MDF_PEER_FENCING =	1 << 2,
	MDF_PEER_FULL_SYNC =	1 << 3,
पूर्ण;

अटल व्योम peer_device_to_statistics(काष्ठा peer_device_statistics *s,
				      काष्ठा drbd_peer_device *peer_device)
अणु
	काष्ठा drbd_device *device = peer_device->device;

	स_रखो(s, 0, माप(*s));
	s->peer_dev_received = device->recv_cnt;
	s->peer_dev_sent = device->send_cnt;
	s->peer_dev_pending = atomic_पढ़ो(&device->ap_pending_cnt) +
			      atomic_पढ़ो(&device->rs_pending_cnt);
	s->peer_dev_unacked = atomic_पढ़ो(&device->unacked_cnt);
	s->peer_dev_out_of_sync = drbd_bm_total_weight(device) << (BM_BLOCK_SHIFT - 9);
	s->peer_dev_resync_failed = device->rs_failed << (BM_BLOCK_SHIFT - 9);
	अगर (get_ldev(device)) अणु
		काष्ठा drbd_md *md = &device->ldev->md;

		spin_lock_irq(&md->uuid_lock);
		s->peer_dev_biपंचांगap_uuid = md->uuid[UI_BITMAP];
		spin_unlock_irq(&md->uuid_lock);
		s->peer_dev_flags =
			(drbd_md_test_flag(device->ldev, MDF_CONNECTED_IND) ?
				MDF_PEER_CONNECTED : 0) +
			(drbd_md_test_flag(device->ldev, MDF_CONSISTENT) &&
			 !drbd_md_test_flag(device->ldev, MDF_WAS_UP_TO_DATE) ?
				MDF_PEER_OUTDATED : 0) +
			/* FIXME: MDF_PEER_FENCING? */
			(drbd_md_test_flag(device->ldev, MDF_FULL_SYNC) ?
				MDF_PEER_FULL_SYNC : 0);
		put_ldev(device);
	पूर्ण
पूर्ण

पूर्णांक drbd_adm_dump_peer_devices_करोne(काष्ठा netlink_callback *cb)
अणु
	वापस put_resource_in_arg0(cb, 9);
पूर्ण

पूर्णांक drbd_adm_dump_peer_devices(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा nlattr *resource_filter;
	काष्ठा drbd_resource *resource;
	काष्ठा drbd_device *device;
	काष्ठा drbd_peer_device *peer_device = शून्य;
	पूर्णांक minor, err, retcode;
	काष्ठा drbd_genlmsghdr *dh;
	काष्ठा idr *idr_to_search;

	resource = (काष्ठा drbd_resource *)cb->args[0];
	अगर (!cb->args[0] && !cb->args[1]) अणु
		resource_filter = find_cfg_context_attr(cb->nlh, T_ctx_resource_name);
		अगर (resource_filter) अणु
			retcode = ERR_RES_NOT_KNOWN;
			resource = drbd_find_resource(nla_data(resource_filter));
			अगर (!resource)
				जाओ put_result;
		पूर्ण
		cb->args[0] = (दीर्घ)resource;
	पूर्ण

	rcu_पढ़ो_lock();
	minor = cb->args[1];
	idr_to_search = resource ? &resource->devices : &drbd_devices;
	device = idr_find(idr_to_search, minor);
	अगर (!device) अणु
next_device:
		minor++;
		cb->args[2] = 0;
		device = idr_get_next(idr_to_search, &minor);
		अगर (!device) अणु
			err = 0;
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (cb->args[2]) अणु
		क्रम_each_peer_device(peer_device, device)
			अगर (peer_device == (काष्ठा drbd_peer_device *)cb->args[2])
				जाओ found_peer_device;
		/* peer device was probably deleted */
		जाओ next_device;
	पूर्ण
	/* Make peer_device poपूर्णांक to the list head (not the first entry). */
	peer_device = list_entry(&device->peer_devices, काष्ठा drbd_peer_device, peer_devices);

found_peer_device:
	list_क्रम_each_entry_जारी_rcu(peer_device, &device->peer_devices, peer_devices) अणु
		अगर (!has_net_conf(peer_device->connection))
			जारी;
		retcode = NO_ERROR;
		जाओ put_result;  /* only one iteration */
	पूर्ण
	जाओ next_device;

put_result:
	dh = genlmsg_put(skb, NETLINK_CB(cb->skb).portid,
			cb->nlh->nlmsg_seq, &drbd_genl_family,
			NLM_F_MULTI, DRBD_ADM_GET_PEER_DEVICES);
	err = -ENOMEM;
	अगर (!dh)
		जाओ out;
	dh->ret_code = retcode;
	dh->minor = -1U;
	अगर (retcode == NO_ERROR) अणु
		काष्ठा peer_device_info peer_device_info;
		काष्ठा peer_device_statistics peer_device_statistics;

		dh->minor = minor;
		err = nla_put_drbd_cfg_context(skb, device->resource, peer_device->connection, device);
		अगर (err)
			जाओ out;
		peer_device_to_info(&peer_device_info, peer_device);
		err = peer_device_info_to_skb(skb, &peer_device_info, !capable(CAP_SYS_ADMIN));
		अगर (err)
			जाओ out;
		peer_device_to_statistics(&peer_device_statistics, peer_device);
		err = peer_device_statistics_to_skb(skb, &peer_device_statistics, !capable(CAP_SYS_ADMIN));
		अगर (err)
			जाओ out;
		cb->args[1] = minor;
		cb->args[2] = (दीर्घ)peer_device;
	पूर्ण
	genlmsg_end(skb, dh);
	err = 0;

out:
	rcu_पढ़ो_unlock();
	अगर (err)
		वापस err;
	वापस skb->len;
पूर्ण
/*
 * Return the connection of @resource अगर @resource has exactly one connection.
 */
अटल काष्ठा drbd_connection *the_only_connection(काष्ठा drbd_resource *resource)
अणु
	काष्ठा list_head *connections = &resource->connections;

	अगर (list_empty(connections) || connections->next->next != connections)
		वापस शून्य;
	वापस list_first_entry(&resource->connections, काष्ठा drbd_connection, connections);
पूर्ण

अटल पूर्णांक nla_put_status_info(काष्ठा sk_buff *skb, काष्ठा drbd_device *device,
		स्थिर काष्ठा sib_info *sib)
अणु
	काष्ठा drbd_resource *resource = device->resource;
	काष्ठा state_info *si = शून्य; /* क्रम माप(si->member); */
	काष्ठा nlattr *nla;
	पूर्णांक got_ldev;
	पूर्णांक err = 0;
	पूर्णांक exclude_sensitive;

	/* If sib != शून्य, this is drbd_bcast_event, which anyone can listen
	 * to.  So we better exclude_sensitive inक्रमmation.
	 *
	 * If sib == शून्य, this is drbd_adm_get_status, executed synchronously
	 * in the context of the requesting user process. Exclude sensitive
	 * inक्रमmation, unless current has superuser.
	 *
	 * NOTE: क्रम drbd_adm_get_status_all(), this is a netlink dump, and
	 * relies on the current implementation of netlink_dump(), which
	 * executes the dump callback successively from netlink_recvmsg(),
	 * always in the context of the receiving process */
	exclude_sensitive = sib || !capable(CAP_SYS_ADMIN);

	got_ldev = get_ldev(device);

	/* We need to add connection name and volume number inक्रमmation still.
	 * Minor number is in drbd_genlmsghdr. */
	अगर (nla_put_drbd_cfg_context(skb, resource, the_only_connection(resource), device))
		जाओ nla_put_failure;

	अगर (res_opts_to_skb(skb, &device->resource->res_opts, exclude_sensitive))
		जाओ nla_put_failure;

	rcu_पढ़ो_lock();
	अगर (got_ldev) अणु
		काष्ठा disk_conf *disk_conf;

		disk_conf = rcu_dereference(device->ldev->disk_conf);
		err = disk_conf_to_skb(skb, disk_conf, exclude_sensitive);
	पूर्ण
	अगर (!err) अणु
		काष्ठा net_conf *nc;

		nc = rcu_dereference(first_peer_device(device)->connection->net_conf);
		अगर (nc)
			err = net_conf_to_skb(skb, nc, exclude_sensitive);
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (err)
		जाओ nla_put_failure;

	nla = nla_nest_start_noflag(skb, DRBD_NLA_STATE_INFO);
	अगर (!nla)
		जाओ nla_put_failure;
	अगर (nla_put_u32(skb, T_sib_reason, sib ? sib->sib_reason : SIB_GET_STATUS_REPLY) ||
	    nla_put_u32(skb, T_current_state, device->state.i) ||
	    nla_put_u64_0pad(skb, T_ed_uuid, device->ed_uuid) ||
	    nla_put_u64_0pad(skb, T_capacity, get_capacity(device->vdisk)) ||
	    nla_put_u64_0pad(skb, T_send_cnt, device->send_cnt) ||
	    nla_put_u64_0pad(skb, T_recv_cnt, device->recv_cnt) ||
	    nla_put_u64_0pad(skb, T_पढ़ो_cnt, device->पढ़ो_cnt) ||
	    nla_put_u64_0pad(skb, T_writ_cnt, device->writ_cnt) ||
	    nla_put_u64_0pad(skb, T_al_writ_cnt, device->al_writ_cnt) ||
	    nla_put_u64_0pad(skb, T_bm_writ_cnt, device->bm_writ_cnt) ||
	    nla_put_u32(skb, T_ap_bio_cnt, atomic_पढ़ो(&device->ap_bio_cnt)) ||
	    nla_put_u32(skb, T_ap_pending_cnt, atomic_पढ़ो(&device->ap_pending_cnt)) ||
	    nla_put_u32(skb, T_rs_pending_cnt, atomic_पढ़ो(&device->rs_pending_cnt)))
		जाओ nla_put_failure;

	अगर (got_ldev) अणु
		पूर्णांक err;

		spin_lock_irq(&device->ldev->md.uuid_lock);
		err = nla_put(skb, T_uuids, माप(si->uuids), device->ldev->md.uuid);
		spin_unlock_irq(&device->ldev->md.uuid_lock);

		अगर (err)
			जाओ nla_put_failure;

		अगर (nla_put_u32(skb, T_disk_flags, device->ldev->md.flags) ||
		    nla_put_u64_0pad(skb, T_bits_total, drbd_bm_bits(device)) ||
		    nla_put_u64_0pad(skb, T_bits_oos,
				     drbd_bm_total_weight(device)))
			जाओ nla_put_failure;
		अगर (C_SYNC_SOURCE <= device->state.conn &&
		    C_PAUSED_SYNC_T >= device->state.conn) अणु
			अगर (nla_put_u64_0pad(skb, T_bits_rs_total,
					     device->rs_total) ||
			    nla_put_u64_0pad(skb, T_bits_rs_failed,
					     device->rs_failed))
				जाओ nla_put_failure;
		पूर्ण
	पूर्ण

	अगर (sib) अणु
		चयन(sib->sib_reason) अणु
		हाल SIB_SYNC_PROGRESS:
		हाल SIB_GET_STATUS_REPLY:
			अवरोध;
		हाल SIB_STATE_CHANGE:
			अगर (nla_put_u32(skb, T_prev_state, sib->os.i) ||
			    nla_put_u32(skb, T_new_state, sib->ns.i))
				जाओ nla_put_failure;
			अवरोध;
		हाल SIB_HELPER_POST:
			अगर (nla_put_u32(skb, T_helper_निकास_code,
					sib->helper_निकास_code))
				जाओ nla_put_failure;
			fallthrough;
		हाल SIB_HELPER_PRE:
			अगर (nla_put_string(skb, T_helper, sib->helper_name))
				जाओ nla_put_failure;
			अवरोध;
		पूर्ण
	पूर्ण
	nla_nest_end(skb, nla);

	अगर (0)
nla_put_failure:
		err = -EMSGSIZE;
	अगर (got_ldev)
		put_ldev(device);
	वापस err;
पूर्ण

पूर्णांक drbd_adm_get_status(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा drbd_config_context adm_ctx;
	क्रमागत drbd_ret_code retcode;
	पूर्णांक err;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_MINOR);
	अगर (!adm_ctx.reply_skb)
		वापस retcode;
	अगर (retcode != NO_ERROR)
		जाओ out;

	err = nla_put_status_info(adm_ctx.reply_skb, adm_ctx.device, शून्य);
	अगर (err) अणु
		nlmsg_मुक्त(adm_ctx.reply_skb);
		वापस err;
	पूर्ण
out:
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;
पूर्ण

अटल पूर्णांक get_one_status(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा drbd_device *device;
	काष्ठा drbd_genlmsghdr *dh;
	काष्ठा drbd_resource *pos = (काष्ठा drbd_resource *)cb->args[0];
	काष्ठा drbd_resource *resource = शून्य;
	काष्ठा drbd_resource *पंचांगp;
	अचिन्हित volume = cb->args[1];

	/* Open coded, deferred, iteration:
	 * क्रम_each_resource_safe(resource, पंचांगp, &drbd_resources) अणु
	 *      connection = "first connection of resource or undefined";
	 *	idr_क्रम_each_entry(&resource->devices, device, i) अणु
	 *	  ...
	 *	पूर्ण
	 * पूर्ण
	 * where resource is cb->args[0];
	 * and i is cb->args[1];
	 *
	 * cb->args[2] indicates अगर we shall loop over all resources,
	 * or just dump all volumes of a single resource.
	 *
	 * This may miss entries inserted after this dump started,
	 * or entries deleted beक्रमe they are reached.
	 *
	 * We need to make sure the device won't disappear जबतक
	 * we are looking at it, and revalidate our iterators
	 * on each iteration.
	 */

	/* synchronize with conn_create()/drbd_destroy_connection() */
	rcu_पढ़ो_lock();
	/* revalidate iterator position */
	क्रम_each_resource_rcu(पंचांगp, &drbd_resources) अणु
		अगर (pos == शून्य) अणु
			/* first iteration */
			pos = पंचांगp;
			resource = pos;
			अवरोध;
		पूर्ण
		अगर (पंचांगp == pos) अणु
			resource = pos;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (resource) अणु
next_resource:
		device = idr_get_next(&resource->devices, &volume);
		अगर (!device) अणु
			/* No more volumes to dump on this resource.
			 * Advance resource iterator. */
			pos = list_entry_rcu(resource->resources.next,
					     काष्ठा drbd_resource, resources);
			/* Did we dump any volume of this resource yet? */
			अगर (volume != 0) अणु
				/* If we reached the end of the list,
				 * or only a single resource dump was requested,
				 * we are करोne. */
				अगर (&pos->resources == &drbd_resources || cb->args[2])
					जाओ out;
				volume = 0;
				resource = pos;
				जाओ next_resource;
			पूर्ण
		पूर्ण

		dh = genlmsg_put(skb, NETLINK_CB(cb->skb).portid,
				cb->nlh->nlmsg_seq, &drbd_genl_family,
				NLM_F_MULTI, DRBD_ADM_GET_STATUS);
		अगर (!dh)
			जाओ out;

		अगर (!device) अणु
			/* This is a connection without a single volume.
			 * Suprisingly enough, it may have a network
			 * configuration. */
			काष्ठा drbd_connection *connection;

			dh->minor = -1U;
			dh->ret_code = NO_ERROR;
			connection = the_only_connection(resource);
			अगर (nla_put_drbd_cfg_context(skb, resource, connection, शून्य))
				जाओ cancel;
			अगर (connection) अणु
				काष्ठा net_conf *nc;

				nc = rcu_dereference(connection->net_conf);
				अगर (nc && net_conf_to_skb(skb, nc, 1) != 0)
					जाओ cancel;
			पूर्ण
			जाओ करोne;
		पूर्ण

		D_ASSERT(device, device->vnr == volume);
		D_ASSERT(device, device->resource == resource);

		dh->minor = device_to_minor(device);
		dh->ret_code = NO_ERROR;

		अगर (nla_put_status_info(skb, device, शून्य)) अणु
cancel:
			genlmsg_cancel(skb, dh);
			जाओ out;
		पूर्ण
करोne:
		genlmsg_end(skb, dh);
	पूर्ण

out:
	rcu_पढ़ो_unlock();
	/* where to start the next iteration */
	cb->args[0] = (दीर्घ)pos;
	cb->args[1] = (pos == resource) ? volume + 1 : 0;

	/* No more resources/volumes/minors found results in an empty skb.
	 * Which will terminate the dump. */
        वापस skb->len;
पूर्ण

/*
 * Request status of all resources, or of all volumes within a single resource.
 *
 * This is a dump, as the answer may not fit in a single reply skb otherwise.
 * Which means we cannot use the family->attrbuf or other such members, because
 * dump is NOT रक्षित by the genl_lock().  During dump, we only have access
 * to the incoming skb, and need to खोलोcode "parsing" of the nlattr payload.
 *
 * Once things are setup properly, we call पूर्णांकo get_one_status().
 */
पूर्णांक drbd_adm_get_status_all(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	स्थिर अचिन्हित hdrlen = GENL_HDRLEN + GENL_MAGIC_FAMILY_HDRSZ;
	काष्ठा nlattr *nla;
	स्थिर अक्षर *resource_name;
	काष्ठा drbd_resource *resource;
	पूर्णांक maxtype;

	/* Is this a followup call? */
	अगर (cb->args[0]) अणु
		/* ... of a single resource dump,
		 * and the resource iterator has been advanced alपढ़ोy? */
		अगर (cb->args[2] && cb->args[2] != cb->args[0])
			वापस 0; /* DONE. */
		जाओ dump;
	पूर्ण

	/* First call (from netlink_dump_start).  We need to figure out
	 * which resource(s) the user wants us to dump. */
	nla = nla_find(nlmsg_attrdata(cb->nlh, hdrlen),
			nlmsg_attrlen(cb->nlh, hdrlen),
			DRBD_NLA_CFG_CONTEXT);

	/* No explicit context given.  Dump all. */
	अगर (!nla)
		जाओ dump;
	maxtype = ARRAY_SIZE(drbd_cfg_context_nl_policy) - 1;
	nla = drbd_nla_find_nested(maxtype, nla, __nla_type(T_ctx_resource_name));
	अगर (IS_ERR(nla))
		वापस PTR_ERR(nla);
	/* context given, but no name present? */
	अगर (!nla)
		वापस -EINVAL;
	resource_name = nla_data(nla);
	अगर (!*resource_name)
		वापस -ENODEV;
	resource = drbd_find_resource(resource_name);
	अगर (!resource)
		वापस -ENODEV;

	kref_put(&resource->kref, drbd_destroy_resource); /* get_one_status() revalidates the resource */

	/* prime iterators, and set "filter" mode mark:
	 * only dump this connection. */
	cb->args[0] = (दीर्घ)resource;
	/* cb->args[1] = 0; passed in this way. */
	cb->args[2] = (दीर्घ)resource;

dump:
	वापस get_one_status(skb, cb);
पूर्ण

पूर्णांक drbd_adm_get_समयout_type(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा drbd_config_context adm_ctx;
	क्रमागत drbd_ret_code retcode;
	काष्ठा समयout_parms tp;
	पूर्णांक err;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_MINOR);
	अगर (!adm_ctx.reply_skb)
		वापस retcode;
	अगर (retcode != NO_ERROR)
		जाओ out;

	tp.समयout_type =
		adm_ctx.device->state.pdsk == D_OUTDATED ? UT_PEER_OUTDATED :
		test_bit(USE_DEGR_WFC_T, &adm_ctx.device->flags) ? UT_DEGRADED :
		UT_DEFAULT;

	err = समयout_parms_to_priv_skb(adm_ctx.reply_skb, &tp);
	अगर (err) अणु
		nlmsg_मुक्त(adm_ctx.reply_skb);
		वापस err;
	पूर्ण
out:
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;
पूर्ण

पूर्णांक drbd_adm_start_ov(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा drbd_config_context adm_ctx;
	काष्ठा drbd_device *device;
	क्रमागत drbd_ret_code retcode;
	काष्ठा start_ov_parms parms;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_MINOR);
	अगर (!adm_ctx.reply_skb)
		वापस retcode;
	अगर (retcode != NO_ERROR)
		जाओ out;

	device = adm_ctx.device;

	/* resume from last known position, अगर possible */
	parms.ov_start_sector = device->ov_start_sector;
	parms.ov_stop_sector = ULदीर्घ_उच्च;
	अगर (info->attrs[DRBD_NLA_START_OV_PARMS]) अणु
		पूर्णांक err = start_ov_parms_from_attrs(&parms, info);
		अगर (err) अणु
			retcode = ERR_MANDATORY_TAG;
			drbd_msg_put_info(adm_ctx.reply_skb, from_attrs_err_to_txt(err));
			जाओ out;
		पूर्ण
	पूर्ण
	mutex_lock(&adm_ctx.resource->adm_mutex);

	/* w_make_ov_request expects position to be aligned */
	device->ov_start_sector = parms.ov_start_sector & ~(BM_SECT_PER_BIT-1);
	device->ov_stop_sector = parms.ov_stop_sector;

	/* If there is still biपंचांगap IO pending, e.g. previous resync or verअगरy
	 * just being finished, रुको क्रम it beक्रमe requesting a new resync. */
	drbd_suspend_io(device);
	रुको_event(device->misc_रुको, !test_bit(BITMAP_IO, &device->flags));
	retcode = drbd_request_state(device, NS(conn, C_VERIFY_S));
	drbd_resume_io(device);

	mutex_unlock(&adm_ctx.resource->adm_mutex);
out:
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;
पूर्ण


पूर्णांक drbd_adm_new_c_uuid(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा drbd_config_context adm_ctx;
	काष्ठा drbd_device *device;
	क्रमागत drbd_ret_code retcode;
	पूर्णांक skip_initial_sync = 0;
	पूर्णांक err;
	काष्ठा new_c_uuid_parms args;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_MINOR);
	अगर (!adm_ctx.reply_skb)
		वापस retcode;
	अगर (retcode != NO_ERROR)
		जाओ out_nolock;

	device = adm_ctx.device;
	स_रखो(&args, 0, माप(args));
	अगर (info->attrs[DRBD_NLA_NEW_C_UUID_PARMS]) अणु
		err = new_c_uuid_parms_from_attrs(&args, info);
		अगर (err) अणु
			retcode = ERR_MANDATORY_TAG;
			drbd_msg_put_info(adm_ctx.reply_skb, from_attrs_err_to_txt(err));
			जाओ out_nolock;
		पूर्ण
	पूर्ण

	mutex_lock(&adm_ctx.resource->adm_mutex);
	mutex_lock(device->state_mutex); /* Protects us against serialized state changes. */

	अगर (!get_ldev(device)) अणु
		retcode = ERR_NO_DISK;
		जाओ out;
	पूर्ण

	/* this is "skip initial sync", assume to be clean */
	अगर (device->state.conn == C_CONNECTED &&
	    first_peer_device(device)->connection->agreed_pro_version >= 90 &&
	    device->ldev->md.uuid[UI_CURRENT] == UUID_JUST_CREATED && args.clear_bm) अणु
		drbd_info(device, "Preparing to skip initial sync\n");
		skip_initial_sync = 1;
	पूर्ण अन्यथा अगर (device->state.conn != C_STANDALONE) अणु
		retcode = ERR_CONNECTED;
		जाओ out_dec;
	पूर्ण

	drbd_uuid_set(device, UI_BITMAP, 0); /* Rotate UI_BITMAP to History 1, etc... */
	drbd_uuid_new_current(device); /* New current, previous to UI_BITMAP */

	अगर (args.clear_bm) अणु
		err = drbd_biपंचांगap_io(device, &drbd_bmio_clear_n_ग_लिखो,
			"clear_n_write from new_c_uuid", BM_LOCKED_MASK);
		अगर (err) अणु
			drbd_err(device, "Writing bitmap failed with %d\n", err);
			retcode = ERR_IO_MD_DISK;
		पूर्ण
		अगर (skip_initial_sync) अणु
			drbd_send_uuids_skip_initial_sync(first_peer_device(device));
			_drbd_uuid_set(device, UI_BITMAP, 0);
			drbd_prपूर्णांक_uuids(device, "cleared bitmap UUID");
			spin_lock_irq(&device->resource->req_lock);
			_drbd_set_state(_NS2(device, disk, D_UP_TO_DATE, pdsk, D_UP_TO_DATE),
					CS_VERBOSE, शून्य);
			spin_unlock_irq(&device->resource->req_lock);
		पूर्ण
	पूर्ण

	drbd_md_sync(device);
out_dec:
	put_ldev(device);
out:
	mutex_unlock(device->state_mutex);
	mutex_unlock(&adm_ctx.resource->adm_mutex);
out_nolock:
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;
पूर्ण

अटल क्रमागत drbd_ret_code
drbd_check_resource_name(काष्ठा drbd_config_context *adm_ctx)
अणु
	स्थिर अक्षर *name = adm_ctx->resource_name;
	अगर (!name || !name[0]) अणु
		drbd_msg_put_info(adm_ctx->reply_skb, "resource name missing");
		वापस ERR_MANDATORY_TAG;
	पूर्ण
	/* अगर we want to use these in sysfs/configfs/debugfs some day,
	 * we must not allow slashes */
	अगर (म_अक्षर(name, '/')) अणु
		drbd_msg_put_info(adm_ctx->reply_skb, "invalid resource name");
		वापस ERR_INVALID_REQUEST;
	पूर्ण
	वापस NO_ERROR;
पूर्ण

अटल व्योम resource_to_info(काष्ठा resource_info *info,
			     काष्ठा drbd_resource *resource)
अणु
	info->res_role = conn_highest_role(first_connection(resource));
	info->res_susp = resource->susp;
	info->res_susp_nod = resource->susp_nod;
	info->res_susp_fen = resource->susp_fen;
पूर्ण

पूर्णांक drbd_adm_new_resource(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा drbd_connection *connection;
	काष्ठा drbd_config_context adm_ctx;
	क्रमागत drbd_ret_code retcode;
	काष्ठा res_opts res_opts;
	पूर्णांक err;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, 0);
	अगर (!adm_ctx.reply_skb)
		वापस retcode;
	अगर (retcode != NO_ERROR)
		जाओ out;

	set_res_opts_शेषs(&res_opts);
	err = res_opts_from_attrs(&res_opts, info);
	अगर (err && err != -ENOMSG) अणु
		retcode = ERR_MANDATORY_TAG;
		drbd_msg_put_info(adm_ctx.reply_skb, from_attrs_err_to_txt(err));
		जाओ out;
	पूर्ण

	retcode = drbd_check_resource_name(&adm_ctx);
	अगर (retcode != NO_ERROR)
		जाओ out;

	अगर (adm_ctx.resource) अणु
		अगर (info->nlhdr->nlmsg_flags & NLM_F_EXCL) अणु
			retcode = ERR_INVALID_REQUEST;
			drbd_msg_put_info(adm_ctx.reply_skb, "resource exists");
		पूर्ण
		/* अन्यथा: still NO_ERROR */
		जाओ out;
	पूर्ण

	/* not yet safe क्रम genl_family.parallel_ops */
	mutex_lock(&resources_mutex);
	connection = conn_create(adm_ctx.resource_name, &res_opts);
	mutex_unlock(&resources_mutex);

	अगर (connection) अणु
		काष्ठा resource_info resource_info;

		mutex_lock(&notअगरication_mutex);
		resource_to_info(&resource_info, connection->resource);
		notअगरy_resource_state(शून्य, 0, connection->resource,
				      &resource_info, NOTIFY_CREATE);
		mutex_unlock(&notअगरication_mutex);
	पूर्ण अन्यथा
		retcode = ERR_NOMEM;

out:
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;
पूर्ण

अटल व्योम device_to_info(काष्ठा device_info *info,
			   काष्ठा drbd_device *device)
अणु
	info->dev_disk_state = device->state.disk;
पूर्ण


पूर्णांक drbd_adm_new_minor(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा drbd_config_context adm_ctx;
	काष्ठा drbd_genlmsghdr *dh = info->userhdr;
	क्रमागत drbd_ret_code retcode;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_RESOURCE);
	अगर (!adm_ctx.reply_skb)
		वापस retcode;
	अगर (retcode != NO_ERROR)
		जाओ out;

	अगर (dh->minor > MINORMASK) अणु
		drbd_msg_put_info(adm_ctx.reply_skb, "requested minor out of range");
		retcode = ERR_INVALID_REQUEST;
		जाओ out;
	पूर्ण
	अगर (adm_ctx.volume > DRBD_VOLUME_MAX) अणु
		drbd_msg_put_info(adm_ctx.reply_skb, "requested volume id out of range");
		retcode = ERR_INVALID_REQUEST;
		जाओ out;
	पूर्ण

	/* drbd_adm_prepare made sure alपढ़ोy
	 * that first_peer_device(device)->connection and device->vnr match the request. */
	अगर (adm_ctx.device) अणु
		अगर (info->nlhdr->nlmsg_flags & NLM_F_EXCL)
			retcode = ERR_MINOR_OR_VOLUME_EXISTS;
		/* अन्यथा: still NO_ERROR */
		जाओ out;
	पूर्ण

	mutex_lock(&adm_ctx.resource->adm_mutex);
	retcode = drbd_create_device(&adm_ctx, dh->minor);
	अगर (retcode == NO_ERROR) अणु
		काष्ठा drbd_device *device;
		काष्ठा drbd_peer_device *peer_device;
		काष्ठा device_info info;
		अचिन्हित पूर्णांक peer_devices = 0;
		क्रमागत drbd_notअगरication_type flags;

		device = minor_to_device(dh->minor);
		क्रम_each_peer_device(peer_device, device) अणु
			अगर (!has_net_conf(peer_device->connection))
				जारी;
			peer_devices++;
		पूर्ण

		device_to_info(&info, device);
		mutex_lock(&notअगरication_mutex);
		flags = (peer_devices--) ? NOTIFY_CONTINUES : 0;
		notअगरy_device_state(शून्य, 0, device, &info, NOTIFY_CREATE | flags);
		क्रम_each_peer_device(peer_device, device) अणु
			काष्ठा peer_device_info peer_device_info;

			अगर (!has_net_conf(peer_device->connection))
				जारी;
			peer_device_to_info(&peer_device_info, peer_device);
			flags = (peer_devices--) ? NOTIFY_CONTINUES : 0;
			notअगरy_peer_device_state(शून्य, 0, peer_device, &peer_device_info,
						 NOTIFY_CREATE | flags);
		पूर्ण
		mutex_unlock(&notअगरication_mutex);
	पूर्ण
	mutex_unlock(&adm_ctx.resource->adm_mutex);
out:
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;
पूर्ण

अटल क्रमागत drbd_ret_code adm_del_minor(काष्ठा drbd_device *device)
अणु
	काष्ठा drbd_peer_device *peer_device;

	अगर (device->state.disk == D_DISKLESS &&
	    /* no need to be device->state.conn == C_STANDALONE &&
	     * we may want to delete a minor from a live replication group.
	     */
	    device->state.role == R_SECONDARY) अणु
		काष्ठा drbd_connection *connection =
			first_connection(device->resource);

		_drbd_request_state(device, NS(conn, C_WF_REPORT_PARAMS),
				    CS_VERBOSE + CS_WAIT_COMPLETE);

		/* If the state engine hasn't stopped the sender thपढ़ो yet, we
		 * need to flush the sender work queue beक्रमe generating the
		 * DESTROY events here. */
		अगर (get_t_state(&connection->worker) == RUNNING)
			drbd_flush_workqueue(&connection->sender_work);

		mutex_lock(&notअगरication_mutex);
		क्रम_each_peer_device(peer_device, device) अणु
			अगर (!has_net_conf(peer_device->connection))
				जारी;
			notअगरy_peer_device_state(शून्य, 0, peer_device, शून्य,
						 NOTIFY_DESTROY | NOTIFY_CONTINUES);
		पूर्ण
		notअगरy_device_state(शून्य, 0, device, शून्य, NOTIFY_DESTROY);
		mutex_unlock(&notअगरication_mutex);

		drbd_delete_device(device);
		वापस NO_ERROR;
	पूर्ण अन्यथा
		वापस ERR_MINOR_CONFIGURED;
पूर्ण

पूर्णांक drbd_adm_del_minor(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा drbd_config_context adm_ctx;
	क्रमागत drbd_ret_code retcode;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_MINOR);
	अगर (!adm_ctx.reply_skb)
		वापस retcode;
	अगर (retcode != NO_ERROR)
		जाओ out;

	mutex_lock(&adm_ctx.resource->adm_mutex);
	retcode = adm_del_minor(adm_ctx.device);
	mutex_unlock(&adm_ctx.resource->adm_mutex);
out:
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;
पूर्ण

अटल पूर्णांक adm_del_resource(काष्ठा drbd_resource *resource)
अणु
	काष्ठा drbd_connection *connection;

	क्रम_each_connection(connection, resource) अणु
		अगर (connection->cstate > C_STANDALONE)
			वापस ERR_NET_CONFIGURED;
	पूर्ण
	अगर (!idr_is_empty(&resource->devices))
		वापस ERR_RES_IN_USE;

	/* The state engine has stopped the sender thपढ़ो, so we करोn't
	 * need to flush the sender work queue beक्रमe generating the
	 * DESTROY event here. */
	mutex_lock(&notअगरication_mutex);
	notअगरy_resource_state(शून्य, 0, resource, शून्य, NOTIFY_DESTROY);
	mutex_unlock(&notअगरication_mutex);

	mutex_lock(&resources_mutex);
	list_del_rcu(&resource->resources);
	mutex_unlock(&resources_mutex);
	/* Make sure all thपढ़ोs have actually stopped: state handling only
	 * करोes drbd_thपढ़ो_stop_noरुको(). */
	list_क्रम_each_entry(connection, &resource->connections, connections)
		drbd_thपढ़ो_stop(&connection->worker);
	synchronize_rcu();
	drbd_मुक्त_resource(resource);
	वापस NO_ERROR;
पूर्ण

पूर्णांक drbd_adm_करोwn(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा drbd_config_context adm_ctx;
	काष्ठा drbd_resource *resource;
	काष्ठा drbd_connection *connection;
	काष्ठा drbd_device *device;
	पूर्णांक retcode; /* क्रमागत drbd_ret_code rsp. क्रमागत drbd_state_rv */
	अचिन्हित i;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_RESOURCE);
	अगर (!adm_ctx.reply_skb)
		वापस retcode;
	अगर (retcode != NO_ERROR)
		जाओ finish;

	resource = adm_ctx.resource;
	mutex_lock(&resource->adm_mutex);
	/* demote */
	क्रम_each_connection(connection, resource) अणु
		काष्ठा drbd_peer_device *peer_device;

		idr_क्रम_each_entry(&connection->peer_devices, peer_device, i) अणु
			retcode = drbd_set_role(peer_device->device, R_SECONDARY, 0);
			अगर (retcode < SS_SUCCESS) अणु
				drbd_msg_put_info(adm_ctx.reply_skb, "failed to demote");
				जाओ out;
			पूर्ण
		पूर्ण

		retcode = conn_try_disconnect(connection, 0);
		अगर (retcode < SS_SUCCESS) अणु
			drbd_msg_put_info(adm_ctx.reply_skb, "failed to disconnect");
			जाओ out;
		पूर्ण
	पूर्ण

	/* detach */
	idr_क्रम_each_entry(&resource->devices, device, i) अणु
		retcode = adm_detach(device, 0);
		अगर (retcode < SS_SUCCESS || retcode > NO_ERROR) अणु
			drbd_msg_put_info(adm_ctx.reply_skb, "failed to detach");
			जाओ out;
		पूर्ण
	पूर्ण

	/* delete volumes */
	idr_क्रम_each_entry(&resource->devices, device, i) अणु
		retcode = adm_del_minor(device);
		अगर (retcode != NO_ERROR) अणु
			/* "can not happen" */
			drbd_msg_put_info(adm_ctx.reply_skb, "failed to delete volume");
			जाओ out;
		पूर्ण
	पूर्ण

	retcode = adm_del_resource(resource);
out:
	mutex_unlock(&resource->adm_mutex);
finish:
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;
पूर्ण

पूर्णांक drbd_adm_del_resource(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा drbd_config_context adm_ctx;
	काष्ठा drbd_resource *resource;
	क्रमागत drbd_ret_code retcode;

	retcode = drbd_adm_prepare(&adm_ctx, skb, info, DRBD_ADM_NEED_RESOURCE);
	अगर (!adm_ctx.reply_skb)
		वापस retcode;
	अगर (retcode != NO_ERROR)
		जाओ finish;
	resource = adm_ctx.resource;

	mutex_lock(&resource->adm_mutex);
	retcode = adm_del_resource(resource);
	mutex_unlock(&resource->adm_mutex);
finish:
	drbd_adm_finish(&adm_ctx, info, retcode);
	वापस 0;
पूर्ण

व्योम drbd_bcast_event(काष्ठा drbd_device *device, स्थिर काष्ठा sib_info *sib)
अणु
	काष्ठा sk_buff *msg;
	काष्ठा drbd_genlmsghdr *d_out;
	अचिन्हित seq;
	पूर्णांक err = -ENOMEM;

	seq = atomic_inc_वापस(&drbd_genl_seq);
	msg = genlmsg_new(NLMSG_GOODSIZE, GFP_NOIO);
	अगर (!msg)
		जाओ failed;

	err = -EMSGSIZE;
	d_out = genlmsg_put(msg, 0, seq, &drbd_genl_family, 0, DRBD_EVENT);
	अगर (!d_out) /* cannot happen, but anyways. */
		जाओ nla_put_failure;
	d_out->minor = device_to_minor(device);
	d_out->ret_code = NO_ERROR;

	अगर (nla_put_status_info(msg, device, sib))
		जाओ nla_put_failure;
	genlmsg_end(msg, d_out);
	err = drbd_genl_multicast_events(msg, GFP_NOWAIT);
	/* msg has been consumed or मुक्तd in netlink_broadcast() */
	अगर (err && err != -ESRCH)
		जाओ failed;

	वापस;

nla_put_failure:
	nlmsg_मुक्त(msg);
failed:
	drbd_err(device, "Error %d while broadcasting event. "
			"Event seq:%u sib_reason:%u\n",
			err, seq, sib->sib_reason);
पूर्ण

अटल पूर्णांक nla_put_notअगरication_header(काष्ठा sk_buff *msg,
				       क्रमागत drbd_notअगरication_type type)
अणु
	काष्ठा drbd_notअगरication_header nh = अणु
		.nh_type = type,
	पूर्ण;

	वापस drbd_notअगरication_header_to_skb(msg, &nh, true);
पूर्ण

व्योम notअगरy_resource_state(काष्ठा sk_buff *skb,
			   अचिन्हित पूर्णांक seq,
			   काष्ठा drbd_resource *resource,
			   काष्ठा resource_info *resource_info,
			   क्रमागत drbd_notअगरication_type type)
अणु
	काष्ठा resource_statistics resource_statistics;
	काष्ठा drbd_genlmsghdr *dh;
	bool multicast = false;
	पूर्णांक err;

	अगर (!skb) अणु
		seq = atomic_inc_वापस(&notअगरy_genl_seq);
		skb = genlmsg_new(NLMSG_GOODSIZE, GFP_NOIO);
		err = -ENOMEM;
		अगर (!skb)
			जाओ failed;
		multicast = true;
	पूर्ण

	err = -EMSGSIZE;
	dh = genlmsg_put(skb, 0, seq, &drbd_genl_family, 0, DRBD_RESOURCE_STATE);
	अगर (!dh)
		जाओ nla_put_failure;
	dh->minor = -1U;
	dh->ret_code = NO_ERROR;
	अगर (nla_put_drbd_cfg_context(skb, resource, शून्य, शून्य) ||
	    nla_put_notअगरication_header(skb, type) ||
	    ((type & ~NOTIFY_FLAGS) != NOTIFY_DESTROY &&
	     resource_info_to_skb(skb, resource_info, true)))
		जाओ nla_put_failure;
	resource_statistics.res_stat_ग_लिखो_ordering = resource->ग_लिखो_ordering;
	err = resource_statistics_to_skb(skb, &resource_statistics, !capable(CAP_SYS_ADMIN));
	अगर (err)
		जाओ nla_put_failure;
	genlmsg_end(skb, dh);
	अगर (multicast) अणु
		err = drbd_genl_multicast_events(skb, GFP_NOWAIT);
		/* skb has been consumed or मुक्तd in netlink_broadcast() */
		अगर (err && err != -ESRCH)
			जाओ failed;
	पूर्ण
	वापस;

nla_put_failure:
	nlmsg_मुक्त(skb);
failed:
	drbd_err(resource, "Error %d while broadcasting event. Event seq:%u\n",
			err, seq);
पूर्ण

व्योम notअगरy_device_state(काष्ठा sk_buff *skb,
			 अचिन्हित पूर्णांक seq,
			 काष्ठा drbd_device *device,
			 काष्ठा device_info *device_info,
			 क्रमागत drbd_notअगरication_type type)
अणु
	काष्ठा device_statistics device_statistics;
	काष्ठा drbd_genlmsghdr *dh;
	bool multicast = false;
	पूर्णांक err;

	अगर (!skb) अणु
		seq = atomic_inc_वापस(&notअगरy_genl_seq);
		skb = genlmsg_new(NLMSG_GOODSIZE, GFP_NOIO);
		err = -ENOMEM;
		अगर (!skb)
			जाओ failed;
		multicast = true;
	पूर्ण

	err = -EMSGSIZE;
	dh = genlmsg_put(skb, 0, seq, &drbd_genl_family, 0, DRBD_DEVICE_STATE);
	अगर (!dh)
		जाओ nla_put_failure;
	dh->minor = device->minor;
	dh->ret_code = NO_ERROR;
	अगर (nla_put_drbd_cfg_context(skb, device->resource, शून्य, device) ||
	    nla_put_notअगरication_header(skb, type) ||
	    ((type & ~NOTIFY_FLAGS) != NOTIFY_DESTROY &&
	     device_info_to_skb(skb, device_info, true)))
		जाओ nla_put_failure;
	device_to_statistics(&device_statistics, device);
	device_statistics_to_skb(skb, &device_statistics, !capable(CAP_SYS_ADMIN));
	genlmsg_end(skb, dh);
	अगर (multicast) अणु
		err = drbd_genl_multicast_events(skb, GFP_NOWAIT);
		/* skb has been consumed or मुक्तd in netlink_broadcast() */
		अगर (err && err != -ESRCH)
			जाओ failed;
	पूर्ण
	वापस;

nla_put_failure:
	nlmsg_मुक्त(skb);
failed:
	drbd_err(device, "Error %d while broadcasting event. Event seq:%u\n",
		 err, seq);
पूर्ण

व्योम notअगरy_connection_state(काष्ठा sk_buff *skb,
			     अचिन्हित पूर्णांक seq,
			     काष्ठा drbd_connection *connection,
			     काष्ठा connection_info *connection_info,
			     क्रमागत drbd_notअगरication_type type)
अणु
	काष्ठा connection_statistics connection_statistics;
	काष्ठा drbd_genlmsghdr *dh;
	bool multicast = false;
	पूर्णांक err;

	अगर (!skb) अणु
		seq = atomic_inc_वापस(&notअगरy_genl_seq);
		skb = genlmsg_new(NLMSG_GOODSIZE, GFP_NOIO);
		err = -ENOMEM;
		अगर (!skb)
			जाओ failed;
		multicast = true;
	पूर्ण

	err = -EMSGSIZE;
	dh = genlmsg_put(skb, 0, seq, &drbd_genl_family, 0, DRBD_CONNECTION_STATE);
	अगर (!dh)
		जाओ nla_put_failure;
	dh->minor = -1U;
	dh->ret_code = NO_ERROR;
	अगर (nla_put_drbd_cfg_context(skb, connection->resource, connection, शून्य) ||
	    nla_put_notअगरication_header(skb, type) ||
	    ((type & ~NOTIFY_FLAGS) != NOTIFY_DESTROY &&
	     connection_info_to_skb(skb, connection_info, true)))
		जाओ nla_put_failure;
	connection_statistics.conn_congested = test_bit(NET_CONGESTED, &connection->flags);
	connection_statistics_to_skb(skb, &connection_statistics, !capable(CAP_SYS_ADMIN));
	genlmsg_end(skb, dh);
	अगर (multicast) अणु
		err = drbd_genl_multicast_events(skb, GFP_NOWAIT);
		/* skb has been consumed or मुक्तd in netlink_broadcast() */
		अगर (err && err != -ESRCH)
			जाओ failed;
	पूर्ण
	वापस;

nla_put_failure:
	nlmsg_मुक्त(skb);
failed:
	drbd_err(connection, "Error %d while broadcasting event. Event seq:%u\n",
		 err, seq);
पूर्ण

व्योम notअगरy_peer_device_state(काष्ठा sk_buff *skb,
			      अचिन्हित पूर्णांक seq,
			      काष्ठा drbd_peer_device *peer_device,
			      काष्ठा peer_device_info *peer_device_info,
			      क्रमागत drbd_notअगरication_type type)
अणु
	काष्ठा peer_device_statistics peer_device_statistics;
	काष्ठा drbd_resource *resource = peer_device->device->resource;
	काष्ठा drbd_genlmsghdr *dh;
	bool multicast = false;
	पूर्णांक err;

	अगर (!skb) अणु
		seq = atomic_inc_वापस(&notअगरy_genl_seq);
		skb = genlmsg_new(NLMSG_GOODSIZE, GFP_NOIO);
		err = -ENOMEM;
		अगर (!skb)
			जाओ failed;
		multicast = true;
	पूर्ण

	err = -EMSGSIZE;
	dh = genlmsg_put(skb, 0, seq, &drbd_genl_family, 0, DRBD_PEER_DEVICE_STATE);
	अगर (!dh)
		जाओ nla_put_failure;
	dh->minor = -1U;
	dh->ret_code = NO_ERROR;
	अगर (nla_put_drbd_cfg_context(skb, resource, peer_device->connection, peer_device->device) ||
	    nla_put_notअगरication_header(skb, type) ||
	    ((type & ~NOTIFY_FLAGS) != NOTIFY_DESTROY &&
	     peer_device_info_to_skb(skb, peer_device_info, true)))
		जाओ nla_put_failure;
	peer_device_to_statistics(&peer_device_statistics, peer_device);
	peer_device_statistics_to_skb(skb, &peer_device_statistics, !capable(CAP_SYS_ADMIN));
	genlmsg_end(skb, dh);
	अगर (multicast) अणु
		err = drbd_genl_multicast_events(skb, GFP_NOWAIT);
		/* skb has been consumed or मुक्तd in netlink_broadcast() */
		अगर (err && err != -ESRCH)
			जाओ failed;
	पूर्ण
	वापस;

nla_put_failure:
	nlmsg_मुक्त(skb);
failed:
	drbd_err(peer_device, "Error %d while broadcasting event. Event seq:%u\n",
		 err, seq);
पूर्ण

व्योम notअगरy_helper(क्रमागत drbd_notअगरication_type type,
		   काष्ठा drbd_device *device, काष्ठा drbd_connection *connection,
		   स्थिर अक्षर *name, पूर्णांक status)
अणु
	काष्ठा drbd_resource *resource = device ? device->resource : connection->resource;
	काष्ठा drbd_helper_info helper_info;
	अचिन्हित पूर्णांक seq = atomic_inc_वापस(&notअगरy_genl_seq);
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा drbd_genlmsghdr *dh;
	पूर्णांक err;

	strlcpy(helper_info.helper_name, name, माप(helper_info.helper_name));
	helper_info.helper_name_len = min(म_माप(name), माप(helper_info.helper_name));
	helper_info.helper_status = status;

	skb = genlmsg_new(NLMSG_GOODSIZE, GFP_NOIO);
	err = -ENOMEM;
	अगर (!skb)
		जाओ fail;

	err = -EMSGSIZE;
	dh = genlmsg_put(skb, 0, seq, &drbd_genl_family, 0, DRBD_HELPER);
	अगर (!dh)
		जाओ fail;
	dh->minor = device ? device->minor : -1;
	dh->ret_code = NO_ERROR;
	mutex_lock(&notअगरication_mutex);
	अगर (nla_put_drbd_cfg_context(skb, resource, connection, device) ||
	    nla_put_notअगरication_header(skb, type) ||
	    drbd_helper_info_to_skb(skb, &helper_info, true))
		जाओ unlock_fail;
	genlmsg_end(skb, dh);
	err = drbd_genl_multicast_events(skb, GFP_NOWAIT);
	skb = शून्य;
	/* skb has been consumed or मुक्तd in netlink_broadcast() */
	अगर (err && err != -ESRCH)
		जाओ unlock_fail;
	mutex_unlock(&notअगरication_mutex);
	वापस;

unlock_fail:
	mutex_unlock(&notअगरication_mutex);
fail:
	nlmsg_मुक्त(skb);
	drbd_err(resource, "Error %d while broadcasting event. Event seq:%u\n",
		 err, seq);
पूर्ण

अटल व्योम notअगरy_initial_state_करोne(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक seq)
अणु
	काष्ठा drbd_genlmsghdr *dh;
	पूर्णांक err;

	err = -EMSGSIZE;
	dh = genlmsg_put(skb, 0, seq, &drbd_genl_family, 0, DRBD_INITIAL_STATE_DONE);
	अगर (!dh)
		जाओ nla_put_failure;
	dh->minor = -1U;
	dh->ret_code = NO_ERROR;
	अगर (nla_put_notअगरication_header(skb, NOTIFY_EXISTS))
		जाओ nla_put_failure;
	genlmsg_end(skb, dh);
	वापस;

nla_put_failure:
	nlmsg_मुक्त(skb);
	pr_err("Error %d sending event. Event seq:%u\n", err, seq);
पूर्ण

अटल व्योम मुक्त_state_changes(काष्ठा list_head *list)
अणु
	जबतक (!list_empty(list)) अणु
		काष्ठा drbd_state_change *state_change =
			list_first_entry(list, काष्ठा drbd_state_change, list);
		list_del(&state_change->list);
		क्रमget_state_change(state_change);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक notअगरications_क्रम_state_change(काष्ठा drbd_state_change *state_change)
अणु
	वापस 1 +
	       state_change->n_connections +
	       state_change->n_devices +
	       state_change->n_devices * state_change->n_connections;
पूर्ण

अटल पूर्णांक get_initial_state(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा drbd_state_change *state_change = (काष्ठा drbd_state_change *)cb->args[0];
	अचिन्हित पूर्णांक seq = cb->args[2];
	अचिन्हित पूर्णांक n;
	क्रमागत drbd_notअगरication_type flags = 0;

	/* There is no need क्रम taking notअगरication_mutex here: it करोesn't
	   matter अगर the initial state events mix with later state chage
	   events; we can always tell the events apart by the NOTIFY_EXISTS
	   flag. */

	cb->args[5]--;
	अगर (cb->args[5] == 1) अणु
		notअगरy_initial_state_करोne(skb, seq);
		जाओ out;
	पूर्ण
	n = cb->args[4]++;
	अगर (cb->args[4] < cb->args[3])
		flags |= NOTIFY_CONTINUES;
	अगर (n < 1) अणु
		notअगरy_resource_state_change(skb, seq, state_change->resource,
					     NOTIFY_EXISTS | flags);
		जाओ next;
	पूर्ण
	n--;
	अगर (n < state_change->n_connections) अणु
		notअगरy_connection_state_change(skb, seq, &state_change->connections[n],
					       NOTIFY_EXISTS | flags);
		जाओ next;
	पूर्ण
	n -= state_change->n_connections;
	अगर (n < state_change->n_devices) अणु
		notअगरy_device_state_change(skb, seq, &state_change->devices[n],
					   NOTIFY_EXISTS | flags);
		जाओ next;
	पूर्ण
	n -= state_change->n_devices;
	अगर (n < state_change->n_devices * state_change->n_connections) अणु
		notअगरy_peer_device_state_change(skb, seq, &state_change->peer_devices[n],
						NOTIFY_EXISTS | flags);
		जाओ next;
	पूर्ण

next:
	अगर (cb->args[4] == cb->args[3]) अणु
		काष्ठा drbd_state_change *next_state_change =
			list_entry(state_change->list.next,
				   काष्ठा drbd_state_change, list);
		cb->args[0] = (दीर्घ)next_state_change;
		cb->args[3] = notअगरications_क्रम_state_change(next_state_change);
		cb->args[4] = 0;
	पूर्ण
out:
	वापस skb->len;
पूर्ण

पूर्णांक drbd_adm_get_initial_state(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा drbd_resource *resource;
	LIST_HEAD(head);

	अगर (cb->args[5] >= 1) अणु
		अगर (cb->args[5] > 1)
			वापस get_initial_state(skb, cb);
		अगर (cb->args[0]) अणु
			काष्ठा drbd_state_change *state_change =
				(काष्ठा drbd_state_change *)cb->args[0];

			/* connect list to head */
			list_add(&head, &state_change->list);
			मुक्त_state_changes(&head);
		पूर्ण
		वापस 0;
	पूर्ण

	cb->args[5] = 2;  /* number of iterations */
	mutex_lock(&resources_mutex);
	क्रम_each_resource(resource, &drbd_resources) अणु
		काष्ठा drbd_state_change *state_change;

		state_change = remember_old_state(resource, GFP_KERNEL);
		अगर (!state_change) अणु
			अगर (!list_empty(&head))
				मुक्त_state_changes(&head);
			mutex_unlock(&resources_mutex);
			वापस -ENOMEM;
		पूर्ण
		copy_old_to_new_state_change(state_change);
		list_add_tail(&state_change->list, &head);
		cb->args[5] += notअगरications_क्रम_state_change(state_change);
	पूर्ण
	mutex_unlock(&resources_mutex);

	अगर (!list_empty(&head)) अणु
		काष्ठा drbd_state_change *state_change =
			list_entry(head.next, काष्ठा drbd_state_change, list);
		cb->args[0] = (दीर्घ)state_change;
		cb->args[3] = notअगरications_क्रम_state_change(state_change);
		list_del(&head);  /* detach list from head */
	पूर्ण

	cb->args[2] = cb->nlh->nlmsg_seq;
	वापस get_initial_state(skb, cb);
पूर्ण
