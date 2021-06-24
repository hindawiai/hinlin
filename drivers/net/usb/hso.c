<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Driver क्रम Option High Speed Mobile Devices.
 *
 *  Copyright (C) 2008 Option International
 *                     Filip Aben <f.aben@option.com>
 *                     Denis Joseph Barrow <d.barow@option.com>
 *                     Jan Dumon <j.dumon@option.com>
 *  Copyright (C) 2007 Andrew Bird (Sphere Systems Ltd)
 *  			<ajb@sphereप्रणालीs.co.uk>
 *  Copyright (C) 2008 Greg Kroah-Harपंचांगan <gregkh@suse.de>
 *  Copyright (C) 2008 Novell, Inc.
 *
 *****************************************************************************/

/******************************************************************************
 *
 * Description of the device:
 *
 * Interface 0:	Contains the IP network पूर्णांकerface on the bulk end poपूर्णांकs.
 *		The multiplexed serial ports are using the पूर्णांकerrupt and
 *		control endpoपूर्णांकs.
 *		Interrupt contains a biपंचांगap telling which multiplexed
 *		serialport needs servicing.
 *
 * Interface 1:	Diagnostics port, uses bulk only, करो not submit urbs until the
 *		port is खोलोed, as this have a huge impact on the network port
 *		throughput.
 *
 * Interface 2:	Standard modem पूर्णांकerface - circuit चयनed पूर्णांकerface, this
 *		can be used to make a standard ppp connection however it
 *              should not be used in conjunction with the IP network पूर्णांकerface
 *              enabled क्रम USB perक्रमmance reasons i.e. अगर using this set
 *              ideally disable_net=1.
 *
 *****************************************************************************/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/usb.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/kmod.h>
#समावेश <linux/rfसमाप्त.h>
#समावेश <linux/ip.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb/cdc.h>
#समावेश <net/arp.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial.h>


#घोषणा MOD_AUTHOR			"Option Wireless"
#घोषणा MOD_DESCRIPTION			"USB High Speed Option driver"

#घोषणा HSO_MAX_NET_DEVICES		10
#घोषणा HSO__MAX_MTU			2048
#घोषणा DEFAULT_MTU			1500
#घोषणा DEFAULT_MRU			1500

#घोषणा CTRL_URB_RX_SIZE		1024
#घोषणा CTRL_URB_TX_SIZE		64

#घोषणा BULK_URB_RX_SIZE		4096
#घोषणा BULK_URB_TX_SIZE		8192

#घोषणा MUX_BULK_RX_BUF_SIZE		HSO__MAX_MTU
#घोषणा MUX_BULK_TX_BUF_SIZE		HSO__MAX_MTU
#घोषणा MUX_BULK_RX_BUF_COUNT		4
#घोषणा USB_TYPE_OPTION_VENDOR		0x20

/* These definitions are used with the काष्ठा hso_net flags element */
/* - use *_bit operations on it. (bit indices not values.) */
#घोषणा HSO_NET_RUNNING			0

#घोषणा	HSO_NET_TX_TIMEOUT		(HZ*10)

#घोषणा HSO_SERIAL_MAGIC		0x48534f31

/* Number of ttys to handle */
#घोषणा HSO_SERIAL_TTY_MINORS		256

#घोषणा MAX_RX_URBS			2

/*****************************************************************************/
/* Debugging functions                                                       */
/*****************************************************************************/
#घोषणा hso_dbg(lvl, fmt, ...)						\
करो अणु									\
	अगर ((lvl) & debug)						\
		pr_info("[%d:%s] " fmt,					\
			__LINE__, __func__, ##__VA_ARGS__);		\
पूर्ण जबतक (0)

/*****************************************************************************/
/* Enumerators                                                               */
/*****************************************************************************/
क्रमागत pkt_parse_state अणु
	WAIT_IP,
	WAIT_DATA,
	WAIT_SYNC
पूर्ण;

/*****************************************************************************/
/* Structs                                                                   */
/*****************************************************************************/

काष्ठा hso_shared_पूर्णांक अणु
	काष्ठा usb_endpoपूर्णांक_descriptor *पूर्णांकr_endp;
	व्योम *shared_पूर्णांकr_buf;
	काष्ठा urb *shared_पूर्णांकr_urb;
	काष्ठा usb_device *usb;
	पूर्णांक use_count;
	पूर्णांक ref_count;
	काष्ठा mutex shared_पूर्णांक_lock;
पूर्ण;

काष्ठा hso_net अणु
	काष्ठा hso_device *parent;
	काष्ठा net_device *net;
	काष्ठा rfसमाप्त *rfसमाप्त;
	अक्षर name[24];

	काष्ठा usb_endpoपूर्णांक_descriptor *in_endp;
	काष्ठा usb_endpoपूर्णांक_descriptor *out_endp;

	काष्ठा urb *mux_bulk_rx_urb_pool[MUX_BULK_RX_BUF_COUNT];
	काष्ठा urb *mux_bulk_tx_urb;
	व्योम *mux_bulk_rx_buf_pool[MUX_BULK_RX_BUF_COUNT];
	व्योम *mux_bulk_tx_buf;

	काष्ठा sk_buff *skb_rx_buf;
	काष्ठा sk_buff *skb_tx_buf;

	क्रमागत pkt_parse_state rx_parse_state;
	spinlock_t net_lock;

	अचिन्हित लघु rx_buf_size;
	अचिन्हित लघु rx_buf_missing;
	काष्ठा iphdr rx_ip_hdr;

	अचिन्हित दीर्घ flags;
पूर्ण;

क्रमागत rx_ctrl_stateअणु
	RX_IDLE,
	RX_SENT,
	RX_PENDING
पूर्ण;

#घोषणा BM_REQUEST_TYPE (0xa1)
#घोषणा B_NOTIFICATION  (0x20)
#घोषणा W_VALUE         (0x0)
#घोषणा W_LENGTH        (0x2)

#घोषणा B_OVERRUN       (0x1<<6)
#घोषणा B_PARITY        (0x1<<5)
#घोषणा B_FRAMING       (0x1<<4)
#घोषणा B_RING_SIGNAL   (0x1<<3)
#घोषणा B_BREAK         (0x1<<2)
#घोषणा B_TX_CARRIER    (0x1<<1)
#घोषणा B_RX_CARRIER    (0x1<<0)

काष्ठा hso_serial_state_notअगरication अणु
	u8 bmRequestType;
	u8 bNotअगरication;
	u16 wValue;
	u16 wIndex;
	u16 wLength;
	u16 UART_state_biपंचांगap;
पूर्ण __packed;

काष्ठा hso_tiocmget अणु
	काष्ठा mutex mutex;
	रुको_queue_head_t रुकोq;
	पूर्णांक    पूर्णांकr_completed;
	काष्ठा usb_endpoपूर्णांक_descriptor *endp;
	काष्ठा urb *urb;
	काष्ठा hso_serial_state_notअगरication *serial_state_notअगरication;
	u16    prev_UART_state_biपंचांगap;
	काष्ठा uart_icount icount;
पूर्ण;


काष्ठा hso_serial अणु
	काष्ठा hso_device *parent;
	पूर्णांक magic;
	u8 minor;

	काष्ठा hso_shared_पूर्णांक *shared_पूर्णांक;

	/* rx/tx urb could be either a bulk urb or a control urb depending
	   on which serial port it is used on. */
	काष्ठा urb *rx_urb[MAX_RX_URBS];
	u8 num_rx_urbs;
	u8 *rx_data[MAX_RX_URBS];
	u16 rx_data_length;	/* should contain allocated length */

	काष्ठा urb *tx_urb;
	u8 *tx_data;
	u8 *tx_buffer;
	u16 tx_data_length;	/* should contain allocated length */
	u16 tx_data_count;
	u16 tx_buffer_count;
	काष्ठा usb_ctrlrequest ctrl_req_tx;
	काष्ठा usb_ctrlrequest ctrl_req_rx;

	काष्ठा usb_endpoपूर्णांक_descriptor *in_endp;
	काष्ठा usb_endpoपूर्णांक_descriptor *out_endp;

	क्रमागत rx_ctrl_state rx_state;
	u8 rts_state;
	u8 dtr_state;
	अचिन्हित tx_urb_used:1;

	काष्ठा tty_port port;
	/* from usb_serial_port */
	spinlock_t serial_lock;

	पूर्णांक (*ग_लिखो_data) (काष्ठा hso_serial *serial);
	काष्ठा hso_tiocmget  *tiocmget;
	/* Hacks required to get flow control
	 * working on the serial receive buffers
	 * so as not to drop अक्षरacters on the न्यूनमान.
	 */
	पूर्णांक  curr_rx_urb_idx;
	u8   rx_urb_filled[MAX_RX_URBS];
	काष्ठा tasklet_काष्ठा unthrottle_tasklet;
पूर्ण;

काष्ठा hso_device अणु
	जोड़ अणु
		काष्ठा hso_serial *dev_serial;
		काष्ठा hso_net *dev_net;
	पूर्ण port_data;

	u32 port_spec;

	u8 is_active;
	u8 usb_gone;
	काष्ठा work_काष्ठा async_get_पूर्णांकf;
	काष्ठा work_काष्ठा async_put_पूर्णांकf;

	काष्ठा usb_device *usb;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;

	काष्ठा device *dev;
	काष्ठा kref ref;
	काष्ठा mutex mutex;
पूर्ण;

/* Type of पूर्णांकerface */
#घोषणा HSO_INTF_MASK		0xFF00
#घोषणा	HSO_INTF_MUX		0x0100
#घोषणा	HSO_INTF_BULK   	0x0200

/* Type of port */
#घोषणा HSO_PORT_MASK		0xFF
#घोषणा HSO_PORT_NO_PORT	0x0
#घोषणा	HSO_PORT_CONTROL	0x1
#घोषणा	HSO_PORT_APP		0x2
#घोषणा	HSO_PORT_GPS		0x3
#घोषणा	HSO_PORT_PCSC		0x4
#घोषणा	HSO_PORT_APP2		0x5
#घोषणा HSO_PORT_GPS_CONTROL	0x6
#घोषणा HSO_PORT_MSD		0x7
#घोषणा HSO_PORT_VOICE		0x8
#घोषणा HSO_PORT_DIAG2		0x9
#घोषणा	HSO_PORT_DIAG		0x10
#घोषणा	HSO_PORT_MODEM		0x11
#घोषणा	HSO_PORT_NETWORK	0x12

/* Additional device info */
#घोषणा HSO_INFO_MASK		0xFF000000
#घोषणा HSO_INFO_CRC_BUG	0x01000000

/*****************************************************************************/
/* Prototypes                                                                */
/*****************************************************************************/
/* Serial driver functions */
अटल पूर्णांक hso_serial_tiocmset(काष्ठा tty_काष्ठा *tty,
			       अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear);
अटल व्योम ctrl_callback(काष्ठा urb *urb);
अटल पूर्णांक put_rxbuf_data(काष्ठा urb *urb, काष्ठा hso_serial *serial);
अटल व्योम hso_kick_transmit(काष्ठा hso_serial *serial);
/* Helper functions */
अटल पूर्णांक hso_mux_submit_पूर्णांकr_urb(काष्ठा hso_shared_पूर्णांक *mux_पूर्णांक,
				   काष्ठा usb_device *usb, gfp_t gfp);
अटल व्योम handle_usb_error(पूर्णांक status, स्थिर अक्षर *function,
			     काष्ठा hso_device *hso_dev);
अटल काष्ठा usb_endpoपूर्णांक_descriptor *hso_get_ep(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
						  पूर्णांक type, पूर्णांक dir);
अटल पूर्णांक hso_get_mux_ports(काष्ठा usb_पूर्णांकerface *पूर्णांकf, अचिन्हित अक्षर *ports);
अटल व्योम hso_मुक्त_पूर्णांकerface(काष्ठा usb_पूर्णांकerface *पूर्णांकf);
अटल पूर्णांक hso_start_serial_device(काष्ठा hso_device *hso_dev, gfp_t flags);
अटल पूर्णांक hso_stop_serial_device(काष्ठा hso_device *hso_dev);
अटल पूर्णांक hso_start_net_device(काष्ठा hso_device *hso_dev);
अटल व्योम hso_मुक्त_shared_पूर्णांक(काष्ठा hso_shared_पूर्णांक *shared_पूर्णांक);
अटल पूर्णांक hso_stop_net_device(काष्ठा hso_device *hso_dev);
अटल व्योम hso_serial_ref_मुक्त(काष्ठा kref *ref);
अटल व्योम hso_std_serial_पढ़ो_bulk_callback(काष्ठा urb *urb);
अटल पूर्णांक hso_mux_serial_पढ़ो(काष्ठा hso_serial *serial);
अटल व्योम async_get_पूर्णांकf(काष्ठा work_काष्ठा *data);
अटल व्योम async_put_पूर्णांकf(काष्ठा work_काष्ठा *data);
अटल पूर्णांक hso_put_activity(काष्ठा hso_device *hso_dev);
अटल पूर्णांक hso_get_activity(काष्ठा hso_device *hso_dev);
अटल व्योम tiocmget_पूर्णांकr_callback(काष्ठा urb *urb);
/*****************************************************************************/
/* Helping functions                                                         */
/*****************************************************************************/

/* #घोषणा DEBUG */

अटल अंतरभूत काष्ठा hso_net *dev2net(काष्ठा hso_device *hso_dev)
अणु
	वापस hso_dev->port_data.dev_net;
पूर्ण

अटल अंतरभूत काष्ठा hso_serial *dev2ser(काष्ठा hso_device *hso_dev)
अणु
	वापस hso_dev->port_data.dev_serial;
पूर्ण

/* Debugging functions */
#अगर_घोषित DEBUG
अटल व्योम dbg_dump(पूर्णांक line_count, स्थिर अक्षर *func_name, अचिन्हित अक्षर *buf,
		     अचिन्हित पूर्णांक len)
अणु
	अटल अक्षर name[255];

	प्र_लिखो(name, "hso[%d:%s]", line_count, func_name);
	prपूर्णांक_hex_dump_bytes(name, DUMP_PREFIX_NONE, buf, len);
पूर्ण

#घोषणा DUMP(buf_, len_)	\
	dbg_dump(__LINE__, __func__, (अचिन्हित अक्षर *)buf_, len_)

#घोषणा DUMP1(buf_, len_)			\
	करो अणु					\
		अगर (0x01 & debug)		\
			DUMP(buf_, len_);	\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा DUMP(buf_, len_)
#घोषणा DUMP1(buf_, len_)
#पूर्ण_अगर

/* module parameters */
अटल पूर्णांक debug;
अटल पूर्णांक tty_major;
अटल पूर्णांक disable_net;

/* driver info */
अटल स्थिर अक्षर driver_name[] = "hso";
अटल स्थिर अक्षर tty_filename[] = "ttyHS";
अटल स्थिर अक्षर *version = __खाता__ ": " MOD_AUTHOR;
/* the usb driver itself (रेजिस्टरed in hso_init) */
अटल काष्ठा usb_driver hso_driver;
/* serial काष्ठाures */
अटल काष्ठा tty_driver *tty_drv;
अटल काष्ठा hso_device *serial_table[HSO_SERIAL_TTY_MINORS];
अटल काष्ठा hso_device *network_table[HSO_MAX_NET_DEVICES];
अटल DEFINE_SPINLOCK(serial_table_lock);

अटल स्थिर s32 शेष_port_spec[] = अणु
	HSO_INTF_MUX | HSO_PORT_NETWORK,
	HSO_INTF_BULK | HSO_PORT_DIAG,
	HSO_INTF_BULK | HSO_PORT_MODEM,
	0
पूर्ण;

अटल स्थिर s32 icon321_port_spec[] = अणु
	HSO_INTF_MUX | HSO_PORT_NETWORK,
	HSO_INTF_BULK | HSO_PORT_DIAG2,
	HSO_INTF_BULK | HSO_PORT_MODEM,
	HSO_INTF_BULK | HSO_PORT_DIAG,
	0
पूर्ण;

#घोषणा शेष_port_device(venकरोr, product)	\
	USB_DEVICE(venकरोr, product),	\
		.driver_info = (kernel_uदीर्घ_t)शेष_port_spec

#घोषणा icon321_port_device(venकरोr, product)	\
	USB_DEVICE(venकरोr, product),	\
		.driver_info = (kernel_uदीर्घ_t)icon321_port_spec

/* list of devices we support */
अटल स्थिर काष्ठा usb_device_id hso_ids[] = अणु
	अणुशेष_port_device(0x0af0, 0x6711)पूर्ण,
	अणुशेष_port_device(0x0af0, 0x6731)पूर्ण,
	अणुशेष_port_device(0x0af0, 0x6751)पूर्ण,
	अणुशेष_port_device(0x0af0, 0x6771)पूर्ण,
	अणुशेष_port_device(0x0af0, 0x6791)पूर्ण,
	अणुशेष_port_device(0x0af0, 0x6811)पूर्ण,
	अणुशेष_port_device(0x0af0, 0x6911)पूर्ण,
	अणुशेष_port_device(0x0af0, 0x6951)पूर्ण,
	अणुशेष_port_device(0x0af0, 0x6971)पूर्ण,
	अणुशेष_port_device(0x0af0, 0x7011)पूर्ण,
	अणुशेष_port_device(0x0af0, 0x7031)पूर्ण,
	अणुशेष_port_device(0x0af0, 0x7051)पूर्ण,
	अणुशेष_port_device(0x0af0, 0x7071)पूर्ण,
	अणुशेष_port_device(0x0af0, 0x7111)पूर्ण,
	अणुशेष_port_device(0x0af0, 0x7211)पूर्ण,
	अणुशेष_port_device(0x0af0, 0x7251)पूर्ण,
	अणुशेष_port_device(0x0af0, 0x7271)पूर्ण,
	अणुशेष_port_device(0x0af0, 0x7311)पूर्ण,
	अणुशेष_port_device(0x0af0, 0xc031)पूर्ण,	/* Icon-Edge */
	अणुicon321_port_device(0x0af0, 0xd013)पूर्ण,	/* Module HSxPA */
	अणुicon321_port_device(0x0af0, 0xd031)पूर्ण,	/* Icon-321 */
	अणुicon321_port_device(0x0af0, 0xd033)पूर्ण,	/* Icon-322 */
	अणुUSB_DEVICE(0x0af0, 0x7301)पूर्ण,		/* GE40x */
	अणुUSB_DEVICE(0x0af0, 0x7361)पूर्ण,		/* GE40x */
	अणुUSB_DEVICE(0x0af0, 0x7381)पूर्ण,		/* GE40x */
	अणुUSB_DEVICE(0x0af0, 0x7401)पूर्ण,		/* GI 0401 */
	अणुUSB_DEVICE(0x0af0, 0x7501)पूर्ण,		/* GTM 382 */
	अणुUSB_DEVICE(0x0af0, 0x7601)पूर्ण,		/* GE40x */
	अणुUSB_DEVICE(0x0af0, 0x7701)पूर्ण,
	अणुUSB_DEVICE(0x0af0, 0x7706)पूर्ण,
	अणुUSB_DEVICE(0x0af0, 0x7801)पूर्ण,
	अणुUSB_DEVICE(0x0af0, 0x7901)पूर्ण,
	अणुUSB_DEVICE(0x0af0, 0x7A01)पूर्ण,
	अणुUSB_DEVICE(0x0af0, 0x7A05)पूर्ण,
	अणुUSB_DEVICE(0x0af0, 0x8200)पूर्ण,
	अणुUSB_DEVICE(0x0af0, 0x8201)पूर्ण,
	अणुUSB_DEVICE(0x0af0, 0x8300)पूर्ण,
	अणुUSB_DEVICE(0x0af0, 0x8302)पूर्ण,
	अणुUSB_DEVICE(0x0af0, 0x8304)पूर्ण,
	अणुUSB_DEVICE(0x0af0, 0x8400)पूर्ण,
	अणुUSB_DEVICE(0x0af0, 0x8600)पूर्ण,
	अणुUSB_DEVICE(0x0af0, 0x8800)पूर्ण,
	अणुUSB_DEVICE(0x0af0, 0x8900)पूर्ण,
	अणुUSB_DEVICE(0x0af0, 0x9000)पूर्ण,
	अणुUSB_DEVICE(0x0af0, 0x9200)पूर्ण,		/* Option GTM671WFS */
	अणुUSB_DEVICE(0x0af0, 0xd035)पूर्ण,
	अणुUSB_DEVICE(0x0af0, 0xd055)पूर्ण,
	अणुUSB_DEVICE(0x0af0, 0xd155)पूर्ण,
	अणुUSB_DEVICE(0x0af0, 0xd255)पूर्ण,
	अणुUSB_DEVICE(0x0af0, 0xd057)पूर्ण,
	अणुUSB_DEVICE(0x0af0, 0xd157)पूर्ण,
	अणुUSB_DEVICE(0x0af0, 0xd257)पूर्ण,
	अणुUSB_DEVICE(0x0af0, 0xd357)पूर्ण,
	अणुUSB_DEVICE(0x0af0, 0xd058)पूर्ण,
	अणुUSB_DEVICE(0x0af0, 0xc100)पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, hso_ids);

