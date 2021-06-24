<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _NFT_SET_PIPAPO_AVX2_H

#अगर defined(CONFIG_X86_64) && !defined(CONFIG_UML)
#समावेश <यंत्र/fpu/xstate.h>
#घोषणा NFT_PIPAPO_ALIGN	(XSAVE_YMM_SIZE / BITS_PER_BYTE)

bool nft_pipapo_avx2_lookup(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
			    स्थिर u32 *key, स्थिर काष्ठा nft_set_ext **ext);
bool nft_pipapo_avx2_estimate(स्थिर काष्ठा nft_set_desc *desc, u32 features,
			      काष्ठा nft_set_estimate *est);
#पूर्ण_अगर /* defined(CONFIG_X86_64) && !defined(CONFIG_UML) */

#पूर्ण_अगर /* _NFT_SET_PIPAPO_AVX2_H */
