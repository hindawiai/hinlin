<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	ds2490.c  USB to one wire bridge
 *
 * Copyright (c) 2004 Evgeniy Polyakov <zbr@ioremap.net>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/usb.h>
#समावेश <linux/slab.h>

#समावेश <linux/w1.h>

/* USB Standard */
/* USB Control request venकरोr type */
#घोषणा VENDOR				0x40

/* COMMAND TYPE CODES */
#घोषणा CONTROL_CMD			0x00
#घोषणा COMM_CMD			0x01
#घोषणा MODE_CMD			0x02

/* CONTROL COMMAND CODES */
#घोषणा CTL_RESET_DEVICE		0x0000
#घोषणा CTL_START_EXE			0x0001
#घोषणा CTL_RESUME_EXE			0x0002
#घोषणा CTL_HALT_EXE_IDLE		0x0003
#घोषणा CTL_HALT_EXE_DONE		0x0004
#घोषणा CTL_FLUSH_COMM_CMDS		0x0007
#घोषणा CTL_FLUSH_RCV_BUFFER		0x0008
#घोषणा CTL_FLUSH_XMT_BUFFER		0x0009
#घोषणा CTL_GET_COMM_CMDS		0x000A

/* MODE COMMAND CODES */
#घोषणा MOD_PULSE_EN			0x0000
#घोषणा MOD_SPEED_CHANGE_EN		0x0001
#घोषणा MOD_1WIRE_SPEED			0x0002
#घोषणा MOD_STRONG_PU_DURATION		0x0003
#घोषणा MOD_PULLDOWN_SLEWRATE		0x0004
#घोषणा MOD_PROG_PULSE_DURATION		0x0005
#घोषणा MOD_WRITE1_LOWTIME		0x0006
#घोषणा MOD_DSOW0_TREC			0x0007

/* COMMUNICATION COMMAND CODES */
#घोषणा COMM_ERROR_ESCAPE		0x0601
#घोषणा COMM_SET_DURATION		0x0012
#घोषणा COMM_BIT_IO			0x0020
#घोषणा COMM_PULSE			0x0030
#घोषणा COMM_1_WIRE_RESET		0x0042
#घोषणा COMM_BYTE_IO			0x0052
#घोषणा COMM_MATCH_ACCESS		0x0064
#घोषणा COMM_BLOCK_IO			0x0074
#घोषणा COMM_READ_STRAIGHT		0x0080
#घोषणा COMM_DO_RELEASE			0x6092
#घोषणा COMM_SET_PATH			0x00A2
#घोषणा COMM_WRITE_SRAM_PAGE		0x00B2
#घोषणा COMM_WRITE_EPROM		0x00C4
#घोषणा COMM_READ_CRC_PROT_PAGE		0x00D4
#घोषणा COMM_READ_REसूचीECT_PAGE_CRC	0x21E4
#घोषणा COMM_SEARCH_ACCESS		0x00F4

/* Communication command bits */
#घोषणा COMM_TYPE			0x0008
#घोषणा COMM_SE				0x0008
#घोषणा COMM_D				0x0008
#घोषणा COMM_Z				0x0008
#घोषणा COMM_CH				0x0008
#घोषणा COMM_SM				0x0008
#घोषणा COMM_R				0x0008
#घोषणा COMM_IM				0x0001

#घोषणा COMM_PS				0x4000
#घोषणा COMM_PST			0x4000
#घोषणा COMM_CIB			0x4000
#घोषणा COMM_RTS			0x4000
#घोषणा COMM_DT				0x2000
#घोषणा COMM_SPU			0x1000
#घोषणा COMM_F				0x0800
#घोषणा COMM_NTF			0x0400
#घोषणा COMM_ICP			0x0200
#घोषणा COMM_RST			0x0100

#घोषणा PULSE_PROG			0x01
#घोषणा PULSE_SPUE			0x02

#घोषणा BRANCH_MAIN			0xCC
#घोषणा BRANCH_AUX			0x33

/* Status flags */
#घोषणा ST_SPUA				0x01  /* Strong Pull-up is active */
#घोषणा ST_PRGA				0x02  /* 12V programming pulse is being generated */
#घोषणा ST_12VP				0x04  /* बाह्यal 12V programming voltage is present */
#घोषणा ST_PMOD				0x08  /* DS2490 घातered from USB and बाह्यal sources */
#घोषणा ST_HALT				0x10  /* DS2490 is currently halted */
#घोषणा ST_IDLE				0x20  /* DS2490 is currently idle */
#घोषणा ST_EPOF				0x80
/* Status transfer size, 16 bytes status, 16 byte result flags */
#घोषणा ST_SIZE				0x20

