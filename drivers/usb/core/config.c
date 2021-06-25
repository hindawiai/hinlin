<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Released under the GPLv2 only.
 */

#समावेश <linux/usb.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/usb/quirks.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <यंत्र/byteorder.h>
#समावेश "usb.h"


#घोषणा USB_MAXALTSETTING		128	/* Hard limit */

#घोषणा USB_MAXCONFIG			8	/* Arbitrary limit */


अटल अंतरभूत स्थिर अक्षर *plural(पूर्णांक n)
अणु
	वापस (n == 1 ? "" : "s");
पूर्ण

अटल पूर्णांक find_next_descriptor(अचिन्हित अक्षर *buffer, पूर्णांक size,
    पूर्णांक dt1, पूर्णांक dt2, पूर्णांक *num_skipped)
अणु
	काष्ठा usb_descriptor_header *h;
	पूर्णांक n = 0;
	अचिन्हित अक्षर *buffer0 = buffer;

	/* Find the next descriptor of type dt1 or dt2 */
	जबतक (size > 0) अणु
		h = (काष्ठा usb_descriptor_header *) buffer;
		अगर (h->bDescriptorType == dt1 || h->bDescriptorType == dt2)
			अवरोध;
		buffer += h->bLength;
		size -= h->bLength;
		++n;
	पूर्ण

	/* Store the number of descriptors skipped and वापस the
	 * number of bytes skipped */
	अगर (num_skipped)
		*num_skipped = n;
	वापस buffer - buffer0;
पूर्ण

अटल व्योम usb_parse_ssp_isoc_endpoपूर्णांक_companion(काष्ठा device *ddev,
		पूर्णांक cfgno, पूर्णांक inum, पूर्णांक asnum, काष्ठा usb_host_endpoपूर्णांक *ep,
		अचिन्हित अक्षर *buffer, पूर्णांक size)
अणु
	काष्ठा usb_ssp_isoc_ep_comp_descriptor *desc;

	/*
	 * The SuperSpeedPlus Isoc endpoपूर्णांक companion descriptor immediately
	 * follows the SuperSpeed Endpoपूर्णांक Companion descriptor
	 */
	desc = (काष्ठा usb_ssp_isoc_ep_comp_descriptor *) buffer;
	अगर (desc->bDescriptorType != USB_DT_SSP_ISOC_ENDPOINT_COMP ||
	    size < USB_DT_SSP_ISOC_EP_COMP_SIZE) अणु
		dev_warn(ddev, "Invalid SuperSpeedPlus isoc endpoint companion"
			 "for config %d interface %d altsetting %d ep %d.\n",
			 cfgno, inum, asnum, ep->desc.bEndpoपूर्णांकAddress);
		वापस;
	पूर्ण
	स_नकल(&ep->ssp_isoc_ep_comp, desc, USB_DT_SSP_ISOC_EP_COMP_SIZE);
पूर्ण

अटल व्योम usb_parse_ss_endpoपूर्णांक_companion(काष्ठा device *ddev, पूर्णांक cfgno,
		पूर्णांक inum, पूर्णांक asnum, काष्ठा usb_host_endpoपूर्णांक *ep,
		अचिन्हित अक्षर *buffer, पूर्णांक size)
अणु
	काष्ठा usb_ss_ep_comp_descriptor *desc;
	पूर्णांक max_tx;

	/* The SuperSpeed endpoपूर्णांक companion descriptor is supposed to
	 * be the first thing immediately following the endpoपूर्णांक descriptor.
	 */
	desc = (काष्ठा usb_ss_ep_comp_descriptor *) buffer;

	अगर (desc->bDescriptorType != USB_DT_SS_ENDPOINT_COMP ||
			size < USB_DT_SS_EP_COMP_SIZE) अणु
		dev_warn(ddev, "No SuperSpeed endpoint companion for config %d "
				" interface %d altsetting %d ep %d: "
				"using minimum values\n",
				cfgno, inum, asnum, ep->desc.bEndpoपूर्णांकAddress);

		/* Fill in some शेष values.
		 * Leave bmAttributes as zero, which will mean no streams क्रम
		 * bulk, and isoc won't support multiple bursts of packets.
		 * With bursts of only one packet, and a Mult of 1, the max
		 * amount of data moved per endpoपूर्णांक service पूर्णांकerval is one
		 * packet.
		 */
		ep->ss_ep_comp.bLength = USB_DT_SS_EP_COMP_SIZE;
		ep->ss_ep_comp.bDescriptorType = USB_DT_SS_ENDPOINT_COMP;
		अगर (usb_endpoपूर्णांक_xfer_isoc(&ep->desc) ||
				usb_endpoपूर्णांक_xfer_पूर्णांक(&ep->desc))
			ep->ss_ep_comp.wBytesPerInterval =
					ep->desc.wMaxPacketSize;
		वापस;
	पूर्ण
	buffer += desc->bLength;
	size -= desc->bLength;
	स_नकल(&ep->ss_ep_comp, desc, USB_DT_SS_EP_COMP_SIZE);

	/* Check the various values */
	अगर (usb_endpoपूर्णांक_xfer_control(&ep->desc) && desc->bMaxBurst != 0) अणु
		dev_warn(ddev, "Control endpoint with bMaxBurst = %d in "
				"config %d interface %d altsetting %d ep %d: "
				"setting to zero\n", desc->bMaxBurst,
				cfgno, inum, asnum, ep->desc.bEndpoपूर्णांकAddress);
		ep->ss_ep_comp.bMaxBurst = 0;
	पूर्ण अन्यथा अगर (desc->bMaxBurst > 15) अणु
		dev_warn(ddev, "Endpoint with bMaxBurst = %d in "
				"config %d interface %d altsetting %d ep %d: "
				"setting to 15\n", desc->bMaxBurst,
				cfgno, inum, asnum, ep->desc.bEndpoपूर्णांकAddress);
		ep->ss_ep_comp.bMaxBurst = 15;
	पूर्ण

	अगर ((usb_endpoपूर्णांक_xfer_control(&ep->desc) ||
			usb_endpoपूर्णांक_xfer_पूर्णांक(&ep->desc)) &&
				desc->bmAttributes != 0) अणु
		dev_warn(ddev, "%s endpoint with bmAttributes = %d in "
				"config %d interface %d altsetting %d ep %d: "
				"setting to zero\n",
				usb_endpoपूर्णांक_xfer_control(&ep->desc) ? "Control" : "Bulk",
				desc->bmAttributes,
				cfgno, inum, asnum, ep->desc.bEndpoपूर्णांकAddress);
		ep->ss_ep_comp.bmAttributes = 0;
	पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_xfer_bulk(&ep->desc) &&
			desc->bmAttributes > 16) अणु
		dev_warn(ddev, "Bulk endpoint with more than 65536 streams in "
				"config %d interface %d altsetting %d ep %d: "
				"setting to max\n",
				cfgno, inum, asnum, ep->desc.bEndpoपूर्णांकAddress);
		ep->ss_ep_comp.bmAttributes = 16;
	पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_xfer_isoc(&ep->desc) &&
		   !USB_SS_SSP_ISOC_COMP(desc->bmAttributes) &&
		   USB_SS_MULT(desc->bmAttributes) > 3) अणु
		dev_warn(ddev, "Isoc endpoint has Mult of %d in "
				"config %d interface %d altsetting %d ep %d: "
				"setting to 3\n",
				USB_SS_MULT(desc->bmAttributes),
				cfgno, inum, asnum, ep->desc.bEndpoपूर्णांकAddress);
		ep->ss_ep_comp.bmAttributes = 2;
	पूर्ण

	अगर (usb_endpoपूर्णांक_xfer_isoc(&ep->desc))
		max_tx = (desc->bMaxBurst + 1) *
			(USB_SS_MULT(desc->bmAttributes)) *
			usb_endpoपूर्णांक_maxp(&ep->desc);
	अन्यथा अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(&ep->desc))
		max_tx = usb_endpoपूर्णांक_maxp(&ep->desc) *
			(desc->bMaxBurst + 1);
	अन्यथा
		max_tx = 999999;
	अगर (le16_to_cpu(desc->wBytesPerInterval) > max_tx) अणु
		dev_warn(ddev, "%s endpoint with wBytesPerInterval of %d in "
				"config %d interface %d altsetting %d ep %d: "
				"setting to %d\n",
				usb_endpoपूर्णांक_xfer_isoc(&ep->desc) ? "Isoc" : "Int",
				le16_to_cpu(desc->wBytesPerInterval),
				cfgno, inum, asnum, ep->desc.bEndpoपूर्णांकAddress,
				max_tx);
		ep->ss_ep_comp.wBytesPerInterval = cpu_to_le16(max_tx);
	पूर्ण
	/* Parse a possible SuperSpeedPlus isoc ep companion descriptor */
	अगर (usb_endpoपूर्णांक_xfer_isoc(&ep->desc) &&
	    USB_SS_SSP_ISOC_COMP(desc->bmAttributes))
		usb_parse_ssp_isoc_endpoपूर्णांक_companion(ddev, cfgno, inum, asnum,
							ep, buffer, size);
