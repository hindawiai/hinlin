<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम the OLPC XO-1.75 Embedded Controller.
 *
 * The EC protocol is करोcumented at:
 * http://wiki.laptop.org/go/XO_1.75_HOST_to_EC_Protocol
 *
 * Copyright (C) 2010 One Laptop per Child Foundation.
 * Copyright (C) 2018 Lubomir Rपूर्णांकel <lkundrak@v3.sk>
 */

#समावेश <linux/completion.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/input.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/module.h>
#समावेश <linux/olpc-ec.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/reboot.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/spi/spi.h>

काष्ठा ec_cmd_t अणु
	u8 cmd;
	u8 bytes_वापसed;
पूर्ण;

क्रमागत ec_chan_t अणु
	CHAN_NONE = 0,
	CHAN_SWITCH,
	CHAN_CMD_RESP,
	CHAN_KEYBOARD,
	CHAN_TOUCHPAD,
	CHAN_EVENT,
	CHAN_DEBUG,
	CHAN_CMD_ERROR,
पूर्ण;

/*
 * EC events
 */
#घोषणा EVENT_AC_CHANGE			1  /* AC plugged/unplugged */
#घोषणा EVENT_BATTERY_STATUS		2  /* Battery low/full/error/gone */
#घोषणा EVENT_BATTERY_CRITICAL		3  /* Battery critical voltage */
#घोषणा EVENT_BATTERY_SOC_CHANGE	4  /* 1% SOC Change */
#घोषणा EVENT_BATTERY_ERROR		5  /* Abnormal error, query क्रम cause */
#घोषणा EVENT_POWER_PRESSED		6  /* Power button was pressed */
#घोषणा EVENT_POWER_PRESS_WAKE		7  /* Woken up with a घातer button */
#घोषणा EVENT_TIMED_HOST_WAKE		8  /* Host wake समयr */
#घोषणा EVENT_OLS_HIGH_LIMIT		9  /* OLS crossed dark threshold */
#घोषणा EVENT_OLS_LOW_LIMIT		10 /* OLS crossed light threshold */

/*
 * EC commands
 * (from http://dev.laptop.org/git/users/rsmith/ec-1.75/tree/ec_cmd.h)
 */
