<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Shared Transport Header file
 *	To be included by the protocol stack drivers क्रम
 *	Texas Instruments BT,FM and GPS combo chip drivers
 *	and also serves the sub-modules of the shared transport driver.
 *
 *  Copyright (C) 2009-2010 Texas Instruments
 *  Author: Pavan Savoy <pavan_savoy@ti.com>
 */

#अगर_अघोषित TI_WILINK_ST_H
#घोषणा TI_WILINK_ST_H

#समावेश <linux/skbuff.h>

/**
 * क्रमागत proto-type - The protocol on WiLink chips which share a
 *	common physical पूर्णांकerface like UART.
 */
क्रमागत proto_type अणु
	ST_BT,
	ST_FM,
	ST_GPS,
	ST_MAX_CHANNELS = 16,
पूर्ण;

/**
 * काष्ठा st_proto_s - Per Protocol काष्ठाure from BT/FM/GPS to ST
 * @type: type of the protocol being रेजिस्टरed among the
 *	available proto_type(BT, FM, GPS the protocol which share TTY).
 * @recv: the receiver callback poपूर्णांकing to a function in the
 *	protocol drivers called by the ST driver upon receiving
 *	relevant data.
 * @match_packet: reserved क्रम future use, to make ST more generic
 * @reg_complete_cb: callback handler poपूर्णांकing to a function in protocol
 *	handler called by ST when the pending registrations are complete.
 *	The registrations are marked pending, in situations when fw
 *	करोwnload is in progress.
 * @ग_लिखो: poपूर्णांकer to function in ST provided to protocol drivers from ST,
 *	to be made use when protocol drivers have data to send to TTY.
 * @priv_data: privdate data holder क्रम the protocol drivers, sent
 *	from the protocol drivers during registration, and sent back on
 *	reg_complete_cb and recv.
 * @chnl_id: channel id the protocol driver is पूर्णांकerested in, the channel
 *	id is nothing but the 1st byte of the packet in UART frame.
 * @max_frame_size: size of the largest frame the protocol can receive.
 * @hdr_len: length of the header काष्ठाure of the protocol.
 * @offset_len_in_hdr: this provides the offset of the length field in the
 *	header काष्ठाure of the protocol header, to assist ST to know
 *	how much to receive, अगर the data is split across UART frames.
 * @len_size: whether the length field inside the header is 2 bytes
 *	or 1 byte.
 * @reserve: the number of bytes ST needs to reserve in the skb being
 *	prepared क्रम the protocol driver.
 */
काष्ठा st_proto_s अणु
	क्रमागत proto_type type;
	दीर्घ (*recv) (व्योम *, काष्ठा sk_buff *);
	अचिन्हित अक्षर (*match_packet) (स्थिर अचिन्हित अक्षर *data);
	व्योम (*reg_complete_cb) (व्योम *, पूर्णांक data);
	दीर्घ (*ग_लिखो) (काष्ठा sk_buff *skb);
	व्योम *priv_data;

	अचिन्हित अक्षर chnl_id;
	अचिन्हित लघु max_frame_size;
	अचिन्हित अक्षर hdr_len;
	अचिन्हित अक्षर offset_len_in_hdr;
	अचिन्हित अक्षर len_size;
	अचिन्हित अक्षर reserve;
पूर्ण;

बाह्य दीर्घ st_रेजिस्टर(काष्ठा st_proto_s *);
बाह्य दीर्घ st_unरेजिस्टर(काष्ठा st_proto_s *);


/*
 * header inक्रमmation used by st_core.c
 */

/* states of protocol list */
#घोषणा ST_NOTEMPTY	1
#घोषणा ST_EMPTY	0

/*
 * possible st_states
 */
#घोषणा ST_INITIALIZING		1
#घोषणा ST_REG_IN_PROGRESS	2
#घोषणा ST_REG_PENDING		3
#घोषणा ST_WAITING_FOR_RESP	4

