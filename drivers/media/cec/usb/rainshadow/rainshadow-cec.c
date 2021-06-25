<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RainShaकरोw Tech HDMI CEC driver
 *
 * Copyright 2016 Hans Verkuil <hverkuil@xs4all.nl
 */

/*
 * Notes:
 *
 * The higher level protocols are currently disabled. This can be added
 * later, similar to how this is करोne क्रम the Pulse Eight CEC driver.
 *
 * Documentation of the protocol is available here:
 *
 * http://rainshaकरोwtech.com/करोc/HDMICECtoUSBandRS232v2.0.pdf
 */

#समावेश <linux/completion.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/serपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समय.स>
#समावेश <linux/workqueue.h>

#समावेश <media/cec.h>

MODULE_AUTHOR("Hans Verkuil <hverkuil@xs4all.nl>");
MODULE_DESCRIPTION("RainShadow Tech HDMI CEC driver");
MODULE_LICENSE("GPL");

#घोषणा DATA_SIZE 256

काष्ठा rain अणु
	काष्ठा device *dev;
	काष्ठा serio *serio;
	काष्ठा cec_adapter *adap;
	काष्ठा completion cmd_करोne;
	काष्ठा work_काष्ठा work;

	/* Low-level ringbuffer, collecting incoming अक्षरacters */
	अक्षर buf[DATA_SIZE];
	अचिन्हित पूर्णांक buf_rd_idx;
	अचिन्हित पूर्णांक buf_wr_idx;
	अचिन्हित पूर्णांक buf_len;
	spinlock_t buf_lock;

	/* command buffer */
	अक्षर cmd[DATA_SIZE];
	अचिन्हित पूर्णांक cmd_idx;
	bool cmd_started;

	/* reply to a command, only used to store the firmware version */
	अक्षर cmd_reply[DATA_SIZE];

	काष्ठा mutex ग_लिखो_lock;
पूर्ण;

अटल व्योम rain_process_msg(काष्ठा rain *rain)
अणु
	काष्ठा cec_msg msg = अणुपूर्ण;
	स्थिर अक्षर *cmd = rain->cmd + 3;
	पूर्णांक stat = -1;

	क्रम (; *cmd; cmd++) अणु
		अगर (!है_षष्ठादशक(*cmd))
			जारी;
		अगर (है_षष्ठादशक(cmd[0]) && है_षष्ठादशक(cmd[1])) अणु
			अगर (msg.len == CEC_MAX_MSG_SIZE)
				अवरोध;
			अगर (hex2bin(msg.msg + msg.len, cmd, 1))
				जारी;
			msg.len++;
			cmd++;
			जारी;
		पूर्ण
		अगर (!cmd[1])
			stat = hex_to_bin(cmd[0]);
		अवरोध;
	पूर्ण

	अगर (rain->cmd[0] == 'R') अणु
		अगर (stat == 1 || stat == 2)
			cec_received_msg(rain->adap, &msg);
		वापस;
	पूर्ण

	चयन (stat) अणु
	हाल 1:
		cec_transmit_attempt_करोne(rain->adap, CEC_TX_STATUS_OK);
		अवरोध;
	हाल 2:
		cec_transmit_attempt_करोne(rain->adap, CEC_TX_STATUS_NACK);
		अवरोध;
	शेष:
		cec_transmit_attempt_करोne(rain->adap, CEC_TX_STATUS_LOW_DRIVE);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rain_irq_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rain *rain =
		container_of(work, काष्ठा rain, work);

	जबतक (true) अणु
		अचिन्हित दीर्घ flags;
		अक्षर data;

		spin_lock_irqsave(&rain->buf_lock, flags);
		अगर (!rain->buf_len) अणु
			spin_unlock_irqrestore(&rain->buf_lock, flags);
			अवरोध;
		पूर्ण

		data = rain->buf[rain->buf_rd_idx];
		rain->buf_len--;
		rain->buf_rd_idx = (rain->buf_rd_idx + 1) & 0xff;

		spin_unlock_irqrestore(&rain->buf_lock, flags);

		अगर (!rain->cmd_started && data != '?')
			जारी;

		चयन (data) अणु
		हाल '\r':
			rain->cmd[rain->cmd_idx] = '\0';
			dev_dbg(rain->dev, "received: %s\n", rain->cmd);
			अगर (!स_भेद(rain->cmd, "REC", 3) ||
			    !स_भेद(rain->cmd, "STA", 3)) अणु
				rain_process_msg(rain);
			पूर्ण अन्यथा अणु
				strscpy(rain->cmd_reply, rain->cmd,
					माप(rain->cmd_reply));
				complete(&rain->cmd_करोne);
			पूर्ण
			rain->cmd_idx = 0;
			rain->cmd_started = false;
			अवरोध;

		हाल '\n':
			rain->cmd_idx = 0;
			rain->cmd_started = false;
			अवरोध;

		हाल '?':
			rain->cmd_idx = 0;
			rain->cmd_started = true;
			अवरोध;

		शेष:
			अगर (rain->cmd_idx >= DATA_SIZE - 1) अणु
				dev_dbg(rain->dev,
					"throwing away %d bytes of garbage\n", rain->cmd_idx);
				rain->cmd_idx = 0;
			पूर्ण
			rain->cmd[rain->cmd_idx++] = data;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t rain_पूर्णांकerrupt(काष्ठा serio *serio, अचिन्हित अक्षर data,
				    अचिन्हित पूर्णांक flags)
