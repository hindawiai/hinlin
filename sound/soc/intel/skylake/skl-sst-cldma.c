<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * skl-sst-cldma.c - Code Loader DMA handler
 *
 * Copyright (C) 2015, Intel Corporation.
 * Author: Subhransu S. Prusty <subhransu.s.prusty@पूर्णांकel.com>
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश "../common/sst-dsp.h"
#समावेश "../common/sst-dsp-priv.h"

अटल व्योम skl_cldma_पूर्णांक_enable(काष्ठा sst_dsp *ctx)
अणु
	sst_dsp_shim_update_bits_unlocked(ctx, SKL_ADSP_REG_ADSPIC,
				SKL_ADSPIC_CL_DMA, SKL_ADSPIC_CL_DMA);
पूर्ण

व्योम skl_cldma_पूर्णांक_disable(काष्ठा sst_dsp *ctx)
अणु
	sst_dsp_shim_update_bits_unlocked(ctx,
			SKL_ADSP_REG_ADSPIC, SKL_ADSPIC_CL_DMA, 0);
पूर्ण

अटल व्योम skl_cldma_stream_run(काष्ठा sst_dsp  *ctx, bool enable)
अणु
	अचिन्हित अक्षर val;
	पूर्णांक समयout;

	sst_dsp_shim_update_bits_unlocked(ctx,
			SKL_ADSP_REG_CL_SD_CTL,
			CL_SD_CTL_RUN_MASK, CL_SD_CTL_RUN(enable));

	udelay(3);
	समयout = 300;
	करो अणु
		/* रुकोing क्रम hardware to report that the stream Run bit set */
		val = sst_dsp_shim_पढ़ो(ctx, SKL_ADSP_REG_CL_SD_CTL) &
			CL_SD_CTL_RUN_MASK;
		अगर (enable && val)
			अवरोध;
		अन्यथा अगर (!enable && !val)
			अवरोध;
		udelay(3);
	पूर्ण जबतक (--समयout);

	अगर (समयout == 0)
		dev_err(ctx->dev, "Failed to set Run bit=%d enable=%d\n", val, enable);
पूर्ण

अटल व्योम skl_cldma_stream_clear(काष्ठा sst_dsp  *ctx)
अणु
	/* make sure Run bit is cleared beक्रमe setting stream रेजिस्टर */
	skl_cldma_stream_run(ctx, 0);

	sst_dsp_shim_update_bits(ctx, SKL_ADSP_REG_CL_SD_CTL,
				CL_SD_CTL_IOCE_MASK, CL_SD_CTL_IOCE(0));
	sst_dsp_shim_update_bits(ctx, SKL_ADSP_REG_CL_SD_CTL,
				CL_SD_CTL_FEIE_MASK, CL_SD_CTL_FEIE(0));
	sst_dsp_shim_update_bits(ctx, SKL_ADSP_REG_CL_SD_CTL,
				CL_SD_CTL_DEIE_MASK, CL_SD_CTL_DEIE(0));
	sst_dsp_shim_update_bits(ctx, SKL_ADSP_REG_CL_SD_CTL,
				CL_SD_CTL_STRM_MASK, CL_SD_CTL_STRM(0));

	sst_dsp_shim_ग_लिखो(ctx, SKL_ADSP_REG_CL_SD_BDLPL, CL_SD_BDLPLBA(0));
	sst_dsp_shim_ग_लिखो(ctx, SKL_ADSP_REG_CL_SD_BDLPU, 0);

	sst_dsp_shim_ग_लिखो(ctx, SKL_ADSP_REG_CL_SD_CBL, 0);
	sst_dsp_shim_ग_लिखो(ctx, SKL_ADSP_REG_CL_SD_LVI, 0);
पूर्ण

/* Code loader helper APIs */
अटल व्योम skl_cldma_setup_bdle(काष्ठा sst_dsp *ctx,
		काष्ठा snd_dma_buffer *dmab_data,
		__le32 **bdlp, पूर्णांक size, पूर्णांक with_ioc)
अणु
	__le32 *bdl = *bdlp;

	ctx->cl_dev.frags = 0;
	जबतक (size > 0) अणु
		phys_addr_t addr = virt_to_phys(dmab_data->area +
				(ctx->cl_dev.frags * ctx->cl_dev.bufsize));

		bdl[0] = cpu_to_le32(lower_32_bits(addr));
		bdl[1] = cpu_to_le32(upper_32_bits(addr));

		bdl[2] = cpu_to_le32(ctx->cl_dev.bufsize);

		size -= ctx->cl_dev.bufsize;
		bdl[3] = (size || !with_ioc) ? 0 : cpu_to_le32(0x01);

		bdl += 4;
		ctx->cl_dev.frags++;
	पूर्ण
