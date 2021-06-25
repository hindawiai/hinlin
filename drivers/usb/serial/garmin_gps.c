<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Garmin GPS driver
 *
 * Copyright (C) 2006-2011 Hermann Kneissel herkne@gmx.de
 *
 * The latest version of the driver can be found at
 * http://sourceक्रमge.net/projects/garmin-gps/
 *
 * This driver has been derived from v2.1 of the visor driver.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/atomic.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>

/* the mode to be set when the port ist खोलोed */
अटल पूर्णांक initial_mode = 1;

#घोषणा GARMIN_VENDOR_ID             0x091E

/*
 * Version Inक्रमmation
 */

#घोषणा VERSION_MAJOR	0
#घोषणा VERSION_MINOR	36

#घोषणा _STR(s) #s
#घोषणा _DRIVER_VERSION(a, b) "v" _STR(a) "." _STR(b)
#घोषणा DRIVER_VERSION _DRIVER_VERSION(VERSION_MAJOR, VERSION_MINOR)
#घोषणा DRIVER_AUTHOR "hermann kneissel"
#घोषणा DRIVER_DESC "garmin gps driver"

/* error codes वापसed by the driver */
#घोषणा EINVPKT	1000	/* invalid packet काष्ठाure */


/* size of the header of a packet using the usb protocol */
#घोषणा GARMIN_PKTHDR_LENGTH	12

/* max. possible size of a packet using the serial protocol */
#घोषणा MAX_SERIAL_PKT_SIZ (3 + 255 + 3)

/*  max. possible size of a packet with worst हाल stuffing */
#घोषणा MAX_SERIAL_PKT_SIZ_STUFFED (MAX_SERIAL_PKT_SIZ + 256)

/* size of a buffer able to hold a complete (no stuffing) packet
 * (the करोcument protocol करोes not contain packets with a larger
 *  size, but in theory a packet may be 64k+12 bytes - अगर in
 *  later protocol versions larger packet sizes occur, this value
 *  should be increased accordingly, so the input buffer is always
 *  large enough the store a complete packet inclusive header) */
#घोषणा GPS_IN_बफ_मान  (GARMIN_PKTHDR_LENGTH+MAX_SERIAL_PKT_SIZ)

/* size of a buffer able to hold a complete (incl. stuffing) packet */
#घोषणा GPS_OUT_बफ_मान (GARMIN_PKTHDR_LENGTH+MAX_SERIAL_PKT_SIZ_STUFFED)

/* where to place the packet id of a serial packet, so we can
 * prepend the usb-packet header without the need to move the
 * packets data */
#घोषणा GSP_INITIAL_OFFSET (GARMIN_PKTHDR_LENGTH-2)

/* max. size of incoming निजी packets (header+1 param) */
#घोषणा PRIVPKTSIZ (GARMIN_PKTHDR_LENGTH+4)

#घोषणा GARMIN_LAYERID_TRANSPORT  0
#घोषणा GARMIN_LAYERID_APPL      20
/* our own layer-id to use क्रम some control mechanisms */
#घोषणा GARMIN_LAYERID_PRIVATE	0x01106E4B

#घोषणा GARMIN_PKTID_PVT_DATA	51
#घोषणा GARMIN_PKTID_L001_COMMAND_DATA 10

#घोषणा CMND_ABORT_TRANSFER 0

/* packet ids used in निजी layer */
#घोषणा PRIV_PKTID_SET_DEBUG	1
#घोषणा PRIV_PKTID_SET_MODE	2
#घोषणा PRIV_PKTID_INFO_REQ	3
#घोषणा PRIV_PKTID_INFO_RESP	4
#घोषणा PRIV_PKTID_RESET_REQ	5
#घोषणा PRIV_PKTID_SET_DEF_MODE	6


#घोषणा ETX	0x03
#घोषणा DLE	0x10
#घोषणा ACK	0x06
#घोषणा NAK	0x15

/* काष्ठाure used to queue incoming packets */
काष्ठा garmin_packet अणु
	काष्ठा list_head  list;
	पूर्णांक               seq;
	/* the real size of the data array, always > 0 */
	पूर्णांक               size;
	__u8              data[];
पूर्ण;

/* काष्ठाure used to keep the current state of the driver */
काष्ठा garmin_data अणु
	__u8   state;
	__u16  flags;
	__u8   mode;
	__u8   count;
	__u8   pkt_id;
	__u32  serial_num;
	काष्ठा समयr_list समयr;
	काष्ठा usb_serial_port *port;
	पूर्णांक    seq_counter;
	पूर्णांक    insize;
	पूर्णांक    outsize;
	__u8   inbuffer [GPS_IN_बफ_मान];  /* tty -> usb */
	__u8   outbuffer[GPS_OUT_बफ_मान]; /* usb -> tty */
	__u8   privpkt[4*6];
	spinlock_t lock;
	काष्ठा list_head pktlist;
	काष्ठा usb_anchor ग_लिखो_urbs;
पूर्ण;


#घोषणा STATE_NEW            0
#घोषणा STATE_INITIAL_DELAY  1
#घोषणा STATE_TIMEOUT        2
#घोषणा STATE_SESSION_REQ1   3
#घोषणा STATE_SESSION_REQ2   4
#घोषणा STATE_ACTIVE         5

#घोषणा STATE_RESET	     8
#घोषणा STATE_DISCONNECTED   9
#घोषणा STATE_WAIT_TTY_ACK  10
#घोषणा STATE_GSP_WAIT_DATA 11

#घोषणा MODE_NATIVE          0
#घोषणा MODE_GARMIN_SERIAL   1

/* Flags used in garmin_data.flags: */
#घोषणा FLAGS_SESSION_REPLY_MASK  0x00C0
#घोषणा FLAGS_SESSION_REPLY1_SEEN 0x0080
#घोषणा FLAGS_SESSION_REPLY2_SEEN 0x0040
#घोषणा FLAGS_BULK_IN_ACTIVE      0x0020
#घोषणा FLAGS_BULK_IN_RESTART     0x0010
#घोषणा FLAGS_THROTTLED           0x0008
#घोषणा APP_REQ_SEEN              0x0004
#घोषणा APP_RESP_SEEN             0x0002
#घोषणा CLEAR_HALT_REQUIRED       0x0001

#घोषणा FLAGS_QUEUING             0x0100
#घोषणा FLAGS_DROP_DATA           0x0800

#घोषणा FLAGS_GSP_SKIP            0x1000
#घोषणा FLAGS_GSP_DLESEEN         0x2000






/* function prototypes */
अटल पूर्णांक gsp_next_packet(काष्ठा garmin_data *garmin_data_p);
अटल पूर्णांक garmin_ग_लिखो_bulk(काष्ठा usb_serial_port *port,
			     स्थिर अचिन्हित अक्षर *buf, पूर्णांक count,
			     पूर्णांक dismiss_ack);

