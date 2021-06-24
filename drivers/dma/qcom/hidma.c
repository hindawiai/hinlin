<शैली गुरु>
/*
 * Qualcomm Technologies HIDMA DMA engine पूर्णांकerface
 *
 * Copyright (c) 2015-2017, The Linux Foundation. All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

/*
 * Copyright (C) Freescale Semicondutor, Inc. 2007, 2008.
 * Copyright (C) Semihalf 2009
 * Copyright (C) Ilya Yanok, Emcraft Systems 2010
 * Copyright (C) Alexander Popov, Promcontroller 2014
 *
 * Written by Piotr Ziecik <kosmo@semihalf.com>. Hardware description
 * (defines, काष्ठाures and comments) was taken from MPC5121 DMA driver
 * written by Hongjun Chen <hong-jun.chen@मुक्तscale.com>.
 *
 * Approved as OSADL project by a majority of OSADL members and funded
 * by OSADL membership fees in 2009;  क्रम details see www.osadl.org.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 *
 * The full GNU General Public License is included in this distribution in the
 * file called COPYING.
 */

/* Linux Foundation elects GPLv2 license only. */

#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/of_device.h>
#समावेश <linux/property.h>
#समावेश <linux/delay.h>
#समावेश <linux/acpi.h>
#समावेश <linux/irq.h>
#समावेश <linux/atomic.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/msi.h>

#समावेश "../dmaengine.h"
#समावेश "hidma.h"

/*
 * Default idle समय is 2 seconds. This parameter can
 * be overridden by changing the following
 * /sys/bus/platक्रमm/devices/QCOM8061:<xy>/घातer/स्वतःsuspend_delay_ms
 * during kernel boot.
 */
#घोषणा HIDMA_AUTOSUSPEND_TIMEOUT		2000
#घोषणा HIDMA_ERR_INFO_SW			0xFF
#घोषणा HIDMA_ERR_CODE_UNEXPECTED_TERMINATE	0x0
#घोषणा HIDMA_NR_DEFAULT_DESC			10
#घोषणा HIDMA_MSI_INTS				11

अटल अंतरभूत काष्ठा hidma_dev *to_hidma_dev(काष्ठा dma_device *dmadev)
अणु
	वापस container_of(dmadev, काष्ठा hidma_dev, ddev);
पूर्ण

अटल अंतरभूत
काष्ठा hidma_dev *to_hidma_dev_from_lldev(काष्ठा hidma_lldev **_lldevp)
अणु
	वापस container_of(_lldevp, काष्ठा hidma_dev, lldev);
पूर्ण

अटल अंतरभूत काष्ठा hidma_chan *to_hidma_chan(काष्ठा dma_chan *dmach)
अणु
	वापस container_of(dmach, काष्ठा hidma_chan, chan);
पूर्ण

अटल व्योम hidma_मुक्त(काष्ठा hidma_dev *dmadev)
अणु
	INIT_LIST_HEAD(&dmadev->ddev.channels);
पूर्ण

अटल अचिन्हित पूर्णांक nr_desc_prm;
module_param(nr_desc_prm, uपूर्णांक, 0644);
MODULE_PARM_DESC(nr_desc_prm, "number of descriptors (default: 0)");

क्रमागत hidma_cap अणु
	HIDMA_MSI_CAP = 1,
	HIDMA_IDENTITY_CAP,
पूर्ण;

/* process completed descriptors */
अटल व्योम hidma_process_completed(काष्ठा hidma_chan *mchan)
अणु
	काष्ठा dma_device *ddev = mchan->chan.device;
	काष्ठा hidma_dev *mdma = to_hidma_dev(ddev);
	काष्ठा dma_async_tx_descriptor *desc;
	dma_cookie_t last_cookie;
	काष्ठा hidma_desc *mdesc;
	काष्ठा hidma_desc *next;
	अचिन्हित दीर्घ irqflags;
	काष्ठा list_head list;

	INIT_LIST_HEAD(&list);

	/* Get all completed descriptors */
	spin_lock_irqsave(&mchan->lock, irqflags);
	list_splice_tail_init(&mchan->completed, &list);
	spin_unlock_irqrestore(&mchan->lock, irqflags);

	/* Execute callbacks and run dependencies */
	list_क्रम_each_entry_safe(mdesc, next, &list, node) अणु
		क्रमागत dma_status llstat;
		काष्ठा dmaengine_desc_callback cb;
		काष्ठा dmaengine_result result;

		desc = &mdesc->desc;
		last_cookie = desc->cookie;

		llstat = hidma_ll_status(mdma->lldev, mdesc->tre_ch);

		spin_lock_irqsave(&mchan->lock, irqflags);
		अगर (llstat == DMA_COMPLETE) अणु
			mchan->last_success = last_cookie;
			result.result = DMA_TRANS_NOERROR;
		पूर्ण अन्यथा अणु
			result.result = DMA_TRANS_ABORTED;
		पूर्ण

		dma_cookie_complete(desc);
		spin_unlock_irqrestore(&mchan->lock, irqflags);

		dmaengine_desc_get_callback(desc, &cb);

		dma_run_dependencies(desc);

		spin_lock_irqsave(&mchan->lock, irqflags);
		list_move(&mdesc->node, &mchan->मुक्त);
		spin_unlock_irqrestore(&mchan->lock, irqflags);

		dmaengine_desc_callback_invoke(&cb, &result);
	पूर्ण
