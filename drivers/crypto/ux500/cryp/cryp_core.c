<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2010
 * Author: Shujuan Chen <shujuan.chen@stericsson.com> क्रम ST-Ericsson.
 * Author: Joakim Bech <joakim.xx.bech@stericsson.com> क्रम ST-Ericsson.
 * Author: Berne Hebark <berne.herbark@stericsson.com> क्रम ST-Ericsson.
 * Author: Niklas Hernaeus <niklas.hernaeus@stericsson.com> क्रम ST-Ericsson.
 * Author: Jonas Linde <jonas.linde@stericsson.com> क्रम ST-Ericsson.
 * Author: Andreas Westin <andreas.westin@stericsson.com> क्रम ST-Ericsson.
 */

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqवापस.h>
#समावेश <linux/kernel.h>
#समावेश <linux/klist.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/platक्रमm_data/dma-ste-dma40.h>

#समावेश <crypto/aes.h>
#समावेश <crypto/ctr.h>
#समावेश <crypto/पूर्णांकernal/des.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/scatterwalk.h>

#समावेश <linux/platक्रमm_data/crypto-ux500.h>

#समावेश "cryp_p.h"
#समावेश "cryp.h"

#घोषणा CRYP_MAX_KEY_SIZE	32
#घोषणा BYTES_PER_WORD		4

अटल पूर्णांक cryp_mode;
अटल atomic_t session_id;

अटल काष्ठा stedma40_chan_cfg *mem_to_engine;
अटल काष्ठा stedma40_chan_cfg *engine_to_mem;

/**
 * काष्ठा cryp_driver_data - data specअगरic to the driver.
 *
 * @device_list: A list of रेजिस्टरed devices to choose from.
 * @device_allocation: A semaphore initialized with number of devices.
 */
काष्ठा cryp_driver_data अणु
	काष्ठा klist device_list;
	काष्ठा semaphore device_allocation;
पूर्ण;

/**
 * काष्ठा cryp_ctx - Crypto context
 * @config: Crypto mode.
 * @key: Key array.
 * @keylen: Length of key.
 * @iv: Poपूर्णांकer to initialization vector.
 * @indata: Poपूर्णांकer to indata.
 * @outdata: Poपूर्णांकer to outdata.
 * @datalen: Length of indata.
 * @outlen: Length of outdata.
 * @blocksize: Size of blocks.
 * @updated: Updated flag.
 * @dev_ctx: Device dependent context.
 * @device: Poपूर्णांकer to the device.
 * @session_id: Atomic session ID.
 */
काष्ठा cryp_ctx अणु
	काष्ठा cryp_config config;
	u8 key[CRYP_MAX_KEY_SIZE];
	u32 keylen;
	u8 *iv;
	स्थिर u8 *indata;
	u8 *outdata;
	u32 datalen;
	u32 outlen;
	u32 blocksize;
	u8 updated;
	काष्ठा cryp_device_context dev_ctx;
	काष्ठा cryp_device_data *device;
	u32 session_id;
पूर्ण;

अटल काष्ठा cryp_driver_data driver_data;

/**
 * swap_bits_in_byte - mirror the bits in a byte
 * @b: the byte to be mirrored
 *
 * The bits are swapped the following way:
 *  Byte b include bits 0-7, nibble 1 (n1) include bits 0-3 and
 *  nibble 2 (n2) bits 4-7.
 *
 *  Nibble 1 (n1):
 *  (The "old" (moved) bit is replaced with a zero)
 *  1. Move bit 6 and 7, 4 positions to the left.
 *  2. Move bit 3 and 5, 2 positions to the left.
 *  3. Move bit 1-4, 1 position to the left.
 *
 *  Nibble 2 (n2):
 *  1. Move bit 0 and 1, 4 positions to the right.
 *  2. Move bit 2 and 4, 2 positions to the right.
 *  3. Move bit 3-6, 1 position to the right.
 *
 *  Combine the two nibbles to a complete and swapped byte.
 */

अटल अंतरभूत u8 swap_bits_in_byte(u8 b)
अणु
#घोषणा R_SHIFT_4_MASK  0xc0 /* Bits 6 and 7, right shअगरt 4 */
#घोषणा R_SHIFT_2_MASK  0x28 /* (After right shअगरt 4) Bits 3 and 5,
				  right shअगरt 2 */
#घोषणा R_SHIFT_1_MASK  0x1e /* (After right shअगरt 2) Bits 1-4,
				  right shअगरt 1 */
#घोषणा L_SHIFT_4_MASK  0x03 /* Bits 0 and 1, left shअगरt 4 */
#घोषणा L_SHIFT_2_MASK  0x14 /* (After left shअगरt 4) Bits 2 and 4,
				  left shअगरt 2 */
#घोषणा L_SHIFT_1_MASK  0x78 /* (After left shअगरt 1) Bits 3-6,
				  left shअगरt 1 */

	u8 n1;
	u8 n2;

	/* Swap most signअगरicant nibble */
	/* Right shअगरt 4, bits 6 and 7 */
	n1 = ((b  & R_SHIFT_4_MASK) >> 4) | (b  & ~(R_SHIFT_4_MASK >> 4));
	/* Right shअगरt 2, bits 3 and 5 */
	n1 = ((n1 & R_SHIFT_2_MASK) >> 2) | (n1 & ~(R_SHIFT_2_MASK >> 2));
	/* Right shअगरt 1, bits 1-4 */
	n1 = (n1  & R_SHIFT_1_MASK) >> 1;

	/* Swap least signअगरicant nibble */
	/* Left shअगरt 4, bits 0 and 1 */
	n2 = ((b  & L_SHIFT_4_MASK) << 4) | (b  & ~(L_SHIFT_4_MASK << 4));
	/* Left shअगरt 2, bits 2 and 4 */
	n2 = ((n2 & L_SHIFT_2_MASK) << 2) | (n2 & ~(L_SHIFT_2_MASK << 2));
	/* Left shअगरt 1, bits 3-6 */
	n2 = (n2  & L_SHIFT_1_MASK) << 1;

	वापस n1 | n2;
पूर्ण

अटल अंतरभूत व्योम swap_words_in_key_and_bits_in_byte(स्थिर u8 *in,
						      u8 *out, u32 len)
अणु
	अचिन्हित पूर्णांक i = 0;
	पूर्णांक j;
	पूर्णांक index = 0;

	j = len - BYTES_PER_WORD;
	जबतक (j >= 0) अणु
		क्रम (i = 0; i < BYTES_PER_WORD; i++) अणु
			index = len - j - BYTES_PER_WORD + i;
			out[j + i] =
				swap_bits_in_byte(in[index]);
		पूर्ण
		j -= BYTES_PER_WORD;
	पूर्ण
पूर्ण

अटल व्योम add_session_id(काष्ठा cryp_ctx *ctx)
अणु
	/*
	 * We never want 0 to be a valid value, since this is the शेष value
	 * क्रम the software context.
	 */
	अगर (unlikely(atomic_inc_and_test(&session_id)))
		atomic_inc(&session_id);

	ctx->session_id = atomic_पढ़ो(&session_id);
पूर्ण

