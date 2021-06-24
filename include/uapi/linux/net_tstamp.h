<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Userspace API क्रम hardware समय stamping of network packets
 *
 * Copyright (C) 2008,2009 Intel Corporation
 * Author: Patrick Ohly <patrick.ohly@पूर्णांकel.com>
 *
 */

#अगर_अघोषित _NET_TIMESTAMPING_H
#घोषणा _NET_TIMESTAMPING_H

#समावेश <linux/types.h>
#समावेश <linux/socket.h>   /* क्रम SO_TIMESTAMPING */

/* SO_TIMESTAMPING माला_लो an पूर्णांकeger bit field comprised of these values */
क्रमागत अणु
	SOF_TIMESTAMPING_TX_HARDWARE = (1<<0),
	SOF_TIMESTAMPING_TX_SOFTWARE = (1<<1),
	SOF_TIMESTAMPING_RX_HARDWARE = (1<<2),
	SOF_TIMESTAMPING_RX_SOFTWARE = (1<<3),
	SOF_TIMESTAMPING_SOFTWARE = (1<<4),
	SOF_TIMESTAMPING_SYS_HARDWARE = (1<<5),
	SOF_TIMESTAMPING_RAW_HARDWARE = (1<<6),
	SOF_TIMESTAMPING_OPT_ID = (1<<7),
	SOF_TIMESTAMPING_TX_SCHED = (1<<8),
	SOF_TIMESTAMPING_TX_ACK = (1<<9),
	SOF_TIMESTAMPING_OPT_CMSG = (1<<10),
	SOF_TIMESTAMPING_OPT_TSONLY = (1<<11),
	SOF_TIMESTAMPING_OPT_STATS = (1<<12),
	SOF_TIMESTAMPING_OPT_PKTINFO = (1<<13),
	SOF_TIMESTAMPING_OPT_TX_SWHW = (1<<14),

	SOF_TIMESTAMPING_LAST = SOF_TIMESTAMPING_OPT_TX_SWHW,
	SOF_TIMESTAMPING_MASK = (SOF_TIMESTAMPING_LAST - 1) |
				 SOF_TIMESTAMPING_LAST
पूर्ण;

/*
 * SO_TIMESTAMPING flags are either क्रम recording a packet बारtamp or क्रम
 * reporting the बारtamp to user space.
 * Recording flags can be set both via socket options and control messages.
 */
#घोषणा SOF_TIMESTAMPING_TX_RECORD_MASK	(SOF_TIMESTAMPING_TX_HARDWARE | \
					 SOF_TIMESTAMPING_TX_SOFTWARE | \
					 SOF_TIMESTAMPING_TX_SCHED | \
					 SOF_TIMESTAMPING_TX_ACK)

/**
 * काष्ठा hwtstamp_config - %SIOCGHWTSTAMP and %SIOCSHWTSTAMP parameter
 *
 * @flags:	no flags defined right now, must be zero क्रम %SIOCSHWTSTAMP
 * @tx_type:	one of HWTSTAMP_TX_*
 * @rx_filter:	one of HWTSTAMP_FILTER_*
 *
 * %SIOCGHWTSTAMP and %SIOCSHWTSTAMP expect a &काष्ठा अगरreq with a
 * अगरr_data poपूर्णांकer to this काष्ठाure.  For %SIOCSHWTSTAMP, अगर the
 * driver or hardware करोes not support the requested @rx_filter value,
 * the driver may use a more general filter mode.  In this हाल
 * @rx_filter will indicate the actual mode on वापस.
 */
काष्ठा hwtstamp_config अणु
	पूर्णांक flags;
	पूर्णांक tx_type;
	पूर्णांक rx_filter;
पूर्ण;

