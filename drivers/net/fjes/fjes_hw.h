<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  FUJITSU Extended Socket Network Device driver
 *  Copyright (c) 2015 FUJITSU LIMITED
 */

#अगर_अघोषित FJES_HW_H_
#घोषणा FJES_HW_H_

#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "fjes_regs.h"

काष्ठा fjes_hw;

#घोषणा EP_BUFFER_SUPPORT_VLAN_MAX 4
#घोषणा EP_BUFFER_INFO_SIZE 4096

#घोषणा FJES_DEBUG_PAGE_SIZE 4096
#घोषणा FJES_DEBUG_BUFFER_SIZE	(16 * FJES_DEBUG_PAGE_SIZE)

#घोषणा FJES_DEVICE_RESET_TIMEOUT  ((17 + 1) * 3 * 8) /* sec */
#घोषणा FJES_COMMAND_REQ_TIMEOUT  ((5 + 1) * 3 * 8) /* sec */
#घोषणा FJES_COMMAND_REQ_BUFF_TIMEOUT	(60 * 3) /* sec */
#घोषणा FJES_COMMAND_EPSTOP_WAIT_TIMEOUT	(1) /* sec */

#घोषणा FJES_CMD_REQ_ERR_INFO_PARAM  (0x0001)
#घोषणा FJES_CMD_REQ_ERR_INFO_STATUS (0x0002)

#घोषणा FJES_CMD_REQ_RES_CODE_NORMAL (0)
#घोषणा FJES_CMD_REQ_RES_CODE_BUSY   (1)

#घोषणा FJES_ZONING_STATUS_DISABLE	(0x00)
#घोषणा FJES_ZONING_STATUS_ENABLE	(0x01)
#घोषणा FJES_ZONING_STATUS_INVALID	(0xFF)

#घोषणा FJES_ZONING_ZONE_TYPE_NONE (0xFF)

#घोषणा FJES_TX_DELAY_SEND_NONE		(0)
#घोषणा FJES_TX_DELAY_SEND_PENDING	(1)

#घोषणा FJES_RX_STOP_REQ_NONE		(0x0)
#घोषणा FJES_RX_STOP_REQ_DONE		(0x1)
#घोषणा FJES_RX_STOP_REQ_REQUEST	(0x2)
#घोषणा FJES_RX_POLL_WORK		(0x4)
#घोषणा FJES_RX_MTU_CHANGING_DONE	(0x8)

#घोषणा EP_BUFFER_SIZE \
	(((माप(जोड़ ep_buffer_info) + (128 * (64 * 1024))) \
		/ EP_BUFFER_INFO_SIZE) * EP_BUFFER_INFO_SIZE)

#घोषणा EP_RING_NUM(buffer_size, frame_size) \
		(u32)((buffer_size) / (frame_size))
#घोषणा EP_RING_INDEX(_num, _max) (((_num) + (_max)) % (_max))
#घोषणा EP_RING_INDEX_INC(_num, _max) \
	((_num) = EP_RING_INDEX((_num) + 1, (_max)))
#घोषणा EP_RING_FULL(_head, _tail, _max)				\
	(0 == EP_RING_INDEX(((_tail) - (_head)), (_max)))
#घोषणा EP_RING_EMPTY(_head, _tail, _max) \
	(1 == EP_RING_INDEX(((_tail) - (_head)), (_max)))

#घोषणा FJES_MTU_TO_BUFFER_SIZE(mtu) \
	(ETH_HLEN + VLAN_HLEN + (mtu) + ETH_FCS_LEN)
#घोषणा FJES_MTU_TO_FRAME_SIZE(mtu) \
	(माप(काष्ठा esmem_frame) + FJES_MTU_TO_BUFFER_SIZE(mtu))
#घोषणा FJES_MTU_DEFINE(size) \
	((size) - माप(काष्ठा esmem_frame) - \
	(ETH_HLEN + VLAN_HLEN + ETH_FCS_LEN))

