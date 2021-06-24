<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Marvell 88SE64xx/88SE94xx मुख्य function
 *
 * Copyright 2007 Red Hat, Inc.
 * Copyright 2008 Marvell. <kewei@marvell.com>
 * Copyright 2009-2011 Marvell. <yuxiangl@marvell.com>
*/

#समावेश "mv_sas.h"

अटल पूर्णांक mvs_find_tag(काष्ठा mvs_info *mvi, काष्ठा sas_task *task, u32 *tag)
अणु
	अगर (task->lldd_task) अणु
		काष्ठा mvs_slot_info *slot;
		slot = task->lldd_task;
		*tag = slot->slot_tag;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

व्योम mvs_tag_clear(काष्ठा mvs_info *mvi, u32 tag)
अणु
	व्योम *biपंचांगap = mvi->tags;
	clear_bit(tag, biपंचांगap);
पूर्ण

व्योम mvs_tag_मुक्त(काष्ठा mvs_info *mvi, u32 tag)
अणु
	mvs_tag_clear(mvi, tag);
पूर्ण

व्योम mvs_tag_set(काष्ठा mvs_info *mvi, अचिन्हित पूर्णांक tag)
अणु
	व्योम *biपंचांगap = mvi->tags;
	set_bit(tag, biपंचांगap);
पूर्ण

अंतरभूत पूर्णांक mvs_tag_alloc(काष्ठा mvs_info *mvi, u32 *tag_out)
अणु
	अचिन्हित पूर्णांक index, tag;
	व्योम *biपंचांगap = mvi->tags;

	index = find_first_zero_bit(biपंचांगap, mvi->tags_num);
	tag = index;
	अगर (tag >= mvi->tags_num)
		वापस -SAS_QUEUE_FULL;
	mvs_tag_set(mvi, tag);
	*tag_out = tag;
	वापस 0;
पूर्ण

व्योम mvs_tag_init(काष्ठा mvs_info *mvi)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < mvi->tags_num; ++i)
		mvs_tag_clear(mvi, i);
पूर्ण

अटल काष्ठा mvs_info *mvs_find_dev_mvi(काष्ठा करोमुख्य_device *dev)
अणु
	अचिन्हित दीर्घ i = 0, j = 0, hi = 0;
	काष्ठा sas_ha_काष्ठा *sha = dev->port->ha;
	काष्ठा mvs_info *mvi = शून्य;
	काष्ठा asd_sas_phy *phy;

	जबतक (sha->sas_port[i]) अणु
		अगर (sha->sas_port[i] == dev->port) अणु
			phy =  container_of(sha->sas_port[i]->phy_list.next,
				काष्ठा asd_sas_phy, port_phy_el);
			j = 0;
			जबतक (sha->sas_phy[j]) अणु
				अगर (sha->sas_phy[j] == phy)
					अवरोध;
				j++;
			पूर्ण
			अवरोध;
		पूर्ण
		i++;
	पूर्ण
	hi = j/((काष्ठा mvs_prv_info *)sha->lldd_ha)->n_phy;
	mvi = ((काष्ठा mvs_prv_info *)sha->lldd_ha)->mvi[hi];

	वापस mvi;

पूर्ण

अटल पूर्णांक mvs_find_dev_phyno(काष्ठा करोमुख्य_device *dev, पूर्णांक *phyno)
अणु
	अचिन्हित दीर्घ i = 0, j = 0, n = 0, num = 0;
	काष्ठा mvs_device *mvi_dev = (काष्ठा mvs_device *)dev->lldd_dev;
	काष्ठा mvs_info *mvi = mvi_dev->mvi_info;
	काष्ठा sas_ha_काष्ठा *sha = dev->port->ha;

	जबतक (sha->sas_port[i]) अणु
		अगर (sha->sas_port[i] == dev->port) अणु
			काष्ठा asd_sas_phy *phy;
			list_क्रम_each_entry(phy,
				&sha->sas_port[i]->phy_list, port_phy_el) अणु
				j = 0;
				जबतक (sha->sas_phy[j]) अणु
					अगर (sha->sas_phy[j] == phy)
						अवरोध;
					j++;
				पूर्ण
				phyno[n] = (j >= mvi->chip->n_phy) ?
					(j - mvi->chip->n_phy) : j;
				num++;
				n++;
			पूर्ण
			अवरोध;
		पूर्ण
		i++;
	पूर्ण
	वापस num;
पूर्ण

काष्ठा mvs_device *mvs_find_dev_by_reg_set(काष्ठा mvs_info *mvi,
						u8 reg_set)
अणु
	u32 dev_no;
	क्रम (dev_no = 0; dev_no < MVS_MAX_DEVICES; dev_no++) अणु
		अगर (mvi->devices[dev_no].taskfileset == MVS_ID_NOT_MAPPED)
			जारी;

		अगर (mvi->devices[dev_no].taskfileset == reg_set)
			वापस &mvi->devices[dev_no];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम mvs_मुक्त_reg_set(काष्ठा mvs_info *mvi,
				काष्ठा mvs_device *dev)
अणु
	अगर (!dev) अणु
		mv_prपूर्णांकk("device has been free.\n");
		वापस;
	पूर्ण
	अगर (dev->taskfileset == MVS_ID_NOT_MAPPED)
		वापस;
	MVS_CHIP_DISP->मुक्त_reg_set(mvi, &dev->taskfileset);
पूर्ण

अटल अंतरभूत u8 mvs_assign_reg_set(काष्ठा mvs_info *mvi,
				काष्ठा mvs_device *dev)
अणु
	अगर (dev->taskfileset != MVS_ID_NOT_MAPPED)
		वापस 0;
	वापस MVS_CHIP_DISP->assign_reg_set(mvi, &dev->taskfileset);
पूर्ण

व्योम mvs_phys_reset(काष्ठा mvs_info *mvi, u32 phy_mask, पूर्णांक hard)
अणु
	u32 no;
	क्रम_each_phy(phy_mask, phy_mask, no) अणु
		अगर (!(phy_mask & 1))
			जारी;
		MVS_CHIP_DISP->phy_reset(mvi, no, hard);
	पूर्ण
पूर्ण

पूर्णांक mvs_phy_control(काष्ठा asd_sas_phy *sas_phy, क्रमागत phy_func func,
			व्योम *funcdata)
अणु
	पूर्णांक rc = 0, phy_id = sas_phy->id;
	u32 पंचांगp, i = 0, hi;
	काष्ठा sas_ha_काष्ठा *sha = sas_phy->ha;
	काष्ठा mvs_info *mvi = शून्य;

	जबतक (sha->sas_phy[i]) अणु
		अगर (sha->sas_phy[i] == sas_phy)
			अवरोध;
		i++;
	पूर्ण
	hi = i/((काष्ठा mvs_prv_info *)sha->lldd_ha)->n_phy;
	mvi = ((काष्ठा mvs_prv_info *)sha->lldd_ha)->mvi[hi];

	चयन (func) अणु
	हाल PHY_FUNC_SET_LINK_RATE:
		MVS_CHIP_DISP->phy_set_link_rate(mvi, phy_id, funcdata);
		अवरोध;

	हाल PHY_FUNC_HARD_RESET:
		पंचांगp = MVS_CHIP_DISP->पढ़ो_phy_ctl(mvi, phy_id);
		अगर (पंचांगp & PHY_RST_HARD)
			अवरोध;
		MVS_CHIP_DISP->phy_reset(mvi, phy_id, MVS_HARD_RESET);
		अवरोध;

	हाल PHY_FUNC_LINK_RESET:
		MVS_CHIP_DISP->phy_enable(mvi, phy_id);
		MVS_CHIP_DISP->phy_reset(mvi, phy_id, MVS_SOFT_RESET);
		अवरोध;

	हाल PHY_FUNC_DISABLE:
		MVS_CHIP_DISP->phy_disable(mvi, phy_id);
		अवरोध;
	हाल PHY_FUNC_RELEASE_SPINUP_HOLD:
	शेष:
		rc = -ENOSYS;
	पूर्ण
	msleep(200);
	वापस rc;
पूर्ण

व्योम mvs_set_sas_addr(काष्ठा mvs_info *mvi, पूर्णांक port_id, u32 off_lo,
		      u32 off_hi, u64 sas_addr)
अणु
	u32 lo = (u32)sas_addr;
	u32 hi = (u32)(sas_addr>>32);

	MVS_CHIP_DISP->ग_लिखो_port_cfg_addr(mvi, port_id, off_lo);
	MVS_CHIP_DISP->ग_लिखो_port_cfg_data(mvi, port_id, lo);
	MVS_CHIP_DISP->ग_लिखो_port_cfg_addr(mvi, port_id, off_hi);
	MVS_CHIP_DISP->ग_लिखो_port_cfg_data(mvi, port_id, hi);
पूर्ण

अटल व्योम mvs_bytes_dmaed(काष्ठा mvs_info *mvi, पूर्णांक i, gfp_t gfp_flags)
अणु
	काष्ठा mvs_phy *phy = &mvi->phy[i];
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;

	अगर (!phy->phy_attached)
		वापस;

	अगर (!(phy->att_dev_info & PORT_DEV_TRGT_MASK)
		&& phy->phy_type & PORT_TYPE_SAS) अणु
		वापस;
	पूर्ण

	sas_notअगरy_phy_event(sas_phy, PHYE_OOB_DONE, gfp_flags);

	अगर (sas_phy->phy) अणु
		काष्ठा sas_phy *sphy = sas_phy->phy;

		sphy->negotiated_linkrate = sas_phy->linkrate;
		sphy->minimum_linkrate = phy->minimum_linkrate;
		sphy->minimum_linkrate_hw = SAS_LINK_RATE_1_5_GBPS;
		sphy->maximum_linkrate = phy->maximum_linkrate;
		sphy->maximum_linkrate_hw = MVS_CHIP_DISP->phy_max_link_rate();
	पूर्ण

	अगर (phy->phy_type & PORT_TYPE_SAS) अणु
		काष्ठा sas_identअगरy_frame *id;

		id = (काष्ठा sas_identअगरy_frame *)phy->frame_rcvd;
		id->dev_type = phy->identअगरy.device_type;
		id->initiator_bits = SAS_PROTOCOL_ALL;
		id->target_bits = phy->identअगरy.target_port_protocols;

		/* direct attached SAS device */
		अगर (phy->att_dev_info & PORT_SSP_TRGT_MASK) अणु
			MVS_CHIP_DISP->ग_लिखो_port_cfg_addr(mvi, i, PHYR_PHY_STAT);
			MVS_CHIP_DISP->ग_लिखो_port_cfg_data(mvi, i, 0x00);
		पूर्ण
	पूर्ण अन्यथा अगर (phy->phy_type & PORT_TYPE_SATA) अणु
		/*Nothing*/
	पूर्ण
	mv_dprपूर्णांकk("phy %d byte dmaded.\n", i + mvi->id * mvi->chip->n_phy);

	sas_phy->frame_rcvd_size = phy->frame_rcvd_size;

	sas_notअगरy_port_event(sas_phy, PORTE_BYTES_DMAED, gfp_flags);
पूर्ण

व्योम mvs_scan_start(काष्ठा Scsi_Host *shost)
अणु
	पूर्णांक i, j;
	अचिन्हित लघु core_nr;
	काष्ठा mvs_info *mvi;
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा mvs_prv_info *mvs_prv = sha->lldd_ha;

	core_nr = ((काष्ठा mvs_prv_info *)sha->lldd_ha)->n_host;

	क्रम (j = 0; j < core_nr; j++) अणु
		mvi = ((काष्ठा mvs_prv_info *)sha->lldd_ha)->mvi[j];
		क्रम (i = 0; i < mvi->chip->n_phy; ++i)
			mvs_bytes_dmaed(mvi, i, GFP_KERNEL);
	पूर्ण
	mvs_prv->scan_finished = 1;
