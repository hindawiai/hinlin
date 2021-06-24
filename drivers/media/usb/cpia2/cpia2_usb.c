<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/****************************************************************************
 *
 *  Filename: cpia2_usb.c
 *
 *  Copyright 2001, STMicrolectronics, Inc.
 *      Contact:  steve.miller@st.com
 *
 *  Description:
 *     This is a USB driver क्रम CPia2 based video cameras.
 *     The infraकाष्ठाure of this driver is based on the cpia usb driver by
 *     Jochen Sअक्षरrlach and Johannes Erdfeldt.
 *
 *  Stripped of 2.4 stuff पढ़ोy क्रम मुख्य kernel submit by
 *		Alan Cox <alan@lxorguk.ukuu.org.uk>
 ****************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/module.h>

#समावेश "cpia2.h"

अटल पूर्णांक frame_sizes[] = अणु
	0,	// USBIF_CMDONLY
	0,	// USBIF_BULK
	128,	// USBIF_ISO_1
	384,	// USBIF_ISO_2
	640,	// USBIF_ISO_3
	768,	// USBIF_ISO_4
	896,	// USBIF_ISO_5
	1023,	// USBIF_ISO_6
पूर्ण;

#घोषणा FRAMES_PER_DESC    10
#घोषणा FRAME_SIZE_PER_DESC   frame_sizes[cam->cur_alt]

अटल व्योम process_frame(काष्ठा camera_data *cam);
अटल व्योम cpia2_usb_complete(काष्ठा urb *urb);
अटल पूर्णांक cpia2_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			   स्थिर काष्ठा usb_device_id *id);
अटल व्योम cpia2_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf);
अटल पूर्णांक cpia2_usb_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message);
अटल पूर्णांक cpia2_usb_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf);

अटल व्योम मुक्त_sbufs(काष्ठा camera_data *cam);
अटल व्योम add_APPn(काष्ठा camera_data *cam);
अटल व्योम add_COM(काष्ठा camera_data *cam);
अटल पूर्णांक submit_urbs(काष्ठा camera_data *cam);
अटल पूर्णांक set_alternate(काष्ठा camera_data *cam, अचिन्हित पूर्णांक alt);
अटल पूर्णांक configure_transfer_mode(काष्ठा camera_data *cam, अचिन्हित पूर्णांक alt);

अटल स्थिर काष्ठा usb_device_id cpia2_id_table[] = अणु
	अणुUSB_DEVICE(0x0553, 0x0100)पूर्ण,
	अणुUSB_DEVICE(0x0553, 0x0140)पूर्ण,
	अणुUSB_DEVICE(0x0553, 0x0151)पूर्ण,  /* STV0676 */
	अणुपूर्ण			/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, cpia2_id_table);

अटल काष्ठा usb_driver cpia2_driver = अणु
	.name		= "cpia2",
	.probe		= cpia2_usb_probe,
	.disconnect	= cpia2_usb_disconnect,
	.suspend	= cpia2_usb_suspend,
	.resume		= cpia2_usb_resume,
	.reset_resume	= cpia2_usb_resume,
	.id_table	= cpia2_id_table
पूर्ण;


/******************************************************************************
 *
 *  process_frame
 *
 *****************************************************************************/
