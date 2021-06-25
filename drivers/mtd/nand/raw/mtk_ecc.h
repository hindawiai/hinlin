<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/*
 * MTK SDG1 ECC controller
 *
 * Copyright (c) 2016 Mediatek
 * Authors:	Xiaolei Li		<xiaolei.li@mediatek.com>
 *		Jorge Ramirez-Ortiz	<jorge.ramirez-ortiz@linaro.org>
 */

#अगर_अघोषित __DRIVERS_MTD_न_अंकD_MTK_ECC_H__
#घोषणा __DRIVERS_MTD_न_अंकD_MTK_ECC_H__

#समावेश <linux/types.h>

क्रमागत mtk_ecc_mode अणुECC_DMA_MODE = 0, ECC_NFI_MODE = 1पूर्ण;
क्रमागत mtk_ecc_operation अणुECC_ENCODE, ECC_DECODEपूर्ण;

काष्ठा device_node;
काष्ठा mtk_ecc;

काष्ठा mtk_ecc_stats अणु
	u32 corrected;
	u32 bitflips;
	u32 failed;
पूर्ण;

काष्ठा mtk_ecc_config अणु
	क्रमागत mtk_ecc_operation op;
	क्रमागत mtk_ecc_mode mode;
	dma_addr_t addr;
	u32 strength;
	u32 sectors;
	u32 len;
पूर्ण;

पूर्णांक mtk_ecc_encode(काष्ठा mtk_ecc *, काष्ठा mtk_ecc_config *, u8 *, u32);
व्योम mtk_ecc_get_stats(काष्ठा mtk_ecc *, काष्ठा mtk_ecc_stats *, पूर्णांक);
पूर्णांक mtk_ecc_रुको_करोne(काष्ठा mtk_ecc *, क्रमागत mtk_ecc_operation);
पूर्णांक mtk_ecc_enable(काष्ठा mtk_ecc *, काष्ठा mtk_ecc_config *);
व्योम mtk_ecc_disable(काष्ठा mtk_ecc *);
व्योम mtk_ecc_adjust_strength(काष्ठा mtk_ecc *ecc, u32 *p);
अचिन्हित पूर्णांक mtk_ecc_get_parity_bits(काष्ठा mtk_ecc *ecc);

काष्ठा mtk_ecc *of_mtk_ecc_get(काष्ठा device_node *);
व्योम mtk_ecc_release(काष्ठा mtk_ecc *);

#पूर्ण_अगर
