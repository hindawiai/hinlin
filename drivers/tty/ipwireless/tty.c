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

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/ppp_defs.h>
#समावेश <linux/अगर.h>
#समावेश <linux/ppp-ioctl.h>
#समावेश <linux/sched.h>
#समावेश <linux/serial.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/uaccess.h>

#समावेश "tty.h"
#समावेश "network.h"
#समावेश "hardware.h"
#समावेश "main.h"

#घोषणा IPWIRELESS_PCMCIA_START 	(0)
#घोषणा IPWIRELESS_PCMCIA_MINORS	(24)
#घोषणा IPWIRELESS_PCMCIA_MINOR_RANGE	(8)

#घोषणा TTYTYPE_MODEM    (0)
#घोषणा TTYTYPE_MONITOR  (1)
#घोषणा TTYTYPE_RAS_RAW  (2)

काष्ठा ipw_tty अणु
	काष्ठा tty_port port;
	पूर्णांक index;
	काष्ठा ipw_hardware *hardware;
	अचिन्हित पूर्णांक channel_idx;
	अचिन्हित पूर्णांक secondary_channel_idx;
	पूर्णांक tty_type;
	काष्ठा ipw_network *network;
	अचिन्हित पूर्णांक control_lines;
	काष्ठा mutex ipw_tty_mutex;
	पूर्णांक tx_bytes_queued;
	पूर्णांक closing;
पूर्ण;

अटल काष्ठा ipw_tty *ttys[IPWIRELESS_PCMCIA_MINORS];

अटल काष्ठा tty_driver *ipw_tty_driver;

अटल अक्षर *tty_type_name(पूर्णांक tty_type)
अणु
	अटल अक्षर *channel_names[] = अणु
		"modem",
		"monitor",
		"RAS-raw"
	पूर्ण;

	वापस channel_names[tty_type];
पूर्ण

अटल काष्ठा ipw_tty *get_tty(पूर्णांक index)
अणु
	/*
	 * The 'ras_raw' channel is only available when 'loopback' mode
	 * is enabled.
	 * Number of minor starts with 16 (_RANGE * _RAS_RAW).
	 */
	अगर (!ipwireless_loopback && index >=
			 IPWIRELESS_PCMCIA_MINOR_RANGE * TTYTYPE_RAS_RAW)
		वापस शून्य;

	वापस ttys[index];
पूर्ण

अटल पूर्णांक ipw_खोलो(काष्ठा tty_काष्ठा *linux_tty, काष्ठा file *filp)
अणु
	काष्ठा ipw_tty *tty = get_tty(linux_tty->index);

	अगर (!tty)
		वापस -ENODEV;

	mutex_lock(&tty->ipw_tty_mutex);
	अगर (tty->port.count == 0)
		tty->tx_bytes_queued = 0;

	tty->port.count++;

	tty->port.tty = linux_tty;
	linux_tty->driver_data = tty;

	अगर (tty->tty_type == TTYTYPE_MODEM)
		ipwireless_ppp_खोलो(tty->network);

	mutex_unlock(&tty->ipw_tty_mutex);

	वापस 0;
पूर्ण

अटल व्योम करो_ipw_बंद(काष्ठा ipw_tty *tty)
अणु
	tty->port.count--;

	अगर (tty->port.count == 0) अणु
		काष्ठा tty_काष्ठा *linux_tty = tty->port.tty;

		अगर (linux_tty != शून्य) अणु
			tty->port.tty = शून्य;
			linux_tty->driver_data = शून्य;

			अगर (tty->tty_type == TTYTYPE_MODEM)
				ipwireless_ppp_बंद(tty->network);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ipw_hangup(काष्ठा tty_काष्ठा *linux_tty)
अणु
	काष्ठा ipw_tty *tty = linux_tty->driver_data;

	अगर (!tty)
		वापस;

	mutex_lock(&tty->ipw_tty_mutex);
	अगर (tty->port.count == 0) अणु
		mutex_unlock(&tty->ipw_tty_mutex);
		वापस;
	पूर्ण

	करो_ipw_बंद(tty);

	mutex_unlock(&tty->ipw_tty_mutex);
पूर्ण

अटल व्योम ipw_बंद(काष्ठा tty_काष्ठा *linux_tty, काष्ठा file *filp)
अणु
	ipw_hangup(linux_tty);
