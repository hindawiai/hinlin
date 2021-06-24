<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Big capacity key type.
 *
 * Copyright (C) 2013 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _KEYS_BIG_KEY_TYPE_H
#घोषणा _KEYS_BIG_KEY_TYPE_H

#समावेश <linux/key-type.h>

बाह्य काष्ठा key_type key_type_big_key;

बाह्य पूर्णांक big_key_preparse(काष्ठा key_preparsed_payload *prep);
बाह्य व्योम big_key_मुक्त_preparse(काष्ठा key_preparsed_payload *prep);
बाह्य व्योम big_key_revoke(काष्ठा key *key);
बाह्य व्योम big_key_destroy(काष्ठा key *key);
बाह्य व्योम big_key_describe(स्थिर काष्ठा key *big_key, काष्ठा seq_file *m);
बाह्य दीर्घ big_key_पढ़ो(स्थिर काष्ठा key *key, अक्षर *buffer, माप_प्रकार buflen);
बाह्य पूर्णांक big_key_update(काष्ठा key *key, काष्ठा key_preparsed_payload *prep);

#पूर्ण_अगर /* _KEYS_BIG_KEY_TYPE_H */
