<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * usb.c - Hardware dependent module क्रम USB
 *
 * Copyright (C) 2013-2015 Microchip Technology Germany II GmbH & Co. KG
 */

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/usb.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/cdev.h>
#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/completion.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/most.h>

#घोषणा USB_MTU			512
#घोषणा NO_ISOCHRONOUS_URB	0
#घोषणा AV_PACKETS_PER_XACT	2
#घोषणा BUF_CHAIN_SIZE		0xFFFF
#घोषणा MAX_NUM_ENDPOINTS	30
#घोषणा MAX_SUFFIX_LEN		10
#घोषणा MAX_STRING_LEN		80
#घोषणा MAX_BUF_SIZE		0xFFFF

#घोषणा USB_VENDOR_ID_SMSC	0x0424  /* VID: SMSC */
#घोषणा USB_DEV_ID_BRDG		0xC001  /* PID: USB Bridge */
#घोषणा USB_DEV_ID_OS81118	0xCF18  /* PID: USB OS81118 */
#घोषणा USB_DEV_ID_OS81119	0xCF19  /* PID: USB OS81119 */
#घोषणा USB_DEV_ID_OS81210	0xCF30  /* PID: USB OS81210 */
/* DRCI Addresses */
#घोषणा DRCI_REG_NI_STATE	0x0100
#घोषणा DRCI_REG_PACKET_BW	0x0101
#घोषणा DRCI_REG_NODE_ADDR	0x0102
#घोषणा DRCI_REG_NODE_POS	0x0103
#घोषणा DRCI_REG_MEP_FILTER	0x0140
#घोषणा DRCI_REG_HASH_TBL0	0x0141
#घोषणा DRCI_REG_HASH_TBL1	0x0142
#घोषणा DRCI_REG_HASH_TBL2	0x0143
#घोषणा DRCI_REG_HASH_TBL3	0x0144
#घोषणा DRCI_REG_HW_ADDR_HI	0x0145
#घोषणा DRCI_REG_HW_ADDR_MI	0x0146
#घोषणा DRCI_REG_HW_ADDR_LO	0x0147
#घोषणा DRCI_REG_BASE		0x1100
#घोषणा DRCI_COMMAND		0x02
#घोषणा DRCI_READ_REQ		0xA0
#घोषणा DRCI_WRITE_REQ		0xA1

/**
 * काष्ठा most_dci_obj - Direct Communication Interface
 * @kobj:position in sysfs
 * @usb_device: poपूर्णांकer to the usb device
 * @reg_addr: रेजिस्टर address क्रम arbitrary DCI access
 */
काष्ठा most_dci_obj अणु
	काष्ठा device dev;
	काष्ठा usb_device *usb_device;
	u16 reg_addr;
पूर्ण;

#घोषणा to_dci_obj(p) container_of(p, काष्ठा most_dci_obj, dev)

काष्ठा most_dev;

काष्ठा clear_hold_work अणु
	काष्ठा work_काष्ठा ws;
	काष्ठा most_dev *mdev;
	अचिन्हित पूर्णांक channel;
	पूर्णांक pipe;
पूर्ण;

#घोषणा to_clear_hold_work(w) container_of(w, काष्ठा clear_hold_work, ws)

/**
 * काष्ठा most_dev - holds all usb पूर्णांकerface specअगरic stuff
 * @usb_device: poपूर्णांकer to usb device
 * @अगरace: hardware पूर्णांकerface
 * @cap: channel capabilities
 * @conf: channel configuration
 * @dci: direct communication पूर्णांकerface of hardware
 * @ep_address: endpoपूर्णांक address table
 * @description: device description
 * @suffix: suffix क्रम channel name
 * @channel_lock: synchronize channel access
 * @padding_active: indicates channel uses padding
 * @is_channel_healthy: health status table of each channel
 * @busy_urbs: list of anchored items
 * @io_mutex: synchronize I/O with disconnect
 * @link_stat_समयr: समयr क्रम link status reports
 * @poll_work_obj: work क्रम polling link status
 */
काष्ठा most_dev अणु
	काष्ठा device dev;
	काष्ठा usb_device *usb_device;
	काष्ठा most_पूर्णांकerface अगरace;
	काष्ठा most_channel_capability *cap;
	काष्ठा most_channel_config *conf;
	काष्ठा most_dci_obj *dci;
	u8 *ep_address;
	अक्षर description[MAX_STRING_LEN];
	अक्षर suffix[MAX_NUM_ENDPOINTS][MAX_SUFFIX_LEN];
	spinlock_t channel_lock[MAX_NUM_ENDPOINTS]; /* sync channel access */
	bool padding_active[MAX_NUM_ENDPOINTS];
	bool is_channel_healthy[MAX_NUM_ENDPOINTS];
	काष्ठा clear_hold_work clear_work[MAX_NUM_ENDPOINTS];
	काष्ठा usb_anchor *busy_urbs;
	काष्ठा mutex io_mutex;
	काष्ठा समयr_list link_stat_समयr;
	काष्ठा work_काष्ठा poll_work_obj;
	व्योम (*on_netinfo)(काष्ठा most_पूर्णांकerface *most_अगरace,
			   अचिन्हित अक्षर link_state, अचिन्हित अक्षर *addrs);
पूर्ण;

#घोषणा to_mdev(d) container_of(d, काष्ठा most_dev, अगरace)
#घोषणा to_mdev_from_dev(d) container_of(d, काष्ठा most_dev, dev)
#घोषणा to_mdev_from_work(w) container_of(w, काष्ठा most_dev, poll_work_obj)

अटल व्योम wq_clear_halt(काष्ठा work_काष्ठा *wq_obj);
अटल व्योम wq_netinfo(काष्ठा work_काष्ठा *wq_obj);

/**
 * drci_rd_reg - पढ़ो a DCI रेजिस्टर
 * @dev: usb device
 * @reg: रेजिस्टर address
 * @buf: buffer to store data
 *
 * This is पढ़ोs data from INIC's direct रेजिस्टर communication पूर्णांकerface
 */
