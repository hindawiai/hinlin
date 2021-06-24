<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2017 - 2019 Pensanकरो Systems, Inc */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/etherdevice.h>
#समावेश "ionic.h"
#समावेश "ionic_dev.h"
#समावेश "ionic_lif.h"

अटल व्योम ionic_watchकरोg_cb(काष्ठा समयr_list *t)
अणु
	काष्ठा ionic *ionic = from_समयr(ionic, t, watchकरोg_समयr);
	काष्ठा ionic_lअगर *lअगर = ionic->lअगर;
	पूर्णांक hb;

	mod_समयr(&ionic->watchकरोg_समयr,
		  round_jअगरfies(jअगरfies + ionic->watchकरोg_period));

	अगर (!lअगर)
		वापस;

	hb = ionic_heartbeat_check(ionic);
	dev_dbg(ionic->dev, "%s: hb %d running %d UP %d\n",
		__func__, hb, netअगर_running(lअगर->netdev),
		test_bit(IONIC_LIF_F_UP, lअगर->state));

	अगर (hb >= 0 &&
	    !test_bit(IONIC_LIF_F_FW_RESET, lअगर->state))
		ionic_link_status_check_request(lअगर, CAN_NOT_SLEEP);
पूर्ण

व्योम ionic_init_devinfo(काष्ठा ionic *ionic)
अणु
	काष्ठा ionic_dev *idev = &ionic->idev;

	idev->dev_info.asic_type = ioपढ़ो8(&idev->dev_info_regs->asic_type);
	idev->dev_info.asic_rev = ioपढ़ो8(&idev->dev_info_regs->asic_rev);

	स_नकल_fromio(idev->dev_info.fw_version,
		      idev->dev_info_regs->fw_version,
		      IONIC_DEVINFO_FWVERS_BUFLEN);

	स_नकल_fromio(idev->dev_info.serial_num,
		      idev->dev_info_regs->serial_num,
		      IONIC_DEVINFO_SERIAL_BUFLEN);

	idev->dev_info.fw_version[IONIC_DEVINFO_FWVERS_BUFLEN] = 0;
	idev->dev_info.serial_num[IONIC_DEVINFO_SERIAL_BUFLEN] = 0;

	dev_dbg(ionic->dev, "fw_version %s\n", idev->dev_info.fw_version);
पूर्ण

पूर्णांक ionic_dev_setup(काष्ठा ionic *ionic)
अणु
	काष्ठा ionic_dev_bar *bar = ionic->bars;
	अचिन्हित पूर्णांक num_bars = ionic->num_bars;
	काष्ठा ionic_dev *idev = &ionic->idev;
	काष्ठा device *dev = ionic->dev;
	u32 sig;

	/* BAR0: dev_cmd and पूर्णांकerrupts */
	अगर (num_bars < 1) अणु
		dev_err(dev, "No bars found, aborting\n");
		वापस -EFAULT;
	पूर्ण

	अगर (bar->len < IONIC_BAR0_SIZE) अणु
		dev_err(dev, "Resource bar size %lu too small, aborting\n",
			bar->len);
		वापस -EFAULT;
	पूर्ण

	idev->dev_info_regs = bar->vaddr + IONIC_BAR0_DEV_INFO_REGS_OFFSET;
	idev->dev_cmd_regs = bar->vaddr + IONIC_BAR0_DEV_CMD_REGS_OFFSET;
	idev->पूर्णांकr_status = bar->vaddr + IONIC_BAR0_INTR_STATUS_OFFSET;
	idev->पूर्णांकr_ctrl = bar->vaddr + IONIC_BAR0_INTR_CTRL_OFFSET;

	idev->hwstamp_regs = &idev->dev_info_regs->hwstamp;

	sig = ioपढ़ो32(&idev->dev_info_regs->signature);
	अगर (sig != IONIC_DEV_INFO_SIGNATURE) अणु
		dev_err(dev, "Incompatible firmware signature %x", sig);
		वापस -EFAULT;
	पूर्ण

	ionic_init_devinfo(ionic);

	/* BAR1: करोorbells */
	bar++;
	अगर (num_bars < 2) अणु
		dev_err(dev, "Doorbell bar missing, aborting\n");
		वापस -EFAULT;
	पूर्ण

	समयr_setup(&ionic->watchकरोg_समयr, ionic_watchकरोg_cb, 0);
	ionic->watchकरोg_period = IONIC_WATCHDOG_SECS * HZ;

	/* set बार to ensure the first check will proceed */
	atomic_दीर्घ_set(&idev->last_check_समय, jअगरfies - 2 * HZ);
	idev->last_hb_समय = jअगरfies - 2 * ionic->watchकरोg_period;
	/* init as पढ़ोy, so no transition अगर the first check succeeds */
	idev->last_fw_hb = 0;
	idev->fw_hb_पढ़ोy = true;
	idev->fw_status_पढ़ोy = true;

	mod_समयr(&ionic->watchकरोg_समयr,
		  round_jअगरfies(jअगरfies + ionic->watchकरोg_period));

	idev->db_pages = bar->vaddr;
	idev->phy_db_pages = bar->bus_addr;

	वापस 0;
