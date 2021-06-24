<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Handles the Intel 27x USB Device Controller (UDC)
 *
 * Inspired by original driver by Frank Becker, David Brownell, and others.
 * Copyright (C) 2008 Robert Jarzmik
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/clk.h>
#समावेश <linux/irq.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/platक्रमm_data/pxa2xx_udc.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>

#समावेश <linux/usb.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/phy.h>

#समावेश "pxa27x_udc.h"

/*
 * This driver handles the USB Device Controller (UDC) in Intel's PXA 27x
 * series processors.
 *
 * Such controller drivers work with a gadget driver.  The gadget driver
 * वापसs descriptors, implements configuration and data protocols used
 * by the host to पूर्णांकeract with this device, and allocates endpoपूर्णांकs to
 * the dअगरferent protocol पूर्णांकerfaces.  The controller driver भवizes
 * usb hardware so that the gadget drivers will be more portable.
 *
 * This UDC hardware wants to implement a bit too much USB protocol. The
 * biggest issues are:  that the endpoपूर्णांकs have to be set up beक्रमe the
 * controller can be enabled (minor, and not uncommon); and each endpoपूर्णांक
 * can only have one configuration, पूर्णांकerface and alternative पूर्णांकerface
 * number (major, and very unusual). Once set up, these cannot be changed
 * without a controller reset.
 *
 * The workaround is to setup all combinations necessary क्रम the gadमाला_लो which
 * will work with this driver. This is करोne in pxa_udc काष्ठाure, अटलally.
 * See pxa_udc, udc_usb_ep versus pxa_ep, and matching function find_pxa_ep.
 * (You could modअगरy this अगर needed.  Some drivers have a "fifo_mode" module
 * parameter to facilitate such changes.)
 *
 * The combinations have been tested with these gadमाला_लो :
 *  - zero gadget
 *  - file storage gadget
 *  - ether gadget
 *
 * The driver करोesn't use DMA, only IO access and IRQ callbacks. No use is
 * made of UDC's द्विगुन buffering either. USB "On-The-Go" is not implemented.
 *
 * All the requests are handled the same way :
 *  - the drivers tries to handle the request directly to the IO
 *  - अगर the IO fअगरo is not big enough, the reमुख्यing is send/received in
 *    पूर्णांकerrupt handling.
 */

#घोषणा	DRIVER_VERSION	"2008-04-18"
#घोषणा	DRIVER_DESC	"PXA 27x USB Device Controller driver"

अटल स्थिर अक्षर driver_name[] = "pxa27x_udc";
अटल काष्ठा pxa_udc *the_controller;

अटल व्योम handle_ep(काष्ठा pxa_ep *ep);

/*
 * Debug fileप्रणाली
 */
#अगर_घोषित CONFIG_USB_GADGET_DEBUG_FS

#समावेश <linux/debugfs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/seq_file.h>

अटल पूर्णांक state_dbg_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा pxa_udc *udc = s->निजी;
	u32 पंचांगp;

	अगर (!udc->driver)
		वापस -ENODEV;

	/* basic device status */
	seq_म_लिखो(s, DRIVER_DESC "\n"
		   "%s version: %s\n"
		   "Gadget driver: %s\n",
		   driver_name, DRIVER_VERSION,
		   udc->driver ? udc->driver->driver.name : "(none)");

	पंचांगp = udc_पढ़ोl(udc, UDCCR);
	seq_म_लिखो(s,
		   "udccr=0x%0x(%s%s%s%s%s%s%s%s%s%s), con=%d,inter=%d,altinter=%d\n",
		   पंचांगp,
		   (पंचांगp & UDCCR_OEN) ? " oen":"",
		   (पंचांगp & UDCCR_AALTHNP) ? " aalthnp":"",
		   (पंचांगp & UDCCR_AHNP) ? " rem" : "",
		   (पंचांगp & UDCCR_BHNP) ? " rstir" : "",
		   (पंचांगp & UDCCR_DWRE) ? " dwre" : "",
		   (पंचांगp & UDCCR_SMAC) ? " smac" : "",
		   (पंचांगp & UDCCR_EMCE) ? " emce" : "",
		   (पंचांगp & UDCCR_UDR) ? " udr" : "",
		   (पंचांगp & UDCCR_UDA) ? " uda" : "",
		   (पंचांगp & UDCCR_UDE) ? " ude" : "",
		   (पंचांगp & UDCCR_ACN) >> UDCCR_ACN_S,
		   (पंचांगp & UDCCR_AIN) >> UDCCR_AIN_S,
		   (पंचांगp & UDCCR_AAISN) >> UDCCR_AAISN_S);
	/* रेजिस्टरs क्रम device and ep0 */
	seq_म_लिखो(s, "udcicr0=0x%08x udcicr1=0x%08x\n",
		   udc_पढ़ोl(udc, UDCICR0), udc_पढ़ोl(udc, UDCICR1));
	seq_म_लिखो(s, "udcisr0=0x%08x udcisr1=0x%08x\n",
		   udc_पढ़ोl(udc, UDCISR0), udc_पढ़ोl(udc, UDCISR1));
	seq_म_लिखो(s, "udcfnr=%d\n", udc_पढ़ोl(udc, UDCFNR));
	seq_म_लिखो(s, "irqs: reset=%lu, suspend=%lu, resume=%lu, reconfig=%lu\n",
		   udc->stats.irqs_reset, udc->stats.irqs_suspend,
		   udc->stats.irqs_resume, udc->stats.irqs_reconfig);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(state_dbg);

अटल पूर्णांक queues_dbg_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा pxa_udc *udc = s->निजी;
	काष्ठा pxa_ep *ep;
	काष्ठा pxa27x_request *req;
	पूर्णांक i, maxpkt;

	अगर (!udc->driver)
		वापस -ENODEV;

	/* dump endpoपूर्णांक queues */
	क्रम (i = 0; i < NR_PXA_ENDPOINTS; i++) अणु
		ep = &udc->pxa_ep[i];
		maxpkt = ep->fअगरo_size;
		seq_म_लिखो(s,  "%-12s max_pkt=%d %s\n",
			   EPNAME(ep), maxpkt, "pio");

		अगर (list_empty(&ep->queue)) अणु
			seq_माला_दो(s, "\t(nothing queued)\n");
			जारी;
		पूर्ण

		list_क्रम_each_entry(req, &ep->queue, queue) अणु
			seq_म_लिखो(s,  "\treq %p len %d/%d buf %p\n",
				   &req->req, req->req.actual,
				   req->req.length, req->req.buf);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(queues_dbg);

अटल पूर्णांक eps_dbg_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा pxa_udc *udc = s->निजी;
	काष्ठा pxa_ep *ep;
	पूर्णांक i;
	u32 पंचांगp;

	अगर (!udc->driver)
		वापस -ENODEV;

	ep = &udc->pxa_ep[0];
	पंचांगp = udc_ep_पढ़ोl(ep, UDCCSR);
	seq_म_लिखो(s, "udccsr0=0x%03x(%s%s%s%s%s%s%s)\n",
		   पंचांगp,
		   (पंचांगp & UDCCSR0_SA) ? " sa" : "",
		   (पंचांगp & UDCCSR0_RNE) ? " rne" : "",
		   (पंचांगp & UDCCSR0_FST) ? " fst" : "",
		   (पंचांगp & UDCCSR0_SST) ? " sst" : "",
		   (पंचांगp & UDCCSR0_DME) ? " dme" : "",
		   (पंचांगp & UDCCSR0_IPR) ? " ipr" : "",
		   (पंचांगp & UDCCSR0_OPC) ? " opc" : "");
	क्रम (i = 0; i < NR_PXA_ENDPOINTS; i++) अणु
		ep = &udc->pxa_ep[i];
		पंचांगp = i? udc_ep_पढ़ोl(ep, UDCCR) : udc_पढ़ोl(udc, UDCCR);
		seq_म_लिखो(s, "%-12s: IN %lu(%lu reqs), OUT %lu(%lu reqs), irqs=%lu, udccr=0x%08x, udccsr=0x%03x, udcbcr=%d\n",
			   EPNAME(ep),
			   ep->stats.in_bytes, ep->stats.in_ops,
			   ep->stats.out_bytes, ep->stats.out_ops,
			   ep->stats.irqs,
			   पंचांगp, udc_ep_पढ़ोl(ep, UDCCSR),
			   udc_ep_पढ़ोl(ep, UDCBCR));
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(eps_dbg);

अटल व्योम pxa_init_debugfs(काष्ठा pxa_udc *udc)
अणु
	काष्ठा dentry *root;

	root = debugfs_create_dir(udc->gadget.name, usb_debug_root);
	udc->debugfs_root = root;

	debugfs_create_file("udcstate", 0400, root, udc, &state_dbg_fops);
	debugfs_create_file("queues", 0400, root, udc, &queues_dbg_fops);
	debugfs_create_file("epstate", 0400, root, udc, &eps_dbg_fops);
पूर्ण

अटल व्योम pxa_cleanup_debugfs(काष्ठा pxa_udc *udc)
अणु
	debugfs_हटाओ_recursive(udc->debugfs_root);
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम pxa_init_debugfs(काष्ठा pxa_udc *udc)
अणु
पूर्ण

अटल अंतरभूत व्योम pxa_cleanup_debugfs(काष्ठा pxa_udc *udc)
अणु
पूर्ण
#पूर्ण_अगर

/**
 * is_match_usb_pxa - check अगर usb_ep and pxa_ep match
 * @udc_usb_ep: usb endpoपूर्णांक
 * @ep: pxa endpoपूर्णांक
 * @config: configuration required in pxa_ep
 * @पूर्णांकerface: पूर्णांकerface required in pxa_ep
 * @altsetting: altsetting required in pxa_ep
 *
 * Returns 1 अगर all criteria match between pxa and usb endpoपूर्णांक, 0 otherwise
 */
अटल पूर्णांक is_match_usb_pxa(काष्ठा udc_usb_ep *udc_usb_ep, काष्ठा pxa_ep *ep,
		पूर्णांक config, पूर्णांक पूर्णांकerface, पूर्णांक altsetting)
अणु
	अगर (usb_endpoपूर्णांक_num(&udc_usb_ep->desc) != ep->addr)
		वापस 0;
	अगर (usb_endpoपूर्णांक_dir_in(&udc_usb_ep->desc) != ep->dir_in)
		वापस 0;
	अगर (usb_endpoपूर्णांक_type(&udc_usb_ep->desc) != ep->type)
		वापस 0;
	अगर ((ep->config != config) || (ep->पूर्णांकerface != पूर्णांकerface)
			|| (ep->alternate != altsetting))
		वापस 0;
	वापस 1;
पूर्ण

/**
 * find_pxa_ep - find pxa_ep काष्ठाure matching udc_usb_ep
 * @udc: pxa udc
 * @udc_usb_ep: udc_usb_ep काष्ठाure
 *
 * Match udc_usb_ep and all pxa_ep available, to see अगर one matches.
 * This is necessary because of the strong pxa hardware restriction requiring
 * that once pxa endpoपूर्णांकs are initialized, their configuration is मुक्तzed, and
 * no change can be made to their address, direction, or in which configuration,
 * पूर्णांकerface or altsetting they are active ... which dअगरfers from more usual
 * models which have endpoपूर्णांकs be roughly just addressable fअगरos, and leave
 * configuration events up to gadget drivers (like all control messages).
 *
 * Note that there is still a blurred poपूर्णांक here :
 *   - we rely on UDCCR रेजिस्टर "active interface" and "active altsetting".
 *     This is a nonsense in regard of USB spec, where multiple पूर्णांकerfaces are
 *     active at the same समय.
 *   - अगर we knew क्रम sure that the pxa can handle multiple पूर्णांकerface at the
 *     same समय, assuming Intel's Developer Guide is wrong, this function
 *     should be reviewed, and a cache of couples (अगरace, altsetting) should
 *     be kept in the pxa_udc काष्ठाure. In this हाल this function would match
 *     against the cache of couples instead of the "last altsetting" set up.
 *
 * Returns the matched pxa_ep काष्ठाure or शून्य अगर none found
 */
अटल काष्ठा pxa_ep *find_pxa_ep(काष्ठा pxa_udc *udc,
		काष्ठा udc_usb_ep *udc_usb_ep)
अणु
	पूर्णांक i;
	काष्ठा pxa_ep *ep;
	पूर्णांक cfg = udc->config;
	पूर्णांक अगरace = udc->last_पूर्णांकerface;
	पूर्णांक alt = udc->last_alternate;

	अगर (udc_usb_ep == &udc->udc_usb_ep[0])
		वापस &udc->pxa_ep[0];

	क्रम (i = 1; i < NR_PXA_ENDPOINTS; i++) अणु
		ep = &udc->pxa_ep[i];
		अगर (is_match_usb_pxa(udc_usb_ep, ep, cfg, अगरace, alt))
			वापस ep;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * update_pxa_ep_matches - update pxa_ep cached values in all udc_usb_ep
 * @udc: pxa udc
 *
 * Context: पूर्णांकerrupt handler
 *
 * Updates all pxa_ep fields in udc_usb_ep काष्ठाures, अगर this field was
 * previously set up (and is not शून्य). The update is necessary is a
 * configuration change or altsetting change was issued by the USB host.
 */
