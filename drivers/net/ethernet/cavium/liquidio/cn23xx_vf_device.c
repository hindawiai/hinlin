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
#समावेश <linux/vदो_स्मृति.h>
#समावेश "liquidio_common.h"
#समावेश "octeon_droq.h"
#समावेश "octeon_iq.h"
#समावेश "response_manager.h"
#समावेश "octeon_device.h"
#समावेश "cn23xx_vf_device.h"
#समावेश "octeon_main.h"
#समावेश "octeon_mailbox.h"

u32 cn23xx_vf_get_oq_ticks(काष्ठा octeon_device *oct, u32 समय_पूर्णांकr_in_us)
अणु
	/* This gives the SLI घड़ी per microsec */
	u32 oqticks_per_us = (u32)oct->pfvf_hsword.coproc_tics_per_us;

	/* This gives the घड़ी cycles per millisecond */
	oqticks_per_us *= 1000;

	/* This gives the oq ticks (1024 core घड़ी cycles) per millisecond */
	oqticks_per_us /= 1024;

	/* समय_पूर्णांकr is in microseconds. The next 2 steps gives the oq ticks
	 * corressponding to समय_पूर्णांकr.
	 */
	oqticks_per_us *= समय_पूर्णांकr_in_us;
	oqticks_per_us /= 1000;

	वापस oqticks_per_us;
पूर्ण

अटल पूर्णांक cn23xx_vf_reset_io_queues(काष्ठा octeon_device *oct, u32 num_queues)
अणु
	u32 loop = BUSY_READING_REG_VF_LOOP_COUNT;
	पूर्णांक ret_val = 0;
	u32 q_no;
	u64 d64;

	क्रम (q_no = 0; q_no < num_queues; q_no++) अणु
		/* set RST bit to 1. This bit applies to both IQ and OQ */
		d64 = octeon_पढ़ो_csr64(oct,
					CN23XX_VF_SLI_IQ_PKT_CONTROL64(q_no));
		d64 |= CN23XX_PKT_INPUT_CTL_RST;
		octeon_ग_लिखो_csr64(oct, CN23XX_VF_SLI_IQ_PKT_CONTROL64(q_no),
				   d64);
	पूर्ण

	/* रुको until the RST bit is clear or the RST and QUIET bits are set */
	क्रम (q_no = 0; q_no < num_queues; q_no++) अणु
		u64 reg_val = octeon_पढ़ो_csr64(oct,
					CN23XX_VF_SLI_IQ_PKT_CONTROL64(q_no));
		जबतक ((READ_ONCE(reg_val) & CN23XX_PKT_INPUT_CTL_RST) &&
		       !(READ_ONCE(reg_val) & CN23XX_PKT_INPUT_CTL_QUIET) &&
		       loop) अणु
			WRITE_ONCE(reg_val, octeon_पढ़ो_csr64(
			    oct, CN23XX_VF_SLI_IQ_PKT_CONTROL64(q_no)));
			loop--;
		पूर्ण
		अगर (!loop) अणु
			dev_err(&oct->pci_dev->dev,
				"clearing the reset reg failed or setting the quiet reg failed for qno: %u\n",
				q_no);
			वापस -1;
		पूर्ण
		WRITE_ONCE(reg_val, READ_ONCE(reg_val) &
			   ~CN23XX_PKT_INPUT_CTL_RST);
		octeon_ग_लिखो_csr64(oct, CN23XX_VF_SLI_IQ_PKT_CONTROL64(q_no),
				   READ_ONCE(reg_val));

		WRITE_ONCE(reg_val, octeon_पढ़ो_csr64(
		    oct, CN23XX_VF_SLI_IQ_PKT_CONTROL64(q_no)));
		अगर (READ_ONCE(reg_val) & CN23XX_PKT_INPUT_CTL_RST) अणु
			dev_err(&oct->pci_dev->dev,
				"clearing the reset failed for qno: %u\n",
				q_no);
			ret_val = -1;
		पूर्ण
	पूर्ण

	वापस ret_val;
पूर्ण