पूर्ण

/* Devcmd Interface */
पूर्णांक ionic_heartbeat_check(काष्ठा ionic *ionic)
अणु
	काष्ठा ionic_dev *idev = &ionic->idev;
	अचिन्हित दीर्घ check_समय, last_check_समय;
	bool fw_status_पढ़ोy, fw_hb_पढ़ोy;
	u8 fw_status;
	u32 fw_hb;

	/* रुको a least one second beक्रमe testing again */
	check_समय = jअगरfies;
	last_check_समय = atomic_दीर्घ_पढ़ो(&idev->last_check_समय);
करो_check_समय:
	अगर (समय_beक्रमe(check_समय, last_check_समय + HZ))
		वापस 0;
	अगर (!atomic_दीर्घ_try_cmpxchg_relaxed(&idev->last_check_समय,
					     &last_check_समय, check_समय)) अणु
		/* अगर called concurrently, only the first should proceed. */
		dev_dbg(ionic->dev, "%s: do_check_time again\n", __func__);
		जाओ करो_check_समय;
	पूर्ण

	/* firmware is useful only अगर the running bit is set and
	 * fw_status != 0xff (bad PCI पढ़ो)
	 */
	fw_status = ioपढ़ो8(&idev->dev_info_regs->fw_status);
	fw_status_पढ़ोy = (fw_status != 0xff) && (fw_status & IONIC_FW_STS_F_RUNNING);

	/* is this a transition? */
	अगर (fw_status_पढ़ोy != idev->fw_status_पढ़ोy) अणु
		काष्ठा ionic_lअगर *lअगर = ionic->lअगर;
		bool trigger = false;

		idev->fw_status_पढ़ोy = fw_status_पढ़ोy;

		अगर (!fw_status_पढ़ोy) अणु
			dev_info(ionic->dev, "FW stopped %u\n", fw_status);
			अगर (lअगर && !test_bit(IONIC_LIF_F_FW_RESET, lअगर->state))
				trigger = true;
		पूर्ण अन्यथा अणु
			dev_info(ionic->dev, "FW running %u\n", fw_status);
			अगर (lअगर && test_bit(IONIC_LIF_F_FW_RESET, lअगर->state))
				trigger = true;
		पूर्ण

		अगर (trigger) अणु
			काष्ठा ionic_deferred_work *work;

			work = kzalloc(माप(*work), GFP_ATOMIC);
			अगर (work) अणु
				work->type = IONIC_DW_TYPE_LIF_RESET;
				work->fw_status = fw_status_पढ़ोy;
				ionic_lअगर_deferred_enqueue(&lअगर->deferred, work);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!fw_status_पढ़ोy)
		वापस -ENXIO;

	/* रुको at least one watchकरोg period since the last heartbeat */
	last_check_समय = idev->last_hb_समय;
	अगर (समय_beक्रमe(check_समय, last_check_समय + ionic->watchकरोg_period))
		वापस 0;

	fw_hb = ioपढ़ो32(&idev->dev_info_regs->fw_heartbeat);
	fw_hb_पढ़ोy = fw_hb != idev->last_fw_hb;

	/* early FW version had no heartbeat, so fake it */
	अगर (!fw_hb_पढ़ोy && !fw_hb)
		fw_hb_पढ़ोy = true;

	dev_dbg(ionic->dev, "%s: fw_hb %u last_fw_hb %u ready %u\n",
		__func__, fw_hb, idev->last_fw_hb, fw_hb_पढ़ोy);

	idev->last_fw_hb = fw_hb;

	/* log a transition */
	अगर (fw_hb_पढ़ोy != idev->fw_hb_पढ़ोy) अणु
		idev->fw_hb_पढ़ोy = fw_hb_पढ़ोy;
		अगर (!fw_hb_पढ़ोy)
			dev_info(ionic->dev, "FW heartbeat stalled at %d\n", fw_hb);
		अन्यथा
			dev_info(ionic->dev, "FW heartbeat restored at %d\n", fw_hb);
	पूर्ण

	अगर (!fw_hb_पढ़ोy)
		वापस -ENXIO;

	idev->last_hb_समय = check_समय;

	वापस 0;