पूर्ण

/* Take data received from hardware, and send it out the tty */
व्योम ipwireless_tty_received(काष्ठा ipw_tty *tty, अचिन्हित अक्षर *data,
			अचिन्हित पूर्णांक length)
अणु
	पूर्णांक work = 0;

	mutex_lock(&tty->ipw_tty_mutex);

	अगर (!tty->port.count) अणु
		mutex_unlock(&tty->ipw_tty_mutex);
		वापस;
	पूर्ण
	mutex_unlock(&tty->ipw_tty_mutex);

	work = tty_insert_flip_string(&tty->port, data, length);

	अगर (work != length)
		prपूर्णांकk(KERN_DEBUG IPWIRELESS_PCCARD_NAME
				": %d chars not inserted to flip buffer!\n",
				length - work);

	अगर (work)
		tty_flip_buffer_push(&tty->port);
पूर्ण

अटल व्योम ipw_ग_लिखो_packet_sent_callback(व्योम *callback_data,
					   अचिन्हित पूर्णांक packet_length)
अणु
	काष्ठा ipw_tty *tty = callback_data;

	/*
	 * Packet has been sent, so we subtract the number of bytes from our
	 * tally of outstanding TX bytes.
	 */
	tty->tx_bytes_queued -= packet_length;
पूर्ण

अटल पूर्णांक ipw_ग_लिखो(काष्ठा tty_काष्ठा *linux_tty,
		     स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा ipw_tty *tty = linux_tty->driver_data;
	पूर्णांक room, ret;

	अगर (!tty)
		वापस -ENODEV;

	mutex_lock(&tty->ipw_tty_mutex);
	अगर (!tty->port.count) अणु
		mutex_unlock(&tty->ipw_tty_mutex);
		वापस -EINVAL;
	पूर्ण

	room = IPWIRELESS_TX_QUEUE_SIZE - tty->tx_bytes_queued;
	अगर (room < 0)
		room = 0;
	/* Don't allow caller to ग_लिखो any more than we have room क्रम */
	अगर (count > room)
		count = room;

	अगर (count == 0) अणु
		mutex_unlock(&tty->ipw_tty_mutex);
		वापस 0;
	पूर्ण

	ret = ipwireless_send_packet(tty->hardware, IPW_CHANNEL_RAS,
			       buf, count,
			       ipw_ग_लिखो_packet_sent_callback, tty);
	अगर (ret < 0) अणु
		mutex_unlock(&tty->ipw_tty_mutex);
		वापस 0;
	पूर्ण

	tty->tx_bytes_queued += count;
	mutex_unlock(&tty->ipw_tty_mutex);

	वापस count;
पूर्ण

अटल पूर्णांक ipw_ग_लिखो_room(काष्ठा tty_काष्ठा *linux_tty)
अणु
	काष्ठा ipw_tty *tty = linux_tty->driver_data;
	पूर्णांक room;

	/* FIXME: Exactly how is the tty object locked here .. */
	अगर (!tty)
		वापस 0;

	अगर (!tty->port.count)
		वापस 0;

	room = IPWIRELESS_TX_QUEUE_SIZE - tty->tx_bytes_queued;
	अगर (room < 0)
		room = 0;

	वापस room;
पूर्ण

अटल पूर्णांक ipwireless_get_serial_info(काष्ठा tty_काष्ठा *linux_tty,
				      काष्ठा serial_काष्ठा *ss)
अणु
	काष्ठा ipw_tty *tty = linux_tty->driver_data;

	अगर (!tty)
		वापस -ENODEV;

	अगर (!tty->port.count)
		वापस -EINVAL;

	ss->type = PORT_UNKNOWN;
	ss->line = tty->index;
	ss->baud_base = 115200;
	वापस 0;
पूर्ण

अटल पूर्णांक ipwireless_set_serial_info(काष्ठा tty_काष्ठा *linux_tty,
				      काष्ठा serial_काष्ठा *ss)
अणु
	वापस 0;	/* Keeps the PCMCIA scripts happy. */
पूर्ण

अटल पूर्णांक ipw_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *linux_tty)
अणु
	काष्ठा ipw_tty *tty = linux_tty->driver_data;

	अगर (!tty)
		वापस 0;

	अगर (!tty->port.count)
		वापस 0;

	वापस tty->tx_bytes_queued;
