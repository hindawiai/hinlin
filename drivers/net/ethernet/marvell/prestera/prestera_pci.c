<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2019-2020 Marvell International Ltd. All rights reserved */

#समावेश <linux/circ_buf.h>
#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "prestera.h"

#घोषणा PRESTERA_MSG_MAX_SIZE 1500

#घोषणा PRESTERA_SUPP_FW_MAJ_VER	2
#घोषणा PRESTERA_SUPP_FW_MIN_VER	0

#घोषणा PRESTERA_FW_PATH_FMT	"mrvl/prestera/mvsw_prestera_fw-v%u.%u.img"

#घोषणा PRESTERA_FW_HDR_MAGIC		0x351D9D06
#घोषणा PRESTERA_FW_DL_TIMEOUT_MS	50000
#घोषणा PRESTERA_FW_BLK_SZ		1024

#घोषणा PRESTERA_FW_VER_MAJ_MUL 1000000
#घोषणा PRESTERA_FW_VER_MIN_MUL 1000

#घोषणा PRESTERA_FW_VER_MAJ(v)	((v) / PRESTERA_FW_VER_MAJ_MUL)

#घोषणा PRESTERA_FW_VER_MIN(v) \
	(((v) - (PRESTERA_FW_VER_MAJ(v) * PRESTERA_FW_VER_MAJ_MUL)) / \
			PRESTERA_FW_VER_MIN_MUL)

#घोषणा PRESTERA_FW_VER_PATCH(v) \
	((v) - (PRESTERA_FW_VER_MAJ(v) * PRESTERA_FW_VER_MAJ_MUL) - \
			(PRESTERA_FW_VER_MIN(v) * PRESTERA_FW_VER_MIN_MUL))

क्रमागत prestera_pci_bar_t अणु
	PRESTERA_PCI_BAR_FW = 2,
	PRESTERA_PCI_BAR_PP = 4,
पूर्ण;

काष्ठा prestera_fw_header अणु
	__be32 magic_number;
	__be32 version_value;
	u8 reserved[8];
पूर्ण;

काष्ठा prestera_ldr_regs अणु
	u32 ldr_पढ़ोy;
	u32 pad1;

	u32 ldr_img_size;
	u32 ldr_ctl_flags;

	u32 ldr_buf_offs;
	u32 ldr_buf_size;

	u32 ldr_buf_rd;
	u32 pad2;
	u32 ldr_buf_wr;

	u32 ldr_status;
पूर्ण;

#घोषणा PRESTERA_LDR_REG_OFFSET(f)	दुरत्व(काष्ठा prestera_ldr_regs, f)

#घोषणा PRESTERA_LDR_READY_MAGIC	0xf00dfeed

#घोषणा PRESTERA_LDR_STATUS_IMG_DL	BIT(0)
#घोषणा PRESTERA_LDR_STATUS_START_FW	BIT(1)
#घोषणा PRESTERA_LDR_STATUS_INVALID_IMG	BIT(2)
#घोषणा PRESTERA_LDR_STATUS_NOMEM	BIT(3)

#घोषणा PRESTERA_LDR_REG_BASE(fw)	((fw)->ldr_regs)
#घोषणा PRESTERA_LDR_REG_ADDR(fw, reg)	(PRESTERA_LDR_REG_BASE(fw) + (reg))

/* fw loader रेजिस्टरs */
#घोषणा PRESTERA_LDR_READY_REG		PRESTERA_LDR_REG_OFFSET(ldr_पढ़ोy)
#घोषणा PRESTERA_LDR_IMG_SIZE_REG	PRESTERA_LDR_REG_OFFSET(ldr_img_size)
#घोषणा PRESTERA_LDR_CTL_REG		PRESTERA_LDR_REG_OFFSET(ldr_ctl_flags)
#घोषणा PRESTERA_LDR_BUF_SIZE_REG	PRESTERA_LDR_REG_OFFSET(ldr_buf_size)
#घोषणा PRESTERA_LDR_BUF_OFFS_REG	PRESTERA_LDR_REG_OFFSET(ldr_buf_offs)
#घोषणा PRESTERA_LDR_BUF_RD_REG		PRESTERA_LDR_REG_OFFSET(ldr_buf_rd)
#घोषणा PRESTERA_LDR_BUF_WR_REG		PRESTERA_LDR_REG_OFFSET(ldr_buf_wr)
#घोषणा PRESTERA_LDR_STATUS_REG		PRESTERA_LDR_REG_OFFSET(ldr_status)

