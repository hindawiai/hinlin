<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*lcs.h*/

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/refcount.h>
#समावेश <यंत्र/ccwdev.h>

#घोषणा LCS_DBF_TEXT(level, name, text) \
	करो अणु \
		debug_text_event(lcs_dbf_##name, level, text); \
	पूर्ण जबतक (0)

#घोषणा LCS_DBF_HEX(level,name,addr,len) \
करो अणु \
	debug_event(lcs_dbf_##name,level,(व्योम*)(addr),len); \
पूर्ण जबतक (0)

#घोषणा LCS_DBF_TEXT_(level,name,text...) \
	करो अणु \
		अगर (debug_level_enabled(lcs_dbf_##name, level)) अणु \
			प्र_लिखो(debug_buffer, text); \
			debug_text_event(lcs_dbf_##name, level, debug_buffer); \
		पूर्ण \
	पूर्ण जबतक (0)

/**
 *	sysfs related stuff
 */
#घोषणा CARD_FROM_DEV(cdev) \
	(काष्ठा lcs_card *) dev_get_drvdata( \
		&((काष्ठा ccwgroup_device *)dev_get_drvdata(&cdev->dev))->dev);

/**
 * Enum क्रम classअगरying detected devices.
 */
क्रमागत lcs_channel_types अणु
	/* Device is not a channel  */
	lcs_channel_type_none,

	/* Device is a 2216 channel */
	lcs_channel_type_parallel,

	/* Device is a 2216 channel */
	lcs_channel_type_2216,

	/* Device is a OSA2 card */
	lcs_channel_type_osa2
पूर्ण;

/**
 * CCW commands used in this driver
 */
#घोषणा LCS_CCW_WRITE		0x01
#घोषणा LCS_CCW_READ		0x02
#घोषणा LCS_CCW_TRANSFER	0x08

/**
 * LCS device status primitives
 */
#घोषणा LCS_CMD_STARTLAN	0x01
#घोषणा LCS_CMD_STOPLAN		0x02
#घोषणा LCS_CMD_LANSTAT		0x04
#घोषणा LCS_CMD_STARTUP		0x07
#घोषणा LCS_CMD_SHUTDOWN	0x08
#घोषणा LCS_CMD_QIPASSIST	0xb2
#घोषणा LCS_CMD_SETIPM		0xb4
#घोषणा LCS_CMD_DELIPM		0xb5

#घोषणा LCS_INITIATOR_TCPIP	0x00
#घोषणा LCS_INITIATOR_LGW	0x01
#घोषणा LCS_STD_CMD_SIZE	16
#घोषणा LCS_MULTICAST_CMD_SIZE	404

/**
 * LCS IPASSIST MASKS,only used when multicast is चयनed on
 */
/* Not supported by LCS */
#घोषणा LCS_IPASS_ARP_PROCESSING	0x0001
#घोषणा LCS_IPASS_IN_CHECKSUM_SUPPORT	0x0002
#घोषणा LCS_IPASS_OUT_CHECKSUM_SUPPORT	0x0004
#घोषणा LCS_IPASS_IP_FRAG_REASSEMBLY	0x0008
#घोषणा LCS_IPASS_IP_FILTERING		0x0010
/* Supported by lcs 3172 */
#घोषणा LCS_IPASS_IPV6_SUPPORT		0x0020
#घोषणा LCS_IPASS_MULTICAST_SUPPORT	0x0040

/**
 * LCS sense byte definitions
 */
#घोषणा LCS_SENSE_BYTE_0 		0
#घोषणा LCS_SENSE_BYTE_1 		1
#घोषणा LCS_SENSE_BYTE_2 		2
#घोषणा LCS_SENSE_BYTE_3 		3
#घोषणा LCS_SENSE_INTERFACE_DISCONNECT	0x01
#घोषणा LCS_SENSE_EQUIPMENT_CHECK	0x10
#घोषणा LCS_SENSE_BUS_OUT_CHECK		0x20
#घोषणा LCS_SENSE_INTERVENTION_REQUIRED 0x40
#घोषणा LCS_SENSE_CMD_REJECT		0x80
#घोषणा LCS_SENSE_RESETTING_EVENT	0x80
#घोषणा LCS_SENSE_DEVICE_ONLINE		0x20

/**
 * LCS packet type definitions
 */
#घोषणा LCS_FRAME_TYPE_CONTROL		0
#घोषणा LCS_FRAME_TYPE_ENET		1
#घोषणा LCS_FRAME_TYPE_TR		2
#घोषणा LCS_FRAME_TYPE_FDDI		7
#घोषणा LCS_FRAME_TYPE_AUTO		-1

/**
 * some more definitions,we will sort them later
 */
#घोषणा LCS_ILLEGAL_OFFSET		0xffff
#घोषणा LCS_IOBUFFERSIZE		0x5000
#घोषणा LCS_NUM_BUFFS			32	/* needs to be घातer of 2 */
#घोषणा LCS_MAC_LENGTH			6
#घोषणा LCS_INVALID_PORT_NO		-1
#घोषणा LCS_LANCMD_TIMEOUT_DEFAULT      5

/**
 * Multicast state
 */
#घोषणा	 LCS_IPM_STATE_SET_REQUIRED	0
#घोषणा	 LCS_IPM_STATE_DEL_REQUIRED	1
#घोषणा	 LCS_IPM_STATE_ON_CARD		2

/**
 * LCS IP Assist declarations
 * seems to be only used क्रम multicast
 */
#घोषणा	 LCS_IPASS_ARP_PROCESSING	0x0001
#घोषणा	 LCS_IPASS_INBOUND_CSUM_SUPP	0x0002
#घोषणा	 LCS_IPASS_OUTBOUND_CSUM_SUPP	0x0004
#घोषणा	 LCS_IPASS_IP_FRAG_REASSEMBLY	0x0008
#घोषणा	 LCS_IPASS_IP_FILTERING		0x0010
#घोषणा	 LCS_IPASS_IPV6_SUPPORT		0x0020
#घोषणा	 LCS_IPASS_MULTICAST_SUPPORT	0x0040

/**
 * LCS Buffer states
 */
क्रमागत lcs_buffer_states अणु
	LCS_BUF_STATE_EMPTY,	/* buffer is empty */
	LCS_BUF_STATE_LOCKED,	/* buffer is locked, करोn't touch */
	LCS_BUF_STATE_READY,	/* buffer is पढ़ोy क्रम पढ़ो/ग_लिखो */
	LCS_BUF_STATE_PROCESSED,
पूर्ण;

/**
 * LCS Channel State Machine declarations
 */
क्रमागत lcs_channel_states अणु
	LCS_CH_STATE_INIT,
	LCS_CH_STATE_HALTED,
	LCS_CH_STATE_STOPPED,
	LCS_CH_STATE_RUNNING,
	LCS_CH_STATE_SUSPENDED,
	LCS_CH_STATE_CLEARED,
	LCS_CH_STATE_ERROR,
पूर्ण;

/**
 * LCS device state machine
 */
क्रमागत lcs_dev_states अणु
	DEV_STATE_DOWN,
	DEV_STATE_UP,
	DEV_STATE_RECOVER,
पूर्ण;

क्रमागत lcs_thपढ़ोs अणु
	LCS_SET_MC_THREAD 	= 1,
	LCS_RECOVERY_THREAD 	= 2,
पूर्ण;

/**
 * LCS काष्ठा declarations
 */
काष्ठा lcs_header अणु
	__u16  offset;
	__u8   type;
	__u8   slot;
पूर्ण  __attribute__ ((packed));

काष्ठा lcs_ip_mac_pair अणु
	__be32  ip_addr;
	__u8   mac_addr[LCS_MAC_LENGTH];
	__u8   reserved[2];
पूर्ण  __attribute__ ((packed));

काष्ठा lcs_ipm_list अणु
	काष्ठा list_head list;
	काष्ठा lcs_ip_mac_pair ipm;
	__u8 ipm_state;
पूर्ण;

काष्ठा lcs_cmd अणु
	__u16  offset;
	__u8   type;
	__u8   slot;
	__u8   cmd_code;
	__u8   initiator;
	__u16  sequence_no;
	__u16  वापस_code;
	जोड़ अणु
		काष्ठा अणु
			__u8   lan_type;
			__u8   portno;
			__u16  parameter_count;
			__u8   चालक_flags[3];
			__u8   reserved[3];
		पूर्ण lcs_std_cmd;
		काष्ठा अणु
			__u16  unused1;
			__u16  buff_size;
			__u8   unused2[6];
		पूर्ण lcs_startup;
		काष्ठा अणु
			__u8   lan_type;
			__u8   portno;
			__u8   unused[10];
			__u8   mac_addr[LCS_MAC_LENGTH];
			__u32  num_packets_deblocked;
			__u32  num_packets_blocked;
			__u32  num_packets_tx_on_lan;
			__u32  num_tx_errors_detected;
			__u32  num_tx_packets_disgarded;
			__u32  num_packets_rx_from_lan;
			__u32  num_rx_errors_detected;
			__u32  num_rx_discarded_nobuffs_avail;
			__u32  num_rx_packets_too_large;
		पूर्ण lcs_lanstat_cmd;
#अगर_घोषित CONFIG_IP_MULTICAST
		काष्ठा अणु
			__u8   lan_type;
			__u8   portno;
			__u16  num_ip_pairs;
			__u16  ip_assists_supported;
			__u16  ip_assists_enabled;
			__u16  version;
			काष्ठा अणु
				काष्ठा lcs_ip_mac_pair
				ip_mac_pair[32];
				__u32	  response_data;
			पूर्ण lcs_ipass_ctlmsg __attribute ((packed));
		पूर्ण lcs_qipassist __attribute__ ((packed));
#पूर्ण_अगर /*CONFIG_IP_MULTICAST */
	पूर्ण cmd __attribute__ ((packed));
पूर्ण  __attribute__ ((packed));

/**
 * Forward declarations.
 */
काष्ठा lcs_card;
काष्ठा lcs_channel;

/**
 * Definition of an lcs buffer.
 */
काष्ठा lcs_buffer अणु
	क्रमागत lcs_buffer_states state;
	व्योम *data;
	पूर्णांक count;
	/* Callback क्रम completion notअगरication. */
	व्योम (*callback)(काष्ठा lcs_channel *, काष्ठा lcs_buffer *);
पूर्ण;

काष्ठा lcs_reply अणु
	काष्ठा list_head list;
	__u16 sequence_no;
	refcount_t refcnt;
	/* Callback क्रम completion notअगरication. */
	व्योम (*callback)(काष्ठा lcs_card *, काष्ठा lcs_cmd *);
	रुको_queue_head_t रुको_q;
	काष्ठा lcs_card *card;
	काष्ठा समयr_list समयr;
	पूर्णांक received;
	पूर्णांक rc;
पूर्ण;

/**
 * Definition of an lcs channel
 */
काष्ठा lcs_channel अणु
	क्रमागत lcs_channel_states state;
	काष्ठा ccw_device *ccwdev;
	काष्ठा ccw1 ccws[LCS_NUM_BUFFS + 1];
	रुको_queue_head_t रुको_q;
	काष्ठा tasklet_काष्ठा irq_tasklet;
	काष्ठा lcs_buffer iob[LCS_NUM_BUFFS];
	पूर्णांक io_idx;
	पूर्णांक buf_idx;
पूर्ण;


/**
 * definition of the lcs card
 */
काष्ठा lcs_card अणु
	spinlock_t lock;
	spinlock_t ipm_lock;
	क्रमागत lcs_dev_states state;
	काष्ठा net_device *dev;
	काष्ठा net_device_stats stats;
	__be16 (*lan_type_trans)(काष्ठा sk_buff *skb,
					 काष्ठा net_device *dev);
	काष्ठा ccwgroup_device *gdev;
	काष्ठा lcs_channel पढ़ो;
	काष्ठा lcs_channel ग_लिखो;
	काष्ठा lcs_buffer *tx_buffer;
	पूर्णांक tx_emitted;
	काष्ठा list_head lancmd_रुकोers;
	पूर्णांक lancmd_समयout;

	काष्ठा work_काष्ठा kernel_thपढ़ो_starter;
	spinlock_t mask_lock;
	अचिन्हित दीर्घ thपढ़ो_start_mask;
	अचिन्हित दीर्घ thपढ़ो_running_mask;
	अचिन्हित दीर्घ thपढ़ो_allowed_mask;
	रुको_queue_head_t रुको_q;

#अगर_घोषित CONFIG_IP_MULTICAST
	काष्ठा list_head ipm_list;
#पूर्ण_अगर
	__u8 mac[LCS_MAC_LENGTH];
	__u16 ip_assists_supported;
	__u16 ip_assists_enabled;
	__s8 lan_type;
	__u32 pkt_seq;
	__u16 sequence_no;
	__s16 portno;
	/* Some info copied from probeinfo */
	u8 device_क्रमced;
	u8 max_port_no;
	u8 hपूर्णांक_port_no;
	s16 port_protocol_no;
पूर्ण  __attribute__ ((aligned(8)));

