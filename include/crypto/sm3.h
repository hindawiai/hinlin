<शैली गुरु>
/*
 * Common values क्रम SM3 algorithm
 */

#अगर_अघोषित _CRYPTO_SM3_H
#घोषणा _CRYPTO_SM3_H

#समावेश <linux/types.h>

#घोषणा SM3_DIGEST_SIZE	32
#घोषणा SM3_BLOCK_SIZE	64

#घोषणा SM3_T1		0x79CC4519
#घोषणा SM3_T2		0x7A879D8A

#घोषणा SM3_IVA		0x7380166f
#घोषणा SM3_IVB		0x4914b2b9
#घोषणा SM3_IVC		0x172442d7
#घोषणा SM3_IVD		0xda8a0600
#घोषणा SM3_IVE		0xa96f30bc
#घोषणा SM3_IVF		0x163138aa
#घोषणा SM3_IVG		0xe38dee4d
#घोषणा SM3_IVH		0xb0fb0e4e

बाह्य स्थिर u8 sm3_zero_message_hash[SM3_DIGEST_SIZE];

काष्ठा sm3_state अणु
	u32 state[SM3_DIGEST_SIZE / 4];
	u64 count;
	u8 buffer[SM3_BLOCK_SIZE];
पूर्ण;

काष्ठा shash_desc;

बाह्य पूर्णांक crypto_sm3_update(काष्ठा shash_desc *desc, स्थिर u8 *data,
			      अचिन्हित पूर्णांक len);

बाह्य पूर्णांक crypto_sm3_final(काष्ठा shash_desc *desc, u8 *out);

बाह्य पूर्णांक crypto_sm3_finup(काष्ठा shash_desc *desc, स्थिर u8 *data,
			     अचिन्हित पूर्णांक len, u8 *hash);
#पूर्ण_अगर
