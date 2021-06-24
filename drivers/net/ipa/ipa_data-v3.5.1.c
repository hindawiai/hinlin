<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2019-2021 Linaro Ltd.
 */

#समावेश <linux/log2.h>

#समावेश "gsi.h"
#समावेश "ipa_data.h"
#समावेश "ipa_endpoint.h"
#समावेश "ipa_mem.h"

/** क्रमागत ipa_resource_type - IPA resource types क्रम an SoC having IPA v3.5.1 */
क्रमागत ipa_resource_type अणु
	/* Source resource types; first must have value 0 */
	IPA_RESOURCE_TYPE_SRC_PKT_CONTEXTS		= 0,
	IPA_RESOURCE_TYPE_SRC_DESCRIPTOR_LISTS,
	IPA_RESOURCE_TYPE_SRC_DESCRIPTOR_BUFF,
	IPA_RESOURCE_TYPE_SRC_HPS_DMARS,
	IPA_RESOURCE_TYPE_SRC_ACK_ENTRIES,

	/* Destination resource types; first must have value 0 */
	IPA_RESOURCE_TYPE_DST_DATA_SECTORS		= 0,
	IPA_RESOURCE_TYPE_DST_DPS_DMARS,
पूर्ण;

/* Resource groups used क्रम an SoC having IPA v3.5.1 */
क्रमागत ipa_rsrc_group_id अणु
	/* Source resource group identअगरiers */
	IPA_RSRC_GROUP_SRC_LWA_DL	= 0,
	IPA_RSRC_GROUP_SRC_UL_DL,
	IPA_RSRC_GROUP_SRC_MHI_DMA,
	IPA_RSRC_GROUP_SRC_UC_RX_Q,
	IPA_RSRC_GROUP_SRC_COUNT,	/* Last in set; not a source group */

	/* Destination resource group identअगरiers */
	IPA_RSRC_GROUP_DST_LWA_DL	= 0,
	IPA_RSRC_GROUP_DST_UL_DL_DPL,
	IPA_RSRC_GROUP_DST_UNUSED_2,
	IPA_RSRC_GROUP_DST_COUNT,	/* Last; not a destination group */
पूर्ण;

/* QSB configuration data क्रम an SoC having IPA v3.5.1 */
अटल स्थिर काष्ठा ipa_qsb_data ipa_qsb_data[] = अणु
	[IPA_QSB_MASTER_DDR] = अणु
		.max_ग_लिखोs	= 8,
		.max_पढ़ोs	= 8,
	पूर्ण,
	[IPA_QSB_MASTER_PCIE] = अणु
		.max_ग_लिखोs	= 4,
		.max_पढ़ोs	= 12,
	पूर्ण,
पूर्ण;

