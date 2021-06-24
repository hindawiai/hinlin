<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  TW5864 driver - core functions
 *
 *  Copyright (C) 2016 Bluecherry, LLC <मुख्यtainers@bluecherrydvr.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/kmod.h>
#समावेश <linux/sound.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pm.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/jअगरfies.h>
#समावेश <यंत्र/dma.h>
#समावेश <media/v4l2-dev.h>

#समावेश "tw5864.h"
#समावेश "tw5864-reg.h"

MODULE_DESCRIPTION("V4L2 driver module for tw5864-based multimedia capture & encoding devices");
MODULE_AUTHOR("Bluecherry Maintainers <maintainers@bluecherrydvr.com>");
MODULE_AUTHOR("Andrey Utkin <andrey.utkin@corp.bluecherry.net>");
MODULE_LICENSE("GPL");

/*
 * BEWARE OF KNOWN ISSUES WITH VIDEO QUALITY
 *
 * This driver was developed by Bluecherry LLC by deducing behaviour of
 * original manufacturer's driver, from both source code and execution traces.
 * It is known that there are some artअगरacts on output video with this driver:
 *  - on all known hardware samples: अक्रमom pixels of wrong color (mostly
 *    white, red or blue) appearing and disappearing on sequences of P-frames;
 *  - on some hardware samples (known with H.264 core version e006:2800):
 *    total madness on P-frames: blocks of wrong luminance; blocks of wrong
 *    colors "creeping" across the picture.
 * There is a workaround क्रम both issues: aव्योम P-frames by setting GOP size
 * to 1. To करो that, run this command on device files created by this driver:
 *
 * v4l2-ctl --device /dev/videoX --set-ctrl=video_gop_size=1
 *
 * These issues are not decoding errors; all produced H.264 streams are decoded
 * properly. Streams without P-frames करोn't have these artifacts so it's not
 * analog-to-digital conversion issues nor पूर्णांकernal memory errors; we conclude
 * it's पूर्णांकernal H.264 encoder issues.
 * We cannot even check the original driver's behaviour because it has never
 * worked properly at all in our development environment. So these issues may
 * be actually related to firmware or hardware. However it may be that there's
 * just some more रेजिस्टर settings missing in the driver which would please
 * the hardware.
 * Manufacturer didn't help much on our inquiries, but feel मुक्त to disturb
 * again the support of Intersil (owner of क्रमmer Techwell).
 */

/* take first मुक्त /dev/videoX indexes by शेष */
अटल अचिन्हित पूर्णांक video_nr[] = अणु[0 ... (TW5864_INPUTS - 1)] = -1 पूर्ण;

