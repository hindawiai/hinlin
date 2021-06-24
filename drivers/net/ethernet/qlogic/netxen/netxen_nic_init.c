<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2003 - 2009 NetXen, Inc.
 * Copyright (C) 2009 - QLogic Corporation.
 * All rights reserved.
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/checksum.h>
#समावेश "netxen_nic.h"
#समावेश "netxen_nic_hw.h"

काष्ठा crb_addr_pair अणु
	u32 addr;
	u32 data;
पूर्ण;

#घोषणा NETXEN_MAX_CRB_XFORM 60
अटल अचिन्हित पूर्णांक crb_addr_xक्रमm[NETXEN_MAX_CRB_XFORM];
#घोषणा NETXEN_ADDR_ERROR (0xffffffff)

#घोषणा crb_addr_transक्रमm(name) \
	crb_addr_xक्रमm[NETXEN_HW_PX_MAP_CRB_##name] = \
	NETXEN_HW_CRB_HUB_AGT_ADR_##name << 20

#घोषणा NETXEN_NIC_XDMA_RESET 0x8000ff

अटल व्योम
netxen_post_rx_buffers_nodb(काष्ठा netxen_adapter *adapter,
		काष्ठा nx_host_rds_ring *rds_ring);
अटल पूर्णांक netxen_p3_has_mn(काष्ठा netxen_adapter *adapter);

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

व्योम netxen_release_rx_buffers(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा netxen_recv_context *recv_ctx;
	काष्ठा nx_host_rds_ring *rds_ring;
	काष्ठा netxen_rx_buffer *rx_buf;
	पूर्णांक i, ring;

	recv_ctx = &adapter->recv_ctx;
	क्रम (ring = 0; ring < adapter->max_rds_rings; ring++) अणु
		rds_ring = &recv_ctx->rds_rings[ring];
		क्रम (i = 0; i < rds_ring->num_desc; ++i) अणु
			rx_buf = &(rds_ring->rx_buf_arr[i]);
			अगर (rx_buf->state == NETXEN_BUFFER_FREE)
				जारी;
			dma_unmap_single(&adapter->pdev->dev, rx_buf->dma,
					 rds_ring->dma_size, DMA_FROM_DEVICE);
			अगर (rx_buf->skb != शून्य)
				dev_kमुक्त_skb_any(rx_buf->skb);
		पूर्ण
	पूर्ण
पूर्ण

व्योम netxen_release_tx_buffers(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा netxen_cmd_buffer *cmd_buf;
	काष्ठा netxen_skb_frag *buffrag;
	पूर्णांक i, j;
	काष्ठा nx_host_tx_ring *tx_ring = adapter->tx_ring;

	spin_lock_bh(&adapter->tx_clean_lock);
	cmd_buf = tx_ring->cmd_buf_arr;
	क्रम (i = 0; i < tx_ring->num_desc; i++) अणु
		buffrag = cmd_buf->frag_array;
		अगर (buffrag->dma) अणु
			dma_unmap_single(&adapter->pdev->dev, buffrag->dma,
					 buffrag->length, DMA_TO_DEVICE);
			buffrag->dma = 0ULL;
		पूर्ण
		क्रम (j = 1; j < cmd_buf->frag_count; j++) अणु
			buffrag++;
			अगर (buffrag->dma) अणु
				dma_unmap_page(&adapter->pdev->dev,
					       buffrag->dma, buffrag->length,
					       DMA_TO_DEVICE);
				buffrag->dma = 0ULL;
			पूर्ण
		पूर्ण
		अगर (cmd_buf->skb) अणु
			dev_kमुक्त_skb_any(cmd_buf->skb);
			cmd_buf->skb = शून्य;
		पूर्ण
		cmd_buf++;
	पूर्ण
	spin_unlock_bh(&adapter->tx_clean_lock);
पूर्ण

व्योम netxen_मुक्त_sw_resources(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा netxen_recv_context *recv_ctx;
	काष्ठा nx_host_rds_ring *rds_ring;
	काष्ठा nx_host_tx_ring *tx_ring;
	पूर्णांक ring;

	recv_ctx = &adapter->recv_ctx;

	अगर (recv_ctx->rds_rings == शून्य)
		जाओ skip_rds;

	क्रम (ring = 0; ring < adapter->max_rds_rings; ring++) अणु
		rds_ring = &recv_ctx->rds_rings[ring];
		vमुक्त(rds_ring->rx_buf_arr);
		rds_ring->rx_buf_arr = शून्य;
	पूर्ण
	kमुक्त(recv_ctx->rds_rings);

skip_rds:
	अगर (adapter->tx_ring == शून्य)
		वापस;

	tx_ring = adapter->tx_ring;
	vमुक्त(tx_ring->cmd_buf_arr);
	kमुक्त(tx_ring);
	adapter->tx_ring = शून्य;
पूर्ण

पूर्णांक netxen_alloc_sw_resources(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा netxen_recv_context *recv_ctx;
	काष्ठा nx_host_rds_ring *rds_ring;
	काष्ठा nx_host_sds_ring *sds_ring;
	काष्ठा nx_host_tx_ring *tx_ring;
	काष्ठा netxen_rx_buffer *rx_buf;
	पूर्णांक ring, i;

	काष्ठा netxen_cmd_buffer *cmd_buf_arr;
	काष्ठा net_device *netdev = adapter->netdev;

	tx_ring = kzalloc(माप(काष्ठा nx_host_tx_ring), GFP_KERNEL);
	अगर (tx_ring == शून्य)
		वापस -ENOMEM;

	adapter->tx_ring = tx_ring;

	tx_ring->num_desc = adapter->num_txd;
	tx_ring->txq = netdev_get_tx_queue(netdev, 0);

	cmd_buf_arr = vzalloc(TX_BUFF_RINGSIZE(tx_ring));
	अगर (cmd_buf_arr == शून्य)
		जाओ err_out;

	tx_ring->cmd_buf_arr = cmd_buf_arr;

	recv_ctx = &adapter->recv_ctx;

	rds_ring = kसुस्मृति(adapter->max_rds_rings,
			   माप(काष्ठा nx_host_rds_ring), GFP_KERNEL);
	अगर (rds_ring == शून्य)
		जाओ err_out;

	recv_ctx->rds_rings = rds_ring;

	क्रम (ring = 0; ring < adapter->max_rds_rings; ring++) अणु
		rds_ring = &recv_ctx->rds_rings[ring];
		चयन (ring) अणु
		हाल RCV_RING_NORMAL:
			rds_ring->num_desc = adapter->num_rxd;
			अगर (adapter->ahw.cut_through) अणु
				rds_ring->dma_size =
					NX_CT_DEFAULT_RX_BUF_LEN;
				rds_ring->skb_size =
					NX_CT_DEFAULT_RX_BUF_LEN;
			पूर्ण अन्यथा अणु
				अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id))
					rds_ring->dma_size =
						NX_P3_RX_BUF_MAX_LEN;
				अन्यथा
					rds_ring->dma_size =
						NX_P2_RX_BUF_MAX_LEN;
				rds_ring->skb_size =
					rds_ring->dma_size + NET_IP_ALIGN;
			पूर्ण
			अवरोध;

		हाल RCV_RING_JUMBO:
			rds_ring->num_desc = adapter->num_jumbo_rxd;
			अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id))
				rds_ring->dma_size =
					NX_P3_RX_JUMBO_BUF_MAX_LEN;
			अन्यथा
				rds_ring->dma_size =
					NX_P2_RX_JUMBO_BUF_MAX_LEN;

			अगर (adapter->capabilities & NX_CAP0_HW_LRO)
				rds_ring->dma_size += NX_LRO_BUFFER_EXTRA;

			rds_ring->skb_size =
				rds_ring->dma_size + NET_IP_ALIGN;
			अवरोध;

		हाल RCV_RING_LRO:
			rds_ring->num_desc = adapter->num_lro_rxd;
			rds_ring->dma_size = NX_RX_LRO_BUFFER_LENGTH;
			rds_ring->skb_size = rds_ring->dma_size + NET_IP_ALIGN;
			अवरोध;

		पूर्ण
		rds_ring->rx_buf_arr = vzalloc(RCV_BUFF_RINGSIZE(rds_ring));
		अगर (rds_ring->rx_buf_arr == शून्य)
			/* मुक्त whatever was alपढ़ोy allocated */
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
			rx_buf->state = NETXEN_BUFFER_FREE;
			rx_buf++;
		पूर्ण
		spin_lock_init(&rds_ring->lock);
	पूर्ण

	क्रम (ring = 0; ring < adapter->max_sds_rings; ring++) अणु
		sds_ring = &recv_ctx->sds_rings[ring];
		sds_ring->irq = adapter->msix_entries[ring].vector;
		sds_ring->adapter = adapter;
		sds_ring->num_desc = adapter->num_rxd;

		क्रम (i = 0; i < NUM_RCV_DESC_RINGS; i++)
			INIT_LIST_HEAD(&sds_ring->मुक्त_list[i]);
	पूर्ण

	वापस 0;

err_out:
	netxen_मुक्त_sw_resources(adapter);
	वापस -ENOMEM;
पूर्ण

/*
 * netxen_decode_crb_addr(0 - utility to translate from पूर्णांकernal Phantom CRB
 * address to बाह्यal PCI CRB address.
 */
अटल u32 netxen_decode_crb_addr(u32 addr)
अणु
	पूर्णांक i;
	u32 base_addr, offset, pci_base;

	crb_addr_transक्रमm_setup();

	pci_base = NETXEN_ADDR_ERROR;
	base_addr = addr & 0xfff00000;
	offset = addr & 0x000fffff;

	क्रम (i = 0; i < NETXEN_MAX_CRB_XFORM; i++) अणु
		अगर (crb_addr_xक्रमm[i] == base_addr) अणु
			pci_base = i << 20;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (pci_base == NETXEN_ADDR_ERROR)
		वापस pci_base;
	अन्यथा
		वापस pci_base + offset;
पूर्ण

#घोषणा NETXEN_MAX_ROM_WAIT_USEC	100

अटल पूर्णांक netxen_रुको_rom_करोne(काष्ठा netxen_adapter *adapter)
अणु
	दीर्घ समयout = 0;
	दीर्घ करोne = 0;

	cond_resched();

	जबतक (करोne == 0) अणु
		करोne = NXRD32(adapter, NETXEN_ROMUSB_GLB_STATUS);
		करोne &= 2;
		अगर (++समयout >= NETXEN_MAX_ROM_WAIT_USEC) अणु
			dev_err(&adapter->pdev->dev,
				"Timeout reached  waiting for rom done");
			वापस -EIO;
		पूर्ण
		udelay(1);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक करो_rom_fast_पढ़ो(काष्ठा netxen_adapter *adapter,
			    पूर्णांक addr, पूर्णांक *valp)
अणु
	NXWR32(adapter, NETXEN_ROMUSB_ROM_ADDRESS, addr);
	NXWR32(adapter, NETXEN_ROMUSB_ROM_DUMMY_BYTE_CNT, 0);
	NXWR32(adapter, NETXEN_ROMUSB_ROM_ABYTE_CNT, 3);
	NXWR32(adapter, NETXEN_ROMUSB_ROM_INSTR_OPCODE, 0xb);
	अगर (netxen_रुको_rom_करोne(adapter)) अणु
		prपूर्णांकk("Error waiting for rom done\n");
		वापस -EIO;
	पूर्ण
	/* reset abyte_cnt and dummy_byte_cnt */
	NXWR32(adapter, NETXEN_ROMUSB_ROM_ABYTE_CNT, 0);
	udelay(10);
	NXWR32(adapter, NETXEN_ROMUSB_ROM_DUMMY_BYTE_CNT, 0);

	*valp = NXRD32(adapter, NETXEN_ROMUSB_ROM_RDATA);
	वापस 0;
पूर्ण

अटल पूर्णांक करो_rom_fast_पढ़ो_words(काष्ठा netxen_adapter *adapter, पूर्णांक addr,
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
netxen_rom_fast_पढ़ो_words(काष्ठा netxen_adapter *adapter, पूर्णांक addr,
				u8 *bytes, माप_प्रकार size)
अणु
	पूर्णांक ret;

	ret = netxen_rom_lock(adapter);
	अगर (ret < 0)
		वापस ret;

	ret = करो_rom_fast_पढ़ो_words(adapter, addr, bytes, size);

	netxen_rom_unlock(adapter);
	वापस ret;
पूर्ण

पूर्णांक netxen_rom_fast_पढ़ो(काष्ठा netxen_adapter *adapter, पूर्णांक addr, पूर्णांक *valp)
अणु
	पूर्णांक ret;

	अगर (netxen_rom_lock(adapter) != 0)
		वापस -EIO;

	ret = करो_rom_fast_पढ़ो(adapter, addr, valp);
	netxen_rom_unlock(adapter);
	वापस ret;
पूर्ण

#घोषणा NETXEN_BOARDTYPE		0x4008
#घोषणा NETXEN_BOARDNUM 		0x400c
#घोषणा NETXEN_CHIPNUM			0x4010

पूर्णांक netxen_pinit_from_rom(काष्ठा netxen_adapter *adapter)
अणु
	पूर्णांक addr, val;
	पूर्णांक i, n, init_delay = 0;
	काष्ठा crb_addr_pair *buf;
	अचिन्हित offset;
	u32 off;

	/* resetall */
	netxen_rom_lock(adapter);
	NXWR32(adapter, NETXEN_ROMUSB_GLB_SW_RESET, 0xfeffffff);
	netxen_rom_unlock(adapter);

	अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id)) अणु
		अगर (netxen_rom_fast_पढ़ो(adapter, 0, &n) != 0 ||
			(n != 0xcafecafe) ||
			netxen_rom_fast_पढ़ो(adapter, 4, &n) != 0) अणु
			prपूर्णांकk(KERN_ERR "%s: ERROR Reading crb_init area: "
					"n: %08x\n", netxen_nic_driver_name, n);
			वापस -EIO;
		पूर्ण
		offset = n & 0xffffU;
		n = (n >> 16) & 0xffffU;
	पूर्ण अन्यथा अणु
		अगर (netxen_rom_fast_पढ़ो(adapter, 0, &n) != 0 ||
			!(n & 0x80000000)) अणु
			prपूर्णांकk(KERN_ERR "%s: ERROR Reading crb_init area: "
					"n: %08x\n", netxen_nic_driver_name, n);
			वापस -EIO;
		पूर्ण
		offset = 1;
		n &= ~0x80000000;
	पूर्ण

	अगर (n >= 1024) अणु
		prपूर्णांकk(KERN_ERR "%s:n=0x%x Error! NetXen card flash not"
		       " initialized.\n", __func__, n);
		वापस -EIO;
	पूर्ण

	buf = kसुस्मृति(n, माप(काष्ठा crb_addr_pair), GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < n; i++) अणु
		अगर (netxen_rom_fast_पढ़ो(adapter, 8*i + 4*offset, &val) != 0 ||
		netxen_rom_fast_पढ़ो(adapter, 8*i + 4*offset + 4, &addr) != 0) अणु
			kमुक्त(buf);
			वापस -EIO;
		पूर्ण

		buf[i].addr = addr;
		buf[i].data = val;

	पूर्ण

	क्रम (i = 0; i < n; i++) अणु

		off = netxen_decode_crb_addr(buf[i].addr);
		अगर (off == NETXEN_ADDR_ERROR) अणु
			prपूर्णांकk(KERN_ERR"CRB init value out of range %x\n",
					buf[i].addr);
			जारी;
		पूर्ण
		off += NETXEN_PCI_CRBSPACE;

		अगर (off & 1)
			जारी;

		/* skipping cold reboot MAGIC */
		अगर (off == NETXEN_CAM_RAM(0x1fc))
			जारी;

		अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id)) अणु
			अगर (off == (NETXEN_CRB_I2C0 + 0x1c))
				जारी;
			/* करो not reset PCI */
			अगर (off == (ROMUSB_GLB + 0xbc))
				जारी;
			अगर (off == (ROMUSB_GLB + 0xa8))
				जारी;
			अगर (off == (ROMUSB_GLB + 0xc8)) /* core घड़ी */
				जारी;
			अगर (off == (ROMUSB_GLB + 0x24)) /* MN घड़ी */
				जारी;
			अगर (off == (ROMUSB_GLB + 0x1c)) /* MS घड़ी */
				जारी;
			अगर ((off & 0x0ff00000) == NETXEN_CRB_DDR_NET)
				जारी;
			अगर (off == (NETXEN_CRB_PEG_NET_1 + 0x18) &&
				!NX_IS_REVISION_P3P(adapter->ahw.revision_id))
				buf[i].data = 0x1020;
			/* skip the function enable रेजिस्टर */
			अगर (off == NETXEN_PCIE_REG(PCIE_SETUP_FUNCTION))
				जारी;
			अगर (off == NETXEN_PCIE_REG(PCIE_SETUP_FUNCTION2))
				जारी;
			अगर ((off & 0x0ff00000) == NETXEN_CRB_SMB)
				जारी;
		पूर्ण

		init_delay = 1;
		/* After writing this रेजिस्टर, HW needs समय क्रम CRB */
		/* to quiet करोwn (अन्यथा crb_winकरोw वापसs 0xffffffff) */
		अगर (off == NETXEN_ROMUSB_GLB_SW_RESET) अणु
			init_delay = 1000;
			अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id)) अणु
				/* hold xdma in reset also */
				buf[i].data = NETXEN_NIC_XDMA_RESET;
				buf[i].data = 0x8000ff;
			पूर्ण
		पूर्ण

		NXWR32(adapter, off, buf[i].data);

		msleep(init_delay);
	पूर्ण
	kमुक्त(buf);

	/* disable_peg_cache_all */

	/* unreset_net_cache */
	अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id)) अणु
		val = NXRD32(adapter, NETXEN_ROMUSB_GLB_SW_RESET);
		NXWR32(adapter, NETXEN_ROMUSB_GLB_SW_RESET, (val & 0xffffff0f));
	पूर्ण

	/* p2dn replyCount */
	NXWR32(adapter, NETXEN_CRB_PEG_NET_D + 0xec, 0x1e);
	/* disable_peg_cache 0 */
	NXWR32(adapter, NETXEN_CRB_PEG_NET_D + 0x4c, 8);
	/* disable_peg_cache 1 */
	NXWR32(adapter, NETXEN_CRB_PEG_NET_I + 0x4c, 8);

	/* peg_clr_all */

	/* peg_clr 0 */
	NXWR32(adapter, NETXEN_CRB_PEG_NET_0 + 0x8, 0);
	NXWR32(adapter, NETXEN_CRB_PEG_NET_0 + 0xc, 0);
	/* peg_clr 1 */
	NXWR32(adapter, NETXEN_CRB_PEG_NET_1 + 0x8, 0);
	NXWR32(adapter, NETXEN_CRB_PEG_NET_1 + 0xc, 0);
	/* peg_clr 2 */
	NXWR32(adapter, NETXEN_CRB_PEG_NET_2 + 0x8, 0);
	NXWR32(adapter, NETXEN_CRB_PEG_NET_2 + 0xc, 0);
	/* peg_clr 3 */
	NXWR32(adapter, NETXEN_CRB_PEG_NET_3 + 0x8, 0);
	NXWR32(adapter, NETXEN_CRB_PEG_NET_3 + 0xc, 0);
	वापस 0;
