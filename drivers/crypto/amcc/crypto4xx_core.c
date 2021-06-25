<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AMCC SoC PPC4xx Crypto Driver
 *
 * Copyright (c) 2008 Applied Micro Circuits Corporation.
 * All rights reserved. James Hsiao <jhsiao@amcc.com>
 *
 * This file implements AMCC crypto offload Linux device driver क्रम use with
 * Linux CryptoAPI.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock_types.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/crypto.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/dcr.h>
#समावेश <यंत्र/dcr-regs.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <crypto/aead.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/ctr.h>
#समावेश <crypto/gcm.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/rng.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/skcipher.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/rng.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश "crypto4xx_reg_def.h"
#समावेश "crypto4xx_core.h"
#समावेश "crypto4xx_sa.h"
#समावेश "crypto4xx_trng.h"

#घोषणा PPC4XX_SEC_VERSION_STR			"0.5"

/*
 * PPC4xx Crypto Engine Initialization Routine
 */
अटल व्योम crypto4xx_hw_init(काष्ठा crypto4xx_device *dev)
अणु
	जोड़ ce_ring_size ring_size;
	जोड़ ce_ring_control ring_ctrl;
	जोड़ ce_part_ring_size part_ring_size;
	जोड़ ce_io_threshold io_threshold;
	u32 अक्रम_num;
	जोड़ ce_pe_dma_cfg pe_dma_cfg;
	u32 device_ctrl;

	ग_लिखोl(PPC4XX_BYTE_ORDER, dev->ce_base + CRYPTO4XX_BYTE_ORDER_CFG);
	/* setup pe dma, include reset sg, pdr and pe, then release reset */
	pe_dma_cfg.w = 0;
	pe_dma_cfg.bf.bo_sgpd_en = 1;
	pe_dma_cfg.bf.bo_data_en = 0;
	pe_dma_cfg.bf.bo_sa_en = 1;
	pe_dma_cfg.bf.bo_pd_en = 1;
	pe_dma_cfg.bf.dynamic_sa_en = 1;
	pe_dma_cfg.bf.reset_sg = 1;
	pe_dma_cfg.bf.reset_pdr = 1;
	pe_dma_cfg.bf.reset_pe = 1;
	ग_लिखोl(pe_dma_cfg.w, dev->ce_base + CRYPTO4XX_PE_DMA_CFG);
	/* un reset pe,sg and pdr */
	pe_dma_cfg.bf.pe_mode = 0;
	pe_dma_cfg.bf.reset_sg = 0;
	pe_dma_cfg.bf.reset_pdr = 0;
	pe_dma_cfg.bf.reset_pe = 0;
	pe_dma_cfg.bf.bo_td_en = 0;
	ग_लिखोl(pe_dma_cfg.w, dev->ce_base + CRYPTO4XX_PE_DMA_CFG);
	ग_लिखोl(dev->pdr_pa, dev->ce_base + CRYPTO4XX_PDR_BASE);
	ग_लिखोl(dev->pdr_pa, dev->ce_base + CRYPTO4XX_RDR_BASE);
	ग_लिखोl(PPC4XX_PRNG_CTRL_AUTO_EN, dev->ce_base + CRYPTO4XX_PRNG_CTRL);
	get_अक्रमom_bytes(&अक्रम_num, माप(अक्रम_num));
	ग_लिखोl(अक्रम_num, dev->ce_base + CRYPTO4XX_PRNG_SEED_L);
	get_अक्रमom_bytes(&अक्रम_num, माप(अक्रम_num));
	ग_लिखोl(अक्रम_num, dev->ce_base + CRYPTO4XX_PRNG_SEED_H);
	ring_size.w = 0;
	ring_size.bf.ring_offset = PPC4XX_PD_SIZE;
	ring_size.bf.ring_size   = PPC4XX_NUM_PD;
	ग_लिखोl(ring_size.w, dev->ce_base + CRYPTO4XX_RING_SIZE);
	ring_ctrl.w = 0;
	ग_लिखोl(ring_ctrl.w, dev->ce_base + CRYPTO4XX_RING_CTRL);
	device_ctrl = पढ़ोl(dev->ce_base + CRYPTO4XX_DEVICE_CTRL);
	device_ctrl |= PPC4XX_DC_3DES_EN;
	ग_लिखोl(device_ctrl, dev->ce_base + CRYPTO4XX_DEVICE_CTRL);
	ग_लिखोl(dev->gdr_pa, dev->ce_base + CRYPTO4XX_GATH_RING_BASE);
	ग_लिखोl(dev->sdr_pa, dev->ce_base + CRYPTO4XX_SCAT_RING_BASE);
	part_ring_size.w = 0;
	part_ring_size.bf.sdr_size = PPC4XX_SDR_SIZE;
	part_ring_size.bf.gdr_size = PPC4XX_GDR_SIZE;
	ग_लिखोl(part_ring_size.w, dev->ce_base + CRYPTO4XX_PART_RING_SIZE);
	ग_लिखोl(PPC4XX_SD_BUFFER_SIZE, dev->ce_base + CRYPTO4XX_PART_RING_CFG);
	io_threshold.w = 0;
	io_threshold.bf.output_threshold = PPC4XX_OUTPUT_THRESHOLD;
	io_threshold.bf.input_threshold  = PPC4XX_INPUT_THRESHOLD;
	ग_लिखोl(io_threshold.w, dev->ce_base + CRYPTO4XX_IO_THRESHOLD);
	ग_लिखोl(0, dev->ce_base + CRYPTO4XX_PDR_BASE_UADDR);
	ग_लिखोl(0, dev->ce_base + CRYPTO4XX_RDR_BASE_UADDR);
	ग_लिखोl(0, dev->ce_base + CRYPTO4XX_PKT_SRC_UADDR);
	ग_लिखोl(0, dev->ce_base + CRYPTO4XX_PKT_DEST_UADDR);
	ग_लिखोl(0, dev->ce_base + CRYPTO4XX_SA_UADDR);
	ग_लिखोl(0, dev->ce_base + CRYPTO4XX_GATH_RING_BASE_UADDR);
	ग_लिखोl(0, dev->ce_base + CRYPTO4XX_SCAT_RING_BASE_UADDR);
	/* un reset pe,sg and pdr */
	pe_dma_cfg.bf.pe_mode = 1;
	pe_dma_cfg.bf.reset_sg = 0;
	pe_dma_cfg.bf.reset_pdr = 0;
	pe_dma_cfg.bf.reset_pe = 0;
	pe_dma_cfg.bf.bo_td_en = 0;
	ग_लिखोl(pe_dma_cfg.w, dev->ce_base + CRYPTO4XX_PE_DMA_CFG);
	/*clear all pending पूर्णांकerrupt*/
	ग_लिखोl(PPC4XX_INTERRUPT_CLR, dev->ce_base + CRYPTO4XX_INT_CLR);
	ग_लिखोl(PPC4XX_INT_DESCR_CNT, dev->ce_base + CRYPTO4XX_INT_DESCR_CNT);
	ग_लिखोl(PPC4XX_INT_DESCR_CNT, dev->ce_base + CRYPTO4XX_INT_DESCR_CNT);
	ग_लिखोl(PPC4XX_INT_CFG, dev->ce_base + CRYPTO4XX_INT_CFG);
	अगर (dev->is_revb) अणु
		ग_लिखोl(PPC4XX_INT_TIMEOUT_CNT_REVB << 10,
		       dev->ce_base + CRYPTO4XX_INT_TIMEOUT_CNT);
		ग_लिखोl(PPC4XX_PD_DONE_INT | PPC4XX_TMO_ERR_INT,
		       dev->ce_base + CRYPTO4XX_INT_EN);
	पूर्ण अन्यथा अणु
		ग_लिखोl(PPC4XX_PD_DONE_INT, dev->ce_base + CRYPTO4XX_INT_EN);
	पूर्ण
पूर्ण

पूर्णांक crypto4xx_alloc_sa(काष्ठा crypto4xx_ctx *ctx, u32 size)
अणु
	ctx->sa_in = kसुस्मृति(size, 4, GFP_ATOMIC);
	अगर (ctx->sa_in == शून्य)
		वापस -ENOMEM;

	ctx->sa_out = kसुस्मृति(size, 4, GFP_ATOMIC);
	अगर (ctx->sa_out == शून्य) अणु
		kमुक्त(ctx->sa_in);
		ctx->sa_in = शून्य;
		वापस -ENOMEM;
	पूर्ण

	ctx->sa_len = size;

	वापस 0;