अटल व्योम update_pxa_ep_matches(काष्ठा pxa_udc *udc)
अणु
	पूर्णांक i;
	काष्ठा udc_usb_ep *udc_usb_ep;

	क्रम (i = 1; i < NR_USB_ENDPOINTS; i++) अणु
		udc_usb_ep = &udc->udc_usb_ep[i];
		अगर (udc_usb_ep->pxa_ep)
			udc_usb_ep->pxa_ep = find_pxa_ep(udc, udc_usb_ep);
	पूर्ण
पूर्ण

/**
 * pio_irq_enable - Enables irq generation क्रम one endpoपूर्णांक
 * @ep: udc endpoपूर्णांक
 */
अटल व्योम pio_irq_enable(काष्ठा pxa_ep *ep)
अणु
	काष्ठा pxa_udc *udc = ep->dev;
	पूर्णांक index = EPIDX(ep);
	u32 udcicr0 = udc_पढ़ोl(udc, UDCICR0);
	u32 udcicr1 = udc_पढ़ोl(udc, UDCICR1);

	अगर (index < 16)
		udc_ग_लिखोl(udc, UDCICR0, udcicr0 | (3 << (index * 2)));
	अन्यथा
		udc_ग_लिखोl(udc, UDCICR1, udcicr1 | (3 << ((index - 16) * 2)));
पूर्ण

/**
 * pio_irq_disable - Disables irq generation क्रम one endpoपूर्णांक
 * @ep: udc endpoपूर्णांक
 */
अटल व्योम pio_irq_disable(काष्ठा pxa_ep *ep)
अणु
	काष्ठा pxa_udc *udc = ep->dev;
	पूर्णांक index = EPIDX(ep);
	u32 udcicr0 = udc_पढ़ोl(udc, UDCICR0);
	u32 udcicr1 = udc_पढ़ोl(udc, UDCICR1);

	अगर (index < 16)
		udc_ग_लिखोl(udc, UDCICR0, udcicr0 & ~(3 << (index * 2)));
	अन्यथा
		udc_ग_लिखोl(udc, UDCICR1, udcicr1 & ~(3 << ((index - 16) * 2)));
पूर्ण

/**
 * udc_set_mask_UDCCR - set bits in UDCCR
 * @udc: udc device
 * @mask: bits to set in UDCCR
 *
 * Sets bits in UDCCR, leaving DME and FST bits as they were.
 */
अटल अंतरभूत व्योम udc_set_mask_UDCCR(काष्ठा pxa_udc *udc, पूर्णांक mask)
अणु
	u32 udccr = udc_पढ़ोl(udc, UDCCR);
	udc_ग_लिखोl(udc, UDCCR,
			(udccr & UDCCR_MASK_BITS) | (mask & UDCCR_MASK_BITS));
पूर्ण

/**
 * udc_clear_mask_UDCCR - clears bits in UDCCR
 * @udc: udc device
 * @mask: bit to clear in UDCCR
 *
 * Clears bits in UDCCR, leaving DME and FST bits as they were.
 */
अटल अंतरभूत व्योम udc_clear_mask_UDCCR(काष्ठा pxa_udc *udc, पूर्णांक mask)
अणु
	u32 udccr = udc_पढ़ोl(udc, UDCCR);
	udc_ग_लिखोl(udc, UDCCR,
			(udccr & UDCCR_MASK_BITS) & ~(mask & UDCCR_MASK_BITS));
पूर्ण

/**
 * ep_ग_लिखो_UDCCSR - set bits in UDCCSR
 * @ep: udc endpoपूर्णांक
 * @mask: bits to set in UDCCR
 *
 * Sets bits in UDCCSR (UDCCSR0 and UDCCSR*).
 *
 * A specअगरic हाल is applied to ep0 : the ACM bit is always set to 1, क्रम
 * SET_INTERFACE and SET_CONFIGURATION.
 */
अटल अंतरभूत व्योम ep_ग_लिखो_UDCCSR(काष्ठा pxa_ep *ep, पूर्णांक mask)
अणु
	अगर (is_ep0(ep))
		mask |= UDCCSR0_ACM;
	udc_ep_ग_लिखोl(ep, UDCCSR, mask);
पूर्ण

/**
 * ep_count_bytes_reमुख्य - get how many bytes in udc endpoपूर्णांक
 * @ep: udc endpoपूर्णांक
 *
 * Returns number of bytes in OUT fअगरos. Broken क्रम IN fअगरos (-EOPNOTSUPP)
 */
अटल पूर्णांक ep_count_bytes_reमुख्य(काष्ठा pxa_ep *ep)
अणु
	अगर (ep->dir_in)
		वापस -EOPNOTSUPP;
	वापस udc_ep_पढ़ोl(ep, UDCBCR) & 0x3ff;
पूर्ण

/**
 * ep_is_empty - checks अगर ep has byte पढ़ोy क्रम पढ़ोing
 * @ep: udc endpoपूर्णांक
 *
 * If endpoपूर्णांक is the control endpoपूर्णांक, checks अगर there are bytes in the
 * control endpoपूर्णांक fअगरo. If endpoपूर्णांक is a data endpoपूर्णांक, checks अगर bytes
 * are पढ़ोy क्रम पढ़ोing on OUT endpoपूर्णांक.
 *
 * Returns 0 अगर ep not empty, 1 अगर ep empty, -EOPNOTSUPP अगर IN endpoपूर्णांक
 */
अटल पूर्णांक ep_is_empty(काष्ठा pxa_ep *ep)
अणु
	पूर्णांक ret;

	अगर (!is_ep0(ep) && ep->dir_in)
		वापस -EOPNOTSUPP;
	अगर (is_ep0(ep))
		ret = !(udc_ep_पढ़ोl(ep, UDCCSR) & UDCCSR0_RNE);
	अन्यथा
		ret = !(udc_ep_पढ़ोl(ep, UDCCSR) & UDCCSR_BNE);
	वापस ret;
पूर्ण

/**
 * ep_is_full - checks अगर ep has place to ग_लिखो bytes
 * @ep: udc endpoपूर्णांक
 *
 * If endpoपूर्णांक is not the control endpoपूर्णांक and is an IN endpoपूर्णांक, checks अगर
 * there is place to ग_लिखो bytes पूर्णांकo the endpoपूर्णांक.
 *
 * Returns 0 अगर ep not full, 1 अगर ep full, -EOPNOTSUPP अगर OUT endpoपूर्णांक
 */
अटल पूर्णांक ep_is_full(काष्ठा pxa_ep *ep)
अणु
	अगर (is_ep0(ep))
		वापस (udc_ep_पढ़ोl(ep, UDCCSR) & UDCCSR0_IPR);
	अगर (!ep->dir_in)
		वापस -EOPNOTSUPP;
	वापस (!(udc_ep_पढ़ोl(ep, UDCCSR) & UDCCSR_BNF));
पूर्ण

/**
 * epout_has_pkt - checks अगर OUT endpoपूर्णांक fअगरo has a packet available
 * @ep: pxa endpoपूर्णांक
 *
 * Returns 1 अगर a complete packet is available, 0 अगर not, -EOPNOTSUPP क्रम IN ep.
 */
अटल पूर्णांक epout_has_pkt(काष्ठा pxa_ep *ep)
अणु
	अगर (!is_ep0(ep) && ep->dir_in)
		वापस -EOPNOTSUPP;
	अगर (is_ep0(ep))
		वापस (udc_ep_पढ़ोl(ep, UDCCSR) & UDCCSR0_OPC);
	वापस (udc_ep_पढ़ोl(ep, UDCCSR) & UDCCSR_PC);
पूर्ण

/**
 * set_ep0state - Set ep0 स्वतःmata state
 * @udc: udc device
 * @state: state
 */
अटल व्योम set_ep0state(काष्ठा pxa_udc *udc, पूर्णांक state)
अणु
	काष्ठा pxa_ep *ep = &udc->pxa_ep[0];
	अक्षर *old_stname = EP0_STNAME(udc);

	udc->ep0state = state;
	ep_dbg(ep, "state=%s->%s, udccsr0=0x%03x, udcbcr=%d\n", old_stname,
		EP0_STNAME(udc), udc_ep_पढ़ोl(ep, UDCCSR),
		udc_ep_पढ़ोl(ep, UDCBCR));
पूर्ण

/**
 * ep0_idle - Put control endpoपूर्णांक पूर्णांकo idle state
 * @dev: udc device
 */
अटल व्योम ep0_idle(काष्ठा pxa_udc *dev)
अणु
	set_ep0state(dev, WAIT_FOR_SETUP);
पूर्ण

/**
 * inc_ep_stats_reqs - Update ep stats counts
 * @ep: physical endpoपूर्णांक
 * @is_in: ep direction (USB_सूची_IN or 0)
 *
 */
अटल व्योम inc_ep_stats_reqs(काष्ठा pxa_ep *ep, पूर्णांक is_in)
अणु
	अगर (is_in)
		ep->stats.in_ops++;
	अन्यथा
		ep->stats.out_ops++;
पूर्ण

/**
 * inc_ep_stats_bytes - Update ep stats counts
 * @ep: physical endpoपूर्णांक
 * @count: bytes transferred on endpoपूर्णांक
 * @is_in: ep direction (USB_सूची_IN or 0)
 */
अटल व्योम inc_ep_stats_bytes(काष्ठा pxa_ep *ep, पूर्णांक count, पूर्णांक is_in)
अणु
	अगर (is_in)
		ep->stats.in_bytes += count;
	अन्यथा
		ep->stats.out_bytes += count;
पूर्ण

/**
 * pxa_ep_setup - Sets up an usb physical endpoपूर्णांक
 * @ep: pxa27x physical endpoपूर्णांक
 *
 * Find the physical pxa27x ep, and setup its UDCCR
 */
अटल व्योम pxa_ep_setup(काष्ठा pxa_ep *ep)
अणु
	u32 new_udccr;

	new_udccr = ((ep->config << UDCCONR_CN_S) & UDCCONR_CN)
		| ((ep->पूर्णांकerface << UDCCONR_IN_S) & UDCCONR_IN)
		| ((ep->alternate << UDCCONR_AISN_S) & UDCCONR_AISN)
		| ((EPADDR(ep) << UDCCONR_EN_S) & UDCCONR_EN)
		| ((EPXFERTYPE(ep) << UDCCONR_ET_S) & UDCCONR_ET)
		| ((ep->dir_in) ? UDCCONR_ED : 0)
		| ((ep->fअगरo_size << UDCCONR_MPS_S) & UDCCONR_MPS)
		| UDCCONR_EE;

	udc_ep_ग_लिखोl(ep, UDCCR, new_udccr);
पूर्ण

/**
 * pxa_eps_setup - Sets up all usb physical endpoपूर्णांकs
 * @dev: udc device
 *
 * Setup all pxa physical endpoपूर्णांकs, except ep0
 */
अटल व्योम pxa_eps_setup(काष्ठा pxa_udc *dev)
अणु
	अचिन्हित पूर्णांक i;

	dev_dbg(dev->dev, "%s: dev=%p\n", __func__, dev);

	क्रम (i = 1; i < NR_PXA_ENDPOINTS; i++)
		pxa_ep_setup(&dev->pxa_ep[i]);
पूर्ण

/**
 * pxa_ep_alloc_request - Allocate usb request
 * @_ep: usb endpoपूर्णांक
 * @gfp_flags:
 *
 * For the pxa27x, these can just wrap kदो_स्मृति/kमुक्त.  gadget drivers
 * must still pass correctly initialized endpoपूर्णांकs, since other controller
 * drivers may care about how it's currently set up (dma issues etc).
  */
अटल काष्ठा usb_request *
pxa_ep_alloc_request(काष्ठा usb_ep *_ep, gfp_t gfp_flags)
अणु
	काष्ठा pxa27x_request *req;

	req = kzalloc(माप *req, gfp_flags);
	अगर (!req)
		वापस शून्य;

	INIT_LIST_HEAD(&req->queue);
	req->in_use = 0;
	req->udc_usb_ep = container_of(_ep, काष्ठा udc_usb_ep, usb_ep);

	वापस &req->req;
पूर्ण

/**
 * pxa_ep_मुक्त_request - Free usb request
 * @_ep: usb endpoपूर्णांक
 * @_req: usb request
 *
 * Wrapper around kमुक्त to मुक्त _req
 */
