<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_sf_h__
#घोषणा __iwl_fw_api_sf_h__

/* Smart Fअगरo state */
क्रमागत iwl_sf_state अणु
	SF_LONG_DELAY_ON = 0, /* should never be called by driver */
	SF_FULL_ON,
	SF_UNINIT,
	SF_INIT_OFF,
	SF_HW_NUM_STATES
पूर्ण;

/* Smart Fअगरo possible scenario */
क्रमागत iwl_sf_scenario अणु
	SF_SCENARIO_SINGLE_UNICAST,
	SF_SCENARIO_AGG_UNICAST,
	SF_SCENARIO_MULTICAST,
	SF_SCENARIO_BA_RESP,
	SF_SCENARIO_TX_RESP,
	SF_NUM_SCENARIO
पूर्ण;

#घोषणा SF_TRANSIENT_STATES_NUMBER 2	/* SF_LONG_DELAY_ON and SF_FULL_ON */
#घोषणा SF_NUM_TIMEOUT_TYPES 2		/* Aging समयr and Idle समयr */

/* smart FIFO शेष values */
#घोषणा SF_W_MARK_SISO 6144
#घोषणा SF_W_MARK_MIMO2 8192
#घोषणा SF_W_MARK_MIMO3 6144
#घोषणा SF_W_MARK_LEGACY 4096
#घोषणा SF_W_MARK_SCAN 4096

/* SF Scenarios समयrs क्रम शेष configuration (aligned to 32 uSec) */
#घोषणा SF_SINGLE_UNICAST_IDLE_TIMER_DEF 160	/* 150 uSec  */
#घोषणा SF_SINGLE_UNICAST_AGING_TIMER_DEF 400	/* 0.4 mSec */
#घोषणा SF_AGG_UNICAST_IDLE_TIMER_DEF 160		/* 150 uSec */
#घोषणा SF_AGG_UNICAST_AGING_TIMER_DEF 400		/* 0.4 mSec */
#घोषणा SF_MCAST_IDLE_TIMER_DEF 160		/* 150 mSec */
#घोषणा SF_MCAST_AGING_TIMER_DEF 400		/* 0.4 mSec */
#घोषणा SF_BA_IDLE_TIMER_DEF 160			/* 150 uSec */
#घोषणा SF_BA_AGING_TIMER_DEF 400			/* 0.4 mSec */
#घोषणा SF_TX_RE_IDLE_TIMER_DEF 160			/* 150 uSec */
#घोषणा SF_TX_RE_AGING_TIMER_DEF 400		/* 0.4 mSec */

/* SF Scenarios समयrs क्रम BSS MAC configuration (aligned to 32 uSec) */
#घोषणा SF_SINGLE_UNICAST_IDLE_TIMER 320	/* 300 uSec  */
#घोषणा SF_SINGLE_UNICAST_AGING_TIMER 2016	/* 2 mSec */
#घोषणा SF_AGG_UNICAST_IDLE_TIMER 320		/* 300 uSec */
#घोषणा SF_AGG_UNICAST_AGING_TIMER 2016		/* 2 mSec */
#घोषणा SF_MCAST_IDLE_TIMER 2016		/* 2 mSec */
#घोषणा SF_MCAST_AGING_TIMER 10016		/* 10 mSec */
#घोषणा SF_BA_IDLE_TIMER 320			/* 300 uSec */
#घोषणा SF_BA_AGING_TIMER 2016			/* 2 mSec */
#घोषणा SF_TX_RE_IDLE_TIMER 320			/* 300 uSec */
#घोषणा SF_TX_RE_AGING_TIMER 2016		/* 2 mSec */

#घोषणा SF_LONG_DELAY_AGING_TIMER 1000000	/* 1 Sec */

#घोषणा SF_CFG_DUMMY_NOTIF_OFF	BIT(16)

/**
 * काष्ठा iwl_sf_cfg_cmd - Smart Fअगरo configuration command.
 * @state: smart fअगरo state, types listed in &क्रमागत iwl_sf_state.
 * @watermark: Minimum allowed available मुक्त space in RXF क्रम transient state.
 * @दीर्घ_delay_समयouts: aging and idle समयr values क्रम each scenario
 * in दीर्घ delay state.
 * @full_on_समयouts: समयr values क्रम each scenario in full on state.
 */
काष्ठा iwl_sf_cfg_cmd अणु
	__le32 state;
	__le32 watermark[SF_TRANSIENT_STATES_NUMBER];
	__le32 दीर्घ_delay_समयouts[SF_NUM_SCENARIO][SF_NUM_TIMEOUT_TYPES];
	__le32 full_on_समयouts[SF_NUM_SCENARIO][SF_NUM_TIMEOUT_TYPES];
पूर्ण __packed; /* SF_CFG_API_S_VER_2 */

#पूर्ण_अगर /* __iwl_fw_api_sf_h__ */
