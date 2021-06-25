<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/mutex.h>
#समावेश <linux/समयr.h>
#समावेश <linux/usb.h>

#घोषणा SIMPLE_IO_TIMEOUT	10000	/* in milliseconds */

/*-------------------------------------------------------------------------*/

अटल पूर्णांक override_alt = -1;
module_param_named(alt, override_alt, पूर्णांक, 0644);
MODULE_PARM_DESC(alt, ">= 0 to override altsetting selection");
अटल व्योम complicated_callback(काष्ठा urb *urb);

/*-------------------------------------------------------------------------*/

/* FIXME make these खुला somewhere; usbdevfs.h? */

/* Parameter क्रम usbtest driver. */
काष्ठा usbtest_param_32 अणु
	/* inमाला_दो */
	__u32		test_num;	/* 0..(TEST_CASES-1) */
	__u32		iterations;
	__u32		length;
	__u32		vary;
	__u32		sglen;

	/* outमाला_दो */
	__s32		duration_sec;
	__s32		duration_usec;
पूर्ण;

/*
 * Compat parameter to the usbtest driver.
 * This supports older user space binaries compiled with 64 bit compiler.
 */
काष्ठा usbtest_param_64 अणु
	/* inमाला_दो */
	__u32		test_num;	/* 0..(TEST_CASES-1) */
	__u32		iterations;
	__u32		length;
	__u32		vary;
	__u32		sglen;

	/* outमाला_दो */
	__s64		duration_sec;
	__s64		duration_usec;
पूर्ण;

/* IOCTL पूर्णांकerface to the driver. */
#घोषणा USBTEST_REQUEST_32    _IOWR('U', 100, काष्ठा usbtest_param_32)
/* COMPAT IOCTL पूर्णांकerface to the driver. */
#घोषणा USBTEST_REQUEST_64    _IOWR('U', 100, काष्ठा usbtest_param_64)

/*-------------------------------------------------------------------------*/

#घोषणा	GENERIC		/* let probe() bind using module params */

/* Some devices that can be used क्रम testing will have "real" drivers.
 * Entries क्रम those need to be enabled here by hand, after disabling
 * that "real" driver.
 */
//#घोषणा	IBOT2		/* grab iBOT2 webcams */
//#घोषणा	KEYSPAN_19Qi	/* grab un-rक्रमागतerated serial adapter */

/*-------------------------------------------------------------------------*/

काष्ठा usbtest_info अणु
	स्थिर अक्षर		*name;
	u8			ep_in;		/* bulk/पूर्णांकr source */
	u8			ep_out;		/* bulk/पूर्णांकr sink */
	अचिन्हित		स्वतःconf:1;
	अचिन्हित		ctrl_out:1;
	अचिन्हित		iso:1;		/* try iso in/out */
	अचिन्हित		पूर्णांकr:1;		/* try पूर्णांकerrupt in/out */
	पूर्णांक			alt;
पूर्ण;

/* this is accessed only through usbfs ioctl calls.
 * one ioctl to issue a test ... one lock per device.
 * tests create other thपढ़ोs अगर they need them.
 * urbs and buffers are allocated dynamically,
 * and data generated deterministically.
 */
काष्ठा usbtest_dev अणु
	काष्ठा usb_पूर्णांकerface	*पूर्णांकf;
	काष्ठा usbtest_info	*info;
	पूर्णांक			in_pipe;
	पूर्णांक			out_pipe;
	पूर्णांक			in_iso_pipe;
	पूर्णांक			out_iso_pipe;
	पूर्णांक			in_पूर्णांक_pipe;
	पूर्णांक			out_पूर्णांक_pipe;
	काष्ठा usb_endpoपूर्णांक_descriptor	*iso_in, *iso_out;
	काष्ठा usb_endpoपूर्णांक_descriptor	*पूर्णांक_in, *पूर्णांक_out;
	काष्ठा mutex		lock;

#घोषणा TBUF_SIZE	256
	u8			*buf;
पूर्ण;

अटल काष्ठा usb_device *testdev_to_usbdev(काष्ठा usbtest_dev *test)
अणु
	वापस पूर्णांकerface_to_usbdev(test->पूर्णांकf);
पूर्ण

/* set up all urbs so they can be used with either bulk or पूर्णांकerrupt */
#घोषणा	INTERRUPT_RATE		1	/* msec/transfer */