अटल व्योम process_frame(काष्ठा camera_data *cam)
अणु
	अटल पूर्णांक frame_count;

	अचिन्हित अक्षर *inbuff = cam->workbuff->data;

	DBG("Processing frame #%d, current:%d\n",
	    cam->workbuff->num, cam->curbuff->num);

	अगर(cam->workbuff->length > cam->workbuff->max_length)
		cam->workbuff->max_length = cam->workbuff->length;

	अगर ((inbuff[0] == 0xFF) && (inbuff[1] == 0xD8)) अणु
		frame_count++;
	पूर्ण अन्यथा अणु
		cam->workbuff->status = FRAME_ERROR;
		DBG("Start of frame not found\n");
		वापस;
	पूर्ण

	/***
	 * Now the output buffer should have a JPEG image in it.
	 ***/
	अगर(!cam->first_image_seen) अणु
		/* Always skip the first image after streaming
		 * starts. It is almost certainly corrupt. */
		cam->first_image_seen = 1;
		cam->workbuff->status = FRAME_EMPTY;
		वापस;
	पूर्ण
	अगर (cam->workbuff->length > 3) अणु
		अगर(cam->mmapped &&
		   cam->workbuff->length < cam->workbuff->max_length) अणु
			/* No junk in the buffers */
			स_रखो(cam->workbuff->data+cam->workbuff->length,
			       0, cam->workbuff->max_length-
				  cam->workbuff->length);
		पूर्ण
		cam->workbuff->max_length = cam->workbuff->length;
		cam->workbuff->status = FRAME_READY;

		अगर(!cam->mmapped && cam->num_frames > 2) अणु
			/* During normal पढ़ोing, the most recent
			 * frame will be पढ़ो.  If the current frame
			 * hasn't started पढ़ोing yet, it will never
			 * be पढ़ो, so mark it empty.  If the buffer is
			 * mmapped, or we have few buffers, we need to
			 * रुको क्रम the user to मुक्त the buffer.
			 *
			 * NOTE: This is not entirely foolproof with 3
			 * buffers, but it would take an EXTREMELY
			 * overloaded प्रणाली to cause problems (possible
			 * image data corruption).  Basically, it would
			 * need to take more समय to execute cpia2_पढ़ो
			 * than it would क्रम the camera to send
			 * cam->num_frames-2 frames beक्रमe problems
			 * could occur.
			 */
			cam->curbuff->status = FRAME_EMPTY;
		पूर्ण
		cam->curbuff = cam->workbuff;
		cam->workbuff = cam->workbuff->next;
		DBG("Changed buffers, work:%d, current:%d\n",
		    cam->workbuff->num, cam->curbuff->num);
		वापस;
	पूर्ण अन्यथा अणु
		DBG("Not enough data for an image.\n");
	पूर्ण

	cam->workbuff->status = FRAME_ERROR;
	वापस;
पूर्ण

/******************************************************************************
 *
 *  add_APPn
 *
 *  Adds a user specअगरied APPn record
 *****************************************************************************/
अटल व्योम add_APPn(काष्ठा camera_data *cam)
अणु
	अगर(cam->APP_len > 0) अणु
		cam->workbuff->data[cam->workbuff->length++] = 0xFF;
		cam->workbuff->data[cam->workbuff->length++] = 0xE0+cam->APPn;
		cam->workbuff->data[cam->workbuff->length++] = 0;
		cam->workbuff->data[cam->workbuff->length++] = cam->APP_len+2;
		स_नकल(cam->workbuff->data+cam->workbuff->length,
		       cam->APP_data, cam->APP_len);
		cam->workbuff->length += cam->APP_len;
	पूर्ण
पूर्ण

/******************************************************************************
 *
 *  add_COM
 *
 *  Adds a user specअगरied COM record
 *****************************************************************************/
अटल व्योम add_COM(काष्ठा camera_data *cam)
अणु
	अगर(cam->COM_len > 0) अणु
		cam->workbuff->data[cam->workbuff->length++] = 0xFF;
		cam->workbuff->data[cam->workbuff->length++] = 0xFE;
		cam->workbuff->data[cam->workbuff->length++] = 0;
		cam->workbuff->data[cam->workbuff->length++] = cam->COM_len+2;
		स_नकल(cam->workbuff->data+cam->workbuff->length,
		       cam->COM_data, cam->COM_len);
		cam->workbuff->length += cam->COM_len;
	पूर्ण
पूर्ण

/******************************************************************************
 *
 *  cpia2_usb_complete
 *
 *  callback when incoming packet is received
 *****************************************************************************/
