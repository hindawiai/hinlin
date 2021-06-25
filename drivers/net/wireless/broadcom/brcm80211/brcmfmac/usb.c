<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2011 Broadcom Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश <linux/usb.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <brcmu_utils.h>
#समावेश <brcm_hw_ids.h>
#समावेश <brcmu_wअगरi.h>
#समावेश "bus.h"
#समावेश "debug.h"
#समावेश "firmware.h"
#समावेश "usb.h"
#समावेश "core.h"
#समावेश "common.h"
#समावेश "bcdc.h"


#घोषणा IOCTL_RESP_TIMEOUT		msecs_to_jअगरfies(2000)

#घोषणा BRCMF_USB_RESET_GETVER_SPINWAIT	100	/* in unit of ms */
#घोषणा BRCMF_USB_RESET_GETVER_LOOP_CNT	10

#घोषणा BRCMF_POSTBOOT_ID		0xA123  /* ID to detect अगर करोngle
						   has boot up */
#घोषणा BRCMF_USB_NRXQ			50
#घोषणा BRCMF_USB_NTXQ			50

#घोषणा BRCMF_USB_CBCTL_WRITE		0
#घोषणा BRCMF_USB_CBCTL_READ		1
#घोषणा BRCMF_USB_MAX_PKT_SIZE		1600

BRCMF_FW_DEF(43143, "brcmfmac43143");
BRCMF_FW_DEF(43236B, "brcmfmac43236b");
BRCMF_FW_DEF(43242A, "brcmfmac43242a");
BRCMF_FW_DEF(43569, "brcmfmac43569");
BRCMF_FW_DEF(4373, "brcmfmac4373");

अटल स्थिर काष्ठा brcmf_firmware_mapping brcmf_usb_fwnames[] = अणु
	BRCMF_FW_ENTRY(BRCM_CC_43143_CHIP_ID, 0xFFFFFFFF, 43143),
	BRCMF_FW_ENTRY(BRCM_CC_43235_CHIP_ID, 0x00000008, 43236B),
	BRCMF_FW_ENTRY(BRCM_CC_43236_CHIP_ID, 0x00000008, 43236B),
	BRCMF_FW_ENTRY(BRCM_CC_43238_CHIP_ID, 0x00000008, 43236B),
	BRCMF_FW_ENTRY(BRCM_CC_43242_CHIP_ID, 0xFFFFFFFF, 43242A),
	BRCMF_FW_ENTRY(BRCM_CC_43566_CHIP_ID, 0xFFFFFFFF, 43569),
	BRCMF_FW_ENTRY(BRCM_CC_43569_CHIP_ID, 0xFFFFFFFF, 43569),
	BRCMF_FW_ENTRY(CY_CC_4373_CHIP_ID, 0xFFFFFFFF, 4373)
पूर्ण;

#घोषणा TRX_MAGIC		0x30524448	/* "HDR0" */
#घोषणा TRX_MAX_OFFSET		3		/* Max number of file offsets */
#घोषणा TRX_UNCOMP_IMAGE	0x20		/* Trx holds uncompressed img */
#घोषणा TRX_RDL_CHUNK		1500		/* size of each dl transfer */
#घोषणा TRX_OFFSETS_DLFWLEN_IDX	0

/* Control messages: bRequest values */
#घोषणा DL_GETSTATE	0	/* वापसs the rdl_state_t काष्ठा */
#घोषणा DL_CHECK_CRC	1	/* currently unused */
#घोषणा DL_GO		2	/* execute करोwnloaded image */
#घोषणा DL_START	3	/* initialize dl state */
#घोषणा DL_REBOOT	4	/* reboot the device in 2 seconds */
#घोषणा DL_GETVER	5	/* वापसs the bootrom_id_t काष्ठा */
#घोषणा DL_GO_PROTECTED	6	/* execute the करोwnloaded code and set reset
				 * event to occur in 2 seconds.  It is the
				 * responsibility of the करोwnloaded code to
				 * clear this event
				 */
#घोषणा DL_EXEC		7	/* jump to a supplied address */
#घोषणा DL_RESETCFG	8	/* To support single क्रमागत on करोngle
				 * - Not used by bootloader
				 */
#घोषणा DL_DEFER_RESP_OK 9	/* Potentially defer the response to setup
				 * अगर resp unavailable
				 */

/* states */
#घोषणा DL_WAITING	0	/* रुकोing to rx first pkt */
#घोषणा DL_READY	1	/* hdr was good, रुकोing क्रम more of the
				 * compressed image
				 */
#घोषणा DL_BAD_HDR	2	/* hdr was corrupted */
#घोषणा DL_BAD_CRC	3	/* compressed image was corrupted */
#घोषणा DL_RUNNABLE	4	/* करोwnload was successful,रुकोing क्रम go cmd */
#घोषणा DL_START_FAIL	5	/* failed to initialize correctly */
#घोषणा DL_NVRAM_TOOBIG	6	/* host specअगरied nvram data exceeds DL_NVRAM
				 * value
				 */
#घोषणा DL_IMAGE_TOOBIG	7	/* firmware image too big */


काष्ठा trx_header_le अणु
	__le32 magic;		/* "HDR0" */
	__le32 len;		/* Length of file including header */
	__le32 crc32;		/* CRC from flag_version to end of file */
	__le32 flag_version;	/* 0:15 flags, 16:31 version */
	__le32 offsets[TRX_MAX_OFFSET];	/* Offsets of partitions from start of
					 * header
					 */
पूर्ण;

काष्ठा rdl_state_le अणु
	__le32 state;
	__le32 bytes;
पूर्ण;

काष्ठा bootrom_id_le अणु
	__le32 chip;		/* Chip id */
	__le32 chiprev;		/* Chip rev */
	__le32 ramsize;		/* Size of  RAM */
	__le32 remapbase;	/* Current remap base address */
	__le32 boardtype;	/* Type of board */
	__le32 boardrev;	/* Board revision */
पूर्ण;

काष्ठा brcmf_usb_image अणु
	काष्ठा list_head list;
	s8 *fwname;
	u8 *image;
	पूर्णांक image_len;
पूर्ण;

काष्ठा brcmf_usbdev_info अणु
	काष्ठा brcmf_usbdev bus_pub; /* MUST BE FIRST */
	spinlock_t qlock;
	काष्ठा list_head rx_मुक्तq;
	काष्ठा list_head rx_postq;
	काष्ठा list_head tx_मुक्तq;
	काष्ठा list_head tx_postq;
	uपूर्णांक rx_pipe, tx_pipe;

	पूर्णांक rx_low_watermark;
	पूर्णांक tx_low_watermark;
	पूर्णांक tx_high_watermark;
	पूर्णांक tx_मुक्तcount;
	bool tx_flowblock;
	spinlock_t tx_flowblock_lock;

	काष्ठा brcmf_usbreq *tx_reqs;
	काष्ठा brcmf_usbreq *rx_reqs;

	अक्षर fw_name[BRCMF_FW_NAME_LEN];
	स्थिर u8 *image;	/* buffer क्रम combine fw and nvram */
	पूर्णांक image_len;

	काष्ठा usb_device *usbdev;
	काष्ठा device *dev;
	काष्ठा completion dev_init_करोne;

	पूर्णांक ctl_in_pipe, ctl_out_pipe;
	काष्ठा urb *ctl_urb; /* URB क्रम control endpoपूर्णांक */
	काष्ठा usb_ctrlrequest ctl_ग_लिखो;
	काष्ठा usb_ctrlrequest ctl_पढ़ो;
	u32 ctl_urb_actual_length;
	पूर्णांक ctl_urb_status;
	पूर्णांक ctl_completed;
	रुको_queue_head_t ioctl_resp_रुको;
	uदीर्घ ctl_op;
	u8 अगरnum;

	काष्ठा urb *bulk_urb; /* used क्रम FW करोwnload */

	काष्ठा brcmf_mp_device *settings;
पूर्ण;

अटल व्योम brcmf_usb_rx_refill(काष्ठा brcmf_usbdev_info *devinfo,
				काष्ठा brcmf_usbreq  *req);