पूर्ण

अटल काष्ठा uni_table_desc *nx_get_table_desc(स्थिर u8 *unirom, पूर्णांक section)
अणु
	uपूर्णांक32_t i;
	काष्ठा uni_table_desc *directory = (काष्ठा uni_table_desc *) &unirom[0];
	__le32 entries = cpu_to_le32(directory->num_entries);

	क्रम (i = 0; i < entries; i++) अणु

		__le32 offs = cpu_to_le32(directory->findex) +
				(i * cpu_to_le32(directory->entry_size));
		__le32 tab_type = cpu_to_le32(*((u32 *)&unirom[offs] + 8));

		अगर (tab_type == section)
			वापस (काष्ठा uni_table_desc *) &unirom[offs];
	पूर्ण

	वापस शून्य;
पूर्ण

#घोषणा	QLCNIC_खाताHEADER_SIZE	(14 * 4)

अटल पूर्णांक
netxen_nic_validate_header(काष्ठा netxen_adapter *adapter)
अणु
	स्थिर u8 *unirom = adapter->fw->data;
	काष्ठा uni_table_desc *directory = (काष्ठा uni_table_desc *) &unirom[0];
	u32 fw_file_size = adapter->fw->size;
	u32 tab_size;
	__le32 entries;
	__le32 entry_size;

	अगर (fw_file_size < QLCNIC_खाताHEADER_SIZE)
		वापस -EINVAL;

	entries = cpu_to_le32(directory->num_entries);
	entry_size = cpu_to_le32(directory->entry_size);
	tab_size = cpu_to_le32(directory->findex) + (entries * entry_size);

	अगर (fw_file_size < tab_size)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक
