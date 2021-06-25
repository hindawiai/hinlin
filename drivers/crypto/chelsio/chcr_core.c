<शैली गुरु>
/*
 * This file is part of the Chelsio T4/T5/T6 Ethernet driver क्रम Linux.
 *
 * Copyright (C) 2011-2016 Chelsio Communications.  All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Written and Maपूर्णांकained by:
 * Manoj Malviya (manojmalviya@chelsio.com)
 * Atul Gupta (atul.gupta@chelsio.com)
 * Jitendra Lulla (jlulla@chelsio.com)
 * Yeshaswi M R Gowda (yeshaswi@chelsio.com)
 * Harsh Jain (harsh@chelsio.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>

#समावेश <crypto/aes.h>
#समावेश <crypto/hash.h>

#समावेश "t4_msg.h"
#समावेश "chcr_core.h"
#समावेश "cxgb4_uld.h"

अटल काष्ठा chcr_driver_data drv_data;

प्रकार पूर्णांक (*chcr_handler_func)(काष्ठा adapter *adap, अचिन्हित अक्षर *input);
अटल पूर्णांक cpl_fw6_pld_handler(काष्ठा adapter *adap, अचिन्हित अक्षर *input);
अटल व्योम *chcr_uld_add(स्थिर काष्ठा cxgb4_lld_info *lld);
अटल पूर्णांक chcr_uld_state_change(व्योम *handle, क्रमागत cxgb4_state state);

अटल chcr_handler_func work_handlers[NUM_CPL_CMDS] = अणु
	[CPL_FW6_PLD] = cpl_fw6_pld_handler,
पूर्ण;

अटल काष्ठा cxgb4_uld_info chcr_uld_info = अणु
	.name = DRV_MODULE_NAME,
	.nrxq = MAX_ULD_QSETS,
	/* Max ntxq will be derived from fw config file*/
	.rxq_size = 1024,
	.add = chcr_uld_add,
	.state_change = chcr_uld_state_change,
	.rx_handler = chcr_uld_rx_handler,
पूर्ण;

अटल व्योम detach_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा chcr_dev *dev;

	dev = container_of(work, काष्ठा chcr_dev, detach_work.work);

	अगर (atomic_पढ़ो(&dev->inflight)) अणु
		dev->wqretry--;
		अगर (dev->wqretry) अणु
			pr_debug("Request Inflight Count %d\n",
				atomic_पढ़ो(&dev->inflight));

			schedule_delayed_work(&dev->detach_work, WQ_DETACH_TM);
		पूर्ण अन्यथा अणु
			WARN(1, "CHCR:%d request Still Pending\n",
				atomic_पढ़ो(&dev->inflight));
			complete(&dev->detach_comp);
		पूर्ण
	पूर्ण अन्यथा अणु
		complete(&dev->detach_comp);
	पूर्ण
पूर्ण

काष्ठा uld_ctx *assign_chcr_device(व्योम)
अणु
	काष्ठा uld_ctx *u_ctx = शून्य;

	/*
	 * When multiple devices are present in प्रणाली select
	 * device in round-robin fashion क्रम crypto operations
	 * Although One session must use the same device to
	 * मुख्यtain request-response ordering.
	 */
	mutex_lock(&drv_data.drv_mutex);
	अगर (!list_empty(&drv_data.act_dev)) अणु
		u_ctx = drv_data.last_dev;
		अगर (list_is_last(&drv_data.last_dev->entry, &drv_data.act_dev))
			drv_data.last_dev = list_first_entry(&drv_data.act_dev,
						  काष्ठा uld_ctx, entry);
		अन्यथा
			drv_data.last_dev =
				list_next_entry(drv_data.last_dev, entry);
	पूर्ण
	mutex_unlock(&drv_data.drv_mutex);
	वापस u_ctx;
पूर्ण

अटल व्योम chcr_dev_add(काष्ठा uld_ctx *u_ctx)
अणु
	काष्ठा chcr_dev *dev;

	dev = &u_ctx->dev;
	dev->state = CHCR_ATTACH;
	atomic_set(&dev->inflight, 0);
	mutex_lock(&drv_data.drv_mutex);
	list_move(&u_ctx->entry, &drv_data.act_dev);
	अगर (!drv_data.last_dev)
		drv_data.last_dev = u_ctx;
	mutex_unlock(&drv_data.drv_mutex);
