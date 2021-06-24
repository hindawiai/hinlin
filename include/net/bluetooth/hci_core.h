<शैली गुरु>
/*
   BlueZ - Bluetooth protocol stack क्रम Linux
   Copyright (c) 2000-2001, 2010, Code Aurora Forum. All rights reserved.

   Written 2000,2001 by Maxim Krasnyansky <maxk@qualcomm.com>

   This program is मुक्त software; you can redistribute it and/or modअगरy
   it under the terms of the GNU General Public License version 2 as
   published by the Free Software Foundation;

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY
   CLAIM, OR ANY SPECIAL INसूचीECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES
   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS,
   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS
   SOFTWARE IS DISCLAIMED.
*/

#अगर_अघोषित __HCI_CORE_H
#घोषणा __HCI_CORE_H

#समावेश <linux/idr.h>
#समावेश <linux/leds.h>
#समावेश <linux/rculist.h>

#समावेश <net/bluetooth/hci.h>
#समावेश <net/bluetooth/hci_sock.h>

/* HCI priority */
#घोषणा HCI_PRIO_MAX	7

/* HCI Core काष्ठाures */
काष्ठा inquiry_data अणु
	bdaddr_t	bdaddr;
	__u8		pscan_rep_mode;
	__u8		pscan_period_mode;
	__u8		pscan_mode;
	__u8		dev_class[3];
	__le16		घड़ी_offset;
	__s8		rssi;
	__u8		ssp_mode;
पूर्ण;

काष्ठा inquiry_entry अणु
	काष्ठा list_head	all;		/* inq_cache.all */
	काष्ठा list_head	list;		/* unknown or resolve */
	क्रमागत अणु
		NAME_NOT_KNOWN,
		NAME_NEEDED,
		NAME_PENDING,
		NAME_KNOWN,
	पूर्ण name_state;
	__u32			बारtamp;
	काष्ठा inquiry_data	data;
पूर्ण;

काष्ठा discovery_state अणु
	पूर्णांक			type;
	क्रमागत अणु
		DISCOVERY_STOPPED,
		DISCOVERY_STARTING,
		DISCOVERY_FINDING,
		DISCOVERY_RESOLVING,
		DISCOVERY_STOPPING,
	पूर्ण state;
	काष्ठा list_head	all;	/* All devices found during inquiry */
	काष्ठा list_head	unknown;	/* Name state not known */
	काष्ठा list_head	resolve;	/* Name needs to be resolved */
	__u32			बारtamp;
	bdaddr_t		last_adv_addr;
	u8			last_adv_addr_type;
	s8			last_adv_rssi;
	u32			last_adv_flags;
	u8			last_adv_data[HCI_MAX_AD_LENGTH];
	u8			last_adv_data_len;
	bool			report_invalid_rssi;
	bool			result_filtering;
	bool			limited;
	s8			rssi;
	u16			uuid_count;
	u8			(*uuids)[16];
	अचिन्हित दीर्घ		scan_start;
	अचिन्हित दीर्घ		scan_duration;
पूर्ण;

#घोषणा SUSPEND_NOTIFIER_TIMEOUT	msecs_to_jअगरfies(2000) /* 2 seconds */

क्रमागत suspend_tasks अणु
	SUSPEND_PAUSE_DISCOVERY,
	SUSPEND_UNPAUSE_DISCOVERY,

	SUSPEND_PAUSE_ADVERTISING,
	SUSPEND_UNPAUSE_ADVERTISING,

	SUSPEND_SCAN_DISABLE,
	SUSPEND_SCAN_ENABLE,
	SUSPEND_DISCONNECTING,

	SUSPEND_POWERING_DOWN,

	SUSPEND_PREPARE_NOTIFIER,

	SUSPEND_SET_ADV_FILTER,
	__SUSPEND_NUM_TASKS
पूर्ण;

क्रमागत suspended_state अणु
	BT_RUNNING = 0,
	BT_SUSPEND_DISCONNECT,
	BT_SUSPEND_CONFIGURE_WAKE,
पूर्ण;

काष्ठा hci_conn_hash अणु
	काष्ठा list_head list;
	अचिन्हित पूर्णांक     acl_num;
	अचिन्हित पूर्णांक     amp_num;
	अचिन्हित पूर्णांक     sco_num;
	अचिन्हित पूर्णांक     le_num;
	अचिन्हित पूर्णांक     le_num_slave;
पूर्ण;

काष्ठा bdaddr_list अणु
	काष्ठा list_head list;
	bdaddr_t bdaddr;
	u8 bdaddr_type;
पूर्ण;

काष्ठा bdaddr_list_with_irk अणु
	काष्ठा list_head list;
	bdaddr_t bdaddr;
	u8 bdaddr_type;
	u8 peer_irk[16];
	u8 local_irk[16];
पूर्ण;

काष्ठा bdaddr_list_with_flags अणु
	काष्ठा list_head list;
	bdaddr_t bdaddr;
	u8 bdaddr_type;
	u32 current_flags;
पूर्ण;

क्रमागत hci_conn_flags अणु
	HCI_CONN_FLAG_REMOTE_WAKEUP,
	HCI_CONN_FLAG_MAX
पूर्ण;

#घोषणा hci_conn_test_flag(nr, flags) ((flags) & (1U << nr))

/* Make sure number of flags करोesn't exceed माप(current_flags) */
अटल_निश्चित(HCI_CONN_FLAG_MAX < 32);

काष्ठा bt_uuid अणु
	काष्ठा list_head list;
	u8 uuid[16];
	u8 size;
	u8 svc_hपूर्णांक;
पूर्ण;

काष्ठा blocked_key अणु
	काष्ठा list_head list;
	काष्ठा rcu_head rcu;
	u8 type;
	u8 val[16];
पूर्ण;

काष्ठा smp_csrk अणु
	bdaddr_t bdaddr;
	u8 bdaddr_type;
	u8 type;
	u8 val[16];
पूर्ण;

काष्ठा smp_ltk अणु
	काष्ठा list_head list;
	काष्ठा rcu_head rcu;
	bdaddr_t bdaddr;
	u8 bdaddr_type;
	u8 authenticated;
	u8 type;
	u8 enc_size;
	__le16 eभाग;
	__le64 अक्रम;
	u8 val[16];
पूर्ण;

काष्ठा smp_irk अणु
	काष्ठा list_head list;
	काष्ठा rcu_head rcu;
	bdaddr_t rpa;
	bdaddr_t bdaddr;
	u8 addr_type;
	u8 val[16];
पूर्ण;

काष्ठा link_key अणु
	काष्ठा list_head list;
	काष्ठा rcu_head rcu;
	bdaddr_t bdaddr;
	u8 type;
	u8 val[HCI_LINK_KEY_SIZE];
	u8 pin_len;
पूर्ण;

काष्ठा oob_data अणु
	काष्ठा list_head list;
	bdaddr_t bdaddr;
	u8 bdaddr_type;
	u8 present;
	u8 hash192[16];
	u8 अक्रम192[16];
	u8 hash256[16];
	u8 अक्रम256[16];
पूर्ण;

काष्ठा adv_info अणु
	काष्ठा list_head list;
	bool pending;
	__u8	instance;
	__u32	flags;
	__u16	समयout;
	__u16	reमुख्यing_समय;
	__u16	duration;
	__u16	adv_data_len;
	__u8	adv_data[HCI_MAX_AD_LENGTH];
	__u16	scan_rsp_len;
	__u8	scan_rsp_data[HCI_MAX_AD_LENGTH];
	__s8	tx_घातer;
	__u32   min_पूर्णांकerval;
	__u32   max_पूर्णांकerval;
	bdaddr_t	अक्रमom_addr;
	bool 		rpa_expired;
	काष्ठा delayed_work	rpa_expired_cb;
पूर्ण;

#घोषणा HCI_MAX_ADV_INSTANCES		5
#घोषणा HCI_DEFAULT_ADV_DURATION	2

#घोषणा HCI_ADV_TX_POWER_NO_PREFERENCE 0x7F

काष्ठा adv_pattern अणु
	काष्ठा list_head list;
	__u8 ad_type;
	__u8 offset;
	__u8 length;
	__u8 value[HCI_MAX_AD_LENGTH];
पूर्ण;

काष्ठा adv_rssi_thresholds अणु
	__s8 low_threshold;
	__s8 high_threshold;
	__u16 low_threshold_समयout;
	__u16 high_threshold_समयout;
	__u8 sampling_period;
पूर्ण;

काष्ठा adv_monitor अणु
	काष्ठा list_head patterns;
	काष्ठा adv_rssi_thresholds rssi;
	__u16		handle;

	क्रमागत अणु
		ADV_MONITOR_STATE_NOT_REGISTERED,
		ADV_MONITOR_STATE_REGISTERED,
		ADV_MONITOR_STATE_OFFLOADED
	पूर्ण state;
पूर्ण;

#घोषणा HCI_MIN_ADV_MONITOR_HANDLE		1
#घोषणा HCI_MAX_ADV_MONITOR_NUM_HANDLES		32
#घोषणा HCI_MAX_ADV_MONITOR_NUM_PATTERNS	16
#घोषणा HCI_ADV_MONITOR_EXT_NONE		1
#घोषणा HCI_ADV_MONITOR_EXT_MSFT		2

#घोषणा HCI_MAX_SHORT_NAME_LENGTH	10

/* Min encryption key size to match with SMP */
#घोषणा HCI_MIN_ENC_KEY_SIZE		7

/* Default LE RPA expiry समय, 15 minutes */
#घोषणा HCI_DEFAULT_RPA_TIMEOUT		(15 * 60)

/* Default min/max age of connection inक्रमmation (1s/3s) */
#घोषणा DEFAULT_CONN_INFO_MIN_AGE	1000
#घोषणा DEFAULT_CONN_INFO_MAX_AGE	3000
/* Default authenticated payload समयout 30s */
#घोषणा DEFAULT_AUTH_PAYLOAD_TIMEOUT   0x0bb8

