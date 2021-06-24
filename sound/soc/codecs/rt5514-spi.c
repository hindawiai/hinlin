<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rt5514-spi.c  --  RT5514 SPI driver
 *
 * Copyright 2015 Realtek Semiconductor Corp.
 * Author: Oder Chiou <oder_chiou@realtek.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/sched.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/clk.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "rt5514-spi.h"

#घोषणा DRV_NAME "rt5514-spi"

अटल काष्ठा spi_device *rt5514_spi;

काष्ठा rt5514_dsp अणु
	काष्ठा device *dev;
	काष्ठा delayed_work copy_work;
	काष्ठा mutex dma_lock;
	काष्ठा snd_pcm_substream *substream;
	अचिन्हित पूर्णांक buf_base, buf_limit, buf_rp;
	माप_प्रकार buf_size, get_size, dma_offset;
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware rt5514_spi_pcm_hardware = अणु
	.info			= SNDRV_PCM_INFO_MMAP |
				  SNDRV_PCM_INFO_MMAP_VALID |
				  SNDRV_PCM_INFO_INTERLEAVED,
	.क्रमmats		= SNDRV_PCM_FMTBIT_S16_LE,
	.period_bytes_min	= PAGE_SIZE,
	.period_bytes_max	= 0x20000 / 8,
	.periods_min		= 8,
	.periods_max		= 8,
	.channels_min		= 1,
	.channels_max		= 1,
	.buffer_bytes_max	= 0x20000,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt5514_spi_dai = अणु
	.name = "rt5514-dsp-cpu-dai",
	.id = 0,
	.capture = अणु
		.stream_name = "DSP Capture",
		.channels_min = 1,
		.channels_max = 1,
		.rates = SNDRV_PCM_RATE_16000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
पूर्ण;

अटल व्योम rt5514_spi_copy_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt5514_dsp *rt5514_dsp =
		container_of(work, काष्ठा rt5514_dsp, copy_work.work);
	काष्ठा snd_pcm_runसमय *runसमय;
	माप_प्रकार period_bytes, truncated_bytes = 0;
	अचिन्हित पूर्णांक cur_wp, reमुख्य_data;
	u8 buf[8];

	mutex_lock(&rt5514_dsp->dma_lock);
	अगर (!rt5514_dsp->substream) अणु
		dev_err(rt5514_dsp->dev, "No pcm substream\n");
		जाओ करोne;
	पूर्ण

	runसमय = rt5514_dsp->substream->runसमय;
	period_bytes = snd_pcm_lib_period_bytes(rt5514_dsp->substream);
	अगर (!period_bytes) अणु
		schedule_delayed_work(&rt5514_dsp->copy_work, 5);
		जाओ करोne;
	पूर्ण

	अगर (rt5514_dsp->buf_size % period_bytes)
		rt5514_dsp->buf_size = (rt5514_dsp->buf_size / period_bytes) *
			period_bytes;

	अगर (rt5514_dsp->get_size >= rt5514_dsp->buf_size) अणु
		rt5514_spi_burst_पढ़ो(RT5514_BUFFER_VOICE_WP, (u8 *)&buf,
			माप(buf));
		cur_wp = buf[0] | buf[1] << 8 | buf[2] << 16 |
					buf[3] << 24;

		अगर (cur_wp >= rt5514_dsp->buf_rp)
			reमुख्य_data = (cur_wp - rt5514_dsp->buf_rp);
		अन्यथा
			reमुख्य_data =
				(rt5514_dsp->buf_limit - rt5514_dsp->buf_rp) +
				(cur_wp - rt5514_dsp->buf_base);

		अगर (reमुख्य_data < period_bytes) अणु
			schedule_delayed_work(&rt5514_dsp->copy_work, 5);
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (rt5514_dsp->buf_rp + period_bytes <= rt5514_dsp->buf_limit) अणु
		rt5514_spi_burst_पढ़ो(rt5514_dsp->buf_rp,
			runसमय->dma_area + rt5514_dsp->dma_offset,
			period_bytes);

		अगर (rt5514_dsp->buf_rp + period_bytes == rt5514_dsp->buf_limit)
			rt5514_dsp->buf_rp = rt5514_dsp->buf_base;
		अन्यथा
			rt5514_dsp->buf_rp += period_bytes;
	पूर्ण अन्यथा अणु
		truncated_bytes = rt5514_dsp->buf_limit - rt5514_dsp->buf_rp;
		rt5514_spi_burst_पढ़ो(rt5514_dsp->buf_rp,
			runसमय->dma_area + rt5514_dsp->dma_offset,
			truncated_bytes);

		rt5514_spi_burst_पढ़ो(rt5514_dsp->buf_base,
			runसमय->dma_area + rt5514_dsp->dma_offset +
			truncated_bytes, period_bytes - truncated_bytes);

		rt5514_dsp->buf_rp = rt5514_dsp->buf_base + period_bytes -
			truncated_bytes;
	पूर्ण

	rt5514_dsp->get_size += period_bytes;
	rt5514_dsp->dma_offset += period_bytes;
	अगर (rt5514_dsp->dma_offset >= runसमय->dma_bytes)
		rt5514_dsp->dma_offset = 0;

	snd_pcm_period_elapsed(rt5514_dsp->substream);

	schedule_delayed_work(&rt5514_dsp->copy_work, 5);

