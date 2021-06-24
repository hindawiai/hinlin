<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2017 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/types.h>

#समावेश <media/cec-pin.h>
#समावेश "cec-pin-priv.h"

/* All timings are in microseconds */

/* start bit timings */
#घोषणा CEC_TIM_START_BIT_LOW		3700
#घोषणा CEC_TIM_START_BIT_LOW_MIN	3500
#घोषणा CEC_TIM_START_BIT_LOW_MAX	3900
#घोषणा CEC_TIM_START_BIT_TOTAL		4500
#घोषणा CEC_TIM_START_BIT_TOTAL_MIN	4300
#घोषणा CEC_TIM_START_BIT_TOTAL_MAX	4700

/* data bit timings */
#घोषणा CEC_TIM_DATA_BIT_0_LOW		1500
#घोषणा CEC_TIM_DATA_BIT_0_LOW_MIN	1300
#घोषणा CEC_TIM_DATA_BIT_0_LOW_MAX	1700
#घोषणा CEC_TIM_DATA_BIT_1_LOW		600
#घोषणा CEC_TIM_DATA_BIT_1_LOW_MIN	400
#घोषणा CEC_TIM_DATA_BIT_1_LOW_MAX	800
#घोषणा CEC_TIM_DATA_BIT_TOTAL		2400
#घोषणा CEC_TIM_DATA_BIT_TOTAL_MIN	2050
#घोषणा CEC_TIM_DATA_BIT_TOTAL_MAX	2750
/* earliest safe समय to sample the bit state */
#घोषणा CEC_TIM_DATA_BIT_SAMPLE		850
/* earliest समय the bit is back to 1 (T7 + 50) */
#घोषणा CEC_TIM_DATA_BIT_HIGH		1750

/* when idle, sample once per millisecond */
#घोषणा CEC_TIM_IDLE_SAMPLE		1000
/* when processing the start bit, sample twice per millisecond */
#घोषणा CEC_TIM_START_BIT_SAMPLE	500
/* when polling क्रम a state change, sample once every 50 microseconds */
#घोषणा CEC_TIM_SAMPLE			50

#घोषणा CEC_TIM_LOW_DRIVE_ERROR		(1.5 * CEC_TIM_DATA_BIT_TOTAL)

/*
 * Total data bit समय that is too लघु/दीर्घ क्रम a valid bit,
 * used क्रम error injection.
 */
#घोषणा CEC_TIM_DATA_BIT_TOTAL_SHORT	1800
#घोषणा CEC_TIM_DATA_BIT_TOTAL_LONG	2900

/*
 * Total start bit समय that is too लघु/दीर्घ क्रम a valid bit,
 * used क्रम error injection.
 */
#घोषणा CEC_TIM_START_BIT_TOTAL_SHORT	4100
#घोषणा CEC_TIM_START_BIT_TOTAL_LONG	5000

/* Data bits are 0-7, EOM is bit 8 and ACK is bit 9 */
#घोषणा EOM_BIT				8
#घोषणा ACK_BIT				9

काष्ठा cec_state अणु
	स्थिर अक्षर * स्थिर name;
	अचिन्हित पूर्णांक usecs;
पूर्ण;

अटल स्थिर काष्ठा cec_state states[CEC_PIN_STATES] = अणु
	अणु "Off",		   0 पूर्ण,
	अणु "Idle",		   CEC_TIM_IDLE_SAMPLE पूर्ण,
	अणु "Tx Wait",		   CEC_TIM_SAMPLE पूर्ण,
	अणु "Tx Wait for High",	   CEC_TIM_IDLE_SAMPLE पूर्ण,
	अणु "Tx Start Bit Low",	   CEC_TIM_START_BIT_LOW पूर्ण,
	अणु "Tx Start Bit High",	   CEC_TIM_START_BIT_TOTAL - CEC_TIM_START_BIT_LOW पूर्ण,
	अणु "Tx Start Bit High Short", CEC_TIM_START_BIT_TOTAL_SHORT - CEC_TIM_START_BIT_LOW पूर्ण,
	अणु "Tx Start Bit High Long", CEC_TIM_START_BIT_TOTAL_LONG - CEC_TIM_START_BIT_LOW पूर्ण,
	अणु "Tx Start Bit Low Custom", 0 पूर्ण,
	अणु "Tx Start Bit High Custom", 0 पूर्ण,
	अणु "Tx Data 0 Low",	   CEC_TIM_DATA_BIT_0_LOW पूर्ण,
	अणु "Tx Data 0 High",	   CEC_TIM_DATA_BIT_TOTAL - CEC_TIM_DATA_BIT_0_LOW पूर्ण,
	अणु "Tx Data 0 High Short",  CEC_TIM_DATA_BIT_TOTAL_SHORT - CEC_TIM_DATA_BIT_0_LOW पूर्ण,
	अणु "Tx Data 0 High Long",   CEC_TIM_DATA_BIT_TOTAL_LONG - CEC_TIM_DATA_BIT_0_LOW पूर्ण,
	अणु "Tx Data 1 Low",	   CEC_TIM_DATA_BIT_1_LOW पूर्ण,
	अणु "Tx Data 1 High",	   CEC_TIM_DATA_BIT_TOTAL - CEC_TIM_DATA_BIT_1_LOW पूर्ण,
	अणु "Tx Data 1 High Short",  CEC_TIM_DATA_BIT_TOTAL_SHORT - CEC_TIM_DATA_BIT_1_LOW पूर्ण,
	अणु "Tx Data 1 High Long",   CEC_TIM_DATA_BIT_TOTAL_LONG - CEC_TIM_DATA_BIT_1_LOW पूर्ण,
	अणु "Tx Data 1 High Pre Sample", CEC_TIM_DATA_BIT_SAMPLE - CEC_TIM_DATA_BIT_1_LOW पूर्ण,
	अणु "Tx Data 1 High Post Sample", CEC_TIM_DATA_BIT_TOTAL - CEC_TIM_DATA_BIT_SAMPLE पूर्ण,
	अणु "Tx Data 1 High Post Sample Short", CEC_TIM_DATA_BIT_TOTAL_SHORT - CEC_TIM_DATA_BIT_SAMPLE पूर्ण,
	अणु "Tx Data 1 High Post Sample Long", CEC_TIM_DATA_BIT_TOTAL_LONG - CEC_TIM_DATA_BIT_SAMPLE पूर्ण,
	अणु "Tx Data Bit Low Custom", 0 पूर्ण,
	अणु "Tx Data Bit High Custom", 0 पूर्ण,
	अणु "Tx Pulse Low Custom",   0 पूर्ण,
	अणु "Tx Pulse High Custom",  0 पूर्ण,
	अणु "Tx Low Drive",	   CEC_TIM_LOW_DRIVE_ERROR पूर्ण,
	अणु "Rx Start Bit Low",	   CEC_TIM_SAMPLE पूर्ण,
	अणु "Rx Start Bit High",	   CEC_TIM_SAMPLE पूर्ण,
	अणु "Rx Data Sample",	   CEC_TIM_DATA_BIT_SAMPLE पूर्ण,
	अणु "Rx Data Post Sample",   CEC_TIM_DATA_BIT_HIGH - CEC_TIM_DATA_BIT_SAMPLE पूर्ण,
	अणु "Rx Data Wait for Low",  CEC_TIM_SAMPLE पूर्ण,
	अणु "Rx Ack Low",		   CEC_TIM_DATA_BIT_0_LOW पूर्ण,
	अणु "Rx Ack Low Post",	   CEC_TIM_DATA_BIT_HIGH - CEC_TIM_DATA_BIT_0_LOW पूर्ण,
	अणु "Rx Ack High Post",	   CEC_TIM_DATA_BIT_HIGH पूर्ण,
	अणु "Rx Ack Finish",	   CEC_TIM_DATA_BIT_TOTAL_MIN - CEC_TIM_DATA_BIT_HIGH पूर्ण,
	अणु "Rx Low Drive",	   CEC_TIM_LOW_DRIVE_ERROR पूर्ण,
	अणु "Rx Irq",		   0 पूर्ण,