#घोषणा FJES_DEV_COMMAND_INFO_REQ_LEN	(4)
#घोषणा FJES_DEV_COMMAND_INFO_RES_LEN(epnum) (8 + 2 * (epnum))
#घोषणा FJES_DEV_COMMAND_SHARE_BUFFER_REQ_LEN(txb, rxb) \
	(24 + (8 * ((txb) / EP_BUFFER_INFO_SIZE + (rxb) / EP_BUFFER_INFO_SIZE)))
#घोषणा FJES_DEV_COMMAND_SHARE_BUFFER_RES_LEN	(8)
#घोषणा FJES_DEV_COMMAND_UNSHARE_BUFFER_REQ_LEN	(8)
#घोषणा FJES_DEV_COMMAND_UNSHARE_BUFFER_RES_LEN	(8)

#घोषणा FJES_DEV_REQ_BUF_SIZE(maxep) \
	FJES_DEV_COMMAND_SHARE_BUFFER_REQ_LEN(EP_BUFFER_SIZE, EP_BUFFER_SIZE)
#घोषणा FJES_DEV_RES_BUF_SIZE(maxep) \
	FJES_DEV_COMMAND_INFO_RES_LEN(maxep)

#घोषणा FJES_DEV_COMMAND_START_DBG_REQ_LEN(byte) \
	(16 + (8 * (byte) / FJES_DEBUG_PAGE_SIZE))
#घोषणा FJES_DEV_COMMAND_START_DBG_RES_LEN (8)
#घोषणा FJES_DEV_COMMAND_STOP_DBG_REQ_LEN (4)
#घोषणा FJES_DEV_COMMAND_STOP_DBG_RES_LEN (8)

/* Frame & MTU */
काष्ठा esmem_frame अणु
	__le32 frame_size;
	u8 frame_data[];
पूर्ण;

/* EP partner status */
क्रमागत ep_partner_status अणु
	EP_PARTNER_UNSHARE,
	EP_PARTNER_SHARED,
	EP_PARTNER_WAITING,
	EP_PARTNER_COMPLETE,
	EP_PARTNER_STATUS_MAX,
पूर्ण;

/* shared status region */
काष्ठा fjes_device_shared_info अणु
	पूर्णांक epnum;
	u8 ep_status[];
पूर्ण;

/* काष्ठाures क्रम command control request data*/
जोड़ fjes_device_command_req अणु
	काष्ठा अणु
		__le32 length;
	पूर्ण info;
	काष्ठा अणु
		__le32 length;
		__le32 epid;
		__le64 buffer[];
	पूर्ण share_buffer;
	काष्ठा अणु
		__le32 length;
		__le32 epid;
	पूर्ण unshare_buffer;
	काष्ठा अणु
		__le32 length;
		__le32 mode;
		__le64 buffer_len;
		__le64 buffer[];
	पूर्ण start_trace;
	काष्ठा अणु
		__le32 length;
	पूर्ण stop_trace;
पूर्ण;

/* काष्ठाures क्रम command control response data */
जोड़ fjes_device_command_res अणु
	काष्ठा अणु
		__le32 length;
		__le32 code;
		काष्ठा अणु
			u8 es_status;
			u8 zone;
		पूर्ण info[];
	पूर्ण info;
	काष्ठा अणु
		__le32 length;
		__le32 code;
	पूर्ण share_buffer;
	काष्ठा अणु
		__le32 length;
		__le32 code;
	पूर्ण unshare_buffer;
	काष्ठा अणु
		__le32 length;
		__le32 code;
	पूर्ण start_trace;
	काष्ठा अणु
		__le32 length;
		__le32 code;
	पूर्ण stop_trace;
पूर्ण;