#घोषणा CMD_GET_API_VERSION		0x08 /* out: u8 */
#घोषणा CMD_READ_VOLTAGE		0x10 /* out: u16, *9.76/32, mV */
#घोषणा CMD_READ_CURRENT		0x11 /* out: s16, *15.625/120, mA */
#घोषणा CMD_READ_ACR			0x12 /* out: s16, *6250/15, uAh */
#घोषणा CMD_READ_BATT_TEMPERATURE	0x13 /* out: u16, *100/256, deg C */
#घोषणा CMD_READ_AMBIENT_TEMPERATURE	0x14 /* unimplemented, no hardware */
#घोषणा CMD_READ_BATTERY_STATUS		0x15 /* out: u8, biपंचांगask */
#घोषणा CMD_READ_SOC			0x16 /* out: u8, percentage */
#घोषणा CMD_READ_GAUGE_ID		0x17 /* out: u8 * 8 */
#घोषणा CMD_READ_GAUGE_DATA		0x18 /* in: u8 addr, out: u8 data */
#घोषणा CMD_READ_BOARD_ID		0x19 /* out: u16 (platक्रमm id) */
#घोषणा CMD_READ_BATT_ERR_CODE		0x1f /* out: u8, error biपंचांगask */
#घोषणा CMD_SET_DCON_POWER		0x26 /* in: u8 */
#घोषणा CMD_RESET_EC			0x28 /* none */
#घोषणा CMD_READ_BATTERY_TYPE		0x2c /* out: u8 */
#घोषणा CMD_SET_AUTOWAK			0x33 /* out: u8 */
#घोषणा CMD_SET_EC_WAKEUP_TIMER		0x36 /* in: u32, out: ? */
#घोषणा CMD_READ_EXT_SCI_MASK		0x37 /* ? */
#घोषणा CMD_WRITE_EXT_SCI_MASK		0x38 /* ? */
#घोषणा CMD_CLEAR_EC_WAKEUP_TIMER	0x39 /* none */
#घोषणा CMD_ENABLE_RUNIN_DISCHARGE	0x3B /* none */
#घोषणा CMD_DISABLE_RUNIN_DISCHARGE	0x3C /* none */
#घोषणा CMD_READ_MPPT_ACTIVE		0x3d /* out: u8 */
#घोषणा CMD_READ_MPPT_LIMIT		0x3e /* out: u8 */
#घोषणा CMD_SET_MPPT_LIMIT		0x3f /* in: u8 */
#घोषणा CMD_DISABLE_MPPT		0x40 /* none */
#घोषणा CMD_ENABLE_MPPT			0x41 /* none */
#घोषणा CMD_READ_VIN			0x42 /* out: u16 */
#घोषणा CMD_EXT_SCI_QUERY		0x43 /* ? */
#घोषणा RSP_KEYBOARD_DATA		0x48 /* ? */
#घोषणा RSP_TOUCHPAD_DATA		0x49 /* ? */
#घोषणा CMD_GET_FW_VERSION		0x4a /* out: u8 * 16 */
#घोषणा CMD_POWER_CYCLE			0x4b /* none */
#घोषणा CMD_POWER_OFF			0x4c /* none */
#घोषणा CMD_RESET_EC_SOFT		0x4d /* none */
#घोषणा CMD_READ_GAUGE_U16		0x4e /* ? */
#घोषणा CMD_ENABLE_MOUSE		0x4f /* ? */
#घोषणा CMD_ECHO			0x52 /* in: u8 * 5, out: u8 * 5 */
#घोषणा CMD_GET_FW_DATE			0x53 /* out: u8 * 16 */
#घोषणा CMD_GET_FW_USER			0x54 /* out: u8 * 16 */
#घोषणा CMD_TURN_OFF_POWER		0x55 /* none (same as 0x4c) */
#घोषणा CMD_READ_OLS			0x56 /* out: u16 */
#घोषणा CMD_OLS_SMT_LEDON		0x57 /* none */
#घोषणा CMD_OLS_SMT_LEDOFF		0x58 /* none */
#घोषणा CMD_START_OLS_ASSY		0x59 /* none */
#घोषणा CMD_STOP_OLS_ASSY		0x5a /* none */
#घोषणा CMD_OLS_SMTTEST_STOP		0x5b /* none */
#घोषणा CMD_READ_VIN_SCALED		0x5c /* out: u16 */
#घोषणा CMD_READ_BAT_MIN_W		0x5d /* out: u16 */
#घोषणा CMD_READ_BAR_MAX_W		0x5e /* out: u16 */
#घोषणा CMD_RESET_BAT_MINMAX_W		0x5f /* none */
#घोषणा CMD_READ_LOCATION		0x60 /* in: u16 addr, out: u8 data */
#घोषणा CMD_WRITE_LOCATION		0x61 /* in: u16 addr, u8 data */
#घोषणा CMD_KEYBOARD_CMD		0x62 /* in: u8, out: ? */
#घोषणा CMD_TOUCHPAD_CMD		0x63 /* in: u8, out: ? */
#घोषणा CMD_GET_FW_HASH			0x64 /* out: u8 * 16 */
#घोषणा CMD_SUSPEND_HINT		0x65 /* in: u8 */
#घोषणा CMD_ENABLE_WAKE_TIMER		0x66 /* in: u8 */
#घोषणा CMD_SET_WAKE_TIMER		0x67 /* in: 32 */
#घोषणा CMD_ENABLE_WAKE_AUTORESET	0x68 /* in: u8 */
#घोषणा CMD_OLS_SET_LIMITS		0x69 /* in: u16, u16 */
#घोषणा CMD_OLS_GET_LIMITS		0x6a /* out: u16, u16 */
#घोषणा CMD_OLS_SET_CEILING		0x6b /* in: u16 */
#घोषणा CMD_OLS_GET_CEILING		0x6c /* out: u16 */

/*
 * Accepted EC commands, and how many bytes they वापस. There are plenty
 * of EC commands that are no दीर्घer implemented, or are implemented only on
 * certain older boards.
 */
