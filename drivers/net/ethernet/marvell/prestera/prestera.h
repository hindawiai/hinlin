<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2019-2020 Marvell International Ltd. All rights reserved. */

#अगर_अघोषित _PRESTERA_H_
#घोषणा _PRESTERA_H_

#समावेश <linux/notअगरier.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/workqueue.h>
#समावेश <net/devlink.h>
#समावेश <uapi/linux/अगर_ether.h>

#घोषणा PRESTERA_DRV_NAME	"prestera"

#घोषणा PRESTERA_DEFAULT_VID    1

काष्ठा prestera_fw_rev अणु
	u16 maj;
	u16 min;
	u16 sub;
पूर्ण;

काष्ठा prestera_port_stats अणु
	u64 good_octets_received;
	u64 bad_octets_received;
	u64 mac_trans_error;
	u64 broadcast_frames_received;
	u64 multicast_frames_received;
	u64 frames_64_octets;
	u64 frames_65_to_127_octets;
	u64 frames_128_to_255_octets;
	u64 frames_256_to_511_octets;
	u64 frames_512_to_1023_octets;
	u64 frames_1024_to_max_octets;
	u64 excessive_collision;
	u64 multicast_frames_sent;
	u64 broadcast_frames_sent;
	u64 fc_sent;
	u64 fc_received;
	u64 buffer_overrun;
	u64 undersize;
	u64 fragments;
	u64 oversize;
	u64 jabber;
	u64 rx_error_frame_received;
	u64 bad_crc;
	u64 collisions;
	u64 late_collision;
	u64 unicast_frames_received;
	u64 unicast_frames_sent;
	u64 sent_multiple;
	u64 sent_deferred;
	u64 good_octets_sent;
पूर्ण;

काष्ठा prestera_port_caps अणु
	u64 supp_link_modes;
	u8 supp_fec;
	u8 type;
	u8 transceiver;
पूर्ण;

काष्ठा prestera_port अणु
	काष्ठा net_device *dev;
	काष्ठा prestera_चयन *sw;
	काष्ठा devlink_port dl_port;
	u32 id;
	u32 hw_id;
	u32 dev_id;
	u16 fp_id;
	u16 pvid;
	bool स्वतःneg;
	u64 adver_link_modes;
	u8 adver_fec;
	काष्ठा prestera_port_caps caps;
	काष्ठा list_head list;
	काष्ठा list_head vlans_list;
	काष्ठा अणु
		काष्ठा prestera_port_stats stats;
		काष्ठा delayed_work caching_dw;
	पूर्ण cached_hw_stats;
पूर्ण;

काष्ठा prestera_device अणु
	काष्ठा device *dev;
	u8 __iomem *ctl_regs;
	u8 __iomem *pp_regs;
	काष्ठा prestera_fw_rev fw_rev;
	व्योम *priv;

	/* called by device driver to handle received packets */
	व्योम (*recv_pkt)(काष्ठा prestera_device *dev);

	/* called by device driver to pass event up to the higher layer */
	पूर्णांक (*recv_msg)(काष्ठा prestera_device *dev, व्योम *msg, माप_प्रकार size);

	/* called by higher layer to send request to the firmware */
	पूर्णांक (*send_req)(काष्ठा prestera_device *dev, व्योम *in_msg,
			माप_प्रकार in_size, व्योम *out_msg, माप_प्रकार out_size,
			अचिन्हित पूर्णांक रुको);
पूर्ण;

क्रमागत prestera_event_type अणु
	PRESTERA_EVENT_TYPE_UNSPEC,

	PRESTERA_EVENT_TYPE_PORT,
	PRESTERA_EVENT_TYPE_FDB,
	PRESTERA_EVENT_TYPE_RXTX,

	PRESTERA_EVENT_TYPE_MAX
पूर्ण;

क्रमागत prestera_rxtx_event_id अणु
	PRESTERA_RXTX_EVENT_UNSPEC,
	PRESTERA_RXTX_EVENT_RCV_PKT,
पूर्ण;

क्रमागत prestera_port_event_id अणु
	PRESTERA_PORT_EVENT_UNSPEC,
	PRESTERA_PORT_EVENT_STATE_CHANGED,
पूर्ण;

काष्ठा prestera_port_event अणु
	u32 port_id;
	जोड़ अणु
		u32 oper_state;
	पूर्ण data;
पूर्ण;

क्रमागत prestera_fdb_event_id अणु
	PRESTERA_FDB_EVENT_UNSPEC,
	PRESTERA_FDB_EVENT_LEARNED,
	PRESTERA_FDB_EVENT_AGED,
पूर्ण;

काष्ठा prestera_fdb_event अणु
	u32 port_id;
	u32 vid;
	जोड़ अणु
		u8 mac[ETH_ALEN];
	पूर्ण data;
पूर्ण;

काष्ठा prestera_event अणु
	u16 id;
	जोड़ अणु
		काष्ठा prestera_port_event port_evt;
		काष्ठा prestera_fdb_event fdb_evt;
	पूर्ण;
पूर्ण;

काष्ठा prestera_चयनdev;
काष्ठा prestera_rxtx;

काष्ठा prestera_चयन अणु
	काष्ठा prestera_device *dev;
	काष्ठा prestera_चयनdev *swdev;
	काष्ठा prestera_rxtx *rxtx;
	काष्ठा list_head event_handlers;
	काष्ठा notअगरier_block netdev_nb;
	अक्षर base_mac[ETH_ALEN];
	काष्ठा list_head port_list;
	rwlock_t port_list_lock;
	u32 port_count;
	u32 mtu_min;
	u32 mtu_max;
	u8 id;
पूर्ण;

काष्ठा prestera_rxtx_params अणु
	bool use_sdma;
	u32 map_addr;
पूर्ण;

#घोषणा prestera_dev(sw)		((sw)->dev->dev)

अटल अंतरभूत व्योम prestera_ग_लिखो(स्थिर काष्ठा prestera_चयन *sw,
				  अचिन्हित पूर्णांक reg, u32 val)
अणु
	ग_लिखोl(val, sw->dev->pp_regs + reg);
पूर्ण

अटल अंतरभूत u32 prestera_पढ़ो(स्थिर काष्ठा prestera_चयन *sw,
				अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl(sw->dev->pp_regs + reg);
पूर्ण

पूर्णांक prestera_device_रेजिस्टर(काष्ठा prestera_device *dev);
व्योम prestera_device_unरेजिस्टर(काष्ठा prestera_device *dev);

काष्ठा prestera_port *prestera_port_find_by_hwid(काष्ठा prestera_चयन *sw,
						 u32 dev_id, u32 hw_id);

पूर्णांक prestera_port_स्वतःneg_set(काष्ठा prestera_port *port, bool enable,
			      u64 adver_link_modes, u8 adver_fec);

काष्ठा prestera_port *prestera_find_port(काष्ठा prestera_चयन *sw, u32 id);

काष्ठा prestera_port *prestera_port_dev_lower_find(काष्ठा net_device *dev);

पूर्णांक prestera_port_pvid_set(काष्ठा prestera_port *port, u16 vid);

bool prestera_netdev_check(स्थिर काष्ठा net_device *dev);

#पूर्ण_अगर /* _PRESTERA_H_ */
