<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * IPWireless 3G PCMCIA Network Driver
 *
 * Original code
 *   by Stephen Blackheath <stephen@blacksapphire.com>,
 *      Ben Martel <benm@symmetric.co.nz>
 *
 * Copyrighted as follows:
 *   Copyright (C) 2004 by Symmetric Systems Ltd (NZ)
 *
 * Various driver changes and reग_लिखोs, port to new kernels
 *   Copyright (C) 2006-2007 Jiri Kosina
 *
 * Misc code cleanups and updates
 *   Copyright (C) 2007 David Sterba
 */

#समावेश "hardware.h"
#समावेश "network.h"
#समावेश "main.h"
#समावेश "tty.h"

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#समावेश <pcmcia/cisreg.h>
#समावेश <pcmcia/device_id.h>
#समावेश <pcmcia/ss.h>
#समावेश <pcmcia/ds.h>

अटल स्थिर काष्ठा pcmcia_device_id ipw_ids[] = अणु
	PCMCIA_DEVICE_MANF_CARD(0x02f2, 0x0100),
	PCMCIA_DEVICE_MANF_CARD(0x02f2, 0x0200),
	PCMCIA_DEVICE_शून्य
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, ipw_ids);

अटल व्योम ipwireless_detach(काष्ठा pcmcia_device *link);

/*
 * Module params
 */
/* Debug mode: more verbose, prपूर्णांक sent/recv bytes */
पूर्णांक ipwireless_debug;
पूर्णांक ipwireless_loopback;
पूर्णांक ipwireless_out_queue = 10;

module_param_named(debug, ipwireless_debug, पूर्णांक, 0);
module_param_named(loopback, ipwireless_loopback, पूर्णांक, 0);
module_param_named(out_queue, ipwireless_out_queue, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "switch on debug messages [0]");
MODULE_PARM_DESC(loopback,
		"debug: enable ras_raw channel [0]");
MODULE_PARM_DESC(out_queue, "debug: set size of outgoing PPP queue [10]");

/* Executes in process context. */
अटल व्योम संकेतled_reboot_work(काष्ठा work_काष्ठा *work_reboot)
अणु
	काष्ठा ipw_dev *ipw = container_of(work_reboot, काष्ठा ipw_dev,
			work_reboot);
	काष्ठा pcmcia_device *link = ipw->link;
	pcmcia_reset_card(link->socket);
पूर्ण

अटल व्योम संकेतled_reboot_callback(व्योम *callback_data)
अणु
	काष्ठा ipw_dev *ipw = (काष्ठा ipw_dev *) callback_data;

	/* Delegate to process context. */
	schedule_work(&ipw->work_reboot);
पूर्ण

अटल पूर्णांक ipwireless_probe(काष्ठा pcmcia_device *p_dev, व्योम *priv_data)
अणु
	काष्ठा ipw_dev *ipw = priv_data;
	पूर्णांक ret;

	p_dev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_AUTO;

	/* 0x40 causes it to generate level mode पूर्णांकerrupts. */
	/* 0x04 enables IREQ pin. */
	p_dev->config_index |= 0x44;
	p_dev->io_lines = 16;
	ret = pcmcia_request_io(p_dev);
	अगर (ret)
		वापस ret;

	अगर (!request_region(p_dev->resource[0]->start,
			    resource_size(p_dev->resource[0]),
			    IPWIRELESS_PCCARD_NAME)) अणु
		ret = -EBUSY;
		जाओ निकास;
	पूर्ण

	p_dev->resource[2]->flags |=
		WIN_DATA_WIDTH_16 | WIN_MEMORY_TYPE_CM | WIN_ENABLE;

	ret = pcmcia_request_winकरोw(p_dev, p_dev->resource[2], 0);
	अगर (ret != 0)
		जाओ निकास1;

	ret = pcmcia_map_mem_page(p_dev, p_dev->resource[2], p_dev->card_addr);
	अगर (ret != 0)
		जाओ निकास1;

	ipw->is_v2_card = resource_size(p_dev->resource[2]) == 0x100;

	ipw->common_memory = ioremap(p_dev->resource[2]->start,
				resource_size(p_dev->resource[2]));
	अगर (!ipw->common_memory) अणु
		ret = -ENOMEM;
		जाओ निकास1;
	पूर्ण
	अगर (!request_mem_region(p_dev->resource[2]->start,
				resource_size(p_dev->resource[2]),
				IPWIRELESS_PCCARD_NAME)) अणु
		ret = -EBUSY;
		जाओ निकास2;
	पूर्ण

	p_dev->resource[3]->flags |= WIN_DATA_WIDTH_16 | WIN_MEMORY_TYPE_AM |
					WIN_ENABLE;
	p_dev->resource[3]->end = 0; /* this used to be 0x1000 */
	ret = pcmcia_request_winकरोw(p_dev, p_dev->resource[3], 0);
	अगर (ret != 0)
		जाओ निकास3;

	ret = pcmcia_map_mem_page(p_dev, p_dev->resource[3], 0);
	अगर (ret != 0)
		जाओ निकास3;

	ipw->attr_memory = ioremap(p_dev->resource[3]->start,
				resource_size(p_dev->resource[3]));
	अगर (!ipw->attr_memory) अणु
		ret = -ENOMEM;
		जाओ निकास3;
	पूर्ण
	अगर (!request_mem_region(p_dev->resource[3]->start,
				resource_size(p_dev->resource[3]),
				IPWIRELESS_PCCARD_NAME)) अणु
		ret = -EBUSY;
		जाओ निकास4;
	पूर्ण

	वापस 0;