/* Result Register flags */
#घोषणा RR_DETECT			0xA5 /* New device detected */
#घोषणा RR_NRS				0x01 /* Reset no presence or ... */
#घोषणा RR_SH				0x02 /* लघु on reset or set path */
#घोषणा RR_APP				0x04 /* alarming presence on reset */
#घोषणा RR_VPP				0x08 /* 12V expected not seen */
#घोषणा RR_CMP				0x10 /* compare error */
#घोषणा RR_CRC				0x20 /* CRC error detected */
#घोषणा RR_RDP				0x40 /* redirected page */
#घोषणा RR_EOS				0x80 /* end of search error */

#घोषणा SPEED_NORMAL			0x00
#घोषणा SPEED_FLEXIBLE			0x01
#घोषणा SPEED_OVERDRIVE			0x02

#घोषणा NUM_EP				4
#घोषणा EP_CONTROL			0
#घोषणा EP_STATUS			1
#घोषणा EP_DATA_OUT			2
#घोषणा EP_DATA_IN			3

काष्ठा ds_device अणु
	काष्ठा list_head	ds_entry;

	काष्ठा usb_device	*udev;
	काष्ठा usb_पूर्णांकerface	*पूर्णांकf;

	पूर्णांक			ep[NUM_EP];

	/* Strong PullUp
	 * 0: pullup not active, अन्यथा duration in milliseconds
	 */
	पूर्णांक			spu_sleep;
	/* spu_bit contains COMM_SPU or 0 depending on अगर the strong pullup
	 * should be active or not क्रम ग_लिखोs.
	 */
	u16			spu_bit;

	u8			st_buf[ST_SIZE];
	u8			byte_buf;

	काष्ठा w1_bus_master	master;
पूर्ण;

काष्ठा ds_status अणु
	u8			enable;
	u8			speed;
	u8			pullup_dur;
	u8			ppuls_dur;
	u8			pullकरोwn_slew;
	u8			ग_लिखो1_समय;
	u8			ग_लिखो0_समय;
	u8			reserved0;
	u8			status;
	u8			command0;
	u8			command1;
	u8			command_buffer_status;
	u8			data_out_buffer_status;
	u8			data_in_buffer_status;
	u8			reserved1;
	u8			reserved2;
पूर्ण;

अटल LIST_HEAD(ds_devices);
अटल DEFINE_MUTEX(ds_mutex);

अटल पूर्णांक ds_send_control_cmd(काष्ठा ds_device *dev, u16 value, u16 index)
अणु
	पूर्णांक err;

	err = usb_control_msg(dev->udev, usb_sndctrlpipe(dev->udev, dev->ep[EP_CONTROL]),
			CONTROL_CMD, VENDOR, value, index, शून्य, 0, 1000);
	अगर (err < 0) अणु
		pr_err("Failed to send command control message %x.%x: err=%d.\n",
				value, index, err);
		वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ds_send_control_mode(काष्ठा ds_device *dev, u16 value, u16 index)
अणु
	पूर्णांक err;

	err = usb_control_msg(dev->udev, usb_sndctrlpipe(dev->udev, dev->ep[EP_CONTROL]),
			MODE_CMD, VENDOR, value, index, शून्य, 0, 1000);
	अगर (err < 0) अणु
		pr_err("Failed to send mode control message %x.%x: err=%d.\n",
				value, index, err);
		वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ds_send_control(काष्ठा ds_device *dev, u16 value, u16 index)
अणु
	पूर्णांक err;

	err = usb_control_msg(dev->udev, usb_sndctrlpipe(dev->udev, dev->ep[EP_CONTROL]),
			COMM_CMD, VENDOR, value, index, शून्य, 0, 1000);
	अगर (err < 0) अणु
		pr_err("Failed to send control message %x.%x: err=%d.\n",
				value, index, err);
		वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल अंतरभूत व्योम ds_prपूर्णांक_msg(अचिन्हित अक्षर *buf, अचिन्हित अक्षर *str, पूर्णांक off)
अणु
	pr_info("%45s: %8x\n", str, buf[off]);
पूर्ण

