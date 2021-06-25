<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2003 - 2009 NetXen, Inc.
 * Copyright (C) 2009 - QLogic Corporation.
 * All rights reserved.
 */

#समावेश "netxen_nic_hw.h"
#समावेश "netxen_nic.h"

#घोषणा NXHAL_VERSION	1

अटल u32
netxen_poll_rsp(काष्ठा netxen_adapter *adapter)
अणु
	u32 rsp = NX_CDRP_RSP_OK;
	पूर्णांक	समयout = 0;

	करो अणु
		/* give atleast 1ms क्रम firmware to respond */
		msleep(1);

		अगर (++समयout > NX_OS_CRB_RETRY_COUNT)
			वापस NX_CDRP_RSP_TIMEOUT;

		rsp = NXRD32(adapter, NX_CDRP_CRB_OFFSET);
	पूर्ण जबतक (!NX_CDRP_IS_RSP(rsp));

	वापस rsp;
पूर्ण

अटल u32
netxen_issue_cmd(काष्ठा netxen_adapter *adapter, काष्ठा netxen_cmd_args *cmd)
अणु
	u32 rsp;
	u32 signature = 0;
	u32 rcode = NX_RCODE_SUCCESS;

	signature = NX_CDRP_SIGNATURE_MAKE(adapter->ahw.pci_func,
						NXHAL_VERSION);
	/* Acquire semaphore beक्रमe accessing CRB */
	अगर (netxen_api_lock(adapter))
		वापस NX_RCODE_TIMEOUT;

	NXWR32(adapter, NX_SIGN_CRB_OFFSET, signature);

	NXWR32(adapter, NX_ARG1_CRB_OFFSET, cmd->req.arg1);

	NXWR32(adapter, NX_ARG2_CRB_OFFSET, cmd->req.arg2);

	NXWR32(adapter, NX_ARG3_CRB_OFFSET, cmd->req.arg3);

	NXWR32(adapter, NX_CDRP_CRB_OFFSET, NX_CDRP_FORM_CMD(cmd->req.cmd));

	rsp = netxen_poll_rsp(adapter);

	अगर (rsp == NX_CDRP_RSP_TIMEOUT) अणु
		prपूर्णांकk(KERN_ERR "%s: card response timeout.\n",
				netxen_nic_driver_name);

		rcode = NX_RCODE_TIMEOUT;
	पूर्ण अन्यथा अगर (rsp == NX_CDRP_RSP_FAIL) अणु
		rcode = NXRD32(adapter, NX_ARG1_CRB_OFFSET);

		prपूर्णांकk(KERN_ERR "%s: failed card response code:0x%x\n",
				netxen_nic_driver_name, rcode);
	पूर्ण अन्यथा अगर (rsp == NX_CDRP_RSP_OK) अणु
		cmd->rsp.cmd = NX_RCODE_SUCCESS;
		अगर (cmd->rsp.arg2)
			cmd->rsp.arg2 = NXRD32(adapter, NX_ARG2_CRB_OFFSET);
		अगर (cmd->rsp.arg3)
			cmd->rsp.arg3 = NXRD32(adapter, NX_ARG3_CRB_OFFSET);
	पूर्ण

	अगर (cmd->rsp.arg1)
		cmd->rsp.arg1 = NXRD32(adapter, NX_ARG1_CRB_OFFSET);
	/* Release semaphore */
	netxen_api_unlock(adapter);

	वापस rcode;
पूर्ण