/* Sysfs attribute */
अटल sमाप_प्रकार hso_sysfs_show_porttype(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा hso_device *hso_dev = dev_get_drvdata(dev);
	अक्षर *port_name;

	अगर (!hso_dev)
		वापस 0;

	चयन (hso_dev->port_spec & HSO_PORT_MASK) अणु
	हाल HSO_PORT_CONTROL:
		port_name = "Control";
		अवरोध;
	हाल HSO_PORT_APP:
		port_name = "Application";
		अवरोध;
	हाल HSO_PORT_APP2:
		port_name = "Application2";
		अवरोध;
	हाल HSO_PORT_GPS:
		port_name = "GPS";
		अवरोध;
	हाल HSO_PORT_GPS_CONTROL:
		port_name = "GPS Control";
		अवरोध;
	हाल HSO_PORT_PCSC:
		port_name = "PCSC";
		अवरोध;
	हाल HSO_PORT_DIAG:
		port_name = "Diagnostic";
		अवरोध;
	हाल HSO_PORT_DIAG2:
		port_name = "Diagnostic2";
		अवरोध;
	हाल HSO_PORT_MODEM:
		port_name = "Modem";
		अवरोध;
	हाल HSO_PORT_NETWORK:
		port_name = "Network";
		अवरोध;
	शेष:
		port_name = "Unknown";
		अवरोध;
	पूर्ण

	वापस प्र_लिखो(buf, "%s\n", port_name);
पूर्ण
अटल DEVICE_ATTR(hsotype, 0444, hso_sysfs_show_porttype, शून्य);

अटल काष्ठा attribute *hso_serial_dev_attrs[] = अणु
	&dev_attr_hsotype.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(hso_serial_dev);

अटल पूर्णांक hso_urb_to_index(काष्ठा hso_serial *serial, काष्ठा urb *urb)
अणु
	पूर्णांक idx;

	क्रम (idx = 0; idx < serial->num_rx_urbs; idx++)
		अगर (serial->rx_urb[idx] == urb)
			वापस idx;
	dev_err(serial->parent->dev, "hso_urb_to_index failed\n");
	वापस -1;
पूर्ण

/* converts mux value to a port spec value */
अटल u32 hso_mux_to_port(पूर्णांक mux)
अणु
	u32 result;

	चयन (mux) अणु
	हाल 0x1:
		result = HSO_PORT_CONTROL;
		अवरोध;
	हाल 0x2:
		result = HSO_PORT_APP;
		अवरोध;
	हाल 0x4:
		result = HSO_PORT_PCSC;
		अवरोध;
	हाल 0x8:
		result = HSO_PORT_GPS;
		अवरोध;
	हाल 0x10:
		result = HSO_PORT_APP2;
		अवरोध;
	शेष:
		result = HSO_PORT_NO_PORT;
	पूर्ण
	वापस result;
पूर्ण

/* converts port spec value to a mux value */
अटल u32 hso_port_to_mux(पूर्णांक port)
अणु
	u32 result;

	चयन (port & HSO_PORT_MASK) अणु
	हाल HSO_PORT_CONTROL:
		result = 0x0;
		अवरोध;
	हाल HSO_PORT_APP:
		result = 0x1;
		अवरोध;
	हाल HSO_PORT_PCSC:
		result = 0x2;
		अवरोध;
	हाल HSO_PORT_GPS:
		result = 0x3;
		अवरोध;
	हाल HSO_PORT_APP2:
		result = 0x4;
		अवरोध;
	शेष:
		result = 0x0;
	पूर्ण
	वापस result;
पूर्ण

अटल काष्ठा hso_serial *get_serial_by_shared_पूर्णांक_and_type(
					काष्ठा hso_shared_पूर्णांक *shared_पूर्णांक,
					पूर्णांक mux)
अणु
	पूर्णांक i, port;

	port = hso_mux_to_port(mux);

	क्रम (i = 0; i < HSO_SERIAL_TTY_MINORS; i++) अणु
		अगर (serial_table[i] &&
		    (dev2ser(serial_table[i])->shared_पूर्णांक == shared_पूर्णांक) &&
		    ((serial_table[i]->port_spec & HSO_PORT_MASK) == port)) अणु
			वापस dev2ser(serial_table[i]);
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा hso_serial *get_serial_by_index(अचिन्हित index)
अणु
	काष्ठा hso_serial *serial = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&serial_table_lock, flags);
	अगर (serial_table[index])
		serial = dev2ser(serial_table[index]);
	spin_unlock_irqrestore(&serial_table_lock, flags);

	वापस serial;
पूर्ण

अटल पूर्णांक obtain_minor(काष्ठा hso_serial *serial)
अणु
	पूर्णांक index;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&serial_table_lock, flags);
	क्रम (index = 0; index < HSO_SERIAL_TTY_MINORS; index++) अणु
		अगर (serial_table[index] == शून्य) अणु
			serial_table[index] = serial->parent;
			serial->minor = index;
			spin_unlock_irqrestore(&serial_table_lock, flags);
			वापस 0;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&serial_table_lock, flags);

	pr_err("%s: no free serial devices in table\n", __func__);
	वापस -1;
पूर्ण

अटल व्योम release_minor(काष्ठा hso_serial *serial)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&serial_table_lock, flags);
	serial_table[serial->minor] = शून्य;
	spin_unlock_irqrestore(&serial_table_lock, flags);
पूर्ण

अटल व्योम handle_usb_error(पूर्णांक status, स्थिर अक्षर *function,
			     काष्ठा hso_device *hso_dev)
अणु
	अक्षर *explanation;

	चयन (status) अणु
	हाल -ENODEV:
		explanation = "no device";
		अवरोध;
	हाल -ENOENT:
		explanation = "endpoint not enabled";
		अवरोध;
	हाल -EPIPE:
		explanation = "endpoint stalled";
		अवरोध;
	हाल -ENOSPC:
		explanation = "not enough bandwidth";
		अवरोध;
	हाल -ESHUTDOWN:
		explanation = "device disabled";
		अवरोध;
	हाल -EHOSTUNREACH:
		explanation = "device suspended";
		अवरोध;
	हाल -EINVAL:
	हाल -EAGAIN:
	हाल -EFBIG:
	हाल -EMSGSIZE:
		explanation = "internal error";
		अवरोध;
	हाल -EILSEQ:
	हाल -EPROTO:
	हाल -ETIME:
	हाल -ETIMEDOUT:
		explanation = "protocol error";
		अगर (hso_dev)
			usb_queue_reset_device(hso_dev->पूर्णांकerface);
		अवरोध;
	शेष:
		explanation = "unknown status";
		अवरोध;
	पूर्ण

	/* log a meaningful explanation of an USB status */
	hso_dbg(0x1, "%s: received USB status - %s (%d)\n",
		function, explanation, status);
पूर्ण

/* Network पूर्णांकerface functions */

/* called when net पूर्णांकerface is brought up by अगरconfig */
अटल पूर्णांक hso_net_खोलो(काष्ठा net_device *net)
अणु
	काष्ठा hso_net *odev = netdev_priv(net);
	अचिन्हित दीर्घ flags = 0;

	अगर (!odev) अणु
		dev_err(&net->dev, "No net device !\n");
		वापस -ENODEV;
	पूर्ण

	odev->skb_tx_buf = शून्य;

	/* setup environment */
	spin_lock_irqsave(&odev->net_lock, flags);
	odev->rx_parse_state = WAIT_IP;
	odev->rx_buf_size = 0;
	odev->rx_buf_missing = माप(काष्ठा iphdr);
	spin_unlock_irqrestore(&odev->net_lock, flags);

	/* We are up and running. */
	set_bit(HSO_NET_RUNNING, &odev->flags);
	hso_start_net_device(odev->parent);

	/* Tell the kernel we are पढ़ोy to start receiving from it */
	netअगर_start_queue(net);

	वापस 0;
पूर्ण

/* called when पूर्णांकerface is brought करोwn by अगरconfig */
अटल पूर्णांक hso_net_बंद(काष्ठा net_device *net)
अणु
	काष्ठा hso_net *odev = netdev_priv(net);

	/* we करोn't need the queue anymore */
	netअगर_stop_queue(net);
	/* no दीर्घer running */
	clear_bit(HSO_NET_RUNNING, &odev->flags);

	hso_stop_net_device(odev->parent);

	/* करोne */
	वापस 0;
पूर्ण

/* USB tells is xmit करोne, we should start the netqueue again */
अटल व्योम ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा hso_net *odev = urb->context;
	पूर्णांक status = urb->status;

	/* Sanity check */
	अगर (!odev || !test_bit(HSO_NET_RUNNING, &odev->flags)) अणु
		dev_err(&urb->dev->dev, "%s: device not running\n", __func__);
		वापस;
	पूर्ण

	/* Do we still have a valid kernel network device? */
	अगर (!netअगर_device_present(odev->net)) अणु
		dev_err(&urb->dev->dev, "%s: net device not present\n",
			__func__);
		वापस;
	पूर्ण

	/* log status, but करोn't act on it, we don't need to resubmit anything
	 * anyhow */
	अगर (status)
		handle_usb_error(status, __func__, odev->parent);

	hso_put_activity(odev->parent);

	/* Tell the network पूर्णांकerface we are पढ़ोy क्रम another frame */
	netअगर_wake_queue(odev->net);
पूर्ण

/* called by kernel when we need to transmit a packet */
अटल netdev_tx_t hso_net_start_xmit(काष्ठा sk_buff *skb,
					    काष्ठा net_device *net)
