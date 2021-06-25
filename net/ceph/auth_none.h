<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FS_CEPH_AUTH_NONE_H
#घोषणा _FS_CEPH_AUTH_NONE_H

#समावेश <linux/slab.h>
#समावेश <linux/ceph/auth.h>

/*
 * null security mode.
 *
 * we use a single अटल authorizer that simply encodes our entity name
 * and global id.
 */

काष्ठा ceph_none_authorizer अणु
	काष्ठा ceph_authorizer base;
	अक्षर buf[128];
	पूर्णांक buf_len;
	अक्षर reply_buf[0];
पूर्ण;

काष्ठा ceph_auth_none_info अणु
	bool starting;
पूर्ण;

पूर्णांक ceph_auth_none_init(काष्ठा ceph_auth_client *ac);

#पूर्ण_अगर
