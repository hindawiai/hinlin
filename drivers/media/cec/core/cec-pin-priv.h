<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * cec-pin-priv.h - पूर्णांकernal cec-pin header
 *
 * Copyright 2017 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित LINUX_CEC_PIN_PRIV_H
#घोषणा LINUX_CEC_PIN_PRIV_H

#समावेश <linux/types.h>
#समावेश <linux/atomic.h>
#समावेश <media/cec-pin.h>

क्रमागत cec_pin_state अणु
	/* CEC is off */
	CEC_ST_OFF,
	/* CEC is idle, रुकोing क्रम Rx or Tx */
	CEC_ST_IDLE,

	/* Tx states */

	/* Pending Tx, रुकोing क्रम Signal Free Time to expire */
	CEC_ST_TX_WAIT,
	/* Low-drive was detected, रुको क्रम bus to go high */
	CEC_ST_TX_WAIT_FOR_HIGH,
	/* Drive CEC low क्रम the start bit */
	CEC_ST_TX_START_BIT_LOW,
	/* Drive CEC high क्रम the start bit */
	CEC_ST_TX_START_BIT_HIGH,
	/* Generate a start bit period that is too लघु */
	CEC_ST_TX_START_BIT_HIGH_SHORT,
	/* Generate a start bit period that is too दीर्घ */
	CEC_ST_TX_START_BIT_HIGH_LONG,
	/* Drive CEC low क्रम the start bit using the custom timing */
	CEC_ST_TX_START_BIT_LOW_CUSTOM,
	/* Drive CEC high क्रम the start bit using the custom timing */
	CEC_ST_TX_START_BIT_HIGH_CUSTOM,
	/* Drive CEC low क्रम the 0 bit */
	CEC_ST_TX_DATA_BIT_0_LOW,
	/* Drive CEC high क्रम the 0 bit */
	CEC_ST_TX_DATA_BIT_0_HIGH,
	/* Generate a bit period that is too लघु */
	CEC_ST_TX_DATA_BIT_0_HIGH_SHORT,
	/* Generate a bit period that is too दीर्घ */
	CEC_ST_TX_DATA_BIT_0_HIGH_LONG,
	/* Drive CEC low क्रम the 1 bit */
	CEC_ST_TX_DATA_BIT_1_LOW,
	/* Drive CEC high क्रम the 1 bit */
	CEC_ST_TX_DATA_BIT_1_HIGH,
	/* Generate a bit period that is too लघु */
	CEC_ST_TX_DATA_BIT_1_HIGH_SHORT,
	/* Generate a bit period that is too दीर्घ */
	CEC_ST_TX_DATA_BIT_1_HIGH_LONG,
	/*
	 * Wait क्रम start of sample समय to check क्रम Ack bit or first
	 * four initiator bits to check क्रम Arbitration Lost.
	 */
	CEC_ST_TX_DATA_BIT_1_HIGH_PRE_SAMPLE,
	/* Wait क्रम end of bit period after sampling */
	CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPLE,
	/* Generate a bit period that is too लघु */
	CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPLE_SHORT,
	/* Generate a bit period that is too दीर्घ */
	CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPLE_LONG,
	/* Drive CEC low क्रम a data bit using the custom timing */
	CEC_ST_TX_DATA_BIT_LOW_CUSTOM,
	/* Drive CEC high क्रम a data bit using the custom timing */
	CEC_ST_TX_DATA_BIT_HIGH_CUSTOM,
	/* Drive CEC low क्रम a standalone pulse using the custom timing */
	CEC_ST_TX_PULSE_LOW_CUSTOM,
	/* Drive CEC high क्रम a standalone pulse using the custom timing */
	CEC_ST_TX_PULSE_HIGH_CUSTOM,
	/* Start low drive */
	CEC_ST_TX_LOW_DRIVE,

	/* Rx states */

	/* Start bit low detected */
	CEC_ST_RX_START_BIT_LOW,
	/* Start bit high detected */
	CEC_ST_RX_START_BIT_HIGH,
	/* Wait क्रम bit sample समय */
	CEC_ST_RX_DATA_SAMPLE,
	/* Wait क्रम earliest end of bit period after sampling */
	CEC_ST_RX_DATA_POST_SAMPLE,
	/* Wait क्रम CEC to go low (i.e. end of bit period) */
	CEC_ST_RX_DATA_WAIT_FOR_LOW,
	/* Drive CEC low to send 0 Ack bit */
	CEC_ST_RX_ACK_LOW,
	/* End of 0 Ack समय, रुको क्रम earliest end of bit period */
	CEC_ST_RX_ACK_LOW_POST,
	/* Wait क्रम CEC to go high (i.e. end of bit period */
	CEC_ST_RX_ACK_HIGH_POST,
	/* Wait क्रम earliest end of bit period and end of message */
	CEC_ST_RX_ACK_FINISH,
	/* Start low drive */
	CEC_ST_RX_LOW_DRIVE,

	/* Monitor pin using पूर्णांकerrupts */
	CEC_ST_RX_IRQ,

	/* Total number of pin states */
	CEC_PIN_STATES
