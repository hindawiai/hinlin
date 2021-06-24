<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018-2020, The Linux Foundation. All rights reserved.
 *
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-direction.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/mhi.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश "internal.h"

पूर्णांक __must_check mhi_पढ़ो_reg(काष्ठा mhi_controller *mhi_cntrl,
			      व्योम __iomem *base, u32 offset, u32 *out)
अणु
	वापस mhi_cntrl->पढ़ो_reg(mhi_cntrl, base + offset, out);
पूर्ण

पूर्णांक __must_check mhi_पढ़ो_reg_field(काष्ठा mhi_controller *mhi_cntrl,
				    व्योम __iomem *base, u32 offset,
				    u32 mask, u32 shअगरt, u32 *out)
अणु
	u32 पंचांगp;
	पूर्णांक ret;

	ret = mhi_पढ़ो_reg(mhi_cntrl, base, offset, &पंचांगp);
	अगर (ret)
		वापस ret;

	*out = (पंचांगp & mask) >> shअगरt;

	वापस 0;
पूर्ण

पूर्णांक __must_check mhi_poll_reg_field(काष्ठा mhi_controller *mhi_cntrl,
				    व्योम __iomem *base, u32 offset,
				    u32 mask, u32 shअगरt, u32 val, u32 delayus)
अणु
	पूर्णांक ret;
	u32 out, retry = (mhi_cntrl->समयout_ms * 1000) / delayus;

	जबतक (retry--) अणु
		ret = mhi_पढ़ो_reg_field(mhi_cntrl, base, offset, mask, shअगरt,
					 &out);
		अगर (ret)
			वापस ret;

		अगर (out == val)
			वापस 0;

		fsleep(delayus);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

व्योम mhi_ग_लिखो_reg(काष्ठा mhi_controller *mhi_cntrl, व्योम __iomem *base,
		   u32 offset, u32 val)
अणु
	mhi_cntrl->ग_लिखो_reg(mhi_cntrl, base + offset, val);
पूर्ण

व्योम mhi_ग_लिखो_reg_field(काष्ठा mhi_controller *mhi_cntrl, व्योम __iomem *base,
			 u32 offset, u32 mask, u32 shअगरt, u32 val)
अणु
	पूर्णांक ret;
	u32 पंचांगp;

	ret = mhi_पढ़ो_reg(mhi_cntrl, base, offset, &पंचांगp);
	अगर (ret)
		वापस;

	पंचांगp &= ~mask;
	पंचांगp |= (val << shअगरt);
	mhi_ग_लिखो_reg(mhi_cntrl, base, offset, पंचांगp);
पूर्ण

व्योम mhi_ग_लिखो_db(काष्ठा mhi_controller *mhi_cntrl, व्योम __iomem *db_addr,
		  dma_addr_t db_val)
अणु
	mhi_ग_लिखो_reg(mhi_cntrl, db_addr, 4, upper_32_bits(db_val));
	mhi_ग_लिखो_reg(mhi_cntrl, db_addr, 0, lower_32_bits(db_val));
पूर्ण

व्योम mhi_db_brsपंचांगode(काष्ठा mhi_controller *mhi_cntrl,
		     काष्ठा db_cfg *db_cfg,
		     व्योम __iomem *db_addr,
		     dma_addr_t db_val)
अणु
	अगर (db_cfg->db_mode) अणु
		db_cfg->db_val = db_val;
		mhi_ग_लिखो_db(mhi_cntrl, db_addr, db_val);
		db_cfg->db_mode = 0;
	पूर्ण
पूर्ण

व्योम mhi_db_brsपंचांगode_disable(काष्ठा mhi_controller *mhi_cntrl,
			     काष्ठा db_cfg *db_cfg,
			     व्योम __iomem *db_addr,
			     dma_addr_t db_val)
अणु
	db_cfg->db_val = db_val;
	mhi_ग_लिखो_db(mhi_cntrl, db_addr, db_val);
पूर्ण

व्योम mhi_ring_er_db(काष्ठा mhi_event *mhi_event)
अणु
	काष्ठा mhi_ring *ring = &mhi_event->ring;

	mhi_event->db_cfg.process_db(mhi_event->mhi_cntrl, &mhi_event->db_cfg,
				     ring->db_addr, *ring->ctxt_wp);
पूर्ण

व्योम mhi_ring_cmd_db(काष्ठा mhi_controller *mhi_cntrl, काष्ठा mhi_cmd *mhi_cmd)
अणु
	dma_addr_t db;
	काष्ठा mhi_ring *ring = &mhi_cmd->ring;

	db = ring->iommu_base + (ring->wp - ring->base);
	*ring->ctxt_wp = db;
	mhi_ग_लिखो_db(mhi_cntrl, ring->db_addr, db);
पूर्ण

व्योम mhi_ring_chan_db(काष्ठा mhi_controller *mhi_cntrl,
		      काष्ठा mhi_chan *mhi_chan)
अणु
	काष्ठा mhi_ring *ring = &mhi_chan->tre_ring;
	dma_addr_t db;

	db = ring->iommu_base + (ring->wp - ring->base);

	/*
	 * Writes to the new ring element must be visible to the hardware
	 * beक्रमe letting h/w know there is new element to fetch.
	 */
	dma_wmb();
	*ring->ctxt_wp = db;

	mhi_chan->db_cfg.process_db(mhi_cntrl, &mhi_chan->db_cfg,
				    ring->db_addr, db);
पूर्ण

क्रमागत mhi_ee_type mhi_get_exec_env(काष्ठा mhi_controller *mhi_cntrl)
अणु
	u32 exec;
	पूर्णांक ret = mhi_पढ़ो_reg(mhi_cntrl, mhi_cntrl->bhi, BHI_EXECENV, &exec);

	वापस (ret) ? MHI_EE_MAX : exec;
पूर्ण
EXPORT_SYMBOL_GPL(mhi_get_exec_env);

क्रमागत mhi_state mhi_get_mhi_state(काष्ठा mhi_controller *mhi_cntrl)
अणु
	u32 state;
	पूर्णांक ret = mhi_पढ़ो_reg_field(mhi_cntrl, mhi_cntrl->regs, MHISTATUS,
				     MHISTATUS_MHISTATE_MASK,
				     MHISTATUS_MHISTATE_SHIFT, &state);
	वापस ret ? MHI_STATE_MAX : state;
पूर्ण
EXPORT_SYMBOL_GPL(mhi_get_mhi_state);

व्योम mhi_soc_reset(काष्ठा mhi_controller *mhi_cntrl)
अणु
	अगर (mhi_cntrl->reset) अणु
		mhi_cntrl->reset(mhi_cntrl);
		वापस;
	पूर्ण

	/* Generic MHI SoC reset */
	mhi_ग_लिखो_reg(mhi_cntrl, mhi_cntrl->regs, MHI_SOC_RESET_REQ_OFFSET,
		      MHI_SOC_RESET_REQ);
पूर्ण
EXPORT_SYMBOL_GPL(mhi_soc_reset);

पूर्णांक mhi_map_single_no_bb(काष्ठा mhi_controller *mhi_cntrl,
			 काष्ठा mhi_buf_info *buf_info)
अणु
	buf_info->p_addr = dma_map_single(mhi_cntrl->cntrl_dev,
					  buf_info->v_addr, buf_info->len,
					  buf_info->dir);
	अगर (dma_mapping_error(mhi_cntrl->cntrl_dev, buf_info->p_addr))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

पूर्णांक mhi_map_single_use_bb(काष्ठा mhi_controller *mhi_cntrl,
			  काष्ठा mhi_buf_info *buf_info)
अणु
	व्योम *buf = mhi_alloc_coherent(mhi_cntrl, buf_info->len,
				       &buf_info->p_addr, GFP_ATOMIC);

	अगर (!buf)
		वापस -ENOMEM;

	अगर (buf_info->dir == DMA_TO_DEVICE)
		स_नकल(buf, buf_info->v_addr, buf_info->len);

	buf_info->bb_addr = buf;

	वापस 0;
पूर्ण

व्योम mhi_unmap_single_no_bb(काष्ठा mhi_controller *mhi_cntrl,
			    काष्ठा mhi_buf_info *buf_info)
अणु
	dma_unmap_single(mhi_cntrl->cntrl_dev, buf_info->p_addr, buf_info->len,
			 buf_info->dir);
पूर्ण

व्योम mhi_unmap_single_use_bb(काष्ठा mhi_controller *mhi_cntrl,
			     काष्ठा mhi_buf_info *buf_info)
अणु
	अगर (buf_info->dir == DMA_FROM_DEVICE)
		स_नकल(buf_info->v_addr, buf_info->bb_addr, buf_info->len);

	mhi_मुक्त_coherent(mhi_cntrl, buf_info->len, buf_info->bb_addr,
			  buf_info->p_addr);
