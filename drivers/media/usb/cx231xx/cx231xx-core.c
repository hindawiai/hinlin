<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
   cx231xx-core.c - driver क्रम Conexant Cx23100/101/102
				USB video capture devices

   Copyright (C) 2008 <srinivasa.deevi at conexant करोt com>
				Based on em28xx driver

 */

#समावेश "cx231xx.h"
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/tuner.h>

#समावेश "cx231xx-reg.h"

/* #घोषणा ENABLE_DEBUG_ISOC_FRAMES */

अटल अचिन्हित पूर्णांक core_debug;
module_param(core_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(core_debug, "enable debug messages [core]");

#घोषणा cx231xx_coredbg(fmt, arg...) करो अणु\
	अगर (core_debug) \
		prपूर्णांकk(KERN_INFO "%s %s :"fmt, \
			 dev->name, __func__ , ##arg); पूर्ण जबतक (0)

अटल अचिन्हित पूर्णांक reg_debug;
module_param(reg_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(reg_debug, "enable debug messages [URB reg]");

अटल पूर्णांक alt = CX231XX_PINOUT;
module_param(alt, पूर्णांक, 0644);
MODULE_PARM_DESC(alt, "alternate setting to use for video endpoint");

#घोषणा cx231xx_isocdbg(fmt, arg...) करो अणु\
	अगर (core_debug) \
		prपूर्णांकk(KERN_INFO "%s %s :"fmt, \
			 dev->name, __func__ , ##arg); पूर्ण जबतक (0)

/*****************************************************************
*             Device control list functions					 *
******************************************************************/

LIST_HEAD(cx231xx_devlist);
अटल DEFINE_MUTEX(cx231xx_devlist_mutex);

/*
 * cx231xx_realease_resources()
 * unरेजिस्टरs the v4l2,i2c and usb devices
 * called when the device माला_लो disconnected or at module unload
*/
व्योम cx231xx_हटाओ_from_devlist(काष्ठा cx231xx *dev)
अणु
	अगर (dev == शून्य)
		वापस;
	अगर (dev->udev == शून्य)
		वापस;

	अगर (atomic_पढ़ो(&dev->devlist_count) > 0) अणु
		mutex_lock(&cx231xx_devlist_mutex);
		list_del(&dev->devlist);
		atomic_dec(&dev->devlist_count);
		mutex_unlock(&cx231xx_devlist_mutex);
	पूर्ण
पूर्ण;

व्योम cx231xx_add_पूर्णांकo_devlist(काष्ठा cx231xx *dev)
अणु
	mutex_lock(&cx231xx_devlist_mutex);
	list_add_tail(&dev->devlist, &cx231xx_devlist);
	atomic_inc(&dev->devlist_count);
	mutex_unlock(&cx231xx_devlist_mutex);
पूर्ण;

अटल LIST_HEAD(cx231xx_extension_devlist);

पूर्णांक cx231xx_रेजिस्टर_extension(काष्ठा cx231xx_ops *ops)
अणु
	काष्ठा cx231xx *dev = शून्य;

	mutex_lock(&cx231xx_devlist_mutex);
	list_add_tail(&ops->next, &cx231xx_extension_devlist);
	list_क्रम_each_entry(dev, &cx231xx_devlist, devlist) अणु
		ops->init(dev);
		dev_info(dev->dev, "%s initialized\n", ops->name);
	पूर्ण
	mutex_unlock(&cx231xx_devlist_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cx231xx_रेजिस्टर_extension);

व्योम cx231xx_unरेजिस्टर_extension(काष्ठा cx231xx_ops *ops)
अणु
	काष्ठा cx231xx *dev = शून्य;

	mutex_lock(&cx231xx_devlist_mutex);
	list_क्रम_each_entry(dev, &cx231xx_devlist, devlist) अणु
		ops->fini(dev);
		dev_info(dev->dev, "%s removed\n", ops->name);
	पूर्ण

	list_del(&ops->next);
	mutex_unlock(&cx231xx_devlist_mutex);
पूर्ण
EXPORT_SYMBOL(cx231xx_unरेजिस्टर_extension);

व्योम cx231xx_init_extension(काष्ठा cx231xx *dev)
अणु
	काष्ठा cx231xx_ops *ops = शून्य;

	mutex_lock(&cx231xx_devlist_mutex);
	list_क्रम_each_entry(ops, &cx231xx_extension_devlist, next) अणु
		अगर (ops->init)
			ops->init(dev);
	पूर्ण
	mutex_unlock(&cx231xx_devlist_mutex);
पूर्ण

व्योम cx231xx_बंद_extension(काष्ठा cx231xx *dev)
अणु
	काष्ठा cx231xx_ops *ops = शून्य;

	mutex_lock(&cx231xx_devlist_mutex);
	list_क्रम_each_entry(ops, &cx231xx_extension_devlist, next) अणु
		अगर (ops->fini)
			ops->fini(dev);
	पूर्ण
	mutex_unlock(&cx231xx_devlist_mutex);
पूर्ण

/****************************************************************
*               U S B related functions                         *
*****************************************************************/
पूर्णांक cx231xx_send_usb_command(काष्ठा cx231xx_i2c *i2c_bus,
			     काष्ठा cx231xx_i2c_xfer_data *req_data)
अणु
	पूर्णांक status = 0;
	काष्ठा cx231xx *dev = i2c_bus->dev;
	काष्ठा VENDOR_REQUEST_IN ven_req;

	u8 saddr_len = 0;
	u8 _i2c_period = 0;
	u8 _i2c_nostop = 0;
	u8 _i2c_reserve = 0;

	अगर (dev->state & DEV_DISCONNECTED)
		वापस -ENODEV;

	/* Get the I2C period, nostop and reserve parameters */
	_i2c_period = i2c_bus->i2c_period;
	_i2c_nostop = i2c_bus->i2c_nostop;
	_i2c_reserve = i2c_bus->i2c_reserve;

	saddr_len = req_data->saddr_len;

	/* Set wValue */
	ven_req.wValue = (req_data->dev_addr << 9 | _i2c_period << 4 |
			  saddr_len << 2 | _i2c_nostop << 1 | I2C_SYNC |
			  _i2c_reserve << 6);

	/* set channel number */
	अगर (req_data->direction & I2C_M_RD) अणु
		/* channel number, क्रम पढ़ो,spec required channel_num +4 */
		ven_req.bRequest = i2c_bus->nr + 4;
	पूर्ण अन्यथा
		ven_req.bRequest = i2c_bus->nr;	/* channel number,  */

	/* set index value */
	चयन (saddr_len) अणु
	हाल 0:
		ven_req.wIndex = 0;	/* need check */
		अवरोध;
	हाल 1:
		ven_req.wIndex = (req_data->saddr_dat & 0xff);
		अवरोध;
	हाल 2:
		ven_req.wIndex = req_data->saddr_dat;
		अवरोध;
	पूर्ण

	/* set wLength value */
	ven_req.wLength = req_data->buf_size;

	/* set bData value */
	ven_req.bData = 0;

	/* set the direction */
	अगर (req_data->direction) अणु
		ven_req.direction = USB_सूची_IN;
		स_रखो(req_data->p_buffer, 0x00, ven_req.wLength);
	पूर्ण अन्यथा
		ven_req.direction = USB_सूची_OUT;

	/* set the buffer क्रम पढ़ो / ग_लिखो */
	ven_req.pBuff = req_data->p_buffer;


	/* call common venकरोr command request */
	status = cx231xx_send_venकरोr_cmd(dev, &ven_req);
	अगर (status < 0 && !dev->i2c_scan_running) अणु
		dev_err(dev->dev, "%s: failed with status -%d\n",
			__func__, status);
	पूर्ण

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(cx231xx_send_usb_command);

/*
 * Sends/Receives URB control messages, assuring to use a kalloced buffer
 * क्रम all operations (dev->urb_buf), to aव्योम using stacked buffers, as
 * they aren't safe क्रम usage with USB, due to DMA restrictions.
 * Also implements the debug code क्रम control URB's.
 */
अटल पूर्णांक __usb_control_msg(काष्ठा cx231xx *dev, अचिन्हित पूर्णांक pipe,
	__u8 request, __u8 requesttype, __u16 value, __u16 index,
	व्योम *data, __u16 size, पूर्णांक समयout)
अणु
	पूर्णांक rc, i;

	अगर (reg_debug) अणु
		prपूर्णांकk(KERN_DEBUG "%s: (pipe 0x%08x): %s:  %02x %02x %02x %02x %02x %02x %02x %02x ",
				dev->name,
				pipe,
				(requesttype & USB_सूची_IN) ? "IN" : "OUT",
				requesttype,
				request,
				value & 0xff, value >> 8,
				index & 0xff, index >> 8,
				size & 0xff, size >> 8);
		अगर (!(requesttype & USB_सूची_IN)) अणु
			prपूर्णांकk(KERN_CONT ">>>");
			क्रम (i = 0; i < size; i++)
				prपूर्णांकk(KERN_CONT " %02x",
				       ((अचिन्हित अक्षर *)data)[i]);
		पूर्ण
	पूर्ण

	/* Do the real call to usb_control_msg */
	mutex_lock(&dev->ctrl_urb_lock);
	अगर (!(requesttype & USB_सूची_IN) && size)
		स_नकल(dev->urb_buf, data, size);
	rc = usb_control_msg(dev->udev, pipe, request, requesttype, value,
			     index, dev->urb_buf, size, समयout);
	अगर ((requesttype & USB_सूची_IN) && size)
		स_नकल(data, dev->urb_buf, size);
	mutex_unlock(&dev->ctrl_urb_lock);

	अगर (reg_debug) अणु
		अगर (unlikely(rc < 0)) अणु
			prपूर्णांकk(KERN_CONT "FAILED!\n");
			वापस rc;
		पूर्ण

		अगर ((requesttype & USB_सूची_IN)) अणु
			prपूर्णांकk(KERN_CONT "<<<");
			क्रम (i = 0; i < size; i++)
				prपूर्णांकk(KERN_CONT " %02x",
				       ((अचिन्हित अक्षर *)data)[i]);
		पूर्ण
		prपूर्णांकk(KERN_CONT "\n");
	पूर्ण

	वापस rc;
पूर्ण


/*
 * cx231xx_पढ़ो_ctrl_reg()
 * पढ़ोs data from the usb device specअगरying bRequest and wValue
 */
पूर्णांक cx231xx_पढ़ो_ctrl_reg(काष्ठा cx231xx *dev, u8 req, u16 reg,
			  अक्षर *buf, पूर्णांक len)
अणु
	u8 val = 0;
	पूर्णांक ret;
	पूर्णांक pipe = usb_rcvctrlpipe(dev->udev, 0);

	अगर (dev->state & DEV_DISCONNECTED)
		वापस -ENODEV;

	अगर (len > URB_MAX_CTRL_SIZE)
		वापस -EINVAL;

	चयन (len) अणु
	हाल 1:
		val = ENABLE_ONE_BYTE;
		अवरोध;
	हाल 2:
		val = ENABLE_TWE_BYTE;
		अवरोध;
	हाल 3:
		val = ENABLE_THREE_BYTE;
		अवरोध;
	हाल 4:
		val = ENABLE_FOUR_BYTE;
		अवरोध;
	शेष:
		val = 0xFF;	/* invalid option */
	पूर्ण

	अगर (val == 0xFF)
		वापस -EINVAL;

	ret = __usb_control_msg(dev, pipe, req,
			      USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      val, reg, buf, len, HZ);
	वापस ret;
पूर्ण

पूर्णांक cx231xx_send_venकरोr_cmd(काष्ठा cx231xx *dev,
				काष्ठा VENDOR_REQUEST_IN *ven_req)
अणु
	पूर्णांक ret;
	पूर्णांक pipe = 0;
	पूर्णांक unsend_size = 0;
	u8 *pdata;

	अगर (dev->state & DEV_DISCONNECTED)
		वापस -ENODEV;

	अगर ((ven_req->wLength > URB_MAX_CTRL_SIZE))
		वापस -EINVAL;

	अगर (ven_req->direction)
		pipe = usb_rcvctrlpipe(dev->udev, 0);
	अन्यथा
		pipe = usb_sndctrlpipe(dev->udev, 0);

	/*
	 * If the cx23102 पढ़ो more than 4 bytes with i2c bus,
	 * need chop to 4 byte per request
	 */
	अगर ((ven_req->wLength > 4) && ((ven_req->bRequest == 0x4) ||
					(ven_req->bRequest == 0x5) ||
					(ven_req->bRequest == 0x6) ||

					/* Internal Master 3 Bus can send
					 * and receive only 4 bytes per समय
					 */
					(ven_req->bRequest == 0x2))) अणु
		unsend_size = 0;
		pdata = ven_req->pBuff;


		unsend_size = ven_req->wLength;

		/* the first package */
		ven_req->wValue = ven_req->wValue & 0xFFFB;
		ven_req->wValue = (ven_req->wValue & 0xFFBD) | 0x2;
		ret = __usb_control_msg(dev, pipe, ven_req->bRequest,
			ven_req->direction | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			ven_req->wValue, ven_req->wIndex, pdata,
			0x0004, HZ);
		unsend_size = unsend_size - 4;

		/* the middle package */
		ven_req->wValue = (ven_req->wValue & 0xFFBD) | 0x42;
		जबतक (unsend_size - 4 > 0) अणु
			pdata = pdata + 4;
			ret = __usb_control_msg(dev, pipe,
				ven_req->bRequest,
				ven_req->direction | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				ven_req->wValue, ven_req->wIndex, pdata,
				0x0004, HZ);
			unsend_size = unsend_size - 4;
		पूर्ण

		/* the last package */
		ven_req->wValue = (ven_req->wValue & 0xFFBD) | 0x40;
		pdata = pdata + 4;
		ret = __usb_control_msg(dev, pipe, ven_req->bRequest,
			ven_req->direction | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			ven_req->wValue, ven_req->wIndex, pdata,
			unsend_size, HZ);
	पूर्ण अन्यथा अणु
		ret = __usb_control_msg(dev, pipe, ven_req->bRequest,
				ven_req->direction | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				ven_req->wValue, ven_req->wIndex,
				ven_req->pBuff, ven_req->wLength, HZ);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * cx231xx_ग_लिखो_ctrl_reg()
 * sends data to the usb device, specअगरying bRequest
 */
पूर्णांक cx231xx_ग_लिखो_ctrl_reg(काष्ठा cx231xx *dev, u8 req, u16 reg, अक्षर *buf,
			   पूर्णांक len)
अणु
	u8 val = 0;
	पूर्णांक ret;
	पूर्णांक pipe = usb_sndctrlpipe(dev->udev, 0);

	अगर (dev->state & DEV_DISCONNECTED)
		वापस -ENODEV;

	अगर ((len < 1) || (len > URB_MAX_CTRL_SIZE))
		वापस -EINVAL;

	चयन (len) अणु
	हाल 1:
		val = ENABLE_ONE_BYTE;
		अवरोध;
	हाल 2:
		val = ENABLE_TWE_BYTE;
		अवरोध;
	हाल 3:
		val = ENABLE_THREE_BYTE;
		अवरोध;
	हाल 4:
		val = ENABLE_FOUR_BYTE;
		अवरोध;
	शेष:
		val = 0xFF;	/* invalid option */
	पूर्ण

	अगर (val == 0xFF)
		वापस -EINVAL;

	अगर (reg_debug) अणु
		पूर्णांक byte;

		cx231xx_isocdbg("(pipe 0x%08x): OUT: %02x %02x %02x %02x %02x %02x %02x %02x >>>",
			pipe,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			req, 0, val, reg & 0xff,
			reg >> 8, len & 0xff, len >> 8);

		क्रम (byte = 0; byte < len; byte++)
			cx231xx_isocdbg(" %02x", (अचिन्हित अक्षर)buf[byte]);
		cx231xx_isocdbg("\n");
	पूर्ण

	ret = __usb_control_msg(dev, pipe, req,
			      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      val, reg, buf, len, HZ);

	वापस ret;
पूर्ण

/****************************************************************
*           USB Alternate Setting functions                     *
*****************************************************************/

पूर्णांक cx231xx_set_video_alternate(काष्ठा cx231xx *dev)
अणु
	पूर्णांक errCode, prev_alt = dev->video_mode.alt;
	अचिन्हित पूर्णांक min_pkt_size = dev->width * 2 + 4;
	u32 usb_पूर्णांकerface_index = 0;

	/* When image size is bigger than a certain value,
	   the frame size should be increased, otherwise, only
	   green screen will be received.
	 */
	अगर (dev->width * 2 * dev->height > 720 * 240 * 2)
		min_pkt_size *= 2;

	अगर (dev->width > 360) अणु
		/* resolutions: 720,704,640 */
		dev->video_mode.alt = 3;
	पूर्ण अन्यथा अगर (dev->width > 180) अणु
		/* resolutions: 360,352,320,240 */
		dev->video_mode.alt = 2;
	पूर्ण अन्यथा अगर (dev->width > 0) अणु
		/* resolutions: 180,176,160,128,88 */
		dev->video_mode.alt = 1;
	पूर्ण अन्यथा अणु
		/* Change to alt0 BULK to release USB bandwidth */
		dev->video_mode.alt = 0;
	पूर्ण

	अगर (dev->USE_ISO == 0)
		dev->video_mode.alt = 0;

	cx231xx_coredbg("dev->video_mode.alt= %d\n", dev->video_mode.alt);

	/* Get the correct video पूर्णांकerface Index */
	usb_पूर्णांकerface_index =
	    dev->current_pcb_config.hs_config_info[0].पूर्णांकerface_info.
	    video_index + 1;

	अगर (dev->video_mode.alt != prev_alt) अणु
		cx231xx_coredbg("minimum isoc packet size: %u (alt=%d)\n",
				min_pkt_size, dev->video_mode.alt);

		अगर (dev->video_mode.alt_max_pkt_size != शून्य)
			dev->video_mode.max_pkt_size =
			dev->video_mode.alt_max_pkt_size[dev->video_mode.alt];
		cx231xx_coredbg("setting alternate %d with wMaxPacketSize=%u\n",
				dev->video_mode.alt,
				dev->video_mode.max_pkt_size);
		errCode =
		    usb_set_पूर्णांकerface(dev->udev, usb_पूर्णांकerface_index,
				      dev->video_mode.alt);
		अगर (errCode < 0) अणु
			dev_err(dev->dev,
				"cannot change alt number to %d (error=%i)\n",
				dev->video_mode.alt, errCode);
			वापस errCode;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक cx231xx_set_alt_setting(काष्ठा cx231xx *dev, u8 index, u8 alt)
अणु
	पूर्णांक status = 0;
	u32 usb_पूर्णांकerface_index = 0;
	u32 max_pkt_size = 0;

	चयन (index) अणु
	हाल INDEX_TS1:
		usb_पूर्णांकerface_index =
		    dev->current_pcb_config.hs_config_info[0].पूर्णांकerface_info.
		    ts1_index + 1;
		dev->ts1_mode.alt = alt;
		अगर (dev->ts1_mode.alt_max_pkt_size != शून्य)
			max_pkt_size = dev->ts1_mode.max_pkt_size =
			    dev->ts1_mode.alt_max_pkt_size[dev->ts1_mode.alt];
		अवरोध;
	हाल INDEX_TS2:
		usb_पूर्णांकerface_index =
		    dev->current_pcb_config.hs_config_info[0].पूर्णांकerface_info.
		    ts2_index + 1;
		अवरोध;
	हाल INDEX_AUDIO:
		usb_पूर्णांकerface_index =
		    dev->current_pcb_config.hs_config_info[0].पूर्णांकerface_info.
		    audio_index + 1;
		dev->adev.alt = alt;
		अगर (dev->adev.alt_max_pkt_size != शून्य)
			max_pkt_size = dev->adev.max_pkt_size =
			    dev->adev.alt_max_pkt_size[dev->adev.alt];
		अवरोध;
	हाल INDEX_VIDEO:
		usb_पूर्णांकerface_index =
		    dev->current_pcb_config.hs_config_info[0].पूर्णांकerface_info.
		    video_index + 1;
		dev->video_mode.alt = alt;
		अगर (dev->video_mode.alt_max_pkt_size != शून्य)
			max_pkt_size = dev->video_mode.max_pkt_size =
			    dev->video_mode.alt_max_pkt_size[dev->video_mode.
							     alt];
		अवरोध;
	हाल INDEX_VANC:
		अगर (dev->board.no_alt_vanc)
			वापस 0;
		usb_पूर्णांकerface_index =
		    dev->current_pcb_config.hs_config_info[0].पूर्णांकerface_info.
		    vanc_index + 1;
		dev->vbi_mode.alt = alt;
		अगर (dev->vbi_mode.alt_max_pkt_size != शून्य)
			max_pkt_size = dev->vbi_mode.max_pkt_size =
			    dev->vbi_mode.alt_max_pkt_size[dev->vbi_mode.alt];
		अवरोध;
	हाल INDEX_HANC:
		usb_पूर्णांकerface_index =
		    dev->current_pcb_config.hs_config_info[0].पूर्णांकerface_info.
		    hanc_index + 1;
		dev->sliced_cc_mode.alt = alt;
		अगर (dev->sliced_cc_mode.alt_max_pkt_size != शून्य)
			max_pkt_size = dev->sliced_cc_mode.max_pkt_size =
			    dev->sliced_cc_mode.alt_max_pkt_size[dev->
								 sliced_cc_mode.
								 alt];
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (alt > 0 && max_pkt_size == 0) अणु
		dev_err(dev->dev,
			"can't change interface %d alt no. to %d: Max. Pkt size = 0\n",
			usb_पूर्णांकerface_index, alt);
		/*To workaround error number=-71 on EP0 क्रम videograbber,
		 need add following codes.*/
		अगर (dev->board.no_alt_vanc)
			वापस -1;
	पूर्ण

	cx231xx_coredbg("setting alternate %d with wMaxPacketSize=%u,Interface = %d\n",
			alt, max_pkt_size,
			usb_पूर्णांकerface_index);

	अगर (usb_पूर्णांकerface_index > 0) अणु
		status = usb_set_पूर्णांकerface(dev->udev, usb_पूर्णांकerface_index, alt);
		अगर (status < 0) अणु
			dev_err(dev->dev,
				"can't change interface %d alt no. to %d (err=%i)\n",
				usb_पूर्णांकerface_index, alt, status);
			वापस status;
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(cx231xx_set_alt_setting);

पूर्णांक cx231xx_gpio_set(काष्ठा cx231xx *dev, काष्ठा cx231xx_reg_seq *gpio)
अणु
	पूर्णांक rc = 0;

	अगर (!gpio)
		वापस rc;

	/* Send GPIO reset sequences specअगरied at board entry */
	जबतक (gpio->sleep >= 0) अणु
		rc = cx231xx_set_gpio_value(dev, gpio->bit, gpio->val);
		अगर (rc < 0)
			वापस rc;

		अगर (gpio->sleep > 0)
			msleep(gpio->sleep);

		gpio++;
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक cx231xx_demod_reset(काष्ठा cx231xx *dev)
अणु

	u8 status = 0;
	u8 value[4] = अणु 0, 0, 0, 0 पूर्ण;

	status = cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, PWR_CTL_EN,
				 value, 4);

	cx231xx_coredbg("reg0x%x=0x%x 0x%x 0x%x 0x%x\n", PWR_CTL_EN,
			value[0], value[1], value[2], value[3]);

	cx231xx_coredbg("Enter cx231xx_demod_reset()\n");

	value[1] = (u8) 0x3;
	status = cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER,
					PWR_CTL_EN, value, 4);
	msleep(10);

	value[1] = (u8) 0x0;
	status = cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER,
					PWR_CTL_EN, value, 4);
	msleep(10);

	value[1] = (u8) 0x3;
	status = cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER,
					PWR_CTL_EN, value, 4);
	msleep(10);

	status = cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, PWR_CTL_EN,
				 value, 4);

	cx231xx_coredbg("reg0x%x=0x%x 0x%x 0x%x 0x%x\n", PWR_CTL_EN,
			value[0], value[1], value[2], value[3]);

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(cx231xx_demod_reset);
पूर्णांक is_fw_load(काष्ठा cx231xx *dev)
अणु
	वापस cx231xx_check_fw(dev);
