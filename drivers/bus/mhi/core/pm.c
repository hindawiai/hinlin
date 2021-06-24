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
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>
#समावेश "internal.h"

/*
 * Not all MHI state transitions are synchronous. Transitions like Linkकरोwn,
 * SYS_ERR, and shutकरोwn can happen anyसमय asynchronously. This function will
 * transition to a new state only अगर we're allowed to.
 *
 * Priority increases as we go करोwn. For instance, from any state in L0, the
 * transition can be made to states in L1, L2 and L3. A notable exception to
 * this rule is state DISABLE.  From DISABLE state we can only transition to
 * POR state. Also, जबतक in L2 state, user cannot jump back to previous
 * L1 or L0 states.
 *
 * Valid transitions:
 * L0: DISABLE <--> POR
 *     POR <--> POR
 *     POR -> M0 -> M2 --> M0
 *     POR -> FW_DL_ERR
 *     FW_DL_ERR <--> FW_DL_ERR
 *     M0 <--> M0
 *     M0 -> FW_DL_ERR
 *     M0 -> M3_ENTER -> M3 -> M3_EXIT --> M0
 * L1: SYS_ERR_DETECT -> SYS_ERR_PROCESS --> POR
 * L2: SHUTDOWN_PROCESS -> LD_ERR_FATAL_DETECT
 *     SHUTDOWN_PROCESS -> DISABLE
 * L3: LD_ERR_FATAL_DETECT <--> LD_ERR_FATAL_DETECT
 *     LD_ERR_FATAL_DETECT -> DISABLE
 */
अटल काष्ठा mhi_pm_transitions स्थिर dev_state_transitions[] = अणु
	/* L0 States */
	अणु
		MHI_PM_DISABLE,
		MHI_PM_POR
	पूर्ण,
	अणु
		MHI_PM_POR,
		MHI_PM_POR | MHI_PM_DISABLE | MHI_PM_M0 |
		MHI_PM_SYS_ERR_DETECT | MHI_PM_SHUTDOWN_PROCESS |
		MHI_PM_LD_ERR_FATAL_DETECT | MHI_PM_FW_DL_ERR
	पूर्ण,
	अणु
		MHI_PM_M0,
		MHI_PM_M0 | MHI_PM_M2 | MHI_PM_M3_ENTER |
		MHI_PM_SYS_ERR_DETECT | MHI_PM_SHUTDOWN_PROCESS |
		MHI_PM_LD_ERR_FATAL_DETECT | MHI_PM_FW_DL_ERR
	पूर्ण,
	अणु
		MHI_PM_M2,
		MHI_PM_M0 | MHI_PM_SYS_ERR_DETECT | MHI_PM_SHUTDOWN_PROCESS |
		MHI_PM_LD_ERR_FATAL_DETECT
	पूर्ण,
	अणु
		MHI_PM_M3_ENTER,
		MHI_PM_M3 | MHI_PM_SYS_ERR_DETECT | MHI_PM_SHUTDOWN_PROCESS |
		MHI_PM_LD_ERR_FATAL_DETECT
	पूर्ण,
	अणु
		MHI_PM_M3,
		MHI_PM_M3_EXIT | MHI_PM_SYS_ERR_DETECT |
		MHI_PM_LD_ERR_FATAL_DETECT
	पूर्ण,
	अणु
		MHI_PM_M3_EXIT,
		MHI_PM_M0 | MHI_PM_SYS_ERR_DETECT | MHI_PM_SHUTDOWN_PROCESS |
		MHI_PM_LD_ERR_FATAL_DETECT
	पूर्ण,
	अणु
		MHI_PM_FW_DL_ERR,
		MHI_PM_FW_DL_ERR | MHI_PM_SYS_ERR_DETECT |
		MHI_PM_SHUTDOWN_PROCESS | MHI_PM_LD_ERR_FATAL_DETECT
	पूर्ण,
	/* L1 States */
	अणु
		MHI_PM_SYS_ERR_DETECT,
		MHI_PM_SYS_ERR_PROCESS | MHI_PM_SHUTDOWN_PROCESS |
		MHI_PM_LD_ERR_FATAL_DETECT
	पूर्ण,
	अणु
		MHI_PM_SYS_ERR_PROCESS,
		MHI_PM_POR | MHI_PM_SHUTDOWN_PROCESS |
		MHI_PM_LD_ERR_FATAL_DETECT
	पूर्ण,
	/* L2 States */
	अणु
		MHI_PM_SHUTDOWN_PROCESS,
		MHI_PM_DISABLE | MHI_PM_LD_ERR_FATAL_DETECT
	पूर्ण,
	/* L3 States */
	अणु
		MHI_PM_LD_ERR_FATAL_DETECT,
		MHI_PM_LD_ERR_FATAL_DETECT | MHI_PM_DISABLE
	पूर्ण,
पूर्ण;

क्रमागत mhi_pm_state __must_check mhi_tryset_pm_state(काष्ठा mhi_controller *mhi_cntrl,
						   क्रमागत mhi_pm_state state)
अणु
	अचिन्हित दीर्घ cur_state = mhi_cntrl->pm_state;
	पूर्णांक index = find_last_bit(&cur_state, 32);

	अगर (unlikely(index >= ARRAY_SIZE(dev_state_transitions)))
		वापस cur_state;

	अगर (unlikely(dev_state_transitions[index].from_state != cur_state))
		वापस cur_state;

	अगर (unlikely(!(dev_state_transitions[index].to_states & state)))
		वापस cur_state;

	mhi_cntrl->pm_state = state;
	वापस mhi_cntrl->pm_state;
पूर्ण

व्योम mhi_set_mhi_state(काष्ठा mhi_controller *mhi_cntrl, क्रमागत mhi_state state)
अणु
	अगर (state == MHI_STATE_RESET) अणु
		mhi_ग_लिखो_reg_field(mhi_cntrl, mhi_cntrl->regs, MHICTRL,
				    MHICTRL_RESET_MASK, MHICTRL_RESET_SHIFT, 1);
	पूर्ण अन्यथा अणु
		mhi_ग_लिखो_reg_field(mhi_cntrl, mhi_cntrl->regs, MHICTRL,
				    MHICTRL_MHISTATE_MASK,
				    MHICTRL_MHISTATE_SHIFT, state);
	पूर्ण
पूर्ण

/* NOP क्रम backward compatibility, host allowed to ring DB in M2 state */
अटल व्योम mhi_toggle_dev_wake_nop(काष्ठा mhi_controller *mhi_cntrl)
अणु
पूर्ण

अटल व्योम mhi_toggle_dev_wake(काष्ठा mhi_controller *mhi_cntrl)
अणु
	mhi_cntrl->wake_get(mhi_cntrl, false);
	mhi_cntrl->wake_put(mhi_cntrl, true);
पूर्ण