अटल व्योम cpia2_usb_complete(काष्ठा urb *urb)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर *cdata;
	अटल bool frame_पढ़ोy = false;
	काष्ठा camera_data *cam = (काष्ठा camera_data *) urb->context;

	अगर (urb->status!=0) अणु
		अगर (!(urb->status == -ENOENT ||
		      urb->status == -ECONNRESET ||
		      urb->status == -ESHUTDOWN))
		अणु
			DBG("urb->status = %d!\n", urb->status);
		पूर्ण
		DBG("Stopping streaming\n");
		वापस;
	पूर्ण

	अगर (!cam->streaming || !video_is_रेजिस्टरed(&cam->vdev)) अणु
		LOG("Will now stop the streaming: streaming = %d, present=%d\n",
		    cam->streaming, video_is_रेजिस्टरed(&cam->vdev));
		वापस;
	पूर्ण

	/***
	 * Packet collater
	 ***/
	//DBG("Collating %d packets\n", urb->number_of_packets);
	क्रम (i = 0; i < urb->number_of_packets; i++) अणु
		u16 checksum, iso_checksum;
		पूर्णांक j;
		पूर्णांक n = urb->iso_frame_desc[i].actual_length;
		पूर्णांक st = urb->iso_frame_desc[i].status;

		अगर(cam->workbuff->status == FRAME_READY) अणु
			काष्ठा framebuf *ptr;
			/* Try to find an available buffer */
			DBG("workbuff full, searching\n");
			क्रम (ptr = cam->workbuff->next;
			     ptr != cam->workbuff;
			     ptr = ptr->next)
			अणु
				अगर (ptr->status == FRAME_EMPTY) अणु
					ptr->status = FRAME_READING;
					ptr->length = 0;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (ptr == cam->workbuff)
				अवरोध; /* No READING or EMPTY buffers left */

			cam->workbuff = ptr;
		पूर्ण

		अगर (cam->workbuff->status == FRAME_EMPTY ||
		    cam->workbuff->status == FRAME_ERROR) अणु
			cam->workbuff->status = FRAME_READING;
			cam->workbuff->length = 0;
		पूर्ण

		//DBG("   Packet %d length = %d, status = %d\n", i, n, st);
		cdata = urb->transfer_buffer + urb->iso_frame_desc[i].offset;

		अगर (st) अणु
			LOG("cpia2 data error: [%d] len=%d, status = %d\n",
			    i, n, st);
			अगर(!ALLOW_CORRUPT)
				cam->workbuff->status = FRAME_ERROR;
			जारी;
		पूर्ण

		अगर(n<=2)
			जारी;

		checksum = 0;
		क्रम(j=0; j<n-2; ++j)
			checksum += cdata[j];
		iso_checksum = cdata[j] + cdata[j+1]*256;
		अगर(checksum != iso_checksum) अणु
			LOG("checksum mismatch: [%d] len=%d, calculated = %x, checksum = %x\n",
			    i, n, (पूर्णांक)checksum, (पूर्णांक)iso_checksum);
			अगर(!ALLOW_CORRUPT) अणु
				cam->workbuff->status = FRAME_ERROR;
				जारी;
			पूर्ण
		पूर्ण
		n -= 2;

		अगर(cam->workbuff->status != FRAME_READING) अणु
			अगर((0xFF == cdata[0] && 0xD8 == cdata[1]) ||
			   (0xD8 == cdata[0] && 0xFF == cdata[1] &&
			    0 != cdata[2])) अणु
				/* frame is skipped, but increment total
				 * frame count anyway */
				cam->frame_count++;
			पूर्ण
			DBG("workbuff not reading, status=%d\n",
			    cam->workbuff->status);
			जारी;
		पूर्ण

		अगर (cam->frame_size < cam->workbuff->length + n) अणु
			ERR("buffer overflow! length: %d, n: %d\n",
			    cam->workbuff->length, n);
			cam->workbuff->status = FRAME_ERROR;
			अगर(cam->workbuff->length > cam->workbuff->max_length)
				cam->workbuff->max_length =
					cam->workbuff->length;
			जारी;
		पूर्ण

		अगर (cam->workbuff->length == 0) अणु
			पूर्णांक data_offset;
			अगर ((0xD8 == cdata[0]) && (0xFF == cdata[1])) अणु
				data_offset = 1;
			पूर्ण अन्यथा अगर((0xFF == cdata[0]) && (0xD8 == cdata[1])
				  && (0xFF == cdata[2])) अणु
				data_offset = 2;
			पूर्ण अन्यथा अणु
				DBG("Ignoring packet, not beginning!\n");
				जारी;
			पूर्ण
			DBG("Start of frame pattern found\n");
			cam->workbuff->ts = kसमय_get_ns();
			cam->workbuff->seq = cam->frame_count++;
			cam->workbuff->data[0] = 0xFF;
			cam->workbuff->data[1] = 0xD8;
			cam->workbuff->length = 2;
			add_APPn(cam);
			add_COM(cam);
			स_नकल(cam->workbuff->data+cam->workbuff->length,
			       cdata+data_offset, n-data_offset);
			cam->workbuff->length += n-data_offset;
		पूर्ण अन्यथा अगर (cam->workbuff->length > 0) अणु
			स_नकल(cam->workbuff->data + cam->workbuff->length,
			       cdata, n);
			cam->workbuff->length += n;
		पूर्ण

		अगर ((cam->workbuff->length >= 3) &&
		    (cam->workbuff->data[cam->workbuff->length - 3] == 0xFF) &&
		    (cam->workbuff->data[cam->workbuff->length - 2] == 0xD9) &&
		    (cam->workbuff->data[cam->workbuff->length - 1] == 0xFF)) अणु
			frame_पढ़ोy = true;
			cam->workbuff->data[cam->workbuff->length - 1] = 0;
			cam->workbuff->length -= 1;
		पूर्ण अन्यथा अगर ((cam->workbuff->length >= 2) &&
		   (cam->workbuff->data[cam->workbuff->length - 2] == 0xFF) &&
		   (cam->workbuff->data[cam->workbuff->length - 1] == 0xD9)) अणु
			frame_पढ़ोy = true;
		पूर्ण

		अगर (frame_पढ़ोy) अणु
			DBG("Workbuff image size = %d\n",cam->workbuff->length);
			process_frame(cam);

			frame_पढ़ोy = false;

			अगर (रुकोqueue_active(&cam->wq_stream))
				wake_up_पूर्णांकerruptible(&cam->wq_stream);
		पूर्ण
	पूर्ण

	अगर(cam->streaming) अणु
		/* resubmit */
		urb->dev = cam->dev;
		अगर ((i = usb_submit_urb(urb, GFP_ATOMIC)) != 0)
			ERR("%s: usb_submit_urb ret %d!\n", __func__, i);
	पूर्ण
