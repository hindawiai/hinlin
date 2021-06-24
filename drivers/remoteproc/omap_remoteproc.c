<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP Remote Processor driver
 *
 * Copyright (C) 2011-2020 Texas Instruments Incorporated - http://www.ti.com/
 * Copyright (C) 2011 Google, Inc.
 *
 * Ohad Ben-Cohen <ohad@wizery.com>
 * Brian Swetland <swetland@google.com>
 * Fernanकरो Guzman Lugo <fernanकरो.lugo@ti.com>
 * Mark Grosen <mgrosen@ti.com>
 * Suman Anna <s-anna@ti.com>
 * Hari Kanigeri <h-kanigeri2@ti.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk/ti.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_device.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/remoteproc.h>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/omap-iommu.h>
#समावेश <linux/omap-mailbox.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/reset.h>
#समावेश <घड़ीsource/समयr-ti-dm.h>

#समावेश <linux/platक्रमm_data/dmसमयr-omap.h>

#समावेश "omap_remoteproc.h"
#समावेश "remoteproc_internal.h"

/* शेष स्वतः-suspend delay (ms) */
#घोषणा DEFAULT_AUTOSUSPEND_DELAY		10000

/**
 * काष्ठा omap_rproc_boot_data - boot data काष्ठाure क्रम the DSP omap rprocs
 * @syscon: regmap handle क्रम the प्रणाली control configuration module
 * @boot_reg: boot रेजिस्टर offset within the @syscon regmap
 * @boot_reg_shअगरt: bit-field shअगरt required क्रम the boot address value in
 *		    @boot_reg
 */
काष्ठा omap_rproc_boot_data अणु
	काष्ठा regmap *syscon;
	अचिन्हित पूर्णांक boot_reg;
	अचिन्हित पूर्णांक boot_reg_shअगरt;
पूर्ण;

/**
 * काष्ठा omap_rproc_mem - पूर्णांकernal memory काष्ठाure
 * @cpu_addr: MPU भव address of the memory region
 * @bus_addr: bus address used to access the memory region
 * @dev_addr: device address of the memory region from DSP view
 * @size: size of the memory region
 */
काष्ठा omap_rproc_mem अणु
	व्योम __iomem *cpu_addr;
	phys_addr_t bus_addr;
	u32 dev_addr;
	माप_प्रकार size;
पूर्ण;

/**
 * काष्ठा omap_rproc_समयr - data काष्ठाure क्रम a समयr used by a omap rproc
 * @odt: समयr poपूर्णांकer
 * @समयr_ops: OMAP dmसमयr ops क्रम @odt समयr
 * @irq: समयr irq
 */
काष्ठा omap_rproc_समयr अणु
	काष्ठा omap_dm_समयr *odt;
	स्थिर काष्ठा omap_dm_समयr_ops *समयr_ops;
	पूर्णांक irq;
पूर्ण;

/**
 * काष्ठा omap_rproc - omap remote processor state
 * @mbox: mailbox channel handle
 * @client: mailbox client to request the mailbox channel
 * @boot_data: boot data काष्ठाure क्रम setting processor boot address
 * @mem: पूर्णांकernal memory regions data
 * @num_mems: number of पूर्णांकernal memory regions
 * @num_समयrs: number of rproc समयr(s)
 * @num_wd_समयrs: number of rproc watchकरोg समयrs
 * @समयrs: समयr(s) info used by rproc
 * @स्वतःsuspend_delay: स्वतः-suspend delay value to be used क्रम runसमय pm
 * @need_resume: अगर true a resume is needed in the प्रणाली resume callback
 * @rproc: rproc handle
 * @reset: reset handle
 * @pm_comp: completion primitive to sync क्रम suspend response
 * @fck: functional घड़ी क्रम the remoteproc
 * @suspend_acked: state machine flag to store the suspend request ack
 */
काष्ठा omap_rproc अणु
	काष्ठा mbox_chan *mbox;
	काष्ठा mbox_client client;
	काष्ठा omap_rproc_boot_data *boot_data;
	काष्ठा omap_rproc_mem *mem;
	पूर्णांक num_mems;
	पूर्णांक num_समयrs;
	पूर्णांक num_wd_समयrs;
	काष्ठा omap_rproc_समयr *समयrs;
	पूर्णांक स्वतःsuspend_delay;
	bool need_resume;
	काष्ठा rproc *rproc;
	काष्ठा reset_control *reset;
	काष्ठा completion pm_comp;
	काष्ठा clk *fck;
	bool suspend_acked;
पूर्ण;

/**
 * काष्ठा omap_rproc_mem_data - memory definitions क्रम an omap remote processor
 * @name: name क्रम this memory entry
 * @dev_addr: device address क्रम the memory entry
 */
काष्ठा omap_rproc_mem_data अणु
	स्थिर अक्षर *name;
	स्थिर u32 dev_addr;
पूर्ण;

/**
 * काष्ठा omap_rproc_dev_data - device data क्रम the omap remote processor
 * @device_name: device name of the remote processor
 * @mems: memory definitions क्रम this remote processor
 */
काष्ठा omap_rproc_dev_data अणु
	स्थिर अक्षर *device_name;
	स्थिर काष्ठा omap_rproc_mem_data *mems;
पूर्ण;

/**
 * omap_rproc_request_समयr() - request a समयr क्रम a remoteproc
 * @dev: device requesting the समयr
 * @np: device node poपूर्णांकer to the desired समयr
 * @समयr: handle to a काष्ठा omap_rproc_समयr to वापस the समयr handle
 *
 * This helper function is used primarily to request a समयr associated with
 * a remoteproc. The वापसed handle is stored in the .odt field of the
 * @समयr काष्ठाure passed in, and is used to invoke other समयr specअगरic
 * ops (like starting a समयr either during device initialization or during
 * a resume operation, or क्रम stopping/मुक्तing a समयr).
 *
 * Return: 0 on success, otherwise an appropriate failure
 */
अटल पूर्णांक omap_rproc_request_समयr(काष्ठा device *dev, काष्ठा device_node *np,
				    काष्ठा omap_rproc_समयr *समयr)
