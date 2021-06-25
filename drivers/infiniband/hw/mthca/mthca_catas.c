<शैली गुरु>
/*
 * Copyright (c) 2005 Cisco Systems.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/समयr.h>
#समावेश <linux/workqueue.h>

#समावेश "mthca_dev.h"

क्रमागत अणु
	MTHCA_CATAS_POLL_INTERVAL	= 5 * HZ,

	MTHCA_CATAS_TYPE_INTERNAL	= 0,
	MTHCA_CATAS_TYPE_UPLINK		= 3,
	MTHCA_CATAS_TYPE_DDR		= 4,
	MTHCA_CATAS_TYPE_PARITY		= 5,
पूर्ण;

अटल DEFINE_SPINLOCK(catas_lock);

अटल LIST_HEAD(catas_list);
अटल काष्ठा workqueue_काष्ठा *catas_wq;
अटल काष्ठा work_काष्ठा catas_work;

अटल पूर्णांक catas_reset_disable;
module_param_named(catas_reset_disable, catas_reset_disable, पूर्णांक, 0644);
MODULE_PARM_DESC(catas_reset_disable, "disable reset on catastrophic event if nonzero");

अटल व्योम catas_reset(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mthca_dev *dev, *पंचांगpdev;
	LIST_HEAD(tlist);
	पूर्णांक ret;

	mutex_lock(&mthca_device_mutex);

	spin_lock_irq(&catas_lock);
	list_splice_init(&catas_list, &tlist);
	spin_unlock_irq(&catas_lock);

	list_क्रम_each_entry_safe(dev, पंचांगpdev, &tlist, catas_err.list) अणु
		काष्ठा pci_dev *pdev = dev->pdev;
		ret = __mthca_restart_one(dev->pdev);
		/* 'dev' now is not valid */
		अगर (ret)
			prपूर्णांकk(KERN_ERR "mthca %s: Reset failed (%d)\n",
			       pci_name(pdev), ret);
		अन्यथा अणु
			काष्ठा mthca_dev *d = pci_get_drvdata(pdev);
			mthca_dbg(d, "Reset succeeded\n");
		पूर्ण
	पूर्ण

	mutex_unlock(&mthca_device_mutex);
पूर्ण

अटल व्योम handle_catas(काष्ठा mthca_dev *dev)
अणु
	काष्ठा ib_event event;
	अचिन्हित दीर्घ flags;
	स्थिर अक्षर *type;
	पूर्णांक i;

	event.device = &dev->ib_dev;
	event.event  = IB_EVENT_DEVICE_FATAL;
	event.element.port_num = 0;
	dev->active = false;

	ib_dispatch_event(&event);

	चयन (swab32(पढ़ोl(dev->catas_err.map)) >> 24) अणु
	हाल MTHCA_CATAS_TYPE_INTERNAL:
		type = "internal error";
		अवरोध;
	हाल MTHCA_CATAS_TYPE_UPLINK:
		type = "uplink bus error";
		अवरोध;
	हाल MTHCA_CATAS_TYPE_DDR:
		type = "DDR data error";
		अवरोध;
	हाल MTHCA_CATAS_TYPE_PARITY:
		type = "internal parity error";
		अवरोध;
	शेष:
		type = "unknown error";
		अवरोध;
	पूर्ण

	mthca_err(dev, "Catastrophic error detected: %s\n", type);
	क्रम (i = 0; i < dev->catas_err.size; ++i)
		mthca_err(dev, "  buf[%02x]: %08x\n",
			  i, swab32(पढ़ोl(dev->catas_err.map + i)));

	अगर (catas_reset_disable)
		वापस;

	spin_lock_irqsave(&catas_lock, flags);
	list_add(&dev->catas_err.list, &catas_list);
	queue_work(catas_wq, &catas_work);
	spin_unlock_irqrestore(&catas_lock, flags);
पूर्ण

अटल व्योम poll_catas(काष्ठा समयr_list *t)
अणु
	काष्ठा mthca_dev *dev = from_समयr(dev, t, catas_err.समयr);
	पूर्णांक i;

	क्रम (i = 0; i < dev->catas_err.size; ++i)
		अगर (पढ़ोl(dev->catas_err.map + i)) अणु
			handle_catas(dev);
			वापस;
		पूर्ण

	mod_समयr(&dev->catas_err.समयr,
		  round_jअगरfies(jअगरfies + MTHCA_CATAS_POLL_INTERVAL));
पूर्ण

व्योम mthca_start_catas_poll(काष्ठा mthca_dev *dev)
अणु
	phys_addr_t addr;

	समयr_setup(&dev->catas_err.समयr, poll_catas, 0);
	dev->catas_err.map  = शून्य;

	addr = pci_resource_start(dev->pdev, 0) +
		((pci_resource_len(dev->pdev, 0) - 1) &
		 dev->catas_err.addr);

	dev->catas_err.map = ioremap(addr, dev->catas_err.size * 4);
	अगर (!dev->catas_err.map) अणु
		mthca_warn(dev, "couldn't map catastrophic error region "
			   "at 0x%llx/0x%x\n", (अचिन्हित दीर्घ दीर्घ) addr,
			   dev->catas_err.size * 4);
		वापस;
	पूर्ण

	dev->catas_err.समयr.expires  = jअगरfies + MTHCA_CATAS_POLL_INTERVAL;
	INIT_LIST_HEAD(&dev->catas_err.list);
	add_समयr(&dev->catas_err.समयr);
पूर्ण

व्योम mthca_stop_catas_poll(काष्ठा mthca_dev *dev)
अणु
	del_समयr_sync(&dev->catas_err.समयr);

	अगर (dev->catas_err.map)
		iounmap(dev->catas_err.map);

	spin_lock_irq(&catas_lock);
	list_del(&dev->catas_err.list);
	spin_unlock_irq(&catas_lock);
पूर्ण

पूर्णांक __init mthca_catas_init(व्योम)
अणु
	INIT_WORK(&catas_work, catas_reset);

	catas_wq = alloc_ordered_workqueue("mthca_catas", WQ_MEM_RECLAIM);
	अगर (!catas_wq)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम mthca_catas_cleanup(व्योम)
अणु
	destroy_workqueue(catas_wq);
पूर्ण
