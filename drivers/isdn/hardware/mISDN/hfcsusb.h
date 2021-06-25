<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * hfcsusb.h, HFC-S USB mISDN driver
 */

#अगर_अघोषित __HFCSUSB_H__
#घोषणा __HFCSUSB_H__


#घोषणा DRIVER_NAME "HFC-S_USB"

#घोषणा DBG_HFC_CALL_TRACE	0x00010000
#घोषणा DBG_HFC_FIFO_VERBOSE	0x00020000
#घोषणा DBG_HFC_USB_VERBOSE	0x00100000
#घोषणा DBG_HFC_URB_INFO	0x00200000
#घोषणा DBG_HFC_URB_ERROR	0x00400000

#घोषणा DEFAULT_TRANSP_BURST_SZ 128

#घोषणा HFC_CTRL_TIMEOUT	20	/* 5ms समयout writing/पढ़ोing regs */
#घोषणा CLKDEL_TE		0x0f	/* CLKDEL in TE mode */
#घोषणा CLKDEL_NT		0x6c	/* CLKDEL in NT mode */

/* hfcsusb Layer1 commands */
#घोषणा HFC_L1_ACTIVATE_TE		1
#घोषणा HFC_L1_ACTIVATE_NT		2
#घोषणा HFC_L1_DEACTIVATE_NT		3
#घोषणा HFC_L1_FORCE_DEACTIVATE_TE	4

/* cmd FLAGS in HFCUSB_STATES रेजिस्टर */
#घोषणा HFCUSB_LOAD_STATE	0x10
#घोषणा HFCUSB_ACTIVATE		0x20
#घोषणा HFCUSB_DO_ACTION	0x40
#घोषणा HFCUSB_NT_G2_G3		0x80

/* समयrs */
#घोषणा NT_ACTIVATION_TIMER	0x01	/* enables NT mode activation Timer */
#घोषणा NT_T1_COUNT		10

#घोषणा MAX_BCH_SIZE		2048	/* allowed B-channel packet size */

#घोषणा HFCUSB_RX_THRESHOLD	64	/* threshold क्रम fअगरo report bit rx */
#घोषणा HFCUSB_TX_THRESHOLD	96	/* threshold क्रम fअगरo report bit tx */

#घोषणा HFCUSB_CHIP_ID		0x16	/* Chip ID रेजिस्टर index */
#घोषणा HFCUSB_CIRM		0x00	/* cirm रेजिस्टर index */
#घोषणा HFCUSB_USB_SIZE		0x07	/* पूर्णांक length रेजिस्टर */
#घोषणा HFCUSB_USB_SIZE_I	0x06	/* iso length रेजिस्टर */
#घोषणा HFCUSB_F_CROSS		0x0b	/* bit order रेजिस्टर */
#घोषणा HFCUSB_CLKDEL		0x37	/* bit delay रेजिस्टर */
#घोषणा HFCUSB_CON_HDLC		0xfa	/* channel connect रेजिस्टर */
#घोषणा HFCUSB_HDLC_PAR		0xfb
#घोषणा HFCUSB_SCTRL		0x31	/* S-bus control रेजिस्टर (tx) */
#घोषणा HFCUSB_SCTRL_E		0x32	/* same क्रम E and special funcs */
#घोषणा HFCUSB_SCTRL_R		0x33	/* S-bus control रेजिस्टर (rx) */
#घोषणा HFCUSB_F_THRES		0x0c	/* threshold रेजिस्टर */
#घोषणा HFCUSB_FIFO		0x0f	/* fअगरo select रेजिस्टर */
#घोषणा HFCUSB_F_USAGE		0x1a	/* fअगरo usage रेजिस्टर */
#घोषणा HFCUSB_MST_MODE0	0x14
#घोषणा HFCUSB_MST_MODE1	0x15
#घोषणा HFCUSB_P_DATA		0x1f
#घोषणा HFCUSB_INC_RES_F	0x0e
#घोषणा HFCUSB_B1_SSL		0x20
#घोषणा HFCUSB_B2_SSL		0x21
#घोषणा HFCUSB_B1_RSL		0x24
#घोषणा HFCUSB_B2_RSL		0x25
#घोषणा HFCUSB_STATES		0x30