पूर्ण;

अटल व्योम cec_pin_update(काष्ठा cec_pin *pin, bool v, bool क्रमce)
अणु
	अगर (!क्रमce && v == pin->adap->cec_pin_is_high)
		वापस;

	pin->adap->cec_pin_is_high = v;
	अगर (atomic_पढ़ो(&pin->work_pin_num_events) < CEC_NUM_PIN_EVENTS) अणु
		u8 ev = v;

		अगर (pin->work_pin_events_dropped) अणु
			pin->work_pin_events_dropped = false;
			ev |= CEC_PIN_EVENT_FL_DROPPED;
		पूर्ण
		pin->work_pin_events[pin->work_pin_events_wr] = ev;
		pin->work_pin_ts[pin->work_pin_events_wr] = kसमय_get();
		pin->work_pin_events_wr =
			(pin->work_pin_events_wr + 1) % CEC_NUM_PIN_EVENTS;
		atomic_inc(&pin->work_pin_num_events);
	पूर्ण अन्यथा अणु
		pin->work_pin_events_dropped = true;
		pin->work_pin_events_dropped_cnt++;
	पूर्ण
	wake_up_पूर्णांकerruptible(&pin->kthपढ़ो_रुकोq);
पूर्ण

अटल bool cec_pin_पढ़ो(काष्ठा cec_pin *pin)
अणु
	bool v = pin->ops->पढ़ो(pin->adap);

	cec_pin_update(pin, v, false);
	वापस v;
पूर्ण

अटल व्योम cec_pin_low(काष्ठा cec_pin *pin)
अणु
	pin->ops->low(pin->adap);
	cec_pin_update(pin, false, false);
पूर्ण

अटल bool cec_pin_high(काष्ठा cec_pin *pin)
अणु
	pin->ops->high(pin->adap);
	वापस cec_pin_पढ़ो(pin);
पूर्ण

अटल bool rx_error_inj(काष्ठा cec_pin *pin, अचिन्हित पूर्णांक mode_offset,
			 पूर्णांक arg_idx, u8 *arg)
अणु
#अगर_घोषित CONFIG_CEC_PIN_ERROR_INJ
	u16 cmd = cec_pin_rx_error_inj(pin);
	u64 e = pin->error_inj[cmd];
	अचिन्हित पूर्णांक mode = (e >> mode_offset) & CEC_ERROR_INJ_MODE_MASK;

	अगर (arg_idx >= 0) अणु
		u8 pos = pin->error_inj_args[cmd][arg_idx];

		अगर (arg)
			*arg = pos;
		अन्यथा अगर (pos != pin->rx_bit)
			वापस false;
	पूर्ण

	चयन (mode) अणु
	हाल CEC_ERROR_INJ_MODE_ONCE:
		pin->error_inj[cmd] &=
			~(CEC_ERROR_INJ_MODE_MASK << mode_offset);
		वापस true;
	हाल CEC_ERROR_INJ_MODE_ALWAYS:
		वापस true;
	हाल CEC_ERROR_INJ_MODE_TOGGLE:
		वापस pin->rx_toggle;
	शेष:
		वापस false;
	पूर्ण
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल bool rx_nack(काष्ठा cec_pin *pin)
अणु
	वापस rx_error_inj(pin, CEC_ERROR_INJ_RX_NACK_OFFSET, -1, शून्य);
पूर्ण

अटल bool rx_low_drive(काष्ठा cec_pin *pin)
अणु
	वापस rx_error_inj(pin, CEC_ERROR_INJ_RX_LOW_DRIVE_OFFSET,
			    CEC_ERROR_INJ_RX_LOW_DRIVE_ARG_IDX, शून्य);
पूर्ण

अटल bool rx_add_byte(काष्ठा cec_pin *pin)
अणु
	वापस rx_error_inj(pin, CEC_ERROR_INJ_RX_ADD_BYTE_OFFSET, -1, शून्य);
पूर्ण

अटल bool rx_हटाओ_byte(काष्ठा cec_pin *pin)
अणु
	वापस rx_error_inj(pin, CEC_ERROR_INJ_RX_REMOVE_BYTE_OFFSET, -1, शून्य);
पूर्ण

अटल bool rx_arb_lost(काष्ठा cec_pin *pin, u8 *poll)
अणु
	वापस pin->tx_msg.len == 0 &&
		rx_error_inj(pin, CEC_ERROR_INJ_RX_ARB_LOST_OFFSET,
			     CEC_ERROR_INJ_RX_ARB_LOST_ARG_IDX, poll);
पूर्ण

अटल bool tx_error_inj(काष्ठा cec_pin *pin, अचिन्हित पूर्णांक mode_offset,
			 पूर्णांक arg_idx, u8 *arg)
अणु
#अगर_घोषित CONFIG_CEC_PIN_ERROR_INJ
	u16 cmd = cec_pin_tx_error_inj(pin);
	u64 e = pin->error_inj[cmd];
	अचिन्हित पूर्णांक mode = (e >> mode_offset) & CEC_ERROR_INJ_MODE_MASK;

	अगर (arg_idx >= 0) अणु
		u8 pos = pin->error_inj_args[cmd][arg_idx];

		अगर (arg)
			*arg = pos;
		अन्यथा अगर (pos != pin->tx_bit)
			वापस false;
	पूर्ण

	चयन (mode) अणु
	हाल CEC_ERROR_INJ_MODE_ONCE:
		pin->error_inj[cmd] &=
			~(CEC_ERROR_INJ_MODE_MASK << mode_offset);
		वापस true;
	हाल CEC_ERROR_INJ_MODE_ALWAYS:
		वापस true;
	हाल CEC_ERROR_INJ_MODE_TOGGLE:
		वापस pin->tx_toggle;
	शेष:
		वापस false;
	पूर्ण
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल bool tx_no_eom(काष्ठा cec_pin *pin)
अणु
	वापस tx_error_inj(pin, CEC_ERROR_INJ_TX_NO_EOM_OFFSET, -1, शून्य);
पूर्ण

अटल bool tx_early_eom(काष्ठा cec_pin *pin)
अणु
	वापस tx_error_inj(pin, CEC_ERROR_INJ_TX_EARLY_EOM_OFFSET, -1, शून्य);
पूर्ण

अटल bool tx_लघु_bit(काष्ठा cec_pin *pin)
अणु
	वापस tx_error_inj(pin, CEC_ERROR_INJ_TX_SHORT_BIT_OFFSET,
			    CEC_ERROR_INJ_TX_SHORT_BIT_ARG_IDX, शून्य);
पूर्ण

अटल bool tx_दीर्घ_bit(काष्ठा cec_pin *pin)
अणु
	वापस tx_error_inj(pin, CEC_ERROR_INJ_TX_LONG_BIT_OFFSET,
			    CEC_ERROR_INJ_TX_LONG_BIT_ARG_IDX, शून्य);
पूर्ण

अटल bool tx_custom_bit(काष्ठा cec_pin *pin)
अणु
	वापस tx_error_inj(pin, CEC_ERROR_INJ_TX_CUSTOM_BIT_OFFSET,
			    CEC_ERROR_INJ_TX_CUSTOM_BIT_ARG_IDX, शून्य);
पूर्ण

अटल bool tx_लघु_start(काष्ठा cec_pin *pin)
अणु
	वापस tx_error_inj(pin, CEC_ERROR_INJ_TX_SHORT_START_OFFSET, -1, शून्य);
पूर्ण

अटल bool tx_दीर्घ_start(काष्ठा cec_pin *pin)
अणु
	वापस tx_error_inj(pin, CEC_ERROR_INJ_TX_LONG_START_OFFSET, -1, शून्य);
पूर्ण

अटल bool tx_custom_start(काष्ठा cec_pin *pin)
अणु
	वापस tx_error_inj(pin, CEC_ERROR_INJ_TX_CUSTOM_START_OFFSET,
			    -1, शून्य);
