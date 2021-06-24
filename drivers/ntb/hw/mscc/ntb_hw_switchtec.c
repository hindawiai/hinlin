<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Microsemi Switchtec(पंचांग) PCIe Management Driver
 * Copyright (c) 2017, Microsemi Corporation
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/ntb.h>
#समावेश <linux/pci.h>
#समावेश <linux/चयनtec.h>

MODULE_DESCRIPTION("Microsemi Switchtec(tm) NTB Driver");
MODULE_VERSION("0.1");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Microsemi Corporation");

अटल uदीर्घ max_mw_size = SZ_2M;
module_param(max_mw_size, uदीर्घ, 0644);
MODULE_PARM_DESC(max_mw_size,
	"Max memory window size reported to the upper layer");

अटल bool use_lut_mws;
module_param(use_lut_mws, bool, 0644);
MODULE_PARM_DESC(use_lut_mws,
		 "Enable the use of the LUT based memory windows");

#घोषणा SWITCHTEC_NTB_MAGIC 0x45CC0001
#घोषणा MAX_MWS     128

काष्ठा shared_mw अणु
	u32 magic;
	u32 link_sta;
	u32 partition_id;
	u64 mw_sizes[MAX_MWS];
	u32 spad[128];
पूर्ण;

#घोषणा MAX_सूचीECT_MW ARRAY_SIZE(((काष्ठा ntb_ctrl_regs *)(0))->bar_entry)
#घोषणा LUT_SIZE SZ_64K

काष्ठा चयनtec_ntb अणु
	काष्ठा ntb_dev ntb;
	काष्ठा चयनtec_dev *stdev;

	पूर्णांक self_partition;
	पूर्णांक peer_partition;

	पूर्णांक करोorbell_irq;
	पूर्णांक message_irq;

	काष्ठा ntb_info_regs __iomem *mmio_ntb;
	काष्ठा ntb_ctrl_regs __iomem *mmio_ctrl;
	काष्ठा ntb_dbmsg_regs __iomem *mmio_dbmsg;
	काष्ठा ntb_ctrl_regs __iomem *mmio_self_ctrl;
	काष्ठा ntb_ctrl_regs __iomem *mmio_peer_ctrl;
	काष्ठा ntb_dbmsg_regs __iomem *mmio_self_dbmsg;
	काष्ठा ntb_dbmsg_regs __iomem *mmio_peer_dbmsg;

	व्योम __iomem *mmio_xlink_win;

	काष्ठा shared_mw *self_shared;
	काष्ठा shared_mw __iomem *peer_shared;
	dma_addr_t self_shared_dma;

	u64 db_mask;
	u64 db_valid_mask;
	पूर्णांक db_shअगरt;
	पूर्णांक db_peer_shअगरt;

	/* synchronize rmw access of db_mask and hw reg */
	spinlock_t db_mask_lock;

	पूर्णांक nr_direct_mw;
	पूर्णांक nr_lut_mw;
	पूर्णांक nr_rsvd_luts;
	पूर्णांक direct_mw_to_bar[MAX_सूचीECT_MW];

	पूर्णांक peer_nr_direct_mw;
	पूर्णांक peer_nr_lut_mw;
	पूर्णांक peer_direct_mw_to_bar[MAX_सूचीECT_MW];

	bool link_is_up;
	क्रमागत ntb_speed link_speed;
	क्रमागत ntb_width link_width;
	काष्ठा work_काष्ठा check_link_status_work;
	bool link_क्रमce_करोwn;
पूर्ण;

अटल काष्ठा चयनtec_ntb *ntb_sndev(काष्ठा ntb_dev *ntb)
अणु
	वापस container_of(ntb, काष्ठा चयनtec_ntb, ntb);
पूर्ण

अटल पूर्णांक चयनtec_ntb_part_op(काष्ठा चयनtec_ntb *sndev,
				 काष्ठा ntb_ctrl_regs __iomem *ctl,
				 u32 op, पूर्णांक रुको_status)
अणु
	अटल स्थिर अक्षर * स्थिर op_text[] = अणु
		[NTB_CTRL_PART_OP_LOCK] = "lock",
		[NTB_CTRL_PART_OP_CFG] = "configure",
		[NTB_CTRL_PART_OP_RESET] = "reset",
	पूर्ण;

	पूर्णांक i;
	u32 ps;
	पूर्णांक status;

	चयन (op) अणु
	हाल NTB_CTRL_PART_OP_LOCK:
		status = NTB_CTRL_PART_STATUS_LOCKING;
		अवरोध;
	हाल NTB_CTRL_PART_OP_CFG:
		status = NTB_CTRL_PART_STATUS_CONFIGURING;
		अवरोध;
	हाल NTB_CTRL_PART_OP_RESET:
		status = NTB_CTRL_PART_STATUS_RESETTING;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ioग_लिखो32(op, &ctl->partition_op);

	क्रम (i = 0; i < 1000; i++) अणु
		अगर (msleep_पूर्णांकerruptible(50) != 0) अणु
			ioग_लिखो32(NTB_CTRL_PART_OP_RESET, &ctl->partition_op);
			वापस -EINTR;
		पूर्ण

		ps = ioपढ़ो32(&ctl->partition_status) & 0xFFFF;

		अगर (ps != status)
			अवरोध;
	पूर्ण

	अगर (ps == रुको_status)
		वापस 0;

	अगर (ps == status) अणु
		dev_err(&sndev->stdev->dev,
			"Timed out while performing %s (%d). (%08x)\n",
			op_text[op], op,
			ioपढ़ो32(&ctl->partition_status));

		वापस -ETIMEDOUT;
	पूर्ण

	वापस -EIO;
पूर्ण

अटल पूर्णांक चयनtec_ntb_send_msg(काष्ठा चयनtec_ntb *sndev, पूर्णांक idx,
				  u32 val)
अणु
	अगर (idx < 0 || idx >= ARRAY_SIZE(sndev->mmio_peer_dbmsg->omsg))
		वापस -EINVAL;

	ioग_लिखो32(val, &sndev->mmio_peer_dbmsg->omsg[idx].msg);

	वापस 0;
पूर्ण

अटल पूर्णांक चयनtec_ntb_mw_count(काष्ठा ntb_dev *ntb, पूर्णांक pidx)
अणु
	काष्ठा चयनtec_ntb *sndev = ntb_sndev(ntb);
	पूर्णांक nr_direct_mw = sndev->peer_nr_direct_mw;
	पूर्णांक nr_lut_mw = sndev->peer_nr_lut_mw - sndev->nr_rsvd_luts;

	अगर (pidx != NTB_DEF_PEER_IDX)
		वापस -EINVAL;

	अगर (!use_lut_mws)
		nr_lut_mw = 0;

	वापस nr_direct_mw + nr_lut_mw;
पूर्ण

अटल पूर्णांक lut_index(काष्ठा चयनtec_ntb *sndev, पूर्णांक mw_idx)
अणु
	वापस mw_idx - sndev->nr_direct_mw + sndev->nr_rsvd_luts;
पूर्ण

अटल पूर्णांक peer_lut_index(काष्ठा चयनtec_ntb *sndev, पूर्णांक mw_idx)
अणु
	वापस mw_idx - sndev->peer_nr_direct_mw + sndev->nr_rsvd_luts;
पूर्ण

अटल पूर्णांक चयनtec_ntb_mw_get_align(काष्ठा ntb_dev *ntb, पूर्णांक pidx,
				      पूर्णांक widx, resource_माप_प्रकार *addr_align,
				      resource_माप_प्रकार *size_align,
				      resource_माप_प्रकार *size_max)
अणु
	काष्ठा चयनtec_ntb *sndev = ntb_sndev(ntb);
	पूर्णांक lut;
	resource_माप_प्रकार size;

	अगर (pidx != NTB_DEF_PEER_IDX)
		वापस -EINVAL;

	lut = widx >= sndev->peer_nr_direct_mw;
	size = ioपढ़ो64(&sndev->peer_shared->mw_sizes[widx]);

	अगर (size == 0)
		वापस -EINVAL;

	अगर (addr_align)
		*addr_align = lut ? size : SZ_4K;

	अगर (size_align)
		*size_align = lut ? size : SZ_4K;

	अगर (size_max)
		*size_max = size;

	वापस 0;