पूर्ण

अटल पूर्णांक get_control_lines(काष्ठा ipw_tty *tty)
अणु
	अचिन्हित पूर्णांक my = tty->control_lines;
	अचिन्हित पूर्णांक out = 0;

	अगर (my & IPW_CONTROL_LINE_RTS)
		out |= TIOCM_RTS;
	अगर (my & IPW_CONTROL_LINE_DTR)
		out |= TIOCM_DTR;
	अगर (my & IPW_CONTROL_LINE_CTS)
		out |= TIOCM_CTS;
	अगर (my & IPW_CONTROL_LINE_DSR)
		out |= TIOCM_DSR;
	अगर (my & IPW_CONTROL_LINE_DCD)
		out |= TIOCM_CD;

	वापस out;
पूर्ण

अटल पूर्णांक set_control_lines(काष्ठा ipw_tty *tty, अचिन्हित पूर्णांक set,
			     अचिन्हित पूर्णांक clear)
अणु
	पूर्णांक ret;

	अगर (set & TIOCM_RTS) अणु
		ret = ipwireless_set_RTS(tty->hardware, tty->channel_idx, 1);
		अगर (ret)
			वापस ret;
		अगर (tty->secondary_channel_idx != -1) अणु
			ret = ipwireless_set_RTS(tty->hardware,
					  tty->secondary_channel_idx, 1);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण
	अगर (set & TIOCM_DTR) अणु
		ret = ipwireless_set_DTR(tty->hardware, tty->channel_idx, 1);
		अगर (ret)
			वापस ret;
		अगर (tty->secondary_channel_idx != -1) अणु
			ret = ipwireless_set_DTR(tty->hardware,
					  tty->secondary_channel_idx, 1);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण
	अगर (clear & TIOCM_RTS) अणु
		ret = ipwireless_set_RTS(tty->hardware, tty->channel_idx, 0);
		अगर (tty->secondary_channel_idx != -1) अणु
			ret = ipwireless_set_RTS(tty->hardware,
					  tty->secondary_channel_idx, 0);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण
	अगर (clear & TIOCM_DTR) अणु
		ret = ipwireless_set_DTR(tty->hardware, tty->channel_idx, 0);
		अगर (tty->secondary_channel_idx != -1) अणु
			ret = ipwireless_set_DTR(tty->hardware,
					  tty->secondary_channel_idx, 0);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ipw_tiocmget(काष्ठा tty_काष्ठा *linux_tty)
अणु
	काष्ठा ipw_tty *tty = linux_tty->driver_data;
	/* FIXME: Exactly how is the tty object locked here .. */

	अगर (!tty)
		वापस -ENODEV;

	अगर (!tty->port.count)
		वापस -EINVAL;

	वापस get_control_lines(tty);
पूर्ण

