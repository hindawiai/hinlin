<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * IPWireless 3G PCMCIA Network Driver
 *
 * Original code
 *   by Stephen Blackheath <stephen@blacksapphire.com>,
 *      Ben Martel <benm@symmetric.co.nz>
 *
 * Copyrighted as follows:
 *   Copyright (C) 2004 by Symmetric Systems Ltd (NZ)
 *
 * Various driver changes and reग_लिखोs, port to new kernels
 *   Copyright (C) 2006-2007 Jiri Kosina
 *
 * Misc code cleanups and updates
 *   Copyright (C) 2007 David Sterba
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>

#समावेश "hardware.h"
#समावेश "setup_protocol.h"
#समावेश "network.h"
#समावेश "main.h"

अटल व्योम ipw_send_setup_packet(काष्ठा ipw_hardware *hw);
अटल व्योम handle_received_SETUP_packet(काष्ठा ipw_hardware *ipw,
					 अचिन्हित पूर्णांक address,
					 स्थिर अचिन्हित अक्षर *data, पूर्णांक len,
					 पूर्णांक is_last);
अटल व्योम ipwireless_setup_समयr(काष्ठा समयr_list *t);
अटल व्योम handle_received_CTRL_packet(काष्ठा ipw_hardware *hw,
		अचिन्हित पूर्णांक channel_idx, स्थिर अचिन्हित अक्षर *data, पूर्णांक len);

/*#घोषणा TIMING_DIAGNOSTICS*/

#अगर_घोषित TIMING_DIAGNOSTICS

अटल काष्ठा timing_stats अणु
	अचिन्हित दीर्घ last_report_समय;
	अचिन्हित दीर्घ पढ़ो_समय;
	अचिन्हित दीर्घ ग_लिखो_समय;
	अचिन्हित दीर्घ पढ़ो_bytes;
	अचिन्हित दीर्घ ग_लिखो_bytes;
	अचिन्हित दीर्घ start_समय;
पूर्ण;

अटल व्योम start_timing(व्योम)
अणु
	timing_stats.start_समय = jअगरfies;
पूर्ण

अटल व्योम end_पढ़ो_timing(अचिन्हित length)
अणु
	timing_stats.पढ़ो_समय += (jअगरfies - start_समय);
	timing_stats.पढ़ो_bytes += length + 2;
	report_timing();
पूर्ण

अटल व्योम end_ग_लिखो_timing(अचिन्हित length)
अणु
	timing_stats.ग_लिखो_समय += (jअगरfies - start_समय);
	timing_stats.ग_लिखो_bytes += length + 2;
	report_timing();
पूर्ण

अटल व्योम report_timing(व्योम)
अणु
	अचिन्हित दीर्घ since = jअगरfies - timing_stats.last_report_समय;

	/* If it's been more than one second... */
	अगर (since >= HZ) अणु
		पूर्णांक first = (timing_stats.last_report_समय == 0);

		timing_stats.last_report_समय = jअगरfies;
		अगर (!first)
			prपूर्णांकk(KERN_INFO IPWIRELESS_PCCARD_NAME
			       ": %u us elapsed - read %lu bytes in %u us, wrote %lu bytes in %u us\n",
			       jअगरfies_to_usecs(since),
			       timing_stats.पढ़ो_bytes,
			       jअगरfies_to_usecs(timing_stats.पढ़ो_समय),
			       timing_stats.ग_लिखो_bytes,
			       jअगरfies_to_usecs(timing_stats.ग_लिखो_समय));

		timing_stats.पढ़ो_समय = 0;
		timing_stats.ग_लिखो_समय = 0;
		timing_stats.पढ़ो_bytes = 0;
		timing_stats.ग_लिखो_bytes = 0;
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम start_timing(व्योम) अणु पूर्ण
अटल व्योम end_पढ़ो_timing(अचिन्हित length) अणु पूर्ण
अटल व्योम end_ग_लिखो_timing(अचिन्हित length) अणु पूर्ण
#पूर्ण_अगर

/* Imported IPW definitions */

#घोषणा LL_MTU_V1 318
#घोषणा LL_MTU_V2 250
#घोषणा LL_MTU_MAX (LL_MTU_V1 > LL_MTU_V2 ? LL_MTU_V1 : LL_MTU_V2)

#घोषणा PRIO_DATA  2
#घोषणा PRIO_CTRL  1
#घोषणा PRIO_SETUP 0

/* Addresses */
#घोषणा ADDR_SETUP_PROT 0

/* Protocol ids */
क्रमागत अणु
	/* Identअगरier क्रम the Com Data protocol */
	TL_PROTOCOLID_COM_DATA = 0,

	/* Identअगरier क्रम the Com Control protocol */
	TL_PROTOCOLID_COM_CTRL = 1,

	/* Identअगरier क्रम the Setup protocol */
	TL_PROTOCOLID_SETUP = 2
पूर्ण;

/* Number of bytes in NL packet header (cannot करो
 * माप(nl_packet_header) since it's a bitfield) */
#घोषणा NL_FIRST_PACKET_HEADER_SIZE        3

/* Number of bytes in NL packet header (cannot करो
 * माप(nl_packet_header) since it's a bitfield) */
#घोषणा NL_FOLLOWING_PACKET_HEADER_SIZE    1

काष्ठा nl_first_packet_header अणु
	अचिन्हित अक्षर protocol:3;
	अचिन्हित अक्षर address:3;
	अचिन्हित अक्षर packet_rank:2;
	अचिन्हित अक्षर length_lsb;
	अचिन्हित अक्षर length_msb;
पूर्ण;

काष्ठा nl_packet_header अणु
	अचिन्हित अक्षर protocol:3;
	अचिन्हित अक्षर address:3;
	अचिन्हित अक्षर packet_rank:2;
पूर्ण;

/* Value of 'packet_rank' above */
#घोषणा NL_INTERMEDIATE_PACKET    0x0
#घोषणा NL_LAST_PACKET            0x1
#घोषणा NL_FIRST_PACKET           0x2

जोड़ nl_packet अणु
	/* Network packet header of the first packet (a special हाल) */
	काष्ठा nl_first_packet_header hdr_first;
	/* Network packet header of the following packets (अगर any) */
	काष्ठा nl_packet_header hdr;
	/* Complete network packet (header + data) */
	अचिन्हित अक्षर rawpkt[LL_MTU_MAX];
पूर्ण __attribute__ ((__packed__));

#घोषणा HW_VERSION_UNKNOWN -1
#घोषणा HW_VERSION_1 1
#घोषणा HW_VERSION_2 2

/* IPW I/O ports */
#घोषणा IOIER 0x00		/* Interrupt Enable Register */
#घोषणा IOIR  0x02		/* Interrupt Source/ACK रेजिस्टर */
#घोषणा IODCR 0x04		/* Data Control Register */
#घोषणा IODRR 0x06		/* Data Read Register */
#घोषणा IODWR 0x08		/* Data Write Register */
#घोषणा IOESR 0x0A		/* Embedded Driver Status Register */
#घोषणा IORXR 0x0C		/* Rx Fअगरo Register (Host to Embedded) */
#घोषणा IOTXR 0x0E		/* Tx Fअगरo Register (Embedded to Host) */

/* I/O ports and bit definitions क्रम version 1 of the hardware */

/* IER bits*/
#घोषणा IER_RXENABLED   0x1
#घोषणा IER_TXENABLED   0x2

/* ISR bits */
#घोषणा IR_RXINTR       0x1
#घोषणा IR_TXINTR       0x2

/* DCR bits */
#घोषणा DCR_RXDONE      0x1
#घोषणा DCR_TXDONE      0x2
#घोषणा DCR_RXRESET     0x4
#घोषणा DCR_TXRESET     0x8

/* I/O ports and bit definitions क्रम version 2 of the hardware */

काष्ठा MEMCCR अणु
	अचिन्हित लघु reg_config_option;	/* PCCOR: Configuration Option Register */
	अचिन्हित लघु reg_config_and_status;	/* PCCSR: Configuration and Status Register */
	अचिन्हित लघु reg_pin_replacement;	/* PCPRR: Pin Replacemant Register */
	अचिन्हित लघु reg_socket_and_copy;	/* PCSCR: Socket and Copy Register */
	अचिन्हित लघु reg_ext_status;		/* PCESR: Extendend Status Register */
	अचिन्हित लघु reg_io_base;		/* PCIOB: I/O Base Register */
पूर्ण;

