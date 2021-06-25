<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005-2006 Micronas USA Inc.
 */

#समावेश "saa7134.h"
#समावेश "saa7134-reg.h"

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/mm.h>
#समावेश <linux/usb.h>
#समावेश <linux/i2c.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "go7007-priv.h"

/*#घोषणा GO7007_HPI_DEBUG*/

क्रमागत hpi_address अणु
	HPI_ADDR_VIDEO_BUFFER = 0xe4,
	HPI_ADDR_INIT_BUFFER = 0xea,
	HPI_ADDR_INTR_RET_VALUE = 0xee,
	HPI_ADDR_INTR_RET_DATA = 0xec,
	HPI_ADDR_INTR_STATUS = 0xf4,
	HPI_ADDR_INTR_WR_PARAM = 0xf6,
	HPI_ADDR_INTR_WR_INDEX = 0xf8,
पूर्ण;

क्रमागत gpio_command अणु
	GPIO_COMMAND_RESET = 0x00, /* 000b */
	GPIO_COMMAND_REQ1  = 0x04, /* 001b */
	GPIO_COMMAND_WRITE = 0x20, /* 010b */
	GPIO_COMMAND_REQ2  = 0x24, /* 011b */
	GPIO_COMMAND_READ  = 0x80, /* 100b */
	GPIO_COMMAND_VIDEO = 0x84, /* 101b */
	GPIO_COMMAND_IDLE  = 0xA0, /* 110b */
	GPIO_COMMAND_ADDR  = 0xA4, /* 111b */
पूर्ण;

काष्ठा saa7134_go7007 अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा saa7134_dev *dev;
	u8 *top;
	u8 *bottom;
	dma_addr_t top_dma;
	dma_addr_t bottom_dma;
पूर्ण;

अटल अंतरभूत काष्ठा saa7134_go7007 *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा saa7134_go7007, sd);
पूर्ण

अटल स्थिर काष्ठा go7007_board_info board_voyager = अणु
	.flags		 = 0,
	.sensor_flags	 = GO7007_SENSOR_656 |
				GO7007_SENSOR_VALID_ENABLE |
				GO7007_SENSOR_TV |
				GO7007_SENSOR_VBI,
	.audio_flags	= GO7007_AUDIO_I2S_MODE_1 |
				GO7007_AUDIO_WORD_16,
	.audio_rate	 = 48000,
	.audio_bclk_भाग	 = 8,
	.audio_मुख्य_भाग	 = 2,
	.hpi_buffer_cap  = 7,
	.num_inमाला_दो	 = 1,
	.inमाला_दो		 = अणु
		अणु
			.name		= "SAA7134",
		पूर्ण,
	पूर्ण,
पूर्ण;

/********************* Driver क्रम GPIO HPI पूर्णांकerface *********************/

अटल पूर्णांक gpio_ग_लिखो(काष्ठा saa7134_dev *dev, u8 addr, u16 data)
अणु
	saa_ग_लिखोb(SAA7134_GPIO_GPMODE0, 0xff);

	/* Write HPI address */
	saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS0, addr);
	saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_ADDR);
	saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_IDLE);

	/* Write low byte */
	saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS0, data & 0xff);
	saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_WRITE);
	saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_IDLE);

	/* Write high byte */
	saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS0, data >> 8);
	saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_WRITE);
	saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_IDLE);

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_पढ़ो(काष्ठा saa7134_dev *dev, u8 addr, u16 *data)
अणु
	saa_ग_लिखोb(SAA7134_GPIO_GPMODE0, 0xff);

	/* Write HPI address */
	saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS0, addr);
	saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_ADDR);
	saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_IDLE);

	saa_ग_लिखोb(SAA7134_GPIO_GPMODE0, 0x00);

	/* Read low byte */
	saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_READ);
	saa_clearb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);
	saa_setb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);
	*data = saa_पढ़ोb(SAA7134_GPIO_GPSTATUS0);
	saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_IDLE);

	/* Read high byte */
	saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_READ);
	saa_clearb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);
	saa_setb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);
	*data |= saa_पढ़ोb(SAA7134_GPIO_GPSTATUS0) << 8;
	saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_IDLE);

	वापस 0;
पूर्ण

