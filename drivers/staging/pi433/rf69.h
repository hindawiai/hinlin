<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * hardware असलtraction/रेजिस्टर access क्रम HopeRf rf69 radio module
 *
 * Copyright (C) 2016 Wolf-Entwicklungen
 *	Marcus Wolf <linux@wolf-entwicklungen.de>
 */
#अगर_अघोषित RF69_H
#घोषणा RF69_H

#समावेश "rf69_enum.h"
#समावेश "rf69_registers.h"

/* NOTE: Modअगरying FREQUENCY value impacts CE certअगरication */
#घोषणा F_OSC		32000000	/* Hz */
#घोषणा FREQUENCY	433920000	/* Hz */
#घोषणा FIFO_SIZE	66		/* bytes */
#घोषणा FIFO_THRESHOLD	15		/* bytes */

पूर्णांक rf69_set_mode(काष्ठा spi_device *spi, क्रमागत mode mode);
पूर्णांक rf69_set_data_mode(काष्ठा spi_device *spi, u8 data_mode);
पूर्णांक rf69_set_modulation(काष्ठा spi_device *spi, क्रमागत modulation modulation);
पूर्णांक rf69_set_modulation_shaping(काष्ठा spi_device *spi,
				क्रमागत mod_shaping mod_shaping);
पूर्णांक rf69_set_bit_rate(काष्ठा spi_device *spi, u16 bit_rate);
पूर्णांक rf69_set_deviation(काष्ठा spi_device *spi, u32 deviation);
पूर्णांक rf69_set_frequency(काष्ठा spi_device *spi, u32 frequency);
पूर्णांक rf69_enable_amplअगरier(काष्ठा spi_device *spi, u8 amplअगरier_mask);
पूर्णांक rf69_disable_amplअगरier(काष्ठा spi_device *spi, u8 amplअगरier_mask);
पूर्णांक rf69_set_output_घातer_level(काष्ठा spi_device *spi, u8 घातer_level);
पूर्णांक rf69_set_pa_ramp(काष्ठा spi_device *spi, क्रमागत pa_ramp pa_ramp);
पूर्णांक rf69_set_antenna_impedance(काष्ठा spi_device *spi,
			       क्रमागत antenna_impedance antenna_impedance);
पूर्णांक rf69_set_lna_gain(काष्ठा spi_device *spi, क्रमागत lna_gain lna_gain);
पूर्णांक rf69_set_bandwidth(काष्ठा spi_device *spi, क्रमागत mantisse mantisse,
		       u8 exponent);
पूर्णांक rf69_set_bandwidth_during_afc(काष्ठा spi_device *spi,
				  क्रमागत mantisse mantisse,
				  u8 exponent);
पूर्णांक rf69_set_ook_threshold_dec(काष्ठा spi_device *spi,
			       क्रमागत threshold_decrement threshold_decrement);
पूर्णांक rf69_set_dio_mapping(काष्ठा spi_device *spi, u8 dio_number, u8 value);
bool rf69_get_flag(काष्ठा spi_device *spi, क्रमागत flag flag);
पूर्णांक rf69_set_rssi_threshold(काष्ठा spi_device *spi, u8 threshold);
पूर्णांक rf69_set_preamble_length(काष्ठा spi_device *spi, u16 preamble_length);
पूर्णांक rf69_enable_sync(काष्ठा spi_device *spi);
पूर्णांक rf69_disable_sync(काष्ठा spi_device *spi);
पूर्णांक rf69_set_fअगरo_fill_condition(काष्ठा spi_device *spi,
				 क्रमागत fअगरo_fill_condition fअगरo_fill_condition);
पूर्णांक rf69_set_sync_size(काष्ठा spi_device *spi, u8 sync_size);
पूर्णांक rf69_set_sync_values(काष्ठा spi_device *spi, u8 sync_values[8]);
पूर्णांक rf69_set_packet_क्रमmat(काष्ठा spi_device *spi,
			   क्रमागत packet_क्रमmat packet_क्रमmat);
पूर्णांक rf69_enable_crc(काष्ठा spi_device *spi);
पूर्णांक rf69_disable_crc(काष्ठा spi_device *spi);
पूर्णांक rf69_set_address_filtering(काष्ठा spi_device *spi,
			       क्रमागत address_filtering address_filtering);
पूर्णांक rf69_set_payload_length(काष्ठा spi_device *spi, u8 payload_length);
पूर्णांक rf69_set_node_address(काष्ठा spi_device *spi, u8 node_address);
पूर्णांक rf69_set_broadcast_address(काष्ठा spi_device *spi, u8 broadcast_address);
पूर्णांक rf69_set_tx_start_condition(काष्ठा spi_device *spi,
				क्रमागत tx_start_condition tx_start_condition);
पूर्णांक rf69_set_fअगरo_threshold(काष्ठा spi_device *spi, u8 threshold);
पूर्णांक rf69_set_dagc(काष्ठा spi_device *spi, क्रमागत dagc dagc);

पूर्णांक rf69_पढ़ो_fअगरo(काष्ठा spi_device *spi, u8 *buffer, अचिन्हित पूर्णांक size);
पूर्णांक rf69_ग_लिखो_fअगरo(काष्ठा spi_device *spi, u8 *buffer, अचिन्हित पूर्णांक size);

#पूर्ण_अगर
