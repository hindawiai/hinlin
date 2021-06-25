<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/mfd/si476x-cmd.c -- Subroutines implementing command
 * protocol of si476x series of chips
 *
 * Copyright (C) 2012 Innovative Converged Devices(ICD)
 * Copyright (C) 2013 Andrey Smirnov
 *
 * Author: Andrey Smirnov <andrew.smirnov@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/atomic.h>
#समावेश <linux/i2c.h>
#समावेश <linux/device.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/videodev2.h>

#समावेश <linux/mfd/si476x-core.h>

#समावेश <यंत्र/unaligned.h>

#घोषणा msb(x)                  ((u8)((u16) x >> 8))
#घोषणा lsb(x)                  ((u8)((u16) x &  0x00FF))



#घोषणा CMD_POWER_UP				0x01
#घोषणा CMD_POWER_UP_A10_NRESP			1
#घोषणा CMD_POWER_UP_A10_NARGS			5

#घोषणा CMD_POWER_UP_A20_NRESP			1
#घोषणा CMD_POWER_UP_A20_NARGS			5

#घोषणा POWER_UP_DELAY_MS			110

#घोषणा CMD_POWER_DOWN				0x11
#घोषणा CMD_POWER_DOWN_A10_NRESP		1

#घोषणा CMD_POWER_DOWN_A20_NRESP		1
#घोषणा CMD_POWER_DOWN_A20_NARGS		1

#घोषणा CMD_FUNC_INFO				0x12
#घोषणा CMD_FUNC_INFO_NRESP			7

#घोषणा CMD_SET_PROPERTY			0x13
#घोषणा CMD_SET_PROPERTY_NARGS			5
#घोषणा CMD_SET_PROPERTY_NRESP			1

#घोषणा CMD_GET_PROPERTY			0x14
#घोषणा CMD_GET_PROPERTY_NARGS			3
#घोषणा CMD_GET_PROPERTY_NRESP			4

#घोषणा CMD_AGC_STATUS				0x17
#घोषणा CMD_AGC_STATUS_NRESP_A10		2
#घोषणा CMD_AGC_STATUS_NRESP_A20                6

#घोषणा PIN_CFG_BYTE(x) (0x7F & (x))
#घोषणा CMD_DIG_AUDIO_PIN_CFG			0x18
#घोषणा CMD_DIG_AUDIO_PIN_CFG_NARGS		4
#घोषणा CMD_DIG_AUDIO_PIN_CFG_NRESP		5

#घोषणा CMD_ZIF_PIN_CFG				0x19
#घोषणा CMD_ZIF_PIN_CFG_NARGS			4
#घोषणा CMD_ZIF_PIN_CFG_NRESP			5

#घोषणा CMD_IC_LINK_GPO_CTL_PIN_CFG		0x1A
#घोषणा CMD_IC_LINK_GPO_CTL_PIN_CFG_NARGS	4
#घोषणा CMD_IC_LINK_GPO_CTL_PIN_CFG_NRESP	5

#घोषणा CMD_ANA_AUDIO_PIN_CFG			0x1B
#घोषणा CMD_ANA_AUDIO_PIN_CFG_NARGS		1
#घोषणा CMD_ANA_AUDIO_PIN_CFG_NRESP		2

#घोषणा CMD_INTB_PIN_CFG			0x1C
#घोषणा CMD_INTB_PIN_CFG_NARGS			2
#घोषणा CMD_INTB_PIN_CFG_A10_NRESP		6
#घोषणा CMD_INTB_PIN_CFG_A20_NRESP		3

#घोषणा CMD_FM_TUNE_FREQ			0x30
#घोषणा CMD_FM_TUNE_FREQ_A10_NARGS		5
#घोषणा CMD_FM_TUNE_FREQ_A20_NARGS		3
#घोषणा CMD_FM_TUNE_FREQ_NRESP			1

#घोषणा CMD_FM_RSQ_STATUS			0x32

#घोषणा CMD_FM_RSQ_STATUS_A10_NARGS		1
#घोषणा CMD_FM_RSQ_STATUS_A10_NRESP		17
#घोषणा CMD_FM_RSQ_STATUS_A30_NARGS		1
#घोषणा CMD_FM_RSQ_STATUS_A30_NRESP		23


#घोषणा CMD_FM_SEEK_START			0x31
#घोषणा CMD_FM_SEEK_START_NARGS			1
#घोषणा CMD_FM_SEEK_START_NRESP			1

#घोषणा CMD_FM_RDS_STATUS			0x36
#घोषणा CMD_FM_RDS_STATUS_NARGS			1
#घोषणा CMD_FM_RDS_STATUS_NRESP			16

#घोषणा CMD_FM_RDS_BLOCKCOUNT			0x37
#घोषणा CMD_FM_RDS_BLOCKCOUNT_NARGS		1
#घोषणा CMD_FM_RDS_BLOCKCOUNT_NRESP		8

#घोषणा CMD_FM_PHASE_DIVERSITY			0x38
#घोषणा CMD_FM_PHASE_DIVERSITY_NARGS		1
#घोषणा CMD_FM_PHASE_DIVERSITY_NRESP		1

#घोषणा CMD_FM_PHASE_DIV_STATUS			0x39
#घोषणा CMD_FM_PHASE_DIV_STATUS_NRESP		2

#घोषणा CMD_AM_TUNE_FREQ			0x40
#घोषणा CMD_AM_TUNE_FREQ_NARGS			3
#घोषणा CMD_AM_TUNE_FREQ_NRESP			1

#घोषणा CMD_AM_RSQ_STATUS			0x42
#घोषणा CMD_AM_RSQ_STATUS_NARGS			1
#घोषणा CMD_AM_RSQ_STATUS_NRESP			13

#घोषणा CMD_AM_SEEK_START			0x41
#घोषणा CMD_AM_SEEK_START_NARGS			1
#घोषणा CMD_AM_SEEK_START_NRESP			1


#घोषणा CMD_AM_ACF_STATUS			0x45
#घोषणा CMD_AM_ACF_STATUS_NRESP			6
#घोषणा CMD_AM_ACF_STATUS_NARGS			1

#घोषणा CMD_FM_ACF_STATUS			0x35
#घोषणा CMD_FM_ACF_STATUS_NRESP			8
#घोषणा CMD_FM_ACF_STATUS_NARGS			1

#घोषणा CMD_MAX_ARGS_COUNT			(10)


क्रमागत si476x_acf_status_report_bits अणु
	SI476X_ACF_BLEND_INT	= (1 << 4),
	SI476X_ACF_HIBLEND_INT	= (1 << 3),
	SI476X_ACF_HICUT_INT	= (1 << 2),
	SI476X_ACF_CHBW_INT	= (1 << 1),
	SI476X_ACF_SOFTMUTE_INT	= (1 << 0),

	SI476X_ACF_SMUTE	= (1 << 0),
	SI476X_ACF_SMATTN	= 0x1f,
	SI476X_ACF_PILOT	= (1 << 7),
	SI476X_ACF_STBLEND	= ~SI476X_ACF_PILOT,
पूर्ण;

क्रमागत si476x_agc_status_report_bits अणु
	SI476X_AGC_MXHI		= (1 << 5),
	SI476X_AGC_MXLO		= (1 << 4),
	SI476X_AGC_LNAHI	= (1 << 3),
	SI476X_AGC_LNALO	= (1 << 2),
पूर्ण;

क्रमागत si476x_errors अणु
	SI476X_ERR_BAD_COMMAND		= 0x10,
	SI476X_ERR_BAD_ARG1		= 0x11,
	SI476X_ERR_BAD_ARG2		= 0x12,
	SI476X_ERR_BAD_ARG3		= 0x13,
	SI476X_ERR_BAD_ARG4		= 0x14,
	SI476X_ERR_BUSY			= 0x18,
	SI476X_ERR_BAD_INTERNAL_MEMORY  = 0x20,
	SI476X_ERR_BAD_PATCH		= 0x30,
	SI476X_ERR_BAD_BOOT_MODE	= 0x31,
	SI476X_ERR_BAD_PROPERTY		= 0x40,
पूर्ण;