अटल पूर्णांक saa7134_go7007_पूर्णांकerface_reset(काष्ठा go7007 *go)
अणु
	काष्ठा saa7134_go7007 *saa = go->hpi_context;
	काष्ठा saa7134_dev *dev = saa->dev;
	u16 पूर्णांकr_val, पूर्णांकr_data;
	पूर्णांक count = 20;

	saa_clearb(SAA7134_TS_PARALLEL, 0x80); /* Disable TS पूर्णांकerface */
	saa_ग_लिखोb(SAA7134_GPIO_GPMODE2, 0xa4);
	saa_ग_लिखोb(SAA7134_GPIO_GPMODE0, 0xff);

	saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_REQ1);
	saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_RESET);
	msleep(1);
	saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_REQ1);
	saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_REQ2);
	msleep(10);

	saa_clearb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);
	saa_setb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);

	saa_पढ़ोb(SAA7134_GPIO_GPSTATUS2);
	/*pr_debug("status is %s\n", saa_पढ़ोb(SAA7134_GPIO_GPSTATUS2) & 0x40 ? "OK" : "not OK"); */

	/* enter command mode...(?) */
	saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_REQ1);
	saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_REQ2);

	करो अणु
		saa_clearb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);
		saa_setb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPRESCAN);
		saa_पढ़ोb(SAA7134_GPIO_GPSTATUS2);
		/*pr_info("gpio is %08x\n", saa_पढ़ोl(SAA7134_GPIO_GPSTATUS0 >> 2)); */
	पूर्ण जबतक (--count > 0);

	/* Wait क्रम an पूर्णांकerrupt to indicate successful hardware reset */
	अगर (go7007_पढ़ो_पूर्णांकerrupt(go, &पूर्णांकr_val, &पूर्णांकr_data) < 0 ||
			(पूर्णांकr_val & ~0x1) != 0x55aa) अणु
		pr_err("saa7134-go7007: unable to reset the GO7007\n");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक saa7134_go7007_ग_लिखो_पूर्णांकerrupt(काष्ठा go7007 *go, पूर्णांक addr, पूर्णांक data)
अणु
	काष्ठा saa7134_go7007 *saa = go->hpi_context;
	काष्ठा saa7134_dev *dev = saa->dev;
	पूर्णांक i;
	u16 status_reg;

#अगर_घोषित GO7007_HPI_DEBUG
	pr_debug("saa7134-go7007: WriteInterrupt: %04x %04x\n", addr, data);
#पूर्ण_अगर

	क्रम (i = 0; i < 100; ++i) अणु
		gpio_पढ़ो(dev, HPI_ADDR_INTR_STATUS, &status_reg);
		अगर (!(status_reg & 0x0010))
			अवरोध;
		msleep(10);
	पूर्ण
	अगर (i == 100) अणु
		pr_err("saa7134-go7007: device is hung, status reg = 0x%04x\n",
			status_reg);
		वापस -1;
	पूर्ण
	gpio_ग_लिखो(dev, HPI_ADDR_INTR_WR_PARAM, data);
	gpio_ग_लिखो(dev, HPI_ADDR_INTR_WR_INDEX, addr);

	वापस 0;
पूर्ण

अटल पूर्णांक saa7134_go7007_पढ़ो_पूर्णांकerrupt(काष्ठा go7007 *go)
अणु
	काष्ठा saa7134_go7007 *saa = go->hpi_context;
	काष्ठा saa7134_dev *dev = saa->dev;

	/* XXX we need to रुको अगर there is no पूर्णांकerrupt available */
	go->पूर्णांकerrupt_available = 1;
	gpio_पढ़ो(dev, HPI_ADDR_INTR_RET_VALUE, &go->पूर्णांकerrupt_value);
	gpio_पढ़ो(dev, HPI_ADDR_INTR_RET_DATA, &go->पूर्णांकerrupt_data);
#अगर_घोषित GO7007_HPI_DEBUG
	pr_debug("saa7134-go7007: ReadInterrupt: %04x %04x\n",
			go->पूर्णांकerrupt_value, go->पूर्णांकerrupt_data);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम saa7134_go7007_irq_ts_करोne(काष्ठा saa7134_dev *dev,
						अचिन्हित दीर्घ status)
