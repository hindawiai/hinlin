<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Linux driver क्रम Philips webcam
   USB and Video4Linux पूर्णांकerface part.
   (C) 1999-2004 Nemosoft Unv.
   (C) 2004-2006 Luc Saillard (luc@saillard.org)
   (C) 2011 Hans de Goede <hdegoede@redhat.com>

   NOTE: this version of pwc is an unofficial (modअगरied) release of pwc & pcwx
   driver and thus may have bugs that are not present in the original version.
   Please send bug reports and support requests to <luc@saillard.org>.
   The decompression routines have been implemented by reverse-engineering the
   Nemosoft binary pwcx module. Caveat emptor.


*/

/*
   This code क्रमms the पूर्णांकerface between the USB layers and the Philips
   specअगरic stuff. Some adanved stuff of the driver falls under an
   NDA, चिन्हित between me and Philips B.V., Eindhoven, the Netherlands, and
   is thus not distributed in source क्रमm. The binary pwcx.o module
   contains the code that falls under the NDA.

   In हाल you're wondering: 'pwc' stands क्रम "Philips WebCam", but
   I really didn't want to type 'philips_web_cam' every time (I'm lazy as
   any Linux kernel hacker, but I करोn't like uncomprehensible abbreviations
   without explanation).

   Oh yes, convention: to disctinguish between all the various poपूर्णांकers to
   device-काष्ठाures, I use these names क्रम the poपूर्णांकer variables:
   udev: काष्ठा usb_device *
   vdev: काष्ठा video_device (member of pwc_dev)
   pdev: काष्ठा pwc_devive *
*/

/* Contributors:
   - Alvaraकरो: adding whitebalance code
   - Alistar Moire: QuickCam 3000 Pro device/product ID
   - Tony Hoyle: Creative Lअसल Webcam 5 device/product ID
   - Mark Burazin: solving hang in VIDIOCSYNC when camera माला_लो unplugged
   - Jk Fang: Sotec Afina Eye ID
   - Xavier Roche: QuickCam Pro 4000 ID
   - Jens Knudsen: QuickCam Zoom ID
   - J. Debert: QuickCam क्रम Notebooks ID
   - Pham Thanh Nam: webcam snapshot button as an event input device
*/

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#अगर_घोषित CONFIG_USB_PWC_INPUT_EVDEV
#समावेश <linux/usb/input.h>
#पूर्ण_अगर
#समावेश <linux/vदो_स्मृति.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/kernel.h>		/* simple_म_से_दीर्घ() */

#समावेश "pwc.h"
#समावेश "pwc-kiara.h"
#समावेश "pwc-timon.h"
#समावेश "pwc-dec23.h"
#समावेश "pwc-dec1.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/pwc.h>

/* Function prototypes and driver ढाँचाs */

/* hotplug device table support */
अटल स्थिर काष्ठा usb_device_id pwc_device_table [] = अणु
	अणु USB_DEVICE(0x041E, 0x400C) पूर्ण, /* Creative Webcam 5 */
	अणु USB_DEVICE(0x041E, 0x4011) पूर्ण, /* Creative Webcam Pro Ex */

	अणु USB_DEVICE(0x046D, 0x08B0) पूर्ण, /* Logitech QuickCam 3000 Pro */
	अणु USB_DEVICE(0x046D, 0x08B1) पूर्ण, /* Logitech QuickCam Notebook Pro */
	अणु USB_DEVICE(0x046D, 0x08B2) पूर्ण, /* Logitech QuickCam 4000 Pro */
	अणु USB_DEVICE(0x046D, 0x08B3) पूर्ण, /* Logitech QuickCam Zoom (old model) */
	अणु USB_DEVICE(0x046D, 0x08B4) पूर्ण, /* Logitech QuickCam Zoom (new model) */
	अणु USB_DEVICE(0x046D, 0x08B5) पूर्ण, /* Logitech QuickCam Orbit/Sphere */
	अणु USB_DEVICE(0x046D, 0x08B6) पूर्ण, /* Logitech/Cisco VT Camera */
	अणु USB_DEVICE(0x046D, 0x08B7) पूर्ण, /* Logitech ViewPort AV 100 */
	अणु USB_DEVICE(0x046D, 0x08B8) पूर्ण, /* Logitech QuickCam */

	अणु USB_DEVICE(0x0471, 0x0302) पूर्ण, /* Philips PCA645VC */
	अणु USB_DEVICE(0x0471, 0x0303) पूर्ण, /* Philips PCA646VC */
	अणु USB_DEVICE(0x0471, 0x0304) पूर्ण, /* Askey VC010 type 2 */
	अणु USB_DEVICE(0x0471, 0x0307) पूर्ण, /* Philips PCVC675K (Vesta) */
	अणु USB_DEVICE(0x0471, 0x0308) पूर्ण, /* Philips PCVC680K (Vesta Pro) */
	अणु USB_DEVICE(0x0471, 0x030C) पूर्ण, /* Philips PCVC690K (Vesta Pro Scan) */
	अणु USB_DEVICE(0x0471, 0x0310) पूर्ण, /* Philips PCVC730K (ToUCam Fun)/PCVC830 (ToUCam II) */
	अणु USB_DEVICE(0x0471, 0x0311) पूर्ण, /* Philips PCVC740K (ToUCam Pro)/PCVC840 (ToUCam II) */
	अणु USB_DEVICE(0x0471, 0x0312) पूर्ण, /* Philips PCVC750K (ToUCam Pro Scan) */
	अणु USB_DEVICE(0x0471, 0x0313) पूर्ण, /* Philips PCVC720K/40 (ToUCam XS) */
	अणु USB_DEVICE(0x0471, 0x0329) पूर्ण, /* Philips SPC 900NC webcam */
	अणु USB_DEVICE(0x0471, 0x032C) पूर्ण, /* Philips SPC 880NC webcam */

	अणु USB_DEVICE(0x04CC, 0x8116) पूर्ण, /* Sotec Afina Eye */

	अणु USB_DEVICE(0x055D, 0x9000) पूर्ण, /* Samsung MPC-C10 */
	अणु USB_DEVICE(0x055D, 0x9001) पूर्ण, /* Samsung MPC-C30 */
	अणु USB_DEVICE(0x055D, 0x9002) पूर्ण,	/* Samsung SNC-35E (Ver3.0) */

	अणु USB_DEVICE(0x069A, 0x0001) पूर्ण, /* Askey VC010 type 1 */

	अणु USB_DEVICE(0x06BE, 0x8116) पूर्ण, /* AME Co. Afina Eye */

	अणु USB_DEVICE(0x0d81, 0x1900) पूर्ण, /* Visionite VCS-UC300 */
	अणु USB_DEVICE(0x0d81, 0x1910) पूर्ण, /* Visionite VCS-UM100 */

	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, pwc_device_table);