अटल पूर्णांक si476x_core_parse_and_nag_about_error(काष्ठा si476x_core *core)
अणु
	पूर्णांक err;
	अक्षर *cause;
	u8 buffer[2];

	अगर (core->revision != SI476X_REVISION_A10) अणु
		err = si476x_core_i2c_xfer(core, SI476X_I2C_RECV,
					   buffer, माप(buffer));
		अगर (err == माप(buffer)) अणु
			चयन (buffer[1]) अणु
			हाल SI476X_ERR_BAD_COMMAND:
				cause = "Bad command";
				err = -EINVAL;
				अवरोध;
			हाल SI476X_ERR_BAD_ARG1:
				cause = "Bad argument #1";
				err = -EINVAL;
				अवरोध;
			हाल SI476X_ERR_BAD_ARG2:
				cause = "Bad argument #2";
				err = -EINVAL;
				अवरोध;
			हाल SI476X_ERR_BAD_ARG3:
				cause = "Bad argument #3";
				err = -EINVAL;
				अवरोध;
			हाल SI476X_ERR_BAD_ARG4:
				cause = "Bad argument #4";
				err = -EINVAL;
				अवरोध;
			हाल SI476X_ERR_BUSY:
				cause = "Chip is busy";
				err = -EBUSY;
				अवरोध;
			हाल SI476X_ERR_BAD_INTERNAL_MEMORY:
				cause = "Bad internal memory";
				err = -EIO;
				अवरोध;
			हाल SI476X_ERR_BAD_PATCH:
				cause = "Bad patch";
				err = -EINVAL;
				अवरोध;
			हाल SI476X_ERR_BAD_BOOT_MODE:
				cause = "Bad boot mode";
				err = -EINVAL;
				अवरोध;
			हाल SI476X_ERR_BAD_PROPERTY:
				cause = "Bad property";
				err = -EINVAL;
				अवरोध;
			शेष:
				cause = "Unknown";
				err = -EIO;
			पूर्ण

			dev_err(&core->client->dev,
				"[Chip error status]: %s\n", cause);
		पूर्ण अन्यथा अणु
			dev_err(&core->client->dev,
				"Failed to fetch error code\n");
			err = (err >= 0) ? -EIO : err;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = -EIO;
	पूर्ण

	वापस err;
पूर्ण

/**
 * si476x_core_send_command() - sends a command to si476x and रुकोs its
 * response
 * @core:     si476x_device काष्ठाure क्रम the device we are
 *            communicating with
 * @command:  command id
 * @args:     command arguments we are sending
 * @argn:     actual size of @args
 * @resp:     buffer to place the expected response from the device
 * @respn:    actual size of @resp
 * @usecs:    amount of समय to रुको beक्रमe पढ़ोing the response (in
 *            usecs)
 *
 * Function वापसs 0 on succsess and negative error code on
 * failure
 */
अटल पूर्णांक si476x_core_send_command(काष्ठा si476x_core *core,
				    स्थिर u8 command,
				    स्थिर u8 args[],
				    स्थिर पूर्णांक argn,
				    u8 resp[],
				    स्थिर पूर्णांक respn,
				    स्थिर पूर्णांक usecs)
अणु
	काष्ठा i2c_client *client = core->client;
	पूर्णांक err;
	u8  data[CMD_MAX_ARGS_COUNT + 1];

	अगर (argn > CMD_MAX_ARGS_COUNT) अणु
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण

	अगर (!client->adapter) अणु
		err = -ENODEV;
		जाओ निकास;
	पूर्ण

	/* First send the command and its arguments */
	data[0] = command;
	स_नकल(&data[1], args, argn);
	dev_dbg(&client->dev, "Command:\n %*ph\n", argn + 1, data);

	err = si476x_core_i2c_xfer(core, SI476X_I2C_SEND,
				   (अक्षर *) data, argn + 1);
	अगर (err != argn + 1) अणु
		dev_err(&core->client->dev,
			"Error while sending command 0x%02x\n",
			command);
		err = (err >= 0) ? -EIO : err;
		जाओ निकास;
	पूर्ण
	/* Set CTS to zero only after the command is send to aव्योम
	 * possible racing conditions when working in polling mode */
	atomic_set(&core->cts, 0);

	/* अगर (unlikely(command == CMD_POWER_DOWN) */
	अगर (!रुको_event_समयout(core->command,
				atomic_पढ़ो(&core->cts),
				usecs_to_jअगरfies(usecs) + 1))
		dev_warn(&core->client->dev,
			 "(%s) [CMD 0x%02x] Answer timeout.\n",
			 __func__, command);

	/*
	  When working in polling mode, क्रम some reason the tuner will
	  report CTS bit as being set in the first status byte पढ़ो,
	  but all the consequtive ones will वापस zeros until the
	  tuner is actually completed the POWER_UP command. To
	  workaround that we रुको क्रम second CTS to be reported
	 */
	अगर (unlikely(!core->client->irq && command == CMD_POWER_UP)) अणु
		अगर (!रुको_event_समयout(core->command,
					atomic_पढ़ो(&core->cts),
					usecs_to_jअगरfies(usecs) + 1))
			dev_warn(&core->client->dev,
				 "(%s) Power up took too much time.\n",
				 __func__);
	पूर्ण

	/* Then get the response */
	err = si476x_core_i2c_xfer(core, SI476X_I2C_RECV, resp, respn);
	अगर (err != respn) अणु
		dev_err(&core->client->dev,
			"Error while reading response for command 0x%02x\n",
			command);
		err = (err >= 0) ? -EIO : err;
		जाओ निकास;
	पूर्ण
	dev_dbg(&client->dev, "Response:\n %*ph\n", respn, resp);

	err = 0;

	अगर (resp[0] & SI476X_ERR) अणु
		dev_err(&core->client->dev,
			"[CMD 0x%02x] Chip set error flag\n", command);
		err = si476x_core_parse_and_nag_about_error(core);
		जाओ निकास;
	पूर्ण

	अगर (!(resp[0] & SI476X_CTS))
		err = -EBUSY;
निकास:
	वापस err;
पूर्ण

अटल पूर्णांक si476x_cmd_clear_stc(काष्ठा si476x_core *core)
अणु
	पूर्णांक err;
	काष्ठा si476x_rsq_status_args args = अणु
		.primary	= false,
		.rsqack		= false,
		.attune		= false,
		.cancel		= false,
		.stcack		= true,
	पूर्ण;

	चयन (core->घातer_up_parameters.func) अणु
	हाल SI476X_FUNC_FM_RECEIVER:
		err = si476x_core_cmd_fm_rsq_status(core, &args, शून्य);
		अवरोध;
	हाल SI476X_FUNC_AM_RECEIVER:
		err = si476x_core_cmd_am_rsq_status(core, &args, शून्य);
		अवरोध;
	शेष:
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक si476x_cmd_tune_seek_freq(काष्ठा si476x_core *core,
				     uपूर्णांक8_t cmd,
				     स्थिर uपूर्णांक8_t args[], माप_प्रकार argn,
				     uपूर्णांक8_t *resp, माप_प्रकार respn)
अणु
	पूर्णांक err;


	atomic_set(&core->stc, 0);
	err = si476x_core_send_command(core, cmd, args, argn, resp, respn,
				       SI476X_TIMEOUT_TUNE);
	अगर (!err) अणु
		रुको_event_समाप्तable(core->tuning,
				    atomic_पढ़ो(&core->stc));
		si476x_cmd_clear_stc(core);
	पूर्ण

	वापस err;
पूर्ण

/**
 * si476x_cmd_func_info() - send 'FUNC_INFO' command to the device
 * @core: device to send the command to
 * @info:  काष्ठा si476x_func_info to fill all the inक्रमmation
 *         वापसed by the command
 *
 * The command requests the firmware and patch version क्रम currently
 * loaded firmware (dependent on the function of the device FM/AM/WB)
 *
 * Function वापसs 0 on succsess and negative error code on
 * failure
 */
पूर्णांक si476x_core_cmd_func_info(काष्ठा si476x_core *core,
			      काष्ठा si476x_func_info *info)
अणु
	पूर्णांक err;
	u8  resp[CMD_FUNC_INFO_NRESP];

	err = si476x_core_send_command(core, CMD_FUNC_INFO,
				       शून्य, 0,
				       resp, ARRAY_SIZE(resp),
				       SI476X_DEFAULT_TIMEOUT);

	info->firmware.major    = resp[1];
	info->firmware.minor[0] = resp[2];
	info->firmware.minor[1] = resp[3];

	info->patch_id = ((u16) resp[4] << 8) | resp[5];
	info->func     = resp[6];

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_cmd_func_info);

/**
 * si476x_cmd_set_property() - send 'SET_PROPERTY' command to the device
 * @core:    device to send the command to
 * @property: property address
 * @value:    property value
 *
 * Function वापसs 0 on succsess and negative error code on
 * failure
 */
पूर्णांक si476x_core_cmd_set_property(काष्ठा si476x_core *core,
				 u16 property, u16 value)