पूर्ण

अटल पूर्णांक get_nr_avail_ring_elements(काष्ठा mhi_controller *mhi_cntrl,
				      काष्ठा mhi_ring *ring)
अणु
	पूर्णांक nr_el;

	अगर (ring->wp < ring->rp) अणु
		nr_el = ((ring->rp - ring->wp) / ring->el_size) - 1;
	पूर्ण अन्यथा अणु
		nr_el = (ring->rp - ring->base) / ring->el_size;
		nr_el += ((ring->base + ring->len - ring->wp) /
			  ring->el_size) - 1;
	पूर्ण

	वापस nr_el;
पूर्ण

अटल व्योम *mhi_to_भव(काष्ठा mhi_ring *ring, dma_addr_t addr)
अणु
	वापस (addr - ring->iommu_base) + ring->base;
पूर्ण

अटल व्योम mhi_add_ring_element(काष्ठा mhi_controller *mhi_cntrl,
				 काष्ठा mhi_ring *ring)
अणु
	ring->wp += ring->el_size;
	अगर (ring->wp >= (ring->base + ring->len))
		ring->wp = ring->base;
	/* smp update */
	smp_wmb();
पूर्ण

अटल व्योम mhi_del_ring_element(काष्ठा mhi_controller *mhi_cntrl,
				 काष्ठा mhi_ring *ring)
अणु
	ring->rp += ring->el_size;
	अगर (ring->rp >= (ring->base + ring->len))
		ring->rp = ring->base;
	/* smp update */
	smp_wmb();
पूर्ण

अटल bool is_valid_ring_ptr(काष्ठा mhi_ring *ring, dma_addr_t addr)
अणु
	वापस addr >= ring->iommu_base && addr < ring->iommu_base + ring->len;
पूर्ण

पूर्णांक mhi_destroy_device(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा mhi_chan *ul_chan, *dl_chan;
	काष्ठा mhi_device *mhi_dev;
	काष्ठा mhi_controller *mhi_cntrl;
	क्रमागत mhi_ee_type ee = MHI_EE_MAX;

	अगर (dev->bus != &mhi_bus_type)
		वापस 0;

	mhi_dev = to_mhi_device(dev);
	mhi_cntrl = mhi_dev->mhi_cntrl;

	/* Only destroy भव devices thats attached to bus */
	अगर (mhi_dev->dev_type == MHI_DEVICE_CONTROLLER)
		वापस 0;

	ul_chan = mhi_dev->ul_chan;
	dl_chan = mhi_dev->dl_chan;

	/*
	 * If execution environment is specअगरied, हटाओ only those devices that
	 * started in them based on ee_mask क्रम the channels as we move on to a
	 * dअगरferent execution environment
	 */
	अगर (data)
		ee = *(क्रमागत mhi_ee_type *)data;

	/*
	 * For the suspend and resume हाल, this function will get called
	 * without mhi_unरेजिस्टर_controller(). Hence, we need to drop the
	 * references to mhi_dev created क्रम ul and dl channels. We can
	 * be sure that there will be no instances of mhi_dev left after
	 * this.
	 */
	अगर (ul_chan) अणु
		अगर (ee != MHI_EE_MAX && !(ul_chan->ee_mask & BIT(ee)))
			वापस 0;

		put_device(&ul_chan->mhi_dev->dev);
	पूर्ण

	अगर (dl_chan) अणु
		अगर (ee != MHI_EE_MAX && !(dl_chan->ee_mask & BIT(ee)))
			वापस 0;

		put_device(&dl_chan->mhi_dev->dev);
	पूर्ण

	dev_dbg(&mhi_cntrl->mhi_dev->dev, "destroy device for chan:%s\n",
		 mhi_dev->name);

	/* Notअगरy the client and हटाओ the device from MHI bus */
	device_del(dev);
	put_device(dev);

	वापस 0;
पूर्ण

पूर्णांक mhi_get_मुक्त_desc_count(काष्ठा mhi_device *mhi_dev,
				क्रमागत dma_data_direction dir)
अणु
	काष्ठा mhi_controller *mhi_cntrl = mhi_dev->mhi_cntrl;
	काष्ठा mhi_chan *mhi_chan = (dir == DMA_TO_DEVICE) ?
		mhi_dev->ul_chan : mhi_dev->dl_chan;
	काष्ठा mhi_ring *tre_ring = &mhi_chan->tre_ring;

	वापस get_nr_avail_ring_elements(mhi_cntrl, tre_ring);
पूर्ण
EXPORT_SYMBOL_GPL(mhi_get_मुक्त_desc_count);

व्योम mhi_notअगरy(काष्ठा mhi_device *mhi_dev, क्रमागत mhi_callback cb_reason)
अणु
	काष्ठा mhi_driver *mhi_drv;

	अगर (!mhi_dev->dev.driver)
		वापस;

	mhi_drv = to_mhi_driver(mhi_dev->dev.driver);

	अगर (mhi_drv->status_cb)
		mhi_drv->status_cb(mhi_dev, cb_reason);
पूर्ण
EXPORT_SYMBOL_GPL(mhi_notअगरy);

/* Bind MHI channels to MHI devices */
व्योम mhi_create_devices(काष्ठा mhi_controller *mhi_cntrl)
अणु
	काष्ठा mhi_chan *mhi_chan;
	काष्ठा mhi_device *mhi_dev;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;
	पूर्णांक i, ret;

	mhi_chan = mhi_cntrl->mhi_chan;
	क्रम (i = 0; i < mhi_cntrl->max_chan; i++, mhi_chan++) अणु
		अगर (!mhi_chan->configured || mhi_chan->mhi_dev ||
		    !(mhi_chan->ee_mask & BIT(mhi_cntrl->ee)))
			जारी;
		mhi_dev = mhi_alloc_device(mhi_cntrl);
		अगर (IS_ERR(mhi_dev))
			वापस;

		mhi_dev->dev_type = MHI_DEVICE_XFER;
		चयन (mhi_chan->dir) अणु
		हाल DMA_TO_DEVICE:
			mhi_dev->ul_chan = mhi_chan;
			mhi_dev->ul_chan_id = mhi_chan->chan;
			अवरोध;
		हाल DMA_FROM_DEVICE:
			/* We use dl_chan as offload channels */
			mhi_dev->dl_chan = mhi_chan;
			mhi_dev->dl_chan_id = mhi_chan->chan;
			अवरोध;
		शेष:
			dev_err(dev, "Direction not supported\n");
			put_device(&mhi_dev->dev);
			वापस;
		पूर्ण

		get_device(&mhi_dev->dev);
		mhi_chan->mhi_dev = mhi_dev;

		/* Check next channel अगर it matches */
		अगर ((i + 1) < mhi_cntrl->max_chan && mhi_chan[1].configured) अणु
			अगर (!म_भेद(mhi_chan[1].name, mhi_chan->name)) अणु
				i++;
				mhi_chan++;
				अगर (mhi_chan->dir == DMA_TO_DEVICE) अणु
					mhi_dev->ul_chan = mhi_chan;
					mhi_dev->ul_chan_id = mhi_chan->chan;
				पूर्ण अन्यथा अणु
					mhi_dev->dl_chan = mhi_chan;
					mhi_dev->dl_chan_id = mhi_chan->chan;
				पूर्ण
				get_device(&mhi_dev->dev);
				mhi_chan->mhi_dev = mhi_dev;
			पूर्ण
		पूर्ण

		/* Channel name is same क्रम both UL and DL */
		mhi_dev->name = mhi_chan->name;
		dev_set_name(&mhi_dev->dev, "%s_%s",
			     dev_name(&mhi_cntrl->mhi_dev->dev),
			     mhi_dev->name);

		/* Init wakeup source अगर available */
		अगर (mhi_dev->dl_chan && mhi_dev->dl_chan->wake_capable)
			device_init_wakeup(&mhi_dev->dev, true);

		ret = device_add(&mhi_dev->dev);
		अगर (ret)
			put_device(&mhi_dev->dev);
	पूर्ण
पूर्ण

irqवापस_t mhi_irq_handler(पूर्णांक irq_number, व्योम *dev)
अणु
	काष्ठा mhi_event *mhi_event = dev;
	काष्ठा mhi_controller *mhi_cntrl = mhi_event->mhi_cntrl;
	काष्ठा mhi_event_ctxt *er_ctxt =
		&mhi_cntrl->mhi_ctxt->er_ctxt[mhi_event->er_index];
	काष्ठा mhi_ring *ev_ring = &mhi_event->ring;
	dma_addr_t ptr = er_ctxt->rp;
	व्योम *dev_rp;

	अगर (!is_valid_ring_ptr(ev_ring, ptr)) अणु
		dev_err(&mhi_cntrl->mhi_dev->dev,
			"Event ring rp points outside of the event ring\n");
		वापस IRQ_HANDLED;
	पूर्ण

	dev_rp = mhi_to_भव(ev_ring, ptr);

	/* Only proceed अगर event ring has pending events */
	अगर (ev_ring->rp == dev_rp)
		वापस IRQ_HANDLED;

	/* For client managed event ring, notअगरy pending data */
	अगर (mhi_event->cl_manage) अणु
		काष्ठा mhi_chan *mhi_chan = mhi_event->mhi_chan;
		काष्ठा mhi_device *mhi_dev = mhi_chan->mhi_dev;

		अगर (mhi_dev)
			mhi_notअगरy(mhi_dev, MHI_CB_PENDING_DATA);
	पूर्ण अन्यथा अणु
		tasklet_schedule(&mhi_event->task);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

irqवापस_t mhi_पूर्णांकvec_thपढ़ोed_handler(पूर्णांक irq_number, व्योम *priv)
अणु
	काष्ठा mhi_controller *mhi_cntrl = priv;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;
	क्रमागत mhi_state state;
	क्रमागत mhi_pm_state pm_state = 0;
	क्रमागत mhi_ee_type ee;

	ग_लिखो_lock_irq(&mhi_cntrl->pm_lock);
	अगर (!MHI_REG_ACCESS_VALID(mhi_cntrl->pm_state)) अणु
		ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);
		जाओ निकास_पूर्णांकvec;
	पूर्ण

	state = mhi_get_mhi_state(mhi_cntrl);
	ee = mhi_get_exec_env(mhi_cntrl);
	dev_dbg(dev, "local ee: %s state: %s device ee: %s state: %s\n",
		TO_MHI_EXEC_STR(mhi_cntrl->ee),
		TO_MHI_STATE_STR(mhi_cntrl->dev_state),
		TO_MHI_EXEC_STR(ee), TO_MHI_STATE_STR(state));

	अगर (state == MHI_STATE_SYS_ERR) अणु
		dev_dbg(dev, "System error detected\n");
		pm_state = mhi_tryset_pm_state(mhi_cntrl,
					       MHI_PM_SYS_ERR_DETECT);
	पूर्ण
	ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);

	अगर (pm_state != MHI_PM_SYS_ERR_DETECT || ee == mhi_cntrl->ee)
		जाओ निकास_पूर्णांकvec;

	चयन (ee) अणु
	हाल MHI_EE_RDDM:
		/* proceed अगर घातer करोwn is not alपढ़ोy in progress */
		अगर (mhi_cntrl->rddm_image && mhi_is_active(mhi_cntrl)) अणु
			mhi_cntrl->status_cb(mhi_cntrl, MHI_CB_EE_RDDM);
			mhi_cntrl->ee = ee;
			wake_up_all(&mhi_cntrl->state_event);
		पूर्ण
		अवरोध;
	हाल MHI_EE_PBL:
	हाल MHI_EE_EDL:
	हाल MHI_EE_PTHRU:
		mhi_cntrl->status_cb(mhi_cntrl, MHI_CB_FATAL_ERROR);
		mhi_cntrl->ee = ee;
		wake_up_all(&mhi_cntrl->state_event);
		mhi_pm_sys_err_handler(mhi_cntrl);
		अवरोध;
	शेष:
		wake_up_all(&mhi_cntrl->state_event);
		mhi_pm_sys_err_handler(mhi_cntrl);
		अवरोध;
	पूर्ण

