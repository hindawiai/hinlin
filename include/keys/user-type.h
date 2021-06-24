<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* user-type.h: User-defined key type
 *
 * Copyright (C) 2005 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _KEYS_USER_TYPE_H
#घोषणा _KEYS_USER_TYPE_H

#समावेश <linux/key.h>
#समावेश <linux/rcupdate.h>

#अगर_घोषित CONFIG_KEYS

/*****************************************************************************/
/*
 * the payload क्रम a key of type "user" or "logon"
 * - once filled in and attached to a key:
 *   - the payload काष्ठा is invariant may not be changed, only replaced
 *   - the payload must be पढ़ो with RCU procedures or with the key semaphore
 *     held
 *   - the payload may only be replaced with the key semaphore ग_लिखो-locked
 * - the key's data length is the size of the actual data, not including the
 *   payload wrapper
 */
काष्ठा user_key_payload अणु
	काष्ठा rcu_head	rcu;		/* RCU deकाष्ठाor */
	अचिन्हित लघु	datalen;	/* length of this data */
	अक्षर		data[] __aligned(__alignof__(u64)); /* actual data */
पूर्ण;

बाह्य काष्ठा key_type key_type_user;
बाह्य काष्ठा key_type key_type_logon;

काष्ठा key_preparsed_payload;

बाह्य पूर्णांक user_preparse(काष्ठा key_preparsed_payload *prep);
बाह्य व्योम user_मुक्त_preparse(काष्ठा key_preparsed_payload *prep);
बाह्य पूर्णांक user_update(काष्ठा key *key, काष्ठा key_preparsed_payload *prep);
बाह्य व्योम user_revoke(काष्ठा key *key);
बाह्य व्योम user_destroy(काष्ठा key *key);
बाह्य व्योम user_describe(स्थिर काष्ठा key *user, काष्ठा seq_file *m);
बाह्य दीर्घ user_पढ़ो(स्थिर काष्ठा key *key, अक्षर *buffer, माप_प्रकार buflen);

अटल अंतरभूत स्थिर काष्ठा user_key_payload *user_key_payload_rcu(स्थिर काष्ठा key *key)
अणु
	वापस (काष्ठा user_key_payload *)dereference_key_rcu(key);
पूर्ण

अटल अंतरभूत काष्ठा user_key_payload *user_key_payload_locked(स्थिर काष्ठा key *key)
अणु
	वापस (काष्ठा user_key_payload *)dereference_key_locked((काष्ठा key *)key);
पूर्ण

#पूर्ण_अगर /* CONFIG_KEYS */

#पूर्ण_अगर /* _KEYS_USER_TYPE_H */