/* possible values क्रम hwtstamp_config->tx_type */
क्रमागत hwtstamp_tx_types अणु
	/*
	 * No outgoing packet will need hardware समय stamping;
	 * should a packet arrive which asks क्रम it, no hardware
	 * समय stamping will be करोne.
	 */
	HWTSTAMP_TX_OFF,

	/*
	 * Enables hardware समय stamping क्रम outgoing packets;
	 * the sender of the packet decides which are to be
	 * समय stamped by setting %SOF_TIMESTAMPING_TX_SOFTWARE
	 * beक्रमe sending the packet.
	 */
	HWTSTAMP_TX_ON,

	/*
	 * Enables समय stamping क्रम outgoing packets just as
	 * HWTSTAMP_TX_ON करोes, but also enables समय stamp insertion
	 * directly पूर्णांकo Sync packets. In this हाल, transmitted Sync
	 * packets will not received a समय stamp via the socket error
	 * queue.
	 */
	HWTSTAMP_TX_ONESTEP_SYNC,

	/*
	 * Same as HWTSTAMP_TX_ONESTEP_SYNC, but also enables समय
	 * stamp insertion directly पूर्णांकo PDelay_Resp packets. In this
	 * हाल, neither transmitted Sync nor PDelay_Resp packets will
	 * receive a समय stamp via the socket error queue.
	 */
	HWTSTAMP_TX_ONESTEP_P2P,

	/* add new स्थिरants above here */
	__HWTSTAMP_TX_CNT
पूर्ण;

/* possible values क्रम hwtstamp_config->rx_filter */
क्रमागत hwtstamp_rx_filters अणु
	/* समय stamp no incoming packet at all */
	HWTSTAMP_FILTER_NONE,

	/* समय stamp any incoming packet */
	HWTSTAMP_FILTER_ALL,

	/* वापस value: समय stamp all packets requested plus some others */
	HWTSTAMP_FILTER_SOME,

	/* PTP v1, UDP, any kind of event packet */
	HWTSTAMP_FILTER_PTP_V1_L4_EVENT,
	/* PTP v1, UDP, Sync packet */
	HWTSTAMP_FILTER_PTP_V1_L4_SYNC,
	/* PTP v1, UDP, Delay_req packet */
	HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ,
	/* PTP v2, UDP, any kind of event packet */
	HWTSTAMP_FILTER_PTP_V2_L4_EVENT,
	/* PTP v2, UDP, Sync packet */
	HWTSTAMP_FILTER_PTP_V2_L4_SYNC,
	/* PTP v2, UDP, Delay_req packet */
	HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ,

	/* 802.AS1, Ethernet, any kind of event packet */
	HWTSTAMP_FILTER_PTP_V2_L2_EVENT,
	/* 802.AS1, Ethernet, Sync packet */
	HWTSTAMP_FILTER_PTP_V2_L2_SYNC,
	/* 802.AS1, Ethernet, Delay_req packet */
	HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ,

	/* PTP v2/802.AS1, any layer, any kind of event packet */
	HWTSTAMP_FILTER_PTP_V2_EVENT,
	/* PTP v2/802.AS1, any layer, Sync packet */
	HWTSTAMP_FILTER_PTP_V2_SYNC,
	/* PTP v2/802.AS1, any layer, Delay_req packet */
	HWTSTAMP_FILTER_PTP_V2_DELAY_REQ,

	/* NTP, UDP, all versions and packet modes */
	HWTSTAMP_FILTER_NTP_ALL,

	/* add new स्थिरants above here */
	__HWTSTAMP_FILTER_CNT
पूर्ण;

/* SCM_TIMESTAMPING_PKTINFO control message */
काष्ठा scm_ts_pktinfo अणु
	__u32 अगर_index;
	__u32 pkt_length;
	__u32 reserved[2];
पूर्ण;

/*
 * SO_TXTIME माला_लो a काष्ठा sock_txसमय with flags being an पूर्णांकeger bit
 * field comprised of these values.
 */
क्रमागत txसमय_flags अणु
	SOF_TXTIME_DEADLINE_MODE = (1 << 0),
	SOF_TXTIME_REPORT_ERRORS = (1 << 1),

	SOF_TXTIME_FLAGS_LAST = SOF_TXTIME_REPORT_ERRORS,
	SOF_TXTIME_FLAGS_MASK = (SOF_TXTIME_FLAGS_LAST - 1) |
				 SOF_TXTIME_FLAGS_LAST
पूर्ण;

काष्ठा sock_txसमय अणु
	__kernel_घड़ीid_t	घड़ीid;/* reference घड़ीid */
	__u32			flags;	/* as defined by क्रमागत txसमय_flags */
पूर्ण;

#पूर्ण_अगर /* _NET_TIMESTAMPING_H */
