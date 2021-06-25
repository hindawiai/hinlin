<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2018-2021 Intel Corporation
 */
#समावेश <linux/firmware.h>
#समावेश "iwl-drv.h"
#समावेश "iwl-trans.h"
#समावेश "iwl-dbg-tlv.h"
#समावेश "fw/dbg.h"
#समावेश "fw/runtime.h"

/**
 * क्रमागत iwl_dbg_tlv_type - debug TLV types
 * @IWL_DBG_TLV_TYPE_DEBUG_INFO: debug info TLV
 * @IWL_DBG_TLV_TYPE_BUF_ALLOC: buffer allocation TLV
 * @IWL_DBG_TLV_TYPE_HCMD: host command TLV
 * @IWL_DBG_TLV_TYPE_REGION: region TLV
 * @IWL_DBG_TLV_TYPE_TRIGGER: trigger TLV
 * @IWL_DBG_TLV_TYPE_NUM: number of debug TLVs
 */
क्रमागत iwl_dbg_tlv_type अणु
	IWL_DBG_TLV_TYPE_DEBUG_INFO =
		IWL_UCODE_TLV_TYPE_DEBUG_INFO - IWL_UCODE_TLV_DEBUG_BASE,
	IWL_DBG_TLV_TYPE_BUF_ALLOC,
	IWL_DBG_TLV_TYPE_HCMD,
	IWL_DBG_TLV_TYPE_REGION,
	IWL_DBG_TLV_TYPE_TRIGGER,
	IWL_DBG_TLV_TYPE_NUM,
पूर्ण;

/**
 * काष्ठा iwl_dbg_tlv_ver_data -  debug TLV version काष्ठा
 * @min_ver: min version supported
 * @max_ver: max version supported
 */
काष्ठा iwl_dbg_tlv_ver_data अणु
	पूर्णांक min_ver;
	पूर्णांक max_ver;
पूर्ण;

/**
 * काष्ठा iwl_dbg_tlv_समयr_node - समयr node काष्ठा
 * @list: list of &काष्ठा iwl_dbg_tlv_समयr_node
 * @समयr: समयr
 * @fwrt: &काष्ठा iwl_fw_runसमय
 * @tlv: TLV attach to the समयr node
 */
काष्ठा iwl_dbg_tlv_समयr_node अणु
	काष्ठा list_head list;
	काष्ठा समयr_list समयr;
	काष्ठा iwl_fw_runसमय *fwrt;
	काष्ठा iwl_ucode_tlv *tlv;
पूर्ण;

अटल स्थिर काष्ठा iwl_dbg_tlv_ver_data
dbg_ver_table[IWL_DBG_TLV_TYPE_NUM] = अणु
	[IWL_DBG_TLV_TYPE_DEBUG_INFO]	= अणु.min_ver = 1, .max_ver = 1,पूर्ण,
	[IWL_DBG_TLV_TYPE_BUF_ALLOC]	= अणु.min_ver = 1, .max_ver = 1,पूर्ण,
	[IWL_DBG_TLV_TYPE_HCMD]		= अणु.min_ver = 1, .max_ver = 1,पूर्ण,
	[IWL_DBG_TLV_TYPE_REGION]	= अणु.min_ver = 1, .max_ver = 1,पूर्ण,
	[IWL_DBG_TLV_TYPE_TRIGGER]	= अणु.min_ver = 1, .max_ver = 1,पूर्ण,
पूर्ण;

अटल पूर्णांक iwl_dbg_tlv_add(स्थिर काष्ठा iwl_ucode_tlv *tlv,
			   काष्ठा list_head *list)
अणु
	u32 len = le32_to_cpu(tlv->length);
	काष्ठा iwl_dbg_tlv_node *node;

	node = kzalloc(माप(*node) + len, GFP_KERNEL);
	अगर (!node)
		वापस -ENOMEM;

	स_नकल(&node->tlv, tlv, माप(node->tlv) + len);
	list_add_tail(&node->list, list);

	वापस 0;
पूर्ण

अटल bool iwl_dbg_tlv_ver_support(स्थिर काष्ठा iwl_ucode_tlv *tlv)
अणु
	स्थिर काष्ठा iwl_fw_ini_header *hdr = (स्थिर व्योम *)&tlv->data[0];
	u32 type = le32_to_cpu(tlv->type);
	u32 tlv_idx = type - IWL_UCODE_TLV_DEBUG_BASE;
	u32 ver = le32_to_cpu(hdr->version);

	अगर (ver < dbg_ver_table[tlv_idx].min_ver ||
	    ver > dbg_ver_table[tlv_idx].max_ver)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक iwl_dbg_tlv_alloc_debug_info(काष्ठा iwl_trans *trans,
					स्थिर काष्ठा iwl_ucode_tlv *tlv)
अणु
	स्थिर काष्ठा iwl_fw_ini_debug_info_tlv *debug_info = (स्थिर व्योम *)tlv->data;

	अगर (le32_to_cpu(tlv->length) != माप(*debug_info))
		वापस -EINVAL;

	IWL_DEBUG_FW(trans, "WRT: Loading debug cfg: %s\n",
		     debug_info->debug_cfg_name);

	वापस iwl_dbg_tlv_add(tlv, &trans->dbg.debug_info_tlv_list);
पूर्ण

अटल पूर्णांक iwl_dbg_tlv_alloc_buf_alloc(काष्ठा iwl_trans *trans,
				       स्थिर काष्ठा iwl_ucode_tlv *tlv)