अटल पूर्णांक cn23xx_vf_setup_global_input_regs(काष्ठा octeon_device *oct)
अणु
	काष्ठा octeon_cn23xx_vf *cn23xx = (काष्ठा octeon_cn23xx_vf *)oct->chip;
	काष्ठा octeon_instr_queue *iq;
	u64 q_no, पूर्णांकr_threshold;
	u64 d64;

	अगर (cn23xx_vf_reset_io_queues(oct, oct->sriov_info.rings_per_vf))
		वापस -1;

	क्रम (q_no = 0; q_no < (oct->sriov_info.rings_per_vf); q_no++) अणु
		व्योम __iomem *inst_cnt_reg;

		octeon_ग_लिखो_csr64(oct, CN23XX_VF_SLI_IQ_DOORBELL(q_no),
				   0xFFFFFFFF);
		iq = oct->instr_queue[q_no];

		अगर (iq)
			inst_cnt_reg = iq->inst_cnt_reg;
		अन्यथा
			inst_cnt_reg = (u8 *)oct->mmio[0].hw_addr +
				       CN23XX_VF_SLI_IQ_INSTR_COUNT64(q_no);

		d64 = octeon_पढ़ो_csr64(oct,
					CN23XX_VF_SLI_IQ_INSTR_COUNT64(q_no));

		d64 &= 0xEFFFFFFFFFFFFFFFL;

		octeon_ग_लिखो_csr64(oct, CN23XX_VF_SLI_IQ_INSTR_COUNT64(q_no),
				   d64);

		/* Select ES, RO, NS, RDSIZE,DPTR Fomat#0 क्रम
		 * the Input Queues
		 */
		octeon_ग_लिखो_csr64(oct, CN23XX_VF_SLI_IQ_PKT_CONTROL64(q_no),
				   CN23XX_PKT_INPUT_CTL_MASK);

		/* set the wmark level to trigger PI_INT */
		पूर्णांकr_threshold = CFG_GET_IQ_INTR_PKT(cn23xx->conf) &
				 CN23XX_PKT_IN_DONE_WMARK_MASK;

		ग_लिखोq((पढ़ोq(inst_cnt_reg) &
			~(CN23XX_PKT_IN_DONE_WMARK_MASK <<
			  CN23XX_PKT_IN_DONE_WMARK_BIT_POS)) |
		       (पूर्णांकr_threshold << CN23XX_PKT_IN_DONE_WMARK_BIT_POS),
		       inst_cnt_reg);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cn23xx_vf_setup_global_output_regs(काष्ठा octeon_device *oct)
अणु
	u32 reg_val;
	u32 q_no;

	क्रम (q_no = 0; q_no < (oct->sriov_info.rings_per_vf); q_no++) अणु
		octeon_ग_लिखो_csr(oct, CN23XX_VF_SLI_OQ_PKTS_CREDIT(q_no),
				 0xFFFFFFFF);

		reg_val =
		    octeon_पढ़ो_csr(oct, CN23XX_VF_SLI_OQ_PKTS_SENT(q_no));

		reg_val &= 0xEFFFFFFFFFFFFFFFL;

		reg_val =
		    octeon_पढ़ो_csr(oct, CN23XX_VF_SLI_OQ_PKT_CONTROL(q_no));

		/* clear IPTR */
		reg_val &= ~CN23XX_PKT_OUTPUT_CTL_IPTR;

		/* set DPTR */
		reg_val |= CN23XX_PKT_OUTPUT_CTL_DPTR;

		/* reset BMODE */
		reg_val &= ~(CN23XX_PKT_OUTPUT_CTL_BMODE);

		/* No Relaxed Ordering, No Snoop, 64-bit Byte swap
		 * क्रम Output Queue ScatterList reset ROR_P, NSR_P
		 */
		reg_val &= ~(CN23XX_PKT_OUTPUT_CTL_ROR_P);
		reg_val &= ~(CN23XX_PKT_OUTPUT_CTL_NSR_P);

#अगर_घोषित __LITTLE_ENDIAN_BITFIELD
		reg_val &= ~(CN23XX_PKT_OUTPUT_CTL_ES_P);
#अन्यथा
		reg_val |= (CN23XX_PKT_OUTPUT_CTL_ES_P);
