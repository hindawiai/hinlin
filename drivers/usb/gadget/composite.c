<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * composite.c - infraकाष्ठाure क्रम Composite USB Gadमाला_लो
 *
 * Copyright (C) 2006-2008 David Brownell
 */

/* #घोषणा VERBOSE_DEBUG */

#समावेश <linux/kallsyms.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/utsname.h>
#समावेश <linux/bitfield.h>

#समावेश <linux/usb/composite.h>
#समावेश <linux/usb/otg.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "u_os_desc.h"

/**
 * काष्ठा usb_os_string - represents OS String to be reported by a gadget
 * @bLength: total length of the entire descritor, always 0x12
 * @bDescriptorType: USB_DT_STRING
 * @qwSignature: the OS String proper
 * @bMS_VenकरोrCode: code used by the host क्रम subsequent requests
 * @bPad: not used, must be zero
 */
काष्ठा usb_os_string अणु
	__u8	bLength;
	__u8	bDescriptorType;
	__u8	qwSignature[OS_STRING_QW_SIGN_LEN];
	__u8	bMS_VenकरोrCode;
	__u8	bPad;
पूर्ण __packed;

/*
 * The code in this file is utility code, used to build a gadget driver
 * from one or more "function" drivers, one or more "configuration"
 * objects, and a "usb_composite_driver" by gluing them together aदीर्घ
 * with the relevant device-wide data.
 */

अटल काष्ठा usb_gadget_strings **get_containers_gs(
		काष्ठा usb_gadget_string_container *uc)
अणु
	वापस (काष्ठा usb_gadget_strings **)uc->stash;
पूर्ण

/**
 * function_descriptors() - get function descriptors क्रम speed
 * @f: the function
 * @speed: the speed
 *
 * Returns the descriptors or शून्य अगर not set.
 */
अटल काष्ठा usb_descriptor_header **
function_descriptors(काष्ठा usb_function *f,
		     क्रमागत usb_device_speed speed)
अणु
	काष्ठा usb_descriptor_header **descriptors;

	/*
	 * NOTE: we try to help gadget drivers which might not be setting
	 * max_speed appropriately.
	 */

	चयन (speed) अणु
	हाल USB_SPEED_SUPER_PLUS:
		descriptors = f->ssp_descriptors;
		अगर (descriptors)
			अवरोध;
		fallthrough;
	हाल USB_SPEED_SUPER:
		descriptors = f->ss_descriptors;
		अगर (descriptors)
			अवरोध;
		fallthrough;
	हाल USB_SPEED_HIGH:
		descriptors = f->hs_descriptors;
		अगर (descriptors)
			अवरोध;
		fallthrough;
	शेष:
		descriptors = f->fs_descriptors;
	पूर्ण

	/*
	 * अगर we can't find any descriptors at all, then this gadget deserves to
	 * Oops with a शून्य poपूर्णांकer dereference
	 */

	वापस descriptors;
पूर्ण

/**
 * next_desc() - advance to the next desc_type descriptor
 * @t: currect poपूर्णांकer within descriptor array
 * @desc_type: descriptor type
 *
 * Return: next desc_type descriptor or शून्य
 *
 * Iterate over @t until either desc_type descriptor found or
 * शून्य (that indicates end of list) encountered
 */
अटल काष्ठा usb_descriptor_header**
next_desc(काष्ठा usb_descriptor_header **t, u8 desc_type)
अणु
	क्रम (; *t; t++) अणु
		अगर ((*t)->bDescriptorType == desc_type)
			वापस t;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * क्रम_each_desc() - iterate over desc_type descriptors in the
 * descriptors list
 * @start: poपूर्णांकer within descriptor array.
 * @iter_desc: desc_type descriptor to use as the loop cursor
 * @desc_type: wanted descriptr type
 */
#घोषणा क्रम_each_desc(start, iter_desc, desc_type) \
	क्रम (iter_desc = next_desc(start, desc_type); \
	     iter_desc; iter_desc = next_desc(iter_desc + 1, desc_type))

/**
 * config_ep_by_speed_and_alt() - configures the given endpoपूर्णांक
 * according to gadget speed.
 * @g: poपूर्णांकer to the gadget
 * @f: usb function
 * @_ep: the endpoपूर्णांक to configure
 * @alt: alternate setting number
 *
 * Return: error code, 0 on success
 *
 * This function chooses the right descriptors क्रम a given
 * endpoपूर्णांक according to gadget speed and saves it in the
 * endpoपूर्णांक desc field. If the endpoपूर्णांक alपढ़ोy has a descriptor
 * asचिन्हित to it - overग_लिखोs it with currently corresponding
 * descriptor. The endpoपूर्णांक maxpacket field is updated according
 * to the chosen descriptor.
 * Note: the supplied function should hold all the descriptors
 * क्रम supported speeds
 */
पूर्णांक config_ep_by_speed_and_alt(काष्ठा usb_gadget *g,
				काष्ठा usb_function *f,
				काष्ठा usb_ep *_ep,
				u8 alt)
अणु
	काष्ठा usb_endpoपूर्णांक_descriptor *chosen_desc = शून्य;
	काष्ठा usb_पूर्णांकerface_descriptor *पूर्णांक_desc = शून्य;
	काष्ठा usb_descriptor_header **speed_desc = शून्य;

	काष्ठा usb_ss_ep_comp_descriptor *comp_desc = शून्य;
	पूर्णांक want_comp_desc = 0;

	काष्ठा usb_descriptor_header **d_spd; /* cursor क्रम speed desc */

	अगर (!g || !f || !_ep)
		वापस -EIO;

	/* select desired speed */
	चयन (g->speed) अणु
	हाल USB_SPEED_SUPER_PLUS:
		अगर (gadget_is_superspeed_plus(g)) अणु
			speed_desc = f->ssp_descriptors;
			want_comp_desc = 1;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल USB_SPEED_SUPER:
		अगर (gadget_is_superspeed(g)) अणु
			speed_desc = f->ss_descriptors;
			want_comp_desc = 1;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल USB_SPEED_HIGH:
		अगर (gadget_is_dualspeed(g)) अणु
			speed_desc = f->hs_descriptors;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		speed_desc = f->fs_descriptors;
	पूर्ण

	/* find correct alternate setting descriptor */
	क्रम_each_desc(speed_desc, d_spd, USB_DT_INTERFACE) अणु
		पूर्णांक_desc = (काष्ठा usb_पूर्णांकerface_descriptor *)*d_spd;

		अगर (पूर्णांक_desc->bAlternateSetting == alt) अणु
			speed_desc = d_spd;
			जाओ पूर्णांकf_found;
		पूर्ण
	पूर्ण
	वापस -EIO;

पूर्णांकf_found:
	/* find descriptors */
	क्रम_each_desc(speed_desc, d_spd, USB_DT_ENDPOINT) अणु
		chosen_desc = (काष्ठा usb_endpoपूर्णांक_descriptor *)*d_spd;
		अगर (chosen_desc->bEndpoपूर्णांकAddress == _ep->address)
			जाओ ep_found;
	पूर्ण
	वापस -EIO;

ep_found:
	/* commit results */
	_ep->maxpacket = usb_endpoपूर्णांक_maxp(chosen_desc);
	_ep->desc = chosen_desc;
	_ep->comp_desc = शून्य;
	_ep->maxburst = 0;
	_ep->mult = 1;

	अगर (g->speed == USB_SPEED_HIGH && (usb_endpoपूर्णांक_xfer_isoc(_ep->desc) ||
				usb_endpoपूर्णांक_xfer_पूर्णांक(_ep->desc)))
		_ep->mult = usb_endpoपूर्णांक_maxp_mult(_ep->desc);

	अगर (!want_comp_desc)
		वापस 0;

	/*
	 * Companion descriptor should follow EP descriptor
	 * USB 3.0 spec, #9.6.7
	 */
	comp_desc = (काष्ठा usb_ss_ep_comp_descriptor *)*(++d_spd);
	अगर (!comp_desc ||
	    (comp_desc->bDescriptorType != USB_DT_SS_ENDPOINT_COMP))
		वापस -EIO;
	_ep->comp_desc = comp_desc;
	अगर (g->speed >= USB_SPEED_SUPER) अणु
		चयन (usb_endpoपूर्णांक_type(_ep->desc)) अणु
		हाल USB_ENDPOINT_XFER_ISOC:
			/* mult: bits 1:0 of bmAttributes */
			_ep->mult = (comp_desc->bmAttributes & 0x3) + 1;
			fallthrough;
		हाल USB_ENDPOINT_XFER_BULK:
		हाल USB_ENDPOINT_XFER_INT:
			_ep->maxburst = comp_desc->bMaxBurst + 1;
			अवरोध;
		शेष:
			अगर (comp_desc->bMaxBurst != 0) अणु
				काष्ठा usb_composite_dev *cdev;

				cdev = get_gadget_data(g);
				ERROR(cdev, "ep0 bMaxBurst must be 0\n");
			पूर्ण
			_ep->maxburst = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(config_ep_by_speed_and_alt);

/**
 * config_ep_by_speed() - configures the given endpoपूर्णांक
 * according to gadget speed.
 * @g: poपूर्णांकer to the gadget
 * @f: usb function
 * @_ep: the endpoपूर्णांक to configure
 *
 * Return: error code, 0 on success
 *
 * This function chooses the right descriptors क्रम a given
 * endpoपूर्णांक according to gadget speed and saves it in the
 * endpoपूर्णांक desc field. If the endpoपूर्णांक alपढ़ोy has a descriptor
 * asचिन्हित to it - overग_लिखोs it with currently corresponding
 * descriptor. The endpoपूर्णांक maxpacket field is updated according
 * to the chosen descriptor.
 * Note: the supplied function should hold all the descriptors
 * क्रम supported speeds
 */
पूर्णांक config_ep_by_speed(काष्ठा usb_gadget *g,
			काष्ठा usb_function *f,
			काष्ठा usb_ep *_ep)
अणु
	वापस config_ep_by_speed_and_alt(g, f, _ep, 0);
पूर्ण
EXPORT_SYMBOL_GPL(config_ep_by_speed);

/**
 * usb_add_function() - add a function to a configuration
 * @config: the configuration
 * @function: the function being added
 * Context: single thपढ़ोed during gadget setup
 *
 * After initialization, each configuration must have one or more
 * functions added to it.  Adding a function involves calling its @bind()
 * method to allocate resources such as पूर्णांकerface and string identअगरiers
 * and endpoपूर्णांकs.
 *
 * This function वापसs the value of the function's bind(), which is
 * zero क्रम success अन्यथा a negative त्रुटि_सं value.
 */
पूर्णांक usb_add_function(काष्ठा usb_configuration *config,
		काष्ठा usb_function *function)
अणु
	पूर्णांक	value = -EINVAL;

	DBG(config->cdev, "adding '%s'/%p to config '%s'/%p\n",
			function->name, function,
			config->label, config);

	अगर (!function->set_alt || !function->disable)
		जाओ करोne;

	function->config = config;
	list_add_tail(&function->list, &config->functions);

	अगर (function->bind_deactivated) अणु
		value = usb_function_deactivate(function);
		अगर (value)
			जाओ करोne;
	पूर्ण

	/* REVISIT *require* function->bind? */
	अगर (function->bind) अणु
		value = function->bind(config, function);
		अगर (value < 0) अणु
			list_del(&function->list);
			function->config = शून्य;
		पूर्ण
	पूर्ण अन्यथा
		value = 0;

	/* We allow configurations that करोn't work at both speeds.
	 * If we run पूर्णांकo a lowspeed Linux प्रणाली, treat it the same
	 * as full speed ... it's the function drivers that will need
	 * to aव्योम bulk and ISO transfers.
	 */
	अगर (!config->fullspeed && function->fs_descriptors)
		config->fullspeed = true;
	अगर (!config->highspeed && function->hs_descriptors)
		config->highspeed = true;
	अगर (!config->superspeed && function->ss_descriptors)
		config->superspeed = true;
	अगर (!config->superspeed_plus && function->ssp_descriptors)
		config->superspeed_plus = true;

