<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Red Hat
 *
 * based in parts on udlfb.c:
 * Copyright (C) 2009 Roberto De Ioris <roberto@unbit.it>
 * Copyright (C) 2009 Jaya Kumar <jayakumar.lkml@gmail.com>
 * Copyright (C) 2009 Bernie Thompson <bernie@plugable.com>
 */

#समावेश <drm/drm.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "udl_drv.h"

/* -BULK_SIZE as per usb-skeleton. Can we get full page and aव्योम overhead? */
#घोषणा BULK_SIZE 512

#घोषणा NR_USB_REQUEST_CHANNEL 0x12

#घोषणा MAX_TRANSFER (PAGE_SIZE*16 - BULK_SIZE)
#घोषणा WRITES_IN_FLIGHT (4)
#घोषणा MAX_VENDOR_DESCRIPTOR_SIZE 256

#घोषणा GET_URB_TIMEOUT	HZ
#घोषणा FREE_URB_TIMEOUT (HZ*2)

अटल पूर्णांक udl_parse_venकरोr_descriptor(काष्ठा udl_device *udl)
अणु
	काष्ठा usb_device *udev = udl_to_usb_device(udl);
	अक्षर *desc;
	अक्षर *buf;
	अक्षर *desc_end;

	u8 total_len = 0;

	buf = kzalloc(MAX_VENDOR_DESCRIPTOR_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस false;
	desc = buf;

	total_len = usb_get_descriptor(udev, 0x5f, /* venकरोr specअगरic */
				    0, desc, MAX_VENDOR_DESCRIPTOR_SIZE);
	अगर (total_len > 5) अणु
		DRM_INFO("vendor descriptor length:%x data:%11ph\n",
			total_len, desc);

		अगर ((desc[0] != total_len) || /* descriptor length */
		    (desc[1] != 0x5f) ||   /* venकरोr descriptor type */
		    (desc[2] != 0x01) ||   /* version (2 bytes) */
		    (desc[3] != 0x00) ||
		    (desc[4] != total_len - 2)) /* length after type */
			जाओ unrecognized;

		desc_end = desc + total_len;
		desc += 5; /* the fixed header we've alपढ़ोy parsed */

		जबतक (desc < desc_end) अणु
			u8 length;
			u16 key;

			key = le16_to_cpu(*((u16 *) desc));
			desc += माप(u16);
			length = *desc;
			desc++;

			चयन (key) अणु
			हाल 0x0200: अणु /* max_area */
				u32 max_area;
				max_area = le32_to_cpu(*((u32 *)desc));
				DRM_DEBUG("DL chip limited to %d pixel modes\n",
					max_area);
				udl->sku_pixel_limit = max_area;
				अवरोध;
			पूर्ण
			शेष:
				अवरोध;
			पूर्ण
			desc += length;
		पूर्ण
	पूर्ण

	जाओ success;

unrecognized:
	/* allow udlfb to load क्रम now even अगर firmware unrecognized */
	DRM_ERROR("Unrecognized vendor firmware descriptor\n");

success:
	kमुक्त(buf);
	वापस true;
पूर्ण

/*
 * Need to ensure a channel is selected beक्रमe submitting URBs
 */
अटल पूर्णांक udl_select_std_channel(काष्ठा udl_device *udl)
अणु
	अटल स्थिर u8 set_def_chn[] = अणु0x57, 0xCD, 0xDC, 0xA7,
					 0x1C, 0x88, 0x5E, 0x15,
					 0x60, 0xFE, 0xC6, 0x97,
					 0x16, 0x3D, 0x47, 0xF2पूर्ण;

	व्योम *sendbuf;
	पूर्णांक ret;
	काष्ठा usb_device *udev = udl_to_usb_device(udl);

	sendbuf = kmemdup(set_def_chn, माप(set_def_chn), GFP_KERNEL);
	अगर (!sendbuf)
		वापस -ENOMEM;

	ret = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			      NR_USB_REQUEST_CHANNEL,
			      (USB_सूची_OUT | USB_TYPE_VENDOR), 0, 0,
			      sendbuf, माप(set_def_chn),
			      USB_CTRL_SET_TIMEOUT);
	kमुक्त(sendbuf);
	वापस ret < 0 ? ret : 0;
