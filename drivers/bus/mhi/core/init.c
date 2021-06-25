<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018-2020, The Linux Foundation. All rights reserved.
 *
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-direction.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/idr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/mhi.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/रुको.h>
#समावेश "internal.h"

अटल DEFINE_IDA(mhi_controller_ida);

स्थिर अक्षर * स्थिर mhi_ee_str[MHI_EE_MAX] = अणु
	[MHI_EE_PBL] = "PRIMARY BOOTLOADER",
	[MHI_EE_SBL] = "SECONDARY BOOTLOADER",
	[MHI_EE_AMSS] = "MISSION MODE",
	[MHI_EE_RDDM] = "RAMDUMP DOWNLOAD MODE",
	[MHI_EE_WFW] = "WLAN FIRMWARE",
	[MHI_EE_PTHRU] = "PASS THROUGH",
	[MHI_EE_EDL] = "EMERGENCY DOWNLOAD",
	[MHI_EE_FP] = "FLASH PROGRAMMER",
	[MHI_EE_DISABLE_TRANSITION] = "DISABLE",
	[MHI_EE_NOT_SUPPORTED] = "NOT SUPPORTED",
पूर्ण;

स्थिर अक्षर * स्थिर dev_state_tran_str[DEV_ST_TRANSITION_MAX] = अणु
	[DEV_ST_TRANSITION_PBL] = "PBL",
	[DEV_ST_TRANSITION_READY] = "READY",
	[DEV_ST_TRANSITION_SBL] = "SBL",
	[DEV_ST_TRANSITION_MISSION_MODE] = "MISSION MODE",
	[DEV_ST_TRANSITION_FP] = "FLASH PROGRAMMER",
	[DEV_ST_TRANSITION_SYS_ERR] = "SYS ERROR",
	[DEV_ST_TRANSITION_DISABLE] = "DISABLE",
पूर्ण;

स्थिर अक्षर * स्थिर mhi_state_str[MHI_STATE_MAX] = अणु
	[MHI_STATE_RESET] = "RESET",
	[MHI_STATE_READY] = "READY",
	[MHI_STATE_M0] = "M0",
	[MHI_STATE_M1] = "M1",
	[MHI_STATE_M2] = "M2",
	[MHI_STATE_M3] = "M3",
	[MHI_STATE_M3_FAST] = "M3 FAST",
	[MHI_STATE_BHI] = "BHI",
	[MHI_STATE_SYS_ERR] = "SYS ERROR",
पूर्ण;

स्थिर अक्षर * स्थिर mhi_ch_state_type_str[MHI_CH_STATE_TYPE_MAX] = अणु
	[MHI_CH_STATE_TYPE_RESET] = "RESET",
	[MHI_CH_STATE_TYPE_STOP] = "STOP",
	[MHI_CH_STATE_TYPE_START] = "START",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mhi_pm_state_str[] = अणु
	[MHI_PM_STATE_DISABLE] = "DISABLE",
	[MHI_PM_STATE_POR] = "POWER ON RESET",
	[MHI_PM_STATE_M0] = "M0",
	[MHI_PM_STATE_M2] = "M2",
	[MHI_PM_STATE_M3_ENTER] = "M?->M3",
	[MHI_PM_STATE_M3] = "M3",
	[MHI_PM_STATE_M3_EXIT] = "M3->M0",
	[MHI_PM_STATE_FW_DL_ERR] = "Firmware Download Error",
	[MHI_PM_STATE_SYS_ERR_DETECT] = "SYS ERROR Detect",
	[MHI_PM_STATE_SYS_ERR_PROCESS] = "SYS ERROR Process",
	[MHI_PM_STATE_SHUTDOWN_PROCESS] = "SHUTDOWN Process",
	[MHI_PM_STATE_LD_ERR_FATAL_DETECT] = "Linkdown or Error Fatal Detect",
पूर्ण;

स्थिर अक्षर *to_mhi_pm_state_str(क्रमागत mhi_pm_state state)
अणु
	पूर्णांक index = find_last_bit((अचिन्हित दीर्घ *)&state, 32);

	अगर (index >= ARRAY_SIZE(mhi_pm_state_str))
		वापस "Invalid State";

	वापस mhi_pm_state_str[index];
पूर्ण

अटल sमाप_प्रकार serial_number_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	काष्ठा mhi_device *mhi_dev = to_mhi_device(dev);
	काष्ठा mhi_controller *mhi_cntrl = mhi_dev->mhi_cntrl;

	वापस snम_लिखो(buf, PAGE_SIZE, "Serial Number: %u\n",
			mhi_cntrl->serial_number);
पूर्ण
अटल DEVICE_ATTR_RO(serial_number);

अटल sमाप_प्रकार oem_pk_hash_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा mhi_device *mhi_dev = to_mhi_device(dev);
	काष्ठा mhi_controller *mhi_cntrl = mhi_dev->mhi_cntrl;
	पूर्णांक i, cnt = 0;

	क्रम (i = 0; i < ARRAY_SIZE(mhi_cntrl->oem_pk_hash); i++)
		cnt += snम_लिखो(buf + cnt, PAGE_SIZE - cnt,
				"OEMPKHASH[%d]: 0x%x\n", i,
				mhi_cntrl->oem_pk_hash[i]);

	वापस cnt;
पूर्ण
अटल DEVICE_ATTR_RO(oem_pk_hash);

अटल काष्ठा attribute *mhi_dev_attrs[] = अणु
	&dev_attr_serial_number.attr,
	&dev_attr_oem_pk_hash.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(mhi_dev);

/* MHI protocol requires the transfer ring to be aligned with ring length */
अटल पूर्णांक mhi_alloc_aligned_ring(काष्ठा mhi_controller *mhi_cntrl,
				  काष्ठा mhi_ring *ring,
				  u64 len)
अणु
	ring->alloc_size = len + (len - 1);
	ring->pre_aligned = mhi_alloc_coherent(mhi_cntrl, ring->alloc_size,
					       &ring->dma_handle, GFP_KERNEL);
	अगर (!ring->pre_aligned)
		वापस -ENOMEM;

	ring->iommu_base = (ring->dma_handle + (len - 1)) & ~(len - 1);
	ring->base = ring->pre_aligned + (ring->iommu_base - ring->dma_handle);

	वापस 0;
पूर्ण

व्योम mhi_deinit_मुक्त_irq(काष्ठा mhi_controller *mhi_cntrl)
अणु
	पूर्णांक i;
	काष्ठा mhi_event *mhi_event = mhi_cntrl->mhi_event;

	क्रम (i = 0; i < mhi_cntrl->total_ev_rings; i++, mhi_event++) अणु
		अगर (mhi_event->offload_ev)
			जारी;

		मुक्त_irq(mhi_cntrl->irq[mhi_event->irq], mhi_event);
	पूर्ण

	मुक्त_irq(mhi_cntrl->irq[0], mhi_cntrl);
पूर्ण