काष्ठा amp_assoc अणु
	__u16	len;
	__u16	offset;
	__u16	rem_len;
	__u16	len_so_far;
	__u8	data[HCI_MAX_AMP_ASSOC_SIZE];
पूर्ण;

#घोषणा HCI_MAX_PAGES	3

काष्ठा hci_dev अणु
	काष्ठा list_head list;
	काष्ठा mutex	lock;

	अक्षर		name[8];
	अचिन्हित दीर्घ	flags;
	__u16		id;
	__u8		bus;
	__u8		dev_type;
	bdaddr_t	bdaddr;
	bdaddr_t	setup_addr;
	bdaddr_t	खुला_addr;
	bdaddr_t	अक्रमom_addr;
	bdaddr_t	अटल_addr;
	__u8		adv_addr_type;
	__u8		dev_name[HCI_MAX_NAME_LENGTH];
	__u8		लघु_name[HCI_MAX_SHORT_NAME_LENGTH];
	__u8		eir[HCI_MAX_EIR_LENGTH];
	__u16		appearance;
	__u8		dev_class[3];
	__u8		major_class;
	__u8		minor_class;
	__u8		max_page;
	__u8		features[HCI_MAX_PAGES][8];
	__u8		le_features[8];
	__u8		le_white_list_size;
	__u8		le_resolv_list_size;
	__u8		le_num_of_adv_sets;
	__u8		le_states[8];
	__u8		commands[64];
	__u8		hci_ver;
	__u16		hci_rev;
	__u8		lmp_ver;
	__u16		manufacturer;
	__u16		lmp_subver;
	__u16		voice_setting;
	__u8		num_iac;
	__u8		stored_max_keys;
	__u8		stored_num_keys;
	__u8		io_capability;
	__s8		inq_tx_घातer;
	__u8		err_data_reporting;
	__u16		page_scan_पूर्णांकerval;
	__u16		page_scan_winकरोw;
	__u8		page_scan_type;
	__u8		le_adv_channel_map;
	__u16		le_adv_min_पूर्णांकerval;
	__u16		le_adv_max_पूर्णांकerval;
	__u8		le_scan_type;
	__u16		le_scan_पूर्णांकerval;
	__u16		le_scan_winकरोw;
	__u16		le_scan_पूर्णांक_suspend;
	__u16		le_scan_winकरोw_suspend;
	__u16		le_scan_पूर्णांक_discovery;
	__u16		le_scan_winकरोw_discovery;
	__u16		le_scan_पूर्णांक_adv_monitor;
	__u16		le_scan_winकरोw_adv_monitor;
	__u16		le_scan_पूर्णांक_connect;
	__u16		le_scan_winकरोw_connect;
	__u16		le_conn_min_पूर्णांकerval;
	__u16		le_conn_max_पूर्णांकerval;
	__u16		le_conn_latency;
	__u16		le_supv_समयout;
	__u16		le_def_tx_len;
	__u16		le_def_tx_समय;
	__u16		le_max_tx_len;
	__u16		le_max_tx_समय;
	__u16		le_max_rx_len;
	__u16		le_max_rx_समय;
	__u8		le_max_key_size;
	__u8		le_min_key_size;
	__u16		discov_पूर्णांकerleaved_समयout;
	__u16		conn_info_min_age;
	__u16		conn_info_max_age;
	__u16		auth_payload_समयout;
	__u8		min_enc_key_size;
	__u8		max_enc_key_size;
	__u8		pairing_opts;
	__u8		ssp_debug_mode;
	__u8		hw_error_code;
	__u32		घड़ी;
	__u16		advmon_allowlist_duration;
	__u16		advmon_no_filter_duration;
	__u8		enable_advmon_पूर्णांकerleave_scan;

	__u16		devid_source;
	__u16		devid_venकरोr;
	__u16		devid_product;
	__u16		devid_version;

	__u8		def_page_scan_type;
	__u16		def_page_scan_पूर्णांक;
	__u16		def_page_scan_winकरोw;
	__u8		def_inq_scan_type;
	__u16		def_inq_scan_पूर्णांक;
	__u16		def_inq_scan_winकरोw;
	__u16		def_br_lsto;
	__u16		def_page_समयout;
	__u16		def_multi_adv_rotation_duration;
	__u16		def_le_स्वतःconnect_समयout;
	__s8		min_le_tx_घातer;
	__s8		max_le_tx_घातer;

	__u16		pkt_type;
	__u16		esco_type;
	__u16		link_policy;
	__u16		link_mode;

	__u32		idle_समयout;
	__u16		snअगरf_min_पूर्णांकerval;
	__u16		snअगरf_max_पूर्णांकerval;

	__u8		amp_status;
	__u32		amp_total_bw;
	__u32		amp_max_bw;
	__u32		amp_min_latency;
	__u32		amp_max_pdu;
	__u8		amp_type;
	__u16		amp_pal_cap;
	__u16		amp_assoc_size;
	__u32		amp_max_flush_to;
	__u32		amp_be_flush_to;

	काष्ठा amp_assoc	loc_assoc;

	__u8		flow_ctl_mode;

	अचिन्हित पूर्णांक	स्वतः_accept_delay;

	अचिन्हित दीर्घ	quirks;

	atomic_t	cmd_cnt;
	अचिन्हित पूर्णांक	acl_cnt;
	अचिन्हित पूर्णांक	sco_cnt;
	अचिन्हित पूर्णांक	le_cnt;

	अचिन्हित पूर्णांक	acl_mtu;
	अचिन्हित पूर्णांक	sco_mtu;
	अचिन्हित पूर्णांक	le_mtu;
	अचिन्हित पूर्णांक	acl_pkts;
	अचिन्हित पूर्णांक	sco_pkts;
	अचिन्हित पूर्णांक	le_pkts;

	__u16		block_len;
	__u16		block_mtu;
	__u16		num_blocks;
	__u16		block_cnt;

	अचिन्हित दीर्घ	acl_last_tx;
	अचिन्हित दीर्घ	sco_last_tx;
	अचिन्हित दीर्घ	le_last_tx;

	__u8		le_tx_def_phys;
	__u8		le_rx_def_phys;

	काष्ठा workqueue_काष्ठा	*workqueue;
	काष्ठा workqueue_काष्ठा	*req_workqueue;

	काष्ठा work_काष्ठा	घातer_on;
	काष्ठा delayed_work	घातer_off;
	काष्ठा work_काष्ठा	error_reset;

	__u16			discov_समयout;
	काष्ठा delayed_work	discov_off;

	काष्ठा delayed_work	service_cache;

	काष्ठा delayed_work	cmd_समयr;

	काष्ठा work_काष्ठा	rx_work;
	काष्ठा work_काष्ठा	cmd_work;
	काष्ठा work_काष्ठा	tx_work;

	काष्ठा work_काष्ठा	discov_update;
	काष्ठा work_काष्ठा	bg_scan_update;
	काष्ठा work_काष्ठा	scan_update;
	काष्ठा work_काष्ठा	connectable_update;
	काष्ठा work_काष्ठा	discoverable_update;
	काष्ठा delayed_work	le_scan_disable;
	काष्ठा delayed_work	le_scan_restart;

	काष्ठा sk_buff_head	rx_q;
	काष्ठा sk_buff_head	raw_q;
	काष्ठा sk_buff_head	cmd_q;

	काष्ठा sk_buff		*sent_cmd;

	काष्ठा mutex		req_lock;
	रुको_queue_head_t	req_रुको_q;
	__u32			req_status;
	__u32			req_result;
	काष्ठा sk_buff		*req_skb;

	व्योम			*smp_data;
	व्योम			*smp_bredr_data;

	काष्ठा discovery_state	discovery;

	पूर्णांक			discovery_old_state;
	bool			discovery_छोड़ोd;
	पूर्णांक			advertising_old_state;
	bool			advertising_छोड़ोd;

	काष्ठा notअगरier_block	suspend_notअगरier;
	काष्ठा work_काष्ठा	suspend_prepare;
	क्रमागत suspended_state	suspend_state_next;
	क्रमागत suspended_state	suspend_state;
	bool			scanning_छोड़ोd;
	bool			suspended;
	u8			wake_reason;
	bdaddr_t		wake_addr;
	u8			wake_addr_type;

	रुको_queue_head_t	suspend_रुको_q;
	DECLARE_BITMAP(suspend_tasks, __SUSPEND_NUM_TASKS);

	काष्ठा hci_conn_hash	conn_hash;

	काष्ठा list_head	mgmt_pending;
	काष्ठा list_head	blacklist;
	काष्ठा list_head	whitelist;
	काष्ठा list_head	uuids;
	काष्ठा list_head	link_keys;
	काष्ठा list_head	दीर्घ_term_keys;
	काष्ठा list_head	identity_resolving_keys;
	काष्ठा list_head	remote_oob_data;
	काष्ठा list_head	le_white_list;
	काष्ठा list_head	le_resolv_list;
	काष्ठा list_head	le_conn_params;
	काष्ठा list_head	pend_le_conns;
	काष्ठा list_head	pend_le_reports;
	काष्ठा list_head	blocked_keys;

	काष्ठा hci_dev_stats	stat;

	atomic_t		promisc;

	स्थिर अक्षर		*hw_info;
	स्थिर अक्षर		*fw_info;
	काष्ठा dentry		*debugfs;

	काष्ठा device		dev;

	काष्ठा rfसमाप्त		*rfसमाप्त;

	DECLARE_BITMAP(dev_flags, __HCI_NUM_FLAGS);

	__s8			adv_tx_घातer;
	__u8			adv_data[HCI_MAX_AD_LENGTH];
	__u8			adv_data_len;
	__u8			scan_rsp_data[HCI_MAX_AD_LENGTH];
	__u8			scan_rsp_data_len;

	काष्ठा list_head	adv_instances;
	अचिन्हित पूर्णांक		adv_instance_cnt;
	__u8			cur_adv_instance;
	__u16			adv_instance_समयout;
	काष्ठा delayed_work	adv_instance_expire;

	काष्ठा idr		adv_monitors_idr;
	अचिन्हित पूर्णांक		adv_monitors_cnt;

	__u8			irk[16];
	__u32			rpa_समयout;
	काष्ठा delayed_work	rpa_expired;
	bdaddr_t		rpa;

	क्रमागत अणु
		INTERLEAVE_SCAN_NONE,
		INTERLEAVE_SCAN_NO_FILTER,
		INTERLEAVE_SCAN_ALLOWLIST
	पूर्ण पूर्णांकerleave_scan_state;

	काष्ठा delayed_work	पूर्णांकerleave_scan;

