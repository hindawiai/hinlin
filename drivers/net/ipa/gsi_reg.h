<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2018-2021 Linaro Ltd.
 */
#अगर_अघोषित _GSI_REG_H_
#घोषणा _GSI_REG_H_

/* === Only "gsi.c" should include this file === */

#समावेश <linux/bits.h>

/**
 * DOC: GSI Registers
 *
 * GSI रेजिस्टरs are located within the "gsi" address space defined by Device
 * Tree.  The offset of each रेजिस्टर within that space is specअगरied by
 * symbols defined below.  The GSI address space is mapped to भव memory
 * space in gsi_init().  All GSI रेजिस्टरs are 32 bits wide.
 *
 * Each रेजिस्टर type is duplicated क्रम a number of instances of something.
 * For example, each GSI channel has its own set of रेजिस्टरs defining its
 * configuration.  The offset to a channel's set of रेजिस्टरs is computed
 * based on a "base" offset plus an additional "stride" amount computed
 * from the channel's ID.  For such रेजिस्टरs, the offset is computed by a
 * function-like macro that takes a parameter used in the computation.
 *
 * The offset of a रेजिस्टर dependent on execution environment is computed
 * by a macro that is supplied a parameter "ee".  The "ee" value is a member
 * of the gsi_ee_id क्रमागतerated type.
 *
 * The offset of a channel रेजिस्टर is computed by a macro that is supplied a
 * parameter "ch".  The "ch" value is a channel id whose maximum value is 30
 * (though the actual limit is hardware-dependent).
 *
 * The offset of an event रेजिस्टर is computed by a macro that is supplied a
 * parameter "ev".  The "ev" value is an event id whose maximum value is 15
 * (though the actual limit is hardware-dependent).
 */

/* GSI EE रेजिस्टरs as a group are shअगरted करोwnward by a fixed स्थिरant amount
 * क्रम IPA versions 4.5 and beyond.  This applies to all GSI रेजिस्टरs we use
 * *except* the ones that disable पूर्णांकer-EE पूर्णांकerrupts क्रम channels and event
 * channels.
 *
 * The "raw" (not adjusted) GSI रेजिस्टर range is mapped, and a poपूर्णांकer to
 * the mapped range is held in gsi->virt_raw.  The पूर्णांकer-EE पूर्णांकerrupt
 * रेजिस्टरs are accessed using that poपूर्णांकer.
 *
 * Most रेजिस्टरs are accessed using gsi->virt, which is a copy of the "raw"
 * poपूर्णांकer, adjusted करोwnward by the fixed amount.
 */
#घोषणा GSI_EE_REG_ADJUST			0x0000d000	/* IPA v4.5+ */

/* The two पूर्णांकer-EE IRQ रेजिस्टर offsets are relative to gsi->virt_raw */
#घोषणा GSI_INTER_EE_SRC_CH_IRQ_MSK_OFFSET \
			GSI_INTER_EE_N_SRC_CH_IRQ_MSK_OFFSET(GSI_EE_AP)
#घोषणा GSI_INTER_EE_N_SRC_CH_IRQ_MSK_OFFSET(ee) \
			(0x0000c020 + 0x1000 * (ee))

#घोषणा GSI_INTER_EE_SRC_EV_CH_IRQ_MSK_OFFSET \
			GSI_INTER_EE_N_SRC_EV_CH_IRQ_MSK_OFFSET(GSI_EE_AP)
#घोषणा GSI_INTER_EE_N_SRC_EV_CH_IRQ_MSK_OFFSET(ee) \
			(0x0000c024 + 0x1000 * (ee))

/* All other रेजिस्टर offsets are relative to gsi->virt */

/** क्रमागत gsi_channel_type - CHTYPE_PROTOCOL field values in CH_C_CNTXT_0 */
क्रमागत gsi_channel_type अणु
	GSI_CHANNEL_TYPE_MHI			= 0x0,
	GSI_CHANNEL_TYPE_XHCI			= 0x1,
	GSI_CHANNEL_TYPE_GPI			= 0x2,
	GSI_CHANNEL_TYPE_XDCI			= 0x3,
	GSI_CHANNEL_TYPE_WDI2			= 0x4,
	GSI_CHANNEL_TYPE_GCI			= 0x5,
	GSI_CHANNEL_TYPE_WDI3			= 0x6,
	GSI_CHANNEL_TYPE_MHIP			= 0x7,
	GSI_CHANNEL_TYPE_AQC			= 0x8,
	GSI_CHANNEL_TYPE_11AD			= 0x9,