अणु
	u8       resp[CMD_SET_PROPERTY_NRESP];
	स्थिर u8 args[CMD_SET_PROPERTY_NARGS] = अणु
		0x00,
		msb(property),
		lsb(property),
		msb(value),
		lsb(value),
	पूर्ण;

	वापस si476x_core_send_command(core, CMD_SET_PROPERTY,
					args, ARRAY_SIZE(args),
					resp, ARRAY_SIZE(resp),
					SI476X_DEFAULT_TIMEOUT);
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_cmd_set_property);

/**
 * si476x_cmd_get_property() - send 'GET_PROPERTY' command to the device
 * @core:    device to send the command to
 * @property: property address
 *
 * Function वापस the value of property as u16 on success or a
 * negative error on failure
 */
पूर्णांक si476x_core_cmd_get_property(काष्ठा si476x_core *core, u16 property)
अणु
	पूर्णांक err;
	u8       resp[CMD_GET_PROPERTY_NRESP];
	स्थिर u8 args[CMD_GET_PROPERTY_NARGS] = अणु
		0x00,
		msb(property),
		lsb(property),
	पूर्ण;

	err = si476x_core_send_command(core, CMD_GET_PROPERTY,
				       args, ARRAY_SIZE(args),
				       resp, ARRAY_SIZE(resp),
				       SI476X_DEFAULT_TIMEOUT);
	अगर (err < 0)
		वापस err;
	अन्यथा
		वापस get_unaligned_be16(resp + 2);
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_cmd_get_property);

/**
 * si476x_cmd_dig_audio_pin_cfg() - send 'DIG_AUDIO_PIN_CFG' command to
 * the device
 * @core: device to send the command to
 * @dclk:  DCLK pin function configuration:
 *	   #SI476X_DCLK_NOOP     - करो not modअगरy the behaviour
 *         #SI476X_DCLK_TRISTATE - put the pin in tristate condition,
 *                                 enable 1MOhm pullकरोwn
 *         #SI476X_DCLK_DAUDIO   - set the pin to be a part of digital
 *                                 audio पूर्णांकerface
 * @dfs:   DFS pin function configuration:
 *         #SI476X_DFS_NOOP      - करो not modअगरy the behaviour
 *         #SI476X_DFS_TRISTATE  - put the pin in tristate condition,
 *                             enable 1MOhm pullकरोwn
 *      SI476X_DFS_DAUDIO    - set the pin to be a part of digital
 *                             audio पूर्णांकerface
 * @करोut: - DOUT pin function configuration:
 *      SI476X_DOUT_NOOP       - करो not modअगरy the behaviour
 *      SI476X_DOUT_TRISTATE   - put the pin in tristate condition,
 *                               enable 1MOhm pullकरोwn
 *      SI476X_DOUT_I2S_OUTPUT - set this pin to be digital out on I2S
 *                               port 1
 *      SI476X_DOUT_I2S_INPUT  - set this pin to be digital in on I2S
 *                               port 1
 * @xout: - XOUT pin function configuration:
 *	SI476X_XOUT_NOOP        - करो not modअगरy the behaviour
 *      SI476X_XOUT_TRISTATE    - put the pin in tristate condition,
 *                                enable 1MOhm pullकरोwn
 *      SI476X_XOUT_I2S_INPUT   - set this pin to be digital in on I2S
 *                                port 1
 *      SI476X_XOUT_MODE_SELECT - set this pin to be the input that
 *                                selects the mode of the I2S audio
 *                                combiner (analog or HD)
 *                                [SI4761/63/65/67 Only]
 *
 * Function वापसs 0 on success and negative error code on failure
 */
पूर्णांक si476x_core_cmd_dig_audio_pin_cfg(काष्ठा  si476x_core *core,
				      क्रमागत si476x_dclk_config dclk,
				      क्रमागत si476x_dfs_config  dfs,
				      क्रमागत si476x_करोut_config करोut,
				      क्रमागत si476x_xout_config xout)
अणु
	u8       resp[CMD_DIG_AUDIO_PIN_CFG_NRESP];
	स्थिर u8 args[CMD_DIG_AUDIO_PIN_CFG_NARGS] = अणु
		PIN_CFG_BYTE(dclk),
		PIN_CFG_BYTE(dfs),
		PIN_CFG_BYTE(करोut),
		PIN_CFG_BYTE(xout),
	पूर्ण;

	वापस si476x_core_send_command(core, CMD_DIG_AUDIO_PIN_CFG,
					args, ARRAY_SIZE(args),
					resp, ARRAY_SIZE(resp),
					SI476X_DEFAULT_TIMEOUT);
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_cmd_dig_audio_pin_cfg);

/**
 * si476x_cmd_zअगर_pin_cfg - send 'ZIF_PIN_CFG_COMMAND'
 * @core: - device to send the command to
 * @iqclk: - IQCL pin function configuration:
 *       SI476X_IQCLK_NOOP     - करो not modअगरy the behaviour
 *       SI476X_IQCLK_TRISTATE - put the pin in tristate condition,
 *                               enable 1MOhm pullकरोwn
 *       SI476X_IQCLK_IQ       - set pin to be a part of I/Q पूर्णांकerace
 *                               in master mode
 * @iqfs: - IQFS pin function configuration:
 *       SI476X_IQFS_NOOP     - करो not modअगरy the behaviour
 *       SI476X_IQFS_TRISTATE - put the pin in tristate condition,
 *                              enable 1MOhm pullकरोwn
 *       SI476X_IQFS_IQ       - set pin to be a part of I/Q पूर्णांकerace
 *                              in master mode
 * @iout: - IOUT pin function configuration:
 *       SI476X_IOUT_NOOP     - करो not modअगरy the behaviour
 *       SI476X_IOUT_TRISTATE - put the pin in tristate condition,
 *                              enable 1MOhm pullकरोwn
 *       SI476X_IOUT_OUTPUT   - set pin to be I out
 * @qout: - QOUT pin function configuration:
 *       SI476X_QOUT_NOOP     - करो not modअगरy the behaviour
 *       SI476X_QOUT_TRISTATE - put the pin in tristate condition,
 *                              enable 1MOhm pullकरोwn
 *       SI476X_QOUT_OUTPUT   - set pin to be Q out
 *
 * Function वापसs 0 on success and negative error code on failure
 */
पूर्णांक si476x_core_cmd_zअगर_pin_cfg(काष्ठा si476x_core *core,
				क्रमागत si476x_iqclk_config iqclk,
				क्रमागत si476x_iqfs_config iqfs,
				क्रमागत si476x_iout_config iout,
				क्रमागत si476x_qout_config qout)
अणु
	u8       resp[CMD_ZIF_PIN_CFG_NRESP];
	स्थिर u8 args[CMD_ZIF_PIN_CFG_NARGS] = अणु
		PIN_CFG_BYTE(iqclk),
		PIN_CFG_BYTE(iqfs),
		PIN_CFG_BYTE(iout),
		PIN_CFG_BYTE(qout),
	पूर्ण;

	वापस si476x_core_send_command(core, CMD_ZIF_PIN_CFG,
					args, ARRAY_SIZE(args),
					resp, ARRAY_SIZE(resp),
					SI476X_DEFAULT_TIMEOUT);
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_cmd_zअगर_pin_cfg);

/**
 * si476x_cmd_ic_link_gpo_ctl_pin_cfg - send
 * 'IC_LINK_GPIO_CTL_PIN_CFG' comand to the device
 * @core: - device to send the command to
 * @icin: - ICIN pin function configuration:
 *      SI476X_ICIN_NOOP      - करो not modअगरy the behaviour
 *      SI476X_ICIN_TRISTATE  - put the pin in tristate condition,
 *                              enable 1MOhm pullकरोwn
 *      SI476X_ICIN_GPO1_HIGH - set pin to be an output, drive it high
 *      SI476X_ICIN_GPO1_LOW  - set pin to be an output, drive it low
 *      SI476X_ICIN_IC_LINK   - set the pin to be a part of Inter-Chip link
 * @icip: - ICIP pin function configuration:
 *      SI476X_ICIP_NOOP      - करो not modअगरy the behaviour
 *      SI476X_ICIP_TRISTATE  - put the pin in tristate condition,
 *                              enable 1MOhm pullकरोwn
 *      SI476X_ICIP_GPO1_HIGH - set pin to be an output, drive it high
 *      SI476X_ICIP_GPO1_LOW  - set pin to be an output, drive it low
 *      SI476X_ICIP_IC_LINK   - set the pin to be a part of Inter-Chip link
 * @icon: - ICON pin function configuration:
 *      SI476X_ICON_NOOP     - करो not modअगरy the behaviour
 *      SI476X_ICON_TRISTATE - put the pin in tristate condition,
 *                             enable 1MOhm pullकरोwn
 *      SI476X_ICON_I2S      - set the pin to be a part of audio
 *                             पूर्णांकerface in slave mode (DCLK)
 *      SI476X_ICON_IC_LINK  - set the pin to be a part of Inter-Chip link
 * @icop: - ICOP pin function configuration:
 *      SI476X_ICOP_NOOP     - करो not modअगरy the behaviour
 *      SI476X_ICOP_TRISTATE - put the pin in tristate condition,
 *                             enable 1MOhm pullकरोwn
 *      SI476X_ICOP_I2S      - set the pin to be a part of audio
 *                             पूर्णांकerface in slave mode (DOUT)
 *                             [Si4761/63/65/67 Only]
 *      SI476X_ICOP_IC_LINK  - set the pin to be a part of Inter-Chip link
 *
 * Function वापसs 0 on success and negative error code on failure
 */