अणु
	पूर्णांक ret;

	समयr->odt = समयr->समयr_ops->request_by_node(np);
	अगर (!समयr->odt) अणु
		dev_err(dev, "request for timer node %p failed\n", np);
		वापस -EBUSY;
	पूर्ण

	ret = समयr->समयr_ops->set_source(समयr->odt, OMAP_TIMER_SRC_SYS_CLK);
	अगर (ret) अणु
		dev_err(dev, "error setting OMAP_TIMER_SRC_SYS_CLK as source for timer node %p\n",
			np);
		समयr->समयr_ops->मुक्त(समयr->odt);
		वापस ret;
	पूर्ण

	/* clean counter, remoteproc code will set the value */
	समयr->समयr_ops->set_load(समयr->odt, 0);

	वापस 0;
पूर्ण

/**
 * omap_rproc_start_समयr() - start a समयr क्रम a remoteproc
 * @समयr: handle to a OMAP rproc समयr
 *
 * This helper function is used to start a समयr associated with a remoteproc,
 * obtained using the request_समयr ops. The helper function needs to be
 * invoked by the driver to start the समयr (during device initialization)
 * or to just resume the समयr.
 *
 * Return: 0 on success, otherwise a failure as वापसed by DMTimer ops
 */
अटल अंतरभूत पूर्णांक omap_rproc_start_समयr(काष्ठा omap_rproc_समयr *समयr)
अणु
	वापस समयr->समयr_ops->start(समयr->odt);
पूर्ण

/**
 * omap_rproc_stop_समयr() - stop a समयr क्रम a remoteproc
 * @समयr: handle to a OMAP rproc समयr
 *
 * This helper function is used to disable a समयr associated with a
 * remoteproc, and needs to be called either during a device shutकरोwn
 * or suspend operation. The separate helper function allows the driver
 * to just stop a समयr without having to release the समयr during a
 * suspend operation.
 *
 * Return: 0 on success, otherwise a failure as वापसed by DMTimer ops
 */
अटल अंतरभूत पूर्णांक omap_rproc_stop_समयr(काष्ठा omap_rproc_समयr *समयr)
अणु
	वापस समयr->समयr_ops->stop(समयr->odt);
पूर्ण

/**
 * omap_rproc_release_समयr() - release a समयr क्रम a remoteproc
 * @समयr: handle to a OMAP rproc समयr
 *
 * This helper function is used primarily to release a समयr associated
 * with a remoteproc. The dmसमयr will be available क्रम other clients to
 * use once released.
 *
 * Return: 0 on success, otherwise a failure as वापसed by DMTimer ops
 */
अटल अंतरभूत पूर्णांक omap_rproc_release_समयr(काष्ठा omap_rproc_समयr *समयr)
अणु
	वापस समयr->समयr_ops->मुक्त(समयr->odt);
पूर्ण

/**
 * omap_rproc_get_समयr_irq() - get the irq क्रम a समयr
 * @समयr: handle to a OMAP rproc समयr
 *
 * This function is used to get the irq associated with a watchकरोg समयr. The
 * function is called by the OMAP remoteproc driver to रेजिस्टर a पूर्णांकerrupt
 * handler to handle watchकरोg events on the remote processor.
 *
 * Return: irq id on success, otherwise a failure as वापसed by DMTimer ops
 */
अटल अंतरभूत पूर्णांक omap_rproc_get_समयr_irq(काष्ठा omap_rproc_समयr *समयr)
अणु
	वापस समयr->समयr_ops->get_irq(समयr->odt);
पूर्ण

/**
 * omap_rproc_ack_समयr_irq() - acknowledge a समयr irq
 * @समयr: handle to a OMAP rproc समयr
 *
 * This function is used to clear the irq associated with a watchकरोg समयr. The
 * The function is called by the OMAP remoteproc upon a watchकरोg event on the
 * remote processor to clear the पूर्णांकerrupt status of the watchकरोg समयr.
 */
अटल अंतरभूत व्योम omap_rproc_ack_समयr_irq(काष्ठा omap_rproc_समयr *समयr)
अणु
	समयr->समयr_ops->ग_लिखो_status(समयr->odt, OMAP_TIMER_INT_OVERFLOW);
पूर्ण

/**
 * omap_rproc_watchकरोg_isr() - Watchकरोg ISR handler क्रम remoteproc device
 * @irq: IRQ number associated with a watchकरोg समयr
 * @data: IRQ handler data
 *
 * This ISR routine executes the required necessary low-level code to
 * acknowledge a watchकरोg समयr पूर्णांकerrupt. There can be multiple watchकरोg
 * समयrs associated with a rproc (like IPUs which have 2 watchकरोg समयrs,
 * one per Cortex M3/M4 core), so a lookup has to be perक्रमmed to identअगरy
 * the समयr to acknowledge its पूर्णांकerrupt.
 *
 * The function also invokes rproc_report_crash to report the watchकरोg event
 * to the remoteproc driver core, to trigger a recovery.
 *
 * Return: IRQ_HANDLED on success, otherwise IRQ_NONE
 */
अटल irqवापस_t omap_rproc_watchकरोg_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rproc *rproc = data;
	काष्ठा omap_rproc *oproc = rproc->priv;
	काष्ठा device *dev = rproc->dev.parent;
	काष्ठा omap_rproc_समयr *समयrs = oproc->समयrs;
	काष्ठा omap_rproc_समयr *wd_समयr = शून्य;
	पूर्णांक num_समयrs = oproc->num_समयrs + oproc->num_wd_समयrs;
	पूर्णांक i;

	क्रम (i = oproc->num_समयrs; i < num_समयrs; i++) अणु
		अगर (समयrs[i].irq > 0 && irq == समयrs[i].irq) अणु
			wd_समयr = &समयrs[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!wd_समयr) अणु
		dev_err(dev, "invalid timer\n");
		वापस IRQ_NONE;
	पूर्ण

	omap_rproc_ack_समयr_irq(wd_समयr);

	rproc_report_crash(rproc, RPROC_WATCHDOG);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * omap_rproc_enable_समयrs() - enable the समयrs क्रम a remoteproc
 * @rproc: handle of a remote processor
 * @configure: boolean flag used to acquire and configure the समयr handle
 *
 * This function is used primarily to enable the समयrs associated with
 * a remoteproc. The configure flag is provided to allow the driver to
 * to either acquire and start a समयr (during device initialization) or
 * to just start a समयr (during a resume operation).
 *
 * Return: 0 on success, otherwise an appropriate failure
 */