पूर्ण;

#घोषणा GSI_CH_C_CNTXT_0_OFFSET(ch) \
		GSI_EE_N_CH_C_CNTXT_0_OFFSET((ch), GSI_EE_AP)
#घोषणा GSI_EE_N_CH_C_CNTXT_0_OFFSET(ch, ee) \
		(0x0001c000 + 0x4000 * (ee) + 0x80 * (ch))
#घोषणा CHTYPE_PROTOCOL_FMASK		GENMASK(2, 0)
#घोषणा CHTYPE_सूची_FMASK		GENMASK(3, 3)
#घोषणा EE_FMASK			GENMASK(7, 4)
#घोषणा CHID_FMASK			GENMASK(12, 8)
/* The next field is present क्रम IPA v4.5 and above */
#घोषणा CHTYPE_PROTOCOL_MSB_FMASK	GENMASK(13, 13)
#घोषणा ERINDEX_FMASK			GENMASK(18, 14)
#घोषणा CHSTATE_FMASK			GENMASK(23, 20)
#घोषणा ELEMENT_SIZE_FMASK		GENMASK(31, 24)

/* Encoded value क्रम CH_C_CNTXT_0 रेजिस्टर channel protocol fields */
अटल अंतरभूत u32
chtype_protocol_encoded(क्रमागत ipa_version version, क्रमागत gsi_channel_type type)
अणु
	u32 val;

	val = u32_encode_bits(type, CHTYPE_PROTOCOL_FMASK);
	अगर (version < IPA_VERSION_4_5)
		वापस val;

	/* Encode upper bit(s) as well */
	type >>= hweight32(CHTYPE_PROTOCOL_FMASK);
	val |= u32_encode_bits(type, CHTYPE_PROTOCOL_MSB_FMASK);

	वापस val;
पूर्ण

#घोषणा GSI_CH_C_CNTXT_1_OFFSET(ch) \
		GSI_EE_N_CH_C_CNTXT_1_OFFSET((ch), GSI_EE_AP)
#घोषणा GSI_EE_N_CH_C_CNTXT_1_OFFSET(ch, ee) \
		(0x0001c004 + 0x4000 * (ee) + 0x80 * (ch))

/* Encoded value क्रम CH_C_CNTXT_1 रेजिस्टर R_LENGTH field */
अटल अंतरभूत u32 r_length_encoded(क्रमागत ipa_version version, u32 length)
अणु
	अगर (version < IPA_VERSION_4_9)
		वापस u32_encode_bits(length, GENMASK(15, 0));
	वापस u32_encode_bits(length, GENMASK(19, 0));
पूर्ण

#घोषणा GSI_CH_C_CNTXT_2_OFFSET(ch) \
		GSI_EE_N_CH_C_CNTXT_2_OFFSET((ch), GSI_EE_AP)
#घोषणा GSI_EE_N_CH_C_CNTXT_2_OFFSET(ch, ee) \
		(0x0001c008 + 0x4000 * (ee) + 0x80 * (ch))

#घोषणा GSI_CH_C_CNTXT_3_OFFSET(ch) \
		GSI_EE_N_CH_C_CNTXT_3_OFFSET((ch), GSI_EE_AP)
#घोषणा GSI_EE_N_CH_C_CNTXT_3_OFFSET(ch, ee) \
		(0x0001c00c + 0x4000 * (ee) + 0x80 * (ch))

#घोषणा GSI_CH_C_QOS_OFFSET(ch) \
		GSI_EE_N_CH_C_QOS_OFFSET((ch), GSI_EE_AP)
#घोषणा GSI_EE_N_CH_C_QOS_OFFSET(ch, ee) \
		(0x0001c05c + 0x4000 * (ee) + 0x80 * (ch))