अटल व्योम ds_dump_status(काष्ठा ds_device *dev, अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	पूर्णांक i;

	pr_info("0x%x: count=%d, status: ", dev->ep[EP_STATUS], count);
	क्रम (i = 0; i < count; ++i)
		pr_info("%02x ", buf[i]);
	pr_info("\n");

	अगर (count >= 16) अणु
		ds_prपूर्णांक_msg(buf, "enable flag", 0);
		ds_prपूर्णांक_msg(buf, "1-wire speed", 1);
		ds_prपूर्णांक_msg(buf, "strong pullup duration", 2);
		ds_prपूर्णांक_msg(buf, "programming pulse duration", 3);
		ds_prपूर्णांक_msg(buf, "pulldown slew rate control", 4);
		ds_prपूर्णांक_msg(buf, "write-1 low time", 5);
		ds_prपूर्णांक_msg(buf, "data sample offset/write-0 recovery time",
			6);
		ds_prपूर्णांक_msg(buf, "reserved (test register)", 7);
		ds_prपूर्णांक_msg(buf, "device status flags", 8);
		ds_prपूर्णांक_msg(buf, "communication command byte 1", 9);
		ds_prपूर्णांक_msg(buf, "communication command byte 2", 10);
		ds_prपूर्णांक_msg(buf, "communication command buffer status", 11);
		ds_prपूर्णांक_msg(buf, "1-wire data output buffer status", 12);
		ds_prपूर्णांक_msg(buf, "1-wire data input buffer status", 13);
		ds_prपूर्णांक_msg(buf, "reserved", 14);
		ds_prपूर्णांक_msg(buf, "reserved", 15);
	पूर्ण
	क्रम (i = 16; i < count; ++i) अणु
		अगर (buf[i] == RR_DETECT) अणु
			ds_prपूर्णांक_msg(buf, "new device detect", i);
			जारी;
		पूर्ण
		ds_prपूर्णांक_msg(buf, "Result Register Value: ", i);
		अगर (buf[i] & RR_NRS)
			pr_info("NRS: Reset no presence or ...\n");
		अगर (buf[i] & RR_SH)
			pr_info("SH: short on reset or set path\n");
		अगर (buf[i] & RR_APP)
			pr_info("APP: alarming presence on reset\n");
		अगर (buf[i] & RR_VPP)
			pr_info("VPP: 12V expected not seen\n");
		अगर (buf[i] & RR_CMP)
			pr_info("CMP: compare error\n");
		अगर (buf[i] & RR_CRC)
			pr_info("CRC: CRC error detected\n");
		अगर (buf[i] & RR_RDP)
			pr_info("RDP: redirected page\n");
		अगर (buf[i] & RR_EOS)
			pr_info("EOS: end of search error\n");
	पूर्ण
पूर्ण

अटल पूर्णांक ds_recv_status(काष्ठा ds_device *dev, काष्ठा ds_status *st,
			  bool dump)
अणु
	पूर्णांक count, err;

	अगर (st)
		स_रखो(st, 0, माप(*st));

	count = 0;
	err = usb_पूर्णांकerrupt_msg(dev->udev,
				usb_rcvपूर्णांकpipe(dev->udev,
					       dev->ep[EP_STATUS]),
				dev->st_buf, माप(dev->st_buf),
				&count, 1000);
	अगर (err < 0) अणु
		pr_err("Failed to read 1-wire data from 0x%x: err=%d.\n",
		       dev->ep[EP_STATUS], err);
		वापस err;
	पूर्ण

	अगर (dump)
		ds_dump_status(dev, dev->st_buf, count);

	अगर (st && count >= माप(*st))
		स_नकल(st, dev->st_buf, माप(*st));

	वापस count;
पूर्ण

अटल व्योम ds_reset_device(काष्ठा ds_device *dev)
अणु
	ds_send_control_cmd(dev, CTL_RESET_DEVICE, 0);
	/* Always allow strong pullup which allow inभागidual ग_लिखोs to use
	 * the strong pullup.
	 */
	अगर (ds_send_control_mode(dev, MOD_PULSE_EN, PULSE_SPUE))
		pr_err("ds_reset_device: Error allowing strong pullup\n");
	/* Chip strong pullup समय was cleared. */
	अगर (dev->spu_sleep) अणु
		/* lower 4 bits are 0, see ds_set_pullup */
		u8 del = dev->spu_sleep>>4;
		अगर (ds_send_control(dev, COMM_SET_DURATION | COMM_IM, del))
			pr_err("ds_reset_device: Error setting duration\n");
	पूर्ण
पूर्ण

अटल पूर्णांक ds_recv_data(काष्ठा ds_device *dev, अचिन्हित अक्षर *buf, पूर्णांक size)
अणु
	पूर्णांक count, err;

	/* Careful on size.  If size is less than what is available in
	 * the input buffer, the device fails the bulk transfer and
	 * clears the input buffer.  It could पढ़ो the maximum size of
	 * the data buffer, but then करो you वापस the first, last, or
	 * some set of the middle size bytes?  As दीर्घ as the rest of
	 * the code is correct there will be size bytes रुकोing.  A
	 * call to ds_रुको_status will रुको until the device is idle
	 * and any data to be received would have been available.
	 */
	count = 0;
	err = usb_bulk_msg(dev->udev, usb_rcvbulkpipe(dev->udev, dev->ep[EP_DATA_IN]),
				buf, size, &count, 1000);
	अगर (err < 0) अणु
		pr_info("Clearing ep0x%x.\n", dev->ep[EP_DATA_IN]);
		usb_clear_halt(dev->udev, usb_rcvbulkpipe(dev->udev, dev->ep[EP_DATA_IN]));
		ds_recv_status(dev, शून्य, true);
		वापस err;
	पूर्ण

#अगर 0
	अणु
		पूर्णांक i;

		prपूर्णांकk("%s: count=%d: ", __func__, count);
		क्रम (i = 0; i < count; ++i)
			prपूर्णांकk("%02x ", buf[i]);
		prपूर्णांकk("\n");
	पूर्ण
#पूर्ण_अगर
	वापस count;
पूर्ण

अटल पूर्णांक ds_send_data(काष्ठा ds_device *dev, अचिन्हित अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक count, err;

	count = 0;
	err = usb_bulk_msg(dev->udev, usb_sndbulkpipe(dev->udev, dev->ep[EP_DATA_OUT]), buf, len, &count, 1000);
	अगर (err < 0) अणु
		pr_err("Failed to write 1-wire data to ep0x%x: "
			"err=%d.\n", dev->ep[EP_DATA_OUT], err);
		वापस err;
	पूर्ण

	वापस err;
पूर्ण

#अगर 0

पूर्णांक ds_stop_pulse(काष्ठा ds_device *dev, पूर्णांक limit)
अणु
	काष्ठा ds_status st;
	पूर्णांक count = 0, err = 0;

	करो अणु
		err = ds_send_control(dev, CTL_HALT_EXE_IDLE, 0);
		अगर (err)
			अवरोध;
		err = ds_send_control(dev, CTL_RESUME_EXE, 0);
		अगर (err)
			अवरोध;
		err = ds_recv_status(dev, &st, false);
		अगर (err)
			अवरोध;

		अगर ((st.status & ST_SPUA) == 0) अणु
			err = ds_send_control_mode(dev, MOD_PULSE_EN, 0);
			अगर (err)
				अवरोध;
		पूर्ण
	पूर्ण जबतक (++count < limit);

	वापस err;
पूर्ण

पूर्णांक ds_detect(काष्ठा ds_device *dev, काष्ठा ds_status *st)
अणु
	पूर्णांक err;

	err = ds_send_control_cmd(dev, CTL_RESET_DEVICE, 0);
	अगर (err)
		वापस err;

	err = ds_send_control(dev, COMM_SET_DURATION | COMM_IM, 0);
	अगर (err)
		वापस err;

	err = ds_send_control(dev, COMM_SET_DURATION | COMM_IM | COMM_TYPE, 0x40);
	अगर (err)
		वापस err;

	err = ds_send_control_mode(dev, MOD_PULSE_EN, PULSE_PROG);
	अगर (err)
		वापस err;

	err = ds_dump_status(dev, st);

	वापस err;
पूर्ण

#पूर्ण_अगर  /*  0  */

अटल पूर्णांक ds_रुको_status(काष्ठा ds_device *dev, काष्ठा ds_status *st)
अणु
	पूर्णांक err, count = 0;

	करो अणु
		st->status = 0;
		err = ds_recv_status(dev, st, false);
#अगर 0
		अगर (err >= 0) अणु
			पूर्णांक i;
			prपूर्णांकk("0x%x: count=%d, status: ", dev->ep[EP_STATUS], err);
			क्रम (i = 0; i < err; ++i)
				prपूर्णांकk("%02x ", dev->st_buf[i]);
			prपूर्णांकk("\n");
		पूर्ण
#पूर्ण_अगर
	पूर्ण जबतक (!(st->status & ST_IDLE) && !(err < 0) && ++count < 100);

	अगर (err >= 16 && st->status & ST_EPOF) अणु
		pr_info("Resetting device after ST_EPOF.\n");
		ds_reset_device(dev);
		/* Always dump the device status. */
		count = 101;
	पूर्ण

	/* Dump the status क्रम errors or अगर there is extended वापस data.
	 * The extended status includes new device detection (maybe someone
	 * can करो something with it).
	 */
	अगर (err > 16 || count >= 100 || err < 0)
		ds_dump_status(dev, dev->st_buf, err);

	/* Extended data isn't an error.  Well, a लघु is, but the dump
	 * would have alपढ़ोy told the user that and we can't करो anything
	 * about it in software anyway.
	 */
	अगर (count >= 100 || err < 0)
		वापस -1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक ds_reset(काष्ठा ds_device *dev)
अणु
	पूर्णांक err;

	/* Other potentionally पूर्णांकeresting flags क्रम reset.
	 *
	 * COMM_NTF: Return result रेजिस्टर feedback.  This could be used to
	 * detect some conditions such as लघु, alarming presence, or
	 * detect अगर a new device was detected.
	 *
	 * COMM_SE which allows SPEED_NORMAL, SPEED_FLEXIBLE, SPEED_OVERDRIVE:
	 * Select the data transfer rate.
	 */
	err = ds_send_control(dev, COMM_1_WIRE_RESET | COMM_IM, SPEED_NORMAL);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

#अगर 0
अटल पूर्णांक ds_set_speed(काष्ठा ds_device *dev, पूर्णांक speed)
अणु
	पूर्णांक err;

	अगर (speed != SPEED_NORMAL && speed != SPEED_FLEXIBLE && speed != SPEED_OVERDRIVE)
		वापस -EINVAL;

	अगर (speed != SPEED_OVERDRIVE)
		speed = SPEED_FLEXIBLE;

	speed &= 0xff;

	err = ds_send_control_mode(dev, MOD_1WIRE_SPEED, speed);
	अगर (err)
		वापस err;

	वापस err;
पूर्ण
#पूर्ण_अगर  /*  0  */

अटल पूर्णांक ds_set_pullup(काष्ठा ds_device *dev, पूर्णांक delay)
अणु
	पूर्णांक err = 0;
	u8 del = 1 + (u8)(delay >> 4);
	/* Just storing delay would not get the trunication and roundup. */
	पूर्णांक ms = del<<4;

	/* Enable spu_bit अगर a delay is set. */
	dev->spu_bit = delay ? COMM_SPU : 0;
	/* If delay is zero, it has alपढ़ोy been disabled, अगर the समय is
	 * the same as the hardware was last programmed to, there is also
	 * nothing more to करो.  Compare with the recalculated value ms
	 * rather than del or delay which can have a dअगरferent value.
	 */
	अगर (delay == 0 || ms == dev->spu_sleep)
		वापस err;

	err = ds_send_control(dev, COMM_SET_DURATION | COMM_IM, del);
	अगर (err)
		वापस err;

	dev->spu_sleep = ms;

	वापस err;
पूर्ण

अटल पूर्णांक ds_touch_bit(काष्ठा ds_device *dev, u8 bit, u8 *tbit)
अणु
	पूर्णांक err;
	काष्ठा ds_status st;

	err = ds_send_control(dev, COMM_BIT_IO | COMM_IM | (bit ? COMM_D : 0),
		0);
	अगर (err)
		वापस err;

	ds_रुको_status(dev, &st);

	err = ds_recv_data(dev, tbit, माप(*tbit));
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

#अगर 0
अटल पूर्णांक ds_ग_लिखो_bit(काष्ठा ds_device *dev, u8 bit)
अणु
	पूर्णांक err;
	काष्ठा ds_status st;

	/* Set COMM_ICP to ग_लिखो without a पढ़ोback.  Note, this will
	 * produce one समय slot, a करोwn followed by an up with COMM_D
	 * only determing the timing.
	 */
	err = ds_send_control(dev, COMM_BIT_IO | COMM_IM | COMM_ICP |
		(bit ? COMM_D : 0), 0);
	अगर (err)
		वापस err;

	ds_रुको_status(dev, &st);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ds_ग_लिखो_byte(काष्ठा ds_device *dev, u8 byte)
अणु
	पूर्णांक err;
	काष्ठा ds_status st;

	err = ds_send_control(dev, COMM_BYTE_IO | COMM_IM | dev->spu_bit, byte);
	अगर (err)
		वापस err;

	अगर (dev->spu_bit)
		msleep(dev->spu_sleep);

	err = ds_रुको_status(dev, &st);
	अगर (err)
		वापस err;

	err = ds_recv_data(dev, &dev->byte_buf, 1);
	अगर (err < 0)
		वापस err;

	वापस !(byte == dev->byte_buf);
पूर्ण

अटल पूर्णांक ds_पढ़ो_byte(काष्ठा ds_device *dev, u8 *byte)
अणु
	पूर्णांक err;
	काष्ठा ds_status st;

	err = ds_send_control(dev, COMM_BYTE_IO | COMM_IM, 0xff);
	अगर (err)
		वापस err;

	ds_रुको_status(dev, &st);

	err = ds_recv_data(dev, byte, माप(*byte));
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक ds_पढ़ो_block(काष्ठा ds_device *dev, u8 *buf, पूर्णांक len)
अणु
	काष्ठा ds_status st;
	पूर्णांक err;

	अगर (len > 64*1024)
		वापस -E2BIG;

	स_रखो(buf, 0xFF, len);

	err = ds_send_data(dev, buf, len);
	अगर (err < 0)
		वापस err;

	err = ds_send_control(dev, COMM_BLOCK_IO | COMM_IM, len);
	अगर (err)
		वापस err;

	ds_रुको_status(dev, &st);

	स_रखो(buf, 0x00, len);
	err = ds_recv_data(dev, buf, len);

	वापस err;
पूर्ण

अटल पूर्णांक ds_ग_लिखो_block(काष्ठा ds_device *dev, u8 *buf, पूर्णांक len)
अणु
	पूर्णांक err;
	काष्ठा ds_status st;

	err = ds_send_data(dev, buf, len);
	अगर (err < 0)
		वापस err;

	err = ds_send_control(dev, COMM_BLOCK_IO | COMM_IM | dev->spu_bit, len);
	अगर (err)
		वापस err;

	अगर (dev->spu_bit)
		msleep(dev->spu_sleep);

	ds_रुको_status(dev, &st);

	err = ds_recv_data(dev, buf, len);
	अगर (err < 0)
		वापस err;

	वापस !(err == len);
पूर्ण

अटल व्योम ds9490r_search(व्योम *data, काष्ठा w1_master *master,
	u8 search_type, w1_slave_found_callback callback)
अणु
	/* When starting with an existing id, the first id वापसed will
	 * be that device (अगर it is still on the bus most likely).
	 *
	 * If the number of devices found is less than or equal to the
	 * search_limit, that number of IDs will be वापसed.  If there are
	 * more, search_limit IDs will be वापसed followed by a non-zero
	 * discrepency value.
	 */
	काष्ठा ds_device *dev = data;
	पूर्णांक err;
	u16 value, index;
	काष्ठा ds_status st;
	पूर्णांक search_limit;
	पूर्णांक found = 0;
	पूर्णांक i;

	/* DS18b20 spec, 13.16 ms per device, 75 per second, sleep क्रम
	 * discovering 8 devices (1 bulk transfer and 1/2 FIFO size) at a समय.
	 */
	स्थिर अचिन्हित दीर्घ jसमय = msecs_to_jअगरfies(1000*8/75);
	/* FIFO 128 bytes, bulk packet size 64, पढ़ो a multiple of the
	 * packet size.
	 */
	स्थिर माप_प्रकार bufsize = 2 * 64;
	u64 *buf, *found_ids;

	buf = kदो_स्मृति(bufsize, GFP_KERNEL);
	अगर (!buf)
		वापस;

	/*
	 * We are holding the bus mutex during the scan, but adding devices via the
	 * callback needs the bus to be unlocked. So we queue up found ids here.
	 */
	found_ids = kदो_स्मृति_array(master->max_slave_count, माप(u64), GFP_KERNEL);
	अगर (!found_ids) अणु
		kमुक्त(buf);
		वापस;
	पूर्ण

	mutex_lock(&master->bus_mutex);

	/* address to start searching at */
	अगर (ds_send_data(dev, (u8 *)&master->search_id, 8) < 0)
		जाओ search_out;
	master->search_id = 0;

	value = COMM_SEARCH_ACCESS | COMM_IM | COMM_RST | COMM_SM | COMM_F |
		COMM_RTS;
	search_limit = master->max_slave_count;
	अगर (search_limit > 255)
		search_limit = 0;
	index = search_type | (search_limit << 8);
	अगर (ds_send_control(dev, value, index) < 0)
		जाओ search_out;

	करो अणु
		schedule_समयout(jसमय);

		err = ds_recv_status(dev, &st, false);
		अगर (err < 0 || err < माप(st))
			अवरोध;

		अगर (st.data_in_buffer_status) अणु
			/* Bulk in can receive partial ids, but when it करोes
			 * they fail crc and will be discarded anyway.
			 * That has only been seen when status in buffer
			 * is 0 and bulk is पढ़ो anyway, so करोn't पढ़ो
			 * bulk without first checking अगर status says there
			 * is data to पढ़ो.
			 */
			err = ds_recv_data(dev, (u8 *)buf, bufsize);
			अगर (err < 0)
				अवरोध;
			क्रम (i = 0; i < err/8; ++i) अणु
				found_ids[found++] = buf[i];
				/* can't know अगर there will be a discrepancy
				 * value after until the next id */
				अगर (found == search_limit) अणु
					master->search_id = buf[i];
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (test_bit(W1_ABORT_SEARCH, &master->flags))
			अवरोध;
	पूर्ण जबतक (!(st.status & (ST_IDLE | ST_HALT)));

	/* only जारी the search अगर some weren't found */
	अगर (found <= search_limit) अणु
		master->search_id = 0;
	पूर्ण अन्यथा अगर (!test_bit(W1_WARN_MAX_COUNT, &master->flags)) अणु
		/* Only max_slave_count will be scanned in a search,
		 * but it will start where it left off next search
		 * until all ids are identअगरied and then it will start
		 * over.  A जारीd search will report the previous
		 * last id as the first id (provided it is still on the
		 * bus).
		 */
		dev_info(&dev->udev->dev, "%s: max_slave_count %d reached, "
			"will continue next search.\n", __func__,
			master->max_slave_count);
		set_bit(W1_WARN_MAX_COUNT, &master->flags);
	पूर्ण

search_out:
	mutex_unlock(&master->bus_mutex);
	kमुक्त(buf);

	क्रम (i = 0; i < found; i++) /* run callback क्रम all queued up IDs */
		callback(master, found_ids[i]);
	kमुक्त(found_ids);
पूर्ण

#अगर 0
/*
 * FIXME: अगर this disabled code is ever used in the future all ds_send_data()
 * calls must be changed to use a DMAable buffer.
 */
अटल पूर्णांक ds_match_access(काष्ठा ds_device *dev, u64 init)
अणु
	पूर्णांक err;
	काष्ठा ds_status st;

	err = ds_send_data(dev, (अचिन्हित अक्षर *)&init, माप(init));
	अगर (err)
		वापस err;

	ds_रुको_status(dev, &st);

	err = ds_send_control(dev, COMM_MATCH_ACCESS | COMM_IM | COMM_RST, 0x0055);
	अगर (err)
		वापस err;

	ds_रुको_status(dev, &st);

	वापस 0;
पूर्ण

अटल पूर्णांक ds_set_path(काष्ठा ds_device *dev, u64 init)
अणु
	पूर्णांक err;
	काष्ठा ds_status st;
	u8 buf[9];

	स_नकल(buf, &init, 8);
	buf[8] = BRANCH_MAIN;

	err = ds_send_data(dev, buf, माप(buf));
	अगर (err)
		वापस err;

	ds_रुको_status(dev, &st);

	err = ds_send_control(dev, COMM_SET_PATH | COMM_IM | COMM_RST, 0);
	अगर (err)
		वापस err;

	ds_रुको_status(dev, &st);

	वापस 0;
पूर्ण

#पूर्ण_अगर  /*  0  */

अटल u8 ds9490r_touch_bit(व्योम *data, u8 bit)
अणु
	काष्ठा ds_device *dev = data;

	अगर (ds_touch_bit(dev, bit, &dev->byte_buf))
		वापस 0;

	वापस dev->byte_buf;
पूर्ण

#अगर 0
अटल व्योम ds9490r_ग_लिखो_bit(व्योम *data, u8 bit)
अणु
	काष्ठा ds_device *dev = data;

	ds_ग_लिखो_bit(dev, bit);
पूर्ण

अटल u8 ds9490r_पढ़ो_bit(व्योम *data)
अणु
	काष्ठा ds_device *dev = data;
	पूर्णांक err;

	err = ds_touch_bit(dev, 1, &dev->byte_buf);
	अगर (err)
		वापस 0;

	वापस dev->byte_buf & 1;
पूर्ण
#पूर्ण_अगर

अटल व्योम ds9490r_ग_लिखो_byte(व्योम *data, u8 byte)
अणु
	काष्ठा ds_device *dev = data;

	ds_ग_लिखो_byte(dev, byte);
पूर्ण

अटल u8 ds9490r_पढ़ो_byte(व्योम *data)
अणु
	काष्ठा ds_device *dev = data;
	पूर्णांक err;

	err = ds_पढ़ो_byte(dev, &dev->byte_buf);
	अगर (err)
		वापस 0;

	वापस dev->byte_buf;
पूर्ण

अटल व्योम ds9490r_ग_लिखो_block(व्योम *data, स्थिर u8 *buf, पूर्णांक len)
अणु
	काष्ठा ds_device *dev = data;
	u8 *tbuf;

	अगर (len <= 0)
		वापस;

	tbuf = kmemdup(buf, len, GFP_KERNEL);
	अगर (!tbuf)
		वापस;

	ds_ग_लिखो_block(dev, tbuf, len);

	kमुक्त(tbuf);
पूर्ण

अटल u8 ds9490r_पढ़ो_block(व्योम *data, u8 *buf, पूर्णांक len)
अणु
	काष्ठा ds_device *dev = data;
	पूर्णांक err;
	u8 *tbuf;

	अगर (len <= 0)
		वापस 0;

	tbuf = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!tbuf)
		वापस 0;

	err = ds_पढ़ो_block(dev, tbuf, len);
	अगर (err >= 0)
		स_नकल(buf, tbuf, len);

	kमुक्त(tbuf);

	वापस err >= 0 ? len : 0;
पूर्ण

अटल u8 ds9490r_reset(व्योम *data)
अणु
	काष्ठा ds_device *dev = data;
	पूर्णांक err;

	err = ds_reset(dev);
	अगर (err)
		वापस 1;

	वापस 0;
पूर्ण

अटल u8 ds9490r_set_pullup(व्योम *data, पूर्णांक delay)
अणु
	काष्ठा ds_device *dev = data;

	अगर (ds_set_pullup(dev, delay))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ds_w1_init(काष्ठा ds_device *dev)
अणु
	स_रखो(&dev->master, 0, माप(काष्ठा w1_bus_master));

	/* Reset the device as it can be in a bad state.
	 * This is necessary because a block ग_लिखो will रुको क्रम data
	 * to be placed in the output buffer and block any later
	 * commands which will keep accumulating and the device will
	 * not be idle.  Another हाल is removing the ds2490 module
	 * जबतक a bus search is in progress, somehow a few commands
	 * get through, but the input transfers fail leaving data in
	 * the input buffer.  This will cause the next पढ़ो to fail
	 * see the note in ds_recv_data.
	 */
	ds_reset_device(dev);

	dev->master.data	= dev;
	dev->master.touch_bit	= &ds9490r_touch_bit;
	/* पढ़ो_bit and ग_लिखो_bit in w1_bus_master are expected to set and
	 * sample the line level.  For ग_लिखो_bit that means it is expected to
	 * set it to that value and leave it there.  ds2490 only supports an
	 * inभागidual समय slot at the lowest level.  The requirement from
	 * pulling the bus state करोwn to पढ़ोing the state is 15us, something
	 * that isn't realistic on the USB bus anyway.
	dev->master.पढ़ो_bit	= &ds9490r_पढ़ो_bit;
	dev->master.ग_लिखो_bit	= &ds9490r_ग_लिखो_bit;
	*/
	dev->master.पढ़ो_byte	= &ds9490r_पढ़ो_byte;
	dev->master.ग_लिखो_byte	= &ds9490r_ग_लिखो_byte;
	dev->master.पढ़ो_block	= &ds9490r_पढ़ो_block;
	dev->master.ग_लिखो_block	= &ds9490r_ग_लिखो_block;
	dev->master.reset_bus	= &ds9490r_reset;
	dev->master.set_pullup	= &ds9490r_set_pullup;
	dev->master.search	= &ds9490r_search;

	वापस w1_add_master_device(&dev->master);
पूर्ण

अटल व्योम ds_w1_fini(काष्ठा ds_device *dev)
अणु
	w1_हटाओ_master_device(&dev->master);
पूर्ण

अटल पूर्णांक ds_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		    स्थिर काष्ठा usb_device_id *udev_id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा ds_device *dev;
	पूर्णांक i, err, alt;

	dev = kzalloc(माप(काष्ठा ds_device), GFP_KERNEL);
	अगर (!dev) अणु
		pr_info("Failed to allocate new DS9490R structure.\n");
		वापस -ENOMEM;
	पूर्ण
	dev->udev = usb_get_dev(udev);
	अगर (!dev->udev) अणु
		err = -ENOMEM;
		जाओ err_out_मुक्त;
	पूर्ण
	स_रखो(dev->ep, 0, माप(dev->ep));

	usb_set_पूर्णांकfdata(पूर्णांकf, dev);

	err = usb_reset_configuration(dev->udev);
	अगर (err) अणु
		dev_err(&dev->udev->dev,
			"Failed to reset configuration: err=%d.\n", err);
		जाओ err_out_clear;
	पूर्ण

	/* alternative 3, 1ms पूर्णांकerrupt (greatly speeds search), 64 byte bulk */
	alt = 3;
	err = usb_set_पूर्णांकerface(dev->udev,
		पूर्णांकf->cur_altsetting->desc.bInterfaceNumber, alt);
	अगर (err) अणु
		dev_err(&dev->udev->dev, "Failed to set alternative setting %d "
			"for %d interface: err=%d.\n", alt,
			पूर्णांकf->cur_altsetting->desc.bInterfaceNumber, err);
		जाओ err_out_clear;
	पूर्ण

	अगरace_desc = पूर्णांकf->cur_altsetting;
	अगर (अगरace_desc->desc.bNumEndpoपूर्णांकs != NUM_EP-1) अणु
		pr_info("Num endpoints=%d. It is not DS9490R.\n",
			अगरace_desc->desc.bNumEndpoपूर्णांकs);
		err = -EINVAL;
		जाओ err_out_clear;
	पूर्ण

	/*
	 * This loop करोesn'd show control 0 endpoपूर्णांक,
	 * so we will fill only 1-3 endpoपूर्णांकs entry.
	 */
	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; ++i) अणु
		endpoपूर्णांक = &अगरace_desc->endpoपूर्णांक[i].desc;

		dev->ep[i+1] = endpoपूर्णांक->bEndpoपूर्णांकAddress;