करोne:
	अगर (value)
		DBG(config->cdev, "adding '%s'/%p --> %d\n",
				function->name, function, value);
	वापस value;
पूर्ण
EXPORT_SYMBOL_GPL(usb_add_function);

व्योम usb_हटाओ_function(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	अगर (f->disable)
		f->disable(f);

	biपंचांगap_zero(f->endpoपूर्णांकs, 32);
	list_del(&f->list);
	अगर (f->unbind)
		f->unbind(c, f);

	अगर (f->bind_deactivated)
		usb_function_activate(f);
पूर्ण
EXPORT_SYMBOL_GPL(usb_हटाओ_function);

/**
 * usb_function_deactivate - prevent function and gadget क्रमागतeration
 * @function: the function that isn't yet पढ़ोy to respond
 *
 * Blocks response of the gadget driver to host क्रमागतeration by
 * preventing the data line pullup from being activated.  This is
 * normally called during @bind() processing to change from the
 * initial "ready to respond" state, or when a required resource
 * becomes available.
 *
 * For example, drivers that serve as a passthrough to a userspace
 * daemon can block क्रमागतeration unless that daemon (such as an OBEX,
 * MTP, or prपूर्णांक server) is पढ़ोy to handle host requests.
 *
 * Not all प्रणालीs support software control of their USB peripheral
 * data pullups.
 *
 * Returns zero on success, अन्यथा negative त्रुटि_सं.
 */
पूर्णांक usb_function_deactivate(काष्ठा usb_function *function)
अणु
	काष्ठा usb_composite_dev	*cdev = function->config->cdev;
	अचिन्हित दीर्घ			flags;
	पूर्णांक				status = 0;

	spin_lock_irqsave(&cdev->lock, flags);

	अगर (cdev->deactivations == 0) अणु
		spin_unlock_irqrestore(&cdev->lock, flags);
		status = usb_gadget_deactivate(cdev->gadget);
		spin_lock_irqsave(&cdev->lock, flags);
	पूर्ण
	अगर (status == 0)
		cdev->deactivations++;

	spin_unlock_irqrestore(&cdev->lock, flags);
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(usb_function_deactivate);

/**
 * usb_function_activate - allow function and gadget क्रमागतeration
 * @function: function on which usb_function_activate() was called
 *
 * Reverses effect of usb_function_deactivate().  If no more functions
 * are delaying their activation, the gadget driver will respond to
 * host क्रमागतeration procedures.
 *
 * Returns zero on success, अन्यथा negative त्रुटि_सं.
 */
पूर्णांक usb_function_activate(काष्ठा usb_function *function)
अणु
	काष्ठा usb_composite_dev	*cdev = function->config->cdev;
	अचिन्हित दीर्घ			flags;
	पूर्णांक				status = 0;

	spin_lock_irqsave(&cdev->lock, flags);

	अगर (WARN_ON(cdev->deactivations == 0))
		status = -EINVAL;
	अन्यथा अणु
		cdev->deactivations--;
		अगर (cdev->deactivations == 0) अणु
			spin_unlock_irqrestore(&cdev->lock, flags);
			status = usb_gadget_activate(cdev->gadget);
			spin_lock_irqsave(&cdev->lock, flags);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&cdev->lock, flags);
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(usb_function_activate);

/**
 * usb_पूर्णांकerface_id() - allocate an unused पूर्णांकerface ID
 * @config: configuration associated with the पूर्णांकerface
 * @function: function handling the पूर्णांकerface
 * Context: single thपढ़ोed during gadget setup
 *
 * usb_पूर्णांकerface_id() is called from usb_function.bind() callbacks to
 * allocate new पूर्णांकerface IDs.  The function driver will then store that
 * ID in पूर्णांकerface, association, CDC जोड़, and other descriptors.  It
 * will also handle any control requests targeted at that पूर्णांकerface,
 * particularly changing its altsetting via set_alt().  There may
 * also be class-specअगरic or venकरोr-specअगरic requests to handle.
 *
 * All पूर्णांकerface identअगरier should be allocated using this routine, to
 * ensure that क्रम example dअगरferent functions करोn't wrongly assign
 * dअगरferent meanings to the same identअगरier.  Note that since पूर्णांकerface
 * identअगरiers are configuration-specअगरic, functions used in more than
 * one configuration (or more than once in a given configuration) need
 * multiple versions of the relevant descriptors.
 *
 * Returns the पूर्णांकerface ID which was allocated; or -ENODEV अगर no
 * more पूर्णांकerface IDs can be allocated.
 */
पूर्णांक usb_पूर्णांकerface_id(काष्ठा usb_configuration *config,
		काष्ठा usb_function *function)
अणु
	अचिन्हित id = config->next_पूर्णांकerface_id;

	अगर (id < MAX_CONFIG_INTERFACES) अणु
		config->पूर्णांकerface[id] = function;
		config->next_पूर्णांकerface_id = id + 1;
		वापस id;
	पूर्ण
	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(usb_पूर्णांकerface_id);

अटल u8 encode_bMaxPower(क्रमागत usb_device_speed speed,
		काष्ठा usb_configuration *c)
अणु
	अचिन्हित val;

	अगर (c->MaxPower)
		val = c->MaxPower;
	अन्यथा
		val = CONFIG_USB_GADGET_VBUS_DRAW;
	अगर (!val)
		वापस 0;
	अगर (speed < USB_SPEED_SUPER)
		वापस min(val, 500U) / 2;
	अन्यथा
		/*
		 * USB 3.x supports up to 900mA, but since 900 isn't भागisible
		 * by 8 the पूर्णांकegral भागision will effectively cap to 896mA.
		 */
		वापस min(val, 900U) / 8;
पूर्ण

अटल पूर्णांक config_buf(काष्ठा usb_configuration *config,
		क्रमागत usb_device_speed speed, व्योम *buf, u8 type)
अणु
	काष्ठा usb_config_descriptor	*c = buf;
	व्योम				*next = buf + USB_DT_CONFIG_SIZE;
	पूर्णांक				len;
	काष्ठा usb_function		*f;
	पूर्णांक				status;

	len = USB_COMP_EP0_बफ_मान - USB_DT_CONFIG_SIZE;
	/* ग_लिखो the config descriptor */
	c = buf;
	c->bLength = USB_DT_CONFIG_SIZE;
	c->bDescriptorType = type;
	/* wTotalLength is written later */
	c->bNumInterfaces = config->next_पूर्णांकerface_id;
	c->bConfigurationValue = config->bConfigurationValue;
	c->iConfiguration = config->iConfiguration;
	c->bmAttributes = USB_CONFIG_ATT_ONE | config->bmAttributes;
	c->bMaxPower = encode_bMaxPower(speed, config);

	/* There may be e.g. OTG descriptors */
	अगर (config->descriptors) अणु
		status = usb_descriptor_fillbuf(next, len,
				config->descriptors);
		अगर (status < 0)
			वापस status;
		len -= status;
		next += status;
	पूर्ण

	/* add each function's descriptors */
	list_क्रम_each_entry(f, &config->functions, list) अणु
		काष्ठा usb_descriptor_header **descriptors;

		descriptors = function_descriptors(f, speed);
		अगर (!descriptors)
			जारी;
		status = usb_descriptor_fillbuf(next, len,
			(स्थिर काष्ठा usb_descriptor_header **) descriptors);
		अगर (status < 0)
			वापस status;
		len -= status;
		next += status;
	पूर्ण

	len = next - buf;
	c->wTotalLength = cpu_to_le16(len);
	वापस len;
पूर्ण

अटल पूर्णांक config_desc(काष्ठा usb_composite_dev *cdev, अचिन्हित w_value)
अणु
	काष्ठा usb_gadget		*gadget = cdev->gadget;
	काष्ठा usb_configuration	*c;
	काष्ठा list_head		*pos;
	u8				type = w_value >> 8;
	क्रमागत usb_device_speed		speed = USB_SPEED_UNKNOWN;

	अगर (gadget->speed >= USB_SPEED_SUPER)
		speed = gadget->speed;
	अन्यथा अगर (gadget_is_dualspeed(gadget)) अणु
		पूर्णांक	hs = 0;
		अगर (gadget->speed == USB_SPEED_HIGH)
			hs = 1;
		अगर (type == USB_DT_OTHER_SPEED_CONFIG)
			hs = !hs;
		अगर (hs)
			speed = USB_SPEED_HIGH;

	पूर्ण

	/* This is a lookup by config *INDEX* */
	w_value &= 0xff;

	pos = &cdev->configs;
	c = cdev->os_desc_config;
	अगर (c)
		जाओ check_config;

	जबतक ((pos = pos->next) !=  &cdev->configs) अणु
		c = list_entry(pos, typeof(*c), list);

		/* skip OS Descriptors config which is handled separately */
		अगर (c == cdev->os_desc_config)
			जारी;

check_config:
		/* ignore configs that won't work at this speed */
		चयन (speed) अणु
		हाल USB_SPEED_SUPER_PLUS:
			अगर (!c->superspeed_plus)
				जारी;
			अवरोध;
		हाल USB_SPEED_SUPER:
			अगर (!c->superspeed)
				जारी;
			अवरोध;
		हाल USB_SPEED_HIGH:
			अगर (!c->highspeed)
				जारी;
			अवरोध;
		शेष:
			अगर (!c->fullspeed)
				जारी;
		पूर्ण

		अगर (w_value == 0)
			वापस config_buf(c, speed, cdev->req->buf, type);
		w_value--;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक count_configs(काष्ठा usb_composite_dev *cdev, अचिन्हित type)
अणु
	काष्ठा usb_gadget		*gadget = cdev->gadget;
	काष्ठा usb_configuration	*c;
	अचिन्हित			count = 0;
	पूर्णांक				hs = 0;
	पूर्णांक				ss = 0;
	पूर्णांक				ssp = 0;

	अगर (gadget_is_dualspeed(gadget)) अणु
		अगर (gadget->speed == USB_SPEED_HIGH)
			hs = 1;
		अगर (gadget->speed == USB_SPEED_SUPER)
			ss = 1;
		अगर (gadget->speed == USB_SPEED_SUPER_PLUS)
			ssp = 1;
		अगर (type == USB_DT_DEVICE_QUALIFIER)
			hs = !hs;
	पूर्ण
	list_क्रम_each_entry(c, &cdev->configs, list) अणु
		/* ignore configs that won't work at this speed */
		अगर (ssp) अणु
			अगर (!c->superspeed_plus)
				जारी;
		पूर्ण अन्यथा अगर (ss) अणु
			अगर (!c->superspeed)
				जारी;
		पूर्ण अन्यथा अगर (hs) अणु
			अगर (!c->highspeed)
				जारी;
		पूर्ण अन्यथा अणु
			अगर (!c->fullspeed)
				जारी;
		पूर्ण
		count++;
	पूर्ण
	वापस count;
पूर्ण

/**
 * bos_desc() - prepares the BOS descriptor.
 * @cdev: poपूर्णांकer to usb_composite device to generate the bos
 *	descriptor क्रम
 *
 * This function generates the BOS (Binary Device Object)
 * descriptor and its device capabilities descriptors. The BOS
 * descriptor should be supported by a SuperSpeed device.
 */
