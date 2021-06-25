<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2010 Broadcom Corporation
 */

/****************
 * Common types *
 */

#अगर_अघोषित BRCMFMAC_CORE_H
#घोषणा BRCMFMAC_CORE_H

#समावेश <net/cfg80211.h>
#समावेश "fweh.h"

#घोषणा TOE_TX_CSUM_OL		0x00000001
#घोषणा TOE_RX_CSUM_OL		0x00000002

/* For supporting multiple पूर्णांकerfaces */
#घोषणा BRCMF_MAX_IFS	16

/* Small, medium and maximum buffer size क्रम dcmd
 */
#घोषणा BRCMF_DCMD_SMLEN	256
#घोषणा BRCMF_DCMD_MEDLEN	1536
#घोषणा BRCMF_DCMD_MAXLEN	8192

/* IOCTL from host to device are limited in length. A device can only handle
 * ethernet frame size. This limitation is to be applied by protocol layer.
 */
#घोषणा BRCMF_TX_IOCTL_MAX_MSG_SIZE	(ETH_FRAME_LEN+ETH_FCS_LEN)

#घोषणा BRCMF_AMPDU_RX_REORDER_MAXFLOWS		256

/* Length of firmware version string stored क्रम
 * ethtool driver info which uses 32 bytes as well.
 */
#घोषणा BRCMF_DRIVER_FIRMWARE_VERSION_LEN	32

#घोषणा NDOL_MAX_ENTRIES	8

/**
 * काष्ठा brcmf_ampdu_rx_reorder - AMPDU receive reorder info
 *
 * @pktslots: dynamic allocated array क्रम ordering AMPDU packets.
 * @flow_id: AMPDU flow identअगरier.
 * @cur_idx: last AMPDU index from firmware.
 * @exp_idx: expected next AMPDU index.
 * @max_idx: maximum amount of packets per AMPDU.
 * @pend_pkts: number of packets currently in @pktslots.
 */
काष्ठा brcmf_ampdu_rx_reorder अणु
	काष्ठा sk_buff **pktslots;
	u8 flow_id;
	u8 cur_idx;
	u8 exp_idx;
	u8 max_idx;
	u8 pend_pkts;
पूर्ण;

/* Forward decls क्रम काष्ठा brcmf_pub (see below) */
काष्ठा brcmf_proto;	/* device communication protocol info */
काष्ठा brcmf_fws_info;	/* firmware संकेतling info */
काष्ठा brcmf_mp_device;	/* module paramateres, device specअगरic */

/*
 * काष्ठा brcmf_rev_info
 *
 * The result field stores the error code of the
 * revision info request from firmware. For the
 * other fields see काष्ठा brcmf_rev_info_le in
 * fwil_types.h
 */
काष्ठा brcmf_rev_info अणु
	पूर्णांक result;
	u32 venकरोrid;
	u32 deviceid;
	u32 radiorev;
	u32 corerev;
	u32 boardid;
	u32 boardvenकरोr;
	u32 boardrev;
	u32 driverrev;
	u32 ucoderev;
	u32 bus;
	अक्षर chipname[12];
	u32 phytype;
	u32 phyrev;
	u32 anarev;
	u32 chippkg;
	u32 nvramrev;
पूर्ण;

/* Common काष्ठाure क्रम module and instance linkage */
काष्ठा brcmf_pub अणु
	/* Linkage ponters */
	काष्ठा brcmf_bus *bus_अगर;
	काष्ठा brcmf_proto *proto;
	काष्ठा wiphy *wiphy;
	काष्ठा cfg80211_ops *ops;
	काष्ठा brcmf_cfg80211_info *config;

	/* Internal brcmf items */
	uपूर्णांक hdrlen;		/* Total BRCMF header length (proto + bus) */

	/* Dongle media info */
	अक्षर fwver[BRCMF_DRIVER_FIRMWARE_VERSION_LEN];
	u8 mac[ETH_ALEN];		/* MAC address obtained from करोngle */

	काष्ठा mac_address addresses[BRCMF_MAX_IFS];

	काष्ठा brcmf_अगर *अगरlist[BRCMF_MAX_IFS];
	s32 अगर2bss[BRCMF_MAX_IFS];
	काष्ठा brcmf_अगर *mon_अगर;

	काष्ठा mutex proto_block;
	अचिन्हित अक्षर proto_buf[BRCMF_DCMD_MAXLEN];

	काष्ठा brcmf_fweh_info fweh;

	काष्ठा brcmf_ampdu_rx_reorder
		*reorder_flows[BRCMF_AMPDU_RX_REORDER_MAXFLOWS];

	u32 feat_flags;
	u32 chip_quirks;

	काष्ठा brcmf_rev_info revinfo;
#अगर_घोषित DEBUG
	काष्ठा dentry *dbgfs_dir;
#पूर्ण_अगर

	काष्ठा notअगरier_block inetaddr_notअगरier;
	काष्ठा notअगरier_block inet6addr_notअगरier;
	काष्ठा brcmf_mp_device *settings;

	काष्ठा work_काष्ठा bus_reset;

	u8 clmver[BRCMF_DCMD_SMLEN];
पूर्ण;