पूर्णांक si476x_core_cmd_ic_link_gpo_ctl_pin_cfg(काष्ठा si476x_core *core,
					    क्रमागत si476x_icin_config icin,
					    क्रमागत si476x_icip_config icip,
					    क्रमागत si476x_icon_config icon,
					    क्रमागत si476x_icop_config icop)
अणु
	u8       resp[CMD_IC_LINK_GPO_CTL_PIN_CFG_NRESP];
	स्थिर u8 args[CMD_IC_LINK_GPO_CTL_PIN_CFG_NARGS] = अणु
		PIN_CFG_BYTE(icin),
		PIN_CFG_BYTE(icip),
		PIN_CFG_BYTE(icon),
		PIN_CFG_BYTE(icop),
	पूर्ण;

	वापस si476x_core_send_command(core, CMD_IC_LINK_GPO_CTL_PIN_CFG,
					args, ARRAY_SIZE(args),
					resp, ARRAY_SIZE(resp),
					SI476X_DEFAULT_TIMEOUT);
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_cmd_ic_link_gpo_ctl_pin_cfg);

/**
 * si476x_cmd_ana_audio_pin_cfg - send 'ANA_AUDIO_PIN_CFG' to the
 * device
 * @core: - device to send the command to
 * @lrout: - LROUT pin function configuration:
 *       SI476X_LROUT_NOOP     - करो not modअगरy the behaviour
 *       SI476X_LROUT_TRISTATE - put the pin in tristate condition,
 *                               enable 1MOhm pullकरोwn
 *       SI476X_LROUT_AUDIO    - set pin to be audio output
 *       SI476X_LROUT_MPX      - set pin to be MPX output
 *
 * Function वापसs 0 on success and negative error code on failure
 */
पूर्णांक si476x_core_cmd_ana_audio_pin_cfg(काष्ठा si476x_core *core,
				      क्रमागत si476x_lrout_config lrout)
अणु
	u8       resp[CMD_ANA_AUDIO_PIN_CFG_NRESP];
	स्थिर u8 args[CMD_ANA_AUDIO_PIN_CFG_NARGS] = अणु
		PIN_CFG_BYTE(lrout),
	पूर्ण;

	वापस si476x_core_send_command(core, CMD_ANA_AUDIO_PIN_CFG,
					args, ARRAY_SIZE(args),
					resp, ARRAY_SIZE(resp),
					SI476X_DEFAULT_TIMEOUT);
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_cmd_ana_audio_pin_cfg);


/**
 * si476x_cmd_पूर्णांकb_pin_cfg - send 'INTB_PIN_CFG' command to the device
 * @core: - device to send the command to
 * @पूर्णांकb: - INTB pin function configuration:
 *      SI476X_INTB_NOOP     - करो not modअगरy the behaviour
 *      SI476X_INTB_TRISTATE - put the pin in tristate condition,
 *                             enable 1MOhm pullकरोwn
 *      SI476X_INTB_DAUDIO   - set pin to be a part of digital
 *                             audio पूर्णांकerface in slave mode
 *      SI476X_INTB_IRQ      - set pin to be an पूर्णांकerrupt request line
 * @a1: - A1 pin function configuration:
 *      SI476X_A1_NOOP     - करो not modअगरy the behaviour
 *      SI476X_A1_TRISTATE - put the pin in tristate condition,
 *                           enable 1MOhm pullकरोwn
 *      SI476X_A1_IRQ      - set pin to be an पूर्णांकerrupt request line
 *
 * Function वापसs 0 on success and negative error code on failure
 */
अटल पूर्णांक si476x_core_cmd_पूर्णांकb_pin_cfg_a10(काष्ठा si476x_core *core,
					    क्रमागत si476x_पूर्णांकb_config पूर्णांकb,
					    क्रमागत si476x_a1_config a1)
अणु
	u8       resp[CMD_INTB_PIN_CFG_A10_NRESP];
	स्थिर u8 args[CMD_INTB_PIN_CFG_NARGS] = अणु
		PIN_CFG_BYTE(पूर्णांकb),
		PIN_CFG_BYTE(a1),
	पूर्ण;

	वापस si476x_core_send_command(core, CMD_INTB_PIN_CFG,
					args, ARRAY_SIZE(args),
					resp, ARRAY_SIZE(resp),
					SI476X_DEFAULT_TIMEOUT);
पूर्ण

अटल पूर्णांक si476x_core_cmd_पूर्णांकb_pin_cfg_a20(काष्ठा si476x_core *core,
					    क्रमागत si476x_पूर्णांकb_config पूर्णांकb,
					    क्रमागत si476x_a1_config a1)
अणु
	u8       resp[CMD_INTB_PIN_CFG_A20_NRESP];
	स्थिर u8 args[CMD_INTB_PIN_CFG_NARGS] = अणु
		PIN_CFG_BYTE(पूर्णांकb),
		PIN_CFG_BYTE(a1),
	पूर्ण;

	वापस si476x_core_send_command(core, CMD_INTB_PIN_CFG,
					args, ARRAY_SIZE(args),
					resp, ARRAY_SIZE(resp),
					SI476X_DEFAULT_TIMEOUT);
पूर्ण



/**
 * si476x_cmd_am_rsq_status - send 'AM_RSQ_STATUS' command to the
 * device
 * @core:  - device to send the command to
 * @rsqargs: - poपूर्णांकer to a काष्ठाure containing a group of sub-args
 *             relevant to sending the RSQ status command
 * @report: - all संकेत quality inक्रमmation retured by the command
 *           (अगर शून्य then the output of the command is ignored)
 *
 * Function वापसs 0 on success and negative error code on failure
 */
पूर्णांक si476x_core_cmd_am_rsq_status(काष्ठा si476x_core *core,
				  काष्ठा si476x_rsq_status_args *rsqargs,
				  काष्ठा si476x_rsq_status_report *report)
अणु
	पूर्णांक err;
	u8       resp[CMD_AM_RSQ_STATUS_NRESP];
	स्थिर u8 args[CMD_AM_RSQ_STATUS_NARGS] = अणु
		rsqargs->rsqack << 3 | rsqargs->attune << 2 |
		rsqargs->cancel << 1 | rsqargs->stcack,
	पूर्ण;

	err = si476x_core_send_command(core, CMD_AM_RSQ_STATUS,
				       args, ARRAY_SIZE(args),
				       resp, ARRAY_SIZE(resp),
				       SI476X_DEFAULT_TIMEOUT);
	/*
	 * Besides getting received संकेत quality inक्रमmation this
	 * command can be used to just acknowledge dअगरferent पूर्णांकerrupt
	 * flags in those हालs it is useless to copy and parse
	 * received data so user can pass शून्य, and thus aव्योम
	 * unnecessary copying.
	 */
	अगर (!report)
		वापस err;

	report->snrhपूर्णांक		= 0x08 & resp[1];
	report->snrlपूर्णांक		= 0x04 & resp[1];
	report->rssihपूर्णांक	= 0x02 & resp[1];
	report->rssilपूर्णांक	= 0x01 & resp[1];

	report->bltf		= 0x80 & resp[2];
	report->snr_पढ़ोy	= 0x20 & resp[2];
	report->rssiपढ़ोy	= 0x08 & resp[2];
	report->afcrl		= 0x02 & resp[2];
	report->valid		= 0x01 & resp[2];

	report->पढ़ोfreq	= get_unaligned_be16(resp + 3);
	report->freqoff		= resp[5];
	report->rssi		= resp[6];
	report->snr		= resp[7];
	report->lassi		= resp[9];
	report->hassi		= resp[10];
	report->mult		= resp[11];
	report->dev		= resp[12];

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_cmd_am_rsq_status);