पूर्ण

व्योम crypto4xx_मुक्त_sa(काष्ठा crypto4xx_ctx *ctx)
अणु
	kमुक्त(ctx->sa_in);
	ctx->sa_in = शून्य;
	kमुक्त(ctx->sa_out);
	ctx->sa_out = शून्य;
	ctx->sa_len = 0;
पूर्ण

/*
 * alloc memory क्रम the gather ring
 * no need to alloc buf क्रम the ring
 * gdr_tail, gdr_head and gdr_count are initialized by this function
 */
अटल u32 crypto4xx_build_pdr(काष्ठा crypto4xx_device *dev)
अणु
	पूर्णांक i;
	dev->pdr = dma_alloc_coherent(dev->core_dev->device,
				      माप(काष्ठा ce_pd) * PPC4XX_NUM_PD,
				      &dev->pdr_pa, GFP_KERNEL);
	अगर (!dev->pdr)
		वापस -ENOMEM;

	dev->pdr_uinfo = kसुस्मृति(PPC4XX_NUM_PD, माप(काष्ठा pd_uinfo),
				 GFP_KERNEL);
	अगर (!dev->pdr_uinfo) अणु
		dma_मुक्त_coherent(dev->core_dev->device,
				  माप(काष्ठा ce_pd) * PPC4XX_NUM_PD,
				  dev->pdr,
				  dev->pdr_pa);
		वापस -ENOMEM;
	पूर्ण
	dev->shaकरोw_sa_pool = dma_alloc_coherent(dev->core_dev->device,
				   माप(जोड़ shaकरोw_sa_buf) * PPC4XX_NUM_PD,
				   &dev->shaकरोw_sa_pool_pa,
				   GFP_KERNEL);
	अगर (!dev->shaकरोw_sa_pool)
		वापस -ENOMEM;

	dev->shaकरोw_sr_pool = dma_alloc_coherent(dev->core_dev->device,
			 माप(काष्ठा sa_state_record) * PPC4XX_NUM_PD,
			 &dev->shaकरोw_sr_pool_pa, GFP_KERNEL);
	अगर (!dev->shaकरोw_sr_pool)
		वापस -ENOMEM;
	क्रम (i = 0; i < PPC4XX_NUM_PD; i++) अणु
		काष्ठा ce_pd *pd = &dev->pdr[i];
		काष्ठा pd_uinfo *pd_uinfo = &dev->pdr_uinfo[i];

		pd->sa = dev->shaकरोw_sa_pool_pa +
			माप(जोड़ shaकरोw_sa_buf) * i;

		/* alloc 256 bytes which is enough क्रम any kind of dynamic sa */
		pd_uinfo->sa_va = &dev->shaकरोw_sa_pool[i].sa;

		/* alloc state record */
		pd_uinfo->sr_va = &dev->shaकरोw_sr_pool[i];
		pd_uinfo->sr_pa = dev->shaकरोw_sr_pool_pa +
		    माप(काष्ठा sa_state_record) * i;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम crypto4xx_destroy_pdr(काष्ठा crypto4xx_device *dev)
अणु
	अगर (dev->pdr)
		dma_मुक्त_coherent(dev->core_dev->device,
				  माप(काष्ठा ce_pd) * PPC4XX_NUM_PD,
				  dev->pdr, dev->pdr_pa);

	अगर (dev->shaकरोw_sa_pool)
		dma_मुक्त_coherent(dev->core_dev->device,
			माप(जोड़ shaकरोw_sa_buf) * PPC4XX_NUM_PD,
			dev->shaकरोw_sa_pool, dev->shaकरोw_sa_pool_pa);

	अगर (dev->shaकरोw_sr_pool)
		dma_मुक्त_coherent(dev->core_dev->device,
			माप(काष्ठा sa_state_record) * PPC4XX_NUM_PD,
			dev->shaकरोw_sr_pool, dev->shaकरोw_sr_pool_pa);

	kमुक्त(dev->pdr_uinfo);
पूर्ण

अटल u32 crypto4xx_get_pd_from_pdr_nolock(काष्ठा crypto4xx_device *dev)
अणु
	u32 retval;
	u32 पंचांगp;

	retval = dev->pdr_head;
	पंचांगp = (dev->pdr_head + 1) % PPC4XX_NUM_PD;

	अगर (पंचांगp == dev->pdr_tail)
		वापस ERING_WAS_FULL;

	dev->pdr_head = पंचांगp;

	वापस retval;
पूर्ण

अटल u32 crypto4xx_put_pd_to_pdr(काष्ठा crypto4xx_device *dev, u32 idx)
अणु
	काष्ठा pd_uinfo *pd_uinfo = &dev->pdr_uinfo[idx];
	u32 tail;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->core_dev->lock, flags);
	pd_uinfo->state = PD_ENTRY_FREE;

	अगर (dev->pdr_tail != PPC4XX_LAST_PD)
		dev->pdr_tail++;
	अन्यथा
		dev->pdr_tail = 0;
	tail = dev->pdr_tail;
	spin_unlock_irqrestore(&dev->core_dev->lock, flags);

	वापस tail;
पूर्ण

/*
 * alloc memory क्रम the gather ring
 * no need to alloc buf क्रम the ring
 * gdr_tail, gdr_head and gdr_count are initialized by this function
 */
अटल u32 crypto4xx_build_gdr(काष्ठा crypto4xx_device *dev)
अणु
	dev->gdr = dma_alloc_coherent(dev->core_dev->device,
				      माप(काष्ठा ce_gd) * PPC4XX_NUM_GD,
				      &dev->gdr_pa, GFP_KERNEL);
	अगर (!dev->gdr)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम crypto4xx_destroy_gdr(काष्ठा crypto4xx_device *dev)
अणु
	अगर (dev->gdr)
		dma_मुक्त_coherent(dev->core_dev->device,
			  माप(काष्ठा ce_gd) * PPC4XX_NUM_GD,
			  dev->gdr, dev->gdr_pa);
पूर्ण

/*
 * when this function is called.
 * preemption or पूर्णांकerrupt must be disabled
 */
अटल u32 crypto4xx_get_n_gd(काष्ठा crypto4xx_device *dev, पूर्णांक n)
अणु
	u32 retval;
	u32 पंचांगp;

	अगर (n >= PPC4XX_NUM_GD)
		वापस ERING_WAS_FULL;

	retval = dev->gdr_head;
	पंचांगp = (dev->gdr_head + n) % PPC4XX_NUM_GD;
	अगर (dev->gdr_head > dev->gdr_tail) अणु
		अगर (पंचांगp < dev->gdr_head && पंचांगp >= dev->gdr_tail)
			वापस ERING_WAS_FULL;
	पूर्ण अन्यथा अगर (dev->gdr_head < dev->gdr_tail) अणु
		अगर (पंचांगp < dev->gdr_head || पंचांगp >= dev->gdr_tail)
			वापस ERING_WAS_FULL;
	पूर्ण
	dev->gdr_head = पंचांगp;

	वापस retval;
पूर्ण

अटल u32 crypto4xx_put_gd_to_gdr(काष्ठा crypto4xx_device *dev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->core_dev->lock, flags);
	अगर (dev->gdr_tail == dev->gdr_head) अणु
		spin_unlock_irqrestore(&dev->core_dev->lock, flags);
		वापस 0;
	पूर्ण

	अगर (dev->gdr_tail != PPC4XX_LAST_GD)
		dev->gdr_tail++;
	अन्यथा
		dev->gdr_tail = 0;

	spin_unlock_irqrestore(&dev->core_dev->lock, flags);

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा ce_gd *crypto4xx_get_gdp(काष्ठा crypto4xx_device *dev,
					      dma_addr_t *gd_dma, u32 idx)
अणु
	*gd_dma = dev->gdr_pa + माप(काष्ठा ce_gd) * idx;

	वापस &dev->gdr[idx];
पूर्ण

/*
 * alloc memory क्रम the scatter ring
 * need to alloc buf क्रम the ring
 * sdr_tail, sdr_head and sdr_count are initialized by this function
 */