पूर्ण

u8 ionic_dev_cmd_status(काष्ठा ionic_dev *idev)
अणु
	वापस ioपढ़ो8(&idev->dev_cmd_regs->comp.comp.status);
पूर्ण

bool ionic_dev_cmd_करोne(काष्ठा ionic_dev *idev)
अणु
	वापस ioपढ़ो32(&idev->dev_cmd_regs->करोne) & IONIC_DEV_CMD_DONE;
पूर्ण

व्योम ionic_dev_cmd_comp(काष्ठा ionic_dev *idev, जोड़ ionic_dev_cmd_comp *comp)
अणु
	स_नकल_fromio(comp, &idev->dev_cmd_regs->comp, माप(*comp));
पूर्ण

व्योम ionic_dev_cmd_go(काष्ठा ionic_dev *idev, जोड़ ionic_dev_cmd *cmd)
अणु
	स_नकल_toio(&idev->dev_cmd_regs->cmd, cmd, माप(*cmd));
	ioग_लिखो32(0, &idev->dev_cmd_regs->करोne);
	ioग_लिखो32(1, &idev->dev_cmd_regs->करोorbell);
पूर्ण

/* Device commands */
व्योम ionic_dev_cmd_identअगरy(काष्ठा ionic_dev *idev, u8 ver)
अणु
	जोड़ ionic_dev_cmd cmd = अणु
		.identअगरy.opcode = IONIC_CMD_IDENTIFY,
		.identअगरy.ver = ver,
	पूर्ण;

	ionic_dev_cmd_go(idev, &cmd);
पूर्ण

व्योम ionic_dev_cmd_init(काष्ठा ionic_dev *idev)
अणु
	जोड़ ionic_dev_cmd cmd = अणु
		.init.opcode = IONIC_CMD_INIT,
		.init.type = 0,
	पूर्ण;

	ionic_dev_cmd_go(idev, &cmd);
पूर्ण

व्योम ionic_dev_cmd_reset(काष्ठा ionic_dev *idev)
अणु
	जोड़ ionic_dev_cmd cmd = अणु
		.reset.opcode = IONIC_CMD_RESET,
	पूर्ण;

	ionic_dev_cmd_go(idev, &cmd);
पूर्ण

/* Port commands */
व्योम ionic_dev_cmd_port_identअगरy(काष्ठा ionic_dev *idev)
अणु
	जोड़ ionic_dev_cmd cmd = अणु
		.port_init.opcode = IONIC_CMD_PORT_IDENTIFY,
		.port_init.index = 0,
	पूर्ण;

	ionic_dev_cmd_go(idev, &cmd);
पूर्ण

व्योम ionic_dev_cmd_port_init(काष्ठा ionic_dev *idev)
अणु
	जोड़ ionic_dev_cmd cmd = अणु
		.port_init.opcode = IONIC_CMD_PORT_INIT,
		.port_init.index = 0,
		.port_init.info_pa = cpu_to_le64(idev->port_info_pa),
	पूर्ण;

	ionic_dev_cmd_go(idev, &cmd);
पूर्ण

