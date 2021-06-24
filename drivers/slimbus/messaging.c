<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2011-2017, The Linux Foundation
 */

#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश "slimbus.h"

/**
 * slim_msg_response() - Deliver Message response received from a device to the
 *			framework.
 *
 * @ctrl: Controller handle
 * @reply: Reply received from the device
 * @len: Length of the reply
 * @tid: Transaction ID received with which framework can associate reply.
 *
 * Called by controller to inक्रमm framework about the response received.
 * This helps in making the API asynchronous, and controller-driver करोesn't need
 * to manage 1 more table other than the one managed by framework mapping TID
 * with buffers
 */
व्योम slim_msg_response(काष्ठा slim_controller *ctrl, u8 *reply, u8 tid, u8 len)
अणु
	काष्ठा slim_msg_txn *txn;
	काष्ठा slim_val_inf *msg;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctrl->txn_lock, flags);
	txn = idr_find(&ctrl->tid_idr, tid);
	spin_unlock_irqrestore(&ctrl->txn_lock, flags);

	अगर (txn == शून्य)
		वापस;

	msg = txn->msg;
	अगर (msg == शून्य || msg->rbuf == शून्य) अणु
		dev_err(ctrl->dev, "Got response to invalid TID:%d, len:%d\n",
				tid, len);
		वापस;
	पूर्ण

	slim_मुक्त_txn_tid(ctrl, txn);
	स_नकल(msg->rbuf, reply, len);
	अगर (txn->comp)
		complete(txn->comp);

	/* Remove runसमय-pm vote now that response was received क्रम TID txn */
	pm_runसमय_mark_last_busy(ctrl->dev);
	pm_runसमय_put_स्वतःsuspend(ctrl->dev);
पूर्ण
EXPORT_SYMBOL_GPL(slim_msg_response);

/**
 * slim_alloc_txn_tid() - Allocate a tid to txn
 *
 * @ctrl: Controller handle
 * @txn: transaction to be allocated with tid.
 *
 * Return: zero on success with valid txn->tid and error code on failures.
 */
