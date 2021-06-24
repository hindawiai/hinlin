<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2017 Chelsio Communications.  All rights reserved.
 */

#समावेश "t4_regs.h"
#समावेश "cxgb4.h"
#समावेश "cxgb4_cudbg.h"
#समावेश "cudbg_zlib.h"

अटल स्थिर काष्ठा cxgb4_collect_entity cxgb4_collect_mem_dump[] = अणु
	अणु CUDBG_EDC0, cudbg_collect_edc0_meminfo पूर्ण,
	अणु CUDBG_EDC1, cudbg_collect_edc1_meminfo पूर्ण,
	अणु CUDBG_MC0, cudbg_collect_mc0_meminfo पूर्ण,
	अणु CUDBG_MC1, cudbg_collect_mc1_meminfo पूर्ण,
	अणु CUDBG_HMA, cudbg_collect_hma_meminfo पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxgb4_collect_entity cxgb4_collect_hw_dump[] = अणु
	अणु CUDBG_MBOX_LOG, cudbg_collect_mbox_log पूर्ण,
	अणु CUDBG_QDESC, cudbg_collect_qdesc पूर्ण,
	अणु CUDBG_DEV_LOG, cudbg_collect_fw_devlog पूर्ण,
	अणु CUDBG_REG_DUMP, cudbg_collect_reg_dump पूर्ण,
	अणु CUDBG_CIM_LA, cudbg_collect_cim_la पूर्ण,
	अणु CUDBG_CIM_MA_LA, cudbg_collect_cim_ma_la पूर्ण,
	अणु CUDBG_CIM_QCFG, cudbg_collect_cim_qcfg पूर्ण,
	अणु CUDBG_CIM_IBQ_TP0, cudbg_collect_cim_ibq_tp0 पूर्ण,
	अणु CUDBG_CIM_IBQ_TP1, cudbg_collect_cim_ibq_tp1 पूर्ण,
	अणु CUDBG_CIM_IBQ_ULP, cudbg_collect_cim_ibq_ulp पूर्ण,
	अणु CUDBG_CIM_IBQ_SGE0, cudbg_collect_cim_ibq_sge0 पूर्ण,
	अणु CUDBG_CIM_IBQ_SGE1, cudbg_collect_cim_ibq_sge1 पूर्ण,
	अणु CUDBG_CIM_IBQ_NCSI, cudbg_collect_cim_ibq_ncsi पूर्ण,
	अणु CUDBG_CIM_OBQ_ULP0, cudbg_collect_cim_obq_ulp0 पूर्ण,
	अणु CUDBG_CIM_OBQ_ULP1, cudbg_collect_cim_obq_ulp1 पूर्ण,
	अणु CUDBG_CIM_OBQ_ULP2, cudbg_collect_cim_obq_ulp2 पूर्ण,
	अणु CUDBG_CIM_OBQ_ULP3, cudbg_collect_cim_obq_ulp3 पूर्ण,
	अणु CUDBG_CIM_OBQ_SGE, cudbg_collect_cim_obq_sge पूर्ण,
	अणु CUDBG_CIM_OBQ_NCSI, cudbg_collect_cim_obq_ncsi पूर्ण,
	अणु CUDBG_RSS, cudbg_collect_rss पूर्ण,
	अणु CUDBG_RSS_VF_CONF, cudbg_collect_rss_vf_config पूर्ण,
	अणु CUDBG_PATH_MTU, cudbg_collect_path_mtu पूर्ण,
	अणु CUDBG_PM_STATS, cudbg_collect_pm_stats पूर्ण,
	अणु CUDBG_HW_SCHED, cudbg_collect_hw_sched पूर्ण,
	अणु CUDBG_TP_INसूचीECT, cudbg_collect_tp_indirect पूर्ण,
	अणु CUDBG_SGE_INसूचीECT, cudbg_collect_sge_indirect पूर्ण,
	अणु CUDBG_ULPRX_LA, cudbg_collect_ulprx_la पूर्ण,
	अणु CUDBG_TP_LA, cudbg_collect_tp_la पूर्ण,
	अणु CUDBG_MEMINFO, cudbg_collect_meminfo पूर्ण,
	अणु CUDBG_CIM_PIF_LA, cudbg_collect_cim_pअगर_la पूर्ण,
	अणु CUDBG_CLK, cudbg_collect_clk_info पूर्ण,
	अणु CUDBG_CIM_OBQ_RXQ0, cudbg_collect_obq_sge_rx_q0 पूर्ण,
	अणु CUDBG_CIM_OBQ_RXQ1, cudbg_collect_obq_sge_rx_q1 पूर्ण,
	अणु CUDBG_PCIE_INसूचीECT, cudbg_collect_pcie_indirect पूर्ण,
	अणु CUDBG_PM_INसूचीECT, cudbg_collect_pm_indirect पूर्ण,
	अणु CUDBG_TID_INFO, cudbg_collect_tid पूर्ण,
	अणु CUDBG_PCIE_CONFIG, cudbg_collect_pcie_config पूर्ण,
	अणु CUDBG_DUMP_CONTEXT, cudbg_collect_dump_context पूर्ण,
	अणु CUDBG_MPS_TCAM, cudbg_collect_mps_tcam पूर्ण,
	अणु CUDBG_VPD_DATA, cudbg_collect_vpd_data पूर्ण,
	अणु CUDBG_LE_TCAM, cudbg_collect_le_tcam पूर्ण,
	अणु CUDBG_CCTRL, cudbg_collect_cctrl पूर्ण,
	अणु CUDBG_MA_INसूचीECT, cudbg_collect_ma_indirect पूर्ण,
	अणु CUDBG_ULPTX_LA, cudbg_collect_ulptx_la पूर्ण,
	अणु CUDBG_UP_CIM_INसूचीECT, cudbg_collect_up_cim_indirect पूर्ण,
	अणु CUDBG_PBT_TABLE, cudbg_collect_pbt_tables पूर्ण,
	अणु CUDBG_HMA_INसूचीECT, cudbg_collect_hma_indirect पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cxgb4_collect_entity cxgb4_collect_flash_dump[] = अणु
	अणु CUDBG_FLASH, cudbg_collect_flash पूर्ण,
