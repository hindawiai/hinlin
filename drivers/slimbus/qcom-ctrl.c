<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2011-2017, The Linux Foundation
 */

#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/pm_runसमय.स>
#समावेश "slimbus.h"

/* Manager रेजिस्टरs */
#घोषणा	MGR_CFG		0x200
#घोषणा	MGR_STATUS	0x204
#घोषणा	MGR_INT_EN	0x210
#घोषणा	MGR_INT_STAT	0x214
#घोषणा	MGR_INT_CLR	0x218
#घोषणा	MGR_TX_MSG	0x230
#घोषणा	MGR_RX_MSG	0x270
#घोषणा	MGR_IE_STAT	0x2F0
#घोषणा	MGR_VE_STAT	0x300
#घोषणा	MGR_CFG_ENABLE	1

/* Framer रेजिस्टरs */
#घोषणा	FRM_CFG		0x400
#घोषणा	FRM_STAT	0x404
#घोषणा	FRM_INT_EN	0x410
#घोषणा	FRM_INT_STAT	0x414
#घोषणा	FRM_INT_CLR	0x418
#घोषणा	FRM_WAKEUP	0x41C
#घोषणा	FRM_CLKCTL_DONE	0x420
#घोषणा	FRM_IE_STAT	0x430
#घोषणा	FRM_VE_STAT	0x440

/* Interface रेजिस्टरs */
#घोषणा	INTF_CFG	0x600
#घोषणा	INTF_STAT	0x604
#घोषणा	INTF_INT_EN	0x610
#घोषणा	INTF_INT_STAT	0x614
#घोषणा	INTF_INT_CLR	0x618
#घोषणा	INTF_IE_STAT	0x630
#घोषणा	INTF_VE_STAT	0x640

/* Interrupt status bits */
#घोषणा	MGR_INT_TX_NACKED_2	BIT(25)
#घोषणा	MGR_INT_MSG_BUF_CONTE	BIT(26)
#घोषणा	MGR_INT_RX_MSG_RCVD	BIT(30)
#घोषणा	MGR_INT_TX_MSG_SENT	BIT(31)

/* Framer config रेजिस्टर settings */
#घोषणा	FRM_ACTIVE	1
#घोषणा	CLK_GEAR	7
#घोषणा	ROOT_FREQ	11
#घोषणा	REF_CLK_GEAR	15
#घोषणा	INTR_WAKE	19

#घोषणा SLIM_MSG_ASM_FIRST_WORD(l, mt, mc, dt, ad) \
		((l) | ((mt) << 5) | ((mc) << 8) | ((dt) << 15) | ((ad) << 16))

#घोषणा SLIM_ROOT_FREQ 24576000
#घोषणा QCOM_SLIM_AUTOSUSPEND 1000

/* MAX message size over control channel */
#घोषणा SLIM_MSGQ_BUF_LEN	40
#घोषणा QCOM_TX_MSGS 2
#घोषणा QCOM_RX_MSGS	8
#घोषणा QCOM_BUF_ALLOC_RETRIES	10

#घोषणा CFG_PORT(r, v) ((v) ? CFG_PORT_V2(r) : CFG_PORT_V1(r))

/* V2 Component रेजिस्टरs */
#घोषणा CFG_PORT_V2(r) ((r ## _V2))
#घोषणा	COMP_CFG_V2		4
#घोषणा	COMP_TRUST_CFG_V2	0x3000

/* V1 Component रेजिस्टरs */
#घोषणा CFG_PORT_V1(r) ((r ## _V1))
#घोषणा	COMP_CFG_V1		0
#घोषणा	COMP_TRUST_CFG_V1	0x14

/* Resource group info क्रम manager, and non-ported generic device-components */
#घोषणा EE_MGR_RSC_GRP	(1 << 10)
#घोषणा EE_NGD_2	(2 << 6)
#घोषणा EE_NGD_1	0

काष्ठा slim_ctrl_buf अणु
	व्योम		*base;
	spinlock_t	lock;
	पूर्णांक		head;
	पूर्णांक		tail;
	पूर्णांक		sl_sz;
	पूर्णांक		n;
पूर्ण;