netxen_nic_validate_bootld(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा uni_table_desc *tab_desc;
	काष्ठा uni_data_desc *descr;
	स्थिर u8 *unirom = adapter->fw->data;
	__le32 idx = cpu_to_le32(*((पूर्णांक *)&unirom[adapter->file_prd_off] +
				NX_UNI_BOOTLD_IDX_OFF));
	u32 offs;
	u32 tab_size;
	u32 data_size;

	tab_desc = nx_get_table_desc(unirom, NX_UNI_सूची_SECT_BOOTLD);

	अगर (!tab_desc)
		वापस -EINVAL;

	tab_size = cpu_to_le32(tab_desc->findex) +
			(cpu_to_le32(tab_desc->entry_size) * (idx + 1));

	अगर (adapter->fw->size < tab_size)
		वापस -EINVAL;

	offs = cpu_to_le32(tab_desc->findex) +
		(cpu_to_le32(tab_desc->entry_size) * (idx));
	descr = (काष्ठा uni_data_desc *)&unirom[offs];

	data_size = cpu_to_le32(descr->findex) + cpu_to_le32(descr->size);

	अगर (adapter->fw->size < data_size)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक
netxen_nic_validate_fw(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा uni_table_desc *tab_desc;
	काष्ठा uni_data_desc *descr;
	स्थिर u8 *unirom = adapter->fw->data;
	__le32 idx = cpu_to_le32(*((पूर्णांक *)&unirom[adapter->file_prd_off] +
				NX_UNI_FIRMWARE_IDX_OFF));
	u32 offs;
	u32 tab_size;
	u32 data_size;

	tab_desc = nx_get_table_desc(unirom, NX_UNI_सूची_SECT_FW);

	अगर (!tab_desc)
		वापस -EINVAL;

	tab_size = cpu_to_le32(tab_desc->findex) +
			(cpu_to_le32(tab_desc->entry_size) * (idx + 1));

	अगर (adapter->fw->size < tab_size)
		वापस -EINVAL;

	offs = cpu_to_le32(tab_desc->findex) +
		(cpu_to_le32(tab_desc->entry_size) * (idx));
	descr = (काष्ठा uni_data_desc *)&unirom[offs];
	data_size = cpu_to_le32(descr->findex) + cpu_to_le32(descr->size);

	अगर (adapter->fw->size < data_size)
		वापस -EINVAL;

	वापस 0;
पूर्ण


अटल पूर्णांक
netxen_nic_validate_product_offs(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा uni_table_desc *ptab_descr;
	स्थिर u8 *unirom = adapter->fw->data;
	पूर्णांक mn_present = (NX_IS_REVISION_P2(adapter->ahw.revision_id)) ?
			1 : netxen_p3_has_mn(adapter);
	__le32 entries;
	__le32 entry_size;
	u32 tab_size;
	u32 i;

	ptab_descr = nx_get_table_desc(unirom, NX_UNI_सूची_SECT_PRODUCT_TBL);
	अगर (ptab_descr == शून्य)
		वापस -EINVAL;

	entries = cpu_to_le32(ptab_descr->num_entries);
	entry_size = cpu_to_le32(ptab_descr->entry_size);
	tab_size = cpu_to_le32(ptab_descr->findex) + (entries * entry_size);

	अगर (adapter->fw->size < tab_size)
		वापस -EINVAL;

nomn:
	क्रम (i = 0; i < entries; i++) अणु

		__le32 flags, file_chiprev, offs;
		u8 chiprev = adapter->ahw.revision_id;
		uपूर्णांक32_t flagbit;

		offs = cpu_to_le32(ptab_descr->findex) +
				(i * cpu_to_le32(ptab_descr->entry_size));
		flags = cpu_to_le32(*((पूर्णांक *)&unirom[offs] + NX_UNI_FLAGS_OFF));
		file_chiprev = cpu_to_le32(*((पूर्णांक *)&unirom[offs] +
							NX_UNI_CHIP_REV_OFF));

		flagbit = mn_present ? 1 : 2;

		अगर ((chiprev == file_chiprev) &&
					((1ULL << flagbit) & flags)) अणु
			adapter->file_prd_off = offs;
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (mn_present && NX_IS_REVISION_P3(adapter->ahw.revision_id)) अणु
		mn_present = 0;
		जाओ nomn;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
netxen_nic_validate_unअगरied_romimage(काष्ठा netxen_adapter *adapter)
अणु
	अगर (netxen_nic_validate_header(adapter)) अणु
		dev_err(&adapter->pdev->dev,
				"unified image: header validation failed\n");
		वापस -EINVAL;
	पूर्ण

	अगर (netxen_nic_validate_product_offs(adapter)) अणु
		dev_err(&adapter->pdev->dev,
				"unified image: product validation failed\n");
		वापस -EINVAL;
	पूर्ण

	अगर (netxen_nic_validate_bootld(adapter)) अणु
		dev_err(&adapter->pdev->dev,
				"unified image: bootld validation failed\n");
		वापस -EINVAL;
	पूर्ण

	अगर (netxen_nic_validate_fw(adapter)) अणु
		dev_err(&adapter->pdev->dev,
				"unified image: firmware validation failed\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा uni_data_desc *nx_get_data_desc(काष्ठा netxen_adapter *adapter,
			u32 section, u32 idx_offset)
अणु
	स्थिर u8 *unirom = adapter->fw->data;
	पूर्णांक idx = cpu_to_le32(*((पूर्णांक *)&unirom[adapter->file_prd_off] +
								idx_offset));
	काष्ठा uni_table_desc *tab_desc;
	__le32 offs;

	tab_desc = nx_get_table_desc(unirom, section);

	अगर (tab_desc == शून्य)
		वापस शून्य;

	offs = cpu_to_le32(tab_desc->findex) +
			(cpu_to_le32(tab_desc->entry_size) * idx);

	वापस (काष्ठा uni_data_desc *)&unirom[offs];
पूर्ण

अटल u8 *
nx_get_bootld_offs(काष्ठा netxen_adapter *adapter)
अणु
	u32 offs = NETXEN_BOOTLD_START;

	अगर (adapter->fw_type == NX_UNIFIED_ROMIMAGE)
		offs = cpu_to_le32((nx_get_data_desc(adapter,
					NX_UNI_सूची_SECT_BOOTLD,
					NX_UNI_BOOTLD_IDX_OFF))->findex);

	वापस (u8 *)&adapter->fw->data[offs];
पूर्ण

अटल u8 *
nx_get_fw_offs(काष्ठा netxen_adapter *adapter)
अणु
	u32 offs = NETXEN_IMAGE_START;

	अगर (adapter->fw_type == NX_UNIFIED_ROMIMAGE)
		offs = cpu_to_le32((nx_get_data_desc(adapter,
					NX_UNI_सूची_SECT_FW,
					NX_UNI_FIRMWARE_IDX_OFF))->findex);

	वापस (u8 *)&adapter->fw->data[offs];
पूर्ण

अटल __le32
nx_get_fw_size(काष्ठा netxen_adapter *adapter)
अणु
	अगर (adapter->fw_type == NX_UNIFIED_ROMIMAGE)
		वापस cpu_to_le32((nx_get_data_desc(adapter,
					NX_UNI_सूची_SECT_FW,
					NX_UNI_FIRMWARE_IDX_OFF))->size);
	अन्यथा
		वापस cpu_to_le32(
				*(u32 *)&adapter->fw->data[NX_FW_SIZE_OFFSET]);
पूर्ण

अटल __le32
nx_get_fw_version(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा uni_data_desc *fw_data_desc;
	स्थिर काष्ठा firmware *fw = adapter->fw;
	__le32 major, minor, sub;
	स्थिर u8 *ver_str;
	पूर्णांक i, ret = 0;

	अगर (adapter->fw_type == NX_UNIFIED_ROMIMAGE) अणु

		fw_data_desc = nx_get_data_desc(adapter,
				NX_UNI_सूची_SECT_FW, NX_UNI_FIRMWARE_IDX_OFF);
		ver_str = fw->data + cpu_to_le32(fw_data_desc->findex) +
				cpu_to_le32(fw_data_desc->size) - 17;

		क्रम (i = 0; i < 12; i++) अणु
			अगर (!म_भेदन(&ver_str[i], "REV=", 4)) अणु
				ret = माला_पूछो(&ver_str[i+4], "%u.%u.%u ",
							&major, &minor, &sub);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (ret != 3)
			वापस 0;

		वापस major + (minor << 8) + (sub << 16);

	पूर्ण अन्यथा
		वापस cpu_to_le32(*(u32 *)&fw->data[NX_FW_VERSION_OFFSET]);
पूर्ण

अटल __le32
nx_get_bios_version(काष्ठा netxen_adapter *adapter)
अणु
	स्थिर काष्ठा firmware *fw = adapter->fw;
	__le32 bios_ver, prd_off = adapter->file_prd_off;

	अगर (adapter->fw_type == NX_UNIFIED_ROMIMAGE) अणु
		bios_ver = cpu_to_le32(*((u32 *) (&fw->data[prd_off])
						+ NX_UNI_BIOS_VERSION_OFF));
		वापस (bios_ver << 16) + ((bios_ver >> 8) & 0xff00) +
							(bios_ver >> 24);
	पूर्ण अन्यथा
		वापस cpu_to_le32(*(u32 *)&fw->data[NX_BIOS_VERSION_OFFSET]);

पूर्ण

पूर्णांक
netxen_need_fw_reset(काष्ठा netxen_adapter *adapter)
अणु
	u32 count, old_count;
	u32 val, version, major, minor, build;
	पूर्णांक i, समयout;
	u8 fw_type;

	/* NX2031 firmware करोesn't support heartbit */
	अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id))
		वापस 1;

	अगर (adapter->need_fw_reset)
		वापस 1;

	/* last attempt had failed */
	अगर (NXRD32(adapter, CRB_CMDPEG_STATE) == PHAN_INITIALIZE_FAILED)
		वापस 1;

	old_count = NXRD32(adapter, NETXEN_PEG_ALIVE_COUNTER);

	क्रम (i = 0; i < 10; i++) अणु

		समयout = msleep_पूर्णांकerruptible(200);
		अगर (समयout) अणु
			NXWR32(adapter, CRB_CMDPEG_STATE,
					PHAN_INITIALIZE_FAILED);
			वापस -EINTR;
		पूर्ण

		count = NXRD32(adapter, NETXEN_PEG_ALIVE_COUNTER);
		अगर (count != old_count)
			अवरोध;
	पूर्ण

	/* firmware is dead */
	अगर (count == old_count)
		वापस 1;

	/* check अगर we have got newer or dअगरferent file firmware */
	अगर (adapter->fw) अणु

		val = nx_get_fw_version(adapter);

		version = NETXEN_DECODE_VERSION(val);

		major = NXRD32(adapter, NETXEN_FW_VERSION_MAJOR);
		minor = NXRD32(adapter, NETXEN_FW_VERSION_MINOR);
		build = NXRD32(adapter, NETXEN_FW_VERSION_SUB);

		अगर (version > NETXEN_VERSION_CODE(major, minor, build))
			वापस 1;

		अगर (version == NETXEN_VERSION_CODE(major, minor, build) &&
			adapter->fw_type != NX_UNIFIED_ROMIMAGE) अणु

			val = NXRD32(adapter, NETXEN_MIU_MN_CONTROL);
			fw_type = (val & 0x4) ?
				NX_P3_CT_ROMIMAGE : NX_P3_MN_ROMIMAGE;

			अगर (adapter->fw_type != fw_type)
				वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा NETXEN_MIN_P3_FW_SUPP	NETXEN_VERSION_CODE(4, 0, 505)

पूर्णांक
netxen_check_flash_fw_compatibility(काष्ठा netxen_adapter *adapter)
अणु
	u32 flash_fw_ver, min_fw_ver;

	अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id))
		वापस 0;

	अगर (netxen_rom_fast_पढ़ो(adapter,
			NX_FW_VERSION_OFFSET, (पूर्णांक *)&flash_fw_ver)) अणु
		dev_err(&adapter->pdev->dev, "Unable to read flash fw"
			"version\n");
		वापस -EIO;
	पूर्ण

	flash_fw_ver = NETXEN_DECODE_VERSION(flash_fw_ver);
	min_fw_ver = NETXEN_MIN_P3_FW_SUPP;
	अगर (flash_fw_ver >= min_fw_ver)
		वापस 0;

	dev_info(&adapter->pdev->dev, "Flash fw[%d.%d.%d] is < min fw supported"
		"[4.0.505]. Please update firmware on flash\n",
		_major(flash_fw_ver), _minor(flash_fw_ver),
		_build(flash_fw_ver));
	वापस -EINVAL;