पूर्ण
EXPORT_SYMBOL_GPL(is_fw_load);

पूर्णांक cx231xx_set_mode(काष्ठा cx231xx *dev, क्रमागत cx231xx_mode set_mode)
अणु
	पूर्णांक errCode = 0;

	अगर (dev->mode == set_mode)
		वापस 0;

	अगर (set_mode == CX231XX_SUSPEND) अणु
		/* Set the chip in घातer saving mode */
		dev->mode = set_mode;
	पूर्ण

	/* Resource is locked */
	अगर (dev->mode != CX231XX_SUSPEND)
		वापस -EINVAL;

	dev->mode = set_mode;

	अगर (dev->mode == CX231XX_DIGITAL_MODE)/* Set Digital घातer mode */ अणु
	/* set AGC mode to Digital */
		चयन (dev->model) अणु
		हाल CX231XX_BOARD_CNXT_CARRAERA:
		हाल CX231XX_BOARD_CNXT_RDE_250:
		हाल CX231XX_BOARD_CNXT_SHELBY:
		हाल CX231XX_BOARD_CNXT_RDU_250:
		errCode = cx231xx_set_agc_analog_digital_mux_select(dev, 0);
			अवरोध;
		हाल CX231XX_BOARD_CNXT_RDE_253S:
		हाल CX231XX_BOARD_CNXT_RDU_253S:
		हाल CX231XX_BOARD_PV_PLAYTV_USB_HYBRID:
			errCode = cx231xx_set_agc_analog_digital_mux_select(dev, 1);
			अवरोध;
		हाल CX231XX_BOARD_HAUPPAUGE_EXETER:
		हाल CX231XX_BOARD_HAUPPAUGE_930C_HD_1113xx:
			errCode = cx231xx_set_घातer_mode(dev,
						POLARIS_AVMODE_DIGITAL);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा/* Set Analog Power mode */ अणु
	/* set AGC mode to Analog */
		चयन (dev->model) अणु
		हाल CX231XX_BOARD_CNXT_CARRAERA:
		हाल CX231XX_BOARD_CNXT_RDE_250:
		हाल CX231XX_BOARD_CNXT_SHELBY:
		हाल CX231XX_BOARD_CNXT_RDU_250:
		errCode = cx231xx_set_agc_analog_digital_mux_select(dev, 1);
			अवरोध;
		हाल CX231XX_BOARD_CNXT_RDE_253S:
		हाल CX231XX_BOARD_CNXT_RDU_253S:
		हाल CX231XX_BOARD_HAUPPAUGE_EXETER:
		हाल CX231XX_BOARD_HAUPPAUGE_930C_HD_1113xx:
		हाल CX231XX_BOARD_PV_PLAYTV_USB_HYBRID:
		हाल CX231XX_BOARD_HAUPPAUGE_USB2_FM_PAL:
		हाल CX231XX_BOARD_HAUPPAUGE_USB2_FM_NTSC:
			errCode = cx231xx_set_agc_analog_digital_mux_select(dev, 0);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (errCode < 0) अणु
		dev_err(dev->dev, "Failed to set devmode to %s: error: %i",
			dev->mode == CX231XX_DIGITAL_MODE ? "digital" : "analog",
			errCode);
		वापस errCode;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cx231xx_set_mode);

