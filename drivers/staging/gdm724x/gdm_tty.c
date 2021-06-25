<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2012 GCT Semiconductor, Inc. All rights reserved. */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb/cdc.h>
#समावेश <linux/serial.h>
#समावेश "gdm_tty.h"

#घोषणा GDM_TTY_MAJOR 0
#घोषणा GDM_TTY_MINOR 32

#घोषणा ACM_CTRL_DTR 0x01
#घोषणा ACM_CTRL_RTS 0x02
#घोषणा ACM_CTRL_DSR 0x02
#घोषणा ACM_CTRL_RI  0x08
#घोषणा ACM_CTRL_DCD 0x01

#घोषणा WRITE_SIZE 2048

#घोषणा MUX_TX_MAX_SIZE 2048

#घोषणा GDM_TTY_READY(gdm) (gdm && gdm->tty_dev && gdm->port.count)

अटल काष्ठा tty_driver *gdm_driver[TTY_MAX_COUNT];
अटल काष्ठा gdm *gdm_table[TTY_MAX_COUNT][GDM_TTY_MINOR];
अटल DEFINE_MUTEX(gdm_table_lock);

अटल स्थिर अक्षर *DRIVER_STRING[TTY_MAX_COUNT] = अणु"GCTATC", "GCTDM"पूर्ण;
अटल अक्षर *DEVICE_STRING[TTY_MAX_COUNT] = अणु"GCT-ATC", "GCT-DM"पूर्ण;

अटल व्योम gdm_port_deकाष्ठा(काष्ठा tty_port *port)
अणु
	काष्ठा gdm *gdm = container_of(port, काष्ठा gdm, port);

	mutex_lock(&gdm_table_lock);
	gdm_table[gdm->index][gdm->minor] = शून्य;
	mutex_unlock(&gdm_table_lock);

	kमुक्त(gdm);
पूर्ण

अटल स्थिर काष्ठा tty_port_operations gdm_port_ops = अणु
	.deकाष्ठा = gdm_port_deकाष्ठा,
पूर्ण;

