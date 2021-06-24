<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016-2018, The Linux Foundation. All rights reserved.
 */

#घोषणा pr_fmt(fmt) "%s " fmt, KBUILD_MODNAME

#समावेश <linux/atomic.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>

#समावेश <soc/qcom/cmd-db.h>
#समावेश <soc/qcom/tcs.h>
#समावेश <dt-bindings/soc/qcom,rpmh-rsc.h>

#समावेश "rpmh-internal.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace-rpmh.h"

#घोषणा RSC_DRV_TCS_OFFSET		672
#घोषणा RSC_DRV_CMD_OFFSET		20

/* DRV HW Solver Configuration Inक्रमmation Register */
#घोषणा DRV_SOLVER_CONFIG		0x04
#घोषणा DRV_HW_SOLVER_MASK		1
#घोषणा DRV_HW_SOLVER_SHIFT		24

/* DRV TCS Configuration Inक्रमmation Register */
#घोषणा DRV_PRNT_CHLD_CONFIG		0x0C
#घोषणा DRV_NUM_TCS_MASK		0x3F
#घोषणा DRV_NUM_TCS_SHIFT		6
#घोषणा DRV_NCPT_MASK			0x1F
#घोषणा DRV_NCPT_SHIFT			27

/* Offsets क्रम common TCS Registers, one bit per TCS */
#घोषणा RSC_DRV_IRQ_ENABLE		0x00
#घोषणा RSC_DRV_IRQ_STATUS		0x04
#घोषणा RSC_DRV_IRQ_CLEAR		0x08	/* w/o; ग_लिखो 1 to clear */

/*
 * Offsets क्रम per TCS Registers.
 *
 * TCSes start at 0x10 from tcs_base and are stored one after another.
 * Multiply tcs_id by RSC_DRV_TCS_OFFSET to find a given TCS and add one
 * of the below to find a रेजिस्टर.
 */
#घोषणा RSC_DRV_CMD_WAIT_FOR_CMPL	0x10	/* 1 bit per command */
#घोषणा RSC_DRV_CONTROL			0x14
#घोषणा RSC_DRV_STATUS			0x18	/* zero अगर tcs is busy */
#घोषणा RSC_DRV_CMD_ENABLE		0x1C	/* 1 bit per command */

/*
 * Offsets क्रम per command in a TCS.
 *
 * Commands (up to 16) start at 0x30 in a TCS; multiply command index
 * by RSC_DRV_CMD_OFFSET and add one of the below to find a रेजिस्टर.
 */
#घोषणा RSC_DRV_CMD_MSGID		0x30
#घोषणा RSC_DRV_CMD_ADDR		0x34
#घोषणा RSC_DRV_CMD_DATA		0x38
#घोषणा RSC_DRV_CMD_STATUS		0x3C
#घोषणा RSC_DRV_CMD_RESP_DATA		0x40

#घोषणा TCS_AMC_MODE_ENABLE		BIT(16)
#घोषणा TCS_AMC_MODE_TRIGGER		BIT(24)

/* TCS CMD रेजिस्टर bit mask */
#घोषणा CMD_MSGID_LEN			8
#घोषणा CMD_MSGID_RESP_REQ		BIT(8)
#घोषणा CMD_MSGID_WRITE			BIT(16)
#घोषणा CMD_STATUS_ISSUED		BIT(8)
#घोषणा CMD_STATUS_COMPL		BIT(16)

/*
 * Here's a high level overview of how all the रेजिस्टरs in RPMH work
 * together:
 *
 * - The मुख्य rpmh-rsc address is the base of a रेजिस्टर space that can
 *   be used to find overall configuration of the hardware
 *   (DRV_PRNT_CHLD_CONFIG). Also found within the rpmh-rsc रेजिस्टर
 *   space are all the TCS blocks. The offset of the TCS blocks is
 *   specअगरied in the device tree by "qcom,tcs-offset" and used to
 *   compute tcs_base.
 * - TCS blocks come one after another. Type, count, and order are
 *   specअगरied by the device tree as "qcom,tcs-config".
 * - Each TCS block has some रेजिस्टरs, then space क्रम up to 16 commands.
 *   Note that though address space is reserved क्रम 16 commands, fewer
 *   might be present. See ncpt (num cmds per TCS).
 *
 * Here's a picture:
 *
 *  +---------------------------------------------------+
 *  |RSC                                                |
 *  | ctrl                                              |
 *  |                                                   |
 *  | Drvs:                                             |
 *  | +-----------------------------------------------+ |
 *  | |DRV0                                           | |
 *  | | ctrl/config                                   | |
 *  | | IRQ                                           | |
 *  | |                                               | |
 *  | | TCSes:                                        | |
 *  | | +------------------------------------------+  | |
 *  | | |TCS0  |  |  |  |  |  |  |  |  |  |  |  |  |  | |
 *  | | | ctrl | 0| 1| 2| 3| 4| 5| .| .| .| .|14|15|  | |
 *  | | |      |  |  |  |  |  |  |  |  |  |  |  |  |  | |
 *  | | +------------------------------------------+  | |
 *  | | +------------------------------------------+  | |
 *  | | |TCS1  |  |  |  |  |  |  |  |  |  |  |  |  |  | |
 *  | | | ctrl | 0| 1| 2| 3| 4| 5| .| .| .| .|14|15|  | |
 *  | | |      |  |  |  |  |  |  |  |  |  |  |  |  |  | |
 *  | | +------------------------------------------+  | |
 *  | | +------------------------------------------+  | |
 *  | | |TCS2  |  |  |  |  |  |  |  |  |  |  |  |  |  | |
 *  | | | ctrl | 0| 1| 2| 3| 4| 5| .| .| .| .|14|15|  | |
 *  | | |      |  |  |  |  |  |  |  |  |  |  |  |  |  | |
 *  | | +------------------------------------------+  | |
 *  | |                    ......                     | |
 *  | +-----------------------------------------------+ |
 *  | +-----------------------------------------------+ |
 *  | |DRV1                                           | |
 *  | | (same as DRV0)                                | |
 *  | +-----------------------------------------------+ |
 *  |                      ......                       |
 *  +---------------------------------------------------+
 */

