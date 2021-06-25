<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * USB SD Host Controller (USHC) controller driver.
 *
 * Copyright (C) 2010 Cambridge Silicon Radio Ltd.
 *
 * Notes:
 *   - Only version 2 devices are supported.
 *   - Version 2 devices only support SDIO cards/devices (R2 response is
 *     unsupported).
 *
 * References:
 *   [USHC] USB SD Host Controller specअगरication (CS-118793-SP)
 */
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/mmc/host.h>

क्रमागत ushc_request अणु
	USHC_GET_CAPS  = 0x00,
	USHC_HOST_CTRL = 0x01,
	USHC_PWR_CTRL  = 0x02,
	USHC_CLK_FREQ  = 0x03,
	USHC_EXEC_CMD  = 0x04,
	USHC_READ_RESP = 0x05,
	USHC_RESET     = 0x06,
पूर्ण;

क्रमागत ushc_request_type अणु
	USHC_GET_CAPS_TYPE  = USB_सूची_IN  | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
	USHC_HOST_CTRL_TYPE = USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
	USHC_PWR_CTRL_TYPE  = USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
	USHC_CLK_FREQ_TYPE  = USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
	USHC_EXEC_CMD_TYPE  = USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
	USHC_READ_RESP_TYPE = USB_सूची_IN  | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
	USHC_RESET_TYPE     = USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
पूर्ण;

#घोषणा USHC_GET_CAPS_VERSION_MASK 0xff
#घोषणा USHC_GET_CAPS_3V3      (1 << 8)
#घोषणा USHC_GET_CAPS_3V0      (1 << 9)
#घोषणा USHC_GET_CAPS_1V8      (1 << 10)
#घोषणा USHC_GET_CAPS_HIGH_SPD (1 << 16)

#घोषणा USHC_HOST_CTRL_4BIT     (1 << 1)
#घोषणा USHC_HOST_CTRL_HIGH_SPD (1 << 0)

#घोषणा USHC_PWR_CTRL_OFF 0x00
#घोषणा USHC_PWR_CTRL_3V3 0x01
#घोषणा USHC_PWR_CTRL_3V0 0x02
#घोषणा USHC_PWR_CTRL_1V8 0x03

#घोषणा USHC_READ_RESP_BUSY        (1 << 4)
#घोषणा USHC_READ_RESP_ERR_TIMEOUT (1 << 3)
#घोषणा USHC_READ_RESP_ERR_CRC     (1 << 2)
#घोषणा USHC_READ_RESP_ERR_DAT     (1 << 1)
#घोषणा USHC_READ_RESP_ERR_CMD     (1 << 0)
#घोषणा USHC_READ_RESP_ERR_MASK    0x0f

काष्ठा ushc_cbw अणु
	__u8 signature;
	__u8 cmd_idx;
	__le16 block_size;
	__le32 arg;
पूर्ण __attribute__((packed));

#घोषणा USHC_CBW_SIGNATURE 'C'

काष्ठा ushc_csw अणु
	__u8 signature;
	__u8 status;
	__le32 response;
पूर्ण __attribute__((packed));

#घोषणा USHC_CSW_SIGNATURE 'S'

काष्ठा ushc_पूर्णांक_data अणु
	u8 status;
	u8 reserved[3];
पूर्ण;

#घोषणा USHC_INT_STATUS_SDIO_INT     (1 << 1)
#घोषणा USHC_INT_STATUS_CARD_PRESENT (1 << 0)


काष्ठा ushc_data अणु
	काष्ठा usb_device *usb_dev;
	काष्ठा mmc_host *mmc;

	काष्ठा urb *पूर्णांक_urb;
	काष्ठा ushc_पूर्णांक_data *पूर्णांक_data;

	काष्ठा urb *cbw_urb;
	काष्ठा ushc_cbw *cbw;

	काष्ठा urb *data_urb;

	काष्ठा urb *csw_urb;
	काष्ठा ushc_csw *csw;

	spinlock_t lock;
	काष्ठा mmc_request *current_req;
	u32 caps;
	u16 host_ctrl;
	अचिन्हित दीर्घ flags;
	u8 last_status;
	पूर्णांक घड़ी_freq;
