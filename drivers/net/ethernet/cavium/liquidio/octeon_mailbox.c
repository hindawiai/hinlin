<शैली गुरु>
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2016 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more details.
 ***********************************************************************/
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश "liquidio_common.h"
#समावेश "octeon_droq.h"
#समावेश "octeon_iq.h"
#समावेश "response_manager.h"
#समावेश "octeon_device.h"
#समावेश "octeon_main.h"
#समावेश "octeon_mailbox.h"
#समावेश "cn23xx_pf_device.h"

/**
 * octeon_mbox_पढ़ो:
 * @mbox: Poपूर्णांकer mailbox
 *
 * Reads the 8-bytes of data from the mbox रेजिस्टर
 * Writes back the acknowldgement inidcating completion of पढ़ो
 */
पूर्णांक octeon_mbox_पढ़ो(काष्ठा octeon_mbox *mbox)
अणु
	जोड़ octeon_mbox_message msg;
	पूर्णांक ret = 0;

	spin_lock(&mbox->lock);

	msg.u64 = पढ़ोq(mbox->mbox_पढ़ो_reg);

	अगर ((msg.u64 == OCTEON_PFVFACK) || (msg.u64 == OCTEON_PFVFSIG)) अणु
		spin_unlock(&mbox->lock);
		वापस 0;
	पूर्ण

	अगर (mbox->state & OCTEON_MBOX_STATE_REQUEST_RECEIVING) अणु
		mbox->mbox_req.data[mbox->mbox_req.recv_len - 1] = msg.u64;
		mbox->mbox_req.recv_len++;
	पूर्ण अन्यथा अणु
		अगर (mbox->state & OCTEON_MBOX_STATE_RESPONSE_RECEIVING) अणु
			mbox->mbox_resp.data[mbox->mbox_resp.recv_len - 1] =
				msg.u64;
			mbox->mbox_resp.recv_len++;
		पूर्ण अन्यथा अणु
			अगर ((mbox->state & OCTEON_MBOX_STATE_IDLE) &&
			    (msg.s.type == OCTEON_MBOX_REQUEST)) अणु
				mbox->state &= ~OCTEON_MBOX_STATE_IDLE;
				mbox->state |=
				    OCTEON_MBOX_STATE_REQUEST_RECEIVING;
				mbox->mbox_req.msg.u64 = msg.u64;
				mbox->mbox_req.q_no = mbox->q_no;
				mbox->mbox_req.recv_len = 1;
			पूर्ण अन्यथा अणु
				अगर ((mbox->state &
				     OCTEON_MBOX_STATE_RESPONSE_PENDING) &&
				    (msg.s.type == OCTEON_MBOX_RESPONSE)) अणु
					mbox->state &=
					    ~OCTEON_MBOX_STATE_RESPONSE_PENDING;
					mbox->state |=
					    OCTEON_MBOX_STATE_RESPONSE_RECEIVING
					    ;
					mbox->mbox_resp.msg.u64 = msg.u64;
					mbox->mbox_resp.q_no = mbox->q_no;
					mbox->mbox_resp.recv_len = 1;
				पूर्ण अन्यथा अणु
					ग_लिखोq(OCTEON_PFVFERR,
					       mbox->mbox_पढ़ो_reg);
					mbox->state |= OCTEON_MBOX_STATE_ERROR;
					spin_unlock(&mbox->lock);
					वापस 1;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (mbox->state & OCTEON_MBOX_STATE_REQUEST_RECEIVING) अणु
		अगर (mbox->mbox_req.recv_len < mbox->mbox_req.msg.s.len) अणु
			ret = 0;
		पूर्ण अन्यथा अणु
			mbox->state &= ~OCTEON_MBOX_STATE_REQUEST_RECEIVING;
			mbox->state |= OCTEON_MBOX_STATE_REQUEST_RECEIVED;
			ret = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (mbox->state & OCTEON_MBOX_STATE_RESPONSE_RECEIVING) अणु
			अगर (mbox->mbox_resp.recv_len <
			    mbox->mbox_resp.msg.s.len) अणु
				ret = 0;
			पूर्ण अन्यथा अणु
				mbox->state &=
				    ~OCTEON_MBOX_STATE_RESPONSE_RECEIVING;
				mbox->state |=
				    OCTEON_MBOX_STATE_RESPONSE_RECEIVED;
				ret = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			WARN_ON(1);
		पूर्ण
	पूर्ण

	ग_लिखोq(OCTEON_PFVFACK, mbox->mbox_पढ़ो_reg);

	spin_unlock(&mbox->lock);

	वापस ret;
