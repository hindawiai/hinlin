<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FS_CEPH_AUTH_X_H
#घोषणा _FS_CEPH_AUTH_X_H

#समावेश <linux/rbtree.h>

#समावेश <linux/ceph/auth.h>

#समावेश "crypto.h"
#समावेश "auth_x_protocol.h"

/*
 * Handle ticket क्रम a single service.
 */
काष्ठा ceph_x_ticket_handler अणु
	काष्ठा rb_node node;
	अचिन्हित पूर्णांक service;

	काष्ठा ceph_crypto_key session_key;
	bool have_key;

	u64 secret_id;
	काष्ठा ceph_buffer *ticket_blob;

	समय64_t renew_after, expires;
पूर्ण;

#घोषणा CEPHX_AU_ENC_BUF_LEN	128  /* big enough क्रम encrypted blob */

काष्ठा ceph_x_authorizer अणु
	काष्ठा ceph_authorizer base;
	काष्ठा ceph_crypto_key session_key;
	काष्ठा ceph_buffer *buf;
	अचिन्हित पूर्णांक service;
	u64 nonce;
	u64 secret_id;
	अक्षर enc_buf[CEPHX_AU_ENC_BUF_LEN] __aligned(8);
पूर्ण;

काष्ठा ceph_x_info अणु
	काष्ठा ceph_crypto_key secret;

	bool starting;
	u64 server_challenge;

	अचिन्हित पूर्णांक have_keys;
	काष्ठा rb_root ticket_handlers;

	काष्ठा ceph_x_authorizer auth_authorizer;
पूर्ण;

पूर्णांक ceph_x_init(काष्ठा ceph_auth_client *ac);

#पूर्ण_अगर