अटल स्थिर काष्ठा ec_cmd_t olpc_xo175_ec_cmds[] = अणु
	अणु CMD_GET_API_VERSION, 1 पूर्ण,
	अणु CMD_READ_VOLTAGE, 2 पूर्ण,
	अणु CMD_READ_CURRENT, 2 पूर्ण,
	अणु CMD_READ_ACR, 2 पूर्ण,
	अणु CMD_READ_BATT_TEMPERATURE, 2 पूर्ण,
	अणु CMD_READ_BATTERY_STATUS, 1 पूर्ण,
	अणु CMD_READ_SOC, 1 पूर्ण,
	अणु CMD_READ_GAUGE_ID, 8 पूर्ण,
	अणु CMD_READ_GAUGE_DATA, 1 पूर्ण,
	अणु CMD_READ_BOARD_ID, 2 पूर्ण,
	अणु CMD_READ_BATT_ERR_CODE, 1 पूर्ण,
	अणु CMD_SET_DCON_POWER, 0 पूर्ण,
	अणु CMD_RESET_EC, 0 पूर्ण,
	अणु CMD_READ_BATTERY_TYPE, 1 पूर्ण,
	अणु CMD_ENABLE_RUNIN_DISCHARGE, 0 पूर्ण,
	अणु CMD_DISABLE_RUNIN_DISCHARGE, 0 पूर्ण,
	अणु CMD_READ_MPPT_ACTIVE, 1 पूर्ण,
	अणु CMD_READ_MPPT_LIMIT, 1 पूर्ण,
	अणु CMD_SET_MPPT_LIMIT, 0 पूर्ण,
	अणु CMD_DISABLE_MPPT, 0 पूर्ण,
	अणु CMD_ENABLE_MPPT, 0 पूर्ण,
	अणु CMD_READ_VIN, 2 पूर्ण,
	अणु CMD_GET_FW_VERSION, 16 पूर्ण,
	अणु CMD_POWER_CYCLE, 0 पूर्ण,
	अणु CMD_POWER_OFF, 0 पूर्ण,
	अणु CMD_RESET_EC_SOFT, 0 पूर्ण,
	अणु CMD_ECHO, 5 पूर्ण,
	अणु CMD_GET_FW_DATE, 16 पूर्ण,
	अणु CMD_GET_FW_USER, 16 पूर्ण,
	अणु CMD_TURN_OFF_POWER, 0 पूर्ण,
	अणु CMD_READ_OLS, 2 पूर्ण,
	अणु CMD_OLS_SMT_LEDON, 0 पूर्ण,
	अणु CMD_OLS_SMT_LEDOFF, 0 पूर्ण,
	अणु CMD_START_OLS_ASSY, 0 पूर्ण,
	अणु CMD_STOP_OLS_ASSY, 0 पूर्ण,
	अणु CMD_OLS_SMTTEST_STOP, 0 पूर्ण,
	अणु CMD_READ_VIN_SCALED, 2 पूर्ण,
	अणु CMD_READ_BAT_MIN_W, 2 पूर्ण,
	अणु CMD_READ_BAR_MAX_W, 2 पूर्ण,
	अणु CMD_RESET_BAT_MINMAX_W, 0 पूर्ण,
	अणु CMD_READ_LOCATION, 1 पूर्ण,
	अणु CMD_WRITE_LOCATION, 0 पूर्ण,
	अणु CMD_GET_FW_HASH, 16 पूर्ण,
	अणु CMD_SUSPEND_HINT, 0 पूर्ण,
	अणु CMD_ENABLE_WAKE_TIMER, 0 पूर्ण,
	अणु CMD_SET_WAKE_TIMER, 0 पूर्ण,
	अणु CMD_ENABLE_WAKE_AUTORESET, 0 पूर्ण,
	अणु CMD_OLS_SET_LIMITS, 0 पूर्ण,
	अणु CMD_OLS_GET_LIMITS, 4 पूर्ण,
	अणु CMD_OLS_SET_CEILING, 0 पूर्ण,
	अणु CMD_OLS_GET_CEILING, 2 पूर्ण,
	अणु CMD_READ_EXT_SCI_MASK, 2 पूर्ण,
	अणु CMD_WRITE_EXT_SCI_MASK, 0 पूर्ण,

	अणु पूर्ण
पूर्ण;

#घोषणा EC_MAX_CMD_DATA_LEN	5
#घोषणा EC_MAX_RESP_LEN		16

#घोषणा LOG_BUF_SIZE		128

#घोषणा PM_WAKEUP_TIME		1000

#घोषणा EC_ALL_EVENTS		GENMASK(15, 0)