पूर्णांक mhi_init_irq_setup(काष्ठा mhi_controller *mhi_cntrl)
अणु
	काष्ठा mhi_event *mhi_event = mhi_cntrl->mhi_event;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;
	अचिन्हित दीर्घ irq_flags = IRQF_SHARED | IRQF_NO_SUSPEND;
	पूर्णांक i, ret;

	/* अगर controller driver has set irq_flags, use it */
	अगर (mhi_cntrl->irq_flags)
		irq_flags = mhi_cntrl->irq_flags;

	/* Setup BHI_INTVEC IRQ */
	ret = request_thपढ़ोed_irq(mhi_cntrl->irq[0], mhi_पूर्णांकvec_handler,
				   mhi_पूर्णांकvec_thपढ़ोed_handler,
				   irq_flags,
				   "bhi", mhi_cntrl);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < mhi_cntrl->total_ev_rings; i++, mhi_event++) अणु
		अगर (mhi_event->offload_ev)
			जारी;

		अगर (mhi_event->irq >= mhi_cntrl->nr_irqs) अणु
			dev_err(dev, "irq %d not available for event ring\n",
				mhi_event->irq);
			ret = -EINVAL;
			जाओ error_request;
		पूर्ण

		ret = request_irq(mhi_cntrl->irq[mhi_event->irq],
				  mhi_irq_handler,
				  irq_flags,
				  "mhi", mhi_event);
		अगर (ret) अणु
			dev_err(dev, "Error requesting irq:%d for ev:%d\n",
				mhi_cntrl->irq[mhi_event->irq], i);
			जाओ error_request;
		पूर्ण
	पूर्ण

	वापस 0;

error_request:
	क्रम (--i, --mhi_event; i >= 0; i--, mhi_event--) अणु
		अगर (mhi_event->offload_ev)
			जारी;

		मुक्त_irq(mhi_cntrl->irq[mhi_event->irq], mhi_event);
	पूर्ण
	मुक्त_irq(mhi_cntrl->irq[0], mhi_cntrl);

	वापस ret;
पूर्ण

व्योम mhi_deinit_dev_ctxt(काष्ठा mhi_controller *mhi_cntrl)
अणु
	पूर्णांक i;
	काष्ठा mhi_ctxt *mhi_ctxt = mhi_cntrl->mhi_ctxt;
	काष्ठा mhi_cmd *mhi_cmd;
	काष्ठा mhi_event *mhi_event;
	काष्ठा mhi_ring *ring;

	mhi_cmd = mhi_cntrl->mhi_cmd;
	क्रम (i = 0; i < NR_OF_CMD_RINGS; i++, mhi_cmd++) अणु
		ring = &mhi_cmd->ring;
		mhi_मुक्त_coherent(mhi_cntrl, ring->alloc_size,
				  ring->pre_aligned, ring->dma_handle);
		ring->base = शून्य;
		ring->iommu_base = 0;
	पूर्ण

	mhi_मुक्त_coherent(mhi_cntrl,
			  माप(*mhi_ctxt->cmd_ctxt) * NR_OF_CMD_RINGS,
			  mhi_ctxt->cmd_ctxt, mhi_ctxt->cmd_ctxt_addr);

	mhi_event = mhi_cntrl->mhi_event;
	क्रम (i = 0; i < mhi_cntrl->total_ev_rings; i++, mhi_event++) अणु
		अगर (mhi_event->offload_ev)
			जारी;

		ring = &mhi_event->ring;
		mhi_मुक्त_coherent(mhi_cntrl, ring->alloc_size,
				  ring->pre_aligned, ring->dma_handle);
		ring->base = शून्य;
		ring->iommu_base = 0;
	पूर्ण

	mhi_मुक्त_coherent(mhi_cntrl, माप(*mhi_ctxt->er_ctxt) *
			  mhi_cntrl->total_ev_rings, mhi_ctxt->er_ctxt,
			  mhi_ctxt->er_ctxt_addr);

	mhi_मुक्त_coherent(mhi_cntrl, माप(*mhi_ctxt->chan_ctxt) *
			  mhi_cntrl->max_chan, mhi_ctxt->chan_ctxt,
			  mhi_ctxt->chan_ctxt_addr);

	kमुक्त(mhi_ctxt);
	mhi_cntrl->mhi_ctxt = शून्य;
पूर्ण

पूर्णांक mhi_init_dev_ctxt(काष्ठा mhi_controller *mhi_cntrl)
अणु
	काष्ठा mhi_ctxt *mhi_ctxt;
	काष्ठा mhi_chan_ctxt *chan_ctxt;
	काष्ठा mhi_event_ctxt *er_ctxt;
	काष्ठा mhi_cmd_ctxt *cmd_ctxt;
	काष्ठा mhi_chan *mhi_chan;
	काष्ठा mhi_event *mhi_event;
	काष्ठा mhi_cmd *mhi_cmd;
	u32 पंचांगp;
	पूर्णांक ret = -ENOMEM, i;

	atomic_set(&mhi_cntrl->dev_wake, 0);
	atomic_set(&mhi_cntrl->pending_pkts, 0);

	mhi_ctxt = kzalloc(माप(*mhi_ctxt), GFP_KERNEL);
	अगर (!mhi_ctxt)
		वापस -ENOMEM;

	/* Setup channel ctxt */
	mhi_ctxt->chan_ctxt = mhi_alloc_coherent(mhi_cntrl,
						 माप(*mhi_ctxt->chan_ctxt) *
						 mhi_cntrl->max_chan,
						 &mhi_ctxt->chan_ctxt_addr,
						 GFP_KERNEL);
	अगर (!mhi_ctxt->chan_ctxt)
		जाओ error_alloc_chan_ctxt;

	mhi_chan = mhi_cntrl->mhi_chan;
	chan_ctxt = mhi_ctxt->chan_ctxt;
	क्रम (i = 0; i < mhi_cntrl->max_chan; i++, chan_ctxt++, mhi_chan++) अणु
		/* Skip अगर it is an offload channel */
		अगर (mhi_chan->offload_ch)
			जारी;

		पंचांगp = chan_ctxt->chcfg;
		पंचांगp &= ~CHAN_CTX_CHSTATE_MASK;
		पंचांगp |= (MHI_CH_STATE_DISABLED << CHAN_CTX_CHSTATE_SHIFT);
		पंचांगp &= ~CHAN_CTX_BRSTMODE_MASK;
		पंचांगp |= (mhi_chan->db_cfg.brsपंचांगode << CHAN_CTX_BRSTMODE_SHIFT);
		पंचांगp &= ~CHAN_CTX_POLLCFG_MASK;
		पंचांगp |= (mhi_chan->db_cfg.pollcfg << CHAN_CTX_POLLCFG_SHIFT);
		chan_ctxt->chcfg = पंचांगp;

		chan_ctxt->chtype = mhi_chan->type;
		chan_ctxt->erindex = mhi_chan->er_index;

		mhi_chan->ch_state = MHI_CH_STATE_DISABLED;
		mhi_chan->tre_ring.db_addr = (व्योम __iomem *)&chan_ctxt->wp;
	पूर्ण

	/* Setup event context */
	mhi_ctxt->er_ctxt = mhi_alloc_coherent(mhi_cntrl,
					       माप(*mhi_ctxt->er_ctxt) *
					       mhi_cntrl->total_ev_rings,
					       &mhi_ctxt->er_ctxt_addr,
					       GFP_KERNEL);
	अगर (!mhi_ctxt->er_ctxt)
		जाओ error_alloc_er_ctxt;

	er_ctxt = mhi_ctxt->er_ctxt;
	mhi_event = mhi_cntrl->mhi_event;
	क्रम (i = 0; i < mhi_cntrl->total_ev_rings; i++, er_ctxt++,
		     mhi_event++) अणु
		काष्ठा mhi_ring *ring = &mhi_event->ring;

		/* Skip अगर it is an offload event */
		अगर (mhi_event->offload_ev)
			जारी;

		पंचांगp = er_ctxt->पूर्णांकmod;
		पंचांगp &= ~EV_CTX_INTMODC_MASK;
		पंचांगp &= ~EV_CTX_INTMODT_MASK;
		पंचांगp |= (mhi_event->पूर्णांकmod << EV_CTX_INTMODT_SHIFT);
		er_ctxt->पूर्णांकmod = पंचांगp;

		er_ctxt->ertype = MHI_ER_TYPE_VALID;
		er_ctxt->msivec = mhi_event->irq;
		mhi_event->db_cfg.db_mode = true;

		ring->el_size = माप(काष्ठा mhi_tre);
		ring->len = ring->el_size * ring->elements;
		ret = mhi_alloc_aligned_ring(mhi_cntrl, ring, ring->len);
		अगर (ret)
			जाओ error_alloc_er;

		/*
		 * If the पढ़ो poपूर्णांकer equals to the ग_लिखो poपूर्णांकer, then the
		 * ring is empty
		 */
		ring->rp = ring->wp = ring->base;
		er_ctxt->rbase = ring->iommu_base;
		er_ctxt->rp = er_ctxt->wp = er_ctxt->rbase;
		er_ctxt->rlen = ring->len;
		ring->ctxt_wp = &er_ctxt->wp;
	पूर्ण

	/* Setup cmd context */
	ret = -ENOMEM;
	mhi_ctxt->cmd_ctxt = mhi_alloc_coherent(mhi_cntrl,
						माप(*mhi_ctxt->cmd_ctxt) *
						NR_OF_CMD_RINGS,
						&mhi_ctxt->cmd_ctxt_addr,
						GFP_KERNEL);
	अगर (!mhi_ctxt->cmd_ctxt)
		जाओ error_alloc_er;

	mhi_cmd = mhi_cntrl->mhi_cmd;
	cmd_ctxt = mhi_ctxt->cmd_ctxt;
	क्रम (i = 0; i < NR_OF_CMD_RINGS; i++, mhi_cmd++, cmd_ctxt++) अणु
		काष्ठा mhi_ring *ring = &mhi_cmd->ring;

		ring->el_size = माप(काष्ठा mhi_tre);
		ring->elements = CMD_EL_PER_RING;
		ring->len = ring->el_size * ring->elements;
		ret = mhi_alloc_aligned_ring(mhi_cntrl, ring, ring->len);
		अगर (ret)
			जाओ error_alloc_cmd;

		ring->rp = ring->wp = ring->base;
		cmd_ctxt->rbase = ring->iommu_base;
		cmd_ctxt->rp = cmd_ctxt->wp = cmd_ctxt->rbase;
		cmd_ctxt->rlen = ring->len;
		ring->ctxt_wp = &cmd_ctxt->wp;
	पूर्ण

	mhi_cntrl->mhi_ctxt = mhi_ctxt;

	वापस 0;

