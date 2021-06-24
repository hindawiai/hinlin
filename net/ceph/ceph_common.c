<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/ceph/ceph_debug.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/fs.h>
#समावेश <linux/inet.h>
#समावेश <linux/in6.h>
#समावेश <linux/key.h>
#समावेश <keys/ceph-type.h>
#समावेश <linux/module.h>
#समावेश <linux/mount.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/fs_parser.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/statfs.h>
#समावेश <linux/माला.स>
#समावेश <linux/vदो_स्मृति.h>


#समावेश <linux/ceph/ceph_features.h>
#समावेश <linux/ceph/libceph.h>
#समावेश <linux/ceph/debugfs.h>
#समावेश <linux/ceph/decode.h>
#समावेश <linux/ceph/mon_client.h>
#समावेश <linux/ceph/auth.h>
#समावेश "crypto.h"


/*
 * Module compatibility पूर्णांकerface.  For now it करोesn't करो anything,
 * but its existence संकेतs a certain level of functionality.
 *
 * The data buffer is used to pass inक्रमmation both to and from
 * libceph.  The वापस value indicates whether libceph determines
 * it is compatible with the caller (from another kernel module),
 * given the provided data.
 *
 * The data poपूर्णांकer can be null.
 */
bool libceph_compatible(व्योम *data)
अणु
	वापस true;
पूर्ण
EXPORT_SYMBOL(libceph_compatible);

अटल पूर्णांक param_get_supported_features(अक्षर *buffer,
					स्थिर काष्ठा kernel_param *kp)
अणु
	वापस प्र_लिखो(buffer, "0x%llx", CEPH_FEATURES_SUPPORTED_DEFAULT);
पूर्ण
अटल स्थिर काष्ठा kernel_param_ops param_ops_supported_features = अणु
	.get = param_get_supported_features,
पूर्ण;
module_param_cb(supported_features, &param_ops_supported_features, शून्य,
		0444);

स्थिर अक्षर *ceph_msg_type_name(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल CEPH_MSG_SHUTDOWN: वापस "shutdown";
	हाल CEPH_MSG_PING: वापस "ping";
	हाल CEPH_MSG_AUTH: वापस "auth";
	हाल CEPH_MSG_AUTH_REPLY: वापस "auth_reply";
	हाल CEPH_MSG_MON_MAP: वापस "mon_map";
	हाल CEPH_MSG_MON_GET_MAP: वापस "mon_get_map";
	हाल CEPH_MSG_MON_SUBSCRIBE: वापस "mon_subscribe";
	हाल CEPH_MSG_MON_SUBSCRIBE_ACK: वापस "mon_subscribe_ack";
	हाल CEPH_MSG_STATFS: वापस "statfs";
	हाल CEPH_MSG_STATFS_REPLY: वापस "statfs_reply";
	हाल CEPH_MSG_MON_GET_VERSION: वापस "mon_get_version";
	हाल CEPH_MSG_MON_GET_VERSION_REPLY: वापस "mon_get_version_reply";
	हाल CEPH_MSG_MDS_MAP: वापस "mds_map";
	हाल CEPH_MSG_FS_MAP_USER: वापस "fs_map_user";
	हाल CEPH_MSG_CLIENT_SESSION: वापस "client_session";
	हाल CEPH_MSG_CLIENT_RECONNECT: वापस "client_reconnect";
	हाल CEPH_MSG_CLIENT_REQUEST: वापस "client_request";
	हाल CEPH_MSG_CLIENT_REQUEST_FORWARD: वापस "client_request_forward";
	हाल CEPH_MSG_CLIENT_REPLY: वापस "client_reply";
	हाल CEPH_MSG_CLIENT_CAPS: वापस "client_caps";
	हाल CEPH_MSG_CLIENT_CAPRELEASE: वापस "client_cap_release";
	हाल CEPH_MSG_CLIENT_QUOTA: वापस "client_quota";
	हाल CEPH_MSG_CLIENT_SNAP: वापस "client_snap";
	हाल CEPH_MSG_CLIENT_LEASE: वापस "client_lease";
	हाल CEPH_MSG_POOLOP_REPLY: वापस "poolop_reply";
	हाल CEPH_MSG_POOLOP: वापस "poolop";
	हाल CEPH_MSG_MON_COMMAND: वापस "mon_command";
	हाल CEPH_MSG_MON_COMMAND_ACK: वापस "mon_command_ack";
	हाल CEPH_MSG_OSD_MAP: वापस "osd_map";
	हाल CEPH_MSG_OSD_OP: वापस "osd_op";
	हाल CEPH_MSG_OSD_OPREPLY: वापस "osd_opreply";
	हाल CEPH_MSG_WATCH_NOTIFY: वापस "watch_notify";
	हाल CEPH_MSG_OSD_BACKOFF: वापस "osd_backoff";
	शेष: वापस "unknown";
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ceph_msg_type_name);