अटल पूर्णांक
netxen_get_minidump_ढाँचा_size(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा netxen_cmd_args cmd;
	स_रखो(&cmd, 0, माप(cmd));
	cmd.req.cmd = NX_CDRP_CMD_TEMP_SIZE;
	स_रखो(&cmd.rsp, 1, माप(काष्ठा _cdrp_cmd));
	netxen_issue_cmd(adapter, &cmd);
	अगर (cmd.rsp.cmd != NX_RCODE_SUCCESS) अणु
		dev_info(&adapter->pdev->dev,
			"Can't get template size %d\n", cmd.rsp.cmd);
		वापस -EIO;
	पूर्ण
	adapter->mdump.md_ढाँचा_size = cmd.rsp.arg2;
	adapter->mdump.md_ढाँचा_ver = cmd.rsp.arg3;
	वापस 0;
पूर्ण

अटल पूर्णांक
netxen_get_minidump_ढाँचा(काष्ठा netxen_adapter *adapter)
अणु
	dma_addr_t md_ढाँचा_addr;
	व्योम *addr;
	u32 size;
	काष्ठा netxen_cmd_args cmd;
	size = adapter->mdump.md_ढाँचा_size;

	अगर (size == 0) अणु
		dev_err(&adapter->pdev->dev, "Can not capture Minidump "
			"template. Invalid template size.\n");
		वापस NX_RCODE_INVALID_ARGS;
	पूर्ण

	addr = dma_alloc_coherent(&adapter->pdev->dev, size,
				  &md_ढाँचा_addr, GFP_KERNEL);
	अगर (!addr) अणु
		dev_err(&adapter->pdev->dev, "Unable to allocate dmable memory for template.\n");
		वापस -ENOMEM;
	पूर्ण

	स_रखो(&cmd, 0, माप(cmd));
	स_रखो(&cmd.rsp, 1, माप(काष्ठा _cdrp_cmd));
	cmd.req.cmd = NX_CDRP_CMD_GET_TEMP_HDR;
	cmd.req.arg1 = LSD(md_ढाँचा_addr);
	cmd.req.arg2 = MSD(md_ढाँचा_addr);
	cmd.req.arg3 |= size;
	netxen_issue_cmd(adapter, &cmd);

	अगर ((cmd.rsp.cmd == NX_RCODE_SUCCESS) && (size == cmd.rsp.arg2)) अणु
		स_नकल(adapter->mdump.md_ढाँचा, addr, size);
	पूर्ण अन्यथा अणु
		dev_err(&adapter->pdev->dev, "Failed to get minidump template, err_code : %d, requested_size : %d, actual_size : %d\n",
			cmd.rsp.cmd, size, cmd.rsp.arg2);
	पूर्ण
	dma_मुक्त_coherent(&adapter->pdev->dev, size, addr, md_ढाँचा_addr);
	वापस 0;
पूर्ण

अटल u32
netxen_check_ढाँचा_checksum(काष्ठा netxen_adapter *adapter)
अणु
	u64 sum =  0 ;
	u32 *buff = adapter->mdump.md_ढाँचा;
	पूर्णांक count =  adapter->mdump.md_ढाँचा_size/माप(uपूर्णांक32_t) ;

	जबतक (count-- > 0)
		sum += *buff++ ;
	जबतक (sum >> 32)
		sum = (sum & 0xFFFFFFFF) +  (sum >> 32) ;

	वापस ~sum;
पूर्ण

पूर्णांक
netxen_setup_minidump(काष्ठा netxen_adapter *adapter)
अणु
	पूर्णांक err = 0, i;
	u32 *ढाँचा, *पंचांगp_buf;
	err = netxen_get_minidump_ढाँचा_size(adapter);
	अगर (err) अणु
		adapter->mdump.fw_supports_md = 0;
		अगर ((err == NX_RCODE_CMD_INVALID) ||
			(err == NX_RCODE_CMD_NOT_IMPL)) अणु
			dev_info(&adapter->pdev->dev,
				"Flashed firmware version does not support minidump, minimum version required is [ %u.%u.%u ]\n",
				NX_MD_SUPPORT_MAJOR, NX_MD_SUPPORT_MINOR,
				NX_MD_SUPPORT_SUBVERSION);
		पूर्ण
		वापस err;
	पूर्ण

	अगर (!adapter->mdump.md_ढाँचा_size) अणु
		dev_err(&adapter->pdev->dev, "Error : Invalid template size "
		",should be non-zero.\n");
		वापस -EIO;
	पूर्ण
	adapter->mdump.md_ढाँचा =
		kदो_स्मृति(adapter->mdump.md_ढाँचा_size, GFP_KERNEL);

	अगर (!adapter->mdump.md_ढाँचा)
		वापस -ENOMEM;

	err = netxen_get_minidump_ढाँचा(adapter);
	अगर (err) अणु
		अगर (err == NX_RCODE_CMD_NOT_IMPL)
			adapter->mdump.fw_supports_md = 0;
		जाओ मुक्त_ढाँचा;
	पूर्ण

	अगर (netxen_check_ढाँचा_checksum(adapter)) अणु
		dev_err(&adapter->pdev->dev, "Minidump template checksum Error\n");
		err = -EIO;
		जाओ मुक्त_ढाँचा;
	पूर्ण

	adapter->mdump.md_capture_mask = NX_DUMP_MASK_DEF;
	पंचांगp_buf = (u32 *) adapter->mdump.md_ढाँचा;
	ढाँचा = (u32 *) adapter->mdump.md_ढाँचा;
	क्रम (i = 0; i < adapter->mdump.md_ढाँचा_size/माप(u32); i++)
		*ढाँचा++ = __le32_to_cpu(*पंचांगp_buf++);
	adapter->mdump.md_capture_buff = शून्य;
	adapter->mdump.fw_supports_md = 1;
	adapter->mdump.md_enabled = 0;

	वापस err;

मुक्त_ढाँचा:
	kमुक्त(adapter->mdump.md_ढाँचा);
	adapter->mdump.md_ढाँचा = शून्य;
	वापस err;
पूर्ण


पूर्णांक
nx_fw_cmd_set_mtu(काष्ठा netxen_adapter *adapter, पूर्णांक mtu)
अणु
	u32 rcode = NX_RCODE_SUCCESS;
	काष्ठा netxen_recv_context *recv_ctx = &adapter->recv_ctx;
	काष्ठा netxen_cmd_args cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.req.cmd = NX_CDRP_CMD_SET_MTU;
	cmd.req.arg1 = recv_ctx->context_id;
	cmd.req.arg2 = mtu;
	cmd.req.arg3 = 0;

	अगर (recv_ctx->state == NX_HOST_CTX_STATE_ACTIVE)
		rcode = netxen_issue_cmd(adapter, &cmd);

	अगर (rcode != NX_RCODE_SUCCESS)
		वापस -EIO;

	वापस 0;
पूर्ण

पूर्णांक
nx_fw_cmd_set_gbe_port(काष्ठा netxen_adapter *adapter,
			u32 speed, u32 duplex, u32 स्वतःneg)
अणु
	काष्ठा netxen_cmd_args cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.req.cmd = NX_CDRP_CMD_CONFIG_GBE_PORT;
	cmd.req.arg1 = speed;
	cmd.req.arg2 = duplex;
	cmd.req.arg3 = स्वतःneg;
	वापस netxen_issue_cmd(adapter, &cmd);
पूर्ण

अटल पूर्णांक
nx_fw_cmd_create_rx_ctx(काष्ठा netxen_adapter *adapter)
अणु
	व्योम *addr;
	nx_hostrq_rx_ctx_t *prq;
	nx_cardrsp_rx_ctx_t *prsp;
	nx_hostrq_rds_ring_t *prq_rds;
	nx_hostrq_sds_ring_t *prq_sds;
	nx_cardrsp_rds_ring_t *prsp_rds;
	nx_cardrsp_sds_ring_t *prsp_sds;
	काष्ठा nx_host_rds_ring *rds_ring;
	काष्ठा nx_host_sds_ring *sds_ring;
	काष्ठा netxen_cmd_args cmd;

	dma_addr_t hostrq_phys_addr, cardrsp_phys_addr;
	u64 phys_addr;

	पूर्णांक i, nrds_rings, nsds_rings;
	माप_प्रकार rq_size, rsp_size;
	u32 cap, reg, val;

	पूर्णांक err;

	काष्ठा netxen_recv_context *recv_ctx = &adapter->recv_ctx;

	nrds_rings = adapter->max_rds_rings;
	nsds_rings = adapter->max_sds_rings;

	rq_size =
		SIZखातापूर्ण_HOSTRQ_RX(nx_hostrq_rx_ctx_t, nrds_rings, nsds_rings);
	rsp_size =
		SIZखातापूर्ण_CARDRSP_RX(nx_cardrsp_rx_ctx_t, nrds_rings, nsds_rings);

	addr = dma_alloc_coherent(&adapter->pdev->dev, rq_size,
				  &hostrq_phys_addr, GFP_KERNEL);
	अगर (addr == शून्य)
		वापस -ENOMEM;
	prq = addr;

	addr = dma_alloc_coherent(&adapter->pdev->dev, rsp_size,
				  &cardrsp_phys_addr, GFP_KERNEL);
	अगर (addr == शून्य) अणु
		err = -ENOMEM;
		जाओ out_मुक्त_rq;
	पूर्ण
	prsp = addr;

	prq->host_rsp_dma_addr = cpu_to_le64(cardrsp_phys_addr);

	cap = (NX_CAP0_LEGACY_CONTEXT | NX_CAP0_LEGACY_MN);
	cap |= (NX_CAP0_JUMBO_CONTIGUOUS | NX_CAP0_LRO_CONTIGUOUS);

	अगर (adapter->flags & NETXEN_FW_MSS_CAP)
		cap |= NX_CAP0_HW_LRO_MSS;

	prq->capabilities[0] = cpu_to_le32(cap);
	prq->host_पूर्णांक_crb_mode =
		cpu_to_le32(NX_HOST_INT_CRB_MODE_SHARED);
	prq->host_rds_crb_mode =
		cpu_to_le32(NX_HOST_RDS_CRB_MODE_UNIQUE);

	prq->num_rds_rings = cpu_to_le16(nrds_rings);
	prq->num_sds_rings = cpu_to_le16(nsds_rings);
	prq->rds_ring_offset = cpu_to_le32(0);

	val = le32_to_cpu(prq->rds_ring_offset) +
		(माप(nx_hostrq_rds_ring_t) * nrds_rings);
	prq->sds_ring_offset = cpu_to_le32(val);

	prq_rds = (nx_hostrq_rds_ring_t *)(prq->data +
			le32_to_cpu(prq->rds_ring_offset));

	क्रम (i = 0; i < nrds_rings; i++) अणु

		rds_ring = &recv_ctx->rds_rings[i];

		prq_rds[i].host_phys_addr = cpu_to_le64(rds_ring->phys_addr);
		prq_rds[i].ring_size = cpu_to_le32(rds_ring->num_desc);
		prq_rds[i].ring_kind = cpu_to_le32(i);
		prq_rds[i].buff_size = cpu_to_le64(rds_ring->dma_size);
	पूर्ण

	prq_sds = (nx_hostrq_sds_ring_t *)(prq->data +
			le32_to_cpu(prq->sds_ring_offset));

	क्रम (i = 0; i < nsds_rings; i++) अणु

		sds_ring = &recv_ctx->sds_rings[i];

		prq_sds[i].host_phys_addr = cpu_to_le64(sds_ring->phys_addr);
		prq_sds[i].ring_size = cpu_to_le32(sds_ring->num_desc);
		prq_sds[i].msi_index = cpu_to_le16(i);
	पूर्ण

	phys_addr = hostrq_phys_addr;
	स_रखो(&cmd, 0, माप(cmd));
	cmd.req.arg1 = (u32)(phys_addr >> 32);
	cmd.req.arg2 = (u32)(phys_addr & 0xffffffff);
	cmd.req.arg3 = rq_size;
	cmd.req.cmd = NX_CDRP_CMD_CREATE_RX_CTX;
	err = netxen_issue_cmd(adapter, &cmd);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING
			"Failed to create rx ctx in firmware%d\n", err);
		जाओ out_मुक्त_rsp;
	पूर्ण


	prsp_rds = ((nx_cardrsp_rds_ring_t *)
			 &prsp->data[le32_to_cpu(prsp->rds_ring_offset)]);

	क्रम (i = 0; i < le16_to_cpu(prsp->num_rds_rings); i++) अणु
		rds_ring = &recv_ctx->rds_rings[i];

		reg = le32_to_cpu(prsp_rds[i].host_producer_crb);
		rds_ring->crb_rcv_producer = netxen_get_ioaddr(adapter,
				NETXEN_NIC_REG(reg - 0x200));
	पूर्ण

	prsp_sds = ((nx_cardrsp_sds_ring_t *)
			&prsp->data[le32_to_cpu(prsp->sds_ring_offset)]);

	क्रम (i = 0; i < le16_to_cpu(prsp->num_sds_rings); i++) अणु
		sds_ring = &recv_ctx->sds_rings[i];

		reg = le32_to_cpu(prsp_sds[i].host_consumer_crb);
		sds_ring->crb_sts_consumer = netxen_get_ioaddr(adapter,
				NETXEN_NIC_REG(reg - 0x200));

		reg = le32_to_cpu(prsp_sds[i].पूर्णांकerrupt_crb);
		sds_ring->crb_पूर्णांकr_mask = netxen_get_ioaddr(adapter,
				NETXEN_NIC_REG(reg - 0x200));
	पूर्ण

	recv_ctx->state = le32_to_cpu(prsp->host_ctx_state);
	recv_ctx->context_id = le16_to_cpu(prsp->context_id);
	recv_ctx->virt_port = prsp->virt_port;