अटल पूर्णांक bos_desc(काष्ठा usb_composite_dev *cdev)
अणु
	काष्ठा usb_ext_cap_descriptor	*usb_ext;
	काष्ठा usb_dcd_config_params	dcd_config_params;
	काष्ठा usb_bos_descriptor	*bos = cdev->req->buf;
	अचिन्हित पूर्णांक			besl = 0;

	bos->bLength = USB_DT_BOS_SIZE;
	bos->bDescriptorType = USB_DT_BOS;

	bos->wTotalLength = cpu_to_le16(USB_DT_BOS_SIZE);
	bos->bNumDeviceCaps = 0;

	/* Get Controller configuration */
	अगर (cdev->gadget->ops->get_config_params) अणु
		cdev->gadget->ops->get_config_params(cdev->gadget,
						     &dcd_config_params);
	पूर्ण अन्यथा अणु
		dcd_config_params.besl_baseline =
			USB_DEFAULT_BESL_UNSPECIFIED;
		dcd_config_params.besl_deep =
			USB_DEFAULT_BESL_UNSPECIFIED;
		dcd_config_params.bU1devExitLat =
			USB_DEFAULT_U1_DEV_EXIT_LAT;
		dcd_config_params.bU2DevExitLat =
			cpu_to_le16(USB_DEFAULT_U2_DEV_EXIT_LAT);
	पूर्ण

	अगर (dcd_config_params.besl_baseline != USB_DEFAULT_BESL_UNSPECIFIED)
		besl = USB_BESL_BASELINE_VALID |
			USB_SET_BESL_BASELINE(dcd_config_params.besl_baseline);

	अगर (dcd_config_params.besl_deep != USB_DEFAULT_BESL_UNSPECIFIED)
		besl |= USB_BESL_DEEP_VALID |
			USB_SET_BESL_DEEP(dcd_config_params.besl_deep);

	/*
	 * A SuperSpeed device shall include the USB2.0 extension descriptor
	 * and shall support LPM when operating in USB2.0 HS mode.
	 */
	usb_ext = cdev->req->buf + le16_to_cpu(bos->wTotalLength);
	bos->bNumDeviceCaps++;
	le16_add_cpu(&bos->wTotalLength, USB_DT_USB_EXT_CAP_SIZE);
	usb_ext->bLength = USB_DT_USB_EXT_CAP_SIZE;
	usb_ext->bDescriptorType = USB_DT_DEVICE_CAPABILITY;
	usb_ext->bDevCapabilityType = USB_CAP_TYPE_EXT;
	usb_ext->bmAttributes = cpu_to_le32(USB_LPM_SUPPORT |
					    USB_BESL_SUPPORT | besl);

	/*
	 * The Superspeed USB Capability descriptor shall be implemented by all
	 * SuperSpeed devices.
	 */
	अगर (gadget_is_superspeed(cdev->gadget)) अणु
		काष्ठा usb_ss_cap_descriptor *ss_cap;

		ss_cap = cdev->req->buf + le16_to_cpu(bos->wTotalLength);
		bos->bNumDeviceCaps++;
		le16_add_cpu(&bos->wTotalLength, USB_DT_USB_SS_CAP_SIZE);
		ss_cap->bLength = USB_DT_USB_SS_CAP_SIZE;
		ss_cap->bDescriptorType = USB_DT_DEVICE_CAPABILITY;
		ss_cap->bDevCapabilityType = USB_SS_CAP_TYPE;
		ss_cap->bmAttributes = 0; /* LTM is not supported yet */
		ss_cap->wSpeedSupported = cpu_to_le16(USB_LOW_SPEED_OPERATION |
						      USB_FULL_SPEED_OPERATION |
						      USB_HIGH_SPEED_OPERATION |
						      USB_5GBPS_OPERATION);
		ss_cap->bFunctionalitySupport = USB_LOW_SPEED_OPERATION;
		ss_cap->bU1devExitLat = dcd_config_params.bU1devExitLat;
		ss_cap->bU2DevExitLat = dcd_config_params.bU2DevExitLat;
	पूर्ण

	/* The SuperSpeedPlus USB Device Capability descriptor */
	अगर (gadget_is_superspeed_plus(cdev->gadget)) अणु
		काष्ठा usb_ssp_cap_descriptor *ssp_cap;
		u8 ssac = 1;
		u8 ssic;
		पूर्णांक i;

		अगर (cdev->gadget->max_ssp_rate == USB_SSP_GEN_2x2)
			ssac = 3;

		/*
		 * Paired RX and TX sublink speed attributes share
		 * the same SSID.
		 */
		ssic = (ssac + 1) / 2 - 1;

		ssp_cap = cdev->req->buf + le16_to_cpu(bos->wTotalLength);
		bos->bNumDeviceCaps++;

		le16_add_cpu(&bos->wTotalLength, USB_DT_USB_SSP_CAP_SIZE(ssac));
		ssp_cap->bLength = USB_DT_USB_SSP_CAP_SIZE(ssac);
		ssp_cap->bDescriptorType = USB_DT_DEVICE_CAPABILITY;
		ssp_cap->bDevCapabilityType = USB_SSP_CAP_TYPE;
		ssp_cap->bReserved = 0;
		ssp_cap->wReserved = 0;

		ssp_cap->bmAttributes =
			cpu_to_le32(FIELD_PREP(USB_SSP_SUBLINK_SPEED_ATTRIBS, ssac) |
				    FIELD_PREP(USB_SSP_SUBLINK_SPEED_IDS, ssic));

		ssp_cap->wFunctionalitySupport =
			cpu_to_le16(FIELD_PREP(USB_SSP_MIN_SUBLINK_SPEED_ATTRIBUTE_ID, 0) |
				    FIELD_PREP(USB_SSP_MIN_RX_LANE_COUNT, 1) |
				    FIELD_PREP(USB_SSP_MIN_TX_LANE_COUNT, 1));

		/*
		 * Use 1 SSID अगर the gadget supports up to gen2x1 or not
		 * specअगरied:
		 * - SSID 0 क्रम symmetric RX/TX sublink speed of 10 Gbps.
		 *
		 * Use 1 SSID अगर the gadget supports up to gen1x2:
		 * - SSID 0 क्रम symmetric RX/TX sublink speed of 5 Gbps.
		 *
		 * Use 2 SSIDs अगर the gadget supports up to gen2x2:
		 * - SSID 0 क्रम symmetric RX/TX sublink speed of 5 Gbps.
		 * - SSID 1 क्रम symmetric RX/TX sublink speed of 10 Gbps.
		 */
		क्रम (i = 0; i < ssac + 1; i++) अणु
			u8 ssid;
			u8 mantissa;
			u8 type;

			ssid = i >> 1;

			अगर (cdev->gadget->max_ssp_rate == USB_SSP_GEN_2x1 ||
			    cdev->gadget->max_ssp_rate == USB_SSP_GEN_UNKNOWN)
				mantissa = 10;
			अन्यथा
				mantissa = 5 << ssid;

			अगर (i % 2)
				type = USB_SSP_SUBLINK_SPEED_ST_SYM_TX;
			अन्यथा
				type = USB_SSP_SUBLINK_SPEED_ST_SYM_RX;

			ssp_cap->bmSublinkSpeedAttr[i] =
				cpu_to_le32(FIELD_PREP(USB_SSP_SUBLINK_SPEED_SSID, ssid) |
					    FIELD_PREP(USB_SSP_SUBLINK_SPEED_LSE,
						       USB_SSP_SUBLINK_SPEED_LSE_GBPS) |
					    FIELD_PREP(USB_SSP_SUBLINK_SPEED_ST, type) |
					    FIELD_PREP(USB_SSP_SUBLINK_SPEED_LP,
						       USB_SSP_SUBLINK_SPEED_LP_SSP) |
					    FIELD_PREP(USB_SSP_SUBLINK_SPEED_LSM, mantissa));
		पूर्ण
	पूर्ण

	वापस le16_to_cpu(bos->wTotalLength);
पूर्ण

अटल व्योम device_qual(काष्ठा usb_composite_dev *cdev)
अणु
	काष्ठा usb_qualअगरier_descriptor	*qual = cdev->req->buf;

	qual->bLength = माप(*qual);
	qual->bDescriptorType = USB_DT_DEVICE_QUALIFIER;
	/* POLICY: same bcdUSB and device type info at both speeds */
	qual->bcdUSB = cdev->desc.bcdUSB;
	qual->bDeviceClass = cdev->desc.bDeviceClass;
	qual->bDeviceSubClass = cdev->desc.bDeviceSubClass;
	qual->bDeviceProtocol = cdev->desc.bDeviceProtocol;
	/* ASSUME same EP0 fअगरo size at both speeds */
	qual->bMaxPacketSize0 = cdev->gadget->ep0->maxpacket;
	qual->bNumConfigurations = count_configs(cdev, USB_DT_DEVICE_QUALIFIER);
	qual->bRESERVED = 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल व्योम reset_config(काष्ठा usb_composite_dev *cdev)
अणु
	काष्ठा usb_function		*f;

	DBG(cdev, "reset config\n");

	list_क्रम_each_entry(f, &cdev->config->functions, list) अणु
		अगर (f->disable)
			f->disable(f);

		biपंचांगap_zero(f->endpoपूर्णांकs, 32);
	पूर्ण
	cdev->config = शून्य;
	cdev->delayed_status = 0;
पूर्ण

अटल पूर्णांक set_config(काष्ठा usb_composite_dev *cdev,
		स्थिर काष्ठा usb_ctrlrequest *ctrl, अचिन्हित number)
अणु
	काष्ठा usb_gadget	*gadget = cdev->gadget;
	काष्ठा usb_configuration *c = शून्य;
	पूर्णांक			result = -EINVAL;
	अचिन्हित		घातer = gadget_is_otg(gadget) ? 8 : 100;
	पूर्णांक			पंचांगp;

	अगर (number) अणु
		list_क्रम_each_entry(c, &cdev->configs, list) अणु
			अगर (c->bConfigurationValue == number) अणु
				/*
				 * We disable the FDs of the previous
				 * configuration only अगर the new configuration
				 * is a valid one
				 */
				अगर (cdev->config)
					reset_config(cdev);
				result = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (result < 0)
			जाओ करोne;
	पूर्ण अन्यथा अणु /* Zero configuration value - need to reset the config */
		अगर (cdev->config)
			reset_config(cdev);
		result = 0;
	पूर्ण

	DBG(cdev, "%s config #%d: %s\n",
	    usb_speed_string(gadget->speed),
	    number, c ? c->label : "unconfigured");

	अगर (!c)
		जाओ करोne;

	usb_gadget_set_state(gadget, USB_STATE_CONFIGURED);
	cdev->config = c;

	/* Initialize all पूर्णांकerfaces by setting them to altsetting zero. */
	क्रम (पंचांगp = 0; पंचांगp < MAX_CONFIG_INTERFACES; पंचांगp++) अणु
		काष्ठा usb_function	*f = c->पूर्णांकerface[पंचांगp];
		काष्ठा usb_descriptor_header **descriptors;

		अगर (!f)
			अवरोध;

		/*
		 * Record which endpoपूर्णांकs are used by the function. This is used
		 * to dispatch control requests targeted at that endpoपूर्णांक to the
		 * function's setup callback instead of the current
		 * configuration's setup callback.
		 */
		descriptors = function_descriptors(f, gadget->speed);

		क्रम (; *descriptors; ++descriptors) अणु
			काष्ठा usb_endpoपूर्णांक_descriptor *ep;
			पूर्णांक addr;

			अगर ((*descriptors)->bDescriptorType != USB_DT_ENDPOINT)
				जारी;

			ep = (काष्ठा usb_endpoपूर्णांक_descriptor *)*descriptors;
			addr = ((ep->bEndpoपूर्णांकAddress & 0x80) >> 3)
			     |  (ep->bEndpoपूर्णांकAddress & 0x0f);
			set_bit(addr, f->endpoपूर्णांकs);
		पूर्ण

		result = f->set_alt(f, पंचांगp, 0);
		अगर (result < 0) अणु
			DBG(cdev, "interface %d (%s/%p) alt 0 --> %d\n",
					पंचांगp, f->name, f, result);

			reset_config(cdev);
			जाओ करोne;
		पूर्ण

		अगर (result == USB_GADGET_DELAYED_STATUS) अणु
			DBG(cdev,
			 "%s: interface %d (%s) requested delayed status\n",
					__func__, पंचांगp, f->name);
			cdev->delayed_status++;
			DBG(cdev, "delayed_status count %d\n",
					cdev->delayed_status);
		पूर्ण
	पूर्ण

	/* when we वापस, be sure our घातer usage is valid */
	घातer = c->MaxPower ? c->MaxPower : CONFIG_USB_GADGET_VBUS_DRAW;
	अगर (gadget->speed < USB_SPEED_SUPER)
		घातer = min(घातer, 500U);
	अन्यथा
		घातer = min(घातer, 900U);