पूर्ण;

/* Error Injection */

/* Error injection modes */
#घोषणा CEC_ERROR_INJ_MODE_OFF				0
#घोषणा CEC_ERROR_INJ_MODE_ONCE				1
#घोषणा CEC_ERROR_INJ_MODE_ALWAYS			2
#घोषणा CEC_ERROR_INJ_MODE_TOGGLE			3
#घोषणा CEC_ERROR_INJ_MODE_MASK				3ULL

/* Receive error injection options */
#घोषणा CEC_ERROR_INJ_RX_NACK_OFFSET			0
#घोषणा CEC_ERROR_INJ_RX_LOW_DRIVE_OFFSET		2
#घोषणा CEC_ERROR_INJ_RX_ADD_BYTE_OFFSET		4
#घोषणा CEC_ERROR_INJ_RX_REMOVE_BYTE_OFFSET		6
#घोषणा CEC_ERROR_INJ_RX_ARB_LOST_OFFSET		8
#घोषणा CEC_ERROR_INJ_RX_MASK				0xffffULL

/* Transmit error injection options */
#घोषणा CEC_ERROR_INJ_TX_NO_EOM_OFFSET			16
#घोषणा CEC_ERROR_INJ_TX_EARLY_EOM_OFFSET		18
#घोषणा CEC_ERROR_INJ_TX_SHORT_BIT_OFFSET		20
#घोषणा CEC_ERROR_INJ_TX_LONG_BIT_OFFSET		22
#घोषणा CEC_ERROR_INJ_TX_CUSTOM_BIT_OFFSET		24
#घोषणा CEC_ERROR_INJ_TX_SHORT_START_OFFSET		26
#घोषणा CEC_ERROR_INJ_TX_LONG_START_OFFSET		28
#घोषणा CEC_ERROR_INJ_TX_CUSTOM_START_OFFSET		30
#घोषणा CEC_ERROR_INJ_TX_LAST_BIT_OFFSET		32
#घोषणा CEC_ERROR_INJ_TX_ADD_BYTES_OFFSET		34
#घोषणा CEC_ERROR_INJ_TX_REMOVE_BYTE_OFFSET		36
#घोषणा CEC_ERROR_INJ_TX_LOW_DRIVE_OFFSET		38
#घोषणा CEC_ERROR_INJ_TX_MASK				0xffffffffffff0000ULL

#घोषणा CEC_ERROR_INJ_RX_LOW_DRIVE_ARG_IDX		0
#घोषणा CEC_ERROR_INJ_RX_ARB_LOST_ARG_IDX		1

#घोषणा CEC_ERROR_INJ_TX_ADD_BYTES_ARG_IDX		2
#घोषणा CEC_ERROR_INJ_TX_SHORT_BIT_ARG_IDX		3
#घोषणा CEC_ERROR_INJ_TX_LONG_BIT_ARG_IDX		4
#घोषणा CEC_ERROR_INJ_TX_CUSTOM_BIT_ARG_IDX		5
#घोषणा CEC_ERROR_INJ_TX_LAST_BIT_ARG_IDX		6
#घोषणा CEC_ERROR_INJ_TX_LOW_DRIVE_ARG_IDX		7
#घोषणा CEC_ERROR_INJ_NUM_ARGS				8

/* Special CEC op values */
#घोषणा CEC_ERROR_INJ_OP_ANY				0x00000100

/* The शेष क्रम the low/high समय of the custom pulse */
#घोषणा CEC_TIM_CUSTOM_DEFAULT				1000