/* Endpoपूर्णांक datdata क्रम an SoC having IPA v3.5.1 */
अटल स्थिर काष्ठा ipa_gsi_endpoपूर्णांक_data ipa_gsi_endpoपूर्णांक_data[] = अणु
	[IPA_ENDPOINT_AP_COMMAND_TX] = अणु
		.ee_id		= GSI_EE_AP,
		.channel_id	= 4,
		.endpoपूर्णांक_id	= 5,
		.toward_ipa	= true,
		.channel = अणु
			.tre_count	= 512,
			.event_count	= 256,
			.tlv_count	= 20,
		पूर्ण,
		.endpoपूर्णांक = अणु
			.config = अणु
				.resource_group	= IPA_RSRC_GROUP_SRC_UL_DL,
				.dma_mode	= true,
				.dma_endpoपूर्णांक	= IPA_ENDPOINT_AP_LAN_RX,
				.tx = अणु
					.seq_type = IPA_SEQ_DMA,
				पूर्ण,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[IPA_ENDPOINT_AP_LAN_RX] = अणु
		.ee_id		= GSI_EE_AP,
		.channel_id	= 5,
		.endpoपूर्णांक_id	= 9,
		.toward_ipa	= false,
		.channel = अणु
			.tre_count	= 256,
			.event_count	= 256,
			.tlv_count	= 8,
		पूर्ण,
		.endpoपूर्णांक = अणु
			.config = अणु
				.resource_group	= IPA_RSRC_GROUP_DST_UL_DL_DPL,
				.aggregation	= true,
				.status_enable	= true,
				.rx = अणु
					.pad_align	= ilog2(माप(u32)),
				पूर्ण,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[IPA_ENDPOINT_AP_MODEM_TX] = अणु
		.ee_id		= GSI_EE_AP,
		.channel_id	= 3,
		.endpoपूर्णांक_id	= 2,
		.toward_ipa	= true,
		.channel = अणु
			.tre_count	= 512,
			.event_count	= 512,
			.tlv_count	= 16,
		पूर्ण,
		.endpoपूर्णांक = अणु
			.filter_support	= true,
			.config = अणु
				.resource_group	= IPA_RSRC_GROUP_SRC_UL_DL,
				.checksum	= true,
				.qmap		= true,
				.status_enable	= true,
				.tx = अणु
					.seq_type = IPA_SEQ_2_PASS_SKIP_LAST_UC,
					.seq_rep_type = IPA_SEQ_REP_DMA_PARSER,
					.status_endpoपूर्णांक =
						IPA_ENDPOINT_MODEM_AP_RX,
				पूर्ण,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[IPA_ENDPOINT_AP_MODEM_RX] = अणु
		.ee_id		= GSI_EE_AP,
		.channel_id	= 6,
		.endpoपूर्णांक_id	= 10,
		.toward_ipa	= false,
		.channel = अणु
			.tre_count	= 256,
			.event_count	= 256,
			.tlv_count	= 8,
		पूर्ण,
		.endpoपूर्णांक = अणु
			.config = अणु
				.resource_group	= IPA_RSRC_GROUP_DST_UL_DL_DPL,
				.checksum	= true,
				.qmap		= true,
				.aggregation	= true,
				.rx = अणु
					.aggr_बंद_eof	= true,
				पूर्ण,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	[IPA_ENDPOINT_MODEM_LAN_TX] = अणु
		.ee_id		= GSI_EE_MODEM,
		.channel_id	= 0,
		.endpoपूर्णांक_id	= 3,
		.toward_ipa	= true,
		.endpoपूर्णांक = अणु
			.filter_support	= true,
		पूर्ण,
	पूर्ण,
	[IPA_ENDPOINT_MODEM_AP_TX] = अणु
		.ee_id		= GSI_EE_MODEM,
		.channel_id	= 4,
		.endpoपूर्णांक_id	= 6,
		.toward_ipa	= true,
		.endpoपूर्णांक = अणु
			.filter_support	= true,
		पूर्ण,
	पूर्ण,
	[IPA_ENDPOINT_MODEM_AP_RX] = अणु
		.ee_id		= GSI_EE_MODEM,
		.channel_id	= 2,
		.endpoपूर्णांक_id	= 12,
		.toward_ipa	= false,
	पूर्ण,
पूर्ण;

/* Source resource configuration data क्रम an SoC having IPA v3.5.1 */
अटल स्थिर काष्ठा ipa_resource ipa_resource_src[] = अणु
	[IPA_RESOURCE_TYPE_SRC_PKT_CONTEXTS] = अणु
		.limits[IPA_RSRC_GROUP_SRC_LWA_DL] = अणु
			.min = 1,	.max = 255,
		पूर्ण,
		.limits[IPA_RSRC_GROUP_SRC_UL_DL] = अणु
			.min = 1,	.max = 255,
		पूर्ण,
		.limits[IPA_RSRC_GROUP_SRC_UC_RX_Q] = अणु
			.min = 1,	.max = 63,
		पूर्ण,
	पूर्ण,
	[IPA_RESOURCE_TYPE_SRC_DESCRIPTOR_LISTS] = अणु
		.limits[IPA_RSRC_GROUP_SRC_LWA_DL] = अणु
			.min = 10,	.max = 10,
		पूर्ण,
		.limits[IPA_RSRC_GROUP_SRC_UL_DL] = अणु
			.min = 10,	.max = 10,
		पूर्ण,
		.limits[IPA_RSRC_GROUP_SRC_UC_RX_Q] = अणु
			.min = 8,	.max = 8,
		पूर्ण,
	पूर्ण,
	[IPA_RESOURCE_TYPE_SRC_DESCRIPTOR_BUFF] = अणु
		.limits[IPA_RSRC_GROUP_SRC_LWA_DL] = अणु
			.min = 12,	.max = 12,
		पूर्ण,
		.limits[IPA_RSRC_GROUP_SRC_UL_DL] = अणु
			.min = 14,	.max = 14,
		पूर्ण,
		.limits[IPA_RSRC_GROUP_SRC_UC_RX_Q] = अणु
			.min = 8,	.max = 8,
		पूर्ण,
	पूर्ण,
	[IPA_RESOURCE_TYPE_SRC_HPS_DMARS] = अणु
		.limits[IPA_RSRC_GROUP_SRC_LWA_DL] = अणु
			.min = 0,	.max = 63,
		पूर्ण,
		.limits[IPA_RSRC_GROUP_SRC_UL_DL] = अणु
			.min = 0,	.max = 63,
		पूर्ण,
		.limits[IPA_RSRC_GROUP_SRC_MHI_DMA] = अणु
			.min = 0,	.max = 63,
		पूर्ण,
		.limits[IPA_RSRC_GROUP_SRC_UC_RX_Q] = अणु
			.min = 0,	.max = 63,
		पूर्ण,
	पूर्ण,
	[IPA_RESOURCE_TYPE_SRC_ACK_ENTRIES] = अणु
		.limits[IPA_RSRC_GROUP_SRC_LWA_DL] = अणु
			.min = 14,	.max = 14,
		पूर्ण,
		.limits[IPA_RSRC_GROUP_SRC_UL_DL] = अणु
			.min = 20,	.max = 20,
		पूर्ण,
		.limits[IPA_RSRC_GROUP_SRC_UC_RX_Q] = अणु
			.min = 14,	.max = 14,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* Destination resource configuration data क्रम an SoC having IPA v3.5.1 */