/* some special packets to be send or received */
अटल अचिन्हित अक्षर स्थिर GARMIN_START_SESSION_REQ[]
	= अणु 0, 0, 0, 0,  5, 0, 0, 0, 0, 0, 0, 0 पूर्ण;
अटल अचिन्हित अक्षर स्थिर GARMIN_START_SESSION_REPLY[]
	= अणु 0, 0, 0, 0,  6, 0, 0, 0, 4, 0, 0, 0 पूर्ण;
अटल अचिन्हित अक्षर स्थिर GARMIN_BULK_IN_AVAIL_REPLY[]
	= अणु 0, 0, 0, 0,  2, 0, 0, 0, 0, 0, 0, 0 पूर्ण;
अटल अचिन्हित अक्षर स्थिर GARMIN_STOP_TRANSFER_REQ[]
	= अणु 20, 0, 0, 0,  10, 0, 0, 0, 2, 0, 0, 0, 0, 0 पूर्ण;
अटल अचिन्हित अक्षर स्थिर GARMIN_STOP_TRANSFER_REQ_V2[]
	= अणु 20, 0, 0, 0,  10, 0, 0, 0, 1, 0, 0, 0, 0 पूर्ण;

/* packets currently unused, left as करोcumentation */
#अगर 0
अटल अचिन्हित अक्षर स्थिर GARMIN_APP_LAYER_REPLY[]
	= अणु 0x14, 0, 0, 0 पूर्ण;
अटल अचिन्हित अक्षर स्थिर GARMIN_START_PVT_REQ[]
	= अणु 20, 0, 0, 0,  10, 0, 0, 0, 2, 0, 0, 0, 49, 0 पूर्ण;
अटल अचिन्हित अक्षर स्थिर GARMIN_STOP_PVT_REQ[]
	= अणु 20, 0, 0, 0,  10, 0, 0, 0, 2, 0, 0, 0, 50, 0 पूर्ण;
अटल अचिन्हित अक्षर स्थिर PRIVATE_REQ[]
	=    अणु 0x4B, 0x6E, 0x10, 0x01,  0xFF, 0, 0, 0, 0xFF, 0, 0, 0 पूर्ण;
#पूर्ण_अगर


अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	/* the same device id seems to be used by all
	   usb enabled GPS devices */
	अणु USB_DEVICE(GARMIN_VENDOR_ID, 3) पूर्ण,
	अणु पूर्ण					/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);


अटल अंतरभूत पूर्णांक getLayerId(स्थिर __u8 *usbPacket)
अणु
	वापस __le32_to_cpup((__le32 *)(usbPacket));
पूर्ण

अटल अंतरभूत पूर्णांक getPacketId(स्थिर __u8 *usbPacket)
अणु
	वापस __le32_to_cpup((__le32 *)(usbPacket+4));
पूर्ण

अटल अंतरभूत पूर्णांक getDataLength(स्थिर __u8 *usbPacket)
अणु
	वापस __le32_to_cpup((__le32 *)(usbPacket+8));
पूर्ण


/*
 * check अगर the usb-packet in buf contains an पात-transfer command.
 * (अगर yes, all queued data will be dropped)
 */
अटल अंतरभूत पूर्णांक isAbortTrfCmnd(स्थिर अचिन्हित अक्षर *buf)
अणु
	अगर (स_भेद(buf, GARMIN_STOP_TRANSFER_REQ,
			माप(GARMIN_STOP_TRANSFER_REQ)) == 0 ||
	    स_भेद(buf, GARMIN_STOP_TRANSFER_REQ_V2,
			माप(GARMIN_STOP_TRANSFER_REQ_V2)) == 0)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण



अटल व्योम send_to_tty(काष्ठा usb_serial_port *port,
			अक्षर *data, अचिन्हित पूर्णांक actual_length)
अणु
	अगर (actual_length) अणु
		usb_serial_debug_data(&port->dev, __func__, actual_length, data);
		tty_insert_flip_string(&port->port, data, actual_length);
		tty_flip_buffer_push(&port->port);
	पूर्ण
पूर्ण


/******************************************************************************
 * packet queue handling
 ******************************************************************************/

/*
 * queue a received (usb-)packet क्रम later processing
 */
अटल पूर्णांक pkt_add(काष्ठा garmin_data *garmin_data_p,
		   अचिन्हित अक्षर *data, अचिन्हित पूर्णांक data_length)
अणु
	पूर्णांक state = 0;
	पूर्णांक result = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा garmin_packet *pkt;

	/* process only packets containing data ... */
	अगर (data_length) अणु
		pkt = kदो_स्मृति(माप(काष्ठा garmin_packet)+data_length,
								GFP_ATOMIC);
		अगर (!pkt)
			वापस 0;

		pkt->size = data_length;
		स_नकल(pkt->data, data, data_length);

		spin_lock_irqsave(&garmin_data_p->lock, flags);
		garmin_data_p->flags |= FLAGS_QUEUING;
		result = list_empty(&garmin_data_p->pktlist);
		pkt->seq = garmin_data_p->seq_counter++;
		list_add_tail(&pkt->list, &garmin_data_p->pktlist);
		state = garmin_data_p->state;
		spin_unlock_irqrestore(&garmin_data_p->lock, flags);

		dev_dbg(&garmin_data_p->port->dev,
			"%s - added: pkt: %d - %d bytes\n", __func__,
			pkt->seq, data_length);

		/* in serial mode, अगर someone is रुकोing क्रम data from
		   the device, convert and send the next packet to tty. */
		अगर (result && (state == STATE_GSP_WAIT_DATA))
			gsp_next_packet(garmin_data_p);
	पूर्ण
	वापस result;
पूर्ण


/* get the next pending packet */
अटल काष्ठा garmin_packet *pkt_pop(काष्ठा garmin_data *garmin_data_p)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा garmin_packet *result = शून्य;

	spin_lock_irqsave(&garmin_data_p->lock, flags);
	अगर (!list_empty(&garmin_data_p->pktlist)) अणु
		result = (काष्ठा garmin_packet *)garmin_data_p->pktlist.next;
		list_del(&result->list);
	पूर्ण
	spin_unlock_irqrestore(&garmin_data_p->lock, flags);
	वापस result;
पूर्ण


/* मुक्त up all queued data */
अटल व्योम pkt_clear(काष्ठा garmin_data *garmin_data_p)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा garmin_packet *result = शून्य;

	spin_lock_irqsave(&garmin_data_p->lock, flags);
	जबतक (!list_empty(&garmin_data_p->pktlist)) अणु
		result = (काष्ठा garmin_packet *)garmin_data_p->pktlist.next;
		list_del(&result->list);
		kमुक्त(result);
	पूर्ण
	spin_unlock_irqrestore(&garmin_data_p->lock, flags);