अटल u32 crypto4xx_build_sdr(काष्ठा crypto4xx_device *dev)
अणु
	पूर्णांक i;

	dev->scatter_buffer_va =
		dma_alloc_coherent(dev->core_dev->device,
			PPC4XX_SD_BUFFER_SIZE * PPC4XX_NUM_SD,
			&dev->scatter_buffer_pa, GFP_KERNEL);
	अगर (!dev->scatter_buffer_va)
		वापस -ENOMEM;

	/* alloc memory क्रम scatter descriptor ring */
	dev->sdr = dma_alloc_coherent(dev->core_dev->device,
				      माप(काष्ठा ce_sd) * PPC4XX_NUM_SD,
				      &dev->sdr_pa, GFP_KERNEL);
	अगर (!dev->sdr)
		वापस -ENOMEM;

	क्रम (i = 0; i < PPC4XX_NUM_SD; i++) अणु
		dev->sdr[i].ptr = dev->scatter_buffer_pa +
				  PPC4XX_SD_BUFFER_SIZE * i;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम crypto4xx_destroy_sdr(काष्ठा crypto4xx_device *dev)
अणु
	अगर (dev->sdr)
		dma_मुक्त_coherent(dev->core_dev->device,
				  माप(काष्ठा ce_sd) * PPC4XX_NUM_SD,
				  dev->sdr, dev->sdr_pa);

	अगर (dev->scatter_buffer_va)
		dma_मुक्त_coherent(dev->core_dev->device,
				  PPC4XX_SD_BUFFER_SIZE * PPC4XX_NUM_SD,
				  dev->scatter_buffer_va,
				  dev->scatter_buffer_pa);
पूर्ण

/*
 * when this function is called.
 * preemption or पूर्णांकerrupt must be disabled
 */
अटल u32 crypto4xx_get_n_sd(काष्ठा crypto4xx_device *dev, पूर्णांक n)
अणु
	u32 retval;
	u32 पंचांगp;

	अगर (n >= PPC4XX_NUM_SD)
		वापस ERING_WAS_FULL;

	retval = dev->sdr_head;
	पंचांगp = (dev->sdr_head + n) % PPC4XX_NUM_SD;
	अगर (dev->sdr_head > dev->gdr_tail) अणु
		अगर (पंचांगp < dev->sdr_head && पंचांगp >= dev->sdr_tail)
			वापस ERING_WAS_FULL;
	पूर्ण अन्यथा अगर (dev->sdr_head < dev->sdr_tail) अणु
		अगर (पंचांगp < dev->sdr_head || पंचांगp >= dev->sdr_tail)
			वापस ERING_WAS_FULL;
	पूर्ण /* the head = tail, or empty हाल is alपढ़ोy take cared */
	dev->sdr_head = पंचांगp;

	वापस retval;
पूर्ण

अटल u32 crypto4xx_put_sd_to_sdr(काष्ठा crypto4xx_device *dev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->core_dev->lock, flags);
	अगर (dev->sdr_tail == dev->sdr_head) अणु
		spin_unlock_irqrestore(&dev->core_dev->lock, flags);
		वापस 0;
	पूर्ण
	अगर (dev->sdr_tail != PPC4XX_LAST_SD)
		dev->sdr_tail++;
	अन्यथा
		dev->sdr_tail = 0;
	spin_unlock_irqrestore(&dev->core_dev->lock, flags);

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा ce_sd *crypto4xx_get_sdp(काष्ठा crypto4xx_device *dev,
					      dma_addr_t *sd_dma, u32 idx)
अणु
	*sd_dma = dev->sdr_pa + माप(काष्ठा ce_sd) * idx;

	वापस &dev->sdr[idx];
पूर्ण

अटल व्योम crypto4xx_copy_pkt_to_dst(काष्ठा crypto4xx_device *dev,
				      काष्ठा ce_pd *pd,
				      काष्ठा pd_uinfo *pd_uinfo,
				      u32 nbytes,
				      काष्ठा scatterlist *dst)
अणु
	अचिन्हित पूर्णांक first_sd = pd_uinfo->first_sd;
	अचिन्हित पूर्णांक last_sd;
	अचिन्हित पूर्णांक overflow = 0;
	अचिन्हित पूर्णांक to_copy;
	अचिन्हित पूर्णांक dst_start = 0;

	/*
	 * Because the scatter buffers are all neatly organized in one
	 * big continuous ringbuffer; scatterwalk_map_and_copy() can
	 * be inकाष्ठाed to copy a range of buffers in one go.
	 */

	last_sd = (first_sd + pd_uinfo->num_sd);
	अगर (last_sd > PPC4XX_LAST_SD) अणु
		last_sd = PPC4XX_LAST_SD;
		overflow = last_sd % PPC4XX_NUM_SD;
	पूर्ण

	जबतक (nbytes) अणु
		व्योम *buf = dev->scatter_buffer_va +
			first_sd * PPC4XX_SD_BUFFER_SIZE;

		to_copy = min(nbytes, PPC4XX_SD_BUFFER_SIZE *
				      (1 + last_sd - first_sd));
		scatterwalk_map_and_copy(buf, dst, dst_start, to_copy, 1);
		nbytes -= to_copy;

		अगर (overflow) अणु
			first_sd = 0;
			last_sd = overflow;
			dst_start += to_copy;
			overflow = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम crypto4xx_copy_digest_to_dst(व्योम *dst,
					काष्ठा pd_uinfo *pd_uinfo,
					काष्ठा crypto4xx_ctx *ctx)
अणु
	काष्ठा dynamic_sa_ctl *sa = (काष्ठा dynamic_sa_ctl *) ctx->sa_in;

	अगर (sa->sa_command_0.bf.hash_alg == SA_HASH_ALG_SHA1) अणु
		स_नकल(dst, pd_uinfo->sr_va->save_digest,
		       SA_HASH_ALG_SHA1_DIGEST_SIZE);
	पूर्ण
पूर्ण

अटल व्योम crypto4xx_ret_sg_desc(काष्ठा crypto4xx_device *dev,
				  काष्ठा pd_uinfo *pd_uinfo)
अणु
	पूर्णांक i;
	अगर (pd_uinfo->num_gd) अणु
		क्रम (i = 0; i < pd_uinfo->num_gd; i++)
			crypto4xx_put_gd_to_gdr(dev);
		pd_uinfo->first_gd = 0xffffffff;
		pd_uinfo->num_gd = 0;
	पूर्ण
	अगर (pd_uinfo->num_sd) अणु
		क्रम (i = 0; i < pd_uinfo->num_sd; i++)
			crypto4xx_put_sd_to_sdr(dev);

		pd_uinfo->first_sd = 0xffffffff;
		pd_uinfo->num_sd = 0;
	पूर्ण
पूर्ण

अटल व्योम crypto4xx_cipher_करोne(काष्ठा crypto4xx_device *dev,
				     काष्ठा pd_uinfo *pd_uinfo,
				     काष्ठा ce_pd *pd)
अणु
	काष्ठा skcipher_request *req;
	काष्ठा scatterlist *dst;
	dma_addr_t addr;

	req = skcipher_request_cast(pd_uinfo->async_req);

	अगर (pd_uinfo->sa_va->sa_command_0.bf.scatter) अणु
		crypto4xx_copy_pkt_to_dst(dev, pd, pd_uinfo,
					  req->cryptlen, req->dst);
	पूर्ण अन्यथा अणु
		dst = pd_uinfo->dest_va;
		addr = dma_map_page(dev->core_dev->device, sg_page(dst),
				    dst->offset, dst->length, DMA_FROM_DEVICE);
	पूर्ण

	अगर (pd_uinfo->sa_va->sa_command_0.bf.save_iv == SA_SAVE_IV) अणु
		काष्ठा crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);

		crypto4xx_स_नकल_from_le32((u32 *)req->iv,
			pd_uinfo->sr_va->save_iv,
			crypto_skcipher_ivsize(skcipher));
	पूर्ण

	crypto4xx_ret_sg_desc(dev, pd_uinfo);

	अगर (pd_uinfo->state & PD_ENTRY_BUSY)
		skcipher_request_complete(req, -EINPROGRESS);
	skcipher_request_complete(req, 0);
पूर्ण

अटल व्योम crypto4xx_ahash_करोne(काष्ठा crypto4xx_device *dev,
				काष्ठा pd_uinfo *pd_uinfo)