#अगर IS_ENABLED(CONFIG_BT_LEDS)
	काष्ठा led_trigger	*घातer_led;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_BT_MSFTEXT)
	__u16			msft_opcode;
	व्योम			*msft_data;
	bool			msft_curve_validity;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_BT_AOSPEXT)
	bool			aosp_capable;
#पूर्ण_अगर

	पूर्णांक (*खोलो)(काष्ठा hci_dev *hdev);
	पूर्णांक (*बंद)(काष्ठा hci_dev *hdev);
	पूर्णांक (*flush)(काष्ठा hci_dev *hdev);
	पूर्णांक (*setup)(काष्ठा hci_dev *hdev);
	पूर्णांक (*shutकरोwn)(काष्ठा hci_dev *hdev);
	पूर्णांक (*send)(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb);
	व्योम (*notअगरy)(काष्ठा hci_dev *hdev, अचिन्हित पूर्णांक evt);
	व्योम (*hw_error)(काष्ठा hci_dev *hdev, u8 code);
	पूर्णांक (*post_init)(काष्ठा hci_dev *hdev);
	पूर्णांक (*set_diag)(काष्ठा hci_dev *hdev, bool enable);
	पूर्णांक (*set_bdaddr)(काष्ठा hci_dev *hdev, स्थिर bdaddr_t *bdaddr);
	व्योम (*cmd_समयout)(काष्ठा hci_dev *hdev);
	bool (*prevent_wake)(काष्ठा hci_dev *hdev);
पूर्ण;

#घोषणा HCI_PHY_HANDLE(handle)	(handle & 0xff)

क्रमागत conn_reasons अणु
	CONN_REASON_PAIR_DEVICE,
	CONN_REASON_L2CAP_CHAN,
	CONN_REASON_SCO_CONNECT,
पूर्ण;

काष्ठा hci_conn अणु
	काष्ठा list_head list;

	atomic_t	refcnt;

	bdaddr_t	dst;
	__u8		dst_type;
	bdaddr_t	src;
	__u8		src_type;
	bdaddr_t	init_addr;
	__u8		init_addr_type;
	bdaddr_t	resp_addr;
	__u8		resp_addr_type;
	__u16		handle;
	__u16		state;
	__u8		mode;
	__u8		type;
	__u8		role;
	bool		out;
	__u8		attempt;
	__u8		dev_class[3];
	__u8		features[HCI_MAX_PAGES][8];
	__u16		pkt_type;
	__u16		link_policy;
	__u8		key_type;
	__u8		auth_type;
	__u8		sec_level;
	__u8		pending_sec_level;
	__u8		pin_length;
	__u8		enc_key_size;
	__u8		io_capability;
	__u32		passkey_notअगरy;
	__u8		passkey_entered;
	__u16		disc_समयout;
	__u16		conn_समयout;
	__u16		setting;
	__u16		auth_payload_समयout;
	__u16		le_conn_min_पूर्णांकerval;
	__u16		le_conn_max_पूर्णांकerval;
	__u16		le_conn_पूर्णांकerval;
	__u16		le_conn_latency;
	__u16		le_supv_समयout;
	__u8		le_adv_data[HCI_MAX_AD_LENGTH];
	__u8		le_adv_data_len;
	__u8		le_tx_phy;
	__u8		le_rx_phy;
	__s8		rssi;
	__s8		tx_घातer;
	__s8		max_tx_घातer;
	अचिन्हित दीर्घ	flags;

	क्रमागत conn_reasons conn_reason;

	__u32		घड़ी;
	__u16		घड़ी_accuracy;

	अचिन्हित दीर्घ	conn_info_बारtamp;

	__u8		remote_cap;
	__u8		remote_auth;
	__u8		remote_id;

	अचिन्हित पूर्णांक	sent;

	काष्ठा sk_buff_head data_q;
	काष्ठा list_head chan_list;

	काष्ठा delayed_work disc_work;
	काष्ठा delayed_work स्वतः_accept_work;
	काष्ठा delayed_work idle_work;
	काष्ठा delayed_work le_conn_समयout;
	काष्ठा work_काष्ठा  le_scan_cleanup;

	काष्ठा device	dev;
	काष्ठा dentry	*debugfs;

	काष्ठा hci_dev	*hdev;
	व्योम		*l2cap_data;
	व्योम		*sco_data;
	काष्ठा amp_mgr	*amp_mgr;

	काष्ठा hci_conn	*link;

	व्योम (*connect_cfm_cb)	(काष्ठा hci_conn *conn, u8 status);
	व्योम (*security_cfm_cb)	(काष्ठा hci_conn *conn, u8 status);
	व्योम (*disconn_cfm_cb)	(काष्ठा hci_conn *conn, u8 reason);
पूर्ण;

काष्ठा hci_chan अणु
	काष्ठा list_head list;
	__u16 handle;
	काष्ठा hci_conn *conn;
	काष्ठा sk_buff_head data_q;
	अचिन्हित पूर्णांक	sent;
	__u8		state;
	bool		amp;
पूर्ण;

काष्ठा hci_conn_params अणु
	काष्ठा list_head list;
	काष्ठा list_head action;

	bdaddr_t addr;
	u8 addr_type;

	u16 conn_min_पूर्णांकerval;
	u16 conn_max_पूर्णांकerval;
	u16 conn_latency;
	u16 supervision_समयout;

	क्रमागत अणु
		HCI_AUTO_CONN_DISABLED,
		HCI_AUTO_CONN_REPORT,
		HCI_AUTO_CONN_सूचीECT,
		HCI_AUTO_CONN_ALWAYS,
		HCI_AUTO_CONN_LINK_LOSS,
		HCI_AUTO_CONN_EXPLICIT,
	पूर्ण स्वतः_connect;

	काष्ठा hci_conn *conn;
	bool explicit_connect;
	u32 current_flags;
पूर्ण;

बाह्य काष्ठा list_head hci_dev_list;
बाह्य काष्ठा list_head hci_cb_list;
बाह्य rwlock_t hci_dev_list_lock;
बाह्य काष्ठा mutex hci_cb_list_lock;

#घोषणा hci_dev_set_flag(hdev, nr)             set_bit((nr), (hdev)->dev_flags)
#घोषणा hci_dev_clear_flag(hdev, nr)           clear_bit((nr), (hdev)->dev_flags)
#घोषणा hci_dev_change_flag(hdev, nr)          change_bit((nr), (hdev)->dev_flags)
#घोषणा hci_dev_test_flag(hdev, nr)            test_bit((nr), (hdev)->dev_flags)
#घोषणा hci_dev_test_and_set_flag(hdev, nr)    test_and_set_bit((nr), (hdev)->dev_flags)
#घोषणा hci_dev_test_and_clear_flag(hdev, nr)  test_and_clear_bit((nr), (hdev)->dev_flags)
#घोषणा hci_dev_test_and_change_flag(hdev, nr) test_and_change_bit((nr), (hdev)->dev_flags)

#घोषणा hci_dev_clear_अस्थिर_flags(hdev)			\
	करो अणु							\
		hci_dev_clear_flag(hdev, HCI_LE_SCAN);		\
		hci_dev_clear_flag(hdev, HCI_LE_ADV);		\
		hci_dev_clear_flag(hdev, HCI_LL_RPA_RESOLUTION);\
		hci_dev_clear_flag(hdev, HCI_PERIODIC_INQ);	\
	पूर्ण जबतक (0)

/* ----- HCI पूर्णांकerface to upper protocols ----- */
पूर्णांक l2cap_connect_ind(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr);
पूर्णांक l2cap_disconn_ind(काष्ठा hci_conn *hcon);
व्योम l2cap_recv_acldata(काष्ठा hci_conn *hcon, काष्ठा sk_buff *skb, u16 flags);

#अगर IS_ENABLED(CONFIG_BT_BREDR)
पूर्णांक sco_connect_ind(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr, __u8 *flags);
व्योम sco_recv_scodata(काष्ठा hci_conn *hcon, काष्ठा sk_buff *skb);
#अन्यथा
अटल अंतरभूत पूर्णांक sco_connect_ind(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
				  __u8 *flags)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sco_recv_scodata(काष्ठा hci_conn *hcon, काष्ठा sk_buff *skb)
अणु
पूर्ण
#पूर्ण_अगर

/* ----- Inquiry cache ----- */
#घोषणा INQUIRY_CACHE_AGE_MAX   (HZ*30)   /* 30 seconds */
#घोषणा INQUIRY_ENTRY_AGE_MAX   (HZ*60)   /* 60 seconds */

अटल अंतरभूत व्योम discovery_init(काष्ठा hci_dev *hdev)
अणु
	hdev->discovery.state = DISCOVERY_STOPPED;
	INIT_LIST_HEAD(&hdev->discovery.all);
	INIT_LIST_HEAD(&hdev->discovery.unknown);
	INIT_LIST_HEAD(&hdev->discovery.resolve);
	hdev->discovery.report_invalid_rssi = true;
	hdev->discovery.rssi = HCI_RSSI_INVALID;
पूर्ण

अटल अंतरभूत व्योम hci_discovery_filter_clear(काष्ठा hci_dev *hdev)
अणु
	hdev->discovery.result_filtering = false;
	hdev->discovery.report_invalid_rssi = true;
	hdev->discovery.rssi = HCI_RSSI_INVALID;
	hdev->discovery.uuid_count = 0;
	kमुक्त(hdev->discovery.uuids);
	hdev->discovery.uuids = शून्य;
	hdev->discovery.scan_start = 0;
	hdev->discovery.scan_duration = 0;
पूर्ण