/* request command type */
क्रमागत fjes_dev_command_request_type अणु
	FJES_CMD_REQ_INFO		= 0x0001,
	FJES_CMD_REQ_SHARE_BUFFER	= 0x0002,
	FJES_CMD_REQ_UNSHARE_BUFFER	= 0x0004,
	FJES_CMD_REQ_START_DEBUG	= 0x0100,
	FJES_CMD_REQ_STOP_DEBUG		= 0x0200,
पूर्ण;

/* parameter क्रम command control */
काष्ठा fjes_device_command_param अणु
	u32 req_len;
	phys_addr_t req_start;
	u32 res_len;
	phys_addr_t res_start;
	phys_addr_t share_start;
पूर्ण;

/* error code क्रम command control */
क्रमागत fjes_dev_command_response_e अणु
	FJES_CMD_STATUS_UNKNOWN,
	FJES_CMD_STATUS_NORMAL,
	FJES_CMD_STATUS_TIMEOUT,
	FJES_CMD_STATUS_ERROR_PARAM,
	FJES_CMD_STATUS_ERROR_STATUS,
पूर्ण;

/* EP buffer inक्रमmation */
जोड़ ep_buffer_info अणु
	u8 raw[EP_BUFFER_INFO_SIZE];

	काष्ठा _ep_buffer_info_common_t अणु
		u32 version;
	पूर्ण common;

	काष्ठा _ep_buffer_info_v1_t अणु
		u32 version;
		u32 info_size;

		u32 buffer_size;
		u16 count_max;

		u16 _rsv_1;

		u32 frame_max;
		u8 mac_addr[ETH_ALEN];

		u16 _rsv_2;
		u32 _rsv_3;

		u16 tx_status;
		u16 rx_status;

		u32 head;
		u32 tail;

		u16 vlan_id[EP_BUFFER_SUPPORT_VLAN_MAX];

	पूर्ण v1i;

पूर्ण;

/* statistics of EP */
काष्ठा fjes_drv_ep_stats अणु
	u64 com_regist_buf_exec;
	u64 com_unregist_buf_exec;
	u64 send_पूर्णांकr_rx;
	u64 send_पूर्णांकr_unshare;
	u64 send_पूर्णांकr_zoneupdate;
	u64 recv_पूर्णांकr_rx;
	u64 recv_पूर्णांकr_unshare;
	u64 recv_पूर्णांकr_stop;
	u64 recv_पूर्णांकr_zoneupdate;
	u64 tx_buffer_full;
	u64 tx_dropped_not_shared;
	u64 tx_dropped_ver_mismatch;
	u64 tx_dropped_buf_size_mismatch;
	u64 tx_dropped_vlanid_mismatch;
पूर्ण;

/* buffer pair क्रम Extended Partition */
काष्ठा ep_share_mem_info अणु
	काष्ठा epbuf_handler अणु
		व्योम *buffer;
		माप_प्रकार size;
		जोड़ ep_buffer_info *info;
		u8 *ring;
	पूर्ण tx, rx;

	काष्ठा rtnl_link_stats64 net_stats;
	काष्ठा fjes_drv_ep_stats ep_stats;

	u16 tx_status_work;

	u8 es_status;
	u8 zone;
पूर्ण;

काष्ठा es_device_trace अणु
	u32 record_num;
	u32 current_record;
	u32 status_flag;
	u32 _rsv;

	काष्ठा अणु
			u16 epid;
			u16 dir_offset;
			u32 data;
			u64 tsc;
	पूर्ण record[];
पूर्ण;

काष्ठा fjes_hw_info अणु
	काष्ठा fjes_device_shared_info *share;
	जोड़ fjes_device_command_req *req_buf;
	u64 req_buf_size;
	जोड़ fjes_device_command_res *res_buf;
	u64 res_buf_size;

	पूर्णांक *my_epid;
	पूर्णांक *max_epid;

	काष्ठा es_device_trace *trace;
	u64 trace_size;

	काष्ठा mutex lock; /* buffer lock*/

	अचिन्हित दीर्घ buffer_share_bit;
	अचिन्हित दीर्घ buffer_unshare_reserve_bit;