पूर्ण

अटल व्योम udl_release_urb_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा urb_node *unode = container_of(work, काष्ठा urb_node,
					      release_urb_work.work);

	up(&unode->dev->urbs.limit_sem);
पूर्ण

व्योम udl_urb_completion(काष्ठा urb *urb)
अणु
	काष्ठा urb_node *unode = urb->context;
	काष्ठा udl_device *udl = unode->dev;
	अचिन्हित दीर्घ flags;

	/* sync/async unlink faults aren't errors */
	अगर (urb->status) अणु
		अगर (!(urb->status == -ENOENT ||
		    urb->status == -ECONNRESET ||
		    urb->status == -ESHUTDOWN)) अणु
			DRM_ERROR("%s - nonzero write bulk status received: %d\n",
				__func__, urb->status);
		पूर्ण
	पूर्ण

	urb->transfer_buffer_length = udl->urbs.size; /* reset to actual */

	spin_lock_irqsave(&udl->urbs.lock, flags);
	list_add_tail(&unode->entry, &udl->urbs.list);
	udl->urbs.available++;
	spin_unlock_irqrestore(&udl->urbs.lock, flags);

#अगर 0
	/*
	 * When using fb_defio, we deadlock अगर up() is called
	 * जबतक another is रुकोing. So queue to another process.
	 */
	अगर (fb_defio)
		schedule_delayed_work(&unode->release_urb_work, 0);
	अन्यथा
#पूर्ण_अगर
		up(&udl->urbs.limit_sem);
पूर्ण

अटल व्योम udl_मुक्त_urb_list(काष्ठा drm_device *dev)
अणु
	काष्ठा udl_device *udl = to_udl(dev);
	पूर्णांक count = udl->urbs.count;
	काष्ठा list_head *node;
	काष्ठा urb_node *unode;
	काष्ठा urb *urb;

	DRM_DEBUG("Waiting for completes and freeing all render urbs\n");

	/* keep रुकोing and मुक्तing, until we've got 'em all */
	जबतक (count--) अणु
		करोwn(&udl->urbs.limit_sem);

		spin_lock_irq(&udl->urbs.lock);

		node = udl->urbs.list.next; /* have reserved one with sem */
		list_del_init(node);

		spin_unlock_irq(&udl->urbs.lock);

		unode = list_entry(node, काष्ठा urb_node, entry);
		urb = unode->urb;

		/* Free each separately allocated piece */
		usb_मुक्त_coherent(urb->dev, udl->urbs.size,
				  urb->transfer_buffer, urb->transfer_dma);
		usb_मुक्त_urb(urb);
		kमुक्त(node);
	पूर्ण
	udl->urbs.count = 0;
पूर्ण

अटल पूर्णांक udl_alloc_urb_list(काष्ठा drm_device *dev, पूर्णांक count, माप_प्रकार size)
अणु
	काष्ठा udl_device *udl = to_udl(dev);
	काष्ठा urb *urb;
	काष्ठा urb_node *unode;
	अक्षर *buf;
	माप_प्रकार wanted_size = count * size;
	काष्ठा usb_device *udev = udl_to_usb_device(udl);

	spin_lock_init(&udl->urbs.lock);

retry:
	udl->urbs.size = size;
	INIT_LIST_HEAD(&udl->urbs.list);

	sema_init(&udl->urbs.limit_sem, 0);
	udl->urbs.count = 0;
	udl->urbs.available = 0;

	जबतक (udl->urbs.count * size < wanted_size) अणु
		unode = kzalloc(माप(काष्ठा urb_node), GFP_KERNEL);
		अगर (!unode)
			अवरोध;
		unode->dev = udl;

		INIT_DELAYED_WORK(&unode->release_urb_work,
			  udl_release_urb_work);

		urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!urb) अणु
			kमुक्त(unode);
			अवरोध;
		पूर्ण
		unode->urb = urb;

		buf = usb_alloc_coherent(udev, size, GFP_KERNEL,
					 &urb->transfer_dma);
		अगर (!buf) अणु
			kमुक्त(unode);
			usb_मुक्त_urb(urb);
			अगर (size > PAGE_SIZE) अणु
				size /= 2;
				udl_मुक्त_urb_list(dev);
				जाओ retry;
			पूर्ण
			अवरोध;
		पूर्ण

		/* urb->transfer_buffer_length set to actual beक्रमe submit */
		usb_fill_bulk_urb(urb, udev, usb_sndbulkpipe(udev, 1),
				  buf, size, udl_urb_completion, unode);
		urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

		list_add_tail(&unode->entry, &udl->urbs.list);

		up(&udl->urbs.limit_sem);
		udl->urbs.count++;
		udl->urbs.available++;
	पूर्ण

	DRM_DEBUG("allocated %d %d byte urbs\n", udl->urbs.count, (पूर्णांक) size);

	वापस udl->urbs.count;