पूर्ण;

#घोषणा DISCONNECTED    0
#घोषणा INT_EN          1
#घोषणा IGNORE_NEXT_INT 2

अटल व्योम data_callback(काष्ठा urb *urb);

अटल पूर्णांक ushc_hw_reset(काष्ठा ushc_data *ushc)
अणु
	वापस usb_control_msg(ushc->usb_dev, usb_sndctrlpipe(ushc->usb_dev, 0),
			       USHC_RESET, USHC_RESET_TYPE,
			       0, 0, शून्य, 0, 100);
पूर्ण

अटल पूर्णांक ushc_hw_get_caps(काष्ठा ushc_data *ushc)
अणु
	पूर्णांक ret;
	पूर्णांक version;

	ret = usb_control_msg(ushc->usb_dev, usb_rcvctrlpipe(ushc->usb_dev, 0),
			      USHC_GET_CAPS, USHC_GET_CAPS_TYPE,
			      0, 0, &ushc->caps, माप(ushc->caps), 100);
	अगर (ret < 0)
		वापस ret;

	ushc->caps = le32_to_cpu(ushc->caps);

	version = ushc->caps & USHC_GET_CAPS_VERSION_MASK;
	अगर (version != 0x02) अणु
		dev_err(&ushc->usb_dev->dev, "controller version %d is not supported\n", version);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ushc_hw_set_host_ctrl(काष्ठा ushc_data *ushc, u16 mask, u16 val)
अणु
	u16 host_ctrl;
	पूर्णांक ret;

	host_ctrl = (ushc->host_ctrl & ~mask) | val;
	ret = usb_control_msg(ushc->usb_dev, usb_sndctrlpipe(ushc->usb_dev, 0),
			      USHC_HOST_CTRL, USHC_HOST_CTRL_TYPE,
			      host_ctrl, 0, शून्य, 0, 100);
	अगर (ret < 0)
		वापस ret;
	ushc->host_ctrl = host_ctrl;
	वापस 0;
पूर्ण

अटल व्योम पूर्णांक_callback(काष्ठा urb *urb)
अणु
	काष्ठा ushc_data *ushc = urb->context;
	u8 status, last_status;

	अगर (urb->status < 0)
		वापस;

	status = ushc->पूर्णांक_data->status;
	last_status = ushc->last_status;
	ushc->last_status = status;

	/*
	 * Ignore the card पूर्णांकerrupt status on पूर्णांकerrupt transfers that
	 * were submitted जबतक card पूर्णांकerrupts where disabled.
	 *
	 * This aव्योम occasional spurious पूर्णांकerrupts when enabling
	 * पूर्णांकerrupts immediately after clearing the source on the card.
	 */

	अगर (!test_and_clear_bit(IGNORE_NEXT_INT, &ushc->flags)
	    && test_bit(INT_EN, &ushc->flags)
	    && status & USHC_INT_STATUS_SDIO_INT) अणु
		mmc_संकेत_sdio_irq(ushc->mmc);
	पूर्ण

	अगर ((status ^ last_status) & USHC_INT_STATUS_CARD_PRESENT)
		mmc_detect_change(ushc->mmc, msecs_to_jअगरfies(100));

	अगर (!test_bit(INT_EN, &ushc->flags))
		set_bit(IGNORE_NEXT_INT, &ushc->flags);
	usb_submit_urb(ushc->पूर्णांक_urb, GFP_ATOMIC);
पूर्ण

अटल व्योम cbw_callback(काष्ठा urb *urb)
अणु
	काष्ठा ushc_data *ushc = urb->context;

	अगर (urb->status != 0) अणु
		usb_unlink_urb(ushc->data_urb);
		usb_unlink_urb(ushc->csw_urb);
	पूर्ण
पूर्ण

अटल व्योम data_callback(काष्ठा urb *urb)
अणु
	काष्ठा ushc_data *ushc = urb->context;

	अगर (urb->status != 0)
		usb_unlink_urb(ushc->csw_urb);
पूर्ण

