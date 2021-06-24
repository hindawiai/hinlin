<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2010-2012 Solarflare Communications Inc.
 */
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश "net_driver.h"
#समावेश "efx.h"
#समावेश "efx_channels.h"
#समावेश "nic.h"
#समावेश "io.h"
#समावेश "mcdi.h"
#समावेश "filter.h"
#समावेश "mcdi_pcol.h"
#समावेश "farch_regs.h"
#समावेश "siena_sriov.h"
#समावेश "vfdi.h"

/* Number of दीर्घs required to track all the VIs in a VF */
#घोषणा VI_MASK_LENGTH BITS_TO_LONGS(1 << EFX_VI_SCALE_MAX)

/* Maximum number of RX queues supported */
#घोषणा VF_MAX_RX_QUEUES 63

/**
 * क्रमागत efx_vf_tx_filter_mode - TX MAC filtering behaviour
 * @VF_TX_FILTER_OFF: Disabled
 * @VF_TX_FILTER_AUTO: Enabled अगर MAC address asचिन्हित to VF and only
 *	2 TX queues allowed per VF.
 * @VF_TX_FILTER_ON: Enabled
 */
क्रमागत efx_vf_tx_filter_mode अणु
	VF_TX_FILTER_OFF,
	VF_TX_FILTER_AUTO,
	VF_TX_FILTER_ON,
पूर्ण;

/**
 * काष्ठा siena_vf - Back-end resource and protocol state क्रम a PCI VF
 * @efx: The Efx NIC owning this VF
 * @pci_rid: The PCI requester ID क्रम this VF
 * @pci_name: The PCI name (क्रमmatted address) of this VF
 * @index: Index of VF within its port and PF.
 * @req: VFDI incoming request work item. Incoming USR_EV events are received
 *	by the NAPI handler, but must be handled by executing MCDI requests
 *	inside a work item.
 * @req_addr: VFDI incoming request DMA address (in VF's PCI address space).
 * @req_type: Expected next incoming (from VF) %VFDI_EV_TYPE member.
 * @req_seqno: Expected next incoming (from VF) %VFDI_EV_SEQ member.
 * @msg_seqno: Next %VFDI_EV_SEQ member to reply to VF. Protected by
 *	@status_lock
 * @busy: VFDI request queued to be processed or being processed. Receiving
 *	a VFDI request when @busy is set is an error condition.
 * @buf: Incoming VFDI requests are DMA from the VF पूर्णांकo this buffer.
 * @buftbl_base: Buffer table entries क्रम this VF start at this index.
 * @rx_filtering: Receive filtering has been requested by the VF driver.
 * @rx_filter_flags: The flags sent in the %VFDI_OP_INSERT_FILTER request.
 * @rx_filter_qid: VF relative qid क्रम RX filter requested by VF.
 * @rx_filter_id: Receive MAC filter ID. Only one filter per VF is supported.
 * @tx_filter_mode: Transmit MAC filtering mode.
 * @tx_filter_id: Transmit MAC filter ID.
 * @addr: The MAC address and outer vlan tag of the VF.
 * @status_addr: VF DMA address of page क्रम &काष्ठा vfdi_status updates.
 * @status_lock: Mutex protecting @msg_seqno, @status_addr, @addr,
 *	@peer_page_addrs and @peer_page_count from simultaneous
 *	updates by the VM and consumption by
 *	efx_siena_sriov_update_vf_addr()
 * @peer_page_addrs: Poपूर्णांकer to an array of guest pages क्रम local addresses.
 * @peer_page_count: Number of entries in @peer_page_count.
 * @evq0_addrs: Array of guest pages backing evq0.
 * @evq0_count: Number of entries in @evq0_addrs.
 * @flush_रुकोq: रुको queue used by %VFDI_OP_FINI_ALL_QUEUES handler
 *	to रुको क्रम flush completions.
 * @txq_lock: Mutex क्रम TX queue allocation.
 * @txq_mask: Mask of initialized transmit queues.
 * @txq_count: Number of initialized transmit queues.
 * @rxq_mask: Mask of initialized receive queues.
 * @rxq_count: Number of initialized receive queues.
 * @rxq_retry_mask: Mask or receive queues that need to be flushed again
 *	due to flush failure.
 * @rxq_retry_count: Number of receive queues in @rxq_retry_mask.
 * @reset_work: Work item to schedule a VF reset.
 */
काष्ठा siena_vf अणु
	काष्ठा efx_nic *efx;
	अचिन्हित पूर्णांक pci_rid;
	अक्षर pci_name[13]; /* dddd:bb:dd.f */
	अचिन्हित पूर्णांक index;
	काष्ठा work_काष्ठा req;
	u64 req_addr;
	पूर्णांक req_type;
	अचिन्हित req_seqno;
	अचिन्हित msg_seqno;
	bool busy;
	काष्ठा efx_buffer buf;
	अचिन्हित buftbl_base;
	bool rx_filtering;
	क्रमागत efx_filter_flags rx_filter_flags;
	अचिन्हित rx_filter_qid;
	पूर्णांक rx_filter_id;
	क्रमागत efx_vf_tx_filter_mode tx_filter_mode;
	पूर्णांक tx_filter_id;
	काष्ठा vfdi_endpoपूर्णांक addr;
	u64 status_addr;
	काष्ठा mutex status_lock;
	u64 *peer_page_addrs;
	अचिन्हित peer_page_count;
	u64 evq0_addrs[EFX_MAX_VF_EVQ_SIZE * माप(efx_qword_t) /
		       EFX_BUF_SIZE];
	अचिन्हित evq0_count;
	रुको_queue_head_t flush_रुकोq;
	काष्ठा mutex txq_lock;
	अचिन्हित दीर्घ txq_mask[VI_MASK_LENGTH];
	अचिन्हित txq_count;
	अचिन्हित दीर्घ rxq_mask[VI_MASK_LENGTH];
	अचिन्हित rxq_count;
	अचिन्हित दीर्घ rxq_retry_mask[VI_MASK_LENGTH];
	atomic_t rxq_retry_count;
	काष्ठा work_काष्ठा reset_work;
पूर्ण;

काष्ठा efx_स_नकल_req अणु
	अचिन्हित पूर्णांक from_rid;
	व्योम *from_buf;
	u64 from_addr;
	अचिन्हित पूर्णांक to_rid;
	u64 to_addr;
	अचिन्हित length;
पूर्ण;

/**
 * काष्ठा efx_local_addr - A MAC address on the vचयन without a VF.
 *
 * Siena करोes not have a चयन, so VFs can't transmit data to each
 * other. Instead the VFs must be made aware of the local addresses
 * on the vचयन, so that they can arrange क्रम an alternative
 * software datapath to be used.
 *
 * @link: List head क्रम insertion पूर्णांकo efx->local_addr_list.
 * @addr: Ethernet address
 */
काष्ठा efx_local_addr अणु
	काष्ठा list_head link;
	u8 addr[ETH_ALEN];
पूर्ण;

/**
 * काष्ठा efx_endpoपूर्णांक_page - Page of vfdi_endpoपूर्णांक काष्ठाures
 *
 * @link: List head क्रम insertion पूर्णांकo efx->local_page_list.
 * @ptr: Poपूर्णांकer to page.
 * @addr: DMA address of page.
 */
काष्ठा efx_endpoपूर्णांक_page अणु
	काष्ठा list_head link;
	व्योम *ptr;
	dma_addr_t addr;
पूर्ण;

/* Buffer table entries are reserved txq0,rxq0,evq0,txq1,rxq1,evq1 */
#घोषणा EFX_BUFTBL_TXQ_BASE(_vf, _qid)					\
	((_vf)->buftbl_base + EFX_VF_BUFTBL_PER_VI * (_qid))
#घोषणा EFX_BUFTBL_RXQ_BASE(_vf, _qid)					\
	(EFX_BUFTBL_TXQ_BASE(_vf, _qid) +				\
	 (EFX_MAX_DMAQ_SIZE * माप(efx_qword_t) / EFX_BUF_SIZE))
#घोषणा EFX_BUFTBL_EVQ_BASE(_vf, _qid)					\
	(EFX_BUFTBL_TXQ_BASE(_vf, _qid) +				\
	 (2 * EFX_MAX_DMAQ_SIZE * माप(efx_qword_t) / EFX_BUF_SIZE))