पूर्ण

/*
 * Called once क्रम each submitted descriptor.
 * PM is locked once क्रम each descriptor that is currently
 * in execution.
 */
अटल व्योम hidma_callback(व्योम *data)
अणु
	काष्ठा hidma_desc *mdesc = data;
	काष्ठा hidma_chan *mchan = to_hidma_chan(mdesc->desc.chan);
	काष्ठा dma_device *ddev = mchan->chan.device;
	काष्ठा hidma_dev *dmadev = to_hidma_dev(ddev);
	अचिन्हित दीर्घ irqflags;
	bool queued = false;

	spin_lock_irqsave(&mchan->lock, irqflags);
	अगर (mdesc->node.next) अणु
		/* Delete from the active list, add to completed list */
		list_move_tail(&mdesc->node, &mchan->completed);
		queued = true;

		/* calculate the next running descriptor */
		mchan->running = list_first_entry(&mchan->active,
						  काष्ठा hidma_desc, node);
	पूर्ण
	spin_unlock_irqrestore(&mchan->lock, irqflags);

	hidma_process_completed(mchan);

	अगर (queued) अणु
		pm_runसमय_mark_last_busy(dmadev->ddev.dev);
		pm_runसमय_put_स्वतःsuspend(dmadev->ddev.dev);
	पूर्ण
पूर्ण

अटल पूर्णांक hidma_chan_init(काष्ठा hidma_dev *dmadev, u32 dma_sig)
अणु
	काष्ठा hidma_chan *mchan;
	काष्ठा dma_device *ddev;

	mchan = devm_kzalloc(dmadev->ddev.dev, माप(*mchan), GFP_KERNEL);
	अगर (!mchan)
		वापस -ENOMEM;

	ddev = &dmadev->ddev;
	mchan->dma_sig = dma_sig;
	mchan->dmadev = dmadev;
	mchan->chan.device = ddev;
	dma_cookie_init(&mchan->chan);

	INIT_LIST_HEAD(&mchan->मुक्त);
	INIT_LIST_HEAD(&mchan->prepared);
	INIT_LIST_HEAD(&mchan->active);
	INIT_LIST_HEAD(&mchan->completed);
	INIT_LIST_HEAD(&mchan->queued);

	spin_lock_init(&mchan->lock);
	list_add_tail(&mchan->chan.device_node, &ddev->channels);
	dmadev->ddev.chancnt++;
	वापस 0;
पूर्ण