module_param_array(video_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(video_nr, "video devices numbers array");

/*
 * Please add any new PCI IDs to: https://pci-ids.ucw.cz.  This keeps
 * the PCI ID database up to date.  Note that the entries must be
 * added under venकरोr 0x1797 (Techwell Inc.) as subप्रणाली IDs.
 */
अटल स्थिर काष्ठा pci_device_id tw5864_pci_tbl[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_TECHWELL, PCI_DEVICE_ID_TECHWELL_5864)पूर्ण,
	अणु0,पूर्ण
पूर्ण;

व्योम tw5864_irqmask_apply(काष्ठा tw5864_dev *dev)
अणु
	tw_ग_लिखोl(TW5864_INTR_ENABLE_L, dev->irqmask & 0xffff);
	tw_ग_लिखोl(TW5864_INTR_ENABLE_H, (dev->irqmask >> 16));
पूर्ण

अटल व्योम tw5864_पूर्णांकerrupts_disable(काष्ठा tw5864_dev *dev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->slock, flags);
	dev->irqmask = 0;
	tw5864_irqmask_apply(dev);
	spin_unlock_irqrestore(&dev->slock, flags);
पूर्ण

अटल व्योम tw5864_समयr_isr(काष्ठा tw5864_dev *dev);
अटल व्योम tw5864_h264_isr(काष्ठा tw5864_dev *dev);

अटल irqवापस_t tw5864_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा tw5864_dev *dev = dev_id;
	u32 status;

	status = tw_पढ़ोl(TW5864_INTR_STATUS_L) |
		tw_पढ़ोl(TW5864_INTR_STATUS_H) << 16;
	अगर (!status)
		वापस IRQ_NONE;

	tw_ग_लिखोl(TW5864_INTR_CLR_L, 0xffff);
	tw_ग_लिखोl(TW5864_INTR_CLR_H, 0xffff);

	अगर (status & TW5864_INTR_VLC_DONE)
		tw5864_h264_isr(dev);

	अगर (status & TW5864_INTR_TIMER)
		tw5864_समयr_isr(dev);

	अगर (!(status & (TW5864_INTR_TIMER | TW5864_INTR_VLC_DONE))) अणु
		dev_dbg(&dev->pci->dev, "Unknown interrupt, status 0x%08X\n",
			status);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम tw5864_h264_isr(काष्ठा tw5864_dev *dev)
अणु
	पूर्णांक channel = tw_पढ़ोl(TW5864_DSP) & TW5864_DSP_ENC_CHN;
	काष्ठा tw5864_input *input = &dev->inमाला_दो[channel];
	पूर्णांक cur_frame_index, next_frame_index;
	काष्ठा tw5864_h264_frame *cur_frame, *next_frame;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->slock, flags);

	cur_frame_index = dev->h264_buf_w_index;
	next_frame_index = (cur_frame_index + 1) % H264_BUF_CNT;
	cur_frame = &dev->h264_buf[cur_frame_index];
	next_frame = &dev->h264_buf[next_frame_index];

	अगर (next_frame_index != dev->h264_buf_r_index) अणु
		cur_frame->vlc_len = tw_पढ़ोl(TW5864_VLC_LENGTH) << 2;
		cur_frame->checksum = tw_पढ़ोl(TW5864_VLC_CRC_REG);
		cur_frame->input = input;
		cur_frame->बारtamp = kसमय_get_ns();
		cur_frame->seqno = input->frame_seqno;
		cur_frame->gop_seqno = input->frame_gop_seqno;

		dev->h264_buf_w_index = next_frame_index;
		tasklet_schedule(&dev->tasklet);

		cur_frame = next_frame;

		spin_lock(&input->slock);
		input->frame_seqno++;
		input->frame_gop_seqno++;
		अगर (input->frame_gop_seqno >= input->gop)
			input->frame_gop_seqno = 0;
		spin_unlock(&input->slock);
	पूर्ण अन्यथा अणु
		dev_err(&dev->pci->dev,
			"Skipped frame on input %d because all buffers busy\n",
			channel);
	पूर्ण

	dev->encoder_busy = 0;

	spin_unlock_irqrestore(&dev->slock, flags);

	tw_ग_लिखोl(TW5864_VLC_STREAM_BASE_ADDR, cur_frame->vlc.dma_addr);
	tw_ग_लिखोl(TW5864_MV_STREAM_BASE_ADDR, cur_frame->mv.dma_addr);

	/* Additional ack क्रम this पूर्णांकerrupt */
	tw_ग_लिखोl(TW5864_VLC_DSP_INTR, 0x00000001);
	tw_ग_लिखोl(TW5864_PCI_INTR_STATUS, TW5864_VLC_DONE_INTR);
पूर्ण

अटल व्योम tw5864_input_deadline_update(काष्ठा tw5864_input *input)
अणु
	input->new_frame_deadline = jअगरfies + msecs_to_jअगरfies(1000);
पूर्ण

अटल व्योम tw5864_समयr_isr(काष्ठा tw5864_dev *dev)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	पूर्णांक encoder_busy;

	/* Additional ack क्रम this पूर्णांकerrupt */
	tw_ग_लिखोl(TW5864_PCI_INTR_STATUS, TW5864_TIMER_INTR);

	spin_lock_irqsave(&dev->slock, flags);
	encoder_busy = dev->encoder_busy;
	spin_unlock_irqrestore(&dev->slock, flags);

	अगर (encoder_busy)
		वापस;

	/*
	 * Traversing inमाला_दो in round-robin fashion, starting from next to the
	 * last processed one
	 */
	क्रम (i = 0; i < TW5864_INPUTS; i++) अणु
		पूर्णांक next_input = (i + dev->next_input) % TW5864_INPUTS;
		काष्ठा tw5864_input *input = &dev->inमाला_दो[next_input];
		पूर्णांक raw_buf_id; /* id of पूर्णांकernal buf with last raw frame */

		spin_lock_irqsave(&input->slock, flags);
		अगर (!input->enabled)
			जाओ next;

		/* Check अगर new raw frame is available */
		raw_buf_id = tw_mask_shअगरt_पढ़ोl(TW5864_SENIF_ORG_FRM_PTR1, 0x3,
						 2 * input->nr);

		अगर (input->buf_id != raw_buf_id) अणु
			input->buf_id = raw_buf_id;
			tw5864_input_deadline_update(input);
			spin_unlock_irqrestore(&input->slock, flags);

			spin_lock_irqsave(&dev->slock, flags);
			dev->encoder_busy = 1;
			dev->next_input = (next_input + 1) % TW5864_INPUTS;
			spin_unlock_irqrestore(&dev->slock, flags);

			tw5864_request_encoded_frame(input);
			अवरोध;
		पूर्ण

		/* No new raw frame; check अगर channel is stuck */
		अगर (समय_is_after_jअगरfies(input->new_frame_deadline)) अणु
			/* If stuck, request new raw frames again */
			tw_mask_shअगरt_ग_लिखोl(TW5864_ENC_BUF_PTR_REC1, 0x3,
					     2 * input->nr, input->buf_id + 3);
			tw5864_input_deadline_update(input);
		पूर्ण