अणु
	स्थिर काष्ठा iwl_fw_ini_allocation_tlv *alloc = (स्थिर व्योम *)tlv->data;
	u32 buf_location;
	u32 alloc_id;

	अगर (le32_to_cpu(tlv->length) != माप(*alloc))
		वापस -EINVAL;

	buf_location = le32_to_cpu(alloc->buf_location);
	alloc_id = le32_to_cpu(alloc->alloc_id);

	अगर (buf_location == IWL_FW_INI_LOCATION_INVALID ||
	    buf_location >= IWL_FW_INI_LOCATION_NUM)
		जाओ err;

	अगर (alloc_id == IWL_FW_INI_ALLOCATION_INVALID ||
	    alloc_id >= IWL_FW_INI_ALLOCATION_NUM)
		जाओ err;

	अगर (buf_location == IWL_FW_INI_LOCATION_NPK_PATH &&
	    alloc_id != IWL_FW_INI_ALLOCATION_ID_DBGC1)
		जाओ err;

	अगर (buf_location == IWL_FW_INI_LOCATION_SRAM_PATH &&
	    alloc_id != IWL_FW_INI_ALLOCATION_ID_DBGC1 &&
	    alloc_id != IWL_FW_INI_ALLOCATION_ID_INTERNAL)
		जाओ err;

	trans->dbg.fw_mon_cfg[alloc_id] = *alloc;

	वापस 0;
err:
	IWL_ERR(trans,
		"WRT: Invalid allocation id %u and/or location id %u for allocation TLV\n",
		alloc_id, buf_location);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक iwl_dbg_tlv_alloc_hcmd(काष्ठा iwl_trans *trans,
				  स्थिर काष्ठा iwl_ucode_tlv *tlv)
अणु
	स्थिर काष्ठा iwl_fw_ini_hcmd_tlv *hcmd = (स्थिर व्योम *)tlv->data;
	u32 tp = le32_to_cpu(hcmd->समय_poपूर्णांक);

	अगर (le32_to_cpu(tlv->length) <= माप(*hcmd))
		वापस -EINVAL;

	/* Host commands can not be sent in early समय poपूर्णांक since the FW
	 * is not पढ़ोy
	 */
	अगर (tp == IWL_FW_INI_TIME_POINT_INVALID ||
	    tp >= IWL_FW_INI_TIME_POINT_NUM ||
	    tp == IWL_FW_INI_TIME_POINT_EARLY) अणु
		IWL_ERR(trans,
			"WRT: Invalid time point %u for host command TLV\n",
			tp);
		वापस -EINVAL;
	पूर्ण

	वापस iwl_dbg_tlv_add(tlv, &trans->dbg.समय_poपूर्णांक[tp].hcmd_list);
पूर्ण

अटल पूर्णांक iwl_dbg_tlv_alloc_region(काष्ठा iwl_trans *trans,
				    स्थिर काष्ठा iwl_ucode_tlv *tlv)
अणु
	स्थिर काष्ठा iwl_fw_ini_region_tlv *reg = (स्थिर व्योम *)tlv->data;
	काष्ठा iwl_ucode_tlv **active_reg;
	u32 id = le32_to_cpu(reg->id);
	u32 type = le32_to_cpu(reg->type);
	u32 tlv_len = माप(*tlv) + le32_to_cpu(tlv->length);

	अगर (le32_to_cpu(tlv->length) < माप(*reg))
		वापस -EINVAL;

	अगर (id >= IWL_FW_INI_MAX_REGION_ID) अणु
		IWL_ERR(trans, "WRT: Invalid region id %u\n", id);
		वापस -EINVAL;
	पूर्ण

	अगर (type <= IWL_FW_INI_REGION_INVALID ||
	    type >= IWL_FW_INI_REGION_NUM) अणु
		IWL_ERR(trans, "WRT: Invalid region type %u\n", type);
		वापस -EINVAL;
	पूर्ण

	अगर (type == IWL_FW_INI_REGION_PCI_IOSF_CONFIG &&
	    !trans->ops->पढ़ो_config32) अणु
		IWL_ERR(trans, "WRT: Unsupported region type %u\n", type);
		वापस -EOPNOTSUPP;
	पूर्ण

	active_reg = &trans->dbg.active_regions[id];
	अगर (*active_reg) अणु
		IWL_WARN(trans, "WRT: Overriding region id %u\n", id);

		kमुक्त(*active_reg);
	पूर्ण

	*active_reg = kmemdup(tlv, tlv_len, GFP_KERNEL);
	अगर (!*active_reg)
		वापस -ENOMEM;

	IWL_DEBUG_FW(trans, "WRT: Enabling region id %u type %u\n", id, type);

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_dbg_tlv_alloc_trigger(काष्ठा iwl_trans *trans,
				     स्थिर काष्ठा iwl_ucode_tlv *tlv)
अणु
	स्थिर काष्ठा iwl_fw_ini_trigger_tlv *trig = (स्थिर व्योम *)tlv->data;
	काष्ठा iwl_fw_ini_trigger_tlv *dup_trig;
	u32 tp = le32_to_cpu(trig->समय_poपूर्णांक);
	काष्ठा iwl_ucode_tlv *dup = शून्य;
	पूर्णांक ret;

	अगर (le32_to_cpu(tlv->length) < माप(*trig))
		वापस -EINVAL;

	अगर (tp <= IWL_FW_INI_TIME_POINT_INVALID ||
	    tp >= IWL_FW_INI_TIME_POINT_NUM) अणु
		IWL_ERR(trans,
			"WRT: Invalid time point %u for trigger TLV\n",
			tp);
		वापस -EINVAL;
	पूर्ण

	अगर (!le32_to_cpu(trig->occurrences)) अणु
		dup = kmemdup(tlv, माप(*tlv) + le32_to_cpu(tlv->length),
				GFP_KERNEL);
		अगर (!dup)
			वापस -ENOMEM;
		dup_trig = (व्योम *)dup->data;
		dup_trig->occurrences = cpu_to_le32(-1);
		tlv = dup;
	पूर्ण

	ret = iwl_dbg_tlv_add(tlv, &trans->dbg.समय_poपूर्णांक[tp].trig_list);
	kमुक्त(dup);

	वापस ret;
पूर्ण

