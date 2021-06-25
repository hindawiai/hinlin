<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * n_gsm.c GSM 0710 tty multiplexor
 * Copyright (c) 2009/10 Intel Corporation
 *
 *	* THIS IS A DEVELOPMENT SNAPSHOT IT IS NOT A FINAL RELEASE *
 *
 * TO DO:
 *	Mostly करोne:	ioctls क्रम setting modes/timing
 *	Partly करोne:	hooks so you can pull off frames to non tty devs
 *	Restart DLCI 0 when it बंदs ?
 *	Improve the tx engine
 *	Resolve tx side locking by adding a queue_head and routing
 *		all control traffic via it
 *	General tidy/करोcument
 *	Review the locking/move to refcounts more (mux now moved to an
 *		alloc/मुक्त model पढ़ोy)
 *	Use newest tty खोलो/बंद port helpers and install hooks
 *	What to करो about घातer functions ?
 *	Termios setting and negotiation
 *	Do we need a 'which mux are you' ioctl to correlate mux and tty sets
 *
 */

#समावेश <linux/types.h>
#समावेश <linux/major.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/tty.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/bitops.h>
#समावेश <linux/file.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <linux/समयr.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/serial.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/skbuff.h>
#समावेश <net/arp.h>
#समावेश <linux/ip.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/gsmmux.h>
#समावेश "tty.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0600);

/* Defaults: these are from the specअगरication */

#घोषणा T1	10		/* 100mS */
#घोषणा T2	34		/* 333mS */
#घोषणा N2	3		/* Retry 3 बार */

/* Use दीर्घ समयrs क्रम testing at low speed with debug on */
#अगर_घोषित DEBUG_TIMING
#घोषणा T1	100
#घोषणा T2	200
#पूर्ण_अगर

/*
 * Semi-arbitrary buffer size limits. 0710 is normally run with 32-64 byte
 * limits so this is plenty
 */
#घोषणा MAX_MRU 1500
#घोषणा MAX_MTU 1500
#घोषणा	GSM_NET_TX_TIMEOUT (HZ*10)

/*
 *	काष्ठा gsm_mux_net	-	network पूर्णांकerface
 *
 *	Created when net पूर्णांकerface is initialized.
 */
काष्ठा gsm_mux_net अणु
	काष्ठा kref ref;
	काष्ठा gsm_dlci *dlci;
पूर्ण;

/*
 *	Each block of data we have queued to go out is in the क्रमm of
 *	a gsm_msg which holds everything we need in a link layer independent
 *	क्रमmat
 */

काष्ठा gsm_msg अणु
	काष्ठा list_head list;
	u8 addr;		/* DLCI address + flags */
	u8 ctrl;		/* Control byte + flags */
	अचिन्हित पूर्णांक len;	/* Length of data block (can be zero) */
	अचिन्हित अक्षर *data;	/* Poपूर्णांकs पूर्णांकo buffer but not at the start */
	अचिन्हित अक्षर buffer[];
पूर्ण;

क्रमागत gsm_dlci_state अणु
	DLCI_CLOSED,
	DLCI_OPENING,		/* Sending SABM not seen UA */
	DLCI_OPEN,		/* SABM/UA complete */
	DLCI_CLOSING,		/* Sending DISC not seen UA/DM */
पूर्ण;

क्रमागत gsm_dlci_mode अणु
	DLCI_MODE_ABM,		/* Normal Asynchronous Balanced Mode */
	DLCI_MODE_ADM,		/* Asynchronous Disconnected Mode */
पूर्ण;

/*
 *	Each active data link has a gsm_dlci काष्ठाure associated which ties
 *	the link layer to an optional tty (अगर the tty side is खोलो). To aव्योम
 *	complनिकासy right now these are only ever मुक्तd up when the mux is
 *	shut करोwn.
 *
 *	At the moment we करोn't मुक्त DLCI objects until the mux is torn करोwn
 *	this aव्योम object lअगरe समय issues but might be worth review later.
 */

काष्ठा gsm_dlci अणु
	काष्ठा gsm_mux *gsm;
	पूर्णांक addr;
	क्रमागत gsm_dlci_state state;
	काष्ठा mutex mutex;

	/* Link layer */
	क्रमागत gsm_dlci_mode mode;
	spinlock_t lock;	/* Protects the पूर्णांकernal state */
	काष्ठा समयr_list t1;	/* Retransmit समयr क्रम SABM and UA */
	पूर्णांक retries;
	/* Uplink tty अगर active */
	काष्ठा tty_port port;	/* The tty bound to this DLCI अगर there is one */
	काष्ठा kfअगरo fअगरo;	/* Queue fअगरo क्रम the DLCI */
	पूर्णांक adaption;		/* Adaption layer in use */
	पूर्णांक prev_adaption;
	u32 modem_rx;		/* Our incoming भव modem lines */
	u32 modem_tx;		/* Our outgoing modem lines */
	bool dead;		/* Refuse re-खोलो */
	/* Flow control */
	bool throttled;		/* Private copy of throttle state */
	bool स्थिरipated;	/* Throttle status क्रम outgoing */
	/* Packetised I/O */
	काष्ठा sk_buff *skb;	/* Frame being sent */
	काष्ठा sk_buff_head skb_list;	/* Queued frames */
	/* Data handling callback */
	व्योम (*data)(काष्ठा gsm_dlci *dlci, स्थिर u8 *data, पूर्णांक len);
	व्योम (*prev_data)(काष्ठा gsm_dlci *dlci, स्थिर u8 *data, पूर्णांक len);
	काष्ठा net_device *net; /* network पूर्णांकerface, अगर created */
पूर्ण;

/* DLCI 0, 62/63 are special or reserved see gsmtty_खोलो */

#घोषणा NUM_DLCI		64

/*
 *	DLCI 0 is used to pass control blocks out of band of the data
 *	flow (and with a higher link priority). One command can be outstanding
 *	at a समय and we use this काष्ठाure to manage them. They are created
 *	and destroyed by the user context, and updated by the receive paths
 *	and समयrs
 */

काष्ठा gsm_control अणु
	u8 cmd;		/* Command we are issuing */
	u8 *data;	/* Data क्रम the command in हाल we retransmit */
	पूर्णांक len;	/* Length of block क्रम retransmission */
	पूर्णांक करोne;	/* Done flag */
	पूर्णांक error;	/* Error अगर any */
पूर्ण;

क्रमागत gsm_mux_state अणु
	GSM_SEARCH,
	GSM_START,
	GSM_ADDRESS,
	GSM_CONTROL,
	GSM_LEN,
	GSM_DATA,
	GSM_FCS,
	GSM_OVERRUN,
	GSM_LEN0,
	GSM_LEN1,
	GSM_SSOF,
पूर्ण;

/*
 *	Each GSM mux we have is represented by this काष्ठाure. If we are
 *	operating as an ldisc then we use this काष्ठाure as our ldisc
 *	state. We need to sort out lअगरeबार and locking with respect
 *	to the gsm mux array. For now we करोn't मुक्त DLCI objects that
 *	have been instantiated until the mux itself is terminated.
 *
 *	To consider further: tty खोलो versus mux shutकरोwn.
 */

काष्ठा gsm_mux अणु
	काष्ठा tty_काष्ठा *tty;		/* The tty our ldisc is bound to */
	spinlock_t lock;
	काष्ठा mutex mutex;
	अचिन्हित पूर्णांक num;
	काष्ठा kref ref;

	/* Events on the GSM channel */
	रुको_queue_head_t event;

	/* Bits क्रम GSM mode decoding */

	/* Framing Layer */
	अचिन्हित अक्षर *buf;
	क्रमागत gsm_mux_state state;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक address;
	अचिन्हित पूर्णांक count;
	bool escape;
	पूर्णांक encoding;
	u8 control;
	u8 fcs;
	u8 received_fcs;
	u8 *txframe;			/* TX framing buffer */

	/* Method क्रम the receiver side */
	व्योम (*receive)(काष्ठा gsm_mux *gsm, u8 ch);

	/* Link Layer */
	अचिन्हित पूर्णांक mru;
	अचिन्हित पूर्णांक mtu;
	पूर्णांक initiator;			/* Did we initiate connection */
	bool dead;			/* Has the mux been shut करोwn */
	काष्ठा gsm_dlci *dlci[NUM_DLCI];
	bool स्थिरipated;		/* Asked by remote to shut up */

	spinlock_t tx_lock;
	अचिन्हित पूर्णांक tx_bytes;		/* TX data outstanding */
#घोषणा TX_THRESH_HI		8192
#घोषणा TX_THRESH_LO		2048
	काष्ठा list_head tx_list;	/* Pending data packets */

	/* Control messages */
	काष्ठा समयr_list t2_समयr;	/* Retransmit समयr क्रम commands */
	पूर्णांक cretries;			/* Command retry counter */
	काष्ठा gsm_control *pending_cmd;/* Our current pending command */
	spinlock_t control_lock;	/* Protects the pending command */

	/* Configuration */
	पूर्णांक adaption;		/* 1 or 2 supported */
	u8 ftype;		/* UI or UIH */
	पूर्णांक t1, t2;		/* Timers in 1/100th of a sec */
	पूर्णांक n2;			/* Retry count */

	/* Statistics (not currently exposed) */
	अचिन्हित दीर्घ bad_fcs;
	अचिन्हित दीर्घ malक्रमmed;
	अचिन्हित दीर्घ io_error;
	अचिन्हित दीर्घ bad_size;
	अचिन्हित दीर्घ unsupported;
पूर्ण;


/*
 *	Mux objects - needed so that we can translate a tty index पूर्णांकo the
 *	relevant mux and DLCI.
 */

#घोषणा MAX_MUX		4			/* 256 minors */
अटल काष्ठा gsm_mux *gsm_mux[MAX_MUX];	/* GSM muxes */
अटल DEFINE_SPINLOCK(gsm_mux_lock);

अटल काष्ठा tty_driver *gsm_tty_driver;

/*
 *	This section of the driver logic implements the GSM encodings
 *	both the basic and the 'advanced'. Reliable transport is not
 *	supported.
 */

#घोषणा CR			0x02
#घोषणा EA			0x01
#घोषणा	PF			0x10

/* I is special: the rest are ..*/
#घोषणा RR			0x01
#घोषणा UI			0x03
#घोषणा RNR			0x05
#घोषणा REJ			0x09
#घोषणा DM			0x0F
#घोषणा SABM			0x2F
#घोषणा DISC			0x43
#घोषणा UA			0x63
#घोषणा	UIH			0xEF

/* Channel commands */
#घोषणा CMD_NSC			0x09
#घोषणा CMD_TEST		0x11
#घोषणा CMD_PSC			0x21
#घोषणा CMD_RLS			0x29
#घोषणा CMD_FCOFF		0x31
#घोषणा CMD_PN			0x41
#घोषणा CMD_RPN			0x49
#घोषणा CMD_FCON		0x51
#घोषणा CMD_CLD			0x61
#घोषणा CMD_SNC			0x69
#घोषणा CMD_MSC			0x71

/* Virtual modem bits */
#घोषणा MDM_FC			0x01
#घोषणा MDM_RTC			0x02
#घोषणा MDM_RTR			0x04
#घोषणा MDM_IC			0x20
#घोषणा MDM_DV			0x40

#घोषणा GSM0_SOF		0xF9
#घोषणा GSM1_SOF		0x7E
#घोषणा GSM1_ESCAPE		0x7D
#घोषणा GSM1_ESCAPE_BITS	0x20
#घोषणा XON			0x11
#घोषणा XOFF			0x13

अटल स्थिर काष्ठा tty_port_operations gsm_port_ops;

/*
 *	CRC table क्रम GSM 0710
 */

अटल स्थिर u8 gsm_fcs8[256] = अणु
	0x00, 0x91, 0xE3, 0x72, 0x07, 0x96, 0xE4, 0x75,
	0x0E, 0x9F, 0xED, 0x7C, 0x09, 0x98, 0xEA, 0x7B,
	0x1C, 0x8D, 0xFF, 0x6E, 0x1B, 0x8A, 0xF8, 0x69,
	0x12, 0x83, 0xF1, 0x60, 0x15, 0x84, 0xF6, 0x67,
	0x38, 0xA9, 0xDB, 0x4A, 0x3F, 0xAE, 0xDC, 0x4D,
	0x36, 0xA7, 0xD5, 0x44, 0x31, 0xA0, 0xD2, 0x43,
	0x24, 0xB5, 0xC7, 0x56, 0x23, 0xB2, 0xC0, 0x51,
	0x2A, 0xBB, 0xC9, 0x58, 0x2D, 0xBC, 0xCE, 0x5F,
	0x70, 0xE1, 0x93, 0x02, 0x77, 0xE6, 0x94, 0x05,
	0x7E, 0xEF, 0x9D, 0x0C, 0x79, 0xE8, 0x9A, 0x0B,
	0x6C, 0xFD, 0x8F, 0x1E, 0x6B, 0xFA, 0x88, 0x19,
	0x62, 0xF3, 0x81, 0x10, 0x65, 0xF4, 0x86, 0x17,
	0x48, 0xD9, 0xAB, 0x3A, 0x4F, 0xDE, 0xAC, 0x3D,
	0x46, 0xD7, 0xA5, 0x34, 0x41, 0xD0, 0xA2, 0x33,
	0x54, 0xC5, 0xB7, 0x26, 0x53, 0xC2, 0xB0, 0x21,
	0x5A, 0xCB, 0xB9, 0x28, 0x5D, 0xCC, 0xBE, 0x2F,
	0xE0, 0x71, 0x03, 0x92, 0xE7, 0x76, 0x04, 0x95,
	0xEE, 0x7F, 0x0D, 0x9C, 0xE9, 0x78, 0x0A, 0x9B,
	0xFC, 0x6D, 0x1F, 0x8E, 0xFB, 0x6A, 0x18, 0x89,
	0xF2, 0x63, 0x11, 0x80, 0xF5, 0x64, 0x16, 0x87,
	0xD8, 0x49, 0x3B, 0xAA, 0xDF, 0x4E, 0x3C, 0xAD,
	0xD6, 0x47, 0x35, 0xA4, 0xD1, 0x40, 0x32, 0xA3,
	0xC4, 0x55, 0x27, 0xB6, 0xC3, 0x52, 0x20, 0xB1,
	0xCA, 0x5B, 0x29, 0xB8, 0xCD, 0x5C, 0x2E, 0xBF,
	0x90, 0x01, 0x73, 0xE2, 0x97, 0x06, 0x74, 0xE5,
	0x9E, 0x0F, 0x7D, 0xEC, 0x99, 0x08, 0x7A, 0xEB,
	0x8C, 0x1D, 0x6F, 0xFE, 0x8B, 0x1A, 0x68, 0xF9,
	0x82, 0x13, 0x61, 0xF0, 0x85, 0x14, 0x66, 0xF7,
	0xA8, 0x39, 0x4B, 0xDA, 0xAF, 0x3E, 0x4C, 0xDD,
	0xA6, 0x37, 0x45, 0xD4, 0xA1, 0x30, 0x42, 0xD3,
	0xB4, 0x25, 0x57, 0xC6, 0xB3, 0x22, 0x50, 0xC1,
	0xBA, 0x2B, 0x59, 0xC8, 0xBD, 0x2C, 0x5E, 0xCF