अणु
	काष्ठा crypto4xx_ctx *ctx;
	काष्ठा ahash_request *ahash_req;

	ahash_req = ahash_request_cast(pd_uinfo->async_req);
	ctx  = crypto_tfm_ctx(ahash_req->base.tfm);

	crypto4xx_copy_digest_to_dst(ahash_req->result, pd_uinfo,
				     crypto_tfm_ctx(ahash_req->base.tfm));
	crypto4xx_ret_sg_desc(dev, pd_uinfo);

	अगर (pd_uinfo->state & PD_ENTRY_BUSY)
		ahash_request_complete(ahash_req, -EINPROGRESS);
	ahash_request_complete(ahash_req, 0);
पूर्ण

अटल व्योम crypto4xx_aead_करोne(काष्ठा crypto4xx_device *dev,
				काष्ठा pd_uinfo *pd_uinfo,
				काष्ठा ce_pd *pd)
अणु
	काष्ठा aead_request *aead_req = container_of(pd_uinfo->async_req,
		काष्ठा aead_request, base);
	काष्ठा scatterlist *dst = pd_uinfo->dest_va;
	माप_प्रकार cp_len = crypto_aead_authsize(
		crypto_aead_reqtfm(aead_req));
	u32 icv[AES_BLOCK_SIZE];
	पूर्णांक err = 0;

	अगर (pd_uinfo->sa_va->sa_command_0.bf.scatter) अणु
		crypto4xx_copy_pkt_to_dst(dev, pd, pd_uinfo,
					  pd->pd_ctl_len.bf.pkt_len,
					  dst);
	पूर्ण अन्यथा अणु
		dma_unmap_page(dev->core_dev->device, pd->dest, dst->length,
				DMA_FROM_DEVICE);
	पूर्ण

	अगर (pd_uinfo->sa_va->sa_command_0.bf.dir == सूची_OUTBOUND) अणु
		/* append icv at the end */
		crypto4xx_स_नकल_from_le32(icv, pd_uinfo->sr_va->save_digest,
					   माप(icv));

		scatterwalk_map_and_copy(icv, dst, aead_req->cryptlen,
					 cp_len, 1);
	पूर्ण अन्यथा अणु
		/* check icv at the end */
		scatterwalk_map_and_copy(icv, aead_req->src,
			aead_req->assoclen + aead_req->cryptlen -
			cp_len, cp_len, 0);

		crypto4xx_स_नकल_from_le32(icv, icv, माप(icv));

		अगर (crypto_memneq(icv, pd_uinfo->sr_va->save_digest, cp_len))
			err = -EBADMSG;
	पूर्ण

	crypto4xx_ret_sg_desc(dev, pd_uinfo);

	अगर (pd->pd_ctl.bf.status & 0xff) अणु
		अगर (!__ratelimit(&dev->aead_ratelimit)) अणु
			अगर (pd->pd_ctl.bf.status & 2)
				pr_err("pad fail error\n");
			अगर (pd->pd_ctl.bf.status & 4)
				pr_err("seqnum fail\n");
			अगर (pd->pd_ctl.bf.status & 8)
				pr_err("error _notify\n");
			pr_err("aead return err status = 0x%02x\n",
				pd->pd_ctl.bf.status & 0xff);
			pr_err("pd pad_ctl = 0x%08x\n",
				pd->pd_ctl.bf.pd_pad_ctl);
		पूर्ण
		err = -EINVAL;
	पूर्ण

	अगर (pd_uinfo->state & PD_ENTRY_BUSY)
		aead_request_complete(aead_req, -EINPROGRESS);

	aead_request_complete(aead_req, err);
पूर्ण

अटल व्योम crypto4xx_pd_करोne(काष्ठा crypto4xx_device *dev, u32 idx)
अणु
	काष्ठा ce_pd *pd = &dev->pdr[idx];
	काष्ठा pd_uinfo *pd_uinfo = &dev->pdr_uinfo[idx];

	चयन (crypto_tfm_alg_type(pd_uinfo->async_req->tfm)) अणु
	हाल CRYPTO_ALG_TYPE_SKCIPHER:
		crypto4xx_cipher_करोne(dev, pd_uinfo, pd);
		अवरोध;
	हाल CRYPTO_ALG_TYPE_AEAD:
		crypto4xx_aead_करोne(dev, pd_uinfo, pd);
		अवरोध;
	हाल CRYPTO_ALG_TYPE_AHASH:
		crypto4xx_ahash_करोne(dev, pd_uinfo);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम crypto4xx_stop_all(काष्ठा crypto4xx_core_device *core_dev)
अणु
	crypto4xx_destroy_pdr(core_dev->dev);
	crypto4xx_destroy_gdr(core_dev->dev);
	crypto4xx_destroy_sdr(core_dev->dev);
	iounmap(core_dev->dev->ce_base);
	kमुक्त(core_dev->dev);
	kमुक्त(core_dev);
पूर्ण

अटल u32 get_next_gd(u32 current)
अणु
	अगर (current != PPC4XX_LAST_GD)
		वापस current + 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल u32 get_next_sd(u32 current)
अणु
	अगर (current != PPC4XX_LAST_SD)
		वापस current + 1;
	अन्यथा
		वापस 0;
पूर्ण

पूर्णांक crypto4xx_build_pd(काष्ठा crypto_async_request *req,
		       काष्ठा crypto4xx_ctx *ctx,
		       काष्ठा scatterlist *src,
		       काष्ठा scatterlist *dst,
		       स्थिर अचिन्हित पूर्णांक datalen,
		       स्थिर __le32 *iv, स्थिर u32 iv_len,
		       स्थिर काष्ठा dynamic_sa_ctl *req_sa,
		       स्थिर अचिन्हित पूर्णांक sa_len,
		       स्थिर अचिन्हित पूर्णांक assoclen,
		       काष्ठा scatterlist *_dst)