काष्ठा qcom_slim_ctrl अणु
	काष्ठा slim_controller  ctrl;
	काष्ठा slim_framer	framer;
	काष्ठा device		*dev;
	व्योम __iomem		*base;
	व्योम __iomem		*slew_reg;

	काष्ठा slim_ctrl_buf	rx;
	काष्ठा slim_ctrl_buf	tx;

	काष्ठा completion	**wr_comp;
	पूर्णांक			irq;
	काष्ठा workqueue_काष्ठा *rxwq;
	काष्ठा work_काष्ठा	wd;
	काष्ठा clk		*rclk;
	काष्ठा clk		*hclk;
पूर्ण;

अटल व्योम qcom_slim_queue_tx(काष्ठा qcom_slim_ctrl *ctrl, व्योम *buf,
			       u8 len, u32 tx_reg)
अणु
	पूर्णांक count = (len + 3) >> 2;

	__ioग_लिखो32_copy(ctrl->base + tx_reg, buf, count);

	/* Ensure Oder of subsequent ग_लिखोs */
	mb();
पूर्ण

अटल व्योम *slim_alloc_rxbuf(काष्ठा qcom_slim_ctrl *ctrl)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक idx;

	spin_lock_irqsave(&ctrl->rx.lock, flags);
	अगर ((ctrl->rx.tail + 1) % ctrl->rx.n == ctrl->rx.head) अणु
		spin_unlock_irqrestore(&ctrl->rx.lock, flags);
		dev_err(ctrl->dev, "RX QUEUE full!");
		वापस शून्य;
	पूर्ण
	idx = ctrl->rx.tail;
	ctrl->rx.tail = (ctrl->rx.tail + 1) % ctrl->rx.n;
	spin_unlock_irqrestore(&ctrl->rx.lock, flags);

	वापस ctrl->rx.base + (idx * ctrl->rx.sl_sz);
पूर्ण

अटल व्योम slim_ack_txn(काष्ठा qcom_slim_ctrl *ctrl, पूर्णांक err)
अणु
	काष्ठा completion *comp;
	अचिन्हित दीर्घ flags;
	पूर्णांक idx;

	spin_lock_irqsave(&ctrl->tx.lock, flags);
	idx = ctrl->tx.head;
	ctrl->tx.head = (ctrl->tx.head + 1) % ctrl->tx.n;
	spin_unlock_irqrestore(&ctrl->tx.lock, flags);

	comp = ctrl->wr_comp[idx];
	ctrl->wr_comp[idx] = शून्य;

	complete(comp);
पूर्ण

अटल irqवापस_t qcom_slim_handle_tx_irq(काष्ठा qcom_slim_ctrl *ctrl,
					   u32 stat)
अणु
	पूर्णांक err = 0;

	अगर (stat & MGR_INT_TX_MSG_SENT)
		ग_लिखोl_relaxed(MGR_INT_TX_MSG_SENT,
			       ctrl->base + MGR_INT_CLR);

	अगर (stat & MGR_INT_TX_NACKED_2) अणु
		u32 mgr_stat = पढ़ोl_relaxed(ctrl->base + MGR_STATUS);
		u32 mgr_ie_stat = पढ़ोl_relaxed(ctrl->base + MGR_IE_STAT);
		u32 frm_stat = पढ़ोl_relaxed(ctrl->base + FRM_STAT);
		u32 frm_cfg = पढ़ोl_relaxed(ctrl->base + FRM_CFG);
		u32 frm_पूर्णांकr_stat = पढ़ोl_relaxed(ctrl->base + FRM_INT_STAT);
		u32 frm_ie_stat = पढ़ोl_relaxed(ctrl->base + FRM_IE_STAT);
		u32 पूर्णांकf_stat = पढ़ोl_relaxed(ctrl->base + INTF_STAT);
		u32 पूर्णांकf_पूर्णांकr_stat = पढ़ोl_relaxed(ctrl->base + INTF_INT_STAT);
		u32 पूर्णांकf_ie_stat = पढ़ोl_relaxed(ctrl->base + INTF_IE_STAT);

		ग_लिखोl_relaxed(MGR_INT_TX_NACKED_2, ctrl->base + MGR_INT_CLR);

		dev_err(ctrl->dev, "TX Nack MGR:int:0x%x, stat:0x%x\n",
			stat, mgr_stat);
		dev_err(ctrl->dev, "TX Nack MGR:ie:0x%x\n", mgr_ie_stat);
		dev_err(ctrl->dev, "TX Nack FRM:int:0x%x, stat:0x%x\n",
			frm_पूर्णांकr_stat, frm_stat);
		dev_err(ctrl->dev, "TX Nack FRM:cfg:0x%x, ie:0x%x\n",
			frm_cfg, frm_ie_stat);
		dev_err(ctrl->dev, "TX Nack INTF:intr:0x%x, stat:0x%x\n",
			पूर्णांकf_पूर्णांकr_stat, पूर्णांकf_stat);
		dev_err(ctrl->dev, "TX Nack INTF:ie:0x%x\n",
			पूर्णांकf_ie_stat);
		err = -ENOTCONN;
	पूर्ण

	slim_ack_txn(ctrl, err);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t qcom_slim_handle_rx_irq(काष्ठा qcom_slim_ctrl *ctrl,
					   u32 stat)