पूर्ण

अटल bool tx_last_bit(काष्ठा cec_pin *pin)
अणु
	वापस tx_error_inj(pin, CEC_ERROR_INJ_TX_LAST_BIT_OFFSET,
			    CEC_ERROR_INJ_TX_LAST_BIT_ARG_IDX, शून्य);
पूर्ण

अटल u8 tx_add_bytes(काष्ठा cec_pin *pin)
अणु
	u8 bytes;

	अगर (tx_error_inj(pin, CEC_ERROR_INJ_TX_ADD_BYTES_OFFSET,
			 CEC_ERROR_INJ_TX_ADD_BYTES_ARG_IDX, &bytes))
		वापस bytes;
	वापस 0;
पूर्ण

अटल bool tx_हटाओ_byte(काष्ठा cec_pin *pin)
अणु
	वापस tx_error_inj(pin, CEC_ERROR_INJ_TX_REMOVE_BYTE_OFFSET, -1, शून्य);
पूर्ण

अटल bool tx_low_drive(काष्ठा cec_pin *pin)
अणु
	वापस tx_error_inj(pin, CEC_ERROR_INJ_TX_LOW_DRIVE_OFFSET,
			    CEC_ERROR_INJ_TX_LOW_DRIVE_ARG_IDX, शून्य);
पूर्ण

अटल व्योम cec_pin_to_idle(काष्ठा cec_pin *pin)
अणु
	/*
	 * Reset all status fields, release the bus and
	 * go to idle state.
	 */
	pin->rx_bit = pin->tx_bit = 0;
	pin->rx_msg.len = 0;
	स_रखो(pin->rx_msg.msg, 0, माप(pin->rx_msg.msg));
	pin->ts = ns_to_kसमय(0);
	pin->tx_generated_poll = false;
	pin->tx_post_eom = false;
	अगर (pin->state >= CEC_ST_TX_WAIT &&
	    pin->state <= CEC_ST_TX_LOW_DRIVE)
		pin->tx_toggle ^= 1;
	अगर (pin->state >= CEC_ST_RX_START_BIT_LOW &&
	    pin->state <= CEC_ST_RX_LOW_DRIVE)
		pin->rx_toggle ^= 1;
	pin->state = CEC_ST_IDLE;
पूर्ण

/*
 * Handle Transmit-related states
 *
 * Basic state changes when transmitting:
 *
 * Idle -> Tx Wait (रुकोing क्रम the end of संकेत मुक्त समय) ->
 *	Tx Start Bit Low -> Tx Start Bit High ->
 *
 *   Regular data bits + EOM:
 *	Tx Data 0 Low -> Tx Data 0 High ->
 *   or:
 *	Tx Data 1 Low -> Tx Data 1 High ->
 *
 *   First 4 data bits or Ack bit:
 *	Tx Data 0 Low -> Tx Data 0 High ->
 *   or:
 *	Tx Data 1 Low -> Tx Data 1 High -> Tx Data 1 Pre Sample ->
 *		Tx Data 1 Post Sample ->
 *
 *   After the last Ack go to Idle.
 *
 * If it detects a Low Drive condition then:
 *	Tx Wait For High -> Idle
 *
 * If it loses arbitration, then it चयनes to state Rx Data Post Sample.
 */