next:
		spin_unlock_irqrestore(&input->slock, flags);
	पूर्ण
पूर्ण

अटल पूर्णांक tw5864_initdev(काष्ठा pci_dev *pci_dev,
			  स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा tw5864_dev *dev;
	पूर्णांक err;

	dev = devm_kzalloc(&pci_dev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	snम_लिखो(dev->name, माप(dev->name), "tw5864:%s", pci_name(pci_dev));

	err = v4l2_device_रेजिस्टर(&pci_dev->dev, &dev->v4l2_dev);
	अगर (err)
		वापस err;

	/* pci init */
	dev->pci = pci_dev;
	err = pci_enable_device(pci_dev);
	अगर (err) अणु
		dev_err(&dev->pci->dev, "pci_enable_device() failed\n");
		जाओ unreg_v4l2;
	पूर्ण

	pci_set_master(pci_dev);

	err = pci_set_dma_mask(pci_dev, DMA_BIT_MASK(32));
	अगर (err) अणु
		dev_err(&dev->pci->dev, "32 bit PCI DMA is not supported\n");
		जाओ disable_pci;
	पूर्ण

	/* get mmio */
	err = pci_request_regions(pci_dev, dev->name);
	अगर (err) अणु
		dev_err(&dev->pci->dev, "Cannot request regions for MMIO\n");
		जाओ disable_pci;
	पूर्ण
	dev->mmio = pci_ioremap_bar(pci_dev, 0);
	अगर (!dev->mmio) अणु
		err = -EIO;
		dev_err(&dev->pci->dev, "can't ioremap() MMIO memory\n");
		जाओ release_mmio;
	पूर्ण

	spin_lock_init(&dev->slock);

	dev_info(&pci_dev->dev, "TW5864 hardware version: %04x\n",
		 tw_पढ़ोl(TW5864_HW_VERSION));
	dev_info(&pci_dev->dev, "TW5864 H.264 core version: %04x:%04x\n",
		 tw_पढ़ोl(TW5864_H264REV),
		 tw_पढ़ोl(TW5864_UNDECLARED_H264REV_PART2));

	err = tw5864_video_init(dev, video_nr);
	अगर (err)
		जाओ unmap_mmio;

	/* get irq */
	err = devm_request_irq(&pci_dev->dev, pci_dev->irq, tw5864_isr,
			       IRQF_SHARED, "tw5864", dev);
	अगर (err < 0) अणु
		dev_err(&dev->pci->dev, "can't get IRQ %d\n", pci_dev->irq);
		जाओ fini_video;
	पूर्ण

	dev_info(&pci_dev->dev, "Note: there are known video quality issues. For details\n");
	dev_info(&pci_dev->dev, "see the comment in drivers/media/pci/tw5864/tw5864-core.c.\n");

	वापस 0;

fini_video:
	tw5864_video_fini(dev);
unmap_mmio:
	iounmap(dev->mmio);
release_mmio:
	pci_release_regions(pci_dev);
disable_pci:
	pci_disable_device(pci_dev);
unreg_v4l2:
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
	वापस err;
पूर्ण

अटल व्योम tw5864_finidev(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा v4l2_device *v4l2_dev = pci_get_drvdata(pci_dev);
	काष्ठा tw5864_dev *dev =
		container_of(v4l2_dev, काष्ठा tw5864_dev, v4l2_dev);

	/* shutकरोwn subप्रणालीs */
	tw5864_पूर्णांकerrupts_disable(dev);

	/* unरेजिस्टर */
	tw5864_video_fini(dev);

	/* release resources */
	iounmap(dev->mmio);
	release_mem_region(pci_resource_start(pci_dev, 0),
			   pci_resource_len(pci_dev, 0));

	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
	devm_kमुक्त(&pci_dev->dev, dev);
पूर्ण

अटल काष्ठा pci_driver tw5864_pci_driver = अणु
	.name = "tw5864",
	.id_table = tw5864_pci_tbl,
	.probe = tw5864_initdev,
	.हटाओ = tw5864_finidev,
पूर्ण;

module_pci_driver(tw5864_pci_driver);