अटल अंतरभूत पूर्णांक drci_rd_reg(काष्ठा usb_device *dev, u16 reg, u16 *buf)
अणु
	पूर्णांक retval;
	__le16 *dma_buf;
	u8 req_type = USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE;

	dma_buf = kzalloc(माप(*dma_buf), GFP_KERNEL);
	अगर (!dma_buf)
		वापस -ENOMEM;

	retval = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
				 DRCI_READ_REQ, req_type,
				 0x0000,
				 reg, dma_buf, माप(*dma_buf), 5 * HZ);
	*buf = le16_to_cpu(*dma_buf);
	kमुक्त(dma_buf);

	अगर (retval < 0)
		वापस retval;
	वापस 0;
पूर्ण

/**
 * drci_wr_reg - ग_लिखो a DCI रेजिस्टर
 * @dev: usb device
 * @reg: रेजिस्टर address
 * @data: data to ग_लिखो
 *
 * This is ग_लिखोs data to INIC's direct रेजिस्टर communication पूर्णांकerface
 */
अटल अंतरभूत पूर्णांक drci_wr_reg(काष्ठा usb_device *dev, u16 reg, u16 data)
अणु
	वापस usb_control_msg(dev,
			       usb_sndctrlpipe(dev, 0),
			       DRCI_WRITE_REQ,
			       USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			       data,
			       reg,
			       शून्य,
			       0,
			       5 * HZ);
पूर्ण

अटल अंतरभूत पूर्णांक start_sync_ep(काष्ठा usb_device *usb_dev, u16 ep)
अणु
	वापस drci_wr_reg(usb_dev, DRCI_REG_BASE + DRCI_COMMAND + ep * 16, 1);
पूर्ण

/**
 * get_stream_frame_size - calculate frame size of current configuration
 * @dev: device काष्ठाure
 * @cfg: channel configuration
 */
अटल अचिन्हित पूर्णांक get_stream_frame_size(काष्ठा device *dev,
					  काष्ठा most_channel_config *cfg)
अणु
	अचिन्हित पूर्णांक frame_size;
	अचिन्हित पूर्णांक sub_size = cfg->subbuffer_size;

	अगर (!sub_size) अणु
		dev_warn(dev, "Misconfig: Subbuffer size zero.\n");
		वापस 0;
	पूर्ण
	चयन (cfg->data_type) अणु
	हाल MOST_CH_ISOC:
		frame_size = AV_PACKETS_PER_XACT * sub_size;
		अवरोध;
	हाल MOST_CH_SYNC:
		अगर (cfg->packets_per_xact == 0) अणु
			dev_warn(dev, "Misconfig: Packets per XACT zero\n");
			frame_size = 0;
		पूर्ण अन्यथा अगर (cfg->packets_per_xact == 0xFF) अणु
			frame_size = (USB_MTU / sub_size) * sub_size;
		पूर्ण अन्यथा अणु
			frame_size = cfg->packets_per_xact * sub_size;
		पूर्ण
		अवरोध;
	शेष:
		dev_warn(dev, "Query frame size of non-streaming channel\n");
		frame_size = 0;
		अवरोध;
	पूर्ण
	वापस frame_size;
पूर्ण

/**
 * hdm_poison_channel - mark buffers of this channel as invalid
 * @अगरace: poपूर्णांकer to the पूर्णांकerface
 * @channel: channel ID
 *
 * This unlinks all URBs submitted to the HCD,
 * calls the associated completion function of the core and हटाओs
 * them from the list.
 *
 * Returns 0 on success or error code otherwise.
 */
अटल पूर्णांक hdm_poison_channel(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक channel)
अणु
	काष्ठा most_dev *mdev = to_mdev(अगरace);
	अचिन्हित दीर्घ flags;
	spinlock_t *lock; /* temp. lock */

	अगर (channel < 0 || channel >= अगरace->num_channels) अणु
		dev_warn(&mdev->usb_device->dev, "Channel ID out of range.\n");
		वापस -ECHRNG;
	पूर्ण

	lock = mdev->channel_lock + channel;
	spin_lock_irqsave(lock, flags);
	mdev->is_channel_healthy[channel] = false;
	spin_unlock_irqrestore(lock, flags);

	cancel_work_sync(&mdev->clear_work[channel].ws);

	mutex_lock(&mdev->io_mutex);
	usb_समाप्त_anchored_urbs(&mdev->busy_urbs[channel]);
	अगर (mdev->padding_active[channel])
		mdev->padding_active[channel] = false;

	अगर (mdev->conf[channel].data_type == MOST_CH_ASYNC) अणु
		del_समयr_sync(&mdev->link_stat_समयr);
		cancel_work_sync(&mdev->poll_work_obj);
	पूर्ण
	mutex_unlock(&mdev->io_mutex);
	वापस 0;
पूर्ण

/**
 * hdm_add_padding - add padding bytes
 * @mdev: most device
 * @channel: channel ID
 * @mbo: buffer object
 *
 * This inserts the INIC hardware specअगरic padding bytes पूर्णांकo a streaming
 * channel's buffer
 */
