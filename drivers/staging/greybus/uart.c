<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * UART driver क्रम the Greybus "generic" UART module.
 *
 * Copyright 2014 Google Inc.
 * Copyright 2014 Linaro Ltd.
 *
 * Heavily based on drivers/usb/class/cdc-acm.c and
 * drivers/usb/serial/usb-serial.c.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mutex.h>
#समावेश <linux/tty.h>
#समावेश <linux/serial.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/idr.h>
#समावेश <linux/fs.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/completion.h>
#समावेश <linux/greybus.h>

#समावेश "gbphy.h"

#घोषणा GB_NUM_MINORS	16	/* 16 is more than enough */
#घोषणा GB_NAME		"ttyGB"

#घोषणा GB_UART_WRITE_FIFO_SIZE		PAGE_SIZE
#घोषणा GB_UART_WRITE_ROOM_MARGIN	1	/* leave some space in fअगरo */
#घोषणा GB_UART_FIRMWARE_CREDITS	4096
#घोषणा GB_UART_CREDIT_WAIT_TIMEOUT_MSEC	10000

काष्ठा gb_tty अणु
	काष्ठा gbphy_device *gbphy_dev;
	काष्ठा tty_port port;
	व्योम *buffer;
	माप_प्रकार buffer_payload_max;
	काष्ठा gb_connection *connection;
	u16 cport_id;
	अचिन्हित पूर्णांक minor;
	अचिन्हित अक्षर clocal;
	bool disconnected;
	spinlock_t पढ़ो_lock;
	spinlock_t ग_लिखो_lock;
	काष्ठा async_icount iocount;
	काष्ठा async_icount oldcount;
	रुको_queue_head_t wioctl;
	काष्ठा mutex mutex;
	u8 ctrlin;	/* input control lines */
	u8 ctrlout;	/* output control lines */
	काष्ठा gb_uart_set_line_coding_request line_coding;
	काष्ठा work_काष्ठा tx_work;
	काष्ठा kfअगरo ग_लिखो_fअगरo;
	bool बंद_pending;
	अचिन्हित पूर्णांक credits;
	काष्ठा completion credits_complete;
पूर्ण;

अटल काष्ठा tty_driver *gb_tty_driver;
अटल DEFINE_IDR(tty_minors);
अटल DEFINE_MUTEX(table_lock);