/**
 * काष्ठा st_data_s - ST core पूर्णांकernal काष्ठाure
 * @st_state: dअगरferent states of ST like initializing, registration
 *	in progress, this is मुख्यly used to वापस relevant err codes
 *	when protocol drivers are रेजिस्टरing. It is also used to track
 *	the recv function, as in during fw करोwnload only HCI events
 *	can occur , where as during other बार other events CH8, CH9
 *	can occur.
 * @tty: tty provided by the TTY core क्रम line disciplines.
 * @tx_skb: If क्रम some reason the tty's ग_लिखो वापसs lesser bytes written
 *	then to मुख्यtain the rest of data to be written on next instance.
 *	This needs to be रक्षित, hence the lock inside wakeup func.
 * @tx_state: अगर the data is being written onto the TTY and protocol driver
 *	wants to send more, queue up data and mark that there is
 *	more data to send.
 * @list: the list of protocols रेजिस्टरed, only MAX can exist, one protocol
 *	can रेजिस्टर only once.
 * @rx_state: states to be मुख्यtained inside st's tty receive
 * @rx_count: count to be मुख्यtained inside st's tty receieve
 * @rx_skb: the skb where all data क्रम a protocol माला_लो accumulated,
 *	since tty might not call receive when a complete event packet
 *	is received, the states, count and the skb needs to be मुख्यtained.
 * @rx_chnl: the channel ID क्रम which the data is getting accumalated क्रम.
 * @txq: the list of skbs which needs to be sent onto the TTY.
 * @tx_रुकोq: अगर the chip is not in AWAKE state, the skbs needs to be queued
 *	up in here, PM(WAKEUP_IND) data needs to be sent and then the skbs
 *	from रुकोq can be moved onto the txq.
 *	Needs locking too.
 * @lock: the lock to protect skbs, queues, and ST states.
 * @protos_रेजिस्टरed: count of the protocols रेजिस्टरed, also when 0 the
 *	chip enable gpio can be toggled, and when it changes to 1 the fw
 *	needs to be करोwnloaded to initialize chip side ST.
 * @ll_state: the various PM states the chip can be, the states are notअगरied
 *	to us, when the chip sends relevant PM packets(SLEEP_IND, WAKE_IND).
 * @kim_data: reference to the parent encapsulating काष्ठाure.
 *
 */
काष्ठा st_data_s अणु
	अचिन्हित दीर्घ st_state;
	काष्ठा sk_buff *tx_skb;
#घोषणा ST_TX_SENDING	1
#घोषणा ST_TX_WAKEUP	2
	अचिन्हित दीर्घ tx_state;
	काष्ठा st_proto_s *list[ST_MAX_CHANNELS];
	bool is_रेजिस्टरed[ST_MAX_CHANNELS];
	अचिन्हित दीर्घ rx_state;
	अचिन्हित दीर्घ rx_count;
	काष्ठा sk_buff *rx_skb;
	अचिन्हित अक्षर rx_chnl;
	काष्ठा sk_buff_head txq, tx_रुकोq;
	spinlock_t lock;
	अचिन्हित अक्षर	protos_रेजिस्टरed;
	अचिन्हित दीर्घ ll_state;
	व्योम *kim_data;
	काष्ठा tty_काष्ठा *tty;
	काष्ठा work_काष्ठा work_ग_लिखो_wakeup;
पूर्ण;

/*
 * wrapper around tty->ops->ग_लिखो_room to check
 * availability during firmware करोwnload
 */
पूर्णांक st_get_uart_wr_room(काष्ठा st_data_s *st_gdata);
/**
 * st_पूर्णांक_ग_लिखो -
 * poपूर्णांक this to tty->driver->ग_लिखो or tty->ops->ग_लिखो
 * depending upon the kernel version
 */
पूर्णांक st_पूर्णांक_ग_लिखो(काष्ठा st_data_s*, स्थिर अचिन्हित अक्षर*, पूर्णांक);