पूर्ण

काष्ठा urb *udl_get_urb(काष्ठा drm_device *dev)
अणु
	काष्ठा udl_device *udl = to_udl(dev);
	पूर्णांक ret = 0;
	काष्ठा list_head *entry;
	काष्ठा urb_node *unode;
	काष्ठा urb *urb = शून्य;

	/* Wait क्रम an in-flight buffer to complete and get re-queued */
	ret = करोwn_समयout(&udl->urbs.limit_sem, GET_URB_TIMEOUT);
	अगर (ret) अणु
		DRM_INFO("wait for urb interrupted: %x available: %d\n",
		       ret, udl->urbs.available);
		जाओ error;
	पूर्ण

	spin_lock_irq(&udl->urbs.lock);

	BUG_ON(list_empty(&udl->urbs.list)); /* reserved one with limit_sem */
	entry = udl->urbs.list.next;
	list_del_init(entry);
	udl->urbs.available--;

	spin_unlock_irq(&udl->urbs.lock);

	unode = list_entry(entry, काष्ठा urb_node, entry);
	urb = unode->urb;

error:
	वापस urb;
पूर्ण

पूर्णांक udl_submit_urb(काष्ठा drm_device *dev, काष्ठा urb *urb, माप_प्रकार len)
अणु
	काष्ठा udl_device *udl = to_udl(dev);
	पूर्णांक ret;

	BUG_ON(len > udl->urbs.size);

	urb->transfer_buffer_length = len; /* set to actual payload len */
	ret = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (ret) अणु
		udl_urb_completion(urb); /* because no one अन्यथा will */
		DRM_ERROR("usb_submit_urb error %x\n", ret);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक udl_init(काष्ठा udl_device *udl)
अणु
	काष्ठा drm_device *dev = &udl->drm;
	पूर्णांक ret = -ENOMEM;

	DRM_DEBUG("\n");

	udl->dmadev = usb_पूर्णांकf_get_dma_device(to_usb_पूर्णांकerface(dev->dev));
	अगर (!udl->dmadev)
		drm_warn(dev, "buffer sharing not supported"); /* not an error */

	mutex_init(&udl->gem_lock);

	अगर (!udl_parse_venकरोr_descriptor(udl)) अणु
		ret = -ENODEV;
		DRM_ERROR("firmware not recognized. Assume incompatible device\n");
		जाओ err;
	पूर्ण

	अगर (udl_select_std_channel(udl))
		DRM_ERROR("Selecting channel failed\n");

	अगर (!udl_alloc_urb_list(dev, WRITES_IN_FLIGHT, MAX_TRANSFER)) अणु
		DRM_ERROR("udl_alloc_urb_list failed\n");
		जाओ err;
	पूर्ण

	DRM_DEBUG("\n");
	ret = udl_modeset_init(dev);
	अगर (ret)
		जाओ err;

	drm_kms_helper_poll_init(dev);

	वापस 0;

err:
	अगर (udl->urbs.count)
		udl_मुक्त_urb_list(dev);
	put_device(udl->dmadev);
	DRM_ERROR("%d\n", ret);
	वापस ret;
पूर्ण

पूर्णांक udl_drop_usb(काष्ठा drm_device *dev)
अणु
	काष्ठा udl_device *udl = to_udl(dev);

	udl_मुक्त_urb_list(dev);
	put_device(udl->dmadev);
	udl->dmadev = शून्य;

	वापस 0;
पूर्ण
