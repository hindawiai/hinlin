<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Header file क्रम the compaq Micro MFD
 */

#अगर_अघोषित _MFD_IPAQ_MICRO_H_
#घोषणा _MFD_IPAQ_MICRO_H_

#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/list.h>

#घोषणा TX_BUF_SIZE	32
#घोषणा RX_BUF_SIZE	16
#घोषणा CHAR_SOF	0x02

/*
 * These are the dअगरferent messages that can be sent to the microcontroller
 * to control various aspects.
 */
#घोषणा MSG_VERSION		0x0
#घोषणा MSG_KEYBOARD		0x2
#घोषणा MSG_TOUCHSCREEN		0x3
#घोषणा MSG_EEPROM_READ		0x4
#घोषणा MSG_EEPROM_WRITE	0x5
#घोषणा MSG_THERMAL_SENSOR	0x6
#घोषणा MSG_NOTIFY_LED		0x8
#घोषणा MSG_BATTERY		0x9
#घोषणा MSG_SPI_READ		0xb
#घोषणा MSG_SPI_WRITE		0xc
#घोषणा MSG_BACKLIGHT		0xd /* H3600 only */
#घोषणा MSG_CODEC_CTRL		0xe /* H3100 only */
#घोषणा MSG_DISPLAY_CTRL	0xf /* H3100 only */

/* state of receiver parser */
क्रमागत rx_state अणु
	STATE_SOF = 0,     /* Next byte should be start of frame */
	STATE_ID,          /* Next byte is ID & message length   */
	STATE_DATA,        /* Next byte is a data byte           */
	STATE_CHKSUM       /* Next byte should be checksum       */
पूर्ण;

/**
 * काष्ठा ipaq_micro_txdev - TX state
 * @len: length of message in TX buffer
 * @index: current index पूर्णांकo TX buffer
 * @buf: TX buffer
 */
काष्ठा ipaq_micro_txdev अणु
	u8 len;
	u8 index;
	u8 buf[TX_BUF_SIZE];
पूर्ण;

/**
 * काष्ठा ipaq_micro_rxdev - RX state
 * @state: context of RX state machine
 * @chksum: calculated checksum
 * @id: message ID from packet
 * @len: RX buffer length
 * @index: RX buffer index
 * @buf: RX buffer
 */
काष्ठा ipaq_micro_rxdev अणु
	क्रमागत rx_state state;
	अचिन्हित अक्षर chksum;
	u8            id;
	अचिन्हित पूर्णांक  len;
	अचिन्हित पूर्णांक  index;
	u8            buf[RX_BUF_SIZE];
पूर्ण;

/**
 * काष्ठा ipaq_micro_msg - message to the iPAQ microcontroller
 * @id: 4-bit ID of the message
 * @tx_len: length of TX data
 * @tx_data: TX data to send
 * @rx_len: length of receieved RX data
 * @rx_data: RX data to recieve
 * @ack: a completion that will be completed when RX is complete
 * @node: list node अगर message माला_लो queued
 */
काष्ठा ipaq_micro_msg अणु
	u8 id;
	u8 tx_len;
	u8 tx_data[TX_BUF_SIZE];
	u8 rx_len;
	u8 rx_data[RX_BUF_SIZE];
	काष्ठा completion ack;
	काष्ठा list_head node;
पूर्ण;

/**
 * काष्ठा ipaq_micro - iPAQ microcontroller state
 * @dev: corresponding platक्रमm device
 * @base: भव memory base क्रम underlying serial device
 * @sdlc: भव memory base क्रम Synchronous Data Link Controller
 * @version: version string
 * @tx: TX state
 * @rx: RX state
 * @lock: lock क्रम this state container
 * @msg: current message
 * @queue: message queue
 * @key: callback क्रम asynchronous key events
 * @key_data: data to pass aदीर्घ with key events
 * @ts: callback क्रम asynchronous touchscreen events
 * @ts_data: data to pass aदीर्घ with key events
 */
काष्ठा ipaq_micro अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	व्योम __iomem *sdlc;
	अक्षर version[5];
	काष्ठा ipaq_micro_txdev tx;	/* transmit ISR state */
	काष्ठा ipaq_micro_rxdev rx;	/* receive ISR state */
	spinlock_t lock;
	काष्ठा ipaq_micro_msg *msg;
	काष्ठा list_head queue;
	व्योम (*key) (व्योम *data, पूर्णांक len, अचिन्हित अक्षर *rxdata);
	व्योम *key_data;
	व्योम (*ts) (व्योम *data, पूर्णांक len, अचिन्हित अक्षर *rxdata);
	व्योम *ts_data;
पूर्ण;

बाह्य पूर्णांक
ipaq_micro_tx_msg(काष्ठा ipaq_micro *micro, काष्ठा ipaq_micro_msg *msg);

अटल अंतरभूत पूर्णांक
ipaq_micro_tx_msg_sync(काष्ठा ipaq_micro *micro,
		       काष्ठा ipaq_micro_msg *msg)
अणु
	पूर्णांक ret;

	init_completion(&msg->ack);
	ret = ipaq_micro_tx_msg(micro, msg);
	रुको_क्रम_completion(&msg->ack);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
ipaq_micro_tx_msg_async(काष्ठा ipaq_micro *micro,
			काष्ठा ipaq_micro_msg *msg)
अणु
	init_completion(&msg->ack);
	वापस ipaq_micro_tx_msg(micro, msg);
पूर्ण

#पूर्ण_अगर /* _MFD_IPAQ_MICRO_H_ */