bool hci_discovery_active(काष्ठा hci_dev *hdev);

व्योम hci_discovery_set_state(काष्ठा hci_dev *hdev, पूर्णांक state);

अटल अंतरभूत पूर्णांक inquiry_cache_empty(काष्ठा hci_dev *hdev)
अणु
	वापस list_empty(&hdev->discovery.all);
पूर्ण

अटल अंतरभूत दीर्घ inquiry_cache_age(काष्ठा hci_dev *hdev)
अणु
	काष्ठा discovery_state *c = &hdev->discovery;
	वापस jअगरfies - c->बारtamp;
पूर्ण

अटल अंतरभूत दीर्घ inquiry_entry_age(काष्ठा inquiry_entry *e)
अणु
	वापस jअगरfies - e->बारtamp;
पूर्ण

काष्ठा inquiry_entry *hci_inquiry_cache_lookup(काष्ठा hci_dev *hdev,
					       bdaddr_t *bdaddr);
काष्ठा inquiry_entry *hci_inquiry_cache_lookup_unknown(काष्ठा hci_dev *hdev,
						       bdaddr_t *bdaddr);
काष्ठा inquiry_entry *hci_inquiry_cache_lookup_resolve(काष्ठा hci_dev *hdev,
						       bdaddr_t *bdaddr,
						       पूर्णांक state);
व्योम hci_inquiry_cache_update_resolve(काष्ठा hci_dev *hdev,
				      काष्ठा inquiry_entry *ie);
u32 hci_inquiry_cache_update(काष्ठा hci_dev *hdev, काष्ठा inquiry_data *data,
			     bool name_known);
व्योम hci_inquiry_cache_flush(काष्ठा hci_dev *hdev);

/* ----- HCI Connections ----- */
क्रमागत अणु
	HCI_CONN_AUTH_PEND,
	HCI_CONN_REAUTH_PEND,
	HCI_CONN_ENCRYPT_PEND,
	HCI_CONN_RSWITCH_PEND,
	HCI_CONN_MODE_CHANGE_PEND,
	HCI_CONN_SCO_SETUP_PEND,
	HCI_CONN_MGMT_CONNECTED,
	HCI_CONN_SSP_ENABLED,
	HCI_CONN_SC_ENABLED,
	HCI_CONN_AES_CCM,
	HCI_CONN_POWER_SAVE,
	HCI_CONN_FLUSH_KEY,
	HCI_CONN_ENCRYPT,
	HCI_CONN_AUTH,
	HCI_CONN_SECURE,
	HCI_CONN_FIPS,
	HCI_CONN_STK_ENCRYPT,
	HCI_CONN_AUTH_INITIATOR,
	HCI_CONN_DROP,
	HCI_CONN_PARAM_REMOVAL_PEND,
	HCI_CONN_NEW_LINK_KEY,
	HCI_CONN_SCANNING,
	HCI_CONN_AUTH_FAILURE,
पूर्ण;

अटल अंतरभूत bool hci_conn_ssp_enabled(काष्ठा hci_conn *conn)
अणु
	काष्ठा hci_dev *hdev = conn->hdev;
	वापस hci_dev_test_flag(hdev, HCI_SSP_ENABLED) &&
	       test_bit(HCI_CONN_SSP_ENABLED, &conn->flags);
पूर्ण

अटल अंतरभूत bool hci_conn_sc_enabled(काष्ठा hci_conn *conn)
अणु
	काष्ठा hci_dev *hdev = conn->hdev;
	वापस hci_dev_test_flag(hdev, HCI_SC_ENABLED) &&
	       test_bit(HCI_CONN_SC_ENABLED, &conn->flags);
पूर्ण