पूर्ण;

#घोषणा INIT_FCS	0xFF
#घोषणा GOOD_FCS	0xCF

अटल पूर्णांक gsmld_output(काष्ठा gsm_mux *gsm, u8 *data, पूर्णांक len);

/**
 *	gsm_fcs_add	-	update FCS
 *	@fcs: Current FCS
 *	@c: Next data
 *
 *	Update the FCS to include c. Uses the algorithm in the specअगरication
 *	notes.
 */

अटल अंतरभूत u8 gsm_fcs_add(u8 fcs, u8 c)
अणु
	वापस gsm_fcs8[fcs ^ c];
पूर्ण

/**
 *	gsm_fcs_add_block	-	update FCS क्रम a block
 *	@fcs: Current FCS
 *	@c: buffer of data
 *	@len: length of buffer
 *
 *	Update the FCS to include c. Uses the algorithm in the specअगरication
 *	notes.
 */

अटल अंतरभूत u8 gsm_fcs_add_block(u8 fcs, u8 *c, पूर्णांक len)
अणु
	जबतक (len--)
		fcs = gsm_fcs8[fcs ^ *c++];
	वापस fcs;
पूर्ण

/**
 *	gsm_पढ़ो_ea		-	पढ़ो a byte पूर्णांकo an EA
 *	@val: variable holding value
 *	@c: byte going पूर्णांकo the EA
 *
 *	Processes one byte of an EA. Updates the passed variable
 *	and वापसs 1 अगर the EA is now completely पढ़ो
 */

अटल पूर्णांक gsm_पढ़ो_ea(अचिन्हित पूर्णांक *val, u8 c)
अणु
	/* Add the next 7 bits पूर्णांकo the value */
	*val <<= 7;
	*val |= c >> 1;
	/* Was this the last byte of the EA 1 = yes*/
	वापस c & EA;
पूर्ण

/**
 *	gsm_encode_modem	-	encode modem data bits
 *	@dlci: DLCI to encode from
 *
 *	Returns the correct GSM encoded modem status bits (6 bit field) क्रम
 *	the current status of the DLCI and attached tty object
 */

अटल u8 gsm_encode_modem(स्थिर काष्ठा gsm_dlci *dlci)
अणु
	u8 modembits = 0;
	/* FC is true flow control not modem bits */
	अगर (dlci->throttled)
		modembits |= MDM_FC;
	अगर (dlci->modem_tx & TIOCM_DTR)
		modembits |= MDM_RTC;
	अगर (dlci->modem_tx & TIOCM_RTS)
		modembits |= MDM_RTR;
	अगर (dlci->modem_tx & TIOCM_RI)
		modembits |= MDM_IC;
	अगर (dlci->modem_tx & TIOCM_CD)
		modembits |= MDM_DV;
	वापस modembits;
पूर्ण

/**
 *	gsm_prपूर्णांक_packet	-	display a frame क्रम debug
 *	@hdr: header to prपूर्णांक beक्रमe decode
 *	@addr: address EA from the frame
 *	@cr: C/R bit from the frame
 *	@control: control including PF bit
 *	@data: following data bytes
 *	@dlen: length of data
 *
 *	Displays a packet in human पढ़ोable क्रमmat क्रम debugging purposes. The
 *	style is based on amateur radio LAP-B dump display.
 */

अटल व्योम gsm_prपूर्णांक_packet(स्थिर अक्षर *hdr, पूर्णांक addr, पूर्णांक cr,
					u8 control, स्थिर u8 *data, पूर्णांक dlen)
अणु
	अगर (!(debug & 1))
		वापस;

	pr_info("%s %d) %c: ", hdr, addr, "RC"[cr]);

	चयन (control & ~PF) अणु
	हाल SABM:
		pr_cont("SABM");
		अवरोध;
	हाल UA:
		pr_cont("UA");
		अवरोध;
	हाल DISC:
		pr_cont("DISC");
		अवरोध;
	हाल DM:
		pr_cont("DM");
		अवरोध;
	हाल UI:
		pr_cont("UI");
		अवरोध;
	हाल UIH:
		pr_cont("UIH");
		अवरोध;
	शेष:
		अगर (!(control & 0x01)) अणु
			pr_cont("I N(S)%d N(R)%d",
				(control & 0x0E) >> 1, (control & 0xE0) >> 5);
		पूर्ण अन्यथा चयन (control & 0x0F) अणु
			हाल RR:
				pr_cont("RR(%d)", (control & 0xE0) >> 5);
				अवरोध;
			हाल RNR:
				pr_cont("RNR(%d)", (control & 0xE0) >> 5);
				अवरोध;
			हाल REJ:
				pr_cont("REJ(%d)", (control & 0xE0) >> 5);
				अवरोध;
			शेष:
				pr_cont("[%02X]", control);
		पूर्ण
	पूर्ण

	अगर (control & PF)
		pr_cont("(P)");
	अन्यथा
		pr_cont("(F)");

	prपूर्णांक_hex_dump_bytes("", DUMP_PREFIX_NONE, data, dlen);
पूर्ण


/*
 *	Link level transmission side
 */

/**
 *	gsm_stuff_packet	-	bytestuff a packet
 *	@input: input buffer
 *	@output: output buffer
 *	@len: length of input
 *
 *	Expand a buffer by bytestuffing it. The worst हाल size change
 *	is करोubling and the caller is responsible क्रम handing out
 *	suitable sized buffers.
 */

अटल पूर्णांक gsm_stuff_frame(स्थिर u8 *input, u8 *output, पूर्णांक len)
अणु
	पूर्णांक olen = 0;
	जबतक (len--) अणु
		अगर (*input == GSM1_SOF || *input == GSM1_ESCAPE
		    || *input == XON || *input == XOFF) अणु
			*output++ = GSM1_ESCAPE;
			*output++ = *input++ ^ GSM1_ESCAPE_BITS;
			olen++;
		पूर्ण अन्यथा
			*output++ = *input++;
		olen++;
	पूर्ण
	वापस olen;
पूर्ण

/**
 *	gsm_send	-	send a control frame
 *	@gsm: our GSM mux
 *	@addr: address क्रम control frame
 *	@cr: command/response bit
 *	@control:  control byte including PF bit
 *
 *	Format up and transmit a control frame. These करो not go via the
 *	queueing logic as they should be transmitted ahead of data when
 *	they are needed.
 *
 *	FIXME: Lock versus data TX path
 */

अटल व्योम gsm_send(काष्ठा gsm_mux *gsm, पूर्णांक addr, पूर्णांक cr, पूर्णांक control)
अणु
	पूर्णांक len;
	u8 cbuf[10];
	u8 ibuf[3];

	चयन (gsm->encoding) अणु
	हाल 0:
		cbuf[0] = GSM0_SOF;
		cbuf[1] = (addr << 2) | (cr << 1) | EA;
		cbuf[2] = control;
		cbuf[3] = EA;	/* Length of data = 0 */
		cbuf[4] = 0xFF - gsm_fcs_add_block(INIT_FCS, cbuf + 1, 3);
		cbuf[5] = GSM0_SOF;
		len = 6;
		अवरोध;
	हाल 1:
	हाल 2:
		/* Control frame + packing (but not frame stuffing) in mode 1 */
		ibuf[0] = (addr << 2) | (cr << 1) | EA;
		ibuf[1] = control;
		ibuf[2] = 0xFF - gsm_fcs_add_block(INIT_FCS, ibuf, 2);
		/* Stuffing may द्विगुन the size worst हाल */
		len = gsm_stuff_frame(ibuf, cbuf + 1, 3);
		/* Now add the SOF markers */
		cbuf[0] = GSM1_SOF;
		cbuf[len + 1] = GSM1_SOF;
		/* FIXME: we can omit the lead one in many हालs */
		len += 2;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस;
	पूर्ण
	gsmld_output(gsm, cbuf, len);
	gsm_prपूर्णांक_packet("-->", addr, cr, control, शून्य, 0);
पूर्ण

/**
 *	gsm_response	-	send a control response
 *	@gsm: our GSM mux
 *	@addr: address क्रम control frame
 *	@control:  control byte including PF bit
 *
 *	Format up and transmit a link level response frame.
 */

अटल अंतरभूत व्योम gsm_response(काष्ठा gsm_mux *gsm, पूर्णांक addr, पूर्णांक control)
अणु
	gsm_send(gsm, addr, 0, control);
पूर्ण

/**
 *	gsm_command	-	send a control command
 *	@gsm: our GSM mux
 *	@addr: address क्रम control frame
 *	@control:  control byte including PF bit
 *
 *	Format up and transmit a link level command frame.
 */

अटल अंतरभूत व्योम gsm_command(काष्ठा gsm_mux *gsm, पूर्णांक addr, पूर्णांक control)
अणु
	gsm_send(gsm, addr, 1, control);
पूर्ण

/* Data transmission */

#घोषणा HDR_LEN		6	/* ADDR CTRL [LEN.2] DATA FCS */

/**
 *	gsm_data_alloc		-	allocate data frame
 *	@gsm: GSM mux
 *	@addr: DLCI address
 *	@len: length excluding header and FCS
 *	@ctrl: control byte
 *
 *	Allocate a new data buffer क्रम sending frames with data. Space is left
 *	at the front क्रम header bytes but that is treated as an implementation
 *	detail and not क्रम the high level code to use
 */

अटल काष्ठा gsm_msg *gsm_data_alloc(काष्ठा gsm_mux *gsm, u8 addr, पूर्णांक len,
								u8 ctrl)
अणु
	काष्ठा gsm_msg *m = kदो_स्मृति(माप(काष्ठा gsm_msg) + len + HDR_LEN,
								GFP_ATOMIC);
	अगर (m == शून्य)
		वापस शून्य;
	m->data = m->buffer + HDR_LEN - 1;	/* Allow क्रम FCS */
	m->len = len;
	m->addr = addr;
	m->ctrl = ctrl;
	INIT_LIST_HEAD(&m->list);
	वापस m;
पूर्ण

/**
 *	gsm_data_kick		-	poke the queue
 *	@gsm: GSM Mux
 *	@dlci: DLCI sending the data
 *
 *	The tty device has called us to indicate that room has appeared in
 *	the transmit queue. Ram more data पूर्णांकo the pipe अगर we have any
 *	If we have been flow-stopped by a CMD_FCOFF, then we can only
 *	send messages on DLCI0 until CMD_FCON
 *
 *	FIXME: lock against link layer control transmissions
 */

अटल व्योम gsm_data_kick(काष्ठा gsm_mux *gsm, काष्ठा gsm_dlci *dlci)
अणु
	काष्ठा gsm_msg *msg, *nmsg;
	पूर्णांक len;

	list_क्रम_each_entry_safe(msg, nmsg, &gsm->tx_list, list) अणु
		अगर (gsm->स्थिरipated && msg->addr)
			जारी;
		अगर (gsm->encoding != 0) अणु
			gsm->txframe[0] = GSM1_SOF;
			len = gsm_stuff_frame(msg->data,
						gsm->txframe + 1, msg->len);
			gsm->txframe[len + 1] = GSM1_SOF;
			len += 2;
		पूर्ण अन्यथा अणु
			gsm->txframe[0] = GSM0_SOF;
			स_नकल(gsm->txframe + 1 , msg->data, msg->len);
			gsm->txframe[msg->len + 1] = GSM0_SOF;
			len = msg->len + 2;
		पूर्ण

		अगर (debug & 4)
			prपूर्णांक_hex_dump_bytes("gsm_data_kick: ",
					     DUMP_PREFIX_OFFSET,
					     gsm->txframe, len);
		अगर (gsmld_output(gsm, gsm->txframe, len) < 0)
			अवरोध;
		/* FIXME: Can eliminate one SOF in many more हालs */
		gsm->tx_bytes -= msg->len;

		list_del(&msg->list);
		kमुक्त(msg);

		अगर (dlci) अणु
			tty_port_tty_wakeup(&dlci->port);
		पूर्ण अन्यथा अणु
			पूर्णांक i = 0;

			क्रम (i = 0; i < NUM_DLCI; i++)
				अगर (gsm->dlci[i])
					tty_port_tty_wakeup(&gsm->dlci[i]->port);
		पूर्ण
	पूर्ण
पूर्ण

/**
 *	__gsm_data_queue		-	queue a UI or UIH frame
 *	@dlci: DLCI sending the data
 *	@msg: message queued
 *
 *	Add data to the transmit queue and try and get stuff moving
 *	out of the mux tty अगर not alपढ़ोy करोing so. The Caller must hold
 *	the gsm tx lock.
 */

अटल व्योम __gsm_data_queue(काष्ठा gsm_dlci *dlci, काष्ठा gsm_msg *msg)
अणु
	काष्ठा gsm_mux *gsm = dlci->gsm;
	u8 *dp = msg->data;
	u8 *fcs = dp + msg->len;

	/* Fill in the header */
	अगर (gsm->encoding == 0) अणु
		अगर (msg->len < 128)
			*--dp = (msg->len << 1) | EA;
		अन्यथा अणु
			*--dp = (msg->len >> 7);	/* bits 7 - 15 */
			*--dp = (msg->len & 127) << 1;	/* bits 0 - 6 */
		पूर्ण
	पूर्ण

	*--dp = msg->ctrl;
	अगर (gsm->initiator)
		*--dp = (msg->addr << 2) | 2 | EA;
	अन्यथा
		*--dp = (msg->addr << 2) | EA;
	*fcs = gsm_fcs_add_block(INIT_FCS, dp , msg->data - dp);
	/* Ugly protocol layering violation */
	अगर (msg->ctrl == UI || msg->ctrl == (UI|PF))
		*fcs = gsm_fcs_add_block(*fcs, msg->data, msg->len);
	*fcs = 0xFF - *fcs;

	gsm_prपूर्णांक_packet("Q> ", msg->addr, gsm->initiator, msg->ctrl,
							msg->data, msg->len);

	/* Move the header back and adjust the length, also allow क्रम the FCS
	   now tacked on the end */
	msg->len += (msg->data - dp) + 1;
	msg->data = dp;

	/* Add to the actual output queue */
	list_add_tail(&msg->list, &gsm->tx_list);
	gsm->tx_bytes += msg->len;
	gsm_data_kick(gsm, dlci);
पूर्ण

/**
 *	gsm_data_queue		-	queue a UI or UIH frame
 *	@dlci: DLCI sending the data
 *	@msg: message queued
 *
 *	Add data to the transmit queue and try and get stuff moving
 *	out of the mux tty अगर not alपढ़ोy करोing so. Take the
 *	the gsm tx lock and dlci lock.
 */

अटल व्योम gsm_data_queue(काष्ठा gsm_dlci *dlci, काष्ठा gsm_msg *msg)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&dlci->gsm->tx_lock, flags);
	__gsm_data_queue(dlci, msg);
	spin_unlock_irqrestore(&dlci->gsm->tx_lock, flags);
पूर्ण