अटल पूर्णांक (*dbg_tlv_alloc[])(काष्ठा iwl_trans *trans,
			      स्थिर काष्ठा iwl_ucode_tlv *tlv) = अणु
	[IWL_DBG_TLV_TYPE_DEBUG_INFO]	= iwl_dbg_tlv_alloc_debug_info,
	[IWL_DBG_TLV_TYPE_BUF_ALLOC]	= iwl_dbg_tlv_alloc_buf_alloc,
	[IWL_DBG_TLV_TYPE_HCMD]		= iwl_dbg_tlv_alloc_hcmd,
	[IWL_DBG_TLV_TYPE_REGION]	= iwl_dbg_tlv_alloc_region,
	[IWL_DBG_TLV_TYPE_TRIGGER]	= iwl_dbg_tlv_alloc_trigger,
पूर्ण;

व्योम iwl_dbg_tlv_alloc(काष्ठा iwl_trans *trans, स्थिर काष्ठा iwl_ucode_tlv *tlv,
		       bool ext)
अणु
	स्थिर काष्ठा iwl_fw_ini_header *hdr = (स्थिर व्योम *)&tlv->data[0];
	u32 type = le32_to_cpu(tlv->type);
	u32 tlv_idx = type - IWL_UCODE_TLV_DEBUG_BASE;
	u32 करोमुख्य = le32_to_cpu(hdr->करोमुख्य);
	क्रमागत iwl_ini_cfg_state *cfg_state = ext ?
		&trans->dbg.बाह्यal_ini_cfg : &trans->dbg.पूर्णांकernal_ini_cfg;
	पूर्णांक ret;

	अगर (करोमुख्य != IWL_FW_INI_DOMAIN_ALWAYS_ON &&
	    !(करोमुख्य & trans->dbg.करोमुख्यs_biपंचांगap)) अणु
		IWL_DEBUG_FW(trans,
			     "WRT: Skipping TLV with disabled domain 0x%0x (0x%0x)\n",
			     करोमुख्य, trans->dbg.करोमुख्यs_biपंचांगap);
		वापस;
	पूर्ण

	अगर (tlv_idx >= ARRAY_SIZE(dbg_tlv_alloc) || !dbg_tlv_alloc[tlv_idx]) अणु
		IWL_ERR(trans, "WRT: Unsupported TLV type 0x%x\n", type);
		जाओ out_err;
	पूर्ण

	अगर (!iwl_dbg_tlv_ver_support(tlv)) अणु
		IWL_ERR(trans, "WRT: Unsupported TLV 0x%x version %u\n", type,
			le32_to_cpu(hdr->version));
		जाओ out_err;
	पूर्ण

	ret = dbg_tlv_alloc[tlv_idx](trans, tlv);
	अगर (ret) अणु
		IWL_ERR(trans,
			"WRT: Failed to allocate TLV 0x%x, ret %d, (ext=%d)\n",
			type, ret, ext);
		जाओ out_err;
	पूर्ण

	अगर (*cfg_state == IWL_INI_CFG_STATE_NOT_LOADED)
		*cfg_state = IWL_INI_CFG_STATE_LOADED;

	वापस;

out_err:
	*cfg_state = IWL_INI_CFG_STATE_CORRUPTED;
पूर्ण

व्योम iwl_dbg_tlv_del_समयrs(काष्ठा iwl_trans *trans)
अणु
	काष्ठा list_head *समयr_list = &trans->dbg.periodic_trig_list;
	काष्ठा iwl_dbg_tlv_समयr_node *node, *पंचांगp;

	list_क्रम_each_entry_safe(node, पंचांगp, समयr_list, list) अणु
		del_समयr(&node->समयr);
		list_del(&node->list);
		kमुक्त(node);
	पूर्ण
पूर्ण
IWL_EXPORT_SYMBOL(iwl_dbg_tlv_del_समयrs);

अटल व्योम iwl_dbg_tlv_fragments_मुक्त(काष्ठा iwl_trans *trans,
				       क्रमागत iwl_fw_ini_allocation_id alloc_id)
अणु
	काष्ठा iwl_fw_mon *fw_mon;
	पूर्णांक i;

	अगर (alloc_id <= IWL_FW_INI_ALLOCATION_INVALID ||
	    alloc_id >= IWL_FW_INI_ALLOCATION_NUM)
		वापस;

	fw_mon = &trans->dbg.fw_mon_ini[alloc_id];

	क्रम (i = 0; i < fw_mon->num_frags; i++) अणु
		काष्ठा iwl_dram_data *frag = &fw_mon->frags[i];

		dma_मुक्त_coherent(trans->dev, frag->size, frag->block,
				  frag->physical);

		frag->physical = 0;
		frag->block = शून्य;
		frag->size = 0;
	पूर्ण

	kमुक्त(fw_mon->frags);
	fw_mon->frags = शून्य;
	fw_mon->num_frags = 0;
पूर्ण

व्योम iwl_dbg_tlv_मुक्त(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_dbg_tlv_node *tlv_node, *tlv_node_पंचांगp;
	पूर्णांक i;

	iwl_dbg_tlv_del_समयrs(trans);

	क्रम (i = 0; i < ARRAY_SIZE(trans->dbg.active_regions); i++) अणु
		काष्ठा iwl_ucode_tlv **active_reg =
			&trans->dbg.active_regions[i];

		kमुक्त(*active_reg);
		*active_reg = शून्य;
	पूर्ण

	list_क्रम_each_entry_safe(tlv_node, tlv_node_पंचांगp,
				 &trans->dbg.debug_info_tlv_list, list) अणु
		list_del(&tlv_node->list);
		kमुक्त(tlv_node);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(trans->dbg.समय_poपूर्णांक); i++) अणु
		काष्ठा iwl_dbg_tlv_समय_poपूर्णांक_data *tp =
			&trans->dbg.समय_poपूर्णांक[i];

		list_क्रम_each_entry_safe(tlv_node, tlv_node_पंचांगp, &tp->trig_list,
					 list) अणु
			list_del(&tlv_node->list);
			kमुक्त(tlv_node);
		पूर्ण

		list_क्रम_each_entry_safe(tlv_node, tlv_node_पंचांगp, &tp->hcmd_list,
					 list) अणु
			list_del(&tlv_node->list);
			kमुक्त(tlv_node);
		पूर्ण

		list_क्रम_each_entry_safe(tlv_node, tlv_node_पंचांगp,
					 &tp->active_trig_list, list) अणु
			list_del(&tlv_node->list);
			kमुक्त(tlv_node);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(trans->dbg.fw_mon_ini); i++)
		iwl_dbg_tlv_fragments_मुक्त(trans, i);