#घोषणा HFCUSB_CHIPID		0x40	/* ID value of HFC-S USB */

/* fअगरo रेजिस्टरs */
#घोषणा HFCUSB_NUM_FIFOS	8	/* maximum number of fअगरos */
#घोषणा HFCUSB_B1_TX		0	/* index क्रम B1 transmit bulk/पूर्णांक */
#घोषणा HFCUSB_B1_RX		1	/* index क्रम B1 receive bulk/पूर्णांक */
#घोषणा HFCUSB_B2_TX		2
#घोषणा HFCUSB_B2_RX		3
#घोषणा HFCUSB_D_TX		4
#घोषणा HFCUSB_D_RX		5
#घोषणा HFCUSB_PCM_TX		6
#घोषणा HFCUSB_PCM_RX		7


#घोषणा USB_INT		0
#घोषणा USB_BULK	1
#घोषणा USB_ISOC	2

#घोषणा ISOC_PACKETS_D	8
#घोषणा ISOC_PACKETS_B	8
#घोषणा ISO_BUFFER_SIZE	128

/* defines how much ISO packets are handled in one URB */
अटल पूर्णांक iso_packets[8] =
अणु ISOC_PACKETS_B, ISOC_PACKETS_B, ISOC_PACKETS_B, ISOC_PACKETS_B,
  ISOC_PACKETS_D, ISOC_PACKETS_D, ISOC_PACKETS_D, ISOC_PACKETS_D
पूर्ण;


/* Fअगरo flow Control क्रम TX ISO */
#घोषणा SINK_MAX	68
#घोषणा SINK_MIN	48
#घोषणा SINK_DMIN	12
#घोषणा SINK_DMAX	18
#घोषणा BITLINE_INF	(-96 * 8)

/* HFC-S USB रेजिस्टर access by Control-URSs */
#घोषणा ग_लिखो_reg_atomic(a, b, c)					\
	usb_control_msg((a)->dev, (a)->ctrl_out_pipe, 0, 0x40, (c), (b), \
			0, 0, HFC_CTRL_TIMEOUT)
#घोषणा पढ़ो_reg_atomic(a, b, c)					\
	usb_control_msg((a)->dev, (a)->ctrl_in_pipe, 1, 0xC0, 0, (b), (c), \
			1, HFC_CTRL_TIMEOUT)
#घोषणा HFC_CTRL_बफ_मानE 64

काष्ठा ctrl_buf अणु
	__u8 hfcs_reg;		/* रेजिस्टर number */
	__u8 reg_val;		/* value to be written (or पढ़ो) */
पूर्ण;

/*
 * URB error codes
 * Used to represent a list of values and their respective symbolic names
 */
काष्ठा hfcusb_symbolic_list अणु
	स्थिर पूर्णांक num;
	स्थिर अक्षर *name;
पूर्ण;