/**
 *	gsm_dlci_data_output	-	try and push data out of a DLCI
 *	@gsm: mux
 *	@dlci: the DLCI to pull data from
 *
 *	Pull data from a DLCI and send it पूर्णांकo the transmit queue अगर there
 *	is data. Keep to the MRU of the mux. This path handles the usual tty
 *	पूर्णांकerface which is a byte stream with optional modem data.
 *
 *	Caller must hold the tx_lock of the mux.
 */

अटल पूर्णांक gsm_dlci_data_output(काष्ठा gsm_mux *gsm, काष्ठा gsm_dlci *dlci)
अणु
	काष्ठा gsm_msg *msg;
	u8 *dp;
	पूर्णांक len, total_size, size;
	पूर्णांक h = dlci->adaption - 1;

	total_size = 0;
	जबतक (1) अणु
		len = kfअगरo_len(&dlci->fअगरo);
		अगर (len == 0)
			वापस total_size;

		/* MTU/MRU count only the data bits */
		अगर (len > gsm->mtu)
			len = gsm->mtu;

		size = len + h;

		msg = gsm_data_alloc(gsm, dlci->addr, size, gsm->ftype);
		/* FIXME: need a समयr or something to kick this so it can't
		   get stuck with no work outstanding and no buffer मुक्त */
		अगर (msg == शून्य)
			वापस -ENOMEM;
		dp = msg->data;
		चयन (dlci->adaption) अणु
		हाल 1:	/* Unकाष्ठाured */
			अवरोध;
		हाल 2:	/* Unकाष्ठाed with modem bits.
		Always one byte as we never send अंतरभूत अवरोध data */
			*dp++ = gsm_encode_modem(dlci);
			अवरोध;
		पूर्ण
		WARN_ON(kfअगरo_out_locked(&dlci->fअगरo, dp , len, &dlci->lock) != len);
		__gsm_data_queue(dlci, msg);
		total_size += size;
	पूर्ण
	/* Bytes of data we used up */
	वापस total_size;
पूर्ण

/**
 *	gsm_dlci_data_output_framed  -	try and push data out of a DLCI
 *	@gsm: mux
 *	@dlci: the DLCI to pull data from
 *
 *	Pull data from a DLCI and send it पूर्णांकo the transmit queue अगर there
 *	is data. Keep to the MRU of the mux. This path handles framed data
 *	queued as skbuffs to the DLCI.
 *
 *	Caller must hold the tx_lock of the mux.
 */

अटल पूर्णांक gsm_dlci_data_output_framed(काष्ठा gsm_mux *gsm,
						काष्ठा gsm_dlci *dlci)
अणु
	काष्ठा gsm_msg *msg;
	u8 *dp;
	पूर्णांक len, size;
	पूर्णांक last = 0, first = 0;
	पूर्णांक overhead = 0;

	/* One byte per frame is used क्रम B/F flags */
	अगर (dlci->adaption == 4)
		overhead = 1;

	/* dlci->skb is locked by tx_lock */
	अगर (dlci->skb == शून्य) अणु
		dlci->skb = skb_dequeue_tail(&dlci->skb_list);
		अगर (dlci->skb == शून्य)
			वापस 0;
		first = 1;
	पूर्ण
	len = dlci->skb->len + overhead;

	/* MTU/MRU count only the data bits */
	अगर (len > gsm->mtu) अणु
		अगर (dlci->adaption == 3) अणु
			/* Over दीर्घ frame, bin it */
			dev_kमुक्त_skb_any(dlci->skb);
			dlci->skb = शून्य;
			वापस 0;
		पूर्ण
		len = gsm->mtu;
	पूर्ण अन्यथा
		last = 1;

	size = len + overhead;
	msg = gsm_data_alloc(gsm, dlci->addr, size, gsm->ftype);

	/* FIXME: need a समयr or something to kick this so it can't
	   get stuck with no work outstanding and no buffer मुक्त */
	अगर (msg == शून्य) अणु
		skb_queue_tail(&dlci->skb_list, dlci->skb);
		dlci->skb = शून्य;
		वापस -ENOMEM;
	पूर्ण
	dp = msg->data;

	अगर (dlci->adaption == 4) अणु /* Interruptible framed (Packetised Data) */
		/* Flag byte to carry the start/end info */
		*dp++ = last << 7 | first << 6 | 1;	/* EA */
		len--;
	पूर्ण
	स_नकल(dp, dlci->skb->data, len);
	skb_pull(dlci->skb, len);
	__gsm_data_queue(dlci, msg);
	अगर (last) अणु
		dev_kमुक्त_skb_any(dlci->skb);
		dlci->skb = शून्य;
	पूर्ण
	वापस size;
पूर्ण

/**
 *	gsm_dlci_data_sweep		-	look क्रम data to send
 *	@gsm: the GSM mux
 *
 *	Sweep the GSM mux channels in priority order looking क्रम ones with
 *	data to send. We could करो with optimising this scan a bit. We aim
 *	to fill the queue totally or up to TX_THRESH_HI bytes. Once we hit
 *	TX_THRESH_LO we get called again
 *
 *	FIXME: We should round robin between groups and in theory you can
 *	renegotiate DLCI priorities with optional stuff. Needs optimising.
 */

अटल व्योम gsm_dlci_data_sweep(काष्ठा gsm_mux *gsm)
अणु
	पूर्णांक len;
	/* Priority ordering: We should करो priority with RR of the groups */
	पूर्णांक i = 1;

	जबतक (i < NUM_DLCI) अणु
		काष्ठा gsm_dlci *dlci;

		अगर (gsm->tx_bytes > TX_THRESH_HI)
			अवरोध;
		dlci = gsm->dlci[i];
		अगर (dlci == शून्य || dlci->स्थिरipated) अणु
			i++;
			जारी;
		पूर्ण
		अगर (dlci->adaption < 3 && !dlci->net)
			len = gsm_dlci_data_output(gsm, dlci);
		अन्यथा
			len = gsm_dlci_data_output_framed(gsm, dlci);
		अगर (len < 0)
			अवरोध;
		/* DLCI empty - try the next */
		अगर (len == 0)
			i++;
	पूर्ण
पूर्ण

/**
 *	gsm_dlci_data_kick	-	transmit अगर possible
 *	@dlci: DLCI to kick
 *
 *	Transmit data from this DLCI अगर the queue is empty. We can't rely on
 *	a tty wakeup except when we filled the pipe so we need to fire off
 *	new data ourselves in other हालs.
 */

अटल व्योम gsm_dlci_data_kick(काष्ठा gsm_dlci *dlci)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक sweep;

	अगर (dlci->स्थिरipated)
		वापस;

	spin_lock_irqsave(&dlci->gsm->tx_lock, flags);
	/* If we have nothing running then we need to fire up */
	sweep = (dlci->gsm->tx_bytes < TX_THRESH_LO);
	अगर (dlci->gsm->tx_bytes == 0) अणु
		अगर (dlci->net)
			gsm_dlci_data_output_framed(dlci->gsm, dlci);
		अन्यथा
			gsm_dlci_data_output(dlci->gsm, dlci);
	पूर्ण
	अगर (sweep)
		gsm_dlci_data_sweep(dlci->gsm);
	spin_unlock_irqrestore(&dlci->gsm->tx_lock, flags);
पूर्ण

/*
 *	Control message processing
 */


/**
 *	gsm_control_reply	-	send a response frame to a control
 *	@gsm: gsm channel
 *	@cmd: the command to use
 *	@data: data to follow encoded info
 *	@dlen: length of data
 *
 *	Encode up and queue a UI/UIH frame containing our response.
 */

अटल व्योम gsm_control_reply(काष्ठा gsm_mux *gsm, पूर्णांक cmd, स्थिर u8 *data,
					पूर्णांक dlen)
अणु
	काष्ठा gsm_msg *msg;
	msg = gsm_data_alloc(gsm, 0, dlen + 2, gsm->ftype);
	अगर (msg == शून्य)
		वापस;
	msg->data[0] = (cmd & 0xFE) << 1 | EA;	/* Clear C/R */
	msg->data[1] = (dlen << 1) | EA;
	स_नकल(msg->data + 2, data, dlen);
	gsm_data_queue(gsm->dlci[0], msg);
पूर्ण

/**
 *	gsm_process_modem	-	process received modem status
 *	@tty: भव tty bound to the DLCI
 *	@dlci: DLCI to affect
 *	@modem: modem bits (full EA)
 *	@clen: command length
 *
 *	Used when a modem control message or line state अंतरभूत in adaption
 *	layer 2 is processed. Sort out the local modem state and throttles
 */

अटल व्योम gsm_process_modem(काष्ठा tty_काष्ठा *tty, काष्ठा gsm_dlci *dlci,
							u32 modem, पूर्णांक clen)
अणु
	पूर्णांक  mlines = 0;
	u8 brk = 0;
	पूर्णांक fc;

	/* The modem status command can either contain one octet (v.24 संकेतs)
	   or two octets (v.24 संकेतs + अवरोध संकेतs). The length field will
	   either be 2 or 3 respectively. This is specअगरied in section
	   5.4.6.3.7 of the  27.010 mux spec. */

	अगर (clen == 2)
		modem = modem & 0x7f;
	अन्यथा अणु
		brk = modem & 0x7f;
		modem = (modem >> 7) & 0x7f;
	पूर्ण

	/* Flow control/पढ़ोy to communicate */
	fc = (modem & MDM_FC) || !(modem & MDM_RTR);
	अगर (fc && !dlci->स्थिरipated) अणु
		/* Need to throttle our output on this device */
		dlci->स्थिरipated = true;
	पूर्ण अन्यथा अगर (!fc && dlci->स्थिरipated) अणु
		dlci->स्थिरipated = false;
		gsm_dlci_data_kick(dlci);
	पूर्ण

	/* Map modem bits */
	अगर (modem & MDM_RTC)
		mlines |= TIOCM_DSR | TIOCM_DTR;
	अगर (modem & MDM_RTR)
		mlines |= TIOCM_RTS | TIOCM_CTS;
	अगर (modem & MDM_IC)
		mlines |= TIOCM_RI;
	अगर (modem & MDM_DV)
		mlines |= TIOCM_CD;

	/* Carrier drop -> hangup */
	अगर (tty) अणु
		अगर ((mlines & TIOCM_CD) == 0 && (dlci->modem_rx & TIOCM_CD))
			अगर (!C_CLOCAL(tty))
				tty_hangup(tty);
	पूर्ण
	अगर (brk & 0x01)
		tty_insert_flip_अक्षर(&dlci->port, 0, TTY_BREAK);
	dlci->modem_rx = mlines;
पूर्ण

/**
 *	gsm_control_modem	-	modem status received
 *	@gsm: GSM channel
 *	@data: data following command
 *	@clen: command length
 *
 *	We have received a modem status control message. This is used by
 *	the GSM mux protocol to pass भव modem line status and optionally
 *	to indicate अवरोध संकेतs. Unpack it, convert to Linux representation
 *	and अगर need be stuff a अवरोध message करोwn the tty.
 */

अटल व्योम gsm_control_modem(काष्ठा gsm_mux *gsm, स्थिर u8 *data, पूर्णांक clen)
अणु
	अचिन्हित पूर्णांक addr = 0;
	अचिन्हित पूर्णांक modem = 0;
	अचिन्हित पूर्णांक brk = 0;
	काष्ठा gsm_dlci *dlci;
	पूर्णांक len = clen;
	स्थिर u8 *dp = data;
	काष्ठा tty_काष्ठा *tty;

	जबतक (gsm_पढ़ो_ea(&addr, *dp++) == 0) अणु
		len--;
		अगर (len == 0)
			वापस;
	पूर्ण
	/* Must be at least one byte following the EA */
	len--;
	अगर (len <= 0)
		वापस;

	addr >>= 1;
	/* Closed port, or invalid ? */
	अगर (addr == 0 || addr >= NUM_DLCI || gsm->dlci[addr] == शून्य)
		वापस;
	dlci = gsm->dlci[addr];

	जबतक (gsm_पढ़ो_ea(&modem, *dp++) == 0) अणु
		len--;
		अगर (len == 0)
			वापस;
	पूर्ण
	len--;
	अगर (len > 0) अणु
		जबतक (gsm_पढ़ो_ea(&brk, *dp++) == 0) अणु
			len--;
			अगर (len == 0)
				वापस;
		पूर्ण
		modem <<= 7;
		modem |= (brk & 0x7f);
	पूर्ण
	tty = tty_port_tty_get(&dlci->port);
	gsm_process_modem(tty, dlci, modem, clen);
	अगर (tty) अणु
		tty_wakeup(tty);
		tty_kref_put(tty);
	पूर्ण
	gsm_control_reply(gsm, CMD_MSC, data, clen);
पूर्ण

/**
 *	gsm_control_rls		-	remote line status
 *	@gsm: GSM channel
 *	@data: data bytes
 *	@clen: data length
 *
 *	The modem sends us a two byte message on the control channel whenever
 *	it wishes to send us an error state from the भव link. Stuff
 *	this पूर्णांकo the uplink tty अगर present
 */

अटल व्योम gsm_control_rls(काष्ठा gsm_mux *gsm, स्थिर u8 *data, पूर्णांक clen)
अणु
	काष्ठा tty_port *port;
	अचिन्हित पूर्णांक addr = 0;
	u8 bits;
	पूर्णांक len = clen;
	स्थिर u8 *dp = data;

	जबतक (gsm_पढ़ो_ea(&addr, *dp++) == 0) अणु
		len--;
		अगर (len == 0)
			वापस;
	पूर्ण
	/* Must be at least one byte following ea */
	len--;
	अगर (len <= 0)
		वापस;
	addr >>= 1;
	/* Closed port, or invalid ? */
	अगर (addr == 0 || addr >= NUM_DLCI || gsm->dlci[addr] == शून्य)
		वापस;
	/* No error ? */
	bits = *dp;
	अगर ((bits & 1) == 0)
		वापस;

	port = &gsm->dlci[addr]->port;

	अगर (bits & 2)
		tty_insert_flip_अक्षर(port, 0, TTY_OVERRUN);
	अगर (bits & 4)
		tty_insert_flip_अक्षर(port, 0, TTY_PARITY);
	अगर (bits & 8)
		tty_insert_flip_अक्षर(port, 0, TTY_FRAME);

	tty_flip_buffer_push(port);

	gsm_control_reply(gsm, CMD_RLS, data, clen);
पूर्ण

अटल व्योम gsm_dlci_begin_बंद(काष्ठा gsm_dlci *dlci);

/**
 *	gsm_control_message	-	DLCI 0 control processing
 *	@gsm: our GSM mux
 *	@command:  the command EA
 *	@data: data beyond the command/length EAs
 *	@clen: length
 *
 *	Input processor क्रम control messages from the other end of the link.
 *	Processes the incoming request and queues a response frame or an
 *	NSC response अगर not supported
 */

अटल व्योम gsm_control_message(काष्ठा gsm_mux *gsm, अचिन्हित पूर्णांक command,
						स्थिर u8 *data, पूर्णांक clen)
