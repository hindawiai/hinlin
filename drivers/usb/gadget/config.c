<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * usb/gadget/config.c -- simplअगरy building config descriptors
 *
 * Copyright (C) 2003 David Brownell
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/माला.स>
#समावेश <linux/device.h>

#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/composite.h>
#समावेश <linux/usb/otg.h>

/**
 * usb_descriptor_fillbuf - fill buffer with descriptors
 * @buf: Buffer to be filled
 * @buflen: Size of buf
 * @src: Array of descriptor poपूर्णांकers, terminated by null poपूर्णांकer.
 *
 * Copies descriptors पूर्णांकo the buffer, वापसing the length or a
 * negative error code अगर they can't all be copied.  Useful when
 * assembling descriptors क्रम an associated set of पूर्णांकerfaces used
 * as part of configuring a composite device; or in other हालs where
 * sets of descriptors need to be marshaled.
 */
पूर्णांक
usb_descriptor_fillbuf(व्योम *buf, अचिन्हित buflen,
		स्थिर काष्ठा usb_descriptor_header **src)
अणु
	u8	*dest = buf;

	अगर (!src)
		वापस -EINVAL;

	/* fill buffer from src[] until null descriptor ptr */
	क्रम (; शून्य != *src; src++) अणु
		अचिन्हित		len = (*src)->bLength;

		अगर (len > buflen)
			वापस -EINVAL;
		स_नकल(dest, *src, len);
		buflen -= len;
		dest += len;
	पूर्ण
	वापस dest - (u8 *)buf;
पूर्ण
EXPORT_SYMBOL_GPL(usb_descriptor_fillbuf);

/**
 * usb_gadget_config_buf - builts a complete configuration descriptor
 * @config: Header क्रम the descriptor, including अक्षरacteristics such
 *	as घातer requirements and number of पूर्णांकerfaces.
 * @desc: Null-terminated vector of poपूर्णांकers to the descriptors (पूर्णांकerface,
 *	endpoपूर्णांक, etc) defining all functions in this device configuration.
 * @buf: Buffer क्रम the resulting configuration descriptor.
 * @length: Length of buffer.  If this is not big enough to hold the
 *	entire configuration descriptor, an error code will be वापसed.
 *
 * This copies descriptors पूर्णांकo the response buffer, building a descriptor
 * क्रम that configuration.  It वापसs the buffer length or a negative
 * status code.  The config.wTotalLength field is set to match the length
 * of the result, but other descriptor fields (including घातer usage and
 * पूर्णांकerface count) must be set by the caller.
 *
 * Gadget drivers could use this when स्थिरructing a config descriptor
 * in response to USB_REQ_GET_DESCRIPTOR.  They will need to patch the
 * resulting bDescriptorType value अगर USB_DT_OTHER_SPEED_CONFIG is needed.
 */
पूर्णांक usb_gadget_config_buf(
	स्थिर काष्ठा usb_config_descriptor	*config,
	व्योम					*buf,
	अचिन्हित				length,
	स्थिर काष्ठा usb_descriptor_header	**desc
)
अणु
	काष्ठा usb_config_descriptor		*cp = buf;
	पूर्णांक					len;

	/* config descriptor first */
	अगर (length < USB_DT_CONFIG_SIZE || !desc)
		वापस -EINVAL;
	*cp = *config;

	/* then पूर्णांकerface/endpoपूर्णांक/class/venकरोr/... */
	len = usb_descriptor_fillbuf(USB_DT_CONFIG_SIZE + (u8 *)buf,
			length - USB_DT_CONFIG_SIZE, desc);
	अगर (len < 0)
		वापस len;
	len += USB_DT_CONFIG_SIZE;
	अगर (len > 0xffff)
		वापस -EINVAL;

	/* patch up the config descriptor */
	cp->bLength = USB_DT_CONFIG_SIZE;
	cp->bDescriptorType = USB_DT_CONFIG;
	cp->wTotalLength = cpu_to_le16(len);
	cp->bmAttributes |= USB_CONFIG_ATT_ONE;
	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(usb_gadget_config_buf);

/**
 * usb_copy_descriptors - copy a vector of USB descriptors
 * @src: null-terminated vector to copy
 * Context: initialization code, which may sleep
 *
 * This makes a copy of a vector of USB descriptors.  Its primary use
 * is to support usb_function objects which can have multiple copies,
 * each needing dअगरferent descriptors.  Functions may have अटल
 * tables of descriptors, which are used as ढाँचाs and customized
 * with identअगरiers (क्रम पूर्णांकerfaces, strings, endpoपूर्णांकs, and more)
 * as needed by a given function instance.
 */
काष्ठा usb_descriptor_header **
usb_copy_descriptors(काष्ठा usb_descriptor_header **src)
अणु
	काष्ठा usb_descriptor_header **पंचांगp;
	अचिन्हित bytes;
	अचिन्हित n_desc;
	व्योम *mem;
	काष्ठा usb_descriptor_header **ret;

	/* count descriptors and their sizes; then add vector size */
	क्रम (bytes = 0, n_desc = 0, पंचांगp = src; *पंचांगp; पंचांगp++, n_desc++)
		bytes += (*पंचांगp)->bLength;
	bytes += (n_desc + 1) * माप(*पंचांगp);

	mem = kदो_स्मृति(bytes, GFP_KERNEL);
	अगर (!mem)
		वापस शून्य;

	/* fill in poपूर्णांकers starting at "tmp",
	 * to descriptors copied starting at "mem";
	 * and वापस "ret"
	 */
	पंचांगp = mem;
	ret = mem;
	mem += (n_desc + 1) * माप(*पंचांगp);
	जबतक (*src) अणु
		स_नकल(mem, *src, (*src)->bLength);
		*पंचांगp = mem;
		पंचांगp++;
		mem += (*src)->bLength;
		src++;
	पूर्ण
	*पंचांगp = शून्य;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_copy_descriptors);

