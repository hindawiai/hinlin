<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the Aपंचांगel USBA high speed USB device controller
 *
 * Copyright (C) 2005-2007 Aपंचांगel Corporation
 */
#समावेश <linux/clk.h>
#समावेश <linux/clk/at91_pmc.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/list.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/usb.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/irq.h>
#समावेश <linux/gpio/consumer.h>

#समावेश "atmel_usba_udc.h"
#घोषणा USBA_VBUS_IRQFLAGS (IRQF_ONESHOT \
			   | IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING)

#अगर_घोषित CONFIG_USB_GADGET_DEBUG_FS
#समावेश <linux/debugfs.h>
#समावेश <linux/uaccess.h>

अटल पूर्णांक queue_dbg_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा usba_ep *ep = inode->i_निजी;
	काष्ठा usba_request *req, *req_copy;
	काष्ठा list_head *queue_data;

	queue_data = kदो_स्मृति(माप(*queue_data), GFP_KERNEL);
	अगर (!queue_data)
		वापस -ENOMEM;
	INIT_LIST_HEAD(queue_data);

	spin_lock_irq(&ep->udc->lock);
	list_क्रम_each_entry(req, &ep->queue, queue) अणु
		req_copy = kmemdup(req, माप(*req_copy), GFP_ATOMIC);
		अगर (!req_copy)
			जाओ fail;
		list_add_tail(&req_copy->queue, queue_data);
	पूर्ण
	spin_unlock_irq(&ep->udc->lock);

	file->निजी_data = queue_data;
	वापस 0;

fail:
	spin_unlock_irq(&ep->udc->lock);
	list_क्रम_each_entry_safe(req, req_copy, queue_data, queue) अणु
		list_del(&req->queue);
		kमुक्त(req);
	पूर्ण
	kमुक्त(queue_data);
	वापस -ENOMEM;
पूर्ण

/*
 * bbbbbbbb llllllll IZS sssss nnnn FDL\न\0
 *
 * b: buffer address
 * l: buffer length
 * I/i: पूर्णांकerrupt/no पूर्णांकerrupt
 * Z/z: zero/no zero
 * S/s: लघु ok/लघु not ok
 * s: status
 * n: nr_packets
 * F/f: submitted/not submitted to FIFO
 * D/d: using/not using DMA
 * L/l: last transaction/not last transaction
 */
अटल sमाप_प्रकार queue_dbg_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
		माप_प्रकार nbytes, loff_t *ppos)
अणु
	काष्ठा list_head *queue = file->निजी_data;
	काष्ठा usba_request *req, *पंचांगp_req;
	माप_प्रकार len, reमुख्यing, actual = 0;
	अक्षर पंचांगpbuf[38];

	अगर (!access_ok(buf, nbytes))
		वापस -EFAULT;

	inode_lock(file_inode(file));
	list_क्रम_each_entry_safe(req, पंचांगp_req, queue, queue) अणु
		len = snम_लिखो(पंचांगpbuf, माप(पंचांगpbuf),
				"%8p %08x %c%c%c %5d %c%c%c\n",
				req->req.buf, req->req.length,
				req->req.no_पूर्णांकerrupt ? 'i' : 'I',
				req->req.zero ? 'Z' : 'z',
				req->req.लघु_not_ok ? 's' : 'S',
				req->req.status,
				req->submitted ? 'F' : 'f',
				req->using_dma ? 'D' : 'd',
				req->last_transaction ? 'L' : 'l');
		len = min(len, माप(पंचांगpbuf));
		अगर (len > nbytes)
			अवरोध;

		list_del(&req->queue);
		kमुक्त(req);

		reमुख्यing = __copy_to_user(buf, पंचांगpbuf, len);
		actual += len - reमुख्यing;
		अगर (reमुख्यing)
			अवरोध;

		nbytes -= len;
		buf += len;
	पूर्ण
	inode_unlock(file_inode(file));

	वापस actual;
पूर्ण

अटल पूर्णांक queue_dbg_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा list_head *queue_data = file->निजी_data;
	काष्ठा usba_request *req, *पंचांगp_req;

	list_क्रम_each_entry_safe(req, पंचांगp_req, queue_data, queue) अणु
		list_del(&req->queue);
		kमुक्त(req);
	पूर्ण
	kमुक्त(queue_data);
	वापस 0;
पूर्ण

अटल पूर्णांक regs_dbg_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा usba_udc *udc;
	अचिन्हित पूर्णांक i;
	u32 *data;
	पूर्णांक ret = -ENOMEM;

	inode_lock(inode);
	udc = inode->i_निजी;
	data = kदो_स्मृति(inode->i_size, GFP_KERNEL);
	अगर (!data)
		जाओ out;

	spin_lock_irq(&udc->lock);
	क्रम (i = 0; i < inode->i_size / 4; i++)
		data[i] = पढ़ोl_relaxed(udc->regs + i * 4);
	spin_unlock_irq(&udc->lock);

	file->निजी_data = data;
	ret = 0;

out:
	inode_unlock(inode);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार regs_dbg_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
		माप_प्रकार nbytes, loff_t *ppos)
अणु
	काष्ठा inode *inode = file_inode(file);
	पूर्णांक ret;

	inode_lock(inode);
	ret = simple_पढ़ो_from_buffer(buf, nbytes, ppos,
			file->निजी_data,
			file_inode(file)->i_size);
	inode_unlock(inode);

	वापस ret;
पूर्ण

अटल पूर्णांक regs_dbg_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	kमुक्त(file->निजी_data);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations queue_dbg_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= queue_dbg_खोलो,
	.llseek		= no_llseek,
	.पढ़ो		= queue_dbg_पढ़ो,
	.release	= queue_dbg_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations regs_dbg_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= regs_dbg_खोलो,
	.llseek		= generic_file_llseek,
	.पढ़ो		= regs_dbg_पढ़ो,
	.release	= regs_dbg_release,
पूर्ण;

अटल व्योम usba_ep_init_debugfs(काष्ठा usba_udc *udc,
		काष्ठा usba_ep *ep)
अणु
	काष्ठा dentry *ep_root;

	ep_root = debugfs_create_dir(ep->ep.name, udc->debugfs_root);
	ep->debugfs_dir = ep_root;

	debugfs_create_file("queue", 0400, ep_root, ep, &queue_dbg_fops);
	अगर (ep->can_dma)
		debugfs_create_u32("dma_status", 0400, ep_root,
				   &ep->last_dma_status);
	अगर (ep_is_control(ep))
		debugfs_create_u32("state", 0400, ep_root, &ep->state);
पूर्ण

अटल व्योम usba_ep_cleanup_debugfs(काष्ठा usba_ep *ep)
अणु
	debugfs_हटाओ_recursive(ep->debugfs_dir);
पूर्ण

अटल व्योम usba_init_debugfs(काष्ठा usba_udc *udc)
अणु
	काष्ठा dentry *root;
	काष्ठा resource *regs_resource;

	root = debugfs_create_dir(udc->gadget.name, usb_debug_root);
	udc->debugfs_root = root;

	regs_resource = platक्रमm_get_resource(udc->pdev, IORESOURCE_MEM,
				CTRL_IOMEM_ID);

	अगर (regs_resource) अणु
		debugfs_create_file_size("regs", 0400, root, udc,
					 &regs_dbg_fops,
					 resource_size(regs_resource));
	पूर्ण

	usba_ep_init_debugfs(udc, to_usba_ep(udc->gadget.ep0));
पूर्ण

अटल व्योम usba_cleanup_debugfs(काष्ठा usba_udc *udc)
अणु
	usba_ep_cleanup_debugfs(to_usba_ep(udc->gadget.ep0));
	debugfs_हटाओ_recursive(udc->debugfs_root);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम usba_ep_init_debugfs(काष्ठा usba_udc *udc,
					 काष्ठा usba_ep *ep)
अणु

पूर्ण

अटल अंतरभूत व्योम usba_ep_cleanup_debugfs(काष्ठा usba_ep *ep)
अणु

पूर्ण

अटल अंतरभूत व्योम usba_init_debugfs(काष्ठा usba_udc *udc)
अणु

पूर्ण

अटल अंतरभूत व्योम usba_cleanup_debugfs(काष्ठा usba_udc *udc)
अणु

पूर्ण
#पूर्ण_अगर

अटल uलघु fअगरo_mode;

module_param(fअगरo_mode, uलघु, 0x0);
MODULE_PARM_DESC(fअगरo_mode, "Endpoint configuration mode");

/* mode 0 - uses स्वतःconfig */

/* mode 1 - fits in 8KB, generic max fअगरo configuration */
अटल काष्ठा usba_fअगरo_cfg mode_1_cfg[] = अणु
अणु .hw_ep_num = 0, .fअगरo_size = 64,	.nr_banks = 1, पूर्ण,
अणु .hw_ep_num = 1, .fअगरo_size = 1024,	.nr_banks = 2, पूर्ण,
अणु .hw_ep_num = 2, .fअगरo_size = 1024,	.nr_banks = 1, पूर्ण,
अणु .hw_ep_num = 3, .fअगरo_size = 1024,	.nr_banks = 1, पूर्ण,
अणु .hw_ep_num = 4, .fअगरo_size = 1024,	.nr_banks = 1, पूर्ण,
अणु .hw_ep_num = 5, .fअगरo_size = 1024,	.nr_banks = 1, पूर्ण,
अणु .hw_ep_num = 6, .fअगरo_size = 1024,	.nr_banks = 1, पूर्ण,
पूर्ण;

/* mode 2 - fits in 8KB, perक्रमmance max fअगरo configuration */
अटल काष्ठा usba_fअगरo_cfg mode_2_cfg[] = अणु
अणु .hw_ep_num = 0, .fअगरo_size = 64,	.nr_banks = 1, पूर्ण,
अणु .hw_ep_num = 1, .fअगरo_size = 1024,	.nr_banks = 3, पूर्ण,
अणु .hw_ep_num = 2, .fअगरo_size = 1024,	.nr_banks = 2, पूर्ण,
अणु .hw_ep_num = 3, .fअगरo_size = 1024,	.nr_banks = 2, पूर्ण,
पूर्ण;

/* mode 3 - fits in 8KB, mixed fअगरo configuration */
अटल काष्ठा usba_fअगरo_cfg mode_3_cfg[] = अणु
अणु .hw_ep_num = 0, .fअगरo_size = 64,	.nr_banks = 1, पूर्ण,
अणु .hw_ep_num = 1, .fअगरo_size = 1024,	.nr_banks = 2, पूर्ण,
अणु .hw_ep_num = 2, .fअगरo_size = 512,	.nr_banks = 2, पूर्ण,
अणु .hw_ep_num = 3, .fअगरo_size = 512,	.nr_banks = 2, पूर्ण,
अणु .hw_ep_num = 4, .fअगरo_size = 512,	.nr_banks = 2, पूर्ण,
अणु .hw_ep_num = 5, .fअगरo_size = 512,	.nr_banks = 2, पूर्ण,
अणु .hw_ep_num = 6, .fअगरo_size = 512,	.nr_banks = 2, पूर्ण,
पूर्ण;

/* mode 4 - fits in 8KB, custom fअगरo configuration */
अटल काष्ठा usba_fअगरo_cfg mode_4_cfg[] = अणु
अणु .hw_ep_num = 0, .fअगरo_size = 64,	.nr_banks = 1, पूर्ण,
अणु .hw_ep_num = 1, .fअगरo_size = 512,	.nr_banks = 2, पूर्ण,
अणु .hw_ep_num = 2, .fअगरo_size = 512,	.nr_banks = 2, पूर्ण,
अणु .hw_ep_num = 3, .fअगरo_size = 8,	.nr_banks = 2, पूर्ण,
अणु .hw_ep_num = 4, .fअगरo_size = 512,	.nr_banks = 2, पूर्ण,
अणु .hw_ep_num = 5, .fअगरo_size = 512,	.nr_banks = 2, पूर्ण,
अणु .hw_ep_num = 6, .fअगरo_size = 16,	.nr_banks = 2, पूर्ण,
अणु .hw_ep_num = 7, .fअगरo_size = 8,	.nr_banks = 2, पूर्ण,
अणु .hw_ep_num = 8, .fअगरo_size = 8,	.nr_banks = 2, पूर्ण,
पूर्ण;
/* Add additional configurations here */