पूर्ण

अटल पूर्णांक iwl_dbg_tlv_parse_bin(काष्ठा iwl_trans *trans, स्थिर u8 *data,
				 माप_प्रकार len)
अणु
	स्थिर काष्ठा iwl_ucode_tlv *tlv;
	u32 tlv_len;

	जबतक (len >= माप(*tlv)) अणु
		len -= माप(*tlv);
		tlv = (व्योम *)data;

		tlv_len = le32_to_cpu(tlv->length);

		अगर (len < tlv_len) अणु
			IWL_ERR(trans, "invalid TLV len: %zd/%u\n",
				len, tlv_len);
			वापस -EINVAL;
		पूर्ण
		len -= ALIGN(tlv_len, 4);
		data += माप(*tlv) + ALIGN(tlv_len, 4);

		iwl_dbg_tlv_alloc(trans, tlv, true);
	पूर्ण

	वापस 0;
पूर्ण

व्योम iwl_dbg_tlv_load_bin(काष्ठा device *dev, काष्ठा iwl_trans *trans)
अणु
	स्थिर काष्ठा firmware *fw;
	पूर्णांक res;

	अगर (!iwlwअगरi_mod_params.enable_ini ||
	    trans->trans_cfg->device_family <= IWL_DEVICE_FAMILY_9000)
		वापस;

	res = firmware_request_nowarn(&fw, "iwl-debug-yoyo.bin", dev);
	अगर (res)
		वापस;

	iwl_dbg_tlv_parse_bin(trans, fw->data, fw->size);

	release_firmware(fw);
पूर्ण

व्योम iwl_dbg_tlv_init(काष्ठा iwl_trans *trans)
अणु
	पूर्णांक i;

	INIT_LIST_HEAD(&trans->dbg.debug_info_tlv_list);
	INIT_LIST_HEAD(&trans->dbg.periodic_trig_list);

	क्रम (i = 0; i < ARRAY_SIZE(trans->dbg.समय_poपूर्णांक); i++) अणु
		काष्ठा iwl_dbg_tlv_समय_poपूर्णांक_data *tp =
			&trans->dbg.समय_poपूर्णांक[i];

		INIT_LIST_HEAD(&tp->trig_list);
		INIT_LIST_HEAD(&tp->hcmd_list);
		INIT_LIST_HEAD(&tp->active_trig_list);
	पूर्ण
पूर्ण

अटल पूर्णांक iwl_dbg_tlv_alloc_fragment(काष्ठा iwl_fw_runसमय *fwrt,
				      काष्ठा iwl_dram_data *frag, u32 pages)
अणु
	व्योम *block = शून्य;
	dma_addr_t physical;

	अगर (!frag || frag->size || !pages)
		वापस -EIO;

	/*
	 * We try to allocate as many pages as we can, starting with
	 * the requested amount and going करोwn until we can allocate
	 * something.  Because of DIV_ROUND_UP(), pages will never go
	 * करोwn to 0 and stop the loop, so stop when pages reaches 1,
	 * which is too small anyway.
	 */
	जबतक (pages > 1) अणु
		block = dma_alloc_coherent(fwrt->dev, pages * PAGE_SIZE,
					   &physical,
					   GFP_KERNEL | __GFP_NOWARN);
		अगर (block)
			अवरोध;

		IWL_WARN(fwrt, "WRT: Failed to allocate fragment size %lu\n",
			 pages * PAGE_SIZE);

		pages = DIV_ROUND_UP(pages, 2);
	पूर्ण

	अगर (!block)
		वापस -ENOMEM;

	frag->physical = physical;
	frag->block = block;
	frag->size = pages * PAGE_SIZE;

	वापस pages;
पूर्ण

अटल पूर्णांक iwl_dbg_tlv_alloc_fragments(काष्ठा iwl_fw_runसमय *fwrt,
				       क्रमागत iwl_fw_ini_allocation_id alloc_id)