पूर्ण

अटल स्थिर अचिन्हित लघु low_speed_maxpacket_maxes[4] = अणु
	[USB_ENDPOINT_XFER_CONTROL] = 8,
	[USB_ENDPOINT_XFER_ISOC] = 0,
	[USB_ENDPOINT_XFER_BULK] = 0,
	[USB_ENDPOINT_XFER_INT] = 8,
पूर्ण;
अटल स्थिर अचिन्हित लघु full_speed_maxpacket_maxes[4] = अणु
	[USB_ENDPOINT_XFER_CONTROL] = 64,
	[USB_ENDPOINT_XFER_ISOC] = 1023,
	[USB_ENDPOINT_XFER_BULK] = 64,
	[USB_ENDPOINT_XFER_INT] = 64,
पूर्ण;
अटल स्थिर अचिन्हित लघु high_speed_maxpacket_maxes[4] = अणु
	[USB_ENDPOINT_XFER_CONTROL] = 64,
	[USB_ENDPOINT_XFER_ISOC] = 1024,

	/* Bulk should be 512, but some devices use 1024: we will warn below */
	[USB_ENDPOINT_XFER_BULK] = 1024,
	[USB_ENDPOINT_XFER_INT] = 1024,
पूर्ण;
अटल स्थिर अचिन्हित लघु super_speed_maxpacket_maxes[4] = अणु
	[USB_ENDPOINT_XFER_CONTROL] = 512,
	[USB_ENDPOINT_XFER_ISOC] = 1024,
	[USB_ENDPOINT_XFER_BULK] = 1024,
	[USB_ENDPOINT_XFER_INT] = 1024,
पूर्ण;

अटल bool endpoपूर्णांक_is_duplicate(काष्ठा usb_endpoपूर्णांक_descriptor *e1,
		काष्ठा usb_endpoपूर्णांक_descriptor *e2)
अणु
	अगर (e1->bEndpoपूर्णांकAddress == e2->bEndpoपूर्णांकAddress)
		वापस true;

	अगर (usb_endpoपूर्णांक_xfer_control(e1) || usb_endpoपूर्णांक_xfer_control(e2)) अणु
		अगर (usb_endpoपूर्णांक_num(e1) == usb_endpoपूर्णांक_num(e2))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Check क्रम duplicate endpoपूर्णांक addresses in other पूर्णांकerfaces and in the
 * altsetting currently being parsed.
 */
अटल bool config_endpoपूर्णांक_is_duplicate(काष्ठा usb_host_config *config,
		पूर्णांक inum, पूर्णांक asnum, काष्ठा usb_endpoपूर्णांक_descriptor *d)
अणु
	काष्ठा usb_endpoपूर्णांक_descriptor *epd;
	काष्ठा usb_पूर्णांकerface_cache *पूर्णांकfc;
	काष्ठा usb_host_पूर्णांकerface *alt;
	पूर्णांक i, j, k;

	क्रम (i = 0; i < config->desc.bNumInterfaces; ++i) अणु
		पूर्णांकfc = config->पूर्णांकf_cache[i];

		क्रम (j = 0; j < पूर्णांकfc->num_altsetting; ++j) अणु
			alt = &पूर्णांकfc->altsetting[j];

			अगर (alt->desc.bInterfaceNumber == inum &&
					alt->desc.bAlternateSetting != asnum)
				जारी;

			क्रम (k = 0; k < alt->desc.bNumEndpoपूर्णांकs; ++k) अणु
				epd = &alt->endpoपूर्णांक[k].desc;

				अगर (endpoपूर्णांक_is_duplicate(epd, d))
					वापस true;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक usb_parse_endpoपूर्णांक(काष्ठा device *ddev, पूर्णांक cfgno,
		काष्ठा usb_host_config *config, पूर्णांक inum, पूर्णांक asnum,
		काष्ठा usb_host_पूर्णांकerface *अगरp, पूर्णांक num_ep,
		अचिन्हित अक्षर *buffer, पूर्णांक size)
