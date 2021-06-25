<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cryptographic API
 *
 * ARC4 Cipher Algorithm
 *
 * Jon Oberheide <jon@oberheide.org>
 */

#समावेश <crypto/arc4.h>
#समावेश <linux/module.h>

पूर्णांक arc4_setkey(काष्ठा arc4_ctx *ctx, स्थिर u8 *in_key, अचिन्हित पूर्णांक key_len)
अणु
	पूर्णांक i, j = 0, k = 0;

	ctx->x = 1;
	ctx->y = 0;

	क्रम (i = 0; i < 256; i++)
		ctx->S[i] = i;

	क्रम (i = 0; i < 256; i++) अणु
		u32 a = ctx->S[i];

		j = (j + in_key[k] + a) & 0xff;
		ctx->S[i] = ctx->S[j];
		ctx->S[j] = a;
		अगर (++k >= key_len)
			k = 0;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(arc4_setkey);

व्योम arc4_crypt(काष्ठा arc4_ctx *ctx, u8 *out, स्थिर u8 *in, अचिन्हित पूर्णांक len)
अणु
	u32 *स्थिर S = ctx->S;
	u32 x, y, a, b;
	u32 ty, ta, tb;

	अगर (len == 0)
		वापस;

	x = ctx->x;
	y = ctx->y;

	a = S[x];
	y = (y + a) & 0xff;
	b = S[y];

	करो अणु
		S[y] = a;
		a = (a + b) & 0xff;
		S[x] = b;
		x = (x + 1) & 0xff;
		ta = S[x];
		ty = (y + ta) & 0xff;
		tb = S[ty];
		*out++ = *in++ ^ S[a];
		अगर (--len == 0)
			अवरोध;
		y = ty;
		a = ta;
		b = tb;
	पूर्ण जबतक (true);

	ctx->x = x;
	ctx->y = y;
पूर्ण
EXPORT_SYMBOL(arc4_crypt);

MODULE_LICENSE("GPL");