अणु
	u8 buf[1];
	अचिन्हित दीर्घ flags;

	चयन (command) अणु
	हाल CMD_CLD: अणु
		काष्ठा gsm_dlci *dlci = gsm->dlci[0];
		/* Modem wishes to बंद करोwn */
		अगर (dlci) अणु
			dlci->dead = true;
			gsm->dead = true;
			gsm_dlci_begin_बंद(dlci);
		पूर्ण
		पूर्ण
		अवरोध;
	हाल CMD_TEST:
		/* Modem wishes to test, reply with the data */
		gsm_control_reply(gsm, CMD_TEST, data, clen);
		अवरोध;
	हाल CMD_FCON:
		/* Modem can accept data again */
		gsm->स्थिरipated = false;
		gsm_control_reply(gsm, CMD_FCON, शून्य, 0);
		/* Kick the link in हाल it is idling */
		spin_lock_irqsave(&gsm->tx_lock, flags);
		gsm_data_kick(gsm, शून्य);
		spin_unlock_irqrestore(&gsm->tx_lock, flags);
		अवरोध;
	हाल CMD_FCOFF:
		/* Modem wants us to STFU */
		gsm->स्थिरipated = true;
		gsm_control_reply(gsm, CMD_FCOFF, शून्य, 0);
		अवरोध;
	हाल CMD_MSC:
		/* Out of band modem line change indicator क्रम a DLCI */
		gsm_control_modem(gsm, data, clen);
		अवरोध;
	हाल CMD_RLS:
		/* Out of band error reception क्रम a DLCI */
		gsm_control_rls(gsm, data, clen);
		अवरोध;
	हाल CMD_PSC:
		/* Modem wishes to enter घातer saving state */
		gsm_control_reply(gsm, CMD_PSC, शून्य, 0);
		अवरोध;
		/* Optional unsupported commands */
	हाल CMD_PN:	/* Parameter negotiation */
	हाल CMD_RPN:	/* Remote port negotiation */
	हाल CMD_SNC:	/* Service negotiation command */
	शेष:
		/* Reply to bad commands with an NSC */
		buf[0] = command;
		gsm_control_reply(gsm, CMD_NSC, buf, 1);
		अवरोध;
	पूर्ण
पूर्ण

/**
 *	gsm_control_response	-	process a response to our control
 *	@gsm: our GSM mux
 *	@command: the command (response) EA
 *	@data: data beyond the command/length EA
 *	@clen: length
 *
 *	Process a response to an outstanding command. We only allow a single
 *	control message in flight so this is fairly easy. All the clean up
 *	is करोne by the caller, we just update the fields, flag it as करोne
 *	and वापस
 */

अटल व्योम gsm_control_response(काष्ठा gsm_mux *gsm, अचिन्हित पूर्णांक command,
						स्थिर u8 *data, पूर्णांक clen)
अणु
	काष्ठा gsm_control *ctrl;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gsm->control_lock, flags);

	ctrl = gsm->pending_cmd;
	/* Does the reply match our command */
	command |= 1;
	अगर (ctrl != शून्य && (command == ctrl->cmd || command == CMD_NSC)) अणु
		/* Our command was replied to, समाप्त the retry समयr */
		del_समयr(&gsm->t2_समयr);
		gsm->pending_cmd = शून्य;
		/* Rejected by the other end */
		अगर (command == CMD_NSC)
			ctrl->error = -EOPNOTSUPP;
		ctrl->करोne = 1;
		wake_up(&gsm->event);
	पूर्ण
	spin_unlock_irqrestore(&gsm->control_lock, flags);
पूर्ण

/**
 *	gsm_control_transmit	-	send control packet
 *	@gsm: gsm mux
 *	@ctrl: frame to send
 *
 *	Send out a pending control command (called under control lock)
 */

अटल व्योम gsm_control_transmit(काष्ठा gsm_mux *gsm, काष्ठा gsm_control *ctrl)
अणु
	काष्ठा gsm_msg *msg = gsm_data_alloc(gsm, 0, ctrl->len + 1, gsm->ftype);
	अगर (msg == शून्य)
		वापस;
	msg->data[0] = (ctrl->cmd << 1) | 2 | EA;	/* command */
	स_नकल(msg->data + 1, ctrl->data, ctrl->len);
	gsm_data_queue(gsm->dlci[0], msg);
पूर्ण

/**
 *	gsm_control_retransmit	-	retransmit a control frame
 *	@t: समयr contained in our gsm object
 *
 *	Called off the T2 समयr expiry in order to retransmit control frames
 *	that have been lost in the प्रणाली somewhere. The control_lock protects
 *	us from colliding with another sender or a receive completion event.
 *	In that situation the समयr may still occur in a small winकरोw but
 *	gsm->pending_cmd will be शून्य and we just let the समयr expire.
 */

अटल व्योम gsm_control_retransmit(काष्ठा समयr_list *t)
अणु
	काष्ठा gsm_mux *gsm = from_समयr(gsm, t, t2_समयr);
	काष्ठा gsm_control *ctrl;
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&gsm->control_lock, flags);
	ctrl = gsm->pending_cmd;
	अगर (ctrl) अणु
		gsm->cretries--;
		अगर (gsm->cretries == 0) अणु
			gsm->pending_cmd = शून्य;
			ctrl->error = -ETIMEDOUT;
			ctrl->करोne = 1;
			spin_unlock_irqrestore(&gsm->control_lock, flags);
			wake_up(&gsm->event);
			वापस;
		पूर्ण
		gsm_control_transmit(gsm, ctrl);
		mod_समयr(&gsm->t2_समयr, jअगरfies + gsm->t2 * HZ / 100);
	पूर्ण
	spin_unlock_irqrestore(&gsm->control_lock, flags);
पूर्ण

/**
 *	gsm_control_send	-	send a control frame on DLCI 0
 *	@gsm: the GSM channel
 *	@command: command  to send including CR bit
 *	@data: bytes of data (must be kदो_स्मृतिed)
 *	@clen: length of the block to send
 *
 *	Queue and dispatch a control command. Only one command can be
 *	active at a समय. In theory more can be outstanding but the matching
 *	माला_लो really complicated so क्रम now stick to one outstanding.
 */

अटल काष्ठा gsm_control *gsm_control_send(काष्ठा gsm_mux *gsm,
		अचिन्हित पूर्णांक command, u8 *data, पूर्णांक clen)
अणु
	काष्ठा gsm_control *ctrl = kzalloc(माप(काष्ठा gsm_control),
						GFP_KERNEL);
	अचिन्हित दीर्घ flags;
	अगर (ctrl == शून्य)
		वापस शून्य;
retry:
	रुको_event(gsm->event, gsm->pending_cmd == शून्य);
	spin_lock_irqsave(&gsm->control_lock, flags);
	अगर (gsm->pending_cmd != शून्य) अणु
		spin_unlock_irqrestore(&gsm->control_lock, flags);
		जाओ retry;
	पूर्ण
	ctrl->cmd = command;
	ctrl->data = data;
	ctrl->len = clen;
	gsm->pending_cmd = ctrl;

	/* If DLCI0 is in ADM mode skip retries, it won't respond */
	अगर (gsm->dlci[0]->mode == DLCI_MODE_ADM)
		gsm->cretries = 1;
	अन्यथा
		gsm->cretries = gsm->n2;

	mod_समयr(&gsm->t2_समयr, jअगरfies + gsm->t2 * HZ / 100);
	gsm_control_transmit(gsm, ctrl);
	spin_unlock_irqrestore(&gsm->control_lock, flags);
	वापस ctrl;
पूर्ण

/**
 *	gsm_control_रुको	-	रुको क्रम a control to finish
 *	@gsm: GSM mux
 *	@control: control we are रुकोing on
 *
 *	Waits क्रम the control to complete or समय out. Frees any used
 *	resources and वापसs 0 क्रम success, or an error अगर the remote
 *	rejected or ignored the request.
 */

अटल पूर्णांक gsm_control_रुको(काष्ठा gsm_mux *gsm, काष्ठा gsm_control *control)
अणु
	पूर्णांक err;
	रुको_event(gsm->event, control->करोne == 1);
	err = control->error;
	kमुक्त(control);
	वापस err;
पूर्ण


/*
 *	DLCI level handling: Needs krefs
 */

/*
 *	State transitions and समयrs
 */

/**
 *	gsm_dlci_बंद		-	a DLCI has बंदd
 *	@dlci: DLCI that बंदd
 *
 *	Perक्रमm processing when moving a DLCI पूर्णांकo बंदd state. If there
 *	is an attached tty this is hung up
 */

अटल व्योम gsm_dlci_बंद(काष्ठा gsm_dlci *dlci)
अणु
	del_समयr(&dlci->t1);
	अगर (debug & 8)
		pr_debug("DLCI %d goes closed.\n", dlci->addr);
	dlci->state = DLCI_CLOSED;
	अगर (dlci->addr != 0) अणु
		tty_port_tty_hangup(&dlci->port, false);
		kfअगरo_reset(&dlci->fअगरo);
	पूर्ण अन्यथा
		dlci->gsm->dead = true;
	wake_up(&dlci->gsm->event);
	/* A DLCI 0 बंद is a MUX termination so we need to kick that
	   back to userspace somehow */
पूर्ण

/**
 *	gsm_dlci_खोलो		-	a DLCI has खोलोed
 *	@dlci: DLCI that खोलोed
 *
 *	Perक्रमm processing when moving a DLCI पूर्णांकo खोलो state.
 */

अटल व्योम gsm_dlci_खोलो(काष्ठा gsm_dlci *dlci)
अणु
	/* Note that SABM UA .. SABM UA first UA lost can mean that we go
	   खोलो -> खोलो */
	del_समयr(&dlci->t1);
	/* This will let a tty खोलो जारी */
	dlci->state = DLCI_OPEN;
	अगर (debug & 8)
		pr_debug("DLCI %d goes open.\n", dlci->addr);
	wake_up(&dlci->gsm->event);
पूर्ण

/**
 *	gsm_dlci_t1		-	T1 समयr expiry
 *	@t: समयr contained in the DLCI that खोलोed
 *
 *	The T1 समयr handles retransmits of control frames (essentially of
 *	SABM and DISC). We resend the command until the retry count runs out
 *	in which हाल an खोलोing port goes back to बंदd and a closing port
 *	is simply put पूर्णांकo बंदd state (any further frames from the other
 *	end will get a DM response)
 *
 *	Some control dlci can stay in ADM mode with other dlci working just
 *	fine. In that हाल we can just keep the control dlci खोलो after the
 *	DLCI_OPENING retries समय out.
 */

अटल व्योम gsm_dlci_t1(काष्ठा समयr_list *t)
अणु
	काष्ठा gsm_dlci *dlci = from_समयr(dlci, t, t1);
	काष्ठा gsm_mux *gsm = dlci->gsm;

	चयन (dlci->state) अणु
	हाल DLCI_OPENING:
		dlci->retries--;
		अगर (dlci->retries) अणु
			gsm_command(dlci->gsm, dlci->addr, SABM|PF);
			mod_समयr(&dlci->t1, jअगरfies + gsm->t1 * HZ / 100);
		पूर्ण अन्यथा अगर (!dlci->addr && gsm->control == (DM | PF)) अणु
			अगर (debug & 8)
				pr_info("DLCI %d opening in ADM mode.\n",
					dlci->addr);
			dlci->mode = DLCI_MODE_ADM;
			gsm_dlci_खोलो(dlci);
		पूर्ण अन्यथा अणु
			gsm_dlci_बंद(dlci);
		पूर्ण

		अवरोध;
	हाल DLCI_CLOSING:
		dlci->retries--;
		अगर (dlci->retries) अणु
			gsm_command(dlci->gsm, dlci->addr, DISC|PF);
			mod_समयr(&dlci->t1, jअगरfies + gsm->t1 * HZ / 100);
		पूर्ण अन्यथा
			gsm_dlci_बंद(dlci);
		अवरोध;
	शेष:
		pr_debug("%s: unhandled state: %d\n", __func__, dlci->state);
		अवरोध;
	पूर्ण
पूर्ण

/**
 *	gsm_dlci_begin_खोलो	-	start channel खोलो procedure
 *	@dlci: DLCI to खोलो
 *
 *	Commence खोलोing a DLCI from the Linux side. We issue SABM messages
 *	to the modem which should then reply with a UA or ADM, at which poपूर्णांक
 *	we will move पूर्णांकo खोलो state. Opening is करोne asynchronously with retry
 *	running off समयrs and the responses.
 */

अटल व्योम gsm_dlci_begin_खोलो(काष्ठा gsm_dlci *dlci)
अणु
	काष्ठा gsm_mux *gsm = dlci->gsm;
	अगर (dlci->state == DLCI_OPEN || dlci->state == DLCI_OPENING)
		वापस;
	dlci->retries = gsm->n2;
	dlci->state = DLCI_OPENING;
	gsm_command(dlci->gsm, dlci->addr, SABM|PF);
	mod_समयr(&dlci->t1, jअगरfies + gsm->t1 * HZ / 100);
पूर्ण

/**
 *	gsm_dlci_begin_बंद	-	start channel खोलो procedure
 *	@dlci: DLCI to खोलो
 *
 *	Commence closing a DLCI from the Linux side. We issue DISC messages
 *	to the modem which should then reply with a UA, at which poपूर्णांक we
 *	will move पूर्णांकo बंदd state. Closing is करोne asynchronously with retry
 *	off समयrs. We may also receive a DM reply from the other end which
 *	indicates the channel was alपढ़ोy बंदd.
 */

अटल व्योम gsm_dlci_begin_बंद(काष्ठा gsm_dlci *dlci)
अणु
	काष्ठा gsm_mux *gsm = dlci->gsm;
	अगर (dlci->state == DLCI_CLOSED || dlci->state == DLCI_CLOSING)
		वापस;
	dlci->retries = gsm->n2;
	dlci->state = DLCI_CLOSING;
	gsm_command(dlci->gsm, dlci->addr, DISC|PF);
	mod_समयr(&dlci->t1, jअगरfies + gsm->t1 * HZ / 100);
पूर्ण

/**
 *	gsm_dlci_data		-	data arrived
 *	@dlci: channel
 *	@data: block of bytes received
 *	@clen: length of received block
 *
 *	A UI or UIH frame has arrived which contains data क्रम a channel
 *	other than the control channel. If the relevant भव tty is
 *	खोलो we shovel the bits करोwn it, अगर not we drop them.
 */

अटल व्योम gsm_dlci_data(काष्ठा gsm_dlci *dlci, स्थिर u8 *data, पूर्णांक clen)
अणु
	/* krefs .. */
	काष्ठा tty_port *port = &dlci->port;
	काष्ठा tty_काष्ठा *tty;
	अचिन्हित पूर्णांक modem = 0;
	पूर्णांक len = clen;

	अगर (debug & 16)
		pr_debug("%d bytes for tty\n", len);
	चयन (dlci->adaption)  अणु
	/* Unsupported types */
	हाल 4:		/* Packetised पूर्णांकerruptible data */
		अवरोध;
	हाल 3:		/* Packetised uinपूर्णांकerruptible voice/data */
		अवरोध;
	हाल 2:		/* Asynchronous serial with line state in each frame */
		जबतक (gsm_पढ़ो_ea(&modem, *data++) == 0) अणु
			len--;
			अगर (len == 0)
				वापस;
		पूर्ण
		tty = tty_port_tty_get(port);
		अगर (tty) अणु
			gsm_process_modem(tty, dlci, modem, clen);
			tty_kref_put(tty);
		पूर्ण
		fallthrough;
	हाल 1:		/* Line state will go via DLCI 0 controls only */
	शेष:
		tty_insert_flip_string(port, data, len);
		tty_flip_buffer_push(port);
	पूर्ण