#घोषणा ERROR(tdev, fmt, args...) \
	dev_err(&(tdev)->पूर्णांकf->dev , fmt , ## args)
#घोषणा WARNING(tdev, fmt, args...) \
	dev_warn(&(tdev)->पूर्णांकf->dev , fmt , ## args)

#घोषणा GUARD_BYTE	0xA5
#घोषणा MAX_SGLEN	128

/*-------------------------------------------------------------------------*/

अटल अंतरभूत व्योम endpoपूर्णांक_update(पूर्णांक edi,
				   काष्ठा usb_host_endpoपूर्णांक **in,
				   काष्ठा usb_host_endpoपूर्णांक **out,
				   काष्ठा usb_host_endpoपूर्णांक *e)
अणु
	अगर (edi) अणु
		अगर (!*in)
			*in = e;
	पूर्ण अन्यथा अणु
		अगर (!*out)
			*out = e;
	पूर्ण
पूर्ण

अटल पूर्णांक
get_endpoपूर्णांकs(काष्ठा usbtest_dev *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक				पंचांगp;
	काष्ठा usb_host_पूर्णांकerface	*alt;
	काष्ठा usb_host_endpoपूर्णांक	*in, *out;
	काष्ठा usb_host_endpoपूर्णांक	*iso_in, *iso_out;
	काष्ठा usb_host_endpoपूर्णांक	*पूर्णांक_in, *पूर्णांक_out;
	काष्ठा usb_device		*udev;

	क्रम (पंचांगp = 0; पंचांगp < पूर्णांकf->num_altsetting; पंचांगp++) अणु
		अचिन्हित	ep;

		in = out = शून्य;
		iso_in = iso_out = शून्य;
		पूर्णांक_in = पूर्णांक_out = शून्य;
		alt = पूर्णांकf->altsetting + पंचांगp;

		अगर (override_alt >= 0 &&
				override_alt != alt->desc.bAlternateSetting)
			जारी;

		/* take the first altsetting with in-bulk + out-bulk;
		 * ignore other endpoपूर्णांकs and altsettings.
		 */
		क्रम (ep = 0; ep < alt->desc.bNumEndpoपूर्णांकs; ep++) अणु
			काष्ठा usb_host_endpoपूर्णांक	*e;
			पूर्णांक edi;

			e = alt->endpoपूर्णांक + ep;
			edi = usb_endpoपूर्णांक_dir_in(&e->desc);

			चयन (usb_endpoपूर्णांक_type(&e->desc)) अणु
			हाल USB_ENDPOINT_XFER_BULK:
				endpoपूर्णांक_update(edi, &in, &out, e);
				जारी;
			हाल USB_ENDPOINT_XFER_INT:
				अगर (dev->info->पूर्णांकr)
					endpoपूर्णांक_update(edi, &पूर्णांक_in, &पूर्णांक_out, e);
				जारी;
			हाल USB_ENDPOINT_XFER_ISOC:
				अगर (dev->info->iso)
					endpoपूर्णांक_update(edi, &iso_in, &iso_out, e);
				fallthrough;
			शेष:
				जारी;
			पूर्ण
		पूर्ण
		अगर ((in && out)  ||  iso_in || iso_out || पूर्णांक_in || पूर्णांक_out)
			जाओ found;
	पूर्ण
	वापस -EINVAL;

found:
	udev = testdev_to_usbdev(dev);
	dev->info->alt = alt->desc.bAlternateSetting;
	अगर (alt->desc.bAlternateSetting != 0) अणु
		पंचांगp = usb_set_पूर्णांकerface(udev,
				alt->desc.bInterfaceNumber,
				alt->desc.bAlternateSetting);
		अगर (पंचांगp < 0)
			वापस पंचांगp;
	पूर्ण

	अगर (in)
		dev->in_pipe = usb_rcvbulkpipe(udev,
			in->desc.bEndpoपूर्णांकAddress & USB_ENDPOINT_NUMBER_MASK);
	अगर (out)
		dev->out_pipe = usb_sndbulkpipe(udev,
			out->desc.bEndpoपूर्णांकAddress & USB_ENDPOINT_NUMBER_MASK);

	अगर (iso_in) अणु
		dev->iso_in = &iso_in->desc;
		dev->in_iso_pipe = usb_rcvisocpipe(udev,
				iso_in->desc.bEndpoपूर्णांकAddress
					& USB_ENDPOINT_NUMBER_MASK);
	पूर्ण

	अगर (iso_out) अणु
		dev->iso_out = &iso_out->desc;
		dev->out_iso_pipe = usb_sndisocpipe(udev,
				iso_out->desc.bEndpoपूर्णांकAddress
					& USB_ENDPOINT_NUMBER_MASK);
	पूर्ण

	अगर (पूर्णांक_in) अणु
		dev->पूर्णांक_in = &पूर्णांक_in->desc;
		dev->in_पूर्णांक_pipe = usb_rcvपूर्णांकpipe(udev,
				पूर्णांक_in->desc.bEndpoपूर्णांकAddress
					& USB_ENDPOINT_NUMBER_MASK);
	पूर्ण

	अगर (पूर्णांक_out) अणु
		dev->पूर्णांक_out = &पूर्णांक_out->desc;
		dev->out_पूर्णांक_pipe = usb_sndपूर्णांकpipe(udev,
				पूर्णांक_out->desc.bEndpoपूर्णांकAddress
					& USB_ENDPOINT_NUMBER_MASK);
	पूर्ण
	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

/* Support क्रम testing basic non-queued I/O streams.
 *
 * These just package urbs as requests that can be easily canceled.
 * Each urb's data buffer is dynamically allocated; callers can fill
 * them with non-zero test data (or test क्रम it) when appropriate.
 */

अटल व्योम simple_callback(काष्ठा urb *urb)
अणु
	complete(urb->context);
पूर्ण

अटल काष्ठा urb *usbtest_alloc_urb(
	काष्ठा usb_device	*udev,
	पूर्णांक			pipe,
	अचिन्हित दीर्घ		bytes,
	अचिन्हित		transfer_flags,
	अचिन्हित		offset,
	u8			bInterval,
	usb_complete_t		complete_fn)
अणु
	काष्ठा urb		*urb;

	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!urb)
		वापस urb;

	अगर (bInterval)
		usb_fill_पूर्णांक_urb(urb, udev, pipe, शून्य, bytes, complete_fn,
				शून्य, bInterval);
	अन्यथा
		usb_fill_bulk_urb(urb, udev, pipe, शून्य, bytes, complete_fn,
				शून्य);

	urb->पूर्णांकerval = (udev->speed == USB_SPEED_HIGH)
			? (INTERRUPT_RATE << 3)
			: INTERRUPT_RATE;
	urb->transfer_flags = transfer_flags;
	अगर (usb_pipein(pipe))
		urb->transfer_flags |= URB_SHORT_NOT_OK;

	अगर ((bytes + offset) == 0)
		वापस urb;

	अगर (urb->transfer_flags & URB_NO_TRANSFER_DMA_MAP)
		urb->transfer_buffer = usb_alloc_coherent(udev, bytes + offset,
			GFP_KERNEL, &urb->transfer_dma);
	अन्यथा
		urb->transfer_buffer = kदो_स्मृति(bytes + offset, GFP_KERNEL);

	अगर (!urb->transfer_buffer) अणु
		usb_मुक्त_urb(urb);
		वापस शून्य;
	पूर्ण

	/* To test unaligned transfers add an offset and fill the
		unused memory with a guard value */
	अगर (offset) अणु
		स_रखो(urb->transfer_buffer, GUARD_BYTE, offset);
		urb->transfer_buffer += offset;
		अगर (urb->transfer_flags & URB_NO_TRANSFER_DMA_MAP)
			urb->transfer_dma += offset;
	पूर्ण

	/* For inbound transfers use guard byte so that test fails अगर
		data not correctly copied */
	स_रखो(urb->transfer_buffer,
			usb_pipein(urb->pipe) ? GUARD_BYTE : 0,
			bytes);
	वापस urb;
पूर्ण

अटल काष्ठा urb *simple_alloc_urb(
	काष्ठा usb_device	*udev,
	पूर्णांक			pipe,
	अचिन्हित दीर्घ		bytes,
	u8			bInterval)
अणु
	वापस usbtest_alloc_urb(udev, pipe, bytes, URB_NO_TRANSFER_DMA_MAP, 0,
			bInterval, simple_callback);
पूर्ण

अटल काष्ठा urb *complicated_alloc_urb(
	काष्ठा usb_device	*udev,
	पूर्णांक			pipe,
	अचिन्हित दीर्घ		bytes,
	u8			bInterval)
अणु
	वापस usbtest_alloc_urb(udev, pipe, bytes, URB_NO_TRANSFER_DMA_MAP, 0,
			bInterval, complicated_callback);
पूर्ण

अटल अचिन्हित pattern;
अटल अचिन्हित mod_pattern;
module_param_named(pattern, mod_pattern, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(mod_pattern, "i/o pattern (0 == zeroes)");

अटल अचिन्हित get_maxpacket(काष्ठा usb_device *udev, पूर्णांक pipe)
अणु
	काष्ठा usb_host_endpoपूर्णांक	*ep;

	ep = usb_pipe_endpoपूर्णांक(udev, pipe);
	वापस le16_to_cpup(&ep->desc.wMaxPacketSize);
पूर्ण

अटल पूर्णांक ss_isoc_get_packet_num(काष्ठा usb_device *udev, पूर्णांक pipe)
अणु
	काष्ठा usb_host_endpoपूर्णांक *ep = usb_pipe_endpoपूर्णांक(udev, pipe);

	वापस USB_SS_MULT(ep->ss_ep_comp.bmAttributes)
		* (1 + ep->ss_ep_comp.bMaxBurst);
पूर्ण

अटल व्योम simple_fill_buf(काष्ठा urb *urb)
अणु
	अचिन्हित	i;
	u8		*buf = urb->transfer_buffer;
	अचिन्हित	len = urb->transfer_buffer_length;
	अचिन्हित	maxpacket;

	चयन (pattern) अणु
	शेष:
		fallthrough;
	हाल 0:
		स_रखो(buf, 0, len);
		अवरोध;
	हाल 1:			/* mod63 */
		maxpacket = get_maxpacket(urb->dev, urb->pipe);
		क्रम (i = 0; i < len; i++)
			*buf++ = (u8) ((i % maxpacket) % 63);
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ buffer_offset(व्योम *buf)
अणु
	वापस (अचिन्हित दीर्घ)buf & (ARCH_KMALLOC_MINALIGN - 1);
पूर्ण

अटल पूर्णांक check_guard_bytes(काष्ठा usbtest_dev *tdev, काष्ठा urb *urb)
अणु
	u8 *buf = urb->transfer_buffer;
	u8 *guard = buf - buffer_offset(buf);
	अचिन्हित i;

	क्रम (i = 0; guard < buf; i++, guard++) अणु
		अगर (*guard != GUARD_BYTE) अणु
			ERROR(tdev, "guard byte[%d] %d (not %d)\n",
				i, *guard, GUARD_BYTE);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक simple_check_buf(काष्ठा usbtest_dev *tdev, काष्ठा urb *urb)
अणु
	अचिन्हित	i;
	u8		expected;
	u8		*buf = urb->transfer_buffer;
	अचिन्हित	len = urb->actual_length;
	अचिन्हित	maxpacket = get_maxpacket(urb->dev, urb->pipe);

	पूर्णांक ret = check_guard_bytes(tdev, urb);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < len; i++, buf++) अणु
		चयन (pattern) अणु
		/* all-zeroes has no synchronization issues */
		हाल 0:
			expected = 0;
			अवरोध;
		/* mod63 stays in sync with लघु-terminated transfers,
		 * or otherwise when host and gadget agree on how large
		 * each usb transfer request should be.  resync is करोne
		 * with set_पूर्णांकerface or set_config.
		 */
		हाल 1:			/* mod63 */
			expected = (i % maxpacket) % 63;
			अवरोध;
		/* always fail unsupported patterns */
		शेष:
			expected = !*buf;
			अवरोध;
		पूर्ण
		अगर (*buf == expected)
			जारी;
		ERROR(tdev, "buf[%d] = %d (not %d)\n", i, *buf, expected);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम simple_मुक्त_urb(काष्ठा urb *urb)
अणु
	अचिन्हित दीर्घ offset = buffer_offset(urb->transfer_buffer);

	अगर (urb->transfer_flags & URB_NO_TRANSFER_DMA_MAP)
		usb_मुक्त_coherent(
			urb->dev,
			urb->transfer_buffer_length + offset,
			urb->transfer_buffer - offset,
			urb->transfer_dma - offset);
	अन्यथा
		kमुक्त(urb->transfer_buffer - offset);
	usb_मुक्त_urb(urb);
पूर्ण

अटल पूर्णांक simple_io(
	काष्ठा usbtest_dev	*tdev,
	काष्ठा urb		*urb,
	पूर्णांक			iterations,
	पूर्णांक			vary,
	पूर्णांक			expected,
	स्थिर अक्षर		*label
)
अणु
	काष्ठा usb_device	*udev = urb->dev;
	पूर्णांक			max = urb->transfer_buffer_length;
	काष्ठा completion	completion;
	पूर्णांक			retval = 0;
	अचिन्हित दीर्घ		expire;

	urb->context = &completion;
	जबतक (retval == 0 && iterations-- > 0) अणु
		init_completion(&completion);
		अगर (usb_pipeout(urb->pipe)) अणु
			simple_fill_buf(urb);
			urb->transfer_flags |= URB_ZERO_PACKET;
		पूर्ण
		retval = usb_submit_urb(urb, GFP_KERNEL);
		अगर (retval != 0)
			अवरोध;

		expire = msecs_to_jअगरfies(SIMPLE_IO_TIMEOUT);
		अगर (!रुको_क्रम_completion_समयout(&completion, expire)) अणु
			usb_समाप्त_urb(urb);
			retval = (urb->status == -ENOENT ?
				  -ETIMEDOUT : urb->status);
		पूर्ण अन्यथा अणु
			retval = urb->status;
		पूर्ण

		urb->dev = udev;
		अगर (retval == 0 && usb_pipein(urb->pipe))
			retval = simple_check_buf(tdev, urb);

		अगर (vary) अणु
			पूर्णांक	len = urb->transfer_buffer_length;

			len += vary;
			len %= max;
			अगर (len == 0)
				len = (vary < max) ? vary : max;
			urb->transfer_buffer_length = len;
		पूर्ण

		/* FIXME अगर endpoपूर्णांक halted, clear halt (and log) */
	पूर्ण
	urb->transfer_buffer_length = max;

	अगर (expected != retval)
		dev_err(&udev->dev,
			"%s failed, iterations left %d, status %d (not %d)\n",
				label, iterations, retval, expected);
	वापस retval;
पूर्ण


/*-------------------------------------------------------------------------*/

/* We use scatterlist primitives to test queued I/O.
 * Yes, this also tests the scatterlist primitives.
 */

अटल व्योम मुक्त_sglist(काष्ठा scatterlist *sg, पूर्णांक nents)
अणु
	अचिन्हित		i;

	अगर (!sg)
		वापस;
	क्रम (i = 0; i < nents; i++) अणु
		अगर (!sg_page(&sg[i]))
			जारी;
		kमुक्त(sg_virt(&sg[i]));
	पूर्ण
	kमुक्त(sg);
पूर्ण

अटल काष्ठा scatterlist *
alloc_sglist(पूर्णांक nents, पूर्णांक max, पूर्णांक vary, काष्ठा usbtest_dev *dev, पूर्णांक pipe)
अणु
	काष्ठा scatterlist	*sg;
	अचिन्हित पूर्णांक		n_size = 0;
	अचिन्हित		i;
	अचिन्हित		size = max;
	अचिन्हित		maxpacket =
		get_maxpacket(पूर्णांकerface_to_usbdev(dev->पूर्णांकf), pipe);

	अगर (max == 0)
		वापस शून्य;

	sg = kदो_स्मृति_array(nents, माप(*sg), GFP_KERNEL);
	अगर (!sg)
		वापस शून्य;
	sg_init_table(sg, nents);

	क्रम (i = 0; i < nents; i++) अणु
		अक्षर		*buf;
		अचिन्हित	j;

		buf = kzalloc(size, GFP_KERNEL);
		अगर (!buf) अणु
			मुक्त_sglist(sg, i);
			वापस शून्य;
		पूर्ण

		/* kदो_स्मृति pages are always physically contiguous! */
		sg_set_buf(&sg[i], buf, size);

		चयन (pattern) अणु
		हाल 0:
			/* alपढ़ोy zeroed */
			अवरोध;
		हाल 1:
			क्रम (j = 0; j < size; j++)
				*buf++ = (u8) (((j + n_size) % maxpacket) % 63);
			n_size += size;
			अवरोध;
		पूर्ण

		अगर (vary) अणु
			size += vary;
			size %= max;
			अगर (size == 0)
				size = (vary < max) ? vary : max;
		पूर्ण
	पूर्ण

	वापस sg;
पूर्ण

काष्ठा sg_समयout अणु
	काष्ठा समयr_list समयr;
	काष्ठा usb_sg_request *req;
पूर्ण;

अटल व्योम sg_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा sg_समयout *समयout = from_समयr(समयout, t, समयr);

	usb_sg_cancel(समयout->req);
पूर्ण

अटल पूर्णांक perक्रमm_sglist(
	काष्ठा usbtest_dev	*tdev,
	अचिन्हित		iterations,
	पूर्णांक			pipe,
	काष्ठा usb_sg_request	*req,
	काष्ठा scatterlist	*sg,
	पूर्णांक			nents
)
अणु
	काष्ठा usb_device	*udev = testdev_to_usbdev(tdev);
	पूर्णांक			retval = 0;
	काष्ठा sg_समयout	समयout = अणु
		.req = req,
	पूर्ण;

	समयr_setup_on_stack(&समयout.समयr, sg_समयout, 0);

	जबतक (retval == 0 && iterations-- > 0) अणु
		retval = usb_sg_init(req, udev, pipe,
				(udev->speed == USB_SPEED_HIGH)
					? (INTERRUPT_RATE << 3)
					: INTERRUPT_RATE,
				sg, nents, 0, GFP_KERNEL);

		अगर (retval)
			अवरोध;
		mod_समयr(&समयout.समयr, jअगरfies +
				msecs_to_jअगरfies(SIMPLE_IO_TIMEOUT));
		usb_sg_रुको(req);
		अगर (!del_समयr_sync(&समयout.समयr))
			retval = -ETIMEDOUT;
		अन्यथा
			retval = req->status;
		destroy_समयr_on_stack(&समयout.समयr);

		/* FIXME check resulting data pattern */

		/* FIXME अगर endpoपूर्णांक halted, clear halt (and log) */
	पूर्ण

	/* FIXME क्रम unlink or fault handling tests, करोn't report
	 * failure अगर retval is as we expected ...
	 */
	अगर (retval)
		ERROR(tdev, "perform_sglist failed, "
				"iterations left %d, status %d\n",
				iterations, retval);
	वापस retval;
पूर्ण


/*-------------------------------------------------------------------------*/

/* unqueued control message testing
 *
 * there's a nice set of device functional requirements in chapter 9 of the
 * usb 2.0 spec, which we can apply to ANY device, even ones that करोn't use
 * special test firmware.
 *
 * we know the device is configured (or suspended) by the समय it's visible
 * through usbfs.  we can't change that, so we won't test क्रमागतeration (which
 * worked 'well enough' to get here, this समय), घातer management (ditto),
 * or remote wakeup (which needs human पूर्णांकeraction).
 */

अटल अचिन्हित realworld = 1;
module_param(realworld, uपूर्णांक, 0);
MODULE_PARM_DESC(realworld, "clear to demand stricter spec compliance");

अटल पूर्णांक get_altsetting(काष्ठा usbtest_dev *dev)
अणु
	काष्ठा usb_पूर्णांकerface	*अगरace = dev->पूर्णांकf;
	काष्ठा usb_device	*udev = पूर्णांकerface_to_usbdev(अगरace);
	पूर्णांक			retval;

	retval = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
			USB_REQ_GET_INTERFACE, USB_सूची_IN|USB_RECIP_INTERFACE,
			0, अगरace->altsetting[0].desc.bInterfaceNumber,
			dev->buf, 1, USB_CTRL_GET_TIMEOUT);
	चयन (retval) अणु
	हाल 1:
		वापस dev->buf[0];
	हाल 0:
		retval = -दुस्फल;
		fallthrough;
	शेष:
		वापस retval;
	पूर्ण
पूर्ण

अटल पूर्णांक set_altsetting(काष्ठा usbtest_dev *dev, पूर्णांक alternate)
अणु
	काष्ठा usb_पूर्णांकerface		*अगरace = dev->पूर्णांकf;
	काष्ठा usb_device		*udev;

	अगर (alternate < 0 || alternate >= 256)
		वापस -EINVAL;

	udev = पूर्णांकerface_to_usbdev(अगरace);
	वापस usb_set_पूर्णांकerface(udev,
			अगरace->altsetting[0].desc.bInterfaceNumber,
			alternate);
पूर्ण

अटल पूर्णांक is_good_config(काष्ठा usbtest_dev *tdev, पूर्णांक len)
अणु
	काष्ठा usb_config_descriptor	*config;

	अगर (len < माप(*config))
		वापस 0;
	config = (काष्ठा usb_config_descriptor *) tdev->buf;

	चयन (config->bDescriptorType) अणु
	हाल USB_DT_CONFIG:
	हाल USB_DT_OTHER_SPEED_CONFIG:
		अगर (config->bLength != 9) अणु
			ERROR(tdev, "bogus config descriptor length\n");
			वापस 0;
		पूर्ण
		/* this bit 'must be 1' but often isn't */
		अगर (!realworld && !(config->bmAttributes & 0x80)) अणु
			ERROR(tdev, "high bit of config attributes not set\n");
			वापस 0;
		पूर्ण
		अगर (config->bmAttributes & 0x1f) अणु	/* reserved == 0 */
			ERROR(tdev, "reserved config bits set\n");
			वापस 0;
		पूर्ण
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (le16_to_cpu(config->wTotalLength) == len)	/* पढ़ो it all */
		वापस 1;
	अगर (le16_to_cpu(config->wTotalLength) >= TBUF_SIZE)	/* max partial पढ़ो */
		वापस 1;
	ERROR(tdev, "bogus config descriptor read size\n");
	वापस 0;
पूर्ण

अटल पूर्णांक is_good_ext(काष्ठा usbtest_dev *tdev, u8 *buf)
अणु
	काष्ठा usb_ext_cap_descriptor *ext;
	u32 attr;

	ext = (काष्ठा usb_ext_cap_descriptor *) buf;

	अगर (ext->bLength != USB_DT_USB_EXT_CAP_SIZE) अणु
		ERROR(tdev, "bogus usb 2.0 extension descriptor length\n");
		वापस 0;
	पूर्ण

	attr = le32_to_cpu(ext->bmAttributes);
	/* bits[1:15] is used and others are reserved */
	अगर (attr & ~0xfffe) अणु	/* reserved == 0 */
		ERROR(tdev, "reserved bits set\n");
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक is_good_ss_cap(काष्ठा usbtest_dev *tdev, u8 *buf)
अणु
	काष्ठा usb_ss_cap_descriptor *ss;

	ss = (काष्ठा usb_ss_cap_descriptor *) buf;

	अगर (ss->bLength != USB_DT_USB_SS_CAP_SIZE) अणु
		ERROR(tdev, "bogus superspeed device capability descriptor length\n");
		वापस 0;
	पूर्ण

	/*
	 * only bit[1] of bmAttributes is used क्रम LTM and others are
	 * reserved
	 */
	अगर (ss->bmAttributes & ~0x02) अणु	/* reserved == 0 */
		ERROR(tdev, "reserved bits set in bmAttributes\n");
		वापस 0;
	पूर्ण

	/* bits[0:3] of wSpeedSupported is used and others are reserved */
	अगर (le16_to_cpu(ss->wSpeedSupported) & ~0x0f) अणु	/* reserved == 0 */
		ERROR(tdev, "reserved bits set in wSpeedSupported\n");
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक is_good_con_id(काष्ठा usbtest_dev *tdev, u8 *buf)
अणु
	काष्ठा usb_ss_container_id_descriptor *con_id;

	con_id = (काष्ठा usb_ss_container_id_descriptor *) buf;

	अगर (con_id->bLength != USB_DT_USB_SS_CONTN_ID_SIZE) अणु
		ERROR(tdev, "bogus container id descriptor length\n");
		वापस 0;
	पूर्ण

	अगर (con_id->bReserved) अणु	/* reserved == 0 */
		ERROR(tdev, "reserved bits set\n");
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/* sanity test क्रम standard requests working with usb_control_mesg() and some
 * of the utility functions which use it.
 *
 * this करोesn't test how endpoपूर्णांक halts behave or data toggles get set, since
 * we won't करो I/O to bulk/पूर्णांकerrupt endpoपूर्णांकs here (which is how to change
 * halt or toggle).  toggle testing is impractical without support from hcds.
 *
 * this aव्योमs failing devices linux would normally work with, by not testing
 * config/altsetting operations क्रम devices that only support their शेषs.
 * such devices rarely support those needless operations.
 *
 * NOTE that since this is a sanity test, it's not examining boundary हालs
 * to see अगर usbcore, hcd, and device all behave right.  such testing would
 * involve varied पढ़ो sizes and other operation sequences.
 */
अटल पूर्णांक ch9_postconfig(काष्ठा usbtest_dev *dev)
अणु
	काष्ठा usb_पूर्णांकerface	*अगरace = dev->पूर्णांकf;
	काष्ठा usb_device	*udev = पूर्णांकerface_to_usbdev(अगरace);
	पूर्णांक			i, alt, retval;

	/* [9.2.3] अगर there's more than one altsetting, we need to be able to
	 * set and get each one.  mostly trusts the descriptors from usbcore.
	 */
	क्रम (i = 0; i < अगरace->num_altsetting; i++) अणु

		/* 9.2.3 स्थिरrains the range here */
		alt = अगरace->altsetting[i].desc.bAlternateSetting;
		अगर (alt < 0 || alt >= अगरace->num_altsetting) अणु
			dev_err(&अगरace->dev,
					"invalid alt [%d].bAltSetting = %d\n",
					i, alt);
		पूर्ण

		/* [real world] get/set unimplemented अगर there's only one */
		अगर (realworld && अगरace->num_altsetting == 1)
			जारी;

		/* [9.4.10] set_पूर्णांकerface */
		retval = set_altsetting(dev, alt);
		अगर (retval) अणु
			dev_err(&अगरace->dev, "can't set_interface = %d, %d\n",
					alt, retval);
			वापस retval;
		पूर्ण

		/* [9.4.4] get_पूर्णांकerface always works */
		retval = get_altsetting(dev);
		अगर (retval != alt) अणु
			dev_err(&अगरace->dev, "get alt should be %d, was %d\n",
					alt, retval);
			वापस (retval < 0) ? retval : -गलत_तर्क;
		पूर्ण

	पूर्ण

	/* [real world] get_config unimplemented अगर there's only one */
	अगर (!realworld || udev->descriptor.bNumConfigurations != 1) अणु
		पूर्णांक	expected = udev->actconfig->desc.bConfigurationValue;

		/* [9.4.2] get_configuration always works
		 * ... although some cheap devices (like one TI Hub I've got)
		 * won't वापस config descriptors except beक्रमe set_config.
		 */
		retval = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
				USB_REQ_GET_CONFIGURATION,
				USB_सूची_IN | USB_RECIP_DEVICE,
				0, 0, dev->buf, 1, USB_CTRL_GET_TIMEOUT);
		अगर (retval != 1 || dev->buf[0] != expected) अणु
			dev_err(&अगरace->dev, "get config --> %d %d (1 %d)\n",
				retval, dev->buf[0], expected);
			वापस (retval < 0) ? retval : -गलत_तर्क;
		पूर्ण
	पूर्ण

	/* there's always [9.4.3] a device descriptor [9.6.1] */
	retval = usb_get_descriptor(udev, USB_DT_DEVICE, 0,
			dev->buf, माप(udev->descriptor));
	अगर (retval != माप(udev->descriptor)) अणु
		dev_err(&अगरace->dev, "dev descriptor --> %d\n", retval);
		वापस (retval < 0) ? retval : -गलत_तर्क;
	पूर्ण

	/*
	 * there's always [9.4.3] a bos device descriptor [9.6.2] in USB
	 * 3.0 spec
	 */
	अगर (le16_to_cpu(udev->descriptor.bcdUSB) >= 0x0210) अणु
		काष्ठा usb_bos_descriptor *bos = शून्य;
		काष्ठा usb_dev_cap_header *header = शून्य;
		अचिन्हित total, num, length;
		u8 *buf;

		retval = usb_get_descriptor(udev, USB_DT_BOS, 0, dev->buf,
				माप(*udev->bos->desc));
		अगर (retval != माप(*udev->bos->desc)) अणु
			dev_err(&अगरace->dev, "bos descriptor --> %d\n", retval);
			वापस (retval < 0) ? retval : -गलत_तर्क;
		पूर्ण

		bos = (काष्ठा usb_bos_descriptor *)dev->buf;
		total = le16_to_cpu(bos->wTotalLength);
		num = bos->bNumDeviceCaps;

		अगर (total > TBUF_SIZE)
			total = TBUF_SIZE;

		/*
		 * get generic device-level capability descriptors [9.6.2]
		 * in USB 3.0 spec
		 */
		retval = usb_get_descriptor(udev, USB_DT_BOS, 0, dev->buf,
				total);
		अगर (retval != total) अणु
			dev_err(&अगरace->dev, "bos descriptor set --> %d\n",
					retval);
			वापस (retval < 0) ? retval : -गलत_तर्क;
		पूर्ण

		length = माप(*udev->bos->desc);
		buf = dev->buf;
		क्रम (i = 0; i < num; i++) अणु
			buf += length;
			अगर (buf + माप(काष्ठा usb_dev_cap_header) >
					dev->buf + total)
				अवरोध;

			header = (काष्ठा usb_dev_cap_header *)buf;
			length = header->bLength;

			अगर (header->bDescriptorType !=
					USB_DT_DEVICE_CAPABILITY) अणु
				dev_warn(&udev->dev, "not device capability descriptor, skip\n");
				जारी;
			पूर्ण

			चयन (header->bDevCapabilityType) अणु
			हाल USB_CAP_TYPE_EXT:
				अगर (buf + USB_DT_USB_EXT_CAP_SIZE >
						dev->buf + total ||
						!is_good_ext(dev, buf)) अणु
					dev_err(&अगरace->dev, "bogus usb 2.0 extension descriptor\n");
					वापस -गलत_तर्क;
				पूर्ण
				अवरोध;
			हाल USB_SS_CAP_TYPE:
				अगर (buf + USB_DT_USB_SS_CAP_SIZE >
						dev->buf + total ||
						!is_good_ss_cap(dev, buf)) अणु
					dev_err(&अगरace->dev, "bogus superspeed device capability descriptor\n");
					वापस -गलत_तर्क;
				पूर्ण
				अवरोध;
			हाल CONTAINER_ID_TYPE:
				अगर (buf + USB_DT_USB_SS_CONTN_ID_SIZE >
						dev->buf + total ||
						!is_good_con_id(dev, buf)) अणु
					dev_err(&अगरace->dev, "bogus container id descriptor\n");
					वापस -गलत_तर्क;
				पूर्ण
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* there's always [9.4.3] at least one config descriptor [9.6.3] */
	क्रम (i = 0; i < udev->descriptor.bNumConfigurations; i++) अणु
		retval = usb_get_descriptor(udev, USB_DT_CONFIG, i,
				dev->buf, TBUF_SIZE);
		अगर (!is_good_config(dev, retval)) अणु
			dev_err(&अगरace->dev,
					"config [%d] descriptor --> %d\n",
					i, retval);
			वापस (retval < 0) ? retval : -गलत_तर्क;
		पूर्ण

		/* FIXME cross-checking udev->config[i] to make sure usbcore
		 * parsed it right (etc) would be good testing paranoia
		 */
	पूर्ण

	/* and someबार [9.2.6.6] speed dependent descriptors */
	अगर (le16_to_cpu(udev->descriptor.bcdUSB) == 0x0200) अणु
		काष्ठा usb_qualअगरier_descriptor *d = शून्य;

		/* device qualअगरier [9.6.2] */
		retval = usb_get_descriptor(udev,
				USB_DT_DEVICE_QUALIFIER, 0, dev->buf,
				माप(काष्ठा usb_qualअगरier_descriptor));
		अगर (retval == -EPIPE) अणु
			अगर (udev->speed == USB_SPEED_HIGH) अणु
				dev_err(&अगरace->dev,
						"hs dev qualifier --> %d\n",
						retval);
				वापस retval;
			पूर्ण
			/* usb2.0 but not high-speed capable; fine */
		पूर्ण अन्यथा अगर (retval != माप(काष्ठा usb_qualअगरier_descriptor)) अणु
			dev_err(&अगरace->dev, "dev qualifier --> %d\n", retval);
			वापस (retval < 0) ? retval : -गलत_तर्क;
		पूर्ण अन्यथा
			d = (काष्ठा usb_qualअगरier_descriptor *) dev->buf;

		/* might not have [9.6.2] any other-speed configs [9.6.4] */
		अगर (d) अणु
			अचिन्हित max = d->bNumConfigurations;
			क्रम (i = 0; i < max; i++) अणु
				retval = usb_get_descriptor(udev,
					USB_DT_OTHER_SPEED_CONFIG, i,
					dev->buf, TBUF_SIZE);
				अगर (!is_good_config(dev, retval)) अणु
					dev_err(&अगरace->dev,
						"other speed config --> %d\n",
						retval);
					वापस (retval < 0) ? retval : -गलत_तर्क;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	/* FIXME fetch strings from at least the device descriptor */

	/* [9.4.5] get_status always works */
	retval = usb_get_std_status(udev, USB_RECIP_DEVICE, 0, dev->buf);
	अगर (retval) अणु
		dev_err(&अगरace->dev, "get dev status --> %d\n", retval);
		वापस retval;
	पूर्ण

	/* FIXME configuration.bmAttributes says अगर we could try to set/clear
	 * the device's remote wakeup feature ... अगर we can, test that here
	 */

	retval = usb_get_std_status(udev, USB_RECIP_INTERFACE,
			अगरace->altsetting[0].desc.bInterfaceNumber, dev->buf);
	अगर (retval) अणु
		dev_err(&अगरace->dev, "get interface status --> %d\n", retval);
		वापस retval;
	पूर्ण
	/* FIXME get status क्रम each endpoपूर्णांक in the पूर्णांकerface */

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

