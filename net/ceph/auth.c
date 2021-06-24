<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>

#समावेश <linux/ceph/types.h>
#समावेश <linux/ceph/decode.h>
#समावेश <linux/ceph/libceph.h>
#समावेश <linux/ceph/messenger.h>
#समावेश "auth_none.h"
#समावेश "auth_x.h"


/*
 * get protocol handler
 */
अटल u32 supported_protocols[] = अणु
	CEPH_AUTH_NONE,
	CEPH_AUTH_CEPHX
पूर्ण;

अटल पूर्णांक init_protocol(काष्ठा ceph_auth_client *ac, पूर्णांक proto)
अणु
	करोut("%s proto %d\n", __func__, proto);

	चयन (proto) अणु
	हाल CEPH_AUTH_NONE:
		वापस ceph_auth_none_init(ac);
	हाल CEPH_AUTH_CEPHX:
		वापस ceph_x_init(ac);
	शेष:
		pr_err("bad auth protocol %d\n", proto);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम set_global_id(काष्ठा ceph_auth_client *ac, u64 global_id)
अणु
	करोut("%s global_id %llu\n", __func__, global_id);

	अगर (!global_id)
		pr_err("got zero global_id\n");

	अगर (ac->global_id && global_id != ac->global_id)
		pr_err("global_id changed from %llu to %llu\n", ac->global_id,
		       global_id);

	ac->global_id = global_id;
पूर्ण

/*
 * setup, tearकरोwn.
 */
काष्ठा ceph_auth_client *ceph_auth_init(स्थिर अक्षर *name,
					स्थिर काष्ठा ceph_crypto_key *key,
					स्थिर पूर्णांक *con_modes)
अणु
	काष्ठा ceph_auth_client *ac;
	पूर्णांक ret;

	ret = -ENOMEM;
	ac = kzalloc(माप(*ac), GFP_NOFS);
	अगर (!ac)
		जाओ out;

	mutex_init(&ac->mutex);
	ac->negotiating = true;
	अगर (name)
		ac->name = name;
	अन्यथा
		ac->name = CEPH_AUTH_NAME_DEFAULT;
	ac->key = key;
	ac->preferred_mode = con_modes[0];
	ac->fallback_mode = con_modes[1];

	करोut("%s name '%s' preferred_mode %d fallback_mode %d\n", __func__,
	     ac->name, ac->preferred_mode, ac->fallback_mode);
	वापस ac;

out:
	वापस ERR_PTR(ret);
पूर्ण

व्योम ceph_auth_destroy(काष्ठा ceph_auth_client *ac)
अणु
	करोut("auth_destroy %p\n", ac);
	अगर (ac->ops)
		ac->ops->destroy(ac);
	kमुक्त(ac);
पूर्ण

/*
 * Reset occurs when reconnecting to the monitor.
 */
व्योम ceph_auth_reset(काष्ठा ceph_auth_client *ac)
अणु
	mutex_lock(&ac->mutex);
	करोut("auth_reset %p\n", ac);
	अगर (ac->ops && !ac->negotiating)
		ac->ops->reset(ac);
	ac->negotiating = true;
	mutex_unlock(&ac->mutex);
पूर्ण

/*
 * EntityName, not to be confused with entity_name_t
 */
पूर्णांक ceph_auth_entity_name_encode(स्थिर अक्षर *name, व्योम **p, व्योम *end)
अणु
	पूर्णांक len = म_माप(name);

	अगर (*p + 2*माप(u32) + len > end)
		वापस -दुस्फल;
	ceph_encode_32(p, CEPH_ENTITY_TYPE_CLIENT);
	ceph_encode_32(p, len);
	ceph_encode_copy(p, name, len);
	वापस 0;
पूर्ण

/*
 * Initiate protocol negotiation with monitor.  Include entity name
 * and list supported protocols.
 */