अटल व्योम cec_pin_tx_states(काष्ठा cec_pin *pin, kसमय_प्रकार ts)
अणु
	bool v;
	bool is_ack_bit, ack;

	चयन (pin->state) अणु
	हाल CEC_ST_TX_WAIT_FOR_HIGH:
		अगर (cec_pin_पढ़ो(pin))
			cec_pin_to_idle(pin);
		अवरोध;

	हाल CEC_ST_TX_START_BIT_LOW:
		अगर (tx_लघु_start(pin)) अणु
			/*
			 * Error Injection: send an invalid (too लघु)
			 * start pulse.
			 */
			pin->state = CEC_ST_TX_START_BIT_HIGH_SHORT;
		पूर्ण अन्यथा अगर (tx_दीर्घ_start(pin)) अणु
			/*
			 * Error Injection: send an invalid (too दीर्घ)
			 * start pulse.
			 */
			pin->state = CEC_ST_TX_START_BIT_HIGH_LONG;
		पूर्ण अन्यथा अणु
			pin->state = CEC_ST_TX_START_BIT_HIGH;
		पूर्ण
		/* Generate start bit */
		cec_pin_high(pin);
		अवरोध;

	हाल CEC_ST_TX_START_BIT_LOW_CUSTOM:
		pin->state = CEC_ST_TX_START_BIT_HIGH_CUSTOM;
		/* Generate start bit */
		cec_pin_high(pin);
		अवरोध;

	हाल CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPLE:
	हाल CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPLE_SHORT:
	हाल CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPLE_LONG:
		अगर (pin->tx_nacked) अणु
			cec_pin_to_idle(pin);
			pin->tx_msg.len = 0;
			अगर (pin->tx_generated_poll)
				अवरोध;
			pin->work_tx_ts = ts;
			pin->work_tx_status = CEC_TX_STATUS_NACK;
			wake_up_पूर्णांकerruptible(&pin->kthपढ़ो_रुकोq);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल CEC_ST_TX_DATA_BIT_0_HIGH:
	हाल CEC_ST_TX_DATA_BIT_0_HIGH_SHORT:
	हाल CEC_ST_TX_DATA_BIT_0_HIGH_LONG:
	हाल CEC_ST_TX_DATA_BIT_1_HIGH:
	हाल CEC_ST_TX_DATA_BIT_1_HIGH_SHORT:
	हाल CEC_ST_TX_DATA_BIT_1_HIGH_LONG:
		/*
		 * If the पढ़ो value is 1, then all is OK, otherwise we have a
		 * low drive condition.
		 *
		 * Special हाल: when we generate a poll message due to an
		 * Arbitration Lost error injection, then ignore this since
		 * the pin can actually be low in that हाल.
		 */
		अगर (!cec_pin_पढ़ो(pin) && !pin->tx_generated_poll) अणु
			/*
			 * It's 0, so someone detected an error and pulled the
			 * line low क्रम 1.5 बार the nominal bit period.
			 */
			pin->tx_msg.len = 0;
			pin->state = CEC_ST_TX_WAIT_FOR_HIGH;
			pin->work_tx_ts = ts;
			pin->work_tx_status = CEC_TX_STATUS_LOW_DRIVE;
			pin->tx_low_drive_cnt++;
			wake_up_पूर्णांकerruptible(&pin->kthपढ़ो_रुकोq);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल CEC_ST_TX_DATA_BIT_HIGH_CUSTOM:
		अगर (tx_last_bit(pin)) अणु
			/* Error Injection: just stop sending after this bit */
			cec_pin_to_idle(pin);
			pin->tx_msg.len = 0;
			अगर (pin->tx_generated_poll)
				अवरोध;
			pin->work_tx_ts = ts;
			pin->work_tx_status = CEC_TX_STATUS_OK;
			wake_up_पूर्णांकerruptible(&pin->kthपढ़ो_रुकोq);
			अवरोध;
		पूर्ण
		pin->tx_bit++;
		fallthrough;
	हाल CEC_ST_TX_START_BIT_HIGH:
	हाल CEC_ST_TX_START_BIT_HIGH_SHORT:
	हाल CEC_ST_TX_START_BIT_HIGH_LONG:
	हाल CEC_ST_TX_START_BIT_HIGH_CUSTOM:
		अगर (tx_low_drive(pin)) अणु
			/* Error injection: go to low drive */
			cec_pin_low(pin);
			pin->state = CEC_ST_TX_LOW_DRIVE;
			pin->tx_msg.len = 0;
			अगर (pin->tx_generated_poll)
				अवरोध;
			pin->work_tx_ts = ts;
			pin->work_tx_status = CEC_TX_STATUS_LOW_DRIVE;
			pin->tx_low_drive_cnt++;
			wake_up_पूर्णांकerruptible(&pin->kthपढ़ो_रुकोq);
			अवरोध;
		पूर्ण
		अगर (pin->tx_bit / 10 >= pin->tx_msg.len + pin->tx_extra_bytes) अणु
			cec_pin_to_idle(pin);
			pin->tx_msg.len = 0;
			अगर (pin->tx_generated_poll)
				अवरोध;
			pin->work_tx_ts = ts;
			pin->work_tx_status = CEC_TX_STATUS_OK;
			wake_up_पूर्णांकerruptible(&pin->kthपढ़ो_रुकोq);
			अवरोध;
		पूर्ण

		चयन (pin->tx_bit % 10) अणु
		शेष: अणु
			/*
			 * In the CEC_ERROR_INJ_TX_ADD_BYTES हाल we transmit
			 * extra bytes, so pin->tx_bit / 10 can become >= 16.
			 * Generate bit values क्रम those extra bytes instead
			 * of पढ़ोing them from the transmit buffer.
			 */
			अचिन्हित पूर्णांक idx = (pin->tx_bit / 10);
			u8 val = idx;

			अगर (idx < pin->tx_msg.len)
				val = pin->tx_msg.msg[idx];
			v = val & (1 << (7 - (pin->tx_bit % 10)));

			pin->state = v ? CEC_ST_TX_DATA_BIT_1_LOW :
					 CEC_ST_TX_DATA_BIT_0_LOW;
			अवरोध;
		पूर्ण
		हाल EOM_BIT: अणु
			अचिन्हित पूर्णांक tot_len = pin->tx_msg.len +
					       pin->tx_extra_bytes;
			अचिन्हित पूर्णांक tx_byte_idx = pin->tx_bit / 10;

			v = !pin->tx_post_eom && tx_byte_idx == tot_len - 1;
			अगर (tot_len > 1 && tx_byte_idx == tot_len - 2 &&
			    tx_early_eom(pin)) अणु
				/* Error injection: set EOM one byte early */
				v = true;
				pin->tx_post_eom = true;
			पूर्ण अन्यथा अगर (v && tx_no_eom(pin)) अणु
				/* Error injection: no EOM */
				v = false;
			पूर्ण
			pin->state = v ? CEC_ST_TX_DATA_BIT_1_LOW :
					 CEC_ST_TX_DATA_BIT_0_LOW;
			अवरोध;
		पूर्ण
		हाल ACK_BIT:
			pin->state = CEC_ST_TX_DATA_BIT_1_LOW;
			अवरोध;
		पूर्ण
		अगर (tx_custom_bit(pin))
			pin->state = CEC_ST_TX_DATA_BIT_LOW_CUSTOM;
		cec_pin_low(pin);
		अवरोध;

	हाल CEC_ST_TX_DATA_BIT_0_LOW:
	हाल CEC_ST_TX_DATA_BIT_1_LOW:
		v = pin->state == CEC_ST_TX_DATA_BIT_1_LOW;
		is_ack_bit = pin->tx_bit % 10 == ACK_BIT;
		अगर (v && (pin->tx_bit < 4 || is_ack_bit)) अणु
			pin->state = CEC_ST_TX_DATA_BIT_1_HIGH_PRE_SAMPLE;
		पूर्ण अन्यथा अगर (!is_ack_bit && tx_लघु_bit(pin)) अणु
			/* Error Injection: send an invalid (too लघु) bit */
			pin->state = v ? CEC_ST_TX_DATA_BIT_1_HIGH_SHORT :
					 CEC_ST_TX_DATA_BIT_0_HIGH_SHORT;
		पूर्ण अन्यथा अगर (!is_ack_bit && tx_दीर्घ_bit(pin)) अणु
			/* Error Injection: send an invalid (too दीर्घ) bit */
			pin->state = v ? CEC_ST_TX_DATA_BIT_1_HIGH_LONG :
					 CEC_ST_TX_DATA_BIT_0_HIGH_LONG;
		पूर्ण अन्यथा अणु
			pin->state = v ? CEC_ST_TX_DATA_BIT_1_HIGH :
					 CEC_ST_TX_DATA_BIT_0_HIGH;
		पूर्ण
		cec_pin_high(pin);
		अवरोध;

	हाल CEC_ST_TX_DATA_BIT_LOW_CUSTOM:
		pin->state = CEC_ST_TX_DATA_BIT_HIGH_CUSTOM;
		cec_pin_high(pin);
		अवरोध;

	हाल CEC_ST_TX_DATA_BIT_1_HIGH_PRE_SAMPLE:
		/* Read the CEC value at the sample समय */
		v = cec_pin_पढ़ो(pin);
		is_ack_bit = pin->tx_bit % 10 == ACK_BIT;
		/*
		 * If v == 0 and we're within the first 4 bits
		 * of the initiator, then someone अन्यथा started
		 * transmitting and we lost the arbitration
		 * (i.e. the logical address of the other
		 * transmitter has more leading 0 bits in the
		 * initiator).
		 */
		अगर (!v && !is_ack_bit && !pin->tx_generated_poll) अणु
			pin->tx_msg.len = 0;
			pin->work_tx_ts = ts;
			pin->work_tx_status = CEC_TX_STATUS_ARB_LOST;
			wake_up_पूर्णांकerruptible(&pin->kthपढ़ो_रुकोq);
			pin->rx_bit = pin->tx_bit;
			pin->tx_bit = 0;
			स_रखो(pin->rx_msg.msg, 0, माप(pin->rx_msg.msg));
			pin->rx_msg.msg[0] = pin->tx_msg.msg[0];
			pin->rx_msg.msg[0] &= (0xff << (8 - pin->rx_bit));
			pin->rx_msg.len = 0;
			pin->ts = kसमय_sub_us(ts, CEC_TIM_DATA_BIT_SAMPLE);
			pin->state = CEC_ST_RX_DATA_POST_SAMPLE;
			pin->rx_bit++;
			अवरोध;
		पूर्ण
		pin->state = CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPLE;
		अगर (!is_ack_bit && tx_लघु_bit(pin)) अणु
			/* Error Injection: send an invalid (too लघु) bit */
			pin->state = CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPLE_SHORT;
		पूर्ण अन्यथा अगर (!is_ack_bit && tx_दीर्घ_bit(pin)) अणु
			/* Error Injection: send an invalid (too दीर्घ) bit */
			pin->state = CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPLE_LONG;
		पूर्ण
		अगर (!is_ack_bit)
			अवरोध;
		/* Was the message ACKed? */
		ack = cec_msg_is_broadcast(&pin->tx_msg) ? v : !v;
		अगर (!ack && (!pin->tx_ignore_nack_until_eom ||
		    pin->tx_bit / 10 == pin->tx_msg.len - 1) &&
		    !pin->tx_post_eom) अणु
			/*
			 * Note: the CEC spec is ambiguous regarding
			 * what action to take when a NACK appears
			 * beक्रमe the last byte of the payload was
			 * transmitted: either stop transmitting
			 * immediately, or रुको until the last byte
			 * was transmitted.
			 *
			 * Most CEC implementations appear to stop
			 * immediately, and that's what we करो here
			 * as well.
			 */
			pin->tx_nacked = true;
		पूर्ण
		अवरोध;

	हाल CEC_ST_TX_PULSE_LOW_CUSTOM:
		cec_pin_high(pin);
		pin->state = CEC_ST_TX_PULSE_HIGH_CUSTOM;
		अवरोध;

	हाल CEC_ST_TX_PULSE_HIGH_CUSTOM:
		cec_pin_to_idle(pin);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Handle Receive-related states
 *
 * Basic state changes when receiving:
 *
 *	Rx Start Bit Low -> Rx Start Bit High ->
 *   Regular data bits + EOM:
 *	Rx Data Sample -> Rx Data Post Sample -> Rx Data High ->
 *   Ack bit 0:
 *	Rx Ack Low -> Rx Ack Low Post -> Rx Data High ->
 *   Ack bit 1:
 *	Rx Ack High Post -> Rx Data High ->
 *   Ack bit 0 && EOM:
 *	Rx Ack Low -> Rx Ack Low Post -> Rx Ack Finish -> Idle
 */