पूर्ण

अटल व्योम चयनtec_ntb_mw_clr_direct(काष्ठा चयनtec_ntb *sndev, पूर्णांक idx)
अणु
	काष्ठा ntb_ctrl_regs __iomem *ctl = sndev->mmio_peer_ctrl;
	पूर्णांक bar = sndev->peer_direct_mw_to_bar[idx];
	u32 ctl_val;

	ctl_val = ioपढ़ो32(&ctl->bar_entry[bar].ctl);
	ctl_val &= ~NTB_CTRL_BAR_सूची_WIN_EN;
	ioग_लिखो32(ctl_val, &ctl->bar_entry[bar].ctl);
	ioग_लिखो32(0, &ctl->bar_entry[bar].win_size);
	ioग_लिखो32(0, &ctl->bar_ext_entry[bar].win_size);
	ioग_लिखो64(sndev->self_partition, &ctl->bar_entry[bar].xlate_addr);
पूर्ण

अटल व्योम चयनtec_ntb_mw_clr_lut(काष्ठा चयनtec_ntb *sndev, पूर्णांक idx)
अणु
	काष्ठा ntb_ctrl_regs __iomem *ctl = sndev->mmio_peer_ctrl;

	ioग_लिखो64(0, &ctl->lut_entry[peer_lut_index(sndev, idx)]);
पूर्ण

अटल व्योम चयनtec_ntb_mw_set_direct(काष्ठा चयनtec_ntb *sndev, पूर्णांक idx,
					dma_addr_t addr, resource_माप_प्रकार size)
अणु
	पूर्णांक xlate_pos = ilog2(size);
	पूर्णांक bar = sndev->peer_direct_mw_to_bar[idx];
	काष्ठा ntb_ctrl_regs __iomem *ctl = sndev->mmio_peer_ctrl;
	u32 ctl_val;

	ctl_val = ioपढ़ो32(&ctl->bar_entry[bar].ctl);
	ctl_val |= NTB_CTRL_BAR_सूची_WIN_EN;

	ioग_लिखो32(ctl_val, &ctl->bar_entry[bar].ctl);
	ioग_लिखो32(xlate_pos | (lower_32_bits(size) & 0xFFFFF000),
		  &ctl->bar_entry[bar].win_size);
	ioग_लिखो32(upper_32_bits(size), &ctl->bar_ext_entry[bar].win_size);
	ioग_लिखो64(sndev->self_partition | addr,
		  &ctl->bar_entry[bar].xlate_addr);
पूर्ण

अटल व्योम चयनtec_ntb_mw_set_lut(काष्ठा चयनtec_ntb *sndev, पूर्णांक idx,
				     dma_addr_t addr, resource_माप_प्रकार size)
अणु
	काष्ठा ntb_ctrl_regs __iomem *ctl = sndev->mmio_peer_ctrl;

	ioग_लिखो64((NTB_CTRL_LUT_EN | (sndev->self_partition << 1) | addr),
		  &ctl->lut_entry[peer_lut_index(sndev, idx)]);
पूर्ण

अटल पूर्णांक चयनtec_ntb_mw_set_trans(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक widx,
				      dma_addr_t addr, resource_माप_प्रकार size)
अणु
	काष्ठा चयनtec_ntb *sndev = ntb_sndev(ntb);
	काष्ठा ntb_ctrl_regs __iomem *ctl = sndev->mmio_peer_ctrl;
	पूर्णांक xlate_pos = ilog2(size);
	पूर्णांक nr_direct_mw = sndev->peer_nr_direct_mw;
	पूर्णांक rc;

	अगर (pidx != NTB_DEF_PEER_IDX)
		वापस -EINVAL;

	dev_dbg(&sndev->stdev->dev, "MW %d: part %d addr %pad size %pap\n",
		widx, pidx, &addr, &size);

	अगर (widx >= चयनtec_ntb_mw_count(ntb, pidx))
		वापस -EINVAL;

	अगर (size != 0 && xlate_pos < 12)
		वापस -EINVAL;

	अगर (!IS_ALIGNED(addr, BIT_ULL(xlate_pos))) अणु
		/*
		 * In certain circumstances we can get a buffer that is
		 * not aligned to its size. (Most of the समय
		 * dma_alloc_coherent ensures this). This can happen when
		 * using large buffers allocated by the CMA
		 * (see CMA_CONFIG_ALIGNMENT)
		 */
		dev_err(&sndev->stdev->dev,
			"ERROR: Memory window address is not aligned to it's size!\n");
		वापस -EINVAL;
	पूर्ण

	rc = चयनtec_ntb_part_op(sndev, ctl, NTB_CTRL_PART_OP_LOCK,
				   NTB_CTRL_PART_STATUS_LOCKED);
	अगर (rc)
		वापस rc;

	अगर (size == 0) अणु
		अगर (widx < nr_direct_mw)
			चयनtec_ntb_mw_clr_direct(sndev, widx);
		अन्यथा
			चयनtec_ntb_mw_clr_lut(sndev, widx);
	पूर्ण अन्यथा अणु
		अगर (widx < nr_direct_mw)
			चयनtec_ntb_mw_set_direct(sndev, widx, addr, size);
		अन्यथा
			चयनtec_ntb_mw_set_lut(sndev, widx, addr, size);
	पूर्ण

	rc = चयनtec_ntb_part_op(sndev, ctl, NTB_CTRL_PART_OP_CFG,
				   NTB_CTRL_PART_STATUS_NORMAL);

	अगर (rc == -EIO) अणु
		dev_err(&sndev->stdev->dev,
			"Hardware reported an error configuring mw %d: %08x\n",
			widx, ioपढ़ो32(&ctl->bar_error));

		अगर (widx < nr_direct_mw)
			चयनtec_ntb_mw_clr_direct(sndev, widx);
		अन्यथा
			चयनtec_ntb_mw_clr_lut(sndev, widx);

		चयनtec_ntb_part_op(sndev, ctl, NTB_CTRL_PART_OP_CFG,
				      NTB_CTRL_PART_STATUS_NORMAL);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक चयनtec_ntb_peer_mw_count(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा चयनtec_ntb *sndev = ntb_sndev(ntb);
	पूर्णांक nr_lut_mw = sndev->nr_lut_mw - sndev->nr_rsvd_luts;

	वापस sndev->nr_direct_mw + (use_lut_mws ? nr_lut_mw : 0);
पूर्ण

अटल पूर्णांक चयनtec_ntb_direct_get_addr(काष्ठा चयनtec_ntb *sndev,
					 पूर्णांक idx, phys_addr_t *base,
					 resource_माप_प्रकार *size)
अणु
	पूर्णांक bar = sndev->direct_mw_to_bar[idx];
	माप_प्रकार offset = 0;

	अगर (bar < 0)
		वापस -EINVAL;

	अगर (idx == 0) अणु
		/*
		 * This is the direct BAR shared with the LUTs
		 * which means the actual winकरोw will be offset
		 * by the size of all the LUT entries.
		 */

		offset = LUT_SIZE * sndev->nr_lut_mw;
	पूर्ण

	अगर (base)
		*base = pci_resource_start(sndev->ntb.pdev, bar) + offset;

	अगर (size) अणु
		*size = pci_resource_len(sndev->ntb.pdev, bar) - offset;
		अगर (offset && *size > offset)
			*size = offset;

		अगर (*size > max_mw_size)
			*size = max_mw_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक चयनtec_ntb_lut_get_addr(काष्ठा चयनtec_ntb *sndev,
				      पूर्णांक idx, phys_addr_t *base,
				      resource_माप_प्रकार *size)
अणु
	पूर्णांक bar = sndev->direct_mw_to_bar[0];
	पूर्णांक offset;

	offset = LUT_SIZE * lut_index(sndev, idx);

	अगर (base)
		*base = pci_resource_start(sndev->ntb.pdev, bar) + offset;

	अगर (size)
		*size = LUT_SIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक चयनtec_ntb_peer_mw_get_addr(काष्ठा ntb_dev *ntb, पूर्णांक idx,
					  phys_addr_t *base,
					  resource_माप_प्रकार *size)
अणु
	काष्ठा चयनtec_ntb *sndev = ntb_sndev(ntb);

	अगर (idx < sndev->nr_direct_mw)
		वापस चयनtec_ntb_direct_get_addr(sndev, idx, base, size);
	अन्यथा अगर (idx < चयनtec_ntb_peer_mw_count(ntb))
		वापस चयनtec_ntb_lut_get_addr(sndev, idx, base, size);
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल व्योम चयनtec_ntb_part_link_speed(काष्ठा चयनtec_ntb *sndev,
					  पूर्णांक partition,
					  क्रमागत ntb_speed *speed,
					  क्रमागत ntb_width *width)
अणु
	काष्ठा चयनtec_dev *stdev = sndev->stdev;

	u32 pff = ioपढ़ो32(&stdev->mmio_part_cfg[partition].vep_pff_inst_id);
	u32 linksta = ioपढ़ो32(&stdev->mmio_pff_csr[pff].pci_cap_region[13]);

	अगर (speed)
		*speed = (linksta >> 16) & 0xF;

	अगर (width)
		*width = (linksta >> 20) & 0x3F;
पूर्ण

अटल व्योम चयनtec_ntb_set_link_speed(काष्ठा चयनtec_ntb *sndev)
अणु
	क्रमागत ntb_speed self_speed, peer_speed;
	क्रमागत ntb_width self_width, peer_width;

	अगर (!sndev->link_is_up) अणु
		sndev->link_speed = NTB_SPEED_NONE;
		sndev->link_width = NTB_WIDTH_NONE;
		वापस;
	पूर्ण

	चयनtec_ntb_part_link_speed(sndev, sndev->self_partition,
				      &self_speed, &self_width);
	चयनtec_ntb_part_link_speed(sndev, sndev->peer_partition,
				      &peer_speed, &peer_width);

	sndev->link_speed = min(self_speed, peer_speed);
	sndev->link_width = min(self_width, peer_width);
पूर्ण

अटल पूर्णांक crosslink_is_enabled(काष्ठा चयनtec_ntb *sndev)
अणु
	काष्ठा ntb_info_regs __iomem *inf = sndev->mmio_ntb;

	वापस ioपढ़ो8(&inf->ntp_info[sndev->peer_partition].xlink_enabled);
पूर्ण

अटल व्योम crosslink_init_dbmsgs(काष्ठा चयनtec_ntb *sndev)
अणु
	पूर्णांक i;
	u32 msg_map = 0;

	अगर (!crosslink_is_enabled(sndev))
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(sndev->mmio_peer_dbmsg->imsg); i++) अणु
		पूर्णांक m = i | sndev->self_partition << 2;

		msg_map |= m << i * 8;
	पूर्ण

	ioग_लिखो32(msg_map, &sndev->mmio_peer_dbmsg->msg_map);
	ioग_लिखो64(sndev->db_valid_mask << sndev->db_peer_shअगरt,
		  &sndev->mmio_peer_dbmsg->odb_mask);