error_alloc_cmd:
	क्रम (--i, --mhi_cmd; i >= 0; i--, mhi_cmd--) अणु
		काष्ठा mhi_ring *ring = &mhi_cmd->ring;

		mhi_मुक्त_coherent(mhi_cntrl, ring->alloc_size,
				  ring->pre_aligned, ring->dma_handle);
	पूर्ण
	mhi_मुक्त_coherent(mhi_cntrl,
			  माप(*mhi_ctxt->cmd_ctxt) * NR_OF_CMD_RINGS,
			  mhi_ctxt->cmd_ctxt, mhi_ctxt->cmd_ctxt_addr);
	i = mhi_cntrl->total_ev_rings;
	mhi_event = mhi_cntrl->mhi_event + i;

error_alloc_er:
	क्रम (--i, --mhi_event; i >= 0; i--, mhi_event--) अणु
		काष्ठा mhi_ring *ring = &mhi_event->ring;

		अगर (mhi_event->offload_ev)
			जारी;

		mhi_मुक्त_coherent(mhi_cntrl, ring->alloc_size,
				  ring->pre_aligned, ring->dma_handle);
	पूर्ण
	mhi_मुक्त_coherent(mhi_cntrl, माप(*mhi_ctxt->er_ctxt) *
			  mhi_cntrl->total_ev_rings, mhi_ctxt->er_ctxt,
			  mhi_ctxt->er_ctxt_addr);

error_alloc_er_ctxt:
	mhi_मुक्त_coherent(mhi_cntrl, माप(*mhi_ctxt->chan_ctxt) *
			  mhi_cntrl->max_chan, mhi_ctxt->chan_ctxt,
			  mhi_ctxt->chan_ctxt_addr);

error_alloc_chan_ctxt:
	kमुक्त(mhi_ctxt);

	वापस ret;
पूर्ण

पूर्णांक mhi_init_mmio(काष्ठा mhi_controller *mhi_cntrl)
अणु
	u32 val;
	पूर्णांक i, ret;
	काष्ठा mhi_chan *mhi_chan;
	काष्ठा mhi_event *mhi_event;
	व्योम __iomem *base = mhi_cntrl->regs;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;
	काष्ठा अणु
		u32 offset;
		u32 mask;
		u32 shअगरt;
		u32 val;
	पूर्ण reg_info[] = अणु
		अणु
			CCABAP_HIGHER, U32_MAX, 0,
			upper_32_bits(mhi_cntrl->mhi_ctxt->chan_ctxt_addr),
		पूर्ण,
		अणु
			CCABAP_LOWER, U32_MAX, 0,
			lower_32_bits(mhi_cntrl->mhi_ctxt->chan_ctxt_addr),
		पूर्ण,
		अणु
			ECABAP_HIGHER, U32_MAX, 0,
			upper_32_bits(mhi_cntrl->mhi_ctxt->er_ctxt_addr),
		पूर्ण,
		अणु
			ECABAP_LOWER, U32_MAX, 0,
			lower_32_bits(mhi_cntrl->mhi_ctxt->er_ctxt_addr),
		पूर्ण,
		अणु
			CRCBAP_HIGHER, U32_MAX, 0,
			upper_32_bits(mhi_cntrl->mhi_ctxt->cmd_ctxt_addr),
		पूर्ण,
		अणु
			CRCBAP_LOWER, U32_MAX, 0,
			lower_32_bits(mhi_cntrl->mhi_ctxt->cmd_ctxt_addr),
		पूर्ण,
		अणु
			MHICFG, MHICFG_NER_MASK, MHICFG_NER_SHIFT,
			mhi_cntrl->total_ev_rings,
		पूर्ण,
		अणु
			MHICFG, MHICFG_NHWER_MASK, MHICFG_NHWER_SHIFT,
			mhi_cntrl->hw_ev_rings,
		पूर्ण,
		अणु
			MHICTRLBASE_HIGHER, U32_MAX, 0,
			upper_32_bits(mhi_cntrl->ioबहु_शुरू),
		पूर्ण,
		अणु
			MHICTRLBASE_LOWER, U32_MAX, 0,
			lower_32_bits(mhi_cntrl->ioबहु_शुरू),
		पूर्ण,
		अणु
			MHIDATABASE_HIGHER, U32_MAX, 0,
			upper_32_bits(mhi_cntrl->ioबहु_शुरू),
		पूर्ण,
		अणु
			MHIDATABASE_LOWER, U32_MAX, 0,
			lower_32_bits(mhi_cntrl->ioबहु_शुरू),
		पूर्ण,
		अणु
			MHICTRLLIMIT_HIGHER, U32_MAX, 0,
			upper_32_bits(mhi_cntrl->iova_stop),
		पूर्ण,
		अणु
			MHICTRLLIMIT_LOWER, U32_MAX, 0,
			lower_32_bits(mhi_cntrl->iova_stop),
		पूर्ण,
		अणु
			MHIDATALIMIT_HIGHER, U32_MAX, 0,
			upper_32_bits(mhi_cntrl->iova_stop),
		पूर्ण,
		अणु
			MHIDATALIMIT_LOWER, U32_MAX, 0,
			lower_32_bits(mhi_cntrl->iova_stop),
		पूर्ण,
		अणु 0, 0, 0 पूर्ण
	पूर्ण;

	dev_dbg(dev, "Initializing MHI registers\n");

	/* Read channel db offset */
	ret = mhi_पढ़ो_reg_field(mhi_cntrl, base, CHDBOFF, CHDBOFF_CHDBOFF_MASK,
				 CHDBOFF_CHDBOFF_SHIFT, &val);
	अगर (ret) अणु
		dev_err(dev, "Unable to read CHDBOFF register\n");
		वापस -EIO;
	पूर्ण

	/* Setup wake db */
	mhi_cntrl->wake_db = base + val + (8 * MHI_DEV_WAKE_DB);
	mhi_cntrl->wake_set = false;

	/* Setup channel db address क्रम each channel in tre_ring */
	mhi_chan = mhi_cntrl->mhi_chan;
	क्रम (i = 0; i < mhi_cntrl->max_chan; i++, val += 8, mhi_chan++)
		mhi_chan->tre_ring.db_addr = base + val;

	/* Read event ring db offset */
	ret = mhi_पढ़ो_reg_field(mhi_cntrl, base, ERDBOFF, ERDBOFF_ERDBOFF_MASK,
				 ERDBOFF_ERDBOFF_SHIFT, &val);
	अगर (ret) अणु
		dev_err(dev, "Unable to read ERDBOFF register\n");
		वापस -EIO;
	पूर्ण

	/* Setup event db address क्रम each ev_ring */
	mhi_event = mhi_cntrl->mhi_event;
	क्रम (i = 0; i < mhi_cntrl->total_ev_rings; i++, val += 8, mhi_event++) अणु
		अगर (mhi_event->offload_ev)
			जारी;

		mhi_event->ring.db_addr = base + val;
	पूर्ण

	/* Setup DB रेजिस्टर क्रम primary CMD rings */
	mhi_cntrl->mhi_cmd[PRIMARY_CMD_RING].ring.db_addr = base + CRDB_LOWER;

	/* Write to MMIO रेजिस्टरs */
	क्रम (i = 0; reg_info[i].offset; i++)
		mhi_ग_लिखो_reg_field(mhi_cntrl, base, reg_info[i].offset,
				    reg_info[i].mask, reg_info[i].shअगरt,
				    reg_info[i].val);

	वापस 0;
