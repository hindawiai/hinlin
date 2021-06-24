<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only WITH Linux-syscall-note */
/*
 * j1939.h
 *
 * Copyright (c) 2010-2011 EIA Electronics
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#अगर_अघोषित _UAPI_CAN_J1939_H_
#घोषणा _UAPI_CAN_J1939_H_

#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/can.h>

#घोषणा J1939_MAX_UNICAST_ADDR 0xfd
#घोषणा J1939_IDLE_ADDR 0xfe
#घोषणा J1939_NO_ADDR 0xff		/* == broadcast or no addr */
#घोषणा J1939_NO_NAME 0
#घोषणा J1939_PGN_REQUEST 0x0ea00		/* Request PG */
#घोषणा J1939_PGN_ADDRESS_CLAIMED 0x0ee00	/* Address Claimed */
#घोषणा J1939_PGN_ADDRESS_COMMANDED 0x0fed8	/* Commanded Address */
#घोषणा J1939_PGN_PDU1_MAX 0x3ff00
#घोषणा J1939_PGN_MAX 0x3ffff
#घोषणा J1939_NO_PGN 0x40000

/* J1939 Parameter Group Number
 *
 * bit 0-7	: PDU Specअगरic (PS)
 * bit 8-15	: PDU Format (PF)
 * bit 16	: Data Page (DP)
 * bit 17	: Reserved (R)
 * bit 19-31	: set to zero
 */
प्रकार __u32 pgn_t;

/* J1939 Priority
 *
 * bit 0-2	: Priority (P)
 * bit 3-7	: set to zero
 */
प्रकार __u8 priority_t;

/* J1939 NAME
 *
 * bit 0-20	: Identity Number
 * bit 21-31	: Manufacturer Code
 * bit 32-34	: ECU Instance
 * bit 35-39	: Function Instance
 * bit 40-47	: Function
 * bit 48	: Reserved
 * bit 49-55	: Vehicle System
 * bit 56-59	: Vehicle System Instance
 * bit 60-62	: Industry Group
 * bit 63	: Arbitrary Address Capable
 */
प्रकार __u64 name_t;

/* J1939 socket options */
#घोषणा SOL_CAN_J1939 (SOL_CAN_BASE + CAN_J1939)
क्रमागत अणु
	SO_J1939_FILTER = 1,	/* set filters */
	SO_J1939_PROMISC = 2,	/* set/clr promiscuous mode */
	SO_J1939_SEND_PRIO = 3,
	SO_J1939_ERRQUEUE = 4,
पूर्ण;

क्रमागत अणु
	SCM_J1939_DEST_ADDR = 1,
	SCM_J1939_DEST_NAME = 2,
	SCM_J1939_PRIO = 3,
	SCM_J1939_ERRQUEUE = 4,
पूर्ण;

क्रमागत अणु
	J1939_NLA_PAD,
	J1939_NLA_BYTES_ACKED,
पूर्ण;

क्रमागत अणु
	J1939_EE_INFO_NONE,
	J1939_EE_INFO_TX_ABORT,
पूर्ण;

काष्ठा j1939_filter अणु
	name_t name;
	name_t name_mask;
	pgn_t pgn;
	pgn_t pgn_mask;
	__u8 addr;
	__u8 addr_mask;
पूर्ण;

#घोषणा J1939_FILTER_MAX 512 /* maximum number of j1939_filter set via setsockopt() */

#पूर्ण_अगर /* !_UAPI_CAN_J1939_H_ */