पूर्ण

अटल अक्षर *fw_name[] = अणु
	NX_P2_MN_ROMIMAGE_NAME,
	NX_P3_CT_ROMIMAGE_NAME,
	NX_P3_MN_ROMIMAGE_NAME,
	NX_UNIFIED_ROMIMAGE_NAME,
	NX_FLASH_ROMIMAGE_NAME,
पूर्ण;

पूर्णांक
netxen_load_firmware(काष्ठा netxen_adapter *adapter)
अणु
	u64 *ptr64;
	u32 i, flashaddr, size;
	स्थिर काष्ठा firmware *fw = adapter->fw;
	काष्ठा pci_dev *pdev = adapter->pdev;

	dev_info(&pdev->dev, "loading firmware from %s\n",
			fw_name[adapter->fw_type]);

	अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id))
		NXWR32(adapter, NETXEN_ROMUSB_GLB_CAS_RST, 1);

	अगर (fw) अणु
		__le64 data;

		size = (NETXEN_IMAGE_START - NETXEN_BOOTLD_START) / 8;

		ptr64 = (u64 *)nx_get_bootld_offs(adapter);
		flashaddr = NETXEN_BOOTLD_START;

		क्रम (i = 0; i < size; i++) अणु
			data = cpu_to_le64(ptr64[i]);

			अगर (adapter->pci_mem_ग_लिखो(adapter, flashaddr, data))
				वापस -EIO;

			flashaddr += 8;
		पूर्ण

		size = (__क्रमce u32)nx_get_fw_size(adapter) / 8;

		ptr64 = (u64 *)nx_get_fw_offs(adapter);
		flashaddr = NETXEN_IMAGE_START;

		क्रम (i = 0; i < size; i++) अणु
			data = cpu_to_le64(ptr64[i]);

			अगर (adapter->pci_mem_ग_लिखो(adapter,
						flashaddr, data))
				वापस -EIO;

			flashaddr += 8;
		पूर्ण

		size = (__क्रमce u32)nx_get_fw_size(adapter) % 8;
		अगर (size) अणु
			data = cpu_to_le64(ptr64[i]);

			अगर (adapter->pci_mem_ग_लिखो(adapter,
						flashaddr, data))
				वापस -EIO;
		पूर्ण

	पूर्ण अन्यथा अणु
		u64 data;
		u32 hi, lo;

		size = (NETXEN_IMAGE_START - NETXEN_BOOTLD_START) / 8;
		flashaddr = NETXEN_BOOTLD_START;

		क्रम (i = 0; i < size; i++) अणु
			अगर (netxen_rom_fast_पढ़ो(adapter,
					flashaddr, (पूर्णांक *)&lo) != 0)
				वापस -EIO;
			अगर (netxen_rom_fast_पढ़ो(adapter,
					flashaddr + 4, (पूर्णांक *)&hi) != 0)
				वापस -EIO;

			/* hi, lo are alपढ़ोy in host endian byteorder */
			data = (((u64)hi << 32) | lo);

			अगर (adapter->pci_mem_ग_लिखो(adapter,
						flashaddr, data))
				वापस -EIO;

			flashaddr += 8;
		पूर्ण
	पूर्ण
	msleep(1);

	अगर (NX_IS_REVISION_P3P(adapter->ahw.revision_id)) अणु
		NXWR32(adapter, NETXEN_CRB_PEG_NET_0 + 0x18, 0x1020);
		NXWR32(adapter, NETXEN_ROMUSB_GLB_SW_RESET, 0x80001e);
	पूर्ण अन्यथा अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id))
		NXWR32(adapter, NETXEN_ROMUSB_GLB_SW_RESET, 0x80001d);
	अन्यथा अणु
		NXWR32(adapter, NETXEN_ROMUSB_GLB_CHIP_CLK_CTRL, 0x3fff);
		NXWR32(adapter, NETXEN_ROMUSB_GLB_CAS_RST, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
netxen_validate_firmware(काष्ठा netxen_adapter *adapter)
अणु
	__le32 val;
	__le32 flash_fw_ver;
	u32 file_fw_ver, min_ver, bios;
	काष्ठा pci_dev *pdev = adapter->pdev;
	स्थिर काष्ठा firmware *fw = adapter->fw;
	u8 fw_type = adapter->fw_type;
	u32 crbinit_fix_fw;

	अगर (fw_type == NX_UNIFIED_ROMIMAGE) अणु
		अगर (netxen_nic_validate_unअगरied_romimage(adapter))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		val = cpu_to_le32(*(u32 *)&fw->data[NX_FW_MAGIC_OFFSET]);
		अगर ((__क्रमce u32)val != NETXEN_BDINFO_MAGIC)
			वापस -EINVAL;

		अगर (fw->size < NX_FW_MIN_SIZE)
			वापस -EINVAL;
	पूर्ण

	val = nx_get_fw_version(adapter);

	अगर (NX_IS_REVISION_P3(adapter->ahw.revision_id))
		min_ver = NETXEN_MIN_P3_FW_SUPP;
	अन्यथा
		min_ver = NETXEN_VERSION_CODE(3, 4, 216);

	file_fw_ver = NETXEN_DECODE_VERSION(val);

	अगर ((_major(file_fw_ver) > _NETXEN_NIC_LINUX_MAJOR) ||
	    (file_fw_ver < min_ver)) अणु
		dev_err(&pdev->dev,
				"%s: firmware version %d.%d.%d unsupported\n",
		fw_name[fw_type], _major(file_fw_ver), _minor(file_fw_ver),
		 _build(file_fw_ver));
		वापस -EINVAL;
	पूर्ण
	val = nx_get_bios_version(adapter);
	अगर (netxen_rom_fast_पढ़ो(adapter, NX_BIOS_VERSION_OFFSET, (पूर्णांक *)&bios))
		वापस -EIO;
	अगर ((__क्रमce u32)val != bios) अणु
		dev_err(&pdev->dev, "%s: firmware bios is incompatible\n",
				fw_name[fw_type]);
		वापस -EINVAL;
	पूर्ण

	अगर (netxen_rom_fast_पढ़ो(adapter,
			NX_FW_VERSION_OFFSET, (पूर्णांक *)&flash_fw_ver)) अणु
		dev_err(&pdev->dev, "Unable to read flash fw version\n");
		वापस -EIO;
	पूर्ण
	flash_fw_ver = NETXEN_DECODE_VERSION(flash_fw_ver);

	/* New fw from file is not allowed, अगर fw on flash is < 4.0.554 */
	crbinit_fix_fw = NETXEN_VERSION_CODE(4, 0, 554);
	अगर (file_fw_ver >= crbinit_fix_fw && flash_fw_ver < crbinit_fix_fw &&
	    NX_IS_REVISION_P3(adapter->ahw.revision_id)) अणु
		dev_err(&pdev->dev, "Incompatibility detected between driver "
			"and firmware version on flash. This configuration "
			"is not recommended. Please update the firmware on "
			"flash immediately\n");
		वापस -EINVAL;
	पूर्ण

	/* check अगर flashed firmware is newer only क्रम no-mn and P2 हाल*/
	अगर (!netxen_p3_has_mn(adapter) ||
	    NX_IS_REVISION_P2(adapter->ahw.revision_id)) अणु
		अगर (flash_fw_ver > file_fw_ver) अणु
			dev_info(&pdev->dev, "%s: firmware is older than flash\n",
				fw_name[fw_type]);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	NXWR32(adapter, NETXEN_CAM_RAM(0x1fc), NETXEN_BDINFO_MAGIC);
	वापस 0;
पूर्ण

अटल व्योम
nx_get_next_fwtype(काष्ठा netxen_adapter *adapter)
अणु
	u8 fw_type;

	चयन (adapter->fw_type) अणु
	हाल NX_UNKNOWN_ROMIMAGE:
		fw_type = NX_UNIFIED_ROMIMAGE;
		अवरोध;

	हाल NX_UNIFIED_ROMIMAGE:
		अगर (NX_IS_REVISION_P3P(adapter->ahw.revision_id))
			fw_type = NX_FLASH_ROMIMAGE;
		अन्यथा अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id))
			fw_type = NX_P2_MN_ROMIMAGE;
		अन्यथा अगर (netxen_p3_has_mn(adapter))
			fw_type = NX_P3_MN_ROMIMAGE;
		अन्यथा
			fw_type = NX_P3_CT_ROMIMAGE;
		अवरोध;

	हाल NX_P3_MN_ROMIMAGE:
		fw_type = NX_P3_CT_ROMIMAGE;
		अवरोध;

	हाल NX_P2_MN_ROMIMAGE:
	हाल NX_P3_CT_ROMIMAGE:
	शेष:
		fw_type = NX_FLASH_ROMIMAGE;
		अवरोध;
	पूर्ण

	adapter->fw_type = fw_type;