क्रमागत ec_state_t अणु
	CMD_STATE_IDLE = 0,
	CMD_STATE_WAITING_FOR_SWITCH,
	CMD_STATE_CMD_IN_TX_FIFO,
	CMD_STATE_CMD_SENT,
	CMD_STATE_RESP_RECEIVED,
	CMD_STATE_ERROR_RECEIVED,
पूर्ण;

काष्ठा olpc_xo175_ec_cmd अणु
	u8 command;
	u8 nr_args;
	u8 data_len;
	u8 args[EC_MAX_CMD_DATA_LEN];
पूर्ण;

काष्ठा olpc_xo175_ec_resp अणु
	u8 channel;
	u8 byte;
पूर्ण;

काष्ठा olpc_xo175_ec अणु
	bool suspended;

	/* SPI related stuff. */
	काष्ठा spi_device *spi;
	काष्ठा spi_transfer xfer;
	काष्ठा spi_message msg;
	जोड़ अणु
		काष्ठा olpc_xo175_ec_cmd cmd;
		काष्ठा olpc_xo175_ec_resp resp;
	पूर्ण tx_buf, rx_buf;

	/* GPIO क्रम the CMD संकेतs. */
	काष्ठा gpio_desc *gpio_cmd;

	/* Command handling related state. */
	spinlock_t cmd_state_lock;
	पूर्णांक cmd_state;
	bool cmd_running;
	काष्ठा completion cmd_करोne;
	काष्ठा olpc_xo175_ec_cmd cmd;
	u8 resp_data[EC_MAX_RESP_LEN];
	पूर्णांक expected_resp_len;
	पूर्णांक resp_len;

	/* Power button. */
	काष्ठा input_dev *pwrbtn;

	/* Debug handling. */
	अक्षर logbuf[LOG_BUF_SIZE];
	पूर्णांक logbuf_len;
पूर्ण;

अटल काष्ठा platक्रमm_device *olpc_ec;

अटल पूर्णांक olpc_xo175_ec_resp_len(u8 cmd)
अणु
	स्थिर काष्ठा ec_cmd_t *p;

	क्रम (p = olpc_xo175_ec_cmds; p->cmd; p++) अणु
		अगर (p->cmd == cmd)
			वापस p->bytes_वापसed;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम olpc_xo175_ec_flush_logbuf(काष्ठा olpc_xo175_ec *priv)
अणु
	dev_dbg(&priv->spi->dev, "got debug string [%*pE]\n",
				priv->logbuf_len, priv->logbuf);
	priv->logbuf_len = 0;
पूर्ण

अटल व्योम olpc_xo175_ec_complete(व्योम *arg);

अटल व्योम olpc_xo175_ec_send_command(काष्ठा olpc_xo175_ec *priv, व्योम *cmd,
								माप_प्रकार cmdlen)
अणु
	पूर्णांक ret;

	स_नकल(&priv->tx_buf, cmd, cmdlen);
	priv->xfer.len = cmdlen;

	spi_message_init_with_transfers(&priv->msg, &priv->xfer, 1);

	priv->msg.complete = olpc_xo175_ec_complete;
	priv->msg.context = priv;

	ret = spi_async(priv->spi, &priv->msg);
	अगर (ret)
		dev_err(&priv->spi->dev, "spi_async() failed %d\n", ret);
पूर्ण

अटल व्योम olpc_xo175_ec_पढ़ो_packet(काष्ठा olpc_xo175_ec *priv)
अणु
	u8 nonce[] = अणु0xA5, 0x5Aपूर्ण;

	olpc_xo175_ec_send_command(priv, nonce, माप(nonce));
पूर्ण