अटल पूर्णांक omap_rproc_enable_समयrs(काष्ठा rproc *rproc, bool configure)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;
	काष्ठा platक्रमm_device *tpdev;
	काष्ठा dmसमयr_platक्रमm_data *tpdata;
	स्थिर काष्ठा omap_dm_समयr_ops *समयr_ops;
	काष्ठा omap_rproc *oproc = rproc->priv;
	काष्ठा omap_rproc_समयr *समयrs = oproc->समयrs;
	काष्ठा device *dev = rproc->dev.parent;
	काष्ठा device_node *np = शून्य;
	पूर्णांक num_समयrs = oproc->num_समयrs + oproc->num_wd_समयrs;

	अगर (!num_समयrs)
		वापस 0;

	अगर (!configure)
		जाओ start_समयrs;

	क्रम (i = 0; i < num_समयrs; i++) अणु
		अगर (i < oproc->num_समयrs)
			np = of_parse_phandle(dev->of_node, "ti,timers", i);
		अन्यथा
			np = of_parse_phandle(dev->of_node,
					      "ti,watchdog-timers",
					      (i - oproc->num_समयrs));
		अगर (!np) अणु
			ret = -ENXIO;
			dev_err(dev, "device node lookup for timer at index %d failed: %d\n",
				i < oproc->num_समयrs ? i :
				i - oproc->num_समयrs, ret);
			जाओ मुक्त_समयrs;
		पूर्ण

		tpdev = of_find_device_by_node(np);
		अगर (!tpdev) अणु
			ret = -ENODEV;
			dev_err(dev, "could not get timer platform device\n");
			जाओ put_node;
		पूर्ण

		tpdata = dev_get_platdata(&tpdev->dev);
		put_device(&tpdev->dev);
		अगर (!tpdata) अणु
			ret = -EINVAL;
			dev_err(dev, "dmtimer pdata structure NULL\n");
			जाओ put_node;
		पूर्ण

		समयr_ops = tpdata->समयr_ops;
		अगर (!समयr_ops || !समयr_ops->request_by_node ||
		    !समयr_ops->set_source || !समयr_ops->set_load ||
		    !समयr_ops->मुक्त || !समयr_ops->start ||
		    !समयr_ops->stop || !समयr_ops->get_irq ||
		    !समयr_ops->ग_लिखो_status) अणु
			ret = -EINVAL;
			dev_err(dev, "device does not have required timer ops\n");
			जाओ put_node;
		पूर्ण

		समयrs[i].irq = -1;
		समयrs[i].समयr_ops = समयr_ops;
		ret = omap_rproc_request_समयr(dev, np, &समयrs[i]);
		अगर (ret) अणु
			dev_err(dev, "request for timer %p failed: %d\n", np,
				ret);
			जाओ put_node;
		पूर्ण
		of_node_put(np);

		अगर (i >= oproc->num_समयrs) अणु
			समयrs[i].irq = omap_rproc_get_समयr_irq(&समयrs[i]);
			अगर (समयrs[i].irq < 0) अणु
				dev_err(dev, "get_irq for timer %p failed: %d\n",
					np, समयrs[i].irq);
				ret = -EBUSY;
				जाओ मुक्त_समयrs;
			पूर्ण

			ret = request_irq(समयrs[i].irq,
					  omap_rproc_watchकरोg_isr, IRQF_SHARED,
					  "rproc-wdt", rproc);
			अगर (ret) अणु
				dev_err(dev, "error requesting irq for timer %p\n",
					np);
				omap_rproc_release_समयr(&समयrs[i]);
				समयrs[i].odt = शून्य;
				समयrs[i].समयr_ops = शून्य;
				समयrs[i].irq = -1;
				जाओ मुक्त_समयrs;
			पूर्ण
		पूर्ण
	पूर्ण

start_समयrs:
	क्रम (i = 0; i < num_समयrs; i++) अणु
		ret = omap_rproc_start_समयr(&समयrs[i]);
		अगर (ret) अणु
			dev_err(dev, "start timer %p failed failed: %d\n", np,
				ret);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (ret) अणु
		जबतक (i >= 0) अणु
			omap_rproc_stop_समयr(&समयrs[i]);
			i--;
		पूर्ण
		जाओ put_node;
	पूर्ण
	वापस 0;

put_node:
	अगर (configure)
		of_node_put(np);
मुक्त_समयrs:
	जबतक (i--) अणु
		अगर (i >= oproc->num_समयrs)
			मुक्त_irq(समयrs[i].irq, rproc);
		omap_rproc_release_समयr(&समयrs[i]);
		समयrs[i].odt = शून्य;
		समयrs[i].समयr_ops = शून्य;
		समयrs[i].irq = -1;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * omap_rproc_disable_समयrs() - disable the समयrs क्रम a remoteproc
 * @rproc: handle of a remote processor
 * @configure: boolean flag used to release the समयr handle
 *
 * This function is used primarily to disable the समयrs associated with
 * a remoteproc. The configure flag is provided to allow the driver to
 * to either stop and release a समयr (during device shutकरोwn) or to just
 * stop a समयr (during a suspend operation).
 *
 * Return: 0 on success or no समयrs
 */
अटल पूर्णांक omap_rproc_disable_समयrs(काष्ठा rproc *rproc, bool configure)
अणु
	पूर्णांक i;
	काष्ठा omap_rproc *oproc = rproc->priv;
	काष्ठा omap_rproc_समयr *समयrs = oproc->समयrs;
	पूर्णांक num_समयrs = oproc->num_समयrs + oproc->num_wd_समयrs;

	अगर (!num_समयrs)
		वापस 0;

	क्रम (i = 0; i < num_समयrs; i++) अणु
		omap_rproc_stop_समयr(&समयrs[i]);
		अगर (configure) अणु
			अगर (i >= oproc->num_समयrs)
				मुक्त_irq(समयrs[i].irq, rproc);
			omap_rproc_release_समयr(&समयrs[i]);
			समयrs[i].odt = शून्य;
			समयrs[i].समयr_ops = शून्य;
			समयrs[i].irq = -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * omap_rproc_mbox_callback() - inbound mailbox message handler
 * @client: mailbox client poपूर्णांकer used क्रम requesting the mailbox channel
 * @data: mailbox payload
 *
 * This handler is invoked by omap's mailbox driver whenever a mailbox
 * message is received. Usually, the mailbox payload simply contains
 * the index of the virtqueue that is kicked by the remote processor,
 * and we let remoteproc core handle it.
 *
 * In addition to virtqueue indices, we also have some out-of-band values
 * that indicates dअगरferent events. Those values are deliberately very
 * big so they करोn't coincide with virtqueue indices.
 */