अटल व्योम pxa_ep_मुक्त_request(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा pxa27x_request *req;

	req = container_of(_req, काष्ठा pxa27x_request, req);
	WARN_ON(!list_empty(&req->queue));
	kमुक्त(req);
पूर्ण

/**
 * ep_add_request - add a request to the endpoपूर्णांक's queue
 * @ep: usb endpoपूर्णांक
 * @req: usb request
 *
 * Context: ep->lock held
 *
 * Queues the request in the endpoपूर्णांक's queue, and enables the पूर्णांकerrupts
 * on the endpoपूर्णांक.
 */
अटल व्योम ep_add_request(काष्ठा pxa_ep *ep, काष्ठा pxa27x_request *req)
अणु
	अगर (unlikely(!req))
		वापस;
	ep_vdbg(ep, "req:%p, lg=%d, udccsr=0x%03x\n", req,
		req->req.length, udc_ep_पढ़ोl(ep, UDCCSR));

	req->in_use = 1;
	list_add_tail(&req->queue, &ep->queue);
	pio_irq_enable(ep);
पूर्ण

/**
 * ep_del_request - हटाओs a request from the endpoपूर्णांक's queue
 * @ep: usb endpoपूर्णांक
 * @req: usb request
 *
 * Context: ep->lock held
 *
 * Unqueue the request from the endpoपूर्णांक's queue. If there are no more requests
 * on the endpoपूर्णांक, and अगर it's not the control endpoपूर्णांक, पूर्णांकerrupts are
 * disabled on the endpoपूर्णांक.
 */
अटल व्योम ep_del_request(काष्ठा pxa_ep *ep, काष्ठा pxa27x_request *req)
अणु
	अगर (unlikely(!req))
		वापस;
	ep_vdbg(ep, "req:%p, lg=%d, udccsr=0x%03x\n", req,
		req->req.length, udc_ep_पढ़ोl(ep, UDCCSR));

	list_del_init(&req->queue);
	req->in_use = 0;
	अगर (!is_ep0(ep) && list_empty(&ep->queue))
		pio_irq_disable(ep);
पूर्ण

/**
 * req_करोne - Complete an usb request
 * @ep: pxa physical endpoपूर्णांक
 * @req: pxa request
 * @status: usb request status sent to gadget API
 * @pflags: flags of previous spinlock_irq_save() or शून्य अगर no lock held
 *
 * Context: ep->lock held अगर flags not शून्य, अन्यथा ep->lock released
 *
 * Retire a pxa27x usb request. Endpoपूर्णांक must be locked.
 */
अटल व्योम req_करोne(काष्ठा pxa_ep *ep, काष्ठा pxa27x_request *req, पूर्णांक status,
	अचिन्हित दीर्घ *pflags)
अणु
	अचिन्हित दीर्घ	flags;

	ep_del_request(ep, req);
	अगर (likely(req->req.status == -EINPROGRESS))
		req->req.status = status;
	अन्यथा
		status = req->req.status;

	अगर (status && status != -ESHUTDOWN)
		ep_dbg(ep, "complete req %p stat %d len %u/%u\n",
			&req->req, status,
			req->req.actual, req->req.length);

	अगर (pflags)
		spin_unlock_irqrestore(&ep->lock, *pflags);
	local_irq_save(flags);
	usb_gadget_giveback_request(&req->udc_usb_ep->usb_ep, &req->req);
	local_irq_restore(flags);
	अगर (pflags)
		spin_lock_irqsave(&ep->lock, *pflags);
पूर्ण

/**
 * ep_end_out_req - Ends endpoपूर्णांक OUT request
 * @ep: physical endpoपूर्णांक
 * @req: pxa request
 * @pflags: flags of previous spinlock_irq_save() or शून्य अगर no lock held
 *
 * Context: ep->lock held or released (see req_करोne())
 *
 * Ends endpoपूर्णांक OUT request (completes usb request).
 */
अटल व्योम ep_end_out_req(काष्ठा pxa_ep *ep, काष्ठा pxa27x_request *req,
	अचिन्हित दीर्घ *pflags)
अणु
	inc_ep_stats_reqs(ep, !USB_सूची_IN);
	req_करोne(ep, req, 0, pflags);
पूर्ण

/**
 * ep0_end_out_req - Ends control endpoपूर्णांक OUT request (ends data stage)
 * @ep: physical endpoपूर्णांक
 * @req: pxa request
 * @pflags: flags of previous spinlock_irq_save() or शून्य अगर no lock held
 *
 * Context: ep->lock held or released (see req_करोne())
 *
 * Ends control endpoपूर्णांक OUT request (completes usb request), and माला_दो
 * control endpoपूर्णांक पूर्णांकo idle state
 */
अटल व्योम ep0_end_out_req(काष्ठा pxa_ep *ep, काष्ठा pxa27x_request *req,
	अचिन्हित दीर्घ *pflags)
अणु
	set_ep0state(ep->dev, OUT_STATUS_STAGE);
	ep_end_out_req(ep, req, pflags);
	ep0_idle(ep->dev);
पूर्ण

/**
 * ep_end_in_req - Ends endpoपूर्णांक IN request
 * @ep: physical endpoपूर्णांक
 * @req: pxa request
 * @pflags: flags of previous spinlock_irq_save() or शून्य अगर no lock held
 *
 * Context: ep->lock held or released (see req_करोne())
 *
 * Ends endpoपूर्णांक IN request (completes usb request).
 */
अटल व्योम ep_end_in_req(काष्ठा pxa_ep *ep, काष्ठा pxa27x_request *req,
	अचिन्हित दीर्घ *pflags)
अणु
	inc_ep_stats_reqs(ep, USB_सूची_IN);
	req_करोne(ep, req, 0, pflags);
पूर्ण

/**
 * ep0_end_in_req - Ends control endpoपूर्णांक IN request (ends data stage)
 * @ep: physical endpoपूर्णांक
 * @req: pxa request
 * @pflags: flags of previous spinlock_irq_save() or शून्य अगर no lock held
 *
 * Context: ep->lock held or released (see req_करोne())
 *
 * Ends control endpoपूर्णांक IN request (completes usb request), and माला_दो
 * control endpoपूर्णांक पूर्णांकo status state
 */
अटल व्योम ep0_end_in_req(काष्ठा pxa_ep *ep, काष्ठा pxa27x_request *req,
	अचिन्हित दीर्घ *pflags)
अणु
	set_ep0state(ep->dev, IN_STATUS_STAGE);
	ep_end_in_req(ep, req, pflags);
पूर्ण

/**
 * nuke - Dequeue all requests
 * @ep: pxa endpoपूर्णांक
 * @status: usb request status
 *
 * Context: ep->lock released
 *
 * Dequeues all requests on an endpoपूर्णांक. As a side effect, पूर्णांकerrupts will be
 * disabled on that endpoपूर्णांक (because no more requests).
 */
अटल व्योम nuke(काष्ठा pxa_ep *ep, पूर्णांक status)
अणु
	काष्ठा pxa27x_request	*req;
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&ep->lock, flags);
	जबतक (!list_empty(&ep->queue)) अणु
		req = list_entry(ep->queue.next, काष्ठा pxa27x_request, queue);
		req_करोne(ep, req, status, &flags);
	पूर्ण
	spin_unlock_irqrestore(&ep->lock, flags);
पूर्ण

/**
 * पढ़ो_packet - transfer 1 packet from an OUT endpoपूर्णांक पूर्णांकo request
 * @ep: pxa physical endpoपूर्णांक
 * @req: usb request
 *
 * Takes bytes from OUT endpoपूर्णांक and transfers them info the usb request.
 * If there is less space in request than bytes received in OUT endpoपूर्णांक,
 * bytes are left in the OUT endpoपूर्णांक.
 *
 * Returns how many bytes were actually transferred
 */
अटल पूर्णांक पढ़ो_packet(काष्ठा pxa_ep *ep, काष्ठा pxa27x_request *req)
अणु
	u32 *buf;
	पूर्णांक bytes_ep, bufferspace, count, i;

	bytes_ep = ep_count_bytes_reमुख्य(ep);
	bufferspace = req->req.length - req->req.actual;

	buf = (u32 *)(req->req.buf + req->req.actual);
	prefetchw(buf);

	अगर (likely(!ep_is_empty(ep)))
		count = min(bytes_ep, bufferspace);
	अन्यथा /* zlp */
		count = 0;

	क्रम (i = count; i > 0; i -= 4)
		*buf++ = udc_ep_पढ़ोl(ep, UDCDR);
	req->req.actual += count;

	ep_ग_लिखो_UDCCSR(ep, UDCCSR_PC);

	वापस count;
पूर्ण

/**
 * ग_लिखो_packet - transfer 1 packet from request पूर्णांकo an IN endpoपूर्णांक
 * @ep: pxa physical endpoपूर्णांक
 * @req: usb request
 * @max: max bytes that fit पूर्णांकo endpoपूर्णांक
 *
 * Takes bytes from usb request, and transfers them पूर्णांकo the physical
 * endpoपूर्णांक. If there are no bytes to transfer, करोesn't ग_लिखो anything
 * to physical endpoपूर्णांक.
 *
 * Returns how many bytes were actually transferred.
 */
अटल पूर्णांक ग_लिखो_packet(काष्ठा pxa_ep *ep, काष्ठा pxa27x_request *req,
			अचिन्हित पूर्णांक max)
अणु
	पूर्णांक length, count, reमुख्य, i;
	u32 *buf;
	u8 *buf_8;

	buf = (u32 *)(req->req.buf + req->req.actual);
	prefetch(buf);

	length = min(req->req.length - req->req.actual, max);
	req->req.actual += length;

	reमुख्य = length & 0x3;
	count = length & ~(0x3);
	क्रम (i = count; i > 0 ; i -= 4)
		udc_ep_ग_लिखोl(ep, UDCDR, *buf++);

	buf_8 = (u8 *)buf;
	क्रम (i = reमुख्य; i > 0; i--)
		udc_ep_ग_लिखोb(ep, UDCDR, *buf_8++);

	ep_vdbg(ep, "length=%d+%d, udccsr=0x%03x\n", count, reमुख्य,
		udc_ep_पढ़ोl(ep, UDCCSR));

	वापस length;
पूर्ण

/**
 * पढ़ो_fअगरo - Transfer packets from OUT endpoपूर्णांक पूर्णांकo usb request
 * @ep: pxa physical endpoपूर्णांक
 * @req: usb request
 *
 * Context: पूर्णांकerrupt handler
 *
 * Unload as many packets as possible from the fअगरo we use क्रम usb OUT
 * transfers and put them पूर्णांकo the request. Caller should have made sure
 * there's at least one packet पढ़ोy.
 * Doesn't complete the request, that's the caller's job
 *
 * Returns 1 अगर the request completed, 0 otherwise
 */
अटल पूर्णांक पढ़ो_fअगरo(काष्ठा pxa_ep *ep, काष्ठा pxa27x_request *req)
अणु
	पूर्णांक count, is_लघु, completed = 0;

	जबतक (epout_has_pkt(ep)) अणु
		count = पढ़ो_packet(ep, req);
		inc_ep_stats_bytes(ep, count, !USB_सूची_IN);

		is_लघु = (count < ep->fअगरo_size);
		ep_dbg(ep, "read udccsr:%03x, count:%d bytes%s req %p %d/%d\n",
			udc_ep_पढ़ोl(ep, UDCCSR), count, is_लघु ? "/S" : "",
			&req->req, req->req.actual, req->req.length);

		/* completion */
		अगर (is_लघु || req->req.actual == req->req.length) अणु
			completed = 1;
			अवरोध;
		पूर्ण
		/* finished that packet.  the next one may be रुकोing... */
	पूर्ण
	वापस completed;
पूर्ण

/**
 * ग_लिखो_fअगरo - transfer packets from usb request पूर्णांकo an IN endpoपूर्णांक
 * @ep: pxa physical endpoपूर्णांक
 * @req: pxa usb request
 *
 * Write to an IN endpoपूर्णांक fअगरo, as many packets as possible.
 * irqs will use this to ग_लिखो the rest later.
 * caller guarantees at least one packet buffer is पढ़ोy (or a zlp).
 * Doesn't complete the request, that's the caller's job
 *
 * Returns 1 अगर request fully transferred, 0 अगर partial transfer
 */