अणु
	काष्ठा iwl_fw_mon *fw_mon;
	काष्ठा iwl_fw_ini_allocation_tlv *fw_mon_cfg;
	u32 num_frags, reमुख्य_pages, frag_pages;
	पूर्णांक i;

	अगर (alloc_id < IWL_FW_INI_ALLOCATION_INVALID ||
	    alloc_id >= IWL_FW_INI_ALLOCATION_NUM)
		वापस -EIO;

	fw_mon_cfg = &fwrt->trans->dbg.fw_mon_cfg[alloc_id];
	fw_mon = &fwrt->trans->dbg.fw_mon_ini[alloc_id];

	अगर (fw_mon->num_frags ||
	    fw_mon_cfg->buf_location !=
	    cpu_to_le32(IWL_FW_INI_LOCATION_DRAM_PATH))
		वापस 0;

	num_frags = le32_to_cpu(fw_mon_cfg->max_frags_num);
	अगर (!fw_has_capa(&fwrt->fw->ucode_capa,
			 IWL_UCODE_TLV_CAPA_DBG_BUF_ALLOC_CMD_SUPP)) अणु
		अगर (alloc_id != IWL_FW_INI_ALLOCATION_ID_DBGC1)
			वापस -EIO;
		num_frags = 1;
	पूर्ण

	reमुख्य_pages = DIV_ROUND_UP(le32_to_cpu(fw_mon_cfg->req_size),
				    PAGE_SIZE);
	num_frags = min_t(u32, num_frags, BUF_ALLOC_MAX_NUM_FRAGS);
	num_frags = min_t(u32, num_frags, reमुख्य_pages);
	frag_pages = DIV_ROUND_UP(reमुख्य_pages, num_frags);

	fw_mon->frags = kसुस्मृति(num_frags, माप(*fw_mon->frags), GFP_KERNEL);
	अगर (!fw_mon->frags)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_frags; i++) अणु
		पूर्णांक pages = min_t(u32, frag_pages, reमुख्य_pages);

		IWL_DEBUG_FW(fwrt,
			     "WRT: Allocating DRAM buffer (alloc_id=%u, fragment=%u, size=0x%lx)\n",
			     alloc_id, i, pages * PAGE_SIZE);

		pages = iwl_dbg_tlv_alloc_fragment(fwrt, &fw_mon->frags[i],
						   pages);
		अगर (pages < 0) अणु
			u32 alloc_size = le32_to_cpu(fw_mon_cfg->req_size) -
				(reमुख्य_pages * PAGE_SIZE);

			अगर (alloc_size < le32_to_cpu(fw_mon_cfg->min_size)) अणु
				iwl_dbg_tlv_fragments_मुक्त(fwrt->trans,
							   alloc_id);
				वापस pages;
			पूर्ण
			अवरोध;
		पूर्ण

		reमुख्य_pages -= pages;
		fw_mon->num_frags++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_dbg_tlv_apply_buffer(काष्ठा iwl_fw_runसमय *fwrt,
				    क्रमागत iwl_fw_ini_allocation_id alloc_id)
अणु
	काष्ठा iwl_fw_mon *fw_mon;
	u32 reमुख्य_frags, num_commands;
	पूर्णांक i, fw_mon_idx = 0;

	अगर (!fw_has_capa(&fwrt->fw->ucode_capa,
			 IWL_UCODE_TLV_CAPA_DBG_BUF_ALLOC_CMD_SUPP))
		वापस 0;

	अगर (alloc_id < IWL_FW_INI_ALLOCATION_INVALID ||
	    alloc_id >= IWL_FW_INI_ALLOCATION_NUM)
		वापस -EIO;

	अगर (le32_to_cpu(fwrt->trans->dbg.fw_mon_cfg[alloc_id].buf_location) !=
	    IWL_FW_INI_LOCATION_DRAM_PATH)
		वापस 0;

	fw_mon = &fwrt->trans->dbg.fw_mon_ini[alloc_id];

	/* the first fragment of DBGC1 is given to the FW via रेजिस्टर
	 * or context info
	 */
	अगर (alloc_id == IWL_FW_INI_ALLOCATION_ID_DBGC1)
		fw_mon_idx++;

	reमुख्य_frags = fw_mon->num_frags - fw_mon_idx;
	अगर (!reमुख्य_frags)
		वापस 0;

	num_commands = DIV_ROUND_UP(reमुख्य_frags, BUF_ALLOC_MAX_NUM_FRAGS);

	IWL_DEBUG_FW(fwrt, "WRT: Applying DRAM destination (alloc_id=%u)\n",
		     alloc_id);

	क्रम (i = 0; i < num_commands; i++) अणु
		u32 num_frags = min_t(u32, reमुख्य_frags,
				      BUF_ALLOC_MAX_NUM_FRAGS);
		काष्ठा iwl_buf_alloc_cmd data = अणु
			.alloc_id = cpu_to_le32(alloc_id),
			.num_frags = cpu_to_le32(num_frags),
			.buf_location =
				cpu_to_le32(IWL_FW_INI_LOCATION_DRAM_PATH),
		पूर्ण;
		काष्ठा iwl_host_cmd hcmd = अणु
			.id = WIDE_ID(DEBUG_GROUP, BUFFER_ALLOCATION),
			.data[0] = &data,
			.len[0] = माप(data),
		पूर्ण;
		पूर्णांक ret, j;

		क्रम (j = 0; j < num_frags; j++) अणु
			काष्ठा iwl_buf_alloc_frag *frag = &data.frags[j];
			काष्ठा iwl_dram_data *fw_mon_frag =
				&fw_mon->frags[fw_mon_idx++];

			frag->addr = cpu_to_le64(fw_mon_frag->physical);
			frag->size = cpu_to_le32(fw_mon_frag->size);
		पूर्ण
		ret = iwl_trans_send_cmd(fwrt->trans, &hcmd);
		अगर (ret)
			वापस ret;

		reमुख्य_frags -= num_frags;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम iwl_dbg_tlv_apply_buffers(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < IWL_FW_INI_ALLOCATION_NUM; i++) अणु
		ret = iwl_dbg_tlv_apply_buffer(fwrt, i);
		अगर (ret)
			IWL_WARN(fwrt,
				 "WRT: Failed to apply DRAM buffer for allocation id %d, ret=%d\n",
				 i, ret);
	पूर्ण
पूर्ण

अटल व्योम iwl_dbg_tlv_send_hcmds(काष्ठा iwl_fw_runसमय *fwrt,
				   काष्ठा list_head *hcmd_list)
अणु
	काष्ठा iwl_dbg_tlv_node *node;

	list_क्रम_each_entry(node, hcmd_list, list) अणु
		काष्ठा iwl_fw_ini_hcmd_tlv *hcmd = (व्योम *)node->tlv.data;
		काष्ठा iwl_fw_ini_hcmd *hcmd_data = &hcmd->hcmd;
		u16 hcmd_len = le32_to_cpu(node->tlv.length) - माप(*hcmd);
		काष्ठा iwl_host_cmd cmd = अणु
			.id = WIDE_ID(hcmd_data->group, hcmd_data->id),
			.len = अणु hcmd_len, पूर्ण,
			.data = अणु hcmd_data->data, पूर्ण,
		पूर्ण;

		iwl_trans_send_cmd(fwrt->trans, &cmd);
	पूर्ण
पूर्ण