अटल व्योम omap_rproc_mbox_callback(काष्ठा mbox_client *client, व्योम *data)
अणु
	काष्ठा omap_rproc *oproc = container_of(client, काष्ठा omap_rproc,
						client);
	काष्ठा device *dev = oproc->rproc->dev.parent;
	स्थिर अक्षर *name = oproc->rproc->name;
	u32 msg = (u32)data;

	dev_dbg(dev, "mbox msg: 0x%x\n", msg);

	चयन (msg) अणु
	हाल RP_MBOX_CRASH:
		/*
		 * remoteproc detected an exception, notअगरy the rproc core.
		 * The remoteproc core will handle the recovery.
		 */
		dev_err(dev, "omap rproc %s crashed\n", name);
		rproc_report_crash(oproc->rproc, RPROC_FATAL_ERROR);
		अवरोध;
	हाल RP_MBOX_ECHO_REPLY:
		dev_info(dev, "received echo reply from %s\n", name);
		अवरोध;
	हाल RP_MBOX_SUSPEND_ACK:
	हाल RP_MBOX_SUSPEND_CANCEL:
		oproc->suspend_acked = msg == RP_MBOX_SUSPEND_ACK;
		complete(&oproc->pm_comp);
		अवरोध;
	शेष:
		अगर (msg >= RP_MBOX_READY && msg < RP_MBOX_END_MSG)
			वापस;
		अगर (msg > oproc->rproc->max_notअगरyid) अणु
			dev_dbg(dev, "dropping unknown message 0x%x", msg);
			वापस;
		पूर्ण
		/* msg contains the index of the triggered vring */
		अगर (rproc_vq_पूर्णांकerrupt(oproc->rproc, msg) == IRQ_NONE)
			dev_dbg(dev, "no message was found in vqid %d\n", msg);
	पूर्ण
पूर्ण

/* kick a virtqueue */
अटल व्योम omap_rproc_kick(काष्ठा rproc *rproc, पूर्णांक vqid)
अणु
	काष्ठा omap_rproc *oproc = rproc->priv;
	काष्ठा device *dev = rproc->dev.parent;
	पूर्णांक ret;

	/* wake up the rproc beक्रमe kicking it */
	ret = pm_runसमय_get_sync(dev);
	अगर (WARN_ON(ret < 0)) अणु
		dev_err(dev, "pm_runtime_get_sync() failed during kick, ret = %d\n",
			ret);
		pm_runसमय_put_noidle(dev);
		वापस;
	पूर्ण

	/* send the index of the triggered virtqueue in the mailbox payload */
	ret = mbox_send_message(oproc->mbox, (व्योम *)vqid);
	अगर (ret < 0)
		dev_err(dev, "failed to send mailbox message, status = %d\n",
			ret);

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);
पूर्ण

/**
 * omap_rproc_ग_लिखो_dsp_boot_addr() - set boot address क्रम DSP remote processor
 * @rproc: handle of a remote processor
 *
 * Set boot address क्रम a supported DSP remote processor.
 *
 * Return: 0 on success, or -EINVAL अगर boot address is not aligned properly
 */
अटल पूर्णांक omap_rproc_ग_लिखो_dsp_boot_addr(काष्ठा rproc *rproc)
अणु
	काष्ठा device *dev = rproc->dev.parent;
	काष्ठा omap_rproc *oproc = rproc->priv;
	काष्ठा omap_rproc_boot_data *bdata = oproc->boot_data;
	u32 offset = bdata->boot_reg;
	u32 value;
	u32 mask;

	अगर (rproc->bootaddr & (SZ_1K - 1)) अणु
		dev_err(dev, "invalid boot address 0x%llx, must be aligned on a 1KB boundary\n",
			rproc->bootaddr);
		वापस -EINVAL;
	पूर्ण

	value = rproc->bootaddr >> bdata->boot_reg_shअगरt;
	mask = ~(SZ_1K - 1) >> bdata->boot_reg_shअगरt;

	वापस regmap_update_bits(bdata->syscon, offset, mask, value);
पूर्ण

/*
 * Power up the remote processor.
 *
 * This function will be invoked only after the firmware क्रम this rproc
 * was loaded, parsed successfully, and all of its resource requirements
 * were met.
 */
अटल पूर्णांक omap_rproc_start(काष्ठा rproc *rproc)
अणु
	काष्ठा omap_rproc *oproc = rproc->priv;
	काष्ठा device *dev = rproc->dev.parent;
	पूर्णांक ret;
	काष्ठा mbox_client *client = &oproc->client;

	अगर (oproc->boot_data) अणु
		ret = omap_rproc_ग_लिखो_dsp_boot_addr(rproc);
		अगर (ret)
			वापस ret;
	पूर्ण

	client->dev = dev;
	client->tx_करोne = शून्य;
	client->rx_callback = omap_rproc_mbox_callback;
	client->tx_block = false;
	client->knows_txकरोne = false;

	oproc->mbox = mbox_request_channel(client, 0);
	अगर (IS_ERR(oproc->mbox)) अणु
		ret = -EBUSY;
		dev_err(dev, "mbox_request_channel failed: %ld\n",
			PTR_ERR(oproc->mbox));
		वापस ret;
	पूर्ण

	/*
	 * Ping the remote processor. this is only क्रम sanity-sake;
	 * there is no functional effect whatsoever.
	 *
	 * Note that the reply will _not_ arrive immediately: this message
	 * will रुको in the mailbox fअगरo until the remote processor is booted.
	 */
	ret = mbox_send_message(oproc->mbox, (व्योम *)RP_MBOX_ECHO_REQUEST);
	अगर (ret < 0) अणु
		dev_err(dev, "mbox_send_message failed: %d\n", ret);
		जाओ put_mbox;
	पूर्ण

	ret = omap_rproc_enable_समयrs(rproc, true);
	अगर (ret) अणु
		dev_err(dev, "omap_rproc_enable_timers failed: %d\n", ret);
		जाओ put_mbox;
	पूर्ण

	ret = reset_control_deनिश्चित(oproc->reset);
	अगर (ret) अणु
		dev_err(dev, "reset control deassert failed: %d\n", ret);
		जाओ disable_समयrs;
	पूर्ण

	/*
	 * remote processor is up, so update the runसमय pm status and
	 * enable the स्वतः-suspend. The device usage count is incremented
	 * manually क्रम balancing it क्रम स्वतः-suspend
	 */
	pm_runसमय_set_active(dev);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_get_noresume(dev);
	pm_runसमय_enable(dev);
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस 0;