अटल पूर्णांक gb_uart_receive_data_handler(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_connection *connection = op->connection;
	काष्ठा gb_tty *gb_tty = gb_connection_get_data(connection);
	काष्ठा tty_port *port = &gb_tty->port;
	काष्ठा gb_message *request = op->request;
	काष्ठा gb_uart_recv_data_request *receive_data;
	u16 recv_data_size;
	पूर्णांक count;
	अचिन्हित दीर्घ tty_flags = TTY_NORMAL;

	अगर (request->payload_size < माप(*receive_data)) अणु
		dev_err(&gb_tty->gbphy_dev->dev,
			"short receive-data request received (%zu < %zu)\n",
			request->payload_size, माप(*receive_data));
		वापस -EINVAL;
	पूर्ण

	receive_data = op->request->payload;
	recv_data_size = le16_to_cpu(receive_data->size);

	अगर (recv_data_size != request->payload_size - माप(*receive_data)) अणु
		dev_err(&gb_tty->gbphy_dev->dev,
			"malformed receive-data request received (%u != %zu)\n",
			recv_data_size,
			request->payload_size - माप(*receive_data));
		वापस -EINVAL;
	पूर्ण

	अगर (!recv_data_size)
		वापस -EINVAL;

	अगर (receive_data->flags) अणु
		अगर (receive_data->flags & GB_UART_RECV_FLAG_BREAK)
			tty_flags = TTY_BREAK;
		अन्यथा अगर (receive_data->flags & GB_UART_RECV_FLAG_PARITY)
			tty_flags = TTY_PARITY;
		अन्यथा अगर (receive_data->flags & GB_UART_RECV_FLAG_FRAMING)
			tty_flags = TTY_FRAME;

		/* overrun is special, not associated with a अक्षर */
		अगर (receive_data->flags & GB_UART_RECV_FLAG_OVERRUN)
			tty_insert_flip_अक्षर(port, 0, TTY_OVERRUN);
	पूर्ण
	count = tty_insert_flip_string_fixed_flag(port, receive_data->data,
						  tty_flags, recv_data_size);
	अगर (count != recv_data_size) अणु
		dev_err(&gb_tty->gbphy_dev->dev,
			"UART: RX 0x%08x bytes only wrote 0x%08x\n",
			recv_data_size, count);
	पूर्ण
	अगर (count)
		tty_flip_buffer_push(port);
	वापस 0;
पूर्ण

अटल पूर्णांक gb_uart_serial_state_handler(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_connection *connection = op->connection;
	काष्ठा gb_tty *gb_tty = gb_connection_get_data(connection);
	काष्ठा gb_message *request = op->request;
	काष्ठा gb_uart_serial_state_request *serial_state;

	अगर (request->payload_size < माप(*serial_state)) अणु
		dev_err(&gb_tty->gbphy_dev->dev,
			"short serial-state event received (%zu < %zu)\n",
			request->payload_size, माप(*serial_state));
		वापस -EINVAL;
	पूर्ण

	serial_state = request->payload;
	gb_tty->ctrlin = serial_state->control;

	वापस 0;
पूर्ण

अटल पूर्णांक gb_uart_receive_credits_handler(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_connection *connection = op->connection;
	काष्ठा gb_tty *gb_tty = gb_connection_get_data(connection);
	काष्ठा gb_message *request = op->request;
	काष्ठा gb_uart_receive_credits_request *credit_request;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक incoming_credits;
	पूर्णांक ret = 0;

	अगर (request->payload_size < माप(*credit_request)) अणु
		dev_err(&gb_tty->gbphy_dev->dev,
			"short receive_credits event received (%zu < %zu)\n",
			request->payload_size,
			माप(*credit_request));
		वापस -EINVAL;
	पूर्ण

	credit_request = request->payload;
	incoming_credits = le16_to_cpu(credit_request->count);

	spin_lock_irqsave(&gb_tty->ग_लिखो_lock, flags);
	gb_tty->credits += incoming_credits;
	अगर (gb_tty->credits > GB_UART_FIRMWARE_CREDITS) अणु
		gb_tty->credits -= incoming_credits;
		ret = -EINVAL;
	पूर्ण
	spin_unlock_irqrestore(&gb_tty->ग_लिखो_lock, flags);

	अगर (ret) अणु
		dev_err(&gb_tty->gbphy_dev->dev,
			"invalid number of incoming credits: %d\n",
			incoming_credits);
		वापस ret;
	पूर्ण

	अगर (!gb_tty->बंद_pending)
		schedule_work(&gb_tty->tx_work);

	/*
	 * the port the tty layer may be रुकोing क्रम credits
	 */
	tty_port_tty_wakeup(&gb_tty->port);

	अगर (gb_tty->credits == GB_UART_FIRMWARE_CREDITS)
		complete(&gb_tty->credits_complete);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_uart_request_handler(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_connection *connection = op->connection;
	काष्ठा gb_tty *gb_tty = gb_connection_get_data(connection);
	पूर्णांक type = op->type;
	पूर्णांक ret;

	चयन (type) अणु
	हाल GB_UART_TYPE_RECEIVE_DATA:
		ret = gb_uart_receive_data_handler(op);
		अवरोध;
	हाल GB_UART_TYPE_SERIAL_STATE:
		ret = gb_uart_serial_state_handler(op);
		अवरोध;
	हाल GB_UART_TYPE_RECEIVE_CREDITS:
		ret = gb_uart_receive_credits_handler(op);
		अवरोध;
	शेष:
		dev_err(&gb_tty->gbphy_dev->dev,
			"unsupported unsolicited request: 0x%02x\n", type);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम  gb_uart_tx_ग_लिखो_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gb_uart_send_data_request *request;
	काष्ठा gb_tty *gb_tty;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक send_size;
	पूर्णांक ret;

	gb_tty = container_of(work, काष्ठा gb_tty, tx_work);
	request = gb_tty->buffer;

	जबतक (1) अणु
		अगर (gb_tty->बंद_pending)
			अवरोध;

		spin_lock_irqsave(&gb_tty->ग_लिखो_lock, flags);
		send_size = gb_tty->buffer_payload_max;
		अगर (send_size > gb_tty->credits)
			send_size = gb_tty->credits;

		send_size = kfअगरo_out_peek(&gb_tty->ग_लिखो_fअगरo,
					   &request->data[0],
					   send_size);
		अगर (!send_size) अणु
			spin_unlock_irqrestore(&gb_tty->ग_लिखो_lock, flags);
			अवरोध;
		पूर्ण

		gb_tty->credits -= send_size;
		spin_unlock_irqrestore(&gb_tty->ग_लिखो_lock, flags);

		request->size = cpu_to_le16(send_size);
		ret = gb_operation_sync(gb_tty->connection,
					GB_UART_TYPE_SEND_DATA,
					request, माप(*request) + send_size,
					शून्य, 0);
		अगर (ret) अणु
			dev_err(&gb_tty->gbphy_dev->dev,
				"send data error: %d\n", ret);
			spin_lock_irqsave(&gb_tty->ग_लिखो_lock, flags);
			gb_tty->credits += send_size;
			spin_unlock_irqrestore(&gb_tty->ग_लिखो_lock, flags);
			अगर (!gb_tty->बंद_pending)
				schedule_work(work);
			वापस;
		पूर्ण

		spin_lock_irqsave(&gb_tty->ग_लिखो_lock, flags);
		ret = kfअगरo_out(&gb_tty->ग_लिखो_fअगरo, &request->data[0],
				send_size);
		spin_unlock_irqrestore(&gb_tty->ग_लिखो_lock, flags);

		tty_port_tty_wakeup(&gb_tty->port);
	पूर्ण
पूर्ण

अटल पूर्णांक send_line_coding(काष्ठा gb_tty *tty)
अणु
	वापस gb_operation_sync(tty->connection, GB_UART_TYPE_SET_LINE_CODING,
				 &tty->line_coding, माप(tty->line_coding),
				 शून्य, 0);
पूर्ण

अटल पूर्णांक send_control(काष्ठा gb_tty *gb_tty, u8 control)
अणु
	काष्ठा gb_uart_set_control_line_state_request request;

	request.control = control;
	वापस gb_operation_sync(gb_tty->connection,
				 GB_UART_TYPE_SET_CONTROL_LINE_STATE,
				 &request, माप(request), शून्य, 0);
पूर्ण

अटल पूर्णांक send_अवरोध(काष्ठा gb_tty *gb_tty, u8 state)
अणु
	काष्ठा gb_uart_set_अवरोध_request request;

	अगर ((state != 0) && (state != 1)) अणु
		dev_err(&gb_tty->gbphy_dev->dev,
			"invalid break state of %d\n", state);
		वापस -EINVAL;
	पूर्ण

	request.state = state;
	वापस gb_operation_sync(gb_tty->connection, GB_UART_TYPE_SEND_BREAK,
				 &request, माप(request), शून्य, 0);
पूर्ण

अटल पूर्णांक gb_uart_रुको_क्रम_all_credits(काष्ठा gb_tty *gb_tty)
अणु
	पूर्णांक ret;

	अगर (gb_tty->credits == GB_UART_FIRMWARE_CREDITS)
		वापस 0;

	ret = रुको_क्रम_completion_समयout(&gb_tty->credits_complete,
			msecs_to_jअगरfies(GB_UART_CREDIT_WAIT_TIMEOUT_MSEC));
	अगर (!ret) अणु
		dev_err(&gb_tty->gbphy_dev->dev,
			"time out waiting for credits\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gb_uart_flush(काष्ठा gb_tty *gb_tty, u8 flags)
अणु
	काष्ठा gb_uart_serial_flush_request request;

	request.flags = flags;
	वापस gb_operation_sync(gb_tty->connection, GB_UART_TYPE_FLUSH_FIFOS,
				 &request, माप(request), शून्य, 0);
पूर्ण

अटल काष्ठा gb_tty *get_gb_by_minor(अचिन्हित पूर्णांक minor)
अणु
	काष्ठा gb_tty *gb_tty;

	mutex_lock(&table_lock);
	gb_tty = idr_find(&tty_minors, minor);
	अगर (gb_tty) अणु
		mutex_lock(&gb_tty->mutex);
		अगर (gb_tty->disconnected) अणु
			mutex_unlock(&gb_tty->mutex);
			gb_tty = शून्य;
		पूर्ण अन्यथा अणु
			tty_port_get(&gb_tty->port);
			mutex_unlock(&gb_tty->mutex);
		पूर्ण
	पूर्ण
	mutex_unlock(&table_lock);
	वापस gb_tty;
पूर्ण

अटल पूर्णांक alloc_minor(काष्ठा gb_tty *gb_tty)
अणु
	पूर्णांक minor;

	mutex_lock(&table_lock);
	minor = idr_alloc(&tty_minors, gb_tty, 0, GB_NUM_MINORS, GFP_KERNEL);
	mutex_unlock(&table_lock);
	अगर (minor >= 0)
		gb_tty->minor = minor;
	वापस minor;
पूर्ण

अटल व्योम release_minor(काष्ठा gb_tty *gb_tty)
अणु
	पूर्णांक minor = gb_tty->minor;

	gb_tty->minor = 0;	/* Maybe should use an invalid value instead */
	mutex_lock(&table_lock);
	idr_हटाओ(&tty_minors, minor);
	mutex_unlock(&table_lock);
पूर्ण

अटल पूर्णांक gb_tty_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gb_tty *gb_tty;
	पूर्णांक retval;

	gb_tty = get_gb_by_minor(tty->index);
	अगर (!gb_tty)
		वापस -ENODEV;

	retval = tty_standard_install(driver, tty);
	अगर (retval)
		जाओ error;

	tty->driver_data = gb_tty;
	वापस 0;
error:
	tty_port_put(&gb_tty->port);
	वापस retval;
पूर्ण

अटल पूर्णांक gb_tty_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file)
अणु
	काष्ठा gb_tty *gb_tty = tty->driver_data;

	वापस tty_port_खोलो(&gb_tty->port, tty, file);
पूर्ण

अटल व्योम gb_tty_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *file)
अणु
	काष्ठा gb_tty *gb_tty = tty->driver_data;

	tty_port_बंद(&gb_tty->port, tty, file);
पूर्ण

अटल व्योम gb_tty_cleanup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gb_tty *gb_tty = tty->driver_data;

	tty_port_put(&gb_tty->port);
पूर्ण

अटल व्योम gb_tty_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gb_tty *gb_tty = tty->driver_data;

	tty_port_hangup(&gb_tty->port);
पूर्ण

अटल पूर्णांक gb_tty_ग_लिखो(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buf,
			पूर्णांक count)
अणु
	काष्ठा gb_tty *gb_tty = tty->driver_data;

	count =  kfअगरo_in_spinlocked(&gb_tty->ग_लिखो_fअगरo, buf, count,
				     &gb_tty->ग_लिखो_lock);
	अगर (count && !gb_tty->बंद_pending)
		schedule_work(&gb_tty->tx_work);

	वापस count;
पूर्ण

अटल पूर्णांक gb_tty_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gb_tty *gb_tty = tty->driver_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक room;

	spin_lock_irqsave(&gb_tty->ग_लिखो_lock, flags);
	room = kfअगरo_avail(&gb_tty->ग_लिखो_fअगरo);
	spin_unlock_irqrestore(&gb_tty->ग_लिखो_lock, flags);

	room -= GB_UART_WRITE_ROOM_MARGIN;
	अगर (room < 0)
		वापस 0;

	वापस room;
पूर्ण

अटल पूर्णांक gb_tty_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gb_tty *gb_tty = tty->driver_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक अक्षरs;

	spin_lock_irqsave(&gb_tty->ग_लिखो_lock, flags);
	अक्षरs = kfअगरo_len(&gb_tty->ग_लिखो_fअगरo);
	अगर (gb_tty->credits < GB_UART_FIRMWARE_CREDITS)
		अक्षरs += GB_UART_FIRMWARE_CREDITS - gb_tty->credits;
	spin_unlock_irqrestore(&gb_tty->ग_लिखो_lock, flags);

	वापस अक्षरs;
पूर्ण

अटल पूर्णांक gb_tty_अवरोध_ctl(काष्ठा tty_काष्ठा *tty, पूर्णांक state)
अणु
	काष्ठा gb_tty *gb_tty = tty->driver_data;

	वापस send_अवरोध(gb_tty, state ? 1 : 0);
पूर्ण

अटल व्योम gb_tty_set_termios(काष्ठा tty_काष्ठा *tty,
			       काष्ठा ktermios *termios_old)
अणु
	काष्ठा gb_uart_set_line_coding_request newline;
	काष्ठा gb_tty *gb_tty = tty->driver_data;
	काष्ठा ktermios *termios = &tty->termios;
	u8 newctrl = gb_tty->ctrlout;

	newline.rate = cpu_to_le32(tty_get_baud_rate(tty));
	newline.क्रमmat = termios->c_cflag & CSTOPB ?
				GB_SERIAL_2_STOP_BITS : GB_SERIAL_1_STOP_BITS;
	newline.parity = termios->c_cflag & PARENB ?
				(termios->c_cflag & PARODD ? 1 : 2) +
				(termios->c_cflag & CMSPAR ? 2 : 0) : 0;

	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
		newline.data_bits = 5;
		अवरोध;
	हाल CS6:
		newline.data_bits = 6;
		अवरोध;
	हाल CS7:
		newline.data_bits = 7;
		अवरोध;
	हाल CS8:
	शेष:
		newline.data_bits = 8;
		अवरोध;
	पूर्ण

	/* FIXME: needs to clear unsupported bits in the termios */
	gb_tty->clocal = ((termios->c_cflag & CLOCAL) != 0);

	अगर (C_BAUD(tty) == B0) अणु
		newline.rate = gb_tty->line_coding.rate;
		newctrl &= ~(GB_UART_CTRL_DTR | GB_UART_CTRL_RTS);
	पूर्ण अन्यथा अगर (termios_old && (termios_old->c_cflag & CBAUD) == B0) अणु
		newctrl |= (GB_UART_CTRL_DTR | GB_UART_CTRL_RTS);
	पूर्ण

	अगर (newctrl != gb_tty->ctrlout) अणु
		gb_tty->ctrlout = newctrl;
		send_control(gb_tty, newctrl);
	पूर्ण

	अगर (C_CRTSCTS(tty) && C_BAUD(tty) != B0)
		newline.flow_control = GB_SERIAL_AUTO_RTSCTS_EN;
	अन्यथा
		newline.flow_control = 0;

	अगर (स_भेद(&gb_tty->line_coding, &newline, माप(newline))) अणु
		स_नकल(&gb_tty->line_coding, &newline, माप(newline));
		send_line_coding(gb_tty);
	पूर्ण
पूर्ण

अटल पूर्णांक gb_tty_tiocmget(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gb_tty *gb_tty = tty->driver_data;

	वापस (gb_tty->ctrlout & GB_UART_CTRL_DTR ? TIOCM_DTR : 0) |
	       (gb_tty->ctrlout & GB_UART_CTRL_RTS ? TIOCM_RTS : 0) |
	       (gb_tty->ctrlin  & GB_UART_CTRL_DSR ? TIOCM_DSR : 0) |
	       (gb_tty->ctrlin  & GB_UART_CTRL_RI  ? TIOCM_RI  : 0) |
	       (gb_tty->ctrlin  & GB_UART_CTRL_DCD ? TIOCM_CD  : 0) |
	       TIOCM_CTS;
पूर्ण

अटल पूर्णांक gb_tty_tiocmset(काष्ठा tty_काष्ठा *tty, अचिन्हित पूर्णांक set,
			   अचिन्हित पूर्णांक clear)
अणु
	काष्ठा gb_tty *gb_tty = tty->driver_data;
	u8 newctrl = gb_tty->ctrlout;

	set = (set & TIOCM_DTR ? GB_UART_CTRL_DTR : 0) |
	      (set & TIOCM_RTS ? GB_UART_CTRL_RTS : 0);
	clear = (clear & TIOCM_DTR ? GB_UART_CTRL_DTR : 0) |
		(clear & TIOCM_RTS ? GB_UART_CTRL_RTS : 0);

	newctrl = (newctrl & ~clear) | set;
	अगर (gb_tty->ctrlout == newctrl)
		वापस 0;

	gb_tty->ctrlout = newctrl;
	वापस send_control(gb_tty, newctrl);
पूर्ण

अटल व्योम gb_tty_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gb_tty *gb_tty = tty->driver_data;
	अचिन्हित अक्षर stop_अक्षर;
	पूर्णांक retval;

	अगर (I_IXOFF(tty)) अणु
		stop_अक्षर = STOP_CHAR(tty);
		retval = gb_tty_ग_लिखो(tty, &stop_अक्षर, 1);
		अगर (retval <= 0)
			वापस;
	पूर्ण

	अगर (tty->termios.c_cflag & CRTSCTS) अणु
		gb_tty->ctrlout &= ~GB_UART_CTRL_RTS;
		retval = send_control(gb_tty, gb_tty->ctrlout);
	पूर्ण
पूर्ण

अटल व्योम gb_tty_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gb_tty *gb_tty = tty->driver_data;
	अचिन्हित अक्षर start_अक्षर;
	पूर्णांक retval;

	अगर (I_IXOFF(tty)) अणु
		start_अक्षर = START_CHAR(tty);
		retval = gb_tty_ग_लिखो(tty, &start_अक्षर, 1);
		अगर (retval <= 0)
			वापस;
	पूर्ण

	अगर (tty->termios.c_cflag & CRTSCTS) अणु
		gb_tty->ctrlout |= GB_UART_CTRL_RTS;
		retval = send_control(gb_tty, gb_tty->ctrlout);
	पूर्ण
पूर्ण

अटल पूर्णांक get_serial_info(काष्ठा tty_काष्ठा *tty,
			   काष्ठा serial_काष्ठा *ss)
अणु
	काष्ठा gb_tty *gb_tty = tty->driver_data;

	ss->line = gb_tty->minor;
	ss->बंद_delay = jअगरfies_to_msecs(gb_tty->port.बंद_delay) / 10;
	ss->closing_रुको =
		gb_tty->port.closing_रुको == ASYNC_CLOSING_WAIT_NONE ?
		ASYNC_CLOSING_WAIT_NONE :
		jअगरfies_to_msecs(gb_tty->port.closing_रुको) / 10;

	वापस 0;
पूर्ण

अटल पूर्णांक set_serial_info(काष्ठा tty_काष्ठा *tty,
			   काष्ठा serial_काष्ठा *ss)
अणु
	काष्ठा gb_tty *gb_tty = tty->driver_data;
	अचिन्हित पूर्णांक closing_रुको;
	अचिन्हित पूर्णांक बंद_delay;
	पूर्णांक retval = 0;

	बंद_delay = msecs_to_jअगरfies(ss->बंद_delay * 10);
	closing_रुको = ss->closing_रुको == ASYNC_CLOSING_WAIT_NONE ?
			ASYNC_CLOSING_WAIT_NONE :
			msecs_to_jअगरfies(ss->closing_रुको * 10);

	mutex_lock(&gb_tty->port.mutex);
	अगर (!capable(CAP_SYS_ADMIN)) अणु
		अगर ((बंद_delay != gb_tty->port.बंद_delay) ||
		    (closing_रुको != gb_tty->port.closing_रुको))
			retval = -EPERM;
	पूर्ण अन्यथा अणु
		gb_tty->port.बंद_delay = बंद_delay;
		gb_tty->port.closing_रुको = closing_रुको;
	पूर्ण
	mutex_unlock(&gb_tty->port.mutex);
	वापस retval;
पूर्ण

अटल पूर्णांक रुको_serial_change(काष्ठा gb_tty *gb_tty, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक retval = 0;
	DECLARE_WAITQUEUE(रुको, current);
	काष्ठा async_icount old;
	काष्ठा async_icount new;

	अगर (!(arg & (TIOCM_DSR | TIOCM_RI | TIOCM_CD)))
		वापस -EINVAL;

	करो अणु
		spin_lock_irq(&gb_tty->पढ़ो_lock);
		old = gb_tty->oldcount;
		new = gb_tty->iocount;
		gb_tty->oldcount = new;
		spin_unlock_irq(&gb_tty->पढ़ो_lock);

		अगर ((arg & TIOCM_DSR) && (old.dsr != new.dsr))
			अवरोध;
		अगर ((arg & TIOCM_CD) && (old.dcd != new.dcd))
			अवरोध;
		अगर ((arg & TIOCM_RI) && (old.rng != new.rng))
			अवरोध;

		add_रुको_queue(&gb_tty->wioctl, &रुको);
		set_current_state(TASK_INTERRUPTIBLE);
		schedule();
		हटाओ_रुको_queue(&gb_tty->wioctl, &रुको);
		अगर (gb_tty->disconnected) अणु
			अगर (arg & TIOCM_CD)
				अवरोध;
			retval = -ENODEV;
		पूर्ण अन्यथा अगर (संकेत_pending(current)) अणु
			retval = -ERESTARTSYS;
		पूर्ण
	पूर्ण जबतक (!retval);

	वापस retval;
पूर्ण

अटल पूर्णांक gb_tty_get_icount(काष्ठा tty_काष्ठा *tty,
			     काष्ठा serial_icounter_काष्ठा *icount)
अणु
	काष्ठा gb_tty *gb_tty = tty->driver_data;

	icount->dsr = gb_tty->iocount.dsr;
	icount->rng = gb_tty->iocount.rng;
	icount->dcd = gb_tty->iocount.dcd;
	icount->frame = gb_tty->iocount.frame;
	icount->overrun = gb_tty->iocount.overrun;
	icount->parity = gb_tty->iocount.parity;
	icount->brk = gb_tty->iocount.brk;

	वापस 0;
पूर्ण

अटल पूर्णांक gb_tty_ioctl(काष्ठा tty_काष्ठा *tty, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ arg)
अणु
	काष्ठा gb_tty *gb_tty = tty->driver_data;

	चयन (cmd) अणु
	हाल TIOCMIWAIT:
		वापस रुको_serial_change(gb_tty, arg);
	पूर्ण

	वापस -ENOIOCTLCMD;
पूर्ण

अटल व्योम gb_tty_dtr_rts(काष्ठा tty_port *port, पूर्णांक on)
अणु
	काष्ठा gb_tty *gb_tty;
	u8 newctrl;

	gb_tty = container_of(port, काष्ठा gb_tty, port);
	newctrl = gb_tty->ctrlout;

	अगर (on)
		newctrl |= (GB_UART_CTRL_DTR | GB_UART_CTRL_RTS);
	अन्यथा
		newctrl &= ~(GB_UART_CTRL_DTR | GB_UART_CTRL_RTS);

	gb_tty->ctrlout = newctrl;
	send_control(gb_tty, newctrl);
पूर्ण

अटल पूर्णांक gb_tty_port_activate(काष्ठा tty_port *port,
				काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gb_tty *gb_tty;

	gb_tty = container_of(port, काष्ठा gb_tty, port);

	वापस gbphy_runसमय_get_sync(gb_tty->gbphy_dev);
पूर्ण

अटल व्योम gb_tty_port_shutकरोwn(काष्ठा tty_port *port)
अणु
	काष्ठा gb_tty *gb_tty;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	gb_tty = container_of(port, काष्ठा gb_tty, port);

	gb_tty->बंद_pending = true;

	cancel_work_sync(&gb_tty->tx_work);

	spin_lock_irqsave(&gb_tty->ग_लिखो_lock, flags);
	kfअगरo_reset_out(&gb_tty->ग_लिखो_fअगरo);
	spin_unlock_irqrestore(&gb_tty->ग_लिखो_lock, flags);

	अगर (gb_tty->credits == GB_UART_FIRMWARE_CREDITS)
		जाओ out;

	ret = gb_uart_flush(gb_tty, GB_SERIAL_FLAG_FLUSH_TRANSMITTER);
	अगर (ret) अणु
		dev_err(&gb_tty->gbphy_dev->dev,
			"error flushing transmitter: %d\n", ret);
	पूर्ण

	gb_uart_रुको_क्रम_all_credits(gb_tty);

out:
	gb_tty->बंद_pending = false;

	gbphy_runसमय_put_स्वतःsuspend(gb_tty->gbphy_dev);
पूर्ण

अटल स्थिर काष्ठा tty_operations gb_ops = अणु
	.install =		gb_tty_install,
	.खोलो =			gb_tty_खोलो,
	.बंद =		gb_tty_बंद,
	.cleanup =		gb_tty_cleanup,
	.hangup =		gb_tty_hangup,
	.ग_लिखो =		gb_tty_ग_लिखो,
	.ग_लिखो_room =		gb_tty_ग_लिखो_room,
	.ioctl =		gb_tty_ioctl,
	.throttle =		gb_tty_throttle,
	.unthrottle =		gb_tty_unthrottle,
	.अक्षरs_in_buffer =	gb_tty_अक्षरs_in_buffer,
	.अवरोध_ctl =		gb_tty_अवरोध_ctl,
	.set_termios =		gb_tty_set_termios,
	.tiocmget =		gb_tty_tiocmget,
	.tiocmset =		gb_tty_tiocmset,
	.get_icount =		gb_tty_get_icount,
	.set_serial =		set_serial_info,
	.get_serial =		get_serial_info,
पूर्ण;

अटल स्थिर काष्ठा tty_port_operations gb_port_ops = अणु
	.dtr_rts =		gb_tty_dtr_rts,
	.activate =		gb_tty_port_activate,
	.shutकरोwn =		gb_tty_port_shutकरोwn,
पूर्ण;

अटल पूर्णांक gb_uart_probe(काष्ठा gbphy_device *gbphy_dev,
			 स्थिर काष्ठा gbphy_device_id *id)
अणु
	काष्ठा gb_connection *connection;
	माप_प्रकार max_payload;
	काष्ठा gb_tty *gb_tty;
	काष्ठा device *tty_dev;
	पूर्णांक retval;
	पूर्णांक minor;

	gb_tty = kzalloc(माप(*gb_tty), GFP_KERNEL);
	अगर (!gb_tty)
		वापस -ENOMEM;

	connection = gb_connection_create(gbphy_dev->bundle,
					  le16_to_cpu(gbphy_dev->cport_desc->id),
					  gb_uart_request_handler);
	अगर (IS_ERR(connection)) अणु
		retval = PTR_ERR(connection);
		जाओ निकास_tty_मुक्त;
	पूर्ण

	max_payload = gb_operation_get_payload_size_max(connection);
	अगर (max_payload < माप(काष्ठा gb_uart_send_data_request)) अणु
		retval = -EINVAL;
		जाओ निकास_connection_destroy;
	पूर्ण

	gb_tty->buffer_payload_max = max_payload -
			माप(काष्ठा gb_uart_send_data_request);

	gb_tty->buffer = kzalloc(gb_tty->buffer_payload_max, GFP_KERNEL);
	अगर (!gb_tty->buffer) अणु
		retval = -ENOMEM;
		जाओ निकास_connection_destroy;
	पूर्ण

	INIT_WORK(&gb_tty->tx_work, gb_uart_tx_ग_लिखो_work);

	retval = kfअगरo_alloc(&gb_tty->ग_लिखो_fअगरo, GB_UART_WRITE_FIFO_SIZE,
			     GFP_KERNEL);
	अगर (retval)
		जाओ निकास_buf_मुक्त;

	gb_tty->credits = GB_UART_FIRMWARE_CREDITS;
	init_completion(&gb_tty->credits_complete);

	minor = alloc_minor(gb_tty);
	अगर (minor < 0) अणु
		अगर (minor == -ENOSPC) अणु
			dev_err(&gbphy_dev->dev,
				"no more free minor numbers\n");
			retval = -ENODEV;
		पूर्ण अन्यथा अणु
			retval = minor;
		पूर्ण
		जाओ निकास_kfअगरo_मुक्त;
	पूर्ण

	gb_tty->minor = minor;
	spin_lock_init(&gb_tty->ग_लिखो_lock);
	spin_lock_init(&gb_tty->पढ़ो_lock);
	init_रुकोqueue_head(&gb_tty->wioctl);
	mutex_init(&gb_tty->mutex);

	tty_port_init(&gb_tty->port);
	gb_tty->port.ops = &gb_port_ops;

	gb_tty->connection = connection;
	gb_tty->gbphy_dev = gbphy_dev;
	gb_connection_set_data(connection, gb_tty);
	gb_gbphy_set_data(gbphy_dev, gb_tty);

	retval = gb_connection_enable_tx(connection);
	अगर (retval)
		जाओ निकास_release_minor;

	send_control(gb_tty, gb_tty->ctrlout);

	/* initialize the uart to be 9600n81 */
	gb_tty->line_coding.rate = cpu_to_le32(9600);
	gb_tty->line_coding.क्रमmat = GB_SERIAL_1_STOP_BITS;
	gb_tty->line_coding.parity = GB_SERIAL_NO_PARITY;
	gb_tty->line_coding.data_bits = 8;
	send_line_coding(gb_tty);

	retval = gb_connection_enable(connection);
	अगर (retval)
		जाओ निकास_connection_disable;

	tty_dev = tty_port_रेजिस्टर_device(&gb_tty->port, gb_tty_driver, minor,
					   &gbphy_dev->dev);
	अगर (IS_ERR(tty_dev)) अणु
		retval = PTR_ERR(tty_dev);
		जाओ निकास_connection_disable;
	पूर्ण

	gbphy_runसमय_put_स्वतःsuspend(gbphy_dev);
	वापस 0;

निकास_connection_disable:
	gb_connection_disable(connection);
निकास_release_minor:
	release_minor(gb_tty);
निकास_kfअगरo_मुक्त:
	kfअगरo_मुक्त(&gb_tty->ग_लिखो_fअगरo);
निकास_buf_मुक्त:
	kमुक्त(gb_tty->buffer);
निकास_connection_destroy:
	gb_connection_destroy(connection);
निकास_tty_मुक्त:
	kमुक्त(gb_tty);

	वापस retval;
पूर्ण

अटल व्योम gb_uart_हटाओ(काष्ठा gbphy_device *gbphy_dev)
अणु
	काष्ठा gb_tty *gb_tty = gb_gbphy_get_data(gbphy_dev);
	काष्ठा gb_connection *connection = gb_tty->connection;
	काष्ठा tty_काष्ठा *tty;
	पूर्णांक ret;

	ret = gbphy_runसमय_get_sync(gbphy_dev);
	अगर (ret)
		gbphy_runसमय_get_noresume(gbphy_dev);

	mutex_lock(&gb_tty->mutex);
	gb_tty->disconnected = true;

	wake_up_all(&gb_tty->wioctl);
	mutex_unlock(&gb_tty->mutex);

	tty = tty_port_tty_get(&gb_tty->port);
	अगर (tty) अणु
		tty_vhangup(tty);
		tty_kref_put(tty);
	पूर्ण

	gb_connection_disable_rx(connection);
	tty_unरेजिस्टर_device(gb_tty_driver, gb_tty->minor);

	/* FIXME - मुक्त transmit / receive buffers */

	gb_connection_disable(connection);
	tty_port_destroy(&gb_tty->port);
	gb_connection_destroy(connection);
	release_minor(gb_tty);
	kfअगरo_मुक्त(&gb_tty->ग_लिखो_fअगरo);
	kमुक्त(gb_tty->buffer);
	kमुक्त(gb_tty);
पूर्ण

अटल पूर्णांक gb_tty_init(व्योम)
अणु
	पूर्णांक retval = 0;

	gb_tty_driver = tty_alloc_driver(GB_NUM_MINORS, 0);
	अगर (IS_ERR(gb_tty_driver)) अणु
		pr_err("Can not allocate tty driver\n");
		retval = -ENOMEM;
		जाओ fail_unरेजिस्टर_dev;
	पूर्ण

	gb_tty_driver->driver_name = "gb";
	gb_tty_driver->name = GB_NAME;
	gb_tty_driver->major = 0;
	gb_tty_driver->minor_start = 0;
	gb_tty_driver->type = TTY_DRIVER_TYPE_SERIAL;
	gb_tty_driver->subtype = SERIAL_TYPE_NORMAL;
	gb_tty_driver->flags = TTY_DRIVER_REAL_RAW | TTY_DRIVER_DYNAMIC_DEV;
	gb_tty_driver->init_termios = tty_std_termios;
	gb_tty_driver->init_termios.c_cflag = B9600 | CS8 |
		CREAD | HUPCL | CLOCAL;
	tty_set_operations(gb_tty_driver, &gb_ops);

	retval = tty_रेजिस्टर_driver(gb_tty_driver);
	अगर (retval) अणु
		pr_err("Can not register tty driver: %d\n", retval);
		जाओ fail_put_gb_tty;
	पूर्ण

	वापस 0;

fail_put_gb_tty:
	put_tty_driver(gb_tty_driver);
fail_unरेजिस्टर_dev:
	वापस retval;
पूर्ण

अटल व्योम gb_tty_निकास(व्योम)
अणु
	tty_unरेजिस्टर_driver(gb_tty_driver);
	put_tty_driver(gb_tty_driver);
	idr_destroy(&tty_minors);
पूर्ण

अटल स्थिर काष्ठा gbphy_device_id gb_uart_id_table[] = अणु
	अणु GBPHY_PROTOCOL(GREYBUS_PROTOCOL_UART) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(gbphy, gb_uart_id_table);

अटल काष्ठा gbphy_driver uart_driver = अणु
	.name		= "uart",
	.probe		= gb_uart_probe,
	.हटाओ		= gb_uart_हटाओ,
	.id_table	= gb_uart_id_table,
पूर्ण;

अटल पूर्णांक gb_uart_driver_init(व्योम)
अणु
	पूर्णांक ret;

	ret = gb_tty_init();
	अगर (ret)
		वापस ret;

	ret = gb_gbphy_रेजिस्टर(&uart_driver);
	अगर (ret) अणु
		gb_tty_निकास();
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
module_init(gb_uart_driver_init);

अटल व्योम gb_uart_driver_निकास(व्योम)
अणु
	gb_gbphy_deरेजिस्टर(&uart_driver);
	gb_tty_निकास();
पूर्ण

module_निकास(gb_uart_driver_निकास);
MODULE_LICENSE("GPL v2");
