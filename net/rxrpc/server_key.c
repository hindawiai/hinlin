<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* RxRPC key management
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * RxRPC keys should have a description of describing their purpose:
 *	"afs@CAMBRIDGE.REDHAT.COM>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <crypto/skcipher.h>
#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/key-type.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <net/af_rxrpc.h>
#समावेश <keys/rxrpc-type.h>
#समावेश <keys/user-type.h>
#समावेश "ar-internal.h"

अटल पूर्णांक rxrpc_vet_description_s(स्थिर अक्षर *);
अटल पूर्णांक rxrpc_preparse_s(काष्ठा key_preparsed_payload *);
अटल व्योम rxrpc_मुक्त_preparse_s(काष्ठा key_preparsed_payload *);
अटल व्योम rxrpc_destroy_s(काष्ठा key *);
अटल व्योम rxrpc_describe_s(स्थिर काष्ठा key *, काष्ठा seq_file *);

/*
 * rxrpc server keys take "<serviceId>:<securityIndex>[:<sec-specific>]" as the
 * description and the key material as the payload.
 */
काष्ठा key_type key_type_rxrpc_s = अणु
	.name		= "rxrpc_s",
	.flags		= KEY_TYPE_NET_DOMAIN,
	.vet_description = rxrpc_vet_description_s,
	.preparse	= rxrpc_preparse_s,
	.मुक्त_preparse	= rxrpc_मुक्त_preparse_s,
	.instantiate	= generic_key_instantiate,
	.destroy	= rxrpc_destroy_s,
	.describe	= rxrpc_describe_s,
पूर्ण;

/*
 * Vet the description क्रम an RxRPC server key.
 */
अटल पूर्णांक rxrpc_vet_description_s(स्थिर अक्षर *desc)
अणु
	अचिन्हित दीर्घ service, sec_class;
	अक्षर *p;

	service = simple_म_से_अदीर्घ(desc, &p, 10);
	अगर (*p != ':' || service > 65535)
		वापस -EINVAL;
	sec_class = simple_म_से_अदीर्घ(p + 1, &p, 10);
	अगर ((*p && *p != ':') || sec_class < 1 || sec_class > 255)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/*
 * Preparse a server secret key.
 */
अटल पूर्णांक rxrpc_preparse_s(काष्ठा key_preparsed_payload *prep)
अणु
	स्थिर काष्ठा rxrpc_security *sec;
	अचिन्हित पूर्णांक service, sec_class;
	पूर्णांक n;

	_enter("%zu", prep->datalen);

	अगर (!prep->orig_description)
		वापस -EINVAL;

	अगर (माला_पूछो(prep->orig_description, "%u:%u%n", &service, &sec_class, &n) != 2)
		वापस -EINVAL;

	sec = rxrpc_security_lookup(sec_class);
	अगर (!sec)
		वापस -ENOPKG;

	prep->payload.data[1] = (काष्ठा rxrpc_security *)sec;

	वापस sec->preparse_server_key(prep);
पूर्ण

अटल व्योम rxrpc_मुक्त_preparse_s(काष्ठा key_preparsed_payload *prep)
अणु
	स्थिर काष्ठा rxrpc_security *sec = prep->payload.data[1];

	अगर (sec)
		sec->मुक्त_preparse_server_key(prep);
पूर्ण

अटल व्योम rxrpc_destroy_s(काष्ठा key *key)
अणु
	स्थिर काष्ठा rxrpc_security *sec = key->payload.data[1];

	अगर (sec)
		sec->destroy_server_key(key);
पूर्ण

अटल व्योम rxrpc_describe_s(स्थिर काष्ठा key *key, काष्ठा seq_file *m)
अणु
	स्थिर काष्ठा rxrpc_security *sec = key->payload.data[1];

	seq_माला_दो(m, key->description);
	अगर (sec && sec->describe_server_key)
		sec->describe_server_key(key, m);
पूर्ण

/*
 * grab the security keyring क्रम a server socket
 */
पूर्णांक rxrpc_server_keyring(काष्ठा rxrpc_sock *rx, sockptr_t optval, पूर्णांक optlen)
अणु
	काष्ठा key *key;
	अक्षर *description;

	_enter("");

	अगर (optlen <= 0 || optlen > PAGE_SIZE - 1)
		वापस -EINVAL;

	description = memdup_sockptr_nul(optval, optlen);
	अगर (IS_ERR(description))
		वापस PTR_ERR(description);

	key = request_key(&key_type_keyring, description, शून्य);
	अगर (IS_ERR(key)) अणु
		kमुक्त(description);
		_leave(" = %ld", PTR_ERR(key));
		वापस PTR_ERR(key);
	पूर्ण

	rx->securities = key;
	kमुक्त(description);
	_leave(" = 0 [key %x]", key->serial);
	वापस 0;
पूर्ण