#घोषणा WRR_WEIGHT_FMASK		GENMASK(3, 0)
#घोषणा MAX_PREFETCH_FMASK		GENMASK(8, 8)
#घोषणा USE_DB_ENG_FMASK		GENMASK(9, 9)
/* The next field is only present क्रम IPA v4.0, v4.1, and v4.2 */
#घोषणा USE_ESCAPE_BUF_ONLY_FMASK	GENMASK(10, 10)
/* The next two fields are present क्रम IPA v4.5 and above */
#घोषणा PREFETCH_MODE_FMASK		GENMASK(13, 10)
#घोषणा EMPTY_LVL_THRSHOLD_FMASK	GENMASK(23, 16)
/* The next field is present क्रम IPA v4.9 and above */
#घोषणा DB_IN_BYTES			GENMASK(24, 24)

/** क्रमागत gsi_prefetch_mode - PREFETCH_MODE field in CH_C_QOS */
क्रमागत gsi_prefetch_mode अणु
	GSI_USE_PREFETCH_BUFS			= 0x0,
	GSI_ESCAPE_BUF_ONLY			= 0x1,
	GSI_SMART_PREFETCH			= 0x2,
	GSI_FREE_PREFETCH			= 0x3,
पूर्ण;

#घोषणा GSI_CH_C_SCRATCH_0_OFFSET(ch) \
		GSI_EE_N_CH_C_SCRATCH_0_OFFSET((ch), GSI_EE_AP)
#घोषणा GSI_EE_N_CH_C_SCRATCH_0_OFFSET(ch, ee) \
		(0x0001c060 + 0x4000 * (ee) + 0x80 * (ch))

#घोषणा GSI_CH_C_SCRATCH_1_OFFSET(ch) \
		GSI_EE_N_CH_C_SCRATCH_1_OFFSET((ch), GSI_EE_AP)
#घोषणा GSI_EE_N_CH_C_SCRATCH_1_OFFSET(ch, ee) \
		(0x0001c064 + 0x4000 * (ee) + 0x80 * (ch))

#घोषणा GSI_CH_C_SCRATCH_2_OFFSET(ch) \
		GSI_EE_N_CH_C_SCRATCH_2_OFFSET((ch), GSI_EE_AP)
#घोषणा GSI_EE_N_CH_C_SCRATCH_2_OFFSET(ch, ee) \
		(0x0001c068 + 0x4000 * (ee) + 0x80 * (ch))

#घोषणा GSI_CH_C_SCRATCH_3_OFFSET(ch) \
		GSI_EE_N_CH_C_SCRATCH_3_OFFSET((ch), GSI_EE_AP)
#घोषणा GSI_EE_N_CH_C_SCRATCH_3_OFFSET(ch, ee) \
		(0x0001c06c + 0x4000 * (ee) + 0x80 * (ch))

#घोषणा GSI_EV_CH_E_CNTXT_0_OFFSET(ev) \
		GSI_EE_N_EV_CH_E_CNTXT_0_OFFSET((ev), GSI_EE_AP)
#घोषणा GSI_EE_N_EV_CH_E_CNTXT_0_OFFSET(ev, ee) \
		(0x0001d000 + 0x4000 * (ee) + 0x80 * (ev))
/* क्रमागत gsi_channel_type defines EV_CHTYPE field values in EV_CH_E_CNTXT_0 */
#घोषणा EV_CHTYPE_FMASK			GENMASK(3, 0)
#घोषणा EV_EE_FMASK			GENMASK(7, 4)
#घोषणा EV_EVCHID_FMASK			GENMASK(15, 8)
#घोषणा EV_INTYPE_FMASK			GENMASK(16, 16)
#घोषणा EV_CHSTATE_FMASK		GENMASK(23, 20)
#घोषणा EV_ELEMENT_SIZE_FMASK		GENMASK(31, 24)

#घोषणा GSI_EV_CH_E_CNTXT_1_OFFSET(ev) \
		GSI_EE_N_EV_CH_E_CNTXT_1_OFFSET((ev), GSI_EE_AP)
#घोषणा GSI_EE_N_EV_CH_E_CNTXT_1_OFFSET(ev, ee) \
		(0x0001d004 + 0x4000 * (ee) + 0x80 * (ev))
/* Encoded value क्रम EV_CH_C_CNTXT_1 रेजिस्टर EV_R_LENGTH field */
अटल अंतरभूत u32 ev_r_length_encoded(क्रमागत ipa_version version, u32 length)
अणु
	अगर (version < IPA_VERSION_4_9)
		वापस u32_encode_bits(length, GENMASK(15, 0));
	वापस u32_encode_bits(length, GENMASK(19, 0));