अणु
	काष्ठा crypto4xx_device *dev = ctx->dev;
	काष्ठा dynamic_sa_ctl *sa;
	काष्ठा ce_gd *gd;
	काष्ठा ce_pd *pd;
	u32 num_gd, num_sd;
	u32 fst_gd = 0xffffffff;
	u32 fst_sd = 0xffffffff;
	u32 pd_entry;
	अचिन्हित दीर्घ flags;
	काष्ठा pd_uinfo *pd_uinfo;
	अचिन्हित पूर्णांक nbytes = datalen;
	माप_प्रकार offset_to_sr_ptr;
	u32 gd_idx = 0;
	पूर्णांक पंचांगp;
	bool is_busy, क्रमce_sd;

	/*
	 * There's a very subtile/disguised "bug" in the hardware that
	 * माला_लो indirectly mentioned in 18.1.3.5 Encryption/Decryption
	 * of the hardware spec:
	 * *drum roll* the AES/(T)DES OFB and CFB modes are listed as
	 * operation modes क्रम >>> "Block ciphers" <<<.
	 *
	 * To workaround this issue and stop the hardware from causing
	 * "overran dst buffer" on crypttexts that are not a multiple
	 * of 16 (AES_BLOCK_SIZE), we क्रमce the driver to use the
	 * scatter buffers.
	 */
	क्रमce_sd = (req_sa->sa_command_1.bf.crypto_mode9_8 == CRYPTO_MODE_CFB
		|| req_sa->sa_command_1.bf.crypto_mode9_8 == CRYPTO_MODE_OFB)
		&& (datalen % AES_BLOCK_SIZE);

	/* figure how many gd are needed */
	पंचांगp = sg_nents_क्रम_len(src, assoclen + datalen);
	अगर (पंचांगp < 0) अणु
		dev_err(dev->core_dev->device, "Invalid number of src SG.\n");
		वापस पंचांगp;
	पूर्ण
	अगर (पंचांगp == 1)
		पंचांगp = 0;
	num_gd = पंचांगp;

	अगर (assoclen) अणु
		nbytes += assoclen;
		dst = scatterwalk_ffwd(_dst, dst, assoclen);
	पूर्ण

	/* figure how many sd are needed */
	अगर (sg_is_last(dst) && क्रमce_sd == false) अणु
		num_sd = 0;
	पूर्ण अन्यथा अणु
		अगर (datalen > PPC4XX_SD_BUFFER_SIZE) अणु
			num_sd = datalen / PPC4XX_SD_BUFFER_SIZE;
			अगर (datalen % PPC4XX_SD_BUFFER_SIZE)
				num_sd++;
		पूर्ण अन्यथा अणु
			num_sd = 1;
		पूर्ण
	पूर्ण

	/*
	 * The follow section of code needs to be रक्षित
	 * The gather ring and scatter ring needs to be consecutive
	 * In हाल of run out of any kind of descriptor, the descriptor
	 * alपढ़ोy got must be वापस the original place.
	 */
	spin_lock_irqsave(&dev->core_dev->lock, flags);
	/*
	 * Let the caller know to slow करोwn, once more than 13/16ths = 81%
	 * of the available data contexts are being used simultaneously.
	 *
	 * With PPC4XX_NUM_PD = 256, this will leave a "backlog queue" क्रम
	 * 31 more contexts. Beक्रमe new requests have to be rejected.
	 */
	अगर (req->flags & CRYPTO_TFM_REQ_MAY_BACKLOG) अणु
		is_busy = ((dev->pdr_head - dev->pdr_tail) % PPC4XX_NUM_PD) >=
			((PPC4XX_NUM_PD * 13) / 16);
	पूर्ण अन्यथा अणु
		/*
		 * To fix contention issues between ipsec (no blacklog) and
		 * dm-crypto (backlog) reserve 32 entries क्रम "no backlog"
		 * data contexts.
		 */
		is_busy = ((dev->pdr_head - dev->pdr_tail) % PPC4XX_NUM_PD) >=
			((PPC4XX_NUM_PD * 15) / 16);

		अगर (is_busy) अणु
			spin_unlock_irqrestore(&dev->core_dev->lock, flags);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	अगर (num_gd) अणु
		fst_gd = crypto4xx_get_n_gd(dev, num_gd);
		अगर (fst_gd == ERING_WAS_FULL) अणु
			spin_unlock_irqrestore(&dev->core_dev->lock, flags);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण
	अगर (num_sd) अणु
		fst_sd = crypto4xx_get_n_sd(dev, num_sd);
		अगर (fst_sd == ERING_WAS_FULL) अणु
			अगर (num_gd)
				dev->gdr_head = fst_gd;
			spin_unlock_irqrestore(&dev->core_dev->lock, flags);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण
	pd_entry = crypto4xx_get_pd_from_pdr_nolock(dev);
	अगर (pd_entry == ERING_WAS_FULL) अणु
		अगर (num_gd)
			dev->gdr_head = fst_gd;
		अगर (num_sd)
			dev->sdr_head = fst_sd;
		spin_unlock_irqrestore(&dev->core_dev->lock, flags);
		वापस -EAGAIN;
	पूर्ण
	spin_unlock_irqrestore(&dev->core_dev->lock, flags);

	pd = &dev->pdr[pd_entry];
	pd->sa_len = sa_len;

	pd_uinfo = &dev->pdr_uinfo[pd_entry];
	pd_uinfo->num_gd = num_gd;
	pd_uinfo->num_sd = num_sd;
	pd_uinfo->dest_va = dst;
	pd_uinfo->async_req = req;

	अगर (iv_len)
		स_नकल(pd_uinfo->sr_va->save_iv, iv, iv_len);

	sa = pd_uinfo->sa_va;
	स_नकल(sa, req_sa, sa_len * 4);

	sa->sa_command_1.bf.hash_crypto_offset = (assoclen >> 2);
	offset_to_sr_ptr = get_dynamic_sa_offset_state_ptr_field(sa);
	*(u32 *)((अचिन्हित दीर्घ)sa + offset_to_sr_ptr) = pd_uinfo->sr_pa;

	अगर (num_gd) अणु
		dma_addr_t gd_dma;
		काष्ठा scatterlist *sg;

		/* get first gd we are going to use */
		gd_idx = fst_gd;
		pd_uinfo->first_gd = fst_gd;
		gd = crypto4xx_get_gdp(dev, &gd_dma, gd_idx);
		pd->src = gd_dma;
		/* enable gather */
		sa->sa_command_0.bf.gather = 1;
		/* walk the sg, and setup gather array */

		sg = src;
		जबतक (nbytes) अणु
			माप_प्रकार len;

			len = min(sg->length, nbytes);
			gd->ptr = dma_map_page(dev->core_dev->device,
				sg_page(sg), sg->offset, len, DMA_TO_DEVICE);
			gd->ctl_len.len = len;
			gd->ctl_len.करोne = 0;
			gd->ctl_len.पढ़ोy = 1;
			अगर (len >= nbytes)
				अवरोध;

			nbytes -= sg->length;
			gd_idx = get_next_gd(gd_idx);
			gd = crypto4xx_get_gdp(dev, &gd_dma, gd_idx);
			sg = sg_next(sg);
		पूर्ण
	पूर्ण अन्यथा अणु
		pd->src = (u32)dma_map_page(dev->core_dev->device, sg_page(src),
				src->offset, min(nbytes, src->length),
				DMA_TO_DEVICE);
		/*
		 * Disable gather in sa command
		 */
		sa->sa_command_0.bf.gather = 0;
		/*
		 * Indicate gather array is not used
		 */
		pd_uinfo->first_gd = 0xffffffff;
	पूर्ण
	अगर (!num_sd) अणु
		/*
		 * we know application give us dst a whole piece of memory
		 * no need to use scatter ring.
		 */
		pd_uinfo->first_sd = 0xffffffff;
		sa->sa_command_0.bf.scatter = 0;
		pd->dest = (u32)dma_map_page(dev->core_dev->device,
					     sg_page(dst), dst->offset,
					     min(datalen, dst->length),
					     DMA_TO_DEVICE);
	पूर्ण अन्यथा अणु
		dma_addr_t sd_dma;
		काष्ठा ce_sd *sd = शून्य;

		u32 sd_idx = fst_sd;
		nbytes = datalen;
		sa->sa_command_0.bf.scatter = 1;
		pd_uinfo->first_sd = fst_sd;
		sd = crypto4xx_get_sdp(dev, &sd_dma, sd_idx);
		pd->dest = sd_dma;
		/* setup scatter descriptor */
		sd->ctl.करोne = 0;
		sd->ctl.rdy = 1;
		/* sd->ptr should be setup by sd_init routine*/
		अगर (nbytes >= PPC4XX_SD_BUFFER_SIZE)
			nbytes -= PPC4XX_SD_BUFFER_SIZE;
		अन्यथा
			nbytes = 0;
		जबतक (nbytes) अणु
			sd_idx = get_next_sd(sd_idx);
			sd = crypto4xx_get_sdp(dev, &sd_dma, sd_idx);
			/* setup scatter descriptor */
			sd->ctl.करोne = 0;
			sd->ctl.rdy = 1;
			अगर (nbytes >= PPC4XX_SD_BUFFER_SIZE) अणु
				nbytes -= PPC4XX_SD_BUFFER_SIZE;
			पूर्ण अन्यथा अणु
				/*
				 * SD entry can hold PPC4XX_SD_BUFFER_SIZE,
				 * which is more than nbytes, so करोne.
				 */
				nbytes = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	pd->pd_ctl.w = PD_CTL_HOST_READY |
		((crypto_tfm_alg_type(req->tfm) == CRYPTO_ALG_TYPE_AHASH) ||
		 (crypto_tfm_alg_type(req->tfm) == CRYPTO_ALG_TYPE_AEAD) ?
			PD_CTL_HASH_FINAL : 0);
	pd->pd_ctl_len.w = 0x00400000 | (assoclen + datalen);
	pd_uinfo->state = PD_ENTRY_INUSE | (is_busy ? PD_ENTRY_BUSY : 0);

	wmb();
	/* ग_लिखो any value to push engine to पढ़ो a pd */
	ग_लिखोl(0, dev->ce_base + CRYPTO4XX_INT_DESCR_RD);
	ग_लिखोl(1, dev->ce_base + CRYPTO4XX_INT_DESCR_RD);
	वापस is_busy ? -EBUSY : -EINPROGRESS;
पूर्ण

/*
 * Algorithm Registration Functions
 */
अटल व्योम crypto4xx_ctx_init(काष्ठा crypto4xx_alg *amcc_alg,
			       काष्ठा crypto4xx_ctx *ctx)
अणु
	ctx->dev = amcc_alg->dev;
	ctx->sa_in = शून्य;
	ctx->sa_out = शून्य;
	ctx->sa_len = 0;
पूर्ण