पूर्ण

/**
 *	gsm_dlci_control	-	data arrived on control channel
 *	@dlci: channel
 *	@data: block of bytes received
 *	@len: length of received block
 *
 *	A UI or UIH frame has arrived which contains data क्रम DLCI 0 the
 *	control channel. This should contain a command EA followed by
 *	control data bytes. The command EA contains a command/response bit
 *	and we भागide up the work accordingly.
 */

अटल व्योम gsm_dlci_command(काष्ठा gsm_dlci *dlci, स्थिर u8 *data, पूर्णांक len)
अणु
	/* See what command is involved */
	अचिन्हित पूर्णांक command = 0;
	जबतक (len-- > 0) अणु
		अगर (gsm_पढ़ो_ea(&command, *data++) == 1) अणु
			पूर्णांक clen = *data++;
			len--;
			/* FIXME: this is properly an EA */
			clen >>= 1;
			/* Malक्रमmed command ? */
			अगर (clen > len)
				वापस;
			अगर (command & 1)
				gsm_control_message(dlci->gsm, command,
								data, clen);
			अन्यथा
				gsm_control_response(dlci->gsm, command,
								data, clen);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

/*
 *	Allocate/Free DLCI channels
 */

/**
 *	gsm_dlci_alloc		-	allocate a DLCI
 *	@gsm: GSM mux
 *	@addr: address of the DLCI
 *
 *	Allocate and install a new DLCI object पूर्णांकo the GSM mux.
 *
 *	FIXME: review locking races
 */

अटल काष्ठा gsm_dlci *gsm_dlci_alloc(काष्ठा gsm_mux *gsm, पूर्णांक addr)
अणु
	काष्ठा gsm_dlci *dlci = kzalloc(माप(काष्ठा gsm_dlci), GFP_ATOMIC);
	अगर (dlci == शून्य)
		वापस शून्य;
	spin_lock_init(&dlci->lock);
	mutex_init(&dlci->mutex);
	अगर (kfअगरo_alloc(&dlci->fअगरo, 4096, GFP_KERNEL) < 0) अणु
		kमुक्त(dlci);
		वापस शून्य;
	पूर्ण

	skb_queue_head_init(&dlci->skb_list);
	समयr_setup(&dlci->t1, gsm_dlci_t1, 0);
	tty_port_init(&dlci->port);
	dlci->port.ops = &gsm_port_ops;
	dlci->gsm = gsm;
	dlci->addr = addr;
	dlci->adaption = gsm->adaption;
	dlci->state = DLCI_CLOSED;
	अगर (addr)
		dlci->data = gsm_dlci_data;
	अन्यथा
		dlci->data = gsm_dlci_command;
	gsm->dlci[addr] = dlci;
	वापस dlci;
पूर्ण

/**
 *	gsm_dlci_मुक्त		-	मुक्त DLCI
 *	@port: tty port क्रम DLCI to मुक्त
 *
 *	Free up a DLCI.
 *
 *	Can sleep.
 */
अटल व्योम gsm_dlci_मुक्त(काष्ठा tty_port *port)
अणु
	काष्ठा gsm_dlci *dlci = container_of(port, काष्ठा gsm_dlci, port);

	del_समयr_sync(&dlci->t1);
	dlci->gsm->dlci[dlci->addr] = शून्य;
	kfअगरo_मुक्त(&dlci->fअगरo);
	जबतक ((dlci->skb = skb_dequeue(&dlci->skb_list)))
		dev_kमुक्त_skb(dlci->skb);
	kमुक्त(dlci);
पूर्ण

अटल अंतरभूत व्योम dlci_get(काष्ठा gsm_dlci *dlci)
अणु
	tty_port_get(&dlci->port);
पूर्ण

अटल अंतरभूत व्योम dlci_put(काष्ठा gsm_dlci *dlci)
अणु
	tty_port_put(&dlci->port);
पूर्ण

अटल व्योम gsm_destroy_network(काष्ठा gsm_dlci *dlci);

/**
 *	gsm_dlci_release		-	release DLCI
 *	@dlci: DLCI to destroy
 *
 *	Release a DLCI. Actual मुक्त is deferred until either
 *	mux is बंदd or tty is बंदd - whichever is last.
 *
 *	Can sleep.
 */
अटल व्योम gsm_dlci_release(काष्ठा gsm_dlci *dlci)
अणु
	काष्ठा tty_काष्ठा *tty = tty_port_tty_get(&dlci->port);
	अगर (tty) अणु
		mutex_lock(&dlci->mutex);
		gsm_destroy_network(dlci);
		mutex_unlock(&dlci->mutex);

		tty_hangup(tty);

		tty_port_tty_set(&dlci->port, शून्य);
		tty_kref_put(tty);
	पूर्ण
	dlci->state = DLCI_CLOSED;
	dlci_put(dlci);
पूर्ण

/*
 *	LAPBish link layer logic
 */

/**
 *	gsm_queue		-	a GSM frame is पढ़ोy to process
 *	@gsm: poपूर्णांकer to our gsm mux
 *
 *	At this poपूर्णांक in समय a frame has arrived and been demangled from
 *	the line encoding. All the dअगरferences between the encodings have
 *	been handled below us and the frame is unpacked पूर्णांकo the काष्ठाures.
 *	The fcs holds the header FCS but any data FCS must be added here.
 */

अटल व्योम gsm_queue(काष्ठा gsm_mux *gsm)
अणु
	काष्ठा gsm_dlci *dlci;
	u8 cr;
	पूर्णांक address;
	/* We have to sneak a look at the packet body to करो the FCS.
	   A somewhat layering violation in the spec */

	अगर ((gsm->control & ~PF) == UI)
		gsm->fcs = gsm_fcs_add_block(gsm->fcs, gsm->buf, gsm->len);
	अगर (gsm->encoding == 0) अणु
		/* WARNING: gsm->received_fcs is used क्रम
		gsm->encoding = 0 only.
		In this हाल it contain the last piece of data
		required to generate final CRC */
		gsm->fcs = gsm_fcs_add(gsm->fcs, gsm->received_fcs);
	पूर्ण
	अगर (gsm->fcs != GOOD_FCS) अणु
		gsm->bad_fcs++;
		अगर (debug & 4)
			pr_debug("BAD FCS %02x\n", gsm->fcs);
		वापस;
	पूर्ण
	address = gsm->address >> 1;
	अगर (address >= NUM_DLCI)
		जाओ invalid;

	cr = gsm->address & 1;		/* C/R bit */

	gsm_prपूर्णांक_packet("<--", address, cr, gsm->control, gsm->buf, gsm->len);

	cr ^= 1 - gsm->initiator;	/* Flip so 1 always means command */
	dlci = gsm->dlci[address];

	चयन (gsm->control) अणु
	हाल SABM|PF:
		अगर (cr == 0)
			जाओ invalid;
		अगर (dlci == शून्य)
			dlci = gsm_dlci_alloc(gsm, address);
		अगर (dlci == शून्य)
			वापस;
		अगर (dlci->dead)
			gsm_response(gsm, address, DM);
		अन्यथा अणु
			gsm_response(gsm, address, UA);
			gsm_dlci_खोलो(dlci);
		पूर्ण
		अवरोध;
	हाल DISC|PF:
		अगर (cr == 0)
			जाओ invalid;
		अगर (dlci == शून्य || dlci->state == DLCI_CLOSED) अणु
			gsm_response(gsm, address, DM);
			वापस;
		पूर्ण
		/* Real बंद complete */
		gsm_response(gsm, address, UA);
		gsm_dlci_बंद(dlci);
		अवरोध;
	हाल UA:
	हाल UA|PF:
		अगर (cr == 0 || dlci == शून्य)
			अवरोध;
		चयन (dlci->state) अणु
		हाल DLCI_CLOSING:
			gsm_dlci_बंद(dlci);
			अवरोध;
		हाल DLCI_OPENING:
			gsm_dlci_खोलो(dlci);
			अवरोध;
		शेष:
			pr_debug("%s: unhandled state: %d\n", __func__,
					dlci->state);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल DM:	/* DM can be valid unsolicited */
	हाल DM|PF:
		अगर (cr)
			जाओ invalid;
		अगर (dlci == शून्य)
			वापस;
		gsm_dlci_बंद(dlci);
		अवरोध;
	हाल UI:
	हाल UI|PF:
	हाल UIH:
	हाल UIH|PF:
#अगर 0
		अगर (cr)
			जाओ invalid;
#पूर्ण_अगर
		अगर (dlci == शून्य || dlci->state != DLCI_OPEN) अणु
			gsm_command(gsm, address, DM|PF);
			वापस;
		पूर्ण
		dlci->data(dlci, gsm->buf, gsm->len);
		अवरोध;
	शेष:
		जाओ invalid;
	पूर्ण
	वापस;
invalid:
	gsm->malक्रमmed++;
	वापस;
पूर्ण


/**
 *	gsm0_receive	-	perक्रमm processing क्रम non-transparency
 *	@gsm: gsm data क्रम this ldisc instance
 *	@c: अक्षरacter
 *
 *	Receive bytes in gsm mode 0
 */

अटल व्योम gsm0_receive(काष्ठा gsm_mux *gsm, अचिन्हित अक्षर c)
अणु
	अचिन्हित पूर्णांक len;

	चयन (gsm->state) अणु
	हाल GSM_SEARCH:	/* SOF marker */
		अगर (c == GSM0_SOF) अणु
			gsm->state = GSM_ADDRESS;
			gsm->address = 0;
			gsm->len = 0;
			gsm->fcs = INIT_FCS;
		पूर्ण
		अवरोध;
	हाल GSM_ADDRESS:	/* Address EA */
		gsm->fcs = gsm_fcs_add(gsm->fcs, c);
		अगर (gsm_पढ़ो_ea(&gsm->address, c))
			gsm->state = GSM_CONTROL;
		अवरोध;
	हाल GSM_CONTROL:	/* Control Byte */
		gsm->fcs = gsm_fcs_add(gsm->fcs, c);
		gsm->control = c;
		gsm->state = GSM_LEN0;
		अवरोध;
	हाल GSM_LEN0:		/* Length EA */
		gsm->fcs = gsm_fcs_add(gsm->fcs, c);
		अगर (gsm_पढ़ो_ea(&gsm->len, c)) अणु
			अगर (gsm->len > gsm->mru) अणु
				gsm->bad_size++;
				gsm->state = GSM_SEARCH;
				अवरोध;
			पूर्ण
			gsm->count = 0;
			अगर (!gsm->len)
				gsm->state = GSM_FCS;
			अन्यथा
				gsm->state = GSM_DATA;
			अवरोध;
		पूर्ण
		gsm->state = GSM_LEN1;
		अवरोध;
	हाल GSM_LEN1:
		gsm->fcs = gsm_fcs_add(gsm->fcs, c);
		len = c;
		gsm->len |= len << 7;
		अगर (gsm->len > gsm->mru) अणु
			gsm->bad_size++;
			gsm->state = GSM_SEARCH;
			अवरोध;
		पूर्ण
		gsm->count = 0;
		अगर (!gsm->len)
			gsm->state = GSM_FCS;
		अन्यथा
			gsm->state = GSM_DATA;
		अवरोध;
	हाल GSM_DATA:		/* Data */
		gsm->buf[gsm->count++] = c;
		अगर (gsm->count == gsm->len)
			gsm->state = GSM_FCS;
		अवरोध;
	हाल GSM_FCS:		/* FCS follows the packet */
		gsm->received_fcs = c;
		gsm_queue(gsm);
		gsm->state = GSM_SSOF;
		अवरोध;
	हाल GSM_SSOF:
		अगर (c == GSM0_SOF) अणु
			gsm->state = GSM_SEARCH;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		pr_debug("%s: unhandled state: %d\n", __func__, gsm->state);
		अवरोध;
	पूर्ण
पूर्ण

/**
 *	gsm1_receive	-	perक्रमm processing क्रम non-transparency
 *	@gsm: gsm data क्रम this ldisc instance
 *	@c: अक्षरacter
 *
 *	Receive bytes in mode 1 (Advanced option)
 */

अटल व्योम gsm1_receive(काष्ठा gsm_mux *gsm, अचिन्हित अक्षर c)
अणु
	अगर (c == GSM1_SOF) अणु
		/* खातापूर्ण is only valid in frame अगर we have got to the data state
		   and received at least one byte (the FCS) */
		अगर (gsm->state == GSM_DATA && gsm->count) अणु
			/* Extract the FCS */
			gsm->count--;
			gsm->fcs = gsm_fcs_add(gsm->fcs, gsm->buf[gsm->count]);
			gsm->len = gsm->count;
			gsm_queue(gsm);
			gsm->state  = GSM_START;
			वापस;
		पूर्ण
		/* Any partial frame was a runt so go back to start */
		अगर (gsm->state != GSM_START) अणु
			gsm->malक्रमmed++;
			gsm->state = GSM_START;
		पूर्ण
		/* A SOF in GSM_START means we are still पढ़ोing idling or
		   framing bytes */
		वापस;
	पूर्ण

	अगर (c == GSM1_ESCAPE) अणु
		gsm->escape = true;
		वापस;
	पूर्ण

	/* Only an unescaped SOF माला_लो us out of GSM search */
	अगर (gsm->state == GSM_SEARCH)
		वापस;

	अगर (gsm->escape) अणु
		c ^= GSM1_ESCAPE_BITS;
		gsm->escape = false;
	पूर्ण
	चयन (gsm->state) अणु
	हाल GSM_START:		/* First byte after SOF */
		gsm->address = 0;
		gsm->state = GSM_ADDRESS;
		gsm->fcs = INIT_FCS;
		fallthrough;
	हाल GSM_ADDRESS:	/* Address continuation */
		gsm->fcs = gsm_fcs_add(gsm->fcs, c);
		अगर (gsm_पढ़ो_ea(&gsm->address, c))
			gsm->state = GSM_CONTROL;
		अवरोध;
	हाल GSM_CONTROL:	/* Control Byte */
		gsm->fcs = gsm_fcs_add(gsm->fcs, c);
		gsm->control = c;
		gsm->count = 0;
		gsm->state = GSM_DATA;
		अवरोध;
	हाल GSM_DATA:		/* Data */
		अगर (gsm->count > gsm->mru) अणु	/* Allow one क्रम the FCS */
			gsm->state = GSM_OVERRUN;
			gsm->bad_size++;
		पूर्ण अन्यथा
			gsm->buf[gsm->count++] = c;
		अवरोध;
	हाल GSM_OVERRUN:	/* Over-दीर्घ - eg a dropped SOF */
		अवरोध;
	शेष:
		pr_debug("%s: unhandled state: %d\n", __func__, gsm->state);
		अवरोध;
	पूर्ण
पूर्ण