#घोषणा PRESTERA_LDR_CTL_DL_START	BIT(0)

#घोषणा PRESTERA_EVT_QNUM_MAX	4

काष्ठा prestera_fw_evtq_regs अणु
	u32 rd_idx;
	u32 pad1;
	u32 wr_idx;
	u32 pad2;
	u32 offs;
	u32 len;
पूर्ण;

काष्ठा prestera_fw_regs अणु
	u32 fw_पढ़ोy;
	u32 pad;
	u32 cmd_offs;
	u32 cmd_len;
	u32 evt_offs;
	u32 evt_qnum;

	u32 cmd_req_ctl;
	u32 cmd_req_len;
	u32 cmd_rcv_ctl;
	u32 cmd_rcv_len;

	u32 fw_status;
	u32 rx_status;

	काष्ठा prestera_fw_evtq_regs evtq_list[PRESTERA_EVT_QNUM_MAX];
पूर्ण;

#घोषणा PRESTERA_FW_REG_OFFSET(f)	दुरत्व(काष्ठा prestera_fw_regs, f)

#घोषणा PRESTERA_FW_READY_MAGIC		0xcafebabe

/* fw रेजिस्टरs */
#घोषणा PRESTERA_FW_READY_REG		PRESTERA_FW_REG_OFFSET(fw_पढ़ोy)

#घोषणा PRESTERA_CMD_BUF_OFFS_REG	PRESTERA_FW_REG_OFFSET(cmd_offs)
#घोषणा PRESTERA_CMD_BUF_LEN_REG	PRESTERA_FW_REG_OFFSET(cmd_len)
#घोषणा PRESTERA_EVT_BUF_OFFS_REG	PRESTERA_FW_REG_OFFSET(evt_offs)
#घोषणा PRESTERA_EVT_QNUM_REG		PRESTERA_FW_REG_OFFSET(evt_qnum)

#घोषणा PRESTERA_CMD_REQ_CTL_REG	PRESTERA_FW_REG_OFFSET(cmd_req_ctl)
#घोषणा PRESTERA_CMD_REQ_LEN_REG	PRESTERA_FW_REG_OFFSET(cmd_req_len)

#घोषणा PRESTERA_CMD_RCV_CTL_REG	PRESTERA_FW_REG_OFFSET(cmd_rcv_ctl)
#घोषणा PRESTERA_CMD_RCV_LEN_REG	PRESTERA_FW_REG_OFFSET(cmd_rcv_len)
#घोषणा PRESTERA_FW_STATUS_REG		PRESTERA_FW_REG_OFFSET(fw_status)
#घोषणा PRESTERA_RX_STATUS_REG		PRESTERA_FW_REG_OFFSET(rx_status)

/* PRESTERA_CMD_REQ_CTL_REG flags */
#घोषणा PRESTERA_CMD_F_REQ_SENT		BIT(0)
#घोषणा PRESTERA_CMD_F_REPL_RCVD	BIT(1)

/* PRESTERA_CMD_RCV_CTL_REG flags */
#घोषणा PRESTERA_CMD_F_REPL_SENT	BIT(0)

#घोषणा PRESTERA_EVTQ_REG_OFFSET(q, f)			\
	(PRESTERA_FW_REG_OFFSET(evtq_list) +		\
	 (q) * माप(काष्ठा prestera_fw_evtq_regs) +	\
	 दुरत्व(काष्ठा prestera_fw_evtq_regs, f))

#घोषणा PRESTERA_EVTQ_RD_IDX_REG(q)	PRESTERA_EVTQ_REG_OFFSET(q, rd_idx)
#घोषणा PRESTERA_EVTQ_WR_IDX_REG(q)	PRESTERA_EVTQ_REG_OFFSET(q, wr_idx)
#घोषणा PRESTERA_EVTQ_OFFS_REG(q)	PRESTERA_EVTQ_REG_OFFSET(q, offs)
#घोषणा PRESTERA_EVTQ_LEN_REG(q)	PRESTERA_EVTQ_REG_OFFSET(q, len)