काष्ठा MEMINFREG अणु
	अचिन्हित लघु memreg_tx_old;	/* TX Register (R/W) */
	अचिन्हित लघु pad1;
	अचिन्हित लघु memreg_rx_करोne;	/* RXDone Register (R/W) */
	अचिन्हित लघु pad2;
	अचिन्हित लघु memreg_rx;	/* RX Register (R/W) */
	अचिन्हित लघु pad3;
	अचिन्हित लघु memreg_pc_पूर्णांकerrupt_ack;	/* PC पूर्णांकr Ack Register (W) */
	अचिन्हित लघु pad4;
	अचिन्हित दीर्घ memreg_card_present;/* Mask क्रम Host to check (R) क्रम
					   * CARD_PRESENT_VALUE */
	अचिन्हित लघु memreg_tx_new;	/* TX2 (new) Register (R/W) */
पूर्ण;

#घोषणा CARD_PRESENT_VALUE (0xBEEFCAFEUL)

#घोषणा MEMTX_TX                       0x0001
#घोषणा MEMRX_RX                       0x0001
#घोषणा MEMRX_RX_DONE                  0x0001
#घोषणा MEMRX_PCINTACKK                0x0001

#घोषणा NL_NUM_OF_PRIORITIES       3
#घोषणा NL_NUM_OF_PROTOCOLS        3
#घोषणा NL_NUM_OF_ADDRESSES        NO_OF_IPW_CHANNELS

काष्ठा ipw_hardware अणु
	अचिन्हित पूर्णांक base_port;
	लघु hw_version;
	अचिन्हित लघु ll_mtu;
	spinlock_t lock;

	पूर्णांक initializing;
	पूर्णांक init_loops;
	काष्ठा समयr_list setup_समयr;

	/* Flag अगर hw is पढ़ोy to send next packet */
	पूर्णांक tx_पढ़ोy;
	/* Count of pending packets to be sent */
	पूर्णांक tx_queued;
	काष्ठा list_head tx_queue[NL_NUM_OF_PRIORITIES];

	पूर्णांक rx_bytes_queued;
	काष्ठा list_head rx_queue;
	/* Pool of rx_packet काष्ठाures that are not currently used. */
	काष्ठा list_head rx_pool;
	पूर्णांक rx_pool_size;
	/* True अगर reception of data is blocked जबतक userspace processes it. */
	पूर्णांक blocking_rx;
	/* True अगर there is RX data पढ़ोy on the hardware. */
	पूर्णांक rx_पढ़ोy;
	अचिन्हित लघु last_memtx_serial;
	/*
	 * Newer versions of the V2 card firmware send serial numbers in the
	 * MemTX रेजिस्टर. 'serial_number_detected' is set true when we detect
	 * a non-zero serial number (indicating the new firmware).  Thereafter,
	 * the driver can safely ignore the Timer Recovery re-sends to aव्योम
	 * out-of-sync problems.
	 */
	पूर्णांक serial_number_detected;
	काष्ठा work_काष्ठा work_rx;

	/* True अगर we are to send the set-up data to the hardware. */
	पूर्णांक to_setup;

	/* Card has been हटाओd */
	पूर्णांक हटाओd;
	/* Saved irq value when we disable the पूर्णांकerrupt. */
	पूर्णांक irq;
	/* True अगर this driver is shutting करोwn. */
	पूर्णांक shutting_करोwn;
	/* Modem control lines */
	अचिन्हित पूर्णांक control_lines[NL_NUM_OF_ADDRESSES];
	काष्ठा ipw_rx_packet *packet_assembler[NL_NUM_OF_ADDRESSES];

	काष्ठा tasklet_काष्ठा tasklet;

	/* The handle क्रम the network layer, क्रम the sending of events to it. */
	काष्ठा ipw_network *network;
	काष्ठा MEMINFREG __iomem *memory_info_regs;
	काष्ठा MEMCCR __iomem *memregs_CCR;
	व्योम (*reboot_callback) (व्योम *data);
	व्योम *reboot_callback_data;

	अचिन्हित लघु __iomem *memreg_tx;
पूर्ण;

/*
 * Packet info काष्ठाure क्रम tx packets.
 * Note: not all the fields defined here are required क्रम all protocols
 */
काष्ठा ipw_tx_packet अणु
	काष्ठा list_head queue;
	/* channel idx + 1 */
	अचिन्हित अक्षर dest_addr;
	/* SETUP, CTRL or DATA */
	अचिन्हित अक्षर protocol;
	/* Length of data block, which starts at the end of this काष्ठाure */
	अचिन्हित लघु length;
	/* Sending state */
	/* Offset of where we've sent up to so far */
	अचिन्हित दीर्घ offset;
	/* Count of packet fragments, starting at 0 */
	पूर्णांक fragment_count;

	/* Called after packet is sent and beक्रमe is मुक्तd */
	व्योम (*packet_callback) (व्योम *cb_data, अचिन्हित पूर्णांक packet_length);
	व्योम *callback_data;
पूर्ण;

/* Signals from DTE */
#घोषणा COMCTRL_RTS	0
#घोषणा COMCTRL_DTR	1

/* Signals from DCE */
#घोषणा COMCTRL_CTS	2
#घोषणा COMCTRL_DCD	3
#घोषणा COMCTRL_DSR	4
#घोषणा COMCTRL_RI	5

काष्ठा ipw_control_packet_body अणु
	/* DTE संकेत or DCE संकेत */
	अचिन्हित अक्षर sig_no;
	/* 0: set संकेत, 1: clear संकेत */
	अचिन्हित अक्षर value;
पूर्ण __attribute__ ((__packed__));

काष्ठा ipw_control_packet अणु
	काष्ठा ipw_tx_packet header;
	काष्ठा ipw_control_packet_body body;
पूर्ण;

काष्ठा ipw_rx_packet अणु
	काष्ठा list_head queue;
	अचिन्हित पूर्णांक capacity;
	अचिन्हित पूर्णांक length;
	अचिन्हित पूर्णांक protocol;
	अचिन्हित पूर्णांक channel_idx;
पूर्ण;

अटल अक्षर *data_type(स्थिर अचिन्हित अक्षर *buf, अचिन्हित length)
अणु
	काष्ठा nl_packet_header *hdr = (काष्ठा nl_packet_header *) buf;

	अगर (length == 0)
		वापस "     ";

	अगर (hdr->packet_rank & NL_FIRST_PACKET) अणु
		चयन (hdr->protocol) अणु
		हाल TL_PROTOCOLID_COM_DATA:	वापस "DATA ";
		हाल TL_PROTOCOLID_COM_CTRL:	वापस "CTRL ";
		हाल TL_PROTOCOLID_SETUP:	वापस "SETUP";
		शेष: वापस "???? ";
		पूर्ण
	पूर्ण अन्यथा
		वापस "     ";
पूर्ण

#घोषणा DUMP_MAX_BYTES 64

अटल व्योम dump_data_bytes(स्थिर अक्षर *type, स्थिर अचिन्हित अक्षर *data,
			    अचिन्हित length)
अणु
	अक्षर prefix[56];

	प्र_लिखो(prefix, IPWIRELESS_PCCARD_NAME ": %s %s ",
			type, data_type(data, length));
	prपूर्णांक_hex_dump_bytes(prefix, 0, (व्योम *)data,
			length < DUMP_MAX_BYTES ? length : DUMP_MAX_BYTES);
पूर्ण

अटल व्योम swap_packet_bitfield_to_le(अचिन्हित अक्षर *data)
अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	अचिन्हित अक्षर पंचांगp = *data, ret = 0;

	/*
	 * transक्रमm bits from aa.bbb.ccc to ccc.bbb.aa
	 */
	ret |= (पंचांगp & 0xc0) >> 6;
	ret |= (पंचांगp & 0x38) >> 1;
	ret |= (पंचांगp & 0x07) << 5;
	*data = ret & 0xff;
#पूर्ण_अगर
पूर्ण

अटल व्योम swap_packet_bitfield_from_le(अचिन्हित अक्षर *data)
अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	अचिन्हित अक्षर पंचांगp = *data, ret = 0;

	/*
	 * transक्रमm bits from ccc.bbb.aa to aa.bbb.ccc
	 */
	ret |= (पंचांगp & 0xe0) >> 5;
	ret |= (पंचांगp & 0x1c) << 1;
	ret |= (पंचांगp & 0x03) << 6;
	*data = ret & 0xff;
#पूर्ण_अगर
पूर्ण

अटल व्योम करो_send_fragment(काष्ठा ipw_hardware *hw, अचिन्हित अक्षर *data,
			    अचिन्हित length)
