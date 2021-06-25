<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>

#समावेश <linux/ceph/decode.h>
#समावेश <linux/ceph/auth.h>

#समावेश "auth_none.h"

अटल व्योम reset(काष्ठा ceph_auth_client *ac)
अणु
	काष्ठा ceph_auth_none_info *xi = ac->निजी;

	xi->starting = true;
पूर्ण

अटल व्योम destroy(काष्ठा ceph_auth_client *ac)
अणु
	kमुक्त(ac->निजी);
	ac->निजी = शून्य;
पूर्ण

अटल पूर्णांक is_authenticated(काष्ठा ceph_auth_client *ac)
अणु
	काष्ठा ceph_auth_none_info *xi = ac->निजी;

	वापस !xi->starting;
पूर्ण

अटल पूर्णांक should_authenticate(काष्ठा ceph_auth_client *ac)
अणु
	काष्ठा ceph_auth_none_info *xi = ac->निजी;

	वापस xi->starting;
पूर्ण

अटल पूर्णांक ceph_auth_none_build_authorizer(काष्ठा ceph_auth_client *ac,
					   काष्ठा ceph_none_authorizer *au)
अणु
	व्योम *p = au->buf;
	व्योम *स्थिर end = p + माप(au->buf);
	पूर्णांक ret;

	ceph_encode_8_safe(&p, end, 1, e_range);
	ret = ceph_auth_entity_name_encode(ac->name, &p, end);
	अगर (ret < 0)
		वापस ret;

	ceph_encode_64_safe(&p, end, ac->global_id, e_range);
	au->buf_len = p - (व्योम *)au->buf;
	करोut("%s built authorizer len %d\n", __func__, au->buf_len);
	वापस 0;

e_range:
	वापस -दुस्फल;
पूर्ण

अटल पूर्णांक build_request(काष्ठा ceph_auth_client *ac, व्योम *buf, व्योम *end)
अणु
	वापस 0;
पूर्ण

/*
 * the generic auth code decode the global_id, and we carry no actual
 * authenticate state, so nothing happens here.
 */
अटल पूर्णांक handle_reply(काष्ठा ceph_auth_client *ac, पूर्णांक result,
			व्योम *buf, व्योम *end, u8 *session_key,
			पूर्णांक *session_key_len, u8 *con_secret,
			पूर्णांक *con_secret_len)
अणु
	काष्ठा ceph_auth_none_info *xi = ac->निजी;

	xi->starting = false;
	वापस result;
पूर्ण

अटल व्योम ceph_auth_none_destroy_authorizer(काष्ठा ceph_authorizer *a)
अणु
	kमुक्त(a);
पूर्ण

/*
 * build an 'authorizer' with our entity_name and global_id.  it is
 * identical क्रम all services we connect to.
 */
अटल पूर्णांक ceph_auth_none_create_authorizer(
	काष्ठा ceph_auth_client *ac, पूर्णांक peer_type,
	काष्ठा ceph_auth_handshake *auth)
अणु
	काष्ठा ceph_none_authorizer *au;
	पूर्णांक ret;

	au = kदो_स्मृति(माप(*au), GFP_NOFS);
	अगर (!au)
		वापस -ENOMEM;

	au->base.destroy = ceph_auth_none_destroy_authorizer;

	ret = ceph_auth_none_build_authorizer(ac, au);
	अगर (ret) अणु
		kमुक्त(au);
		वापस ret;
	पूर्ण

	auth->authorizer = (काष्ठा ceph_authorizer *) au;
	auth->authorizer_buf = au->buf;
	auth->authorizer_buf_len = au->buf_len;
	auth->authorizer_reply_buf = au->reply_buf;
	auth->authorizer_reply_buf_len = माप (au->reply_buf);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ceph_auth_client_ops ceph_auth_none_ops = अणु
	.reset = reset,
	.destroy = destroy,
	.is_authenticated = is_authenticated,
	.should_authenticate = should_authenticate,
	.build_request = build_request,
	.handle_reply = handle_reply,
	.create_authorizer = ceph_auth_none_create_authorizer,
पूर्ण;

पूर्णांक ceph_auth_none_init(काष्ठा ceph_auth_client *ac)
अणु
	काष्ठा ceph_auth_none_info *xi;

	करोut("ceph_auth_none_init %p\n", ac);
	xi = kzalloc(माप(*xi), GFP_NOFS);
	अगर (!xi)
		वापस -ENOMEM;

	xi->starting = true;

	ac->protocol = CEPH_AUTH_NONE;
	ac->निजी = xi;
	ac->ops = &ceph_auth_none_ops;
	वापस 0;
पूर्ण