#घोषणा PRESTERA_FW_REG_BASE(fw)	((fw)->dev.ctl_regs)
#घोषणा PRESTERA_FW_REG_ADDR(fw, reg)	PRESTERA_FW_REG_BASE((fw)) + (reg)

#घोषणा PRESTERA_FW_CMD_DEFAULT_WAIT_MS	30000
#घोषणा PRESTERA_FW_READY_WAIT_MS	20000

काष्ठा prestera_fw_evtq अणु
	u8 __iomem *addr;
	माप_प्रकार len;
पूर्ण;

काष्ठा prestera_fw अणु
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा prestera_device dev;
	u8 __iomem *ldr_regs;
	u8 __iomem *ldr_ring_buf;
	u32 ldr_buf_len;
	u32 ldr_wr_idx;
	काष्ठा mutex cmd_mtx; /* serialize access to dev->send_req */
	माप_प्रकार cmd_mbox_len;
	u8 __iomem *cmd_mbox;
	काष्ठा prestera_fw_evtq evt_queue[PRESTERA_EVT_QNUM_MAX];
	u8 evt_qnum;
	काष्ठा work_काष्ठा evt_work;
	u8 __iomem *evt_buf;
	u8 *evt_msg;
पूर्ण;

अटल पूर्णांक prestera_fw_load(काष्ठा prestera_fw *fw);

अटल व्योम prestera_fw_ग_लिखो(काष्ठा prestera_fw *fw, u32 reg, u32 val)
अणु
	ग_लिखोl(val, PRESTERA_FW_REG_ADDR(fw, reg));
पूर्ण

अटल u32 prestera_fw_पढ़ो(काष्ठा prestera_fw *fw, u32 reg)
अणु
	वापस पढ़ोl(PRESTERA_FW_REG_ADDR(fw, reg));
पूर्ण

अटल u32 prestera_fw_evtq_len(काष्ठा prestera_fw *fw, u8 qid)
अणु
	वापस fw->evt_queue[qid].len;
पूर्ण

अटल u32 prestera_fw_evtq_avail(काष्ठा prestera_fw *fw, u8 qid)
अणु
	u32 wr_idx = prestera_fw_पढ़ो(fw, PRESTERA_EVTQ_WR_IDX_REG(qid));
	u32 rd_idx = prestera_fw_पढ़ो(fw, PRESTERA_EVTQ_RD_IDX_REG(qid));

	वापस CIRC_CNT(wr_idx, rd_idx, prestera_fw_evtq_len(fw, qid));
पूर्ण

अटल व्योम prestera_fw_evtq_rd_set(काष्ठा prestera_fw *fw,
				    u8 qid, u32 idx)
अणु
	u32 rd_idx = idx & (prestera_fw_evtq_len(fw, qid) - 1);

	prestera_fw_ग_लिखो(fw, PRESTERA_EVTQ_RD_IDX_REG(qid), rd_idx);
पूर्ण

अटल u8 __iomem *prestera_fw_evtq_buf(काष्ठा prestera_fw *fw, u8 qid)
अणु
	वापस fw->evt_queue[qid].addr;
पूर्ण

अटल u32 prestera_fw_evtq_पढ़ो32(काष्ठा prestera_fw *fw, u8 qid)
अणु
	u32 rd_idx = prestera_fw_पढ़ो(fw, PRESTERA_EVTQ_RD_IDX_REG(qid));
	u32 val;

	val = पढ़ोl(prestera_fw_evtq_buf(fw, qid) + rd_idx);
	prestera_fw_evtq_rd_set(fw, qid, rd_idx + 4);
	वापस val;
पूर्ण

अटल sमाप_प्रकार prestera_fw_evtq_पढ़ो_buf(काष्ठा prestera_fw *fw,
					 u8 qid, व्योम *buf, माप_प्रकार len)
अणु
	u32 idx = prestera_fw_पढ़ो(fw, PRESTERA_EVTQ_RD_IDX_REG(qid));
	u8 __iomem *evtq_addr = prestera_fw_evtq_buf(fw, qid);
	u32 *buf32 = buf;
	पूर्णांक i;

	क्रम (i = 0; i < len / 4; buf32++, i++) अणु
		*buf32 = पढ़ोl_relaxed(evtq_addr + idx);
		idx = (idx + 4) & (prestera_fw_evtq_len(fw, qid) - 1);
	पूर्ण

	prestera_fw_evtq_rd_set(fw, qid, idx);

	वापस i;
