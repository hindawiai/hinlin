<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2016-2017 Linaro Ltd., Rob Herring <robh@kernel.org>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/serdev.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/poll.h>

#घोषणा SERPORT_ACTIVE		1

काष्ठा serport अणु
	काष्ठा tty_port *port;
	काष्ठा tty_काष्ठा *tty;
	काष्ठा tty_driver *tty_drv;
	पूर्णांक tty_idx;
	अचिन्हित दीर्घ flags;
पूर्ण;

/*
 * Callback functions from the tty port.
 */

अटल पूर्णांक ttyport_receive_buf(काष्ठा tty_port *port, स्थिर अचिन्हित अक्षर *cp,
				स्थिर अचिन्हित अक्षर *fp, माप_प्रकार count)
अणु
	काष्ठा serdev_controller *ctrl = port->client_data;
	काष्ठा serport *serport = serdev_controller_get_drvdata(ctrl);
	पूर्णांक ret;

	अगर (!test_bit(SERPORT_ACTIVE, &serport->flags))
		वापस 0;

	ret = serdev_controller_receive_buf(ctrl, cp, count);

	dev_WARN_ONCE(&ctrl->dev, ret < 0 || ret > count,
				"receive_buf returns %d (count = %zu)\n",
				ret, count);
	अगर (ret < 0)
		वापस 0;
	अन्यथा अगर (ret > count)
		वापस count;

	वापस ret;
पूर्ण

अटल व्योम ttyport_ग_लिखो_wakeup(काष्ठा tty_port *port)
अणु
	काष्ठा serdev_controller *ctrl = port->client_data;
	काष्ठा serport *serport = serdev_controller_get_drvdata(ctrl);
	काष्ठा tty_काष्ठा *tty;

	tty = tty_port_tty_get(port);
	अगर (!tty)
		वापस;

	अगर (test_and_clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags) &&
	    test_bit(SERPORT_ACTIVE, &serport->flags))
		serdev_controller_ग_लिखो_wakeup(ctrl);

	/* Wake up any tty_रुको_until_sent() */
	wake_up_पूर्णांकerruptible(&tty->ग_लिखो_रुको);

	tty_kref_put(tty);
पूर्ण

अटल स्थिर काष्ठा tty_port_client_operations client_ops = अणु
	.receive_buf = ttyport_receive_buf,
	.ग_लिखो_wakeup = ttyport_ग_लिखो_wakeup,
पूर्ण;

/*
 * Callback functions from the serdev core.
 */

अटल पूर्णांक ttyport_ग_लिखो_buf(काष्ठा serdev_controller *ctrl, स्थिर अचिन्हित अक्षर *data, माप_प्रकार len)
अणु
	काष्ठा serport *serport = serdev_controller_get_drvdata(ctrl);
	काष्ठा tty_काष्ठा *tty = serport->tty;

	अगर (!test_bit(SERPORT_ACTIVE, &serport->flags))
		वापस 0;

	set_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
	वापस tty->ops->ग_लिखो(serport->tty, data, len);
पूर्ण

अटल व्योम ttyport_ग_लिखो_flush(काष्ठा serdev_controller *ctrl)
अणु
	काष्ठा serport *serport = serdev_controller_get_drvdata(ctrl);
	काष्ठा tty_काष्ठा *tty = serport->tty;

	tty_driver_flush_buffer(tty);
पूर्ण

अटल पूर्णांक ttyport_ग_लिखो_room(काष्ठा serdev_controller *ctrl)
अणु
	काष्ठा serport *serport = serdev_controller_get_drvdata(ctrl);
	काष्ठा tty_काष्ठा *tty = serport->tty;

	वापस tty_ग_लिखो_room(tty);
पूर्ण

