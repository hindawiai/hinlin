<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2018-2021 Linaro Ltd.
 */
#अगर_अघोषित _IPA_REG_H_
#घोषणा _IPA_REG_H_

#समावेश <linux/bitfield.h>

#समावेश "ipa_version.h"

काष्ठा ipa;

/**
 * DOC: IPA Registers
 *
 * IPA रेजिस्टरs are located within the "ipa-reg" address space defined by
 * Device Tree.  The offset of each रेजिस्टर within that space is specअगरied
 * by symbols defined below.  The address space is mapped to भव memory
 * space in ipa_mem_init().  All IPA रेजिस्टरs are 32 bits wide.
 *
 * Certain रेजिस्टर types are duplicated क्रम a number of instances of
 * something.  For example, each IPA endpoपूर्णांक has an set of रेजिस्टरs
 * defining its configuration.  The offset to an endpoपूर्णांक's set of रेजिस्टरs
 * is computed based on an "base" offset, plus an endpoपूर्णांक's ID multiplied
 * and a "stride" value क्रम the रेजिस्टर.  For such रेजिस्टरs, the offset is
 * computed by a function-like macro that takes a parameter used in the
 * computation.
 *
 * Some रेजिस्टर offsets depend on execution environment.  For these an "ee"
 * parameter is supplied to the offset macro.  The "ee" value is a member of
 * the gsi_ee क्रमागतerated type.
 *
 * The offset of a रेजिस्टर dependent on endpoपूर्णांक ID is computed by a macro
 * that is supplied a parameter "ep", "txep", or "rxep".  A रेजिस्टर with an
 * "ep" parameter is valid क्रम any endpoपूर्णांक; a रेजिस्टर with a "txep" or
 * "rxep" parameter is valid only क्रम TX or RX endpoपूर्णांकs, respectively.  The
 * "*ep" value is assumed to be less than the maximum valid endpoपूर्णांक ID
 * क्रम the current hardware, and that will not exceed IPA_ENDPOपूर्णांक_उच्च.
 *
 * The offset of रेजिस्टरs related to filter and route tables is computed
 * by a macro that is supplied a parameter "er".  The "er" represents an
 * endpoपूर्णांक ID क्रम filters, or a route ID क्रम routes.  For filters, the
 * endpoपूर्णांक ID must be less than IPA_ENDPOपूर्णांक_उच्च, but is further restricted
 * because not all endpoपूर्णांकs support filtering.  For routes, the route ID
 * must be less than IPA_ROUTE_MAX.
 *
 * The offset of रेजिस्टरs related to resource types is computed by a macro
 * that is supplied a parameter "rt".  The "rt" represents a resource type,
 * which is is a member of the ipa_resource_type_src क्रमागतerated type क्रम
 * source endpoपूर्णांक resources or the ipa_resource_type_dst क्रमागतerated type
 * क्रम destination endpoपूर्णांक resources.
 *
 * Some रेजिस्टरs encode multiple fields within them.  For these, each field
 * has a symbol below defining a field mask that encodes both the position
 * and width of the field within its रेजिस्टर.
 *
 * In some हालs, dअगरferent versions of IPA hardware use dअगरferent offset or
 * field mask values.  In such हालs an अंतरभूत_function(ipa) is used rather
 * than a MACRO to define the offset or field mask to use.
 *
 * Finally, some रेजिस्टरs hold biपंचांगasks representing endpoपूर्णांकs.  In such
 * हालs the @available field in the @ipa काष्ठाure defines the "full" set
 * of valid bits क्रम the रेजिस्टर.
 */

#घोषणा IPA_REG_COMP_CFG_OFFSET				0x0000003c
/* The next field is not supported क्रम IPA v4.0+, not present क्रम IPA v4.5+ */
#घोषणा ENABLE_FMASK				GENMASK(0, 0)
/* The next field is present क्रम IPA v4.7+ */
#घोषणा RAM_ARB_PRI_CLIENT_SAMP_FIX_DIS_FMASK	GENMASK(0, 0)
#घोषणा GSI_SNOC_BYPASS_DIS_FMASK		GENMASK(1, 1)
#घोषणा GEN_QMB_0_SNOC_BYPASS_DIS_FMASK		GENMASK(2, 2)
#घोषणा GEN_QMB_1_SNOC_BYPASS_DIS_FMASK		GENMASK(3, 3)
/* The next field is not present क्रम IPA v4.5+ */
#घोषणा IPA_DCMP_FAST_CLK_EN_FMASK		GENMASK(4, 4)
/* The next twelve fields are present क्रम IPA v4.0+ */
#घोषणा IPA_QMB_SELECT_CONS_EN_FMASK		GENMASK(5, 5)
#घोषणा IPA_QMB_SELECT_PROD_EN_FMASK		GENMASK(6, 6)
#घोषणा GSI_MULTI_INORDER_RD_DIS_FMASK		GENMASK(7, 7)
#घोषणा GSI_MULTI_INORDER_WR_DIS_FMASK		GENMASK(8, 8)
#घोषणा GEN_QMB_0_MULTI_INORDER_RD_DIS_FMASK	GENMASK(9, 9)
#घोषणा GEN_QMB_1_MULTI_INORDER_RD_DIS_FMASK	GENMASK(10, 10)
#घोषणा GEN_QMB_0_MULTI_INORDER_WR_DIS_FMASK	GENMASK(11, 11)
#घोषणा GEN_QMB_1_MULTI_INORDER_WR_DIS_FMASK	GENMASK(12, 12)
#घोषणा GEN_QMB_0_SNOC_CNOC_LOOP_PROT_DIS_FMASK	GENMASK(13, 13)
#घोषणा GSI_SNOC_CNOC_LOOP_PROT_DISABLE_FMASK	GENMASK(14, 14)
#घोषणा GSI_MULTI_AXI_MASTERS_DIS_FMASK		GENMASK(15, 15)
#घोषणा IPA_QMB_SELECT_GLOBAL_EN_FMASK		GENMASK(16, 16)
/* The next five fields are present क्रम IPA v4.9+ */
#घोषणा QMB_RAM_RD_CACHE_DISABLE_FMASK		GENMASK(19, 19)
#घोषणा GENQMB_AOOOWR_FMASK			GENMASK(20, 20)
#घोषणा IF_OUT_OF_BUF_STOP_RESET_MASK_EN_FMASK	GENMASK(21, 21)
#घोषणा GEN_QMB_1_DYNAMIC_ASIZE_FMASK		GENMASK(30, 30)
#घोषणा GEN_QMB_0_DYNAMIC_ASIZE_FMASK		GENMASK(31, 31)

