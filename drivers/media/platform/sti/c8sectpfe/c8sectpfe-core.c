<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * c8sectpfe-core.c - C8SECTPFE STi DVB driver
 *
 * Copyright (c) STMicroelectronics 2015
 *
 *   Author:Peter Bennett <peter.bennett@st.com>
 *	    Peter Grअगरfin <peter.grअगरfin@linaro.org>
 *
 */
#समावेश <linux/atomic.h>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dvb/dmx.h>
#समावेश <linux/dvb/frontend.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/firmware.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/version.h>
#समावेश <linux/रुको.h>
#समावेश <linux/pinctrl/pinctrl.h>

#समावेश "c8sectpfe-core.h"
#समावेश "c8sectpfe-common.h"
#समावेश "c8sectpfe-debugfs.h"
#समावेश <media/dmxdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_net.h>

#घोषणा FIRMWARE_MEMDMA "pti_memdma_h407.elf"
MODULE_FIRMWARE(FIRMWARE_MEMDMA);

#घोषणा PID_TABLE_SIZE 1024
#घोषणा POLL_MSECS 50

अटल पूर्णांक load_c8sectpfe_fw(काष्ठा c8sectpfei *fei);

#घोषणा TS_PKT_SIZE 188
#घोषणा HEADER_SIZE (4)
#घोषणा PACKET_SIZE (TS_PKT_SIZE+HEADER_SIZE)

#घोषणा FEI_ALIGNMENT (32)
/* hw requires minimum of 8*PACKET_SIZE and padded to 8byte boundary */
#घोषणा FEI_BUFFER_SIZE (8*PACKET_SIZE*340)

#घोषणा FIFO_LEN 1024

अटल व्योम c8sectpfe_समयr_पूर्णांकerrupt(काष्ठा समयr_list *t)
अणु
	काष्ठा c8sectpfei *fei = from_समयr(fei, t, समयr);
	काष्ठा channel_info *channel;
	पूर्णांक chan_num;

	/* iterate through input block channels */
	क्रम (chan_num = 0; chan_num < fei->tsin_count; chan_num++) अणु
		channel = fei->channel_data[chan_num];

		/* is this descriptor initialised and TP enabled */
		अगर (channel->irec && पढ़ोl(channel->irec + DMA_PRDS_TPENABLE))
			tasklet_schedule(&channel->tsklet);
	पूर्ण

	fei->समयr.expires = jअगरfies +	msecs_to_jअगरfies(POLL_MSECS);
	add_समयr(&fei->समयr);
पूर्ण

अटल व्योम channel_swdemux_tsklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा channel_info *channel = from_tasklet(channel, t, tsklet);
	काष्ठा c8sectpfei *fei;
	अचिन्हित दीर्घ wp, rp;
	पूर्णांक pos, num_packets, n, size;
	u8 *buf;

	अगर (unlikely(!channel || !channel->irec))
		वापस;

	fei = channel->fei;

	wp = पढ़ोl(channel->irec + DMA_PRDS_BUSWP_TP(0));
	rp = पढ़ोl(channel->irec + DMA_PRDS_BUSRP_TP(0));

	pos = rp - channel->back_buffer_busaddr;

	/* has it wrapped */
	अगर (wp < rp)
		wp = channel->back_buffer_busaddr + FEI_BUFFER_SIZE;

	size = wp - rp;
	num_packets = size / PACKET_SIZE;

	/* manage cache so data is visible to CPU */
	dma_sync_single_क्रम_cpu(fei->dev,
				rp,
				size,
				DMA_FROM_DEVICE);

	buf = (u8 *) channel->back_buffer_aligned;

	dev_dbg(fei->dev,
		"chan=%d channel=%p num_packets = %d, buf = %p, pos = 0x%x\n\trp=0x%lx, wp=0x%lx\n",
		channel->tsin_id, channel, num_packets, buf, pos, rp, wp);

	क्रम (n = 0; n < num_packets; n++) अणु
		dvb_dmx_swfilter_packets(
			&fei->c8sectpfe[0]->
				demux[channel->demux_mapping].dvb_demux,
			&buf[pos], 1);

		pos += PACKET_SIZE;
	पूर्ण

	/* advance the पढ़ो poपूर्णांकer */
	अगर (wp == (channel->back_buffer_busaddr + FEI_BUFFER_SIZE))
		ग_लिखोl(channel->back_buffer_busaddr, channel->irec +
			DMA_PRDS_BUSRP_TP(0));
	अन्यथा
		ग_लिखोl(wp, channel->irec + DMA_PRDS_BUSRP_TP(0));
पूर्ण

