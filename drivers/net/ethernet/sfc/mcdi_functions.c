<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2019 Solarflare Communications Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, incorporated herein by reference.
 */

#समावेश "net_driver.h"
#समावेश "efx.h"
#समावेश "nic.h"
#समावेश "mcdi_functions.h"
#समावेश "mcdi.h"
#समावेश "mcdi_pcol.h"

पूर्णांक efx_mcdi_मुक्त_vis(काष्ठा efx_nic *efx)
अणु
	MCDI_DECLARE_BUF_ERR(outbuf);
	माप_प्रकार outlen;
	पूर्णांक rc = efx_mcdi_rpc_quiet(efx, MC_CMD_FREE_VIS, शून्य, 0,
				    outbuf, माप(outbuf), &outlen);

	/* -EALREADY means nothing to मुक्त, so ignore */
	अगर (rc == -EALREADY)
		rc = 0;
	अगर (rc)
		efx_mcdi_display_error(efx, MC_CMD_FREE_VIS, 0, outbuf, outlen,
				       rc);
	वापस rc;
पूर्ण

पूर्णांक efx_mcdi_alloc_vis(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक min_vis,
		       अचिन्हित पूर्णांक max_vis, अचिन्हित पूर्णांक *vi_base,
		       अचिन्हित पूर्णांक *allocated_vis)
अणु
	MCDI_DECLARE_BUF(outbuf, MC_CMD_ALLOC_VIS_OUT_LEN);
	MCDI_DECLARE_BUF(inbuf, MC_CMD_ALLOC_VIS_IN_LEN);
	माप_प्रकार outlen;
	पूर्णांक rc;

	MCDI_SET_DWORD(inbuf, ALLOC_VIS_IN_MIN_VI_COUNT, min_vis);
	MCDI_SET_DWORD(inbuf, ALLOC_VIS_IN_MAX_VI_COUNT, max_vis);
	rc = efx_mcdi_rpc(efx, MC_CMD_ALLOC_VIS, inbuf, माप(inbuf),
			  outbuf, माप(outbuf), &outlen);
	अगर (rc != 0)
		वापस rc;

	अगर (outlen < MC_CMD_ALLOC_VIS_OUT_LEN)
		वापस -EIO;

	netअगर_dbg(efx, drv, efx->net_dev, "base VI is A0x%03x\n",
		  MCDI_DWORD(outbuf, ALLOC_VIS_OUT_VI_BASE));

	अगर (vi_base)
		*vi_base = MCDI_DWORD(outbuf, ALLOC_VIS_OUT_VI_BASE);
	अगर (allocated_vis)
		*allocated_vis = MCDI_DWORD(outbuf, ALLOC_VIS_OUT_VI_COUNT);
	वापस 0;
पूर्ण

पूर्णांक efx_mcdi_ev_probe(काष्ठा efx_channel *channel)
अणु
	वापस efx_nic_alloc_buffer(channel->efx, &channel->eventq.buf,
				    (channel->eventq_mask + 1) *
				    माप(efx_qword_t),
				    GFP_KERNEL);
पूर्ण