पूर्णांक ceph_auth_build_hello(काष्ठा ceph_auth_client *ac, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा ceph_mon_request_header *monhdr = buf;
	व्योम *p = monhdr + 1, *end = buf + len, *lenp;
	पूर्णांक i, num;
	पूर्णांक ret;

	mutex_lock(&ac->mutex);
	करोut("auth_build_hello\n");
	monhdr->have_version = 0;
	monhdr->session_mon = cpu_to_le16(-1);
	monhdr->session_mon_tid = 0;

	ceph_encode_32(&p, CEPH_AUTH_UNKNOWN);  /* no protocol, yet */

	lenp = p;
	p += माप(u32);

	ceph_decode_need(&p, end, 1 + माप(u32), bad);
	ceph_encode_8(&p, 1);
	num = ARRAY_SIZE(supported_protocols);
	ceph_encode_32(&p, num);
	ceph_decode_need(&p, end, num * माप(u32), bad);
	क्रम (i = 0; i < num; i++)
		ceph_encode_32(&p, supported_protocols[i]);

	ret = ceph_auth_entity_name_encode(ac->name, &p, end);
	अगर (ret < 0)
		जाओ out;
	ceph_decode_need(&p, end, माप(u64), bad);
	ceph_encode_64(&p, ac->global_id);

	ceph_encode_32(&lenp, p - lenp - माप(u32));
	ret = p - buf;
out:
	mutex_unlock(&ac->mutex);
	वापस ret;

bad:
	ret = -दुस्फल;
	जाओ out;
पूर्ण

अटल पूर्णांक build_request(काष्ठा ceph_auth_client *ac, bool add_header,
			 व्योम *buf, पूर्णांक buf_len)
अणु
	व्योम *end = buf + buf_len;
	व्योम *p;
	पूर्णांक ret;

	p = buf;
	अगर (add_header) अणु
		/* काष्ठा ceph_mon_request_header + protocol */
		ceph_encode_64_safe(&p, end, 0, e_range);
		ceph_encode_16_safe(&p, end, -1, e_range);
		ceph_encode_64_safe(&p, end, 0, e_range);
		ceph_encode_32_safe(&p, end, ac->protocol, e_range);
	पूर्ण

	ceph_encode_need(&p, end, माप(u32), e_range);
	ret = ac->ops->build_request(ac, p + माप(u32), end);
	अगर (ret < 0) अणु
		pr_err("auth protocol '%s' building request failed: %d\n",
		       ceph_auth_proto_name(ac->protocol), ret);
		वापस ret;
	पूर्ण
	करोut(" built request %d bytes\n", ret);
	ceph_encode_32(&p, ret);
	वापस p + ret - buf;

e_range:
	वापस -दुस्फल;
पूर्ण

/*
 * Handle auth message from monitor.
 */
पूर्णांक ceph_handle_auth_reply(काष्ठा ceph_auth_client *ac,
			   व्योम *buf, माप_प्रकार len,
			   व्योम *reply_buf, माप_प्रकार reply_len)
अणु
	व्योम *p = buf;
	व्योम *end = buf + len;
	पूर्णांक protocol;
	s32 result;
	u64 global_id;
	व्योम *payload, *payload_end;
	पूर्णांक payload_len;
	अक्षर *result_msg;
	पूर्णांक result_msg_len;
	पूर्णांक ret = -EINVAL;

	mutex_lock(&ac->mutex);
	करोut("handle_auth_reply %p %p\n", p, end);
	ceph_decode_need(&p, end, माप(u32) * 3 + माप(u64), bad);
	protocol = ceph_decode_32(&p);
	result = ceph_decode_32(&p);
	global_id = ceph_decode_64(&p);
	payload_len = ceph_decode_32(&p);
	payload = p;
	p += payload_len;
	ceph_decode_need(&p, end, माप(u32), bad);
	result_msg_len = ceph_decode_32(&p);
	result_msg = p;
	p += result_msg_len;
	अगर (p != end)
		जाओ bad;

	करोut(" result %d '%.*s' gid %llu len %d\n", result, result_msg_len,
	     result_msg, global_id, payload_len);

	payload_end = payload + payload_len;

	अगर (ac->negotiating) अणु
		/* server करोes not support our protocols? */
		अगर (!protocol && result < 0) अणु
			ret = result;
			जाओ out;
		पूर्ण
		/* set up (new) protocol handler? */
		अगर (ac->protocol && ac->protocol != protocol) अणु
			ac->ops->destroy(ac);
			ac->protocol = 0;
			ac->ops = शून्य;
		पूर्ण
		अगर (ac->protocol != protocol) अणु
			ret = init_protocol(ac, protocol);
			अगर (ret) अणु
				pr_err("auth protocol '%s' init failed: %d\n",
				       ceph_auth_proto_name(protocol), ret);
				जाओ out;
			पूर्ण
		पूर्ण

		ac->negotiating = false;
	पूर्ण

	ret = ac->ops->handle_reply(ac, result, payload, payload_end,
				    शून्य, शून्य, शून्य, शून्य);
	अगर (ret == -EAGAIN) अणु
		ret = build_request(ac, true, reply_buf, reply_len);
		जाओ out;
	पूर्ण अन्यथा अगर (ret) अणु
		pr_err("auth protocol '%s' mauth authentication failed: %d\n",
		       ceph_auth_proto_name(ac->protocol), result);
		जाओ out;
	पूर्ण

	set_global_id(ac, global_id);

out:
	mutex_unlock(&ac->mutex);
	वापस ret;

bad:
	pr_err("failed to decode auth msg\n");
	ret = -EINVAL;
	जाओ out;
पूर्ण

पूर्णांक ceph_build_auth(काष्ठा ceph_auth_client *ac,
		    व्योम *msg_buf, माप_प्रकार msg_len)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&ac->mutex);
	अगर (ac->ops->should_authenticate(ac))
		ret = build_request(ac, true, msg_buf, msg_len);
	mutex_unlock(&ac->mutex);
	वापस ret;