अटल पूर्णांक crypto4xx_sk_init(काष्ठा crypto_skcipher *sk)
अणु
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(sk);
	काष्ठा crypto4xx_alg *amcc_alg;
	काष्ठा crypto4xx_ctx *ctx =  crypto_skcipher_ctx(sk);

	अगर (alg->base.cra_flags & CRYPTO_ALG_NEED_FALLBACK) अणु
		ctx->sw_cipher.cipher =
			crypto_alloc_sync_skcipher(alg->base.cra_name, 0,
					      CRYPTO_ALG_NEED_FALLBACK);
		अगर (IS_ERR(ctx->sw_cipher.cipher))
			वापस PTR_ERR(ctx->sw_cipher.cipher);
	पूर्ण

	amcc_alg = container_of(alg, काष्ठा crypto4xx_alg, alg.u.cipher);
	crypto4xx_ctx_init(amcc_alg, ctx);
	वापस 0;
पूर्ण

अटल व्योम crypto4xx_common_निकास(काष्ठा crypto4xx_ctx *ctx)
अणु
	crypto4xx_मुक्त_sa(ctx);
पूर्ण

अटल व्योम crypto4xx_sk_निकास(काष्ठा crypto_skcipher *sk)
अणु
	काष्ठा crypto4xx_ctx *ctx =  crypto_skcipher_ctx(sk);

	crypto4xx_common_निकास(ctx);
	अगर (ctx->sw_cipher.cipher)
		crypto_मुक्त_sync_skcipher(ctx->sw_cipher.cipher);
पूर्ण

अटल पूर्णांक crypto4xx_aead_init(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा aead_alg *alg = crypto_aead_alg(tfm);
	काष्ठा crypto4xx_ctx *ctx = crypto_aead_ctx(tfm);
	काष्ठा crypto4xx_alg *amcc_alg;

	ctx->sw_cipher.aead = crypto_alloc_aead(alg->base.cra_name, 0,
						CRYPTO_ALG_NEED_FALLBACK |
						CRYPTO_ALG_ASYNC);
	अगर (IS_ERR(ctx->sw_cipher.aead))
		वापस PTR_ERR(ctx->sw_cipher.aead);

	amcc_alg = container_of(alg, काष्ठा crypto4xx_alg, alg.u.aead);
	crypto4xx_ctx_init(amcc_alg, ctx);
	crypto_aead_set_reqsize(tfm, max(माप(काष्ठा aead_request) + 32 +
				crypto_aead_reqsize(ctx->sw_cipher.aead),
				माप(काष्ठा crypto4xx_aead_reqctx)));
	वापस 0;
पूर्ण

अटल व्योम crypto4xx_aead_निकास(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा crypto4xx_ctx *ctx = crypto_aead_ctx(tfm);

	crypto4xx_common_निकास(ctx);
	crypto_मुक्त_aead(ctx->sw_cipher.aead);
पूर्ण

अटल पूर्णांक crypto4xx_रेजिस्टर_alg(काष्ठा crypto4xx_device *sec_dev,
				  काष्ठा crypto4xx_alg_common *crypto_alg,
				  पूर्णांक array_size)
अणु
	काष्ठा crypto4xx_alg *alg;
	पूर्णांक i;
	पूर्णांक rc = 0;

	क्रम (i = 0; i < array_size; i++) अणु
		alg = kzalloc(माप(काष्ठा crypto4xx_alg), GFP_KERNEL);
		अगर (!alg)
			वापस -ENOMEM;

		alg->alg = crypto_alg[i];
		alg->dev = sec_dev;

		चयन (alg->alg.type) अणु
		हाल CRYPTO_ALG_TYPE_AEAD:
			rc = crypto_रेजिस्टर_aead(&alg->alg.u.aead);
			अवरोध;

		हाल CRYPTO_ALG_TYPE_AHASH:
			rc = crypto_रेजिस्टर_ahash(&alg->alg.u.hash);
			अवरोध;

		हाल CRYPTO_ALG_TYPE_RNG:
			rc = crypto_रेजिस्टर_rng(&alg->alg.u.rng);
			अवरोध;

		शेष:
			rc = crypto_रेजिस्टर_skcipher(&alg->alg.u.cipher);
			अवरोध;
		पूर्ण

		अगर (rc)
			kमुक्त(alg);
		अन्यथा
			list_add_tail(&alg->entry, &sec_dev->alg_list);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम crypto4xx_unरेजिस्टर_alg(काष्ठा crypto4xx_device *sec_dev)
अणु
	काष्ठा crypto4xx_alg *alg, *पंचांगp;

	list_क्रम_each_entry_safe(alg, पंचांगp, &sec_dev->alg_list, entry) अणु
		list_del(&alg->entry);
		चयन (alg->alg.type) अणु
		हाल CRYPTO_ALG_TYPE_AHASH:
			crypto_unरेजिस्टर_ahash(&alg->alg.u.hash);
			अवरोध;

		हाल CRYPTO_ALG_TYPE_AEAD:
			crypto_unरेजिस्टर_aead(&alg->alg.u.aead);
			अवरोध;

		हाल CRYPTO_ALG_TYPE_RNG:
			crypto_unरेजिस्टर_rng(&alg->alg.u.rng);
			अवरोध;

		शेष:
			crypto_unरेजिस्टर_skcipher(&alg->alg.u.cipher);
		पूर्ण
		kमुक्त(alg);
	पूर्ण
पूर्ण

अटल व्योम crypto4xx_bh_tasklet_cb(अचिन्हित दीर्घ data)
अणु
	काष्ठा device *dev = (काष्ठा device *)data;
	काष्ठा crypto4xx_core_device *core_dev = dev_get_drvdata(dev);
	काष्ठा pd_uinfo *pd_uinfo;
	काष्ठा ce_pd *pd;
	u32 tail = core_dev->dev->pdr_tail;
	u32 head = core_dev->dev->pdr_head;

	करो अणु
		pd_uinfo = &core_dev->dev->pdr_uinfo[tail];
		pd = &core_dev->dev->pdr[tail];
		अगर ((pd_uinfo->state & PD_ENTRY_INUSE) &&
		     ((READ_ONCE(pd->pd_ctl.w) &
		       (PD_CTL_PE_DONE | PD_CTL_HOST_READY)) ==
		       PD_CTL_PE_DONE)) अणु
			crypto4xx_pd_करोne(core_dev->dev, tail);
			tail = crypto4xx_put_pd_to_pdr(core_dev->dev, tail);
		पूर्ण अन्यथा अणु
			/* अगर tail not करोne, अवरोध */
			अवरोध;
		पूर्ण
	पूर्ण जबतक (head != tail);
पूर्ण

/*
 * Top Half of isr.
 */
अटल अंतरभूत irqवापस_t crypto4xx_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *data,
						      u32 clr_val)
अणु
	काष्ठा device *dev = (काष्ठा device *)data;
	काष्ठा crypto4xx_core_device *core_dev = dev_get_drvdata(dev);

	ग_लिखोl(clr_val, core_dev->dev->ce_base + CRYPTO4XX_INT_CLR);
	tasklet_schedule(&core_dev->tasklet);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t crypto4xx_ce_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *data)
अणु
	वापस crypto4xx_पूर्णांकerrupt_handler(irq, data, PPC4XX_INTERRUPT_CLR);
पूर्ण

अटल irqवापस_t crypto4xx_ce_पूर्णांकerrupt_handler_revb(पूर्णांक irq, व्योम *data)
अणु
	वापस crypto4xx_पूर्णांकerrupt_handler(irq, data, PPC4XX_INTERRUPT_CLR |
		PPC4XX_TMO_ERR_INT);
पूर्ण

अटल पूर्णांक ppc4xx_prng_data_पढ़ो(काष्ठा crypto4xx_device *dev,
				 u8 *data, अचिन्हित पूर्णांक max)
अणु
	अचिन्हित पूर्णांक i, curr = 0;
	u32 val[2];

	करो अणु
		/* trigger PRN generation */
		ग_लिखोl(PPC4XX_PRNG_CTRL_AUTO_EN,
		       dev->ce_base + CRYPTO4XX_PRNG_CTRL);

		क्रम (i = 0; i < 1024; i++) अणु
			/* usually 19 iterations are enough */
			अगर ((पढ़ोl(dev->ce_base + CRYPTO4XX_PRNG_STAT) &
			     CRYPTO4XX_PRNG_STAT_BUSY))
				जारी;

			val[0] = पढ़ोl_be(dev->ce_base + CRYPTO4XX_PRNG_RES_0);
			val[1] = पढ़ोl_be(dev->ce_base + CRYPTO4XX_PRNG_RES_1);
			अवरोध;
		पूर्ण
		अगर (i == 1024)
			वापस -ETIMEDOUT;

		अगर ((max - curr) >= 8) अणु
			स_नकल(data, &val, 8);
			data += 8;
			curr += 8;
		पूर्ण अन्यथा अणु
			/* copy only reमुख्यing bytes */
			स_नकल(data, &val, max - curr);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (curr < max);

	वापस curr;