पूर्ण


/******************************************************************************
 * garmin serial protocol handling handling
 ******************************************************************************/

/* send an ack packet back to the tty */
अटल पूर्णांक gsp_send_ack(काष्ठा garmin_data *garmin_data_p, __u8 pkt_id)
अणु
	__u8 pkt[10];
	__u8 cksum = 0;
	__u8 *ptr = pkt;
	अचिन्हित  l = 0;

	dev_dbg(&garmin_data_p->port->dev, "%s - pkt-id: 0x%X.\n", __func__,
			pkt_id);

	*ptr++ = DLE;
	*ptr++ = ACK;
	cksum += ACK;

	*ptr++ = 2;
	cksum += 2;

	*ptr++ = pkt_id;
	cksum += pkt_id;

	अगर (pkt_id == DLE)
		*ptr++ = DLE;

	*ptr++ = 0;
	*ptr++ = (-cksum) & 0xFF;
	*ptr++ = DLE;
	*ptr++ = ETX;

	l = ptr-pkt;

	send_to_tty(garmin_data_p->port, pkt, l);
	वापस 0;
पूर्ण



/*
 * called क्रम a complete packet received from tty layer
 *
 * the complete packet (pktid ... cksum) is in garmin_data_p->inbuf starting
 * at GSP_INITIAL_OFFSET.
 *
 * count - number of bytes in the input buffer including space reserved क्रम
 *         the usb header: GSP_INITIAL_OFFSET + number of bytes in packet
 *         (including pkt-id, data-length a. cksum)
 */
अटल पूर्णांक gsp_rec_packet(काष्ठा garmin_data *garmin_data_p, पूर्णांक count)
अणु
	काष्ठा device *dev = &garmin_data_p->port->dev;
	अचिन्हित दीर्घ flags;
	स्थिर __u8 *recpkt = garmin_data_p->inbuffer+GSP_INITIAL_OFFSET;
	__le32 *usbdata = (__le32 *) garmin_data_p->inbuffer;
	पूर्णांक cksum = 0;
	पूर्णांक n = 0;
	पूर्णांक pktid = recpkt[0];
	पूर्णांक size = recpkt[1];

	usb_serial_debug_data(&garmin_data_p->port->dev, __func__,
			      count-GSP_INITIAL_OFFSET, recpkt);

	अगर (size != (count-GSP_INITIAL_OFFSET-3)) अणु
		dev_dbg(dev, "%s - invalid size, expected %d bytes, got %d\n",
			__func__, size, (count-GSP_INITIAL_OFFSET-3));
		वापस -EINVPKT;
	पूर्ण

	cksum += *recpkt++;
	cksum += *recpkt++;

	/* sanity check, हटाओ after test ... */
	अगर ((__u8 *)&(usbdata[3]) != recpkt) अणु
		dev_dbg(dev, "%s - ptr mismatch %p - %p\n", __func__,
			&(usbdata[4]), recpkt);
		वापस -EINVPKT;
	पूर्ण

	जबतक (n < size) अणु
		cksum += *recpkt++;
		n++;
	पूर्ण

	अगर (((cksum + *recpkt) & 0xff) != 0) अणु
		dev_dbg(dev, "%s - invalid checksum, expected %02x, got %02x\n",
			__func__, -cksum & 0xff, *recpkt);
		वापस -EINVPKT;
	पूर्ण

	usbdata[0] = __cpu_to_le32(GARMIN_LAYERID_APPL);
	usbdata[1] = __cpu_to_le32(pktid);
	usbdata[2] = __cpu_to_le32(size);

	garmin_ग_लिखो_bulk(garmin_data_p->port, garmin_data_p->inbuffer,
			   GARMIN_PKTHDR_LENGTH+size, 0);

	/* अगर this was an पात-transfer command, flush all
	   queued data. */
	अगर (isAbortTrfCmnd(garmin_data_p->inbuffer)) अणु
		spin_lock_irqsave(&garmin_data_p->lock, flags);
		garmin_data_p->flags |= FLAGS_DROP_DATA;
		spin_unlock_irqrestore(&garmin_data_p->lock, flags);
		pkt_clear(garmin_data_p);
	पूर्ण

	वापस count;
पूर्ण



/*
 * Called क्रम data received from tty
 *
 * buf contains the data पढ़ो, it may span more than one packet or even
 * incomplete packets
 *
 * input record should be a serial-record, but it may not be complete.
 * Copy it पूर्णांकo our local buffer, until an etx is seen (or an error
 * occurs).
 * Once the record is complete, convert पूर्णांकo a usb packet and send it
 * to the bulk pipe, send an ack back to the tty.
 *
 * If the input is an ack, just send the last queued packet to the
 * tty layer.
 *
 * अगर the input is an पात command, drop all queued data.
 */