अटल अंतरभूत व्योम __iomem *
tcs_reg_addr(स्थिर काष्ठा rsc_drv *drv, पूर्णांक reg, पूर्णांक tcs_id)
अणु
	वापस drv->tcs_base + RSC_DRV_TCS_OFFSET * tcs_id + reg;
पूर्ण

अटल अंतरभूत व्योम __iomem *
tcs_cmd_addr(स्थिर काष्ठा rsc_drv *drv, पूर्णांक reg, पूर्णांक tcs_id, पूर्णांक cmd_id)
अणु
	वापस tcs_reg_addr(drv, reg, tcs_id) + RSC_DRV_CMD_OFFSET * cmd_id;
पूर्ण

अटल u32 पढ़ो_tcs_cmd(स्थिर काष्ठा rsc_drv *drv, पूर्णांक reg, पूर्णांक tcs_id,
			पूर्णांक cmd_id)
अणु
	वापस पढ़ोl_relaxed(tcs_cmd_addr(drv, reg, tcs_id, cmd_id));
पूर्ण

अटल u32 पढ़ो_tcs_reg(स्थिर काष्ठा rsc_drv *drv, पूर्णांक reg, पूर्णांक tcs_id)
अणु
	वापस पढ़ोl_relaxed(tcs_reg_addr(drv, reg, tcs_id));
पूर्ण

अटल व्योम ग_लिखो_tcs_cmd(स्थिर काष्ठा rsc_drv *drv, पूर्णांक reg, पूर्णांक tcs_id,
			  पूर्णांक cmd_id, u32 data)
अणु
	ग_लिखोl_relaxed(data, tcs_cmd_addr(drv, reg, tcs_id, cmd_id));
पूर्ण

अटल व्योम ग_लिखो_tcs_reg(स्थिर काष्ठा rsc_drv *drv, पूर्णांक reg, पूर्णांक tcs_id,
			  u32 data)
अणु
	ग_लिखोl_relaxed(data, tcs_reg_addr(drv, reg, tcs_id));
पूर्ण

अटल व्योम ग_लिखो_tcs_reg_sync(स्थिर काष्ठा rsc_drv *drv, पूर्णांक reg, पूर्णांक tcs_id,
			       u32 data)
अणु
	पूर्णांक i;

	ग_लिखोl(data, tcs_reg_addr(drv, reg, tcs_id));

	/*
	 * Wait until we पढ़ो back the same value.  Use a counter rather than
	 * kसमय क्रम समयout since this may be called after समयkeeping stops.
	 */
	क्रम (i = 0; i < USEC_PER_SEC; i++) अणु
		अगर (पढ़ोl(tcs_reg_addr(drv, reg, tcs_id)) == data)
			वापस;
		udelay(1);
	पूर्ण
	pr_err("%s: error writing %#x to %d:%#x\n", drv->name,
	       data, tcs_id, reg);
पूर्ण

/**
 * tcs_invalidate() - Invalidate all TCSes of the given type (sleep or wake).
 * @drv:  The RSC controller.
 * @type: SLEEP_TCS or WAKE_TCS
 *
 * This will clear the "slots" variable of the given tcs_group and also
 * tell the hardware to क्रमget about all entries.
 *
 * The caller must ensure that no other RPMH actions are happening when this
 * function is called, since otherwise the device may immediately become
 * used again even beक्रमe this function निकासs.
 */
अटल व्योम tcs_invalidate(काष्ठा rsc_drv *drv, पूर्णांक type)
अणु
	पूर्णांक m;
	काष्ठा tcs_group *tcs = &drv->tcs[type];

	/* Caller ensures nobody अन्यथा is running so no lock */
	अगर (biपंचांगap_empty(tcs->slots, MAX_TCS_SLOTS))
		वापस;

	क्रम (m = tcs->offset; m < tcs->offset + tcs->num_tcs; m++)
		ग_लिखो_tcs_reg_sync(drv, RSC_DRV_CMD_ENABLE, m, 0);

	biपंचांगap_zero(tcs->slots, MAX_TCS_SLOTS);
पूर्ण

/**
 * rpmh_rsc_invalidate() - Invalidate sleep and wake TCSes.
 * @drv: The RSC controller.
 *
 * The caller must ensure that no other RPMH actions are happening when this
 * function is called, since otherwise the device may immediately become
 * used again even beक्रमe this function निकासs.
 */
व्योम rpmh_rsc_invalidate(काष्ठा rsc_drv *drv)
अणु
	tcs_invalidate(drv, SLEEP_TCS);
	tcs_invalidate(drv, WAKE_TCS);
पूर्ण