पूर्ण

#घोषणा GSI_EV_CH_E_CNTXT_2_OFFSET(ev) \
		GSI_EE_N_EV_CH_E_CNTXT_2_OFFSET((ev), GSI_EE_AP)
#घोषणा GSI_EE_N_EV_CH_E_CNTXT_2_OFFSET(ev, ee) \
		(0x0001d008 + 0x4000 * (ee) + 0x80 * (ev))

#घोषणा GSI_EV_CH_E_CNTXT_3_OFFSET(ev) \
		GSI_EE_N_EV_CH_E_CNTXT_3_OFFSET((ev), GSI_EE_AP)
#घोषणा GSI_EE_N_EV_CH_E_CNTXT_3_OFFSET(ev, ee) \
		(0x0001d00c + 0x4000 * (ee) + 0x80 * (ev))

#घोषणा GSI_EV_CH_E_CNTXT_4_OFFSET(ev) \
		GSI_EE_N_EV_CH_E_CNTXT_4_OFFSET((ev), GSI_EE_AP)
#घोषणा GSI_EE_N_EV_CH_E_CNTXT_4_OFFSET(ev, ee) \
		(0x0001d010 + 0x4000 * (ee) + 0x80 * (ev))

#घोषणा GSI_EV_CH_E_CNTXT_8_OFFSET(ev) \
		GSI_EE_N_EV_CH_E_CNTXT_8_OFFSET((ev), GSI_EE_AP)
#घोषणा GSI_EE_N_EV_CH_E_CNTXT_8_OFFSET(ev, ee) \
		(0x0001d020 + 0x4000 * (ee) + 0x80 * (ev))
#घोषणा MODT_FMASK			GENMASK(15, 0)
#घोषणा MODC_FMASK			GENMASK(23, 16)
#घोषणा MOD_CNT_FMASK			GENMASK(31, 24)

#घोषणा GSI_EV_CH_E_CNTXT_9_OFFSET(ev) \
		GSI_EE_N_EV_CH_E_CNTXT_9_OFFSET((ev), GSI_EE_AP)
#घोषणा GSI_EE_N_EV_CH_E_CNTXT_9_OFFSET(ev, ee) \
		(0x0001d024 + 0x4000 * (ee) + 0x80 * (ev))

#घोषणा GSI_EV_CH_E_CNTXT_10_OFFSET(ev) \
		GSI_EE_N_EV_CH_E_CNTXT_10_OFFSET((ev), GSI_EE_AP)
#घोषणा GSI_EE_N_EV_CH_E_CNTXT_10_OFFSET(ev, ee) \
		(0x0001d028 + 0x4000 * (ee) + 0x80 * (ev))

#घोषणा GSI_EV_CH_E_CNTXT_11_OFFSET(ev) \
		GSI_EE_N_EV_CH_E_CNTXT_11_OFFSET((ev), GSI_EE_AP)
#घोषणा GSI_EE_N_EV_CH_E_CNTXT_11_OFFSET(ev, ee) \
		(0x0001d02c + 0x4000 * (ee) + 0x80 * (ev))

#घोषणा GSI_EV_CH_E_CNTXT_12_OFFSET(ev) \
		GSI_EE_N_EV_CH_E_CNTXT_12_OFFSET((ev), GSI_EE_AP)
#घोषणा GSI_EE_N_EV_CH_E_CNTXT_12_OFFSET(ev, ee) \
		(0x0001d030 + 0x4000 * (ee) + 0x80 * (ev))

#घोषणा GSI_EV_CH_E_CNTXT_13_OFFSET(ev) \
		GSI_EE_N_EV_CH_E_CNTXT_13_OFFSET((ev), GSI_EE_AP)
#घोषणा GSI_EE_N_EV_CH_E_CNTXT_13_OFFSET(ev, ee) \
		(0x0001d034 + 0x4000 * (ee) + 0x80 * (ev))

#घोषणा GSI_EV_CH_E_SCRATCH_0_OFFSET(ev) \
		GSI_EE_N_EV_CH_E_SCRATCH_0_OFFSET((ev), GSI_EE_AP)
