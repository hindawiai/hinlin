<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only WITH Linux-syscall-note */
/*
 * linux/can/netlink.h
 *
 * Definitions क्रम the CAN netlink पूर्णांकerface
 *
 * Copyright (c) 2009 Wolfgang Gअक्रमegger <wg@gअक्रमegger.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the version 2 of the GNU General Public License
 * as published by the Free Software Foundation
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित _UAPI_CAN_NETLINK_H
#घोषणा _UAPI_CAN_NETLINK_H

#समावेश <linux/types.h>

/*
 * CAN bit-timing parameters
 *
 * For further inक्रमmation, please पढ़ो chapter "8 BIT TIMING
 * REQUIREMENTS" of the "Bosch CAN Specअगरication version 2.0"
 * at http://www.semiconductors.bosch.de/pdf/can2spec.pdf.
 */
काष्ठा can_bittiming अणु
	__u32 bitrate;		/* Bit-rate in bits/second */
	__u32 sample_poपूर्णांक;	/* Sample poपूर्णांक in one-tenth of a percent */
	__u32 tq;		/* Time quanta (TQ) in nanoseconds */
	__u32 prop_seg;		/* Propagation segment in TQs */
	__u32 phase_seg1;	/* Phase buffer segment 1 in TQs */
	__u32 phase_seg2;	/* Phase buffer segment 2 in TQs */
	__u32 sjw;		/* Synchronisation jump width in TQs */
	__u32 brp;		/* Bit-rate prescaler */
पूर्ण;

/*
 * CAN hardware-dependent bit-timing स्थिरant
 *
 * Used क्रम calculating and checking bit-timing parameters
 */
काष्ठा can_bittiming_स्थिर अणु
	अक्षर name[16];		/* Name of the CAN controller hardware */
	__u32 tseg1_min;	/* Time segment 1 = prop_seg + phase_seg1 */
	__u32 tseg1_max;
	__u32 tseg2_min;	/* Time segment 2 = phase_seg2 */
	__u32 tseg2_max;
	__u32 sjw_max;		/* Synchronisation jump width */
	__u32 brp_min;		/* Bit-rate prescaler */
	__u32 brp_max;
	__u32 brp_inc;
पूर्ण;

/*
 * CAN घड़ी parameters
 */
काष्ठा can_घड़ी अणु
	__u32 freq;		/* CAN प्रणाली घड़ी frequency in Hz */
पूर्ण;

/*
 * CAN operational and error states
 */
क्रमागत can_state अणु
	CAN_STATE_ERROR_ACTIVE = 0,	/* RX/TX error count < 96 */
	CAN_STATE_ERROR_WARNING,	/* RX/TX error count < 128 */
	CAN_STATE_ERROR_PASSIVE,	/* RX/TX error count < 256 */
	CAN_STATE_BUS_OFF,		/* RX/TX error count >= 256 */
	CAN_STATE_STOPPED,		/* Device is stopped */
	CAN_STATE_SLEEPING,		/* Device is sleeping */
	CAN_STATE_MAX
पूर्ण;

/*
 * CAN bus error counters
 */
काष्ठा can_berr_counter अणु
	__u16 txerr;
	__u16 rxerr;
पूर्ण;

/*
 * CAN controller mode
 */
काष्ठा can_ctrlmode अणु
	__u32 mask;
	__u32 flags;
पूर्ण;

#घोषणा CAN_CTRLMODE_LOOPBACK		0x01	/* Loopback mode */
#घोषणा CAN_CTRLMODE_LISTENONLY		0x02	/* Listen-only mode */
#घोषणा CAN_CTRLMODE_3_SAMPLES		0x04	/* Triple sampling mode */
#घोषणा CAN_CTRLMODE_ONE_SHOT		0x08	/* One-Shot mode */
#घोषणा CAN_CTRLMODE_BERR_REPORTING	0x10	/* Bus-error reporting */
#घोषणा CAN_CTRLMODE_FD			0x20	/* CAN FD mode */
#घोषणा CAN_CTRLMODE_PRESUME_ACK	0x40	/* Ignore missing CAN ACKs */
#घोषणा CAN_CTRLMODE_FD_NON_ISO		0x80	/* CAN FD in non-ISO mode */
#घोषणा CAN_CTRLMODE_CC_LEN8_DLC	0x100	/* Classic CAN DLC option */

/*
 * CAN device statistics
 */
काष्ठा can_device_stats अणु
	__u32 bus_error;	/* Bus errors */
	__u32 error_warning;	/* Changes to error warning state */
	__u32 error_passive;	/* Changes to error passive state */
	__u32 bus_off;		/* Changes to bus off state */
	__u32 arbitration_lost; /* Arbitration lost errors */
	__u32 restarts;		/* CAN controller re-starts */
पूर्ण;

/*
 * CAN netlink पूर्णांकerface
 */
क्रमागत अणु
	IFLA_CAN_UNSPEC,
	IFLA_CAN_BITTIMING,
	IFLA_CAN_BITTIMING_CONST,
	IFLA_CAN_CLOCK,
	IFLA_CAN_STATE,
	IFLA_CAN_CTRLMODE,
	IFLA_CAN_RESTART_MS,
	IFLA_CAN_RESTART,
	IFLA_CAN_BERR_COUNTER,
	IFLA_CAN_DATA_BITTIMING,
	IFLA_CAN_DATA_BITTIMING_CONST,
	IFLA_CAN_TERMINATION,
	IFLA_CAN_TERMINATION_CONST,
	IFLA_CAN_BITRATE_CONST,
	IFLA_CAN_DATA_BITRATE_CONST,
	IFLA_CAN_BITRATE_MAX,
	__IFLA_CAN_MAX
पूर्ण;

#घोषणा IFLA_CAN_MAX	(__IFLA_CAN_MAX - 1)

/* u16 termination range: 1..65535 Ohms */
#घोषणा CAN_TERMINATION_DISABLED 0

#पूर्ण_अगर /* !_UAPI_CAN_NETLINK_H */