अटल पूर्णांक gsp_receive(काष्ठा garmin_data *garmin_data_p,
		       स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा device *dev = &garmin_data_p->port->dev;
	अचिन्हित दीर्घ flags;
	पूर्णांक offs = 0;
	पूर्णांक ack_or_nak_seen = 0;
	__u8 *dest;
	पूर्णांक size;
	/* dleSeen: set अगर last byte पढ़ो was a DLE */
	पूर्णांक dleSeen;
	/* skip: अगर set, skip incoming data until possible start of
	 *       new packet
	 */
	पूर्णांक skip;
	__u8 data;

	spin_lock_irqsave(&garmin_data_p->lock, flags);
	dest = garmin_data_p->inbuffer;
	size = garmin_data_p->insize;
	dleSeen = garmin_data_p->flags & FLAGS_GSP_DLESEEN;
	skip = garmin_data_p->flags & FLAGS_GSP_SKIP;
	spin_unlock_irqrestore(&garmin_data_p->lock, flags);

	/* dev_dbg(dev, "%s - dle=%d skip=%d size=%d count=%d\n",
		__func__, dleSeen, skip, size, count); */

	अगर (size == 0)
		size = GSP_INITIAL_OFFSET;

	जबतक (offs < count) अणु

		data = *(buf+offs);
		offs++;

		अगर (data == DLE) अणु
			अगर (skip) अणु /* start of a new pkt */
				skip = 0;
				size = GSP_INITIAL_OFFSET;
				dleSeen = 1;
			पूर्ण अन्यथा अगर (dleSeen) अणु
				dest[size++] = data;
				dleSeen = 0;
			पूर्ण अन्यथा अणु
				dleSeen = 1;
			पूर्ण
		पूर्ण अन्यथा अगर (data == ETX) अणु
			अगर (dleSeen) अणु
				/* packet complete */

				data = dest[GSP_INITIAL_OFFSET];

				अगर (data == ACK) अणु
					ack_or_nak_seen = ACK;
					dev_dbg(dev, "ACK packet complete.\n");
				पूर्ण अन्यथा अगर (data == NAK) अणु
					ack_or_nak_seen = NAK;
					dev_dbg(dev, "NAK packet complete.\n");
				पूर्ण अन्यथा अणु
					dev_dbg(dev, "packet complete - id=0x%X.\n",
							data);
					gsp_rec_packet(garmin_data_p, size);
				पूर्ण

				skip = 1;
				size = GSP_INITIAL_OFFSET;
				dleSeen = 0;
			पूर्ण अन्यथा अणु
				dest[size++] = data;
			पूर्ण
		पूर्ण अन्यथा अगर (!skip) अणु

			अगर (dleSeen) अणु
				size = GSP_INITIAL_OFFSET;
				dleSeen = 0;
			पूर्ण

			dest[size++] = data;
		पूर्ण

		अगर (size >= GPS_IN_बफ_मान) अणु
			dev_dbg(dev, "%s - packet too large.\n", __func__);
			skip = 1;
			size = GSP_INITIAL_OFFSET;
			dleSeen = 0;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&garmin_data_p->lock, flags);

	garmin_data_p->insize = size;

	/* copy flags back to काष्ठाure */
	अगर (skip)
		garmin_data_p->flags |= FLAGS_GSP_SKIP;
	अन्यथा
		garmin_data_p->flags &= ~FLAGS_GSP_SKIP;

	अगर (dleSeen)
		garmin_data_p->flags |= FLAGS_GSP_DLESEEN;
	अन्यथा
		garmin_data_p->flags &= ~FLAGS_GSP_DLESEEN;

	spin_unlock_irqrestore(&garmin_data_p->lock, flags);

	अगर (ack_or_nak_seen) अणु
		अगर (gsp_next_packet(garmin_data_p) > 0)
			garmin_data_p->state = STATE_ACTIVE;
		अन्यथा
			garmin_data_p->state = STATE_GSP_WAIT_DATA;
	पूर्ण
	वापस count;
पूर्ण



/*
 * Sends a usb packet to the tty
 *
 * Assumes, that all packages and at an usb-packet boundary.
 *
 * वापस <0 on error, 0 अगर packet is incomplete or > 0 अगर packet was sent
 */
