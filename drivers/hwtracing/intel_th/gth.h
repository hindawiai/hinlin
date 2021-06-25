<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Intel(R) Trace Hub Global Trace Hub (GTH) data काष्ठाures
 *
 * Copyright (C) 2014-2015 Intel Corporation.
 */

#अगर_अघोषित __INTEL_TH_GTH_H__
#घोषणा __INTEL_TH_GTH_H__

/* Map output port parameter bits to symbolic names */
#घोषणा TH_OUTPUT_PARM(name)			\
	TH_OUTPUT_ ## name

क्रमागत पूर्णांकel_th_output_parm अणु
	/* output port type */
	TH_OUTPUT_PARM(port),
	/* generate शून्य packet */
	TH_OUTPUT_PARM(null),
	/* packet drop */
	TH_OUTPUT_PARM(drop),
	/* port in reset state */
	TH_OUTPUT_PARM(reset),
	/* flush out data */
	TH_OUTPUT_PARM(flush),
	/* मुख्यenance packet frequency */
	TH_OUTPUT_PARM(smcfreq),
पूर्ण;

/*
 * Register offsets
 */
क्रमागत अणु
	REG_GTH_GTHOPT0		= 0x00, /* Output ports 0..3 config */
	REG_GTH_GTHOPT1		= 0x04, /* Output ports 4..7 config */
	REG_GTH_SWDEST0		= 0x08, /* Switching destination masters 0..7 */
	REG_GTH_GSWTDEST	= 0x88, /* Global sw trace destination */
	REG_GTH_SMCR0		= 0x9c, /* STP मुख्यenance क्रम ports 0/1 */
	REG_GTH_SMCR1		= 0xa0, /* STP मुख्यenance क्रम ports 2/3 */
	REG_GTH_SMCR2		= 0xa4, /* STP मुख्यenance क्रम ports 4/5 */
	REG_GTH_SMCR3		= 0xa8, /* STP मुख्यenance क्रम ports 6/7 */
	REG_GTH_SCR		= 0xc8, /* Source control (storeEn override) */
	REG_GTH_STAT		= 0xd4, /* GTH status */
	REG_GTH_SCR2		= 0xd8, /* Source control (क्रमce storeEn off) */
	REG_GTH_DESTOVR		= 0xdc, /* Destination override */
	REG_GTH_SCRPD0		= 0xe0, /* ScratchPad[0] */
	REG_GTH_SCRPD1		= 0xe4, /* ScratchPad[1] */
	REG_GTH_SCRPD2		= 0xe8, /* ScratchPad[2] */
	REG_GTH_SCRPD3		= 0xec, /* ScratchPad[3] */
	REG_TSCU_TSUCTRL	= 0x2000, /* TSCU control रेजिस्टर */
	REG_TSCU_TSCUSTAT	= 0x2004, /* TSCU status रेजिस्टर */

	/* Common Capture Sequencer (CTS) रेजिस्टरs */
	REG_CTS_C0S0_EN		= 0x30c0, /* clause_event_enable_c0s0 */
	REG_CTS_C0S0_ACT	= 0x3180, /* clause_action_control_c0s0 */
	REG_CTS_STAT		= 0x32a0, /* cts_status */
	REG_CTS_CTL		= 0x32a4, /* cts_control */
पूर्ण;

/* रुकोing क्रम Pipeline Empty bit(s) to निश्चित क्रम GTH */
#घोषणा GTH_PLE_WAITLOOP_DEPTH	10000

#घोषणा TSUCTRL_CTCRESYNC	BIT(0)
#घोषणा TSCUSTAT_CTCSYNCING	BIT(1)

/* रुकोing क्रम Trigger status to निश्चित क्रम CTS */
#घोषणा CTS_TRIG_WAITLOOP_DEPTH	10000

#घोषणा CTS_EVENT_ENABLE_IF_ANYTHING	BIT(31)
#घोषणा CTS_ACTION_CONTROL_STATE_OFF	27
#घोषणा CTS_ACTION_CONTROL_SET_STATE(x)	\
	(((x) & 0x1f) << CTS_ACTION_CONTROL_STATE_OFF)
#घोषणा CTS_ACTION_CONTROL_TRIGGER	BIT(4)

#घोषणा CTS_STATE_IDLE			0x10u

#घोषणा CTS_CTL_SEQUENCER_ENABLE	BIT(0)

#पूर्ण_अगर /* __INTEL_TH_GTH_H__ */
