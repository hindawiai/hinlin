<शैली गुरु>
/*
 * TI ADC MFD driver
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - https://www.ti.com/
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/iio/machine.h>
#समावेश <linux/iio/driver.h>

#समावेश <linux/mfd/ti_am335x_tscadc.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/kfअगरo_buf.h>

#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>

#घोषणा DMA_BUFFER_SIZE		SZ_2K

काष्ठा tiadc_dma अणु
	काष्ठा dma_slave_config	conf;
	काष्ठा dma_chan		*chan;
	dma_addr_t		addr;
	dma_cookie_t		cookie;
	u8			*buf;
	पूर्णांक			current_period;
	पूर्णांक			period_size;
	u8			fअगरo_thresh;
पूर्ण;

काष्ठा tiadc_device अणु
	काष्ठा ti_tscadc_dev *mfd_tscadc;
	काष्ठा tiadc_dma dma;
	काष्ठा mutex fअगरo1_lock; /* to protect fअगरo access */
	पूर्णांक channels;
	पूर्णांक total_ch_enabled;
	u8 channel_line[8];
	u8 channel_step[8];
	पूर्णांक buffer_en_ch_steps;
	u16 data[8];
	u32 खोलो_delay[8], sample_delay[8], step_avg[8];
पूर्ण;

अटल अचिन्हित पूर्णांक tiadc_पढ़ोl(काष्ठा tiadc_device *adc, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl(adc->mfd_tscadc->tscadc_base + reg);
पूर्ण

अटल व्योम tiadc_ग_लिखोl(काष्ठा tiadc_device *adc, अचिन्हित पूर्णांक reg,
					अचिन्हित पूर्णांक val)
अणु
	ग_लिखोl(val, adc->mfd_tscadc->tscadc_base + reg);
पूर्ण

अटल u32 get_adc_step_mask(काष्ठा tiadc_device *adc_dev)
अणु
	u32 step_en;

	step_en = ((1 << adc_dev->channels) - 1);
	step_en <<= TOTAL_STEPS - adc_dev->channels + 1;
	वापस step_en;
पूर्ण

अटल u32 get_adc_chan_step_mask(काष्ठा tiadc_device *adc_dev,
		काष्ठा iio_chan_spec स्थिर *chan)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(adc_dev->channel_step); i++) अणु
		अगर (chan->channel == adc_dev->channel_line[i]) अणु
			u32 step;

			step = adc_dev->channel_step[i];
			/* +1 क्रम the अक्षरger */
			वापस 1 << (step + 1);
		पूर्ण
	पूर्ण
	WARN_ON(1);
	वापस 0;
पूर्ण

अटल u32 get_adc_step_bit(काष्ठा tiadc_device *adc_dev, पूर्णांक chan)
अणु
	वापस 1 << adc_dev->channel_step[chan];
पूर्ण