अटल पूर्णांक ग_लिखो_fअगरo(काष्ठा pxa_ep *ep, काष्ठा pxa27x_request *req)
अणु
	अचिन्हित max;
	पूर्णांक count, is_लघु, is_last = 0, completed = 0, totcount = 0;
	u32 udccsr;

	max = ep->fअगरo_size;
	करो अणु
		udccsr = udc_ep_पढ़ोl(ep, UDCCSR);
		अगर (udccsr & UDCCSR_PC) अणु
			ep_vdbg(ep, "Clearing Transmit Complete, udccsr=%x\n",
				udccsr);
			ep_ग_लिखो_UDCCSR(ep, UDCCSR_PC);
		पूर्ण
		अगर (udccsr & UDCCSR_TRN) अणु
			ep_vdbg(ep, "Clearing Underrun on, udccsr=%x\n",
				udccsr);
			ep_ग_लिखो_UDCCSR(ep, UDCCSR_TRN);
		पूर्ण

		count = ग_लिखो_packet(ep, req, max);
		inc_ep_stats_bytes(ep, count, USB_सूची_IN);
		totcount += count;

		/* last packet is usually लघु (or a zlp) */
		अगर (unlikely(count < max)) अणु
			is_last = 1;
			is_लघु = 1;
		पूर्ण अन्यथा अणु
			अगर (likely(req->req.length > req->req.actual)
					|| req->req.zero)
				is_last = 0;
			अन्यथा
				is_last = 1;
			/* पूर्णांकerrupt/iso maxpacket may not fill the fअगरo */
			is_लघु = unlikely(max < ep->fअगरo_size);
		पूर्ण

		अगर (is_लघु)
			ep_ग_लिखो_UDCCSR(ep, UDCCSR_SP);

		/* requests complete when all IN data is in the FIFO */
		अगर (is_last) अणु
			completed = 1;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (!ep_is_full(ep));

	ep_dbg(ep, "wrote count:%d bytes%s%s, left:%d req=%p\n",
			totcount, is_last ? "/L" : "", is_लघु ? "/S" : "",
			req->req.length - req->req.actual, &req->req);

	वापस completed;
पूर्ण

/**
 * पढ़ो_ep0_fअगरo - Transfer packets from control endpoपूर्णांक पूर्णांकo usb request
 * @ep: control endpoपूर्णांक
 * @req: pxa usb request
 *
 * Special ep0 version of the above पढ़ो_fअगरo. Reads as many bytes from control
 * endpoपूर्णांक as can be पढ़ो, and stores them पूर्णांकo usb request (limited by request
 * maximum length).
 *
 * Returns 0 अगर usb request only partially filled, 1 अगर fully filled
 */
अटल पूर्णांक पढ़ो_ep0_fअगरo(काष्ठा pxa_ep *ep, काष्ठा pxa27x_request *req)
अणु
	पूर्णांक count, is_लघु, completed = 0;

	जबतक (epout_has_pkt(ep)) अणु
		count = पढ़ो_packet(ep, req);
		ep_ग_लिखो_UDCCSR(ep, UDCCSR0_OPC);
		inc_ep_stats_bytes(ep, count, !USB_सूची_IN);

		is_लघु = (count < ep->fअगरo_size);
		ep_dbg(ep, "read udccsr:%03x, count:%d bytes%s req %p %d/%d\n",
			udc_ep_पढ़ोl(ep, UDCCSR), count, is_लघु ? "/S" : "",
			&req->req, req->req.actual, req->req.length);

		अगर (is_लघु || req->req.actual >= req->req.length) अणु
			completed = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस completed;
पूर्ण

/**
 * ग_लिखो_ep0_fअगरo - Send a request to control endpoपूर्णांक (ep0 in)
 * @ep: control endpoपूर्णांक
 * @req: request
 *
 * Context: पूर्णांकerrupt handler
 *
 * Sends a request (or a part of the request) to the control endpoपूर्णांक (ep0 in).
 * If the request करोesn't fit, the reमुख्यing part will be sent from irq.
 * The request is considered fully written only अगर either :
 *   - last ग_लिखो transferred all reमुख्यing bytes, but fअगरo was not fully filled
 *   - last ग_लिखो was a 0 length ग_लिखो
 *
 * Returns 1 अगर request fully written, 0 अगर request only partially sent
 */
अटल पूर्णांक ग_लिखो_ep0_fअगरo(काष्ठा pxa_ep *ep, काष्ठा pxa27x_request *req)
अणु
	अचिन्हित	count;
	पूर्णांक		is_last, is_लघु;

	count = ग_लिखो_packet(ep, req, EP0_FIFO_SIZE);
	inc_ep_stats_bytes(ep, count, USB_सूची_IN);

	is_लघु = (count < EP0_FIFO_SIZE);
	is_last = ((count == 0) || (count < EP0_FIFO_SIZE));

	/* Sends either a लघु packet or a 0 length packet */
	अगर (unlikely(is_लघु))
		ep_ग_लिखो_UDCCSR(ep, UDCCSR0_IPR);

	ep_dbg(ep, "in %d bytes%s%s, %d left, req=%p, udccsr0=0x%03x\n",
		count, is_लघु ? "/S" : "", is_last ? "/L" : "",
		req->req.length - req->req.actual,
		&req->req, udc_ep_पढ़ोl(ep, UDCCSR));

	वापस is_last;
पूर्ण

/**
 * pxa_ep_queue - Queue a request पूर्णांकo an IN endpoपूर्णांक
 * @_ep: usb endpoपूर्णांक
 * @_req: usb request
 * @gfp_flags: flags
 *
 * Context: thपढ़ो context or from the पूर्णांकerrupt handler in the
 * special हाल of ep0 setup :
 *   (irq->handle_ep0_ctrl_req->gadget_setup->pxa_ep_queue)
 *
 * Returns 0 अगर succedeed, error otherwise
 */
अटल पूर्णांक pxa_ep_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req,
			gfp_t gfp_flags)
अणु
	काष्ठा udc_usb_ep	*udc_usb_ep;
	काष्ठा pxa_ep		*ep;
	काष्ठा pxa27x_request	*req;
	काष्ठा pxa_udc		*dev;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			rc = 0;
	पूर्णांक			is_first_req;
	अचिन्हित		length;
	पूर्णांक			recursion_detected;

	req = container_of(_req, काष्ठा pxa27x_request, req);
	udc_usb_ep = container_of(_ep, काष्ठा udc_usb_ep, usb_ep);

	अगर (unlikely(!_req || !_req->complete || !_req->buf))
		वापस -EINVAL;

	अगर (unlikely(!_ep))
		वापस -EINVAL;

	ep = udc_usb_ep->pxa_ep;
	अगर (unlikely(!ep))
		वापस -EINVAL;

	dev = ep->dev;
	अगर (unlikely(!dev->driver || dev->gadget.speed == USB_SPEED_UNKNOWN)) अणु
		ep_dbg(ep, "bogus device state\n");
		वापस -ESHUTDOWN;
	पूर्ण

	/* iso is always one packet per request, that's the only way
	 * we can report per-packet status.  that also helps with dma.
	 */
	अगर (unlikely(EPXFERTYPE_is_ISO(ep)
			&& req->req.length > ep->fअगरo_size))
		वापस -EMSGSIZE;

	spin_lock_irqsave(&ep->lock, flags);
	recursion_detected = ep->in_handle_ep;

	is_first_req = list_empty(&ep->queue);
	ep_dbg(ep, "queue req %p(first=%s), len %d buf %p\n",
			_req, is_first_req ? "yes" : "no",
			_req->length, _req->buf);

	अगर (!ep->enabled) अणु
		_req->status = -ESHUTDOWN;
		rc = -ESHUTDOWN;
		जाओ out_locked;
	पूर्ण

	अगर (req->in_use) अणु
		ep_err(ep, "refusing to queue req %p (already queued)\n", req);
		जाओ out_locked;
	पूर्ण

	length = _req->length;
	_req->status = -EINPROGRESS;
	_req->actual = 0;

	ep_add_request(ep, req);
	spin_unlock_irqrestore(&ep->lock, flags);

	अगर (is_ep0(ep)) अणु
		चयन (dev->ep0state) अणु
		हाल WAIT_ACK_SET_CONF_INTERF:
			अगर (length == 0) अणु
				ep_end_in_req(ep, req, शून्य);
			पूर्ण अन्यथा अणु
				ep_err(ep, "got a request of %d bytes while"
					"in state WAIT_ACK_SET_CONF_INTERF\n",
					length);
				ep_del_request(ep, req);
				rc = -EL2HLT;
			पूर्ण
			ep0_idle(ep->dev);
			अवरोध;
		हाल IN_DATA_STAGE:
			अगर (!ep_is_full(ep))
				अगर (ग_लिखो_ep0_fअगरo(ep, req))
					ep0_end_in_req(ep, req, शून्य);
			अवरोध;
		हाल OUT_DATA_STAGE:
			अगर ((length == 0) || !epout_has_pkt(ep))
				अगर (पढ़ो_ep0_fअगरo(ep, req))
					ep0_end_out_req(ep, req, शून्य);
			अवरोध;
		शेष:
			ep_err(ep, "odd state %s to send me a request\n",
				EP0_STNAME(ep->dev));
			ep_del_request(ep, req);
			rc = -EL2HLT;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!recursion_detected)
			handle_ep(ep);
	पूर्ण

out:
	वापस rc;
out_locked:
	spin_unlock_irqrestore(&ep->lock, flags);
	जाओ out;
पूर्ण

/**
 * pxa_ep_dequeue - Dequeue one request
 * @_ep: usb endpoपूर्णांक
 * @_req: usb request
 *
 * Return 0 अगर no error, -EINVAL or -ECONNRESET otherwise
 */
अटल पूर्णांक pxa_ep_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा pxa_ep		*ep;
	काष्ठा udc_usb_ep	*udc_usb_ep;
	काष्ठा pxa27x_request	*req;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			rc = -EINVAL;

	अगर (!_ep)
		वापस rc;
	udc_usb_ep = container_of(_ep, काष्ठा udc_usb_ep, usb_ep);
	ep = udc_usb_ep->pxa_ep;
	अगर (!ep || is_ep0(ep))
		वापस rc;

	spin_lock_irqsave(&ep->lock, flags);

	/* make sure it's actually queued on this endpoपूर्णांक */
	list_क्रम_each_entry(req, &ep->queue, queue) अणु
		अगर (&req->req == _req) अणु
			rc = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&ep->lock, flags);
	अगर (!rc)
		req_करोne(ep, req, -ECONNRESET, शून्य);
	वापस rc;
पूर्ण

/**
 * pxa_ep_set_halt - Halts operations on one endpoपूर्णांक
 * @_ep: usb endpoपूर्णांक
 * @value:
 *
 * Returns 0 अगर no error, -EINVAL, -EROFS, -EAGAIN otherwise
 */
अटल पूर्णांक pxa_ep_set_halt(काष्ठा usb_ep *_ep, पूर्णांक value)
अणु
	काष्ठा pxa_ep		*ep;
	काष्ठा udc_usb_ep	*udc_usb_ep;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;


	अगर (!_ep)
		वापस -EINVAL;
	udc_usb_ep = container_of(_ep, काष्ठा udc_usb_ep, usb_ep);
	ep = udc_usb_ep->pxa_ep;
	अगर (!ep || is_ep0(ep))
		वापस -EINVAL;

	अगर (value == 0) अणु
		/*
		 * This path (reset toggle+halt) is needed to implement
		 * SET_INTERFACE on normal hardware.  but it can't be
		 * करोne from software on the PXA UDC, and the hardware
		 * क्रममाला_लो to करो it as part of SET_INTERFACE स्वतःmagic.
		 */
		ep_dbg(ep, "only host can clear halt\n");
		वापस -EROFS;
	पूर्ण

	spin_lock_irqsave(&ep->lock, flags);

	rc = -EAGAIN;
	अगर (ep->dir_in	&& (ep_is_full(ep) || !list_empty(&ep->queue)))
		जाओ out;

	/* FST, FEF bits are the same क्रम control and non control endpoपूर्णांकs */
	rc = 0;
	ep_ग_लिखो_UDCCSR(ep, UDCCSR_FST | UDCCSR_FEF);
	अगर (is_ep0(ep))
		set_ep0state(ep->dev, STALL);

out:
	spin_unlock_irqrestore(&ep->lock, flags);
	वापस rc;
पूर्ण

/**
 * pxa_ep_fअगरo_status - Get how many bytes in physical endpoपूर्णांक
 * @_ep: usb endpoपूर्णांक
 *
 * Returns number of bytes in OUT fअगरos. Broken क्रम IN fअगरos.
 */
अटल पूर्णांक pxa_ep_fअगरo_status(काष्ठा usb_ep *_ep)
अणु
	काष्ठा pxa_ep		*ep;
	काष्ठा udc_usb_ep	*udc_usb_ep;

	अगर (!_ep)
		वापस -ENODEV;
	udc_usb_ep = container_of(_ep, काष्ठा udc_usb_ep, usb_ep);
	ep = udc_usb_ep->pxa_ep;
	अगर (!ep || is_ep0(ep))
		वापस -ENODEV;

	अगर (ep->dir_in)
		वापस -EOPNOTSUPP;
	अगर (ep->dev->gadget.speed == USB_SPEED_UNKNOWN || ep_is_empty(ep))
		वापस 0;
	अन्यथा
		वापस ep_count_bytes_reमुख्य(ep) + 1;