पूर्णांक efx_mcdi_ev_init(काष्ठा efx_channel *channel, bool v1_cut_thru, bool v2)
अणु
	MCDI_DECLARE_BUF(inbuf,
			 MC_CMD_INIT_EVQ_V2_IN_LEN(EFX_MAX_EVQ_SIZE * 8 /
						   EFX_BUF_SIZE));
	MCDI_DECLARE_BUF(outbuf, MC_CMD_INIT_EVQ_V2_OUT_LEN);
	माप_प्रकार entries = channel->eventq.buf.len / EFX_BUF_SIZE;
	काष्ठा efx_nic *efx = channel->efx;
	माप_प्रकार inlen, outlen;
	dma_addr_t dma_addr;
	पूर्णांक rc, i;

	/* Fill event queue with all ones (i.e. empty events) */
	स_रखो(channel->eventq.buf.addr, 0xff, channel->eventq.buf.len);

	MCDI_SET_DWORD(inbuf, INIT_EVQ_IN_SIZE, channel->eventq_mask + 1);
	MCDI_SET_DWORD(inbuf, INIT_EVQ_IN_INSTANCE, channel->channel);
	/* INIT_EVQ expects index in vector table, not असलolute */
	MCDI_SET_DWORD(inbuf, INIT_EVQ_IN_IRQ_NUM, channel->channel);
	MCDI_SET_DWORD(inbuf, INIT_EVQ_IN_TMR_MODE,
		       MC_CMD_INIT_EVQ_IN_TMR_MODE_DIS);
	MCDI_SET_DWORD(inbuf, INIT_EVQ_IN_TMR_LOAD, 0);
	MCDI_SET_DWORD(inbuf, INIT_EVQ_IN_TMR_RELOAD, 0);
	MCDI_SET_DWORD(inbuf, INIT_EVQ_IN_COUNT_MODE,
		       MC_CMD_INIT_EVQ_IN_COUNT_MODE_DIS);
	MCDI_SET_DWORD(inbuf, INIT_EVQ_IN_COUNT_THRSHLD, 0);

	अगर (v2) अणु
		/* Use the new generic approach to specअगरying event queue
		 * configuration, requesting lower latency or higher throughput.
		 * The options that actually get used appear in the output.
		 */
		MCDI_POPULATE_DWORD_2(inbuf, INIT_EVQ_V2_IN_FLAGS,
				      INIT_EVQ_V2_IN_FLAG_INTERRUPTING, 1,
				      INIT_EVQ_V2_IN_FLAG_TYPE,
				      MC_CMD_INIT_EVQ_V2_IN_FLAG_TYPE_AUTO);
	पूर्ण अन्यथा अणु
		MCDI_POPULATE_DWORD_4(inbuf, INIT_EVQ_IN_FLAGS,
				      INIT_EVQ_IN_FLAG_INTERRUPTING, 1,
				      INIT_EVQ_IN_FLAG_RX_MERGE, 1,
				      INIT_EVQ_IN_FLAG_TX_MERGE, 1,
				      INIT_EVQ_IN_FLAG_CUT_THRU, v1_cut_thru);
	पूर्ण

	dma_addr = channel->eventq.buf.dma_addr;
	क्रम (i = 0; i < entries; ++i) अणु
		MCDI_SET_ARRAY_QWORD(inbuf, INIT_EVQ_IN_DMA_ADDR, i, dma_addr);
		dma_addr += EFX_BUF_SIZE;
	पूर्ण

	inlen = MC_CMD_INIT_EVQ_IN_LEN(entries);

	rc = efx_mcdi_rpc(efx, MC_CMD_INIT_EVQ, inbuf, inlen,
			  outbuf, माप(outbuf), &outlen);

	अगर (outlen >= MC_CMD_INIT_EVQ_V2_OUT_LEN)
		netअगर_dbg(efx, drv, efx->net_dev,
			  "Channel %d using event queue flags %08x\n",
			  channel->channel,
			  MCDI_DWORD(outbuf, INIT_EVQ_V2_OUT_FLAGS));

	वापस rc;
पूर्ण

व्योम efx_mcdi_ev_हटाओ(काष्ठा efx_channel *channel)
अणु
	efx_nic_मुक्त_buffer(channel->efx, &channel->eventq.buf);
पूर्ण

व्योम efx_mcdi_ev_fini(काष्ठा efx_channel *channel)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_FINI_EVQ_IN_LEN);
	MCDI_DECLARE_BUF_ERR(outbuf);
	काष्ठा efx_nic *efx = channel->efx;
	माप_प्रकार outlen;
	पूर्णांक rc;

	MCDI_SET_DWORD(inbuf, FINI_EVQ_IN_INSTANCE, channel->channel);

	rc = efx_mcdi_rpc_quiet(efx, MC_CMD_FINI_EVQ, inbuf, माप(inbuf),
				outbuf, माप(outbuf), &outlen);

	अगर (rc && rc != -EALREADY)
		जाओ fail;

	वापस;

fail:
	efx_mcdi_display_error(efx, MC_CMD_FINI_EVQ, MC_CMD_FINI_EVQ_IN_LEN,
			       outbuf, outlen, rc);
पूर्ण