पूर्ण

पूर्णांक mvs_scan_finished(काष्ठा Scsi_Host *shost, अचिन्हित दीर्घ समय)
अणु
	काष्ठा sas_ha_काष्ठा *sha = SHOST_TO_SAS_HA(shost);
	काष्ठा mvs_prv_info *mvs_prv = sha->lldd_ha;

	अगर (mvs_prv->scan_finished == 0)
		वापस 0;

	sas_drain_work(sha);
	वापस 1;
पूर्ण

अटल पूर्णांक mvs_task_prep_smp(काष्ठा mvs_info *mvi,
			     काष्ठा mvs_task_exec_info *tei)
अणु
	पूर्णांक elem, rc, i;
	काष्ठा sas_ha_काष्ठा *sha = mvi->sas;
	काष्ठा sas_task *task = tei->task;
	काष्ठा mvs_cmd_hdr *hdr = tei->hdr;
	काष्ठा करोमुख्य_device *dev = task->dev;
	काष्ठा asd_sas_port *sas_port = dev->port;
	काष्ठा sas_phy *sphy = dev->phy;
	काष्ठा asd_sas_phy *sas_phy = sha->sas_phy[sphy->number];
	काष्ठा scatterlist *sg_req, *sg_resp;
	u32 req_len, resp_len, tag = tei->tag;
	व्योम *buf_पंचांगp;
	u8 *buf_oaf;
	dma_addr_t buf_पंचांगp_dma;
	व्योम *buf_prd;
	काष्ठा mvs_slot_info *slot = &mvi->slot_info[tag];
	u32 flags = (tei->n_elem << MCH_PRD_LEN_SHIFT);

	/*
	 * DMA-map SMP request, response buffers
	 */
	sg_req = &task->smp_task.smp_req;
	elem = dma_map_sg(mvi->dev, sg_req, 1, DMA_TO_DEVICE);
	अगर (!elem)
		वापस -ENOMEM;
	req_len = sg_dma_len(sg_req);

	sg_resp = &task->smp_task.smp_resp;
	elem = dma_map_sg(mvi->dev, sg_resp, 1, DMA_FROM_DEVICE);
	अगर (!elem) अणु
		rc = -ENOMEM;
		जाओ err_out;
	पूर्ण
	resp_len = SB_RFB_MAX;

	/* must be in dwords */
	अगर ((req_len & 0x3) || (resp_len & 0x3)) अणु
		rc = -EINVAL;
		जाओ err_out_2;
	पूर्ण

	/*
	 * arrange MVS_SLOT_BUF_SZ-sized DMA buffer according to our needs
	 */

	/* region 1: command table area (MVS_SSP_CMD_SZ bytes) ***** */
	buf_पंचांगp = slot->buf;
	buf_पंचांगp_dma = slot->buf_dma;

	hdr->cmd_tbl = cpu_to_le64(sg_dma_address(sg_req));

	/* region 2: खोलो address frame area (MVS_OAF_SZ bytes) ********* */
	buf_oaf = buf_पंचांगp;
	hdr->खोलो_frame = cpu_to_le64(buf_पंचांगp_dma);

	buf_पंचांगp += MVS_OAF_SZ;
	buf_पंचांगp_dma += MVS_OAF_SZ;

	/* region 3: PRD table *********************************** */
	buf_prd = buf_पंचांगp;
	अगर (tei->n_elem)
		hdr->prd_tbl = cpu_to_le64(buf_पंचांगp_dma);
	अन्यथा
		hdr->prd_tbl = 0;

	i = MVS_CHIP_DISP->prd_size() * tei->n_elem;
	buf_पंचांगp += i;
	buf_पंचांगp_dma += i;

	/* region 4: status buffer (larger the PRD, smaller this buf) ****** */
	slot->response = buf_पंचांगp;
	hdr->status_buf = cpu_to_le64(buf_पंचांगp_dma);
	अगर (mvi->flags & MVF_FLAG_SOC)
		hdr->reserved[0] = 0;

	/*
	 * Fill in TX ring and command slot header
	 */
	slot->tx = mvi->tx_prod;
	mvi->tx[mvi->tx_prod] = cpu_to_le32((TXQ_CMD_SMP << TXQ_CMD_SHIFT) |
					TXQ_MODE_I | tag |
					(MVS_PHY_ID << TXQ_PHY_SHIFT));

	hdr->flags |= flags;
	hdr->lens = cpu_to_le32(((resp_len / 4) << 16) | ((req_len - 4) / 4));
	hdr->tags = cpu_to_le32(tag);
	hdr->data_len = 0;

	/* generate खोलो address frame hdr (first 12 bytes) */
	/* initiator, SMP, ftype 1h */
	buf_oaf[0] = (1 << 7) | (PROTOCOL_SMP << 4) | 0x01;
	buf_oaf[1] = min(sas_port->linkrate, dev->linkrate) & 0xf;
	*(u16 *)(buf_oaf + 2) = 0xFFFF;		/* SAS SPEC */
	स_नकल(buf_oaf + 4, dev->sas_addr, SAS_ADDR_SIZE);

	/* fill in PRD (scatter/gather) table, अगर any */
	MVS_CHIP_DISP->make_prd(task->scatter, tei->n_elem, buf_prd);

	वापस 0;

err_out_2:
	dma_unmap_sg(mvi->dev, &tei->task->smp_task.smp_resp, 1,
		     DMA_FROM_DEVICE);
err_out:
	dma_unmap_sg(mvi->dev, &tei->task->smp_task.smp_req, 1,
		     DMA_TO_DEVICE);
	वापस rc;
पूर्ण

अटल u32 mvs_get_ncq_tag(काष्ठा sas_task *task, u32 *tag)
अणु
	काष्ठा ata_queued_cmd *qc = task->uldd_task;

	अगर (qc) अणु
		अगर (qc->tf.command == ATA_CMD_FPDMA_WRITE ||
		    qc->tf.command == ATA_CMD_FPDMA_READ ||
		    qc->tf.command == ATA_CMD_FPDMA_RECV ||
		    qc->tf.command == ATA_CMD_FPDMA_SEND ||
		    qc->tf.command == ATA_CMD_NCQ_NON_DATA) अणु
			*tag = qc->tag;
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mvs_task_prep_ata(काष्ठा mvs_info *mvi,
			     काष्ठा mvs_task_exec_info *tei)
अणु
	काष्ठा sas_task *task = tei->task;
	काष्ठा करोमुख्य_device *dev = task->dev;
	काष्ठा mvs_device *mvi_dev = dev->lldd_dev;
	काष्ठा mvs_cmd_hdr *hdr = tei->hdr;
	काष्ठा asd_sas_port *sas_port = dev->port;
	काष्ठा mvs_slot_info *slot;
	व्योम *buf_prd;
	u32 tag = tei->tag, hdr_tag;
	u32 flags, del_q;
	व्योम *buf_पंचांगp;
	u8 *buf_cmd, *buf_oaf;
	dma_addr_t buf_पंचांगp_dma;
	u32 i, req_len, resp_len;
	स्थिर u32 max_resp_len = SB_RFB_MAX;

	अगर (mvs_assign_reg_set(mvi, mvi_dev) == MVS_ID_NOT_MAPPED) अणु
		mv_dprपूर्णांकk("Have not enough regiset for dev %d.\n",
			mvi_dev->device_id);
		वापस -EBUSY;
	पूर्ण
	slot = &mvi->slot_info[tag];
	slot->tx = mvi->tx_prod;
	del_q = TXQ_MODE_I | tag |
		(TXQ_CMD_STP << TXQ_CMD_SHIFT) |
		((sas_port->phy_mask & TXQ_PHY_MASK) << TXQ_PHY_SHIFT) |
		(mvi_dev->taskfileset << TXQ_SRS_SHIFT);
	mvi->tx[mvi->tx_prod] = cpu_to_le32(del_q);

	अगर (task->data_dir == DMA_FROM_DEVICE)
		flags = (MVS_CHIP_DISP->prd_count() << MCH_PRD_LEN_SHIFT);
	अन्यथा
		flags = (tei->n_elem << MCH_PRD_LEN_SHIFT);

	अगर (task->ata_task.use_ncq)
		flags |= MCH_FPDMA;
	अगर (dev->sata_dev.class == ATA_DEV_ATAPI) अणु
		अगर (task->ata_task.fis.command != ATA_CMD_ID_ATAPI)
			flags |= MCH_ATAPI;
	पूर्ण

	hdr->flags = cpu_to_le32(flags);

	अगर (task->ata_task.use_ncq && mvs_get_ncq_tag(task, &hdr_tag))
		task->ata_task.fis.sector_count |= (u8) (hdr_tag << 3);
	अन्यथा
		hdr_tag = tag;

	hdr->tags = cpu_to_le32(hdr_tag);

	hdr->data_len = cpu_to_le32(task->total_xfer_len);

	/*
	 * arrange MVS_SLOT_BUF_SZ-sized DMA buffer according to our needs
	 */

	/* region 1: command table area (MVS_ATA_CMD_SZ bytes) ************** */
	buf_cmd = buf_पंचांगp = slot->buf;
	buf_पंचांगp_dma = slot->buf_dma;

	hdr->cmd_tbl = cpu_to_le64(buf_पंचांगp_dma);

	buf_पंचांगp += MVS_ATA_CMD_SZ;
	buf_पंचांगp_dma += MVS_ATA_CMD_SZ;

	/* region 2: खोलो address frame area (MVS_OAF_SZ bytes) ********* */
	/* used क्रम STP.  unused क्रम SATA? */
	buf_oaf = buf_पंचांगp;
	hdr->खोलो_frame = cpu_to_le64(buf_पंचांगp_dma);

	buf_पंचांगp += MVS_OAF_SZ;
	buf_पंचांगp_dma += MVS_OAF_SZ;

	/* region 3: PRD table ********************************************* */
	buf_prd = buf_पंचांगp;

	अगर (tei->n_elem)
		hdr->prd_tbl = cpu_to_le64(buf_पंचांगp_dma);
	अन्यथा
		hdr->prd_tbl = 0;
	i = MVS_CHIP_DISP->prd_size() * MVS_CHIP_DISP->prd_count();

	buf_पंचांगp += i;
	buf_पंचांगp_dma += i;

	/* region 4: status buffer (larger the PRD, smaller this buf) ****** */
	slot->response = buf_पंचांगp;
	hdr->status_buf = cpu_to_le64(buf_पंचांगp_dma);
	अगर (mvi->flags & MVF_FLAG_SOC)
		hdr->reserved[0] = 0;

	req_len = माप(काष्ठा host_to_dev_fis);
	resp_len = MVS_SLOT_BUF_SZ - MVS_ATA_CMD_SZ -
	    माप(काष्ठा mvs_err_info) - i;

	/* request, response lengths */
	resp_len = min(resp_len, max_resp_len);
	hdr->lens = cpu_to_le32(((resp_len / 4) << 16) | (req_len / 4));

	अगर (likely(!task->ata_task.device_control_reg_update))
		task->ata_task.fis.flags |= 0x80; /* C=1: update ATA cmd reg */
	/* fill in command FIS and ATAPI CDB */
	स_नकल(buf_cmd, &task->ata_task.fis, माप(काष्ठा host_to_dev_fis));
	अगर (dev->sata_dev.class == ATA_DEV_ATAPI)
		स_नकल(buf_cmd + STP_ATAPI_CMD,
			task->ata_task.atapi_packet, 16);

	/* generate खोलो address frame hdr (first 12 bytes) */
	/* initiator, STP, ftype 1h */
	buf_oaf[0] = (1 << 7) | (PROTOCOL_STP << 4) | 0x1;
	buf_oaf[1] = min(sas_port->linkrate, dev->linkrate) & 0xf;
	*(u16 *)(buf_oaf + 2) = cpu_to_be16(mvi_dev->device_id + 1);
	स_नकल(buf_oaf + 4, dev->sas_addr, SAS_ADDR_SIZE);

	/* fill in PRD (scatter/gather) table, अगर any */
	MVS_CHIP_DISP->make_prd(task->scatter, tei->n_elem, buf_prd);

	अगर (task->data_dir == DMA_FROM_DEVICE)
		MVS_CHIP_DISP->dma_fix(mvi, sas_port->phy_mask,
				TRASH_BUCKET_SIZE, tei->n_elem, buf_prd);

	वापस 0;