पूर्णांक slim_alloc_txn_tid(काष्ठा slim_controller *ctrl, काष्ठा slim_msg_txn *txn)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&ctrl->txn_lock, flags);
	ret = idr_alloc_cyclic(&ctrl->tid_idr, txn, 0,
				SLIM_MAX_TIDS, GFP_ATOMIC);
	अगर (ret < 0) अणु
		spin_unlock_irqrestore(&ctrl->txn_lock, flags);
		वापस ret;
	पूर्ण
	txn->tid = ret;
	spin_unlock_irqrestore(&ctrl->txn_lock, flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(slim_alloc_txn_tid);

/**
 * slim_मुक्त_txn_tid() - Freee tid of txn
 *
 * @ctrl: Controller handle
 * @txn: transaction whose tid should be मुक्तd
 */
व्योम slim_मुक्त_txn_tid(काष्ठा slim_controller *ctrl, काष्ठा slim_msg_txn *txn)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctrl->txn_lock, flags);
	idr_हटाओ(&ctrl->tid_idr, txn->tid);
	spin_unlock_irqrestore(&ctrl->txn_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(slim_मुक्त_txn_tid);

/**
 * slim_करो_transfer() - Process a SLIMbus-messaging transaction
 *
 * @ctrl: Controller handle
 * @txn: Transaction to be sent over SLIMbus
 *
 * Called by controller to transmit messaging transactions not dealing with
 * Interface/Value elements. (e.g. transmittting a message to assign logical
 * address to a slave device
 *
 * Return: -ETIMEDOUT: If transmission of this message समयd out
 *	(e.g. due to bus lines not being घड़ीed or driven by controller)
 */
पूर्णांक slim_करो_transfer(काष्ठा slim_controller *ctrl, काष्ठा slim_msg_txn *txn)
अणु
	DECLARE_COMPLETION_ONSTACK(करोne);
	bool need_tid = false, clk_छोड़ो_msg = false;
	पूर्णांक ret, समयout;

	/*
	 * करो not vote क्रम runसमय-PM अगर the transactions are part of घड़ी
	 * छोड़ो sequence
	 */
	अगर (ctrl->sched.clk_state == SLIM_CLK_ENTERING_PAUSE &&
		(txn->mt == SLIM_MSG_MT_CORE &&
		 txn->mc >= SLIM_MSG_MC_BEGIN_RECONFIGURATION &&
		 txn->mc <= SLIM_MSG_MC_RECONFIGURE_NOW))
		clk_छोड़ो_msg = true;

	अगर (!clk_छोड़ो_msg) अणु
		ret = pm_runसमय_get_sync(ctrl->dev);
		अगर (ctrl->sched.clk_state != SLIM_CLK_ACTIVE) अणु
			dev_err(ctrl->dev, "ctrl wrong state:%d, ret:%d\n",
				ctrl->sched.clk_state, ret);
			जाओ slim_xfer_err;
		पूर्ण
	पूर्ण

	need_tid = slim_tid_txn(txn->mt, txn->mc);

	अगर (need_tid) अणु
		ret = slim_alloc_txn_tid(ctrl, txn);
		अगर (ret)
			वापस ret;

		अगर (!txn->msg->comp)
			txn->comp = &करोne;
		अन्यथा
			txn->comp = txn->comp;
	पूर्ण

	ret = ctrl->xfer_msg(ctrl, txn);

	अगर (!ret && need_tid && !txn->msg->comp) अणु
		अचिन्हित दीर्घ ms = txn->rl + HZ;

		समयout = रुको_क्रम_completion_समयout(txn->comp,
						      msecs_to_jअगरfies(ms));
		अगर (!समयout) अणु
			ret = -ETIMEDOUT;
			slim_मुक्त_txn_tid(ctrl, txn);
		पूर्ण
	पूर्ण

	अगर (ret)
		dev_err(ctrl->dev, "Tx:MT:0x%x, MC:0x%x, LA:0x%x failed:%d\n",
			txn->mt, txn->mc, txn->la, ret);

slim_xfer_err:
	अगर (!clk_छोड़ो_msg && (!need_tid  || ret == -ETIMEDOUT)) अणु
		/*
		 * हटाओ runसमय-pm vote अगर this was TX only, or
		 * अगर there was error during this transaction
		 */
		pm_runसमय_mark_last_busy(ctrl->dev);
		pm_runसमय_put_स्वतःsuspend(ctrl->dev);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(slim_करो_transfer);

अटल पूर्णांक slim_val_inf_sanity(काष्ठा slim_controller *ctrl,
			       काष्ठा slim_val_inf *msg, u8 mc)
अणु
	अगर (!msg || msg->num_bytes > 16 ||
	    (msg->start_offset + msg->num_bytes) > 0xC00)
		जाओ reterr;
	चयन (mc) अणु
	हाल SLIM_MSG_MC_REQUEST_VALUE:
	हाल SLIM_MSG_MC_REQUEST_INFORMATION:
		अगर (msg->rbuf != शून्य)
			वापस 0;
		अवरोध;

	हाल SLIM_MSG_MC_CHANGE_VALUE:
	हाल SLIM_MSG_MC_CLEAR_INFORMATION:
		अगर (msg->wbuf != शून्य)
			वापस 0;
		अवरोध;

	हाल SLIM_MSG_MC_REQUEST_CHANGE_VALUE:
	हाल SLIM_MSG_MC_REQUEST_CLEAR_INFORMATION:
		अगर (msg->rbuf != शून्य && msg->wbuf != शून्य)
			वापस 0;
		अवरोध;
	पूर्ण
reterr:
	अगर (msg)
		dev_err(ctrl->dev, "Sanity check failed:msg:offset:0x%x, mc:%d\n",
			msg->start_offset, mc);
	वापस -EINVAL;
पूर्ण

अटल u16 slim_slicesize(पूर्णांक code)
अणु
	अटल स्थिर u8 sizetocode[16] = अणु
		0, 1, 2, 3, 3, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7
	पूर्ण;

	code = clamp(code, 1, (पूर्णांक)ARRAY_SIZE(sizetocode));

	वापस sizetocode[code - 1];
पूर्ण

/**
 * slim_xfer_msg() - Transfer a value info message on slim device
 *
 * @sbdev: slim device to which this msg has to be transfered
 * @msg: value info message poपूर्णांकer
 * @mc: message code of the message
 *
 * Called by drivers which want to transfer a vlaue or info elements.
 *
 * Return: -ETIMEDOUT: If transmission of this message समयd out
 */
पूर्णांक slim_xfer_msg(काष्ठा slim_device *sbdev, काष्ठा slim_val_inf *msg,
		  u8 mc)
अणु
	DEFINE_SLIM_LDEST_TXN(txn_stack, mc, 6, sbdev->laddr, msg);
	काष्ठा slim_msg_txn *txn = &txn_stack;
	काष्ठा slim_controller *ctrl = sbdev->ctrl;
	पूर्णांक ret;
	u16 sl;

	अगर (!ctrl)
		वापस -EINVAL;

	ret = slim_val_inf_sanity(ctrl, msg, mc);
	अगर (ret)
		वापस ret;

	sl = slim_slicesize(msg->num_bytes);

	dev_dbg(ctrl->dev, "SB xfer msg:os:%x, len:%d, MC:%x, sl:%x\n",
		msg->start_offset, msg->num_bytes, mc, sl);

	txn->ec = ((sl | (1 << 3)) | ((msg->start_offset & 0xFFF) << 4));

	चयन (mc) अणु
	हाल SLIM_MSG_MC_REQUEST_CHANGE_VALUE:
	हाल SLIM_MSG_MC_CHANGE_VALUE:
	हाल SLIM_MSG_MC_REQUEST_CLEAR_INFORMATION:
	हाल SLIM_MSG_MC_CLEAR_INFORMATION:
		txn->rl += msg->num_bytes;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (slim_tid_txn(txn->mt, txn->mc))
		txn->rl++;

	वापस slim_करो_transfer(ctrl, txn);
पूर्ण
EXPORT_SYMBOL_GPL(slim_xfer_msg);

अटल व्योम slim_fill_msg(काष्ठा slim_val_inf *msg, u32 addr,
			 माप_प्रकार count, u8 *rbuf, u8 *wbuf)
अणु
	msg->start_offset = addr;
	msg->num_bytes = count;
	msg->rbuf = rbuf;
	msg->wbuf = wbuf;
	msg->comp = शून्य;
पूर्ण

/**
 * slim_पढ़ो() - Read SLIMbus value element
 *
 * @sdev: client handle.
 * @addr:  address of value element to पढ़ो.
 * @count: number of bytes to पढ़ो. Maximum bytes allowed are 16.
 * @val: will वापस what the value element value was
 *
 * Return: -EINVAL क्रम Invalid parameters, -ETIMEDOUT If transmission of
 * this message समयd out (e.g. due to bus lines not being घड़ीed
 * or driven by controller)
 */
पूर्णांक slim_पढ़ो(काष्ठा slim_device *sdev, u32 addr, माप_प्रकार count, u8 *val)
अणु
	काष्ठा slim_val_inf msg;

	slim_fill_msg(&msg, addr, count, val, शून्य);

	वापस slim_xfer_msg(sdev, &msg, SLIM_MSG_MC_REQUEST_VALUE);
पूर्ण
EXPORT_SYMBOL_GPL(slim_पढ़ो);

/**
 * slim_पढ़ोb() - Read byte from SLIMbus value element
 *
 * @sdev: client handle.
 * @addr:  address in the value element to पढ़ो.
 *
 * Return: byte value of value element.
 */
पूर्णांक slim_पढ़ोb(काष्ठा slim_device *sdev, u32 addr)
अणु
	पूर्णांक ret;
	u8 buf;

	ret = slim_पढ़ो(sdev, addr, 1, &buf);
	अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस buf;
पूर्ण
EXPORT_SYMBOL_GPL(slim_पढ़ोb);

/**
 * slim_ग_लिखो() - Write SLIMbus value element
 *
 * @sdev: client handle.
 * @addr:  address in the value element to ग_लिखो.
 * @count: number of bytes to ग_लिखो. Maximum bytes allowed are 16.
 * @val: value to ग_लिखो to value element
 *
 * Return: -EINVAL क्रम Invalid parameters, -ETIMEDOUT If transmission of
 * this message समयd out (e.g. due to bus lines not being घड़ीed
 * or driven by controller)
 */
पूर्णांक slim_ग_लिखो(काष्ठा slim_device *sdev, u32 addr, माप_प्रकार count, u8 *val)
अणु
	काष्ठा slim_val_inf msg;

	slim_fill_msg(&msg, addr, count,  शून्य, val);

	वापस slim_xfer_msg(sdev, &msg, SLIM_MSG_MC_CHANGE_VALUE);
पूर्ण
EXPORT_SYMBOL_GPL(slim_ग_लिखो);

/**
 * slim_ग_लिखोb() - Write byte to SLIMbus value element
 *
 * @sdev: client handle.
 * @addr:  address of value element to ग_लिखो.
 * @value: value to ग_लिखो to value element
 *
 * Return: -EINVAL क्रम Invalid parameters, -ETIMEDOUT If transmission of
 * this message समयd out (e.g. due to bus lines not being घड़ीed
 * or driven by controller)
 *
 */
पूर्णांक slim_ग_लिखोb(काष्ठा slim_device *sdev, u32 addr, u8 value)
अणु
	वापस slim_ग_लिखो(sdev, addr, 1, &value);
पूर्ण
EXPORT_SYMBOL_GPL(slim_ग_लिखोb);