अटल पूर्णांक hdm_add_padding(काष्ठा most_dev *mdev, पूर्णांक channel, काष्ठा mbo *mbo)
अणु
	काष्ठा most_channel_config *conf = &mdev->conf[channel];
	अचिन्हित पूर्णांक frame_size = get_stream_frame_size(&mdev->dev, conf);
	अचिन्हित पूर्णांक j, num_frames;

	अगर (!frame_size)
		वापस -EINVAL;
	num_frames = mbo->buffer_length / frame_size;

	अगर (num_frames < 1) अणु
		dev_err(&mdev->usb_device->dev,
			"Missed minimal transfer unit.\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (j = num_frames - 1; j > 0; j--)
		स_हटाओ(mbo->virt_address + j * USB_MTU,
			mbo->virt_address + j * frame_size,
			frame_size);
	mbo->buffer_length = num_frames * USB_MTU;
	वापस 0;
पूर्ण

/**
 * hdm_हटाओ_padding - हटाओ padding bytes
 * @mdev: most device
 * @channel: channel ID
 * @mbo: buffer object
 *
 * This takes the INIC hardware specअगरic padding bytes off a streaming
 * channel's buffer.
 */
अटल पूर्णांक hdm_हटाओ_padding(काष्ठा most_dev *mdev, पूर्णांक channel,
			      काष्ठा mbo *mbo)
अणु
	काष्ठा most_channel_config *स्थिर conf = &mdev->conf[channel];
	अचिन्हित पूर्णांक frame_size = get_stream_frame_size(&mdev->dev, conf);
	अचिन्हित पूर्णांक j, num_frames;

	अगर (!frame_size)
		वापस -EINVAL;
	num_frames = mbo->processed_length / USB_MTU;

	क्रम (j = 1; j < num_frames; j++)
		स_हटाओ(mbo->virt_address + frame_size * j,
			mbo->virt_address + USB_MTU * j,
			frame_size);

	mbo->processed_length = frame_size * num_frames;
	वापस 0;
पूर्ण

/**
 * hdm_ग_लिखो_completion - completion function क्रम submitted Tx URBs
 * @urb: the URB that has been completed
 *
 * This checks the status of the completed URB. In हाल the URB has been
 * unlinked beक्रमe, it is immediately मुक्तd. On any other error the MBO
 * transfer flag is set. On success it मुक्तs allocated resources and calls
 * the completion function.
 *
 * Context: पूर्णांकerrupt!
 */
अटल व्योम hdm_ग_लिखो_completion(काष्ठा urb *urb)
अणु
	काष्ठा mbo *mbo = urb->context;
	काष्ठा most_dev *mdev = to_mdev(mbo->अगरp);
	अचिन्हित पूर्णांक channel = mbo->hdm_channel_id;
	spinlock_t *lock = mdev->channel_lock + channel;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(lock, flags);

	mbo->processed_length = 0;
	mbo->status = MBO_E_INVAL;
	अगर (likely(mdev->is_channel_healthy[channel])) अणु
		चयन (urb->status) अणु
		हाल 0:
		हाल -ESHUTDOWN:
			mbo->processed_length = urb->actual_length;
			mbo->status = MBO_SUCCESS;
			अवरोध;
		हाल -EPIPE:
			dev_warn(&mdev->usb_device->dev,
				 "Broken pipe on ep%02x\n",
				 mdev->ep_address[channel]);
			mdev->is_channel_healthy[channel] = false;
			mdev->clear_work[channel].pipe = urb->pipe;
			schedule_work(&mdev->clear_work[channel].ws);
			अवरोध;
		हाल -ENODEV:
		हाल -EPROTO:
			mbo->status = MBO_E_CLOSE;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(lock, flags);

	अगर (likely(mbo->complete))
		mbo->complete(mbo);
	usb_मुक्त_urb(urb);
पूर्ण

/**
 * hdm_पढ़ो_completion - completion function क्रम submitted Rx URBs
 * @urb: the URB that has been completed
 *
 * This checks the status of the completed URB. In हाल the URB has been
 * unlinked beक्रमe it is immediately मुक्तd. On any other error the MBO transfer
 * flag is set. On success it मुक्तs allocated resources, हटाओs
 * padding bytes -अगर necessary- and calls the completion function.
 *
 * Context: पूर्णांकerrupt!
 */
अटल व्योम hdm_पढ़ो_completion(काष्ठा urb *urb)
अणु
	काष्ठा mbo *mbo = urb->context;
	काष्ठा most_dev *mdev = to_mdev(mbo->अगरp);
	अचिन्हित पूर्णांक channel = mbo->hdm_channel_id;
	काष्ठा device *dev = &mdev->usb_device->dev;
	spinlock_t *lock = mdev->channel_lock + channel;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(lock, flags);

	mbo->processed_length = 0;
	mbo->status = MBO_E_INVAL;
	अगर (likely(mdev->is_channel_healthy[channel])) अणु
		चयन (urb->status) अणु
		हाल 0:
		हाल -ESHUTDOWN:
			mbo->processed_length = urb->actual_length;
			mbo->status = MBO_SUCCESS;
			अगर (mdev->padding_active[channel] &&
			    hdm_हटाओ_padding(mdev, channel, mbo)) अणु
				mbo->processed_length = 0;
				mbo->status = MBO_E_INVAL;
			पूर्ण
			अवरोध;
		हाल -EPIPE:
			dev_warn(dev, "Broken pipe on ep%02x\n",
				 mdev->ep_address[channel]);
			mdev->is_channel_healthy[channel] = false;
			mdev->clear_work[channel].pipe = urb->pipe;
			schedule_work(&mdev->clear_work[channel].ws);
			अवरोध;
		हाल -ENODEV:
		हाल -EPROTO:
			mbo->status = MBO_E_CLOSE;
			अवरोध;
		हाल -EOVERFLOW:
			dev_warn(dev, "Babble on ep%02x\n",
				 mdev->ep_address[channel]);
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(lock, flags);

	अगर (likely(mbo->complete))
		mbo->complete(mbo);
	usb_मुक्त_urb(urb);
पूर्ण

/**
 * hdm_enqueue - receive a buffer to be used क्रम data transfer
 * @अगरace: पूर्णांकerface to enqueue to
 * @channel: ID of the channel
 * @mbo: poपूर्णांकer to the buffer object
 *
 * This allocates a new URB and fills it according to the channel
 * that is being used क्रम transmission of data. Beक्रमe the URB is
 * submitted it is stored in the निजी anchor list.
 *
 * Returns 0 on success. On any error the URB is मुक्तd and a error code
 * is वापसed.
 *
 * Context: Could in _some_ हालs be पूर्णांकerrupt!
 */
अटल पूर्णांक hdm_enqueue(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक channel,
		       काष्ठा mbo *mbo)
अणु
	काष्ठा most_dev *mdev = to_mdev(अगरace);
	काष्ठा most_channel_config *conf;
	पूर्णांक retval = 0;
	काष्ठा urb *urb;
	अचिन्हित दीर्घ length;
	व्योम *virt_address;

	अगर (!mbo)
		वापस -EINVAL;
	अगर (अगरace->num_channels <= channel || channel < 0)
		वापस -ECHRNG;

	urb = usb_alloc_urb(NO_ISOCHRONOUS_URB, GFP_KERNEL);
	अगर (!urb)
		वापस -ENOMEM;

	conf = &mdev->conf[channel];

	mutex_lock(&mdev->io_mutex);
	अगर (!mdev->usb_device) अणु
		retval = -ENODEV;
		जाओ err_मुक्त_urb;
	पूर्ण

	अगर ((conf->direction & MOST_CH_TX) && mdev->padding_active[channel] &&
	    hdm_add_padding(mdev, channel, mbo)) अणु
		retval = -EINVAL;
		जाओ err_मुक्त_urb;
	पूर्ण

	urb->transfer_dma = mbo->bus_address;
	virt_address = mbo->virt_address;
	length = mbo->buffer_length;

	अगर (conf->direction & MOST_CH_TX) अणु
		usb_fill_bulk_urb(urb, mdev->usb_device,
				  usb_sndbulkpipe(mdev->usb_device,
						  mdev->ep_address[channel]),
				  virt_address,
				  length,
				  hdm_ग_लिखो_completion,
				  mbo);
		अगर (conf->data_type != MOST_CH_ISOC &&
		    conf->data_type != MOST_CH_SYNC)
			urb->transfer_flags |= URB_ZERO_PACKET;
	पूर्ण अन्यथा अणु
		usb_fill_bulk_urb(urb, mdev->usb_device,
				  usb_rcvbulkpipe(mdev->usb_device,
						  mdev->ep_address[channel]),
				  virt_address,
				  length + conf->extra_len,
				  hdm_पढ़ो_completion,
				  mbo);
	पूर्ण
	urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	usb_anchor_urb(urb, &mdev->busy_urbs[channel]);

	retval = usb_submit_urb(urb, GFP_KERNEL);
	अगर (retval) अणु
		dev_err(&mdev->usb_device->dev,
			"URB submit failed with error %d.\n", retval);
		जाओ err_unanchor_urb;
	पूर्ण
	mutex_unlock(&mdev->io_mutex);
	वापस 0;

err_unanchor_urb:
	usb_unanchor_urb(urb);
err_मुक्त_urb:
	usb_मुक्त_urb(urb);
	mutex_unlock(&mdev->io_mutex);
	वापस retval;
पूर्ण

अटल व्योम *hdm_dma_alloc(काष्ठा mbo *mbo, u32 size)
अणु
	काष्ठा most_dev *mdev = to_mdev(mbo->अगरp);

	वापस usb_alloc_coherent(mdev->usb_device, size, GFP_KERNEL,
				  &mbo->bus_address);
पूर्ण

अटल व्योम hdm_dma_मुक्त(काष्ठा mbo *mbo, u32 size)
अणु
	काष्ठा most_dev *mdev = to_mdev(mbo->अगरp);

	usb_मुक्त_coherent(mdev->usb_device, size, mbo->virt_address,
			  mbo->bus_address);
पूर्ण

/**
 * hdm_configure_channel - receive channel configuration from core
 * @अगरace: पूर्णांकerface
 * @channel: channel ID
 * @conf: काष्ठाure that holds the configuration inक्रमmation
 *
 * The attached network पूर्णांकerface controller (NIC) supports a padding mode
 * to aव्योम लघु packets on USB, hence increasing the perक्रमmance due to a
 * lower पूर्णांकerrupt load. This mode is शेष क्रम synchronous data and can
 * be चयनed on क्रम isochronous data. In हाल padding is active the
 * driver needs to know the frame size of the payload in order to calculate
 * the number of bytes it needs to pad when transmitting or to cut off when
 * receiving data.
 *
 */
अटल पूर्णांक hdm_configure_channel(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक channel,
				 काष्ठा most_channel_config *conf)
अणु
	अचिन्हित पूर्णांक num_frames;
	अचिन्हित पूर्णांक frame_size;
	काष्ठा most_dev *mdev = to_mdev(अगरace);
	काष्ठा device *dev = &mdev->usb_device->dev;

	अगर (!conf) अणु
		dev_err(dev, "Bad config pointer.\n");
		वापस -EINVAL;
	पूर्ण
	अगर (channel < 0 || channel >= अगरace->num_channels) अणु
		dev_err(dev, "Channel ID out of range.\n");
		वापस -EINVAL;
	पूर्ण

	mdev->is_channel_healthy[channel] = true;
	mdev->clear_work[channel].channel = channel;
	mdev->clear_work[channel].mdev = mdev;
	INIT_WORK(&mdev->clear_work[channel].ws, wq_clear_halt);

	अगर (!conf->num_buffers || !conf->buffer_size) अणु
		dev_err(dev, "Misconfig: buffer size or #buffers zero.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (conf->data_type != MOST_CH_SYNC &&
	    !(conf->data_type == MOST_CH_ISOC &&
	      conf->packets_per_xact != 0xFF)) अणु
		mdev->padding_active[channel] = false;
		/*
		 * Since the NIC's padding mode is not going to be
		 * used, we can skip the frame size calculations and
		 * move directly on to निकास.
		 */
		जाओ निकास;
	पूर्ण

	mdev->padding_active[channel] = true;

	frame_size = get_stream_frame_size(&mdev->dev, conf);
	अगर (frame_size == 0 || frame_size > USB_MTU) अणु
		dev_warn(dev, "Misconfig: frame size wrong\n");
		वापस -EINVAL;
	पूर्ण

	num_frames = conf->buffer_size / frame_size;

	अगर (conf->buffer_size % frame_size) अणु
		u16 old_size = conf->buffer_size;

		conf->buffer_size = num_frames * frame_size;
		dev_warn(dev, "%s: fixed buffer size (%d -> %d)\n",
			 mdev->suffix[channel], old_size, conf->buffer_size);
	पूर्ण

	/* calculate extra length to comply w/ HW padding */
	conf->extra_len = num_frames * (USB_MTU - frame_size);

निकास:
	mdev->conf[channel] = *conf;
	अगर (conf->data_type == MOST_CH_ASYNC) अणु
		u16 ep = mdev->ep_address[channel];

		अगर (start_sync_ep(mdev->usb_device, ep) < 0)
			dev_warn(dev, "sync for ep%02x failed", ep);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * hdm_request_netinfo - request network inक्रमmation
 * @अगरace: poपूर्णांकer to पूर्णांकerface
 * @channel: channel ID
 *
 * This is used as trigger to set up the link status समयr that
 * polls क्रम the NI state of the INIC every 2 seconds.
 *
 */
अटल व्योम hdm_request_netinfo(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक channel,
				व्योम (*on_netinfo)(काष्ठा most_पूर्णांकerface *,
						   अचिन्हित अक्षर,
						   अचिन्हित अक्षर *))
अणु
	काष्ठा most_dev *mdev = to_mdev(अगरace);

	mdev->on_netinfo = on_netinfo;
	अगर (!on_netinfo)
		वापस;

	mdev->link_stat_समयr.expires = jअगरfies + HZ;
	mod_समयr(&mdev->link_stat_समयr, mdev->link_stat_समयr.expires);
पूर्ण

/**
 * link_stat_समयr_handler - schedule work obtaining mac address and link status
 * @data: poपूर्णांकer to USB device instance
 *
 * The handler runs in पूर्णांकerrupt context. That's why we need to defer the
 * tasks to a work queue.
 */
अटल व्योम link_stat_समयr_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा most_dev *mdev = from_समयr(mdev, t, link_stat_समयr);

	schedule_work(&mdev->poll_work_obj);
	mdev->link_stat_समयr.expires = jअगरfies + (2 * HZ);
	add_समयr(&mdev->link_stat_समयr);
पूर्ण

/**
 * wq_netinfo - work queue function to deliver latest networking inक्रमmation
 * @wq_obj: object that holds data क्रम our deferred work to करो
 *
 * This retrieves the network पूर्णांकerface status of the USB INIC
 */
अटल व्योम wq_netinfo(काष्ठा work_काष्ठा *wq_obj)
अणु
	काष्ठा most_dev *mdev = to_mdev_from_work(wq_obj);
	काष्ठा usb_device *usb_device = mdev->usb_device;
	काष्ठा device *dev = &usb_device->dev;
	u16 hi, mi, lo, link;
	u8 hw_addr[6];

	अगर (drci_rd_reg(usb_device, DRCI_REG_HW_ADDR_HI, &hi)) अणु
		dev_err(dev, "Vendor request 'hw_addr_hi' failed\n");
		वापस;
	पूर्ण

	अगर (drci_rd_reg(usb_device, DRCI_REG_HW_ADDR_MI, &mi)) अणु
		dev_err(dev, "Vendor request 'hw_addr_mid' failed\n");
		वापस;
	पूर्ण

	अगर (drci_rd_reg(usb_device, DRCI_REG_HW_ADDR_LO, &lo)) अणु
		dev_err(dev, "Vendor request 'hw_addr_low' failed\n");
		वापस;
	पूर्ण

	अगर (drci_rd_reg(usb_device, DRCI_REG_NI_STATE, &link)) अणु
		dev_err(dev, "Vendor request 'link status' failed\n");
		वापस;
	पूर्ण

	hw_addr[0] = hi >> 8;
	hw_addr[1] = hi;
	hw_addr[2] = mi >> 8;
	hw_addr[3] = mi;
	hw_addr[4] = lo >> 8;
	hw_addr[5] = lo;

	अगर (mdev->on_netinfo)
		mdev->on_netinfo(&mdev->अगरace, link, hw_addr);
पूर्ण

/**
 * wq_clear_halt - work queue function
 * @wq_obj: work_काष्ठा object to execute
 *
 * This sends a clear_halt to the given USB pipe.
 */
अटल व्योम wq_clear_halt(काष्ठा work_काष्ठा *wq_obj)
अणु
	काष्ठा clear_hold_work *clear_work = to_clear_hold_work(wq_obj);
	काष्ठा most_dev *mdev = clear_work->mdev;
	अचिन्हित पूर्णांक channel = clear_work->channel;
	पूर्णांक pipe = clear_work->pipe;
	पूर्णांक snd_pipe;
	पूर्णांक peer;

	mutex_lock(&mdev->io_mutex);
	most_stop_enqueue(&mdev->अगरace, channel);
	usb_समाप्त_anchored_urbs(&mdev->busy_urbs[channel]);
	अगर (usb_clear_halt(mdev->usb_device, pipe))
		dev_warn(&mdev->usb_device->dev, "Failed to reset endpoint.\n");

	/* If the functional Stall condition has been set on an
	 * asynchronous rx channel, we need to clear the tx channel
	 * too, since the hardware runs its clean-up sequence on both
	 * channels, as they are physically one on the network.
	 *
	 * The USB पूर्णांकerface that exposes the asynchronous channels
	 * contains always two endpoपूर्णांकs, and two only.
	 */
	अगर (mdev->conf[channel].data_type == MOST_CH_ASYNC &&
	    mdev->conf[channel].direction == MOST_CH_RX) अणु
		अगर (channel == 0)
			peer = 1;
		अन्यथा
			peer = 0;
		snd_pipe = usb_sndbulkpipe(mdev->usb_device,
					   mdev->ep_address[peer]);
		usb_clear_halt(mdev->usb_device, snd_pipe);
	पूर्ण
	mdev->is_channel_healthy[channel] = true;
	most_resume_enqueue(&mdev->अगरace, channel);
	mutex_unlock(&mdev->io_mutex);
पूर्ण

/**
 * hdm_usb_fops - file operation table क्रम USB driver
 */
अटल स्थिर काष्ठा file_operations hdm_usb_fops = अणु
	.owner = THIS_MODULE,
पूर्ण;

/**
 * usb_device_id - ID table क्रम HCD device probing
 */
अटल स्थिर काष्ठा usb_device_id usbid[] = अणु
	अणु USB_DEVICE(USB_VENDOR_ID_SMSC, USB_DEV_ID_BRDG), पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_SMSC, USB_DEV_ID_OS81118), पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_SMSC, USB_DEV_ID_OS81119), पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_SMSC, USB_DEV_ID_OS81210), पूर्ण,
	अणु पूर्ण /* Terminating entry */