पूर्ण

व्योम mhi_deinit_chan_ctxt(काष्ठा mhi_controller *mhi_cntrl,
			  काष्ठा mhi_chan *mhi_chan)
अणु
	काष्ठा mhi_ring *buf_ring;
	काष्ठा mhi_ring *tre_ring;
	काष्ठा mhi_chan_ctxt *chan_ctxt;
	u32 पंचांगp;

	buf_ring = &mhi_chan->buf_ring;
	tre_ring = &mhi_chan->tre_ring;
	chan_ctxt = &mhi_cntrl->mhi_ctxt->chan_ctxt[mhi_chan->chan];

	अगर (!chan_ctxt->rbase) /* Alपढ़ोy uninitialized */
		वापस;

	mhi_मुक्त_coherent(mhi_cntrl, tre_ring->alloc_size,
			  tre_ring->pre_aligned, tre_ring->dma_handle);
	vमुक्त(buf_ring->base);

	buf_ring->base = tre_ring->base = शून्य;
	tre_ring->ctxt_wp = शून्य;
	chan_ctxt->rbase = 0;
	chan_ctxt->rlen = 0;
	chan_ctxt->rp = 0;
	chan_ctxt->wp = 0;

	पंचांगp = chan_ctxt->chcfg;
	पंचांगp &= ~CHAN_CTX_CHSTATE_MASK;
	पंचांगp |= (MHI_CH_STATE_DISABLED << CHAN_CTX_CHSTATE_SHIFT);
	chan_ctxt->chcfg = पंचांगp;

	/* Update to all cores */
	smp_wmb();
पूर्ण

पूर्णांक mhi_init_chan_ctxt(काष्ठा mhi_controller *mhi_cntrl,
		       काष्ठा mhi_chan *mhi_chan)
अणु
	काष्ठा mhi_ring *buf_ring;
	काष्ठा mhi_ring *tre_ring;
	काष्ठा mhi_chan_ctxt *chan_ctxt;
	u32 पंचांगp;
	पूर्णांक ret;

	buf_ring = &mhi_chan->buf_ring;
	tre_ring = &mhi_chan->tre_ring;
	tre_ring->el_size = माप(काष्ठा mhi_tre);
	tre_ring->len = tre_ring->el_size * tre_ring->elements;
	chan_ctxt = &mhi_cntrl->mhi_ctxt->chan_ctxt[mhi_chan->chan];
	ret = mhi_alloc_aligned_ring(mhi_cntrl, tre_ring, tre_ring->len);
	अगर (ret)
		वापस -ENOMEM;

	buf_ring->el_size = माप(काष्ठा mhi_buf_info);
	buf_ring->len = buf_ring->el_size * buf_ring->elements;
	buf_ring->base = vzalloc(buf_ring->len);

	अगर (!buf_ring->base) अणु
		mhi_मुक्त_coherent(mhi_cntrl, tre_ring->alloc_size,
				  tre_ring->pre_aligned, tre_ring->dma_handle);
		वापस -ENOMEM;
	पूर्ण

	पंचांगp = chan_ctxt->chcfg;
	पंचांगp &= ~CHAN_CTX_CHSTATE_MASK;
	पंचांगp |= (MHI_CH_STATE_ENABLED << CHAN_CTX_CHSTATE_SHIFT);
	chan_ctxt->chcfg = पंचांगp;

	chan_ctxt->rbase = tre_ring->iommu_base;
	chan_ctxt->rp = chan_ctxt->wp = chan_ctxt->rbase;
	chan_ctxt->rlen = tre_ring->len;
	tre_ring->ctxt_wp = &chan_ctxt->wp;

	tre_ring->rp = tre_ring->wp = tre_ring->base;
	buf_ring->rp = buf_ring->wp = buf_ring->base;
	mhi_chan->db_cfg.db_mode = 1;

	/* Update to all cores */
	smp_wmb();

	वापस 0;
पूर्ण

अटल पूर्णांक parse_ev_cfg(काष्ठा mhi_controller *mhi_cntrl,
			स्थिर काष्ठा mhi_controller_config *config)