अटल स्थिर काष्ठा ipa_resource ipa_resource_dst[] = अणु
	[IPA_RESOURCE_TYPE_DST_DATA_SECTORS] = अणु
		.limits[IPA_RSRC_GROUP_DST_LWA_DL] = अणु
			.min = 4,	.max = 4,
		पूर्ण,
		.limits[1] = अणु
			.min = 4,	.max = 4,
		पूर्ण,
		.limits[IPA_RSRC_GROUP_DST_UNUSED_2] = अणु
			.min = 3,	.max = 3,
		पूर्ण
	पूर्ण,
	[IPA_RESOURCE_TYPE_DST_DPS_DMARS] = अणु
		.limits[IPA_RSRC_GROUP_DST_LWA_DL] = अणु
			.min = 2,	.max = 63,
		पूर्ण,
		.limits[IPA_RSRC_GROUP_DST_UL_DL_DPL] = अणु
			.min = 1,	.max = 63,
		पूर्ण,
		.limits[IPA_RSRC_GROUP_DST_UNUSED_2] = अणु
			.min = 1,	.max = 2,
		पूर्ण
	पूर्ण,
पूर्ण;

/* Resource configuration data क्रम an SoC having IPA v3.5.1 */
अटल स्थिर काष्ठा ipa_resource_data ipa_resource_data = अणु
	.rsrc_group_src_count	= IPA_RSRC_GROUP_SRC_COUNT,
	.rsrc_group_dst_count	= IPA_RSRC_GROUP_DST_COUNT,
	.resource_src_count	= ARRAY_SIZE(ipa_resource_src),
	.resource_src		= ipa_resource_src,
	.resource_dst_count	= ARRAY_SIZE(ipa_resource_dst),
	.resource_dst		= ipa_resource_dst,
पूर्ण;