#घोषणा CEC_NUM_PIN_EVENTS				128
#घोषणा CEC_PIN_EVENT_FL_IS_HIGH			(1 << 0)
#घोषणा CEC_PIN_EVENT_FL_DROPPED			(1 << 1)

#घोषणा CEC_PIN_IRQ_UNCHANGED	0
#घोषणा CEC_PIN_IRQ_DISABLE	1
#घोषणा CEC_PIN_IRQ_ENABLE	2

काष्ठा cec_pin अणु
	काष्ठा cec_adapter		*adap;
	स्थिर काष्ठा cec_pin_ops	*ops;
	काष्ठा task_काष्ठा		*kthपढ़ो;
	रुको_queue_head_t		kthपढ़ो_रुकोq;
	काष्ठा hrसमयr			समयr;
	kसमय_प्रकार				ts;
	अचिन्हित पूर्णांक			रुको_usecs;
	u16				la_mask;
	bool				enabled;
	bool				monitor_all;
	bool				rx_eom;
	bool				enable_irq_failed;
	क्रमागत cec_pin_state		state;
	काष्ठा cec_msg			tx_msg;
	u32				tx_bit;
	bool				tx_nacked;
	u32				tx_संकेत_मुक्त_समय;
	bool				tx_toggle;
	काष्ठा cec_msg			rx_msg;
	u32				rx_bit;
	bool				rx_toggle;
	u32				rx_start_bit_low_too_लघु_cnt;
	u64				rx_start_bit_low_too_लघु_ts;
	u32				rx_start_bit_low_too_लघु_delta;
	u32				rx_start_bit_too_लघु_cnt;
	u64				rx_start_bit_too_लघु_ts;
	u32				rx_start_bit_too_लघु_delta;
	u32				rx_start_bit_too_दीर्घ_cnt;
	u32				rx_data_bit_too_लघु_cnt;
	u64				rx_data_bit_too_लघु_ts;
	u32				rx_data_bit_too_लघु_delta;
	u32				rx_data_bit_too_दीर्घ_cnt;
	u32				rx_low_drive_cnt;

	काष्ठा cec_msg			work_rx_msg;
	u8				work_tx_status;
	kसमय_प्रकार				work_tx_ts;
	atomic_t			work_irq_change;
	atomic_t			work_pin_num_events;
	अचिन्हित पूर्णांक			work_pin_events_wr;
	अचिन्हित पूर्णांक			work_pin_events_rd;
	kसमय_प्रकार				work_pin_ts[CEC_NUM_PIN_EVENTS];
	u8				work_pin_events[CEC_NUM_PIN_EVENTS];
	bool				work_pin_events_dropped;
	u32				work_pin_events_dropped_cnt;
	kसमय_प्रकार				समयr_ts;
	u32				समयr_cnt;
	u32				समयr_100ms_overruns;
	u32				समयr_300ms_overruns;
	u32				समयr_max_overrun;
	u32				समयr_sum_overrun;

	u32				tx_custom_low_usecs;
	u32				tx_custom_high_usecs;
	bool				tx_ignore_nack_until_eom;
	bool				tx_custom_pulse;
	bool				tx_generated_poll;
	bool				tx_post_eom;
	u8				tx_extra_bytes;
	u32				tx_low_drive_cnt;
#अगर_घोषित CONFIG_CEC_PIN_ERROR_INJ
	u64				error_inj[CEC_ERROR_INJ_OP_ANY + 1];
	u8				error_inj_args[CEC_ERROR_INJ_OP_ANY + 1][CEC_ERROR_INJ_NUM_ARGS];
#पूर्ण_अगर
पूर्ण;

व्योम cec_pin_start_समयr(काष्ठा cec_pin *pin);

#अगर_घोषित CONFIG_CEC_PIN_ERROR_INJ
bool cec_pin_error_inj_parse_line(काष्ठा cec_adapter *adap, अक्षर *line);
पूर्णांक cec_pin_error_inj_show(काष्ठा cec_adapter *adap, काष्ठा seq_file *sf);

u16 cec_pin_rx_error_inj(काष्ठा cec_pin *pin);
u16 cec_pin_tx_error_inj(काष्ठा cec_pin *pin);
#पूर्ण_अगर

#पूर्ण_अगर