पूर्णांक cx231xx_ep5_bulkout(काष्ठा cx231xx *dev, u8 *firmware, u16 size)
अणु
	पूर्णांक errCode = 0;
	पूर्णांक actlen = -1;
	पूर्णांक ret = -ENOMEM;
	u32 *buffer;

	buffer = kzalloc(4096, GFP_KERNEL);
	अगर (buffer == शून्य)
		वापस -ENOMEM;
	स_नकल(&buffer[0], firmware, 4096);

	ret = usb_bulk_msg(dev->udev, usb_sndbulkpipe(dev->udev, 5),
			buffer, 4096, &actlen, 2000);

	अगर (ret)
		dev_err(dev->dev,
			"bulk message failed: %d (%d/%d)", ret,
			size, actlen);
	अन्यथा अणु
		errCode = actlen != size ? -1 : 0;
	पूर्ण
	kमुक्त(buffer);
	वापस errCode;
पूर्ण

/*****************************************************************
*                URB Streaming functions                         *
******************************************************************/

/*
 * IRQ callback, called by URB callback
 */
अटल व्योम cx231xx_isoc_irq_callback(काष्ठा urb *urb)
अणु
	काष्ठा cx231xx_dmaqueue *dma_q = urb->context;
	काष्ठा cx231xx_video_mode *vmode =
	    container_of(dma_q, काष्ठा cx231xx_video_mode, vidq);
	काष्ठा cx231xx *dev = container_of(vmode, काष्ठा cx231xx, video_mode);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	चयन (urb->status) अणु
	हाल 0:		/* success */
	हाल -ETIMEDOUT:	/* NAK */
		अवरोध;
	हाल -ECONNRESET:	/* समाप्त */
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		वापस;
	शेष:		/* error */
		cx231xx_isocdbg("urb completion error %d.\n", urb->status);
		अवरोध;
	पूर्ण

	/* Copy data from URB */
	spin_lock_irqsave(&dev->video_mode.slock, flags);
	dev->video_mode.isoc_ctl.isoc_copy(dev, urb);
	spin_unlock_irqrestore(&dev->video_mode.slock, flags);

	/* Reset urb buffers */
	क्रम (i = 0; i < urb->number_of_packets; i++) अणु
		urb->iso_frame_desc[i].status = 0;
		urb->iso_frame_desc[i].actual_length = 0;
	पूर्ण

	urb->status = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (urb->status) अणु
		cx231xx_isocdbg("urb resubmit failed (error=%i)\n",
				urb->status);
	पूर्ण