व्योम ionic_dev_cmd_port_reset(काष्ठा ionic_dev *idev)
अणु
	जोड़ ionic_dev_cmd cmd = अणु
		.port_reset.opcode = IONIC_CMD_PORT_RESET,
		.port_reset.index = 0,
	पूर्ण;

	ionic_dev_cmd_go(idev, &cmd);
पूर्ण

व्योम ionic_dev_cmd_port_state(काष्ठा ionic_dev *idev, u8 state)
अणु
	जोड़ ionic_dev_cmd cmd = अणु
		.port_setattr.opcode = IONIC_CMD_PORT_SETATTR,
		.port_setattr.index = 0,
		.port_setattr.attr = IONIC_PORT_ATTR_STATE,
		.port_setattr.state = state,
	पूर्ण;

	ionic_dev_cmd_go(idev, &cmd);
पूर्ण

व्योम ionic_dev_cmd_port_speed(काष्ठा ionic_dev *idev, u32 speed)
अणु
	जोड़ ionic_dev_cmd cmd = अणु
		.port_setattr.opcode = IONIC_CMD_PORT_SETATTR,
		.port_setattr.index = 0,
		.port_setattr.attr = IONIC_PORT_ATTR_SPEED,
		.port_setattr.speed = cpu_to_le32(speed),
	पूर्ण;

	ionic_dev_cmd_go(idev, &cmd);
पूर्ण

व्योम ionic_dev_cmd_port_स्वतःneg(काष्ठा ionic_dev *idev, u8 an_enable)
अणु
	जोड़ ionic_dev_cmd cmd = अणु
		.port_setattr.opcode = IONIC_CMD_PORT_SETATTR,
		.port_setattr.index = 0,
		.port_setattr.attr = IONIC_PORT_ATTR_AUTONEG,
		.port_setattr.an_enable = an_enable,
	पूर्ण;

	ionic_dev_cmd_go(idev, &cmd);
पूर्ण

व्योम ionic_dev_cmd_port_fec(काष्ठा ionic_dev *idev, u8 fec_type)
अणु
	जोड़ ionic_dev_cmd cmd = अणु
		.port_setattr.opcode = IONIC_CMD_PORT_SETATTR,
		.port_setattr.index = 0,
		.port_setattr.attr = IONIC_PORT_ATTR_FEC,
		.port_setattr.fec_type = fec_type,
	पूर्ण;

	ionic_dev_cmd_go(idev, &cmd);
पूर्ण

व्योम ionic_dev_cmd_port_छोड़ो(काष्ठा ionic_dev *idev, u8 छोड़ो_type)
अणु
	जोड़ ionic_dev_cmd cmd = अणु
		.port_setattr.opcode = IONIC_CMD_PORT_SETATTR,
		.port_setattr.index = 0,
		.port_setattr.attr = IONIC_PORT_ATTR_PAUSE,
		.port_setattr.छोड़ो_type = छोड़ो_type,
	पूर्ण;

	ionic_dev_cmd_go(idev, &cmd);
पूर्ण