अटल व्योम olpc_xo175_ec_complete(व्योम *arg)
अणु
	काष्ठा olpc_xo175_ec *priv = arg;
	काष्ठा device *dev = &priv->spi->dev;
	काष्ठा घातer_supply *psy;
	अचिन्हित दीर्घ flags;
	u8 channel;
	u8 byte;
	पूर्णांक ret;

	ret = priv->msg.status;
	अगर (ret) अणु
		dev_err(dev, "SPI transfer failed: %d\n", ret);

		spin_lock_irqsave(&priv->cmd_state_lock, flags);
		अगर (priv->cmd_running) अणु
			priv->resp_len = 0;
			priv->cmd_state = CMD_STATE_ERROR_RECEIVED;
			complete(&priv->cmd_करोne);
		पूर्ण
		spin_unlock_irqrestore(&priv->cmd_state_lock, flags);

		अगर (ret != -EINTR)
			olpc_xo175_ec_पढ़ो_packet(priv);

		वापस;
	पूर्ण

	channel = priv->rx_buf.resp.channel;
	byte = priv->rx_buf.resp.byte;

	चयन (channel) अणु
	हाल CHAN_NONE:
		spin_lock_irqsave(&priv->cmd_state_lock, flags);

		अगर (!priv->cmd_running) अणु
			/* We can safely ignore these */
			dev_err(dev, "spurious FIFO read packet\n");
			spin_unlock_irqrestore(&priv->cmd_state_lock, flags);
			वापस;
		पूर्ण

		priv->cmd_state = CMD_STATE_CMD_SENT;
		अगर (!priv->expected_resp_len)
			complete(&priv->cmd_करोne);
		olpc_xo175_ec_पढ़ो_packet(priv);

		spin_unlock_irqrestore(&priv->cmd_state_lock, flags);
		वापस;

	हाल CHAN_SWITCH:
		spin_lock_irqsave(&priv->cmd_state_lock, flags);

		अगर (!priv->cmd_running) अणु
			/* Just go with the flow */
			dev_err(dev, "spurious SWITCH packet\n");
			स_रखो(&priv->cmd, 0, माप(priv->cmd));
			priv->cmd.command = CMD_ECHO;
		पूर्ण

		priv->cmd_state = CMD_STATE_CMD_IN_TX_FIFO;

		/* Throw command पूर्णांकo TxFIFO */
		gpiod_set_value_cansleep(priv->gpio_cmd, 0);
		olpc_xo175_ec_send_command(priv, &priv->cmd, माप(priv->cmd));

		spin_unlock_irqrestore(&priv->cmd_state_lock, flags);
		वापस;

	हाल CHAN_CMD_RESP:
		spin_lock_irqsave(&priv->cmd_state_lock, flags);

		अगर (!priv->cmd_running) अणु
			dev_err(dev, "spurious response packet\n");
		पूर्ण अन्यथा अगर (priv->resp_len >= priv->expected_resp_len) अणु
			dev_err(dev, "too many response packets\n");
		पूर्ण अन्यथा अणु
			priv->resp_data[priv->resp_len++] = byte;
			अगर (priv->resp_len == priv->expected_resp_len) अणु
				priv->cmd_state = CMD_STATE_RESP_RECEIVED;
				complete(&priv->cmd_करोne);
			पूर्ण
		पूर्ण

		spin_unlock_irqrestore(&priv->cmd_state_lock, flags);
		अवरोध;

	हाल CHAN_CMD_ERROR:
		spin_lock_irqsave(&priv->cmd_state_lock, flags);

		अगर (!priv->cmd_running) अणु
			dev_err(dev, "spurious cmd error packet\n");
		पूर्ण अन्यथा अणु
			priv->resp_data[0] = byte;
			priv->resp_len = 1;
			priv->cmd_state = CMD_STATE_ERROR_RECEIVED;
			complete(&priv->cmd_करोne);
		पूर्ण
		spin_unlock_irqrestore(&priv->cmd_state_lock, flags);
		अवरोध;

	हाल CHAN_KEYBOARD:
		dev_warn(dev, "keyboard is not supported\n");
		अवरोध;

	हाल CHAN_TOUCHPAD:
		dev_warn(dev, "touchpad is not supported\n");
		अवरोध;

	हाल CHAN_EVENT:
		dev_dbg(dev, "got event %.2x\n", byte);
		चयन (byte) अणु
		हाल EVENT_AC_CHANGE:
			psy = घातer_supply_get_by_name("olpc_ac");
			अगर (psy) अणु
				घातer_supply_changed(psy);
				घातer_supply_put(psy);
			पूर्ण
			अवरोध;
		हाल EVENT_BATTERY_STATUS:
		हाल EVENT_BATTERY_CRITICAL:
		हाल EVENT_BATTERY_SOC_CHANGE:
		हाल EVENT_BATTERY_ERROR:
			psy = घातer_supply_get_by_name("olpc_battery");
			अगर (psy) अणु
				घातer_supply_changed(psy);
				घातer_supply_put(psy);
			पूर्ण
			अवरोध;
		हाल EVENT_POWER_PRESSED:
			input_report_key(priv->pwrbtn, KEY_POWER, 1);
			input_sync(priv->pwrbtn);
			input_report_key(priv->pwrbtn, KEY_POWER, 0);
			input_sync(priv->pwrbtn);
			fallthrough;
		हाल EVENT_POWER_PRESS_WAKE:
		हाल EVENT_TIMED_HOST_WAKE:
			pm_wakeup_event(priv->pwrbtn->dev.parent,
						PM_WAKEUP_TIME);
			अवरोध;
		शेष:
			dev_dbg(dev, "ignored unknown event %.2x\n", byte);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल CHAN_DEBUG:
		अगर (byte == '\n') अणु
			olpc_xo175_ec_flush_logbuf(priv);
		पूर्ण अन्यथा अगर (है_छाप(byte)) अणु
			priv->logbuf[priv->logbuf_len++] = byte;
			अगर (priv->logbuf_len == LOG_BUF_SIZE)
				olpc_xo175_ec_flush_logbuf(priv);
		पूर्ण
		अवरोध;

	शेष:
		dev_warn(dev, "unknown channel: %d, %.2x\n", channel, byte);
		अवरोध;
	पूर्ण

	/* Most non-command packets get the TxFIFO refilled and an ACK. */
	olpc_xo175_ec_पढ़ो_packet(priv);