पूर्ण

/*
 * Setup controller
 * Configure the रेजिस्टरs to update the dma buffer address and
 * enable पूर्णांकerrupts.
 * Note: Using the channel 1 क्रम transfer
 */
अटल व्योम skl_cldma_setup_controller(काष्ठा sst_dsp  *ctx,
		काष्ठा snd_dma_buffer *dmab_bdl, अचिन्हित पूर्णांक max_size,
		u32 count)
अणु
	skl_cldma_stream_clear(ctx);
	sst_dsp_shim_ग_लिखो(ctx, SKL_ADSP_REG_CL_SD_BDLPL,
			CL_SD_BDLPLBA(dmab_bdl->addr));
	sst_dsp_shim_ग_लिखो(ctx, SKL_ADSP_REG_CL_SD_BDLPU,
			CL_SD_BDLPUBA(dmab_bdl->addr));

	sst_dsp_shim_ग_लिखो(ctx, SKL_ADSP_REG_CL_SD_CBL, max_size);
	sst_dsp_shim_ग_लिखो(ctx, SKL_ADSP_REG_CL_SD_LVI, count - 1);
	sst_dsp_shim_update_bits(ctx, SKL_ADSP_REG_CL_SD_CTL,
			CL_SD_CTL_IOCE_MASK, CL_SD_CTL_IOCE(1));
	sst_dsp_shim_update_bits(ctx, SKL_ADSP_REG_CL_SD_CTL,
			CL_SD_CTL_FEIE_MASK, CL_SD_CTL_FEIE(1));
	sst_dsp_shim_update_bits(ctx, SKL_ADSP_REG_CL_SD_CTL,
			CL_SD_CTL_DEIE_MASK, CL_SD_CTL_DEIE(1));
	sst_dsp_shim_update_bits(ctx, SKL_ADSP_REG_CL_SD_CTL,
			CL_SD_CTL_STRM_MASK, CL_SD_CTL_STRM(FW_CL_STREAM_NUMBER));
पूर्ण

अटल व्योम skl_cldma_setup_spb(काष्ठा sst_dsp  *ctx,
		अचिन्हित पूर्णांक size, bool enable)
अणु
	अगर (enable)
		sst_dsp_shim_update_bits_unlocked(ctx,
				SKL_ADSP_REG_CL_SPBFIFO_SPBFCCTL,
				CL_SPBFIFO_SPBFCCTL_SPIBE_MASK,
				CL_SPBFIFO_SPBFCCTL_SPIBE(1));

	sst_dsp_shim_ग_लिखो_unlocked(ctx, SKL_ADSP_REG_CL_SPBFIFO_SPIB, size);
पूर्ण

अटल व्योम skl_cldma_cleanup_spb(काष्ठा sst_dsp  *ctx)
अणु
	sst_dsp_shim_update_bits_unlocked(ctx,
			SKL_ADSP_REG_CL_SPBFIFO_SPBFCCTL,
			CL_SPBFIFO_SPBFCCTL_SPIBE_MASK,
			CL_SPBFIFO_SPBFCCTL_SPIBE(0));

	sst_dsp_shim_ग_लिखो_unlocked(ctx, SKL_ADSP_REG_CL_SPBFIFO_SPIB, 0);
पूर्ण

अटल व्योम skl_cldma_cleanup(काष्ठा sst_dsp  *ctx)
अणु
	skl_cldma_cleanup_spb(ctx);
	skl_cldma_stream_clear(ctx);

	ctx->dsp_ops.मुक्त_dma_buf(ctx->dev, &ctx->cl_dev.dmab_data);
	ctx->dsp_ops.मुक्त_dma_buf(ctx->dev, &ctx->cl_dev.dmab_bdl);
पूर्ण

पूर्णांक skl_cldma_रुको_पूर्णांकerruptible(काष्ठा sst_dsp *ctx)
अणु
	पूर्णांक ret = 0;

	अगर (!रुको_event_समयout(ctx->cl_dev.रुको_queue,
				ctx->cl_dev.रुको_condition,
				msecs_to_jअगरfies(SKL_WAIT_TIMEOUT))) अणु
		dev_err(ctx->dev, "%s: Wait timeout\n", __func__);
		ret = -EIO;
		जाओ cleanup;
	पूर्ण

	dev_dbg(ctx->dev, "%s: Event wake\n", __func__);
	अगर (ctx->cl_dev.wake_status != SKL_CL_DMA_BUF_COMPLETE) अणु
		dev_err(ctx->dev, "%s: DMA Error\n", __func__);
		ret = -EIO;
	पूर्ण