अटल पूर्णांक
ipw_tiocmset(काष्ठा tty_काष्ठा *linux_tty,
	     अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा ipw_tty *tty = linux_tty->driver_data;
	/* FIXME: Exactly how is the tty object locked here .. */

	अगर (!tty)
		वापस -ENODEV;

	अगर (!tty->port.count)
		वापस -EINVAL;

	वापस set_control_lines(tty, set, clear);
पूर्ण

अटल पूर्णांक ipw_ioctl(काष्ठा tty_काष्ठा *linux_tty,
		     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ipw_tty *tty = linux_tty->driver_data;

	अगर (!tty)
		वापस -ENODEV;

	अगर (!tty->port.count)
		वापस -EINVAL;

	/* FIXME: Exactly how is the tty object locked here .. */
	अगर (tty->tty_type == TTYTYPE_MODEM) अणु
		चयन (cmd) अणु
		हाल PPPIOCGCHAN:
			अणु
				पूर्णांक chan = ipwireless_ppp_channel_index(
							tty->network);

				अगर (chan < 0)
					वापस -ENODEV;
				अगर (put_user(chan, (पूर्णांक __user *) arg))
					वापस -EFAULT;
			पूर्ण
			वापस 0;

		हाल PPPIOCGUNIT:
			अणु
				पूर्णांक unit = ipwireless_ppp_unit_number(
						tty->network);

				अगर (unit < 0)
					वापस -ENODEV;
				अगर (put_user(unit, (पूर्णांक __user *) arg))
					वापस -EFAULT;
			पूर्ण
			वापस 0;

		हाल FIONREAD:
			अणु
				पूर्णांक val = 0;

				अगर (put_user(val, (पूर्णांक __user *) arg))
					वापस -EFAULT;
			पूर्ण
			वापस 0;
		हाल TCFLSH:
			वापस tty_perक्रमm_flush(linux_tty, arg);
		पूर्ण
	पूर्ण
	वापस -ENOIOCTLCMD;
पूर्ण

अटल पूर्णांक add_tty(पूर्णांक j,
		    काष्ठा ipw_hardware *hardware,
		    काष्ठा ipw_network *network, पूर्णांक channel_idx,
		    पूर्णांक secondary_channel_idx, पूर्णांक tty_type)
अणु
	ttys[j] = kzalloc(माप(काष्ठा ipw_tty), GFP_KERNEL);
	अगर (!ttys[j])
		वापस -ENOMEM;
	ttys[j]->index = j;
	ttys[j]->hardware = hardware;
	ttys[j]->channel_idx = channel_idx;
	ttys[j]->secondary_channel_idx = secondary_channel_idx;
	ttys[j]->network = network;
	ttys[j]->tty_type = tty_type;
	mutex_init(&ttys[j]->ipw_tty_mutex);
	tty_port_init(&ttys[j]->port);

	tty_port_रेजिस्टर_device(&ttys[j]->port, ipw_tty_driver, j, शून्य);
	ipwireless_associate_network_tty(network, channel_idx, ttys[j]);

	अगर (secondary_channel_idx != -1)
		ipwireless_associate_network_tty(network,
						 secondary_channel_idx,
						 ttys[j]);
	/* check अगर we provide raw device (अगर loopback is enabled) */
	अगर (get_tty(j))
		prपूर्णांकk(KERN_INFO IPWIRELESS_PCCARD_NAME
		       ": registering %s device ttyIPWp%d\n",
		       tty_type_name(tty_type), j);

	वापस 0;
पूर्ण

काष्ठा ipw_tty *ipwireless_tty_create(काष्ठा ipw_hardware *hardware,
				      काष्ठा ipw_network *network)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < IPWIRELESS_PCMCIA_MINOR_RANGE; i++) अणु
		पूर्णांक allमुक्त = 1;

		क्रम (j = i; j < IPWIRELESS_PCMCIA_MINORS;
				j += IPWIRELESS_PCMCIA_MINOR_RANGE)
			अगर (ttys[j] != शून्य) अणु
				allमुक्त = 0;
				अवरोध;
			पूर्ण

		अगर (allमुक्त) अणु
			j = i;

			अगर (add_tty(j, hardware, network,
					IPW_CHANNEL_DIALLER, IPW_CHANNEL_RAS,
					TTYTYPE_MODEM))
				वापस शून्य;

			j += IPWIRELESS_PCMCIA_MINOR_RANGE;
			अगर (add_tty(j, hardware, network,
					IPW_CHANNEL_DIALLER, -1,
					TTYTYPE_MONITOR))
				वापस शून्य;

			j += IPWIRELESS_PCMCIA_MINOR_RANGE;
			अगर (add_tty(j, hardware, network,
					IPW_CHANNEL_RAS, -1,
					TTYTYPE_RAS_RAW))
				वापस शून्य;

			वापस ttys[i];
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Must be called beक्रमe ipwireless_network_मुक्त().
 */
व्योम ipwireless_tty_मुक्त(काष्ठा ipw_tty *tty)
अणु
	पूर्णांक j;
	काष्ठा ipw_network *network = ttys[tty->index]->network;

	क्रम (j = tty->index; j < IPWIRELESS_PCMCIA_MINORS;
			j += IPWIRELESS_PCMCIA_MINOR_RANGE) अणु
		काष्ठा ipw_tty *ttyj = ttys[j];

		अगर (ttyj) अणु
			mutex_lock(&ttyj->ipw_tty_mutex);
			अगर (get_tty(j))
				prपूर्णांकk(KERN_INFO IPWIRELESS_PCCARD_NAME
				       ": deregistering %s device ttyIPWp%d\n",
				       tty_type_name(ttyj->tty_type), j);
			ttyj->closing = 1;
			अगर (ttyj->port.tty != शून्य) अणु
				mutex_unlock(&ttyj->ipw_tty_mutex);
				tty_vhangup(ttyj->port.tty);
				/* FIXME: Exactly how is the tty object locked here
				   against a parallel ioctl etc */
				/* FIXME2: hangup करोes not mean all processes
				 * are gone */
				mutex_lock(&ttyj->ipw_tty_mutex);
			पूर्ण
			जबतक (ttyj->port.count)
				करो_ipw_बंद(ttyj);
			ipwireless_disassociate_network_ttys(network,
							     ttyj->channel_idx);
			tty_unरेजिस्टर_device(ipw_tty_driver, j);
			tty_port_destroy(&ttyj->port);
			ttys[j] = शून्य;
			mutex_unlock(&ttyj->ipw_tty_mutex);
			kमुक्त(ttyj);
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा tty_operations tty_ops = अणु
	.खोलो = ipw_खोलो,
	.बंद = ipw_बंद,
	.hangup = ipw_hangup,
	.ग_लिखो = ipw_ग_लिखो,
	.ग_लिखो_room = ipw_ग_लिखो_room,
	.ioctl = ipw_ioctl,
	.अक्षरs_in_buffer = ipw_अक्षरs_in_buffer,
	.tiocmget = ipw_tiocmget,
	.tiocmset = ipw_tiocmset,
	.set_serial = ipwireless_set_serial_info,
	.get_serial = ipwireless_get_serial_info,
पूर्ण;

पूर्णांक ipwireless_tty_init(व्योम)
अणु
	पूर्णांक result;

	ipw_tty_driver = alloc_tty_driver(IPWIRELESS_PCMCIA_MINORS);
	अगर (!ipw_tty_driver)
		वापस -ENOMEM;

	ipw_tty_driver->driver_name = IPWIRELESS_PCCARD_NAME;
	ipw_tty_driver->name = "ttyIPWp";
	ipw_tty_driver->major = 0;
	ipw_tty_driver->minor_start = IPWIRELESS_PCMCIA_START;
	ipw_tty_driver->type = TTY_DRIVER_TYPE_SERIAL;
	ipw_tty_driver->subtype = SERIAL_TYPE_NORMAL;
	ipw_tty_driver->flags = TTY_DRIVER_REAL_RAW | TTY_DRIVER_DYNAMIC_DEV;
	ipw_tty_driver->init_termios = tty_std_termios;
	ipw_tty_driver->init_termios.c_cflag =
	    B9600 | CS8 | CREAD | HUPCL | CLOCAL;
	ipw_tty_driver->init_termios.c_ispeed = 9600;
	ipw_tty_driver->init_termios.c_ospeed = 9600;
	tty_set_operations(ipw_tty_driver, &tty_ops);
	result = tty_रेजिस्टर_driver(ipw_tty_driver);
	अगर (result) अणु
		prपूर्णांकk(KERN_ERR IPWIRELESS_PCCARD_NAME
		       ": failed to register tty driver\n");
		put_tty_driver(ipw_tty_driver);
		वापस result;
	पूर्ण

	वापस 0;
पूर्ण

व्योम ipwireless_tty_release(व्योम)
अणु
	tty_unरेजिस्टर_driver(ipw_tty_driver);
	put_tty_driver(ipw_tty_driver);
पूर्ण

पूर्णांक ipwireless_tty_is_modem(काष्ठा ipw_tty *tty)
अणु
	वापस tty->tty_type == TTYTYPE_MODEM;
पूर्ण

व्योम
ipwireless_tty_notअगरy_control_line_change(काष्ठा ipw_tty *tty,
					  अचिन्हित पूर्णांक channel_idx,
					  अचिन्हित पूर्णांक control_lines,
					  अचिन्हित पूर्णांक changed_mask)
अणु
	अचिन्हित पूर्णांक old_control_lines = tty->control_lines;

	tty->control_lines = (tty->control_lines & ~changed_mask)
		| (control_lines & changed_mask);

	/*
	 * If DCD is de-निश्चितed, we बंद the tty so pppd can tell that we
	 * have gone offline.
	 */
	अगर ((old_control_lines & IPW_CONTROL_LINE_DCD)
			&& !(tty->control_lines & IPW_CONTROL_LINE_DCD)
			&& tty->port.tty) अणु
		tty_hangup(tty->port.tty);
	पूर्ण
पूर्ण