out_मुक्त_rsp:
	dma_मुक्त_coherent(&adapter->pdev->dev, rsp_size, prsp,
			  cardrsp_phys_addr);
out_मुक्त_rq:
	dma_मुक्त_coherent(&adapter->pdev->dev, rq_size, prq, hostrq_phys_addr);
	वापस err;
पूर्ण

अटल व्योम
nx_fw_cmd_destroy_rx_ctx(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा netxen_recv_context *recv_ctx = &adapter->recv_ctx;
	काष्ठा netxen_cmd_args cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.req.arg1 = recv_ctx->context_id;
	cmd.req.arg2 = NX_DESTROY_CTX_RESET;
	cmd.req.arg3 = 0;
	cmd.req.cmd = NX_CDRP_CMD_DESTROY_RX_CTX;

	अगर (netxen_issue_cmd(adapter, &cmd)) अणु
		prपूर्णांकk(KERN_WARNING
			"%s: Failed to destroy rx ctx in firmware\n",
			netxen_nic_driver_name);
	पूर्ण
पूर्ण

अटल पूर्णांक
nx_fw_cmd_create_tx_ctx(काष्ठा netxen_adapter *adapter)
अणु
	nx_hostrq_tx_ctx_t	*prq;
	nx_hostrq_cds_ring_t	*prq_cds;
	nx_cardrsp_tx_ctx_t	*prsp;
	व्योम	*rq_addr, *rsp_addr;
	माप_प्रकार	rq_size, rsp_size;
	u32	temp;
	पूर्णांक	err = 0;
	u64	offset, phys_addr;
	dma_addr_t	rq_phys_addr, rsp_phys_addr;
	काष्ठा nx_host_tx_ring *tx_ring = adapter->tx_ring;
	काष्ठा netxen_recv_context *recv_ctx = &adapter->recv_ctx;
	काष्ठा netxen_cmd_args cmd;

	rq_size = SIZखातापूर्ण_HOSTRQ_TX(nx_hostrq_tx_ctx_t);
	rq_addr = dma_alloc_coherent(&adapter->pdev->dev, rq_size,
				     &rq_phys_addr, GFP_KERNEL);
	अगर (!rq_addr)
		वापस -ENOMEM;

	rsp_size = SIZखातापूर्ण_CARDRSP_TX(nx_cardrsp_tx_ctx_t);
	rsp_addr = dma_alloc_coherent(&adapter->pdev->dev, rsp_size,
				      &rsp_phys_addr, GFP_KERNEL);
	अगर (!rsp_addr) अणु
		err = -ENOMEM;
		जाओ out_मुक्त_rq;
	पूर्ण

	prq = rq_addr;

	prsp = rsp_addr;

	prq->host_rsp_dma_addr = cpu_to_le64(rsp_phys_addr);

	temp = (NX_CAP0_LEGACY_CONTEXT | NX_CAP0_LEGACY_MN | NX_CAP0_LSO);
	prq->capabilities[0] = cpu_to_le32(temp);

	prq->host_पूर्णांक_crb_mode =
		cpu_to_le32(NX_HOST_INT_CRB_MODE_SHARED);

	prq->पूर्णांकerrupt_ctl = 0;
	prq->msi_index = 0;

	prq->dummy_dma_addr = cpu_to_le64(adapter->dummy_dma.phys_addr);

	offset = recv_ctx->phys_addr + माप(काष्ठा netxen_ring_ctx);
	prq->cmd_cons_dma_addr = cpu_to_le64(offset);

	prq_cds = &prq->cds_ring;

	prq_cds->host_phys_addr = cpu_to_le64(tx_ring->phys_addr);
	prq_cds->ring_size = cpu_to_le32(tx_ring->num_desc);

	phys_addr = rq_phys_addr;
	स_रखो(&cmd, 0, माप(cmd));
	cmd.req.arg1 = (u32)(phys_addr >> 32);
	cmd.req.arg2 = ((u32)phys_addr & 0xffffffff);
	cmd.req.arg3 = rq_size;
	cmd.req.cmd = NX_CDRP_CMD_CREATE_TX_CTX;
	err = netxen_issue_cmd(adapter, &cmd);

	अगर (err == NX_RCODE_SUCCESS) अणु
		temp = le32_to_cpu(prsp->cds_ring.host_producer_crb);
		tx_ring->crb_cmd_producer = netxen_get_ioaddr(adapter,
				NETXEN_NIC_REG(temp - 0x200));
#अगर 0
		adapter->tx_state =
			le32_to_cpu(prsp->host_ctx_state);
#पूर्ण_अगर
		adapter->tx_context_id =
			le16_to_cpu(prsp->context_id);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING
			"Failed to create tx ctx in firmware%d\n", err);
		err = -EIO;
	पूर्ण

	dma_मुक्त_coherent(&adapter->pdev->dev, rsp_size, rsp_addr,
			  rsp_phys_addr);