पूर्णांक efx_mcdi_tx_init(काष्ठा efx_tx_queue *tx_queue)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_INIT_TXQ_IN_LEN(EFX_MAX_DMAQ_SIZE * 8 /
						       EFX_BUF_SIZE));
	bool csum_offload = tx_queue->type & EFX_TXQ_TYPE_OUTER_CSUM;
	bool inner_csum = tx_queue->type & EFX_TXQ_TYPE_INNER_CSUM;
	माप_प्रकार entries = tx_queue->txd.buf.len / EFX_BUF_SIZE;
	काष्ठा efx_channel *channel = tx_queue->channel;
	काष्ठा efx_nic *efx = tx_queue->efx;
	dma_addr_t dma_addr;
	माप_प्रकार inlen;
	पूर्णांक rc, i;

	BUILD_BUG_ON(MC_CMD_INIT_TXQ_OUT_LEN != 0);

	MCDI_SET_DWORD(inbuf, INIT_TXQ_IN_SIZE, tx_queue->ptr_mask + 1);
	MCDI_SET_DWORD(inbuf, INIT_TXQ_IN_TARGET_EVQ, channel->channel);
	MCDI_SET_DWORD(inbuf, INIT_TXQ_IN_LABEL, tx_queue->label);
	MCDI_SET_DWORD(inbuf, INIT_TXQ_IN_INSTANCE, tx_queue->queue);
	MCDI_SET_DWORD(inbuf, INIT_TXQ_IN_OWNER_ID, 0);
	MCDI_SET_DWORD(inbuf, INIT_TXQ_IN_PORT_ID, efx->vport_id);

	dma_addr = tx_queue->txd.buf.dma_addr;

	netअगर_dbg(efx, hw, efx->net_dev, "pushing TXQ %d. %zu entries (%llx)\n",
		  tx_queue->queue, entries, (u64)dma_addr);

	क्रम (i = 0; i < entries; ++i) अणु
		MCDI_SET_ARRAY_QWORD(inbuf, INIT_TXQ_IN_DMA_ADDR, i, dma_addr);
		dma_addr += EFX_BUF_SIZE;
	पूर्ण

	inlen = MC_CMD_INIT_TXQ_IN_LEN(entries);

	करो अणु
		bool tso_v2 = tx_queue->tso_version == 2;

		/* TSOv2 implies IP header checksum offload क्रम TSO frames,
		 * so we can safely disable IP header checksum offload क्रम
		 * everything अन्यथा.  If we करोn't have TSOv2, then we have to
		 * enable IP header checksum offload, which is strictly
		 * incorrect but better than अवरोधing TSO.
		 */
		MCDI_POPULATE_DWORD_6(inbuf, INIT_TXQ_IN_FLAGS,
				/* This flag was हटाओd from mcdi_pcol.h क्रम
				 * the non-_EXT version of INIT_TXQ.  However,
				 * firmware still honours it.
				 */
				INIT_TXQ_EXT_IN_FLAG_TSOV2_EN, tso_v2,
				INIT_TXQ_IN_FLAG_IP_CSUM_DIS, !(csum_offload && tso_v2),
				INIT_TXQ_IN_FLAG_TCP_CSUM_DIS, !csum_offload,
				INIT_TXQ_EXT_IN_FLAG_TIMESTAMP, tx_queue->बारtamping,
				INIT_TXQ_IN_FLAG_INNER_IP_CSUM_EN, inner_csum && !tso_v2,
				INIT_TXQ_IN_FLAG_INNER_TCP_CSUM_EN, inner_csum);

		rc = efx_mcdi_rpc_quiet(efx, MC_CMD_INIT_TXQ, inbuf, inlen,
					शून्य, 0, शून्य);
		अगर (rc == -ENOSPC && tso_v2) अणु
			/* Retry without TSOv2 अगर we're लघु on contexts. */
			tx_queue->tso_version = 0;
			netअगर_warn(efx, probe, efx->net_dev,
				   "TSOv2 context not available to segment in "
				   "hardware. TCP performance may be reduced.\n"
				   );
		पूर्ण अन्यथा अगर (rc) अणु
			efx_mcdi_display_error(efx, MC_CMD_INIT_TXQ,
					       MC_CMD_INIT_TXQ_EXT_IN_LEN,
					       शून्य, 0, rc);
			जाओ fail;
		पूर्ण
	पूर्ण जबतक (rc);

	वापस 0;

fail:
	वापस rc;
पूर्ण

व्योम efx_mcdi_tx_हटाओ(काष्ठा efx_tx_queue *tx_queue)
अणु
	efx_nic_मुक्त_buffer(tx_queue->efx, &tx_queue->txd.buf);
पूर्ण

