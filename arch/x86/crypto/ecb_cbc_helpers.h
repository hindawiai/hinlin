<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _CRYPTO_ECB_CBC_HELPER_H
#घोषणा _CRYPTO_ECB_CBC_HELPER_H

#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <यंत्र/fpu/api.h>

/*
 * Mode helpers to instantiate parameterized skcipher ECB/CBC modes without
 * having to rely on indirect calls and retpolines.
 */

#घोषणा ECB_WALK_START(req, bsize, fpu_blocks) करो अणु			\
	व्योम *ctx = crypto_skcipher_ctx(crypto_skcipher_reqtfm(req));	\
	स्थिर पूर्णांक __bsize = (bsize);					\
	काष्ठा skcipher_walk walk;					\
	पूर्णांक err = skcipher_walk_virt(&walk, (req), false);		\
	जबतक (walk.nbytes > 0) अणु					\
		अचिन्हित पूर्णांक nbytes = walk.nbytes;			\
		bool करो_fpu = (fpu_blocks) != -1 &&			\
			      nbytes >= (fpu_blocks) * __bsize;		\
		स्थिर u8 *src = walk.src.virt.addr;			\
		u8 *dst = walk.dst.virt.addr;				\
		u8 __maybe_unused buf[(bsize)];				\
		अगर (करो_fpu) kernel_fpu_begin()

#घोषणा CBC_WALK_START(req, bsize, fpu_blocks)				\
	ECB_WALK_START(req, bsize, fpu_blocks)

#घोषणा ECB_WALK_ADVANCE(blocks) करो अणु					\
	dst += (blocks) * __bsize;					\
	src += (blocks) * __bsize;					\
	nbytes -= (blocks) * __bsize;					\
पूर्ण जबतक (0)

#घोषणा ECB_BLOCK(blocks, func) करो अणु					\
	जबतक (nbytes >= (blocks) * __bsize) अणु				\
		(func)(ctx, dst, src);					\
		ECB_WALK_ADVANCE(blocks);				\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा CBC_ENC_BLOCK(func) करो अणु					\
	स्थिर u8 *__iv = walk.iv;					\
	जबतक (nbytes >= __bsize) अणु					\
		crypto_xor_cpy(dst, src, __iv, __bsize);		\
		(func)(ctx, dst, dst);					\
		__iv = dst;						\
		ECB_WALK_ADVANCE(1);					\
	पूर्ण								\
	स_नकल(walk.iv, __iv, __bsize);					\
पूर्ण जबतक (0)

#घोषणा CBC_DEC_BLOCK(blocks, func) करो अणु				\
	जबतक (nbytes >= (blocks) * __bsize) अणु				\
		स्थिर u8 *__iv = src + ((blocks) - 1) * __bsize;	\
		अगर (dst == src)						\
			__iv = स_नकल(buf, __iv, __bsize);		\
		(func)(ctx, dst, src);					\
		crypto_xor(dst, walk.iv, __bsize);			\
		स_नकल(walk.iv, __iv, __bsize);				\
		ECB_WALK_ADVANCE(blocks);				\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा ECB_WALK_END()							\
		अगर (करो_fpu) kernel_fpu_end();				\
		err = skcipher_walk_करोne(&walk, nbytes);		\
	पूर्ण								\
	वापस err;							\
पूर्ण जबतक (0)

#घोषणा CBC_WALK_END() ECB_WALK_END()

#पूर्ण_अगर