पूर्ण

/**
 * pxa_ep_fअगरo_flush - Flushes one endpoपूर्णांक
 * @_ep: usb endpoपूर्णांक
 *
 * Discards all data in one endpoपूर्णांक(IN or OUT), except control endpoपूर्णांक.
 */
अटल व्योम pxa_ep_fअगरo_flush(काष्ठा usb_ep *_ep)
अणु
	काष्ठा pxa_ep		*ep;
	काष्ठा udc_usb_ep	*udc_usb_ep;
	अचिन्हित दीर्घ		flags;

	अगर (!_ep)
		वापस;
	udc_usb_ep = container_of(_ep, काष्ठा udc_usb_ep, usb_ep);
	ep = udc_usb_ep->pxa_ep;
	अगर (!ep || is_ep0(ep))
		वापस;

	spin_lock_irqsave(&ep->lock, flags);

	अगर (unlikely(!list_empty(&ep->queue)))
		ep_dbg(ep, "called while queue list not empty\n");
	ep_dbg(ep, "called\n");

	/* क्रम OUT, just पढ़ो and discard the FIFO contents. */
	अगर (!ep->dir_in) अणु
		जबतक (!ep_is_empty(ep))
			udc_ep_पढ़ोl(ep, UDCDR);
	पूर्ण अन्यथा अणु
		/* most IN status is the same, but ISO can't stall */
		ep_ग_लिखो_UDCCSR(ep,
				UDCCSR_PC | UDCCSR_FEF | UDCCSR_TRN
				| (EPXFERTYPE_is_ISO(ep) ? 0 : UDCCSR_SST));
	पूर्ण

	spin_unlock_irqrestore(&ep->lock, flags);
पूर्ण

/**
 * pxa_ep_enable - Enables usb endpoपूर्णांक
 * @_ep: usb endpoपूर्णांक
 * @desc: usb endpoपूर्णांक descriptor
 *
 * Nothing much to करो here, as ep configuration is करोne once and क्रम all
 * beक्रमe udc is enabled. After udc enable, no physical endpoपूर्णांक configuration
 * can be changed.
 * Function makes sanity checks and flushes the endpoपूर्णांक.
 */