cleanup:
	ctx->cl_dev.wake_status = SKL_CL_DMA_STATUS_NONE;
	वापस ret;
पूर्ण

अटल व्योम skl_cldma_stop(काष्ठा sst_dsp *ctx)
अणु
	skl_cldma_stream_run(ctx, false);
पूर्ण

अटल व्योम skl_cldma_fill_buffer(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक size,
		स्थिर व्योम *curr_pos, bool पूर्णांकr_enable, bool trigger)
अणु
	dev_dbg(ctx->dev, "Size: %x, intr_enable: %d\n", size, पूर्णांकr_enable);
	dev_dbg(ctx->dev, "buf_pos_index:%d, trigger:%d\n",
			ctx->cl_dev.dma_buffer_offset, trigger);
	dev_dbg(ctx->dev, "spib position: %d\n", ctx->cl_dev.curr_spib_pos);

	/*
	 * Check अगर the size exceeds buffer boundary. If it exceeds
	 * max_buffer size, then copy till buffer size and then copy
	 * reमुख्यing buffer from the start of ring buffer.
	 */
	अगर (ctx->cl_dev.dma_buffer_offset + size > ctx->cl_dev.bufsize) अणु
		अचिन्हित पूर्णांक size_b = ctx->cl_dev.bufsize -
					ctx->cl_dev.dma_buffer_offset;
		स_नकल(ctx->cl_dev.dmab_data.area + ctx->cl_dev.dma_buffer_offset,
			curr_pos, size_b);
		size -= size_b;
		curr_pos += size_b;
		ctx->cl_dev.dma_buffer_offset = 0;
	पूर्ण

	स_नकल(ctx->cl_dev.dmab_data.area + ctx->cl_dev.dma_buffer_offset,
			curr_pos, size);

	अगर (ctx->cl_dev.curr_spib_pos == ctx->cl_dev.bufsize)
		ctx->cl_dev.dma_buffer_offset = 0;
	अन्यथा
		ctx->cl_dev.dma_buffer_offset = ctx->cl_dev.curr_spib_pos;

	ctx->cl_dev.रुको_condition = false;

	अगर (पूर्णांकr_enable)
		skl_cldma_पूर्णांक_enable(ctx);

	ctx->cl_dev.ops.cl_setup_spb(ctx, ctx->cl_dev.curr_spib_pos, trigger);
	अगर (trigger)
		ctx->cl_dev.ops.cl_trigger(ctx, true);
पूर्ण

/*
 * The CL dma करोesn't have any way to update the transfer status until a BDL
 * buffer is fully transferred
 *
 * So Copying is भागided in two parts.
 * 1. Interrupt on buffer करोne where the size to be transferred is more than
 *    ring buffer size.
 * 2. Polling on fw रेजिस्टर to identअगरy अगर data left to transferred करोesn't
 *    fill the ring buffer. Caller takes care of polling the required status
 *    रेजिस्टर to identअगरy the transfer status.
 * 3. अगर रुको flag is set, रुकोs क्रम DBL पूर्णांकerrupt to copy the next chunk till
 *    bytes_left is 0.
 *    अगर रुको flag is not set, करोesn't रुको क्रम BDL पूर्णांकerrupt. after ccopying
 *    the first chunk वापस the no of bytes_left to be copied.
 */
अटल पूर्णांक
skl_cldma_copy_to_buf(काष्ठा sst_dsp *ctx, स्थिर व्योम *bin,
			u32 total_size, bool रुको)