अटल व्योम cec_pin_rx_states(काष्ठा cec_pin *pin, kसमय_प्रकार ts)
अणु
	s32 delta;
	bool v;
	bool ack;
	bool bcast, क्रम_us;
	u8 dest;
	u8 poll;

	चयन (pin->state) अणु
	/* Receive states */
	हाल CEC_ST_RX_START_BIT_LOW:
		v = cec_pin_पढ़ो(pin);
		अगर (!v)
			अवरोध;
		pin->state = CEC_ST_RX_START_BIT_HIGH;
		delta = kसमय_us_delta(ts, pin->ts);
		/* Start bit low is too लघु, go back to idle */
		अगर (delta < CEC_TIM_START_BIT_LOW_MIN - CEC_TIM_IDLE_SAMPLE) अणु
			अगर (!pin->rx_start_bit_low_too_लघु_cnt++) अणु
				pin->rx_start_bit_low_too_लघु_ts = kसमय_प्रकारo_ns(pin->ts);
				pin->rx_start_bit_low_too_लघु_delta = delta;
			पूर्ण
			cec_pin_to_idle(pin);
			अवरोध;
		पूर्ण
		अगर (rx_arb_lost(pin, &poll)) अणु
			cec_msg_init(&pin->tx_msg, poll >> 4, poll & 0xf);
			pin->tx_generated_poll = true;
			pin->tx_extra_bytes = 0;
			pin->state = CEC_ST_TX_START_BIT_HIGH;
			pin->ts = ts;
		पूर्ण
		अवरोध;

	हाल CEC_ST_RX_START_BIT_HIGH:
		v = cec_pin_पढ़ो(pin);
		delta = kसमय_us_delta(ts, pin->ts);
		/*
		 * Unक्रमtunately the spec करोes not specअगरy when to give up
		 * and go to idle. We just pick TOTAL_LONG.
		 */
		अगर (v && delta > CEC_TIM_START_BIT_TOTAL_LONG) अणु
			pin->rx_start_bit_too_दीर्घ_cnt++;
			cec_pin_to_idle(pin);
			अवरोध;
		पूर्ण
		अगर (v)
			अवरोध;
		/* Start bit is too लघु, go back to idle */
		अगर (delta < CEC_TIM_START_BIT_TOTAL_MIN - CEC_TIM_IDLE_SAMPLE) अणु
			अगर (!pin->rx_start_bit_too_लघु_cnt++) अणु
				pin->rx_start_bit_too_लघु_ts = kसमय_प्रकारo_ns(pin->ts);
				pin->rx_start_bit_too_लघु_delta = delta;
			पूर्ण
			cec_pin_to_idle(pin);
			अवरोध;
		पूर्ण
		अगर (rx_low_drive(pin)) अणु
			/* Error injection: go to low drive */
			cec_pin_low(pin);
			pin->state = CEC_ST_RX_LOW_DRIVE;
			pin->rx_low_drive_cnt++;
			अवरोध;
		पूर्ण
		pin->state = CEC_ST_RX_DATA_SAMPLE;
		pin->ts = ts;
		pin->rx_eom = false;
		अवरोध;

	हाल CEC_ST_RX_DATA_SAMPLE:
		v = cec_pin_पढ़ो(pin);
		pin->state = CEC_ST_RX_DATA_POST_SAMPLE;
		चयन (pin->rx_bit % 10) अणु
		शेष:
			अगर (pin->rx_bit / 10 < CEC_MAX_MSG_SIZE)
				pin->rx_msg.msg[pin->rx_bit / 10] |=
					v << (7 - (pin->rx_bit % 10));
			अवरोध;
		हाल EOM_BIT:
			pin->rx_eom = v;
			pin->rx_msg.len = pin->rx_bit / 10 + 1;
			अवरोध;
		हाल ACK_BIT:
			अवरोध;
		पूर्ण
		pin->rx_bit++;
		अवरोध;

	हाल CEC_ST_RX_DATA_POST_SAMPLE:
		pin->state = CEC_ST_RX_DATA_WAIT_FOR_LOW;
		अवरोध;

	हाल CEC_ST_RX_DATA_WAIT_FOR_LOW:
		v = cec_pin_पढ़ो(pin);
		delta = kसमय_us_delta(ts, pin->ts);
		/*
		 * Unक्रमtunately the spec करोes not specअगरy when to give up
		 * and go to idle. We just pick TOTAL_LONG.
		 */
		अगर (v && delta > CEC_TIM_DATA_BIT_TOTAL_LONG) अणु
			pin->rx_data_bit_too_दीर्घ_cnt++;
			cec_pin_to_idle(pin);
			अवरोध;
		पूर्ण
		अगर (v)
			अवरोध;

		अगर (rx_low_drive(pin)) अणु
			/* Error injection: go to low drive */
			cec_pin_low(pin);
			pin->state = CEC_ST_RX_LOW_DRIVE;
			pin->rx_low_drive_cnt++;
			अवरोध;
		पूर्ण

		/*
		 * Go to low drive state when the total bit समय is
		 * too लघु.
		 */
		अगर (delta < CEC_TIM_DATA_BIT_TOTAL_MIN) अणु
			अगर (!pin->rx_data_bit_too_लघु_cnt++) अणु
				pin->rx_data_bit_too_लघु_ts = kसमय_प्रकारo_ns(pin->ts);
				pin->rx_data_bit_too_लघु_delta = delta;
			पूर्ण
			cec_pin_low(pin);
			pin->state = CEC_ST_RX_LOW_DRIVE;
			pin->rx_low_drive_cnt++;
			अवरोध;
		पूर्ण
		pin->ts = ts;
		अगर (pin->rx_bit % 10 != 9) अणु
			pin->state = CEC_ST_RX_DATA_SAMPLE;
			अवरोध;
		पूर्ण

		dest = cec_msg_destination(&pin->rx_msg);
		bcast = dest == CEC_LOG_ADDR_BROADCAST;
		/* क्रम_us == broadcast or directed to us */
		क्रम_us = bcast || (pin->la_mask & (1 << dest));
		/* ACK bit value */
		ack = bcast ? 1 : !क्रम_us;

		अगर (क्रम_us && rx_nack(pin)) अणु
			/* Error injection: toggle the ACK bit */
			ack = !ack;
		पूर्ण

		अगर (ack) अणु
			/* No need to ग_लिखो to the bus, just रुको */
			pin->state = CEC_ST_RX_ACK_HIGH_POST;
			अवरोध;
		पूर्ण
		cec_pin_low(pin);
		pin->state = CEC_ST_RX_ACK_LOW;
		अवरोध;

	हाल CEC_ST_RX_ACK_LOW:
		cec_pin_high(pin);
		pin->state = CEC_ST_RX_ACK_LOW_POST;
		अवरोध;

	हाल CEC_ST_RX_ACK_LOW_POST:
	हाल CEC_ST_RX_ACK_HIGH_POST:
		v = cec_pin_पढ़ो(pin);
		अगर (v && pin->rx_eom) अणु
			pin->work_rx_msg = pin->rx_msg;
			pin->work_rx_msg.rx_ts = kसमय_प्रकारo_ns(ts);
			wake_up_पूर्णांकerruptible(&pin->kthपढ़ो_रुकोq);
			pin->ts = ts;
			pin->state = CEC_ST_RX_ACK_FINISH;
			अवरोध;
		पूर्ण
		pin->rx_bit++;
		pin->state = CEC_ST_RX_DATA_WAIT_FOR_LOW;
		अवरोध;

	हाल CEC_ST_RX_ACK_FINISH:
		cec_pin_to_idle(pin);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Main समयr function
 *
 */