/**
 * st_ग_लिखो -
 * पूर्णांकernal ग_लिखो function, passed onto protocol drivers
 * via the ग_लिखो function ptr of protocol काष्ठा
 */
दीर्घ st_ग_लिखो(काष्ठा sk_buff *);

/* function to be called from ST-LL */
व्योम st_ll_send_frame(क्रमागत proto_type, काष्ठा sk_buff *);

/* पूर्णांकernal wake up function */
व्योम st_tx_wakeup(काष्ठा st_data_s *st_data);

/* init, निकास entry funcs called from KIM */
पूर्णांक st_core_init(काष्ठा st_data_s **);
व्योम st_core_निकास(काष्ठा st_data_s *);

/* ask क्रम reference from KIM */
व्योम st_kim_ref(काष्ठा st_data_s **, पूर्णांक);

#घोषणा GPS_STUB_TEST
#अगर_घोषित GPS_STUB_TEST
पूर्णांक gps_chrdrv_stub_ग_लिखो(स्थिर अचिन्हित अक्षर*, पूर्णांक);
व्योम gps_chrdrv_stub_init(व्योम);
#पूर्ण_अगर

/*
 * header inक्रमmation used by st_kim.c
 */

/* समय in msec to रुको क्रम
 * line discipline to be installed
 */
#घोषणा LDISC_TIME	1000
#घोषणा CMD_RESP_TIME	800
#घोषणा CMD_WR_TIME	5000
#घोषणा MAKEWORD(a, b)  ((अचिन्हित लघु)(((अचिन्हित अक्षर)(a)) \
	| ((अचिन्हित लघु)((अचिन्हित अक्षर)(b))) << 8))

#घोषणा GPIO_HIGH 1
#घोषणा GPIO_LOW  0

/* the Power-On-Reset logic, requires to attempt
 * to करोwnload firmware onto chip more than once
 * since the self-test क्रम chip takes a जबतक
 */
#घोषणा POR_RETRY_COUNT 5

/**
 * काष्ठा chip_version - save the chip version
 */
काष्ठा chip_version अणु
	अचिन्हित लघु full;
	अचिन्हित लघु chip;
	अचिन्हित लघु min_ver;
	अचिन्हित लघु maj_ver;
पूर्ण;

#घोषणा UART_DEV_NAME_LEN 32
/**
 * काष्ठा kim_data_s - the KIM पूर्णांकernal data, embedded as the
 *	platक्रमm's drv data. One क्रम each ST device in the प्रणाली.
 * @uim_pid: KIM needs to communicate with UIM to request to install
 *	the ldisc by खोलोing UART when protocol drivers रेजिस्टर.
 * @kim_pdev: the platक्रमm device added in one of the board-XX.c file
 *	in arch/XX/ directory, 1 क्रम each ST device.
 * @kim_rcvd: completion handler to notअगरy when data was received,
 *	मुख्यly used during fw करोwnload, which involves multiple send/रुको
 *	क्रम each of the HCI-VS commands.
 * @ldisc_installed: completion handler to notअगरy that the UIM accepted
 *	the request to install ldisc, notअगरy from tty_खोलो which suggests
 *	the ldisc was properly installed.
 * @resp_buffer: data buffer क्रम the .bts fw file name.
 * @fw_entry: firmware class काष्ठा to request/release the fw.
 * @rx_state: the rx state क्रम kim's receive func during fw करोwnload.
 * @rx_count: the rx count क्रम the kim's receive func during fw करोwnload.
 * @rx_skb: all of fw data might not come at once, and hence data storage क्रम
 *	whole of the fw response, only HCI_EVENTs and hence dअगरf from ST's
 *	response.
 * @core_data: ST core's data, which mainly is the tty's disc_data
 * @version: chip version available via a sysfs entry.
 *
 */
