<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Key to pathname encoder
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/slab.h>
#समावेश "internal.h"

अटल स्थिर अक्षर cachefiles_अक्षरmap[64] =
	"0123456789"			/* 0 - 9 */
	"abcdefghijklmnopqrstuvwxyz"	/* 10 - 35 */
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"	/* 36 - 61 */
	"_-"				/* 62 - 63 */
	;

अटल स्थिर अक्षर cachefiles_fileअक्षरmap[256] = अणु
	/* we skip space and tab and control अक्षरs */
	[33 ... 46] = 1,		/* '!' -> '.' */
	/* we skip '/' as it's signअगरicant to pathwalk */
	[48 ... 127] = 1,		/* '0' -> '~' */
पूर्ण;

/*
 * turn the raw key पूर्णांकo something cooked
 * - the raw key should include the length in the two bytes at the front
 * - the key may be up to 514 bytes in length (including the length word)
 *   - "base64" encode the strange keys, mapping 3 bytes of raw to four of
 *     cooked
 *   - need to cut the cooked key पूर्णांकo 252 अक्षर lengths (189 raw bytes)
 */
अक्षर *cachefiles_cook_key(स्थिर u8 *raw, पूर्णांक keylen, uपूर्णांक8_t type)
अणु
	अचिन्हित अक्षर csum, ch;
	अचिन्हित पूर्णांक acc;
	अक्षर *key;
	पूर्णांक loop, len, max, seg, mark, prपूर्णांक;

	_enter(",%d", keylen);

	BUG_ON(keylen < 2 || keylen > 514);

	csum = raw[0] + raw[1];
	prपूर्णांक = 1;
	क्रम (loop = 2; loop < keylen; loop++) अणु
		ch = raw[loop];
		csum += ch;
		prपूर्णांक &= cachefiles_fileअक्षरmap[ch];
	पूर्ण

	अगर (prपूर्णांक) अणु
		/* अगर the path is usable ASCII, then we render it directly */
		max = keylen - 2;
		max += 2;	/* two base64'd length अक्षरs on the front */
		max += 5;	/* @checksum/M */
		max += 3 * 2;	/* maximum number of segment भागiders (".../M")
				 * is ((514 + 251) / 252) = 3
				 */
		max += 1;	/* NUL on end */
	पूर्ण अन्यथा अणु
		/* calculate the maximum length of the cooked key */
		keylen = (keylen + 2) / 3;

		max = keylen * 4;
		max += 5;	/* @checksum/M */
		max += 3 * 2;	/* maximum number of segment भागiders (".../M")
				 * is ((514 + 188) / 189) = 3
				 */
		max += 1;	/* NUL on end */
	पूर्ण

	max += 1;	/* 2nd NUL on end */

	_debug("max: %d", max);

	key = kदो_स्मृति(max, cachefiles_gfp);
	अगर (!key)
		वापस शून्य;

	len = 0;

	/* build the cooked key */
	प्र_लिखो(key, "@%02x%c+", (अचिन्हित) csum, 0);
	len = 5;
	mark = len - 1;

	अगर (prपूर्णांक) अणु
		acc = *(uपूर्णांक16_t *) raw;
		raw += 2;

		key[len + 1] = cachefiles_अक्षरmap[acc & 63];
		acc >>= 6;
		key[len] = cachefiles_अक्षरmap[acc & 63];
		len += 2;

		seg = 250;
		क्रम (loop = keylen; loop > 0; loop--) अणु
			अगर (seg <= 0) अणु
				key[len++] = '\0';
				mark = len;
				key[len++] = '+';
				seg = 252;
			पूर्ण

			key[len++] = *raw++;
			ASSERT(len < max);
		पूर्ण

		चयन (type) अणु
		हाल FSCACHE_COOKIE_TYPE_INDEX:		type = 'I';	अवरोध;
		हाल FSCACHE_COOKIE_TYPE_DATAखाता:	type = 'D';	अवरोध;
		शेष:				type = 'S';	अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		seg = 252;
		क्रम (loop = keylen; loop > 0; loop--) अणु
			अगर (seg <= 0) अणु
				key[len++] = '\0';
				mark = len;
				key[len++] = '+';
				seg = 252;
			पूर्ण

			acc = *raw++;
			acc |= *raw++ << 8;
			acc |= *raw++ << 16;

			_debug("acc: %06x", acc);

			key[len++] = cachefiles_अक्षरmap[acc & 63];
			acc >>= 6;
			key[len++] = cachefiles_अक्षरmap[acc & 63];
			acc >>= 6;
			key[len++] = cachefiles_अक्षरmap[acc & 63];
			acc >>= 6;
			key[len++] = cachefiles_अक्षरmap[acc & 63];

			ASSERT(len < max);
		पूर्ण

		चयन (type) अणु
		हाल FSCACHE_COOKIE_TYPE_INDEX:		type = 'J';	अवरोध;
		हाल FSCACHE_COOKIE_TYPE_DATAखाता:	type = 'E';	अवरोध;
		शेष:				type = 'T';	अवरोध;
		पूर्ण
	पूर्ण

	key[mark] = type;
	key[len++] = 0;
	key[len] = 0;

	_leave(" = %p %d", key, len);
	वापस key;
पूर्ण
