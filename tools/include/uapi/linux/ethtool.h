<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * ethtool.h: Defines क्रम Linux ethtool.
 *
 * Copyright (C) 1998 David S. Miller (davem@redhat.com)
 * Copyright 2001 Jeff Garzik <jgarzik@pobox.com>
 * Portions Copyright 2001 Sun Microप्रणालीs (thockin@sun.com)
 * Portions Copyright 2002 Intel (eli.kupermann@पूर्णांकel.com,
 *                                christopher.leech@पूर्णांकel.com,
 *                                scott.feldman@पूर्णांकel.com)
 * Portions Copyright (C) Sun Microप्रणालीs 2008
 */

#अगर_अघोषित _UAPI_LINUX_ETHTOOL_H
#घोषणा _UAPI_LINUX_ETHTOOL_H

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>

#घोषणा ETHTOOL_GCHANNELS       0x0000003c /* Get no of channels */

/**
 * काष्ठा ethtool_channels - configuring number of network channel
 * @cmd: ETHTOOL_अणुG,Sपूर्णCHANNELS
 * @max_rx: Read only. Maximum number of receive channel the driver support.
 * @max_tx: Read only. Maximum number of transmit channel the driver support.
 * @max_other: Read only. Maximum number of other channel the driver support.
 * @max_combined: Read only. Maximum number of combined channel the driver
 *	support. Set of queues RX, TX or other.
 * @rx_count: Valid values are in the range 1 to the max_rx.
 * @tx_count: Valid values are in the range 1 to the max_tx.
 * @other_count: Valid values are in the range 1 to the max_other.
 * @combined_count: Valid values are in the range 1 to the max_combined.
 *
 * This can be used to configure RX, TX and other channels.
 */

काष्ठा ethtool_channels अणु
	__u32	cmd;
	__u32	max_rx;
	__u32	max_tx;
	__u32	max_other;
	__u32	max_combined;
	__u32	rx_count;
	__u32	tx_count;
	__u32	other_count;
	__u32	combined_count;
पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_ETHTOOL_H */