पूर्ण

पूर्णांक ceph_auth_is_authenticated(काष्ठा ceph_auth_client *ac)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&ac->mutex);
	अगर (ac->ops)
		ret = ac->ops->is_authenticated(ac);
	mutex_unlock(&ac->mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ceph_auth_is_authenticated);

पूर्णांक __ceph_auth_get_authorizer(काष्ठा ceph_auth_client *ac,
			       काष्ठा ceph_auth_handshake *auth,
			       पूर्णांक peer_type, bool क्रमce_new,
			       पूर्णांक *proto, पूर्णांक *pref_mode, पूर्णांक *fallb_mode)
अणु
	पूर्णांक ret;

	mutex_lock(&ac->mutex);
	अगर (क्रमce_new && auth->authorizer) अणु
		ceph_auth_destroy_authorizer(auth->authorizer);
		auth->authorizer = शून्य;
	पूर्ण
	अगर (!auth->authorizer)
		ret = ac->ops->create_authorizer(ac, peer_type, auth);
	अन्यथा अगर (ac->ops->update_authorizer)
		ret = ac->ops->update_authorizer(ac, peer_type, auth);
	अन्यथा
		ret = 0;
	अगर (ret)
		जाओ out;

	*proto = ac->protocol;
	अगर (pref_mode && fallb_mode) अणु
		*pref_mode = ac->preferred_mode;
		*fallb_mode = ac->fallback_mode;
	पूर्ण

out:
	mutex_unlock(&ac->mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(__ceph_auth_get_authorizer);

व्योम ceph_auth_destroy_authorizer(काष्ठा ceph_authorizer *a)
अणु
	a->destroy(a);
पूर्ण
EXPORT_SYMBOL(ceph_auth_destroy_authorizer);

पूर्णांक ceph_auth_add_authorizer_challenge(काष्ठा ceph_auth_client *ac,
				       काष्ठा ceph_authorizer *a,
				       व्योम *challenge_buf,
				       पूर्णांक challenge_buf_len)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&ac->mutex);
	अगर (ac->ops && ac->ops->add_authorizer_challenge)
		ret = ac->ops->add_authorizer_challenge(ac, a, challenge_buf,
							challenge_buf_len);
	mutex_unlock(&ac->mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ceph_auth_add_authorizer_challenge);