अटल पूर्णांक gsp_send(काष्ठा garmin_data *garmin_data_p,
		    स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा device *dev = &garmin_data_p->port->dev;
	स्थिर अचिन्हित अक्षर *src;
	अचिन्हित अक्षर *dst;
	पूर्णांक pktid = 0;
	पूर्णांक datalen = 0;
	पूर्णांक cksum = 0;
	पूर्णांक i = 0;
	पूर्णांक k;

	dev_dbg(dev, "%s - state %d - %d bytes.\n", __func__,
		garmin_data_p->state, count);

	k = garmin_data_p->outsize;
	अगर ((k+count) > GPS_OUT_बफ_मान) अणु
		dev_dbg(dev, "packet too large\n");
		garmin_data_p->outsize = 0;
		वापस -4;
	पूर्ण

	स_नकल(garmin_data_p->outbuffer+k, buf, count);
	k += count;
	garmin_data_p->outsize = k;

	अगर (k >= GARMIN_PKTHDR_LENGTH) अणु
		pktid  = getPacketId(garmin_data_p->outbuffer);
		datalen = getDataLength(garmin_data_p->outbuffer);
		i = GARMIN_PKTHDR_LENGTH + datalen;
		अगर (k < i)
			वापस 0;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	dev_dbg(dev, "%s - %d bytes in buffer, %d bytes in pkt.\n", __func__, k, i);

	/* garmin_data_p->outbuffer now contains a complete packet */

	usb_serial_debug_data(&garmin_data_p->port->dev, __func__, k,
			      garmin_data_p->outbuffer);

	garmin_data_p->outsize = 0;

	अगर (getLayerId(garmin_data_p->outbuffer) != GARMIN_LAYERID_APPL) अणु
		dev_dbg(dev, "not an application packet (%d)\n",
				getLayerId(garmin_data_p->outbuffer));
		वापस -1;
	पूर्ण

	अगर (pktid > 255) अणु
		dev_dbg(dev, "packet-id %d too large\n", pktid);
		वापस -2;
	पूर्ण

	अगर (datalen > 255) अणु
		dev_dbg(dev, "packet-size %d too large\n", datalen);
		वापस -3;
	पूर्ण

	/* the serial protocol should be able to handle this packet */

	k = 0;
	src = garmin_data_p->outbuffer+GARMIN_PKTHDR_LENGTH;
	क्रम (i = 0; i < datalen; i++) अणु
		अगर (*src++ == DLE)
			k++;
	पूर्ण

	src = garmin_data_p->outbuffer+GARMIN_PKTHDR_LENGTH;
	अगर (k > (GARMIN_PKTHDR_LENGTH-2)) अणु
		/* can't add stuffing DLEs in place, move data to end
		   of buffer ... */
		dst = garmin_data_p->outbuffer+GPS_OUT_बफ_मान-datalen;
		स_नकल(dst, src, datalen);
		src = dst;
	पूर्ण

	dst = garmin_data_p->outbuffer;

	*dst++ = DLE;
	*dst++ = pktid;
	cksum += pktid;
	*dst++ = datalen;
	cksum += datalen;
	अगर (datalen == DLE)
		*dst++ = DLE;

	क्रम (i = 0; i < datalen; i++) अणु
		__u8 c = *src++;
		*dst++ = c;
		cksum += c;
		अगर (c == DLE)
			*dst++ = DLE;
	पूर्ण

	cksum = -cksum & 0xFF;
	*dst++ = cksum;
	अगर (cksum == DLE)
		*dst++ = DLE;
	*dst++ = DLE;
	*dst++ = ETX;

	i = dst-garmin_data_p->outbuffer;

	send_to_tty(garmin_data_p->port, garmin_data_p->outbuffer, i);

	garmin_data_p->pkt_id = pktid;
	garmin_data_p->state  = STATE_WAIT_TTY_ACK;

	वापस i;
पूर्ण


/*
 * Process the next pending data packet - अगर there is one
 */
अटल पूर्णांक gsp_next_packet(काष्ठा garmin_data *garmin_data_p)
अणु
	पूर्णांक result = 0;
	काष्ठा garmin_packet *pkt = शून्य;

	जबतक ((pkt = pkt_pop(garmin_data_p)) != शून्य) अणु
		dev_dbg(&garmin_data_p->port->dev, "%s - next pkt: %d\n", __func__, pkt->seq);
		result = gsp_send(garmin_data_p, pkt->data, pkt->size);
		अगर (result > 0) अणु
			kमुक्त(pkt);
			वापस result;
		पूर्ण
		kमुक्त(pkt);
	पूर्ण
	वापस result;
पूर्ण



/******************************************************************************
 * garmin native mode
 ******************************************************************************/


/*
 * Called क्रम data received from tty
 *
 * The input data is expected to be in garmin usb-packet क्रमmat.
 *
 * buf contains the data पढ़ो, it may span more than one packet
 * or even incomplete packets
 */
अटल पूर्णांक nat_receive(काष्ठा garmin_data *garmin_data_p,
		       स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	अचिन्हित दीर्घ flags;
	__u8 *dest;
	पूर्णांक offs = 0;
	पूर्णांक result = count;
	पूर्णांक len;

	जबतक (offs < count) अणु
		/* अगर buffer contains header, copy rest of data */
		अगर (garmin_data_p->insize >= GARMIN_PKTHDR_LENGTH)
			len = GARMIN_PKTHDR_LENGTH
			      +getDataLength(garmin_data_p->inbuffer);
		अन्यथा
			len = GARMIN_PKTHDR_LENGTH;

		अगर (len >= GPS_IN_बफ_मान) अणु
			/* seems to be an invalid packet, ignore rest
			   of input */
			dev_dbg(&garmin_data_p->port->dev,
				"%s - packet size too large: %d\n",
				__func__, len);
			garmin_data_p->insize = 0;
			count = 0;
			result = -EINVPKT;
		पूर्ण अन्यथा अणु
			len -= garmin_data_p->insize;
			अगर (len > (count-offs))
				len = (count-offs);
			अगर (len > 0) अणु
				dest = garmin_data_p->inbuffer
						+ garmin_data_p->insize;
				स_नकल(dest, buf+offs, len);
				garmin_data_p->insize += len;
				offs += len;
			पूर्ण
		पूर्ण

		/* करो we have a complete packet ? */
		अगर (garmin_data_p->insize >= GARMIN_PKTHDR_LENGTH) अणु
			len = GARMIN_PKTHDR_LENGTH+
			   getDataLength(garmin_data_p->inbuffer);
			अगर (garmin_data_p->insize >= len) अणु
				garmin_ग_लिखो_bulk(garmin_data_p->port,
						   garmin_data_p->inbuffer,
						   len, 0);
				garmin_data_p->insize = 0;

				/* अगर this was an पात-transfer command,
				   flush all queued data. */
				अगर (isAbortTrfCmnd(garmin_data_p->inbuffer)) अणु
					spin_lock_irqsave(&garmin_data_p->lock,
									flags);
					garmin_data_p->flags |= FLAGS_DROP_DATA;
					spin_unlock_irqrestore(
						&garmin_data_p->lock, flags);
					pkt_clear(garmin_data_p);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस result;
पूर्ण


/******************************************************************************
 * निजी packets
 ******************************************************************************/

अटल व्योम priv_status_resp(काष्ठा usb_serial_port *port)
अणु
	काष्ठा garmin_data *garmin_data_p = usb_get_serial_port_data(port);
	__le32 *pkt = (__le32 *)garmin_data_p->privpkt;

	pkt[0] = __cpu_to_le32(GARMIN_LAYERID_PRIVATE);
	pkt[1] = __cpu_to_le32(PRIV_PKTID_INFO_RESP);
	pkt[2] = __cpu_to_le32(12);
	pkt[3] = __cpu_to_le32(VERSION_MAJOR << 16 | VERSION_MINOR);
	pkt[4] = __cpu_to_le32(garmin_data_p->mode);
	pkt[5] = __cpu_to_le32(garmin_data_p->serial_num);

	send_to_tty(port, (__u8 *)pkt, 6 * 4);
पूर्ण


/******************************************************************************
 * Garmin specअगरic driver functions
 ******************************************************************************/

अटल पूर्णांक process_resetdev_request(काष्ठा usb_serial_port *port)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक status;
	काष्ठा garmin_data *garmin_data_p = usb_get_serial_port_data(port);

	spin_lock_irqsave(&garmin_data_p->lock, flags);
	garmin_data_p->flags &= ~(CLEAR_HALT_REQUIRED);
	garmin_data_p->state = STATE_RESET;
	garmin_data_p->serial_num = 0;
	spin_unlock_irqrestore(&garmin_data_p->lock, flags);

	usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);
	dev_dbg(&port->dev, "%s - usb_reset_device\n", __func__);
	status = usb_reset_device(port->serial->dev);
	अगर (status)
		dev_dbg(&port->dev, "%s - usb_reset_device failed: %d\n",
			__func__, status);
	वापस status;
पूर्ण



/*
 * clear all cached data
 */
अटल पूर्णांक garmin_clear(काष्ठा garmin_data *garmin_data_p)
अणु
	अचिन्हित दीर्घ flags;

	/* flush all queued data */
	pkt_clear(garmin_data_p);

	spin_lock_irqsave(&garmin_data_p->lock, flags);
	garmin_data_p->insize = 0;
	garmin_data_p->outsize = 0;
	spin_unlock_irqrestore(&garmin_data_p->lock, flags);

	वापस 0;
पूर्ण


अटल पूर्णांक garmin_init_session(काष्ठा usb_serial_port *port)
अणु
	काष्ठा garmin_data *garmin_data_p = usb_get_serial_port_data(port);
	पूर्णांक status;
	पूर्णांक i;

	usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);

	status = usb_submit_urb(port->पूर्णांकerrupt_in_urb, GFP_KERNEL);
	अगर (status) अणु
		dev_err(&port->dev, "failed to submit interrupt urb: %d\n",
				status);
		वापस status;
	पूर्ण

	/*
	 * using the initialization method from gpsbabel. See comments in
	 * gpsbabel/jeeps/gpslibusb.c gusb_reset_toggles()
	 */
	dev_dbg(&port->dev, "%s - starting session ...\n", __func__);
	garmin_data_p->state = STATE_ACTIVE;

	क्रम (i = 0; i < 3; i++) अणु
		status = garmin_ग_लिखो_bulk(port, GARMIN_START_SESSION_REQ,
				माप(GARMIN_START_SESSION_REQ), 0);
		अगर (status < 0)
			जाओ err_समाप्त_urbs;
	पूर्ण

	वापस 0;

err_समाप्त_urbs:
	usb_समाप्त_anchored_urbs(&garmin_data_p->ग_लिखो_urbs);
	usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);

	वापस status;
पूर्ण