व्योम efx_mcdi_tx_fini(काष्ठा efx_tx_queue *tx_queue)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_FINI_TXQ_IN_LEN);
	MCDI_DECLARE_BUF_ERR(outbuf);
	काष्ठा efx_nic *efx = tx_queue->efx;
	माप_प्रकार outlen;
	पूर्णांक rc;

	MCDI_SET_DWORD(inbuf, FINI_TXQ_IN_INSTANCE,
		       tx_queue->queue);

	rc = efx_mcdi_rpc_quiet(efx, MC_CMD_FINI_TXQ, inbuf, माप(inbuf),
				outbuf, माप(outbuf), &outlen);

	अगर (rc && rc != -EALREADY)
		जाओ fail;

	वापस;

fail:
	efx_mcdi_display_error(efx, MC_CMD_FINI_TXQ, MC_CMD_FINI_TXQ_IN_LEN,
			       outbuf, outlen, rc);
पूर्ण

पूर्णांक efx_mcdi_rx_probe(काष्ठा efx_rx_queue *rx_queue)
अणु
	वापस efx_nic_alloc_buffer(rx_queue->efx, &rx_queue->rxd.buf,
				    (rx_queue->ptr_mask + 1) *
				    माप(efx_qword_t),
				    GFP_KERNEL);
पूर्ण

व्योम efx_mcdi_rx_init(काष्ठा efx_rx_queue *rx_queue)
अणु
	काष्ठा efx_channel *channel = efx_rx_queue_channel(rx_queue);
	माप_प्रकार entries = rx_queue->rxd.buf.len / EFX_BUF_SIZE;
	MCDI_DECLARE_BUF(inbuf, MC_CMD_INIT_RXQ_V4_IN_LEN);
	काष्ठा efx_nic *efx = rx_queue->efx;
	अचिन्हित पूर्णांक buffer_size;
	dma_addr_t dma_addr;
	पूर्णांक rc;
	पूर्णांक i;
	BUILD_BUG_ON(MC_CMD_INIT_RXQ_OUT_LEN != 0);

	rx_queue->scatter_n = 0;
	rx_queue->scatter_len = 0;
	अगर (efx->type->revision == EFX_REV_EF100)
		buffer_size = efx->rx_page_buf_step;
	अन्यथा
		buffer_size = 0;

	MCDI_SET_DWORD(inbuf, INIT_RXQ_IN_SIZE, rx_queue->ptr_mask + 1);
	MCDI_SET_DWORD(inbuf, INIT_RXQ_IN_TARGET_EVQ, channel->channel);
	MCDI_SET_DWORD(inbuf, INIT_RXQ_IN_LABEL, efx_rx_queue_index(rx_queue));
	MCDI_SET_DWORD(inbuf, INIT_RXQ_IN_INSTANCE,
		       efx_rx_queue_index(rx_queue));
	MCDI_POPULATE_DWORD_2(inbuf, INIT_RXQ_IN_FLAGS,
			      INIT_RXQ_IN_FLAG_PREFIX, 1,
			      INIT_RXQ_IN_FLAG_TIMESTAMP, 1);
	MCDI_SET_DWORD(inbuf, INIT_RXQ_IN_OWNER_ID, 0);
	MCDI_SET_DWORD(inbuf, INIT_RXQ_IN_PORT_ID, efx->vport_id);
	MCDI_SET_DWORD(inbuf, INIT_RXQ_V4_IN_BUFFER_SIZE_BYTES, buffer_size);

	dma_addr = rx_queue->rxd.buf.dma_addr;

	netअगर_dbg(efx, hw, efx->net_dev, "pushing RXQ %d. %zu entries (%llx)\n",
		  efx_rx_queue_index(rx_queue), entries, (u64)dma_addr);

	क्रम (i = 0; i < entries; ++i) अणु
		MCDI_SET_ARRAY_QWORD(inbuf, INIT_RXQ_IN_DMA_ADDR, i, dma_addr);
		dma_addr += EFX_BUF_SIZE;
	पूर्ण

	rc = efx_mcdi_rpc(efx, MC_CMD_INIT_RXQ, inbuf, माप(inbuf),
			  शून्य, 0, शून्य);
	अगर (rc)
		netdev_WARN(efx->net_dev, "failed to initialise RXQ %d\n",
			    efx_rx_queue_index(rx_queue));
पूर्ण