अणु
	अचिन्हित i;
	अचिन्हित दीर्घ flags;

	start_timing();
	BUG_ON(length > hw->ll_mtu);

	अगर (ipwireless_debug)
		dump_data_bytes("send", data, length);

	spin_lock_irqsave(&hw->lock, flags);

	hw->tx_पढ़ोy = 0;
	swap_packet_bitfield_to_le(data);

	अगर (hw->hw_version == HW_VERSION_1) अणु
		outw((अचिन्हित लघु) length, hw->base_port + IODWR);

		क्रम (i = 0; i < length; i += 2) अणु
			अचिन्हित लघु d = data[i];
			__le16 raw_data;

			अगर (i + 1 < length)
				d |= data[i + 1] << 8;
			raw_data = cpu_to_le16(d);
			outw(raw_data, hw->base_port + IODWR);
		पूर्ण

		outw(DCR_TXDONE, hw->base_port + IODCR);
	पूर्ण अन्यथा अगर (hw->hw_version == HW_VERSION_2) अणु
		outw((अचिन्हित लघु) length, hw->base_port);

		क्रम (i = 0; i < length; i += 2) अणु
			अचिन्हित लघु d = data[i];
			__le16 raw_data;

			अगर (i + 1 < length)
				d |= data[i + 1] << 8;
			raw_data = cpu_to_le16(d);
			outw(raw_data, hw->base_port);
		पूर्ण
		जबतक ((i & 3) != 2) अणु
			outw((अचिन्हित लघु) 0xDEAD, hw->base_port);
			i += 2;
		पूर्ण
		ग_लिखोw(MEMRX_RX, &hw->memory_info_regs->memreg_rx);
	पूर्ण

	spin_unlock_irqrestore(&hw->lock, flags);

	end_ग_लिखो_timing(length);
पूर्ण

अटल व्योम करो_send_packet(काष्ठा ipw_hardware *hw, काष्ठा ipw_tx_packet *packet)
अणु
	अचिन्हित लघु fragment_data_len;
	अचिन्हित लघु data_left = packet->length - packet->offset;
	अचिन्हित लघु header_size;
	जोड़ nl_packet pkt;

	header_size =
	    (packet->fragment_count == 0)
	    ? NL_FIRST_PACKET_HEADER_SIZE
	    : NL_FOLLOWING_PACKET_HEADER_SIZE;
	fragment_data_len = hw->ll_mtu - header_size;
	अगर (data_left < fragment_data_len)
		fragment_data_len = data_left;

	/*
	 * hdr_first is now in machine bitfield order, which will be swapped
	 * to le just beक्रमe it goes to hw
	 */
	pkt.hdr_first.protocol = packet->protocol;
	pkt.hdr_first.address = packet->dest_addr;
	pkt.hdr_first.packet_rank = 0;

	/* First packet? */
	अगर (packet->fragment_count == 0) अणु
		pkt.hdr_first.packet_rank |= NL_FIRST_PACKET;
		pkt.hdr_first.length_lsb = (अचिन्हित अक्षर) packet->length;
		pkt.hdr_first.length_msb =
			(अचिन्हित अक्षर) (packet->length >> 8);
	पूर्ण

	स_नकल(pkt.rawpkt + header_size,
	       ((अचिन्हित अक्षर *) packet) + माप(काष्ठा ipw_tx_packet) +
	       packet->offset, fragment_data_len);
	packet->offset += fragment_data_len;
	packet->fragment_count++;

	/* Last packet? (May also be first packet.) */
	अगर (packet->offset == packet->length)
		pkt.hdr_first.packet_rank |= NL_LAST_PACKET;
	करो_send_fragment(hw, pkt.rawpkt, header_size + fragment_data_len);

	/* If this packet has unsent data, then re-queue it. */
	अगर (packet->offset < packet->length) अणु
		/*
		 * Re-queue it at the head of the highest priority queue so
		 * it goes beक्रमe all other packets
		 */
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&hw->lock, flags);
		list_add(&packet->queue, &hw->tx_queue[0]);
		hw->tx_queued++;
		spin_unlock_irqrestore(&hw->lock, flags);
	पूर्ण अन्यथा अणु
		अगर (packet->packet_callback)
			packet->packet_callback(packet->callback_data,
					packet->length);
		kमुक्त(packet);
	पूर्ण
पूर्ण

अटल व्योम ipw_setup_hardware(काष्ठा ipw_hardware *hw)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hw->lock, flags);
	अगर (hw->hw_version == HW_VERSION_1) अणु
		/* Reset RX FIFO */
		outw(DCR_RXRESET, hw->base_port + IODCR);
		/* SB: Reset TX FIFO */
		outw(DCR_TXRESET, hw->base_port + IODCR);

		/* Enable TX and RX पूर्णांकerrupts. */
		outw(IER_TXENABLED | IER_RXENABLED, hw->base_port + IOIER);
	पूर्ण अन्यथा अणु
		/*
		 * Set INTRACK bit (bit 0), which means we must explicitly
		 * acknowledge पूर्णांकerrupts by clearing bit 2 of reg_config_and_status.
		 */
		अचिन्हित लघु csr = पढ़ोw(&hw->memregs_CCR->reg_config_and_status);

		csr |= 1;
		ग_लिखोw(csr, &hw->memregs_CCR->reg_config_and_status);
	पूर्ण
	spin_unlock_irqrestore(&hw->lock, flags);
पूर्ण

/*
 * If 'packet' is शून्य, then this function allocates a new packet, setting its
 * length to 0 and ensuring it has the specअगरied minimum amount of मुक्त space.
 *
 * If 'packet' is not NULL, then this function enlarges it if it doesn't
 * have the specअगरied minimum amount of मुक्त space.
 *
 */
अटल काष्ठा ipw_rx_packet *pool_allocate(काष्ठा ipw_hardware *hw,
					   काष्ठा ipw_rx_packet *packet,
					   पूर्णांक minimum_मुक्त_space)
अणु

	अगर (!packet) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&hw->lock, flags);
		अगर (!list_empty(&hw->rx_pool)) अणु
			packet = list_first_entry(&hw->rx_pool,
					काष्ठा ipw_rx_packet, queue);
			hw->rx_pool_size--;
			spin_unlock_irqrestore(&hw->lock, flags);
			list_del(&packet->queue);
		पूर्ण अन्यथा अणु
			स्थिर पूर्णांक min_capacity =
				ipwireless_ppp_mru(hw->network) + 2;
			पूर्णांक new_capacity;

			spin_unlock_irqrestore(&hw->lock, flags);
			new_capacity =
				(minimum_मुक्त_space > min_capacity
				 ? minimum_मुक्त_space
				 : min_capacity);
			packet = kदो_स्मृति(माप(काष्ठा ipw_rx_packet)
					+ new_capacity, GFP_ATOMIC);
			अगर (!packet)
				वापस शून्य;
			packet->capacity = new_capacity;
		पूर्ण
		packet->length = 0;
	पूर्ण

	अगर (packet->length + minimum_मुक्त_space > packet->capacity) अणु
		काष्ठा ipw_rx_packet *old_packet = packet;

		packet = kदो_स्मृति(माप(काष्ठा ipw_rx_packet) +
				old_packet->length + minimum_मुक्त_space,
				GFP_ATOMIC);
		अगर (!packet) अणु
			kमुक्त(old_packet);
			वापस शून्य;
		पूर्ण
		स_नकल(packet, old_packet,
				माप(काष्ठा ipw_rx_packet)
					+ old_packet->length);
		packet->capacity = old_packet->length + minimum_मुक्त_space;
		kमुक्त(old_packet);
	पूर्ण

	वापस packet;
पूर्ण

अटल व्योम pool_मुक्त(काष्ठा ipw_hardware *hw, काष्ठा ipw_rx_packet *packet)
अणु
	अगर (hw->rx_pool_size > 6)
		kमुक्त(packet);
	अन्यथा अणु
		hw->rx_pool_size++;
		list_add(&packet->queue, &hw->rx_pool);
	पूर्ण
पूर्ण

अटल व्योम queue_received_packet(काष्ठा ipw_hardware *hw,
				  अचिन्हित पूर्णांक protocol,
				  अचिन्हित पूर्णांक address,
				  स्थिर अचिन्हित अक्षर *data, पूर्णांक length,
				  पूर्णांक is_last)