अटल पूर्णांक garmin_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक status = 0;
	काष्ठा garmin_data *garmin_data_p = usb_get_serial_port_data(port);

	spin_lock_irqsave(&garmin_data_p->lock, flags);
	garmin_data_p->mode  = initial_mode;
	garmin_data_p->count = 0;
	garmin_data_p->flags &= FLAGS_SESSION_REPLY1_SEEN;
	spin_unlock_irqrestore(&garmin_data_p->lock, flags);

	/* shutकरोwn any bulk पढ़ोs that might be going on */
	usb_समाप्त_urb(port->पढ़ो_urb);

	अगर (garmin_data_p->state == STATE_RESET)
		status = garmin_init_session(port);

	garmin_data_p->state = STATE_ACTIVE;
	वापस status;
पूर्ण


अटल व्योम garmin_बंद(काष्ठा usb_serial_port *port)
अणु
	काष्ठा garmin_data *garmin_data_p = usb_get_serial_port_data(port);

	dev_dbg(&port->dev, "%s - mode=%d state=%d flags=0x%X\n",
		__func__, garmin_data_p->mode, garmin_data_p->state,
		garmin_data_p->flags);

	garmin_clear(garmin_data_p);

	/* shutकरोwn our urbs */
	usb_समाप्त_urb(port->पढ़ो_urb);
	usb_समाप्त_anchored_urbs(&garmin_data_p->ग_लिखो_urbs);

	/* keep reset state so we know that we must start a new session */
	अगर (garmin_data_p->state != STATE_RESET)
		garmin_data_p->state = STATE_DISCONNECTED;
पूर्ण


अटल व्योम garmin_ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_serial_port *port = urb->context;

	अगर (port) अणु
		काष्ठा garmin_data *garmin_data_p =
					usb_get_serial_port_data(port);

		अगर (getLayerId(urb->transfer_buffer) == GARMIN_LAYERID_APPL) अणु

			अगर (garmin_data_p->mode == MODE_GARMIN_SERIAL) अणु
				gsp_send_ack(garmin_data_p,
					((__u8 *)urb->transfer_buffer)[4]);
			पूर्ण
		पूर्ण
		usb_serial_port_softपूर्णांक(port);
	पूर्ण

	/* Ignore errors that resulted from garmin_ग_लिखो_bulk with
	   dismiss_ack = 1 */

	/* मुक्त up the transfer buffer, as usb_मुक्त_urb() करोes not करो this */
	kमुक्त(urb->transfer_buffer);
पूर्ण


अटल पूर्णांक garmin_ग_लिखो_bulk(काष्ठा usb_serial_port *port,
			      स्थिर अचिन्हित अक्षर *buf, पूर्णांक count,
			      पूर्णांक dismiss_ack)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा usb_serial *serial = port->serial;
	काष्ठा garmin_data *garmin_data_p = usb_get_serial_port_data(port);
	काष्ठा urb *urb;
	अचिन्हित अक्षर *buffer;
	पूर्णांक status;

	spin_lock_irqsave(&garmin_data_p->lock, flags);
	garmin_data_p->flags &= ~FLAGS_DROP_DATA;
	spin_unlock_irqrestore(&garmin_data_p->lock, flags);

	buffer = kदो_स्मृति(count, GFP_ATOMIC);
	अगर (!buffer)
		वापस -ENOMEM;

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb) अणु
		kमुक्त(buffer);
		वापस -ENOMEM;
	पूर्ण

	स_नकल(buffer, buf, count);

	usb_serial_debug_data(&port->dev, __func__, count, buffer);

	usb_fill_bulk_urb(urb, serial->dev,
				usb_sndbulkpipe(serial->dev,
					port->bulk_out_endpoपूर्णांकAddress),
				buffer, count,
				garmin_ग_लिखो_bulk_callback,
				dismiss_ack ? शून्य : port);
	urb->transfer_flags |= URB_ZERO_PACKET;

	अगर (getLayerId(buffer) == GARMIN_LAYERID_APPL) अणु

		spin_lock_irqsave(&garmin_data_p->lock, flags);
		garmin_data_p->flags |= APP_REQ_SEEN;
		spin_unlock_irqrestore(&garmin_data_p->lock, flags);

		अगर (garmin_data_p->mode == MODE_GARMIN_SERIAL)  अणु
			pkt_clear(garmin_data_p);
			garmin_data_p->state = STATE_GSP_WAIT_DATA;
		पूर्ण
	पूर्ण

	/* send it करोwn the pipe */
	usb_anchor_urb(urb, &garmin_data_p->ग_लिखो_urbs);
	status = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (status) अणु
		dev_err(&port->dev,
		   "%s - usb_submit_urb(write bulk) failed with status = %d\n",
				__func__, status);
		count = status;
		usb_unanchor_urb(urb);
		kमुक्त(buffer);
	पूर्ण

	/* we are करोne with this urb, so let the host driver
	 * really मुक्त it when it is finished with it */
	usb_मुक्त_urb(urb);

	वापस count;
पूर्ण

अटल पूर्णांक garmin_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
					 स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा device *dev = &port->dev;
	पूर्णांक pktid, pktsiz, len;
	काष्ठा garmin_data *garmin_data_p = usb_get_serial_port_data(port);
	__le32 *privpkt = (__le32 *)garmin_data_p->privpkt;

	usb_serial_debug_data(dev, __func__, count, buf);

	अगर (garmin_data_p->state == STATE_RESET)
		वापस -EIO;

	/* check क्रम our निजी packets */
	अगर (count >= GARMIN_PKTHDR_LENGTH) अणु
		len = PRIVPKTSIZ;
		अगर (count < len)
			len = count;

		स_नकल(garmin_data_p->privpkt, buf, len);

		pktsiz = getDataLength(garmin_data_p->privpkt);
		pktid  = getPacketId(garmin_data_p->privpkt);

		अगर (count == (GARMIN_PKTHDR_LENGTH + pktsiz) &&
				getLayerId(garmin_data_p->privpkt) ==
						GARMIN_LAYERID_PRIVATE) अणु

			dev_dbg(dev, "%s - processing private request %d\n",
				__func__, pktid);

			/* drop all unfinished transfers */
			garmin_clear(garmin_data_p);

			चयन (pktid) अणु
			हाल PRIV_PKTID_SET_MODE:
				अगर (pktsiz != 4)
					वापस -EINVPKT;
				garmin_data_p->mode = __le32_to_cpu(privpkt[3]);
				dev_dbg(dev, "%s - mode set to %d\n",
					__func__, garmin_data_p->mode);
				अवरोध;

			हाल PRIV_PKTID_INFO_REQ:
				priv_status_resp(port);
				अवरोध;

			हाल PRIV_PKTID_RESET_REQ:
				process_resetdev_request(port);
				अवरोध;

			हाल PRIV_PKTID_SET_DEF_MODE:
				अगर (pktsiz != 4)
					वापस -EINVPKT;
				initial_mode = __le32_to_cpu(privpkt[3]);
				dev_dbg(dev, "%s - initial_mode set to %d\n",
					__func__,
					garmin_data_p->mode);
				अवरोध;
			पूर्ण
			वापस count;
		पूर्ण
	पूर्ण

	अगर (garmin_data_p->mode == MODE_GARMIN_SERIAL) अणु
		वापस gsp_receive(garmin_data_p, buf, count);
	पूर्ण अन्यथा अणु	/* MODE_NATIVE */
		वापस nat_receive(garmin_data_p, buf, count);
	पूर्ण