अटल पूर्णांक ttyport_खोलो(काष्ठा serdev_controller *ctrl)
अणु
	काष्ठा serport *serport = serdev_controller_get_drvdata(ctrl);
	काष्ठा tty_काष्ठा *tty;
	काष्ठा ktermios ktermios;
	पूर्णांक ret;

	tty = tty_init_dev(serport->tty_drv, serport->tty_idx);
	अगर (IS_ERR(tty))
		वापस PTR_ERR(tty);
	serport->tty = tty;

	अगर (!tty->ops->खोलो || !tty->ops->बंद) अणु
		ret = -ENODEV;
		जाओ err_unlock;
	पूर्ण

	ret = tty->ops->खोलो(serport->tty, शून्य);
	अगर (ret)
		जाओ err_बंद;

	tty_unlock(serport->tty);

	/* Bring the UART पूर्णांकo a known 8 bits no parity hw fc state */
	ktermios = tty->termios;
	ktermios.c_अगरlag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP |
			      INLCR | IGNCR | ICRNL | IXON);
	ktermios.c_oflag &= ~OPOST;
	ktermios.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	ktermios.c_cflag &= ~(CSIZE | PARENB);
	ktermios.c_cflag |= CS8;
	ktermios.c_cflag |= CRTSCTS;
	/* Hangups are not supported so make sure to ignore carrier detect. */
	ktermios.c_cflag |= CLOCAL;
	tty_set_termios(tty, &ktermios);

	set_bit(SERPORT_ACTIVE, &serport->flags);

	वापस 0;

err_बंद:
	tty->ops->बंद(tty, शून्य);
err_unlock:
	tty_unlock(tty);
	tty_release_काष्ठा(tty, serport->tty_idx);

	वापस ret;
पूर्ण

अटल व्योम ttyport_बंद(काष्ठा serdev_controller *ctrl)
अणु
	काष्ठा serport *serport = serdev_controller_get_drvdata(ctrl);
	काष्ठा tty_काष्ठा *tty = serport->tty;

	clear_bit(SERPORT_ACTIVE, &serport->flags);

	tty_lock(tty);
	अगर (tty->ops->बंद)
		tty->ops->बंद(tty, शून्य);
	tty_unlock(tty);

	tty_release_काष्ठा(tty, serport->tty_idx);
पूर्ण

अटल अचिन्हित पूर्णांक ttyport_set_baudrate(काष्ठा serdev_controller *ctrl, अचिन्हित पूर्णांक speed)
अणु
	काष्ठा serport *serport = serdev_controller_get_drvdata(ctrl);
	काष्ठा tty_काष्ठा *tty = serport->tty;
	काष्ठा ktermios ktermios = tty->termios;

	ktermios.c_cflag &= ~CBAUD;
	tty_termios_encode_baud_rate(&ktermios, speed, speed);

	/* tty_set_termios() वापस not checked as it is always 0 */
	tty_set_termios(tty, &ktermios);
	वापस ktermios.c_ospeed;
पूर्ण

अटल व्योम ttyport_set_flow_control(काष्ठा serdev_controller *ctrl, bool enable)
अणु
	काष्ठा serport *serport = serdev_controller_get_drvdata(ctrl);
	काष्ठा tty_काष्ठा *tty = serport->tty;
	काष्ठा ktermios ktermios = tty->termios;

	अगर (enable)
		ktermios.c_cflag |= CRTSCTS;
	अन्यथा
		ktermios.c_cflag &= ~CRTSCTS;

	tty_set_termios(tty, &ktermios);
पूर्ण

अटल पूर्णांक ttyport_set_parity(काष्ठा serdev_controller *ctrl,
			      क्रमागत serdev_parity parity)