पूर्ण

क्रमागत चयनtec_msg अणु
	LINK_MESSAGE = 0,
	MSG_LINK_UP = 1,
	MSG_LINK_DOWN = 2,
	MSG_CHECK_LINK = 3,
	MSG_LINK_FORCE_DOWN = 4,
पूर्ण;

अटल पूर्णांक चयनtec_ntb_reinit_peer(काष्ठा चयनtec_ntb *sndev);

अटल व्योम चयनtec_ntb_link_status_update(काष्ठा चयनtec_ntb *sndev)
अणु
	पूर्णांक link_sta;
	पूर्णांक old = sndev->link_is_up;

	link_sta = sndev->self_shared->link_sta;
	अगर (link_sta) अणु
		u64 peer = ioपढ़ो64(&sndev->peer_shared->magic);

		अगर ((peer & 0xFFFFFFFF) == SWITCHTEC_NTB_MAGIC)
			link_sta = peer >> 32;
		अन्यथा
			link_sta = 0;
	पूर्ण

	sndev->link_is_up = link_sta;
	चयनtec_ntb_set_link_speed(sndev);

	अगर (link_sta != old) अणु
		चयनtec_ntb_send_msg(sndev, LINK_MESSAGE, MSG_CHECK_LINK);
		ntb_link_event(&sndev->ntb);
		dev_info(&sndev->stdev->dev, "ntb link %s\n",
			 link_sta ? "up" : "down");

		अगर (link_sta)
			crosslink_init_dbmsgs(sndev);
	पूर्ण
पूर्ण

अटल व्योम check_link_status_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा चयनtec_ntb *sndev;

	sndev = container_of(work, काष्ठा चयनtec_ntb,
			     check_link_status_work);

	अगर (sndev->link_क्रमce_करोwn) अणु
		sndev->link_क्रमce_करोwn = false;
		चयनtec_ntb_reinit_peer(sndev);

		अगर (sndev->link_is_up) अणु
			sndev->link_is_up = 0;
			ntb_link_event(&sndev->ntb);
			dev_info(&sndev->stdev->dev, "ntb link forced down\n");
		पूर्ण

		वापस;
	पूर्ण

	चयनtec_ntb_link_status_update(sndev);
पूर्ण

अटल व्योम चयनtec_ntb_check_link(काष्ठा चयनtec_ntb *sndev,
				      क्रमागत चयनtec_msg msg)
अणु
	अगर (msg == MSG_LINK_FORCE_DOWN)
		sndev->link_क्रमce_करोwn = true;

	schedule_work(&sndev->check_link_status_work);
पूर्ण

अटल व्योम चयनtec_ntb_link_notअगरication(काष्ठा चयनtec_dev *stdev)
अणु
	काष्ठा चयनtec_ntb *sndev = stdev->sndev;

	चयनtec_ntb_check_link(sndev, MSG_CHECK_LINK);
पूर्ण

अटल u64 चयनtec_ntb_link_is_up(काष्ठा ntb_dev *ntb,
				    क्रमागत ntb_speed *speed,
				    क्रमागत ntb_width *width)
अणु
	काष्ठा चयनtec_ntb *sndev = ntb_sndev(ntb);

	अगर (speed)
		*speed = sndev->link_speed;
	अगर (width)
		*width = sndev->link_width;

	वापस sndev->link_is_up;
पूर्ण

अटल पूर्णांक चयनtec_ntb_link_enable(काष्ठा ntb_dev *ntb,
				     क्रमागत ntb_speed max_speed,
				     क्रमागत ntb_width max_width)
अणु
	काष्ठा चयनtec_ntb *sndev = ntb_sndev(ntb);

	dev_dbg(&sndev->stdev->dev, "enabling link\n");

	sndev->self_shared->link_sta = 1;
	चयनtec_ntb_send_msg(sndev, LINK_MESSAGE, MSG_LINK_UP);

	चयनtec_ntb_link_status_update(sndev);

	वापस 0;
पूर्ण