अटल काष्ठा hfcusb_symbolic_list urb_errlist[] = अणु
	अणु-ENOMEM, "No memory for allocation of internal structures"पूर्ण,
	अणु-ENOSPC, "The host controller's bandwidth is already consumed"पूर्ण,
	अणु-ENOENT, "URB was canceled by unlink_urb"पूर्ण,
	अणु-EXDEV, "ISO transfer only partially completed"पूर्ण,
	अणु-EAGAIN, "Too match scheduled for the future"पूर्ण,
	अणु-ENXIO, "URB already queued"पूर्ण,
	अणु-EFBIG, "Too much ISO frames requested"पूर्ण,
	अणु-ENOSR, "Buffer error (overrun)"पूर्ण,
	अणु-EPIPE, "Specified endpoint is stalled (device not responding)"पूर्ण,
	अणु-EOVERFLOW, "Babble (bad cable?)"पूर्ण,
	अणु-EPROTO, "Bit-stuff error (bad cable?)"पूर्ण,
	अणु-EILSEQ, "CRC/Timeout"पूर्ण,
	अणु-ETIMEDOUT, "NAK (device does not respond)"पूर्ण,
	अणु-ESHUTDOWN, "Device unplugged"पूर्ण,
	अणु-1, शून्यपूर्ण
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *
symbolic(काष्ठा hfcusb_symbolic_list list[], स्थिर पूर्णांक num)
अणु
	पूर्णांक i;
	क्रम (i = 0; list[i].name != शून्य; i++)
		अगर (list[i].num == num)
			वापस list[i].name;
	वापस "<unknown USB Error>";
पूर्ण

/* USB descriptor need to contain one of the following EndPoपूर्णांक combination: */
#घोषणा CNF_4INT3ISO	1	/* 4 INT IN, 3 ISO OUT */
#घोषणा CNF_3INT3ISO	2	/* 3 INT IN, 3 ISO OUT */
#घोषणा CNF_4ISO3ISO	3	/* 4 ISO IN, 3 ISO OUT */
#घोषणा CNF_3ISO3ISO	4	/* 3 ISO IN, 3 ISO OUT */

#घोषणा EP_NUL 1	/* Endpoपूर्णांक at this position not allowed */
#घोषणा EP_NOP 2	/* all type of endpoपूर्णांकs allowed at this position */
#घोषणा EP_ISO 3	/* Isochron endpoपूर्णांक mandatory at this position */
#घोषणा EP_BLK 4	/* Bulk endpoपूर्णांक mandatory at this position */
#घोषणा EP_INT 5	/* Interrupt endpoपूर्णांक mandatory at this position */

#घोषणा HFC_CHAN_B1	0
#घोषणा HFC_CHAN_B2	1
#घोषणा HFC_CHAN_D	2
#घोषणा HFC_CHAN_E	3


/*
 * List of all supported endpoपूर्णांक configuration sets, used to find the
 * best matching endpoपूर्णांक configuration within a device's USB descriptor.
 * We need at least 3 RX endpoपूर्णांकs, and 3 TX endpoपूर्णांकs, either
 * INT-in and ISO-out, or ISO-in and ISO-out)
 * with 4 RX endpoपूर्णांकs even E-Channel logging is possible
 */
अटल पूर्णांक
validconf[][19] = अणु
	/* INT in, ISO out config */
	अणुEP_NUL, EP_INT, EP_NUL, EP_INT, EP_NUL, EP_INT, EP_NOP, EP_INT,
	 EP_ISO, EP_NUL, EP_ISO, EP_NUL, EP_ISO, EP_NUL, EP_NUL, EP_NUL,
	 CNF_4INT3ISO, 2, 1पूर्ण,
	अणुEP_NUL, EP_INT, EP_NUL, EP_INT, EP_NUL, EP_INT, EP_NUL, EP_NUL,
	 EP_ISO, EP_NUL, EP_ISO, EP_NUL, EP_ISO, EP_NUL, EP_NUL, EP_NUL,
	 CNF_3INT3ISO, 2, 0पूर्ण,
	/* ISO in, ISO out config */
	अणुEP_NOP, EP_NOP, EP_NOP, EP_NOP, EP_NOP, EP_NOP, EP_NOP, EP_NOP,
	 EP_ISO, EP_ISO, EP_ISO, EP_ISO, EP_ISO, EP_ISO, EP_NOP, EP_ISO,
	 CNF_4ISO3ISO, 2, 1पूर्ण,
	अणुEP_NUL, EP_NUL, EP_NUL, EP_NUL, EP_NUL, EP_NUL, EP_NUL, EP_NUL,
	 EP_ISO, EP_ISO, EP_ISO, EP_ISO, EP_ISO, EP_ISO, EP_NUL, EP_NUL,
	 CNF_3ISO3ISO, 2, 0पूर्ण,
	अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण /* EOL element */