अणु
	काष्ठा serport *serport = serdev_controller_get_drvdata(ctrl);
	काष्ठा tty_काष्ठा *tty = serport->tty;
	काष्ठा ktermios ktermios = tty->termios;

	ktermios.c_cflag &= ~(PARENB | PARODD | CMSPAR);
	अगर (parity != SERDEV_PARITY_NONE) अणु
		ktermios.c_cflag |= PARENB;
		अगर (parity == SERDEV_PARITY_ODD)
			ktermios.c_cflag |= PARODD;
	पूर्ण

	tty_set_termios(tty, &ktermios);

	अगर ((tty->termios.c_cflag & (PARENB | PARODD | CMSPAR)) !=
	    (ktermios.c_cflag & (PARENB | PARODD | CMSPAR)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम ttyport_रुको_until_sent(काष्ठा serdev_controller *ctrl, दीर्घ समयout)
अणु
	काष्ठा serport *serport = serdev_controller_get_drvdata(ctrl);
	काष्ठा tty_काष्ठा *tty = serport->tty;

	tty_रुको_until_sent(tty, समयout);
पूर्ण

अटल पूर्णांक ttyport_get_tiocm(काष्ठा serdev_controller *ctrl)
अणु
	काष्ठा serport *serport = serdev_controller_get_drvdata(ctrl);
	काष्ठा tty_काष्ठा *tty = serport->tty;

	अगर (!tty->ops->tiocmget)
		वापस -ENOTSUPP;

	वापस tty->ops->tiocmget(tty);
पूर्ण

अटल पूर्णांक ttyport_set_tiocm(काष्ठा serdev_controller *ctrl, अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear)
अणु
	काष्ठा serport *serport = serdev_controller_get_drvdata(ctrl);
	काष्ठा tty_काष्ठा *tty = serport->tty;

	अगर (!tty->ops->tiocmset)
		वापस -ENOTSUPP;

	वापस tty->ops->tiocmset(tty, set, clear);
पूर्ण

अटल स्थिर काष्ठा serdev_controller_ops ctrl_ops = अणु
	.ग_लिखो_buf = ttyport_ग_लिखो_buf,
	.ग_लिखो_flush = ttyport_ग_लिखो_flush,
	.ग_लिखो_room = ttyport_ग_लिखो_room,
	.खोलो = ttyport_खोलो,
	.बंद = ttyport_बंद,
	.set_flow_control = ttyport_set_flow_control,
	.set_parity = ttyport_set_parity,
	.set_baudrate = ttyport_set_baudrate,
	.रुको_until_sent = ttyport_रुको_until_sent,
	.get_tiocm = ttyport_get_tiocm,
	.set_tiocm = ttyport_set_tiocm,
पूर्ण;

काष्ठा device *serdev_tty_port_रेजिस्टर(काष्ठा tty_port *port,
					काष्ठा device *parent,
					काष्ठा tty_driver *drv, पूर्णांक idx)
अणु
	काष्ठा serdev_controller *ctrl;
	काष्ठा serport *serport;
	पूर्णांक ret;

	अगर (!port || !drv || !parent)
		वापस ERR_PTR(-ENODEV);

	ctrl = serdev_controller_alloc(parent, माप(काष्ठा serport));
	अगर (!ctrl)
		वापस ERR_PTR(-ENOMEM);
	serport = serdev_controller_get_drvdata(ctrl);

	serport->port = port;
	serport->tty_idx = idx;
	serport->tty_drv = drv;

	ctrl->ops = &ctrl_ops;

	port->client_ops = &client_ops;
	port->client_data = ctrl;

	ret = serdev_controller_add(ctrl);
	अगर (ret)
		जाओ err_reset_data;

	dev_info(&ctrl->dev, "tty port %s%d registered\n", drv->name, idx);
	वापस &ctrl->dev;

err_reset_data:
	port->client_data = शून्य;
	port->client_ops = &tty_port_शेष_client_ops;
	serdev_controller_put(ctrl);

	वापस ERR_PTR(ret);
पूर्ण

पूर्णांक serdev_tty_port_unरेजिस्टर(काष्ठा tty_port *port)
अणु
	काष्ठा serdev_controller *ctrl = port->client_data;
	काष्ठा serport *serport = serdev_controller_get_drvdata(ctrl);

	अगर (!serport)
		वापस -ENODEV;

	serdev_controller_हटाओ(ctrl);
	port->client_data = शून्य;
	port->client_ops = &tty_port_शेष_client_ops;
	serdev_controller_put(ctrl);

	वापस 0;
पूर्ण