#घोषणा GSI_EE_N_EV_CH_E_SCRATCH_0_OFFSET(ev, ee) \
		(0x0001d048 + 0x4000 * (ee) + 0x80 * (ev))

#घोषणा GSI_EV_CH_E_SCRATCH_1_OFFSET(ev) \
		GSI_EE_N_EV_CH_E_SCRATCH_1_OFFSET((ev), GSI_EE_AP)
#घोषणा GSI_EE_N_EV_CH_E_SCRATCH_1_OFFSET(ev, ee) \
		(0x0001d04c + 0x4000 * (ee) + 0x80 * (ev))

#घोषणा GSI_CH_C_DOORBELL_0_OFFSET(ch) \
		GSI_EE_N_CH_C_DOORBELL_0_OFFSET((ch), GSI_EE_AP)
#घोषणा GSI_EE_N_CH_C_DOORBELL_0_OFFSET(ch, ee) \
			(0x0001e000 + 0x4000 * (ee) + 0x08 * (ch))

#घोषणा GSI_EV_CH_E_DOORBELL_0_OFFSET(ev) \
			GSI_EE_N_EV_CH_E_DOORBELL_0_OFFSET((ev), GSI_EE_AP)
#घोषणा GSI_EE_N_EV_CH_E_DOORBELL_0_OFFSET(ev, ee) \
			(0x0001e100 + 0x4000 * (ee) + 0x08 * (ev))

#घोषणा GSI_GSI_STATUS_OFFSET \
			GSI_EE_N_GSI_STATUS_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_GSI_STATUS_OFFSET(ee) \
			(0x0001f000 + 0x4000 * (ee))
#घोषणा ENABLED_FMASK			GENMASK(0, 0)

#घोषणा GSI_CH_CMD_OFFSET \
			GSI_EE_N_CH_CMD_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_CH_CMD_OFFSET(ee) \
			(0x0001f008 + 0x4000 * (ee))
#घोषणा CH_CHID_FMASK			GENMASK(7, 0)
#घोषणा CH_OPCODE_FMASK			GENMASK(31, 24)

/** क्रमागत gsi_ch_cmd_opcode - CH_OPCODE field values in CH_CMD */
क्रमागत gsi_ch_cmd_opcode अणु
	GSI_CH_ALLOCATE				= 0x0,
	GSI_CH_START				= 0x1,
	GSI_CH_STOP				= 0x2,
	GSI_CH_RESET				= 0x9,
	GSI_CH_DE_ALLOC				= 0xa,
	GSI_CH_DB_STOP				= 0xb,
पूर्ण;

#घोषणा GSI_EV_CH_CMD_OFFSET \
			GSI_EE_N_EV_CH_CMD_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_EV_CH_CMD_OFFSET(ee) \
			(0x0001f010 + 0x4000 * (ee))
#घोषणा EV_CHID_FMASK			GENMASK(7, 0)
#घोषणा EV_OPCODE_FMASK			GENMASK(31, 24)

/** क्रमागत gsi_evt_cmd_opcode - EV_OPCODE field values in EV_CH_CMD */
क्रमागत gsi_evt_cmd_opcode अणु
	GSI_EVT_ALLOCATE			= 0x0,
	GSI_EVT_RESET				= 0x9,
	GSI_EVT_DE_ALLOC			= 0xa,
पूर्ण;

#घोषणा GSI_GENERIC_CMD_OFFSET \
			GSI_EE_N_GENERIC_CMD_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_GENERIC_CMD_OFFSET(ee) \
			(0x0001f018 + 0x4000 * (ee))
#घोषणा GENERIC_OPCODE_FMASK		GENMASK(4, 0)
#घोषणा GENERIC_CHID_FMASK		GENMASK(9, 5)
#घोषणा GENERIC_EE_FMASK		GENMASK(13, 10)

/** क्रमागत gsi_generic_cmd_opcode - GENERIC_OPCODE field values in GENERIC_CMD */
क्रमागत gsi_generic_cmd_opcode अणु
	GSI_GENERIC_HALT_CHANNEL		= 0x1,
	GSI_GENERIC_ALLOCATE_CHANNEL		= 0x2,
पूर्ण;

