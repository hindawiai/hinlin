<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *
 * Includes क्रम cdc-acm.c
 *
 * Mainly take from usbnet's cdc-ether part
 *
 */

/*
 * CMSPAR, some architectures can't have space and mark parity.
 */

#अगर_अघोषित CMSPAR
#घोषणा CMSPAR			0
#पूर्ण_अगर

/*
 * Major and minor numbers.
 */

#घोषणा ACM_TTY_MAJOR		166
#घोषणा ACM_TTY_MINORS		256

/*
 * Requests.
 */

#घोषणा USB_RT_ACM		(USB_TYPE_CLASS | USB_RECIP_INTERFACE)

/*
 * Output control lines.
 */

#घोषणा ACM_CTRL_DTR		0x01
#घोषणा ACM_CTRL_RTS		0x02

/*
 * Input control lines and line errors.
 */

#घोषणा ACM_CTRL_DCD		0x01
#घोषणा ACM_CTRL_DSR		0x02
#घोषणा ACM_CTRL_BRK		0x04
#घोषणा ACM_CTRL_RI		0x08

#घोषणा ACM_CTRL_FRAMING	0x10
#घोषणा ACM_CTRL_PARITY		0x20
#घोषणा ACM_CTRL_OVERRUN	0x40

/*
 * Internal driver काष्ठाures.
 */

/*
 * The only reason to have several buffers is to accommodate assumptions
 * in line disciplines. They ask क्रम empty space amount, receive our URB size,
 * and proceed to issue several 1-अक्षरacter ग_लिखोs, assuming they will fit.
 * The very first ग_लिखो takes a complete URB. Fortunately, this only happens
 * when processing onlcr, so we only need 2 buffers. These values must be
 * घातers of 2.
 */
#घोषणा ACM_NW  16
#घोषणा ACM_NR  16

काष्ठा acm_wb अणु
	u8 *buf;
	dma_addr_t dmah;
	अचिन्हित पूर्णांक len;
	काष्ठा urb		*urb;
	काष्ठा acm		*instance;
	bool use;
पूर्ण;

काष्ठा acm_rb अणु
	पूर्णांक			size;
	अचिन्हित अक्षर		*base;
	dma_addr_t		dma;
	पूर्णांक			index;
	काष्ठा acm		*instance;
पूर्ण;

काष्ठा acm अणु
	काष्ठा usb_device *dev;				/* the corresponding usb device */
	काष्ठा usb_पूर्णांकerface *control;			/* control पूर्णांकerface */
	काष्ठा usb_पूर्णांकerface *data;			/* data पूर्णांकerface */
	अचिन्हित in, out;				/* i/o pipes */
	काष्ठा tty_port port;			 	/* our tty port data */
	काष्ठा urb *ctrlurb;				/* urbs */
	u8 *ctrl_buffer;				/* buffers of urbs */
	dma_addr_t ctrl_dma;				/* dma handles of buffers */
	u8 *country_codes;				/* country codes from device */
	अचिन्हित पूर्णांक country_code_size;			/* size of this buffer */
	अचिन्हित पूर्णांक country_rel_date;			/* release date of version */
	काष्ठा acm_wb wb[ACM_NW];
	अचिन्हित दीर्घ पढ़ो_urbs_मुक्त;
	काष्ठा urb *पढ़ो_urbs[ACM_NR];
	काष्ठा acm_rb पढ़ो_buffers[ACM_NR];
	पूर्णांक rx_buflimit;
	spinlock_t पढ़ो_lock;
	u8 *notअगरication_buffer;			/* to reassemble fragmented notअगरications */
	अचिन्हित पूर्णांक nb_index;
	अचिन्हित पूर्णांक nb_size;
	पूर्णांक transmitting;
	spinlock_t ग_लिखो_lock;
	काष्ठा mutex mutex;
	bool disconnected;
	अचिन्हित दीर्घ flags;
#		define EVENT_TTY_WAKEUP	0
#		define EVENT_RX_STALL	1
#		define ACM_THROTTLED	2
#		define ACM_ERROR_DELAY	3
	अचिन्हित दीर्घ urbs_in_error_delay;		/* these need to be restarted after a delay */
	काष्ठा usb_cdc_line_coding line;		/* bits, stop, parity */
	काष्ठा delayed_work dwork;		        /* work queue entry क्रम various purposes */
	अचिन्हित पूर्णांक ctrlin;				/* input control lines (DCD, DSR, RI, अवरोध, overruns) */
	अचिन्हित पूर्णांक ctrlout;				/* output control lines (DTR, RTS) */
	काष्ठा async_icount iocount;			/* counters क्रम control line changes */
	काष्ठा async_icount oldcount;			/* क्रम comparison of counter */
	रुको_queue_head_t wioctl;			/* क्रम ioctl */
	अचिन्हित पूर्णांक ग_लिखोsize;				/* max packet size क्रम the output bulk endpoपूर्णांक */
	अचिन्हित पूर्णांक पढ़ोsize,ctrlsize;			/* buffer sizes क्रम मुक्तing */
	अचिन्हित पूर्णांक minor;				/* acm minor number */
	अचिन्हित अक्षर clocal;				/* termios CLOCAL */
	अचिन्हित पूर्णांक ctrl_caps;				/* control capabilities from the class specअगरic header */
	अचिन्हित पूर्णांक susp_count;			/* number of suspended पूर्णांकerfaces */
	अचिन्हित पूर्णांक combined_पूर्णांकerfaces:1;		/* control and data collapsed */
	u8 bInterval;
	काष्ठा usb_anchor delayed;			/* ग_लिखोs queued क्रम a device about to be woken */
	अचिन्हित दीर्घ quirks;
पूर्ण;

/* स्थिरants describing various quirks and errors */
#घोषणा NO_UNION_NORMAL			BIT(0)
#घोषणा SINGLE_RX_URB			BIT(1)
#घोषणा NO_CAP_LINE			BIT(2)
#घोषणा IGNORE_DEVICE			BIT(3)
#घोषणा QUIRK_CONTROL_LINE_STATE	BIT(4)
#घोषणा CLEAR_HALT_CONDITIONS		BIT(5)
#घोषणा SEND_ZERO_PACKET		BIT(6)
#घोषणा DISABLE_ECHO			BIT(7)