/* Handle device पढ़ोy state transition */
पूर्णांक mhi_पढ़ोy_state_transition(काष्ठा mhi_controller *mhi_cntrl)
अणु
	काष्ठा mhi_event *mhi_event;
	क्रमागत mhi_pm_state cur_state;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;
	u32 पूर्णांकerval_us = 25000; /* poll रेजिस्टर field every 25 milliseconds */
	पूर्णांक ret, i;

	/* Check अगर device entered error state */
	अगर (MHI_PM_IN_FATAL_STATE(mhi_cntrl->pm_state)) अणु
		dev_err(dev, "Device link is not accessible\n");
		वापस -EIO;
	पूर्ण

	/* Wait क्रम RESET to be cleared and READY bit to be set by the device */
	ret = mhi_poll_reg_field(mhi_cntrl, mhi_cntrl->regs, MHICTRL,
				 MHICTRL_RESET_MASK, MHICTRL_RESET_SHIFT, 0,
				 पूर्णांकerval_us);
	अगर (ret) अणु
		dev_err(dev, "Device failed to clear MHI Reset\n");
		वापस ret;
	पूर्ण

	ret = mhi_poll_reg_field(mhi_cntrl, mhi_cntrl->regs, MHISTATUS,
				 MHISTATUS_READY_MASK, MHISTATUS_READY_SHIFT, 1,
				 पूर्णांकerval_us);
	अगर (ret) अणु
		dev_err(dev, "Device failed to enter MHI Ready\n");
		वापस ret;
	पूर्ण

	dev_dbg(dev, "Device in READY State\n");
	ग_लिखो_lock_irq(&mhi_cntrl->pm_lock);
	cur_state = mhi_tryset_pm_state(mhi_cntrl, MHI_PM_POR);
	mhi_cntrl->dev_state = MHI_STATE_READY;
	ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);

	अगर (cur_state != MHI_PM_POR) अणु
		dev_err(dev, "Error moving to state %s from %s\n",
			to_mhi_pm_state_str(MHI_PM_POR),
			to_mhi_pm_state_str(cur_state));
		वापस -EIO;
	पूर्ण

	पढ़ो_lock_bh(&mhi_cntrl->pm_lock);
	अगर (!MHI_REG_ACCESS_VALID(mhi_cntrl->pm_state)) अणु
		dev_err(dev, "Device registers not accessible\n");
		जाओ error_mmio;
	पूर्ण

	/* Configure MMIO रेजिस्टरs */
	ret = mhi_init_mmio(mhi_cntrl);
	अगर (ret) अणु
		dev_err(dev, "Error configuring MMIO registers\n");
		जाओ error_mmio;
	पूर्ण

	/* Add elements to all SW event rings */
	mhi_event = mhi_cntrl->mhi_event;
	क्रम (i = 0; i < mhi_cntrl->total_ev_rings; i++, mhi_event++) अणु
		काष्ठा mhi_ring *ring = &mhi_event->ring;

		/* Skip अगर this is an offload or HW event */
		अगर (mhi_event->offload_ev || mhi_event->hw_ring)
			जारी;

		ring->wp = ring->base + ring->len - ring->el_size;
		*ring->ctxt_wp = ring->iommu_base + ring->len - ring->el_size;
		/* Update all cores */
		smp_wmb();

		/* Ring the event ring db */
		spin_lock_irq(&mhi_event->lock);
		mhi_ring_er_db(mhi_event);
		spin_unlock_irq(&mhi_event->lock);
	पूर्ण

	/* Set MHI to M0 state */
	mhi_set_mhi_state(mhi_cntrl, MHI_STATE_M0);
	पढ़ो_unlock_bh(&mhi_cntrl->pm_lock);

	वापस 0;

error_mmio:
	पढ़ो_unlock_bh(&mhi_cntrl->pm_lock);

	वापस -EIO;
पूर्ण

पूर्णांक mhi_pm_m0_transition(काष्ठा mhi_controller *mhi_cntrl)
अणु
	क्रमागत mhi_pm_state cur_state;
	काष्ठा mhi_chan *mhi_chan;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;
	पूर्णांक i;

	ग_लिखो_lock_irq(&mhi_cntrl->pm_lock);
	mhi_cntrl->dev_state = MHI_STATE_M0;
	cur_state = mhi_tryset_pm_state(mhi_cntrl, MHI_PM_M0);
	ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);
	अगर (unlikely(cur_state != MHI_PM_M0)) अणु
		dev_err(dev, "Unable to transition to M0 state\n");
		वापस -EIO;
	पूर्ण
	mhi_cntrl->M0++;

	/* Wake up the device */
	पढ़ो_lock_bh(&mhi_cntrl->pm_lock);
	mhi_cntrl->wake_get(mhi_cntrl, true);

	/* Ring all event rings and CMD ring only अगर we're in mission mode */
	अगर (MHI_IN_MISSION_MODE(mhi_cntrl->ee)) अणु
		काष्ठा mhi_event *mhi_event = mhi_cntrl->mhi_event;
		काष्ठा mhi_cmd *mhi_cmd =
			&mhi_cntrl->mhi_cmd[PRIMARY_CMD_RING];

		क्रम (i = 0; i < mhi_cntrl->total_ev_rings; i++, mhi_event++) अणु
			अगर (mhi_event->offload_ev)
				जारी;

			spin_lock_irq(&mhi_event->lock);
			mhi_ring_er_db(mhi_event);
			spin_unlock_irq(&mhi_event->lock);
		पूर्ण

		/* Only ring primary cmd ring अगर ring is not empty */
		spin_lock_irq(&mhi_cmd->lock);
		अगर (mhi_cmd->ring.rp != mhi_cmd->ring.wp)
			mhi_ring_cmd_db(mhi_cntrl, mhi_cmd);
		spin_unlock_irq(&mhi_cmd->lock);
	पूर्ण

	/* Ring channel DB रेजिस्टरs */
	mhi_chan = mhi_cntrl->mhi_chan;
	क्रम (i = 0; i < mhi_cntrl->max_chan; i++, mhi_chan++) अणु
		काष्ठा mhi_ring *tre_ring = &mhi_chan->tre_ring;

		अगर (mhi_chan->db_cfg.reset_req) अणु
			ग_लिखो_lock_irq(&mhi_chan->lock);
			mhi_chan->db_cfg.db_mode = true;
			ग_लिखो_unlock_irq(&mhi_chan->lock);
		पूर्ण

		पढ़ो_lock_irq(&mhi_chan->lock);

		/* Only ring DB अगर ring is not empty */
		अगर (tre_ring->base && tre_ring->wp  != tre_ring->rp)
			mhi_ring_chan_db(mhi_cntrl, mhi_chan);
		पढ़ो_unlock_irq(&mhi_chan->lock);
	पूर्ण

	mhi_cntrl->wake_put(mhi_cntrl, false);
	पढ़ो_unlock_bh(&mhi_cntrl->pm_lock);
	wake_up_all(&mhi_cntrl->state_event);

	वापस 0;
पूर्ण

/*
 * After receiving the MHI state change event from the device indicating the
 * transition to M1 state, the host can transition the device to M2 state
 * क्रम keeping it in low घातer state.
 */