अणु
	काष्ठा mhi_event *mhi_event;
	स्थिर काष्ठा mhi_event_config *event_cfg;
	काष्ठा device *dev = mhi_cntrl->cntrl_dev;
	पूर्णांक i, num;

	num = config->num_events;
	mhi_cntrl->total_ev_rings = num;
	mhi_cntrl->mhi_event = kसुस्मृति(num, माप(*mhi_cntrl->mhi_event),
				       GFP_KERNEL);
	अगर (!mhi_cntrl->mhi_event)
		वापस -ENOMEM;

	/* Populate event ring */
	mhi_event = mhi_cntrl->mhi_event;
	क्रम (i = 0; i < num; i++) अणु
		event_cfg = &config->event_cfg[i];

		mhi_event->er_index = i;
		mhi_event->ring.elements = event_cfg->num_elements;
		mhi_event->पूर्णांकmod = event_cfg->irq_moderation_ms;
		mhi_event->irq = event_cfg->irq;

		अगर (event_cfg->channel != U32_MAX) अणु
			/* This event ring has a dedicated channel */
			mhi_event->chan = event_cfg->channel;
			अगर (mhi_event->chan >= mhi_cntrl->max_chan) अणु
				dev_err(dev,
					"Event Ring channel not available\n");
				जाओ error_ev_cfg;
			पूर्ण

			mhi_event->mhi_chan =
				&mhi_cntrl->mhi_chan[mhi_event->chan];
		पूर्ण

		/* Priority is fixed to 1 क्रम now */
		mhi_event->priority = 1;

		mhi_event->db_cfg.brsपंचांगode = event_cfg->mode;
		अगर (MHI_INVALID_BRSTMODE(mhi_event->db_cfg.brsपंचांगode))
			जाओ error_ev_cfg;

		अगर (mhi_event->db_cfg.brsपंचांगode == MHI_DB_BRST_ENABLE)
			mhi_event->db_cfg.process_db = mhi_db_brsपंचांगode;
		अन्यथा
			mhi_event->db_cfg.process_db = mhi_db_brsपंचांगode_disable;

		mhi_event->data_type = event_cfg->data_type;

		चयन (mhi_event->data_type) अणु
		हाल MHI_ER_DATA:
			mhi_event->process_event = mhi_process_data_event_ring;
			अवरोध;
		हाल MHI_ER_CTRL:
			mhi_event->process_event = mhi_process_ctrl_ev_ring;
			अवरोध;
		शेष:
			dev_err(dev, "Event Ring type not supported\n");
			जाओ error_ev_cfg;
		पूर्ण

		mhi_event->hw_ring = event_cfg->hardware_event;
		अगर (mhi_event->hw_ring)
			mhi_cntrl->hw_ev_rings++;
		अन्यथा
			mhi_cntrl->sw_ev_rings++;

		mhi_event->cl_manage = event_cfg->client_managed;
		mhi_event->offload_ev = event_cfg->offload_channel;
		mhi_event++;
	पूर्ण

	वापस 0;

error_ev_cfg:

	kमुक्त(mhi_cntrl->mhi_event);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक parse_ch_cfg(काष्ठा mhi_controller *mhi_cntrl,
			स्थिर काष्ठा mhi_controller_config *config)
अणु
	स्थिर काष्ठा mhi_channel_config *ch_cfg;
	काष्ठा device *dev = mhi_cntrl->cntrl_dev;
	पूर्णांक i;
	u32 chan;

	mhi_cntrl->max_chan = config->max_channels;

	/*
	 * The allocation of MHI channels can exceed 32KB in some scenarios,
	 * so to aव्योम any memory possible allocation failures, vzalloc is
	 * used here
	 */
	mhi_cntrl->mhi_chan = vzalloc(mhi_cntrl->max_chan *
				      माप(*mhi_cntrl->mhi_chan));
	अगर (!mhi_cntrl->mhi_chan)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&mhi_cntrl->lpm_chans);

	/* Populate channel configurations */
	क्रम (i = 0; i < config->num_channels; i++) अणु
		काष्ठा mhi_chan *mhi_chan;

		ch_cfg = &config->ch_cfg[i];

		chan = ch_cfg->num;
		अगर (chan >= mhi_cntrl->max_chan) अणु
			dev_err(dev, "Channel %d not available\n", chan);
			जाओ error_chan_cfg;
		पूर्ण

		mhi_chan = &mhi_cntrl->mhi_chan[chan];
		mhi_chan->name = ch_cfg->name;
		mhi_chan->chan = chan;

		mhi_chan->tre_ring.elements = ch_cfg->num_elements;
		अगर (!mhi_chan->tre_ring.elements)
			जाओ error_chan_cfg;

		/*
		 * For some channels, local ring length should be bigger than
		 * the transfer ring length due to पूर्णांकernal logical channels
		 * in device. So host can queue much more buffers than transfer
		 * ring length. Example, RSC channels should have a larger local
		 * channel length than transfer ring length.
		 */
		mhi_chan->buf_ring.elements = ch_cfg->local_elements;
		अगर (!mhi_chan->buf_ring.elements)
			mhi_chan->buf_ring.elements = mhi_chan->tre_ring.elements;
		mhi_chan->er_index = ch_cfg->event_ring;
		mhi_chan->dir = ch_cfg->dir;

		/*
		 * For most channels, chtype is identical to channel directions.
		 * So, अगर it is not defined then assign channel direction to
		 * chtype
		 */
		mhi_chan->type = ch_cfg->type;
		अगर (!mhi_chan->type)
			mhi_chan->type = (क्रमागत mhi_ch_type)mhi_chan->dir;

		mhi_chan->ee_mask = ch_cfg->ee_mask;
		mhi_chan->db_cfg.pollcfg = ch_cfg->pollcfg;
		mhi_chan->lpm_notअगरy = ch_cfg->lpm_notअगरy;
		mhi_chan->offload_ch = ch_cfg->offload_channel;
		mhi_chan->db_cfg.reset_req = ch_cfg->करोorbell_mode_चयन;
		mhi_chan->pre_alloc = ch_cfg->स्वतः_queue;

		/*
		 * If MHI host allocates buffers, then the channel direction
		 * should be DMA_FROM_DEVICE
		 */
		अगर (mhi_chan->pre_alloc && mhi_chan->dir != DMA_FROM_DEVICE) अणु
			dev_err(dev, "Invalid channel configuration\n");
			जाओ error_chan_cfg;
		पूर्ण

		/*
		 * Bi-directional and direction less channel must be an
		 * offload channel
		 */
		अगर ((mhi_chan->dir == DMA_BIसूचीECTIONAL ||
		     mhi_chan->dir == DMA_NONE) && !mhi_chan->offload_ch) अणु
			dev_err(dev, "Invalid channel configuration\n");
			जाओ error_chan_cfg;
		पूर्ण

		अगर (!mhi_chan->offload_ch) अणु
			mhi_chan->db_cfg.brsपंचांगode = ch_cfg->करोorbell;
			अगर (MHI_INVALID_BRSTMODE(mhi_chan->db_cfg.brsपंचांगode)) अणु
				dev_err(dev, "Invalid Door bell mode\n");
				जाओ error_chan_cfg;
			पूर्ण
		पूर्ण

		अगर (mhi_chan->db_cfg.brsपंचांगode == MHI_DB_BRST_ENABLE)
			mhi_chan->db_cfg.process_db = mhi_db_brsपंचांगode;
		अन्यथा
			mhi_chan->db_cfg.process_db = mhi_db_brsपंचांगode_disable;

		mhi_chan->configured = true;

		अगर (mhi_chan->lpm_notअगरy)
			list_add_tail(&mhi_chan->node, &mhi_cntrl->lpm_chans);
	पूर्ण

	वापस 0;

error_chan_cfg:
	vमुक्त(mhi_cntrl->mhi_chan);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक parse_config(काष्ठा mhi_controller *mhi_cntrl,
			स्थिर काष्ठा mhi_controller_config *config)