पूर्णांक si476x_core_cmd_fm_acf_status(काष्ठा si476x_core *core,
			     काष्ठा si476x_acf_status_report *report)
अणु
	पूर्णांक err;
	u8       resp[CMD_FM_ACF_STATUS_NRESP];
	स्थिर u8 args[CMD_FM_ACF_STATUS_NARGS] = अणु
		0x0,
	पूर्ण;

	अगर (!report)
		वापस -EINVAL;

	err = si476x_core_send_command(core, CMD_FM_ACF_STATUS,
				       args, ARRAY_SIZE(args),
				       resp, ARRAY_SIZE(resp),
				       SI476X_DEFAULT_TIMEOUT);
	अगर (err < 0)
		वापस err;

	report->blend_पूर्णांक	= resp[1] & SI476X_ACF_BLEND_INT;
	report->hblend_पूर्णांक	= resp[1] & SI476X_ACF_HIBLEND_INT;
	report->hicut_पूर्णांक	= resp[1] & SI476X_ACF_HICUT_INT;
	report->chbw_पूर्णांक	= resp[1] & SI476X_ACF_CHBW_INT;
	report->sofपंचांगute_पूर्णांक	= resp[1] & SI476X_ACF_SOFTMUTE_INT;
	report->smute		= resp[2] & SI476X_ACF_SMUTE;
	report->smattn		= resp[3] & SI476X_ACF_SMATTN;
	report->chbw		= resp[4];
	report->hicut		= resp[5];
	report->hiblend		= resp[6];
	report->pilot		= resp[7] & SI476X_ACF_PILOT;
	report->stblend		= resp[7] & SI476X_ACF_STBLEND;

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_cmd_fm_acf_status);

पूर्णांक si476x_core_cmd_am_acf_status(काष्ठा si476x_core *core,
				  काष्ठा si476x_acf_status_report *report)
अणु
	पूर्णांक err;
	u8       resp[CMD_AM_ACF_STATUS_NRESP];
	स्थिर u8 args[CMD_AM_ACF_STATUS_NARGS] = अणु
		0x0,
	पूर्ण;

	अगर (!report)
		वापस -EINVAL;

	err = si476x_core_send_command(core, CMD_AM_ACF_STATUS,
				       args, ARRAY_SIZE(args),
				       resp, ARRAY_SIZE(resp),
				       SI476X_DEFAULT_TIMEOUT);
	अगर (err < 0)
		वापस err;

	report->blend_पूर्णांक	= resp[1] & SI476X_ACF_BLEND_INT;
	report->hblend_पूर्णांक	= resp[1] & SI476X_ACF_HIBLEND_INT;
	report->hicut_पूर्णांक	= resp[1] & SI476X_ACF_HICUT_INT;
	report->chbw_पूर्णांक	= resp[1] & SI476X_ACF_CHBW_INT;
	report->sofपंचांगute_पूर्णांक	= resp[1] & SI476X_ACF_SOFTMUTE_INT;
	report->smute		= resp[2] & SI476X_ACF_SMUTE;
	report->smattn		= resp[3] & SI476X_ACF_SMATTN;
	report->chbw		= resp[4];
	report->hicut		= resp[5];

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_cmd_am_acf_status);


/**
 * si476x_cmd_fm_seek_start - send 'FM_SEEK_START' command to the
 * device
 * @core:  - device to send the command to
 * @seekup: - अगर set the direction of the search is 'up'
 * @wrap:   - अगर set seek wraps when hitting band limit
 *
 * This function begins search क्रम a valid station. The station is
 * considered valid when 'FM_VALID_SNR_THRESHOLD' and
 * 'FM_VALID_RSSI_THRESHOLD' and 'FM_VALID_MAX_TUNE_ERROR' criteria
 * are met.
पूर्ण *
 * Function वापसs 0 on success and negative error code on failure
 */
पूर्णांक si476x_core_cmd_fm_seek_start(काष्ठा si476x_core *core,
				  bool seekup, bool wrap)
अणु
	u8       resp[CMD_FM_SEEK_START_NRESP];
	स्थिर u8 args[CMD_FM_SEEK_START_NARGS] = अणु
		seekup << 3 | wrap << 2,
	पूर्ण;

	वापस si476x_cmd_tune_seek_freq(core, CMD_FM_SEEK_START,
					 args, माप(args),
					 resp, माप(resp));
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_cmd_fm_seek_start);

/**
 * si476x_cmd_fm_rds_status - send 'FM_RDS_STATUS' command to the
 * device
 * @core: - device to send the command to
 * @status_only: - अगर set the data is not हटाओd from RDSFIFO,
 *                RDSFIFOUSED is not decremented and data in all the
 *                rest RDS data contains the last valid info received
 * @mtfअगरo: अगर set the command clears RDS receive FIFO
 * @पूर्णांकack: अगर set the command clards the RDSINT bit.
 * @report: - all संकेत quality inक्रमmation retured by the command
 *           (अगर शून्य then the output of the command is ignored)
 *
 * Function वापसs 0 on success and negative error code on failure
 */
पूर्णांक si476x_core_cmd_fm_rds_status(काष्ठा si476x_core *core,
				  bool status_only,
				  bool mtfअगरo,
				  bool पूर्णांकack,
				  काष्ठा si476x_rds_status_report *report)
अणु
	पूर्णांक err;
	u8       resp[CMD_FM_RDS_STATUS_NRESP];
	स्थिर u8 args[CMD_FM_RDS_STATUS_NARGS] = अणु
		status_only << 2 | mtfअगरo << 1 | पूर्णांकack,
	पूर्ण;

	err = si476x_core_send_command(core, CMD_FM_RDS_STATUS,
				       args, ARRAY_SIZE(args),
				       resp, ARRAY_SIZE(resp),
				       SI476X_DEFAULT_TIMEOUT);
	/*
	 * Besides getting RDS status inक्रमmation this command can be
	 * used to just acknowledge dअगरferent पूर्णांकerrupt flags in those
	 * हालs it is useless to copy and parse received data so user
	 * can pass शून्य, and thus aव्योम unnecessary copying.
	 */
	अगर (err < 0 || report == शून्य)
		वापस err;

	report->rdstpptyपूर्णांक	= 0x10 & resp[1];
	report->rdspiपूर्णांक	= 0x08 & resp[1];
	report->rdssyncपूर्णांक	= 0x02 & resp[1];
	report->rdsfअगरoपूर्णांक	= 0x01 & resp[1];

	report->tpptyvalid	= 0x10 & resp[2];
	report->pivalid		= 0x08 & resp[2];
	report->rdssync		= 0x02 & resp[2];
	report->rdsfअगरolost	= 0x01 & resp[2];

	report->tp		= 0x20 & resp[3];
	report->pty		= 0x1f & resp[3];

	report->pi		= get_unaligned_be16(resp + 4);
	report->rdsfअगरoused	= resp[6];

	report->ble[V4L2_RDS_BLOCK_A]	= 0xc0 & resp[7];
	report->ble[V4L2_RDS_BLOCK_B]	= 0x30 & resp[7];
	report->ble[V4L2_RDS_BLOCK_C]	= 0x0c & resp[7];
	report->ble[V4L2_RDS_BLOCK_D]	= 0x03 & resp[7];

	report->rds[V4L2_RDS_BLOCK_A].block = V4L2_RDS_BLOCK_A;
	report->rds[V4L2_RDS_BLOCK_A].msb = resp[8];
	report->rds[V4L2_RDS_BLOCK_A].lsb = resp[9];

	report->rds[V4L2_RDS_BLOCK_B].block = V4L2_RDS_BLOCK_B;
	report->rds[V4L2_RDS_BLOCK_B].msb = resp[10];
	report->rds[V4L2_RDS_BLOCK_B].lsb = resp[11];

	report->rds[V4L2_RDS_BLOCK_C].block = V4L2_RDS_BLOCK_C;
	report->rds[V4L2_RDS_BLOCK_C].msb = resp[12];
	report->rds[V4L2_RDS_BLOCK_C].lsb = resp[13];

	report->rds[V4L2_RDS_BLOCK_D].block = V4L2_RDS_BLOCK_D;
	report->rds[V4L2_RDS_BLOCK_D].msb = resp[14];
	report->rds[V4L2_RDS_BLOCK_D].lsb = resp[15];

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_cmd_fm_rds_status);

पूर्णांक si476x_core_cmd_fm_rds_blockcount(काष्ठा si476x_core *core,
				bool clear,
				काष्ठा si476x_rds_blockcount_report *report)