पूर्णांक ceph_auth_verअगरy_authorizer_reply(काष्ठा ceph_auth_client *ac,
				      काष्ठा ceph_authorizer *a,
				      व्योम *reply, पूर्णांक reply_len,
				      u8 *session_key, पूर्णांक *session_key_len,
				      u8 *con_secret, पूर्णांक *con_secret_len)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&ac->mutex);
	अगर (ac->ops && ac->ops->verअगरy_authorizer_reply)
		ret = ac->ops->verअगरy_authorizer_reply(ac, a,
			reply, reply_len, session_key, session_key_len,
			con_secret, con_secret_len);
	mutex_unlock(&ac->mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ceph_auth_verअगरy_authorizer_reply);

व्योम ceph_auth_invalidate_authorizer(काष्ठा ceph_auth_client *ac, पूर्णांक peer_type)
अणु
	mutex_lock(&ac->mutex);
	अगर (ac->ops && ac->ops->invalidate_authorizer)
		ac->ops->invalidate_authorizer(ac, peer_type);
	mutex_unlock(&ac->mutex);
पूर्ण
EXPORT_SYMBOL(ceph_auth_invalidate_authorizer);

/*
 * msgr2 authentication
 */

अटल bool contains(स्थिर पूर्णांक *arr, पूर्णांक cnt, पूर्णांक val)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cnt; i++) अणु
		अगर (arr[i] == val)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक encode_con_modes(व्योम **p, व्योम *end, पूर्णांक pref_mode, पूर्णांक fallb_mode)
अणु
	WARN_ON(pref_mode == CEPH_CON_MODE_UNKNOWN);
	अगर (fallb_mode != CEPH_CON_MODE_UNKNOWN) अणु
		ceph_encode_32_safe(p, end, 2, e_range);
		ceph_encode_32_safe(p, end, pref_mode, e_range);
		ceph_encode_32_safe(p, end, fallb_mode, e_range);
	पूर्ण अन्यथा अणु
		ceph_encode_32_safe(p, end, 1, e_range);
		ceph_encode_32_safe(p, end, pref_mode, e_range);
	पूर्ण

	वापस 0;

e_range:
	वापस -दुस्फल;
पूर्ण

/*
 * Similar to ceph_auth_build_hello().
 */
पूर्णांक ceph_auth_get_request(काष्ठा ceph_auth_client *ac, व्योम *buf, पूर्णांक buf_len)
अणु
	पूर्णांक proto = ac->key ? CEPH_AUTH_CEPHX : CEPH_AUTH_NONE;
	व्योम *end = buf + buf_len;
	व्योम *lenp;
	व्योम *p;
	पूर्णांक ret;

	mutex_lock(&ac->mutex);
	अगर (ac->protocol == CEPH_AUTH_UNKNOWN) अणु
		ret = init_protocol(ac, proto);
		अगर (ret) अणु
			pr_err("auth protocol '%s' init failed: %d\n",
			       ceph_auth_proto_name(proto), ret);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		WARN_ON(ac->protocol != proto);
		ac->ops->reset(ac);
	पूर्ण

	p = buf;
	ceph_encode_32_safe(&p, end, ac->protocol, e_range);
	ret = encode_con_modes(&p, end, ac->preferred_mode, ac->fallback_mode);
	अगर (ret)
		जाओ out;

	lenp = p;
	p += 4;  /* space क्रम len */

	ceph_encode_8_safe(&p, end, CEPH_AUTH_MODE_MON, e_range);
	ret = ceph_auth_entity_name_encode(ac->name, &p, end);
	अगर (ret)
		जाओ out;

	ceph_encode_64_safe(&p, end, ac->global_id, e_range);
	ceph_encode_32(&lenp, p - lenp - 4);
	ret = p - buf;

out:
	mutex_unlock(&ac->mutex);
	वापस ret;

e_range:
	ret = -दुस्फल;
	जाओ out;
पूर्ण