/* VF commands */
पूर्णांक ionic_set_vf_config(काष्ठा ionic *ionic, पूर्णांक vf, u8 attr, u8 *data)
अणु
	जोड़ ionic_dev_cmd cmd = अणु
		.vf_setattr.opcode = IONIC_CMD_VF_SETATTR,
		.vf_setattr.attr = attr,
		.vf_setattr.vf_index = cpu_to_le16(vf),
	पूर्ण;
	पूर्णांक err;

	चयन (attr) अणु
	हाल IONIC_VF_ATTR_SPOOFCHK:
		cmd.vf_setattr.spoofchk = *data;
		dev_dbg(ionic->dev, "%s: vf %d spoof %d\n",
			__func__, vf, *data);
		अवरोध;
	हाल IONIC_VF_ATTR_TRUST:
		cmd.vf_setattr.trust = *data;
		dev_dbg(ionic->dev, "%s: vf %d trust %d\n",
			__func__, vf, *data);
		अवरोध;
	हाल IONIC_VF_ATTR_LINKSTATE:
		cmd.vf_setattr.linkstate = *data;
		dev_dbg(ionic->dev, "%s: vf %d linkstate %d\n",
			__func__, vf, *data);
		अवरोध;
	हाल IONIC_VF_ATTR_MAC:
		ether_addr_copy(cmd.vf_setattr.macaddr, data);
		dev_dbg(ionic->dev, "%s: vf %d macaddr %pM\n",
			__func__, vf, data);
		अवरोध;
	हाल IONIC_VF_ATTR_VLAN:
		cmd.vf_setattr.vlanid = cpu_to_le16(*(u16 *)data);
		dev_dbg(ionic->dev, "%s: vf %d vlan %d\n",
			__func__, vf, *(u16 *)data);
		अवरोध;
	हाल IONIC_VF_ATTR_RATE:
		cmd.vf_setattr.maxrate = cpu_to_le32(*(u32 *)data);
		dev_dbg(ionic->dev, "%s: vf %d maxrate %d\n",
			__func__, vf, *(u32 *)data);
		अवरोध;
	हाल IONIC_VF_ATTR_STATSADDR:
		cmd.vf_setattr.stats_pa = cpu_to_le64(*(u64 *)data);
		dev_dbg(ionic->dev, "%s: vf %d stats_pa 0x%08llx\n",
			__func__, vf, *(u64 *)data);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&ionic->dev_cmd_lock);
	ionic_dev_cmd_go(&ionic->idev, &cmd);
	err = ionic_dev_cmd_रुको(ionic, DEVCMD_TIMEOUT);
	mutex_unlock(&ionic->dev_cmd_lock);

	वापस err;
पूर्ण

/* LIF commands */
व्योम ionic_dev_cmd_queue_identअगरy(काष्ठा ionic_dev *idev,
				  u16 lअगर_type, u8 qtype, u8 qver)
अणु
	जोड़ ionic_dev_cmd cmd = अणु
		.q_identअगरy.opcode = IONIC_CMD_Q_IDENTIFY,
		.q_identअगरy.lअगर_type = cpu_to_le16(lअगर_type),
		.q_identअगरy.type = qtype,
		.q_identअगरy.ver = qver,
	पूर्ण;

	ionic_dev_cmd_go(idev, &cmd);
पूर्ण

व्योम ionic_dev_cmd_lअगर_identअगरy(काष्ठा ionic_dev *idev, u8 type, u8 ver)
अणु
	जोड़ ionic_dev_cmd cmd = अणु
		.lअगर_identअगरy.opcode = IONIC_CMD_LIF_IDENTIFY,
		.lअगर_identअगरy.type = type,
		.lअगर_identअगरy.ver = ver,
	पूर्ण;

	ionic_dev_cmd_go(idev, &cmd);
पूर्ण

व्योम ionic_dev_cmd_lअगर_init(काष्ठा ionic_dev *idev, u16 lअगर_index,
			    dma_addr_t info_pa)
अणु
	जोड़ ionic_dev_cmd cmd = अणु
		.lअगर_init.opcode = IONIC_CMD_LIF_INIT,
		.lअगर_init.index = cpu_to_le16(lअगर_index),
		.lअगर_init.info_pa = cpu_to_le64(info_pa),
	पूर्ण;

	ionic_dev_cmd_go(idev, &cmd);
पूर्ण

व्योम ionic_dev_cmd_lअगर_reset(काष्ठा ionic_dev *idev, u16 lअगर_index)
अणु
	जोड़ ionic_dev_cmd cmd = अणु
		.lअगर_init.opcode = IONIC_CMD_LIF_RESET,
		.lअगर_init.index = cpu_to_le16(lअगर_index),
	पूर्ण;

	ionic_dev_cmd_go(idev, &cmd);
पूर्ण

व्योम ionic_dev_cmd_adminq_init(काष्ठा ionic_dev *idev, काष्ठा ionic_qcq *qcq,
			       u16 lअगर_index, u16 पूर्णांकr_index)