पूर्णांक usb_assign_descriptors(काष्ठा usb_function *f,
		काष्ठा usb_descriptor_header **fs,
		काष्ठा usb_descriptor_header **hs,
		काष्ठा usb_descriptor_header **ss,
		काष्ठा usb_descriptor_header **ssp)
अणु
	काष्ठा usb_gadget *g = f->config->cdev->gadget;

	/* super-speed-plus descriptor falls back to super-speed one,
	 * अगर such a descriptor was provided, thus aव्योमing a शून्य
	 * poपूर्णांकer dereference अगर a 5gbps capable gadget is used with
	 * a 10gbps capable config (device port + cable + host port)
	 */
	अगर (!ssp)
		ssp = ss;

	अगर (fs) अणु
		f->fs_descriptors = usb_copy_descriptors(fs);
		अगर (!f->fs_descriptors)
			जाओ err;
	पूर्ण
	अगर (hs && gadget_is_dualspeed(g)) अणु
		f->hs_descriptors = usb_copy_descriptors(hs);
		अगर (!f->hs_descriptors)
			जाओ err;
	पूर्ण
	अगर (ss && gadget_is_superspeed(g)) अणु
		f->ss_descriptors = usb_copy_descriptors(ss);
		अगर (!f->ss_descriptors)
			जाओ err;
	पूर्ण
	अगर (ssp && gadget_is_superspeed_plus(g)) अणु
		f->ssp_descriptors = usb_copy_descriptors(ssp);
		अगर (!f->ssp_descriptors)
			जाओ err;
	पूर्ण
	वापस 0;
err:
	usb_मुक्त_all_descriptors(f);
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL_GPL(usb_assign_descriptors);

व्योम usb_मुक्त_all_descriptors(काष्ठा usb_function *f)
अणु
	usb_मुक्त_descriptors(f->fs_descriptors);
	f->fs_descriptors = शून्य;
	usb_मुक्त_descriptors(f->hs_descriptors);
	f->hs_descriptors = शून्य;
	usb_मुक्त_descriptors(f->ss_descriptors);
	f->ss_descriptors = शून्य;
	usb_मुक्त_descriptors(f->ssp_descriptors);
	f->ssp_descriptors = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(usb_मुक्त_all_descriptors);

काष्ठा usb_descriptor_header *usb_otg_descriptor_alloc(
				काष्ठा usb_gadget *gadget)
अणु
	काष्ठा usb_descriptor_header *otg_desc;
	अचिन्हित length = 0;

	अगर (gadget->otg_caps && (gadget->otg_caps->otg_rev >= 0x0200))
		length = माप(काष्ठा usb_otg20_descriptor);
	अन्यथा
		length = माप(काष्ठा usb_otg_descriptor);

	otg_desc = kzalloc(length, GFP_KERNEL);
	वापस otg_desc;
पूर्ण
EXPORT_SYMBOL_GPL(usb_otg_descriptor_alloc);

पूर्णांक usb_otg_descriptor_init(काष्ठा usb_gadget *gadget,
		काष्ठा usb_descriptor_header *otg_desc)
अणु
	काष्ठा usb_otg_descriptor *otg1x_desc;
	काष्ठा usb_otg20_descriptor *otg20_desc;
	काष्ठा usb_otg_caps *otg_caps = gadget->otg_caps;
	u8 otg_attributes = 0;

	अगर (!otg_desc)
		वापस -EINVAL;

	अगर (otg_caps && otg_caps->otg_rev) अणु
		अगर (otg_caps->hnp_support)
			otg_attributes |= USB_OTG_HNP;
		अगर (otg_caps->srp_support)
			otg_attributes |= USB_OTG_SRP;
		अगर (otg_caps->adp_support && (otg_caps->otg_rev >= 0x0200))
			otg_attributes |= USB_OTG_ADP;
	पूर्ण अन्यथा अणु
		otg_attributes = USB_OTG_SRP | USB_OTG_HNP;
	पूर्ण

	अगर (otg_caps && (otg_caps->otg_rev >= 0x0200)) अणु
		otg20_desc = (काष्ठा usb_otg20_descriptor *)otg_desc;
		otg20_desc->bLength = माप(काष्ठा usb_otg20_descriptor);
		otg20_desc->bDescriptorType = USB_DT_OTG;
		otg20_desc->bmAttributes = otg_attributes;
		otg20_desc->bcdOTG = cpu_to_le16(otg_caps->otg_rev);
	पूर्ण अन्यथा अणु
		otg1x_desc = (काष्ठा usb_otg_descriptor *)otg_desc;
		otg1x_desc->bLength = माप(काष्ठा usb_otg_descriptor);
		otg1x_desc->bDescriptorType = USB_DT_OTG;
		otg1x_desc->bmAttributes = otg_attributes;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_otg_descriptor_init);
