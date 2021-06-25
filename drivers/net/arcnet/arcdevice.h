<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET         An implementation of the TCP/IP protocol suite क्रम the LINUX
 *              operating प्रणाली.  NET  is implemented using the  BSD Socket
 *              पूर्णांकerface as the means of communication with the user level.
 *
 *              Definitions used by the ARCnet driver.
 *
 * Authors:     Avery Pennarun and David Woodhouse
 */
#अगर_अघोषित _LINUX_ARCDEVICE_H
#घोषणा _LINUX_ARCDEVICE_H

#समावेश <यंत्र/समयx.h>
#समावेश <linux/अगर_arcnet.h>

#अगर_घोषित __KERNEL__
#समावेश <linux/पूर्णांकerrupt.h>

/*
 * RECON_THRESHOLD is the maximum number of RECON messages to receive
 * within one minute beक्रमe prपूर्णांकing a "cabling problem" warning. The
 * शेष value should be fine.
 *
 * After that, a "cabling restored" message will be prपूर्णांकed on the next IRQ
 * अगर no RECON messages have been received क्रम 10 seconds.
 *
 * Do not define RECON_THRESHOLD at all अगर you want to disable this feature.
 */
#घोषणा RECON_THRESHOLD 30

/*
 * Define this to the minimum "timeout" value.  If a transmit takes दीर्घer
 * than TX_TIMEOUT jअगरfies, Linux will पात the TX and retry.  On a large
 * network, or one with heavy network traffic, this समयout may need to be
 * increased.  The larger it is, though, the दीर्घer it will be between
 * necessary transmits - करोn't set this too high.
 */
#घोषणा TX_TIMEOUT (HZ * 200 / 1000)

/* Display warnings about the driver being an ALPHA version. */
#अघोषित ALPHA_WARNING

/*
 * Debugging bitflags: each option can be enabled inभागidually.
 *
 * Note: only debug flags included in the ARCNET_DEBUG_MAX define will
 *   actually be available.  GCC will (at least, GCC 2.7.0 will) notice
 *   lines using a BUGLVL not in ARCNET_DEBUG_MAX and स्वतःmatically optimize
 *   them out.
 */
#घोषणा D_NORMAL	1	/* important operational info             */
#घोषणा D_EXTRA		2	/* useful, but non-vital inक्रमmation      */
#घोषणा	D_INIT		4	/* show init/probe messages               */
#घोषणा D_INIT_REASONS	8	/* show reasons क्रम discarding probes     */
#घोषणा D_RECON		32	/* prपूर्णांक a message whenever token is lost */
#घोषणा D_PROTO		64	/* debug स्वतः-protocol support            */
/* debug levels below give LOTS of output during normal operation! */
#घोषणा D_DURING	128	/* trace operations (including irq's)     */
#घोषणा D_TX	        256	/* show tx packets                        */
#घोषणा D_RX		512	/* show rx packets                        */
#घोषणा D_SKB		1024	/* show skb's                             */
#घोषणा D_SKB_SIZE	2048	/* show skb sizes			  */
#घोषणा D_TIMING	4096	/* show समय needed to copy buffers to card */
#घोषणा D_DEBUG         8192    /* Very detailed debug line क्रम line */

#अगर_अघोषित ARCNET_DEBUG_MAX
#घोषणा ARCNET_DEBUG_MAX (127)	/* change to ~0 अगर you want detailed debugging */
#पूर्ण_अगर

#अगर_अघोषित ARCNET_DEBUG
#घोषणा ARCNET_DEBUG (D_NORMAL | D_EXTRA)
#पूर्ण_अगर
बाह्य पूर्णांक arcnet_debug;

#घोषणा BUGLVL(x)	((x) & ARCNET_DEBUG_MAX & arcnet_debug)