अणु
	अचिन्हित पूर्णांक channel_idx = address - 1;
	काष्ठा ipw_rx_packet *packet = शून्य;
	अचिन्हित दीर्घ flags;

	/* Discard packet अगर channel index is out of range. */
	अगर (channel_idx >= NL_NUM_OF_ADDRESSES) अणु
		prपूर्णांकk(KERN_INFO IPWIRELESS_PCCARD_NAME
		       ": data packet has bad address %u\n", address);
		वापस;
	पूर्ण

	/*
	 * ->packet_assembler is safe to touch unlocked, this is the only place
	 */
	अगर (protocol == TL_PROTOCOLID_COM_DATA) अणु
		काष्ठा ipw_rx_packet **assem =
			&hw->packet_assembler[channel_idx];

		/*
		 * Create a new packet, or assembler alपढ़ोy contains one
		 * enlarge it by 'length' bytes.
		 */
		(*assem) = pool_allocate(hw, *assem, length);
		अगर (!(*assem)) अणु
			prपूर्णांकk(KERN_ERR IPWIRELESS_PCCARD_NAME
				": no memory for incoming data packet, dropped!\n");
			वापस;
		पूर्ण
		(*assem)->protocol = protocol;
		(*assem)->channel_idx = channel_idx;

		/* Append this packet data onto existing data. */
		स_नकल((अचिन्हित अक्षर *)(*assem) +
			       माप(काष्ठा ipw_rx_packet)
				+ (*assem)->length, data, length);
		(*assem)->length += length;
		अगर (is_last) अणु
			packet = *assem;
			*assem = शून्य;
			/* Count queued DATA bytes only */
			spin_lock_irqsave(&hw->lock, flags);
			hw->rx_bytes_queued += packet->length;
			spin_unlock_irqrestore(&hw->lock, flags);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* If it's a CTRL packet, don't assemble, just queue it. */
		packet = pool_allocate(hw, शून्य, length);
		अगर (!packet) अणु
			prपूर्णांकk(KERN_ERR IPWIRELESS_PCCARD_NAME
				": no memory for incoming ctrl packet, dropped!\n");
			वापस;
		पूर्ण
		packet->protocol = protocol;
		packet->channel_idx = channel_idx;
		स_नकल((अचिन्हित अक्षर *)packet + माप(काष्ठा ipw_rx_packet),
				data, length);
		packet->length = length;
	पूर्ण

	/*
	 * If this is the last packet, then send the assembled packet on to the
	 * network layer.
	 */
	अगर (packet) अणु
		spin_lock_irqsave(&hw->lock, flags);
		list_add_tail(&packet->queue, &hw->rx_queue);
		/* Block reception of incoming packets अगर queue is full. */
		hw->blocking_rx =
			(hw->rx_bytes_queued >= IPWIRELESS_RX_QUEUE_SIZE);

		spin_unlock_irqrestore(&hw->lock, flags);
		schedule_work(&hw->work_rx);
	पूर्ण
पूर्ण

/*
 * Workqueue callback
 */
अटल व्योम ipw_receive_data_work(काष्ठा work_काष्ठा *work_rx)
अणु
	काष्ठा ipw_hardware *hw =
	    container_of(work_rx, काष्ठा ipw_hardware, work_rx);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hw->lock, flags);
	जबतक (!list_empty(&hw->rx_queue)) अणु
		काष्ठा ipw_rx_packet *packet =
			list_first_entry(&hw->rx_queue,
					काष्ठा ipw_rx_packet, queue);

		अगर (hw->shutting_करोwn)
			अवरोध;
		list_del(&packet->queue);

		/*
		 * Note: ipwireless_network_packet_received must be called in a
		 * process context (i.e. via schedule_work) because the tty
		 * output code can sleep in the tty_flip_buffer_push call.
		 */
		अगर (packet->protocol == TL_PROTOCOLID_COM_DATA) अणु
			अगर (hw->network != शून्य) अणु
				/* If the network hasn't been disconnected. */
				spin_unlock_irqrestore(&hw->lock, flags);
				/*
				 * This must run unlocked due to tty processing
				 * and mutex locking
				 */
				ipwireless_network_packet_received(
						hw->network,
						packet->channel_idx,
						(अचिन्हित अक्षर *)packet
						+ माप(काष्ठा ipw_rx_packet),
						packet->length);
				spin_lock_irqsave(&hw->lock, flags);
			पूर्ण
			/* Count queued DATA bytes only */
			hw->rx_bytes_queued -= packet->length;
		पूर्ण अन्यथा अणु
			/*
			 * This is safe to be called locked, callchain करोes
			 * not block
			 */
			handle_received_CTRL_packet(hw, packet->channel_idx,
					(अचिन्हित अक्षर *)packet
					+ माप(काष्ठा ipw_rx_packet),
					packet->length);
		पूर्ण
		pool_मुक्त(hw, packet);
		/*
		 * Unblock reception of incoming packets अगर queue is no दीर्घer
		 * full.
		 */
		hw->blocking_rx =
			hw->rx_bytes_queued >= IPWIRELESS_RX_QUEUE_SIZE;
		अगर (hw->shutting_करोwn)
			अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&hw->lock, flags);
पूर्ण

अटल व्योम handle_received_CTRL_packet(काष्ठा ipw_hardware *hw,
					अचिन्हित पूर्णांक channel_idx,
					स्थिर अचिन्हित अक्षर *data, पूर्णांक len)
अणु
	स्थिर काष्ठा ipw_control_packet_body *body =
		(स्थिर काष्ठा ipw_control_packet_body *) data;
	अचिन्हित पूर्णांक changed_mask;

	अगर (len != माप(काष्ठा ipw_control_packet_body)) अणु
		prपूर्णांकk(KERN_INFO IPWIRELESS_PCCARD_NAME
		       ": control packet was %d bytes - wrong size!\n",
		       len);
		वापस;
	पूर्ण

	चयन (body->sig_no) अणु
	हाल COMCTRL_CTS:
		changed_mask = IPW_CONTROL_LINE_CTS;
		अवरोध;
	हाल COMCTRL_DCD:
		changed_mask = IPW_CONTROL_LINE_DCD;
		अवरोध;
	हाल COMCTRL_DSR:
		changed_mask = IPW_CONTROL_LINE_DSR;
		अवरोध;
	हाल COMCTRL_RI:
		changed_mask = IPW_CONTROL_LINE_RI;
		अवरोध;
	शेष:
		changed_mask = 0;
	पूर्ण

	अगर (changed_mask != 0) अणु
		अगर (body->value)
			hw->control_lines[channel_idx] |= changed_mask;
		अन्यथा
			hw->control_lines[channel_idx] &= ~changed_mask;
		अगर (hw->network)
			ipwireless_network_notअगरy_control_line_change(
					hw->network,
					channel_idx,
					hw->control_lines[channel_idx],
					changed_mask);
	पूर्ण
पूर्ण

अटल व्योम handle_received_packet(काष्ठा ipw_hardware *hw,
				   स्थिर जोड़ nl_packet *packet,
				   अचिन्हित लघु len)
अणु
	अचिन्हित पूर्णांक protocol = packet->hdr.protocol;
	अचिन्हित पूर्णांक address = packet->hdr.address;
	अचिन्हित पूर्णांक header_length;
	स्थिर अचिन्हित अक्षर *data;
	अचिन्हित पूर्णांक data_len;
	पूर्णांक is_last = packet->hdr.packet_rank & NL_LAST_PACKET;

	अगर (packet->hdr.packet_rank & NL_FIRST_PACKET)
		header_length = NL_FIRST_PACKET_HEADER_SIZE;
	अन्यथा
		header_length = NL_FOLLOWING_PACKET_HEADER_SIZE;

	data = packet->rawpkt + header_length;
	data_len = len - header_length;
	चयन (protocol) अणु
	हाल TL_PROTOCOLID_COM_DATA:
	हाल TL_PROTOCOLID_COM_CTRL:
		queue_received_packet(hw, protocol, address, data, data_len,
				is_last);
		अवरोध;
	हाल TL_PROTOCOLID_SETUP:
		handle_received_SETUP_packet(hw, address, data, data_len,
				is_last);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम acknowledge_data_पढ़ो(काष्ठा ipw_hardware *hw)
अणु
	अगर (hw->hw_version == HW_VERSION_1)
		outw(DCR_RXDONE, hw->base_port + IODCR);
	अन्यथा
		ग_लिखोw(MEMRX_PCINTACKK,
				&hw->memory_info_regs->memreg_pc_पूर्णांकerrupt_ack);
पूर्ण

/*
 * Retrieve a packet from the IPW hardware.
 */
अटल व्योम करो_receive_packet(काष्ठा ipw_hardware *hw)
अणु
	अचिन्हित len;
	अचिन्हित i;
	अचिन्हित अक्षर pkt[LL_MTU_MAX];

	start_timing();

	अगर (hw->hw_version == HW_VERSION_1) अणु
		len = inw(hw->base_port + IODRR);
		अगर (len > hw->ll_mtu) अणु
			prपूर्णांकk(KERN_INFO IPWIRELESS_PCCARD_NAME
			       ": received a packet of %u bytes - longer than the MTU!\n", len);
			outw(DCR_RXDONE | DCR_RXRESET, hw->base_port + IODCR);
			वापस;
		पूर्ण

		क्रम (i = 0; i < len; i += 2) अणु
			__le16 raw_data = inw(hw->base_port + IODRR);
			अचिन्हित लघु data = le16_to_cpu(raw_data);

			pkt[i] = (अचिन्हित अक्षर) data;
			pkt[i + 1] = (अचिन्हित अक्षर) (data >> 8);
		पूर्ण
	पूर्ण अन्यथा अणु
		len = inw(hw->base_port);
		अगर (len > hw->ll_mtu) अणु
			prपूर्णांकk(KERN_INFO IPWIRELESS_PCCARD_NAME
			       ": received a packet of %u bytes - longer than the MTU!\n", len);
			ग_लिखोw(MEMRX_PCINTACKK,
				&hw->memory_info_regs->memreg_pc_पूर्णांकerrupt_ack);
			वापस;
		पूर्ण

		क्रम (i = 0; i < len; i += 2) अणु
			__le16 raw_data = inw(hw->base_port);
			अचिन्हित लघु data = le16_to_cpu(raw_data);

			pkt[i] = (अचिन्हित अक्षर) data;
			pkt[i + 1] = (अचिन्हित अक्षर) (data >> 8);
		पूर्ण

		जबतक ((i & 3) != 2) अणु
			inw(hw->base_port);
			i += 2;
		पूर्ण
	पूर्ण

	acknowledge_data_पढ़ो(hw);

	swap_packet_bitfield_from_le(pkt);

	अगर (ipwireless_debug)
		dump_data_bytes("recv", pkt, len);

	handle_received_packet(hw, (जोड़ nl_packet *) pkt, len);

	end_पढ़ो_timing(len);