व्योम efx_mcdi_rx_हटाओ(काष्ठा efx_rx_queue *rx_queue)
अणु
	efx_nic_मुक्त_buffer(rx_queue->efx, &rx_queue->rxd.buf);
पूर्ण

व्योम efx_mcdi_rx_fini(काष्ठा efx_rx_queue *rx_queue)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_FINI_RXQ_IN_LEN);
	MCDI_DECLARE_BUF_ERR(outbuf);
	काष्ठा efx_nic *efx = rx_queue->efx;
	माप_प्रकार outlen;
	पूर्णांक rc;

	MCDI_SET_DWORD(inbuf, FINI_RXQ_IN_INSTANCE,
		       efx_rx_queue_index(rx_queue));

	rc = efx_mcdi_rpc_quiet(efx, MC_CMD_FINI_RXQ, inbuf, माप(inbuf),
				outbuf, माप(outbuf), &outlen);

	अगर (rc && rc != -EALREADY)
		जाओ fail;

	वापस;

fail:
	efx_mcdi_display_error(efx, MC_CMD_FINI_RXQ, MC_CMD_FINI_RXQ_IN_LEN,
			       outbuf, outlen, rc);
पूर्ण

पूर्णांक efx_fini_dmaq(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_tx_queue *tx_queue;
	काष्ठा efx_rx_queue *rx_queue;
	काष्ठा efx_channel *channel;
	पूर्णांक pending;

	/* If the MC has just rebooted, the TX/RX queues will have alपढ़ोy been
	 * torn करोwn, but efx->active_queues needs to be set to zero.
	 */
	अगर (efx->must_पुनः_स्मृति_vis) अणु
		atomic_set(&efx->active_queues, 0);
		वापस 0;
	पूर्ण

	/* Do not attempt to ग_लिखो to the NIC during EEH recovery */
	अगर (efx->state != STATE_RECOVERY) अणु
		efx_क्रम_each_channel(channel, efx) अणु
			efx_क्रम_each_channel_rx_queue(rx_queue, channel)
				efx_mcdi_rx_fini(rx_queue);
			efx_क्रम_each_channel_tx_queue(tx_queue, channel)
				efx_mcdi_tx_fini(tx_queue);
		पूर्ण

		रुको_event_समयout(efx->flush_wq,
				   atomic_पढ़ो(&efx->active_queues) == 0,
				   msecs_to_jअगरfies(EFX_MAX_FLUSH_TIME));
		pending = atomic_पढ़ो(&efx->active_queues);
		अगर (pending) अणु
			netअगर_err(efx, hw, efx->net_dev, "failed to flush %d queues\n",
				  pending);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक efx_mcdi_winकरोw_mode_to_stride(काष्ठा efx_nic *efx, u8 vi_winकरोw_mode)
अणु
	चयन (vi_winकरोw_mode) अणु
	हाल MC_CMD_GET_CAPABILITIES_V3_OUT_VI_WINDOW_MODE_8K:
		efx->vi_stride = 8192;
		अवरोध;
	हाल MC_CMD_GET_CAPABILITIES_V3_OUT_VI_WINDOW_MODE_16K:
		efx->vi_stride = 16384;
		अवरोध;
	हाल MC_CMD_GET_CAPABILITIES_V3_OUT_VI_WINDOW_MODE_64K:
		efx->vi_stride = 65536;
		अवरोध;
	शेष:
		netअगर_err(efx, probe, efx->net_dev,
			  "Unrecognised VI window mode %d\n",
			  vi_winकरोw_mode);
		वापस -EIO;
	पूर्ण
	netअगर_dbg(efx, probe, efx->net_dev, "vi_stride = %u\n",
		  efx->vi_stride);
	वापस 0;
पूर्ण

पूर्णांक efx_get_pf_index(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक *pf_index)
अणु
	MCDI_DECLARE_BUF(outbuf, MC_CMD_GET_FUNCTION_INFO_OUT_LEN);
	माप_प्रकार outlen;
	पूर्णांक rc;

	rc = efx_mcdi_rpc(efx, MC_CMD_GET_FUNCTION_INFO, शून्य, 0, outbuf,
			  माप(outbuf), &outlen);
	अगर (rc)
		वापस rc;
	अगर (outlen < माप(outbuf))
		वापस -EIO;

	*pf_index = MCDI_DWORD(outbuf, GET_FUNCTION_INFO_OUT_PF);
	वापस 0;
पूर्ण