व्योम mhi_pm_m1_transition(काष्ठा mhi_controller *mhi_cntrl)
अणु
	क्रमागत mhi_pm_state state;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;

	ग_लिखो_lock_irq(&mhi_cntrl->pm_lock);
	state = mhi_tryset_pm_state(mhi_cntrl, MHI_PM_M2);
	अगर (state == MHI_PM_M2) अणु
		mhi_set_mhi_state(mhi_cntrl, MHI_STATE_M2);
		mhi_cntrl->dev_state = MHI_STATE_M2;

		ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);

		mhi_cntrl->M2++;
		wake_up_all(&mhi_cntrl->state_event);

		/* If there are any pending resources, निकास M2 immediately */
		अगर (unlikely(atomic_पढ़ो(&mhi_cntrl->pending_pkts) ||
			     atomic_पढ़ो(&mhi_cntrl->dev_wake))) अणु
			dev_dbg(dev,
				"Exiting M2, pending_pkts: %d dev_wake: %d\n",
				atomic_पढ़ो(&mhi_cntrl->pending_pkts),
				atomic_पढ़ो(&mhi_cntrl->dev_wake));
			पढ़ो_lock_bh(&mhi_cntrl->pm_lock);
			mhi_cntrl->wake_get(mhi_cntrl, true);
			mhi_cntrl->wake_put(mhi_cntrl, true);
			पढ़ो_unlock_bh(&mhi_cntrl->pm_lock);
		पूर्ण अन्यथा अणु
			mhi_cntrl->status_cb(mhi_cntrl, MHI_CB_IDLE);
		पूर्ण
	पूर्ण अन्यथा अणु
		ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);
	पूर्ण
पूर्ण

/* MHI M3 completion handler */
पूर्णांक mhi_pm_m3_transition(काष्ठा mhi_controller *mhi_cntrl)
अणु
	क्रमागत mhi_pm_state state;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;

	ग_लिखो_lock_irq(&mhi_cntrl->pm_lock);
	mhi_cntrl->dev_state = MHI_STATE_M3;
	state = mhi_tryset_pm_state(mhi_cntrl, MHI_PM_M3);
	ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);
	अगर (state != MHI_PM_M3) अणु
		dev_err(dev, "Unable to transition to M3 state\n");
		वापस -EIO;
	पूर्ण

	mhi_cntrl->M3++;
	wake_up_all(&mhi_cntrl->state_event);

	वापस 0;
पूर्ण

/* Handle device Mission Mode transition */
अटल पूर्णांक mhi_pm_mission_mode_transition(काष्ठा mhi_controller *mhi_cntrl)
अणु
	काष्ठा mhi_event *mhi_event;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;
	क्रमागत mhi_ee_type ee = MHI_EE_MAX, current_ee = mhi_cntrl->ee;
	पूर्णांक i, ret;

	dev_dbg(dev, "Processing Mission Mode transition\n");

	ग_लिखो_lock_irq(&mhi_cntrl->pm_lock);
	अगर (MHI_REG_ACCESS_VALID(mhi_cntrl->pm_state))
		ee = mhi_get_exec_env(mhi_cntrl);

	अगर (!MHI_IN_MISSION_MODE(ee)) अणु
		mhi_cntrl->pm_state = MHI_PM_LD_ERR_FATAL_DETECT;
		ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);
		wake_up_all(&mhi_cntrl->state_event);
		वापस -EIO;
	पूर्ण
	mhi_cntrl->ee = ee;
	ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);

	wake_up_all(&mhi_cntrl->state_event);

	device_क्रम_each_child(&mhi_cntrl->mhi_dev->dev, &current_ee,
			      mhi_destroy_device);
	mhi_cntrl->status_cb(mhi_cntrl, MHI_CB_EE_MISSION_MODE);

	/* Force MHI to be in M0 state beक्रमe continuing */
	ret = __mhi_device_get_sync(mhi_cntrl);
	अगर (ret)
		वापस ret;

	पढ़ो_lock_bh(&mhi_cntrl->pm_lock);

	अगर (MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state)) अणु
		ret = -EIO;
		जाओ error_mission_mode;
	पूर्ण

	/* Add elements to all HW event rings */
	mhi_event = mhi_cntrl->mhi_event;
	क्रम (i = 0; i < mhi_cntrl->total_ev_rings; i++, mhi_event++) अणु
		काष्ठा mhi_ring *ring = &mhi_event->ring;

		अगर (mhi_event->offload_ev || !mhi_event->hw_ring)
			जारी;

		ring->wp = ring->base + ring->len - ring->el_size;
		*ring->ctxt_wp = ring->iommu_base + ring->len - ring->el_size;
		/* Update to all cores */
		smp_wmb();

		spin_lock_irq(&mhi_event->lock);
		अगर (MHI_DB_ACCESS_VALID(mhi_cntrl))
			mhi_ring_er_db(mhi_event);
		spin_unlock_irq(&mhi_event->lock);
	पूर्ण

	पढ़ो_unlock_bh(&mhi_cntrl->pm_lock);

	/*
	 * The MHI devices are only created when the client device चयनes its
	 * Execution Environment (EE) to either SBL or AMSS states
	 */
	mhi_create_devices(mhi_cntrl);

	पढ़ो_lock_bh(&mhi_cntrl->pm_lock);

error_mission_mode:
	mhi_cntrl->wake_put(mhi_cntrl, false);
	पढ़ो_unlock_bh(&mhi_cntrl->pm_lock);

	वापस ret;
पूर्ण