पूर्ण

अटल पूर्णांक
netxen_p3_has_mn(काष्ठा netxen_adapter *adapter)
अणु
	u32 capability, flashed_ver;
	capability = 0;

	/* NX2031 always had MN */
	अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id))
		वापस 1;

	netxen_rom_fast_पढ़ो(adapter,
			NX_FW_VERSION_OFFSET, (पूर्णांक *)&flashed_ver);
	flashed_ver = NETXEN_DECODE_VERSION(flashed_ver);

	अगर (flashed_ver >= NETXEN_VERSION_CODE(4, 0, 220)) अणु

		capability = NXRD32(adapter, NX_PEG_TUNE_CAPABILITY);
		अगर (capability & NX_PEG_TUNE_MN_PRESENT)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

व्योम netxen_request_firmware(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक rc = 0;

	adapter->fw_type = NX_UNKNOWN_ROMIMAGE;

next:
	nx_get_next_fwtype(adapter);

	अगर (adapter->fw_type == NX_FLASH_ROMIMAGE) अणु
		adapter->fw = शून्य;
	पूर्ण अन्यथा अणु
		rc = request_firmware(&adapter->fw,
				fw_name[adapter->fw_type], &pdev->dev);
		अगर (rc != 0)
			जाओ next;

		rc = netxen_validate_firmware(adapter);
		अगर (rc != 0) अणु
			release_firmware(adapter->fw);
			msleep(1);
			जाओ next;
		पूर्ण
	पूर्ण
पूर्ण


व्योम
netxen_release_firmware(काष्ठा netxen_adapter *adapter)
अणु
	release_firmware(adapter->fw);
	adapter->fw = शून्य;
पूर्ण

पूर्णांक netxen_init_dummy_dma(काष्ठा netxen_adapter *adapter)
अणु
	u64 addr;
	u32 hi, lo;

	अगर (!NX_IS_REVISION_P2(adapter->ahw.revision_id))
		वापस 0;

	adapter->dummy_dma.addr = dma_alloc_coherent(&adapter->pdev->dev,
						     NETXEN_HOST_DUMMY_DMA_SIZE,
						     &adapter->dummy_dma.phys_addr,
						     GFP_KERNEL);
	अगर (adapter->dummy_dma.addr == शून्य) अणु
		dev_err(&adapter->pdev->dev,
			"ERROR: Could not allocate dummy DMA memory\n");
		वापस -ENOMEM;
	पूर्ण

	addr = (uपूर्णांक64_t) adapter->dummy_dma.phys_addr;
	hi = (addr >> 32) & 0xffffffff;
	lo = addr & 0xffffffff;

	NXWR32(adapter, CRB_HOST_DUMMY_BUF_ADDR_HI, hi);
	NXWR32(adapter, CRB_HOST_DUMMY_BUF_ADDR_LO, lo);

	वापस 0;
पूर्ण

/*
 * NetXen DMA watchकरोg control:
 *
 *	Bit 0		: enabled => R/O: 1 watchकरोg active, 0 inactive
 *	Bit 1		: disable_request => 1 req disable dma watchकरोg
 *	Bit 2		: enable_request =>  1 req enable dma watchकरोg
 *	Bit 3-31	: unused
 */
व्योम netxen_मुक्त_dummy_dma(काष्ठा netxen_adapter *adapter)
अणु
	पूर्णांक i = 100;
	u32 ctrl;

	अगर (!NX_IS_REVISION_P2(adapter->ahw.revision_id))
		वापस;

	अगर (!adapter->dummy_dma.addr)
		वापस;

	ctrl = NXRD32(adapter, NETXEN_DMA_WATCHDOG_CTRL);
	अगर ((ctrl & 0x1) != 0) अणु
		NXWR32(adapter, NETXEN_DMA_WATCHDOG_CTRL, (ctrl | 0x2));

		जबतक ((ctrl & 0x1) != 0) अणु

			msleep(50);

			ctrl = NXRD32(adapter, NETXEN_DMA_WATCHDOG_CTRL);

			अगर (--i == 0)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (i) अणु
		dma_मुक्त_coherent(&adapter->pdev->dev,
				  NETXEN_HOST_DUMMY_DMA_SIZE,
				  adapter->dummy_dma.addr,
				  adapter->dummy_dma.phys_addr);
		adapter->dummy_dma.addr = शून्य;
	पूर्ण अन्यथा
		dev_err(&adapter->pdev->dev, "dma_watchdog_shutdown failed\n");
पूर्ण

पूर्णांक netxen_phantom_init(काष्ठा netxen_adapter *adapter, पूर्णांक pegtune_val)
अणु
	u32 val = 0;
	पूर्णांक retries = 60;

	अगर (pegtune_val)
		वापस 0;

	करो अणु
		val = NXRD32(adapter, CRB_CMDPEG_STATE);
		चयन (val) अणु
		हाल PHAN_INITIALIZE_COMPLETE:
		हाल PHAN_INITIALIZE_ACK:
			वापस 0;
		हाल PHAN_INITIALIZE_FAILED:
			जाओ out_err;
		शेष:
			अवरोध;
		पूर्ण

		msleep(500);

	पूर्ण जबतक (--retries);

	NXWR32(adapter, CRB_CMDPEG_STATE, PHAN_INITIALIZE_FAILED);

out_err:
	dev_warn(&adapter->pdev->dev, "firmware init failed\n");
	वापस -EIO;
पूर्ण

अटल पूर्णांक
netxen_receive_peg_पढ़ोy(काष्ठा netxen_adapter *adapter)
अणु
	u32 val = 0;
	पूर्णांक retries = 2000;

	करो अणु
		val = NXRD32(adapter, CRB_RCVPEG_STATE);

		अगर (val == PHAN_PEG_RCV_INITIALIZED)
			वापस 0;

		msleep(10);

	पूर्ण जबतक (--retries);

	pr_err("Receive Peg initialization not complete, state: 0x%x.\n", val);
	वापस -EIO;
पूर्ण

पूर्णांक netxen_init_firmware(काष्ठा netxen_adapter *adapter)
अणु
	पूर्णांक err;

	err = netxen_receive_peg_पढ़ोy(adapter);
	अगर (err)
		वापस err;

	NXWR32(adapter, CRB_NIC_CAPABILITIES_HOST, INTR_SCHEME_PERPORT);
	NXWR32(adapter, CRB_MPORT_MODE, MPORT_MULTI_FUNCTION_MODE);
	NXWR32(adapter, CRB_CMDPEG_STATE, PHAN_INITIALIZE_ACK);

	अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id))
		NXWR32(adapter, CRB_NIC_MSI_MODE_HOST, MSI_MODE_MULTIFUNC);

	वापस err;