out_मुक्त_rq:
	dma_मुक्त_coherent(&adapter->pdev->dev, rq_size, rq_addr, rq_phys_addr);

	वापस err;
पूर्ण

अटल व्योम
nx_fw_cmd_destroy_tx_ctx(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा netxen_cmd_args cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.req.arg1 = adapter->tx_context_id;
	cmd.req.arg2 = NX_DESTROY_CTX_RESET;
	cmd.req.arg3 = 0;
	cmd.req.cmd = NX_CDRP_CMD_DESTROY_TX_CTX;
	अगर (netxen_issue_cmd(adapter, &cmd)) अणु
		prपूर्णांकk(KERN_WARNING
			"%s: Failed to destroy tx ctx in firmware\n",
			netxen_nic_driver_name);
	पूर्ण
पूर्ण

पूर्णांक
nx_fw_cmd_query_phy(काष्ठा netxen_adapter *adapter, u32 reg, u32 *val)
अणु
	u32 rcode;
	काष्ठा netxen_cmd_args cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.req.arg1 = reg;
	cmd.req.arg2 = 0;
	cmd.req.arg3 = 0;
	cmd.req.cmd = NX_CDRP_CMD_READ_PHY;
	cmd.rsp.arg1 = 1;
	rcode = netxen_issue_cmd(adapter, &cmd);
	अगर (rcode != NX_RCODE_SUCCESS)
		वापस -EIO;

	अगर (val == शून्य)
		वापस -EIO;

	*val = cmd.rsp.arg1;
	वापस 0;
पूर्ण

पूर्णांक
nx_fw_cmd_set_phy(काष्ठा netxen_adapter *adapter, u32 reg, u32 val)
अणु
	u32 rcode;
	काष्ठा netxen_cmd_args cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.req.arg1 = reg;
	cmd.req.arg2 = val;
	cmd.req.arg3 = 0;
	cmd.req.cmd = NX_CDRP_CMD_WRITE_PHY;
	rcode = netxen_issue_cmd(adapter, &cmd);
	अगर (rcode != NX_RCODE_SUCCESS)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल u64 ctx_addr_sig_regs[][3] = अणु
	अणुNETXEN_NIC_REG(0x188), NETXEN_NIC_REG(0x18c), NETXEN_NIC_REG(0x1c0)पूर्ण,
	अणुNETXEN_NIC_REG(0x190), NETXEN_NIC_REG(0x194), NETXEN_NIC_REG(0x1c4)पूर्ण,
	अणुNETXEN_NIC_REG(0x198), NETXEN_NIC_REG(0x19c), NETXEN_NIC_REG(0x1c8)पूर्ण,
	अणुNETXEN_NIC_REG(0x1a0), NETXEN_NIC_REG(0x1a4), NETXEN_NIC_REG(0x1cc)पूर्ण
पूर्ण;

#घोषणा CRB_CTX_ADDR_REG_LO(FUNC_ID)	(ctx_addr_sig_regs[FUNC_ID][0])
#घोषणा CRB_CTX_ADDR_REG_HI(FUNC_ID)	(ctx_addr_sig_regs[FUNC_ID][2])
#घोषणा CRB_CTX_SIGNATURE_REG(FUNC_ID)	(ctx_addr_sig_regs[FUNC_ID][1])

#घोषणा lower32(x)	((u32)((x) & 0xffffffff))
#घोषणा upper32(x)	((u32)(((u64)(x) >> 32) & 0xffffffff))

अटल काष्ठा netxen_recv_crb recv_crb_रेजिस्टरs[] = अणु
	/* Instance 0 */
	अणु
		/* crb_rcv_producer: */
		अणु
			NETXEN_NIC_REG(0x100),
			/* Jumbo frames */
			NETXEN_NIC_REG(0x110),
			/* LRO */
			NETXEN_NIC_REG(0x120)
		पूर्ण,
		/* crb_sts_consumer: */
		अणु
			NETXEN_NIC_REG(0x138),
			NETXEN_NIC_REG_2(0x000),
			NETXEN_NIC_REG_2(0x004),
			NETXEN_NIC_REG_2(0x008),
		पूर्ण,
		/* sw_पूर्णांक_mask */
		अणु
			CRB_SW_INT_MASK_0,
			NETXEN_NIC_REG_2(0x044),
			NETXEN_NIC_REG_2(0x048),
			NETXEN_NIC_REG_2(0x04c),
		पूर्ण,
	पूर्ण,
	/* Instance 1 */
	अणु
		/* crb_rcv_producer: */
		अणु
			NETXEN_NIC_REG(0x144),
			/* Jumbo frames */
			NETXEN_NIC_REG(0x154),
			/* LRO */
			NETXEN_NIC_REG(0x164)
		पूर्ण,
		/* crb_sts_consumer: */
		अणु
			NETXEN_NIC_REG(0x17c),
			NETXEN_NIC_REG_2(0x020),
			NETXEN_NIC_REG_2(0x024),
			NETXEN_NIC_REG_2(0x028),
		पूर्ण,
		/* sw_पूर्णांक_mask */
		अणु
			CRB_SW_INT_MASK_1,
			NETXEN_NIC_REG_2(0x064),
			NETXEN_NIC_REG_2(0x068),
			NETXEN_NIC_REG_2(0x06c),
		पूर्ण,
	पूर्ण,
	/* Instance 2 */
	अणु
		/* crb_rcv_producer: */
		अणु
			NETXEN_NIC_REG(0x1d8),
			/* Jumbo frames */
			NETXEN_NIC_REG(0x1f8),
			/* LRO */
			NETXEN_NIC_REG(0x208)
		पूर्ण,
		/* crb_sts_consumer: */
		अणु
			NETXEN_NIC_REG(0x220),
			NETXEN_NIC_REG_2(0x03c),
			NETXEN_NIC_REG_2(0x03c),
			NETXEN_NIC_REG_2(0x03c),
		पूर्ण,
		/* sw_पूर्णांक_mask */
		अणु
			CRB_SW_INT_MASK_2,
			NETXEN_NIC_REG_2(0x03c),
			NETXEN_NIC_REG_2(0x03c),
			NETXEN_NIC_REG_2(0x03c),
		पूर्ण,
	पूर्ण,
	/* Instance 3 */
	अणु
		/* crb_rcv_producer: */
		अणु
			NETXEN_NIC_REG(0x22c),
			/* Jumbo frames */
			NETXEN_NIC_REG(0x23c),
			/* LRO */
			NETXEN_NIC_REG(0x24c)
		पूर्ण,
		/* crb_sts_consumer: */
		अणु
			NETXEN_NIC_REG(0x264),
			NETXEN_NIC_REG_2(0x03c),
			NETXEN_NIC_REG_2(0x03c),
			NETXEN_NIC_REG_2(0x03c),
		पूर्ण,
		/* sw_पूर्णांक_mask */
		अणु
			CRB_SW_INT_MASK_3,
			NETXEN_NIC_REG_2(0x03c),
			NETXEN_NIC_REG_2(0x03c),
			NETXEN_NIC_REG_2(0x03c),
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक
netxen_init_old_ctx(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा netxen_recv_context *recv_ctx;
	काष्ठा nx_host_rds_ring *rds_ring;
	काष्ठा nx_host_sds_ring *sds_ring;
	काष्ठा nx_host_tx_ring *tx_ring;
	पूर्णांक ring;
	पूर्णांक port = adapter->portnum;
	काष्ठा netxen_ring_ctx *hwctx;
	u32 signature;

	tx_ring = adapter->tx_ring;
	recv_ctx = &adapter->recv_ctx;
	hwctx = recv_ctx->hwctx;

	hwctx->cmd_ring_addr = cpu_to_le64(tx_ring->phys_addr);
	hwctx->cmd_ring_size = cpu_to_le32(tx_ring->num_desc);


	क्रम (ring = 0; ring < adapter->max_rds_rings; ring++) अणु
		rds_ring = &recv_ctx->rds_rings[ring];

		hwctx->rcv_rings[ring].addr =
			cpu_to_le64(rds_ring->phys_addr);
		hwctx->rcv_rings[ring].size =
			cpu_to_le32(rds_ring->num_desc);
	पूर्ण

	क्रम (ring = 0; ring < adapter->max_sds_rings; ring++) अणु
		sds_ring = &recv_ctx->sds_rings[ring];

		अगर (ring == 0) अणु
			hwctx->sts_ring_addr = cpu_to_le64(sds_ring->phys_addr);
			hwctx->sts_ring_size = cpu_to_le32(sds_ring->num_desc);
		पूर्ण
		hwctx->sts_rings[ring].addr = cpu_to_le64(sds_ring->phys_addr);
		hwctx->sts_rings[ring].size = cpu_to_le32(sds_ring->num_desc);
		hwctx->sts_rings[ring].msi_index = cpu_to_le16(ring);
	पूर्ण
	hwctx->sts_ring_count = cpu_to_le32(adapter->max_sds_rings);

	signature = (adapter->max_sds_rings > 1) ?
		NETXEN_CTX_SIGNATURE_V2 : NETXEN_CTX_SIGNATURE;

	NXWR32(adapter, CRB_CTX_ADDR_REG_LO(port),
			lower32(recv_ctx->phys_addr));
	NXWR32(adapter, CRB_CTX_ADDR_REG_HI(port),
			upper32(recv_ctx->phys_addr));
	NXWR32(adapter, CRB_CTX_SIGNATURE_REG(port),
			signature | port);
	वापस 0;
पूर्ण

पूर्णांक netxen_alloc_hw_resources(काष्ठा netxen_adapter *adapter)
अणु
	व्योम *addr;
	पूर्णांक err = 0;
	पूर्णांक ring;
	काष्ठा netxen_recv_context *recv_ctx;
	काष्ठा nx_host_rds_ring *rds_ring;
	काष्ठा nx_host_sds_ring *sds_ring;
	काष्ठा nx_host_tx_ring *tx_ring;

	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक port = adapter->portnum;

	recv_ctx = &adapter->recv_ctx;
	tx_ring = adapter->tx_ring;

	addr = dma_alloc_coherent(&pdev->dev,
				  माप(काष्ठा netxen_ring_ctx) + माप(uपूर्णांक32_t),
				  &recv_ctx->phys_addr, GFP_KERNEL);
	अगर (addr == शून्य) अणु
		dev_err(&pdev->dev, "failed to allocate hw context\n");
		वापस -ENOMEM;
	पूर्ण

	recv_ctx->hwctx = addr;
	recv_ctx->hwctx->ctx_id = cpu_to_le32(port);
	recv_ctx->hwctx->cmd_consumer_offset =
		cpu_to_le64(recv_ctx->phys_addr +
			माप(काष्ठा netxen_ring_ctx));
	tx_ring->hw_consumer =
		(__le32 *)(((अक्षर *)addr) + माप(काष्ठा netxen_ring_ctx));

	/* cmd desc ring */
	addr = dma_alloc_coherent(&pdev->dev, TX_DESC_RINGSIZE(tx_ring),
				  &tx_ring->phys_addr, GFP_KERNEL);

	अगर (addr == शून्य) अणु
		dev_err(&pdev->dev, "%s: failed to allocate tx desc ring\n",
				netdev->name);
		err = -ENOMEM;
		जाओ err_out_मुक्त;
	पूर्ण

	tx_ring->desc_head = addr;

	क्रम (ring = 0; ring < adapter->max_rds_rings; ring++) अणु
		rds_ring = &recv_ctx->rds_rings[ring];
		addr = dma_alloc_coherent(&adapter->pdev->dev,
					  RCV_DESC_RINGSIZE(rds_ring),
					  &rds_ring->phys_addr, GFP_KERNEL);
		अगर (addr == शून्य) अणु
			dev_err(&pdev->dev,
				"%s: failed to allocate rds ring [%d]\n",
				netdev->name, ring);
			err = -ENOMEM;
			जाओ err_out_मुक्त;
		पूर्ण
		rds_ring->desc_head = addr;

		अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id))
			rds_ring->crb_rcv_producer =
				netxen_get_ioaddr(adapter,
			recv_crb_रेजिस्टरs[port].crb_rcv_producer[ring]);
	पूर्ण

	क्रम (ring = 0; ring < adapter->max_sds_rings; ring++) अणु
		sds_ring = &recv_ctx->sds_rings[ring];

		addr = dma_alloc_coherent(&adapter->pdev->dev,
					  STATUS_DESC_RINGSIZE(sds_ring),
					  &sds_ring->phys_addr, GFP_KERNEL);
		अगर (addr == शून्य) अणु
			dev_err(&pdev->dev,
				"%s: failed to allocate sds ring [%d]\n",
				netdev->name, ring);
			err = -ENOMEM;
			जाओ err_out_मुक्त;
		पूर्ण
		sds_ring->desc_head = addr;

		अगर (NX_IS_REVISION_P2(adapter->ahw.revision_id)) अणु
			sds_ring->crb_sts_consumer =
				netxen_get_ioaddr(adapter,
				recv_crb_रेजिस्टरs[port].crb_sts_consumer[ring]);

			sds_ring->crb_पूर्णांकr_mask =
				netxen_get_ioaddr(adapter,
				recv_crb_रेजिस्टरs[port].sw_पूर्णांक_mask[ring]);
		पूर्ण
	पूर्ण


	अगर (!NX_IS_REVISION_P2(adapter->ahw.revision_id)) अणु
		अगर (test_and_set_bit(__NX_FW_ATTACHED, &adapter->state))
			जाओ करोne;
		err = nx_fw_cmd_create_rx_ctx(adapter);
		अगर (err)
			जाओ err_out_मुक्त;
		err = nx_fw_cmd_create_tx_ctx(adapter);
		अगर (err)
			जाओ err_out_मुक्त;
	पूर्ण अन्यथा अणु
		err = netxen_init_old_ctx(adapter);
		अगर (err)
			जाओ err_out_मुक्त;
	पूर्ण