अणु
	काष्ठा go7007 *go = video_get_drvdata(dev->empress_dev);
	काष्ठा saa7134_go7007 *saa = go->hpi_context;

	अगर (!vb2_is_streaming(&go->vidq))
		वापस;
	अगर (0 != (status & 0x000f0000))
		pr_debug("saa7134-go7007: irq: lost %ld\n",
				(status >> 16) & 0x0f);
	अगर (status & 0x100000) अणु
		dma_sync_single_क्रम_cpu(&dev->pci->dev,
					saa->bottom_dma, PAGE_SIZE, DMA_FROM_DEVICE);
		go7007_parse_video_stream(go, saa->bottom, PAGE_SIZE);
		saa_ग_लिखोl(SAA7134_RS_BA2(5), saa->bottom_dma);
	पूर्ण अन्यथा अणु
		dma_sync_single_क्रम_cpu(&dev->pci->dev,
					saa->top_dma, PAGE_SIZE, DMA_FROM_DEVICE);
		go7007_parse_video_stream(go, saa->top, PAGE_SIZE);
		saa_ग_लिखोl(SAA7134_RS_BA1(5), saa->top_dma);
	पूर्ण
पूर्ण

अटल पूर्णांक saa7134_go7007_stream_start(काष्ठा go7007 *go)
अणु
	काष्ठा saa7134_go7007 *saa = go->hpi_context;
	काष्ठा saa7134_dev *dev = saa->dev;

	saa->top_dma = dma_map_page(&dev->pci->dev, virt_to_page(saa->top),
			0, PAGE_SIZE, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&dev->pci->dev, saa->top_dma))
		वापस -ENOMEM;
	saa->bottom_dma = dma_map_page(&dev->pci->dev,
			virt_to_page(saa->bottom),
			0, PAGE_SIZE, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&dev->pci->dev, saa->bottom_dma)) अणु
		dma_unmap_page(&dev->pci->dev, saa->top_dma, PAGE_SIZE,
				DMA_FROM_DEVICE);
		वापस -ENOMEM;
	पूर्ण

	saa_ग_लिखोl(SAA7134_VIDEO_PORT_CTRL0 >> 2, 0xA300B000);
	saa_ग_लिखोl(SAA7134_VIDEO_PORT_CTRL4 >> 2, 0x40000200);

	/* Set HPI पूर्णांकerface क्रम video */
	saa_ग_लिखोb(SAA7134_GPIO_GPMODE0, 0xff);
	saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS0, HPI_ADDR_VIDEO_BUFFER);
	saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_ADDR);
	saa_ग_लिखोb(SAA7134_GPIO_GPMODE0, 0x00);

	/* Enable TS पूर्णांकerface */
	saa_ग_लिखोb(SAA7134_TS_PARALLEL, 0xe6);

	/* Reset TS पूर्णांकerface */
	saa_setb(SAA7134_TS_SERIAL1, 0x01);
	saa_clearb(SAA7134_TS_SERIAL1, 0x01);

	/* Set up transfer block size */
	saa_ग_लिखोb(SAA7134_TS_PARALLEL_SERIAL, 128 - 1);
	saa_ग_लिखोb(SAA7134_TS_DMA0, ((PAGE_SIZE >> 7) - 1) & 0xff);
	saa_ग_लिखोb(SAA7134_TS_DMA1, (PAGE_SIZE >> 15) & 0xff);
	saa_ग_लिखोb(SAA7134_TS_DMA2, (PAGE_SIZE >> 31) & 0x3f);

	/* Enable video streaming mode */
	saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_VIDEO);

	saa_ग_लिखोl(SAA7134_RS_BA1(5), saa->top_dma);
	saa_ग_लिखोl(SAA7134_RS_BA2(5), saa->bottom_dma);
	saa_ग_लिखोl(SAA7134_RS_PITCH(5), 128);
	saa_ग_लिखोl(SAA7134_RS_CONTROL(5), SAA7134_RS_CONTROL_BURST_MAX);

	/* Enable TS FIFO */
	saa_setl(SAA7134_MAIN_CTRL, SAA7134_MAIN_CTRL_TE5);

	/* Enable DMA IRQ */
	saa_setl(SAA7134_IRQ1,
			SAA7134_IRQ1_INTE_RA2_1 | SAA7134_IRQ1_INTE_RA2_0);

	वापस 0;
पूर्ण