अणु
	काष्ठा hso_net *odev = netdev_priv(net);
	पूर्णांक result;

	/* Tell the kernel, "No more frames 'til we are done with this one." */
	netअगर_stop_queue(net);
	अगर (hso_get_activity(odev->parent) == -EAGAIN) अणु
		odev->skb_tx_buf = skb;
		वापस NETDEV_TX_OK;
	पूर्ण

	/* log अगर asked */
	DUMP1(skb->data, skb->len);
	/* Copy it from kernel memory to OUR memory */
	स_नकल(odev->mux_bulk_tx_buf, skb->data, skb->len);
	hso_dbg(0x1, "len: %d/%d\n", skb->len, MUX_BULK_TX_BUF_SIZE);

	/* Fill in the URB क्रम shipping it out. */
	usb_fill_bulk_urb(odev->mux_bulk_tx_urb,
			  odev->parent->usb,
			  usb_sndbulkpipe(odev->parent->usb,
					  odev->out_endp->
					  bEndpoपूर्णांकAddress & 0x7F),
			  odev->mux_bulk_tx_buf, skb->len, ग_लिखो_bulk_callback,
			  odev);

	/* Deal with the Zero Length packet problem, I hope */
	odev->mux_bulk_tx_urb->transfer_flags |= URB_ZERO_PACKET;

	/* Send the URB on its merry way. */
	result = usb_submit_urb(odev->mux_bulk_tx_urb, GFP_ATOMIC);
	अगर (result) अणु
		dev_warn(&odev->parent->पूर्णांकerface->dev,
			"failed mux_bulk_tx_urb %d\n", result);
		net->stats.tx_errors++;
		netअगर_start_queue(net);
	पूर्ण अन्यथा अणु
		net->stats.tx_packets++;
		net->stats.tx_bytes += skb->len;
	पूर्ण
	dev_kमुक्त_skb(skb);
	/* we're करोne */
	वापस NETDEV_TX_OK;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ops = अणु
	.get_link = ethtool_op_get_link
पूर्ण;

/* called when a packet did not ack after watchकरोgसमयout */
अटल व्योम hso_net_tx_समयout(काष्ठा net_device *net, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा hso_net *odev = netdev_priv(net);

	अगर (!odev)
		वापस;

	/* Tell syslog we are hosed. */
	dev_warn(&net->dev, "Tx timed out.\n");

	/* Tear the रुकोing frame off the list */
	अगर (odev->mux_bulk_tx_urb)
		usb_unlink_urb(odev->mux_bulk_tx_urb);

	/* Update statistics */
	net->stats.tx_errors++;
पूर्ण

/* make a real packet from the received USB buffer */
अटल व्योम packetizeRx(काष्ठा hso_net *odev, अचिन्हित अक्षर *ip_pkt,
			अचिन्हित पूर्णांक count, अचिन्हित अक्षर is_eop)
अणु
	अचिन्हित लघु temp_bytes;
	अचिन्हित लघु buffer_offset = 0;
	अचिन्हित लघु frame_len;

	/* log अगर needed */
	hso_dbg(0x1, "Rx %d bytes\n", count);
	DUMP(ip_pkt, min(128, (पूर्णांक)count));

	जबतक (count) अणु
		चयन (odev->rx_parse_state) अणु
		हाल WAIT_IP:
			/* रुकोing क्रम IP header. */
			/* wanted bytes - size of ip header */
			temp_bytes =
			    (count <
			     odev->rx_buf_missing) ? count : odev->
			    rx_buf_missing;

			स_नकल(((अचिन्हित अक्षर *)(&odev->rx_ip_hdr)) +
			       odev->rx_buf_size, ip_pkt + buffer_offset,
			       temp_bytes);

			odev->rx_buf_size += temp_bytes;
			buffer_offset += temp_bytes;
			odev->rx_buf_missing -= temp_bytes;
			count -= temp_bytes;

			अगर (!odev->rx_buf_missing) अणु
				/* header is complete allocate an sk_buffer and
				 * जारी to WAIT_DATA */
				frame_len = ntohs(odev->rx_ip_hdr.tot_len);

				अगर ((frame_len > DEFAULT_MRU) ||
				    (frame_len < माप(काष्ठा iphdr))) अणु
					dev_err(&odev->net->dev,
						"Invalid frame (%d) length\n",
						frame_len);
					odev->rx_parse_state = WAIT_SYNC;
					जारी;
				पूर्ण
				/* Allocate an sk_buff */
				odev->skb_rx_buf = netdev_alloc_skb(odev->net,
								    frame_len);
				अगर (!odev->skb_rx_buf) अणु
					/* We got no receive buffer. */
					hso_dbg(0x1, "could not allocate memory\n");
					odev->rx_parse_state = WAIT_SYNC;
					जारी;
				पूर्ण

				/* Copy what we got so far. make room क्रम iphdr
				 * after tail. */
				skb_put_data(odev->skb_rx_buf,
					     (अक्षर *)&(odev->rx_ip_hdr),
					     माप(काष्ठा iphdr));

				/* ETH_HLEN */
				odev->rx_buf_size = माप(काष्ठा iphdr);

				/* Filip actually use .tot_len */
				odev->rx_buf_missing =
				    frame_len - माप(काष्ठा iphdr);
				odev->rx_parse_state = WAIT_DATA;
			पूर्ण
			अवरोध;

		हाल WAIT_DATA:
			temp_bytes = (count < odev->rx_buf_missing)
					? count : odev->rx_buf_missing;

			/* Copy the rest of the bytes that are left in the
			 * buffer पूर्णांकo the रुकोing sk_buf. */
			/* Make room क्रम temp_bytes after tail. */
			skb_put_data(odev->skb_rx_buf,
				     ip_pkt + buffer_offset,
				     temp_bytes);

			odev->rx_buf_missing -= temp_bytes;
			count -= temp_bytes;
			buffer_offset += temp_bytes;
			odev->rx_buf_size += temp_bytes;
			अगर (!odev->rx_buf_missing) अणु
				/* Packet is complete. Inject पूर्णांकo stack. */
				/* We have IP packet here */
				odev->skb_rx_buf->protocol = cpu_to_be16(ETH_P_IP);
				skb_reset_mac_header(odev->skb_rx_buf);

				/* Ship it off to the kernel */
				netअगर_rx(odev->skb_rx_buf);
				/* No दीर्घer our buffer. */
				odev->skb_rx_buf = शून्य;

				/* update out statistics */
				odev->net->stats.rx_packets++;

				odev->net->stats.rx_bytes += odev->rx_buf_size;

				odev->rx_buf_size = 0;
				odev->rx_buf_missing = माप(काष्ठा iphdr);
				odev->rx_parse_state = WAIT_IP;
			पूर्ण
			अवरोध;

		हाल WAIT_SYNC:
			hso_dbg(0x1, " W_S\n");
			count = 0;
			अवरोध;
		शेष:
			hso_dbg(0x1, "\n");
			count--;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Recovery mechanism क्रम WAIT_SYNC state. */
	अगर (is_eop) अणु
		अगर (odev->rx_parse_state == WAIT_SYNC) अणु
			odev->rx_parse_state = WAIT_IP;
			odev->rx_buf_size = 0;
			odev->rx_buf_missing = माप(काष्ठा iphdr);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम fix_crc_bug(काष्ठा urb *urb, __le16 max_packet_size)
अणु
	अटल स्थिर u8 crc_check[4] = अणु 0xDE, 0xAD, 0xBE, 0xEF पूर्ण;
	u32 rest = urb->actual_length % le16_to_cpu(max_packet_size);

	अगर (((rest == 5) || (rest == 6)) &&
	    !स_भेद(((u8 *)urb->transfer_buffer) + urb->actual_length - 4,
		    crc_check, 4)) अणु
		urb->actual_length -= 4;
	पूर्ण
पूर्ण

/* Moving data from usb to kernel (in पूर्णांकerrupt state) */
अटल व्योम पढ़ो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा hso_net *odev = urb->context;
	काष्ठा net_device *net;
	पूर्णांक result;
	अचिन्हित दीर्घ flags;
	पूर्णांक status = urb->status;

	/* is al ok?  (Filip: Who's Al ?) */
	अगर (status) अणु
		handle_usb_error(status, __func__, odev->parent);
		वापस;
	पूर्ण

	/* Sanity check */
	अगर (!odev || !test_bit(HSO_NET_RUNNING, &odev->flags)) अणु
		hso_dbg(0x1, "BULK IN callback but driver is not active!\n");
		वापस;
	पूर्ण
	usb_mark_last_busy(urb->dev);

	net = odev->net;

	अगर (!netअगर_device_present(net)) अणु
		/* Somebody समाप्तed our network पूर्णांकerface... */
		वापस;
	पूर्ण

	अगर (odev->parent->port_spec & HSO_INFO_CRC_BUG)
		fix_crc_bug(urb, odev->in_endp->wMaxPacketSize);

	/* करो we even have a packet? */
	अगर (urb->actual_length) अणु
		/* Handle the IP stream, add header and push it onto network
		 * stack अगर the packet is complete. */
		spin_lock_irqsave(&odev->net_lock, flags);
		packetizeRx(odev, urb->transfer_buffer, urb->actual_length,
			    (urb->transfer_buffer_length >
			     urb->actual_length) ? 1 : 0);
		spin_unlock_irqrestore(&odev->net_lock, flags);
	पूर्ण

	/* We are करोne with this URB, resubmit it. Prep the USB to रुको क्रम
	 * another frame. Reuse same as received. */
	usb_fill_bulk_urb(urb,
			  odev->parent->usb,
			  usb_rcvbulkpipe(odev->parent->usb,
					  odev->in_endp->
					  bEndpoपूर्णांकAddress & 0x7F),
			  urb->transfer_buffer, MUX_BULK_RX_BUF_SIZE,
			  पढ़ो_bulk_callback, odev);

	/* Give this to the USB subप्रणाली so it can tell us when more data
	 * arrives. */
	result = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (result)
		dev_warn(&odev->parent->पूर्णांकerface->dev,
			 "%s failed submit mux_bulk_rx_urb %d\n", __func__,
			 result);
पूर्ण

/* Serial driver functions */

अटल व्योम hso_init_termios(काष्ठा ktermios *termios)
अणु
	/*
	 * The शेष requirements क्रम this device are:
	 */
	termios->c_अगरlag &=
		~(IGNBRK	/* disable ignore अवरोध */
		| BRKINT	/* disable अवरोध causes पूर्णांकerrupt */
		| PARMRK	/* disable mark parity errors */
		| ISTRIP	/* disable clear high bit of input अक्षरacters */
		| INLCR		/* disable translate NL to CR */
		| IGNCR		/* disable ignore CR */
		| ICRNL		/* disable translate CR to NL */
		| IXON);	/* disable enable XON/XOFF flow control */

	/* disable postprocess output अक्षरacters */
	termios->c_oflag &= ~OPOST;

	termios->c_lflag &=
		~(ECHO		/* disable echo input अक्षरacters */
		| ECHONL	/* disable echo new line */
		| ICANON	/* disable erase, समाप्त, werase, and rprnt
				   special अक्षरacters */
		| ISIG		/* disable पूर्णांकerrupt, quit, and suspend special
				   अक्षरacters */
		| IEXTEN);	/* disable non-POSIX special अक्षरacters */

	termios->c_cflag &=
		~(CSIZE		/* no size */
		| PARENB	/* disable parity bit */
		| CBAUD		/* clear current baud rate */
		| CBAUDEX);	/* clear current buad rate */

	termios->c_cflag |= CS8;	/* अक्षरacter size 8 bits */

	/* baud rate 115200 */
	tty_termios_encode_baud_rate(termios, 115200, 115200);
पूर्ण

अटल व्योम _hso_serial_set_termios(काष्ठा tty_काष्ठा *tty,
				    काष्ठा ktermios *old)
अणु
	काष्ठा hso_serial *serial = tty->driver_data;

	अगर (!serial) अणु
		pr_err("%s: no tty structures", __func__);
		वापस;
	पूर्ण

	hso_dbg(0x8, "port %d\n", serial->minor);

	/*
	 *	Fix up unsupported bits
	 */
	tty->termios.c_अगरlag &= ~IXON; /* disable enable XON/XOFF flow control */

	tty->termios.c_cflag &=
		~(CSIZE		/* no size */
		| PARENB	/* disable parity bit */
		| CBAUD		/* clear current baud rate */
		| CBAUDEX);	/* clear current buad rate */

	tty->termios.c_cflag |= CS8;	/* अक्षरacter size 8 bits */

	/* baud rate 115200 */
	tty_encode_baud_rate(tty, 115200, 115200);
पूर्ण

अटल व्योम hso_resubmit_rx_bulk_urb(काष्ठा hso_serial *serial, काष्ठा urb *urb)
अणु
	पूर्णांक result;
	/* We are करोne with this URB, resubmit it. Prep the USB to रुको क्रम
	 * another frame */
	usb_fill_bulk_urb(urb, serial->parent->usb,
			  usb_rcvbulkpipe(serial->parent->usb,
					  serial->in_endp->
					  bEndpoपूर्णांकAddress & 0x7F),
			  urb->transfer_buffer, serial->rx_data_length,
			  hso_std_serial_पढ़ो_bulk_callback, serial);
	/* Give this to the USB subप्रणाली so it can tell us when more data
	 * arrives. */
	result = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (result) अणु
		dev_err(&urb->dev->dev, "%s failed submit serial rx_urb %d\n",
			__func__, result);
	पूर्ण
पूर्ण




अटल व्योम put_rxbuf_data_and_resubmit_bulk_urb(काष्ठा hso_serial *serial)
अणु
	पूर्णांक count;
	काष्ठा urb *curr_urb;

	जबतक (serial->rx_urb_filled[serial->curr_rx_urb_idx]) अणु
		curr_urb = serial->rx_urb[serial->curr_rx_urb_idx];
		count = put_rxbuf_data(curr_urb, serial);
		अगर (count == -1)
			वापस;
		अगर (count == 0) अणु
			serial->curr_rx_urb_idx++;
			अगर (serial->curr_rx_urb_idx >= serial->num_rx_urbs)
				serial->curr_rx_urb_idx = 0;
			hso_resubmit_rx_bulk_urb(serial, curr_urb);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम put_rxbuf_data_and_resubmit_ctrl_urb(काष्ठा hso_serial *serial)
अणु
	पूर्णांक count = 0;
	काष्ठा urb *urb;

	urb = serial->rx_urb[0];
	अगर (serial->port.count > 0) अणु
		count = put_rxbuf_data(urb, serial);
		अगर (count == -1)
			वापस;
	पूर्ण
	/* Re issue a पढ़ो as दीर्घ as we receive data. */

	अगर (count == 0 && ((urb->actual_length != 0) ||
			   (serial->rx_state == RX_PENDING))) अणु
		serial->rx_state = RX_SENT;
		hso_mux_serial_पढ़ो(serial);
	पूर्ण अन्यथा
		serial->rx_state = RX_IDLE;
पूर्ण


/* पढ़ो callback क्रम Diag and CS port */
अटल व्योम hso_std_serial_पढ़ो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा hso_serial *serial = urb->context;
	पूर्णांक status = urb->status;
	अचिन्हित दीर्घ flags;

	hso_dbg(0x8, "--- Got serial_read_bulk callback %02x ---\n", status);

	/* sanity check */
	अगर (!serial) अणु
		hso_dbg(0x1, "serial == NULL\n");
		वापस;
	पूर्ण
	अगर (status) अणु
		handle_usb_error(status, __func__, serial->parent);
		वापस;
	पूर्ण

	hso_dbg(0x1, "Actual length = %d\n", urb->actual_length);
	DUMP1(urb->transfer_buffer, urb->actual_length);

	/* Anyone listening? */
	अगर (serial->port.count == 0)
		वापस;

	अगर (serial->parent->port_spec & HSO_INFO_CRC_BUG)
		fix_crc_bug(urb, serial->in_endp->wMaxPacketSize);
	/* Valid data, handle RX data */
	spin_lock_irqsave(&serial->serial_lock, flags);
	serial->rx_urb_filled[hso_urb_to_index(serial, urb)] = 1;
	put_rxbuf_data_and_resubmit_bulk_urb(serial);
	spin_unlock_irqrestore(&serial->serial_lock, flags);
पूर्ण

/*
 * This needs to be a tasklet otherwise we will
 * end up recursively calling this function.
 */
अटल व्योम hso_unthrottle_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा hso_serial *serial = from_tasklet(serial, t,
						 unthrottle_tasklet);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&serial->serial_lock, flags);
	अगर ((serial->parent->port_spec & HSO_INTF_MUX))
		put_rxbuf_data_and_resubmit_ctrl_urb(serial);
	अन्यथा
		put_rxbuf_data_and_resubmit_bulk_urb(serial);
	spin_unlock_irqrestore(&serial->serial_lock, flags);