पूर्ण


अटल पूर्णांक garmin_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	/*
	 * Report back the bytes currently available in the output buffer.
	 */
	काष्ठा garmin_data *garmin_data_p = usb_get_serial_port_data(port);
	वापस GPS_OUT_बफ_मान-garmin_data_p->outsize;
पूर्ण


अटल व्योम garmin_पढ़ो_process(काष्ठा garmin_data *garmin_data_p,
				 अचिन्हित अक्षर *data, अचिन्हित data_length,
				 पूर्णांक bulk_data)
अणु
	अचिन्हित दीर्घ flags;

	अगर (garmin_data_p->flags & FLAGS_DROP_DATA) अणु
		/* पात-transfer cmd is active */
		dev_dbg(&garmin_data_p->port->dev, "%s - pkt dropped\n", __func__);
	पूर्ण अन्यथा अगर (garmin_data_p->state != STATE_DISCONNECTED &&
		garmin_data_p->state != STATE_RESET) अणु

		/* अगर throttling is active or postprecessing is required
		   put the received data in the input queue, otherwise
		   send it directly to the tty port */
		अगर (garmin_data_p->flags & FLAGS_QUEUING) अणु
			pkt_add(garmin_data_p, data, data_length);
		पूर्ण अन्यथा अगर (bulk_data || (data_length >= माप(u32) &&
				getLayerId(data) == GARMIN_LAYERID_APPL)) अणु

			spin_lock_irqsave(&garmin_data_p->lock, flags);
			garmin_data_p->flags |= APP_RESP_SEEN;
			spin_unlock_irqrestore(&garmin_data_p->lock, flags);

			अगर (garmin_data_p->mode == MODE_GARMIN_SERIAL) अणु
				pkt_add(garmin_data_p, data, data_length);
			पूर्ण अन्यथा अणु
				send_to_tty(garmin_data_p->port, data,
						data_length);
			पूर्ण
		पूर्ण
		/* ignore प्रणाली layer packets ... */
	पूर्ण
पूर्ण


अटल व्योम garmin_पढ़ो_bulk_callback(काष्ठा urb *urb)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा garmin_data *garmin_data_p = usb_get_serial_port_data(port);
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	पूर्णांक status = urb->status;
	पूर्णांक retval;

	अगर (status) अणु
		dev_dbg(&urb->dev->dev, "%s - nonzero read bulk status received: %d\n",
			__func__, status);
		वापस;
	पूर्ण

	usb_serial_debug_data(&port->dev, __func__, urb->actual_length, data);

	garmin_पढ़ो_process(garmin_data_p, data, urb->actual_length, 1);

	अगर (urb->actual_length == 0 &&
			(garmin_data_p->flags & FLAGS_BULK_IN_RESTART) != 0) अणु
		spin_lock_irqsave(&garmin_data_p->lock, flags);
		garmin_data_p->flags &= ~FLAGS_BULK_IN_RESTART;
		spin_unlock_irqrestore(&garmin_data_p->lock, flags);
		retval = usb_submit_urb(port->पढ़ो_urb, GFP_ATOMIC);
		अगर (retval)
			dev_err(&port->dev,
				"%s - failed resubmitting read urb, error %d\n",
				__func__, retval);
	पूर्ण अन्यथा अगर (urb->actual_length > 0) अणु
		/* Continue trying to पढ़ो until nothing more is received  */
		अगर ((garmin_data_p->flags & FLAGS_THROTTLED) == 0) अणु
			retval = usb_submit_urb(port->पढ़ो_urb, GFP_ATOMIC);
			अगर (retval)
				dev_err(&port->dev,
					"%s - failed resubmitting read urb, error %d\n",
					__func__, retval);
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_dbg(&port->dev, "%s - end of bulk data\n", __func__);
		spin_lock_irqsave(&garmin_data_p->lock, flags);
		garmin_data_p->flags &= ~FLAGS_BULK_IN_ACTIVE;
		spin_unlock_irqrestore(&garmin_data_p->lock, flags);
	पूर्ण
पूर्ण


अटल व्योम garmin_पढ़ो_पूर्णांक_callback(काष्ठा urb *urb)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;
	काष्ठा usb_serial_port *port = urb->context;
	काष्ठा garmin_data *garmin_data_p = usb_get_serial_port_data(port);
	अचिन्हित अक्षर *data = urb->transfer_buffer;
	पूर्णांक status = urb->status;

	चयन (status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_dbg(&urb->dev->dev, "%s - urb shutting down with status: %d\n",
			__func__, status);
		वापस;
	शेष:
		dev_dbg(&urb->dev->dev, "%s - nonzero urb status received: %d\n",
			__func__, status);
		वापस;
	पूर्ण

	usb_serial_debug_data(&port->dev, __func__, urb->actual_length,
			      urb->transfer_buffer);

	अगर (urb->actual_length == माप(GARMIN_BULK_IN_AVAIL_REPLY) &&
		स_भेद(data, GARMIN_BULK_IN_AVAIL_REPLY,
				माप(GARMIN_BULK_IN_AVAIL_REPLY)) == 0) अणु

		dev_dbg(&port->dev, "%s - bulk data available.\n", __func__);

		अगर ((garmin_data_p->flags & FLAGS_BULK_IN_ACTIVE) == 0) अणु

			/* bulk data available */
			retval = usb_submit_urb(port->पढ़ो_urb, GFP_ATOMIC);
			अगर (retval) अणु
				dev_err(&port->dev,
				 "%s - failed submitting read urb, error %d\n",
							__func__, retval);
			पूर्ण अन्यथा अणु
				spin_lock_irqsave(&garmin_data_p->lock, flags);
				garmin_data_p->flags |= FLAGS_BULK_IN_ACTIVE;
				spin_unlock_irqrestore(&garmin_data_p->lock,
									flags);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* bulk-in transfer still active */
			spin_lock_irqsave(&garmin_data_p->lock, flags);
			garmin_data_p->flags |= FLAGS_BULK_IN_RESTART;
			spin_unlock_irqrestore(&garmin_data_p->lock, flags);
		पूर्ण

	पूर्ण अन्यथा अगर (urb->actual_length == (4+माप(GARMIN_START_SESSION_REPLY))
			 && स_भेद(data, GARMIN_START_SESSION_REPLY,
				 माप(GARMIN_START_SESSION_REPLY)) == 0) अणु

		spin_lock_irqsave(&garmin_data_p->lock, flags);
		garmin_data_p->flags |= FLAGS_SESSION_REPLY1_SEEN;
		spin_unlock_irqrestore(&garmin_data_p->lock, flags);

		/* save the serial number */
		garmin_data_p->serial_num = __le32_to_cpup(
					(__le32 *)(data+GARMIN_PKTHDR_LENGTH));

		dev_dbg(&port->dev, "%s - start-of-session reply seen - serial %u.\n",
			__func__, garmin_data_p->serial_num);
	पूर्ण

	garmin_पढ़ो_process(garmin_data_p, data, urb->actual_length, 0);

	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval)
		dev_err(&urb->dev->dev,
			"%s - Error %d submitting interrupt urb\n",
			__func__, retval);