अणु
	काष्ठा ionic_queue *q = &qcq->q;
	काष्ठा ionic_cq *cq = &qcq->cq;

	जोड़ ionic_dev_cmd cmd = अणु
		.q_init.opcode = IONIC_CMD_Q_INIT,
		.q_init.lअगर_index = cpu_to_le16(lअगर_index),
		.q_init.type = q->type,
		.q_init.ver = qcq->q.lअगर->qtype_info[q->type].version,
		.q_init.index = cpu_to_le32(q->index),
		.q_init.flags = cpu_to_le16(IONIC_QINIT_F_IRQ |
					    IONIC_QINIT_F_ENA),
		.q_init.pid = cpu_to_le16(q->pid),
		.q_init.पूर्णांकr_index = cpu_to_le16(पूर्णांकr_index),
		.q_init.ring_size = ilog2(q->num_descs),
		.q_init.ring_base = cpu_to_le64(q->base_pa),
		.q_init.cq_ring_base = cpu_to_le64(cq->base_pa),
	पूर्ण;

	ionic_dev_cmd_go(idev, &cmd);
पूर्ण

पूर्णांक ionic_db_page_num(काष्ठा ionic_lअगर *lअगर, पूर्णांक pid)
अणु
	वापस (lअगर->hw_index * lअगर->dbid_count) + pid;
पूर्ण

पूर्णांक ionic_cq_init(काष्ठा ionic_lअगर *lअगर, काष्ठा ionic_cq *cq,
		  काष्ठा ionic_पूर्णांकr_info *पूर्णांकr,
		  अचिन्हित पूर्णांक num_descs, माप_प्रकार desc_size)
अणु
	अचिन्हित पूर्णांक ring_size;

	अगर (desc_size == 0 || !is_घातer_of_2(num_descs))
		वापस -EINVAL;

	ring_size = ilog2(num_descs);
	अगर (ring_size < 2 || ring_size > 16)
		वापस -EINVAL;

	cq->lअगर = lअगर;
	cq->bound_पूर्णांकr = पूर्णांकr;
	cq->num_descs = num_descs;
	cq->desc_size = desc_size;
	cq->tail_idx = 0;
	cq->करोne_color = 1;

	वापस 0;
पूर्ण

व्योम ionic_cq_map(काष्ठा ionic_cq *cq, व्योम *base, dma_addr_t base_pa)
अणु
	काष्ठा ionic_cq_info *cur;
	अचिन्हित पूर्णांक i;

	cq->base = base;
	cq->base_pa = base_pa;

	क्रम (i = 0, cur = cq->info; i < cq->num_descs; i++, cur++)
		cur->cq_desc = base + (i * cq->desc_size);
पूर्ण

व्योम ionic_cq_bind(काष्ठा ionic_cq *cq, काष्ठा ionic_queue *q)
अणु
	cq->bound_q = q;
पूर्ण

अचिन्हित पूर्णांक ionic_cq_service(काष्ठा ionic_cq *cq, अचिन्हित पूर्णांक work_to_करो,
			      ionic_cq_cb cb, ionic_cq_करोne_cb करोne_cb,
			      व्योम *करोne_arg)
अणु
	काष्ठा ionic_cq_info *cq_info;
	अचिन्हित पूर्णांक work_करोne = 0;

	अगर (work_to_करो == 0)
		वापस 0;

	cq_info = &cq->info[cq->tail_idx];
	जबतक (cb(cq, cq_info)) अणु
		अगर (cq->tail_idx == cq->num_descs - 1)
			cq->करोne_color = !cq->करोne_color;
		cq->tail_idx = (cq->tail_idx + 1) & (cq->num_descs - 1);
		cq_info = &cq->info[cq->tail_idx];
		DEBUG_STATS_CQE_CNT(cq);

		अगर (++work_करोne >= work_to_करो)
			अवरोध;
	पूर्ण

	अगर (work_करोne && करोne_cb)
		करोne_cb(करोne_arg);

	वापस work_करोne;
पूर्ण

पूर्णांक ionic_q_init(काष्ठा ionic_lअगर *lअगर, काष्ठा ionic_dev *idev,
		 काष्ठा ionic_queue *q, अचिन्हित पूर्णांक index, स्थिर अक्षर *name,
		 अचिन्हित पूर्णांक num_descs, माप_प्रकार desc_size,
		 माप_प्रकार sg_desc_size, अचिन्हित पूर्णांक pid)