/* Encoded value क्रम COMP_CFG रेजिस्टर ATOMIC_FETCHER_ARB_LOCK_DIS field */
अटल अंतरभूत u32 arbitration_lock_disable_encoded(क्रमागत ipa_version version,
						   u32 mask)
अणु
	/* निश्चित(version >= IPA_VERSION_4_0); */

	अगर (version < IPA_VERSION_4_9)
		वापस u32_encode_bits(mask, GENMASK(20, 17));

	अगर (version == IPA_VERSION_4_9)
		वापस u32_encode_bits(mask, GENMASK(24, 22));

	वापस u32_encode_bits(mask, GENMASK(23, 22));
पूर्ण

/* Encoded value क्रम COMP_CFG रेजिस्टर FULL_FLUSH_WAIT_RS_CLOSURE_EN field */
अटल अंतरभूत u32 full_flush_rsc_closure_en_encoded(क्रमागत ipa_version version,
						    bool enable)
अणु
	u32 val = enable ? 1 : 0;

	/* निश्चित(version >= IPA_VERSION_4_5); */

	अगर (version == IPA_VERSION_4_5 || version == IPA_VERSION_4_7)
		वापस u32_encode_bits(val, GENMASK(21, 21));

	वापस u32_encode_bits(val, GENMASK(17, 17));
पूर्ण

#घोषणा IPA_REG_CLKON_CFG_OFFSET			0x00000044
#घोषणा RX_FMASK				GENMASK(0, 0)
#घोषणा PROC_FMASK				GENMASK(1, 1)
#घोषणा TX_WRAPPER_FMASK			GENMASK(2, 2)
#घोषणा MISC_FMASK				GENMASK(3, 3)
#घोषणा RAM_ARB_FMASK				GENMASK(4, 4)
#घोषणा FTCH_HPS_FMASK				GENMASK(5, 5)
#घोषणा FTCH_DPS_FMASK				GENMASK(6, 6)
#घोषणा HPS_FMASK				GENMASK(7, 7)
#घोषणा DPS_FMASK				GENMASK(8, 8)
#घोषणा RX_HPS_CMDQS_FMASK			GENMASK(9, 9)
#घोषणा HPS_DPS_CMDQS_FMASK			GENMASK(10, 10)
#घोषणा DPS_TX_CMDQS_FMASK			GENMASK(11, 11)
#घोषणा RSRC_MNGR_FMASK				GENMASK(12, 12)
#घोषणा CTX_HANDLER_FMASK			GENMASK(13, 13)
#घोषणा ACK_MNGR_FMASK				GENMASK(14, 14)
#घोषणा D_DCPH_FMASK				GENMASK(15, 15)
#घोषणा H_DCPH_FMASK				GENMASK(16, 16)
/* The next field is not present क्रम IPA v4.5+ */
#घोषणा DCMP_FMASK				GENMASK(17, 17)
/* The next three fields are present क्रम IPA v3.5+ */
#घोषणा NTF_TX_CMDQS_FMASK			GENMASK(18, 18)
#घोषणा TX_0_FMASK				GENMASK(19, 19)
#घोषणा TX_1_FMASK				GENMASK(20, 20)
/* The next field is present क्रम IPA v3.5.1+ */
#घोषणा FNR_FMASK				GENMASK(21, 21)
/* The next eight fields are present क्रम IPA v4.0+ */
#घोषणा QSB2AXI_CMDQ_L_FMASK			GENMASK(22, 22)
#घोषणा AGGR_WRAPPER_FMASK			GENMASK(23, 23)
#घोषणा RAM_SLAVEWAY_FMASK			GENMASK(24, 24)
#घोषणा QMB_FMASK				GENMASK(25, 25)
#घोषणा WEIGHT_ARB_FMASK			GENMASK(26, 26)
#घोषणा GSI_IF_FMASK				GENMASK(27, 27)
#घोषणा GLOBAL_FMASK				GENMASK(28, 28)
#घोषणा GLOBAL_2X_CLK_FMASK			GENMASK(29, 29)
/* The next field is present क्रम IPA v4.5+ */
#घोषणा DPL_FIFO_FMASK				GENMASK(30, 30)
/* The next field is present क्रम IPA v4.7+ */
#घोषणा DRBIP_FMASK				GENMASK(31, 31)

#घोषणा IPA_REG_ROUTE_OFFSET				0x00000048
#घोषणा ROUTE_DIS_FMASK				GENMASK(0, 0)
#घोषणा ROUTE_DEF_PIPE_FMASK			GENMASK(5, 1)
#घोषणा ROUTE_DEF_HDR_TABLE_FMASK		GENMASK(6, 6)
#घोषणा ROUTE_DEF_HDR_OFST_FMASK		GENMASK(16, 7)
#घोषणा ROUTE_FRAG_DEF_PIPE_FMASK		GENMASK(21, 17)
#घोषणा ROUTE_DEF_RETAIN_HDR_FMASK		GENMASK(24, 24)

#घोषणा IPA_REG_SHARED_MEM_SIZE_OFFSET			0x00000054
#घोषणा SHARED_MEM_SIZE_FMASK			GENMASK(15, 0)
#घोषणा SHARED_MEM_BADDR_FMASK			GENMASK(31, 16)

#घोषणा IPA_REG_QSB_MAX_WRITES_OFFSET			0x00000074
#घोषणा GEN_QMB_0_MAX_WRITES_FMASK		GENMASK(3, 0)
#घोषणा GEN_QMB_1_MAX_WRITES_FMASK		GENMASK(7, 4)

#घोषणा IPA_REG_QSB_MAX_READS_OFFSET			0x00000078
#घोषणा GEN_QMB_0_MAX_READS_FMASK		GENMASK(3, 0)
#घोषणा GEN_QMB_1_MAX_READS_FMASK		GENMASK(7, 4)
/* The next two fields are present क्रम IPA v4.0+ */
#घोषणा GEN_QMB_0_MAX_READS_BEATS_FMASK		GENMASK(23, 16)
#घोषणा GEN_QMB_1_MAX_READS_BEATS_FMASK		GENMASK(31, 24)

अटल अंतरभूत u32 ipa_reg_filt_rout_hash_en_offset(क्रमागत ipa_version version)
अणु
	अगर (version < IPA_VERSION_4_0)
		वापस 0x000008c;

	वापस 0x0000148;
पूर्ण

अटल अंतरभूत u32 ipa_reg_filt_rout_hash_flush_offset(क्रमागत ipa_version version)
अणु
	अगर (version < IPA_VERSION_4_0)
		वापस 0x0000090;

	वापस 0x000014c;
पूर्ण

