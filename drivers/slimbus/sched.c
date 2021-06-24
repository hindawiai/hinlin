<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2011-2017, The Linux Foundation
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश "slimbus.h"

/**
 * slim_ctrl_clk_छोड़ो() - Called by slimbus controller to enter/निकास
 *			   'clock pause'
 * @ctrl: controller requesting bus to be छोड़ोd or woken up
 * @wakeup: Wakeup this controller from घड़ी छोड़ो.
 * @restart: Restart समय value per spec used क्रम घड़ी छोड़ो. This value
 *	isn't used when controller is to be woken up.
 *
 * Slimbus specअगरication needs this sequence to turn-off घड़ीs क्रम the bus.
 * The sequence involves sending 3 broadcast messages (reconfiguration
 * sequence) to inक्रमm all devices on the bus.
 * To निकास घड़ी-छोड़ो, controller typically wakes up active framer device.
 * This API executes घड़ी छोड़ो reconfiguration sequence अगर wakeup is false.
 * If wakeup is true, controller's wakeup is called.
 * For entering घड़ी-छोड़ो, -EBUSY is वापसed अगर a message txn in pending.
 */
पूर्णांक slim_ctrl_clk_छोड़ो(काष्ठा slim_controller *ctrl, bool wakeup, u8 restart)
अणु
	पूर्णांक i, ret = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा slim_sched *sched = &ctrl->sched;
	काष्ठा slim_val_inf msg = अणु0, 0, शून्य, शून्यपूर्ण;

	DEFINE_SLIM_BCAST_TXN(txn, SLIM_MSG_MC_BEGIN_RECONFIGURATION,
				3, SLIM_LA_MANAGER, &msg);

	अगर (wakeup == false && restart > SLIM_CLK_UNSPECIFIED)
		वापस -EINVAL;

	mutex_lock(&sched->m_reconf);
	अगर (wakeup) अणु
		अगर (sched->clk_state == SLIM_CLK_ACTIVE) अणु
			mutex_unlock(&sched->m_reconf);
			वापस 0;
		पूर्ण

		/*
		 * Fine-tune calculation based on घड़ी gear,
		 * message-bandwidth after bandwidth management
		 */
		ret = रुको_क्रम_completion_समयout(&sched->छोड़ो_comp,
				msecs_to_jअगरfies(100));
		अगर (!ret) अणु
			mutex_unlock(&sched->m_reconf);
			pr_err("Previous clock pause did not finish");
			वापस -ETIMEDOUT;
		पूर्ण
		ret = 0;

		/*
		 * Slimbus framework will call controller wakeup
		 * Controller should make sure that it sets active framer
		 * out of घड़ी छोड़ो
		 */
		अगर (sched->clk_state == SLIM_CLK_PAUSED && ctrl->wakeup)
			ret = ctrl->wakeup(ctrl);
		अगर (!ret)
			sched->clk_state = SLIM_CLK_ACTIVE;
		mutex_unlock(&sched->m_reconf);

		वापस ret;
	पूर्ण

	/* alपढ़ोy छोड़ोd */
	अगर (ctrl->sched.clk_state == SLIM_CLK_PAUSED) अणु
		mutex_unlock(&sched->m_reconf);
		वापस 0;
	पूर्ण

	spin_lock_irqsave(&ctrl->txn_lock, flags);
	क्रम (i = 0; i < SLIM_MAX_TIDS; i++) अणु
		/* Pending response क्रम a message */
		अगर (idr_find(&ctrl->tid_idr, i)) अणु
			spin_unlock_irqrestore(&ctrl->txn_lock, flags);
			mutex_unlock(&sched->m_reconf);
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ctrl->txn_lock, flags);

	sched->clk_state = SLIM_CLK_ENTERING_PAUSE;

	/* घड़ी छोड़ो sequence */
	ret = slim_करो_transfer(ctrl, &txn);
	अगर (ret)
		जाओ clk_छोड़ो_ret;

	txn.mc = SLIM_MSG_MC_NEXT_PAUSE_CLOCK;
	txn.rl = 4;
	msg.num_bytes = 1;
	msg.wbuf = &restart;
	ret = slim_करो_transfer(ctrl, &txn);
	अगर (ret)
		जाओ clk_छोड़ो_ret;

	txn.mc = SLIM_MSG_MC_RECONFIGURE_NOW;
	txn.rl = 3;
	msg.num_bytes = 1;
	msg.wbuf = शून्य;
	ret = slim_करो_transfer(ctrl, &txn);

clk_छोड़ो_ret:
	अगर (ret) अणु
		sched->clk_state = SLIM_CLK_ACTIVE;
	पूर्ण अन्यथा अणु
		sched->clk_state = SLIM_CLK_PAUSED;
		complete(&sched->छोड़ो_comp);
	पूर्ण
	mutex_unlock(&sched->m_reconf);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(slim_ctrl_clk_छोड़ो);