अटल काष्ठा brcmf_usbdev *brcmf_usb_get_buspub(काष्ठा device *dev)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(dev);
	वापस bus_अगर->bus_priv.usb;
पूर्ण

अटल काष्ठा brcmf_usbdev_info *brcmf_usb_get_businfo(काष्ठा device *dev)
अणु
	वापस brcmf_usb_get_buspub(dev)->devinfo;
पूर्ण

अटल पूर्णांक brcmf_usb_ioctl_resp_रुको(काष्ठा brcmf_usbdev_info *devinfo)
अणु
	वापस रुको_event_समयout(devinfo->ioctl_resp_रुको,
				  devinfo->ctl_completed, IOCTL_RESP_TIMEOUT);
पूर्ण

अटल व्योम brcmf_usb_ioctl_resp_wake(काष्ठा brcmf_usbdev_info *devinfo)
अणु
	wake_up(&devinfo->ioctl_resp_रुको);
पूर्ण

अटल व्योम
brcmf_usb_ctl_complete(काष्ठा brcmf_usbdev_info *devinfo, पूर्णांक type, पूर्णांक status)
अणु
	brcmf_dbg(USB, "Enter, status=%d\n", status);

	अगर (unlikely(devinfo == शून्य))
		वापस;

	अगर (type == BRCMF_USB_CBCTL_READ) अणु
		अगर (status == 0)
			devinfo->bus_pub.stats.rx_ctlpkts++;
		अन्यथा
			devinfo->bus_pub.stats.rx_ctlerrs++;
	पूर्ण अन्यथा अगर (type == BRCMF_USB_CBCTL_WRITE) अणु
		अगर (status == 0)
			devinfo->bus_pub.stats.tx_ctlpkts++;
		अन्यथा
			devinfo->bus_pub.stats.tx_ctlerrs++;
	पूर्ण

	devinfo->ctl_urb_status = status;
	devinfo->ctl_completed = true;
	brcmf_usb_ioctl_resp_wake(devinfo);
पूर्ण

अटल व्योम
brcmf_usb_ctlपढ़ो_complete(काष्ठा urb *urb)
अणु
	काष्ठा brcmf_usbdev_info *devinfo =
		(काष्ठा brcmf_usbdev_info *)urb->context;

	brcmf_dbg(USB, "Enter\n");
	devinfo->ctl_urb_actual_length = urb->actual_length;
	brcmf_usb_ctl_complete(devinfo, BRCMF_USB_CBCTL_READ,
		urb->status);
पूर्ण

अटल व्योम
brcmf_usb_ctlग_लिखो_complete(काष्ठा urb *urb)
अणु
	काष्ठा brcmf_usbdev_info *devinfo =
		(काष्ठा brcmf_usbdev_info *)urb->context;

	brcmf_dbg(USB, "Enter\n");
	brcmf_usb_ctl_complete(devinfo, BRCMF_USB_CBCTL_WRITE,
		urb->status);
पूर्ण

अटल पूर्णांक
brcmf_usb_send_ctl(काष्ठा brcmf_usbdev_info *devinfo, u8 *buf, पूर्णांक len)
अणु
	पूर्णांक ret;
	u16 size;

	brcmf_dbg(USB, "Enter\n");
	अगर (devinfo == शून्य || buf == शून्य ||
	    len == 0 || devinfo->ctl_urb == शून्य)
		वापस -EINVAL;

	size = len;
	devinfo->ctl_ग_लिखो.wLength = cpu_to_le16p(&size);
	devinfo->ctl_urb->transfer_buffer_length = size;
	devinfo->ctl_urb_status = 0;
	devinfo->ctl_urb_actual_length = 0;

	usb_fill_control_urb(devinfo->ctl_urb,
		devinfo->usbdev,
		devinfo->ctl_out_pipe,
		(अचिन्हित अक्षर *) &devinfo->ctl_ग_लिखो,
		buf, size,
		(usb_complete_t)brcmf_usb_ctlग_लिखो_complete,
		devinfo);

	ret = usb_submit_urb(devinfo->ctl_urb, GFP_ATOMIC);
	अगर (ret < 0)
		brcmf_err("usb_submit_urb failed %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक
brcmf_usb_recv_ctl(काष्ठा brcmf_usbdev_info *devinfo, u8 *buf, पूर्णांक len)
अणु
	पूर्णांक ret;
	u16 size;

	brcmf_dbg(USB, "Enter\n");
	अगर ((devinfo == शून्य) || (buf == शून्य) || (len == 0)
		|| (devinfo->ctl_urb == शून्य))
		वापस -EINVAL;

	size = len;
	devinfo->ctl_पढ़ो.wLength = cpu_to_le16p(&size);
	devinfo->ctl_urb->transfer_buffer_length = size;

	devinfo->ctl_पढ़ो.bRequestType = USB_सूची_IN
		| USB_TYPE_CLASS | USB_RECIP_INTERFACE;
	devinfo->ctl_पढ़ो.bRequest = 1;

	usb_fill_control_urb(devinfo->ctl_urb,
		devinfo->usbdev,
		devinfo->ctl_in_pipe,
		(अचिन्हित अक्षर *) &devinfo->ctl_पढ़ो,
		buf, size,
		(usb_complete_t)brcmf_usb_ctlपढ़ो_complete,
		devinfo);

	ret = usb_submit_urb(devinfo->ctl_urb, GFP_ATOMIC);
	अगर (ret < 0)
		brcmf_err("usb_submit_urb failed %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक brcmf_usb_tx_ctlpkt(काष्ठा device *dev, u8 *buf, u32 len)
अणु
	पूर्णांक err = 0;
	पूर्णांक समयout = 0;
	काष्ठा brcmf_usbdev_info *devinfo = brcmf_usb_get_businfo(dev);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);

	brcmf_dbg(USB, "Enter\n");

	err = usb_स्वतःpm_get_पूर्णांकerface(पूर्णांकf);
	अगर (err)
		जाओ out;

	अगर (devinfo->bus_pub.state != BRCMFMAC_USB_STATE_UP) अणु
		err = -EIO;
		जाओ fail;
	पूर्ण

	अगर (test_and_set_bit(0, &devinfo->ctl_op)) अणु
		err = -EIO;
		जाओ fail;
	पूर्ण

	devinfo->ctl_completed = false;
	err = brcmf_usb_send_ctl(devinfo, buf, len);
	अगर (err) अणु
		brcmf_err("fail %d bytes: %d\n", err, len);
		clear_bit(0, &devinfo->ctl_op);
		जाओ fail;
	पूर्ण
	समयout = brcmf_usb_ioctl_resp_रुको(devinfo);
	अगर (!समयout) अणु
		brcmf_err("Txctl wait timed out\n");
		usb_समाप्त_urb(devinfo->ctl_urb);
		err = -EIO;
		जाओ fail;
	पूर्ण
	clear_bit(0, &devinfo->ctl_op);

fail:
	usb_स्वतःpm_put_पूर्णांकerface(पूर्णांकf);
out:
	वापस err;
पूर्ण

अटल पूर्णांक brcmf_usb_rx_ctlpkt(काष्ठा device *dev, u8 *buf, u32 len)
अणु
	पूर्णांक err = 0;
	पूर्णांक समयout = 0;
	काष्ठा brcmf_usbdev_info *devinfo = brcmf_usb_get_businfo(dev);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);

	brcmf_dbg(USB, "Enter\n");

	err = usb_स्वतःpm_get_पूर्णांकerface(पूर्णांकf);
	अगर (err)
		जाओ out;

	अगर (devinfo->bus_pub.state != BRCMFMAC_USB_STATE_UP) अणु
		err = -EIO;
		जाओ fail;
	पूर्ण

	अगर (test_and_set_bit(0, &devinfo->ctl_op)) अणु
		err = -EIO;
		जाओ fail;
	पूर्ण

	devinfo->ctl_completed = false;
	err = brcmf_usb_recv_ctl(devinfo, buf, len);
	अगर (err) अणु
		brcmf_err("fail %d bytes: %d\n", err, len);
		clear_bit(0, &devinfo->ctl_op);
		जाओ fail;
	पूर्ण
	समयout = brcmf_usb_ioctl_resp_रुको(devinfo);
	err = devinfo->ctl_urb_status;
	अगर (!समयout) अणु
		brcmf_err("rxctl wait timed out\n");
		usb_समाप्त_urb(devinfo->ctl_urb);
		err = -EIO;
		जाओ fail;
	पूर्ण
	clear_bit(0, &devinfo->ctl_op);