करोne:
	mutex_unlock(&rt5514_dsp->dma_lock);
पूर्ण

अटल व्योम rt5514_schedule_copy(काष्ठा rt5514_dsp *rt5514_dsp)
अणु
	u8 buf[8];

	अगर (!rt5514_dsp->substream)
		वापस;

	rt5514_dsp->get_size = 0;

	/**
	 * The address area x1800XXXX is the रेजिस्टर address, and it cannot
	 * support spi burst पढ़ो perfectly. So we use the spi burst पढ़ो
	 * inभागidually to make sure the data correctly.
	 */
	rt5514_spi_burst_पढ़ो(RT5514_BUFFER_VOICE_BASE, (u8 *)&buf,
		माप(buf));
	rt5514_dsp->buf_base = buf[0] | buf[1] << 8 | buf[2] << 16 |
				buf[3] << 24;

	rt5514_spi_burst_पढ़ो(RT5514_BUFFER_VOICE_LIMIT, (u8 *)&buf,
		माप(buf));
	rt5514_dsp->buf_limit = buf[0] | buf[1] << 8 | buf[2] << 16 |
				buf[3] << 24;

	rt5514_spi_burst_पढ़ो(RT5514_BUFFER_VOICE_WP, (u8 *)&buf,
		माप(buf));
	rt5514_dsp->buf_rp = buf[0] | buf[1] << 8 | buf[2] << 16 |
				buf[3] << 24;

	अगर (rt5514_dsp->buf_rp % 8)
		rt5514_dsp->buf_rp = (rt5514_dsp->buf_rp / 8) * 8;

	rt5514_dsp->buf_size = rt5514_dsp->buf_limit - rt5514_dsp->buf_base;

	अगर (rt5514_dsp->buf_base && rt5514_dsp->buf_limit &&
		rt5514_dsp->buf_rp && rt5514_dsp->buf_size)
		schedule_delayed_work(&rt5514_dsp->copy_work, 0);
पूर्ण

अटल irqवापस_t rt5514_spi_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rt5514_dsp *rt5514_dsp = data;

	rt5514_schedule_copy(rt5514_dsp);

	वापस IRQ_HANDLED;
पूर्ण

/* PCM क्रम streaming audio from the DSP buffer */
अटल पूर्णांक rt5514_spi_pcm_खोलो(काष्ठा snd_soc_component *component,
			       काष्ठा snd_pcm_substream *substream)