अटल पूर्णांक pxa_ep_enable(काष्ठा usb_ep *_ep,
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा pxa_ep		*ep;
	काष्ठा udc_usb_ep	*udc_usb_ep;
	काष्ठा pxa_udc		*udc;

	अगर (!_ep || !desc)
		वापस -EINVAL;

	udc_usb_ep = container_of(_ep, काष्ठा udc_usb_ep, usb_ep);
	अगर (udc_usb_ep->pxa_ep) अणु
		ep = udc_usb_ep->pxa_ep;
		ep_warn(ep, "usb_ep %s already enabled, doing nothing\n",
			_ep->name);
	पूर्ण अन्यथा अणु
		ep = find_pxa_ep(udc_usb_ep->dev, udc_usb_ep);
	पूर्ण

	अगर (!ep || is_ep0(ep)) अणु
		dev_err(udc_usb_ep->dev->dev,
			"unable to match pxa_ep for ep %s\n",
			_ep->name);
		वापस -EINVAL;
	पूर्ण

	अगर ((desc->bDescriptorType != USB_DT_ENDPOINT)
			|| (ep->type != usb_endpoपूर्णांक_type(desc))) अणु
		ep_err(ep, "type mismatch\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ep->fअगरo_size < usb_endpoपूर्णांक_maxp(desc)) अणु
		ep_err(ep, "bad maxpacket\n");
		वापस -दुस्फल;
	पूर्ण

	udc_usb_ep->pxa_ep = ep;
	udc = ep->dev;

	अगर (!udc->driver || udc->gadget.speed == USB_SPEED_UNKNOWN) अणु
		ep_err(ep, "bogus device state\n");
		वापस -ESHUTDOWN;
	पूर्ण

	ep->enabled = 1;

	/* flush fअगरo (mostly क्रम OUT buffers) */
	pxa_ep_fअगरo_flush(_ep);

	ep_dbg(ep, "enabled\n");
	वापस 0;
पूर्ण

/**
 * pxa_ep_disable - Disable usb endpoपूर्णांक
 * @_ep: usb endpoपूर्णांक
 *
 * Same as क्रम pxa_ep_enable, no physical endpoपूर्णांक configuration can be
 * changed.
 * Function flushes the endpoपूर्णांक and related requests.
 */
अटल पूर्णांक pxa_ep_disable(काष्ठा usb_ep *_ep)
अणु
	काष्ठा pxa_ep		*ep;
	काष्ठा udc_usb_ep	*udc_usb_ep;

	अगर (!_ep)
		वापस -EINVAL;

	udc_usb_ep = container_of(_ep, काष्ठा udc_usb_ep, usb_ep);
	ep = udc_usb_ep->pxa_ep;
	अगर (!ep || is_ep0(ep) || !list_empty(&ep->queue))
		वापस -EINVAL;

	ep->enabled = 0;
	nuke(ep, -ESHUTDOWN);

	pxa_ep_fअगरo_flush(_ep);
	udc_usb_ep->pxa_ep = शून्य;

	ep_dbg(ep, "disabled\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops pxa_ep_ops = अणु
	.enable		= pxa_ep_enable,
	.disable	= pxa_ep_disable,

	.alloc_request	= pxa_ep_alloc_request,
	.मुक्त_request	= pxa_ep_मुक्त_request,

	.queue		= pxa_ep_queue,
	.dequeue	= pxa_ep_dequeue,

	.set_halt	= pxa_ep_set_halt,
	.fअगरo_status	= pxa_ep_fअगरo_status,
	.fअगरo_flush	= pxa_ep_fअगरo_flush,
पूर्ण;

/**
 * dplus_pullup - Connect or disconnect pullup resistor to D+ pin
 * @udc: udc device
 * @on: 0 अगर disconnect pullup resistor, 1 otherwise
 * Context: any
 *
 * Handle D+ pullup resistor, make the device visible to the usb bus, and
 * declare it as a full speed usb device
 */
अटल व्योम dplus_pullup(काष्ठा pxa_udc *udc, पूर्णांक on)
अणु
	अगर (udc->gpiod) अणु
		gpiod_set_value(udc->gpiod, on);
	पूर्ण अन्यथा अगर (udc->udc_command) अणु
		अगर (on)
			udc->udc_command(PXA2XX_UDC_CMD_CONNECT);
		अन्यथा
			udc->udc_command(PXA2XX_UDC_CMD_DISCONNECT);
	पूर्ण
	udc->pullup_on = on;
पूर्ण

/**
 * pxa_udc_get_frame - Returns usb frame number
 * @_gadget: usb gadget
 */
अटल पूर्णांक pxa_udc_get_frame(काष्ठा usb_gadget *_gadget)
अणु
	काष्ठा pxa_udc *udc = to_gadget_udc(_gadget);

	वापस (udc_पढ़ोl(udc, UDCFNR) & 0x7ff);
पूर्ण

/**
 * pxa_udc_wakeup - Force udc device out of suspend
 * @_gadget: usb gadget
 *
 * Returns 0 अगर successful, error code otherwise
 */
अटल पूर्णांक pxa_udc_wakeup(काष्ठा usb_gadget *_gadget)
अणु
	काष्ठा pxa_udc *udc = to_gadget_udc(_gadget);

	/* host may not have enabled remote wakeup */
	अगर ((udc_पढ़ोl(udc, UDCCR) & UDCCR_DWRE) == 0)
		वापस -EHOSTUNREACH;
	udc_set_mask_UDCCR(udc, UDCCR_UDR);
	वापस 0;
पूर्ण

अटल व्योम udc_enable(काष्ठा pxa_udc *udc);
अटल व्योम udc_disable(काष्ठा pxa_udc *udc);

/**
 * should_enable_udc - Tells अगर UDC should be enabled
 * @udc: udc device
 * Context: any
 *
 * The UDC should be enabled अगर :
 *  - the pullup resistor is connected
 *  - and a gadget driver is bound
 *  - and vbus is sensed (or no vbus sense is available)
 *
 * Returns 1 अगर UDC should be enabled, 0 otherwise
 */
अटल पूर्णांक should_enable_udc(काष्ठा pxa_udc *udc)
अणु
	पूर्णांक put_on;

	put_on = ((udc->pullup_on) && (udc->driver));
	put_on &= ((udc->vbus_sensed) || (IS_ERR_OR_शून्य(udc->transceiver)));
	वापस put_on;
पूर्ण

/**
 * should_disable_udc - Tells अगर UDC should be disabled
 * @udc: udc device
 * Context: any
 *
 * The UDC should be disabled अगर :
 *  - the pullup resistor is not connected
 *  - or no gadget driver is bound
 *  - or no vbus is sensed (when vbus sesing is available)
 *
 * Returns 1 अगर UDC should be disabled
 */
अटल पूर्णांक should_disable_udc(काष्ठा pxa_udc *udc)
अणु
	पूर्णांक put_off;

	put_off = ((!udc->pullup_on) || (!udc->driver));
	put_off |= ((!udc->vbus_sensed) && (!IS_ERR_OR_शून्य(udc->transceiver)));
	वापस put_off;
पूर्ण

/**
 * pxa_udc_pullup - Offer manual D+ pullup control
 * @_gadget: usb gadget using the control
 * @is_active: 0 अगर disconnect, अन्यथा connect D+ pullup resistor
 *
 * Context: task context, might sleep
 *
 * Returns 0 अगर OK, -EOPNOTSUPP अगर udc driver करोesn't handle D+ pullup
 */
अटल पूर्णांक pxa_udc_pullup(काष्ठा usb_gadget *_gadget, पूर्णांक is_active)
अणु
	काष्ठा pxa_udc *udc = to_gadget_udc(_gadget);

	अगर (!udc->gpiod && !udc->udc_command)
		वापस -EOPNOTSUPP;

	dplus_pullup(udc, is_active);

	अगर (should_enable_udc(udc))
		udc_enable(udc);
	अगर (should_disable_udc(udc))
		udc_disable(udc);
	वापस 0;
पूर्ण

/**
 * pxa_udc_vbus_session - Called by बाह्यal transceiver to enable/disable udc
 * @_gadget: usb gadget
 * @is_active: 0 अगर should disable the udc, 1 अगर should enable
 *
 * Enables the udc, and optionnaly activates D+ pullup resistor. Or disables the
 * udc, and deactivates D+ pullup resistor.
 *
 * Returns 0
 */
अटल पूर्णांक pxa_udc_vbus_session(काष्ठा usb_gadget *_gadget, पूर्णांक is_active)
अणु
	काष्ठा pxa_udc *udc = to_gadget_udc(_gadget);

	udc->vbus_sensed = is_active;
	अगर (should_enable_udc(udc))
		udc_enable(udc);
	अगर (should_disable_udc(udc))
		udc_disable(udc);

	वापस 0;
पूर्ण

/**
 * pxa_udc_vbus_draw - Called by gadget driver after SET_CONFIGURATION completed
 * @_gadget: usb gadget
 * @mA: current drawn
 *
 * Context: task context, might sleep
 *
 * Called after a configuration was chosen by a USB host, to inक्रमm how much
 * current can be drawn by the device from VBus line.
 *
 * Returns 0 or -EOPNOTSUPP अगर no transceiver is handling the udc
 */
अटल पूर्णांक pxa_udc_vbus_draw(काष्ठा usb_gadget *_gadget, अचिन्हित mA)
अणु
	काष्ठा pxa_udc *udc;

	udc = to_gadget_udc(_gadget);
	अगर (!IS_ERR_OR_शून्य(udc->transceiver))
		वापस usb_phy_set_घातer(udc->transceiver, mA);
	वापस -EOPNOTSUPP;
पूर्ण

/**
 * pxa_udc_phy_event - Called by phy upon VBus event
 * @nb: notअगरier block
 * @action: phy action, is vbus connect or disconnect
 * @data: the usb_gadget काष्ठाure in pxa_udc
 *
 * Called by the USB Phy when a cable connect or disconnect is sensed.
 *
 * Returns 0
 */
अटल पूर्णांक pxa_udc_phy_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action,
			     व्योम *data)
अणु
	काष्ठा usb_gadget *gadget = data;

	चयन (action) अणु
	हाल USB_EVENT_VBUS:
		usb_gadget_vbus_connect(gadget);
		वापस NOTIFY_OK;
	हाल USB_EVENT_NONE:
		usb_gadget_vbus_disconnect(gadget);
		वापस NOTIFY_OK;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण
पूर्ण

अटल काष्ठा notअगरier_block pxa27x_udc_phy = अणु
	.notअगरier_call = pxa_udc_phy_event,
पूर्ण;

अटल पूर्णांक pxa27x_udc_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver);
अटल पूर्णांक pxa27x_udc_stop(काष्ठा usb_gadget *g);

अटल स्थिर काष्ठा usb_gadget_ops pxa_udc_ops = अणु
	.get_frame	= pxa_udc_get_frame,
	.wakeup		= pxa_udc_wakeup,
	.pullup		= pxa_udc_pullup,
	.vbus_session	= pxa_udc_vbus_session,
	.vbus_draw	= pxa_udc_vbus_draw,
	.udc_start	= pxa27x_udc_start,
	.udc_stop	= pxa27x_udc_stop,
पूर्ण;

/**
 * udc_disable - disable udc device controller
 * @udc: udc device
 * Context: any
 *
 * Disables the udc device : disables घड़ीs, udc पूर्णांकerrupts, control endpoपूर्णांक
 * पूर्णांकerrupts.
 */
अटल व्योम udc_disable(काष्ठा pxa_udc *udc)
अणु
	अगर (!udc->enabled)
		वापस;

	udc_ग_लिखोl(udc, UDCICR0, 0);
	udc_ग_लिखोl(udc, UDCICR1, 0);

	udc_clear_mask_UDCCR(udc, UDCCR_UDE);

	ep0_idle(udc);
	udc->gadget.speed = USB_SPEED_UNKNOWN;
	clk_disable(udc->clk);

	udc->enabled = 0;
पूर्ण

/**
 * udc_init_data - Initialize udc device data काष्ठाures
 * @dev: udc device
 *
 * Initializes gadget endpoपूर्णांक list, endpoपूर्णांकs locks. No action is taken
 * on the hardware.
 */
अटल व्योम udc_init_data(काष्ठा pxa_udc *dev)
अणु
	पूर्णांक i;
	काष्ठा pxa_ep *ep;

	/* device/ep0 records init */
	INIT_LIST_HEAD(&dev->gadget.ep_list);
	INIT_LIST_HEAD(&dev->gadget.ep0->ep_list);
	dev->udc_usb_ep[0].pxa_ep = &dev->pxa_ep[0];
	dev->gadget.quirk_altset_not_supp = 1;
	ep0_idle(dev);

	/* PXA endpoपूर्णांकs init */
	क्रम (i = 0; i < NR_PXA_ENDPOINTS; i++) अणु
		ep = &dev->pxa_ep[i];

		ep->enabled = is_ep0(ep);
		INIT_LIST_HEAD(&ep->queue);
		spin_lock_init(&ep->lock);
	पूर्ण

	/* USB endpoपूर्णांकs init */
	क्रम (i = 1; i < NR_USB_ENDPOINTS; i++) अणु
		list_add_tail(&dev->udc_usb_ep[i].usb_ep.ep_list,
				&dev->gadget.ep_list);
		usb_ep_set_maxpacket_limit(&dev->udc_usb_ep[i].usb_ep,
					   dev->udc_usb_ep[i].usb_ep.maxpacket);
	पूर्ण
पूर्ण

/**
 * udc_enable - Enables the udc device
 * @udc: udc device
 *
 * Enables the udc device : enables घड़ीs, udc पूर्णांकerrupts, control endpoपूर्णांक
 * पूर्णांकerrupts, sets usb as UDC client and setups endpoपूर्णांकs.
 */
अटल व्योम udc_enable(काष्ठा pxa_udc *udc)
अणु
	अगर (udc->enabled)
		वापस;

	clk_enable(udc->clk);
	udc_ग_लिखोl(udc, UDCICR0, 0);
	udc_ग_लिखोl(udc, UDCICR1, 0);
	udc_clear_mask_UDCCR(udc, UDCCR_UDE);

	ep0_idle(udc);
	udc->gadget.speed = USB_SPEED_FULL;
	स_रखो(&udc->stats, 0, माप(udc->stats));

	pxa_eps_setup(udc);
	udc_set_mask_UDCCR(udc, UDCCR_UDE);
	ep_ग_लिखो_UDCCSR(&udc->pxa_ep[0], UDCCSR0_ACM);
	udelay(2);
	अगर (udc_पढ़ोl(udc, UDCCR) & UDCCR_EMCE)
		dev_err(udc->dev, "Configuration errors, udc disabled\n");

	/*
	 * Caller must be able to sleep in order to cope with startup transients
	 */
	msleep(100);

	/* enable suspend/resume and reset irqs */
	udc_ग_लिखोl(udc, UDCICR1,
			UDCICR1_IECC | UDCICR1_IERU
			| UDCICR1_IESU | UDCICR1_IERS);

	/* enable ep0 irqs */
	pio_irq_enable(&udc->pxa_ep[0]);

	udc->enabled = 1;
पूर्ण

/**
 * pxa27x_start - Register gadget driver
 * @g: gadget
 * @driver: gadget driver
 *
 * When a driver is successfully रेजिस्टरed, it will receive control requests
 * including set_configuration(), which enables non-control requests.  Then
 * usb traffic follows until a disconnect is reported.  Then a host may connect
 * again, or the driver might get unbound.
 *
 * Note that the udc is not स्वतःmatically enabled. Check function
 * should_enable_udc().
 *
 * Returns 0 अगर no error, -EINVAL, -ENODEV, -EBUSY otherwise
 */
अटल पूर्णांक pxa27x_udc_start(काष्ठा usb_gadget *g,
		काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा pxa_udc *udc = to_pxa(g);
	पूर्णांक retval;

	/* first hook up the driver ... */
	udc->driver = driver;

	अगर (!IS_ERR_OR_शून्य(udc->transceiver)) अणु
		retval = otg_set_peripheral(udc->transceiver->otg,
						&udc->gadget);
		अगर (retval) अणु
			dev_err(udc->dev, "can't bind to transceiver\n");
			जाओ fail;
		पूर्ण
	पूर्ण

	अगर (should_enable_udc(udc))
		udc_enable(udc);
	वापस 0;

fail:
	udc->driver = शून्य;
	वापस retval;
पूर्ण

/**
 * stop_activity - Stops udc endpoपूर्णांकs
 * @udc: udc device
 *
 * Disables all udc endpoपूर्णांकs (even control endpoपूर्णांक), report disconnect to
 * the gadget user.
 */
अटल व्योम stop_activity(काष्ठा pxa_udc *udc)
अणु
	पूर्णांक i;

	udc->gadget.speed = USB_SPEED_UNKNOWN;

	क्रम (i = 0; i < NR_USB_ENDPOINTS; i++)
		pxa_ep_disable(&udc->udc_usb_ep[i].usb_ep);
पूर्ण

/**
 * pxa27x_udc_stop - Unरेजिस्टर the gadget driver
 * @g: gadget
 *
 * Returns 0 अगर no error, -ENODEV, -EINVAL otherwise
 */
अटल पूर्णांक pxa27x_udc_stop(काष्ठा usb_gadget *g)
अणु
	काष्ठा pxa_udc *udc = to_pxa(g);

	stop_activity(udc);
	udc_disable(udc);

	udc->driver = शून्य;

	अगर (!IS_ERR_OR_शून्य(udc->transceiver))
		वापस otg_set_peripheral(udc->transceiver->otg, शून्य);
	वापस 0;
पूर्ण

/**
 * handle_ep0_ctrl_req - handle control endpoपूर्णांक control request
 * @udc: udc device
 * @req: control request
 */
अटल व्योम handle_ep0_ctrl_req(काष्ठा pxa_udc *udc,
				काष्ठा pxa27x_request *req)
अणु
	काष्ठा pxa_ep *ep = &udc->pxa_ep[0];
	जोड़ अणु
		काष्ठा usb_ctrlrequest	r;
		u32			word[2];
	पूर्ण u;
	पूर्णांक i;
	पूर्णांक have_extrabytes = 0;
	अचिन्हित दीर्घ flags;

	nuke(ep, -EPROTO);
	spin_lock_irqsave(&ep->lock, flags);

	/*
	 * In the PXA320 manual, in the section about Back-to-Back setup
	 * packets, it describes this situation.  The solution is to set OPC to
	 * get rid of the status packet, and then जारी with the setup
	 * packet. Generalize to pxa27x CPUs.
	 */
	अगर (epout_has_pkt(ep) && (ep_count_bytes_reमुख्य(ep) == 0))
		ep_ग_लिखो_UDCCSR(ep, UDCCSR0_OPC);

	/* पढ़ो SETUP packet */
	क्रम (i = 0; i < 2; i++) अणु
		अगर (unlikely(ep_is_empty(ep)))
			जाओ stall;
		u.word[i] = udc_ep_पढ़ोl(ep, UDCDR);
	पूर्ण

	have_extrabytes = !ep_is_empty(ep);
	जबतक (!ep_is_empty(ep)) अणु
		i = udc_ep_पढ़ोl(ep, UDCDR);
		ep_err(ep, "wrong to have extra bytes for setup : 0x%08x\n", i);
	पूर्ण

	ep_dbg(ep, "SETUP %02x.%02x v%04x i%04x l%04x\n",
		u.r.bRequestType, u.r.bRequest,
		le16_to_cpu(u.r.wValue), le16_to_cpu(u.r.wIndex),
		le16_to_cpu(u.r.wLength));
	अगर (unlikely(have_extrabytes))
		जाओ stall;

	अगर (u.r.bRequestType & USB_सूची_IN)
		set_ep0state(udc, IN_DATA_STAGE);
	अन्यथा
		set_ep0state(udc, OUT_DATA_STAGE);

	/* Tell UDC to enter Data Stage */
	ep_ग_लिखो_UDCCSR(ep, UDCCSR0_SA | UDCCSR0_OPC);

	spin_unlock_irqrestore(&ep->lock, flags);
	i = udc->driver->setup(&udc->gadget, &u.r);
	spin_lock_irqsave(&ep->lock, flags);
	अगर (i < 0)
		जाओ stall;
out:
	spin_unlock_irqrestore(&ep->lock, flags);
	वापस;
stall:
	ep_dbg(ep, "protocol STALL, udccsr0=%03x err %d\n",
		udc_ep_पढ़ोl(ep, UDCCSR), i);
	ep_ग_लिखो_UDCCSR(ep, UDCCSR0_FST | UDCCSR0_FTF);
	set_ep0state(udc, STALL);
	जाओ out;
पूर्ण

/**
 * handle_ep0 - Handle control endpoपूर्णांक data transfers
 * @udc: udc device
 * @fअगरo_irq: 1 अगर triggered by fअगरo service type irq
 * @opc_irq: 1 अगर triggered by output packet complete type irq
 *
 * Context : पूर्णांकerrupt handler
 *
 * Tries to transfer all pending request data पूर्णांकo the endpoपूर्णांक and/or
 * transfer all pending data in the endpoपूर्णांक पूर्णांकo usb requests.
 * Handles states of ep0 स्वतःmata.
 *
 * PXA27x hardware handles several standard usb control requests without
 * driver notअगरication.  The requests fully handled by hardware are :
 *  SET_ADDRESS, SET_FEATURE, CLEAR_FEATURE, GET_CONFIGURATION, GET_INTERFACE,
 *  GET_STATUS
 * The requests handled by hardware, but with irq notअगरication are :
 *  SYNCH_FRAME, SET_CONFIGURATION, SET_INTERFACE
 * The reमुख्यing standard requests really handled by handle_ep0 are :
 *  GET_DESCRIPTOR, SET_DESCRIPTOR, specअगरic requests.
 * Requests standardized outside of USB 2.0 chapter 9 are handled more
 * unअगरormly, by gadget drivers.
 *
 * The control endpoपूर्णांक state machine is _not_ USB spec compliant, it's even
 * hardly compliant with Intel PXA270 developers guide.
 * The key poपूर्णांकs which inferred this state machine are :
 *   - on every setup token, bit UDCCSR0_SA is उठाओd and held until cleared by
 *     software.
 *   - on every OUT packet received, UDCCSR0_OPC is उठाओd and held until
 *     cleared by software.
 *   - clearing UDCCSR0_OPC always flushes ep0. If in setup stage, never करो it
 *     beक्रमe पढ़ोing ep0.
 *     This is true only क्रम PXA27x. This is not true anymore क्रम PXA3xx family
 *     (check Back-to-Back setup packet in developers guide).
 *   - irq can be called on a "packet complete" event (opc_irq=1), जबतक
 *     UDCCSR0_OPC is not yet उठाओd (delta can be as big as 100ms
 *     from experimentation).
 *   - as UDCCSR0_SA can be activated जबतक in irq handling, and clearing
 *     UDCCSR0_OPC would flush the setup data, we almost never clear UDCCSR0_OPC
 *     => we never actually पढ़ो the "status stage" packet of an IN data stage
 *     => this is not करोcumented in Intel करोcumentation
 *   - hardware as no idea of STATUS STAGE, it only handle SETUP STAGE and DATA
 *     STAGE. The driver add STATUS STAGE to send last zero length packet in
 *     OUT_STATUS_STAGE.
 *   - special attention was needed क्रम IN_STATUS_STAGE. If a packet complete
 *     event is detected, we terminate the status stage without ackowledging the
 *     packet (not to risk to loose a potential SETUP packet)
 */
अटल व्योम handle_ep0(काष्ठा pxa_udc *udc, पूर्णांक fअगरo_irq, पूर्णांक opc_irq)
अणु
	u32			udccsr0;
	काष्ठा pxa_ep		*ep = &udc->pxa_ep[0];
	काष्ठा pxa27x_request	*req = शून्य;
	पूर्णांक			completed = 0;

	अगर (!list_empty(&ep->queue))
		req = list_entry(ep->queue.next, काष्ठा pxa27x_request, queue);

	udccsr0 = udc_ep_पढ़ोl(ep, UDCCSR);
	ep_dbg(ep, "state=%s, req=%p, udccsr0=0x%03x, udcbcr=%d, irq_msk=%x\n",
		EP0_STNAME(udc), req, udccsr0, udc_ep_पढ़ोl(ep, UDCBCR),
		(fअगरo_irq << 1 | opc_irq));

	अगर (udccsr0 & UDCCSR0_SST) अणु
		ep_dbg(ep, "clearing stall status\n");
		nuke(ep, -EPIPE);
		ep_ग_लिखो_UDCCSR(ep, UDCCSR0_SST);
		ep0_idle(udc);
	पूर्ण

	अगर (udccsr0 & UDCCSR0_SA) अणु
		nuke(ep, 0);
		set_ep0state(udc, SETUP_STAGE);
	पूर्ण

	चयन (udc->ep0state) अणु
	हाल WAIT_FOR_SETUP:
		/*
		 * Hardware bug : beware, we cannot clear OPC, since we would
		 * miss a potential OPC irq क्रम a setup packet.
		 * So, we only करो ... nothing, and hope क्रम a next irq with
		 * UDCCSR0_SA set.
		 */
		अवरोध;
	हाल SETUP_STAGE:
		udccsr0 &= UDCCSR0_CTRL_REQ_MASK;
		अगर (likely(udccsr0 == UDCCSR0_CTRL_REQ_MASK))
			handle_ep0_ctrl_req(udc, req);
		अवरोध;
	हाल IN_DATA_STAGE:			/* GET_DESCRIPTOR */
		अगर (epout_has_pkt(ep))
			ep_ग_लिखो_UDCCSR(ep, UDCCSR0_OPC);
		अगर (req && !ep_is_full(ep))
			completed = ग_लिखो_ep0_fअगरo(ep, req);
		अगर (completed)
			ep0_end_in_req(ep, req, शून्य);
		अवरोध;
	हाल OUT_DATA_STAGE:			/* SET_DESCRIPTOR */
		अगर (epout_has_pkt(ep) && req)
			completed = पढ़ो_ep0_fअगरo(ep, req);
		अगर (completed)
			ep0_end_out_req(ep, req, शून्य);
		अवरोध;
	हाल STALL:
		ep_ग_लिखो_UDCCSR(ep, UDCCSR0_FST);
		अवरोध;
	हाल IN_STATUS_STAGE:
		/*
		 * Hardware bug : beware, we cannot clear OPC, since we would
		 * miss a potential PC irq क्रम a setup packet.
		 * So, we only put the ep0 पूर्णांकo WAIT_FOR_SETUP state.
		 */
		अगर (opc_irq)
			ep0_idle(udc);
		अवरोध;
	हाल OUT_STATUS_STAGE:
	हाल WAIT_ACK_SET_CONF_INTERF:
		ep_warn(ep, "should never get in %s state here!!!\n",
				EP0_STNAME(ep->dev));
		ep0_idle(udc);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * handle_ep - Handle endpoपूर्णांक data tranfers
 * @ep: pxa physical endpoपूर्णांक
 *
 * Tries to transfer all pending request data पूर्णांकo the endpoपूर्णांक and/or
 * transfer all pending data in the endpoपूर्णांक पूर्णांकo usb requests.
 *
 * Is always called from the पूर्णांकerrupt handler. ep->lock must not be held.
 */
अटल व्योम handle_ep(काष्ठा pxa_ep *ep)
अणु
	काष्ठा pxa27x_request	*req;
	पूर्णांक completed;
	u32 udccsr;
	पूर्णांक is_in = ep->dir_in;
	पूर्णांक loop = 0;
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&ep->lock, flags);
	अगर (ep->in_handle_ep)
		जाओ recursion_detected;
	ep->in_handle_ep = 1;

	करो अणु
		completed = 0;
		udccsr = udc_ep_पढ़ोl(ep, UDCCSR);

		अगर (likely(!list_empty(&ep->queue)))
			req = list_entry(ep->queue.next,
					काष्ठा pxa27x_request, queue);
		अन्यथा
			req = शून्य;

		ep_dbg(ep, "req:%p, udccsr 0x%03x loop=%d\n",
				req, udccsr, loop++);

		अगर (unlikely(udccsr & (UDCCSR_SST | UDCCSR_TRN)))
			udc_ep_ग_लिखोl(ep, UDCCSR,
					udccsr & (UDCCSR_SST | UDCCSR_TRN));
		अगर (!req)
			अवरोध;

		अगर (unlikely(is_in)) अणु
			अगर (likely(!ep_is_full(ep)))
				completed = ग_लिखो_fअगरo(ep, req);
		पूर्ण अन्यथा अणु
			अगर (likely(epout_has_pkt(ep)))
				completed = पढ़ो_fअगरo(ep, req);
		पूर्ण

		अगर (completed) अणु
			अगर (is_in)
				ep_end_in_req(ep, req, &flags);
			अन्यथा
				ep_end_out_req(ep, req, &flags);
		पूर्ण
	पूर्ण जबतक (completed);

	ep->in_handle_ep = 0;
recursion_detected:
	spin_unlock_irqrestore(&ep->lock, flags);
पूर्ण

/**
 * pxa27x_change_configuration - Handle SET_CONF usb request notअगरication
 * @udc: udc device
 * @config: usb configuration
 *
 * Post the request to upper level.
 * Don't use any pxa specअगरic harware configuration capabilities
 */
अटल व्योम pxa27x_change_configuration(काष्ठा pxa_udc *udc, पूर्णांक config)
अणु
	काष्ठा usb_ctrlrequest req ;

	dev_dbg(udc->dev, "config=%d\n", config);

	udc->config = config;
	udc->last_पूर्णांकerface = 0;
	udc->last_alternate = 0;

	req.bRequestType = 0;
	req.bRequest = USB_REQ_SET_CONFIGURATION;
	req.wValue = config;
	req.wIndex = 0;
	req.wLength = 0;

	set_ep0state(udc, WAIT_ACK_SET_CONF_INTERF);
	udc->driver->setup(&udc->gadget, &req);
	ep_ग_लिखो_UDCCSR(&udc->pxa_ep[0], UDCCSR0_AREN);
पूर्ण

/**
 * pxa27x_change_पूर्णांकerface - Handle SET_INTERF usb request notअगरication
 * @udc: udc device
 * @अगरace: पूर्णांकerface number
 * @alt: alternate setting number
 *
 * Post the request to upper level.
 * Don't use any pxa specअगरic harware configuration capabilities
 */
अटल व्योम pxa27x_change_पूर्णांकerface(काष्ठा pxa_udc *udc, पूर्णांक अगरace, पूर्णांक alt)
अणु
	काष्ठा usb_ctrlrequest  req;

	dev_dbg(udc->dev, "interface=%d, alternate setting=%d\n", अगरace, alt);

	udc->last_पूर्णांकerface = अगरace;
	udc->last_alternate = alt;

	req.bRequestType = USB_RECIP_INTERFACE;
	req.bRequest = USB_REQ_SET_INTERFACE;
	req.wValue = alt;
	req.wIndex = अगरace;
	req.wLength = 0;

	set_ep0state(udc, WAIT_ACK_SET_CONF_INTERF);
	udc->driver->setup(&udc->gadget, &req);
	ep_ग_लिखो_UDCCSR(&udc->pxa_ep[0], UDCCSR0_AREN);
पूर्ण

/*
 * irq_handle_data - Handle data transfer
 * @irq: irq IRQ number
 * @udc: dev pxa_udc device काष्ठाure
 *
 * Called from irq handler, transferts data to or from endpoपूर्णांक to queue
 */
अटल व्योम irq_handle_data(पूर्णांक irq, काष्ठा pxa_udc *udc)
अणु
	पूर्णांक i;
	काष्ठा pxa_ep *ep;
	u32 udcisr0 = udc_पढ़ोl(udc, UDCISR0) & UDCCISR0_EP_MASK;
	u32 udcisr1 = udc_पढ़ोl(udc, UDCISR1) & UDCCISR1_EP_MASK;

	अगर (udcisr0 & UDCISR_INT_MASK) अणु
		udc->pxa_ep[0].stats.irqs++;
		udc_ग_लिखोl(udc, UDCISR0, UDCISR_INT(0, UDCISR_INT_MASK));
		handle_ep0(udc, !!(udcisr0 & UDCICR_FIFOERR),
				!!(udcisr0 & UDCICR_PKTCOMPL));
	पूर्ण

	udcisr0 >>= 2;
	क्रम (i = 1; udcisr0 != 0 && i < 16; udcisr0 >>= 2, i++) अणु
		अगर (!(udcisr0 & UDCISR_INT_MASK))
			जारी;

		udc_ग_लिखोl(udc, UDCISR0, UDCISR_INT(i, UDCISR_INT_MASK));

		WARN_ON(i >= ARRAY_SIZE(udc->pxa_ep));
		अगर (i < ARRAY_SIZE(udc->pxa_ep)) अणु
			ep = &udc->pxa_ep[i];
			ep->stats.irqs++;
			handle_ep(ep);
		पूर्ण
	पूर्ण

	क्रम (i = 16; udcisr1 != 0 && i < 24; udcisr1 >>= 2, i++) अणु
		udc_ग_लिखोl(udc, UDCISR1, UDCISR_INT(i - 16, UDCISR_INT_MASK));
		अगर (!(udcisr1 & UDCISR_INT_MASK))
			जारी;

		WARN_ON(i >= ARRAY_SIZE(udc->pxa_ep));
		अगर (i < ARRAY_SIZE(udc->pxa_ep)) अणु
			ep = &udc->pxa_ep[i];
			ep->stats.irqs++;
			handle_ep(ep);
		पूर्ण
	पूर्ण

पूर्ण

/**
 * irq_udc_suspend - Handle IRQ "UDC Suspend"
 * @udc: udc device
 */
अटल व्योम irq_udc_suspend(काष्ठा pxa_udc *udc)
अणु
	udc_ग_लिखोl(udc, UDCISR1, UDCISR1_IRSU);
	udc->stats.irqs_suspend++;

	अगर (udc->gadget.speed != USB_SPEED_UNKNOWN
			&& udc->driver && udc->driver->suspend)
		udc->driver->suspend(&udc->gadget);
	ep0_idle(udc);
पूर्ण

/**
  * irq_udc_resume - Handle IRQ "UDC Resume"
  * @udc: udc device
  */
अटल व्योम irq_udc_resume(काष्ठा pxa_udc *udc)
अणु
	udc_ग_लिखोl(udc, UDCISR1, UDCISR1_IRRU);
	udc->stats.irqs_resume++;

	अगर (udc->gadget.speed != USB_SPEED_UNKNOWN
			&& udc->driver && udc->driver->resume)
		udc->driver->resume(&udc->gadget);
पूर्ण

/**
 * irq_udc_reconfig - Handle IRQ "UDC Change Configuration"
 * @udc: udc device
 */
अटल व्योम irq_udc_reconfig(काष्ठा pxa_udc *udc)
अणु
	अचिन्हित config, पूर्णांकerface, alternate, config_change;
	u32 udccr = udc_पढ़ोl(udc, UDCCR);

	udc_ग_लिखोl(udc, UDCISR1, UDCISR1_IRCC);
	udc->stats.irqs_reconfig++;

	config = (udccr & UDCCR_ACN) >> UDCCR_ACN_S;
	config_change = (config != udc->config);
	pxa27x_change_configuration(udc, config);

	पूर्णांकerface = (udccr & UDCCR_AIN) >> UDCCR_AIN_S;
	alternate = (udccr & UDCCR_AAISN) >> UDCCR_AAISN_S;
	pxa27x_change_पूर्णांकerface(udc, पूर्णांकerface, alternate);

	अगर (config_change)
		update_pxa_ep_matches(udc);
	udc_set_mask_UDCCR(udc, UDCCR_SMAC);
पूर्ण

/**
 * irq_udc_reset - Handle IRQ "UDC Reset"
 * @udc: udc device
 */
अटल व्योम irq_udc_reset(काष्ठा pxa_udc *udc)
अणु
	u32 udccr = udc_पढ़ोl(udc, UDCCR);
	काष्ठा pxa_ep *ep = &udc->pxa_ep[0];

	dev_info(udc->dev, "USB reset\n");
	udc_ग_लिखोl(udc, UDCISR1, UDCISR1_IRRS);
	udc->stats.irqs_reset++;

	अगर ((udccr & UDCCR_UDA) == 0) अणु
		dev_dbg(udc->dev, "USB reset start\n");
		stop_activity(udc);
	पूर्ण
	udc->gadget.speed = USB_SPEED_FULL;
	स_रखो(&udc->stats, 0, माप udc->stats);

	nuke(ep, -EPROTO);
	ep_ग_लिखो_UDCCSR(ep, UDCCSR0_FTF | UDCCSR0_OPC);
	ep0_idle(udc);
पूर्ण

/**
 * pxa_udc_irq - Main irq handler
 * @irq: irq number
 * @_dev: udc device
 *
 * Handles all udc पूर्णांकerrupts
 */
अटल irqवापस_t pxa_udc_irq(पूर्णांक irq, व्योम *_dev)
अणु
	काष्ठा pxa_udc *udc = _dev;
	u32 udcisr0 = udc_पढ़ोl(udc, UDCISR0);
	u32 udcisr1 = udc_पढ़ोl(udc, UDCISR1);
	u32 udccr = udc_पढ़ोl(udc, UDCCR);
	u32 udcisr1_spec;

	dev_vdbg(udc->dev, "Interrupt, UDCISR0:0x%08x, UDCISR1:0x%08x, "
		 "UDCCR:0x%08x\n", udcisr0, udcisr1, udccr);

	udcisr1_spec = udcisr1 & 0xf8000000;
	अगर (unlikely(udcisr1_spec & UDCISR1_IRSU))
		irq_udc_suspend(udc);
	अगर (unlikely(udcisr1_spec & UDCISR1_IRRU))
		irq_udc_resume(udc);
	अगर (unlikely(udcisr1_spec & UDCISR1_IRCC))
		irq_udc_reconfig(udc);
	अगर (unlikely(udcisr1_spec & UDCISR1_IRRS))
		irq_udc_reset(udc);

	अगर ((udcisr0 & UDCCISR0_EP_MASK) | (udcisr1 & UDCCISR1_EP_MASK))
		irq_handle_data(irq, udc);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा pxa_udc memory = अणु
	.gadget = अणु
		.ops		= &pxa_udc_ops,
		.ep0		= &memory.udc_usb_ep[0].usb_ep,
		.name		= driver_name,
		.dev = अणु
			.init_name	= "gadget",
		पूर्ण,
	पूर्ण,

	.udc_usb_ep = अणु
		USB_EP_CTRL,
		USB_EP_OUT_BULK(1),
		USB_EP_IN_BULK(2),
		USB_EP_IN_ISO(3),
		USB_EP_OUT_ISO(4),
		USB_EP_IN_INT(5),
	पूर्ण,

	.pxa_ep = अणु
		PXA_EP_CTRL,
		/* Endpoपूर्णांकs क्रम gadget zero */
		PXA_EP_OUT_BULK(1, 1, 3, 0, 0),
		PXA_EP_IN_BULK(2,  2, 3, 0, 0),
		/* Endpoपूर्णांकs क्रम ether gadget, file storage gadget */
		PXA_EP_OUT_BULK(3, 1, 1, 0, 0),
		PXA_EP_IN_BULK(4,  2, 1, 0, 0),
		PXA_EP_IN_ISO(5,   3, 1, 0, 0),
		PXA_EP_OUT_ISO(6,  4, 1, 0, 0),
		PXA_EP_IN_INT(7,   5, 1, 0, 0),
		/* Endpoपूर्णांकs क्रम RNDIS, serial */
		PXA_EP_OUT_BULK(8, 1, 2, 0, 0),
		PXA_EP_IN_BULK(9,  2, 2, 0, 0),
		PXA_EP_IN_INT(10,  5, 2, 0, 0),
		/*
		 * All the following endpoपूर्णांकs are only क्रम completion.  They
		 * won't never work, as multiple पूर्णांकerfaces are really broken on
		 * the pxa.
		*/
		PXA_EP_OUT_BULK(11, 1, 2, 1, 0),
		PXA_EP_IN_BULK(12,  2, 2, 1, 0),
		/* Endpoपूर्णांक क्रम CDC Ether */
		PXA_EP_OUT_BULK(13, 1, 1, 1, 1),
		PXA_EP_IN_BULK(14,  2, 1, 1, 1),
	पूर्ण
पूर्ण;

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id udc_pxa_dt_ids[] = अणु
	अणु .compatible = "marvell,pxa270-udc" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, udc_pxa_dt_ids);