fail:
	usb_स्वतःpm_put_पूर्णांकerface(पूर्णांकf);
	अगर (!err)
		वापस devinfo->ctl_urb_actual_length;
out:
	वापस err;
पूर्ण

अटल काष्ठा brcmf_usbreq *brcmf_usb_deq(काष्ठा brcmf_usbdev_info *devinfo,
					  काष्ठा list_head *q, पूर्णांक *counter)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा brcmf_usbreq  *req;
	spin_lock_irqsave(&devinfo->qlock, flags);
	अगर (list_empty(q)) अणु
		spin_unlock_irqrestore(&devinfo->qlock, flags);
		वापस शून्य;
	पूर्ण
	req = list_entry(q->next, काष्ठा brcmf_usbreq, list);
	list_del_init(q->next);
	अगर (counter)
		(*counter)--;
	spin_unlock_irqrestore(&devinfo->qlock, flags);
	वापस req;

पूर्ण

अटल व्योम brcmf_usb_enq(काष्ठा brcmf_usbdev_info *devinfo,
			  काष्ठा list_head *q, काष्ठा brcmf_usbreq *req,
			  पूर्णांक *counter)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&devinfo->qlock, flags);
	list_add_tail(&req->list, q);
	अगर (counter)
		(*counter)++;
	spin_unlock_irqrestore(&devinfo->qlock, flags);
पूर्ण

अटल काष्ठा brcmf_usbreq *
brcmf_usbdev_qinit(काष्ठा list_head *q, पूर्णांक qsize)
अणु
	पूर्णांक i;
	काष्ठा brcmf_usbreq *req, *reqs;

	reqs = kसुस्मृति(qsize, माप(काष्ठा brcmf_usbreq), GFP_ATOMIC);
	अगर (reqs == शून्य)
		वापस शून्य;

	req = reqs;

	क्रम (i = 0; i < qsize; i++) अणु
		req->urb = usb_alloc_urb(0, GFP_ATOMIC);
		अगर (!req->urb)
			जाओ fail;

		INIT_LIST_HEAD(&req->list);
		list_add_tail(&req->list, q);
		req++;
	पूर्ण
	वापस reqs;
fail:
	brcmf_err("fail!\n");
	जबतक (!list_empty(q)) अणु
		req = list_entry(q->next, काष्ठा brcmf_usbreq, list);
		अगर (req)
			usb_मुक्त_urb(req->urb);
		list_del(q->next);
	पूर्ण
	kमुक्त(reqs);
	वापस शून्य;

पूर्ण

अटल व्योम brcmf_usb_मुक्त_q(काष्ठा list_head *q)
अणु
	काष्ठा brcmf_usbreq *req, *next;

	list_क्रम_each_entry_safe(req, next, q, list) अणु
		अगर (!req->urb) अणु
			brcmf_err("bad req\n");
			अवरोध;
		पूर्ण
		usb_मुक्त_urb(req->urb);
		list_del_init(&req->list);
	पूर्ण
पूर्ण

अटल व्योम brcmf_usb_del_fromq(काष्ठा brcmf_usbdev_info *devinfo,
				काष्ठा brcmf_usbreq *req)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&devinfo->qlock, flags);
	list_del_init(&req->list);
	spin_unlock_irqrestore(&devinfo->qlock, flags);
पूर्ण


अटल व्योम brcmf_usb_tx_complete(काष्ठा urb *urb)
अणु
	काष्ठा brcmf_usbreq *req = (काष्ठा brcmf_usbreq *)urb->context;
	काष्ठा brcmf_usbdev_info *devinfo = req->devinfo;
	अचिन्हित दीर्घ flags;

	brcmf_dbg(USB, "Enter, urb->status=%d, skb=%p\n", urb->status,
		  req->skb);
	brcmf_usb_del_fromq(devinfo, req);

	brcmf_proto_bcdc_txcomplete(devinfo->dev, req->skb, urb->status == 0);
	req->skb = शून्य;
	brcmf_usb_enq(devinfo, &devinfo->tx_मुक्तq, req, &devinfo->tx_मुक्तcount);
	spin_lock_irqsave(&devinfo->tx_flowblock_lock, flags);
	अगर (devinfo->tx_मुक्तcount > devinfo->tx_high_watermark &&
		devinfo->tx_flowblock) अणु
		brcmf_proto_bcdc_txflowblock(devinfo->dev, false);
		devinfo->tx_flowblock = false;
	पूर्ण
	spin_unlock_irqrestore(&devinfo->tx_flowblock_lock, flags);
पूर्ण

अटल व्योम brcmf_usb_rx_complete(काष्ठा urb *urb)
अणु
	काष्ठा brcmf_usbreq  *req = (काष्ठा brcmf_usbreq *)urb->context;
	काष्ठा brcmf_usbdev_info *devinfo = req->devinfo;
	काष्ठा sk_buff *skb;

	brcmf_dbg(USB, "Enter, urb->status=%d\n", urb->status);
	brcmf_usb_del_fromq(devinfo, req);
	skb = req->skb;
	req->skb = शून्य;

	/* zero length packets indicate usb "failure". Do not refill */
	अगर (urb->status != 0 || !urb->actual_length) अणु
		brcmu_pkt_buf_मुक्त_skb(skb);
		brcmf_usb_enq(devinfo, &devinfo->rx_मुक्तq, req, शून्य);
		वापस;
	पूर्ण

	अगर (devinfo->bus_pub.state == BRCMFMAC_USB_STATE_UP ||
	    devinfo->bus_pub.state == BRCMFMAC_USB_STATE_SLEEP) अणु
		skb_put(skb, urb->actual_length);
		brcmf_rx_frame(devinfo->dev, skb, true, true);
		brcmf_usb_rx_refill(devinfo, req);
		usb_mark_last_busy(urb->dev);
	पूर्ण अन्यथा अणु
		brcmu_pkt_buf_मुक्त_skb(skb);
		brcmf_usb_enq(devinfo, &devinfo->rx_मुक्तq, req, शून्य);
	पूर्ण
	वापस;

पूर्ण

अटल व्योम brcmf_usb_rx_refill(काष्ठा brcmf_usbdev_info *devinfo,
				काष्ठा brcmf_usbreq  *req)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	अगर (!req || !devinfo)
		वापस;

	skb = dev_alloc_skb(devinfo->bus_pub.bus_mtu);
	अगर (!skb) अणु
		brcmf_usb_enq(devinfo, &devinfo->rx_मुक्तq, req, शून्य);
		वापस;
	पूर्ण
	req->skb = skb;

	usb_fill_bulk_urb(req->urb, devinfo->usbdev, devinfo->rx_pipe,
			  skb->data, skb_tailroom(skb), brcmf_usb_rx_complete,
			  req);
	req->devinfo = devinfo;
	brcmf_usb_enq(devinfo, &devinfo->rx_postq, req, शून्य);

	ret = usb_submit_urb(req->urb, GFP_ATOMIC);
	अगर (ret) अणु
		brcmf_usb_del_fromq(devinfo, req);
		brcmu_pkt_buf_मुक्त_skb(req->skb);
		req->skb = शून्य;
		brcmf_usb_enq(devinfo, &devinfo->rx_मुक्तq, req, शून्य);
	पूर्ण
	वापस;
पूर्ण