अटल पूर्णांक c8sectpfe_start_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा dvb_demux *demux = dvbdmxfeed->demux;
	काष्ठा stdemux *stdemux = (काष्ठा stdemux *)demux->priv;
	काष्ठा c8sectpfei *fei = stdemux->c8sectpfei;
	काष्ठा channel_info *channel;
	u32 पंचांगp;
	अचिन्हित दीर्घ *biपंचांगap;
	पूर्णांक ret;

	चयन (dvbdmxfeed->type) अणु
	हाल DMX_TYPE_TS:
		अवरोध;
	हाल DMX_TYPE_SEC:
		अवरोध;
	शेष:
		dev_err(fei->dev, "%s:%d Error bailing\n"
			, __func__, __LINE__);
		वापस -EINVAL;
	पूर्ण

	अगर (dvbdmxfeed->type == DMX_TYPE_TS) अणु
		चयन (dvbdmxfeed->pes_type) अणु
		हाल DMX_PES_VIDEO:
		हाल DMX_PES_AUDIO:
		हाल DMX_PES_TELETEXT:
		हाल DMX_PES_PCR:
		हाल DMX_PES_OTHER:
			अवरोध;
		शेष:
			dev_err(fei->dev, "%s:%d Error bailing\n"
				, __func__, __LINE__);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!atomic_पढ़ो(&fei->fw_loaded)) अणु
		ret = load_c8sectpfe_fw(fei);
		अगर (ret)
			वापस ret;
	पूर्ण

	mutex_lock(&fei->lock);

	channel = fei->channel_data[stdemux->tsin_index];

	biपंचांगap = (अचिन्हित दीर्घ *) channel->pid_buffer_aligned;

	/* 8192 is a special PID */
	अगर (dvbdmxfeed->pid == 8192) अणु
		पंचांगp = पढ़ोl(fei->io + C8SECTPFE_IB_PID_SET(channel->tsin_id));
		पंचांगp &= ~C8SECTPFE_PID_ENABLE;
		ग_लिखोl(पंचांगp, fei->io + C8SECTPFE_IB_PID_SET(channel->tsin_id));

	पूर्ण अन्यथा अणु
		biपंचांगap_set(biपंचांगap, dvbdmxfeed->pid, 1);
	पूर्ण

	/* manage cache so PID biपंचांगap is visible to HW */
	dma_sync_single_क्रम_device(fei->dev,
					channel->pid_buffer_busaddr,
					PID_TABLE_SIZE,
					DMA_TO_DEVICE);

	channel->active = 1;

	अगर (fei->global_feed_count == 0) अणु
		fei->समयr.expires = jअगरfies +
			msecs_to_jअगरfies(msecs_to_jअगरfies(POLL_MSECS));

		add_समयr(&fei->समयr);
	पूर्ण

	अगर (stdemux->running_feed_count == 0) अणु

		dev_dbg(fei->dev, "Starting channel=%p\n", channel);

		tasklet_setup(&channel->tsklet, channel_swdemux_tsklet);

		/* Reset the पूर्णांकernal inputblock sram poपूर्णांकers */
		ग_लिखोl(channel->fअगरo,
			fei->io + C8SECTPFE_IB_BUFF_STRT(channel->tsin_id));
		ग_लिखोl(channel->fअगरo + FIFO_LEN - 1,
			fei->io + C8SECTPFE_IB_BUFF_END(channel->tsin_id));

		ग_लिखोl(channel->fअगरo,
			fei->io + C8SECTPFE_IB_READ_PNT(channel->tsin_id));
		ग_लिखोl(channel->fअगरo,
			fei->io + C8SECTPFE_IB_WRT_PNT(channel->tsin_id));


		/* reset पढ़ो / ग_लिखो memdma ptrs क्रम this channel */
		ग_लिखोl(channel->back_buffer_busaddr, channel->irec +
			DMA_PRDS_BUSBASE_TP(0));

		पंचांगp = channel->back_buffer_busaddr + FEI_BUFFER_SIZE - 1;
		ग_लिखोl(पंचांगp, channel->irec + DMA_PRDS_BUSTOP_TP(0));

		ग_लिखोl(channel->back_buffer_busaddr, channel->irec +
			DMA_PRDS_BUSWP_TP(0));

		/* Issue a reset and enable InputBlock */
		ग_लिखोl(C8SECTPFE_SYS_ENABLE | C8SECTPFE_SYS_RESET
			, fei->io + C8SECTPFE_IB_SYS(channel->tsin_id));

		/* and enable the tp */
		ग_लिखोl(0x1, channel->irec + DMA_PRDS_TPENABLE);

		dev_dbg(fei->dev, "%s:%d Starting DMA feed on stdemux=%p\n"
			, __func__, __LINE__, stdemux);
	पूर्ण

	stdemux->running_feed_count++;
	fei->global_feed_count++;

	mutex_unlock(&fei->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक c8sectpfe_stop_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु

	काष्ठा dvb_demux *demux = dvbdmxfeed->demux;
	काष्ठा stdemux *stdemux = (काष्ठा stdemux *)demux->priv;
	काष्ठा c8sectpfei *fei = stdemux->c8sectpfei;
	काष्ठा channel_info *channel;
	पूर्णांक idlereq;
	u32 पंचांगp;
	पूर्णांक ret;
	अचिन्हित दीर्घ *biपंचांगap;

	अगर (!atomic_पढ़ो(&fei->fw_loaded)) अणु
		ret = load_c8sectpfe_fw(fei);
		अगर (ret)
			वापस ret;
	पूर्ण

	mutex_lock(&fei->lock);

	channel = fei->channel_data[stdemux->tsin_index];

	biपंचांगap = (अचिन्हित दीर्घ *) channel->pid_buffer_aligned;

	अगर (dvbdmxfeed->pid == 8192) अणु
		पंचांगp = पढ़ोl(fei->io + C8SECTPFE_IB_PID_SET(channel->tsin_id));
		पंचांगp |= C8SECTPFE_PID_ENABLE;
		ग_लिखोl(पंचांगp, fei->io + C8SECTPFE_IB_PID_SET(channel->tsin_id));
	पूर्ण अन्यथा अणु
		biपंचांगap_clear(biपंचांगap, dvbdmxfeed->pid, 1);
	पूर्ण

	/* manage cache so data is visible to HW */
	dma_sync_single_क्रम_device(fei->dev,
					channel->pid_buffer_busaddr,
					PID_TABLE_SIZE,
					DMA_TO_DEVICE);

	अगर (--stdemux->running_feed_count == 0) अणु

		channel = fei->channel_data[stdemux->tsin_index];

		/* TP re-configuration on page 168 of functional spec */

		/* disable IB (prevents more TS data going to memdma) */
		ग_लिखोl(0, fei->io + C8SECTPFE_IB_SYS(channel->tsin_id));

		/* disable this channels descriptor */
		ग_लिखोl(0,  channel->irec + DMA_PRDS_TPENABLE);

		tasklet_disable(&channel->tsklet);

		/* now request memdma channel goes idle */
		idlereq = (1 << channel->tsin_id) | IDLEREQ;
		ग_लिखोl(idlereq, fei->io + DMA_IDLE_REQ);

		/* रुको क्रम idle irq handler to संकेत completion */
		ret = रुको_क्रम_completion_समयout(&channel->idle_completion,
						msecs_to_jअगरfies(100));

		अगर (ret == 0)
			dev_warn(fei->dev,
				"Timeout waiting for idle irq on tsin%d\n",
				channel->tsin_id);

		reinit_completion(&channel->idle_completion);

		/* reset पढ़ो / ग_लिखो ptrs क्रम this channel */

		ग_लिखोl(channel->back_buffer_busaddr,
			channel->irec + DMA_PRDS_BUSBASE_TP(0));

		पंचांगp = channel->back_buffer_busaddr + FEI_BUFFER_SIZE - 1;
		ग_लिखोl(पंचांगp, channel->irec + DMA_PRDS_BUSTOP_TP(0));

		ग_लिखोl(channel->back_buffer_busaddr,
			channel->irec + DMA_PRDS_BUSWP_TP(0));

		dev_dbg(fei->dev,
			"%s:%d stopping DMA feed on stdemux=%p channel=%d\n",
			__func__, __LINE__, stdemux, channel->tsin_id);

		/* turn off all PIDS in the biपंचांगap */
		स_रखो((व्योम *)channel->pid_buffer_aligned
			, 0x00, PID_TABLE_SIZE);

		/* manage cache so data is visible to HW */
		dma_sync_single_क्रम_device(fei->dev,
					channel->pid_buffer_busaddr,
					PID_TABLE_SIZE,
					DMA_TO_DEVICE);

		channel->active = 0;
	पूर्ण

	अगर (--fei->global_feed_count == 0) अणु
		dev_dbg(fei->dev, "%s:%d global_feed_count=%d\n"
			, __func__, __LINE__, fei->global_feed_count);

		del_समयr(&fei->समयr);
	पूर्ण

	mutex_unlock(&fei->lock);

	वापस 0;
पूर्ण

अटल काष्ठा channel_info *find_channel(काष्ठा c8sectpfei *fei, पूर्णांक tsin_num)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < C8SECTPFE_MAX_TSIN_CHAN; i++) अणु
		अगर (!fei->channel_data[i])
			जारी;

		अगर (fei->channel_data[i]->tsin_id == tsin_num)
			वापस fei->channel_data[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम c8sectpfe_अ_लोonfig(काष्ठा c8sectpfei *fei)
अणु
	काष्ठा c8sectpfe_hw *hw = &fei->hw_stats;

	hw->num_ib = पढ़ोl(fei->io + SYS_CFG_NUM_IB);
	hw->num_mib = पढ़ोl(fei->io + SYS_CFG_NUM_MIB);
	hw->num_swts = पढ़ोl(fei->io + SYS_CFG_NUM_SWTS);
	hw->num_tsout = पढ़ोl(fei->io + SYS_CFG_NUM_TSOUT);
	hw->num_ccsc = पढ़ोl(fei->io + SYS_CFG_NUM_CCSC);
	hw->num_ram = पढ़ोl(fei->io + SYS_CFG_NUM_RAM);
	hw->num_tp = पढ़ोl(fei->io + SYS_CFG_NUM_TP);

	dev_info(fei->dev, "C8SECTPFE hw supports the following:\n");
	dev_info(fei->dev, "Input Blocks: %d\n", hw->num_ib);
	dev_info(fei->dev, "Merged Input Blocks: %d\n", hw->num_mib);
	dev_info(fei->dev, "Software Transport Stream Inputs: %d\n"
				, hw->num_swts);
	dev_info(fei->dev, "Transport Stream Output: %d\n", hw->num_tsout);
	dev_info(fei->dev, "Cable Card Converter: %d\n", hw->num_ccsc);
	dev_info(fei->dev, "RAMs supported by C8SECTPFE: %d\n", hw->num_ram);
	dev_info(fei->dev, "Tango TPs supported by C8SECTPFE: %d\n"
			, hw->num_tp);
पूर्ण

अटल irqवापस_t c8sectpfe_idle_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा c8sectpfei *fei = priv;
	काष्ठा channel_info *chan;
	पूर्णांक bit;
	अचिन्हित दीर्घ पंचांगp = पढ़ोl(fei->io + DMA_IDLE_REQ);

	/* page 168 of functional spec: Clear the idle request
	   by writing 0 to the C8SECTPFE_DMA_IDLE_REQ रेजिस्टर. */

	/* संकेत idle completion */
	क्रम_each_set_bit(bit, &पंचांगp, fei->hw_stats.num_ib) अणु

		chan = find_channel(fei, bit);

		अगर (chan)
			complete(&chan->idle_completion);
	पूर्ण

	ग_लिखोl(0, fei->io + DMA_IDLE_REQ);

	वापस IRQ_HANDLED;
पूर्ण


अटल व्योम मुक्त_input_block(काष्ठा c8sectpfei *fei, काष्ठा channel_info *tsin)
अणु
	अगर (!fei || !tsin)
		वापस;

	अगर (tsin->back_buffer_busaddr)
		अगर (!dma_mapping_error(fei->dev, tsin->back_buffer_busaddr))
			dma_unmap_single(fei->dev, tsin->back_buffer_busaddr,
				FEI_BUFFER_SIZE, DMA_BIसूचीECTIONAL);

	kमुक्त(tsin->back_buffer_start);

	अगर (tsin->pid_buffer_busaddr)
		अगर (!dma_mapping_error(fei->dev, tsin->pid_buffer_busaddr))
			dma_unmap_single(fei->dev, tsin->pid_buffer_busaddr,
				PID_TABLE_SIZE, DMA_BIसूचीECTIONAL);

	kमुक्त(tsin->pid_buffer_start);
पूर्ण

#घोषणा MAX_NAME 20

अटल पूर्णांक configure_memdma_and_inputblock(काष्ठा c8sectpfei *fei,
				काष्ठा channel_info *tsin)
अणु
	पूर्णांक ret;
	u32 पंचांगp;
	अक्षर tsin_pin_name[MAX_NAME];

	अगर (!fei || !tsin)
		वापस -EINVAL;

	dev_dbg(fei->dev, "%s:%d Configuring channel=%p tsin=%d\n"
		, __func__, __LINE__, tsin, tsin->tsin_id);

	init_completion(&tsin->idle_completion);

	tsin->back_buffer_start = kzalloc(FEI_BUFFER_SIZE +
					FEI_ALIGNMENT, GFP_KERNEL);

	अगर (!tsin->back_buffer_start) अणु
		ret = -ENOMEM;
		जाओ err_unmap;
	पूर्ण

	/* Ensure backbuffer is 32byte aligned */
	tsin->back_buffer_aligned = tsin->back_buffer_start
		+ FEI_ALIGNMENT;

	tsin->back_buffer_aligned = (व्योम *)
		(((uपूर्णांकptr_t) tsin->back_buffer_aligned) & ~0x1F);

	tsin->back_buffer_busaddr = dma_map_single(fei->dev,
					(व्योम *)tsin->back_buffer_aligned,
					FEI_BUFFER_SIZE,
					DMA_BIसूचीECTIONAL);

	अगर (dma_mapping_error(fei->dev, tsin->back_buffer_busaddr)) अणु
		dev_err(fei->dev, "failed to map back_buffer\n");
		ret = -EFAULT;
		जाओ err_unmap;
	पूर्ण

	/*
	 * The pid buffer can be configured (in hw) क्रम byte or bit
	 * per pid. By घातers of deduction we conclude stih407 family
	 * is configured (at SoC design stage) क्रम bit per pid.
	 */
	tsin->pid_buffer_start = kzalloc(2048, GFP_KERNEL);

	अगर (!tsin->pid_buffer_start) अणु
		ret = -ENOMEM;
		जाओ err_unmap;
	पूर्ण

	/*
	 * PID buffer needs to be aligned to size of the pid table
	 * which at bit per pid is 1024 bytes (8192 pids / 8).
	 * PIDF_BASE रेजिस्टर enक्रमces this alignment when writing
	 * the रेजिस्टर.
	 */

	tsin->pid_buffer_aligned = tsin->pid_buffer_start +
		PID_TABLE_SIZE;

	tsin->pid_buffer_aligned = (व्योम *)
		(((uपूर्णांकptr_t) tsin->pid_buffer_aligned) & ~0x3ff);

	tsin->pid_buffer_busaddr = dma_map_single(fei->dev,
						tsin->pid_buffer_aligned,
						PID_TABLE_SIZE,
						DMA_BIसूचीECTIONAL);

	अगर (dma_mapping_error(fei->dev, tsin->pid_buffer_busaddr)) अणु
		dev_err(fei->dev, "failed to map pid_bitmap\n");
		ret = -EFAULT;
		जाओ err_unmap;
	पूर्ण

	/* manage cache so pid biपंचांगap is visible to HW */
	dma_sync_single_क्रम_device(fei->dev,
				tsin->pid_buffer_busaddr,
				PID_TABLE_SIZE,
				DMA_TO_DEVICE);

	snम_लिखो(tsin_pin_name, MAX_NAME, "tsin%d-%s", tsin->tsin_id,
		(tsin->serial_not_parallel ? "serial" : "parallel"));

	tsin->pstate = pinctrl_lookup_state(fei->pinctrl, tsin_pin_name);
	अगर (IS_ERR(tsin->pstate)) अणु
		dev_err(fei->dev, "%s: pinctrl_lookup_state couldn't find %s state\n"
			, __func__, tsin_pin_name);
		ret = PTR_ERR(tsin->pstate);
		जाओ err_unmap;
	पूर्ण

	ret = pinctrl_select_state(fei->pinctrl, tsin->pstate);

	अगर (ret) अणु
		dev_err(fei->dev, "%s: pinctrl_select_state failed\n"
			, __func__);
		जाओ err_unmap;
	पूर्ण

	/* Enable this input block */
	पंचांगp = पढ़ोl(fei->io + SYS_INPUT_CLKEN);
	पंचांगp |= BIT(tsin->tsin_id);
	ग_लिखोl(पंचांगp, fei->io + SYS_INPUT_CLKEN);

	अगर (tsin->serial_not_parallel)
		पंचांगp |= C8SECTPFE_SERIAL_NOT_PARALLEL;

	अगर (tsin->invert_ts_clk)
		पंचांगp |= C8SECTPFE_INVERT_TSCLK;

	अगर (tsin->async_not_sync)
		पंचांगp |= C8SECTPFE_ASYNC_NOT_SYNC;

	पंचांगp |= C8SECTPFE_ALIGN_BYTE_SOP | C8SECTPFE_BYTE_ENDIANNESS_MSB;

	ग_लिखोl(पंचांगp, fei->io + C8SECTPFE_IB_IP_FMT_CFG(tsin->tsin_id));

	ग_लिखोl(C8SECTPFE_SYNC(0x9) |
		C8SECTPFE_DROP(0x9) |
		C8SECTPFE_TOKEN(0x47),
		fei->io + C8SECTPFE_IB_SYNCLCKDRP_CFG(tsin->tsin_id));

	ग_लिखोl(TS_PKT_SIZE, fei->io + C8SECTPFE_IB_PKT_LEN(tsin->tsin_id));

	/* Place the FIFO's at the end of the irec descriptors */

	tsin->fअगरo = (tsin->tsin_id * FIFO_LEN);

	ग_लिखोl(tsin->fअगरo, fei->io + C8SECTPFE_IB_BUFF_STRT(tsin->tsin_id));
	ग_लिखोl(tsin->fअगरo + FIFO_LEN - 1,
		fei->io + C8SECTPFE_IB_BUFF_END(tsin->tsin_id));

	ग_लिखोl(tsin->fअगरo, fei->io + C8SECTPFE_IB_READ_PNT(tsin->tsin_id));
	ग_लिखोl(tsin->fअगरo, fei->io + C8SECTPFE_IB_WRT_PNT(tsin->tsin_id));

	ग_लिखोl(tsin->pid_buffer_busaddr,
		fei->io + PIDF_BASE(tsin->tsin_id));

	dev_dbg(fei->dev, "chan=%d PIDF_BASE=0x%x pid_bus_addr=%pad\n",
		tsin->tsin_id, पढ़ोl(fei->io + PIDF_BASE(tsin->tsin_id)),
		&tsin->pid_buffer_busaddr);

	/* Configure and enable HW PID filtering */

	/*
	 * The PID value is created by assembling the first 8 bytes of
	 * the TS packet पूर्णांकo a 64-bit word in big-endian क्रमmat. A
	 * slice of that 64-bit word is taken from
	 * (PID_OFFSET+PID_NUM_BITS-1) to PID_OFFSET.
	 */
	पंचांगp = (C8SECTPFE_PID_ENABLE | C8SECTPFE_PID_NUMBITS(13)
		| C8SECTPFE_PID_OFFSET(40));

	ग_लिखोl(पंचांगp, fei->io + C8SECTPFE_IB_PID_SET(tsin->tsin_id));

	dev_dbg(fei->dev, "chan=%d setting wp: %d, rp: %d, buf: %d-%d\n",
		tsin->tsin_id,
		पढ़ोl(fei->io + C8SECTPFE_IB_WRT_PNT(tsin->tsin_id)),
		पढ़ोl(fei->io + C8SECTPFE_IB_READ_PNT(tsin->tsin_id)),
		पढ़ोl(fei->io + C8SECTPFE_IB_BUFF_STRT(tsin->tsin_id)),
		पढ़ोl(fei->io + C8SECTPFE_IB_BUFF_END(tsin->tsin_id)));

	/* Get base addpress of poपूर्णांकer record block from DMEM */
	tsin->irec = fei->io + DMA_MEMDMA_OFFSET + DMA_DMEM_OFFSET +
			पढ़ोl(fei->io + DMA_PTRREC_BASE);

	/* fill out poपूर्णांकer record data काष्ठाure */

	/* advance poपूर्णांकer record block to our channel */
	tsin->irec += (tsin->tsin_id * DMA_PRDS_SIZE);

	ग_लिखोl(tsin->fअगरo, tsin->irec + DMA_PRDS_MEMBASE);

	ग_लिखोl(tsin->fअगरo + FIFO_LEN - 1, tsin->irec + DMA_PRDS_MEMTOP);

	ग_लिखोl((188 + 7)&~7, tsin->irec + DMA_PRDS_PKTSIZE);

	ग_लिखोl(0x1, tsin->irec + DMA_PRDS_TPENABLE);

	/* पढ़ो/ग_लिखो poपूर्णांकers with physical bus address */

	ग_लिखोl(tsin->back_buffer_busaddr, tsin->irec + DMA_PRDS_BUSBASE_TP(0));

	पंचांगp = tsin->back_buffer_busaddr + FEI_BUFFER_SIZE - 1;
	ग_लिखोl(पंचांगp, tsin->irec + DMA_PRDS_BUSTOP_TP(0));

	ग_लिखोl(tsin->back_buffer_busaddr, tsin->irec + DMA_PRDS_BUSWP_TP(0));
	ग_लिखोl(tsin->back_buffer_busaddr, tsin->irec + DMA_PRDS_BUSRP_TP(0));

	/* initialize tasklet */
	tasklet_setup(&tsin->tsklet, channel_swdemux_tsklet);

	वापस 0;

err_unmap:
	मुक्त_input_block(fei, tsin);
	वापस ret;
पूर्ण

अटल irqवापस_t c8sectpfe_error_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा c8sectpfei *fei = priv;

	dev_err(fei->dev, "%s: error handling not yet implemented\n"
		, __func__);

	/*
	 * TODO FIXME we should detect some error conditions here
	 * and ideally करो something about them!
	 */

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक c8sectpfe_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *child, *np = dev->of_node;
	काष्ठा c8sectpfei *fei;
	काष्ठा resource *res;
	पूर्णांक ret, index = 0;
	काष्ठा channel_info *tsin;

	/* Allocate the c8sectpfei काष्ठाure */
	fei = devm_kzalloc(dev, माप(काष्ठा c8sectpfei), GFP_KERNEL);
	अगर (!fei)
		वापस -ENOMEM;

	fei->dev = dev;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "c8sectpfe");
	fei->io = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(fei->io))
		वापस PTR_ERR(fei->io);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
					"c8sectpfe-ram");
	fei->sram = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(fei->sram))
		वापस PTR_ERR(fei->sram);

	fei->sram_size = resource_size(res);

	fei->idle_irq = platक्रमm_get_irq_byname(pdev, "c8sectpfe-idle-irq");
	अगर (fei->idle_irq < 0)
		वापस fei->idle_irq;

	fei->error_irq = platक्रमm_get_irq_byname(pdev, "c8sectpfe-error-irq");
	अगर (fei->error_irq < 0)
		वापस fei->error_irq;

	platक्रमm_set_drvdata(pdev, fei);

	fei->c8sectpfeclk = devm_clk_get(dev, "c8sectpfe");
	अगर (IS_ERR(fei->c8sectpfeclk)) अणु
		dev_err(dev, "c8sectpfe clk not found\n");
		वापस PTR_ERR(fei->c8sectpfeclk);
	पूर्ण

	ret = clk_prepare_enable(fei->c8sectpfeclk);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable c8sectpfe clock\n");
		वापस ret;
	पूर्ण

	/* to save घातer disable all IP's (on by शेष) */
	ग_लिखोl(0, fei->io + SYS_INPUT_CLKEN);

	/* Enable memdma घड़ी */
	ग_लिखोl(MEMDMAENABLE, fei->io + SYS_OTHER_CLKEN);

	/* clear पूर्णांकernal sram */
	स_रखो_io(fei->sram, 0x0, fei->sram_size);

	c8sectpfe_अ_लोonfig(fei);

	ret = devm_request_irq(dev, fei->idle_irq, c8sectpfe_idle_irq_handler,
			0, "c8sectpfe-idle-irq", fei);
	अगर (ret) अणु
		dev_err(dev, "Can't register c8sectpfe-idle-irq IRQ.\n");
		जाओ err_clk_disable;
	पूर्ण

	ret = devm_request_irq(dev, fei->error_irq,
				c8sectpfe_error_irq_handler, 0,
				"c8sectpfe-error-irq", fei);
	अगर (ret) अणु
		dev_err(dev, "Can't register c8sectpfe-error-irq IRQ.\n");
		जाओ err_clk_disable;
	पूर्ण

	fei->tsin_count = of_get_child_count(np);

	अगर (fei->tsin_count > C8SECTPFE_MAX_TSIN_CHAN ||
		fei->tsin_count > fei->hw_stats.num_ib) अणु

		dev_err(dev, "More tsin declared than exist on SoC!\n");
		ret = -EINVAL;
		जाओ err_clk_disable;
	पूर्ण

	fei->pinctrl = devm_pinctrl_get(dev);

	अगर (IS_ERR(fei->pinctrl)) अणु
		dev_err(dev, "Error getting tsin pins\n");
		ret = PTR_ERR(fei->pinctrl);
		जाओ err_clk_disable;
	पूर्ण

	क्रम_each_child_of_node(np, child) अणु
		काष्ठा device_node *i2c_bus;

		fei->channel_data[index] = devm_kzalloc(dev,
						माप(काष्ठा channel_info),
						GFP_KERNEL);

		अगर (!fei->channel_data[index]) अणु
			ret = -ENOMEM;
			जाओ err_node_put;
		पूर्ण

		tsin = fei->channel_data[index];

		tsin->fei = fei;

		ret = of_property_पढ़ो_u32(child, "tsin-num", &tsin->tsin_id);
		अगर (ret) अणु
			dev_err(&pdev->dev, "No tsin_num found\n");
			जाओ err_node_put;
		पूर्ण

		/* sanity check value */
		अगर (tsin->tsin_id > fei->hw_stats.num_ib) अणु
			dev_err(&pdev->dev,
				"tsin-num %d specified greater than number\n\tof input block hw in SoC! (%d)",
				tsin->tsin_id, fei->hw_stats.num_ib);
			ret = -EINVAL;
			जाओ err_node_put;
		पूर्ण

		tsin->invert_ts_clk = of_property_पढ़ो_bool(child,
							"invert-ts-clk");

		tsin->serial_not_parallel = of_property_पढ़ो_bool(child,
							"serial-not-parallel");

		tsin->async_not_sync = of_property_पढ़ो_bool(child,
							"async-not-sync");

		ret = of_property_पढ़ो_u32(child, "dvb-card",
					&tsin->dvb_card);
		अगर (ret) अणु
			dev_err(&pdev->dev, "No dvb-card found\n");
			जाओ err_node_put;
		पूर्ण

		i2c_bus = of_parse_phandle(child, "i2c-bus", 0);
		अगर (!i2c_bus) अणु
			dev_err(&pdev->dev, "No i2c-bus found\n");
			ret = -ENODEV;
			जाओ err_node_put;
		पूर्ण
		tsin->i2c_adapter =
			of_find_i2c_adapter_by_node(i2c_bus);
		अगर (!tsin->i2c_adapter) अणु
			dev_err(&pdev->dev, "No i2c adapter found\n");
			of_node_put(i2c_bus);
			ret = -ENODEV;
			जाओ err_node_put;
		पूर्ण
		of_node_put(i2c_bus);

		tsin->rst_gpio = of_get_named_gpio(child, "reset-gpios", 0);

		ret = gpio_is_valid(tsin->rst_gpio);
		अगर (!ret) अणु
			dev_err(dev,
				"reset gpio for tsin%d not valid (gpio=%d)\n",
				tsin->tsin_id, tsin->rst_gpio);
			ret = -EINVAL;
			जाओ err_node_put;
		पूर्ण

		ret = devm_gpio_request_one(dev, tsin->rst_gpio,
					GPIOF_OUT_INIT_LOW, "NIM reset");
		अगर (ret && ret != -EBUSY) अणु
			dev_err(dev, "Can't request tsin%d reset gpio\n"
				, fei->channel_data[index]->tsin_id);
			जाओ err_node_put;
		पूर्ण

		अगर (!ret) अणु
			/* toggle reset lines */
			gpio_direction_output(tsin->rst_gpio, 0);
			usleep_range(3500, 5000);
			gpio_direction_output(tsin->rst_gpio, 1);
			usleep_range(3000, 5000);
		पूर्ण

		tsin->demux_mapping = index;

		dev_dbg(fei->dev,
			"channel=%p n=%d tsin_num=%d, invert-ts-clk=%d\n\tserial-not-parallel=%d pkt-clk-valid=%d dvb-card=%d\n",
			fei->channel_data[index], index,
			tsin->tsin_id, tsin->invert_ts_clk,
			tsin->serial_not_parallel, tsin->async_not_sync,
			tsin->dvb_card);

		index++;
	पूर्ण

	/* Setup समयr पूर्णांकerrupt */
	समयr_setup(&fei->समयr, c8sectpfe_समयr_पूर्णांकerrupt, 0);

	mutex_init(&fei->lock);

	/* Get the configuration inक्रमmation about the tuners */
	ret = c8sectpfe_tuner_रेजिस्टर_frontend(&fei->c8sectpfe[0],
					(व्योम *)fei,
					c8sectpfe_start_feed,
					c8sectpfe_stop_feed);
	अगर (ret) अणु
		dev_err(dev, "c8sectpfe_tuner_register_frontend failed (%d)\n",
			ret);
		जाओ err_clk_disable;
	पूर्ण

	c8sectpfe_debugfs_init(fei);

	वापस 0;