/**
 *	gsm_error		-	handle tty error
 *	@gsm: ldisc data
 *	@data: byte received (may be invalid)
 *	@flag: error received
 *
 *	Handle an error in the receipt of data क्रम a frame. Currently we just
 *	go back to hunting क्रम a SOF.
 *
 *	FIXME: better diagnostics ?
 */

अटल व्योम gsm_error(काष्ठा gsm_mux *gsm,
				अचिन्हित अक्षर data, अचिन्हित अक्षर flag)
अणु
	gsm->state = GSM_SEARCH;
	gsm->io_error++;
पूर्ण

अटल पूर्णांक gsm_disconnect(काष्ठा gsm_mux *gsm)
अणु
	काष्ठा gsm_dlci *dlci = gsm->dlci[0];
	काष्ठा gsm_control *gc;

	अगर (!dlci)
		वापस 0;

	/* In theory disconnecting DLCI 0 is sufficient but क्रम some
	   modems this is apparently not the हाल. */
	gc = gsm_control_send(gsm, CMD_CLD, शून्य, 0);
	अगर (gc)
		gsm_control_रुको(gsm, gc);

	del_समयr_sync(&gsm->t2_समयr);
	/* Now we are sure T2 has stopped */

	gsm_dlci_begin_बंद(dlci);
	रुको_event_पूर्णांकerruptible(gsm->event,
				dlci->state == DLCI_CLOSED);

	अगर (संकेत_pending(current))
		वापस -EINTR;

	वापस 0;
पूर्ण

/**
 *	gsm_cleanup_mux		-	generic GSM protocol cleanup
 *	@gsm: our mux
 *
 *	Clean up the bits of the mux which are the same क्रम all framing
 *	protocols. Remove the mux from the mux table, stop all the समयrs
 *	and then shut करोwn each device hanging up the channels as we go.
 */

अटल व्योम gsm_cleanup_mux(काष्ठा gsm_mux *gsm)
अणु
	पूर्णांक i;
	काष्ठा gsm_dlci *dlci = gsm->dlci[0];
	काष्ठा gsm_msg *txq, *ntxq;

	gsm->dead = true;

	spin_lock(&gsm_mux_lock);
	क्रम (i = 0; i < MAX_MUX; i++) अणु
		अगर (gsm_mux[i] == gsm) अणु
			gsm_mux[i] = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&gsm_mux_lock);
	/* खोलो failed beक्रमe रेजिस्टरing => nothing to करो */
	अगर (i == MAX_MUX)
		वापस;

	del_समयr_sync(&gsm->t2_समयr);
	/* Now we are sure T2 has stopped */
	अगर (dlci)
		dlci->dead = true;

	/* Free up any link layer users */
	mutex_lock(&gsm->mutex);
	क्रम (i = 0; i < NUM_DLCI; i++)
		अगर (gsm->dlci[i])
			gsm_dlci_release(gsm->dlci[i]);
	mutex_unlock(&gsm->mutex);
	/* Now wipe the queues */
	list_क्रम_each_entry_safe(txq, ntxq, &gsm->tx_list, list)
		kमुक्त(txq);
	INIT_LIST_HEAD(&gsm->tx_list);
पूर्ण

/**
 *	gsm_activate_mux	-	generic GSM setup
 *	@gsm: our mux
 *
 *	Set up the bits of the mux which are the same क्रम all framing
 *	protocols. Add the mux to the mux table so it can be खोलोed and
 *	finally kick off connecting to DLCI 0 on the modem.
 */

अटल पूर्णांक gsm_activate_mux(काष्ठा gsm_mux *gsm)
अणु
	काष्ठा gsm_dlci *dlci;
	पूर्णांक i = 0;

	समयr_setup(&gsm->t2_समयr, gsm_control_retransmit, 0);
	init_रुकोqueue_head(&gsm->event);
	spin_lock_init(&gsm->control_lock);
	spin_lock_init(&gsm->tx_lock);

	अगर (gsm->encoding == 0)
		gsm->receive = gsm0_receive;
	अन्यथा
		gsm->receive = gsm1_receive;

	spin_lock(&gsm_mux_lock);
	क्रम (i = 0; i < MAX_MUX; i++) अणु
		अगर (gsm_mux[i] == शून्य) अणु
			gsm->num = i;
			gsm_mux[i] = gsm;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&gsm_mux_lock);
	अगर (i == MAX_MUX)
		वापस -EBUSY;

	dlci = gsm_dlci_alloc(gsm, 0);
	अगर (dlci == शून्य)
		वापस -ENOMEM;
	gsm->dead = false;		/* Tty खोलोs are now permissible */
	वापस 0;
पूर्ण

/**
 *	gsm_मुक्त_mux		-	मुक्त up a mux
 *	@gsm: mux to मुक्त
 *
 *	Dispose of allocated resources क्रम a dead mux
 */
अटल व्योम gsm_मुक्त_mux(काष्ठा gsm_mux *gsm)
अणु
	kमुक्त(gsm->txframe);
	kमुक्त(gsm->buf);
	kमुक्त(gsm);
पूर्ण

/**
 *	gsm_मुक्त_muxr		-	मुक्त up a mux
 *	@ref: kreference to the mux to मुक्त
 *
 *	Dispose of allocated resources क्रम a dead mux
 */
अटल व्योम gsm_मुक्त_muxr(काष्ठा kref *ref)
अणु
	काष्ठा gsm_mux *gsm = container_of(ref, काष्ठा gsm_mux, ref);
	gsm_मुक्त_mux(gsm);
पूर्ण

अटल अंतरभूत व्योम mux_get(काष्ठा gsm_mux *gsm)
अणु
	kref_get(&gsm->ref);
पूर्ण

अटल अंतरभूत व्योम mux_put(काष्ठा gsm_mux *gsm)
अणु
	kref_put(&gsm->ref, gsm_मुक्त_muxr);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक mux_num_to_base(काष्ठा gsm_mux *gsm)
अणु
	वापस gsm->num * NUM_DLCI;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक mux_line_to_num(अचिन्हित पूर्णांक line)
अणु
	वापस line / NUM_DLCI;
पूर्ण

/**
 *	gsm_alloc_mux		-	allocate a mux
 *
 *	Creates a new mux पढ़ोy क्रम activation.
 */

अटल काष्ठा gsm_mux *gsm_alloc_mux(व्योम)
अणु
	काष्ठा gsm_mux *gsm = kzalloc(माप(काष्ठा gsm_mux), GFP_KERNEL);
	अगर (gsm == शून्य)
		वापस शून्य;
	gsm->buf = kदो_स्मृति(MAX_MRU + 1, GFP_KERNEL);
	अगर (gsm->buf == शून्य) अणु
		kमुक्त(gsm);
		वापस शून्य;
	पूर्ण
	gsm->txframe = kदो_स्मृति(2 * MAX_MRU + 2, GFP_KERNEL);
	अगर (gsm->txframe == शून्य) अणु
		kमुक्त(gsm->buf);
		kमुक्त(gsm);
		वापस शून्य;
	पूर्ण
	spin_lock_init(&gsm->lock);
	mutex_init(&gsm->mutex);
	kref_init(&gsm->ref);
	INIT_LIST_HEAD(&gsm->tx_list);

	gsm->t1 = T1;
	gsm->t2 = T2;
	gsm->n2 = N2;
	gsm->ftype = UIH;
	gsm->adaption = 1;
	gsm->encoding = 1;
	gsm->mru = 64;	/* Default to encoding 1 so these should be 64 */
	gsm->mtu = 64;
	gsm->dead = true;	/* Aव्योम early tty खोलोs */

	वापस gsm;
पूर्ण

अटल व्योम gsm_copy_config_values(काष्ठा gsm_mux *gsm,
				   काष्ठा gsm_config *c)
अणु
	स_रखो(c, 0, माप(*c));
	c->adaption = gsm->adaption;
	c->encapsulation = gsm->encoding;
	c->initiator = gsm->initiator;
	c->t1 = gsm->t1;
	c->t2 = gsm->t2;
	c->t3 = 0;	/* Not supported */
	c->n2 = gsm->n2;
	अगर (gsm->ftype == UIH)
		c->i = 1;
	अन्यथा
		c->i = 2;
	pr_debug("Ftype %d i %d\n", gsm->ftype, c->i);
	c->mru = gsm->mru;
	c->mtu = gsm->mtu;
	c->k = 0;
पूर्ण

अटल पूर्णांक gsm_config(काष्ठा gsm_mux *gsm, काष्ठा gsm_config *c)
अणु
	पूर्णांक need_बंद = 0;
	पूर्णांक need_restart = 0;

	/* Stuff we करोn't support yet - UI or I frame transport, winकरोwing */
	अगर ((c->adaption != 1 && c->adaption != 2) || c->k)
		वापस -EOPNOTSUPP;
	/* Check the MRU/MTU range looks sane */
	अगर (c->mru > MAX_MRU || c->mtu > MAX_MTU || c->mru < 8 || c->mtu < 8)
		वापस -EINVAL;
	अगर (c->n2 < 3)
		वापस -EINVAL;
	अगर (c->encapsulation > 1)	/* Basic, advanced, no I */
		वापस -EINVAL;
	अगर (c->initiator > 1)
		वापस -EINVAL;
	अगर (c->i == 0 || c->i > 2)	/* UIH and UI only */
		वापस -EINVAL;
	/*
	 * See what is needed क्रम reconfiguration
	 */

	/* Timing fields */
	अगर (c->t1 != 0 && c->t1 != gsm->t1)
		need_restart = 1;
	अगर (c->t2 != 0 && c->t2 != gsm->t2)
		need_restart = 1;
	अगर (c->encapsulation != gsm->encoding)
		need_restart = 1;
	अगर (c->adaption != gsm->adaption)
		need_restart = 1;
	/* Requires care */
	अगर (c->initiator != gsm->initiator)
		need_बंद = 1;
	अगर (c->mru != gsm->mru)
		need_restart = 1;
	अगर (c->mtu != gsm->mtu)
		need_restart = 1;

	/*
	 * Close करोwn what is needed, restart and initiate the new
	 * configuration
	 */

	अगर (need_बंद || need_restart) अणु
		पूर्णांक ret;

		ret = gsm_disconnect(gsm);

		अगर (ret)
			वापस ret;
	पूर्ण
	अगर (need_restart)
		gsm_cleanup_mux(gsm);

	gsm->initiator = c->initiator;
	gsm->mru = c->mru;
	gsm->mtu = c->mtu;
	gsm->encoding = c->encapsulation;
	gsm->adaption = c->adaption;
	gsm->n2 = c->n2;

	अगर (c->i == 1)
		gsm->ftype = UIH;
	अन्यथा अगर (c->i == 2)
		gsm->ftype = UI;

	अगर (c->t1)
		gsm->t1 = c->t1;
	अगर (c->t2)
		gsm->t2 = c->t2;

	/*
	 * FIXME: We need to separate activation/deactivation from adding
	 * and removing from the mux array
	 */
	अगर (need_restart)
		gsm_activate_mux(gsm);
	अगर (gsm->initiator && need_बंद)
		gsm_dlci_begin_खोलो(gsm->dlci[0]);
	वापस 0;
पूर्ण

/**
 *	gsmld_output		-	ग_लिखो to link
 *	@gsm: our mux
 *	@data: bytes to output
 *	@len: size
 *
 *	Write a block of data from the GSM mux to the data channel. This
 *	will eventually be serialized from above but at the moment isn't.
 */

अटल पूर्णांक gsmld_output(काष्ठा gsm_mux *gsm, u8 *data, पूर्णांक len)
अणु
	अगर (tty_ग_लिखो_room(gsm->tty) < len) अणु
		set_bit(TTY_DO_WRITE_WAKEUP, &gsm->tty->flags);
		वापस -ENOSPC;
	पूर्ण
	अगर (debug & 4)
		prपूर्णांक_hex_dump_bytes("gsmld_output: ", DUMP_PREFIX_OFFSET,
				     data, len);
	gsm->tty->ops->ग_लिखो(gsm->tty, data, len);
	वापस len;
पूर्ण

/**
 *	gsmld_attach_gsm	-	mode set up
 *	@tty: our tty काष्ठाure
 *	@gsm: our mux
 *
 *	Set up the MUX क्रम basic mode and commence connecting to the
 *	modem. Currently called from the line discipline set up but
 *	will need moving to an ioctl path.
 */

अटल पूर्णांक gsmld_attach_gsm(काष्ठा tty_काष्ठा *tty, काष्ठा gsm_mux *gsm)
अणु
	अचिन्हित पूर्णांक base;
	पूर्णांक ret, i;

	gsm->tty = tty_kref_get(tty);
	ret =  gsm_activate_mux(gsm);
	अगर (ret != 0)
		tty_kref_put(gsm->tty);
	अन्यथा अणु
		/* Don't रेजिस्टर device 0 - this is the control channel and not
		   a usable tty पूर्णांकerface */
		base = mux_num_to_base(gsm); /* Base क्रम this MUX */
		क्रम (i = 1; i < NUM_DLCI; i++) अणु
			काष्ठा device *dev;

			dev = tty_रेजिस्टर_device(gsm_tty_driver,
							base + i, शून्य);
			अगर (IS_ERR(dev)) अणु
				क्रम (i--; i >= 1; i--)
					tty_unरेजिस्टर_device(gsm_tty_driver,
								base + i);
				वापस PTR_ERR(dev);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण


/**
 *	gsmld_detach_gsm	-	stop करोing 0710 mux
 *	@tty: tty attached to the mux
 *	@gsm: mux
 *
 *	Shutकरोwn and then clean up the resources used by the line discipline
 */

अटल व्योम gsmld_detach_gsm(काष्ठा tty_काष्ठा *tty, काष्ठा gsm_mux *gsm)
अणु
	अचिन्हित पूर्णांक base = mux_num_to_base(gsm); /* Base क्रम this MUX */
	पूर्णांक i;

	WARN_ON(tty != gsm->tty);
	क्रम (i = 1; i < NUM_DLCI; i++)
		tty_unरेजिस्टर_device(gsm_tty_driver, base + i);
	gsm_cleanup_mux(gsm);
	tty_kref_put(gsm->tty);
	gsm->tty = शून्य;
पूर्ण

अटल व्योम gsmld_receive_buf(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *cp,
			      अक्षर *fp, पूर्णांक count)
अणु
	काष्ठा gsm_mux *gsm = tty->disc_data;
	अक्षर flags = TTY_NORMAL;

	अगर (debug & 4)
		prपूर्णांक_hex_dump_bytes("gsmld_receive: ", DUMP_PREFIX_OFFSET,
				     cp, count);

	क्रम (; count; count--, cp++) अणु
		अगर (fp)
			flags = *fp++;
		चयन (flags) अणु
		हाल TTY_NORMAL:
			gsm->receive(gsm, *cp);
			अवरोध;
		हाल TTY_OVERRUN:
		हाल TTY_BREAK:
		हाल TTY_PARITY:
		हाल TTY_FRAME:
			gsm_error(gsm, *cp, flags);
			अवरोध;
		शेष:
			WARN_ONCE(1, "%s: unknown flag %d\n",
			       tty_name(tty), flags);
			अवरोध;
		पूर्ण
	पूर्ण
	/* FASYNC अगर needed ? */
	/* If clogged call tty_throttle(tty); */