पूर्ण

अटल u8 prestera_fw_evtq_pick(काष्ठा prestera_fw *fw)
अणु
	पूर्णांक qid;

	क्रम (qid = 0; qid < fw->evt_qnum; qid++) अणु
		अगर (prestera_fw_evtq_avail(fw, qid) >= 4)
			वापस qid;
	पूर्ण

	वापस PRESTERA_EVT_QNUM_MAX;
पूर्ण

अटल व्योम prestera_fw_evt_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा prestera_fw *fw;
	व्योम *msg;
	u8 qid;

	fw = container_of(work, काष्ठा prestera_fw, evt_work);
	msg = fw->evt_msg;

	जबतक ((qid = prestera_fw_evtq_pick(fw)) < PRESTERA_EVT_QNUM_MAX) अणु
		u32 idx;
		u32 len;

		len = prestera_fw_evtq_पढ़ो32(fw, qid);
		idx = prestera_fw_पढ़ो(fw, PRESTERA_EVTQ_RD_IDX_REG(qid));

		WARN_ON(prestera_fw_evtq_avail(fw, qid) < len);

		अगर (WARN_ON(len > PRESTERA_MSG_MAX_SIZE)) अणु
			prestera_fw_evtq_rd_set(fw, qid, idx + len);
			जारी;
		पूर्ण

		prestera_fw_evtq_पढ़ो_buf(fw, qid, msg, len);

		अगर (fw->dev.recv_msg)
			fw->dev.recv_msg(&fw->dev, msg, len);
	पूर्ण
पूर्ण

अटल पूर्णांक prestera_fw_रुको_reg32(काष्ठा prestera_fw *fw, u32 reg, u32 cmp,
				  अचिन्हित पूर्णांक रुकोms)
अणु
	u8 __iomem *addr = PRESTERA_FW_REG_ADDR(fw, reg);
	u32 val;

	वापस पढ़ोl_poll_समयout(addr, val, cmp == val,
				  1 * USEC_PER_MSEC, रुकोms * USEC_PER_MSEC);
पूर्ण

अटल पूर्णांक prestera_fw_cmd_send(काष्ठा prestera_fw *fw,
				व्योम *in_msg, माप_प्रकार in_size,
				व्योम *out_msg, माप_प्रकार out_size,
				अचिन्हित पूर्णांक रुकोms)
अणु
	u32 ret_size;
	पूर्णांक err;

	अगर (!रुकोms)
		रुकोms = PRESTERA_FW_CMD_DEFAULT_WAIT_MS;

	अगर (ALIGN(in_size, 4) > fw->cmd_mbox_len)
		वापस -EMSGSIZE;

	/* रुको क्रम finish previous reply from FW */
	err = prestera_fw_रुको_reg32(fw, PRESTERA_CMD_RCV_CTL_REG, 0, 30);
	अगर (err) अणु
		dev_err(fw->dev.dev, "finish reply from FW is timed out\n");
		वापस err;
	पूर्ण

	prestera_fw_ग_लिखो(fw, PRESTERA_CMD_REQ_LEN_REG, in_size);
	स_नकल_toio(fw->cmd_mbox, in_msg, in_size);

	prestera_fw_ग_लिखो(fw, PRESTERA_CMD_REQ_CTL_REG, PRESTERA_CMD_F_REQ_SENT);

	/* रुको क्रम reply from FW */
	err = prestera_fw_रुको_reg32(fw, PRESTERA_CMD_RCV_CTL_REG,
				     PRESTERA_CMD_F_REPL_SENT, रुकोms);
	अगर (err) अणु
		dev_err(fw->dev.dev, "reply from FW is timed out\n");
		जाओ cmd_निकास;
	पूर्ण

	ret_size = prestera_fw_पढ़ो(fw, PRESTERA_CMD_RCV_LEN_REG);
	अगर (ret_size > out_size) अणु
		dev_err(fw->dev.dev, "ret_size (%u) > out_len(%zu)\n",
			ret_size, out_size);
		err = -EMSGSIZE;
		जाओ cmd_निकास;
	पूर्ण

	स_नकल_fromio(out_msg, fw->cmd_mbox + in_size, ret_size);