err_node_put:
	of_node_put(child);
err_clk_disable:
	clk_disable_unprepare(fei->c8sectpfeclk);
	वापस ret;
पूर्ण

अटल पूर्णांक c8sectpfe_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा c8sectpfei *fei = platक्रमm_get_drvdata(pdev);
	काष्ठा channel_info *channel;
	पूर्णांक i;

	रुको_क्रम_completion(&fei->fw_ack);

	c8sectpfe_tuner_unरेजिस्टर_frontend(fei->c8sectpfe[0], fei);

	/*
	 * Now loop through and un-configure each of the InputBlock resources
	 */
	क्रम (i = 0; i < fei->tsin_count; i++) अणु
		channel = fei->channel_data[i];
		मुक्त_input_block(fei, channel);
	पूर्ण

	c8sectpfe_debugfs_निकास(fei);

	dev_info(fei->dev, "Stopping memdma SLIM core\n");
	अगर (पढ़ोl(fei->io + DMA_CPU_RUN))
		ग_लिखोl(0x0,  fei->io + DMA_CPU_RUN);

	/* unघड़ी all पूर्णांकernal IP's */
	अगर (पढ़ोl(fei->io + SYS_INPUT_CLKEN))
		ग_लिखोl(0, fei->io + SYS_INPUT_CLKEN);

	अगर (पढ़ोl(fei->io + SYS_OTHER_CLKEN))
		ग_लिखोl(0, fei->io + SYS_OTHER_CLKEN);

	अगर (fei->c8sectpfeclk)
		clk_disable_unprepare(fei->c8sectpfeclk);

	वापस 0;