पूर्ण

/**
 *	gsmld_flush_buffer	-	clean input queue
 *	@tty:	terminal device
 *
 *	Flush the input buffer. Called when the line discipline is
 *	being बंदd, when the tty layer wants the buffer flushed (eg
 *	at hangup).
 */

अटल व्योम gsmld_flush_buffer(काष्ठा tty_काष्ठा *tty)
अणु
पूर्ण

/**
 *	gsmld_बंद		-	बंद the ldisc क्रम this tty
 *	@tty: device
 *
 *	Called from the terminal layer when this line discipline is
 *	being shut करोwn, either because of a बंद or becsuse of a
 *	discipline change. The function will not be called जबतक other
 *	ldisc methods are in progress.
 */

अटल व्योम gsmld_बंद(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gsm_mux *gsm = tty->disc_data;

	gsmld_detach_gsm(tty, gsm);

	gsmld_flush_buffer(tty);
	/* Do other clean up here */
	mux_put(gsm);
पूर्ण

/**
 *	gsmld_खोलो		-	खोलो an ldisc
 *	@tty: terminal to खोलो
 *
 *	Called when this line discipline is being attached to the
 *	terminal device. Can sleep. Called serialized so that no
 *	other events will occur in parallel. No further खोलो will occur
 *	until a बंद.
 */

अटल पूर्णांक gsmld_खोलो(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gsm_mux *gsm;
	पूर्णांक ret;

	अगर (tty->ops->ग_लिखो == शून्य)
		वापस -EINVAL;

	/* Attach our ldisc data */
	gsm = gsm_alloc_mux();
	अगर (gsm == शून्य)
		वापस -ENOMEM;

	tty->disc_data = gsm;
	tty->receive_room = 65536;

	/* Attach the initial passive connection */
	gsm->encoding = 1;

	ret = gsmld_attach_gsm(tty, gsm);
	अगर (ret != 0) अणु
		gsm_cleanup_mux(gsm);
		mux_put(gsm);
	पूर्ण
	वापस ret;
पूर्ण

/**
 *	gsmld_ग_लिखो_wakeup	-	asynchronous I/O notअगरier
 *	@tty: tty device
 *
 *	Required क्रम the ptys, serial driver etc. since processes
 *	that attach themselves to the master and rely on ASYNC
 *	IO must be woken up
 */

अटल व्योम gsmld_ग_लिखो_wakeup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gsm_mux *gsm = tty->disc_data;
	अचिन्हित दीर्घ flags;

	/* Queue poll */
	clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
	spin_lock_irqsave(&gsm->tx_lock, flags);
	gsm_data_kick(gsm, शून्य);
	अगर (gsm->tx_bytes < TX_THRESH_LO) अणु
		gsm_dlci_data_sweep(gsm);
	पूर्ण
	spin_unlock_irqrestore(&gsm->tx_lock, flags);
पूर्ण

/**
 *	gsmld_पढ़ो		-	पढ़ो function क्रम tty
 *	@tty: tty device
 *	@file: file object
 *	@buf: userspace buffer poपूर्णांकer
 *	@nr: size of I/O
 *
 *	Perक्रमm पढ़ोs क्रम the line discipline. We are guaranteed that the
 *	line discipline will not be बंदd under us but we may get multiple
 *	parallel पढ़ोers and must handle this ourselves. We may also get
 *	a hangup. Always called in user context, may sleep.
 *
 *	This code must be sure never to sleep through a hangup.
 */

अटल sमाप_प्रकार gsmld_पढ़ो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
			  अचिन्हित अक्षर *buf, माप_प्रकार nr,
			  व्योम **cookie, अचिन्हित दीर्घ offset)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

/**
 *	gsmld_ग_लिखो		-	ग_लिखो function क्रम tty
 *	@tty: tty device
 *	@file: file object
 *	@buf: userspace buffer poपूर्णांकer
 *	@nr: size of I/O
 *
 *	Called when the owner of the device wants to send a frame
 *	itself (or some other control data). The data is transferred
 *	as-is and must be properly framed and checksummed as appropriate
 *	by userspace. Frames are either sent whole or not at all as this
 *	aव्योमs pain user side.
 */

अटल sमाप_प्रकार gsmld_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
			   स्थिर अचिन्हित अक्षर *buf, माप_प्रकार nr)
अणु
	पूर्णांक space = tty_ग_लिखो_room(tty);
	अगर (space >= nr)
		वापस tty->ops->ग_लिखो(tty, buf, nr);
	set_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
	वापस -ENOBUFS;
पूर्ण

/**
 *	gsmld_poll		-	poll method क्रम N_GSM0710
 *	@tty: terminal device
 *	@file: file accessing it
 *	@रुको: poll table
 *
 *	Called when the line discipline is asked to poll() क्रम data or
 *	क्रम special events. This code is not serialized with respect to
 *	other events save खोलो/बंद.
 *
 *	This code must be sure never to sleep through a hangup.
 *	Called without the kernel lock held - fine
 */

अटल __poll_t gsmld_poll(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
							poll_table *रुको)
अणु
	__poll_t mask = 0;
	काष्ठा gsm_mux *gsm = tty->disc_data;

	poll_रुको(file, &tty->पढ़ो_रुको, रुको);
	poll_रुको(file, &tty->ग_लिखो_रुको, रुको);
	अगर (tty_hung_up_p(file))
		mask |= EPOLLHUP;
	अगर (!tty_is_ग_लिखोlocked(tty) && tty_ग_लिखो_room(tty) > 0)
		mask |= EPOLLOUT | EPOLLWRNORM;
	अगर (gsm->dead)
		mask |= EPOLLHUP;
	वापस mask;
पूर्ण

अटल पूर्णांक gsmld_ioctl(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
		       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा gsm_config c;
	काष्ठा gsm_mux *gsm = tty->disc_data;
	अचिन्हित पूर्णांक base;

	चयन (cmd) अणु
	हाल GSMIOC_GETCONF:
		gsm_copy_config_values(gsm, &c);
		अगर (copy_to_user((व्योम __user *)arg, &c, माप(c)))
			वापस -EFAULT;
		वापस 0;
	हाल GSMIOC_SETCONF:
		अगर (copy_from_user(&c, (व्योम __user *)arg, माप(c)))
			वापस -EFAULT;
		वापस gsm_config(gsm, &c);
	हाल GSMIOC_GETFIRST:
		base = mux_num_to_base(gsm);
		वापस put_user(base + 1, (__u32 __user *)arg);
	शेष:
		वापस n_tty_ioctl_helper(tty, file, cmd, arg);
	पूर्ण
पूर्ण

/*
 *	Network पूर्णांकerface
 *
 */

अटल पूर्णांक gsm_mux_net_खोलो(काष्ठा net_device *net)
अणु
	pr_debug("%s called\n", __func__);
	netअगर_start_queue(net);
	वापस 0;
पूर्ण

अटल पूर्णांक gsm_mux_net_बंद(काष्ठा net_device *net)
अणु
	netअगर_stop_queue(net);
	वापस 0;
पूर्ण

अटल व्योम dlci_net_मुक्त(काष्ठा gsm_dlci *dlci)
अणु
	अगर (!dlci->net) अणु
		WARN_ON(1);
		वापस;
	पूर्ण
	dlci->adaption = dlci->prev_adaption;
	dlci->data = dlci->prev_data;
	मुक्त_netdev(dlci->net);
	dlci->net = शून्य;
पूर्ण
अटल व्योम net_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा gsm_mux_net *mux_net;
	काष्ठा gsm_dlci *dlci;

	mux_net = container_of(ref, काष्ठा gsm_mux_net, ref);
	dlci = mux_net->dlci;

	अगर (dlci->net) अणु
		unरेजिस्टर_netdev(dlci->net);
		dlci_net_मुक्त(dlci);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम muxnet_get(काष्ठा gsm_mux_net *mux_net)
अणु
	kref_get(&mux_net->ref);
पूर्ण

अटल अंतरभूत व्योम muxnet_put(काष्ठा gsm_mux_net *mux_net)
अणु
	kref_put(&mux_net->ref, net_मुक्त);
पूर्ण

अटल netdev_tx_t gsm_mux_net_start_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *net)
अणु
	काष्ठा gsm_mux_net *mux_net = netdev_priv(net);
	काष्ठा gsm_dlci *dlci = mux_net->dlci;
	muxnet_get(mux_net);

	skb_queue_head(&dlci->skb_list, skb);
	net->stats.tx_packets++;
	net->stats.tx_bytes += skb->len;
	gsm_dlci_data_kick(dlci);
	/* And tell the kernel when the last transmit started. */
	netअगर_trans_update(net);
	muxnet_put(mux_net);
	वापस NETDEV_TX_OK;
पूर्ण

/* called when a packet did not ack after watchकरोgसमयout */
अटल व्योम gsm_mux_net_tx_समयout(काष्ठा net_device *net, अचिन्हित पूर्णांक txqueue)
अणु
	/* Tell syslog we are hosed. */
	dev_dbg(&net->dev, "Tx timed out.\n");

	/* Update statistics */
	net->stats.tx_errors++;
पूर्ण

अटल व्योम gsm_mux_rx_netअक्षर(काष्ठा gsm_dlci *dlci,
				स्थिर अचिन्हित अक्षर *in_buf, पूर्णांक size)
अणु
	काष्ठा net_device *net = dlci->net;
	काष्ठा sk_buff *skb;
	काष्ठा gsm_mux_net *mux_net = netdev_priv(net);
	muxnet_get(mux_net);

	/* Allocate an sk_buff */
	skb = dev_alloc_skb(size + NET_IP_ALIGN);
	अगर (!skb) अणु
		/* We got no receive buffer. */
		net->stats.rx_dropped++;
		muxnet_put(mux_net);
		वापस;
	पूर्ण
	skb_reserve(skb, NET_IP_ALIGN);
	skb_put_data(skb, in_buf, size);

	skb->dev = net;
	skb->protocol = htons(ETH_P_IP);

	/* Ship it off to the kernel */
	netअगर_rx(skb);

	/* update out statistics */
	net->stats.rx_packets++;
	net->stats.rx_bytes += size;
	muxnet_put(mux_net);
	वापस;
पूर्ण

अटल व्योम gsm_mux_net_init(काष्ठा net_device *net)
अणु
	अटल स्थिर काष्ठा net_device_ops gsm_netdev_ops = अणु
		.nकरो_खोलो		= gsm_mux_net_खोलो,
		.nकरो_stop		= gsm_mux_net_बंद,
		.nकरो_start_xmit		= gsm_mux_net_start_xmit,
		.nकरो_tx_समयout		= gsm_mux_net_tx_समयout,
	पूर्ण;

	net->netdev_ops = &gsm_netdev_ops;

	/* fill in the other fields */
	net->watchकरोg_समयo = GSM_NET_TX_TIMEOUT;
	net->flags = IFF_POINTOPOINT | IFF_NOARP | IFF_MULTICAST;
	net->type = ARPHRD_NONE;
	net->tx_queue_len = 10;
पूर्ण


/* caller holds the dlci mutex */
अटल व्योम gsm_destroy_network(काष्ठा gsm_dlci *dlci)
अणु
	काष्ठा gsm_mux_net *mux_net;

	pr_debug("destroy network interface\n");
	अगर (!dlci->net)
		वापस;
	mux_net = netdev_priv(dlci->net);
	muxnet_put(mux_net);
पूर्ण


/* caller holds the dlci mutex */
अटल पूर्णांक gsm_create_network(काष्ठा gsm_dlci *dlci, काष्ठा gsm_netconfig *nc)
अणु
	अक्षर *netname;
	पूर्णांक retval = 0;
	काष्ठा net_device *net;
	काष्ठा gsm_mux_net *mux_net;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	/* Alपढ़ोy in a non tty mode */
	अगर (dlci->adaption > 2)
		वापस -EBUSY;

	अगर (nc->protocol != htons(ETH_P_IP))
		वापस -EPROTONOSUPPORT;

	अगर (nc->adaption != 3 && nc->adaption != 4)
		वापस -EPROTONOSUPPORT;

	pr_debug("create network interface\n");

	netname = "gsm%d";
	अगर (nc->अगर_name[0] != '\0')
		netname = nc->अगर_name;
	net = alloc_netdev(माप(काष्ठा gsm_mux_net), netname,
			   NET_NAME_UNKNOWN, gsm_mux_net_init);
	अगर (!net) अणु
		pr_err("alloc_netdev failed\n");
		वापस -ENOMEM;
	पूर्ण
	net->mtu = dlci->gsm->mtu;
	net->min_mtu = 8;
	net->max_mtu = dlci->gsm->mtu;
	mux_net = netdev_priv(net);
	mux_net->dlci = dlci;
	kref_init(&mux_net->ref);
	म_नकलन(nc->अगर_name, net->name, IFNAMSIZ); /* वापस net name */

	/* reconfigure dlci क्रम network */
	dlci->prev_adaption = dlci->adaption;
	dlci->prev_data = dlci->data;
	dlci->adaption = nc->adaption;
	dlci->data = gsm_mux_rx_netअक्षर;
	dlci->net = net;

	pr_debug("register netdev\n");
	retval = रेजिस्टर_netdev(net);
	अगर (retval) अणु
		pr_err("network register fail %d\n", retval);
		dlci_net_मुक्त(dlci);
		वापस retval;
	पूर्ण
	वापस net->अगरindex;	/* वापस network index */
पूर्ण

/* Line discipline क्रम real tty */
अटल काष्ठा tty_ldisc_ops tty_ldisc_packet = अणु
	.owner		 = THIS_MODULE,
	.name            = "n_gsm",
	.खोलो            = gsmld_खोलो,
	.बंद           = gsmld_बंद,
	.flush_buffer    = gsmld_flush_buffer,
	.पढ़ो            = gsmld_पढ़ो,
	.ग_लिखो           = gsmld_ग_लिखो,
	.ioctl           = gsmld_ioctl,
	.poll            = gsmld_poll,
	.receive_buf     = gsmld_receive_buf,
	.ग_लिखो_wakeup    = gsmld_ग_लिखो_wakeup
पूर्ण;

/*
 *	Virtual tty side
 */

#घोषणा TX_SIZE		512

अटल पूर्णांक gsmtty_modem_update(काष्ठा gsm_dlci *dlci, u8 brk)
अणु
	u8 modembits[5];
	काष्ठा gsm_control *ctrl;
	पूर्णांक len = 2;

	अगर (brk)
		len++;

	modembits[0] = len << 1 | EA;		/* Data bytes */
	modembits[1] = dlci->addr << 2 | 3;	/* DLCI, EA, 1 */
	modembits[2] = gsm_encode_modem(dlci) << 1 | EA;
	अगर (brk)
		modembits[3] = brk << 4 | 2 | EA;	/* Valid, EA */
	ctrl = gsm_control_send(dlci->gsm, CMD_MSC, modembits, len + 1);
	अगर (ctrl == शून्य)
		वापस -ENOMEM;
	वापस gsm_control_रुको(dlci->gsm, ctrl);
पूर्ण