निकास_पूर्णांकvec:

	वापस IRQ_HANDLED;
पूर्ण

irqवापस_t mhi_पूर्णांकvec_handler(पूर्णांक irq_number, व्योम *dev)
अणु
	काष्ठा mhi_controller *mhi_cntrl = dev;

	/* Wake up events रुकोing क्रम state change */
	wake_up_all(&mhi_cntrl->state_event);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल व्योम mhi_recycle_ev_ring_element(काष्ठा mhi_controller *mhi_cntrl,
					काष्ठा mhi_ring *ring)
अणु
	dma_addr_t ctxt_wp;

	/* Update the WP */
	ring->wp += ring->el_size;
	ctxt_wp = *ring->ctxt_wp + ring->el_size;

	अगर (ring->wp >= (ring->base + ring->len)) अणु
		ring->wp = ring->base;
		ctxt_wp = ring->iommu_base;
	पूर्ण

	*ring->ctxt_wp = ctxt_wp;

	/* Update the RP */
	ring->rp += ring->el_size;
	अगर (ring->rp >= (ring->base + ring->len))
		ring->rp = ring->base;

	/* Update to all cores */
	smp_wmb();
पूर्ण

अटल पूर्णांक parse_xfer_event(काष्ठा mhi_controller *mhi_cntrl,
			    काष्ठा mhi_tre *event,
			    काष्ठा mhi_chan *mhi_chan)
अणु
	काष्ठा mhi_ring *buf_ring, *tre_ring;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;
	काष्ठा mhi_result result;
	अचिन्हित दीर्घ flags = 0;
	u32 ev_code;

	ev_code = MHI_TRE_GET_EV_CODE(event);
	buf_ring = &mhi_chan->buf_ring;
	tre_ring = &mhi_chan->tre_ring;

	result.transaction_status = (ev_code == MHI_EV_CC_OVERFLOW) ?
		-EOVERFLOW : 0;

	/*
	 * If it's a DB Event then we need to grab the lock
	 * with preemption disabled and as a ग_लिखो because we
	 * have to update db रेजिस्टर and there are chances that
	 * another thपढ़ो could be करोing the same.
	 */
	अगर (ev_code >= MHI_EV_CC_OOB)
		ग_लिखो_lock_irqsave(&mhi_chan->lock, flags);
	अन्यथा
		पढ़ो_lock_bh(&mhi_chan->lock);

	अगर (mhi_chan->ch_state != MHI_CH_STATE_ENABLED)
		जाओ end_process_tx_event;

	चयन (ev_code) अणु
	हाल MHI_EV_CC_OVERFLOW:
	हाल MHI_EV_CC_EOB:
	हाल MHI_EV_CC_EOT:
	अणु
		dma_addr_t ptr = MHI_TRE_GET_EV_PTR(event);
		काष्ठा mhi_tre *local_rp, *ev_tre;
		व्योम *dev_rp;
		काष्ठा mhi_buf_info *buf_info;
		u16 xfer_len;

		अगर (!is_valid_ring_ptr(tre_ring, ptr)) अणु
			dev_err(&mhi_cntrl->mhi_dev->dev,
				"Event element points outside of the tre ring\n");
			अवरोध;
		पूर्ण
		/* Get the TRB this event poपूर्णांकs to */
		ev_tre = mhi_to_भव(tre_ring, ptr);

		dev_rp = ev_tre + 1;
		अगर (dev_rp >= (tre_ring->base + tre_ring->len))
			dev_rp = tre_ring->base;

		result.dir = mhi_chan->dir;

		local_rp = tre_ring->rp;
		जबतक (local_rp != dev_rp) अणु
			buf_info = buf_ring->rp;
			/* If it's the last TRE, get length from the event */
			अगर (local_rp == ev_tre)
				xfer_len = MHI_TRE_GET_EV_LEN(event);
			अन्यथा
				xfer_len = buf_info->len;

			/* Unmap अगर it's not pre-mapped by client */
			अगर (likely(!buf_info->pre_mapped))
				mhi_cntrl->unmap_single(mhi_cntrl, buf_info);

			result.buf_addr = buf_info->cb_buf;

			/* truncate to buf len अगर xfer_len is larger */
			result.bytes_xferd =
				min_t(u16, xfer_len, buf_info->len);
			mhi_del_ring_element(mhi_cntrl, buf_ring);
			mhi_del_ring_element(mhi_cntrl, tre_ring);
			local_rp = tre_ring->rp;

			/* notअगरy client */
			mhi_chan->xfer_cb(mhi_chan->mhi_dev, &result);

			अगर (mhi_chan->dir == DMA_TO_DEVICE) अणु
				atomic_dec(&mhi_cntrl->pending_pkts);
				/* Release the reference got from mhi_queue() */
				mhi_cntrl->runसमय_put(mhi_cntrl);
			पूर्ण

			/*
			 * Recycle the buffer अगर buffer is pre-allocated,
			 * अगर there is an error, not much we can करो apart
			 * from dropping the packet
			 */
			अगर (mhi_chan->pre_alloc) अणु
				अगर (mhi_queue_buf(mhi_chan->mhi_dev,
						  mhi_chan->dir,
						  buf_info->cb_buf,
						  buf_info->len, MHI_EOT)) अणु
					dev_err(dev,
						"Error recycling buffer for chan:%d\n",
						mhi_chan->chan);
					kमुक्त(buf_info->cb_buf);
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण /* CC_EOT */
	हाल MHI_EV_CC_OOB:
	हाल MHI_EV_CC_DB_MODE:
	अणु
		अचिन्हित दीर्घ pm_lock_flags;

		mhi_chan->db_cfg.db_mode = 1;
		पढ़ो_lock_irqsave(&mhi_cntrl->pm_lock, pm_lock_flags);
		अगर (tre_ring->wp != tre_ring->rp &&
		    MHI_DB_ACCESS_VALID(mhi_cntrl)) अणु
			mhi_ring_chan_db(mhi_cntrl, mhi_chan);
		पूर्ण
		पढ़ो_unlock_irqrestore(&mhi_cntrl->pm_lock, pm_lock_flags);
		अवरोध;
	पूर्ण
	हाल MHI_EV_CC_BAD_TRE:
	शेष:
		dev_err(dev, "Unknown event 0x%x\n", ev_code);
		अवरोध;
	पूर्ण /* चयन(MHI_EV_READ_CODE(EV_TRB_CODE,event)) */