/* use ch9 requests to test whether:
 *   (a) queues work क्रम control, keeping N subtests queued and
 *       active (स्वतः-resubmit) क्रम M loops through the queue.
 *   (b) protocol stalls (control-only) will स्वतःrecover.
 *       it's not like bulk/पूर्णांकr; no halt clearing.
 *   (c) लघु control पढ़ोs are reported and handled.
 *   (d) queues are always processed in-order
 */

काष्ठा ctrl_ctx अणु
	spinlock_t		lock;
	काष्ठा usbtest_dev	*dev;
	काष्ठा completion	complete;
	अचिन्हित		count;
	अचिन्हित		pending;
	पूर्णांक			status;
	काष्ठा urb		**urb;
	काष्ठा usbtest_param_32	*param;
	पूर्णांक			last;
पूर्ण;

#घोषणा NUM_SUBCASES	16		/* how many test subहालs here? */

काष्ठा subहाल अणु
	काष्ठा usb_ctrlrequest	setup;
	पूर्णांक			number;
	पूर्णांक			expected;
पूर्ण;

अटल व्योम ctrl_complete(काष्ठा urb *urb)
अणु
	काष्ठा ctrl_ctx		*ctx = urb->context;
	काष्ठा usb_ctrlrequest	*reqp;
	काष्ठा subहाल		*subहाल;
	पूर्णांक			status = urb->status;
	अचिन्हित दीर्घ		flags;

	reqp = (काष्ठा usb_ctrlrequest *)urb->setup_packet;
	subहाल = container_of(reqp, काष्ठा subहाल, setup);

	spin_lock_irqsave(&ctx->lock, flags);
	ctx->count--;
	ctx->pending--;

	/* queue must transfer and complete in fअगरo order, unless
	 * usb_unlink_urb() is used to unlink something not at the
	 * physical queue head (not tested).
	 */
	अगर (subहाल->number > 0) अणु
		अगर ((subहाल->number - ctx->last) != 1) अणु
			ERROR(ctx->dev,
				"subcase %d completed out of order, last %d\n",
				subहाल->number, ctx->last);
			status = -गलत_तर्क;
			ctx->last = subहाल->number;
			जाओ error;
		पूर्ण
	पूर्ण
	ctx->last = subहाल->number;

	/* succeed or fault in only one way? */
	अगर (status == subहाल->expected)
		status = 0;

	/* async unlink क्रम cleanup? */
	अन्यथा अगर (status != -ECONNRESET) अणु

		/* some faults are allowed, not required */
		अगर (subहाल->expected > 0 && (
			  ((status == -subहाल->expected	/* happened */
			   || status == 0))))			/* didn't */
			status = 0;
		/* someबार more than one fault is allowed */
		अन्यथा अगर (subहाल->number == 12 && status == -EPIPE)
			status = 0;
		अन्यथा
			ERROR(ctx->dev, "subtest %d error, status %d\n",
					subहाल->number, status);
	पूर्ण

	/* unexpected status codes mean errors; ideally, in hardware */
	अगर (status) अणु