अटल व्योम iwl_dbg_tlv_periodic_trig_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा iwl_dbg_tlv_समयr_node *समयr_node =
		from_समयr(समयr_node, t, समयr);
	काष्ठा iwl_fwrt_dump_data dump_data = अणु
		.trig = (व्योम *)समयr_node->tlv->data,
	पूर्ण;
	पूर्णांक ret;

	ret = iwl_fw_dbg_ini_collect(समयr_node->fwrt, &dump_data);
	अगर (!ret || ret == -EBUSY) अणु
		u32 occur = le32_to_cpu(dump_data.trig->occurrences);
		u32 collect_पूर्णांकerval = le32_to_cpu(dump_data.trig->data[0]);

		अगर (!occur)
			वापस;

		mod_समयr(t, jअगरfies + msecs_to_jअगरfies(collect_पूर्णांकerval));
	पूर्ण
पूर्ण

अटल व्योम iwl_dbg_tlv_set_periodic_trigs(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	काष्ठा iwl_dbg_tlv_node *node;
	काष्ठा list_head *trig_list =
		&fwrt->trans->dbg.समय_poपूर्णांक[IWL_FW_INI_TIME_POINT_PERIODIC].active_trig_list;

	list_क्रम_each_entry(node, trig_list, list) अणु
		काष्ठा iwl_fw_ini_trigger_tlv *trig = (व्योम *)node->tlv.data;
		काष्ठा iwl_dbg_tlv_समयr_node *समयr_node;
		u32 occur = le32_to_cpu(trig->occurrences), collect_पूर्णांकerval;
		u32 min_पूर्णांकerval = 100;

		अगर (!occur)
			जारी;

		/* make sure there is at least one dword of data क्रम the
		 * पूर्णांकerval value
		 */
		अगर (le32_to_cpu(node->tlv.length) <
		    माप(*trig) + माप(__le32)) अणु
			IWL_ERR(fwrt,
				"WRT: Invalid periodic trigger data was not given\n");
			जारी;
		पूर्ण

		अगर (le32_to_cpu(trig->data[0]) < min_पूर्णांकerval) अणु
			IWL_WARN(fwrt,
				 "WRT: Override min interval from %u to %u msec\n",
				 le32_to_cpu(trig->data[0]), min_पूर्णांकerval);
			trig->data[0] = cpu_to_le32(min_पूर्णांकerval);
		पूर्ण

		collect_पूर्णांकerval = le32_to_cpu(trig->data[0]);

		समयr_node = kzalloc(माप(*समयr_node), GFP_KERNEL);
		अगर (!समयr_node) अणु
			IWL_ERR(fwrt,
				"WRT: Failed to allocate periodic trigger\n");
			जारी;
		पूर्ण

		समयr_node->fwrt = fwrt;
		समयr_node->tlv = &node->tlv;
		समयr_setup(&समयr_node->समयr,
			    iwl_dbg_tlv_periodic_trig_handler, 0);

		list_add_tail(&समयr_node->list,
			      &fwrt->trans->dbg.periodic_trig_list);

		IWL_DEBUG_FW(fwrt, "WRT: Enabling periodic trigger\n");

		mod_समयr(&समयr_node->समयr,
			  jअगरfies + msecs_to_jअगरfies(collect_पूर्णांकerval));
	पूर्ण
पूर्ण

अटल bool is_trig_data_contained(स्थिर काष्ठा iwl_ucode_tlv *new,
				   स्थिर काष्ठा iwl_ucode_tlv *old)
अणु
	स्थिर काष्ठा iwl_fw_ini_trigger_tlv *new_trig = (स्थिर व्योम *)new->data;
	स्थिर काष्ठा iwl_fw_ini_trigger_tlv *old_trig = (स्थिर व्योम *)old->data;
	स्थिर __le32 *new_data = new_trig->data, *old_data = old_trig->data;
	u32 new_dwords_num = iwl_tlv_array_len(new, new_trig, data);
	u32 old_dwords_num = iwl_tlv_array_len(old, old_trig, data);
	पूर्णांक i, j;

	क्रम (i = 0; i < new_dwords_num; i++) अणु
		bool match = false;

		क्रम (j = 0; j < old_dwords_num; j++) अणु
			अगर (new_data[i] == old_data[j]) अणु
				match = true;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!match)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक iwl_dbg_tlv_override_trig_node(काष्ठा iwl_fw_runसमय *fwrt,
					  काष्ठा iwl_ucode_tlv *trig_tlv,
					  काष्ठा iwl_dbg_tlv_node *node)