करोne:
	वापस 0;

err_out_मुक्त:
	netxen_मुक्त_hw_resources(adapter);
	वापस err;
पूर्ण

व्योम netxen_मुक्त_hw_resources(काष्ठा netxen_adapter *adapter)
अणु
	काष्ठा netxen_recv_context *recv_ctx;
	काष्ठा nx_host_rds_ring *rds_ring;
	काष्ठा nx_host_sds_ring *sds_ring;
	काष्ठा nx_host_tx_ring *tx_ring;
	पूर्णांक ring;

	पूर्णांक port = adapter->portnum;

	अगर (!NX_IS_REVISION_P2(adapter->ahw.revision_id)) अणु
		अगर (!test_and_clear_bit(__NX_FW_ATTACHED, &adapter->state))
			जाओ करोne;

		nx_fw_cmd_destroy_rx_ctx(adapter);
		nx_fw_cmd_destroy_tx_ctx(adapter);
	पूर्ण अन्यथा अणु
		netxen_api_lock(adapter);
		NXWR32(adapter, CRB_CTX_SIGNATURE_REG(port),
				NETXEN_CTX_D3_RESET | port);
		netxen_api_unlock(adapter);
	पूर्ण

	/* Allow dma queues to drain after context reset */
	msleep(20);

करोne:
	recv_ctx = &adapter->recv_ctx;

	अगर (recv_ctx->hwctx != शून्य) अणु
		dma_मुक्त_coherent(&adapter->pdev->dev,
				  माप(काष्ठा netxen_ring_ctx) + माप(uपूर्णांक32_t),
				  recv_ctx->hwctx, recv_ctx->phys_addr);
		recv_ctx->hwctx = शून्य;
	पूर्ण

	tx_ring = adapter->tx_ring;
	अगर (tx_ring->desc_head != शून्य) अणु
		dma_मुक्त_coherent(&adapter->pdev->dev,
				  TX_DESC_RINGSIZE(tx_ring),
				  tx_ring->desc_head, tx_ring->phys_addr);
		tx_ring->desc_head = शून्य;
	पूर्ण

	क्रम (ring = 0; ring < adapter->max_rds_rings; ring++) अणु
		rds_ring = &recv_ctx->rds_rings[ring];

		अगर (rds_ring->desc_head != शून्य) अणु
			dma_मुक्त_coherent(&adapter->pdev->dev,
					  RCV_DESC_RINGSIZE(rds_ring),
					  rds_ring->desc_head,
					  rds_ring->phys_addr);
			rds_ring->desc_head = शून्य;
		पूर्ण
	पूर्ण

	क्रम (ring = 0; ring < adapter->max_sds_rings; ring++) अणु
		sds_ring = &recv_ctx->sds_rings[ring];

		अगर (sds_ring->desc_head != शून्य) अणु
			dma_मुक्त_coherent(&adapter->pdev->dev,
					  STATUS_DESC_RINGSIZE(sds_ring),
					  sds_ring->desc_head,
					  sds_ring->phys_addr);
			sds_ring->desc_head = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