अटल व्योम tiadc_step_config(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा tiadc_device *adc_dev = iio_priv(indio_dev);
	काष्ठा device *dev = adc_dev->mfd_tscadc->dev;
	अचिन्हित पूर्णांक stepconfig;
	पूर्णांक i, steps = 0;

	/*
	 * There are 16 configurable steps and 8 analog input
	 * lines available which are shared between Touchscreen and ADC.
	 *
	 * Steps क्रमwards i.e. from 0 towards 16 are used by ADC
	 * depending on number of input lines needed.
	 * Channel would represent which analog input
	 * needs to be given to ADC to digitalize data.
	 */


	क्रम (i = 0; i < adc_dev->channels; i++) अणु
		पूर्णांक chan;

		chan = adc_dev->channel_line[i];

		अगर (adc_dev->step_avg[i] > STEPCONFIG_AVG_16) अणु
			dev_warn(dev, "chan %d step_avg truncating to %d\n",
				 chan, STEPCONFIG_AVG_16);
			adc_dev->step_avg[i] = STEPCONFIG_AVG_16;
		पूर्ण

		अगर (adc_dev->step_avg[i])
			stepconfig =
			STEPCONFIG_AVG(ffs(adc_dev->step_avg[i]) - 1) |
			STEPCONFIG_FIFO1;
		अन्यथा
			stepconfig = STEPCONFIG_FIFO1;

		अगर (iio_buffer_enabled(indio_dev))
			stepconfig |= STEPCONFIG_MODE_SWCNT;

		tiadc_ग_लिखोl(adc_dev, REG_STEPCONFIG(steps),
				stepconfig | STEPCONFIG_INP(chan) |
				STEPCONFIG_INM_ADCREFM |
				STEPCONFIG_RFP_VREFP |
				STEPCONFIG_RFM_VREFN);

		अगर (adc_dev->खोलो_delay[i] > STEPDELAY_OPEN_MASK) अणु
			dev_warn(dev, "chan %d open delay truncating to 0x3FFFF\n",
				 chan);
			adc_dev->खोलो_delay[i] = STEPDELAY_OPEN_MASK;
		पूर्ण

		अगर (adc_dev->sample_delay[i] > 0xFF) अणु
			dev_warn(dev, "chan %d sample delay truncating to 0xFF\n",
				 chan);
			adc_dev->sample_delay[i] = 0xFF;
		पूर्ण

		tiadc_ग_लिखोl(adc_dev, REG_STEPDELAY(steps),
				STEPDELAY_OPEN(adc_dev->खोलो_delay[i]) |
				STEPDELAY_SAMPLE(adc_dev->sample_delay[i]));

		adc_dev->channel_step[i] = steps;
		steps++;
	पूर्ण
पूर्ण

अटल irqवापस_t tiadc_irq_h(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा tiadc_device *adc_dev = iio_priv(indio_dev);
	अचिन्हित पूर्णांक status, config, adc_fsm;
	अचिन्हित लघु count = 0;

	status = tiadc_पढ़ोl(adc_dev, REG_IRQSTATUS);

	/*
	 * ADC and touchscreen share the IRQ line.
	 * FIFO0 पूर्णांकerrupts are used by TSC. Handle FIFO1 IRQs here only
	 */
	अगर (status & IRQENB_FIFO1OVRRUN) अणु
		/* FIFO Overrun. Clear flag. Disable/Enable ADC to recover */
		config = tiadc_पढ़ोl(adc_dev, REG_CTRL);
		config &= ~(CNTRLREG_TSCSSENB);
		tiadc_ग_लिखोl(adc_dev, REG_CTRL, config);
		tiadc_ग_लिखोl(adc_dev, REG_IRQSTATUS, IRQENB_FIFO1OVRRUN
				| IRQENB_FIFO1UNDRFLW | IRQENB_FIFO1THRES);

		/* रुको क्रम idle state.
		 * ADC needs to finish the current conversion
		 * beक्रमe disabling the module
		 */
		करो अणु
			adc_fsm = tiadc_पढ़ोl(adc_dev, REG_ADCFSM);
		पूर्ण जबतक (adc_fsm != 0x10 && count++ < 100);

		tiadc_ग_लिखोl(adc_dev, REG_CTRL, (config | CNTRLREG_TSCSSENB));
		वापस IRQ_HANDLED;
	पूर्ण अन्यथा अगर (status & IRQENB_FIFO1THRES) अणु
		/* Disable irq and wake worker thपढ़ो */
		tiadc_ग_लिखोl(adc_dev, REG_IRQCLR, IRQENB_FIFO1THRES);
		वापस IRQ_WAKE_THREAD;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल irqवापस_t tiadc_worker_h(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा tiadc_device *adc_dev = iio_priv(indio_dev);
	पूर्णांक i, k, fअगरo1count, पढ़ो;
	u16 *data = adc_dev->data;

	fअगरo1count = tiadc_पढ़ोl(adc_dev, REG_FIFO1CNT);
	क्रम (k = 0; k < fअगरo1count; k = k + i) अणु
		क्रम (i = 0; i < (indio_dev->scan_bytes)/2; i++) अणु
			पढ़ो = tiadc_पढ़ोl(adc_dev, REG_FIFO1);
			data[i] = पढ़ो & FIFOREAD_DATA_MASK;
		पूर्ण
		iio_push_to_buffers(indio_dev, (u8 *) data);
	पूर्ण

	tiadc_ग_लिखोl(adc_dev, REG_IRQSTATUS, IRQENB_FIFO1THRES);
	tiadc_ग_लिखोl(adc_dev, REG_IRQENABLE, IRQENB_FIFO1THRES);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम tiadc_dma_rx_complete(व्योम *param)
अणु
	काष्ठा iio_dev *indio_dev = param;
	काष्ठा tiadc_device *adc_dev = iio_priv(indio_dev);
	काष्ठा tiadc_dma *dma = &adc_dev->dma;
	u8 *data;
	पूर्णांक i;

	data = dma->buf + dma->current_period * dma->period_size;
	dma->current_period = 1 - dma->current_period; /* swap the buffer ID */

	क्रम (i = 0; i < dma->period_size; i += indio_dev->scan_bytes) अणु
		iio_push_to_buffers(indio_dev, data);
		data += indio_dev->scan_bytes;
	पूर्ण
पूर्ण

अटल पूर्णांक tiadc_start_dma(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा tiadc_device *adc_dev = iio_priv(indio_dev);
	काष्ठा tiadc_dma *dma = &adc_dev->dma;
	काष्ठा dma_async_tx_descriptor *desc;

	dma->current_period = 0; /* We start to fill period 0 */
	/*
	 * Make the fअगरo thresh as the multiple of total number of
	 * channels enabled, so make sure that cyclic DMA period
	 * length is also a multiple of total number of channels
	 * enabled. This ensures that no invalid data is reported
	 * to the stack via iio_push_to_buffers().
	 */
	dma->fअगरo_thresh = roundकरोwn(FIFO1_THRESHOLD + 1,
				     adc_dev->total_ch_enabled) - 1;
	/* Make sure that period length is multiple of fअगरo thresh level */
	dma->period_size = roundकरोwn(DMA_BUFFER_SIZE / 2,
				    (dma->fअगरo_thresh + 1) * माप(u16));

	dma->conf.src_maxburst = dma->fअगरo_thresh + 1;
	dmaengine_slave_config(dma->chan, &dma->conf);

	desc = dmaengine_prep_dma_cyclic(dma->chan, dma->addr,
					 dma->period_size * 2,
					 dma->period_size, DMA_DEV_TO_MEM,
					 DMA_PREP_INTERRUPT);
	अगर (!desc)
		वापस -EBUSY;

	desc->callback = tiadc_dma_rx_complete;
	desc->callback_param = indio_dev;

	dma->cookie = dmaengine_submit(desc);

	dma_async_issue_pending(dma->chan);

	tiadc_ग_लिखोl(adc_dev, REG_FIFO1THR, dma->fअगरo_thresh);
	tiadc_ग_लिखोl(adc_dev, REG_DMA1REQ, dma->fअगरo_thresh);
	tiadc_ग_लिखोl(adc_dev, REG_DMAENABLE_SET, DMA_FIFO1);

	वापस 0;
पूर्ण

अटल पूर्णांक tiadc_buffer_preenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा tiadc_device *adc_dev = iio_priv(indio_dev);
	पूर्णांक i, fअगरo1count;

	tiadc_ग_लिखोl(adc_dev, REG_IRQCLR, (IRQENB_FIFO1THRES |
				IRQENB_FIFO1OVRRUN |
				IRQENB_FIFO1UNDRFLW));

	/* Flush FIFO. Needed in corner हालs in simultaneous tsc/adc use */
	fअगरo1count = tiadc_पढ़ोl(adc_dev, REG_FIFO1CNT);
	क्रम (i = 0; i < fअगरo1count; i++)
		tiadc_पढ़ोl(adc_dev, REG_FIFO1);

	वापस 0;
पूर्ण

अटल पूर्णांक tiadc_buffer_postenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा tiadc_device *adc_dev = iio_priv(indio_dev);
	काष्ठा tiadc_dma *dma = &adc_dev->dma;
	अचिन्हित पूर्णांक irq_enable;
	अचिन्हित पूर्णांक enb = 0;
	u8 bit;

	tiadc_step_config(indio_dev);
	क्रम_each_set_bit(bit, indio_dev->active_scan_mask, adc_dev->channels) अणु
		enb |= (get_adc_step_bit(adc_dev, bit) << 1);
		adc_dev->total_ch_enabled++;
	पूर्ण
	adc_dev->buffer_en_ch_steps = enb;

	अगर (dma->chan)
		tiadc_start_dma(indio_dev);

	am335x_tsc_se_set_cache(adc_dev->mfd_tscadc, enb);

	tiadc_ग_लिखोl(adc_dev,  REG_IRQSTATUS, IRQENB_FIFO1THRES
				| IRQENB_FIFO1OVRRUN | IRQENB_FIFO1UNDRFLW);

	irq_enable = IRQENB_FIFO1OVRRUN;
	अगर (!dma->chan)
		irq_enable |= IRQENB_FIFO1THRES;
	tiadc_ग_लिखोl(adc_dev,  REG_IRQENABLE, irq_enable);

	वापस 0;
पूर्ण

अटल पूर्णांक tiadc_buffer_predisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा tiadc_device *adc_dev = iio_priv(indio_dev);
	काष्ठा tiadc_dma *dma = &adc_dev->dma;
	पूर्णांक fअगरo1count, i;

	tiadc_ग_लिखोl(adc_dev, REG_IRQCLR, (IRQENB_FIFO1THRES |
				IRQENB_FIFO1OVRRUN | IRQENB_FIFO1UNDRFLW));
	am335x_tsc_se_clr(adc_dev->mfd_tscadc, adc_dev->buffer_en_ch_steps);
	adc_dev->buffer_en_ch_steps = 0;
	adc_dev->total_ch_enabled = 0;
	अगर (dma->chan) अणु
		tiadc_ग_लिखोl(adc_dev, REG_DMAENABLE_CLEAR, 0x2);
		dmaengine_terminate_async(dma->chan);
	पूर्ण

	/* Flush FIFO of leftover data in the समय it takes to disable adc */
	fअगरo1count = tiadc_पढ़ोl(adc_dev, REG_FIFO1CNT);
	क्रम (i = 0; i < fअगरo1count; i++)
		tiadc_पढ़ोl(adc_dev, REG_FIFO1);

	वापस 0;
पूर्ण

अटल पूर्णांक tiadc_buffer_postdisable(काष्ठा iio_dev *indio_dev)
अणु
	tiadc_step_config(indio_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops tiadc_buffer_setup_ops = अणु
	.preenable = &tiadc_buffer_preenable,
	.postenable = &tiadc_buffer_postenable,
	.predisable = &tiadc_buffer_predisable,
	.postdisable = &tiadc_buffer_postdisable,
पूर्ण;

अटल पूर्णांक tiadc_iio_buffered_hardware_setup(काष्ठा device *dev,
	काष्ठा iio_dev *indio_dev,
	irqवापस_t (*pollfunc_bh)(पूर्णांक irq, व्योम *p),
	irqवापस_t (*pollfunc_th)(पूर्णांक irq, व्योम *p),
	पूर्णांक irq,
	अचिन्हित दीर्घ flags,
	स्थिर काष्ठा iio_buffer_setup_ops *setup_ops)
अणु
	पूर्णांक ret;

	ret = devm_iio_kfअगरo_buffer_setup(dev, indio_dev,
					  INDIO_BUFFER_SOFTWARE,
					  setup_ops);
	अगर (ret)
		वापस ret;

	वापस devm_request_thपढ़ोed_irq(dev, irq, pollfunc_th, pollfunc_bh,
				flags, indio_dev->name, indio_dev);
पूर्ण

अटल स्थिर अक्षर * स्थिर chan_name_ain[] = अणु
	"AIN0",
	"AIN1",
	"AIN2",
	"AIN3",
	"AIN4",
	"AIN5",
	"AIN6",
	"AIN7",
पूर्ण;

अटल पूर्णांक tiadc_channel_init(काष्ठा device *dev, काष्ठा iio_dev *indio_dev,
			      पूर्णांक channels)
अणु
	काष्ठा tiadc_device *adc_dev = iio_priv(indio_dev);
	काष्ठा iio_chan_spec *chan_array;
	काष्ठा iio_chan_spec *chan;
	पूर्णांक i;

	indio_dev->num_channels = channels;
	chan_array = devm_kसुस्मृति(dev, channels, माप(*chan_array),
				  GFP_KERNEL);
	अगर (chan_array == शून्य)
		वापस -ENOMEM;

	chan = chan_array;
	क्रम (i = 0; i < channels; i++, chan++) अणु

		chan->type = IIO_VOLTAGE;
		chan->indexed = 1;
		chan->channel = adc_dev->channel_line[i];
		chan->info_mask_separate = BIT(IIO_CHAN_INFO_RAW);
		chan->datasheet_name = chan_name_ain[chan->channel];
		chan->scan_index = i;
		chan->scan_type.sign = 'u';
		chan->scan_type.realbits = 12;
		chan->scan_type.storagebits = 16;
	पूर्ण

	indio_dev->channels = chan_array;

	वापस 0;
पूर्ण

अटल पूर्णांक tiadc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
		काष्ठा iio_chan_spec स्थिर *chan,
		पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा tiadc_device *adc_dev = iio_priv(indio_dev);
	पूर्णांक ret = IIO_VAL_INT;
	पूर्णांक i, map_val;
	अचिन्हित पूर्णांक fअगरo1count, पढ़ो, stepid;
	bool found = false;
	u32 step_en;
	अचिन्हित दीर्घ समयout;

	अगर (iio_buffer_enabled(indio_dev))
		वापस -EBUSY;

	step_en = get_adc_chan_step_mask(adc_dev, chan);
	अगर (!step_en)
		वापस -EINVAL;

	mutex_lock(&adc_dev->fअगरo1_lock);
	fअगरo1count = tiadc_पढ़ोl(adc_dev, REG_FIFO1CNT);
	जबतक (fअगरo1count--)
		tiadc_पढ़ोl(adc_dev, REG_FIFO1);

	am335x_tsc_se_set_once(adc_dev->mfd_tscadc, step_en);

	समयout = jअगरfies + msecs_to_jअगरfies
				(IDLE_TIMEOUT * adc_dev->channels);
	/* Wait क्रम Fअगरo threshold पूर्णांकerrupt */
	जबतक (1) अणु
		fअगरo1count = tiadc_पढ़ोl(adc_dev, REG_FIFO1CNT);
		अगर (fअगरo1count)
			अवरोध;

		अगर (समय_after(jअगरfies, समयout)) अणु
			am335x_tsc_se_adc_करोne(adc_dev->mfd_tscadc);
			ret = -EAGAIN;
			जाओ err_unlock;
		पूर्ण
	पूर्ण
	map_val = adc_dev->channel_step[chan->scan_index];

	/*
	 * We check the complete FIFO. We programmed just one entry but in हाल
	 * something went wrong we left empty handed (-EAGAIN previously) and
	 * then the value apeared somehow in the FIFO we would have two entries.
	 * Thereक्रमe we पढ़ो every item and keep only the latest version of the
	 * requested channel.
	 */
	क्रम (i = 0; i < fअगरo1count; i++) अणु
		पढ़ो = tiadc_पढ़ोl(adc_dev, REG_FIFO1);
		stepid = पढ़ो & FIFOREAD_CHNLID_MASK;
		stepid = stepid >> 0x10;

		अगर (stepid == map_val) अणु
			पढ़ो = पढ़ो & FIFOREAD_DATA_MASK;
			found = true;
			*val = (u16) पढ़ो;
		पूर्ण
	पूर्ण
	am335x_tsc_se_adc_करोne(adc_dev->mfd_tscadc);

	अगर (!found)
		ret =  -EBUSY;

err_unlock:
	mutex_unlock(&adc_dev->fअगरo1_lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info tiadc_info = अणु
	.पढ़ो_raw = &tiadc_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक tiadc_request_dma(काष्ठा platक्रमm_device *pdev,
			     काष्ठा tiadc_device *adc_dev)
अणु
	काष्ठा tiadc_dma	*dma = &adc_dev->dma;
	dma_cap_mask_t		mask;

	/* Default slave configuration parameters */
	dma->conf.direction = DMA_DEV_TO_MEM;
	dma->conf.src_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
	dma->conf.src_addr = adc_dev->mfd_tscadc->tscadc_phys_base + REG_FIFO1;

	dma_cap_zero(mask);
	dma_cap_set(DMA_CYCLIC, mask);

	/* Get a channel क्रम RX */
	dma->chan = dma_request_chan(adc_dev->mfd_tscadc->dev, "fifo1");
	अगर (IS_ERR(dma->chan)) अणु
		पूर्णांक ret = PTR_ERR(dma->chan);

		dma->chan = शून्य;
		वापस ret;
	पूर्ण

	/* RX buffer */
	dma->buf = dma_alloc_coherent(dma->chan->device->dev, DMA_BUFFER_SIZE,
				      &dma->addr, GFP_KERNEL);
	अगर (!dma->buf)
		जाओ err;

	वापस 0;
err:
	dma_release_channel(dma->chan);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक tiadc_parse_dt(काष्ठा platक्रमm_device *pdev,
			  काष्ठा tiadc_device *adc_dev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा property *prop;
	स्थिर __be32 *cur;
	पूर्णांक channels = 0;
	u32 val;

	of_property_क्रम_each_u32(node, "ti,adc-channels", prop, cur, val) अणु
		adc_dev->channel_line[channels] = val;

		/* Set Default values क्रम optional DT parameters */
		adc_dev->खोलो_delay[channels] = STEPCONFIG_OPENDLY;
		adc_dev->sample_delay[channels] = STEPCONFIG_SAMPLEDLY;
		adc_dev->step_avg[channels] = 16;

		channels++;
	पूर्ण

	of_property_पढ़ो_u32_array(node, "ti,chan-step-avg",
				   adc_dev->step_avg, channels);
	of_property_पढ़ो_u32_array(node, "ti,chan-step-opendelay",
				   adc_dev->खोलो_delay, channels);
	of_property_पढ़ो_u32_array(node, "ti,chan-step-sampledelay",
				   adc_dev->sample_delay, channels);

	adc_dev->channels = channels;
	वापस 0;
पूर्ण

अटल पूर्णांक tiadc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev		*indio_dev;
	काष्ठा tiadc_device	*adc_dev;
	काष्ठा device_node	*node = pdev->dev.of_node;
	पूर्णांक			err;

	अगर (!node) अणु
		dev_err(&pdev->dev, "Could not find valid DT data.\n");
		वापस -EINVAL;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*adc_dev));
	अगर (indio_dev == शून्य) अणु
		dev_err(&pdev->dev, "failed to allocate iio device\n");
		वापस -ENOMEM;
	पूर्ण
	adc_dev = iio_priv(indio_dev);

	adc_dev->mfd_tscadc = ti_tscadc_dev_get(pdev);
	tiadc_parse_dt(pdev, adc_dev);

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &tiadc_info;

	tiadc_step_config(indio_dev);
	tiadc_ग_लिखोl(adc_dev, REG_FIFO1THR, FIFO1_THRESHOLD);
	mutex_init(&adc_dev->fअगरo1_lock);

	err = tiadc_channel_init(&pdev->dev, indio_dev, adc_dev->channels);
	अगर (err < 0)
		वापस err;

	err = tiadc_iio_buffered_hardware_setup(&pdev->dev, indio_dev,
		&tiadc_worker_h,
		&tiadc_irq_h,
		adc_dev->mfd_tscadc->irq,
		IRQF_SHARED,
		&tiadc_buffer_setup_ops);

	अगर (err)
		जाओ err_मुक्त_channels;

	err = iio_device_रेजिस्टर(indio_dev);
	अगर (err)
		जाओ err_buffer_unरेजिस्टर;

	platक्रमm_set_drvdata(pdev, indio_dev);

	err = tiadc_request_dma(pdev, adc_dev);
	अगर (err && err == -EPROBE_DEFER)
		जाओ err_dma;

	वापस 0;

err_dma:
	iio_device_unरेजिस्टर(indio_dev);
err_buffer_unरेजिस्टर:
err_मुक्त_channels:
	वापस err;
पूर्ण

अटल पूर्णांक tiadc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा tiadc_device *adc_dev = iio_priv(indio_dev);
	काष्ठा tiadc_dma *dma = &adc_dev->dma;
	u32 step_en;

	अगर (dma->chan) अणु
		dma_मुक्त_coherent(dma->chan->device->dev, DMA_BUFFER_SIZE,
				  dma->buf, dma->addr);
		dma_release_channel(dma->chan);
	पूर्ण
	iio_device_unरेजिस्टर(indio_dev);

	step_en = get_adc_step_mask(adc_dev);
	am335x_tsc_se_clr(adc_dev->mfd_tscadc, step_en);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tiadc_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा tiadc_device *adc_dev = iio_priv(indio_dev);
	अचिन्हित पूर्णांक idle;

	idle = tiadc_पढ़ोl(adc_dev, REG_CTRL);
	idle &= ~(CNTRLREG_TSCSSENB);
	tiadc_ग_लिखोl(adc_dev, REG_CTRL, (idle |
			CNTRLREG_POWERDOWN));

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tiadc_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा tiadc_device *adc_dev = iio_priv(indio_dev);
	अचिन्हित पूर्णांक restore;

	/* Make sure ADC is घातered up */
	restore = tiadc_पढ़ोl(adc_dev, REG_CTRL);
	restore &= ~(CNTRLREG_POWERDOWN);
	tiadc_ग_लिखोl(adc_dev, REG_CTRL, restore);

	tiadc_step_config(indio_dev);
	am335x_tsc_se_set_cache(adc_dev->mfd_tscadc,
			adc_dev->buffer_en_ch_steps);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(tiadc_pm_ops, tiadc_suspend, tiadc_resume);

अटल स्थिर काष्ठा of_device_id ti_adc_dt_ids[] = अणु
	अणु .compatible = "ti,am3359-adc", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ti_adc_dt_ids);

अटल काष्ठा platक्रमm_driver tiadc_driver = अणु
	.driver = अणु
		.name   = "TI-am335x-adc",
		.pm	= &tiadc_pm_ops,
		.of_match_table = ti_adc_dt_ids,
	पूर्ण,
	.probe	= tiadc_probe,
	.हटाओ	= tiadc_हटाओ,
पूर्ण;
module_platक्रमm_driver(tiadc_driver);

MODULE_DESCRIPTION("TI ADC controller driver");
MODULE_AUTHOR("Rachna Patil <rachna@ti.com>");
MODULE_LICENSE("GPL");