पूर्ण;

/* string description of chosen config */
अटल अक्षर *conf_str[] = अणु
	"4 Interrupt IN + 3 Isochron OUT",
	"3 Interrupt IN + 3 Isochron OUT",
	"4 Isochron IN + 3 Isochron OUT",
	"3 Isochron IN + 3 Isochron OUT"
पूर्ण;


#घोषणा LED_OFF		0	/* no LED support */
#घोषणा LED_SCHEME1	1	/* LED standard scheme */
#घोषणा LED_SCHEME2	2	/* not used yet... */

#घोषणा LED_POWER_ON	1
#घोषणा LED_POWER_OFF	2
#घोषणा LED_S0_ON	3
#घोषणा LED_S0_OFF	4
#घोषणा LED_B1_ON	5
#घोषणा LED_B1_OFF	6
#घोषणा LED_B1_DATA	7
#घोषणा LED_B2_ON	8
#घोषणा LED_B2_OFF	9
#घोषणा LED_B2_DATA	10

#घोषणा LED_NORMAL	0	/* LEDs are normal */
#घोषणा LED_INVERTED	1	/* LEDs are inverted */

/* समय in ms to perक्रमm a Flashing LED when B-Channel has traffic */
#घोषणा LED_TIME      250



काष्ठा hfcsusb;
काष्ठा usb_fअगरo;

/* काष्ठाure defining input+output fअगरos (पूर्णांकerrupt/bulk mode) */
काष्ठा iso_urb अणु
	काष्ठा urb *urb;
	__u8 buffer[ISO_BUFFER_SIZE];	/* buffer rx/tx USB URB data */
	काष्ठा usb_fअगरo *owner_fअगरo;	/* poपूर्णांकer to owner fअगरo */
	__u8 indx; /* Fअगरos's ISO द्विगुन buffer 0 or 1 ? */
#अगर_घोषित ISO_FRAME_START_DEBUG
	पूर्णांक start_frames[ISO_FRAME_START_RING_COUNT];
	__u8 iso_frm_strt_pos; /* index in start_frame[] */
#पूर्ण_अगर
पूर्ण;

काष्ठा usb_fअगरo अणु
	पूर्णांक fअगरonum;		/* fअगरo index attached to this काष्ठाure */
	पूर्णांक active;		/* fअगरo is currently active */
	काष्ठा hfcsusb *hw;	/* poपूर्णांकer to मुख्य काष्ठाure */
	पूर्णांक pipe;		/* address of endpoपूर्णांक */
	__u8 usb_packet_maxlen;	/* maximum length क्रम usb transfer */
	अचिन्हित पूर्णांक max_size;	/* maximum size of receive/send packet */
	__u8 पूर्णांकervall;		/* पूर्णांकerrupt पूर्णांकerval */
	काष्ठा urb *urb;	/* transfer काष्ठाure क्रम usb routines */
	__u8 buffer[128];	/* buffer USB INT OUT URB data */
	पूर्णांक bit_line;		/* how much bits are in the fअगरo? */

	__u8 usb_transfer_mode; /* चयनed between ISO and INT */
	काष्ठा iso_urb	iso[2]; /* two urbs to have one always
				   one pending */

	काष्ठा dchannel *dch;	/* link to hfcsusb_t->dch */
	काष्ठा bchannel *bch;	/* link to hfcsusb_t->bch */
	काष्ठा dchannel *ech;	/* link to hfcsusb_t->ech, TODO: E-CHANNEL */
	पूर्णांक last_urblen;	/* remember length of last packet */
	__u8 stop_gracefull;	/* stops URB retransmission */
पूर्ण;