अटल व्योम hidma_issue_task(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा hidma_dev *dmadev = from_tasklet(dmadev, t, task);

	pm_runसमय_get_sync(dmadev->ddev.dev);
	hidma_ll_start(dmadev->lldev);
पूर्ण

अटल व्योम hidma_issue_pending(काष्ठा dma_chan *dmach)
अणु
	काष्ठा hidma_chan *mchan = to_hidma_chan(dmach);
	काष्ठा hidma_dev *dmadev = mchan->dmadev;
	अचिन्हित दीर्घ flags;
	काष्ठा hidma_desc *qdesc, *next;
	पूर्णांक status;

	spin_lock_irqsave(&mchan->lock, flags);
	list_क्रम_each_entry_safe(qdesc, next, &mchan->queued, node) अणु
		hidma_ll_queue_request(dmadev->lldev, qdesc->tre_ch);
		list_move_tail(&qdesc->node, &mchan->active);
	पूर्ण

	अगर (!mchan->running) अणु
		काष्ठा hidma_desc *desc = list_first_entry(&mchan->active,
							   काष्ठा hidma_desc,
							   node);
		mchan->running = desc;
	पूर्ण
	spin_unlock_irqrestore(&mchan->lock, flags);

	/* PM will be released in hidma_callback function. */
	status = pm_runसमय_get(dmadev->ddev.dev);
	अगर (status < 0)
		tasklet_schedule(&dmadev->task);
	अन्यथा
		hidma_ll_start(dmadev->lldev);
पूर्ण

अटल अंतरभूत bool hidma_txn_is_success(dma_cookie_t cookie,
		dma_cookie_t last_success, dma_cookie_t last_used)
अणु
	अगर (last_success <= last_used) अणु
		अगर ((cookie <= last_success) || (cookie > last_used))
			वापस true;
	पूर्ण अन्यथा अणु
		अगर ((cookie <= last_success) && (cookie > last_used))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल क्रमागत dma_status hidma_tx_status(काष्ठा dma_chan *dmach,
				       dma_cookie_t cookie,
				       काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा hidma_chan *mchan = to_hidma_chan(dmach);
	क्रमागत dma_status ret;

	ret = dma_cookie_status(dmach, cookie, txstate);
	अगर (ret == DMA_COMPLETE) अणु
		bool is_success;

		is_success = hidma_txn_is_success(cookie, mchan->last_success,
						  dmach->cookie);
		वापस is_success ? ret : DMA_ERROR;
	पूर्ण

	अगर (mchan->छोड़ोd && (ret == DMA_IN_PROGRESS)) अणु
		अचिन्हित दीर्घ flags;
		dma_cookie_t runcookie;

		spin_lock_irqsave(&mchan->lock, flags);
		अगर (mchan->running)
			runcookie = mchan->running->desc.cookie;
		अन्यथा
			runcookie = -EINVAL;

		अगर (runcookie == cookie)
			ret = DMA_PAUSED;

		spin_unlock_irqrestore(&mchan->lock, flags);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Submit descriptor to hardware.
 * Lock the PM क्रम each descriptor we are sending.
 */
अटल dma_cookie_t hidma_tx_submit(काष्ठा dma_async_tx_descriptor *txd)
अणु
	काष्ठा hidma_chan *mchan = to_hidma_chan(txd->chan);
	काष्ठा hidma_dev *dmadev = mchan->dmadev;
	काष्ठा hidma_desc *mdesc;
	अचिन्हित दीर्घ irqflags;
	dma_cookie_t cookie;

	pm_runसमय_get_sync(dmadev->ddev.dev);
	अगर (!hidma_ll_isenabled(dmadev->lldev)) अणु
		pm_runसमय_mark_last_busy(dmadev->ddev.dev);
		pm_runसमय_put_स्वतःsuspend(dmadev->ddev.dev);
		वापस -ENODEV;
	पूर्ण
	pm_runसमय_mark_last_busy(dmadev->ddev.dev);
	pm_runसमय_put_स्वतःsuspend(dmadev->ddev.dev);

	mdesc = container_of(txd, काष्ठा hidma_desc, desc);
	spin_lock_irqsave(&mchan->lock, irqflags);

	/* Move descriptor to queued */
	list_move_tail(&mdesc->node, &mchan->queued);

	/* Update cookie */
	cookie = dma_cookie_assign(txd);

	spin_unlock_irqrestore(&mchan->lock, irqflags);

	वापस cookie;
पूर्ण

अटल पूर्णांक hidma_alloc_chan_resources(काष्ठा dma_chan *dmach)
अणु
	काष्ठा hidma_chan *mchan = to_hidma_chan(dmach);
	काष्ठा hidma_dev *dmadev = mchan->dmadev;
	काष्ठा hidma_desc *mdesc, *पंचांगp;
	अचिन्हित दीर्घ irqflags;
	LIST_HEAD(descs);
	अचिन्हित पूर्णांक i;
	पूर्णांक rc = 0;

	अगर (mchan->allocated)
		वापस 0;

	/* Alloc descriptors क्रम this channel */
	क्रम (i = 0; i < dmadev->nr_descriptors; i++) अणु
		mdesc = kzalloc(माप(काष्ठा hidma_desc), GFP_NOWAIT);
		अगर (!mdesc) अणु
			rc = -ENOMEM;
			अवरोध;
		पूर्ण
		dma_async_tx_descriptor_init(&mdesc->desc, dmach);
		mdesc->desc.tx_submit = hidma_tx_submit;

		rc = hidma_ll_request(dmadev->lldev, mchan->dma_sig,
				      "DMA engine", hidma_callback, mdesc,
				      &mdesc->tre_ch);
		अगर (rc) अणु
			dev_err(dmach->device->dev,
				"channel alloc failed at %u\n", i);
			kमुक्त(mdesc);
			अवरोध;
		पूर्ण
		list_add_tail(&mdesc->node, &descs);
	पूर्ण

	अगर (rc) अणु
		/* वापस the allocated descriptors */
		list_क्रम_each_entry_safe(mdesc, पंचांगp, &descs, node) अणु
			hidma_ll_मुक्त(dmadev->lldev, mdesc->tre_ch);
			kमुक्त(mdesc);
		पूर्ण
		वापस rc;
	पूर्ण

	spin_lock_irqsave(&mchan->lock, irqflags);
	list_splice_tail_init(&descs, &mchan->मुक्त);
	mchan->allocated = true;
	spin_unlock_irqrestore(&mchan->lock, irqflags);
	वापस 1;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
hidma_prep_dma_स_नकल(काष्ठा dma_chan *dmach, dma_addr_t dest, dma_addr_t src,
		माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा hidma_chan *mchan = to_hidma_chan(dmach);
	काष्ठा hidma_desc *mdesc = शून्य;
	काष्ठा hidma_dev *mdma = mchan->dmadev;
	अचिन्हित दीर्घ irqflags;

	/* Get मुक्त descriptor */
	spin_lock_irqsave(&mchan->lock, irqflags);
	अगर (!list_empty(&mchan->मुक्त)) अणु
		mdesc = list_first_entry(&mchan->मुक्त, काष्ठा hidma_desc, node);
		list_del(&mdesc->node);
	पूर्ण
	spin_unlock_irqrestore(&mchan->lock, irqflags);

	अगर (!mdesc)
		वापस शून्य;

	mdesc->desc.flags = flags;
	hidma_ll_set_transfer_params(mdma->lldev, mdesc->tre_ch,
				     src, dest, len, flags,
				     HIDMA_TRE_MEMCPY);

	/* Place descriptor in prepared list */
	spin_lock_irqsave(&mchan->lock, irqflags);
	list_add_tail(&mdesc->node, &mchan->prepared);
	spin_unlock_irqrestore(&mchan->lock, irqflags);

	वापस &mdesc->desc;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
hidma_prep_dma_स_रखो(काष्ठा dma_chan *dmach, dma_addr_t dest, पूर्णांक value,
		माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा hidma_chan *mchan = to_hidma_chan(dmach);
	काष्ठा hidma_desc *mdesc = शून्य;
	काष्ठा hidma_dev *mdma = mchan->dmadev;
	अचिन्हित दीर्घ irqflags;

	/* Get मुक्त descriptor */
	spin_lock_irqsave(&mchan->lock, irqflags);
	अगर (!list_empty(&mchan->मुक्त)) अणु
		mdesc = list_first_entry(&mchan->मुक्त, काष्ठा hidma_desc, node);
		list_del(&mdesc->node);
	पूर्ण
	spin_unlock_irqrestore(&mchan->lock, irqflags);

	अगर (!mdesc)
		वापस शून्य;

	mdesc->desc.flags = flags;
	hidma_ll_set_transfer_params(mdma->lldev, mdesc->tre_ch,
				     value, dest, len, flags,
				     HIDMA_TRE_MEMSET);

	/* Place descriptor in prepared list */
	spin_lock_irqsave(&mchan->lock, irqflags);
	list_add_tail(&mdesc->node, &mchan->prepared);
	spin_unlock_irqrestore(&mchan->lock, irqflags);

	वापस &mdesc->desc;
पूर्ण

अटल पूर्णांक hidma_terminate_channel(काष्ठा dma_chan *chan)
अणु
	काष्ठा hidma_chan *mchan = to_hidma_chan(chan);
	काष्ठा hidma_dev *dmadev = to_hidma_dev(mchan->chan.device);
	काष्ठा hidma_desc *पंचांगp, *mdesc;
	अचिन्हित दीर्घ irqflags;
	LIST_HEAD(list);
	पूर्णांक rc;

	pm_runसमय_get_sync(dmadev->ddev.dev);
	/* give completed requests a chance to finish */
	hidma_process_completed(mchan);

	spin_lock_irqsave(&mchan->lock, irqflags);
	mchan->last_success = 0;
	list_splice_init(&mchan->active, &list);
	list_splice_init(&mchan->prepared, &list);
	list_splice_init(&mchan->completed, &list);
	list_splice_init(&mchan->queued, &list);
	spin_unlock_irqrestore(&mchan->lock, irqflags);

	/* this suspends the existing transfer */
	rc = hidma_ll_disable(dmadev->lldev);
	अगर (rc) अणु
		dev_err(dmadev->ddev.dev, "channel did not pause\n");
		जाओ out;
	पूर्ण

	/* वापस all user requests */
	list_क्रम_each_entry_safe(mdesc, पंचांगp, &list, node) अणु
		काष्ठा dma_async_tx_descriptor *txd = &mdesc->desc;

		dma_descriptor_unmap(txd);
		dmaengine_desc_get_callback_invoke(txd, शून्य);
		dma_run_dependencies(txd);

		/* move myself to मुक्त_list */
		list_move(&mdesc->node, &mchan->मुक्त);
	पूर्ण

	rc = hidma_ll_enable(dmadev->lldev);
out:
	pm_runसमय_mark_last_busy(dmadev->ddev.dev);
	pm_runसमय_put_स्वतःsuspend(dmadev->ddev.dev);
	वापस rc;
पूर्ण

अटल पूर्णांक hidma_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा hidma_chan *mchan = to_hidma_chan(chan);
	काष्ठा hidma_dev *dmadev = to_hidma_dev(mchan->chan.device);
	पूर्णांक rc;

	rc = hidma_terminate_channel(chan);
	अगर (rc)
		वापस rc;

	/* reinitialize the hardware */
	pm_runसमय_get_sync(dmadev->ddev.dev);
	rc = hidma_ll_setup(dmadev->lldev);
	pm_runसमय_mark_last_busy(dmadev->ddev.dev);
	pm_runसमय_put_स्वतःsuspend(dmadev->ddev.dev);
	वापस rc;
पूर्ण

अटल व्योम hidma_मुक्त_chan_resources(काष्ठा dma_chan *dmach)
अणु
	काष्ठा hidma_chan *mchan = to_hidma_chan(dmach);
	काष्ठा hidma_dev *mdma = mchan->dmadev;
	काष्ठा hidma_desc *mdesc, *पंचांगp;
	अचिन्हित दीर्घ irqflags;
	LIST_HEAD(descs);

	/* terminate running transactions and मुक्त descriptors */
	hidma_terminate_channel(dmach);

	spin_lock_irqsave(&mchan->lock, irqflags);

	/* Move data */
	list_splice_tail_init(&mchan->मुक्त, &descs);

	/* Free descriptors */
	list_क्रम_each_entry_safe(mdesc, पंचांगp, &descs, node) अणु
		hidma_ll_मुक्त(mdma->lldev, mdesc->tre_ch);
		list_del(&mdesc->node);
		kमुक्त(mdesc);
	पूर्ण

	mchan->allocated = false;
	spin_unlock_irqrestore(&mchan->lock, irqflags);
पूर्ण

अटल पूर्णांक hidma_छोड़ो(काष्ठा dma_chan *chan)
अणु
	काष्ठा hidma_chan *mchan;
	काष्ठा hidma_dev *dmadev;

	mchan = to_hidma_chan(chan);
	dmadev = to_hidma_dev(mchan->chan.device);
	अगर (!mchan->छोड़ोd) अणु
		pm_runसमय_get_sync(dmadev->ddev.dev);
		अगर (hidma_ll_disable(dmadev->lldev))
			dev_warn(dmadev->ddev.dev, "channel did not stop\n");
		mchan->छोड़ोd = true;
		pm_runसमय_mark_last_busy(dmadev->ddev.dev);
		pm_runसमय_put_स्वतःsuspend(dmadev->ddev.dev);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hidma_resume(काष्ठा dma_chan *chan)
अणु
	काष्ठा hidma_chan *mchan;
	काष्ठा hidma_dev *dmadev;
	पूर्णांक rc = 0;

	mchan = to_hidma_chan(chan);
	dmadev = to_hidma_dev(mchan->chan.device);
	अगर (mchan->छोड़ोd) अणु
		pm_runसमय_get_sync(dmadev->ddev.dev);
		rc = hidma_ll_enable(dmadev->lldev);
		अगर (!rc)
			mchan->छोड़ोd = false;
		अन्यथा
			dev_err(dmadev->ddev.dev,
				"failed to resume the channel");
		pm_runसमय_mark_last_busy(dmadev->ddev.dev);
		pm_runसमय_put_स्वतःsuspend(dmadev->ddev.dev);
	पूर्ण
	वापस rc;
पूर्ण

अटल irqवापस_t hidma_chirq_handler(पूर्णांक chirq, व्योम *arg)
अणु
	काष्ठा hidma_lldev *lldev = arg;

	/*
	 * All पूर्णांकerrupts are request driven.
	 * HW करोesn't send an पूर्णांकerrupt by itself.
	 */
	वापस hidma_ll_पूर्णांकhandler(chirq, lldev);
पूर्ण

#अगर_घोषित CONFIG_GENERIC_MSI_IRQ_DOMAIN
अटल irqवापस_t hidma_chirq_handler_msi(पूर्णांक chirq, व्योम *arg)
अणु
	काष्ठा hidma_lldev **lldevp = arg;
	काष्ठा hidma_dev *dmadev = to_hidma_dev_from_lldev(lldevp);

	वापस hidma_ll_पूर्णांकhandler_msi(chirq, *lldevp,
				       1 << (chirq - dmadev->msi_virqbase));
पूर्ण
#पूर्ण_अगर

अटल sमाप_प्रकार hidma_show_values(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hidma_dev *mdev = dev_get_drvdata(dev);

	buf[0] = 0;

	अगर (म_भेद(attr->attr.name, "chid") == 0)
		प्र_लिखो(buf, "%d\n", mdev->chidx);

	वापस म_माप(buf);
पूर्ण

अटल अंतरभूत व्योम  hidma_sysfs_uninit(काष्ठा hidma_dev *dev)
अणु
	device_हटाओ_file(dev->ddev.dev, dev->chid_attrs);
पूर्ण

अटल काष्ठा device_attribute*
hidma_create_sysfs_entry(काष्ठा hidma_dev *dev, अक्षर *name, पूर्णांक mode)
अणु
	काष्ठा device_attribute *attrs;
	अक्षर *name_copy;

	attrs = devm_kदो_स्मृति(dev->ddev.dev, माप(काष्ठा device_attribute),
			     GFP_KERNEL);
	अगर (!attrs)
		वापस शून्य;

	name_copy = devm_kstrdup(dev->ddev.dev, name, GFP_KERNEL);
	अगर (!name_copy)
		वापस शून्य;

	attrs->attr.name = name_copy;
	attrs->attr.mode = mode;
	attrs->show = hidma_show_values;
	sysfs_attr_init(&attrs->attr);

	वापस attrs;
पूर्ण

अटल पूर्णांक hidma_sysfs_init(काष्ठा hidma_dev *dev)
अणु
	dev->chid_attrs = hidma_create_sysfs_entry(dev, "chid", S_IRUGO);
	अगर (!dev->chid_attrs)
		वापस -ENOMEM;

	वापस device_create_file(dev->ddev.dev, dev->chid_attrs);
पूर्ण

#अगर_घोषित CONFIG_GENERIC_MSI_IRQ_DOMAIN
अटल व्योम hidma_ग_लिखो_msi_msg(काष्ठा msi_desc *desc, काष्ठा msi_msg *msg)
अणु
	काष्ठा device *dev = msi_desc_to_dev(desc);
	काष्ठा hidma_dev *dmadev = dev_get_drvdata(dev);

	अगर (!desc->platक्रमm.msi_index) अणु
		ग_लिखोl(msg->address_lo, dmadev->dev_evca + 0x118);
		ग_लिखोl(msg->address_hi, dmadev->dev_evca + 0x11C);
		ग_लिखोl(msg->data, dmadev->dev_evca + 0x120);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम hidma_मुक्त_msis(काष्ठा hidma_dev *dmadev)
अणु
#अगर_घोषित CONFIG_GENERIC_MSI_IRQ_DOMAIN
	काष्ठा device *dev = dmadev->ddev.dev;
	काष्ठा msi_desc *desc;

	/* मुक्त allocated MSI पूर्णांकerrupts above */
	क्रम_each_msi_entry(desc, dev)
		devm_मुक्त_irq(dev, desc->irq, &dmadev->lldev);

	platक्रमm_msi_करोमुख्य_मुक्त_irqs(dev);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक hidma_request_msi(काष्ठा hidma_dev *dmadev,
			     काष्ठा platक्रमm_device *pdev)
अणु
#अगर_घोषित CONFIG_GENERIC_MSI_IRQ_DOMAIN
	पूर्णांक rc;
	काष्ठा msi_desc *desc;
	काष्ठा msi_desc *failed_desc = शून्य;

	rc = platक्रमm_msi_करोमुख्य_alloc_irqs(&pdev->dev, HIDMA_MSI_INTS,
					    hidma_ग_लिखो_msi_msg);
	अगर (rc)
		वापस rc;

	क्रम_each_msi_entry(desc, &pdev->dev) अणु
		अगर (!desc->platक्रमm.msi_index)
			dmadev->msi_virqbase = desc->irq;

		rc = devm_request_irq(&pdev->dev, desc->irq,
				       hidma_chirq_handler_msi,
				       0, "qcom-hidma-msi",
				       &dmadev->lldev);
		अगर (rc) अणु
			failed_desc = desc;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (rc) अणु
		/* मुक्त allocated MSI पूर्णांकerrupts above */
		क्रम_each_msi_entry(desc, &pdev->dev) अणु
			अगर (desc == failed_desc)
				अवरोध;
			devm_मुक्त_irq(&pdev->dev, desc->irq,
				      &dmadev->lldev);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Add callback to मुक्त MSIs on tearकरोwn */
		hidma_ll_setup_irq(dmadev->lldev, true);

	पूर्ण
	अगर (rc)
		dev_warn(&pdev->dev,
			 "failed to request MSI irq, falling back to wired IRQ\n");
	वापस rc;
#अन्यथा
	वापस -EINVAL;
#पूर्ण_अगर
पूर्ण

अटल bool hidma_test_capability(काष्ठा device *dev, क्रमागत hidma_cap test_cap)
अणु
	क्रमागत hidma_cap cap;

	cap = (क्रमागत hidma_cap) device_get_match_data(dev);
	वापस cap ? ((cap & test_cap) > 0) : 0;
पूर्ण

अटल पूर्णांक hidma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hidma_dev *dmadev;
	काष्ठा resource *trca_resource;
	काष्ठा resource *evca_resource;
	पूर्णांक chirq;
	व्योम __iomem *evca;
	व्योम __iomem *trca;
	पूर्णांक rc;
	bool msi;

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, HIDMA_AUTOSUSPEND_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	trca_resource = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	trca = devm_ioremap_resource(&pdev->dev, trca_resource);
	अगर (IS_ERR(trca)) अणु
		rc = -ENOMEM;
		जाओ bailout;
	पूर्ण

	evca_resource = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	evca = devm_ioremap_resource(&pdev->dev, evca_resource);
	अगर (IS_ERR(evca)) अणु
		rc = -ENOMEM;
		जाओ bailout;
	पूर्ण

	/*
	 * This driver only handles the channel IRQs.
	 * Common IRQ is handled by the management driver.
	 */
	chirq = platक्रमm_get_irq(pdev, 0);
	अगर (chirq < 0) अणु
		rc = -ENODEV;
		जाओ bailout;
	पूर्ण

	dmadev = devm_kzalloc(&pdev->dev, माप(*dmadev), GFP_KERNEL);
	अगर (!dmadev) अणु
		rc = -ENOMEM;
		जाओ bailout;
	पूर्ण

	INIT_LIST_HEAD(&dmadev->ddev.channels);
	spin_lock_init(&dmadev->lock);
	dmadev->ddev.dev = &pdev->dev;
	pm_runसमय_get_sync(dmadev->ddev.dev);

	dma_cap_set(DMA_MEMCPY, dmadev->ddev.cap_mask);
	dma_cap_set(DMA_MEMSET, dmadev->ddev.cap_mask);
	अगर (WARN_ON(!pdev->dev.dma_mask)) अणु
		rc = -ENXIO;
		जाओ dmaमुक्त;
	पूर्ण

	dmadev->dev_evca = evca;
	dmadev->evca_resource = evca_resource;
	dmadev->dev_trca = trca;
	dmadev->trca_resource = trca_resource;
	dmadev->ddev.device_prep_dma_स_नकल = hidma_prep_dma_स_नकल;
	dmadev->ddev.device_prep_dma_स_रखो = hidma_prep_dma_स_रखो;
	dmadev->ddev.device_alloc_chan_resources = hidma_alloc_chan_resources;
	dmadev->ddev.device_मुक्त_chan_resources = hidma_मुक्त_chan_resources;
	dmadev->ddev.device_tx_status = hidma_tx_status;
	dmadev->ddev.device_issue_pending = hidma_issue_pending;
	dmadev->ddev.device_छोड़ो = hidma_छोड़ो;
	dmadev->ddev.device_resume = hidma_resume;
	dmadev->ddev.device_terminate_all = hidma_terminate_all;
	dmadev->ddev.copy_align = 8;

	/*
	 * Determine the MSI capability of the platक्रमm. Old HW करोesn't
	 * support MSI.
	 */
	msi = hidma_test_capability(&pdev->dev, HIDMA_MSI_CAP);
	device_property_पढ़ो_u32(&pdev->dev, "desc-count",
				 &dmadev->nr_descriptors);

	अगर (nr_desc_prm) अणु
		dev_info(&pdev->dev, "overriding number of descriptors as %d\n",
			 nr_desc_prm);
		dmadev->nr_descriptors = nr_desc_prm;
	पूर्ण

	अगर (!dmadev->nr_descriptors)
		dmadev->nr_descriptors = HIDMA_NR_DEFAULT_DESC;

	अगर (hidma_test_capability(&pdev->dev, HIDMA_IDENTITY_CAP))
		dmadev->chidx = पढ़ोl(dmadev->dev_trca + 0x40);
	अन्यथा
		dmadev->chidx = पढ़ोl(dmadev->dev_trca + 0x28);

	/* Set DMA mask to 64 bits. */
	rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (rc) अणु
		dev_warn(&pdev->dev, "unable to set coherent mask to 64");
		rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		अगर (rc)
			जाओ dmaमुक्त;
	पूर्ण

	dmadev->lldev = hidma_ll_init(dmadev->ddev.dev,
				      dmadev->nr_descriptors, dmadev->dev_trca,
				      dmadev->dev_evca, dmadev->chidx);
	अगर (!dmadev->lldev) अणु
		rc = -EPROBE_DEFER;
		जाओ dmaमुक्त;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dmadev);
	अगर (msi)
		rc = hidma_request_msi(dmadev, pdev);

	अगर (!msi || rc) अणु
		hidma_ll_setup_irq(dmadev->lldev, false);
		rc = devm_request_irq(&pdev->dev, chirq, hidma_chirq_handler,
				      0, "qcom-hidma", dmadev->lldev);
		अगर (rc)
			जाओ uninit;
	पूर्ण

	INIT_LIST_HEAD(&dmadev->ddev.channels);
	rc = hidma_chan_init(dmadev, 0);
	अगर (rc)
		जाओ uninit;

	rc = dma_async_device_रेजिस्टर(&dmadev->ddev);
	अगर (rc)
		जाओ uninit;

	dmadev->irq = chirq;
	tasklet_setup(&dmadev->task, hidma_issue_task);
	hidma_debug_init(dmadev);
	hidma_sysfs_init(dmadev);
	dev_info(&pdev->dev, "HI-DMA engine driver registration complete\n");
	pm_runसमय_mark_last_busy(dmadev->ddev.dev);
	pm_runसमय_put_स्वतःsuspend(dmadev->ddev.dev);
	वापस 0;

uninit:
	अगर (msi)
		hidma_मुक्त_msis(dmadev);

	hidma_ll_uninit(dmadev->lldev);
dmaमुक्त:
	अगर (dmadev)
		hidma_मुक्त(dmadev);
bailout:
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	वापस rc;
पूर्ण

अटल व्योम hidma_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hidma_dev *dmadev = platक्रमm_get_drvdata(pdev);

	dev_info(dmadev->ddev.dev, "HI-DMA engine shutdown\n");

	pm_runसमय_get_sync(dmadev->ddev.dev);
	अगर (hidma_ll_disable(dmadev->lldev))
		dev_warn(dmadev->ddev.dev, "channel did not stop\n");
	pm_runसमय_mark_last_busy(dmadev->ddev.dev);
	pm_runसमय_put_स्वतःsuspend(dmadev->ddev.dev);

पूर्ण

अटल पूर्णांक hidma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hidma_dev *dmadev = platक्रमm_get_drvdata(pdev);

	pm_runसमय_get_sync(dmadev->ddev.dev);
	dma_async_device_unरेजिस्टर(&dmadev->ddev);
	अगर (!dmadev->lldev->msi_support)
		devm_मुक्त_irq(dmadev->ddev.dev, dmadev->irq, dmadev->lldev);
	अन्यथा
		hidma_मुक्त_msis(dmadev);

	tasklet_समाप्त(&dmadev->task);
	hidma_sysfs_uninit(dmadev);
	hidma_debug_uninit(dmadev);
	hidma_ll_uninit(dmadev->lldev);
	hidma_मुक्त(dmadev);

	dev_info(&pdev->dev, "HI-DMA engine removed\n");
	pm_runसमय_put_sync_suspend(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_ACPI)
अटल स्थिर काष्ठा acpi_device_id hidma_acpi_ids[] = अणु
	अणु"QCOM8061"पूर्ण,
	अणु"QCOM8062", HIDMA_MSI_CAPपूर्ण,
	अणु"QCOM8063", (HIDMA_MSI_CAP | HIDMA_IDENTITY_CAP)पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, hidma_acpi_ids);
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id hidma_match[] = अणु
	अणु.compatible = "qcom,hidma-1.0",पूर्ण,
	अणु.compatible = "qcom,hidma-1.1", .data = (व्योम *)(HIDMA_MSI_CAP),पूर्ण,
	अणु.compatible = "qcom,hidma-1.2",
	 .data = (व्योम *)(HIDMA_MSI_CAP | HIDMA_IDENTITY_CAP),पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hidma_match);

अटल काष्ठा platक्रमm_driver hidma_driver = अणु
	.probe = hidma_probe,
	.हटाओ = hidma_हटाओ,
	.shutकरोwn = hidma_shutकरोwn,
	.driver = अणु
		   .name = "hidma",
		   .of_match_table = hidma_match,
		   .acpi_match_table = ACPI_PTR(hidma_acpi_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(hidma_driver);
MODULE_LICENSE("GPL v2");