अणु
	snd_soc_set_runसमय_hwparams(substream, &rt5514_spi_pcm_hardware);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5514_spi_hw_params(काष्ठा snd_soc_component *component,
				काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा rt5514_dsp *rt5514_dsp =
		snd_soc_component_get_drvdata(component);
	u8 buf[8];

	mutex_lock(&rt5514_dsp->dma_lock);
	rt5514_dsp->substream = substream;
	rt5514_dsp->dma_offset = 0;

	/* Read IRQ status and schedule copy accordingly. */
	rt5514_spi_burst_पढ़ो(RT5514_IRQ_CTRL, (u8 *)&buf, माप(buf));
	अगर (buf[0] & RT5514_IRQ_STATUS_BIT)
		rt5514_schedule_copy(rt5514_dsp);

	mutex_unlock(&rt5514_dsp->dma_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक rt5514_spi_hw_मुक्त(काष्ठा snd_soc_component *component,
			      काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा rt5514_dsp *rt5514_dsp =
		snd_soc_component_get_drvdata(component);

	mutex_lock(&rt5514_dsp->dma_lock);
	rt5514_dsp->substream = शून्य;
	mutex_unlock(&rt5514_dsp->dma_lock);

	cancel_delayed_work_sync(&rt5514_dsp->copy_work);

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t rt5514_spi_pcm_poपूर्णांकer(
		काष्ठा snd_soc_component *component,
		काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा rt5514_dsp *rt5514_dsp =
		snd_soc_component_get_drvdata(component);

	वापस bytes_to_frames(runसमय, rt5514_dsp->dma_offset);
पूर्ण


अटल पूर्णांक rt5514_spi_pcm_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt5514_dsp *rt5514_dsp;
	पूर्णांक ret;

	rt5514_dsp = devm_kzalloc(component->dev, माप(*rt5514_dsp),
			GFP_KERNEL);
	अगर (!rt5514_dsp)
		वापस -ENOMEM;

	rt5514_dsp->dev = &rt5514_spi->dev;
	mutex_init(&rt5514_dsp->dma_lock);
	INIT_DELAYED_WORK(&rt5514_dsp->copy_work, rt5514_spi_copy_work);
	snd_soc_component_set_drvdata(component, rt5514_dsp);

	अगर (rt5514_spi->irq) अणु
		ret = devm_request_thपढ़ोed_irq(&rt5514_spi->dev,
			rt5514_spi->irq, शून्य, rt5514_spi_irq,
			IRQF_TRIGGER_RISING | IRQF_ONESHOT, "rt5514-spi",
			rt5514_dsp);
		अगर (ret)
			dev_err(&rt5514_spi->dev,
				"%s Failed to reguest IRQ: %d\n", __func__,
				ret);
		अन्यथा
			device_init_wakeup(rt5514_dsp->dev, true);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt5514_spi_pcm_new(काष्ठा snd_soc_component *component,
			      काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	snd_pcm_set_managed_buffer_all(rtd->pcm, SNDRV_DMA_TYPE_VMALLOC,
				       शून्य, 0, 0);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver rt5514_spi_component = अणु
	.name		= DRV_NAME,
	.probe		= rt5514_spi_pcm_probe,
	.खोलो		= rt5514_spi_pcm_खोलो,
	.hw_params	= rt5514_spi_hw_params,
	.hw_मुक्त	= rt5514_spi_hw_मुक्त,
	.poपूर्णांकer	= rt5514_spi_pcm_poपूर्णांकer,
	.pcm_स्थिरruct	= rt5514_spi_pcm_new,
पूर्ण;

/**
 * rt5514_spi_burst_पढ़ो - Read data from SPI by rt5514 address.
 * @addr: Start address.
 * @rxbuf: Data Buffer क्रम पढ़ोing.
 * @len: Data length, it must be a multiple of 8.
 *
 *
 * Returns true क्रम success.
 */
पूर्णांक rt5514_spi_burst_पढ़ो(अचिन्हित पूर्णांक addr, u8 *rxbuf, माप_प्रकार len)
अणु
	u8 spi_cmd = RT5514_SPI_CMD_BURST_READ;
	पूर्णांक status;
	u8 ग_लिखो_buf[8];
	अचिन्हित पूर्णांक i, end, offset = 0;

	काष्ठा spi_message message;
	काष्ठा spi_transfer x[3];

	जबतक (offset < len) अणु
		अगर (offset + RT5514_SPI_BUF_LEN <= len)
			end = RT5514_SPI_BUF_LEN;
		अन्यथा
			end = len % RT5514_SPI_BUF_LEN;

		ग_लिखो_buf[0] = spi_cmd;
		ग_लिखो_buf[1] = ((addr + offset) & 0xff000000) >> 24;
		ग_लिखो_buf[2] = ((addr + offset) & 0x00ff0000) >> 16;
		ग_लिखो_buf[3] = ((addr + offset) & 0x0000ff00) >> 8;
		ग_लिखो_buf[4] = ((addr + offset) & 0x000000ff) >> 0;

		spi_message_init(&message);
		स_रखो(x, 0, माप(x));

		x[0].len = 5;
		x[0].tx_buf = ग_लिखो_buf;
		spi_message_add_tail(&x[0], &message);

		x[1].len = 4;
		x[1].tx_buf = ग_लिखो_buf;
		spi_message_add_tail(&x[1], &message);

		x[2].len = end;
		x[2].rx_buf = rxbuf + offset;
		spi_message_add_tail(&x[2], &message);

		status = spi_sync(rt5514_spi, &message);

		अगर (status)
			वापस false;

		offset += RT5514_SPI_BUF_LEN;
	पूर्ण

	क्रम (i = 0; i < len; i += 8) अणु
		ग_लिखो_buf[0] = rxbuf[i + 0];
		ग_लिखो_buf[1] = rxbuf[i + 1];
		ग_लिखो_buf[2] = rxbuf[i + 2];
		ग_लिखो_buf[3] = rxbuf[i + 3];
		ग_लिखो_buf[4] = rxbuf[i + 4];
		ग_लिखो_buf[5] = rxbuf[i + 5];
		ग_लिखो_buf[6] = rxbuf[i + 6];
		ग_लिखो_buf[7] = rxbuf[i + 7];

		rxbuf[i + 0] = ग_लिखो_buf[7];
		rxbuf[i + 1] = ग_लिखो_buf[6];
		rxbuf[i + 2] = ग_लिखो_buf[5];
		rxbuf[i + 3] = ग_लिखो_buf[4];
		rxbuf[i + 4] = ग_लिखो_buf[3];
		rxbuf[i + 5] = ग_लिखो_buf[2];
		rxbuf[i + 6] = ग_लिखो_buf[1];
		rxbuf[i + 7] = ग_लिखो_buf[0];
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(rt5514_spi_burst_पढ़ो);

/**
 * rt5514_spi_burst_ग_लिखो - Write data to SPI by rt5514 address.
 * @addr: Start address.
 * @txbuf: Data Buffer क्रम writng.
 * @len: Data length, it must be a multiple of 8.
 *
 *
 * Returns true क्रम success.
 */
पूर्णांक rt5514_spi_burst_ग_लिखो(u32 addr, स्थिर u8 *txbuf, माप_प्रकार len)
अणु
	u8 spi_cmd = RT5514_SPI_CMD_BURST_WRITE;
	u8 *ग_लिखो_buf;
	अचिन्हित पूर्णांक i, end, offset = 0;

	ग_लिखो_buf = kदो_स्मृति(RT5514_SPI_BUF_LEN + 6, GFP_KERNEL);

	अगर (ग_लिखो_buf == शून्य)
		वापस -ENOMEM;

	जबतक (offset < len) अणु
		अगर (offset + RT5514_SPI_BUF_LEN <= len)
			end = RT5514_SPI_BUF_LEN;
		अन्यथा
			end = len % RT5514_SPI_BUF_LEN;

		ग_लिखो_buf[0] = spi_cmd;
		ग_लिखो_buf[1] = ((addr + offset) & 0xff000000) >> 24;
		ग_लिखो_buf[2] = ((addr + offset) & 0x00ff0000) >> 16;
		ग_लिखो_buf[3] = ((addr + offset) & 0x0000ff00) >> 8;
		ग_लिखो_buf[4] = ((addr + offset) & 0x000000ff) >> 0;

		क्रम (i = 0; i < end; i += 8) अणु
			ग_लिखो_buf[i + 12] = txbuf[offset + i + 0];
			ग_लिखो_buf[i + 11] = txbuf[offset + i + 1];
			ग_लिखो_buf[i + 10] = txbuf[offset + i + 2];
			ग_लिखो_buf[i +  9] = txbuf[offset + i + 3];
			ग_लिखो_buf[i +  8] = txbuf[offset + i + 4];
			ग_लिखो_buf[i +  7] = txbuf[offset + i + 5];
			ग_लिखो_buf[i +  6] = txbuf[offset + i + 6];
			ग_लिखो_buf[i +  5] = txbuf[offset + i + 7];
		पूर्ण

		ग_लिखो_buf[end + 5] = spi_cmd;

		spi_ग_लिखो(rt5514_spi, ग_लिखो_buf, end + 6);

		offset += RT5514_SPI_BUF_LEN;
	पूर्ण

	kमुक्त(ग_लिखो_buf);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt5514_spi_burst_ग_लिखो);

अटल पूर्णांक rt5514_spi_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;

	rt5514_spi = spi;

	ret = devm_snd_soc_रेजिस्टर_component(&spi->dev,
					      &rt5514_spi_component,
					      &rt5514_spi_dai, 1);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "Failed to register component.\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rt5514_suspend(काष्ठा device *dev)
अणु
	पूर्णांक irq = to_spi_device(dev)->irq;

	अगर (device_may_wakeup(dev))
		enable_irq_wake(irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rt5514_resume(काष्ठा device *dev)
अणु
	काष्ठा rt5514_dsp *rt5514_dsp = dev_get_drvdata(dev);
	पूर्णांक irq = to_spi_device(dev)->irq;
	u8 buf[8];

	अगर (device_may_wakeup(dev))
		disable_irq_wake(irq);

	अगर (rt5514_dsp) अणु
		अगर (rt5514_dsp->substream) अणु
			rt5514_spi_burst_पढ़ो(RT5514_IRQ_CTRL, (u8 *)&buf,
				माप(buf));
			अगर (buf[0] & RT5514_IRQ_STATUS_BIT)
				rt5514_schedule_copy(rt5514_dsp);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops rt5514_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(rt5514_suspend, rt5514_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id rt5514_of_match[] = अणु
	अणु .compatible = "realtek,rt5514", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rt5514_of_match);

अटल काष्ठा spi_driver rt5514_spi_driver = अणु
	.driver = अणु
		.name = "rt5514",
		.pm = &rt5514_pm_ops,
		.of_match_table = of_match_ptr(rt5514_of_match),
	पूर्ण,
	.probe = rt5514_spi_probe,
पूर्ण;
module_spi_driver(rt5514_spi_driver);

MODULE_DESCRIPTION("RT5514 SPI driver");
MODULE_AUTHOR("Oder Chiou <oder_chiou@realtek.com>");
MODULE_LICENSE("GPL v2");