करोne:
	अगर (घातer <= USB_SELF_POWER_VBUS_MAX_DRAW)
		usb_gadget_set_selfघातered(gadget);
	अन्यथा
		usb_gadget_clear_selfघातered(gadget);

	usb_gadget_vbus_draw(gadget, घातer);
	अगर (result >= 0 && cdev->delayed_status)
		result = USB_GADGET_DELAYED_STATUS;
	वापस result;
पूर्ण

पूर्णांक usb_add_config_only(काष्ठा usb_composite_dev *cdev,
		काष्ठा usb_configuration *config)
अणु
	काष्ठा usb_configuration *c;

	अगर (!config->bConfigurationValue)
		वापस -EINVAL;

	/* Prevent duplicate configuration identअगरiers */
	list_क्रम_each_entry(c, &cdev->configs, list) अणु
		अगर (c->bConfigurationValue == config->bConfigurationValue)
			वापस -EBUSY;
	पूर्ण

	config->cdev = cdev;
	list_add_tail(&config->list, &cdev->configs);

	INIT_LIST_HEAD(&config->functions);
	config->next_पूर्णांकerface_id = 0;
	स_रखो(config->पूर्णांकerface, 0, माप(config->पूर्णांकerface));

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_add_config_only);

/**
 * usb_add_config() - add a configuration to a device.
 * @cdev: wraps the USB gadget
 * @config: the configuration, with bConfigurationValue asचिन्हित
 * @bind: the configuration's bind function
 * Context: single thपढ़ोed during gadget setup
 *
 * One of the मुख्य tasks of a composite @bind() routine is to
 * add each of the configurations it supports, using this routine.
 *
 * This function वापसs the value of the configuration's @bind(), which
 * is zero क्रम success अन्यथा a negative त्रुटि_सं value.  Binding configurations
 * assigns global resources including string IDs, and per-configuration
 * resources such as पूर्णांकerface IDs and endpoपूर्णांकs.
 */
पूर्णांक usb_add_config(काष्ठा usb_composite_dev *cdev,
		काष्ठा usb_configuration *config,
		पूर्णांक (*bind)(काष्ठा usb_configuration *))
अणु
	पूर्णांक				status = -EINVAL;

	अगर (!bind)
		जाओ करोne;

	DBG(cdev, "adding config #%u '%s'/%p\n",
			config->bConfigurationValue,
			config->label, config);

	status = usb_add_config_only(cdev, config);
	अगर (status)
		जाओ करोne;

	status = bind(config);
	अगर (status < 0) अणु
		जबतक (!list_empty(&config->functions)) अणु
			काष्ठा usb_function		*f;

			f = list_first_entry(&config->functions,
					काष्ठा usb_function, list);
			list_del(&f->list);
			अगर (f->unbind) अणु
				DBG(cdev, "unbind function '%s'/%p\n",
					f->name, f);
				f->unbind(config, f);
				/* may मुक्त memory क्रम "f" */
			पूर्ण
		पूर्ण
		list_del(&config->list);
		config->cdev = शून्य;
	पूर्ण अन्यथा अणु
		अचिन्हित	i;

		DBG(cdev, "cfg %d/%p speeds:%s%s%s%s\n",
			config->bConfigurationValue, config,
			config->superspeed_plus ? " superplus" : "",
			config->superspeed ? " super" : "",
			config->highspeed ? " high" : "",
			config->fullspeed
				? (gadget_is_dualspeed(cdev->gadget)
					? " full"
					: " full/low")
				: "");

		क्रम (i = 0; i < MAX_CONFIG_INTERFACES; i++) अणु
			काष्ठा usb_function	*f = config->पूर्णांकerface[i];

			अगर (!f)
				जारी;
			DBG(cdev, "  interface %d = %s/%p\n",
				i, f->name, f);
		पूर्ण
	पूर्ण

	/* set_alt(), or next bind(), sets up ep->claimed as needed */
	usb_ep_स्वतःconfig_reset(cdev->gadget);

करोne:
	अगर (status)
		DBG(cdev, "added config '%s'/%u --> %d\n", config->label,
				config->bConfigurationValue, status);
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(usb_add_config);

अटल व्योम हटाओ_config(काष्ठा usb_composite_dev *cdev,
			      काष्ठा usb_configuration *config)
अणु
	जबतक (!list_empty(&config->functions)) अणु
		काष्ठा usb_function		*f;

		f = list_first_entry(&config->functions,
				काष्ठा usb_function, list);

		usb_हटाओ_function(config, f);
	पूर्ण
	list_del(&config->list);
	अगर (config->unbind) अणु
		DBG(cdev, "unbind config '%s'/%p\n", config->label, config);
		config->unbind(config);
			/* may मुक्त memory क्रम "c" */
	पूर्ण
पूर्ण

/**
 * usb_हटाओ_config() - हटाओ a configuration from a device.
 * @cdev: wraps the USB gadget
 * @config: the configuration
 *
 * Drivers must call usb_gadget_disconnect beक्रमe calling this function
 * to disconnect the device from the host and make sure the host will not
 * try to क्रमागतerate the device जबतक we are changing the config list.
 */
व्योम usb_हटाओ_config(काष्ठा usb_composite_dev *cdev,
		      काष्ठा usb_configuration *config)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cdev->lock, flags);

	अगर (cdev->config == config)
		reset_config(cdev);

	spin_unlock_irqrestore(&cdev->lock, flags);

	हटाओ_config(cdev, config);
पूर्ण

/*-------------------------------------------------------------------------*/

/* We support strings in multiple languages ... string descriptor zero
 * says which languages are supported.  The typical हाल will be that
 * only one language (probably English) is used, with i18n handled on
 * the host side.
 */

अटल व्योम collect_langs(काष्ठा usb_gadget_strings **sp, __le16 *buf)
अणु
	स्थिर काष्ठा usb_gadget_strings	*s;
	__le16				language;
	__le16				*पंचांगp;

	जबतक (*sp) अणु
		s = *sp;
		language = cpu_to_le16(s->language);
		क्रम (पंचांगp = buf; *पंचांगp && पंचांगp < &buf[USB_MAX_STRING_LEN]; पंचांगp++) अणु
			अगर (*पंचांगp == language)
				जाओ repeat;
		पूर्ण
		*पंचांगp++ = language;
repeat:
		sp++;
	पूर्ण
पूर्ण

अटल पूर्णांक lookup_string(
	काष्ठा usb_gadget_strings	**sp,
	व्योम				*buf,
	u16				language,
	पूर्णांक				id
)
अणु
	काष्ठा usb_gadget_strings	*s;
	पूर्णांक				value;

	जबतक (*sp) अणु
		s = *sp++;
		अगर (s->language != language)
			जारी;
		value = usb_gadget_get_string(s, id, buf);
		अगर (value > 0)
			वापस value;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक get_string(काष्ठा usb_composite_dev *cdev,
		व्योम *buf, u16 language, पूर्णांक id)
अणु
	काष्ठा usb_composite_driver	*composite = cdev->driver;
	काष्ठा usb_gadget_string_container *uc;
	काष्ठा usb_configuration	*c;
	काष्ठा usb_function		*f;
	पूर्णांक				len;

	/* Yes, not only is USB's i18n support probably more than most
	 * folk will ever care about ... also, it's all supported here.
	 * (Except क्रम UTF8 support क्रम Unicode's "Astral Planes".)
	 */

	/* 0 == report all available language codes */
	अगर (id == 0) अणु
		काष्ठा usb_string_descriptor	*s = buf;
		काष्ठा usb_gadget_strings	**sp;

		स_रखो(s, 0, 256);
		s->bDescriptorType = USB_DT_STRING;

		sp = composite->strings;
		अगर (sp)
			collect_langs(sp, s->wData);

		list_क्रम_each_entry(c, &cdev->configs, list) अणु
			sp = c->strings;
			अगर (sp)
				collect_langs(sp, s->wData);

			list_क्रम_each_entry(f, &c->functions, list) अणु
				sp = f->strings;
				अगर (sp)
					collect_langs(sp, s->wData);
			पूर्ण
		पूर्ण
		list_क्रम_each_entry(uc, &cdev->gstrings, list) अणु
			काष्ठा usb_gadget_strings **sp;

			sp = get_containers_gs(uc);
			collect_langs(sp, s->wData);
		पूर्ण

		क्रम (len = 0; len <= USB_MAX_STRING_LEN && s->wData[len]; len++)
			जारी;
		अगर (!len)
			वापस -EINVAL;

		s->bLength = 2 * (len + 1);
		वापस s->bLength;
	पूर्ण

	अगर (cdev->use_os_string && language == 0 && id == OS_STRING_IDX) अणु
		काष्ठा usb_os_string *b = buf;
		b->bLength = माप(*b);
		b->bDescriptorType = USB_DT_STRING;
		compileसमय_निश्चित(
			माप(b->qwSignature) == माप(cdev->qw_sign),
			"qwSignature size must be equal to qw_sign");
		स_नकल(&b->qwSignature, cdev->qw_sign, माप(b->qwSignature));
		b->bMS_VenकरोrCode = cdev->b_venकरोr_code;
		b->bPad = 0;
		वापस माप(*b);
	पूर्ण

	list_क्रम_each_entry(uc, &cdev->gstrings, list) अणु
		काष्ठा usb_gadget_strings **sp;

		sp = get_containers_gs(uc);
		len = lookup_string(sp, buf, language, id);
		अगर (len > 0)
			वापस len;
	पूर्ण

	/* String IDs are device-scoped, so we look up each string
	 * table we're told about.  These lookups are infrequent;
	 * simpler-is-better here.
	 */
	अगर (composite->strings) अणु
		len = lookup_string(composite->strings, buf, language, id);
		अगर (len > 0)
			वापस len;
	पूर्ण
	list_क्रम_each_entry(c, &cdev->configs, list) अणु
		अगर (c->strings) अणु
			len = lookup_string(c->strings, buf, language, id);
			अगर (len > 0)
				वापस len;
		पूर्ण
		list_क्रम_each_entry(f, &c->functions, list) अणु
			अगर (!f->strings)
				जारी;
			len = lookup_string(f->strings, buf, language, id);
			अगर (len > 0)
				वापस len;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

/**
 * usb_string_id() - allocate an unused string ID
 * @cdev: the device whose string descriptor IDs are being allocated
 * Context: single thपढ़ोed during gadget setup
 *
 * @usb_string_id() is called from bind() callbacks to allocate
 * string IDs.  Drivers क्रम functions, configurations, or gadमाला_लो will
 * then store that ID in the appropriate descriptors and string table.
 *
 * All string identअगरier should be allocated using this,
 * @usb_string_ids_tab() or @usb_string_ids_n() routine, to ensure
 * that क्रम example dअगरferent functions करोn't wrongly assign dअगरferent
 * meanings to the same identअगरier.
 */
पूर्णांक usb_string_id(काष्ठा usb_composite_dev *cdev)
अणु
	अगर (cdev->next_string_id < 254) अणु
		/* string id 0 is reserved by USB spec क्रम list of
		 * supported languages */
		/* 255 reserved as well? -- mina86 */
		cdev->next_string_id++;
		वापस cdev->next_string_id;
	पूर्ण
	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(usb_string_id);