पूर्ण

अटल पूर्णांक get_current_packet_priority(काष्ठा ipw_hardware *hw)
अणु
	/*
	 * If we're initializing, don't send anything of higher priority than
	 * PRIO_SETUP.  The network layer thereक्रमe need not care about
	 * hardware initialization - any of its stuff will simply be queued
	 * until setup is complete.
	 */
	वापस (hw->to_setup || hw->initializing
			? PRIO_SETUP + 1 : NL_NUM_OF_PRIORITIES);
पूर्ण

/*
 * वापस 1 अगर something has been received from hw
 */
अटल पूर्णांक get_packets_from_hw(काष्ठा ipw_hardware *hw)
अणु
	पूर्णांक received = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hw->lock, flags);
	जबतक (hw->rx_पढ़ोy && !hw->blocking_rx) अणु
		received = 1;
		hw->rx_पढ़ोy--;
		spin_unlock_irqrestore(&hw->lock, flags);

		करो_receive_packet(hw);

		spin_lock_irqsave(&hw->lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&hw->lock, flags);

	वापस received;
पूर्ण

/*
 * Send pending packet up to given priority, prioritize SETUP data until
 * hardware is fully setup.
 *
 * वापस 1 अगर more packets can be sent
 */
अटल पूर्णांक send_pending_packet(काष्ठा ipw_hardware *hw, पूर्णांक priority_limit)
अणु
	पूर्णांक more_to_send = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hw->lock, flags);
	अगर (hw->tx_queued && hw->tx_पढ़ोy) अणु
		पूर्णांक priority;
		काष्ठा ipw_tx_packet *packet = शून्य;

		/* Pick a packet */
		क्रम (priority = 0; priority < priority_limit; priority++) अणु
			अगर (!list_empty(&hw->tx_queue[priority])) अणु
				packet = list_first_entry(
						&hw->tx_queue[priority],
						काष्ठा ipw_tx_packet,
						queue);

				hw->tx_queued--;
				list_del(&packet->queue);

				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!packet) अणु
			hw->tx_queued = 0;
			spin_unlock_irqrestore(&hw->lock, flags);
			वापस 0;
		पूर्ण

		spin_unlock_irqrestore(&hw->lock, flags);

		/* Send */
		करो_send_packet(hw, packet);

		/* Check अगर more to send */
		spin_lock_irqsave(&hw->lock, flags);
		क्रम (priority = 0; priority < priority_limit; priority++)
			अगर (!list_empty(&hw->tx_queue[priority])) अणु
				more_to_send = 1;
				अवरोध;
			पूर्ण

		अगर (!more_to_send)
			hw->tx_queued = 0;
	पूर्ण
	spin_unlock_irqrestore(&hw->lock, flags);

	वापस more_to_send;
पूर्ण

/*
 * Send and receive all queued packets.
 */
अटल व्योम ipwireless_करो_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ipw_hardware *hw = from_tasklet(hw, t, tasklet);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hw->lock, flags);
	अगर (hw->shutting_करोwn) अणु
		spin_unlock_irqrestore(&hw->lock, flags);
		वापस;
	पूर्ण

	अगर (hw->to_setup == 1) अणु
		/*
		 * Initial setup data sent to hardware
		 */
		hw->to_setup = 2;
		spin_unlock_irqrestore(&hw->lock, flags);

		ipw_setup_hardware(hw);
		ipw_send_setup_packet(hw);

		send_pending_packet(hw, PRIO_SETUP + 1);
		get_packets_from_hw(hw);
	पूर्ण अन्यथा अणु
		पूर्णांक priority_limit = get_current_packet_priority(hw);
		पूर्णांक again;

		spin_unlock_irqrestore(&hw->lock, flags);

		करो अणु
			again = send_pending_packet(hw, priority_limit);
			again |= get_packets_from_hw(hw);
		पूर्ण जबतक (again);
	पूर्ण
पूर्ण

/*
 * वापस true अगर the card is physically present.
 */
अटल पूर्णांक is_card_present(काष्ठा ipw_hardware *hw)
अणु
	अगर (hw->hw_version == HW_VERSION_1)
		वापस inw(hw->base_port + IOIR) != 0xFFFF;
	अन्यथा
		वापस पढ़ोl(&hw->memory_info_regs->memreg_card_present) ==
		    CARD_PRESENT_VALUE;
पूर्ण

अटल irqवापस_t ipwireless_handle_v1_पूर्णांकerrupt(पूर्णांक irq,
						  काष्ठा ipw_hardware *hw)
अणु
	अचिन्हित लघु irqn;

	irqn = inw(hw->base_port + IOIR);

	/* Check अगर card is present */
	अगर (irqn == 0xFFFF)
		वापस IRQ_NONE;
	अन्यथा अगर (irqn != 0) अणु
		अचिन्हित लघु ack = 0;
		अचिन्हित दीर्घ flags;

		/* Transmit complete. */
		अगर (irqn & IR_TXINTR) अणु
			ack |= IR_TXINTR;
			spin_lock_irqsave(&hw->lock, flags);
			hw->tx_पढ़ोy = 1;
			spin_unlock_irqrestore(&hw->lock, flags);
		पूर्ण
		/* Received data */
		अगर (irqn & IR_RXINTR) अणु
			ack |= IR_RXINTR;
			spin_lock_irqsave(&hw->lock, flags);
			hw->rx_पढ़ोy++;
			spin_unlock_irqrestore(&hw->lock, flags);
		पूर्ण
		अगर (ack != 0) अणु
			outw(ack, hw->base_port + IOIR);
			tasklet_schedule(&hw->tasklet);
		पूर्ण
		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

अटल व्योम acknowledge_pcmcia_पूर्णांकerrupt(काष्ठा ipw_hardware *hw)
अणु
	अचिन्हित लघु csr = पढ़ोw(&hw->memregs_CCR->reg_config_and_status);

	csr &= 0xfffd;
	ग_लिखोw(csr, &hw->memregs_CCR->reg_config_and_status);
पूर्ण

अटल irqवापस_t ipwireless_handle_v2_v3_पूर्णांकerrupt(पूर्णांक irq,
						     काष्ठा ipw_hardware *hw)