पूर्ण

अटल	व्योम hso_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा hso_serial *serial = tty->driver_data;

	tasklet_hi_schedule(&serial->unthrottle_tasklet);
पूर्ण

/* खोलो the requested serial port */
अटल पूर्णांक hso_serial_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा hso_serial *serial = get_serial_by_index(tty->index);
	पूर्णांक result;

	/* sanity check */
	अगर (serial == शून्य || serial->magic != HSO_SERIAL_MAGIC) अणु
		WARN_ON(1);
		tty->driver_data = शून्य;
		hso_dbg(0x1, "Failed to open port\n");
		वापस -ENODEV;
	पूर्ण

	mutex_lock(&serial->parent->mutex);
	result = usb_स्वतःpm_get_पूर्णांकerface(serial->parent->पूर्णांकerface);
	अगर (result < 0)
		जाओ err_out;

	hso_dbg(0x1, "Opening %d\n", serial->minor);

	/* setup */
	tty->driver_data = serial;
	tty_port_tty_set(&serial->port, tty);

	/* check क्रम port alपढ़ोy खोलोed, अगर not set the termios */
	serial->port.count++;
	अगर (serial->port.count == 1) अणु
		serial->rx_state = RX_IDLE;
		/* Force शेष termio settings */
		_hso_serial_set_termios(tty, शून्य);
		tasklet_setup(&serial->unthrottle_tasklet,
			      hso_unthrottle_tasklet);
		result = hso_start_serial_device(serial->parent, GFP_KERNEL);
		अगर (result) अणु
			hso_stop_serial_device(serial->parent);
			serial->port.count--;
		पूर्ण अन्यथा अणु
			kref_get(&serial->parent->ref);
		पूर्ण
	पूर्ण अन्यथा अणु
		hso_dbg(0x1, "Port was already open\n");
	पूर्ण

	usb_स्वतःpm_put_पूर्णांकerface(serial->parent->पूर्णांकerface);

	/* करोne */
	अगर (result)
		hso_serial_tiocmset(tty, TIOCM_RTS | TIOCM_DTR, 0);
err_out:
	mutex_unlock(&serial->parent->mutex);
	वापस result;
पूर्ण

/* बंद the requested serial port */
अटल व्योम hso_serial_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा hso_serial *serial = tty->driver_data;
	u8 usb_gone;

	hso_dbg(0x1, "Closing serial port\n");

	/* Open failed, no बंद cleanup required */
	अगर (serial == शून्य)
		वापस;

	mutex_lock(&serial->parent->mutex);
	usb_gone = serial->parent->usb_gone;

	अगर (!usb_gone)
		usb_स्वतःpm_get_पूर्णांकerface(serial->parent->पूर्णांकerface);

	/* reset the rts and dtr */
	/* करो the actual बंद */
	serial->port.count--;

	अगर (serial->port.count <= 0) अणु
		serial->port.count = 0;
		tty_port_tty_set(&serial->port, शून्य);
		अगर (!usb_gone)
			hso_stop_serial_device(serial->parent);
		tasklet_समाप्त(&serial->unthrottle_tasklet);
	पूर्ण

	अगर (!usb_gone)
		usb_स्वतःpm_put_पूर्णांकerface(serial->parent->पूर्णांकerface);

	mutex_unlock(&serial->parent->mutex);
पूर्ण

/* बंद the requested serial port */
अटल पूर्णांक hso_serial_ग_लिखो(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buf,
			    पूर्णांक count)
अणु
	काष्ठा hso_serial *serial = tty->driver_data;
	पूर्णांक space, tx_bytes;
	अचिन्हित दीर्घ flags;

	/* sanity check */
	अगर (serial == शून्य) अणु
		pr_err("%s: serial is NULL\n", __func__);
		वापस -ENODEV;
	पूर्ण

	spin_lock_irqsave(&serial->serial_lock, flags);

	space = serial->tx_data_length - serial->tx_buffer_count;
	tx_bytes = (count < space) ? count : space;

	अगर (!tx_bytes)
		जाओ out;

	स_नकल(serial->tx_buffer + serial->tx_buffer_count, buf, tx_bytes);
	serial->tx_buffer_count += tx_bytes;

out:
	spin_unlock_irqrestore(&serial->serial_lock, flags);

	hso_kick_transmit(serial);
	/* करोne */
	वापस tx_bytes;
पूर्ण

/* how much room is there क्रम writing */
अटल पूर्णांक hso_serial_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा hso_serial *serial = tty->driver_data;
	पूर्णांक room;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&serial->serial_lock, flags);
	room = serial->tx_data_length - serial->tx_buffer_count;
	spin_unlock_irqrestore(&serial->serial_lock, flags);

	/* वापस मुक्त room */
	वापस room;
पूर्ण

अटल व्योम hso_serial_cleanup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा hso_serial *serial = tty->driver_data;

	अगर (!serial)
		वापस;

	kref_put(&serial->parent->ref, hso_serial_ref_मुक्त);
पूर्ण

/* setup the term */
अटल व्योम hso_serial_set_termios(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios *old)
अणु
	काष्ठा hso_serial *serial = tty->driver_data;
	अचिन्हित दीर्घ flags;

	अगर (old)
		hso_dbg(0x16, "Termios called with: cflags new[%u] - old[%u]\n",
			(अचिन्हित पूर्णांक)tty->termios.c_cflag,
			(अचिन्हित पूर्णांक)old->c_cflag);

	/* the actual setup */
	spin_lock_irqsave(&serial->serial_lock, flags);
	अगर (serial->port.count)
		_hso_serial_set_termios(tty, old);
	अन्यथा
		tty->termios = *old;
	spin_unlock_irqrestore(&serial->serial_lock, flags);

	/* करोne */
पूर्ण

/* how many अक्षरacters in the buffer */
अटल पूर्णांक hso_serial_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा hso_serial *serial = tty->driver_data;
	पूर्णांक अक्षरs;
	अचिन्हित दीर्घ flags;

	/* sanity check */
	अगर (serial == शून्य)
		वापस 0;

	spin_lock_irqsave(&serial->serial_lock, flags);
	अक्षरs = serial->tx_buffer_count;
	spin_unlock_irqrestore(&serial->serial_lock, flags);

	वापस अक्षरs;
पूर्ण
अटल पूर्णांक tiocmget_submit_urb(काष्ठा hso_serial *serial,
			       काष्ठा hso_tiocmget *tiocmget,
			       काष्ठा usb_device *usb)
अणु
	पूर्णांक result;

	अगर (serial->parent->usb_gone)
		वापस -ENODEV;
	usb_fill_पूर्णांक_urb(tiocmget->urb, usb,
			 usb_rcvपूर्णांकpipe(usb,
					tiocmget->endp->
					bEndpoपूर्णांकAddress & 0x7F),
			 tiocmget->serial_state_notअगरication,
			 माप(काष्ठा hso_serial_state_notअगरication),
			 tiocmget_पूर्णांकr_callback, serial,
			 tiocmget->endp->bInterval);
	result = usb_submit_urb(tiocmget->urb, GFP_ATOMIC);
	अगर (result) अणु
		dev_warn(&usb->dev, "%s usb_submit_urb failed %d\n", __func__,
			 result);
	पूर्ण
	वापस result;

पूर्ण

अटल व्योम tiocmget_पूर्णांकr_callback(काष्ठा urb *urb)
अणु
	काष्ठा hso_serial *serial = urb->context;
	काष्ठा hso_tiocmget *tiocmget;
	पूर्णांक status = urb->status;
	u16 UART_state_biपंचांगap, prev_UART_state_biपंचांगap;
	काष्ठा uart_icount *icount;
	काष्ठा hso_serial_state_notअगरication *serial_state_notअगरication;
	काष्ठा usb_device *usb;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;
	पूर्णांक अगर_num;

	/* Sanity checks */
	अगर (!serial)
		वापस;
	अगर (status) अणु
		handle_usb_error(status, __func__, serial->parent);
		वापस;
	पूर्ण

	/* tiocmget is only supported on HSO_PORT_MODEM */
	tiocmget = serial->tiocmget;
	अगर (!tiocmget)
		वापस;
	BUG_ON((serial->parent->port_spec & HSO_PORT_MASK) != HSO_PORT_MODEM);

	usb = serial->parent->usb;
	पूर्णांकerface = serial->parent->पूर्णांकerface;

	अगर_num = पूर्णांकerface->cur_altsetting->desc.bInterfaceNumber;

	/* wIndex should be the USB पूर्णांकerface number of the port to which the
	 * notअगरication applies, which should always be the Modem port.
	 */
	serial_state_notअगरication = tiocmget->serial_state_notअगरication;
	अगर (serial_state_notअगरication->bmRequestType != BM_REQUEST_TYPE ||
	    serial_state_notअगरication->bNotअगरication != B_NOTIFICATION ||
	    le16_to_cpu(serial_state_notअगरication->wValue) != W_VALUE ||
	    le16_to_cpu(serial_state_notअगरication->wIndex) != अगर_num ||
	    le16_to_cpu(serial_state_notअगरication->wLength) != W_LENGTH) अणु
		dev_warn(&usb->dev,
			 "hso received invalid serial state notification\n");
		DUMP(serial_state_notअगरication,
		     माप(काष्ठा hso_serial_state_notअगरication));
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ flags;

		UART_state_biपंचांगap = le16_to_cpu(serial_state_notअगरication->
						UART_state_biपंचांगap);
		prev_UART_state_biपंचांगap = tiocmget->prev_UART_state_biपंचांगap;
		icount = &tiocmget->icount;
		spin_lock_irqsave(&serial->serial_lock, flags);
		अगर ((UART_state_biपंचांगap & B_OVERRUN) !=
		   (prev_UART_state_biपंचांगap & B_OVERRUN))
			icount->parity++;
		अगर ((UART_state_biपंचांगap & B_PARITY) !=
		   (prev_UART_state_biपंचांगap & B_PARITY))
			icount->parity++;
		अगर ((UART_state_biपंचांगap & B_FRAMING) !=
		   (prev_UART_state_biपंचांगap & B_FRAMING))
			icount->frame++;
		अगर ((UART_state_biपंचांगap & B_RING_SIGNAL) &&
		   !(prev_UART_state_biपंचांगap & B_RING_SIGNAL))
			icount->rng++;
		अगर ((UART_state_biपंचांगap & B_BREAK) !=
		   (prev_UART_state_biपंचांगap & B_BREAK))
			icount->brk++;
		अगर ((UART_state_biपंचांगap & B_TX_CARRIER) !=
		   (prev_UART_state_biपंचांगap & B_TX_CARRIER))
			icount->dsr++;
		अगर ((UART_state_biपंचांगap & B_RX_CARRIER) !=
		   (prev_UART_state_biपंचांगap & B_RX_CARRIER))
			icount->dcd++;
		tiocmget->prev_UART_state_biपंचांगap = UART_state_biपंचांगap;
		spin_unlock_irqrestore(&serial->serial_lock, flags);
		tiocmget->पूर्णांकr_completed = 1;
		wake_up_पूर्णांकerruptible(&tiocmget->रुकोq);
	पूर्ण
	स_रखो(serial_state_notअगरication, 0,
	       माप(काष्ठा hso_serial_state_notअगरication));
	tiocmget_submit_urb(serial,
			    tiocmget,
			    serial->parent->usb);
पूर्ण

/*
 * next few functions largely stolen from drivers/serial/serial_core.c
 */
/* Wait क्रम any of the 4 modem inमाला_दो (DCD,RI,DSR,CTS) to change
 * - mask passed in arg क्रम lines of पूर्णांकerest
 *   (use |'ed TIOCM_RNG/DSR/CD/CTS क्रम masking)
 * Caller should use TIOCGICOUNT to see which one it was
 */
अटल पूर्णांक
hso_रुको_modem_status(काष्ठा hso_serial *serial, अचिन्हित दीर्घ arg)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	काष्ठा uart_icount cprev, cnow;
	काष्ठा hso_tiocmget  *tiocmget;
	पूर्णांक ret;

	tiocmget = serial->tiocmget;
	अगर (!tiocmget)
		वापस -ENOENT;
	/*
	 * note the counters on entry
	 */
	spin_lock_irq(&serial->serial_lock);
	स_नकल(&cprev, &tiocmget->icount, माप(काष्ठा uart_icount));
	spin_unlock_irq(&serial->serial_lock);
	add_रुको_queue(&tiocmget->रुकोq, &रुको);
	क्रम (;;) अणु
		spin_lock_irq(&serial->serial_lock);
		स_नकल(&cnow, &tiocmget->icount, माप(काष्ठा uart_icount));
		spin_unlock_irq(&serial->serial_lock);
		set_current_state(TASK_INTERRUPTIBLE);
		अगर (((arg & TIOCM_RNG) && (cnow.rng != cprev.rng)) ||
		    ((arg & TIOCM_DSR) && (cnow.dsr != cprev.dsr)) ||
		    ((arg & TIOCM_CD)  && (cnow.dcd != cprev.dcd))) अणु
			ret = 0;
			अवरोध;
		पूर्ण
		schedule();
		/* see अगर a संकेत did it */
		अगर (संकेत_pending(current)) अणु
			ret = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		cprev = cnow;
	पूर्ण
	__set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&tiocmget->रुकोq, &रुको);

	वापस ret;
पूर्ण

/*
 * Get counter of input serial line पूर्णांकerrupts (DCD,RI,DSR,CTS)
 * Return: ग_लिखो counters to the user passed counter काष्ठा
 * NB: both 1->0 and 0->1 transitions are counted except क्रम
 *     RI where only 0->1 is counted.
 */
अटल पूर्णांक hso_get_count(काष्ठा tty_काष्ठा *tty,
		  काष्ठा serial_icounter_काष्ठा *icount)
अणु
	काष्ठा uart_icount cnow;
	काष्ठा hso_serial *serial = tty->driver_data;
	काष्ठा hso_tiocmget  *tiocmget = serial->tiocmget;

	स_रखो(icount, 0, माप(काष्ठा serial_icounter_काष्ठा));

	अगर (!tiocmget)
		 वापस -ENOENT;
	spin_lock_irq(&serial->serial_lock);
	स_नकल(&cnow, &tiocmget->icount, माप(काष्ठा uart_icount));
	spin_unlock_irq(&serial->serial_lock);

	icount->cts         = cnow.cts;
	icount->dsr         = cnow.dsr;
	icount->rng         = cnow.rng;
	icount->dcd         = cnow.dcd;
	icount->rx          = cnow.rx;
	icount->tx          = cnow.tx;
	icount->frame       = cnow.frame;
	icount->overrun     = cnow.overrun;
	icount->parity      = cnow.parity;
	icount->brk         = cnow.brk;
	icount->buf_overrun = cnow.buf_overrun;

	वापस 0;
पूर्ण