/* The next four fields are used क्रम the hash enable and flush रेजिस्टरs */
#घोषणा IPV6_ROUTER_HASH_FMASK			GENMASK(0, 0)
#घोषणा IPV6_FILTER_HASH_FMASK			GENMASK(4, 4)
#घोषणा IPV4_ROUTER_HASH_FMASK			GENMASK(8, 8)
#घोषणा IPV4_FILTER_HASH_FMASK			GENMASK(12, 12)

/* ipa->available defines the valid bits in the STATE_AGGR_ACTIVE रेजिस्टर */
अटल अंतरभूत u32 ipa_reg_state_aggr_active_offset(क्रमागत ipa_version version)
अणु
	अगर (version < IPA_VERSION_4_0)
		वापस 0x0000010c;

	वापस 0x000000b4;
पूर्ण

/* The next रेजिस्टर is not present क्रम IPA v4.5+ */
#घोषणा IPA_REG_BCR_OFFSET				0x000001d0
/* The next two fields are not present क्रम IPA v4.2+ */
#घोषणा BCR_CMDQ_L_LACK_ONE_ENTRY_FMASK		GENMASK(0, 0)
#घोषणा BCR_TX_NOT_USING_BRESP_FMASK		GENMASK(1, 1)
/* The next field is invalid क्रम IPA v4.0+ */
#घोषणा BCR_TX_SUSPEND_IRQ_ASSERT_ONCE_FMASK	GENMASK(2, 2)
/* The next two fields are not present क्रम IPA v4.2+ */
#घोषणा BCR_SUSPEND_L2_IRQ_FMASK		GENMASK(3, 3)
#घोषणा BCR_HOLB_DROP_L2_IRQ_FMASK		GENMASK(4, 4)
/* The next five fields are present क्रम IPA v3.5+ */
#घोषणा BCR_DUAL_TX_FMASK			GENMASK(5, 5)
#घोषणा BCR_ENABLE_FILTER_DATA_CACHE_FMASK	GENMASK(6, 6)
#घोषणा BCR_NOTIF_PRIORITY_OVER_ZLT_FMASK	GENMASK(7, 7)
#घोषणा BCR_FILTER_PREFETCH_EN_FMASK		GENMASK(8, 8)
#घोषणा BCR_ROUTER_PREFETCH_EN_FMASK		GENMASK(9, 9)

/* The value of the next रेजिस्टर must be a multiple of 8 (bottom 3 bits 0) */
#घोषणा IPA_REG_LOCAL_PKT_PROC_CNTXT_OFFSET		0x000001e8

/* Encoded value क्रम LOCAL_PKT_PROC_CNTXT रेजिस्टर BASE_ADDR field */
अटल अंतरभूत u32 proc_cntxt_base_addr_encoded(क्रमागत ipa_version version,
					       u32 addr)
अणु
	अगर (version < IPA_VERSION_4_5)
		वापस u32_encode_bits(addr, GENMASK(16, 0));

	वापस u32_encode_bits(addr, GENMASK(17, 0));
पूर्ण

/* ipa->available defines the valid bits in the AGGR_FORCE_CLOSE रेजिस्टर */
#घोषणा IPA_REG_AGGR_FORCE_CLOSE_OFFSET			0x000001ec

/* The next रेजिस्टर is not present क्रम IPA v4.5+ */
#घोषणा IPA_REG_COUNTER_CFG_OFFSET			0x000001f0
/* The next field is not present क्रम IPA v3.5+ */
#घोषणा EOT_COAL_GRANULARITY			GENMASK(3, 0)
#घोषणा AGGR_GRANULARITY_FMASK			GENMASK(8, 4)

/* The next रेजिस्टर is present क्रम IPA v3.5+ */
#घोषणा IPA_REG_TX_CFG_OFFSET				0x000001fc
/* The next three fields are not present क्रम IPA v4.0+ */
#घोषणा TX0_PREFETCH_DISABLE_FMASK		GENMASK(0, 0)
#घोषणा TX1_PREFETCH_DISABLE_FMASK		GENMASK(1, 1)
#घोषणा PREFETCH_ALMOST_EMPTY_SIZE_FMASK	GENMASK(4, 2)
/* The next six fields are present क्रम IPA v4.0+ */
#घोषणा PREFETCH_ALMOST_EMPTY_SIZE_TX0_FMASK	GENMASK(5, 2)
#घोषणा DMAW_SCND_OUTSD_PRED_THRESHOLD_FMASK	GENMASK(9, 6)
#घोषणा DMAW_SCND_OUTSD_PRED_EN_FMASK		GENMASK(10, 10)
#घोषणा DMAW_MAX_BEATS_256_DIS_FMASK		GENMASK(11, 11)
#घोषणा PA_MASK_EN_FMASK			GENMASK(12, 12)
#घोषणा PREFETCH_ALMOST_EMPTY_SIZE_TX1_FMASK	GENMASK(16, 13)
/* The next field is present क्रम IPA v4.5+ */
#घोषणा DUAL_TX_ENABLE_FMASK			GENMASK(17, 17)
/* The next field is present क्रम IPA v4.2+, but not IPA v4.5 */
#घोषणा SSPND_PA_NO_START_STATE_FMASK		GENMASK(18, 18)
/* The next field is present क्रम IPA v4.2 only */
#घोषणा SSPND_PA_NO_BQ_STATE_FMASK		GENMASK(19, 19)

/* The next रेजिस्टर is present क्रम IPA v3.5+ */
#घोषणा IPA_REG_FLAVOR_0_OFFSET				0x00000210
#घोषणा IPA_MAX_PIPES_FMASK			GENMASK(3, 0)
#घोषणा IPA_MAX_CONS_PIPES_FMASK		GENMASK(12, 8)
#घोषणा IPA_MAX_PROD_PIPES_FMASK		GENMASK(20, 16)
#घोषणा IPA_PROD_LOWEST_FMASK			GENMASK(27, 24)

/* The next रेजिस्टर is present क्रम IPA v3.5+ */
अटल अंतरभूत u32 ipa_reg_idle_indication_cfg_offset(क्रमागत ipa_version version)
अणु
	अगर (version >= IPA_VERSION_4_2)
		वापस 0x00000240;

	वापस 0x00000220;
पूर्ण

#घोषणा ENTER_IDLE_DEBOUNCE_THRESH_FMASK	GENMASK(15, 0)
#घोषणा CONST_NON_IDLE_ENABLE_FMASK		GENMASK(16, 16)

/* The next रेजिस्टर is present क्रम IPA v4.5+ */
#घोषणा IPA_REG_QTIME_TIMESTAMP_CFG_OFFSET		0x0000024c
#घोषणा DPL_TIMESTAMP_LSB_FMASK			GENMASK(4, 0)
#घोषणा DPL_TIMESTAMP_SEL_FMASK			GENMASK(7, 7)
#घोषणा TAG_TIMESTAMP_LSB_FMASK			GENMASK(12, 8)
#घोषणा NAT_TIMESTAMP_LSB_FMASK			GENMASK(20, 16)