/* Handle shutकरोwn transitions */
अटल व्योम mhi_pm_disable_transition(काष्ठा mhi_controller *mhi_cntrl)
अणु
	क्रमागत mhi_pm_state cur_state;
	काष्ठा mhi_event *mhi_event;
	काष्ठा mhi_cmd_ctxt *cmd_ctxt;
	काष्ठा mhi_cmd *mhi_cmd;
	काष्ठा mhi_event_ctxt *er_ctxt;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;
	पूर्णांक ret, i;

	dev_dbg(dev, "Processing disable transition with PM state: %s\n",
		to_mhi_pm_state_str(mhi_cntrl->pm_state));

	mutex_lock(&mhi_cntrl->pm_mutex);

	/* Trigger MHI RESET so that the device will not access host memory */
	अगर (!MHI_PM_IN_FATAL_STATE(mhi_cntrl->pm_state)) अणु
		u32 in_reset = -1;
		अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(mhi_cntrl->समयout_ms);

		dev_dbg(dev, "Triggering MHI Reset in device\n");
		mhi_set_mhi_state(mhi_cntrl, MHI_STATE_RESET);

		/* Wait क्रम the reset bit to be cleared by the device */
		ret = रुको_event_समयout(mhi_cntrl->state_event,
					 mhi_पढ़ो_reg_field(mhi_cntrl,
							    mhi_cntrl->regs,
							    MHICTRL,
							    MHICTRL_RESET_MASK,
							    MHICTRL_RESET_SHIFT,
							    &in_reset) ||
					!in_reset, समयout);
		अगर (!ret || in_reset)
			dev_err(dev, "Device failed to exit MHI Reset state\n");

		/*
		 * Device will clear BHI_INTVEC as a part of RESET processing,
		 * hence re-program it
		 */
		mhi_ग_लिखो_reg(mhi_cntrl, mhi_cntrl->bhi, BHI_INTVEC, 0);
	पूर्ण

	dev_dbg(dev,
		 "Waiting for all pending event ring processing to complete\n");
	mhi_event = mhi_cntrl->mhi_event;
	क्रम (i = 0; i < mhi_cntrl->total_ev_rings; i++, mhi_event++) अणु
		अगर (mhi_event->offload_ev)
			जारी;
		मुक्त_irq(mhi_cntrl->irq[mhi_event->irq], mhi_event);
		tasklet_समाप्त(&mhi_event->task);
	पूर्ण

	/* Release lock and रुको क्रम all pending thपढ़ोs to complete */
	mutex_unlock(&mhi_cntrl->pm_mutex);
	dev_dbg(dev, "Waiting for all pending threads to complete\n");
	wake_up_all(&mhi_cntrl->state_event);

	dev_dbg(dev, "Reset all active channels and remove MHI devices\n");
	device_क्रम_each_child(&mhi_cntrl->mhi_dev->dev, शून्य, mhi_destroy_device);

	mutex_lock(&mhi_cntrl->pm_mutex);

	WARN_ON(atomic_पढ़ो(&mhi_cntrl->dev_wake));
	WARN_ON(atomic_पढ़ो(&mhi_cntrl->pending_pkts));

	/* Reset the ev rings and cmd rings */
	dev_dbg(dev, "Resetting EV CTXT and CMD CTXT\n");
	mhi_cmd = mhi_cntrl->mhi_cmd;
	cmd_ctxt = mhi_cntrl->mhi_ctxt->cmd_ctxt;
	क्रम (i = 0; i < NR_OF_CMD_RINGS; i++, mhi_cmd++, cmd_ctxt++) अणु
		काष्ठा mhi_ring *ring = &mhi_cmd->ring;

		ring->rp = ring->base;
		ring->wp = ring->base;
		cmd_ctxt->rp = cmd_ctxt->rbase;
		cmd_ctxt->wp = cmd_ctxt->rbase;
	पूर्ण

	mhi_event = mhi_cntrl->mhi_event;
	er_ctxt = mhi_cntrl->mhi_ctxt->er_ctxt;
	क्रम (i = 0; i < mhi_cntrl->total_ev_rings; i++, er_ctxt++,
		     mhi_event++) अणु
		काष्ठा mhi_ring *ring = &mhi_event->ring;

		/* Skip offload events */
		अगर (mhi_event->offload_ev)
			जारी;

		ring->rp = ring->base;
		ring->wp = ring->base;
		er_ctxt->rp = er_ctxt->rbase;
		er_ctxt->wp = er_ctxt->rbase;
	पूर्ण

	/* Move to disable state */
	ग_लिखो_lock_irq(&mhi_cntrl->pm_lock);
	cur_state = mhi_tryset_pm_state(mhi_cntrl, MHI_PM_DISABLE);
	ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);
	अगर (unlikely(cur_state != MHI_PM_DISABLE))
		dev_err(dev, "Error moving from PM state: %s to: %s\n",
			to_mhi_pm_state_str(cur_state),
			to_mhi_pm_state_str(MHI_PM_DISABLE));

	dev_dbg(dev, "Exiting with PM state: %s, MHI state: %s\n",
		to_mhi_pm_state_str(mhi_cntrl->pm_state),
		TO_MHI_STATE_STR(mhi_cntrl->dev_state));

	mutex_unlock(&mhi_cntrl->pm_mutex);
पूर्ण

