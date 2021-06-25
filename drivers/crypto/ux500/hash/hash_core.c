<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Cryptographic API.
 * Support क्रम Nomadik hardware crypto engine.

 * Copyright (C) ST-Ericsson SA 2010
 * Author: Shujuan Chen <shujuan.chen@stericsson.com> क्रम ST-Ericsson
 * Author: Joakim Bech <joakim.xx.bech@stericsson.com> क्रम ST-Ericsson
 * Author: Berne Hebark <berne.herbark@stericsson.com> क्रम ST-Ericsson.
 * Author: Niklas Hernaeus <niklas.hernaeus@stericsson.com> क्रम ST-Ericsson.
 * Author: Andreas Westin <andreas.westin@stericsson.com> क्रम ST-Ericsson.
 */

#घोषणा pr_fmt(fmt) "hashX hashX: " fmt

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/klist.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/crypto.h>

#समावेश <linux/regulator/consumer.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/bitops.h>

#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/algapi.h>

#समावेश <linux/platक्रमm_data/crypto-ux500.h>

#समावेश "hash_alg.h"

अटल पूर्णांक hash_mode;
module_param(hash_mode, पूर्णांक, 0);
MODULE_PARM_DESC(hash_mode, "CPU or DMA mode. CPU = 0 (default), DMA = 1");

/* HMAC-SHA1, no key */
अटल स्थिर u8 zero_message_hmac_sha1[SHA1_DIGEST_SIZE] = अणु
	0xfb, 0xdb, 0x1d, 0x1b, 0x18, 0xaa, 0x6c, 0x08,
	0x32, 0x4b, 0x7d, 0x64, 0xb7, 0x1f, 0xb7, 0x63,
	0x70, 0x69, 0x0e, 0x1d
पूर्ण;

/* HMAC-SHA256, no key */
अटल स्थिर u8 zero_message_hmac_sha256[SHA256_DIGEST_SIZE] = अणु
	0xb6, 0x13, 0x67, 0x9a, 0x08, 0x14, 0xd9, 0xec,
	0x77, 0x2f, 0x95, 0xd7, 0x78, 0xc3, 0x5f, 0xc5,
	0xff, 0x16, 0x97, 0xc4, 0x93, 0x71, 0x56, 0x53,
	0xc6, 0xc7, 0x12, 0x14, 0x42, 0x92, 0xc5, 0xad
पूर्ण;

/**
 * काष्ठा hash_driver_data - data specअगरic to the driver.
 *
 * @device_list:	A list of रेजिस्टरed devices to choose from.
 * @device_allocation:	A semaphore initialized with number of devices.
 */
काष्ठा hash_driver_data अणु
	काष्ठा klist		device_list;
	काष्ठा semaphore	device_allocation;
पूर्ण;

अटल काष्ठा hash_driver_data	driver_data;

/* Declaration of functions */
/**
 * hash_messagepad - Pads a message and ग_लिखो the nblw bits.
 * @device_data:	Structure क्रम the hash device.
 * @message:		Last word of a message
 * @index_bytes:	The number of bytes in the last message
 *
 * This function manages the final part of the digest calculation, when less
 * than 512 bits (64 bytes) reमुख्य in message. This means index_bytes < 64.
 *
 */
अटल व्योम hash_messagepad(काष्ठा hash_device_data *device_data,
			    स्थिर u32 *message, u8 index_bytes);

/**
 * release_hash_device - Releases a previously allocated hash device.
 * @device_data:	Structure क्रम the hash device.
 *
 */
अटल व्योम release_hash_device(काष्ठा hash_device_data *device_data)
अणु
	spin_lock(&device_data->ctx_lock);
	device_data->current_ctx->device = शून्य;
	device_data->current_ctx = शून्य;
	spin_unlock(&device_data->ctx_lock);

	/*
	 * The करोwn_पूर्णांकerruptible part क्रम this semaphore is called in
	 * cryp_get_device_data.
	 */
	up(&driver_data.device_allocation);
पूर्ण

अटल व्योम hash_dma_setup_channel(काष्ठा hash_device_data *device_data,
				   काष्ठा device *dev)
अणु
	काष्ठा hash_platक्रमm_data *platक्रमm_data = dev->platक्रमm_data;
	काष्ठा dma_slave_config conf = अणु
		.direction = DMA_MEM_TO_DEV,
		.dst_addr = device_data->phybase + HASH_DMA_FIFO,
		.dst_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES,
		.dst_maxburst = 16,
	पूर्ण;

	dma_cap_zero(device_data->dma.mask);
	dma_cap_set(DMA_SLAVE, device_data->dma.mask);

	device_data->dma.cfg_mem2hash = platक्रमm_data->mem_to_engine;
	device_data->dma.chan_mem2hash =
		dma_request_channel(device_data->dma.mask,
				    platक्रमm_data->dma_filter,
				    device_data->dma.cfg_mem2hash);

	dmaengine_slave_config(device_data->dma.chan_mem2hash, &conf);

	init_completion(&device_data->dma.complete);
पूर्ण

अटल व्योम hash_dma_callback(व्योम *data)
अणु
	काष्ठा hash_ctx *ctx = data;

	complete(&ctx->device->dma.complete);
पूर्ण

अटल पूर्णांक hash_set_dma_transfer(काष्ठा hash_ctx *ctx, काष्ठा scatterlist *sg,
				 पूर्णांक len, क्रमागत dma_data_direction direction)
अणु
	काष्ठा dma_async_tx_descriptor *desc = शून्य;
	काष्ठा dma_chan *channel = शून्य;

	अगर (direction != DMA_TO_DEVICE) अणु
		dev_err(ctx->device->dev, "%s: Invalid DMA direction\n",
			__func__);
		वापस -EFAULT;
	पूर्ण

	sg->length = ALIGN(sg->length, HASH_DMA_ALIGN_SIZE);

	channel = ctx->device->dma.chan_mem2hash;
	ctx->device->dma.sg = sg;
	ctx->device->dma.sg_len = dma_map_sg(channel->device->dev,
			ctx->device->dma.sg, ctx->device->dma.nents,
			direction);

	अगर (!ctx->device->dma.sg_len) अणु
		dev_err(ctx->device->dev, "%s: Could not map the sg list (TO_DEVICE)\n",
			__func__);
		वापस -EFAULT;
	पूर्ण

	dev_dbg(ctx->device->dev, "%s: Setting up DMA for buffer (TO_DEVICE)\n",
		__func__);
	desc = dmaengine_prep_slave_sg(channel,
			ctx->device->dma.sg, ctx->device->dma.sg_len,
			DMA_MEM_TO_DEV, DMA_CTRL_ACK | DMA_PREP_INTERRUPT);
	अगर (!desc) अणु
		dev_err(ctx->device->dev,
			"%s: dmaengine_prep_slave_sg() failed!\n", __func__);
		वापस -EFAULT;
	पूर्ण

	desc->callback = hash_dma_callback;
	desc->callback_param = ctx;

	dmaengine_submit(desc);
	dma_async_issue_pending(channel);

	वापस 0;
पूर्ण

अटल व्योम hash_dma_करोne(काष्ठा hash_ctx *ctx)
अणु
	काष्ठा dma_chan *chan;

	chan = ctx->device->dma.chan_mem2hash;
	dmaengine_terminate_all(chan);
	dma_unmap_sg(chan->device->dev, ctx->device->dma.sg,
		     ctx->device->dma.nents, DMA_TO_DEVICE);
पूर्ण

अटल पूर्णांक hash_dma_ग_लिखो(काष्ठा hash_ctx *ctx,
			  काष्ठा scatterlist *sg, पूर्णांक len)
अणु
	पूर्णांक error = hash_set_dma_transfer(ctx, sg, len, DMA_TO_DEVICE);
	अगर (error) अणु
		dev_dbg(ctx->device->dev,
			"%s: hash_set_dma_transfer() failed\n", __func__);
		वापस error;
	पूर्ण

	वापस len;
पूर्ण

/**
 * get_empty_message_digest - Returns a pre-calculated digest क्रम
 * the empty message.
 * @device_data:	Structure क्रम the hash device.
 * @zero_hash:		Buffer to वापस the empty message digest.
 * @zero_hash_size:	Hash size of the empty message digest.
 * @zero_digest:	True अगर zero_digest वापसed.
 */
अटल पूर्णांक get_empty_message_digest(
		काष्ठा hash_device_data *device_data,
		u8 *zero_hash, u32 *zero_hash_size, bool *zero_digest)