पूर्ण

अटल व्योम chcr_dev_init(काष्ठा uld_ctx *u_ctx)
अणु
	काष्ठा chcr_dev *dev;

	dev = &u_ctx->dev;
	spin_lock_init(&dev->lock_chcr_dev);
	INIT_DELAYED_WORK(&dev->detach_work, detach_work_fn);
	init_completion(&dev->detach_comp);
	dev->state = CHCR_INIT;
	dev->wqretry = WQ_RETRY;
	atomic_inc(&drv_data.dev_count);
	atomic_set(&dev->inflight, 0);
	mutex_lock(&drv_data.drv_mutex);
	list_add_tail(&u_ctx->entry, &drv_data.inact_dev);
	mutex_unlock(&drv_data.drv_mutex);
पूर्ण

अटल पूर्णांक chcr_dev_move(काष्ठा uld_ctx *u_ctx)
अणु
	mutex_lock(&drv_data.drv_mutex);
	अगर (drv_data.last_dev == u_ctx) अणु
		अगर (list_is_last(&drv_data.last_dev->entry, &drv_data.act_dev))
			drv_data.last_dev = list_first_entry(&drv_data.act_dev,
						  काष्ठा uld_ctx, entry);
		अन्यथा
			drv_data.last_dev =
				list_next_entry(drv_data.last_dev, entry);
	पूर्ण
	list_move(&u_ctx->entry, &drv_data.inact_dev);
	अगर (list_empty(&drv_data.act_dev))
		drv_data.last_dev = शून्य;
	atomic_dec(&drv_data.dev_count);
	mutex_unlock(&drv_data.drv_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक cpl_fw6_pld_handler(काष्ठा adapter *adap,
			       अचिन्हित अक्षर *input)
अणु
	काष्ठा crypto_async_request *req;
	काष्ठा cpl_fw6_pld *fw6_pld;
	u32 ack_err_status = 0;
	पूर्णांक error_status = 0;

	fw6_pld = (काष्ठा cpl_fw6_pld *)input;
	req = (काष्ठा crypto_async_request *)(uपूर्णांकptr_t)be64_to_cpu(
						    fw6_pld->data[1]);

	ack_err_status =
		ntohl(*(__be32 *)((अचिन्हित अक्षर *)&fw6_pld->data[0] + 4));
	अगर (CHK_MAC_ERR_BIT(ack_err_status) || CHK_PAD_ERR_BIT(ack_err_status))
		error_status = -EBADMSG;
	/* call completion callback with failure status */
	अगर (req) अणु
		error_status = chcr_handle_resp(req, input, error_status);
	पूर्ण अन्यथा अणु
		pr_err("Incorrect request address from the firmware\n");
		वापस -EFAULT;
	पूर्ण
	अगर (error_status)
		atomic_inc(&adap->chcr_stats.error);

	वापस 0;
पूर्ण

पूर्णांक chcr_send_wr(काष्ठा sk_buff *skb)
अणु
	वापस cxgb4_crypto_send(skb->dev, skb);
पूर्ण

अटल व्योम *chcr_uld_add(स्थिर काष्ठा cxgb4_lld_info *lld)
अणु
	काष्ठा uld_ctx *u_ctx;

	/* Create the device and add it in the device list */
	pr_info_once("%s\n", DRV_DESC);
	अगर (!(lld->ulp_crypto & ULP_CRYPTO_LOOKASIDE))
		वापस ERR_PTR(-EOPNOTSUPP);

	/* Create the device and add it in the device list */
	u_ctx = kzalloc(माप(*u_ctx), GFP_KERNEL);
	अगर (!u_ctx) अणु
		u_ctx = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण
	u_ctx->lldi = *lld;
	chcr_dev_init(u_ctx);
out:
	वापस u_ctx;
पूर्ण

पूर्णांक chcr_uld_rx_handler(व्योम *handle, स्थिर __be64 *rsp,
			स्थिर काष्ठा pkt_gl *pgl)
अणु
	काष्ठा uld_ctx *u_ctx = (काष्ठा uld_ctx *)handle;
	काष्ठा chcr_dev *dev = &u_ctx->dev;
	काष्ठा adapter *adap = padap(dev);
	स्थिर काष्ठा cpl_fw6_pld *rpl = (काष्ठा cpl_fw6_pld *)rsp;

	अगर (!work_handlers[rpl->opcode]) अणु
		pr_err("Unsupported opcode %d received\n", rpl->opcode);
		वापस 0;
	पूर्ण

	अगर (!pgl)
		work_handlers[rpl->opcode](adap, (अचिन्हित अक्षर *)&rsp[1]);
	अन्यथा
		work_handlers[rpl->opcode](adap, pgl->va);
	वापस 0;
पूर्ण

अटल व्योम chcr_detach_device(काष्ठा uld_ctx *u_ctx)
अणु
	काष्ठा chcr_dev *dev = &u_ctx->dev;

	अगर (dev->state == CHCR_DETACH) अणु
		pr_debug("Detached Event received for already detach device\n");
		वापस;
	पूर्ण
	dev->state = CHCR_DETACH;
	अगर (atomic_पढ़ो(&dev->inflight) != 0) अणु
		schedule_delayed_work(&dev->detach_work, WQ_DETACH_TM);
		रुको_क्रम_completion(&dev->detach_comp);
	पूर्ण

	// Move u_ctx to inactive_dev list
	chcr_dev_move(u_ctx);
पूर्ण

अटल पूर्णांक chcr_uld_state_change(व्योम *handle, क्रमागत cxgb4_state state)
अणु
	काष्ठा uld_ctx *u_ctx = handle;
	पूर्णांक ret = 0;

	चयन (state) अणु
	हाल CXGB4_STATE_UP:
		अगर (u_ctx->dev.state != CHCR_INIT) अणु
			// ALपढ़ोy Initialised.
			वापस 0;
		पूर्ण
		chcr_dev_add(u_ctx);
		ret = start_crypto();
		अवरोध;

	हाल CXGB4_STATE_DETACH:
		chcr_detach_device(u_ctx);
		अगर (!atomic_पढ़ो(&drv_data.dev_count))
			stop_crypto();
		अवरोध;

	हाल CXGB4_STATE_START_RECOVERY:
	हाल CXGB4_STATE_DOWN:
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक __init chcr_crypto_init(व्योम)
अणु
	INIT_LIST_HEAD(&drv_data.act_dev);
	INIT_LIST_HEAD(&drv_data.inact_dev);
	atomic_set(&drv_data.dev_count, 0);
	mutex_init(&drv_data.drv_mutex);
	drv_data.last_dev = शून्य;
	cxgb4_रेजिस्टर_uld(CXGB4_ULD_CRYPTO, &chcr_uld_info);

	वापस 0;
पूर्ण

अटल व्योम __निकास chcr_crypto_निकास(व्योम)
अणु
	काष्ठा uld_ctx *u_ctx, *पंचांगp;
	काष्ठा adapter *adap;

	stop_crypto();
	cxgb4_unरेजिस्टर_uld(CXGB4_ULD_CRYPTO);
	/* Remove all devices from list */
	mutex_lock(&drv_data.drv_mutex);
	list_क्रम_each_entry_safe(u_ctx, पंचांगp, &drv_data.act_dev, entry) अणु
		adap = padap(&u_ctx->dev);
		स_रखो(&adap->chcr_stats, 0, माप(adap->chcr_stats));
		list_del(&u_ctx->entry);
		kमुक्त(u_ctx);
	पूर्ण
	list_क्रम_each_entry_safe(u_ctx, पंचांगp, &drv_data.inact_dev, entry) अणु
		adap = padap(&u_ctx->dev);
		स_रखो(&adap->chcr_stats, 0, माप(adap->chcr_stats));
		list_del(&u_ctx->entry);
		kमुक्त(u_ctx);
	पूर्ण
	mutex_unlock(&drv_data.drv_mutex);
पूर्ण

module_init(chcr_crypto_init);
module_निकास(chcr_crypto_निकास);

MODULE_DESCRIPTION("Crypto Co-processor for Chelsio Terminator cards.");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chelsio Communications");