#घोषणा EFX_FIELD_MASK(_field)			\
	((1 << _field ## _WIDTH) - 1)

/* VFs can only use this many transmit channels */
अटल अचिन्हित पूर्णांक vf_max_tx_channels = 2;
module_param(vf_max_tx_channels, uपूर्णांक, 0444);
MODULE_PARM_DESC(vf_max_tx_channels,
		 "Limit the number of TX channels VFs can use");

अटल पूर्णांक max_vfs = -1;
module_param(max_vfs, पूर्णांक, 0444);
MODULE_PARM_DESC(max_vfs,
		 "Reduce the number of VFs initialized by the driver");

/* Workqueue used by VFDI communication.  We can't use the global
 * workqueue because it may be running the VF driver's probe()
 * routine, which will be blocked there रुकोing क्रम a VFDI response.
 */
अटल काष्ठा workqueue_काष्ठा *vfdi_workqueue;

अटल अचिन्हित असल_index(काष्ठा siena_vf *vf, अचिन्हित index)
अणु
	वापस EFX_VI_BASE + vf->index * efx_vf_size(vf->efx) + index;
पूर्ण

अटल पूर्णांक efx_siena_sriov_cmd(काष्ठा efx_nic *efx, bool enable,
			       अचिन्हित *vi_scale_out, अचिन्हित *vf_total_out)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_SRIOV_IN_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_SRIOV_OUT_LEN);
	अचिन्हित vi_scale, vf_total;
	माप_प्रकार outlen;
	पूर्णांक rc;

	MCDI_SET_DWORD(inbuf, SRIOV_IN_ENABLE, enable ? 1 : 0);
	MCDI_SET_DWORD(inbuf, SRIOV_IN_VI_BASE, EFX_VI_BASE);
	MCDI_SET_DWORD(inbuf, SRIOV_IN_VF_COUNT, efx->vf_count);

	rc = efx_mcdi_rpc_quiet(efx, MC_CMD_SRIOV, inbuf, MC_CMD_SRIOV_IN_LEN,
				outbuf, MC_CMD_SRIOV_OUT_LEN, &outlen);
	अगर (rc)
		वापस rc;
	अगर (outlen < MC_CMD_SRIOV_OUT_LEN)
		वापस -EIO;

	vf_total = MCDI_DWORD(outbuf, SRIOV_OUT_VF_TOTAL);
	vi_scale = MCDI_DWORD(outbuf, SRIOV_OUT_VI_SCALE);
	अगर (vi_scale > EFX_VI_SCALE_MAX)
		वापस -EOPNOTSUPP;

	अगर (vi_scale_out)
		*vi_scale_out = vi_scale;
	अगर (vf_total_out)
		*vf_total_out = vf_total;

	वापस 0;
पूर्ण

अटल व्योम efx_siena_sriov_usrev(काष्ठा efx_nic *efx, bool enabled)
अणु
	काष्ठा siena_nic_data *nic_data = efx->nic_data;
	efx_oword_t reg;

	EFX_POPULATE_OWORD_2(reg,
			     FRF_CZ_USREV_DIS, enabled ? 0 : 1,
			     FRF_CZ_DFLT_EVQ, nic_data->vfdi_channel->channel);
	efx_ग_लिखोo(efx, &reg, FR_CZ_USR_EV_CFG);
पूर्ण

अटल पूर्णांक efx_siena_sriov_स_नकल(काष्ठा efx_nic *efx,
				  काष्ठा efx_स_नकल_req *req,
				  अचिन्हित पूर्णांक count)
अणु
	MCDI_DECLARE_BUF(inbuf, MCDI_CTL_SDU_LEN_MAX_V1);
	MCDI_DECLARE_STRUCT_PTR(record);
	अचिन्हित पूर्णांक index, used;
	u64 from_addr;
	u32 from_rid;
	पूर्णांक rc;

	mb();	/* Finish writing source/पढ़ोing dest beक्रमe DMA starts */

	अगर (WARN_ON(count > MC_CMD_MEMCPY_IN_RECORD_MAXNUM))
		वापस -ENOBUFS;
	used = MC_CMD_MEMCPY_IN_LEN(count);

	क्रम (index = 0; index < count; index++) अणु
		record = MCDI_ARRAY_STRUCT_PTR(inbuf, MEMCPY_IN_RECORD, index);
		MCDI_SET_DWORD(record, MEMCPY_RECORD_TYPEDEF_NUM_RECORDS,
			       count);
		MCDI_SET_DWORD(record, MEMCPY_RECORD_TYPEDEF_TO_RID,
			       req->to_rid);
		MCDI_SET_QWORD(record, MEMCPY_RECORD_TYPEDEF_TO_ADDR,
			       req->to_addr);
		अगर (req->from_buf == शून्य) अणु
			from_rid = req->from_rid;
			from_addr = req->from_addr;
		पूर्ण अन्यथा अणु
			अगर (WARN_ON(used + req->length >
				    MCDI_CTL_SDU_LEN_MAX_V1)) अणु
				rc = -ENOBUFS;
				जाओ out;
			पूर्ण

			from_rid = MC_CMD_MEMCPY_RECORD_TYPEDEF_RID_INLINE;
			from_addr = used;
			स_नकल(_MCDI_PTR(inbuf, used), req->from_buf,
			       req->length);
			used += req->length;
		पूर्ण

		MCDI_SET_DWORD(record, MEMCPY_RECORD_TYPEDEF_FROM_RID, from_rid);
		MCDI_SET_QWORD(record, MEMCPY_RECORD_TYPEDEF_FROM_ADDR,
			       from_addr);
		MCDI_SET_DWORD(record, MEMCPY_RECORD_TYPEDEF_LENGTH,
			       req->length);

		++req;
	पूर्ण

	rc = efx_mcdi_rpc(efx, MC_CMD_MEMCPY, inbuf, used, शून्य, 0, शून्य);
out:
	mb();	/* Don't ग_लिखो source/पढ़ो dest beक्रमe DMA is complete */

	वापस rc;
पूर्ण

/* The TX filter is entirely controlled by this driver, and is modअगरied
 * underneath the feet of the VF
 */
अटल व्योम efx_siena_sriov_reset_tx_filter(काष्ठा siena_vf *vf)
अणु
	काष्ठा efx_nic *efx = vf->efx;
	काष्ठा efx_filter_spec filter;
	u16 vlan;
	पूर्णांक rc;

	अगर (vf->tx_filter_id != -1) अणु
		efx_filter_हटाओ_id_safe(efx, EFX_FILTER_PRI_REQUIRED,
					  vf->tx_filter_id);
		netअगर_dbg(efx, hw, efx->net_dev, "Removed vf %s tx filter %d\n",
			  vf->pci_name, vf->tx_filter_id);
		vf->tx_filter_id = -1;
	पूर्ण

	अगर (is_zero_ether_addr(vf->addr.mac_addr))
		वापस;

	/* Turn on TX filtering स्वतःmatically अगर not explicitly
	 * enabled or disabled.
	 */
	अगर (vf->tx_filter_mode == VF_TX_FILTER_AUTO && vf_max_tx_channels <= 2)
		vf->tx_filter_mode = VF_TX_FILTER_ON;

	vlan = ntohs(vf->addr.tci) & VLAN_VID_MASK;
	efx_filter_init_tx(&filter, असल_index(vf, 0));
	rc = efx_filter_set_eth_local(&filter,
				      vlan ? vlan : EFX_FILTER_VID_UNSPEC,
				      vf->addr.mac_addr);
	BUG_ON(rc);

	rc = efx_filter_insert_filter(efx, &filter, true);
	अगर (rc < 0) अणु
		netअगर_warn(efx, hw, efx->net_dev,
			   "Unable to migrate tx filter for vf %s\n",
			   vf->pci_name);
	पूर्ण अन्यथा अणु
		netअगर_dbg(efx, hw, efx->net_dev, "Inserted vf %s tx filter %d\n",
			  vf->pci_name, rc);
		vf->tx_filter_id = rc;
	पूर्ण
पूर्ण

/* The RX filter is managed here on behalf of the VF driver */
अटल व्योम efx_siena_sriov_reset_rx_filter(काष्ठा siena_vf *vf)
अणु
	काष्ठा efx_nic *efx = vf->efx;
	काष्ठा efx_filter_spec filter;
	u16 vlan;
	पूर्णांक rc;

	अगर (vf->rx_filter_id != -1) अणु
		efx_filter_हटाओ_id_safe(efx, EFX_FILTER_PRI_REQUIRED,
					  vf->rx_filter_id);
		netअगर_dbg(efx, hw, efx->net_dev, "Removed vf %s rx filter %d\n",
			  vf->pci_name, vf->rx_filter_id);
		vf->rx_filter_id = -1;
	पूर्ण

	अगर (!vf->rx_filtering || is_zero_ether_addr(vf->addr.mac_addr))
		वापस;

	vlan = ntohs(vf->addr.tci) & VLAN_VID_MASK;
	efx_filter_init_rx(&filter, EFX_FILTER_PRI_REQUIRED,
			   vf->rx_filter_flags,
			   असल_index(vf, vf->rx_filter_qid));
	rc = efx_filter_set_eth_local(&filter,
				      vlan ? vlan : EFX_FILTER_VID_UNSPEC,
				      vf->addr.mac_addr);
	BUG_ON(rc);

	rc = efx_filter_insert_filter(efx, &filter, true);
	अगर (rc < 0) अणु
		netअगर_warn(efx, hw, efx->net_dev,
			   "Unable to insert rx filter for vf %s\n",
			   vf->pci_name);
	पूर्ण अन्यथा अणु
		netअगर_dbg(efx, hw, efx->net_dev, "Inserted vf %s rx filter %d\n",
			  vf->pci_name, rc);
		vf->rx_filter_id = rc;
	पूर्ण
पूर्ण

अटल व्योम __efx_siena_sriov_update_vf_addr(काष्ठा siena_vf *vf)
अणु
	काष्ठा efx_nic *efx = vf->efx;
	काष्ठा siena_nic_data *nic_data = efx->nic_data;

	efx_siena_sriov_reset_tx_filter(vf);
	efx_siena_sriov_reset_rx_filter(vf);
	queue_work(vfdi_workqueue, &nic_data->peer_work);
पूर्ण

/* Push the peer list to this VF. The caller must hold status_lock to पूर्णांकerlock
 * with VFDI requests, and they must be serialised against manipulation of
 * local_page_list, either by acquiring local_lock or by running from
 * efx_siena_sriov_peer_work()
 */
अटल व्योम __efx_siena_sriov_push_vf_status(काष्ठा siena_vf *vf)
अणु
	काष्ठा efx_nic *efx = vf->efx;
	काष्ठा siena_nic_data *nic_data = efx->nic_data;
	काष्ठा vfdi_status *status = nic_data->vfdi_status.addr;
	काष्ठा efx_स_नकल_req copy[4];
	काष्ठा efx_endpoपूर्णांक_page *epp;
	अचिन्हित पूर्णांक pos, count;
	अचिन्हित data_offset;
	efx_qword_t event;

	WARN_ON(!mutex_is_locked(&vf->status_lock));
	WARN_ON(!vf->status_addr);

	status->local = vf->addr;
	status->generation_end = ++status->generation_start;

	स_रखो(copy, '\0', माप(copy));
	/* Write generation_start */
	copy[0].from_buf = &status->generation_start;
	copy[0].to_rid = vf->pci_rid;
	copy[0].to_addr = vf->status_addr + दुरत्व(काष्ठा vfdi_status,
						     generation_start);
	copy[0].length = माप(status->generation_start);
	/* DMA the rest of the काष्ठाure (excluding the generations). This
	 * assumes that the non-generation portion of vfdi_status is in
	 * one chunk starting at the version member.
	 */
	data_offset = दुरत्व(काष्ठा vfdi_status, version);
	copy[1].from_rid = efx->pci_dev->devfn;
	copy[1].from_addr = nic_data->vfdi_status.dma_addr + data_offset;
	copy[1].to_rid = vf->pci_rid;
	copy[1].to_addr = vf->status_addr + data_offset;
	copy[1].length =  status->length - data_offset;

	/* Copy the peer pages */
	pos = 2;
	count = 0;
	list_क्रम_each_entry(epp, &nic_data->local_page_list, link) अणु
		अगर (count == vf->peer_page_count) अणु
			/* The VF driver will know they need to provide more
			 * pages because peer_addr_count is too large.
			 */
			अवरोध;
		पूर्ण
		copy[pos].from_buf = शून्य;
		copy[pos].from_rid = efx->pci_dev->devfn;
		copy[pos].from_addr = epp->addr;
		copy[pos].to_rid = vf->pci_rid;
		copy[pos].to_addr = vf->peer_page_addrs[count];
		copy[pos].length = EFX_PAGE_SIZE;

		अगर (++pos == ARRAY_SIZE(copy)) अणु
			efx_siena_sriov_स_नकल(efx, copy, ARRAY_SIZE(copy));
			pos = 0;
		पूर्ण
		++count;
	पूर्ण

	/* Write generation_end */
	copy[pos].from_buf = &status->generation_end;
	copy[pos].to_rid = vf->pci_rid;
	copy[pos].to_addr = vf->status_addr + दुरत्व(काष्ठा vfdi_status,
						       generation_end);
	copy[pos].length = माप(status->generation_end);
	efx_siena_sriov_स_नकल(efx, copy, pos + 1);

	/* Notअगरy the guest */
	EFX_POPULATE_QWORD_3(event,
			     FSF_AZ_EV_CODE, FSE_CZ_EV_CODE_USER_EV,
			     VFDI_EV_SEQ, (vf->msg_seqno & 0xff),
			     VFDI_EV_TYPE, VFDI_EV_TYPE_STATUS);
	++vf->msg_seqno;
	efx_farch_generate_event(efx,
				 EFX_VI_BASE + vf->index * efx_vf_size(efx),
				 &event);
पूर्ण

अटल व्योम efx_siena_sriov_bufs(काष्ठा efx_nic *efx, अचिन्हित offset,
				 u64 *addr, अचिन्हित count)
अणु
	efx_qword_t buf;
	अचिन्हित pos;

	क्रम (pos = 0; pos < count; ++pos) अणु
		EFX_POPULATE_QWORD_3(buf,
				     FRF_AZ_BUF_ADR_REGION, 0,
				     FRF_AZ_BUF_ADR_FBUF,
				     addr ? addr[pos] >> 12 : 0,
				     FRF_AZ_BUF_OWNER_ID_FBUF, 0);
		efx_sram_ग_लिखोq(efx, efx->membase + FR_BZ_BUF_FULL_TBL,
				&buf, offset + pos);
	पूर्ण
पूर्ण

अटल bool bad_vf_index(काष्ठा efx_nic *efx, अचिन्हित index)
अणु
	वापस index >= efx_vf_size(efx);
पूर्ण

अटल bool bad_buf_count(अचिन्हित buf_count, अचिन्हित max_entry_count)
अणु
	अचिन्हित max_buf_count = max_entry_count *
		माप(efx_qword_t) / EFX_BUF_SIZE;

	वापस ((buf_count & (buf_count - 1)) || buf_count > max_buf_count);
पूर्ण

/* Check that VI specअगरied by per-port index beदीर्घs to a VF.
 * Optionally set VF index and VI index within the VF.
 */
अटल bool map_vi_index(काष्ठा efx_nic *efx, अचिन्हित असल_index,
			 काष्ठा siena_vf **vf_out, अचिन्हित *rel_index_out)
अणु
	काष्ठा siena_nic_data *nic_data = efx->nic_data;
	अचिन्हित vf_i;

	अगर (असल_index < EFX_VI_BASE)
		वापस true;
	vf_i = (असल_index - EFX_VI_BASE) / efx_vf_size(efx);
	अगर (vf_i >= efx->vf_init_count)
		वापस true;

	अगर (vf_out)
		*vf_out = nic_data->vf + vf_i;
	अगर (rel_index_out)
		*rel_index_out = असल_index % efx_vf_size(efx);
	वापस false;
पूर्ण

अटल पूर्णांक efx_vfdi_init_evq(काष्ठा siena_vf *vf)
अणु
	काष्ठा efx_nic *efx = vf->efx;
	काष्ठा vfdi_req *req = vf->buf.addr;
	अचिन्हित vf_evq = req->u.init_evq.index;
	अचिन्हित buf_count = req->u.init_evq.buf_count;
	अचिन्हित असल_evq = असल_index(vf, vf_evq);
	अचिन्हित buftbl = EFX_BUFTBL_EVQ_BASE(vf, vf_evq);
	efx_oword_t reg;

	अगर (bad_vf_index(efx, vf_evq) ||
	    bad_buf_count(buf_count, EFX_MAX_VF_EVQ_SIZE)) अणु
		अगर (net_ratelimit())
			netअगर_err(efx, hw, efx->net_dev,
				  "ERROR: Invalid INIT_EVQ from %s: evq %d bufs %d\n",
				  vf->pci_name, vf_evq, buf_count);
		वापस VFDI_RC_EINVAL;
	पूर्ण

	efx_siena_sriov_bufs(efx, buftbl, req->u.init_evq.addr, buf_count);

	EFX_POPULATE_OWORD_3(reg,
			     FRF_CZ_TIMER_Q_EN, 1,
			     FRF_CZ_HOST_NOTIFY_MODE, 0,
			     FRF_CZ_TIMER_MODE, FFE_CZ_TIMER_MODE_DIS);
	efx_ग_लिखोo_table(efx, &reg, FR_BZ_TIMER_TBL, असल_evq);
	EFX_POPULATE_OWORD_3(reg,
			     FRF_AZ_EVQ_EN, 1,
			     FRF_AZ_EVQ_SIZE, __ffs(buf_count),
			     FRF_AZ_EVQ_BUF_BASE_ID, buftbl);
	efx_ग_लिखोo_table(efx, &reg, FR_BZ_EVQ_PTR_TBL, असल_evq);

	अगर (vf_evq == 0) अणु
		स_नकल(vf->evq0_addrs, req->u.init_evq.addr,
		       buf_count * माप(u64));
		vf->evq0_count = buf_count;
	पूर्ण

	वापस VFDI_RC_SUCCESS;
पूर्ण

अटल पूर्णांक efx_vfdi_init_rxq(काष्ठा siena_vf *vf)
अणु
	काष्ठा efx_nic *efx = vf->efx;
	काष्ठा vfdi_req *req = vf->buf.addr;
	अचिन्हित vf_rxq = req->u.init_rxq.index;
	अचिन्हित vf_evq = req->u.init_rxq.evq;
	अचिन्हित buf_count = req->u.init_rxq.buf_count;
	अचिन्हित buftbl = EFX_BUFTBL_RXQ_BASE(vf, vf_rxq);
	अचिन्हित label;
	efx_oword_t reg;

	अगर (bad_vf_index(efx, vf_evq) || bad_vf_index(efx, vf_rxq) ||
	    vf_rxq >= VF_MAX_RX_QUEUES ||
	    bad_buf_count(buf_count, EFX_MAX_DMAQ_SIZE)) अणु
		अगर (net_ratelimit())
			netअगर_err(efx, hw, efx->net_dev,
				  "ERROR: Invalid INIT_RXQ from %s: rxq %d evq %d "
				  "buf_count %d\n", vf->pci_name, vf_rxq,
				  vf_evq, buf_count);
		वापस VFDI_RC_EINVAL;
	पूर्ण
	अगर (__test_and_set_bit(req->u.init_rxq.index, vf->rxq_mask))
		++vf->rxq_count;
	efx_siena_sriov_bufs(efx, buftbl, req->u.init_rxq.addr, buf_count);

	label = req->u.init_rxq.label & EFX_FIELD_MASK(FRF_AZ_RX_DESCQ_LABEL);
	EFX_POPULATE_OWORD_6(reg,
			     FRF_AZ_RX_DESCQ_BUF_BASE_ID, buftbl,
			     FRF_AZ_RX_DESCQ_EVQ_ID, असल_index(vf, vf_evq),
			     FRF_AZ_RX_DESCQ_LABEL, label,
			     FRF_AZ_RX_DESCQ_SIZE, __ffs(buf_count),
			     FRF_AZ_RX_DESCQ_JUMBO,
			     !!(req->u.init_rxq.flags &
				VFDI_RXQ_FLAG_SCATTER_EN),
			     FRF_AZ_RX_DESCQ_EN, 1);
	efx_ग_लिखोo_table(efx, &reg, FR_BZ_RX_DESC_PTR_TBL,
			 असल_index(vf, vf_rxq));

	वापस VFDI_RC_SUCCESS;
पूर्ण

अटल पूर्णांक efx_vfdi_init_txq(काष्ठा siena_vf *vf)
अणु
	काष्ठा efx_nic *efx = vf->efx;
	काष्ठा vfdi_req *req = vf->buf.addr;
	अचिन्हित vf_txq = req->u.init_txq.index;
	अचिन्हित vf_evq = req->u.init_txq.evq;
	अचिन्हित buf_count = req->u.init_txq.buf_count;
	अचिन्हित buftbl = EFX_BUFTBL_TXQ_BASE(vf, vf_txq);
	अचिन्हित label, eth_filt_en;
	efx_oword_t reg;

	अगर (bad_vf_index(efx, vf_evq) || bad_vf_index(efx, vf_txq) ||
	    vf_txq >= vf_max_tx_channels ||
	    bad_buf_count(buf_count, EFX_MAX_DMAQ_SIZE)) अणु
		अगर (net_ratelimit())
			netअगर_err(efx, hw, efx->net_dev,
				  "ERROR: Invalid INIT_TXQ from %s: txq %d evq %d "
				  "buf_count %d\n", vf->pci_name, vf_txq,
				  vf_evq, buf_count);
		वापस VFDI_RC_EINVAL;
	पूर्ण

	mutex_lock(&vf->txq_lock);
	अगर (__test_and_set_bit(req->u.init_txq.index, vf->txq_mask))
		++vf->txq_count;
	mutex_unlock(&vf->txq_lock);
	efx_siena_sriov_bufs(efx, buftbl, req->u.init_txq.addr, buf_count);

	eth_filt_en = vf->tx_filter_mode == VF_TX_FILTER_ON;

	label = req->u.init_txq.label & EFX_FIELD_MASK(FRF_AZ_TX_DESCQ_LABEL);
	EFX_POPULATE_OWORD_8(reg,
			     FRF_CZ_TX_DPT_Q_MASK_WIDTH, min(efx->vi_scale, 1U),
			     FRF_CZ_TX_DPT_ETH_FILT_EN, eth_filt_en,
			     FRF_AZ_TX_DESCQ_EN, 1,
			     FRF_AZ_TX_DESCQ_BUF_BASE_ID, buftbl,
			     FRF_AZ_TX_DESCQ_EVQ_ID, असल_index(vf, vf_evq),
			     FRF_AZ_TX_DESCQ_LABEL, label,
			     FRF_AZ_TX_DESCQ_SIZE, __ffs(buf_count),
			     FRF_BZ_TX_NON_IP_DROP_DIS, 1);
	efx_ग_लिखोo_table(efx, &reg, FR_BZ_TX_DESC_PTR_TBL,
			 असल_index(vf, vf_txq));

	वापस VFDI_RC_SUCCESS;
पूर्ण

/* Returns true when efx_vfdi_fini_all_queues should wake */
अटल bool efx_vfdi_flush_wake(काष्ठा siena_vf *vf)
अणु
	/* Ensure that all updates are visible to efx_vfdi_fini_all_queues() */
	smp_mb();

	वापस (!vf->txq_count && !vf->rxq_count) ||
		atomic_पढ़ो(&vf->rxq_retry_count);
पूर्ण

अटल व्योम efx_vfdi_flush_clear(काष्ठा siena_vf *vf)
अणु
	स_रखो(vf->txq_mask, 0, माप(vf->txq_mask));
	vf->txq_count = 0;
	स_रखो(vf->rxq_mask, 0, माप(vf->rxq_mask));
	vf->rxq_count = 0;
	स_रखो(vf->rxq_retry_mask, 0, माप(vf->rxq_retry_mask));
	atomic_set(&vf->rxq_retry_count, 0);
पूर्ण

अटल पूर्णांक efx_vfdi_fini_all_queues(काष्ठा siena_vf *vf)
अणु
	काष्ठा efx_nic *efx = vf->efx;
	efx_oword_t reg;
	अचिन्हित count = efx_vf_size(efx);
	अचिन्हित vf_offset = EFX_VI_BASE + vf->index * efx_vf_size(efx);
	अचिन्हित समयout = HZ;
	अचिन्हित index, rxqs_count;
	MCDI_DECLARE_BUF(inbuf, MC_CMD_FLUSH_RX_QUEUES_IN_LENMAX);
	पूर्णांक rc;

	BUILD_BUG_ON(VF_MAX_RX_QUEUES >
		     MC_CMD_FLUSH_RX_QUEUES_IN_QID_OFST_MAXNUM);

	rtnl_lock();
	siena_prepare_flush(efx);
	rtnl_unlock();

	/* Flush all the initialized queues */
	rxqs_count = 0;
	क्रम (index = 0; index < count; ++index) अणु
		अगर (test_bit(index, vf->txq_mask)) अणु
			EFX_POPULATE_OWORD_2(reg,
					     FRF_AZ_TX_FLUSH_DESCQ_CMD, 1,
					     FRF_AZ_TX_FLUSH_DESCQ,
					     vf_offset + index);
			efx_ग_लिखोo(efx, &reg, FR_AZ_TX_FLUSH_DESCQ);
		पूर्ण
		अगर (test_bit(index, vf->rxq_mask)) अणु
			MCDI_SET_ARRAY_DWORD(
				inbuf, FLUSH_RX_QUEUES_IN_QID_OFST,
				rxqs_count, vf_offset + index);
			rxqs_count++;
		पूर्ण
	पूर्ण

	atomic_set(&vf->rxq_retry_count, 0);
	जबतक (समयout && (vf->rxq_count || vf->txq_count)) अणु
		rc = efx_mcdi_rpc(efx, MC_CMD_FLUSH_RX_QUEUES, inbuf,
				  MC_CMD_FLUSH_RX_QUEUES_IN_LEN(rxqs_count),
				  शून्य, 0, शून्य);
		WARN_ON(rc < 0);

		समयout = रुको_event_समयout(vf->flush_रुकोq,
					     efx_vfdi_flush_wake(vf),
					     समयout);
		rxqs_count = 0;
		क्रम (index = 0; index < count; ++index) अणु
			अगर (test_and_clear_bit(index, vf->rxq_retry_mask)) अणु
				atomic_dec(&vf->rxq_retry_count);
				MCDI_SET_ARRAY_DWORD(
					inbuf, FLUSH_RX_QUEUES_IN_QID_OFST,
					rxqs_count, vf_offset + index);
				rxqs_count++;
			पूर्ण
		पूर्ण
	पूर्ण

	rtnl_lock();
	siena_finish_flush(efx);
	rtnl_unlock();

	/* Irrespective of success/failure, fini the queues */
	EFX_ZERO_OWORD(reg);
	क्रम (index = 0; index < count; ++index) अणु
		efx_ग_लिखोo_table(efx, &reg, FR_BZ_RX_DESC_PTR_TBL,
				 vf_offset + index);
		efx_ग_लिखोo_table(efx, &reg, FR_BZ_TX_DESC_PTR_TBL,
				 vf_offset + index);
		efx_ग_लिखोo_table(efx, &reg, FR_BZ_EVQ_PTR_TBL,
				 vf_offset + index);
		efx_ग_लिखोo_table(efx, &reg, FR_BZ_TIMER_TBL,
				 vf_offset + index);
	पूर्ण
	efx_siena_sriov_bufs(efx, vf->buftbl_base, शून्य,
			     EFX_VF_BUFTBL_PER_VI * efx_vf_size(efx));
	efx_vfdi_flush_clear(vf);

	vf->evq0_count = 0;

	वापस समयout ? 0 : VFDI_RC_ETIMEDOUT;
पूर्ण

अटल पूर्णांक efx_vfdi_insert_filter(काष्ठा siena_vf *vf)
अणु
	काष्ठा efx_nic *efx = vf->efx;
	काष्ठा siena_nic_data *nic_data = efx->nic_data;
	काष्ठा vfdi_req *req = vf->buf.addr;
	अचिन्हित vf_rxq = req->u.mac_filter.rxq;
	अचिन्हित flags;

	अगर (bad_vf_index(efx, vf_rxq) || vf->rx_filtering) अणु
		अगर (net_ratelimit())
			netअगर_err(efx, hw, efx->net_dev,
				  "ERROR: Invalid INSERT_FILTER from %s: rxq %d "
				  "flags 0x%x\n", vf->pci_name, vf_rxq,
				  req->u.mac_filter.flags);
		वापस VFDI_RC_EINVAL;
	पूर्ण

	flags = 0;
	अगर (req->u.mac_filter.flags & VFDI_MAC_FILTER_FLAG_RSS)
		flags |= EFX_FILTER_FLAG_RX_RSS;
	अगर (req->u.mac_filter.flags & VFDI_MAC_FILTER_FLAG_SCATTER)
		flags |= EFX_FILTER_FLAG_RX_SCATTER;
	vf->rx_filter_flags = flags;
	vf->rx_filter_qid = vf_rxq;
	vf->rx_filtering = true;

	efx_siena_sriov_reset_rx_filter(vf);
	queue_work(vfdi_workqueue, &nic_data->peer_work);

	वापस VFDI_RC_SUCCESS;
पूर्ण

अटल पूर्णांक efx_vfdi_हटाओ_all_filters(काष्ठा siena_vf *vf)
अणु
	काष्ठा efx_nic *efx = vf->efx;
	काष्ठा siena_nic_data *nic_data = efx->nic_data;

	vf->rx_filtering = false;
	efx_siena_sriov_reset_rx_filter(vf);
	queue_work(vfdi_workqueue, &nic_data->peer_work);

	वापस VFDI_RC_SUCCESS;
पूर्ण

अटल पूर्णांक efx_vfdi_set_status_page(काष्ठा siena_vf *vf)
अणु
	काष्ठा efx_nic *efx = vf->efx;
	काष्ठा siena_nic_data *nic_data = efx->nic_data;
	काष्ठा vfdi_req *req = vf->buf.addr;
	u64 page_count = req->u.set_status_page.peer_page_count;
	u64 max_page_count =
		(EFX_PAGE_SIZE -
		 दुरत्व(काष्ठा vfdi_req, u.set_status_page.peer_page_addr[0]))
		/ माप(req->u.set_status_page.peer_page_addr[0]);

	अगर (!req->u.set_status_page.dma_addr || page_count > max_page_count) अणु
		अगर (net_ratelimit())
			netअगर_err(efx, hw, efx->net_dev,
				  "ERROR: Invalid SET_STATUS_PAGE from %s\n",
				  vf->pci_name);
		वापस VFDI_RC_EINVAL;
	पूर्ण

	mutex_lock(&nic_data->local_lock);
	mutex_lock(&vf->status_lock);
	vf->status_addr = req->u.set_status_page.dma_addr;

	kमुक्त(vf->peer_page_addrs);
	vf->peer_page_addrs = शून्य;
	vf->peer_page_count = 0;

	अगर (page_count) अणु
		vf->peer_page_addrs = kसुस्मृति(page_count, माप(u64),
					      GFP_KERNEL);
		अगर (vf->peer_page_addrs) अणु
			स_नकल(vf->peer_page_addrs,
			       req->u.set_status_page.peer_page_addr,
			       page_count * माप(u64));
			vf->peer_page_count = page_count;
		पूर्ण
	पूर्ण

	__efx_siena_sriov_push_vf_status(vf);
	mutex_unlock(&vf->status_lock);
	mutex_unlock(&nic_data->local_lock);

	वापस VFDI_RC_SUCCESS;
पूर्ण

अटल पूर्णांक efx_vfdi_clear_status_page(काष्ठा siena_vf *vf)
अणु
	mutex_lock(&vf->status_lock);
	vf->status_addr = 0;
	mutex_unlock(&vf->status_lock);

	वापस VFDI_RC_SUCCESS;
पूर्ण

प्रकार पूर्णांक (*efx_vfdi_op_t)(काष्ठा siena_vf *vf);

अटल स्थिर efx_vfdi_op_t vfdi_ops[VFDI_OP_LIMIT] = अणु
	[VFDI_OP_INIT_EVQ] = efx_vfdi_init_evq,
	[VFDI_OP_INIT_TXQ] = efx_vfdi_init_txq,
	[VFDI_OP_INIT_RXQ] = efx_vfdi_init_rxq,
	[VFDI_OP_FINI_ALL_QUEUES] = efx_vfdi_fini_all_queues,
	[VFDI_OP_INSERT_FILTER] = efx_vfdi_insert_filter,
	[VFDI_OP_REMOVE_ALL_FILTERS] = efx_vfdi_हटाओ_all_filters,
	[VFDI_OP_SET_STATUS_PAGE] = efx_vfdi_set_status_page,
	[VFDI_OP_CLEAR_STATUS_PAGE] = efx_vfdi_clear_status_page,
पूर्ण;

अटल व्योम efx_siena_sriov_vfdi(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा siena_vf *vf = container_of(work, काष्ठा siena_vf, req);
	काष्ठा efx_nic *efx = vf->efx;
	काष्ठा vfdi_req *req = vf->buf.addr;
	काष्ठा efx_स_नकल_req copy[2];
	पूर्णांक rc;

	/* Copy this page पूर्णांकo the local address space */
	स_रखो(copy, '\0', माप(copy));
	copy[0].from_rid = vf->pci_rid;
	copy[0].from_addr = vf->req_addr;
	copy[0].to_rid = efx->pci_dev->devfn;
	copy[0].to_addr = vf->buf.dma_addr;
	copy[0].length = EFX_PAGE_SIZE;
	rc = efx_siena_sriov_स_नकल(efx, copy, 1);
	अगर (rc) अणु
		/* If we can't get the request, we can't reply to the caller */
		अगर (net_ratelimit())
			netअगर_err(efx, hw, efx->net_dev,
				  "ERROR: Unable to fetch VFDI request from %s rc %d\n",
				  vf->pci_name, -rc);
		vf->busy = false;
		वापस;
	पूर्ण

	अगर (req->op < VFDI_OP_LIMIT && vfdi_ops[req->op] != शून्य) अणु
		rc = vfdi_ops[req->op](vf);
		अगर (rc == 0) अणु
			netअगर_dbg(efx, hw, efx->net_dev,
				  "vfdi request %d from %s ok\n",
				  req->op, vf->pci_name);
		पूर्ण
	पूर्ण अन्यथा अणु
		netअगर_dbg(efx, hw, efx->net_dev,
			  "ERROR: Unrecognised request %d from VF %s addr "
			  "%llx\n", req->op, vf->pci_name,
			  (अचिन्हित दीर्घ दीर्घ)vf->req_addr);
		rc = VFDI_RC_EOPNOTSUPP;
	पूर्ण

	/* Allow subsequent VF requests */
	vf->busy = false;
	smp_wmb();

	/* Respond to the request */
	req->rc = rc;
	req->op = VFDI_OP_RESPONSE;

	स_रखो(copy, '\0', माप(copy));
	copy[0].from_buf = &req->rc;
	copy[0].to_rid = vf->pci_rid;
	copy[0].to_addr = vf->req_addr + दुरत्व(काष्ठा vfdi_req, rc);
	copy[0].length = माप(req->rc);
	copy[1].from_buf = &req->op;
	copy[1].to_rid = vf->pci_rid;
	copy[1].to_addr = vf->req_addr + दुरत्व(काष्ठा vfdi_req, op);
	copy[1].length = माप(req->op);

	(व्योम)efx_siena_sriov_स_नकल(efx, copy, ARRAY_SIZE(copy));
पूर्ण



/* After a reset the event queues inside the guests no दीर्घer exist. Fill the
 * event ring in guest memory with VFDI reset events, then (re-initialise) the
 * event queue to उठाओ an पूर्णांकerrupt. The guest driver will then recover.
 */

अटल व्योम efx_siena_sriov_reset_vf(काष्ठा siena_vf *vf,
				     काष्ठा efx_buffer *buffer)
अणु
	काष्ठा efx_nic *efx = vf->efx;
	काष्ठा efx_स_नकल_req copy_req[4];
	efx_qword_t event;
	अचिन्हित पूर्णांक pos, count, k, buftbl, असल_evq;
	efx_oword_t reg;
	efx_dword_t ptr;
	पूर्णांक rc;

	BUG_ON(buffer->len != EFX_PAGE_SIZE);

	अगर (!vf->evq0_count)
		वापस;
	BUG_ON(vf->evq0_count & (vf->evq0_count - 1));

	mutex_lock(&vf->status_lock);
	EFX_POPULATE_QWORD_3(event,
			     FSF_AZ_EV_CODE, FSE_CZ_EV_CODE_USER_EV,
			     VFDI_EV_SEQ, vf->msg_seqno,
			     VFDI_EV_TYPE, VFDI_EV_TYPE_RESET);
	vf->msg_seqno++;
	क्रम (pos = 0; pos < EFX_PAGE_SIZE; pos += माप(event))
		स_नकल(buffer->addr + pos, &event, माप(event));

	क्रम (pos = 0; pos < vf->evq0_count; pos += count) अणु
		count = min_t(अचिन्हित, vf->evq0_count - pos,
			      ARRAY_SIZE(copy_req));
		क्रम (k = 0; k < count; k++) अणु
			copy_req[k].from_buf = शून्य;
			copy_req[k].from_rid = efx->pci_dev->devfn;
			copy_req[k].from_addr = buffer->dma_addr;
			copy_req[k].to_rid = vf->pci_rid;
			copy_req[k].to_addr = vf->evq0_addrs[pos + k];
			copy_req[k].length = EFX_PAGE_SIZE;
		पूर्ण
		rc = efx_siena_sriov_स_नकल(efx, copy_req, count);
		अगर (rc) अणु
			अगर (net_ratelimit())
				netअगर_err(efx, hw, efx->net_dev,
					  "ERROR: Unable to notify %s of reset"
					  ": %d\n", vf->pci_name, -rc);
			अवरोध;
		पूर्ण
	पूर्ण

	/* Reinitialise, arm and trigger evq0 */
	असल_evq = असल_index(vf, 0);
	buftbl = EFX_BUFTBL_EVQ_BASE(vf, 0);
	efx_siena_sriov_bufs(efx, buftbl, vf->evq0_addrs, vf->evq0_count);

	EFX_POPULATE_OWORD_3(reg,
			     FRF_CZ_TIMER_Q_EN, 1,
			     FRF_CZ_HOST_NOTIFY_MODE, 0,
			     FRF_CZ_TIMER_MODE, FFE_CZ_TIMER_MODE_DIS);
	efx_ग_लिखोo_table(efx, &reg, FR_BZ_TIMER_TBL, असल_evq);
	EFX_POPULATE_OWORD_3(reg,
			     FRF_AZ_EVQ_EN, 1,
			     FRF_AZ_EVQ_SIZE, __ffs(vf->evq0_count),
			     FRF_AZ_EVQ_BUF_BASE_ID, buftbl);
	efx_ग_लिखोo_table(efx, &reg, FR_BZ_EVQ_PTR_TBL, असल_evq);
	EFX_POPULATE_DWORD_1(ptr, FRF_AZ_EVQ_RPTR, 0);
	efx_ग_लिखोd(efx, &ptr, FR_BZ_EVQ_RPTR + FR_BZ_EVQ_RPTR_STEP * असल_evq);

	mutex_unlock(&vf->status_lock);
पूर्ण

अटल व्योम efx_siena_sriov_reset_vf_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा siena_vf *vf = container_of(work, काष्ठा siena_vf, req);
	काष्ठा efx_nic *efx = vf->efx;
	काष्ठा efx_buffer buf;

	अगर (!efx_nic_alloc_buffer(efx, &buf, EFX_PAGE_SIZE, GFP_NOIO)) अणु
		efx_siena_sriov_reset_vf(vf, &buf);
		efx_nic_मुक्त_buffer(efx, &buf);
	पूर्ण
पूर्ण

अटल व्योम efx_siena_sriov_handle_no_channel(काष्ठा efx_nic *efx)
अणु
	netअगर_err(efx, drv, efx->net_dev,
		  "ERROR: IOV requires MSI-X and 1 additional interrupt"
		  "vector. IOV disabled\n");
	efx->vf_count = 0;
पूर्ण

अटल पूर्णांक efx_siena_sriov_probe_channel(काष्ठा efx_channel *channel)
अणु
	काष्ठा siena_nic_data *nic_data = channel->efx->nic_data;
	nic_data->vfdi_channel = channel;

	वापस 0;
पूर्ण

अटल व्योम
efx_siena_sriov_get_channel_name(काष्ठा efx_channel *channel,
				 अक्षर *buf, माप_प्रकार len)
अणु
	snम_लिखो(buf, len, "%s-iov", channel->efx->name);
पूर्ण

अटल स्थिर काष्ठा efx_channel_type efx_siena_sriov_channel_type = अणु
	.handle_no_channel	= efx_siena_sriov_handle_no_channel,
	.pre_probe		= efx_siena_sriov_probe_channel,
	.post_हटाओ		= efx_channel_dummy_op_व्योम,
	.get_name		= efx_siena_sriov_get_channel_name,
	/* no copy operation; channel must not be पुनः_स्मृतिated */
	.keep_eventq		= true,
पूर्ण;

व्योम efx_siena_sriov_probe(काष्ठा efx_nic *efx)
अणु
	अचिन्हित count;

	अगर (!max_vfs)
		वापस;

	अगर (efx_siena_sriov_cmd(efx, false, &efx->vi_scale, &count)) अणु
		netअगर_info(efx, probe, efx->net_dev, "no SR-IOV VFs probed\n");
		वापस;
	पूर्ण
	अगर (count > 0 && count > max_vfs)
		count = max_vfs;

	/* efx_nic_dimension_resources() will reduce vf_count as appopriate */
	efx->vf_count = count;

	efx->extra_channel_type[EFX_EXTRA_CHANNEL_IOV] = &efx_siena_sriov_channel_type;
पूर्ण

/* Copy the list of inभागidual addresses पूर्णांकo the vfdi_status.peers
 * array and auxiliary pages, रक्षित by %local_lock. Drop that lock
 * and then broadcast the address list to every VF.
 */
अटल व्योम efx_siena_sriov_peer_work(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा siena_nic_data *nic_data = container_of(data,
						       काष्ठा siena_nic_data,
						       peer_work);
	काष्ठा efx_nic *efx = nic_data->efx;
	काष्ठा vfdi_status *vfdi_status = nic_data->vfdi_status.addr;
	काष्ठा siena_vf *vf;
	काष्ठा efx_local_addr *local_addr;
	काष्ठा vfdi_endpoपूर्णांक *peer;
	काष्ठा efx_endpoपूर्णांक_page *epp;
	काष्ठा list_head pages;
	अचिन्हित पूर्णांक peer_space;
	अचिन्हित पूर्णांक peer_count;
	अचिन्हित पूर्णांक pos;

	mutex_lock(&nic_data->local_lock);

	/* Move the existing peer pages off %local_page_list */
	INIT_LIST_HEAD(&pages);
	list_splice_tail_init(&nic_data->local_page_list, &pages);

	/* Populate the VF addresses starting from entry 1 (entry 0 is
	 * the PF address)
	 */
	peer = vfdi_status->peers + 1;
	peer_space = ARRAY_SIZE(vfdi_status->peers) - 1;
	peer_count = 1;
	क्रम (pos = 0; pos < efx->vf_count; ++pos) अणु
		vf = nic_data->vf + pos;

		mutex_lock(&vf->status_lock);
		अगर (vf->rx_filtering && !is_zero_ether_addr(vf->addr.mac_addr)) अणु
			*peer++ = vf->addr;
			++peer_count;
			--peer_space;
			BUG_ON(peer_space == 0);
		पूर्ण
		mutex_unlock(&vf->status_lock);
	पूर्ण

	/* Fill the reमुख्यing addresses */
	list_क्रम_each_entry(local_addr, &nic_data->local_addr_list, link) अणु
		ether_addr_copy(peer->mac_addr, local_addr->addr);
		peer->tci = 0;
		++peer;
		++peer_count;
		अगर (--peer_space == 0) अणु
			अगर (list_empty(&pages)) अणु
				epp = kदो_स्मृति(माप(*epp), GFP_KERNEL);
				अगर (!epp)
					अवरोध;
				epp->ptr = dma_alloc_coherent(
					&efx->pci_dev->dev, EFX_PAGE_SIZE,
					&epp->addr, GFP_KERNEL);
				अगर (!epp->ptr) अणु
					kमुक्त(epp);
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				epp = list_first_entry(
					&pages, काष्ठा efx_endpoपूर्णांक_page, link);
				list_del(&epp->link);
			पूर्ण

			list_add_tail(&epp->link, &nic_data->local_page_list);
			peer = (काष्ठा vfdi_endpoपूर्णांक *)epp->ptr;
			peer_space = EFX_PAGE_SIZE / माप(काष्ठा vfdi_endpoपूर्णांक);
		पूर्ण
	पूर्ण
	vfdi_status->peer_count = peer_count;
	mutex_unlock(&nic_data->local_lock);

	/* Free any now unused endpoपूर्णांक pages */
	जबतक (!list_empty(&pages)) अणु
		epp = list_first_entry(
			&pages, काष्ठा efx_endpoपूर्णांक_page, link);
		list_del(&epp->link);
		dma_मुक्त_coherent(&efx->pci_dev->dev, EFX_PAGE_SIZE,
				  epp->ptr, epp->addr);
		kमुक्त(epp);
	पूर्ण

	/* Finally, push the pages */
	क्रम (pos = 0; pos < efx->vf_count; ++pos) अणु
		vf = nic_data->vf + pos;

		mutex_lock(&vf->status_lock);
		अगर (vf->status_addr)
			__efx_siena_sriov_push_vf_status(vf);
		mutex_unlock(&vf->status_lock);
	पूर्ण
पूर्ण

अटल व्योम efx_siena_sriov_मुक्त_local(काष्ठा efx_nic *efx)
अणु
	काष्ठा siena_nic_data *nic_data = efx->nic_data;
	काष्ठा efx_local_addr *local_addr;
	काष्ठा efx_endpoपूर्णांक_page *epp;

	जबतक (!list_empty(&nic_data->local_addr_list)) अणु
		local_addr = list_first_entry(&nic_data->local_addr_list,
					      काष्ठा efx_local_addr, link);
		list_del(&local_addr->link);
		kमुक्त(local_addr);
	पूर्ण

	जबतक (!list_empty(&nic_data->local_page_list)) अणु
		epp = list_first_entry(&nic_data->local_page_list,
				       काष्ठा efx_endpoपूर्णांक_page, link);
		list_del(&epp->link);
		dma_मुक्त_coherent(&efx->pci_dev->dev, EFX_PAGE_SIZE,
				  epp->ptr, epp->addr);
		kमुक्त(epp);
	पूर्ण
पूर्ण

अटल पूर्णांक efx_siena_sriov_vf_alloc(काष्ठा efx_nic *efx)
अणु
	अचिन्हित index;
	काष्ठा siena_vf *vf;
	काष्ठा siena_nic_data *nic_data = efx->nic_data;

	nic_data->vf = kसुस्मृति(efx->vf_count, माप(*nic_data->vf),
			       GFP_KERNEL);
	अगर (!nic_data->vf)
		वापस -ENOMEM;

	क्रम (index = 0; index < efx->vf_count; ++index) अणु
		vf = nic_data->vf + index;

		vf->efx = efx;
		vf->index = index;
		vf->rx_filter_id = -1;
		vf->tx_filter_mode = VF_TX_FILTER_AUTO;
		vf->tx_filter_id = -1;
		INIT_WORK(&vf->req, efx_siena_sriov_vfdi);
		INIT_WORK(&vf->reset_work, efx_siena_sriov_reset_vf_work);
		init_रुकोqueue_head(&vf->flush_रुकोq);
		mutex_init(&vf->status_lock);
		mutex_init(&vf->txq_lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम efx_siena_sriov_vfs_fini(काष्ठा efx_nic *efx)
अणु
	काष्ठा siena_nic_data *nic_data = efx->nic_data;
	काष्ठा siena_vf *vf;
	अचिन्हित पूर्णांक pos;

	क्रम (pos = 0; pos < efx->vf_count; ++pos) अणु
		vf = nic_data->vf + pos;

		efx_nic_मुक्त_buffer(efx, &vf->buf);
		kमुक्त(vf->peer_page_addrs);
		vf->peer_page_addrs = शून्य;
		vf->peer_page_count = 0;

		vf->evq0_count = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक efx_siena_sriov_vfs_init(काष्ठा efx_nic *efx)
अणु
	काष्ठा pci_dev *pci_dev = efx->pci_dev;
	काष्ठा siena_nic_data *nic_data = efx->nic_data;
	अचिन्हित index, devfn, sriov, buftbl_base;
	u16 offset, stride;
	काष्ठा siena_vf *vf;
	पूर्णांक rc;

	sriov = pci_find_ext_capability(pci_dev, PCI_EXT_CAP_ID_SRIOV);
	अगर (!sriov)
		वापस -ENOENT;

	pci_पढ़ो_config_word(pci_dev, sriov + PCI_SRIOV_VF_OFFSET, &offset);
	pci_पढ़ो_config_word(pci_dev, sriov + PCI_SRIOV_VF_STRIDE, &stride);

	buftbl_base = nic_data->vf_buftbl_base;
	devfn = pci_dev->devfn + offset;
	क्रम (index = 0; index < efx->vf_count; ++index) अणु
		vf = nic_data->vf + index;

		/* Reserve buffer entries */
		vf->buftbl_base = buftbl_base;
		buftbl_base += EFX_VF_BUFTBL_PER_VI * efx_vf_size(efx);

		vf->pci_rid = devfn;
		snम_लिखो(vf->pci_name, माप(vf->pci_name),
			 "%04x:%02x:%02x.%d",
			 pci_करोमुख्य_nr(pci_dev->bus), pci_dev->bus->number,
			 PCI_SLOT(devfn), PCI_FUNC(devfn));

		rc = efx_nic_alloc_buffer(efx, &vf->buf, EFX_PAGE_SIZE,
					  GFP_KERNEL);
		अगर (rc)
			जाओ fail;

		devfn += stride;
	पूर्ण

	वापस 0;

fail:
	efx_siena_sriov_vfs_fini(efx);
	वापस rc;
पूर्ण

पूर्णांक efx_siena_sriov_init(काष्ठा efx_nic *efx)
अणु
	काष्ठा net_device *net_dev = efx->net_dev;
	काष्ठा siena_nic_data *nic_data = efx->nic_data;
	काष्ठा vfdi_status *vfdi_status;
	पूर्णांक rc;

	/* Ensure there's room क्रम vf_channel */
	BUILD_BUG_ON(EFX_MAX_CHANNELS + 1 >= EFX_VI_BASE);
	/* Ensure that VI_BASE is aligned on VI_SCALE */
	BUILD_BUG_ON(EFX_VI_BASE & ((1 << EFX_VI_SCALE_MAX) - 1));

	अगर (efx->vf_count == 0)
		वापस 0;

	rc = efx_siena_sriov_cmd(efx, true, शून्य, शून्य);
	अगर (rc)
		जाओ fail_cmd;

	rc = efx_nic_alloc_buffer(efx, &nic_data->vfdi_status,
				  माप(*vfdi_status), GFP_KERNEL);
	अगर (rc)
		जाओ fail_status;
	vfdi_status = nic_data->vfdi_status.addr;
	स_रखो(vfdi_status, 0, माप(*vfdi_status));
	vfdi_status->version = 1;
	vfdi_status->length = माप(*vfdi_status);
	vfdi_status->max_tx_channels = vf_max_tx_channels;
	vfdi_status->vi_scale = efx->vi_scale;
	vfdi_status->rss_rxq_count = efx->rss_spपढ़ो;
	vfdi_status->peer_count = 1 + efx->vf_count;
	vfdi_status->समयr_quantum_ns = efx->समयr_quantum_ns;

	rc = efx_siena_sriov_vf_alloc(efx);
	अगर (rc)
		जाओ fail_alloc;

	mutex_init(&nic_data->local_lock);
	INIT_WORK(&nic_data->peer_work, efx_siena_sriov_peer_work);
	INIT_LIST_HEAD(&nic_data->local_addr_list);
	INIT_LIST_HEAD(&nic_data->local_page_list);

	rc = efx_siena_sriov_vfs_init(efx);
	अगर (rc)
		जाओ fail_vfs;

	rtnl_lock();
	ether_addr_copy(vfdi_status->peers[0].mac_addr, net_dev->dev_addr);
	efx->vf_init_count = efx->vf_count;
	rtnl_unlock();

	efx_siena_sriov_usrev(efx, true);

	/* At this poपूर्णांक we must be पढ़ोy to accept VFDI requests */

	rc = pci_enable_sriov(efx->pci_dev, efx->vf_count);
	अगर (rc)
		जाओ fail_pci;

	netअगर_info(efx, probe, net_dev,
		   "enabled SR-IOV for %d VFs, %d VI per VF\n",
		   efx->vf_count, efx_vf_size(efx));
	वापस 0;

fail_pci:
	efx_siena_sriov_usrev(efx, false);
	rtnl_lock();
	efx->vf_init_count = 0;
	rtnl_unlock();
	efx_siena_sriov_vfs_fini(efx);
fail_vfs:
	cancel_work_sync(&nic_data->peer_work);
	efx_siena_sriov_मुक्त_local(efx);
	kमुक्त(nic_data->vf);
fail_alloc:
	efx_nic_मुक्त_buffer(efx, &nic_data->vfdi_status);
fail_status:
	efx_siena_sriov_cmd(efx, false, शून्य, शून्य);
fail_cmd:
	वापस rc;
पूर्ण

व्योम efx_siena_sriov_fini(काष्ठा efx_nic *efx)
अणु
	काष्ठा siena_vf *vf;
	अचिन्हित पूर्णांक pos;
	काष्ठा siena_nic_data *nic_data = efx->nic_data;

	अगर (efx->vf_init_count == 0)
		वापस;

	/* Disable all पूर्णांकerfaces to reconfiguration */
	BUG_ON(nic_data->vfdi_channel->enabled);
	efx_siena_sriov_usrev(efx, false);
	rtnl_lock();
	efx->vf_init_count = 0;
	rtnl_unlock();

	/* Flush all reconfiguration work */
	क्रम (pos = 0; pos < efx->vf_count; ++pos) अणु
		vf = nic_data->vf + pos;
		cancel_work_sync(&vf->req);
		cancel_work_sync(&vf->reset_work);
	पूर्ण
	cancel_work_sync(&nic_data->peer_work);

	pci_disable_sriov(efx->pci_dev);

	/* Tear करोwn back-end state */
	efx_siena_sriov_vfs_fini(efx);
	efx_siena_sriov_मुक्त_local(efx);
	kमुक्त(nic_data->vf);
	efx_nic_मुक्त_buffer(efx, &nic_data->vfdi_status);
	efx_siena_sriov_cmd(efx, false, शून्य, शून्य);
पूर्ण

व्योम efx_siena_sriov_event(काष्ठा efx_channel *channel, efx_qword_t *event)
अणु
	काष्ठा efx_nic *efx = channel->efx;
	काष्ठा siena_vf *vf;
	अचिन्हित qid, seq, type, data;

	qid = EFX_QWORD_FIELD(*event, FSF_CZ_USER_QID);

	/* USR_EV_REG_VALUE is dword0, so access the VFDI_EV fields directly */
	BUILD_BUG_ON(FSF_CZ_USER_EV_REG_VALUE_LBN != 0);
	seq = EFX_QWORD_FIELD(*event, VFDI_EV_SEQ);
	type = EFX_QWORD_FIELD(*event, VFDI_EV_TYPE);
	data = EFX_QWORD_FIELD(*event, VFDI_EV_DATA);

	netअगर_vdbg(efx, hw, efx->net_dev,
		   "USR_EV event from qid %d seq 0x%x type %d data 0x%x\n",
		   qid, seq, type, data);

	अगर (map_vi_index(efx, qid, &vf, शून्य))
		वापस;
	अगर (vf->busy)
		जाओ error;

	अगर (type == VFDI_EV_TYPE_REQ_WORD0) अणु
		/* Resynchronise */
		vf->req_type = VFDI_EV_TYPE_REQ_WORD0;
		vf->req_seqno = seq + 1;
		vf->req_addr = 0;
	पूर्ण अन्यथा अगर (seq != (vf->req_seqno++ & 0xff) || type != vf->req_type)
		जाओ error;

	चयन (vf->req_type) अणु
	हाल VFDI_EV_TYPE_REQ_WORD0:
	हाल VFDI_EV_TYPE_REQ_WORD1:
	हाल VFDI_EV_TYPE_REQ_WORD2:
		vf->req_addr |= (u64)data << (vf->req_type << 4);
		++vf->req_type;
		वापस;

	हाल VFDI_EV_TYPE_REQ_WORD3:
		vf->req_addr |= (u64)data << 48;
		vf->req_type = VFDI_EV_TYPE_REQ_WORD0;
		vf->busy = true;
		queue_work(vfdi_workqueue, &vf->req);
		वापस;
	पूर्ण

error:
	अगर (net_ratelimit())
		netअगर_err(efx, hw, efx->net_dev,
			  "ERROR: Screaming VFDI request from %s\n",
			  vf->pci_name);
	/* Reset the request and sequence number */
	vf->req_type = VFDI_EV_TYPE_REQ_WORD0;
	vf->req_seqno = seq + 1;
पूर्ण

व्योम efx_siena_sriov_flr(काष्ठा efx_nic *efx, अचिन्हित vf_i)
अणु
	काष्ठा siena_nic_data *nic_data = efx->nic_data;
	काष्ठा siena_vf *vf;

	अगर (vf_i > efx->vf_init_count)
		वापस;
	vf = nic_data->vf + vf_i;
	netअगर_info(efx, hw, efx->net_dev,
		   "FLR on VF %s\n", vf->pci_name);

	vf->status_addr = 0;
	efx_vfdi_हटाओ_all_filters(vf);
	efx_vfdi_flush_clear(vf);

	vf->evq0_count = 0;
पूर्ण

पूर्णांक efx_siena_sriov_mac_address_changed(काष्ठा efx_nic *efx)
अणु
	काष्ठा siena_nic_data *nic_data = efx->nic_data;
	काष्ठा vfdi_status *vfdi_status = nic_data->vfdi_status.addr;

	अगर (!efx->vf_init_count)
		वापस 0;
	ether_addr_copy(vfdi_status->peers[0].mac_addr,
			efx->net_dev->dev_addr);
	queue_work(vfdi_workqueue, &nic_data->peer_work);

	वापस 0;
पूर्ण

व्योम efx_siena_sriov_tx_flush_करोne(काष्ठा efx_nic *efx, efx_qword_t *event)
अणु
	काष्ठा siena_vf *vf;
	अचिन्हित queue, qid;

	queue = EFX_QWORD_FIELD(*event,  FSF_AZ_DRIVER_EV_SUBDATA);
	अगर (map_vi_index(efx, queue, &vf, &qid))
		वापस;
	/* Ignore flush completions triggered by an FLR */
	अगर (!test_bit(qid, vf->txq_mask))
		वापस;

	__clear_bit(qid, vf->txq_mask);
	--vf->txq_count;

	अगर (efx_vfdi_flush_wake(vf))
		wake_up(&vf->flush_रुकोq);
पूर्ण

व्योम efx_siena_sriov_rx_flush_करोne(काष्ठा efx_nic *efx, efx_qword_t *event)
अणु
	काष्ठा siena_vf *vf;
	अचिन्हित ev_failed, queue, qid;

	queue = EFX_QWORD_FIELD(*event, FSF_AZ_DRIVER_EV_RX_DESCQ_ID);
	ev_failed = EFX_QWORD_FIELD(*event,
				    FSF_AZ_DRIVER_EV_RX_FLUSH_FAIL);
	अगर (map_vi_index(efx, queue, &vf, &qid))
		वापस;
	अगर (!test_bit(qid, vf->rxq_mask))
		वापस;

	अगर (ev_failed) अणु
		set_bit(qid, vf->rxq_retry_mask);
		atomic_inc(&vf->rxq_retry_count);
	पूर्ण अन्यथा अणु
		__clear_bit(qid, vf->rxq_mask);
		--vf->rxq_count;
	पूर्ण
	अगर (efx_vfdi_flush_wake(vf))
		wake_up(&vf->flush_रुकोq);
पूर्ण

/* Called from napi. Schedule the reset work item */
व्योम efx_siena_sriov_desc_fetch_err(काष्ठा efx_nic *efx, अचिन्हित dmaq)
अणु
	काष्ठा siena_vf *vf;
	अचिन्हित पूर्णांक rel;

	अगर (map_vi_index(efx, dmaq, &vf, &rel))
		वापस;

	अगर (net_ratelimit())
		netअगर_err(efx, hw, efx->net_dev,
			  "VF %d DMA Q %d reports descriptor fetch error.\n",
			  vf->index, rel);
	queue_work(vfdi_workqueue, &vf->reset_work);
पूर्ण

/* Reset all VFs */
व्योम efx_siena_sriov_reset(काष्ठा efx_nic *efx)
अणु
	काष्ठा siena_nic_data *nic_data = efx->nic_data;
	अचिन्हित पूर्णांक vf_i;
	काष्ठा efx_buffer buf;
	काष्ठा siena_vf *vf;

	ASSERT_RTNL();

	अगर (efx->vf_init_count == 0)
		वापस;

	efx_siena_sriov_usrev(efx, true);
	(व्योम)efx_siena_sriov_cmd(efx, true, शून्य, शून्य);

	अगर (efx_nic_alloc_buffer(efx, &buf, EFX_PAGE_SIZE, GFP_NOIO))
		वापस;

	क्रम (vf_i = 0; vf_i < efx->vf_init_count; ++vf_i) अणु
		vf = nic_data->vf + vf_i;
		efx_siena_sriov_reset_vf(vf, &buf);
	पूर्ण

	efx_nic_मुक्त_buffer(efx, &buf);
पूर्ण

पूर्णांक efx_init_sriov(व्योम)
अणु
	/* A single thपढ़ोed workqueue is sufficient. efx_siena_sriov_vfdi() and
	 * efx_siena_sriov_peer_work() spend almost all their समय sleeping क्रम
	 * MCDI to complete anyway
	 */
	vfdi_workqueue = create_singlethपढ़ो_workqueue("sfc_vfdi");
	अगर (!vfdi_workqueue)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम efx_fini_sriov(व्योम)
अणु
	destroy_workqueue(vfdi_workqueue);
पूर्ण

पूर्णांक efx_siena_sriov_set_vf_mac(काष्ठा efx_nic *efx, पूर्णांक vf_i, u8 *mac)
अणु
	काष्ठा siena_nic_data *nic_data = efx->nic_data;
	काष्ठा siena_vf *vf;

	अगर (vf_i >= efx->vf_init_count)
		वापस -EINVAL;
	vf = nic_data->vf + vf_i;

	mutex_lock(&vf->status_lock);
	ether_addr_copy(vf->addr.mac_addr, mac);
	__efx_siena_sriov_update_vf_addr(vf);
	mutex_unlock(&vf->status_lock);

	वापस 0;
पूर्ण

पूर्णांक efx_siena_sriov_set_vf_vlan(काष्ठा efx_nic *efx, पूर्णांक vf_i,
				u16 vlan, u8 qos)
अणु
	काष्ठा siena_nic_data *nic_data = efx->nic_data;
	काष्ठा siena_vf *vf;
	u16 tci;

	अगर (vf_i >= efx->vf_init_count)
		वापस -EINVAL;
	vf = nic_data->vf + vf_i;

	mutex_lock(&vf->status_lock);
	tci = (vlan & VLAN_VID_MASK) | ((qos & 0x7) << VLAN_PRIO_SHIFT);
	vf->addr.tci = htons(tci);
	__efx_siena_sriov_update_vf_addr(vf);
	mutex_unlock(&vf->status_lock);

	वापस 0;
पूर्ण

पूर्णांक efx_siena_sriov_set_vf_spoofchk(काष्ठा efx_nic *efx, पूर्णांक vf_i,
				    bool spoofchk)
अणु
	काष्ठा siena_nic_data *nic_data = efx->nic_data;
	काष्ठा siena_vf *vf;
	पूर्णांक rc;

	अगर (vf_i >= efx->vf_init_count)
		वापस -EINVAL;
	vf = nic_data->vf + vf_i;

	mutex_lock(&vf->txq_lock);
	अगर (vf->txq_count == 0) अणु
		vf->tx_filter_mode =
			spoofchk ? VF_TX_FILTER_ON : VF_TX_FILTER_OFF;
		rc = 0;
	पूर्ण अन्यथा अणु
		/* This cannot be changed जबतक TX queues are running */
		rc = -EBUSY;
	पूर्ण
	mutex_unlock(&vf->txq_lock);
	वापस rc;
पूर्ण

पूर्णांक efx_siena_sriov_get_vf_config(काष्ठा efx_nic *efx, पूर्णांक vf_i,
				  काष्ठा अगरla_vf_info *ivi)
अणु
	काष्ठा siena_nic_data *nic_data = efx->nic_data;
	काष्ठा siena_vf *vf;
	u16 tci;

	अगर (vf_i >= efx->vf_init_count)
		वापस -EINVAL;
	vf = nic_data->vf + vf_i;

	ivi->vf = vf_i;
	ether_addr_copy(ivi->mac, vf->addr.mac_addr);
	ivi->max_tx_rate = 0;
	ivi->min_tx_rate = 0;
	tci = ntohs(vf->addr.tci);
	ivi->vlan = tci & VLAN_VID_MASK;
	ivi->qos = (tci >> VLAN_PRIO_SHIFT) & 0x7;
	ivi->spoofchk = vf->tx_filter_mode == VF_TX_FILTER_ON;

	वापस 0;
पूर्ण

bool efx_siena_sriov_wanted(काष्ठा efx_nic *efx)
अणु
	वापस efx->vf_count != 0;
पूर्ण

पूर्णांक efx_siena_sriov_configure(काष्ठा efx_nic *efx, पूर्णांक num_vfs)
अणु
	वापस 0;
पूर्ण