#अगर 0
		prपूर्णांकk("%d: addr=%x, size=%d, dir=%s, type=%x\n",
			i, endpoपूर्णांक->bEndpoपूर्णांकAddress, le16_to_cpu(endpoपूर्णांक->wMaxPacketSize),
			(endpoपूर्णांक->bEndpoपूर्णांकAddress & USB_सूची_IN)?"IN":"OUT",
			endpoपूर्णांक->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK);
#पूर्ण_अगर
	पूर्ण

	err = ds_w1_init(dev);
	अगर (err)
		जाओ err_out_clear;

	mutex_lock(&ds_mutex);
	list_add_tail(&dev->ds_entry, &ds_devices);
	mutex_unlock(&ds_mutex);

	वापस 0;

err_out_clear:
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	usb_put_dev(dev->udev);
err_out_मुक्त:
	kमुक्त(dev);
	वापस err;
पूर्ण

अटल व्योम ds_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ds_device *dev;

	dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	अगर (!dev)
		वापस;

	mutex_lock(&ds_mutex);
	list_del(&dev->ds_entry);
	mutex_unlock(&ds_mutex);

	ds_w1_fini(dev);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	usb_put_dev(dev->udev);
	kमुक्त(dev);
पूर्ण

अटल स्थिर काष्ठा usb_device_id ds_id_table[] = अणु
	अणु USB_DEVICE(0x04fa, 0x2490) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, ds_id_table);

अटल काष्ठा usb_driver ds_driver = अणु
	.name =		"DS9490R",
	.probe =	ds_probe,
	.disconnect =	ds_disconnect,
	.id_table =	ds_id_table,
पूर्ण;
module_usb_driver(ds_driver);

MODULE_AUTHOR("Evgeniy Polyakov <zbr@ioremap.net>");
MODULE_DESCRIPTION("DS2490 USB <-> W1 bus master driver (DS9490*)");
MODULE_LICENSE("GPL");