/**
 * usb_string_ids_tab() - allocate unused string IDs in batch
 * @cdev: the device whose string descriptor IDs are being allocated
 * @str: an array of usb_string objects to assign numbers to
 * Context: single thपढ़ोed during gadget setup
 *
 * @usb_string_ids() is called from bind() callbacks to allocate
 * string IDs.  Drivers क्रम functions, configurations, or gadमाला_लो will
 * then copy IDs from the string table to the appropriate descriptors
 * and string table क्रम other languages.
 *
 * All string identअगरier should be allocated using this,
 * @usb_string_id() or @usb_string_ids_n() routine, to ensure that क्रम
 * example dअगरferent functions करोn't wrongly assign dअगरferent meanings
 * to the same identअगरier.
 */
पूर्णांक usb_string_ids_tab(काष्ठा usb_composite_dev *cdev, काष्ठा usb_string *str)
अणु
	पूर्णांक next = cdev->next_string_id;

	क्रम (; str->s; ++str) अणु
		अगर (unlikely(next >= 254))
			वापस -ENODEV;
		str->id = ++next;
	पूर्ण

	cdev->next_string_id = next;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_string_ids_tab);

अटल काष्ठा usb_gadget_string_container *copy_gadget_strings(
		काष्ठा usb_gadget_strings **sp, अचिन्हित n_gstrings,
		अचिन्हित n_strings)
अणु
	काष्ठा usb_gadget_string_container *uc;
	काष्ठा usb_gadget_strings **gs_array;
	काष्ठा usb_gadget_strings *gs;
	काष्ठा usb_string *s;
	अचिन्हित mem;
	अचिन्हित n_gs;
	अचिन्हित n_s;
	व्योम *stash;

	mem = माप(*uc);
	mem += माप(व्योम *) * (n_gstrings + 1);
	mem += माप(काष्ठा usb_gadget_strings) * n_gstrings;
	mem += माप(काष्ठा usb_string) * (n_strings + 1) * (n_gstrings);
	uc = kदो_स्मृति(mem, GFP_KERNEL);
	अगर (!uc)
		वापस ERR_PTR(-ENOMEM);
	gs_array = get_containers_gs(uc);
	stash = uc->stash;
	stash += माप(व्योम *) * (n_gstrings + 1);
	क्रम (n_gs = 0; n_gs < n_gstrings; n_gs++) अणु
		काष्ठा usb_string *org_s;

		gs_array[n_gs] = stash;
		gs = gs_array[n_gs];
		stash += माप(काष्ठा usb_gadget_strings);
		gs->language = sp[n_gs]->language;
		gs->strings = stash;
		org_s = sp[n_gs]->strings;

		क्रम (n_s = 0; n_s < n_strings; n_s++) अणु
			s = stash;
			stash += माप(काष्ठा usb_string);
			अगर (org_s->s)
				s->s = org_s->s;
			अन्यथा
				s->s = "";
			org_s++;
		पूर्ण
		s = stash;
		s->s = शून्य;
		stash += माप(काष्ठा usb_string);

	पूर्ण
	gs_array[n_gs] = शून्य;
	वापस uc;
पूर्ण

/**
 * usb_gstrings_attach() - attach gadget strings to a cdev and assign ids
 * @cdev: the device whose string descriptor IDs are being allocated
 * and attached.
 * @sp: an array of usb_gadget_strings to attach.
 * @n_strings: number of entries in each usb_strings array (sp[]->strings)
 *
 * This function will create a deep copy of usb_gadget_strings and usb_string
 * and attach it to the cdev. The actual string (usb_string.s) will not be
 * copied but only a referenced will be made. The काष्ठा usb_gadget_strings
 * array may contain multiple languages and should be शून्य terminated.
 * The ->language poपूर्णांकer of each काष्ठा usb_gadget_strings has to contain the
 * same amount of entries.
 * For instance: sp[0] is en-US, sp[1] is es-ES. It is expected that the first
 * usb_string entry of es-ES contains the translation of the first usb_string
 * entry of en-US. Thereक्रमe both entries become the same id assign.
 */
काष्ठा usb_string *usb_gstrings_attach(काष्ठा usb_composite_dev *cdev,
		काष्ठा usb_gadget_strings **sp, अचिन्हित n_strings)
अणु
	काष्ठा usb_gadget_string_container *uc;
	काष्ठा usb_gadget_strings **n_gs;
	अचिन्हित n_gstrings = 0;
	अचिन्हित i;
	पूर्णांक ret;

	क्रम (i = 0; sp[i]; i++)
		n_gstrings++;

	अगर (!n_gstrings)
		वापस ERR_PTR(-EINVAL);

	uc = copy_gadget_strings(sp, n_gstrings, n_strings);
	अगर (IS_ERR(uc))
		वापस ERR_CAST(uc);

	n_gs = get_containers_gs(uc);
	ret = usb_string_ids_tab(cdev, n_gs[0]->strings);
	अगर (ret)
		जाओ err;

	क्रम (i = 1; i < n_gstrings; i++) अणु
		काष्ठा usb_string *m_s;
		काष्ठा usb_string *s;
		अचिन्हित n;

		m_s = n_gs[0]->strings;
		s = n_gs[i]->strings;
		क्रम (n = 0; n < n_strings; n++) अणु
			s->id = m_s->id;
			s++;
			m_s++;
		पूर्ण
	पूर्ण
	list_add_tail(&uc->list, &cdev->gstrings);
	वापस n_gs[0]->strings;
err:
	kमुक्त(uc);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(usb_gstrings_attach);

/**
 * usb_string_ids_n() - allocate unused string IDs in batch
 * @c: the device whose string descriptor IDs are being allocated
 * @n: number of string IDs to allocate
 * Context: single thपढ़ोed during gadget setup
 *
 * Returns the first requested ID.  This ID and next @n-1 IDs are now
 * valid IDs.  At least provided that @n is non-zero because अगर it
 * is, वापसs last requested ID which is now very useful inक्रमmation.
 *
 * @usb_string_ids_n() is called from bind() callbacks to allocate
 * string IDs.  Drivers क्रम functions, configurations, or gadमाला_लो will
 * then store that ID in the appropriate descriptors and string table.
 *
 * All string identअगरier should be allocated using this,
 * @usb_string_id() or @usb_string_ids_n() routine, to ensure that क्रम
 * example dअगरferent functions करोn't wrongly assign dअगरferent meanings
 * to the same identअगरier.
 */
पूर्णांक usb_string_ids_n(काष्ठा usb_composite_dev *c, अचिन्हित n)
अणु
	अचिन्हित next = c->next_string_id;
	अगर (unlikely(n > 254 || (अचिन्हित)next + n > 254))
		वापस -ENODEV;
	c->next_string_id += n;
	वापस next + 1;
पूर्ण
EXPORT_SYMBOL_GPL(usb_string_ids_n);

/*-------------------------------------------------------------------------*/

अटल व्योम composite_setup_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा usb_composite_dev *cdev;

	अगर (req->status || req->actual != req->length)
		DBG((काष्ठा usb_composite_dev *) ep->driver_data,
				"setup complete --> %d, %d/%d\n",
				req->status, req->actual, req->length);

	/*
	 * REVIST The same ep0 requests are shared with function drivers
	 * so they करोn't have to मुख्यtain the same ->complete() stubs.
	 *
	 * Because of that, we need to check क्रम the validity of ->context
	 * here, even though we know we've set it to something useful.
	 */
	अगर (!req->context)
		वापस;

	cdev = req->context;

	अगर (cdev->req == req)
		cdev->setup_pending = false;
	अन्यथा अगर (cdev->os_desc_req == req)
		cdev->os_desc_pending = false;
	अन्यथा
		WARN(1, "unknown request %p\n", req);
पूर्ण

अटल पूर्णांक composite_ep0_queue(काष्ठा usb_composite_dev *cdev,
		काष्ठा usb_request *req, gfp_t gfp_flags)
अणु
	पूर्णांक ret;

	ret = usb_ep_queue(cdev->gadget->ep0, req, gfp_flags);
	अगर (ret == 0) अणु
		अगर (cdev->req == req)
			cdev->setup_pending = true;
		अन्यथा अगर (cdev->os_desc_req == req)
			cdev->os_desc_pending = true;
		अन्यथा
			WARN(1, "unknown request %p\n", req);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक count_ext_compat(काष्ठा usb_configuration *c)
अणु
	पूर्णांक i, res;

	res = 0;
	क्रम (i = 0; i < c->next_पूर्णांकerface_id; ++i) अणु
		काष्ठा usb_function *f;
		पूर्णांक j;

		f = c->पूर्णांकerface[i];
		क्रम (j = 0; j < f->os_desc_n; ++j) अणु
			काष्ठा usb_os_desc *d;

			अगर (i != f->os_desc_table[j].अगर_id)
				जारी;
			d = f->os_desc_table[j].os_desc;
			अगर (d && d->ext_compat_id)
				++res;
		पूर्ण
	पूर्ण
	BUG_ON(res > 255);
	वापस res;
पूर्ण

अटल पूर्णांक fill_ext_compat(काष्ठा usb_configuration *c, u8 *buf)
अणु
	पूर्णांक i, count;

	count = 16;
	buf += 16;
	क्रम (i = 0; i < c->next_पूर्णांकerface_id; ++i) अणु
		काष्ठा usb_function *f;
		पूर्णांक j;

		f = c->पूर्णांकerface[i];
		क्रम (j = 0; j < f->os_desc_n; ++j) अणु
			काष्ठा usb_os_desc *d;

			अगर (i != f->os_desc_table[j].अगर_id)
				जारी;
			d = f->os_desc_table[j].os_desc;
			अगर (d && d->ext_compat_id) अणु
				*buf++ = i;
				*buf++ = 0x01;
				स_नकल(buf, d->ext_compat_id, 16);
				buf += 22;
			पूर्ण अन्यथा अणु
				++buf;
				*buf = 0x01;
				buf += 23;
			पूर्ण
			count += 24;
			अगर (count + 24 >= USB_COMP_EP0_OS_DESC_बफ_मान)
				वापस count;
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक count_ext_prop(काष्ठा usb_configuration *c, पूर्णांक पूर्णांकerface)
अणु
	काष्ठा usb_function *f;
	पूर्णांक j;

	f = c->पूर्णांकerface[पूर्णांकerface];
	क्रम (j = 0; j < f->os_desc_n; ++j) अणु
		काष्ठा usb_os_desc *d;

		अगर (पूर्णांकerface != f->os_desc_table[j].अगर_id)
			जारी;
		d = f->os_desc_table[j].os_desc;
		अगर (d && d->ext_compat_id)
			वापस d->ext_prop_count;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक len_ext_prop(काष्ठा usb_configuration *c, पूर्णांक पूर्णांकerface)
अणु
	काष्ठा usb_function *f;
	काष्ठा usb_os_desc *d;
	पूर्णांक j, res;

	res = 10; /* header length */
	f = c->पूर्णांकerface[पूर्णांकerface];
	क्रम (j = 0; j < f->os_desc_n; ++j) अणु
		अगर (पूर्णांकerface != f->os_desc_table[j].अगर_id)
			जारी;
		d = f->os_desc_table[j].os_desc;
		अगर (d)
			वापस min(res + d->ext_prop_len, 4096);
	पूर्ण
	वापस res;
पूर्ण