#पूर्ण_अगर
		/* No Relaxed Ordering, No Snoop, 64-bit Byte swap
		 * क्रम Output Queue Data reset ROR, NSR
		 */
		reg_val &= ~(CN23XX_PKT_OUTPUT_CTL_ROR);
		reg_val &= ~(CN23XX_PKT_OUTPUT_CTL_NSR);
		/* set the ES bit */
		reg_val |= (CN23XX_PKT_OUTPUT_CTL_ES);

		/* ग_लिखो all the selected settings */
		octeon_ग_लिखो_csr(oct, CN23XX_VF_SLI_OQ_PKT_CONTROL(q_no),
				 reg_val);
	पूर्ण
पूर्ण

अटल पूर्णांक cn23xx_setup_vf_device_regs(काष्ठा octeon_device *oct)
अणु
	अगर (cn23xx_vf_setup_global_input_regs(oct))
		वापस -1;

	cn23xx_vf_setup_global_output_regs(oct);

	वापस 0;
पूर्ण

अटल व्योम cn23xx_setup_vf_iq_regs(काष्ठा octeon_device *oct, u32 iq_no)
अणु
	काष्ठा octeon_instr_queue *iq = oct->instr_queue[iq_no];
	u64 pkt_in_करोne;

	/* Write the start of the input queue's ring and its size */
	octeon_ग_लिखो_csr64(oct, CN23XX_VF_SLI_IQ_BASE_ADDR64(iq_no),
			   iq->base_addr_dma);
	octeon_ग_लिखो_csr(oct, CN23XX_VF_SLI_IQ_SIZE(iq_no), iq->max_count);

	/* Remember the करोorbell & inकाष्ठाion count रेजिस्टर addr
	 * क्रम this queue
	 */
	iq->करोorbell_reg =
	    (u8 *)oct->mmio[0].hw_addr + CN23XX_VF_SLI_IQ_DOORBELL(iq_no);
	iq->inst_cnt_reg =
	    (u8 *)oct->mmio[0].hw_addr + CN23XX_VF_SLI_IQ_INSTR_COUNT64(iq_no);
	dev_dbg(&oct->pci_dev->dev, "InstQ[%d]:dbell reg @ 0x%p instcnt_reg @ 0x%p\n",
		iq_no, iq->करोorbell_reg, iq->inst_cnt_reg);

	/* Store the current inकाष्ठाion counter (used in flush_iq
	 * calculation)
	 */
	pkt_in_करोne = पढ़ोq(iq->inst_cnt_reg);

	अगर (oct->msix_on) अणु
		/* Set CINT_ENB to enable IQ पूर्णांकerrupt */
		ग_लिखोq((pkt_in_करोne | CN23XX_INTR_CINT_ENB),
		       iq->inst_cnt_reg);
	पूर्ण
	iq->reset_instr_cnt = 0;
पूर्ण

अटल व्योम cn23xx_setup_vf_oq_regs(काष्ठा octeon_device *oct, u32 oq_no)
अणु
	काष्ठा octeon_droq *droq = oct->droq[oq_no];

	octeon_ग_लिखो_csr64(oct, CN23XX_VF_SLI_OQ_BASE_ADDR64(oq_no),
			   droq->desc_ring_dma);
	octeon_ग_लिखो_csr(oct, CN23XX_VF_SLI_OQ_SIZE(oq_no), droq->max_count);

	octeon_ग_लिखो_csr(oct, CN23XX_VF_SLI_OQ_BUFF_INFO_SIZE(oq_no),
			 droq->buffer_size);

	/* Get the mapped address of the pkt_sent and pkts_credit regs */
	droq->pkts_sent_reg =
	    (u8 *)oct->mmio[0].hw_addr + CN23XX_VF_SLI_OQ_PKTS_SENT(oq_no);
	droq->pkts_credit_reg =
	    (u8 *)oct->mmio[0].hw_addr + CN23XX_VF_SLI_OQ_PKTS_CREDIT(oq_no);
पूर्ण