अणु
	u32 *rx_buf, pkt[10];
	bool q_rx = false;
	u8 mc, mt, len;

	pkt[0] = पढ़ोl_relaxed(ctrl->base + MGR_RX_MSG);
	mt = SLIM_HEADER_GET_MT(pkt[0]);
	len = SLIM_HEADER_GET_RL(pkt[0]);
	mc = SLIM_HEADER_GET_MC(pkt[0]>>8);

	/*
	 * this message cannot be handled by ISR, so
	 * let work-queue handle it
	 */
	अगर (mt == SLIM_MSG_MT_CORE && mc == SLIM_MSG_MC_REPORT_PRESENT) अणु
		rx_buf = (u32 *)slim_alloc_rxbuf(ctrl);
		अगर (!rx_buf) अणु
			dev_err(ctrl->dev, "dropping RX:0x%x due to RX full\n",
					pkt[0]);
			जाओ rx_ret_irq;
		पूर्ण
		rx_buf[0] = pkt[0];

	पूर्ण अन्यथा अणु
		rx_buf = pkt;
	पूर्ण

	__ioपढ़ो32_copy(rx_buf + 1, ctrl->base + MGR_RX_MSG + 4,
			DIV_ROUND_UP(len, 4));

	चयन (mc) अणु

	हाल SLIM_MSG_MC_REPORT_PRESENT:
		q_rx = true;
		अवरोध;
	हाल SLIM_MSG_MC_REPLY_INFORMATION:
	हाल SLIM_MSG_MC_REPLY_VALUE:
		slim_msg_response(&ctrl->ctrl, (u8 *)(rx_buf + 1),
				  (u8)(*rx_buf >> 24), (len - 4));
		अवरोध;
	शेष:
		dev_err(ctrl->dev, "unsupported MC,%x MT:%x\n",
			mc, mt);
		अवरोध;
	पूर्ण