अणु
	पूर्णांक err;
	u8       resp[CMD_FM_RDS_BLOCKCOUNT_NRESP];
	स्थिर u8 args[CMD_FM_RDS_BLOCKCOUNT_NARGS] = अणु
		clear,
	पूर्ण;

	अगर (!report)
		वापस -EINVAL;

	err = si476x_core_send_command(core, CMD_FM_RDS_BLOCKCOUNT,
				       args, ARRAY_SIZE(args),
				       resp, ARRAY_SIZE(resp),
				       SI476X_DEFAULT_TIMEOUT);

	अगर (!err) अणु
		report->expected	= get_unaligned_be16(resp + 2);
		report->received	= get_unaligned_be16(resp + 4);
		report->uncorrectable	= get_unaligned_be16(resp + 6);
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_cmd_fm_rds_blockcount);

पूर्णांक si476x_core_cmd_fm_phase_भागersity(काष्ठा si476x_core *core,
				       क्रमागत si476x_phase_भागersity_mode mode)
अणु
	u8       resp[CMD_FM_PHASE_DIVERSITY_NRESP];
	स्थिर u8 args[CMD_FM_PHASE_DIVERSITY_NARGS] = अणु
		mode & 0x07,
	पूर्ण;

	वापस si476x_core_send_command(core, CMD_FM_PHASE_DIVERSITY,
					args, ARRAY_SIZE(args),
					resp, ARRAY_SIZE(resp),
					SI476X_DEFAULT_TIMEOUT);
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_cmd_fm_phase_भागersity);
/**
 * si476x_core_cmd_fm_phase_भाग_status() - get the phase भागersity
 * status
 *
 * @core: si476x device
 *
 * NOTE caller must hold core lock
 *
 * Function वापसs the value of the status bit in हाल of success and
 * negative error code in हाल of failre.
 */
पूर्णांक si476x_core_cmd_fm_phase_भाग_status(काष्ठा si476x_core *core)
अणु
	पूर्णांक err;
	u8 resp[CMD_FM_PHASE_DIV_STATUS_NRESP];

	err = si476x_core_send_command(core, CMD_FM_PHASE_DIV_STATUS,
				       शून्य, 0,
				       resp, ARRAY_SIZE(resp),
				       SI476X_DEFAULT_TIMEOUT);

	वापस (err < 0) ? err : resp[1];
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_cmd_fm_phase_भाग_status);


/**
 * si476x_cmd_am_seek_start - send 'FM_SEEK_START' command to the
 * device
 * @core:  - device to send the command to
 * @seekup: - अगर set the direction of the search is 'up'
 * @wrap:   - अगर set seek wraps when hitting band limit
 *
 * This function begins search क्रम a valid station. The station is
 * considered valid when 'FM_VALID_SNR_THRESHOLD' and
 * 'FM_VALID_RSSI_THRESHOLD' and 'FM_VALID_MAX_TUNE_ERROR' criteria
 * are met.
 *
 * Function वापसs 0 on success and negative error code on failure
 */
पूर्णांक si476x_core_cmd_am_seek_start(काष्ठा si476x_core *core,
				  bool seekup, bool wrap)
अणु
	u8       resp[CMD_AM_SEEK_START_NRESP];
	स्थिर u8 args[CMD_AM_SEEK_START_NARGS] = अणु
		seekup << 3 | wrap << 2,
	पूर्ण;

	वापस si476x_cmd_tune_seek_freq(core,  CMD_AM_SEEK_START,
					 args, माप(args),
					 resp, माप(resp));
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_cmd_am_seek_start);



अटल पूर्णांक si476x_core_cmd_घातer_up_a10(काष्ठा si476x_core *core,
					काष्ठा si476x_घातer_up_args *puargs)
अणु
	u8       resp[CMD_POWER_UP_A10_NRESP];
	स्थिर bool पूर्णांकsel = (core->pinmux.a1 == SI476X_A1_IRQ);
	स्थिर bool ctsen  = (core->client->irq != 0);
	स्थिर u8 args[CMD_POWER_UP_A10_NARGS] = अणु
		0xF7,		/* Reserved, always 0xF7 */
		0x3F & puargs->xcload,	/* First two bits are reserved to be
				 * zeros */
		ctsen << 7 | पूर्णांकsel << 6 | 0x07, /* Last five bits
						   * are reserved to
						   * be written as 0x7 */
		puargs->func << 4 | puargs->freq,
		0x11,		/* Reserved, always 0x11 */
	पूर्ण;

	वापस si476x_core_send_command(core, CMD_POWER_UP,
					args, ARRAY_SIZE(args),
					resp, ARRAY_SIZE(resp),
					SI476X_TIMEOUT_POWER_UP);
पूर्ण

अटल पूर्णांक si476x_core_cmd_घातer_up_a20(काष्ठा si476x_core *core,
				 काष्ठा si476x_घातer_up_args *puargs)
अणु
	u8       resp[CMD_POWER_UP_A20_NRESP];
	स्थिर bool पूर्णांकsel = (core->pinmux.a1 == SI476X_A1_IRQ);
	स्थिर bool ctsen  = (core->client->irq != 0);
	स्थिर u8 args[CMD_POWER_UP_A20_NARGS] = अणु
		puargs->ibias6x << 7 | puargs->xstart,
		0x3F & puargs->xcload,	/* First two bits are reserved to be
					 * zeros */
		ctsen << 7 | पूर्णांकsel << 6 | puargs->fastboot << 5 |
		puargs->xbiashc << 3 | puargs->xbias,
		puargs->func << 4 | puargs->freq,
		0x10 | puargs->xmode,
	पूर्ण;

	वापस si476x_core_send_command(core, CMD_POWER_UP,
					args, ARRAY_SIZE(args),
					resp, ARRAY_SIZE(resp),
					SI476X_TIMEOUT_POWER_UP);
पूर्ण

अटल पूर्णांक si476x_core_cmd_घातer_करोwn_a10(काष्ठा si476x_core *core,
					  काष्ठा si476x_घातer_करोwn_args *pdargs)
अणु
	u8 resp[CMD_POWER_DOWN_A10_NRESP];

	वापस si476x_core_send_command(core, CMD_POWER_DOWN,
					शून्य, 0,
					resp, ARRAY_SIZE(resp),
					SI476X_DEFAULT_TIMEOUT);
पूर्ण

अटल पूर्णांक si476x_core_cmd_घातer_करोwn_a20(काष्ठा si476x_core *core,
					  काष्ठा si476x_घातer_करोwn_args *pdargs)
अणु
	u8 resp[CMD_POWER_DOWN_A20_NRESP];
	स्थिर u8 args[CMD_POWER_DOWN_A20_NARGS] = अणु
		pdargs->xosc,
	पूर्ण;
	वापस si476x_core_send_command(core, CMD_POWER_DOWN,
					args, ARRAY_SIZE(args),
					resp, ARRAY_SIZE(resp),
					SI476X_DEFAULT_TIMEOUT);
पूर्ण

अटल पूर्णांक si476x_core_cmd_am_tune_freq_a10(काष्ठा si476x_core *core,
					काष्ठा si476x_tune_freq_args *tuneargs)
अणु

	स्थिर पूर्णांक am_freq = tuneargs->freq;
	u8       resp[CMD_AM_TUNE_FREQ_NRESP];
	स्थिर u8 args[CMD_AM_TUNE_FREQ_NARGS] = अणु
		(tuneargs->hd << 6),
		msb(am_freq),
		lsb(am_freq),
	पूर्ण;

	वापस si476x_cmd_tune_seek_freq(core, CMD_AM_TUNE_FREQ, args,
					 माप(args),
					 resp, माप(resp));
पूर्ण

अटल पूर्णांक si476x_core_cmd_am_tune_freq_a20(काष्ठा si476x_core *core,
					काष्ठा si476x_tune_freq_args *tuneargs)
अणु
	स्थिर पूर्णांक am_freq = tuneargs->freq;
	u8       resp[CMD_AM_TUNE_FREQ_NRESP];
	स्थिर u8 args[CMD_AM_TUNE_FREQ_NARGS] = अणु
		(tuneargs->zअगरsr << 6) | (tuneargs->injside & 0x03),
		msb(am_freq),
		lsb(am_freq),
	पूर्ण;

	वापस si476x_cmd_tune_seek_freq(core, CMD_AM_TUNE_FREQ,
					 args, माप(args),
					 resp, माप(resp));
पूर्ण

अटल पूर्णांक si476x_core_cmd_fm_rsq_status_a10(काष्ठा si476x_core *core,
					काष्ठा si476x_rsq_status_args *rsqargs,
					काष्ठा si476x_rsq_status_report *report)