error:
		अगर (ctx->status == 0) अणु
			पूर्णांक		i;

			ctx->status = status;
			ERROR(ctx->dev, "control queue %02x.%02x, err %d, "
					"%d left, subcase %d, len %d/%d\n",
					reqp->bRequestType, reqp->bRequest,
					status, ctx->count, subहाल->number,
					urb->actual_length,
					urb->transfer_buffer_length);

			/* FIXME this "unlink everything" निकास route should
			 * be a separate test हाल.
			 */

			/* unlink whatever's still pending */
			क्रम (i = 1; i < ctx->param->sglen; i++) अणु
				काष्ठा urb *u = ctx->urb[
							(i + subहाल->number)
							% ctx->param->sglen];

				अगर (u == urb || !u->dev)
					जारी;
				spin_unlock(&ctx->lock);
				status = usb_unlink_urb(u);
				spin_lock(&ctx->lock);
				चयन (status) अणु
				हाल -EINPROGRESS:
				हाल -EBUSY:
				हाल -EIDRM:
					जारी;
				शेष:
					ERROR(ctx->dev, "urb unlink --> %d\n",
							status);
				पूर्ण
			पूर्ण
			status = ctx->status;
		पूर्ण
	पूर्ण

	/* resubmit अगर we need to, अन्यथा mark this as करोne */
	अगर ((status == 0) && (ctx->pending < ctx->count)) अणु
		status = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (status != 0) अणु
			ERROR(ctx->dev,
				"can't resubmit ctrl %02x.%02x, err %d\n",
				reqp->bRequestType, reqp->bRequest, status);
			urb->dev = शून्य;
		पूर्ण अन्यथा
			ctx->pending++;
	पूर्ण अन्यथा
		urb->dev = शून्य;

	/* संकेत completion when nothing's queued */
	अगर (ctx->pending == 0)
		complete(&ctx->complete);
	spin_unlock_irqrestore(&ctx->lock, flags);
पूर्ण

अटल पूर्णांक
test_ctrl_queue(काष्ठा usbtest_dev *dev, काष्ठा usbtest_param_32 *param)
अणु
	काष्ठा usb_device	*udev = testdev_to_usbdev(dev);
	काष्ठा urb		**urb;
	काष्ठा ctrl_ctx		context;
	पूर्णांक			i;

	अगर (param->sglen == 0 || param->iterations > अच_पूर्णांक_उच्च / param->sglen)
		वापस -EOPNOTSUPP;

	spin_lock_init(&context.lock);
	context.dev = dev;
	init_completion(&context.complete);
	context.count = param->sglen * param->iterations;
	context.pending = 0;
	context.status = -ENOMEM;
	context.param = param;
	context.last = -1;

	/* allocate and init the urbs we'll queue.
	 * as with bulk/पूर्णांकr sglists, sglen is the queue depth; it also
	 * controls which subtests run (more tests than sglen) or rerun.
	 */
	urb = kसुस्मृति(param->sglen, माप(काष्ठा urb *), GFP_KERNEL);
	अगर (!urb)
		वापस -ENOMEM;
	क्रम (i = 0; i < param->sglen; i++) अणु
		पूर्णांक			pipe = usb_rcvctrlpipe(udev, 0);
		अचिन्हित		len;
		काष्ठा urb		*u;
		काष्ठा usb_ctrlrequest	req;
		काष्ठा subहाल		*reqp;

		/* sign of this variable means:
		 *  -: tested code must वापस this (negative) error code
		 *  +: tested code may वापस this (negative too) error code
		 */
		पूर्णांक			expected = 0;

		/* requests here are mostly expected to succeed on any
		 * device, but some are chosen to trigger protocol stalls
		 * or लघु पढ़ोs.
		 */
		स_रखो(&req, 0, माप(req));
		req.bRequest = USB_REQ_GET_DESCRIPTOR;
		req.bRequestType = USB_सूची_IN|USB_RECIP_DEVICE;

		चयन (i % NUM_SUBCASES) अणु
		हाल 0:		/* get device descriptor */
			req.wValue = cpu_to_le16(USB_DT_DEVICE << 8);
			len = माप(काष्ठा usb_device_descriptor);
			अवरोध;
		हाल 1:		/* get first config descriptor (only) */
			req.wValue = cpu_to_le16((USB_DT_CONFIG << 8) | 0);
			len = माप(काष्ठा usb_config_descriptor);
			अवरोध;
		हाल 2:		/* get altsetting (OFTEN STALLS) */
			req.bRequest = USB_REQ_GET_INTERFACE;
			req.bRequestType = USB_सूची_IN|USB_RECIP_INTERFACE;
			/* index = 0 means first पूर्णांकerface */
			len = 1;
			expected = EPIPE;
			अवरोध;
		हाल 3:		/* get पूर्णांकerface status */
			req.bRequest = USB_REQ_GET_STATUS;
			req.bRequestType = USB_सूची_IN|USB_RECIP_INTERFACE;
			/* पूर्णांकerface 0 */
			len = 2;
			अवरोध;
		हाल 4:		/* get device status */
			req.bRequest = USB_REQ_GET_STATUS;
			req.bRequestType = USB_सूची_IN|USB_RECIP_DEVICE;
			len = 2;
			अवरोध;
		हाल 5:		/* get device qualअगरier (MAY STALL) */
			req.wValue = cpu_to_le16 (USB_DT_DEVICE_QUALIFIER << 8);
			len = माप(काष्ठा usb_qualअगरier_descriptor);
			अगर (udev->speed != USB_SPEED_HIGH)
				expected = EPIPE;
			अवरोध;
		हाल 6:		/* get first config descriptor, plus पूर्णांकerface */
			req.wValue = cpu_to_le16((USB_DT_CONFIG << 8) | 0);
			len = माप(काष्ठा usb_config_descriptor);
			len += माप(काष्ठा usb_पूर्णांकerface_descriptor);
			अवरोध;
		हाल 7:		/* get पूर्णांकerface descriptor (ALWAYS STALLS) */
			req.wValue = cpu_to_le16 (USB_DT_INTERFACE << 8);
			/* पूर्णांकerface == 0 */
			len = माप(काष्ठा usb_पूर्णांकerface_descriptor);
			expected = -EPIPE;
			अवरोध;
		/* NOTE: two consecutive stalls in the queue here.
		 *  that tests fault recovery a bit more aggressively. */
		हाल 8:		/* clear endpoपूर्णांक halt (MAY STALL) */
			req.bRequest = USB_REQ_CLEAR_FEATURE;
			req.bRequestType = USB_RECIP_ENDPOINT;
			/* wValue 0 == ep halt */
			/* wIndex 0 == ep0 (shouldn't halt!) */
			len = 0;
			pipe = usb_sndctrlpipe(udev, 0);
			expected = EPIPE;
			अवरोध;
		हाल 9:		/* get endpoपूर्णांक status */
			req.bRequest = USB_REQ_GET_STATUS;
			req.bRequestType = USB_सूची_IN|USB_RECIP_ENDPOINT;
			/* endpoपूर्णांक 0 */
			len = 2;
			अवरोध;
		हाल 10:	/* trigger लघु पढ़ो (EREMOTEIO) */
			req.wValue = cpu_to_le16((USB_DT_CONFIG << 8) | 0);
			len = 1024;
			expected = -EREMOTEIO;
			अवरोध;
		/* NOTE: two consecutive _dअगरferent_ faults in the queue. */
		हाल 11:	/* get endpoपूर्णांक descriptor (ALWAYS STALLS) */
			req.wValue = cpu_to_le16(USB_DT_ENDPOINT << 8);
			/* endpoपूर्णांक == 0 */
			len = माप(काष्ठा usb_पूर्णांकerface_descriptor);
			expected = EPIPE;
			अवरोध;
		/* NOTE: someबार even a third fault in the queue! */
		हाल 12:	/* get string 0 descriptor (MAY STALL) */
			req.wValue = cpu_to_le16(USB_DT_STRING << 8);
			/* string == 0, क्रम language IDs */
			len = माप(काष्ठा usb_पूर्णांकerface_descriptor);
			/* may succeed when > 4 languages */
			expected = EREMOTEIO;	/* or EPIPE, अगर no strings */
			अवरोध;
		हाल 13:	/* लघु पढ़ो, resembling हाल 10 */
			req.wValue = cpu_to_le16((USB_DT_CONFIG << 8) | 0);
			/* last data packet "should" be DATA1, not DATA0 */
			अगर (udev->speed == USB_SPEED_SUPER)
				len = 1024 - 512;
			अन्यथा
				len = 1024 - udev->descriptor.bMaxPacketSize0;
			expected = -EREMOTEIO;
			अवरोध;
		हाल 14:	/* लघु पढ़ो; try to fill the last packet */
			req.wValue = cpu_to_le16((USB_DT_DEVICE << 8) | 0);
			/* device descriptor size == 18 bytes */
			len = udev->descriptor.bMaxPacketSize0;
			अगर (udev->speed == USB_SPEED_SUPER)
				len = 512;
			चयन (len) अणु
			हाल 8:
				len = 24;
				अवरोध;
			हाल 16:
				len = 32;
				अवरोध;
			पूर्ण
			expected = -EREMOTEIO;
			अवरोध;
		हाल 15:
			req.wValue = cpu_to_le16(USB_DT_BOS << 8);
			अगर (udev->bos)
				len = le16_to_cpu(udev->bos->desc->wTotalLength);
			अन्यथा
				len = माप(काष्ठा usb_bos_descriptor);
			अगर (le16_to_cpu(udev->descriptor.bcdUSB) < 0x0201)
				expected = -EPIPE;
			अवरोध;
		शेष:
			ERROR(dev, "bogus number of ctrl queue testcases!\n");
			context.status = -EINVAL;
			जाओ cleanup;
		पूर्ण
		req.wLength = cpu_to_le16(len);
		urb[i] = u = simple_alloc_urb(udev, pipe, len, 0);
		अगर (!u)
			जाओ cleanup;

		reqp = kदो_स्मृति(माप(*reqp), GFP_KERNEL);
		अगर (!reqp)
			जाओ cleanup;
		reqp->setup = req;
		reqp->number = i % NUM_SUBCASES;
		reqp->expected = expected;
		u->setup_packet = (अक्षर *) &reqp->setup;

		u->context = &context;
		u->complete = ctrl_complete;
	पूर्ण

	/* queue the urbs */
	context.urb = urb;
	spin_lock_irq(&context.lock);
	क्रम (i = 0; i < param->sglen; i++) अणु
		context.status = usb_submit_urb(urb[i], GFP_ATOMIC);
		अगर (context.status != 0) अणु
			ERROR(dev, "can't submit urb[%d], status %d\n",
					i, context.status);
			context.count = context.pending;
			अवरोध;
		पूर्ण
		context.pending++;
	पूर्ण
	spin_unlock_irq(&context.lock);

	/* FIXME  set समयr and समय out; provide a disconnect hook */

	/* रुको क्रम the last one to complete */
	अगर (context.pending > 0)
		रुको_क्रम_completion(&context.complete);

cleanup:
	क्रम (i = 0; i < param->sglen; i++) अणु
		अगर (!urb[i])
			जारी;
		urb[i]->dev = udev;
		kमुक्त(urb[i]->setup_packet);
		simple_मुक्त_urb(urb[i]);
	पूर्ण
	kमुक्त(urb);
	वापस context.status;
पूर्ण
#अघोषित NUM_SUBCASES


/*-------------------------------------------------------------------------*/

अटल व्योम unlink1_callback(काष्ठा urb *urb)
अणु
	पूर्णांक	status = urb->status;

	/* we "know" -EPIPE (stall) never happens */
	अगर (!status)
		status = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (status) अणु
		urb->status = status;
		complete(urb->context);
	पूर्ण
पूर्ण

अटल पूर्णांक unlink1(काष्ठा usbtest_dev *dev, पूर्णांक pipe, पूर्णांक size, पूर्णांक async)
अणु
	काष्ठा urb		*urb;
	काष्ठा completion	completion;
	पूर्णांक			retval = 0;

	init_completion(&completion);
	urb = simple_alloc_urb(testdev_to_usbdev(dev), pipe, size, 0);
	अगर (!urb)
		वापस -ENOMEM;
	urb->context = &completion;
	urb->complete = unlink1_callback;

	अगर (usb_pipeout(urb->pipe)) अणु
		simple_fill_buf(urb);
		urb->transfer_flags |= URB_ZERO_PACKET;
	पूर्ण

	/* keep the endpoपूर्णांक busy.  there are lots of hc/hcd-पूर्णांकernal
	 * states, and testing should get to all of them over समय.
	 *
	 * FIXME want additional tests क्रम when endpoपूर्णांक is STALLing
	 * due to errors, or is just NAKing requests.
	 */
	retval = usb_submit_urb(urb, GFP_KERNEL);
	अगर (retval != 0) अणु
		dev_err(&dev->पूर्णांकf->dev, "submit fail %d\n", retval);
		वापस retval;
	पूर्ण

	/* unlinking that should always work.  variable delay tests more
	 * hcd states and code paths, even with little other प्रणाली load.
	 */
	msleep(jअगरfies % (2 * INTERRUPT_RATE));
	अगर (async) अणु
		जबतक (!completion_करोne(&completion)) अणु
			retval = usb_unlink_urb(urb);

			अगर (retval == 0 && usb_pipein(urb->pipe))
				retval = simple_check_buf(dev, urb);

			चयन (retval) अणु
			हाल -EBUSY:
			हाल -EIDRM:
				/* we can't unlink urbs while they're completing
				 * or अगर they've completed, and we haven't
				 * resubmitted. "normal" drivers would prevent
				 * resubmission, but since we're testing unlink
				 * paths, we can't.
				 */
				ERROR(dev, "unlink retry\n");
				जारी;
			हाल 0:
			हाल -EINPROGRESS:
				अवरोध;

			शेष:
				dev_err(&dev->पूर्णांकf->dev,
					"unlink fail %d\n", retval);
				वापस retval;
			पूर्ण

			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		usb_समाप्त_urb(urb);

	रुको_क्रम_completion(&completion);
	retval = urb->status;
	simple_मुक्त_urb(urb);

	अगर (async)
		वापस (retval == -ECONNRESET) ? 0 : retval - 1000;
	अन्यथा
		वापस (retval == -ENOENT || retval == -EPERM) ?
				0 : retval - 2000;
पूर्ण

अटल पूर्णांक unlink_simple(काष्ठा usbtest_dev *dev, पूर्णांक pipe, पूर्णांक len)
अणु
	पूर्णांक			retval = 0;

	/* test sync and async paths */
	retval = unlink1(dev, pipe, len, 1);
	अगर (!retval)
		retval = unlink1(dev, pipe, len, 0);
	वापस retval;
पूर्ण

/*-------------------------------------------------------------------------*/

काष्ठा queued_ctx अणु
	काष्ठा completion	complete;
	atomic_t		pending;
	अचिन्हित		num;
	पूर्णांक			status;
	काष्ठा urb		**urbs;