अणु
	अचिन्हित पूर्णांक ring_size;

	अगर (desc_size == 0 || !is_घातer_of_2(num_descs))
		वापस -EINVAL;

	ring_size = ilog2(num_descs);
	अगर (ring_size < 2 || ring_size > 16)
		वापस -EINVAL;

	q->lअगर = lअगर;
	q->idev = idev;
	q->index = index;
	q->num_descs = num_descs;
	q->desc_size = desc_size;
	q->sg_desc_size = sg_desc_size;
	q->tail_idx = 0;
	q->head_idx = 0;
	q->pid = pid;

	snम_लिखो(q->name, माप(q->name), "L%d-%s%u", lअगर->index, name, index);

	वापस 0;
पूर्ण

व्योम ionic_q_map(काष्ठा ionic_queue *q, व्योम *base, dma_addr_t base_pa)
अणु
	काष्ठा ionic_desc_info *cur;
	अचिन्हित पूर्णांक i;

	q->base = base;
	q->base_pa = base_pa;

	क्रम (i = 0, cur = q->info; i < q->num_descs; i++, cur++)
		cur->desc = base + (i * q->desc_size);
पूर्ण

व्योम ionic_q_sg_map(काष्ठा ionic_queue *q, व्योम *base, dma_addr_t base_pa)
अणु
	काष्ठा ionic_desc_info *cur;
	अचिन्हित पूर्णांक i;

	q->sg_base = base;
	q->sg_base_pa = base_pa;

	क्रम (i = 0, cur = q->info; i < q->num_descs; i++, cur++)
		cur->sg_desc = base + (i * q->sg_desc_size);
पूर्ण

व्योम ionic_q_post(काष्ठा ionic_queue *q, bool ring_करोorbell, ionic_desc_cb cb,
		  व्योम *cb_arg)
अणु
	काष्ठा ionic_desc_info *desc_info;
	काष्ठा ionic_lअगर *lअगर = q->lअगर;
	काष्ठा device *dev = q->dev;

	desc_info = &q->info[q->head_idx];
	desc_info->cb = cb;
	desc_info->cb_arg = cb_arg;

	q->head_idx = (q->head_idx + 1) & (q->num_descs - 1);

	dev_dbg(dev, "lif=%d qname=%s qid=%d qtype=%d p_index=%d ringdb=%d\n",
		q->lअगर->index, q->name, q->hw_type, q->hw_index,
		q->head_idx, ring_करोorbell);

	अगर (ring_करोorbell)
		ionic_dbell_ring(lअगर->kern_dbpage, q->hw_type,
				 q->dbval | q->head_idx);
पूर्ण

अटल bool ionic_q_is_posted(काष्ठा ionic_queue *q, अचिन्हित पूर्णांक pos)
अणु
	अचिन्हित पूर्णांक mask, tail, head;

	mask = q->num_descs - 1;
	tail = q->tail_idx;
	head = q->head_idx;

	वापस ((pos - tail) & mask) < ((head - tail) & mask);
पूर्ण

व्योम ionic_q_service(काष्ठा ionic_queue *q, काष्ठा ionic_cq_info *cq_info,
		     अचिन्हित पूर्णांक stop_index)
अणु
	काष्ठा ionic_desc_info *desc_info;
	ionic_desc_cb cb;
	व्योम *cb_arg;
	u16 index;

	/* check क्रम empty queue */
	अगर (q->tail_idx == q->head_idx)
		वापस;

	/* stop index must be क्रम a descriptor that is not yet completed */
	अगर (unlikely(!ionic_q_is_posted(q, stop_index)))
		dev_err(q->dev,
			"ionic stop is not posted %s stop %u tail %u head %u\n",
			q->name, stop_index, q->tail_idx, q->head_idx);

	करो अणु
		desc_info = &q->info[q->tail_idx];
		index = q->tail_idx;
		q->tail_idx = (q->tail_idx + 1) & (q->num_descs - 1);

		cb = desc_info->cb;
		cb_arg = desc_info->cb_arg;

		desc_info->cb = शून्य;
		desc_info->cb_arg = शून्य;

		अगर (cb)
			cb(q, desc_info, cq_info, cb_arg);
	पूर्ण जबतक (index != stop_index);
पूर्ण