अटल पूर्णांक usb_pwc_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id);
अटल व्योम usb_pwc_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf);
अटल व्योम pwc_isoc_cleanup(काष्ठा pwc_device *pdev);

अटल काष्ठा usb_driver pwc_driver = अणु
	.name =			"Philips webcam",	/* name */
	.id_table =		pwc_device_table,
	.probe =		usb_pwc_probe,		/* probe() */
	.disconnect =		usb_pwc_disconnect,	/* disconnect() */
पूर्ण;

#घोषणा MAX_DEV_HINTS	20
#घोषणा MAX_ISOC_ERRORS	20

#अगर_घोषित CONFIG_USB_PWC_DEBUG
	पूर्णांक pwc_trace = PWC_DEBUG_LEVEL;
#पूर्ण_अगर
अटल पूर्णांक घातer_save = -1;
अटल पूर्णांक leds[2] = अणु 100, 0 पूर्ण;

/***/

अटल स्थिर काष्ठा v4l2_file_operations pwc_fops = अणु
	.owner =	THIS_MODULE,
	.खोलो =		v4l2_fh_खोलो,
	.release =	vb2_fop_release,
	.पढ़ो =		vb2_fop_पढ़ो,
	.poll =		vb2_fop_poll,
	.mmap =		vb2_fop_mmap,
	.unlocked_ioctl = video_ioctl2,
पूर्ण;
अटल स्थिर काष्ठा video_device pwc_ढाँचा = अणु
	.name =		"Philips Webcam",	/* Filled in later */
	.release =	video_device_release_empty,
	.fops =         &pwc_fops,
	.ioctl_ops =	&pwc_ioctl_ops,
पूर्ण;

/***************************************************************************/
/* Private functions */

अटल व्योम *pwc_alloc_urb_buffer(काष्ठा usb_device *dev,
				  माप_प्रकार size, dma_addr_t *dma_handle)
अणु
	काष्ठा device *dmadev = dev->bus->sysdev;
	व्योम *buffer = kदो_स्मृति(size, GFP_KERNEL);

	अगर (!buffer)
		वापस शून्य;

	*dma_handle = dma_map_single(dmadev, buffer, size, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(dmadev, *dma_handle)) अणु
		kमुक्त(buffer);
		वापस शून्य;
	पूर्ण

	वापस buffer;
पूर्ण

अटल व्योम pwc_मुक्त_urb_buffer(काष्ठा usb_device *dev,
				माप_प्रकार size,
				व्योम *buffer,
				dma_addr_t dma_handle)
अणु
	काष्ठा device *dmadev = dev->bus->sysdev;

	dma_unmap_single(dmadev, dma_handle, size, DMA_FROM_DEVICE);
	kमुक्त(buffer);
पूर्ण

अटल काष्ठा pwc_frame_buf *pwc_get_next_fill_buf(काष्ठा pwc_device *pdev)
अणु
	अचिन्हित दीर्घ flags = 0;
	काष्ठा pwc_frame_buf *buf = शून्य;

	spin_lock_irqsave(&pdev->queued_bufs_lock, flags);
	अगर (list_empty(&pdev->queued_bufs))
		जाओ leave;

	buf = list_entry(pdev->queued_bufs.next, काष्ठा pwc_frame_buf, list);
	list_del(&buf->list);
leave:
	spin_unlock_irqrestore(&pdev->queued_bufs_lock, flags);
	वापस buf;
पूर्ण

अटल व्योम pwc_snapshot_button(काष्ठा pwc_device *pdev, पूर्णांक करोwn)
अणु
	अगर (करोwn) अणु
		PWC_TRACE("Snapshot button pressed.\n");
	पूर्ण अन्यथा अणु
		PWC_TRACE("Snapshot button released.\n");
	पूर्ण

#अगर_घोषित CONFIG_USB_PWC_INPUT_EVDEV
	अगर (pdev->button_dev) अणु
		input_report_key(pdev->button_dev, KEY_CAMERA, करोwn);
		input_sync(pdev->button_dev);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम pwc_frame_complete(काष्ठा pwc_device *pdev)
अणु
	काष्ठा pwc_frame_buf *fbuf = pdev->fill_buf;

	/* The ToUCam Fun CMOS sensor causes the firmware to send 2 or 3 bogus
	   frames on the USB wire after an exposure change. This conditition is
	   however detected  in the cam and a bit is set in the header.
	   */
	अगर (pdev->type == 730) अणु
		अचिन्हित अक्षर *ptr = (अचिन्हित अक्षर *)fbuf->data;

		अगर (ptr[1] == 1 && ptr[0] & 0x10) अणु
			PWC_TRACE("Hyundai CMOS sensor bug. Dropping frame.\n");
			pdev->drop_frames += 2;
		पूर्ण
		अगर ((ptr[0] ^ pdev->vmirror) & 0x01) अणु
			pwc_snapshot_button(pdev, ptr[0] & 0x01);
		पूर्ण
		अगर ((ptr[0] ^ pdev->vmirror) & 0x02) अणु
			अगर (ptr[0] & 0x02)
				PWC_TRACE("Image is mirrored.\n");
			अन्यथा
				PWC_TRACE("Image is normal.\n");
		पूर्ण
		pdev->vmirror = ptr[0] & 0x03;
		/* Someबार the trailer of the 730 is still sent as a 4 byte packet
		   after a लघु frame; this condition is filtered out specअगरically. A 4 byte
		   frame करोesn't make sense anyway.
		   So we get either this sequence:
		   drop_bit set -> 4 byte frame -> लघु frame -> good frame
		   Or this one:
		   drop_bit set -> लघु frame -> good frame
		   So we drop either 3 or 2 frames in all!
		   */
		अगर (fbuf->filled == 4)
			pdev->drop_frames++;
	पूर्ण अन्यथा अगर (pdev->type == 740 || pdev->type == 720) अणु
		अचिन्हित अक्षर *ptr = (अचिन्हित अक्षर *)fbuf->data;
		अगर ((ptr[0] ^ pdev->vmirror) & 0x01) अणु
			pwc_snapshot_button(pdev, ptr[0] & 0x01);
		पूर्ण
		pdev->vmirror = ptr[0] & 0x03;
	पूर्ण

	/* In हाल we were inकाष्ठाed to drop the frame, करो so silently. */
	अगर (pdev->drop_frames > 0) अणु
		pdev->drop_frames--;
	पूर्ण अन्यथा अणु
		/* Check क्रम underflow first */
		अगर (fbuf->filled < pdev->frame_total_size) अणु
			PWC_DEBUG_FLOW("Frame buffer underflow (%d bytes); discarded.\n",
				       fbuf->filled);
		पूर्ण अन्यथा अणु
			fbuf->vb.field = V4L2_FIELD_NONE;
			fbuf->vb.sequence = pdev->vframe_count;
			vb2_buffer_करोne(&fbuf->vb.vb2_buf, VB2_BUF_STATE_DONE);
			pdev->fill_buf = शून्य;
			pdev->vsync = 0;
		पूर्ण
	पूर्ण /* !drop_frames */
	pdev->vframe_count++;