/* IPA-resident memory region data क्रम an SoC having IPA v3.5.1 */
अटल स्थिर काष्ठा ipa_mem ipa_mem_local_data[] = अणु
	[IPA_MEM_UC_SHARED] = अणु
		.offset		= 0x0000,
		.size		= 0x0080,
		.canary_count	= 0,
	पूर्ण,
	[IPA_MEM_UC_INFO] = अणु
		.offset		= 0x0080,
		.size		= 0x0200,
		.canary_count	= 0,
	पूर्ण,
	[IPA_MEM_V4_FILTER_HASHED] = अणु
		.offset		= 0x0288,
		.size		= 0x0078,
		.canary_count	= 2,
	पूर्ण,
	[IPA_MEM_V4_FILTER] = अणु
		.offset		= 0x0308,
		.size		= 0x0078,
		.canary_count	= 2,
	पूर्ण,
	[IPA_MEM_V6_FILTER_HASHED] = अणु
		.offset		= 0x0388,
		.size		= 0x0078,
		.canary_count	= 2,
	पूर्ण,
	[IPA_MEM_V6_FILTER] = अणु
		.offset		= 0x0408,
		.size		= 0x0078,
		.canary_count	= 2,
	पूर्ण,
	[IPA_MEM_V4_ROUTE_HASHED] = अणु
		.offset		= 0x0488,
		.size		= 0x0078,
		.canary_count	= 2,
	पूर्ण,
	[IPA_MEM_V4_ROUTE] = अणु
		.offset		= 0x0508,
		.size		= 0x0078,
		.canary_count	= 2,
	पूर्ण,
	[IPA_MEM_V6_ROUTE_HASHED] = अणु
		.offset		= 0x0588,
		.size		= 0x0078,
		.canary_count	= 2,
	पूर्ण,
	[IPA_MEM_V6_ROUTE] = अणु
		.offset		= 0x0608,
		.size		= 0x0078,
		.canary_count	= 2,
	पूर्ण,
	[IPA_MEM_MODEM_HEADER] = अणु
		.offset		= 0x0688,
		.size		= 0x0140,
		.canary_count	= 2,
	पूर्ण,
	[IPA_MEM_MODEM_PROC_CTX] = अणु
		.offset		= 0x07d0,
		.size		= 0x0200,
		.canary_count	= 2,
	पूर्ण,
	[IPA_MEM_AP_PROC_CTX] = अणु
		.offset		= 0x09d0,
		.size		= 0x0200,
		.canary_count	= 0,
	पूर्ण,
	[IPA_MEM_MODEM] = अणु
		.offset		= 0x0bd8,
		.size		= 0x1024,
		.canary_count	= 0,
	पूर्ण,
	[IPA_MEM_UC_EVENT_RING] = अणु
		.offset		= 0x1c00,
		.size		= 0x0400,
		.canary_count	= 1,
	पूर्ण,
पूर्ण;

/* Memory configuration data क्रम an SoC having IPA v3.5.1 */
अटल स्थिर काष्ठा ipa_mem_data ipa_mem_data = अणु
	.local_count	= ARRAY_SIZE(ipa_mem_local_data),
	.local		= ipa_mem_local_data,
	.imem_addr	= 0x146bd000,
	.imem_size	= 0x00002000,
	.smem_id	= 497,
	.smem_size	= 0x00002000,
पूर्ण;

/* Interconnect bandwidths are in 1000 byte/second units */
अटल स्थिर काष्ठा ipa_पूर्णांकerconnect_data ipa_पूर्णांकerconnect_data[] = अणु
	अणु
		.name			= "memory",
		.peak_bandwidth		= 600000,	/* 600 MBps */
		.average_bandwidth	= 80000,	/* 80 MBps */
	पूर्ण,
	/* Average bandwidth is unused क्रम the next two पूर्णांकerconnects */
	अणु
		.name			= "imem",
		.peak_bandwidth		= 350000,	/* 350 MBps */
		.average_bandwidth	= 0,		/* unused */
	पूर्ण,
	अणु
		.name			= "config",
		.peak_bandwidth		= 40000,	/* 40 MBps */
		.average_bandwidth	= 0,		/* unused */
	पूर्ण,
पूर्ण;

/* Clock and पूर्णांकerconnect configuration data क्रम an SoC having IPA v3.5.1 */
अटल स्थिर काष्ठा ipa_घड़ी_data ipa_घड़ी_data = अणु
	.core_घड़ी_rate	= 75 * 1000 * 1000,	/* Hz */
	.पूर्णांकerconnect_count	= ARRAY_SIZE(ipa_पूर्णांकerconnect_data),
	.पूर्णांकerconnect_data	= ipa_पूर्णांकerconnect_data,
पूर्ण;

/* Configuration data क्रम an SoC having IPA v3.5.1 */
स्थिर काष्ठा ipa_data ipa_data_v3_5_1 = अणु
	.version	= IPA_VERSION_3_5_1,
	.backward_compat = BCR_CMDQ_L_LACK_ONE_ENTRY_FMASK |
			   BCR_TX_NOT_USING_BRESP_FMASK |
			   BCR_SUSPEND_L2_IRQ_FMASK |
			   BCR_HOLB_DROP_L2_IRQ_FMASK |
			   BCR_DUAL_TX_FMASK,
	.qsb_count	= ARRAY_SIZE(ipa_qsb_data),
	.qsb_data	= ipa_qsb_data,
	.endpoपूर्णांक_count	= ARRAY_SIZE(ipa_gsi_endpoपूर्णांक_data),
	.endpoपूर्णांक_data	= ipa_gsi_endpoपूर्णांक_data,
	.resource_data	= &ipa_resource_data,
	.mem_data	= &ipa_mem_data,
	.घड़ी_data	= &ipa_घड़ी_data,
पूर्ण;