पूर्ण;

अटल व्योम unlink_queued_callback(काष्ठा urb *urb)
अणु
	पूर्णांक			status = urb->status;
	काष्ठा queued_ctx	*ctx = urb->context;

	अगर (ctx->status)
		जाओ करोne;
	अगर (urb == ctx->urbs[ctx->num - 4] || urb == ctx->urbs[ctx->num - 2]) अणु
		अगर (status == -ECONNRESET)
			जाओ करोne;
		/* What error should we report अगर the URB completed normally? */
	पूर्ण
	अगर (status != 0)
		ctx->status = status;

 करोne:
	अगर (atomic_dec_and_test(&ctx->pending))
		complete(&ctx->complete);
पूर्ण

अटल पूर्णांक unlink_queued(काष्ठा usbtest_dev *dev, पूर्णांक pipe, अचिन्हित num,
		अचिन्हित size)
अणु
	काष्ठा queued_ctx	ctx;
	काष्ठा usb_device	*udev = testdev_to_usbdev(dev);
	व्योम			*buf;
	dma_addr_t		buf_dma;
	पूर्णांक			i;
	पूर्णांक			retval = -ENOMEM;

	init_completion(&ctx.complete);
	atomic_set(&ctx.pending, 1);	/* One more than the actual value */
	ctx.num = num;
	ctx.status = 0;

	buf = usb_alloc_coherent(udev, size, GFP_KERNEL, &buf_dma);
	अगर (!buf)
		वापस retval;
	स_रखो(buf, 0, size);

	/* Allocate and init the urbs we'll queue */
	ctx.urbs = kसुस्मृति(num, माप(काष्ठा urb *), GFP_KERNEL);
	अगर (!ctx.urbs)
		जाओ मुक्त_buf;
	क्रम (i = 0; i < num; i++) अणु
		ctx.urbs[i] = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!ctx.urbs[i])
			जाओ मुक्त_urbs;
		usb_fill_bulk_urb(ctx.urbs[i], udev, pipe, buf, size,
				unlink_queued_callback, &ctx);
		ctx.urbs[i]->transfer_dma = buf_dma;
		ctx.urbs[i]->transfer_flags = URB_NO_TRANSFER_DMA_MAP;

		अगर (usb_pipeout(ctx.urbs[i]->pipe)) अणु
			simple_fill_buf(ctx.urbs[i]);
			ctx.urbs[i]->transfer_flags |= URB_ZERO_PACKET;
		पूर्ण
	पूर्ण

	/* Submit all the URBs and then unlink URBs num - 4 and num - 2. */
	क्रम (i = 0; i < num; i++) अणु
		atomic_inc(&ctx.pending);
		retval = usb_submit_urb(ctx.urbs[i], GFP_KERNEL);
		अगर (retval != 0) अणु
			dev_err(&dev->पूर्णांकf->dev, "submit urbs[%d] fail %d\n",
					i, retval);
			atomic_dec(&ctx.pending);
			ctx.status = retval;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == num) अणु
		usb_unlink_urb(ctx.urbs[num - 4]);
		usb_unlink_urb(ctx.urbs[num - 2]);
	पूर्ण अन्यथा अणु
		जबतक (--i >= 0)
			usb_unlink_urb(ctx.urbs[i]);
	पूर्ण

	अगर (atomic_dec_and_test(&ctx.pending))		/* The extra count */
		complete(&ctx.complete);
	रुको_क्रम_completion(&ctx.complete);
	retval = ctx.status;

 मुक्त_urbs:
	क्रम (i = 0; i < num; i++)
		usb_मुक्त_urb(ctx.urbs[i]);
	kमुक्त(ctx.urbs);
 मुक्त_buf:
	usb_मुक्त_coherent(udev, size, buf, buf_dma);
	वापस retval;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक verअगरy_not_halted(काष्ठा usbtest_dev *tdev, पूर्णांक ep, काष्ठा urb *urb)
अणु
	पूर्णांक	retval;
	u16	status;

	/* shouldn't look or act halted */
	retval = usb_get_std_status(urb->dev, USB_RECIP_ENDPOINT, ep, &status);
	अगर (retval < 0) अणु
		ERROR(tdev, "ep %02x couldn't get no-halt status, %d\n",
				ep, retval);
		वापस retval;
	पूर्ण
	अगर (status != 0) अणु
		ERROR(tdev, "ep %02x bogus status: %04x != 0\n", ep, status);
		वापस -EINVAL;
	पूर्ण
	retval = simple_io(tdev, urb, 1, 0, 0, __func__);
	अगर (retval != 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक verअगरy_halted(काष्ठा usbtest_dev *tdev, पूर्णांक ep, काष्ठा urb *urb)
अणु
	पूर्णांक	retval;
	u16	status;

	/* should look and act halted */
	retval = usb_get_std_status(urb->dev, USB_RECIP_ENDPOINT, ep, &status);
	अगर (retval < 0) अणु
		ERROR(tdev, "ep %02x couldn't get halt status, %d\n",
				ep, retval);
		वापस retval;
	पूर्ण
	अगर (status != 1) अणु
		ERROR(tdev, "ep %02x bogus status: %04x != 1\n", ep, status);
		वापस -EINVAL;
	पूर्ण
	retval = simple_io(tdev, urb, 1, 0, -EPIPE, __func__);
	अगर (retval != -EPIPE)
		वापस -EINVAL;
	retval = simple_io(tdev, urb, 1, 0, -EPIPE, "verify_still_halted");
	अगर (retval != -EPIPE)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक test_halt(काष्ठा usbtest_dev *tdev, पूर्णांक ep, काष्ठा urb *urb)
अणु
	पूर्णांक	retval;

	/* shouldn't look or act halted now */
	retval = verअगरy_not_halted(tdev, ep, urb);
	अगर (retval < 0)
		वापस retval;

	/* set halt (protocol test only), verअगरy it worked */
	retval = usb_control_msg(urb->dev, usb_sndctrlpipe(urb->dev, 0),
			USB_REQ_SET_FEATURE, USB_RECIP_ENDPOINT,
			USB_ENDPOINT_HALT, ep,
			शून्य, 0, USB_CTRL_SET_TIMEOUT);
	अगर (retval < 0) अणु
		ERROR(tdev, "ep %02x couldn't set halt, %d\n", ep, retval);
		वापस retval;
	पूर्ण
	retval = verअगरy_halted(tdev, ep, urb);
	अगर (retval < 0) अणु
		पूर्णांक ret;

		/* clear halt anyways, अन्यथा further tests will fail */
		ret = usb_clear_halt(urb->dev, urb->pipe);
		अगर (ret)
			ERROR(tdev, "ep %02x couldn't clear halt, %d\n",
			      ep, ret);

		वापस retval;
	पूर्ण

	/* clear halt (tests API + protocol), verअगरy it worked */
	retval = usb_clear_halt(urb->dev, urb->pipe);
	अगर (retval < 0) अणु
		ERROR(tdev, "ep %02x couldn't clear halt, %d\n", ep, retval);
		वापस retval;
	पूर्ण
	retval = verअगरy_not_halted(tdev, ep, urb);
	अगर (retval < 0)
		वापस retval;

	/* NOTE:  could also verअगरy SET_INTERFACE clear halts ... */

	वापस 0;
पूर्ण

अटल पूर्णांक test_toggle_sync(काष्ठा usbtest_dev *tdev, पूर्णांक ep, काष्ठा urb *urb)
अणु
	पूर्णांक	retval;

	/* clear initial data toggle to DATA0 */
	retval = usb_clear_halt(urb->dev, urb->pipe);
	अगर (retval < 0) अणु
		ERROR(tdev, "ep %02x couldn't clear halt, %d\n", ep, retval);
		वापस retval;
	पूर्ण

	/* transfer 3 data packets, should be DATA0, DATA1, DATA0 */
	retval = simple_io(tdev, urb, 1, 0, 0, __func__);
	अगर (retval != 0)
		वापस -EINVAL;

	/* clear halt resets device side data toggle, host should react to it */
	retval = usb_clear_halt(urb->dev, urb->pipe);
	अगर (retval < 0) अणु
		ERROR(tdev, "ep %02x couldn't clear halt, %d\n", ep, retval);
		वापस retval;
	पूर्ण

	/* host should use DATA0 again after clear halt */
	retval = simple_io(tdev, urb, 1, 0, 0, __func__);

	वापस retval;
पूर्ण

अटल पूर्णांक halt_simple(काष्ठा usbtest_dev *dev)
अणु
	पूर्णांक			ep;
	पूर्णांक			retval = 0;
	काष्ठा urb		*urb;
	काष्ठा usb_device	*udev = testdev_to_usbdev(dev);

	अगर (udev->speed == USB_SPEED_SUPER)
		urb = simple_alloc_urb(udev, 0, 1024, 0);
	अन्यथा
		urb = simple_alloc_urb(udev, 0, 512, 0);
	अगर (urb == शून्य)
		वापस -ENOMEM;

	अगर (dev->in_pipe) अणु
		ep = usb_pipeendpoपूर्णांक(dev->in_pipe) | USB_सूची_IN;
		urb->pipe = dev->in_pipe;
		retval = test_halt(dev, ep, urb);
		अगर (retval < 0)
			जाओ करोne;
	पूर्ण

	अगर (dev->out_pipe) अणु
		ep = usb_pipeendpoपूर्णांक(dev->out_pipe);
		urb->pipe = dev->out_pipe;
		retval = test_halt(dev, ep, urb);
	पूर्ण
करोne:
	simple_मुक्त_urb(urb);
	वापस retval;
पूर्ण

अटल पूर्णांक toggle_sync_simple(काष्ठा usbtest_dev *dev)
अणु
	पूर्णांक			ep;
	पूर्णांक			retval = 0;
	काष्ठा urb		*urb;
	काष्ठा usb_device	*udev = testdev_to_usbdev(dev);
	अचिन्हित		maxp = get_maxpacket(udev, dev->out_pipe);

	/*
	 * Create a URB that causes a transfer of uneven amount of data packets
	 * This way the clear toggle has an impact on the data toggle sequence.
	 * Use 2 maxpacket length packets and one zero packet.
	 */
	urb = simple_alloc_urb(udev, 0,  2 * maxp, 0);
	अगर (urb == शून्य)
		वापस -ENOMEM;

	urb->transfer_flags |= URB_ZERO_PACKET;

	ep = usb_pipeendpoपूर्णांक(dev->out_pipe);
	urb->pipe = dev->out_pipe;
	retval = test_toggle_sync(dev, ep, urb);

	simple_मुक्त_urb(urb);
	वापस retval;
पूर्ण

/*-------------------------------------------------------------------------*/

/* Control OUT tests use the venकरोr control requests from Intel's
 * USB 2.0 compliance test device:  ग_लिखो a buffer, पढ़ो it back.
 *
 * Intel's spec only _requires_ that it work क्रम one packet, which
 * is pretty weak.   Some HCDs place limits here; most devices will
 * need to be able to handle more than one OUT data packet.  We'll
 * try whatever we're told to try.
 */
अटल पूर्णांक ctrl_out(काष्ठा usbtest_dev *dev,
		अचिन्हित count, अचिन्हित length, अचिन्हित vary, अचिन्हित offset)
अणु
	अचिन्हित		i, j, len;
	पूर्णांक			retval;
	u8			*buf;
	अक्षर			*what = "?";
	काष्ठा usb_device	*udev;

	अगर (length < 1 || length > 0xffff || vary >= length)
		वापस -EINVAL;

	buf = kदो_स्मृति(length + offset, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	buf += offset;
	udev = testdev_to_usbdev(dev);
	len = length;
	retval = 0;

	/* NOTE:  hardware might well act dअगरferently अगर we pushed it
	 * with lots back-to-back queued requests.
	 */
	क्रम (i = 0; i < count; i++) अणु
		/* ग_लिखो patterned data */
		क्रम (j = 0; j < len; j++)
			buf[j] = (u8)(i + j);
		retval = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				0x5b, USB_सूची_OUT|USB_TYPE_VENDOR,
				0, 0, buf, len, USB_CTRL_SET_TIMEOUT);
		अगर (retval != len) अणु
			what = "write";
			अगर (retval >= 0) अणु
				ERROR(dev, "ctrl_out, wlen %d (expected %d)\n",
						retval, len);
				retval = -EBADMSG;
			पूर्ण
			अवरोध;
		पूर्ण

		/* पढ़ो it back -- assuming nothing पूर्णांकervened!!  */
		retval = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
				0x5c, USB_सूची_IN|USB_TYPE_VENDOR,
				0, 0, buf, len, USB_CTRL_GET_TIMEOUT);
		अगर (retval != len) अणु
			what = "read";
			अगर (retval >= 0) अणु
				ERROR(dev, "ctrl_out, rlen %d (expected %d)\n",
						retval, len);
				retval = -EBADMSG;
			पूर्ण
			अवरोध;
		पूर्ण

		/* fail अगर we can't verअगरy */
		क्रम (j = 0; j < len; j++) अणु
			अगर (buf[j] != (u8)(i + j)) अणु
				ERROR(dev, "ctrl_out, byte %d is %d not %d\n",
					j, buf[j], (u8)(i + j));
				retval = -EBADMSG;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (retval < 0) अणु
			what = "verify";
			अवरोध;
		पूर्ण

		len += vary;

		/* [real world] the "zero bytes IN" हाल isn't really used.
		 * hardware can easily trip up in this weird हाल, since its
		 * status stage is IN, not OUT like other ep0in transfers.
		 */
		अगर (len > length)
			len = realworld ? 1 : 0;
	पूर्ण

	अगर (retval < 0)
		ERROR(dev, "ctrl_out %s failed, code %d, count %d\n",
			what, retval, i);

	kमुक्त(buf - offset);
	वापस retval;
पूर्ण

/*-------------------------------------------------------------------------*/

/* ISO/BULK tests ... mimics common usage
 *  - buffer length is split पूर्णांकo N packets (mostly maxpacket sized)
 *  - multi-buffers according to sglen
 */

काष्ठा transfer_context अणु
	अचिन्हित		count;
	अचिन्हित		pending;
	spinlock_t		lock;
	काष्ठा completion	करोne;
	पूर्णांक			submit_error;
	अचिन्हित दीर्घ		errors;
	अचिन्हित दीर्घ		packet_count;
	काष्ठा usbtest_dev	*dev;
	bool			is_iso;