पूर्ण
/*****************************************************************
*                URB Streaming functions                         *
******************************************************************/

/*
 * IRQ callback, called by URB callback
 */
अटल व्योम cx231xx_bulk_irq_callback(काष्ठा urb *urb)
अणु
	काष्ठा cx231xx_dmaqueue *dma_q = urb->context;
	काष्ठा cx231xx_video_mode *vmode =
	    container_of(dma_q, काष्ठा cx231xx_video_mode, vidq);
	काष्ठा cx231xx *dev = container_of(vmode, काष्ठा cx231xx, video_mode);
	अचिन्हित दीर्घ flags;

	चयन (urb->status) अणु
	हाल 0:		/* success */
	हाल -ETIMEDOUT:	/* NAK */
		अवरोध;
	हाल -ECONNRESET:	/* समाप्त */
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		वापस;
	हाल -EPIPE:		/* stall */
		cx231xx_isocdbg("urb completion error - device is stalled.\n");
		वापस;
	शेष:		/* error */
		cx231xx_isocdbg("urb completion error %d.\n", urb->status);
		अवरोध;
	पूर्ण

	/* Copy data from URB */
	spin_lock_irqsave(&dev->video_mode.slock, flags);
	dev->video_mode.bulk_ctl.bulk_copy(dev, urb);
	spin_unlock_irqrestore(&dev->video_mode.slock, flags);

	/* Reset urb buffers */
	urb->status = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (urb->status) अणु
		cx231xx_isocdbg("urb resubmit failed (error=%i)\n",
				urb->status);
	पूर्ण
पूर्ण
/*
 * Stop and Deallocate URBs
 */
व्योम cx231xx_uninit_isoc(काष्ठा cx231xx *dev)
अणु
	काष्ठा cx231xx_dmaqueue *dma_q = &dev->video_mode.vidq;
	काष्ठा urb *urb;
	पूर्णांक i;
	bool broken_pipe = false;

	cx231xx_isocdbg("cx231xx: called cx231xx_uninit_isoc\n");

	dev->video_mode.isoc_ctl.nfields = -1;
	क्रम (i = 0; i < dev->video_mode.isoc_ctl.num_bufs; i++) अणु
		urb = dev->video_mode.isoc_ctl.urb[i];
		अगर (urb) अणु
			अगर (!irqs_disabled())
				usb_समाप्त_urb(urb);
			अन्यथा
				usb_unlink_urb(urb);

			अगर (dev->video_mode.isoc_ctl.transfer_buffer[i]) अणु
				usb_मुक्त_coherent(dev->udev,
						  urb->transfer_buffer_length,
						  dev->video_mode.isoc_ctl.
						  transfer_buffer[i],
						  urb->transfer_dma);
			पूर्ण
			अगर (urb->status == -EPIPE) अणु
				broken_pipe = true;
			पूर्ण
			usb_मुक्त_urb(urb);
			dev->video_mode.isoc_ctl.urb[i] = शून्य;
		पूर्ण
		dev->video_mode.isoc_ctl.transfer_buffer[i] = शून्य;
	पूर्ण

	अगर (broken_pipe) अणु
		cx231xx_isocdbg("Reset endpoint to recover broken pipe.");
		usb_reset_endpoपूर्णांक(dev->udev, dev->video_mode.end_poपूर्णांक_addr);
	पूर्ण
	kमुक्त(dev->video_mode.isoc_ctl.urb);
	kमुक्त(dev->video_mode.isoc_ctl.transfer_buffer);
	kमुक्त(dma_q->p_left_data);

	dev->video_mode.isoc_ctl.urb = शून्य;
	dev->video_mode.isoc_ctl.transfer_buffer = शून्य;
	dev->video_mode.isoc_ctl.num_bufs = 0;
	dma_q->p_left_data = शून्य;

	अगर (dev->mode_tv == 0)
		cx231xx_capture_start(dev, 0, Raw_Video);
	अन्यथा
		cx231xx_capture_start(dev, 0, TS1_serial_mode);


