<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Copyright (C) 2003-2006, Advanced Micro Devices, Inc.
 */

#अगर_अघोषित _GEODE_AES_H_
#घोषणा _GEODE_AES_H_

/* driver logic flags */
#घोषणा AES_MODE_ECB 0
#घोषणा AES_MODE_CBC 1

#घोषणा AES_सूची_DECRYPT 0
#घोषणा AES_सूची_ENCRYPT 1

#घोषणा AES_FLAGS_HIDDENKEY (1 << 0)

/* Register definitions */

#घोषणा AES_CTRLA_REG  0x0000

#घोषणा AES_CTRL_START     0x01
#घोषणा AES_CTRL_DECRYPT   0x00
#घोषणा AES_CTRL_ENCRYPT   0x02
#घोषणा AES_CTRL_WRKEY     0x04
#घोषणा AES_CTRL_DCA       0x08
#घोषणा AES_CTRL_SCA       0x10
#घोषणा AES_CTRL_CBC       0x20

#घोषणा AES_INTR_REG  0x0008

#घोषणा AES_INTRA_PENDING (1 << 16)
#घोषणा AES_INTRB_PENDING (1 << 17)

#घोषणा AES_INTR_PENDING  (AES_INTRA_PENDING | AES_INTRB_PENDING)
#घोषणा AES_INTR_MASK     0x07

#घोषणा AES_SOURCEA_REG   0x0010
#घोषणा AES_DSTA_REG      0x0014
#घोषणा AES_LENA_REG      0x0018
#घोषणा AES_WRITEKEY0_REG 0x0030
#घोषणा AES_WRITEIV0_REG  0x0040

/*  A very large counter that is used to gracefully bail out of an
 *  operation in हाल of trouble
 */

#घोषणा AES_OP_TIMEOUT    0x50000

काष्ठा geode_aes_tfm_ctx अणु
	u8 key[AES_KEYSIZE_128];
	जोड़ अणु
		काष्ठा crypto_skcipher *skcipher;
		काष्ठा crypto_cipher *cip;
	पूर्ण fallback;
	u32 keylen;
पूर्ण;

#पूर्ण_अगर