/*
 * Initially learn our fsid, or verअगरy an fsid matches.
 */
पूर्णांक ceph_check_fsid(काष्ठा ceph_client *client, काष्ठा ceph_fsid *fsid)
अणु
	अगर (client->have_fsid) अणु
		अगर (ceph_fsid_compare(&client->fsid, fsid)) अणु
			pr_err("bad fsid, had %pU got %pU",
			       &client->fsid, fsid);
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		स_नकल(&client->fsid, fsid, माप(*fsid));
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ceph_check_fsid);

अटल पूर्णांक म_भेद_null(स्थिर अक्षर *s1, स्थिर अक्षर *s2)
अणु
	अगर (!s1 && !s2)
		वापस 0;
	अगर (s1 && !s2)
		वापस -1;
	अगर (!s1 && s2)
		वापस 1;
	वापस म_भेद(s1, s2);
पूर्ण

पूर्णांक ceph_compare_options(काष्ठा ceph_options *new_opt,
			 काष्ठा ceph_client *client)
अणु
	काष्ठा ceph_options *opt1 = new_opt;
	काष्ठा ceph_options *opt2 = client->options;
	पूर्णांक ofs = दुरत्व(काष्ठा ceph_options, mon_addr);
	पूर्णांक i;
	पूर्णांक ret;

	/*
	 * Don't bother comparing options if network namespaces don't
	 * match.
	 */
	अगर (!net_eq(current->nsproxy->net_ns, पढ़ो_pnet(&client->msgr.net)))
		वापस -1;

	ret = स_भेद(opt1, opt2, ofs);
	अगर (ret)
		वापस ret;

	ret = म_भेद_null(opt1->name, opt2->name);
	अगर (ret)
		वापस ret;

	अगर (opt1->key && !opt2->key)
		वापस -1;
	अगर (!opt1->key && opt2->key)
		वापस 1;
	अगर (opt1->key && opt2->key) अणु
		अगर (opt1->key->type != opt2->key->type)
			वापस -1;
		अगर (opt1->key->created.tv_sec != opt2->key->created.tv_sec)
			वापस -1;
		अगर (opt1->key->created.tv_nsec != opt2->key->created.tv_nsec)
			वापस -1;
		अगर (opt1->key->len != opt2->key->len)
			वापस -1;
		अगर (opt1->key->key && !opt2->key->key)
			वापस -1;
		अगर (!opt1->key->key && opt2->key->key)
			वापस 1;
		अगर (opt1->key->key && opt2->key->key) अणु
			ret = स_भेद(opt1->key->key, opt2->key->key, opt1->key->len);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	ret = ceph_compare_crush_locs(&opt1->crush_locs, &opt2->crush_locs);
	अगर (ret)
		वापस ret;

	/* any matching mon ip implies a match */
	क्रम (i = 0; i < opt1->num_mon; i++) अणु
		अगर (ceph_monmap_contains(client->monc.monmap,
				 &opt1->mon_addr[i]))
			वापस 0;
	पूर्ण
	वापस -1;
पूर्ण
EXPORT_SYMBOL(ceph_compare_options);

/*
 * kvदो_स्मृति() करोesn't fall back to the vदो_स्मृति allocator unless flags are
 * compatible with (a superset of) GFP_KERNEL.  This is because जबतक the
 * actual pages are allocated with the specअगरied flags, the page table pages
 * are always allocated with GFP_KERNEL.
 *
 * ceph_kvदो_स्मृति() may be called with GFP_KERNEL, GFP_NOFS or GFP_NOIO.
 */
व्योम *ceph_kvदो_स्मृति(माप_प्रकार size, gfp_t flags)
अणु
	व्योम *p;

	अगर ((flags & (__GFP_IO | __GFP_FS)) == (__GFP_IO | __GFP_FS)) अणु
		p = kvदो_स्मृति(size, flags);
	पूर्ण अन्यथा अगर ((flags & (__GFP_IO | __GFP_FS)) == __GFP_IO) अणु
		अचिन्हित पूर्णांक nofs_flag = meदो_स्मृति_nofs_save();
		p = kvदो_स्मृति(size, GFP_KERNEL);
		meदो_स्मृति_nofs_restore(nofs_flag);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक noio_flag = meदो_स्मृति_noio_save();
		p = kvदो_स्मृति(size, GFP_KERNEL);
		meदो_स्मृति_noio_restore(noio_flag);
	पूर्ण

	वापस p;
पूर्ण

