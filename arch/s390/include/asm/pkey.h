<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Kernelspace पूर्णांकerface to the pkey device driver
 *
 * Copyright IBM Corp. 2016,2019
 *
 * Author: Harald Freudenberger <freude@de.ibm.com>
 *
 */

#अगर_अघोषित _KAPI_PKEY_H
#घोषणा _KAPI_PKEY_H

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>
#समावेश <uapi/यंत्र/pkey.h>

/*
 * In-kernel API: Transक्रमm an key blob (of any type) पूर्णांकo a रक्षित key.
 * @param key poपूर्णांकer to a buffer containing the key blob
 * @param keylen size of the key blob in bytes
 * @param protkey poपूर्णांकer to buffer receiving the रक्षित key
 * @वापस 0 on success, negative त्रुटि_सं value on failure
 */
पूर्णांक pkey_keyblob2pkey(स्थिर u8 *key, u32 keylen,
		      काष्ठा pkey_protkey *protkey);

#पूर्ण_अगर /* _KAPI_PKEY_H */