काष्ठा kim_data_s अणु
	दीर्घ uim_pid;
	काष्ठा platक्रमm_device *kim_pdev;
	काष्ठा completion kim_rcvd, ldisc_installed;
	अक्षर resp_buffer[30];
	स्थिर काष्ठा firmware *fw_entry;
	अचिन्हित nshutकरोwn;
	अचिन्हित दीर्घ rx_state;
	अचिन्हित दीर्घ rx_count;
	काष्ठा sk_buff *rx_skb;
	काष्ठा st_data_s *core_data;
	काष्ठा chip_version version;
	अचिन्हित अक्षर ldisc_install;
	अचिन्हित अक्षर dev_name[UART_DEV_NAME_LEN + 1];
	अचिन्हित flow_cntrl;
	अचिन्हित baud_rate;
पूर्ण;

/**
 * functions called when 1 of the protocol drivers माला_लो
 * रेजिस्टरed, these need to communicate with UIM to request
 * ldisc installed, पढ़ो chip_version, करोwnload relevant fw
 */
दीर्घ st_kim_start(व्योम *);
दीर्घ st_kim_stop(व्योम *);

व्योम st_kim_complete(व्योम *);
व्योम kim_st_list_protocols(काष्ठा st_data_s *, व्योम *);
व्योम st_kim_recv(व्योम *, स्थिर अचिन्हित अक्षर *, दीर्घ);


/*
 * BTS headers
 */
#घोषणा ACTION_SEND_COMMAND     1
#घोषणा ACTION_WAIT_EVENT       2
#घोषणा ACTION_SERIAL           3
#घोषणा ACTION_DELAY            4
#घोषणा ACTION_RUN_SCRIPT       5
#घोषणा ACTION_REMARKS          6

/**
 * काष्ठा bts_header - the fw file is NOT binary which can
 *	be sent onto TTY as is. The .bts is more a script
 *	file which has dअगरferent types of actions.
 *	Each such action needs to be parsed by the KIM and
 *	relevant procedure to be called.
 */
काष्ठा bts_header अणु
	u32 magic;
	u32 version;
	u8 future[24];
	u8 actions[];
पूर्ण __attribute__ ((packed));

/**
 * काष्ठा bts_action - Each .bts action has its own type of
 *	data.
 */
काष्ठा bts_action अणु
	u16 type;
	u16 size;
	u8 data[];
पूर्ण __attribute__ ((packed));

काष्ठा bts_action_send अणु
	u8 data[0];
पूर्ण __attribute__ ((packed));

काष्ठा bts_action_रुको अणु
	u32 msec;
	u32 size;
	u8 data[];
पूर्ण __attribute__ ((packed));

काष्ठा bts_action_delay अणु
	u32 msec;
पूर्ण __attribute__ ((packed));

काष्ठा bts_action_serial अणु
	u32 baud;
	u32 flow_control;
पूर्ण __attribute__ ((packed));

/**
 * काष्ठा hci_command - the HCI-VS क्रम पूर्णांकrepreting
 *	the change baud rate of host-side UART, which
 *	needs to be ignored, since UIM would करो that
 *	when it receives request from KIM क्रम ldisc installation.
 */
काष्ठा hci_command अणु
	u8 prefix;
	u16 opcode;
	u8 plen;
	u32 speed;
पूर्ण __attribute__ ((packed));

/*
 * header inक्रमmation used by st_ll.c
 */

/* ST LL receiver states */
#घोषणा ST_W4_PACKET_TYPE       0
#घोषणा ST_W4_HEADER		1
#घोषणा ST_W4_DATA		2

/* ST LL state machines */
#घोषणा ST_LL_ASLEEP               0
#घोषणा ST_LL_ASLEEP_TO_AWAKE      1
#घोषणा ST_LL_AWAKE                2
#घोषणा ST_LL_AWAKE_TO_ASLEEP      3
#घोषणा ST_LL_INVALID		   4