अटल पूर्णांक parse_fsid(स्थिर अक्षर *str, काष्ठा ceph_fsid *fsid)
अणु
	पूर्णांक i = 0;
	अक्षर पंचांगp[3];
	पूर्णांक err = -EINVAL;
	पूर्णांक d;

	करोut("parse_fsid '%s'\n", str);
	पंचांगp[2] = 0;
	जबतक (*str && i < 16) अणु
		अगर (है_विराम(*str)) अणु
			str++;
			जारी;
		पूर्ण
		अगर (!है_षष्ठादशक(str[0]) || !है_षष्ठादशक(str[1]))
			अवरोध;
		पंचांगp[0] = str[0];
		पंचांगp[1] = str[1];
		अगर (माला_पूछो(पंचांगp, "%x", &d) < 1)
			अवरोध;
		fsid->fsid[i] = d & 0xff;
		i++;
		str += 2;
	पूर्ण

	अगर (i == 16)
		err = 0;
	करोut("parse_fsid ret %d got fsid %pU\n", err, fsid);
	वापस err;
पूर्ण

/*
 * ceph options
 */
क्रमागत अणु
	Opt_osdkeepaliveसमयout,
	Opt_mount_समयout,
	Opt_osd_idle_ttl,
	Opt_osd_request_समयout,
	/* पूर्णांक args above */
	Opt_fsid,
	Opt_name,
	Opt_secret,
	Opt_key,
	Opt_ip,
	Opt_crush_location,
	Opt_पढ़ो_from_replica,
	Opt_ms_mode,
	/* string args above */
	Opt_share,
	Opt_crc,
	Opt_cephx_require_signatures,
	Opt_cephx_sign_messages,
	Opt_tcp_nodelay,
	Opt_पात_on_full,
पूर्ण;

क्रमागत अणु
	Opt_पढ़ो_from_replica_no,
	Opt_पढ़ो_from_replica_balance,
	Opt_पढ़ो_from_replica_localize,
पूर्ण;

अटल स्थिर काष्ठा स्थिरant_table ceph_param_पढ़ो_from_replica[] = अणु
	अणु"no",		Opt_पढ़ो_from_replica_noपूर्ण,
	अणु"balance",	Opt_पढ़ो_from_replica_balanceपूर्ण,
	अणु"localize",	Opt_पढ़ो_from_replica_localizeपूर्ण,
	अणुपूर्ण
पूर्ण;

क्रमागत ceph_ms_mode अणु
	Opt_ms_mode_legacy,
	Opt_ms_mode_crc,
	Opt_ms_mode_secure,
	Opt_ms_mode_prefer_crc,
	Opt_ms_mode_prefer_secure
पूर्ण;

अटल स्थिर काष्ठा स्थिरant_table ceph_param_ms_mode[] = अणु
	अणु"legacy",		Opt_ms_mode_legacyपूर्ण,
	अणु"crc",			Opt_ms_mode_crcपूर्ण,
	अणु"secure",		Opt_ms_mode_secureपूर्ण,
	अणु"prefer-crc",		Opt_ms_mode_prefer_crcपूर्ण,
	अणु"prefer-secure",	Opt_ms_mode_prefer_secureपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा fs_parameter_spec ceph_parameters[] = अणु
	fsparam_flag	("abort_on_full",		Opt_पात_on_full),
	__fsparam	(शून्य, "cephx_require_signatures", Opt_cephx_require_signatures,
			 fs_param_neg_with_no|fs_param_deprecated, शून्य),
	fsparam_flag_no ("cephx_sign_messages",		Opt_cephx_sign_messages),
	fsparam_flag_no ("crc",				Opt_crc),
	fsparam_string	("crush_location",		Opt_crush_location),
	fsparam_string	("fsid",			Opt_fsid),
	fsparam_string	("ip",				Opt_ip),
	fsparam_string	("key",				Opt_key),
	fsparam_u32	("mount_timeout",		Opt_mount_समयout),
	fsparam_string	("name",			Opt_name),
	fsparam_u32	("osd_idle_ttl",		Opt_osd_idle_ttl),
	fsparam_u32	("osd_request_timeout",		Opt_osd_request_समयout),
	fsparam_u32	("osdkeepalive",		Opt_osdkeepaliveसमयout),
	fsparam_क्रमागत	("read_from_replica",		Opt_पढ़ो_from_replica,
			 ceph_param_पढ़ो_from_replica),
	fsparam_क्रमागत	("ms_mode",			Opt_ms_mode,
			 ceph_param_ms_mode),
	fsparam_string	("secret",			Opt_secret),
	fsparam_flag_no ("share",			Opt_share),
	fsparam_flag_no ("tcp_nodelay",			Opt_tcp_nodelay),
	अणुपूर्ण
पूर्ण;