पूर्ण
EXPORT_SYMBOL_GPL(cx231xx_uninit_isoc);

/*
 * Stop and Deallocate URBs
 */
व्योम cx231xx_uninit_bulk(काष्ठा cx231xx *dev)
अणु
	काष्ठा cx231xx_dmaqueue *dma_q = &dev->video_mode.vidq;
	काष्ठा urb *urb;
	पूर्णांक i;
	bool broken_pipe = false;

	cx231xx_isocdbg("cx231xx: called cx231xx_uninit_bulk\n");

	dev->video_mode.bulk_ctl.nfields = -1;
	क्रम (i = 0; i < dev->video_mode.bulk_ctl.num_bufs; i++) अणु
		urb = dev->video_mode.bulk_ctl.urb[i];
		अगर (urb) अणु
			अगर (!irqs_disabled())
				usb_समाप्त_urb(urb);
			अन्यथा
				usb_unlink_urb(urb);

			अगर (dev->video_mode.bulk_ctl.transfer_buffer[i]) अणु
				usb_मुक्त_coherent(dev->udev,
						urb->transfer_buffer_length,
						dev->video_mode.bulk_ctl.
						transfer_buffer[i],
						urb->transfer_dma);
			पूर्ण
			अगर (urb->status == -EPIPE) अणु
				broken_pipe = true;
			पूर्ण
			usb_मुक्त_urb(urb);
			dev->video_mode.bulk_ctl.urb[i] = शून्य;
		पूर्ण
		dev->video_mode.bulk_ctl.transfer_buffer[i] = शून्य;
	पूर्ण

	अगर (broken_pipe) अणु
		cx231xx_isocdbg("Reset endpoint to recover broken pipe.");
		usb_reset_endpoपूर्णांक(dev->udev, dev->video_mode.end_poपूर्णांक_addr);
	पूर्ण
	kमुक्त(dev->video_mode.bulk_ctl.urb);
	kमुक्त(dev->video_mode.bulk_ctl.transfer_buffer);
	kमुक्त(dma_q->p_left_data);

	dev->video_mode.bulk_ctl.urb = शून्य;
	dev->video_mode.bulk_ctl.transfer_buffer = शून्य;
	dev->video_mode.bulk_ctl.num_bufs = 0;
	dma_q->p_left_data = शून्य;

	अगर (dev->mode_tv == 0)
		cx231xx_capture_start(dev, 0, Raw_Video);
	अन्यथा
		cx231xx_capture_start(dev, 0, TS1_serial_mode);


पूर्ण
EXPORT_SYMBOL_GPL(cx231xx_uninit_bulk);

/*
 * Allocate URBs and start IRQ
 */
पूर्णांक cx231xx_init_isoc(काष्ठा cx231xx *dev, पूर्णांक max_packets,
		      पूर्णांक num_bufs, पूर्णांक max_pkt_size,
		      पूर्णांक (*isoc_copy) (काष्ठा cx231xx *dev, काष्ठा urb *urb))
अणु
	काष्ठा cx231xx_dmaqueue *dma_q = &dev->video_mode.vidq;
	पूर्णांक i;
	पूर्णांक sb_size, pipe;
	काष्ठा urb *urb;
	पूर्णांक j, k;
	पूर्णांक rc;

	/* De-allocates all pending stuff */
	cx231xx_uninit_isoc(dev);

	dma_q->p_left_data = kzalloc(4096, GFP_KERNEL);
	अगर (dma_q->p_left_data == शून्य)
		वापस -ENOMEM;

	dev->video_mode.isoc_ctl.isoc_copy = isoc_copy;
	dev->video_mode.isoc_ctl.num_bufs = num_bufs;
	dma_q->pos = 0;
	dma_q->is_partial_line = 0;
	dma_q->last_sav = 0;
	dma_q->current_field = -1;
	dma_q->field1_करोne = 0;
	dma_q->lines_per_field = dev->height / 2;
	dma_q->bytes_left_in_line = dev->width << 1;
	dma_q->lines_completed = 0;
	dma_q->mpeg_buffer_करोne = 0;
	dma_q->left_data_count = 0;
	dma_q->mpeg_buffer_completed = 0;
	dma_q->add_ps_package_head = CX231XX_NEED_ADD_PS_PACKAGE_HEAD;
	dma_q->ps_head[0] = 0x00;
	dma_q->ps_head[1] = 0x00;
	dma_q->ps_head[2] = 0x01;
	dma_q->ps_head[3] = 0xBA;
	क्रम (i = 0; i < 8; i++)
		dma_q->partial_buf[i] = 0;

	dev->video_mode.isoc_ctl.urb =
	    kसुस्मृति(num_bufs, माप(व्योम *), GFP_KERNEL);
	अगर (!dev->video_mode.isoc_ctl.urb) अणु
		dev_err(dev->dev,
			"cannot alloc memory for usb buffers\n");
		वापस -ENOMEM;
	पूर्ण

	dev->video_mode.isoc_ctl.transfer_buffer =
	    kसुस्मृति(num_bufs, माप(व्योम *), GFP_KERNEL);
	अगर (!dev->video_mode.isoc_ctl.transfer_buffer) अणु
		dev_err(dev->dev,
			"cannot allocate memory for usbtransfer\n");
		kमुक्त(dev->video_mode.isoc_ctl.urb);
		वापस -ENOMEM;
	पूर्ण

	dev->video_mode.isoc_ctl.max_pkt_size = max_pkt_size;
	dev->video_mode.isoc_ctl.buf = शून्य;

	sb_size = max_packets * dev->video_mode.isoc_ctl.max_pkt_size;

	अगर (dev->mode_tv == 1)
		dev->video_mode.end_poपूर्णांक_addr = 0x81;
	अन्यथा
		dev->video_mode.end_poपूर्णांक_addr = 0x84;


	/* allocate urbs and transfer buffers */
	क्रम (i = 0; i < dev->video_mode.isoc_ctl.num_bufs; i++) अणु
		urb = usb_alloc_urb(max_packets, GFP_KERNEL);
		अगर (!urb) अणु
			cx231xx_uninit_isoc(dev);
			वापस -ENOMEM;
		पूर्ण
		dev->video_mode.isoc_ctl.urb[i] = urb;

		dev->video_mode.isoc_ctl.transfer_buffer[i] =
		    usb_alloc_coherent(dev->udev, sb_size, GFP_KERNEL,
				       &urb->transfer_dma);
		अगर (!dev->video_mode.isoc_ctl.transfer_buffer[i]) अणु
			dev_err(dev->dev,
				"unable to allocate %i bytes for transfer buffer %i\n",
				sb_size, i);
			cx231xx_uninit_isoc(dev);
			वापस -ENOMEM;
		पूर्ण
		स_रखो(dev->video_mode.isoc_ctl.transfer_buffer[i], 0, sb_size);

		pipe =
		    usb_rcvisocpipe(dev->udev, dev->video_mode.end_poपूर्णांक_addr);

		usb_fill_पूर्णांक_urb(urb, dev->udev, pipe,
				 dev->video_mode.isoc_ctl.transfer_buffer[i],
				 sb_size, cx231xx_isoc_irq_callback, dma_q, 1);

		urb->number_of_packets = max_packets;
		urb->transfer_flags = URB_ISO_ASAP | URB_NO_TRANSFER_DMA_MAP;

		k = 0;
		क्रम (j = 0; j < max_packets; j++) अणु
			urb->iso_frame_desc[j].offset = k;
			urb->iso_frame_desc[j].length =
			    dev->video_mode.isoc_ctl.max_pkt_size;
			k += dev->video_mode.isoc_ctl.max_pkt_size;
		पूर्ण
	पूर्ण

	init_रुकोqueue_head(&dma_q->wq);

	/* submit urbs and enables IRQ */
	क्रम (i = 0; i < dev->video_mode.isoc_ctl.num_bufs; i++) अणु
		rc = usb_submit_urb(dev->video_mode.isoc_ctl.urb[i],
				    GFP_ATOMIC);
		अगर (rc) अणु
			dev_err(dev->dev,
				"submit of urb %i failed (error=%i)\n", i,
				rc);
			cx231xx_uninit_isoc(dev);
			वापस rc;
		पूर्ण
	पूर्ण

	अगर (dev->mode_tv == 0)
		cx231xx_capture_start(dev, 1, Raw_Video);
	अन्यथा
		cx231xx_capture_start(dev, 1, TS1_serial_mode);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cx231xx_init_isoc);

/*
 * Allocate URBs and start IRQ
 */