पूर्ण;

u32 cxgb4_get_dump_length(काष्ठा adapter *adap, u32 flag)
अणु
	u32 i, entity;
	u32 len = 0;
	u32 wsize;

	अगर (flag & CXGB4_ETH_DUMP_HW) अणु
		क्रम (i = 0; i < ARRAY_SIZE(cxgb4_collect_hw_dump); i++) अणु
			entity = cxgb4_collect_hw_dump[i].entity;
			len += cudbg_get_entity_length(adap, entity);
		पूर्ण
	पूर्ण

	अगर (flag & CXGB4_ETH_DUMP_MEM) अणु
		क्रम (i = 0; i < ARRAY_SIZE(cxgb4_collect_mem_dump); i++) अणु
			entity = cxgb4_collect_mem_dump[i].entity;
			len += cudbg_get_entity_length(adap, entity);
		पूर्ण
	पूर्ण

	अगर (flag & CXGB4_ETH_DUMP_FLASH)
		len += adap->params.sf_size;

	/* If compression is enabled, a smaller destination buffer is enough */
	wsize = cudbg_get_workspace_size();
	अगर (wsize && len > CUDBG_DUMP_BUFF_SIZE)
		len = CUDBG_DUMP_BUFF_SIZE;

	वापस len;
पूर्ण

अटल व्योम cxgb4_cudbg_collect_entity(काष्ठा cudbg_init *pdbg_init,
				       काष्ठा cudbg_buffer *dbg_buff,
				       स्थिर काष्ठा cxgb4_collect_entity *e_arr,
				       u32 arr_size, व्योम *buf, u32 *tot_size)
अणु
	काष्ठा cudbg_error cudbg_err = अणु 0 पूर्ण;
	काष्ठा cudbg_entity_hdr *entity_hdr;
	u32 i, total_size = 0;
	पूर्णांक ret;

	क्रम (i = 0; i < arr_size; i++) अणु
		स्थिर काष्ठा cxgb4_collect_entity *e = &e_arr[i];

		entity_hdr = cudbg_get_entity_hdr(buf, e->entity);
		entity_hdr->entity_type = e->entity;
		entity_hdr->start_offset = dbg_buff->offset;
		स_रखो(&cudbg_err, 0, माप(काष्ठा cudbg_error));
		ret = e->collect_cb(pdbg_init, dbg_buff, &cudbg_err);
		अगर (ret) अणु
			entity_hdr->size = 0;
			dbg_buff->offset = entity_hdr->start_offset;
		पूर्ण अन्यथा अणु
			cudbg_align_debug_buffer(dbg_buff, entity_hdr);
		पूर्ण

		/* Log error and जारी with next entity */
		अगर (cudbg_err.sys_err)
			ret = CUDBG_SYSTEM_ERROR;

		entity_hdr->hdr_flags = ret;
		entity_hdr->sys_err = cudbg_err.sys_err;
		entity_hdr->sys_warn = cudbg_err.sys_warn;
		total_size += entity_hdr->size;
	पूर्ण

	*tot_size += total_size;
पूर्ण

अटल पूर्णांक cudbg_alloc_compress_buff(काष्ठा cudbg_init *pdbg_init)
अणु
	u32 workspace_size;

	workspace_size = cudbg_get_workspace_size();
	pdbg_init->compress_buff = vzalloc(CUDBG_COMPRESS_BUFF_SIZE +
					   workspace_size);
	अगर (!pdbg_init->compress_buff)
		वापस -ENOMEM;

	pdbg_init->compress_buff_size = CUDBG_COMPRESS_BUFF_SIZE;
	pdbg_init->workspace = (u8 *)pdbg_init->compress_buff +
			       CUDBG_COMPRESS_BUFF_SIZE - workspace_size;
	वापस 0;
पूर्ण

अटल व्योम cudbg_मुक्त_compress_buff(काष्ठा cudbg_init *pdbg_init)
अणु
	vमुक्त(pdbg_init->compress_buff);
पूर्ण

पूर्णांक cxgb4_cudbg_collect(काष्ठा adapter *adap, व्योम *buf, u32 *buf_size,
			u32 flag)