अटल पूर्णांक चयनtec_ntb_link_disable(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा चयनtec_ntb *sndev = ntb_sndev(ntb);

	dev_dbg(&sndev->stdev->dev, "disabling link\n");

	sndev->self_shared->link_sta = 0;
	चयनtec_ntb_send_msg(sndev, LINK_MESSAGE, MSG_LINK_DOWN);

	चयनtec_ntb_link_status_update(sndev);

	वापस 0;
पूर्ण

अटल u64 चयनtec_ntb_db_valid_mask(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा चयनtec_ntb *sndev = ntb_sndev(ntb);

	वापस sndev->db_valid_mask;
पूर्ण

अटल पूर्णांक चयनtec_ntb_db_vector_count(काष्ठा ntb_dev *ntb)
अणु
	वापस 1;
पूर्ण

अटल u64 चयनtec_ntb_db_vector_mask(काष्ठा ntb_dev *ntb, पूर्णांक db_vector)
अणु
	काष्ठा चयनtec_ntb *sndev = ntb_sndev(ntb);

	अगर (db_vector < 0 || db_vector > 1)
		वापस 0;

	वापस sndev->db_valid_mask;
पूर्ण

अटल u64 चयनtec_ntb_db_पढ़ो(काष्ठा ntb_dev *ntb)
अणु
	u64 ret;
	काष्ठा चयनtec_ntb *sndev = ntb_sndev(ntb);

	ret = ioपढ़ो64(&sndev->mmio_self_dbmsg->idb) >> sndev->db_shअगरt;

	वापस ret & sndev->db_valid_mask;
पूर्ण

अटल पूर्णांक चयनtec_ntb_db_clear(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	काष्ठा चयनtec_ntb *sndev = ntb_sndev(ntb);

	ioग_लिखो64(db_bits << sndev->db_shअगरt, &sndev->mmio_self_dbmsg->idb);

	वापस 0;
पूर्ण

अटल पूर्णांक चयनtec_ntb_db_set_mask(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	अचिन्हित दीर्घ irqflags;
	काष्ठा चयनtec_ntb *sndev = ntb_sndev(ntb);

	अगर (db_bits & ~sndev->db_valid_mask)
		वापस -EINVAL;

	spin_lock_irqsave(&sndev->db_mask_lock, irqflags);

	sndev->db_mask |= db_bits << sndev->db_shअगरt;
	ioग_लिखो64(~sndev->db_mask, &sndev->mmio_self_dbmsg->idb_mask);

	spin_unlock_irqrestore(&sndev->db_mask_lock, irqflags);

	वापस 0;
पूर्ण

अटल पूर्णांक चयनtec_ntb_db_clear_mask(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	अचिन्हित दीर्घ irqflags;
	काष्ठा चयनtec_ntb *sndev = ntb_sndev(ntb);

	अगर (db_bits & ~sndev->db_valid_mask)
		वापस -EINVAL;

	spin_lock_irqsave(&sndev->db_mask_lock, irqflags);

	sndev->db_mask &= ~(db_bits << sndev->db_shअगरt);
	ioग_लिखो64(~sndev->db_mask, &sndev->mmio_self_dbmsg->idb_mask);

	spin_unlock_irqrestore(&sndev->db_mask_lock, irqflags);

	वापस 0;
पूर्ण

अटल u64 चयनtec_ntb_db_पढ़ो_mask(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा चयनtec_ntb *sndev = ntb_sndev(ntb);

	वापस (sndev->db_mask >> sndev->db_shअगरt) & sndev->db_valid_mask;
पूर्ण

अटल पूर्णांक चयनtec_ntb_peer_db_addr(काष्ठा ntb_dev *ntb,
				      phys_addr_t *db_addr,
				      resource_माप_प्रकार *db_size,
				      u64 *db_data,
				      पूर्णांक db_bit)
अणु
	काष्ठा चयनtec_ntb *sndev = ntb_sndev(ntb);
	अचिन्हित दीर्घ offset;

	अगर (unlikely(db_bit >= BITS_PER_LONG_LONG))
		वापस -EINVAL;

	offset = (अचिन्हित दीर्घ)sndev->mmio_peer_dbmsg->odb -
		(अचिन्हित दीर्घ)sndev->stdev->mmio;

	offset += sndev->db_shअगरt / 8;

	अगर (db_addr)
		*db_addr = pci_resource_start(ntb->pdev, 0) + offset;
	अगर (db_size)
		*db_size = माप(u32);
	अगर (db_data)
		*db_data = BIT_ULL(db_bit) << sndev->db_peer_shअगरt;

	वापस 0;
पूर्ण

अटल पूर्णांक चयनtec_ntb_peer_db_set(काष्ठा ntb_dev *ntb, u64 db_bits)
अणु
	काष्ठा चयनtec_ntb *sndev = ntb_sndev(ntb);

	ioग_लिखो64(db_bits << sndev->db_peer_shअगरt,
		  &sndev->mmio_peer_dbmsg->odb);

	वापस 0;
पूर्ण

अटल पूर्णांक चयनtec_ntb_spad_count(काष्ठा ntb_dev *ntb)
अणु
	काष्ठा चयनtec_ntb *sndev = ntb_sndev(ntb);

	वापस ARRAY_SIZE(sndev->self_shared->spad);
पूर्ण

अटल u32 चयनtec_ntb_spad_पढ़ो(काष्ठा ntb_dev *ntb, पूर्णांक idx)
अणु
	काष्ठा चयनtec_ntb *sndev = ntb_sndev(ntb);

	अगर (idx < 0 || idx >= ARRAY_SIZE(sndev->self_shared->spad))
		वापस 0;

	अगर (!sndev->self_shared)
		वापस 0;

	वापस sndev->self_shared->spad[idx];
पूर्ण

अटल पूर्णांक चयनtec_ntb_spad_ग_लिखो(काष्ठा ntb_dev *ntb, पूर्णांक idx, u32 val)
अणु
	काष्ठा चयनtec_ntb *sndev = ntb_sndev(ntb);

	अगर (idx < 0 || idx >= ARRAY_SIZE(sndev->self_shared->spad))
		वापस -EINVAL;

	अगर (!sndev->self_shared)
		वापस -EIO;

	sndev->self_shared->spad[idx] = val;

	वापस 0;
पूर्ण

अटल u32 चयनtec_ntb_peer_spad_पढ़ो(काष्ठा ntb_dev *ntb, पूर्णांक pidx,
					पूर्णांक sidx)
अणु
	काष्ठा चयनtec_ntb *sndev = ntb_sndev(ntb);

	अगर (pidx != NTB_DEF_PEER_IDX)
		वापस -EINVAL;

	अगर (sidx < 0 || sidx >= ARRAY_SIZE(sndev->peer_shared->spad))
		वापस 0;

	अगर (!sndev->peer_shared)
		वापस 0;

	वापस ioपढ़ो32(&sndev->peer_shared->spad[sidx]);
पूर्ण

अटल पूर्णांक चयनtec_ntb_peer_spad_ग_लिखो(काष्ठा ntb_dev *ntb, पूर्णांक pidx,
					 पूर्णांक sidx, u32 val)
अणु
	काष्ठा चयनtec_ntb *sndev = ntb_sndev(ntb);

	अगर (pidx != NTB_DEF_PEER_IDX)
		वापस -EINVAL;

	अगर (sidx < 0 || sidx >= ARRAY_SIZE(sndev->peer_shared->spad))
		वापस -EINVAL;

	अगर (!sndev->peer_shared)
		वापस -EIO;

	ioग_लिखो32(val, &sndev->peer_shared->spad[sidx]);

	वापस 0;
पूर्ण

अटल पूर्णांक चयनtec_ntb_peer_spad_addr(काष्ठा ntb_dev *ntb, पूर्णांक pidx,
					पूर्णांक sidx, phys_addr_t *spad_addr)
अणु
	काष्ठा चयनtec_ntb *sndev = ntb_sndev(ntb);
	अचिन्हित दीर्घ offset;

	अगर (pidx != NTB_DEF_PEER_IDX)
		वापस -EINVAL;

	offset = (अचिन्हित दीर्घ)&sndev->peer_shared->spad[sidx] -
		(अचिन्हित दीर्घ)sndev->stdev->mmio;

	अगर (spad_addr)
		*spad_addr = pci_resource_start(ntb->pdev, 0) + offset;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ntb_dev_ops चयनtec_ntb_ops = अणु
	.mw_count		= चयनtec_ntb_mw_count,
	.mw_get_align		= चयनtec_ntb_mw_get_align,
	.mw_set_trans		= चयनtec_ntb_mw_set_trans,
	.peer_mw_count		= चयनtec_ntb_peer_mw_count,
	.peer_mw_get_addr	= चयनtec_ntb_peer_mw_get_addr,
	.link_is_up		= चयनtec_ntb_link_is_up,
	.link_enable		= चयनtec_ntb_link_enable,
	.link_disable		= चयनtec_ntb_link_disable,
	.db_valid_mask		= चयनtec_ntb_db_valid_mask,
	.db_vector_count	= चयनtec_ntb_db_vector_count,
	.db_vector_mask		= चयनtec_ntb_db_vector_mask,
	.db_पढ़ो		= चयनtec_ntb_db_पढ़ो,
	.db_clear		= चयनtec_ntb_db_clear,
	.db_set_mask		= चयनtec_ntb_db_set_mask,
	.db_clear_mask		= चयनtec_ntb_db_clear_mask,
	.db_पढ़ो_mask		= चयनtec_ntb_db_पढ़ो_mask,
	.peer_db_addr		= चयनtec_ntb_peer_db_addr,
	.peer_db_set		= चयनtec_ntb_peer_db_set,
	.spad_count		= चयनtec_ntb_spad_count,
	.spad_पढ़ो		= चयनtec_ntb_spad_पढ़ो,
	.spad_ग_लिखो		= चयनtec_ntb_spad_ग_लिखो,
	.peer_spad_पढ़ो		= चयनtec_ntb_peer_spad_पढ़ो,
	.peer_spad_ग_लिखो	= चयनtec_ntb_peer_spad_ग_लिखो,
	.peer_spad_addr		= चयनtec_ntb_peer_spad_addr,
पूर्ण;

अटल पूर्णांक चयनtec_ntb_init_sndev(काष्ठा चयनtec_ntb *sndev)
अणु
	u64 tpart_vec;
	पूर्णांक self;
	u64 part_map;
	पूर्णांक bit;

	sndev->ntb.pdev = sndev->stdev->pdev;
	sndev->ntb.topo = NTB_TOPO_SWITCH;
	sndev->ntb.ops = &चयनtec_ntb_ops;

	INIT_WORK(&sndev->check_link_status_work, check_link_status_work);
	sndev->link_क्रमce_करोwn = false;

	sndev->self_partition = sndev->stdev->partition;

	sndev->mmio_ntb = sndev->stdev->mmio_ntb;

	self = sndev->self_partition;
	tpart_vec = ioपढ़ो32(&sndev->mmio_ntb->ntp_info[self].target_part_high);
	tpart_vec <<= 32;
	tpart_vec |= ioपढ़ो32(&sndev->mmio_ntb->ntp_info[self].target_part_low);

	part_map = ioपढ़ो64(&sndev->mmio_ntb->ep_map);
	part_map &= ~(1 << sndev->self_partition);

	अगर (!ffs(tpart_vec)) अणु
		अगर (sndev->stdev->partition_count != 2) अणु
			dev_err(&sndev->stdev->dev,
				"ntb target partition not defined\n");
			वापस -ENODEV;
		पूर्ण

		bit = ffs(part_map);
		अगर (!bit) अणु
			dev_err(&sndev->stdev->dev,
				"peer partition is not NT partition\n");
			वापस -ENODEV;
		पूर्ण

		sndev->peer_partition = bit - 1;
	पूर्ण अन्यथा अणु
		अगर (ffs(tpart_vec) != fls(tpart_vec)) अणु
			dev_err(&sndev->stdev->dev,
				"ntb driver only supports 1 pair of 1-1 ntb mapping\n");
			वापस -ENODEV;
		पूर्ण

		sndev->peer_partition = ffs(tpart_vec) - 1;
		अगर (!(part_map & (1ULL << sndev->peer_partition))) अणु
			dev_err(&sndev->stdev->dev,
				"ntb target partition is not NT partition\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	dev_dbg(&sndev->stdev->dev, "Partition ID %d of %d\n",
		sndev->self_partition, sndev->stdev->partition_count);

	sndev->mmio_ctrl = (व्योम * __iomem)sndev->mmio_ntb +
		SWITCHTEC_NTB_REG_CTRL_OFFSET;
	sndev->mmio_dbmsg = (व्योम * __iomem)sndev->mmio_ntb +
		SWITCHTEC_NTB_REG_DBMSG_OFFSET;

	sndev->mmio_self_ctrl = &sndev->mmio_ctrl[sndev->self_partition];
	sndev->mmio_peer_ctrl = &sndev->mmio_ctrl[sndev->peer_partition];
	sndev->mmio_self_dbmsg = &sndev->mmio_dbmsg[sndev->self_partition];
	sndev->mmio_peer_dbmsg = sndev->mmio_self_dbmsg;

	वापस 0;
पूर्ण

अटल पूर्णांक config_rsvd_lut_win(काष्ठा चयनtec_ntb *sndev,
			       काष्ठा ntb_ctrl_regs __iomem *ctl,
			       पूर्णांक lut_idx, पूर्णांक partition, u64 addr)
अणु
	पूर्णांक peer_bar = sndev->peer_direct_mw_to_bar[0];
	u32 ctl_val;
	पूर्णांक rc;

	rc = चयनtec_ntb_part_op(sndev, ctl, NTB_CTRL_PART_OP_LOCK,
				   NTB_CTRL_PART_STATUS_LOCKED);
	अगर (rc)
		वापस rc;

	ctl_val = ioपढ़ो32(&ctl->bar_entry[peer_bar].ctl);
	ctl_val &= 0xFF;
	ctl_val |= NTB_CTRL_BAR_LUT_WIN_EN;
	ctl_val |= ilog2(LUT_SIZE) << 8;
	ctl_val |= (sndev->nr_lut_mw - 1) << 14;
	ioग_लिखो32(ctl_val, &ctl->bar_entry[peer_bar].ctl);

	ioग_लिखो64((NTB_CTRL_LUT_EN | (partition << 1) | addr),
		  &ctl->lut_entry[lut_idx]);

	rc = चयनtec_ntb_part_op(sndev, ctl, NTB_CTRL_PART_OP_CFG,
				   NTB_CTRL_PART_STATUS_NORMAL);
	अगर (rc) अणु
		u32 bar_error, lut_error;

		bar_error = ioपढ़ो32(&ctl->bar_error);
		lut_error = ioपढ़ो32(&ctl->lut_error);
		dev_err(&sndev->stdev->dev,
			"Error setting up reserved lut window: %08x / %08x\n",
			bar_error, lut_error);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक config_req_id_table(काष्ठा चयनtec_ntb *sndev,
			       काष्ठा ntb_ctrl_regs __iomem *mmio_ctrl,
			       पूर्णांक *req_ids, पूर्णांक count)
अणु
	पूर्णांक i, rc = 0;
	u32 error;
	u32 proxy_id;

	अगर (ioपढ़ो32(&mmio_ctrl->req_id_table_size) < count) अणु
		dev_err(&sndev->stdev->dev,
			"Not enough requester IDs available.\n");
		वापस -EFAULT;
	पूर्ण

	rc = चयनtec_ntb_part_op(sndev, mmio_ctrl,
				   NTB_CTRL_PART_OP_LOCK,
				   NTB_CTRL_PART_STATUS_LOCKED);
	अगर (rc)
		वापस rc;

	ioग_लिखो32(NTB_PART_CTRL_ID_PROT_DIS,
		  &mmio_ctrl->partition_ctrl);

	क्रम (i = 0; i < count; i++) अणु
		ioग_लिखो32(req_ids[i] << 16 | NTB_CTRL_REQ_ID_EN,
			  &mmio_ctrl->req_id_table[i]);

		proxy_id = ioपढ़ो32(&mmio_ctrl->req_id_table[i]);
		dev_dbg(&sndev->stdev->dev,
			"Requester ID %02X:%02X.%X -> BB:%02X.%X\n",
			req_ids[i] >> 8, (req_ids[i] >> 3) & 0x1F,
			req_ids[i] & 0x7, (proxy_id >> 4) & 0x1F,
			(proxy_id >> 1) & 0x7);
	पूर्ण

	rc = चयनtec_ntb_part_op(sndev, mmio_ctrl,
				   NTB_CTRL_PART_OP_CFG,
				   NTB_CTRL_PART_STATUS_NORMAL);

	अगर (rc == -EIO) अणु
		error = ioपढ़ो32(&mmio_ctrl->req_id_error);
		dev_err(&sndev->stdev->dev,
			"Error setting up the requester ID table: %08x\n",
			error);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक crosslink_setup_mws(काष्ठा चयनtec_ntb *sndev, पूर्णांक ntb_lut_idx,
			       u64 *mw_addrs, पूर्णांक mw_count)
अणु
	पूर्णांक rc, i;
	काष्ठा ntb_ctrl_regs __iomem *ctl = sndev->mmio_self_ctrl;
	u64 addr;
	माप_प्रकार size, offset;
	पूर्णांक bar;
	पूर्णांक xlate_pos;
	u32 ctl_val;

	rc = चयनtec_ntb_part_op(sndev, ctl, NTB_CTRL_PART_OP_LOCK,
				   NTB_CTRL_PART_STATUS_LOCKED);
	अगर (rc)
		वापस rc;

	क्रम (i = 0; i < sndev->nr_lut_mw; i++) अणु
		अगर (i == ntb_lut_idx)
			जारी;

		addr = mw_addrs[0] + LUT_SIZE * i;

		ioग_लिखो64((NTB_CTRL_LUT_EN | (sndev->peer_partition << 1) |
			   addr),
			  &ctl->lut_entry[i]);
	पूर्ण

	sndev->nr_direct_mw = min_t(पूर्णांक, sndev->nr_direct_mw, mw_count);

	क्रम (i = 0; i < sndev->nr_direct_mw; i++) अणु
		bar = sndev->direct_mw_to_bar[i];
		offset = (i == 0) ? LUT_SIZE * sndev->nr_lut_mw : 0;
		addr = mw_addrs[i] + offset;
		size = pci_resource_len(sndev->ntb.pdev, bar) - offset;
		xlate_pos = ilog2(size);

		अगर (offset && size > offset)
			size = offset;

		ctl_val = ioपढ़ो32(&ctl->bar_entry[bar].ctl);
		ctl_val |= NTB_CTRL_BAR_सूची_WIN_EN;

		ioग_लिखो32(ctl_val, &ctl->bar_entry[bar].ctl);
		ioग_लिखो32(xlate_pos | (lower_32_bits(size) & 0xFFFFF000),
			  &ctl->bar_entry[bar].win_size);
		ioग_लिखो32(upper_32_bits(size), &ctl->bar_ext_entry[bar].win_size);
		ioग_लिखो64(sndev->peer_partition | addr,
			  &ctl->bar_entry[bar].xlate_addr);
	पूर्ण

	rc = चयनtec_ntb_part_op(sndev, ctl, NTB_CTRL_PART_OP_CFG,
				   NTB_CTRL_PART_STATUS_NORMAL);
	अगर (rc) अणु
		u32 bar_error, lut_error;

		bar_error = ioपढ़ो32(&ctl->bar_error);
		lut_error = ioपढ़ो32(&ctl->lut_error);
		dev_err(&sndev->stdev->dev,
			"Error setting up cross link windows: %08x / %08x\n",
			bar_error, lut_error);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक crosslink_setup_req_ids(काष्ठा चयनtec_ntb *sndev,
	काष्ठा ntb_ctrl_regs __iomem *mmio_ctrl)
अणु
	पूर्णांक req_ids[16];
	पूर्णांक i;
	u32 proxy_id;

	क्रम (i = 0; i < ARRAY_SIZE(req_ids); i++) अणु
		proxy_id = ioपढ़ो32(&sndev->mmio_self_ctrl->req_id_table[i]);

		अगर (!(proxy_id & NTB_CTRL_REQ_ID_EN))
			अवरोध;

		req_ids[i] = ((proxy_id >> 1) & 0xFF);
	पूर्ण

	वापस config_req_id_table(sndev, mmio_ctrl, req_ids, i);
पूर्ण

/*
 * In crosslink configuration there is a भव partition in the
 * middle of the two चयनes. The BARs in this partition have to be
 * क्रमागतerated and asचिन्हित addresses.
 */
अटल पूर्णांक crosslink_क्रमागत_partition(काष्ठा चयनtec_ntb *sndev,
				    u64 *bar_addrs)
अणु
	काष्ठा part_cfg_regs __iomem *part_cfg =
		&sndev->stdev->mmio_part_cfg_all[sndev->peer_partition];
	u32 pff = ioपढ़ो32(&part_cfg->vep_pff_inst_id);
	काष्ठा pff_csr_regs __iomem *mmio_pff =
		&sndev->stdev->mmio_pff_csr[pff];
	स्थिर u64 bar_space = 0x1000000000LL;
	u64 bar_addr;
	पूर्णांक bar_cnt = 0;
	पूर्णांक i;

	ioग_लिखो16(0x6, &mmio_pff->pcicmd);

	क्रम (i = 0; i < ARRAY_SIZE(mmio_pff->pci_bar64); i++) अणु
		ioग_लिखो64(bar_space * i, &mmio_pff->pci_bar64[i]);
		bar_addr = ioपढ़ो64(&mmio_pff->pci_bar64[i]);
		bar_addr &= ~0xf;

		dev_dbg(&sndev->stdev->dev,
			"Crosslink BAR%d addr: %llx\n",
			i*2, bar_addr);

		अगर (bar_addr != bar_space * i)
			जारी;

		bar_addrs[bar_cnt++] = bar_addr;
	पूर्ण

	वापस bar_cnt;
पूर्ण

अटल पूर्णांक चयनtec_ntb_init_crosslink(काष्ठा चयनtec_ntb *sndev)
अणु
	पूर्णांक rc;
	पूर्णांक bar = sndev->direct_mw_to_bar[0];
	स्थिर पूर्णांक ntb_lut_idx = 1;
	u64 bar_addrs[6];
	u64 addr;
	पूर्णांक offset;
	पूर्णांक bar_cnt;

	अगर (!crosslink_is_enabled(sndev))
		वापस 0;

	dev_info(&sndev->stdev->dev, "Using crosslink configuration\n");
	sndev->ntb.topo = NTB_TOPO_CROSSLINK;

	bar_cnt = crosslink_क्रमागत_partition(sndev, bar_addrs);
	अगर (bar_cnt < sndev->nr_direct_mw + 1) अणु
		dev_err(&sndev->stdev->dev,
			"Error enumerating crosslink partition\n");
		वापस -EINVAL;
	पूर्ण

	addr = (bar_addrs[0] + SWITCHTEC_GAS_NTB_OFFSET +
		SWITCHTEC_NTB_REG_DBMSG_OFFSET +
		माप(काष्ठा ntb_dbmsg_regs) * sndev->peer_partition);

	offset = addr & (LUT_SIZE - 1);
	addr -= offset;

	rc = config_rsvd_lut_win(sndev, sndev->mmio_self_ctrl, ntb_lut_idx,
				 sndev->peer_partition, addr);
	अगर (rc)
		वापस rc;

	rc = crosslink_setup_mws(sndev, ntb_lut_idx, &bar_addrs[1],
				 bar_cnt - 1);
	अगर (rc)
		वापस rc;

	rc = crosslink_setup_req_ids(sndev, sndev->mmio_peer_ctrl);
	अगर (rc)
		वापस rc;

	sndev->mmio_xlink_win = pci_iomap_range(sndev->stdev->pdev, bar,
						LUT_SIZE, LUT_SIZE);
	अगर (!sndev->mmio_xlink_win) अणु
		rc = -ENOMEM;
		वापस rc;
	पूर्ण

	sndev->mmio_peer_dbmsg = sndev->mmio_xlink_win + offset;
	sndev->nr_rsvd_luts++;

	crosslink_init_dbmsgs(sndev);

	वापस 0;
पूर्ण

अटल व्योम चयनtec_ntb_deinit_crosslink(काष्ठा चयनtec_ntb *sndev)
अणु
	अगर (sndev->mmio_xlink_win)
		pci_iounmap(sndev->stdev->pdev, sndev->mmio_xlink_win);
पूर्ण

अटल पूर्णांक map_bars(पूर्णांक *map, काष्ठा ntb_ctrl_regs __iomem *ctrl)
अणु
	पूर्णांक i;
	पूर्णांक cnt = 0;

	क्रम (i = 0; i < ARRAY_SIZE(ctrl->bar_entry); i++) अणु
		u32 r = ioपढ़ो32(&ctrl->bar_entry[i].ctl);

		अगर (r & NTB_CTRL_BAR_VALID)
			map[cnt++] = i;
	पूर्ण

	वापस cnt;
पूर्ण

अटल व्योम चयनtec_ntb_init_mw(काष्ठा चयनtec_ntb *sndev)
अणु
	sndev->nr_direct_mw = map_bars(sndev->direct_mw_to_bar,
				       sndev->mmio_self_ctrl);

	sndev->nr_lut_mw = ioपढ़ो16(&sndev->mmio_self_ctrl->lut_table_entries);
	sndev->nr_lut_mw = roundकरोwn_घात_of_two(sndev->nr_lut_mw);

	dev_dbg(&sndev->stdev->dev, "MWs: %d direct, %d lut\n",
		sndev->nr_direct_mw, sndev->nr_lut_mw);

	sndev->peer_nr_direct_mw = map_bars(sndev->peer_direct_mw_to_bar,
					    sndev->mmio_peer_ctrl);

	sndev->peer_nr_lut_mw =
		ioपढ़ो16(&sndev->mmio_peer_ctrl->lut_table_entries);
	sndev->peer_nr_lut_mw = roundकरोwn_घात_of_two(sndev->peer_nr_lut_mw);

	dev_dbg(&sndev->stdev->dev, "Peer MWs: %d direct, %d lut\n",
		sndev->peer_nr_direct_mw, sndev->peer_nr_lut_mw);

पूर्ण

/*
 * There are 64 करोorbells in the चयन hardware but this is
 * shared among all partitions. So we must split them in half
 * (32 क्रम each partition). However, the message पूर्णांकerrupts are
 * also shared with the top 4 करोorbells so we just limit this to
 * 28 करोorbells per partition.
 *
 * In crosslink mode, each side has it's own dbmsg रेजिस्टर so
 * they can each use all 60 of the available करोorbells.
 */
अटल व्योम चयनtec_ntb_init_db(काष्ठा चयनtec_ntb *sndev)
अणु
	sndev->db_mask = 0x0FFFFFFFFFFFFFFFULL;

	अगर (sndev->mmio_peer_dbmsg != sndev->mmio_self_dbmsg) अणु
		sndev->db_shअगरt = 0;
		sndev->db_peer_shअगरt = 0;
		sndev->db_valid_mask = sndev->db_mask;
	पूर्ण अन्यथा अगर (sndev->self_partition < sndev->peer_partition) अणु
		sndev->db_shअगरt = 0;
		sndev->db_peer_shअगरt = 32;
		sndev->db_valid_mask = 0x0FFFFFFF;
	पूर्ण अन्यथा अणु
		sndev->db_shअगरt = 32;
		sndev->db_peer_shअगरt = 0;
		sndev->db_valid_mask = 0x0FFFFFFF;
	पूर्ण

	ioग_लिखो64(~sndev->db_mask, &sndev->mmio_self_dbmsg->idb_mask);
	ioग_लिखो64(sndev->db_valid_mask << sndev->db_peer_shअगरt,
		  &sndev->mmio_peer_dbmsg->odb_mask);

	dev_dbg(&sndev->stdev->dev, "dbs: shift %d/%d, mask %016llx\n",
		sndev->db_shअगरt, sndev->db_peer_shअगरt, sndev->db_valid_mask);
पूर्ण

अटल व्योम चयनtec_ntb_init_msgs(काष्ठा चयनtec_ntb *sndev)
अणु
	पूर्णांक i;
	u32 msg_map = 0;

	क्रम (i = 0; i < ARRAY_SIZE(sndev->mmio_self_dbmsg->imsg); i++) अणु
		पूर्णांक m = i | sndev->peer_partition << 2;

		msg_map |= m << i * 8;
	पूर्ण

	ioग_लिखो32(msg_map, &sndev->mmio_self_dbmsg->msg_map);

	क्रम (i = 0; i < ARRAY_SIZE(sndev->mmio_self_dbmsg->imsg); i++)
		ioग_लिखो64(NTB_DBMSG_IMSG_STATUS | NTB_DBMSG_IMSG_MASK,
			  &sndev->mmio_self_dbmsg->imsg[i]);
पूर्ण

अटल पूर्णांक
चयनtec_ntb_init_req_id_table(काष्ठा चयनtec_ntb *sndev)
अणु
	पूर्णांक req_ids[2];

	/*
	 * Root Complex Requester ID (which is 0:00.0)
	 */
	req_ids[0] = 0;

	/*
	 * Host Bridge Requester ID (as पढ़ो from the mmap address)
	 */
	req_ids[1] = ioपढ़ो16(&sndev->mmio_ntb->requester_id);

	वापस config_req_id_table(sndev, sndev->mmio_self_ctrl, req_ids,
				   ARRAY_SIZE(req_ids));
पूर्ण

अटल व्योम चयनtec_ntb_init_shared(काष्ठा चयनtec_ntb *sndev)
अणु
	पूर्णांक i;

	स_रखो(sndev->self_shared, 0, LUT_SIZE);
	sndev->self_shared->magic = SWITCHTEC_NTB_MAGIC;
	sndev->self_shared->partition_id = sndev->stdev->partition;

	क्रम (i = 0; i < sndev->nr_direct_mw; i++) अणु
		पूर्णांक bar = sndev->direct_mw_to_bar[i];
		resource_माप_प्रकार sz = pci_resource_len(sndev->stdev->pdev, bar);

		अगर (i == 0)
			sz = min_t(resource_माप_प्रकार, sz,
				   LUT_SIZE * sndev->nr_lut_mw);

		sndev->self_shared->mw_sizes[i] = sz;
	पूर्ण

	क्रम (i = 0; i < sndev->nr_lut_mw; i++) अणु
		पूर्णांक idx = sndev->nr_direct_mw + i;

		sndev->self_shared->mw_sizes[idx] = LUT_SIZE;
	पूर्ण
पूर्ण

अटल पूर्णांक चयनtec_ntb_init_shared_mw(काष्ठा चयनtec_ntb *sndev)
अणु
	पूर्णांक self_bar = sndev->direct_mw_to_bar[0];
	पूर्णांक rc;

	sndev->nr_rsvd_luts++;
	sndev->self_shared = dma_alloc_coherent(&sndev->stdev->pdev->dev,
						LUT_SIZE,
						&sndev->self_shared_dma,
						GFP_KERNEL);
	अगर (!sndev->self_shared) अणु
		dev_err(&sndev->stdev->dev,
			"unable to allocate memory for shared mw\n");
		वापस -ENOMEM;
	पूर्ण

	चयनtec_ntb_init_shared(sndev);

	rc = config_rsvd_lut_win(sndev, sndev->mmio_peer_ctrl, 0,
				 sndev->self_partition,
				 sndev->self_shared_dma);
	अगर (rc)
		जाओ unalloc_and_निकास;

	sndev->peer_shared = pci_iomap(sndev->stdev->pdev, self_bar, LUT_SIZE);
	अगर (!sndev->peer_shared) अणु
		rc = -ENOMEM;
		जाओ unalloc_and_निकास;
	पूर्ण

	dev_dbg(&sndev->stdev->dev, "Shared MW Ready\n");
	वापस 0;

unalloc_and_निकास:
	dma_मुक्त_coherent(&sndev->stdev->pdev->dev, LUT_SIZE,
			  sndev->self_shared, sndev->self_shared_dma);

	वापस rc;
पूर्ण

अटल व्योम चयनtec_ntb_deinit_shared_mw(काष्ठा चयनtec_ntb *sndev)
अणु
	अगर (sndev->peer_shared)
		pci_iounmap(sndev->stdev->pdev, sndev->peer_shared);

	अगर (sndev->self_shared)
		dma_मुक्त_coherent(&sndev->stdev->pdev->dev, LUT_SIZE,
				  sndev->self_shared,
				  sndev->self_shared_dma);
	sndev->nr_rsvd_luts--;
पूर्ण

अटल irqवापस_t चयनtec_ntb_करोorbell_isr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा चयनtec_ntb *sndev = dev;

	dev_dbg(&sndev->stdev->dev, "doorbell\n");

	ntb_db_event(&sndev->ntb, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t चयनtec_ntb_message_isr(पूर्णांक irq, व्योम *dev)
अणु
	पूर्णांक i;
	काष्ठा चयनtec_ntb *sndev = dev;

	क्रम (i = 0; i < ARRAY_SIZE(sndev->mmio_self_dbmsg->imsg); i++) अणु
		u64 msg = ioपढ़ो64(&sndev->mmio_self_dbmsg->imsg[i]);

		अगर (msg & NTB_DBMSG_IMSG_STATUS) अणु
			dev_dbg(&sndev->stdev->dev, "message: %d %08x\n",
				i, (u32)msg);
			ioग_लिखो8(1, &sndev->mmio_self_dbmsg->imsg[i].status);

			अगर (i == LINK_MESSAGE)
				चयनtec_ntb_check_link(sndev, msg);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक चयनtec_ntb_init_db_msg_irq(काष्ठा चयनtec_ntb *sndev)
अणु
	पूर्णांक i;
	पूर्णांक rc;
	पूर्णांक करोorbell_irq = 0;
	पूर्णांक message_irq = 0;
	पूर्णांक event_irq;
	पूर्णांक idb_vecs = माप(sndev->mmio_self_dbmsg->idb_vec_map);

	event_irq = ioपढ़ो32(&sndev->stdev->mmio_part_cfg->vep_vector_number);

	जबतक (करोorbell_irq == event_irq)
		करोorbell_irq++;
	जबतक (message_irq == करोorbell_irq ||
	       message_irq == event_irq)
		message_irq++;

	dev_dbg(&sndev->stdev->dev, "irqs - event: %d, db: %d, msgs: %d\n",
		event_irq, करोorbell_irq, message_irq);

	क्रम (i = 0; i < idb_vecs - 4; i++)
		ioग_लिखो8(करोorbell_irq,
			 &sndev->mmio_self_dbmsg->idb_vec_map[i]);

	क्रम (; i < idb_vecs; i++)
		ioग_लिखो8(message_irq,
			 &sndev->mmio_self_dbmsg->idb_vec_map[i]);

	sndev->करोorbell_irq = pci_irq_vector(sndev->stdev->pdev, करोorbell_irq);
	sndev->message_irq = pci_irq_vector(sndev->stdev->pdev, message_irq);

	rc = request_irq(sndev->करोorbell_irq,
			 चयनtec_ntb_करोorbell_isr, 0,
			 "switchtec_ntb_doorbell", sndev);
	अगर (rc)
		वापस rc;

	rc = request_irq(sndev->message_irq,
			 चयनtec_ntb_message_isr, 0,
			 "switchtec_ntb_message", sndev);
	अगर (rc) अणु
		मुक्त_irq(sndev->करोorbell_irq, sndev);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम चयनtec_ntb_deinit_db_msg_irq(काष्ठा चयनtec_ntb *sndev)
अणु
	मुक्त_irq(sndev->करोorbell_irq, sndev);
	मुक्त_irq(sndev->message_irq, sndev);
पूर्ण

अटल पूर्णांक चयनtec_ntb_reinit_peer(काष्ठा चयनtec_ntb *sndev)
अणु
	पूर्णांक rc;

	अगर (crosslink_is_enabled(sndev))
		वापस 0;

	dev_info(&sndev->stdev->dev, "reinitialize shared memory window\n");
	rc = config_rsvd_lut_win(sndev, sndev->mmio_peer_ctrl, 0,
				 sndev->self_partition,
				 sndev->self_shared_dma);
	वापस rc;
पूर्ण

अटल पूर्णांक चयनtec_ntb_add(काष्ठा device *dev,
			     काष्ठा class_पूर्णांकerface *class_पूर्णांकf)
अणु
	काष्ठा चयनtec_dev *stdev = to_stdev(dev);
	काष्ठा चयनtec_ntb *sndev;
	पूर्णांक rc;

	stdev->sndev = शून्य;

	अगर (stdev->pdev->class != (PCI_CLASS_BRIDGE_OTHER << 8))
		वापस -ENODEV;

	sndev = kzalloc_node(माप(*sndev), GFP_KERNEL, dev_to_node(dev));
	अगर (!sndev)
		वापस -ENOMEM;

	sndev->stdev = stdev;
	rc = चयनtec_ntb_init_sndev(sndev);
	अगर (rc)
		जाओ मुक्त_and_निकास;

	चयनtec_ntb_init_mw(sndev);

	rc = चयनtec_ntb_init_req_id_table(sndev);
	अगर (rc)
		जाओ मुक्त_and_निकास;

	rc = चयनtec_ntb_init_crosslink(sndev);
	अगर (rc)
		जाओ मुक्त_and_निकास;

	चयनtec_ntb_init_db(sndev);
	चयनtec_ntb_init_msgs(sndev);

	rc = चयनtec_ntb_init_shared_mw(sndev);
	अगर (rc)
		जाओ deinit_crosslink;

	rc = चयनtec_ntb_init_db_msg_irq(sndev);
	अगर (rc)
		जाओ deinit_shared_and_निकास;

	/*
	 * If this host crashed, the other host may think the link is
	 * still up. Tell them to क्रमce it करोwn (it will go back up
	 * once we रेजिस्टर the ntb device).
	 */
	चयनtec_ntb_send_msg(sndev, LINK_MESSAGE, MSG_LINK_FORCE_DOWN);

	rc = ntb_रेजिस्टर_device(&sndev->ntb);
	अगर (rc)
		जाओ deinit_and_निकास;

	stdev->sndev = sndev;
	stdev->link_notअगरier = चयनtec_ntb_link_notअगरication;
	dev_info(dev, "NTB device registered\n");

	वापस 0;

deinit_and_निकास:
	चयनtec_ntb_deinit_db_msg_irq(sndev);
deinit_shared_and_निकास:
	चयनtec_ntb_deinit_shared_mw(sndev);
deinit_crosslink:
	चयनtec_ntb_deinit_crosslink(sndev);
मुक्त_and_निकास:
	kमुक्त(sndev);
	dev_err(dev, "failed to register ntb device: %d\n", rc);
	वापस rc;
पूर्ण

अटल व्योम चयनtec_ntb_हटाओ(काष्ठा device *dev,
				 काष्ठा class_पूर्णांकerface *class_पूर्णांकf)
अणु
	काष्ठा चयनtec_dev *stdev = to_stdev(dev);
	काष्ठा चयनtec_ntb *sndev = stdev->sndev;

	अगर (!sndev)
		वापस;

	stdev->link_notअगरier = शून्य;
	stdev->sndev = शून्य;
	ntb_unरेजिस्टर_device(&sndev->ntb);
	चयनtec_ntb_deinit_db_msg_irq(sndev);
	चयनtec_ntb_deinit_shared_mw(sndev);
	चयनtec_ntb_deinit_crosslink(sndev);
	kमुक्त(sndev);
	dev_info(dev, "ntb device unregistered\n");
पूर्ण

अटल काष्ठा class_पूर्णांकerface चयनtec_पूर्णांकerface  = अणु
	.add_dev = चयनtec_ntb_add,
	.हटाओ_dev = चयनtec_ntb_हटाओ,
पूर्ण;

अटल पूर्णांक __init चयनtec_ntb_init(व्योम)
अणु
	चयनtec_पूर्णांकerface.class = चयनtec_class;
	वापस class_पूर्णांकerface_रेजिस्टर(&चयनtec_पूर्णांकerface);
पूर्ण
module_init(चयनtec_ntb_init);

अटल व्योम __निकास चयनtec_ntb_निकास(व्योम)
अणु
	class_पूर्णांकerface_unरेजिस्टर(&चयनtec_पूर्णांकerface);
पूर्ण
module_निकास(चयनtec_ntb_निकास);