अटल पूर्णांक hso_serial_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	पूर्णांक retval;
	काष्ठा hso_serial *serial = tty->driver_data;
	काष्ठा hso_tiocmget  *tiocmget;
	u16 UART_state_biपंचांगap;

	/* sanity check */
	अगर (!serial) अणु
		hso_dbg(0x1, "no tty structures\n");
		वापस -EINVAL;
	पूर्ण
	spin_lock_irq(&serial->serial_lock);
	retval = ((serial->rts_state) ? TIOCM_RTS : 0) |
	    ((serial->dtr_state) ? TIOCM_DTR : 0);
	tiocmget = serial->tiocmget;
	अगर (tiocmget) अणु

		UART_state_biपंचांगap = le16_to_cpu(
			tiocmget->prev_UART_state_biपंचांगap);
		अगर (UART_state_biपंचांगap & B_RING_SIGNAL)
			retval |=  TIOCM_RNG;
		अगर (UART_state_biपंचांगap & B_RX_CARRIER)
			retval |=  TIOCM_CD;
		अगर (UART_state_biपंचांगap & B_TX_CARRIER)
			retval |=  TIOCM_DSR;
	पूर्ण
	spin_unlock_irq(&serial->serial_lock);
	वापस retval;
पूर्ण

अटल पूर्णांक hso_serial_tiocmset(काष्ठा tty_काष्ठा *tty,
			       अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	पूर्णांक val = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक अगर_num;
	काष्ठा hso_serial *serial = tty->driver_data;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;

	/* sanity check */
	अगर (!serial) अणु
		hso_dbg(0x1, "no tty structures\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((serial->parent->port_spec & HSO_PORT_MASK) != HSO_PORT_MODEM)
		वापस -EINVAL;

	पूर्णांकerface = serial->parent->पूर्णांकerface;
	अगर_num = पूर्णांकerface->cur_altsetting->desc.bInterfaceNumber;

	spin_lock_irqsave(&serial->serial_lock, flags);
	अगर (set & TIOCM_RTS)
		serial->rts_state = 1;
	अगर (set & TIOCM_DTR)
		serial->dtr_state = 1;

	अगर (clear & TIOCM_RTS)
		serial->rts_state = 0;
	अगर (clear & TIOCM_DTR)
		serial->dtr_state = 0;

	अगर (serial->dtr_state)
		val |= 0x01;
	अगर (serial->rts_state)
		val |= 0x02;

	spin_unlock_irqrestore(&serial->serial_lock, flags);

	वापस usb_control_msg(serial->parent->usb,
			       usb_sndctrlpipe(serial->parent->usb, 0), 0x22,
			       0x21, val, अगर_num, शून्य, 0,
			       USB_CTRL_SET_TIMEOUT);
पूर्ण

अटल पूर्णांक hso_serial_ioctl(काष्ठा tty_काष्ठा *tty,
			    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा hso_serial *serial = tty->driver_data;
	पूर्णांक ret = 0;
	hso_dbg(0x8, "IOCTL cmd: %d, arg: %ld\n", cmd, arg);

	अगर (!serial)
		वापस -ENODEV;
	चयन (cmd) अणु
	हाल TIOCMIWAIT:
		ret = hso_रुको_modem_status(serial, arg);
		अवरोध;
	शेष:
		ret = -ENOIOCTLCMD;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण


/* starts a transmit */
अटल व्योम hso_kick_transmit(काष्ठा hso_serial *serial)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक res;

	spin_lock_irqsave(&serial->serial_lock, flags);
	अगर (!serial->tx_buffer_count)
		जाओ out;

	अगर (serial->tx_urb_used)
		जाओ out;

	/* Wakeup USB पूर्णांकerface अगर necessary */
	अगर (hso_get_activity(serial->parent) == -EAGAIN)
		जाओ out;

	/* Switch poपूर्णांकers around to aव्योम स_नकल */
	swap(serial->tx_buffer, serial->tx_data);
	serial->tx_data_count = serial->tx_buffer_count;
	serial->tx_buffer_count = 0;

	/* If serial->tx_data is set, it means we चयनed buffers */
	अगर (serial->tx_data && serial->ग_लिखो_data) अणु
		res = serial->ग_लिखो_data(serial);
		अगर (res >= 0)
			serial->tx_urb_used = 1;
	पूर्ण
out:
	spin_unlock_irqrestore(&serial->serial_lock, flags);
पूर्ण

/* make a request (क्रम पढ़ोing and writing data to muxed serial port) */
अटल पूर्णांक mux_device_request(काष्ठा hso_serial *serial, u8 type, u16 port,
			      काष्ठा urb *ctrl_urb,
			      काष्ठा usb_ctrlrequest *ctrl_req,
			      u8 *ctrl_urb_data, u32 size)
अणु
	पूर्णांक result;
	पूर्णांक pipe;

	/* Sanity check */
	अगर (!serial || !ctrl_urb || !ctrl_req) अणु
		pr_err("%s: Wrong arguments\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* initialize */
	ctrl_req->wValue = 0;
	ctrl_req->wIndex = cpu_to_le16(hso_port_to_mux(port));
	ctrl_req->wLength = cpu_to_le16(size);

	अगर (type == USB_CDC_GET_ENCAPSULATED_RESPONSE) अणु
		/* Reading command */
		ctrl_req->bRequestType = USB_सूची_IN |
					 USB_TYPE_OPTION_VENDOR |
					 USB_RECIP_INTERFACE;
		ctrl_req->bRequest = USB_CDC_GET_ENCAPSULATED_RESPONSE;
		pipe = usb_rcvctrlpipe(serial->parent->usb, 0);
	पूर्ण अन्यथा अणु
		/* Writing command */
		ctrl_req->bRequestType = USB_सूची_OUT |
					 USB_TYPE_OPTION_VENDOR |
					 USB_RECIP_INTERFACE;
		ctrl_req->bRequest = USB_CDC_SEND_ENCAPSULATED_COMMAND;
		pipe = usb_sndctrlpipe(serial->parent->usb, 0);
	पूर्ण
	/* syslog */
	hso_dbg(0x2, "%s command (%02x) len: %d, port: %d\n",
		type == USB_CDC_GET_ENCAPSULATED_RESPONSE ? "Read" : "Write",
		ctrl_req->bRequestType, ctrl_req->wLength, port);

	/* Load ctrl urb */
	ctrl_urb->transfer_flags = 0;
	usb_fill_control_urb(ctrl_urb,
			     serial->parent->usb,
			     pipe,
			     (u8 *) ctrl_req,
			     ctrl_urb_data, size, ctrl_callback, serial);
	/* Send it on merry way */
	result = usb_submit_urb(ctrl_urb, GFP_ATOMIC);
	अगर (result) अणु
		dev_err(&ctrl_urb->dev->dev,
			"%s failed submit ctrl_urb %d type %d\n", __func__,
			result, type);
		वापस result;
	पूर्ण

	/* करोne */
	वापस size;
पूर्ण

/* called by पूर्णांकr_callback when पढ़ो occurs */
अटल पूर्णांक hso_mux_serial_पढ़ो(काष्ठा hso_serial *serial)
अणु
	अगर (!serial)
		वापस -EINVAL;

	/* clean data */
	स_रखो(serial->rx_data[0], 0, CTRL_URB_RX_SIZE);
	/* make the request */

	अगर (serial->num_rx_urbs != 1) अणु
		dev_err(&serial->parent->पूर्णांकerface->dev,
			"ERROR: mux'd reads with multiple buffers "
			"not possible\n");
		वापस 0;
	पूर्ण
	वापस mux_device_request(serial,
				  USB_CDC_GET_ENCAPSULATED_RESPONSE,
				  serial->parent->port_spec & HSO_PORT_MASK,
				  serial->rx_urb[0],
				  &serial->ctrl_req_rx,
				  serial->rx_data[0], serial->rx_data_length);
पूर्ण

/* used क्रम muxed serial port callback (muxed serial पढ़ो) */
अटल व्योम पूर्णांकr_callback(काष्ठा urb *urb)
अणु
	काष्ठा hso_shared_पूर्णांक *shared_पूर्णांक = urb->context;
	काष्ठा hso_serial *serial;
	अचिन्हित अक्षर *port_req;
	पूर्णांक status = urb->status;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	usb_mark_last_busy(urb->dev);

	/* sanity check */
	अगर (!shared_पूर्णांक)
		वापस;

	/* status check */
	अगर (status) अणु
		handle_usb_error(status, __func__, शून्य);
		वापस;
	पूर्ण
	hso_dbg(0x8, "--- Got intr callback 0x%02X ---\n", status);

	/* what request? */
	port_req = urb->transfer_buffer;
	hso_dbg(0x8, "port_req = 0x%.2X\n", *port_req);
	/* loop over all muxed ports to find the one sending this */
	क्रम (i = 0; i < 8; i++) अणु
		/* max 8 channels on MUX */
		अगर (*port_req & (1 << i)) अणु
			serial = get_serial_by_shared_पूर्णांक_and_type(shared_पूर्णांक,
								   (1 << i));
			अगर (serial != शून्य) अणु
				hso_dbg(0x1, "Pending read interrupt on port %d\n",
					i);
				spin_lock_irqsave(&serial->serial_lock, flags);
				अगर (serial->rx_state == RX_IDLE &&
					serial->port.count > 0) अणु
					/* Setup and send a ctrl req पढ़ो on
					 * port i */
					अगर (!serial->rx_urb_filled[0]) अणु
						serial->rx_state = RX_SENT;
						hso_mux_serial_पढ़ो(serial);
					पूर्ण अन्यथा
						serial->rx_state = RX_PENDING;
				पूर्ण अन्यथा अणु
					hso_dbg(0x1, "Already a read pending on port %d or port not open\n",
						i);
				पूर्ण
				spin_unlock_irqrestore(&serial->serial_lock,
						       flags);
			पूर्ण
		पूर्ण
	पूर्ण
	/* Resubmit पूर्णांकerrupt urb */
	hso_mux_submit_पूर्णांकr_urb(shared_पूर्णांक, urb->dev, GFP_ATOMIC);
पूर्ण

/* called क्रम writing to muxed serial port */
अटल पूर्णांक hso_mux_serial_ग_लिखो_data(काष्ठा hso_serial *serial)
अणु
	अगर (शून्य == serial)
		वापस -EINVAL;

	वापस mux_device_request(serial,
				  USB_CDC_SEND_ENCAPSULATED_COMMAND,
				  serial->parent->port_spec & HSO_PORT_MASK,
				  serial->tx_urb,
				  &serial->ctrl_req_tx,
				  serial->tx_data, serial->tx_data_count);
पूर्ण

/* ग_लिखो callback क्रम Diag and CS port */
अटल व्योम hso_std_serial_ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा hso_serial *serial = urb->context;
	पूर्णांक status = urb->status;
	अचिन्हित दीर्घ flags;

	/* sanity check */
	अगर (!serial) अणु
		hso_dbg(0x1, "serial == NULL\n");
		वापस;
	पूर्ण

	spin_lock_irqsave(&serial->serial_lock, flags);
	serial->tx_urb_used = 0;
	spin_unlock_irqrestore(&serial->serial_lock, flags);
	अगर (status) अणु
		handle_usb_error(status, __func__, serial->parent);
		वापस;
	पूर्ण
	hso_put_activity(serial->parent);
	tty_port_tty_wakeup(&serial->port);
	hso_kick_transmit(serial);

	hso_dbg(0x1, "\n");
पूर्ण

/* called क्रम writing diag or CS serial port */
अटल पूर्णांक hso_std_serial_ग_लिखो_data(काष्ठा hso_serial *serial)
अणु
	पूर्णांक count = serial->tx_data_count;
	पूर्णांक result;

	usb_fill_bulk_urb(serial->tx_urb,
			  serial->parent->usb,
			  usb_sndbulkpipe(serial->parent->usb,
					  serial->out_endp->
					  bEndpoपूर्णांकAddress & 0x7F),
			  serial->tx_data, serial->tx_data_count,
			  hso_std_serial_ग_लिखो_bulk_callback, serial);

	result = usb_submit_urb(serial->tx_urb, GFP_ATOMIC);
	अगर (result) अणु
		dev_warn(&serial->parent->usb->dev,
			 "Failed to submit urb - res %d\n", result);
		वापस result;
	पूर्ण

	वापस count;
पूर्ण

/* callback after पढ़ो or ग_लिखो on muxed serial port */
अटल व्योम ctrl_callback(काष्ठा urb *urb)
अणु
	काष्ठा hso_serial *serial = urb->context;
	काष्ठा usb_ctrlrequest *req;
	पूर्णांक status = urb->status;
	अचिन्हित दीर्घ flags;

	/* sanity check */
	अगर (!serial)
		वापस;

	spin_lock_irqsave(&serial->serial_lock, flags);
	serial->tx_urb_used = 0;
	spin_unlock_irqrestore(&serial->serial_lock, flags);
	अगर (status) अणु
		handle_usb_error(status, __func__, serial->parent);
		वापस;
	पूर्ण

	/* what request? */
	req = (काष्ठा usb_ctrlrequest *)(urb->setup_packet);
	hso_dbg(0x8, "--- Got muxed ctrl callback 0x%02X ---\n", status);
	hso_dbg(0x8, "Actual length of urb = %d\n", urb->actual_length);
	DUMP1(urb->transfer_buffer, urb->actual_length);

	अगर (req->bRequestType ==
	    (USB_सूची_IN | USB_TYPE_OPTION_VENDOR | USB_RECIP_INTERFACE)) अणु
		/* response to a पढ़ो command */
		serial->rx_urb_filled[0] = 1;
		spin_lock_irqsave(&serial->serial_lock, flags);
		put_rxbuf_data_and_resubmit_ctrl_urb(serial);
		spin_unlock_irqrestore(&serial->serial_lock, flags);
	पूर्ण अन्यथा अणु
		hso_put_activity(serial->parent);
		tty_port_tty_wakeup(&serial->port);
		/* response to a ग_लिखो command */
		hso_kick_transmit(serial);
	पूर्ण
पूर्ण

/* handle RX data क्रम serial port */
अटल पूर्णांक put_rxbuf_data(काष्ठा urb *urb, काष्ठा hso_serial *serial)
अणु
	काष्ठा tty_काष्ठा *tty;
	पूर्णांक count;

	/* Sanity check */
	अगर (urb == शून्य || serial == शून्य) अणु
		hso_dbg(0x1, "serial = NULL\n");
		वापस -2;
	पूर्ण

	tty = tty_port_tty_get(&serial->port);

	अगर (tty && tty_throttled(tty)) अणु
		tty_kref_put(tty);
		वापस -1;
	पूर्ण

	/* Push data to tty */
	hso_dbg(0x1, "data to push to tty\n");
	count = tty_buffer_request_room(&serial->port, urb->actual_length);
	अगर (count >= urb->actual_length) अणु
		tty_insert_flip_string(&serial->port, urb->transfer_buffer,
				       urb->actual_length);
		tty_flip_buffer_push(&serial->port);
	पूर्ण अन्यथा अणु
		dev_warn(&serial->parent->usb->dev,
			 "dropping data, %d bytes lost\n", urb->actual_length);
	पूर्ण

	tty_kref_put(tty);

	serial->rx_urb_filled[hso_urb_to_index(serial, urb)] = 0;

	वापस 0;
पूर्ण


/* Base driver functions */

अटल व्योम hso_log_port(काष्ठा hso_device *hso_dev)
अणु
	अक्षर *port_type;
	अक्षर port_dev[20];

	चयन (hso_dev->port_spec & HSO_PORT_MASK) अणु
	हाल HSO_PORT_CONTROL:
		port_type = "Control";
		अवरोध;
	हाल HSO_PORT_APP:
		port_type = "Application";
		अवरोध;
	हाल HSO_PORT_GPS:
		port_type = "GPS";
		अवरोध;
	हाल HSO_PORT_GPS_CONTROL:
		port_type = "GPS control";
		अवरोध;
	हाल HSO_PORT_APP2:
		port_type = "Application2";
		अवरोध;
	हाल HSO_PORT_PCSC:
		port_type = "PCSC";
		अवरोध;
	हाल HSO_PORT_DIAG:
		port_type = "Diagnostic";
		अवरोध;
	हाल HSO_PORT_DIAG2:
		port_type = "Diagnostic2";
		अवरोध;
	हाल HSO_PORT_MODEM:
		port_type = "Modem";
		अवरोध;
	हाल HSO_PORT_NETWORK:
		port_type = "Network";
		अवरोध;
	शेष:
		port_type = "Unknown";
		अवरोध;
	पूर्ण
	अगर ((hso_dev->port_spec & HSO_PORT_MASK) == HSO_PORT_NETWORK) अणु
		प्र_लिखो(port_dev, "%s", dev2net(hso_dev)->net->name);
	पूर्ण अन्यथा
		प्र_लिखो(port_dev, "/dev/%s%d", tty_filename,
			dev2ser(hso_dev)->minor);

	dev_dbg(&hso_dev->पूर्णांकerface->dev, "HSO: Found %s port %s\n",
		port_type, port_dev);
पूर्ण

अटल पूर्णांक hso_start_net_device(काष्ठा hso_device *hso_dev)
अणु
	पूर्णांक i, result = 0;
	काष्ठा hso_net *hso_net = dev2net(hso_dev);

	अगर (!hso_net)
		वापस -ENODEV;

	/* send URBs क्रम all पढ़ो buffers */
	क्रम (i = 0; i < MUX_BULK_RX_BUF_COUNT; i++) अणु

		/* Prep a receive URB */
		usb_fill_bulk_urb(hso_net->mux_bulk_rx_urb_pool[i],
				  hso_dev->usb,
				  usb_rcvbulkpipe(hso_dev->usb,
						  hso_net->in_endp->
						  bEndpoपूर्णांकAddress & 0x7F),
				  hso_net->mux_bulk_rx_buf_pool[i],
				  MUX_BULK_RX_BUF_SIZE, पढ़ो_bulk_callback,
				  hso_net);

		/* Put it out there so the device can send us stuff */
		result = usb_submit_urb(hso_net->mux_bulk_rx_urb_pool[i],
					GFP_NOIO);
		अगर (result)
			dev_warn(&hso_dev->usb->dev,
				"%s failed mux_bulk_rx_urb[%d] %d\n", __func__,
				i, result);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक hso_stop_net_device(काष्ठा hso_device *hso_dev)
अणु
	पूर्णांक i;
	काष्ठा hso_net *hso_net = dev2net(hso_dev);

	अगर (!hso_net)
		वापस -ENODEV;

	क्रम (i = 0; i < MUX_BULK_RX_BUF_COUNT; i++) अणु
		अगर (hso_net->mux_bulk_rx_urb_pool[i])
			usb_समाप्त_urb(hso_net->mux_bulk_rx_urb_pool[i]);

	पूर्ण
	अगर (hso_net->mux_bulk_tx_urb)
		usb_समाप्त_urb(hso_net->mux_bulk_tx_urb);

	वापस 0;
पूर्ण

अटल पूर्णांक hso_start_serial_device(काष्ठा hso_device *hso_dev, gfp_t flags)
अणु
	पूर्णांक i, result = 0;
	काष्ठा hso_serial *serial = dev2ser(hso_dev);

	अगर (!serial)
		वापस -ENODEV;

	/* If it is not the MUX port fill in and submit a bulk urb (alपढ़ोy
	 * allocated in hso_serial_start) */
	अगर (!(serial->parent->port_spec & HSO_INTF_MUX)) अणु
		क्रम (i = 0; i < serial->num_rx_urbs; i++) अणु
			usb_fill_bulk_urb(serial->rx_urb[i],
					  serial->parent->usb,
					  usb_rcvbulkpipe(serial->parent->usb,
							  serial->in_endp->
							  bEndpoपूर्णांकAddress &
							  0x7F),
					  serial->rx_data[i],
					  serial->rx_data_length,
					  hso_std_serial_पढ़ो_bulk_callback,
					  serial);
			result = usb_submit_urb(serial->rx_urb[i], flags);
			अगर (result) अणु
				dev_warn(&serial->parent->usb->dev,
					 "Failed to submit urb - res %d\n",
					 result);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		mutex_lock(&serial->shared_पूर्णांक->shared_पूर्णांक_lock);
		अगर (!serial->shared_पूर्णांक->use_count) अणु
			result =
			    hso_mux_submit_पूर्णांकr_urb(serial->shared_पूर्णांक,
						    hso_dev->usb, flags);
		पूर्ण
		serial->shared_पूर्णांक->use_count++;
		mutex_unlock(&serial->shared_पूर्णांक->shared_पूर्णांक_lock);
	पूर्ण
	अगर (serial->tiocmget)
		tiocmget_submit_urb(serial,
				    serial->tiocmget,
				    serial->parent->usb);
	वापस result;
पूर्ण

अटल पूर्णांक hso_stop_serial_device(काष्ठा hso_device *hso_dev)
अणु
	पूर्णांक i;
	काष्ठा hso_serial *serial = dev2ser(hso_dev);
	काष्ठा hso_tiocmget  *tiocmget;

	अगर (!serial)
		वापस -ENODEV;

	क्रम (i = 0; i < serial->num_rx_urbs; i++) अणु
		अगर (serial->rx_urb[i]) अणु
			usb_समाप्त_urb(serial->rx_urb[i]);
			serial->rx_urb_filled[i] = 0;
		पूर्ण
	पूर्ण
	serial->curr_rx_urb_idx = 0;

	अगर (serial->tx_urb)
		usb_समाप्त_urb(serial->tx_urb);

	अगर (serial->shared_पूर्णांक) अणु
		mutex_lock(&serial->shared_पूर्णांक->shared_पूर्णांक_lock);
		अगर (serial->shared_पूर्णांक->use_count &&
		    (--serial->shared_पूर्णांक->use_count == 0)) अणु
			काष्ठा urb *urb;

			urb = serial->shared_पूर्णांक->shared_पूर्णांकr_urb;
			अगर (urb)
				usb_समाप्त_urb(urb);
		पूर्ण
		mutex_unlock(&serial->shared_पूर्णांक->shared_पूर्णांक_lock);
	पूर्ण
	tiocmget = serial->tiocmget;
	अगर (tiocmget) अणु
		wake_up_पूर्णांकerruptible(&tiocmget->रुकोq);
		usb_समाप्त_urb(tiocmget->urb);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hso_serial_tty_unरेजिस्टर(काष्ठा hso_serial *serial)
अणु
	tty_unरेजिस्टर_device(tty_drv, serial->minor);
	release_minor(serial);
पूर्ण

अटल व्योम hso_serial_common_मुक्त(काष्ठा hso_serial *serial)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < serial->num_rx_urbs; i++) अणु
		/* unlink and मुक्त RX URB */
		usb_मुक्त_urb(serial->rx_urb[i]);
		/* मुक्त the RX buffer */
		kमुक्त(serial->rx_data[i]);
	पूर्ण

	/* unlink and मुक्त TX URB */
	usb_मुक्त_urb(serial->tx_urb);
	kमुक्त(serial->tx_buffer);
	kमुक्त(serial->tx_data);
	tty_port_destroy(&serial->port);
पूर्ण

अटल पूर्णांक hso_serial_common_create(काष्ठा hso_serial *serial, पूर्णांक num_urbs,
				    पूर्णांक rx_size, पूर्णांक tx_size)
अणु
	पूर्णांक i;

	tty_port_init(&serial->port);

	अगर (obtain_minor(serial))
		जाओ निकास2;

	/* रेजिस्टर our minor number */
	serial->parent->dev = tty_port_रेजिस्टर_device_attr(&serial->port,
			tty_drv, serial->minor, &serial->parent->पूर्णांकerface->dev,
			serial->parent, hso_serial_dev_groups);
	अगर (IS_ERR(serial->parent->dev)) अणु
		release_minor(serial);
		जाओ निकास2;
	पूर्ण

	serial->magic = HSO_SERIAL_MAGIC;
	spin_lock_init(&serial->serial_lock);
	serial->num_rx_urbs = num_urbs;

	/* RX, allocate urb and initialize */

	/* prepare our RX buffer */
	serial->rx_data_length = rx_size;
	क्रम (i = 0; i < serial->num_rx_urbs; i++) अणु
		serial->rx_urb[i] = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!serial->rx_urb[i])
			जाओ निकास;
		serial->rx_urb[i]->transfer_buffer = शून्य;
		serial->rx_urb[i]->transfer_buffer_length = 0;
		serial->rx_data[i] = kzalloc(serial->rx_data_length,
					     GFP_KERNEL);
		अगर (!serial->rx_data[i])
			जाओ निकास;
	पूर्ण

	/* TX, allocate urb and initialize */
	serial->tx_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!serial->tx_urb)
		जाओ निकास;
	serial->tx_urb->transfer_buffer = शून्य;
	serial->tx_urb->transfer_buffer_length = 0;
	/* prepare our TX buffer */
	serial->tx_data_count = 0;
	serial->tx_buffer_count = 0;
	serial->tx_data_length = tx_size;
	serial->tx_data = kzalloc(serial->tx_data_length, GFP_KERNEL);
	अगर (!serial->tx_data)
		जाओ निकास;

	serial->tx_buffer = kzalloc(serial->tx_data_length, GFP_KERNEL);
	अगर (!serial->tx_buffer)
		जाओ निकास;

	वापस 0;
निकास:
	hso_serial_tty_unरेजिस्टर(serial);
निकास2:
	hso_serial_common_मुक्त(serial);
	वापस -1;
पूर्ण

/* Creates a general hso device */
अटल काष्ठा hso_device *hso_create_device(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
					    पूर्णांक port_spec)
अणु
	काष्ठा hso_device *hso_dev;

	hso_dev = kzalloc(माप(*hso_dev), GFP_ATOMIC);
	अगर (!hso_dev)
		वापस शून्य;

	hso_dev->port_spec = port_spec;
	hso_dev->usb = पूर्णांकerface_to_usbdev(पूर्णांकf);
	hso_dev->पूर्णांकerface = पूर्णांकf;
	kref_init(&hso_dev->ref);
	mutex_init(&hso_dev->mutex);

	INIT_WORK(&hso_dev->async_get_पूर्णांकf, async_get_पूर्णांकf);
	INIT_WORK(&hso_dev->async_put_पूर्णांकf, async_put_पूर्णांकf);

	वापस hso_dev;
पूर्ण

/* Removes a network device in the network device table */
अटल पूर्णांक हटाओ_net_device(काष्ठा hso_device *hso_dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < HSO_MAX_NET_DEVICES; i++) अणु
		अगर (network_table[i] == hso_dev) अणु
			network_table[i] = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == HSO_MAX_NET_DEVICES)
		वापस -1;
	वापस 0;