अटल व्योम csw_callback(काष्ठा urb *urb)
अणु
	काष्ठा ushc_data *ushc = urb->context;
	काष्ठा mmc_request *req = ushc->current_req;
	पूर्णांक status;

	status = ushc->csw->status;

	अगर (urb->status != 0) अणु
		req->cmd->error = urb->status;
	पूर्ण अन्यथा अगर (status & USHC_READ_RESP_ERR_CMD) अणु
		अगर (status & USHC_READ_RESP_ERR_CRC)
			req->cmd->error = -EIO;
		अन्यथा
			req->cmd->error = -ETIMEDOUT;
	पूर्ण
	अगर (req->data) अणु
		अगर (status & USHC_READ_RESP_ERR_DAT) अणु
			अगर (status & USHC_READ_RESP_ERR_CRC)
				req->data->error = -EIO;
			अन्यथा
				req->data->error = -ETIMEDOUT;
			req->data->bytes_xfered = 0;
		पूर्ण अन्यथा अणु
			req->data->bytes_xfered = req->data->blksz * req->data->blocks;
		पूर्ण
	पूर्ण

	req->cmd->resp[0] = le32_to_cpu(ushc->csw->response);

	mmc_request_करोne(ushc->mmc, req);
पूर्ण

अटल व्योम ushc_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *req)
अणु
	काष्ठा ushc_data *ushc = mmc_priv(mmc);
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ushc->lock, flags);

	अगर (test_bit(DISCONNECTED, &ushc->flags)) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	/* Version 2 firmware करोesn't support the R2 response क्रमmat. */
	अगर (req->cmd->flags & MMC_RSP_136) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* The Astoria's data FIFOs don't work with घड़ी speeds < 5MHz so
	   limit commands with data to 6MHz or more. */
	अगर (req->data && ushc->घड़ी_freq < 6000000) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ushc->current_req = req;

	/* Start cmd with CBW. */
	ushc->cbw->cmd_idx = cpu_to_le16(req->cmd->opcode);
	अगर (req->data)
		ushc->cbw->block_size = cpu_to_le16(req->data->blksz);
	अन्यथा
		ushc->cbw->block_size = 0;
	ushc->cbw->arg = cpu_to_le32(req->cmd->arg);

	ret = usb_submit_urb(ushc->cbw_urb, GFP_ATOMIC);
	अगर (ret < 0)
		जाओ out;

	/* Submit data (अगर any). */
	अगर (req->data) अणु
		काष्ठा mmc_data *data = req->data;
		पूर्णांक pipe;

		अगर (data->flags & MMC_DATA_READ)
			pipe = usb_rcvbulkpipe(ushc->usb_dev, 6);
		अन्यथा
			pipe = usb_sndbulkpipe(ushc->usb_dev, 2);

		usb_fill_bulk_urb(ushc->data_urb, ushc->usb_dev, pipe,
				  शून्य, data->sg->length,
				  data_callback, ushc);
		ushc->data_urb->num_sgs = 1;
		ushc->data_urb->sg = data->sg;
		ret = usb_submit_urb(ushc->data_urb, GFP_ATOMIC);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	/* Submit CSW. */
	ret = usb_submit_urb(ushc->csw_urb, GFP_ATOMIC);

out:
	spin_unlock_irqrestore(&ushc->lock, flags);
	अगर (ret < 0) अणु
		usb_unlink_urb(ushc->cbw_urb);
		usb_unlink_urb(ushc->data_urb);
		req->cmd->error = ret;
		mmc_request_करोne(mmc, req);
	पूर्ण
पूर्ण

अटल पूर्णांक ushc_set_घातer(काष्ठा ushc_data *ushc, अचिन्हित अक्षर घातer_mode)
अणु
	u16 voltage;

	चयन (घातer_mode) अणु
	हाल MMC_POWER_OFF:
		voltage = USHC_PWR_CTRL_OFF;
		अवरोध;
	हाल MMC_POWER_UP:
	हाल MMC_POWER_ON:
		voltage = USHC_PWR_CTRL_3V3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस usb_control_msg(ushc->usb_dev, usb_sndctrlpipe(ushc->usb_dev, 0),
			       USHC_PWR_CTRL, USHC_PWR_CTRL_TYPE,
			       voltage, 0, शून्य, 0, 100);
पूर्ण