/**
 * get_tcs_क्रम_msg() - Get the tcs_group used to send the given message.
 * @drv: The RSC controller.
 * @msg: The message we want to send.
 *
 * This is normally pretty straightक्रमward except अगर we are trying to send
 * an ACTIVE_ONLY message but करोn't have any active_only TCSes.
 *
 * Return: A poपूर्णांकer to a tcs_group or an ERR_PTR.
 */
अटल काष्ठा tcs_group *get_tcs_क्रम_msg(काष्ठा rsc_drv *drv,
					 स्थिर काष्ठा tcs_request *msg)
अणु
	पूर्णांक type;
	काष्ठा tcs_group *tcs;

	चयन (msg->state) अणु
	हाल RPMH_ACTIVE_ONLY_STATE:
		type = ACTIVE_TCS;
		अवरोध;
	हाल RPMH_WAKE_ONLY_STATE:
		type = WAKE_TCS;
		अवरोध;
	हाल RPMH_SLEEP_STATE:
		type = SLEEP_TCS;
		अवरोध;
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/*
	 * If we are making an active request on a RSC that करोes not have a
	 * dedicated TCS क्रम active state use, then re-purpose a wake TCS to
	 * send active votes. This is safe because we ensure any active-only
	 * transfers have finished beक्रमe we use it (maybe by running from
	 * the last CPU in PM code).
	 */
	tcs = &drv->tcs[type];
	अगर (msg->state == RPMH_ACTIVE_ONLY_STATE && !tcs->num_tcs)
		tcs = &drv->tcs[WAKE_TCS];

	वापस tcs;
पूर्ण

/**
 * get_req_from_tcs() - Get a stashed request that was xfering on the given TCS.
 * @drv:    The RSC controller.
 * @tcs_id: The global ID of this TCS.
 *
 * For ACTIVE_ONLY transfers we want to call back पूर्णांकo the client when the
 * transfer finishes. To करो this we need the "request" that the client
 * originally provided us. This function grअसल the request that we stashed
 * when we started the transfer.
 *
 * This only makes sense क्रम ACTIVE_ONLY transfers since those are the only
 * ones we track sending (the only ones we enable पूर्णांकerrupts क्रम and the only
 * ones we call back to the client क्रम).
 *
 * Return: The stashed request.
 */
अटल स्थिर काष्ठा tcs_request *get_req_from_tcs(काष्ठा rsc_drv *drv,
						  पूर्णांक tcs_id)
अणु
	काष्ठा tcs_group *tcs;
	पूर्णांक i;

	क्रम (i = 0; i < TCS_TYPE_NR; i++) अणु
		tcs = &drv->tcs[i];
		अगर (tcs->mask & BIT(tcs_id))
			वापस tcs->req[tcs_id - tcs->offset];
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * __tcs_set_trigger() - Start xfer on a TCS or unset trigger on a borrowed TCS
 * @drv:     The controller.
 * @tcs_id:  The global ID of this TCS.
 * @trigger: If true then untrigger/retrigger. If false then just untrigger.
 *
 * In the normal हाल we only ever call with "trigger=true" to start a
 * transfer. That will un-trigger/disable the TCS from the last transfer
 * then trigger/enable क्रम this transfer.
 *
 * If we borrowed a wake TCS क्रम an active-only transfer we'll also call
 * this function with "trigger=false" to just करो the un-trigger/disable
 * beक्रमe using the TCS क्रम wake purposes again.
 *
 * Note that the AP is only in अक्षरge of triggering active-only transfers.
 * The AP never triggers sleep/wake values using this function.
 */
अटल व्योम __tcs_set_trigger(काष्ठा rsc_drv *drv, पूर्णांक tcs_id, bool trigger)
अणु
	u32 enable;

	/*
	 * HW req: Clear the DRV_CONTROL and enable TCS again
	 * While clearing ensure that the AMC mode trigger is cleared
	 * and then the mode enable is cleared.
	 */
	enable = पढ़ो_tcs_reg(drv, RSC_DRV_CONTROL, tcs_id);
	enable &= ~TCS_AMC_MODE_TRIGGER;
	ग_लिखो_tcs_reg_sync(drv, RSC_DRV_CONTROL, tcs_id, enable);
	enable &= ~TCS_AMC_MODE_ENABLE;
	ग_लिखो_tcs_reg_sync(drv, RSC_DRV_CONTROL, tcs_id, enable);

	अगर (trigger) अणु
		/* Enable the AMC mode on the TCS and then trigger the TCS */
		enable = TCS_AMC_MODE_ENABLE;
		ग_लिखो_tcs_reg_sync(drv, RSC_DRV_CONTROL, tcs_id, enable);
		enable |= TCS_AMC_MODE_TRIGGER;
		ग_लिखो_tcs_reg(drv, RSC_DRV_CONTROL, tcs_id, enable);
	पूर्ण
पूर्ण

/**
 * enable_tcs_irq() - Enable or disable पूर्णांकerrupts on the given TCS.
 * @drv:     The controller.
 * @tcs_id:  The global ID of this TCS.
 * @enable:  If true then enable; अगर false then disable
 *
 * We only ever call this when we borrow a wake TCS क्रम an active-only
 * transfer. For active-only TCSes पूर्णांकerrupts are always left enabled.
 */
अटल व्योम enable_tcs_irq(काष्ठा rsc_drv *drv, पूर्णांक tcs_id, bool enable)
अणु
	u32 data;

	data = पढ़ोl_relaxed(drv->tcs_base + RSC_DRV_IRQ_ENABLE);
	अगर (enable)
		data |= BIT(tcs_id);
	अन्यथा
		data &= ~BIT(tcs_id);
	ग_लिखोl_relaxed(data, drv->tcs_base + RSC_DRV_IRQ_ENABLE);