पूर्ण

/* This माला_लो called क्रम the Isochronous pipe (video). This is करोne in
 * पूर्णांकerrupt समय, so it has to be fast, not crash, and not stall. Neat.
 */
अटल व्योम pwc_isoc_handler(काष्ठा urb *urb)
अणु
	काष्ठा pwc_device *pdev = (काष्ठा pwc_device *)urb->context;
	काष्ठा device *dmadev = urb->dev->bus->sysdev;
	पूर्णांक i, fst, flen;
	अचिन्हित अक्षर *iso_buf = शून्य;

	trace_pwc_handler_enter(urb, pdev);

	अगर (urb->status == -ENOENT || urb->status == -ECONNRESET ||
	    urb->status == -ESHUTDOWN) अणु
		PWC_DEBUG_OPEN("URB (%p) unlinked %ssynchronously.\n",
			       urb, urb->status == -ENOENT ? "" : "a");
		वापस;
	पूर्ण

	अगर (pdev->fill_buf == शून्य)
		pdev->fill_buf = pwc_get_next_fill_buf(pdev);

	अगर (urb->status != 0) अणु
		स्थिर अक्षर *errmsg;

		errmsg = "Unknown";
		चयन(urb->status) अणु
			हाल -ENOSR:		errmsg = "Buffer error (overrun)"; अवरोध;
			हाल -EPIPE:		errmsg = "Stalled (device not responding)"; अवरोध;
			हाल -EOVERFLOW:	errmsg = "Babble (bad cable?)"; अवरोध;
			हाल -EPROTO:		errmsg = "Bit-stuff error (bad cable?)"; अवरोध;
			हाल -EILSEQ:		errmsg = "CRC/Timeout (could be anything)"; अवरोध;
			हाल -ETIME:		errmsg = "Device does not respond"; अवरोध;
		पूर्ण
		PWC_ERROR("pwc_isoc_handler() called with status %d [%s].\n",
			  urb->status, errmsg);
		/* Give up after a number of contiguous errors */
		अगर (++pdev->visoc_errors > MAX_ISOC_ERRORS)
		अणु
			PWC_ERROR("Too many ISOC errors, bailing out.\n");
			अगर (pdev->fill_buf) अणु
				vb2_buffer_करोne(&pdev->fill_buf->vb.vb2_buf,
						VB2_BUF_STATE_ERROR);
				pdev->fill_buf = शून्य;
			पूर्ण
		पूर्ण
		pdev->vsync = 0; /* Drop the current frame */
		जाओ handler_end;
	पूर्ण

	/* Reset ISOC error counter. We did get here, after all. */
	pdev->visoc_errors = 0;

	dma_sync_single_क्रम_cpu(dmadev,
				urb->transfer_dma,
				urb->transfer_buffer_length,
				DMA_FROM_DEVICE);

	/* vsync: 0 = करोn't copy data
		  1 = sync-hunt
		  2 = synched
	 */
	/* Compact data */
	क्रम (i = 0; i < urb->number_of_packets; i++) अणु
		fst  = urb->iso_frame_desc[i].status;
		flen = urb->iso_frame_desc[i].actual_length;
		iso_buf = urb->transfer_buffer + urb->iso_frame_desc[i].offset;
		अगर (fst != 0) अणु
			PWC_ERROR("Iso frame %d has error %d\n", i, fst);
			जारी;
		पूर्ण
		अगर (flen > 0 && pdev->vsync) अणु
			काष्ठा pwc_frame_buf *fbuf = pdev->fill_buf;

			अगर (pdev->vsync == 1) अणु
				fbuf->vb.vb2_buf.बारtamp = kसमय_get_ns();
				pdev->vsync = 2;
			पूर्ण

			अगर (flen + fbuf->filled > pdev->frame_total_size) अणु
				PWC_ERROR("Frame overflow (%d > %d)\n",
					  flen + fbuf->filled,
					  pdev->frame_total_size);
				pdev->vsync = 0; /* Let's रुको क्रम an खातापूर्ण */
			पूर्ण अन्यथा अणु
				स_नकल(fbuf->data + fbuf->filled, iso_buf,
				       flen);
				fbuf->filled += flen;
			पूर्ण
		पूर्ण
		अगर (flen < pdev->vlast_packet_size) अणु
			/* Shorter packet... end of frame */
			अगर (pdev->vsync == 2)
				pwc_frame_complete(pdev);
			अगर (pdev->fill_buf == शून्य)
				pdev->fill_buf = pwc_get_next_fill_buf(pdev);
			अगर (pdev->fill_buf) अणु
				pdev->fill_buf->filled = 0;
				pdev->vsync = 1;
			पूर्ण
		पूर्ण
		pdev->vlast_packet_size = flen;
	पूर्ण

	dma_sync_single_क्रम_device(dmadev,
				   urb->transfer_dma,
				   urb->transfer_buffer_length,
				   DMA_FROM_DEVICE);

handler_end:
	trace_pwc_handler_निकास(urb, pdev);

	i = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (i != 0)
		PWC_ERROR("Error (%d) re-submitting urb in pwc_isoc_handler.\n", i);
पूर्ण