#पूर्ण_अगर

/**
 * pxa_udc_probe - probes the udc device
 * @pdev: platक्रमm device
 *
 * Perक्रमm basic init : allocates udc घड़ी, creates sysfs files, requests
 * irq.
 */
अटल पूर्णांक pxa_udc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pxa_udc *udc = &memory;
	पूर्णांक retval = 0, gpio;
	काष्ठा pxa2xx_udc_mach_info *mach = dev_get_platdata(&pdev->dev);
	अचिन्हित दीर्घ gpio_flags;

	अगर (mach) अणु
		gpio_flags = mach->gpio_pullup_inverted ? GPIOF_ACTIVE_LOW : 0;
		gpio = mach->gpio_pullup;
		अगर (gpio_is_valid(gpio)) अणु
			retval = devm_gpio_request_one(&pdev->dev, gpio,
						       gpio_flags,
						       "USB D+ pullup");
			अगर (retval)
				वापस retval;
			udc->gpiod = gpio_to_desc(mach->gpio_pullup);
		पूर्ण
		udc->udc_command = mach->udc_command;
	पूर्ण अन्यथा अणु
		udc->gpiod = devm_gpiod_get(&pdev->dev, शून्य, GPIOD_ASIS);
	पूर्ण

	udc->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(udc->regs))
		वापस PTR_ERR(udc->regs);
	udc->irq = platक्रमm_get_irq(pdev, 0);
	अगर (udc->irq < 0)
		वापस udc->irq;

	udc->dev = &pdev->dev;
	अगर (of_have_populated_dt()) अणु
		udc->transceiver =
			devm_usb_get_phy_by_phandle(udc->dev, "phys", 0);
		अगर (IS_ERR(udc->transceiver))
			वापस PTR_ERR(udc->transceiver);
	पूर्ण अन्यथा अणु
		udc->transceiver = usb_get_phy(USB_PHY_TYPE_USB2);
	पूर्ण

	अगर (IS_ERR(udc->gpiod)) अणु
		dev_err(&pdev->dev, "Couldn't find or request D+ gpio : %ld\n",
			PTR_ERR(udc->gpiod));
		वापस PTR_ERR(udc->gpiod);
	पूर्ण
	अगर (udc->gpiod)
		gpiod_direction_output(udc->gpiod, 0);

	udc->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(udc->clk))
		वापस PTR_ERR(udc->clk);

	retval = clk_prepare(udc->clk);
	अगर (retval)
		वापस retval;

	udc->vbus_sensed = 0;

	the_controller = udc;
	platक्रमm_set_drvdata(pdev, udc);
	udc_init_data(udc);

	/* irq setup after old hardware state is cleaned up */
	retval = devm_request_irq(&pdev->dev, udc->irq, pxa_udc_irq,
				  IRQF_SHARED, driver_name, udc);
	अगर (retval != 0) अणु
		dev_err(udc->dev, "%s: can't get irq %i, err %d\n",
			driver_name, udc->irq, retval);
		जाओ err;
	पूर्ण

	अगर (!IS_ERR_OR_शून्य(udc->transceiver))
		usb_रेजिस्टर_notअगरier(udc->transceiver, &pxa27x_udc_phy);
	retval = usb_add_gadget_udc(&pdev->dev, &udc->gadget);
	अगर (retval)
		जाओ err_add_gadget;

	pxa_init_debugfs(udc);
	अगर (should_enable_udc(udc))
		udc_enable(udc);
	वापस 0;