अटल पूर्णांक saa7134_go7007_stream_stop(काष्ठा go7007 *go)
अणु
	काष्ठा saa7134_go7007 *saa = go->hpi_context;
	काष्ठा saa7134_dev *dev;

	अगर (!saa)
		वापस -EINVAL;
	dev = saa->dev;
	अगर (!dev)
		वापस -EINVAL;

	/* Shut करोwn TS FIFO */
	saa_clearl(SAA7134_MAIN_CTRL, SAA7134_MAIN_CTRL_TE5);

	/* Disable DMA IRQ */
	saa_clearl(SAA7134_IRQ1,
			SAA7134_IRQ1_INTE_RA2_1 | SAA7134_IRQ1_INTE_RA2_0);

	/* Disable TS पूर्णांकerface */
	saa_clearb(SAA7134_TS_PARALLEL, 0x80);

	dma_unmap_page(&dev->pci->dev, saa->top_dma, PAGE_SIZE,
			DMA_FROM_DEVICE);
	dma_unmap_page(&dev->pci->dev, saa->bottom_dma, PAGE_SIZE,
			DMA_FROM_DEVICE);

	वापस 0;
पूर्ण

अटल पूर्णांक saa7134_go7007_send_firmware(काष्ठा go7007 *go, u8 *data, पूर्णांक len)
अणु
	काष्ठा saa7134_go7007 *saa = go->hpi_context;
	काष्ठा saa7134_dev *dev = saa->dev;
	u16 status_reg;
	पूर्णांक i;

#अगर_घोषित GO7007_HPI_DEBUG
	pr_debug("saa7134-go7007: DownloadBuffer sending %d bytes\n", len);
#पूर्ण_अगर

	जबतक (len > 0) अणु
		i = len > 64 ? 64 : len;
		saa_ग_लिखोb(SAA7134_GPIO_GPMODE0, 0xff);
		saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS0, HPI_ADDR_INIT_BUFFER);
		saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_ADDR);
		saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_IDLE);
		जबतक (i-- > 0) अणु
			saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS0, *data);
			saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_WRITE);
			saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS2, GPIO_COMMAND_IDLE);
			++data;
			--len;
		पूर्ण
		क्रम (i = 0; i < 100; ++i) अणु
			gpio_पढ़ो(dev, HPI_ADDR_INTR_STATUS, &status_reg);
			अगर (!(status_reg & 0x0002))
				अवरोध;
		पूर्ण
		अगर (i == 100) अणु
			pr_err("saa7134-go7007: device is hung, status reg = 0x%04x\n",
			       status_reg);
			वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा go7007_hpi_ops saa7134_go7007_hpi_ops = अणु
	.पूर्णांकerface_reset	= saa7134_go7007_पूर्णांकerface_reset,
	.ग_लिखो_पूर्णांकerrupt	= saa7134_go7007_ग_लिखो_पूर्णांकerrupt,
	.पढ़ो_पूर्णांकerrupt		= saa7134_go7007_पढ़ो_पूर्णांकerrupt,
	.stream_start		= saa7134_go7007_stream_start,
	.stream_stop		= saa7134_go7007_stream_stop,
	.send_firmware		= saa7134_go7007_send_firmware,
पूर्ण;
MODULE_FIRMWARE("go7007/go7007tv.bin");

/* --------------------------------------------------------------------------*/

अटल पूर्णांक saa7134_go7007_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id norm)
अणु
#अगर 0
	काष्ठा saa7134_go7007 *saa = to_state(sd);
	काष्ठा saa7134_dev *dev = saa->dev;

	वापस saa7134_s_std_पूर्णांकernal(dev, शून्य, norm);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops saa7134_go7007_video_ops = अणु
	.s_std = saa7134_go7007_s_std,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops saa7134_go7007_sd_ops = अणु
	.video = &saa7134_go7007_video_ops,
पूर्ण;

/* --------------------------------------------------------------------------*/


/********************* Add/हटाओ functions *********************/