अणु
	काष्ठा iwl_ucode_tlv *node_tlv = &node->tlv;
	काष्ठा iwl_fw_ini_trigger_tlv *node_trig = (व्योम *)node_tlv->data;
	काष्ठा iwl_fw_ini_trigger_tlv *trig = (व्योम *)trig_tlv->data;
	u32 policy = le32_to_cpu(trig->apply_policy);
	u32 size = le32_to_cpu(trig_tlv->length);
	u32 trig_data_len = size - माप(*trig);
	u32 offset = 0;

	अगर (!(policy & IWL_FW_INI_APPLY_POLICY_OVERRIDE_DATA)) अणु
		u32 data_len = le32_to_cpu(node_tlv->length) -
			माप(*node_trig);

		IWL_DEBUG_FW(fwrt,
			     "WRT: Appending trigger data (time point %u)\n",
			     le32_to_cpu(trig->समय_poपूर्णांक));

		offset += data_len;
		size += data_len;
	पूर्ण अन्यथा अणु
		IWL_DEBUG_FW(fwrt,
			     "WRT: Overriding trigger data (time point %u)\n",
			     le32_to_cpu(trig->समय_poपूर्णांक));
	पूर्ण

	अगर (size != le32_to_cpu(node_tlv->length)) अणु
		काष्ठा list_head *prev = node->list.prev;
		काष्ठा iwl_dbg_tlv_node *पंचांगp;

		list_del(&node->list);

		पंचांगp = kपुनः_स्मृति(node, माप(*node) + size, GFP_KERNEL);
		अगर (!पंचांगp) अणु
			IWL_WARN(fwrt,
				 "WRT: No memory to override trigger (time point %u)\n",
				 le32_to_cpu(trig->समय_poपूर्णांक));

			list_add(&node->list, prev);

			वापस -ENOMEM;
		पूर्ण

		list_add(&पंचांगp->list, prev);
		node_tlv = &पंचांगp->tlv;
		node_trig = (व्योम *)node_tlv->data;
	पूर्ण

	स_नकल(node_trig->data + offset, trig->data, trig_data_len);
	node_tlv->length = cpu_to_le32(size);

	अगर (policy & IWL_FW_INI_APPLY_POLICY_OVERRIDE_CFG) अणु
		IWL_DEBUG_FW(fwrt,
			     "WRT: Overriding trigger configuration (time point %u)\n",
			     le32_to_cpu(trig->समय_poपूर्णांक));

		/* the first 11 dwords are configuration related */
		स_नकल(node_trig, trig, माप(__le32) * 11);
	पूर्ण

	अगर (policy & IWL_FW_INI_APPLY_POLICY_OVERRIDE_REGIONS) अणु
		IWL_DEBUG_FW(fwrt,
			     "WRT: Overriding trigger regions (time point %u)\n",
			     le32_to_cpu(trig->समय_poपूर्णांक));

		node_trig->regions_mask = trig->regions_mask;
	पूर्ण अन्यथा अणु
		IWL_DEBUG_FW(fwrt,
			     "WRT: Appending trigger regions (time point %u)\n",
			     le32_to_cpu(trig->समय_poपूर्णांक));

		node_trig->regions_mask |= trig->regions_mask;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
iwl_dbg_tlv_add_active_trigger(काष्ठा iwl_fw_runसमय *fwrt,
			       काष्ठा list_head *trig_list,
			       काष्ठा iwl_ucode_tlv *trig_tlv)
अणु
	काष्ठा iwl_fw_ini_trigger_tlv *trig = (व्योम *)trig_tlv->data;
	काष्ठा iwl_dbg_tlv_node *node, *match = शून्य;
	u32 policy = le32_to_cpu(trig->apply_policy);

	list_क्रम_each_entry(node, trig_list, list) अणु
		अगर (!(policy & IWL_FW_INI_APPLY_POLICY_MATCH_TIME_POINT))
			अवरोध;

		अगर (!(policy & IWL_FW_INI_APPLY_POLICY_MATCH_DATA) ||
		    is_trig_data_contained(trig_tlv, &node->tlv)) अणु
			match = node;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!match) अणु
		IWL_DEBUG_FW(fwrt, "WRT: Enabling trigger (time point %u)\n",
			     le32_to_cpu(trig->समय_poपूर्णांक));
		वापस iwl_dbg_tlv_add(trig_tlv, trig_list);
	पूर्ण

	वापस iwl_dbg_tlv_override_trig_node(fwrt, trig_tlv, match);
पूर्ण

अटल व्योम
iwl_dbg_tlv_gen_active_trig_list(काष्ठा iwl_fw_runसमय *fwrt,
				 काष्ठा iwl_dbg_tlv_समय_poपूर्णांक_data *tp)
अणु
	काष्ठा iwl_dbg_tlv_node *node;
	काष्ठा list_head *trig_list = &tp->trig_list;
	काष्ठा list_head *active_trig_list = &tp->active_trig_list;

	list_क्रम_each_entry(node, trig_list, list) अणु
		काष्ठा iwl_ucode_tlv *tlv = &node->tlv;

		iwl_dbg_tlv_add_active_trigger(fwrt, active_trig_list, tlv);
	पूर्ण
पूर्ण

अटल bool iwl_dbg_tlv_check_fw_pkt(काष्ठा iwl_fw_runसमय *fwrt,
				     काष्ठा iwl_fwrt_dump_data *dump_data,
				     जोड़ iwl_dbg_tlv_tp_data *tp_data,
				     u32 trig_data)
अणु
	काष्ठा iwl_rx_packet *pkt = tp_data->fw_pkt;
	काष्ठा iwl_cmd_header *wanted_hdr = (व्योम *)&trig_data;

	अगर (pkt && (pkt->hdr.cmd == wanted_hdr->cmd &&
		    pkt->hdr.group_id == wanted_hdr->group_id)) अणु
		काष्ठा iwl_rx_packet *fw_pkt =
			kmemdup(pkt,
				माप(*pkt) + iwl_rx_packet_payload_len(pkt),
				GFP_ATOMIC);

		अगर (!fw_pkt)
			वापस false;

		dump_data->fw_pkt = fw_pkt;

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक
iwl_dbg_tlv_tp_trigger(काष्ठा iwl_fw_runसमय *fwrt,
		       काष्ठा list_head *active_trig_list,
		       जोड़ iwl_dbg_tlv_tp_data *tp_data,
		       bool (*data_check)(काष्ठा iwl_fw_runसमय *fwrt,
					  काष्ठा iwl_fwrt_dump_data *dump_data,
					  जोड़ iwl_dbg_tlv_tp_data *tp_data,
					  u32 trig_data))