/* The next रेजिस्टर is present क्रम IPA v4.5+ */
#घोषणा IPA_REG_TIMERS_XO_CLK_DIV_CFG_OFFSET		0x00000250
#घोषणा DIV_VALUE_FMASK				GENMASK(8, 0)
#घोषणा DIV_ENABLE_FMASK			GENMASK(31, 31)

/* The next रेजिस्टर is present क्रम IPA v4.5+ */
#घोषणा IPA_REG_TIMERS_PULSE_GRAN_CFG_OFFSET		0x00000254
#घोषणा GRAN_0_FMASK				GENMASK(2, 0)
#घोषणा GRAN_1_FMASK				GENMASK(5, 3)
#घोषणा GRAN_2_FMASK				GENMASK(8, 6)
/* Values क्रम GRAN_x fields of TIMERS_PULSE_GRAN_CFG */
क्रमागत ipa_pulse_gran अणु
	IPA_GRAN_10_US				= 0x0,
	IPA_GRAN_20_US				= 0x1,
	IPA_GRAN_50_US				= 0x2,
	IPA_GRAN_100_US				= 0x3,
	IPA_GRAN_1_MS				= 0x4,
	IPA_GRAN_10_MS				= 0x5,
	IPA_GRAN_100_MS				= 0x6,
	IPA_GRAN_655350_US			= 0x7,
पूर्ण;

/* Not all of the following are present (depends on IPA version) */
#घोषणा IPA_REG_SRC_RSRC_GRP_01_RSRC_TYPE_N_OFFSET(rt) \
					(0x00000400 + 0x0020 * (rt))
#घोषणा IPA_REG_SRC_RSRC_GRP_23_RSRC_TYPE_N_OFFSET(rt) \
					(0x00000404 + 0x0020 * (rt))
#घोषणा IPA_REG_SRC_RSRC_GRP_45_RSRC_TYPE_N_OFFSET(rt) \
					(0x00000408 + 0x0020 * (rt))
#घोषणा IPA_REG_SRC_RSRC_GRP_67_RSRC_TYPE_N_OFFSET(rt) \
					(0x0000040c + 0x0020 * (rt))
#घोषणा IPA_REG_DST_RSRC_GRP_01_RSRC_TYPE_N_OFFSET(rt) \
					(0x00000500 + 0x0020 * (rt))
#घोषणा IPA_REG_DST_RSRC_GRP_23_RSRC_TYPE_N_OFFSET(rt) \
					(0x00000504 + 0x0020 * (rt))
#घोषणा IPA_REG_DST_RSRC_GRP_45_RSRC_TYPE_N_OFFSET(rt) \
					(0x00000508 + 0x0020 * (rt))
#घोषणा IPA_REG_DST_RSRC_GRP_67_RSRC_TYPE_N_OFFSET(rt) \
					(0x0000050c + 0x0020 * (rt))
/* The next four fields are used क्रम all resource group रेजिस्टरs */
#घोषणा X_MIN_LIM_FMASK				GENMASK(5, 0)
#घोषणा X_MAX_LIM_FMASK				GENMASK(13, 8)
/* The next two fields are not always present (अगर resource count is odd) */
#घोषणा Y_MIN_LIM_FMASK				GENMASK(21, 16)
#घोषणा Y_MAX_LIM_FMASK				GENMASK(29, 24)

#घोषणा IPA_REG_ENDP_INIT_CTRL_N_OFFSET(ep) \
					(0x00000800 + 0x0070 * (ep))
/* Valid only क्रम RX (IPA producer) endpoपूर्णांकs (करो not use क्रम IPA v4.0+) */
#घोषणा ENDP_SUSPEND_FMASK			GENMASK(0, 0)
/* Valid only क्रम TX (IPA consumer) endpoपूर्णांकs */
#घोषणा ENDP_DELAY_FMASK			GENMASK(1, 1)

#घोषणा IPA_REG_ENDP_INIT_CFG_N_OFFSET(ep) \
					(0x00000808 + 0x0070 * (ep))
#घोषणा FRAG_OFFLOAD_EN_FMASK			GENMASK(0, 0)
#घोषणा CS_OFFLOAD_EN_FMASK			GENMASK(2, 1)
#घोषणा CS_METADATA_HDR_OFFSET_FMASK		GENMASK(6, 3)
#घोषणा CS_GEN_QMB_MASTER_SEL_FMASK		GENMASK(8, 8)

/** क्रमागत ipa_cs_offload_en - ENDP_INIT_CFG रेजिस्टर CS_OFFLOAD_EN field value */
क्रमागत ipa_cs_offload_en अणु
	IPA_CS_OFFLOAD_NONE		= 0x0,
	IPA_CS_OFFLOAD_UL		= 0x1,	/* Beक्रमe IPA v4.5 (TX) */
	IPA_CS_OFFLOAD_DL		= 0x2,	/* Beक्रमe IPA v4.5 (RX) */
पूर्ण;

/* Valid only क्रम TX (IPA consumer) endpoपूर्णांकs */
#घोषणा IPA_REG_ENDP_INIT_NAT_N_OFFSET(ep) \
					(0x0000080c + 0x0070 * (ep))
#घोषणा NAT_EN_FMASK				GENMASK(1, 0)

/** क्रमागत ipa_nat_en - ENDP_INIT_NAT रेजिस्टर NAT_EN field value */
क्रमागत ipa_nat_en अणु
	IPA_NAT_BYPASS			= 0x0,
	IPA_NAT_SRC			= 0x1,
	IPA_NAT_DST			= 0x2,
पूर्ण;

#घोषणा IPA_REG_ENDP_INIT_HDR_N_OFFSET(ep) \
					(0x00000810 + 0x0070 * (ep))
#घोषणा HDR_LEN_FMASK				GENMASK(5, 0)
#घोषणा HDR_OFST_METADATA_VALID_FMASK		GENMASK(6, 6)
#घोषणा HDR_OFST_METADATA_FMASK			GENMASK(12, 7)
#घोषणा HDR_ADDITIONAL_CONST_LEN_FMASK		GENMASK(18, 13)
#घोषणा HDR_OFST_PKT_SIZE_VALID_FMASK		GENMASK(19, 19)
#घोषणा HDR_OFST_PKT_SIZE_FMASK			GENMASK(25, 20)
/* The next field is not present क्रम IPA v4.9+ */
#घोषणा HDR_A5_MUX_FMASK			GENMASK(26, 26)
#घोषणा HDR_LEN_INC_DEAGG_HDR_FMASK		GENMASK(27, 27)
/* The next field is not present क्रम IPA v4.5+ */
#घोषणा HDR_METADATA_REG_VALID_FMASK		GENMASK(28, 28)
/* The next two fields are present क्रम IPA v4.5+ */
#घोषणा HDR_LEN_MSB_FMASK			GENMASK(29, 28)
#घोषणा HDR_OFST_METADATA_MSB_FMASK		GENMASK(31, 30)