पूर्ण

/*
 * This function is रक्षित with a mutex. We can safely assume that
 * there will be only one instance of this function running at a समय.
 * One of the ways in which we enक्रमce this is by रुकोing until we get
 * all response bytes back from the EC, rather than just the number that
 * the caller requests (otherwise, we might start a new command जबतक an
 * old command's response bytes are still incoming).
 */
अटल पूर्णांक olpc_xo175_ec_cmd(u8 cmd, u8 *inbuf, माप_प्रकार inlen, u8 *resp,
					माप_प्रकार resp_len, व्योम *ec_cb_arg)
अणु
	काष्ठा olpc_xo175_ec *priv = ec_cb_arg;
	काष्ठा device *dev = &priv->spi->dev;
	अचिन्हित दीर्घ flags;
	माप_प्रकार nr_bytes;
	पूर्णांक ret = 0;

	dev_dbg(dev, "CMD %x, %zd bytes expected\n", cmd, resp_len);

	अगर (inlen > 5) अणु
		dev_err(dev, "command len %zd too big!\n", resp_len);
		वापस -EOVERFLOW;
	पूर्ण

	/* Suspending in the middle of an EC command hoses things badly! */
	अगर (WARN_ON(priv->suspended))
		वापस -EBUSY;

	/* Ensure a valid command and वापस bytes */
	ret = olpc_xo175_ec_resp_len(cmd);
	अगर (ret < 0) अणु
		dev_err_ratelimited(dev, "unknown command 0x%x\n", cmd);

		/*
		 * Assume the best in our callers, and allow unknown commands
		 * through. I'm not the अक्षरitable type, but it was beaten
		 * पूर्णांकo me. Just मुख्यtain a minimum standard of sanity.
		 */
		अगर (resp_len > माप(priv->resp_data)) अणु
			dev_err(dev, "response too big: %zd!\n", resp_len);
			वापस -EOVERFLOW;
		पूर्ण
		nr_bytes = resp_len;
	पूर्ण अन्यथा अणु
		nr_bytes = (माप_प्रकार)ret;
		ret = 0;
	पूर्ण
	resp_len = min(resp_len, nr_bytes);

	spin_lock_irqsave(&priv->cmd_state_lock, flags);

	/* Initialize the state machine */
	init_completion(&priv->cmd_करोne);
	priv->cmd_running = true;
	priv->cmd_state = CMD_STATE_WAITING_FOR_SWITCH;
	स_रखो(&priv->cmd, 0, माप(priv->cmd));
	priv->cmd.command = cmd;
	priv->cmd.nr_args = inlen;
	priv->cmd.data_len = 0;
	स_नकल(priv->cmd.args, inbuf, inlen);
	priv->expected_resp_len = nr_bytes;
	priv->resp_len = 0;

	/* Tickle the cmd gpio to get things started */
	gpiod_set_value_cansleep(priv->gpio_cmd, 1);

	spin_unlock_irqrestore(&priv->cmd_state_lock, flags);

	/* The irq handler should करो the rest */
	अगर (!रुको_क्रम_completion_समयout(&priv->cmd_करोne,
			msecs_to_jअगरfies(4000))) अणु
		dev_err(dev, "EC cmd error: timeout in STATE %d\n",
				priv->cmd_state);
		gpiod_set_value_cansleep(priv->gpio_cmd, 0);
		spi_slave_पात(priv->spi);
		olpc_xo175_ec_पढ़ो_packet(priv);
		वापस -ETIMEDOUT;
	पूर्ण

	spin_lock_irqsave(&priv->cmd_state_lock, flags);

	/* Deal with the results. */
	अगर (priv->cmd_state == CMD_STATE_ERROR_RECEIVED) अणु
		/* EC-provided error is in the single response byte */
		dev_err(dev, "command 0x%x returned error 0x%x\n",
						cmd, priv->resp_data[0]);
		ret = -EREMOTEIO;
	पूर्ण अन्यथा अगर (priv->resp_len != nr_bytes) अणु
		dev_err(dev, "command 0x%x returned %d bytes, expected %zd bytes\n",
						cmd, priv->resp_len, nr_bytes);
		ret = -EREMOTEIO;
	पूर्ण अन्यथा अणु
		/*
		 * We may have 8 bytes in priv->resp, but we only care about
		 * what we've been asked क्रम. If the caller asked क्रम only 2
		 * bytes, give them that. We've guaranteed that
		 * resp_len <= priv->resp_len and priv->resp_len == nr_bytes.
		 */
		स_नकल(resp, priv->resp_data, resp_len);
	पूर्ण

	/* This should alपढ़ोy be low, but just in हाल. */
	gpiod_set_value_cansleep(priv->gpio_cmd, 0);
	priv->cmd_running = false;

	spin_unlock_irqrestore(&priv->cmd_state_lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक olpc_xo175_ec_set_event_mask(अचिन्हित पूर्णांक mask)
अणु
	u8 args[2];

	args[0] = mask >> 0;
	args[1] = mask >> 8;
	वापस olpc_ec_cmd(CMD_WRITE_EXT_SCI_MASK, args, 2, शून्य, 0);
पूर्ण

अटल व्योम olpc_xo175_ec_घातer_off(व्योम)
अणु
	जबतक (1) अणु
		olpc_ec_cmd(CMD_POWER_OFF, शून्य, 0, शून्य, 0);
		mdelay(1000);
	पूर्ण
पूर्ण

अटल पूर्णांक __maybe_unused olpc_xo175_ec_suspend(काष्ठा device *dev)
अणु
	काष्ठा olpc_xo175_ec *priv = dev_get_drvdata(dev);
	अटल काष्ठा अणु
		u8 suspend;
		u32 suspend_count;
	पूर्ण __packed hपूर्णांकargs;
	अटल अचिन्हित पूर्णांक suspend_count;

	/*
	 * SOC_SLEEP is not wired to the EC on B3 and earlier boards.
	 * This command lets the EC know instead. The suspend count करोesn't seem
	 * to be used anywhere but in the EC debug output.
	 */
	hपूर्णांकargs.suspend = 1;
	hपूर्णांकargs.suspend_count = suspend_count++;
	olpc_ec_cmd(CMD_SUSPEND_HINT, (व्योम *)&hपूर्णांकargs, माप(hपूर्णांकargs),
								शून्य, 0);

	/*
	 * After we've sent the suspend hint, don't allow further EC commands
	 * to be run until we've resumed. Userspace tasks should be frozen,
	 * but kernel thपढ़ोs and पूर्णांकerrupts could still schedule EC commands.
	 */
	priv->suspended = true;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused olpc_xo175_ec_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा olpc_xo175_ec *priv = dev_get_drvdata(dev);

	priv->suspended = false;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused olpc_xo175_ec_resume(काष्ठा device *dev)
अणु
	u8 x = 0;

	/*
	 * The resume hपूर्णांक is only needed अगर no other commands are
	 * being sent during resume. all it करोes is tell the EC
	 * the SoC is definitely awake.
	 */
	olpc_ec_cmd(CMD_SUSPEND_HINT, &x, 1, शून्य, 0);

	/* Enable all EC events जबतक we're awake */
	olpc_xo175_ec_set_event_mask(EC_ALL_EVENTS);

	वापस 0;
पूर्ण

अटल काष्ठा olpc_ec_driver olpc_xo175_ec_driver = अणु
	.ec_cmd = olpc_xo175_ec_cmd,
पूर्ण;

अटल पूर्णांक olpc_xo175_ec_हटाओ(काष्ठा spi_device *spi)
अणु
	अगर (pm_घातer_off == olpc_xo175_ec_घातer_off)
		pm_घातer_off = शून्य;

	spi_slave_पात(spi);

	platक्रमm_device_unरेजिस्टर(olpc_ec);
	olpc_ec = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक olpc_xo175_ec_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा olpc_xo175_ec *priv;
	पूर्णांक ret;

	अगर (olpc_ec) अणु
		dev_err(&spi->dev, "OLPC EC already registered.\n");
		वापस -EBUSY;
	पूर्ण

	priv = devm_kzalloc(&spi->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->gpio_cmd = devm_gpiod_get(&spi->dev, "cmd", GPIOD_OUT_LOW);
	अगर (IS_ERR(priv->gpio_cmd)) अणु
		dev_err(&spi->dev, "failed to get cmd gpio: %ld\n",
					PTR_ERR(priv->gpio_cmd));
		वापस PTR_ERR(priv->gpio_cmd);
	पूर्ण

	priv->spi = spi;

	spin_lock_init(&priv->cmd_state_lock);
	priv->cmd_state = CMD_STATE_IDLE;
	init_completion(&priv->cmd_करोne);

	priv->logbuf_len = 0;

	/* Set up घातer button input device */
	priv->pwrbtn = devm_input_allocate_device(&spi->dev);
	अगर (!priv->pwrbtn)
		वापस -ENOMEM;
	priv->pwrbtn->name = "Power Button";
	priv->pwrbtn->dev.parent = &spi->dev;
	input_set_capability(priv->pwrbtn, EV_KEY, KEY_POWER);
	ret = input_रेजिस्टर_device(priv->pwrbtn);
	अगर (ret) अणु
		dev_err(&spi->dev, "error registering input device: %d\n", ret);
		वापस ret;
	पूर्ण

	spi_set_drvdata(spi, priv);

	priv->xfer.rx_buf = &priv->rx_buf;
	priv->xfer.tx_buf = &priv->tx_buf;

	olpc_xo175_ec_पढ़ो_packet(priv);

	olpc_ec_driver_रेजिस्टर(&olpc_xo175_ec_driver, priv);
	olpc_ec = platक्रमm_device_रेजिस्टर_resndata(&spi->dev, "olpc-ec", -1,
							शून्य, 0, शून्य, 0);

	/* Enable all EC events जबतक we're awake */
	olpc_xo175_ec_set_event_mask(EC_ALL_EVENTS);

	अगर (pm_घातer_off == शून्य)
		pm_घातer_off = olpc_xo175_ec_घातer_off;

	dev_info(&spi->dev, "OLPC XO-1.75 Embedded Controller driver\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops olpc_xo175_ec_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(शून्य, olpc_xo175_ec_resume_noirq)
	SET_RUNTIME_PM_OPS(olpc_xo175_ec_suspend, olpc_xo175_ec_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id olpc_xo175_ec_of_match[] = अणु
	अणु .compatible = "olpc,xo1.75-ec" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, olpc_xo175_ec_of_match);

अटल स्थिर काष्ठा spi_device_id olpc_xo175_ec_id_table[] = अणु
	अणु "xo1.75-ec", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, olpc_xo175_ec_id_table);

अटल काष्ठा spi_driver olpc_xo175_ec_spi_driver = अणु
	.driver = अणु
		.name	= "olpc-xo175-ec",
		.of_match_table = olpc_xo175_ec_of_match,
		.pm = &olpc_xo175_ec_pm_ops,
	पूर्ण,
	.probe		= olpc_xo175_ec_probe,
	.हटाओ		= olpc_xo175_ec_हटाओ,
पूर्ण;
module_spi_driver(olpc_xo175_ec_spi_driver);

MODULE_DESCRIPTION("OLPC XO-1.75 Embedded Controller driver");
MODULE_AUTHOR("Lennert Buytenhek <buytenh@wantstofly.org>"); /* Functionality */
MODULE_AUTHOR("Lubomir Rintel <lkundrak@v3.sk>"); /* Bugs */
MODULE_LICENSE("GPL");
