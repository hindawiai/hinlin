<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* RxRPC key type
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _KEYS_RXRPC_TYPE_H
#घोषणा _KEYS_RXRPC_TYPE_H

#समावेश <linux/key.h>

/*
 * key type क्रम AF_RXRPC keys
 */
बाह्य काष्ठा key_type key_type_rxrpc;

बाह्य काष्ठा key *rxrpc_get_null_key(स्थिर अक्षर *);

/*
 * RxRPC key क्रम Kerberos IV (type-2 security)
 */
काष्ठा rxkad_key अणु
	u32	vice_id;
	u32	start;			/* समय at which ticket starts */
	u32	expiry;			/* समय at which ticket expires */
	u32	kvno;			/* key version number */
	u8	primary_flag;		/* T अगर key क्रम primary cell क्रम this user */
	u16	ticket_len;		/* length of ticket[] */
	u8	session_key[8];		/* DES session key */
	u8	ticket[];		/* the encrypted ticket */
पूर्ण;

/*
 * list of tokens attached to an rxrpc key
 */
काष्ठा rxrpc_key_token अणु
	u16	security_index;		/* RxRPC header security index */
	bool	no_leak_key;		/* Don't copy the key to userspace */
	काष्ठा rxrpc_key_token *next;	/* the next token in the list */
	जोड़ अणु
		काष्ठा rxkad_key *kad;
	पूर्ण;
पूर्ण;

/*
 * काष्ठाure of raw payloads passed to add_key() or instantiate key
 */
काष्ठा rxrpc_key_data_v1 अणु
	u16		security_index;
	u16		ticket_length;
	u32		expiry;			/* समय_प्रकार */
	u32		kvno;
	u8		session_key[8];
	u8		ticket[];
पूर्ण;

/*
 * AF_RXRPC key payload derived from XDR क्रमmat
 * - based on खोलोafs-1.4.10/src/auth/afs_token.xg
 */
#घोषणा AFSTOKEN_LENGTH_MAX		16384	/* max payload size */
#घोषणा AFSTOKEN_STRING_MAX		256	/* max small string length */
#घोषणा AFSTOKEN_DATA_MAX		64	/* max small data length */
#घोषणा AFSTOKEN_CELL_MAX		64	/* max cellname length */
#घोषणा AFSTOKEN_MAX			8	/* max tokens per payload */
#घोषणा AFSTOKEN_BDATALN_MAX		16384	/* max big data length */
#घोषणा AFSTOKEN_RK_TIX_MAX		12000	/* max RxKAD ticket size */
#घोषणा AFSTOKEN_GK_KEY_MAX		64	/* max GSSAPI key size */
#घोषणा AFSTOKEN_GK_TOKEN_MAX		16384	/* max GSSAPI token size */

/*
 * Truncate a समय64_t to the range from 1970 to 2106 as in the network
 * protocol.
 */
अटल अंतरभूत u32 rxrpc_समय64_to_u32(समय64_t समय)
अणु
	अगर (समय < 0)
		वापस 0;

	अगर (समय > अच_पूर्णांक_उच्च)
		वापस अच_पूर्णांक_उच्च;

	वापस (u32)समय;
पूर्ण

/*
 * Extend u32 back to समय64_t using the same 1970-2106 range.
 */
अटल अंतरभूत समय64_t rxrpc_u32_to_समय64(u32 समय)
अणु
	वापस (समय64_t)समय;
पूर्ण

#पूर्ण_अगर /* _KEYS_RXRPC_TYPE_H */