पूर्ण

/* Frees our network device */
अटल व्योम hso_मुक्त_net_device(काष्ठा hso_device *hso_dev, bool bailout)
अणु
	पूर्णांक i;
	काष्ठा hso_net *hso_net = dev2net(hso_dev);

	अगर (!hso_net)
		वापस;

	हटाओ_net_device(hso_net->parent);

	अगर (hso_net->net)
		unरेजिस्टर_netdev(hso_net->net);

	/* start मुक्तing */
	क्रम (i = 0; i < MUX_BULK_RX_BUF_COUNT; i++) अणु
		usb_मुक्त_urb(hso_net->mux_bulk_rx_urb_pool[i]);
		kमुक्त(hso_net->mux_bulk_rx_buf_pool[i]);
		hso_net->mux_bulk_rx_buf_pool[i] = शून्य;
	पूर्ण
	usb_मुक्त_urb(hso_net->mux_bulk_tx_urb);
	kमुक्त(hso_net->mux_bulk_tx_buf);
	hso_net->mux_bulk_tx_buf = शून्य;

	अगर (hso_net->net && !bailout)
		मुक्त_netdev(hso_net->net);

	kमुक्त(hso_dev);
पूर्ण

अटल स्थिर काष्ठा net_device_ops hso_netdev_ops = अणु
	.nकरो_खोलो	= hso_net_खोलो,
	.nकरो_stop	= hso_net_बंद,
	.nकरो_start_xmit = hso_net_start_xmit,
	.nकरो_tx_समयout = hso_net_tx_समयout,
पूर्ण;

/* initialize the network पूर्णांकerface */
अटल व्योम hso_net_init(काष्ठा net_device *net)
अणु
	काष्ठा hso_net *hso_net = netdev_priv(net);

	hso_dbg(0x1, "sizeof hso_net is %zu\n", माप(*hso_net));

	/* fill in the other fields */
	net->netdev_ops = &hso_netdev_ops;
	net->watchकरोg_समयo = HSO_NET_TX_TIMEOUT;
	net->flags = IFF_POINTOPOINT | IFF_NOARP | IFF_MULTICAST;
	net->type = ARPHRD_NONE;
	net->mtu = DEFAULT_MTU - 14;
	net->tx_queue_len = 10;
	net->ethtool_ops = &ops;

	/* and initialize the semaphore */
	spin_lock_init(&hso_net->net_lock);
पूर्ण

/* Adds a network device in the network device table */
अटल पूर्णांक add_net_device(काष्ठा hso_device *hso_dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < HSO_MAX_NET_DEVICES; i++) अणु
		अगर (network_table[i] == शून्य) अणु
			network_table[i] = hso_dev;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == HSO_MAX_NET_DEVICES)
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक hso_rfसमाप्त_set_block(व्योम *data, bool blocked)
अणु
	काष्ठा hso_device *hso_dev = data;
	पूर्णांक enabled = !blocked;
	पूर्णांक rv;

	mutex_lock(&hso_dev->mutex);
	अगर (hso_dev->usb_gone)
		rv = 0;
	अन्यथा
		rv = usb_control_msg(hso_dev->usb, usb_sndctrlpipe(hso_dev->usb, 0),
				       enabled ? 0x82 : 0x81, 0x40, 0, 0, शून्य, 0,
				       USB_CTRL_SET_TIMEOUT);
	mutex_unlock(&hso_dev->mutex);
	वापस rv;
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops hso_rfसमाप्त_ops = अणु
	.set_block = hso_rfसमाप्त_set_block,
पूर्ण;