अटल पूर्णांक gsm_carrier_उठाओd(काष्ठा tty_port *port)
अणु
	काष्ठा gsm_dlci *dlci = container_of(port, काष्ठा gsm_dlci, port);
	काष्ठा gsm_mux *gsm = dlci->gsm;

	/* Not yet खोलो so no carrier info */
	अगर (dlci->state != DLCI_OPEN)
		वापस 0;
	अगर (debug & 2)
		वापस 1;

	/*
	 * Basic mode with control channel in ADM mode may not respond
	 * to CMD_MSC at all and modem_rx is empty.
	 */
	अगर (gsm->encoding == 0 && gsm->dlci[0]->mode == DLCI_MODE_ADM &&
	    !dlci->modem_rx)
		वापस 1;

	वापस dlci->modem_rx & TIOCM_CD;
पूर्ण

अटल व्योम gsm_dtr_rts(काष्ठा tty_port *port, पूर्णांक onoff)
अणु
	काष्ठा gsm_dlci *dlci = container_of(port, काष्ठा gsm_dlci, port);
	अचिन्हित पूर्णांक modem_tx = dlci->modem_tx;
	अगर (onoff)
		modem_tx |= TIOCM_DTR | TIOCM_RTS;
	अन्यथा
		modem_tx &= ~(TIOCM_DTR | TIOCM_RTS);
	अगर (modem_tx != dlci->modem_tx) अणु
		dlci->modem_tx = modem_tx;
		gsmtty_modem_update(dlci, 0);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा tty_port_operations gsm_port_ops = अणु
	.carrier_उठाओd = gsm_carrier_उठाओd,
	.dtr_rts = gsm_dtr_rts,
	.deकाष्ठा = gsm_dlci_मुक्त,
पूर्ण;

अटल पूर्णांक gsmtty_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gsm_mux *gsm;
	काष्ठा gsm_dlci *dlci;
	अचिन्हित पूर्णांक line = tty->index;
	अचिन्हित पूर्णांक mux = mux_line_to_num(line);
	bool alloc = false;
	पूर्णांक ret;

	line = line & 0x3F;

	अगर (mux >= MAX_MUX)
		वापस -ENXIO;
	/* FIXME: we need to lock gsm_mux क्रम lअगरeबार of ttys eventually */
	अगर (gsm_mux[mux] == शून्य)
		वापस -EUNATCH;
	अगर (line == 0 || line > 61)	/* 62/63 reserved */
		वापस -ECHRNG;
	gsm = gsm_mux[mux];
	अगर (gsm->dead)
		वापस -EL2HLT;
	/* If DLCI 0 is not yet fully खोलो वापस an error.
	This is ok from a locking
	perspective as we करोn't have to worry about this
	अगर DLCI0 is lost */
	mutex_lock(&gsm->mutex);
	अगर (gsm->dlci[0] && gsm->dlci[0]->state != DLCI_OPEN) अणु
		mutex_unlock(&gsm->mutex);
		वापस -EL2NSYNC;
	पूर्ण
	dlci = gsm->dlci[line];
	अगर (dlci == शून्य) अणु
		alloc = true;
		dlci = gsm_dlci_alloc(gsm, line);
	पूर्ण
	अगर (dlci == शून्य) अणु
		mutex_unlock(&gsm->mutex);
		वापस -ENOMEM;
	पूर्ण
	ret = tty_port_install(&dlci->port, driver, tty);
	अगर (ret) अणु
		अगर (alloc)
			dlci_put(dlci);
		mutex_unlock(&gsm->mutex);
		वापस ret;
	पूर्ण

	dlci_get(dlci);
	dlci_get(gsm->dlci[0]);
	mux_get(gsm);
	tty->driver_data = dlci;
	mutex_unlock(&gsm->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक gsmtty_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा gsm_dlci *dlci = tty->driver_data;
	काष्ठा tty_port *port = &dlci->port;

	port->count++;
	tty_port_tty_set(port, tty);

	dlci->modem_rx = 0;
	/* We could in theory खोलो and बंद beक्रमe we रुको - eg अगर we get
	   a DM straight back. This is ok as that will have caused a hangup */
	tty_port_set_initialized(port, 1);
	/* Start sending off SABM messages */
	gsm_dlci_begin_खोलो(dlci);
	/* And रुको क्रम भव carrier */
	वापस tty_port_block_til_पढ़ोy(port, tty, filp);
पूर्ण

अटल व्योम gsmtty_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा gsm_dlci *dlci = tty->driver_data;

	अगर (dlci == शून्य)
		वापस;
	अगर (dlci->state == DLCI_CLOSED)
		वापस;
	mutex_lock(&dlci->mutex);
	gsm_destroy_network(dlci);
	mutex_unlock(&dlci->mutex);
	अगर (tty_port_बंद_start(&dlci->port, tty, filp) == 0)
		वापस;
	gsm_dlci_begin_बंद(dlci);
	अगर (tty_port_initialized(&dlci->port) && C_HUPCL(tty))
		tty_port_lower_dtr_rts(&dlci->port);
	tty_port_बंद_end(&dlci->port, tty);
	tty_port_tty_set(&dlci->port, शून्य);
	वापस;
पूर्ण

अटल व्योम gsmtty_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gsm_dlci *dlci = tty->driver_data;
	अगर (dlci->state == DLCI_CLOSED)
		वापस;
	tty_port_hangup(&dlci->port);
	gsm_dlci_begin_बंद(dlci);
पूर्ण

अटल पूर्णांक gsmtty_ग_लिखो(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buf,
								    पूर्णांक len)
अणु
	पूर्णांक sent;
	काष्ठा gsm_dlci *dlci = tty->driver_data;
	अगर (dlci->state == DLCI_CLOSED)
		वापस -EINVAL;
	/* Stuff the bytes पूर्णांकo the fअगरo queue */
	sent = kfअगरo_in_locked(&dlci->fअगरo, buf, len, &dlci->lock);
	/* Need to kick the channel */
	gsm_dlci_data_kick(dlci);
	वापस sent;
पूर्ण

अटल पूर्णांक gsmtty_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gsm_dlci *dlci = tty->driver_data;
	अगर (dlci->state == DLCI_CLOSED)
		वापस 0;
	वापस TX_SIZE - kfअगरo_len(&dlci->fअगरo);
पूर्ण

अटल पूर्णांक gsmtty_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gsm_dlci *dlci = tty->driver_data;
	अगर (dlci->state == DLCI_CLOSED)
		वापस 0;
	वापस kfअगरo_len(&dlci->fअगरo);
पूर्ण

अटल व्योम gsmtty_flush_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gsm_dlci *dlci = tty->driver_data;
	अगर (dlci->state == DLCI_CLOSED)
		वापस;
	/* Caution needed: If we implement reliable transport classes
	   then the data being transmitted can't simply be junked once
	   it has first hit the stack. Until then we can just blow it
	   away */
	kfअगरo_reset(&dlci->fअगरo);
	/* Need to unhook this DLCI from the transmit queue logic */
पूर्ण

अटल व्योम gsmtty_रुको_until_sent(काष्ठा tty_काष्ठा *tty, पूर्णांक समयout)
अणु
	/* The FIFO handles the queue so the kernel will करो the right
	   thing रुकोing on अक्षरs_in_buffer beक्रमe calling us. No work
	   to करो here */
पूर्ण

अटल पूर्णांक gsmtty_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gsm_dlci *dlci = tty->driver_data;
	अगर (dlci->state == DLCI_CLOSED)
		वापस -EINVAL;
	वापस dlci->modem_rx;
पूर्ण

अटल पूर्णांक gsmtty_tiocmset(काष्ठा tty_काष्ठा *tty,
	अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा gsm_dlci *dlci = tty->driver_data;
	अचिन्हित पूर्णांक modem_tx = dlci->modem_tx;

	अगर (dlci->state == DLCI_CLOSED)
		वापस -EINVAL;
	modem_tx &= ~clear;
	modem_tx |= set;

	अगर (modem_tx != dlci->modem_tx) अणु
		dlci->modem_tx = modem_tx;
		वापस gsmtty_modem_update(dlci, 0);
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक gsmtty_ioctl(काष्ठा tty_काष्ठा *tty,
			अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा gsm_dlci *dlci = tty->driver_data;
	काष्ठा gsm_netconfig nc;
	पूर्णांक index;

	अगर (dlci->state == DLCI_CLOSED)
		वापस -EINVAL;
	चयन (cmd) अणु
	हाल GSMIOC_ENABLE_NET:
		अगर (copy_from_user(&nc, (व्योम __user *)arg, माप(nc)))
			वापस -EFAULT;
		nc.अगर_name[IFNAMSIZ-1] = '\0';
		/* वापस net पूर्णांकerface index or error code */
		mutex_lock(&dlci->mutex);
		index = gsm_create_network(dlci, &nc);
		mutex_unlock(&dlci->mutex);
		अगर (copy_to_user((व्योम __user *)arg, &nc, माप(nc)))
			वापस -EFAULT;
		वापस index;
	हाल GSMIOC_DISABLE_NET:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		mutex_lock(&dlci->mutex);
		gsm_destroy_network(dlci);
		mutex_unlock(&dlci->mutex);
		वापस 0;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

अटल व्योम gsmtty_set_termios(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios *old)
अणु
	काष्ठा gsm_dlci *dlci = tty->driver_data;
	अगर (dlci->state == DLCI_CLOSED)
		वापस;
	/* For the moment its fixed. In actual fact the speed inक्रमmation
	   क्रम the भव channel can be propogated in both directions by
	   the RPN control message. This however rapidly माला_लो nasty as we
	   then have to remap modem संकेतs each way according to whether
	   our भव cable is null modem etc .. */
	tty_termios_copy_hw(&tty->termios, old);
पूर्ण

अटल व्योम gsmtty_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gsm_dlci *dlci = tty->driver_data;
	अगर (dlci->state == DLCI_CLOSED)
		वापस;
	अगर (C_CRTSCTS(tty))
		dlci->modem_tx &= ~TIOCM_DTR;
	dlci->throttled = true;
	/* Send an MSC with DTR cleared */
	gsmtty_modem_update(dlci, 0);
पूर्ण

अटल व्योम gsmtty_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gsm_dlci *dlci = tty->driver_data;
	अगर (dlci->state == DLCI_CLOSED)
		वापस;
	अगर (C_CRTSCTS(tty))
		dlci->modem_tx |= TIOCM_DTR;
	dlci->throttled = false;
	/* Send an MSC with DTR set */
	gsmtty_modem_update(dlci, 0);
पूर्ण

अटल पूर्णांक gsmtty_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक state)
अणु
	काष्ठा gsm_dlci *dlci = tty->driver_data;
	पूर्णांक encode = 0;	/* Off */
	अगर (dlci->state == DLCI_CLOSED)
		वापस -EINVAL;

	अगर (state == -1)	/* "On indefinitely" - we can't encode this
				    properly */
		encode = 0x0F;
	अन्यथा अगर (state > 0) अणु
		encode = state / 200;	/* mS to encoding */
		अगर (encode > 0x0F)
			encode = 0x0F;	/* Best efक्रमt */
	पूर्ण
	वापस gsmtty_modem_update(dlci, encode);
पूर्ण

अटल व्योम gsmtty_cleanup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gsm_dlci *dlci = tty->driver_data;
	काष्ठा gsm_mux *gsm = dlci->gsm;

	dlci_put(dlci);
	dlci_put(gsm->dlci[0]);
	mux_put(gsm);
पूर्ण

/* Virtual ttys क्रम the demux */
अटल स्थिर काष्ठा tty_operations gsmtty_ops = अणु
	.install		= gsmtty_install,
	.खोलो			= gsmtty_खोलो,
	.बंद			= gsmtty_बंद,
	.ग_लिखो			= gsmtty_ग_लिखो,
	.ग_लिखो_room		= gsmtty_ग_लिखो_room,
	.अक्षरs_in_buffer	= gsmtty_अक्षरs_in_buffer,
	.flush_buffer		= gsmtty_flush_buffer,
	.ioctl			= gsmtty_ioctl,
	.throttle		= gsmtty_throttle,
	.unthrottle		= gsmtty_unthrottle,
	.set_termios		= gsmtty_set_termios,
	.hangup			= gsmtty_hangup,
	.रुको_until_sent	= gsmtty_रुको_until_sent,
	.tiocmget		= gsmtty_tiocmget,
	.tiocmset		= gsmtty_tiocmset,
	.अवरोध_ctl		= gsmtty_अवरोध_ctl,
	.cleanup		= gsmtty_cleanup,
पूर्ण;



अटल पूर्णांक __init gsm_init(व्योम)
अणु
	/* Fill in our line protocol discipline, and रेजिस्टर it */
	पूर्णांक status = tty_रेजिस्टर_ldisc(N_GSM0710, &tty_ldisc_packet);
	अगर (status != 0) अणु
		pr_err("n_gsm: can't register line discipline (err = %d)\n",
								status);
		वापस status;
	पूर्ण

	gsm_tty_driver = alloc_tty_driver(256);
	अगर (!gsm_tty_driver) अणु
		tty_unरेजिस्टर_ldisc(N_GSM0710);
		pr_err("gsm_init: tty allocation failed.\n");
		वापस -EINVAL;
	पूर्ण
	gsm_tty_driver->driver_name	= "gsmtty";
	gsm_tty_driver->name		= "gsmtty";
	gsm_tty_driver->major		= 0;	/* Dynamic */
	gsm_tty_driver->minor_start	= 0;
	gsm_tty_driver->type		= TTY_DRIVER_TYPE_SERIAL;
	gsm_tty_driver->subtype	= SERIAL_TYPE_NORMAL;
	gsm_tty_driver->flags	= TTY_DRIVER_REAL_RAW | TTY_DRIVER_DYNAMIC_DEV
						| TTY_DRIVER_HARDWARE_BREAK;
	gsm_tty_driver->init_termios	= tty_std_termios;
	/* Fixme */
	gsm_tty_driver->init_termios.c_lflag &= ~ECHO;
	tty_set_operations(gsm_tty_driver, &gsmtty_ops);

	अगर (tty_रेजिस्टर_driver(gsm_tty_driver)) अणु
		put_tty_driver(gsm_tty_driver);
		tty_unरेजिस्टर_ldisc(N_GSM0710);
		pr_err("gsm_init: tty registration failed.\n");
		वापस -EBUSY;
	पूर्ण
	pr_debug("gsm_init: loaded as %d,%d.\n",
			gsm_tty_driver->major, gsm_tty_driver->minor_start);
	वापस 0;
पूर्ण

अटल व्योम __निकास gsm_निकास(व्योम)
अणु
	पूर्णांक status = tty_unरेजिस्टर_ldisc(N_GSM0710);
	अगर (status != 0)
		pr_err("n_gsm: can't unregister line discipline (err = %d)\n",
								status);
	tty_unरेजिस्टर_driver(gsm_tty_driver);
	put_tty_driver(gsm_tty_driver);
पूर्ण

module_init(gsm_init);
module_निकास(gsm_निकास);


MODULE_LICENSE("GPL");
MODULE_ALIAS_LDISC(N_GSM0710);