अणु
	पूर्णांक ret;

	/* Parse MHI channel configuration */
	ret = parse_ch_cfg(mhi_cntrl, config);
	अगर (ret)
		वापस ret;

	/* Parse MHI event configuration */
	ret = parse_ev_cfg(mhi_cntrl, config);
	अगर (ret)
		जाओ error_ev_cfg;

	mhi_cntrl->समयout_ms = config->समयout_ms;
	अगर (!mhi_cntrl->समयout_ms)
		mhi_cntrl->समयout_ms = MHI_TIMEOUT_MS;

	mhi_cntrl->bounce_buf = config->use_bounce_buf;
	mhi_cntrl->buffer_len = config->buf_len;
	अगर (!mhi_cntrl->buffer_len)
		mhi_cntrl->buffer_len = MHI_MAX_MTU;

	/* By शेष, host is allowed to ring DB in both M0 and M2 states */
	mhi_cntrl->db_access = MHI_PM_M0 | MHI_PM_M2;
	अगर (config->m2_no_db)
		mhi_cntrl->db_access &= ~MHI_PM_M2;

	वापस 0;

error_ev_cfg:
	vमुक्त(mhi_cntrl->mhi_chan);

	वापस ret;
पूर्ण

पूर्णांक mhi_रेजिस्टर_controller(काष्ठा mhi_controller *mhi_cntrl,
			    स्थिर काष्ठा mhi_controller_config *config)
अणु
	काष्ठा mhi_event *mhi_event;
	काष्ठा mhi_chan *mhi_chan;
	काष्ठा mhi_cmd *mhi_cmd;
	काष्ठा mhi_device *mhi_dev;
	u32 soc_info;
	पूर्णांक ret, i;

	अगर (!mhi_cntrl || !mhi_cntrl->cntrl_dev || !mhi_cntrl->regs ||
	    !mhi_cntrl->runसमय_get || !mhi_cntrl->runसमय_put ||
	    !mhi_cntrl->status_cb || !mhi_cntrl->पढ़ो_reg ||
	    !mhi_cntrl->ग_लिखो_reg || !mhi_cntrl->nr_irqs || !mhi_cntrl->irq)
		वापस -EINVAL;

	ret = parse_config(mhi_cntrl, config);
	अगर (ret)
		वापस -EINVAL;

	mhi_cntrl->mhi_cmd = kसुस्मृति(NR_OF_CMD_RINGS,
				     माप(*mhi_cntrl->mhi_cmd), GFP_KERNEL);
	अगर (!mhi_cntrl->mhi_cmd) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_event;
	पूर्ण

	INIT_LIST_HEAD(&mhi_cntrl->transition_list);
	mutex_init(&mhi_cntrl->pm_mutex);
	rwlock_init(&mhi_cntrl->pm_lock);
	spin_lock_init(&mhi_cntrl->transition_lock);
	spin_lock_init(&mhi_cntrl->wlock);
	INIT_WORK(&mhi_cntrl->st_worker, mhi_pm_st_worker);
	init_रुकोqueue_head(&mhi_cntrl->state_event);

	mhi_cntrl->hiprio_wq = alloc_ordered_workqueue("mhi_hiprio_wq", WQ_HIGHPRI);
	अगर (!mhi_cntrl->hiprio_wq) अणु
		dev_err(mhi_cntrl->cntrl_dev, "Failed to allocate workqueue\n");
		ret = -ENOMEM;
		जाओ err_मुक्त_cmd;
	पूर्ण

	mhi_cmd = mhi_cntrl->mhi_cmd;
	क्रम (i = 0; i < NR_OF_CMD_RINGS; i++, mhi_cmd++)
		spin_lock_init(&mhi_cmd->lock);

	mhi_event = mhi_cntrl->mhi_event;
	क्रम (i = 0; i < mhi_cntrl->total_ev_rings; i++, mhi_event++) अणु
		/* Skip क्रम offload events */
		अगर (mhi_event->offload_ev)
			जारी;

		mhi_event->mhi_cntrl = mhi_cntrl;
		spin_lock_init(&mhi_event->lock);
		अगर (mhi_event->data_type == MHI_ER_CTRL)
			tasklet_init(&mhi_event->task, mhi_ctrl_ev_task,
				     (uदीर्घ)mhi_event);
		अन्यथा
			tasklet_init(&mhi_event->task, mhi_ev_task,
				     (uदीर्घ)mhi_event);
	पूर्ण

	mhi_chan = mhi_cntrl->mhi_chan;
	क्रम (i = 0; i < mhi_cntrl->max_chan; i++, mhi_chan++) अणु
		mutex_init(&mhi_chan->mutex);
		init_completion(&mhi_chan->completion);
		rwlock_init(&mhi_chan->lock);

		/* used in setting bei field of TRE */
		mhi_event = &mhi_cntrl->mhi_event[mhi_chan->er_index];
		mhi_chan->पूर्णांकmod = mhi_event->पूर्णांकmod;
	पूर्ण

	अगर (mhi_cntrl->bounce_buf) अणु
		mhi_cntrl->map_single = mhi_map_single_use_bb;
		mhi_cntrl->unmap_single = mhi_unmap_single_use_bb;
	पूर्ण अन्यथा अणु
		mhi_cntrl->map_single = mhi_map_single_no_bb;
		mhi_cntrl->unmap_single = mhi_unmap_single_no_bb;
	पूर्ण

	/* Read the MHI device info */
	ret = mhi_पढ़ो_reg(mhi_cntrl, mhi_cntrl->regs,
			   SOC_HW_VERSION_OFFS, &soc_info);
	अगर (ret)
		जाओ err_destroy_wq;

	mhi_cntrl->family_number = (soc_info & SOC_HW_VERSION_FAM_NUM_BMSK) >>
					SOC_HW_VERSION_FAM_NUM_SHFT;
	mhi_cntrl->device_number = (soc_info & SOC_HW_VERSION_DEV_NUM_BMSK) >>
					SOC_HW_VERSION_DEV_NUM_SHFT;
	mhi_cntrl->major_version = (soc_info & SOC_HW_VERSION_MAJOR_VER_BMSK) >>
					SOC_HW_VERSION_MAJOR_VER_SHFT;
	mhi_cntrl->minor_version = (soc_info & SOC_HW_VERSION_MINOR_VER_BMSK) >>
					SOC_HW_VERSION_MINOR_VER_SHFT;

	mhi_cntrl->index = ida_alloc(&mhi_controller_ida, GFP_KERNEL);
	अगर (mhi_cntrl->index < 0) अणु
		ret = mhi_cntrl->index;
		जाओ err_destroy_wq;
	पूर्ण

	/* Register controller with MHI bus */
	mhi_dev = mhi_alloc_device(mhi_cntrl);
	अगर (IS_ERR(mhi_dev)) अणु
		dev_err(mhi_cntrl->cntrl_dev, "Failed to allocate MHI device\n");
		ret = PTR_ERR(mhi_dev);
		जाओ err_ida_मुक्त;
	पूर्ण

	mhi_dev->dev_type = MHI_DEVICE_CONTROLLER;
	mhi_dev->mhi_cntrl = mhi_cntrl;
	dev_set_name(&mhi_dev->dev, "mhi%d", mhi_cntrl->index);
	mhi_dev->name = dev_name(&mhi_dev->dev);

	/* Init wakeup source */
	device_init_wakeup(&mhi_dev->dev, true);

	ret = device_add(&mhi_dev->dev);
	अगर (ret)
		जाओ err_release_dev;

	mhi_cntrl->mhi_dev = mhi_dev;

	mhi_create_debugfs(mhi_cntrl);

	वापस 0;

err_release_dev:
	put_device(&mhi_dev->dev);