काष्ठा ceph_options *ceph_alloc_options(व्योम)
अणु
	काष्ठा ceph_options *opt;

	opt = kzalloc(माप(*opt), GFP_KERNEL);
	अगर (!opt)
		वापस शून्य;

	opt->crush_locs = RB_ROOT;
	opt->mon_addr = kसुस्मृति(CEPH_MAX_MON, माप(*opt->mon_addr),
				GFP_KERNEL);
	अगर (!opt->mon_addr) अणु
		kमुक्त(opt);
		वापस शून्य;
	पूर्ण

	opt->flags = CEPH_OPT_DEFAULT;
	opt->osd_keepalive_समयout = CEPH_OSD_KEEPALIVE_DEFAULT;
	opt->mount_समयout = CEPH_MOUNT_TIMEOUT_DEFAULT;
	opt->osd_idle_ttl = CEPH_OSD_IDLE_TTL_DEFAULT;
	opt->osd_request_समयout = CEPH_OSD_REQUEST_TIMEOUT_DEFAULT;
	opt->पढ़ो_from_replica = CEPH_READ_FROM_REPLICA_DEFAULT;
	opt->con_modes[0] = CEPH_CON_MODE_UNKNOWN;
	opt->con_modes[1] = CEPH_CON_MODE_UNKNOWN;
	वापस opt;
पूर्ण
EXPORT_SYMBOL(ceph_alloc_options);

व्योम ceph_destroy_options(काष्ठा ceph_options *opt)
अणु
	करोut("destroy_options %p\n", opt);
	अगर (!opt)
		वापस;

	ceph_clear_crush_locs(&opt->crush_locs);
	kमुक्त(opt->name);
	अगर (opt->key) अणु
		ceph_crypto_key_destroy(opt->key);
		kमुक्त(opt->key);
	पूर्ण
	kमुक्त(opt->mon_addr);
	kमुक्त(opt);
पूर्ण
EXPORT_SYMBOL(ceph_destroy_options);

/* get secret from key store */
अटल पूर्णांक get_secret(काष्ठा ceph_crypto_key *dst, स्थिर अक्षर *name,
		      काष्ठा p_log *log)
अणु
	काष्ठा key *ukey;
	पूर्णांक key_err;
	पूर्णांक err = 0;
	काष्ठा ceph_crypto_key *ckey;

	ukey = request_key(&key_type_ceph, name, शून्य);
	अगर (IS_ERR(ukey)) अणु
		/* request_key errors करोn't map nicely to mount(2)
		   errors; करोn't even try, but still prपूर्णांकk */
		key_err = PTR_ERR(ukey);
		चयन (key_err) अणु
		हाल -ENOKEY:
			error_plog(log, "Failed due to key not found: %s",
			       name);
			अवरोध;
		हाल -EKEYEXPIRED:
			error_plog(log, "Failed due to expired key: %s",
			       name);
			अवरोध;
		हाल -EKEYREVOKED:
			error_plog(log, "Failed due to revoked key: %s",
			       name);
			अवरोध;
		शेष:
			error_plog(log, "Failed due to key error %d: %s",
			       key_err, name);
		पूर्ण
		err = -EPERM;
		जाओ out;
	पूर्ण

	ckey = ukey->payload.data[0];
	err = ceph_crypto_key_clone(dst, ckey);
	अगर (err)
		जाओ out_key;
	/* pass through, err is 0 */

out_key:
	key_put(ukey);
out:
	वापस err;
पूर्ण

पूर्णांक ceph_parse_mon_ips(स्थिर अक्षर *buf, माप_प्रकार len, काष्ठा ceph_options *opt,
		       काष्ठा fc_log *l)
अणु
	काष्ठा p_log log = अणु.prefix = "libceph", .log = lपूर्ण;
	पूर्णांक ret;

	/* ip1[:port1][,ip2[:port2]...] */
	ret = ceph_parse_ips(buf, buf + len, opt->mon_addr, CEPH_MAX_MON,
			     &opt->num_mon);
	अगर (ret) अणु
		error_plog(&log, "Failed to parse monitor IPs: %d", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ceph_parse_mon_ips);

पूर्णांक ceph_parse_param(काष्ठा fs_parameter *param, काष्ठा ceph_options *opt,
		     काष्ठा fc_log *l)
