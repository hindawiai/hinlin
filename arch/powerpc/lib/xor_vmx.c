<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) IBM Corporation, 2012
 *
 * Author: Anton Blanअक्षरd <anton@au.ibm.com>
 */

/*
 * Sparse (as at v0.5.0) माला_लो very, very confused by this file.
 * Make it a bit simpler क्रम it.
 */
#अगर !defined(__CHECKER__)
#समावेश <altivec.h>
#अन्यथा
#घोषणा vec_xor(a, b) a ^ b
#घोषणा vector __attribute__((vector_size(16)))
#पूर्ण_अगर

#समावेश "xor_vmx.h"

प्रकार vector चिन्हित अक्षर unative_t;

#घोषणा DEFINE(V)				\
	unative_t *V = (unative_t *)V##_in;	\
	unative_t V##_0, V##_1, V##_2, V##_3

#घोषणा LOAD(V)			\
	करो अणु			\
		V##_0 = V[0];	\
		V##_1 = V[1];	\
		V##_2 = V[2];	\
		V##_3 = V[3];	\
	पूर्ण जबतक (0)

#घोषणा STORE(V)		\
	करो अणु			\
		V[0] = V##_0;	\
		V[1] = V##_1;	\
		V[2] = V##_2;	\
		V[3] = V##_3;	\
	पूर्ण जबतक (0)

#घोषणा XOR(V1, V2)					\
	करो अणु						\
		V1##_0 = vec_xor(V1##_0, V2##_0);	\
		V1##_1 = vec_xor(V1##_1, V2##_1);	\
		V1##_2 = vec_xor(V1##_2, V2##_2);	\
		V1##_3 = vec_xor(V1##_3, V2##_3);	\
	पूर्ण जबतक (0)

व्योम __xor_altivec_2(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *v1_in,
		     अचिन्हित दीर्घ *v2_in)
अणु
	DEFINE(v1);
	DEFINE(v2);
	अचिन्हित दीर्घ lines = bytes / (माप(unative_t)) / 4;

	करो अणु
		LOAD(v1);
		LOAD(v2);
		XOR(v1, v2);
		STORE(v1);

		v1 += 4;
		v2 += 4;
	पूर्ण जबतक (--lines > 0);
पूर्ण

व्योम __xor_altivec_3(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *v1_in,
		     अचिन्हित दीर्घ *v2_in, अचिन्हित दीर्घ *v3_in)
अणु
	DEFINE(v1);
	DEFINE(v2);
	DEFINE(v3);
	अचिन्हित दीर्घ lines = bytes / (माप(unative_t)) / 4;

	करो अणु
		LOAD(v1);
		LOAD(v2);
		LOAD(v3);
		XOR(v1, v2);
		XOR(v1, v3);
		STORE(v1);

		v1 += 4;
		v2 += 4;
		v3 += 4;
	पूर्ण जबतक (--lines > 0);
पूर्ण

व्योम __xor_altivec_4(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *v1_in,
		     अचिन्हित दीर्घ *v2_in, अचिन्हित दीर्घ *v3_in,
		     अचिन्हित दीर्घ *v4_in)
अणु
	DEFINE(v1);
	DEFINE(v2);
	DEFINE(v3);
	DEFINE(v4);
	अचिन्हित दीर्घ lines = bytes / (माप(unative_t)) / 4;

	करो अणु
		LOAD(v1);
		LOAD(v2);
		LOAD(v3);
		LOAD(v4);
		XOR(v1, v2);
		XOR(v3, v4);
		XOR(v1, v3);
		STORE(v1);

		v1 += 4;
		v2 += 4;
		v3 += 4;
		v4 += 4;
	पूर्ण जबतक (--lines > 0);
पूर्ण

व्योम __xor_altivec_5(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *v1_in,
		     अचिन्हित दीर्घ *v2_in, अचिन्हित दीर्घ *v3_in,
		     अचिन्हित दीर्घ *v4_in, अचिन्हित दीर्घ *v5_in)
अणु
	DEFINE(v1);
	DEFINE(v2);
	DEFINE(v3);
	DEFINE(v4);
	DEFINE(v5);
	अचिन्हित दीर्घ lines = bytes / (माप(unative_t)) / 4;

	करो अणु
		LOAD(v1);
		LOAD(v2);
		LOAD(v3);
		LOAD(v4);
		LOAD(v5);
		XOR(v1, v2);
		XOR(v3, v4);
		XOR(v1, v5);
		XOR(v1, v3);
		STORE(v1);

		v1 += 4;
		v2 += 4;
		v3 += 4;
		v4 += 4;
		v5 += 4;
	पूर्ण जबतक (--lines > 0);
पूर्ण