अटल irqवापस_t cryp_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *param)
अणु
	काष्ठा cryp_ctx *ctx;
	पूर्णांक count;
	काष्ठा cryp_device_data *device_data;

	अगर (param == शून्य) अणु
		BUG_ON(!param);
		वापस IRQ_HANDLED;
	पूर्ण

	/* The device is coming from the one found in hw_crypt_noxts. */
	device_data = (काष्ठा cryp_device_data *)param;

	ctx = device_data->current_ctx;

	अगर (ctx == शून्य) अणु
		BUG_ON(!ctx);
		वापस IRQ_HANDLED;
	पूर्ण

	dev_dbg(ctx->device->dev, "[%s] (len: %d) %s, ", __func__, ctx->outlen,
		cryp_pending_irq_src(device_data, CRYP_IRQ_SRC_OUTPUT_FIFO) ?
		"out" : "in");

	अगर (cryp_pending_irq_src(device_data,
				 CRYP_IRQ_SRC_OUTPUT_FIFO)) अणु
		अगर (ctx->outlen / ctx->blocksize > 0) अणु
			count = ctx->blocksize / 4;

			पढ़ोsl(&device_data->base->करोut, ctx->outdata, count);
			ctx->outdata += count;
			ctx->outlen -= count;

			अगर (ctx->outlen == 0) अणु
				cryp_disable_irq_src(device_data,
						     CRYP_IRQ_SRC_OUTPUT_FIFO);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (cryp_pending_irq_src(device_data,
					CRYP_IRQ_SRC_INPUT_FIFO)) अणु
		अगर (ctx->datalen / ctx->blocksize > 0) अणु
			count = ctx->blocksize / 4;

			ग_लिखोsl(&device_data->base->din, ctx->indata, count);

			ctx->indata += count;
			ctx->datalen -= count;

			अगर (ctx->datalen == 0)
				cryp_disable_irq_src(device_data,
						   CRYP_IRQ_SRC_INPUT_FIFO);

			अगर (ctx->config.algomode == CRYP_ALGO_AES_XTS) अणु
				CRYP_PUT_BITS(&device_data->base->cr,
					      CRYP_START_ENABLE,
					      CRYP_CR_START_POS,
					      CRYP_CR_START_MASK);

				cryp_रुको_until_करोne(device_data);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mode_is_aes(क्रमागत cryp_algo_mode mode)
अणु
	वापस	CRYP_ALGO_AES_ECB == mode ||
		CRYP_ALGO_AES_CBC == mode ||
		CRYP_ALGO_AES_CTR == mode ||
		CRYP_ALGO_AES_XTS == mode;
पूर्ण

अटल पूर्णांक cfg_iv(काष्ठा cryp_device_data *device_data, u32 left, u32 right,
		  क्रमागत cryp_init_vector_index index)
अणु
	काष्ठा cryp_init_vector_value vector_value;

	dev_dbg(device_data->dev, "[%s]", __func__);

	vector_value.init_value_left = left;
	vector_value.init_value_right = right;

	वापस cryp_configure_init_vector(device_data,
					  index,
					  vector_value);
पूर्ण

अटल पूर्णांक cfg_ivs(काष्ठा cryp_device_data *device_data, काष्ठा cryp_ctx *ctx)
अणु
	पूर्णांक i;
	पूर्णांक status = 0;
	पूर्णांक num_of_regs = ctx->blocksize / 8;
	__be32 *civ = (__be32 *)ctx->iv;
	u32 iv[AES_BLOCK_SIZE / 4];

	dev_dbg(device_data->dev, "[%s]", __func__);

	/*
	 * Since we loop on num_of_regs we need to have a check in हाल
	 * someone provides an incorrect blocksize which would क्रमce calling
	 * cfg_iv with i greater than 2 which is an error.
	 */
	अगर (num_of_regs > 2) अणु
		dev_err(device_data->dev, "[%s] Incorrect blocksize %d",
			__func__, ctx->blocksize);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ctx->blocksize / 4; i++)
		iv[i] = be32_to_cpup(civ + i);

	क्रम (i = 0; i < num_of_regs; i++) अणु
		status = cfg_iv(device_data, iv[i*2], iv[i*2+1],
				(क्रमागत cryp_init_vector_index) i);
		अगर (status != 0)
			वापस status;
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक set_key(काष्ठा cryp_device_data *device_data,
		   u32 left_key,
		   u32 right_key,
		   क्रमागत cryp_key_reg_index index)
अणु
	काष्ठा cryp_key_value key_value;
	पूर्णांक cryp_error;

	dev_dbg(device_data->dev, "[%s]", __func__);

	key_value.key_value_left = left_key;
	key_value.key_value_right = right_key;

	cryp_error = cryp_configure_key_values(device_data,
					       index,
					       key_value);
	अगर (cryp_error != 0)
		dev_err(device_data->dev, "[%s]: "
			"cryp_configure_key_values() failed!", __func__);

	वापस cryp_error;
पूर्ण

अटल पूर्णांक cfg_keys(काष्ठा cryp_ctx *ctx)
अणु
	पूर्णांक i;
	पूर्णांक num_of_regs = ctx->keylen / 8;
	u32 swapped_key[CRYP_MAX_KEY_SIZE / 4];
	__be32 *ckey = (__be32 *)ctx->key;
	पूर्णांक cryp_error = 0;

	dev_dbg(ctx->device->dev, "[%s]", __func__);

	अगर (mode_is_aes(ctx->config.algomode)) अणु
		swap_words_in_key_and_bits_in_byte((u8 *)ckey,
						   (u8 *)swapped_key,
						   ctx->keylen);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < ctx->keylen / 4; i++)
			swapped_key[i] = be32_to_cpup(ckey + i);
	पूर्ण

	क्रम (i = 0; i < num_of_regs; i++) अणु
		cryp_error = set_key(ctx->device,
				     swapped_key[i * 2],
				     swapped_key[i * 2 + 1],
				     (क्रमागत cryp_key_reg_index) i);

		अगर (cryp_error != 0) अणु
			dev_err(ctx->device->dev, "[%s]: set_key() failed!",
					__func__);
			वापस cryp_error;
		पूर्ण
	पूर्ण
	वापस cryp_error;
पूर्ण

अटल पूर्णांक cryp_setup_context(काष्ठा cryp_ctx *ctx,
			      काष्ठा cryp_device_data *device_data)
अणु
	u32 control_रेजिस्टर = CRYP_CR_DEFAULT;

	चयन (cryp_mode) अणु
	हाल CRYP_MODE_INTERRUPT:
		ग_लिखोl_relaxed(CRYP_IMSC_DEFAULT, &device_data->base->imsc);
		अवरोध;

	हाल CRYP_MODE_DMA:
		ग_लिखोl_relaxed(CRYP_DMACR_DEFAULT, &device_data->base->dmacr);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (ctx->updated == 0) अणु
		cryp_flush_inoutfअगरo(device_data);
		अगर (cfg_keys(ctx) != 0) अणु
			dev_err(ctx->device->dev, "[%s]: cfg_keys failed!",
				__func__);
			वापस -EINVAL;
		पूर्ण

		अगर (ctx->iv &&
		    CRYP_ALGO_AES_ECB != ctx->config.algomode &&
		    CRYP_ALGO_DES_ECB != ctx->config.algomode &&
		    CRYP_ALGO_TDES_ECB != ctx->config.algomode) अणु
			अगर (cfg_ivs(device_data, ctx) != 0)
				वापस -EPERM;
		पूर्ण

		cryp_set_configuration(device_data, &ctx->config,
				       &control_रेजिस्टर);
		add_session_id(ctx);
	पूर्ण अन्यथा अगर (ctx->updated == 1 &&
		   ctx->session_id != atomic_पढ़ो(&session_id)) अणु
		cryp_flush_inoutfअगरo(device_data);
		cryp_restore_device_context(device_data, &ctx->dev_ctx);

		add_session_id(ctx);
		control_रेजिस्टर = ctx->dev_ctx.cr;
	पूर्ण अन्यथा
		control_रेजिस्टर = ctx->dev_ctx.cr;

	ग_लिखोl(control_रेजिस्टर |
	       (CRYP_CRYPEN_ENABLE << CRYP_CR_CRYPEN_POS),
	       &device_data->base->cr);

	वापस 0;