rx_ret_irq:
	ग_लिखोl(MGR_INT_RX_MSG_RCVD, ctrl->base +
		       MGR_INT_CLR);
	अगर (q_rx)
		queue_work(ctrl->rxwq, &ctrl->wd);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t qcom_slim_पूर्णांकerrupt(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा qcom_slim_ctrl *ctrl = d;
	u32 stat = पढ़ोl_relaxed(ctrl->base + MGR_INT_STAT);
	पूर्णांक ret = IRQ_NONE;

	अगर (stat & MGR_INT_TX_MSG_SENT || stat & MGR_INT_TX_NACKED_2)
		ret = qcom_slim_handle_tx_irq(ctrl, stat);

	अगर (stat & MGR_INT_RX_MSG_RCVD)
		ret = qcom_slim_handle_rx_irq(ctrl, stat);

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_clk_छोड़ो_wakeup(काष्ठा slim_controller *sctrl)
अणु
	काष्ठा qcom_slim_ctrl *ctrl = dev_get_drvdata(sctrl->dev);

	clk_prepare_enable(ctrl->hclk);
	clk_prepare_enable(ctrl->rclk);
	enable_irq(ctrl->irq);

	ग_लिखोl_relaxed(1, ctrl->base + FRM_WAKEUP);
	/* Make sure framer wakeup ग_लिखो goes through beक्रमe ISR fires */
	mb();
	/*
	 * HW Workaround: Currently, slave is reporting lost-sync messages
	 * after SLIMbus comes out of घड़ी छोड़ो.
	 * Transaction with slave fail beक्रमe slave reports that message
	 * Give some समय क्रम that report to come
	 * SLIMbus wakes up in घड़ी gear 10 at 24.576MHz. With each superframe
	 * being 250 usecs, we रुको क्रम 5-10 superframes here to ensure
	 * we get the message
	 */
	usleep_range(1250, 2500);
	वापस 0;
पूर्ण

अटल व्योम *slim_alloc_txbuf(काष्ठा qcom_slim_ctrl *ctrl,
			      काष्ठा slim_msg_txn *txn,
			      काष्ठा completion *करोne)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक idx;

	spin_lock_irqsave(&ctrl->tx.lock, flags);
	अगर (((ctrl->tx.head + 1) % ctrl->tx.n) == ctrl->tx.tail) अणु
		spin_unlock_irqrestore(&ctrl->tx.lock, flags);
		dev_err(ctrl->dev, "controller TX buf unavailable");
		वापस शून्य;
	पूर्ण
	idx = ctrl->tx.tail;
	ctrl->wr_comp[idx] = करोne;
	ctrl->tx.tail = (ctrl->tx.tail + 1) % ctrl->tx.n;

	spin_unlock_irqrestore(&ctrl->tx.lock, flags);

	वापस ctrl->tx.base + (idx * ctrl->tx.sl_sz);
पूर्ण


अटल पूर्णांक qcom_xfer_msg(काष्ठा slim_controller *sctrl,
			 काष्ठा slim_msg_txn *txn)
अणु
	काष्ठा qcom_slim_ctrl *ctrl = dev_get_drvdata(sctrl->dev);
	DECLARE_COMPLETION_ONSTACK(करोne);
	व्योम *pbuf = slim_alloc_txbuf(ctrl, txn, &करोne);
	अचिन्हित दीर्घ ms = txn->rl + HZ;
	u8 *puc;
	पूर्णांक ret = 0, समयout, retries = QCOM_BUF_ALLOC_RETRIES;
	u8 la = txn->la;
	u32 *head;
	/* HW expects length field to be excluded */
	txn->rl--;

	/* spin till buffer is made available */
	अगर (!pbuf) अणु
		जबतक (retries--) अणु
			usleep_range(10000, 15000);
			pbuf = slim_alloc_txbuf(ctrl, txn, &करोne);
			अगर (pbuf)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (retries < 0 && !pbuf)
		वापस -ENOMEM;

	puc = (u8 *)pbuf;
	head = (u32 *)pbuf;

	अगर (txn->dt == SLIM_MSG_DEST_LOGICALADDR) अणु
		*head = SLIM_MSG_ASM_FIRST_WORD(txn->rl, txn->mt,
						txn->mc, 0, la);
		puc += 3;
	पूर्ण अन्यथा अणु
		*head = SLIM_MSG_ASM_FIRST_WORD(txn->rl, txn->mt,
						txn->mc, 1, la);
		puc += 2;
	पूर्ण

	अगर (slim_tid_txn(txn->mt, txn->mc))
		*(puc++) = txn->tid;

	अगर (slim_ec_txn(txn->mt, txn->mc)) अणु
		*(puc++) = (txn->ec & 0xFF);
		*(puc++) = (txn->ec >> 8) & 0xFF;
	पूर्ण

	अगर (txn->msg && txn->msg->wbuf)
		स_नकल(puc, txn->msg->wbuf, txn->msg->num_bytes);

	qcom_slim_queue_tx(ctrl, head, txn->rl, MGR_TX_MSG);
	समयout = रुको_क्रम_completion_समयout(&करोne, msecs_to_jअगरfies(ms));

	अगर (!समयout) अणु
		dev_err(ctrl->dev, "TX timed out:MC:0x%x,mt:0x%x", txn->mc,
					txn->mt);
		ret = -ETIMEDOUT;
	पूर्ण

	वापस ret;

पूर्ण

अटल पूर्णांक qcom_set_laddr(काष्ठा slim_controller *sctrl,
				काष्ठा slim_eaddr *ead, u8 laddr)
अणु
	काष्ठा qcom_slim_ctrl *ctrl = dev_get_drvdata(sctrl->dev);
	काष्ठा अणु
		__be16 manf_id;
		__be16 prod_code;
		u8 dev_index;
		u8 instance;
		u8 laddr;
	पूर्ण __packed p;
	काष्ठा slim_val_inf msg = अणु0पूर्ण;
	DEFINE_SLIM_EDEST_TXN(txn, SLIM_MSG_MC_ASSIGN_LOGICAL_ADDRESS,
			      10, laddr, &msg);
	पूर्णांक ret;

	p.manf_id = cpu_to_be16(ead->manf_id);
	p.prod_code = cpu_to_be16(ead->prod_code);
	p.dev_index = ead->dev_index;
	p.instance = ead->instance;
	p.laddr = laddr;

	msg.wbuf = (व्योम *)&p;
	msg.num_bytes = 7;
	ret = slim_करो_transfer(&ctrl->ctrl, &txn);

	अगर (ret)
		dev_err(ctrl->dev, "set LA:0x%x failed:ret:%d\n",
				  laddr, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक slim_get_current_rxbuf(काष्ठा qcom_slim_ctrl *ctrl, व्योम *buf)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctrl->rx.lock, flags);
	अगर (ctrl->rx.tail == ctrl->rx.head) अणु
		spin_unlock_irqrestore(&ctrl->rx.lock, flags);
		वापस -ENODATA;
	पूर्ण
	स_नकल(buf, ctrl->rx.base + (ctrl->rx.head * ctrl->rx.sl_sz),
				ctrl->rx.sl_sz);

	ctrl->rx.head = (ctrl->rx.head + 1) % ctrl->rx.n;
	spin_unlock_irqrestore(&ctrl->rx.lock, flags);

	वापस 0;
पूर्ण

अटल व्योम qcom_slim_rxwq(काष्ठा work_काष्ठा *work)
अणु
	u8 buf[SLIM_MSGQ_BUF_LEN];
	u8 mc, mt;
	पूर्णांक ret;
	काष्ठा qcom_slim_ctrl *ctrl = container_of(work, काष्ठा qcom_slim_ctrl,
						 wd);

	जबतक ((slim_get_current_rxbuf(ctrl, buf)) != -ENODATA) अणु
		mt = SLIM_HEADER_GET_MT(buf[0]);
		mc = SLIM_HEADER_GET_MC(buf[1]);
		अगर (mt == SLIM_MSG_MT_CORE &&
			mc == SLIM_MSG_MC_REPORT_PRESENT) अणु
			काष्ठा slim_eaddr ea;
			u8 laddr;

			ea.manf_id = be16_to_cpup((__be16 *)&buf[2]);
			ea.prod_code = be16_to_cpup((__be16 *)&buf[4]);
			ea.dev_index = buf[6];
			ea.instance = buf[7];

			ret = slim_device_report_present(&ctrl->ctrl, &ea,
							 &laddr);
			अगर (ret < 0)
				dev_err(ctrl->dev, "assign laddr failed:%d\n",
					ret);
		पूर्ण अन्यथा अणु
			dev_err(ctrl->dev, "unexpected message:mc:%x, mt:%x\n",
				mc, mt);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qcom_slim_prg_slew(काष्ठा platक्रमm_device *pdev,
				काष्ठा qcom_slim_ctrl *ctrl)
अणु
	अगर (!ctrl->slew_reg) अणु
		/* SLEW RATE रेजिस्टर क्रम this SLIMbus */
		ctrl->slew_reg = devm_platक्रमm_ioremap_resource_byname(pdev, "slew");
		अगर (IS_ERR(ctrl->slew_reg))
			वापस;
	पूर्ण

	ग_लिखोl_relaxed(1, ctrl->slew_reg);
	/* Make sure SLIMbus-slew rate enabling goes through */
	wmb();
पूर्ण

अटल पूर्णांक qcom_slim_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_slim_ctrl *ctrl;
	काष्ठा slim_controller *sctrl;
	काष्ठा resource *slim_mem;
	पूर्णांक ret, ver;

	ctrl = devm_kzalloc(&pdev->dev, माप(*ctrl), GFP_KERNEL);
	अगर (!ctrl)
		वापस -ENOMEM;

	ctrl->hclk = devm_clk_get(&pdev->dev, "iface");
	अगर (IS_ERR(ctrl->hclk))
		वापस PTR_ERR(ctrl->hclk);

	ctrl->rclk = devm_clk_get(&pdev->dev, "core");
	अगर (IS_ERR(ctrl->rclk))
		वापस PTR_ERR(ctrl->rclk);

	ret = clk_set_rate(ctrl->rclk, SLIM_ROOT_FREQ);
	अगर (ret) अणु
		dev_err(&pdev->dev, "ref-clock set-rate failed:%d\n", ret);
		वापस ret;
	पूर्ण

	ctrl->irq = platक्रमm_get_irq(pdev, 0);
	अगर (!ctrl->irq) अणु
		dev_err(&pdev->dev, "no slimbus IRQ\n");
		वापस -ENODEV;
	पूर्ण

	sctrl = &ctrl->ctrl;
	sctrl->dev = &pdev->dev;
	ctrl->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, ctrl);
	dev_set_drvdata(ctrl->dev, ctrl);

	slim_mem = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "ctrl");
	ctrl->base = devm_ioremap_resource(ctrl->dev, slim_mem);
	अगर (IS_ERR(ctrl->base))
		वापस PTR_ERR(ctrl->base);

	sctrl->set_laddr = qcom_set_laddr;
	sctrl->xfer_msg = qcom_xfer_msg;
	sctrl->wakeup =  qcom_clk_छोड़ो_wakeup;
	ctrl->tx.n = QCOM_TX_MSGS;
	ctrl->tx.sl_sz = SLIM_MSGQ_BUF_LEN;
	ctrl->rx.n = QCOM_RX_MSGS;
	ctrl->rx.sl_sz = SLIM_MSGQ_BUF_LEN;
	ctrl->wr_comp = kसुस्मृति(QCOM_TX_MSGS, माप(काष्ठा completion *),
				GFP_KERNEL);
	अगर (!ctrl->wr_comp)
		वापस -ENOMEM;

	spin_lock_init(&ctrl->rx.lock);
	spin_lock_init(&ctrl->tx.lock);
	INIT_WORK(&ctrl->wd, qcom_slim_rxwq);
	ctrl->rxwq = create_singlethपढ़ो_workqueue("qcom_slim_rx");
	अगर (!ctrl->rxwq) अणु
		dev_err(ctrl->dev, "Failed to start Rx WQ\n");
		वापस -ENOMEM;
	पूर्ण

	ctrl->framer.rootfreq = SLIM_ROOT_FREQ / 8;
	ctrl->framer.superfreq =
		ctrl->framer.rootfreq / SLIM_CL_PER_SUPERFRAME_DIV8;
	sctrl->a_framer = &ctrl->framer;
	sctrl->clkgear = SLIM_MAX_CLK_GEAR;

	qcom_slim_prg_slew(pdev, ctrl);

	ret = devm_request_irq(&pdev->dev, ctrl->irq, qcom_slim_पूर्णांकerrupt,
				IRQF_TRIGGER_HIGH, "qcom_slim_irq", ctrl);
	अगर (ret) अणु
		dev_err(&pdev->dev, "request IRQ failed\n");
		जाओ err_request_irq_failed;
	पूर्ण

	ret = clk_prepare_enable(ctrl->hclk);
	अगर (ret)
		जाओ err_hclk_enable_failed;

	ret = clk_prepare_enable(ctrl->rclk);
	अगर (ret)
		जाओ err_rclk_enable_failed;

	ctrl->tx.base = devm_kसुस्मृति(&pdev->dev, ctrl->tx.n, ctrl->tx.sl_sz,
				     GFP_KERNEL);
	अगर (!ctrl->tx.base) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ctrl->rx.base = devm_kसुस्मृति(&pdev->dev,ctrl->rx.n, ctrl->rx.sl_sz,
				     GFP_KERNEL);
	अगर (!ctrl->rx.base) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	/* Register with framework beक्रमe enabling frame, घड़ी */
	ret = slim_रेजिस्टर_controller(&ctrl->ctrl);
	अगर (ret) अणु
		dev_err(ctrl->dev, "error adding controller\n");
		जाओ err;
	पूर्ण

	ver = पढ़ोl_relaxed(ctrl->base);
	/* Version info in 16 MSbits */
	ver >>= 16;
	/* Component रेजिस्टर initialization */
	ग_लिखोl(1, ctrl->base + CFG_PORT(COMP_CFG, ver));
	ग_लिखोl((EE_MGR_RSC_GRP | EE_NGD_2 | EE_NGD_1),
				ctrl->base + CFG_PORT(COMP_TRUST_CFG, ver));

	ग_लिखोl((MGR_INT_TX_NACKED_2 |
			MGR_INT_MSG_BUF_CONTE | MGR_INT_RX_MSG_RCVD |
			MGR_INT_TX_MSG_SENT), ctrl->base + MGR_INT_EN);
	ग_लिखोl(1, ctrl->base + MGR_CFG);
	/* Framer रेजिस्टर initialization */
	ग_लिखोl((1 << INTR_WAKE) | (0xA << REF_CLK_GEAR) |
		(0xA << CLK_GEAR) | (1 << ROOT_FREQ) | (1 << FRM_ACTIVE) | 1,
		ctrl->base + FRM_CFG);
	ग_लिखोl(MGR_CFG_ENABLE, ctrl->base + MGR_CFG);
	ग_लिखोl(1, ctrl->base + INTF_CFG);
	ग_लिखोl(1, ctrl->base + CFG_PORT(COMP_CFG, ver));

	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, QCOM_SLIM_AUTOSUSPEND);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_mark_last_busy(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	dev_dbg(ctrl->dev, "QCOM SB controller is up:ver:0x%x!\n", ver);
	वापस 0;

err:
	clk_disable_unprepare(ctrl->rclk);
err_rclk_enable_failed:
	clk_disable_unprepare(ctrl->hclk);
err_hclk_enable_failed:
err_request_irq_failed:
	destroy_workqueue(ctrl->rxwq);
	वापस ret;
पूर्ण

अटल पूर्णांक qcom_slim_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_slim_ctrl *ctrl = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(&pdev->dev);
	slim_unरेजिस्टर_controller(&ctrl->ctrl);
	clk_disable_unprepare(ctrl->rclk);
	clk_disable_unprepare(ctrl->hclk);
	destroy_workqueue(ctrl->rxwq);
	वापस 0;
पूर्ण

/*
 * If PM_RUNTIME is not defined, these 2 functions become helper
 * functions to be called from प्रणाली suspend/resume.
 */
#अगर_घोषित CONFIG_PM
अटल पूर्णांक qcom_slim_runसमय_suspend(काष्ठा device *device)
अणु
	काष्ठा qcom_slim_ctrl *ctrl = dev_get_drvdata(device);
	पूर्णांक ret;

	dev_dbg(device, "pm_runtime: suspending...\n");
	ret = slim_ctrl_clk_छोड़ो(&ctrl->ctrl, false, SLIM_CLK_UNSPECIFIED);
	अगर (ret) अणु
		dev_err(device, "clk pause not entered:%d", ret);
	पूर्ण अन्यथा अणु
		disable_irq(ctrl->irq);
		clk_disable_unprepare(ctrl->hclk);
		clk_disable_unprepare(ctrl->rclk);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक qcom_slim_runसमय_resume(काष्ठा device *device)
अणु
	काष्ठा qcom_slim_ctrl *ctrl = dev_get_drvdata(device);
	पूर्णांक ret = 0;

	dev_dbg(device, "pm_runtime: resuming...\n");
	ret = slim_ctrl_clk_छोड़ो(&ctrl->ctrl, true, 0);
	अगर (ret)
		dev_err(device, "clk pause not exited:%d", ret);
	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक qcom_slim_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret = 0;

	अगर (!pm_runसमय_enabled(dev) ||
		(!pm_runसमय_suspended(dev))) अणु
		dev_dbg(dev, "system suspend");
		ret = qcom_slim_runसमय_suspend(dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_slim_resume(काष्ठा device *dev)
अणु
	अगर (!pm_runसमय_enabled(dev) || !pm_runसमय_suspended(dev)) अणु
		पूर्णांक ret;

		dev_dbg(dev, "system resume");
		ret = qcom_slim_runसमय_resume(dev);
		अगर (!ret) अणु
			pm_runसमय_mark_last_busy(dev);
			pm_request_स्वतःsuspend(dev);
		पूर्ण
		वापस ret;

	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा dev_pm_ops qcom_slim_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(qcom_slim_suspend, qcom_slim_resume)
	SET_RUNTIME_PM_OPS(
			   qcom_slim_runसमय_suspend,
			   qcom_slim_runसमय_resume,
			   शून्य
	)
पूर्ण;

अटल स्थिर काष्ठा of_device_id qcom_slim_dt_match[] = अणु
	अणु .compatible = "qcom,slim", पूर्ण,
	अणु .compatible = "qcom,apq8064-slim", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver qcom_slim_driver = अणु
	.probe = qcom_slim_probe,
	.हटाओ = qcom_slim_हटाओ,
	.driver	= अणु
		.name = "qcom_slim_ctrl",
		.of_match_table = qcom_slim_dt_match,
		.pm = &qcom_slim_dev_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(qcom_slim_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Qualcomm SLIMbus Controller");