पूर्णांक cx231xx_init_bulk(काष्ठा cx231xx *dev, पूर्णांक max_packets,
		      पूर्णांक num_bufs, पूर्णांक max_pkt_size,
		      पूर्णांक (*bulk_copy) (काष्ठा cx231xx *dev, काष्ठा urb *urb))
अणु
	काष्ठा cx231xx_dmaqueue *dma_q = &dev->video_mode.vidq;
	पूर्णांक i;
	पूर्णांक sb_size, pipe;
	काष्ठा urb *urb;
	पूर्णांक rc;

	dev->video_input = dev->video_input > 2 ? 2 : dev->video_input;

	cx231xx_coredbg("Setting Video mux to %d\n", dev->video_input);

	video_mux(dev, dev->video_input);

	/* De-allocates all pending stuff */
	cx231xx_uninit_bulk(dev);

	dev->video_mode.bulk_ctl.bulk_copy = bulk_copy;
	dev->video_mode.bulk_ctl.num_bufs = num_bufs;
	dma_q->pos = 0;
	dma_q->is_partial_line = 0;
	dma_q->last_sav = 0;
	dma_q->current_field = -1;
	dma_q->field1_करोne = 0;
	dma_q->lines_per_field = dev->height / 2;
	dma_q->bytes_left_in_line = dev->width << 1;
	dma_q->lines_completed = 0;
	dma_q->mpeg_buffer_करोne = 0;
	dma_q->left_data_count = 0;
	dma_q->mpeg_buffer_completed = 0;
	dma_q->ps_head[0] = 0x00;
	dma_q->ps_head[1] = 0x00;
	dma_q->ps_head[2] = 0x01;
	dma_q->ps_head[3] = 0xBA;
	क्रम (i = 0; i < 8; i++)
		dma_q->partial_buf[i] = 0;

	dev->video_mode.bulk_ctl.urb =
	    kसुस्मृति(num_bufs, माप(व्योम *), GFP_KERNEL);
	अगर (!dev->video_mode.bulk_ctl.urb) अणु
		dev_err(dev->dev,
			"cannot alloc memory for usb buffers\n");
		वापस -ENOMEM;
	पूर्ण

	dev->video_mode.bulk_ctl.transfer_buffer =
	    kसुस्मृति(num_bufs, माप(व्योम *), GFP_KERNEL);
	अगर (!dev->video_mode.bulk_ctl.transfer_buffer) अणु
		dev_err(dev->dev,
			"cannot allocate memory for usbtransfer\n");
		kमुक्त(dev->video_mode.bulk_ctl.urb);
		वापस -ENOMEM;
	पूर्ण

	dev->video_mode.bulk_ctl.max_pkt_size = max_pkt_size;
	dev->video_mode.bulk_ctl.buf = शून्य;

	sb_size = max_packets * dev->video_mode.bulk_ctl.max_pkt_size;

	अगर (dev->mode_tv == 1)
		dev->video_mode.end_poपूर्णांक_addr = 0x81;
	अन्यथा
		dev->video_mode.end_poपूर्णांक_addr = 0x84;


	/* allocate urbs and transfer buffers */
	क्रम (i = 0; i < dev->video_mode.bulk_ctl.num_bufs; i++) अणु
		urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!urb) अणु
			cx231xx_uninit_bulk(dev);
			वापस -ENOMEM;
		पूर्ण
		dev->video_mode.bulk_ctl.urb[i] = urb;
		urb->transfer_flags = URB_NO_TRANSFER_DMA_MAP;

		dev->video_mode.bulk_ctl.transfer_buffer[i] =
		    usb_alloc_coherent(dev->udev, sb_size, GFP_KERNEL,
				     &urb->transfer_dma);
		अगर (!dev->video_mode.bulk_ctl.transfer_buffer[i]) अणु
			dev_err(dev->dev,
				"unable to allocate %i bytes for transfer buffer %i\n",
				sb_size, i);
			cx231xx_uninit_bulk(dev);
			वापस -ENOMEM;
		पूर्ण
		स_रखो(dev->video_mode.bulk_ctl.transfer_buffer[i], 0, sb_size);

		pipe = usb_rcvbulkpipe(dev->udev,
				 dev->video_mode.end_poपूर्णांक_addr);
		usb_fill_bulk_urb(urb, dev->udev, pipe,
				  dev->video_mode.bulk_ctl.transfer_buffer[i],
				  sb_size, cx231xx_bulk_irq_callback, dma_q);
	पूर्ण

	/* clear halt */
	rc = usb_clear_halt(dev->udev, dev->video_mode.bulk_ctl.urb[0]->pipe);
	अगर (rc < 0) अणु
		dev_err(dev->dev,
			"failed to clear USB bulk endpoint stall/halt condition (error=%i)\n",
			rc);
		cx231xx_uninit_bulk(dev);
		वापस rc;
	पूर्ण

	init_रुकोqueue_head(&dma_q->wq);

	/* submit urbs and enables IRQ */
	क्रम (i = 0; i < dev->video_mode.bulk_ctl.num_bufs; i++) अणु
		rc = usb_submit_urb(dev->video_mode.bulk_ctl.urb[i],
				    GFP_ATOMIC);
		अगर (rc) अणु
			dev_err(dev->dev,
				"submit of urb %i failed (error=%i)\n", i, rc);
			cx231xx_uninit_bulk(dev);
			वापस rc;
		पूर्ण
	पूर्ण

	अगर (dev->mode_tv == 0)
		cx231xx_capture_start(dev, 1, Raw_Video);
	अन्यथा
		cx231xx_capture_start(dev, 1, TS1_serial_mode);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cx231xx_init_bulk);
व्योम cx231xx_stop_TS1(काष्ठा cx231xx *dev)
अणु
	u8 val[4] = अणु 0, 0, 0, 0 पूर्ण;

	val[0] = 0x00;
	val[1] = 0x03;
	val[2] = 0x00;
	val[3] = 0x00;
	cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER,
			TS_MODE_REG, val, 4);

	val[0] = 0x00;
	val[1] = 0x70;
	val[2] = 0x04;
	val[3] = 0x00;
	cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER,
			TS1_CFG_REG, val, 4);
पूर्ण
/* EXPORT_SYMBOL_GPL(cx231xx_stop_TS1); */
व्योम cx231xx_start_TS1(काष्ठा cx231xx *dev)
अणु
	u8 val[4] = अणु 0, 0, 0, 0 पूर्ण;

	val[0] = 0x03;
	val[1] = 0x03;
	val[2] = 0x00;
	val[3] = 0x00;
	cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER,
			TS_MODE_REG, val, 4);

	val[0] = 0x04;
	val[1] = 0xA3;
	val[2] = 0x3B;
	val[3] = 0x00;
	cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER,
			TS1_CFG_REG, val, 4);