पूर्ण


अटल पूर्णांक configure_channels(काष्ठा c8sectpfei *fei)
अणु
	पूर्णांक index = 0, ret;
	काष्ठा channel_info *tsin;
	काष्ठा device_node *child, *np = fei->dev->of_node;

	/* iterate round each tsin and configure memdma descriptor and IB hw */
	क्रम_each_child_of_node(np, child) अणु

		tsin = fei->channel_data[index];

		ret = configure_memdma_and_inputblock(fei,
						fei->channel_data[index]);

		अगर (ret) अणु
			dev_err(fei->dev,
				"configure_memdma_and_inputblock failed\n");
			जाओ err_unmap;
		पूर्ण
		index++;
	पूर्ण

	वापस 0;

err_unmap:
	क्रम (index = 0; index < fei->tsin_count; index++) अणु
		tsin = fei->channel_data[index];
		मुक्त_input_block(fei, tsin);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
c8sectpfe_elf_sanity_check(काष्ठा c8sectpfei *fei, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा elf32_hdr *ehdr;
	अक्षर class;

	अगर (!fw) अणु
		dev_err(fei->dev, "failed to load %s\n", FIRMWARE_MEMDMA);
		वापस -EINVAL;
	पूर्ण

	अगर (fw->size < माप(काष्ठा elf32_hdr)) अणु
		dev_err(fei->dev, "Image is too small\n");
		वापस -EINVAL;
	पूर्ण

	ehdr = (काष्ठा elf32_hdr *)fw->data;

	/* We only support ELF32 at this poपूर्णांक */
	class = ehdr->e_ident[EI_CLASS];
	अगर (class != ELFCLASS32) अणु
		dev_err(fei->dev, "Unsupported class: %d\n", class);
		वापस -EINVAL;
	पूर्ण

	अगर (ehdr->e_ident[EI_DATA] != ELFDATA2LSB) अणु
		dev_err(fei->dev, "Unsupported firmware endianness\n");
		वापस -EINVAL;
	पूर्ण

	अगर (fw->size < ehdr->e_shoff + माप(काष्ठा elf32_shdr)) अणु
		dev_err(fei->dev, "Image is too small\n");
		वापस -EINVAL;
	पूर्ण

	अगर (स_भेद(ehdr->e_ident, ELFMAG, SELFMAG)) अणु
		dev_err(fei->dev, "Image is corrupted (bad magic)\n");
		वापस -EINVAL;
	पूर्ण

	/* Check ELF magic */
	ehdr = (Elf32_Ehdr *)fw->data;
	अगर (ehdr->e_ident[EI_MAG0] != ELFMAG0 ||
	    ehdr->e_ident[EI_MAG1] != ELFMAG1 ||
	    ehdr->e_ident[EI_MAG2] != ELFMAG2 ||
	    ehdr->e_ident[EI_MAG3] != ELFMAG3) अणु
		dev_err(fei->dev, "Invalid ELF magic\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ehdr->e_type != ET_EXEC) अणु
		dev_err(fei->dev, "Unsupported ELF header type\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ehdr->e_phoff > fw->size) अणु
		dev_err(fei->dev, "Firmware size is too small\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण


अटल व्योम load_imem_segment(काष्ठा c8sectpfei *fei, Elf32_Phdr *phdr,
			स्थिर काष्ठा firmware *fw, u8 __iomem *dest,
			पूर्णांक seg_num)
अणु
	स्थिर u8 *imem_src = fw->data + phdr->p_offset;
	पूर्णांक i;

	/*
	 * For IMEM segments, the segment contains 24-bit
	 * inकाष्ठाions which must be padded to 32-bit
	 * inकाष्ठाions beक्रमe being written. The written
	 * segment is padded with NOP inकाष्ठाions.
	 */

	dev_dbg(fei->dev,
		"Loading IMEM segment %d 0x%08x\n\t (0x%x bytes) -> 0x%p (0x%x bytes)\n",
		seg_num, phdr->p_paddr, phdr->p_filesz, dest,
		phdr->p_memsz + phdr->p_memsz / 3);

	क्रम (i = 0; i < phdr->p_filesz; i++) अणु

		ग_लिखोb(पढ़ोb((व्योम __iomem *)imem_src), (व्योम __iomem *)dest);

		/* Every 3 bytes, add an additional
		 * padding zero in destination */
		अगर (i % 3 == 2) अणु
			dest++;
			ग_लिखोb(0x00, (व्योम __iomem *)dest);
		पूर्ण

		dest++;
		imem_src++;
	पूर्ण
पूर्ण

अटल व्योम load_dmem_segment(काष्ठा c8sectpfei *fei, Elf32_Phdr *phdr,
			स्थिर काष्ठा firmware *fw, u8 __iomem *dst, पूर्णांक seg_num)
अणु
	/*
	 * For DMEM segments copy the segment data from the ELF
	 * file and pad segment with zeroes
	 */

	dev_dbg(fei->dev,
		"Loading DMEM segment %d 0x%08x\n\t(0x%x bytes) -> 0x%p (0x%x bytes)\n",
		seg_num, phdr->p_paddr, phdr->p_filesz,
		dst, phdr->p_memsz);

	स_नकल((व्योम __क्रमce *)dst, (व्योम *)fw->data + phdr->p_offset,
		phdr->p_filesz);

	स_रखो((व्योम __क्रमce *)dst + phdr->p_filesz, 0,
		phdr->p_memsz - phdr->p_filesz);
पूर्ण

अटल पूर्णांक load_slim_core_fw(स्थिर काष्ठा firmware *fw, काष्ठा c8sectpfei *fei)
अणु
	Elf32_Ehdr *ehdr;
	Elf32_Phdr *phdr;
	u8 __iomem *dst;
	पूर्णांक err = 0, i;

	अगर (!fw || !fei)
		वापस -EINVAL;

	ehdr = (Elf32_Ehdr *)fw->data;
	phdr = (Elf32_Phdr *)(fw->data + ehdr->e_phoff);

	/* go through the available ELF segments */
	क्रम (i = 0; i < ehdr->e_phnum; i++, phdr++) अणु

		/* Only consider LOAD segments */
		अगर (phdr->p_type != PT_LOAD)
			जारी;

		/*
		 * Check segment is contained within the fw->data buffer
		 */
		अगर (phdr->p_offset + phdr->p_filesz > fw->size) अणु
			dev_err(fei->dev,
				"Segment %d is outside of firmware file\n", i);
			err = -EINVAL;
			अवरोध;
		पूर्ण

		/*
		 * MEMDMA IMEM has executable flag set, otherwise load
		 * this segment पूर्णांकo DMEM.
		 *
		 */

		अगर (phdr->p_flags & PF_X) अणु
			dst = (u8 __iomem *) fei->io + DMA_MEMDMA_IMEM;
			/*
			 * The Slim ELF file uses 32-bit word addressing क्रम
			 * load offsets.
			 */
			dst += (phdr->p_paddr & 0xFFFFF) * माप(अचिन्हित पूर्णांक);
			load_imem_segment(fei, phdr, fw, dst, i);
		पूर्ण अन्यथा अणु
			dst = (u8 __iomem *) fei->io + DMA_MEMDMA_DMEM;
			/*
			 * The Slim ELF file uses 32-bit word addressing क्रम
			 * load offsets.
			 */
			dst += (phdr->p_paddr & 0xFFFFF) * माप(अचिन्हित पूर्णांक);
			load_dmem_segment(fei, phdr, fw, dst, i);
		पूर्ण
	पूर्ण

	release_firmware(fw);
	वापस err;
पूर्ण

अटल पूर्णांक load_c8sectpfe_fw(काष्ठा c8sectpfei *fei)
अणु
	स्थिर काष्ठा firmware *fw;
	पूर्णांक err;

	dev_info(fei->dev, "Loading firmware: %s\n", FIRMWARE_MEMDMA);

	err = request_firmware(&fw, FIRMWARE_MEMDMA, fei->dev);
	अगर (err)
		वापस err;

	err = c8sectpfe_elf_sanity_check(fei, fw);
	अगर (err) अणु
		dev_err(fei->dev, "c8sectpfe_elf_sanity_check failed err=(%d)\n"
			, err);
		release_firmware(fw);
		वापस err;
	पूर्ण

	err = load_slim_core_fw(fw, fei);
	अगर (err) अणु
		dev_err(fei->dev, "load_slim_core_fw failed err=(%d)\n", err);
		वापस err;
	पूर्ण

	/* now the firmware is loaded configure the input blocks */
	err = configure_channels(fei);
	अगर (err) अणु
		dev_err(fei->dev, "configure_channels failed err=(%d)\n", err);
		वापस err;
	पूर्ण

	/*
	 * STBus target port can access IMEM and DMEM ports
	 * without रुकोing क्रम CPU
	 */
	ग_लिखोl(0x1, fei->io + DMA_PER_STBUS_SYNC);

	dev_info(fei->dev, "Boot the memdma SLIM core\n");
	ग_लिखोl(0x1,  fei->io + DMA_CPU_RUN);

	atomic_set(&fei->fw_loaded, 1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id c8sectpfe_match[] = अणु
	अणु .compatible = "st,stih407-c8sectpfe" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, c8sectpfe_match);

अटल काष्ठा platक्रमm_driver c8sectpfe_driver = अणु
	.driver = अणु
		.name = "c8sectpfe",
		.of_match_table = of_match_ptr(c8sectpfe_match),
	पूर्ण,
	.probe	= c8sectpfe_probe,
	.हटाओ	= c8sectpfe_हटाओ,
पूर्ण;

module_platक्रमm_driver(c8sectpfe_driver);

MODULE_AUTHOR("Peter Bennett <peter.bennett@st.com>");
MODULE_AUTHOR("Peter Griffin <peter.griffin@linaro.org>");
MODULE_DESCRIPTION("C8SECTPFE STi DVB Driver");
MODULE_LICENSE("GPL");