/* Both v4l2_lock and vb_queue_lock should be locked when calling this */
अटल पूर्णांक pwc_isoc_init(काष्ठा pwc_device *pdev)
अणु
	काष्ठा usb_device *udev;
	काष्ठा urb *urb;
	पूर्णांक i, j, ret;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा usb_host_पूर्णांकerface *idesc = शून्य;
	पूर्णांक compression = 0; /* 0..3 = uncompressed..high */

	pdev->vsync = 0;
	pdev->vlast_packet_size = 0;
	pdev->fill_buf = शून्य;
	pdev->vframe_count = 0;
	pdev->visoc_errors = 0;
	udev = pdev->udev;

retry:
	/* We first try with low compression and then retry with a higher
	   compression setting अगर there is not enough bandwidth. */
	ret = pwc_set_video_mode(pdev, pdev->width, pdev->height, pdev->pixfmt,
				 pdev->vframes, &compression, 1);

	/* Get the current alternate पूर्णांकerface, adjust packet size */
	पूर्णांकf = usb_अगरnum_to_अगर(udev, 0);
	अगर (पूर्णांकf)
		idesc = usb_altnum_to_altsetting(पूर्णांकf, pdev->valternate);
	अगर (!idesc)
		वापस -EIO;

	/* Search video endpoपूर्णांक */
	pdev->vmax_packet_size = -1;
	क्रम (i = 0; i < idesc->desc.bNumEndpoपूर्णांकs; i++) अणु
		अगर ((idesc->endpoपूर्णांक[i].desc.bEndpoपूर्णांकAddress & 0xF) == pdev->vendpoपूर्णांक) अणु
			pdev->vmax_packet_size = le16_to_cpu(idesc->endpoपूर्णांक[i].desc.wMaxPacketSize);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (pdev->vmax_packet_size < 0 || pdev->vmax_packet_size > ISO_MAX_FRAME_SIZE) अणु
		PWC_ERROR("Failed to find packet size for video endpoint in current alternate setting.\n");
		वापस -ENखाता; /* Odd error, that should be noticeable */
	पूर्ण

	/* Set alternate पूर्णांकerface */
	PWC_DEBUG_OPEN("Setting alternate interface %d\n", pdev->valternate);
	ret = usb_set_पूर्णांकerface(pdev->udev, 0, pdev->valternate);
	अगर (ret == -ENOSPC && compression < 3) अणु
		compression++;
		जाओ retry;
	पूर्ण
	अगर (ret < 0)
		वापस ret;

	/* Allocate and init Isochronuous urbs */
	क्रम (i = 0; i < MAX_ISO_BUFS; i++) अणु
		urb = usb_alloc_urb(ISO_FRAMES_PER_DESC, GFP_KERNEL);
		अगर (urb == शून्य) अणु
			pwc_isoc_cleanup(pdev);
			वापस -ENOMEM;
		पूर्ण
		pdev->urbs[i] = urb;
		PWC_DEBUG_MEMORY("Allocated URB at 0x%p\n", urb);

		urb->पूर्णांकerval = 1; // devik
		urb->dev = udev;
		urb->pipe = usb_rcvisocpipe(udev, pdev->vendpoपूर्णांक);
		urb->transfer_flags = URB_ISO_ASAP | URB_NO_TRANSFER_DMA_MAP;
		urb->transfer_buffer_length = ISO_BUFFER_SIZE;
		urb->transfer_buffer = pwc_alloc_urb_buffer(udev,
							    urb->transfer_buffer_length,
							    &urb->transfer_dma);
		अगर (urb->transfer_buffer == शून्य) अणु
			PWC_ERROR("Failed to allocate urb buffer %d\n", i);
			pwc_isoc_cleanup(pdev);
			वापस -ENOMEM;
		पूर्ण
		urb->complete = pwc_isoc_handler;
		urb->context = pdev;
		urb->start_frame = 0;
		urb->number_of_packets = ISO_FRAMES_PER_DESC;
		क्रम (j = 0; j < ISO_FRAMES_PER_DESC; j++) अणु
			urb->iso_frame_desc[j].offset = j * ISO_MAX_FRAME_SIZE;
			urb->iso_frame_desc[j].length = pdev->vmax_packet_size;
		पूर्ण
	पूर्ण

	/* link */
	क्रम (i = 0; i < MAX_ISO_BUFS; i++) अणु
		ret = usb_submit_urb(pdev->urbs[i], GFP_KERNEL);
		अगर (ret == -ENOSPC && compression < 3) अणु
			compression++;
			pwc_isoc_cleanup(pdev);
			जाओ retry;
		पूर्ण
		अगर (ret) अणु
			PWC_ERROR("isoc_init() submit_urb %d failed with error %d\n", i, ret);
			pwc_isoc_cleanup(pdev);
			वापस ret;
		पूर्ण
		PWC_DEBUG_MEMORY("URB 0x%p submitted.\n", pdev->urbs[i]);
	पूर्ण

	/* All is करोne... */
	PWC_DEBUG_OPEN("<< pwc_isoc_init()\n");
	वापस 0;
पूर्ण