पूर्ण

/**
 * tcs_tx_करोne() - TX Done पूर्णांकerrupt handler.
 * @irq: The IRQ number (ignored).
 * @p:   Poपूर्णांकer to "struct rsc_drv".
 *
 * Called क्रम ACTIVE_ONLY transfers (those are the only ones we enable the
 * IRQ क्रम) when a transfer is करोne.
 *
 * Return: IRQ_HANDLED
 */
अटल irqवापस_t tcs_tx_करोne(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा rsc_drv *drv = p;
	पूर्णांक i, j, err = 0;
	अचिन्हित दीर्घ irq_status;
	स्थिर काष्ठा tcs_request *req;
	काष्ठा tcs_cmd *cmd;

	irq_status = पढ़ोl_relaxed(drv->tcs_base + RSC_DRV_IRQ_STATUS);

	क्रम_each_set_bit(i, &irq_status, BITS_PER_TYPE(u32)) अणु
		req = get_req_from_tcs(drv, i);
		अगर (WARN_ON(!req))
			जाओ skip;

		err = 0;
		क्रम (j = 0; j < req->num_cmds; j++) अणु
			u32 sts;

			cmd = &req->cmds[j];
			sts = पढ़ो_tcs_cmd(drv, RSC_DRV_CMD_STATUS, i, j);
			अगर (!(sts & CMD_STATUS_ISSUED) ||
			   ((req->रुको_क्रम_compl || cmd->रुको) &&
			   !(sts & CMD_STATUS_COMPL))) अणु
				pr_err("Incomplete request: %s: addr=%#x data=%#x",
				       drv->name, cmd->addr, cmd->data);
				err = -EIO;
			पूर्ण
		पूर्ण

		trace_rpmh_tx_करोne(drv, i, req, err);

		/*
		 * If wake tcs was re-purposed क्रम sending active
		 * votes, clear AMC trigger & enable modes and
		 * disable पूर्णांकerrupt क्रम this TCS
		 */
		अगर (!drv->tcs[ACTIVE_TCS].num_tcs)
			__tcs_set_trigger(drv, i, false);
skip:
		/* Reclaim the TCS */
		ग_लिखो_tcs_reg(drv, RSC_DRV_CMD_ENABLE, i, 0);
		ग_लिखोl_relaxed(BIT(i), drv->tcs_base + RSC_DRV_IRQ_CLEAR);
		spin_lock(&drv->lock);
		clear_bit(i, drv->tcs_in_use);
		/*
		 * Disable पूर्णांकerrupt क्रम WAKE TCS to aव्योम being
		 * spammed with पूर्णांकerrupts coming when the solver
		 * sends its wake votes.
		 */
		अगर (!drv->tcs[ACTIVE_TCS].num_tcs)
			enable_tcs_irq(drv, i, false);
		spin_unlock(&drv->lock);
		wake_up(&drv->tcs_रुको);
		अगर (req)
			rpmh_tx_करोne(req, err);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/**
 * __tcs_buffer_ग_लिखो() - Write to TCS hardware from a request; करोn't trigger.
 * @drv:    The controller.
 * @tcs_id: The global ID of this TCS.
 * @cmd_id: The index within the TCS to start writing.
 * @msg:    The message we want to send, which will contain several addr/data
 *          pairs to program (but few enough that they all fit in one TCS).
 *
 * This is used क्रम all types of transfers (active, sleep, and wake).
 */
अटल व्योम __tcs_buffer_ग_लिखो(काष्ठा rsc_drv *drv, पूर्णांक tcs_id, पूर्णांक cmd_id,
			       स्थिर काष्ठा tcs_request *msg)
अणु
	u32 msgid;
	u32 cmd_msgid = CMD_MSGID_LEN | CMD_MSGID_WRITE;
	u32 cmd_enable = 0;
	काष्ठा tcs_cmd *cmd;
	पूर्णांक i, j;

	/* Convert all commands to RR when the request has रुको_क्रम_compl set */
	cmd_msgid |= msg->रुको_क्रम_compl ? CMD_MSGID_RESP_REQ : 0;

	क्रम (i = 0, j = cmd_id; i < msg->num_cmds; i++, j++) अणु
		cmd = &msg->cmds[i];
		cmd_enable |= BIT(j);
		msgid = cmd_msgid;
		/*
		 * Additionally, अगर the cmd->रुको is set, make the command
		 * response reqd even अगर the overall request was fire-n-क्रमget.
		 */
		msgid |= cmd->रुको ? CMD_MSGID_RESP_REQ : 0;

		ग_लिखो_tcs_cmd(drv, RSC_DRV_CMD_MSGID, tcs_id, j, msgid);
		ग_लिखो_tcs_cmd(drv, RSC_DRV_CMD_ADDR, tcs_id, j, cmd->addr);
		ग_लिखो_tcs_cmd(drv, RSC_DRV_CMD_DATA, tcs_id, j, cmd->data);
		trace_rpmh_send_msg(drv, tcs_id, j, msgid, cmd);
	पूर्ण

	cmd_enable |= पढ़ो_tcs_reg(drv, RSC_DRV_CMD_ENABLE, tcs_id);
	ग_लिखो_tcs_reg(drv, RSC_DRV_CMD_ENABLE, tcs_id, cmd_enable);
पूर्ण

/**
 * check_क्रम_req_inflight() - Look to see अगर conflicting cmds are in flight.
 * @drv: The controller.
 * @tcs: A poपूर्णांकer to the tcs_group used क्रम ACTIVE_ONLY transfers.
 * @msg: The message we want to send, which will contain several addr/data
 *       pairs to program (but few enough that they all fit in one TCS).
 *
 * This will walk through the TCSes in the group and check अगर any of them
 * appear to be sending to addresses referenced in the message. If it finds
 * one it'll वापस -EBUSY.
 *
 * Only क्रम use क्रम active-only transfers.
 *
 * Must be called with the drv->lock held since that protects tcs_in_use.
 *
 * Return: 0 अगर nothing in flight or -EBUSY अगर we should try again later.
 *         The caller must re-enable पूर्णांकerrupts between tries since that's
 *         the only way tcs_in_use will ever be updated and the only way
 *         RSC_DRV_CMD_ENABLE will ever be cleared.
 */
अटल पूर्णांक check_क्रम_req_inflight(काष्ठा rsc_drv *drv, काष्ठा tcs_group *tcs,
				  स्थिर काष्ठा tcs_request *msg)
अणु
	अचिन्हित दीर्घ curr_enabled;
	u32 addr;
	पूर्णांक j, k;
	पूर्णांक i = tcs->offset;

	क्रम_each_set_bit_from(i, drv->tcs_in_use, tcs->offset + tcs->num_tcs) अणु
		curr_enabled = पढ़ो_tcs_reg(drv, RSC_DRV_CMD_ENABLE, i);

		क्रम_each_set_bit(j, &curr_enabled, MAX_CMDS_PER_TCS) अणु
			addr = पढ़ो_tcs_cmd(drv, RSC_DRV_CMD_ADDR, i, j);
			क्रम (k = 0; k < msg->num_cmds; k++) अणु
				अगर (addr == msg->cmds[k].addr)
					वापस -EBUSY;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * find_मुक्त_tcs() - Find मुक्त tcs in the given tcs_group; only क्रम active.
 * @tcs: A poपूर्णांकer to the active-only tcs_group (or the wake tcs_group अगर
 *       we borrowed it because there are zero active-only ones).
 *
 * Must be called with the drv->lock held since that protects tcs_in_use.
 *
 * Return: The first tcs that's मुक्त or -EBUSY अगर all in use.
 */
अटल पूर्णांक find_मुक्त_tcs(काष्ठा tcs_group *tcs)
अणु
	स्थिर काष्ठा rsc_drv *drv = tcs->drv;
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ max = tcs->offset + tcs->num_tcs;

	i = find_next_zero_bit(drv->tcs_in_use, max, tcs->offset);
	अगर (i >= max)
		वापस -EBUSY;

	वापस i;
पूर्ण

/**
 * claim_tcs_क्रम_req() - Claim a tcs in the given tcs_group; only क्रम active.
 * @drv: The controller.
 * @tcs: The tcs_group used क्रम ACTIVE_ONLY transfers.
 * @msg: The data to be sent.
 *
 * Claims a tcs in the given tcs_group जबतक making sure that no existing cmd
 * is in flight that would conflict with the one in @msg.
 *
 * Context: Must be called with the drv->lock held since that protects
 * tcs_in_use.
 *
 * Return: The id of the claimed tcs or -EBUSY अगर a matching msg is in flight
 * or the tcs_group is full.
 */
अटल पूर्णांक claim_tcs_क्रम_req(काष्ठा rsc_drv *drv, काष्ठा tcs_group *tcs,
			     स्थिर काष्ठा tcs_request *msg)
अणु
	पूर्णांक ret;

	/*
	 * The h/w करोes not like अगर we send a request to the same address,
	 * when one is alपढ़ोy in-flight or being processed.
	 */
	ret = check_क्रम_req_inflight(drv, tcs, msg);
	अगर (ret)
		वापस ret;

	वापस find_मुक्त_tcs(tcs);
पूर्ण

/**
 * rpmh_rsc_send_data() - Write / trigger active-only message.
 * @drv: The controller.
 * @msg: The data to be sent.
 *
 * NOTES:
 * - This is only used क्रम "ACTIVE_ONLY" since the limitations of this
 *   function करोn't make sense क्रम sleep/wake हालs.
 * - To करो the transfer, we will grab a whole TCS क्रम ourselves--we करोn't
 *   try to share. If there are none available we'll रुको indefinitely
 *   क्रम a मुक्त one.
 * - This function will not रुको क्रम the commands to be finished, only क्रम
 *   data to be programmed पूर्णांकo the RPMh. See rpmh_tx_करोne() which will
 *   be called when the transfer is fully complete.
 * - This function must be called with पूर्णांकerrupts enabled. If the hardware
 *   is busy करोing someone अन्यथा's transfer we need that transfer to fully
 *   finish so that we can have the hardware, and to fully finish it needs
 *   the पूर्णांकerrupt handler to run. If the पूर्णांकerrupts is set to run on the
 *   active CPU this can never happen अगर पूर्णांकerrupts are disabled.
 *
 * Return: 0 on success, -EINVAL on error.
 */
पूर्णांक rpmh_rsc_send_data(काष्ठा rsc_drv *drv, स्थिर काष्ठा tcs_request *msg)
अणु
	काष्ठा tcs_group *tcs;
	पूर्णांक tcs_id;
	अचिन्हित दीर्घ flags;

	tcs = get_tcs_क्रम_msg(drv, msg);
	अगर (IS_ERR(tcs))
		वापस PTR_ERR(tcs);

	spin_lock_irqsave(&drv->lock, flags);

	/* Wait क्रमever क्रम a मुक्त tcs. It better be there eventually! */
	रुको_event_lock_irq(drv->tcs_रुको,
			    (tcs_id = claim_tcs_क्रम_req(drv, tcs, msg)) >= 0,
			    drv->lock);

	tcs->req[tcs_id - tcs->offset] = msg;
	set_bit(tcs_id, drv->tcs_in_use);
	अगर (msg->state == RPMH_ACTIVE_ONLY_STATE && tcs->type != ACTIVE_TCS) अणु
		/*
		 * Clear previously programmed WAKE commands in selected
		 * repurposed TCS to aव्योम triggering them. tcs->slots will be
		 * cleaned from rpmh_flush() by invoking rpmh_rsc_invalidate()
		 */
		ग_लिखो_tcs_reg_sync(drv, RSC_DRV_CMD_ENABLE, tcs_id, 0);
		enable_tcs_irq(drv, tcs_id, true);
	पूर्ण
	spin_unlock_irqrestore(&drv->lock, flags);

	/*
	 * These two can be करोne after the lock is released because:
	 * - We marked "tcs_in_use" under lock.
	 * - Once "tcs_in_use" has been marked nobody अन्यथा could be writing
	 *   to these रेजिस्टरs until the पूर्णांकerrupt goes off.
	 * - The पूर्णांकerrupt can't go off until we trigger w/ the last line
	 *   of __tcs_set_trigger() below.
	 */
	__tcs_buffer_ग_लिखो(drv, tcs_id, 0, msg);
	__tcs_set_trigger(drv, tcs_id, true);

	वापस 0;
पूर्ण

/**
 * find_slots() - Find a place to ग_लिखो the given message.
 * @tcs:    The tcs group to search.
 * @msg:    The message we want to find room क्रम.
 * @tcs_id: If we वापस 0 from the function, we वापस the global ID of the
 *          TCS to ग_लिखो to here.
 * @cmd_id: If we वापस 0 from the function, we वापस the index of
 *          the command array of the वापसed TCS where the client should
 *          start writing the message.
 *
 * Only क्रम use on sleep/wake TCSes since those are the only ones we मुख्यtain
 * tcs->slots क्रम.
 *
 * Return: -ENOMEM अगर there was no room, अन्यथा 0.
 */
अटल पूर्णांक find_slots(काष्ठा tcs_group *tcs, स्थिर काष्ठा tcs_request *msg,
		      पूर्णांक *tcs_id, पूर्णांक *cmd_id)
अणु
	पूर्णांक slot, offset;
	पूर्णांक i = 0;

	/* Do over, until we can fit the full payload in a single TCS */
	करो अणु
		slot = biपंचांगap_find_next_zero_area(tcs->slots, MAX_TCS_SLOTS,
						  i, msg->num_cmds, 0);
		अगर (slot >= tcs->num_tcs * tcs->ncpt)
			वापस -ENOMEM;
		i += tcs->ncpt;
	पूर्ण जबतक (slot + msg->num_cmds - 1 >= i);

	biपंचांगap_set(tcs->slots, slot, msg->num_cmds);

	offset = slot / tcs->ncpt;
	*tcs_id = offset + tcs->offset;
	*cmd_id = slot % tcs->ncpt;

	वापस 0;
पूर्ण

/**
 * rpmh_rsc_ग_लिखो_ctrl_data() - Write request to controller but करोn't trigger.
 * @drv: The controller.
 * @msg: The data to be written to the controller.
 *
 * This should only be called क्रम क्रम sleep/wake state, never active-only
 * state.
 *
 * The caller must ensure that no other RPMH actions are happening and the
 * controller is idle when this function is called since it runs lockless.
 *
 * Return: 0 अगर no error; अन्यथा -error.
 */
पूर्णांक rpmh_rsc_ग_लिखो_ctrl_data(काष्ठा rsc_drv *drv, स्थिर काष्ठा tcs_request *msg)
अणु
	काष्ठा tcs_group *tcs;
	पूर्णांक tcs_id = 0, cmd_id = 0;
	पूर्णांक ret;

	tcs = get_tcs_क्रम_msg(drv, msg);
	अगर (IS_ERR(tcs))
		वापस PTR_ERR(tcs);

	/* find the TCS id and the command in the TCS to ग_लिखो to */
	ret = find_slots(tcs, msg, &tcs_id, &cmd_id);
	अगर (!ret)
		__tcs_buffer_ग_लिखो(drv, tcs_id, cmd_id, msg);

	वापस ret;
पूर्ण

/**
 * rpmh_rsc_ctrlr_is_busy() - Check अगर any of the AMCs are busy.
 * @drv: The controller
 *
 * Checks अगर any of the AMCs are busy in handling ACTIVE sets.
 * This is called from the last cpu घातering करोwn beक्रमe flushing
 * SLEEP and WAKE sets. If AMCs are busy, controller can not enter
 * घातer collapse, so deny from the last cpu's pm notअगरication.
 *
 * Context: Must be called with the drv->lock held.
 *
 * Return:
 * * False		- AMCs are idle
 * * True		- AMCs are busy
 */
अटल bool rpmh_rsc_ctrlr_is_busy(काष्ठा rsc_drv *drv)
अणु
	अचिन्हित दीर्घ set;
	स्थिर काष्ठा tcs_group *tcs = &drv->tcs[ACTIVE_TCS];
	अचिन्हित दीर्घ max;

	/*
	 * If we made an active request on a RSC that करोes not have a
	 * dedicated TCS क्रम active state use, then re-purposed wake TCSes
	 * should be checked क्रम not busy, because we used wake TCSes क्रम
	 * active requests in this हाल.
	 */
	अगर (!tcs->num_tcs)
		tcs = &drv->tcs[WAKE_TCS];

	max = tcs->offset + tcs->num_tcs;
	set = find_next_bit(drv->tcs_in_use, max, tcs->offset);

	वापस set < max;
पूर्ण

/**
 * rpmh_rsc_cpu_pm_callback() - Check अगर any of the AMCs are busy.
 * @nfb:    Poपूर्णांकer to the notअगरier block in काष्ठा rsc_drv.
 * @action: CPU_PM_ENTER, CPU_PM_ENTER_FAILED, or CPU_PM_EXIT.
 * @v:      Unused
 *
 * This function is given to cpu_pm_रेजिस्टर_notअगरier so we can be inक्रमmed
 * about when CPUs go करोwn. When all CPUs go करोwn we know no more active
 * transfers will be started so we ग_लिखो sleep/wake sets. This function माला_लो
 * called from cpuidle code paths and also at प्रणाली suspend समय.
 *
 * If its last CPU going करोwn and AMCs are not busy then ग_लिखोs cached sleep
 * and wake messages to TCSes. The firmware then takes care of triggering
 * them when entering deepest low घातer modes.
 *
 * Return: See cpu_pm_रेजिस्टर_notअगरier()
 */
अटल पूर्णांक rpmh_rsc_cpu_pm_callback(काष्ठा notअगरier_block *nfb,
				    अचिन्हित दीर्घ action, व्योम *v)
अणु
	काष्ठा rsc_drv *drv = container_of(nfb, काष्ठा rsc_drv, rsc_pm);
	पूर्णांक ret = NOTIFY_OK;
	पूर्णांक cpus_in_pm;

	चयन (action) अणु
	हाल CPU_PM_ENTER:
		cpus_in_pm = atomic_inc_वापस(&drv->cpus_in_pm);
		/*
		 * NOTE: comments क्रम num_online_cpus() poपूर्णांक out that it's
		 * only a snapshot so we need to be careful. It should be OK
		 * क्रम us to use, though.  It's important क्रम us not to miss
		 * अगर we're the last CPU going करोwn so it would only be a
		 * problem अगर a CPU went offline right after we did the check
		 * AND that CPU was not idle AND that CPU was the last non-idle
		 * CPU. That can't happen. CPUs would have to come out of idle
		 * beक्रमe the CPU could go offline.
		 */
		अगर (cpus_in_pm < num_online_cpus())
			वापस NOTIFY_OK;
		अवरोध;
	हाल CPU_PM_ENTER_FAILED:
	हाल CPU_PM_EXIT:
		atomic_dec(&drv->cpus_in_pm);
		वापस NOTIFY_OK;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	/*
	 * It's likely we're on the last CPU. Grab the drv->lock and ग_लिखो
	 * out the sleep/wake commands to RPMH hardware. Grabbing the lock
	 * means that अगर we race with another CPU coming up we are still
	 * guaranteed to be safe. If another CPU came up just after we checked
	 * and has grabbed the lock or started an active transfer then we'll
	 * notice we're busy and पात. If another CPU comes up after we start
	 * flushing it will be blocked from starting an active transfer until
	 * we're करोne flushing. If another CPU starts an active transfer after
	 * we release the lock we're still OK because we're no दीर्घer the last
	 * CPU.
	 */
	अगर (spin_trylock(&drv->lock)) अणु
		अगर (rpmh_rsc_ctrlr_is_busy(drv) || rpmh_flush(&drv->client))
			ret = NOTIFY_BAD;
		spin_unlock(&drv->lock);
	पूर्ण अन्यथा अणु
		/* Another CPU must be up */
		वापस NOTIFY_OK;
	पूर्ण

	अगर (ret == NOTIFY_BAD) अणु
		/* Double-check अगर we're here because someone अन्यथा is up */
		अगर (cpus_in_pm < num_online_cpus())
			ret = NOTIFY_OK;
		अन्यथा
			/* We won't be called w/ CPU_PM_ENTER_FAILED */
			atomic_dec(&drv->cpus_in_pm);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rpmh_probe_tcs_config(काष्ठा platक्रमm_device *pdev,
				 काष्ठा rsc_drv *drv, व्योम __iomem *base)
अणु
	काष्ठा tcs_type_config अणु
		u32 type;
		u32 n;
	पूर्ण tcs_cfg[TCS_TYPE_NR] = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा device_node *dn = pdev->dev.of_node;
	u32 config, max_tcs, ncpt, offset;
	पूर्णांक i, ret, n, st = 0;
	काष्ठा tcs_group *tcs;

	ret = of_property_पढ़ो_u32(dn, "qcom,tcs-offset", &offset);
	अगर (ret)
		वापस ret;
	drv->tcs_base = base + offset;

	config = पढ़ोl_relaxed(base + DRV_PRNT_CHLD_CONFIG);

	max_tcs = config;
	max_tcs &= DRV_NUM_TCS_MASK << (DRV_NUM_TCS_SHIFT * drv->id);
	max_tcs = max_tcs >> (DRV_NUM_TCS_SHIFT * drv->id);

	ncpt = config & (DRV_NCPT_MASK << DRV_NCPT_SHIFT);
	ncpt = ncpt >> DRV_NCPT_SHIFT;

	n = of_property_count_u32_elems(dn, "qcom,tcs-config");
	अगर (n != 2 * TCS_TYPE_NR)
		वापस -EINVAL;

	क्रम (i = 0; i < TCS_TYPE_NR; i++) अणु
		ret = of_property_पढ़ो_u32_index(dn, "qcom,tcs-config",
						 i * 2, &tcs_cfg[i].type);
		अगर (ret)
			वापस ret;
		अगर (tcs_cfg[i].type >= TCS_TYPE_NR)
			वापस -EINVAL;

		ret = of_property_पढ़ो_u32_index(dn, "qcom,tcs-config",
						 i * 2 + 1, &tcs_cfg[i].n);
		अगर (ret)
			वापस ret;
		अगर (tcs_cfg[i].n > MAX_TCS_PER_TYPE)
			वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < TCS_TYPE_NR; i++) अणु
		tcs = &drv->tcs[tcs_cfg[i].type];
		अगर (tcs->drv)
			वापस -EINVAL;
		tcs->drv = drv;
		tcs->type = tcs_cfg[i].type;
		tcs->num_tcs = tcs_cfg[i].n;
		tcs->ncpt = ncpt;

		अगर (!tcs->num_tcs || tcs->type == CONTROL_TCS)
			जारी;

		अगर (st + tcs->num_tcs > max_tcs ||
		    st + tcs->num_tcs >= BITS_PER_BYTE * माप(tcs->mask))
			वापस -EINVAL;

		tcs->mask = ((1 << tcs->num_tcs) - 1) << st;
		tcs->offset = st;
		st += tcs->num_tcs;
	पूर्ण

	drv->num_tcs = st;

	वापस 0;