पूर्ण

/******************************************************************************
 *
 * configure_transfer_mode
 *
 *****************************************************************************/
अटल पूर्णांक configure_transfer_mode(काष्ठा camera_data *cam, अचिन्हित पूर्णांक alt)
अणु
	अटल अचिन्हित अक्षर iso_regs[8][4] = अणु
		अणु0x00, 0x00, 0x00, 0x00पूर्ण,
		अणु0x00, 0x00, 0x00, 0x00पूर्ण,
		अणु0xB9, 0x00, 0x00, 0x7Eपूर्ण,
		अणु0xB9, 0x00, 0x01, 0x7Eपूर्ण,
		अणु0xB9, 0x00, 0x02, 0x7Eपूर्ण,
		अणु0xB9, 0x00, 0x02, 0xFEपूर्ण,
		अणु0xB9, 0x00, 0x03, 0x7Eपूर्ण,
		अणु0xB9, 0x00, 0x03, 0xFDपूर्ण
	पूर्ण;
	काष्ठा cpia2_command cmd;
	अचिन्हित अक्षर reg;

	अगर (!video_is_रेजिस्टरed(&cam->vdev))
		वापस -ENODEV;

	/***
	 * Write the isoc रेजिस्टरs according to the alternate selected
	 ***/
	cmd.direction = TRANSFER_WRITE;
	cmd.buffer.block_data[0] = iso_regs[alt][0];
	cmd.buffer.block_data[1] = iso_regs[alt][1];
	cmd.buffer.block_data[2] = iso_regs[alt][2];
	cmd.buffer.block_data[3] = iso_regs[alt][3];
	cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VC;
	cmd.start = CPIA2_VC_USB_ISOLIM;
	cmd.reg_count = 4;
	cpia2_send_command(cam, &cmd);

	/***
	 * Enable relevant streams beक्रमe starting polling.
	 * First पढ़ो USB Stream Config Register.
	 ***/
	cmd.direction = TRANSFER_READ;
	cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VC;
	cmd.start = CPIA2_VC_USB_STRM;
	cmd.reg_count = 1;
	cpia2_send_command(cam, &cmd);
	reg = cmd.buffer.block_data[0];

	/* Clear iso, bulk, and पूर्णांक */
	reg &= ~(CPIA2_VC_USB_STRM_BLK_ENABLE |
		 CPIA2_VC_USB_STRM_ISO_ENABLE |
		 CPIA2_VC_USB_STRM_INT_ENABLE);

	अगर (alt == USBIF_BULK) अणु
		DBG("Enabling bulk xfer\n");
		reg |= CPIA2_VC_USB_STRM_BLK_ENABLE;	/* Enable Bulk */
		cam->xfer_mode = XFER_BULK;
	पूर्ण अन्यथा अगर (alt >= USBIF_ISO_1) अणु
		DBG("Enabling ISOC xfer\n");
		reg |= CPIA2_VC_USB_STRM_ISO_ENABLE;
		cam->xfer_mode = XFER_ISOC;
	पूर्ण

	cmd.buffer.block_data[0] = reg;
	cmd.direction = TRANSFER_WRITE;
	cmd.start = CPIA2_VC_USB_STRM;
	cmd.reg_count = 1;
	cmd.req_mode = CAMERAACCESS_TYPE_BLOCK | CAMERAACCESS_VC;
	cpia2_send_command(cam, &cmd);

	वापस 0;