अटल क्रमागत hrसमयr_restart cec_pin_समयr(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा cec_pin *pin = container_of(समयr, काष्ठा cec_pin, समयr);
	काष्ठा cec_adapter *adap = pin->adap;
	kसमय_प्रकार ts;
	s32 delta;
	u32 usecs;

	ts = kसमय_get();
	अगर (kसमय_प्रकारo_ns(pin->समयr_ts)) अणु
		delta = kसमय_us_delta(ts, pin->समयr_ts);
		pin->समयr_cnt++;
		अगर (delta > 100 && pin->state != CEC_ST_IDLE) अणु
			/* Keep track of समयr overruns */
			pin->समयr_sum_overrun += delta;
			pin->समयr_100ms_overruns++;
			अगर (delta > 300)
				pin->समयr_300ms_overruns++;
			अगर (delta > pin->समयr_max_overrun)
				pin->समयr_max_overrun = delta;
		पूर्ण
	पूर्ण
	अगर (adap->monitor_pin_cnt)
		cec_pin_पढ़ो(pin);

	अगर (pin->रुको_usecs) अणु
		/*
		 * If we are monitoring the pin, then we have to
		 * sample at regular पूर्णांकervals.
		 */
		अगर (pin->रुको_usecs > 150) अणु
			pin->रुको_usecs -= 100;
			pin->समयr_ts = kसमय_add_us(ts, 100);
			hrसमयr_क्रमward_now(समयr, ns_to_kसमय(100000));
			वापस HRTIMER_RESTART;
		पूर्ण
		अगर (pin->रुको_usecs > 100) अणु
			pin->रुको_usecs /= 2;
			pin->समयr_ts = kसमय_add_us(ts, pin->रुको_usecs);
			hrसमयr_क्रमward_now(समयr,
					ns_to_kसमय(pin->रुको_usecs * 1000));
			वापस HRTIMER_RESTART;
		पूर्ण
		pin->समयr_ts = kसमय_add_us(ts, pin->रुको_usecs);
		hrसमयr_क्रमward_now(समयr,
				    ns_to_kसमय(pin->रुको_usecs * 1000));
		pin->रुको_usecs = 0;
		वापस HRTIMER_RESTART;
	पूर्ण

	चयन (pin->state) अणु
	/* Transmit states */
	हाल CEC_ST_TX_WAIT_FOR_HIGH:
	हाल CEC_ST_TX_START_BIT_LOW:
	हाल CEC_ST_TX_START_BIT_HIGH:
	हाल CEC_ST_TX_START_BIT_HIGH_SHORT:
	हाल CEC_ST_TX_START_BIT_HIGH_LONG:
	हाल CEC_ST_TX_START_BIT_LOW_CUSTOM:
	हाल CEC_ST_TX_START_BIT_HIGH_CUSTOM:
	हाल CEC_ST_TX_DATA_BIT_0_LOW:
	हाल CEC_ST_TX_DATA_BIT_0_HIGH:
	हाल CEC_ST_TX_DATA_BIT_0_HIGH_SHORT:
	हाल CEC_ST_TX_DATA_BIT_0_HIGH_LONG:
	हाल CEC_ST_TX_DATA_BIT_1_LOW:
	हाल CEC_ST_TX_DATA_BIT_1_HIGH:
	हाल CEC_ST_TX_DATA_BIT_1_HIGH_SHORT:
	हाल CEC_ST_TX_DATA_BIT_1_HIGH_LONG:
	हाल CEC_ST_TX_DATA_BIT_1_HIGH_PRE_SAMPLE:
	हाल CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPLE:
	हाल CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPLE_SHORT:
	हाल CEC_ST_TX_DATA_BIT_1_HIGH_POST_SAMPLE_LONG:
	हाल CEC_ST_TX_DATA_BIT_LOW_CUSTOM:
	हाल CEC_ST_TX_DATA_BIT_HIGH_CUSTOM:
	हाल CEC_ST_TX_PULSE_LOW_CUSTOM:
	हाल CEC_ST_TX_PULSE_HIGH_CUSTOM:
		cec_pin_tx_states(pin, ts);
		अवरोध;

	/* Receive states */
	हाल CEC_ST_RX_START_BIT_LOW:
	हाल CEC_ST_RX_START_BIT_HIGH:
	हाल CEC_ST_RX_DATA_SAMPLE:
	हाल CEC_ST_RX_DATA_POST_SAMPLE:
	हाल CEC_ST_RX_DATA_WAIT_FOR_LOW:
	हाल CEC_ST_RX_ACK_LOW:
	हाल CEC_ST_RX_ACK_LOW_POST:
	हाल CEC_ST_RX_ACK_HIGH_POST:
	हाल CEC_ST_RX_ACK_FINISH:
		cec_pin_rx_states(pin, ts);
		अवरोध;

	हाल CEC_ST_IDLE:
	हाल CEC_ST_TX_WAIT:
		अगर (!cec_pin_high(pin)) अणु
			/* Start bit, चयन to receive state */
			pin->ts = ts;
			pin->state = CEC_ST_RX_START_BIT_LOW;
			/*
			 * If a transmit is pending, then that transmit should
			 * use a संकेत मुक्त समय of no more than
			 * CEC_SIGNAL_FREE_TIME_NEW_INITIATOR since it will
			 * have a new initiator due to the receive that is now
			 * starting.
			 */
			अगर (pin->tx_msg.len && pin->tx_संकेत_मुक्त_समय >
			    CEC_SIGNAL_FREE_TIME_NEW_INITIATOR)
				pin->tx_संकेत_मुक्त_समय =
					CEC_SIGNAL_FREE_TIME_NEW_INITIATOR;
			अवरोध;
		पूर्ण
		अगर (kसमय_प्रकारo_ns(pin->ts) == 0)
			pin->ts = ts;
		अगर (pin->tx_msg.len) अणु
			/*
			 * Check अगर the bus has been मुक्त क्रम दीर्घ enough
			 * so we can kick off the pending transmit.
			 */
			delta = kसमय_us_delta(ts, pin->ts);
			अगर (delta / CEC_TIM_DATA_BIT_TOTAL >
			    pin->tx_संकेत_मुक्त_समय) अणु
				pin->tx_nacked = false;
				अगर (tx_custom_start(pin))
					pin->state = CEC_ST_TX_START_BIT_LOW_CUSTOM;
				अन्यथा
					pin->state = CEC_ST_TX_START_BIT_LOW;
				/* Generate start bit */
				cec_pin_low(pin);
				अवरोध;
			पूर्ण
			अगर (delta / CEC_TIM_DATA_BIT_TOTAL >
			    pin->tx_संकेत_मुक्त_समय - 1)
				pin->state = CEC_ST_TX_WAIT;
			अवरोध;
		पूर्ण
		अगर (pin->tx_custom_pulse && pin->state == CEC_ST_IDLE) अणु
			pin->tx_custom_pulse = false;
			/* Generate custom pulse */
			cec_pin_low(pin);
			pin->state = CEC_ST_TX_PULSE_LOW_CUSTOM;
			अवरोध;
		पूर्ण
		अगर (pin->state != CEC_ST_IDLE || pin->ops->enable_irq == शून्य ||
		    pin->enable_irq_failed || adap->is_configuring ||
		    adap->is_configured || adap->monitor_all_cnt)
			अवरोध;
		/* Switch to पूर्णांकerrupt mode */
		atomic_set(&pin->work_irq_change, CEC_PIN_IRQ_ENABLE);
		pin->state = CEC_ST_RX_IRQ;
		wake_up_पूर्णांकerruptible(&pin->kthपढ़ो_रुकोq);
		वापस HRTIMER_NORESTART;

	हाल CEC_ST_TX_LOW_DRIVE:
	हाल CEC_ST_RX_LOW_DRIVE:
		cec_pin_high(pin);
		cec_pin_to_idle(pin);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	चयन (pin->state) अणु
	हाल CEC_ST_TX_START_BIT_LOW_CUSTOM:
	हाल CEC_ST_TX_DATA_BIT_LOW_CUSTOM:
	हाल CEC_ST_TX_PULSE_LOW_CUSTOM:
		usecs = pin->tx_custom_low_usecs;
		अवरोध;
	हाल CEC_ST_TX_START_BIT_HIGH_CUSTOM:
	हाल CEC_ST_TX_DATA_BIT_HIGH_CUSTOM:
	हाल CEC_ST_TX_PULSE_HIGH_CUSTOM:
		usecs = pin->tx_custom_high_usecs;
		अवरोध;
	शेष:
		usecs = states[pin->state].usecs;
		अवरोध;
	पूर्ण

	अगर (!adap->monitor_pin_cnt || usecs <= 150) अणु
		pin->रुको_usecs = 0;
		pin->समयr_ts = kसमय_add_us(ts, usecs);
		hrसमयr_क्रमward_now(समयr,
				ns_to_kसमय(usecs * 1000));
		वापस HRTIMER_RESTART;
	पूर्ण
	pin->रुको_usecs = usecs - 100;
	pin->समयr_ts = kसमय_add_us(ts, 100);
	hrसमयr_क्रमward_now(समयr, ns_to_kसमय(100000));
	वापस HRTIMER_RESTART;
पूर्ण

अटल पूर्णांक cec_pin_thपढ़ो_func(व्योम *_adap)
अणु
	काष्ठा cec_adapter *adap = _adap;
	काष्ठा cec_pin *pin = adap->pin;

	क्रम (;;) अणु
		रुको_event_पूर्णांकerruptible(pin->kthपढ़ो_रुकोq,
			kthपढ़ो_should_stop() ||
			pin->work_rx_msg.len ||
			pin->work_tx_status ||
			atomic_पढ़ो(&pin->work_irq_change) ||
			atomic_पढ़ो(&pin->work_pin_num_events));

		अगर (pin->work_rx_msg.len) अणु
			काष्ठा cec_msg *msg = &pin->work_rx_msg;

			अगर (msg->len > 1 && msg->len < CEC_MAX_MSG_SIZE &&
			    rx_add_byte(pin)) अणु
				/* Error injection: add byte to the message */
				msg->msg[msg->len++] = 0x55;
			पूर्ण
			अगर (msg->len > 2 && rx_हटाओ_byte(pin)) अणु
				/* Error injection: हटाओ byte from message */
				msg->len--;
			पूर्ण
			अगर (msg->len > CEC_MAX_MSG_SIZE)
				msg->len = CEC_MAX_MSG_SIZE;
			cec_received_msg_ts(adap, msg,
				ns_to_kसमय(pin->work_rx_msg.rx_ts));
			msg->len = 0;
		पूर्ण
		अगर (pin->work_tx_status) अणु
			अचिन्हित पूर्णांक tx_status = pin->work_tx_status;

			pin->work_tx_status = 0;
			cec_transmit_attempt_करोne_ts(adap, tx_status,
						     pin->work_tx_ts);
		पूर्ण

		जबतक (atomic_पढ़ो(&pin->work_pin_num_events)) अणु
			अचिन्हित पूर्णांक idx = pin->work_pin_events_rd;
			u8 v = pin->work_pin_events[idx];

			cec_queue_pin_cec_event(adap,
						v & CEC_PIN_EVENT_FL_IS_HIGH,
						v & CEC_PIN_EVENT_FL_DROPPED,
						pin->work_pin_ts[idx]);
			pin->work_pin_events_rd = (idx + 1) % CEC_NUM_PIN_EVENTS;
			atomic_dec(&pin->work_pin_num_events);
		पूर्ण

		चयन (atomic_xchg(&pin->work_irq_change,
				    CEC_PIN_IRQ_UNCHANGED)) अणु
		हाल CEC_PIN_IRQ_DISABLE:
			pin->ops->disable_irq(adap);
			cec_pin_high(pin);
			cec_pin_to_idle(pin);
			hrसमयr_start(&pin->समयr, ns_to_kसमय(0),
				      HRTIMER_MODE_REL);
			अवरोध;
		हाल CEC_PIN_IRQ_ENABLE:
			pin->enable_irq_failed = !pin->ops->enable_irq(adap);
			अगर (pin->enable_irq_failed) अणु
				cec_pin_to_idle(pin);
				hrसमयr_start(&pin->समयr, ns_to_kसमय(0),
					      HRTIMER_MODE_REL);
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (kthपढ़ो_should_stop())
			अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cec_pin_adap_enable(काष्ठा cec_adapter *adap, bool enable)
अणु
	काष्ठा cec_pin *pin = adap->pin;

	pin->enabled = enable;
	अगर (enable) अणु
		atomic_set(&pin->work_pin_num_events, 0);
		pin->work_pin_events_rd = pin->work_pin_events_wr = 0;
		pin->work_pin_events_dropped = false;
		cec_pin_पढ़ो(pin);
		cec_pin_to_idle(pin);
		pin->tx_msg.len = 0;
		pin->समयr_ts = ns_to_kसमय(0);
		atomic_set(&pin->work_irq_change, CEC_PIN_IRQ_UNCHANGED);
		pin->kthपढ़ो = kthपढ़ो_run(cec_pin_thपढ़ो_func, adap,
					   "cec-pin");
		अगर (IS_ERR(pin->kthपढ़ो)) अणु
			pr_err("cec-pin: kernel_thread() failed\n");
			वापस PTR_ERR(pin->kthपढ़ो);
		पूर्ण
		hrसमयr_start(&pin->समयr, ns_to_kसमय(0),
			      HRTIMER_MODE_REL);
	पूर्ण अन्यथा अणु
		अगर (pin->ops->disable_irq)
			pin->ops->disable_irq(adap);
		hrसमयr_cancel(&pin->समयr);
		kthपढ़ो_stop(pin->kthपढ़ो);
		cec_pin_पढ़ो(pin);
		cec_pin_to_idle(pin);
		pin->state = CEC_ST_OFF;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cec_pin_adap_log_addr(काष्ठा cec_adapter *adap, u8 log_addr)
अणु
	काष्ठा cec_pin *pin = adap->pin;

	अगर (log_addr == CEC_LOG_ADDR_INVALID)
		pin->la_mask = 0;
	अन्यथा
		pin->la_mask |= (1 << log_addr);
	वापस 0;
पूर्ण

व्योम cec_pin_start_समयr(काष्ठा cec_pin *pin)
अणु
	अगर (pin->state != CEC_ST_RX_IRQ)
		वापस;

	atomic_set(&pin->work_irq_change, CEC_PIN_IRQ_UNCHANGED);
	pin->ops->disable_irq(pin->adap);
	cec_pin_high(pin);
	cec_pin_to_idle(pin);
	hrसमयr_start(&pin->समयr, ns_to_kसमय(0), HRTIMER_MODE_REL);
पूर्ण

अटल पूर्णांक cec_pin_adap_transmit(काष्ठा cec_adapter *adap, u8 attempts,
				      u32 संकेत_मुक्त_समय, काष्ठा cec_msg *msg)
अणु
	काष्ठा cec_pin *pin = adap->pin;

	/*
	 * If a receive is in progress, then this transmit should use
	 * a संकेत मुक्त समय of max CEC_SIGNAL_FREE_TIME_NEW_INITIATOR
	 * since when it starts transmitting it will have a new initiator.
	 */
	अगर (pin->state != CEC_ST_IDLE &&
	    संकेत_मुक्त_समय > CEC_SIGNAL_FREE_TIME_NEW_INITIATOR)
		संकेत_मुक्त_समय = CEC_SIGNAL_FREE_TIME_NEW_INITIATOR;

	pin->tx_संकेत_मुक्त_समय = संकेत_मुक्त_समय;
	pin->tx_extra_bytes = 0;
	pin->tx_msg = *msg;
	अगर (msg->len > 1) अणु
		/* Error injection: add byte to the message */
		pin->tx_extra_bytes = tx_add_bytes(pin);
	पूर्ण
	अगर (msg->len > 2 && tx_हटाओ_byte(pin)) अणु
		/* Error injection: हटाओ byte from the message */
		pin->tx_msg.len--;
	पूर्ण
	pin->work_tx_status = 0;
	pin->tx_bit = 0;
	cec_pin_start_समयr(pin);
	वापस 0;
पूर्ण

अटल व्योम cec_pin_adap_status(काष्ठा cec_adapter *adap,
				       काष्ठा seq_file *file)
अणु
	काष्ठा cec_pin *pin = adap->pin;

	seq_म_लिखो(file, "state: %s\n", states[pin->state].name);
	seq_म_लिखो(file, "tx_bit: %d\n", pin->tx_bit);
	seq_म_लिखो(file, "rx_bit: %d\n", pin->rx_bit);
	seq_म_लिखो(file, "cec pin: %d\n", pin->ops->पढ़ो(adap));
	seq_म_लिखो(file, "cec pin events dropped: %u\n",
		   pin->work_pin_events_dropped_cnt);
	seq_म_लिखो(file, "irq failed: %d\n", pin->enable_irq_failed);
	अगर (pin->समयr_100ms_overruns) अणु
		seq_म_लिखो(file, "timer overruns > 100ms: %u of %u\n",
			   pin->समयr_100ms_overruns, pin->समयr_cnt);
		seq_म_लिखो(file, "timer overruns > 300ms: %u of %u\n",
			   pin->समयr_300ms_overruns, pin->समयr_cnt);
		seq_म_लिखो(file, "max timer overrun: %u usecs\n",
			   pin->समयr_max_overrun);
		seq_म_लिखो(file, "avg timer overrun: %u usecs\n",
			   pin->समयr_sum_overrun / pin->समयr_100ms_overruns);
	पूर्ण
	अगर (pin->rx_start_bit_low_too_लघु_cnt)
		seq_म_लिखो(file,
			   "rx start bit low too short: %u (delta %u, ts %llu)\n",
			   pin->rx_start_bit_low_too_लघु_cnt,
			   pin->rx_start_bit_low_too_लघु_delta,
			   pin->rx_start_bit_low_too_लघु_ts);
	अगर (pin->rx_start_bit_too_लघु_cnt)
		seq_म_लिखो(file,
			   "rx start bit too short: %u (delta %u, ts %llu)\n",
			   pin->rx_start_bit_too_लघु_cnt,
			   pin->rx_start_bit_too_लघु_delta,
			   pin->rx_start_bit_too_लघु_ts);
	अगर (pin->rx_start_bit_too_दीर्घ_cnt)
		seq_म_लिखो(file, "rx start bit too long: %u\n",
			   pin->rx_start_bit_too_दीर्घ_cnt);
	अगर (pin->rx_data_bit_too_लघु_cnt)
		seq_म_लिखो(file,
			   "rx data bit too short: %u (delta %u, ts %llu)\n",
			   pin->rx_data_bit_too_लघु_cnt,
			   pin->rx_data_bit_too_लघु_delta,
			   pin->rx_data_bit_too_लघु_ts);
	अगर (pin->rx_data_bit_too_दीर्घ_cnt)
		seq_म_लिखो(file, "rx data bit too long: %u\n",
			   pin->rx_data_bit_too_दीर्घ_cnt);
	seq_म_लिखो(file, "rx initiated low drive: %u\n", pin->rx_low_drive_cnt);
	seq_म_लिखो(file, "tx detected low drive: %u\n", pin->tx_low_drive_cnt);
	pin->work_pin_events_dropped_cnt = 0;
	pin->समयr_cnt = 0;
	pin->समयr_100ms_overruns = 0;
	pin->समयr_300ms_overruns = 0;
	pin->समयr_max_overrun = 0;
	pin->समयr_sum_overrun = 0;
	pin->rx_start_bit_low_too_लघु_cnt = 0;
	pin->rx_start_bit_too_लघु_cnt = 0;
	pin->rx_start_bit_too_दीर्घ_cnt = 0;
	pin->rx_data_bit_too_लघु_cnt = 0;
	pin->rx_data_bit_too_दीर्घ_cnt = 0;
	pin->rx_low_drive_cnt = 0;
	pin->tx_low_drive_cnt = 0;
	अगर (pin->ops->status)
		pin->ops->status(adap, file);
पूर्ण

अटल पूर्णांक cec_pin_adap_monitor_all_enable(काष्ठा cec_adapter *adap,
						  bool enable)
अणु
	काष्ठा cec_pin *pin = adap->pin;

	pin->monitor_all = enable;
	वापस 0;
पूर्ण

अटल व्योम cec_pin_adap_मुक्त(काष्ठा cec_adapter *adap)
अणु
	काष्ठा cec_pin *pin = adap->pin;

	अगर (pin->ops->मुक्त)
		pin->ops->मुक्त(adap);
	adap->pin = शून्य;
	kमुक्त(pin);
पूर्ण

अटल पूर्णांक cec_pin_received(काष्ठा cec_adapter *adap, काष्ठा cec_msg *msg)
अणु
	काष्ठा cec_pin *pin = adap->pin;

	अगर (pin->ops->received)
		वापस pin->ops->received(adap, msg);
	वापस -ENOMSG;
पूर्ण

व्योम cec_pin_changed(काष्ठा cec_adapter *adap, bool value)
अणु
	काष्ठा cec_pin *pin = adap->pin;

	cec_pin_update(pin, value, false);
	अगर (!value && (adap->is_configuring || adap->is_configured ||
		       adap->monitor_all_cnt))
		atomic_set(&pin->work_irq_change, CEC_PIN_IRQ_DISABLE);
पूर्ण
EXPORT_SYMBOL_GPL(cec_pin_changed);

अटल स्थिर काष्ठा cec_adap_ops cec_pin_adap_ops = अणु
	.adap_enable = cec_pin_adap_enable,
	.adap_monitor_all_enable = cec_pin_adap_monitor_all_enable,
	.adap_log_addr = cec_pin_adap_log_addr,
	.adap_transmit = cec_pin_adap_transmit,
	.adap_status = cec_pin_adap_status,
	.adap_मुक्त = cec_pin_adap_मुक्त,
#अगर_घोषित CONFIG_CEC_PIN_ERROR_INJ
	.error_inj_parse_line = cec_pin_error_inj_parse_line,
	.error_inj_show = cec_pin_error_inj_show,
#पूर्ण_अगर
	.received = cec_pin_received,
पूर्ण;

काष्ठा cec_adapter *cec_pin_allocate_adapter(स्थिर काष्ठा cec_pin_ops *pin_ops,
					व्योम *priv, स्थिर अक्षर *name, u32 caps)
अणु
	काष्ठा cec_adapter *adap;
	काष्ठा cec_pin *pin = kzalloc(माप(*pin), GFP_KERNEL);

	अगर (pin == शून्य)
		वापस ERR_PTR(-ENOMEM);
	pin->ops = pin_ops;
	hrसमयr_init(&pin->समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	pin->समयr.function = cec_pin_समयr;
	init_रुकोqueue_head(&pin->kthपढ़ो_रुकोq);
	pin->tx_custom_low_usecs = CEC_TIM_CUSTOM_DEFAULT;
	pin->tx_custom_high_usecs = CEC_TIM_CUSTOM_DEFAULT;

	adap = cec_allocate_adapter(&cec_pin_adap_ops, priv, name,
			    caps | CEC_CAP_MONITOR_ALL | CEC_CAP_MONITOR_PIN,
			    CEC_MAX_LOG_ADDRS);

	अगर (IS_ERR(adap)) अणु
		kमुक्त(pin);
		वापस adap;
	पूर्ण

	adap->pin = pin;
	pin->adap = adap;
	cec_pin_update(pin, cec_pin_high(pin), true);
	वापस adap;
पूर्ण
EXPORT_SYMBOL_GPL(cec_pin_allocate_adapter);