अणु
	काष्ठा rain *rain = serio_get_drvdata(serio);

	अगर (rain->buf_len == DATA_SIZE) अणु
		dev_warn_once(rain->dev, "buffer overflow\n");
		वापस IRQ_HANDLED;
	पूर्ण
	spin_lock(&rain->buf_lock);
	rain->buf_len++;
	rain->buf[rain->buf_wr_idx] = data;
	rain->buf_wr_idx = (rain->buf_wr_idx + 1) & 0xff;
	spin_unlock(&rain->buf_lock);
	schedule_work(&rain->work);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rain_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा rain *rain = serio_get_drvdata(serio);

	cancel_work_sync(&rain->work);
	cec_unरेजिस्टर_adapter(rain->adap);
	dev_info(&serio->dev, "disconnected\n");
	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	kमुक्त(rain);
पूर्ण

अटल पूर्णांक rain_send(काष्ठा rain *rain, स्थिर अक्षर *command)
अणु
	पूर्णांक err = serio_ग_लिखो(rain->serio, '!');

	dev_dbg(rain->dev, "send: %s\n", command);
	जबतक (!err && *command)
		err = serio_ग_लिखो(rain->serio, *command++);
	अगर (!err)
		err = serio_ग_लिखो(rain->serio, '~');

	वापस err;
पूर्ण

अटल पूर्णांक rain_send_and_रुको(काष्ठा rain *rain,
			      स्थिर अक्षर *cmd, स्थिर अक्षर *reply)
अणु
	पूर्णांक err;

	init_completion(&rain->cmd_करोne);

	mutex_lock(&rain->ग_लिखो_lock);
	err = rain_send(rain, cmd);
	अगर (err)
		जाओ err;

	अगर (!रुको_क्रम_completion_समयout(&rain->cmd_करोne, HZ)) अणु
		err = -ETIMEDOUT;
		जाओ err;
	पूर्ण
	अगर (reply && म_भेदन(rain->cmd_reply, reply, म_माप(reply))) अणु
		dev_dbg(rain->dev,
			 "transmit of '%s': received '%s' instead of '%s'\n",
			 cmd, rain->cmd_reply, reply);
		err = -EIO;
	पूर्ण
err:
	mutex_unlock(&rain->ग_लिखो_lock);
	वापस err;
पूर्ण

अटल पूर्णांक rain_setup(काष्ठा rain *rain, काष्ठा serio *serio,
			काष्ठा cec_log_addrs *log_addrs, u16 *pa)
अणु
	पूर्णांक err;

	err = rain_send_and_रुको(rain, "R", "REV");
	अगर (err)
		वापस err;
	dev_info(rain->dev, "Firmware version %s\n", rain->cmd_reply + 4);

	err = rain_send_and_रुको(rain, "Q 1", "QTY");
	अगर (err)
		वापस err;
	err = rain_send_and_रुको(rain, "c0000", "CFG");
	अगर (err)
		वापस err;
	वापस rain_send_and_रुको(rain, "A F 0000", "ADR");
पूर्ण