अटल अंतरभूत व्योम hci_conn_hash_add(काष्ठा hci_dev *hdev, काष्ठा hci_conn *c)
अणु
	काष्ठा hci_conn_hash *h = &hdev->conn_hash;
	list_add_rcu(&c->list, &h->list);
	चयन (c->type) अणु
	हाल ACL_LINK:
		h->acl_num++;
		अवरोध;
	हाल AMP_LINK:
		h->amp_num++;
		अवरोध;
	हाल LE_LINK:
		h->le_num++;
		अगर (c->role == HCI_ROLE_SLAVE)
			h->le_num_slave++;
		अवरोध;
	हाल SCO_LINK:
	हाल ESCO_LINK:
		h->sco_num++;
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम hci_conn_hash_del(काष्ठा hci_dev *hdev, काष्ठा hci_conn *c)
अणु
	काष्ठा hci_conn_hash *h = &hdev->conn_hash;

	list_del_rcu(&c->list);
	synchronize_rcu();

	चयन (c->type) अणु
	हाल ACL_LINK:
		h->acl_num--;
		अवरोध;
	हाल AMP_LINK:
		h->amp_num--;
		अवरोध;
	हाल LE_LINK:
		h->le_num--;
		अगर (c->role == HCI_ROLE_SLAVE)
			h->le_num_slave--;
		अवरोध;
	हाल SCO_LINK:
	हाल ESCO_LINK:
		h->sco_num--;
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक hci_conn_num(काष्ठा hci_dev *hdev, __u8 type)
अणु
	काष्ठा hci_conn_hash *h = &hdev->conn_hash;
	चयन (type) अणु
	हाल ACL_LINK:
		वापस h->acl_num;
	हाल AMP_LINK:
		वापस h->amp_num;
	हाल LE_LINK:
		वापस h->le_num;
	हाल SCO_LINK:
	हाल ESCO_LINK:
		वापस h->sco_num;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक hci_conn_count(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_conn_hash *c = &hdev->conn_hash;

	वापस c->acl_num + c->amp_num + c->sco_num + c->le_num;
पूर्ण

अटल अंतरभूत __u8 hci_conn_lookup_type(काष्ठा hci_dev *hdev, __u16 handle)
अणु
	काष्ठा hci_conn_hash *h = &hdev->conn_hash;
	काष्ठा hci_conn *c;
	__u8 type = INVALID_LINK;

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(c, &h->list, list) अणु
		अगर (c->handle == handle) अणु
			type = c->type;
			अवरोध;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस type;
पूर्ण

अटल अंतरभूत काष्ठा hci_conn *hci_conn_hash_lookup_handle(काष्ठा hci_dev *hdev,
								__u16 handle)
अणु
	काष्ठा hci_conn_hash *h = &hdev->conn_hash;
	काष्ठा hci_conn  *c;

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(c, &h->list, list) अणु
		अगर (c->handle == handle) अणु
			rcu_पढ़ो_unlock();
			वापस c;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा hci_conn *hci_conn_hash_lookup_ba(काष्ठा hci_dev *hdev,
							__u8 type, bdaddr_t *ba)
अणु
	काष्ठा hci_conn_hash *h = &hdev->conn_hash;
	काष्ठा hci_conn  *c;

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(c, &h->list, list) अणु
		अगर (c->type == type && !bacmp(&c->dst, ba)) अणु
			rcu_पढ़ो_unlock();
			वापस c;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा hci_conn *hci_conn_hash_lookup_le(काष्ठा hci_dev *hdev,
						       bdaddr_t *ba,
						       __u8 ba_type)
अणु
	काष्ठा hci_conn_hash *h = &hdev->conn_hash;
	काष्ठा hci_conn  *c;

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(c, &h->list, list) अणु
		अगर (c->type != LE_LINK)
		       जारी;

		अगर (ba_type == c->dst_type && !bacmp(&c->dst, ba)) अणु
			rcu_पढ़ो_unlock();
			वापस c;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा hci_conn *hci_conn_hash_lookup_state(काष्ठा hci_dev *hdev,
							__u8 type, __u16 state)
अणु
	काष्ठा hci_conn_hash *h = &hdev->conn_hash;
	काष्ठा hci_conn  *c;

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(c, &h->list, list) अणु
		अगर (c->type == type && c->state == state) अणु
			rcu_पढ़ो_unlock();
			वापस c;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा hci_conn *hci_lookup_le_connect(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_conn_hash *h = &hdev->conn_hash;
	काष्ठा hci_conn  *c;

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(c, &h->list, list) अणु
		अगर (c->type == LE_LINK && c->state == BT_CONNECT &&
		    !test_bit(HCI_CONN_SCANNING, &c->flags)) अणु
			rcu_पढ़ो_unlock();
			वापस c;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस शून्य;
पूर्ण

पूर्णांक hci_disconnect(काष्ठा hci_conn *conn, __u8 reason);
bool hci_setup_sync(काष्ठा hci_conn *conn, __u16 handle);
व्योम hci_sco_setup(काष्ठा hci_conn *conn, __u8 status);

काष्ठा hci_conn *hci_conn_add(काष्ठा hci_dev *hdev, पूर्णांक type, bdaddr_t *dst,
			      u8 role);
पूर्णांक hci_conn_del(काष्ठा hci_conn *conn);
व्योम hci_conn_hash_flush(काष्ठा hci_dev *hdev);
व्योम hci_conn_check_pending(काष्ठा hci_dev *hdev);

काष्ठा hci_chan *hci_chan_create(काष्ठा hci_conn *conn);
व्योम hci_chan_del(काष्ठा hci_chan *chan);
व्योम hci_chan_list_flush(काष्ठा hci_conn *conn);
काष्ठा hci_chan *hci_chan_lookup_handle(काष्ठा hci_dev *hdev, __u16 handle);

काष्ठा hci_conn *hci_connect_le_scan(काष्ठा hci_dev *hdev, bdaddr_t *dst,
				     u8 dst_type, u8 sec_level,
				     u16 conn_समयout,
				     क्रमागत conn_reasons conn_reason);
काष्ठा hci_conn *hci_connect_le(काष्ठा hci_dev *hdev, bdaddr_t *dst,
				u8 dst_type, u8 sec_level, u16 conn_समयout,
				u8 role, bdaddr_t *direct_rpa);
काष्ठा hci_conn *hci_connect_acl(काष्ठा hci_dev *hdev, bdaddr_t *dst,
				 u8 sec_level, u8 auth_type,
				 क्रमागत conn_reasons conn_reason);
काष्ठा hci_conn *hci_connect_sco(काष्ठा hci_dev *hdev, पूर्णांक type, bdaddr_t *dst,
				 __u16 setting);
पूर्णांक hci_conn_check_link_mode(काष्ठा hci_conn *conn);
पूर्णांक hci_conn_check_secure(काष्ठा hci_conn *conn, __u8 sec_level);
पूर्णांक hci_conn_security(काष्ठा hci_conn *conn, __u8 sec_level, __u8 auth_type,
		      bool initiator);
पूर्णांक hci_conn_चयन_role(काष्ठा hci_conn *conn, __u8 role);

व्योम hci_conn_enter_active_mode(काष्ठा hci_conn *conn, __u8 क्रमce_active);

व्योम hci_le_conn_failed(काष्ठा hci_conn *conn, u8 status);

/*
 * hci_conn_get() and hci_conn_put() are used to control the lअगरe-समय of an
 * "hci_conn" object. They करो not guarantee that the hci_conn object is running,
 * working or anything अन्यथा. They just guarantee that the object is available
 * and can be dereferenced. So you can use its locks, local variables and any
 * other स्थिरant data.
 * Beक्रमe accessing runसमय data, you _must_ lock the object and then check that
 * it is still running. As soon as you release the locks, the connection might
 * get dropped, though.
 *
 * On the other hand, hci_conn_hold() and hci_conn_drop() are used to control
 * how दीर्घ the underlying connection is held. So every channel that runs on the
 * hci_conn object calls this to prevent the connection from disappearing. As
 * दीर्घ as you hold a device, you must also guarantee that you have a valid
 * reference to the device via hci_conn_get() (or the initial reference from
 * hci_conn_add()).
 * The hold()/drop() ref-count is known to drop below 0 someबार, which करोesn't
 * अवरोध because nobody cares क्रम that. But this means, we cannot use
 * _get()/_drop() in it, but require the caller to have a valid ref (FIXME).
 */

अटल अंतरभूत काष्ठा hci_conn *hci_conn_get(काष्ठा hci_conn *conn)
अणु
	get_device(&conn->dev);
	वापस conn;
पूर्ण

अटल अंतरभूत व्योम hci_conn_put(काष्ठा hci_conn *conn)
अणु
	put_device(&conn->dev);
पूर्ण

अटल अंतरभूत व्योम hci_conn_hold(काष्ठा hci_conn *conn)
अणु
	BT_DBG("hcon %p orig refcnt %d", conn, atomic_पढ़ो(&conn->refcnt));

	atomic_inc(&conn->refcnt);
	cancel_delayed_work(&conn->disc_work);
पूर्ण

अटल अंतरभूत व्योम hci_conn_drop(काष्ठा hci_conn *conn)
अणु
	BT_DBG("hcon %p orig refcnt %d", conn, atomic_पढ़ो(&conn->refcnt));

	अगर (atomic_dec_and_test(&conn->refcnt)) अणु
		अचिन्हित दीर्घ समयo;

		चयन (conn->type) अणु
		हाल ACL_LINK:
		हाल LE_LINK:
			cancel_delayed_work(&conn->idle_work);
			अगर (conn->state == BT_CONNECTED) अणु
				समयo = conn->disc_समयout;
				अगर (!conn->out)
					समयo *= 2;
			पूर्ण अन्यथा अणु
				समयo = 0;
			पूर्ण
			अवरोध;

		हाल AMP_LINK:
			समयo = conn->disc_समयout;
			अवरोध;

		शेष:
			समयo = 0;
			अवरोध;
		पूर्ण

		cancel_delayed_work(&conn->disc_work);
		queue_delayed_work(conn->hdev->workqueue,
				   &conn->disc_work, समयo);
	पूर्ण
पूर्ण

/* ----- HCI Devices ----- */
अटल अंतरभूत व्योम hci_dev_put(काष्ठा hci_dev *d)
अणु
	BT_DBG("%s orig refcnt %d", d->name,
	       kref_पढ़ो(&d->dev.kobj.kref));

	put_device(&d->dev);
पूर्ण

अटल अंतरभूत काष्ठा hci_dev *hci_dev_hold(काष्ठा hci_dev *d)
अणु
	BT_DBG("%s orig refcnt %d", d->name,
	       kref_पढ़ो(&d->dev.kobj.kref));

	get_device(&d->dev);
	वापस d;
पूर्ण

#घोषणा hci_dev_lock(d)		mutex_lock(&d->lock)
#घोषणा hci_dev_unlock(d)	mutex_unlock(&d->lock)

#घोषणा to_hci_dev(d) container_of(d, काष्ठा hci_dev, dev)
#घोषणा to_hci_conn(c) container_of(c, काष्ठा hci_conn, dev)

अटल अंतरभूत व्योम *hci_get_drvdata(काष्ठा hci_dev *hdev)
अणु
	वापस dev_get_drvdata(&hdev->dev);
पूर्ण

अटल अंतरभूत व्योम hci_set_drvdata(काष्ठा hci_dev *hdev, व्योम *data)
अणु
	dev_set_drvdata(&hdev->dev, data);
पूर्ण

काष्ठा hci_dev *hci_dev_get(पूर्णांक index);
काष्ठा hci_dev *hci_get_route(bdaddr_t *dst, bdaddr_t *src, u8 src_type);

काष्ठा hci_dev *hci_alloc_dev(व्योम);
व्योम hci_मुक्त_dev(काष्ठा hci_dev *hdev);
पूर्णांक hci_रेजिस्टर_dev(काष्ठा hci_dev *hdev);
व्योम hci_unरेजिस्टर_dev(काष्ठा hci_dev *hdev);
पूर्णांक hci_suspend_dev(काष्ठा hci_dev *hdev);
पूर्णांक hci_resume_dev(काष्ठा hci_dev *hdev);
पूर्णांक hci_reset_dev(काष्ठा hci_dev *hdev);
पूर्णांक hci_recv_frame(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb);
पूर्णांक hci_recv_diag(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb);
__म_लिखो(2, 3) व्योम hci_set_hw_info(काष्ठा hci_dev *hdev, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3) व्योम hci_set_fw_info(काष्ठा hci_dev *hdev, स्थिर अक्षर *fmt, ...);

अटल अंतरभूत व्योम hci_set_msft_opcode(काष्ठा hci_dev *hdev, __u16 opcode)
अणु
#अगर IS_ENABLED(CONFIG_BT_MSFTEXT)
	hdev->msft_opcode = opcode;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम hci_set_aosp_capable(काष्ठा hci_dev *hdev)
अणु
#अगर IS_ENABLED(CONFIG_BT_AOSPEXT)
	hdev->aosp_capable = true;
#पूर्ण_अगर
पूर्ण

पूर्णांक hci_dev_खोलो(__u16 dev);
पूर्णांक hci_dev_बंद(__u16 dev);
पूर्णांक hci_dev_करो_बंद(काष्ठा hci_dev *hdev);
पूर्णांक hci_dev_reset(__u16 dev);
पूर्णांक hci_dev_reset_stat(__u16 dev);
पूर्णांक hci_dev_cmd(अचिन्हित पूर्णांक cmd, व्योम __user *arg);
पूर्णांक hci_get_dev_list(व्योम __user *arg);
पूर्णांक hci_get_dev_info(व्योम __user *arg);
पूर्णांक hci_get_conn_list(व्योम __user *arg);
पूर्णांक hci_get_conn_info(काष्ठा hci_dev *hdev, व्योम __user *arg);
पूर्णांक hci_get_auth_info(काष्ठा hci_dev *hdev, व्योम __user *arg);
पूर्णांक hci_inquiry(व्योम __user *arg);

काष्ठा bdaddr_list *hci_bdaddr_list_lookup(काष्ठा list_head *list,
					   bdaddr_t *bdaddr, u8 type);
काष्ठा bdaddr_list_with_irk *hci_bdaddr_list_lookup_with_irk(
				    काष्ठा list_head *list, bdaddr_t *bdaddr,
				    u8 type);
काष्ठा bdaddr_list_with_flags *
hci_bdaddr_list_lookup_with_flags(काष्ठा list_head *list, bdaddr_t *bdaddr,
				  u8 type);
पूर्णांक hci_bdaddr_list_add(काष्ठा list_head *list, bdaddr_t *bdaddr, u8 type);
पूर्णांक hci_bdaddr_list_add_with_irk(काष्ठा list_head *list, bdaddr_t *bdaddr,
				 u8 type, u8 *peer_irk, u8 *local_irk);
पूर्णांक hci_bdaddr_list_add_with_flags(काष्ठा list_head *list, bdaddr_t *bdaddr,
				   u8 type, u32 flags);
पूर्णांक hci_bdaddr_list_del(काष्ठा list_head *list, bdaddr_t *bdaddr, u8 type);
पूर्णांक hci_bdaddr_list_del_with_irk(काष्ठा list_head *list, bdaddr_t *bdaddr,
				 u8 type);
पूर्णांक hci_bdaddr_list_del_with_flags(काष्ठा list_head *list, bdaddr_t *bdaddr,
				   u8 type);
व्योम hci_bdaddr_list_clear(काष्ठा list_head *list);

काष्ठा hci_conn_params *hci_conn_params_lookup(काष्ठा hci_dev *hdev,
					       bdaddr_t *addr, u8 addr_type);
काष्ठा hci_conn_params *hci_conn_params_add(काष्ठा hci_dev *hdev,
					    bdaddr_t *addr, u8 addr_type);
व्योम hci_conn_params_del(काष्ठा hci_dev *hdev, bdaddr_t *addr, u8 addr_type);
व्योम hci_conn_params_clear_disabled(काष्ठा hci_dev *hdev);

काष्ठा hci_conn_params *hci_pend_le_action_lookup(काष्ठा list_head *list,
						  bdaddr_t *addr,
						  u8 addr_type);

व्योम hci_uuids_clear(काष्ठा hci_dev *hdev);

व्योम hci_link_keys_clear(काष्ठा hci_dev *hdev);
काष्ठा link_key *hci_find_link_key(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr);
काष्ठा link_key *hci_add_link_key(काष्ठा hci_dev *hdev, काष्ठा hci_conn *conn,
				  bdaddr_t *bdaddr, u8 *val, u8 type,
				  u8 pin_len, bool *persistent);
काष्ठा smp_ltk *hci_add_ltk(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
			    u8 addr_type, u8 type, u8 authenticated,
			    u8 tk[16], u8 enc_size, __le16 eभाग, __le64 अक्रम);
काष्ठा smp_ltk *hci_find_ltk(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
			     u8 addr_type, u8 role);
पूर्णांक hci_हटाओ_ltk(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr, u8 bdaddr_type);
व्योम hci_smp_ltks_clear(काष्ठा hci_dev *hdev);
पूर्णांक hci_हटाओ_link_key(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr);

काष्ठा smp_irk *hci_find_irk_by_rpa(काष्ठा hci_dev *hdev, bdaddr_t *rpa);
काष्ठा smp_irk *hci_find_irk_by_addr(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
				     u8 addr_type);
काष्ठा smp_irk *hci_add_irk(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
			    u8 addr_type, u8 val[16], bdaddr_t *rpa);
व्योम hci_हटाओ_irk(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr, u8 addr_type);
bool hci_is_blocked_key(काष्ठा hci_dev *hdev, u8 type, u8 val[16]);
व्योम hci_blocked_keys_clear(काष्ठा hci_dev *hdev);
व्योम hci_smp_irks_clear(काष्ठा hci_dev *hdev);

bool hci_bdaddr_is_paired(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr, u8 type);

व्योम hci_remote_oob_data_clear(काष्ठा hci_dev *hdev);
काष्ठा oob_data *hci_find_remote_oob_data(काष्ठा hci_dev *hdev,
					  bdaddr_t *bdaddr, u8 bdaddr_type);
पूर्णांक hci_add_remote_oob_data(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
			    u8 bdaddr_type, u8 *hash192, u8 *अक्रम192,
			    u8 *hash256, u8 *अक्रम256);
पूर्णांक hci_हटाओ_remote_oob_data(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
			       u8 bdaddr_type);

व्योम hci_adv_instances_clear(काष्ठा hci_dev *hdev);
काष्ठा adv_info *hci_find_adv_instance(काष्ठा hci_dev *hdev, u8 instance);
काष्ठा adv_info *hci_get_next_instance(काष्ठा hci_dev *hdev, u8 instance);
पूर्णांक hci_add_adv_instance(काष्ठा hci_dev *hdev, u8 instance, u32 flags,
			 u16 adv_data_len, u8 *adv_data,
			 u16 scan_rsp_len, u8 *scan_rsp_data,
			 u16 समयout, u16 duration, s8 tx_घातer,
			 u32 min_पूर्णांकerval, u32 max_पूर्णांकerval);
पूर्णांक hci_set_adv_instance_data(काष्ठा hci_dev *hdev, u8 instance,
			 u16 adv_data_len, u8 *adv_data,
			 u16 scan_rsp_len, u8 *scan_rsp_data);
पूर्णांक hci_हटाओ_adv_instance(काष्ठा hci_dev *hdev, u8 instance);
व्योम hci_adv_instances_set_rpa_expired(काष्ठा hci_dev *hdev, bool rpa_expired);

व्योम hci_adv_monitors_clear(काष्ठा hci_dev *hdev);
व्योम hci_मुक्त_adv_monitor(काष्ठा hci_dev *hdev, काष्ठा adv_monitor *monitor);
पूर्णांक hci_add_adv_patterns_monitor_complete(काष्ठा hci_dev *hdev, u8 status);
पूर्णांक hci_हटाओ_adv_monitor_complete(काष्ठा hci_dev *hdev, u8 status);
bool hci_add_adv_monitor(काष्ठा hci_dev *hdev, काष्ठा adv_monitor *monitor,
			पूर्णांक *err);
bool hci_हटाओ_single_adv_monitor(काष्ठा hci_dev *hdev, u16 handle, पूर्णांक *err);
bool hci_हटाओ_all_adv_monitor(काष्ठा hci_dev *hdev, पूर्णांक *err);
bool hci_is_adv_monitoring(काष्ठा hci_dev *hdev);
पूर्णांक hci_get_adv_monitor_offload_ext(काष्ठा hci_dev *hdev);

व्योम hci_event_packet(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb);

व्योम hci_init_sysfs(काष्ठा hci_dev *hdev);
व्योम hci_conn_init_sysfs(काष्ठा hci_conn *conn);
व्योम hci_conn_add_sysfs(काष्ठा hci_conn *conn);
व्योम hci_conn_del_sysfs(काष्ठा hci_conn *conn);

#घोषणा SET_HCIDEV_DEV(hdev, pdev) ((hdev)->dev.parent = (pdev))

/* ----- LMP capabilities ----- */
#घोषणा lmp_encrypt_capable(dev)   ((dev)->features[0][0] & LMP_ENCRYPT)
#घोषणा lmp_rचयन_capable(dev)   ((dev)->features[0][0] & LMP_RSWITCH)
#घोषणा lmp_hold_capable(dev)      ((dev)->features[0][0] & LMP_HOLD)
#घोषणा lmp_snअगरf_capable(dev)     ((dev)->features[0][0] & LMP_SNIFF)
#घोषणा lmp_park_capable(dev)      ((dev)->features[0][1] & LMP_PARK)
#घोषणा lmp_inq_rssi_capable(dev)  ((dev)->features[0][3] & LMP_RSSI_INQ)
#घोषणा lmp_esco_capable(dev)      ((dev)->features[0][3] & LMP_ESCO)
#घोषणा lmp_bredr_capable(dev)     (!((dev)->features[0][4] & LMP_NO_BREDR))
#घोषणा lmp_le_capable(dev)        ((dev)->features[0][4] & LMP_LE)
#घोषणा lmp_snअगरfsubr_capable(dev) ((dev)->features[0][5] & LMP_SNIFF_SUBR)
#घोषणा lmp_छोड़ो_enc_capable(dev) ((dev)->features[0][5] & LMP_PAUSE_ENC)
#घोषणा lmp_esco_2m_capable(dev)   ((dev)->features[0][5] & LMP_EDR_ESCO_2M)
#घोषणा lmp_ext_inq_capable(dev)   ((dev)->features[0][6] & LMP_EXT_INQ)
#घोषणा lmp_le_br_capable(dev)     (!!((dev)->features[0][6] & LMP_SIMUL_LE_BR))
#घोषणा lmp_ssp_capable(dev)       ((dev)->features[0][6] & LMP_SIMPLE_PAIR)
#घोषणा lmp_no_flush_capable(dev)  ((dev)->features[0][6] & LMP_NO_FLUSH)
#घोषणा lmp_lsto_capable(dev)      ((dev)->features[0][7] & LMP_LSTO)
#घोषणा lmp_inq_tx_pwr_capable(dev) ((dev)->features[0][7] & LMP_INQ_TX_PWR)
#घोषणा lmp_ext_feat_capable(dev)  ((dev)->features[0][7] & LMP_EXTFEATURES)
#घोषणा lmp_transp_capable(dev)    ((dev)->features[0][2] & LMP_TRANSPARENT)
#घोषणा lmp_edr_2m_capable(dev)    ((dev)->features[0][3] & LMP_EDR_2M)
#घोषणा lmp_edr_3m_capable(dev)    ((dev)->features[0][3] & LMP_EDR_3M)
#घोषणा lmp_edr_3slot_capable(dev) ((dev)->features[0][4] & LMP_EDR_3SLOT)
#घोषणा lmp_edr_5slot_capable(dev) ((dev)->features[0][5] & LMP_EDR_5SLOT)

/* ----- Extended LMP capabilities ----- */
#घोषणा lmp_csb_master_capable(dev) ((dev)->features[2][0] & LMP_CSB_MASTER)
#घोषणा lmp_csb_slave_capable(dev)  ((dev)->features[2][0] & LMP_CSB_SLAVE)
#घोषणा lmp_sync_train_capable(dev) ((dev)->features[2][0] & LMP_SYNC_TRAIN)
#घोषणा lmp_sync_scan_capable(dev)  ((dev)->features[2][0] & LMP_SYNC_SCAN)
#घोषणा lmp_sc_capable(dev)         ((dev)->features[2][1] & LMP_SC)
#घोषणा lmp_ping_capable(dev)       ((dev)->features[2][1] & LMP_PING)

/* ----- Host capabilities ----- */
#घोषणा lmp_host_ssp_capable(dev)  ((dev)->features[1][0] & LMP_HOST_SSP)
#घोषणा lmp_host_sc_capable(dev)   ((dev)->features[1][0] & LMP_HOST_SC)
#घोषणा lmp_host_le_capable(dev)   (!!((dev)->features[1][0] & LMP_HOST_LE))
#घोषणा lmp_host_le_br_capable(dev) (!!((dev)->features[1][0] & LMP_HOST_LE_BREDR))

#घोषणा hdev_is_घातered(dev)   (test_bit(HCI_UP, &(dev)->flags) && \
				!hci_dev_test_flag(dev, HCI_AUTO_OFF))
#घोषणा bredr_sc_enabled(dev)  (lmp_sc_capable(dev) && \
				hci_dev_test_flag(dev, HCI_SC_ENABLED))

