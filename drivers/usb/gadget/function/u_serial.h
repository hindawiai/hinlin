<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * u_serial.h - पूर्णांकerface to USB gadget "serial port"/TTY utilities
 *
 * Copyright (C) 2008 David Brownell
 * Copyright (C) 2008 by Nokia Corporation
 */

#अगर_अघोषित __U_SERIAL_H
#घोषणा __U_SERIAL_H

#समावेश <linux/usb/composite.h>
#समावेश <linux/usb/cdc.h>

#घोषणा MAX_U_SERIAL_PORTS	8

काष्ठा f_serial_opts अणु
	काष्ठा usb_function_instance func_inst;
	u8 port_num;
पूर्ण;

/*
 * One non-multiplexed "serial" I/O port ... there can be several of these
 * on any given USB peripheral device, अगर it provides enough endpoपूर्णांकs.
 *
 * The "u_serial" utility component exists to करो one thing:  manage TTY
 * style I/O using the USB peripheral endpoपूर्णांकs listed here, including
 * hookups to sysfs and /dev क्रम each logical "tty" device.
 *
 * REVISIT at least ACM could support tiocmget() अगर needed.
 *
 * REVISIT someday, allow multiplexing several TTYs over these endpoपूर्णांकs.
 */
काष्ठा gserial अणु
	काष्ठा usb_function		func;

	/* port is managed by gserial_अणुconnect,disconnectपूर्ण */
	काष्ठा gs_port			*ioport;

	काष्ठा usb_ep			*in;
	काष्ठा usb_ep			*out;

	/* REVISIT aव्योम this CDC-ACM support harder ... */
	काष्ठा usb_cdc_line_coding port_line_coding;	/* 9600-8-N-1 etc */

	/* notअगरication callbacks */
	व्योम (*connect)(काष्ठा gserial *p);
	व्योम (*disconnect)(काष्ठा gserial *p);
	पूर्णांक (*send_अवरोध)(काष्ठा gserial *p, पूर्णांक duration);
पूर्ण;

/* utilities to allocate/मुक्त request and buffer */
काष्ठा usb_request *gs_alloc_req(काष्ठा usb_ep *ep, अचिन्हित len, gfp_t flags);
व्योम gs_मुक्त_req(काष्ठा usb_ep *, काष्ठा usb_request *req);

/* management of inभागidual TTY ports */
पूर्णांक gserial_alloc_line_no_console(अचिन्हित अक्षर *port_line);
पूर्णांक gserial_alloc_line(अचिन्हित अक्षर *port_line);
व्योम gserial_मुक्त_line(अचिन्हित अक्षर port_line);

#अगर_घोषित CONFIG_U_SERIAL_CONSOLE

sमाप_प्रकार gserial_set_console(अचिन्हित अक्षर port_num, स्थिर अक्षर *page, माप_प्रकार count);
sमाप_प्रकार gserial_get_console(अचिन्हित अक्षर port_num, अक्षर *page);

#पूर्ण_अगर /* CONFIG_U_SERIAL_CONSOLE */

/* connect/disconnect is handled by inभागidual functions */
पूर्णांक gserial_connect(काष्ठा gserial *, u8 port_num);
व्योम gserial_disconnect(काष्ठा gserial *);
व्योम gserial_suspend(काष्ठा gserial *p);
व्योम gserial_resume(काष्ठा gserial *p);

/* functions are bound to configurations by a config or gadget driver */
पूर्णांक gser_bind_config(काष्ठा usb_configuration *c, u8 port_num);
पूर्णांक obex_bind_config(काष्ठा usb_configuration *c, u8 port_num);

#पूर्ण_अगर /* __U_SERIAL_H */