अटल पूर्णांक rain_cec_adap_enable(काष्ठा cec_adapter *adap, bool enable)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक rain_cec_adap_log_addr(काष्ठा cec_adapter *adap, u8 log_addr)
अणु
	काष्ठा rain *rain = cec_get_drvdata(adap);
	u8 cmd[16];

	अगर (log_addr == CEC_LOG_ADDR_INVALID)
		log_addr = CEC_LOG_ADDR_UNREGISTERED;
	snम_लिखो(cmd, माप(cmd), "A %x", log_addr);
	वापस rain_send_and_रुको(rain, cmd, "ADR");
पूर्ण

अटल पूर्णांक rain_cec_adap_transmit(काष्ठा cec_adapter *adap, u8 attempts,
				    u32 संकेत_मुक्त_समय, काष्ठा cec_msg *msg)
अणु
	काष्ठा rain *rain = cec_get_drvdata(adap);
	अक्षर cmd[2 * CEC_MAX_MSG_SIZE + 16];
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	अगर (msg->len == 1) अणु
		snम_लिखो(cmd, माप(cmd), "x%x", cec_msg_destination(msg));
	पूर्ण अन्यथा अणु
		अक्षर hex[3];

		snम_लिखो(cmd, माप(cmd), "x%x %02x ",
			 cec_msg_destination(msg), msg->msg[1]);
		क्रम (i = 2; i < msg->len; i++) अणु
			snम_लिखो(hex, माप(hex), "%02x", msg->msg[i]);
			strlcat(cmd, hex, माप(cmd));
		पूर्ण
	पूर्ण
	mutex_lock(&rain->ग_लिखो_lock);
	err = rain_send(rain, cmd);
	mutex_unlock(&rain->ग_लिखो_lock);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा cec_adap_ops rain_cec_adap_ops = अणु
	.adap_enable = rain_cec_adap_enable,
	.adap_log_addr = rain_cec_adap_log_addr,
	.adap_transmit = rain_cec_adap_transmit,
पूर्ण;

अटल पूर्णांक rain_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	u32 caps = CEC_CAP_DEFAULTS | CEC_CAP_PHYS_ADDR | CEC_CAP_MONITOR_ALL;
	काष्ठा rain *rain;
	पूर्णांक err = -ENOMEM;
	काष्ठा cec_log_addrs log_addrs = अणुपूर्ण;
	u16 pa = CEC_PHYS_ADDR_INVALID;

	rain = kzalloc(माप(*rain), GFP_KERNEL);

	अगर (!rain)
		वापस -ENOMEM;

	rain->serio = serio;
	rain->adap = cec_allocate_adapter(&rain_cec_adap_ops, rain,
					  dev_name(&serio->dev), caps, 1);
	err = PTR_ERR_OR_ZERO(rain->adap);
	अगर (err < 0)
		जाओ मुक्त_device;

	rain->dev = &serio->dev;
	serio_set_drvdata(serio, rain);
	INIT_WORK(&rain->work, rain_irq_work_handler);
	mutex_init(&rain->ग_लिखो_lock);
	spin_lock_init(&rain->buf_lock);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ delete_adap;

	err = rain_setup(rain, serio, &log_addrs, &pa);
	अगर (err)
		जाओ बंद_serio;

	err = cec_रेजिस्टर_adapter(rain->adap, &serio->dev);
	अगर (err < 0)
		जाओ बंद_serio;

	rain->dev = &rain->adap->devnode.dev;
	वापस 0;

बंद_serio:
	serio_बंद(serio);
delete_adap:
	cec_delete_adapter(rain->adap);
	serio_set_drvdata(serio, शून्य);
मुक्त_device:
	kमुक्त(rain);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा serio_device_id rain_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_RAINSHADOW_CEC,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, rain_serio_ids);

अटल काष्ठा serio_driver rain_drv = अणु
	.driver		= अणु
		.name	= "rainshadow-cec",
	पूर्ण,
	.description	= "RainShadow Tech HDMI CEC driver",
	.id_table	= rain_serio_ids,
	.पूर्णांकerrupt	= rain_पूर्णांकerrupt,
	.connect	= rain_connect,
	.disconnect	= rain_disconnect,
पूर्ण;

module_serio_driver(rain_drv);