cmd_निकास:
	prestera_fw_ग_लिखो(fw, PRESTERA_CMD_REQ_CTL_REG, PRESTERA_CMD_F_REPL_RCVD);
	वापस err;
पूर्ण

अटल पूर्णांक prestera_fw_send_req(काष्ठा prestera_device *dev,
				व्योम *in_msg, माप_प्रकार in_size, व्योम *out_msg,
				माप_प्रकार out_size, अचिन्हित पूर्णांक रुकोms)
अणु
	काष्ठा prestera_fw *fw;
	sमाप_प्रकार ret;

	fw = container_of(dev, काष्ठा prestera_fw, dev);

	mutex_lock(&fw->cmd_mtx);
	ret = prestera_fw_cmd_send(fw, in_msg, in_size, out_msg, out_size, रुकोms);
	mutex_unlock(&fw->cmd_mtx);

	वापस ret;
पूर्ण

अटल पूर्णांक prestera_fw_init(काष्ठा prestera_fw *fw)
अणु
	u8 __iomem *base;
	पूर्णांक err;
	u8 qid;

	fw->dev.send_req = prestera_fw_send_req;
	fw->ldr_regs = fw->dev.ctl_regs;

	err = prestera_fw_load(fw);
	अगर (err)
		वापस err;

	err = prestera_fw_रुको_reg32(fw, PRESTERA_FW_READY_REG,
				     PRESTERA_FW_READY_MAGIC,
				     PRESTERA_FW_READY_WAIT_MS);
	अगर (err) अणु
		dev_err(fw->dev.dev, "FW failed to start\n");
		वापस err;
	पूर्ण

	base = fw->dev.ctl_regs;

	fw->cmd_mbox = base + prestera_fw_पढ़ो(fw, PRESTERA_CMD_BUF_OFFS_REG);
	fw->cmd_mbox_len = prestera_fw_पढ़ो(fw, PRESTERA_CMD_BUF_LEN_REG);
	mutex_init(&fw->cmd_mtx);

	fw->evt_buf = base + prestera_fw_पढ़ो(fw, PRESTERA_EVT_BUF_OFFS_REG);
	fw->evt_qnum = prestera_fw_पढ़ो(fw, PRESTERA_EVT_QNUM_REG);
	fw->evt_msg = kदो_स्मृति(PRESTERA_MSG_MAX_SIZE, GFP_KERNEL);
	अगर (!fw->evt_msg)
		वापस -ENOMEM;

	क्रम (qid = 0; qid < fw->evt_qnum; qid++) अणु
		u32 offs = prestera_fw_पढ़ो(fw, PRESTERA_EVTQ_OFFS_REG(qid));
		काष्ठा prestera_fw_evtq *evtq = &fw->evt_queue[qid];

		evtq->len = prestera_fw_पढ़ो(fw, PRESTERA_EVTQ_LEN_REG(qid));
		evtq->addr = fw->evt_buf + offs;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम prestera_fw_uninit(काष्ठा prestera_fw *fw)
अणु
	kमुक्त(fw->evt_msg);
पूर्ण