अणु
	काष्ठा usb_device *udev = to_usb_device(ddev);
	अचिन्हित अक्षर *buffer0 = buffer;
	काष्ठा usb_endpoपूर्णांक_descriptor *d;
	काष्ठा usb_host_endpoपूर्णांक *endpoपूर्णांक;
	पूर्णांक n, i, j, retval;
	अचिन्हित पूर्णांक maxp;
	स्थिर अचिन्हित लघु *maxpacket_maxes;

	d = (काष्ठा usb_endpoपूर्णांक_descriptor *) buffer;
	buffer += d->bLength;
	size -= d->bLength;

	अगर (d->bLength >= USB_DT_ENDPOINT_AUDIO_SIZE)
		n = USB_DT_ENDPOINT_AUDIO_SIZE;
	अन्यथा अगर (d->bLength >= USB_DT_ENDPOINT_SIZE)
		n = USB_DT_ENDPOINT_SIZE;
	अन्यथा अणु
		dev_warn(ddev, "config %d interface %d altsetting %d has an "
		    "invalid endpoint descriptor of length %d, skipping\n",
		    cfgno, inum, asnum, d->bLength);
		जाओ skip_to_next_endpoपूर्णांक_or_पूर्णांकerface_descriptor;
	पूर्ण

	i = d->bEndpoपूर्णांकAddress & ~USB_ENDPOINT_सूची_MASK;
	अगर (i >= 16 || i == 0) अणु
		dev_warn(ddev, "config %d interface %d altsetting %d has an "
		    "invalid endpoint with address 0x%X, skipping\n",
		    cfgno, inum, asnum, d->bEndpoपूर्णांकAddress);
		जाओ skip_to_next_endpoपूर्णांक_or_पूर्णांकerface_descriptor;
	पूर्ण

	/* Only store as many endpoपूर्णांकs as we have room क्रम */
	अगर (अगरp->desc.bNumEndpoपूर्णांकs >= num_ep)
		जाओ skip_to_next_endpoपूर्णांक_or_पूर्णांकerface_descriptor;

	/* Check क्रम duplicate endpoपूर्णांक addresses */
	अगर (config_endpoपूर्णांक_is_duplicate(config, inum, asnum, d)) अणु
		dev_warn(ddev, "config %d interface %d altsetting %d has a duplicate endpoint with address 0x%X, skipping\n",
				cfgno, inum, asnum, d->bEndpoपूर्णांकAddress);
		जाओ skip_to_next_endpoपूर्णांक_or_पूर्णांकerface_descriptor;
	पूर्ण

	/* Ignore some endpoपूर्णांकs */
	अगर (udev->quirks & USB_QUIRK_ENDPOINT_IGNORE) अणु
		अगर (usb_endpoपूर्णांक_is_ignored(udev, अगरp, d)) अणु
			dev_warn(ddev, "config %d interface %d altsetting %d has an ignored endpoint with address 0x%X, skipping\n",
					cfgno, inum, asnum,
					d->bEndpoपूर्णांकAddress);
			जाओ skip_to_next_endpoपूर्णांक_or_पूर्णांकerface_descriptor;
		पूर्ण
	पूर्ण

	endpoपूर्णांक = &अगरp->endpoपूर्णांक[अगरp->desc.bNumEndpoपूर्णांकs];
	++अगरp->desc.bNumEndpoपूर्णांकs;

	स_नकल(&endpoपूर्णांक->desc, d, n);
	INIT_LIST_HEAD(&endpoपूर्णांक->urb_list);

	/*
	 * Fix up bInterval values outside the legal range.
	 * Use 10 or 8 ms अगर no proper value can be guessed.
	 */
	i = 0;		/* i = min, j = max, n = शेष */
	j = 255;
	अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(d)) अणु
		i = 1;
		चयन (udev->speed) अणु
		हाल USB_SPEED_SUPER_PLUS:
		हाल USB_SPEED_SUPER:
		हाल USB_SPEED_HIGH:
			/*
			 * Many device manufacturers are using full-speed
			 * bInterval values in high-speed पूर्णांकerrupt endpoपूर्णांक
			 * descriptors. Try to fix those and fall back to an
			 * 8-ms शेष value otherwise.
			 */
			n = fls(d->bInterval*8);
			अगर (n == 0)
				n = 7;	/* 8 ms = 2^(7-1) uframes */
			j = 16;

			/*
			 * Adjust bInterval क्रम quirked devices.
			 */
			/*
			 * This quirk fixes bIntervals reported in ms.
			 */
			अगर (udev->quirks & USB_QUIRK_LINEAR_FRAME_INTR_BINTERVAL) अणु
				n = clamp(fls(d->bInterval) + 3, i, j);
				i = j = n;
			पूर्ण
			/*
			 * This quirk fixes bIntervals reported in
			 * linear microframes.
			 */
			अगर (udev->quirks & USB_QUIRK_LINEAR_UFRAME_INTR_BINTERVAL) अणु
				n = clamp(fls(d->bInterval), i, j);
				i = j = n;
			पूर्ण
			अवरोध;
		शेष:		/* USB_SPEED_FULL or _LOW */
			/*
			 * For low-speed, 10 ms is the official minimum.
			 * But some "overclocked" devices might want faster
			 * polling so we'll allow it.
			 */
			n = 10;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_xfer_isoc(d)) अणु
		i = 1;
		j = 16;
		चयन (udev->speed) अणु
		हाल USB_SPEED_HIGH:
			n = 7;		/* 8 ms = 2^(7-1) uframes */
			अवरोध;
		शेष:		/* USB_SPEED_FULL */
			n = 4;		/* 8 ms = 2^(4-1) frames */
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (d->bInterval < i || d->bInterval > j) अणु
		dev_warn(ddev, "config %d interface %d altsetting %d "
		    "endpoint 0x%X has an invalid bInterval %d, "
		    "changing to %d\n",
		    cfgno, inum, asnum,
		    d->bEndpoपूर्णांकAddress, d->bInterval, n);
		endpoपूर्णांक->desc.bInterval = n;
	पूर्ण

	/* Some buggy low-speed devices have Bulk endpoपूर्णांकs, which is
	 * explicitly क्रमbidden by the USB spec.  In an attempt to make
	 * them usable, we will try treating them as Interrupt endpoपूर्णांकs.
	 */
	अगर (udev->speed == USB_SPEED_LOW && usb_endpoपूर्णांक_xfer_bulk(d)) अणु
		dev_warn(ddev, "config %d interface %d altsetting %d "
		    "endpoint 0x%X is Bulk; changing to Interrupt\n",
		    cfgno, inum, asnum, d->bEndpoपूर्णांकAddress);
		endpoपूर्णांक->desc.bmAttributes = USB_ENDPOINT_XFER_INT;
		endpoपूर्णांक->desc.bInterval = 1;
		अगर (usb_endpoपूर्णांक_maxp(&endpoपूर्णांक->desc) > 8)
			endpoपूर्णांक->desc.wMaxPacketSize = cpu_to_le16(8);
	पूर्ण

	/*
	 * Validate the wMaxPacketSize field.
	 * Some devices have isochronous endpoपूर्णांकs in altsetting 0;
	 * the USB-2 spec requires such endpoपूर्णांकs to have wMaxPacketSize = 0
	 * (see the end of section 5.6.3), so करोn't warn about them.
	 */
	maxp = usb_endpoपूर्णांक_maxp(&endpoपूर्णांक->desc);
	अगर (maxp == 0 && !(usb_endpoपूर्णांक_xfer_isoc(d) && asnum == 0)) अणु
		dev_warn(ddev, "config %d interface %d altsetting %d endpoint 0x%X has invalid wMaxPacketSize 0\n",
		    cfgno, inum, asnum, d->bEndpoपूर्णांकAddress);
	पूर्ण

	/* Find the highest legal maxpacket size क्रम this endpoपूर्णांक */
	i = 0;		/* additional transactions per microframe */
	चयन (udev->speed) अणु
	हाल USB_SPEED_LOW:
		maxpacket_maxes = low_speed_maxpacket_maxes;
		अवरोध;
	हाल USB_SPEED_FULL:
		maxpacket_maxes = full_speed_maxpacket_maxes;
		अवरोध;
	हाल USB_SPEED_HIGH:
		/* Bits 12..11 are allowed only क्रम HS periodic endpoपूर्णांकs */
		अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(d) || usb_endpoपूर्णांक_xfer_isoc(d)) अणु
			i = maxp & (BIT(12) | BIT(11));
			maxp &= ~i;
		पूर्ण
		fallthrough;
	शेष:
		maxpacket_maxes = high_speed_maxpacket_maxes;
		अवरोध;
	हाल USB_SPEED_SUPER:
	हाल USB_SPEED_SUPER_PLUS:
		maxpacket_maxes = super_speed_maxpacket_maxes;
		अवरोध;
	पूर्ण
	j = maxpacket_maxes[usb_endpoपूर्णांक_type(&endpoपूर्णांक->desc)];

	अगर (maxp > j) अणु
		dev_warn(ddev, "config %d interface %d altsetting %d endpoint 0x%X has invalid maxpacket %d, setting to %d\n",
		    cfgno, inum, asnum, d->bEndpoपूर्णांकAddress, maxp, j);
		maxp = j;
		endpoपूर्णांक->desc.wMaxPacketSize = cpu_to_le16(i | maxp);
	पूर्ण

	/*
	 * Some buggy high speed devices have bulk endpoपूर्णांकs using
	 * maxpacket sizes other than 512.  High speed HCDs may not
	 * be able to handle that particular bug, so let's warn...
	 */
	अगर (udev->speed == USB_SPEED_HIGH && usb_endpoपूर्णांक_xfer_bulk(d)) अणु
		अगर (maxp != 512)
			dev_warn(ddev, "config %d interface %d altsetting %d "
				"bulk endpoint 0x%X has invalid maxpacket %d\n",
				cfgno, inum, asnum, d->bEndpoपूर्णांकAddress,
				maxp);
	पूर्ण

	/* Parse a possible SuperSpeed endpoपूर्णांक companion descriptor */
	अगर (udev->speed >= USB_SPEED_SUPER)
		usb_parse_ss_endpoपूर्णांक_companion(ddev, cfgno,
				inum, asnum, endpoपूर्णांक, buffer, size);

	/* Skip over any Class Specअगरic or Venकरोr Specअगरic descriptors;
	 * find the next endpoपूर्णांक or पूर्णांकerface descriptor */
	endpoपूर्णांक->extra = buffer;
	i = find_next_descriptor(buffer, size, USB_DT_ENDPOINT,
			USB_DT_INTERFACE, &n);
	endpoपूर्णांक->extralen = i;
	retval = buffer - buffer0 + i;
	अगर (n > 0)
		dev_dbg(ddev, "skipped %d descriptor%s after %s\n",
		    n, plural(n), "endpoint");
	वापस retval;