पूर्ण

अटल पूर्णांक rpmh_rsc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *dn = pdev->dev.of_node;
	काष्ठा rsc_drv *drv;
	काष्ठा resource *res;
	अक्षर drv_id[10] = अणु0पूर्ण;
	पूर्णांक ret, irq;
	u32 solver_config;
	व्योम __iomem *base;

	/*
	 * Even though RPMh करोesn't directly use cmd-db, all of its children
	 * करो. To aव्योम adding this check to our children we'll करो it now.
	 */
	ret = cmd_db_पढ़ोy();
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Command DB not available (%d)\n",
									ret);
		वापस ret;
	पूर्ण

	drv = devm_kzalloc(&pdev->dev, माप(*drv), GFP_KERNEL);
	अगर (!drv)
		वापस -ENOMEM;

	ret = of_property_पढ़ो_u32(dn, "qcom,drv-id", &drv->id);
	अगर (ret)
		वापस ret;

	drv->name = of_get_property(dn, "label", शून्य);
	अगर (!drv->name)
		drv->name = dev_name(&pdev->dev);

	snम_लिखो(drv_id, ARRAY_SIZE(drv_id), "drv-%d", drv->id);
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, drv_id);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	ret = rpmh_probe_tcs_config(pdev, drv, base);
	अगर (ret)
		वापस ret;

	spin_lock_init(&drv->lock);
	init_रुकोqueue_head(&drv->tcs_रुको);
	biपंचांगap_zero(drv->tcs_in_use, MAX_TCS_NR);

	irq = platक्रमm_get_irq(pdev, drv->id);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(&pdev->dev, irq, tcs_tx_करोne,
			       IRQF_TRIGGER_HIGH | IRQF_NO_SUSPEND,
			       drv->name, drv);
	अगर (ret)
		वापस ret;

	/*
	 * CPU PM notअगरication are not required क्रम controllers that support
	 * 'HW solver' mode where they can be in स्वतःnomous mode executing low
	 * घातer mode to घातer करोwn.
	 */
	solver_config = पढ़ोl_relaxed(base + DRV_SOLVER_CONFIG);
	solver_config &= DRV_HW_SOLVER_MASK << DRV_HW_SOLVER_SHIFT;
	solver_config = solver_config >> DRV_HW_SOLVER_SHIFT;
	अगर (!solver_config) अणु
		drv->rsc_pm.notअगरier_call = rpmh_rsc_cpu_pm_callback;
		cpu_pm_रेजिस्टर_notअगरier(&drv->rsc_pm);
	पूर्ण

	/* Enable the active TCS to send requests immediately */
	ग_लिखोl_relaxed(drv->tcs[ACTIVE_TCS].mask,
		       drv->tcs_base + RSC_DRV_IRQ_ENABLE);

	spin_lock_init(&drv->client.cache_lock);
	INIT_LIST_HEAD(&drv->client.cache);
	INIT_LIST_HEAD(&drv->client.batch_cache);

	dev_set_drvdata(&pdev->dev, drv);

	वापस devm_of_platक्रमm_populate(&pdev->dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id rpmh_drv_match[] = अणु
	अणु .compatible = "qcom,rpmh-rsc", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rpmh_drv_match);

अटल काष्ठा platक्रमm_driver rpmh_driver = अणु
	.probe = rpmh_rsc_probe,
	.driver = अणु
		  .name = "rpmh",
		  .of_match_table = rpmh_drv_match,
		  .suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init rpmh_driver_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&rpmh_driver);
पूर्ण
arch_initcall(rpmh_driver_init);

MODULE_DESCRIPTION("Qualcomm Technologies, Inc. RPMh Driver");
MODULE_LICENSE("GPL v2");
