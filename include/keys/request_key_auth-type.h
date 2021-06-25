<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* request_key authorisation token key type
 *
 * Copyright (C) 2005 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _KEYS_REQUEST_KEY_AUTH_TYPE_H
#घोषणा _KEYS_REQUEST_KEY_AUTH_TYPE_H

#समावेश <linux/key.h>

/*
 * Authorisation record क्रम request_key().
 */
काष्ठा request_key_auth अणु
	काष्ठा rcu_head		rcu;
	काष्ठा key		*target_key;
	काष्ठा key		*dest_keyring;
	स्थिर काष्ठा cred	*cred;
	व्योम			*callout_info;
	माप_प्रकार			callout_len;
	pid_t			pid;
	अक्षर			op[8];
पूर्ण __अक्रमomize_layout;

अटल अंतरभूत काष्ठा request_key_auth *get_request_key_auth(स्थिर काष्ठा key *key)
अणु
	वापस key->payload.data[0];
पूर्ण


#पूर्ण_अगर /* _KEYS_REQUEST_KEY_AUTH_TYPE_H */