पूर्ण

/**
 * octeon_mbox_ग_लिखो:
 * @oct: Poपूर्णांकer Octeon Device
 * @mbox_cmd: Cmd to send to mailbox.
 *
 * Populates the queue specअगरic mbox काष्ठाure
 * with cmd inक्रमmation.
 * Write the cmd to mbox रेजिस्टर
 */
पूर्णांक octeon_mbox_ग_लिखो(काष्ठा octeon_device *oct,
		      काष्ठा octeon_mbox_cmd *mbox_cmd)
अणु
	काष्ठा octeon_mbox *mbox = oct->mbox[mbox_cmd->q_no];
	u32 count, i, ret = OCTEON_MBOX_STATUS_SUCCESS;
	दीर्घ समयout = LIO_MBOX_WRITE_WAIT_TIME;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mbox->lock, flags);

	अगर ((mbox_cmd->msg.s.type == OCTEON_MBOX_RESPONSE) &&
	    !(mbox->state & OCTEON_MBOX_STATE_REQUEST_RECEIVED)) अणु
		spin_unlock_irqrestore(&mbox->lock, flags);
		वापस OCTEON_MBOX_STATUS_FAILED;
	पूर्ण

	अगर ((mbox_cmd->msg.s.type == OCTEON_MBOX_REQUEST) &&
	    !(mbox->state & OCTEON_MBOX_STATE_IDLE)) अणु
		spin_unlock_irqrestore(&mbox->lock, flags);
		वापस OCTEON_MBOX_STATUS_BUSY;
	पूर्ण

	अगर (mbox_cmd->msg.s.type == OCTEON_MBOX_REQUEST) अणु
		स_नकल(&mbox->mbox_resp, mbox_cmd,
		       माप(काष्ठा octeon_mbox_cmd));
		mbox->state = OCTEON_MBOX_STATE_RESPONSE_PENDING;
	पूर्ण

	spin_unlock_irqrestore(&mbox->lock, flags);

	count = 0;

	जबतक (पढ़ोq(mbox->mbox_ग_लिखो_reg) != OCTEON_PFVFSIG) अणु
		schedule_समयout_unपूर्णांकerruptible(समयout);
		अगर (count++ == LIO_MBOX_WRITE_WAIT_CNT) अणु
			ret = OCTEON_MBOX_STATUS_FAILED;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret == OCTEON_MBOX_STATUS_SUCCESS) अणु
		ग_लिखोq(mbox_cmd->msg.u64, mbox->mbox_ग_लिखो_reg);
		क्रम (i = 0; i < (u32)(mbox_cmd->msg.s.len - 1); i++) अणु
			count = 0;
			जबतक (पढ़ोq(mbox->mbox_ग_लिखो_reg) !=
			       OCTEON_PFVFACK) अणु
				schedule_समयout_unपूर्णांकerruptible(समयout);
				अगर (count++ == LIO_MBOX_WRITE_WAIT_CNT) अणु
					ret = OCTEON_MBOX_STATUS_FAILED;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (ret == OCTEON_MBOX_STATUS_SUCCESS)
				ग_लिखोq(mbox_cmd->data[i], mbox->mbox_ग_लिखो_reg);
			अन्यथा
				अवरोध;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&mbox->lock, flags);
	अगर (mbox_cmd->msg.s.type == OCTEON_MBOX_RESPONSE) अणु
		mbox->state = OCTEON_MBOX_STATE_IDLE;
		ग_लिखोq(OCTEON_PFVFSIG, mbox->mbox_पढ़ो_reg);
	पूर्ण अन्यथा अणु
		अगर ((!mbox_cmd->msg.s.resp_needed) ||
		    (ret == OCTEON_MBOX_STATUS_FAILED)) अणु
			mbox->state &= ~OCTEON_MBOX_STATE_RESPONSE_PENDING;
			अगर (!(mbox->state &
			      (OCTEON_MBOX_STATE_REQUEST_RECEIVING |
			       OCTEON_MBOX_STATE_REQUEST_RECEIVED)))
				mbox->state = OCTEON_MBOX_STATE_IDLE;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&mbox->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम get_vf_stats(काष्ठा octeon_device *oct,
			 काष्ठा oct_vf_stats *stats)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < oct->num_iqs; i++) अणु
		अगर (!oct->instr_queue[i])
			जारी;
		stats->tx_packets += oct->instr_queue[i]->stats.tx_करोne;
		stats->tx_bytes += oct->instr_queue[i]->stats.tx_tot_bytes;
	पूर्ण

	क्रम (i = 0; i < oct->num_oqs; i++) अणु
		अगर (!oct->droq[i])
			जारी;
		stats->rx_packets += oct->droq[i]->stats.rx_pkts_received;
		stats->rx_bytes += oct->droq[i]->stats.rx_bytes_received;
	पूर्ण