पूर्ण

अटल पूर्णांक cryp_get_device_data(काष्ठा cryp_ctx *ctx,
				काष्ठा cryp_device_data **device_data)
अणु
	पूर्णांक ret;
	काष्ठा klist_iter device_iterator;
	काष्ठा klist_node *device_node;
	काष्ठा cryp_device_data *local_device_data = शून्य;
	pr_debug(DEV_DBG_NAME " [%s]", __func__);

	/* Wait until a device is available */
	ret = करोwn_पूर्णांकerruptible(&driver_data.device_allocation);
	अगर (ret)
		वापस ret;  /* Interrupted */

	/* Select a device */
	klist_iter_init(&driver_data.device_list, &device_iterator);

	device_node = klist_next(&device_iterator);
	जबतक (device_node) अणु
		local_device_data = container_of(device_node,
					   काष्ठा cryp_device_data, list_node);
		spin_lock(&local_device_data->ctx_lock);
		/* current_ctx allocates a device, शून्य = unallocated */
		अगर (local_device_data->current_ctx) अणु
			device_node = klist_next(&device_iterator);
		पूर्ण अन्यथा अणु
			local_device_data->current_ctx = ctx;
			ctx->device = local_device_data;
			spin_unlock(&local_device_data->ctx_lock);
			अवरोध;
		पूर्ण
		spin_unlock(&local_device_data->ctx_lock);
	पूर्ण
	klist_iter_निकास(&device_iterator);

	अगर (!device_node) अणु
		/**
		 * No मुक्त device found.
		 * Since we allocated a device with करोwn_पूर्णांकerruptible, this
		 * should not be able to happen.
		 * Number of available devices, which are contained in
		 * device_allocation, is thereक्रमe decremented by not करोing
		 * an up(device_allocation).
		 */
		वापस -EBUSY;
	पूर्ण

	*device_data = local_device_data;

	वापस 0;
पूर्ण

अटल व्योम cryp_dma_setup_channel(काष्ठा cryp_device_data *device_data,
				   काष्ठा device *dev)
अणु
	काष्ठा dma_slave_config mem2cryp = अणु
		.direction = DMA_MEM_TO_DEV,
		.dst_addr = device_data->phybase + CRYP_DMA_TX_FIFO,
		.dst_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES,
		.dst_maxburst = 4,
	पूर्ण;
	काष्ठा dma_slave_config cryp2mem = अणु
		.direction = DMA_DEV_TO_MEM,
		.src_addr = device_data->phybase + CRYP_DMA_RX_FIFO,
		.src_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES,
		.src_maxburst = 4,
	पूर्ण;

	dma_cap_zero(device_data->dma.mask);
	dma_cap_set(DMA_SLAVE, device_data->dma.mask);

	device_data->dma.cfg_mem2cryp = mem_to_engine;
	device_data->dma.chan_mem2cryp =
		dma_request_channel(device_data->dma.mask,
				    stedma40_filter,
				    device_data->dma.cfg_mem2cryp);

	device_data->dma.cfg_cryp2mem = engine_to_mem;
	device_data->dma.chan_cryp2mem =
		dma_request_channel(device_data->dma.mask,
				    stedma40_filter,
				    device_data->dma.cfg_cryp2mem);

	dmaengine_slave_config(device_data->dma.chan_mem2cryp, &mem2cryp);
	dmaengine_slave_config(device_data->dma.chan_cryp2mem, &cryp2mem);

	init_completion(&device_data->dma.cryp_dma_complete);
पूर्ण

अटल व्योम cryp_dma_out_callback(व्योम *data)
अणु
	काष्ठा cryp_ctx *ctx = (काष्ठा cryp_ctx *) data;
	dev_dbg(ctx->device->dev, "[%s]: ", __func__);

	complete(&ctx->device->dma.cryp_dma_complete);
पूर्ण

अटल पूर्णांक cryp_set_dma_transfer(काष्ठा cryp_ctx *ctx,
				 काष्ठा scatterlist *sg,
				 पूर्णांक len,
				 क्रमागत dma_data_direction direction)
अणु
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा dma_chan *channel = शून्य;
	dma_cookie_t cookie;

	dev_dbg(ctx->device->dev, "[%s]: ", __func__);

	अगर (unlikely(!IS_ALIGNED((अचिन्हित दीर्घ)sg, 4))) अणु
		dev_err(ctx->device->dev, "[%s]: Data in sg list isn't "
			"aligned! Addr: 0x%08lx", __func__, (अचिन्हित दीर्घ)sg);
		वापस -EFAULT;
	पूर्ण

	चयन (direction) अणु
	हाल DMA_TO_DEVICE:
		channel = ctx->device->dma.chan_mem2cryp;
		ctx->device->dma.sg_src = sg;
		ctx->device->dma.sg_src_len = dma_map_sg(channel->device->dev,
						 ctx->device->dma.sg_src,
						 ctx->device->dma.nents_src,
						 direction);

		अगर (!ctx->device->dma.sg_src_len) अणु
			dev_dbg(ctx->device->dev,
				"[%s]: Could not map the sg list (TO_DEVICE)",
				__func__);
			वापस -EFAULT;
		पूर्ण

		dev_dbg(ctx->device->dev, "[%s]: Setting up DMA for buffer "
			"(TO_DEVICE)", __func__);

		desc = dmaengine_prep_slave_sg(channel,
				ctx->device->dma.sg_src,
				ctx->device->dma.sg_src_len,
				DMA_MEM_TO_DEV, DMA_CTRL_ACK);
		अवरोध;

	हाल DMA_FROM_DEVICE:
		channel = ctx->device->dma.chan_cryp2mem;
		ctx->device->dma.sg_dst = sg;
		ctx->device->dma.sg_dst_len = dma_map_sg(channel->device->dev,
						 ctx->device->dma.sg_dst,
						 ctx->device->dma.nents_dst,
						 direction);

		अगर (!ctx->device->dma.sg_dst_len) अणु
			dev_dbg(ctx->device->dev,
				"[%s]: Could not map the sg list (FROM_DEVICE)",
				__func__);
			वापस -EFAULT;
		पूर्ण

		dev_dbg(ctx->device->dev, "[%s]: Setting up DMA for buffer "
			"(FROM_DEVICE)", __func__);

		desc = dmaengine_prep_slave_sg(channel,
				ctx->device->dma.sg_dst,
				ctx->device->dma.sg_dst_len,
				DMA_DEV_TO_MEM,
				DMA_CTRL_ACK |
				DMA_PREP_INTERRUPT);

		desc->callback = cryp_dma_out_callback;
		desc->callback_param = ctx;
		अवरोध;

	शेष:
		dev_dbg(ctx->device->dev, "[%s]: Invalid DMA direction",
			__func__);
		वापस -EFAULT;
	पूर्ण

	cookie = dmaengine_submit(desc);
	अगर (dma_submit_error(cookie)) अणु
		dev_dbg(ctx->device->dev, "[%s]: DMA submission failed\n",
			__func__);
		वापस cookie;
	पूर्ण

	dma_async_issue_pending(channel);

	वापस 0;