काष्ठा hfcsusb अणु
	काष्ठा list_head	list;
	काष्ठा dchannel		dch;
	काष्ठा bchannel		bch[2];
	काष्ठा dchannel		ech; /* TODO : रुको क्रम काष्ठा echannel ;) */

	काष्ठा usb_device	*dev;		/* our device */
	काष्ठा usb_पूर्णांकerface	*पूर्णांकf;		/* used पूर्णांकerface */
	पूर्णांक			अगर_used;	/* used पूर्णांकerface number */
	पूर्णांक			alt_used;	/* used alternate config */
	पूर्णांक			cfg_used;	/* configuration index used */
	पूर्णांक			vend_idx;	/* index in hfcsusb_idtab */
	पूर्णांक			packet_size;
	पूर्णांक			iso_packet_size;
	काष्ठा usb_fअगरo		fअगरos[HFCUSB_NUM_FIFOS];

	/* control pipe background handling */
	काष्ठा ctrl_buf		ctrl_buff[HFC_CTRL_बफ_मानE];
	पूर्णांक			ctrl_in_idx, ctrl_out_idx, ctrl_cnt;
	काष्ठा urb		*ctrl_urb;
	काष्ठा usb_ctrlrequest	ctrl_ग_लिखो;
	काष्ठा usb_ctrlrequest	ctrl_पढ़ो;
	पूर्णांक			ctrl_paksize;
	पूर्णांक			ctrl_in_pipe, ctrl_out_pipe;
	spinlock_t		ctrl_lock; /* lock क्रम ctrl */
	spinlock_t              lock;

	__u8			threshold_mask;
	__u8			led_state;

	__u8			protocol;
	पूर्णांक			nt_समयr;
	पूर्णांक			खोलो;
	__u8			समयrs;
	__u8			initकरोne;
	अक्षर			name[MISDN_MAX_IDLEN];
पूर्ण;

/* निजी venकरोr specअगरic data */
काष्ठा hfcsusb_vdata अणु
	__u8		led_scheme;  /* led display scheme */
	चिन्हित लघु	led_bits[8]; /* array of 8 possible LED biपंचांगask */
	अक्षर		*vend_name;  /* device name */
पूर्ण;


#घोषणा HFC_MAX_TE_LAYER1_STATE 8
#घोषणा HFC_MAX_NT_LAYER1_STATE 4

अटल स्थिर अक्षर *HFC_TE_LAYER1_STATES[HFC_MAX_TE_LAYER1_STATE + 1] = अणु
	"TE F0 - Reset",
	"TE F1 - Reset",
	"TE F2 - Sensing",
	"TE F3 - Deactivated",
	"TE F4 - Awaiting signal",
	"TE F5 - Identifying input",
	"TE F6 - Synchronized",
	"TE F7 - Activated",
	"TE F8 - Lost framing",
पूर्ण;

अटल स्थिर अक्षर *HFC_NT_LAYER1_STATES[HFC_MAX_NT_LAYER1_STATE + 1] = अणु
	"NT G0 - Reset",
	"NT G1 - Deactive",
	"NT G2 - Pending activation",
	"NT G3 - Active",
	"NT G4 - Pending deactivation",
पूर्ण;