पूर्ण

अटल पूर्णांक crypto4xx_prng_generate(काष्ठा crypto_rng *tfm,
				   स्थिर u8 *src, अचिन्हित पूर्णांक slen,
				   u8 *dstn, अचिन्हित पूर्णांक dlen)
अणु
	काष्ठा rng_alg *alg = crypto_rng_alg(tfm);
	काष्ठा crypto4xx_alg *amcc_alg;
	काष्ठा crypto4xx_device *dev;
	पूर्णांक ret;

	amcc_alg = container_of(alg, काष्ठा crypto4xx_alg, alg.u.rng);
	dev = amcc_alg->dev;

	mutex_lock(&dev->core_dev->rng_lock);
	ret = ppc4xx_prng_data_पढ़ो(dev, dstn, dlen);
	mutex_unlock(&dev->core_dev->rng_lock);
	वापस ret;
पूर्ण


अटल पूर्णांक crypto4xx_prng_seed(काष्ठा crypto_rng *tfm, स्थिर u8 *seed,
			अचिन्हित पूर्णांक slen)
अणु
	वापस 0;
पूर्ण

/*
 * Supported Crypto Algorithms
 */
अटल काष्ठा crypto4xx_alg_common crypto4xx_alg[] = अणु
	/* Crypto AES modes */
	अणु .type = CRYPTO_ALG_TYPE_SKCIPHER, .u.cipher = अणु
		.base = अणु
			.cra_name = "cbc(aes)",
			.cra_driver_name = "cbc-aes-ppc4xx",
			.cra_priority = CRYPTO4XX_CRYPTO_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा crypto4xx_ctx),
			.cra_module = THIS_MODULE,
		पूर्ण,
		.min_keysize = AES_MIN_KEY_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE,
		.ivsize	= AES_IV_SIZE,
		.setkey = crypto4xx_setkey_aes_cbc,
		.encrypt = crypto4xx_encrypt_iv_block,
		.decrypt = crypto4xx_decrypt_iv_block,
		.init = crypto4xx_sk_init,
		.निकास = crypto4xx_sk_निकास,
	पूर्ण पूर्ण,
	अणु .type = CRYPTO_ALG_TYPE_SKCIPHER, .u.cipher = अणु
		.base = अणु
			.cra_name = "cfb(aes)",
			.cra_driver_name = "cfb-aes-ppc4xx",
			.cra_priority = CRYPTO4XX_CRYPTO_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा crypto4xx_ctx),
			.cra_module = THIS_MODULE,
		पूर्ण,
		.min_keysize = AES_MIN_KEY_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE,
		.ivsize	= AES_IV_SIZE,
		.setkey	= crypto4xx_setkey_aes_cfb,
		.encrypt = crypto4xx_encrypt_iv_stream,
		.decrypt = crypto4xx_decrypt_iv_stream,
		.init = crypto4xx_sk_init,
		.निकास = crypto4xx_sk_निकास,
	पूर्ण पूर्ण,
	अणु .type = CRYPTO_ALG_TYPE_SKCIPHER, .u.cipher = अणु
		.base = अणु
			.cra_name = "ctr(aes)",
			.cra_driver_name = "ctr-aes-ppc4xx",
			.cra_priority = CRYPTO4XX_CRYPTO_PRIORITY,
			.cra_flags = CRYPTO_ALG_NEED_FALLBACK |
				CRYPTO_ALG_ASYNC |
				CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा crypto4xx_ctx),
			.cra_module = THIS_MODULE,
		पूर्ण,
		.min_keysize = AES_MIN_KEY_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE,
		.ivsize	= AES_IV_SIZE,
		.setkey	= crypto4xx_setkey_aes_ctr,
		.encrypt = crypto4xx_encrypt_ctr,
		.decrypt = crypto4xx_decrypt_ctr,
		.init = crypto4xx_sk_init,
		.निकास = crypto4xx_sk_निकास,
	पूर्ण पूर्ण,
	अणु .type = CRYPTO_ALG_TYPE_SKCIPHER, .u.cipher = अणु
		.base = अणु
			.cra_name = "rfc3686(ctr(aes))",
			.cra_driver_name = "rfc3686-ctr-aes-ppc4xx",
			.cra_priority = CRYPTO4XX_CRYPTO_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा crypto4xx_ctx),
			.cra_module = THIS_MODULE,
		पूर्ण,
		.min_keysize = AES_MIN_KEY_SIZE + CTR_RFC3686_NONCE_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE + CTR_RFC3686_NONCE_SIZE,
		.ivsize	= CTR_RFC3686_IV_SIZE,
		.setkey = crypto4xx_setkey_rfc3686,
		.encrypt = crypto4xx_rfc3686_encrypt,
		.decrypt = crypto4xx_rfc3686_decrypt,
		.init = crypto4xx_sk_init,
		.निकास = crypto4xx_sk_निकास,
	पूर्ण पूर्ण,
	अणु .type = CRYPTO_ALG_TYPE_SKCIPHER, .u.cipher = अणु
		.base = अणु
			.cra_name = "ecb(aes)",
			.cra_driver_name = "ecb-aes-ppc4xx",
			.cra_priority = CRYPTO4XX_CRYPTO_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = AES_BLOCK_SIZE,
			.cra_ctxsize = माप(काष्ठा crypto4xx_ctx),
			.cra_module = THIS_MODULE,
		पूर्ण,
		.min_keysize = AES_MIN_KEY_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE,
		.setkey	= crypto4xx_setkey_aes_ecb,
		.encrypt = crypto4xx_encrypt_noiv_block,
		.decrypt = crypto4xx_decrypt_noiv_block,
		.init = crypto4xx_sk_init,
		.निकास = crypto4xx_sk_निकास,
	पूर्ण पूर्ण,
	अणु .type = CRYPTO_ALG_TYPE_SKCIPHER, .u.cipher = अणु
		.base = अणु
			.cra_name = "ofb(aes)",
			.cra_driver_name = "ofb-aes-ppc4xx",
			.cra_priority = CRYPTO4XX_CRYPTO_PRIORITY,
			.cra_flags = CRYPTO_ALG_ASYNC |
				CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize = 1,
			.cra_ctxsize = माप(काष्ठा crypto4xx_ctx),
			.cra_module = THIS_MODULE,
		पूर्ण,
		.min_keysize = AES_MIN_KEY_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE,
		.ivsize	= AES_IV_SIZE,
		.setkey	= crypto4xx_setkey_aes_ofb,
		.encrypt = crypto4xx_encrypt_iv_stream,
		.decrypt = crypto4xx_decrypt_iv_stream,
		.init = crypto4xx_sk_init,
		.निकास = crypto4xx_sk_निकास,
	पूर्ण पूर्ण,

	/* AEAD */
	अणु .type = CRYPTO_ALG_TYPE_AEAD, .u.aead = अणु
		.setkey		= crypto4xx_setkey_aes_ccm,
		.setauthsize	= crypto4xx_setauthsize_aead,
		.encrypt	= crypto4xx_encrypt_aes_ccm,
		.decrypt	= crypto4xx_decrypt_aes_ccm,
		.init		= crypto4xx_aead_init,
		.निकास		= crypto4xx_aead_निकास,
		.ivsize		= AES_BLOCK_SIZE,
		.maxauthsize    = 16,
		.base = अणु
			.cra_name	= "ccm(aes)",
			.cra_driver_name = "ccm-aes-ppc4xx",
			.cra_priority	= CRYPTO4XX_CRYPTO_PRIORITY,
			.cra_flags	= CRYPTO_ALG_ASYNC |
					  CRYPTO_ALG_NEED_FALLBACK |
					  CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize	= 1,
			.cra_ctxsize	= माप(काष्ठा crypto4xx_ctx),
			.cra_module	= THIS_MODULE,
		पूर्ण,
	पूर्ण पूर्ण,
	अणु .type = CRYPTO_ALG_TYPE_AEAD, .u.aead = अणु
		.setkey		= crypto4xx_setkey_aes_gcm,
		.setauthsize	= crypto4xx_setauthsize_aead,
		.encrypt	= crypto4xx_encrypt_aes_gcm,
		.decrypt	= crypto4xx_decrypt_aes_gcm,
		.init		= crypto4xx_aead_init,
		.निकास		= crypto4xx_aead_निकास,
		.ivsize		= GCM_AES_IV_SIZE,
		.maxauthsize	= 16,
		.base = अणु
			.cra_name	= "gcm(aes)",
			.cra_driver_name = "gcm-aes-ppc4xx",
			.cra_priority	= CRYPTO4XX_CRYPTO_PRIORITY,
			.cra_flags	= CRYPTO_ALG_ASYNC |
					  CRYPTO_ALG_NEED_FALLBACK |
					  CRYPTO_ALG_KERN_DRIVER_ONLY,
			.cra_blocksize	= 1,
			.cra_ctxsize	= माप(काष्ठा crypto4xx_ctx),
			.cra_module	= THIS_MODULE,
		पूर्ण,
	पूर्ण पूर्ण,
	अणु .type = CRYPTO_ALG_TYPE_RNG, .u.rng = अणु
		.base = अणु
			.cra_name		= "stdrng",
			.cra_driver_name        = "crypto4xx_rng",
			.cra_priority		= 300,
			.cra_ctxsize		= 0,
			.cra_module		= THIS_MODULE,
		पूर्ण,
		.generate               = crypto4xx_prng_generate,
		.seed                   = crypto4xx_prng_seed,
		.seedsize               = 0,
	पूर्ण पूर्ण,