पूर्ण;

काष्ठा regs अणु
	स्थिर अक्षर *name;
	u16 reg;
पूर्ण;

अटल स्थिर काष्ठा regs ro_regs[] = अणु
	अणु "ni_state", DRCI_REG_NI_STATE पूर्ण,
	अणु "packet_bandwidth", DRCI_REG_PACKET_BW पूर्ण,
	अणु "node_address", DRCI_REG_NODE_ADDR पूर्ण,
	अणु "node_position", DRCI_REG_NODE_POS पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regs rw_regs[] = अणु
	अणु "mep_filter", DRCI_REG_MEP_FILTER पूर्ण,
	अणु "mep_hash0", DRCI_REG_HASH_TBL0 पूर्ण,
	अणु "mep_hash1", DRCI_REG_HASH_TBL1 पूर्ण,
	अणु "mep_hash2", DRCI_REG_HASH_TBL2 पूर्ण,
	अणु "mep_hash3", DRCI_REG_HASH_TBL3 पूर्ण,
	अणु "mep_eui48_hi", DRCI_REG_HW_ADDR_HI पूर्ण,
	अणु "mep_eui48_mi", DRCI_REG_HW_ADDR_MI पूर्ण,
	अणु "mep_eui48_lo", DRCI_REG_HW_ADDR_LO पूर्ण,