skip_to_next_endpoपूर्णांक_or_पूर्णांकerface_descriptor:
	i = find_next_descriptor(buffer, size, USB_DT_ENDPOINT,
	    USB_DT_INTERFACE, शून्य);
	वापस buffer - buffer0 + i;
पूर्ण

व्योम usb_release_पूर्णांकerface_cache(काष्ठा kref *ref)
अणु
	काष्ठा usb_पूर्णांकerface_cache *पूर्णांकfc = ref_to_usb_पूर्णांकerface_cache(ref);
	पूर्णांक j;

	क्रम (j = 0; j < पूर्णांकfc->num_altsetting; j++) अणु
		काष्ठा usb_host_पूर्णांकerface *alt = &पूर्णांकfc->altsetting[j];

		kमुक्त(alt->endpoपूर्णांक);
		kमुक्त(alt->string);
	पूर्ण
	kमुक्त(पूर्णांकfc);
पूर्ण

अटल पूर्णांक usb_parse_पूर्णांकerface(काष्ठा device *ddev, पूर्णांक cfgno,
    काष्ठा usb_host_config *config, अचिन्हित अक्षर *buffer, पूर्णांक size,
    u8 inums[], u8 nalts[])
अणु
	अचिन्हित अक्षर *buffer0 = buffer;
	काष्ठा usb_पूर्णांकerface_descriptor	*d;
	पूर्णांक inum, asnum;
	काष्ठा usb_पूर्णांकerface_cache *पूर्णांकfc;
	काष्ठा usb_host_पूर्णांकerface *alt;
	पूर्णांक i, n;
	पूर्णांक len, retval;
	पूर्णांक num_ep, num_ep_orig;

	d = (काष्ठा usb_पूर्णांकerface_descriptor *) buffer;
	buffer += d->bLength;
	size -= d->bLength;

	अगर (d->bLength < USB_DT_INTERFACE_SIZE)
		जाओ skip_to_next_पूर्णांकerface_descriptor;

	/* Which पूर्णांकerface entry is this? */
	पूर्णांकfc = शून्य;
	inum = d->bInterfaceNumber;
	क्रम (i = 0; i < config->desc.bNumInterfaces; ++i) अणु
		अगर (inums[i] == inum) अणु
			पूर्णांकfc = config->पूर्णांकf_cache[i];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!पूर्णांकfc || पूर्णांकfc->num_altsetting >= nalts[i])
		जाओ skip_to_next_पूर्णांकerface_descriptor;

	/* Check क्रम duplicate altsetting entries */
	asnum = d->bAlternateSetting;
	क्रम ((i = 0, alt = &पूर्णांकfc->altsetting[0]);
	      i < पूर्णांकfc->num_altsetting;
	     (++i, ++alt)) अणु
		अगर (alt->desc.bAlternateSetting == asnum) अणु
			dev_warn(ddev, "Duplicate descriptor for config %d "
			    "interface %d altsetting %d, skipping\n",
			    cfgno, inum, asnum);
			जाओ skip_to_next_पूर्णांकerface_descriptor;
		पूर्ण
	पूर्ण

	++पूर्णांकfc->num_altsetting;
	स_नकल(&alt->desc, d, USB_DT_INTERFACE_SIZE);

	/* Skip over any Class Specअगरic or Venकरोr Specअगरic descriptors;
	 * find the first endpoपूर्णांक or पूर्णांकerface descriptor */
	alt->extra = buffer;
	i = find_next_descriptor(buffer, size, USB_DT_ENDPOINT,
	    USB_DT_INTERFACE, &n);
	alt->extralen = i;
	अगर (n > 0)
		dev_dbg(ddev, "skipped %d descriptor%s after %s\n",
		    n, plural(n), "interface");
	buffer += i;
	size -= i;

	/* Allocate space क्रम the right(?) number of endpoपूर्णांकs */
	num_ep = num_ep_orig = alt->desc.bNumEndpoपूर्णांकs;
	alt->desc.bNumEndpoपूर्णांकs = 0;		/* Use as a counter */
	अगर (num_ep > USB_MAXENDPOINTS) अणु
		dev_warn(ddev, "too many endpoints for config %d interface %d "
		    "altsetting %d: %d, using maximum allowed: %d\n",
		    cfgno, inum, asnum, num_ep, USB_MAXENDPOINTS);
		num_ep = USB_MAXENDPOINTS;
	पूर्ण

	अगर (num_ep > 0) अणु
		/* Can't allocate 0 bytes */
		len = माप(काष्ठा usb_host_endpoपूर्णांक) * num_ep;
		alt->endpoपूर्णांक = kzalloc(len, GFP_KERNEL);
		अगर (!alt->endpoपूर्णांक)
			वापस -ENOMEM;
	पूर्ण

	/* Parse all the endpoपूर्णांक descriptors */
	n = 0;
	जबतक (size > 0) अणु
		अगर (((काष्ठा usb_descriptor_header *) buffer)->bDescriptorType
		     == USB_DT_INTERFACE)
			अवरोध;
		retval = usb_parse_endpoपूर्णांक(ddev, cfgno, config, inum, asnum,
				alt, num_ep, buffer, size);
		अगर (retval < 0)
			वापस retval;
		++n;

		buffer += retval;
		size -= retval;
	पूर्ण

	अगर (n != num_ep_orig)
		dev_warn(ddev, "config %d interface %d altsetting %d has %d "
		    "endpoint descriptor%s, different from the interface "
		    "descriptor's value: %d\n",
		    cfgno, inum, asnum, n, plural(n), num_ep_orig);
	वापस buffer - buffer0;