पूर्णांक ceph_auth_handle_reply_more(काष्ठा ceph_auth_client *ac, व्योम *reply,
				पूर्णांक reply_len, व्योम *buf, पूर्णांक buf_len)
अणु
	पूर्णांक ret;

	mutex_lock(&ac->mutex);
	ret = ac->ops->handle_reply(ac, 0, reply, reply + reply_len,
				    शून्य, शून्य, शून्य, शून्य);
	अगर (ret == -EAGAIN)
		ret = build_request(ac, false, buf, buf_len);
	अन्यथा
		WARN_ON(ret >= 0);
	mutex_unlock(&ac->mutex);
	वापस ret;
पूर्ण

पूर्णांक ceph_auth_handle_reply_करोne(काष्ठा ceph_auth_client *ac,
				u64 global_id, व्योम *reply, पूर्णांक reply_len,
				u8 *session_key, पूर्णांक *session_key_len,
				u8 *con_secret, पूर्णांक *con_secret_len)
अणु
	पूर्णांक ret;

	mutex_lock(&ac->mutex);
	ret = ac->ops->handle_reply(ac, 0, reply, reply + reply_len,
				    session_key, session_key_len,
				    con_secret, con_secret_len);
	अगर (!ret)
		set_global_id(ac, global_id);
	mutex_unlock(&ac->mutex);
	वापस ret;
पूर्ण

bool ceph_auth_handle_bad_method(काष्ठा ceph_auth_client *ac,
				 पूर्णांक used_proto, पूर्णांक result,
				 स्थिर पूर्णांक *allowed_protos, पूर्णांक proto_cnt,
				 स्थिर पूर्णांक *allowed_modes, पूर्णांक mode_cnt)
अणु
	mutex_lock(&ac->mutex);
	WARN_ON(used_proto != ac->protocol);

	अगर (result == -EOPNOTSUPP) अणु
		अगर (!contains(allowed_protos, proto_cnt, ac->protocol)) अणु
			pr_err("auth protocol '%s' not allowed\n",
			       ceph_auth_proto_name(ac->protocol));
			जाओ not_allowed;
		पूर्ण
		अगर (!contains(allowed_modes, mode_cnt, ac->preferred_mode) &&
		    (ac->fallback_mode == CEPH_CON_MODE_UNKNOWN ||
		     !contains(allowed_modes, mode_cnt, ac->fallback_mode))) अणु
			pr_err("preferred mode '%s' not allowed\n",
			       ceph_con_mode_name(ac->preferred_mode));
			अगर (ac->fallback_mode == CEPH_CON_MODE_UNKNOWN)
				pr_err("no fallback mode\n");
			अन्यथा
				pr_err("fallback mode '%s' not allowed\n",
				       ceph_con_mode_name(ac->fallback_mode));
			जाओ not_allowed;
		पूर्ण
	पूर्ण

	WARN_ON(result == -EOPNOTSUPP || result >= 0);
	pr_err("auth protocol '%s' msgr authentication failed: %d\n",
	       ceph_auth_proto_name(ac->protocol), result);

	mutex_unlock(&ac->mutex);
	वापस true;

not_allowed:
	mutex_unlock(&ac->mutex);
	वापस false;
पूर्ण

पूर्णांक ceph_auth_get_authorizer(काष्ठा ceph_auth_client *ac,
			     काष्ठा ceph_auth_handshake *auth,
			     पूर्णांक peer_type, व्योम *buf, पूर्णांक *buf_len)
अणु
	व्योम *end = buf + *buf_len;
	पूर्णांक pref_mode, fallb_mode;
	पूर्णांक proto;
	व्योम *p;
	पूर्णांक ret;

	ret = __ceph_auth_get_authorizer(ac, auth, peer_type, true, &proto,
					 &pref_mode, &fallb_mode);
	अगर (ret)
		वापस ret;

	p = buf;
	ceph_encode_32_safe(&p, end, proto, e_range);
	ret = encode_con_modes(&p, end, pref_mode, fallb_mode);
	अगर (ret)
		वापस ret;

	ceph_encode_32_safe(&p, end, auth->authorizer_buf_len, e_range);
	*buf_len = p - buf;
	वापस 0;