/* Handle प्रणाली error transitions */
अटल व्योम mhi_pm_sys_error_transition(काष्ठा mhi_controller *mhi_cntrl)
अणु
	क्रमागत mhi_pm_state cur_state, prev_state;
	क्रमागत dev_st_transition next_state;
	काष्ठा mhi_event *mhi_event;
	काष्ठा mhi_cmd_ctxt *cmd_ctxt;
	काष्ठा mhi_cmd *mhi_cmd;
	काष्ठा mhi_event_ctxt *er_ctxt;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;
	पूर्णांक ret, i;

	dev_dbg(dev, "Transitioning from PM state: %s to: %s\n",
		to_mhi_pm_state_str(mhi_cntrl->pm_state),
		to_mhi_pm_state_str(MHI_PM_SYS_ERR_PROCESS));

	/* We must notअगरy MHI control driver so it can clean up first */
	mhi_cntrl->status_cb(mhi_cntrl, MHI_CB_SYS_ERROR);

	mutex_lock(&mhi_cntrl->pm_mutex);
	ग_लिखो_lock_irq(&mhi_cntrl->pm_lock);
	prev_state = mhi_cntrl->pm_state;
	cur_state = mhi_tryset_pm_state(mhi_cntrl, MHI_PM_SYS_ERR_PROCESS);
	ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);

	अगर (cur_state != MHI_PM_SYS_ERR_PROCESS) अणु
		dev_err(dev, "Failed to transition from PM state: %s to: %s\n",
			to_mhi_pm_state_str(cur_state),
			to_mhi_pm_state_str(MHI_PM_SYS_ERR_PROCESS));
		जाओ निकास_sys_error_transition;
	पूर्ण

	mhi_cntrl->ee = MHI_EE_DISABLE_TRANSITION;
	mhi_cntrl->dev_state = MHI_STATE_RESET;

	/* Wake up thपढ़ोs रुकोing क्रम state transition */
	wake_up_all(&mhi_cntrl->state_event);

	/* Trigger MHI RESET so that the device will not access host memory */
	अगर (MHI_REG_ACCESS_VALID(prev_state)) अणु
		u32 in_reset = -1;
		अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(mhi_cntrl->समयout_ms);

		dev_dbg(dev, "Triggering MHI Reset in device\n");
		mhi_set_mhi_state(mhi_cntrl, MHI_STATE_RESET);

		/* Wait क्रम the reset bit to be cleared by the device */
		ret = रुको_event_समयout(mhi_cntrl->state_event,
					 mhi_पढ़ो_reg_field(mhi_cntrl,
							    mhi_cntrl->regs,
							    MHICTRL,
							    MHICTRL_RESET_MASK,
							    MHICTRL_RESET_SHIFT,
							    &in_reset) ||
					!in_reset, समयout);
		अगर (!ret || in_reset) अणु
			dev_err(dev, "Device failed to exit MHI Reset state\n");
			जाओ निकास_sys_error_transition;
		पूर्ण

		/*
		 * Device will clear BHI_INTVEC as a part of RESET processing,
		 * hence re-program it
		 */
		mhi_ग_लिखो_reg(mhi_cntrl, mhi_cntrl->bhi, BHI_INTVEC, 0);
	पूर्ण

	dev_dbg(dev,
		"Waiting for all pending event ring processing to complete\n");
	mhi_event = mhi_cntrl->mhi_event;
	क्रम (i = 0; i < mhi_cntrl->total_ev_rings; i++, mhi_event++) अणु
		अगर (mhi_event->offload_ev)
			जारी;
		tasklet_समाप्त(&mhi_event->task);
	पूर्ण

	/* Release lock and रुको क्रम all pending thपढ़ोs to complete */
	mutex_unlock(&mhi_cntrl->pm_mutex);
	dev_dbg(dev, "Waiting for all pending threads to complete\n");
	wake_up_all(&mhi_cntrl->state_event);

	dev_dbg(dev, "Reset all active channels and remove MHI devices\n");
	device_क्रम_each_child(&mhi_cntrl->mhi_dev->dev, शून्य, mhi_destroy_device);

	mutex_lock(&mhi_cntrl->pm_mutex);

	WARN_ON(atomic_पढ़ो(&mhi_cntrl->dev_wake));
	WARN_ON(atomic_पढ़ो(&mhi_cntrl->pending_pkts));

	/* Reset the ev rings and cmd rings */
	dev_dbg(dev, "Resetting EV CTXT and CMD CTXT\n");
	mhi_cmd = mhi_cntrl->mhi_cmd;
	cmd_ctxt = mhi_cntrl->mhi_ctxt->cmd_ctxt;
	क्रम (i = 0; i < NR_OF_CMD_RINGS; i++, mhi_cmd++, cmd_ctxt++) अणु
		काष्ठा mhi_ring *ring = &mhi_cmd->ring;

		ring->rp = ring->base;
		ring->wp = ring->base;
		cmd_ctxt->rp = cmd_ctxt->rbase;
		cmd_ctxt->wp = cmd_ctxt->rbase;
	पूर्ण

	mhi_event = mhi_cntrl->mhi_event;
	er_ctxt = mhi_cntrl->mhi_ctxt->er_ctxt;
	क्रम (i = 0; i < mhi_cntrl->total_ev_rings; i++, er_ctxt++,
	     mhi_event++) अणु
		काष्ठा mhi_ring *ring = &mhi_event->ring;

		/* Skip offload events */
		अगर (mhi_event->offload_ev)
			जारी;

		ring->rp = ring->base;
		ring->wp = ring->base;
		er_ctxt->rp = er_ctxt->rbase;
		er_ctxt->wp = er_ctxt->rbase;
	पूर्ण

	/* Transition to next state */
	अगर (MHI_IN_PBL(mhi_get_exec_env(mhi_cntrl))) अणु
		ग_लिखो_lock_irq(&mhi_cntrl->pm_lock);
		cur_state = mhi_tryset_pm_state(mhi_cntrl, MHI_PM_POR);
		ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);
		अगर (cur_state != MHI_PM_POR) अणु
			dev_err(dev, "Error moving to state %s from %s\n",
				to_mhi_pm_state_str(MHI_PM_POR),
				to_mhi_pm_state_str(cur_state));
			जाओ निकास_sys_error_transition;
		पूर्ण
		next_state = DEV_ST_TRANSITION_PBL;
	पूर्ण अन्यथा अणु
		next_state = DEV_ST_TRANSITION_READY;
	पूर्ण

	mhi_queue_state_transition(mhi_cntrl, next_state);

निकास_sys_error_transition:
	dev_dbg(dev, "Exiting with PM state: %s, MHI state: %s\n",
		to_mhi_pm_state_str(mhi_cntrl->pm_state),
		TO_MHI_STATE_STR(mhi_cntrl->dev_state));

	mutex_unlock(&mhi_cntrl->pm_mutex);
पूर्ण

/* Queue a new work item and schedule work */
पूर्णांक mhi_queue_state_transition(काष्ठा mhi_controller *mhi_cntrl,
			       क्रमागत dev_st_transition state)
अणु
	काष्ठा state_transition *item = kदो_स्मृति(माप(*item), GFP_ATOMIC);
	अचिन्हित दीर्घ flags;

	अगर (!item)
		वापस -ENOMEM;

	item->state = state;
	spin_lock_irqsave(&mhi_cntrl->transition_lock, flags);
	list_add_tail(&item->node, &mhi_cntrl->transition_list);
	spin_unlock_irqrestore(&mhi_cntrl->transition_lock, flags);

	queue_work(mhi_cntrl->hiprio_wq, &mhi_cntrl->st_worker);

	वापस 0;
पूर्ण

/* SYS_ERR worker */
व्योम mhi_pm_sys_err_handler(काष्ठा mhi_controller *mhi_cntrl)
अणु
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;

	/* skip अगर controller supports RDDM */
	अगर (mhi_cntrl->rddm_image) अणु
		dev_dbg(dev, "Controller supports RDDM, skip SYS_ERROR\n");
		वापस;
	पूर्ण

	mhi_queue_state_transition(mhi_cntrl, DEV_ST_TRANSITION_SYS_ERR);
पूर्ण

/* Device State Transition worker */
व्योम mhi_pm_st_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा state_transition *itr, *पंचांगp;
	LIST_HEAD(head);
	काष्ठा mhi_controller *mhi_cntrl = container_of(work,
							काष्ठा mhi_controller,
							st_worker);
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;

	spin_lock_irq(&mhi_cntrl->transition_lock);
	list_splice_tail_init(&mhi_cntrl->transition_list, &head);
	spin_unlock_irq(&mhi_cntrl->transition_lock);

	list_क्रम_each_entry_safe(itr, पंचांगp, &head, node) अणु
		list_del(&itr->node);
		dev_dbg(dev, "Handling state transition: %s\n",
			TO_DEV_STATE_TRANS_STR(itr->state));

		चयन (itr->state) अणु
		हाल DEV_ST_TRANSITION_PBL:
			ग_लिखो_lock_irq(&mhi_cntrl->pm_lock);
			अगर (MHI_REG_ACCESS_VALID(mhi_cntrl->pm_state))
				mhi_cntrl->ee = mhi_get_exec_env(mhi_cntrl);
			ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);
			mhi_fw_load_handler(mhi_cntrl);
			अवरोध;
		हाल DEV_ST_TRANSITION_SBL:
			ग_लिखो_lock_irq(&mhi_cntrl->pm_lock);
			mhi_cntrl->ee = MHI_EE_SBL;
			ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);
			/*
			 * The MHI devices are only created when the client
			 * device चयनes its Execution Environment (EE) to
			 * either SBL or AMSS states
			 */
			mhi_create_devices(mhi_cntrl);
			अगर (mhi_cntrl->fbc_करोwnload)
				mhi_करोwnload_amss_image(mhi_cntrl);
			अवरोध;
		हाल DEV_ST_TRANSITION_MISSION_MODE:
			mhi_pm_mission_mode_transition(mhi_cntrl);
			अवरोध;
		हाल DEV_ST_TRANSITION_FP:
			ग_लिखो_lock_irq(&mhi_cntrl->pm_lock);
			mhi_cntrl->ee = MHI_EE_FP;
			ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);
			mhi_create_devices(mhi_cntrl);
			अवरोध;
		हाल DEV_ST_TRANSITION_READY:
			mhi_पढ़ोy_state_transition(mhi_cntrl);
			अवरोध;
		हाल DEV_ST_TRANSITION_SYS_ERR:
			mhi_pm_sys_error_transition(mhi_cntrl);
			अवरोध;
		हाल DEV_ST_TRANSITION_DISABLE:
			mhi_pm_disable_transition(mhi_cntrl);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		kमुक्त(itr);
	पूर्ण