अटल व्योम brcmf_usb_rx_fill_all(काष्ठा brcmf_usbdev_info *devinfo)
अणु
	काष्ठा brcmf_usbreq *req;

	अगर (devinfo->bus_pub.state != BRCMFMAC_USB_STATE_UP) अणु
		brcmf_err("bus is not up=%d\n", devinfo->bus_pub.state);
		वापस;
	पूर्ण
	जबतक ((req = brcmf_usb_deq(devinfo, &devinfo->rx_मुक्तq, शून्य)) != शून्य)
		brcmf_usb_rx_refill(devinfo, req);
पूर्ण

अटल व्योम
brcmf_usb_state_change(काष्ठा brcmf_usbdev_info *devinfo, पूर्णांक state)
अणु
	काष्ठा brcmf_bus *bcmf_bus = devinfo->bus_pub.bus;

	brcmf_dbg(USB, "Enter, current state=%d, new state=%d\n",
		  devinfo->bus_pub.state, state);

	अगर (devinfo->bus_pub.state == state)
		वापस;

	devinfo->bus_pub.state = state;

	/* update state of upper layer */
	अगर (state == BRCMFMAC_USB_STATE_DOWN) अणु
		brcmf_dbg(USB, "DBUS is down\n");
		brcmf_bus_change_state(bcmf_bus, BRCMF_BUS_DOWN);
	पूर्ण अन्यथा अगर (state == BRCMFMAC_USB_STATE_UP) अणु
		brcmf_dbg(USB, "DBUS is up\n");
		brcmf_bus_change_state(bcmf_bus, BRCMF_BUS_UP);
	पूर्ण अन्यथा अणु
		brcmf_dbg(USB, "DBUS current state=%d\n", state);
	पूर्ण
पूर्ण

अटल पूर्णांक brcmf_usb_tx(काष्ठा device *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा brcmf_usbdev_info *devinfo = brcmf_usb_get_businfo(dev);
	काष्ठा brcmf_usbreq  *req;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);

	ret = usb_स्वतःpm_get_पूर्णांकerface(पूर्णांकf);
	अगर (ret)
		जाओ out;

	brcmf_dbg(USB, "Enter, skb=%p\n", skb);
	अगर (devinfo->bus_pub.state != BRCMFMAC_USB_STATE_UP) अणु
		ret = -EIO;
		जाओ fail;
	पूर्ण

	req = brcmf_usb_deq(devinfo, &devinfo->tx_मुक्तq,
					&devinfo->tx_मुक्तcount);
	अगर (!req) अणु
		brcmf_err("no req to send\n");
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	req->skb = skb;
	req->devinfo = devinfo;
	usb_fill_bulk_urb(req->urb, devinfo->usbdev, devinfo->tx_pipe,
			  skb->data, skb->len, brcmf_usb_tx_complete, req);
	req->urb->transfer_flags |= URB_ZERO_PACKET;
	brcmf_usb_enq(devinfo, &devinfo->tx_postq, req, शून्य);
	ret = usb_submit_urb(req->urb, GFP_ATOMIC);
	अगर (ret) अणु
		brcmf_err("brcmf_usb_tx usb_submit_urb FAILED\n");
		brcmf_usb_del_fromq(devinfo, req);
		req->skb = शून्य;
		brcmf_usb_enq(devinfo, &devinfo->tx_मुक्तq, req,
			      &devinfo->tx_मुक्तcount);
		जाओ fail;
	पूर्ण

	spin_lock_irqsave(&devinfo->tx_flowblock_lock, flags);
	अगर (devinfo->tx_मुक्तcount < devinfo->tx_low_watermark &&
	    !devinfo->tx_flowblock) अणु
		brcmf_proto_bcdc_txflowblock(dev, true);
		devinfo->tx_flowblock = true;
	पूर्ण
	spin_unlock_irqrestore(&devinfo->tx_flowblock_lock, flags);

fail:
	usb_स्वतःpm_put_पूर्णांकerface(पूर्णांकf);
out:
	वापस ret;
पूर्ण


अटल पूर्णांक brcmf_usb_up(काष्ठा device *dev)
अणु
	काष्ठा brcmf_usbdev_info *devinfo = brcmf_usb_get_businfo(dev);

	brcmf_dbg(USB, "Enter\n");
	अगर (devinfo->bus_pub.state == BRCMFMAC_USB_STATE_UP)
		वापस 0;

	/* Success, indicate devinfo is fully up */
	brcmf_usb_state_change(devinfo, BRCMFMAC_USB_STATE_UP);

	अगर (devinfo->ctl_urb) अणु
		devinfo->ctl_in_pipe = usb_rcvctrlpipe(devinfo->usbdev, 0);
		devinfo->ctl_out_pipe = usb_sndctrlpipe(devinfo->usbdev, 0);

		/* CTL Write */
		devinfo->ctl_ग_लिखो.bRequestType =
			USB_सूची_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE;
		devinfo->ctl_ग_लिखो.bRequest = 0;
		devinfo->ctl_ग_लिखो.wValue = cpu_to_le16(0);
		devinfo->ctl_ग_लिखो.wIndex = cpu_to_le16(devinfo->अगरnum);

		/* CTL Read */
		devinfo->ctl_पढ़ो.bRequestType =
			USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE;
		devinfo->ctl_पढ़ो.bRequest = 1;
		devinfo->ctl_पढ़ो.wValue = cpu_to_le16(0);
		devinfo->ctl_पढ़ो.wIndex = cpu_to_le16(devinfo->अगरnum);
	पूर्ण
	brcmf_usb_rx_fill_all(devinfo);
	वापस 0;
पूर्ण

अटल व्योम brcmf_cancel_all_urbs(काष्ठा brcmf_usbdev_info *devinfo)
अणु
	पूर्णांक i;

	अगर (devinfo->ctl_urb)
		usb_समाप्त_urb(devinfo->ctl_urb);
	अगर (devinfo->bulk_urb)
		usb_समाप्त_urb(devinfo->bulk_urb);
	अगर (devinfo->tx_reqs)
		क्रम (i = 0; i < devinfo->bus_pub.ntxq; i++)
			usb_समाप्त_urb(devinfo->tx_reqs[i].urb);
	अगर (devinfo->rx_reqs)
		क्रम (i = 0; i < devinfo->bus_pub.nrxq; i++)
			usb_समाप्त_urb(devinfo->rx_reqs[i].urb);
पूर्ण

अटल व्योम brcmf_usb_करोwn(काष्ठा device *dev)
अणु
	काष्ठा brcmf_usbdev_info *devinfo = brcmf_usb_get_businfo(dev);

	brcmf_dbg(USB, "Enter\n");
	अगर (devinfo == शून्य)
		वापस;

	अगर (devinfo->bus_pub.state == BRCMFMAC_USB_STATE_DOWN)
		वापस;

	brcmf_usb_state_change(devinfo, BRCMFMAC_USB_STATE_DOWN);

	brcmf_cancel_all_urbs(devinfo);
पूर्ण

अटल व्योम
brcmf_usb_sync_complete(काष्ठा urb *urb)
अणु
	काष्ठा brcmf_usbdev_info *devinfo =
			(काष्ठा brcmf_usbdev_info *)urb->context;

	devinfo->ctl_completed = true;
	brcmf_usb_ioctl_resp_wake(devinfo);
पूर्ण

अटल पूर्णांक brcmf_usb_dl_cmd(काष्ठा brcmf_usbdev_info *devinfo, u8 cmd,
			    व्योम *buffer, पूर्णांक buflen)