पूर्ण;

अटल व्योम complicated_callback(काष्ठा urb *urb)
अणु
	काष्ठा transfer_context	*ctx = urb->context;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->lock, flags);
	ctx->count--;

	ctx->packet_count += urb->number_of_packets;
	अगर (urb->error_count > 0)
		ctx->errors += urb->error_count;
	अन्यथा अगर (urb->status != 0)
		ctx->errors += (ctx->is_iso ? urb->number_of_packets : 1);
	अन्यथा अगर (urb->actual_length != urb->transfer_buffer_length)
		ctx->errors++;
	अन्यथा अगर (check_guard_bytes(ctx->dev, urb) != 0)
		ctx->errors++;

	अगर (urb->status == 0 && ctx->count > (ctx->pending - 1)
			&& !ctx->submit_error) अणु
		पूर्णांक status = usb_submit_urb(urb, GFP_ATOMIC);
		चयन (status) अणु
		हाल 0:
			जाओ करोne;
		शेष:
			dev_err(&ctx->dev->पूर्णांकf->dev,
					"resubmit err %d\n",
					status);
			fallthrough;
		हाल -ENODEV:			/* disconnected */
		हाल -ESHUTDOWN:		/* endpoपूर्णांक disabled */
			ctx->submit_error = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	ctx->pending--;
	अगर (ctx->pending == 0) अणु
		अगर (ctx->errors)
			dev_err(&ctx->dev->पूर्णांकf->dev,
				"during the test, %lu errors out of %lu\n",
				ctx->errors, ctx->packet_count);
		complete(&ctx->करोne);
	पूर्ण
करोne:
	spin_unlock_irqrestore(&ctx->lock, flags);
पूर्ण

अटल काष्ठा urb *iso_alloc_urb(
	काष्ठा usb_device	*udev,
	पूर्णांक			pipe,
	काष्ठा usb_endpoपूर्णांक_descriptor	*desc,
	दीर्घ			bytes,
	अचिन्हित offset
)
अणु
	काष्ठा urb		*urb;
	अचिन्हित		i, maxp, packets;

	अगर (bytes < 0 || !desc)
		वापस शून्य;

	maxp = usb_endpoपूर्णांक_maxp(desc);
	अगर (udev->speed >= USB_SPEED_SUPER)
		maxp *= ss_isoc_get_packet_num(udev, pipe);
	अन्यथा
		maxp *= usb_endpoपूर्णांक_maxp_mult(desc);

	packets = DIV_ROUND_UP(bytes, maxp);

	urb = usb_alloc_urb(packets, GFP_KERNEL);
	अगर (!urb)
		वापस urb;
	urb->dev = udev;
	urb->pipe = pipe;

	urb->number_of_packets = packets;
	urb->transfer_buffer_length = bytes;
	urb->transfer_buffer = usb_alloc_coherent(udev, bytes + offset,
							GFP_KERNEL,
							&urb->transfer_dma);
	अगर (!urb->transfer_buffer) अणु
		usb_मुक्त_urb(urb);
		वापस शून्य;
	पूर्ण
	अगर (offset) अणु
		स_रखो(urb->transfer_buffer, GUARD_BYTE, offset);
		urb->transfer_buffer += offset;
		urb->transfer_dma += offset;
	पूर्ण
	/* For inbound transfers use guard byte so that test fails अगर
		data not correctly copied */
	स_रखो(urb->transfer_buffer,
			usb_pipein(urb->pipe) ? GUARD_BYTE : 0,
			bytes);

	क्रम (i = 0; i < packets; i++) अणु
		/* here, only the last packet will be लघु */
		urb->iso_frame_desc[i].length = min((अचिन्हित) bytes, maxp);
		bytes -= urb->iso_frame_desc[i].length;

		urb->iso_frame_desc[i].offset = maxp * i;
	पूर्ण

	urb->complete = complicated_callback;
	/* urb->context = SET BY CALLER */
	urb->पूर्णांकerval = 1 << (desc->bInterval - 1);
	urb->transfer_flags = URB_ISO_ASAP | URB_NO_TRANSFER_DMA_MAP;
	वापस urb;
पूर्ण

अटल पूर्णांक
test_queue(काष्ठा usbtest_dev *dev, काष्ठा usbtest_param_32 *param,
		पूर्णांक pipe, काष्ठा usb_endpoपूर्णांक_descriptor *desc, अचिन्हित offset)
अणु
	काष्ठा transfer_context	context;
	काष्ठा usb_device	*udev;
	अचिन्हित		i;
	अचिन्हित दीर्घ		packets = 0;
	पूर्णांक			status = 0;
	काष्ठा urb		**urbs;

	अगर (!param->sglen || param->iterations > अच_पूर्णांक_उच्च / param->sglen)
		वापस -EINVAL;

	अगर (param->sglen > MAX_SGLEN)
		वापस -EINVAL;

	urbs = kसुस्मृति(param->sglen, माप(*urbs), GFP_KERNEL);
	अगर (!urbs)
		वापस -ENOMEM;

	स_रखो(&context, 0, माप(context));
	context.count = param->iterations * param->sglen;
	context.dev = dev;
	context.is_iso = !!desc;
	init_completion(&context.करोne);
	spin_lock_init(&context.lock);

	udev = testdev_to_usbdev(dev);

	क्रम (i = 0; i < param->sglen; i++) अणु
		अगर (context.is_iso)
			urbs[i] = iso_alloc_urb(udev, pipe, desc,
					param->length, offset);
		अन्यथा
			urbs[i] = complicated_alloc_urb(udev, pipe,
					param->length, 0);

		अगर (!urbs[i]) अणु
			status = -ENOMEM;
			जाओ fail;
		पूर्ण
		packets += urbs[i]->number_of_packets;
		urbs[i]->context = &context;
	पूर्ण
	packets *= param->iterations;

	अगर (context.is_iso) अणु
		पूर्णांक transaction_num;

		अगर (udev->speed >= USB_SPEED_SUPER)
			transaction_num = ss_isoc_get_packet_num(udev, pipe);
		अन्यथा
			transaction_num = usb_endpoपूर्णांक_maxp_mult(desc);

		dev_info(&dev->पूर्णांकf->dev,
			"iso period %d %sframes, wMaxPacket %d, transactions: %d\n",
			1 << (desc->bInterval - 1),
			(udev->speed >= USB_SPEED_HIGH) ? "micro" : "",
			usb_endpoपूर्णांक_maxp(desc),
			transaction_num);

		dev_info(&dev->पूर्णांकf->dev,
			"total %lu msec (%lu packets)\n",
			(packets * (1 << (desc->bInterval - 1)))
				/ ((udev->speed >= USB_SPEED_HIGH) ? 8 : 1),
			packets);
	पूर्ण

	spin_lock_irq(&context.lock);
	क्रम (i = 0; i < param->sglen; i++) अणु
		++context.pending;
		status = usb_submit_urb(urbs[i], GFP_ATOMIC);
		अगर (status < 0) अणु
			ERROR(dev, "submit iso[%d], error %d\n", i, status);
			अगर (i == 0) अणु
				spin_unlock_irq(&context.lock);
				जाओ fail;
			पूर्ण

			simple_मुक्त_urb(urbs[i]);
			urbs[i] = शून्य;
			context.pending--;
			context.submit_error = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&context.lock);

	रुको_क्रम_completion(&context.करोne);

	क्रम (i = 0; i < param->sglen; i++) अणु
		अगर (urbs[i])
			simple_मुक्त_urb(urbs[i]);
	पूर्ण
	/*
	 * Isochronous transfers are expected to fail someबार.  As an
	 * arbitrary limit, we will report an error अगर any submissions
	 * fail or अगर the transfer failure rate is > 10%.
	 */
	अगर (status != 0)
		;
	अन्यथा अगर (context.submit_error)
		status = -EACCES;
	अन्यथा अगर (context.errors >
			(context.is_iso ? context.packet_count / 10 : 0))
		status = -EIO;

	kमुक्त(urbs);
	वापस status;

fail:
	क्रम (i = 0; i < param->sglen; i++) अणु
		अगर (urbs[i])
			simple_मुक्त_urb(urbs[i]);
	पूर्ण

	kमुक्त(urbs);
	वापस status;
पूर्ण

अटल पूर्णांक test_unaligned_bulk(
	काष्ठा usbtest_dev *tdev,
	पूर्णांक pipe,
	अचिन्हित length,
	पूर्णांक iterations,
	अचिन्हित transfer_flags,
	स्थिर अक्षर *label)
अणु
	पूर्णांक retval;
	काष्ठा urb *urb = usbtest_alloc_urb(testdev_to_usbdev(tdev),
			pipe, length, transfer_flags, 1, 0, simple_callback);

	अगर (!urb)
		वापस -ENOMEM;

	retval = simple_io(tdev, urb, iterations, 0, 0, label);
	simple_मुक्त_urb(urb);
	वापस retval;
पूर्ण