पूर्ण

पूर्णांक mhi_pm_suspend(काष्ठा mhi_controller *mhi_cntrl)
अणु
	काष्ठा mhi_chan *itr, *पंचांगp;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;
	क्रमागत mhi_pm_state new_state;
	पूर्णांक ret;

	अगर (mhi_cntrl->pm_state == MHI_PM_DISABLE)
		वापस -EINVAL;

	अगर (MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state))
		वापस -EIO;

	/* Return busy अगर there are any pending resources */
	अगर (atomic_पढ़ो(&mhi_cntrl->dev_wake) ||
	    atomic_पढ़ो(&mhi_cntrl->pending_pkts))
		वापस -EBUSY;

	/* Take MHI out of M2 state */
	पढ़ो_lock_bh(&mhi_cntrl->pm_lock);
	mhi_cntrl->wake_get(mhi_cntrl, false);
	पढ़ो_unlock_bh(&mhi_cntrl->pm_lock);

	ret = रुको_event_समयout(mhi_cntrl->state_event,
				 mhi_cntrl->dev_state == MHI_STATE_M0 ||
				 mhi_cntrl->dev_state == MHI_STATE_M1 ||
				 MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state),
				 msecs_to_jअगरfies(mhi_cntrl->समयout_ms));

	पढ़ो_lock_bh(&mhi_cntrl->pm_lock);
	mhi_cntrl->wake_put(mhi_cntrl, false);
	पढ़ो_unlock_bh(&mhi_cntrl->pm_lock);

	अगर (!ret || MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state)) अणु
		dev_err(dev,
			"Could not enter M0/M1 state");
		वापस -EIO;
	पूर्ण

	ग_लिखो_lock_irq(&mhi_cntrl->pm_lock);

	अगर (atomic_पढ़ो(&mhi_cntrl->dev_wake) ||
	    atomic_पढ़ो(&mhi_cntrl->pending_pkts)) अणु
		ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);
		वापस -EBUSY;
	पूर्ण

	dev_dbg(dev, "Allowing M3 transition\n");
	new_state = mhi_tryset_pm_state(mhi_cntrl, MHI_PM_M3_ENTER);
	अगर (new_state != MHI_PM_M3_ENTER) अणु
		ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);
		dev_err(dev,
			"Error setting to PM state: %s from: %s\n",
			to_mhi_pm_state_str(MHI_PM_M3_ENTER),
			to_mhi_pm_state_str(mhi_cntrl->pm_state));
		वापस -EIO;
	पूर्ण

	/* Set MHI to M3 and रुको क्रम completion */
	mhi_set_mhi_state(mhi_cntrl, MHI_STATE_M3);
	ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);
	dev_dbg(dev, "Waiting for M3 completion\n");

	ret = रुको_event_समयout(mhi_cntrl->state_event,
				 mhi_cntrl->dev_state == MHI_STATE_M3 ||
				 MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state),
				 msecs_to_jअगरfies(mhi_cntrl->समयout_ms));

	अगर (!ret || MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state)) अणु
		dev_err(dev,
			"Did not enter M3 state, MHI state: %s, PM state: %s\n",
			TO_MHI_STATE_STR(mhi_cntrl->dev_state),
			to_mhi_pm_state_str(mhi_cntrl->pm_state));
		वापस -EIO;
	पूर्ण

	/* Notअगरy clients about entering LPM */
	list_क्रम_each_entry_safe(itr, पंचांगp, &mhi_cntrl->lpm_chans, node) अणु
		mutex_lock(&itr->mutex);
		अगर (itr->mhi_dev)
			mhi_notअगरy(itr->mhi_dev, MHI_CB_LPM_ENTER);
		mutex_unlock(&itr->mutex);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mhi_pm_suspend);

पूर्णांक mhi_pm_resume(काष्ठा mhi_controller *mhi_cntrl)
अणु
	काष्ठा mhi_chan *itr, *पंचांगp;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;
	क्रमागत mhi_pm_state cur_state;
	पूर्णांक ret;

	dev_dbg(dev, "Entered with PM state: %s, MHI state: %s\n",
		to_mhi_pm_state_str(mhi_cntrl->pm_state),
		TO_MHI_STATE_STR(mhi_cntrl->dev_state));

	अगर (mhi_cntrl->pm_state == MHI_PM_DISABLE)
		वापस 0;

	अगर (MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state))
		वापस -EIO;

	अगर (mhi_get_mhi_state(mhi_cntrl) != MHI_STATE_M3)
		वापस -EINVAL;

	/* Notअगरy clients about निकासing LPM */
	list_क्रम_each_entry_safe(itr, पंचांगp, &mhi_cntrl->lpm_chans, node) अणु
		mutex_lock(&itr->mutex);
		अगर (itr->mhi_dev)
			mhi_notअगरy(itr->mhi_dev, MHI_CB_LPM_EXIT);
		mutex_unlock(&itr->mutex);
	पूर्ण

	ग_लिखो_lock_irq(&mhi_cntrl->pm_lock);
	cur_state = mhi_tryset_pm_state(mhi_cntrl, MHI_PM_M3_EXIT);
	अगर (cur_state != MHI_PM_M3_EXIT) अणु
		ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);
		dev_info(dev,
			 "Error setting to PM state: %s from: %s\n",
			 to_mhi_pm_state_str(MHI_PM_M3_EXIT),
			 to_mhi_pm_state_str(mhi_cntrl->pm_state));
		वापस -EIO;
	पूर्ण

	/* Set MHI to M0 and रुको क्रम completion */
	mhi_set_mhi_state(mhi_cntrl, MHI_STATE_M0);
	ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);

	ret = रुको_event_समयout(mhi_cntrl->state_event,
				 mhi_cntrl->dev_state == MHI_STATE_M0 ||
				 MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state),
				 msecs_to_jअगरfies(mhi_cntrl->समयout_ms));

	अगर (!ret || MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state)) अणु
		dev_err(dev,
			"Did not enter M0 state, MHI state: %s, PM state: %s\n",
			TO_MHI_STATE_STR(mhi_cntrl->dev_state),
			to_mhi_pm_state_str(mhi_cntrl->pm_state));
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mhi_pm_resume);