पूर्ण

अटल पूर्णांक mvs_task_prep_ssp(काष्ठा mvs_info *mvi,
			     काष्ठा mvs_task_exec_info *tei, पूर्णांक is_पंचांगf,
			     काष्ठा mvs_पंचांगf_task *पंचांगf)
अणु
	काष्ठा sas_task *task = tei->task;
	काष्ठा mvs_cmd_hdr *hdr = tei->hdr;
	काष्ठा mvs_port *port = tei->port;
	काष्ठा करोमुख्य_device *dev = task->dev;
	काष्ठा mvs_device *mvi_dev = dev->lldd_dev;
	काष्ठा asd_sas_port *sas_port = dev->port;
	काष्ठा mvs_slot_info *slot;
	व्योम *buf_prd;
	काष्ठा ssp_frame_hdr *ssp_hdr;
	व्योम *buf_पंचांगp;
	u8 *buf_cmd, *buf_oaf, fburst = 0;
	dma_addr_t buf_पंचांगp_dma;
	u32 flags;
	u32 resp_len, req_len, i, tag = tei->tag;
	स्थिर u32 max_resp_len = SB_RFB_MAX;
	u32 phy_mask;

	slot = &mvi->slot_info[tag];

	phy_mask = ((port->wide_port_phymap) ? port->wide_port_phymap :
		sas_port->phy_mask) & TXQ_PHY_MASK;

	slot->tx = mvi->tx_prod;
	mvi->tx[mvi->tx_prod] = cpu_to_le32(TXQ_MODE_I | tag |
				(TXQ_CMD_SSP << TXQ_CMD_SHIFT) |
				(phy_mask << TXQ_PHY_SHIFT));

	flags = MCH_RETRY;
	अगर (task->ssp_task.enable_first_burst) अणु
		flags |= MCH_FBURST;
		fburst = (1 << 7);
	पूर्ण
	अगर (is_पंचांगf)
		flags |= (MCH_SSP_FR_TASK << MCH_SSP_FR_TYPE_SHIFT);
	अन्यथा
		flags |= (MCH_SSP_FR_CMD << MCH_SSP_FR_TYPE_SHIFT);

	hdr->flags = cpu_to_le32(flags | (tei->n_elem << MCH_PRD_LEN_SHIFT));
	hdr->tags = cpu_to_le32(tag);
	hdr->data_len = cpu_to_le32(task->total_xfer_len);

	/*
	 * arrange MVS_SLOT_BUF_SZ-sized DMA buffer according to our needs
	 */

	/* region 1: command table area (MVS_SSP_CMD_SZ bytes) ************** */
	buf_cmd = buf_पंचांगp = slot->buf;
	buf_पंचांगp_dma = slot->buf_dma;

	hdr->cmd_tbl = cpu_to_le64(buf_पंचांगp_dma);

	buf_पंचांगp += MVS_SSP_CMD_SZ;
	buf_पंचांगp_dma += MVS_SSP_CMD_SZ;

	/* region 2: खोलो address frame area (MVS_OAF_SZ bytes) ********* */
	buf_oaf = buf_पंचांगp;
	hdr->खोलो_frame = cpu_to_le64(buf_पंचांगp_dma);

	buf_पंचांगp += MVS_OAF_SZ;
	buf_पंचांगp_dma += MVS_OAF_SZ;

	/* region 3: PRD table ********************************************* */
	buf_prd = buf_पंचांगp;
	अगर (tei->n_elem)
		hdr->prd_tbl = cpu_to_le64(buf_पंचांगp_dma);
	अन्यथा
		hdr->prd_tbl = 0;

	i = MVS_CHIP_DISP->prd_size() * tei->n_elem;
	buf_पंचांगp += i;
	buf_पंचांगp_dma += i;

	/* region 4: status buffer (larger the PRD, smaller this buf) ****** */
	slot->response = buf_पंचांगp;
	hdr->status_buf = cpu_to_le64(buf_पंचांगp_dma);
	अगर (mvi->flags & MVF_FLAG_SOC)
		hdr->reserved[0] = 0;

	resp_len = MVS_SLOT_BUF_SZ - MVS_SSP_CMD_SZ - MVS_OAF_SZ -
	    माप(काष्ठा mvs_err_info) - i;
	resp_len = min(resp_len, max_resp_len);

	req_len = माप(काष्ठा ssp_frame_hdr) + 28;

	/* request, response lengths */
	hdr->lens = cpu_to_le32(((resp_len / 4) << 16) | (req_len / 4));

	/* generate खोलो address frame hdr (first 12 bytes) */
	/* initiator, SSP, ftype 1h */
	buf_oaf[0] = (1 << 7) | (PROTOCOL_SSP << 4) | 0x1;
	buf_oaf[1] = min(sas_port->linkrate, dev->linkrate) & 0xf;
	*(u16 *)(buf_oaf + 2) = cpu_to_be16(mvi_dev->device_id + 1);
	स_नकल(buf_oaf + 4, dev->sas_addr, SAS_ADDR_SIZE);

	/* fill in SSP frame header (Command Table.SSP frame header) */
	ssp_hdr = (काष्ठा ssp_frame_hdr *)buf_cmd;

	अगर (is_पंचांगf)
		ssp_hdr->frame_type = SSP_TASK;
	अन्यथा
		ssp_hdr->frame_type = SSP_COMMAND;

	स_नकल(ssp_hdr->hashed_dest_addr, dev->hashed_sas_addr,
	       HASHED_SAS_ADDR_SIZE);
	स_नकल(ssp_hdr->hashed_src_addr,
	       dev->hashed_sas_addr, HASHED_SAS_ADDR_SIZE);
	ssp_hdr->tag = cpu_to_be16(tag);

	/* fill in IU क्रम TASK and Command Frame */
	buf_cmd += माप(*ssp_hdr);
	स_नकल(buf_cmd, &task->ssp_task.LUN, 8);

	अगर (ssp_hdr->frame_type != SSP_TASK) अणु
		buf_cmd[9] = fburst | task->ssp_task.task_attr |
				(task->ssp_task.task_prio << 3);
		स_नकल(buf_cmd + 12, task->ssp_task.cmd->cmnd,
		       task->ssp_task.cmd->cmd_len);
	पूर्ण अन्यथाअणु
		buf_cmd[10] = पंचांगf->पंचांगf;
		चयन (पंचांगf->पंचांगf) अणु
		हाल TMF_ABORT_TASK:
		हाल TMF_QUERY_TASK:
			buf_cmd[12] =
				(पंचांगf->tag_of_task_to_be_managed >> 8) & 0xff;
			buf_cmd[13] =
				पंचांगf->tag_of_task_to_be_managed & 0xff;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	/* fill in PRD (scatter/gather) table, अगर any */
	MVS_CHIP_DISP->make_prd(task->scatter, tei->n_elem, buf_prd);
	वापस 0;
पूर्ण

#घोषणा	DEV_IS_GONE(mvi_dev)	((!mvi_dev || (mvi_dev->dev_type == SAS_PHY_UNUSED)))
अटल पूर्णांक mvs_task_prep(काष्ठा sas_task *task, काष्ठा mvs_info *mvi, पूर्णांक is_पंचांगf,
				काष्ठा mvs_पंचांगf_task *पंचांगf, पूर्णांक *pass)
अणु
	काष्ठा करोमुख्य_device *dev = task->dev;
	काष्ठा mvs_device *mvi_dev = dev->lldd_dev;
	काष्ठा mvs_task_exec_info tei;
	काष्ठा mvs_slot_info *slot;
	u32 tag = 0xdeadbeef, n_elem = 0;
	पूर्णांक rc = 0;

	अगर (!dev->port) अणु
		काष्ठा task_status_काष्ठा *tsm = &task->task_status;

		tsm->resp = SAS_TASK_UNDELIVERED;
		tsm->stat = SAS_PHY_DOWN;
		/*
		 * libsas will use dev->port, should
		 * not call task_करोne क्रम sata
		 */
		अगर (dev->dev_type != SAS_SATA_DEV)
			task->task_करोne(task);
		वापस rc;
	पूर्ण

	अगर (DEV_IS_GONE(mvi_dev)) अणु
		अगर (mvi_dev)
			mv_dprपूर्णांकk("device %d not ready.\n",
				mvi_dev->device_id);
		अन्यथा
			mv_dprपूर्णांकk("device %016llx not ready.\n",
				SAS_ADDR(dev->sas_addr));

		rc = SAS_PHY_DOWN;
		वापस rc;
	पूर्ण
	tei.port = dev->port->lldd_port;
	अगर (tei.port && !tei.port->port_attached && !पंचांगf) अणु
		अगर (sas_protocol_ata(task->task_proto)) अणु
			काष्ठा task_status_काष्ठा *ts = &task->task_status;
			mv_dprपूर्णांकk("SATA/STP port %d does not attach"
					"device.\n", dev->port->id);
			ts->resp = SAS_TASK_COMPLETE;
			ts->stat = SAS_PHY_DOWN;

			task->task_करोne(task);

		पूर्ण अन्यथा अणु
			काष्ठा task_status_काष्ठा *ts = &task->task_status;
			mv_dprपूर्णांकk("SAS port %d does not attach"
				"device.\n", dev->port->id);
			ts->resp = SAS_TASK_UNDELIVERED;
			ts->stat = SAS_PHY_DOWN;
			task->task_करोne(task);
		पूर्ण
		वापस rc;
	पूर्ण

	अगर (!sas_protocol_ata(task->task_proto)) अणु
		अगर (task->num_scatter) अणु
			n_elem = dma_map_sg(mvi->dev,
					    task->scatter,
					    task->num_scatter,
					    task->data_dir);
			अगर (!n_elem) अणु
				rc = -ENOMEM;
				जाओ prep_out;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		n_elem = task->num_scatter;
	पूर्ण

	rc = mvs_tag_alloc(mvi, &tag);
	अगर (rc)
		जाओ err_out;

	slot = &mvi->slot_info[tag];

	task->lldd_task = शून्य;
	slot->n_elem = n_elem;
	slot->slot_tag = tag;

	slot->buf = dma_pool_zalloc(mvi->dma_pool, GFP_ATOMIC, &slot->buf_dma);
	अगर (!slot->buf) अणु
		rc = -ENOMEM;
		जाओ err_out_tag;
	पूर्ण

	tei.task = task;
	tei.hdr = &mvi->slot[tag];
	tei.tag = tag;
	tei.n_elem = n_elem;
	चयन (task->task_proto) अणु
	हाल SAS_PROTOCOL_SMP:
		rc = mvs_task_prep_smp(mvi, &tei);
		अवरोध;
	हाल SAS_PROTOCOL_SSP:
		rc = mvs_task_prep_ssp(mvi, &tei, is_पंचांगf, पंचांगf);
		अवरोध;
	हाल SAS_PROTOCOL_SATA:
	हाल SAS_PROTOCOL_STP:
	हाल SAS_PROTOCOL_SATA | SAS_PROTOCOL_STP:
		rc = mvs_task_prep_ata(mvi, &tei);
		अवरोध;
	शेष:
		dev_prपूर्णांकk(KERN_ERR, mvi->dev,
			"unknown sas_task proto: 0x%x\n",
			task->task_proto);
		rc = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (rc) अणु
		mv_dprपूर्णांकk("rc is %x\n", rc);
		जाओ err_out_slot_buf;
	पूर्ण
	slot->task = task;
	slot->port = tei.port;
	task->lldd_task = slot;
	list_add_tail(&slot->entry, &tei.port->list);
	spin_lock(&task->task_state_lock);
	task->task_state_flags |= SAS_TASK_AT_INITIATOR;
	spin_unlock(&task->task_state_lock);

	mvi_dev->running_req++;
	++(*pass);
	mvi->tx_prod = (mvi->tx_prod + 1) & (MVS_CHIP_SLOT_SZ - 1);

	वापस rc;