अटल पूर्णांक fill_ext_prop(काष्ठा usb_configuration *c, पूर्णांक पूर्णांकerface, u8 *buf)
अणु
	काष्ठा usb_function *f;
	काष्ठा usb_os_desc *d;
	काष्ठा usb_os_desc_ext_prop *ext_prop;
	पूर्णांक j, count, n, ret;

	f = c->पूर्णांकerface[पूर्णांकerface];
	count = 10; /* header length */
	buf += 10;
	क्रम (j = 0; j < f->os_desc_n; ++j) अणु
		अगर (पूर्णांकerface != f->os_desc_table[j].अगर_id)
			जारी;
		d = f->os_desc_table[j].os_desc;
		अगर (d)
			list_क्रम_each_entry(ext_prop, &d->ext_prop, entry) अणु
				n = ext_prop->data_len +
					ext_prop->name_len + 14;
				अगर (count + n >= USB_COMP_EP0_OS_DESC_बफ_मान)
					वापस count;
				usb_ext_prop_put_size(buf, n);
				usb_ext_prop_put_type(buf, ext_prop->type);
				ret = usb_ext_prop_put_name(buf, ext_prop->name,
							    ext_prop->name_len);
				अगर (ret < 0)
					वापस ret;
				चयन (ext_prop->type) अणु
				हाल USB_EXT_PROP_UNICODE:
				हाल USB_EXT_PROP_UNICODE_ENV:
				हाल USB_EXT_PROP_UNICODE_LINK:
					usb_ext_prop_put_unicode(buf, ret,
							 ext_prop->data,
							 ext_prop->data_len);
					अवरोध;
				हाल USB_EXT_PROP_BINARY:
					usb_ext_prop_put_binary(buf, ret,
							ext_prop->data,
							ext_prop->data_len);
					अवरोध;
				हाल USB_EXT_PROP_LE32:
					/* not implemented */
				हाल USB_EXT_PROP_BE32:
					/* not implemented */
				शेष:
					वापस -EINVAL;
				पूर्ण
				buf += n;
				count += n;
			पूर्ण
	पूर्ण

	वापस count;
पूर्ण

/*
 * The setup() callback implements all the ep0 functionality that's
 * not handled lower करोwn, in hardware or the hardware driver(like
 * device and endpoपूर्णांक feature flags, and their status).  It's all
 * housekeeping क्रम the gadget function we're implementing.  Most of
 * the work is in config and function specअगरic setup.
 */