अणु
	काष्ठा fs_parse_result result;
	पूर्णांक token, err;
	काष्ठा p_log log = अणु.prefix = "libceph", .log = lपूर्ण;

	token = __fs_parse(&log, ceph_parameters, param, &result);
	करोut("%s fs_parse '%s' token %d\n", __func__, param->key, token);
	अगर (token < 0)
		वापस token;

	चयन (token) अणु
	हाल Opt_ip:
		err = ceph_parse_ips(param->string,
				     param->string + param->size,
				     &opt->my_addr,
				     1, शून्य);
		अगर (err) अणु
			error_plog(&log, "Failed to parse ip: %d", err);
			वापस err;
		पूर्ण
		opt->flags |= CEPH_OPT_MYIP;
		अवरोध;

	हाल Opt_fsid:
		err = parse_fsid(param->string, &opt->fsid);
		अगर (err) अणु
			error_plog(&log, "Failed to parse fsid: %d", err);
			वापस err;
		पूर्ण
		opt->flags |= CEPH_OPT_FSID;
		अवरोध;
	हाल Opt_name:
		kमुक्त(opt->name);
		opt->name = param->string;
		param->string = शून्य;
		अवरोध;
	हाल Opt_secret:
		ceph_crypto_key_destroy(opt->key);
		kमुक्त(opt->key);

		opt->key = kzalloc(माप(*opt->key), GFP_KERNEL);
		अगर (!opt->key)
			वापस -ENOMEM;
		err = ceph_crypto_key_unarmor(opt->key, param->string);
		अगर (err) अणु
			error_plog(&log, "Failed to parse secret: %d", err);
			वापस err;
		पूर्ण
		अवरोध;
	हाल Opt_key:
		ceph_crypto_key_destroy(opt->key);
		kमुक्त(opt->key);

		opt->key = kzalloc(माप(*opt->key), GFP_KERNEL);
		अगर (!opt->key)
			वापस -ENOMEM;
		वापस get_secret(opt->key, param->string, &log);
	हाल Opt_crush_location:
		ceph_clear_crush_locs(&opt->crush_locs);
		err = ceph_parse_crush_location(param->string,
						&opt->crush_locs);
		अगर (err) अणु
			error_plog(&log, "Failed to parse CRUSH location: %d",
				   err);
			वापस err;
		पूर्ण
		अवरोध;
	हाल Opt_पढ़ो_from_replica:
		चयन (result.uपूर्णांक_32) अणु
		हाल Opt_पढ़ो_from_replica_no:
			opt->पढ़ो_from_replica = 0;
			अवरोध;
		हाल Opt_पढ़ो_from_replica_balance:
			opt->पढ़ो_from_replica = CEPH_OSD_FLAG_BALANCE_READS;
			अवरोध;
		हाल Opt_पढ़ो_from_replica_localize:
			opt->पढ़ो_from_replica = CEPH_OSD_FLAG_LOCALIZE_READS;
			अवरोध;
		शेष:
			BUG();
		पूर्ण
		अवरोध;
	हाल Opt_ms_mode:
		चयन (result.uपूर्णांक_32) अणु
		हाल Opt_ms_mode_legacy:
			opt->con_modes[0] = CEPH_CON_MODE_UNKNOWN;
			opt->con_modes[1] = CEPH_CON_MODE_UNKNOWN;
			अवरोध;
		हाल Opt_ms_mode_crc:
			opt->con_modes[0] = CEPH_CON_MODE_CRC;
			opt->con_modes[1] = CEPH_CON_MODE_UNKNOWN;
			अवरोध;
		हाल Opt_ms_mode_secure:
			opt->con_modes[0] = CEPH_CON_MODE_SECURE;
			opt->con_modes[1] = CEPH_CON_MODE_UNKNOWN;
			अवरोध;
		हाल Opt_ms_mode_prefer_crc:
			opt->con_modes[0] = CEPH_CON_MODE_CRC;
			opt->con_modes[1] = CEPH_CON_MODE_SECURE;
			अवरोध;
		हाल Opt_ms_mode_prefer_secure:
			opt->con_modes[0] = CEPH_CON_MODE_SECURE;
			opt->con_modes[1] = CEPH_CON_MODE_CRC;
			अवरोध;
		शेष:
			BUG();
		पूर्ण
		अवरोध;

	हाल Opt_osdkeepaliveसमयout:
		/* 0 isn't well defined right now, reject it */
		अगर (result.uपूर्णांक_32 < 1 || result.uपूर्णांक_32 > पूर्णांक_उच्च / 1000)
			जाओ out_of_range;
		opt->osd_keepalive_समयout =
		    msecs_to_jअगरfies(result.uपूर्णांक_32 * 1000);
		अवरोध;
	हाल Opt_osd_idle_ttl:
		/* 0 isn't well defined right now, reject it */
		अगर (result.uपूर्णांक_32 < 1 || result.uपूर्णांक_32 > पूर्णांक_उच्च / 1000)
			जाओ out_of_range;
		opt->osd_idle_ttl = msecs_to_jअगरfies(result.uपूर्णांक_32 * 1000);
		अवरोध;
	हाल Opt_mount_समयout:
		/* 0 is "wait forever" (i.e. infinite समयout) */
		अगर (result.uपूर्णांक_32 > पूर्णांक_उच्च / 1000)
			जाओ out_of_range;
		opt->mount_समयout = msecs_to_jअगरfies(result.uपूर्णांक_32 * 1000);
		अवरोध;
	हाल Opt_osd_request_समयout:
		/* 0 is "wait forever" (i.e. infinite समयout) */
		अगर (result.uपूर्णांक_32 > पूर्णांक_उच्च / 1000)
			जाओ out_of_range;
		opt->osd_request_समयout =
		    msecs_to_jअगरfies(result.uपूर्णांक_32 * 1000);
		अवरोध;

	हाल Opt_share:
		अगर (!result.negated)
			opt->flags &= ~CEPH_OPT_NOSHARE;
		अन्यथा
			opt->flags |= CEPH_OPT_NOSHARE;
		अवरोध;
	हाल Opt_crc:
		अगर (!result.negated)
			opt->flags &= ~CEPH_OPT_NOCRC;
		अन्यथा
			opt->flags |= CEPH_OPT_NOCRC;
		अवरोध;
	हाल Opt_cephx_require_signatures:
		अगर (!result.negated)
			warn_plog(&log, "Ignoring cephx_require_signatures");
		अन्यथा
			warn_plog(&log, "Ignoring nocephx_require_signatures, use nocephx_sign_messages");
		अवरोध;
	हाल Opt_cephx_sign_messages:
		अगर (!result.negated)
			opt->flags &= ~CEPH_OPT_NOMSGSIGN;
		अन्यथा
			opt->flags |= CEPH_OPT_NOMSGSIGN;
		अवरोध;
	हाल Opt_tcp_nodelay:
		अगर (!result.negated)
			opt->flags |= CEPH_OPT_TCP_NODELAY;
		अन्यथा
			opt->flags &= ~CEPH_OPT_TCP_NODELAY;
		अवरोध;

	हाल Opt_पात_on_full:
		opt->flags |= CEPH_OPT_ABORT_ON_FULL;
		अवरोध;

	शेष:
		BUG();
	पूर्ण

	वापस 0;

