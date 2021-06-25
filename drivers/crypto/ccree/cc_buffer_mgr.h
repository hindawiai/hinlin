<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2012-2019 ARM Limited (or its affiliates). */

/* \पile cc_buffer_mgr.h
 * Buffer Manager
 */

#अगर_अघोषित __CC_BUFFER_MGR_H__
#घोषणा __CC_BUFFER_MGR_H__

#समावेश <crypto/algapi.h>

#समावेश "cc_driver.h"

क्रमागत cc_req_dma_buf_type अणु
	CC_DMA_BUF_शून्य = 0,
	CC_DMA_BUF_DLLI,
	CC_DMA_BUF_MLLI
पूर्ण;

क्रमागत cc_sg_cpy_direct अणु
	CC_SG_TO_BUF = 0,
	CC_SG_FROM_BUF = 1
पूर्ण;

काष्ठा cc_mlli अणु
	u32 sram_addr;
	अचिन्हित पूर्णांक mapped_nents;
	अचिन्हित पूर्णांक nents; //sg nents
	अचिन्हित पूर्णांक mlli_nents; //mlli nents might be dअगरferent than the above
पूर्ण;

काष्ठा mlli_params अणु
	काष्ठा dma_pool *curr_pool;
	व्योम *mlli_virt_addr;
	dma_addr_t mlli_dma_addr;
	u32 mlli_len;
पूर्ण;

पूर्णांक cc_buffer_mgr_init(काष्ठा cc_drvdata *drvdata);

पूर्णांक cc_buffer_mgr_fini(काष्ठा cc_drvdata *drvdata);

पूर्णांक cc_map_cipher_request(काष्ठा cc_drvdata *drvdata, व्योम *ctx,
			  अचिन्हित पूर्णांक ivsize, अचिन्हित पूर्णांक nbytes,
			  व्योम *info, काष्ठा scatterlist *src,
			  काष्ठा scatterlist *dst, gfp_t flags);

व्योम cc_unmap_cipher_request(काष्ठा device *dev, व्योम *ctx, अचिन्हित पूर्णांक ivsize,
			     काष्ठा scatterlist *src, काष्ठा scatterlist *dst);

पूर्णांक cc_map_aead_request(काष्ठा cc_drvdata *drvdata, काष्ठा aead_request *req);

व्योम cc_unmap_aead_request(काष्ठा device *dev, काष्ठा aead_request *req);

पूर्णांक cc_map_hash_request_final(काष्ठा cc_drvdata *drvdata, व्योम *ctx,
			      काष्ठा scatterlist *src, अचिन्हित पूर्णांक nbytes,
			      bool करो_update, gfp_t flags);

पूर्णांक cc_map_hash_request_update(काष्ठा cc_drvdata *drvdata, व्योम *ctx,
			       काष्ठा scatterlist *src, अचिन्हित पूर्णांक nbytes,
			       अचिन्हित पूर्णांक block_size, gfp_t flags);

व्योम cc_unmap_hash_request(काष्ठा device *dev, व्योम *ctx,
			   काष्ठा scatterlist *src, bool करो_revert);

व्योम cc_copy_sg_portion(काष्ठा device *dev, u8 *dest, काष्ठा scatterlist *sg,
			u32 to_skip, u32 end, क्रमागत cc_sg_cpy_direct direct);

#पूर्ण_अगर /*__BUFFER_MGR_H__*/