अणु
	पूर्णांक tx = 0;
	पूर्णांक rx = 0;
	पूर्णांक rx_repeat = 0;
	पूर्णांक try_mem_tx_old;
	अचिन्हित दीर्घ flags;

	करो अणु

	अचिन्हित लघु memtx = पढ़ोw(hw->memreg_tx);
	अचिन्हित लघु memtx_serial;
	अचिन्हित लघु memrxकरोne =
		पढ़ोw(&hw->memory_info_regs->memreg_rx_करोne);

	try_mem_tx_old = 0;

	/* check whether the पूर्णांकerrupt was generated by ipwireless card */
	अगर (!(memtx & MEMTX_TX) && !(memrxकरोne & MEMRX_RX_DONE)) अणु

		/* check अगर the card uses memreg_tx_old रेजिस्टर */
		अगर (hw->memreg_tx == &hw->memory_info_regs->memreg_tx_new) अणु
			memtx = पढ़ोw(&hw->memory_info_regs->memreg_tx_old);
			अगर (memtx & MEMTX_TX) अणु
				prपूर्णांकk(KERN_INFO IPWIRELESS_PCCARD_NAME
					": Using memreg_tx_old\n");
				hw->memreg_tx =
					&hw->memory_info_regs->memreg_tx_old;
			पूर्ण अन्यथा अणु
				वापस IRQ_NONE;
			पूर्ण
		पूर्ण अन्यथा
			वापस IRQ_NONE;
	पूर्ण

	/*
	 * See अगर the card is physically present. Note that जबतक it is
	 * घातering up, it appears not to be present.
	 */
	अगर (!is_card_present(hw)) अणु
		acknowledge_pcmcia_पूर्णांकerrupt(hw);
		वापस IRQ_HANDLED;
	पूर्ण

	memtx_serial = memtx & (अचिन्हित लघु) 0xff00;
	अगर (memtx & MEMTX_TX) अणु
		ग_लिखोw(memtx_serial, hw->memreg_tx);

		अगर (hw->serial_number_detected) अणु
			अगर (memtx_serial != hw->last_memtx_serial) अणु
				hw->last_memtx_serial = memtx_serial;
				spin_lock_irqsave(&hw->lock, flags);
				hw->rx_पढ़ोy++;
				spin_unlock_irqrestore(&hw->lock, flags);
				rx = 1;
			पूर्ण अन्यथा
				/* Ignore 'Timer Recovery' duplicates. */
				rx_repeat = 1;
		पूर्ण अन्यथा अणु
			/*
			 * If a non-zero serial number is seen, then enable
			 * serial number checking.
			 */
			अगर (memtx_serial != 0) अणु
				hw->serial_number_detected = 1;
				prपूर्णांकk(KERN_DEBUG IPWIRELESS_PCCARD_NAME
					": memreg_tx serial num detected\n");

				spin_lock_irqsave(&hw->lock, flags);
				hw->rx_पढ़ोy++;
				spin_unlock_irqrestore(&hw->lock, flags);
			पूर्ण
			rx = 1;
		पूर्ण
	पूर्ण
	अगर (memrxकरोne & MEMRX_RX_DONE) अणु
		ग_लिखोw(0, &hw->memory_info_regs->memreg_rx_करोne);
		spin_lock_irqsave(&hw->lock, flags);
		hw->tx_पढ़ोy = 1;
		spin_unlock_irqrestore(&hw->lock, flags);
		tx = 1;
	पूर्ण
	अगर (tx)
		ग_लिखोw(MEMRX_PCINTACKK,
				&hw->memory_info_regs->memreg_pc_पूर्णांकerrupt_ack);

	acknowledge_pcmcia_पूर्णांकerrupt(hw);

	अगर (tx || rx)
		tasklet_schedule(&hw->tasklet);
	अन्यथा अगर (!rx_repeat) अणु
		अगर (hw->memreg_tx == &hw->memory_info_regs->memreg_tx_new) अणु
			अगर (hw->serial_number_detected)
				prपूर्णांकk(KERN_WARNING IPWIRELESS_PCCARD_NAME
					": spurious interrupt - new_tx mode\n");
			अन्यथा अणु
				prपूर्णांकk(KERN_WARNING IPWIRELESS_PCCARD_NAME
					": no valid memreg_tx value - switching to the old memreg_tx\n");
				hw->memreg_tx =
					&hw->memory_info_regs->memreg_tx_old;
				try_mem_tx_old = 1;
			पूर्ण
		पूर्ण अन्यथा
			prपूर्णांकk(KERN_WARNING IPWIRELESS_PCCARD_NAME
					": spurious interrupt - old_tx mode\n");
	पूर्ण

	पूर्ण जबतक (try_mem_tx_old == 1);

	वापस IRQ_HANDLED;
पूर्ण

irqवापस_t ipwireless_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ipw_dev *ipw = dev_id;

	अगर (ipw->hardware->hw_version == HW_VERSION_1)
		वापस ipwireless_handle_v1_पूर्णांकerrupt(irq, ipw->hardware);
	अन्यथा
		वापस ipwireless_handle_v2_v3_पूर्णांकerrupt(irq, ipw->hardware);
पूर्ण

अटल व्योम flush_packets_to_hw(काष्ठा ipw_hardware *hw)
अणु
	पूर्णांक priority_limit;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hw->lock, flags);
	priority_limit = get_current_packet_priority(hw);
	spin_unlock_irqrestore(&hw->lock, flags);

	जबतक (send_pending_packet(hw, priority_limit));
पूर्ण

अटल व्योम send_packet(काष्ठा ipw_hardware *hw, पूर्णांक priority,
			काष्ठा ipw_tx_packet *packet)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hw->lock, flags);
	list_add_tail(&packet->queue, &hw->tx_queue[priority]);
	hw->tx_queued++;
	spin_unlock_irqrestore(&hw->lock, flags);

	flush_packets_to_hw(hw);
पूर्ण

/* Create data packet, non-atomic allocation */
अटल व्योम *alloc_data_packet(पूर्णांक data_size,
				अचिन्हित अक्षर dest_addr,
				अचिन्हित अक्षर protocol)
अणु
	काष्ठा ipw_tx_packet *packet = kzalloc(
			माप(काष्ठा ipw_tx_packet) + data_size,
			GFP_ATOMIC);

	अगर (!packet)
		वापस शून्य;

	INIT_LIST_HEAD(&packet->queue);
	packet->dest_addr = dest_addr;
	packet->protocol = protocol;
	packet->length = data_size;

	वापस packet;
पूर्ण

अटल व्योम *alloc_ctrl_packet(पूर्णांक header_size,
			       अचिन्हित अक्षर dest_addr,
			       अचिन्हित अक्षर protocol,
			       अचिन्हित अक्षर sig_no)
अणु
	/*
	 * sig_no is located right after ipw_tx_packet काष्ठा in every
	 * CTRL or SETUP packets, we can use ipw_control_packet as a
	 * common काष्ठा
	 */
	काष्ठा ipw_control_packet *packet = kzalloc(header_size, GFP_ATOMIC);

	अगर (!packet)
		वापस शून्य;

	INIT_LIST_HEAD(&packet->header.queue);
	packet->header.dest_addr = dest_addr;
	packet->header.protocol = protocol;
	packet->header.length = header_size - माप(काष्ठा ipw_tx_packet);
	packet->body.sig_no = sig_no;

	वापस packet;
पूर्ण

पूर्णांक ipwireless_send_packet(काष्ठा ipw_hardware *hw, अचिन्हित पूर्णांक channel_idx,
			    स्थिर अचिन्हित अक्षर *data, अचिन्हित पूर्णांक length,
			    व्योम (*callback) (व्योम *cb, अचिन्हित पूर्णांक length),
			    व्योम *callback_data)
अणु
	काष्ठा ipw_tx_packet *packet;

	packet = alloc_data_packet(length, (channel_idx + 1),
			TL_PROTOCOLID_COM_DATA);
	अगर (!packet)
		वापस -ENOMEM;
	packet->packet_callback = callback;
	packet->callback_data = callback_data;
	स_नकल((अचिन्हित अक्षर *) packet + माप(काष्ठा ipw_tx_packet), data,
			length);

	send_packet(hw, PRIO_DATA, packet);
	वापस 0;
पूर्ण

अटल पूर्णांक set_control_line(काष्ठा ipw_hardware *hw, पूर्णांक prio,
			   अचिन्हित पूर्णांक channel_idx, पूर्णांक line, पूर्णांक state)
अणु
	काष्ठा ipw_control_packet *packet;
	पूर्णांक protocolid = TL_PROTOCOLID_COM_CTRL;

	अगर (prio == PRIO_SETUP)
		protocolid = TL_PROTOCOLID_SETUP;

	packet = alloc_ctrl_packet(माप(काष्ठा ipw_control_packet),
			(channel_idx + 1), protocolid, line);
	अगर (!packet)
		वापस -ENOMEM;
	packet->header.length = माप(काष्ठा ipw_control_packet_body);
	packet->body.value = (state == 0 ? 0 : 1);
	send_packet(hw, prio, &packet->header);
	वापस 0;
पूर्ण


अटल पूर्णांक set_DTR(काष्ठा ipw_hardware *hw, पूर्णांक priority,
		   अचिन्हित पूर्णांक channel_idx, पूर्णांक state)
अणु
	अगर (state != 0)
		hw->control_lines[channel_idx] |= IPW_CONTROL_LINE_DTR;
	अन्यथा
		hw->control_lines[channel_idx] &= ~IPW_CONTROL_LINE_DTR;

	वापस set_control_line(hw, priority, channel_idx, COMCTRL_DTR, state);
पूर्ण

अटल पूर्णांक set_RTS(काष्ठा ipw_hardware *hw, पूर्णांक priority,
		   अचिन्हित पूर्णांक channel_idx, पूर्णांक state)
अणु
	अगर (state != 0)
		hw->control_lines[channel_idx] |= IPW_CONTROL_LINE_RTS;
	अन्यथा
		hw->control_lines[channel_idx] &= ~IPW_CONTROL_LINE_RTS;

	वापस set_control_line(hw, priority, channel_idx, COMCTRL_RTS, state);
पूर्ण

पूर्णांक ipwireless_set_DTR(काष्ठा ipw_hardware *hw, अचिन्हित पूर्णांक channel_idx,
		       पूर्णांक state)
अणु
	वापस set_DTR(hw, PRIO_CTRL, channel_idx, state);
पूर्ण

