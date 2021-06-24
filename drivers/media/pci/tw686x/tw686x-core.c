<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 VanguardiaSur - www.vanguardiasur.com.ar
 *
 * Based on original driver by Krzysztof Ha?asa:
 * Copyright (C) 2015 Industrial Research Institute क्रम Automation
 * and Measurements PIAP
 *
 * Notes
 * -----
 *
 * 1. Under stress-testing, it has been observed that the PCIe link
 * goes करोwn, without reason. Thereक्रमe, the driver takes special care
 * to allow device hot-unplugging.
 *
 * 2. TW686X devices are capable of setting a few dअगरferent DMA modes,
 * including: scatter-gather, field and frame modes. However,
 * under stress testings it has been found that the machine can
 * मुक्तze completely अगर DMA रेजिस्टरs are programmed जबतक streaming
 * is active.
 *
 * Thereक्रमe, driver implements a dma_mode called 'memcpy' which
 * aव्योमs cycling the DMA buffers, and insteads allocates extra DMA buffers
 * and then copies पूर्णांकo vदो_स्मृति'ed user buffers.
 *
 * In addition to this, when streaming is on, the driver tries to access
 * hardware रेजिस्टरs as infrequently as possible. This is करोne by using
 * a समयr to limit the rate at which DMA is reset on DMA channels error.
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>

#समावेश "tw686x.h"
#समावेश "tw686x-regs.h"

/*
 * This module parameter allows to control the DMA_TIMER_INTERVAL value.
 * The DMA_TIMER_INTERVAL रेजिस्टर controls the minimum DMA पूर्णांकerrupt
 * समय span (iow, the maximum DMA पूर्णांकerrupt rate) thus allowing क्रम
 * IRQ coalescing.
 *
 * The chip datasheet करोes not mention a समय unit क्रम this value, so
 * users wanting fine-grain control over the पूर्णांकerrupt rate should
 * determine the desired value through testing.
 */
अटल u32 dma_पूर्णांकerval = 0x00098968;
module_param(dma_पूर्णांकerval, पूर्णांक, 0444);
MODULE_PARM_DESC(dma_पूर्णांकerval, "Minimum time span for DMA interrupting host");