skip_to_next_पूर्णांकerface_descriptor:
	i = find_next_descriptor(buffer, size, USB_DT_INTERFACE,
	    USB_DT_INTERFACE, शून्य);
	वापस buffer - buffer0 + i;
पूर्ण

अटल पूर्णांक usb_parse_configuration(काष्ठा usb_device *dev, पूर्णांक cfgidx,
    काष्ठा usb_host_config *config, अचिन्हित अक्षर *buffer, पूर्णांक size)
अणु
	काष्ठा device *ddev = &dev->dev;
	अचिन्हित अक्षर *buffer0 = buffer;
	पूर्णांक cfgno;
	पूर्णांक nपूर्णांकf, nपूर्णांकf_orig;
	पूर्णांक i, j, n;
	काष्ठा usb_पूर्णांकerface_cache *पूर्णांकfc;
	अचिन्हित अक्षर *buffer2;
	पूर्णांक size2;
	काष्ठा usb_descriptor_header *header;
	पूर्णांक retval;
	u8 inums[USB_MAXINTERFACES], nalts[USB_MAXINTERFACES];
	अचिन्हित iad_num = 0;

	स_नकल(&config->desc, buffer, USB_DT_CONFIG_SIZE);
	nपूर्णांकf = nपूर्णांकf_orig = config->desc.bNumInterfaces;
	config->desc.bNumInterfaces = 0;	// Adjusted later

	अगर (config->desc.bDescriptorType != USB_DT_CONFIG ||
	    config->desc.bLength < USB_DT_CONFIG_SIZE ||
	    config->desc.bLength > size) अणु
		dev_err(ddev, "invalid descriptor for config index %d: "
		    "type = 0x%X, length = %d\n", cfgidx,
		    config->desc.bDescriptorType, config->desc.bLength);
		वापस -EINVAL;
	पूर्ण
	cfgno = config->desc.bConfigurationValue;

	buffer += config->desc.bLength;
	size -= config->desc.bLength;

	अगर (nपूर्णांकf > USB_MAXINTERFACES) अणु
		dev_warn(ddev, "config %d has too many interfaces: %d, "
		    "using maximum allowed: %d\n",
		    cfgno, nपूर्णांकf, USB_MAXINTERFACES);
		nपूर्णांकf = USB_MAXINTERFACES;
	पूर्ण

	/* Go through the descriptors, checking their length and counting the
	 * number of altsettings क्रम each पूर्णांकerface */
	n = 0;
	क्रम ((buffer2 = buffer, size2 = size);
	      size2 > 0;
	     (buffer2 += header->bLength, size2 -= header->bLength)) अणु

		अगर (size2 < माप(काष्ठा usb_descriptor_header)) अणु
			dev_warn(ddev, "config %d descriptor has %d excess "
			    "byte%s, ignoring\n",
			    cfgno, size2, plural(size2));
			अवरोध;
		पूर्ण

		header = (काष्ठा usb_descriptor_header *) buffer2;
		अगर ((header->bLength > size2) || (header->bLength < 2)) अणु
			dev_warn(ddev, "config %d has an invalid descriptor "
			    "of length %d, skipping remainder of the config\n",
			    cfgno, header->bLength);
			अवरोध;
		पूर्ण

		अगर (header->bDescriptorType == USB_DT_INTERFACE) अणु
			काष्ठा usb_पूर्णांकerface_descriptor *d;
			पूर्णांक inum;

			d = (काष्ठा usb_पूर्णांकerface_descriptor *) header;
			अगर (d->bLength < USB_DT_INTERFACE_SIZE) अणु
				dev_warn(ddev, "config %d has an invalid "
				    "interface descriptor of length %d, "
				    "skipping\n", cfgno, d->bLength);
				जारी;
			पूर्ण

			inum = d->bInterfaceNumber;

			अगर ((dev->quirks & USB_QUIRK_HONOR_BNUMINTERFACES) &&
			    n >= nपूर्णांकf_orig) अणु
				dev_warn(ddev, "config %d has more interface "
				    "descriptors, than it declares in "
				    "bNumInterfaces, ignoring interface "
				    "number: %d\n", cfgno, inum);
				जारी;
			पूर्ण

			अगर (inum >= nपूर्णांकf_orig)
				dev_warn(ddev, "config %d has an invalid "
				    "interface number: %d but max is %d\n",
				    cfgno, inum, nपूर्णांकf_orig - 1);

			/* Have we alपढ़ोy encountered this पूर्णांकerface?
			 * Count its altsettings */
			क्रम (i = 0; i < n; ++i) अणु
				अगर (inums[i] == inum)
					अवरोध;
			पूर्ण
			अगर (i < n) अणु
				अगर (nalts[i] < 255)
					++nalts[i];
			पूर्ण अन्यथा अगर (n < USB_MAXINTERFACES) अणु
				inums[n] = inum;
				nalts[n] = 1;
				++n;
			पूर्ण

		पूर्ण अन्यथा अगर (header->bDescriptorType ==
				USB_DT_INTERFACE_ASSOCIATION) अणु
			काष्ठा usb_पूर्णांकerface_assoc_descriptor *d;

			d = (काष्ठा usb_पूर्णांकerface_assoc_descriptor *)header;
			अगर (d->bLength < USB_DT_INTERFACE_ASSOCIATION_SIZE) अणु
				dev_warn(ddev,
					 "config %d has an invalid interface association descriptor of length %d, skipping\n",
					 cfgno, d->bLength);
				जारी;
			पूर्ण

			अगर (iad_num == USB_MAXIADS) अणु
				dev_warn(ddev, "found more Interface "
					       "Association Descriptors "
					       "than allocated for in "
					       "configuration %d\n", cfgno);
			पूर्ण अन्यथा अणु
				config->पूर्णांकf_assoc[iad_num] = d;
				iad_num++;
			पूर्ण

		पूर्ण अन्यथा अगर (header->bDescriptorType == USB_DT_DEVICE ||
			    header->bDescriptorType == USB_DT_CONFIG)
			dev_warn(ddev, "config %d contains an unexpected "
			    "descriptor of type 0x%X, skipping\n",
			    cfgno, header->bDescriptorType);

	पूर्ण	/* क्रम ((buffer2 = buffer, size2 = size); ...) */
	size = buffer2 - buffer;
	config->desc.wTotalLength = cpu_to_le16(buffer2 - buffer0);

	अगर (n != nपूर्णांकf)
		dev_warn(ddev, "config %d has %d interface%s, different from "
		    "the descriptor's value: %d\n",
		    cfgno, n, plural(n), nपूर्णांकf_orig);
	अन्यथा अगर (n == 0)
		dev_warn(ddev, "config %d has no interfaces?\n", cfgno);
	config->desc.bNumInterfaces = nपूर्णांकf = n;

	/* Check क्रम missing पूर्णांकerface numbers */
	क्रम (i = 0; i < nपूर्णांकf; ++i) अणु
		क्रम (j = 0; j < nपूर्णांकf; ++j) अणु
			अगर (inums[j] == i)
				अवरोध;
		पूर्ण
		अगर (j >= nपूर्णांकf)
			dev_warn(ddev, "config %d has no interface number "
			    "%d\n", cfgno, i);
	पूर्ण

	/* Allocate the usb_पूर्णांकerface_caches and altsetting arrays */
	क्रम (i = 0; i < nपूर्णांकf; ++i) अणु
		j = nalts[i];
		अगर (j > USB_MAXALTSETTING) अणु
			dev_warn(ddev, "too many alternate settings for "
			    "config %d interface %d: %d, "
			    "using maximum allowed: %d\n",
			    cfgno, inums[i], j, USB_MAXALTSETTING);
			nalts[i] = j = USB_MAXALTSETTING;
		पूर्ण

		पूर्णांकfc = kzalloc(काष्ठा_size(पूर्णांकfc, altsetting, j), GFP_KERNEL);
		config->पूर्णांकf_cache[i] = पूर्णांकfc;
		अगर (!पूर्णांकfc)
			वापस -ENOMEM;
		kref_init(&पूर्णांकfc->ref);
	पूर्ण

	/* FIXME: parse the BOS descriptor */

	/* Skip over any Class Specअगरic or Venकरोr Specअगरic descriptors;
	 * find the first पूर्णांकerface descriptor */
	config->extra = buffer;
	i = find_next_descriptor(buffer, size, USB_DT_INTERFACE,
	    USB_DT_INTERFACE, &n);
	config->extralen = i;
	अगर (n > 0)
		dev_dbg(ddev, "skipped %d descriptor%s after %s\n",
		    n, plural(n), "configuration");
	buffer += i;
	size -= i;

	/* Parse all the पूर्णांकerface/altsetting descriptors */
	जबतक (size > 0) अणु
		retval = usb_parse_पूर्णांकerface(ddev, cfgno, config,
		    buffer, size, inums, nalts);
		अगर (retval < 0)
			वापस retval;

		buffer += retval;
		size -= retval;
	पूर्ण

	/* Check क्रम missing altsettings */
	क्रम (i = 0; i < nपूर्णांकf; ++i) अणु
		पूर्णांकfc = config->पूर्णांकf_cache[i];
		क्रम (j = 0; j < पूर्णांकfc->num_altsetting; ++j) अणु
			क्रम (n = 0; n < पूर्णांकfc->num_altsetting; ++n) अणु
				अगर (पूर्णांकfc->altsetting[n].desc.
				    bAlternateSetting == j)
					अवरोध;
			पूर्ण
			अगर (n >= पूर्णांकfc->num_altsetting)
				dev_warn(ddev, "config %d interface %d has no "
				    "altsetting %d\n", cfgno, inums[i], j);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* hub-only!! ... and only exported क्रम reset/reinit path.
 * otherwise used पूर्णांकernally on disconnect/destroy path
 */