err_ida_मुक्त:
	ida_मुक्त(&mhi_controller_ida, mhi_cntrl->index);
err_destroy_wq:
	destroy_workqueue(mhi_cntrl->hiprio_wq);
err_मुक्त_cmd:
	kमुक्त(mhi_cntrl->mhi_cmd);
err_मुक्त_event:
	kमुक्त(mhi_cntrl->mhi_event);
	vमुक्त(mhi_cntrl->mhi_chan);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mhi_रेजिस्टर_controller);

व्योम mhi_unरेजिस्टर_controller(काष्ठा mhi_controller *mhi_cntrl)
अणु
	काष्ठा mhi_device *mhi_dev = mhi_cntrl->mhi_dev;
	काष्ठा mhi_chan *mhi_chan = mhi_cntrl->mhi_chan;
	अचिन्हित पूर्णांक i;

	mhi_destroy_debugfs(mhi_cntrl);

	destroy_workqueue(mhi_cntrl->hiprio_wq);
	kमुक्त(mhi_cntrl->mhi_cmd);
	kमुक्त(mhi_cntrl->mhi_event);

	/* Drop the references to MHI devices created क्रम channels */
	क्रम (i = 0; i < mhi_cntrl->max_chan; i++, mhi_chan++) अणु
		अगर (!mhi_chan->mhi_dev)
			जारी;

		put_device(&mhi_chan->mhi_dev->dev);
	पूर्ण
	vमुक्त(mhi_cntrl->mhi_chan);

	device_del(&mhi_dev->dev);
	put_device(&mhi_dev->dev);

	ida_मुक्त(&mhi_controller_ida, mhi_cntrl->index);
पूर्ण
EXPORT_SYMBOL_GPL(mhi_unरेजिस्टर_controller);

काष्ठा mhi_controller *mhi_alloc_controller(व्योम)
अणु
	काष्ठा mhi_controller *mhi_cntrl;

	mhi_cntrl = kzalloc(माप(*mhi_cntrl), GFP_KERNEL);

	वापस mhi_cntrl;
पूर्ण
EXPORT_SYMBOL_GPL(mhi_alloc_controller);

व्योम mhi_मुक्त_controller(काष्ठा mhi_controller *mhi_cntrl)
अणु
	kमुक्त(mhi_cntrl);
पूर्ण
EXPORT_SYMBOL_GPL(mhi_मुक्त_controller);

पूर्णांक mhi_prepare_क्रम_घातer_up(काष्ठा mhi_controller *mhi_cntrl)
अणु
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;
	u32 bhie_off;
	पूर्णांक ret;

	mutex_lock(&mhi_cntrl->pm_mutex);

	ret = mhi_init_dev_ctxt(mhi_cntrl);
	अगर (ret)
		जाओ error_dev_ctxt;

	/*
	 * Allocate RDDM table अगर specअगरied, this table is क्रम debugging purpose
	 */
	अगर (mhi_cntrl->rddm_size) अणु
		mhi_alloc_bhie_table(mhi_cntrl, &mhi_cntrl->rddm_image,
				     mhi_cntrl->rddm_size);

		/*
		 * This controller supports RDDM, so we need to manually clear
		 * BHIE RX रेजिस्टरs since POR values are undefined.
		 */
		ret = mhi_पढ़ो_reg(mhi_cntrl, mhi_cntrl->regs, BHIखातापूर्णF,
				   &bhie_off);
		अगर (ret) अणु
			dev_err(dev, "Error getting BHIE offset\n");
			जाओ bhie_error;
		पूर्ण

		mhi_cntrl->bhie = mhi_cntrl->regs + bhie_off;
		स_रखो_io(mhi_cntrl->bhie + BHIE_RXVECADDR_LOW_OFFS,
			  0, BHIE_RXVECSTATUS_OFFS - BHIE_RXVECADDR_LOW_OFFS +
			  4);

		अगर (mhi_cntrl->rddm_image)
			mhi_rddm_prepare(mhi_cntrl, mhi_cntrl->rddm_image);
	पूर्ण

	mutex_unlock(&mhi_cntrl->pm_mutex);

	वापस 0;

bhie_error:
	अगर (mhi_cntrl->rddm_image) अणु
		mhi_मुक्त_bhie_table(mhi_cntrl, mhi_cntrl->rddm_image);
		mhi_cntrl->rddm_image = शून्य;
	पूर्ण

error_dev_ctxt:
	mutex_unlock(&mhi_cntrl->pm_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mhi_prepare_क्रम_घातer_up);

व्योम mhi_unprepare_after_घातer_करोwn(काष्ठा mhi_controller *mhi_cntrl)
अणु
	अगर (mhi_cntrl->fbc_image) अणु
		mhi_मुक्त_bhie_table(mhi_cntrl, mhi_cntrl->fbc_image);
		mhi_cntrl->fbc_image = शून्य;
	पूर्ण

	अगर (mhi_cntrl->rddm_image) अणु
		mhi_मुक्त_bhie_table(mhi_cntrl, mhi_cntrl->rddm_image);
		mhi_cntrl->rddm_image = शून्य;
	पूर्ण

	mhi_deinit_dev_ctxt(mhi_cntrl);
पूर्ण
EXPORT_SYMBOL_GPL(mhi_unprepare_after_घातer_करोwn);

अटल व्योम mhi_release_device(काष्ठा device *dev)
अणु
	काष्ठा mhi_device *mhi_dev = to_mhi_device(dev);

	/*
	 * We need to set the mhi_chan->mhi_dev to शून्य here since the MHI
	 * devices क्रम the channels will only get created अगर the mhi_dev
	 * associated with it is शून्य. This scenario will happen during the
	 * controller suspend and resume.
	 */
	अगर (mhi_dev->ul_chan)
		mhi_dev->ul_chan->mhi_dev = शून्य;

	अगर (mhi_dev->dl_chan)
		mhi_dev->dl_chan->mhi_dev = शून्य;

	kमुक्त(mhi_dev);
पूर्ण

काष्ठा mhi_device *mhi_alloc_device(काष्ठा mhi_controller *mhi_cntrl)
अणु
	काष्ठा mhi_device *mhi_dev;
	काष्ठा device *dev;

	mhi_dev = kzalloc(माप(*mhi_dev), GFP_KERNEL);
	अगर (!mhi_dev)
		वापस ERR_PTR(-ENOMEM);

	dev = &mhi_dev->dev;
	device_initialize(dev);
	dev->bus = &mhi_bus_type;
	dev->release = mhi_release_device;

	अगर (mhi_cntrl->mhi_dev) अणु
		/* क्रम MHI client devices, parent is the MHI controller device */
		dev->parent = &mhi_cntrl->mhi_dev->dev;
	पूर्ण अन्यथा अणु
		/* क्रम MHI controller device, parent is the bus device (e.g. pci device) */
		dev->parent = mhi_cntrl->cntrl_dev;
	पूर्ण

	mhi_dev->mhi_cntrl = mhi_cntrl;
	mhi_dev->dev_wake = 0;

	वापस mhi_dev;
पूर्ण