अटल पूर्णांक usba_config_fअगरo_table(काष्ठा usba_udc *udc)
अणु
	पूर्णांक n;

	चयन (fअगरo_mode) अणु
	शेष:
		fअगरo_mode = 0;
		fallthrough;
	हाल 0:
		udc->fअगरo_cfg = शून्य;
		n = 0;
		अवरोध;
	हाल 1:
		udc->fअगरo_cfg = mode_1_cfg;
		n = ARRAY_SIZE(mode_1_cfg);
		अवरोध;
	हाल 2:
		udc->fअगरo_cfg = mode_2_cfg;
		n = ARRAY_SIZE(mode_2_cfg);
		अवरोध;
	हाल 3:
		udc->fअगरo_cfg = mode_3_cfg;
		n = ARRAY_SIZE(mode_3_cfg);
		अवरोध;
	हाल 4:
		udc->fअगरo_cfg = mode_4_cfg;
		n = ARRAY_SIZE(mode_4_cfg);
		अवरोध;
	पूर्ण
	DBG(DBG_HW, "Setup fifo_mode %d\n", fअगरo_mode);

	वापस n;
पूर्ण

अटल अंतरभूत u32 usba_पूर्णांक_enb_get(काष्ठा usba_udc *udc)
अणु
	वापस udc->पूर्णांक_enb_cache;
पूर्ण

अटल अंतरभूत व्योम usba_पूर्णांक_enb_set(काष्ठा usba_udc *udc, u32 mask)
अणु
	u32 val;

	val = udc->पूर्णांक_enb_cache | mask;
	usba_ग_लिखोl(udc, INT_ENB, val);
	udc->पूर्णांक_enb_cache = val;
पूर्ण

अटल अंतरभूत व्योम usba_पूर्णांक_enb_clear(काष्ठा usba_udc *udc, u32 mask)
अणु
	u32 val;

	val = udc->पूर्णांक_enb_cache & ~mask;
	usba_ग_लिखोl(udc, INT_ENB, val);
	udc->पूर्णांक_enb_cache = val;
पूर्ण

अटल पूर्णांक vbus_is_present(काष्ठा usba_udc *udc)
अणु
	अगर (udc->vbus_pin)
		वापस gpiod_get_value(udc->vbus_pin);

	/* No Vbus detection: Assume always present */
	वापस 1;
पूर्ण

अटल व्योम toggle_bias(काष्ठा usba_udc *udc, पूर्णांक is_on)
अणु
	अगर (udc->errata && udc->errata->toggle_bias)
		udc->errata->toggle_bias(udc, is_on);
पूर्ण

अटल व्योम generate_bias_pulse(काष्ठा usba_udc *udc)
अणु
	अगर (!udc->bias_pulse_needed)
		वापस;

	अगर (udc->errata && udc->errata->pulse_bias)
		udc->errata->pulse_bias(udc);

	udc->bias_pulse_needed = false;
पूर्ण

अटल व्योम next_fअगरo_transaction(काष्ठा usba_ep *ep, काष्ठा usba_request *req)
अणु
	अचिन्हित पूर्णांक transaction_len;

	transaction_len = req->req.length - req->req.actual;
	req->last_transaction = 1;
	अगर (transaction_len > ep->ep.maxpacket) अणु
		transaction_len = ep->ep.maxpacket;
		req->last_transaction = 0;
	पूर्ण अन्यथा अगर (transaction_len == ep->ep.maxpacket && req->req.zero)
		req->last_transaction = 0;

	DBG(DBG_QUEUE, "%s: submit_transaction, req %p (length %d)%s\n",
		ep->ep.name, req, transaction_len,
		req->last_transaction ? ", done" : "");

	स_नकल_toio(ep->fअगरo, req->req.buf + req->req.actual, transaction_len);
	usba_ep_ग_लिखोl(ep, SET_STA, USBA_TX_PK_RDY);
	req->req.actual += transaction_len;
पूर्ण

अटल व्योम submit_request(काष्ठा usba_ep *ep, काष्ठा usba_request *req)
अणु
	DBG(DBG_QUEUE, "%s: submit_request: req %p (length %d)\n",
		ep->ep.name, req, req->req.length);

	req->req.actual = 0;
	req->submitted = 1;

	अगर (req->using_dma) अणु
		अगर (req->req.length == 0) अणु
			usba_ep_ग_लिखोl(ep, CTL_ENB, USBA_TX_PK_RDY);
			वापस;
		पूर्ण

		अगर (req->req.zero)
			usba_ep_ग_लिखोl(ep, CTL_ENB, USBA_SHORT_PACKET);
		अन्यथा
			usba_ep_ग_लिखोl(ep, CTL_DIS, USBA_SHORT_PACKET);

		usba_dma_ग_लिखोl(ep, ADDRESS, req->req.dma);
		usba_dma_ग_लिखोl(ep, CONTROL, req->ctrl);
	पूर्ण अन्यथा अणु
		next_fअगरo_transaction(ep, req);
		अगर (req->last_transaction) अणु
			usba_ep_ग_लिखोl(ep, CTL_DIS, USBA_TX_PK_RDY);
			अगर (ep_is_control(ep))
				usba_ep_ग_लिखोl(ep, CTL_ENB, USBA_TX_COMPLETE);
		पूर्ण अन्यथा अणु
			अगर (ep_is_control(ep))
				usba_ep_ग_लिखोl(ep, CTL_DIS, USBA_TX_COMPLETE);
			usba_ep_ग_लिखोl(ep, CTL_ENB, USBA_TX_PK_RDY);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम submit_next_request(काष्ठा usba_ep *ep)
अणु
	काष्ठा usba_request *req;

	अगर (list_empty(&ep->queue)) अणु
		usba_ep_ग_लिखोl(ep, CTL_DIS, USBA_TX_PK_RDY | USBA_RX_BK_RDY);
		वापस;
	पूर्ण

	req = list_entry(ep->queue.next, काष्ठा usba_request, queue);
	अगर (!req->submitted)
		submit_request(ep, req);
पूर्ण

अटल व्योम send_status(काष्ठा usba_udc *udc, काष्ठा usba_ep *ep)
अणु
	ep->state = STATUS_STAGE_IN;
	usba_ep_ग_लिखोl(ep, SET_STA, USBA_TX_PK_RDY);
	usba_ep_ग_लिखोl(ep, CTL_ENB, USBA_TX_COMPLETE);
पूर्ण

अटल व्योम receive_data(काष्ठा usba_ep *ep)
अणु
	काष्ठा usba_udc *udc = ep->udc;
	काष्ठा usba_request *req;
	अचिन्हित दीर्घ status;
	अचिन्हित पूर्णांक bytecount, nr_busy;
	पूर्णांक is_complete = 0;

	status = usba_ep_पढ़ोl(ep, STA);
	nr_busy = USBA_BFEXT(BUSY_BANKS, status);

	DBG(DBG_QUEUE, "receive data: nr_busy=%u\n", nr_busy);

	जबतक (nr_busy > 0) अणु
		अगर (list_empty(&ep->queue)) अणु
			usba_ep_ग_लिखोl(ep, CTL_DIS, USBA_RX_BK_RDY);
			अवरोध;
		पूर्ण
		req = list_entry(ep->queue.next,
				 काष्ठा usba_request, queue);

		bytecount = USBA_BFEXT(BYTE_COUNT, status);

		अगर (status & (1 << 31))
			is_complete = 1;
		अगर (req->req.actual + bytecount >= req->req.length) अणु
			is_complete = 1;
			bytecount = req->req.length - req->req.actual;
		पूर्ण

		स_नकल_fromio(req->req.buf + req->req.actual,
				ep->fअगरo, bytecount);
		req->req.actual += bytecount;

		usba_ep_ग_लिखोl(ep, CLR_STA, USBA_RX_BK_RDY);

		अगर (is_complete) अणु
			DBG(DBG_QUEUE, "%s: request done\n", ep->ep.name);
			req->req.status = 0;
			list_del_init(&req->queue);
			usba_ep_ग_लिखोl(ep, CTL_DIS, USBA_RX_BK_RDY);
			spin_unlock(&udc->lock);
			usb_gadget_giveback_request(&ep->ep, &req->req);
			spin_lock(&udc->lock);
		पूर्ण

		status = usba_ep_पढ़ोl(ep, STA);
		nr_busy = USBA_BFEXT(BUSY_BANKS, status);

		अगर (is_complete && ep_is_control(ep)) अणु
			send_status(udc, ep);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
request_complete(काष्ठा usba_ep *ep, काष्ठा usba_request *req, पूर्णांक status)
अणु
	काष्ठा usba_udc *udc = ep->udc;

	WARN_ON(!list_empty(&req->queue));

	अगर (req->req.status == -EINPROGRESS)
		req->req.status = status;

	अगर (req->using_dma)
		usb_gadget_unmap_request(&udc->gadget, &req->req, ep->is_in);

	DBG(DBG_GADGET | DBG_REQ,
		"%s: req %p complete: status %d, actual %u\n",
		ep->ep.name, req, req->req.status, req->req.actual);

	spin_unlock(&udc->lock);
	usb_gadget_giveback_request(&ep->ep, &req->req);
	spin_lock(&udc->lock);
पूर्ण

अटल व्योम
request_complete_list(काष्ठा usba_ep *ep, काष्ठा list_head *list, पूर्णांक status)
अणु
	काष्ठा usba_request *req, *पंचांगp_req;

	list_क्रम_each_entry_safe(req, पंचांगp_req, list, queue) अणु
		list_del_init(&req->queue);
		request_complete(ep, req, status);
	पूर्ण
पूर्ण