अटल irqवापस_t prestera_pci_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा prestera_fw *fw = dev_id;

	अगर (prestera_fw_पढ़ो(fw, PRESTERA_RX_STATUS_REG)) अणु
		prestera_fw_ग_लिखो(fw, PRESTERA_RX_STATUS_REG, 0);

		अगर (fw->dev.recv_pkt)
			fw->dev.recv_pkt(&fw->dev);
	पूर्ण

	queue_work(fw->wq, &fw->evt_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम prestera_ldr_ग_लिखो(काष्ठा prestera_fw *fw, u32 reg, u32 val)
अणु
	ग_लिखोl(val, PRESTERA_LDR_REG_ADDR(fw, reg));
पूर्ण

अटल u32 prestera_ldr_पढ़ो(काष्ठा prestera_fw *fw, u32 reg)
अणु
	वापस पढ़ोl(PRESTERA_LDR_REG_ADDR(fw, reg));
पूर्ण

अटल पूर्णांक prestera_ldr_रुको_reg32(काष्ठा prestera_fw *fw,
				   u32 reg, u32 cmp, अचिन्हित पूर्णांक रुकोms)
अणु
	u8 __iomem *addr = PRESTERA_LDR_REG_ADDR(fw, reg);
	u32 val;

	वापस पढ़ोl_poll_समयout(addr, val, cmp == val,
				  10 * USEC_PER_MSEC, रुकोms * USEC_PER_MSEC);
पूर्ण

अटल u32 prestera_ldr_रुको_buf(काष्ठा prestera_fw *fw, माप_प्रकार len)
अणु
	u8 __iomem *addr = PRESTERA_LDR_REG_ADDR(fw, PRESTERA_LDR_BUF_RD_REG);
	u32 buf_len = fw->ldr_buf_len;
	u32 wr_idx = fw->ldr_wr_idx;
	u32 rd_idx;

	वापस पढ़ोl_poll_समयout(addr, rd_idx,
				 CIRC_SPACE(wr_idx, rd_idx, buf_len) >= len,
				 1 * USEC_PER_MSEC, 100 * USEC_PER_MSEC);
पूर्ण

अटल पूर्णांक prestera_ldr_रुको_dl_finish(काष्ठा prestera_fw *fw)
अणु
	u8 __iomem *addr = PRESTERA_LDR_REG_ADDR(fw, PRESTERA_LDR_STATUS_REG);
	अचिन्हित दीर्घ mask = ~(PRESTERA_LDR_STATUS_IMG_DL);
	u32 val;
	पूर्णांक err;

	err = पढ़ोl_poll_समयout(addr, val, val & mask, 10 * USEC_PER_MSEC,
				 PRESTERA_FW_DL_TIMEOUT_MS * USEC_PER_MSEC);
	अगर (err) अणु
		dev_err(fw->dev.dev, "Timeout to load FW img [state=%d]",
			prestera_ldr_पढ़ो(fw, PRESTERA_LDR_STATUS_REG));
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम prestera_ldr_wr_idx_move(काष्ठा prestera_fw *fw, अचिन्हित पूर्णांक n)
अणु
	fw->ldr_wr_idx = (fw->ldr_wr_idx + (n)) & (fw->ldr_buf_len - 1);
पूर्ण

अटल व्योम prestera_ldr_wr_idx_commit(काष्ठा prestera_fw *fw)
अणु
	prestera_ldr_ग_लिखो(fw, PRESTERA_LDR_BUF_WR_REG, fw->ldr_wr_idx);
पूर्ण

अटल u8 __iomem *prestera_ldr_wr_ptr(काष्ठा prestera_fw *fw)
अणु
	वापस fw->ldr_ring_buf + fw->ldr_wr_idx;
पूर्ण

अटल पूर्णांक prestera_ldr_send(काष्ठा prestera_fw *fw, स्थिर u8 *buf, माप_प्रकार len)
अणु
	पूर्णांक err;
	पूर्णांक i;

	err = prestera_ldr_रुको_buf(fw, len);
	अगर (err) अणु
		dev_err(fw->dev.dev, "failed wait for sending firmware\n");
		वापस err;
	पूर्ण

	क्रम (i = 0; i < len; i += 4) अणु
		ग_लिखोl_relaxed(*(u32 *)(buf + i), prestera_ldr_wr_ptr(fw));
		prestera_ldr_wr_idx_move(fw, 4);
	पूर्ण

	prestera_ldr_wr_idx_commit(fw);
	वापस 0;
पूर्ण

अटल पूर्णांक prestera_ldr_fw_send(काष्ठा prestera_fw *fw,
				स्थिर अक्षर *img, u32 fw_size)
अणु
	u32 status;
	u32 pos;
	पूर्णांक err;

	err = prestera_ldr_रुको_reg32(fw, PRESTERA_LDR_STATUS_REG,
				      PRESTERA_LDR_STATUS_IMG_DL,
				      5 * MSEC_PER_SEC);
	अगर (err) अणु
		dev_err(fw->dev.dev, "Loader is not ready to load image\n");
		वापस err;
	पूर्ण

	क्रम (pos = 0; pos < fw_size; pos += PRESTERA_FW_BLK_SZ) अणु
		अगर (pos + PRESTERA_FW_BLK_SZ > fw_size)
			अवरोध;

		err = prestera_ldr_send(fw, img + pos, PRESTERA_FW_BLK_SZ);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (pos < fw_size) अणु
		err = prestera_ldr_send(fw, img + pos, fw_size - pos);
		अगर (err)
			वापस err;
	पूर्ण

	err = prestera_ldr_रुको_dl_finish(fw);
	अगर (err)
		वापस err;

	status = prestera_ldr_पढ़ो(fw, PRESTERA_LDR_STATUS_REG);

	चयन (status) अणु
	हाल PRESTERA_LDR_STATUS_INVALID_IMG:
		dev_err(fw->dev.dev, "FW img has bad CRC\n");
		वापस -EINVAL;
	हाल PRESTERA_LDR_STATUS_NOMEM:
		dev_err(fw->dev.dev, "Loader has no enough mem\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम prestera_fw_rev_parse(स्थिर काष्ठा prestera_fw_header *hdr,
				  काष्ठा prestera_fw_rev *rev)
अणु
	u32 version = be32_to_cpu(hdr->version_value);

	rev->maj = PRESTERA_FW_VER_MAJ(version);
	rev->min = PRESTERA_FW_VER_MIN(version);
	rev->sub = PRESTERA_FW_VER_PATCH(version);
पूर्ण

अटल पूर्णांक prestera_fw_rev_check(काष्ठा prestera_fw *fw)
अणु
	काष्ठा prestera_fw_rev *rev = &fw->dev.fw_rev;
	u16 maj_supp = PRESTERA_SUPP_FW_MAJ_VER;
	u16 min_supp = PRESTERA_SUPP_FW_MIN_VER;

	अगर (rev->maj == maj_supp && rev->min >= min_supp)
		वापस 0;

	dev_err(fw->dev.dev, "Driver supports FW version only '%u.%u.x'",
		PRESTERA_SUPP_FW_MAJ_VER, PRESTERA_SUPP_FW_MIN_VER);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक prestera_fw_hdr_parse(काष्ठा prestera_fw *fw,
				 स्थिर काष्ठा firmware *img)
अणु
	काष्ठा prestera_fw_header *hdr = (काष्ठा prestera_fw_header *)img->data;
	काष्ठा prestera_fw_rev *rev = &fw->dev.fw_rev;
	u32 magic;

	magic = be32_to_cpu(hdr->magic_number);
	अगर (magic != PRESTERA_FW_HDR_MAGIC) अणु
		dev_err(fw->dev.dev, "FW img hdr magic is invalid");
		वापस -EINVAL;
	पूर्ण

	prestera_fw_rev_parse(hdr, rev);

	dev_info(fw->dev.dev, "FW version '%u.%u.%u'\n",
		 rev->maj, rev->min, rev->sub);

	वापस prestera_fw_rev_check(fw);
पूर्ण

अटल पूर्णांक prestera_fw_load(काष्ठा prestera_fw *fw)
अणु
	माप_प्रकार hlen = माप(काष्ठा prestera_fw_header);
	स्थिर काष्ठा firmware *f;
	अक्षर fw_path[128];
	पूर्णांक err;

	err = prestera_ldr_रुको_reg32(fw, PRESTERA_LDR_READY_REG,
				      PRESTERA_LDR_READY_MAGIC,
				      5 * MSEC_PER_SEC);
	अगर (err) अणु
		dev_err(fw->dev.dev, "waiting for FW loader is timed out");
		वापस err;
	पूर्ण

	fw->ldr_ring_buf = fw->ldr_regs +
		prestera_ldr_पढ़ो(fw, PRESTERA_LDR_BUF_OFFS_REG);

	fw->ldr_buf_len =
		prestera_ldr_पढ़ो(fw, PRESTERA_LDR_BUF_SIZE_REG);

	fw->ldr_wr_idx = 0;

	snम_लिखो(fw_path, माप(fw_path), PRESTERA_FW_PATH_FMT,
		 PRESTERA_SUPP_FW_MAJ_VER, PRESTERA_SUPP_FW_MIN_VER);

	err = request_firmware_direct(&f, fw_path, fw->dev.dev);
	अगर (err) अणु
		dev_err(fw->dev.dev, "failed to request firmware file\n");
		वापस err;
	पूर्ण

	err = prestera_fw_hdr_parse(fw, f);
	अगर (err) अणु
		dev_err(fw->dev.dev, "FW image header is invalid\n");
		जाओ out_release;
	पूर्ण

	prestera_ldr_ग_लिखो(fw, PRESTERA_LDR_IMG_SIZE_REG, f->size - hlen);
	prestera_ldr_ग_लिखो(fw, PRESTERA_LDR_CTL_REG, PRESTERA_LDR_CTL_DL_START);

	dev_info(fw->dev.dev, "Loading %s ...", fw_path);

	err = prestera_ldr_fw_send(fw, f->data + hlen, f->size - hlen);

out_release:
	release_firmware(f);
	वापस err;
पूर्ण

अटल पूर्णांक prestera_pci_probe(काष्ठा pci_dev *pdev,
			      स्थिर काष्ठा pci_device_id *id)
अणु
	स्थिर अक्षर *driver_name = pdev->driver->name;
	काष्ठा prestera_fw *fw;
	पूर्णांक err;

	err = pcim_enable_device(pdev);
	अगर (err)
		वापस err;

	err = pcim_iomap_regions(pdev, BIT(PRESTERA_PCI_BAR_FW) |
				 BIT(PRESTERA_PCI_BAR_PP),
				 pci_name(pdev));
	अगर (err)
		वापस err;

	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(30));
	अगर (err) अणु
		dev_err(&pdev->dev, "fail to set DMA mask\n");
		जाओ err_dma_mask;
	पूर्ण

	pci_set_master(pdev);

	fw = devm_kzalloc(&pdev->dev, माप(*fw), GFP_KERNEL);
	अगर (!fw) अणु
		err = -ENOMEM;
		जाओ err_pci_dev_alloc;
	पूर्ण

	fw->dev.ctl_regs = pcim_iomap_table(pdev)[PRESTERA_PCI_BAR_FW];
	fw->dev.pp_regs = pcim_iomap_table(pdev)[PRESTERA_PCI_BAR_PP];
	fw->dev.dev = &pdev->dev;

	pci_set_drvdata(pdev, fw);

	err = prestera_fw_init(fw);
	अगर (err)
		जाओ err_prestera_fw_init;

	dev_info(fw->dev.dev, "Prestera FW is ready\n");

	fw->wq = alloc_workqueue("prestera_fw_wq", WQ_HIGHPRI, 1);
	अगर (!fw->wq) अणु
		err = -ENOMEM;
		जाओ err_wq_alloc;
	पूर्ण

	INIT_WORK(&fw->evt_work, prestera_fw_evt_work_fn);

	err = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_MSI);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "MSI IRQ init failed\n");
		जाओ err_irq_alloc;
	पूर्ण

	err = request_irq(pci_irq_vector(pdev, 0), prestera_pci_irq_handler,
			  0, driver_name, fw);
	अगर (err) अणु
		dev_err(&pdev->dev, "fail to request IRQ\n");
		जाओ err_request_irq;
	पूर्ण

	err = prestera_device_रेजिस्टर(&fw->dev);
	अगर (err)
		जाओ err_prestera_dev_रेजिस्टर;

	वापस 0;