disable_समयrs:
	omap_rproc_disable_समयrs(rproc, true);
put_mbox:
	mbox_मुक्त_channel(oproc->mbox);
	वापस ret;
पूर्ण

/* घातer off the remote processor */
अटल पूर्णांक omap_rproc_stop(काष्ठा rproc *rproc)
अणु
	काष्ठा device *dev = rproc->dev.parent;
	काष्ठा omap_rproc *oproc = rproc->priv;
	पूर्णांक ret;

	/*
	 * cancel any possible scheduled runसमय suspend by incrementing
	 * the device usage count, and resuming the device. The remoteproc
	 * also needs to be woken up अगर suspended, to aव्योम the remoteproc
	 * OS to जारी to remember any context that it has saved, and
	 * aव्योम potential issues in misindentअगरying a subsequent device
	 * reboot as a घातer restore boot
	 */
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		वापस ret;
	पूर्ण

	ret = reset_control_निश्चित(oproc->reset);
	अगर (ret)
		जाओ out;

	ret = omap_rproc_disable_समयrs(rproc, true);
	अगर (ret)
		जाओ enable_device;

	mbox_मुक्त_channel(oproc->mbox);

	/*
	 * update the runसमय pm states and status now that the remoteproc
	 * has stopped
	 */
	pm_runसमय_disable(dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(dev);
	pm_runसमय_put_noidle(dev);
	pm_runसमय_set_suspended(dev);

	वापस 0;

enable_device:
	reset_control_deनिश्चित(oproc->reset);
out:
	/* schedule the next स्वतः-suspend */
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);
	वापस ret;
पूर्ण

/**
 * omap_rproc_da_to_va() - पूर्णांकernal memory translation helper
 * @rproc: remote processor to apply the address translation क्रम
 * @da: device address to translate
 * @len: length of the memory buffer
 *
 * Custom function implementing the rproc .da_to_va ops to provide address
 * translation (device address to kernel भव address) क्रम पूर्णांकernal RAMs
 * present in a DSP or IPU device). The translated addresses can be used
 * either by the remoteproc core क्रम loading, or by any rpmsg bus drivers.
 *
 * Return: translated भव address in kernel memory space on success,
 *         or शून्य on failure.
 */
अटल व्योम *omap_rproc_da_to_va(काष्ठा rproc *rproc, u64 da, माप_प्रकार len, bool *is_iomem)
अणु
	काष्ठा omap_rproc *oproc = rproc->priv;
	पूर्णांक i;
	u32 offset;

	अगर (len <= 0)
		वापस शून्य;

	अगर (!oproc->num_mems)
		वापस शून्य;

	क्रम (i = 0; i < oproc->num_mems; i++) अणु
		अगर (da >= oproc->mem[i].dev_addr && da + len <=
		    oproc->mem[i].dev_addr + oproc->mem[i].size) अणु
			offset = da - oproc->mem[i].dev_addr;
			/* __क्रमce to make sparse happy with type conversion */
			वापस (__क्रमce व्योम *)(oproc->mem[i].cpu_addr +
						offset);
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा rproc_ops omap_rproc_ops = अणु
	.start		= omap_rproc_start,
	.stop		= omap_rproc_stop,
	.kick		= omap_rproc_kick,
	.da_to_va	= omap_rproc_da_to_va,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल bool _is_rproc_in_standby(काष्ठा omap_rproc *oproc)
अणु
	वापस ti_clk_is_in_standby(oproc->fck);
पूर्ण