पूर्णांक ipwireless_set_RTS(काष्ठा ipw_hardware *hw, अचिन्हित पूर्णांक channel_idx,
		       पूर्णांक state)
अणु
	वापस set_RTS(hw, PRIO_CTRL, channel_idx, state);
पूर्ण

काष्ठा ipw_setup_get_version_query_packet अणु
	काष्ठा ipw_tx_packet header;
	काष्ठा tl_setup_get_version_qry body;
पूर्ण;

काष्ठा ipw_setup_config_packet अणु
	काष्ठा ipw_tx_packet header;
	काष्ठा tl_setup_config_msg body;
पूर्ण;

काष्ठा ipw_setup_config_करोne_packet अणु
	काष्ठा ipw_tx_packet header;
	काष्ठा tl_setup_config_करोne_msg body;
पूर्ण;

काष्ठा ipw_setup_खोलो_packet अणु
	काष्ठा ipw_tx_packet header;
	काष्ठा tl_setup_खोलो_msg body;
पूर्ण;

काष्ठा ipw_setup_info_packet अणु
	काष्ठा ipw_tx_packet header;
	काष्ठा tl_setup_info_msg body;
पूर्ण;

काष्ठा ipw_setup_reboot_msg_ack अणु
	काष्ठा ipw_tx_packet header;
	काष्ठा TlSetupRebootMsgAck body;
पूर्ण;

/* This handles the actual initialization of the card */
अटल व्योम __handle_setup_get_version_rsp(काष्ठा ipw_hardware *hw)
अणु
	काष्ठा ipw_setup_config_packet *config_packet;
	काष्ठा ipw_setup_config_करोne_packet *config_करोne_packet;
	काष्ठा ipw_setup_खोलो_packet *खोलो_packet;
	काष्ठा ipw_setup_info_packet *info_packet;
	पूर्णांक port;
	अचिन्हित पूर्णांक channel_idx;

	/* generate config packet */
	क्रम (port = 1; port <= NL_NUM_OF_ADDRESSES; port++) अणु
		config_packet = alloc_ctrl_packet(
				माप(काष्ठा ipw_setup_config_packet),
				ADDR_SETUP_PROT,
				TL_PROTOCOLID_SETUP,
				TL_SETUP_SIGNO_CONFIG_MSG);
		अगर (!config_packet)
			जाओ निकास_nomem;
		config_packet->header.length = माप(काष्ठा tl_setup_config_msg);
		config_packet->body.port_no = port;
		config_packet->body.prio_data = PRIO_DATA;
		config_packet->body.prio_ctrl = PRIO_CTRL;
		send_packet(hw, PRIO_SETUP, &config_packet->header);
	पूर्ण
	config_करोne_packet = alloc_ctrl_packet(
			माप(काष्ठा ipw_setup_config_करोne_packet),
			ADDR_SETUP_PROT,
			TL_PROTOCOLID_SETUP,
			TL_SETUP_SIGNO_CONFIG_DONE_MSG);
	अगर (!config_करोne_packet)
		जाओ निकास_nomem;
	config_करोne_packet->header.length = माप(काष्ठा tl_setup_config_करोne_msg);
	send_packet(hw, PRIO_SETUP, &config_करोne_packet->header);

	/* generate खोलो packet */
	क्रम (port = 1; port <= NL_NUM_OF_ADDRESSES; port++) अणु
		खोलो_packet = alloc_ctrl_packet(
				माप(काष्ठा ipw_setup_खोलो_packet),
				ADDR_SETUP_PROT,
				TL_PROTOCOLID_SETUP,
				TL_SETUP_SIGNO_OPEN_MSG);
		अगर (!खोलो_packet)
			जाओ निकास_nomem;
		खोलो_packet->header.length = माप(काष्ठा tl_setup_खोलो_msg);
		खोलो_packet->body.port_no = port;
		send_packet(hw, PRIO_SETUP, &खोलो_packet->header);
	पूर्ण
	क्रम (channel_idx = 0;
			channel_idx < NL_NUM_OF_ADDRESSES; channel_idx++) अणु
		पूर्णांक ret;

		ret = set_DTR(hw, PRIO_SETUP, channel_idx,
			(hw->control_lines[channel_idx] &
			 IPW_CONTROL_LINE_DTR) != 0);
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR IPWIRELESS_PCCARD_NAME
					": error setting DTR (%d)\n", ret);
			वापस;
		पूर्ण

		ret = set_RTS(hw, PRIO_SETUP, channel_idx,
			(hw->control_lines [channel_idx] &
			 IPW_CONTROL_LINE_RTS) != 0);
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR IPWIRELESS_PCCARD_NAME
					": error setting RTS (%d)\n", ret);
			वापस;
		पूर्ण
	पूर्ण
	/*
	 * For NDIS we assume that we are using sync PPP frames, क्रम COM async.
	 * This driver uses NDIS mode too. We करोn't bother with translation
	 * from async -> sync PPP.
	 */
	info_packet = alloc_ctrl_packet(माप(काष्ठा ipw_setup_info_packet),
			ADDR_SETUP_PROT,
			TL_PROTOCOLID_SETUP,
			TL_SETUP_SIGNO_INFO_MSG);
	अगर (!info_packet)
		जाओ निकास_nomem;
	info_packet->header.length = माप(काष्ठा tl_setup_info_msg);
	info_packet->body.driver_type = NDISWAN_DRIVER;
	info_packet->body.major_version = NDISWAN_DRIVER_MAJOR_VERSION;
	info_packet->body.minor_version = NDISWAN_DRIVER_MINOR_VERSION;
	send_packet(hw, PRIO_SETUP, &info_packet->header);

	/* Initialization is now complete, so we clear the 'to_setup' flag */
	hw->to_setup = 0;

	वापस;

निकास_nomem:
	prपूर्णांकk(KERN_ERR IPWIRELESS_PCCARD_NAME
			": not enough memory to alloc control packet\n");
	hw->to_setup = -1;
पूर्ण

अटल व्योम handle_setup_get_version_rsp(काष्ठा ipw_hardware *hw,
		अचिन्हित अक्षर vers_no)
अणु
	del_समयr(&hw->setup_समयr);
	hw->initializing = 0;
	prपूर्णांकk(KERN_INFO IPWIRELESS_PCCARD_NAME ": card is ready.\n");

	अगर (vers_no == TL_SETUP_VERSION)
		__handle_setup_get_version_rsp(hw);
	अन्यथा
		prपूर्णांकk(KERN_ERR IPWIRELESS_PCCARD_NAME
				": invalid hardware version no %u\n",
				(अचिन्हित पूर्णांक) vers_no);
पूर्ण

अटल व्योम ipw_send_setup_packet(काष्ठा ipw_hardware *hw)
अणु
	काष्ठा ipw_setup_get_version_query_packet *ver_packet;

	ver_packet = alloc_ctrl_packet(
			माप(काष्ठा ipw_setup_get_version_query_packet),
			ADDR_SETUP_PROT, TL_PROTOCOLID_SETUP,
			TL_SETUP_SIGNO_GET_VERSION_QRY);
	अगर (!ver_packet)
		वापस;
	ver_packet->header.length = माप(काष्ठा tl_setup_get_version_qry);

	/*
	 * Response is handled in handle_received_SETUP_packet
	 */
	send_packet(hw, PRIO_SETUP, &ver_packet->header);
पूर्ण

अटल व्योम handle_received_SETUP_packet(काष्ठा ipw_hardware *hw,
					 अचिन्हित पूर्णांक address,
					 स्थिर अचिन्हित अक्षर *data, पूर्णांक len,
					 पूर्णांक is_last)