पूर्ण
/* EXPORT_SYMBOL_GPL(cx231xx_start_TS1); */
/*****************************************************************
*             Device Init/UnInit functions                       *
******************************************************************/
पूर्णांक cx231xx_dev_init(काष्ठा cx231xx *dev)
अणु
	पूर्णांक errCode = 0;

	/* Initialize I2C bus */

	/* External Master 1 Bus */
	dev->i2c_bus[0].nr = 0;
	dev->i2c_bus[0].dev = dev;
	dev->i2c_bus[0].i2c_period = I2C_SPEED_100K;	/* 100 KHz */
	dev->i2c_bus[0].i2c_nostop = 0;
	dev->i2c_bus[0].i2c_reserve = 0;
	dev->i2c_bus[0].i2c_rc = -ENODEV;

	/* External Master 2 Bus */
	dev->i2c_bus[1].nr = 1;
	dev->i2c_bus[1].dev = dev;
	dev->i2c_bus[1].i2c_period = I2C_SPEED_100K;	/* 100 KHz */
	dev->i2c_bus[1].i2c_nostop = 0;
	dev->i2c_bus[1].i2c_reserve = 0;
	dev->i2c_bus[1].i2c_rc = -ENODEV;

	/* Internal Master 3 Bus */
	dev->i2c_bus[2].nr = 2;
	dev->i2c_bus[2].dev = dev;
	dev->i2c_bus[2].i2c_period = I2C_SPEED_100K;	/* 100kHz */
	dev->i2c_bus[2].i2c_nostop = 0;
	dev->i2c_bus[2].i2c_reserve = 0;
	dev->i2c_bus[2].i2c_rc = -ENODEV;

	/* रेजिस्टर I2C buses */
	errCode = cx231xx_i2c_रेजिस्टर(&dev->i2c_bus[0]);
	अगर (errCode < 0)
		वापस errCode;
	errCode = cx231xx_i2c_रेजिस्टर(&dev->i2c_bus[1]);
	अगर (errCode < 0)
		वापस errCode;
	errCode = cx231xx_i2c_रेजिस्टर(&dev->i2c_bus[2]);
	अगर (errCode < 0)
		वापस errCode;

	errCode = cx231xx_i2c_mux_create(dev);
	अगर (errCode < 0) अणु
		dev_err(dev->dev,
			"%s: Failed to create I2C mux\n", __func__);
		वापस errCode;
	पूर्ण
	errCode = cx231xx_i2c_mux_रेजिस्टर(dev, 0);
	अगर (errCode < 0)
		वापस errCode;

	errCode = cx231xx_i2c_mux_रेजिस्टर(dev, 1);
	अगर (errCode < 0)
		वापस errCode;

	/* scan the real bus segments in the order of physical port numbers */
	cx231xx_करो_i2c_scan(dev, I2C_0);
	cx231xx_करो_i2c_scan(dev, I2C_1_MUX_1);
	cx231xx_करो_i2c_scan(dev, I2C_2);
	cx231xx_करो_i2c_scan(dev, I2C_1_MUX_3);

	/* init hardware */
	/* Note : with out calling set घातer mode function,
	afe can not be set up correctly */
	अगर (dev->board.बाह्यal_av) अणु
		errCode = cx231xx_set_घातer_mode(dev,
				 POLARIS_AVMODE_ENXTERNAL_AV);
		अगर (errCode < 0) अणु
			dev_err(dev->dev,
				"%s: Failed to set Power - errCode [%d]!\n",
				__func__, errCode);
			वापस errCode;
		पूर्ण
	पूर्ण अन्यथा अणु
		errCode = cx231xx_set_घातer_mode(dev,
				 POLARIS_AVMODE_ANALOGT_TV);
		अगर (errCode < 0) अणु
			dev_err(dev->dev,
				"%s: Failed to set Power - errCode [%d]!\n",
				__func__, errCode);
			वापस errCode;
		पूर्ण
	पूर्ण

	/* reset the Tuner, अगर it is a Xceive tuner */
	अगर ((dev->board.tuner_type == TUNER_XC5000) ||
	    (dev->board.tuner_type == TUNER_XC2028))
			cx231xx_gpio_set(dev, dev->board.tuner_gpio);

	/* initialize Colibri block */
	errCode = cx231xx_afe_init_super_block(dev, 0x23c);
	अगर (errCode < 0) अणु
		dev_err(dev->dev,
			"%s: cx231xx_afe init super block - errCode [%d]!\n",
			__func__, errCode);
		वापस errCode;
	पूर्ण
	errCode = cx231xx_afe_init_channels(dev);
	अगर (errCode < 0) अणु
		dev_err(dev->dev,
			"%s: cx231xx_afe init channels - errCode [%d]!\n",
			__func__, errCode);
		वापस errCode;
	पूर्ण

	/* Set DIF in By pass mode */
	errCode = cx231xx_dअगर_set_standard(dev, DIF_USE_BASEBAND);
	अगर (errCode < 0) अणु
		dev_err(dev->dev,
			"%s: cx231xx_dif set to By pass mode - errCode [%d]!\n",
			__func__, errCode);
		वापस errCode;
	पूर्ण

	/* I2S block related functions */
	errCode = cx231xx_i2s_blk_initialize(dev);
	अगर (errCode < 0) अणु
		dev_err(dev->dev,
			"%s: cx231xx_i2s block initialize - errCode [%d]!\n",
			__func__, errCode);
		वापस errCode;
	पूर्ण

	/* init control pins */
	errCode = cx231xx_init_ctrl_pin_status(dev);
	अगर (errCode < 0) अणु
		dev_err(dev->dev,
			"%s: cx231xx_init ctrl pins - errCode [%d]!\n",
			__func__, errCode);
		वापस errCode;
	पूर्ण

	/* set AGC mode to Analog */
	चयन (dev->model) अणु
	हाल CX231XX_BOARD_CNXT_CARRAERA:
	हाल CX231XX_BOARD_CNXT_RDE_250:
	हाल CX231XX_BOARD_CNXT_SHELBY:
	हाल CX231XX_BOARD_CNXT_RDU_250:
	errCode = cx231xx_set_agc_analog_digital_mux_select(dev, 1);
		अवरोध;
	हाल CX231XX_BOARD_CNXT_RDE_253S:
	हाल CX231XX_BOARD_CNXT_RDU_253S:
	हाल CX231XX_BOARD_HAUPPAUGE_EXETER:
	हाल CX231XX_BOARD_HAUPPAUGE_930C_HD_1113xx:
	हाल CX231XX_BOARD_PV_PLAYTV_USB_HYBRID:
	हाल CX231XX_BOARD_HAUPPAUGE_USB2_FM_PAL:
	हाल CX231XX_BOARD_HAUPPAUGE_USB2_FM_NTSC:
	errCode = cx231xx_set_agc_analog_digital_mux_select(dev, 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (errCode < 0) अणु
		dev_err(dev->dev,
			"%s: cx231xx_AGC mode to Analog - errCode [%d]!\n",
			__func__, errCode);
		वापस errCode;
	पूर्ण

	/* set all alternate settings to zero initially */
	cx231xx_set_alt_setting(dev, INDEX_VIDEO, 0);
	cx231xx_set_alt_setting(dev, INDEX_VANC, 0);
	cx231xx_set_alt_setting(dev, INDEX_HANC, 0);
	अगर (dev->board.has_dvb)
		cx231xx_set_alt_setting(dev, INDEX_TS1, 0);

	errCode = 0;
	वापस errCode;
पूर्ण
EXPORT_SYMBOL_GPL(cx231xx_dev_init);

व्योम cx231xx_dev_uninit(काष्ठा cx231xx *dev)
अणु
	/* Un Initialize I2C bus */
	cx231xx_i2c_mux_unरेजिस्टर(dev);
	cx231xx_i2c_unरेजिस्टर(&dev->i2c_bus[2]);
	cx231xx_i2c_unरेजिस्टर(&dev->i2c_bus[1]);
	cx231xx_i2c_unरेजिस्टर(&dev->i2c_bus[0]);
पूर्ण
EXPORT_SYMBOL_GPL(cx231xx_dev_uninit);

/*****************************************************************
*              G P I O related functions                         *
******************************************************************/
पूर्णांक cx231xx_send_gpio_cmd(काष्ठा cx231xx *dev, u32 gpio_bit, u8 *gpio_val,
			  u8 len, u8 request, u8 direction)
अणु
	पूर्णांक status = 0;
	काष्ठा VENDOR_REQUEST_IN ven_req;

	/* Set wValue */
	ven_req.wValue = (u16) (gpio_bit >> 16 & 0xffff);

	/* set request */
	अगर (!request) अणु
		अगर (direction)
			ven_req.bRequest = VRT_GET_GPIO;	/* 0x9 gpio */
		अन्यथा
			ven_req.bRequest = VRT_SET_GPIO;	/* 0x8 gpio */
	पूर्ण अन्यथा अणु
		अगर (direction)
			ven_req.bRequest = VRT_GET_GPIE;	/* 0xb gpie */
		अन्यथा
			ven_req.bRequest = VRT_SET_GPIE;	/* 0xa gpie */
	पूर्ण

	/* set index value */
	ven_req.wIndex = (u16) (gpio_bit & 0xffff);

	/* set wLength value */
	ven_req.wLength = len;

	/* set bData value */
	ven_req.bData = 0;

	/* set the buffer क्रम पढ़ो / ग_लिखो */
	ven_req.pBuff = gpio_val;

	/* set the direction */
	अगर (direction) अणु
		ven_req.direction = USB_सूची_IN;
		स_रखो(ven_req.pBuff, 0x00, ven_req.wLength);
	पूर्ण अन्यथा
		ven_req.direction = USB_सूची_OUT;


	/* call common venकरोr command request */
	status = cx231xx_send_venकरोr_cmd(dev, &ven_req);
	अगर (status < 0) अणु
		dev_err(dev->dev, "%s: failed with status -%d\n",
			__func__, status);
	पूर्ण

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(cx231xx_send_gpio_cmd);

/*****************************************************************
 *    C O N T R O L - Register R E A D / W R I T E functions     *
 *****************************************************************/
पूर्णांक cx231xx_mode_रेजिस्टर(काष्ठा cx231xx *dev, u16 address, u32 mode)
अणु
	u8 value[4] = अणु 0x0, 0x0, 0x0, 0x0 पूर्ण;
	u32 पंचांगp = 0;
	पूर्णांक status = 0;

	status =
	    cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, address, value, 4);
	अगर (status < 0)
		वापस status;

	पंचांगp = le32_to_cpu(*((__le32 *) value));
	पंचांगp |= mode;

	value[0] = (u8) पंचांगp;
	value[1] = (u8) (पंचांगp >> 8);
	value[2] = (u8) (पंचांगp >> 16);
	value[3] = (u8) (पंचांगp >> 24);

	status =
	    cx231xx_ग_लिखो_ctrl_reg(dev, VRT_SET_REGISTER, address, value, 4);

	वापस status;