अणु
	पूर्णांक ret;
	अक्षर *पंचांगpbuf;
	u16 size;

	अगर ((!devinfo) || (devinfo->ctl_urb == शून्य))
		वापस -EINVAL;

	पंचांगpbuf = kदो_स्मृति(buflen, GFP_ATOMIC);
	अगर (!पंचांगpbuf)
		वापस -ENOMEM;

	size = buflen;
	devinfo->ctl_urb->transfer_buffer_length = size;

	devinfo->ctl_पढ़ो.wLength = cpu_to_le16p(&size);
	devinfo->ctl_पढ़ो.bRequestType = USB_सूची_IN | USB_TYPE_VENDOR |
		USB_RECIP_INTERFACE;
	devinfo->ctl_पढ़ो.bRequest = cmd;

	usb_fill_control_urb(devinfo->ctl_urb,
		devinfo->usbdev,
		usb_rcvctrlpipe(devinfo->usbdev, 0),
		(अचिन्हित अक्षर *) &devinfo->ctl_पढ़ो,
		(व्योम *) पंचांगpbuf, size,
		(usb_complete_t)brcmf_usb_sync_complete, devinfo);

	devinfo->ctl_completed = false;
	ret = usb_submit_urb(devinfo->ctl_urb, GFP_ATOMIC);
	अगर (ret < 0) अणु
		brcmf_err("usb_submit_urb failed %d\n", ret);
		जाओ finalize;
	पूर्ण

	अगर (!brcmf_usb_ioctl_resp_रुको(devinfo)) अणु
		usb_समाप्त_urb(devinfo->ctl_urb);
		ret = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		स_नकल(buffer, पंचांगpbuf, buflen);
	पूर्ण

finalize:
	kमुक्त(पंचांगpbuf);
	वापस ret;
पूर्ण

अटल bool
brcmf_usb_dlneeded(काष्ठा brcmf_usbdev_info *devinfo)
अणु
	काष्ठा bootrom_id_le id;
	u32 chipid, chiprev;

	brcmf_dbg(USB, "Enter\n");

	अगर (devinfo == शून्य)
		वापस false;

	/* Check अगर firmware करोwnloaded alपढ़ोy by querying runसमय ID */
	id.chip = cpu_to_le32(0xDEAD);
	brcmf_usb_dl_cmd(devinfo, DL_GETVER, &id, माप(id));

	chipid = le32_to_cpu(id.chip);
	chiprev = le32_to_cpu(id.chiprev);

	अगर ((chipid & 0x4300) == 0x4300)
		brcmf_dbg(USB, "chip %x rev 0x%x\n", chipid, chiprev);
	अन्यथा
		brcmf_dbg(USB, "chip %d rev 0x%x\n", chipid, chiprev);
	अगर (chipid == BRCMF_POSTBOOT_ID) अणु
		brcmf_dbg(USB, "firmware already downloaded\n");
		brcmf_usb_dl_cmd(devinfo, DL_RESETCFG, &id, माप(id));
		वापस false;
	पूर्ण अन्यथा अणु
		devinfo->bus_pub.devid = chipid;
		devinfo->bus_pub.chiprev = chiprev;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक
brcmf_usb_resetcfg(काष्ठा brcmf_usbdev_info *devinfo)
अणु
	काष्ठा bootrom_id_le id;
	u32 loop_cnt;
	पूर्णांक err;

	brcmf_dbg(USB, "Enter\n");

	loop_cnt = 0;
	करो अणु
		mdelay(BRCMF_USB_RESET_GETVER_SPINWAIT);
		loop_cnt++;
		id.chip = cpu_to_le32(0xDEAD);       /* Get the ID */
		err = brcmf_usb_dl_cmd(devinfo, DL_GETVER, &id, माप(id));
		अगर ((err) && (err != -ETIMEDOUT))
			वापस err;
		अगर (id.chip == cpu_to_le32(BRCMF_POSTBOOT_ID))
			अवरोध;
	पूर्ण जबतक (loop_cnt < BRCMF_USB_RESET_GETVER_LOOP_CNT);

	अगर (id.chip == cpu_to_le32(BRCMF_POSTBOOT_ID)) अणु
		brcmf_dbg(USB, "postboot chip 0x%x/rev 0x%x\n",
			  le32_to_cpu(id.chip), le32_to_cpu(id.chiprev));

		brcmf_usb_dl_cmd(devinfo, DL_RESETCFG, &id, माप(id));
		वापस 0;
	पूर्ण अन्यथा अणु
		brcmf_err("Cannot talk to Dongle. Firmware is not UP, %d ms\n",
			  BRCMF_USB_RESET_GETVER_SPINWAIT * loop_cnt);
		वापस -EINVAL;
	पूर्ण
पूर्ण


अटल पूर्णांक
brcmf_usb_dl_send_bulk(काष्ठा brcmf_usbdev_info *devinfo, व्योम *buffer, पूर्णांक len)
अणु
	पूर्णांक ret;

	अगर ((devinfo == शून्य) || (devinfo->bulk_urb == शून्य))
		वापस -EINVAL;

	/* Prepare the URB */
	usb_fill_bulk_urb(devinfo->bulk_urb, devinfo->usbdev,
			  devinfo->tx_pipe, buffer, len,
			  (usb_complete_t)brcmf_usb_sync_complete, devinfo);

	devinfo->bulk_urb->transfer_flags |= URB_ZERO_PACKET;

	devinfo->ctl_completed = false;
	ret = usb_submit_urb(devinfo->bulk_urb, GFP_ATOMIC);
	अगर (ret) अणु
		brcmf_err("usb_submit_urb failed %d\n", ret);
		वापस ret;
	पूर्ण
	ret = brcmf_usb_ioctl_resp_रुको(devinfo);
	वापस (ret == 0);
पूर्ण

अटल पूर्णांक
brcmf_usb_dl_ग_लिखोimage(काष्ठा brcmf_usbdev_info *devinfo, u8 *fw, पूर्णांक fwlen)
अणु
	अचिन्हित पूर्णांक sendlen, sent, dllen;
	अक्षर *bulkchunk = शून्य, *dlpos;
	काष्ठा rdl_state_le state;
	u32 rdlstate, rdlbytes;
	पूर्णांक err = 0;

	brcmf_dbg(USB, "Enter, fw %p, len %d\n", fw, fwlen);

	bulkchunk = kदो_स्मृति(TRX_RDL_CHUNK, GFP_ATOMIC);
	अगर (bulkchunk == शून्य) अणु
		err = -ENOMEM;
		जाओ fail;
	पूर्ण

	/* 1) Prepare USB boot loader क्रम runसमय image */
	brcmf_usb_dl_cmd(devinfo, DL_START, &state, माप(state));

	rdlstate = le32_to_cpu(state.state);
	rdlbytes = le32_to_cpu(state.bytes);

	/* 2) Check we are in the Waiting state */
	अगर (rdlstate != DL_WAITING) अणु
		brcmf_err("Failed to DL_START\n");
		err = -EINVAL;
		जाओ fail;
	पूर्ण
	sent = 0;
	dlpos = fw;
	dllen = fwlen;

	/* Get chip id and rev */
	जबतक (rdlbytes != dllen) अणु
		/* Wait until the usb device reports it received all
		 * the bytes we sent */
		अगर ((rdlbytes == sent) && (rdlbytes != dllen)) अणु
			अगर ((dllen-sent) < TRX_RDL_CHUNK)
				sendlen = dllen-sent;
			अन्यथा
				sendlen = TRX_RDL_CHUNK;

			/* simply aव्योम having to send a ZLP by ensuring we
			 * never have an even
			 * multiple of 64
			 */
			अगर (!(sendlen % 64))
				sendlen -= 4;

			/* send data */
			स_नकल(bulkchunk, dlpos, sendlen);
			अगर (brcmf_usb_dl_send_bulk(devinfo, bulkchunk,
						   sendlen)) अणु
				brcmf_err("send_bulk failed\n");
				err = -EINVAL;
				जाओ fail;
			पूर्ण

			dlpos += sendlen;
			sent += sendlen;
		पूर्ण
		err = brcmf_usb_dl_cmd(devinfo, DL_GETSTATE, &state,
				       माप(state));
		अगर (err) अणु
			brcmf_err("DL_GETSTATE Failed\n");
			जाओ fail;
		पूर्ण

		rdlstate = le32_to_cpu(state.state);
		rdlbytes = le32_to_cpu(state.bytes);

		/* restart अगर an error is reported */
		अगर (rdlstate == DL_BAD_HDR || rdlstate == DL_BAD_CRC) अणु
			brcmf_err("Bad Hdr or Bad CRC state %d\n",
				  rdlstate);
			err = -EINVAL;
			जाओ fail;
		पूर्ण
	पूर्ण

