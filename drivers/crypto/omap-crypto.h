<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP Crypto driver common support routines.
 *
 * Copyright (c) 2017 Texas Instruments Incorporated
 *   Tero Kristo <t-kristo@ti.com>
 */

#अगर_अघोषित __CRYPTO_OMAP_CRYPTO_H
#घोषणा __CRYPTO_OMAP_CRYPTO_H

क्रमागत अणु
	OMAP_CRYPTO_NOT_ALIGNED = 1,
	OMAP_CRYPTO_BAD_DATA_LENGTH,
पूर्ण;

#घोषणा OMAP_CRYPTO_DATA_COPIED		BIT(0)
#घोषणा OMAP_CRYPTO_SG_COPIED		BIT(1)

#घोषणा OMAP_CRYPTO_COPY_MASK		0x3

#घोषणा OMAP_CRYPTO_COPY_DATA		BIT(0)
#घोषणा OMAP_CRYPTO_FORCE_COPY		BIT(1)
#घोषणा OMAP_CRYPTO_ZERO_BUF		BIT(2)
#घोषणा OMAP_CRYPTO_FORCE_SINGLE_ENTRY	BIT(3)

पूर्णांक omap_crypto_align_sg(काष्ठा scatterlist **sg, पूर्णांक total, पूर्णांक bs,
			 काष्ठा scatterlist *new_sg, u16 flags,
			 u8 flags_shअगरt, अचिन्हित दीर्घ *dd_flags);
व्योम omap_crypto_cleanup(काष्ठा scatterlist *sg, काष्ठा scatterlist *orig,
			 पूर्णांक offset, पूर्णांक len, u8 flags_shअगरt,
			 अचिन्हित दीर्घ flags);

#पूर्ण_अगर