व्योम usb_destroy_configuration(काष्ठा usb_device *dev)
अणु
	पूर्णांक c, i;

	अगर (!dev->config)
		वापस;

	अगर (dev->rawdescriptors) अणु
		क्रम (i = 0; i < dev->descriptor.bNumConfigurations; i++)
			kमुक्त(dev->rawdescriptors[i]);

		kमुक्त(dev->rawdescriptors);
		dev->rawdescriptors = शून्य;
	पूर्ण

	क्रम (c = 0; c < dev->descriptor.bNumConfigurations; c++) अणु
		काष्ठा usb_host_config *cf = &dev->config[c];

		kमुक्त(cf->string);
		क्रम (i = 0; i < cf->desc.bNumInterfaces; i++) अणु
			अगर (cf->पूर्णांकf_cache[i])
				kref_put(&cf->पूर्णांकf_cache[i]->ref,
					  usb_release_पूर्णांकerface_cache);
		पूर्ण
	पूर्ण
	kमुक्त(dev->config);
	dev->config = शून्य;
पूर्ण


/*
 * Get the USB config descriptors, cache and parse'em
 *
 * hub-only!! ... and only in reset path, or usb_new_device()
 * (used by real hubs and भव root hubs)
 */
पूर्णांक usb_get_configuration(काष्ठा usb_device *dev)
अणु
	काष्ठा device *ddev = &dev->dev;
	पूर्णांक ncfg = dev->descriptor.bNumConfigurations;
	अचिन्हित पूर्णांक cfgno, length;
	अचिन्हित अक्षर *bigbuffer;
	काष्ठा usb_config_descriptor *desc;
	पूर्णांक result;

	अगर (ncfg > USB_MAXCONFIG) अणु
		dev_warn(ddev, "too many configurations: %d, "
		    "using maximum allowed: %d\n", ncfg, USB_MAXCONFIG);
		dev->descriptor.bNumConfigurations = ncfg = USB_MAXCONFIG;
	पूर्ण

	अगर (ncfg < 1) अणु
		dev_err(ddev, "no configurations\n");
		वापस -EINVAL;
	पूर्ण

	length = ncfg * माप(काष्ठा usb_host_config);
	dev->config = kzalloc(length, GFP_KERNEL);
	अगर (!dev->config)
		वापस -ENOMEM;

	length = ncfg * माप(अक्षर *);
	dev->rawdescriptors = kzalloc(length, GFP_KERNEL);
	अगर (!dev->rawdescriptors)
		वापस -ENOMEM;

	desc = kदो_स्मृति(USB_DT_CONFIG_SIZE, GFP_KERNEL);
	अगर (!desc)
		वापस -ENOMEM;

	क्रम (cfgno = 0; cfgno < ncfg; cfgno++) अणु
		/* We grab just the first descriptor so we know how दीर्घ
		 * the whole configuration is */
		result = usb_get_descriptor(dev, USB_DT_CONFIG, cfgno,
		    desc, USB_DT_CONFIG_SIZE);
		अगर (result < 0) अणु
			dev_err(ddev, "unable to read config index %d "
			    "descriptor/%s: %d\n", cfgno, "start", result);
			अगर (result != -EPIPE)
				जाओ err;
			dev_err(ddev, "chopping to %d config(s)\n", cfgno);
			dev->descriptor.bNumConfigurations = cfgno;
			अवरोध;
		पूर्ण अन्यथा अगर (result < 4) अणु
			dev_err(ddev, "config index %d descriptor too short "
			    "(expected %i, got %i)\n", cfgno,
			    USB_DT_CONFIG_SIZE, result);
			result = -EINVAL;
			जाओ err;
		पूर्ण
		length = max((पूर्णांक) le16_to_cpu(desc->wTotalLength),
		    USB_DT_CONFIG_SIZE);

		/* Now that we know the length, get the whole thing */
		bigbuffer = kदो_स्मृति(length, GFP_KERNEL);
		अगर (!bigbuffer) अणु
			result = -ENOMEM;
			जाओ err;
		पूर्ण

		अगर (dev->quirks & USB_QUIRK_DELAY_INIT)
			msleep(200);

		result = usb_get_descriptor(dev, USB_DT_CONFIG, cfgno,
		    bigbuffer, length);
		अगर (result < 0) अणु
			dev_err(ddev, "unable to read config index %d "
			    "descriptor/%s\n", cfgno, "all");
			kमुक्त(bigbuffer);
			जाओ err;
		पूर्ण
		अगर (result < length) अणु
			dev_warn(ddev, "config index %d descriptor too short "
			    "(expected %i, got %i)\n", cfgno, length, result);
			length = result;
		पूर्ण

		dev->rawdescriptors[cfgno] = bigbuffer;

		result = usb_parse_configuration(dev, cfgno,
		    &dev->config[cfgno], bigbuffer, length);
		अगर (result < 0) अणु
			++cfgno;
			जाओ err;
		पूर्ण
	पूर्ण