अणु
	स्थिर जोड़ ipw_setup_rx_msg *rx_msg = (स्थिर जोड़ ipw_setup_rx_msg *) data;

	अगर (address != ADDR_SETUP_PROT) अणु
		prपूर्णांकk(KERN_INFO IPWIRELESS_PCCARD_NAME
		       ": setup packet has bad address %d\n", address);
		वापस;
	पूर्ण

	चयन (rx_msg->sig_no) अणु
	हाल TL_SETUP_SIGNO_GET_VERSION_RSP:
		अगर (hw->to_setup)
			handle_setup_get_version_rsp(hw,
					rx_msg->version_rsp_msg.version);
		अवरोध;

	हाल TL_SETUP_SIGNO_OPEN_MSG:
		अगर (ipwireless_debug) अणु
			अचिन्हित पूर्णांक channel_idx = rx_msg->खोलो_msg.port_no - 1;

			prपूर्णांकk(KERN_INFO IPWIRELESS_PCCARD_NAME
			       ": OPEN_MSG [channel %u] reply received\n",
			       channel_idx);
		पूर्ण
		अवरोध;

	हाल TL_SETUP_SIGNO_INFO_MSG_ACK:
		अगर (ipwireless_debug)
			prपूर्णांकk(KERN_DEBUG IPWIRELESS_PCCARD_NAME
			       ": card successfully configured as NDISWAN\n");
		अवरोध;

	हाल TL_SETUP_SIGNO_REBOOT_MSG:
		अगर (hw->to_setup)
			prपूर्णांकk(KERN_DEBUG IPWIRELESS_PCCARD_NAME
			       ": Setup not completed - ignoring reboot msg\n");
		अन्यथा अणु
			काष्ठा ipw_setup_reboot_msg_ack *packet;

			prपूर्णांकk(KERN_DEBUG IPWIRELESS_PCCARD_NAME
			       ": Acknowledging REBOOT message\n");
			packet = alloc_ctrl_packet(
					माप(काष्ठा ipw_setup_reboot_msg_ack),
					ADDR_SETUP_PROT, TL_PROTOCOLID_SETUP,
					TL_SETUP_SIGNO_REBOOT_MSG_ACK);
			अगर (!packet) अणु
				pr_err(IPWIRELESS_PCCARD_NAME
				       ": Not enough memory to send reboot packet");
				अवरोध;
			पूर्ण
			packet->header.length =
				माप(काष्ठा TlSetupRebootMsgAck);
			send_packet(hw, PRIO_SETUP, &packet->header);
			अगर (hw->reboot_callback)
				hw->reboot_callback(hw->reboot_callback_data);
		पूर्ण
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_INFO IPWIRELESS_PCCARD_NAME
		       ": unknown setup message %u received\n",
		       (अचिन्हित पूर्णांक) rx_msg->sig_no);
	पूर्ण
पूर्ण

अटल व्योम करो_बंद_hardware(काष्ठा ipw_hardware *hw)
अणु
	अचिन्हित पूर्णांक irqn;

	अगर (hw->hw_version == HW_VERSION_1) अणु
		/* Disable TX and RX पूर्णांकerrupts. */
		outw(0, hw->base_port + IOIER);

		/* Acknowledge any outstanding पूर्णांकerrupt requests */
		irqn = inw(hw->base_port + IOIR);
		अगर (irqn & IR_TXINTR)
			outw(IR_TXINTR, hw->base_port + IOIR);
		अगर (irqn & IR_RXINTR)
			outw(IR_RXINTR, hw->base_port + IOIR);

		synchronize_irq(hw->irq);
	पूर्ण
पूर्ण

काष्ठा ipw_hardware *ipwireless_hardware_create(व्योम)
अणु
	पूर्णांक i;
	काष्ठा ipw_hardware *hw =
		kzalloc(माप(काष्ठा ipw_hardware), GFP_KERNEL);

	अगर (!hw)
		वापस शून्य;

	hw->irq = -1;
	hw->initializing = 1;
	hw->tx_पढ़ोy = 1;
	hw->rx_bytes_queued = 0;
	hw->rx_pool_size = 0;
	hw->last_memtx_serial = (अचिन्हित लघु) 0xffff;
	क्रम (i = 0; i < NL_NUM_OF_PRIORITIES; i++)
		INIT_LIST_HEAD(&hw->tx_queue[i]);

	INIT_LIST_HEAD(&hw->rx_queue);
	INIT_LIST_HEAD(&hw->rx_pool);
	spin_lock_init(&hw->lock);
	tasklet_setup(&hw->tasklet, ipwireless_करो_tasklet);
	INIT_WORK(&hw->work_rx, ipw_receive_data_work);
	समयr_setup(&hw->setup_समयr, ipwireless_setup_समयr, 0);

	वापस hw;
पूर्ण

व्योम ipwireless_init_hardware_v1(काष्ठा ipw_hardware *hw,
		अचिन्हित पूर्णांक base_port,
		व्योम __iomem *attr_memory,
		व्योम __iomem *common_memory,
		पूर्णांक is_v2_card,
		व्योम (*reboot_callback) (व्योम *data),
		व्योम *reboot_callback_data)
अणु
	अगर (hw->हटाओd) अणु
		hw->हटाओd = 0;
		enable_irq(hw->irq);
	पूर्ण
	hw->base_port = base_port;
	hw->hw_version = (is_v2_card ? HW_VERSION_2 : HW_VERSION_1);
	hw->ll_mtu = (hw->hw_version == HW_VERSION_1 ? LL_MTU_V1 : LL_MTU_V2);
	hw->memregs_CCR = (काष्ठा MEMCCR __iomem *)
			((अचिन्हित लघु __iomem *) attr_memory + 0x200);
	hw->memory_info_regs = (काष्ठा MEMINFREG __iomem *) common_memory;
	hw->memreg_tx = &hw->memory_info_regs->memreg_tx_new;
	hw->reboot_callback = reboot_callback;
	hw->reboot_callback_data = reboot_callback_data;
पूर्ण

व्योम ipwireless_init_hardware_v2_v3(काष्ठा ipw_hardware *hw)
अणु
	hw->initializing = 1;
	hw->init_loops = 0;
	prपूर्णांकk(KERN_INFO IPWIRELESS_PCCARD_NAME
	       ": waiting for card to start up...\n");
	ipwireless_setup_समयr(&hw->setup_समयr);
पूर्ण

अटल व्योम ipwireless_setup_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ipw_hardware *hw = from_समयr(hw, t, setup_समयr);

	hw->init_loops++;

	अगर (hw->init_loops == TL_SETUP_MAX_VERSION_QRY &&
			hw->hw_version == HW_VERSION_2 &&
			hw->memreg_tx == &hw->memory_info_regs->memreg_tx_new) अणु
		prपूर्णांकk(KERN_INFO IPWIRELESS_PCCARD_NAME
				": failed to startup using TX2, trying TX\n");

		hw->memreg_tx = &hw->memory_info_regs->memreg_tx_old;
		hw->init_loops = 0;
	पूर्ण
	/* Give up after a certain number of retries */
	अगर (hw->init_loops == TL_SETUP_MAX_VERSION_QRY) अणु
		prपूर्णांकk(KERN_INFO IPWIRELESS_PCCARD_NAME
		       ": card failed to start up!\n");
		hw->initializing = 0;
	पूर्ण अन्यथा अणु
		/* Do not attempt to ग_लिखो to the board अगर it is not present. */
		अगर (is_card_present(hw)) अणु
			अचिन्हित दीर्घ flags;

			spin_lock_irqsave(&hw->lock, flags);
			hw->to_setup = 1;
			hw->tx_पढ़ोy = 1;
			spin_unlock_irqrestore(&hw->lock, flags);
			tasklet_schedule(&hw->tasklet);
		पूर्ण

		mod_समयr(&hw->setup_समयr,
			jअगरfies + msecs_to_jअगरfies(TL_SETUP_VERSION_QRY_TMO));
	पूर्ण
पूर्ण

/*
 * Stop any पूर्णांकerrupts from executing so that, once this function वापसs,
 * other layers of the driver can be sure they won't get any more callbacks.
 * Thus must be called on a proper process context.
 */
व्योम ipwireless_stop_पूर्णांकerrupts(काष्ठा ipw_hardware *hw)
अणु
	अगर (!hw->shutting_करोwn) अणु
		/* Tell everyone we are going करोwn. */
		hw->shutting_करोwn = 1;
		del_समयr(&hw->setup_समयr);

		/* Prevent the hardware from sending any more पूर्णांकerrupts */
		करो_बंद_hardware(hw);
	पूर्ण
पूर्ण

व्योम ipwireless_hardware_मुक्त(काष्ठा ipw_hardware *hw)
अणु
	पूर्णांक i;
	काष्ठा ipw_rx_packet *rp, *rq;
	काष्ठा ipw_tx_packet *tp, *tq;

	ipwireless_stop_पूर्णांकerrupts(hw);

	flush_work(&hw->work_rx);

	क्रम (i = 0; i < NL_NUM_OF_ADDRESSES; i++)
		kमुक्त(hw->packet_assembler[i]);

	क्रम (i = 0; i < NL_NUM_OF_PRIORITIES; i++)
		list_क्रम_each_entry_safe(tp, tq, &hw->tx_queue[i], queue) अणु
			list_del(&tp->queue);
			kमुक्त(tp);
		पूर्ण

	list_क्रम_each_entry_safe(rp, rq, &hw->rx_queue, queue) अणु
		list_del(&rp->queue);
		kमुक्त(rp);
	पूर्ण

	list_क्रम_each_entry_safe(rp, rq, &hw->rx_pool, queue) अणु
		list_del(&rp->queue);
		kमुक्त(rp);
	पूर्ण
	kमुक्त(hw);
पूर्ण

/*
 * Associate the specअगरied network with this hardware, so it will receive events
 * from it.
 */
व्योम ipwireless_associate_network(काष्ठा ipw_hardware *hw,
				  काष्ठा ipw_network *network)
अणु
	hw->network = network;
पूर्ण