#घोषणा scan_1m(dev) (((dev)->le_tx_def_phys & HCI_LE_SET_PHY_1M) || \
		      ((dev)->le_rx_def_phys & HCI_LE_SET_PHY_1M))

#घोषणा scan_2m(dev) (((dev)->le_tx_def_phys & HCI_LE_SET_PHY_2M) || \
		      ((dev)->le_rx_def_phys & HCI_LE_SET_PHY_2M))

#घोषणा scan_coded(dev) (((dev)->le_tx_def_phys & HCI_LE_SET_PHY_CODED) || \
			 ((dev)->le_rx_def_phys & HCI_LE_SET_PHY_CODED))

/* Use LL Privacy based address resolution अगर supported */
#घोषणा use_ll_privacy(dev) ((dev)->le_features[0] & HCI_LE_LL_PRIVACY)

/* Use ext scanning अगर set ext scan param and ext scan enable is supported */
#घोषणा use_ext_scan(dev) (((dev)->commands[37] & 0x20) && \
			   ((dev)->commands[37] & 0x40))
/* Use ext create connection अगर command is supported */
#घोषणा use_ext_conn(dev) ((dev)->commands[37] & 0x80)

/* Extended advertising support */
#घोषणा ext_adv_capable(dev) (((dev)->le_features[1] & HCI_LE_EXT_ADV))