/* 1 sec is दीर्घ enough समय to let the remoteproc side suspend the device */
#घोषणा DEF_SUSPEND_TIMEOUT 1000
अटल पूर्णांक _omap_rproc_suspend(काष्ठा rproc *rproc, bool स्वतः_suspend)
अणु
	काष्ठा device *dev = rproc->dev.parent;
	काष्ठा omap_rproc *oproc = rproc->priv;
	अचिन्हित दीर्घ to = msecs_to_jअगरfies(DEF_SUSPEND_TIMEOUT);
	अचिन्हित दीर्घ ta = jअगरfies + to;
	u32 suspend_msg = स्वतः_suspend ?
				RP_MBOX_SUSPEND_AUTO : RP_MBOX_SUSPEND_SYSTEM;
	पूर्णांक ret;

	reinit_completion(&oproc->pm_comp);
	oproc->suspend_acked = false;
	ret = mbox_send_message(oproc->mbox, (व्योम *)suspend_msg);
	अगर (ret < 0) अणु
		dev_err(dev, "PM mbox_send_message failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = रुको_क्रम_completion_समयout(&oproc->pm_comp, to);
	अगर (!oproc->suspend_acked)
		वापस -EBUSY;

	/*
	 * The remoteproc side is वापसing the ACK message beक्रमe saving the
	 * context, because the context saving is perक्रमmed within a SYS/BIOS
	 * function, and it cannot have any पूर्णांकer-dependencies against the IPC
	 * layer. Also, as the SYS/BIOS needs to preserve properly the processor
	 * रेजिस्टर set, sending this ACK or संकेतling the completion of the
	 * context save through a shared memory variable can never be the
	 * असलolute last thing to be executed on the remoteproc side, and the
	 * MPU cannot use the ACK message as a sync poपूर्णांक to put the remoteproc
	 * पूर्णांकo reset. The only way to ensure that the remote processor has
	 * completed saving the context is to check that the module has reached
	 * STANDBY state (after saving the context, the SYS/BIOS executes the
	 * appropriate target-specअगरic WFI inकाष्ठाion causing the module to
	 * enter STANDBY).
	 */
	जबतक (!_is_rproc_in_standby(oproc)) अणु
		अगर (समय_after(jअगरfies, ta))
			वापस -ETIME;
		schedule();
	पूर्ण

	ret = reset_control_निश्चित(oproc->reset);
	अगर (ret) अणु
		dev_err(dev, "reset assert during suspend failed %d\n", ret);
		वापस ret;
	पूर्ण

	ret = omap_rproc_disable_समयrs(rproc, false);
	अगर (ret) अणु
		dev_err(dev, "disabling timers during suspend failed %d\n",
			ret);
		जाओ enable_device;
	पूर्ण

	/*
	 * IOMMUs would have to be disabled specअगरically क्रम runसमय suspend.
	 * They are handled स्वतःmatically through System PM callbacks क्रम
	 * regular प्रणाली suspend
	 */
	अगर (स्वतः_suspend) अणु
		ret = omap_iommu_करोमुख्य_deactivate(rproc->करोमुख्य);
		अगर (ret) अणु
			dev_err(dev, "iommu domain deactivate failed %d\n",
				ret);
			जाओ enable_समयrs;
		पूर्ण
	पूर्ण

	वापस 0;

enable_समयrs:
	/* ignore errors on re-enabling code */
	omap_rproc_enable_समयrs(rproc, false);
enable_device:
	reset_control_deनिश्चित(oproc->reset);
	वापस ret;
पूर्ण

अटल पूर्णांक _omap_rproc_resume(काष्ठा rproc *rproc, bool स्वतः_suspend)
अणु
	काष्ठा device *dev = rproc->dev.parent;
	काष्ठा omap_rproc *oproc = rproc->priv;
	पूर्णांक ret;

	/*
	 * IOMMUs would have to be enabled specअगरically क्रम runसमय resume.
	 * They would have been alपढ़ोy enabled स्वतःmatically through System
	 * PM callbacks क्रम regular प्रणाली resume
	 */
	अगर (स्वतः_suspend) अणु
		ret = omap_iommu_करोमुख्य_activate(rproc->करोमुख्य);
		अगर (ret) अणु
			dev_err(dev, "omap_iommu activate failed %d\n", ret);
			जाओ out;
		पूर्ण
	पूर्ण

	/* boot address could be lost after suspend, so restore it */
	अगर (oproc->boot_data) अणु
		ret = omap_rproc_ग_लिखो_dsp_boot_addr(rproc);
		अगर (ret) अणु
			dev_err(dev, "boot address restore failed %d\n", ret);
			जाओ suspend_iommu;
		पूर्ण
	पूर्ण

	ret = omap_rproc_enable_समयrs(rproc, false);
	अगर (ret) अणु
		dev_err(dev, "enabling timers during resume failed %d\n", ret);
		जाओ suspend_iommu;
	पूर्ण

	ret = reset_control_deनिश्चित(oproc->reset);
	अगर (ret) अणु
		dev_err(dev, "reset deassert during resume failed %d\n", ret);
		जाओ disable_समयrs;
	पूर्ण

	वापस 0;

disable_समयrs:
	omap_rproc_disable_समयrs(rproc, false);
suspend_iommu:
	अगर (स्वतः_suspend)
		omap_iommu_करोमुख्य_deactivate(rproc->करोमुख्य);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused omap_rproc_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा rproc *rproc = platक्रमm_get_drvdata(pdev);
	काष्ठा omap_rproc *oproc = rproc->priv;
	पूर्णांक ret = 0;

	mutex_lock(&rproc->lock);
	अगर (rproc->state == RPROC_OFFLINE)
		जाओ out;

	अगर (rproc->state == RPROC_SUSPENDED)
		जाओ out;

	अगर (rproc->state != RPROC_RUNNING) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ret = _omap_rproc_suspend(rproc, false);
	अगर (ret) अणु
		dev_err(dev, "suspend failed %d\n", ret);
		जाओ out;
	पूर्ण

	/*
	 * remoteproc is running at the समय of प्रणाली suspend, so remember
	 * it so as to wake it up during प्रणाली resume
	 */
	oproc->need_resume = true;
	rproc->state = RPROC_SUSPENDED;

out:
	mutex_unlock(&rproc->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused omap_rproc_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा rproc *rproc = platक्रमm_get_drvdata(pdev);
	काष्ठा omap_rproc *oproc = rproc->priv;
	पूर्णांक ret = 0;

	mutex_lock(&rproc->lock);
	अगर (rproc->state == RPROC_OFFLINE)
		जाओ out;

	अगर (rproc->state != RPROC_SUSPENDED) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	/*
	 * remoteproc was स्वतः-suspended at the समय of प्रणाली suspend,
	 * so no need to wake-up the processor (leave it in suspended
	 * state, will be woken up during a subsequent runसमय_resume)
	 */
	अगर (!oproc->need_resume)
		जाओ out;

	ret = _omap_rproc_resume(rproc, false);
	अगर (ret) अणु
		dev_err(dev, "resume failed %d\n", ret);
		जाओ out;
	पूर्ण

	oproc->need_resume = false;
	rproc->state = RPROC_RUNNING;

	pm_runसमय_mark_last_busy(dev);
out:
	mutex_unlock(&rproc->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक omap_rproc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा rproc *rproc = dev_get_drvdata(dev);
	काष्ठा omap_rproc *oproc = rproc->priv;
	पूर्णांक ret;

	mutex_lock(&rproc->lock);
	अगर (rproc->state == RPROC_CRASHED) अणु
		dev_dbg(dev, "rproc cannot be runtime suspended when crashed!\n");
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (WARN_ON(rproc->state != RPROC_RUNNING)) अणु
		dev_err(dev, "rproc cannot be runtime suspended when not running!\n");
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	/*
	 * करो not even attempt suspend अगर the remote processor is not
	 * idled क्रम runसमय स्वतः-suspend
	 */
	अगर (!_is_rproc_in_standby(oproc)) अणु
		ret = -EBUSY;
		जाओ पात;
	पूर्ण

	ret = _omap_rproc_suspend(rproc, true);
	अगर (ret)
		जाओ पात;

	rproc->state = RPROC_SUSPENDED;
	mutex_unlock(&rproc->lock);
	वापस 0;

पात:
	pm_runसमय_mark_last_busy(dev);
out:
	mutex_unlock(&rproc->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक omap_rproc_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा rproc *rproc = dev_get_drvdata(dev);
	पूर्णांक ret;

	mutex_lock(&rproc->lock);
	अगर (WARN_ON(rproc->state != RPROC_SUSPENDED)) अणु
		dev_err(dev, "rproc cannot be runtime resumed if not suspended! state=%d\n",
			rproc->state);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ret = _omap_rproc_resume(rproc, true);
	अगर (ret) अणु
		dev_err(dev, "runtime resume failed %d\n", ret);
		जाओ out;
	पूर्ण

	rproc->state = RPROC_RUNNING;
out:
	mutex_unlock(&rproc->lock);
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा omap_rproc_mem_data ipu_mems[] = अणु
	अणु .name = "l2ram", .dev_addr = 0x20000000 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_rproc_mem_data dra7_dsp_mems[] = अणु
	अणु .name = "l2ram", .dev_addr = 0x800000 पूर्ण,
	अणु .name = "l1pram", .dev_addr = 0xe00000 पूर्ण,
	अणु .name = "l1dram", .dev_addr = 0xf00000 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_rproc_dev_data omap4_dsp_dev_data = अणु
	.device_name	= "dsp",
पूर्ण;

अटल स्थिर काष्ठा omap_rproc_dev_data omap4_ipu_dev_data = अणु
	.device_name	= "ipu",
	.mems		= ipu_mems,
पूर्ण;

अटल स्थिर काष्ठा omap_rproc_dev_data omap5_dsp_dev_data = अणु
	.device_name	= "dsp",
पूर्ण;

अटल स्थिर काष्ठा omap_rproc_dev_data omap5_ipu_dev_data = अणु
	.device_name	= "ipu",
	.mems		= ipu_mems,
पूर्ण;

अटल स्थिर काष्ठा omap_rproc_dev_data dra7_dsp_dev_data = अणु
	.device_name	= "dsp",
	.mems		= dra7_dsp_mems,
पूर्ण;

अटल स्थिर काष्ठा omap_rproc_dev_data dra7_ipu_dev_data = अणु
	.device_name	= "ipu",
	.mems		= ipu_mems,
पूर्ण;

अटल स्थिर काष्ठा of_device_id omap_rproc_of_match[] = अणु
	अणु
		.compatible     = "ti,omap4-dsp",
		.data           = &omap4_dsp_dev_data,
	पूर्ण,
	अणु
		.compatible     = "ti,omap4-ipu",
		.data           = &omap4_ipu_dev_data,
	पूर्ण,
	अणु
		.compatible     = "ti,omap5-dsp",
		.data           = &omap5_dsp_dev_data,
	पूर्ण,
	अणु
		.compatible     = "ti,omap5-ipu",
		.data           = &omap5_ipu_dev_data,
	पूर्ण,
	अणु
		.compatible     = "ti,dra7-dsp",
		.data           = &dra7_dsp_dev_data,
	पूर्ण,
	अणु
		.compatible     = "ti,dra7-ipu",
		.data           = &dra7_ipu_dev_data,
	पूर्ण,
	अणु
		/* end */
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_rproc_of_match);

अटल स्थिर अक्षर *omap_rproc_get_firmware(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर अक्षर *fw_name;
	पूर्णांक ret;

	ret = of_property_पढ़ो_string(pdev->dev.of_node, "firmware-name",
				      &fw_name);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस fw_name;
पूर्ण

अटल पूर्णांक omap_rproc_get_boot_data(काष्ठा platक्रमm_device *pdev,
				    काष्ठा rproc *rproc)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा omap_rproc *oproc = rproc->priv;
	स्थिर काष्ठा omap_rproc_dev_data *data;
	पूर्णांक ret;

	data = of_device_get_match_data(&pdev->dev);
	अगर (!data)
		वापस -ENODEV;

	अगर (!of_property_पढ़ो_bool(np, "ti,bootreg"))
		वापस 0;

	oproc->boot_data = devm_kzalloc(&pdev->dev, माप(*oproc->boot_data),
					GFP_KERNEL);
	अगर (!oproc->boot_data)
		वापस -ENOMEM;

	oproc->boot_data->syscon =
			syscon_regmap_lookup_by_phandle(np, "ti,bootreg");
	अगर (IS_ERR(oproc->boot_data->syscon)) अणु
		ret = PTR_ERR(oproc->boot_data->syscon);
		वापस ret;
	पूर्ण

	अगर (of_property_पढ़ो_u32_index(np, "ti,bootreg", 1,
				       &oproc->boot_data->boot_reg)) अणु
		dev_err(&pdev->dev, "couldn't get the boot register\n");
		वापस -EINVAL;
	पूर्ण

	of_property_पढ़ो_u32_index(np, "ti,bootreg", 2,
				   &oproc->boot_data->boot_reg_shअगरt);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_rproc_of_get_पूर्णांकernal_memories(काष्ठा platक्रमm_device *pdev,
					       काष्ठा rproc *rproc)
अणु
	काष्ठा omap_rproc *oproc = rproc->priv;
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा omap_rproc_dev_data *data;
	काष्ठा resource *res;
	पूर्णांक num_mems;
	पूर्णांक i;

	data = of_device_get_match_data(dev);
	अगर (!data)
		वापस -ENODEV;

	अगर (!data->mems)
		वापस 0;

	num_mems = of_property_count_elems_of_size(dev->of_node, "reg",
						   माप(u32)) / 2;

	oproc->mem = devm_kसुस्मृति(dev, num_mems, माप(*oproc->mem),
				  GFP_KERNEL);
	अगर (!oproc->mem)
		वापस -ENOMEM;

	क्रम (i = 0; data->mems[i].name; i++) अणु
		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						   data->mems[i].name);
		अगर (!res) अणु
			dev_err(dev, "no memory defined for %s\n",
				data->mems[i].name);
			वापस -ENOMEM;
		पूर्ण
		oproc->mem[i].cpu_addr = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(oproc->mem[i].cpu_addr)) अणु
			dev_err(dev, "failed to parse and map %s memory\n",
				data->mems[i].name);
			वापस PTR_ERR(oproc->mem[i].cpu_addr);
		पूर्ण
		oproc->mem[i].bus_addr = res->start;
		oproc->mem[i].dev_addr = data->mems[i].dev_addr;
		oproc->mem[i].size = resource_size(res);

		dev_dbg(dev, "memory %8s: bus addr %pa size 0x%x va %pK da 0x%x\n",
			data->mems[i].name, &oproc->mem[i].bus_addr,
			oproc->mem[i].size, oproc->mem[i].cpu_addr,
			oproc->mem[i].dev_addr);
	पूर्ण
	oproc->num_mems = num_mems;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OMAP_REMOTEPROC_WATCHDOG
अटल पूर्णांक omap_rproc_count_wकरोg_समयrs(काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक ret;

	ret = of_count_phandle_with_args(np, "ti,watchdog-timers", शून्य);
	अगर (ret <= 0) अणु
		dev_dbg(dev, "device does not have watchdog timers, status = %d\n",
			ret);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण
#अन्यथा
अटल पूर्णांक omap_rproc_count_wकरोg_समयrs(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक omap_rproc_of_get_समयrs(काष्ठा platक्रमm_device *pdev,
				    काष्ठा rproc *rproc)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा omap_rproc *oproc = rproc->priv;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक num_समयrs;

	/*
	 * Timer nodes are directly used in client nodes as phandles, so
	 * retrieve the count using appropriate size
	 */
	oproc->num_समयrs = of_count_phandle_with_args(np, "ti,timers", शून्य);
	अगर (oproc->num_समयrs <= 0) अणु
		dev_dbg(dev, "device does not have timers, status = %d\n",
			oproc->num_समयrs);
		oproc->num_समयrs = 0;
	पूर्ण

	oproc->num_wd_समयrs = omap_rproc_count_wकरोg_समयrs(dev);

	num_समयrs = oproc->num_समयrs + oproc->num_wd_समयrs;
	अगर (num_समयrs) अणु
		oproc->समयrs = devm_kसुस्मृति(dev, num_समयrs,
					     माप(*oproc->समयrs),
					     GFP_KERNEL);
		अगर (!oproc->समयrs)
			वापस -ENOMEM;

		dev_dbg(dev, "device has %d tick timers and %d watchdog timers\n",
			oproc->num_समयrs, oproc->num_wd_समयrs);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omap_rproc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा omap_rproc *oproc;
	काष्ठा rproc *rproc;
	स्थिर अक्षर *firmware;
	पूर्णांक ret;
	काष्ठा reset_control *reset;

	अगर (!np) अणु
		dev_err(&pdev->dev, "only DT-based devices are supported\n");
		वापस -ENODEV;
	पूर्ण

	reset = devm_reset_control_array_get_exclusive(&pdev->dev);
	अगर (IS_ERR(reset))
		वापस PTR_ERR(reset);

	firmware = omap_rproc_get_firmware(pdev);
	अगर (IS_ERR(firmware))
		वापस PTR_ERR(firmware);

	ret = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_err(&pdev->dev, "dma_set_coherent_mask: %d\n", ret);
		वापस ret;
	पूर्ण

	rproc = rproc_alloc(&pdev->dev, dev_name(&pdev->dev), &omap_rproc_ops,
			    firmware, माप(*oproc));
	अगर (!rproc)
		वापस -ENOMEM;

	oproc = rproc->priv;
	oproc->rproc = rproc;
	oproc->reset = reset;
	/* All existing OMAP IPU and DSP processors have an MMU */
	rproc->has_iommu = true;

	ret = omap_rproc_of_get_पूर्णांकernal_memories(pdev, rproc);
	अगर (ret)
		जाओ मुक्त_rproc;

	ret = omap_rproc_get_boot_data(pdev, rproc);
	अगर (ret)
		जाओ मुक्त_rproc;

	ret = omap_rproc_of_get_समयrs(pdev, rproc);
	अगर (ret)
		जाओ मुक्त_rproc;

	init_completion(&oproc->pm_comp);
	oproc->स्वतःsuspend_delay = DEFAULT_AUTOSUSPEND_DELAY;

	of_property_पढ़ो_u32(pdev->dev.of_node, "ti,autosuspend-delay-ms",
			     &oproc->स्वतःsuspend_delay);

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, oproc->स्वतःsuspend_delay);

	oproc->fck = devm_clk_get(&pdev->dev, 0);
	अगर (IS_ERR(oproc->fck)) अणु
		ret = PTR_ERR(oproc->fck);
		जाओ मुक्त_rproc;
	पूर्ण

	ret = of_reserved_mem_device_init(&pdev->dev);
	अगर (ret) अणु
		dev_warn(&pdev->dev, "device does not have specific CMA pool.\n");
		dev_warn(&pdev->dev, "Typically this should be provided,\n");
		dev_warn(&pdev->dev, "only omit if you know what you are doing.\n");
	पूर्ण

	platक्रमm_set_drvdata(pdev, rproc);

	ret = rproc_add(rproc);
	अगर (ret)
		जाओ release_mem;

	वापस 0;

release_mem:
	of_reserved_mem_device_release(&pdev->dev);
मुक्त_rproc:
	rproc_मुक्त(rproc);
	वापस ret;
पूर्ण

अटल पूर्णांक omap_rproc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rproc *rproc = platक्रमm_get_drvdata(pdev);

	rproc_del(rproc);
	rproc_मुक्त(rproc);
	of_reserved_mem_device_release(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops omap_rproc_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(omap_rproc_suspend, omap_rproc_resume)
	SET_RUNTIME_PM_OPS(omap_rproc_runसमय_suspend,
			   omap_rproc_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver omap_rproc_driver = अणु
	.probe = omap_rproc_probe,
	.हटाओ = omap_rproc_हटाओ,
	.driver = अणु
		.name = "omap-rproc",
		.pm = &omap_rproc_pm_ops,
		.of_match_table = omap_rproc_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(omap_rproc_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("OMAP Remote Processor control driver");