पूर्णांक __mhi_device_get_sync(काष्ठा mhi_controller *mhi_cntrl)
अणु
	पूर्णांक ret;

	/* Wake up the device */
	पढ़ो_lock_bh(&mhi_cntrl->pm_lock);
	अगर (MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state)) अणु
		पढ़ो_unlock_bh(&mhi_cntrl->pm_lock);
		वापस -EIO;
	पूर्ण
	mhi_cntrl->wake_get(mhi_cntrl, true);
	अगर (MHI_PM_IN_SUSPEND_STATE(mhi_cntrl->pm_state))
		mhi_trigger_resume(mhi_cntrl);
	पढ़ो_unlock_bh(&mhi_cntrl->pm_lock);

	ret = रुको_event_समयout(mhi_cntrl->state_event,
				 mhi_cntrl->pm_state == MHI_PM_M0 ||
				 MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state),
				 msecs_to_jअगरfies(mhi_cntrl->समयout_ms));

	अगर (!ret || MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state)) अणु
		पढ़ो_lock_bh(&mhi_cntrl->pm_lock);
		mhi_cntrl->wake_put(mhi_cntrl, false);
		पढ़ो_unlock_bh(&mhi_cntrl->pm_lock);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/* Assert device wake db */
अटल व्योम mhi_निश्चित_dev_wake(काष्ठा mhi_controller *mhi_cntrl, bool क्रमce)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * If क्रमce flag is set, then increment the wake count value and
	 * ring wake db
	 */
	अगर (unlikely(क्रमce)) अणु
		spin_lock_irqsave(&mhi_cntrl->wlock, flags);
		atomic_inc(&mhi_cntrl->dev_wake);
		अगर (MHI_WAKE_DB_FORCE_SET_VALID(mhi_cntrl->pm_state) &&
		    !mhi_cntrl->wake_set) अणु
			mhi_ग_लिखो_db(mhi_cntrl, mhi_cntrl->wake_db, 1);
			mhi_cntrl->wake_set = true;
		पूर्ण
		spin_unlock_irqrestore(&mhi_cntrl->wlock, flags);
	पूर्ण अन्यथा अणु
		/*
		 * If resources are alपढ़ोy requested, then just increment
		 * the wake count value and वापस
		 */
		अगर (likely(atomic_add_unless(&mhi_cntrl->dev_wake, 1, 0)))
			वापस;

		spin_lock_irqsave(&mhi_cntrl->wlock, flags);
		अगर ((atomic_inc_वापस(&mhi_cntrl->dev_wake) == 1) &&
		    MHI_WAKE_DB_SET_VALID(mhi_cntrl->pm_state) &&
		    !mhi_cntrl->wake_set) अणु
			mhi_ग_लिखो_db(mhi_cntrl, mhi_cntrl->wake_db, 1);
			mhi_cntrl->wake_set = true;
		पूर्ण
		spin_unlock_irqrestore(&mhi_cntrl->wlock, flags);
	पूर्ण
पूर्ण

/* De-निश्चित device wake db */
अटल व्योम mhi_deनिश्चित_dev_wake(काष्ठा mhi_controller *mhi_cntrl,
				  bool override)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * Only जारी अगर there is a single resource, अन्यथा just decrement
	 * and वापस
	 */
	अगर (likely(atomic_add_unless(&mhi_cntrl->dev_wake, -1, 1)))
		वापस;

	spin_lock_irqsave(&mhi_cntrl->wlock, flags);
	अगर ((atomic_dec_वापस(&mhi_cntrl->dev_wake) == 0) &&
	    MHI_WAKE_DB_CLEAR_VALID(mhi_cntrl->pm_state) && !override &&
	    mhi_cntrl->wake_set) अणु
		mhi_ग_लिखो_db(mhi_cntrl, mhi_cntrl->wake_db, 0);
		mhi_cntrl->wake_set = false;
	पूर्ण
	spin_unlock_irqrestore(&mhi_cntrl->wlock, flags);
पूर्ण

पूर्णांक mhi_async_घातer_up(काष्ठा mhi_controller *mhi_cntrl)
अणु
	क्रमागत mhi_state state;
	क्रमागत mhi_ee_type current_ee;
	क्रमागत dev_st_transition next_state;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;
	u32 val;
	पूर्णांक ret;

	dev_info(dev, "Requested to power ON\n");

	/* Supply शेष wake routines अगर not provided by controller driver */
	अगर (!mhi_cntrl->wake_get || !mhi_cntrl->wake_put ||
	    !mhi_cntrl->wake_toggle) अणु
		mhi_cntrl->wake_get = mhi_निश्चित_dev_wake;
		mhi_cntrl->wake_put = mhi_deनिश्चित_dev_wake;
		mhi_cntrl->wake_toggle = (mhi_cntrl->db_access & MHI_PM_M2) ?
			mhi_toggle_dev_wake_nop : mhi_toggle_dev_wake;
	पूर्ण

	mutex_lock(&mhi_cntrl->pm_mutex);
	mhi_cntrl->pm_state = MHI_PM_DISABLE;

	ret = mhi_init_irq_setup(mhi_cntrl);
	अगर (ret)
		जाओ error_setup_irq;

	/* Setup BHI offset & INTVEC */
	ग_लिखो_lock_irq(&mhi_cntrl->pm_lock);
	ret = mhi_पढ़ो_reg(mhi_cntrl, mhi_cntrl->regs, BHIOFF, &val);
	अगर (ret) अणु
		ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);
		जाओ error_bhi_offset;
	पूर्ण

	mhi_cntrl->bhi = mhi_cntrl->regs + val;

	/* Setup BHIE offset */
	अगर (mhi_cntrl->fbc_करोwnload) अणु
		ret = mhi_पढ़ो_reg(mhi_cntrl, mhi_cntrl->regs, BHIखातापूर्णF, &val);
		अगर (ret) अणु
			ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);
			dev_err(dev, "Error reading BHIE offset\n");
			जाओ error_bhi_offset;
		पूर्ण

		mhi_cntrl->bhie = mhi_cntrl->regs + val;
	पूर्ण

	mhi_ग_लिखो_reg(mhi_cntrl, mhi_cntrl->bhi, BHI_INTVEC, 0);
	mhi_cntrl->pm_state = MHI_PM_POR;
	mhi_cntrl->ee = MHI_EE_MAX;
	current_ee = mhi_get_exec_env(mhi_cntrl);
	ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);

	/* Confirm that the device is in valid exec env */
	अगर (!MHI_IN_PBL(current_ee) && current_ee != MHI_EE_AMSS) अणु
		dev_err(dev, "Not a valid EE for power on\n");
		ret = -EIO;
		जाओ error_bhi_offset;
	पूर्ण

	state = mhi_get_mhi_state(mhi_cntrl);
	अगर (state == MHI_STATE_SYS_ERR) अणु
		mhi_set_mhi_state(mhi_cntrl, MHI_STATE_RESET);
		ret = रुको_event_समयout(mhi_cntrl->state_event,
				MHI_PM_IN_FATAL_STATE(mhi_cntrl->pm_state) ||
					mhi_पढ़ो_reg_field(mhi_cntrl,
							   mhi_cntrl->regs,
							   MHICTRL,
							   MHICTRL_RESET_MASK,
							   MHICTRL_RESET_SHIFT,
							   &val) ||
					!val,
				msecs_to_jअगरfies(mhi_cntrl->समयout_ms));
		अगर (!ret) अणु
			ret = -EIO;
			dev_info(dev, "Failed to reset MHI due to syserr state\n");
			जाओ error_bhi_offset;
		पूर्ण

		/*
		 * device cleares INTVEC as part of RESET processing,
		 * re-program it
		 */
		mhi_ग_लिखो_reg(mhi_cntrl, mhi_cntrl->bhi, BHI_INTVEC, 0);
	पूर्ण

	/* Transition to next state */
	next_state = MHI_IN_PBL(current_ee) ?
		DEV_ST_TRANSITION_PBL : DEV_ST_TRANSITION_READY;

	mhi_queue_state_transition(mhi_cntrl, next_state);

	mutex_unlock(&mhi_cntrl->pm_mutex);

	dev_info(dev, "Power on setup success\n");

	वापस 0;