/* macros to simplअगरy debug checking */
#घोषणा arc_prपूर्णांकk(x, dev, fmt, ...)					\
करो अणु									\
	अगर (BUGLVL(x)) अणु						\
		अगर ((x) == D_NORMAL)					\
			netdev_warn(dev, fmt, ##__VA_ARGS__);		\
		अन्यथा अगर ((x) < D_DURING)				\
			netdev_info(dev, fmt, ##__VA_ARGS__);		\
		अन्यथा							\
			netdev_dbg(dev, fmt, ##__VA_ARGS__);		\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा arc_cont(x, fmt, ...)						\
करो अणु									\
	अगर (BUGLVL(x))							\
		pr_cont(fmt, ##__VA_ARGS__);				\
पूर्ण जबतक (0)

/* see how दीर्घ a function call takes to run, expressed in CPU cycles */
#घोषणा TIME(dev, name, bytes, call)					\
करो अणु									\
	अगर (BUGLVL(D_TIMING)) अणु						\
		अचिन्हित दीर्घ _x, _y;					\
		_x = get_cycles();					\
		call;							\
		_y = get_cycles();					\
		arc_prपूर्णांकk(D_TIMING, dev,				\
			   "%s: %d bytes in %lu cycles == %lu Kbytes/100Mcycle\n", \
			   name, bytes, _y - _x,			\
			   100000000 / 1024 * bytes / (_y - _x + 1));	\
	पूर्ण अन्यथा अणु							\
		call;							\
	पूर्ण								\
पूर्ण जबतक (0)

/*
 * Time needed to reset the card - in ms (milliseconds).  This works on my
 * SMC PC100.  I can't find a reference that tells me just how दीर्घ I
 * should रुको.
 */
#घोषणा RESETसमय (300)

/*
 * These are the max/min lengths of packet payload, not including the
 * arc_hardware header, but definitely including the soft header.
 *
 * Note: packet sizes 254, 255, 256 are impossible because of the way
 * ARCnet रेजिस्टरs work  That's why RFC1201 defines "exception" packets.
 * In non-RFC1201 protocols, we have to just tack some extra bytes on the
 * end.
 */
#घोषणा MTU	253		/* normal packet max size */
#घोषणा MinTU	257		/* extended packet min size */
#घोषणा XMTU	508		/* extended packet max size */

/* status/पूर्णांकerrupt mask bit fields */
#घोषणा TXFREEflag	0x01	/* transmitter available */
#घोषणा TXACKflag       0x02	/* transmitted msg. ackd */
#घोषणा RECONflag       0x04	/* network reconfigured */
#घोषणा TESTflag        0x08	/* test flag */
#घोषणा EXCNAKflag      0x08    /* excesive nak flag */
#घोषणा RESETflag       0x10	/* घातer-on-reset */
#घोषणा RES1flag        0x20	/* reserved - usually set by jumper */
#घोषणा RES2flag        0x40	/* reserved - usually set by jumper */
#घोषणा NORXflag        0x80	/* receiver inhibited */

/* Flags used क्रम IO-mapped memory operations */
#घोषणा AUTOINCflag     0x40	/* Increase location with each access */
#घोषणा IOMAPflag       0x02	/* (क्रम 90xx) Use IO mapped memory, not mmap */
#घोषणा ENABLE16flag    0x80	/* (क्रम 90xx) Enable 16-bit mode */

/* in the command रेजिस्टर, the following bits have these meanings:
 *                0-2     command
 *                3-4     page number (क्रम enable rcv/xmt command)
 *                 7      receive broadcasts
 */
#घोषणा NOTXcmd         0x01	/* disable transmitter */
#घोषणा NORXcmd         0x02	/* disable receiver */
#घोषणा TXcmd           0x03	/* enable transmitter */
#घोषणा RXcmd           0x04	/* enable receiver */
#घोषणा CONFIGcmd       0x05	/* define configuration */
#घोषणा CFLAGScmd       0x06	/* clear flags */
#घोषणा TESTcmd         0x07	/* load test flags */
#घोषणा STARTIOcmd      0x18	/* start पूर्णांकernal operation */

/* flags क्रम "clear flags" command */
#घोषणा RESETclear      0x08	/* घातer-on-reset */
#घोषणा CONFIGclear     0x10	/* प्रणाली reconfigured */

#घोषणा EXCNAKclear     0x0E    /* Clear and acknowledge the excive nak bit */

/* flags क्रम "load test flags" command */
#घोषणा TESTload        0x08	/* test flag (diagnostic) */

/* byte deposited पूर्णांकo first address of buffers on reset */
#घोषणा TESTvalue       0321	/* that's octal क्रम 0xD1 :) */

/* क्रम "enable receiver" command */
#घोषणा RXbcasts        0x80	/* receive broadcasts */

/* flags क्रम "define configuration" command */
#घोषणा NORMALconf      0x00	/* 1-249 byte packets */
#घोषणा EXTconf         0x08	/* 250-504 byte packets */

/* card feature flags, set during स्वतः-detection.
 * (currently only used by com20020pci)
 */
#घोषणा ARC_IS_5MBIT    1   /* card शेष speed is 5MBit */
#घोषणा ARC_CAN_10MBIT  2   /* card uses COM20022, supporting 10MBit,
				 but शेष is 2.5MBit. */

/* inक्रमmation needed to define an encapsulation driver */
काष्ठा ArcProto अणु
	अक्षर suffix;		/* a क्रम RFC1201, e क्रम ether-encap, etc. */
	पूर्णांक mtu;		/* largest possible packet */
	पूर्णांक is_ip;              /* This is a ip plugin - not a raw thing */

	व्योम (*rx)(काष्ठा net_device *dev, पूर्णांक bufnum,
		   काष्ठा archdr *pkthdr, पूर्णांक length);
	पूर्णांक (*build_header)(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			    अचिन्हित लघु ethproto, uपूर्णांक8_t daddr);

	/* these functions वापस '1' अगर the skb can now be मुक्तd */
	पूर्णांक (*prepare_tx)(काष्ठा net_device *dev, काष्ठा archdr *pkt,
			  पूर्णांक length, पूर्णांक bufnum);
	पूर्णांक (*जारी_tx)(काष्ठा net_device *dev, पूर्णांक bufnum);
	पूर्णांक (*ack_tx)(काष्ठा net_device *dev, पूर्णांक acked);
पूर्ण;

बाह्य काष्ठा ArcProto *arc_proto_map[256], *arc_proto_शेष,
	*arc_bcast_proto, *arc_raw_proto;

/*
 * "Incoming" is inक्रमmation needed क्रम each address that could be sending
 * to us.  Mostly क्रम partially-received split packets.
 */
काष्ठा Incoming अणु
	काष्ठा sk_buff *skb;	/* packet data buffer             */
	__be16 sequence;	/* sequence number of assembly    */
	uपूर्णांक8_t lastpacket,	/* number of last packet (from 1) */
		numpackets;	/* number of packets in split     */
पूर्ण;

/* only needed क्रम RFC1201 */
काष्ठा Outgoing अणु
	काष्ठा ArcProto *proto;	/* protocol driver that owns this:
				 *   अगर शून्य, no packet is pending.
				 */
	काष्ठा sk_buff *skb;	/* buffer from upper levels */
	काष्ठा archdr *pkt;	/* a poपूर्णांकer पूर्णांकo the skb */
	uपूर्णांक16_t length,	/* bytes total */
		dataleft,	/* bytes left */
		segnum,		/* segment being sent */
		numsegs;	/* number of segments */
पूर्ण;

#घोषणा ARCNET_LED_NAME_SZ (IFNAMSIZ + 6)

काष्ठा arcnet_local अणु
	uपूर्णांक8_t config,		/* current value of CONFIG रेजिस्टर */
		समयout,	/* Extended समयout क्रम COM20020 */
		backplane,	/* Backplane flag क्रम COM20020 */
		घड़ीp,		/* COM20020 घड़ी भागider */
		घड़ीm,		/* COM20020 घड़ी multiplier flag */
		setup,		/* Contents of setup1 रेजिस्टर */
		setup2,		/* Contents of setup2 रेजिस्टर */
		पूर्णांकmask;	/* current value of INTMASK रेजिस्टर */
	uपूर्णांक8_t शेष_proto[256];	/* शेष encap to use क्रम each host */
	पूर्णांक	cur_tx,		/* buffer used by current transmit, or -1 */
		next_tx,	/* buffer where a packet is पढ़ोy to send */
		cur_rx;		/* current receive buffer */
	पूर्णांक	lastload_dest,	/* can last loaded packet be acked? */
		lasttrans_dest;	/* can last TX'd packet be acked? */
	पूर्णांक	समयd_out;	/* need to process TX समयout and drop packet */
	अचिन्हित दीर्घ last_समयout;	/* समय of last reported समयout */
	अक्षर *card_name;	/* card ident string */
	पूर्णांक card_flags;		/* special card features */

	/* On preemtive and SMB a lock is needed */
	spinlock_t lock;

	काष्ठा led_trigger *tx_led_trig;
	अक्षर tx_led_trig_name[ARCNET_LED_NAME_SZ];
	काष्ठा led_trigger *recon_led_trig;
	अक्षर recon_led_trig_name[ARCNET_LED_NAME_SZ];

	काष्ठा समयr_list	समयr;

	काष्ठा net_device *dev;
	पूर्णांक reply_status;
	काष्ठा tasklet_काष्ठा reply_tasklet;

	/*
	 * Buffer management: an ARCnet card has 4 x 512-byte buffers, each of
	 * which can be used क्रम either sending or receiving.  The new dynamic
	 * buffer management routines use a simple circular queue of available
	 * buffers, and take them as they're needed.  This way, we simplअगरy
	 * situations in which we (क्रम example) want to pre-load a transmit
	 * buffer, or start receiving जबतक we copy a received packet to
	 * memory.
	 *
	 * The rules: only the पूर्णांकerrupt handler is allowed to _add_ buffers to
	 * the queue; thus, this करोesn't require a lock.  Both the पूर्णांकerrupt
	 * handler and the transmit function will want to _हटाओ_ buffers, so
	 * we need to handle the situation where they try to करो it at the same
	 * समय.
	 *
	 * If next_buf == first_मुक्त_buf, the queue is empty.  Since there are
	 * only four possible buffers, the queue should never be full.
	 */
	atomic_t buf_lock;
	पूर्णांक buf_queue[5];
	पूर्णांक next_buf, first_मुक्त_buf;

	/* network "reconfiguration" handling */
	अचिन्हित दीर्घ first_recon; /* समय of "first" RECON message to count */
	अचिन्हित दीर्घ last_recon;  /* समय of most recent RECON */
	पूर्णांक num_recons;		/* number of RECONs between first and last. */
	पूर्णांक network_करोwn;	/* करो we think the network is करोwn? */

	पूर्णांक excnak_pending;    /* We just got an excesive nak पूर्णांकerrupt */

	/* RESET flag handling */
	पूर्णांक reset_in_progress;
	काष्ठा work_काष्ठा reset_work;

	काष्ठा अणु
		uपूर्णांक16_t sequence;	/* sequence number (incs with each packet) */
		__be16 पातed_seq;

		काष्ठा Incoming incoming[256];	/* one from each address */
	पूर्ण rfc1201;

	/* really only used by rfc1201, but we'll pretend it's not */
	काष्ठा Outgoing outgoing;	/* packet currently being sent */

	/* hardware-specअगरic functions */
	काष्ठा अणु
		काष्ठा module *owner;
		व्योम (*command)(काष्ठा net_device *dev, पूर्णांक cmd);
		पूर्णांक (*status)(काष्ठा net_device *dev);
		व्योम (*पूर्णांकmask)(काष्ठा net_device *dev, पूर्णांक mask);
		पूर्णांक (*reset)(काष्ठा net_device *dev, पूर्णांक really_reset);
		व्योम (*खोलो)(काष्ठा net_device *dev);
		व्योम (*बंद)(काष्ठा net_device *dev);
		व्योम (*datatrigger) (काष्ठा net_device * dev, पूर्णांक enable);
		व्योम (*recontrigger) (काष्ठा net_device * dev, पूर्णांक enable);

		व्योम (*copy_to_card)(काष्ठा net_device *dev, पूर्णांक bufnum,
				     पूर्णांक offset, व्योम *buf, पूर्णांक count);
		व्योम (*copy_from_card)(काष्ठा net_device *dev, पूर्णांक bufnum,
				       पूर्णांक offset, व्योम *buf, पूर्णांक count);
	पूर्ण hw;

	व्योम __iomem *mem_start;	/* poपूर्णांकer to ioremap'ed MMIO */
पूर्ण;

क्रमागत arcnet_led_event अणु
	ARCNET_LED_EVENT_RECON,
	ARCNET_LED_EVENT_OPEN,
	ARCNET_LED_EVENT_STOP,
	ARCNET_LED_EVENT_TX,
पूर्ण;

व्योम arcnet_led_event(काष्ठा net_device *netdev, क्रमागत arcnet_led_event event);
व्योम devm_arcnet_led_init(काष्ठा net_device *netdev, पूर्णांक index, पूर्णांक subid);

#अगर ARCNET_DEBUG_MAX & D_SKB
व्योम arcnet_dump_skb(काष्ठा net_device *dev, काष्ठा sk_buff *skb, अक्षर *desc);
#अन्यथा
अटल अंतरभूत
व्योम arcnet_dump_skb(काष्ठा net_device *dev, काष्ठा sk_buff *skb, अक्षर *desc)
अणु
पूर्ण
#पूर्ण_अगर

व्योम arcnet_unरेजिस्टर_proto(काष्ठा ArcProto *proto);
irqवापस_t arcnet_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

काष्ठा net_device *alloc_arcdev(स्थिर अक्षर *name);
व्योम मुक्त_arcdev(काष्ठा net_device *dev);

पूर्णांक arcnet_खोलो(काष्ठा net_device *dev);
पूर्णांक arcnet_बंद(काष्ठा net_device *dev);
netdev_tx_t arcnet_send_packet(काष्ठा sk_buff *skb,
			       काष्ठा net_device *dev);
व्योम arcnet_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);

/* I/O equivalents */

#अगर_घोषित CONFIG_SA1100_CT6001
#घोषणा BUS_ALIGN  2  /* 8 bit device on a 16 bit bus - needs padding */
#अन्यथा
#घोषणा BUS_ALIGN  1
#पूर्ण_अगर

/* addr and offset allow रेजिस्टर like names to define the actual IO  address.
 * A configuration option multiplies the offset क्रम alignment.
 */
#घोषणा arcnet_inb(addr, offset)					\
	inb((addr) + BUS_ALIGN * (offset))
#घोषणा arcnet_outb(value, addr, offset)				\
	outb(value, (addr) + BUS_ALIGN * (offset))

#घोषणा arcnet_insb(addr, offset, buffer, count)			\
	insb((addr) + BUS_ALIGN * (offset), buffer, count)
#घोषणा arcnet_outsb(addr, offset, buffer, count)			\
	outsb((addr) + BUS_ALIGN * (offset), buffer, count)

#घोषणा arcnet_पढ़ोb(addr, offset)					\
	पढ़ोb((addr) + (offset))
#घोषणा arcnet_ग_लिखोb(value, addr, offset)				\
	ग_लिखोb(value, (addr) + (offset))

#पूर्ण_अगर				/* __KERNEL__ */
#पूर्ण_अगर				/* _LINUX_ARCDEVICE_H */