out_of_range:
	वापस inval_plog(&log, "%s out of range", param->key);
पूर्ण
EXPORT_SYMBOL(ceph_parse_param);

पूर्णांक ceph_prपूर्णांक_client_options(काष्ठा seq_file *m, काष्ठा ceph_client *client,
			      bool show_all)
अणु
	काष्ठा ceph_options *opt = client->options;
	माप_प्रकार pos = m->count;
	काष्ठा rb_node *n;

	अगर (opt->name) अणु
		seq_माला_दो(m, "name=");
		seq_escape(m, opt->name, ", \t\n\\");
		seq_अ_दो(m, ',');
	पूर्ण
	अगर (opt->key)
		seq_माला_दो(m, "secret=<hidden>,");

	अगर (!RB_EMPTY_ROOT(&opt->crush_locs)) अणु
		seq_माला_दो(m, "crush_location=");
		क्रम (n = rb_first(&opt->crush_locs); ; ) अणु
			काष्ठा crush_loc_node *loc =
			    rb_entry(n, काष्ठा crush_loc_node, cl_node);

			seq_म_लिखो(m, "%s:%s", loc->cl_loc.cl_type_name,
				   loc->cl_loc.cl_name);
			n = rb_next(n);
			अगर (!n)
				अवरोध;

			seq_अ_दो(m, '|');
		पूर्ण
		seq_अ_दो(m, ',');
	पूर्ण
	अगर (opt->पढ़ो_from_replica == CEPH_OSD_FLAG_BALANCE_READS) अणु
		seq_माला_दो(m, "read_from_replica=balance,");
	पूर्ण अन्यथा अगर (opt->पढ़ो_from_replica == CEPH_OSD_FLAG_LOCALIZE_READS) अणु
		seq_माला_दो(m, "read_from_replica=localize,");
	पूर्ण
	अगर (opt->con_modes[0] != CEPH_CON_MODE_UNKNOWN) अणु
		अगर (opt->con_modes[0] == CEPH_CON_MODE_CRC &&
		    opt->con_modes[1] == CEPH_CON_MODE_UNKNOWN) अणु
			seq_माला_दो(m, "ms_mode=crc,");
		पूर्ण अन्यथा अगर (opt->con_modes[0] == CEPH_CON_MODE_SECURE &&
			   opt->con_modes[1] == CEPH_CON_MODE_UNKNOWN) अणु
			seq_माला_दो(m, "ms_mode=secure,");
		पूर्ण अन्यथा अगर (opt->con_modes[0] == CEPH_CON_MODE_CRC &&
			   opt->con_modes[1] == CEPH_CON_MODE_SECURE) अणु
			seq_माला_दो(m, "ms_mode=prefer-crc,");
		पूर्ण अन्यथा अगर (opt->con_modes[0] == CEPH_CON_MODE_SECURE &&
			   opt->con_modes[1] == CEPH_CON_MODE_CRC) अणु
			seq_माला_दो(m, "ms_mode=prefer-secure,");
		पूर्ण
	पूर्ण

	अगर (opt->flags & CEPH_OPT_FSID)
		seq_म_लिखो(m, "fsid=%pU,", &opt->fsid);
	अगर (opt->flags & CEPH_OPT_NOSHARE)
		seq_माला_दो(m, "noshare,");
	अगर (opt->flags & CEPH_OPT_NOCRC)
		seq_माला_दो(m, "nocrc,");
	अगर (opt->flags & CEPH_OPT_NOMSGSIGN)
		seq_माला_दो(m, "nocephx_sign_messages,");
	अगर ((opt->flags & CEPH_OPT_TCP_NODELAY) == 0)
		seq_माला_दो(m, "notcp_nodelay,");
	अगर (show_all && (opt->flags & CEPH_OPT_ABORT_ON_FULL))
		seq_माला_दो(m, "abort_on_full,");

	अगर (opt->mount_समयout != CEPH_MOUNT_TIMEOUT_DEFAULT)
		seq_म_लिखो(m, "mount_timeout=%d,",
			   jअगरfies_to_msecs(opt->mount_समयout) / 1000);
	अगर (opt->osd_idle_ttl != CEPH_OSD_IDLE_TTL_DEFAULT)
		seq_म_लिखो(m, "osd_idle_ttl=%d,",
			   jअगरfies_to_msecs(opt->osd_idle_ttl) / 1000);
	अगर (opt->osd_keepalive_समयout != CEPH_OSD_KEEPALIVE_DEFAULT)
		seq_म_लिखो(m, "osdkeepalivetimeout=%d,",
		    jअगरfies_to_msecs(opt->osd_keepalive_समयout) / 1000);
	अगर (opt->osd_request_समयout != CEPH_OSD_REQUEST_TIMEOUT_DEFAULT)
		seq_म_लिखो(m, "osd_request_timeout=%d,",
			   jअगरfies_to_msecs(opt->osd_request_समयout) / 1000);

	/* drop redundant comma */
	अगर (m->count != pos)
		m->count--;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ceph_prपूर्णांक_client_options);