/* Encoded value क्रम ENDP_INIT_HDR रेजिस्टर HDR_LEN* field(s) */
अटल अंतरभूत u32 ipa_header_size_encoded(क्रमागत ipa_version version,
					  u32 header_size)
अणु
	u32 size = header_size & field_mask(HDR_LEN_FMASK);
	u32 val;

	val = u32_encode_bits(size, HDR_LEN_FMASK);
	अगर (version < IPA_VERSION_4_5) अणु
		/* ipa_निश्चित(header_size == size); */
		वापस val;
	पूर्ण

	/* IPA v4.5 adds a few more most-signअगरicant bits */
	size = header_size >> hweight32(HDR_LEN_FMASK);
	val |= u32_encode_bits(size, HDR_LEN_MSB_FMASK);

	वापस val;
पूर्ण

/* Encoded value क्रम ENDP_INIT_HDR रेजिस्टर OFST_METADATA* field(s) */
अटल अंतरभूत u32 ipa_metadata_offset_encoded(क्रमागत ipa_version version,
					      u32 offset)
अणु
	u32 off = offset & field_mask(HDR_OFST_METADATA_FMASK);
	u32 val;

	val = u32_encode_bits(off, HDR_OFST_METADATA_FMASK);
	अगर (version < IPA_VERSION_4_5) अणु
		/* ipa_निश्चित(offset == off); */
		वापस val;
	पूर्ण

	/* IPA v4.5 adds a few more most-signअगरicant bits */
	off = offset >> hweight32(HDR_OFST_METADATA_FMASK);
	val |= u32_encode_bits(off, HDR_OFST_METADATA_MSB_FMASK);

	वापस val;
पूर्ण

#घोषणा IPA_REG_ENDP_INIT_HDR_EXT_N_OFFSET(ep) \
					(0x00000814 + 0x0070 * (ep))
#घोषणा HDR_ENDIANNESS_FMASK			GENMASK(0, 0)
#घोषणा HDR_TOTAL_LEN_OR_PAD_VALID_FMASK	GENMASK(1, 1)
#घोषणा HDR_TOTAL_LEN_OR_PAD_FMASK		GENMASK(2, 2)
#घोषणा HDR_PAYLOAD_LEN_INC_PADDING_FMASK	GENMASK(3, 3)
#घोषणा HDR_TOTAL_LEN_OR_PAD_OFFSET_FMASK	GENMASK(9, 4)
#घोषणा HDR_PAD_TO_ALIGNMENT_FMASK		GENMASK(13, 10)
/* The next three fields are present क्रम IPA v4.5+ */
#घोषणा HDR_TOTAL_LEN_OR_PAD_OFFSET_MSB_FMASK	GENMASK(17, 16)
#घोषणा HDR_OFST_PKT_SIZE_MSB_FMASK		GENMASK(19, 18)
#घोषणा HDR_ADDITIONAL_CONST_LEN_MSB_FMASK	GENMASK(21, 20)

/* Valid only क्रम RX (IPA producer) endpoपूर्णांकs */
#घोषणा IPA_REG_ENDP_INIT_HDR_METADATA_MASK_N_OFFSET(rxep) \
					(0x00000818 + 0x0070 * (rxep))

/* Valid only क्रम TX (IPA consumer) endpoपूर्णांकs */
#घोषणा IPA_REG_ENDP_INIT_MODE_N_OFFSET(txep) \
					(0x00000820 + 0x0070 * (txep))
#घोषणा MODE_FMASK				GENMASK(2, 0)
/* The next field is present क्रम IPA v4.5+ */
#घोषणा DCPH_ENABLE_FMASK			GENMASK(3, 3)
#घोषणा DEST_PIPE_INDEX_FMASK			GENMASK(8, 4)
#घोषणा BYTE_THRESHOLD_FMASK			GENMASK(27, 12)
#घोषणा PIPE_REPLICATION_EN_FMASK		GENMASK(28, 28)
#घोषणा PAD_EN_FMASK				GENMASK(29, 29)
/* The next field is not present क्रम IPA v4.5+ */
#घोषणा HDR_FTCH_DISABLE_FMASK			GENMASK(30, 30)
/* The next field is present क्रम IPA v4.9+ */
#घोषणा DRBIP_ACL_ENABLE			GENMASK(30, 30)

/** क्रमागत ipa_mode - ENDP_INIT_MODE रेजिस्टर MODE field value */
क्रमागत ipa_mode अणु
	IPA_BASIC			= 0x0,
	IPA_ENABLE_FRAMING_HDLC		= 0x1,
	IPA_ENABLE_DEFRAMING_HDLC	= 0x2,
	IPA_DMA				= 0x3,
पूर्ण;

#घोषणा IPA_REG_ENDP_INIT_AGGR_N_OFFSET(ep) \
					(0x00000824 +  0x0070 * (ep))
#घोषणा AGGR_EN_FMASK				GENMASK(1, 0)
#घोषणा AGGR_TYPE_FMASK				GENMASK(4, 2)

/* The legacy value is used क्रम IPA hardware beक्रमe IPA v4.5 */
अटल अंतरभूत u32 aggr_byte_limit_fmask(bool legacy)
अणु
	वापस legacy ? GENMASK(9, 5) : GENMASK(10, 5);
पूर्ण

/* The legacy value is used क्रम IPA hardware beक्रमe IPA v4.5 */
अटल अंतरभूत u32 aggr_समय_limit_fmask(bool legacy)
अणु
	वापस legacy ? GENMASK(14, 10) : GENMASK(16, 12);
पूर्ण

/* The legacy value is used क्रम IPA hardware beक्रमe IPA v4.5 */
अटल अंतरभूत u32 aggr_pkt_limit_fmask(bool legacy)
अणु
	वापस legacy ? GENMASK(20, 15) : GENMASK(22, 17);
पूर्ण

/* The legacy value is used क्रम IPA hardware beक्रमe IPA v4.5 */
अटल अंतरभूत u32 aggr_sw_eof_active_fmask(bool legacy)
अणु
	वापस legacy ? GENMASK(21, 21) : GENMASK(23, 23);
पूर्ण