पूर्ण

अटल व्योम cryp_dma_करोne(काष्ठा cryp_ctx *ctx)
अणु
	काष्ठा dma_chan *chan;

	dev_dbg(ctx->device->dev, "[%s]: ", __func__);

	chan = ctx->device->dma.chan_mem2cryp;
	dmaengine_terminate_all(chan);
	dma_unmap_sg(chan->device->dev, ctx->device->dma.sg_src,
		     ctx->device->dma.nents_src, DMA_TO_DEVICE);

	chan = ctx->device->dma.chan_cryp2mem;
	dmaengine_terminate_all(chan);
	dma_unmap_sg(chan->device->dev, ctx->device->dma.sg_dst,
		     ctx->device->dma.nents_dst, DMA_FROM_DEVICE);
पूर्ण

अटल पूर्णांक cryp_dma_ग_लिखो(काष्ठा cryp_ctx *ctx, काष्ठा scatterlist *sg,
			  पूर्णांक len)
अणु
	पूर्णांक error = cryp_set_dma_transfer(ctx, sg, len, DMA_TO_DEVICE);
	dev_dbg(ctx->device->dev, "[%s]: ", __func__);

	अगर (error) अणु
		dev_dbg(ctx->device->dev, "[%s]: cryp_set_dma_transfer() "
			"failed", __func__);
		वापस error;
	पूर्ण

	वापस len;
पूर्ण

अटल पूर्णांक cryp_dma_पढ़ो(काष्ठा cryp_ctx *ctx, काष्ठा scatterlist *sg, पूर्णांक len)
अणु
	पूर्णांक error = cryp_set_dma_transfer(ctx, sg, len, DMA_FROM_DEVICE);
	अगर (error) अणु
		dev_dbg(ctx->device->dev, "[%s]: cryp_set_dma_transfer() "
			"failed", __func__);
		वापस error;
	पूर्ण

	वापस len;
पूर्ण

अटल व्योम cryp_polling_mode(काष्ठा cryp_ctx *ctx,
			      काष्ठा cryp_device_data *device_data)
अणु
	पूर्णांक len = ctx->blocksize / BYTES_PER_WORD;
	पूर्णांक reमुख्यing_length = ctx->datalen;
	u32 *indata = (u32 *)ctx->indata;
	u32 *outdata = (u32 *)ctx->outdata;

	जबतक (reमुख्यing_length > 0) अणु
		ग_लिखोsl(&device_data->base->din, indata, len);
		indata += len;
		reमुख्यing_length -= (len * BYTES_PER_WORD);
		cryp_रुको_until_करोne(device_data);

		पढ़ोsl(&device_data->base->करोut, outdata, len);
		outdata += len;
		cryp_रुको_until_करोne(device_data);
	पूर्ण
पूर्ण

अटल पूर्णांक cryp_disable_घातer(काष्ठा device *dev,
			      काष्ठा cryp_device_data *device_data,
			      bool save_device_context)
अणु
	पूर्णांक ret = 0;

	dev_dbg(dev, "[%s]", __func__);

	spin_lock(&device_data->घातer_state_spinlock);
	अगर (!device_data->घातer_state)
		जाओ out;

	spin_lock(&device_data->ctx_lock);
	अगर (save_device_context && device_data->current_ctx) अणु
		cryp_save_device_context(device_data,
				&device_data->current_ctx->dev_ctx,
				cryp_mode);
		device_data->restore_dev_ctx = true;
	पूर्ण
	spin_unlock(&device_data->ctx_lock);

	clk_disable(device_data->clk);
	ret = regulator_disable(device_data->pwr_regulator);
	अगर (ret)
		dev_err(dev, "[%s]: "
				"regulator_disable() failed!",
				__func__);

	device_data->घातer_state = false;

out:
	spin_unlock(&device_data->घातer_state_spinlock);

	वापस ret;
पूर्ण

अटल पूर्णांक cryp_enable_घातer(
		काष्ठा device *dev,
		काष्ठा cryp_device_data *device_data,
		bool restore_device_context)
अणु
	पूर्णांक ret = 0;

	dev_dbg(dev, "[%s]", __func__);

	spin_lock(&device_data->घातer_state_spinlock);
	अगर (!device_data->घातer_state) अणु
		ret = regulator_enable(device_data->pwr_regulator);
		अगर (ret) अणु
			dev_err(dev, "[%s]: regulator_enable() failed!",
					__func__);
			जाओ out;
		पूर्ण

		ret = clk_enable(device_data->clk);
		अगर (ret) अणु
			dev_err(dev, "[%s]: clk_enable() failed!",
					__func__);
			regulator_disable(device_data->pwr_regulator);
			जाओ out;
		पूर्ण
		device_data->घातer_state = true;
	पूर्ण

	अगर (device_data->restore_dev_ctx) अणु
		spin_lock(&device_data->ctx_lock);
		अगर (restore_device_context && device_data->current_ctx) अणु
			device_data->restore_dev_ctx = false;
			cryp_restore_device_context(device_data,
					&device_data->current_ctx->dev_ctx);
		पूर्ण
		spin_unlock(&device_data->ctx_lock);
	पूर्ण
out:
	spin_unlock(&device_data->घातer_state_spinlock);

	वापस ret;
पूर्ण

अटल पूर्णांक hw_crypt_noxts(काष्ठा cryp_ctx *ctx,
			  काष्ठा cryp_device_data *device_data)
अणु
	पूर्णांक ret = 0;

	स्थिर u8 *indata = ctx->indata;
	u8 *outdata = ctx->outdata;
	u32 datalen = ctx->datalen;
	u32 outlen = datalen;

	pr_debug(DEV_DBG_NAME " [%s]", __func__);

	ctx->outlen = ctx->datalen;

	अगर (unlikely(!IS_ALIGNED((अचिन्हित दीर्घ)indata, 4))) अणु
		pr_debug(DEV_DBG_NAME " [%s]: Data isn't aligned! Addr: "
			 "0x%08lx", __func__, (अचिन्हित दीर्घ)indata);
		वापस -EINVAL;
	पूर्ण

	ret = cryp_setup_context(ctx, device_data);

	अगर (ret)
		जाओ out;

	अगर (cryp_mode == CRYP_MODE_INTERRUPT) अणु
		cryp_enable_irq_src(device_data, CRYP_IRQ_SRC_INPUT_FIFO |
				    CRYP_IRQ_SRC_OUTPUT_FIFO);

		/*
		 * ctx->outlen is decremented in the cryp_पूर्णांकerrupt_handler
		 * function. We had to add cpu_relax() (barrier) to make sure
		 * that gcc didn't optimze away this variable.
		 */
		जबतक (ctx->outlen > 0)
			cpu_relax();
	पूर्ण अन्यथा अगर (cryp_mode == CRYP_MODE_POLLING ||
		   cryp_mode == CRYP_MODE_DMA) अणु
		/*
		 * The reason क्रम having DMA in this अगर हाल is that अगर we are
		 * running cryp_mode = 2, then we separate DMA routines क्रम
		 * handling cipher/plaपूर्णांकext > blocksize, except when
		 * running the normal CRYPTO_ALG_TYPE_CIPHER, then we still use
		 * the polling mode. Overhead of करोing DMA setup eats up the
		 * benefits using it.
		 */
		cryp_polling_mode(ctx, device_data);
	पूर्ण अन्यथा अणु
		dev_err(ctx->device->dev, "[%s]: Invalid operation mode!",
			__func__);
		ret = -EPERM;
		जाओ out;
	पूर्ण

	cryp_save_device_context(device_data, &ctx->dev_ctx, cryp_mode);
	ctx->updated = 1;