पूर्ण;

/*
 * Module Initialization Routine
 */
अटल पूर्णांक crypto4xx_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	पूर्णांक rc;
	काष्ठा resource res;
	काष्ठा device *dev = &ofdev->dev;
	काष्ठा crypto4xx_core_device *core_dev;
	u32 pvr;
	bool is_revb = true;

	rc = of_address_to_resource(ofdev->dev.of_node, 0, &res);
	अगर (rc)
		वापस -ENODEV;

	अगर (of_find_compatible_node(शून्य, शून्य, "amcc,ppc460ex-crypto")) अणु
		mtdcri(SDR0, PPC460EX_SDR0_SRST,
		       mfdcri(SDR0, PPC460EX_SDR0_SRST) | PPC460EX_CE_RESET);
		mtdcri(SDR0, PPC460EX_SDR0_SRST,
		       mfdcri(SDR0, PPC460EX_SDR0_SRST) & ~PPC460EX_CE_RESET);
	पूर्ण अन्यथा अगर (of_find_compatible_node(शून्य, शून्य,
			"amcc,ppc405ex-crypto")) अणु
		mtdcri(SDR0, PPC405EX_SDR0_SRST,
		       mfdcri(SDR0, PPC405EX_SDR0_SRST) | PPC405EX_CE_RESET);
		mtdcri(SDR0, PPC405EX_SDR0_SRST,
		       mfdcri(SDR0, PPC405EX_SDR0_SRST) & ~PPC405EX_CE_RESET);
		is_revb = false;
	पूर्ण अन्यथा अगर (of_find_compatible_node(शून्य, शून्य,
			"amcc,ppc460sx-crypto")) अणु
		mtdcri(SDR0, PPC460SX_SDR0_SRST,
		       mfdcri(SDR0, PPC460SX_SDR0_SRST) | PPC460SX_CE_RESET);
		mtdcri(SDR0, PPC460SX_SDR0_SRST,
		       mfdcri(SDR0, PPC460SX_SDR0_SRST) & ~PPC460SX_CE_RESET);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "Crypto Function Not supported!\n");
		वापस -EINVAL;
	पूर्ण

	core_dev = kzalloc(माप(काष्ठा crypto4xx_core_device), GFP_KERNEL);
	अगर (!core_dev)
		वापस -ENOMEM;

	dev_set_drvdata(dev, core_dev);
	core_dev->ofdev = ofdev;
	core_dev->dev = kzalloc(माप(काष्ठा crypto4xx_device), GFP_KERNEL);
	rc = -ENOMEM;
	अगर (!core_dev->dev)
		जाओ err_alloc_dev;

	/*
	 * Older version of 460EX/GT have a hardware bug.
	 * Hence they करो not support H/W based security पूर्णांकr coalescing
	 */
	pvr = mfspr(SPRN_PVR);
	अगर (is_revb && ((pvr >> 4) == 0x130218A)) अणु
		u32 min = PVR_MIN(pvr);

		अगर (min < 4) अणु
			dev_info(dev, "RevA detected - disable interrupt coalescing\n");
			is_revb = false;
		पूर्ण
	पूर्ण

	core_dev->dev->core_dev = core_dev;
	core_dev->dev->is_revb = is_revb;
	core_dev->device = dev;
	mutex_init(&core_dev->rng_lock);
	spin_lock_init(&core_dev->lock);
	INIT_LIST_HEAD(&core_dev->dev->alg_list);
	ratelimit_शेष_init(&core_dev->dev->aead_ratelimit);
	rc = crypto4xx_build_sdr(core_dev->dev);
	अगर (rc)
		जाओ err_build_sdr;
	rc = crypto4xx_build_pdr(core_dev->dev);
	अगर (rc)
		जाओ err_build_sdr;

	rc = crypto4xx_build_gdr(core_dev->dev);
	अगर (rc)
		जाओ err_build_sdr;

	/* Init tasklet क्रम bottom half processing */
	tasklet_init(&core_dev->tasklet, crypto4xx_bh_tasklet_cb,
		     (अचिन्हित दीर्घ) dev);

	core_dev->dev->ce_base = of_iomap(ofdev->dev.of_node, 0);
	अगर (!core_dev->dev->ce_base) अणु
		dev_err(dev, "failed to of_iomap\n");
		rc = -ENOMEM;
		जाओ err_iomap;
	पूर्ण

	/* Register क्रम Crypto isr, Crypto Engine IRQ */
	core_dev->irq = irq_of_parse_and_map(ofdev->dev.of_node, 0);
	rc = request_irq(core_dev->irq, is_revb ?
			 crypto4xx_ce_पूर्णांकerrupt_handler_revb :
			 crypto4xx_ce_पूर्णांकerrupt_handler, 0,
			 KBUILD_MODNAME, dev);
	अगर (rc)
		जाओ err_request_irq;

	/* need to setup pdr, rdr, gdr and sdr beक्रमe this */
	crypto4xx_hw_init(core_dev->dev);

	/* Register security algorithms with Linux CryptoAPI */
	rc = crypto4xx_रेजिस्टर_alg(core_dev->dev, crypto4xx_alg,
			       ARRAY_SIZE(crypto4xx_alg));
	अगर (rc)
		जाओ err_start_dev;

	ppc4xx_trng_probe(core_dev);
	वापस 0;

err_start_dev:
	मुक्त_irq(core_dev->irq, dev);
err_request_irq:
	irq_dispose_mapping(core_dev->irq);
	iounmap(core_dev->dev->ce_base);
err_iomap:
	tasklet_समाप्त(&core_dev->tasklet);
err_build_sdr:
	crypto4xx_destroy_sdr(core_dev->dev);
	crypto4xx_destroy_gdr(core_dev->dev);
	crypto4xx_destroy_pdr(core_dev->dev);
	kमुक्त(core_dev->dev);
err_alloc_dev:
	kमुक्त(core_dev);

	वापस rc;
पूर्ण

अटल पूर्णांक crypto4xx_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा device *dev = &ofdev->dev;
	काष्ठा crypto4xx_core_device *core_dev = dev_get_drvdata(dev);

	ppc4xx_trng_हटाओ(core_dev);

	मुक्त_irq(core_dev->irq, dev);
	irq_dispose_mapping(core_dev->irq);

	tasklet_समाप्त(&core_dev->tasklet);
	/* Un-रेजिस्टर with Linux CryptoAPI */
	crypto4xx_unरेजिस्टर_alg(core_dev->dev);
	mutex_destroy(&core_dev->rng_lock);
	/* Free all allocated memory */
	crypto4xx_stop_all(core_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id crypto4xx_match[] = अणु
	अणु .compatible      = "amcc,ppc4xx-crypto",पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, crypto4xx_match);

अटल काष्ठा platक्रमm_driver crypto4xx_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = crypto4xx_match,
	पूर्ण,
	.probe		= crypto4xx_probe,
	.हटाओ		= crypto4xx_हटाओ,
पूर्ण;

module_platक्रमm_driver(crypto4xx_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("James Hsiao <jhsiao@amcc.com>");
MODULE_DESCRIPTION("Driver for AMCC PPC4xx crypto accelerator");