/* The next रेजिस्टर is present क्रम IPA v3.5.1 and above */
#घोषणा GSI_GSI_HW_PARAM_2_OFFSET \
			GSI_EE_N_GSI_HW_PARAM_2_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_GSI_HW_PARAM_2_OFFSET(ee) \
			(0x0001f040 + 0x4000 * (ee))
#घोषणा IRAM_SIZE_FMASK			GENMASK(2, 0)
#घोषणा NUM_CH_PER_EE_FMASK		GENMASK(7, 3)
#घोषणा NUM_EV_PER_EE_FMASK		GENMASK(12, 8)
#घोषणा GSI_CH_PEND_TRANSLATE_FMASK	GENMASK(13, 13)
#घोषणा GSI_CH_FULL_LOGIC_FMASK		GENMASK(14, 14)
/* Fields below are present क्रम IPA v4.0 and above */
#घोषणा GSI_USE_SDMA_FMASK		GENMASK(15, 15)
#घोषणा GSI_SDMA_N_INT_FMASK		GENMASK(18, 16)
#घोषणा GSI_SDMA_MAX_BURST_FMASK	GENMASK(26, 19)
#घोषणा GSI_SDMA_N_IOVEC_FMASK		GENMASK(29, 27)
/* Fields below are present क्रम IPA v4.2 and above */
#घोषणा GSI_USE_RD_WR_ENG_FMASK		GENMASK(30, 30)
#घोषणा GSI_USE_INTER_EE_FMASK		GENMASK(31, 31)

/** क्रमागत gsi_iram_size - IRAM_SIZE field values in HW_PARAM_2 */
क्रमागत gsi_iram_size अणु
	IRAM_SIZE_ONE_KB			= 0x0,
	IRAM_SIZE_TWO_KB			= 0x1,
	/* The next two values are available क्रम IPA v4.0 and above */
	IRAM_SIZE_TWO_N_HALF_KB			= 0x2,
	IRAM_SIZE_THREE_KB			= 0x3,
	/* The next two values are available क्रम IPA v4.5 and above */
	IRAM_SIZE_THREE_N_HALF_KB		= 0x4,
	IRAM_SIZE_FOUR_KB			= 0x5,
पूर्ण;

/* IRQ condition क्रम each type is cleared by writing type-specअगरic रेजिस्टर */
#घोषणा GSI_CNTXT_TYPE_IRQ_OFFSET \
			GSI_EE_N_CNTXT_TYPE_IRQ_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_CNTXT_TYPE_IRQ_OFFSET(ee) \
			(0x0001f080 + 0x4000 * (ee))
#घोषणा GSI_CNTXT_TYPE_IRQ_MSK_OFFSET \
			GSI_EE_N_CNTXT_TYPE_IRQ_MSK_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_CNTXT_TYPE_IRQ_MSK_OFFSET(ee) \
			(0x0001f088 + 0x4000 * (ee))

/* Values here are bit positions in the TYPE_IRQ and TYPE_IRQ_MSK रेजिस्टरs */
क्रमागत gsi_irq_type_id अणु
	GSI_CH_CTRL		= 0x0,	/* channel allocation, etc.  */
	GSI_EV_CTRL		= 0x1,	/* event ring allocation, etc. */
	GSI_GLOB_EE		= 0x2,	/* global/general event */
	GSI_IEOB		= 0x3,	/* TRE completion */
	GSI_INTER_EE_CH_CTRL	= 0x4,	/* remote-issued stop/reset (unused) */
	GSI_INTER_EE_EV_CTRL	= 0x5,	/* remote-issued event reset (unused) */
	GSI_GENERAL		= 0x6,	/* general-purpose event */
पूर्ण;

#घोषणा GSI_CNTXT_SRC_CH_IRQ_OFFSET \
			GSI_EE_N_CNTXT_SRC_CH_IRQ_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_CNTXT_SRC_CH_IRQ_OFFSET(ee) \
			(0x0001f090 + 0x4000 * (ee))

#घोषणा GSI_CNTXT_SRC_EV_CH_IRQ_OFFSET \
			GSI_EE_N_CNTXT_SRC_EV_CH_IRQ_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_CNTXT_SRC_EV_CH_IRQ_OFFSET(ee) \
			(0x0001f094 + 0x4000 * (ee))