/* dअगरferent PM notअगरications coming from chip */
#घोषणा LL_SLEEP_IND	0x30
#घोषणा LL_SLEEP_ACK	0x31
#घोषणा LL_WAKE_UP_IND	0x32
#घोषणा LL_WAKE_UP_ACK	0x33

/* initialize and de-init ST LL */
दीर्घ st_ll_init(काष्ठा st_data_s *);
दीर्घ st_ll_deinit(काष्ठा st_data_s *);

/**
 * enable/disable ST LL aदीर्घ with KIM start/stop
 * called by ST Core
 */
व्योम st_ll_enable(काष्ठा st_data_s *);
व्योम st_ll_disable(काष्ठा st_data_s *);

/**
 * various funcs used by ST core to set/get the various PM states
 * of the chip.
 */
अचिन्हित दीर्घ st_ll_माला_लोtate(काष्ठा st_data_s *);
अचिन्हित दीर्घ st_ll_sleep_state(काष्ठा st_data_s *, अचिन्हित अक्षर);
व्योम st_ll_wakeup(काष्ठा st_data_s *);

/*
 * header inक्रमmation used by st_core.c क्रम FM and GPS
 * packet parsing, the bluetooth headers are alपढ़ोy available
 * at net/bluetooth/
 */

काष्ठा fm_event_hdr अणु
	u8 plen;
पूर्ण __attribute__ ((packed));

#घोषणा FM_MAX_FRAME_SIZE 0xFF	/* TODO: */
#घोषणा FM_EVENT_HDR_SIZE 1	/* size of fm_event_hdr */
#घोषणा ST_FM_CH8_PKT 0x8

/* gps stuff */
काष्ठा gps_event_hdr अणु
	u8 opcode;
	u16 plen;
पूर्ण __attribute__ ((packed));

/**
 * काष्ठा ti_st_plat_data - platक्रमm data shared between ST driver and
 *	platक्रमm specअगरic board file which adds the ST device.
 * @nshutकरोwn_gpio: Host's GPIO line to which chip's BT_EN is connected.
 * @dev_name: The UART/TTY name to which chip is पूर्णांकerfaced. (eg: /dev/ttyS1)
 * @flow_cntrl: Should always be 1, since UART's CTS/RTS is used क्रम PM
 *	purposes.
 * @baud_rate: The baud rate supported by the Host UART controller, this will
 *	be shared across with the chip via a HCI VS command from User-Space Init
 *	Mgr application.
 * @suspend:
 * @resume: legacy PM routines hooked to platक्रमm specअगरic board file, so as
 *	to take chip-host पूर्णांकerface specअगरic action.
 * @chip_enable:
 * @chip_disable: Platक्रमm/Interface specअगरic mux mode setting, GPIO
 *	configuring, Host side PM disabling etc.. can be करोne here.
 * @chip_asleep:
 * @chip_awake: Chip specअगरic deep sleep states is communicated to Host
 *	specअगरic board-xx.c to take actions such as cut UART घड़ीs when chip
 *	asleep or run host faster when chip awake etc..
 *
 */
काष्ठा ti_st_plat_data अणु
	u32 nshutकरोwn_gpio;
	अचिन्हित अक्षर dev_name[UART_DEV_NAME_LEN]; /* uart name */
	u32 flow_cntrl; /* flow control flag */
	u32 baud_rate;
	पूर्णांक (*suspend)(काष्ठा platक्रमm_device *, pm_message_t);
	पूर्णांक (*resume)(काष्ठा platक्रमm_device *);
	पूर्णांक (*chip_enable) (काष्ठा kim_data_s *);
	पूर्णांक (*chip_disable) (काष्ठा kim_data_s *);
	पूर्णांक (*chip_asleep) (काष्ठा kim_data_s *);
	पूर्णांक (*chip_awake) (काष्ठा kim_data_s *);
पूर्ण;

#पूर्ण_अगर /* TI_WILINK_ST_H */