/* Run tests. */
अटल पूर्णांक
usbtest_करो_ioctl(काष्ठा usb_पूर्णांकerface *पूर्णांकf, काष्ठा usbtest_param_32 *param)
अणु
	काष्ठा usbtest_dev	*dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा usb_device	*udev = testdev_to_usbdev(dev);
	काष्ठा urb		*urb;
	काष्ठा scatterlist	*sg;
	काष्ठा usb_sg_request	req;
	अचिन्हित		i;
	पूर्णांक	retval = -EOPNOTSUPP;

	अगर (param->iterations <= 0)
		वापस -EINVAL;
	अगर (param->sglen > MAX_SGLEN)
		वापस -EINVAL;
	/*
	 * Just a bunch of test हालs that every HCD is expected to handle.
	 *
	 * Some may need specअगरic firmware, though it'd be good to have
	 * one firmware image to handle all the test हालs.
	 *
	 * FIXME add more tests!  cancel requests, verअगरy the data, control
	 * queueing, concurrent पढ़ो+ग_लिखो thपढ़ोs, and so on.
	 */
	चयन (param->test_num) अणु

	हाल 0:
		dev_info(&पूर्णांकf->dev, "TEST 0:  NOP\n");
		retval = 0;
		अवरोध;

	/* Simple non-queued bulk I/O tests */
	हाल 1:
		अगर (dev->out_pipe == 0)
			अवरोध;
		dev_info(&पूर्णांकf->dev,
				"TEST 1:  write %d bytes %u times\n",
				param->length, param->iterations);
		urb = simple_alloc_urb(udev, dev->out_pipe, param->length, 0);
		अगर (!urb) अणु
			retval = -ENOMEM;
			अवरोध;
		पूर्ण
		/* FIRMWARE:  bulk sink (maybe accepts लघु ग_लिखोs) */
		retval = simple_io(dev, urb, param->iterations, 0, 0, "test1");
		simple_मुक्त_urb(urb);
		अवरोध;
	हाल 2:
		अगर (dev->in_pipe == 0)
			अवरोध;
		dev_info(&पूर्णांकf->dev,
				"TEST 2:  read %d bytes %u times\n",
				param->length, param->iterations);
		urb = simple_alloc_urb(udev, dev->in_pipe, param->length, 0);
		अगर (!urb) अणु
			retval = -ENOMEM;
			अवरोध;
		पूर्ण
		/* FIRMWARE:  bulk source (maybe generates लघु ग_लिखोs) */
		retval = simple_io(dev, urb, param->iterations, 0, 0, "test2");
		simple_मुक्त_urb(urb);
		अवरोध;
	हाल 3:
		अगर (dev->out_pipe == 0 || param->vary == 0)
			अवरोध;
		dev_info(&पूर्णांकf->dev,
				"TEST 3:  write/%d 0..%d bytes %u times\n",
				param->vary, param->length, param->iterations);
		urb = simple_alloc_urb(udev, dev->out_pipe, param->length, 0);
		अगर (!urb) अणु
			retval = -ENOMEM;
			अवरोध;
		पूर्ण
		/* FIRMWARE:  bulk sink (maybe accepts लघु ग_लिखोs) */
		retval = simple_io(dev, urb, param->iterations, param->vary,
					0, "test3");
		simple_मुक्त_urb(urb);
		अवरोध;
	हाल 4:
		अगर (dev->in_pipe == 0 || param->vary == 0)
			अवरोध;
		dev_info(&पूर्णांकf->dev,
				"TEST 4:  read/%d 0..%d bytes %u times\n",
				param->vary, param->length, param->iterations);
		urb = simple_alloc_urb(udev, dev->in_pipe, param->length, 0);
		अगर (!urb) अणु
			retval = -ENOMEM;
			अवरोध;
		पूर्ण
		/* FIRMWARE:  bulk source (maybe generates लघु ग_लिखोs) */
		retval = simple_io(dev, urb, param->iterations, param->vary,
					0, "test4");
		simple_मुक्त_urb(urb);
		अवरोध;

	/* Queued bulk I/O tests */
	हाल 5:
		अगर (dev->out_pipe == 0 || param->sglen == 0)
			अवरोध;
		dev_info(&पूर्णांकf->dev,
			"TEST 5:  write %d sglists %d entries of %d bytes\n",
				param->iterations,
				param->sglen, param->length);
		sg = alloc_sglist(param->sglen, param->length,
				0, dev, dev->out_pipe);
		अगर (!sg) अणु
			retval = -ENOMEM;
			अवरोध;
		पूर्ण
		/* FIRMWARE:  bulk sink (maybe accepts लघु ग_लिखोs) */
		retval = perक्रमm_sglist(dev, param->iterations, dev->out_pipe,
				&req, sg, param->sglen);
		मुक्त_sglist(sg, param->sglen);
		अवरोध;

	हाल 6:
		अगर (dev->in_pipe == 0 || param->sglen == 0)
			अवरोध;
		dev_info(&पूर्णांकf->dev,
			"TEST 6:  read %d sglists %d entries of %d bytes\n",
				param->iterations,
				param->sglen, param->length);
		sg = alloc_sglist(param->sglen, param->length,
				0, dev, dev->in_pipe);
		अगर (!sg) अणु
			retval = -ENOMEM;
			अवरोध;
		पूर्ण
		/* FIRMWARE:  bulk source (maybe generates लघु ग_लिखोs) */
		retval = perक्रमm_sglist(dev, param->iterations, dev->in_pipe,
				&req, sg, param->sglen);
		मुक्त_sglist(sg, param->sglen);
		अवरोध;
	हाल 7:
		अगर (dev->out_pipe == 0 || param->sglen == 0 || param->vary == 0)
			अवरोध;
		dev_info(&पूर्णांकf->dev,
			"TEST 7:  write/%d %d sglists %d entries 0..%d bytes\n",
				param->vary, param->iterations,
				param->sglen, param->length);
		sg = alloc_sglist(param->sglen, param->length,
				param->vary, dev, dev->out_pipe);
		अगर (!sg) अणु
			retval = -ENOMEM;
			अवरोध;
		पूर्ण
		/* FIRMWARE:  bulk sink (maybe accepts लघु ग_लिखोs) */
		retval = perक्रमm_sglist(dev, param->iterations, dev->out_pipe,
				&req, sg, param->sglen);
		मुक्त_sglist(sg, param->sglen);
		अवरोध;
	हाल 8:
		अगर (dev->in_pipe == 0 || param->sglen == 0 || param->vary == 0)
			अवरोध;
		dev_info(&पूर्णांकf->dev,
			"TEST 8:  read/%d %d sglists %d entries 0..%d bytes\n",
				param->vary, param->iterations,
				param->sglen, param->length);
		sg = alloc_sglist(param->sglen, param->length,
				param->vary, dev, dev->in_pipe);
		अगर (!sg) अणु
			retval = -ENOMEM;
			अवरोध;
		पूर्ण
		/* FIRMWARE:  bulk source (maybe generates लघु ग_लिखोs) */
		retval = perक्रमm_sglist(dev, param->iterations, dev->in_pipe,
				&req, sg, param->sglen);
		मुक्त_sglist(sg, param->sglen);
		अवरोध;

	/* non-queued sanity tests क्रम control (chapter 9 subset) */
	हाल 9:
		retval = 0;
		dev_info(&पूर्णांकf->dev,
			"TEST 9:  ch9 (subset) control tests, %d times\n",
				param->iterations);
		क्रम (i = param->iterations; retval == 0 && i--; /* NOP */)
			retval = ch9_postconfig(dev);
		अगर (retval)
			dev_err(&पूर्णांकf->dev, "ch9 subset failed, "
					"iterations left %d\n", i);
		अवरोध;

	/* queued control messaging */
	हाल 10:
		retval = 0;
		dev_info(&पूर्णांकf->dev,
				"TEST 10:  queue %d control calls, %d times\n",
				param->sglen,
				param->iterations);
		retval = test_ctrl_queue(dev, param);
		अवरोध;

	/* simple non-queued unlinks (ring with one urb) */
	हाल 11:
		अगर (dev->in_pipe == 0 || !param->length)
			अवरोध;
		retval = 0;
		dev_info(&पूर्णांकf->dev, "TEST 11:  unlink %d reads of %d\n",
				param->iterations, param->length);
		क्रम (i = param->iterations; retval == 0 && i--; /* NOP */)
			retval = unlink_simple(dev, dev->in_pipe,
						param->length);
		अगर (retval)
			dev_err(&पूर्णांकf->dev, "unlink reads failed %d, "
				"iterations left %d\n", retval, i);
		अवरोध;
	हाल 12:
		अगर (dev->out_pipe == 0 || !param->length)
			अवरोध;
		retval = 0;
		dev_info(&पूर्णांकf->dev, "TEST 12:  unlink %d writes of %d\n",
				param->iterations, param->length);
		क्रम (i = param->iterations; retval == 0 && i--; /* NOP */)
			retval = unlink_simple(dev, dev->out_pipe,
						param->length);
		अगर (retval)
			dev_err(&पूर्णांकf->dev, "unlink writes failed %d, "
				"iterations left %d\n", retval, i);
		अवरोध;

	/* ep halt tests */
	हाल 13:
		अगर (dev->out_pipe == 0 && dev->in_pipe == 0)
			अवरोध;
		retval = 0;
		dev_info(&पूर्णांकf->dev, "TEST 13:  set/clear %d halts\n",
				param->iterations);
		क्रम (i = param->iterations; retval == 0 && i--; /* NOP */)
			retval = halt_simple(dev);

		अगर (retval)
			ERROR(dev, "halts failed, iterations left %d\n", i);
		अवरोध;

	/* control ग_लिखो tests */
	हाल 14:
		अगर (!dev->info->ctrl_out)
			अवरोध;
		dev_info(&पूर्णांकf->dev, "TEST 14:  %d ep0out, %d..%d vary %d\n",
				param->iterations,
				realworld ? 1 : 0, param->length,
				param->vary);
		retval = ctrl_out(dev, param->iterations,
				param->length, param->vary, 0);
		अवरोध;

	/* iso ग_लिखो tests */
	हाल 15:
		अगर (dev->out_iso_pipe == 0 || param->sglen == 0)
			अवरोध;
		dev_info(&पूर्णांकf->dev,
			"TEST 15:  write %d iso, %d entries of %d bytes\n",
				param->iterations,
				param->sglen, param->length);
		/* FIRMWARE:  iso sink */
		retval = test_queue(dev, param,
				dev->out_iso_pipe, dev->iso_out, 0);
		अवरोध;

	/* iso पढ़ो tests */
	हाल 16:
		अगर (dev->in_iso_pipe == 0 || param->sglen == 0)
			अवरोध;
		dev_info(&पूर्णांकf->dev,
			"TEST 16:  read %d iso, %d entries of %d bytes\n",
				param->iterations,
				param->sglen, param->length);
		/* FIRMWARE:  iso source */
		retval = test_queue(dev, param,
				dev->in_iso_pipe, dev->iso_in, 0);
		अवरोध;

	/* FIXME scatterlist cancel (needs helper thपढ़ो) */

	/* Tests क्रम bulk I/O using DMA mapping by core and odd address */
	हाल 17:
		अगर (dev->out_pipe == 0)
			अवरोध;
		dev_info(&पूर्णांकf->dev,
			"TEST 17:  write odd addr %d bytes %u times core map\n",
			param->length, param->iterations);

		retval = test_unaligned_bulk(
				dev, dev->out_pipe,
				param->length, param->iterations,
				0, "test17");
		अवरोध;

	हाल 18:
		अगर (dev->in_pipe == 0)
			अवरोध;
		dev_info(&पूर्णांकf->dev,
			"TEST 18:  read odd addr %d bytes %u times core map\n",
			param->length, param->iterations);

		retval = test_unaligned_bulk(
				dev, dev->in_pipe,
				param->length, param->iterations,
				0, "test18");
		अवरोध;

	/* Tests क्रम bulk I/O using premapped coherent buffer and odd address */
	हाल 19:
		अगर (dev->out_pipe == 0)
			अवरोध;
		dev_info(&पूर्णांकf->dev,
			"TEST 19:  write odd addr %d bytes %u times premapped\n",
			param->length, param->iterations);

		retval = test_unaligned_bulk(
				dev, dev->out_pipe,
				param->length, param->iterations,
				URB_NO_TRANSFER_DMA_MAP, "test19");
		अवरोध;

	हाल 20:
		अगर (dev->in_pipe == 0)
			अवरोध;
		dev_info(&पूर्णांकf->dev,
			"TEST 20:  read odd addr %d bytes %u times premapped\n",
			param->length, param->iterations);

		retval = test_unaligned_bulk(
				dev, dev->in_pipe,
				param->length, param->iterations,
				URB_NO_TRANSFER_DMA_MAP, "test20");
		अवरोध;

	/* control ग_लिखो tests with unaligned buffer */
	हाल 21:
		अगर (!dev->info->ctrl_out)
			अवरोध;
		dev_info(&पूर्णांकf->dev,
				"TEST 21:  %d ep0out odd addr, %d..%d vary %d\n",
				param->iterations,
				realworld ? 1 : 0, param->length,
				param->vary);
		retval = ctrl_out(dev, param->iterations,
				param->length, param->vary, 1);
		अवरोध;

	/* unaligned iso tests */
	हाल 22:
		अगर (dev->out_iso_pipe == 0 || param->sglen == 0)
			अवरोध;
		dev_info(&पूर्णांकf->dev,
			"TEST 22:  write %d iso odd, %d entries of %d bytes\n",
				param->iterations,
				param->sglen, param->length);
		retval = test_queue(dev, param,
				dev->out_iso_pipe, dev->iso_out, 1);
		अवरोध;

	हाल 23:
		अगर (dev->in_iso_pipe == 0 || param->sglen == 0)
			अवरोध;
		dev_info(&पूर्णांकf->dev,
			"TEST 23:  read %d iso odd, %d entries of %d bytes\n",
				param->iterations,
				param->sglen, param->length);
		retval = test_queue(dev, param,
				dev->in_iso_pipe, dev->iso_in, 1);
		अवरोध;

	/* unlink URBs from a bulk-OUT queue */
	हाल 24:
		अगर (dev->out_pipe == 0 || !param->length || param->sglen < 4)
			अवरोध;
		retval = 0;
		dev_info(&पूर्णांकf->dev, "TEST 24:  unlink from %d queues of "
				"%d %d-byte writes\n",
				param->iterations, param->sglen, param->length);
		क्रम (i = param->iterations; retval == 0 && i > 0; --i) अणु
			retval = unlink_queued(dev, dev->out_pipe,
						param->sglen, param->length);
			अगर (retval) अणु
				dev_err(&पूर्णांकf->dev,
					"unlink queued writes failed %d, "
					"iterations left %d\n", retval, i);
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;

	/* Simple non-queued पूर्णांकerrupt I/O tests */
	हाल 25:
		अगर (dev->out_पूर्णांक_pipe == 0)
			अवरोध;
		dev_info(&पूर्णांकf->dev,
				"TEST 25: write %d bytes %u times\n",
				param->length, param->iterations);
		urb = simple_alloc_urb(udev, dev->out_पूर्णांक_pipe, param->length,
				dev->पूर्णांक_out->bInterval);
		अगर (!urb) अणु
			retval = -ENOMEM;
			अवरोध;
		पूर्ण
		/* FIRMWARE: पूर्णांकerrupt sink (maybe accepts लघु ग_लिखोs) */
		retval = simple_io(dev, urb, param->iterations, 0, 0, "test25");
		simple_मुक्त_urb(urb);
		अवरोध;
	हाल 26:
		अगर (dev->in_पूर्णांक_pipe == 0)
			अवरोध;
		dev_info(&पूर्णांकf->dev,
				"TEST 26: read %d bytes %u times\n",
				param->length, param->iterations);
		urb = simple_alloc_urb(udev, dev->in_पूर्णांक_pipe, param->length,
				dev->पूर्णांक_in->bInterval);
		अगर (!urb) अणु
			retval = -ENOMEM;
			अवरोध;
		पूर्ण
		/* FIRMWARE: पूर्णांकerrupt source (maybe generates लघु ग_लिखोs) */
		retval = simple_io(dev, urb, param->iterations, 0, 0, "test26");
		simple_मुक्त_urb(urb);
		अवरोध;
	हाल 27:
		/* We करो perक्रमmance test, so ignore data compare */
		अगर (dev->out_pipe == 0 || param->sglen == 0 || pattern != 0)
			अवरोध;
		dev_info(&पूर्णांकf->dev,
			"TEST 27: bulk write %dMbytes\n", (param->iterations *
			param->sglen * param->length) / (1024 * 1024));
		retval = test_queue(dev, param,
				dev->out_pipe, शून्य, 0);
		अवरोध;
	हाल 28:
		अगर (dev->in_pipe == 0 || param->sglen == 0 || pattern != 0)
			अवरोध;
		dev_info(&पूर्णांकf->dev,
			"TEST 28: bulk read %dMbytes\n", (param->iterations *
			param->sglen * param->length) / (1024 * 1024));
		retval = test_queue(dev, param,
				dev->in_pipe, शून्य, 0);
		अवरोध;
	/* Test data Toggle/seq_nr clear between bulk out transfers */
	हाल 29:
		अगर (dev->out_pipe == 0)
			अवरोध;
		retval = 0;
		dev_info(&पूर्णांकf->dev, "TEST 29: Clear toggle between bulk writes %d times\n",
				param->iterations);
		क्रम (i = param->iterations; retval == 0 && i > 0; --i)
			retval = toggle_sync_simple(dev);

		अगर (retval)
			ERROR(dev, "toggle sync failed, iterations left %d\n",
			      i);
		अवरोध;
	पूर्ण
	वापस retval;
पूर्ण

/*-------------------------------------------------------------------------*/

/* We only have this one पूर्णांकerface to user space, through usbfs.
 * User mode code can scan usbfs to find N dअगरferent devices (maybe on
 * dअगरferent busses) to use when testing, and allocate one thपढ़ो per
 * test.  So discovery is simplअगरied, and we have no device naming issues.
 *
 * Don't use these only as stress/load tests.  Use them aदीर्घ with with
 * other USB bus activity:  plugging, unplugging, mousing, mp3 playback,
 * video capture, and so on.  Run dअगरferent tests at dअगरferent बार, in
 * dअगरferent sequences.  Nothing here should पूर्णांकeract with other devices,
 * except indirectly by consuming USB bandwidth and CPU resources क्रम test
 * thपढ़ोs and request completion.  But the only way to know that क्रम sure
 * is to test when HC queues are in use by many devices.
 *
 * WARNING:  Because usbfs grअसल udev->dev.sem beक्रमe calling this ioctl(),
 * it locks out usbcore in certain code paths.  Notably, अगर you disconnect
 * the device-under-test, hub_wq will रुको block क्रमever रुकोing क्रम the
 * ioctl to complete ... so that usb_disconnect() can पात the pending
 * urbs and then call usbtest_disconnect().  To पात a test, you're best
 * off just समाप्तing the userspace task and रुकोing क्रम it to निकास.
 */