out:
	ctx->indata = indata;
	ctx->outdata = outdata;
	ctx->datalen = datalen;
	ctx->outlen = outlen;

	वापस ret;
पूर्ण

अटल पूर्णांक get_nents(काष्ठा scatterlist *sg, पूर्णांक nbytes)
अणु
	पूर्णांक nents = 0;

	जबतक (nbytes > 0) अणु
		nbytes -= sg->length;
		sg = sg_next(sg);
		nents++;
	पूर्ण

	वापस nents;
पूर्ण

अटल पूर्णांक ablk_dma_crypt(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *cipher = crypto_skcipher_reqtfm(areq);
	काष्ठा cryp_ctx *ctx = crypto_skcipher_ctx(cipher);
	काष्ठा cryp_device_data *device_data;

	पूर्णांक bytes_written = 0;
	पूर्णांक bytes_पढ़ो = 0;
	पूर्णांक ret;

	pr_debug(DEV_DBG_NAME " [%s]", __func__);

	ctx->datalen = areq->cryptlen;
	ctx->outlen = areq->cryptlen;

	ret = cryp_get_device_data(ctx, &device_data);
	अगर (ret)
		वापस ret;

	ret = cryp_setup_context(ctx, device_data);
	अगर (ret)
		जाओ out;

	/* We have the device now, so store the nents in the dma काष्ठा. */
	ctx->device->dma.nents_src = get_nents(areq->src, ctx->datalen);
	ctx->device->dma.nents_dst = get_nents(areq->dst, ctx->outlen);

	/* Enable DMA in- and output. */
	cryp_configure_क्रम_dma(device_data, CRYP_DMA_ENABLE_BOTH_सूचीECTIONS);

	bytes_written = cryp_dma_ग_लिखो(ctx, areq->src, ctx->datalen);
	bytes_पढ़ो = cryp_dma_पढ़ो(ctx, areq->dst, bytes_written);

	रुको_क्रम_completion(&ctx->device->dma.cryp_dma_complete);
	cryp_dma_करोne(ctx);

	cryp_save_device_context(device_data, &ctx->dev_ctx, cryp_mode);
	ctx->updated = 1;

out:
	spin_lock(&device_data->ctx_lock);
	device_data->current_ctx = शून्य;
	ctx->device = शून्य;
	spin_unlock(&device_data->ctx_lock);

	/*
	 * The करोwn_पूर्णांकerruptible part क्रम this semaphore is called in
	 * cryp_get_device_data.
	 */
	up(&driver_data.device_allocation);

	अगर (unlikely(bytes_written != bytes_पढ़ो))
		वापस -EPERM;

	वापस 0;
पूर्ण

अटल पूर्णांक ablk_crypt(काष्ठा skcipher_request *areq)
अणु
	काष्ठा skcipher_walk walk;
	काष्ठा crypto_skcipher *cipher = crypto_skcipher_reqtfm(areq);
	काष्ठा cryp_ctx *ctx = crypto_skcipher_ctx(cipher);
	काष्ठा cryp_device_data *device_data;
	अचिन्हित दीर्घ src_paddr;
	अचिन्हित दीर्घ dst_paddr;
	पूर्णांक ret;
	पूर्णांक nbytes;

	pr_debug(DEV_DBG_NAME " [%s]", __func__);

	ret = cryp_get_device_data(ctx, &device_data);
	अगर (ret)
		जाओ out;

	ret = skcipher_walk_async(&walk, areq);

	अगर (ret) अणु
		pr_err(DEV_DBG_NAME "[%s]: skcipher_walk_async() failed!",
			__func__);
		जाओ out;
	पूर्ण

	जबतक ((nbytes = walk.nbytes) > 0) अणु
		ctx->iv = walk.iv;
		src_paddr = (page_to_phys(walk.src.phys.page) + walk.src.phys.offset);
		ctx->indata = phys_to_virt(src_paddr);

		dst_paddr = (page_to_phys(walk.dst.phys.page) + walk.dst.phys.offset);
		ctx->outdata = phys_to_virt(dst_paddr);

		ctx->datalen = nbytes - (nbytes % ctx->blocksize);

		ret = hw_crypt_noxts(ctx, device_data);
		अगर (ret)
			जाओ out;

		nbytes -= ctx->datalen;
		ret = skcipher_walk_करोne(&walk, nbytes);
		अगर (ret)
			जाओ out;
	पूर्ण

out:
	/* Release the device */
	spin_lock(&device_data->ctx_lock);
	device_data->current_ctx = शून्य;
	ctx->device = शून्य;
	spin_unlock(&device_data->ctx_lock);

	/*
	 * The करोwn_पूर्णांकerruptible part क्रम this semaphore is called in
	 * cryp_get_device_data.
	 */
	up(&driver_data.device_allocation);

	वापस ret;
पूर्ण

अटल पूर्णांक aes_skcipher_setkey(काष्ठा crypto_skcipher *cipher,
				 स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा cryp_ctx *ctx = crypto_skcipher_ctx(cipher);

	pr_debug(DEV_DBG_NAME " [%s]", __func__);

	चयन (keylen) अणु
	हाल AES_KEYSIZE_128:
		ctx->config.keysize = CRYP_KEY_SIZE_128;
		अवरोध;

	हाल AES_KEYSIZE_192:
		ctx->config.keysize = CRYP_KEY_SIZE_192;
		अवरोध;

	हाल AES_KEYSIZE_256:
		ctx->config.keysize = CRYP_KEY_SIZE_256;
		अवरोध;

	शेष:
		pr_err(DEV_DBG_NAME "[%s]: Unknown keylen!", __func__);
		वापस -EINVAL;
	पूर्ण

	स_नकल(ctx->key, key, keylen);
	ctx->keylen = keylen;

	ctx->updated = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक des_skcipher_setkey(काष्ठा crypto_skcipher *cipher,
				 स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा cryp_ctx *ctx = crypto_skcipher_ctx(cipher);
	पूर्णांक err;

	pr_debug(DEV_DBG_NAME " [%s]", __func__);

	err = verअगरy_skcipher_des_key(cipher, key);
	अगर (err)
		वापस err;

	स_नकल(ctx->key, key, keylen);
	ctx->keylen = keylen;

	ctx->updated = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक des3_skcipher_setkey(काष्ठा crypto_skcipher *cipher,
				  स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा cryp_ctx *ctx = crypto_skcipher_ctx(cipher);
	पूर्णांक err;

	pr_debug(DEV_DBG_NAME " [%s]", __func__);

	err = verअगरy_skcipher_des3_key(cipher, key);
	अगर (err)
		वापस err;

	स_नकल(ctx->key, key, keylen);
	ctx->keylen = keylen;

	ctx->updated = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक cryp_blk_encrypt(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *cipher = crypto_skcipher_reqtfm(areq);
	काष्ठा cryp_ctx *ctx = crypto_skcipher_ctx(cipher);

	pr_debug(DEV_DBG_NAME " [%s]", __func__);

	ctx->config.algodir = CRYP_ALGORITHM_ENCRYPT;

	/*
	 * DMA करोes not work क्रम DES due to a hw bug */
	अगर (cryp_mode == CRYP_MODE_DMA && mode_is_aes(ctx->config.algomode))
		वापस ablk_dma_crypt(areq);

	/* For everything except DMA, we run the non DMA version. */
	वापस ablk_crypt(areq);
पूर्ण

अटल पूर्णांक cryp_blk_decrypt(काष्ठा skcipher_request *areq)
अणु
	काष्ठा crypto_skcipher *cipher = crypto_skcipher_reqtfm(areq);
	काष्ठा cryp_ctx *ctx = crypto_skcipher_ctx(cipher);

	pr_debug(DEV_DBG_NAME " [%s]", __func__);

	ctx->config.algodir = CRYP_ALGORITHM_DECRYPT;

	/* DMA करोes not work क्रम DES due to a hw bug */
	अगर (cryp_mode == CRYP_MODE_DMA && mode_is_aes(ctx->config.algomode))
		वापस ablk_dma_crypt(areq);

	/* For everything except DMA, we run the non DMA version. */
	वापस ablk_crypt(areq);
पूर्ण

काष्ठा cryp_algo_ढाँचा अणु
	क्रमागत cryp_algo_mode algomode;
	काष्ठा skcipher_alg skcipher;
पूर्ण;

अटल पूर्णांक cryp_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा cryp_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(tfm);
	काष्ठा cryp_algo_ढाँचा *cryp_alg = container_of(alg,
			काष्ठा cryp_algo_ढाँचा,
			skcipher);

	ctx->config.algomode = cryp_alg->algomode;
	ctx->blocksize = crypto_skcipher_blocksize(tfm);

	वापस 0;
पूर्ण

अटल काष्ठा cryp_algo_ढाँचा cryp_algs[] = अणु
	अणु
		.algomode = CRYP_ALGO_AES_ECB,
		.skcipher = अणु
			.base.cra_name		= "ecb(aes)",
			.base.cra_driver_name	= "ecb-aes-ux500",
			.base.cra_priority	= 300,
			.base.cra_flags		= CRYPTO_ALG_ASYNC,
			.base.cra_blocksize	= AES_BLOCK_SIZE,
			.base.cra_ctxsize	= माप(काष्ठा cryp_ctx),
			.base.cra_alignmask	= 3,
			.base.cra_module	= THIS_MODULE,

			.min_keysize		= AES_MIN_KEY_SIZE,
			.max_keysize		= AES_MAX_KEY_SIZE,
			.setkey			= aes_skcipher_setkey,
			.encrypt		= cryp_blk_encrypt,
			.decrypt		= cryp_blk_decrypt,
			.init			= cryp_init_tfm,
		पूर्ण
	पूर्ण,
	अणु
		.algomode = CRYP_ALGO_AES_CBC,
		.skcipher = अणु
			.base.cra_name		= "cbc(aes)",
			.base.cra_driver_name	= "cbc-aes-ux500",
			.base.cra_priority	= 300,
			.base.cra_flags		= CRYPTO_ALG_ASYNC,
			.base.cra_blocksize	= AES_BLOCK_SIZE,
			.base.cra_ctxsize	= माप(काष्ठा cryp_ctx),
			.base.cra_alignmask	= 3,
			.base.cra_module	= THIS_MODULE,

			.min_keysize		= AES_MIN_KEY_SIZE,
			.max_keysize		= AES_MAX_KEY_SIZE,
			.setkey			= aes_skcipher_setkey,
			.encrypt		= cryp_blk_encrypt,
			.decrypt		= cryp_blk_decrypt,
			.init			= cryp_init_tfm,
			.ivsize			= AES_BLOCK_SIZE,
		पूर्ण
	पूर्ण,
	अणु
		.algomode = CRYP_ALGO_AES_CTR,
		.skcipher = अणु
			.base.cra_name		= "ctr(aes)",
			.base.cra_driver_name	= "ctr-aes-ux500",
			.base.cra_priority	= 300,
			.base.cra_flags		= CRYPTO_ALG_ASYNC,
			.base.cra_blocksize	= 1,
			.base.cra_ctxsize	= माप(काष्ठा cryp_ctx),
			.base.cra_alignmask	= 3,
			.base.cra_module	= THIS_MODULE,

			.min_keysize		= AES_MIN_KEY_SIZE,
			.max_keysize		= AES_MAX_KEY_SIZE,
			.setkey			= aes_skcipher_setkey,
			.encrypt		= cryp_blk_encrypt,
			.decrypt		= cryp_blk_decrypt,
			.init			= cryp_init_tfm,
			.ivsize			= AES_BLOCK_SIZE,
			.chunksize		= AES_BLOCK_SIZE,
		पूर्ण
	पूर्ण,
	अणु
		.algomode = CRYP_ALGO_DES_ECB,
		.skcipher = अणु
			.base.cra_name		= "ecb(des)",
			.base.cra_driver_name	= "ecb-des-ux500",
			.base.cra_priority	= 300,
			.base.cra_flags		= CRYPTO_ALG_ASYNC,
			.base.cra_blocksize	= DES_BLOCK_SIZE,
			.base.cra_ctxsize	= माप(काष्ठा cryp_ctx),
			.base.cra_alignmask	= 3,
			.base.cra_module	= THIS_MODULE,

			.min_keysize		= DES_KEY_SIZE,
			.max_keysize		= DES_KEY_SIZE,
			.setkey			= des_skcipher_setkey,
			.encrypt		= cryp_blk_encrypt,
			.decrypt		= cryp_blk_decrypt,
			.init			= cryp_init_tfm,
		पूर्ण
	पूर्ण,
	अणु
		.algomode = CRYP_ALGO_TDES_ECB,
		.skcipher = अणु
			.base.cra_name		= "ecb(des3_ede)",
			.base.cra_driver_name	= "ecb-des3_ede-ux500",
			.base.cra_priority	= 300,
			.base.cra_flags		= CRYPTO_ALG_ASYNC,
			.base.cra_blocksize	= DES3_EDE_BLOCK_SIZE,
			.base.cra_ctxsize	= माप(काष्ठा cryp_ctx),
			.base.cra_alignmask	= 3,
			.base.cra_module	= THIS_MODULE,

			.min_keysize		= DES3_EDE_KEY_SIZE,
			.max_keysize		= DES3_EDE_KEY_SIZE,
			.setkey			= des3_skcipher_setkey,
			.encrypt		= cryp_blk_encrypt,
			.decrypt		= cryp_blk_decrypt,
			.init			= cryp_init_tfm,
		पूर्ण
	पूर्ण,
	अणु
		.algomode = CRYP_ALGO_DES_CBC,
		.skcipher = अणु
			.base.cra_name		= "cbc(des)",
			.base.cra_driver_name	= "cbc-des-ux500",
			.base.cra_priority	= 300,
			.base.cra_flags		= CRYPTO_ALG_ASYNC,
			.base.cra_blocksize	= DES_BLOCK_SIZE,
			.base.cra_ctxsize	= माप(काष्ठा cryp_ctx),
			.base.cra_alignmask	= 3,
			.base.cra_module	= THIS_MODULE,

			.min_keysize		= DES_KEY_SIZE,
			.max_keysize		= DES_KEY_SIZE,
			.setkey			= des_skcipher_setkey,
			.encrypt		= cryp_blk_encrypt,
			.decrypt		= cryp_blk_decrypt,
			.ivsize			= DES_BLOCK_SIZE,
			.init			= cryp_init_tfm,
		पूर्ण
	पूर्ण,
	अणु
		.algomode = CRYP_ALGO_TDES_CBC,
		.skcipher = अणु
			.base.cra_name		= "cbc(des3_ede)",
			.base.cra_driver_name	= "cbc-des3_ede-ux500",
			.base.cra_priority	= 300,
			.base.cra_flags		= CRYPTO_ALG_ASYNC,
			.base.cra_blocksize	= DES3_EDE_BLOCK_SIZE,
			.base.cra_ctxsize	= माप(काष्ठा cryp_ctx),
			.base.cra_alignmask	= 3,
			.base.cra_module	= THIS_MODULE,

			.min_keysize		= DES3_EDE_KEY_SIZE,
			.max_keysize		= DES3_EDE_KEY_SIZE,
			.setkey			= des3_skcipher_setkey,
			.encrypt		= cryp_blk_encrypt,
			.decrypt		= cryp_blk_decrypt,
			.ivsize			= DES3_EDE_BLOCK_SIZE,
			.init			= cryp_init_tfm,
		पूर्ण
	पूर्ण
पूर्ण;

/**
 * cryp_algs_रेजिस्टर_all -
 */
अटल पूर्णांक cryp_algs_रेजिस्टर_all(व्योम)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	पूर्णांक count;

	pr_debug("[%s]", __func__);

	क्रम (i = 0; i < ARRAY_SIZE(cryp_algs); i++) अणु
		ret = crypto_रेजिस्टर_skcipher(&cryp_algs[i].skcipher);
		अगर (ret) अणु
			count = i;
			pr_err("[%s] alg registration failed",
					cryp_algs[i].skcipher.base.cra_driver_name);
			जाओ unreg;
		पूर्ण
	पूर्ण
	वापस 0;
unreg:
	क्रम (i = 0; i < count; i++)
		crypto_unरेजिस्टर_skcipher(&cryp_algs[i].skcipher);
	वापस ret;
पूर्ण

/**
 * cryp_algs_unरेजिस्टर_all -
 */
अटल व्योम cryp_algs_unरेजिस्टर_all(व्योम)
अणु
	पूर्णांक i;

	pr_debug(DEV_DBG_NAME " [%s]", __func__);

	क्रम (i = 0; i < ARRAY_SIZE(cryp_algs); i++)
		crypto_unरेजिस्टर_skcipher(&cryp_algs[i].skcipher);
पूर्ण

अटल पूर्णांक ux500_cryp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा resource *res;
	काष्ठा resource *res_irq;
	काष्ठा cryp_device_data *device_data;
	काष्ठा cryp_protection_config prot = अणु
		.privilege_access = CRYP_STATE_ENABLE
	पूर्ण;
	काष्ठा device *dev = &pdev->dev;

	dev_dbg(dev, "[%s]", __func__);
	device_data = devm_kzalloc(dev, माप(*device_data), GFP_ATOMIC);
	अगर (!device_data) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	device_data->dev = dev;
	device_data->current_ctx = शून्य;

	/* Grab the DMA configuration from platक्रमm data. */
	mem_to_engine = &((काष्ठा cryp_platक्रमm_data *)
			 dev->platक्रमm_data)->mem_to_engine;
	engine_to_mem = &((काष्ठा cryp_platक्रमm_data *)
			 dev->platक्रमm_data)->engine_to_mem;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(dev, "[%s]: platform_get_resource() failed",
				__func__);
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	device_data->phybase = res->start;
	device_data->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(device_data->base)) अणु
		ret = PTR_ERR(device_data->base);
		जाओ out;
	पूर्ण

	spin_lock_init(&device_data->ctx_lock);
	spin_lock_init(&device_data->घातer_state_spinlock);

	/* Enable घातer क्रम CRYP hardware block */
	device_data->pwr_regulator = regulator_get(&pdev->dev, "v-ape");
	अगर (IS_ERR(device_data->pwr_regulator)) अणु
		dev_err(dev, "[%s]: could not get cryp regulator", __func__);
		ret = PTR_ERR(device_data->pwr_regulator);
		device_data->pwr_regulator = शून्य;
		जाओ out;
	पूर्ण

	/* Enable the clk क्रम CRYP hardware block */
	device_data->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(device_data->clk)) अणु
		dev_err(dev, "[%s]: clk_get() failed!", __func__);
		ret = PTR_ERR(device_data->clk);
		जाओ out_regulator;
	पूर्ण

	ret = clk_prepare(device_data->clk);
	अगर (ret) अणु
		dev_err(dev, "[%s]: clk_prepare() failed!", __func__);
		जाओ out_regulator;
	पूर्ण

	/* Enable device घातer (and घड़ी) */
	ret = cryp_enable_घातer(device_data->dev, device_data, false);
	अगर (ret) अणु
		dev_err(dev, "[%s]: cryp_enable_power() failed!", __func__);
		जाओ out_clk_unprepare;
	पूर्ण

	अगर (cryp_check(device_data)) अणु
		dev_err(dev, "[%s]: cryp_check() failed!", __func__);
		ret = -EINVAL;
		जाओ out_घातer;
	पूर्ण

	अगर (cryp_configure_protection(device_data, &prot)) अणु
		dev_err(dev, "[%s]: cryp_configure_protection() failed!",
			__func__);
		ret = -EINVAL;
		जाओ out_घातer;
	पूर्ण

	res_irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res_irq) अणु
		dev_err(dev, "[%s]: IORESOURCE_IRQ unavailable",
			__func__);
		ret = -ENODEV;
		जाओ out_घातer;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, res_irq->start,
			       cryp_पूर्णांकerrupt_handler, 0, "cryp1", device_data);
	अगर (ret) अणु
		dev_err(dev, "[%s]: Unable to request IRQ", __func__);
		जाओ out_घातer;
	पूर्ण

	अगर (cryp_mode == CRYP_MODE_DMA)
		cryp_dma_setup_channel(device_data, dev);

	platक्रमm_set_drvdata(pdev, device_data);

	/* Put the new device पूर्णांकo the device list... */
	klist_add_tail(&device_data->list_node, &driver_data.device_list);

	/* ... and संकेत that a new device is available. */
	up(&driver_data.device_allocation);

	atomic_set(&session_id, 1);

	ret = cryp_algs_रेजिस्टर_all();
	अगर (ret) अणु
		dev_err(dev, "[%s]: cryp_algs_register_all() failed!",
			__func__);
		जाओ out_घातer;
	पूर्ण

	dev_info(dev, "successfully registered\n");

	वापस 0;

out_घातer:
	cryp_disable_घातer(device_data->dev, device_data, false);

out_clk_unprepare:
	clk_unprepare(device_data->clk);

out_regulator:
	regulator_put(device_data->pwr_regulator);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ux500_cryp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cryp_device_data *device_data;

	dev_dbg(&pdev->dev, "[%s]", __func__);
	device_data = platक्रमm_get_drvdata(pdev);
	अगर (!device_data) अणु
		dev_err(&pdev->dev, "[%s]: platform_get_drvdata() failed!",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	/* Try to decrease the number of available devices. */
	अगर (करोwn_trylock(&driver_data.device_allocation))
		वापस -EBUSY;

	/* Check that the device is मुक्त */
	spin_lock(&device_data->ctx_lock);
	/* current_ctx allocates a device, शून्य = unallocated */
	अगर (device_data->current_ctx) अणु
		/* The device is busy */
		spin_unlock(&device_data->ctx_lock);
		/* Return the device to the pool. */
		up(&driver_data.device_allocation);
		वापस -EBUSY;
	पूर्ण

	spin_unlock(&device_data->ctx_lock);

	/* Remove the device from the list */
	अगर (klist_node_attached(&device_data->list_node))
		klist_हटाओ(&device_data->list_node);

	/* If this was the last device, हटाओ the services */
	अगर (list_empty(&driver_data.device_list.k_list))
		cryp_algs_unरेजिस्टर_all();

	अगर (cryp_disable_घातer(&pdev->dev, device_data, false))
		dev_err(&pdev->dev, "[%s]: cryp_disable_power() failed",
			__func__);

	clk_unprepare(device_data->clk);
	regulator_put(device_data->pwr_regulator);

	वापस 0;
पूर्ण

अटल व्योम ux500_cryp_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cryp_device_data *device_data;

	dev_dbg(&pdev->dev, "[%s]", __func__);

	device_data = platक्रमm_get_drvdata(pdev);
	अगर (!device_data) अणु
		dev_err(&pdev->dev, "[%s]: platform_get_drvdata() failed!",
			__func__);
		वापस;
	पूर्ण

	/* Check that the device is मुक्त */
	spin_lock(&device_data->ctx_lock);
	/* current_ctx allocates a device, शून्य = unallocated */
	अगर (!device_data->current_ctx) अणु
		अगर (करोwn_trylock(&driver_data.device_allocation))
			dev_dbg(&pdev->dev, "[%s]: Cryp still in use!"
				"Shutting down anyway...", __func__);
		/**
		 * (Allocate the device)
		 * Need to set this to non-null (dummy) value,
		 * to aव्योम usage अगर context चयनing.
		 */
		device_data->current_ctx++;
	पूर्ण
	spin_unlock(&device_data->ctx_lock);

	/* Remove the device from the list */
	अगर (klist_node_attached(&device_data->list_node))
		klist_हटाओ(&device_data->list_node);

	/* If this was the last device, हटाओ the services */
	अगर (list_empty(&driver_data.device_list.k_list))
		cryp_algs_unरेजिस्टर_all();

	अगर (cryp_disable_घातer(&pdev->dev, device_data, false))
		dev_err(&pdev->dev, "[%s]: cryp_disable_power() failed",
			__func__);

पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ux500_cryp_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा cryp_device_data *device_data;
	काष्ठा resource *res_irq;
	काष्ठा cryp_ctx *temp_ctx = शून्य;

	dev_dbg(dev, "[%s]", __func__);

	/* Handle state? */
	device_data = platक्रमm_get_drvdata(pdev);
	अगर (!device_data) अणु
		dev_err(dev, "[%s]: platform_get_drvdata() failed!", __func__);
		वापस -ENOMEM;
	पूर्ण

	res_irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res_irq)
		dev_err(dev, "[%s]: IORESOURCE_IRQ, unavailable", __func__);
	अन्यथा
		disable_irq(res_irq->start);

	spin_lock(&device_data->ctx_lock);
	अगर (!device_data->current_ctx)
		device_data->current_ctx++;
	spin_unlock(&device_data->ctx_lock);

	अगर (device_data->current_ctx == ++temp_ctx) अणु
		अगर (करोwn_पूर्णांकerruptible(&driver_data.device_allocation))
			dev_dbg(dev, "[%s]: down_interruptible() failed",
				__func__);
		ret = cryp_disable_घातer(dev, device_data, false);

	पूर्ण अन्यथा
		ret = cryp_disable_घातer(dev, device_data, true);

	अगर (ret)
		dev_err(dev, "[%s]: cryp_disable_power()", __func__);

	वापस ret;
पूर्ण

अटल पूर्णांक ux500_cryp_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret = 0;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा cryp_device_data *device_data;
	काष्ठा resource *res_irq;
	काष्ठा cryp_ctx *temp_ctx = शून्य;

	dev_dbg(dev, "[%s]", __func__);

	device_data = platक्रमm_get_drvdata(pdev);
	अगर (!device_data) अणु
		dev_err(dev, "[%s]: platform_get_drvdata() failed!", __func__);
		वापस -ENOMEM;
	पूर्ण

	spin_lock(&device_data->ctx_lock);
	अगर (device_data->current_ctx == ++temp_ctx)
		device_data->current_ctx = शून्य;
	spin_unlock(&device_data->ctx_lock);


	अगर (!device_data->current_ctx)
		up(&driver_data.device_allocation);
	अन्यथा
		ret = cryp_enable_घातer(dev, device_data, true);

	अगर (ret)
		dev_err(dev, "[%s]: cryp_enable_power() failed!", __func__);
	अन्यथा अणु
		res_irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
		अगर (res_irq)
			enable_irq(res_irq->start);
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(ux500_cryp_pm, ux500_cryp_suspend, ux500_cryp_resume);

अटल स्थिर काष्ठा of_device_id ux500_cryp_match[] = अणु
	अणु .compatible = "stericsson,ux500-cryp" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ux500_cryp_match);