अटल पूर्णांक ushc_set_bus_width(काष्ठा ushc_data *ushc, पूर्णांक bus_width)
अणु
	वापस ushc_hw_set_host_ctrl(ushc, USHC_HOST_CTRL_4BIT,
				     bus_width == 4 ? USHC_HOST_CTRL_4BIT : 0);
पूर्ण

अटल पूर्णांक ushc_set_bus_freq(काष्ठा ushc_data *ushc, पूर्णांक clk, bool enable_hs)
अणु
	पूर्णांक ret;

	/* Hardware can't detect पूर्णांकerrupts जबतक the घड़ी is off. */
	अगर (clk == 0)
		clk = 400000;

	ret = ushc_hw_set_host_ctrl(ushc, USHC_HOST_CTRL_HIGH_SPD,
				    enable_hs ? USHC_HOST_CTRL_HIGH_SPD : 0);
	अगर (ret < 0)
		वापस ret;

	ret = usb_control_msg(ushc->usb_dev, usb_sndctrlpipe(ushc->usb_dev, 0),
			      USHC_CLK_FREQ, USHC_CLK_FREQ_TYPE,
			      clk & 0xffff, (clk >> 16) & 0xffff, शून्य, 0, 100);
	अगर (ret < 0)
		वापस ret;

	ushc->घड़ी_freq = clk;
	वापस 0;
पूर्ण

अटल व्योम ushc_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा ushc_data *ushc = mmc_priv(mmc);

	ushc_set_घातer(ushc, ios->घातer_mode);
	ushc_set_bus_width(ushc, 1 << ios->bus_width);
	ushc_set_bus_freq(ushc, ios->घड़ी, ios->timing == MMC_TIMING_SD_HS);
पूर्ण

अटल पूर्णांक ushc_get_cd(काष्ठा mmc_host *mmc)
अणु
	काष्ठा ushc_data *ushc = mmc_priv(mmc);

	वापस !!(ushc->last_status & USHC_INT_STATUS_CARD_PRESENT);
पूर्ण

अटल व्योम ushc_enable_sdio_irq(काष्ठा mmc_host *mmc, पूर्णांक enable)
अणु
	काष्ठा ushc_data *ushc = mmc_priv(mmc);

	अगर (enable)
		set_bit(INT_EN, &ushc->flags);
	अन्यथा
		clear_bit(INT_EN, &ushc->flags);
पूर्ण

अटल व्योम ushc_clean_up(काष्ठा ushc_data *ushc)
अणु
	usb_मुक्त_urb(ushc->पूर्णांक_urb);
	usb_मुक्त_urb(ushc->csw_urb);
	usb_मुक्त_urb(ushc->data_urb);
	usb_मुक्त_urb(ushc->cbw_urb);

	kमुक्त(ushc->पूर्णांक_data);
	kमुक्त(ushc->cbw);
	kमुक्त(ushc->csw);

	mmc_मुक्त_host(ushc->mmc);
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops ushc_ops = अणु
	.request         = ushc_request,
	.set_ios         = ushc_set_ios,
	.get_cd          = ushc_get_cd,
	.enable_sdio_irq = ushc_enable_sdio_irq,
पूर्ण;