पूर्ण;

काष्ठा fjes_hw अणु
	व्योम *back;

	अचिन्हित दीर्घ txrx_stop_req_bit;
	अचिन्हित दीर्घ epstop_req_bit;
	काष्ठा work_काष्ठा update_zone_task;
	काष्ठा work_काष्ठा epstop_task;

	पूर्णांक my_epid;
	पूर्णांक max_epid;

	काष्ठा ep_share_mem_info *ep_shm_info;

	काष्ठा fjes_hw_resource अणु
		u64 start;
		u64 size;
		पूर्णांक irq;
	पूर्ण hw_res;

	u8 *base;

	काष्ठा fjes_hw_info hw_info;

	spinlock_t rx_status_lock; /* spinlock क्रम rx_status */

	u32 debug_mode;
पूर्ण;

पूर्णांक fjes_hw_init(काष्ठा fjes_hw *);
व्योम fjes_hw_निकास(काष्ठा fjes_hw *);
पूर्णांक fjes_hw_reset(काष्ठा fjes_hw *);
पूर्णांक fjes_hw_request_info(काष्ठा fjes_hw *);
पूर्णांक fjes_hw_रेजिस्टर_buff_addr(काष्ठा fjes_hw *, पूर्णांक,
			       काष्ठा ep_share_mem_info *);
पूर्णांक fjes_hw_unरेजिस्टर_buff_addr(काष्ठा fjes_hw *, पूर्णांक);
व्योम fjes_hw_init_command_रेजिस्टरs(काष्ठा fjes_hw *,
				    काष्ठा fjes_device_command_param *);
व्योम fjes_hw_setup_epbuf(काष्ठा epbuf_handler *, u8 *, u32);
पूर्णांक fjes_hw_उठाओ_पूर्णांकerrupt(काष्ठा fjes_hw *, पूर्णांक, क्रमागत REG_ICTL_MASK);
व्योम fjes_hw_set_irqmask(काष्ठा fjes_hw *, क्रमागत REG_ICTL_MASK, bool);
u32 fjes_hw_capture_पूर्णांकerrupt_status(काष्ठा fjes_hw *);
व्योम fjes_hw_उठाओ_epstop(काष्ठा fjes_hw *);
पूर्णांक fjes_hw_रुको_epstop(काष्ठा fjes_hw *);
क्रमागत ep_partner_status
	fjes_hw_get_partner_ep_status(काष्ठा fjes_hw *, पूर्णांक);

bool fjes_hw_epid_is_same_zone(काष्ठा fjes_hw *, पूर्णांक);
पूर्णांक fjes_hw_epid_is_shared(काष्ठा fjes_device_shared_info *, पूर्णांक);
bool fjes_hw_check_epbuf_version(काष्ठा epbuf_handler *, u32);
bool fjes_hw_check_mtu(काष्ठा epbuf_handler *, u32);
bool fjes_hw_check_vlan_id(काष्ठा epbuf_handler *, u16);
bool fjes_hw_set_vlan_id(काष्ठा epbuf_handler *, u16);
व्योम fjes_hw_del_vlan_id(काष्ठा epbuf_handler *, u16);
bool fjes_hw_epbuf_rx_is_empty(काष्ठा epbuf_handler *);
व्योम *fjes_hw_epbuf_rx_curpkt_get_addr(काष्ठा epbuf_handler *, माप_प्रकार *);
व्योम fjes_hw_epbuf_rx_curpkt_drop(काष्ठा epbuf_handler *);
पूर्णांक fjes_hw_epbuf_tx_pkt_send(काष्ठा epbuf_handler *, व्योम *, माप_प्रकार);

पूर्णांक fjes_hw_start_debug(काष्ठा fjes_hw *);
पूर्णांक fjes_hw_stop_debug(काष्ठा fjes_hw *);
#पूर्ण_अगर /* FJES_HW_H_ */