अटल व्योम pwc_iso_stop(काष्ठा pwc_device *pdev)
अणु
	पूर्णांक i;

	/* Unlinking ISOC buffers one by one */
	क्रम (i = 0; i < MAX_ISO_BUFS; i++) अणु
		अगर (pdev->urbs[i]) अणु
			PWC_DEBUG_MEMORY("Unlinking URB %p\n", pdev->urbs[i]);
			usb_समाप्त_urb(pdev->urbs[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pwc_iso_मुक्त(काष्ठा pwc_device *pdev)
अणु
	पूर्णांक i;

	/* Freeing ISOC buffers one by one */
	क्रम (i = 0; i < MAX_ISO_BUFS; i++) अणु
		काष्ठा urb *urb = pdev->urbs[i];

		अगर (urb) अणु
			PWC_DEBUG_MEMORY("Freeing URB\n");
			अगर (urb->transfer_buffer)
				pwc_मुक्त_urb_buffer(urb->dev,
						    urb->transfer_buffer_length,
						    urb->transfer_buffer,
						    urb->transfer_dma);
			usb_मुक्त_urb(urb);
			pdev->urbs[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/* Both v4l2_lock and vb_queue_lock should be locked when calling this */
अटल व्योम pwc_isoc_cleanup(काष्ठा pwc_device *pdev)
अणु
	PWC_DEBUG_OPEN(">> pwc_isoc_cleanup()\n");

	pwc_iso_stop(pdev);
	pwc_iso_मुक्त(pdev);
	usb_set_पूर्णांकerface(pdev->udev, 0, 0);

	PWC_DEBUG_OPEN("<< pwc_isoc_cleanup()\n");
पूर्ण

/* Must be called with vb_queue_lock hold */
अटल व्योम pwc_cleanup_queued_bufs(काष्ठा pwc_device *pdev,
				    क्रमागत vb2_buffer_state state)
अणु
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(&pdev->queued_bufs_lock, flags);
	जबतक (!list_empty(&pdev->queued_bufs)) अणु
		काष्ठा pwc_frame_buf *buf;

		buf = list_entry(pdev->queued_bufs.next, काष्ठा pwc_frame_buf,
				 list);
		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, state);
	पूर्ण
	spin_unlock_irqrestore(&pdev->queued_bufs_lock, flags);
पूर्ण

#अगर_घोषित CONFIG_USB_PWC_DEBUG
अटल स्थिर अक्षर *pwc_sensor_type_to_string(अचिन्हित पूर्णांक sensor_type)
अणु
	चयन(sensor_type) अणु
		हाल 0x00:
			वापस "Hyundai CMOS sensor";
		हाल 0x20:
			वापस "Sony CCD sensor + TDA8787";
		हाल 0x2E:
			वापस "Sony CCD sensor + Exas 98L59";
		हाल 0x2F:
			वापस "Sony CCD sensor + ADI 9804";
		हाल 0x30:
			वापस "Sharp CCD sensor + TDA8787";
		हाल 0x3E:
			वापस "Sharp CCD sensor + Exas 98L59";
		हाल 0x3F:
			वापस "Sharp CCD sensor + ADI 9804";
		हाल 0x40:
			वापस "UPA 1021 sensor";
		हाल 0x100:
			वापस "VGA sensor";
		हाल 0x101:
			वापस "PAL MR sensor";
		शेष:
			वापस "unknown type of sensor";
	पूर्ण
पूर्ण
#पूर्ण_अगर

/***************************************************************************/
/* Video4Linux functions */

अटल व्योम pwc_video_release(काष्ठा v4l2_device *v)
अणु
	काष्ठा pwc_device *pdev = container_of(v, काष्ठा pwc_device, v4l2_dev);

	v4l2_ctrl_handler_मुक्त(&pdev->ctrl_handler);
	v4l2_device_unरेजिस्टर(&pdev->v4l2_dev);
	kमुक्त(pdev->ctrl_buf);
	kमुक्त(pdev);
पूर्ण

/***************************************************************************/
/* Videobuf2 operations */

अटल पूर्णांक queue_setup(काष्ठा vb2_queue *vq,
				अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
				अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा pwc_device *pdev = vb2_get_drv_priv(vq);
	पूर्णांक size;

	अगर (*nbuffers < MIN_FRAMES)
		*nbuffers = MIN_FRAMES;
	अन्यथा अगर (*nbuffers > MAX_FRAMES)
		*nbuffers = MAX_FRAMES;

	*nplanes = 1;

	size = pwc_get_size(pdev, MAX_WIDTH, MAX_HEIGHT);
	sizes[0] = PAGE_ALIGN(pwc_image_sizes[size][0] *
			      pwc_image_sizes[size][1] * 3 / 2);

	वापस 0;
पूर्ण

अटल पूर्णांक buffer_init(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा pwc_frame_buf *buf =
		container_of(vbuf, काष्ठा pwc_frame_buf, vb);

	/* need vदो_स्मृति since frame buffer > 128K */
	buf->data = vzalloc(PWC_FRAME_SIZE);
	अगर (buf->data == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा pwc_device *pdev = vb2_get_drv_priv(vb->vb2_queue);

	/* Don't allow queueing new buffers after device disconnection */
	अगर (!pdev->udev)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल व्योम buffer_finish(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा pwc_device *pdev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा pwc_frame_buf *buf =
		container_of(vbuf, काष्ठा pwc_frame_buf, vb);

	अगर (vb->state == VB2_BUF_STATE_DONE) अणु
		/*
		 * Application has called dqbuf and is getting back a buffer
		 * we've filled, take the pwc data we've stored in buf->data
		 * and decompress it पूर्णांकo a usable क्रमmat, storing the result
		 * in the vb2_buffer.
		 */
		pwc_decompress(pdev, buf);
	पूर्ण
पूर्ण

अटल व्योम buffer_cleanup(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा pwc_frame_buf *buf =
		container_of(vbuf, काष्ठा pwc_frame_buf, vb);

	vमुक्त(buf->data);
पूर्ण

अटल व्योम buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा pwc_device *pdev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा pwc_frame_buf *buf =
		container_of(vbuf, काष्ठा pwc_frame_buf, vb);
	अचिन्हित दीर्घ flags = 0;

	/* Check the device has not disconnected between prep and queuing */
	अगर (!pdev->udev) अणु
		vb2_buffer_करोne(vb, VB2_BUF_STATE_ERROR);
		वापस;
	पूर्ण

	spin_lock_irqsave(&pdev->queued_bufs_lock, flags);
	list_add_tail(&buf->list, &pdev->queued_bufs);
	spin_unlock_irqrestore(&pdev->queued_bufs_lock, flags);
पूर्ण

अटल पूर्णांक start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा pwc_device *pdev = vb2_get_drv_priv(vq);
	पूर्णांक r;

	अगर (!pdev->udev)
		वापस -ENODEV;

	अगर (mutex_lock_पूर्णांकerruptible(&pdev->v4l2_lock))
		वापस -ERESTARTSYS;
	/* Turn on camera and set LEDS on */
	pwc_camera_घातer(pdev, 1);
	pwc_set_leds(pdev, leds[0], leds[1]);

	r = pwc_isoc_init(pdev);
	अगर (r) अणु
		/* If we failed turn camera and LEDS back off */
		pwc_set_leds(pdev, 0, 0);
		pwc_camera_घातer(pdev, 0);
		/* And cleanup any queued bufs!! */
		pwc_cleanup_queued_bufs(pdev, VB2_BUF_STATE_QUEUED);
	पूर्ण
	mutex_unlock(&pdev->v4l2_lock);

	वापस r;
पूर्ण

अटल व्योम stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा pwc_device *pdev = vb2_get_drv_priv(vq);

	mutex_lock(&pdev->v4l2_lock);
	अगर (pdev->udev) अणु
		pwc_set_leds(pdev, 0, 0);
		pwc_camera_घातer(pdev, 0);
		pwc_isoc_cleanup(pdev);
	पूर्ण

	pwc_cleanup_queued_bufs(pdev, VB2_BUF_STATE_ERROR);
	अगर (pdev->fill_buf)
		vb2_buffer_करोne(&pdev->fill_buf->vb.vb2_buf,
				VB2_BUF_STATE_ERROR);
	mutex_unlock(&pdev->v4l2_lock);
पूर्ण

अटल स्थिर काष्ठा vb2_ops pwc_vb_queue_ops = अणु
	.queue_setup		= queue_setup,
	.buf_init		= buffer_init,
	.buf_prepare		= buffer_prepare,
	.buf_finish		= buffer_finish,
	.buf_cleanup		= buffer_cleanup,
	.buf_queue		= buffer_queue,
	.start_streaming	= start_streaming,
	.stop_streaming		= stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

/***************************************************************************/
/* USB functions */

/* This function माला_लो called when a new device is plugged in or the usb core
 * is loaded.
 */

अटल पूर्णांक usb_pwc_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा pwc_device *pdev = शून्य;
	पूर्णांक venकरोr_id, product_id, type_id;
	पूर्णांक rc;
	पूर्णांक features = 0;
	पूर्णांक compression = 0;
	पूर्णांक my_घातer_save = घातer_save;
	अक्षर serial_number[30], *name;

	venकरोr_id = le16_to_cpu(udev->descriptor.idVenकरोr);
	product_id = le16_to_cpu(udev->descriptor.idProduct);

	/* Check अगर we can handle this device */
	PWC_DEBUG_PROBE("probe() called [%04X %04X], if %d\n",
		venकरोr_id, product_id,
		पूर्णांकf->altsetting->desc.bInterfaceNumber);

	/* the पूर्णांकerfaces are probed one by one. We are only पूर्णांकerested in the
	   video पूर्णांकerface (0) now.
	   Interface 1 is the Audio Control, and पूर्णांकerface 2 Audio itself.
	 */
	अगर (पूर्णांकf->altsetting->desc.bInterfaceNumber > 0)
		वापस -ENODEV;

	अगर (venकरोr_id == 0x0471) अणु
		चयन (product_id) अणु
		हाल 0x0302:
			PWC_INFO("Philips PCA645VC USB webcam detected.\n");
			name = "Philips 645 webcam";
			type_id = 645;
			अवरोध;
		हाल 0x0303:
			PWC_INFO("Philips PCA646VC USB webcam detected.\n");
			name = "Philips 646 webcam";
			type_id = 646;
			अवरोध;
		हाल 0x0304:
			PWC_INFO("Askey VC010 type 2 USB webcam detected.\n");
			name = "Askey VC010 webcam";
			type_id = 646;
			अवरोध;
		हाल 0x0307:
			PWC_INFO("Philips PCVC675K (Vesta) USB webcam detected.\n");
			name = "Philips 675 webcam";
			type_id = 675;
			अवरोध;
		हाल 0x0308:
			PWC_INFO("Philips PCVC680K (Vesta Pro) USB webcam detected.\n");
			name = "Philips 680 webcam";
			type_id = 680;
			अवरोध;
		हाल 0x030C:
			PWC_INFO("Philips PCVC690K (Vesta Pro Scan) USB webcam detected.\n");
			name = "Philips 690 webcam";
			type_id = 690;
			अवरोध;
		हाल 0x0310:
			PWC_INFO("Philips PCVC730K (ToUCam Fun)/PCVC830 (ToUCam II) USB webcam detected.\n");
			name = "Philips 730 webcam";
			type_id = 730;
			अवरोध;
		हाल 0x0311:
			PWC_INFO("Philips PCVC740K (ToUCam Pro)/PCVC840 (ToUCam II) USB webcam detected.\n");
			name = "Philips 740 webcam";
			type_id = 740;
			अवरोध;
		हाल 0x0312:
			PWC_INFO("Philips PCVC750K (ToUCam Pro Scan) USB webcam detected.\n");
			name = "Philips 750 webcam";
			type_id = 750;
			अवरोध;
		हाल 0x0313:
			PWC_INFO("Philips PCVC720K/40 (ToUCam XS) USB webcam detected.\n");
			name = "Philips 720K/40 webcam";
			type_id = 720;
			अवरोध;
		हाल 0x0329:
			PWC_INFO("Philips SPC 900NC USB webcam detected.\n");
			name = "Philips SPC 900NC webcam";
			type_id = 740;
			अवरोध;
		हाल 0x032C:
			PWC_INFO("Philips SPC 880NC USB webcam detected.\n");
			name = "Philips SPC 880NC webcam";
			type_id = 740;
			अवरोध;
		शेष:
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	अन्यथा अगर (venकरोr_id == 0x069A) अणु
		चयन(product_id) अणु
		हाल 0x0001:
			PWC_INFO("Askey VC010 type 1 USB webcam detected.\n");
			name = "Askey VC010 webcam";
			type_id = 645;
			अवरोध;
		शेष:
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	अन्यथा अगर (venकरोr_id == 0x046d) अणु
		चयन(product_id) अणु
		हाल 0x08b0:
			PWC_INFO("Logitech QuickCam Pro 3000 USB webcam detected.\n");
			name = "Logitech QuickCam Pro 3000";
			type_id = 740; /* CCD sensor */
			अवरोध;
		हाल 0x08b1:
			PWC_INFO("Logitech QuickCam Notebook Pro USB webcam detected.\n");
			name = "Logitech QuickCam Notebook Pro";
			type_id = 740; /* CCD sensor */
			अवरोध;
		हाल 0x08b2:
			PWC_INFO("Logitech QuickCam 4000 Pro USB webcam detected.\n");
			name = "Logitech QuickCam Pro 4000";
			type_id = 740; /* CCD sensor */
			अगर (my_घातer_save == -1)
				my_घातer_save = 1;
			अवरोध;
		हाल 0x08b3:
			PWC_INFO("Logitech QuickCam Zoom USB webcam detected.\n");
			name = "Logitech QuickCam Zoom";
			type_id = 740; /* CCD sensor */
			अवरोध;
		हाल 0x08B4:
			PWC_INFO("Logitech QuickCam Zoom (new model) USB webcam detected.\n");
			name = "Logitech QuickCam Zoom";
			type_id = 740; /* CCD sensor */
			अगर (my_घातer_save == -1)
				my_घातer_save = 1;
			अवरोध;
		हाल 0x08b5:
			PWC_INFO("Logitech QuickCam Orbit/Sphere USB webcam detected.\n");
			name = "Logitech QuickCam Orbit";
			type_id = 740; /* CCD sensor */
			अगर (my_घातer_save == -1)
				my_घातer_save = 1;
			features |= FEATURE_MOTOR_PANTILT;
			अवरोध;
		हाल 0x08b6:
			PWC_INFO("Logitech/Cisco VT Camera webcam detected.\n");
			name = "Cisco VT Camera";
			type_id = 740; /* CCD sensor */
			अवरोध;
		हाल 0x08b7:
			PWC_INFO("Logitech ViewPort AV 100 webcam detected.\n");
			name = "Logitech ViewPort AV 100";
			type_id = 740; /* CCD sensor */
			अवरोध;
		हाल 0x08b8: /* Where this released? */
			PWC_INFO("Logitech QuickCam detected (reserved ID).\n");
			name = "Logitech QuickCam (res.)";
			type_id = 730; /* Assuming CMOS */
			अवरोध;
		शेष:
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	अन्यथा अगर (venकरोr_id == 0x055d) अणु
		/* I करोn't know the dअगरference between the C10 and the C30;
		   I suppose the dअगरference is the sensor, but both cameras
		   work equally well with a type_id of 675
		 */
		चयन(product_id) अणु
		हाल 0x9000:
			PWC_INFO("Samsung MPC-C10 USB webcam detected.\n");
			name = "Samsung MPC-C10";
			type_id = 675;
			अवरोध;
		हाल 0x9001:
			PWC_INFO("Samsung MPC-C30 USB webcam detected.\n");
			name = "Samsung MPC-C30";
			type_id = 675;
			अवरोध;
		हाल 0x9002:
			PWC_INFO("Samsung SNC-35E (v3.0) USB webcam detected.\n");
			name = "Samsung MPC-C30";
			type_id = 740;
			अवरोध;
		शेष:
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	अन्यथा अगर (venकरोr_id == 0x041e) अणु
		चयन(product_id) अणु
		हाल 0x400c:
			PWC_INFO("Creative Labs Webcam 5 detected.\n");
			name = "Creative Labs Webcam 5";
			type_id = 730;
			अगर (my_घातer_save == -1)
				my_घातer_save = 1;
			अवरोध;
		हाल 0x4011:
			PWC_INFO("Creative Labs Webcam Pro Ex detected.\n");
			name = "Creative Labs Webcam Pro Ex";
			type_id = 740;
			अवरोध;
		शेष:
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	अन्यथा अगर (venकरोr_id == 0x04cc) अणु
		चयन(product_id) अणु
		हाल 0x8116:
			PWC_INFO("Sotec Afina Eye USB webcam detected.\n");
			name = "Sotec Afina Eye";
			type_id = 730;
			अवरोध;
		शेष:
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	अन्यथा अगर (venकरोr_id == 0x06be) अणु
		चयन(product_id) अणु
		हाल 0x8116:
			/* This is essentially the same cam as the Sotec Afina Eye */
			PWC_INFO("AME Co. Afina Eye USB webcam detected.\n");
			name = "AME Co. Afina Eye";
			type_id = 750;
			अवरोध;
		शेष:
			वापस -ENODEV;
		पूर्ण

	पूर्ण
	अन्यथा अगर (venकरोr_id == 0x0d81) अणु
		चयन(product_id) अणु
		हाल 0x1900:
			PWC_INFO("Visionite VCS-UC300 USB webcam detected.\n");
			name = "Visionite VCS-UC300";
			type_id = 740; /* CCD sensor */
			अवरोध;
		हाल 0x1910:
			PWC_INFO("Visionite VCS-UM100 USB webcam detected.\n");
			name = "Visionite VCS-UM100";
			type_id = 730; /* CMOS sensor */
			अवरोध;
		शेष:
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	अन्यथा
		वापस -ENODEV; /* Not any of the know types; but the list keeps growing. */

	अगर (my_घातer_save == -1)
		my_घातer_save = 0;

	स_रखो(serial_number, 0, 30);
	usb_string(udev, udev->descriptor.iSerialNumber, serial_number, 29);
	PWC_DEBUG_PROBE("Device serial number is %s\n", serial_number);

	अगर (udev->descriptor.bNumConfigurations > 1)
		PWC_WARNING("Warning: more than 1 configuration available.\n");

	/* Allocate काष्ठाure, initialize poपूर्णांकers, mutexes, etc. and link it to the usb_device */
	pdev = kzalloc(माप(काष्ठा pwc_device), GFP_KERNEL);
	अगर (pdev == शून्य) अणु
		PWC_ERROR("Oops, could not allocate memory for pwc_device.\n");
		वापस -ENOMEM;
	पूर्ण
	pdev->type = type_id;
	pdev->features = features;
	pwc_स्थिरruct(pdev); /* set min/max sizes correct */

	mutex_init(&pdev->v4l2_lock);
	mutex_init(&pdev->vb_queue_lock);
	spin_lock_init(&pdev->queued_bufs_lock);
	INIT_LIST_HEAD(&pdev->queued_bufs);

	pdev->udev = udev;
	pdev->घातer_save = my_घातer_save;

	/* Init videobuf2 queue काष्ठाure */
	pdev->vb_queue.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	pdev->vb_queue.io_modes = VB2_MMAP | VB2_USERPTR | VB2_READ;
	pdev->vb_queue.drv_priv = pdev;
	pdev->vb_queue.buf_काष्ठा_size = माप(काष्ठा pwc_frame_buf);
	pdev->vb_queue.ops = &pwc_vb_queue_ops;
	pdev->vb_queue.mem_ops = &vb2_vदो_स्मृति_memops;
	pdev->vb_queue.बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	rc = vb2_queue_init(&pdev->vb_queue);
	अगर (rc < 0) अणु
		PWC_ERROR("Oops, could not initialize vb2 queue.\n");
		जाओ err_मुक्त_mem;
	पूर्ण

	/* Init video_device काष्ठाure */
	pdev->vdev = pwc_ढाँचा;
	strscpy(pdev->vdev.name, name, माप(pdev->vdev.name));
	pdev->vdev.queue = &pdev->vb_queue;
	pdev->vdev.queue->lock = &pdev->vb_queue_lock;
	video_set_drvdata(&pdev->vdev, pdev);

	pdev->release = le16_to_cpu(udev->descriptor.bcdDevice);
	PWC_DEBUG_PROBE("Release: %04x\n", pdev->release);

	/* Allocate USB command buffers */
	pdev->ctrl_buf = kदो_स्मृति(माप(pdev->cmd_buf), GFP_KERNEL);
	अगर (!pdev->ctrl_buf) अणु
		PWC_ERROR("Oops, could not allocate memory for pwc_device.\n");
		rc = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

#अगर_घोषित CONFIG_USB_PWC_DEBUG
	/* Query sensor type */
	अगर (pwc_get_cmos_sensor(pdev, &rc) >= 0) अणु
		PWC_DEBUG_OPEN("This %s camera is equipped with a %s (%d).\n",
				pdev->vdev.name,
				pwc_sensor_type_to_string(rc), rc);
	पूर्ण
#पूर्ण_अगर

	/* Set the leds off */
	pwc_set_leds(pdev, 0, 0);

	/* Setup initial videomode */
	rc = pwc_set_video_mode(pdev, MAX_WIDTH, MAX_HEIGHT,
				V4L2_PIX_FMT_YUV420, 30, &compression, 1);
	अगर (rc)
		जाओ err_मुक्त_mem;

	/* Register controls (and पढ़ो शेष values from camera */
	rc = pwc_init_controls(pdev);
	अगर (rc) अणु
		PWC_ERROR("Failed to register v4l2 controls (%d).\n", rc);
		जाओ err_मुक्त_mem;
	पूर्ण

	/* And घातerकरोwn the camera until streaming starts */
	pwc_camera_घातer(pdev, 0);

	/* Register the v4l2_device काष्ठाure */
	pdev->v4l2_dev.release = pwc_video_release;
	rc = v4l2_device_रेजिस्टर(&पूर्णांकf->dev, &pdev->v4l2_dev);
	अगर (rc) अणु
		PWC_ERROR("Failed to register v4l2-device (%d).\n", rc);
		जाओ err_मुक्त_controls;
	पूर्ण

	pdev->v4l2_dev.ctrl_handler = &pdev->ctrl_handler;
	pdev->vdev.v4l2_dev = &pdev->v4l2_dev;
	pdev->vdev.lock = &pdev->v4l2_lock;
	pdev->vdev.device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING |
				 V4L2_CAP_READWRITE;

	rc = video_रेजिस्टर_device(&pdev->vdev, VFL_TYPE_VIDEO, -1);
	अगर (rc < 0) अणु
		PWC_ERROR("Failed to register as video device (%d).\n", rc);
		जाओ err_unरेजिस्टर_v4l2_dev;
	पूर्ण
	PWC_INFO("Registered as %s.\n", video_device_node_name(&pdev->vdev));

#अगर_घोषित CONFIG_USB_PWC_INPUT_EVDEV
	/* रेजिस्टर webcam snapshot button input device */
	pdev->button_dev = input_allocate_device();
	अगर (!pdev->button_dev) अणु
		rc = -ENOMEM;
		जाओ err_video_unreg;
	पूर्ण

	usb_make_path(udev, pdev->button_phys, माप(pdev->button_phys));
	strlcat(pdev->button_phys, "/input0", माप(pdev->button_phys));

	pdev->button_dev->name = "PWC snapshot button";
	pdev->button_dev->phys = pdev->button_phys;
	usb_to_input_id(pdev->udev, &pdev->button_dev->id);
	pdev->button_dev->dev.parent = &pdev->udev->dev;
	pdev->button_dev->evbit[0] = BIT_MASK(EV_KEY);
	pdev->button_dev->keybit[BIT_WORD(KEY_CAMERA)] = BIT_MASK(KEY_CAMERA);

	rc = input_रेजिस्टर_device(pdev->button_dev);
	अगर (rc) अणु
		input_मुक्त_device(pdev->button_dev);
		pdev->button_dev = शून्य;
		जाओ err_video_unreg;
	पूर्ण
#पूर्ण_अगर

	वापस 0;

#अगर_घोषित CONFIG_USB_PWC_INPUT_EVDEV
err_video_unreg:
	video_unरेजिस्टर_device(&pdev->vdev);
#पूर्ण_अगर
err_unरेजिस्टर_v4l2_dev:
	v4l2_device_unरेजिस्टर(&pdev->v4l2_dev);
err_मुक्त_controls:
	v4l2_ctrl_handler_मुक्त(&pdev->ctrl_handler);
err_मुक्त_mem:
	kमुक्त(pdev->ctrl_buf);
	kमुक्त(pdev);
	वापस rc;
पूर्ण

/* The user yanked out the cable... */
अटल व्योम usb_pwc_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा v4l2_device *v = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा pwc_device *pdev = container_of(v, काष्ठा pwc_device, v4l2_dev);

	mutex_lock(&pdev->vb_queue_lock);
	mutex_lock(&pdev->v4l2_lock);
	/* No need to keep the urbs around after disconnection */
	अगर (pdev->vb_queue.streaming)
		pwc_isoc_cleanup(pdev);
	pdev->udev = शून्य;

	v4l2_device_disconnect(&pdev->v4l2_dev);
	video_unरेजिस्टर_device(&pdev->vdev);
	mutex_unlock(&pdev->v4l2_lock);
	mutex_unlock(&pdev->vb_queue_lock);

#अगर_घोषित CONFIG_USB_PWC_INPUT_EVDEV
	अगर (pdev->button_dev)
		input_unरेजिस्टर_device(pdev->button_dev);
#पूर्ण_अगर

	v4l2_device_put(&pdev->v4l2_dev);
पूर्ण


/*
 * Initialization code & module stuff
 */

अटल अचिन्हित पूर्णांक leds_nargs;

#अगर_घोषित CONFIG_USB_PWC_DEBUG
module_param_named(trace, pwc_trace, पूर्णांक, 0644);
#पूर्ण_अगर
module_param(घातer_save, पूर्णांक, 0644);
module_param_array(leds, पूर्णांक, &leds_nargs, 0444);

#अगर_घोषित CONFIG_USB_PWC_DEBUG
MODULE_PARM_DESC(trace, "For debugging purposes");
#पूर्ण_अगर
MODULE_PARM_DESC(घातer_save, "Turn power saving for new cameras on or off");
MODULE_PARM_DESC(leds, "LED on,off time in milliseconds");

MODULE_DESCRIPTION("Philips & OEM USB webcam driver");
MODULE_AUTHOR("Luc Saillard <luc@saillard.org>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("pwcx");
MODULE_VERSION( PWC_VERSION );

module_usb_driver(pwc_driver);