पूर्ण

अटल व्योम
netxen_handle_linkevent(काष्ठा netxen_adapter *adapter, nx_fw_msg_t *msg)
अणु
	u32 cable_OUI;
	u16 cable_len;
	u16 link_speed;
	u8  link_status, module, duplex, स्वतःneg;
	काष्ठा net_device *netdev = adapter->netdev;

	adapter->has_link_events = 1;

	cable_OUI = msg->body[1] & 0xffffffff;
	cable_len = (msg->body[1] >> 32) & 0xffff;
	link_speed = (msg->body[1] >> 48) & 0xffff;

	link_status = msg->body[2] & 0xff;
	duplex = (msg->body[2] >> 16) & 0xff;
	स्वतःneg = (msg->body[2] >> 24) & 0xff;

	module = (msg->body[2] >> 8) & 0xff;
	अगर (module == LINKEVENT_MODULE_TWINAX_UNSUPPORTED_CABLE) अणु
		prपूर्णांकk(KERN_INFO "%s: unsupported cable: OUI 0x%x, length %d\n",
				netdev->name, cable_OUI, cable_len);
	पूर्ण अन्यथा अगर (module == LINKEVENT_MODULE_TWINAX_UNSUPPORTED_CABLELEN) अणु
		prपूर्णांकk(KERN_INFO "%s: unsupported cable length %d\n",
				netdev->name, cable_len);
	पूर्ण

	/* update link parameters */
	अगर (duplex == LINKEVENT_FULL_DUPLEX)
		adapter->link_duplex = DUPLEX_FULL;
	अन्यथा
		adapter->link_duplex = DUPLEX_HALF;
	adapter->module_type = module;
	adapter->link_स्वतःneg = स्वतःneg;
	adapter->link_speed = link_speed;

	netxen_advert_link_change(adapter, link_status);
पूर्ण

अटल व्योम
netxen_handle_fw_message(पूर्णांक desc_cnt, पूर्णांक index,
		काष्ठा nx_host_sds_ring *sds_ring)
अणु
	nx_fw_msg_t msg;
	काष्ठा status_desc *desc;
	पूर्णांक i = 0, opcode;

	जबतक (desc_cnt > 0 && i < 8) अणु
		desc = &sds_ring->desc_head[index];
		msg.words[i++] = le64_to_cpu(desc->status_desc_data[0]);
		msg.words[i++] = le64_to_cpu(desc->status_desc_data[1]);

		index = get_next_index(index, sds_ring->num_desc);
		desc_cnt--;
	पूर्ण

	opcode = netxen_get_nic_msg_opcode(msg.body[0]);
	चयन (opcode) अणु
	हाल NX_NIC_C2H_OPCODE_GET_LINKEVENT_RESPONSE:
		netxen_handle_linkevent(sds_ring->adapter, &msg);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक
netxen_alloc_rx_skb(काष्ठा netxen_adapter *adapter,
		काष्ठा nx_host_rds_ring *rds_ring,
		काष्ठा netxen_rx_buffer *buffer)
अणु
	काष्ठा sk_buff *skb;
	dma_addr_t dma;
	काष्ठा pci_dev *pdev = adapter->pdev;

	buffer->skb = netdev_alloc_skb(adapter->netdev, rds_ring->skb_size);
	अगर (!buffer->skb)
		वापस 1;

	skb = buffer->skb;

	अगर (!adapter->ahw.cut_through)
		skb_reserve(skb, 2);

	dma = dma_map_single(&pdev->dev, skb->data, rds_ring->dma_size,
			     DMA_FROM_DEVICE);

	अगर (dma_mapping_error(&pdev->dev, dma)) अणु
		dev_kमुक्त_skb_any(skb);
		buffer->skb = शून्य;
		वापस 1;
	पूर्ण

	buffer->skb = skb;
	buffer->dma = dma;
	buffer->state = NETXEN_BUFFER_BUSY;

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *netxen_process_rxbuf(काष्ठा netxen_adapter *adapter,
		काष्ठा nx_host_rds_ring *rds_ring, u16 index, u16 cksum)
अणु
	काष्ठा netxen_rx_buffer *buffer;
	काष्ठा sk_buff *skb;

	buffer = &rds_ring->rx_buf_arr[index];

	dma_unmap_single(&adapter->pdev->dev, buffer->dma, rds_ring->dma_size,
			 DMA_FROM_DEVICE);

	skb = buffer->skb;
	अगर (!skb)
		जाओ no_skb;

	अगर (likely((adapter->netdev->features & NETIF_F_RXCSUM)
	    && cksum == STATUS_CKSUM_OK)) अणु
		adapter->stats.csummed++;
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण अन्यथा
		skb->ip_summed = CHECKSUM_NONE;

	buffer->skb = शून्य;
no_skb:
	buffer->state = NETXEN_BUFFER_FREE;
	वापस skb;
पूर्ण

अटल काष्ठा netxen_rx_buffer *
netxen_process_rcv(काष्ठा netxen_adapter *adapter,
		काष्ठा nx_host_sds_ring *sds_ring,
		पूर्णांक ring, u64 sts_data0)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा netxen_recv_context *recv_ctx = &adapter->recv_ctx;
	काष्ठा netxen_rx_buffer *buffer;
	काष्ठा sk_buff *skb;
	काष्ठा nx_host_rds_ring *rds_ring;
	पूर्णांक index, length, cksum, pkt_offset;

	अगर (unlikely(ring >= adapter->max_rds_rings))
		वापस शून्य;

	rds_ring = &recv_ctx->rds_rings[ring];

	index = netxen_get_sts_refhandle(sts_data0);
	अगर (unlikely(index >= rds_ring->num_desc))
		वापस शून्य;

	buffer = &rds_ring->rx_buf_arr[index];

	length = netxen_get_sts_totallength(sts_data0);
	cksum  = netxen_get_sts_status(sts_data0);
	pkt_offset = netxen_get_sts_pkt_offset(sts_data0);

	skb = netxen_process_rxbuf(adapter, rds_ring, index, cksum);
	अगर (!skb)
		वापस buffer;

	अगर (length > rds_ring->skb_size)
		skb_put(skb, rds_ring->skb_size);
	अन्यथा
		skb_put(skb, length);


	अगर (pkt_offset)
		skb_pull(skb, pkt_offset);

	skb->protocol = eth_type_trans(skb, netdev);

	napi_gro_receive(&sds_ring->napi, skb);

	adapter->stats.rx_pkts++;
	adapter->stats.rxbytes += length;

	वापस buffer;
पूर्ण

#घोषणा TCP_HDR_SIZE            20
#घोषणा TCP_TS_OPTION_SIZE      12
#घोषणा TCP_TS_HDR_SIZE         (TCP_HDR_SIZE + TCP_TS_OPTION_SIZE)

अटल काष्ठा netxen_rx_buffer *
netxen_process_lro(काष्ठा netxen_adapter *adapter,
		काष्ठा nx_host_sds_ring *sds_ring,
		पूर्णांक ring, u64 sts_data0, u64 sts_data1)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा netxen_recv_context *recv_ctx = &adapter->recv_ctx;
	काष्ठा netxen_rx_buffer *buffer;
	काष्ठा sk_buff *skb;
	काष्ठा nx_host_rds_ring *rds_ring;
	काष्ठा iphdr *iph;
	काष्ठा tcphdr *th;
	bool push, बारtamp;
	पूर्णांक l2_hdr_offset, l4_hdr_offset;
	पूर्णांक index;
	u16 lro_length, length, data_offset;
	u32 seq_number;
	u8 vhdr_len = 0;

	अगर (unlikely(ring >= adapter->max_rds_rings))
		वापस शून्य;

	rds_ring = &recv_ctx->rds_rings[ring];

	index = netxen_get_lro_sts_refhandle(sts_data0);
	अगर (unlikely(index >= rds_ring->num_desc))
		वापस शून्य;

	buffer = &rds_ring->rx_buf_arr[index];

	बारtamp = netxen_get_lro_sts_बारtamp(sts_data0);
	lro_length = netxen_get_lro_sts_length(sts_data0);
	l2_hdr_offset = netxen_get_lro_sts_l2_hdr_offset(sts_data0);
	l4_hdr_offset = netxen_get_lro_sts_l4_hdr_offset(sts_data0);
	push = netxen_get_lro_sts_push_flag(sts_data0);
	seq_number = netxen_get_lro_sts_seq_number(sts_data1);

	skb = netxen_process_rxbuf(adapter, rds_ring, index, STATUS_CKSUM_OK);
	अगर (!skb)
		वापस buffer;

	अगर (बारtamp)
		data_offset = l4_hdr_offset + TCP_TS_HDR_SIZE;
	अन्यथा
		data_offset = l4_hdr_offset + TCP_HDR_SIZE;

	skb_put(skb, lro_length + data_offset);

	skb_pull(skb, l2_hdr_offset);
	skb->protocol = eth_type_trans(skb, netdev);

	अगर (skb->protocol == htons(ETH_P_8021Q))
		vhdr_len = VLAN_HLEN;
	iph = (काष्ठा iphdr *)(skb->data + vhdr_len);
	th = (काष्ठा tcphdr *)((skb->data + vhdr_len) + (iph->ihl << 2));

	length = (iph->ihl << 2) + (th->करोff << 2) + lro_length;
	csum_replace2(&iph->check, iph->tot_len, htons(length));
	iph->tot_len = htons(length);
	th->psh = push;
	th->seq = htonl(seq_number);

	length = skb->len;

	अगर (adapter->flags & NETXEN_FW_MSS_CAP)
		skb_shinfo(skb)->gso_size  =  netxen_get_lro_sts_mss(sts_data1);

	netअगर_receive_skb(skb);

	adapter->stats.lro_pkts++;
	adapter->stats.rxbytes += length;

	वापस buffer;
पूर्ण

#घोषणा netxen_merge_rx_buffers(list, head) \
	करो अणु list_splice_tail_init(list, head); पूर्ण जबतक (0);

पूर्णांक
netxen_process_rcv_ring(काष्ठा nx_host_sds_ring *sds_ring, पूर्णांक max)
अणु
	काष्ठा netxen_adapter *adapter = sds_ring->adapter;

	काष्ठा list_head *cur;

	काष्ठा status_desc *desc;
	काष्ठा netxen_rx_buffer *rxbuf;

	u32 consumer = sds_ring->consumer;

	पूर्णांक count = 0;
	u64 sts_data0, sts_data1;
	पूर्णांक opcode, ring = 0, desc_cnt;

	जबतक (count < max) अणु
		desc = &sds_ring->desc_head[consumer];
		sts_data0 = le64_to_cpu(desc->status_desc_data[0]);

		अगर (!(sts_data0 & STATUS_OWNER_HOST))
			अवरोध;

		desc_cnt = netxen_get_sts_desc_cnt(sts_data0);

		opcode = netxen_get_sts_opcode(sts_data0);

		चयन (opcode) अणु
		हाल NETXEN_NIC_RXPKT_DESC:
		हाल NETXEN_OLD_RXPKT_DESC:
		हाल NETXEN_NIC_SYN_OFFLOAD:
			ring = netxen_get_sts_type(sts_data0);
			rxbuf = netxen_process_rcv(adapter, sds_ring,
					ring, sts_data0);
			अवरोध;
		हाल NETXEN_NIC_LRO_DESC:
			ring = netxen_get_lro_sts_type(sts_data0);
			sts_data1 = le64_to_cpu(desc->status_desc_data[1]);
			rxbuf = netxen_process_lro(adapter, sds_ring,
					ring, sts_data0, sts_data1);
			अवरोध;
		हाल NETXEN_NIC_RESPONSE_DESC:
			netxen_handle_fw_message(desc_cnt, consumer, sds_ring);
		शेष:
			जाओ skip;
		पूर्ण

		WARN_ON(desc_cnt > 1);

		अगर (rxbuf)
			list_add_tail(&rxbuf->list, &sds_ring->मुक्त_list[ring]);