/* ----- HCI protocols ----- */
#घोषणा HCI_PROTO_DEFER             0x01

अटल अंतरभूत पूर्णांक hci_proto_connect_ind(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
					__u8 type, __u8 *flags)
अणु
	चयन (type) अणु
	हाल ACL_LINK:
		वापस l2cap_connect_ind(hdev, bdaddr);

	हाल SCO_LINK:
	हाल ESCO_LINK:
		वापस sco_connect_ind(hdev, bdaddr, flags);

	शेष:
		BT_ERR("unknown link type %d", type);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक hci_proto_disconn_ind(काष्ठा hci_conn *conn)
अणु
	अगर (conn->type != ACL_LINK && conn->type != LE_LINK)
		वापस HCI_ERROR_REMOTE_USER_TERM;

	वापस l2cap_disconn_ind(conn);
पूर्ण

/* ----- HCI callbacks ----- */
काष्ठा hci_cb अणु
	काष्ठा list_head list;

	अक्षर *name;

	व्योम (*connect_cfm)	(काष्ठा hci_conn *conn, __u8 status);
	व्योम (*disconn_cfm)	(काष्ठा hci_conn *conn, __u8 status);
	व्योम (*security_cfm)	(काष्ठा hci_conn *conn, __u8 status,
								__u8 encrypt);
	व्योम (*key_change_cfm)	(काष्ठा hci_conn *conn, __u8 status);
	व्योम (*role_चयन_cfm)	(काष्ठा hci_conn *conn, __u8 status, __u8 role);
पूर्ण;

अटल अंतरभूत व्योम hci_connect_cfm(काष्ठा hci_conn *conn, __u8 status)
अणु
	काष्ठा hci_cb *cb;

	mutex_lock(&hci_cb_list_lock);
	list_क्रम_each_entry(cb, &hci_cb_list, list) अणु
		अगर (cb->connect_cfm)
			cb->connect_cfm(conn, status);
	पूर्ण
	mutex_unlock(&hci_cb_list_lock);

	अगर (conn->connect_cfm_cb)
		conn->connect_cfm_cb(conn, status);
पूर्ण

अटल अंतरभूत व्योम hci_disconn_cfm(काष्ठा hci_conn *conn, __u8 reason)
अणु
	काष्ठा hci_cb *cb;

	mutex_lock(&hci_cb_list_lock);
	list_क्रम_each_entry(cb, &hci_cb_list, list) अणु
		अगर (cb->disconn_cfm)
			cb->disconn_cfm(conn, reason);
	पूर्ण
	mutex_unlock(&hci_cb_list_lock);

	अगर (conn->disconn_cfm_cb)
		conn->disconn_cfm_cb(conn, reason);
पूर्ण

अटल अंतरभूत व्योम hci_auth_cfm(काष्ठा hci_conn *conn, __u8 status)
अणु
	काष्ठा hci_cb *cb;
	__u8 encrypt;

	अगर (test_bit(HCI_CONN_ENCRYPT_PEND, &conn->flags))
		वापस;

	encrypt = test_bit(HCI_CONN_ENCRYPT, &conn->flags) ? 0x01 : 0x00;

	mutex_lock(&hci_cb_list_lock);
	list_क्रम_each_entry(cb, &hci_cb_list, list) अणु
		अगर (cb->security_cfm)
			cb->security_cfm(conn, status, encrypt);
	पूर्ण
	mutex_unlock(&hci_cb_list_lock);

	अगर (conn->security_cfm_cb)
		conn->security_cfm_cb(conn, status);
पूर्ण

अटल अंतरभूत व्योम hci_encrypt_cfm(काष्ठा hci_conn *conn, __u8 status)
अणु
	काष्ठा hci_cb *cb;
	__u8 encrypt;

	अगर (conn->state == BT_CONFIG) अणु
		अगर (!status)
			conn->state = BT_CONNECTED;

		hci_connect_cfm(conn, status);
		hci_conn_drop(conn);
		वापस;
	पूर्ण

	अगर (!test_bit(HCI_CONN_ENCRYPT, &conn->flags))
		encrypt = 0x00;
	अन्यथा अगर (test_bit(HCI_CONN_AES_CCM, &conn->flags))
		encrypt = 0x02;
	अन्यथा
		encrypt = 0x01;

	अगर (!status) अणु
		अगर (conn->sec_level == BT_SECURITY_SDP)
			conn->sec_level = BT_SECURITY_LOW;

		अगर (conn->pending_sec_level > conn->sec_level)
			conn->sec_level = conn->pending_sec_level;
	पूर्ण

	mutex_lock(&hci_cb_list_lock);
	list_क्रम_each_entry(cb, &hci_cb_list, list) अणु
		अगर (cb->security_cfm)
			cb->security_cfm(conn, status, encrypt);
	पूर्ण
	mutex_unlock(&hci_cb_list_lock);

	अगर (conn->security_cfm_cb)
		conn->security_cfm_cb(conn, status);
पूर्ण

अटल अंतरभूत व्योम hci_key_change_cfm(काष्ठा hci_conn *conn, __u8 status)
अणु
	काष्ठा hci_cb *cb;

	mutex_lock(&hci_cb_list_lock);
	list_क्रम_each_entry(cb, &hci_cb_list, list) अणु
		अगर (cb->key_change_cfm)
			cb->key_change_cfm(conn, status);
	पूर्ण
	mutex_unlock(&hci_cb_list_lock);
पूर्ण

अटल अंतरभूत व्योम hci_role_चयन_cfm(काष्ठा hci_conn *conn, __u8 status,
								__u8 role)
अणु
	काष्ठा hci_cb *cb;

	mutex_lock(&hci_cb_list_lock);
	list_क्रम_each_entry(cb, &hci_cb_list, list) अणु
		अगर (cb->role_चयन_cfm)
			cb->role_चयन_cfm(conn, status, role);
	पूर्ण
	mutex_unlock(&hci_cb_list_lock);
पूर्ण

अटल अंतरभूत व्योम *eir_get_data(u8 *eir, माप_प्रकार eir_len, u8 type,
				 माप_प्रकार *data_len)
अणु
	माप_प्रकार parsed = 0;

	अगर (eir_len < 2)
		वापस शून्य;

	जबतक (parsed < eir_len - 1) अणु
		u8 field_len = eir[0];

		अगर (field_len == 0)
			अवरोध;

		parsed += field_len + 1;

		अगर (parsed > eir_len)
			अवरोध;

		अगर (eir[1] != type) अणु
			eir += field_len + 1;
			जारी;
		पूर्ण

		/* Zero length data */
		अगर (field_len == 1)
			वापस शून्य;

		अगर (data_len)
			*data_len = field_len - 1;

		वापस &eir[2];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत bool hci_bdaddr_is_rpa(bdaddr_t *bdaddr, u8 addr_type)
अणु
	अगर (addr_type != ADDR_LE_DEV_RANDOM)
		वापस false;

	अगर ((bdaddr->b[5] & 0xc0) == 0x40)
	       वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool hci_is_identity_address(bdaddr_t *addr, u8 addr_type)
अणु
	अगर (addr_type == ADDR_LE_DEV_PUBLIC)
		वापस true;

	/* Check क्रम Ranकरोm Static address type */
	अगर ((addr->b[5] & 0xc0) == 0xc0)
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा smp_irk *hci_get_irk(काष्ठा hci_dev *hdev,
					  bdaddr_t *bdaddr, u8 addr_type)
अणु
	अगर (!hci_bdaddr_is_rpa(bdaddr, addr_type))
		वापस शून्य;

	वापस hci_find_irk_by_rpa(hdev, bdaddr);
पूर्ण

अटल अंतरभूत पूर्णांक hci_check_conn_params(u16 min, u16 max, u16 latency,
					u16 to_multiplier)
अणु
	u16 max_latency;

	अगर (min > max || min < 6 || max > 3200)
		वापस -EINVAL;

	अगर (to_multiplier < 10 || to_multiplier > 3200)
		वापस -EINVAL;

	अगर (max >= to_multiplier * 8)
		वापस -EINVAL;

	max_latency = (to_multiplier * 4 / max) - 1;
	अगर (latency > 499 || latency > max_latency)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक hci_रेजिस्टर_cb(काष्ठा hci_cb *hcb);
पूर्णांक hci_unरेजिस्टर_cb(काष्ठा hci_cb *hcb);

काष्ठा sk_buff *__hci_cmd_sync(काष्ठा hci_dev *hdev, u16 opcode, u32 plen,
			       स्थिर व्योम *param, u32 समयout);
काष्ठा sk_buff *__hci_cmd_sync_ev(काष्ठा hci_dev *hdev, u16 opcode, u32 plen,
				  स्थिर व्योम *param, u8 event, u32 समयout);
पूर्णांक __hci_cmd_send(काष्ठा hci_dev *hdev, u16 opcode, u32 plen,
		   स्थिर व्योम *param);

पूर्णांक hci_send_cmd(काष्ठा hci_dev *hdev, __u16 opcode, __u32 plen,
		 स्थिर व्योम *param);
व्योम hci_send_acl(काष्ठा hci_chan *chan, काष्ठा sk_buff *skb, __u16 flags);
व्योम hci_send_sco(काष्ठा hci_conn *conn, काष्ठा sk_buff *skb);

व्योम *hci_sent_cmd_data(काष्ठा hci_dev *hdev, __u16 opcode);