अटल पूर्णांक ushc_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा mmc_host *mmc;
	काष्ठा ushc_data *ushc;
	पूर्णांक ret;

	अगर (पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs < 1)
		वापस -ENODEV;

	mmc = mmc_alloc_host(माप(काष्ठा ushc_data), &पूर्णांकf->dev);
	अगर (mmc == शून्य)
		वापस -ENOMEM;
	ushc = mmc_priv(mmc);
	usb_set_पूर्णांकfdata(पूर्णांकf, ushc);

	ushc->usb_dev = usb_dev;
	ushc->mmc = mmc;

	spin_lock_init(&ushc->lock);

	ret = ushc_hw_reset(ushc);
	अगर (ret < 0)
		जाओ err;

	/* Read capabilities. */
	ret = ushc_hw_get_caps(ushc);
	अगर (ret < 0)
		जाओ err;

	mmc->ops = &ushc_ops;

	mmc->f_min = 400000;
	mmc->f_max = 50000000;
	mmc->ocr_avail = MMC_VDD_32_33 | MMC_VDD_33_34;
	mmc->caps = MMC_CAP_4_BIT_DATA | MMC_CAP_SDIO_IRQ;
	mmc->caps |= (ushc->caps & USHC_GET_CAPS_HIGH_SPD) ? MMC_CAP_SD_HIGHSPEED : 0;

	mmc->max_seg_size  = 512*511;
	mmc->max_segs      = 1;
	mmc->max_req_size  = 512*511;
	mmc->max_blk_size  = 512;
	mmc->max_blk_count = 511;

	ushc->पूर्णांक_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (ushc->पूर्णांक_urb == शून्य) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	ushc->पूर्णांक_data = kzalloc(माप(काष्ठा ushc_पूर्णांक_data), GFP_KERNEL);
	अगर (ushc->पूर्णांक_data == शून्य) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	usb_fill_पूर्णांक_urb(ushc->पूर्णांक_urb, ushc->usb_dev,
			 usb_rcvपूर्णांकpipe(usb_dev,
					पूर्णांकf->cur_altsetting->endpoपूर्णांक[0].desc.bEndpoपूर्णांकAddress),
			 ushc->पूर्णांक_data, माप(काष्ठा ushc_पूर्णांक_data),
			 पूर्णांक_callback, ushc,
			 पूर्णांकf->cur_altsetting->endpoपूर्णांक[0].desc.bInterval);

	ushc->cbw_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (ushc->cbw_urb == शून्य) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	ushc->cbw = kzalloc(माप(काष्ठा ushc_cbw), GFP_KERNEL);
	अगर (ushc->cbw == शून्य) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	ushc->cbw->signature = USHC_CBW_SIGNATURE;

	usb_fill_bulk_urb(ushc->cbw_urb, ushc->usb_dev, usb_sndbulkpipe(usb_dev, 2),
			  ushc->cbw, माप(काष्ठा ushc_cbw),
			  cbw_callback, ushc);

	ushc->data_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (ushc->data_urb == शून्य) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ushc->csw_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (ushc->csw_urb == शून्य) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	ushc->csw = kzalloc(माप(काष्ठा ushc_csw), GFP_KERNEL);
	अगर (ushc->csw == शून्य) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	usb_fill_bulk_urb(ushc->csw_urb, ushc->usb_dev, usb_rcvbulkpipe(usb_dev, 6),
			  ushc->csw, माप(काष्ठा ushc_csw),
			  csw_callback, ushc);

	ret = mmc_add_host(ushc->mmc);
	अगर (ret)
		जाओ err;

	ret = usb_submit_urb(ushc->पूर्णांक_urb, GFP_KERNEL);
	अगर (ret < 0) अणु
		mmc_हटाओ_host(ushc->mmc);
		जाओ err;
	पूर्ण

	वापस 0;

err:
	ushc_clean_up(ushc);
	वापस ret;
पूर्ण

अटल व्योम ushc_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ushc_data *ushc = usb_get_पूर्णांकfdata(पूर्णांकf);

	spin_lock_irq(&ushc->lock);
	set_bit(DISCONNECTED, &ushc->flags);
	spin_unlock_irq(&ushc->lock);

	usb_समाप्त_urb(ushc->पूर्णांक_urb);
	usb_समाप्त_urb(ushc->cbw_urb);
	usb_समाप्त_urb(ushc->data_urb);
	usb_समाप्त_urb(ushc->csw_urb);

	mmc_हटाओ_host(ushc->mmc);

	ushc_clean_up(ushc);
पूर्ण

अटल काष्ठा usb_device_id ushc_id_table[] = अणु
	/* CSR USB SD Host Controller */
	अणु USB_DEVICE(0x0a12, 0x5d10) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, ushc_id_table);

अटल काष्ठा usb_driver ushc_driver = अणु
	.name       = "ushc",
	.id_table   = ushc_id_table,
	.probe      = ushc_probe,
	.disconnect = ushc_disconnect,
पूर्ण;

module_usb_driver(ushc_driver);

MODULE_DESCRIPTION("USB SD Host Controller driver");
MODULE_AUTHOR("David Vrabel <david.vrabel@csr.com>");
MODULE_LICENSE("GPL");
