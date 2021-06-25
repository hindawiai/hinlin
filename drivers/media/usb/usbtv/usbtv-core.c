<शैली गुरु>
/*
 * Copyright (c) 2013 Lubomir Rपूर्णांकel
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. The name of the author may not be used to enकरोrse or promote products
 *    derived from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL").
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * Fushicai USBTV007 Audio-Video Grabber Driver
 *
 * Product web site:
 * http://www.fushicai.com/products_detail/&productId=d05449ee-b690-42f9-a661-aa7353894bed.hपंचांगl
 *
 * Following LWN articles were very useful in स्थिरruction of this driver:
 * Video4Linux2 API series: http://lwn.net/Articles/203924/
 * videobuf2 API explanation: http://lwn.net/Articles/447435/
 * Thanks go to Jonathan Corbet क्रम providing this quality करोcumentation.
 * He is awesome.
 *
 * No physical hardware was harmed running Winकरोws during the
 * reverse-engineering activity
 */

#समावेश "usbtv.h"

पूर्णांक usbtv_set_regs(काष्ठा usbtv *usbtv, स्थिर u16 regs[][2], पूर्णांक size)
अणु
	पूर्णांक ret;
	पूर्णांक pipe = usb_rcvctrlpipe(usbtv->udev, 0);
	पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		u16 index = regs[i][0];
		u16 value = regs[i][1];

		ret = usb_control_msg(usbtv->udev, pipe, USBTV_REQUEST_REG,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value, index, शून्य, 0, USB_CTRL_GET_TIMEOUT);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक usbtv_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
	स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक ret;
	पूर्णांक size;
	काष्ठा device *dev = &पूर्णांकf->dev;
	काष्ठा usbtv *usbtv;
	काष्ठा usb_host_endpoपूर्णांक *ep;

	/* Checks that the device is what we think it is. */
	अगर (पूर्णांकf->num_altsetting != 2)
		वापस -ENODEV;
	अगर (पूर्णांकf->altsetting[1].desc.bNumEndpoपूर्णांकs != 4)
		वापस -ENODEV;

	ep = &पूर्णांकf->altsetting[1].endpoपूर्णांक[0];

	/* Packet size is split पूर्णांकo 11 bits of base size and count of
	 * extra multiplies of it.*/
	size = usb_endpoपूर्णांक_maxp(&ep->desc);
	size = size * usb_endpoपूर्णांक_maxp_mult(&ep->desc);

	/* Device काष्ठाure */
	usbtv = kzalloc(माप(काष्ठा usbtv), GFP_KERNEL);
	अगर (usbtv == शून्य)
		वापस -ENOMEM;
	usbtv->dev = dev;
	usbtv->udev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकf));

	usbtv->iso_size = size;

	usb_set_पूर्णांकfdata(पूर्णांकf, usbtv);

	ret = usbtv_video_init(usbtv);
	अगर (ret < 0)
		जाओ usbtv_video_fail;

	ret = usbtv_audio_init(usbtv);
	अगर (ret < 0)
		जाओ usbtv_audio_fail;

	/* क्रम simplicity we exploit the v4l2_device reference counting */
	v4l2_device_get(&usbtv->v4l2_dev);

	dev_info(dev, "Fushicai USBTV007 Audio-Video Grabber\n");
	वापस 0;

usbtv_audio_fail:
	/* we must not मुक्त at this poपूर्णांक */
	v4l2_device_get(&usbtv->v4l2_dev);
	/* this will unकरो the v4l2_device_get() */
	usbtv_video_मुक्त(usbtv);

usbtv_video_fail:
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	usb_put_dev(usbtv->udev);
	kमुक्त(usbtv);

	वापस ret;
पूर्ण

अटल व्योम usbtv_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usbtv *usbtv = usb_get_पूर्णांकfdata(पूर्णांकf);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	अगर (!usbtv)
		वापस;

	usbtv_audio_मुक्त(usbtv);
	usbtv_video_मुक्त(usbtv);

	usb_put_dev(usbtv->udev);
	usbtv->udev = शून्य;

	/* the usbtv काष्ठाure will be deallocated when v4l2 will be
	   करोne using it */
	v4l2_device_put(&usbtv->v4l2_dev);
पूर्ण

अटल स्थिर काष्ठा usb_device_id usbtv_id_table[] = अणु
	अणु USB_DEVICE(0x1b71, 0x3002) पूर्ण,
	अणु USB_DEVICE(0x1f71, 0x3301) पूर्ण,
	अणु USB_DEVICE(0x1f71, 0x3306) पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, usbtv_id_table);

MODULE_AUTHOR("Lubomir Rintel, Federico Simoncelli");
MODULE_DESCRIPTION("Fushicai USBTV007 Audio-Video Grabber Driver");
MODULE_LICENSE("Dual BSD/GPL");

अटल काष्ठा usb_driver usbtv_usb_driver = अणु
	.name = "usbtv",
	.id_table = usbtv_id_table,
	.probe = usbtv_probe,
	.disconnect = usbtv_disconnect,
पूर्ण;

module_usb_driver(usbtv_usb_driver);