skip:
		क्रम (; desc_cnt > 0; desc_cnt--) अणु
			desc = &sds_ring->desc_head[consumer];
			desc->status_desc_data[0] =
				cpu_to_le64(STATUS_OWNER_PHANTOM);
			consumer = get_next_index(consumer, sds_ring->num_desc);
		पूर्ण
		count++;
	पूर्ण

	क्रम (ring = 0; ring < adapter->max_rds_rings; ring++) अणु
		काष्ठा nx_host_rds_ring *rds_ring =
			&adapter->recv_ctx.rds_rings[ring];

		अगर (!list_empty(&sds_ring->मुक्त_list[ring])) अणु
			list_क्रम_each(cur, &sds_ring->मुक्त_list[ring]) अणु
				rxbuf = list_entry(cur,
						काष्ठा netxen_rx_buffer, list);
				netxen_alloc_rx_skb(adapter, rds_ring, rxbuf);
			पूर्ण
			spin_lock(&rds_ring->lock);
			netxen_merge_rx_buffers(&sds_ring->मुक्त_list[ring],
						&rds_ring->मुक्त_list);
			spin_unlock(&rds_ring->lock);
		पूर्ण

		netxen_post_rx_buffers_nodb(adapter, rds_ring);
	पूर्ण

	अगर (count) अणु
		sds_ring->consumer = consumer;
		NXWRIO(adapter, sds_ring->crb_sts_consumer, consumer);
	पूर्ण

	वापस count;
पूर्ण

/* Process Command status ring */
पूर्णांक netxen_process_cmd_ring(काष्ठा netxen_adapter *adapter)
अणु
	u32 sw_consumer, hw_consumer;
	पूर्णांक count = 0, i;
	काष्ठा netxen_cmd_buffer *buffer;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा netxen_skb_frag *frag;
	पूर्णांक करोne = 0;
	काष्ठा nx_host_tx_ring *tx_ring = adapter->tx_ring;

	अगर (!spin_trylock_bh(&adapter->tx_clean_lock))
		वापस 1;

	sw_consumer = tx_ring->sw_consumer;
	hw_consumer = le32_to_cpu(*(tx_ring->hw_consumer));

	जबतक (sw_consumer != hw_consumer) अणु
		buffer = &tx_ring->cmd_buf_arr[sw_consumer];
		अगर (buffer->skb) अणु
			frag = &buffer->frag_array[0];
			dma_unmap_single(&pdev->dev, frag->dma, frag->length,
					 DMA_TO_DEVICE);
			frag->dma = 0ULL;
			क्रम (i = 1; i < buffer->frag_count; i++) अणु
				frag++;	/* Get the next frag */
				dma_unmap_page(&pdev->dev, frag->dma,
					       frag->length, DMA_TO_DEVICE);
				frag->dma = 0ULL;
			पूर्ण

			adapter->stats.xmitfinished++;
			dev_kमुक्त_skb_any(buffer->skb);
			buffer->skb = शून्य;
		पूर्ण

		sw_consumer = get_next_index(sw_consumer, tx_ring->num_desc);
		अगर (++count >= MAX_STATUS_HANDLE)
			अवरोध;
	पूर्ण

	tx_ring->sw_consumer = sw_consumer;

	अगर (count && netअगर_running(netdev)) अणु
		smp_mb();

		अगर (netअगर_queue_stopped(netdev) && netअगर_carrier_ok(netdev))
			अगर (netxen_tx_avail(tx_ring) > TX_STOP_THRESH)
				netअगर_wake_queue(netdev);
		adapter->tx_समयo_cnt = 0;
	पूर्ण
	/*
	 * If everything is मुक्तd up to consumer then check अगर the ring is full
	 * If the ring is full then check अगर more needs to be मुक्तd and
	 * schedule the call back again.
	 *
	 * This happens when there are 2 CPUs. One could be मुक्तing and the
	 * other filling it. If the ring is full when we get out of here and
	 * the card has alपढ़ोy पूर्णांकerrupted the host then the host can miss the
	 * पूर्णांकerrupt.
	 *
	 * There is still a possible race condition and the host could miss an
	 * पूर्णांकerrupt. The card has to take care of this.
	 */
	hw_consumer = le32_to_cpu(*(tx_ring->hw_consumer));
	करोne = (sw_consumer == hw_consumer);
	spin_unlock_bh(&adapter->tx_clean_lock);

	वापस करोne;
पूर्ण

व्योम
netxen_post_rx_buffers(काष्ठा netxen_adapter *adapter, u32 ringid,
	काष्ठा nx_host_rds_ring *rds_ring)
अणु
	काष्ठा rcv_desc *pdesc;
	काष्ठा netxen_rx_buffer *buffer;
	पूर्णांक producer, count = 0;
	netxen_ctx_msg msg = 0;
	काष्ठा list_head *head;

	producer = rds_ring->producer;

	head = &rds_ring->मुक्त_list;
	जबतक (!list_empty(head)) अणु

		buffer = list_entry(head->next, काष्ठा netxen_rx_buffer, list);

		अगर (!buffer->skb) अणु
			अगर (netxen_alloc_rx_skb(adapter, rds_ring, buffer))
				अवरोध;
		पूर्ण

		count++;
		list_del(&buffer->list);

		/* make a rcv descriptor  */
		pdesc = &rds_ring->desc_head[producer];
		pdesc->addr_buffer = cpu_to_le64(buffer->dma);
		pdesc->reference_handle = cpu_to_le16(buffer->ref_handle);
		pdesc->buffer_length = cpu_to_le32(rds_ring->dma_size);

		producer = get_next_index(producer, rds_ring->num_desc);
	पूर्ण

	अगर (count) अणु
		rds_ring->producer = producer;
		NXWRIO(adapter, rds_ring->crb_rcv_producer,
				(producer-1) & (rds_ring->num_desc-1));

		अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id)) अणु
			/*
			 * Write a करोorbell msg to tell phanmon of change in
			 * receive ring producer
			 * Only क्रम firmware version < 4.0.0
			 */
			netxen_set_msg_peg_id(msg, NETXEN_RCV_PEG_DB_ID);
			netxen_set_msg_privid(msg);
			netxen_set_msg_count(msg,
					     ((producer - 1) &
					      (rds_ring->num_desc - 1)));
			netxen_set_msg_ctxid(msg, adapter->portnum);
			netxen_set_msg_opcode(msg, NETXEN_RCV_PRODUCER(ringid));
			NXWRIO(adapter, DB_NORMALIZE(adapter,
					NETXEN_RCV_PRODUCER_OFFSET), msg);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
netxen_post_rx_buffers_nodb(काष्ठा netxen_adapter *adapter,
		काष्ठा nx_host_rds_ring *rds_ring)
अणु
	काष्ठा rcv_desc *pdesc;
	काष्ठा netxen_rx_buffer *buffer;
	पूर्णांक producer, count = 0;
	काष्ठा list_head *head;

	अगर (!spin_trylock(&rds_ring->lock))
		वापस;

	producer = rds_ring->producer;

	head = &rds_ring->मुक्त_list;
	जबतक (!list_empty(head)) अणु

		buffer = list_entry(head->next, काष्ठा netxen_rx_buffer, list);

		अगर (!buffer->skb) अणु
			अगर (netxen_alloc_rx_skb(adapter, rds_ring, buffer))
				अवरोध;
		पूर्ण

		count++;
		list_del(&buffer->list);

		/* make a rcv descriptor  */
		pdesc = &rds_ring->desc_head[producer];
		pdesc->reference_handle = cpu_to_le16(buffer->ref_handle);
		pdesc->buffer_length = cpu_to_le32(rds_ring->dma_size);
		pdesc->addr_buffer = cpu_to_le64(buffer->dma);

		producer = get_next_index(producer, rds_ring->num_desc);
	पूर्ण

	अगर (count) अणु
		rds_ring->producer = producer;
		NXWRIO(adapter, rds_ring->crb_rcv_producer,
				(producer - 1) & (rds_ring->num_desc - 1));
	पूर्ण
	spin_unlock(&rds_ring->lock);
पूर्ण

व्योम netxen_nic_clear_stats(काष्ठा netxen_adapter *adapter)
अणु
	स_रखो(&adapter->stats, 0, माप(adapter->stats));
पूर्ण