/* The legacy value is used क्रम IPA hardware beक्रमe IPA v4.5 */
अटल अंतरभूत u32 aggr_क्रमce_बंद_fmask(bool legacy)
अणु
	वापस legacy ? GENMASK(22, 22) : GENMASK(24, 24);
पूर्ण

/* The legacy value is used क्रम IPA hardware beक्रमe IPA v4.5 */
अटल अंतरभूत u32 aggr_hard_byte_limit_enable_fmask(bool legacy)
अणु
	वापस legacy ? GENMASK(24, 24) : GENMASK(26, 26);
पूर्ण

/* The next field is present क्रम IPA v4.5+ */
#घोषणा AGGR_GRAN_SEL_FMASK			GENMASK(27, 27)

/** क्रमागत ipa_aggr_en - ENDP_INIT_AGGR रेजिस्टर AGGR_EN field value */
क्रमागत ipa_aggr_en अणु
	IPA_BYPASS_AGGR			= 0x0,	/* (TX, RX) */
	IPA_ENABLE_AGGR			= 0x1,	/* (RX) */
	IPA_ENABLE_DEAGGR		= 0x2,	/* (TX) */
पूर्ण;

/** क्रमागत ipa_aggr_type - ENDP_INIT_AGGR रेजिस्टर AGGR_TYPE field value */
क्रमागत ipa_aggr_type अणु
	IPA_MBIM_16			= 0x0,
	IPA_HDLC			= 0x1,
	IPA_TLP				= 0x2,
	IPA_RNDIS			= 0x3,
	IPA_GENERIC			= 0x4,
	IPA_COALESCE			= 0x5,
	IPA_QCMAP			= 0x6,
पूर्ण;

/* Valid only क्रम RX (IPA producer) endpoपूर्णांकs */
#घोषणा IPA_REG_ENDP_INIT_HOL_BLOCK_EN_N_OFFSET(rxep) \
					(0x0000082c +  0x0070 * (rxep))
#घोषणा HOL_BLOCK_EN_FMASK			GENMASK(0, 0)

/* Valid only क्रम RX (IPA producer) endpoपूर्णांकs */
#घोषणा IPA_REG_ENDP_INIT_HOL_BLOCK_TIMER_N_OFFSET(rxep) \
					(0x00000830 +  0x0070 * (rxep))
/* The next two fields are present क्रम IPA v4.2 only */
#घोषणा BASE_VALUE_FMASK			GENMASK(4, 0)
#घोषणा SCALE_FMASK				GENMASK(12, 8)
/* The next two fields are present क्रम IPA v4.5 */
#घोषणा TIME_LIMIT_FMASK			GENMASK(4, 0)
#घोषणा GRAN_SEL_FMASK				GENMASK(8, 8)

/* Valid only क्रम TX (IPA consumer) endpoपूर्णांकs */
#घोषणा IPA_REG_ENDP_INIT_DEAGGR_N_OFFSET(txep) \
					(0x00000834 + 0x0070 * (txep))
#घोषणा DEAGGR_HDR_LEN_FMASK			GENMASK(5, 0)
#घोषणा SYSPIPE_ERR_DETECTION_FMASK		GENMASK(6, 6)
#घोषणा PACKET_OFFSET_VALID_FMASK		GENMASK(7, 7)
#घोषणा PACKET_OFFSET_LOCATION_FMASK		GENMASK(13, 8)
#घोषणा IGNORE_MIN_PKT_ERR_FMASK		GENMASK(14, 14)
#घोषणा MAX_PACKET_LEN_FMASK			GENMASK(31, 16)

#घोषणा IPA_REG_ENDP_INIT_RSRC_GRP_N_OFFSET(ep) \
					(0x00000838 + 0x0070 * (ep))
/* Encoded value क्रम ENDP_INIT_RSRC_GRP रेजिस्टर RSRC_GRP field */
अटल अंतरभूत u32 rsrc_grp_encoded(क्रमागत ipa_version version, u32 rsrc_grp)
अणु
	अगर (version < IPA_VERSION_3_5 || version == IPA_VERSION_4_5)
		वापस u32_encode_bits(rsrc_grp, GENMASK(2, 0));

	अगर (version == IPA_VERSION_4_2 || version == IPA_VERSION_4_7)
		वापस u32_encode_bits(rsrc_grp, GENMASK(0, 0));

	वापस u32_encode_bits(rsrc_grp, GENMASK(1, 0));
पूर्ण

/* Valid only क्रम TX (IPA consumer) endpoपूर्णांकs */
#घोषणा IPA_REG_ENDP_INIT_SEQ_N_OFFSET(txep) \
					(0x0000083c + 0x0070 * (txep))
#घोषणा SEQ_TYPE_FMASK				GENMASK(7, 0)
#घोषणा SEQ_REP_TYPE_FMASK			GENMASK(15, 8)

/**
 * क्रमागत ipa_seq_type - HPS and DPS sequencer type
 * @IPA_SEQ_DMA:		 Perक्रमm DMA only
 * @IPA_SEQ_1_PASS:		 One pass through the pipeline
 * @IPA_SEQ_2_PASS_SKIP_LAST_UC: Two passes, skip the microcprocessor
 * @IPA_SEQ_1_PASS_SKIP_LAST_UC: One pass, skip the microcprocessor
 * @IPA_SEQ_2_PASS:		 Two passes through the pipeline
 * @IPA_SEQ_3_PASS_SKIP_LAST_UC: Three passes, skip the microcprocessor
 * @IPA_SEQ_DECIPHER:		 Optional deciphering step (combined)
 *
 * The low-order byte of the sequencer type रेजिस्टर defines the number of
 * passes a packet takes through the IPA pipeline.  The last pass through can
 * optionally skip the microprocessor.  Deciphering is optional क्रम all types;
 * अगर enabled, an additional mask (two bits) is added to the type value.
 *
 * Note: not all combinations of ipa_seq_type and ipa_seq_rep_type are
 * supported (or meaningful).
 */
क्रमागत ipa_seq_type अणु
	IPA_SEQ_DMA				= 0x00,
	IPA_SEQ_1_PASS				= 0x02,
	IPA_SEQ_2_PASS_SKIP_LAST_UC		= 0x04,
	IPA_SEQ_1_PASS_SKIP_LAST_UC		= 0x06,
	IPA_SEQ_2_PASS				= 0x0a,
	IPA_SEQ_3_PASS_SKIP_LAST_UC		= 0x0c,
	/* The next value can be ORed with the above */
	IPA_SEQ_DECIPHER			= 0x11,
पूर्ण;