काष्ठा ceph_entity_addr *ceph_client_addr(काष्ठा ceph_client *client)
अणु
	वापस &client->msgr.inst.addr;
पूर्ण
EXPORT_SYMBOL(ceph_client_addr);

u64 ceph_client_gid(काष्ठा ceph_client *client)
अणु
	वापस client->monc.auth->global_id;
पूर्ण
EXPORT_SYMBOL(ceph_client_gid);

/*
 * create a fresh client instance
 */
काष्ठा ceph_client *ceph_create_client(काष्ठा ceph_options *opt, व्योम *निजी)
अणु
	काष्ठा ceph_client *client;
	काष्ठा ceph_entity_addr *myaddr = शून्य;
	पूर्णांक err;

	err = रुको_क्रम_अक्रमom_bytes();
	अगर (err < 0)
		वापस ERR_PTR(err);

	client = kzalloc(माप(*client), GFP_KERNEL);
	अगर (client == शून्य)
		वापस ERR_PTR(-ENOMEM);

	client->निजी = निजी;
	client->options = opt;

	mutex_init(&client->mount_mutex);
	init_रुकोqueue_head(&client->auth_wq);
	client->auth_err = 0;

	client->extra_mon_dispatch = शून्य;
	client->supported_features = CEPH_FEATURES_SUPPORTED_DEFAULT;
	client->required_features = CEPH_FEATURES_REQUIRED_DEFAULT;

	अगर (!ceph_test_opt(client, NOMSGSIGN))
		client->required_features |= CEPH_FEATURE_MSG_AUTH;

	/* msgr */
	अगर (ceph_test_opt(client, MYIP))
		myaddr = &client->options->my_addr;

	ceph_messenger_init(&client->msgr, myaddr);

	/* subप्रणालीs */
	err = ceph_monc_init(&client->monc, client);
	अगर (err < 0)
		जाओ fail;
	err = ceph_osdc_init(&client->osdc, client);
	अगर (err < 0)
		जाओ fail_monc;

	वापस client;

fail_monc:
	ceph_monc_stop(&client->monc);
fail:
	ceph_messenger_fini(&client->msgr);
	kमुक्त(client);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL(ceph_create_client);

व्योम ceph_destroy_client(काष्ठा ceph_client *client)
अणु
	करोut("destroy_client %p\n", client);

	atomic_set(&client->msgr.stopping, 1);

	/* unmount */
	ceph_osdc_stop(&client->osdc);
	ceph_monc_stop(&client->monc);
	ceph_messenger_fini(&client->msgr);

	ceph_debugfs_client_cleanup(client);

	ceph_destroy_options(client->options);

	kमुक्त(client);
	करोut("destroy_client %p done\n", client);