/* supported devices */
अटल स्थिर काष्ठा usb_device_id hfcsusb_idtab[] = अणु
	अणु
		USB_DEVICE(0x0959, 0x2bd0),
		.driver_info = (अचिन्हित दीर्घ) &((काष्ठा hfcsusb_vdata)
			अणुLED_OFF, अणु4, 0, 2, 1पूर्ण,
					"ISDN USB TA (Cologne Chip HFC-S USB based)"पूर्ण),
	पूर्ण,
	अणु
		USB_DEVICE(0x0675, 0x1688),
		.driver_info = (अचिन्हित दीर्घ) &((काष्ठा hfcsusb_vdata)
			अणुLED_SCHEME1, अणु1, 2, 0, 0पूर्ण,
					"DrayTek miniVigor 128 USB ISDN TA"पूर्ण),
	पूर्ण,
	अणु
		USB_DEVICE(0x07b0, 0x0007),
		.driver_info = (अचिन्हित दीर्घ) &((काष्ठा hfcsusb_vdata)
			अणुLED_SCHEME1, अणु0x80, -64, -32, -16पूर्ण,
					"Billion tiny USB ISDN TA 128"पूर्ण),
	पूर्ण,
	अणु
		USB_DEVICE(0x0742, 0x2008),
		.driver_info = (अचिन्हित दीर्घ) &((काष्ठा hfcsusb_vdata)
			अणुLED_SCHEME1, अणु4, 0, 2, 1पूर्ण,
					"Stollmann USB TA"पूर्ण),
	पूर्ण,
	अणु
		USB_DEVICE(0x0742, 0x2009),
		.driver_info = (अचिन्हित दीर्घ) &((काष्ठा hfcsusb_vdata)
			अणुLED_SCHEME1, अणु4, 0, 2, 1पूर्ण,
					"Aceex USB ISDN TA"पूर्ण),
	पूर्ण,
	अणु
		USB_DEVICE(0x0742, 0x200A),
		.driver_info = (अचिन्हित दीर्घ) &((काष्ठा hfcsusb_vdata)
			अणुLED_SCHEME1, अणु4, 0, 2, 1पूर्ण,
					"OEM USB ISDN TA"पूर्ण),
	पूर्ण,
	अणु
		USB_DEVICE(0x08e3, 0x0301),
		.driver_info = (अचिन्हित दीर्घ) &((काष्ठा hfcsusb_vdata)
			अणुLED_SCHEME1, अणु2, 0, 1, 4पूर्ण,
					"Olitec USB RNIS"पूर्ण),
	पूर्ण,
	अणु
		USB_DEVICE(0x07fa, 0x0846),
		.driver_info = (अचिन्हित दीर्घ) &((काष्ठा hfcsusb_vdata)
			अणुLED_SCHEME1, अणु0x80, -64, -32, -16पूर्ण,
					"Bewan Modem RNIS USB"पूर्ण),
	पूर्ण,
	अणु
		USB_DEVICE(0x07fa, 0x0847),
		.driver_info = (अचिन्हित दीर्घ) &((काष्ठा hfcsusb_vdata)
			अणुLED_SCHEME1, अणु0x80, -64, -32, -16पूर्ण,
					"Djinn Numeris USB"पूर्ण),
	पूर्ण,
	अणु
		USB_DEVICE(0x07b0, 0x0006),
		.driver_info = (अचिन्हित दीर्घ) &((काष्ठा hfcsusb_vdata)
			अणुLED_SCHEME1, अणु0x80, -64, -32, -16पूर्ण,
					"Twister ISDN TA"पूर्ण),
	पूर्ण,
	अणु
		USB_DEVICE(0x071d, 0x1005),
		.driver_info = (अचिन्हित दीर्घ) &((काष्ठा hfcsusb_vdata)
			अणुLED_SCHEME1, अणु0x02, 0, 0x01, 0x04पूर्ण,
					"Eicon DIVA USB 4.0"पूर्ण),
	पूर्ण,
	अणु
		USB_DEVICE(0x0586, 0x0102),
		.driver_info = (अचिन्हित दीर्घ) &((काष्ठा hfcsusb_vdata)
			अणुLED_SCHEME1, अणु0x88, -64, -32, -16पूर्ण,
					"ZyXEL OMNI.NET USB II"पूर्ण),
	पूर्ण,
	अणु
		USB_DEVICE(0x1ae7, 0x0525),
		.driver_info = (अचिन्हित दीर्घ) &((काष्ठा hfcsusb_vdata)
			अणुLED_SCHEME1, अणु0x88, -64, -32, -16पूर्ण,
					"X-Tensions USB ISDN TA XC-525"पूर्ण),
	पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, hfcsusb_idtab);

#पूर्ण_अगर	/* __HFCSUSB_H__ */
