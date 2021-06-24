<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * क्रमागतerations क्रम HopeRf rf69 radio module
 *
 * Copyright (C) 2016 Wolf-Entwicklungen
 *	Marcus Wolf <linux@wolf-entwicklungen.de>
 */

#अगर_अघोषित RF69_ENUM_H
#घोषणा RF69_ENUM_H

क्रमागत mode अणु
	mode_sleep,
	standby,
	synthesizer,
	transmit,
	receive
पूर्ण;

क्रमागत modulation अणु
	OOK,
	FSK,
	UNDEF
पूर्ण;

क्रमागत mod_shaping अणु
	SHAPING_OFF,
	SHAPING_1_0,
	SHAPING_0_5,
	SHAPING_0_3,
	SHAPING_BR,
	SHAPING_2BR
पूर्ण;

क्रमागत pa_ramp अणु
	ramp3400,
	ramp2000,
	ramp1000,
	ramp500,
	ramp250,
	ramp125,
	ramp100,
	ramp62,
	ramp50,
	ramp40,
	ramp31,
	ramp25,
	ramp20,
	ramp15,
	ramp12,
	ramp10
पूर्ण;

क्रमागत antenna_impedance अणु
	fअगरty_ohm,
	two_hundred_ohm
पूर्ण;

क्रमागत lna_gain अणु
	स्वतःmatic,
	max,
	max_minus_6,
	max_minus_12,
	max_minus_24,
	max_minus_36,
	max_minus_48,
	undefined
पूर्ण;

क्रमागत mantisse अणु
	mantisse16,
	mantisse20,
	mantisse24
पूर्ण;

क्रमागत threshold_decrement अणु
	dec_every8th,
	dec_every4th,
	dec_every2nd,
	dec_once,
	dec_twice,
	dec_4बार,
	dec_8बार,
	dec_16बार
पूर्ण;

क्रमागत flag अणु
	mode_चयन_completed,
	पढ़ोy_to_receive,
	पढ़ोy_to_send,
	pll_locked,
	rssi_exceeded_threshold,
	समयout,
	स्वतःmode,
	sync_address_match,
	fअगरo_full,
//	fअगरo_not_empty, collision with next क्रमागत; replaced by following क्रमागत...
	fअगरo_empty,
	fअगरo_level_below_threshold,
	fअगरo_overrun,
	packet_sent,
	payload_पढ़ोy,
	crc_ok,
	battery_low
पूर्ण;

क्रमागत fअगरo_fill_condition अणु
	after_sync_पूर्णांकerrupt,
	always
पूर्ण;

क्रमागत packet_क्रमmat अणु
	packet_length_fix,
	packet_length_var
पूर्ण;

क्रमागत tx_start_condition अणु
	fअगरo_level,
	fअगरo_not_empty
पूर्ण;

क्रमागत address_filtering अणु
	filtering_off,
	node_address,
	node_or_broadcast_address
पूर्ण;

क्रमागत dagc अणु
	normal_mode,
	improve,
	improve_क्रम_low_modulation_index
पूर्ण;

#पूर्ण_अगर