err_out_slot_buf:
	dma_pool_मुक्त(mvi->dma_pool, slot->buf, slot->buf_dma);
err_out_tag:
	mvs_tag_मुक्त(mvi, tag);
err_out:

	dev_prपूर्णांकk(KERN_ERR, mvi->dev, "mvsas prep failed[%d]!\n", rc);
	अगर (!sas_protocol_ata(task->task_proto))
		अगर (n_elem)
			dma_unmap_sg(mvi->dev, task->scatter, n_elem,
				     task->data_dir);
prep_out:
	वापस rc;
पूर्ण

अटल पूर्णांक mvs_task_exec(काष्ठा sas_task *task, gfp_t gfp_flags,
				काष्ठा completion *completion, पूर्णांक is_पंचांगf,
				काष्ठा mvs_पंचांगf_task *पंचांगf)
अणु
	काष्ठा mvs_info *mvi = शून्य;
	u32 rc = 0;
	u32 pass = 0;
	अचिन्हित दीर्घ flags = 0;

	mvi = ((काष्ठा mvs_device *)task->dev->lldd_dev)->mvi_info;

	spin_lock_irqsave(&mvi->lock, flags);
	rc = mvs_task_prep(task, mvi, is_पंचांगf, पंचांगf, &pass);
	अगर (rc)
		dev_prपूर्णांकk(KERN_ERR, mvi->dev, "mvsas exec failed[%d]!\n", rc);

	अगर (likely(pass))
			MVS_CHIP_DISP->start_delivery(mvi, (mvi->tx_prod - 1) &
				(MVS_CHIP_SLOT_SZ - 1));
	spin_unlock_irqrestore(&mvi->lock, flags);

	वापस rc;
पूर्ण

पूर्णांक mvs_queue_command(काष्ठा sas_task *task, gfp_t gfp_flags)
अणु
	वापस mvs_task_exec(task, gfp_flags, शून्य, 0, शून्य);
पूर्ण

अटल व्योम mvs_slot_मुक्त(काष्ठा mvs_info *mvi, u32 rx_desc)
अणु
	u32 slot_idx = rx_desc & RXQ_SLOT_MASK;
	mvs_tag_clear(mvi, slot_idx);
पूर्ण

अटल व्योम mvs_slot_task_मुक्त(काष्ठा mvs_info *mvi, काष्ठा sas_task *task,
			  काष्ठा mvs_slot_info *slot, u32 slot_idx)
अणु
	अगर (!slot)
		वापस;
	अगर (!slot->task)
		वापस;
	अगर (!sas_protocol_ata(task->task_proto))
		अगर (slot->n_elem)
			dma_unmap_sg(mvi->dev, task->scatter,
				     slot->n_elem, task->data_dir);

	चयन (task->task_proto) अणु
	हाल SAS_PROTOCOL_SMP:
		dma_unmap_sg(mvi->dev, &task->smp_task.smp_resp, 1,
			     DMA_FROM_DEVICE);
		dma_unmap_sg(mvi->dev, &task->smp_task.smp_req, 1,
			     DMA_TO_DEVICE);
		अवरोध;

	हाल SAS_PROTOCOL_SATA:
	हाल SAS_PROTOCOL_STP:
	हाल SAS_PROTOCOL_SSP:
	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण

	अगर (slot->buf) अणु
		dma_pool_मुक्त(mvi->dma_pool, slot->buf, slot->buf_dma);
		slot->buf = शून्य;
	पूर्ण
	list_del_init(&slot->entry);
	task->lldd_task = शून्य;
	slot->task = शून्य;
	slot->port = शून्य;
	slot->slot_tag = 0xFFFFFFFF;
	mvs_slot_मुक्त(mvi, slot_idx);
पूर्ण

अटल व्योम mvs_update_wideport(काष्ठा mvs_info *mvi, पूर्णांक phy_no)
अणु
	काष्ठा mvs_phy *phy = &mvi->phy[phy_no];
	काष्ठा mvs_port *port = phy->port;
	पूर्णांक j, no;

	क्रम_each_phy(port->wide_port_phymap, j, no) अणु
		अगर (j & 1) अणु
			MVS_CHIP_DISP->ग_लिखो_port_cfg_addr(mvi, no,
						PHYR_WIDE_PORT);
			MVS_CHIP_DISP->ग_लिखो_port_cfg_data(mvi, no,
						port->wide_port_phymap);
		पूर्ण अन्यथा अणु
			MVS_CHIP_DISP->ग_लिखो_port_cfg_addr(mvi, no,
						PHYR_WIDE_PORT);
			MVS_CHIP_DISP->ग_लिखो_port_cfg_data(mvi, no,
						0);
		पूर्ण
	पूर्ण
पूर्ण

अटल u32 mvs_is_phy_पढ़ोy(काष्ठा mvs_info *mvi, पूर्णांक i)
अणु
	u32 पंचांगp;
	काष्ठा mvs_phy *phy = &mvi->phy[i];
	काष्ठा mvs_port *port = phy->port;

	पंचांगp = MVS_CHIP_DISP->पढ़ो_phy_ctl(mvi, i);
	अगर ((पंचांगp & PHY_READY_MASK) && !(phy->irq_status & PHYEV_POOF)) अणु
		अगर (!port)
			phy->phy_attached = 1;
		वापस पंचांगp;
	पूर्ण

	अगर (port) अणु
		अगर (phy->phy_type & PORT_TYPE_SAS) अणु
			port->wide_port_phymap &= ~(1U << i);
			अगर (!port->wide_port_phymap)
				port->port_attached = 0;
			mvs_update_wideport(mvi, i);
		पूर्ण अन्यथा अगर (phy->phy_type & PORT_TYPE_SATA)
			port->port_attached = 0;
		phy->port = शून्य;
		phy->phy_attached = 0;
		phy->phy_type &= ~(PORT_TYPE_SAS | PORT_TYPE_SATA);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम *mvs_get_d2h_reg(काष्ठा mvs_info *mvi, पूर्णांक i, व्योम *buf)
अणु
	u32 *s = (u32 *) buf;

	अगर (!s)
		वापस शून्य;

	MVS_CHIP_DISP->ग_लिखो_port_cfg_addr(mvi, i, PHYR_SATA_SIG3);
	s[3] = cpu_to_le32(MVS_CHIP_DISP->पढ़ो_port_cfg_data(mvi, i));

	MVS_CHIP_DISP->ग_लिखो_port_cfg_addr(mvi, i, PHYR_SATA_SIG2);
	s[2] = cpu_to_le32(MVS_CHIP_DISP->पढ़ो_port_cfg_data(mvi, i));

	MVS_CHIP_DISP->ग_लिखो_port_cfg_addr(mvi, i, PHYR_SATA_SIG1);
	s[1] = cpu_to_le32(MVS_CHIP_DISP->पढ़ो_port_cfg_data(mvi, i));

	MVS_CHIP_DISP->ग_लिखो_port_cfg_addr(mvi, i, PHYR_SATA_SIG0);
	s[0] = cpu_to_le32(MVS_CHIP_DISP->पढ़ो_port_cfg_data(mvi, i));

	अगर (((s[1] & 0x00FFFFFF) == 0x00EB1401) && (*(u8 *)&s[3] == 0x01))
		s[1] = 0x00EB1401 | (*((u8 *)&s[1] + 3) & 0x10);

	वापस s;
पूर्ण

अटल u32 mvs_is_sig_fis_received(u32 irq_status)
अणु
	वापस irq_status & PHYEV_SIG_FIS;
पूर्ण

अटल व्योम mvs_sig_हटाओ_समयr(काष्ठा mvs_phy *phy)
अणु
	अगर (phy->समयr.function)
		del_समयr(&phy->समयr);
	phy->समयr.function = शून्य;
पूर्ण

व्योम mvs_update_phyinfo(काष्ठा mvs_info *mvi, पूर्णांक i, पूर्णांक get_st)
अणु
	काष्ठा mvs_phy *phy = &mvi->phy[i];
	काष्ठा sas_identअगरy_frame *id;

	id = (काष्ठा sas_identअगरy_frame *)phy->frame_rcvd;

	अगर (get_st) अणु
		phy->irq_status = MVS_CHIP_DISP->पढ़ो_port_irq_stat(mvi, i);
		phy->phy_status = mvs_is_phy_पढ़ोy(mvi, i);
	पूर्ण

	अगर (phy->phy_status) अणु
		पूर्णांक oob_करोne = 0;
		काष्ठा asd_sas_phy *sas_phy = &mvi->phy[i].sas_phy;

		oob_करोne = MVS_CHIP_DISP->oob_करोne(mvi, i);

		MVS_CHIP_DISP->fix_phy_info(mvi, i, id);
		अगर (phy->phy_type & PORT_TYPE_SATA) अणु
			phy->identअगरy.target_port_protocols = SAS_PROTOCOL_STP;
			अगर (mvs_is_sig_fis_received(phy->irq_status)) अणु
				mvs_sig_हटाओ_समयr(phy);
				phy->phy_attached = 1;
				phy->att_dev_sas_addr =
					i + mvi->id * mvi->chip->n_phy;
				अगर (oob_करोne)
					sas_phy->oob_mode = SATA_OOB_MODE;
				phy->frame_rcvd_size =
				    माप(काष्ठा dev_to_host_fis);
				mvs_get_d2h_reg(mvi, i, id);
			पूर्ण अन्यथा अणु
				u32 पंचांगp;
				dev_prपूर्णांकk(KERN_DEBUG, mvi->dev,
					"Phy%d : No sig fis\n", i);
				पंचांगp = MVS_CHIP_DISP->पढ़ो_port_irq_mask(mvi, i);
				MVS_CHIP_DISP->ग_लिखो_port_irq_mask(mvi, i,
						पंचांगp | PHYEV_SIG_FIS);
				phy->phy_attached = 0;
				phy->phy_type &= ~PORT_TYPE_SATA;
				जाओ out_करोne;
			पूर्ण
		पूर्ण	अन्यथा अगर (phy->phy_type & PORT_TYPE_SAS
			|| phy->att_dev_info & PORT_SSP_INIT_MASK) अणु
			phy->phy_attached = 1;
			phy->identअगरy.device_type =
				phy->att_dev_info & PORT_DEV_TYPE_MASK;

			अगर (phy->identअगरy.device_type == SAS_END_DEVICE)
				phy->identअगरy.target_port_protocols =
							SAS_PROTOCOL_SSP;
			अन्यथा अगर (phy->identअगरy.device_type != SAS_PHY_UNUSED)
				phy->identअगरy.target_port_protocols =
							SAS_PROTOCOL_SMP;
			अगर (oob_करोne)
				sas_phy->oob_mode = SAS_OOB_MODE;
			phy->frame_rcvd_size =
			    माप(काष्ठा sas_identअगरy_frame);
		पूर्ण
		स_नकल(sas_phy->attached_sas_addr,
			&phy->att_dev_sas_addr, SAS_ADDR_SIZE);

		अगर (MVS_CHIP_DISP->phy_work_around)
			MVS_CHIP_DISP->phy_work_around(mvi, i);
	पूर्ण
	mv_dprपूर्णांकk("phy %d attach dev info is %x\n",
		i + mvi->id * mvi->chip->n_phy, phy->att_dev_info);
	mv_dprपूर्णांकk("phy %d attach sas addr is %llx\n",
		i + mvi->id * mvi->chip->n_phy, phy->att_dev_sas_addr);