/* Creates and sets up everything क्रम rfसमाप्त */
अटल व्योम hso_create_rfसमाप्त(काष्ठा hso_device *hso_dev,
			     काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा hso_net *hso_net = dev2net(hso_dev);
	काष्ठा device *dev = &hso_net->net->dev;
	अटल u32 rfसमाप्त_counter;

	snम_लिखो(hso_net->name, माप(hso_net->name), "hso-%d",
		 rfसमाप्त_counter++);

	hso_net->rfसमाप्त = rfसमाप्त_alloc(hso_net->name,
				       &पूर्णांकerface_to_usbdev(पूर्णांकerface)->dev,
				       RFKILL_TYPE_WWAN,
				       &hso_rfसमाप्त_ops, hso_dev);
	अगर (!hso_net->rfसमाप्त)
		वापस;

	अगर (rfसमाप्त_रेजिस्टर(hso_net->rfसमाप्त) < 0) अणु
		rfसमाप्त_destroy(hso_net->rfसमाप्त);
		hso_net->rfसमाप्त = शून्य;
		dev_err(dev, "%s - Failed to register rfkill\n", __func__);
		वापस;
	पूर्ण
पूर्ण

अटल काष्ठा device_type hso_type = अणु
	.name	= "wwan",
पूर्ण;

/* Creates our network device */
अटल काष्ठा hso_device *hso_create_net_device(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
						पूर्णांक port_spec)
अणु
	पूर्णांक result, i;
	काष्ठा net_device *net;
	काष्ठा hso_net *hso_net;
	काष्ठा hso_device *hso_dev;

	hso_dev = hso_create_device(पूर्णांकerface, port_spec);
	अगर (!hso_dev)
		वापस शून्य;

	/* allocate our network device, then we can put in our निजी data */
	/* call hso_net_init to करो the basic initialization */
	net = alloc_netdev(माप(काष्ठा hso_net), "hso%d", NET_NAME_UNKNOWN,
			   hso_net_init);
	अगर (!net) अणु
		dev_err(&पूर्णांकerface->dev, "Unable to create ethernet device\n");
		जाओ निकास;
	पूर्ण

	hso_net = netdev_priv(net);

	hso_dev->port_data.dev_net = hso_net;
	hso_net->net = net;
	hso_net->parent = hso_dev;

	hso_net->in_endp = hso_get_ep(पूर्णांकerface, USB_ENDPOINT_XFER_BULK,
				      USB_सूची_IN);
	अगर (!hso_net->in_endp) अणु
		dev_err(&पूर्णांकerface->dev, "Can't find BULK IN endpoint\n");
		जाओ निकास;
	पूर्ण
	hso_net->out_endp = hso_get_ep(पूर्णांकerface, USB_ENDPOINT_XFER_BULK,
				       USB_सूची_OUT);
	अगर (!hso_net->out_endp) अणु
		dev_err(&पूर्णांकerface->dev, "Can't find BULK OUT endpoint\n");
		जाओ निकास;
	पूर्ण
	SET_NETDEV_DEV(net, &पूर्णांकerface->dev);
	SET_NETDEV_DEVTYPE(net, &hso_type);

	/* start allocating */
	क्रम (i = 0; i < MUX_BULK_RX_BUF_COUNT; i++) अणु
		hso_net->mux_bulk_rx_urb_pool[i] = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!hso_net->mux_bulk_rx_urb_pool[i])
			जाओ निकास;
		hso_net->mux_bulk_rx_buf_pool[i] = kzalloc(MUX_BULK_RX_BUF_SIZE,
							   GFP_KERNEL);
		अगर (!hso_net->mux_bulk_rx_buf_pool[i])
			जाओ निकास;
	पूर्ण
	hso_net->mux_bulk_tx_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!hso_net->mux_bulk_tx_urb)
		जाओ निकास;
	hso_net->mux_bulk_tx_buf = kzalloc(MUX_BULK_TX_BUF_SIZE, GFP_KERNEL);
	अगर (!hso_net->mux_bulk_tx_buf)
		जाओ निकास;

	add_net_device(hso_dev);

	/* रेजिस्टरing our net device */
	result = रेजिस्टर_netdev(net);
	अगर (result) अणु
		dev_err(&पूर्णांकerface->dev, "Failed to register device\n");
		जाओ निकास;
	पूर्ण

	hso_log_port(hso_dev);

	hso_create_rfसमाप्त(hso_dev, पूर्णांकerface);

	वापस hso_dev;
निकास:
	hso_मुक्त_net_device(hso_dev, true);
	वापस शून्य;
पूर्ण

अटल व्योम hso_मुक्त_tiomget(काष्ठा hso_serial *serial)
अणु
	काष्ठा hso_tiocmget *tiocmget;
	अगर (!serial)
		वापस;
	tiocmget = serial->tiocmget;
	अगर (tiocmget) अणु
		usb_मुक्त_urb(tiocmget->urb);
		tiocmget->urb = शून्य;
		serial->tiocmget = शून्य;
		kमुक्त(tiocmget->serial_state_notअगरication);
		tiocmget->serial_state_notअगरication = शून्य;
		kमुक्त(tiocmget);
	पूर्ण
पूर्ण

/* Frees an AT channel ( goes क्रम both mux and non-mux ) */
अटल व्योम hso_मुक्त_serial_device(काष्ठा hso_device *hso_dev)
अणु
	काष्ठा hso_serial *serial = dev2ser(hso_dev);

	अगर (!serial)
		वापस;

	hso_serial_common_मुक्त(serial);

	अगर (serial->shared_पूर्णांक) अणु
		mutex_lock(&serial->shared_पूर्णांक->shared_पूर्णांक_lock);
		अगर (--serial->shared_पूर्णांक->ref_count == 0)
			hso_मुक्त_shared_पूर्णांक(serial->shared_पूर्णांक);
		अन्यथा
			mutex_unlock(&serial->shared_पूर्णांक->shared_पूर्णांक_lock);
	पूर्ण
	hso_मुक्त_tiomget(serial);
	kमुक्त(serial);
	kमुक्त(hso_dev);
पूर्ण

/* Creates a bulk AT channel */
अटल काष्ठा hso_device *hso_create_bulk_serial_device(
			काष्ठा usb_पूर्णांकerface *पूर्णांकerface, पूर्णांक port)
अणु
	काष्ठा hso_device *hso_dev;
	काष्ठा hso_serial *serial;
	पूर्णांक num_urbs;
	काष्ठा hso_tiocmget *tiocmget;

	hso_dev = hso_create_device(पूर्णांकerface, port);
	अगर (!hso_dev)
		वापस शून्य;

	serial = kzalloc(माप(*serial), GFP_KERNEL);
	अगर (!serial)
		जाओ निकास;

	serial->parent = hso_dev;
	hso_dev->port_data.dev_serial = serial;

	अगर ((port & HSO_PORT_MASK) == HSO_PORT_MODEM) अणु
		num_urbs = 2;
		serial->tiocmget = kzalloc(माप(काष्ठा hso_tiocmget),
					   GFP_KERNEL);
		अगर (!serial->tiocmget)
			जाओ निकास;
		serial->tiocmget->serial_state_notअगरication
			= kzalloc(माप(काष्ठा hso_serial_state_notअगरication),
					   GFP_KERNEL);
		अगर (!serial->tiocmget->serial_state_notअगरication)
			जाओ निकास;
		tiocmget = serial->tiocmget;
		tiocmget->endp = hso_get_ep(पूर्णांकerface,
					    USB_ENDPOINT_XFER_INT,
					    USB_सूची_IN);
		अगर (!tiocmget->endp) अणु
			dev_err(&पूर्णांकerface->dev, "Failed to find INT IN ep\n");
			जाओ निकास;
		पूर्ण

		tiocmget->urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!tiocmget->urb)
			जाओ निकास;

		mutex_init(&tiocmget->mutex);
		init_रुकोqueue_head(&tiocmget->रुकोq);
	पूर्ण अन्यथा अणु
		num_urbs = 1;
	पूर्ण

	अगर (hso_serial_common_create(serial, num_urbs, BULK_URB_RX_SIZE,
				     BULK_URB_TX_SIZE))
		जाओ निकास;

	serial->in_endp = hso_get_ep(पूर्णांकerface, USB_ENDPOINT_XFER_BULK,
				     USB_सूची_IN);
	अगर (!serial->in_endp) अणु
		dev_err(&पूर्णांकerface->dev, "Failed to find BULK IN ep\n");
		जाओ निकास2;
	पूर्ण

	अगर (!
	    (serial->out_endp =
	     hso_get_ep(पूर्णांकerface, USB_ENDPOINT_XFER_BULK, USB_सूची_OUT))) अणु
		dev_err(&पूर्णांकerface->dev, "Failed to find BULK OUT ep\n");
		जाओ निकास2;
	पूर्ण

	serial->ग_लिखो_data = hso_std_serial_ग_लिखो_data;

	/* setup the proc dirs and files अगर needed */
	hso_log_port(hso_dev);

	/* करोne, वापस it */
	वापस hso_dev;

निकास2:
	hso_serial_tty_unरेजिस्टर(serial);
	hso_serial_common_मुक्त(serial);
निकास:
	hso_मुक्त_tiomget(serial);
	kमुक्त(serial);
	kमुक्त(hso_dev);
	वापस शून्य;
पूर्ण

/* Creates a multiplexed AT channel */
अटल
काष्ठा hso_device *hso_create_mux_serial_device(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
						पूर्णांक port,
						काष्ठा hso_shared_पूर्णांक *mux)
अणु
	काष्ठा hso_device *hso_dev;
	काष्ठा hso_serial *serial;
	पूर्णांक port_spec;

	port_spec = HSO_INTF_MUX;
	port_spec &= ~HSO_PORT_MASK;

	port_spec |= hso_mux_to_port(port);
	अगर ((port_spec & HSO_PORT_MASK) == HSO_PORT_NO_PORT)
		वापस शून्य;

	hso_dev = hso_create_device(पूर्णांकerface, port_spec);
	अगर (!hso_dev)
		वापस शून्य;

	serial = kzalloc(माप(*serial), GFP_KERNEL);
	अगर (!serial)
		जाओ निकास;

	hso_dev->port_data.dev_serial = serial;
	serial->parent = hso_dev;

	अगर (hso_serial_common_create
	    (serial, 1, CTRL_URB_RX_SIZE, CTRL_URB_TX_SIZE))
		जाओ निकास;

	serial->tx_data_length--;
	serial->ग_लिखो_data = hso_mux_serial_ग_लिखो_data;

	serial->shared_पूर्णांक = mux;
	mutex_lock(&serial->shared_पूर्णांक->shared_पूर्णांक_lock);
	serial->shared_पूर्णांक->ref_count++;
	mutex_unlock(&serial->shared_पूर्णांक->shared_पूर्णांक_lock);

	/* setup the proc dirs and files अगर needed */
	hso_log_port(hso_dev);

	/* करोne, वापस it */
	वापस hso_dev;

निकास:
	अगर (serial) अणु
		tty_unरेजिस्टर_device(tty_drv, serial->minor);
		kमुक्त(serial);
	पूर्ण
	kमुक्त(hso_dev);
	वापस शून्य;

पूर्ण

अटल व्योम hso_मुक्त_shared_पूर्णांक(काष्ठा hso_shared_पूर्णांक *mux)
अणु
	usb_मुक्त_urb(mux->shared_पूर्णांकr_urb);
	kमुक्त(mux->shared_पूर्णांकr_buf);
	mutex_unlock(&mux->shared_पूर्णांक_lock);
	kमुक्त(mux);
पूर्ण

अटल
काष्ठा hso_shared_पूर्णांक *hso_create_shared_पूर्णांक(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा hso_shared_पूर्णांक *mux = kzalloc(माप(*mux), GFP_KERNEL);

	अगर (!mux)
		वापस शून्य;

	mux->पूर्णांकr_endp = hso_get_ep(पूर्णांकerface, USB_ENDPOINT_XFER_INT,
				    USB_सूची_IN);
	अगर (!mux->पूर्णांकr_endp) अणु
		dev_err(&पूर्णांकerface->dev, "Can't find INT IN endpoint\n");
		जाओ निकास;
	पूर्ण

	mux->shared_पूर्णांकr_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!mux->shared_पूर्णांकr_urb)
		जाओ निकास;
	mux->shared_पूर्णांकr_buf =
		kzalloc(le16_to_cpu(mux->पूर्णांकr_endp->wMaxPacketSize),
			GFP_KERNEL);
	अगर (!mux->shared_पूर्णांकr_buf)
		जाओ निकास;

	mutex_init(&mux->shared_पूर्णांक_lock);

	वापस mux;

निकास:
	kमुक्त(mux->shared_पूर्णांकr_buf);
	usb_मुक्त_urb(mux->shared_पूर्णांकr_urb);
	kमुक्त(mux);
	वापस शून्य;
पूर्ण