अटल पूर्णांक gdm_tty_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gdm *gdm = शून्य;
	पूर्णांक ret;

	ret = match_string(DRIVER_STRING, TTY_MAX_COUNT,
			   tty->driver->driver_name);
	अगर (ret < 0)
		वापस -ENODEV;

	mutex_lock(&gdm_table_lock);
	gdm = gdm_table[ret][tty->index];
	अगर (!gdm) अणु
		mutex_unlock(&gdm_table_lock);
		वापस -ENODEV;
	पूर्ण

	tty_port_get(&gdm->port);

	ret = tty_standard_install(driver, tty);
	अगर (ret) अणु
		tty_port_put(&gdm->port);
		mutex_unlock(&gdm_table_lock);
		वापस ret;
	पूर्ण

	tty->driver_data = gdm;
	mutex_unlock(&gdm_table_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक gdm_tty_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा gdm *gdm = tty->driver_data;

	वापस tty_port_खोलो(&gdm->port, tty, filp);
पूर्ण

अटल व्योम gdm_tty_cleanup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gdm *gdm = tty->driver_data;

	tty_port_put(&gdm->port);
पूर्ण

अटल व्योम gdm_tty_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gdm *gdm = tty->driver_data;

	tty_port_hangup(&gdm->port);
पूर्ण

अटल व्योम gdm_tty_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा gdm *gdm = tty->driver_data;

	tty_port_बंद(&gdm->port, tty, filp);
पूर्ण

अटल पूर्णांक gdm_tty_recv_complete(व्योम *data,
				 पूर्णांक len,
				 पूर्णांक index,
				 काष्ठा tty_dev *tty_dev,
				 पूर्णांक complete)
अणु
	काष्ठा gdm *gdm = tty_dev->gdm[index];

	अगर (!GDM_TTY_READY(gdm)) अणु
		अगर (complete == RECV_PACKET_PROCESS_COMPLETE)
			gdm->tty_dev->recv_func(gdm->tty_dev->priv_dev,
						gdm_tty_recv_complete);
		वापस TO_HOST_PORT_CLOSE;
	पूर्ण

	अगर (data && len) अणु
		अगर (tty_buffer_request_room(&gdm->port, len) == len) अणु
			tty_insert_flip_string(&gdm->port, data, len);
			tty_flip_buffer_push(&gdm->port);
		पूर्ण अन्यथा अणु
			वापस TO_HOST_BUFFER_REQUEST_FAIL;
		पूर्ण
	पूर्ण

	अगर (complete == RECV_PACKET_PROCESS_COMPLETE)
		gdm->tty_dev->recv_func(gdm->tty_dev->priv_dev,
					gdm_tty_recv_complete);

	वापस 0;
पूर्ण

अटल व्योम gdm_tty_send_complete(व्योम *arg)
अणु
	काष्ठा gdm *gdm = arg;

	अगर (!GDM_TTY_READY(gdm))
		वापस;

	tty_port_tty_wakeup(&gdm->port);
पूर्ण

अटल पूर्णांक gdm_tty_ग_लिखो(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *buf,
			 पूर्णांक len)
अणु
	काष्ठा gdm *gdm = tty->driver_data;
	पूर्णांक reमुख्य = len;
	पूर्णांक sent_len = 0;
	पूर्णांक sending_len = 0;

	अगर (!GDM_TTY_READY(gdm))
		वापस -ENODEV;

	अगर (!len)
		वापस 0;

	जबतक (1) अणु
		sending_len = min(MUX_TX_MAX_SIZE, reमुख्य);
		gdm->tty_dev->send_func(gdm->tty_dev->priv_dev,
					(व्योम *)(buf + sent_len),
					sending_len,
					gdm->index,
					gdm_tty_send_complete,
					gdm);
		sent_len += sending_len;
		reमुख्य -= sending_len;
		अगर (reमुख्य <= 0)
			अवरोध;
	पूर्ण

	वापस len;
पूर्ण

अटल पूर्णांक gdm_tty_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा gdm *gdm = tty->driver_data;

	अगर (!GDM_TTY_READY(gdm))
		वापस 0;

	वापस WRITE_SIZE;
पूर्ण

पूर्णांक रेजिस्टर_lte_tty_device(काष्ठा tty_dev *tty_dev, काष्ठा device *device)
अणु
	काष्ठा gdm *gdm;
	पूर्णांक i;
	पूर्णांक j;

	क्रम (i = 0; i < TTY_MAX_COUNT; i++) अणु
		gdm = kदो_स्मृति(माप(*gdm), GFP_KERNEL);
		अगर (!gdm)
			वापस -ENOMEM;

		mutex_lock(&gdm_table_lock);
		क्रम (j = 0; j < GDM_TTY_MINOR; j++) अणु
			अगर (!gdm_table[i][j])
				अवरोध;
		पूर्ण

		अगर (j == GDM_TTY_MINOR) अणु
			kमुक्त(gdm);
			mutex_unlock(&gdm_table_lock);
			वापस -EINVAL;
		पूर्ण

		gdm_table[i][j] = gdm;
		mutex_unlock(&gdm_table_lock);

		tty_dev->gdm[i] = gdm;
		tty_port_init(&gdm->port);

		gdm->port.ops = &gdm_port_ops;
		gdm->index = i;
		gdm->minor = j;
		gdm->tty_dev = tty_dev;

		tty_port_रेजिस्टर_device(&gdm->port, gdm_driver[i],
					 gdm->minor, device);
	पूर्ण

	क्रम (i = 0; i < MAX_ISSUE_NUM; i++)
		gdm->tty_dev->recv_func(gdm->tty_dev->priv_dev,
					gdm_tty_recv_complete);

	वापस 0;
पूर्ण

व्योम unरेजिस्टर_lte_tty_device(काष्ठा tty_dev *tty_dev)
अणु
	काष्ठा gdm *gdm;
	काष्ठा tty_काष्ठा *tty;
	पूर्णांक i;

	क्रम (i = 0; i < TTY_MAX_COUNT; i++) अणु
		gdm = tty_dev->gdm[i];
		अगर (!gdm)
			जारी;

		mutex_lock(&gdm_table_lock);
		gdm_table[gdm->index][gdm->minor] = शून्य;
		mutex_unlock(&gdm_table_lock);

		tty = tty_port_tty_get(&gdm->port);
		अगर (tty) अणु
			tty_vhangup(tty);
			tty_kref_put(tty);
		पूर्ण

		tty_unरेजिस्टर_device(gdm_driver[i], gdm->minor);
		tty_port_put(&gdm->port);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा tty_operations gdm_tty_ops = अणु
	.install =	gdm_tty_install,
	.खोलो =		gdm_tty_खोलो,
	.बंद =	gdm_tty_बंद,
	.cleanup =	gdm_tty_cleanup,
	.hangup =	gdm_tty_hangup,
	.ग_लिखो =	gdm_tty_ग_लिखो,
	.ग_लिखो_room =	gdm_tty_ग_लिखो_room,
पूर्ण;

पूर्णांक रेजिस्टर_lte_tty_driver(व्योम)
अणु
	काष्ठा tty_driver *tty_driver;
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < TTY_MAX_COUNT; i++) अणु
		tty_driver = alloc_tty_driver(GDM_TTY_MINOR);
		अगर (!tty_driver)
			वापस -ENOMEM;

		tty_driver->owner = THIS_MODULE;
		tty_driver->driver_name = DRIVER_STRING[i];
		tty_driver->name = DEVICE_STRING[i];
		tty_driver->major = GDM_TTY_MAJOR;
		tty_driver->type = TTY_DRIVER_TYPE_SERIAL;
		tty_driver->subtype = SERIAL_TYPE_NORMAL;
		tty_driver->flags = TTY_DRIVER_REAL_RAW |
					TTY_DRIVER_DYNAMIC_DEV;
		tty_driver->init_termios = tty_std_termios;
		tty_driver->init_termios.c_cflag = B9600 | CS8 | HUPCL | CLOCAL;
		tty_driver->init_termios.c_lflag = ISIG | ICANON | IEXTEN;
		tty_set_operations(tty_driver, &gdm_tty_ops);

		ret = tty_रेजिस्टर_driver(tty_driver);
		अगर (ret) अणु
			put_tty_driver(tty_driver);
			वापस ret;
		पूर्ण

		gdm_driver[i] = tty_driver;
	पूर्ण

	वापस ret;
पूर्ण

व्योम unरेजिस्टर_lte_tty_driver(व्योम)
अणु
	काष्ठा tty_driver *tty_driver;
	पूर्णांक i;

	क्रम (i = 0; i < TTY_MAX_COUNT; i++) अणु
		tty_driver = gdm_driver[i];
		अगर (tty_driver) अणु
			tty_unरेजिस्टर_driver(tty_driver);
			put_tty_driver(tty_driver);
		पूर्ण
	पूर्ण
पूर्ण