fail:
	kमुक्त(bulkchunk);
	brcmf_dbg(USB, "Exit, err=%d\n", err);
	वापस err;
पूर्ण

अटल पूर्णांक brcmf_usb_dlstart(काष्ठा brcmf_usbdev_info *devinfo, u8 *fw, पूर्णांक len)
अणु
	पूर्णांक err;

	brcmf_dbg(USB, "Enter\n");

	अगर (devinfo == शून्य)
		वापस -EINVAL;

	अगर (devinfo->bus_pub.devid == 0xDEAD)
		वापस -EINVAL;

	err = brcmf_usb_dl_ग_लिखोimage(devinfo, fw, len);
	अगर (err == 0)
		devinfo->bus_pub.state = BRCMFMAC_USB_STATE_DL_DONE;
	अन्यथा
		devinfo->bus_pub.state = BRCMFMAC_USB_STATE_DL_FAIL;
	brcmf_dbg(USB, "Exit, err=%d\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक brcmf_usb_dlrun(काष्ठा brcmf_usbdev_info *devinfo)
अणु
	काष्ठा rdl_state_le state;

	brcmf_dbg(USB, "Enter\n");
	अगर (!devinfo)
		वापस -EINVAL;

	अगर (devinfo->bus_pub.devid == 0xDEAD)
		वापस -EINVAL;

	/* Check we are runnable */
	state.state = 0;
	brcmf_usb_dl_cmd(devinfo, DL_GETSTATE, &state, माप(state));

	/* Start the image */
	अगर (state.state == cpu_to_le32(DL_RUNNABLE)) अणु
		अगर (brcmf_usb_dl_cmd(devinfo, DL_GO, &state, माप(state)))
			वापस -ENODEV;
		अगर (brcmf_usb_resetcfg(devinfo))
			वापस -ENODEV;
		/* The Dongle may go क्रम re-क्रमागतeration. */
	पूर्ण अन्यथा अणु
		brcmf_err("Dongle not runnable\n");
		वापस -EINVAL;
	पूर्ण
	brcmf_dbg(USB, "Exit\n");
	वापस 0;
पूर्ण

अटल पूर्णांक
brcmf_usb_fw_करोwnload(काष्ठा brcmf_usbdev_info *devinfo)
अणु
	पूर्णांक err;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;

	brcmf_dbg(USB, "Enter\n");
	अगर (!devinfo) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (!devinfo->image) अणु
		brcmf_err("No firmware!\n");
		err = -ENOENT;
		जाओ out;
	पूर्ण

	पूर्णांकf = to_usb_पूर्णांकerface(devinfo->dev);
	err = usb_स्वतःpm_get_पूर्णांकerface(पूर्णांकf);
	अगर (err)
		जाओ out;

	err = brcmf_usb_dlstart(devinfo,
		(u8 *)devinfo->image, devinfo->image_len);
	अगर (err == 0)
		err = brcmf_usb_dlrun(devinfo);

	usb_स्वतःpm_put_पूर्णांकerface(पूर्णांकf);
out:
	वापस err;
पूर्ण


अटल व्योम brcmf_usb_detach(काष्ठा brcmf_usbdev_info *devinfo)
अणु
	brcmf_dbg(USB, "Enter, devinfo %p\n", devinfo);

	/* मुक्त the URBS */
	brcmf_usb_मुक्त_q(&devinfo->rx_मुक्तq);
	brcmf_usb_मुक्त_q(&devinfo->tx_मुक्तq);

	usb_मुक्त_urb(devinfo->ctl_urb);
	usb_मुक्त_urb(devinfo->bulk_urb);

	kमुक्त(devinfo->tx_reqs);
	kमुक्त(devinfo->rx_reqs);

	अगर (devinfo->settings)
		brcmf_release_module_param(devinfo->settings);
पूर्ण


अटल पूर्णांक check_file(स्थिर u8 *headers)
अणु
	काष्ठा trx_header_le *trx;
	पूर्णांक actual_len = -1;

	brcmf_dbg(USB, "Enter\n");
	/* Extract trx header */
	trx = (काष्ठा trx_header_le *) headers;
	अगर (trx->magic != cpu_to_le32(TRX_MAGIC))
		वापस -1;

	headers += माप(काष्ठा trx_header_le);

	अगर (le32_to_cpu(trx->flag_version) & TRX_UNCOMP_IMAGE) अणु
		actual_len = le32_to_cpu(trx->offsets[TRX_OFFSETS_DLFWLEN_IDX]);
		वापस actual_len + माप(काष्ठा trx_header_le);
	पूर्ण
	वापस -1;
पूर्ण


अटल
काष्ठा brcmf_usbdev *brcmf_usb_attach(काष्ठा brcmf_usbdev_info *devinfo,
				      पूर्णांक nrxq, पूर्णांक ntxq)
अणु
	brcmf_dbg(USB, "Enter\n");

	devinfo->bus_pub.nrxq = nrxq;
	devinfo->rx_low_watermark = nrxq / 2;
	devinfo->bus_pub.devinfo = devinfo;
	devinfo->bus_pub.ntxq = ntxq;
	devinfo->bus_pub.state = BRCMFMAC_USB_STATE_DOWN;

	/* flow control when too many tx urbs posted */
	devinfo->tx_low_watermark = ntxq / 4;
	devinfo->tx_high_watermark = devinfo->tx_low_watermark * 3;
	devinfo->bus_pub.bus_mtu = BRCMF_USB_MAX_PKT_SIZE;

	/* Initialize other काष्ठाure content */
	init_रुकोqueue_head(&devinfo->ioctl_resp_रुको);

	/* Initialize the spinlocks */
	spin_lock_init(&devinfo->qlock);
	spin_lock_init(&devinfo->tx_flowblock_lock);

	INIT_LIST_HEAD(&devinfo->rx_मुक्तq);
	INIT_LIST_HEAD(&devinfo->rx_postq);

	INIT_LIST_HEAD(&devinfo->tx_मुक्तq);
	INIT_LIST_HEAD(&devinfo->tx_postq);

	devinfo->tx_flowblock = false;

	devinfo->rx_reqs = brcmf_usbdev_qinit(&devinfo->rx_मुक्तq, nrxq);
	अगर (!devinfo->rx_reqs)
		जाओ error;

	devinfo->tx_reqs = brcmf_usbdev_qinit(&devinfo->tx_मुक्तq, ntxq);
	अगर (!devinfo->tx_reqs)
		जाओ error;
	devinfo->tx_मुक्तcount = ntxq;

	devinfo->ctl_urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!devinfo->ctl_urb)
		जाओ error;
	devinfo->bulk_urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!devinfo->bulk_urb)
		जाओ error;

	वापस &devinfo->bus_pub;

error:
	brcmf_err("failed!\n");
	brcmf_usb_detach(devinfo);
	वापस शून्य;
पूर्ण

अटल
पूर्णांक brcmf_usb_get_fwname(काष्ठा device *dev, स्थिर अक्षर *ext, u8 *fw_name)
अणु
	काष्ठा brcmf_bus *bus = dev_get_drvdata(dev);
	काष्ठा brcmf_fw_request *fwreq;
	काष्ठा brcmf_fw_name fwnames[] = अणु
		अणु ext, fw_name पूर्ण,
	पूर्ण;

	fwreq = brcmf_fw_alloc_request(bus->chip, bus->chiprev,
				       brcmf_usb_fwnames,
				       ARRAY_SIZE(brcmf_usb_fwnames),
				       fwnames, ARRAY_SIZE(fwnames));
	अगर (!fwreq)
		वापस -ENOMEM;

	kमुक्त(fwreq);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा brcmf_bus_ops brcmf_usb_bus_ops = अणु
	.preinit = brcmf_usb_up,
	.stop = brcmf_usb_करोwn,
	.txdata = brcmf_usb_tx,
	.txctl = brcmf_usb_tx_ctlpkt,
	.rxctl = brcmf_usb_rx_ctlpkt,
	.get_fwname = brcmf_usb_get_fwname,
