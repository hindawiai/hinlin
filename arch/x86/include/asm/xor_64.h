<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_XOR_64_H
#घोषणा _ASM_X86_XOR_64_H

अटल काष्ठा xor_block_ढाँचा xor_block_sse = अणु
	.name = "generic_sse",
	.करो_2 = xor_sse_2,
	.करो_3 = xor_sse_3,
	.करो_4 = xor_sse_4,
	.करो_5 = xor_sse_5,
पूर्ण;


/* Also try the AVX routines */
#समावेश <यंत्र/xor_avx.h>

/* We क्रमce the use of the SSE xor block because it can ग_लिखो around L2.
   We may also be able to load पूर्णांकo the L1 only depending on how the cpu
   deals with a load to a line that is being prefetched.  */
#अघोषित XOR_TRY_TEMPLATES
#घोषणा XOR_TRY_TEMPLATES			\
करो अणु						\
	AVX_XOR_SPEED;				\
	xor_speed(&xor_block_sse_pf64);		\
	xor_speed(&xor_block_sse);		\
पूर्ण जबतक (0)

#पूर्ण_अगर /* _ASM_X86_XOR_64_H */