out_करोne:
	अगर (get_st)
		MVS_CHIP_DISP->ग_लिखो_port_irq_stat(mvi, i, phy->irq_status);
पूर्ण

अटल व्योम mvs_port_notअगरy_क्रमmed(काष्ठा asd_sas_phy *sas_phy, पूर्णांक lock)
अणु
	काष्ठा sas_ha_काष्ठा *sas_ha = sas_phy->ha;
	काष्ठा mvs_info *mvi = शून्य; पूर्णांक i = 0, hi;
	काष्ठा mvs_phy *phy = sas_phy->lldd_phy;
	काष्ठा asd_sas_port *sas_port = sas_phy->port;
	काष्ठा mvs_port *port;
	अचिन्हित दीर्घ flags = 0;
	अगर (!sas_port)
		वापस;

	जबतक (sas_ha->sas_phy[i]) अणु
		अगर (sas_ha->sas_phy[i] == sas_phy)
			अवरोध;
		i++;
	पूर्ण
	hi = i/((काष्ठा mvs_prv_info *)sas_ha->lldd_ha)->n_phy;
	mvi = ((काष्ठा mvs_prv_info *)sas_ha->lldd_ha)->mvi[hi];
	अगर (i >= mvi->chip->n_phy)
		port = &mvi->port[i - mvi->chip->n_phy];
	अन्यथा
		port = &mvi->port[i];
	अगर (lock)
		spin_lock_irqsave(&mvi->lock, flags);
	port->port_attached = 1;
	phy->port = port;
	sas_port->lldd_port = port;
	अगर (phy->phy_type & PORT_TYPE_SAS) अणु
		port->wide_port_phymap = sas_port->phy_mask;
		mv_prपूर्णांकk("set wide port phy map %x\n", sas_port->phy_mask);
		mvs_update_wideport(mvi, sas_phy->id);

		/* direct attached SAS device */
		अगर (phy->att_dev_info & PORT_SSP_TRGT_MASK) अणु
			MVS_CHIP_DISP->ग_लिखो_port_cfg_addr(mvi, i, PHYR_PHY_STAT);
			MVS_CHIP_DISP->ग_लिखो_port_cfg_data(mvi, i, 0x04);
		पूर्ण
	पूर्ण
	अगर (lock)
		spin_unlock_irqrestore(&mvi->lock, flags);
पूर्ण

अटल व्योम mvs_port_notअगरy_deक्रमmed(काष्ठा asd_sas_phy *sas_phy, पूर्णांक lock)
अणु
	काष्ठा करोमुख्य_device *dev;
	काष्ठा mvs_phy *phy = sas_phy->lldd_phy;
	काष्ठा mvs_info *mvi = phy->mvi;
	काष्ठा asd_sas_port *port = sas_phy->port;
	पूर्णांक phy_no = 0;

	जबतक (phy != &mvi->phy[phy_no]) अणु
		phy_no++;
		अगर (phy_no >= MVS_MAX_PHYS)
			वापस;
	पूर्ण
	list_क्रम_each_entry(dev, &port->dev_list, dev_list_node)
		mvs_करो_release_task(phy->mvi, phy_no, dev);

पूर्ण


व्योम mvs_port_क्रमmed(काष्ठा asd_sas_phy *sas_phy)
अणु
	mvs_port_notअगरy_क्रमmed(sas_phy, 1);
पूर्ण

व्योम mvs_port_deक्रमmed(काष्ठा asd_sas_phy *sas_phy)
अणु
	mvs_port_notअगरy_deक्रमmed(sas_phy, 1);
पूर्ण

अटल काष्ठा mvs_device *mvs_alloc_dev(काष्ठा mvs_info *mvi)
अणु
	u32 dev;
	क्रम (dev = 0; dev < MVS_MAX_DEVICES; dev++) अणु
		अगर (mvi->devices[dev].dev_type == SAS_PHY_UNUSED) अणु
			mvi->devices[dev].device_id = dev;
			वापस &mvi->devices[dev];
		पूर्ण
	पूर्ण

	अगर (dev == MVS_MAX_DEVICES)
		mv_prपूर्णांकk("max support %d devices, ignore ..\n",
			MVS_MAX_DEVICES);

	वापस शून्य;
पूर्ण

अटल व्योम mvs_मुक्त_dev(काष्ठा mvs_device *mvi_dev)
अणु
	u32 id = mvi_dev->device_id;
	स_रखो(mvi_dev, 0, माप(*mvi_dev));
	mvi_dev->device_id = id;
	mvi_dev->dev_type = SAS_PHY_UNUSED;
	mvi_dev->dev_status = MVS_DEV_NORMAL;
	mvi_dev->taskfileset = MVS_ID_NOT_MAPPED;
पूर्ण

अटल पूर्णांक mvs_dev_found_notअगरy(काष्ठा करोमुख्य_device *dev, पूर्णांक lock)
अणु
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक res = 0;
	काष्ठा mvs_info *mvi = शून्य;
	काष्ठा करोमुख्य_device *parent_dev = dev->parent;
	काष्ठा mvs_device *mvi_device;

	mvi = mvs_find_dev_mvi(dev);

	अगर (lock)
		spin_lock_irqsave(&mvi->lock, flags);

	mvi_device = mvs_alloc_dev(mvi);
	अगर (!mvi_device) अणु
		res = -1;
		जाओ found_out;
	पूर्ण
	dev->lldd_dev = mvi_device;
	mvi_device->dev_status = MVS_DEV_NORMAL;
	mvi_device->dev_type = dev->dev_type;
	mvi_device->mvi_info = mvi;
	mvi_device->sas_device = dev;
	अगर (parent_dev && dev_is_expander(parent_dev->dev_type)) अणु
		पूर्णांक phy_id;
		u8 phy_num = parent_dev->ex_dev.num_phys;
		काष्ठा ex_phy *phy;
		क्रम (phy_id = 0; phy_id < phy_num; phy_id++) अणु
			phy = &parent_dev->ex_dev.ex_phy[phy_id];
			अगर (SAS_ADDR(phy->attached_sas_addr) ==
				SAS_ADDR(dev->sas_addr)) अणु
				mvi_device->attached_phy = phy_id;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (phy_id == phy_num) अणु
			mv_prपूर्णांकk("Error: no attached dev:%016llx"
				"at ex:%016llx.\n",
				SAS_ADDR(dev->sas_addr),
				SAS_ADDR(parent_dev->sas_addr));
			res = -1;
		पूर्ण
	पूर्ण

found_out:
	अगर (lock)
		spin_unlock_irqrestore(&mvi->lock, flags);
	वापस res;
पूर्ण

पूर्णांक mvs_dev_found(काष्ठा करोमुख्य_device *dev)
अणु
	वापस mvs_dev_found_notअगरy(dev, 1);
पूर्ण

अटल व्योम mvs_dev_gone_notअगरy(काष्ठा करोमुख्य_device *dev)
अणु
	अचिन्हित दीर्घ flags = 0;
	काष्ठा mvs_device *mvi_dev = dev->lldd_dev;
	काष्ठा mvs_info *mvi;

	अगर (!mvi_dev) अणु
		mv_dprपूर्णांकk("found dev has gone.\n");
		वापस;
	पूर्ण

	mvi = mvi_dev->mvi_info;

	spin_lock_irqsave(&mvi->lock, flags);

	mv_dprपूर्णांकk("found dev[%d:%x] is gone.\n",
		mvi_dev->device_id, mvi_dev->dev_type);
	mvs_release_task(mvi, dev);
	mvs_मुक्त_reg_set(mvi, mvi_dev);
	mvs_मुक्त_dev(mvi_dev);

	dev->lldd_dev = शून्य;
	mvi_dev->sas_device = शून्य;

	spin_unlock_irqrestore(&mvi->lock, flags);
पूर्ण


व्योम mvs_dev_gone(काष्ठा करोमुख्य_device *dev)
अणु
	mvs_dev_gone_notअगरy(dev);
पूर्ण

अटल व्योम mvs_task_करोne(काष्ठा sas_task *task)
अणु
	अगर (!del_समयr(&task->slow_task->समयr))
		वापस;
	complete(&task->slow_task->completion);
पूर्ण

अटल व्योम mvs_पंचांगf_समयकरोut(काष्ठा समयr_list *t)
अणु
	काष्ठा sas_task_slow *slow = from_समयr(slow, t, समयr);
	काष्ठा sas_task *task = slow->task;

	task->task_state_flags |= SAS_TASK_STATE_ABORTED;
	complete(&task->slow_task->completion);
पूर्ण

#घोषणा MVS_TASK_TIMEOUT 20
अटल पूर्णांक mvs_exec_पूर्णांकernal_पंचांगf_task(काष्ठा करोमुख्य_device *dev,
			व्योम *parameter, u32 para_len, काष्ठा mvs_पंचांगf_task *पंचांगf)
अणु
	पूर्णांक res, retry;
	काष्ठा sas_task *task = शून्य;

	क्रम (retry = 0; retry < 3; retry++) अणु
		task = sas_alloc_slow_task(GFP_KERNEL);
		अगर (!task)
			वापस -ENOMEM;

		task->dev = dev;
		task->task_proto = dev->tproto;

		स_नकल(&task->ssp_task, parameter, para_len);
		task->task_करोne = mvs_task_करोne;

		task->slow_task->समयr.function = mvs_पंचांगf_समयकरोut;
		task->slow_task->समयr.expires = jअगरfies + MVS_TASK_TIMEOUT*HZ;
		add_समयr(&task->slow_task->समयr);

		res = mvs_task_exec(task, GFP_KERNEL, शून्य, 1, पंचांगf);

		अगर (res) अणु
			del_समयr(&task->slow_task->समयr);
			mv_prपूर्णांकk("executing internal task failed:%d\n", res);
			जाओ ex_err;
		पूर्ण

		रुको_क्रम_completion(&task->slow_task->completion);
		res = TMF_RESP_FUNC_FAILED;
		/* Even TMF समयd out, वापस direct. */
		अगर ((task->task_state_flags & SAS_TASK_STATE_ABORTED)) अणु
			अगर (!(task->task_state_flags & SAS_TASK_STATE_DONE)) अणु
				mv_prपूर्णांकk("TMF task[%x] timeout.\n", पंचांगf->पंचांगf);
				जाओ ex_err;
			पूर्ण
		पूर्ण

		अगर (task->task_status.resp == SAS_TASK_COMPLETE &&
		    task->task_status.stat == SAM_STAT_GOOD) अणु
			res = TMF_RESP_FUNC_COMPLETE;
			अवरोध;
		पूर्ण

		अगर (task->task_status.resp == SAS_TASK_COMPLETE &&
		      task->task_status.stat == SAS_DATA_UNDERRUN) अणु
			/* no error, but वापस the number of bytes of
			 * underrun */
			res = task->task_status.residual;
			अवरोध;
		पूर्ण

		अगर (task->task_status.resp == SAS_TASK_COMPLETE &&
		      task->task_status.stat == SAS_DATA_OVERRUN) अणु
			mv_dprपूर्णांकk("blocked task error.\n");
			res = -EMSGSIZE;
			अवरोध;
		पूर्ण अन्यथा अणु
			mv_dprपूर्णांकk(" task to dev %016llx response: 0x%x "
				    "status 0x%x\n",
				    SAS_ADDR(dev->sas_addr),
				    task->task_status.resp,
				    task->task_status.stat);
			sas_मुक्त_task(task);
			task = शून्य;

		पूर्ण
	पूर्ण