end_process_tx_event:
	अगर (ev_code >= MHI_EV_CC_OOB)
		ग_लिखो_unlock_irqrestore(&mhi_chan->lock, flags);
	अन्यथा
		पढ़ो_unlock_bh(&mhi_chan->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक parse_rsc_event(काष्ठा mhi_controller *mhi_cntrl,
			   काष्ठा mhi_tre *event,
			   काष्ठा mhi_chan *mhi_chan)
अणु
	काष्ठा mhi_ring *buf_ring, *tre_ring;
	काष्ठा mhi_buf_info *buf_info;
	काष्ठा mhi_result result;
	पूर्णांक ev_code;
	u32 cookie; /* offset to local descriptor */
	u16 xfer_len;

	buf_ring = &mhi_chan->buf_ring;
	tre_ring = &mhi_chan->tre_ring;

	ev_code = MHI_TRE_GET_EV_CODE(event);
	cookie = MHI_TRE_GET_EV_COOKIE(event);
	xfer_len = MHI_TRE_GET_EV_LEN(event);

	/* Received out of bound cookie */
	WARN_ON(cookie >= buf_ring->len);

	buf_info = buf_ring->base + cookie;

	result.transaction_status = (ev_code == MHI_EV_CC_OVERFLOW) ?
		-EOVERFLOW : 0;

	/* truncate to buf len अगर xfer_len is larger */
	result.bytes_xferd = min_t(u16, xfer_len, buf_info->len);
	result.buf_addr = buf_info->cb_buf;
	result.dir = mhi_chan->dir;

	पढ़ो_lock_bh(&mhi_chan->lock);

	अगर (mhi_chan->ch_state != MHI_CH_STATE_ENABLED)
		जाओ end_process_rsc_event;

	WARN_ON(!buf_info->used);

	/* notअगरy the client */
	mhi_chan->xfer_cb(mhi_chan->mhi_dev, &result);

	/*
	 * Note: We're arbitrarily incrementing RP even though, completion
	 * packet we processed might not be the same one, reason we can करो this
	 * is because device guaranteed to cache descriptors in order it
	 * receive, so even though completion event is dअगरferent we can re-use
	 * all descriptors in between.
	 * Example:
	 * Transfer Ring has descriptors: A, B, C, D
	 * Last descriptor host queue is D (WP) and first descriptor
	 * host queue is A (RP).
	 * The completion event we just serviced is descriptor C.
	 * Then we can safely queue descriptors to replace A, B, and C
	 * even though host did not receive any completions.
	 */
	mhi_del_ring_element(mhi_cntrl, tre_ring);
	buf_info->used = false;

end_process_rsc_event:
	पढ़ो_unlock_bh(&mhi_chan->lock);

	वापस 0;
पूर्ण

अटल व्योम mhi_process_cmd_completion(काष्ठा mhi_controller *mhi_cntrl,
				       काष्ठा mhi_tre *tre)
अणु
	dma_addr_t ptr = MHI_TRE_GET_EV_PTR(tre);
	काष्ठा mhi_cmd *cmd_ring = &mhi_cntrl->mhi_cmd[PRIMARY_CMD_RING];
	काष्ठा mhi_ring *mhi_ring = &cmd_ring->ring;
	काष्ठा mhi_tre *cmd_pkt;
	काष्ठा mhi_chan *mhi_chan;
	u32 chan;

	अगर (!is_valid_ring_ptr(mhi_ring, ptr)) अणु
		dev_err(&mhi_cntrl->mhi_dev->dev,
			"Event element points outside of the cmd ring\n");
		वापस;
	पूर्ण

	cmd_pkt = mhi_to_भव(mhi_ring, ptr);

	chan = MHI_TRE_GET_CMD_CHID(cmd_pkt);
	mhi_chan = &mhi_cntrl->mhi_chan[chan];
	ग_लिखो_lock_bh(&mhi_chan->lock);
	mhi_chan->ccs = MHI_TRE_GET_EV_CODE(tre);
	complete(&mhi_chan->completion);
	ग_लिखो_unlock_bh(&mhi_chan->lock);

	mhi_del_ring_element(mhi_cntrl, mhi_ring);
पूर्ण

पूर्णांक mhi_process_ctrl_ev_ring(काष्ठा mhi_controller *mhi_cntrl,
			     काष्ठा mhi_event *mhi_event,
			     u32 event_quota)
अणु
	काष्ठा mhi_tre *dev_rp, *local_rp;
	काष्ठा mhi_ring *ev_ring = &mhi_event->ring;
	काष्ठा mhi_event_ctxt *er_ctxt =
		&mhi_cntrl->mhi_ctxt->er_ctxt[mhi_event->er_index];
	काष्ठा mhi_chan *mhi_chan;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;
	u32 chan;
	पूर्णांक count = 0;
	dma_addr_t ptr = er_ctxt->rp;

	/*
	 * This is a quick check to aव्योम unnecessary event processing
	 * in हाल MHI is alपढ़ोy in error state, but it's still possible
	 * to transition to error state जबतक processing events
	 */
	अगर (unlikely(MHI_EVENT_ACCESS_INVALID(mhi_cntrl->pm_state)))
		वापस -EIO;

	अगर (!is_valid_ring_ptr(ev_ring, ptr)) अणु
		dev_err(&mhi_cntrl->mhi_dev->dev,
			"Event ring rp points outside of the event ring\n");
		वापस -EIO;
	पूर्ण

	dev_rp = mhi_to_भव(ev_ring, ptr);
	local_rp = ev_ring->rp;

	जबतक (dev_rp != local_rp) अणु
		क्रमागत mhi_pkt_type type = MHI_TRE_GET_EV_TYPE(local_rp);

		चयन (type) अणु
		हाल MHI_PKT_TYPE_BW_REQ_EVENT:
		अणु
			काष्ठा mhi_link_info *link_info;

			link_info = &mhi_cntrl->mhi_link_info;
			ग_लिखो_lock_irq(&mhi_cntrl->pm_lock);
			link_info->target_link_speed =
				MHI_TRE_GET_EV_LINKSPEED(local_rp);
			link_info->target_link_width =
				MHI_TRE_GET_EV_LINKWIDTH(local_rp);
			ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);
			dev_dbg(dev, "Received BW_REQ event\n");
			mhi_cntrl->status_cb(mhi_cntrl, MHI_CB_BW_REQ);
			अवरोध;
		पूर्ण
		हाल MHI_PKT_TYPE_STATE_CHANGE_EVENT:
		अणु
			क्रमागत mhi_state new_state;

			new_state = MHI_TRE_GET_EV_STATE(local_rp);

			dev_dbg(dev, "State change event to state: %s\n",
				TO_MHI_STATE_STR(new_state));

			चयन (new_state) अणु
			हाल MHI_STATE_M0:
				mhi_pm_m0_transition(mhi_cntrl);
				अवरोध;
			हाल MHI_STATE_M1:
				mhi_pm_m1_transition(mhi_cntrl);
				अवरोध;
			हाल MHI_STATE_M3:
				mhi_pm_m3_transition(mhi_cntrl);
				अवरोध;
			हाल MHI_STATE_SYS_ERR:
			अणु
				क्रमागत mhi_pm_state pm_state;

				dev_dbg(dev, "System error detected\n");
				ग_लिखो_lock_irq(&mhi_cntrl->pm_lock);
				pm_state = mhi_tryset_pm_state(mhi_cntrl,
							MHI_PM_SYS_ERR_DETECT);
				ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);
				अगर (pm_state == MHI_PM_SYS_ERR_DETECT)
					mhi_pm_sys_err_handler(mhi_cntrl);
				अवरोध;
			पूर्ण
			शेष:
				dev_err(dev, "Invalid state: %s\n",
					TO_MHI_STATE_STR(new_state));
			पूर्ण

			अवरोध;
		पूर्ण
		हाल MHI_PKT_TYPE_CMD_COMPLETION_EVENT:
			mhi_process_cmd_completion(mhi_cntrl, local_rp);
			अवरोध;
		हाल MHI_PKT_TYPE_EE_EVENT:
		अणु
			क्रमागत dev_st_transition st = DEV_ST_TRANSITION_MAX;
			क्रमागत mhi_ee_type event = MHI_TRE_GET_EV_EXECENV(local_rp);

			dev_dbg(dev, "Received EE event: %s\n",
				TO_MHI_EXEC_STR(event));
			चयन (event) अणु
			हाल MHI_EE_SBL:
				st = DEV_ST_TRANSITION_SBL;
				अवरोध;
			हाल MHI_EE_WFW:
			हाल MHI_EE_AMSS:
				st = DEV_ST_TRANSITION_MISSION_MODE;
				अवरोध;
			हाल MHI_EE_FP:
				st = DEV_ST_TRANSITION_FP;
				अवरोध;
			हाल MHI_EE_RDDM:
				mhi_cntrl->status_cb(mhi_cntrl, MHI_CB_EE_RDDM);
				ग_लिखो_lock_irq(&mhi_cntrl->pm_lock);
				mhi_cntrl->ee = event;
				ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);
				wake_up_all(&mhi_cntrl->state_event);
				अवरोध;
			शेष:
				dev_err(dev,
					"Unhandled EE event: 0x%x\n", type);
			पूर्ण
			अगर (st != DEV_ST_TRANSITION_MAX)
				mhi_queue_state_transition(mhi_cntrl, st);

			अवरोध;
		पूर्ण
		हाल MHI_PKT_TYPE_TX_EVENT:
			chan = MHI_TRE_GET_EV_CHID(local_rp);

			WARN_ON(chan >= mhi_cntrl->max_chan);

			/*
			 * Only process the event ring elements whose channel
			 * ID is within the maximum supported range.
			 */
			अगर (chan < mhi_cntrl->max_chan) अणु
				mhi_chan = &mhi_cntrl->mhi_chan[chan];
				अगर (!mhi_chan->configured)
					अवरोध;
				parse_xfer_event(mhi_cntrl, local_rp, mhi_chan);
				event_quota--;
			पूर्ण
			अवरोध;
		शेष:
			dev_err(dev, "Unhandled event type: %d\n", type);
			अवरोध;
		पूर्ण

		mhi_recycle_ev_ring_element(mhi_cntrl, ev_ring);
		local_rp = ev_ring->rp;

		ptr = er_ctxt->rp;
		अगर (!is_valid_ring_ptr(ev_ring, ptr)) अणु
			dev_err(&mhi_cntrl->mhi_dev->dev,
				"Event ring rp points outside of the event ring\n");
			वापस -EIO;
		पूर्ण

		dev_rp = mhi_to_भव(ev_ring, ptr);
		count++;
	पूर्ण

	पढ़ो_lock_bh(&mhi_cntrl->pm_lock);
	अगर (likely(MHI_DB_ACCESS_VALID(mhi_cntrl)))
		mhi_ring_er_db(mhi_event);
	पढ़ो_unlock_bh(&mhi_cntrl->pm_lock);

	वापस count;