पूर्ण
EXPORT_SYMBOL(ceph_destroy_client);

व्योम ceph_reset_client_addr(काष्ठा ceph_client *client)
अणु
	ceph_messenger_reset_nonce(&client->msgr);
	ceph_monc_reखोलो_session(&client->monc);
	ceph_osdc_reखोलो_osds(&client->osdc);
पूर्ण
EXPORT_SYMBOL(ceph_reset_client_addr);

/*
 * true अगर we have the mon map (and have thus joined the cluster)
 */
अटल bool have_mon_and_osd_map(काष्ठा ceph_client *client)
अणु
	वापस client->monc.monmap && client->monc.monmap->epoch &&
	       client->osdc.osdmap && client->osdc.osdmap->epoch;
पूर्ण

/*
 * mount: join the ceph cluster, and खोलो root directory.
 */
पूर्णांक __ceph_खोलो_session(काष्ठा ceph_client *client, अचिन्हित दीर्घ started)
अणु
	अचिन्हित दीर्घ समयout = client->options->mount_समयout;
	दीर्घ err;

	/* खोलो session, and रुको क्रम mon and osd maps */
	err = ceph_monc_खोलो_session(&client->monc);
	अगर (err < 0)
		वापस err;

	जबतक (!have_mon_and_osd_map(client)) अणु
		अगर (समयout && समय_after_eq(jअगरfies, started + समयout))
			वापस -ETIMEDOUT;

		/* रुको */
		करोut("mount waiting for mon_map\n");
		err = रुको_event_पूर्णांकerruptible_समयout(client->auth_wq,
			have_mon_and_osd_map(client) || (client->auth_err < 0),
			ceph_समयout_jअगरfies(समयout));
		अगर (err < 0)
			वापस err;
		अगर (client->auth_err < 0)
			वापस client->auth_err;
	पूर्ण

	pr_info("client%llu fsid %pU\n", ceph_client_gid(client),
		&client->fsid);
	ceph_debugfs_client_init(client);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(__ceph_खोलो_session);

पूर्णांक ceph_खोलो_session(काष्ठा ceph_client *client)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ started = jअगरfies;  /* note the start समय */

	करोut("open_session start\n");
	mutex_lock(&client->mount_mutex);

	ret = __ceph_खोलो_session(client, started);

	mutex_unlock(&client->mount_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ceph_खोलो_session);

पूर्णांक ceph_रुको_क्रम_latest_osdmap(काष्ठा ceph_client *client,
				अचिन्हित दीर्घ समयout)
अणु
	u64 newest_epoch;
	पूर्णांक ret;

	ret = ceph_monc_get_version(&client->monc, "osdmap", &newest_epoch);
	अगर (ret)
		वापस ret;

	अगर (client->osdc.osdmap->epoch >= newest_epoch)
		वापस 0;

	ceph_osdc_maybe_request_map(&client->osdc);
	वापस ceph_monc_रुको_osdmap(&client->monc, newest_epoch, समयout);
पूर्ण
EXPORT_SYMBOL(ceph_रुको_क्रम_latest_osdmap);

अटल पूर्णांक __init init_ceph_lib(व्योम)
अणु
	पूर्णांक ret = 0;

	ceph_debugfs_init();

	ret = ceph_crypto_init();
	अगर (ret < 0)
		जाओ out_debugfs;

	ret = ceph_msgr_init();
	अगर (ret < 0)
		जाओ out_crypto;

	ret = ceph_osdc_setup();
	अगर (ret < 0)
		जाओ out_msgr;

	pr_info("loaded (mon/osd proto %d/%d)\n",
		CEPH_MONC_PROTOCOL, CEPH_OSDC_PROTOCOL);

	वापस 0;

out_msgr:
	ceph_msgr_निकास();
out_crypto:
	ceph_crypto_shutकरोwn();
out_debugfs:
	ceph_debugfs_cleanup();
	वापस ret;
पूर्ण

अटल व्योम __निकास निकास_ceph_lib(व्योम)
अणु
	करोut("exit_ceph_lib\n");
	WARN_ON(!ceph_strings_empty());

	ceph_osdc_cleanup();
	ceph_msgr_निकास();
	ceph_crypto_shutकरोwn();
	ceph_debugfs_cleanup();
पूर्ण

module_init(init_ceph_lib);
module_निकास(निकास_ceph_lib);

MODULE_AUTHOR("Sage Weil <sage@newdream.net>");
MODULE_AUTHOR("Yehuda Sadeh <yehuda@hq.newdream.net>");
MODULE_AUTHOR("Patience Warnick <patience@newdream.net>");
MODULE_DESCRIPTION("Ceph core library");
MODULE_LICENSE("GPL");