अणु
	काष्ठा iwl_dbg_tlv_node *node;

	list_क्रम_each_entry(node, active_trig_list, list) अणु
		काष्ठा iwl_fwrt_dump_data dump_data = अणु
			.trig = (व्योम *)node->tlv.data,
		पूर्ण;
		u32 num_data = iwl_tlv_array_len(&node->tlv, dump_data.trig,
						 data);
		पूर्णांक ret, i;

		अगर (!num_data) अणु
			ret = iwl_fw_dbg_ini_collect(fwrt, &dump_data);
			अगर (ret)
				वापस ret;
		पूर्ण

		क्रम (i = 0; i < num_data; i++) अणु
			अगर (!data_check ||
			    data_check(fwrt, &dump_data, tp_data,
				       le32_to_cpu(dump_data.trig->data[i]))) अणु
				ret = iwl_fw_dbg_ini_collect(fwrt, &dump_data);
				अगर (ret)
					वापस ret;

				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम iwl_dbg_tlv_init_cfg(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	क्रमागत iwl_fw_ini_buffer_location *ini_dest = &fwrt->trans->dbg.ini_dest;
	पूर्णांक ret, i;
	u32 failed_alloc = 0;

	अगर (*ini_dest != IWL_FW_INI_LOCATION_INVALID)
		वापस;

	IWL_DEBUG_FW(fwrt,
		     "WRT: Generating active triggers list, domain 0x%x\n",
		     fwrt->trans->dbg.करोमुख्यs_biपंचांगap);

	क्रम (i = 0; i < ARRAY_SIZE(fwrt->trans->dbg.समय_poपूर्णांक); i++) अणु
		काष्ठा iwl_dbg_tlv_समय_poपूर्णांक_data *tp =
			&fwrt->trans->dbg.समय_poपूर्णांक[i];

		iwl_dbg_tlv_gen_active_trig_list(fwrt, tp);
	पूर्ण

	*ini_dest = IWL_FW_INI_LOCATION_INVALID;
	क्रम (i = 0; i < IWL_FW_INI_ALLOCATION_NUM; i++) अणु
		काष्ठा iwl_fw_ini_allocation_tlv *fw_mon_cfg =
			&fwrt->trans->dbg.fw_mon_cfg[i];
		u32 dest = le32_to_cpu(fw_mon_cfg->buf_location);

		अगर (dest == IWL_FW_INI_LOCATION_INVALID)
			जारी;

		अगर (*ini_dest == IWL_FW_INI_LOCATION_INVALID)
			*ini_dest = dest;

		अगर (dest != *ini_dest)
			जारी;

		ret = iwl_dbg_tlv_alloc_fragments(fwrt, i);

		अगर (ret) अणु
			IWL_WARN(fwrt,
				 "WRT: Failed to allocate DRAM buffer for allocation id %d, ret=%d\n",
				 i, ret);
			failed_alloc |= BIT(i);
		पूर्ण
	पूर्ण

	अगर (!failed_alloc)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(fwrt->trans->dbg.active_regions) && failed_alloc; i++) अणु
		काष्ठा iwl_fw_ini_region_tlv *reg;
		काष्ठा iwl_ucode_tlv **active_reg =
			&fwrt->trans->dbg.active_regions[i];
		u32 reg_type;

		अगर (!*active_reg)
			जारी;

		reg = (व्योम *)(*active_reg)->data;
		reg_type = le32_to_cpu(reg->type);

		अगर (reg_type != IWL_FW_INI_REGION_DRAM_BUFFER ||
		    !(BIT(le32_to_cpu(reg->dram_alloc_id)) & failed_alloc))
			जारी;

		IWL_DEBUG_FW(fwrt,
			     "WRT: removing allocation id %d from region id %d\n",
			     le32_to_cpu(reg->dram_alloc_id), i);

		failed_alloc &= ~le32_to_cpu(reg->dram_alloc_id);
		fwrt->trans->dbg.unsupported_region_msk |= BIT(i);

		kमुक्त(*active_reg);
		*active_reg = शून्य;
	पूर्ण
पूर्ण

व्योम iwl_dbg_tlv_समय_poपूर्णांक(काष्ठा iwl_fw_runसमय *fwrt,
			    क्रमागत iwl_fw_ini_समय_poपूर्णांक tp_id,
			    जोड़ iwl_dbg_tlv_tp_data *tp_data)
अणु
	काष्ठा list_head *hcmd_list, *trig_list;

	अगर (!iwl_trans_dbg_ini_valid(fwrt->trans) ||
	    tp_id == IWL_FW_INI_TIME_POINT_INVALID ||
	    tp_id >= IWL_FW_INI_TIME_POINT_NUM)
		वापस;

	hcmd_list = &fwrt->trans->dbg.समय_poपूर्णांक[tp_id].hcmd_list;
	trig_list = &fwrt->trans->dbg.समय_poपूर्णांक[tp_id].active_trig_list;

	चयन (tp_id) अणु
	हाल IWL_FW_INI_TIME_POINT_EARLY:
		iwl_dbg_tlv_init_cfg(fwrt);
		iwl_dbg_tlv_tp_trigger(fwrt, trig_list, tp_data, शून्य);
		अवरोध;
	हाल IWL_FW_INI_TIME_POINT_AFTER_ALIVE:
		iwl_dbg_tlv_apply_buffers(fwrt);
		iwl_dbg_tlv_send_hcmds(fwrt, hcmd_list);
		iwl_dbg_tlv_tp_trigger(fwrt, trig_list, tp_data, शून्य);
		अवरोध;
	हाल IWL_FW_INI_TIME_POINT_PERIODIC:
		iwl_dbg_tlv_set_periodic_trigs(fwrt);
		iwl_dbg_tlv_send_hcmds(fwrt, hcmd_list);
		अवरोध;
	हाल IWL_FW_INI_TIME_POINT_FW_RSP_OR_NOTIF:
	हाल IWL_FW_INI_TIME_POINT_MISSED_BEACONS:
	हाल IWL_FW_INI_TIME_POINT_FW_DHC_NOTIFICATION:
		iwl_dbg_tlv_send_hcmds(fwrt, hcmd_list);
		iwl_dbg_tlv_tp_trigger(fwrt, trig_list, tp_data,
				       iwl_dbg_tlv_check_fw_pkt);
		अवरोध;
	शेष:
		iwl_dbg_tlv_send_hcmds(fwrt, hcmd_list);
		iwl_dbg_tlv_tp_trigger(fwrt, trig_list, tp_data, शून्य);
		अवरोध;
	पूर्ण
पूर्ण
IWL_EXPORT_SYMBOL(iwl_dbg_tlv_समय_poपूर्णांक);