अणु
	पूर्णांक ret;
	bool start = true;
	अचिन्हित पूर्णांक excess_bytes;
	u32 size;
	अचिन्हित पूर्णांक bytes_left = total_size;
	स्थिर व्योम *curr_pos = bin;

	अगर (total_size <= 0)
		वापस -EINVAL;

	dev_dbg(ctx->dev, "%s: Total binary size: %u\n", __func__, bytes_left);

	जबतक (bytes_left) अणु
		अगर (bytes_left > ctx->cl_dev.bufsize) अणु

			/*
			 * dma transfers only till the ग_लिखो poपूर्णांकer as
			 * updated in spib
			 */
			अगर (ctx->cl_dev.curr_spib_pos == 0)
				ctx->cl_dev.curr_spib_pos = ctx->cl_dev.bufsize;

			size = ctx->cl_dev.bufsize;
			skl_cldma_fill_buffer(ctx, size, curr_pos, true, start);

			अगर (रुको) अणु
				start = false;
				ret = skl_cldma_रुको_पूर्णांकerruptible(ctx);
				अगर (ret < 0) अणु
					skl_cldma_stop(ctx);
					वापस ret;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			skl_cldma_पूर्णांक_disable(ctx);

			अगर ((ctx->cl_dev.curr_spib_pos + bytes_left)
							<= ctx->cl_dev.bufsize) अणु
				ctx->cl_dev.curr_spib_pos += bytes_left;
			पूर्ण अन्यथा अणु
				excess_bytes = bytes_left -
					(ctx->cl_dev.bufsize -
					ctx->cl_dev.curr_spib_pos);
				ctx->cl_dev.curr_spib_pos = excess_bytes;
			पूर्ण

			size = bytes_left;
			skl_cldma_fill_buffer(ctx, size,
					curr_pos, false, start);
		पूर्ण
		bytes_left -= size;
		curr_pos = curr_pos + size;
		अगर (!रुको)
			वापस bytes_left;
	पूर्ण

	वापस bytes_left;
पूर्ण

व्योम skl_cldma_process_पूर्णांकr(काष्ठा sst_dsp *ctx)
अणु
	u8 cl_dma_पूर्णांकr_status;

	cl_dma_पूर्णांकr_status =
		sst_dsp_shim_पढ़ो_unlocked(ctx, SKL_ADSP_REG_CL_SD_STS);

	अगर (!(cl_dma_पूर्णांकr_status & SKL_CL_DMA_SD_INT_COMPLETE))
		ctx->cl_dev.wake_status = SKL_CL_DMA_ERR;
	अन्यथा
		ctx->cl_dev.wake_status = SKL_CL_DMA_BUF_COMPLETE;

	ctx->cl_dev.रुको_condition = true;
	wake_up(&ctx->cl_dev.रुको_queue);
पूर्ण

पूर्णांक skl_cldma_prepare(काष्ठा sst_dsp *ctx)
अणु
	पूर्णांक ret;
	__le32 *bdl;

	ctx->cl_dev.bufsize = SKL_MAX_BUFFER_SIZE;

	/* Allocate cl ops */
	ctx->cl_dev.ops.cl_setup_bdle = skl_cldma_setup_bdle;
	ctx->cl_dev.ops.cl_setup_controller = skl_cldma_setup_controller;
	ctx->cl_dev.ops.cl_setup_spb = skl_cldma_setup_spb;
	ctx->cl_dev.ops.cl_cleanup_spb = skl_cldma_cleanup_spb;
	ctx->cl_dev.ops.cl_trigger = skl_cldma_stream_run;
	ctx->cl_dev.ops.cl_cleanup_controller = skl_cldma_cleanup;
	ctx->cl_dev.ops.cl_copy_to_dmabuf = skl_cldma_copy_to_buf;
	ctx->cl_dev.ops.cl_stop_dma = skl_cldma_stop;

	/* Allocate buffer*/
	ret = ctx->dsp_ops.alloc_dma_buf(ctx->dev,
			&ctx->cl_dev.dmab_data, ctx->cl_dev.bufsize);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Alloc buffer for base fw failed: %x\n", ret);
		वापस ret;
	पूर्ण
	/* Setup Code loader BDL */
	ret = ctx->dsp_ops.alloc_dma_buf(ctx->dev,
			&ctx->cl_dev.dmab_bdl, PAGE_SIZE);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Alloc buffer for blde failed: %x\n", ret);
		ctx->dsp_ops.मुक्त_dma_buf(ctx->dev, &ctx->cl_dev.dmab_data);
		वापस ret;
	पूर्ण
	bdl = (__le32 *)ctx->cl_dev.dmab_bdl.area;

	/* Allocate BDLs */
	ctx->cl_dev.ops.cl_setup_bdle(ctx, &ctx->cl_dev.dmab_data,
			&bdl, ctx->cl_dev.bufsize, 1);
	ctx->cl_dev.ops.cl_setup_controller(ctx, &ctx->cl_dev.dmab_bdl,
			ctx->cl_dev.bufsize, ctx->cl_dev.frags);

	ctx->cl_dev.curr_spib_pos = 0;
	ctx->cl_dev.dma_buffer_offset = 0;
	init_रुकोqueue_head(&ctx->cl_dev.रुको_queue);

	वापस ret;
पूर्ण