अटल पूर्णांक saa7134_go7007_init(काष्ठा saa7134_dev *dev)
अणु
	काष्ठा go7007 *go;
	काष्ठा saa7134_go7007 *saa;
	काष्ठा v4l2_subdev *sd;

	pr_debug("saa7134-go7007: probing new SAA713X board\n");

	go = go7007_alloc(&board_voyager, &dev->pci->dev);
	अगर (go == शून्य)
		वापस -ENOMEM;

	saa = kzalloc(माप(काष्ठा saa7134_go7007), GFP_KERNEL);
	अगर (saa == शून्य) अणु
		kमुक्त(go);
		वापस -ENOMEM;
	पूर्ण

	go->board_id = GO7007_BOARDID_PCI_VOYAGER;
	snम_लिखो(go->bus_info, माप(go->bus_info), "PCI:%s", pci_name(dev->pci));
	strscpy(go->name, saa7134_boards[dev->board].name, माप(go->name));
	go->hpi_ops = &saa7134_go7007_hpi_ops;
	go->hpi_context = saa;
	saa->dev = dev;

	/* Init the subdevice पूर्णांकerface */
	sd = &saa->sd;
	v4l2_subdev_init(sd, &saa7134_go7007_sd_ops);
	v4l2_set_subdevdata(sd, saa);
	strscpy(sd->name, "saa7134-go7007", माप(sd->name));

	/* Allocate a couple pages क्रम receiving the compressed stream */
	saa->top = (u8 *)get_zeroed_page(GFP_KERNEL);
	अगर (!saa->top)
		जाओ allocfail;
	saa->bottom = (u8 *)get_zeroed_page(GFP_KERNEL);
	अगर (!saa->bottom)
		जाओ allocfail;

	/* Boot the GO7007 */
	अगर (go7007_boot_encoder(go, go->board_info->flags &
					GO7007_BOARD_USE_ONBOARD_I2C) < 0)
		जाओ allocfail;

	/* Do any final GO7007 initialization, then रेजिस्टर the
	 * V4L2 and ALSA पूर्णांकerfaces */
	अगर (go7007_रेजिस्टर_encoder(go, go->board_info->num_i2c_devs) < 0)
		जाओ allocfail;

	/* Register the subdevice पूर्णांकerface with the go7007 device */
	अगर (v4l2_device_रेजिस्टर_subdev(&go->v4l2_dev, sd) < 0)
		pr_info("saa7134-go7007: register subdev failed\n");

	dev->empress_dev = &go->vdev;

	go->status = STATUS_ONLINE;
	वापस 0;

allocfail:
	अगर (saa->top)
		मुक्त_page((अचिन्हित दीर्घ)saa->top);
	अगर (saa->bottom)
		मुक्त_page((अचिन्हित दीर्घ)saa->bottom);
	kमुक्त(saa);
	kमुक्त(go);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक saa7134_go7007_fini(काष्ठा saa7134_dev *dev)
अणु
	काष्ठा go7007 *go;
	काष्ठा saa7134_go7007 *saa;

	अगर (शून्य == dev->empress_dev)
		वापस 0;

	go = video_get_drvdata(dev->empress_dev);
	अगर (go->audio_enabled)
		go7007_snd_हटाओ(go);

	saa = go->hpi_context;
	go->status = STATUS_SHUTDOWN;
	मुक्त_page((अचिन्हित दीर्घ)saa->top);
	मुक्त_page((अचिन्हित दीर्घ)saa->bottom);
	v4l2_device_unरेजिस्टर_subdev(&saa->sd);
	kमुक्त(saa);
	vb2_video_unरेजिस्टर_device(&go->vdev);

	v4l2_device_put(&go->v4l2_dev);
	dev->empress_dev = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा saa7134_mpeg_ops saa7134_go7007_ops = अणु
	.type          = SAA7134_MPEG_GO7007,
	.init          = saa7134_go7007_init,
	.fini          = saa7134_go7007_fini,
	.irq_ts_करोne   = saa7134_go7007_irq_ts_करोne,
पूर्ण;

अटल पूर्णांक __init saa7134_go7007_mod_init(व्योम)
अणु
	वापस saa7134_ts_रेजिस्टर(&saa7134_go7007_ops);
पूर्ण

अटल व्योम __निकास saa7134_go7007_mod_cleanup(व्योम)
अणु
	saa7134_ts_unरेजिस्टर(&saa7134_go7007_ops);
पूर्ण

module_init(saa7134_go7007_mod_init);
module_निकास(saa7134_go7007_mod_cleanup);

MODULE_LICENSE("GPL v2");
