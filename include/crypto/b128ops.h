<शैली गुरु>
/* b128ops.h - common 128-bit block operations
 *
 * Copyright (c) 2003, Dr Brian Gladman, Worcester, UK.
 * Copyright (c) 2006, Rik Snel <rsnel@cube.dyndns.org>
 *
 * Based on Dr Brian Gladman's (GPL'd) work published at
 * http://fp.gladman.plus.com/cryptography_technology/index.hपंचांग
 * See the original copyright notice below.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */
/*
 ---------------------------------------------------------------------------
 Copyright (c) 2003, Dr Brian Gladman, Worcester, UK.   All rights reserved.

 LICENSE TERMS

 The मुक्त distribution and use of this software in both source and binary
 क्रमm is allowed (with or without changes) provided that:

   1. distributions of this source code include the above copyright
      notice, this list of conditions and the following disclaimer;

   2. distributions in binary क्रमm include the above copyright
      notice, this list of conditions and the following disclaimer
      in the करोcumentation and/or other associated materials;

   3. the copyright holder's name is not used to enकरोrse products
      built using this software without specअगरic written permission.

 ALTERNATIVELY, provided that this notice is retained in full, this product
 may be distributed under the terms of the GNU General Public License (GPL),
 in which हाल the provisions of the GPL apply INSTEAD OF those given above.

 DISCLAIMER

 This software is provided 'as is' with no explicit or implied warranties
 in respect of its properties, including, but not limited to, correctness
 and/or fitness क्रम purpose.
 ---------------------------------------------------------------------------
 Issue Date: 13/06/2006
*/

#अगर_अघोषित _CRYPTO_B128OPS_H
#घोषणा _CRYPTO_B128OPS_H

#समावेश <linux/types.h>

प्रकार काष्ठा अणु
	u64 a, b;
पूर्ण u128;

प्रकार काष्ठा अणु
	__be64 a, b;
पूर्ण be128;

प्रकार काष्ठा अणु
	__le64 b, a;
पूर्ण le128;

अटल अंतरभूत व्योम u128_xor(u128 *r, स्थिर u128 *p, स्थिर u128 *q)
अणु
	r->a = p->a ^ q->a;
	r->b = p->b ^ q->b;
पूर्ण

अटल अंतरभूत व्योम be128_xor(be128 *r, स्थिर be128 *p, स्थिर be128 *q)
अणु
	u128_xor((u128 *)r, (u128 *)p, (u128 *)q);
पूर्ण

अटल अंतरभूत व्योम le128_xor(le128 *r, स्थिर le128 *p, स्थिर le128 *q)
अणु
	u128_xor((u128 *)r, (u128 *)p, (u128 *)q);
पूर्ण

#पूर्ण_अगर /* _CRYPTO_B128OPS_H */