अणु
	पूर्णांक err;
	u8       resp[CMD_FM_RSQ_STATUS_A10_NRESP];
	स्थिर u8 args[CMD_FM_RSQ_STATUS_A10_NARGS] = अणु
		rsqargs->rsqack << 3 | rsqargs->attune << 2 |
		rsqargs->cancel << 1 | rsqargs->stcack,
	पूर्ण;

	err = si476x_core_send_command(core, CMD_FM_RSQ_STATUS,
				       args, ARRAY_SIZE(args),
				       resp, ARRAY_SIZE(resp),
				       SI476X_DEFAULT_TIMEOUT);
	/*
	 * Besides getting received संकेत quality inक्रमmation this
	 * command can be used to just acknowledge dअगरferent पूर्णांकerrupt
	 * flags in those हालs it is useless to copy and parse
	 * received data so user can pass शून्य, and thus aव्योम
	 * unnecessary copying.
	 */
	अगर (err < 0 || report == शून्य)
		वापस err;

	report->multhपूर्णांक	= 0x80 & resp[1];
	report->multlपूर्णांक	= 0x40 & resp[1];
	report->snrhपूर्णांक		= 0x08 & resp[1];
	report->snrlपूर्णांक		= 0x04 & resp[1];
	report->rssihपूर्णांक	= 0x02 & resp[1];
	report->rssilपूर्णांक	= 0x01 & resp[1];

	report->bltf		= 0x80 & resp[2];
	report->snr_पढ़ोy	= 0x20 & resp[2];
	report->rssiपढ़ोy	= 0x08 & resp[2];
	report->afcrl		= 0x02 & resp[2];
	report->valid		= 0x01 & resp[2];

	report->पढ़ोfreq	= get_unaligned_be16(resp + 3);
	report->freqoff		= resp[5];
	report->rssi		= resp[6];
	report->snr		= resp[7];
	report->lassi		= resp[9];
	report->hassi		= resp[10];
	report->mult		= resp[11];
	report->dev		= resp[12];
	report->पढ़ोantcap	= get_unaligned_be16(resp + 13);
	report->assi		= resp[15];
	report->usn		= resp[16];

	वापस err;
पूर्ण

अटल पूर्णांक si476x_core_cmd_fm_rsq_status_a20(काष्ठा si476x_core *core,
				     काष्ठा si476x_rsq_status_args *rsqargs,
				     काष्ठा si476x_rsq_status_report *report)
अणु
	पूर्णांक err;
	u8       resp[CMD_FM_RSQ_STATUS_A10_NRESP];
	स्थिर u8 args[CMD_FM_RSQ_STATUS_A30_NARGS] = अणु
		rsqargs->primary << 4 | rsqargs->rsqack << 3 |
		rsqargs->attune  << 2 | rsqargs->cancel << 1 |
		rsqargs->stcack,
	पूर्ण;

	err = si476x_core_send_command(core, CMD_FM_RSQ_STATUS,
				       args, ARRAY_SIZE(args),
				       resp, ARRAY_SIZE(resp),
				       SI476X_DEFAULT_TIMEOUT);
	/*
	 * Besides getting received संकेत quality inक्रमmation this
	 * command can be used to just acknowledge dअगरferent पूर्णांकerrupt
	 * flags in those हालs it is useless to copy and parse
	 * received data so user can pass शून्य, and thus aव्योम
	 * unnecessary copying.
	 */
	अगर (err < 0 || report == शून्य)
		वापस err;

	report->multhपूर्णांक	= 0x80 & resp[1];
	report->multlपूर्णांक	= 0x40 & resp[1];
	report->snrhपूर्णांक		= 0x08 & resp[1];
	report->snrlपूर्णांक		= 0x04 & resp[1];
	report->rssihपूर्णांक	= 0x02 & resp[1];
	report->rssilपूर्णांक	= 0x01 & resp[1];

	report->bltf		= 0x80 & resp[2];
	report->snr_पढ़ोy	= 0x20 & resp[2];
	report->rssiपढ़ोy	= 0x08 & resp[2];
	report->afcrl		= 0x02 & resp[2];
	report->valid		= 0x01 & resp[2];

	report->पढ़ोfreq	= get_unaligned_be16(resp + 3);
	report->freqoff		= resp[5];
	report->rssi		= resp[6];
	report->snr		= resp[7];
	report->lassi		= resp[9];
	report->hassi		= resp[10];
	report->mult		= resp[11];
	report->dev		= resp[12];
	report->पढ़ोantcap	= get_unaligned_be16(resp + 13);
	report->assi		= resp[15];
	report->usn		= resp[16];

	वापस err;
पूर्ण


अटल पूर्णांक si476x_core_cmd_fm_rsq_status_a30(काष्ठा si476x_core *core,
					काष्ठा si476x_rsq_status_args *rsqargs,
					काष्ठा si476x_rsq_status_report *report)
अणु
	पूर्णांक err;
	u8       resp[CMD_FM_RSQ_STATUS_A30_NRESP];
	स्थिर u8 args[CMD_FM_RSQ_STATUS_A30_NARGS] = अणु
		rsqargs->primary << 4 | rsqargs->rsqack << 3 |
		rsqargs->attune << 2 | rsqargs->cancel << 1 |
		rsqargs->stcack,
	पूर्ण;

	err = si476x_core_send_command(core, CMD_FM_RSQ_STATUS,
				       args, ARRAY_SIZE(args),
				       resp, ARRAY_SIZE(resp),
				       SI476X_DEFAULT_TIMEOUT);
	/*
	 * Besides getting received संकेत quality inक्रमmation this
	 * command can be used to just acknowledge dअगरferent पूर्णांकerrupt
	 * flags in those हालs it is useless to copy and parse
	 * received data so user can pass शून्य, and thus aव्योम
	 * unnecessary copying.
	 */
	अगर (err < 0 || report == शून्य)
		वापस err;

	report->multhपूर्णांक	= 0x80 & resp[1];
	report->multlपूर्णांक	= 0x40 & resp[1];
	report->snrhपूर्णांक		= 0x08 & resp[1];
	report->snrlपूर्णांक		= 0x04 & resp[1];
	report->rssihपूर्णांक	= 0x02 & resp[1];
	report->rssilपूर्णांक	= 0x01 & resp[1];

	report->bltf		= 0x80 & resp[2];
	report->snr_पढ़ोy	= 0x20 & resp[2];
	report->rssiपढ़ोy	= 0x08 & resp[2];
	report->injside         = 0x04 & resp[2];
	report->afcrl		= 0x02 & resp[2];
	report->valid		= 0x01 & resp[2];

	report->पढ़ोfreq	= get_unaligned_be16(resp + 3);
	report->freqoff		= resp[5];
	report->rssi		= resp[6];
	report->snr		= resp[7];
	report->issi		= resp[8];
	report->lassi		= resp[9];
	report->hassi		= resp[10];
	report->mult		= resp[11];
	report->dev		= resp[12];
	report->पढ़ोantcap	= get_unaligned_be16(resp + 13);
	report->assi		= resp[15];
	report->usn		= resp[16];

	report->pilotdev	= resp[17];
	report->rdsdev		= resp[18];
	report->assidev		= resp[19];
	report->strongdev	= resp[20];
	report->rdspi		= get_unaligned_be16(resp + 21);

	वापस err;
पूर्ण

अटल पूर्णांक si476x_core_cmd_fm_tune_freq_a10(काष्ठा si476x_core *core,
					काष्ठा si476x_tune_freq_args *tuneargs)
अणु
	u8       resp[CMD_FM_TUNE_FREQ_NRESP];
	स्थिर u8 args[CMD_FM_TUNE_FREQ_A10_NARGS] = अणु
		(tuneargs->hd << 6) | (tuneargs->tunemode << 4)
		| (tuneargs->smoothmetrics << 2),
		msb(tuneargs->freq),
		lsb(tuneargs->freq),
		msb(tuneargs->antcap),
		lsb(tuneargs->antcap)
	पूर्ण;

	वापस si476x_cmd_tune_seek_freq(core, CMD_FM_TUNE_FREQ,
					 args, माप(args),
					 resp, माप(resp));
पूर्ण

अटल पूर्णांक si476x_core_cmd_fm_tune_freq_a20(काष्ठा si476x_core *core,
					काष्ठा si476x_tune_freq_args *tuneargs)
अणु
	u8       resp[CMD_FM_TUNE_FREQ_NRESP];
	स्थिर u8 args[CMD_FM_TUNE_FREQ_A20_NARGS] = अणु
		(tuneargs->hd << 6) | (tuneargs->tunemode << 4)
		|  (tuneargs->smoothmetrics << 2) | (tuneargs->injside),
		msb(tuneargs->freq),
		lsb(tuneargs->freq),
	पूर्ण;

	वापस si476x_cmd_tune_seek_freq(core, CMD_FM_TUNE_FREQ,
					 args, माप(args),
					 resp, माप(resp));