पूर्ण;

#घोषणा BRCMF_USB_FW_CODE	0

अटल व्योम brcmf_usb_probe_phase2(काष्ठा device *dev, पूर्णांक ret,
				   काष्ठा brcmf_fw_request *fwreq)
अणु
	काष्ठा brcmf_bus *bus = dev_get_drvdata(dev);
	काष्ठा brcmf_usbdev_info *devinfo = bus->bus_priv.usb->devinfo;
	स्थिर काष्ठा firmware *fw;

	अगर (ret)
		जाओ error;

	brcmf_dbg(USB, "Start fw downloading\n");

	fw = fwreq->items[BRCMF_USB_FW_CODE].binary;
	kमुक्त(fwreq);

	ret = check_file(fw->data);
	अगर (ret < 0) अणु
		brcmf_err("invalid firmware\n");
		release_firmware(fw);
		जाओ error;
	पूर्ण

	devinfo->image = fw->data;
	devinfo->image_len = fw->size;

	ret = brcmf_usb_fw_करोwnload(devinfo);
	release_firmware(fw);
	अगर (ret)
		जाओ error;

	ret = brcmf_alloc(devinfo->dev, devinfo->settings);
	अगर (ret)
		जाओ error;

	/* Attach to the common driver पूर्णांकerface */
	ret = brcmf_attach(devinfo->dev);
	अगर (ret)
		जाओ error;

	complete(&devinfo->dev_init_करोne);
	वापस;
error:
	brcmf_dbg(TRACE, "failed: dev=%s, err=%d\n", dev_name(dev), ret);
	complete(&devinfo->dev_init_करोne);
	device_release_driver(dev);
पूर्ण

अटल काष्ठा brcmf_fw_request *
brcmf_usb_prepare_fw_request(काष्ठा brcmf_usbdev_info *devinfo)
अणु
	काष्ठा brcmf_fw_request *fwreq;
	काष्ठा brcmf_fw_name fwnames[] = अणु
		अणु ".bin", devinfo->fw_name पूर्ण,
	पूर्ण;

	fwreq = brcmf_fw_alloc_request(devinfo->bus_pub.devid,
				       devinfo->bus_pub.chiprev,
				       brcmf_usb_fwnames,
				       ARRAY_SIZE(brcmf_usb_fwnames),
				       fwnames, ARRAY_SIZE(fwnames));
	अगर (!fwreq)
		वापस शून्य;

	fwreq->items[BRCMF_USB_FW_CODE].type = BRCMF_FW_TYPE_BINARY;

	वापस fwreq;
पूर्ण

अटल पूर्णांक brcmf_usb_probe_cb(काष्ठा brcmf_usbdev_info *devinfo)
अणु
	काष्ठा brcmf_bus *bus = शून्य;
	काष्ठा brcmf_usbdev *bus_pub = शून्य;
	काष्ठा device *dev = devinfo->dev;
	काष्ठा brcmf_fw_request *fwreq;
	पूर्णांक ret;

	brcmf_dbg(USB, "Enter\n");
	bus_pub = brcmf_usb_attach(devinfo, BRCMF_USB_NRXQ, BRCMF_USB_NTXQ);
	अगर (!bus_pub)
		वापस -ENODEV;

	bus = kzalloc(माप(काष्ठा brcmf_bus), GFP_ATOMIC);
	अगर (!bus) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	bus->dev = dev;
	bus_pub->bus = bus;
	bus->bus_priv.usb = bus_pub;
	dev_set_drvdata(dev, bus);
	bus->ops = &brcmf_usb_bus_ops;
	bus->proto_type = BRCMF_PROTO_BCDC;
	bus->always_use_fws_queue = true;
#अगर_घोषित CONFIG_PM
	bus->wowl_supported = true;
#पूर्ण_अगर

	devinfo->settings = brcmf_get_module_param(bus->dev, BRCMF_BUSTYPE_USB,
						   bus_pub->devid,
						   bus_pub->chiprev);
	अगर (!devinfo->settings) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	अगर (!brcmf_usb_dlneeded(devinfo)) अणु
		ret = brcmf_alloc(devinfo->dev, devinfo->settings);
		अगर (ret)
			जाओ fail;
		ret = brcmf_attach(devinfo->dev);
		अगर (ret)
			जाओ fail;
		/* we are करोne */
		complete(&devinfo->dev_init_करोne);
		वापस 0;
	पूर्ण
	bus->chip = bus_pub->devid;
	bus->chiprev = bus_pub->chiprev;

	fwreq = brcmf_usb_prepare_fw_request(devinfo);
	अगर (!fwreq) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	/* request firmware here */
	ret = brcmf_fw_get_firmwares(dev, fwreq, brcmf_usb_probe_phase2);
	अगर (ret) अणु
		brcmf_err("firmware request failed: %d\n", ret);
		kमुक्त(fwreq);
		जाओ fail;
	पूर्ण

	वापस 0;

fail:
	/* Release resources in reverse order */
	brcmf_मुक्त(devinfo->dev);
	kमुक्त(bus);
	brcmf_usb_detach(devinfo);
	वापस ret;
पूर्ण

अटल व्योम
brcmf_usb_disconnect_cb(काष्ठा brcmf_usbdev_info *devinfo)
अणु
	अगर (!devinfo)
		वापस;
	brcmf_dbg(USB, "Enter, bus_pub %p\n", devinfo);

	brcmf_detach(devinfo->dev);
	brcmf_मुक्त(devinfo->dev);
	kमुक्त(devinfo->bus_pub.bus);
	brcmf_usb_detach(devinfo);
पूर्ण

अटल पूर्णांक
brcmf_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *usb = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा brcmf_usbdev_info *devinfo;
	काष्ठा usb_पूर्णांकerface_descriptor	*desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	पूर्णांक ret = 0;
	u32 num_of_eps;
	u8 endpoपूर्णांक_num, ep;

	brcmf_dbg(USB, "Enter 0x%04x:0x%04x\n", id->idVenकरोr, id->idProduct);

	devinfo = kzalloc(माप(*devinfo), GFP_ATOMIC);
	अगर (devinfo == शून्य)
		वापस -ENOMEM;

	devinfo->usbdev = usb;
	devinfo->dev = &usb->dev;
	/* Init completion, to protect क्रम disconnect जबतक still loading.
	 * Necessary because of the asynchronous firmware load स्थिरruction
	 */
	init_completion(&devinfo->dev_init_करोne);

	usb_set_पूर्णांकfdata(पूर्णांकf, devinfo);

	पूर्णांकf->needs_remote_wakeup = 1;

	/* Check that the device supports only one configuration */
	अगर (usb->descriptor.bNumConfigurations != 1) अणु
		brcmf_err("Number of configurations: %d not supported\n",
			  usb->descriptor.bNumConfigurations);
		ret = -ENODEV;
		जाओ fail;
	पूर्ण

	अगर ((usb->descriptor.bDeviceClass != USB_CLASS_VENDOR_SPEC) &&
	    (usb->descriptor.bDeviceClass != USB_CLASS_MISC) &&
	    (usb->descriptor.bDeviceClass != USB_CLASS_WIRELESS_CONTROLLER)) अणु
		brcmf_err("Device class: 0x%x not supported\n",
			  usb->descriptor.bDeviceClass);
		ret = -ENODEV;
		जाओ fail;
	पूर्ण

	desc = &पूर्णांकf->cur_altsetting->desc;
	अगर ((desc->bInterfaceClass != USB_CLASS_VENDOR_SPEC) ||
	    (desc->bInterfaceSubClass != 2) ||
	    (desc->bInterfaceProtocol != 0xff)) अणु
		brcmf_err("non WLAN interface %d: 0x%x:0x%x:0x%x\n",
			  desc->bInterfaceNumber, desc->bInterfaceClass,
			  desc->bInterfaceSubClass, desc->bInterfaceProtocol);
		ret = -ENODEV;
		जाओ fail;
	पूर्ण

	num_of_eps = desc->bNumEndpoपूर्णांकs;
	क्रम (ep = 0; ep < num_of_eps; ep++) अणु
		endpoपूर्णांक = &पूर्णांकf->cur_altsetting->endpoपूर्णांक[ep].desc;
		endpoपूर्णांक_num = usb_endpoपूर्णांक_num(endpoपूर्णांक);
		अगर (!usb_endpoपूर्णांक_xfer_bulk(endpoपूर्णांक))
			जारी;
		अगर (usb_endpoपूर्णांक_dir_in(endpoपूर्णांक)) अणु
			अगर (!devinfo->rx_pipe)
				devinfo->rx_pipe =
					usb_rcvbulkpipe(usb, endpoपूर्णांक_num);
		पूर्ण अन्यथा अणु
			अगर (!devinfo->tx_pipe)
				devinfo->tx_pipe =
					usb_sndbulkpipe(usb, endpoपूर्णांक_num);
		पूर्ण
	पूर्ण
	अगर (devinfo->rx_pipe == 0) अणु
		brcmf_err("No RX (in) Bulk EP found\n");
		ret = -ENODEV;
		जाओ fail;
	पूर्ण
	अगर (devinfo->tx_pipe == 0) अणु
		brcmf_err("No TX (out) Bulk EP found\n");
		ret = -ENODEV;
		जाओ fail;
	पूर्ण

	devinfo->अगरnum = desc->bInterfaceNumber;

	अगर (usb->speed == USB_SPEED_SUPER_PLUS)
		brcmf_dbg(USB, "Broadcom super speed plus USB WLAN interface detected\n");
	अन्यथा अगर (usb->speed == USB_SPEED_SUPER)
		brcmf_dbg(USB, "Broadcom super speed USB WLAN interface detected\n");
	अन्यथा अगर (usb->speed == USB_SPEED_HIGH)
		brcmf_dbg(USB, "Broadcom high speed USB WLAN interface detected\n");
	अन्यथा
		brcmf_dbg(USB, "Broadcom full speed USB WLAN interface detected\n");

	ret = brcmf_usb_probe_cb(devinfo);
	अगर (ret)
		जाओ fail;

	/* Success */
	वापस 0;

