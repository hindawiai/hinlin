<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * nvec_ps2: mouse driver क्रम a NVIDIA compliant embedded controller
 *
 * Copyright (C) 2011 The AC100 Kernel Team <ac100@lists.launchpad.net>
 *
 * Authors:  Pierre-Hugues Husson <phhusson@मुक्त.fr>
 *           Ilya Petrov <ilya.muromec@gmail.com>
 *           Marc Dietrich <marvin24@gmx.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/serपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "nvec.h"

#घोषणा PACKET_SIZE	6

#घोषणा ENABLE_MOUSE	0xf4
#घोषणा DISABLE_MOUSE	0xf5
#घोषणा PSMOUSE_RST	0xff

#अगर_घोषित NVEC_PS2_DEBUG
#घोषणा NVEC_PHD(str, buf, len) \
	prपूर्णांक_hex_dump(KERN_DEBUG, str, DUMP_PREFIX_NONE, \
			16, 1, buf, len, false)
#अन्यथा
#घोषणा NVEC_PHD(str, buf, len) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

क्रमागत ps2_subcmds अणु
	SEND_COMMAND = 1,
	RECEIVE_N,
	AUTO_RECEIVE_N,
	CANCEL_AUTO_RECEIVE,
पूर्ण;

काष्ठा nvec_ps2 अणु
	काष्ठा serio *ser_dev;
	काष्ठा notअगरier_block notअगरier;
	काष्ठा nvec_chip *nvec;
पूर्ण;

अटल काष्ठा nvec_ps2 ps2_dev;

अटल पूर्णांक ps2_startstreaming(काष्ठा serio *ser_dev)
अणु
	अचिन्हित अक्षर buf[] = अणु NVEC_PS2, AUTO_RECEIVE_N, PACKET_SIZE पूर्ण;

	वापस nvec_ग_लिखो_async(ps2_dev.nvec, buf, माप(buf));
पूर्ण

अटल व्योम ps2_stopstreaming(काष्ठा serio *ser_dev)
अणु
	अचिन्हित अक्षर buf[] = अणु NVEC_PS2, CANCEL_AUTO_RECEIVE पूर्ण;

	nvec_ग_लिखो_async(ps2_dev.nvec, buf, माप(buf));
पूर्ण

अटल पूर्णांक ps2_sendcommand(काष्ठा serio *ser_dev, अचिन्हित अक्षर cmd)
अणु
	अचिन्हित अक्षर buf[] = अणु NVEC_PS2, SEND_COMMAND, ENABLE_MOUSE, 1 पूर्ण;

	buf[2] = cmd & 0xff;

	dev_dbg(&ser_dev->dev, "Sending ps2 cmd %02x\n", cmd);
	वापस nvec_ग_लिखो_async(ps2_dev.nvec, buf, माप(buf));
पूर्ण

अटल पूर्णांक nvec_ps2_notअगरier(काष्ठा notअगरier_block *nb,
			     अचिन्हित दीर्घ event_type, व्योम *data)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर *msg = data;

	चयन (event_type) अणु
	हाल NVEC_PS2_EVT:
		क्रम (i = 0; i < msg[1]; i++)
			serio_पूर्णांकerrupt(ps2_dev.ser_dev, msg[2 + i], 0);
		NVEC_PHD("ps/2 mouse event: ", &msg[2], msg[1]);
		वापस NOTIFY_STOP;

	हाल NVEC_PS2:
		अगर (msg[2] == 1) अणु
			क्रम (i = 0; i < (msg[1] - 2); i++)
				serio_पूर्णांकerrupt(ps2_dev.ser_dev, msg[i + 4], 0);
			NVEC_PHD("ps/2 mouse reply: ", &msg[4], msg[1] - 2);
		पूर्ण

		अन्यथा अगर (msg[1] != 2) /* !ack */
			NVEC_PHD("unhandled mouse event: ", msg, msg[1] + 2);
		वापस NOTIFY_STOP;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक nvec_mouse_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nvec_chip *nvec = dev_get_drvdata(pdev->dev.parent);
	काष्ठा serio *ser_dev;

	ser_dev = kzalloc(माप(*ser_dev), GFP_KERNEL);
	अगर (!ser_dev)
		वापस -ENOMEM;

	ser_dev->id.type = SERIO_8042;
	ser_dev->ग_लिखो = ps2_sendcommand;
	ser_dev->start = ps2_startstreaming;
	ser_dev->stop = ps2_stopstreaming;

	strscpy(ser_dev->name, "nvec mouse", माप(ser_dev->name));
	strscpy(ser_dev->phys, "nvec", माप(ser_dev->phys));

	ps2_dev.ser_dev = ser_dev;
	ps2_dev.notअगरier.notअगरier_call = nvec_ps2_notअगरier;
	ps2_dev.nvec = nvec;
	nvec_रेजिस्टर_notअगरier(nvec, &ps2_dev.notअगरier, 0);

	serio_रेजिस्टर_port(ser_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक nvec_mouse_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nvec_chip *nvec = dev_get_drvdata(pdev->dev.parent);

	ps2_sendcommand(ps2_dev.ser_dev, DISABLE_MOUSE);
	ps2_stopstreaming(ps2_dev.ser_dev);
	nvec_unरेजिस्टर_notअगरier(nvec, &ps2_dev.notअगरier);
	serio_unरेजिस्टर_port(ps2_dev.ser_dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक nvec_mouse_suspend(काष्ठा device *dev)
अणु
	/* disable mouse */
	ps2_sendcommand(ps2_dev.ser_dev, DISABLE_MOUSE);

	/* send cancel स्वतःreceive */
	ps2_stopstreaming(ps2_dev.ser_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक nvec_mouse_resume(काष्ठा device *dev)
अणु
	/* start streaming */
	ps2_startstreaming(ps2_dev.ser_dev);

	/* enable mouse */
	ps2_sendcommand(ps2_dev.ser_dev, ENABLE_MOUSE);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(nvec_mouse_pm_ops, nvec_mouse_suspend,
			 nvec_mouse_resume);

अटल काष्ठा platक्रमm_driver nvec_mouse_driver = अणु
	.probe  = nvec_mouse_probe,
	.हटाओ = nvec_mouse_हटाओ,
	.driver = अणु
		.name = "nvec-mouse",
		.pm = &nvec_mouse_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(nvec_mouse_driver);

MODULE_DESCRIPTION("NVEC mouse driver");
MODULE_AUTHOR("Marc Dietrich <marvin24@gmx.de>");
MODULE_ALIAS("platform:nvec-mouse");
MODULE_LICENSE("GPL");