पूर्ण;

अटल पूर्णांक get_stat_reg_addr(स्थिर काष्ठा regs *regs, पूर्णांक size,
			     स्थिर अक्षर *name, u16 *reg_addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		अगर (sysfs_streq(name, regs[i].name)) अणु
			*reg_addr = regs[i].reg;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

#घोषणा get_अटल_reg_addr(regs, name, reg_addr) \
	get_stat_reg_addr(regs, ARRAY_SIZE(regs), name, reg_addr)

अटल sमाप_प्रकार value_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	स्थिर अक्षर *name = attr->attr.name;
	काष्ठा most_dci_obj *dci_obj = to_dci_obj(dev);
	u16 val;
	u16 reg_addr;
	पूर्णांक err;

	अगर (sysfs_streq(name, "arb_address"))
		वापस snम_लिखो(buf, PAGE_SIZE, "%04x\n", dci_obj->reg_addr);

	अगर (sysfs_streq(name, "arb_value"))
		reg_addr = dci_obj->reg_addr;
	अन्यथा अगर (get_अटल_reg_addr(ro_regs, name, &reg_addr) &&
		 get_अटल_reg_addr(rw_regs, name, &reg_addr))
		वापस -EINVAL;

	err = drci_rd_reg(dci_obj->usb_device, reg_addr, &val);
	अगर (err < 0)
		वापस err;

	वापस snम_लिखो(buf, PAGE_SIZE, "%04x\n", val);
पूर्ण

अटल sमाप_प्रकार value_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u16 val;
	u16 reg_addr;
	स्थिर अक्षर *name = attr->attr.name;
	काष्ठा most_dci_obj *dci_obj = to_dci_obj(dev);
	काष्ठा usb_device *usb_dev = dci_obj->usb_device;
	पूर्णांक err;

	err = kstrtou16(buf, 16, &val);
	अगर (err)
		वापस err;

	अगर (sysfs_streq(name, "arb_address")) अणु
		dci_obj->reg_addr = val;
		वापस count;
	पूर्ण

	अगर (sysfs_streq(name, "arb_value"))
		err = drci_wr_reg(usb_dev, dci_obj->reg_addr, val);
	अन्यथा अगर (sysfs_streq(name, "sync_ep"))
		err = start_sync_ep(usb_dev, val);
	अन्यथा अगर (!get_अटल_reg_addr(rw_regs, name, &reg_addr))
		err = drci_wr_reg(usb_dev, reg_addr, val);
	अन्यथा
		वापस -EINVAL;

	अगर (err < 0)
		वापस err;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(ni_state, 0444, value_show, शून्य);
अटल DEVICE_ATTR(packet_bandwidth, 0444, value_show, शून्य);
अटल DEVICE_ATTR(node_address, 0444, value_show, शून्य);
अटल DEVICE_ATTR(node_position, 0444, value_show, शून्य);
अटल DEVICE_ATTR(sync_ep, 0200, शून्य, value_store);
अटल DEVICE_ATTR(mep_filter, 0644, value_show, value_store);
अटल DEVICE_ATTR(mep_hash0, 0644, value_show, value_store);
अटल DEVICE_ATTR(mep_hash1, 0644, value_show, value_store);
अटल DEVICE_ATTR(mep_hash2, 0644, value_show, value_store);
अटल DEVICE_ATTR(mep_hash3, 0644, value_show, value_store);
अटल DEVICE_ATTR(mep_eui48_hi, 0644, value_show, value_store);
अटल DEVICE_ATTR(mep_eui48_mi, 0644, value_show, value_store);
अटल DEVICE_ATTR(mep_eui48_lo, 0644, value_show, value_store);
अटल DEVICE_ATTR(arb_address, 0644, value_show, value_store);
अटल DEVICE_ATTR(arb_value, 0644, value_show, value_store);

अटल काष्ठा attribute *dci_attrs[] = अणु
	&dev_attr_ni_state.attr,
	&dev_attr_packet_bandwidth.attr,
	&dev_attr_node_address.attr,
	&dev_attr_node_position.attr,
	&dev_attr_sync_ep.attr,
	&dev_attr_mep_filter.attr,
	&dev_attr_mep_hash0.attr,
	&dev_attr_mep_hash1.attr,
	&dev_attr_mep_hash2.attr,
	&dev_attr_mep_hash3.attr,
	&dev_attr_mep_eui48_hi.attr,
	&dev_attr_mep_eui48_mi.attr,
	&dev_attr_mep_eui48_lo.attr,
	&dev_attr_arb_address.attr,
	&dev_attr_arb_value.attr,
	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(dci);

अटल व्योम release_dci(काष्ठा device *dev)
अणु
	काष्ठा most_dci_obj *dci = to_dci_obj(dev);

	put_device(dev->parent);
	kमुक्त(dci);
पूर्ण

अटल व्योम release_mdev(काष्ठा device *dev)
अणु
	काष्ठा most_dev *mdev = to_mdev_from_dev(dev);

	kमुक्त(mdev);
पूर्ण
/**
 * hdm_probe - probe function of USB device driver
 * @पूर्णांकerface: Interface of the attached USB device
 * @id: Poपूर्णांकer to the USB ID table.
 *
 * This allocates and initializes the device instance, adds the new
 * entry to the पूर्णांकernal list, scans the USB descriptors and रेजिस्टरs
 * the पूर्णांकerface with the core.
 * Additionally, the DCI objects are created and the hardware is sync'd.
 *
 * Return 0 on success. In हाल of an error a negative number is वापसed.
 */
अटल पूर्णांक
hdm_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_host_पूर्णांकerface *usb_अगरace_desc = पूर्णांकerface->cur_altsetting;
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा device *dev = &usb_dev->dev;
	काष्ठा most_dev *mdev;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक num_endpoपूर्णांकs;
	काष्ठा most_channel_capability *पंचांगp_cap;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_desc;
	पूर्णांक ret = -ENOMEM;

	mdev = kzalloc(माप(*mdev), GFP_KERNEL);
	अगर (!mdev)
		वापस -ENOMEM;

	usb_set_पूर्णांकfdata(पूर्णांकerface, mdev);
	num_endpoपूर्णांकs = usb_अगरace_desc->desc.bNumEndpoपूर्णांकs;
	अगर (num_endpoपूर्णांकs > MAX_NUM_ENDPOINTS) अणु
		kमुक्त(mdev);
		वापस -EINVAL;
	पूर्ण
	mutex_init(&mdev->io_mutex);
	INIT_WORK(&mdev->poll_work_obj, wq_netinfo);
	समयr_setup(&mdev->link_stat_समयr, link_stat_समयr_handler, 0);

	mdev->usb_device = usb_dev;
	mdev->link_stat_समयr.expires = jअगरfies + (2 * HZ);

	mdev->अगरace.mod = hdm_usb_fops.owner;
	mdev->अगरace.dev = &mdev->dev;
	mdev->अगरace.driver_dev = &पूर्णांकerface->dev;
	mdev->अगरace.पूर्णांकerface = ITYPE_USB;
	mdev->अगरace.configure = hdm_configure_channel;
	mdev->अगरace.request_netinfo = hdm_request_netinfo;
	mdev->अगरace.enqueue = hdm_enqueue;
	mdev->अगरace.poison_channel = hdm_poison_channel;
	mdev->अगरace.dma_alloc = hdm_dma_alloc;
	mdev->अगरace.dma_मुक्त = hdm_dma_मुक्त;
	mdev->अगरace.description = mdev->description;
	mdev->अगरace.num_channels = num_endpoपूर्णांकs;

	snम_लिखो(mdev->description, माप(mdev->description),
		 "%d-%s:%d.%d",
		 usb_dev->bus->busnum,
		 usb_dev->devpath,
		 usb_dev->config->desc.bConfigurationValue,
		 usb_अगरace_desc->desc.bInterfaceNumber);

	mdev->dev.init_name = mdev->description;
	mdev->dev.parent = &पूर्णांकerface->dev;
	mdev->dev.release = release_mdev;
	mdev->conf = kसुस्मृति(num_endpoपूर्णांकs, माप(*mdev->conf), GFP_KERNEL);
	अगर (!mdev->conf)
		जाओ err_मुक्त_mdev;

	mdev->cap = kसुस्मृति(num_endpoपूर्णांकs, माप(*mdev->cap), GFP_KERNEL);
	अगर (!mdev->cap)
		जाओ err_मुक्त_conf;

	mdev->अगरace.channel_vector = mdev->cap;
	mdev->ep_address =
		kसुस्मृति(num_endpoपूर्णांकs, माप(*mdev->ep_address), GFP_KERNEL);
	अगर (!mdev->ep_address)
		जाओ err_मुक्त_cap;

	mdev->busy_urbs =
		kसुस्मृति(num_endpoपूर्णांकs, माप(*mdev->busy_urbs), GFP_KERNEL);
	अगर (!mdev->busy_urbs)
		जाओ err_मुक्त_ep_address;

	पंचांगp_cap = mdev->cap;
	क्रम (i = 0; i < num_endpoपूर्णांकs; i++) अणु
		ep_desc = &usb_अगरace_desc->endpoपूर्णांक[i].desc;
		mdev->ep_address[i] = ep_desc->bEndpoपूर्णांकAddress;
		mdev->padding_active[i] = false;
		mdev->is_channel_healthy[i] = true;

		snम_लिखो(&mdev->suffix[i][0], MAX_SUFFIX_LEN, "ep%02x",
			 mdev->ep_address[i]);

		पंचांगp_cap->name_suffix = &mdev->suffix[i][0];
		पंचांगp_cap->buffer_size_packet = MAX_BUF_SIZE;
		पंचांगp_cap->buffer_size_streaming = MAX_BUF_SIZE;
		पंचांगp_cap->num_buffers_packet = BUF_CHAIN_SIZE;
		पंचांगp_cap->num_buffers_streaming = BUF_CHAIN_SIZE;
		पंचांगp_cap->data_type = MOST_CH_CONTROL | MOST_CH_ASYNC |
				     MOST_CH_ISOC | MOST_CH_SYNC;
		अगर (usb_endpoपूर्णांक_dir_in(ep_desc))
			पंचांगp_cap->direction = MOST_CH_RX;
		अन्यथा
			पंचांगp_cap->direction = MOST_CH_TX;
		पंचांगp_cap++;
		init_usb_anchor(&mdev->busy_urbs[i]);
		spin_lock_init(&mdev->channel_lock[i]);
	पूर्ण
	dev_dbg(dev, "claimed gadget: Vendor=%4.4x ProdID=%4.4x Bus=%02x Device=%02x\n",
		le16_to_cpu(usb_dev->descriptor.idVenकरोr),
		le16_to_cpu(usb_dev->descriptor.idProduct),
		usb_dev->bus->busnum,
		usb_dev->devnum);

	dev_dbg(dev, "device path: /sys/bus/usb/devices/%d-%s:%d.%d\n",
		usb_dev->bus->busnum,
		usb_dev->devpath,
		usb_dev->config->desc.bConfigurationValue,
		usb_अगरace_desc->desc.bInterfaceNumber);

	ret = most_रेजिस्टर_पूर्णांकerface(&mdev->अगरace);
	अगर (ret)
		जाओ err_मुक्त_busy_urbs;

	mutex_lock(&mdev->io_mutex);
	अगर (le16_to_cpu(usb_dev->descriptor.idProduct) == USB_DEV_ID_OS81118 ||
	    le16_to_cpu(usb_dev->descriptor.idProduct) == USB_DEV_ID_OS81119 ||
	    le16_to_cpu(usb_dev->descriptor.idProduct) == USB_DEV_ID_OS81210) अणु
		mdev->dci = kzalloc(माप(*mdev->dci), GFP_KERNEL);
		अगर (!mdev->dci) अणु
			mutex_unlock(&mdev->io_mutex);
			most_deरेजिस्टर_पूर्णांकerface(&mdev->अगरace);
			ret = -ENOMEM;
			जाओ err_मुक्त_busy_urbs;
		पूर्ण

		mdev->dci->dev.init_name = "dci";
		mdev->dci->dev.parent = get_device(mdev->अगरace.dev);
		mdev->dci->dev.groups = dci_groups;
		mdev->dci->dev.release = release_dci;
		अगर (device_रेजिस्टर(&mdev->dci->dev)) अणु
			mutex_unlock(&mdev->io_mutex);
			most_deरेजिस्टर_पूर्णांकerface(&mdev->अगरace);
			ret = -ENOMEM;
			जाओ err_मुक्त_dci;
		पूर्ण
		mdev->dci->usb_device = mdev->usb_device;
	पूर्ण
	mutex_unlock(&mdev->io_mutex);
	वापस 0;
err_मुक्त_dci:
	put_device(&mdev->dci->dev);
err_मुक्त_busy_urbs:
	kमुक्त(mdev->busy_urbs);
err_मुक्त_ep_address:
	kमुक्त(mdev->ep_address);
err_मुक्त_cap:
	kमुक्त(mdev->cap);
err_मुक्त_conf:
	kमुक्त(mdev->conf);
err_मुक्त_mdev:
	put_device(&mdev->dev);
	वापस ret;
पूर्ण

/**
 * hdm_disconnect - disconnect function of USB device driver
 * @पूर्णांकerface: Interface of the attached USB device
 *
 * This deरेजिस्टरs the पूर्णांकerface with the core, हटाओs the kernel समयr
 * and मुक्तs resources.
 *
 * Context: hub kernel thपढ़ो
 */
अटल व्योम hdm_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा most_dev *mdev = usb_get_पूर्णांकfdata(पूर्णांकerface);

	mutex_lock(&mdev->io_mutex);
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
	mdev->usb_device = शून्य;
	mutex_unlock(&mdev->io_mutex);

	del_समयr_sync(&mdev->link_stat_समयr);
	cancel_work_sync(&mdev->poll_work_obj);

	अगर (mdev->dci)
		device_unरेजिस्टर(&mdev->dci->dev);
	most_deरेजिस्टर_पूर्णांकerface(&mdev->अगरace);

	kमुक्त(mdev->busy_urbs);
	kमुक्त(mdev->cap);
	kमुक्त(mdev->conf);
	kमुक्त(mdev->ep_address);
	put_device(&mdev->dci->dev);
	put_device(&mdev->dev);
पूर्ण

अटल पूर्णांक hdm_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकerface, pm_message_t message)
अणु
	काष्ठा most_dev *mdev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	पूर्णांक i;

	mutex_lock(&mdev->io_mutex);
	क्रम (i = 0; i < mdev->अगरace.num_channels; i++) अणु
		most_stop_enqueue(&mdev->अगरace, i);
		usb_समाप्त_anchored_urbs(&mdev->busy_urbs[i]);
	पूर्ण
	mutex_unlock(&mdev->io_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक hdm_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा most_dev *mdev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	पूर्णांक i;

	mutex_lock(&mdev->io_mutex);
	क्रम (i = 0; i < mdev->अगरace.num_channels; i++)
		most_resume_enqueue(&mdev->अगरace, i);
	mutex_unlock(&mdev->io_mutex);
	वापस 0;
पूर्ण

अटल काष्ठा usb_driver hdm_usb = अणु
	.name = "hdm_usb",
	.id_table = usbid,
	.probe = hdm_probe,
	.disconnect = hdm_disconnect,
	.resume = hdm_resume,
	.suspend = hdm_suspend,
पूर्ण;

module_usb_driver(hdm_usb);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Gromm <christian.gromm@microchip.com>");
MODULE_DESCRIPTION("HDM_4_USB");