#घोषणा GSI_CNTXT_SRC_CH_IRQ_MSK_OFFSET \
			GSI_EE_N_CNTXT_SRC_CH_IRQ_MSK_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_CNTXT_SRC_CH_IRQ_MSK_OFFSET(ee) \
			(0x0001f098 + 0x4000 * (ee))

#घोषणा GSI_CNTXT_SRC_EV_CH_IRQ_MSK_OFFSET \
			GSI_EE_N_CNTXT_SRC_EV_CH_IRQ_MSK_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_CNTXT_SRC_EV_CH_IRQ_MSK_OFFSET(ee) \
			(0x0001f09c + 0x4000 * (ee))

#घोषणा GSI_CNTXT_SRC_CH_IRQ_CLR_OFFSET \
			GSI_EE_N_CNTXT_SRC_CH_IRQ_CLR_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_CNTXT_SRC_CH_IRQ_CLR_OFFSET(ee) \
			(0x0001f0a0 + 0x4000 * (ee))

#घोषणा GSI_CNTXT_SRC_EV_CH_IRQ_CLR_OFFSET \
			GSI_EE_N_CNTXT_SRC_EV_CH_IRQ_CLR_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_CNTXT_SRC_EV_CH_IRQ_CLR_OFFSET(ee) \
			(0x0001f0a4 + 0x4000 * (ee))

#घोषणा GSI_CNTXT_SRC_IEOB_IRQ_OFFSET \
			GSI_EE_N_CNTXT_SRC_IEOB_IRQ_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_CNTXT_SRC_IEOB_IRQ_OFFSET(ee) \
			(0x0001f0b0 + 0x4000 * (ee))

#घोषणा GSI_CNTXT_SRC_IEOB_IRQ_MSK_OFFSET \
			GSI_EE_N_CNTXT_SRC_IEOB_IRQ_MSK_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_CNTXT_SRC_IEOB_IRQ_MSK_OFFSET(ee) \
			(0x0001f0b8 + 0x4000 * (ee))

#घोषणा GSI_CNTXT_SRC_IEOB_IRQ_CLR_OFFSET \
			GSI_EE_N_CNTXT_SRC_IEOB_IRQ_CLR_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_CNTXT_SRC_IEOB_IRQ_CLR_OFFSET(ee) \
			(0x0001f0c0 + 0x4000 * (ee))

#घोषणा GSI_CNTXT_GLOB_IRQ_STTS_OFFSET \
			GSI_EE_N_CNTXT_GLOB_IRQ_STTS_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_CNTXT_GLOB_IRQ_STTS_OFFSET(ee) \
			(0x0001f100 + 0x4000 * (ee))
#घोषणा GSI_CNTXT_GLOB_IRQ_EN_OFFSET \
			GSI_EE_N_CNTXT_GLOB_IRQ_EN_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_CNTXT_GLOB_IRQ_EN_OFFSET(ee) \
			(0x0001f108 + 0x4000 * (ee))
#घोषणा GSI_CNTXT_GLOB_IRQ_CLR_OFFSET \
			GSI_EE_N_CNTXT_GLOB_IRQ_CLR_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_CNTXT_GLOB_IRQ_CLR_OFFSET(ee) \
			(0x0001f110 + 0x4000 * (ee))
/* Values here are bit positions in the GLOB_IRQ_* रेजिस्टरs */
क्रमागत gsi_global_irq_id अणु
	ERROR_INT				= 0x0,
	GP_INT1					= 0x1,
	GP_INT2					= 0x2,
	GP_INT3					= 0x3,
पूर्ण;

#घोषणा GSI_CNTXT_GSI_IRQ_STTS_OFFSET \
			GSI_EE_N_CNTXT_GSI_IRQ_STTS_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_CNTXT_GSI_IRQ_STTS_OFFSET(ee) \
			(0x0001f118 + 0x4000 * (ee))
#घोषणा GSI_CNTXT_GSI_IRQ_EN_OFFSET \
			GSI_EE_N_CNTXT_GSI_IRQ_EN_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_CNTXT_GSI_IRQ_EN_OFFSET(ee) \
			(0x0001f120 + 0x4000 * (ee))