ex_err:
	BUG_ON(retry == 3 && task != शून्य);
	sas_मुक्त_task(task);
	वापस res;
पूर्ण

अटल पूर्णांक mvs_debug_issue_ssp_पंचांगf(काष्ठा करोमुख्य_device *dev,
				u8 *lun, काष्ठा mvs_पंचांगf_task *पंचांगf)
अणु
	काष्ठा sas_ssp_task ssp_task;
	अगर (!(dev->tproto & SAS_PROTOCOL_SSP))
		वापस TMF_RESP_FUNC_ESUPP;

	स_नकल(ssp_task.LUN, lun, 8);

	वापस mvs_exec_पूर्णांकernal_पंचांगf_task(dev, &ssp_task,
				माप(ssp_task), पंचांगf);
पूर्ण


/*  Standard mandates link reset क्रम ATA  (type 0)
    and hard reset क्रम SSP (type 1) , only क्रम RECOVERY */
अटल पूर्णांक mvs_debug_I_T_nexus_reset(काष्ठा करोमुख्य_device *dev)
अणु
	पूर्णांक rc;
	काष्ठा sas_phy *phy = sas_get_local_phy(dev);
	पूर्णांक reset_type = (dev->dev_type == SAS_SATA_DEV ||
			(dev->tproto & SAS_PROTOCOL_STP)) ? 0 : 1;
	rc = sas_phy_reset(phy, reset_type);
	sas_put_local_phy(phy);
	msleep(2000);
	वापस rc;
पूर्ण

/* mandatory SAM-3 */
पूर्णांक mvs_lu_reset(काष्ठा करोमुख्य_device *dev, u8 *lun)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = TMF_RESP_FUNC_FAILED;
	काष्ठा mvs_पंचांगf_task पंचांगf_task;
	काष्ठा mvs_device * mvi_dev = dev->lldd_dev;
	काष्ठा mvs_info *mvi = mvi_dev->mvi_info;

	पंचांगf_task.पंचांगf = TMF_LU_RESET;
	mvi_dev->dev_status = MVS_DEV_EH;
	rc = mvs_debug_issue_ssp_पंचांगf(dev, lun, &पंचांगf_task);
	अगर (rc == TMF_RESP_FUNC_COMPLETE) अणु
		spin_lock_irqsave(&mvi->lock, flags);
		mvs_release_task(mvi, dev);
		spin_unlock_irqrestore(&mvi->lock, flags);
	पूर्ण
	/* If failed, fall-through I_T_Nexus reset */
	mv_prपूर्णांकk("%s for device[%x]:rc= %d\n", __func__,
			mvi_dev->device_id, rc);
	वापस rc;
पूर्ण

पूर्णांक mvs_I_T_nexus_reset(काष्ठा करोमुख्य_device *dev)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = TMF_RESP_FUNC_FAILED;
	काष्ठा mvs_device *mvi_dev = (काष्ठा mvs_device *)dev->lldd_dev;
	काष्ठा mvs_info *mvi = mvi_dev->mvi_info;

	अगर (mvi_dev->dev_status != MVS_DEV_EH)
		वापस TMF_RESP_FUNC_COMPLETE;
	अन्यथा
		mvi_dev->dev_status = MVS_DEV_NORMAL;
	rc = mvs_debug_I_T_nexus_reset(dev);
	mv_prपूर्णांकk("%s for device[%x]:rc= %d\n",
		__func__, mvi_dev->device_id, rc);

	spin_lock_irqsave(&mvi->lock, flags);
	mvs_release_task(mvi, dev);
	spin_unlock_irqrestore(&mvi->lock, flags);

	वापस rc;
पूर्ण
/* optional SAM-3 */
पूर्णांक mvs_query_task(काष्ठा sas_task *task)
अणु
	u32 tag;
	काष्ठा scsi_lun lun;
	काष्ठा mvs_पंचांगf_task पंचांगf_task;
	पूर्णांक rc = TMF_RESP_FUNC_FAILED;

	अगर (task->lldd_task && task->task_proto & SAS_PROTOCOL_SSP) अणु
		काष्ठा scsi_cmnd * cmnd = (काष्ठा scsi_cmnd *)task->uldd_task;
		काष्ठा करोमुख्य_device *dev = task->dev;
		काष्ठा mvs_device *mvi_dev = (काष्ठा mvs_device *)dev->lldd_dev;
		काष्ठा mvs_info *mvi = mvi_dev->mvi_info;

		पूर्णांक_to_scsilun(cmnd->device->lun, &lun);
		rc = mvs_find_tag(mvi, task, &tag);
		अगर (rc == 0) अणु
			rc = TMF_RESP_FUNC_FAILED;
			वापस rc;
		पूर्ण

		पंचांगf_task.पंचांगf = TMF_QUERY_TASK;
		पंचांगf_task.tag_of_task_to_be_managed = cpu_to_le16(tag);

		rc = mvs_debug_issue_ssp_पंचांगf(dev, lun.scsi_lun, &पंचांगf_task);
		चयन (rc) अणु
		/* The task is still in Lun, release it then */
		हाल TMF_RESP_FUNC_SUCC:
		/* The task is not in Lun or failed, reset the phy */
		हाल TMF_RESP_FUNC_FAILED:
		हाल TMF_RESP_FUNC_COMPLETE:
			अवरोध;
		पूर्ण
	पूर्ण
	mv_prपूर्णांकk("%s:rc= %d\n", __func__, rc);
	वापस rc;
पूर्ण

/*  mandatory SAM-3, still need मुक्त task/slot info */
पूर्णांक mvs_पात_task(काष्ठा sas_task *task)
अणु
	काष्ठा scsi_lun lun;
	काष्ठा mvs_पंचांगf_task पंचांगf_task;
	काष्ठा करोमुख्य_device *dev = task->dev;
	काष्ठा mvs_device *mvi_dev = (काष्ठा mvs_device *)dev->lldd_dev;
	काष्ठा mvs_info *mvi;
	पूर्णांक rc = TMF_RESP_FUNC_FAILED;
	अचिन्हित दीर्घ flags;
	u32 tag;

	अगर (!mvi_dev) अणु
		mv_prपूर्णांकk("Device has removed\n");
		वापस TMF_RESP_FUNC_FAILED;
	पूर्ण

	mvi = mvi_dev->mvi_info;

	spin_lock_irqsave(&task->task_state_lock, flags);
	अगर (task->task_state_flags & SAS_TASK_STATE_DONE) अणु
		spin_unlock_irqrestore(&task->task_state_lock, flags);
		rc = TMF_RESP_FUNC_COMPLETE;
		जाओ out;
	पूर्ण
	spin_unlock_irqrestore(&task->task_state_lock, flags);
	mvi_dev->dev_status = MVS_DEV_EH;
	अगर (task->lldd_task && task->task_proto & SAS_PROTOCOL_SSP) अणु
		काष्ठा scsi_cmnd * cmnd = (काष्ठा scsi_cmnd *)task->uldd_task;

		पूर्णांक_to_scsilun(cmnd->device->lun, &lun);
		rc = mvs_find_tag(mvi, task, &tag);
		अगर (rc == 0) अणु
			mv_prपूर्णांकk("No such tag in %s\n", __func__);
			rc = TMF_RESP_FUNC_FAILED;
			वापस rc;
		पूर्ण

		पंचांगf_task.पंचांगf = TMF_ABORT_TASK;
		पंचांगf_task.tag_of_task_to_be_managed = cpu_to_le16(tag);

		rc = mvs_debug_issue_ssp_पंचांगf(dev, lun.scsi_lun, &पंचांगf_task);

		/* अगर successful, clear the task and callback क्रमwards.*/
		अगर (rc == TMF_RESP_FUNC_COMPLETE) अणु
			u32 slot_no;
			काष्ठा mvs_slot_info *slot;

			अगर (task->lldd_task) अणु
				slot = task->lldd_task;
				slot_no = (u32) (slot - mvi->slot_info);
				spin_lock_irqsave(&mvi->lock, flags);
				mvs_slot_complete(mvi, slot_no, 1);
				spin_unlock_irqrestore(&mvi->lock, flags);
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अगर (task->task_proto & SAS_PROTOCOL_SATA ||
		task->task_proto & SAS_PROTOCOL_STP) अणु
		अगर (SAS_SATA_DEV == dev->dev_type) अणु
			काष्ठा mvs_slot_info *slot = task->lldd_task;
			u32 slot_idx = (u32)(slot - mvi->slot_info);
			mv_dprपूर्णांकk("mvs_abort_task() mvi=%p task=%p "
				   "slot=%p slot_idx=x%x\n",
				   mvi, task, slot, slot_idx);
			task->task_state_flags |= SAS_TASK_STATE_ABORTED;
			mvs_slot_task_मुक्त(mvi, task, slot, slot_idx);
			rc = TMF_RESP_FUNC_COMPLETE;
			जाओ out;
		पूर्ण

	पूर्ण
out:
	अगर (rc != TMF_RESP_FUNC_COMPLETE)
		mv_prपूर्णांकk("%s:rc= %d\n", __func__, rc);
	वापस rc;
पूर्ण

पूर्णांक mvs_पात_task_set(काष्ठा करोमुख्य_device *dev, u8 *lun)
अणु
	पूर्णांक rc;
	काष्ठा mvs_पंचांगf_task पंचांगf_task;

	पंचांगf_task.पंचांगf = TMF_ABORT_TASK_SET;
	rc = mvs_debug_issue_ssp_पंचांगf(dev, lun, &पंचांगf_task);

	वापस rc;
पूर्ण

पूर्णांक mvs_clear_aca(काष्ठा करोमुख्य_device *dev, u8 *lun)
अणु
	पूर्णांक rc = TMF_RESP_FUNC_FAILED;
	काष्ठा mvs_पंचांगf_task पंचांगf_task;

	पंचांगf_task.पंचांगf = TMF_CLEAR_ACA;
	rc = mvs_debug_issue_ssp_पंचांगf(dev, lun, &पंचांगf_task);

	वापस rc;
पूर्ण

पूर्णांक mvs_clear_task_set(काष्ठा करोमुख्य_device *dev, u8 *lun)
अणु
	पूर्णांक rc = TMF_RESP_FUNC_FAILED;
	काष्ठा mvs_पंचांगf_task पंचांगf_task;

	पंचांगf_task.पंचांगf = TMF_CLEAR_TASK_SET;
	rc = mvs_debug_issue_ssp_पंचांगf(dev, lun, &पंचांगf_task);

	वापस rc;
पूर्ण

अटल पूर्णांक mvs_sata_करोne(काष्ठा mvs_info *mvi, काष्ठा sas_task *task,
			u32 slot_idx, पूर्णांक err)