err_add_gadget:
	अगर (!IS_ERR_OR_शून्य(udc->transceiver))
		usb_unरेजिस्टर_notअगरier(udc->transceiver, &pxa27x_udc_phy);
err:
	clk_unprepare(udc->clk);
	वापस retval;
पूर्ण

/**
 * pxa_udc_हटाओ - हटाओs the udc device driver
 * @_dev: platक्रमm device
 */
अटल पूर्णांक pxa_udc_हटाओ(काष्ठा platक्रमm_device *_dev)
अणु
	काष्ठा pxa_udc *udc = platक्रमm_get_drvdata(_dev);

	usb_del_gadget_udc(&udc->gadget);
	pxa_cleanup_debugfs(udc);

	अगर (!IS_ERR_OR_शून्य(udc->transceiver)) अणु
		usb_unरेजिस्टर_notअगरier(udc->transceiver, &pxa27x_udc_phy);
		usb_put_phy(udc->transceiver);
	पूर्ण

	udc->transceiver = शून्य;
	the_controller = शून्य;
	clk_unprepare(udc->clk);

	वापस 0;
पूर्ण

अटल व्योम pxa_udc_shutकरोwn(काष्ठा platक्रमm_device *_dev)
अणु
	काष्ठा pxa_udc *udc = platक्रमm_get_drvdata(_dev);

	अगर (udc_पढ़ोl(udc, UDCCR) & UDCCR_UDE)
		udc_disable(udc);
पूर्ण

#अगर_घोषित CONFIG_PXA27x
बाह्य व्योम pxa27x_clear_otgph(व्योम);
#अन्यथा
#घोषणा pxa27x_clear_otgph()   करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
/**
 * pxa_udc_suspend - Suspend udc device
 * @_dev: platक्रमm device
 * @state: suspend state
 *
 * Suspends udc : saves configuration रेजिस्टरs (UDCCR*), then disables the udc
 * device.
 */
अटल पूर्णांक pxa_udc_suspend(काष्ठा platक्रमm_device *_dev, pm_message_t state)
अणु
	काष्ठा pxa_udc *udc = platक्रमm_get_drvdata(_dev);
	काष्ठा pxa_ep *ep;

	ep = &udc->pxa_ep[0];
	udc->udccsr0 = udc_ep_पढ़ोl(ep, UDCCSR);

	udc_disable(udc);
	udc->pullup_resume = udc->pullup_on;
	dplus_pullup(udc, 0);

	अगर (udc->driver)
		udc->driver->disconnect(&udc->gadget);

	वापस 0;
पूर्ण

/**
 * pxa_udc_resume - Resume udc device
 * @_dev: platक्रमm device
 *
 * Resumes udc : restores configuration रेजिस्टरs (UDCCR*), then enables the udc
 * device.
 */
अटल पूर्णांक pxa_udc_resume(काष्ठा platक्रमm_device *_dev)
अणु
	काष्ठा pxa_udc *udc = platक्रमm_get_drvdata(_dev);
	काष्ठा pxa_ep *ep;

	ep = &udc->pxa_ep[0];
	udc_ep_ग_लिखोl(ep, UDCCSR, udc->udccsr0 & (UDCCSR0_FST | UDCCSR0_DME));

	dplus_pullup(udc, udc->pullup_resume);
	अगर (should_enable_udc(udc))
		udc_enable(udc);
	/*
	 * We करो not handle OTG yet.
	 *
	 * OTGPH bit is set when sleep mode is entered.
	 * it indicates that OTG pad is retaining its state.
	 * Upon निकास from sleep mode and beक्रमe clearing OTGPH,
	 * Software must configure the USB OTG pad, UDC, and UHC
	 * to the state they were in beक्रमe entering sleep mode.
	 */
	pxa27x_clear_otgph();

	वापस 0;
पूर्ण
#पूर्ण_अगर

/* work with hotplug and coldplug */
MODULE_ALIAS("platform:pxa27x-udc");

अटल काष्ठा platक्रमm_driver udc_driver = अणु
	.driver		= अणु
		.name	= "pxa27x-udc",
		.of_match_table = of_match_ptr(udc_pxa_dt_ids),
	पूर्ण,
	.probe		= pxa_udc_probe,
	.हटाओ		= pxa_udc_हटाओ,
	.shutकरोwn	= pxa_udc_shutकरोwn,
#अगर_घोषित CONFIG_PM
	.suspend	= pxa_udc_suspend,
	.resume		= pxa_udc_resume
#पूर्ण_अगर
पूर्ण;

module_platक्रमm_driver(udc_driver);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("Robert Jarzmik");
MODULE_LICENSE("GPL");
