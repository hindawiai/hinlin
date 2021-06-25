<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic qlcnic NIC Driver
 * Copyright (c) 2009-2013 QLogic Corporation
 */

#समावेश "qlcnic.h"
#समावेश "qlcnic_hw.h"

काष्ठा crb_addr_pair अणु
	u32 addr;
	u32 data;
पूर्ण;

#घोषणा QLCNIC_MAX_CRB_XFORM 60
अटल अचिन्हित पूर्णांक crb_addr_xक्रमm[QLCNIC_MAX_CRB_XFORM];

#घोषणा crb_addr_transक्रमm(name) \
	(crb_addr_xक्रमm[QLCNIC_HW_PX_MAP_CRB_##name] = \
	QLCNIC_HW_CRB_HUB_AGT_ADR_##name << 20)

#घोषणा QLCNIC_ADDR_ERROR (0xffffffff)

अटल पूर्णांक
qlcnic_check_fw_hearbeat(काष्ठा qlcnic_adapter *adapter);

अटल व्योम crb_addr_transक्रमm_setup(व्योम)
अणु
	crb_addr_transक्रमm(XDMA);
	crb_addr_transक्रमm(TIMR);
	crb_addr_transक्रमm(SRE);
	crb_addr_transक्रमm(SQN3);
	crb_addr_transक्रमm(SQN2);
	crb_addr_transक्रमm(SQN1);
	crb_addr_transक्रमm(SQN0);
	crb_addr_transक्रमm(SQS3);
	crb_addr_transक्रमm(SQS2);
	crb_addr_transक्रमm(SQS1);
	crb_addr_transक्रमm(SQS0);
	crb_addr_transक्रमm(RPMX7);
	crb_addr_transक्रमm(RPMX6);
	crb_addr_transक्रमm(RPMX5);
	crb_addr_transक्रमm(RPMX4);
	crb_addr_transक्रमm(RPMX3);
	crb_addr_transक्रमm(RPMX2);
	crb_addr_transक्रमm(RPMX1);
	crb_addr_transक्रमm(RPMX0);
	crb_addr_transक्रमm(ROMUSB);
	crb_addr_transक्रमm(SN);
	crb_addr_transक्रमm(QMN);
	crb_addr_transक्रमm(QMS);
	crb_addr_transक्रमm(PGNI);
	crb_addr_transक्रमm(PGND);
	crb_addr_transक्रमm(PGN3);
	crb_addr_transक्रमm(PGN2);
	crb_addr_transक्रमm(PGN1);
	crb_addr_transक्रमm(PGN0);
	crb_addr_transक्रमm(PGSI);
	crb_addr_transक्रमm(PGSD);
	crb_addr_transक्रमm(PGS3);
	crb_addr_transक्रमm(PGS2);
	crb_addr_transक्रमm(PGS1);
	crb_addr_transक्रमm(PGS0);
	crb_addr_transक्रमm(PS);
	crb_addr_transक्रमm(PH);
	crb_addr_transक्रमm(NIU);
	crb_addr_transक्रमm(I2Q);
	crb_addr_transक्रमm(EG);
	crb_addr_transक्रमm(MN);
	crb_addr_transक्रमm(MS);
	crb_addr_transक्रमm(CAS2);
	crb_addr_transक्रमm(CAS1);
	crb_addr_transक्रमm(CAS0);
	crb_addr_transक्रमm(CAM);
	crb_addr_transक्रमm(C2C1);
	crb_addr_transक्रमm(C2C0);
	crb_addr_transक्रमm(SMB);
	crb_addr_transक्रमm(OCM0);
	crb_addr_transक्रमm(I2C0);
पूर्ण

व्योम qlcnic_release_rx_buffers(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_recv_context *recv_ctx;
	काष्ठा qlcnic_host_rds_ring *rds_ring;
	काष्ठा qlcnic_rx_buffer *rx_buf;
	पूर्णांक i, ring;

	recv_ctx = adapter->recv_ctx;
	क्रम (ring = 0; ring < adapter->max_rds_rings; ring++) अणु
		rds_ring = &recv_ctx->rds_rings[ring];
		क्रम (i = 0; i < rds_ring->num_desc; ++i) अणु
			rx_buf = &(rds_ring->rx_buf_arr[i]);
			अगर (rx_buf->skb == शून्य)
				जारी;

			pci_unmap_single(adapter->pdev,
					rx_buf->dma,
					rds_ring->dma_size,
					PCI_DMA_FROMDEVICE);

			dev_kमुक्त_skb_any(rx_buf->skb);
		पूर्ण
	पूर्ण
पूर्ण

व्योम qlcnic_reset_rx_buffers_list(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_recv_context *recv_ctx;
	काष्ठा qlcnic_host_rds_ring *rds_ring;
	काष्ठा qlcnic_rx_buffer *rx_buf;
	पूर्णांक i, ring;

	recv_ctx = adapter->recv_ctx;
	क्रम (ring = 0; ring < adapter->max_rds_rings; ring++) अणु
		rds_ring = &recv_ctx->rds_rings[ring];

		INIT_LIST_HEAD(&rds_ring->मुक्त_list);

		rx_buf = rds_ring->rx_buf_arr;
		क्रम (i = 0; i < rds_ring->num_desc; i++) अणु
			list_add_tail(&rx_buf->list,
					&rds_ring->मुक्त_list);
			rx_buf++;
		पूर्ण
	पूर्ण
पूर्ण

व्योम qlcnic_release_tx_buffers(काष्ठा qlcnic_adapter *adapter,
			       काष्ठा qlcnic_host_tx_ring *tx_ring)
अणु
	काष्ठा qlcnic_cmd_buffer *cmd_buf;
	काष्ठा qlcnic_skb_frag *buffrag;
	पूर्णांक i, j;

	spin_lock(&tx_ring->tx_clean_lock);

	cmd_buf = tx_ring->cmd_buf_arr;
	क्रम (i = 0; i < tx_ring->num_desc; i++) अणु
		buffrag = cmd_buf->frag_array;
		अगर (buffrag->dma) अणु
			pci_unmap_single(adapter->pdev, buffrag->dma,
					 buffrag->length, PCI_DMA_TODEVICE);
			buffrag->dma = 0ULL;
		पूर्ण
		क्रम (j = 1; j < cmd_buf->frag_count; j++) अणु
			buffrag++;
			अगर (buffrag->dma) अणु
				pci_unmap_page(adapter->pdev, buffrag->dma,
					       buffrag->length,
					       PCI_DMA_TODEVICE);
				buffrag->dma = 0ULL;
			पूर्ण
		पूर्ण
		अगर (cmd_buf->skb) अणु
			dev_kमुक्त_skb_any(cmd_buf->skb);
			cmd_buf->skb = शून्य;
		पूर्ण
		cmd_buf++;
	पूर्ण

	spin_unlock(&tx_ring->tx_clean_lock);
पूर्ण

व्योम qlcnic_मुक्त_sw_resources(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_recv_context *recv_ctx;
	काष्ठा qlcnic_host_rds_ring *rds_ring;
	पूर्णांक ring;

	recv_ctx = adapter->recv_ctx;

	अगर (recv_ctx->rds_rings == शून्य)
		वापस;

	क्रम (ring = 0; ring < adapter->max_rds_rings; ring++) अणु
		rds_ring = &recv_ctx->rds_rings[ring];
		vमुक्त(rds_ring->rx_buf_arr);
		rds_ring->rx_buf_arr = शून्य;
	पूर्ण
	kमुक्त(recv_ctx->rds_rings);
पूर्ण

पूर्णांक qlcnic_alloc_sw_resources(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_recv_context *recv_ctx;
	काष्ठा qlcnic_host_rds_ring *rds_ring;
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	काष्ठा qlcnic_rx_buffer *rx_buf;
	पूर्णांक ring, i;

	recv_ctx = adapter->recv_ctx;

	rds_ring = kसुस्मृति(adapter->max_rds_rings,
			   माप(काष्ठा qlcnic_host_rds_ring), GFP_KERNEL);
	अगर (rds_ring == शून्य)
		जाओ err_out;

	recv_ctx->rds_rings = rds_ring;

	क्रम (ring = 0; ring < adapter->max_rds_rings; ring++) अणु
		rds_ring = &recv_ctx->rds_rings[ring];
		चयन (ring) अणु
		हाल RCV_RING_NORMAL:
			rds_ring->num_desc = adapter->num_rxd;
			rds_ring->dma_size = QLCNIC_P3P_RX_BUF_MAX_LEN;
			rds_ring->skb_size = rds_ring->dma_size + NET_IP_ALIGN;
			अवरोध;

		हाल RCV_RING_JUMBO:
			rds_ring->num_desc = adapter->num_jumbo_rxd;
			rds_ring->dma_size =
				QLCNIC_P3P_RX_JUMBO_BUF_MAX_LEN;

			अगर (adapter->ahw->capabilities &
			    QLCNIC_FW_CAPABILITY_HW_LRO)
				rds_ring->dma_size += QLCNIC_LRO_BUFFER_EXTRA;

			rds_ring->skb_size =
				rds_ring->dma_size + NET_IP_ALIGN;
			अवरोध;
		पूर्ण
		rds_ring->rx_buf_arr = vzalloc(RCV_BUFF_RINGSIZE(rds_ring));
		अगर (rds_ring->rx_buf_arr == शून्य)
			जाओ err_out;

		INIT_LIST_HEAD(&rds_ring->मुक्त_list);
		/*
		 * Now go through all of them, set reference handles
		 * and put them in the queues.
		 */
		rx_buf = rds_ring->rx_buf_arr;
		क्रम (i = 0; i < rds_ring->num_desc; i++) अणु
			list_add_tail(&rx_buf->list,
					&rds_ring->मुक्त_list);
			rx_buf->ref_handle = i;
			rx_buf++;
		पूर्ण
		spin_lock_init(&rds_ring->lock);
	पूर्ण

	क्रम (ring = 0; ring < adapter->drv_sds_rings; ring++) अणु
		sds_ring = &recv_ctx->sds_rings[ring];
		sds_ring->irq = adapter->msix_entries[ring].vector;
		sds_ring->adapter = adapter;
		sds_ring->num_desc = adapter->num_rxd;
		अगर (qlcnic_82xx_check(adapter)) अणु
			अगर (qlcnic_check_multi_tx(adapter) &&
			    !adapter->ahw->diag_test)
				sds_ring->tx_ring = &adapter->tx_ring[ring];
			अन्यथा
				sds_ring->tx_ring = &adapter->tx_ring[0];
		पूर्ण
		क्रम (i = 0; i < NUM_RCV_DESC_RINGS; i++)
			INIT_LIST_HEAD(&sds_ring->मुक्त_list[i]);
	पूर्ण

	वापस 0;

err_out:
	qlcnic_मुक्त_sw_resources(adapter);
	वापस -ENOMEM;
पूर्ण

/*
 * Utility to translate from पूर्णांकernal Phantom CRB address
 * to बाह्यal PCI CRB address.
 */
अटल u32 qlcnic_decode_crb_addr(u32 addr)
अणु
	पूर्णांक i;
	u32 base_addr, offset, pci_base;

	crb_addr_transक्रमm_setup();

	pci_base = QLCNIC_ADDR_ERROR;
	base_addr = addr & 0xfff00000;
	offset = addr & 0x000fffff;

	क्रम (i = 0; i < QLCNIC_MAX_CRB_XFORM; i++) अणु
		अगर (crb_addr_xक्रमm[i] == base_addr) अणु
			pci_base = i << 20;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (pci_base == QLCNIC_ADDR_ERROR)
		वापस pci_base;
	अन्यथा
		वापस pci_base + offset;
पूर्ण

#घोषणा QLCNIC_MAX_ROM_WAIT_USEC	100

अटल पूर्णांक qlcnic_रुको_rom_करोne(काष्ठा qlcnic_adapter *adapter)
अणु
	दीर्घ समयout = 0;
	दीर्घ करोne = 0;
	पूर्णांक err = 0;

	cond_resched();
	जबतक (करोne == 0) अणु
		करोne = QLCRD32(adapter, QLCNIC_ROMUSB_GLB_STATUS, &err);
		करोne &= 2;
		अगर (++समयout >= QLCNIC_MAX_ROM_WAIT_USEC) अणु
			dev_err(&adapter->pdev->dev,
				"Timeout reached  waiting for rom done");
			वापस -EIO;
		पूर्ण
		udelay(1);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक करो_rom_fast_पढ़ो(काष्ठा qlcnic_adapter *adapter,
			    u32 addr, u32 *valp)
अणु
	पूर्णांक err = 0;

	QLCWR32(adapter, QLCNIC_ROMUSB_ROM_ADDRESS, addr);
	QLCWR32(adapter, QLCNIC_ROMUSB_ROM_DUMMY_BYTE_CNT, 0);
	QLCWR32(adapter, QLCNIC_ROMUSB_ROM_ABYTE_CNT, 3);
	QLCWR32(adapter, QLCNIC_ROMUSB_ROM_INSTR_OPCODE, 0xb);
	अगर (qlcnic_रुको_rom_करोne(adapter)) अणु
		dev_err(&adapter->pdev->dev, "Error waiting for rom done\n");
		वापस -EIO;
	पूर्ण
	/* reset abyte_cnt and dummy_byte_cnt */
	QLCWR32(adapter, QLCNIC_ROMUSB_ROM_ABYTE_CNT, 0);
	udelay(10);
	QLCWR32(adapter, QLCNIC_ROMUSB_ROM_DUMMY_BYTE_CNT, 0);

	*valp = QLCRD32(adapter, QLCNIC_ROMUSB_ROM_RDATA, &err);
	अगर (err == -EIO)
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक करो_rom_fast_पढ़ो_words(काष्ठा qlcnic_adapter *adapter, पूर्णांक addr,
				  u8 *bytes, माप_प्रकार size)
अणु
	पूर्णांक addridx;
	पूर्णांक ret = 0;

	क्रम (addridx = addr; addridx < (addr + size); addridx += 4) अणु
		पूर्णांक v;
		ret = करो_rom_fast_पढ़ो(adapter, addridx, &v);
		अगर (ret != 0)
			अवरोध;
		*(__le32 *)bytes = cpu_to_le32(v);
		bytes += 4;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक
qlcnic_rom_fast_पढ़ो_words(काष्ठा qlcnic_adapter *adapter, पूर्णांक addr,
				u8 *bytes, माप_प्रकार size)
अणु
	पूर्णांक ret;

	ret = qlcnic_rom_lock(adapter);
	अगर (ret < 0)
		वापस ret;

	ret = करो_rom_fast_पढ़ो_words(adapter, addr, bytes, size);

	qlcnic_rom_unlock(adapter);
	वापस ret;
पूर्ण

पूर्णांक qlcnic_rom_fast_पढ़ो(काष्ठा qlcnic_adapter *adapter, u32 addr, u32 *valp)
अणु
	पूर्णांक ret;

	अगर (qlcnic_rom_lock(adapter) != 0)
		वापस -EIO;

	ret = करो_rom_fast_पढ़ो(adapter, addr, valp);
	qlcnic_rom_unlock(adapter);
	वापस ret;
पूर्ण

पूर्णांक qlcnic_pinit_from_rom(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक addr, err = 0;
	पूर्णांक i, n, init_delay;
	काष्ठा crb_addr_pair *buf;
	अचिन्हित offset;
	u32 off, val;
	काष्ठा pci_dev *pdev = adapter->pdev;

	QLC_SHARED_REG_WR32(adapter, QLCNIC_CMDPEG_STATE, 0);
	QLC_SHARED_REG_WR32(adapter, QLCNIC_RCVPEG_STATE, 0);

	/* Halt all the inभागiual PEGs and other blocks */
	/* disable all I2Q */
	QLCWR32(adapter, QLCNIC_CRB_I2Q + 0x10, 0x0);
	QLCWR32(adapter, QLCNIC_CRB_I2Q + 0x14, 0x0);
	QLCWR32(adapter, QLCNIC_CRB_I2Q + 0x18, 0x0);
	QLCWR32(adapter, QLCNIC_CRB_I2Q + 0x1c, 0x0);
	QLCWR32(adapter, QLCNIC_CRB_I2Q + 0x20, 0x0);
	QLCWR32(adapter, QLCNIC_CRB_I2Q + 0x24, 0x0);

	/* disable all niu पूर्णांकerrupts */
	QLCWR32(adapter, QLCNIC_CRB_NIU + 0x40, 0xff);
	/* disable xge rx/tx */
	QLCWR32(adapter, QLCNIC_CRB_NIU + 0x70000, 0x00);
	/* disable xg1 rx/tx */
	QLCWR32(adapter, QLCNIC_CRB_NIU + 0x80000, 0x00);
	/* disable sideband mac */
	QLCWR32(adapter, QLCNIC_CRB_NIU + 0x90000, 0x00);
	/* disable ap0 mac */
	QLCWR32(adapter, QLCNIC_CRB_NIU + 0xa0000, 0x00);
	/* disable ap1 mac */
	QLCWR32(adapter, QLCNIC_CRB_NIU + 0xb0000, 0x00);

	/* halt sre */
	val = QLCRD32(adapter, QLCNIC_CRB_SRE + 0x1000, &err);
	अगर (err == -EIO)
		वापस err;
	QLCWR32(adapter, QLCNIC_CRB_SRE + 0x1000, val & (~(0x1)));

	/* halt epg */
	QLCWR32(adapter, QLCNIC_CRB_EPG + 0x1300, 0x1);

	/* halt समयrs */
	QLCWR32(adapter, QLCNIC_CRB_TIMER + 0x0, 0x0);
	QLCWR32(adapter, QLCNIC_CRB_TIMER + 0x8, 0x0);
	QLCWR32(adapter, QLCNIC_CRB_TIMER + 0x10, 0x0);
	QLCWR32(adapter, QLCNIC_CRB_TIMER + 0x18, 0x0);
	QLCWR32(adapter, QLCNIC_CRB_TIMER + 0x100, 0x0);
	QLCWR32(adapter, QLCNIC_CRB_TIMER + 0x200, 0x0);
	/* halt pegs */
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_0 + 0x3c, 1);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_1 + 0x3c, 1);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_2 + 0x3c, 1);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_3 + 0x3c, 1);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_4 + 0x3c, 1);
	msleep(20);

	qlcnic_rom_unlock(adapter);
	/* big hammer करोn't reset CAM block on reset */
	QLCWR32(adapter, QLCNIC_ROMUSB_GLB_SW_RESET, 0xfeffffff);

	/* Init HW CRB block */
	अगर (qlcnic_rom_fast_पढ़ो(adapter, 0, &n) != 0 || (n != 0xcafecafe) ||
			qlcnic_rom_fast_पढ़ो(adapter, 4, &n) != 0) अणु
		dev_err(&pdev->dev, "ERROR Reading crb_init area: val:%x\n", n);
		वापस -EIO;
	पूर्ण
	offset = n & 0xffffU;
	n = (n >> 16) & 0xffffU;

	अगर (n >= 1024) अणु
		dev_err(&pdev->dev, "QLOGIC card flash not initialized.\n");
		वापस -EIO;
	पूर्ण

	buf = kसुस्मृति(n, माप(काष्ठा crb_addr_pair), GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < n; i++) अणु
		अगर (qlcnic_rom_fast_पढ़ो(adapter, 8*i + 4*offset, &val) != 0 ||
		qlcnic_rom_fast_पढ़ो(adapter, 8*i + 4*offset + 4, &addr) != 0) अणु
			kमुक्त(buf);
			वापस -EIO;
		पूर्ण

		buf[i].addr = addr;
		buf[i].data = val;
	पूर्ण

	क्रम (i = 0; i < n; i++) अणु

		off = qlcnic_decode_crb_addr(buf[i].addr);
		अगर (off == QLCNIC_ADDR_ERROR) अणु
			dev_err(&pdev->dev, "CRB init value out of range %x\n",
					buf[i].addr);
			जारी;
		पूर्ण
		off += QLCNIC_PCI_CRBSPACE;

		अगर (off & 1)
			जारी;

		/* skipping cold reboot MAGIC */
		अगर (off == QLCNIC_CAM_RAM(0x1fc))
			जारी;
		अगर (off == (QLCNIC_CRB_I2C0 + 0x1c))
			जारी;
		अगर (off == (ROMUSB_GLB + 0xbc)) /* करो not reset PCI */
			जारी;
		अगर (off == (ROMUSB_GLB + 0xa8))
			जारी;
		अगर (off == (ROMUSB_GLB + 0xc8)) /* core घड़ी */
			जारी;
		अगर (off == (ROMUSB_GLB + 0x24)) /* MN घड़ी */
			जारी;
		अगर (off == (ROMUSB_GLB + 0x1c)) /* MS घड़ी */
			जारी;
		अगर ((off & 0x0ff00000) == QLCNIC_CRB_DDR_NET)
			जारी;
		/* skip the function enable रेजिस्टर */
		अगर (off == QLCNIC_PCIE_REG(PCIE_SETUP_FUNCTION))
			जारी;
		अगर (off == QLCNIC_PCIE_REG(PCIE_SETUP_FUNCTION2))
			जारी;
		अगर ((off & 0x0ff00000) == QLCNIC_CRB_SMB)
			जारी;

		init_delay = 1;
		/* After writing this रेजिस्टर, HW needs समय क्रम CRB */
		/* to quiet करोwn (अन्यथा crb_winकरोw वापसs 0xffffffff) */
		अगर (off == QLCNIC_ROMUSB_GLB_SW_RESET)
			init_delay = 1000;

		QLCWR32(adapter, off, buf[i].data);

		msleep(init_delay);
	पूर्ण
	kमुक्त(buf);

	/* Initialize protocol process engine */
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_D + 0xec, 0x1e);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_D + 0x4c, 8);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_I + 0x4c, 8);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_0 + 0x8, 0);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_0 + 0xc, 0);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_1 + 0x8, 0);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_1 + 0xc, 0);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_2 + 0x8, 0);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_2 + 0xc, 0);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_3 + 0x8, 0);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_3 + 0xc, 0);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_4 + 0x8, 0);
	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_4 + 0xc, 0);
	usleep_range(1000, 1500);

	QLC_SHARED_REG_WR32(adapter, QLCNIC_PEG_HALT_STATUS1, 0);
	QLC_SHARED_REG_WR32(adapter, QLCNIC_PEG_HALT_STATUS2, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_cmd_peg_पढ़ोy(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 val;
	पूर्णांक retries = QLCNIC_CMDPEG_CHECK_RETRY_COUNT;

	करो अणु
		val = QLC_SHARED_REG_RD32(adapter, QLCNIC_CMDPEG_STATE);

		चयन (val) अणु
		हाल PHAN_INITIALIZE_COMPLETE:
		हाल PHAN_INITIALIZE_ACK:
			वापस 0;
		हाल PHAN_INITIALIZE_FAILED:
			जाओ out_err;
		शेष:
			अवरोध;
		पूर्ण

		msleep(QLCNIC_CMDPEG_CHECK_DELAY);

	पूर्ण जबतक (--retries);

	QLC_SHARED_REG_WR32(adapter, QLCNIC_CMDPEG_STATE,
			    PHAN_INITIALIZE_FAILED);

out_err:
	dev_err(&adapter->pdev->dev, "Command Peg initialization not "
		      "complete, state: 0x%x.\n", val);
	वापस -EIO;
पूर्ण

अटल पूर्णांक
qlcnic_receive_peg_पढ़ोy(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 val;
	पूर्णांक retries = QLCNIC_RCVPEG_CHECK_RETRY_COUNT;

	करो अणु
		val = QLC_SHARED_REG_RD32(adapter, QLCNIC_RCVPEG_STATE);

		अगर (val == PHAN_PEG_RCV_INITIALIZED)
			वापस 0;

		msleep(QLCNIC_RCVPEG_CHECK_DELAY);

	पूर्ण जबतक (--retries);

	dev_err(&adapter->pdev->dev, "Receive Peg initialization not complete, state: 0x%x.\n",
		val);
	वापस -EIO;
पूर्ण

पूर्णांक
qlcnic_check_fw_status(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक err;

	err = qlcnic_cmd_peg_पढ़ोy(adapter);
	अगर (err)
		वापस err;

	err = qlcnic_receive_peg_पढ़ोy(adapter);
	अगर (err)
		वापस err;

	QLC_SHARED_REG_WR32(adapter, QLCNIC_CMDPEG_STATE, PHAN_INITIALIZE_ACK);

	वापस err;
पूर्ण

पूर्णांक
qlcnic_setup_idc_param(काष्ठा qlcnic_adapter *adapter) अणु

	पूर्णांक समयo;
	u32 val;

	val = QLC_SHARED_REG_RD32(adapter, QLCNIC_CRB_DEV_PARTITION_INFO);
	val = QLC_DEV_GET_DRV(val, adapter->portnum);
	अगर ((val & 0x3) != QLCNIC_TYPE_NIC) अणु
		dev_err(&adapter->pdev->dev,
			"Not an Ethernet NIC func=%u\n", val);
		वापस -EIO;
	पूर्ण
	adapter->ahw->physical_port = (val >> 2);
	अगर (qlcnic_rom_fast_पढ़ो(adapter, QLCNIC_ROM_DEV_INIT_TIMEOUT, &समयo))
		समयo = QLCNIC_INIT_TIMEOUT_SECS;

	adapter->dev_init_समयo = समयo;

	अगर (qlcnic_rom_fast_पढ़ो(adapter, QLCNIC_ROM_DRV_RESET_TIMEOUT, &समयo))
		समयo = QLCNIC_RESET_TIMEOUT_SECS;

	adapter->reset_ack_समयo = समयo;

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_get_flt_entry(काष्ठा qlcnic_adapter *adapter, u8 region,
				काष्ठा qlcnic_flt_entry *region_entry)
अणु
	काष्ठा qlcnic_flt_header flt_hdr;
	काष्ठा qlcnic_flt_entry *flt_entry;
	पूर्णांक i = 0, ret;
	u32 entry_size;

	स_रखो(region_entry, 0, माप(काष्ठा qlcnic_flt_entry));
	ret = qlcnic_rom_fast_पढ़ो_words(adapter, QLCNIC_FLT_LOCATION,
					 (u8 *)&flt_hdr,
					 माप(काष्ठा qlcnic_flt_header));
	अगर (ret) अणु
		dev_warn(&adapter->pdev->dev,
			 "error reading flash layout header\n");
		वापस -EIO;
	पूर्ण

	entry_size = flt_hdr.len - माप(काष्ठा qlcnic_flt_header);
	flt_entry = vzalloc(entry_size);
	अगर (flt_entry == शून्य)
		वापस -EIO;

	ret = qlcnic_rom_fast_पढ़ो_words(adapter, QLCNIC_FLT_LOCATION +
					 माप(काष्ठा qlcnic_flt_header),
					 (u8 *)flt_entry, entry_size);
	अगर (ret) अणु
		dev_warn(&adapter->pdev->dev,
			 "error reading flash layout entries\n");
		जाओ err_out;
	पूर्ण

	जबतक (i < (entry_size/माप(काष्ठा qlcnic_flt_entry))) अणु
		अगर (flt_entry[i].region == region)
			अवरोध;
		i++;
	पूर्ण
	अगर (i >= (entry_size/माप(काष्ठा qlcnic_flt_entry))) अणु
		dev_warn(&adapter->pdev->dev,
			 "region=%x not found in %d regions\n", region, i);
		ret = -EIO;
		जाओ err_out;
	पूर्ण
	स_नकल(region_entry, &flt_entry[i], माप(काष्ठा qlcnic_flt_entry));

err_out:
	vमुक्त(flt_entry);
	वापस ret;
पूर्ण

पूर्णांक
qlcnic_check_flash_fw_ver(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_flt_entry fw_entry;
	u32 ver = -1, min_ver;
	पूर्णांक ret;

	अगर (adapter->ahw->revision_id == QLCNIC_P3P_C0)
		ret = qlcnic_get_flt_entry(adapter, QLCNIC_C0_FW_IMAGE_REGION,
						 &fw_entry);
	अन्यथा
		ret = qlcnic_get_flt_entry(adapter, QLCNIC_B0_FW_IMAGE_REGION,
						 &fw_entry);

	अगर (!ret)
		/* 0-4:-signature,  4-8:-fw version */
		qlcnic_rom_fast_पढ़ो(adapter, fw_entry.start_addr + 4,
				     (पूर्णांक *)&ver);
	अन्यथा
		qlcnic_rom_fast_पढ़ो(adapter, QLCNIC_FW_VERSION_OFFSET,
				     (पूर्णांक *)&ver);

	ver = QLCNIC_DECODE_VERSION(ver);
	min_ver = QLCNIC_MIN_FW_VERSION;

	अगर (ver < min_ver) अणु
		dev_err(&adapter->pdev->dev,
			"firmware version %d.%d.%d unsupported."
			"Min supported version %d.%d.%d\n",
			_major(ver), _minor(ver), _build(ver),
			_major(min_ver), _minor(min_ver), _build(min_ver));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
qlcnic_has_mn(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 capability = 0;
	पूर्णांक err = 0;

	capability = QLCRD32(adapter, QLCNIC_PEG_TUNE_CAPABILITY, &err);
	अगर (err == -EIO)
		वापस err;
	अगर (capability & QLCNIC_PEG_TUNE_MN_PRESENT)
		वापस 1;

	वापस 0;
पूर्ण

अटल
काष्ठा uni_table_desc *qlcnic_get_table_desc(स्थिर u8 *unirom, पूर्णांक section)
अणु
	u32 i, entries;
	काष्ठा uni_table_desc *directory = (काष्ठा uni_table_desc *) &unirom[0];
	entries = le32_to_cpu(directory->num_entries);

	क्रम (i = 0; i < entries; i++) अणु

		u32 offs = le32_to_cpu(directory->findex) +
			   i * le32_to_cpu(directory->entry_size);
		u32 tab_type = le32_to_cpu(*((__le32 *)&unirom[offs] + 8));

		अगर (tab_type == section)
			वापस (काष्ठा uni_table_desc *) &unirom[offs];
	पूर्ण

	वापस शून्य;
पूर्ण

#घोषणा खाताHEADER_SIZE (14 * 4)

अटल पूर्णांक
qlcnic_validate_header(काष्ठा qlcnic_adapter *adapter)
अणु
	स्थिर u8 *unirom = adapter->fw->data;
	काष्ठा uni_table_desc *directory = (काष्ठा uni_table_desc *) &unirom[0];
	u32 entries, entry_size, tab_size, fw_file_size;

	fw_file_size = adapter->fw->size;

	अगर (fw_file_size < खाताHEADER_SIZE)
		वापस -EINVAL;

	entries = le32_to_cpu(directory->num_entries);
	entry_size = le32_to_cpu(directory->entry_size);
	tab_size = le32_to_cpu(directory->findex) + (entries * entry_size);

	अगर (fw_file_size < tab_size)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक
qlcnic_validate_bootld(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा uni_table_desc *tab_desc;
	काष्ठा uni_data_desc *descr;
	u32 offs, tab_size, data_size, idx;
	स्थिर u8 *unirom = adapter->fw->data;
	__le32 temp;

	temp = *((__le32 *)&unirom[adapter->file_prd_off] +
		 QLCNIC_UNI_BOOTLD_IDX_OFF);
	idx = le32_to_cpu(temp);
	tab_desc = qlcnic_get_table_desc(unirom, QLCNIC_UNI_सूची_SECT_BOOTLD);

	अगर (!tab_desc)
		वापस -EINVAL;

	tab_size = le32_to_cpu(tab_desc->findex) +
		   le32_to_cpu(tab_desc->entry_size) * (idx + 1);

	अगर (adapter->fw->size < tab_size)
		वापस -EINVAL;

	offs = le32_to_cpu(tab_desc->findex) +
	       le32_to_cpu(tab_desc->entry_size) * idx;
	descr = (काष्ठा uni_data_desc *)&unirom[offs];

	data_size = le32_to_cpu(descr->findex) + le32_to_cpu(descr->size);

	अगर (adapter->fw->size < data_size)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक
qlcnic_validate_fw(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा uni_table_desc *tab_desc;
	काष्ठा uni_data_desc *descr;
	स्थिर u8 *unirom = adapter->fw->data;
	u32 offs, tab_size, data_size, idx;
	__le32 temp;

	temp = *((__le32 *)&unirom[adapter->file_prd_off] +
		 QLCNIC_UNI_FIRMWARE_IDX_OFF);
	idx = le32_to_cpu(temp);
	tab_desc = qlcnic_get_table_desc(unirom, QLCNIC_UNI_सूची_SECT_FW);

	अगर (!tab_desc)
		वापस -EINVAL;

	tab_size = le32_to_cpu(tab_desc->findex) +
		   le32_to_cpu(tab_desc->entry_size) * (idx + 1);

	अगर (adapter->fw->size < tab_size)
		वापस -EINVAL;

	offs = le32_to_cpu(tab_desc->findex) +
	       le32_to_cpu(tab_desc->entry_size) * idx;
	descr = (काष्ठा uni_data_desc *)&unirom[offs];
	data_size = le32_to_cpu(descr->findex) + le32_to_cpu(descr->size);

	अगर (adapter->fw->size < data_size)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक
qlcnic_validate_product_offs(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा uni_table_desc *ptab_descr;
	स्थिर u8 *unirom = adapter->fw->data;
	पूर्णांक mn_present = qlcnic_has_mn(adapter);
	u32 entries, entry_size, tab_size, i;
	__le32 temp;

	ptab_descr = qlcnic_get_table_desc(unirom,
				QLCNIC_UNI_सूची_SECT_PRODUCT_TBL);
	अगर (!ptab_descr)
		वापस -EINVAL;

	entries = le32_to_cpu(ptab_descr->num_entries);
	entry_size = le32_to_cpu(ptab_descr->entry_size);
	tab_size = le32_to_cpu(ptab_descr->findex) + (entries * entry_size);

	अगर (adapter->fw->size < tab_size)
		वापस -EINVAL;

nomn:
	क्रम (i = 0; i < entries; i++) अणु

		u32 flags, file_chiprev, offs;
		u8 chiprev = adapter->ahw->revision_id;
		u32 flagbit;

		offs = le32_to_cpu(ptab_descr->findex) +
		       i * le32_to_cpu(ptab_descr->entry_size);
		temp = *((__le32 *)&unirom[offs] + QLCNIC_UNI_FLAGS_OFF);
		flags = le32_to_cpu(temp);
		temp = *((__le32 *)&unirom[offs] + QLCNIC_UNI_CHIP_REV_OFF);
		file_chiprev = le32_to_cpu(temp);

		flagbit = mn_present ? 1 : 2;

		अगर ((chiprev == file_chiprev) &&
					((1ULL << flagbit) & flags)) अणु
			adapter->file_prd_off = offs;
			वापस 0;
		पूर्ण
	पूर्ण
	अगर (mn_present) अणु
		mn_present = 0;
		जाओ nomn;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
qlcnic_validate_unअगरied_romimage(काष्ठा qlcnic_adapter *adapter)
अणु
	अगर (qlcnic_validate_header(adapter)) अणु
		dev_err(&adapter->pdev->dev,
				"unified image: header validation failed\n");
		वापस -EINVAL;
	पूर्ण

	अगर (qlcnic_validate_product_offs(adapter)) अणु
		dev_err(&adapter->pdev->dev,
				"unified image: product validation failed\n");
		वापस -EINVAL;
	पूर्ण

	अगर (qlcnic_validate_bootld(adapter)) अणु
		dev_err(&adapter->pdev->dev,
				"unified image: bootld validation failed\n");
		वापस -EINVAL;
	पूर्ण

	अगर (qlcnic_validate_fw(adapter)) अणु
		dev_err(&adapter->pdev->dev,
				"unified image: firmware validation failed\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल
काष्ठा uni_data_desc *qlcnic_get_data_desc(काष्ठा qlcnic_adapter *adapter,
			u32 section, u32 idx_offset)
अणु
	स्थिर u8 *unirom = adapter->fw->data;
	काष्ठा uni_table_desc *tab_desc;
	u32 offs, idx;
	__le32 temp;

	temp = *((__le32 *)&unirom[adapter->file_prd_off] + idx_offset);
	idx = le32_to_cpu(temp);

	tab_desc = qlcnic_get_table_desc(unirom, section);

	अगर (tab_desc == शून्य)
		वापस शून्य;

	offs = le32_to_cpu(tab_desc->findex) +
	       le32_to_cpu(tab_desc->entry_size) * idx;

	वापस (काष्ठा uni_data_desc *)&unirom[offs];
पूर्ण

अटल u8 *
qlcnic_get_bootld_offs(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 offs = QLCNIC_BOOTLD_START;
	काष्ठा uni_data_desc *data_desc;

	data_desc = qlcnic_get_data_desc(adapter, QLCNIC_UNI_सूची_SECT_BOOTLD,
					 QLCNIC_UNI_BOOTLD_IDX_OFF);

	अगर (adapter->ahw->fw_type == QLCNIC_UNIFIED_ROMIMAGE)
		offs = le32_to_cpu(data_desc->findex);

	वापस (u8 *)&adapter->fw->data[offs];
पूर्ण

अटल u8 *
qlcnic_get_fw_offs(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 offs = QLCNIC_IMAGE_START;
	काष्ठा uni_data_desc *data_desc;

	data_desc = qlcnic_get_data_desc(adapter, QLCNIC_UNI_सूची_SECT_FW,
					 QLCNIC_UNI_FIRMWARE_IDX_OFF);
	अगर (adapter->ahw->fw_type == QLCNIC_UNIFIED_ROMIMAGE)
		offs = le32_to_cpu(data_desc->findex);

	वापस (u8 *)&adapter->fw->data[offs];
पूर्ण

अटल u32 qlcnic_get_fw_size(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा uni_data_desc *data_desc;
	स्थिर u8 *unirom = adapter->fw->data;

	data_desc = qlcnic_get_data_desc(adapter, QLCNIC_UNI_सूची_SECT_FW,
					 QLCNIC_UNI_FIRMWARE_IDX_OFF);

	अगर (adapter->ahw->fw_type == QLCNIC_UNIFIED_ROMIMAGE)
		वापस le32_to_cpu(data_desc->size);
	अन्यथा
		वापस le32_to_cpu(*(__le32 *)&unirom[QLCNIC_FW_SIZE_OFFSET]);
पूर्ण

अटल u32 qlcnic_get_fw_version(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा uni_data_desc *fw_data_desc;
	स्थिर काष्ठा firmware *fw = adapter->fw;
	u32 major, minor, sub;
	__le32 version_offset;
	स्थिर u8 *ver_str;
	पूर्णांक i, ret;

	अगर (adapter->ahw->fw_type != QLCNIC_UNIFIED_ROMIMAGE) अणु
		version_offset = *(__le32 *)&fw->data[QLCNIC_FW_VERSION_OFFSET];
		वापस le32_to_cpu(version_offset);
	पूर्ण

	fw_data_desc = qlcnic_get_data_desc(adapter, QLCNIC_UNI_सूची_SECT_FW,
			QLCNIC_UNI_FIRMWARE_IDX_OFF);
	ver_str = fw->data + le32_to_cpu(fw_data_desc->findex) +
		  le32_to_cpu(fw_data_desc->size) - 17;

	क्रम (i = 0; i < 12; i++) अणु
		अगर (!म_भेदन(&ver_str[i], "REV=", 4)) अणु
			ret = माला_पूछो(&ver_str[i+4], "%u.%u.%u ",
					&major, &minor, &sub);
			अगर (ret != 3)
				वापस 0;
			अन्यथा
				वापस major + (minor << 8) + (sub << 16);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 qlcnic_get_bios_version(काष्ठा qlcnic_adapter *adapter)
अणु
	स्थिर काष्ठा firmware *fw = adapter->fw;
	u32 bios_ver, prd_off = adapter->file_prd_off;
	u8 *version_offset;
	__le32 temp;

	अगर (adapter->ahw->fw_type != QLCNIC_UNIFIED_ROMIMAGE) अणु
		version_offset = (u8 *)&fw->data[QLCNIC_BIOS_VERSION_OFFSET];
		वापस le32_to_cpu(*(__le32 *)version_offset);
	पूर्ण

	temp = *((__le32 *)(&fw->data[prd_off]) + QLCNIC_UNI_BIOS_VERSION_OFF);
	bios_ver = le32_to_cpu(temp);

	वापस (bios_ver << 16) + ((bios_ver >> 8) & 0xff00) + (bios_ver >> 24);
पूर्ण

अटल व्योम qlcnic_rom_lock_recovery(काष्ठा qlcnic_adapter *adapter)
अणु
	अगर (qlcnic_pcie_sem_lock(adapter, 2, QLCNIC_ROM_LOCK_ID))
		dev_info(&adapter->pdev->dev, "Resetting rom_lock\n");

	qlcnic_pcie_sem_unlock(adapter, 2);
पूर्ण

अटल पूर्णांक
qlcnic_check_fw_hearbeat(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 heartbeat, ret = -EIO;
	पूर्णांक retries = QLCNIC_HEARTBEAT_CHECK_RETRY_COUNT;

	adapter->heartbeat = QLC_SHARED_REG_RD32(adapter,
						 QLCNIC_PEG_ALIVE_COUNTER);

	करो अणु
		msleep(QLCNIC_HEARTBEAT_PERIOD_MSECS);
		heartbeat = QLC_SHARED_REG_RD32(adapter,
						QLCNIC_PEG_ALIVE_COUNTER);
		अगर (heartbeat != adapter->heartbeat) अणु
			ret = QLCNIC_RCODE_SUCCESS;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (--retries);

	वापस ret;
पूर्ण

पूर्णांक
qlcnic_need_fw_reset(काष्ठा qlcnic_adapter *adapter)
अणु
	अगर ((adapter->flags & QLCNIC_FW_HANG) ||
			qlcnic_check_fw_hearbeat(adapter)) अणु
		qlcnic_rom_lock_recovery(adapter);
		वापस 1;
	पूर्ण

	अगर (adapter->need_fw_reset)
		वापस 1;

	अगर (adapter->fw)
		वापस 1;

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *fw_name[] = अणु
	QLCNIC_UNIFIED_ROMIMAGE_NAME,
	QLCNIC_FLASH_ROMIMAGE_NAME,
पूर्ण;

पूर्णांक
qlcnic_load_firmware(काष्ठा qlcnic_adapter *adapter)
अणु
	__le64 *ptr64;
	u32 i, flashaddr, size;
	स्थिर काष्ठा firmware *fw = adapter->fw;
	काष्ठा pci_dev *pdev = adapter->pdev;

	dev_info(&pdev->dev, "loading firmware from %s\n",
		 fw_name[adapter->ahw->fw_type]);

	अगर (fw) अणु
		u64 data;

		size = (QLCNIC_IMAGE_START - QLCNIC_BOOTLD_START) / 8;

		ptr64 = (__le64 *)qlcnic_get_bootld_offs(adapter);
		flashaddr = QLCNIC_BOOTLD_START;

		क्रम (i = 0; i < size; i++) अणु
			data = le64_to_cpu(ptr64[i]);

			अगर (qlcnic_pci_mem_ग_लिखो_2M(adapter, flashaddr, data))
				वापस -EIO;

			flashaddr += 8;
		पूर्ण

		size = qlcnic_get_fw_size(adapter) / 8;

		ptr64 = (__le64 *)qlcnic_get_fw_offs(adapter);
		flashaddr = QLCNIC_IMAGE_START;

		क्रम (i = 0; i < size; i++) अणु
			data = le64_to_cpu(ptr64[i]);

			अगर (qlcnic_pci_mem_ग_लिखो_2M(adapter,
						flashaddr, data))
				वापस -EIO;

			flashaddr += 8;
		पूर्ण

		size = qlcnic_get_fw_size(adapter) % 8;
		अगर (size) अणु
			data = le64_to_cpu(ptr64[i]);

			अगर (qlcnic_pci_mem_ग_लिखो_2M(adapter,
						flashaddr, data))
				वापस -EIO;
		पूर्ण

	पूर्ण अन्यथा अणु
		u64 data;
		u32 hi, lo;
		पूर्णांक ret;
		काष्ठा qlcnic_flt_entry bootld_entry;

		ret = qlcnic_get_flt_entry(adapter, QLCNIC_BOOTLD_REGION,
					&bootld_entry);
		अगर (!ret) अणु
			size = bootld_entry.size / 8;
			flashaddr = bootld_entry.start_addr;
		पूर्ण अन्यथा अणु
			size = (QLCNIC_IMAGE_START - QLCNIC_BOOTLD_START) / 8;
			flashaddr = QLCNIC_BOOTLD_START;
			dev_info(&pdev->dev,
				"using legacy method to get flash fw region");
		पूर्ण

		क्रम (i = 0; i < size; i++) अणु
			अगर (qlcnic_rom_fast_पढ़ो(adapter,
					flashaddr, (पूर्णांक *)&lo) != 0)
				वापस -EIO;
			अगर (qlcnic_rom_fast_पढ़ो(adapter,
					flashaddr + 4, (पूर्णांक *)&hi) != 0)
				वापस -EIO;

			data = (((u64)hi << 32) | lo);

			अगर (qlcnic_pci_mem_ग_लिखो_2M(adapter,
						flashaddr, data))
				वापस -EIO;

			flashaddr += 8;
		पूर्ण
	पूर्ण
	usleep_range(1000, 1500);

	QLCWR32(adapter, QLCNIC_CRB_PEG_NET_0 + 0x18, 0x1020);
	QLCWR32(adapter, QLCNIC_ROMUSB_GLB_SW_RESET, 0x80001e);
	वापस 0;
पूर्ण

अटल पूर्णांक
qlcnic_validate_firmware(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 val;
	u32 ver, bios, min_size;
	काष्ठा pci_dev *pdev = adapter->pdev;
	स्थिर काष्ठा firmware *fw = adapter->fw;
	u8 fw_type = adapter->ahw->fw_type;

	अगर (fw_type == QLCNIC_UNIFIED_ROMIMAGE) अणु
		अगर (qlcnic_validate_unअगरied_romimage(adapter))
			वापस -EINVAL;

		min_size = QLCNIC_UNI_FW_MIN_SIZE;
	पूर्ण अन्यथा अणु
		val = le32_to_cpu(*(__le32 *)&fw->data[QLCNIC_FW_MAGIC_OFFSET]);
		अगर (val != QLCNIC_BDINFO_MAGIC)
			वापस -EINVAL;

		min_size = QLCNIC_FW_MIN_SIZE;
	पूर्ण

	अगर (fw->size < min_size)
		वापस -EINVAL;

	val = qlcnic_get_fw_version(adapter);
	ver = QLCNIC_DECODE_VERSION(val);

	अगर (ver < QLCNIC_MIN_FW_VERSION) अणु
		dev_err(&pdev->dev,
				"%s: firmware version %d.%d.%d unsupported\n",
		fw_name[fw_type], _major(ver), _minor(ver), _build(ver));
		वापस -EINVAL;
	पूर्ण

	val = qlcnic_get_bios_version(adapter);
	qlcnic_rom_fast_पढ़ो(adapter, QLCNIC_BIOS_VERSION_OFFSET, (पूर्णांक *)&bios);
	अगर (val != bios) अणु
		dev_err(&pdev->dev, "%s: firmware bios is incompatible\n",
				fw_name[fw_type]);
		वापस -EINVAL;
	पूर्ण

	QLC_SHARED_REG_WR32(adapter, QLCNIC_FW_IMG_VALID, QLCNIC_BDINFO_MAGIC);
	वापस 0;
पूर्ण

अटल व्योम
qlcnic_get_next_fwtype(काष्ठा qlcnic_adapter *adapter)
अणु
	u8 fw_type;

	चयन (adapter->ahw->fw_type) अणु
	हाल QLCNIC_UNKNOWN_ROMIMAGE:
		fw_type = QLCNIC_UNIFIED_ROMIMAGE;
		अवरोध;

	हाल QLCNIC_UNIFIED_ROMIMAGE:
	शेष:
		fw_type = QLCNIC_FLASH_ROMIMAGE;
		अवरोध;
	पूर्ण

	adapter->ahw->fw_type = fw_type;
पूर्ण



व्योम qlcnic_request_firmware(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक rc;

	adapter->ahw->fw_type = QLCNIC_UNKNOWN_ROMIMAGE;

next:
	qlcnic_get_next_fwtype(adapter);

	अगर (adapter->ahw->fw_type == QLCNIC_FLASH_ROMIMAGE) अणु
		adapter->fw = शून्य;
	पूर्ण अन्यथा अणु
		rc = request_firmware(&adapter->fw,
				      fw_name[adapter->ahw->fw_type],
				      &pdev->dev);
		अगर (rc != 0)
			जाओ next;

		rc = qlcnic_validate_firmware(adapter);
		अगर (rc != 0) अणु
			release_firmware(adapter->fw);
			usleep_range(1000, 1500);
			जाओ next;
		पूर्ण
	पूर्ण
पूर्ण


व्योम
qlcnic_release_firmware(काष्ठा qlcnic_adapter *adapter)
अणु
	release_firmware(adapter->fw);
	adapter->fw = शून्य;
पूर्ण
