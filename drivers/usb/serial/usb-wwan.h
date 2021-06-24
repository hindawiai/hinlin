<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Definitions क्रम USB serial mobile broadband cards
 */

#अगर_अघोषित __LINUX_USB_USB_WWAN
#घोषणा __LINUX_USB_USB_WWAN

बाह्य व्योम usb_wwan_dtr_rts(काष्ठा usb_serial_port *port, पूर्णांक on);
बाह्य पूर्णांक usb_wwan_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port);
बाह्य व्योम usb_wwan_बंद(काष्ठा usb_serial_port *port);
बाह्य पूर्णांक usb_wwan_port_probe(काष्ठा usb_serial_port *port);
बाह्य व्योम usb_wwan_port_हटाओ(काष्ठा usb_serial_port *port);
बाह्य पूर्णांक usb_wwan_ग_लिखो_room(काष्ठा tty_काष्ठा *tty);
बाह्य पूर्णांक usb_wwan_tiocmget(काष्ठा tty_काष्ठा *tty);
बाह्य पूर्णांक usb_wwan_tiocmset(काष्ठा tty_काष्ठा *tty,
			     अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear);
बाह्य पूर्णांक usb_wwan_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा usb_serial_port *port,
			  स्थिर अचिन्हित अक्षर *buf, पूर्णांक count);
बाह्य पूर्णांक usb_wwan_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty);
#अगर_घोषित CONFIG_PM
बाह्य पूर्णांक usb_wwan_suspend(काष्ठा usb_serial *serial, pm_message_t message);
बाह्य पूर्णांक usb_wwan_resume(काष्ठा usb_serial *serial);
#पूर्ण_अगर

/* per port निजी data */

#घोषणा N_IN_URB 4
#घोषणा N_OUT_URB 4
#घोषणा IN_BUFLEN 4096
#घोषणा OUT_BUFLEN 4096

काष्ठा usb_wwan_पूर्णांकf_निजी अणु
	spinlock_t susp_lock;
	अचिन्हित पूर्णांक suspended:1;
	अचिन्हित पूर्णांक use_send_setup:1;
	अचिन्हित पूर्णांक use_zlp:1;
	पूर्णांक in_flight;
	अचिन्हित पूर्णांक खोलो_ports;
	व्योम *निजी;
पूर्ण;

काष्ठा usb_wwan_port_निजी अणु
	/* Input endpoपूर्णांकs and buffer क्रम this port */
	काष्ठा urb *in_urbs[N_IN_URB];
	u8 *in_buffer[N_IN_URB];
	/* Output endpoपूर्णांकs and buffer क्रम this port */
	काष्ठा urb *out_urbs[N_OUT_URB];
	u8 *out_buffer[N_OUT_URB];
	अचिन्हित दीर्घ out_busy;	/* Bit vector of URBs in use */
	काष्ठा usb_anchor delayed;

	/* Settings क्रम the port */
	पूर्णांक rts_state;		/* Handshaking pins (outमाला_दो) */
	पूर्णांक dtr_state;
	पूर्णांक cts_state;		/* Handshaking pins (inमाला_दो) */
	पूर्णांक dsr_state;
	पूर्णांक dcd_state;
	पूर्णांक ri_state;

	अचिन्हित दीर्घ tx_start_समय[N_OUT_URB];
पूर्ण;

#पूर्ण_अगर /* __LINUX_USB_USB_WWAN */