काष्ठा sk_buff *hci_cmd_sync(काष्ठा hci_dev *hdev, u16 opcode, u32 plen,
			     स्थिर व्योम *param, u32 समयout);

u32 hci_conn_get_phy(काष्ठा hci_conn *conn);

/* ----- HCI Sockets ----- */
व्योम hci_send_to_sock(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb);
व्योम hci_send_to_channel(अचिन्हित लघु channel, काष्ठा sk_buff *skb,
			 पूर्णांक flag, काष्ठा sock *skip_sk);
व्योम hci_send_to_monitor(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb);
व्योम hci_send_monitor_ctrl_event(काष्ठा hci_dev *hdev, u16 event,
				 व्योम *data, u16 data_len, kसमय_प्रकार tstamp,
				 पूर्णांक flag, काष्ठा sock *skip_sk);

व्योम hci_sock_dev_event(काष्ठा hci_dev *hdev, पूर्णांक event);

#घोषणा HCI_MGMT_VAR_LEN	BIT(0)
#घोषणा HCI_MGMT_NO_HDEV	BIT(1)
#घोषणा HCI_MGMT_UNTRUSTED	BIT(2)
#घोषणा HCI_MGMT_UNCONFIGURED	BIT(3)
#घोषणा HCI_MGMT_HDEV_OPTIONAL	BIT(4)

काष्ठा hci_mgmt_handler अणु
	पूर्णांक (*func) (काष्ठा sock *sk, काष्ठा hci_dev *hdev, व्योम *data,
		     u16 data_len);
	माप_प्रकार data_len;
	अचिन्हित दीर्घ flags;
पूर्ण;

काष्ठा hci_mgmt_chan अणु
	काष्ठा list_head list;
	अचिन्हित लघु channel;
	माप_प्रकार handler_count;
	स्थिर काष्ठा hci_mgmt_handler *handlers;
	व्योम (*hdev_init) (काष्ठा sock *sk, काष्ठा hci_dev *hdev);
पूर्ण;

पूर्णांक hci_mgmt_chan_रेजिस्टर(काष्ठा hci_mgmt_chan *c);
व्योम hci_mgmt_chan_unरेजिस्टर(काष्ठा hci_mgmt_chan *c);

/* Management पूर्णांकerface */
#घोषणा DISCOV_TYPE_BREDR		(BIT(BDADDR_BREDR))
#घोषणा DISCOV_TYPE_LE			(BIT(BDADDR_LE_PUBLIC) | \
					 BIT(BDADDR_LE_RANDOM))
#घोषणा DISCOV_TYPE_INTERLEAVED		(BIT(BDADDR_BREDR) | \
					 BIT(BDADDR_LE_PUBLIC) | \
					 BIT(BDADDR_LE_RANDOM))

/* These LE scan and inquiry parameters were chosen according to LE General
 * Discovery Procedure specअगरication.
 */
#घोषणा DISCOV_LE_SCAN_WIN		0x12
#घोषणा DISCOV_LE_SCAN_INT		0x12
#घोषणा DISCOV_LE_TIMEOUT		10240	/* msec */
#घोषणा DISCOV_INTERLEAVED_TIMEOUT	5120	/* msec */
#घोषणा DISCOV_INTERLEAVED_INQUIRY_LEN	0x04
#घोषणा DISCOV_BREDR_INQUIRY_LEN	0x08
#घोषणा DISCOV_LE_RESTART_DELAY		msecs_to_jअगरfies(200)	/* msec */
#घोषणा DISCOV_LE_FAST_ADV_पूर्णांक_न्यून	0x00A0	/* 100 msec */
#घोषणा DISCOV_LE_FAST_ADV_पूर्णांक_उच्च	0x00F0	/* 150 msec */

व्योम mgmt_fill_version_info(व्योम *ver);
पूर्णांक mgmt_new_settings(काष्ठा hci_dev *hdev);
व्योम mgmt_index_added(काष्ठा hci_dev *hdev);
व्योम mgmt_index_हटाओd(काष्ठा hci_dev *hdev);
व्योम mgmt_set_घातered_failed(काष्ठा hci_dev *hdev, पूर्णांक err);
व्योम mgmt_घातer_on(काष्ठा hci_dev *hdev, पूर्णांक err);
व्योम __mgmt_घातer_off(काष्ठा hci_dev *hdev);
व्योम mgmt_new_link_key(काष्ठा hci_dev *hdev, काष्ठा link_key *key,
		       bool persistent);
व्योम mgmt_device_connected(काष्ठा hci_dev *hdev, काष्ठा hci_conn *conn,
			   u32 flags, u8 *name, u8 name_len);
व्योम mgmt_device_disconnected(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
			      u8 link_type, u8 addr_type, u8 reason,
			      bool mgmt_connected);
व्योम mgmt_disconnect_failed(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
			    u8 link_type, u8 addr_type, u8 status);
व्योम mgmt_connect_failed(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr, u8 link_type,
			 u8 addr_type, u8 status);
व्योम mgmt_pin_code_request(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr, u8 secure);
व्योम mgmt_pin_code_reply_complete(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
				  u8 status);
व्योम mgmt_pin_code_neg_reply_complete(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
				      u8 status);
पूर्णांक mgmt_user_confirm_request(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
			      u8 link_type, u8 addr_type, u32 value,
			      u8 confirm_hपूर्णांक);
पूर्णांक mgmt_user_confirm_reply_complete(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
				     u8 link_type, u8 addr_type, u8 status);
पूर्णांक mgmt_user_confirm_neg_reply_complete(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
					 u8 link_type, u8 addr_type, u8 status);
पूर्णांक mgmt_user_passkey_request(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
			      u8 link_type, u8 addr_type);
पूर्णांक mgmt_user_passkey_reply_complete(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
				     u8 link_type, u8 addr_type, u8 status);
पूर्णांक mgmt_user_passkey_neg_reply_complete(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
					 u8 link_type, u8 addr_type, u8 status);
पूर्णांक mgmt_user_passkey_notअगरy(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
			     u8 link_type, u8 addr_type, u32 passkey,
			     u8 entered);
व्योम mgmt_auth_failed(काष्ठा hci_conn *conn, u8 status);
व्योम mgmt_auth_enable_complete(काष्ठा hci_dev *hdev, u8 status);
व्योम mgmt_ssp_enable_complete(काष्ठा hci_dev *hdev, u8 enable, u8 status);
व्योम mgmt_set_class_of_dev_complete(काष्ठा hci_dev *hdev, u8 *dev_class,
				    u8 status);
व्योम mgmt_set_local_name_complete(काष्ठा hci_dev *hdev, u8 *name, u8 status);
व्योम mgmt_start_discovery_complete(काष्ठा hci_dev *hdev, u8 status);
व्योम mgmt_stop_discovery_complete(काष्ठा hci_dev *hdev, u8 status);
व्योम mgmt_device_found(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr, u8 link_type,
		       u8 addr_type, u8 *dev_class, s8 rssi, u32 flags,
		       u8 *eir, u16 eir_len, u8 *scan_rsp, u8 scan_rsp_len);
व्योम mgmt_remote_name(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr, u8 link_type,
		      u8 addr_type, s8 rssi, u8 *name, u8 name_len);
व्योम mgmt_discovering(काष्ठा hci_dev *hdev, u8 discovering);
व्योम mgmt_suspending(काष्ठा hci_dev *hdev, u8 state);
व्योम mgmt_resuming(काष्ठा hci_dev *hdev, u8 reason, bdaddr_t *bdaddr,
		   u8 addr_type);
bool mgmt_घातering_करोwn(काष्ठा hci_dev *hdev);
व्योम mgmt_new_ltk(काष्ठा hci_dev *hdev, काष्ठा smp_ltk *key, bool persistent);
व्योम mgmt_new_irk(काष्ठा hci_dev *hdev, काष्ठा smp_irk *irk, bool persistent);
व्योम mgmt_new_csrk(काष्ठा hci_dev *hdev, काष्ठा smp_csrk *csrk,
		   bool persistent);
व्योम mgmt_new_conn_param(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
			 u8 bdaddr_type, u8 store_hपूर्णांक, u16 min_पूर्णांकerval,
			 u16 max_पूर्णांकerval, u16 latency, u16 समयout);
व्योम mgmt_smp_complete(काष्ठा hci_conn *conn, bool complete);
bool mgmt_get_connectable(काष्ठा hci_dev *hdev);
व्योम mgmt_set_connectable_complete(काष्ठा hci_dev *hdev, u8 status);
व्योम mgmt_set_discoverable_complete(काष्ठा hci_dev *hdev, u8 status);
u8 mgmt_get_adv_discov_flags(काष्ठा hci_dev *hdev);
व्योम mgmt_advertising_added(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			    u8 instance);
व्योम mgmt_advertising_हटाओd(काष्ठा sock *sk, काष्ठा hci_dev *hdev,
			      u8 instance);
व्योम mgmt_adv_monitor_हटाओd(काष्ठा hci_dev *hdev, u16 handle);
पूर्णांक mgmt_phy_configuration_changed(काष्ठा hci_dev *hdev, काष्ठा sock *skip);
पूर्णांक mgmt_add_adv_patterns_monitor_complete(काष्ठा hci_dev *hdev, u8 status);
पूर्णांक mgmt_हटाओ_adv_monitor_complete(काष्ठा hci_dev *hdev, u8 status);

u8 hci_le_conn_update(काष्ठा hci_conn *conn, u16 min, u16 max, u16 latency,
		      u16 to_multiplier);
व्योम hci_le_start_enc(काष्ठा hci_conn *conn, __le16 eभाग, __le64 अक्रम,
		      __u8 ltk[16], __u8 key_size);

व्योम hci_copy_identity_address(काष्ठा hci_dev *hdev, bdaddr_t *bdaddr,
			       u8 *bdaddr_type);

#घोषणा SCO_AIRMODE_MASK       0x0003
#घोषणा SCO_AIRMODE_CVSD       0x0000
#घोषणा SCO_AIRMODE_TRANSP     0x0003

#पूर्ण_अगर /* __HCI_CORE_H */