अणु
	पूर्णांक ret = 0;
	काष्ठा hash_ctx *ctx = device_data->current_ctx;
	*zero_digest = false;

	/**
	 * Caller responsible क्रम ctx != शून्य.
	 */

	अगर (HASH_OPER_MODE_HASH == ctx->config.oper_mode) अणु
		अगर (HASH_ALGO_SHA1 == ctx->config.algorithm) अणु
			स_नकल(zero_hash, &sha1_zero_message_hash[0],
			       SHA1_DIGEST_SIZE);
			*zero_hash_size = SHA1_DIGEST_SIZE;
			*zero_digest = true;
		पूर्ण अन्यथा अगर (HASH_ALGO_SHA256 ==
				ctx->config.algorithm) अणु
			स_नकल(zero_hash, &sha256_zero_message_hash[0],
			       SHA256_DIGEST_SIZE);
			*zero_hash_size = SHA256_DIGEST_SIZE;
			*zero_digest = true;
		पूर्ण अन्यथा अणु
			dev_err(device_data->dev, "%s: Incorrect algorithm!\n",
				__func__);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (HASH_OPER_MODE_HMAC == ctx->config.oper_mode) अणु
		अगर (!ctx->keylen) अणु
			अगर (HASH_ALGO_SHA1 == ctx->config.algorithm) अणु
				स_नकल(zero_hash, &zero_message_hmac_sha1[0],
				       SHA1_DIGEST_SIZE);
				*zero_hash_size = SHA1_DIGEST_SIZE;
				*zero_digest = true;
			पूर्ण अन्यथा अगर (HASH_ALGO_SHA256 == ctx->config.algorithm) अणु
				स_नकल(zero_hash, &zero_message_hmac_sha256[0],
				       SHA256_DIGEST_SIZE);
				*zero_hash_size = SHA256_DIGEST_SIZE;
				*zero_digest = true;
			पूर्ण अन्यथा अणु
				dev_err(device_data->dev, "%s: Incorrect algorithm!\n",
					__func__);
				ret = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_dbg(device_data->dev,
				"%s: Continue hash calculation, since hmac key available\n",
				__func__);
		पूर्ण
	पूर्ण
out:

	वापस ret;
पूर्ण

/**
 * hash_disable_घातer - Request to disable घातer and घड़ी.
 * @device_data:	Structure क्रम the hash device.
 * @save_device_state:	If true, saves the current hw state.
 *
 * This function request क्रम disabling घातer (regulator) and घड़ी,
 * and could also save current hw state.
 */
अटल पूर्णांक hash_disable_घातer(काष्ठा hash_device_data *device_data,
			      bool save_device_state)
अणु
	पूर्णांक ret = 0;
	काष्ठा device *dev = device_data->dev;

	spin_lock(&device_data->घातer_state_lock);
	अगर (!device_data->घातer_state)
		जाओ out;

	अगर (save_device_state) अणु
		hash_save_state(device_data,
				&device_data->state);
		device_data->restore_dev_state = true;
	पूर्ण

	clk_disable(device_data->clk);
	ret = regulator_disable(device_data->regulator);
	अगर (ret)
		dev_err(dev, "%s: regulator_disable() failed!\n", __func__);

	device_data->घातer_state = false;

out:
	spin_unlock(&device_data->घातer_state_lock);

	वापस ret;
पूर्ण

/**
 * hash_enable_घातer - Request to enable घातer and घड़ी.
 * @device_data:		Structure क्रम the hash device.
 * @restore_device_state:	If true, restores a previous saved hw state.
 *
 * This function request क्रम enabling घातer (regulator) and घड़ी,
 * and could also restore a previously saved hw state.
 */
अटल पूर्णांक hash_enable_घातer(काष्ठा hash_device_data *device_data,
			     bool restore_device_state)
अणु
	पूर्णांक ret = 0;
	काष्ठा device *dev = device_data->dev;

	spin_lock(&device_data->घातer_state_lock);
	अगर (!device_data->घातer_state) अणु
		ret = regulator_enable(device_data->regulator);
		अगर (ret) अणु
			dev_err(dev, "%s: regulator_enable() failed!\n",
				__func__);
			जाओ out;
		पूर्ण
		ret = clk_enable(device_data->clk);
		अगर (ret) अणु
			dev_err(dev, "%s: clk_enable() failed!\n", __func__);
			ret = regulator_disable(
					device_data->regulator);
			जाओ out;
		पूर्ण
		device_data->घातer_state = true;
	पूर्ण

	अगर (device_data->restore_dev_state) अणु
		अगर (restore_device_state) अणु
			device_data->restore_dev_state = false;
			hash_resume_state(device_data, &device_data->state);
		पूर्ण
	पूर्ण
out:
	spin_unlock(&device_data->घातer_state_lock);

	वापस ret;
पूर्ण

/**
 * hash_get_device_data - Checks क्रम an available hash device and वापस it.
 * @ctx:		Structure क्रम the hash context.
 * @device_data:	Structure क्रम the hash device.
 *
 * This function check क्रम an available hash device and वापस it to
 * the caller.
 * Note! Caller need to release the device, calling up().
 */
अटल पूर्णांक hash_get_device_data(काष्ठा hash_ctx *ctx,
				काष्ठा hash_device_data **device_data)
अणु
	पूर्णांक			ret;
	काष्ठा klist_iter	device_iterator;
	काष्ठा klist_node	*device_node;
	काष्ठा hash_device_data *local_device_data = शून्य;

	/* Wait until a device is available */
	ret = करोwn_पूर्णांकerruptible(&driver_data.device_allocation);
	अगर (ret)
		वापस ret;  /* Interrupted */

	/* Select a device */
	klist_iter_init(&driver_data.device_list, &device_iterator);
	device_node = klist_next(&device_iterator);
	जबतक (device_node) अणु
		local_device_data = container_of(device_node,
					   काष्ठा hash_device_data, list_node);
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

/**
 * hash_hw_ग_लिखो_key - Writes the key to the hardware registries.
 *
 * @device_data:	Structure क्रम the hash device.
 * @key:		Key to be written.
 * @keylen:		The lengt of the key.
 *
 * Note! This function DOES NOT ग_लिखो to the NBLW registry, even though
 * specअगरied in the the hw design spec. Either due to incorrect info in the
 * spec or due to a bug in the hw.
 */