अटल पूर्णांक
usbtest_ioctl(काष्ठा usb_पूर्णांकerface *पूर्णांकf, अचिन्हित पूर्णांक code, व्योम *buf)
अणु

	काष्ठा usbtest_dev	*dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा usbtest_param_64 *param_64 = buf;
	काष्ठा usbtest_param_32 temp;
	काष्ठा usbtest_param_32 *param_32 = buf;
	काष्ठा बारpec64 start;
	काष्ठा बारpec64 end;
	काष्ठा बारpec64 duration;
	पूर्णांक retval = -EOPNOTSUPP;

	/* FIXME USBDEVFS_CONNECTINFO करोesn't say how fast the device is. */

	pattern = mod_pattern;

	अगर (mutex_lock_पूर्णांकerruptible(&dev->lock))
		वापस -ERESTARTSYS;

	/* FIXME: What अगर a प्रणाली sleep starts जबतक a test is running? */

	/* some devices, like ez-usb शेष devices, need a non-शेष
	 * altsetting to have any active endpoपूर्णांकs.  some tests change
	 * altsettings; क्रमce a शेष so most tests करोn't need to check.
	 */
	अगर (dev->info->alt >= 0) अणु
		अगर (पूर्णांकf->altsetting->desc.bInterfaceNumber) अणु
			retval = -ENODEV;
			जाओ मुक्त_mutex;
		पूर्ण
		retval = set_altsetting(dev, dev->info->alt);
		अगर (retval) अणु
			dev_err(&पूर्णांकf->dev,
					"set altsetting to %d failed, %d\n",
					dev->info->alt, retval);
			जाओ मुक्त_mutex;
		पूर्ण
	पूर्ण

	चयन (code) अणु
	हाल USBTEST_REQUEST_64:
		temp.test_num = param_64->test_num;
		temp.iterations = param_64->iterations;
		temp.length = param_64->length;
		temp.sglen = param_64->sglen;
		temp.vary = param_64->vary;
		param_32 = &temp;
		अवरोध;

	हाल USBTEST_REQUEST_32:
		अवरोध;

	शेष:
		retval = -EOPNOTSUPP;
		जाओ मुक्त_mutex;
	पूर्ण

	kसमय_get_ts64(&start);

	retval = usbtest_करो_ioctl(पूर्णांकf, param_32);
	अगर (retval < 0)
		जाओ मुक्त_mutex;

	kसमय_get_ts64(&end);

	duration = बारpec64_sub(end, start);

	temp.duration_sec = duration.tv_sec;
	temp.duration_usec = duration.tv_nsec/NSEC_PER_USEC;

	चयन (code) अणु
	हाल USBTEST_REQUEST_32:
		param_32->duration_sec = temp.duration_sec;
		param_32->duration_usec = temp.duration_usec;
		अवरोध;

	हाल USBTEST_REQUEST_64:
		param_64->duration_sec = temp.duration_sec;
		param_64->duration_usec = temp.duration_usec;
		अवरोध;
	पूर्ण

मुक्त_mutex:
	mutex_unlock(&dev->lock);
	वापस retval;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल अचिन्हित क्रमce_पूर्णांकerrupt;
module_param(क्रमce_पूर्णांकerrupt, uपूर्णांक, 0);
MODULE_PARM_DESC(क्रमce_पूर्णांकerrupt, "0 = test default; else interrupt");

#अगर_घोषित	GENERIC
अटल अचिन्हित लघु venकरोr;
module_param(venकरोr, uलघु, 0);
MODULE_PARM_DESC(venकरोr, "vendor code (from usb-if)");

अटल अचिन्हित लघु product;
module_param(product, uलघु, 0);
MODULE_PARM_DESC(product, "product code (from vendor)");
#पूर्ण_अगर

अटल पूर्णांक
usbtest_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device	*udev;
	काष्ठा usbtest_dev	*dev;
	काष्ठा usbtest_info	*info;
	अक्षर			*rtest, *wtest;
	अक्षर			*irtest, *iwtest;
	अक्षर			*पूर्णांकrtest, *पूर्णांकwtest;

	udev = पूर्णांकerface_to_usbdev(पूर्णांकf);

#अगर_घोषित	GENERIC
	/* specअगरy devices by module parameters? */
	अगर (id->match_flags == 0) अणु
		/* venकरोr match required, product match optional */
		अगर (!venकरोr || le16_to_cpu(udev->descriptor.idVenकरोr) != (u16)venकरोr)
			वापस -ENODEV;
		अगर (product && le16_to_cpu(udev->descriptor.idProduct) != (u16)product)
			वापस -ENODEV;
		dev_info(&पूर्णांकf->dev, "matched module params, "
					"vend=0x%04x prod=0x%04x\n",
				le16_to_cpu(udev->descriptor.idVenकरोr),
				le16_to_cpu(udev->descriptor.idProduct));
	पूर्ण
#पूर्ण_अगर

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;
	info = (काष्ठा usbtest_info *) id->driver_info;
	dev->info = info;
	mutex_init(&dev->lock);

	dev->पूर्णांकf = पूर्णांकf;

	/* cacheline-aligned scratch क्रम i/o */
	dev->buf = kदो_स्मृति(TBUF_SIZE, GFP_KERNEL);
	अगर (dev->buf == शून्य) अणु
		kमुक्त(dev);
		वापस -ENOMEM;
	पूर्ण

	/* NOTE this करोesn't yet test the handful of dअगरference that are
	 * visible with high speed पूर्णांकerrupts:  bigger maxpacket (1K) and
	 * "high bandwidth" modes (up to 3 packets/uframe).
	 */
	rtest = wtest = "";
	irtest = iwtest = "";
	पूर्णांकrtest = पूर्णांकwtest = "";
	अगर (क्रमce_पूर्णांकerrupt || udev->speed == USB_SPEED_LOW) अणु
		अगर (info->ep_in) अणु
			dev->in_pipe = usb_rcvपूर्णांकpipe(udev, info->ep_in);
			rtest = " intr-in";
		पूर्ण
		अगर (info->ep_out) अणु
			dev->out_pipe = usb_sndपूर्णांकpipe(udev, info->ep_out);
			wtest = " intr-out";
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (override_alt >= 0 || info->स्वतःconf) अणु
			पूर्णांक status;

			status = get_endpoपूर्णांकs(dev, पूर्णांकf);
			अगर (status < 0) अणु
				WARNING(dev, "couldn't get endpoints, %d\n",
						status);
				kमुक्त(dev->buf);
				kमुक्त(dev);
				वापस status;
			पूर्ण
			/* may find bulk or ISO pipes */
		पूर्ण अन्यथा अणु
			अगर (info->ep_in)
				dev->in_pipe = usb_rcvbulkpipe(udev,
							info->ep_in);
			अगर (info->ep_out)
				dev->out_pipe = usb_sndbulkpipe(udev,
							info->ep_out);
		पूर्ण
		अगर (dev->in_pipe)
			rtest = " bulk-in";
		अगर (dev->out_pipe)
			wtest = " bulk-out";
		अगर (dev->in_iso_pipe)
			irtest = " iso-in";
		अगर (dev->out_iso_pipe)
			iwtest = " iso-out";
		अगर (dev->in_पूर्णांक_pipe)
			पूर्णांकrtest = " int-in";
		अगर (dev->out_पूर्णांक_pipe)
			पूर्णांकwtest = " int-out";
	पूर्ण

	usb_set_पूर्णांकfdata(पूर्णांकf, dev);
	dev_info(&पूर्णांकf->dev, "%s\n", info->name);
	dev_info(&पूर्णांकf->dev, "%s {control%s%s%s%s%s%s%s} tests%s\n",
			usb_speed_string(udev->speed),
			info->ctrl_out ? " in/out" : "",
			rtest, wtest,
			irtest, iwtest,
			पूर्णांकrtest, पूर्णांकwtest,
			info->alt >= 0 ? " (+alt)" : "");
	वापस 0;
पूर्ण

अटल पूर्णांक usbtest_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक usbtest_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस 0;
पूर्ण


अटल व्योम usbtest_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usbtest_dev	*dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	dev_dbg(&पूर्णांकf->dev, "disconnect\n");
	kमुक्त(dev->buf);
	kमुक्त(dev);
पूर्ण

/* Basic testing only needs a device that can source or sink bulk traffic.
 * Any device can test control transfers (शेष with GENERIC binding).
 *
 * Several entries work with the शेष EP0 implementation that's built
 * पूर्णांकo EZ-USB chips.  There's a शेष venकरोr ID which can be overridden
 * by (very) small config EEPROMS, but otherwise all these devices act
 * identically until firmware is loaded:  only EP0 works.  It turns out
 * to be easy to make other endpoपूर्णांकs work, without modअगरying that EP0
 * behavior.  For now, we expect that kind of firmware.
 */

/* an21xx or fx versions of ez-usb */
अटल काष्ठा usbtest_info ez1_info = अणु
	.name		= "EZ-USB device",
	.ep_in		= 2,
	.ep_out		= 2,
	.alt		= 1,
पूर्ण;

/* fx2 version of ez-usb */
अटल काष्ठा usbtest_info ez2_info = अणु
	.name		= "FX2 device",
	.ep_in		= 6,
	.ep_out		= 2,
	.alt		= 1,
पूर्ण;

/* ezusb family device with dedicated usb test firmware,
 */
अटल काष्ठा usbtest_info fw_info = अणु
	.name		= "usb test device",
	.ep_in		= 2,
	.ep_out		= 2,
	.alt		= 1,
	.स्वतःconf	= 1,		/* iso and ctrl_out need स्वतःconf */
	.ctrl_out	= 1,
	.iso		= 1,		/* iso_ep's are #8 in/out */
पूर्ण;

/* peripheral running Linux and 'zero.c' test firmware, or
 * its user-mode cousin. dअगरferent versions of this use
 * dअगरferent hardware with the same venकरोr/product codes.
 * host side MUST rely on the endpoपूर्णांक descriptors.
 */
अटल काष्ठा usbtest_info gz_info = अणु
	.name		= "Linux gadget zero",
	.स्वतःconf	= 1,
	.ctrl_out	= 1,
	.iso		= 1,
	.पूर्णांकr		= 1,
	.alt		= 0,
पूर्ण;

अटल काष्ठा usbtest_info um_info = अणु
	.name		= "Linux user mode test driver",
	.स्वतःconf	= 1,
	.alt		= -1,
पूर्ण;

अटल काष्ठा usbtest_info um2_info = अणु
	.name		= "Linux user mode ISO test driver",
	.स्वतःconf	= 1,
	.iso		= 1,
	.alt		= -1,
पूर्ण;

#अगर_घोषित IBOT2
/* this is a nice source of high speed bulk data;
 * uses an FX2, with firmware provided in the device
 */
अटल काष्ठा usbtest_info ibot2_info = अणु
	.name		= "iBOT2 webcam",
	.ep_in		= 2,
	.alt		= -1,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित GENERIC
/* we can use any device to test control traffic */
अटल काष्ठा usbtest_info generic_info = अणु
	.name		= "Generic USB device",
	.alt		= -1,
पूर्ण;
#पूर्ण_अगर


अटल स्थिर काष्ठा usb_device_id id_table[] = अणु

	/*-------------------------------------------------------------*/

	/* EZ-USB devices which करोwnload firmware to replace (or in our
	 * हाल augment) the शेष device implementation.
	 */

	/* generic EZ-USB FX controller */
	अणु USB_DEVICE(0x0547, 0x2235),
		.driver_info = (अचिन्हित दीर्घ) &ez1_info,
	पूर्ण,

	/* CY3671 development board with EZ-USB FX */
	अणु USB_DEVICE(0x0547, 0x0080),
		.driver_info = (अचिन्हित दीर्घ) &ez1_info,
	पूर्ण,

	/* generic EZ-USB FX2 controller (or development board) */
	अणु USB_DEVICE(0x04b4, 0x8613),
		.driver_info = (अचिन्हित दीर्घ) &ez2_info,
	पूर्ण,

	/* re-क्रमागतerated usb test device firmware */
	अणु USB_DEVICE(0xfff0, 0xfff0),
		.driver_info = (अचिन्हित दीर्घ) &fw_info,
	पूर्ण,

	/* "Gadget Zero" firmware runs under Linux */
	अणु USB_DEVICE(0x0525, 0xa4a0),
		.driver_info = (अचिन्हित दीर्घ) &gz_info,
	पूर्ण,

	/* so करोes a user-mode variant */
	अणु USB_DEVICE(0x0525, 0xa4a4),
		.driver_info = (अचिन्हित दीर्घ) &um_info,
	पूर्ण,

	/* ... and a user-mode variant that talks iso */
	अणु USB_DEVICE(0x0525, 0xa4a3),
		.driver_info = (अचिन्हित दीर्घ) &um2_info,
	पूर्ण,

#अगर_घोषित KEYSPAN_19Qi
	/* Keyspan 19qi uses an21xx (original EZ-USB) */
	/* this करोes not coexist with the real Keyspan 19qi driver! */
	अणु USB_DEVICE(0x06cd, 0x010b),
		.driver_info = (अचिन्हित दीर्घ) &ez1_info,
	पूर्ण,
#पूर्ण_अगर

	/*-------------------------------------------------------------*/

#अगर_घोषित IBOT2
	/* iBOT2 makes a nice source of high speed bulk-in data */
	/* this करोes not coexist with a real iBOT2 driver! */
	अणु USB_DEVICE(0x0b62, 0x0059),
		.driver_info = (अचिन्हित दीर्घ) &ibot2_info,
	पूर्ण,
#पूर्ण_अगर

	/*-------------------------------------------------------------*/

#अगर_घोषित GENERIC
	/* module params can specअगरy devices to use क्रम control tests */
	अणु .driver_info = (अचिन्हित दीर्घ) &generic_info, पूर्ण,
#पूर्ण_अगर

	/*-------------------------------------------------------------*/

	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

अटल काष्ठा usb_driver usbtest_driver = अणु
	.name =		"usbtest",
	.id_table =	id_table,
	.probe =	usbtest_probe,
	.unlocked_ioctl = usbtest_ioctl,
	.disconnect =	usbtest_disconnect,
	.suspend =	usbtest_suspend,
	.resume =	usbtest_resume,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक __init usbtest_init(व्योम)
अणु
#अगर_घोषित GENERIC
	अगर (venकरोr)
		pr_debug("params: vend=0x%04x prod=0x%04x\n", venकरोr, product);
#पूर्ण_अगर
	वापस usb_रेजिस्टर(&usbtest_driver);
पूर्ण
module_init(usbtest_init);

अटल व्योम __निकास usbtest_निकास(व्योम)
अणु
	usb_deरेजिस्टर(&usbtest_driver);
पूर्ण
module_निकास(usbtest_निकास);

MODULE_DESCRIPTION("USB Core/HCD Testing Driver");
MODULE_LICENSE("GPL");

