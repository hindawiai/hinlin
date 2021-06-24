<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * include/linux/TODO
 *
 * userspace पूर्णांकerface क्रम pi433 radio module
 *
 * Pi433 is a 433MHz radio module क्रम the Raspberry Pi.
 * It is based on the HopeRf Module RFM69CW. Thereक्रमe inside of this
 * driver, you'll find an असलtraction of the rf69 chip.
 *
 * If needed, this driver could be extended, to also support other
 * devices, basing on HopeRfs rf69.
 *
 * The driver can also be extended, to support other modules of
 * HopeRf with a similar पूर्णांकerace - e. g. RFM69HCW, RFM12, RFM95, ...
 * Copyright (C) 2016 Wolf-Entwicklungen
 *	Marcus Wolf <linux@wolf-entwicklungen.de>
 */

#अगर_अघोषित PI433_H
#घोषणा PI433_H

#समावेश <linux/types.h>
#समावेश "rf69_enum.h"

/*---------------------------------------------------------------------------*/

क्रमागत option_on_off अणु
	OPTION_OFF,
	OPTION_ON
पूर्ण;

/* IOCTL काष्ठाs and commands */

/**
 * काष्ठा pi433_tx_config
 * describes the configuration of the radio module क्रम sending
 * @frequency:
 * @bit_rate:
 * @modulation:
 * @data_mode:
 * @preamble_length:
 * @sync_pattern:
 * @tx_start_condition:
 * @payload_length:
 * @repetitions:
 *
 * ATTENTION:
 * If the contents of 'pi433_tx_config' ever change
 * incompatibly, then the ioctl number (see define below) must change.
 *
 * NOTE: काष्ठा layout is the same in 64bit and 32bit userspace.
 */
#घोषणा PI433_TX_CFG_IOCTL_NR	0
काष्ठा pi433_tx_cfg अणु
	__u32			frequency;
	__u16			bit_rate;
	__u32			dev_frequency;
	क्रमागत modulation		modulation;
	क्रमागत mod_shaping	mod_shaping;

	क्रमागत pa_ramp		pa_ramp;

	क्रमागत tx_start_condition	tx_start_condition;

	__u16			repetitions;

	/* packet क्रमmat */
	क्रमागत option_on_off	enable_preamble;
	क्रमागत option_on_off	enable_sync;
	क्रमागत option_on_off	enable_length_byte;
	क्रमागत option_on_off	enable_address_byte;
	क्रमागत option_on_off	enable_crc;

	__u16			preamble_length;
	__u8			sync_length;
	__u8			fixed_message_length;

	__u8			sync_pattern[8];
	__u8			address_byte;
पूर्ण;

/**
 * काष्ठा pi433_rx_config
 * describes the configuration of the radio module क्रम sending
 * @frequency:
 * @bit_rate:
 * @modulation:
 * @data_mode:
 * @preamble_length:
 * @sync_pattern:
 * @tx_start_condition:
 * @payload_length:
 * @repetitions:
 *
 * ATTENTION:
 * If the contents of 'pi433_rx_config' ever change
 * incompatibly, then the ioctl number (see define below) must change
 *
 * NOTE: काष्ठा layout is the same in 64bit and 32bit userspace.
 */
#घोषणा PI433_RX_CFG_IOCTL_NR	1
काष्ठा pi433_rx_cfg अणु
	__u32			frequency;
	__u16			bit_rate;
	__u32			dev_frequency;

	क्रमागत modulation		modulation;

	__u8			rssi_threshold;
	क्रमागत threshold_decrement threshold_decrement;
	क्रमागत antenna_impedance	antenna_impedance;
	क्रमागत lna_gain		lna_gain;
	क्रमागत mantisse		bw_mantisse;	/* normal: 0x50 */
	__u8			bw_exponent;	/* during AFC: 0x8b */
	क्रमागत dagc		dagc;

	/* packet क्रमmat */
	क्रमागत option_on_off	enable_sync;

	/* should be used in combination with sync, only */
	क्रमागत option_on_off	enable_length_byte;

	/* operational with sync, only */
	क्रमागत address_filtering	enable_address_filtering;

	/* only operational, अगर sync on and fixed length or length byte is used */
	क्रमागत option_on_off	enable_crc;

	__u8			sync_length;
	__u8			fixed_message_length;
	__u32			bytes_to_drop;

	__u8			sync_pattern[8];
	__u8			node_address;
	__u8			broadcast_address;
पूर्ण;

#घोषणा PI433_IOC_MAGIC	'r'

#घोषणा PI433_IOC_RD_TX_CFG                                             \
	_IOR(PI433_IOC_MAGIC, PI433_TX_CFG_IOCTL_NR, अक्षर[माप(काष्ठा pi433_tx_cfg)])
#घोषणा PI433_IOC_WR_TX_CFG                                             \
	_IOW(PI433_IOC_MAGIC, PI433_TX_CFG_IOCTL_NR, अक्षर[माप(काष्ठा pi433_tx_cfg)])

#घोषणा PI433_IOC_RD_RX_CFG                                             \
	_IOR(PI433_IOC_MAGIC, PI433_RX_CFG_IOCTL_NR, अक्षर[माप(काष्ठा pi433_rx_cfg)])
#घोषणा PI433_IOC_WR_RX_CFG                                             \
	_IOW(PI433_IOC_MAGIC, PI433_RX_CFG_IOCTL_NR, अक्षर[माप(काष्ठा pi433_rx_cfg)])

#पूर्ण_अगर /* PI433_H */