अटल पूर्णांक mhi_driver_probe(काष्ठा device *dev)
अणु
	काष्ठा mhi_device *mhi_dev = to_mhi_device(dev);
	काष्ठा mhi_controller *mhi_cntrl = mhi_dev->mhi_cntrl;
	काष्ठा device_driver *drv = dev->driver;
	काष्ठा mhi_driver *mhi_drv = to_mhi_driver(drv);
	काष्ठा mhi_event *mhi_event;
	काष्ठा mhi_chan *ul_chan = mhi_dev->ul_chan;
	काष्ठा mhi_chan *dl_chan = mhi_dev->dl_chan;
	पूर्णांक ret;

	/* Bring device out of LPM */
	ret = mhi_device_get_sync(mhi_dev);
	अगर (ret)
		वापस ret;

	ret = -EINVAL;

	अगर (ul_chan) अणु
		/*
		 * If channel supports LPM notअगरications then status_cb should
		 * be provided
		 */
		अगर (ul_chan->lpm_notअगरy && !mhi_drv->status_cb)
			जाओ निकास_probe;

		/* For non-offload channels then xfer_cb should be provided */
		अगर (!ul_chan->offload_ch && !mhi_drv->ul_xfer_cb)
			जाओ निकास_probe;

		ul_chan->xfer_cb = mhi_drv->ul_xfer_cb;
	पूर्ण

	ret = -EINVAL;
	अगर (dl_chan) अणु
		/*
		 * If channel supports LPM notअगरications then status_cb should
		 * be provided
		 */
		अगर (dl_chan->lpm_notअगरy && !mhi_drv->status_cb)
			जाओ निकास_probe;

		/* For non-offload channels then xfer_cb should be provided */
		अगर (!dl_chan->offload_ch && !mhi_drv->dl_xfer_cb)
			जाओ निकास_probe;

		mhi_event = &mhi_cntrl->mhi_event[dl_chan->er_index];

		/*
		 * If the channel event ring is managed by client, then
		 * status_cb must be provided so that the framework can
		 * notअगरy pending data
		 */
		अगर (mhi_event->cl_manage && !mhi_drv->status_cb)
			जाओ निकास_probe;

		dl_chan->xfer_cb = mhi_drv->dl_xfer_cb;
	पूर्ण

	/* Call the user provided probe function */
	ret = mhi_drv->probe(mhi_dev, mhi_dev->id);
	अगर (ret)
		जाओ निकास_probe;

	mhi_device_put(mhi_dev);

	वापस ret;

निकास_probe:
	mhi_unprepare_from_transfer(mhi_dev);

	mhi_device_put(mhi_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक mhi_driver_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा mhi_device *mhi_dev = to_mhi_device(dev);
	काष्ठा mhi_driver *mhi_drv = to_mhi_driver(dev->driver);
	काष्ठा mhi_controller *mhi_cntrl = mhi_dev->mhi_cntrl;
	काष्ठा mhi_chan *mhi_chan;
	क्रमागत mhi_ch_state ch_state[] = अणु
		MHI_CH_STATE_DISABLED,
		MHI_CH_STATE_DISABLED
	पूर्ण;
	पूर्णांक dir;

	/* Skip अगर it is a controller device */
	अगर (mhi_dev->dev_type == MHI_DEVICE_CONTROLLER)
		वापस 0;

	/* Reset both channels */
	क्रम (dir = 0; dir < 2; dir++) अणु
		mhi_chan = dir ? mhi_dev->ul_chan : mhi_dev->dl_chan;

		अगर (!mhi_chan)
			जारी;

		/* Wake all thपढ़ोs रुकोing क्रम completion */
		ग_लिखो_lock_irq(&mhi_chan->lock);
		mhi_chan->ccs = MHI_EV_CC_INVALID;
		complete_all(&mhi_chan->completion);
		ग_लिखो_unlock_irq(&mhi_chan->lock);

		/* Set the channel state to disabled */
		mutex_lock(&mhi_chan->mutex);
		ग_लिखो_lock_irq(&mhi_chan->lock);
		ch_state[dir] = mhi_chan->ch_state;
		mhi_chan->ch_state = MHI_CH_STATE_SUSPENDED;
		ग_लिखो_unlock_irq(&mhi_chan->lock);

		/* Reset the non-offload channel */
		अगर (!mhi_chan->offload_ch)
			mhi_reset_chan(mhi_cntrl, mhi_chan);

		mutex_unlock(&mhi_chan->mutex);
	पूर्ण

	mhi_drv->हटाओ(mhi_dev);

	/* De-init channel अगर it was enabled */
	क्रम (dir = 0; dir < 2; dir++) अणु
		mhi_chan = dir ? mhi_dev->ul_chan : mhi_dev->dl_chan;

		अगर (!mhi_chan)
			जारी;

		mutex_lock(&mhi_chan->mutex);

		अगर ((ch_state[dir] == MHI_CH_STATE_ENABLED ||
		     ch_state[dir] == MHI_CH_STATE_STOP) &&
		    !mhi_chan->offload_ch)
			mhi_deinit_chan_ctxt(mhi_cntrl, mhi_chan);

		mhi_chan->ch_state = MHI_CH_STATE_DISABLED;

		mutex_unlock(&mhi_chan->mutex);
	पूर्ण

	जबतक (mhi_dev->dev_wake)
		mhi_device_put(mhi_dev);

	वापस 0;
पूर्ण

पूर्णांक __mhi_driver_रेजिस्टर(काष्ठा mhi_driver *mhi_drv, काष्ठा module *owner)
अणु
	काष्ठा device_driver *driver = &mhi_drv->driver;

	अगर (!mhi_drv->probe || !mhi_drv->हटाओ)
		वापस -EINVAL;

	driver->bus = &mhi_bus_type;
	driver->owner = owner;
	driver->probe = mhi_driver_probe;
	driver->हटाओ = mhi_driver_हटाओ;

	वापस driver_रेजिस्टर(driver);
पूर्ण
EXPORT_SYMBOL_GPL(__mhi_driver_रेजिस्टर);

व्योम mhi_driver_unरेजिस्टर(काष्ठा mhi_driver *mhi_drv)
अणु
	driver_unरेजिस्टर(&mhi_drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(mhi_driver_unरेजिस्टर);

अटल पूर्णांक mhi_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा mhi_device *mhi_dev = to_mhi_device(dev);

	वापस add_uevent_var(env, "MODALIAS=" MHI_DEVICE_MODALIAS_FMT,
					mhi_dev->name);
पूर्ण

अटल पूर्णांक mhi_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा mhi_device *mhi_dev = to_mhi_device(dev);
	काष्ठा mhi_driver *mhi_drv = to_mhi_driver(drv);
	स्थिर काष्ठा mhi_device_id *id;

	/*
	 * If the device is a controller type then there is no client driver
	 * associated with it
	 */
	अगर (mhi_dev->dev_type == MHI_DEVICE_CONTROLLER)
		वापस 0;

	क्रम (id = mhi_drv->id_table; id->chan[0]; id++)
		अगर (!म_भेद(mhi_dev->name, id->chan)) अणु
			mhi_dev->id = id;
			वापस 1;
		पूर्ण

	वापस 0;
पूर्ण;

काष्ठा bus_type mhi_bus_type = अणु
	.name = "mhi",
	.dev_name = "mhi",
	.match = mhi_match,
	.uevent = mhi_uevent,
	.dev_groups = mhi_dev_groups,
पूर्ण;

अटल पूर्णांक __init mhi_init(व्योम)
अणु
	mhi_debugfs_init();
	वापस bus_रेजिस्टर(&mhi_bus_type);
पूर्ण

अटल व्योम __निकास mhi_निकास(व्योम)
अणु
	mhi_debugfs_निकास();
	bus_unरेजिस्टर(&mhi_bus_type);
पूर्ण

postcore_initcall(mhi_init);
module_निकास(mhi_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MHI Host Interface");