err_prestera_dev_रेजिस्टर:
	मुक्त_irq(pci_irq_vector(pdev, 0), fw);
err_request_irq:
	pci_मुक्त_irq_vectors(pdev);
err_irq_alloc:
	destroy_workqueue(fw->wq);
err_wq_alloc:
	prestera_fw_uninit(fw);
err_prestera_fw_init:
err_pci_dev_alloc:
err_dma_mask:
	वापस err;
पूर्ण

अटल व्योम prestera_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा prestera_fw *fw = pci_get_drvdata(pdev);

	prestera_device_unरेजिस्टर(&fw->dev);
	मुक्त_irq(pci_irq_vector(pdev, 0), fw);
	pci_मुक्त_irq_vectors(pdev);
	destroy_workqueue(fw->wq);
	prestera_fw_uninit(fw);
पूर्ण

अटल स्थिर काष्ठा pci_device_id prestera_pci_devices[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0xC804) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0xC80C) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, prestera_pci_devices);

अटल काष्ठा pci_driver prestera_pci_driver = अणु
	.name     = "Prestera DX",
	.id_table = prestera_pci_devices,
	.probe    = prestera_pci_probe,
	.हटाओ   = prestera_pci_हटाओ,
पूर्ण;
module_pci_driver(prestera_pci_driver);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Marvell Prestera switch PCI interface");