अणु
	काष्ठा mvs_device *mvi_dev = task->dev->lldd_dev;
	काष्ठा task_status_काष्ठा *tstat = &task->task_status;
	काष्ठा ata_task_resp *resp = (काष्ठा ata_task_resp *)tstat->buf;
	पूर्णांक stat = SAM_STAT_GOOD;


	resp->frame_len = माप(काष्ठा dev_to_host_fis);
	स_नकल(&resp->ending_fis[0],
	       SATA_RECEIVED_D2H_FIS(mvi_dev->taskfileset),
	       माप(काष्ठा dev_to_host_fis));
	tstat->buf_valid_size = माप(*resp);
	अगर (unlikely(err)) अणु
		अगर (unlikely(err & CMD_ISS_STPD))
			stat = SAS_OPEN_REJECT;
		अन्यथा
			stat = SAS_PROTO_RESPONSE;
       पूर्ण

	वापस stat;
पूर्ण

अटल व्योम mvs_set_sense(u8 *buffer, पूर्णांक len, पूर्णांक d_sense,
		पूर्णांक key, पूर्णांक asc, पूर्णांक ascq)
अणु
	स_रखो(buffer, 0, len);

	अगर (d_sense) अणु
		/* Descriptor क्रमmat */
		अगर (len < 4) अणु
			mv_prपूर्णांकk("Length %d of sense buffer too small to "
				"fit sense %x:%x:%x", len, key, asc, ascq);
		पूर्ण

		buffer[0] = 0x72;		/* Response Code	*/
		अगर (len > 1)
			buffer[1] = key;	/* Sense Key */
		अगर (len > 2)
			buffer[2] = asc;	/* ASC	*/
		अगर (len > 3)
			buffer[3] = ascq;	/* ASCQ	*/
	पूर्ण अन्यथा अणु
		अगर (len < 14) अणु
			mv_prपूर्णांकk("Length %d of sense buffer too small to "
				"fit sense %x:%x:%x", len, key, asc, ascq);
		पूर्ण

		buffer[0] = 0x70;		/* Response Code	*/
		अगर (len > 2)
			buffer[2] = key;	/* Sense Key */
		अगर (len > 7)
			buffer[7] = 0x0a;	/* Additional Sense Length */
		अगर (len > 12)
			buffer[12] = asc;	/* ASC */
		अगर (len > 13)
			buffer[13] = ascq; /* ASCQ */
	पूर्ण

	वापस;
पूर्ण

अटल व्योम mvs_fill_ssp_resp_iu(काष्ठा ssp_response_iu *iu,
				u8 key, u8 asc, u8 asc_q)
अणु
	iu->datapres = 2;
	iu->response_data_len = 0;
	iu->sense_data_len = 17;
	iu->status = 02;
	mvs_set_sense(iu->sense_data, 17, 0,
			key, asc, asc_q);
पूर्ण

अटल पूर्णांक mvs_slot_err(काष्ठा mvs_info *mvi, काष्ठा sas_task *task,
			 u32 slot_idx)
अणु
	काष्ठा mvs_slot_info *slot = &mvi->slot_info[slot_idx];
	पूर्णांक stat;
	u32 err_dw0 = le32_to_cpu(*(u32 *)slot->response);
	u32 err_dw1 = le32_to_cpu(*((u32 *)slot->response + 1));
	u32 tfs = 0;
	क्रमागत mvs_port_type type = PORT_TYPE_SAS;

	अगर (err_dw0 & CMD_ISS_STPD)
		MVS_CHIP_DISP->issue_stop(mvi, type, tfs);

	MVS_CHIP_DISP->command_active(mvi, slot_idx);

	stat = SAM_STAT_CHECK_CONDITION;
	चयन (task->task_proto) अणु
	हाल SAS_PROTOCOL_SSP:
	अणु
		stat = SAS_ABORTED_TASK;
		अगर ((err_dw0 & NO_DEST) || err_dw1 & bit(31)) अणु
			काष्ठा ssp_response_iu *iu = slot->response +
				माप(काष्ठा mvs_err_info);
			mvs_fill_ssp_resp_iu(iu, NOT_READY, 0x04, 01);
			sas_ssp_task_response(mvi->dev, task, iu);
			stat = SAM_STAT_CHECK_CONDITION;
		पूर्ण
		अगर (err_dw1 & bit(31))
			mv_prपूर्णांकk("reuse same slot, retry command.\n");
		अवरोध;
	पूर्ण
	हाल SAS_PROTOCOL_SMP:
		stat = SAM_STAT_CHECK_CONDITION;
		अवरोध;

	हाल SAS_PROTOCOL_SATA:
	हाल SAS_PROTOCOL_STP:
	हाल SAS_PROTOCOL_SATA | SAS_PROTOCOL_STP:
	अणु
		task->ata_task.use_ncq = 0;
		stat = SAS_PROTO_RESPONSE;
		mvs_sata_करोne(mvi, task, slot_idx, err_dw0);
	पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस stat;
पूर्ण

पूर्णांक mvs_slot_complete(काष्ठा mvs_info *mvi, u32 rx_desc, u32 flags)
अणु
	u32 slot_idx = rx_desc & RXQ_SLOT_MASK;
	काष्ठा mvs_slot_info *slot = &mvi->slot_info[slot_idx];
	काष्ठा sas_task *task = slot->task;
	काष्ठा mvs_device *mvi_dev = शून्य;
	काष्ठा task_status_काष्ठा *tstat;
	काष्ठा करोमुख्य_device *dev;
	u32 पातed;

	व्योम *to;
	क्रमागत exec_status sts;

	अगर (unlikely(!task || !task->lldd_task || !task->dev))
		वापस -1;

	tstat = &task->task_status;
	dev = task->dev;
	mvi_dev = dev->lldd_dev;

	spin_lock(&task->task_state_lock);
	task->task_state_flags &=
		~(SAS_TASK_STATE_PENDING | SAS_TASK_AT_INITIATOR);
	task->task_state_flags |= SAS_TASK_STATE_DONE;
	/* race condition*/
	पातed = task->task_state_flags & SAS_TASK_STATE_ABORTED;
	spin_unlock(&task->task_state_lock);

	स_रखो(tstat, 0, माप(*tstat));
	tstat->resp = SAS_TASK_COMPLETE;

	अगर (unlikely(पातed)) अणु
		tstat->stat = SAS_ABORTED_TASK;
		अगर (mvi_dev && mvi_dev->running_req)
			mvi_dev->running_req--;
		अगर (sas_protocol_ata(task->task_proto))
			mvs_मुक्त_reg_set(mvi, mvi_dev);

		mvs_slot_task_मुक्त(mvi, task, slot, slot_idx);
		वापस -1;
	पूर्ण

	/* when no device attaching, go ahead and complete by error handling*/
	अगर (unlikely(!mvi_dev || flags)) अणु
		अगर (!mvi_dev)
			mv_dprपूर्णांकk("port has not device.\n");
		tstat->stat = SAS_PHY_DOWN;
		जाओ out;
	पूर्ण

	/*
	 * error info record present; slot->response is 32 bit aligned but may
	 * not be 64 bit aligned, so check क्रम zero in two 32 bit पढ़ोs
	 */
	अगर (unlikely((rx_desc & RXQ_ERR)
		     && (*((u32 *)slot->response)
			 || *(((u32 *)slot->response) + 1)))) अणु
		mv_dprपूर्णांकk("port %d slot %d rx_desc %X has error info"
			"%016llX.\n", slot->port->sas_port.id, slot_idx,
			 rx_desc, get_unaligned_le64(slot->response));
		tstat->stat = mvs_slot_err(mvi, task, slot_idx);
		tstat->resp = SAS_TASK_COMPLETE;
		जाओ out;
	पूर्ण

	चयन (task->task_proto) अणु
	हाल SAS_PROTOCOL_SSP:
		/* hw says status == 0, datapres == 0 */
		अगर (rx_desc & RXQ_GOOD) अणु
			tstat->stat = SAM_STAT_GOOD;
			tstat->resp = SAS_TASK_COMPLETE;
		पूर्ण
		/* response frame present */
		अन्यथा अगर (rx_desc & RXQ_RSP) अणु
			काष्ठा ssp_response_iu *iu = slot->response +
						माप(काष्ठा mvs_err_info);
			sas_ssp_task_response(mvi->dev, task, iu);
		पूर्ण अन्यथा
			tstat->stat = SAM_STAT_CHECK_CONDITION;
		अवरोध;

	हाल SAS_PROTOCOL_SMP: अणु
			काष्ठा scatterlist *sg_resp = &task->smp_task.smp_resp;
			tstat->stat = SAM_STAT_GOOD;
			to = kmap_atomic(sg_page(sg_resp));
			स_नकल(to + sg_resp->offset,
				slot->response + माप(काष्ठा mvs_err_info),
				sg_dma_len(sg_resp));
			kunmap_atomic(to);
			अवरोध;
		पूर्ण

	हाल SAS_PROTOCOL_SATA:
	हाल SAS_PROTOCOL_STP:
	हाल SAS_PROTOCOL_SATA | SAS_PROTOCOL_STP: अणु
			tstat->stat = mvs_sata_करोne(mvi, task, slot_idx, 0);
			अवरोध;
		पूर्ण

	शेष:
		tstat->stat = SAM_STAT_CHECK_CONDITION;
		अवरोध;
	पूर्ण
	अगर (!slot->port->port_attached) अणु
		mv_dprपूर्णांकk("port %d has removed.\n", slot->port->sas_port.id);
		tstat->stat = SAS_PHY_DOWN;
	पूर्ण


out:
	अगर (mvi_dev && mvi_dev->running_req) अणु
		mvi_dev->running_req--;
		अगर (sas_protocol_ata(task->task_proto) && !mvi_dev->running_req)
			mvs_मुक्त_reg_set(mvi, mvi_dev);
	पूर्ण
	mvs_slot_task_मुक्त(mvi, task, slot, slot_idx);
	sts = tstat->stat;

	spin_unlock(&mvi->lock);
	अगर (task->task_करोne)
		task->task_करोne(task);

	spin_lock(&mvi->lock);

	वापस sts;
पूर्ण

व्योम mvs_करो_release_task(काष्ठा mvs_info *mvi,
		पूर्णांक phy_no, काष्ठा करोमुख्य_device *dev)
अणु
	u32 slot_idx;
	काष्ठा mvs_phy *phy;
	काष्ठा mvs_port *port;
	काष्ठा mvs_slot_info *slot, *slot2;

	phy = &mvi->phy[phy_no];
	port = phy->port;
	अगर (!port)
		वापस;
	/* clean cmpl queue in हाल request is alपढ़ोy finished */
	mvs_पूर्णांक_rx(mvi, false);



	list_क्रम_each_entry_safe(slot, slot2, &port->list, entry) अणु
		काष्ठा sas_task *task;
		slot_idx = (u32) (slot - mvi->slot_info);
		task = slot->task;

		अगर (dev && task->dev != dev)
			जारी;

		mv_prपूर्णांकk("Release slot [%x] tag[%x], task [%p]:\n",
			slot_idx, slot->slot_tag, task);
		MVS_CHIP_DISP->command_active(mvi, slot_idx);

		mvs_slot_complete(mvi, slot_idx, 1);
	पूर्ण
पूर्ण

व्योम mvs_release_task(काष्ठा mvs_info *mvi,
		      काष्ठा करोमुख्य_device *dev)
अणु
	पूर्णांक i, phyno[WIDE_PORT_MAX_PHY], num;
	num = mvs_find_dev_phyno(dev, phyno);
	क्रम (i = 0; i < num; i++)
		mvs_करो_release_task(mvi, phyno[i], dev);
पूर्ण

अटल व्योम mvs_phy_disconnected(काष्ठा mvs_phy *phy)
अणु
	phy->phy_attached = 0;
	phy->att_dev_info = 0;
	phy->att_dev_sas_addr = 0;
पूर्ण