पूर्ण

/******************************************************************************
 *
 * cpia2_usb_change_streaming_alternate
 *
 *****************************************************************************/
पूर्णांक cpia2_usb_change_streaming_alternate(काष्ठा camera_data *cam,
					 अचिन्हित पूर्णांक alt)
अणु
	पूर्णांक ret = 0;

	अगर(alt < USBIF_ISO_1 || alt > USBIF_ISO_6)
		वापस -EINVAL;

	अगर(alt == cam->params.camera_state.stream_mode)
		वापस 0;

	cpia2_usb_stream_छोड़ो(cam);

	configure_transfer_mode(cam, alt);

	cam->params.camera_state.stream_mode = alt;

	/* Reset the camera to prevent image quality degradation */
	cpia2_reset_camera(cam);

	cpia2_usb_stream_resume(cam);

	वापस ret;
पूर्ण

/******************************************************************************
 *
 * set_alternate
 *
 *****************************************************************************/
अटल पूर्णांक set_alternate(काष्ठा camera_data *cam, अचिन्हित पूर्णांक alt)
अणु
	पूर्णांक ret = 0;

	अगर(alt == cam->cur_alt)
		वापस 0;

	अगर (cam->cur_alt != USBIF_CMDONLY) अणु
		DBG("Changing from alt %d to %d\n", cam->cur_alt, USBIF_CMDONLY);
		ret = usb_set_पूर्णांकerface(cam->dev, cam->अगरace, USBIF_CMDONLY);
		अगर (ret != 0)
			वापस ret;
	पूर्ण
	अगर (alt != USBIF_CMDONLY) अणु
		DBG("Changing from alt %d to %d\n", USBIF_CMDONLY, alt);
		ret = usb_set_पूर्णांकerface(cam->dev, cam->अगरace, alt);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	cam->old_alt = cam->cur_alt;
	cam->cur_alt = alt;

	वापस ret;
पूर्ण

/******************************************************************************
 *
 * मुक्त_sbufs
 *
 * Free all cam->sbuf[]. All non-शून्य .data and .urb members that are non-शून्य
 * are assumed to be allocated. Non-शून्य .urb members are also assumed to be
 * submitted (and must thereक्रमe be समाप्तed beक्रमe they are मुक्तd).
 *****************************************************************************/
अटल व्योम मुक्त_sbufs(काष्ठा camera_data *cam)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_SBUF; i++) अणु
		अगर(cam->sbuf[i].urb) अणु
			usb_समाप्त_urb(cam->sbuf[i].urb);
			usb_मुक्त_urb(cam->sbuf[i].urb);
			cam->sbuf[i].urb = शून्य;
		पूर्ण
		अगर(cam->sbuf[i].data) अणु
			kमुक्त(cam->sbuf[i].data);
			cam->sbuf[i].data = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/*******
* Convenience functions
*******/
/****************************************************************************
 *
 *  ग_लिखो_packet
 *
 ***************************************************************************/
अटल पूर्णांक ग_लिखो_packet(काष्ठा usb_device *udev,
			u8 request, u8 * रेजिस्टरs, u16 start, माप_प्रकार size)
