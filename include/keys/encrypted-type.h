<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2010 IBM Corporation
 * Copyright (C) 2010 Politecnico di Torino, Italy
 *                    TORSEC group -- https://security.polito.it
 *
 * Authors:
 * Mimi Zohar <zohar@us.ibm.com>
 * Roberto Sassu <roberto.sassu@polito.it>
 */

#अगर_अघोषित _KEYS_ENCRYPTED_TYPE_H
#घोषणा _KEYS_ENCRYPTED_TYPE_H

#समावेश <linux/key.h>
#समावेश <linux/rcupdate.h>

काष्ठा encrypted_key_payload अणु
	काष्ठा rcu_head rcu;
	अक्षर *क्रमmat;		/* datablob: क्रमmat */
	अक्षर *master_desc;	/* datablob: master key name */
	अक्षर *datalen;		/* datablob: decrypted key length */
	u8 *iv;			/* datablob: iv */
	u8 *encrypted_data;	/* datablob: encrypted data */
	अचिन्हित लघु datablob_len;	/* length of datablob */
	अचिन्हित लघु decrypted_datalen;	/* decrypted data length */
	अचिन्हित लघु payload_datalen;		/* payload data length */
	अचिन्हित लघु encrypted_key_क्रमmat;	/* encrypted key क्रमmat */
	u8 *decrypted_data;	/* decrypted data */
	u8 payload_data[];	/* payload data + datablob + hmac */
पूर्ण;

बाह्य काष्ठा key_type key_type_encrypted;

#पूर्ण_अगर /* _KEYS_ENCRYPTED_TYPE_H */