/**
 * क्रमागत ipa_seq_rep_type - replicated packet sequencer type
 * @IPA_SEQ_REP_DMA_PARSER:	DMA parser क्रम replicated packets
 *
 * This goes in the second byte of the endpoपूर्णांक sequencer type रेजिस्टर.
 *
 * Note: not all combinations of ipa_seq_type and ipa_seq_rep_type are
 * supported (or meaningful).
 */
क्रमागत ipa_seq_rep_type अणु
	IPA_SEQ_REP_DMA_PARSER			= 0x08,
पूर्ण;

#घोषणा IPA_REG_ENDP_STATUS_N_OFFSET(ep) \
					(0x00000840 + 0x0070 * (ep))
#घोषणा STATUS_EN_FMASK				GENMASK(0, 0)
#घोषणा STATUS_ENDP_FMASK			GENMASK(5, 1)
/* The next field is not present क्रम IPA v4.5+ */
#घोषणा STATUS_LOCATION_FMASK			GENMASK(8, 8)
/* The next field is present क्रम IPA v4.0+ */
#घोषणा STATUS_PKT_SUPPRESS_FMASK		GENMASK(9, 9)

/* The next रेजिस्टर is not present क्रम IPA v4.2 (which no hashing support) */
#घोषणा IPA_REG_ENDP_FILTER_ROUTER_HSH_CFG_N_OFFSET(er) \
					(0x0000085c + 0x0070 * (er))
#घोषणा FILTER_HASH_MSK_SRC_ID_FMASK		GENMASK(0, 0)
#घोषणा FILTER_HASH_MSK_SRC_IP_FMASK		GENMASK(1, 1)
#घोषणा FILTER_HASH_MSK_DST_IP_FMASK		GENMASK(2, 2)
#घोषणा FILTER_HASH_MSK_SRC_PORT_FMASK		GENMASK(3, 3)
#घोषणा FILTER_HASH_MSK_DST_PORT_FMASK		GENMASK(4, 4)
#घोषणा FILTER_HASH_MSK_PROTOCOL_FMASK		GENMASK(5, 5)
#घोषणा FILTER_HASH_MSK_METADATA_FMASK		GENMASK(6, 6)
#घोषणा IPA_REG_ENDP_FILTER_HASH_MSK_ALL	GENMASK(6, 0)

#घोषणा ROUTER_HASH_MSK_SRC_ID_FMASK		GENMASK(16, 16)
#घोषणा ROUTER_HASH_MSK_SRC_IP_FMASK		GENMASK(17, 17)
#घोषणा ROUTER_HASH_MSK_DST_IP_FMASK		GENMASK(18, 18)
#घोषणा ROUTER_HASH_MSK_SRC_PORT_FMASK		GENMASK(19, 19)
#घोषणा ROUTER_HASH_MSK_DST_PORT_FMASK		GENMASK(20, 20)
#घोषणा ROUTER_HASH_MSK_PROTOCOL_FMASK		GENMASK(21, 21)
#घोषणा ROUTER_HASH_MSK_METADATA_FMASK		GENMASK(22, 22)
#घोषणा IPA_REG_ENDP_ROUTER_HASH_MSK_ALL	GENMASK(22, 16)

अटल अंतरभूत u32 ipa_reg_irq_stts_ee_n_offset(क्रमागत ipa_version version,
					       u32 ee)
अणु
	अगर (version < IPA_VERSION_4_9)
		वापस 0x00003008 + 0x1000 * ee;

	वापस 0x00004008 + 0x1000 * ee;
पूर्ण

अटल अंतरभूत u32 ipa_reg_irq_stts_offset(क्रमागत ipa_version version)
अणु
	वापस ipa_reg_irq_stts_ee_n_offset(version, GSI_EE_AP);
पूर्ण

अटल अंतरभूत u32 ipa_reg_irq_en_ee_n_offset(क्रमागत ipa_version version, u32 ee)
अणु
	अगर (version < IPA_VERSION_4_9)
		वापस 0x0000300c + 0x1000 * ee;

	वापस 0x0000400c + 0x1000 * ee;
पूर्ण

अटल अंतरभूत u32 ipa_reg_irq_en_offset(क्रमागत ipa_version version)
अणु
	वापस ipa_reg_irq_en_ee_n_offset(version, GSI_EE_AP);
पूर्ण

अटल अंतरभूत u32 ipa_reg_irq_clr_ee_n_offset(क्रमागत ipa_version version, u32 ee)
अणु
	अगर (version < IPA_VERSION_4_9)
		वापस 0x00003010 + 0x1000 * ee;

	वापस 0x00004010 + 0x1000 * ee;
पूर्ण

अटल अंतरभूत u32 ipa_reg_irq_clr_offset(क्रमागत ipa_version version)
अणु
	वापस ipa_reg_irq_clr_ee_n_offset(version, GSI_EE_AP);
पूर्ण

/**
 * क्रमागत ipa_irq_id - Bit positions representing type of IPA IRQ
 * @IPA_IRQ_UC_0:	Microcontroller event पूर्णांकerrupt
 * @IPA_IRQ_UC_1:	Microcontroller response पूर्णांकerrupt
 * @IPA_IRQ_TX_SUSPEND:	Data पढ़ोy पूर्णांकerrupt
 * @IPA_IRQ_COUNT:	Number of IRQ ids (must be last)
 *
 * IRQ types not described above are not currently used.
 *
 * @IPA_IRQ_BAD_SNOC_ACCESS:		(Not currently used)
 * @IPA_IRQ_EOT_COAL:			(Not currently used)
 * @IPA_IRQ_UC_2:			(Not currently used)
 * @IPA_IRQ_UC_3:			(Not currently used)
 * @IPA_IRQ_UC_IN_Q_NOT_EMPTY:		(Not currently used)
 * @IPA_IRQ_UC_RX_CMD_Q_NOT_FULL:	(Not currently used)
 * @IPA_IRQ_PROC_UC_ACK_Q_NOT_EMPTY:	(Not currently used)
 * @IPA_IRQ_RX_ERR:			(Not currently used)
 * @IPA_IRQ_DEAGGR_ERR:			(Not currently used)
 * @IPA_IRQ_TX_ERR:			(Not currently used)
 * @IPA_IRQ_STEP_MODE:			(Not currently used)
 * @IPA_IRQ_PROC_ERR:			(Not currently used)
 * @IPA_IRQ_TX_HOLB_DROP:		(Not currently used)
 * @IPA_IRQ_BAM_GSI_IDLE:		(Not currently used)
 * @IPA_IRQ_PIPE_YELLOW_BELOW:		(Not currently used)
 * @IPA_IRQ_PIPE_RED_BELOW:		(Not currently used)
 * @IPA_IRQ_PIPE_YELLOW_ABOVE:		(Not currently used)
 * @IPA_IRQ_PIPE_RED_ABOVE:		(Not currently used)
 * @IPA_IRQ_UCP:			(Not currently used)
 * @IPA_IRQ_DCMP:			(Not currently used)
 * @IPA_IRQ_GSI_EE:			(Not currently used)
 * @IPA_IRQ_GSI_IPA_IF_TLV_RCVD:	(Not currently used)
 * @IPA_IRQ_GSI_UC:			(Not currently used)
 * @IPA_IRQ_TLV_LEN_MIN_DSM:		(Not currently used)
 * @IPA_IRQ_DRBIP_PKT_EXCEED_MAX_SIZE_EN: (Not currently used)
 * @IPA_IRQ_DRBIP_DATA_SCTR_CFG_ERROR_EN: (Not currently used)
 * @IPA_IRQ_DRBIP_IMM_CMD_NO_FLSH_HZRD_EN: (Not currently used)
 */