err:
	kमुक्त(desc);
	dev->descriptor.bNumConfigurations = cfgno;

	वापस result;
पूर्ण

व्योम usb_release_bos_descriptor(काष्ठा usb_device *dev)
अणु
	अगर (dev->bos) अणु
		kमुक्त(dev->bos->desc);
		kमुक्त(dev->bos);
		dev->bos = शून्य;
	पूर्ण
पूर्ण

अटल स्थिर __u8 bos_desc_len[256] = अणु
	[USB_CAP_TYPE_WIRELESS_USB] = USB_DT_USB_WIRELESS_CAP_SIZE,
	[USB_CAP_TYPE_EXT]          = USB_DT_USB_EXT_CAP_SIZE,
	[USB_SS_CAP_TYPE]           = USB_DT_USB_SS_CAP_SIZE,
	[USB_SSP_CAP_TYPE]          = USB_DT_USB_SSP_CAP_SIZE(1),
	[CONTAINER_ID_TYPE]         = USB_DT_USB_SS_CONTN_ID_SIZE,
	[USB_PTM_CAP_TYPE]          = USB_DT_USB_PTM_ID_SIZE,
पूर्ण;

/* Get BOS descriptor set */
पूर्णांक usb_get_bos_descriptor(काष्ठा usb_device *dev)
अणु
	काष्ठा device *ddev = &dev->dev;
	काष्ठा usb_bos_descriptor *bos;
	काष्ठा usb_dev_cap_header *cap;
	काष्ठा usb_ssp_cap_descriptor *ssp_cap;
	अचिन्हित अक्षर *buffer, *buffer0;
	पूर्णांक length, total_len, num, i, ssac;
	__u8 cap_type;
	पूर्णांक ret;

	bos = kzalloc(माप(काष्ठा usb_bos_descriptor), GFP_KERNEL);
	अगर (!bos)
		वापस -ENOMEM;

	/* Get BOS descriptor */
	ret = usb_get_descriptor(dev, USB_DT_BOS, 0, bos, USB_DT_BOS_SIZE);
	अगर (ret < USB_DT_BOS_SIZE || bos->bLength < USB_DT_BOS_SIZE) अणु
		dev_err(ddev, "unable to get BOS descriptor or descriptor too short\n");
		अगर (ret >= 0)
			ret = -ENOMSG;
		kमुक्त(bos);
		वापस ret;
	पूर्ण

	length = bos->bLength;
	total_len = le16_to_cpu(bos->wTotalLength);
	num = bos->bNumDeviceCaps;
	kमुक्त(bos);
	अगर (total_len < length)
		वापस -EINVAL;

	dev->bos = kzalloc(माप(काष्ठा usb_host_bos), GFP_KERNEL);
	अगर (!dev->bos)
		वापस -ENOMEM;

	/* Now let's get the whole BOS descriptor set */
	buffer = kzalloc(total_len, GFP_KERNEL);
	अगर (!buffer) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	dev->bos->desc = (काष्ठा usb_bos_descriptor *)buffer;

	ret = usb_get_descriptor(dev, USB_DT_BOS, 0, buffer, total_len);
	अगर (ret < total_len) अणु
		dev_err(ddev, "unable to get BOS descriptor set\n");
		अगर (ret >= 0)
			ret = -ENOMSG;
		जाओ err;
	पूर्ण

	buffer0 = buffer;
	total_len -= length;
	buffer += length;

	क्रम (i = 0; i < num; i++) अणु
		cap = (काष्ठा usb_dev_cap_header *)buffer;

		अगर (total_len < माप(*cap) || total_len < cap->bLength) अणु
			dev->bos->desc->bNumDeviceCaps = i;
			अवरोध;
		पूर्ण
		cap_type = cap->bDevCapabilityType;
		length = cap->bLength;
		अगर (bos_desc_len[cap_type] && length < bos_desc_len[cap_type]) अणु
			dev->bos->desc->bNumDeviceCaps = i;
			अवरोध;
		पूर्ण

		अगर (cap->bDescriptorType != USB_DT_DEVICE_CAPABILITY) अणु
			dev_warn(ddev, "descriptor type invalid, skip\n");
			जारी;
		पूर्ण

		चयन (cap_type) अणु
		हाल USB_CAP_TYPE_WIRELESS_USB:
			/* Wireless USB cap descriptor is handled by wusb */
			अवरोध;
		हाल USB_CAP_TYPE_EXT:
			dev->bos->ext_cap =
				(काष्ठा usb_ext_cap_descriptor *)buffer;
			अवरोध;
		हाल USB_SS_CAP_TYPE:
			dev->bos->ss_cap =
				(काष्ठा usb_ss_cap_descriptor *)buffer;
			अवरोध;
		हाल USB_SSP_CAP_TYPE:
			ssp_cap = (काष्ठा usb_ssp_cap_descriptor *)buffer;
			ssac = (le32_to_cpu(ssp_cap->bmAttributes) &
				USB_SSP_SUBLINK_SPEED_ATTRIBS);
			अगर (length >= USB_DT_USB_SSP_CAP_SIZE(ssac))
				dev->bos->ssp_cap = ssp_cap;
			अवरोध;
		हाल CONTAINER_ID_TYPE:
			dev->bos->ss_id =
				(काष्ठा usb_ss_container_id_descriptor *)buffer;
			अवरोध;
		हाल USB_PTM_CAP_TYPE:
			dev->bos->pपंचांग_cap =
				(काष्ठा usb_pपंचांग_cap_descriptor *)buffer;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		total_len -= length;
		buffer += length;
	पूर्ण
	dev->bos->desc->wTotalLength = cpu_to_le16(buffer - buffer0);

	वापस 0;

err:
	usb_release_bos_descriptor(dev);
	वापस ret;
पूर्ण