पूर्ण

पूर्णांक mhi_process_data_event_ring(काष्ठा mhi_controller *mhi_cntrl,
				काष्ठा mhi_event *mhi_event,
				u32 event_quota)
अणु
	काष्ठा mhi_tre *dev_rp, *local_rp;
	काष्ठा mhi_ring *ev_ring = &mhi_event->ring;
	काष्ठा mhi_event_ctxt *er_ctxt =
		&mhi_cntrl->mhi_ctxt->er_ctxt[mhi_event->er_index];
	पूर्णांक count = 0;
	u32 chan;
	काष्ठा mhi_chan *mhi_chan;
	dma_addr_t ptr = er_ctxt->rp;

	अगर (unlikely(MHI_EVENT_ACCESS_INVALID(mhi_cntrl->pm_state)))
		वापस -EIO;

	अगर (!is_valid_ring_ptr(ev_ring, ptr)) अणु
		dev_err(&mhi_cntrl->mhi_dev->dev,
			"Event ring rp points outside of the event ring\n");
		वापस -EIO;
	पूर्ण

	dev_rp = mhi_to_भव(ev_ring, ptr);
	local_rp = ev_ring->rp;

	जबतक (dev_rp != local_rp && event_quota > 0) अणु
		क्रमागत mhi_pkt_type type = MHI_TRE_GET_EV_TYPE(local_rp);

		chan = MHI_TRE_GET_EV_CHID(local_rp);

		WARN_ON(chan >= mhi_cntrl->max_chan);

		/*
		 * Only process the event ring elements whose channel
		 * ID is within the maximum supported range.
		 */
		अगर (chan < mhi_cntrl->max_chan &&
		    mhi_cntrl->mhi_chan[chan].configured) अणु
			mhi_chan = &mhi_cntrl->mhi_chan[chan];

			अगर (likely(type == MHI_PKT_TYPE_TX_EVENT)) अणु
				parse_xfer_event(mhi_cntrl, local_rp, mhi_chan);
				event_quota--;
			पूर्ण अन्यथा अगर (type == MHI_PKT_TYPE_RSC_TX_EVENT) अणु
				parse_rsc_event(mhi_cntrl, local_rp, mhi_chan);
				event_quota--;
			पूर्ण
		पूर्ण

		mhi_recycle_ev_ring_element(mhi_cntrl, ev_ring);
		local_rp = ev_ring->rp;

		ptr = er_ctxt->rp;
		अगर (!is_valid_ring_ptr(ev_ring, ptr)) अणु
			dev_err(&mhi_cntrl->mhi_dev->dev,
				"Event ring rp points outside of the event ring\n");
			वापस -EIO;
		पूर्ण

		dev_rp = mhi_to_भव(ev_ring, ptr);
		count++;
	पूर्ण
	पढ़ो_lock_bh(&mhi_cntrl->pm_lock);
	अगर (likely(MHI_DB_ACCESS_VALID(mhi_cntrl)))
		mhi_ring_er_db(mhi_event);
	पढ़ो_unlock_bh(&mhi_cntrl->pm_lock);

	वापस count;
पूर्ण

व्योम mhi_ev_task(अचिन्हित दीर्घ data)
अणु
	काष्ठा mhi_event *mhi_event = (काष्ठा mhi_event *)data;
	काष्ठा mhi_controller *mhi_cntrl = mhi_event->mhi_cntrl;

	/* process all pending events */
	spin_lock_bh(&mhi_event->lock);
	mhi_event->process_event(mhi_cntrl, mhi_event, U32_MAX);
	spin_unlock_bh(&mhi_event->lock);
पूर्ण

व्योम mhi_ctrl_ev_task(अचिन्हित दीर्घ data)
अणु
	काष्ठा mhi_event *mhi_event = (काष्ठा mhi_event *)data;
	काष्ठा mhi_controller *mhi_cntrl = mhi_event->mhi_cntrl;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;
	क्रमागत mhi_state state;
	क्रमागत mhi_pm_state pm_state = 0;
	पूर्णांक ret;

	/*
	 * We can check PM state w/o a lock here because there is no way
	 * PM state can change from reg access valid to no access जबतक this
	 * thपढ़ो being executed.
	 */
	अगर (!MHI_REG_ACCESS_VALID(mhi_cntrl->pm_state)) अणु
		/*
		 * We may have a pending event but not allowed to
		 * process it since we are probably in a suspended state,
		 * so trigger a resume.
		 */
		mhi_trigger_resume(mhi_cntrl);

		वापस;
	पूर्ण

	/* Process ctrl events events */
	ret = mhi_event->process_event(mhi_cntrl, mhi_event, U32_MAX);

	/*
	 * We received an IRQ but no events to process, maybe device went to
	 * SYS_ERR state? Check the state to confirm.
	 */
	अगर (!ret) अणु
		ग_लिखो_lock_irq(&mhi_cntrl->pm_lock);
		state = mhi_get_mhi_state(mhi_cntrl);
		अगर (state == MHI_STATE_SYS_ERR) अणु
			dev_dbg(dev, "System error detected\n");
			pm_state = mhi_tryset_pm_state(mhi_cntrl,
						       MHI_PM_SYS_ERR_DETECT);
		पूर्ण
		ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);
		अगर (pm_state == MHI_PM_SYS_ERR_DETECT)
			mhi_pm_sys_err_handler(mhi_cntrl);
	पूर्ण