पूर्ण

/*****************************************************************
 *            I 2 C Internal C O N T R O L   functions           *
 *****************************************************************/
पूर्णांक cx231xx_पढ़ो_i2c_master(काष्ठा cx231xx *dev, u8 dev_addr, u16 saddr,
			  u8 saddr_len, u32 *data, u8 data_len, पूर्णांक master)
अणु
	पूर्णांक status = 0;
	काष्ठा cx231xx_i2c_xfer_data req_data;
	u8 value[64] = "0";

	अगर (saddr_len == 0)
		saddr = 0;
	अन्यथा अगर (saddr_len == 1)
		saddr &= 0xff;

	/* prepare xfer_data काष्ठा */
	req_data.dev_addr = dev_addr >> 1;
	req_data.direction = I2C_M_RD;
	req_data.saddr_len = saddr_len;
	req_data.saddr_dat = saddr;
	req_data.buf_size = data_len;
	req_data.p_buffer = (u8 *) value;

	/* usb send command */
	अगर (master == 0)
		status = dev->cx231xx_send_usb_command(&dev->i2c_bus[0],
					 &req_data);
	अन्यथा अगर (master == 1)
		status = dev->cx231xx_send_usb_command(&dev->i2c_bus[1],
					 &req_data);
	अन्यथा अगर (master == 2)
		status = dev->cx231xx_send_usb_command(&dev->i2c_bus[2],
					 &req_data);

	अगर (status >= 0) अणु
		/* Copy the data पढ़ो back to मुख्य buffer */
		अगर (data_len == 1)
			*data = value[0];
		अन्यथा अगर (data_len == 4)
			*data =
			    value[0] | value[1] << 8 | value[2] << 16 | value[3]
			    << 24;
		अन्यथा अगर (data_len > 4)
			*data = value[saddr];
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक cx231xx_ग_लिखो_i2c_master(काष्ठा cx231xx *dev, u8 dev_addr, u16 saddr,
			   u8 saddr_len, u32 data, u8 data_len, पूर्णांक master)
अणु
	पूर्णांक status = 0;
	u8 value[4] = अणु 0, 0, 0, 0 पूर्ण;
	काष्ठा cx231xx_i2c_xfer_data req_data;

	value[0] = (u8) data;
	value[1] = (u8) (data >> 8);
	value[2] = (u8) (data >> 16);
	value[3] = (u8) (data >> 24);

	अगर (saddr_len == 0)
		saddr = 0;
	अन्यथा अगर (saddr_len == 1)
		saddr &= 0xff;

	/* prepare xfer_data काष्ठा */
	req_data.dev_addr = dev_addr >> 1;
	req_data.direction = 0;
	req_data.saddr_len = saddr_len;
	req_data.saddr_dat = saddr;
	req_data.buf_size = data_len;
	req_data.p_buffer = value;

	/* usb send command */
	अगर (master == 0)
		status = dev->cx231xx_send_usb_command(&dev->i2c_bus[0],
				 &req_data);
	अन्यथा अगर (master == 1)
		status = dev->cx231xx_send_usb_command(&dev->i2c_bus[1],
				 &req_data);
	अन्यथा अगर (master == 2)
		status = dev->cx231xx_send_usb_command(&dev->i2c_bus[2],
				 &req_data);

	वापस status;
पूर्ण

पूर्णांक cx231xx_पढ़ो_i2c_data(काष्ठा cx231xx *dev, u8 dev_addr, u16 saddr,
			  u8 saddr_len, u32 *data, u8 data_len)
अणु
	पूर्णांक status = 0;
	काष्ठा cx231xx_i2c_xfer_data req_data;
	u8 value[4] = अणु 0, 0, 0, 0 पूर्ण;

	अगर (saddr_len == 0)
		saddr = 0;
	अन्यथा अगर (saddr_len == 1)
		saddr &= 0xff;

	/* prepare xfer_data काष्ठा */
	req_data.dev_addr = dev_addr >> 1;
	req_data.direction = I2C_M_RD;
	req_data.saddr_len = saddr_len;
	req_data.saddr_dat = saddr;
	req_data.buf_size = data_len;
	req_data.p_buffer = (u8 *) value;

	/* usb send command */
	status = dev->cx231xx_send_usb_command(&dev->i2c_bus[0], &req_data);

	अगर (status >= 0) अणु
		/* Copy the data पढ़ो back to मुख्य buffer */
		अगर (data_len == 1)
			*data = value[0];
		अन्यथा
			*data =
			    value[0] | value[1] << 8 | value[2] << 16 | value[3]
			    << 24;
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक cx231xx_ग_लिखो_i2c_data(काष्ठा cx231xx *dev, u8 dev_addr, u16 saddr,
			   u8 saddr_len, u32 data, u8 data_len)
अणु
	पूर्णांक status = 0;
	u8 value[4] = अणु 0, 0, 0, 0 पूर्ण;
	काष्ठा cx231xx_i2c_xfer_data req_data;

	value[0] = (u8) data;
	value[1] = (u8) (data >> 8);
	value[2] = (u8) (data >> 16);
	value[3] = (u8) (data >> 24);

	अगर (saddr_len == 0)
		saddr = 0;
	अन्यथा अगर (saddr_len == 1)
		saddr &= 0xff;

	/* prepare xfer_data काष्ठा */
	req_data.dev_addr = dev_addr >> 1;
	req_data.direction = 0;
	req_data.saddr_len = saddr_len;
	req_data.saddr_dat = saddr;
	req_data.buf_size = data_len;
	req_data.p_buffer = value;

	/* usb send command */
	status = dev->cx231xx_send_usb_command(&dev->i2c_bus[0], &req_data);

	वापस status;
पूर्ण

पूर्णांक cx231xx_reg_mask_ग_लिखो(काष्ठा cx231xx *dev, u8 dev_addr, u8 size,
			   u16 रेजिस्टर_address, u8 bit_start, u8 bit_end,
			   u32 value)
अणु
	पूर्णांक status = 0;
	u32 पंचांगp;
	u32 mask = 0;
	पूर्णांक i;

	अगर (bit_start > (size - 1) || bit_end > (size - 1))
		वापस -1;

	अगर (size == 8) अणु
		status =
		    cx231xx_पढ़ो_i2c_data(dev, dev_addr, रेजिस्टर_address, 2,
					  &पंचांगp, 1);
	पूर्ण अन्यथा अणु
		status =
		    cx231xx_पढ़ो_i2c_data(dev, dev_addr, रेजिस्टर_address, 2,
					  &पंचांगp, 4);
	पूर्ण

	अगर (status < 0)
		वापस status;

	mask = 1 << bit_end;
	क्रम (i = bit_end; i > bit_start && i > 0; i--)
		mask = mask + (1 << (i - 1));

	value <<= bit_start;

	अगर (size == 8) अणु
		पंचांगp &= ~mask;
		पंचांगp |= value;
		पंचांगp &= 0xff;
		status =
		    cx231xx_ग_लिखो_i2c_data(dev, dev_addr, रेजिस्टर_address, 2,
					   पंचांगp, 1);
	पूर्ण अन्यथा अणु
		पंचांगp &= ~mask;
		पंचांगp |= value;
		status =
		    cx231xx_ग_लिखो_i2c_data(dev, dev_addr, रेजिस्टर_address, 2,
					   पंचांगp, 4);
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(काष्ठा cx231xx *dev, u8 dev_addr,
					u16 saddr, u32 mask, u32 value)
अणु
	u32 temp;
	पूर्णांक status = 0;

	status = cx231xx_पढ़ो_i2c_data(dev, dev_addr, saddr, 2, &temp, 4);

	अगर (status < 0)
		वापस status;

	temp &= ~mask;
	temp |= value;

	status = cx231xx_ग_लिखो_i2c_data(dev, dev_addr, saddr, 2, temp, 4);

	वापस status;
पूर्ण

u32 cx231xx_set_field(u32 field_mask, u32 data)
अणु
	u32 temp;

	क्रम (temp = field_mask; (temp & 1) == 0; temp >>= 1)
		data <<= 1;

	वापस data;
पूर्ण
