<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *
 *  Bluetooth HCI UART driver
 *
 *  Copyright (C) 2000-2001  Qualcomm Incorporated
 *  Copyright (C) 2002-2003  Maxim Krasnyansky <maxk@qualcomm.com>
 *  Copyright (C) 2004-2005  Marcel Holपंचांगann <marcel@holपंचांगann.org>
 */

#अगर_अघोषित N_HCI
#घोषणा N_HCI	15
#पूर्ण_अगर

/* Ioctls */
#घोषणा HCIUARTSETPROTO		_IOW('U', 200, पूर्णांक)
#घोषणा HCIUARTGETPROTO		_IOR('U', 201, पूर्णांक)
#घोषणा HCIUARTGETDEVICE	_IOR('U', 202, पूर्णांक)
#घोषणा HCIUARTSETFLAGS		_IOW('U', 203, पूर्णांक)
#घोषणा HCIUARTGETFLAGS		_IOR('U', 204, पूर्णांक)

/* UART protocols */
#घोषणा HCI_UART_MAX_PROTO	12

#घोषणा HCI_UART_H4	0
#घोषणा HCI_UART_BCSP	1
#घोषणा HCI_UART_3WIRE	2
#घोषणा HCI_UART_H4DS	3
#घोषणा HCI_UART_LL	4
#घोषणा HCI_UART_ATH3K	5
#घोषणा HCI_UART_INTEL	6
#घोषणा HCI_UART_BCM	7
#घोषणा HCI_UART_QCA	8
#घोषणा HCI_UART_AG6XX	9
#घोषणा HCI_UART_NOKIA	10
#घोषणा HCI_UART_MRVL	11

#घोषणा HCI_UART_RAW_DEVICE	0
#घोषणा HCI_UART_RESET_ON_INIT	1
#घोषणा HCI_UART_CREATE_AMP	2
#घोषणा HCI_UART_INIT_PENDING	3
#घोषणा HCI_UART_EXT_CONFIG	4
#घोषणा HCI_UART_VND_DETECT	5

काष्ठा hci_uart;
काष्ठा serdev_device;

काष्ठा hci_uart_proto अणु
	अचिन्हित पूर्णांक id;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक manufacturer;
	अचिन्हित पूर्णांक init_speed;
	अचिन्हित पूर्णांक oper_speed;
	पूर्णांक (*खोलो)(काष्ठा hci_uart *hu);
	पूर्णांक (*बंद)(काष्ठा hci_uart *hu);
	पूर्णांक (*flush)(काष्ठा hci_uart *hu);
	पूर्णांक (*setup)(काष्ठा hci_uart *hu);
	पूर्णांक (*set_baudrate)(काष्ठा hci_uart *hu, अचिन्हित पूर्णांक speed);
	पूर्णांक (*recv)(काष्ठा hci_uart *hu, स्थिर व्योम *data, पूर्णांक len);
	पूर्णांक (*enqueue)(काष्ठा hci_uart *hu, काष्ठा sk_buff *skb);
	काष्ठा sk_buff *(*dequeue)(काष्ठा hci_uart *hu);
पूर्ण;

काष्ठा hci_uart अणु
	काष्ठा tty_काष्ठा	*tty;
	काष्ठा serdev_device	*serdev;
	काष्ठा hci_dev		*hdev;
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		hdev_flags;

	काष्ठा work_काष्ठा	init_पढ़ोy;
	काष्ठा work_काष्ठा	ग_लिखो_work;

	स्थिर काष्ठा hci_uart_proto *proto;
	काष्ठा percpu_rw_semaphore proto_lock;	/* Stop work क्रम proto बंद */
	व्योम			*priv;

	काष्ठा sk_buff		*tx_skb;
	अचिन्हित दीर्घ		tx_state;

	अचिन्हित पूर्णांक init_speed;
	अचिन्हित पूर्णांक oper_speed;

	u8			alignment;
	u8			padding;
पूर्ण;

/* HCI_UART proto flag bits */
#घोषणा HCI_UART_PROTO_SET	0
#घोषणा HCI_UART_REGISTERED	1
#घोषणा HCI_UART_PROTO_READY	2

/* TX states  */
#घोषणा HCI_UART_SENDING	1
#घोषणा HCI_UART_TX_WAKEUP	2

पूर्णांक hci_uart_रेजिस्टर_proto(स्थिर काष्ठा hci_uart_proto *p);
पूर्णांक hci_uart_unरेजिस्टर_proto(स्थिर काष्ठा hci_uart_proto *p);
पूर्णांक hci_uart_रेजिस्टर_device(काष्ठा hci_uart *hu, स्थिर काष्ठा hci_uart_proto *p);
व्योम hci_uart_unरेजिस्टर_device(काष्ठा hci_uart *hu);