क्रमागत ipa_irq_id अणु
	IPA_IRQ_BAD_SNOC_ACCESS			= 0x0,
	/* The next bit is not present क्रम IPA v3.5+ */
	IPA_IRQ_EOT_COAL			= 0x1,
	IPA_IRQ_UC_0				= 0x2,
	IPA_IRQ_UC_1				= 0x3,
	IPA_IRQ_UC_2				= 0x4,
	IPA_IRQ_UC_3				= 0x5,
	IPA_IRQ_UC_IN_Q_NOT_EMPTY		= 0x6,
	IPA_IRQ_UC_RX_CMD_Q_NOT_FULL		= 0x7,
	IPA_IRQ_PROC_UC_ACK_Q_NOT_EMPTY		= 0x8,
	IPA_IRQ_RX_ERR				= 0x9,
	IPA_IRQ_DEAGGR_ERR			= 0xa,
	IPA_IRQ_TX_ERR				= 0xb,
	IPA_IRQ_STEP_MODE			= 0xc,
	IPA_IRQ_PROC_ERR			= 0xd,
	IPA_IRQ_TX_SUSPEND			= 0xe,
	IPA_IRQ_TX_HOLB_DROP			= 0xf,
	IPA_IRQ_BAM_GSI_IDLE			= 0x10,
	IPA_IRQ_PIPE_YELLOW_BELOW		= 0x11,
	IPA_IRQ_PIPE_RED_BELOW			= 0x12,
	IPA_IRQ_PIPE_YELLOW_ABOVE		= 0x13,
	IPA_IRQ_PIPE_RED_ABOVE			= 0x14,
	IPA_IRQ_UCP				= 0x15,
	/* The next bit is not present क्रम IPA v4.5+ */
	IPA_IRQ_DCMP				= 0x16,
	IPA_IRQ_GSI_EE				= 0x17,
	IPA_IRQ_GSI_IPA_IF_TLV_RCVD		= 0x18,
	IPA_IRQ_GSI_UC				= 0x19,
	/* The next bit is present क्रम IPA v4.5+ */
	IPA_IRQ_TLV_LEN_MIN_DSM			= 0x1a,
	/* The next three bits are present क्रम IPA v4.9+ */
	IPA_IRQ_DRBIP_PKT_EXCEED_MAX_SIZE_EN	= 0x1b,
	IPA_IRQ_DRBIP_DATA_SCTR_CFG_ERROR_EN	= 0x1c,
	IPA_IRQ_DRBIP_IMM_CMD_NO_FLSH_HZRD_EN	= 0x1d,
	IPA_IRQ_COUNT,				/* Last; not an id */
पूर्ण;

अटल अंतरभूत u32 ipa_reg_irq_uc_ee_n_offset(क्रमागत ipa_version version, u32 ee)
अणु
	अगर (version < IPA_VERSION_4_9)
		वापस 0x0000301c + 0x1000 * ee;

	वापस 0x0000401c + 0x1000 * ee;
पूर्ण

अटल अंतरभूत u32 ipa_reg_irq_uc_offset(क्रमागत ipa_version version)
अणु
	वापस ipa_reg_irq_uc_ee_n_offset(version, GSI_EE_AP);
पूर्ण

#घोषणा UC_INTR_FMASK				GENMASK(0, 0)

/* ipa->available defines the valid bits in the SUSPEND_INFO रेजिस्टर */
अटल अंतरभूत u32
ipa_reg_irq_suspend_info_ee_n_offset(क्रमागत ipa_version version, u32 ee)
अणु
	अगर (version == IPA_VERSION_3_0)
		वापस 0x00003098 + 0x1000 * ee;

	अगर (version < IPA_VERSION_4_9)
		वापस 0x00003030 + 0x1000 * ee;

	वापस 0x00004030 + 0x1000 * ee;
पूर्ण

अटल अंतरभूत u32
ipa_reg_irq_suspend_info_offset(क्रमागत ipa_version version)
अणु
	वापस ipa_reg_irq_suspend_info_ee_n_offset(version, GSI_EE_AP);
पूर्ण

/* ipa->available defines the valid bits in the SUSPEND_EN रेजिस्टर */
अटल अंतरभूत u32
ipa_reg_irq_suspend_en_ee_n_offset(क्रमागत ipa_version version, u32 ee)
अणु
	/* निश्चित(version != IPA_VERSION_3_0); */

	अगर (version < IPA_VERSION_4_9)
		वापस 0x00003034 + 0x1000 * ee;

	वापस 0x00004034 + 0x1000 * ee;
पूर्ण

अटल अंतरभूत u32
ipa_reg_irq_suspend_en_offset(क्रमागत ipa_version version)
अणु
	वापस ipa_reg_irq_suspend_en_ee_n_offset(version, GSI_EE_AP);
पूर्ण

/* ipa->available defines the valid bits in the SUSPEND_CLR रेजिस्टर */
अटल अंतरभूत u32
ipa_reg_irq_suspend_clr_ee_n_offset(क्रमागत ipa_version version, u32 ee)
अणु
	/* निश्चित(version != IPA_VERSION_3_0); */

	अगर (version < IPA_VERSION_4_9)
		वापस 0x00003038 + 0x1000 * ee;

	वापस 0x00004038 + 0x1000 * ee;
पूर्ण

अटल अंतरभूत u32
ipa_reg_irq_suspend_clr_offset(क्रमागत ipa_version version)
अणु
	वापस ipa_reg_irq_suspend_clr_ee_n_offset(version, GSI_EE_AP);
पूर्ण

पूर्णांक ipa_reg_init(काष्ठा ipa *ipa);
व्योम ipa_reg_निकास(काष्ठा ipa *ipa);

#पूर्ण_अगर /* _IPA_REG_H_ */