अटल व्योम mvs_work_queue(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dw = container_of(work, काष्ठा delayed_work, work);
	काष्ठा mvs_wq *mwq = container_of(dw, काष्ठा mvs_wq, work_q);
	काष्ठा mvs_info *mvi = mwq->mvi;
	अचिन्हित दीर्घ flags;
	u32 phy_no = (अचिन्हित दीर्घ) mwq->data;
	काष्ठा mvs_phy *phy = &mvi->phy[phy_no];
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;

	spin_lock_irqsave(&mvi->lock, flags);
	अगर (mwq->handler & PHY_PLUG_EVENT) अणु

		अगर (phy->phy_event & PHY_PLUG_OUT) अणु
			u32 पंचांगp;

			पंचांगp = MVS_CHIP_DISP->पढ़ो_phy_ctl(mvi, phy_no);
			phy->phy_event &= ~PHY_PLUG_OUT;
			अगर (!(पंचांगp & PHY_READY_MASK)) अणु
				sas_phy_disconnected(sas_phy);
				mvs_phy_disconnected(phy);
				sas_notअगरy_phy_event(sas_phy,
					PHYE_LOSS_OF_SIGNAL, GFP_ATOMIC);
				mv_dprपूर्णांकk("phy%d Removed Device\n", phy_no);
			पूर्ण अन्यथा अणु
				MVS_CHIP_DISP->detect_porttype(mvi, phy_no);
				mvs_update_phyinfo(mvi, phy_no, 1);
				mvs_bytes_dmaed(mvi, phy_no, GFP_ATOMIC);
				mvs_port_notअगरy_क्रमmed(sas_phy, 0);
				mv_dprपूर्णांकk("phy%d Attached Device\n", phy_no);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (mwq->handler & EXP_BRCT_CHG) अणु
		phy->phy_event &= ~EXP_BRCT_CHG;
		sas_notअगरy_port_event(sas_phy,
				PORTE_BROADCAST_RCVD, GFP_ATOMIC);
		mv_dprपूर्णांकk("phy%d Got Broadcast Change\n", phy_no);
	पूर्ण
	list_del(&mwq->entry);
	spin_unlock_irqrestore(&mvi->lock, flags);
	kमुक्त(mwq);
पूर्ण

अटल पूर्णांक mvs_handle_event(काष्ठा mvs_info *mvi, व्योम *data, पूर्णांक handler)
अणु
	काष्ठा mvs_wq *mwq;
	पूर्णांक ret = 0;

	mwq = kदो_स्मृति(माप(काष्ठा mvs_wq), GFP_ATOMIC);
	अगर (mwq) अणु
		mwq->mvi = mvi;
		mwq->data = data;
		mwq->handler = handler;
		MV_INIT_DELAYED_WORK(&mwq->work_q, mvs_work_queue, mwq);
		list_add_tail(&mwq->entry, &mvi->wq_list);
		schedule_delayed_work(&mwq->work_q, HZ * 2);
	पूर्ण अन्यथा
		ret = -ENOMEM;

	वापस ret;
पूर्ण

अटल व्योम mvs_sig_समय_out(काष्ठा समयr_list *t)
अणु
	काष्ठा mvs_phy *phy = from_समयr(phy, t, समयr);
	काष्ठा mvs_info *mvi = phy->mvi;
	u8 phy_no;

	क्रम (phy_no = 0; phy_no < mvi->chip->n_phy; phy_no++) अणु
		अगर (&mvi->phy[phy_no] == phy) अणु
			mv_dprपूर्णांकk("Get signature time out, reset phy %d\n",
				phy_no+mvi->id*mvi->chip->n_phy);
			MVS_CHIP_DISP->phy_reset(mvi, phy_no, MVS_HARD_RESET);
		पूर्ण
	पूर्ण
पूर्ण

व्योम mvs_पूर्णांक_port(काष्ठा mvs_info *mvi, पूर्णांक phy_no, u32 events)
अणु
	u32 पंचांगp;
	काष्ठा mvs_phy *phy = &mvi->phy[phy_no];

	phy->irq_status = MVS_CHIP_DISP->पढ़ो_port_irq_stat(mvi, phy_no);
	MVS_CHIP_DISP->ग_लिखो_port_irq_stat(mvi, phy_no, phy->irq_status);
	mv_dprपूर्णांकk("phy %d ctrl sts=0x%08X.\n", phy_no+mvi->id*mvi->chip->n_phy,
		MVS_CHIP_DISP->पढ़ो_phy_ctl(mvi, phy_no));
	mv_dprपूर्णांकk("phy %d irq sts = 0x%08X\n", phy_no+mvi->id*mvi->chip->n_phy,
		phy->irq_status);

	/*
	* events is port event now ,
	* we need check the पूर्णांकerrupt status which beदीर्घs to per port.
	*/

	अगर (phy->irq_status & PHYEV_DCDR_ERR) अणु
		mv_dprपूर्णांकk("phy %d STP decoding error.\n",
		phy_no + mvi->id*mvi->chip->n_phy);
	पूर्ण

	अगर (phy->irq_status & PHYEV_POOF) अणु
		mdelay(500);
		अगर (!(phy->phy_event & PHY_PLUG_OUT)) अणु
			पूर्णांक dev_sata = phy->phy_type & PORT_TYPE_SATA;
			पूर्णांक पढ़ोy;
			mvs_करो_release_task(mvi, phy_no, शून्य);
			phy->phy_event |= PHY_PLUG_OUT;
			MVS_CHIP_DISP->clear_srs_irq(mvi, 0, 1);
			mvs_handle_event(mvi,
				(व्योम *)(अचिन्हित दीर्घ)phy_no,
				PHY_PLUG_EVENT);
			पढ़ोy = mvs_is_phy_पढ़ोy(mvi, phy_no);
			अगर (पढ़ोy || dev_sata) अणु
				अगर (MVS_CHIP_DISP->stp_reset)
					MVS_CHIP_DISP->stp_reset(mvi,
							phy_no);
				अन्यथा
					MVS_CHIP_DISP->phy_reset(mvi,
							phy_no, MVS_SOFT_RESET);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (phy->irq_status & PHYEV_COMWAKE) अणु
		पंचांगp = MVS_CHIP_DISP->पढ़ो_port_irq_mask(mvi, phy_no);
		MVS_CHIP_DISP->ग_लिखो_port_irq_mask(mvi, phy_no,
					पंचांगp | PHYEV_SIG_FIS);
		अगर (phy->समयr.function == शून्य) अणु
			phy->समयr.function = mvs_sig_समय_out;
			phy->समयr.expires = jअगरfies + 5*HZ;
			add_समयr(&phy->समयr);
		पूर्ण
	पूर्ण
	अगर (phy->irq_status & (PHYEV_SIG_FIS | PHYEV_ID_DONE)) अणु
		phy->phy_status = mvs_is_phy_पढ़ोy(mvi, phy_no);
		mv_dprपूर्णांकk("notify plug in on phy[%d]\n", phy_no);
		अगर (phy->phy_status) अणु
			mdelay(10);
			MVS_CHIP_DISP->detect_porttype(mvi, phy_no);
			अगर (phy->phy_type & PORT_TYPE_SATA) अणु
				पंचांगp = MVS_CHIP_DISP->पढ़ो_port_irq_mask(
						mvi, phy_no);
				पंचांगp &= ~PHYEV_SIG_FIS;
				MVS_CHIP_DISP->ग_लिखो_port_irq_mask(mvi,
							phy_no, पंचांगp);
			पूर्ण
			mvs_update_phyinfo(mvi, phy_no, 0);
			अगर (phy->phy_type & PORT_TYPE_SAS) अणु
				MVS_CHIP_DISP->phy_reset(mvi, phy_no, MVS_PHY_TUNE);
				mdelay(10);
			पूर्ण

			mvs_bytes_dmaed(mvi, phy_no, GFP_ATOMIC);
			/* whether driver is going to handle hot plug */
			अगर (phy->phy_event & PHY_PLUG_OUT) अणु
				mvs_port_notअगरy_क्रमmed(&phy->sas_phy, 0);
				phy->phy_event &= ~PHY_PLUG_OUT;
			पूर्ण
		पूर्ण अन्यथा अणु
			mv_dprपूर्णांकk("plugin interrupt but phy%d is gone\n",
				phy_no + mvi->id*mvi->chip->n_phy);
		पूर्ण
	पूर्ण अन्यथा अगर (phy->irq_status & PHYEV_BROAD_CH) अणु
		mv_dprपूर्णांकk("phy %d broadcast change.\n",
			phy_no + mvi->id*mvi->chip->n_phy);
		mvs_handle_event(mvi, (व्योम *)(अचिन्हित दीर्घ)phy_no,
				EXP_BRCT_CHG);
	पूर्ण
पूर्ण

पूर्णांक mvs_पूर्णांक_rx(काष्ठा mvs_info *mvi, bool self_clear)
अणु
	u32 rx_prod_idx, rx_desc;
	bool attn = false;

	/* the first dword in the RX ring is special: it contains
	 * a mirror of the hardware's RX producer index, so that
	 * we करोn't have to stall the CPU पढ़ोing that रेजिस्टर.
	 * The actual RX ring is offset by one dword, due to this.
	 */
	rx_prod_idx = mvi->rx_cons;
	mvi->rx_cons = le32_to_cpu(mvi->rx[0]);
	अगर (mvi->rx_cons == 0xfff)	/* h/w hasn't touched RX ring yet */
		वापस 0;

	/* The CMPL_Q may come late, पढ़ो from रेजिस्टर and try again
	* note: अगर coalescing is enabled,
	* it will need to पढ़ो from रेजिस्टर every समय क्रम sure
	*/
	अगर (unlikely(mvi->rx_cons == rx_prod_idx))
		mvi->rx_cons = MVS_CHIP_DISP->rx_update(mvi) & RX_RING_SZ_MASK;

	अगर (mvi->rx_cons == rx_prod_idx)
		वापस 0;

	जबतक (mvi->rx_cons != rx_prod_idx) अणु
		/* increment our पूर्णांकernal RX consumer poपूर्णांकer */
		rx_prod_idx = (rx_prod_idx + 1) & (MVS_RX_RING_SZ - 1);
		rx_desc = le32_to_cpu(mvi->rx[rx_prod_idx + 1]);

		अगर (likely(rx_desc & RXQ_DONE))
			mvs_slot_complete(mvi, rx_desc, 0);
		अगर (rx_desc & RXQ_ATTN) अणु
			attn = true;
		पूर्ण अन्यथा अगर (rx_desc & RXQ_ERR) अणु
			अगर (!(rx_desc & RXQ_DONE))
				mvs_slot_complete(mvi, rx_desc, 0);
		पूर्ण अन्यथा अगर (rx_desc & RXQ_SLOT_RESET) अणु
			mvs_slot_मुक्त(mvi, rx_desc);
		पूर्ण
	पूर्ण

	अगर (attn && self_clear)
		MVS_CHIP_DISP->पूर्णांक_full(mvi);
	वापस 0;
पूर्ण

पूर्णांक mvs_gpio_ग_लिखो(काष्ठा sas_ha_काष्ठा *sha, u8 reg_type, u8 reg_index,
			u8 reg_count, u8 *ग_लिखो_data)
अणु
	काष्ठा mvs_prv_info *mvs_prv = sha->lldd_ha;
	काष्ठा mvs_info *mvi = mvs_prv->mvi[0];

	अगर (MVS_CHIP_DISP->gpio_ग_लिखो) अणु
		वापस MVS_CHIP_DISP->gpio_ग_लिखो(mvs_prv, reg_type,
			reg_index, reg_count, ग_लिखो_data);
	पूर्ण

	वापस -ENOSYS;
पूर्ण