पूर्णांक
composite_setup(काष्ठा usb_gadget *gadget, स्थिर काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा usb_composite_dev	*cdev = get_gadget_data(gadget);
	काष्ठा usb_request		*req = cdev->req;
	पूर्णांक				value = -EOPNOTSUPP;
	पूर्णांक				status = 0;
	u16				w_index = le16_to_cpu(ctrl->wIndex);
	u8				पूर्णांकf = w_index & 0xFF;
	u16				w_value = le16_to_cpu(ctrl->wValue);
	u16				w_length = le16_to_cpu(ctrl->wLength);
	काष्ठा usb_function		*f = शून्य;
	u8				endp;

	/* partial re-init of the response message; the function or the
	 * gadget might need to पूर्णांकercept e.g. a control-OUT completion
	 * when we delegate to it.
	 */
	req->zero = 0;
	req->context = cdev;
	req->complete = composite_setup_complete;
	req->length = 0;
	gadget->ep0->driver_data = cdev;

	/*
	 * Don't let non-standard requests match any of the हालs below
	 * by accident.
	 */
	अगर ((ctrl->bRequestType & USB_TYPE_MASK) != USB_TYPE_STANDARD)
		जाओ unknown;

	चयन (ctrl->bRequest) अणु

	/* we handle all standard USB descriptors */
	हाल USB_REQ_GET_DESCRIPTOR:
		अगर (ctrl->bRequestType != USB_सूची_IN)
			जाओ unknown;
		चयन (w_value >> 8) अणु

		हाल USB_DT_DEVICE:
			cdev->desc.bNumConfigurations =
				count_configs(cdev, USB_DT_DEVICE);
			cdev->desc.bMaxPacketSize0 =
				cdev->gadget->ep0->maxpacket;
			अगर (gadget_is_superspeed(gadget)) अणु
				अगर (gadget->speed >= USB_SPEED_SUPER) अणु
					cdev->desc.bcdUSB = cpu_to_le16(0x0320);
					cdev->desc.bMaxPacketSize0 = 9;
				पूर्ण अन्यथा अणु
					cdev->desc.bcdUSB = cpu_to_le16(0x0210);
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (gadget->lpm_capable)
					cdev->desc.bcdUSB = cpu_to_le16(0x0201);
				अन्यथा
					cdev->desc.bcdUSB = cpu_to_le16(0x0200);
			पूर्ण

			value = min(w_length, (u16) माप cdev->desc);
			स_नकल(req->buf, &cdev->desc, value);
			अवरोध;
		हाल USB_DT_DEVICE_QUALIFIER:
			अगर (!gadget_is_dualspeed(gadget) ||
			    gadget->speed >= USB_SPEED_SUPER)
				अवरोध;
			device_qual(cdev);
			value = min_t(पूर्णांक, w_length,
				माप(काष्ठा usb_qualअगरier_descriptor));
			अवरोध;
		हाल USB_DT_OTHER_SPEED_CONFIG:
			अगर (!gadget_is_dualspeed(gadget) ||
			    gadget->speed >= USB_SPEED_SUPER)
				अवरोध;
			fallthrough;
		हाल USB_DT_CONFIG:
			value = config_desc(cdev, w_value);
			अगर (value >= 0)
				value = min(w_length, (u16) value);
			अवरोध;
		हाल USB_DT_STRING:
			value = get_string(cdev, req->buf,
					w_index, w_value & 0xff);
			अगर (value >= 0)
				value = min(w_length, (u16) value);
			अवरोध;
		हाल USB_DT_BOS:
			अगर (gadget_is_superspeed(gadget) ||
			    gadget->lpm_capable) अणु
				value = bos_desc(cdev);
				value = min(w_length, (u16) value);
			पूर्ण
			अवरोध;
		हाल USB_DT_OTG:
			अगर (gadget_is_otg(gadget)) अणु
				काष्ठा usb_configuration *config;
				पूर्णांक otg_desc_len = 0;

				अगर (cdev->config)
					config = cdev->config;
				अन्यथा
					config = list_first_entry(
							&cdev->configs,
						काष्ठा usb_configuration, list);
				अगर (!config)
					जाओ करोne;

				अगर (gadget->otg_caps &&
					(gadget->otg_caps->otg_rev >= 0x0200))
					otg_desc_len += माप(
						काष्ठा usb_otg20_descriptor);
				अन्यथा
					otg_desc_len += माप(
						काष्ठा usb_otg_descriptor);

				value = min_t(पूर्णांक, w_length, otg_desc_len);
				स_नकल(req->buf, config->descriptors[0], value);
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;

	/* any number of configs can work */
	हाल USB_REQ_SET_CONFIGURATION:
		अगर (ctrl->bRequestType != 0)
			जाओ unknown;
		अगर (gadget_is_otg(gadget)) अणु
			अगर (gadget->a_hnp_support)
				DBG(cdev, "HNP available\n");
			अन्यथा अगर (gadget->a_alt_hnp_support)
				DBG(cdev, "HNP on another port\n");
			अन्यथा
				VDBG(cdev, "HNP inactive\n");
		पूर्ण
		spin_lock(&cdev->lock);
		value = set_config(cdev, ctrl, w_value);
		spin_unlock(&cdev->lock);
		अवरोध;
	हाल USB_REQ_GET_CONFIGURATION:
		अगर (ctrl->bRequestType != USB_सूची_IN)
			जाओ unknown;
		अगर (cdev->config)
			*(u8 *)req->buf = cdev->config->bConfigurationValue;
		अन्यथा
			*(u8 *)req->buf = 0;
		value = min(w_length, (u16) 1);
		अवरोध;

	/* function drivers must handle get/set altsetting */
	हाल USB_REQ_SET_INTERFACE:
		अगर (ctrl->bRequestType != USB_RECIP_INTERFACE)
			जाओ unknown;
		अगर (!cdev->config || पूर्णांकf >= MAX_CONFIG_INTERFACES)
			अवरोध;
		f = cdev->config->पूर्णांकerface[पूर्णांकf];
		अगर (!f)
			अवरोध;

		/*
		 * If there's no get_alt() method, we know only altsetting zero
		 * works. There is no need to check अगर set_alt() is not शून्य
		 * as we check this in usb_add_function().
		 */
		अगर (w_value && !f->get_alt)
			अवरोध;

		spin_lock(&cdev->lock);
		value = f->set_alt(f, w_index, w_value);
		अगर (value == USB_GADGET_DELAYED_STATUS) अणु
			DBG(cdev,
			 "%s: interface %d (%s) requested delayed status\n",
					__func__, पूर्णांकf, f->name);
			cdev->delayed_status++;
			DBG(cdev, "delayed_status count %d\n",
					cdev->delayed_status);
		पूर्ण
		spin_unlock(&cdev->lock);
		अवरोध;
	हाल USB_REQ_GET_INTERFACE:
		अगर (ctrl->bRequestType != (USB_सूची_IN|USB_RECIP_INTERFACE))
			जाओ unknown;
		अगर (!cdev->config || पूर्णांकf >= MAX_CONFIG_INTERFACES)
			अवरोध;
		f = cdev->config->पूर्णांकerface[पूर्णांकf];
		अगर (!f)
			अवरोध;
		/* lots of पूर्णांकerfaces only need altsetting zero... */
		value = f->get_alt ? f->get_alt(f, w_index) : 0;
		अगर (value < 0)
			अवरोध;
		*((u8 *)req->buf) = value;
		value = min(w_length, (u16) 1);
		अवरोध;
	हाल USB_REQ_GET_STATUS:
		अगर (gadget_is_otg(gadget) && gadget->hnp_polling_support &&
						(w_index == OTG_STS_SELECTOR)) अणु
			अगर (ctrl->bRequestType != (USB_सूची_IN |
							USB_RECIP_DEVICE))
				जाओ unknown;
			*((u8 *)req->buf) = gadget->host_request_flag;
			value = 1;
			अवरोध;
		पूर्ण

		/*
		 * USB 3.0 additions:
		 * Function driver should handle get_status request. If such cb
		 * wasn't supplied we respond with शेष value = 0
		 * Note: function driver should supply such cb only क्रम the
		 * first पूर्णांकerface of the function
		 */
		अगर (!gadget_is_superspeed(gadget))
			जाओ unknown;
		अगर (ctrl->bRequestType != (USB_सूची_IN | USB_RECIP_INTERFACE))
			जाओ unknown;
		value = 2;	/* This is the length of the get_status reply */
		put_unaligned_le16(0, req->buf);
		अगर (!cdev->config || पूर्णांकf >= MAX_CONFIG_INTERFACES)
			अवरोध;
		f = cdev->config->पूर्णांकerface[पूर्णांकf];
		अगर (!f)
			अवरोध;
		status = f->get_status ? f->get_status(f) : 0;
		अगर (status < 0)
			अवरोध;
		put_unaligned_le16(status & 0x0000ffff, req->buf);
		अवरोध;
	/*
	 * Function drivers should handle SetFeature/ClearFeature
	 * (FUNCTION_SUSPEND) request. function_suspend cb should be supplied
	 * only क्रम the first पूर्णांकerface of the function
	 */
	हाल USB_REQ_CLEAR_FEATURE:
	हाल USB_REQ_SET_FEATURE:
		अगर (!gadget_is_superspeed(gadget))
			जाओ unknown;
		अगर (ctrl->bRequestType != (USB_सूची_OUT | USB_RECIP_INTERFACE))
			जाओ unknown;
		चयन (w_value) अणु
		हाल USB_INTRF_FUNC_SUSPEND:
			अगर (!cdev->config || पूर्णांकf >= MAX_CONFIG_INTERFACES)
				अवरोध;
			f = cdev->config->पूर्णांकerface[पूर्णांकf];
			अगर (!f)
				अवरोध;
			value = 0;
			अगर (f->func_suspend)
				value = f->func_suspend(f, w_index >> 8);
			अगर (value < 0) अणु
				ERROR(cdev,
				      "func_suspend() returned error %d\n",
				      value);
				value = 0;
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
unknown:
		/*
		 * OS descriptors handling
		 */
		अगर (cdev->use_os_string && cdev->os_desc_config &&
		    (ctrl->bRequestType & USB_TYPE_VENDOR) &&
		    ctrl->bRequest == cdev->b_venकरोr_code) अणु
			काष्ठा usb_configuration	*os_desc_cfg;
			u8				*buf;
			पूर्णांक				पूर्णांकerface;
			पूर्णांक				count = 0;

			req = cdev->os_desc_req;
			req->context = cdev;
			req->complete = composite_setup_complete;
			buf = req->buf;
			os_desc_cfg = cdev->os_desc_config;
			w_length = min_t(u16, w_length, USB_COMP_EP0_OS_DESC_बफ_मान);
			स_रखो(buf, 0, w_length);
			buf[5] = 0x01;
			चयन (ctrl->bRequestType & USB_RECIP_MASK) अणु
			हाल USB_RECIP_DEVICE:
				अगर (w_index != 0x4 || (w_value >> 8))
					अवरोध;
				buf[6] = w_index;
				/* Number of ext compat पूर्णांकerfaces */
				count = count_ext_compat(os_desc_cfg);
				buf[8] = count;
				count *= 24; /* 24 B/ext compat desc */
				count += 16; /* header */
				put_unaligned_le32(count, buf);
				value = w_length;
				अगर (w_length > 0x10) अणु
					value = fill_ext_compat(os_desc_cfg, buf);
					value = min_t(u16, w_length, value);
				पूर्ण
				अवरोध;
			हाल USB_RECIP_INTERFACE:
				अगर (w_index != 0x5 || (w_value >> 8))
					अवरोध;
				पूर्णांकerface = w_value & 0xFF;
				buf[6] = w_index;
				count = count_ext_prop(os_desc_cfg,
					पूर्णांकerface);
				put_unaligned_le16(count, buf + 8);
				count = len_ext_prop(os_desc_cfg,
					पूर्णांकerface);
				put_unaligned_le32(count, buf);
				value = w_length;
				अगर (w_length > 0x0A) अणु
					value = fill_ext_prop(os_desc_cfg,
							      पूर्णांकerface, buf);
					अगर (value >= 0)
						value = min_t(u16, w_length, value);
				पूर्ण
				अवरोध;
			पूर्ण

			जाओ check_value;
		पूर्ण

		VDBG(cdev,
			"non-core control req%02x.%02x v%04x i%04x l%d\n",
			ctrl->bRequestType, ctrl->bRequest,
			w_value, w_index, w_length);

		/* functions always handle their पूर्णांकerfaces and endpoपूर्णांकs...
		 * punt other recipients (other, WUSB, ...) to the current
		 * configuration code.
		 */
		अगर (cdev->config) अणु
			list_क्रम_each_entry(f, &cdev->config->functions, list)
				अगर (f->req_match &&
				    f->req_match(f, ctrl, false))
					जाओ try_fun_setup;
		पूर्ण अन्यथा अणु
			काष्ठा usb_configuration *c;
			list_क्रम_each_entry(c, &cdev->configs, list)
				list_क्रम_each_entry(f, &c->functions, list)
					अगर (f->req_match &&
					    f->req_match(f, ctrl, true))
						जाओ try_fun_setup;
		पूर्ण
		f = शून्य;

		चयन (ctrl->bRequestType & USB_RECIP_MASK) अणु
		हाल USB_RECIP_INTERFACE:
			अगर (!cdev->config || पूर्णांकf >= MAX_CONFIG_INTERFACES)
				अवरोध;
			f = cdev->config->पूर्णांकerface[पूर्णांकf];
			अवरोध;

		हाल USB_RECIP_ENDPOINT:
			अगर (!cdev->config)
				अवरोध;
			endp = ((w_index & 0x80) >> 3) | (w_index & 0x0f);
			list_क्रम_each_entry(f, &cdev->config->functions, list) अणु
				अगर (test_bit(endp, f->endpoपूर्णांकs))
					अवरोध;
			पूर्ण
			अगर (&f->list == &cdev->config->functions)
				f = शून्य;
			अवरोध;
		पूर्ण
try_fun_setup:
		अगर (f && f->setup)
			value = f->setup(f, ctrl);
		अन्यथा अणु
			काष्ठा usb_configuration	*c;

			c = cdev->config;
			अगर (!c)
				जाओ करोne;

			/* try current config's setup */
			अगर (c->setup) अणु
				value = c->setup(c, ctrl);
				जाओ करोne;
			पूर्ण

			/* try the only function in the current config */
			अगर (!list_is_singular(&c->functions))
				जाओ करोne;
			f = list_first_entry(&c->functions, काष्ठा usb_function,
					     list);
			अगर (f->setup)
				value = f->setup(f, ctrl);
		पूर्ण

		जाओ करोne;
	पूर्ण

check_value:
	/* respond with data transfer beक्रमe status phase? */
	अगर (value >= 0 && value != USB_GADGET_DELAYED_STATUS) अणु
		req->length = value;
		req->context = cdev;
		req->zero = value < w_length;
		value = composite_ep0_queue(cdev, req, GFP_ATOMIC);
		अगर (value < 0) अणु
			DBG(cdev, "ep_queue --> %d\n", value);
			req->status = 0;
			composite_setup_complete(gadget->ep0, req);
		पूर्ण
	पूर्ण अन्यथा अगर (value == USB_GADGET_DELAYED_STATUS && w_length != 0) अणु
		WARN(cdev,
			"%s: Delayed status not supported for w_length != 0",
			__func__);
	पूर्ण

करोne:
	/* device either stalls (value < 0) or reports success */
	वापस value;
पूर्ण

अटल व्योम __composite_disconnect(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा usb_composite_dev	*cdev = get_gadget_data(gadget);
	अचिन्हित दीर्घ			flags;

	/* REVISIT:  should we have config and device level
	 * disconnect callbacks?
	 */
	spin_lock_irqsave(&cdev->lock, flags);
	cdev->suspended = 0;
	अगर (cdev->config)
		reset_config(cdev);
	अगर (cdev->driver->disconnect)
		cdev->driver->disconnect(cdev);
	spin_unlock_irqrestore(&cdev->lock, flags);
पूर्ण

व्योम composite_disconnect(काष्ठा usb_gadget *gadget)
अणु
	usb_gadget_vbus_draw(gadget, 0);
	__composite_disconnect(gadget);
पूर्ण

व्योम composite_reset(काष्ठा usb_gadget *gadget)
अणु
	/*
	 * Section 1.4.13 Standard Downstream Port of the USB battery अक्षरging
	 * specअगरication v1.2 states that a device connected on a SDP shall only
	 * draw at max 100mA जबतक in a connected, but unconfigured state.
	 */
	usb_gadget_vbus_draw(gadget, 100);
	__composite_disconnect(gadget);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल sमाप_प्रकार suspended_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा usb_gadget *gadget = dev_to_usb_gadget(dev);
	काष्ठा usb_composite_dev *cdev = get_gadget_data(gadget);

	वापस प्र_लिखो(buf, "%d\n", cdev->suspended);
पूर्ण
अटल DEVICE_ATTR_RO(suspended);

अटल व्योम __composite_unbind(काष्ठा usb_gadget *gadget, bool unbind_driver)
अणु
	काष्ठा usb_composite_dev	*cdev = get_gadget_data(gadget);
	काष्ठा usb_gadget_strings	*gstr = cdev->driver->strings[0];
	काष्ठा usb_string		*dev_str = gstr->strings;

	/* composite_disconnect() must alपढ़ोy have been called
	 * by the underlying peripheral controller driver!
	 * so there's no i/o concurrency that could affect the
	 * state रक्षित by cdev->lock.
	 */
	WARN_ON(cdev->config);

	जबतक (!list_empty(&cdev->configs)) अणु
		काष्ठा usb_configuration	*c;
		c = list_first_entry(&cdev->configs,
				काष्ठा usb_configuration, list);
		हटाओ_config(cdev, c);
	पूर्ण
	अगर (cdev->driver->unbind && unbind_driver)
		cdev->driver->unbind(cdev);

	composite_dev_cleanup(cdev);

	अगर (dev_str[USB_GADGET_MANUFACTURER_IDX].s == cdev->def_manufacturer)
		dev_str[USB_GADGET_MANUFACTURER_IDX].s = "";

	kमुक्त(cdev->def_manufacturer);
	kमुक्त(cdev);
	set_gadget_data(gadget, शून्य);
पूर्ण

अटल व्योम composite_unbind(काष्ठा usb_gadget *gadget)
अणु
	__composite_unbind(gadget, true);
पूर्ण

अटल व्योम update_unchanged_dev_desc(काष्ठा usb_device_descriptor *new,
		स्थिर काष्ठा usb_device_descriptor *old)
अणु
	__le16 idVenकरोr;
	__le16 idProduct;
	__le16 bcdDevice;
	u8 iSerialNumber;
	u8 iManufacturer;
	u8 iProduct;

	/*
	 * these variables may have been set in
	 * usb_composite_overग_लिखो_options()
	 */
	idVenकरोr = new->idVenकरोr;
	idProduct = new->idProduct;
	bcdDevice = new->bcdDevice;
	iSerialNumber = new->iSerialNumber;
	iManufacturer = new->iManufacturer;
	iProduct = new->iProduct;

	*new = *old;
	अगर (idVenकरोr)
		new->idVenकरोr = idVenकरोr;
	अगर (idProduct)
		new->idProduct = idProduct;
	अगर (bcdDevice)
		new->bcdDevice = bcdDevice;
	अन्यथा
		new->bcdDevice = cpu_to_le16(get_शेष_bcdDevice());
	अगर (iSerialNumber)
		new->iSerialNumber = iSerialNumber;
	अगर (iManufacturer)
		new->iManufacturer = iManufacturer;
	अगर (iProduct)
		new->iProduct = iProduct;
पूर्ण

पूर्णांक composite_dev_prepare(काष्ठा usb_composite_driver *composite,
		काष्ठा usb_composite_dev *cdev)
अणु
	काष्ठा usb_gadget *gadget = cdev->gadget;
	पूर्णांक ret = -ENOMEM;

	/* pपुनः_स्मृतिate control response and buffer */
	cdev->req = usb_ep_alloc_request(gadget->ep0, GFP_KERNEL);
	अगर (!cdev->req)
		वापस -ENOMEM;

	cdev->req->buf = kदो_स्मृति(USB_COMP_EP0_बफ_मान, GFP_KERNEL);
	अगर (!cdev->req->buf)
		जाओ fail;

	ret = device_create_file(&gadget->dev, &dev_attr_suspended);
	अगर (ret)
		जाओ fail_dev;

	cdev->req->complete = composite_setup_complete;
	cdev->req->context = cdev;
	gadget->ep0->driver_data = cdev;

	cdev->driver = composite;

	/*
	 * As per USB compliance update, a device that is actively drawing
	 * more than 100mA from USB must report itself as bus-घातered in
	 * the GetStatus(DEVICE) call.
	 */
	अगर (CONFIG_USB_GADGET_VBUS_DRAW <= USB_SELF_POWER_VBUS_MAX_DRAW)
		usb_gadget_set_selfघातered(gadget);

	/* पूर्णांकerface and string IDs start at zero via kzalloc.
	 * we क्रमce endpoपूर्णांकs to start unasचिन्हित; few controller
	 * drivers will zero ep->driver_data.
	 */
	usb_ep_स्वतःconfig_reset(gadget);
	वापस 0;
fail_dev:
	kमुक्त(cdev->req->buf);
fail:
	usb_ep_मुक्त_request(gadget->ep0, cdev->req);
	cdev->req = शून्य;
	वापस ret;
पूर्ण

पूर्णांक composite_os_desc_req_prepare(काष्ठा usb_composite_dev *cdev,
				  काष्ठा usb_ep *ep0)
अणु
	पूर्णांक ret = 0;

	cdev->os_desc_req = usb_ep_alloc_request(ep0, GFP_KERNEL);
	अगर (!cdev->os_desc_req) अणु
		ret = -ENOMEM;
		जाओ end;
	पूर्ण

	cdev->os_desc_req->buf = kदो_स्मृति(USB_COMP_EP0_OS_DESC_बफ_मान,
					 GFP_KERNEL);
	अगर (!cdev->os_desc_req->buf) अणु
		ret = -ENOMEM;
		usb_ep_मुक्त_request(ep0, cdev->os_desc_req);
		जाओ end;
	पूर्ण
	cdev->os_desc_req->context = cdev;
	cdev->os_desc_req->complete = composite_setup_complete;
end:
	वापस ret;
पूर्ण

व्योम composite_dev_cleanup(काष्ठा usb_composite_dev *cdev)
अणु
	काष्ठा usb_gadget_string_container *uc, *पंचांगp;
	काष्ठा usb_ep			   *ep, *पंचांगp_ep;

	list_क्रम_each_entry_safe(uc, पंचांगp, &cdev->gstrings, list) अणु
		list_del(&uc->list);
		kमुक्त(uc);
	पूर्ण
	अगर (cdev->os_desc_req) अणु
		अगर (cdev->os_desc_pending)
			usb_ep_dequeue(cdev->gadget->ep0, cdev->os_desc_req);

		kमुक्त(cdev->os_desc_req->buf);
		cdev->os_desc_req->buf = शून्य;
		usb_ep_मुक्त_request(cdev->gadget->ep0, cdev->os_desc_req);
		cdev->os_desc_req = शून्य;
	पूर्ण
	अगर (cdev->req) अणु
		अगर (cdev->setup_pending)
			usb_ep_dequeue(cdev->gadget->ep0, cdev->req);

		kमुक्त(cdev->req->buf);
		cdev->req->buf = शून्य;
		usb_ep_मुक्त_request(cdev->gadget->ep0, cdev->req);
		cdev->req = शून्य;
	पूर्ण
	cdev->next_string_id = 0;
	device_हटाओ_file(&cdev->gadget->dev, &dev_attr_suspended);

	/*
	 * Some UDC backends have a dynamic EP allocation scheme.
	 *
	 * In that हाल, the dispose() callback is used to notअगरy the
	 * backend that the EPs are no दीर्घer in use.
	 *
	 * Note: The UDC backend can हटाओ the EP from the ep_list as
	 *	 a result, so we need to use the _safe list iterator.
	 */
	list_क्रम_each_entry_safe(ep, पंचांगp_ep,
				 &cdev->gadget->ep_list, ep_list) अणु
		अगर (ep->ops->dispose)
			ep->ops->dispose(ep);
	पूर्ण
पूर्ण

अटल पूर्णांक composite_bind(काष्ठा usb_gadget *gadget,
		काष्ठा usb_gadget_driver *gdriver)
अणु
	काष्ठा usb_composite_dev	*cdev;
	काष्ठा usb_composite_driver	*composite = to_cdriver(gdriver);
	पूर्णांक				status = -ENOMEM;

	cdev = kzalloc(माप *cdev, GFP_KERNEL);
	अगर (!cdev)
		वापस status;

	spin_lock_init(&cdev->lock);
	cdev->gadget = gadget;
	set_gadget_data(gadget, cdev);
	INIT_LIST_HEAD(&cdev->configs);
	INIT_LIST_HEAD(&cdev->gstrings);

	status = composite_dev_prepare(composite, cdev);
	अगर (status)
		जाओ fail;

	/* composite gadget needs to assign strings क्रम whole device (like
	 * serial number), रेजिस्टर function drivers, potentially update
	 * घातer state and consumption, etc
	 */
	status = composite->bind(cdev);
	अगर (status < 0)
		जाओ fail;

	अगर (cdev->use_os_string) अणु
		status = composite_os_desc_req_prepare(cdev, gadget->ep0);
		अगर (status)
			जाओ fail;
	पूर्ण

	update_unchanged_dev_desc(&cdev->desc, composite->dev);

	/* has userspace failed to provide a serial number? */
	अगर (composite->needs_serial && !cdev->desc.iSerialNumber)
		WARNING(cdev, "userspace failed to provide iSerialNumber\n");

	INFO(cdev, "%s ready\n", composite->name);
	वापस 0;

fail:
	__composite_unbind(gadget, false);
	वापस status;
पूर्ण

/*-------------------------------------------------------------------------*/

व्योम composite_suspend(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा usb_composite_dev	*cdev = get_gadget_data(gadget);
	काष्ठा usb_function		*f;

	/* REVISIT:  should we have config level
	 * suspend/resume callbacks?
	 */
	DBG(cdev, "suspend\n");
	अगर (cdev->config) अणु
		list_क्रम_each_entry(f, &cdev->config->functions, list) अणु
			अगर (f->suspend)
				f->suspend(f);
		पूर्ण
	पूर्ण
	अगर (cdev->driver->suspend)
		cdev->driver->suspend(cdev);

	cdev->suspended = 1;

	usb_gadget_set_selfघातered(gadget);
	usb_gadget_vbus_draw(gadget, 2);
पूर्ण

व्योम composite_resume(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा usb_composite_dev	*cdev = get_gadget_data(gadget);
	काष्ठा usb_function		*f;
	अचिन्हित			maxघातer;

	/* REVISIT:  should we have config level
	 * suspend/resume callbacks?
	 */
	DBG(cdev, "resume\n");
	अगर (cdev->driver->resume)
		cdev->driver->resume(cdev);
	अगर (cdev->config) अणु
		list_क्रम_each_entry(f, &cdev->config->functions, list) अणु
			अगर (f->resume)
				f->resume(f);
		पूर्ण

		maxघातer = cdev->config->MaxPower ?
			cdev->config->MaxPower : CONFIG_USB_GADGET_VBUS_DRAW;
		अगर (gadget->speed < USB_SPEED_SUPER)
			maxघातer = min(maxघातer, 500U);
		अन्यथा
			maxघातer = min(maxघातer, 900U);

		अगर (maxघातer > USB_SELF_POWER_VBUS_MAX_DRAW)
			usb_gadget_clear_selfघातered(gadget);

		usb_gadget_vbus_draw(gadget, maxघातer);
	पूर्ण

	cdev->suspended = 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल स्थिर काष्ठा usb_gadget_driver composite_driver_ढाँचा = अणु
	.bind		= composite_bind,
	.unbind		= composite_unbind,

	.setup		= composite_setup,
	.reset		= composite_reset,
	.disconnect	= composite_disconnect,

	.suspend	= composite_suspend,
	.resume		= composite_resume,

	.driver	= अणु
		.owner		= THIS_MODULE,
	पूर्ण,
पूर्ण;

/**
 * usb_composite_probe() - रेजिस्टर a composite driver
 * @driver: the driver to रेजिस्टर
 *
 * Context: single thपढ़ोed during gadget setup
 *
 * This function is used to रेजिस्टर drivers using the composite driver
 * framework.  The वापस value is zero, or a negative त्रुटि_सं value.
 * Those values normally come from the driver's @bind method, which करोes
 * all the work of setting up the driver to match the hardware.
 *
 * On successful वापस, the gadget is पढ़ोy to respond to requests from
 * the host, unless one of its components invokes usb_gadget_disconnect()
 * जबतक it was binding.  That would usually be करोne in order to रुको क्रम
 * some userspace participation.
 */
पूर्णांक usb_composite_probe(काष्ठा usb_composite_driver *driver)
अणु
	काष्ठा usb_gadget_driver *gadget_driver;

	अगर (!driver || !driver->dev || !driver->bind)
		वापस -EINVAL;

	अगर (!driver->name)
		driver->name = "composite";

	driver->gadget_driver = composite_driver_ढाँचा;
	gadget_driver = &driver->gadget_driver;

	gadget_driver->function =  (अक्षर *) driver->name;
	gadget_driver->driver.name = driver->name;
	gadget_driver->max_speed = driver->max_speed;

	वापस usb_gadget_probe_driver(gadget_driver);
पूर्ण
EXPORT_SYMBOL_GPL(usb_composite_probe);

/**
 * usb_composite_unरेजिस्टर() - unरेजिस्टर a composite driver
 * @driver: the driver to unरेजिस्टर
 *
 * This function is used to unरेजिस्टर drivers using the composite
 * driver framework.
 */
व्योम usb_composite_unरेजिस्टर(काष्ठा usb_composite_driver *driver)
अणु
	usb_gadget_unरेजिस्टर_driver(&driver->gadget_driver);
पूर्ण
EXPORT_SYMBOL_GPL(usb_composite_unरेजिस्टर);

/**
 * usb_composite_setup_जारी() - Continue with the control transfer
 * @cdev: the composite device who's control transfer was kept रुकोing
 *
 * This function must be called by the USB function driver to जारी
 * with the control transfer's data/status stage in हाल it had requested to
 * delay the data/status stages. A USB function's setup handler (e.g. set_alt())
 * can request the composite framework to delay the setup request's data/status
 * stages by वापसing USB_GADGET_DELAYED_STATUS.
 */
व्योम usb_composite_setup_जारी(काष्ठा usb_composite_dev *cdev)
अणु
	पूर्णांक			value;
	काष्ठा usb_request	*req = cdev->req;
	अचिन्हित दीर्घ		flags;

	DBG(cdev, "%s\n", __func__);
	spin_lock_irqsave(&cdev->lock, flags);

	अगर (cdev->delayed_status == 0) अणु
		WARN(cdev, "%s: Unexpected call\n", __func__);

	पूर्ण अन्यथा अगर (--cdev->delayed_status == 0) अणु
		DBG(cdev, "%s: Completing delayed status\n", __func__);
		req->length = 0;
		req->context = cdev;
		value = composite_ep0_queue(cdev, req, GFP_ATOMIC);
		अगर (value < 0) अणु
			DBG(cdev, "ep_queue --> %d\n", value);
			req->status = 0;
			composite_setup_complete(cdev->gadget->ep0, req);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&cdev->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(usb_composite_setup_जारी);

अटल अक्षर *composite_शेष_mfr(काष्ठा usb_gadget *gadget)
अणु
	वापस kaप्र_लिखो(GFP_KERNEL, "%s %s with %s", init_utsname()->sysname,
			 init_utsname()->release, gadget->name);
पूर्ण

व्योम usb_composite_overग_लिखो_options(काष्ठा usb_composite_dev *cdev,
		काष्ठा usb_composite_overग_लिखो *covr)
अणु
	काष्ठा usb_device_descriptor	*desc = &cdev->desc;
	काष्ठा usb_gadget_strings	*gstr = cdev->driver->strings[0];
	काष्ठा usb_string		*dev_str = gstr->strings;

	अगर (covr->idVenकरोr)
		desc->idVenकरोr = cpu_to_le16(covr->idVenकरोr);

	अगर (covr->idProduct)
		desc->idProduct = cpu_to_le16(covr->idProduct);

	अगर (covr->bcdDevice)
		desc->bcdDevice = cpu_to_le16(covr->bcdDevice);

	अगर (covr->serial_number) अणु
		desc->iSerialNumber = dev_str[USB_GADGET_SERIAL_IDX].id;
		dev_str[USB_GADGET_SERIAL_IDX].s = covr->serial_number;
	पूर्ण
	अगर (covr->manufacturer) अणु
		desc->iManufacturer = dev_str[USB_GADGET_MANUFACTURER_IDX].id;
		dev_str[USB_GADGET_MANUFACTURER_IDX].s = covr->manufacturer;

	पूर्ण अन्यथा अगर (!म_माप(dev_str[USB_GADGET_MANUFACTURER_IDX].s)) अणु
		desc->iManufacturer = dev_str[USB_GADGET_MANUFACTURER_IDX].id;
		cdev->def_manufacturer = composite_शेष_mfr(cdev->gadget);
		dev_str[USB_GADGET_MANUFACTURER_IDX].s = cdev->def_manufacturer;
	पूर्ण

	अगर (covr->product) अणु
		desc->iProduct = dev_str[USB_GADGET_PRODUCT_IDX].id;
		dev_str[USB_GADGET_PRODUCT_IDX].s = covr->product;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usb_composite_overग_लिखो_options);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Brownell");