पूर्ण

अटल पूर्णांक si476x_core_cmd_agc_status_a20(काष्ठा si476x_core *core,
					काष्ठा si476x_agc_status_report *report)
अणु
	पूर्णांक err;
	u8 resp[CMD_AGC_STATUS_NRESP_A20];

	अगर (!report)
		वापस -EINVAL;

	err = si476x_core_send_command(core, CMD_AGC_STATUS,
				       शून्य, 0,
				       resp, ARRAY_SIZE(resp),
				       SI476X_DEFAULT_TIMEOUT);
	अगर (err < 0)
		वापस err;

	report->mxhi		= resp[1] & SI476X_AGC_MXHI;
	report->mxlo		= resp[1] & SI476X_AGC_MXLO;
	report->lnahi		= resp[1] & SI476X_AGC_LNAHI;
	report->lnalo		= resp[1] & SI476X_AGC_LNALO;
	report->fmagc1		= resp[2];
	report->fmagc2		= resp[3];
	report->pgagain		= resp[4];
	report->fmwblang	= resp[5];

	वापस err;
पूर्ण

अटल पूर्णांक si476x_core_cmd_agc_status_a10(काष्ठा si476x_core *core,
					काष्ठा si476x_agc_status_report *report)
अणु
	पूर्णांक err;
	u8 resp[CMD_AGC_STATUS_NRESP_A10];

	अगर (!report)
		वापस -EINVAL;

	err = si476x_core_send_command(core, CMD_AGC_STATUS,
				       शून्य, 0,
				       resp, ARRAY_SIZE(resp),
				       SI476X_DEFAULT_TIMEOUT);
	अगर (err < 0)
		वापस err;

	report->mxhi	= resp[1] & SI476X_AGC_MXHI;
	report->mxlo	= resp[1] & SI476X_AGC_MXLO;
	report->lnahi	= resp[1] & SI476X_AGC_LNAHI;
	report->lnalo	= resp[1] & SI476X_AGC_LNALO;

	वापस err;
पूर्ण

प्रकार पूर्णांक (*tune_freq_func_t) (काष्ठा si476x_core *core,
				 काष्ठा si476x_tune_freq_args *tuneargs);

अटल काष्ठा अणु
	पूर्णांक (*घातer_up)(काष्ठा si476x_core *,
			काष्ठा si476x_घातer_up_args *);
	पूर्णांक (*घातer_करोwn)(काष्ठा si476x_core *,
			  काष्ठा si476x_घातer_करोwn_args *);

	tune_freq_func_t fm_tune_freq;
	tune_freq_func_t am_tune_freq;

	पूर्णांक (*fm_rsq_status)(काष्ठा si476x_core *,
			     काष्ठा si476x_rsq_status_args *,
			     काष्ठा si476x_rsq_status_report *);

	पूर्णांक (*agc_status)(काष्ठा si476x_core *,
			  काष्ठा si476x_agc_status_report *);
	पूर्णांक (*पूर्णांकb_pin_cfg)(काष्ठा si476x_core *core,
			    क्रमागत si476x_पूर्णांकb_config पूर्णांकb,
			    क्रमागत si476x_a1_config a1);
पूर्ण si476x_cmds_vtable[] = अणु
	[SI476X_REVISION_A10] = अणु
		.घातer_up	= si476x_core_cmd_घातer_up_a10,
		.घातer_करोwn	= si476x_core_cmd_घातer_करोwn_a10,
		.fm_tune_freq	= si476x_core_cmd_fm_tune_freq_a10,
		.am_tune_freq	= si476x_core_cmd_am_tune_freq_a10,
		.fm_rsq_status	= si476x_core_cmd_fm_rsq_status_a10,
		.agc_status	= si476x_core_cmd_agc_status_a10,
		.पूर्णांकb_pin_cfg   = si476x_core_cmd_पूर्णांकb_pin_cfg_a10,
	पूर्ण,
	[SI476X_REVISION_A20] = अणु
		.घातer_up	= si476x_core_cmd_घातer_up_a20,
		.घातer_करोwn	= si476x_core_cmd_घातer_करोwn_a20,
		.fm_tune_freq	= si476x_core_cmd_fm_tune_freq_a20,
		.am_tune_freq	= si476x_core_cmd_am_tune_freq_a20,
		.fm_rsq_status	= si476x_core_cmd_fm_rsq_status_a20,
		.agc_status	= si476x_core_cmd_agc_status_a20,
		.पूर्णांकb_pin_cfg   = si476x_core_cmd_पूर्णांकb_pin_cfg_a20,
	पूर्ण,
	[SI476X_REVISION_A30] = अणु
		.घातer_up	= si476x_core_cmd_घातer_up_a20,
		.घातer_करोwn	= si476x_core_cmd_घातer_करोwn_a20,
		.fm_tune_freq	= si476x_core_cmd_fm_tune_freq_a20,
		.am_tune_freq	= si476x_core_cmd_am_tune_freq_a20,
		.fm_rsq_status	= si476x_core_cmd_fm_rsq_status_a30,
		.agc_status	= si476x_core_cmd_agc_status_a20,
		.पूर्णांकb_pin_cfg   = si476x_core_cmd_पूर्णांकb_pin_cfg_a20,
	पूर्ण,
पूर्ण;

पूर्णांक si476x_core_cmd_घातer_up(काष्ठा si476x_core *core,
			     काष्ठा si476x_घातer_up_args *args)
अणु
	BUG_ON(core->revision > SI476X_REVISION_A30 ||
	       core->revision == -1);
	वापस si476x_cmds_vtable[core->revision].घातer_up(core, args);
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_cmd_घातer_up);

पूर्णांक si476x_core_cmd_घातer_करोwn(काष्ठा si476x_core *core,
			       काष्ठा si476x_घातer_करोwn_args *args)
अणु
	BUG_ON(core->revision > SI476X_REVISION_A30 ||
	       core->revision == -1);
	वापस si476x_cmds_vtable[core->revision].घातer_करोwn(core, args);
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_cmd_घातer_करोwn);

पूर्णांक si476x_core_cmd_fm_tune_freq(काष्ठा si476x_core *core,
				 काष्ठा si476x_tune_freq_args *args)
अणु
	BUG_ON(core->revision > SI476X_REVISION_A30 ||
	       core->revision == -1);
	वापस si476x_cmds_vtable[core->revision].fm_tune_freq(core, args);
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_cmd_fm_tune_freq);

पूर्णांक si476x_core_cmd_am_tune_freq(काष्ठा si476x_core *core,
				 काष्ठा si476x_tune_freq_args *args)
अणु
	BUG_ON(core->revision > SI476X_REVISION_A30 ||
	       core->revision == -1);
	वापस si476x_cmds_vtable[core->revision].am_tune_freq(core, args);
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_cmd_am_tune_freq);

पूर्णांक si476x_core_cmd_fm_rsq_status(काष्ठा si476x_core *core,
				  काष्ठा si476x_rsq_status_args *args,
				  काष्ठा si476x_rsq_status_report *report)

अणु
	BUG_ON(core->revision > SI476X_REVISION_A30 ||
	       core->revision == -1);
	वापस si476x_cmds_vtable[core->revision].fm_rsq_status(core, args,
								report);
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_cmd_fm_rsq_status);

पूर्णांक si476x_core_cmd_agc_status(काष्ठा si476x_core *core,
				  काष्ठा si476x_agc_status_report *report)

अणु
	BUG_ON(core->revision > SI476X_REVISION_A30 ||
	       core->revision == -1);
	वापस si476x_cmds_vtable[core->revision].agc_status(core, report);
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_cmd_agc_status);

पूर्णांक si476x_core_cmd_पूर्णांकb_pin_cfg(काष्ठा si476x_core *core,
			    क्रमागत si476x_पूर्णांकb_config पूर्णांकb,
			    क्रमागत si476x_a1_config a1)
अणु
	BUG_ON(core->revision > SI476X_REVISION_A30 ||
	       core->revision == -1);

	वापस si476x_cmds_vtable[core->revision].पूर्णांकb_pin_cfg(core, पूर्णांकb, a1);
पूर्ण
EXPORT_SYMBOL_GPL(si476x_core_cmd_पूर्णांकb_pin_cfg);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Andrey Smirnov <andrew.smirnov@gmail.com>");
MODULE_DESCRIPTION("API for command exchange for si476x");