अटल अचिन्हित पूर्णांक dma_mode = TW686X_DMA_MODE_MEMCPY;
अटल स्थिर अक्षर *dma_mode_name(अचिन्हित पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल TW686X_DMA_MODE_MEMCPY:
		वापस "memcpy";
	हाल TW686X_DMA_MODE_CONTIG:
		वापस "contig";
	हाल TW686X_DMA_MODE_SG:
		वापस "sg";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

अटल पूर्णांक tw686x_dma_mode_get(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	वापस प्र_लिखो(buffer, "%s", dma_mode_name(dma_mode));
पूर्ण

अटल पूर्णांक tw686x_dma_mode_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	अगर (!strहालcmp(val, dma_mode_name(TW686X_DMA_MODE_MEMCPY)))
		dma_mode = TW686X_DMA_MODE_MEMCPY;
	अन्यथा अगर (!strहालcmp(val, dma_mode_name(TW686X_DMA_MODE_CONTIG)))
		dma_mode = TW686X_DMA_MODE_CONTIG;
	अन्यथा अगर (!strहालcmp(val, dma_mode_name(TW686X_DMA_MODE_SG)))
		dma_mode = TW686X_DMA_MODE_SG;
	अन्यथा
		वापस -EINVAL;
	वापस 0;
पूर्ण
module_param_call(dma_mode, tw686x_dma_mode_set, tw686x_dma_mode_get,
		  &dma_mode, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(dma_mode, "DMA operation mode (memcpy/contig/sg, default=memcpy)");

व्योम tw686x_disable_channel(काष्ठा tw686x_dev *dev, अचिन्हित पूर्णांक channel)
अणु
	u32 dma_en = reg_पढ़ो(dev, DMA_CHANNEL_ENABLE);
	u32 dma_cmd = reg_पढ़ो(dev, DMA_CMD);

	dma_en &= ~BIT(channel);
	dma_cmd &= ~BIT(channel);

	/* Must हटाओ it from pending too */
	dev->pending_dma_en &= ~BIT(channel);
	dev->pending_dma_cmd &= ~BIT(channel);

	/* Stop DMA अगर no channels are enabled */
	अगर (!dma_en)
		dma_cmd = 0;
	reg_ग_लिखो(dev, DMA_CHANNEL_ENABLE, dma_en);
	reg_ग_लिखो(dev, DMA_CMD, dma_cmd);
पूर्ण

व्योम tw686x_enable_channel(काष्ठा tw686x_dev *dev, अचिन्हित पूर्णांक channel)
अणु
	u32 dma_en = reg_पढ़ो(dev, DMA_CHANNEL_ENABLE);
	u32 dma_cmd = reg_पढ़ो(dev, DMA_CMD);

	dev->pending_dma_en |= dma_en | BIT(channel);
	dev->pending_dma_cmd |= dma_cmd | DMA_CMD_ENABLE | BIT(channel);
पूर्ण

/*
 * The purpose of this awful hack is to aव्योम enabling the DMA
 * channels "too fast" which makes some TW686x devices very
 * angry and मुक्तze the CPU (see note 1).
 */
अटल व्योम tw686x_dma_delay(काष्ठा समयr_list *t)
अणु
	काष्ठा tw686x_dev *dev = from_समयr(dev, t, dma_delay_समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->lock, flags);

	reg_ग_लिखो(dev, DMA_CHANNEL_ENABLE, dev->pending_dma_en);
	reg_ग_लिखो(dev, DMA_CMD, dev->pending_dma_cmd);
	dev->pending_dma_en = 0;
	dev->pending_dma_cmd = 0;

	spin_unlock_irqrestore(&dev->lock, flags);
पूर्ण

अटल व्योम tw686x_reset_channels(काष्ठा tw686x_dev *dev, अचिन्हित पूर्णांक ch_mask)
अणु
	u32 dma_en, dma_cmd;

	dma_en = reg_पढ़ो(dev, DMA_CHANNEL_ENABLE);
	dma_cmd = reg_पढ़ो(dev, DMA_CMD);

	/*
	 * Save pending रेजिस्टर status, the समयr will
	 * restore them.
	 */
	dev->pending_dma_en |= dma_en;
	dev->pending_dma_cmd |= dma_cmd;

	/* Disable the reset channels */
	reg_ग_लिखो(dev, DMA_CHANNEL_ENABLE, dma_en & ~ch_mask);

	अगर ((dma_en & ~ch_mask) == 0) अणु
		dev_dbg(&dev->pci_dev->dev, "reset: stopping DMA\n");
		dma_cmd &= ~DMA_CMD_ENABLE;
	पूर्ण
	reg_ग_लिखो(dev, DMA_CMD, dma_cmd & ~ch_mask);
पूर्ण

अटल irqवापस_t tw686x_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा tw686x_dev *dev = (काष्ठा tw686x_dev *)dev_id;
	अचिन्हित पूर्णांक video_requests, audio_requests, reset_ch;
	u32 fअगरo_status, fअगरo_संकेत, fअगरo_ov, fअगरo_bad, fअगरo_errors;
	u32 पूर्णांक_status, dma_en, video_en, pb_status;
	अचिन्हित दीर्घ flags;

	पूर्णांक_status = reg_पढ़ो(dev, INT_STATUS); /* cleared on पढ़ो */
	fअगरo_status = reg_पढ़ो(dev, VIDEO_FIFO_STATUS);

	/* INT_STATUS करोes not include FIFO_STATUS errors! */
	अगर (!पूर्णांक_status && !TW686X_FIFO_ERROR(fअगरo_status))
		वापस IRQ_NONE;

	अगर (पूर्णांक_status & INT_STATUS_DMA_TOUT) अणु
		dev_dbg(&dev->pci_dev->dev,
			"DMA timeout. Resetting DMA for all channels\n");
		reset_ch = ~0;
		जाओ reset_channels;
	पूर्ण

	spin_lock_irqsave(&dev->lock, flags);
	dma_en = reg_पढ़ो(dev, DMA_CHANNEL_ENABLE);
	spin_unlock_irqrestore(&dev->lock, flags);

	video_en = dma_en & 0xff;
	fअगरo_संकेत = ~(fअगरo_status & 0xff) & video_en;
	fअगरo_ov = fअगरo_status >> 24;
	fअगरo_bad = fअगरo_status >> 16;

	/* Mask of channels with संकेत and FIFO errors */
	fअगरo_errors = fअगरo_संकेत & (fअगरo_ov | fअगरo_bad);

	reset_ch = 0;
	pb_status = reg_पढ़ो(dev, PB_STATUS);

	/* Coalesce video frame/error events */
	video_requests = (पूर्णांक_status & video_en) | fअगरo_errors;
	audio_requests = (पूर्णांक_status & dma_en) >> 8;

	अगर (video_requests)
		tw686x_video_irq(dev, video_requests, pb_status,
				 fअगरo_status, &reset_ch);
	अगर (audio_requests)
		tw686x_audio_irq(dev, audio_requests, pb_status);

reset_channels:
	अगर (reset_ch) अणु
		spin_lock_irqsave(&dev->lock, flags);
		tw686x_reset_channels(dev, reset_ch);
		spin_unlock_irqrestore(&dev->lock, flags);
		mod_समयr(&dev->dma_delay_समयr,
			  jअगरfies + msecs_to_jअगरfies(100));
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम tw686x_dev_release(काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा tw686x_dev *dev = container_of(v4l2_dev, काष्ठा tw686x_dev,
					      v4l2_dev);
	अचिन्हित पूर्णांक ch;

	क्रम (ch = 0; ch < max_channels(dev); ch++)
		v4l2_ctrl_handler_मुक्त(&dev->video_channels[ch].ctrl_handler);

	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);

	kमुक्त(dev->audio_channels);
	kमुक्त(dev->video_channels);
	kमुक्त(dev);
पूर्ण

अटल पूर्णांक tw686x_probe(काष्ठा pci_dev *pci_dev,
			स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा tw686x_dev *dev;
	पूर्णांक err;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;
	dev->type = pci_id->driver_data;
	dev->dma_mode = dma_mode;
	प्र_लिखो(dev->name, "tw%04X", pci_dev->device);

	dev->video_channels = kसुस्मृति(max_channels(dev),
		माप(*dev->video_channels), GFP_KERNEL);
	अगर (!dev->video_channels) अणु
		err = -ENOMEM;
		जाओ मुक्त_dev;
	पूर्ण

	dev->audio_channels = kसुस्मृति(max_channels(dev),
		माप(*dev->audio_channels), GFP_KERNEL);
	अगर (!dev->audio_channels) अणु
		err = -ENOMEM;
		जाओ मुक्त_video;
	पूर्ण

	pr_info("%s: PCI %s, IRQ %d, MMIO 0x%lx (%s mode)\n", dev->name,
		pci_name(pci_dev), pci_dev->irq,
		(अचिन्हित दीर्घ)pci_resource_start(pci_dev, 0),
		dma_mode_name(dma_mode));

	dev->pci_dev = pci_dev;
	अगर (pci_enable_device(pci_dev)) अणु
		err = -EIO;
		जाओ मुक्त_audio;
	पूर्ण

	pci_set_master(pci_dev);
	err = dma_set_mask(&pci_dev->dev, DMA_BIT_MASK(32));
	अगर (err) अणु
		dev_err(&pci_dev->dev, "32-bit PCI DMA not supported\n");
		err = -EIO;
		जाओ disable_pci;
	पूर्ण

	err = pci_request_regions(pci_dev, dev->name);
	अगर (err) अणु
		dev_err(&pci_dev->dev, "unable to request PCI region\n");
		जाओ disable_pci;
	पूर्ण

	dev->mmio = pci_ioremap_bar(pci_dev, 0);
	अगर (!dev->mmio) अणु
		dev_err(&pci_dev->dev, "unable to remap PCI region\n");
		err = -ENOMEM;
		जाओ मुक्त_region;
	पूर्ण

	/* Reset all subप्रणालीs */
	reg_ग_लिखो(dev, SYS_SOFT_RST, 0x0f);
	mdelay(1);

	reg_ग_लिखो(dev, SRST[0], 0x3f);
	अगर (max_channels(dev) > 4)
		reg_ग_लिखो(dev, SRST[1], 0x3f);

	/* Disable the DMA engine */
	reg_ग_लिखो(dev, DMA_CMD, 0);
	reg_ग_लिखो(dev, DMA_CHANNEL_ENABLE, 0);

	/* Enable DMA FIFO overflow and poपूर्णांकer check */
	reg_ग_लिखो(dev, DMA_CONFIG, 0xffffff04);
	reg_ग_लिखो(dev, DMA_CHANNEL_TIMEOUT, 0x140c8584);
	reg_ग_लिखो(dev, DMA_TIMER_INTERVAL, dma_पूर्णांकerval);

	spin_lock_init(&dev->lock);

	err = request_irq(pci_dev->irq, tw686x_irq, IRQF_SHARED,
			  dev->name, dev);
	अगर (err < 0) अणु
		dev_err(&pci_dev->dev, "unable to request interrupt\n");
		जाओ iounmap;
	पूर्ण

	समयr_setup(&dev->dma_delay_समयr, tw686x_dma_delay, 0);

	/*
	 * This must be set right beक्रमe initializing v4l2_dev.
	 * It's used to release resources after the last handle
	 * held is released.
	 */
	dev->v4l2_dev.release = tw686x_dev_release;
	err = tw686x_video_init(dev);
	अगर (err) अणु
		dev_err(&pci_dev->dev, "can't register video\n");
		जाओ मुक्त_irq;
	पूर्ण

	err = tw686x_audio_init(dev);
	अगर (err)
		dev_warn(&pci_dev->dev, "can't register audio\n");

	pci_set_drvdata(pci_dev, dev);
	वापस 0;

मुक्त_irq:
	मुक्त_irq(pci_dev->irq, dev);
iounmap:
	pci_iounmap(pci_dev, dev->mmio);
मुक्त_region:
	pci_release_regions(pci_dev);
disable_pci:
	pci_disable_device(pci_dev);
मुक्त_audio:
	kमुक्त(dev->audio_channels);
मुक्त_video:
	kमुक्त(dev->video_channels);
मुक्त_dev:
	kमुक्त(dev);
	वापस err;
पूर्ण

अटल व्योम tw686x_हटाओ(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा tw686x_dev *dev = pci_get_drvdata(pci_dev);
	अचिन्हित दीर्घ flags;

	/* This guarantees the IRQ handler is no दीर्घer running,
	 * which means we can kiss good-bye some resources.
	 */
	मुक्त_irq(pci_dev->irq, dev);

	tw686x_video_मुक्त(dev);
	tw686x_audio_मुक्त(dev);
	del_समयr_sync(&dev->dma_delay_समयr);

	pci_iounmap(pci_dev, dev->mmio);
	pci_release_regions(pci_dev);
	pci_disable_device(pci_dev);

	/*
	 * Setting pci_dev to शून्य allows to detect hardware is no दीर्घer
	 * available and will be used by vb2_ops. This is required because
	 * the device someबार hot-unplugs itself as the result of a PCIe
	 * link करोwn.
	 * The lock is really important here.
	 */
	spin_lock_irqsave(&dev->lock, flags);
	dev->pci_dev = शून्य;
	spin_unlock_irqrestore(&dev->lock, flags);

	/*
	 * This calls tw686x_dev_release अगर it's the last reference.
	 * Otherwise, release is postponed until there are no users left.
	 */
	v4l2_device_put(&dev->v4l2_dev);
पूर्ण

/*
 * On TW6864 and TW6868, all channels share the pair of video DMA SG tables,
 * with 10-bit start_idx and end_idx determining start and end of frame buffer
 * क्रम particular channel.
 * TW6868 with all its 8 channels would be problematic (only 127 SG entries per
 * channel) but we support only 4 channels on this chip anyway (the first
 * 4 channels are driven with पूर्णांकernal video decoder, the other 4 would require
 * an बाह्यal TW286x part).
 *
 * On TW6865 and TW6869, each channel has its own DMA SG table, with indexes
 * starting with 0. Both chips have complete sets of पूर्णांकernal video decoders
 * (respectively 4 or 8-channel).
 *
 * All chips have separate SG tables क्रम two video frames.
 */

/* driver_data is number of A/V channels */
अटल स्थिर काष्ठा pci_device_id tw686x_pci_tbl[] = अणु
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_TECHWELL, 0x6864),
		.driver_data = 4
	पूर्ण,
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_TECHWELL, 0x6865), /* not tested */
		.driver_data = 4 | TYPE_SECOND_GEN
	पूर्ण,
	/*
	 * TW6868 supports 8 A/V channels with an बाह्यal TW2865 chip;
	 * not supported by the driver.
	 */
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_TECHWELL, 0x6868), /* not tested */
		.driver_data = 4
	पूर्ण,
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_TECHWELL, 0x6869),
		.driver_data = 8 | TYPE_SECOND_GENपूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, tw686x_pci_tbl);

अटल काष्ठा pci_driver tw686x_pci_driver = अणु
	.name = "tw686x",
	.id_table = tw686x_pci_tbl,
	.probe = tw686x_probe,
	.हटाओ = tw686x_हटाओ,
पूर्ण;
module_pci_driver(tw686x_pci_driver);

MODULE_DESCRIPTION("Driver for video frame grabber cards based on Intersil/Techwell TW686[4589]");
MODULE_AUTHOR("Ezequiel Garcia <ezequiel@vanguardiasur.com.ar>");
MODULE_AUTHOR("Krzysztof Ha?asa <khalasa@piap.pl>");
MODULE_LICENSE("GPL v2");