अणु
	अचिन्हित अक्षर *buf;
	पूर्णांक ret;

	अगर (!रेजिस्टरs || size <= 0)
		वापस -EINVAL;

	buf = kmemdup(रेजिस्टरs, size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = usb_control_msg(udev,
			       usb_sndctrlpipe(udev, 0),
			       request,
			       USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			       start,	/* value */
			       0,	/* index */
			       buf,	/* buffer */
			       size,
			       HZ);

	kमुक्त(buf);
	वापस ret;
पूर्ण

/****************************************************************************
 *
 *  पढ़ो_packet
 *
 ***************************************************************************/
अटल पूर्णांक पढ़ो_packet(काष्ठा usb_device *udev,
		       u8 request, u8 * रेजिस्टरs, u16 start, माप_प्रकार size)
अणु
	अचिन्हित अक्षर *buf;
	पूर्णांक ret;

	अगर (!रेजिस्टरs || size <= 0)
		वापस -EINVAL;

	buf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = usb_control_msg(udev,
			       usb_rcvctrlpipe(udev, 0),
			       request,
			       USB_सूची_IN|USB_TYPE_VENDOR|USB_RECIP_DEVICE,
			       start,	/* value */
			       0,	/* index */
			       buf,	/* buffer */
			       size,
			       HZ);

	अगर (ret >= 0)
		स_नकल(रेजिस्टरs, buf, size);

	kमुक्त(buf);

	वापस ret;
पूर्ण

/******************************************************************************
 *
 *  cpia2_usb_transfer_cmd
 *
 *****************************************************************************/
पूर्णांक cpia2_usb_transfer_cmd(काष्ठा camera_data *cam,
			   व्योम *रेजिस्टरs,
			   u8 request, u8 start, u8 count, u8 direction)
अणु
	पूर्णांक err = 0;
	काष्ठा usb_device *udev = cam->dev;

	अगर (!udev) अणु
		ERR("%s: Internal driver error: udev is NULL\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (!रेजिस्टरs) अणु
		ERR("%s: Internal driver error: register array is NULL\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (direction == TRANSFER_READ) अणु
		err = पढ़ो_packet(udev, request, (u8 *)रेजिस्टरs, start, count);
		अगर (err > 0)
			err = 0;
	पूर्ण अन्यथा अगर (direction == TRANSFER_WRITE) अणु
		err =ग_लिखो_packet(udev, request, (u8 *)रेजिस्टरs, start, count);
		अगर (err < 0) अणु
			LOG("Control message failed, err val = %d\n", err);
			LOG("Message: request = 0x%0X, start = 0x%0X\n",
			    request, start);
			LOG("Message: count = %d, register[0] = 0x%0X\n",
			    count, ((अचिन्हित अक्षर *) रेजिस्टरs)[0]);
		पूर्ण अन्यथा
			err=0;
	पूर्ण अन्यथा अणु
		LOG("Unexpected first byte of direction: %d\n",
		       direction);
		वापस -EINVAL;
	पूर्ण

	अगर(err != 0)
		LOG("Unexpected error: %d\n", err);
	वापस err;
पूर्ण


/******************************************************************************
 *
 *  submit_urbs
 *
 *****************************************************************************/
अटल पूर्णांक submit_urbs(काष्ठा camera_data *cam)
अणु
	काष्ठा urb *urb;
	पूर्णांक fx, err, i, j;

	क्रम(i=0; i<NUM_SBUF; ++i) अणु
		अगर (cam->sbuf[i].data)
			जारी;
		cam->sbuf[i].data =
		    kदो_स्मृति_array(FRAME_SIZE_PER_DESC, FRAMES_PER_DESC,
				  GFP_KERNEL);
		अगर (!cam->sbuf[i].data) अणु
			जबतक (--i >= 0) अणु
				kमुक्त(cam->sbuf[i].data);
				cam->sbuf[i].data = शून्य;
			पूर्ण
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	/* We द्विगुन buffer the Isoc lists, and also know the polling
	 * पूर्णांकerval is every frame (1 == (1 << (bInterval -1))).
	 */
	क्रम(i=0; i<NUM_SBUF; ++i) अणु
		अगर(cam->sbuf[i].urb) अणु
			जारी;
		पूर्ण
		urb = usb_alloc_urb(FRAMES_PER_DESC, GFP_KERNEL);
		अगर (!urb) अणु
			क्रम (j = 0; j < i; j++)
				usb_मुक्त_urb(cam->sbuf[j].urb);
			क्रम (j = 0; j < NUM_SBUF; j++) अणु
				kमुक्त(cam->sbuf[j].data);
				cam->sbuf[j].data = शून्य;
			पूर्ण
			वापस -ENOMEM;
		पूर्ण

		cam->sbuf[i].urb = urb;
		urb->dev = cam->dev;
		urb->context = cam;
		urb->pipe = usb_rcvisocpipe(cam->dev, 1 /*ISOC endpoपूर्णांक*/);
		urb->transfer_flags = URB_ISO_ASAP;
		urb->transfer_buffer = cam->sbuf[i].data;
		urb->complete = cpia2_usb_complete;
		urb->number_of_packets = FRAMES_PER_DESC;
		urb->पूर्णांकerval = 1;
		urb->transfer_buffer_length =
			FRAME_SIZE_PER_DESC * FRAMES_PER_DESC;

		क्रम (fx = 0; fx < FRAMES_PER_DESC; fx++) अणु
			urb->iso_frame_desc[fx].offset =
				FRAME_SIZE_PER_DESC * fx;
			urb->iso_frame_desc[fx].length = FRAME_SIZE_PER_DESC;
		पूर्ण
	पूर्ण


	/* Queue the ISO urbs, and resubmit in the completion handler */
	क्रम(i=0; i<NUM_SBUF; ++i) अणु
		err = usb_submit_urb(cam->sbuf[i].urb, GFP_KERNEL);
		अगर (err) अणु
			ERR("usb_submit_urb[%d]() = %d\n", i, err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/******************************************************************************
 *
 *  cpia2_usb_stream_start
 *
 *****************************************************************************/
पूर्णांक cpia2_usb_stream_start(काष्ठा camera_data *cam, अचिन्हित पूर्णांक alternate)
अणु
	पूर्णांक ret;
	पूर्णांक old_alt;

	अगर(cam->streaming)
		वापस 0;

	अगर (cam->flush) अणु
		पूर्णांक i;
		DBG("Flushing buffers\n");
		क्रम(i=0; i<cam->num_frames; ++i) अणु
			cam->buffers[i].status = FRAME_EMPTY;
			cam->buffers[i].length = 0;
		पूर्ण
		cam->curbuff = &cam->buffers[0];
		cam->workbuff = cam->curbuff->next;
		cam->flush = false;
	पूर्ण

	old_alt = cam->params.camera_state.stream_mode;
	cam->params.camera_state.stream_mode = 0;
	ret = cpia2_usb_change_streaming_alternate(cam, alternate);
	अगर (ret < 0) अणु
		पूर्णांक ret2;
		ERR("cpia2_usb_change_streaming_alternate() = %d!\n", ret);
		cam->params.camera_state.stream_mode = old_alt;
		ret2 = set_alternate(cam, USBIF_CMDONLY);
		अगर (ret2 < 0) अणु
			ERR("cpia2_usb_change_streaming_alternate(%d) =%d has already failed. Then tried to call set_alternate(USBIF_CMDONLY) = %d.\n",
			    alternate, ret, ret2);
		पूर्ण
	पूर्ण अन्यथा अणु
		cam->frame_count = 0;
		cam->streaming = 1;
		ret = cpia2_usb_stream_resume(cam);
	पूर्ण
	वापस ret;
पूर्ण

/******************************************************************************
 *
 *  cpia2_usb_stream_छोड़ो
 *
 *****************************************************************************/
पूर्णांक cpia2_usb_stream_छोड़ो(काष्ठा camera_data *cam)
अणु
	पूर्णांक ret = 0;
	अगर(cam->streaming) अणु
		मुक्त_sbufs(cam);
		ret = set_alternate(cam, USBIF_CMDONLY);
	पूर्ण
	वापस ret;
पूर्ण

/******************************************************************************
 *
 *  cpia2_usb_stream_resume
 *
 *****************************************************************************/
पूर्णांक cpia2_usb_stream_resume(काष्ठा camera_data *cam)
अणु
	पूर्णांक ret = 0;
	अगर(cam->streaming) अणु
		cam->first_image_seen = 0;
		ret = set_alternate(cam, cam->params.camera_state.stream_mode);
		अगर(ret == 0) अणु
			/* क्रम some reason the user effects need to be set
			   again when starting streaming. */
			cpia2_करो_command(cam, CPIA2_CMD_SET_USER_EFFECTS, TRANSFER_WRITE,
					cam->params.vp_params.user_effects);
			ret = submit_urbs(cam);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/******************************************************************************
 *
 *  cpia2_usb_stream_stop
 *
 *****************************************************************************/
पूर्णांक cpia2_usb_stream_stop(काष्ठा camera_data *cam)
अणु
	पूर्णांक ret;

	ret = cpia2_usb_stream_छोड़ो(cam);
	cam->streaming = 0;
	configure_transfer_mode(cam, 0);
	वापस ret;
पूर्ण

/******************************************************************************
 *
 *  cpia2_usb_probe
 *
 *  Probe and initialize.
 *****************************************************************************/
अटल पूर्णांक cpia2_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			   स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_पूर्णांकerface_descriptor *पूर्णांकerface;
	काष्ठा camera_data *cam;
	पूर्णांक ret;

	/* A multi-config CPiA2 camera? */
	अगर (udev->descriptor.bNumConfigurations != 1)
		वापस -ENODEV;
	पूर्णांकerface = &पूर्णांकf->cur_altsetting->desc;

	/* If we get to this poपूर्णांक, we found a CPiA2 camera */
	LOG("CPiA2 USB camera found\n");

	cam = cpia2_init_camera_काष्ठा(पूर्णांकf);
	अगर (cam == शून्य)
		वापस -ENOMEM;

	cam->dev = udev;
	cam->अगरace = पूर्णांकerface->bInterfaceNumber;

	ret = set_alternate(cam, USBIF_CMDONLY);
	अगर (ret < 0) अणु
		ERR("%s: usb_set_interface error (ret = %d)\n", __func__, ret);
		kमुक्त(cam);
		वापस ret;
	पूर्ण


	अगर((ret = cpia2_init_camera(cam)) < 0) अणु
		ERR("%s: failed to initialize cpia2 camera (ret = %d)\n", __func__, ret);
		kमुक्त(cam);
		वापस ret;
	पूर्ण
	LOG("  CPiA Version: %d.%02d (%d.%d)\n",
	       cam->params.version.firmware_revision_hi,
	       cam->params.version.firmware_revision_lo,
	       cam->params.version.asic_id,
	       cam->params.version.asic_rev);
	LOG("  CPiA PnP-ID: %04x:%04x:%04x\n",
	       cam->params.pnp_id.venकरोr,
	       cam->params.pnp_id.product,
	       cam->params.pnp_id.device_revision);
	LOG("  SensorID: %d.(version %d)\n",
	       cam->params.version.sensor_flags,
	       cam->params.version.sensor_rev);

	usb_set_पूर्णांकfdata(पूर्णांकf, cam);

	ret = cpia2_रेजिस्टर_camera(cam);
	अगर (ret < 0) अणु
		ERR("%s: Failed to register cpia2 camera (ret = %d)\n", __func__, ret);
		kमुक्त(cam);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/******************************************************************************
 *
 *  cpia2_disconnect
 *
 *****************************************************************************/
अटल व्योम cpia2_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा camera_data *cam = usb_get_पूर्णांकfdata(पूर्णांकf);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	DBG("Stopping stream\n");
	cpia2_usb_stream_stop(cam);

	mutex_lock(&cam->v4l2_lock);
	DBG("Unregistering camera\n");
	cpia2_unरेजिस्टर_camera(cam);
	v4l2_device_disconnect(&cam->v4l2_dev);
	mutex_unlock(&cam->v4l2_lock);

	अगर(cam->buffers) अणु
		DBG("Wakeup waiting processes\n");
		cam->curbuff->status = FRAME_READY;
		cam->curbuff->length = 0;
		wake_up_पूर्णांकerruptible(&cam->wq_stream);
	पूर्ण

	v4l2_device_put(&cam->v4l2_dev);

	LOG("CPiA2 camera disconnected.\n");
पूर्ण

अटल पूर्णांक cpia2_usb_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा camera_data *cam = usb_get_पूर्णांकfdata(पूर्णांकf);

	mutex_lock(&cam->v4l2_lock);
	अगर (cam->streaming) अणु
		cpia2_usb_stream_stop(cam);
		cam->streaming = 1;
	पूर्ण
	mutex_unlock(&cam->v4l2_lock);

	dev_info(&पूर्णांकf->dev, "going into suspend..\n");
	वापस 0;
पूर्ण

/* Resume device - start device. */
अटल पूर्णांक cpia2_usb_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा camera_data *cam = usb_get_पूर्णांकfdata(पूर्णांकf);

	mutex_lock(&cam->v4l2_lock);
	v4l2_ctrl_handler_setup(&cam->hdl);
	अगर (cam->streaming) अणु
		cam->streaming = 0;
		cpia2_usb_stream_start(cam,
				cam->params.camera_state.stream_mode);
	पूर्ण
	mutex_unlock(&cam->v4l2_lock);

	dev_info(&पूर्णांकf->dev, "coming out of suspend..\n");
	वापस 0;
पूर्ण

/******************************************************************************
 *
 *  usb_cpia2_init
 *
 *****************************************************************************/
पूर्णांक cpia2_usb_init(व्योम)
अणु
	वापस usb_रेजिस्टर(&cpia2_driver);
पूर्ण

/******************************************************************************
 *
 *  usb_cpia_cleanup
 *
 *****************************************************************************/
व्योम cpia2_usb_cleanup(व्योम)
अणु
	schedule_समयout(2 * HZ);
	usb_deरेजिस्टर(&cpia2_driver);
पूर्ण