पूर्ण

अटल bool mhi_is_ring_full(काष्ठा mhi_controller *mhi_cntrl,
			     काष्ठा mhi_ring *ring)
अणु
	व्योम *पंचांगp = ring->wp + ring->el_size;

	अगर (पंचांगp >= (ring->base + ring->len))
		पंचांगp = ring->base;

	वापस (पंचांगp == ring->rp);
पूर्ण

अटल पूर्णांक mhi_queue(काष्ठा mhi_device *mhi_dev, काष्ठा mhi_buf_info *buf_info,
		     क्रमागत dma_data_direction dir, क्रमागत mhi_flags mflags)
अणु
	काष्ठा mhi_controller *mhi_cntrl = mhi_dev->mhi_cntrl;
	काष्ठा mhi_chan *mhi_chan = (dir == DMA_TO_DEVICE) ? mhi_dev->ul_chan :
							     mhi_dev->dl_chan;
	काष्ठा mhi_ring *tre_ring = &mhi_chan->tre_ring;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (unlikely(MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state)))
		वापस -EIO;

	पढ़ो_lock_irqsave(&mhi_cntrl->pm_lock, flags);

	ret = mhi_is_ring_full(mhi_cntrl, tre_ring);
	अगर (unlikely(ret)) अणु
		ret = -EAGAIN;
		जाओ निकास_unlock;
	पूर्ण

	ret = mhi_gen_tre(mhi_cntrl, mhi_chan, buf_info, mflags);
	अगर (unlikely(ret))
		जाओ निकास_unlock;

	/* Packet is queued, take a usage ref to निकास M3 अगर necessary
	 * क्रम host->device buffer, balanced put is करोne on buffer completion
	 * क्रम device->host buffer, balanced put is after ringing the DB
	 */
	mhi_cntrl->runसमय_get(mhi_cntrl);

	/* Assert dev_wake (to निकास/prevent M1/M2)*/
	mhi_cntrl->wake_toggle(mhi_cntrl);

	अगर (mhi_chan->dir == DMA_TO_DEVICE)
		atomic_inc(&mhi_cntrl->pending_pkts);

	अगर (likely(MHI_DB_ACCESS_VALID(mhi_cntrl)))
		mhi_ring_chan_db(mhi_cntrl, mhi_chan);

	अगर (dir == DMA_FROM_DEVICE)
		mhi_cntrl->runसमय_put(mhi_cntrl);

निकास_unlock:
	पढ़ो_unlock_irqrestore(&mhi_cntrl->pm_lock, flags);

	वापस ret;
पूर्ण

पूर्णांक mhi_queue_skb(काष्ठा mhi_device *mhi_dev, क्रमागत dma_data_direction dir,
		  काष्ठा sk_buff *skb, माप_प्रकार len, क्रमागत mhi_flags mflags)
अणु
	काष्ठा mhi_chan *mhi_chan = (dir == DMA_TO_DEVICE) ? mhi_dev->ul_chan :
							     mhi_dev->dl_chan;
	काष्ठा mhi_buf_info buf_info = अणु पूर्ण;

	buf_info.v_addr = skb->data;
	buf_info.cb_buf = skb;
	buf_info.len = len;

	अगर (unlikely(mhi_chan->pre_alloc))
		वापस -EINVAL;

	वापस mhi_queue(mhi_dev, &buf_info, dir, mflags);
पूर्ण
EXPORT_SYMBOL_GPL(mhi_queue_skb);

पूर्णांक mhi_queue_dma(काष्ठा mhi_device *mhi_dev, क्रमागत dma_data_direction dir,
		  काष्ठा mhi_buf *mhi_buf, माप_प्रकार len, क्रमागत mhi_flags mflags)
अणु
	काष्ठा mhi_chan *mhi_chan = (dir == DMA_TO_DEVICE) ? mhi_dev->ul_chan :
							     mhi_dev->dl_chan;
	काष्ठा mhi_buf_info buf_info = अणु पूर्ण;

	buf_info.p_addr = mhi_buf->dma_addr;
	buf_info.cb_buf = mhi_buf;
	buf_info.pre_mapped = true;
	buf_info.len = len;

	अगर (unlikely(mhi_chan->pre_alloc))
		वापस -EINVAL;

	वापस mhi_queue(mhi_dev, &buf_info, dir, mflags);
पूर्ण
EXPORT_SYMBOL_GPL(mhi_queue_dma);

पूर्णांक mhi_gen_tre(काष्ठा mhi_controller *mhi_cntrl, काष्ठा mhi_chan *mhi_chan,
			काष्ठा mhi_buf_info *info, क्रमागत mhi_flags flags)
अणु
	काष्ठा mhi_ring *buf_ring, *tre_ring;
	काष्ठा mhi_tre *mhi_tre;
	काष्ठा mhi_buf_info *buf_info;
	पूर्णांक eot, eob, chain, bei;
	पूर्णांक ret;

	buf_ring = &mhi_chan->buf_ring;
	tre_ring = &mhi_chan->tre_ring;

	buf_info = buf_ring->wp;
	WARN_ON(buf_info->used);
	buf_info->pre_mapped = info->pre_mapped;
	अगर (info->pre_mapped)
		buf_info->p_addr = info->p_addr;
	अन्यथा
		buf_info->v_addr = info->v_addr;
	buf_info->cb_buf = info->cb_buf;
	buf_info->wp = tre_ring->wp;
	buf_info->dir = mhi_chan->dir;
	buf_info->len = info->len;

	अगर (!info->pre_mapped) अणु
		ret = mhi_cntrl->map_single(mhi_cntrl, buf_info);
		अगर (ret)
			वापस ret;
	पूर्ण

	eob = !!(flags & MHI_EOB);
	eot = !!(flags & MHI_EOT);
	chain = !!(flags & MHI_CHAIN);
	bei = !!(mhi_chan->पूर्णांकmod);

	mhi_tre = tre_ring->wp;
	mhi_tre->ptr = MHI_TRE_DATA_PTR(buf_info->p_addr);
	mhi_tre->dword[0] = MHI_TRE_DATA_DWORD0(info->len);
	mhi_tre->dword[1] = MHI_TRE_DATA_DWORD1(bei, eot, eob, chain);

	/* increment WP */
	mhi_add_ring_element(mhi_cntrl, tre_ring);
	mhi_add_ring_element(mhi_cntrl, buf_ring);

	वापस 0;
पूर्ण

पूर्णांक mhi_queue_buf(काष्ठा mhi_device *mhi_dev, क्रमागत dma_data_direction dir,
		  व्योम *buf, माप_प्रकार len, क्रमागत mhi_flags mflags)
अणु
	काष्ठा mhi_buf_info buf_info = अणु पूर्ण;

	buf_info.v_addr = buf;
	buf_info.cb_buf = buf;
	buf_info.len = len;

	वापस mhi_queue(mhi_dev, &buf_info, dir, mflags);
पूर्ण
EXPORT_SYMBOL_GPL(mhi_queue_buf);

bool mhi_queue_is_full(काष्ठा mhi_device *mhi_dev, क्रमागत dma_data_direction dir)
अणु
	काष्ठा mhi_controller *mhi_cntrl = mhi_dev->mhi_cntrl;
	काष्ठा mhi_chan *mhi_chan = (dir == DMA_TO_DEVICE) ?
					mhi_dev->ul_chan : mhi_dev->dl_chan;
	काष्ठा mhi_ring *tre_ring = &mhi_chan->tre_ring;

	वापस mhi_is_ring_full(mhi_cntrl, tre_ring);
पूर्ण
EXPORT_SYMBOL_GPL(mhi_queue_is_full);

पूर्णांक mhi_send_cmd(काष्ठा mhi_controller *mhi_cntrl,
		 काष्ठा mhi_chan *mhi_chan,
		 क्रमागत mhi_cmd_type cmd)
