<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Marvell XOR platक्रमm device data definition file.
 */

#अगर_अघोषित __DMA_MV_XOR_H
#घोषणा __DMA_MV_XOR_H

#समावेश <linux/dmaengine.h>
#समावेश <linux/mbus.h>

#घोषणा MV_XOR_NAME	"mv_xor"

काष्ठा mv_xor_channel_data अणु
	dma_cap_mask_t			cap_mask;
पूर्ण;

काष्ठा mv_xor_platक्रमm_data अणु
	काष्ठा mv_xor_channel_data    *channels;
पूर्ण;

#पूर्ण_अगर