fail:
	complete(&devinfo->dev_init_करोne);
	kमुक्त(devinfo);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	वापस ret;
पूर्ण

अटल व्योम
brcmf_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा brcmf_usbdev_info *devinfo;

	brcmf_dbg(USB, "Enter\n");
	devinfo = (काष्ठा brcmf_usbdev_info *)usb_get_पूर्णांकfdata(पूर्णांकf);

	अगर (devinfo) अणु
		रुको_क्रम_completion(&devinfo->dev_init_करोne);
		/* Make sure that devinfo still exists. Firmware probe routines
		 * may have released the device and cleared the पूर्णांकfdata.
		 */
		अगर (!usb_get_पूर्णांकfdata(पूर्णांकf))
			जाओ करोne;

		brcmf_usb_disconnect_cb(devinfo);
		kमुक्त(devinfo);
	पूर्ण
करोne:
	brcmf_dbg(USB, "Exit\n");
पूर्ण

/*
 * only need to संकेत the bus being करोwn and update the state.
 */
अटल पूर्णांक brcmf_usb_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t state)
अणु
	काष्ठा usb_device *usb = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा brcmf_usbdev_info *devinfo = brcmf_usb_get_businfo(&usb->dev);

	brcmf_dbg(USB, "Enter\n");
	devinfo->bus_pub.state = BRCMFMAC_USB_STATE_SLEEP;
	brcmf_cancel_all_urbs(devinfo);
	device_set_wakeup_enable(devinfo->dev, true);
	वापस 0;
पूर्ण

/*
 * (re-) start the bus.
 */
अटल पूर्णांक brcmf_usb_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_device *usb = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा brcmf_usbdev_info *devinfo = brcmf_usb_get_businfo(&usb->dev);

	brcmf_dbg(USB, "Enter\n");

	devinfo->bus_pub.state = BRCMFMAC_USB_STATE_UP;
	brcmf_usb_rx_fill_all(devinfo);
	device_set_wakeup_enable(devinfo->dev, false);
	वापस 0;
पूर्ण

अटल पूर्णांक brcmf_usb_reset_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_device *usb = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा brcmf_usbdev_info *devinfo = brcmf_usb_get_businfo(&usb->dev);
	काष्ठा brcmf_fw_request *fwreq;
	पूर्णांक ret;

	brcmf_dbg(USB, "Enter\n");

	fwreq = brcmf_usb_prepare_fw_request(devinfo);
	अगर (!fwreq)
		वापस -ENOMEM;

	ret = brcmf_fw_get_firmwares(&usb->dev, fwreq, brcmf_usb_probe_phase2);
	अगर (ret < 0)
		kमुक्त(fwreq);

	वापस ret;
पूर्ण

#घोषणा BRCMF_USB_DEVICE(dev_id)	\
	अणु USB_DEVICE(BRCM_USB_VENDOR_ID_BROADCOM, dev_id) पूर्ण

#घोषणा LINKSYS_USB_DEVICE(dev_id)	\
	अणु USB_DEVICE(BRCM_USB_VENDOR_ID_LINKSYS, dev_id) पूर्ण

#घोषणा CYPRESS_USB_DEVICE(dev_id)	\
	अणु USB_DEVICE(CY_USB_VENDOR_ID_CYPRESS, dev_id) पूर्ण

अटल स्थिर काष्ठा usb_device_id brcmf_usb_devid_table[] = अणु
	BRCMF_USB_DEVICE(BRCM_USB_43143_DEVICE_ID),
	BRCMF_USB_DEVICE(BRCM_USB_43236_DEVICE_ID),
	BRCMF_USB_DEVICE(BRCM_USB_43242_DEVICE_ID),
	BRCMF_USB_DEVICE(BRCM_USB_43569_DEVICE_ID),
	LINKSYS_USB_DEVICE(BRCM_USB_43235_LINKSYS_DEVICE_ID),
	CYPRESS_USB_DEVICE(CY_USB_4373_DEVICE_ID),
	अणु USB_DEVICE(BRCM_USB_VENDOR_ID_LG, BRCM_USB_43242_LG_DEVICE_ID) पूर्ण,
	/* special entry क्रम device with firmware loaded and running */
	BRCMF_USB_DEVICE(BRCM_USB_BCMFW_DEVICE_ID),
	CYPRESS_USB_DEVICE(BRCM_USB_BCMFW_DEVICE_ID),
	अणु /* end: all zeroes */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, brcmf_usb_devid_table);

अटल काष्ठा usb_driver brcmf_usbdrvr = अणु
	.name = KBUILD_MODNAME,
	.probe = brcmf_usb_probe,
	.disconnect = brcmf_usb_disconnect,
	.id_table = brcmf_usb_devid_table,
	.suspend = brcmf_usb_suspend,
	.resume = brcmf_usb_resume,
	.reset_resume = brcmf_usb_reset_resume,
	.supports_स्वतःsuspend = true,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

अटल पूर्णांक brcmf_usb_reset_device(काष्ठा device *dev, व्योम *notused)
अणु
	/* device past is the usb पूर्णांकerface so we
	 * need to use parent here.
	 */
	brcmf_dev_reset(dev->parent);
	वापस 0;
पूर्ण

व्योम brcmf_usb_निकास(व्योम)
अणु
	काष्ठा device_driver *drv = &brcmf_usbdrvr.drvwrap.driver;
	पूर्णांक ret;

	brcmf_dbg(USB, "Enter\n");
	ret = driver_क्रम_each_device(drv, शून्य, शून्य,
				     brcmf_usb_reset_device);
	अगर (ret)
		brcmf_err("failed to reset all usb devices %d\n", ret);

	usb_deरेजिस्टर(&brcmf_usbdrvr);
पूर्ण

पूर्णांक brcmf_usb_रेजिस्टर(व्योम)
अणु
	brcmf_dbg(USB, "Enter\n");
	वापस usb_रेजिस्टर(&brcmf_usbdrvr);
पूर्ण