पूर्ण

/**
 * octeon_mbox_process_cmd:
 * @mbox: Poपूर्णांकer mailbox
 * @mbox_cmd: Poपूर्णांकer to command received
 *
 * Process the cmd received in mbox
 */
अटल पूर्णांक octeon_mbox_process_cmd(काष्ठा octeon_mbox *mbox,
				   काष्ठा octeon_mbox_cmd *mbox_cmd)
अणु
	काष्ठा octeon_device *oct = mbox->oct_dev;

	चयन (mbox_cmd->msg.s.cmd) अणु
	हाल OCTEON_VF_ACTIVE:
		dev_dbg(&oct->pci_dev->dev, "got vfactive sending data back\n");
		mbox_cmd->msg.s.type = OCTEON_MBOX_RESPONSE;
		mbox_cmd->msg.s.resp_needed = 1;
		mbox_cmd->msg.s.len = 2;
		mbox_cmd->data[0] = 0; /* VF version is in mbox_cmd->data[0] */
		((काष्ठा lio_version *)&mbox_cmd->data[0])->major =
			LIQUIDIO_BASE_MAJOR_VERSION;
		((काष्ठा lio_version *)&mbox_cmd->data[0])->minor =
			LIQUIDIO_BASE_MINOR_VERSION;
		((काष्ठा lio_version *)&mbox_cmd->data[0])->micro =
			LIQUIDIO_BASE_MICRO_VERSION;
		स_नकल(mbox_cmd->msg.s.params, (uपूर्णांक8_t *)&oct->pfvf_hsword, 6);
		/* Sending core cofig info to the corresponding active VF.*/
		octeon_mbox_ग_लिखो(oct, mbox_cmd);
		अवरोध;

	हाल OCTEON_VF_FLR_REQUEST:
		dev_info(&oct->pci_dev->dev,
			 "got a request for FLR from VF that owns DPI ring %u\n",
			 mbox->q_no);
		pcie_flr(oct->sriov_info.dpiring_to_vfpcidev_lut[mbox->q_no]);
		अवरोध;

	हाल OCTEON_PF_CHANGED_VF_MACADDR:
		अगर (OCTEON_CN23XX_VF(oct))
			octeon_pf_changed_vf_macaddr(oct,
						     mbox_cmd->msg.s.params);
		अवरोध;

	हाल OCTEON_GET_VF_STATS:
		dev_dbg(&oct->pci_dev->dev, "Got VF stats request. Sending data back\n");
		mbox_cmd->msg.s.type = OCTEON_MBOX_RESPONSE;
		mbox_cmd->msg.s.resp_needed = 1;
		mbox_cmd->msg.s.len = 1 +
			माप(काष्ठा oct_vf_stats) / माप(u64);
		get_vf_stats(oct, (काष्ठा oct_vf_stats *)mbox_cmd->data);
		octeon_mbox_ग_लिखो(oct, mbox_cmd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * octeon_mbox_process_message
 * @mbox: mailbox
 *
 * Process the received mbox message.
 */
पूर्णांक octeon_mbox_process_message(काष्ठा octeon_mbox *mbox)
अणु
	काष्ठा octeon_mbox_cmd mbox_cmd;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mbox->lock, flags);

	अगर (mbox->state & OCTEON_MBOX_STATE_ERROR) अणु
		अगर (mbox->state & (OCTEON_MBOX_STATE_RESPONSE_PENDING |
				   OCTEON_MBOX_STATE_RESPONSE_RECEIVING)) अणु
			स_नकल(&mbox_cmd, &mbox->mbox_resp,
			       माप(काष्ठा octeon_mbox_cmd));
			mbox->state = OCTEON_MBOX_STATE_IDLE;
			ग_लिखोq(OCTEON_PFVFSIG, mbox->mbox_पढ़ो_reg);
			spin_unlock_irqrestore(&mbox->lock, flags);
			mbox_cmd.recv_status = 1;
			अगर (mbox_cmd.fn)
				mbox_cmd.fn(mbox->oct_dev, &mbox_cmd,
					    mbox_cmd.fn_arg);
			वापस 0;
		पूर्ण

		mbox->state = OCTEON_MBOX_STATE_IDLE;
		ग_लिखोq(OCTEON_PFVFSIG, mbox->mbox_पढ़ो_reg);
		spin_unlock_irqrestore(&mbox->lock, flags);
		वापस 0;
	पूर्ण

	अगर (mbox->state & OCTEON_MBOX_STATE_RESPONSE_RECEIVED) अणु
		स_नकल(&mbox_cmd, &mbox->mbox_resp,
		       माप(काष्ठा octeon_mbox_cmd));
		mbox->state = OCTEON_MBOX_STATE_IDLE;
		ग_लिखोq(OCTEON_PFVFSIG, mbox->mbox_पढ़ो_reg);
		spin_unlock_irqrestore(&mbox->lock, flags);
		mbox_cmd.recv_status = 0;
		अगर (mbox_cmd.fn)
			mbox_cmd.fn(mbox->oct_dev, &mbox_cmd, mbox_cmd.fn_arg);
		वापस 0;
	पूर्ण

	अगर (mbox->state & OCTEON_MBOX_STATE_REQUEST_RECEIVED) अणु
		स_नकल(&mbox_cmd, &mbox->mbox_req,
		       माप(काष्ठा octeon_mbox_cmd));
		अगर (!mbox_cmd.msg.s.resp_needed) अणु
			mbox->state &= ~OCTEON_MBOX_STATE_REQUEST_RECEIVED;
			अगर (!(mbox->state &
			      OCTEON_MBOX_STATE_RESPONSE_PENDING))
				mbox->state = OCTEON_MBOX_STATE_IDLE;
			ग_लिखोq(OCTEON_PFVFSIG, mbox->mbox_पढ़ो_reg);
		पूर्ण

		spin_unlock_irqrestore(&mbox->lock, flags);
		octeon_mbox_process_cmd(mbox, &mbox_cmd);
		वापस 0;
	पूर्ण

	spin_unlock_irqrestore(&mbox->lock, flags);
	WARN_ON(1);

	वापस 0;
पूर्ण

पूर्णांक octeon_mbox_cancel(काष्ठा octeon_device *oct, पूर्णांक q_no)
अणु
	काष्ठा octeon_mbox *mbox = oct->mbox[q_no];
	काष्ठा octeon_mbox_cmd *mbox_cmd;
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(&mbox->lock, flags);
	mbox_cmd = &mbox->mbox_resp;

	अगर (!(mbox->state & OCTEON_MBOX_STATE_RESPONSE_PENDING)) अणु
		spin_unlock_irqrestore(&mbox->lock, flags);
		वापस 1;
	पूर्ण

	mbox->state = OCTEON_MBOX_STATE_IDLE;
	स_रखो(mbox_cmd, 0, माप(*mbox_cmd));
	ग_लिखोq(OCTEON_PFVFSIG, mbox->mbox_पढ़ो_reg);
	spin_unlock_irqrestore(&mbox->lock, flags);

	वापस 0;
पूर्ण