/* क्रमward declarations */
काष्ठा brcmf_cfg80211_vअगर;
काष्ठा brcmf_fws_mac_descriptor;

/**
 * क्रमागत brcmf_netअगर_stop_reason - reason क्रम stopping netअगर queue.
 *
 * @BRCMF_NETIF_STOP_REASON_FWS_FC:
 *	netअगर stopped due to firmware संकेतling flow control.
 * @BRCMF_NETIF_STOP_REASON_FLOW:
 *	netअगर stopped due to flowring full.
 * @BRCMF_NETIF_STOP_REASON_DISCONNECTED:
 *	netअगर stopped due to not being connected (STA mode).
 */
क्रमागत brcmf_netअगर_stop_reason अणु
	BRCMF_NETIF_STOP_REASON_FWS_FC = BIT(0),
	BRCMF_NETIF_STOP_REASON_FLOW = BIT(1),
	BRCMF_NETIF_STOP_REASON_DISCONNECTED = BIT(2)
पूर्ण;

/**
 * काष्ठा brcmf_अगर - पूर्णांकerface control inक्रमmation.
 *
 * @drvr: poपूर्णांकs to device related inक्रमmation.
 * @vअगर: poपूर्णांकs to cfg80211 specअगरic पूर्णांकerface inक्रमmation.
 * @ndev: associated network device.
 * @multicast_work: worker object क्रम multicast provisioning.
 * @nकरोffload_work: worker object क्रम neighbor discovery offload configuration.
 * @fws_desc: पूर्णांकerface specअगरic firmware-संकेतling descriptor.
 * @अगरidx: पूर्णांकerface index in device firmware.
 * @bsscfgidx: index of bss associated with this पूर्णांकerface.
 * @mac_addr: asचिन्हित mac address.
 * @netअगर_stop: biपंचांगap indicates reason why netअगर queues are stopped.
 * @netअगर_stop_lock: spinlock क्रम update netअगर_stop from multiple sources.
 * @pend_8021x_cnt: tracks outstanding number of 802.1x frames.
 * @pend_8021x_रुको: used क्रम संकेतling change in count.
 * @fwil_fwerr: flag indicating fwil layer should वापस firmware error codes.
 */
काष्ठा brcmf_अगर अणु
	काष्ठा brcmf_pub *drvr;
	काष्ठा brcmf_cfg80211_vअगर *vअगर;
	काष्ठा net_device *ndev;
	काष्ठा work_काष्ठा multicast_work;
	काष्ठा work_काष्ठा nकरोffload_work;
	काष्ठा brcmf_fws_mac_descriptor *fws_desc;
	पूर्णांक अगरidx;
	s32 bsscfgidx;
	u8 mac_addr[ETH_ALEN];
	u8 netअगर_stop;
	spinlock_t netअगर_stop_lock;
	atomic_t pend_8021x_cnt;
	रुको_queue_head_t pend_8021x_रुको;
	काष्ठा in6_addr ipv6_addr_tbl[NDOL_MAX_ENTRIES];
	u8 ipv6addr_idx;
	bool fwil_fwerr;
पूर्ण;

पूर्णांक brcmf_netdev_रुको_pend8021x(काष्ठा brcmf_अगर *अगरp);

/* Return poपूर्णांकer to पूर्णांकerface name */
अक्षर *brcmf_अगरname(काष्ठा brcmf_अगर *अगरp);
काष्ठा brcmf_अगर *brcmf_get_अगरp(काष्ठा brcmf_pub *drvr, पूर्णांक अगरidx);
व्योम brcmf_configure_arp_nd_offload(काष्ठा brcmf_अगर *अगरp, bool enable);
पूर्णांक brcmf_net_attach(काष्ठा brcmf_अगर *अगरp, bool locked);
काष्ठा brcmf_अगर *brcmf_add_अगर(काष्ठा brcmf_pub *drvr, s32 bsscfgidx, s32 अगरidx,
			      bool is_p2pdev, स्थिर अक्षर *name, u8 *mac_addr);
व्योम brcmf_हटाओ_पूर्णांकerface(काष्ठा brcmf_अगर *अगरp, bool locked);
व्योम brcmf_txflowblock_अगर(काष्ठा brcmf_अगर *अगरp,
			  क्रमागत brcmf_netअगर_stop_reason reason, bool state);
व्योम brcmf_txfinalize(काष्ठा brcmf_अगर *अगरp, काष्ठा sk_buff *txp, bool success);
व्योम brcmf_netअगर_rx(काष्ठा brcmf_अगर *अगरp, काष्ठा sk_buff *skb, bool inirq);
व्योम brcmf_netअगर_mon_rx(काष्ठा brcmf_अगर *अगरp, काष्ठा sk_buff *skb);
व्योम brcmf_net_detach(काष्ठा net_device *ndev, bool locked);
पूर्णांक brcmf_net_mon_attach(काष्ठा brcmf_अगर *अगरp);
व्योम brcmf_net_setcarrier(काष्ठा brcmf_अगर *अगरp, bool on);
पूर्णांक __init brcmf_core_init(व्योम);
व्योम __निकास brcmf_core_निकास(व्योम);

#पूर्ण_अगर /* BRCMFMAC_CORE_H */