पूर्ण


/*
 * Sends the next queued packt to the tty port (garmin native mode only)
 * and then sets a समयr to call itself again until all queued data
 * is sent.
 */
अटल पूर्णांक garmin_flush_queue(काष्ठा garmin_data *garmin_data_p)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा garmin_packet *pkt;

	अगर ((garmin_data_p->flags & FLAGS_THROTTLED) == 0) अणु
		pkt = pkt_pop(garmin_data_p);
		अगर (pkt != शून्य) अणु
			send_to_tty(garmin_data_p->port, pkt->data, pkt->size);
			kमुक्त(pkt);
			mod_समयr(&garmin_data_p->समयr, (1)+jअगरfies);

		पूर्ण अन्यथा अणु
			spin_lock_irqsave(&garmin_data_p->lock, flags);
			garmin_data_p->flags &= ~FLAGS_QUEUING;
			spin_unlock_irqrestore(&garmin_data_p->lock, flags);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


अटल व्योम garmin_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा garmin_data *garmin_data_p = usb_get_serial_port_data(port);

	/* set flag, data received will be put पूर्णांकo a queue
	   क्रम later processing */
	spin_lock_irq(&garmin_data_p->lock);
	garmin_data_p->flags |= FLAGS_QUEUING|FLAGS_THROTTLED;
	spin_unlock_irq(&garmin_data_p->lock);
पूर्ण


अटल व्योम garmin_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा usb_serial_port *port = tty->driver_data;
	काष्ठा garmin_data *garmin_data_p = usb_get_serial_port_data(port);
	पूर्णांक status;

	spin_lock_irq(&garmin_data_p->lock);
	garmin_data_p->flags &= ~FLAGS_THROTTLED;
	spin_unlock_irq(&garmin_data_p->lock);

	/* in native mode send queued data to tty, in
	   serial mode nothing needs to be करोne here */
	अगर (garmin_data_p->mode == MODE_NATIVE)
		garmin_flush_queue(garmin_data_p);

	अगर ((garmin_data_p->flags & FLAGS_BULK_IN_ACTIVE) != 0) अणु
		status = usb_submit_urb(port->पढ़ो_urb, GFP_KERNEL);
		अगर (status)
			dev_err(&port->dev,
				"%s - failed resubmitting read urb, error %d\n",
				__func__, status);
	पूर्ण
पूर्ण

/*
 * The समयr is currently only used to send queued packets to
 * the tty in हालs where the protocol provides no own handshaking
 * to initiate the transfer.
 */
अटल व्योम समयout_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा garmin_data *garmin_data_p = from_समयr(garmin_data_p, t, समयr);

	/* send the next queued packet to the tty port */
	अगर (garmin_data_p->mode == MODE_NATIVE)
		अगर (garmin_data_p->flags & FLAGS_QUEUING)
			garmin_flush_queue(garmin_data_p);
पूर्ण



अटल पूर्णांक garmin_port_probe(काष्ठा usb_serial_port *port)
अणु
	पूर्णांक status;
	काष्ठा garmin_data *garmin_data_p;

	garmin_data_p = kzalloc(माप(काष्ठा garmin_data), GFP_KERNEL);
	अगर (!garmin_data_p)
		वापस -ENOMEM;

	समयr_setup(&garmin_data_p->समयr, समयout_handler, 0);
	spin_lock_init(&garmin_data_p->lock);
	INIT_LIST_HEAD(&garmin_data_p->pktlist);
	garmin_data_p->port = port;
	garmin_data_p->state = 0;
	garmin_data_p->flags = 0;
	garmin_data_p->count = 0;
	init_usb_anchor(&garmin_data_p->ग_लिखो_urbs);
	usb_set_serial_port_data(port, garmin_data_p);

	status = garmin_init_session(port);
	अगर (status)
		जाओ err_मुक्त;

	वापस 0;
err_मुक्त:
	kमुक्त(garmin_data_p);

	वापस status;
पूर्ण


अटल व्योम garmin_port_हटाओ(काष्ठा usb_serial_port *port)
अणु
	काष्ठा garmin_data *garmin_data_p = usb_get_serial_port_data(port);

	usb_समाप्त_anchored_urbs(&garmin_data_p->ग_लिखो_urbs);
	usb_समाप्त_urb(port->पूर्णांकerrupt_in_urb);
	del_समयr_sync(&garmin_data_p->समयr);
	kमुक्त(garmin_data_p);
पूर्ण


/* All of the device info needed */
अटल काष्ठा usb_serial_driver garmin_device = अणु
	.driver = अणु
		.owner       = THIS_MODULE,
		.name        = "garmin_gps",
	पूर्ण,
	.description         = "Garmin GPS usb/tty",
	.id_table            = id_table,
	.num_ports           = 1,
	.खोलो                = garmin_खोलो,
	.बंद               = garmin_बंद,
	.throttle            = garmin_throttle,
	.unthrottle          = garmin_unthrottle,
	.port_probe		= garmin_port_probe,
	.port_हटाओ		= garmin_port_हटाओ,
	.ग_लिखो               = garmin_ग_लिखो,
	.ग_लिखो_room          = garmin_ग_लिखो_room,
	.ग_लिखो_bulk_callback = garmin_ग_लिखो_bulk_callback,
	.पढ़ो_bulk_callback  = garmin_पढ़ो_bulk_callback,
	.पढ़ो_पूर्णांक_callback   = garmin_पढ़ो_पूर्णांक_callback,
पूर्ण;

अटल काष्ठा usb_serial_driver * स्थिर serial_drivers[] = अणु
	&garmin_device, शून्य
पूर्ण;

module_usb_serial_driver(serial_drivers, id_table);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

module_param(initial_mode, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(initial_mode, "Initial mode");