अटल व्योम hash_hw_ग_लिखो_key(काष्ठा hash_device_data *device_data,
			      स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	u32 word = 0;
	पूर्णांक nwords = 1;

	HASH_CLEAR_BITS(&device_data->base->str, HASH_STR_NBLW_MASK);

	जबतक (keylen >= 4) अणु
		u32 *key_word = (u32 *)key;

		HASH_SET_DIN(key_word, nwords);
		keylen -= 4;
		key += 4;
	पूर्ण

	/* Take care of the reमुख्यing bytes in the last word */
	अगर (keylen) अणु
		word = 0;
		जबतक (keylen) अणु
			word |= (key[keylen - 1] << (8 * (keylen - 1)));
			keylen--;
		पूर्ण

		HASH_SET_DIN(&word, nwords);
	पूर्ण

	जबतक (पढ़ोl(&device_data->base->str) & HASH_STR_DCAL_MASK)
		cpu_relax();

	HASH_SET_DCAL;

	जबतक (पढ़ोl(&device_data->base->str) & HASH_STR_DCAL_MASK)
		cpu_relax();
पूर्ण

/**
 * init_hash_hw - Initialise the hash hardware क्रम a new calculation.
 * @device_data:	Structure क्रम the hash device.
 * @ctx:		The hash context.
 *
 * This function will enable the bits needed to clear and start a new
 * calculation.
 */
अटल पूर्णांक init_hash_hw(काष्ठा hash_device_data *device_data,
			काष्ठा hash_ctx *ctx)
अणु
	पूर्णांक ret = 0;

	ret = hash_setconfiguration(device_data, &ctx->config);
	अगर (ret) अणु
		dev_err(device_data->dev, "%s: hash_setconfiguration() failed!\n",
			__func__);
		वापस ret;
	पूर्ण

	hash_begin(device_data, ctx);

	अगर (ctx->config.oper_mode == HASH_OPER_MODE_HMAC)
		hash_hw_ग_लिखो_key(device_data, ctx->key, ctx->keylen);

	वापस ret;
पूर्ण

/**
 * hash_get_nents - Return number of entries (nents) in scatterlist (sg).
 *
 * @sg:		Scatterlist.
 * @size:	Size in bytes.
 * @aligned:	True अगर sg data aligned to work in DMA mode.
 *
 */
अटल पूर्णांक hash_get_nents(काष्ठा scatterlist *sg, पूर्णांक size, bool *aligned)
अणु
	पूर्णांक nents = 0;
	bool aligned_data = true;

	जबतक (size > 0 && sg) अणु
		nents++;
		size -= sg->length;

		/* hash_set_dma_transfer will align last nent */
		अगर ((aligned && !IS_ALIGNED(sg->offset, HASH_DMA_ALIGN_SIZE)) ||
		    (!IS_ALIGNED(sg->length, HASH_DMA_ALIGN_SIZE) && size > 0))
			aligned_data = false;

		sg = sg_next(sg);
	पूर्ण

	अगर (aligned)
		*aligned = aligned_data;

	अगर (size != 0)
		वापस -EFAULT;

	वापस nents;
पूर्ण

/**
 * hash_dma_valid_data - checks क्रम dma valid sg data.
 * @sg:		Scatterlist.
 * @datasize:	Datasize in bytes.
 *
 * NOTE! This function checks क्रम dma valid sg data, since dma
 * only accept datasizes of even wordsize.
 */
अटल bool hash_dma_valid_data(काष्ठा scatterlist *sg, पूर्णांक datasize)
अणु
	bool aligned;

	/* Need to include at least one nent, अन्यथा error */
	अगर (hash_get_nents(sg, datasize, &aligned) < 1)
		वापस false;

	वापस aligned;
पूर्ण

/**
 * ux500_hash_init - Common hash init function क्रम SHA1/SHA2 (SHA256).
 * @req: The hash request क्रम the job.
 *
 * Initialize काष्ठाures.
 */
अटल पूर्णांक ux500_hash_init(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा hash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा hash_req_ctx *req_ctx = ahash_request_ctx(req);

	अगर (!ctx->key)
		ctx->keylen = 0;

	स_रखो(&req_ctx->state, 0, माप(काष्ठा hash_state));
	req_ctx->updated = 0;
	अगर (hash_mode == HASH_MODE_DMA) अणु
		अगर (req->nbytes < HASH_DMA_ALIGN_SIZE) अणु
			req_ctx->dma_mode = false; /* Don't use DMA */

			pr_debug("%s: DMA mode, but direct to CPU mode for data size < %d\n",
				 __func__, HASH_DMA_ALIGN_SIZE);
		पूर्ण अन्यथा अणु
			अगर (req->nbytes >= HASH_DMA_PERFORMANCE_MIN_SIZE &&
			    hash_dma_valid_data(req->src, req->nbytes)) अणु
				req_ctx->dma_mode = true;
			पूर्ण अन्यथा अणु
				req_ctx->dma_mode = false;
				pr_debug("%s: DMA mode, but use CPU mode for datalength < %d or non-aligned data, except in last nent\n",
					 __func__,
					 HASH_DMA_PERFORMANCE_MIN_SIZE);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * hash_processblock - This function processes a single block of 512 bits (64
 *                     bytes), word aligned, starting at message.
 * @device_data:	Structure क्रम the hash device.
 * @message:		Block (512 bits) of message to be written to
 *			the HASH hardware.
 * @length:		Message length
 *
 */
अटल व्योम hash_processblock(काष्ठा hash_device_data *device_data,
			      स्थिर u32 *message, पूर्णांक length)
अणु
	पूर्णांक len = length / HASH_BYTES_PER_WORD;
	/*
	 * NBLW bits. Reset the number of bits in last word (NBLW).
	 */
	HASH_CLEAR_BITS(&device_data->base->str, HASH_STR_NBLW_MASK);

	/*
	 * Write message data to the HASH_DIN रेजिस्टर.
	 */
	HASH_SET_DIN(message, len);
पूर्ण

/**
 * hash_messagepad - Pads a message and ग_लिखो the nblw bits.
 * @device_data:	Structure क्रम the hash device.
 * @message:		Last word of a message.
 * @index_bytes:	The number of bytes in the last message.
 *
 * This function manages the final part of the digest calculation, when less
 * than 512 bits (64 bytes) reमुख्य in message. This means index_bytes < 64.
 *
 */
अटल व्योम hash_messagepad(काष्ठा hash_device_data *device_data,
			    स्थिर u32 *message, u8 index_bytes)
अणु
	पूर्णांक nwords = 1;

	/*
	 * Clear hash str रेजिस्टर, only clear NBLW
	 * since DCAL will be reset by hardware.
	 */
	HASH_CLEAR_BITS(&device_data->base->str, HASH_STR_NBLW_MASK);

	/* Main loop */
	जबतक (index_bytes >= 4) अणु
		HASH_SET_DIN(message, nwords);
		index_bytes -= 4;
		message++;
	पूर्ण

	अगर (index_bytes)
		HASH_SET_DIN(message, nwords);

	जबतक (पढ़ोl(&device_data->base->str) & HASH_STR_DCAL_MASK)
		cpu_relax();

	/* num_of_bytes == 0 => NBLW <- 0 (32 bits valid in DATAIN) */
	HASH_SET_NBLW(index_bytes * 8);
	dev_dbg(device_data->dev, "%s: DIN=0x%08x NBLW=%lu\n",
		__func__, पढ़ोl_relaxed(&device_data->base->din),
		पढ़ोl_relaxed(&device_data->base->str) & HASH_STR_NBLW_MASK);
	HASH_SET_DCAL;
	dev_dbg(device_data->dev, "%s: after dcal -> DIN=0x%08x NBLW=%lu\n",
		__func__, पढ़ोl_relaxed(&device_data->base->din),
		पढ़ोl_relaxed(&device_data->base->str) & HASH_STR_NBLW_MASK);

	जबतक (पढ़ोl(&device_data->base->str) & HASH_STR_DCAL_MASK)
		cpu_relax();
पूर्ण

/**
 * hash_incrementlength - Increments the length of the current message.
 * @ctx: Hash context
 * @incr: Length of message processed alपढ़ोy
 *
 * Overflow cannot occur, because conditions क्रम overflow are checked in
 * hash_hw_update.
 */
अटल व्योम hash_incrementlength(काष्ठा hash_req_ctx *ctx, u32 incr)
अणु
	ctx->state.length.low_word += incr;

	/* Check क्रम wrap-around */
	अगर (ctx->state.length.low_word < incr)
		ctx->state.length.high_word++;
पूर्ण

/**
 * hash_setconfiguration - Sets the required configuration क्रम the hash
 *                         hardware.
 * @device_data:	Structure क्रम the hash device.
 * @config:		Poपूर्णांकer to a configuration काष्ठाure.
 */
पूर्णांक hash_setconfiguration(काष्ठा hash_device_data *device_data,
			  काष्ठा hash_config *config)
अणु
	पूर्णांक ret = 0;

	अगर (config->algorithm != HASH_ALGO_SHA1 &&
	    config->algorithm != HASH_ALGO_SHA256)
		वापस -EPERM;

	/*
	 * DATAFORM bits. Set the DATAFORM bits to 0b11, which means the data
	 * to be written to HASH_DIN is considered as 32 bits.
	 */
	HASH_SET_DATA_FORMAT(config->data_क्रमmat);

	/*
	 * ALGO bit. Set to 0b1 क्रम SHA-1 and 0b0 क्रम SHA-256
	 */
	चयन (config->algorithm) अणु
	हाल HASH_ALGO_SHA1:
		HASH_SET_BITS(&device_data->base->cr, HASH_CR_ALGO_MASK);
		अवरोध;

	हाल HASH_ALGO_SHA256:
		HASH_CLEAR_BITS(&device_data->base->cr, HASH_CR_ALGO_MASK);
		अवरोध;

	शेष:
		dev_err(device_data->dev, "%s: Incorrect algorithm\n",
			__func__);
		वापस -EPERM;
	पूर्ण

	/*
	 * MODE bit. This bit selects between HASH or HMAC mode क्रम the
	 * selected algorithm. 0b0 = HASH and 0b1 = HMAC.
	 */
	अगर (HASH_OPER_MODE_HASH == config->oper_mode)
		HASH_CLEAR_BITS(&device_data->base->cr,
				HASH_CR_MODE_MASK);
	अन्यथा अगर (HASH_OPER_MODE_HMAC == config->oper_mode) अणु
		HASH_SET_BITS(&device_data->base->cr, HASH_CR_MODE_MASK);
		अगर (device_data->current_ctx->keylen > HASH_BLOCK_SIZE) अणु
			/* Truncate key to blocksize */
			dev_dbg(device_data->dev, "%s: LKEY set\n", __func__);
			HASH_SET_BITS(&device_data->base->cr,
				      HASH_CR_LKEY_MASK);
		पूर्ण अन्यथा अणु
			dev_dbg(device_data->dev, "%s: LKEY cleared\n",
				__func__);
			HASH_CLEAR_BITS(&device_data->base->cr,
					HASH_CR_LKEY_MASK);
		पूर्ण
	पूर्ण अन्यथा अणु	/* Wrong hash mode */
		ret = -EPERM;
		dev_err(device_data->dev, "%s: HASH_INVALID_PARAMETER!\n",
			__func__);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * hash_begin - This routine resets some globals and initializes the hash
 *              hardware.
 * @device_data:	Structure क्रम the hash device.
 * @ctx:		Hash context.
 */
व्योम hash_begin(काष्ठा hash_device_data *device_data, काष्ठा hash_ctx *ctx)
अणु
	/* HW and SW initializations */
	/* Note: there is no need to initialize buffer and digest members */

	जबतक (पढ़ोl(&device_data->base->str) & HASH_STR_DCAL_MASK)
		cpu_relax();

	/*
	 * INIT bit. Set this bit to 0b1 to reset the HASH processor core and
	 * prepare the initialize the HASH accelerator to compute the message
	 * digest of a new message.
	 */
	HASH_INITIALIZE;

	/*
	 * NBLW bits. Reset the number of bits in last word (NBLW).
	 */
	HASH_CLEAR_BITS(&device_data->base->str, HASH_STR_NBLW_MASK);
पूर्ण

अटल पूर्णांक hash_process_data(काष्ठा hash_device_data *device_data,
			     काष्ठा hash_ctx *ctx, काष्ठा hash_req_ctx *req_ctx,
			     पूर्णांक msg_length, u8 *data_buffer, u8 *buffer,
			     u8 *index)
अणु
	पूर्णांक ret = 0;
	u32 count;

	करो अणु
		अगर ((*index + msg_length) < HASH_BLOCK_SIZE) अणु
			क्रम (count = 0; count < msg_length; count++) अणु
				buffer[*index + count] =
					*(data_buffer + count);
			पूर्ण
			*index += msg_length;
			msg_length = 0;
		पूर्ण अन्यथा अणु
			अगर (req_ctx->updated) अणु
				ret = hash_resume_state(device_data,
						&device_data->state);
				स_हटाओ(req_ctx->state.buffer,
					device_data->state.buffer,
					HASH_BLOCK_SIZE);
				अगर (ret) अणु
					dev_err(device_data->dev,
						"%s: hash_resume_state() failed!\n",
						__func__);
					जाओ out;
				पूर्ण
			पूर्ण अन्यथा अणु
				ret = init_hash_hw(device_data, ctx);
				अगर (ret) अणु
					dev_err(device_data->dev,
						"%s: init_hash_hw() failed!\n",
						__func__);
					जाओ out;
				पूर्ण
				req_ctx->updated = 1;
			पूर्ण
			/*
			 * If 'data_buffer' is four byte aligned and
			 * local buffer करोes not have any data, we can
			 * ग_लिखो data directly from 'data_buffer' to
			 * HW peripheral, otherwise we first copy data
			 * to a local buffer
			 */
			अगर (IS_ALIGNED((अचिन्हित दीर्घ)data_buffer, 4) &&
			    (0 == *index))
				hash_processblock(device_data,
						  (स्थिर u32 *)data_buffer,
						  HASH_BLOCK_SIZE);
			अन्यथा अणु
				क्रम (count = 0;
				     count < (u32)(HASH_BLOCK_SIZE - *index);
				     count++) अणु
					buffer[*index + count] =
						*(data_buffer + count);
				पूर्ण
				hash_processblock(device_data,
						  (स्थिर u32 *)buffer,
						  HASH_BLOCK_SIZE);
			पूर्ण
			hash_incrementlength(req_ctx, HASH_BLOCK_SIZE);
			data_buffer += (HASH_BLOCK_SIZE - *index);

			msg_length -= (HASH_BLOCK_SIZE - *index);
			*index = 0;

			ret = hash_save_state(device_data,
					&device_data->state);

			स_हटाओ(device_data->state.buffer,
				req_ctx->state.buffer,
				HASH_BLOCK_SIZE);
			अगर (ret) अणु
				dev_err(device_data->dev, "%s: hash_save_state() failed!\n",
					__func__);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (msg_length != 0);
out:

	वापस ret;
पूर्ण

/**
 * hash_dma_final - The hash dma final function क्रम SHA1/SHA256.
 * @req:	The hash request क्रम the job.
 */
अटल पूर्णांक hash_dma_final(काष्ठा ahash_request *req)
अणु
	पूर्णांक ret = 0;
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा hash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा hash_req_ctx *req_ctx = ahash_request_ctx(req);
	काष्ठा hash_device_data *device_data;
	u8 digest[SHA256_DIGEST_SIZE];
	पूर्णांक bytes_written = 0;

	ret = hash_get_device_data(ctx, &device_data);
	अगर (ret)
		वापस ret;

	dev_dbg(device_data->dev, "%s: (ctx=0x%lx)!\n", __func__,
		(अचिन्हित दीर्घ)ctx);

	अगर (req_ctx->updated) अणु
		ret = hash_resume_state(device_data, &device_data->state);

		अगर (ret) अणु
			dev_err(device_data->dev, "%s: hash_resume_state() failed!\n",
				__func__);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!req_ctx->updated) अणु
		ret = hash_setconfiguration(device_data, &ctx->config);
		अगर (ret) अणु
			dev_err(device_data->dev,
				"%s: hash_setconfiguration() failed!\n",
				__func__);
			जाओ out;
		पूर्ण

		/* Enable DMA input */
		अगर (hash_mode != HASH_MODE_DMA || !req_ctx->dma_mode) अणु
			HASH_CLEAR_BITS(&device_data->base->cr,
					HASH_CR_DMAE_MASK);
		पूर्ण अन्यथा अणु
			HASH_SET_BITS(&device_data->base->cr,
				      HASH_CR_DMAE_MASK);
			HASH_SET_BITS(&device_data->base->cr,
				      HASH_CR_PRIVN_MASK);
		पूर्ण

		HASH_INITIALIZE;

		अगर (ctx->config.oper_mode == HASH_OPER_MODE_HMAC)
			hash_hw_ग_लिखो_key(device_data, ctx->key, ctx->keylen);

		/* Number of bits in last word = (nbytes * 8) % 32 */
		HASH_SET_NBLW((req->nbytes * 8) % 32);
		req_ctx->updated = 1;
	पूर्ण

	/* Store the nents in the dma काष्ठा. */
	ctx->device->dma.nents = hash_get_nents(req->src, req->nbytes, शून्य);
	अगर (!ctx->device->dma.nents) अणु
		dev_err(device_data->dev, "%s: ctx->device->dma.nents = 0\n",
			__func__);
		ret = ctx->device->dma.nents;
		जाओ out;
	पूर्ण

	bytes_written = hash_dma_ग_लिखो(ctx, req->src, req->nbytes);
	अगर (bytes_written != req->nbytes) अणु
		dev_err(device_data->dev, "%s: hash_dma_write() failed!\n",
			__func__);
		ret = bytes_written;
		जाओ out;
	पूर्ण

	रुको_क्रम_completion(&ctx->device->dma.complete);
	hash_dma_करोne(ctx);

	जबतक (पढ़ोl(&device_data->base->str) & HASH_STR_DCAL_MASK)
		cpu_relax();

	अगर (ctx->config.oper_mode == HASH_OPER_MODE_HMAC && ctx->key) अणु
		अचिन्हित पूर्णांक keylen = ctx->keylen;
		u8 *key = ctx->key;

		dev_dbg(device_data->dev, "%s: keylen: %d\n",
			__func__, ctx->keylen);
		hash_hw_ग_लिखो_key(device_data, key, keylen);
	पूर्ण

	hash_get_digest(device_data, digest, ctx->config.algorithm);
	स_नकल(req->result, digest, ctx->digestsize);

out:
	release_hash_device(device_data);

	/**
	 * Allocated in setkey, and only used in HMAC.
	 */
	kमुक्त(ctx->key);

	वापस ret;
पूर्ण

/**
 * hash_hw_final - The final hash calculation function
 * @req:	The hash request क्रम the job.
 */
अटल पूर्णांक hash_hw_final(काष्ठा ahash_request *req)
अणु
	पूर्णांक ret = 0;
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा hash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा hash_req_ctx *req_ctx = ahash_request_ctx(req);
	काष्ठा hash_device_data *device_data;
	u8 digest[SHA256_DIGEST_SIZE];

	ret = hash_get_device_data(ctx, &device_data);
	अगर (ret)
		वापस ret;

	dev_dbg(device_data->dev, "%s: (ctx=0x%lx)!\n", __func__,
		(अचिन्हित दीर्घ)ctx);

	अगर (req_ctx->updated) अणु
		ret = hash_resume_state(device_data, &device_data->state);

		अगर (ret) अणु
			dev_err(device_data->dev,
				"%s: hash_resume_state() failed!\n", __func__);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (req->nbytes == 0 && ctx->keylen == 0) अणु
		u8 zero_hash[SHA256_DIGEST_SIZE];
		u32 zero_hash_size = 0;
		bool zero_digest = false;
		/**
		 * Use a pre-calculated empty message digest
		 * (workaround since hw वापस zeroes, hw bug!?)
		 */
		ret = get_empty_message_digest(device_data, &zero_hash[0],
				&zero_hash_size, &zero_digest);
		अगर (!ret && likely(zero_hash_size == ctx->digestsize) &&
		    zero_digest) अणु
			स_नकल(req->result, &zero_hash[0], ctx->digestsize);
			जाओ out;
		पूर्ण अन्यथा अगर (!ret && !zero_digest) अणु
			dev_dbg(device_data->dev,
				"%s: HMAC zero msg with key, continue...\n",
				__func__);
		पूर्ण अन्यथा अणु
			dev_err(device_data->dev,
				"%s: ret=%d, or wrong digest size? %s\n",
				__func__, ret,
				zero_hash_size == ctx->digestsize ?
				"true" : "false");
			/* Return error */
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (req->nbytes == 0 && ctx->keylen > 0) अणु
		dev_err(device_data->dev, "%s: Empty message with keylength > 0, NOT supported\n",
			__func__);
		जाओ out;
	पूर्ण

	अगर (!req_ctx->updated) अणु
		ret = init_hash_hw(device_data, ctx);
		अगर (ret) अणु
			dev_err(device_data->dev,
				"%s: init_hash_hw() failed!\n", __func__);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (req_ctx->state.index) अणु
		hash_messagepad(device_data, req_ctx->state.buffer,
				req_ctx->state.index);
	पूर्ण अन्यथा अणु
		HASH_SET_DCAL;
		जबतक (पढ़ोl(&device_data->base->str) & HASH_STR_DCAL_MASK)
			cpu_relax();
	पूर्ण

	अगर (ctx->config.oper_mode == HASH_OPER_MODE_HMAC && ctx->key) अणु
		अचिन्हित पूर्णांक keylen = ctx->keylen;
		u8 *key = ctx->key;

		dev_dbg(device_data->dev, "%s: keylen: %d\n",
			__func__, ctx->keylen);
		hash_hw_ग_लिखो_key(device_data, key, keylen);
	पूर्ण

	hash_get_digest(device_data, digest, ctx->config.algorithm);
	स_नकल(req->result, digest, ctx->digestsize);

out:
	release_hash_device(device_data);

	/**
	 * Allocated in setkey, and only used in HMAC.
	 */
	kमुक्त(ctx->key);

	वापस ret;
पूर्ण

/**
 * hash_hw_update - Updates current HASH computation hashing another part of
 *                  the message.
 * @req:	Byte array containing the message to be hashed (caller
 *		allocated).
 */
पूर्णांक hash_hw_update(काष्ठा ahash_request *req)
अणु
	पूर्णांक ret = 0;
	u8 index = 0;
	u8 *buffer;
	काष्ठा hash_device_data *device_data;
	u8 *data_buffer;
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा hash_ctx *ctx = crypto_ahash_ctx(tfm);
	काष्ठा hash_req_ctx *req_ctx = ahash_request_ctx(req);
	काष्ठा crypto_hash_walk walk;
	पूर्णांक msg_length;

	index = req_ctx->state.index;
	buffer = (u8 *)req_ctx->state.buffer;

	ret = hash_get_device_data(ctx, &device_data);
	अगर (ret)
		वापस ret;

	msg_length = crypto_hash_walk_first(req, &walk);

	/* Empty message ("") is correct indata */
	अगर (msg_length == 0) अणु
		ret = 0;
		जाओ release_dev;
	पूर्ण

	/* Check अगर ctx->state.length + msg_length
	   overflows */
	अगर (msg_length > (req_ctx->state.length.low_word + msg_length) &&
	    HASH_HIGH_WORD_MAX_VAL == req_ctx->state.length.high_word) अणु
		pr_err("%s: HASH_MSG_LENGTH_OVERFLOW!\n", __func__);
		ret = crypto_hash_walk_करोne(&walk, -EPERM);
		जाओ release_dev;
	पूर्ण

	/* Main loop */
	जबतक (0 != msg_length) अणु
		data_buffer = walk.data;
		ret = hash_process_data(device_data, ctx, req_ctx, msg_length,
				data_buffer, buffer, &index);

		अगर (ret) अणु
			dev_err(device_data->dev, "%s: hash_internal_hw_update() failed!\n",
				__func__);
			crypto_hash_walk_करोne(&walk, ret);
			जाओ release_dev;
		पूर्ण

		msg_length = crypto_hash_walk_करोne(&walk, 0);
	पूर्ण

	req_ctx->state.index = index;
	dev_dbg(device_data->dev, "%s: indata length=%d, bin=%d\n",
		__func__, req_ctx->state.index, req_ctx->state.bit_index);

release_dev:
	release_hash_device(device_data);

	वापस ret;
पूर्ण

/**
 * hash_resume_state - Function that resumes the state of an calculation.
 * @device_data:	Poपूर्णांकer to the device काष्ठाure.
 * @device_state:	The state to be restored in the hash hardware
 */
पूर्णांक hash_resume_state(काष्ठा hash_device_data *device_data,
		      स्थिर काष्ठा hash_state *device_state)
अणु
	u32 temp_cr;
	s32 count;
	पूर्णांक hash_mode = HASH_OPER_MODE_HASH;

	अगर (शून्य == device_state) अणु
		dev_err(device_data->dev, "%s: HASH_INVALID_PARAMETER!\n",
			__func__);
		वापस -EPERM;
	पूर्ण

	/* Check correctness of index and length members */
	अगर (device_state->index > HASH_BLOCK_SIZE ||
	    (device_state->length.low_word % HASH_BLOCK_SIZE) != 0) अणु
		dev_err(device_data->dev, "%s: HASH_INVALID_PARAMETER!\n",
			__func__);
		वापस -EPERM;
	पूर्ण

	/*
	 * INIT bit. Set this bit to 0b1 to reset the HASH processor core and
	 * prepare the initialize the HASH accelerator to compute the message
	 * digest of a new message.
	 */
	HASH_INITIALIZE;

	temp_cr = device_state->temp_cr;
	ग_लिखोl_relaxed(temp_cr & HASH_CR_RESUME_MASK, &device_data->base->cr);

	अगर (पढ़ोl(&device_data->base->cr) & HASH_CR_MODE_MASK)
		hash_mode = HASH_OPER_MODE_HMAC;
	अन्यथा
		hash_mode = HASH_OPER_MODE_HASH;

	क्रम (count = 0; count < HASH_CSR_COUNT; count++) अणु
		अगर ((count >= 36) && (hash_mode == HASH_OPER_MODE_HASH))
			अवरोध;

		ग_लिखोl_relaxed(device_state->csr[count],
			       &device_data->base->csrx[count]);
	पूर्ण

	ग_लिखोl_relaxed(device_state->csfull, &device_data->base->csfull);
	ग_लिखोl_relaxed(device_state->csdatain, &device_data->base->csdatain);

	ग_लिखोl_relaxed(device_state->str_reg, &device_data->base->str);
	ग_लिखोl_relaxed(temp_cr, &device_data->base->cr);

	वापस 0;
पूर्ण

/**
 * hash_save_state - Function that saves the state of hardware.
 * @device_data:	Poपूर्णांकer to the device काष्ठाure.
 * @device_state:	The strucure where the hardware state should be saved.
 */
पूर्णांक hash_save_state(काष्ठा hash_device_data *device_data,
		    काष्ठा hash_state *device_state)
अणु
	u32 temp_cr;
	u32 count;
	पूर्णांक hash_mode = HASH_OPER_MODE_HASH;

	अगर (शून्य == device_state) अणु
		dev_err(device_data->dev, "%s: HASH_INVALID_PARAMETER!\n",
			__func__);
		वापस -ENOTSUPP;
	पूर्ण

	/* Write dummy value to क्रमce digest पूर्णांकermediate calculation. This
	 * actually makes sure that there isn't any ongoing calculation in the
	 * hardware.
	 */
	जबतक (पढ़ोl(&device_data->base->str) & HASH_STR_DCAL_MASK)
		cpu_relax();

	temp_cr = पढ़ोl_relaxed(&device_data->base->cr);

	device_state->str_reg = पढ़ोl_relaxed(&device_data->base->str);

	device_state->din_reg = पढ़ोl_relaxed(&device_data->base->din);

	अगर (पढ़ोl(&device_data->base->cr) & HASH_CR_MODE_MASK)
		hash_mode = HASH_OPER_MODE_HMAC;
	अन्यथा
		hash_mode = HASH_OPER_MODE_HASH;

	क्रम (count = 0; count < HASH_CSR_COUNT; count++) अणु
		अगर ((count >= 36) && (hash_mode == HASH_OPER_MODE_HASH))
			अवरोध;

		device_state->csr[count] =
			पढ़ोl_relaxed(&device_data->base->csrx[count]);
	पूर्ण

	device_state->csfull = पढ़ोl_relaxed(&device_data->base->csfull);
	device_state->csdatain = पढ़ोl_relaxed(&device_data->base->csdatain);

	device_state->temp_cr = temp_cr;

	वापस 0;
पूर्ण

/**
 * hash_check_hw - This routine checks क्रम peripheral Ids and PCell Ids.
 * @device_data:
 *
 */
पूर्णांक hash_check_hw(काष्ठा hash_device_data *device_data)
अणु
	/* Checking Peripheral Ids  */
	अगर (HASH_P_ID0 == पढ़ोl_relaxed(&device_data->base->periphid0) &&
	    HASH_P_ID1 == पढ़ोl_relaxed(&device_data->base->periphid1) &&
	    HASH_P_ID2 == पढ़ोl_relaxed(&device_data->base->periphid2) &&
	    HASH_P_ID3 == पढ़ोl_relaxed(&device_data->base->periphid3) &&
	    HASH_CELL_ID0 == पढ़ोl_relaxed(&device_data->base->cellid0) &&
	    HASH_CELL_ID1 == पढ़ोl_relaxed(&device_data->base->cellid1) &&
	    HASH_CELL_ID2 == पढ़ोl_relaxed(&device_data->base->cellid2) &&
	    HASH_CELL_ID3 == पढ़ोl_relaxed(&device_data->base->cellid3)) अणु
		वापस 0;
	पूर्ण

	dev_err(device_data->dev, "%s: HASH_UNSUPPORTED_HW!\n", __func__);
	वापस -ENOTSUPP;
पूर्ण

/**
 * hash_get_digest - Gets the digest.
 * @device_data:	Poपूर्णांकer to the device काष्ठाure.
 * @digest:		User allocated byte array क्रम the calculated digest.
 * @algorithm:		The algorithm in use.
 */
व्योम hash_get_digest(काष्ठा hash_device_data *device_data,
		     u8 *digest, पूर्णांक algorithm)
अणु
	u32 temp_hx_val, count;
	पूर्णांक loop_ctr;

	अगर (algorithm != HASH_ALGO_SHA1 && algorithm != HASH_ALGO_SHA256) अणु
		dev_err(device_data->dev, "%s: Incorrect algorithm %d\n",
			__func__, algorithm);
		वापस;
	पूर्ण

	अगर (algorithm == HASH_ALGO_SHA1)
		loop_ctr = SHA1_DIGEST_SIZE / माप(u32);
	अन्यथा
		loop_ctr = SHA256_DIGEST_SIZE / माप(u32);

	dev_dbg(device_data->dev, "%s: digest array:(0x%lx)\n",
		__func__, (अचिन्हित दीर्घ)digest);

	/* Copy result पूर्णांकo digest array */
	क्रम (count = 0; count < loop_ctr; count++) अणु
		temp_hx_val = पढ़ोl_relaxed(&device_data->base->hx[count]);
		digest[count * 4] = (u8) ((temp_hx_val >> 24) & 0xFF);
		digest[count * 4 + 1] = (u8) ((temp_hx_val >> 16) & 0xFF);
		digest[count * 4 + 2] = (u8) ((temp_hx_val >> 8) & 0xFF);
		digest[count * 4 + 3] = (u8) ((temp_hx_val >> 0) & 0xFF);
	पूर्ण
पूर्ण

/**
 * ahash_update - The hash update function क्रम SHA1/SHA2 (SHA256).
 * @req: The hash request क्रम the job.
 */
अटल पूर्णांक ahash_update(काष्ठा ahash_request *req)
अणु
	पूर्णांक ret = 0;
	काष्ठा hash_req_ctx *req_ctx = ahash_request_ctx(req);

	अगर (hash_mode != HASH_MODE_DMA || !req_ctx->dma_mode)
		ret = hash_hw_update(req);
	/* Skip update क्रम DMA, all data will be passed to DMA in final */

	अगर (ret) अणु
		pr_err("%s: hash_hw_update() failed!\n", __func__);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * ahash_final - The hash final function क्रम SHA1/SHA2 (SHA256).
 * @req:	The hash request क्रम the job.
 */
अटल पूर्णांक ahash_final(काष्ठा ahash_request *req)
अणु
	पूर्णांक ret = 0;
	काष्ठा hash_req_ctx *req_ctx = ahash_request_ctx(req);

	pr_debug("%s: data size: %d\n", __func__, req->nbytes);

	अगर ((hash_mode == HASH_MODE_DMA) && req_ctx->dma_mode)
		ret = hash_dma_final(req);
	अन्यथा
		ret = hash_hw_final(req);

	अगर (ret) अणु
		pr_err("%s: hash_hw/dma_final() failed\n", __func__);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hash_setkey(काष्ठा crypto_ahash *tfm,
		       स्थिर u8 *key, अचिन्हित पूर्णांक keylen, पूर्णांक alg)
अणु
	पूर्णांक ret = 0;
	काष्ठा hash_ctx *ctx = crypto_ahash_ctx(tfm);

	/**
	 * Freed in final.
	 */
	ctx->key = kmemdup(key, keylen, GFP_KERNEL);
	अगर (!ctx->key) अणु
		pr_err("%s: Failed to allocate ctx->key for %d\n",
		       __func__, alg);
		वापस -ENOMEM;
	पूर्ण
	ctx->keylen = keylen;

	वापस ret;
पूर्ण

अटल पूर्णांक ahash_sha1_init(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा hash_ctx *ctx = crypto_ahash_ctx(tfm);

	ctx->config.data_क्रमmat = HASH_DATA_8_BITS;
	ctx->config.algorithm = HASH_ALGO_SHA1;
	ctx->config.oper_mode = HASH_OPER_MODE_HASH;
	ctx->digestsize = SHA1_DIGEST_SIZE;

	वापस ux500_hash_init(req);
पूर्ण

अटल पूर्णांक ahash_sha256_init(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा hash_ctx *ctx = crypto_ahash_ctx(tfm);

	ctx->config.data_क्रमmat = HASH_DATA_8_BITS;
	ctx->config.algorithm = HASH_ALGO_SHA256;
	ctx->config.oper_mode = HASH_OPER_MODE_HASH;
	ctx->digestsize = SHA256_DIGEST_SIZE;

	वापस ux500_hash_init(req);
पूर्ण

अटल पूर्णांक ahash_sha1_digest(काष्ठा ahash_request *req)
अणु
	पूर्णांक ret2, ret1;

	ret1 = ahash_sha1_init(req);
	अगर (ret1)
		जाओ out;

	ret1 = ahash_update(req);
	ret2 = ahash_final(req);

out:
	वापस ret1 ? ret1 : ret2;
पूर्ण

अटल पूर्णांक ahash_sha256_digest(काष्ठा ahash_request *req)
अणु
	पूर्णांक ret2, ret1;

	ret1 = ahash_sha256_init(req);
	अगर (ret1)
		जाओ out;

	ret1 = ahash_update(req);
	ret2 = ahash_final(req);

out:
	वापस ret1 ? ret1 : ret2;
पूर्ण

अटल पूर्णांक ahash_noimport(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक ahash_noexport(काष्ठा ahash_request *req, व्योम *out)
अणु
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक hmac_sha1_init(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा hash_ctx *ctx = crypto_ahash_ctx(tfm);

	ctx->config.data_क्रमmat	= HASH_DATA_8_BITS;
	ctx->config.algorithm	= HASH_ALGO_SHA1;
	ctx->config.oper_mode	= HASH_OPER_MODE_HMAC;
	ctx->digestsize		= SHA1_DIGEST_SIZE;

	वापस ux500_hash_init(req);
पूर्ण

अटल पूर्णांक hmac_sha256_init(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा hash_ctx *ctx = crypto_ahash_ctx(tfm);

	ctx->config.data_क्रमmat	= HASH_DATA_8_BITS;
	ctx->config.algorithm	= HASH_ALGO_SHA256;
	ctx->config.oper_mode	= HASH_OPER_MODE_HMAC;
	ctx->digestsize		= SHA256_DIGEST_SIZE;

	वापस ux500_hash_init(req);
पूर्ण

अटल पूर्णांक hmac_sha1_digest(काष्ठा ahash_request *req)
अणु
	पूर्णांक ret2, ret1;

	ret1 = hmac_sha1_init(req);
	अगर (ret1)
		जाओ out;

	ret1 = ahash_update(req);
	ret2 = ahash_final(req);

out:
	वापस ret1 ? ret1 : ret2;
पूर्ण

अटल पूर्णांक hmac_sha256_digest(काष्ठा ahash_request *req)
अणु
	पूर्णांक ret2, ret1;

	ret1 = hmac_sha256_init(req);
	अगर (ret1)
		जाओ out;

	ret1 = ahash_update(req);
	ret2 = ahash_final(req);

out:
	वापस ret1 ? ret1 : ret2;
पूर्ण

अटल पूर्णांक hmac_sha1_setkey(काष्ठा crypto_ahash *tfm,
			    स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस hash_setkey(tfm, key, keylen, HASH_ALGO_SHA1);
पूर्ण

अटल पूर्णांक hmac_sha256_setkey(काष्ठा crypto_ahash *tfm,
			      स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	वापस hash_setkey(tfm, key, keylen, HASH_ALGO_SHA256);
पूर्ण

काष्ठा hash_algo_ढाँचा अणु
	काष्ठा hash_config conf;
	काष्ठा ahash_alg hash;
पूर्ण;

अटल पूर्णांक hash_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा hash_ctx *ctx = crypto_tfm_ctx(tfm);
	काष्ठा crypto_alg *alg = tfm->__crt_alg;
	काष्ठा hash_algo_ढाँचा *hash_alg;

	hash_alg = container_of(__crypto_ahash_alg(alg),
			काष्ठा hash_algo_ढाँचा,
			hash);

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा hash_req_ctx));

	ctx->config.data_क्रमmat = HASH_DATA_8_BITS;
	ctx->config.algorithm = hash_alg->conf.algorithm;
	ctx->config.oper_mode = hash_alg->conf.oper_mode;

	ctx->digestsize = hash_alg->hash.halg.digestsize;

	वापस 0;
पूर्ण

अटल काष्ठा hash_algo_ढाँचा hash_algs[] = अणु
	अणु
		.conf.algorithm = HASH_ALGO_SHA1,
		.conf.oper_mode = HASH_OPER_MODE_HASH,
		.hash = अणु
			.init = ux500_hash_init,
			.update = ahash_update,
			.final = ahash_final,
			.digest = ahash_sha1_digest,
			.export = ahash_noexport,
			.import = ahash_noimport,
			.halg.digestsize = SHA1_DIGEST_SIZE,
			.halg.statesize = माप(काष्ठा hash_ctx),
			.halg.base = अणु
				.cra_name = "sha1",
				.cra_driver_name = "sha1-ux500",
				.cra_flags = CRYPTO_ALG_ASYNC,
				.cra_blocksize = SHA1_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा hash_ctx),
				.cra_init = hash_cra_init,
				.cra_module = THIS_MODULE,
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.conf.algorithm	= HASH_ALGO_SHA256,
		.conf.oper_mode	= HASH_OPER_MODE_HASH,
		.hash = अणु
			.init = ux500_hash_init,
			.update	= ahash_update,
			.final = ahash_final,
			.digest = ahash_sha256_digest,
			.export = ahash_noexport,
			.import = ahash_noimport,
			.halg.digestsize = SHA256_DIGEST_SIZE,
			.halg.statesize = माप(काष्ठा hash_ctx),
			.halg.base = अणु
				.cra_name = "sha256",
				.cra_driver_name = "sha256-ux500",
				.cra_flags = CRYPTO_ALG_ASYNC,
				.cra_blocksize = SHA256_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा hash_ctx),
				.cra_init = hash_cra_init,
				.cra_module = THIS_MODULE,
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.conf.algorithm = HASH_ALGO_SHA1,
		.conf.oper_mode = HASH_OPER_MODE_HMAC,
			.hash = अणु
			.init = ux500_hash_init,
			.update = ahash_update,
			.final = ahash_final,
			.digest = hmac_sha1_digest,
			.setkey = hmac_sha1_setkey,
			.export = ahash_noexport,
			.import = ahash_noimport,
			.halg.digestsize = SHA1_DIGEST_SIZE,
			.halg.statesize = माप(काष्ठा hash_ctx),
			.halg.base = अणु
				.cra_name = "hmac(sha1)",
				.cra_driver_name = "hmac-sha1-ux500",
				.cra_flags = CRYPTO_ALG_ASYNC,
				.cra_blocksize = SHA1_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा hash_ctx),
				.cra_init = hash_cra_init,
				.cra_module = THIS_MODULE,
			पूर्ण
		पूर्ण
	पूर्ण,
	अणु
		.conf.algorithm = HASH_ALGO_SHA256,
		.conf.oper_mode = HASH_OPER_MODE_HMAC,
		.hash = अणु
			.init = ux500_hash_init,
			.update = ahash_update,
			.final = ahash_final,
			.digest = hmac_sha256_digest,
			.setkey = hmac_sha256_setkey,
			.export = ahash_noexport,
			.import = ahash_noimport,
			.halg.digestsize = SHA256_DIGEST_SIZE,
			.halg.statesize = माप(काष्ठा hash_ctx),
			.halg.base = अणु
				.cra_name = "hmac(sha256)",
				.cra_driver_name = "hmac-sha256-ux500",
				.cra_flags = CRYPTO_ALG_ASYNC,
				.cra_blocksize = SHA256_BLOCK_SIZE,
				.cra_ctxsize = माप(काष्ठा hash_ctx),
				.cra_init = hash_cra_init,
				.cra_module = THIS_MODULE,
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण;

अटल पूर्णांक ahash_algs_रेजिस्टर_all(काष्ठा hash_device_data *device_data)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	पूर्णांक count;

	क्रम (i = 0; i < ARRAY_SIZE(hash_algs); i++) अणु
		ret = crypto_रेजिस्टर_ahash(&hash_algs[i].hash);
		अगर (ret) अणु
			count = i;
			dev_err(device_data->dev, "%s: alg registration failed\n",
				hash_algs[i].hash.halg.base.cra_driver_name);
			जाओ unreg;
		पूर्ण
	पूर्ण
	वापस 0;
unreg:
	क्रम (i = 0; i < count; i++)
		crypto_unरेजिस्टर_ahash(&hash_algs[i].hash);
	वापस ret;
पूर्ण

अटल व्योम ahash_algs_unरेजिस्टर_all(काष्ठा hash_device_data *device_data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(hash_algs); i++)
		crypto_unरेजिस्टर_ahash(&hash_algs[i].hash);
पूर्ण

/**
 * ux500_hash_probe - Function that probes the hash hardware.
 * @pdev: The platक्रमm device.
 */
अटल पूर्णांक ux500_hash_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक			ret = 0;
	काष्ठा resource		*res = शून्य;
	काष्ठा hash_device_data *device_data;
	काष्ठा device		*dev = &pdev->dev;

	device_data = devm_kzalloc(dev, माप(*device_data), GFP_ATOMIC);
	अगर (!device_data) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	device_data->dev = dev;
	device_data->current_ctx = शून्य;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_dbg(dev, "%s: platform_get_resource() failed!\n", __func__);
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
	spin_lock_init(&device_data->घातer_state_lock);

	/* Enable घातer क्रम HASH1 hardware block */
	device_data->regulator = regulator_get(dev, "v-ape");
	अगर (IS_ERR(device_data->regulator)) अणु
		dev_err(dev, "%s: regulator_get() failed!\n", __func__);
		ret = PTR_ERR(device_data->regulator);
		device_data->regulator = शून्य;
		जाओ out;
	पूर्ण

	/* Enable the घड़ी क्रम HASH1 hardware block */
	device_data->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(device_data->clk)) अणु
		dev_err(dev, "%s: clk_get() failed!\n", __func__);
		ret = PTR_ERR(device_data->clk);
		जाओ out_regulator;
	पूर्ण

	ret = clk_prepare(device_data->clk);
	अगर (ret) अणु
		dev_err(dev, "%s: clk_prepare() failed!\n", __func__);
		जाओ out_regulator;
	पूर्ण

	/* Enable device घातer (and घड़ी) */
	ret = hash_enable_घातer(device_data, false);
	अगर (ret) अणु
		dev_err(dev, "%s: hash_enable_power() failed!\n", __func__);
		जाओ out_clk_unprepare;
	पूर्ण

	ret = hash_check_hw(device_data);
	अगर (ret) अणु
		dev_err(dev, "%s: hash_check_hw() failed!\n", __func__);
		जाओ out_घातer;
	पूर्ण

	अगर (hash_mode == HASH_MODE_DMA)
		hash_dma_setup_channel(device_data, dev);

	platक्रमm_set_drvdata(pdev, device_data);

	/* Put the new device पूर्णांकo the device list... */
	klist_add_tail(&device_data->list_node, &driver_data.device_list);
	/* ... and संकेत that a new device is available. */
	up(&driver_data.device_allocation);

	ret = ahash_algs_रेजिस्टर_all(device_data);
	अगर (ret) अणु
		dev_err(dev, "%s: ahash_algs_register_all() failed!\n",
			__func__);
		जाओ out_घातer;
	पूर्ण

	dev_info(dev, "successfully registered\n");
	वापस 0;

out_घातer:
	hash_disable_घातer(device_data, false);

out_clk_unprepare:
	clk_unprepare(device_data->clk);

out_regulator:
	regulator_put(device_data->regulator);

out:
	वापस ret;
पूर्ण

/**
 * ux500_hash_हटाओ - Function that हटाओs the hash device from the platक्रमm.
 * @pdev: The platक्रमm device.
 */
अटल पूर्णांक ux500_hash_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hash_device_data *device_data;
	काष्ठा device		*dev = &pdev->dev;

	device_data = platक्रमm_get_drvdata(pdev);
	अगर (!device_data) अणु
		dev_err(dev, "%s: platform_get_drvdata() failed!\n", __func__);
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
		ahash_algs_unरेजिस्टर_all(device_data);

	अगर (hash_disable_घातer(device_data, false))
		dev_err(dev, "%s: hash_disable_power() failed\n",
			__func__);

	clk_unprepare(device_data->clk);
	regulator_put(device_data->regulator);

	वापस 0;
पूर्ण

/**
 * ux500_hash_shutकरोwn - Function that shutकरोwn the hash device.
 * @pdev: The platक्रमm device
 */
अटल व्योम ux500_hash_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hash_device_data *device_data;

	device_data = platक्रमm_get_drvdata(pdev);
	अगर (!device_data) अणु
		dev_err(&pdev->dev, "%s: platform_get_drvdata() failed!\n",
			__func__);
		वापस;
	पूर्ण

	/* Check that the device is मुक्त */
	spin_lock(&device_data->ctx_lock);
	/* current_ctx allocates a device, शून्य = unallocated */
	अगर (!device_data->current_ctx) अणु
		अगर (करोwn_trylock(&driver_data.device_allocation))
			dev_dbg(&pdev->dev, "%s: Cryp still in use! Shutting down anyway...\n",
				__func__);
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
		ahash_algs_unरेजिस्टर_all(device_data);

	अगर (hash_disable_घातer(device_data, false))
		dev_err(&pdev->dev, "%s: hash_disable_power() failed\n",
			__func__);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/**
 * ux500_hash_suspend - Function that suspends the hash device.
 * @dev:	Device to suspend.
 */
अटल पूर्णांक ux500_hash_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा hash_device_data *device_data;
	काष्ठा hash_ctx *temp_ctx = शून्य;

	device_data = dev_get_drvdata(dev);
	अगर (!device_data) अणु
		dev_err(dev, "%s: platform_get_drvdata() failed!\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	spin_lock(&device_data->ctx_lock);
	अगर (!device_data->current_ctx)
		device_data->current_ctx++;
	spin_unlock(&device_data->ctx_lock);

	अगर (device_data->current_ctx == ++temp_ctx) अणु
		अगर (करोwn_पूर्णांकerruptible(&driver_data.device_allocation))
			dev_dbg(dev, "%s: down_interruptible() failed\n",
				__func__);
		ret = hash_disable_घातer(device_data, false);

	पूर्ण अन्यथा अणु
		ret = hash_disable_घातer(device_data, true);
	पूर्ण

	अगर (ret)
		dev_err(dev, "%s: hash_disable_power()\n", __func__);

	वापस ret;
पूर्ण

/**
 * ux500_hash_resume - Function that resume the hash device.
 * @dev:	Device to resume.
 */
अटल पूर्णांक ux500_hash_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret = 0;
	काष्ठा hash_device_data *device_data;
	काष्ठा hash_ctx *temp_ctx = शून्य;

	device_data = dev_get_drvdata(dev);
	अगर (!device_data) अणु
		dev_err(dev, "%s: platform_get_drvdata() failed!\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	spin_lock(&device_data->ctx_lock);
	अगर (device_data->current_ctx == ++temp_ctx)
		device_data->current_ctx = शून्य;
	spin_unlock(&device_data->ctx_lock);

	अगर (!device_data->current_ctx)
		up(&driver_data.device_allocation);
	अन्यथा
		ret = hash_enable_घातer(device_data, true);

	अगर (ret)
		dev_err(dev, "%s: hash_enable_power() failed!\n", __func__);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(ux500_hash_pm, ux500_hash_suspend, ux500_hash_resume);

अटल स्थिर काष्ठा of_device_id ux500_hash_match[] = अणु
	अणु .compatible = "stericsson,ux500-hash" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ux500_hash_match);

अटल काष्ठा platक्रमm_driver hash_driver = अणु
	.probe  = ux500_hash_probe,
	.हटाओ = ux500_hash_हटाओ,
	.shutकरोwn = ux500_hash_shutकरोwn,
	.driver = अणु
		.name  = "hash1",
		.of_match_table = ux500_hash_match,
		.pm    = &ux500_hash_pm,
	पूर्ण
पूर्ण;

/**
 * ux500_hash_mod_init - The kernel module init function.
 */
अटल पूर्णांक __init ux500_hash_mod_init(व्योम)
अणु
	klist_init(&driver_data.device_list, शून्य, शून्य);
	/* Initialize the semaphore to 0 devices (locked state) */
	sema_init(&driver_data.device_allocation, 0);

	वापस platक्रमm_driver_रेजिस्टर(&hash_driver);
पूर्ण

/**
 * ux500_hash_mod_fini - The kernel module निकास function.
 */
अटल व्योम __निकास ux500_hash_mod_fini(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&hash_driver);
पूर्ण

module_init(ux500_hash_mod_init);
module_निकास(ux500_hash_mod_fini);

MODULE_DESCRIPTION("Driver for ST-Ericsson UX500 HASH engine.");
MODULE_LICENSE("GPL");

MODULE_ALIAS_CRYPTO("sha1-all");
MODULE_ALIAS_CRYPTO("sha256-all");
MODULE_ALIAS_CRYPTO("hmac-sha1-all");
MODULE_ALIAS_CRYPTO("hmac-sha256-all");