पूर्णांक hci_uart_tx_wakeup(काष्ठा hci_uart *hu);
पूर्णांक hci_uart_रुको_until_sent(काष्ठा hci_uart *hu);
पूर्णांक hci_uart_init_पढ़ोy(काष्ठा hci_uart *hu);
व्योम hci_uart_init_work(काष्ठा work_काष्ठा *work);
व्योम hci_uart_set_baudrate(काष्ठा hci_uart *hu, अचिन्हित पूर्णांक speed);
bool hci_uart_has_flow_control(काष्ठा hci_uart *hu);
व्योम hci_uart_set_flow_control(काष्ठा hci_uart *hu, bool enable);
व्योम hci_uart_set_speeds(काष्ठा hci_uart *hu, अचिन्हित पूर्णांक init_speed,
			 अचिन्हित पूर्णांक oper_speed);

#अगर_घोषित CONFIG_BT_HCIUART_H4
पूर्णांक h4_init(व्योम);
पूर्णांक h4_deinit(व्योम);

काष्ठा h4_recv_pkt अणु
	u8  type;	/* Packet type */
	u8  hlen;	/* Header length */
	u8  loff;	/* Data length offset in header */
	u8  lsize;	/* Data length field size */
	u16 maxlen;	/* Max overall packet length */
	पूर्णांक (*recv)(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb);
पूर्ण;

#घोषणा H4_RECV_ACL \
	.type = HCI_ACLDATA_PKT, \
	.hlen = HCI_ACL_HDR_SIZE, \
	.loff = 2, \
	.lsize = 2, \
	.maxlen = HCI_MAX_FRAME_SIZE \

#घोषणा H4_RECV_SCO \
	.type = HCI_SCODATA_PKT, \
	.hlen = HCI_SCO_HDR_SIZE, \
	.loff = 2, \
	.lsize = 1, \
	.maxlen = HCI_MAX_SCO_SIZE

#घोषणा H4_RECV_EVENT \
	.type = HCI_EVENT_PKT, \
	.hlen = HCI_EVENT_HDR_SIZE, \
	.loff = 1, \
	.lsize = 1, \
	.maxlen = HCI_MAX_EVENT_SIZE

#घोषणा H4_RECV_ISO \
	.type = HCI_ISODATA_PKT, \
	.hlen = HCI_ISO_HDR_SIZE, \
	.loff = 2, \
	.lsize = 2, \
	.maxlen = HCI_MAX_FRAME_SIZE \

काष्ठा sk_buff *h4_recv_buf(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb,
			    स्थिर अचिन्हित अक्षर *buffer, पूर्णांक count,
			    स्थिर काष्ठा h4_recv_pkt *pkts, पूर्णांक pkts_count);
#पूर्ण_अगर

#अगर_घोषित CONFIG_BT_HCIUART_BCSP
पूर्णांक bcsp_init(व्योम);
पूर्णांक bcsp_deinit(व्योम);
#पूर्ण_अगर

#अगर_घोषित CONFIG_BT_HCIUART_LL
पूर्णांक ll_init(व्योम);
पूर्णांक ll_deinit(व्योम);
#पूर्ण_अगर

#अगर_घोषित CONFIG_BT_HCIUART_ATH3K
पूर्णांक ath_init(व्योम);
पूर्णांक ath_deinit(व्योम);
#पूर्ण_अगर

#अगर_घोषित CONFIG_BT_HCIUART_3WIRE
पूर्णांक h5_init(व्योम);
पूर्णांक h5_deinit(व्योम);
#पूर्ण_अगर

#अगर_घोषित CONFIG_BT_HCIUART_INTEL
पूर्णांक पूर्णांकel_init(व्योम);
पूर्णांक पूर्णांकel_deinit(व्योम);
#पूर्ण_अगर

#अगर_घोषित CONFIG_BT_HCIUART_BCM
पूर्णांक bcm_init(व्योम);
पूर्णांक bcm_deinit(व्योम);
#पूर्ण_अगर

#अगर_घोषित CONFIG_BT_HCIUART_QCA
पूर्णांक qca_init(व्योम);
पूर्णांक qca_deinit(व्योम);
#पूर्ण_अगर

#अगर_घोषित CONFIG_BT_HCIUART_AG6XX
पूर्णांक ag6xx_init(व्योम);
पूर्णांक ag6xx_deinit(व्योम);
#पूर्ण_अगर

#अगर_घोषित CONFIG_BT_HCIUART_MRVL
पूर्णांक mrvl_init(व्योम);
पूर्णांक mrvl_deinit(व्योम);
#पूर्ण_अगर