#घोषणा GSI_CNTXT_GSI_IRQ_CLR_OFFSET \
			GSI_EE_N_CNTXT_GSI_IRQ_CLR_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_CNTXT_GSI_IRQ_CLR_OFFSET(ee) \
			(0x0001f128 + 0x4000 * (ee))
/* Values here are bit positions in the (general) GSI_IRQ_* रेजिस्टरs */
क्रमागत gsi_general_id अणु
	BREAK_POINT				= 0x0,
	BUS_ERROR				= 0x1,
	CMD_FIFO_OVRFLOW			= 0x2,
	MCS_STACK_OVRFLOW			= 0x3,
पूर्ण;

#घोषणा GSI_CNTXT_INTSET_OFFSET \
			GSI_EE_N_CNTXT_INTSET_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_CNTXT_INTSET_OFFSET(ee) \
			(0x0001f180 + 0x4000 * (ee))
#घोषणा INTYPE_FMASK			GENMASK(0, 0)

#घोषणा GSI_ERROR_LOG_OFFSET \
			GSI_EE_N_ERROR_LOG_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_ERROR_LOG_OFFSET(ee) \
			(0x0001f200 + 0x4000 * (ee))

/* Fields below are present क्रम IPA v3.5.1 and above */
#घोषणा ERR_ARG3_FMASK			GENMASK(3, 0)
#घोषणा ERR_ARG2_FMASK			GENMASK(7, 4)
#घोषणा ERR_ARG1_FMASK			GENMASK(11, 8)
#घोषणा ERR_CODE_FMASK			GENMASK(15, 12)
#घोषणा ERR_VIRT_IDX_FMASK		GENMASK(23, 19)
#घोषणा ERR_TYPE_FMASK			GENMASK(27, 24)
#घोषणा ERR_EE_FMASK			GENMASK(31, 28)

/** क्रमागत gsi_err_code - ERR_CODE field values in EE_ERR_LOG */
क्रमागत gsi_err_code अणु
	GSI_INVALID_TRE				= 0x1,
	GSI_OUT_OF_BUFFERS			= 0x2,
	GSI_OUT_OF_RESOURCES			= 0x3,
	GSI_UNSUPPORTED_INTER_EE_OP		= 0x4,
	GSI_EVT_RING_EMPTY			= 0x5,
	GSI_NON_ALLOCATED_EVT_ACCESS		= 0x6,
	/* 7 is not asचिन्हित */
	GSI_HWO_1				= 0x8,
पूर्ण;

/** क्रमागत gsi_err_type - ERR_TYPE field values in EE_ERR_LOG */
क्रमागत gsi_err_type अणु
	GSI_ERR_TYPE_GLOB			= 0x1,
	GSI_ERR_TYPE_CHAN			= 0x2,
	GSI_ERR_TYPE_EVT			= 0x3,
पूर्ण;

#घोषणा GSI_ERROR_LOG_CLR_OFFSET \
			GSI_EE_N_ERROR_LOG_CLR_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_ERROR_LOG_CLR_OFFSET(ee) \
			(0x0001f210 + 0x4000 * (ee))

#घोषणा GSI_CNTXT_SCRATCH_0_OFFSET \
			GSI_EE_N_CNTXT_SCRATCH_0_OFFSET(GSI_EE_AP)
#घोषणा GSI_EE_N_CNTXT_SCRATCH_0_OFFSET(ee) \
			(0x0001f400 + 0x4000 * (ee))
#घोषणा INTER_EE_RESULT_FMASK		GENMASK(2, 0)
#घोषणा GENERIC_EE_RESULT_FMASK		GENMASK(7, 5)

/** क्रमागत gsi_generic_ee_result - GENERIC_EE_RESULT field values in SCRATCH_0 */
क्रमागत gsi_generic_ee_result अणु
	GENERIC_EE_SUCCESS			= 0x1,
	GENERIC_EE_CHANNEL_NOT_RUNNING		= 0x2,
	GENERIC_EE_INCORRECT_सूचीECTION		= 0x3,
	GENERIC_EE_INCORRECT_CHANNEL_TYPE	= 0x4,
	GENERIC_EE_INCORRECT_CHANNEL		= 0x5,
	GENERIC_EE_RETRY			= 0x6,
	GENERIC_EE_NO_RESOURCES			= 0x7,
पूर्ण;

#पूर्ण_अगर	/* _GSI_REG_H_ */