error_bhi_offset:
	mhi_deinit_मुक्त_irq(mhi_cntrl);

error_setup_irq:
	mhi_cntrl->pm_state = MHI_PM_DISABLE;
	mutex_unlock(&mhi_cntrl->pm_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mhi_async_घातer_up);

व्योम mhi_घातer_करोwn(काष्ठा mhi_controller *mhi_cntrl, bool graceful)
अणु
	क्रमागत mhi_pm_state cur_state, transition_state;
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;

	mutex_lock(&mhi_cntrl->pm_mutex);
	ग_लिखो_lock_irq(&mhi_cntrl->pm_lock);
	cur_state = mhi_cntrl->pm_state;
	अगर (cur_state == MHI_PM_DISABLE) अणु
		ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);
		mutex_unlock(&mhi_cntrl->pm_mutex);
		वापस; /* Alपढ़ोy घातered करोwn */
	पूर्ण

	/* If it's not a graceful shutकरोwn, क्रमce MHI to linkकरोwn state */
	transition_state = (graceful) ? MHI_PM_SHUTDOWN_PROCESS :
			   MHI_PM_LD_ERR_FATAL_DETECT;

	cur_state = mhi_tryset_pm_state(mhi_cntrl, transition_state);
	अगर (cur_state != transition_state) अणु
		dev_err(dev, "Failed to move to state: %s from: %s\n",
			to_mhi_pm_state_str(transition_state),
			to_mhi_pm_state_str(mhi_cntrl->pm_state));
		/* Force link करोwn or error fatal detected state */
		mhi_cntrl->pm_state = MHI_PM_LD_ERR_FATAL_DETECT;
	पूर्ण

	/* mark device inactive to aव्योम any further host processing */
	mhi_cntrl->ee = MHI_EE_DISABLE_TRANSITION;
	mhi_cntrl->dev_state = MHI_STATE_RESET;

	wake_up_all(&mhi_cntrl->state_event);

	ग_लिखो_unlock_irq(&mhi_cntrl->pm_lock);
	mutex_unlock(&mhi_cntrl->pm_mutex);

	mhi_queue_state_transition(mhi_cntrl, DEV_ST_TRANSITION_DISABLE);

	/* Wait क्रम shutकरोwn to complete */
	flush_work(&mhi_cntrl->st_worker);

	मुक्त_irq(mhi_cntrl->irq[0], mhi_cntrl);
पूर्ण
EXPORT_SYMBOL_GPL(mhi_घातer_करोwn);

पूर्णांक mhi_sync_घातer_up(काष्ठा mhi_controller *mhi_cntrl)
अणु
	पूर्णांक ret = mhi_async_घातer_up(mhi_cntrl);

	अगर (ret)
		वापस ret;

	रुको_event_समयout(mhi_cntrl->state_event,
			   MHI_IN_MISSION_MODE(mhi_cntrl->ee) ||
			   MHI_PM_IN_ERROR_STATE(mhi_cntrl->pm_state),
			   msecs_to_jअगरfies(mhi_cntrl->समयout_ms));

	ret = (MHI_IN_MISSION_MODE(mhi_cntrl->ee)) ? 0 : -ETIMEDOUT;
	अगर (ret)
		mhi_घातer_करोwn(mhi_cntrl, false);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(mhi_sync_घातer_up);

पूर्णांक mhi_क्रमce_rddm_mode(काष्ठा mhi_controller *mhi_cntrl)
अणु
	काष्ठा device *dev = &mhi_cntrl->mhi_dev->dev;
	पूर्णांक ret;

	/* Check अगर device is alपढ़ोy in RDDM */
	अगर (mhi_cntrl->ee == MHI_EE_RDDM)
		वापस 0;

	dev_dbg(dev, "Triggering SYS_ERR to force RDDM state\n");
	mhi_set_mhi_state(mhi_cntrl, MHI_STATE_SYS_ERR);

	/* Wait क्रम RDDM event */
	ret = रुको_event_समयout(mhi_cntrl->state_event,
				 mhi_cntrl->ee == MHI_EE_RDDM,
				 msecs_to_jअगरfies(mhi_cntrl->समयout_ms));
	ret = ret ? 0 : -EIO;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mhi_क्रमce_rddm_mode);

व्योम mhi_device_get(काष्ठा mhi_device *mhi_dev)
अणु
	काष्ठा mhi_controller *mhi_cntrl = mhi_dev->mhi_cntrl;

	mhi_dev->dev_wake++;
	पढ़ो_lock_bh(&mhi_cntrl->pm_lock);
	अगर (MHI_PM_IN_SUSPEND_STATE(mhi_cntrl->pm_state))
		mhi_trigger_resume(mhi_cntrl);

	mhi_cntrl->wake_get(mhi_cntrl, true);
	पढ़ो_unlock_bh(&mhi_cntrl->pm_lock);
पूर्ण
EXPORT_SYMBOL_GPL(mhi_device_get);

पूर्णांक mhi_device_get_sync(काष्ठा mhi_device *mhi_dev)
अणु
	काष्ठा mhi_controller *mhi_cntrl = mhi_dev->mhi_cntrl;
	पूर्णांक ret;

	ret = __mhi_device_get_sync(mhi_cntrl);
	अगर (!ret)
		mhi_dev->dev_wake++;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mhi_device_get_sync);

व्योम mhi_device_put(काष्ठा mhi_device *mhi_dev)
अणु
	काष्ठा mhi_controller *mhi_cntrl = mhi_dev->mhi_cntrl;

	mhi_dev->dev_wake--;
	पढ़ो_lock_bh(&mhi_cntrl->pm_lock);
	अगर (MHI_PM_IN_SUSPEND_STATE(mhi_cntrl->pm_state))
		mhi_trigger_resume(mhi_cntrl);

	mhi_cntrl->wake_put(mhi_cntrl, false);
	पढ़ो_unlock_bh(&mhi_cntrl->pm_lock);
पूर्ण
EXPORT_SYMBOL_GPL(mhi_device_put);