अटल काष्ठा platक्रमm_driver cryp_driver = अणु
	.probe  = ux500_cryp_probe,
	.हटाओ = ux500_cryp_हटाओ,
	.shutकरोwn = ux500_cryp_shutकरोwn,
	.driver = अणु
		.name  = "cryp1",
		.of_match_table = ux500_cryp_match,
		.pm    = &ux500_cryp_pm,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init ux500_cryp_mod_init(व्योम)
अणु
	pr_debug("[%s] is called!", __func__);
	klist_init(&driver_data.device_list, शून्य, शून्य);
	/* Initialize the semaphore to 0 devices (locked state) */
	sema_init(&driver_data.device_allocation, 0);
	वापस platक्रमm_driver_रेजिस्टर(&cryp_driver);
पूर्ण

अटल व्योम __निकास ux500_cryp_mod_fini(व्योम)
अणु
	pr_debug("[%s] is called!", __func__);
	platक्रमm_driver_unरेजिस्टर(&cryp_driver);
पूर्ण

module_init(ux500_cryp_mod_init);
module_निकास(ux500_cryp_mod_fini);

module_param(cryp_mode, पूर्णांक, 0);

MODULE_DESCRIPTION("Driver for ST-Ericsson UX500 CRYP crypto engine.");
MODULE_ALIAS_CRYPTO("aes-all");
MODULE_ALIAS_CRYPTO("des-all");

MODULE_LICENSE("GPL");