निकास4:
	iounmap(ipw->attr_memory);
निकास3:
	release_mem_region(p_dev->resource[2]->start,
			resource_size(p_dev->resource[2]));
निकास2:
	iounmap(ipw->common_memory);
निकास1:
	release_region(p_dev->resource[0]->start,
		       resource_size(p_dev->resource[0]));
निकास:
	pcmcia_disable_device(p_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक config_ipwireless(काष्ठा ipw_dev *ipw)
अणु
	काष्ठा pcmcia_device *link = ipw->link;
	पूर्णांक ret = 0;

	ipw->is_v2_card = 0;
	link->config_flags |= CONF_AUTO_SET_IO | CONF_AUTO_SET_IOMEM |
		CONF_ENABLE_IRQ;

	ret = pcmcia_loop_config(link, ipwireless_probe, ipw);
	अगर (ret != 0)
		वापस ret;

	INIT_WORK(&ipw->work_reboot, संकेतled_reboot_work);

	ipwireless_init_hardware_v1(ipw->hardware, link->resource[0]->start,
				    ipw->attr_memory, ipw->common_memory,
				    ipw->is_v2_card, संकेतled_reboot_callback,
				    ipw);

	ret = pcmcia_request_irq(link, ipwireless_पूर्णांकerrupt);
	अगर (ret != 0)
		जाओ निकास;

	prपूर्णांकk(KERN_INFO IPWIRELESS_PCCARD_NAME ": Card type %s\n",
			ipw->is_v2_card ? "V2/V3" : "V1");
	prपूर्णांकk(KERN_INFO IPWIRELESS_PCCARD_NAME
		": I/O ports %pR, irq %d\n", link->resource[0],
			(अचिन्हित पूर्णांक) link->irq);
	अगर (ipw->attr_memory && ipw->common_memory)
		prपूर्णांकk(KERN_INFO IPWIRELESS_PCCARD_NAME
			": attr memory %pR, common memory %pR\n",
			link->resource[3],
			link->resource[2]);

	ipw->network = ipwireless_network_create(ipw->hardware);
	अगर (!ipw->network)
		जाओ निकास;

	ipw->tty = ipwireless_tty_create(ipw->hardware, ipw->network);
	अगर (!ipw->tty)
		जाओ निकास;

	ipwireless_init_hardware_v2_v3(ipw->hardware);

	/*
	 * Do the RequestConfiguration last, because it enables पूर्णांकerrupts.
	 * Then we करोn't get any interrupts before we're पढ़ोy क्रम them.
	 */
	ret = pcmcia_enable_device(link);
	अगर (ret != 0)
		जाओ निकास;

	वापस 0;

निकास:
	अगर (ipw->common_memory) अणु
		release_mem_region(link->resource[2]->start,
				resource_size(link->resource[2]));
		iounmap(ipw->common_memory);
	पूर्ण
	अगर (ipw->attr_memory) अणु
		release_mem_region(link->resource[3]->start,
				resource_size(link->resource[3]));
		iounmap(ipw->attr_memory);
	पूर्ण
	pcmcia_disable_device(link);
	वापस -1;
पूर्ण

अटल व्योम release_ipwireless(काष्ठा ipw_dev *ipw)
अणु
	release_region(ipw->link->resource[0]->start,
		       resource_size(ipw->link->resource[0]));
	अगर (ipw->common_memory) अणु
		release_mem_region(ipw->link->resource[2]->start,
				resource_size(ipw->link->resource[2]));
		iounmap(ipw->common_memory);
	पूर्ण
	अगर (ipw->attr_memory) अणु
		release_mem_region(ipw->link->resource[3]->start,
				resource_size(ipw->link->resource[3]));
		iounmap(ipw->attr_memory);
	पूर्ण
	pcmcia_disable_device(ipw->link);
पूर्ण

/*
 * ipwireless_attach() creates an "instance" of the driver, allocating
 * local data काष्ठाures क्रम one device (one पूर्णांकerface).  The device
 * is रेजिस्टरed with Card Services.
 *
 * The pcmcia_device काष्ठाure is initialized, but we करोn't actually
 * configure the card at this poपूर्णांक -- we रुको until we receive a
 * card insertion event.
 */
अटल पूर्णांक ipwireless_attach(काष्ठा pcmcia_device *link)
अणु
	काष्ठा ipw_dev *ipw;
	पूर्णांक ret;

	ipw = kzalloc(माप(काष्ठा ipw_dev), GFP_KERNEL);
	अगर (!ipw)
		वापस -ENOMEM;

	ipw->link = link;
	link->priv = ipw;

	ipw->hardware = ipwireless_hardware_create();
	अगर (!ipw->hardware) अणु
		kमुक्त(ipw);
		वापस -ENOMEM;
	पूर्ण
	/* RegisterClient will call config_ipwireless */

	ret = config_ipwireless(ipw);

	अगर (ret != 0) अणु
		ipwireless_detach(link);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This deletes a driver "instance".  The device is de-रेजिस्टरed with
 * Card Services.  If it has been released, all local data काष्ठाures
 * are मुक्तd.  Otherwise, the काष्ठाures will be मुक्तd when the device
 * is released.
 */
अटल व्योम ipwireless_detach(काष्ठा pcmcia_device *link)
अणु
	काष्ठा ipw_dev *ipw = link->priv;

	release_ipwireless(ipw);

	अगर (ipw->tty != शून्य)
		ipwireless_tty_मुक्त(ipw->tty);
	अगर (ipw->network != शून्य)
		ipwireless_network_मुक्त(ipw->network);
	अगर (ipw->hardware != शून्य)
		ipwireless_hardware_मुक्त(ipw->hardware);
	kमुक्त(ipw);
पूर्ण

अटल काष्ठा pcmcia_driver me = अणु
	.owner		= THIS_MODULE,
	.probe          = ipwireless_attach,
	.हटाओ         = ipwireless_detach,
	.name		= IPWIRELESS_PCCARD_NAME,
	.id_table       = ipw_ids
पूर्ण;

/*
 * Module insertion : initialisation of the module.
 * Register the card with cardmgr...
 */
अटल पूर्णांक __init init_ipwireless(व्योम)
अणु
	पूर्णांक ret;

	ret = ipwireless_tty_init();
	अगर (ret != 0)
		वापस ret;

	ret = pcmcia_रेजिस्टर_driver(&me);
	अगर (ret != 0)
		ipwireless_tty_release();

	वापस ret;
पूर्ण

/*
 * Module removal
 */
अटल व्योम __निकास निकास_ipwireless(व्योम)
अणु
	pcmcia_unरेजिस्टर_driver(&me);
	ipwireless_tty_release();
पूर्ण

module_init(init_ipwireless);
module_निकास(निकास_ipwireless);

MODULE_AUTHOR(IPWIRELESS_PCMCIA_AUTHOR);
MODULE_DESCRIPTION(IPWIRELESS_PCCARD_NAME " " IPWIRELESS_PCMCIA_VERSION);
MODULE_LICENSE("GPL");