e_range:
	वापस -दुस्फल;
पूर्ण
EXPORT_SYMBOL(ceph_auth_get_authorizer);

पूर्णांक ceph_auth_handle_svc_reply_more(काष्ठा ceph_auth_client *ac,
				    काष्ठा ceph_auth_handshake *auth,
				    व्योम *reply, पूर्णांक reply_len,
				    व्योम *buf, पूर्णांक *buf_len)
अणु
	व्योम *end = buf + *buf_len;
	व्योम *p;
	पूर्णांक ret;

	ret = ceph_auth_add_authorizer_challenge(ac, auth->authorizer,
						 reply, reply_len);
	अगर (ret)
		वापस ret;

	p = buf;
	ceph_encode_32_safe(&p, end, auth->authorizer_buf_len, e_range);
	*buf_len = p - buf;
	वापस 0;

e_range:
	वापस -दुस्फल;
पूर्ण
EXPORT_SYMBOL(ceph_auth_handle_svc_reply_more);

पूर्णांक ceph_auth_handle_svc_reply_करोne(काष्ठा ceph_auth_client *ac,
				    काष्ठा ceph_auth_handshake *auth,
				    व्योम *reply, पूर्णांक reply_len,
				    u8 *session_key, पूर्णांक *session_key_len,
				    u8 *con_secret, पूर्णांक *con_secret_len)
अणु
	वापस ceph_auth_verअगरy_authorizer_reply(ac, auth->authorizer,
		reply, reply_len, session_key, session_key_len,
		con_secret, con_secret_len);
पूर्ण
EXPORT_SYMBOL(ceph_auth_handle_svc_reply_करोne);

bool ceph_auth_handle_bad_authorizer(काष्ठा ceph_auth_client *ac,
				     पूर्णांक peer_type, पूर्णांक used_proto, पूर्णांक result,
				     स्थिर पूर्णांक *allowed_protos, पूर्णांक proto_cnt,
				     स्थिर पूर्णांक *allowed_modes, पूर्णांक mode_cnt)
अणु
	mutex_lock(&ac->mutex);
	WARN_ON(used_proto != ac->protocol);

	अगर (result == -EOPNOTSUPP) अणु
		अगर (!contains(allowed_protos, proto_cnt, ac->protocol)) अणु
			pr_err("auth protocol '%s' not allowed by %s\n",
			       ceph_auth_proto_name(ac->protocol),
			       ceph_entity_type_name(peer_type));
			जाओ not_allowed;
		पूर्ण
		अगर (!contains(allowed_modes, mode_cnt, ac->preferred_mode) &&
		    (ac->fallback_mode == CEPH_CON_MODE_UNKNOWN ||
		     !contains(allowed_modes, mode_cnt, ac->fallback_mode))) अणु
			pr_err("preferred mode '%s' not allowed by %s\n",
			       ceph_con_mode_name(ac->preferred_mode),
			       ceph_entity_type_name(peer_type));
			अगर (ac->fallback_mode == CEPH_CON_MODE_UNKNOWN)
				pr_err("no fallback mode\n");
			अन्यथा
				pr_err("fallback mode '%s' not allowed by %s\n",
				       ceph_con_mode_name(ac->fallback_mode),
				       ceph_entity_type_name(peer_type));
			जाओ not_allowed;
		पूर्ण
	पूर्ण

	WARN_ON(result == -EOPNOTSUPP || result >= 0);
	pr_err("auth protocol '%s' authorization to %s failed: %d\n",
	       ceph_auth_proto_name(ac->protocol),
	       ceph_entity_type_name(peer_type), result);

	अगर (ac->ops->invalidate_authorizer)
		ac->ops->invalidate_authorizer(ac, peer_type);

	mutex_unlock(&ac->mutex);
	वापस true;

not_allowed:
	mutex_unlock(&ac->mutex);
	वापस false;
पूर्ण
EXPORT_SYMBOL(ceph_auth_handle_bad_authorizer);