अणु
	काष्ठा mhi_tre *cmd_tre = शून्य;
	काष्ठा mhi_cmd *mhi_cmd = &mhi_cntrl->mhi_cmd[PRIMARY_CMD_RING];
	काष्ठा mhi_ring *ring = &mhi_cmd->ring;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;
	पूर्णांक chan = 0;

	अगर (mhi_chan)
		chan = mhi_chan->chan;

	spin_lock_bh(&mhi_cmd->lock);
	अगर (!get_nr_avail_ring_elements(mhi_cntrl, ring)) अणु
		spin_unlock_bh(&mhi_cmd->lock);
		वापस -ENOMEM;
	पूर्ण

	/* prepare the cmd tre */
	cmd_tre = ring->wp;
	चयन (cmd) अणु
	हाल MHI_CMD_RESET_CHAN:
		cmd_tre->ptr = MHI_TRE_CMD_RESET_PTR;
		cmd_tre->dword[0] = MHI_TRE_CMD_RESET_DWORD0;
		cmd_tre->dword[1] = MHI_TRE_CMD_RESET_DWORD1(chan);
		अवरोध;
	हाल MHI_CMD_STOP_CHAN:
		cmd_tre->ptr = MHI_TRE_CMD_STOP_PTR;
		cmd_tre->dword[0] = MHI_TRE_CMD_STOP_DWORD0;
		cmd_tre->dword[1] = MHI_TRE_CMD_STOP_DWORD1(chan);
		अवरोध;
	हाल MHI_CMD_START_CHAN:
		cmd_tre->ptr = MHI_TRE_CMD_START_PTR;
		cmd_tre->dword[0] = MHI_TRE_CMD_START_DWORD0;
		cmd_tre->dword[1] = MHI_TRE_CMD_START_DWORD1(chan);
		अवरोध;
	शेष:
		dev_err(dev, "Command not supported\n");
		अवरोध;
	पूर्ण

	/* queue to hardware */
	mhi_add_ring_element(mhi_cntrl, ring);
	पढ़ो_lock_bh(&mhi_cntrl->pm_lock);
	अगर (likely(MHI_DB_ACCESS_VALID(mhi_cntrl)))
		mhi_ring_cmd_db(mhi_cntrl, mhi_cmd);
	पढ़ो_unlock_bh(&mhi_cntrl->pm_lock);
	spin_unlock_bh(&mhi_cmd->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक mhi_update_channel_state(काष्ठा mhi_controller *mhi_cntrl,
				    काष्ठा mhi_chan *mhi_chan,
				    क्रमागत mhi_ch_state_type to_state)
अणु
	काष्ठा device *dev = &mhi_chan->mhi_dev->dev;
	क्रमागत mhi_cmd_type cmd = MHI_CMD_NOP;
	पूर्णांक ret;

	dev_dbg(dev, "%d: Updating channel state to: %s\n", mhi_chan->chan,
		TO_CH_STATE_TYPE_STR(to_state));

	चयन (to_state) अणु
	हाल MHI_CH_STATE_TYPE_RESET:
		ग_लिखो_lock_irq(&mhi_chan->lock);
		अगर (mhi_chan->ch_state != MHI_CH_STATE_STOP &&
		    mhi_chan->ch_state != MHI_CH_STATE_ENABLED &&
		    mhi_chan->ch_state != MHI_CH_STATE_SUSPENDED) अणु
			ग_लिखो_unlock_irq(&mhi_chan->lock);
			वापस -EINVAL;
		पूर्ण
		mhi_chan->ch_state = MHI_CH_STATE_DISABLED;
		ग_लिखो_unlock_irq(&mhi_chan->lock);

		cmd = MHI_CMD_RESET_CHAN;
		अवरोध;
	हाल MHI_CH_STATE_TYPE_STOP:
		अगर (mhi_chan->ch_state != MHI_CH_STATE_ENABLED)
			वापस -EINVAL;

		cmd = MHI_CMD_STOP_CHAN;
		अवरोध;
	हाल MHI_CH_STATE_TYPE_START:
		अगर (mhi_chan->ch_state != MHI_CH_STATE_STOP &&
		    mhi_chan->ch_state != MHI_CH_STATE_DISABLED)
			वापस -EINVAL;

		cmd = MHI_CMD_START_CHAN;
		अवरोध;
	शेष:
		dev_err(dev, "%d: Channel state update to %s not allowed\n",
			mhi_chan->chan, TO_CH_STATE_TYPE_STR(to_state));
		वापस -EINVAL;
	पूर्ण

	/* bring host and device out of suspended states */
	ret = mhi_device_get_sync(mhi_cntrl->mhi_dev);
	अगर (ret)
		वापस ret;
	mhi_cntrl->runसमय_get(mhi_cntrl);

	reinit_completion(&mhi_chan->completion);
	ret = mhi_send_cmd(mhi_cntrl, mhi_chan, cmd);
	अगर (ret) अणु
		dev_err(dev, "%d: Failed to send %s channel command\n",
			mhi_chan->chan, TO_CH_STATE_TYPE_STR(to_state));
		जाओ निकास_channel_update;
	पूर्ण

	ret = रुको_क्रम_completion_समयout(&mhi_chan->completion,
				       msecs_to_jअगरfies(mhi_cntrl->समयout_ms));
	अगर (!ret || mhi_chan->ccs != MHI_EV_CC_SUCCESS) अणु
		dev_err(dev,
			"%d: Failed to receive %s channel command completion\n",
			mhi_chan->chan, TO_CH_STATE_TYPE_STR(to_state));
		ret = -EIO;
		जाओ निकास_channel_update;
	पूर्ण

	ret = 0;

	अगर (to_state != MHI_CH_STATE_TYPE_RESET) अणु
		ग_लिखो_lock_irq(&mhi_chan->lock);
		mhi_chan->ch_state = (to_state == MHI_CH_STATE_TYPE_START) ?
				      MHI_CH_STATE_ENABLED : MHI_CH_STATE_STOP;
		ग_लिखो_unlock_irq(&mhi_chan->lock);
	पूर्ण

	dev_dbg(dev, "%d: Channel state change to %s successful\n",
		mhi_chan->chan, TO_CH_STATE_TYPE_STR(to_state));

निकास_channel_update:
	mhi_cntrl->runसमय_put(mhi_cntrl);
	mhi_device_put(mhi_cntrl->mhi_dev);

	वापस ret;
पूर्ण

अटल व्योम mhi_unprepare_channel(काष्ठा mhi_controller *mhi_cntrl,
				  काष्ठा mhi_chan *mhi_chan)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = &mhi_chan->mhi_dev->dev;

	mutex_lock(&mhi_chan->mutex);

	अगर (!(BIT(mhi_cntrl->ee) & mhi_chan->ee_mask)) अणु
		dev_dbg(dev, "Current EE: %s Required EE Mask: 0x%x\n",
			TO_MHI_EXEC_STR(mhi_cntrl->ee), mhi_chan->ee_mask);
		जाओ निकास_unprepare_channel;
	पूर्ण

	/* no more processing events क्रम this channel */
	ret = mhi_update_channel_state(mhi_cntrl, mhi_chan,
				       MHI_CH_STATE_TYPE_RESET);
	अगर (ret)
		dev_err(dev, "%d: Failed to reset channel, still resetting\n",
			mhi_chan->chan);

निकास_unprepare_channel:
	ग_लिखो_lock_irq(&mhi_chan->lock);
	mhi_chan->ch_state = MHI_CH_STATE_DISABLED;
	ग_लिखो_unlock_irq(&mhi_chan->lock);

	अगर (!mhi_chan->offload_ch) अणु
		mhi_reset_chan(mhi_cntrl, mhi_chan);
		mhi_deinit_chan_ctxt(mhi_cntrl, mhi_chan);
	पूर्ण
	dev_dbg(dev, "%d: successfully reset\n", mhi_chan->chan);

	mutex_unlock(&mhi_chan->mutex);
पूर्ण

पूर्णांक mhi_prepare_channel(काष्ठा mhi_controller *mhi_cntrl,
			काष्ठा mhi_chan *mhi_chan)
अणु
	पूर्णांक ret = 0;
	काष्ठा device *dev = &mhi_chan->mhi_dev->dev;

	अगर (!(BIT(mhi_cntrl->ee) & mhi_chan->ee_mask)) अणु
		dev_err(dev, "Current EE: %s Required EE Mask: 0x%x\n",
			TO_MHI_EXEC_STR(mhi_cntrl->ee), mhi_chan->ee_mask);
		वापस -ENOTCONN;
	पूर्ण

	mutex_lock(&mhi_chan->mutex);

	/* Check of client manages channel context क्रम offload channels */
	अगर (!mhi_chan->offload_ch) अणु
		ret = mhi_init_chan_ctxt(mhi_cntrl, mhi_chan);
		अगर (ret)
			जाओ error_init_chan;
	पूर्ण

	ret = mhi_update_channel_state(mhi_cntrl, mhi_chan,
				       MHI_CH_STATE_TYPE_START);
	अगर (ret)
		जाओ error_pm_state;

	/* Pre-allocate buffer क्रम xfer ring */
	अगर (mhi_chan->pre_alloc) अणु
		पूर्णांक nr_el = get_nr_avail_ring_elements(mhi_cntrl,
						       &mhi_chan->tre_ring);
		माप_प्रकार len = mhi_cntrl->buffer_len;

		जबतक (nr_el--) अणु
			व्योम *buf;
			काष्ठा mhi_buf_info info = अणु पूर्ण;
			buf = kदो_स्मृति(len, GFP_KERNEL);
			अगर (!buf) अणु
				ret = -ENOMEM;
				जाओ error_pre_alloc;
			पूर्ण

			/* Prepare transfer descriptors */
			info.v_addr = buf;
			info.cb_buf = buf;
			info.len = len;
			ret = mhi_gen_tre(mhi_cntrl, mhi_chan, &info, MHI_EOT);
			अगर (ret) अणु
				kमुक्त(buf);
				जाओ error_pre_alloc;
			पूर्ण
		पूर्ण

		पढ़ो_lock_bh(&mhi_cntrl->pm_lock);
		अगर (MHI_DB_ACCESS_VALID(mhi_cntrl)) अणु
			पढ़ो_lock_irq(&mhi_chan->lock);
			mhi_ring_chan_db(mhi_cntrl, mhi_chan);
			पढ़ो_unlock_irq(&mhi_chan->lock);
		पूर्ण
		पढ़ो_unlock_bh(&mhi_cntrl->pm_lock);
	पूर्ण

	mutex_unlock(&mhi_chan->mutex);

	वापस 0;

error_pm_state:
	अगर (!mhi_chan->offload_ch)
		mhi_deinit_chan_ctxt(mhi_cntrl, mhi_chan);

error_init_chan:
	mutex_unlock(&mhi_chan->mutex);

	वापस ret;

error_pre_alloc:
	mutex_unlock(&mhi_chan->mutex);
	mhi_unprepare_channel(mhi_cntrl, mhi_chan);

	वापस ret;
पूर्ण

अटल व्योम mhi_mark_stale_events(काष्ठा mhi_controller *mhi_cntrl,
				  काष्ठा mhi_event *mhi_event,
				  काष्ठा mhi_event_ctxt *er_ctxt,
				  पूर्णांक chan)

अणु
	काष्ठा mhi_tre *dev_rp, *local_rp;
	काष्ठा mhi_ring *ev_ring;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;
	अचिन्हित दीर्घ flags;
	dma_addr_t ptr;

	dev_dbg(dev, "Marking all events for chan: %d as stale\n", chan);

	ev_ring = &mhi_event->ring;

	/* mark all stale events related to channel as STALE event */
	spin_lock_irqsave(&mhi_event->lock, flags);

	ptr = er_ctxt->rp;
	अगर (!is_valid_ring_ptr(ev_ring, ptr)) अणु
		dev_err(&mhi_cntrl->mhi_dev->dev,
			"Event ring rp points outside of the event ring\n");
		dev_rp = ev_ring->rp;
	पूर्ण अन्यथा अणु
		dev_rp = mhi_to_भव(ev_ring, ptr);
	पूर्ण

	local_rp = ev_ring->rp;
	जबतक (dev_rp != local_rp) अणु
		अगर (MHI_TRE_GET_EV_TYPE(local_rp) == MHI_PKT_TYPE_TX_EVENT &&
		    chan == MHI_TRE_GET_EV_CHID(local_rp))
			local_rp->dword[1] = MHI_TRE_EV_DWORD1(chan,
					MHI_PKT_TYPE_STALE_EVENT);
		local_rp++;
		अगर (local_rp == (ev_ring->base + ev_ring->len))
			local_rp = ev_ring->base;
	पूर्ण

	dev_dbg(dev, "Finished marking events as stale events\n");
	spin_unlock_irqrestore(&mhi_event->lock, flags);
पूर्ण

अटल व्योम mhi_reset_data_chan(काष्ठा mhi_controller *mhi_cntrl,
				काष्ठा mhi_chan *mhi_chan)
अणु
	काष्ठा mhi_ring *buf_ring, *tre_ring;
	काष्ठा mhi_result result;

	/* Reset any pending buffers */
	buf_ring = &mhi_chan->buf_ring;
	tre_ring = &mhi_chan->tre_ring;
	result.transaction_status = -ENOTCONN;
	result.bytes_xferd = 0;
	जबतक (tre_ring->rp != tre_ring->wp) अणु
		काष्ठा mhi_buf_info *buf_info = buf_ring->rp;

		अगर (mhi_chan->dir == DMA_TO_DEVICE) अणु
			atomic_dec(&mhi_cntrl->pending_pkts);
			/* Release the reference got from mhi_queue() */
			mhi_cntrl->runसमय_put(mhi_cntrl);
		पूर्ण

		अगर (!buf_info->pre_mapped)
			mhi_cntrl->unmap_single(mhi_cntrl, buf_info);

		mhi_del_ring_element(mhi_cntrl, buf_ring);
		mhi_del_ring_element(mhi_cntrl, tre_ring);

		अगर (mhi_chan->pre_alloc) अणु
			kमुक्त(buf_info->cb_buf);
		पूर्ण अन्यथा अणु
			result.buf_addr = buf_info->cb_buf;
			mhi_chan->xfer_cb(mhi_chan->mhi_dev, &result);
		पूर्ण
	पूर्ण
पूर्ण

व्योम mhi_reset_chan(काष्ठा mhi_controller *mhi_cntrl, काष्ठा mhi_chan *mhi_chan)
अणु
	काष्ठा mhi_event *mhi_event;
	काष्ठा mhi_event_ctxt *er_ctxt;
	पूर्णांक chan = mhi_chan->chan;

	/* Nothing to reset, client करोesn't queue buffers */
	अगर (mhi_chan->offload_ch)
		वापस;

	पढ़ो_lock_bh(&mhi_cntrl->pm_lock);
	mhi_event = &mhi_cntrl->mhi_event[mhi_chan->er_index];
	er_ctxt = &mhi_cntrl->mhi_ctxt->er_ctxt[mhi_chan->er_index];

	mhi_mark_stale_events(mhi_cntrl, mhi_event, er_ctxt, chan);

	mhi_reset_data_chan(mhi_cntrl, mhi_chan);

	पढ़ो_unlock_bh(&mhi_cntrl->pm_lock);
पूर्ण

/* Move channel to start state */
पूर्णांक mhi_prepare_क्रम_transfer(काष्ठा mhi_device *mhi_dev)
अणु
	पूर्णांक ret, dir;
	काष्ठा mhi_controller *mhi_cntrl = mhi_dev->mhi_cntrl;
	काष्ठा mhi_chan *mhi_chan;

	क्रम (dir = 0; dir < 2; dir++) अणु
		mhi_chan = dir ? mhi_dev->dl_chan : mhi_dev->ul_chan;
		अगर (!mhi_chan)
			जारी;

		ret = mhi_prepare_channel(mhi_cntrl, mhi_chan);
		अगर (ret)
			जाओ error_खोलो_chan;
	पूर्ण

	वापस 0;

error_खोलो_chan:
	क्रम (--dir; dir >= 0; dir--) अणु
		mhi_chan = dir ? mhi_dev->dl_chan : mhi_dev->ul_chan;
		अगर (!mhi_chan)
			जारी;

		mhi_unprepare_channel(mhi_cntrl, mhi_chan);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mhi_prepare_क्रम_transfer);

व्योम mhi_unprepare_from_transfer(काष्ठा mhi_device *mhi_dev)
अणु
	काष्ठा mhi_controller *mhi_cntrl = mhi_dev->mhi_cntrl;
	काष्ठा mhi_chan *mhi_chan;
	पूर्णांक dir;

	क्रम (dir = 0; dir < 2; dir++) अणु
		mhi_chan = dir ? mhi_dev->ul_chan : mhi_dev->dl_chan;
		अगर (!mhi_chan)
			जारी;

		mhi_unprepare_channel(mhi_cntrl, mhi_chan);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mhi_unprepare_from_transfer);

पूर्णांक mhi_poll(काष्ठा mhi_device *mhi_dev, u32 budget)
अणु
	काष्ठा mhi_controller *mhi_cntrl = mhi_dev->mhi_cntrl;
	काष्ठा mhi_chan *mhi_chan = mhi_dev->dl_chan;
	काष्ठा mhi_event *mhi_event = &mhi_cntrl->mhi_event[mhi_chan->er_index];
	पूर्णांक ret;

	spin_lock_bh(&mhi_event->lock);
	ret = mhi_event->process_event(mhi_cntrl, mhi_event, budget);
	spin_unlock_bh(&mhi_event->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mhi_poll);