अणु
	काष्ठा cudbg_buffer dbg_buff = अणु 0 पूर्ण;
	u32 size, min_size, total_size = 0;
	काष्ठा cudbg_init cudbg_init;
	काष्ठा cudbg_hdr *cudbg_hdr;
	पूर्णांक rc;

	size = *buf_size;

	स_रखो(&cudbg_init, 0, माप(काष्ठा cudbg_init));
	cudbg_init.adap = adap;
	cudbg_init.outbuf = buf;
	cudbg_init.outbuf_size = size;

	dbg_buff.data = buf;
	dbg_buff.size = size;
	dbg_buff.offset = 0;

	cudbg_hdr = (काष्ठा cudbg_hdr *)buf;
	cudbg_hdr->signature = CUDBG_SIGNATURE;
	cudbg_hdr->hdr_len = माप(काष्ठा cudbg_hdr);
	cudbg_hdr->major_ver = CUDBG_MAJOR_VERSION;
	cudbg_hdr->minor_ver = CUDBG_MINOR_VERSION;
	cudbg_hdr->max_entities = CUDBG_MAX_ENTITY;
	cudbg_hdr->chip_ver = adap->params.chip;
	cudbg_hdr->dump_type = CUDBG_DUMP_TYPE_MINI;

	min_size = माप(काष्ठा cudbg_hdr) +
		   माप(काष्ठा cudbg_entity_hdr) *
		   cudbg_hdr->max_entities;
	अगर (size < min_size)
		वापस -ENOMEM;

	rc = cudbg_get_workspace_size();
	अगर (rc) अणु
		/* Zlib available.  So, use zlib deflate */
		cudbg_init.compress_type = CUDBG_COMPRESSION_ZLIB;
		rc = cudbg_alloc_compress_buff(&cudbg_init);
		अगर (rc) अणु
			/* Ignore error and जारी without compression. */
			dev_warn(adap->pdev_dev,
				 "Fail allocating compression buffer ret: %d.  Continuing without compression.\n",
				 rc);
			cudbg_init.compress_type = CUDBG_COMPRESSION_NONE;
			rc = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		cudbg_init.compress_type = CUDBG_COMPRESSION_NONE;
	पूर्ण

	cudbg_hdr->compress_type = cudbg_init.compress_type;
	dbg_buff.offset += min_size;
	total_size = dbg_buff.offset;

	अगर (flag & CXGB4_ETH_DUMP_HW)
		cxgb4_cudbg_collect_entity(&cudbg_init, &dbg_buff,
					   cxgb4_collect_hw_dump,
					   ARRAY_SIZE(cxgb4_collect_hw_dump),
					   buf,
					   &total_size);

	अगर (flag & CXGB4_ETH_DUMP_MEM)
		cxgb4_cudbg_collect_entity(&cudbg_init, &dbg_buff,
					   cxgb4_collect_mem_dump,
					   ARRAY_SIZE(cxgb4_collect_mem_dump),
					   buf,
					   &total_size);

	अगर (flag & CXGB4_ETH_DUMP_FLASH)
		cxgb4_cudbg_collect_entity(&cudbg_init, &dbg_buff,
					   cxgb4_collect_flash_dump,
					   ARRAY_SIZE(cxgb4_collect_flash_dump),
					   buf,
					   &total_size);

	cudbg_मुक्त_compress_buff(&cudbg_init);
	cudbg_hdr->data_len = total_size;
	अगर (cudbg_init.compress_type != CUDBG_COMPRESSION_NONE)
		*buf_size = size;
	अन्यथा
		*buf_size = total_size;
	वापस 0;
पूर्ण

व्योम cxgb4_init_ethtool_dump(काष्ठा adapter *adapter)
अणु
	adapter->eth_dump.flag = CXGB4_ETH_DUMP_NONE;
	adapter->eth_dump.version = adapter->params.fw_vers;
	adapter->eth_dump.len = 0;
पूर्ण

अटल पूर्णांक cxgb4_cudbg_vmcoredd_collect(काष्ठा vmcoredd_data *data, व्योम *buf)
अणु
	काष्ठा adapter *adap = container_of(data, काष्ठा adapter, vmcoredd);
	u32 len = data->size;

	वापस cxgb4_cudbg_collect(adap, buf, &len, CXGB4_ETH_DUMP_ALL);
पूर्ण

पूर्णांक cxgb4_cudbg_vmcore_add_dump(काष्ठा adapter *adap)
अणु
	काष्ठा vmcoredd_data *data = &adap->vmcoredd;
	u32 len;

	len = माप(काष्ठा cudbg_hdr) +
	      माप(काष्ठा cudbg_entity_hdr) * CUDBG_MAX_ENTITY;
	len += CUDBG_DUMP_BUFF_SIZE;

	data->size = len;
	snम_लिखो(data->dump_name, माप(data->dump_name), "%s_%s",
		 cxgb4_driver_name, adap->name);
	data->vmcoredd_callback = cxgb4_cudbg_vmcoredd_collect;

	वापस vmcore_add_device_dump(data);
पूर्ण