अटल पूर्णांक
usba_ep_enable(काष्ठा usb_ep *_ep, स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा usba_ep *ep = to_usba_ep(_ep);
	काष्ठा usba_udc *udc = ep->udc;
	अचिन्हित दीर्घ flags, maxpacket;
	अचिन्हित पूर्णांक nr_trans;

	DBG(DBG_GADGET, "%s: ep_enable: desc=%p\n", ep->ep.name, desc);

	maxpacket = usb_endpoपूर्णांक_maxp(desc);

	अगर (((desc->bEndpoपूर्णांकAddress & USB_ENDPOINT_NUMBER_MASK) != ep->index)
			|| ep->index == 0
			|| desc->bDescriptorType != USB_DT_ENDPOINT
			|| maxpacket == 0
			|| maxpacket > ep->fअगरo_size) अणु
		DBG(DBG_ERR, "ep_enable: Invalid argument");
		वापस -EINVAL;
	पूर्ण

	ep->is_isoc = 0;
	ep->is_in = 0;

	DBG(DBG_ERR, "%s: EPT_CFG = 0x%lx (maxpacket = %lu)\n",
			ep->ep.name, ep->ept_cfg, maxpacket);

	अगर (usb_endpoपूर्णांक_dir_in(desc)) अणु
		ep->is_in = 1;
		ep->ept_cfg |= USBA_EPT_सूची_IN;
	पूर्ण

	चयन (usb_endpoपूर्णांक_type(desc)) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
		ep->ept_cfg |= USBA_BF(EPT_TYPE, USBA_EPT_TYPE_CONTROL);
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		अगर (!ep->can_isoc) अणु
			DBG(DBG_ERR, "ep_enable: %s is not isoc capable\n",
					ep->ep.name);
			वापस -EINVAL;
		पूर्ण

		/*
		 * Bits 11:12 specअगरy number of _additional_
		 * transactions per microframe.
		 */
		nr_trans = usb_endpoपूर्णांक_maxp_mult(desc);
		अगर (nr_trans > 3)
			वापस -EINVAL;

		ep->is_isoc = 1;
		ep->ept_cfg |= USBA_BF(EPT_TYPE, USBA_EPT_TYPE_ISO);
		ep->ept_cfg |= USBA_BF(NB_TRANS, nr_trans);

		अवरोध;
	हाल USB_ENDPOINT_XFER_BULK:
		ep->ept_cfg |= USBA_BF(EPT_TYPE, USBA_EPT_TYPE_BULK);
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		ep->ept_cfg |= USBA_BF(EPT_TYPE, USBA_EPT_TYPE_INT);
		अवरोध;
	पूर्ण

	spin_lock_irqsave(&ep->udc->lock, flags);

	ep->ep.desc = desc;
	ep->ep.maxpacket = maxpacket;

	usba_ep_ग_लिखोl(ep, CFG, ep->ept_cfg);
	usba_ep_ग_लिखोl(ep, CTL_ENB, USBA_EPT_ENABLE);

	अगर (ep->can_dma) अणु
		u32 ctrl;

		usba_पूर्णांक_enb_set(udc, USBA_BF(EPT_INT, 1 << ep->index) |
				      USBA_BF(DMA_INT, 1 << ep->index));
		ctrl = USBA_AUTO_VALID | USBA_INTDIS_DMA;
		usba_ep_ग_लिखोl(ep, CTL_ENB, ctrl);
	पूर्ण अन्यथा अणु
		usba_पूर्णांक_enb_set(udc, USBA_BF(EPT_INT, 1 << ep->index));
	पूर्ण

	spin_unlock_irqrestore(&udc->lock, flags);

	DBG(DBG_HW, "EPT_CFG%d after init: %#08lx\n", ep->index,
			(अचिन्हित दीर्घ)usba_ep_पढ़ोl(ep, CFG));
	DBG(DBG_HW, "INT_ENB after init: %#08lx\n",
			(अचिन्हित दीर्घ)usba_पूर्णांक_enb_get(udc));

	वापस 0;
पूर्ण

अटल पूर्णांक usba_ep_disable(काष्ठा usb_ep *_ep)
अणु
	काष्ठा usba_ep *ep = to_usba_ep(_ep);
	काष्ठा usba_udc *udc = ep->udc;
	LIST_HEAD(req_list);
	अचिन्हित दीर्घ flags;

	DBG(DBG_GADGET, "ep_disable: %s\n", ep->ep.name);

	spin_lock_irqsave(&udc->lock, flags);

	अगर (!ep->ep.desc) अणु
		spin_unlock_irqrestore(&udc->lock, flags);
		DBG(DBG_ERR, "ep_disable: %s not enabled\n", ep->ep.name);
		वापस -EINVAL;
	पूर्ण
	ep->ep.desc = शून्य;

	list_splice_init(&ep->queue, &req_list);
	अगर (ep->can_dma) अणु
		usba_dma_ग_लिखोl(ep, CONTROL, 0);
		usba_dma_ग_लिखोl(ep, ADDRESS, 0);
		usba_dma_पढ़ोl(ep, STATUS);
	पूर्ण
	usba_ep_ग_लिखोl(ep, CTL_DIS, USBA_EPT_ENABLE);
	usba_पूर्णांक_enb_clear(udc, USBA_BF(EPT_INT, 1 << ep->index));

	request_complete_list(ep, &req_list, -ESHUTDOWN);

	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा usb_request *
usba_ep_alloc_request(काष्ठा usb_ep *_ep, gfp_t gfp_flags)
अणु
	काष्ठा usba_request *req;

	DBG(DBG_GADGET, "ep_alloc_request: %p, 0x%x\n", _ep, gfp_flags);

	req = kzalloc(माप(*req), gfp_flags);
	अगर (!req)
		वापस शून्य;

	INIT_LIST_HEAD(&req->queue);

	वापस &req->req;
पूर्ण

अटल व्योम
usba_ep_मुक्त_request(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा usba_request *req = to_usba_req(_req);

	DBG(DBG_GADGET, "ep_free_request: %p, %p\n", _ep, _req);

	kमुक्त(req);
पूर्ण

अटल पूर्णांक queue_dma(काष्ठा usba_udc *udc, काष्ठा usba_ep *ep,
		काष्ठा usba_request *req, gfp_t gfp_flags)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	DBG(DBG_DMA, "%s: req l/%u d/%pad %c%c%c\n",
		ep->ep.name, req->req.length, &req->req.dma,
		req->req.zero ? 'Z' : 'z',
		req->req.लघु_not_ok ? 'S' : 's',
		req->req.no_पूर्णांकerrupt ? 'I' : 'i');

	अगर (req->req.length > 0x10000) अणु
		/* Lengths from 0 to 65536 (inclusive) are supported */
		DBG(DBG_ERR, "invalid request length %u\n", req->req.length);
		वापस -EINVAL;
	पूर्ण

	ret = usb_gadget_map_request(&udc->gadget, &req->req, ep->is_in);
	अगर (ret)
		वापस ret;

	req->using_dma = 1;
	req->ctrl = USBA_BF(DMA_BUF_LEN, req->req.length)
			| USBA_DMA_CH_EN | USBA_DMA_END_BUF_IE
			| USBA_DMA_END_BUF_EN;

	अगर (!ep->is_in)
		req->ctrl |= USBA_DMA_END_TR_EN | USBA_DMA_END_TR_IE;

	/*
	 * Add this request to the queue and submit क्रम DMA अगर
	 * possible. Check अगर we're still alive first -- we may have
	 * received a reset since last समय we checked.
	 */
	ret = -ESHUTDOWN;
	spin_lock_irqsave(&udc->lock, flags);
	अगर (ep->ep.desc) अणु
		अगर (list_empty(&ep->queue))
			submit_request(ep, req);

		list_add_tail(&req->queue, &ep->queue);
		ret = 0;
	पूर्ण
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक
usba_ep_queue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req, gfp_t gfp_flags)
अणु
	काष्ठा usba_request *req = to_usba_req(_req);
	काष्ठा usba_ep *ep = to_usba_ep(_ep);
	काष्ठा usba_udc *udc = ep->udc;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	DBG(DBG_GADGET | DBG_QUEUE | DBG_REQ, "%s: queue req %p, len %u\n",
			ep->ep.name, req, _req->length);

	अगर (!udc->driver || udc->gadget.speed == USB_SPEED_UNKNOWN ||
	    !ep->ep.desc)
		वापस -ESHUTDOWN;

	req->submitted = 0;
	req->using_dma = 0;
	req->last_transaction = 0;

	_req->status = -EINPROGRESS;
	_req->actual = 0;

	अगर (ep->can_dma)
		वापस queue_dma(udc, ep, req, gfp_flags);

	/* May have received a reset since last समय we checked */
	ret = -ESHUTDOWN;
	spin_lock_irqsave(&udc->lock, flags);
	अगर (ep->ep.desc) अणु
		list_add_tail(&req->queue, &ep->queue);

		अगर ((!ep_is_control(ep) && ep->is_in) ||
			(ep_is_control(ep)
				&& (ep->state == DATA_STAGE_IN
					|| ep->state == STATUS_STAGE_IN)))
			usba_ep_ग_लिखोl(ep, CTL_ENB, USBA_TX_PK_RDY);
		अन्यथा
			usba_ep_ग_लिखोl(ep, CTL_ENB, USBA_RX_BK_RDY);
		ret = 0;
	पूर्ण
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम
usba_update_req(काष्ठा usba_ep *ep, काष्ठा usba_request *req, u32 status)
अणु
	req->req.actual = req->req.length - USBA_BFEXT(DMA_BUF_LEN, status);
पूर्ण

अटल पूर्णांक stop_dma(काष्ठा usba_ep *ep, u32 *pstatus)
अणु
	अचिन्हित पूर्णांक समयout;
	u32 status;

	/*
	 * Stop the DMA controller. When writing both CH_EN
	 * and LINK to 0, the other bits are not affected.
	 */
	usba_dma_ग_लिखोl(ep, CONTROL, 0);

	/* Wait क्रम the FIFO to empty */
	क्रम (समयout = 40; समयout; --समयout) अणु
		status = usba_dma_पढ़ोl(ep, STATUS);
		अगर (!(status & USBA_DMA_CH_EN))
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (pstatus)
		*pstatus = status;

	अगर (समयout == 0) अणु
		dev_err(&ep->udc->pdev->dev,
			"%s: timed out waiting for DMA FIFO to empty\n",
			ep->ep.name);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक usba_ep_dequeue(काष्ठा usb_ep *_ep, काष्ठा usb_request *_req)
अणु
	काष्ठा usba_ep *ep = to_usba_ep(_ep);
	काष्ठा usba_udc *udc = ep->udc;
	काष्ठा usba_request *req;
	अचिन्हित दीर्घ flags;
	u32 status;

	DBG(DBG_GADGET | DBG_QUEUE, "ep_dequeue: %s, req %p\n",
			ep->ep.name, _req);

	spin_lock_irqsave(&udc->lock, flags);

	list_क्रम_each_entry(req, &ep->queue, queue) अणु
		अगर (&req->req == _req)
			अवरोध;
	पूर्ण

	अगर (&req->req != _req) अणु
		spin_unlock_irqrestore(&udc->lock, flags);
		वापस -EINVAL;
	पूर्ण

	अगर (req->using_dma) अणु
		/*
		 * If this request is currently being transferred,
		 * stop the DMA controller and reset the FIFO.
		 */
		अगर (ep->queue.next == &req->queue) अणु
			status = usba_dma_पढ़ोl(ep, STATUS);
			अगर (status & USBA_DMA_CH_EN)
				stop_dma(ep, &status);

#अगर_घोषित CONFIG_USB_GADGET_DEBUG_FS
			ep->last_dma_status = status;
#पूर्ण_अगर

			usba_ग_लिखोl(udc, EPT_RST, 1 << ep->index);

			usba_update_req(ep, req, status);
		पूर्ण
	पूर्ण

	/*
	 * Errors should stop the queue from advancing until the
	 * completion function वापसs.
	 */
	list_del_init(&req->queue);

	request_complete(ep, req, -ECONNRESET);

	/* Process the next request अगर any */
	submit_next_request(ep);
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक usba_ep_set_halt(काष्ठा usb_ep *_ep, पूर्णांक value)
अणु
	काष्ठा usba_ep *ep = to_usba_ep(_ep);
	काष्ठा usba_udc *udc = ep->udc;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	DBG(DBG_GADGET, "endpoint %s: %s HALT\n", ep->ep.name,
			value ? "set" : "clear");

	अगर (!ep->ep.desc) अणु
		DBG(DBG_ERR, "Attempted to halt uninitialized ep %s\n",
				ep->ep.name);
		वापस -ENODEV;
	पूर्ण
	अगर (ep->is_isoc) अणु
		DBG(DBG_ERR, "Attempted to halt isochronous ep %s\n",
				ep->ep.name);
		वापस -ENOTTY;
	पूर्ण

	spin_lock_irqsave(&udc->lock, flags);

	/*
	 * We can't halt IN endpoपूर्णांकs जबतक there are still data to be
	 * transferred
	 */
	अगर (!list_empty(&ep->queue)
			|| ((value && ep->is_in && (usba_ep_पढ़ोl(ep, STA)
					& USBA_BF(BUSY_BANKS, -1L))))) अणु
		ret = -EAGAIN;
	पूर्ण अन्यथा अणु
		अगर (value)
			usba_ep_ग_लिखोl(ep, SET_STA, USBA_FORCE_STALL);
		अन्यथा
			usba_ep_ग_लिखोl(ep, CLR_STA,
					USBA_FORCE_STALL | USBA_TOGGLE_CLR);
		usba_ep_पढ़ोl(ep, STA);
	पूर्ण

	spin_unlock_irqrestore(&udc->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक usba_ep_fअगरo_status(काष्ठा usb_ep *_ep)
अणु
	काष्ठा usba_ep *ep = to_usba_ep(_ep);

	वापस USBA_BFEXT(BYTE_COUNT, usba_ep_पढ़ोl(ep, STA));
पूर्ण

अटल व्योम usba_ep_fअगरo_flush(काष्ठा usb_ep *_ep)
अणु
	काष्ठा usba_ep *ep = to_usba_ep(_ep);
	काष्ठा usba_udc *udc = ep->udc;

	usba_ग_लिखोl(udc, EPT_RST, 1 << ep->index);
पूर्ण

अटल स्थिर काष्ठा usb_ep_ops usba_ep_ops = अणु
	.enable		= usba_ep_enable,
	.disable	= usba_ep_disable,
	.alloc_request	= usba_ep_alloc_request,
	.मुक्त_request	= usba_ep_मुक्त_request,
	.queue		= usba_ep_queue,
	.dequeue	= usba_ep_dequeue,
	.set_halt	= usba_ep_set_halt,
	.fअगरo_status	= usba_ep_fअगरo_status,
	.fअगरo_flush	= usba_ep_fअगरo_flush,
पूर्ण;

अटल पूर्णांक usba_udc_get_frame(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा usba_udc *udc = to_usba_udc(gadget);

	वापस USBA_BFEXT(FRAME_NUMBER, usba_पढ़ोl(udc, FNUM));
पूर्ण

अटल पूर्णांक usba_udc_wakeup(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा usba_udc *udc = to_usba_udc(gadget);
	अचिन्हित दीर्घ flags;
	u32 ctrl;
	पूर्णांक ret = -EINVAL;

	spin_lock_irqsave(&udc->lock, flags);
	अगर (udc->devstatus & (1 << USB_DEVICE_REMOTE_WAKEUP)) अणु
		ctrl = usba_पढ़ोl(udc, CTRL);
		usba_ग_लिखोl(udc, CTRL, ctrl | USBA_REMOTE_WAKE_UP);
		ret = 0;
	पूर्ण
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक
usba_udc_set_selfघातered(काष्ठा usb_gadget *gadget, पूर्णांक is_selfघातered)
अणु
	काष्ठा usba_udc *udc = to_usba_udc(gadget);
	अचिन्हित दीर्घ flags;

	gadget->is_selfघातered = (is_selfघातered != 0);
	spin_lock_irqsave(&udc->lock, flags);
	अगर (is_selfघातered)
		udc->devstatus |= 1 << USB_DEVICE_SELF_POWERED;
	अन्यथा
		udc->devstatus &= ~(1 << USB_DEVICE_SELF_POWERED);
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_usba_pullup(काष्ठा usb_gadget *gadget, पूर्णांक is_on);
अटल पूर्णांक aपंचांगel_usba_start(काष्ठा usb_gadget *gadget,
		काष्ठा usb_gadget_driver *driver);
अटल पूर्णांक aपंचांगel_usba_stop(काष्ठा usb_gadget *gadget);

अटल काष्ठा usb_ep *aपंचांगel_usba_match_ep(काष्ठा usb_gadget *gadget,
				काष्ठा usb_endpoपूर्णांक_descriptor	*desc,
				काष्ठा usb_ss_ep_comp_descriptor *ep_comp)
अणु
	काष्ठा usb_ep	*_ep;
	काष्ठा usba_ep *ep;

	/* Look at endpoपूर्णांकs until an unclaimed one looks usable */
	list_क्रम_each_entry(_ep, &gadget->ep_list, ep_list) अणु
		अगर (usb_gadget_ep_match_desc(gadget, _ep, desc, ep_comp))
			जाओ found_ep;
	पूर्ण
	/* Fail */
	वापस शून्य;

found_ep:

	अगर (fअगरo_mode == 0) अणु
		/* Optimize hw fअगरo size based on ep type and other info */
		ep = to_usba_ep(_ep);

		चयन (usb_endpoपूर्णांक_type(desc)) अणु
		हाल USB_ENDPOINT_XFER_CONTROL:
			ep->nr_banks = 1;
			अवरोध;

		हाल USB_ENDPOINT_XFER_ISOC:
			ep->fअगरo_size = 1024;
			अगर (ep->udc->ep_pपुनः_स्मृति)
				ep->nr_banks = 2;
			अवरोध;

		हाल USB_ENDPOINT_XFER_BULK:
			ep->fअगरo_size = 512;
			अगर (ep->udc->ep_pपुनः_स्मृति)
				ep->nr_banks = 1;
			अवरोध;

		हाल USB_ENDPOINT_XFER_INT:
			अगर (desc->wMaxPacketSize == 0)
				ep->fअगरo_size =
				    roundup_घात_of_two(_ep->maxpacket_limit);
			अन्यथा
				ep->fअगरo_size =
				    roundup_घात_of_two(le16_to_cpu(desc->wMaxPacketSize));
			अगर (ep->udc->ep_pपुनः_स्मृति)
				ep->nr_banks = 1;
			अवरोध;
		पूर्ण

		/* It might be a little bit late to set this */
		usb_ep_set_maxpacket_limit(&ep->ep, ep->fअगरo_size);

		/* Generate ept_cfg basd on FIFO size and number of banks */
		अगर (ep->fअगरo_size  <= 8)
			ep->ept_cfg = USBA_BF(EPT_SIZE, USBA_EPT_SIZE_8);
		अन्यथा
			/* LSB is bit 1, not 0 */
			ep->ept_cfg =
				USBA_BF(EPT_SIZE, fls(ep->fअगरo_size - 1) - 3);

		ep->ept_cfg |= USBA_BF(BK_NUMBER, ep->nr_banks);
	पूर्ण

	वापस _ep;
पूर्ण

अटल स्थिर काष्ठा usb_gadget_ops usba_udc_ops = अणु
	.get_frame		= usba_udc_get_frame,
	.wakeup			= usba_udc_wakeup,
	.set_selfघातered	= usba_udc_set_selfघातered,
	.pullup			= aपंचांगel_usba_pullup,
	.udc_start		= aपंचांगel_usba_start,
	.udc_stop		= aपंचांगel_usba_stop,
	.match_ep		= aपंचांगel_usba_match_ep,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor usba_ep0_desc = अणु
	.bLength = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress = 0,
	.bmAttributes = USB_ENDPOINT_XFER_CONTROL,
	.wMaxPacketSize = cpu_to_le16(64),
	/* FIXME: I have no idea what to put here */
	.bInterval = 1,
पूर्ण;

अटल स्थिर काष्ठा usb_gadget usba_gadget_ढाँचा = अणु
	.ops		= &usba_udc_ops,
	.max_speed	= USB_SPEED_HIGH,
	.name		= "atmel_usba_udc",
पूर्ण;

/*
 * Called with पूर्णांकerrupts disabled and udc->lock held.
 */
अटल व्योम reset_all_endpoपूर्णांकs(काष्ठा usba_udc *udc)
अणु
	काष्ठा usba_ep *ep;
	काष्ठा usba_request *req, *पंचांगp_req;

	usba_ग_लिखोl(udc, EPT_RST, ~0UL);

	ep = to_usba_ep(udc->gadget.ep0);
	list_क्रम_each_entry_safe(req, पंचांगp_req, &ep->queue, queue) अणु
		list_del_init(&req->queue);
		request_complete(ep, req, -ECONNRESET);
	पूर्ण
पूर्ण

अटल काष्ठा usba_ep *get_ep_by_addr(काष्ठा usba_udc *udc, u16 wIndex)
अणु
	काष्ठा usba_ep *ep;

	अगर ((wIndex & USB_ENDPOINT_NUMBER_MASK) == 0)
		वापस to_usba_ep(udc->gadget.ep0);

	list_क्रम_each_entry (ep, &udc->gadget.ep_list, ep.ep_list) अणु
		u8 bEndpoपूर्णांकAddress;

		अगर (!ep->ep.desc)
			जारी;
		bEndpoपूर्णांकAddress = ep->ep.desc->bEndpoपूर्णांकAddress;
		अगर ((wIndex ^ bEndpoपूर्णांकAddress) & USB_सूची_IN)
			जारी;
		अगर ((bEndpoपूर्णांकAddress & USB_ENDPOINT_NUMBER_MASK)
				== (wIndex & USB_ENDPOINT_NUMBER_MASK))
			वापस ep;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Called with पूर्णांकerrupts disabled and udc->lock held */
अटल अंतरभूत व्योम set_protocol_stall(काष्ठा usba_udc *udc, काष्ठा usba_ep *ep)
अणु
	usba_ep_ग_लिखोl(ep, SET_STA, USBA_FORCE_STALL);
	ep->state = WAIT_FOR_SETUP;
पूर्ण

अटल अंतरभूत पूर्णांक is_stalled(काष्ठा usba_udc *udc, काष्ठा usba_ep *ep)
अणु
	अगर (usba_ep_पढ़ोl(ep, STA) & USBA_FORCE_STALL)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम set_address(काष्ठा usba_udc *udc, अचिन्हित पूर्णांक addr)
अणु
	u32 regval;

	DBG(DBG_BUS, "setting address %u...\n", addr);
	regval = usba_पढ़ोl(udc, CTRL);
	regval = USBA_BFINS(DEV_ADDR, addr, regval);
	usba_ग_लिखोl(udc, CTRL, regval);
पूर्ण

अटल पूर्णांक करो_test_mode(काष्ठा usba_udc *udc)
अणु
	अटल स्थिर अक्षर test_packet_buffer[] = अणु
		/* JKJKJKJK * 9 */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		/* JJKKJJKK * 8 */
		0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
		/* JJKKJJKK * 8 */
		0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE,
		/* JJJJJJJKKKKKKK * 8 */
		0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		/* JJJJJJJK * 8 */
		0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD,
		/* अणुJKKKKKKK * 10पूर्ण, JK */
		0xFC, 0x7E, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD, 0x7E
	पूर्ण;
	काष्ठा usba_ep *ep;
	काष्ठा device *dev = &udc->pdev->dev;
	पूर्णांक test_mode;

	test_mode = udc->test_mode;

	/* Start from a clean slate */
	reset_all_endpoपूर्णांकs(udc);

	चयन (test_mode) अणु
	हाल 0x0100:
		/* Test_J */
		usba_ग_लिखोl(udc, TST, USBA_TST_J_MODE);
		dev_info(dev, "Entering Test_J mode...\n");
		अवरोध;
	हाल 0x0200:
		/* Test_K */
		usba_ग_लिखोl(udc, TST, USBA_TST_K_MODE);
		dev_info(dev, "Entering Test_K mode...\n");
		अवरोध;
	हाल 0x0300:
		/*
		 * Test_SE0_NAK: Force high-speed mode and set up ep0
		 * क्रम Bulk IN transfers
		 */
		ep = &udc->usba_ep[0];
		usba_ग_लिखोl(udc, TST,
				USBA_BF(SPEED_CFG, USBA_SPEED_CFG_FORCE_HIGH));
		usba_ep_ग_लिखोl(ep, CFG,
				USBA_BF(EPT_SIZE, USBA_EPT_SIZE_64)
				| USBA_EPT_सूची_IN
				| USBA_BF(EPT_TYPE, USBA_EPT_TYPE_BULK)
				| USBA_BF(BK_NUMBER, 1));
		अगर (!(usba_ep_पढ़ोl(ep, CFG) & USBA_EPT_MAPPED)) अणु
			set_protocol_stall(udc, ep);
			dev_err(dev, "Test_SE0_NAK: ep0 not mapped\n");
		पूर्ण अन्यथा अणु
			usba_ep_ग_लिखोl(ep, CTL_ENB, USBA_EPT_ENABLE);
			dev_info(dev, "Entering Test_SE0_NAK mode...\n");
		पूर्ण
		अवरोध;
	हाल 0x0400:
		/* Test_Packet */
		ep = &udc->usba_ep[0];
		usba_ep_ग_लिखोl(ep, CFG,
				USBA_BF(EPT_SIZE, USBA_EPT_SIZE_64)
				| USBA_EPT_सूची_IN
				| USBA_BF(EPT_TYPE, USBA_EPT_TYPE_BULK)
				| USBA_BF(BK_NUMBER, 1));
		अगर (!(usba_ep_पढ़ोl(ep, CFG) & USBA_EPT_MAPPED)) अणु
			set_protocol_stall(udc, ep);
			dev_err(dev, "Test_Packet: ep0 not mapped\n");
		पूर्ण अन्यथा अणु
			usba_ep_ग_लिखोl(ep, CTL_ENB, USBA_EPT_ENABLE);
			usba_ग_लिखोl(udc, TST, USBA_TST_PKT_MODE);
			स_नकल_toio(ep->fअगरo, test_packet_buffer,
					माप(test_packet_buffer));
			usba_ep_ग_लिखोl(ep, SET_STA, USBA_TX_PK_RDY);
			dev_info(dev, "Entering Test_Packet mode...\n");
		पूर्ण
		अवरोध;
	शेष:
		dev_err(dev, "Invalid test mode: 0x%04x\n", test_mode);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Aव्योम overly दीर्घ expressions */
अटल अंतरभूत bool feature_is_dev_remote_wakeup(काष्ठा usb_ctrlrequest *crq)
अणु
	अगर (crq->wValue == cpu_to_le16(USB_DEVICE_REMOTE_WAKEUP))
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool feature_is_dev_test_mode(काष्ठा usb_ctrlrequest *crq)
अणु
	अगर (crq->wValue == cpu_to_le16(USB_DEVICE_TEST_MODE))
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool feature_is_ep_halt(काष्ठा usb_ctrlrequest *crq)
अणु
	अगर (crq->wValue == cpu_to_le16(USB_ENDPOINT_HALT))
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक handle_ep0_setup(काष्ठा usba_udc *udc, काष्ठा usba_ep *ep,
		काष्ठा usb_ctrlrequest *crq)
अणु
	पूर्णांक retval = 0;

	चयन (crq->bRequest) अणु
	हाल USB_REQ_GET_STATUS: अणु
		u16 status;

		अगर (crq->bRequestType == (USB_सूची_IN | USB_RECIP_DEVICE)) अणु
			status = cpu_to_le16(udc->devstatus);
		पूर्ण अन्यथा अगर (crq->bRequestType
				== (USB_सूची_IN | USB_RECIP_INTERFACE)) अणु
			status = cpu_to_le16(0);
		पूर्ण अन्यथा अगर (crq->bRequestType
				== (USB_सूची_IN | USB_RECIP_ENDPOINT)) अणु
			काष्ठा usba_ep *target;

			target = get_ep_by_addr(udc, le16_to_cpu(crq->wIndex));
			अगर (!target)
				जाओ stall;

			status = 0;
			अगर (is_stalled(udc, target))
				status |= cpu_to_le16(1);
		पूर्ण अन्यथा
			जाओ delegate;

		/* Write directly to the FIFO. No queueing is करोne. */
		अगर (crq->wLength != cpu_to_le16(माप(status)))
			जाओ stall;
		ep->state = DATA_STAGE_IN;
		ग_लिखोw_relaxed(status, ep->fअगरo);
		usba_ep_ग_लिखोl(ep, SET_STA, USBA_TX_PK_RDY);
		अवरोध;
	पूर्ण

	हाल USB_REQ_CLEAR_FEATURE: अणु
		अगर (crq->bRequestType == USB_RECIP_DEVICE) अणु
			अगर (feature_is_dev_remote_wakeup(crq))
				udc->devstatus
					&= ~(1 << USB_DEVICE_REMOTE_WAKEUP);
			अन्यथा
				/* Can't CLEAR_FEATURE TEST_MODE */
				जाओ stall;
		पूर्ण अन्यथा अगर (crq->bRequestType == USB_RECIP_ENDPOINT) अणु
			काष्ठा usba_ep *target;

			अगर (crq->wLength != cpu_to_le16(0)
					|| !feature_is_ep_halt(crq))
				जाओ stall;
			target = get_ep_by_addr(udc, le16_to_cpu(crq->wIndex));
			अगर (!target)
				जाओ stall;

			usba_ep_ग_लिखोl(target, CLR_STA, USBA_FORCE_STALL);
			अगर (target->index != 0)
				usba_ep_ग_लिखोl(target, CLR_STA,
						USBA_TOGGLE_CLR);
		पूर्ण अन्यथा अणु
			जाओ delegate;
		पूर्ण

		send_status(udc, ep);
		अवरोध;
	पूर्ण

	हाल USB_REQ_SET_FEATURE: अणु
		अगर (crq->bRequestType == USB_RECIP_DEVICE) अणु
			अगर (feature_is_dev_test_mode(crq)) अणु
				send_status(udc, ep);
				ep->state = STATUS_STAGE_TEST;
				udc->test_mode = le16_to_cpu(crq->wIndex);
				वापस 0;
			पूर्ण अन्यथा अगर (feature_is_dev_remote_wakeup(crq)) अणु
				udc->devstatus |= 1 << USB_DEVICE_REMOTE_WAKEUP;
			पूर्ण अन्यथा अणु
				जाओ stall;
			पूर्ण
		पूर्ण अन्यथा अगर (crq->bRequestType == USB_RECIP_ENDPOINT) अणु
			काष्ठा usba_ep *target;

			अगर (crq->wLength != cpu_to_le16(0)
					|| !feature_is_ep_halt(crq))
				जाओ stall;

			target = get_ep_by_addr(udc, le16_to_cpu(crq->wIndex));
			अगर (!target)
				जाओ stall;

			usba_ep_ग_लिखोl(target, SET_STA, USBA_FORCE_STALL);
		पूर्ण अन्यथा
			जाओ delegate;

		send_status(udc, ep);
		अवरोध;
	पूर्ण

	हाल USB_REQ_SET_ADDRESS:
		अगर (crq->bRequestType != (USB_सूची_OUT | USB_RECIP_DEVICE))
			जाओ delegate;

		set_address(udc, le16_to_cpu(crq->wValue));
		send_status(udc, ep);
		ep->state = STATUS_STAGE_ADDR;
		अवरोध;

	शेष:
delegate:
		spin_unlock(&udc->lock);
		retval = udc->driver->setup(&udc->gadget, crq);
		spin_lock(&udc->lock);
	पूर्ण

	वापस retval;

stall:
	pr_err("udc: %s: Invalid setup request: %02x.%02x v%04x i%04x l%d, "
		"halting endpoint...\n",
		ep->ep.name, crq->bRequestType, crq->bRequest,
		le16_to_cpu(crq->wValue), le16_to_cpu(crq->wIndex),
		le16_to_cpu(crq->wLength));
	set_protocol_stall(udc, ep);
	वापस -1;
पूर्ण

अटल व्योम usba_control_irq(काष्ठा usba_udc *udc, काष्ठा usba_ep *ep)
अणु
	काष्ठा usba_request *req;
	u32 epstatus;
	u32 epctrl;

restart:
	epstatus = usba_ep_पढ़ोl(ep, STA);
	epctrl = usba_ep_पढ़ोl(ep, CTL);

	DBG(DBG_INT, "%s [%d]: s/%08x c/%08x\n",
			ep->ep.name, ep->state, epstatus, epctrl);

	req = शून्य;
	अगर (!list_empty(&ep->queue))
		req = list_entry(ep->queue.next,
				 काष्ठा usba_request, queue);

	अगर ((epctrl & USBA_TX_PK_RDY) && !(epstatus & USBA_TX_PK_RDY)) अणु
		अगर (req->submitted)
			next_fअगरo_transaction(ep, req);
		अन्यथा
			submit_request(ep, req);

		अगर (req->last_transaction) अणु
			usba_ep_ग_लिखोl(ep, CTL_DIS, USBA_TX_PK_RDY);
			usba_ep_ग_लिखोl(ep, CTL_ENB, USBA_TX_COMPLETE);
		पूर्ण
		जाओ restart;
	पूर्ण
	अगर ((epstatus & epctrl) & USBA_TX_COMPLETE) अणु
		usba_ep_ग_लिखोl(ep, CLR_STA, USBA_TX_COMPLETE);

		चयन (ep->state) अणु
		हाल DATA_STAGE_IN:
			usba_ep_ग_लिखोl(ep, CTL_ENB, USBA_RX_BK_RDY);
			usba_ep_ग_लिखोl(ep, CTL_DIS, USBA_TX_COMPLETE);
			ep->state = STATUS_STAGE_OUT;
			अवरोध;
		हाल STATUS_STAGE_ADDR:
			/* Activate our new address */
			usba_ग_लिखोl(udc, CTRL, (usba_पढ़ोl(udc, CTRL)
						| USBA_FADDR_EN));
			usba_ep_ग_लिखोl(ep, CTL_DIS, USBA_TX_COMPLETE);
			ep->state = WAIT_FOR_SETUP;
			अवरोध;
		हाल STATUS_STAGE_IN:
			अगर (req) अणु
				list_del_init(&req->queue);
				request_complete(ep, req, 0);
				submit_next_request(ep);
			पूर्ण
			usba_ep_ग_लिखोl(ep, CTL_DIS, USBA_TX_COMPLETE);
			ep->state = WAIT_FOR_SETUP;
			अवरोध;
		हाल STATUS_STAGE_TEST:
			usba_ep_ग_लिखोl(ep, CTL_DIS, USBA_TX_COMPLETE);
			ep->state = WAIT_FOR_SETUP;
			अगर (करो_test_mode(udc))
				set_protocol_stall(udc, ep);
			अवरोध;
		शेष:
			pr_err("udc: %s: TXCOMP: Invalid endpoint state %d, "
				"halting endpoint...\n",
				ep->ep.name, ep->state);
			set_protocol_stall(udc, ep);
			अवरोध;
		पूर्ण

		जाओ restart;
	पूर्ण
	अगर ((epstatus & epctrl) & USBA_RX_BK_RDY) अणु
		चयन (ep->state) अणु
		हाल STATUS_STAGE_OUT:
			usba_ep_ग_लिखोl(ep, CLR_STA, USBA_RX_BK_RDY);
			usba_ep_ग_लिखोl(ep, CTL_DIS, USBA_RX_BK_RDY);

			अगर (req) अणु
				list_del_init(&req->queue);
				request_complete(ep, req, 0);
			पूर्ण
			ep->state = WAIT_FOR_SETUP;
			अवरोध;

		हाल DATA_STAGE_OUT:
			receive_data(ep);
			अवरोध;

		शेष:
			usba_ep_ग_लिखोl(ep, CLR_STA, USBA_RX_BK_RDY);
			usba_ep_ग_लिखोl(ep, CTL_DIS, USBA_RX_BK_RDY);
			pr_err("udc: %s: RXRDY: Invalid endpoint state %d, "
				"halting endpoint...\n",
				ep->ep.name, ep->state);
			set_protocol_stall(udc, ep);
			अवरोध;
		पूर्ण

		जाओ restart;
	पूर्ण
	अगर (epstatus & USBA_RX_SETUP) अणु
		जोड़ अणु
			काष्ठा usb_ctrlrequest crq;
			अचिन्हित दीर्घ data[2];
		पूर्ण crq;
		अचिन्हित पूर्णांक pkt_len;
		पूर्णांक ret;

		अगर (ep->state != WAIT_FOR_SETUP) अणु
			/*
			 * Didn't expect a SETUP packet at this
			 * poपूर्णांक. Clean up any pending requests (which
			 * may be successful).
			 */
			पूर्णांक status = -EPROTO;

			/*
			 * RXRDY and TXCOMP are dropped when SETUP
			 * packets arrive.  Just pretend we received
			 * the status packet.
			 */
			अगर (ep->state == STATUS_STAGE_OUT
					|| ep->state == STATUS_STAGE_IN) अणु
				usba_ep_ग_लिखोl(ep, CTL_DIS, USBA_RX_BK_RDY);
				status = 0;
			पूर्ण

			अगर (req) अणु
				list_del_init(&req->queue);
				request_complete(ep, req, status);
			पूर्ण
		पूर्ण

		pkt_len = USBA_BFEXT(BYTE_COUNT, usba_ep_पढ़ोl(ep, STA));
		DBG(DBG_HW, "Packet length: %u\n", pkt_len);
		अगर (pkt_len != माप(crq)) अणु
			pr_warn("udc: Invalid packet length %u (expected %zu)\n",
				pkt_len, माप(crq));
			set_protocol_stall(udc, ep);
			वापस;
		पूर्ण

		DBG(DBG_FIFO, "Copying ctrl request from 0x%p:\n", ep->fअगरo);
		स_नकल_fromio(crq.data, ep->fअगरo, माप(crq));

		/* Free up one bank in the FIFO so that we can
		 * generate or receive a reply right away. */
		usba_ep_ग_लिखोl(ep, CLR_STA, USBA_RX_SETUP);

		/* prपूर्णांकk(KERN_DEBUG "setup: %d: %02x.%02x\n",
			ep->state, crq.crq.bRequestType,
			crq.crq.bRequest); */

		अगर (crq.crq.bRequestType & USB_सूची_IN) अणु
			/*
			 * The USB 2.0 spec states that "अगर wLength is
			 * zero, there is no data transfer phase."
			 * However, testusb #14 seems to actually
			 * expect a data phase even अगर wLength = 0...
			 */
			ep->state = DATA_STAGE_IN;
		पूर्ण अन्यथा अणु
			अगर (crq.crq.wLength != cpu_to_le16(0))
				ep->state = DATA_STAGE_OUT;
			अन्यथा
				ep->state = STATUS_STAGE_IN;
		पूर्ण

		ret = -1;
		अगर (ep->index == 0)
			ret = handle_ep0_setup(udc, ep, &crq.crq);
		अन्यथा अणु
			spin_unlock(&udc->lock);
			ret = udc->driver->setup(&udc->gadget, &crq.crq);
			spin_lock(&udc->lock);
		पूर्ण

		DBG(DBG_BUS, "req %02x.%02x, length %d, state %d, ret %d\n",
			crq.crq.bRequestType, crq.crq.bRequest,
			le16_to_cpu(crq.crq.wLength), ep->state, ret);

		अगर (ret < 0) अणु
			/* Let the host know that we failed */
			set_protocol_stall(udc, ep);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम usba_ep_irq(काष्ठा usba_udc *udc, काष्ठा usba_ep *ep)
अणु
	काष्ठा usba_request *req;
	u32 epstatus;
	u32 epctrl;

	epstatus = usba_ep_पढ़ोl(ep, STA);
	epctrl = usba_ep_पढ़ोl(ep, CTL);

	DBG(DBG_INT, "%s: interrupt, status: 0x%08x\n", ep->ep.name, epstatus);

	जबतक ((epctrl & USBA_TX_PK_RDY) && !(epstatus & USBA_TX_PK_RDY)) अणु
		DBG(DBG_BUS, "%s: TX PK ready\n", ep->ep.name);

		अगर (list_empty(&ep->queue)) अणु
			dev_warn(&udc->pdev->dev, "ep_irq: queue empty\n");
			usba_ep_ग_लिखोl(ep, CTL_DIS, USBA_TX_PK_RDY);
			वापस;
		पूर्ण

		req = list_entry(ep->queue.next, काष्ठा usba_request, queue);

		अगर (req->using_dma) अणु
			/* Send a zero-length packet */
			usba_ep_ग_लिखोl(ep, SET_STA,
					USBA_TX_PK_RDY);
			usba_ep_ग_लिखोl(ep, CTL_DIS,
					USBA_TX_PK_RDY);
			list_del_init(&req->queue);
			submit_next_request(ep);
			request_complete(ep, req, 0);
		पूर्ण अन्यथा अणु
			अगर (req->submitted)
				next_fअगरo_transaction(ep, req);
			अन्यथा
				submit_request(ep, req);

			अगर (req->last_transaction) अणु
				list_del_init(&req->queue);
				submit_next_request(ep);
				request_complete(ep, req, 0);
			पूर्ण
		पूर्ण

		epstatus = usba_ep_पढ़ोl(ep, STA);
		epctrl = usba_ep_पढ़ोl(ep, CTL);
	पूर्ण
	अगर ((epstatus & epctrl) & USBA_RX_BK_RDY) अणु
		DBG(DBG_BUS, "%s: RX data ready\n", ep->ep.name);
		receive_data(ep);
	पूर्ण
पूर्ण

अटल व्योम usba_dma_irq(काष्ठा usba_udc *udc, काष्ठा usba_ep *ep)
अणु
	काष्ठा usba_request *req;
	u32 status, control, pending;

	status = usba_dma_पढ़ोl(ep, STATUS);
	control = usba_dma_पढ़ोl(ep, CONTROL);
#अगर_घोषित CONFIG_USB_GADGET_DEBUG_FS
	ep->last_dma_status = status;
#पूर्ण_अगर
	pending = status & control;
	DBG(DBG_INT | DBG_DMA, "dma irq, s/%#08x, c/%#08x\n", status, control);

	अगर (status & USBA_DMA_CH_EN) अणु
		dev_err(&udc->pdev->dev,
			"DMA_CH_EN is set after transfer is finished!\n");
		dev_err(&udc->pdev->dev,
			"status=%#08x, pending=%#08x, control=%#08x\n",
			status, pending, control);

		/*
		 * try to pretend nothing happened. We might have to
		 * करो something here...
		 */
	पूर्ण

	अगर (list_empty(&ep->queue))
		/* Might happen अगर a reset comes aदीर्घ at the right moment */
		वापस;

	अगर (pending & (USBA_DMA_END_TR_ST | USBA_DMA_END_BUF_ST)) अणु
		req = list_entry(ep->queue.next, काष्ठा usba_request, queue);
		usba_update_req(ep, req, status);

		list_del_init(&req->queue);
		submit_next_request(ep);
		request_complete(ep, req, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक start_घड़ी(काष्ठा usba_udc *udc);
अटल व्योम stop_घड़ी(काष्ठा usba_udc *udc);

अटल irqवापस_t usba_udc_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा usba_udc *udc = devid;
	u32 status, पूर्णांक_enb;
	u32 dma_status;
	u32 ep_status;

	spin_lock(&udc->lock);

	पूर्णांक_enb = usba_पूर्णांक_enb_get(udc);
	status = usba_पढ़ोl(udc, INT_STA) & (पूर्णांक_enb | USBA_HIGH_SPEED);
	DBG(DBG_INT, "irq, status=%#08x\n", status);

	अगर (status & USBA_DET_SUSPEND) अणु
		usba_ग_लिखोl(udc, INT_CLR, USBA_DET_SUSPEND|USBA_WAKE_UP);
		usba_पूर्णांक_enb_set(udc, USBA_WAKE_UP);
		usba_पूर्णांक_enb_clear(udc, USBA_DET_SUSPEND);
		udc->suspended = true;
		toggle_bias(udc, 0);
		udc->bias_pulse_needed = true;
		stop_घड़ी(udc);
		DBG(DBG_BUS, "Suspend detected\n");
		अगर (udc->gadget.speed != USB_SPEED_UNKNOWN
				&& udc->driver && udc->driver->suspend) अणु
			spin_unlock(&udc->lock);
			udc->driver->suspend(&udc->gadget);
			spin_lock(&udc->lock);
		पूर्ण
	पूर्ण

	अगर (status & USBA_WAKE_UP) अणु
		start_घड़ी(udc);
		toggle_bias(udc, 1);
		usba_ग_लिखोl(udc, INT_CLR, USBA_WAKE_UP);
		DBG(DBG_BUS, "Wake Up CPU detected\n");
	पूर्ण

	अगर (status & USBA_END_OF_RESUME) अणु
		udc->suspended = false;
		usba_ग_लिखोl(udc, INT_CLR, USBA_END_OF_RESUME);
		usba_पूर्णांक_enb_clear(udc, USBA_WAKE_UP);
		usba_पूर्णांक_enb_set(udc, USBA_DET_SUSPEND);
		generate_bias_pulse(udc);
		DBG(DBG_BUS, "Resume detected\n");
		अगर (udc->gadget.speed != USB_SPEED_UNKNOWN
				&& udc->driver && udc->driver->resume) अणु
			spin_unlock(&udc->lock);
			udc->driver->resume(&udc->gadget);
			spin_lock(&udc->lock);
		पूर्ण
	पूर्ण

	dma_status = USBA_BFEXT(DMA_INT, status);
	अगर (dma_status) अणु
		पूर्णांक i;

		usba_पूर्णांक_enb_set(udc, USBA_DET_SUSPEND);

		क्रम (i = 1; i <= USBA_NR_DMAS; i++)
			अगर (dma_status & (1 << i))
				usba_dma_irq(udc, &udc->usba_ep[i]);
	पूर्ण

	ep_status = USBA_BFEXT(EPT_INT, status);
	अगर (ep_status) अणु
		पूर्णांक i;

		usba_पूर्णांक_enb_set(udc, USBA_DET_SUSPEND);

		क्रम (i = 0; i < udc->num_ep; i++)
			अगर (ep_status & (1 << i)) अणु
				अगर (ep_is_control(&udc->usba_ep[i]))
					usba_control_irq(udc, &udc->usba_ep[i]);
				अन्यथा
					usba_ep_irq(udc, &udc->usba_ep[i]);
			पूर्ण
	पूर्ण

	अगर (status & USBA_END_OF_RESET) अणु
		काष्ठा usba_ep *ep0, *ep;
		पूर्णांक i;

		usba_ग_लिखोl(udc, INT_CLR,
			USBA_END_OF_RESET|USBA_END_OF_RESUME
			|USBA_DET_SUSPEND|USBA_WAKE_UP);
		generate_bias_pulse(udc);
		reset_all_endpoपूर्णांकs(udc);

		अगर (udc->gadget.speed != USB_SPEED_UNKNOWN && udc->driver) अणु
			udc->gadget.speed = USB_SPEED_UNKNOWN;
			spin_unlock(&udc->lock);
			usb_gadget_udc_reset(&udc->gadget, udc->driver);
			spin_lock(&udc->lock);
		पूर्ण

		अगर (status & USBA_HIGH_SPEED)
			udc->gadget.speed = USB_SPEED_HIGH;
		अन्यथा
			udc->gadget.speed = USB_SPEED_FULL;
		DBG(DBG_BUS, "%s bus reset detected\n",
		    usb_speed_string(udc->gadget.speed));

		ep0 = &udc->usba_ep[0];
		ep0->ep.desc = &usba_ep0_desc;
		ep0->state = WAIT_FOR_SETUP;
		usba_ep_ग_लिखोl(ep0, CFG,
				(USBA_BF(EPT_SIZE, EP0_EPT_SIZE)
				| USBA_BF(EPT_TYPE, USBA_EPT_TYPE_CONTROL)
				| USBA_BF(BK_NUMBER, USBA_BK_NUMBER_ONE)));
		usba_ep_ग_लिखोl(ep0, CTL_ENB,
				USBA_EPT_ENABLE | USBA_RX_SETUP);

		/* If we get reset जबतक suspended... */
		udc->suspended = false;
		usba_पूर्णांक_enb_clear(udc, USBA_WAKE_UP);

		usba_पूर्णांक_enb_set(udc, USBA_BF(EPT_INT, 1) |
				      USBA_DET_SUSPEND | USBA_END_OF_RESUME);

		/*
		 * Unclear why we hit this irregularly, e.g. in usbtest,
		 * but it's clearly harmless...
		 */
		अगर (!(usba_ep_पढ़ोl(ep0, CFG) & USBA_EPT_MAPPED))
			dev_err(&udc->pdev->dev,
				"ODD: EP0 configuration is invalid!\n");

		/* Pपुनः_स्मृतिate other endpoपूर्णांकs */
		क्रम (i = 1; i < udc->num_ep; i++) अणु
			ep = &udc->usba_ep[i];
			अगर (ep->ep.claimed) अणु
				usba_ep_ग_लिखोl(ep, CFG, ep->ept_cfg);
				अगर (!(usba_ep_पढ़ोl(ep, CFG) & USBA_EPT_MAPPED))
					dev_err(&udc->pdev->dev,
						"ODD: EP%d configuration is invalid!\n", i);
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock(&udc->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक start_घड़ी(काष्ठा usba_udc *udc)
अणु
	पूर्णांक ret;

	अगर (udc->घड़ीed)
		वापस 0;

	pm_stay_awake(&udc->pdev->dev);

	ret = clk_prepare_enable(udc->pclk);
	अगर (ret)
		वापस ret;
	ret = clk_prepare_enable(udc->hclk);
	अगर (ret) अणु
		clk_disable_unprepare(udc->pclk);
		वापस ret;
	पूर्ण

	udc->घड़ीed = true;
	वापस 0;
पूर्ण

अटल व्योम stop_घड़ी(काष्ठा usba_udc *udc)
अणु
	अगर (!udc->घड़ीed)
		वापस;

	clk_disable_unprepare(udc->hclk);
	clk_disable_unprepare(udc->pclk);

	udc->घड़ीed = false;

	pm_relax(&udc->pdev->dev);
पूर्ण

अटल पूर्णांक usba_start(काष्ठा usba_udc *udc)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = start_घड़ी(udc);
	अगर (ret)
		वापस ret;

	अगर (udc->suspended)
		वापस 0;

	spin_lock_irqsave(&udc->lock, flags);
	toggle_bias(udc, 1);
	usba_ग_लिखोl(udc, CTRL, USBA_ENABLE_MASK);
	/* Clear all requested and pending पूर्णांकerrupts... */
	usba_ग_लिखोl(udc, INT_ENB, 0);
	udc->पूर्णांक_enb_cache = 0;
	usba_ग_लिखोl(udc, INT_CLR,
		USBA_END_OF_RESET|USBA_END_OF_RESUME
		|USBA_DET_SUSPEND|USBA_WAKE_UP);
	/* ...and enable just 'reset' IRQ to get us started */
	usba_पूर्णांक_enb_set(udc, USBA_END_OF_RESET);
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम usba_stop(काष्ठा usba_udc *udc)
अणु
	अचिन्हित दीर्घ flags;

	अगर (udc->suspended)
		वापस;

	spin_lock_irqsave(&udc->lock, flags);
	udc->gadget.speed = USB_SPEED_UNKNOWN;
	reset_all_endpoपूर्णांकs(udc);

	/* This will also disable the DP pullup */
	toggle_bias(udc, 0);
	usba_ग_लिखोl(udc, CTRL, USBA_DISABLE_MASK);
	spin_unlock_irqrestore(&udc->lock, flags);

	stop_घड़ी(udc);
पूर्ण

अटल irqवापस_t usba_vbus_irq_thपढ़ो(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा usba_udc *udc = devid;
	पूर्णांक vbus;

	/* debounce */
	udelay(10);

	mutex_lock(&udc->vbus_mutex);

	vbus = vbus_is_present(udc);
	अगर (vbus != udc->vbus_prev) अणु
		अगर (vbus) अणु
			usba_start(udc);
		पूर्ण अन्यथा अणु
			udc->suspended = false;
			अगर (udc->driver->disconnect)
				udc->driver->disconnect(&udc->gadget);

			usba_stop(udc);
		पूर्ण
		udc->vbus_prev = vbus;
	पूर्ण

	mutex_unlock(&udc->vbus_mutex);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक aपंचांगel_usba_pullup(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	काष्ठा usba_udc *udc = container_of(gadget, काष्ठा usba_udc, gadget);
	अचिन्हित दीर्घ flags;
	u32 ctrl;

	spin_lock_irqsave(&udc->lock, flags);
	ctrl = usba_पढ़ोl(udc, CTRL);
	अगर (is_on)
		ctrl &= ~USBA_DETACH;
	अन्यथा
		ctrl |= USBA_DETACH;
	usba_ग_लिखोl(udc, CTRL, ctrl);
	spin_unlock_irqrestore(&udc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_usba_start(काष्ठा usb_gadget *gadget,
		काष्ठा usb_gadget_driver *driver)
अणु
	पूर्णांक ret;
	काष्ठा usba_udc *udc = container_of(gadget, काष्ठा usba_udc, gadget);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&udc->lock, flags);
	udc->devstatus = 1 << USB_DEVICE_SELF_POWERED;
	udc->driver = driver;
	spin_unlock_irqrestore(&udc->lock, flags);

	mutex_lock(&udc->vbus_mutex);

	अगर (udc->vbus_pin)
		enable_irq(gpiod_to_irq(udc->vbus_pin));

	/* If Vbus is present, enable the controller and रुको क्रम reset */
	udc->vbus_prev = vbus_is_present(udc);
	अगर (udc->vbus_prev) अणु
		ret = usba_start(udc);
		अगर (ret)
			जाओ err;
	पूर्ण

	mutex_unlock(&udc->vbus_mutex);
	वापस 0;

err:
	अगर (udc->vbus_pin)
		disable_irq(gpiod_to_irq(udc->vbus_pin));

	mutex_unlock(&udc->vbus_mutex);

	spin_lock_irqsave(&udc->lock, flags);
	udc->devstatus &= ~(1 << USB_DEVICE_SELF_POWERED);
	udc->driver = शून्य;
	spin_unlock_irqrestore(&udc->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_usba_stop(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा usba_udc *udc = container_of(gadget, काष्ठा usba_udc, gadget);

	अगर (udc->vbus_pin)
		disable_irq(gpiod_to_irq(udc->vbus_pin));

	udc->suspended = false;
	usba_stop(udc);

	udc->driver = शून्य;

	वापस 0;
पूर्ण

अटल व्योम at91sam9rl_toggle_bias(काष्ठा usba_udc *udc, पूर्णांक is_on)
अणु
	regmap_update_bits(udc->pmc, AT91_CKGR_UCKR, AT91_PMC_BIASEN,
			   is_on ? AT91_PMC_BIASEN : 0);
पूर्ण

अटल व्योम at91sam9g45_pulse_bias(काष्ठा usba_udc *udc)
अणु
	regmap_update_bits(udc->pmc, AT91_CKGR_UCKR, AT91_PMC_BIASEN, 0);
	regmap_update_bits(udc->pmc, AT91_CKGR_UCKR, AT91_PMC_BIASEN,
			   AT91_PMC_BIASEN);
पूर्ण

अटल स्थिर काष्ठा usba_udc_errata at91sam9rl_errata = अणु
	.toggle_bias = at91sam9rl_toggle_bias,
पूर्ण;

अटल स्थिर काष्ठा usba_udc_errata at91sam9g45_errata = अणु
	.pulse_bias = at91sam9g45_pulse_bias,
पूर्ण;

अटल स्थिर काष्ठा usba_ep_config ep_config_sam9[] __initस्थिर = अणु
	अणु .nr_banks = 1 पूर्ण,				/* ep 0 */
	अणु .nr_banks = 2, .can_dma = 1, .can_isoc = 1 पूर्ण,	/* ep 1 */
	अणु .nr_banks = 2, .can_dma = 1, .can_isoc = 1 पूर्ण,	/* ep 2 */
	अणु .nr_banks = 3, .can_dma = 1 पूर्ण,		/* ep 3 */
	अणु .nr_banks = 3, .can_dma = 1 पूर्ण,		/* ep 4 */
	अणु .nr_banks = 3, .can_dma = 1, .can_isoc = 1 पूर्ण,	/* ep 5 */
	अणु .nr_banks = 3, .can_dma = 1, .can_isoc = 1 पूर्ण,	/* ep 6 */
पूर्ण;

अटल स्थिर काष्ठा usba_ep_config ep_config_sama5[] __initस्थिर = अणु
	अणु .nr_banks = 1 पूर्ण,				/* ep 0 */
	अणु .nr_banks = 3, .can_dma = 1, .can_isoc = 1 पूर्ण,	/* ep 1 */
	अणु .nr_banks = 3, .can_dma = 1, .can_isoc = 1 पूर्ण,	/* ep 2 */
	अणु .nr_banks = 2, .can_dma = 1, .can_isoc = 1 पूर्ण,	/* ep 3 */
	अणु .nr_banks = 2, .can_dma = 1, .can_isoc = 1 पूर्ण,	/* ep 4 */
	अणु .nr_banks = 2, .can_dma = 1, .can_isoc = 1 पूर्ण,	/* ep 5 */
	अणु .nr_banks = 2, .can_dma = 1, .can_isoc = 1 पूर्ण,	/* ep 6 */
	अणु .nr_banks = 2, .can_dma = 1, .can_isoc = 1 पूर्ण,	/* ep 7 */
	अणु .nr_banks = 2, .can_isoc = 1 पूर्ण,		/* ep 8 */
	अणु .nr_banks = 2, .can_isoc = 1 पूर्ण,		/* ep 9 */
	अणु .nr_banks = 2, .can_isoc = 1 पूर्ण,		/* ep 10 */
	अणु .nr_banks = 2, .can_isoc = 1 पूर्ण,		/* ep 11 */
	अणु .nr_banks = 2, .can_isoc = 1 पूर्ण,		/* ep 12 */
	अणु .nr_banks = 2, .can_isoc = 1 पूर्ण,		/* ep 13 */
	अणु .nr_banks = 2, .can_isoc = 1 पूर्ण,		/* ep 14 */
	अणु .nr_banks = 2, .can_isoc = 1 पूर्ण,		/* ep 15 */
पूर्ण;

अटल स्थिर काष्ठा usba_udc_config udc_at91sam9rl_cfg = अणु
	.errata = &at91sam9rl_errata,
	.config = ep_config_sam9,
	.num_ep = ARRAY_SIZE(ep_config_sam9),
	.ep_pपुनः_स्मृति = true,
पूर्ण;

अटल स्थिर काष्ठा usba_udc_config udc_at91sam9g45_cfg = अणु
	.errata = &at91sam9g45_errata,
	.config = ep_config_sam9,
	.num_ep = ARRAY_SIZE(ep_config_sam9),
	.ep_pपुनः_स्मृति = true,
पूर्ण;

अटल स्थिर काष्ठा usba_udc_config udc_sama5d3_cfg = अणु
	.config = ep_config_sama5,
	.num_ep = ARRAY_SIZE(ep_config_sama5),
	.ep_pपुनः_स्मृति = true,
पूर्ण;

अटल स्थिर काष्ठा usba_udc_config udc_sam9x60_cfg = अणु
	.num_ep = ARRAY_SIZE(ep_config_sam9),
	.config = ep_config_sam9,
	.ep_pपुनः_स्मृति = false,
पूर्ण;

अटल स्थिर काष्ठा of_device_id aपंचांगel_udc_dt_ids[] = अणु
	अणु .compatible = "atmel,at91sam9rl-udc", .data = &udc_at91sam9rl_cfg पूर्ण,
	अणु .compatible = "atmel,at91sam9g45-udc", .data = &udc_at91sam9g45_cfg पूर्ण,
	अणु .compatible = "atmel,sama5d3-udc", .data = &udc_sama5d3_cfg पूर्ण,
	अणु .compatible = "microchip,sam9x60-udc", .data = &udc_sam9x60_cfg पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, aपंचांगel_udc_dt_ids);

अटल स्थिर काष्ठा of_device_id aपंचांगel_pmc_dt_ids[] = अणु
	अणु .compatible = "atmel,at91sam9g45-pmc" पूर्ण,
	अणु .compatible = "atmel,at91sam9rl-pmc" पूर्ण,
	अणु .compatible = "atmel,at91sam9x5-pmc" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा usba_ep * aपंचांगel_udc_of_init(काष्ठा platक्रमm_device *pdev,
						    काष्ठा usba_udc *udc)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *pp;
	पूर्णांक i, ret;
	काष्ठा usba_ep *eps, *ep;
	स्थिर काष्ठा usba_udc_config *udc_config;

	match = of_match_node(aपंचांगel_udc_dt_ids, np);
	अगर (!match)
		वापस ERR_PTR(-EINVAL);

	udc_config = match->data;
	udc->ep_pपुनः_स्मृति = udc_config->ep_pपुनः_स्मृति;
	udc->errata = udc_config->errata;
	अगर (udc->errata) अणु
		pp = of_find_matching_node_and_match(शून्य, aपंचांगel_pmc_dt_ids,
						     शून्य);
		अगर (!pp)
			वापस ERR_PTR(-ENODEV);

		udc->pmc = syscon_node_to_regmap(pp);
		of_node_put(pp);
		अगर (IS_ERR(udc->pmc))
			वापस ERR_CAST(udc->pmc);
	पूर्ण

	udc->num_ep = 0;

	udc->vbus_pin = devm_gpiod_get_optional(&pdev->dev, "atmel,vbus",
						GPIOD_IN);

	अगर (fअगरo_mode == 0) अणु
		udc->num_ep = udc_config->num_ep;
	पूर्ण अन्यथा अणु
		udc->num_ep = usba_config_fअगरo_table(udc);
	पूर्ण

	eps = devm_kसुस्मृति(&pdev->dev, udc->num_ep, माप(काष्ठा usba_ep),
			   GFP_KERNEL);
	अगर (!eps)
		वापस ERR_PTR(-ENOMEM);

	udc->gadget.ep0 = &eps[0].ep;

	INIT_LIST_HEAD(&eps[0].ep.ep_list);

	i = 0;
	जबतक (i < udc->num_ep) अणु
		स्थिर काष्ठा usba_ep_config *ep_cfg = &udc_config->config[i];

		ep = &eps[i];

		ep->index = fअगरo_mode ? udc->fअगरo_cfg[i].hw_ep_num : i;

		/* Only the first EP is 64 bytes */
		अगर (ep->index == 0)
			ep->fअगरo_size = 64;
		अन्यथा
			ep->fअगरo_size = 1024;

		अगर (fअगरo_mode) अणु
			अगर (ep->fअगरo_size < udc->fअगरo_cfg[i].fअगरo_size)
				dev_warn(&pdev->dev,
					 "Using default max fifo-size value\n");
			अन्यथा
				ep->fअगरo_size = udc->fअगरo_cfg[i].fअगरo_size;
		पूर्ण

		ep->nr_banks = ep_cfg->nr_banks;
		अगर (fअगरo_mode) अणु
			अगर (ep->nr_banks < udc->fअगरo_cfg[i].nr_banks)
				dev_warn(&pdev->dev,
					 "Using default max nb-banks value\n");
			अन्यथा
				ep->nr_banks = udc->fअगरo_cfg[i].nr_banks;
		पूर्ण

		ep->can_dma = ep_cfg->can_dma;
		ep->can_isoc = ep_cfg->can_isoc;

		प्र_लिखो(ep->name, "ep%d", ep->index);
		ep->ep.name = ep->name;

		ep->ep_regs = udc->regs + USBA_EPT_BASE(i);
		ep->dma_regs = udc->regs + USBA_DMA_BASE(i);
		ep->fअगरo = udc->fअगरo + USBA_FIFO_BASE(i);
		ep->ep.ops = &usba_ep_ops;
		usb_ep_set_maxpacket_limit(&ep->ep, ep->fअगरo_size);
		ep->udc = udc;
		INIT_LIST_HEAD(&ep->queue);

		अगर (ep->index == 0) अणु
			ep->ep.caps.type_control = true;
		पूर्ण अन्यथा अणु
			ep->ep.caps.type_iso = ep->can_isoc;
			ep->ep.caps.type_bulk = true;
			ep->ep.caps.type_पूर्णांक = true;
		पूर्ण

		ep->ep.caps.dir_in = true;
		ep->ep.caps.dir_out = true;

		अगर (fअगरo_mode != 0) अणु
			/*
			 * Generate ept_cfg based on FIFO size and
			 * banks number
			 */
			अगर (ep->fअगरo_size  <= 8)
				ep->ept_cfg = USBA_BF(EPT_SIZE, USBA_EPT_SIZE_8);
			अन्यथा
				/* LSB is bit 1, not 0 */
				ep->ept_cfg =
				  USBA_BF(EPT_SIZE, fls(ep->fअगरo_size - 1) - 3);

			ep->ept_cfg |= USBA_BF(BK_NUMBER, ep->nr_banks);
		पूर्ण

		अगर (i)
			list_add_tail(&ep->ep.ep_list, &udc->gadget.ep_list);

		i++;
	पूर्ण

	अगर (i == 0) अणु
		dev_err(&pdev->dev, "of_probe: no endpoint specified\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	वापस eps;
err:
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक usba_udc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा clk *pclk, *hclk;
	काष्ठा usba_udc *udc;
	पूर्णांक irq, ret, i;

	udc = devm_kzalloc(&pdev->dev, माप(*udc), GFP_KERNEL);
	अगर (!udc)
		वापस -ENOMEM;

	udc->gadget = usba_gadget_ढाँचा;
	INIT_LIST_HEAD(&udc->gadget.ep_list);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, CTRL_IOMEM_ID);
	udc->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(udc->regs))
		वापस PTR_ERR(udc->regs);
	dev_info(&pdev->dev, "MMIO registers at %pR mapped at %p\n",
		 res, udc->regs);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, FIFO_IOMEM_ID);
	udc->fअगरo = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(udc->fअगरo))
		वापस PTR_ERR(udc->fअगरo);
	dev_info(&pdev->dev, "FIFO at %pR mapped at %p\n", res, udc->fअगरo);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	pclk = devm_clk_get(&pdev->dev, "pclk");
	अगर (IS_ERR(pclk))
		वापस PTR_ERR(pclk);
	hclk = devm_clk_get(&pdev->dev, "hclk");
	अगर (IS_ERR(hclk))
		वापस PTR_ERR(hclk);

	spin_lock_init(&udc->lock);
	mutex_init(&udc->vbus_mutex);
	udc->pdev = pdev;
	udc->pclk = pclk;
	udc->hclk = hclk;

	platक्रमm_set_drvdata(pdev, udc);

	/* Make sure we start from a clean slate */
	ret = clk_prepare_enable(pclk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to enable pclk, aborting.\n");
		वापस ret;
	पूर्ण

	usba_ग_लिखोl(udc, CTRL, USBA_DISABLE_MASK);
	clk_disable_unprepare(pclk);

	udc->usba_ep = aपंचांगel_udc_of_init(pdev, udc);

	toggle_bias(udc, 0);

	अगर (IS_ERR(udc->usba_ep))
		वापस PTR_ERR(udc->usba_ep);

	ret = devm_request_irq(&pdev->dev, irq, usba_udc_irq, 0,
				"atmel_usba_udc", udc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot request irq %d (error %d)\n",
			irq, ret);
		वापस ret;
	पूर्ण
	udc->irq = irq;

	अगर (udc->vbus_pin) अणु
		irq_set_status_flags(gpiod_to_irq(udc->vbus_pin), IRQ_NOAUTOEN);
		ret = devm_request_thपढ़ोed_irq(&pdev->dev,
				gpiod_to_irq(udc->vbus_pin), शून्य,
				usba_vbus_irq_thपढ़ो, USBA_VBUS_IRQFLAGS,
				"atmel_usba_udc", udc);
		अगर (ret) अणु
			udc->vbus_pin = शून्य;
			dev_warn(&udc->pdev->dev,
				 "failed to request vbus irq; "
				 "assuming always on\n");
		पूर्ण
	पूर्ण

	ret = usb_add_gadget_udc(&pdev->dev, &udc->gadget);
	अगर (ret)
		वापस ret;
	device_init_wakeup(&pdev->dev, 1);

	usba_init_debugfs(udc);
	क्रम (i = 1; i < udc->num_ep; i++)
		usba_ep_init_debugfs(udc, &udc->usba_ep[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक usba_udc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usba_udc *udc;
	पूर्णांक i;

	udc = platक्रमm_get_drvdata(pdev);

	device_init_wakeup(&pdev->dev, 0);
	usb_del_gadget_udc(&udc->gadget);

	क्रम (i = 1; i < udc->num_ep; i++)
		usba_ep_cleanup_debugfs(&udc->usba_ep[i]);
	usba_cleanup_debugfs(udc);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक usba_udc_suspend(काष्ठा device *dev)
अणु
	काष्ठा usba_udc *udc = dev_get_drvdata(dev);

	/* Not started */
	अगर (!udc->driver)
		वापस 0;

	mutex_lock(&udc->vbus_mutex);

	अगर (!device_may_wakeup(dev)) अणु
		udc->suspended = false;
		usba_stop(udc);
		जाओ out;
	पूर्ण

	/*
	 * Device may wake up. We stay घड़ीed अगर we failed
	 * to request vbus irq, assuming always on.
	 */
	अगर (udc->vbus_pin) अणु
		/* FIXME: right to stop here...??? */
		usba_stop(udc);
		enable_irq_wake(gpiod_to_irq(udc->vbus_pin));
	पूर्ण

	enable_irq_wake(udc->irq);

out:
	mutex_unlock(&udc->vbus_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक usba_udc_resume(काष्ठा device *dev)
अणु
	काष्ठा usba_udc *udc = dev_get_drvdata(dev);

	/* Not started */
	अगर (!udc->driver)
		वापस 0;

	अगर (device_may_wakeup(dev)) अणु
		अगर (udc->vbus_pin)
			disable_irq_wake(gpiod_to_irq(udc->vbus_pin));

		disable_irq_wake(udc->irq);
	पूर्ण

	/* If Vbus is present, enable the controller and रुको क्रम reset */
	mutex_lock(&udc->vbus_mutex);
	udc->vbus_prev = vbus_is_present(udc);
	अगर (udc->vbus_prev)
		usba_start(udc);
	mutex_unlock(&udc->vbus_mutex);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(usba_udc_pm_ops, usba_udc_suspend, usba_udc_resume);

अटल काष्ठा platक्रमm_driver udc_driver = अणु
	.हटाओ		= usba_udc_हटाओ,
	.driver		= अणु
		.name		= "atmel_usba_udc",
		.pm		= &usba_udc_pm_ops,
		.of_match_table	= aपंचांगel_udc_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(udc_driver, usba_udc_probe);

MODULE_DESCRIPTION("Atmel USBA UDC driver");
MODULE_AUTHOR("Haavard Skinnemoen (Atmel)");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:atmel_usba_udc");