अटल व्योम cn23xx_vf_mbox_thपढ़ो(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cavium_wk *wk = (काष्ठा cavium_wk *)work;
	काष्ठा octeon_mbox *mbox = (काष्ठा octeon_mbox *)wk->ctxptr;

	octeon_mbox_process_message(mbox);
पूर्ण

अटल पूर्णांक cn23xx_मुक्त_vf_mbox(काष्ठा octeon_device *oct)
अणु
	cancel_delayed_work_sync(&oct->mbox[0]->mbox_poll_wk.work);
	vमुक्त(oct->mbox[0]);
	वापस 0;
पूर्ण

अटल पूर्णांक cn23xx_setup_vf_mbox(काष्ठा octeon_device *oct)
अणु
	काष्ठा octeon_mbox *mbox = शून्य;

	mbox = vदो_स्मृति(माप(*mbox));
	अगर (!mbox)
		वापस 1;

	स_रखो(mbox, 0, माप(काष्ठा octeon_mbox));

	spin_lock_init(&mbox->lock);

	mbox->oct_dev = oct;

	mbox->q_no = 0;

	mbox->state = OCTEON_MBOX_STATE_IDLE;

	/* VF mbox पूर्णांकerrupt reg */
	mbox->mbox_पूर्णांक_reg =
	    (u8 *)oct->mmio[0].hw_addr + CN23XX_VF_SLI_PKT_MBOX_INT(0);
	/* VF पढ़ोs from SIG0 reg */
	mbox->mbox_पढ़ो_reg =
	    (u8 *)oct->mmio[0].hw_addr + CN23XX_SLI_PKT_PF_VF_MBOX_SIG(0, 0);
	/* VF ग_लिखोs पूर्णांकo SIG1 reg */
	mbox->mbox_ग_लिखो_reg =
	    (u8 *)oct->mmio[0].hw_addr + CN23XX_SLI_PKT_PF_VF_MBOX_SIG(0, 1);

	INIT_DELAYED_WORK(&mbox->mbox_poll_wk.work,
			  cn23xx_vf_mbox_thपढ़ो);

	mbox->mbox_poll_wk.ctxptr = mbox;

	oct->mbox[0] = mbox;

	ग_लिखोq(OCTEON_PFVFSIG, mbox->mbox_पढ़ो_reg);

	वापस 0;
पूर्ण

अटल पूर्णांक cn23xx_enable_vf_io_queues(काष्ठा octeon_device *oct)
अणु
	u32 q_no;

	क्रम (q_no = 0; q_no < oct->num_iqs; q_no++) अणु
		u64 reg_val;

		/* set the corresponding IQ IS_64B bit */
		अगर (oct->io_qmask.iq64B & BIT_ULL(q_no)) अणु
			reg_val = octeon_पढ़ो_csr64(
			    oct, CN23XX_VF_SLI_IQ_PKT_CONTROL64(q_no));
			reg_val |= CN23XX_PKT_INPUT_CTL_IS_64B;
			octeon_ग_लिखो_csr64(
			    oct, CN23XX_VF_SLI_IQ_PKT_CONTROL64(q_no), reg_val);
		पूर्ण

		/* set the corresponding IQ ENB bit */
		अगर (oct->io_qmask.iq & BIT_ULL(q_no)) अणु
			reg_val = octeon_पढ़ो_csr64(
			    oct, CN23XX_VF_SLI_IQ_PKT_CONTROL64(q_no));
			reg_val |= CN23XX_PKT_INPUT_CTL_RING_ENB;
			octeon_ग_लिखो_csr64(
			    oct, CN23XX_VF_SLI_IQ_PKT_CONTROL64(q_no), reg_val);
		पूर्ण
	पूर्ण
	क्रम (q_no = 0; q_no < oct->num_oqs; q_no++) अणु
		u32 reg_val;

		/* set the corresponding OQ ENB bit */
		अगर (oct->io_qmask.oq & BIT_ULL(q_no)) अणु
			reg_val = octeon_पढ़ो_csr(
			    oct, CN23XX_VF_SLI_OQ_PKT_CONTROL(q_no));
			reg_val |= CN23XX_PKT_OUTPUT_CTL_RING_ENB;
			octeon_ग_लिखो_csr(
			    oct, CN23XX_VF_SLI_OQ_PKT_CONTROL(q_no), reg_val);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cn23xx_disable_vf_io_queues(काष्ठा octeon_device *oct)
अणु
	u32 num_queues = oct->num_iqs;

	/* per HRM, rings can only be disabled via reset operation,
	 * NOT via SLI_PKT()_INPUT/OUTPUT_CONTROL[ENB]
	 */
	अगर (num_queues < oct->num_oqs)
		num_queues = oct->num_oqs;

	cn23xx_vf_reset_io_queues(oct, num_queues);
पूर्ण

व्योम cn23xx_vf_ask_pf_to_करो_flr(काष्ठा octeon_device *oct)
अणु
	काष्ठा octeon_mbox_cmd mbox_cmd;

	mbox_cmd.msg.u64 = 0;
	mbox_cmd.msg.s.type = OCTEON_MBOX_REQUEST;
	mbox_cmd.msg.s.resp_needed = 0;
	mbox_cmd.msg.s.cmd = OCTEON_VF_FLR_REQUEST;
	mbox_cmd.msg.s.len = 1;
	mbox_cmd.q_no = 0;
	mbox_cmd.recv_len = 0;
	mbox_cmd.recv_status = 0;
	mbox_cmd.fn = शून्य;
	mbox_cmd.fn_arg = शून्य;

	octeon_mbox_ग_लिखो(oct, &mbox_cmd);
पूर्ण

अटल व्योम octeon_pfvf_hs_callback(काष्ठा octeon_device *oct,
				    काष्ठा octeon_mbox_cmd *cmd,
				    व्योम *arg)
अणु
	u32 major = 0;

	स_नकल((uपूर्णांक8_t *)&oct->pfvf_hsword, cmd->msg.s.params,
	       CN23XX_MAILBOX_MSGPARAM_SIZE);
	अगर (cmd->recv_len > 1)  अणु
		major = ((काष्ठा lio_version *)(cmd->data))->major;
		major = major << 16;
	पूर्ण

	atomic_set((atomic_t *)arg, major | 1);
पूर्ण

पूर्णांक cn23xx_octeon_pfvf_handshake(काष्ठा octeon_device *oct)
अणु
	काष्ठा octeon_mbox_cmd mbox_cmd;
	u32 q_no, count = 0;
	atomic_t status;
	u32 pfmajor;
	u32 vfmajor;
	u32 ret;

	/* Sending VF_ACTIVE indication to the PF driver */
	dev_dbg(&oct->pci_dev->dev, "requesting info from pf\n");

	mbox_cmd.msg.u64 = 0;
	mbox_cmd.msg.s.type = OCTEON_MBOX_REQUEST;
	mbox_cmd.msg.s.resp_needed = 1;
	mbox_cmd.msg.s.cmd = OCTEON_VF_ACTIVE;
	mbox_cmd.msg.s.len = 2;
	mbox_cmd.data[0] = 0;
	((काष्ठा lio_version *)&mbox_cmd.data[0])->major =
						LIQUIDIO_BASE_MAJOR_VERSION;
	((काष्ठा lio_version *)&mbox_cmd.data[0])->minor =
						LIQUIDIO_BASE_MINOR_VERSION;
	((काष्ठा lio_version *)&mbox_cmd.data[0])->micro =
						LIQUIDIO_BASE_MICRO_VERSION;
	mbox_cmd.q_no = 0;
	mbox_cmd.recv_len = 0;
	mbox_cmd.recv_status = 0;
	mbox_cmd.fn = (octeon_mbox_callback_t)octeon_pfvf_hs_callback;
	mbox_cmd.fn_arg = &status;

	octeon_mbox_ग_लिखो(oct, &mbox_cmd);

	atomic_set(&status, 0);

	करो अणु
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण जबतक ((!atomic_पढ़ो(&status)) && (count++ < 100000));

	ret = atomic_पढ़ो(&status);
	अगर (!ret) अणु
		dev_err(&oct->pci_dev->dev, "octeon_pfvf_handshake timeout\n");
		वापस 1;
	पूर्ण

	क्रम (q_no = 0 ; q_no < oct->num_iqs ; q_no++)
		oct->instr_queue[q_no]->txpciq.s.pkind = oct->pfvf_hsword.pkind;

	vfmajor = LIQUIDIO_BASE_MAJOR_VERSION;
	pfmajor = ret >> 16;
	अगर (pfmajor != vfmajor) अणु
		dev_err(&oct->pci_dev->dev,
			"VF Liquidio driver (major version %d) is not compatible with Liquidio PF driver (major version %d)\n",
			vfmajor, pfmajor);
		वापस 1;
	पूर्ण

	dev_dbg(&oct->pci_dev->dev,
		"VF Liquidio driver (major version %d), Liquidio PF driver (major version %d)\n",
		vfmajor, pfmajor);

	dev_dbg(&oct->pci_dev->dev, "got data from pf pkind is %d\n",
		oct->pfvf_hsword.pkind);

	वापस 0;
पूर्ण

अटल व्योम cn23xx_handle_vf_mbox_पूर्णांकr(काष्ठा octeon_ioq_vector *ioq_vector)
अणु
	काष्ठा octeon_device *oct = ioq_vector->oct_dev;
	u64 mbox_पूर्णांक_val;

	अगर (!ioq_vector->droq_index) अणु
		/* पढ़ो and clear by writing 1 */
		mbox_पूर्णांक_val = पढ़ोq(oct->mbox[0]->mbox_पूर्णांक_reg);
		ग_लिखोq(mbox_पूर्णांक_val, oct->mbox[0]->mbox_पूर्णांक_reg);
		अगर (octeon_mbox_पढ़ो(oct->mbox[0]))
			schedule_delayed_work(&oct->mbox[0]->mbox_poll_wk.work,
					      msecs_to_jअगरfies(0));
	पूर्ण
पूर्ण

अटल u64 cn23xx_vf_msix_पूर्णांकerrupt_handler(व्योम *dev)
अणु
	काष्ठा octeon_ioq_vector *ioq_vector = (काष्ठा octeon_ioq_vector *)dev;
	काष्ठा octeon_device *oct = ioq_vector->oct_dev;
	काष्ठा octeon_droq *droq = oct->droq[ioq_vector->droq_index];
	u64 pkts_sent;
	u64 ret = 0;

	dev_dbg(&oct->pci_dev->dev, "In %s octeon_dev @ %p\n", __func__, oct);
	pkts_sent = पढ़ोq(droq->pkts_sent_reg);

	/* If our device has पूर्णांकerrupted, then proceed. Also check
	 * क्रम all f's अगर पूर्णांकerrupt was triggered on an error
	 * and the PCI पढ़ो fails.
	 */
	अगर (!pkts_sent || (pkts_sent == 0xFFFFFFFFFFFFFFFFULL))
		वापस ret;

	/* Write count reg in sli_pkt_cnts to clear these पूर्णांक. */
	अगर ((pkts_sent & CN23XX_INTR_PO_INT) ||
	    (pkts_sent & CN23XX_INTR_PI_INT)) अणु
		अगर (pkts_sent & CN23XX_INTR_PO_INT)
			ret |= MSIX_PO_INT;
	पूर्ण

	अगर (pkts_sent & CN23XX_INTR_PI_INT)
		/* We will clear the count when we update the पढ़ो_index. */
		ret |= MSIX_PI_INT;

	अगर (pkts_sent & CN23XX_INTR_MBOX_INT) अणु
		cn23xx_handle_vf_mbox_पूर्णांकr(ioq_vector);
		ret |= MSIX_MBOX_INT;
	पूर्ण

	वापस ret;
पूर्ण

अटल u32 cn23xx_update_पढ़ो_index(काष्ठा octeon_instr_queue *iq)
अणु
	u32 pkt_in_करोne = पढ़ोl(iq->inst_cnt_reg);
	u32 last_करोne;
	u32 new_idx;

	last_करोne = pkt_in_करोne - iq->pkt_in_करोne;
	iq->pkt_in_करोne = pkt_in_करोne;

	/* Modulo of the new index with the IQ size will give us
	 * the new index.  The iq->reset_instr_cnt is always zero क्रम
	 * cn23xx, so no extra adjusपंचांगents are needed.
	 */
	new_idx = (iq->octeon_पढ़ो_index +
		   (u32)(last_करोne & CN23XX_PKT_IN_DONE_CNT_MASK)) %
		  iq->max_count;

	वापस new_idx;
पूर्ण

अटल व्योम cn23xx_enable_vf_पूर्णांकerrupt(काष्ठा octeon_device *oct, u8 पूर्णांकr_flag)
अणु
	काष्ठा octeon_cn23xx_vf *cn23xx = (काष्ठा octeon_cn23xx_vf *)oct->chip;
	u32 q_no, समय_प्रकारhreshold;

	अगर (पूर्णांकr_flag & OCTEON_OUTPUT_INTR) अणु
		क्रम (q_no = 0; q_no < oct->num_oqs; q_no++) अणु
			/* Set up पूर्णांकerrupt packet and समय thresholds
			 * क्रम all the OQs
			 */
			समय_प्रकारhreshold = cn23xx_vf_get_oq_ticks(
				oct, (u32)CFG_GET_OQ_INTR_TIME(cn23xx->conf));

			octeon_ग_लिखो_csr64(
			    oct, CN23XX_VF_SLI_OQ_PKT_INT_LEVELS(q_no),
			    (CFG_GET_OQ_INTR_PKT(cn23xx->conf) |
			     ((u64)समय_प्रकारhreshold << 32)));
		पूर्ण
	पूर्ण

	अगर (पूर्णांकr_flag & OCTEON_INPUT_INTR) अणु
		क्रम (q_no = 0; q_no < oct->num_oqs; q_no++) अणु
			/* Set CINT_ENB to enable IQ पूर्णांकerrupt */
			octeon_ग_लिखो_csr64(
			    oct, CN23XX_VF_SLI_IQ_INSTR_COUNT64(q_no),
			    ((octeon_पढ़ो_csr64(
				  oct, CN23XX_VF_SLI_IQ_INSTR_COUNT64(q_no)) &
			      ~CN23XX_PKT_IN_DONE_CNT_MASK) |
			     CN23XX_INTR_CINT_ENB));
		पूर्ण
	पूर्ण

	/* Set queue-0 MBOX_ENB to enable VF mailbox पूर्णांकerrupt */
	अगर (पूर्णांकr_flag & OCTEON_MBOX_INTR) अणु
		octeon_ग_लिखो_csr64(
		    oct, CN23XX_VF_SLI_PKT_MBOX_INT(0),
		    (octeon_पढ़ो_csr64(oct, CN23XX_VF_SLI_PKT_MBOX_INT(0)) |
		     CN23XX_INTR_MBOX_ENB));
	पूर्ण
पूर्ण

अटल व्योम cn23xx_disable_vf_पूर्णांकerrupt(काष्ठा octeon_device *oct, u8 पूर्णांकr_flag)
अणु
	u32 q_no;

	अगर (पूर्णांकr_flag & OCTEON_OUTPUT_INTR) अणु
		क्रम (q_no = 0; q_no < oct->num_oqs; q_no++) अणु
			/* Write all 1's in INT_LEVEL reg to disable PO_INT */
			octeon_ग_लिखो_csr64(
			    oct, CN23XX_VF_SLI_OQ_PKT_INT_LEVELS(q_no),
			    0x3fffffffffffff);
		पूर्ण
	पूर्ण
	अगर (पूर्णांकr_flag & OCTEON_INPUT_INTR) अणु
		क्रम (q_no = 0; q_no < oct->num_oqs; q_no++) अणु
			octeon_ग_लिखो_csr64(
			    oct, CN23XX_VF_SLI_IQ_INSTR_COUNT64(q_no),
			    (octeon_पढ़ो_csr64(
				 oct, CN23XX_VF_SLI_IQ_INSTR_COUNT64(q_no)) &
			     ~(CN23XX_INTR_CINT_ENB |
			       CN23XX_PKT_IN_DONE_CNT_MASK)));
		पूर्ण
	पूर्ण

	अगर (पूर्णांकr_flag & OCTEON_MBOX_INTR) अणु
		octeon_ग_लिखो_csr64(
		    oct, CN23XX_VF_SLI_PKT_MBOX_INT(0),
		    (octeon_पढ़ो_csr64(oct, CN23XX_VF_SLI_PKT_MBOX_INT(0)) &
		     ~CN23XX_INTR_MBOX_ENB));
	पूर्ण
पूर्ण

पूर्णांक cn23xx_setup_octeon_vf_device(काष्ठा octeon_device *oct)
अणु
	काष्ठा octeon_cn23xx_vf *cn23xx = (काष्ठा octeon_cn23xx_vf *)oct->chip;
	u32 rings_per_vf;
	u64 reg_val;

	अगर (octeon_map_pci_barx(oct, 0, 0))
		वापस 1;

	/* INPUT_CONTROL[RPVF] gives the VF IOq count */
	reg_val = octeon_पढ़ो_csr64(oct, CN23XX_VF_SLI_IQ_PKT_CONTROL64(0));

	oct->pf_num = (reg_val >> CN23XX_PKT_INPUT_CTL_PF_NUM_POS) &
		      CN23XX_PKT_INPUT_CTL_PF_NUM_MASK;
	oct->vf_num = (reg_val >> CN23XX_PKT_INPUT_CTL_VF_NUM_POS) &
		      CN23XX_PKT_INPUT_CTL_VF_NUM_MASK;

	reg_val = reg_val >> CN23XX_PKT_INPUT_CTL_RPVF_POS;

	rings_per_vf = reg_val & CN23XX_PKT_INPUT_CTL_RPVF_MASK;

	cn23xx->conf  = oct_get_config_info(oct, LIO_23XX);
	अगर (!cn23xx->conf) अणु
		dev_err(&oct->pci_dev->dev, "%s No Config found for CN23XX\n",
			__func__);
		octeon_unmap_pci_barx(oct, 0);
		वापस 1;
	पूर्ण

	अगर (oct->sriov_info.rings_per_vf > rings_per_vf) अणु
		dev_warn(&oct->pci_dev->dev,
			 "num_queues:%d greater than PF configured rings_per_vf:%d. Reducing to %d.\n",
			 oct->sriov_info.rings_per_vf, rings_per_vf,
			 rings_per_vf);
		oct->sriov_info.rings_per_vf = rings_per_vf;
	पूर्ण अन्यथा अणु
		अगर (rings_per_vf > num_present_cpus()) अणु
			dev_warn(&oct->pci_dev->dev,
				 "PF configured rings_per_vf:%d greater than num_cpu:%d. Using rings_per_vf:%d equal to num cpus\n",
				 rings_per_vf,
				 num_present_cpus(),
				 num_present_cpus());
			oct->sriov_info.rings_per_vf =
				num_present_cpus();
		पूर्ण अन्यथा अणु
			oct->sriov_info.rings_per_vf = rings_per_vf;
		पूर्ण
	पूर्ण

	oct->fn_list.setup_iq_regs = cn23xx_setup_vf_iq_regs;
	oct->fn_list.setup_oq_regs = cn23xx_setup_vf_oq_regs;
	oct->fn_list.setup_mbox = cn23xx_setup_vf_mbox;
	oct->fn_list.मुक्त_mbox = cn23xx_मुक्त_vf_mbox;

	oct->fn_list.msix_पूर्णांकerrupt_handler = cn23xx_vf_msix_पूर्णांकerrupt_handler;

	oct->fn_list.setup_device_regs = cn23xx_setup_vf_device_regs;
	oct->fn_list.update_iq_पढ़ो_idx = cn23xx_update_पढ़ो_index;

	oct->fn_list.enable_पूर्णांकerrupt = cn23xx_enable_vf_पूर्णांकerrupt;
	oct->fn_list.disable_पूर्णांकerrupt = cn23xx_disable_vf_पूर्णांकerrupt;

	oct->fn_list.enable_io_queues = cn23xx_enable_vf_io_queues;
	oct->fn_list.disable_io_queues = cn23xx_disable_vf_io_queues;

	वापस 0;
पूर्ण
