<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Quick & dirty crypto testing module.
 *
 * This will only exist until we have a better testing mechanism
 * (e.g. a अक्षर device).
 *
 * Copyright (c) 2002 James Morris <jmorris@पूर्णांकercode.com.au>
 * Copyright (c) 2002 Jean-Francois Dive <jef@linuxbe.org>
 * Copyright (c) 2007 Nokia Siemens Networks
 */
#अगर_अघोषित _CRYPTO_TCRYPT_H
#घोषणा _CRYPTO_TCRYPT_H

काष्ठा cipher_speed_ढाँचा अणु
	स्थिर अक्षर *key;
	अचिन्हित पूर्णांक klen;
पूर्ण;

काष्ठा aead_speed_ढाँचा अणु
	स्थिर अक्षर *key;
	अचिन्हित पूर्णांक klen;
पूर्ण;

काष्ठा hash_speed अणु
	अचिन्हित पूर्णांक blen;	/* buffer length */
	अचिन्हित पूर्णांक plen;	/* per-update length */
पूर्ण;

/*
 * DES test vectors.
 */
#घोषणा DES3_SPEED_VECTORS	1

अटल काष्ठा cipher_speed_ढाँचा des3_speed_ढाँचा[] = अणु
	अणु
		.key	= "\x01\x23\x45\x67\x89\xab\xcd\xef"
			  "\x55\x55\x55\x55\x55\x55\x55\x55"
			  "\xfe\xdc\xba\x98\x76\x54\x32\x10",
		.klen	= 24,
	पूर्ण
पूर्ण;

/*
 * Cipher speed tests
 */
अटल u8 speed_ढाँचा_8[] = अणु8, 0पूर्ण;
अटल u8 speed_ढाँचा_16[] = अणु16, 0पूर्ण;
अटल u8 speed_ढाँचा_24[] = अणु24, 0पूर्ण;
अटल u8 speed_ढाँचा_8_16[] = अणु8, 16, 0पूर्ण;
अटल u8 speed_ढाँचा_8_32[] = अणु8, 32, 0पूर्ण;
अटल u8 speed_ढाँचा_16_32[] = अणु16, 32, 0पूर्ण;
अटल u8 speed_ढाँचा_16_24_32[] = अणु16, 24, 32, 0पूर्ण;
अटल u8 speed_ढाँचा_20_28_36[] = अणु20, 28, 36, 0पूर्ण;
अटल u8 speed_ढाँचा_32_40_48[] = अणु32, 40, 48, 0पूर्ण;
अटल u8 speed_ढाँचा_32_48[] = अणु32, 48, 0पूर्ण;
अटल u8 speed_ढाँचा_32_48_64[] = अणु32, 48, 64, 0पूर्ण;
अटल u8 speed_ढाँचा_32_64[] = अणु32, 64, 0पूर्ण;
अटल u8 speed_ढाँचा_32[] = अणु32, 0पूर्ण;

/*
 * AEAD speed tests
 */
अटल u8 aead_speed_ढाँचा_19[] = अणु19, 0पूर्ण;
अटल u8 aead_speed_ढाँचा_20[] = अणु20, 0पूर्ण;
अटल u8 aead_speed_ढाँचा_36[] = अणु36, 0पूर्ण;

/*
 * Digest speed tests
 */
अटल काष्ठा hash_speed generic_hash_speed_ढाँचा[] = अणु
	अणु .blen = 16,	.plen = 16, पूर्ण,
	अणु .blen = 64,	.plen = 16, पूर्ण,
	अणु .blen = 64,	.plen = 64, पूर्ण,
	अणु .blen = 256,	.plen = 16, पूर्ण,
	अणु .blen = 256,	.plen = 64, पूर्ण,
	अणु .blen = 256,	.plen = 256, पूर्ण,
	अणु .blen = 1024,	.plen = 16, पूर्ण,
	अणु .blen = 1024,	.plen = 256, पूर्ण,
	अणु .blen = 1024,	.plen = 1024, पूर्ण,
	अणु .blen = 2048,	.plen = 16, पूर्ण,
	अणु .blen = 2048,	.plen = 256, पूर्ण,
	अणु .blen = 2048,	.plen = 1024, पूर्ण,
	अणु .blen = 2048,	.plen = 2048, पूर्ण,
	अणु .blen = 4096,	.plen = 16, पूर्ण,
	अणु .blen = 4096,	.plen = 256, पूर्ण,
	अणु .blen = 4096,	.plen = 1024, पूर्ण,
	अणु .blen = 4096,	.plen = 4096, पूर्ण,
	अणु .blen = 8192,	.plen = 16, पूर्ण,
	अणु .blen = 8192,	.plen = 256, पूर्ण,
	अणु .blen = 8192,	.plen = 1024, पूर्ण,
	अणु .blen = 8192,	.plen = 4096, पूर्ण,
	अणु .blen = 8192,	.plen = 8192, पूर्ण,

	/* End marker */
	अणु  .blen = 0,	.plen = 0, पूर्ण
पूर्ण;

अटल काष्ठा hash_speed poly1305_speed_ढाँचा[] = अणु
	अणु .blen = 96,	.plen = 16, पूर्ण,
	अणु .blen = 96,	.plen = 32, पूर्ण,
	अणु .blen = 96,	.plen = 96, पूर्ण,
	अणु .blen = 288,	.plen = 16, पूर्ण,
	अणु .blen = 288,	.plen = 32, पूर्ण,
	अणु .blen = 288,	.plen = 288, पूर्ण,
	अणु .blen = 1056,	.plen = 32, पूर्ण,
	अणु .blen = 1056,	.plen = 1056, पूर्ण,
	अणु .blen = 2080,	.plen = 32, पूर्ण,
	अणु .blen = 2080,	.plen = 2080, पूर्ण,
	अणु .blen = 4128,	.plen = 4128, पूर्ण,
	अणु .blen = 8224,	.plen = 8224, पूर्ण,

	/* End marker */
	अणु  .blen = 0,	.plen = 0, पूर्ण
पूर्ण;

#पूर्ण_अगर	/* _CRYPTO_TCRYPT_H */