/* Gets the port spec क्रम a certain पूर्णांकerface */
अटल पूर्णांक hso_get_config_data(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	u8 *config_data = kदो_स्मृति(17, GFP_KERNEL);
	u32 अगर_num = पूर्णांकerface->cur_altsetting->desc.bInterfaceNumber;
	s32 result;

	अगर (!config_data)
		वापस -ENOMEM;
	अगर (usb_control_msg(usbdev, usb_rcvctrlpipe(usbdev, 0),
			    0x86, 0xC0, 0, 0, config_data, 17,
			    USB_CTRL_SET_TIMEOUT) != 0x11) अणु
		kमुक्त(config_data);
		वापस -EIO;
	पूर्ण

	/* check अगर we have a valid पूर्णांकerface */
	अगर (अगर_num > 16) अणु
		kमुक्त(config_data);
		वापस -EINVAL;
	पूर्ण

	चयन (config_data[अगर_num]) अणु
	हाल 0x0:
		result = 0;
		अवरोध;
	हाल 0x1:
		result = HSO_PORT_DIAG;
		अवरोध;
	हाल 0x2:
		result = HSO_PORT_GPS;
		अवरोध;
	हाल 0x3:
		result = HSO_PORT_GPS_CONTROL;
		अवरोध;
	हाल 0x4:
		result = HSO_PORT_APP;
		अवरोध;
	हाल 0x5:
		result = HSO_PORT_APP2;
		अवरोध;
	हाल 0x6:
		result = HSO_PORT_CONTROL;
		अवरोध;
	हाल 0x7:
		result = HSO_PORT_NETWORK;
		अवरोध;
	हाल 0x8:
		result = HSO_PORT_MODEM;
		अवरोध;
	हाल 0x9:
		result = HSO_PORT_MSD;
		अवरोध;
	हाल 0xa:
		result = HSO_PORT_PCSC;
		अवरोध;
	हाल 0xb:
		result = HSO_PORT_VOICE;
		अवरोध;
	शेष:
		result = 0;
	पूर्ण

	अगर (result)
		result |= HSO_INTF_BULK;

	अगर (config_data[16] & 0x1)
		result |= HSO_INFO_CRC_BUG;

	kमुक्त(config_data);
	वापस result;
पूर्ण

/* called once क्रम each पूर्णांकerface upon device insertion */
अटल पूर्णांक hso_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		     स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक mux, i, अगर_num, port_spec;
	अचिन्हित अक्षर port_mask;
	काष्ठा hso_device *hso_dev = शून्य;
	काष्ठा hso_shared_पूर्णांक *shared_पूर्णांक;
	काष्ठा hso_device *पंचांगp_dev = शून्य;

	अगर (पूर्णांकerface->cur_altsetting->desc.bInterfaceClass != 0xFF) अणु
		dev_err(&पूर्णांकerface->dev, "Not our interface\n");
		वापस -ENODEV;
	पूर्ण

	अगर_num = पूर्णांकerface->cur_altsetting->desc.bInterfaceNumber;

	/* Get the पूर्णांकerface/port specअगरication from either driver_info or from
	 * the device itself */
	अगर (id->driver_info) अणु
		/* अगर_num is controlled by the device, driver_info is a 0 terminated
		 * array. Make sure, the access is in bounds! */
		क्रम (i = 0; i <= अगर_num; ++i)
			अगर (((u32 *)(id->driver_info))[i] == 0)
				जाओ निकास;
		port_spec = ((u32 *)(id->driver_info))[अगर_num];
	पूर्ण अन्यथा अणु
		port_spec = hso_get_config_data(पूर्णांकerface);
		अगर (port_spec < 0)
			जाओ निकास;
	पूर्ण

	/* Check अगर we need to चयन to alt पूर्णांकerfaces prior to port
	 * configuration */
	अगर (पूर्णांकerface->num_altsetting > 1)
		usb_set_पूर्णांकerface(पूर्णांकerface_to_usbdev(पूर्णांकerface), अगर_num, 1);
	पूर्णांकerface->needs_remote_wakeup = 1;

	/* Allocate new hso device(s) */
	चयन (port_spec & HSO_INTF_MASK) अणु
	हाल HSO_INTF_MUX:
		अगर ((port_spec & HSO_PORT_MASK) == HSO_PORT_NETWORK) अणु
			/* Create the network device */
			अगर (!disable_net) अणु
				hso_dev = hso_create_net_device(पूर्णांकerface,
								port_spec);
				अगर (!hso_dev)
					जाओ निकास;
				पंचांगp_dev = hso_dev;
			पूर्ण
		पूर्ण

		अगर (hso_get_mux_ports(पूर्णांकerface, &port_mask))
			/* TODO: de-allocate everything */
			जाओ निकास;

		shared_पूर्णांक = hso_create_shared_पूर्णांक(पूर्णांकerface);
		अगर (!shared_पूर्णांक)
			जाओ निकास;

		क्रम (i = 1, mux = 0; i < 0x100; i = i << 1, mux++) अणु
			अगर (port_mask & i) अणु
				hso_dev = hso_create_mux_serial_device(
						पूर्णांकerface, i, shared_पूर्णांक);
				अगर (!hso_dev)
					जाओ निकास;
			पूर्ण
		पूर्ण

		अगर (पंचांगp_dev)
			hso_dev = पंचांगp_dev;
		अवरोध;

	हाल HSO_INTF_BULK:
		/* It's a regular bulk पूर्णांकerface */
		अगर ((port_spec & HSO_PORT_MASK) == HSO_PORT_NETWORK) अणु
			अगर (!disable_net)
				hso_dev =
				    hso_create_net_device(पूर्णांकerface, port_spec);
		पूर्ण अन्यथा अणु
			hso_dev =
			    hso_create_bulk_serial_device(पूर्णांकerface, port_spec);
		पूर्ण
		अगर (!hso_dev)
			जाओ निकास;
		अवरोध;
	शेष:
		जाओ निकास;
	पूर्ण

	/* save our data poपूर्णांकer in this device */
	usb_set_पूर्णांकfdata(पूर्णांकerface, hso_dev);

	/* करोne */
	वापस 0;
निकास:
	hso_मुक्त_पूर्णांकerface(पूर्णांकerface);
	वापस -ENODEV;
पूर्ण

/* device हटाओd, cleaning up */
अटल व्योम hso_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	hso_मुक्त_पूर्णांकerface(पूर्णांकerface);

	/* हटाओ reference of our निजी data */
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
पूर्ण

अटल व्योम async_get_पूर्णांकf(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा hso_device *hso_dev =
	    container_of(data, काष्ठा hso_device, async_get_पूर्णांकf);
	usb_स्वतःpm_get_पूर्णांकerface(hso_dev->पूर्णांकerface);
पूर्ण

अटल व्योम async_put_पूर्णांकf(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा hso_device *hso_dev =
	    container_of(data, काष्ठा hso_device, async_put_पूर्णांकf);
	usb_स्वतःpm_put_पूर्णांकerface(hso_dev->पूर्णांकerface);
पूर्ण

अटल पूर्णांक hso_get_activity(काष्ठा hso_device *hso_dev)
अणु
	अगर (hso_dev->usb->state == USB_STATE_SUSPENDED) अणु
		अगर (!hso_dev->is_active) अणु
			hso_dev->is_active = 1;
			schedule_work(&hso_dev->async_get_पूर्णांकf);
		पूर्ण
	पूर्ण

	अगर (hso_dev->usb->state != USB_STATE_CONFIGURED)
		वापस -EAGAIN;

	usb_mark_last_busy(hso_dev->usb);

	वापस 0;
पूर्ण

अटल पूर्णांक hso_put_activity(काष्ठा hso_device *hso_dev)
अणु
	अगर (hso_dev->usb->state != USB_STATE_SUSPENDED) अणु
		अगर (hso_dev->is_active) अणु
			hso_dev->is_active = 0;
			schedule_work(&hso_dev->async_put_पूर्णांकf);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण
	hso_dev->is_active = 0;
	वापस 0;
पूर्ण

/* called by kernel when we need to suspend device */
अटल पूर्णांक hso_suspend(काष्ठा usb_पूर्णांकerface *अगरace, pm_message_t message)
अणु
	पूर्णांक i, result;

	/* Stop all serial ports */
	क्रम (i = 0; i < HSO_SERIAL_TTY_MINORS; i++) अणु
		अगर (serial_table[i] && (serial_table[i]->पूर्णांकerface == अगरace)) अणु
			result = hso_stop_serial_device(serial_table[i]);
			अगर (result)
				जाओ out;
		पूर्ण
	पूर्ण

	/* Stop all network ports */
	क्रम (i = 0; i < HSO_MAX_NET_DEVICES; i++) अणु
		अगर (network_table[i] &&
		    (network_table[i]->पूर्णांकerface == अगरace)) अणु
			result = hso_stop_net_device(network_table[i]);
			अगर (result)
				जाओ out;
		पूर्ण
	पूर्ण

out:
	वापस 0;
पूर्ण

/* called by kernel when we need to resume device */
अटल पूर्णांक hso_resume(काष्ठा usb_पूर्णांकerface *अगरace)
अणु
	पूर्णांक i, result = 0;
	काष्ठा hso_net *hso_net;

	/* Start all serial ports */
	क्रम (i = 0; i < HSO_SERIAL_TTY_MINORS; i++) अणु
		अगर (serial_table[i] && (serial_table[i]->पूर्णांकerface == अगरace)) अणु
			अगर (dev2ser(serial_table[i])->port.count) अणु
				result =
				    hso_start_serial_device(serial_table[i], GFP_NOIO);
				hso_kick_transmit(dev2ser(serial_table[i]));
				अगर (result)
					जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Start all network ports */
	क्रम (i = 0; i < HSO_MAX_NET_DEVICES; i++) अणु
		अगर (network_table[i] &&
		    (network_table[i]->पूर्णांकerface == अगरace)) अणु
			hso_net = dev2net(network_table[i]);
			अगर (hso_net->flags & IFF_UP) अणु
				/* First transmit any lingering data,
				   then restart the device. */
				अगर (hso_net->skb_tx_buf) अणु
					dev_dbg(&अगरace->dev,
						"Transmitting"
						" lingering data\n");
					hso_net_start_xmit(hso_net->skb_tx_buf,
							   hso_net->net);
					hso_net->skb_tx_buf = शून्य;
				पूर्ण
				result = hso_start_net_device(network_table[i]);
				अगर (result)
					जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

out:
	वापस result;
पूर्ण

अटल व्योम hso_serial_ref_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा hso_device *hso_dev = container_of(ref, काष्ठा hso_device, ref);

	hso_मुक्त_serial_device(hso_dev);
पूर्ण

अटल व्योम hso_मुक्त_पूर्णांकerface(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा hso_serial *serial;
	पूर्णांक i;

	क्रम (i = 0; i < HSO_SERIAL_TTY_MINORS; i++) अणु
		अगर (serial_table[i] &&
		    (serial_table[i]->पूर्णांकerface == पूर्णांकerface)) अणु
			serial = dev2ser(serial_table[i]);
			tty_port_tty_hangup(&serial->port, false);
			mutex_lock(&serial->parent->mutex);
			serial->parent->usb_gone = 1;
			mutex_unlock(&serial->parent->mutex);
			cancel_work_sync(&serial_table[i]->async_put_पूर्णांकf);
			cancel_work_sync(&serial_table[i]->async_get_पूर्णांकf);
			hso_serial_tty_unरेजिस्टर(serial);
			kref_put(&serial->parent->ref, hso_serial_ref_मुक्त);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < HSO_MAX_NET_DEVICES; i++) अणु
		अगर (network_table[i] &&
		    (network_table[i]->पूर्णांकerface == पूर्णांकerface)) अणु
			काष्ठा rfसमाप्त *rfk = dev2net(network_table[i])->rfसमाप्त;
			/* hso_stop_net_device करोesn't stop the net queue since
			 * traffic needs to start it again when suspended */
			netअगर_stop_queue(dev2net(network_table[i])->net);
			hso_stop_net_device(network_table[i]);
			cancel_work_sync(&network_table[i]->async_put_पूर्णांकf);
			cancel_work_sync(&network_table[i]->async_get_पूर्णांकf);
			अगर (rfk) अणु
				rfसमाप्त_unरेजिस्टर(rfk);
				rfसमाप्त_destroy(rfk);
			पूर्ण
			hso_मुक्त_net_device(network_table[i], false);
		पूर्ण
	पूर्ण
पूर्ण

/* Helper functions */

/* Get the endpoपूर्णांक ! */
अटल काष्ठा usb_endpoपूर्णांक_descriptor *hso_get_ep(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
						  पूर्णांक type, पूर्णांक dir)
अणु
	पूर्णांक i;
	काष्ठा usb_host_पूर्णांकerface *अगरace = पूर्णांकf->cur_altsetting;
	काष्ठा usb_endpoपूर्णांक_descriptor *endp;

	क्रम (i = 0; i < अगरace->desc.bNumEndpoपूर्णांकs; i++) अणु
		endp = &अगरace->endpoपूर्णांक[i].desc;
		अगर (((endp->bEndpoपूर्णांकAddress & USB_ENDPOINT_सूची_MASK) == dir) &&
		    (usb_endpoपूर्णांक_type(endp) == type))
			वापस endp;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Get the byte that describes which ports are enabled */
अटल पूर्णांक hso_get_mux_ports(काष्ठा usb_पूर्णांकerface *पूर्णांकf, अचिन्हित अक्षर *ports)
अणु
	पूर्णांक i;
	काष्ठा usb_host_पूर्णांकerface *अगरace = पूर्णांकf->cur_altsetting;

	अगर (अगरace->extralen == 3) अणु
		*ports = अगरace->extra[2];
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < अगरace->desc.bNumEndpoपूर्णांकs; i++) अणु
		अगर (अगरace->endpoपूर्णांक[i].extralen == 3) अणु
			*ports = अगरace->endpoपूर्णांक[i].extra[2];
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण

/* पूर्णांकerrupt urb needs to be submitted, used क्रम serial पढ़ो of muxed port */
अटल पूर्णांक hso_mux_submit_पूर्णांकr_urb(काष्ठा hso_shared_पूर्णांक *shared_पूर्णांक,
				   काष्ठा usb_device *usb, gfp_t gfp)
अणु
	पूर्णांक result;

	usb_fill_पूर्णांक_urb(shared_पूर्णांक->shared_पूर्णांकr_urb, usb,
			 usb_rcvपूर्णांकpipe(usb,
				shared_पूर्णांक->पूर्णांकr_endp->bEndpoपूर्णांकAddress & 0x7F),
			 shared_पूर्णांक->shared_पूर्णांकr_buf,
			 1,
			 पूर्णांकr_callback, shared_पूर्णांक,
			 shared_पूर्णांक->पूर्णांकr_endp->bInterval);

	result = usb_submit_urb(shared_पूर्णांक->shared_पूर्णांकr_urb, gfp);
	अगर (result)
		dev_warn(&usb->dev, "%s failed mux_intr_urb %d\n", __func__,
			result);

	वापस result;
पूर्ण

/* operations setup of the serial पूर्णांकerface */
अटल स्थिर काष्ठा tty_operations hso_serial_ops = अणु
	.खोलो = hso_serial_खोलो,
	.बंद = hso_serial_बंद,
	.ग_लिखो = hso_serial_ग_लिखो,
	.ग_लिखो_room = hso_serial_ग_लिखो_room,
	.cleanup = hso_serial_cleanup,
	.ioctl = hso_serial_ioctl,
	.set_termios = hso_serial_set_termios,
	.अक्षरs_in_buffer = hso_serial_अक्षरs_in_buffer,
	.tiocmget = hso_serial_tiocmget,
	.tiocmset = hso_serial_tiocmset,
	.get_icount = hso_get_count,
	.unthrottle = hso_unthrottle
पूर्ण;

अटल काष्ठा usb_driver hso_driver = अणु
	.name = driver_name,
	.probe = hso_probe,
	.disconnect = hso_disconnect,
	.id_table = hso_ids,
	.suspend = hso_suspend,
	.resume = hso_resume,
	.reset_resume = hso_resume,
	.supports_स्वतःsuspend = 1,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

अटल पूर्णांक __init hso_init(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक result;

	/* put it in the log */
	pr_info("%s\n", version);

	/* Initialise the serial table semaphore and table */
	क्रम (i = 0; i < HSO_SERIAL_TTY_MINORS; i++)
		serial_table[i] = शून्य;

	/* allocate our driver using the proper amount of supported minors */
	tty_drv = alloc_tty_driver(HSO_SERIAL_TTY_MINORS);
	अगर (!tty_drv)
		वापस -ENOMEM;

	/* fill in all needed values */
	tty_drv->driver_name = driver_name;
	tty_drv->name = tty_filename;

	/* अगर major number is provided as parameter, use that one */
	अगर (tty_major)
		tty_drv->major = tty_major;

	tty_drv->minor_start = 0;
	tty_drv->type = TTY_DRIVER_TYPE_SERIAL;
	tty_drv->subtype = SERIAL_TYPE_NORMAL;
	tty_drv->flags = TTY_DRIVER_REAL_RAW | TTY_DRIVER_DYNAMIC_DEV;
	tty_drv->init_termios = tty_std_termios;
	hso_init_termios(&tty_drv->init_termios);
	tty_set_operations(tty_drv, &hso_serial_ops);

	/* रेजिस्टर the tty driver */
	result = tty_रेजिस्टर_driver(tty_drv);
	अगर (result) अणु
		pr_err("%s - tty_register_driver failed(%d)\n",
		       __func__, result);
		जाओ err_मुक्त_tty;
	पूर्ण

	/* रेजिस्टर this module as an usb driver */
	result = usb_रेजिस्टर(&hso_driver);
	अगर (result) अणु
		pr_err("Could not register hso driver - error: %d\n", result);
		जाओ err_unreg_tty;
	पूर्ण

	/* करोne */
	वापस 0;
err_unreg_tty:
	tty_unरेजिस्टर_driver(tty_drv);
err_मुक्त_tty:
	put_tty_driver(tty_drv);
	वापस result;
पूर्ण

अटल व्योम __निकास hso_निकास(व्योम)
अणु
	pr_info("unloaded\n");

	tty_unरेजिस्टर_driver(tty_drv);
	/* deरेजिस्टर the usb driver */
	usb_deरेजिस्टर(&hso_driver);
	put_tty_driver(tty_drv);
पूर्ण

/* Module definitions */
module_init(hso_init);
module_निकास(hso_निकास);

MODULE_AUTHOR(MOD_AUTHOR);
MODULE_DESCRIPTION(MOD_DESCRIPTION);
MODULE_LICENSE("GPL");

/* change the debug level (eg: insmod hso.ko debug=0x04) */
MODULE_PARM_DESC(debug, "debug level mask [0x01 | 0x02 | 0x04 | 0x08 | 0x10]");
module_param(debug, पूर्णांक, 0644);

/* set the major tty number (eg: insmod hso.ko tty_major=245) */
MODULE_PARM_DESC(tty_major, "Set the major tty number");
module_param(tty_major, पूर्णांक, 0644);

/* disable network पूर्णांकerface (eg: insmod hso.ko disable_net=1) */
MODULE_PARM_DESC(disable_net, "Disable the network interface");
module_param(disable_net, पूर्णांक, 0644);
