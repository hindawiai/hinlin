<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * --------------------------------------------------------------------
 * Driver क्रम ST NFC Transceiver ST95HF
 * --------------------------------------------------------------------
 * Copyright (C) 2015 STMicroelectronics Pvt. Ltd. All rights reserved.
 */

#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/nfc.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/property.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/रुको.h>
#समावेश <net/nfc/digital.h>
#समावेश <net/nfc/nfc.h>

#समावेश "spi.h"

/* supported protocols */
#घोषणा ST95HF_SUPPORTED_PROT		(NFC_PROTO_ISO14443_MASK | \
					NFC_PROTO_ISO14443_B_MASK | \
					NFC_PROTO_ISO15693_MASK)
/* driver capabilities */
#घोषणा ST95HF_CAPABILITIES		NFC_DIGITAL_DRV_CAPS_IN_CRC

/* Command Send Interface */
/* ST95HF_COMMAND_SEND CMD Ids */
#घोषणा ECHO_CMD			0x55
#घोषणा WRITE_REGISTER_CMD		0x9
#घोषणा PROTOCOL_SELECT_CMD		0x2
#घोषणा SEND_RECEIVE_CMD		0x4

/* Select protocol codes */
#घोषणा ISO15693_PROTOCOL_CODE		0x1
#घोषणा ISO14443A_PROTOCOL_CODE		0x2
#घोषणा ISO14443B_PROTOCOL_CODE		0x3

/*
 * head room len is 3
 * 1 byte क्रम control byte
 * 1 byte क्रम cmd
 * 1 byte क्रम size
 */
#घोषणा ST95HF_HEADROOM_LEN		3

/*
 * tailroom is 1 क्रम ISO14443A
 * and 0 क्रम ISO14443B/ISO15693,
 * hence the max value 1 should be
 * taken.
 */
#घोषणा ST95HF_TAILROOM_LEN		1

/* Command Response पूर्णांकerface */
#घोषणा MAX_RESPONSE_BUFFER_SIZE	280
#घोषणा ECHORESPONSE			0x55
#घोषणा ST95HF_ERR_MASK			0xF
#घोषणा ST95HF_TIMEOUT_ERROR		0x87
#घोषणा ST95HF_NFCA_CRC_ERR_MASK	0x20
#घोषणा ST95HF_NFCB_CRC_ERR_MASK	0x01

/* ST95HF transmission flag values */
#घोषणा TRFLAG_NFCA_SHORT_FRAME		0x07
#घोषणा TRFLAG_NFCA_STD_FRAME		0x08
#घोषणा TRFLAG_NFCA_STD_FRAME_CRC	0x28

/* Misc defs */
#घोषणा HIGH				1
#घोषणा LOW				0
#घोषणा ISO14443A_RATS_REQ		0xE0
#घोषणा RATS_TB1_PRESENT_MASK		0x20
#घोषणा RATS_TA1_PRESENT_MASK		0x10
#घोषणा TB1_FWI_MASK			0xF0
#घोषणा WTX_REQ_FROM_TAG		0xF2

#घोषणा MAX_CMD_LEN			0x7

#घोषणा MAX_CMD_PARAMS			4
काष्ठा cmd अणु
	पूर्णांक cmd_len;
	अचिन्हित अक्षर cmd_id;
	अचिन्हित अक्षर no_cmd_params;
	अचिन्हित अक्षर cmd_params[MAX_CMD_PARAMS];
	क्रमागत req_type req;
पूर्ण;

काष्ठा param_list अणु
	पूर्णांक param_offset;
	पूर्णांक new_param_val;
पूर्ण;

/*
 * List of top-level cmds to be used पूर्णांकernally by the driver.
 * All these commands are build on top of ST95HF basic commands
 * such as SEND_RECEIVE_CMD, PROTOCOL_SELECT_CMD, etc.
 * These top level cmds are used पूर्णांकernally जबतक implementing various ops of
 * digital layer/driver probe or extending the digital framework layer क्रम
 * features that are not yet implemented there, क्रम example, WTX cmd handling.
 */
क्रमागत st95hf_cmd_list अणु
	CMD_ECHO,
	CMD_ISO14443A_CONFIG,
	CMD_ISO14443A_DEMOGAIN,
	CMD_ISO14443B_DEMOGAIN,
	CMD_ISO14443A_PROTOCOL_SELECT,
	CMD_ISO14443B_PROTOCOL_SELECT,
	CMD_WTX_RESPONSE,
	CMD_FIELD_OFF,
	CMD_ISO15693_PROTOCOL_SELECT,
पूर्ण;

अटल स्थिर काष्ठा cmd cmd_array[] = अणु
	[CMD_ECHO] = अणु
		.cmd_len = 0x2,
		.cmd_id = ECHO_CMD,
		.no_cmd_params = 0,
		.req = SYNC,
	पूर्ण,
	[CMD_ISO14443A_CONFIG] = अणु
		.cmd_len = 0x7,
		.cmd_id = WRITE_REGISTER_CMD,
		.no_cmd_params = 0x4,
		.cmd_params = अणु0x3A, 0x00, 0x5A, 0x04पूर्ण,
		.req = SYNC,
	पूर्ण,
	[CMD_ISO14443A_DEMOGAIN] = अणु
		.cmd_len = 0x7,
		.cmd_id = WRITE_REGISTER_CMD,
		.no_cmd_params = 0x4,
		.cmd_params = अणु0x68, 0x01, 0x01, 0xDFपूर्ण,
		.req = SYNC,
	पूर्ण,
	[CMD_ISO14443B_DEMOGAIN] = अणु
		.cmd_len = 0x7,
		.cmd_id = WRITE_REGISTER_CMD,
		.no_cmd_params = 0x4,
		.cmd_params = अणु0x68, 0x01, 0x01, 0x51पूर्ण,
		.req = SYNC,
	पूर्ण,
	[CMD_ISO14443A_PROTOCOL_SELECT] = अणु
		.cmd_len = 0x7,
		.cmd_id = PROTOCOL_SELECT_CMD,
		.no_cmd_params = 0x4,
		.cmd_params = अणुISO14443A_PROTOCOL_CODE, 0x00, 0x01, 0xA0पूर्ण,
		.req = SYNC,
	पूर्ण,
	[CMD_ISO14443B_PROTOCOL_SELECT] = अणु
		.cmd_len = 0x7,
		.cmd_id = PROTOCOL_SELECT_CMD,
		.no_cmd_params = 0x4,
		.cmd_params = अणुISO14443B_PROTOCOL_CODE, 0x01, 0x03, 0xFFपूर्ण,
		.req = SYNC,
	पूर्ण,
	[CMD_WTX_RESPONSE] = अणु
		.cmd_len = 0x6,
		.cmd_id = SEND_RECEIVE_CMD,
		.no_cmd_params = 0x3,
		.cmd_params = अणु0xF2, 0x00, TRFLAG_NFCA_STD_FRAME_CRCपूर्ण,
		.req = ASYNC,
	पूर्ण,
	[CMD_FIELD_OFF] = अणु
		.cmd_len = 0x5,
		.cmd_id = PROTOCOL_SELECT_CMD,
		.no_cmd_params = 0x2,
		.cmd_params = अणु0x0, 0x0पूर्ण,
		.req = SYNC,
	पूर्ण,
	[CMD_ISO15693_PROTOCOL_SELECT] = अणु
		.cmd_len = 0x5,
		.cmd_id = PROTOCOL_SELECT_CMD,
		.no_cmd_params = 0x2,
		.cmd_params = अणुISO15693_PROTOCOL_CODE, 0x0Dपूर्ण,
		.req = SYNC,
	पूर्ण,
पूर्ण;

/* st95_digital_cmd_complete_arg stores client context */
काष्ठा st95_digital_cmd_complete_arg अणु
	काष्ठा sk_buff *skb_resp;
	nfc_digital_cmd_complete_t complete_cb;
	व्योम *cb_usrarg;
	bool rats;
पूर्ण;

/*
 * काष्ठाure containing ST95HF driver specअगरic data.
 * @spicontext: काष्ठाure containing inक्रमmation required
 *	क्रम spi communication between st95hf and host.
 * @ddev: nfc digital device object.
 * @nfcdev: nfc device object.
 * @enable_gpio: gpio used to enable st95hf transceiver.
 * @complete_cb_arg: काष्ठाure to store various context inक्रमmation
 *	that is passed from nfc requesting thपढ़ो to the thपढ़ोed ISR.
 * @st95hf_supply: regulator "consumer" क्रम NFC device.
 * @sendrcv_trflag: last byte of frame send by sendrecv command
 *	of st95hf. This byte contains transmission flag info.
 * @exchange_lock: semaphore used क्रम संकेतing the st95hf_हटाओ
 *	function that the last outstanding async nfc request is finished.
 * @rm_lock: mutex क्रम ensuring safe access of nfc digital object
 *	from thपढ़ोed ISR. Usage of this mutex aव्योमs any race between
 *	deletion of the object from st95hf_हटाओ() and its access from
 *	the thपढ़ोed ISR.
 * @nfcdev_मुक्त: flag to have the state of nfc device object.
 *	[alive | died]
 * @current_protocol: current nfc protocol.
 * @current_rf_tech: current rf technology.
 * @fwi: frame रुकोing index, received in reply of RATS according to
 *	digital protocol.
 */
काष्ठा st95hf_context अणु
	काष्ठा st95hf_spi_context spicontext;
	काष्ठा nfc_digital_dev *ddev;
	काष्ठा nfc_dev *nfcdev;
	अचिन्हित पूर्णांक enable_gpio;
	काष्ठा st95_digital_cmd_complete_arg complete_cb_arg;
	काष्ठा regulator *st95hf_supply;
	अचिन्हित अक्षर sendrcv_trflag;
	काष्ठा semaphore exchange_lock;
	काष्ठा mutex rm_lock;
	bool nfcdev_मुक्त;
	u8 current_protocol;
	u8 current_rf_tech;
	पूर्णांक fwi;
पूर्ण;

/*
 * st95hf_send_recv_cmd() is क्रम sending commands to ST95HF
 * that are described in the cmd_array[]. It can optionally
 * receive the response अगर the cmd request is of type
 * SYNC. For that to happen caller must pass true to recv_res.
 * For ASYNC request, recv_res is ignored and the
 * function will never try to receive the response on behalf
 * of the caller.
 */
अटल पूर्णांक st95hf_send_recv_cmd(काष्ठा st95hf_context *st95context,
				क्रमागत st95hf_cmd_list cmd,
				पूर्णांक no_modअगर,
				काष्ठा param_list *list_array,
				bool recv_res)
अणु
	अचिन्हित अक्षर spi_cmd_buffer[MAX_CMD_LEN];
	पूर्णांक i, ret;
	काष्ठा device *dev = &st95context->spicontext.spidev->dev;

	अगर (cmd_array[cmd].cmd_len > MAX_CMD_LEN)
		वापस -EINVAL;
	अगर (cmd_array[cmd].no_cmd_params < no_modअगर)
		वापस -EINVAL;
	अगर (no_modअगर && !list_array)
		वापस -EINVAL;

	spi_cmd_buffer[0] = ST95HF_COMMAND_SEND;
	spi_cmd_buffer[1] = cmd_array[cmd].cmd_id;
	spi_cmd_buffer[2] = cmd_array[cmd].no_cmd_params;

	स_नकल(&spi_cmd_buffer[3], cmd_array[cmd].cmd_params,
	       spi_cmd_buffer[2]);

	क्रम (i = 0; i < no_modअगर; i++) अणु
		अगर (list_array[i].param_offset >= cmd_array[cmd].no_cmd_params)
			वापस -EINVAL;
		spi_cmd_buffer[3 + list_array[i].param_offset] =
						list_array[i].new_param_val;
	पूर्ण

	ret = st95hf_spi_send(&st95context->spicontext,
			      spi_cmd_buffer,
			      cmd_array[cmd].cmd_len,
			      cmd_array[cmd].req);
	अगर (ret) अणु
		dev_err(dev, "st95hf_spi_send failed with error %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (cmd_array[cmd].req == SYNC && recv_res) अणु
		अचिन्हित अक्षर st95hf_response_arr[2];

		ret = st95hf_spi_recv_response(&st95context->spicontext,
					       st95hf_response_arr);
		अगर (ret < 0) अणु
			dev_err(dev, "spi error from st95hf_spi_recv_response(), err = 0x%x\n",
				ret);
			वापस ret;
		पूर्ण

		अगर (st95hf_response_arr[0]) अणु
			dev_err(dev, "st95hf error from st95hf_spi_recv_response(), err = 0x%x\n",
				st95hf_response_arr[0]);
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक st95hf_echo_command(काष्ठा st95hf_context *st95context)
अणु
	पूर्णांक result = 0;
	अचिन्हित अक्षर echo_response;

	result = st95hf_send_recv_cmd(st95context, CMD_ECHO, 0, शून्य, false);
	अगर (result)
		वापस result;

	/* If control reached here, response can be taken */
	result = st95hf_spi_recv_echo_res(&st95context->spicontext,
					  &echo_response);
	अगर (result) अणु
		dev_err(&st95context->spicontext.spidev->dev,
			"err: echo response receive error = 0x%x\n", result);
		वापस result;
	पूर्ण

	अगर (echo_response == ECHORESPONSE)
		वापस 0;

	dev_err(&st95context->spicontext.spidev->dev, "err: echo res is 0x%x\n",
		echo_response);

	वापस -EIO;
पूर्ण

अटल पूर्णांक secondary_configuration_type4a(काष्ठा st95hf_context *stcontext)
अणु
	पूर्णांक result = 0;
	काष्ठा device *dev = &stcontext->nfcdev->dev;

	/* 14443A config setting after select protocol */
	result = st95hf_send_recv_cmd(stcontext,
				      CMD_ISO14443A_CONFIG,
				      0,
				      शून्य,
				      true);
	अगर (result) अणु
		dev_err(dev, "type a config cmd, err = 0x%x\n", result);
		वापस result;
	पूर्ण

	/* 14443A demo gain setting */
	result = st95hf_send_recv_cmd(stcontext,
				      CMD_ISO14443A_DEMOGAIN,
				      0,
				      शून्य,
				      true);
	अगर (result)
		dev_err(dev, "type a demogain cmd, err = 0x%x\n", result);

	वापस result;
पूर्ण

अटल पूर्णांक secondary_configuration_type4b(काष्ठा st95hf_context *stcontext)
अणु
	पूर्णांक result = 0;
	काष्ठा device *dev = &stcontext->nfcdev->dev;

	result = st95hf_send_recv_cmd(stcontext,
				      CMD_ISO14443B_DEMOGAIN,
				      0,
				      शून्य,
				      true);
	अगर (result)
		dev_err(dev, "type b demogain cmd, err = 0x%x\n", result);

	वापस result;
पूर्ण

अटल पूर्णांक st95hf_select_protocol(काष्ठा st95hf_context *stcontext, पूर्णांक type)
अणु
	पूर्णांक result = 0;
	काष्ठा device *dev;

	dev = &stcontext->nfcdev->dev;

	चयन (type) अणु
	हाल NFC_DIGITAL_RF_TECH_106A:
		stcontext->current_rf_tech = NFC_DIGITAL_RF_TECH_106A;
		result = st95hf_send_recv_cmd(stcontext,
					      CMD_ISO14443A_PROTOCOL_SELECT,
					      0,
					      शून्य,
					      true);
		अगर (result) अणु
			dev_err(dev, "protocol sel, err = 0x%x\n",
				result);
			वापस result;
		पूर्ण

		/* secondary config. क्रम 14443Type 4A after protocol select */
		result = secondary_configuration_type4a(stcontext);
		अगर (result) अणु
			dev_err(dev, "type a secondary config, err = 0x%x\n",
				result);
			वापस result;
		पूर्ण
		अवरोध;
	हाल NFC_DIGITAL_RF_TECH_106B:
		stcontext->current_rf_tech = NFC_DIGITAL_RF_TECH_106B;
		result = st95hf_send_recv_cmd(stcontext,
					      CMD_ISO14443B_PROTOCOL_SELECT,
					      0,
					      शून्य,
					      true);
		अगर (result) अणु
			dev_err(dev, "protocol sel send, err = 0x%x\n",
				result);
			वापस result;
		पूर्ण

		/*
		 * delay of 5-6 ms is required after select protocol
		 * command in हाल of ISO14443 Type B
		 */
		usleep_range(50000, 60000);

		/* secondary config. क्रम 14443Type 4B after protocol select */
		result = secondary_configuration_type4b(stcontext);
		अगर (result) अणु
			dev_err(dev, "type b secondary config, err = 0x%x\n",
				result);
			वापस result;
		पूर्ण
		अवरोध;
	हाल NFC_DIGITAL_RF_TECH_ISO15693:
		stcontext->current_rf_tech = NFC_DIGITAL_RF_TECH_ISO15693;
		result = st95hf_send_recv_cmd(stcontext,
					      CMD_ISO15693_PROTOCOL_SELECT,
					      0,
					      शून्य,
					      true);
		अगर (result) अणु
			dev_err(dev, "protocol sel send, err = 0x%x\n",
				result);
			वापस result;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम st95hf_send_st95enable_negativepulse(काष्ठा st95hf_context *st95con)
अणु
	/* First make irq_in pin high */
	gpio_set_value(st95con->enable_gpio, HIGH);

	/* रुको क्रम 1 milisecond */
	usleep_range(1000, 2000);

	/* Make irq_in pin low */
	gpio_set_value(st95con->enable_gpio, LOW);

	/* रुको क्रम minimum पूर्णांकerrupt pulse to make st95 active */
	usleep_range(1000, 2000);

	/* At end make it high */
	gpio_set_value(st95con->enable_gpio, HIGH);
पूर्ण

/*
 * Send a reset sequence over SPI bus (Reset command + रुको 3ms +
 * negative pulse on st95hf enable gpio
 */
अटल पूर्णांक st95hf_send_spi_reset_sequence(काष्ठा st95hf_context *st95context)
अणु
	पूर्णांक result = 0;
	अचिन्हित अक्षर reset_cmd = ST95HF_COMMAND_RESET;

	result = st95hf_spi_send(&st95context->spicontext,
				 &reset_cmd,
				 ST95HF_RESET_CMD_LEN,
				 ASYNC);
	अगर (result) अणु
		dev_err(&st95context->spicontext.spidev->dev,
			"spi reset sequence cmd error = %d", result);
		वापस result;
	पूर्ण

	/* रुको क्रम 3 milisecond to complete the controller reset process */
	usleep_range(3000, 4000);

	/* send negative pulse to make st95hf active */
	st95hf_send_st95enable_negativepulse(st95context);

	/* रुको क्रम 10 milisecond : HFO setup समय */
	usleep_range(10000, 20000);

	वापस result;
पूर्ण

अटल पूर्णांक st95hf_por_sequence(काष्ठा st95hf_context *st95context)
अणु
	पूर्णांक nth_attempt = 1;
	पूर्णांक result;

	st95hf_send_st95enable_negativepulse(st95context);

	usleep_range(5000, 6000);
	करो अणु
		/* send an ECHO command and checks ST95HF response */
		result = st95hf_echo_command(st95context);

		dev_dbg(&st95context->spicontext.spidev->dev,
			"response from echo function = 0x%x, attempt = %d\n",
			result, nth_attempt);

		अगर (!result)
			वापस 0;

		/* send an pulse on IRQ in हाल of the chip is on sleep state */
		अगर (nth_attempt == 2)
			st95hf_send_st95enable_negativepulse(st95context);
		अन्यथा
			st95hf_send_spi_reset_sequence(st95context);

		/* delay of 50 milisecond */
		usleep_range(50000, 51000);
	पूर्ण जबतक (nth_attempt++ < 3);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक iso14443_config_fdt(काष्ठा st95hf_context *st95context, पूर्णांक wtxm)
अणु
	पूर्णांक result = 0;
	काष्ठा device *dev = &st95context->spicontext.spidev->dev;
	काष्ठा nfc_digital_dev *nfcddev = st95context->ddev;
	अचिन्हित अक्षर pp_typeb;
	काष्ठा param_list new_params[2];

	pp_typeb = cmd_array[CMD_ISO14443B_PROTOCOL_SELECT].cmd_params[2];

	अगर (nfcddev->curr_protocol == NFC_PROTO_ISO14443 &&
	    st95context->fwi < 4)
		st95context->fwi = 4;

	new_params[0].param_offset = 2;
	अगर (nfcddev->curr_protocol == NFC_PROTO_ISO14443)
		new_params[0].new_param_val = st95context->fwi;
	अन्यथा अगर (nfcddev->curr_protocol == NFC_PROTO_ISO14443_B)
		new_params[0].new_param_val = pp_typeb;

	new_params[1].param_offset = 3;
	new_params[1].new_param_val = wtxm;

	चयन (nfcddev->curr_protocol) अणु
	हाल NFC_PROTO_ISO14443:
		result = st95hf_send_recv_cmd(st95context,
					      CMD_ISO14443A_PROTOCOL_SELECT,
					      2,
					      new_params,
					      true);
		अगर (result) अणु
			dev_err(dev, "WTX type a sel proto, err = 0x%x\n",
				result);
			वापस result;
		पूर्ण

		/* secondary config. क्रम 14443Type 4A after protocol select */
		result = secondary_configuration_type4a(st95context);
		अगर (result) अणु
			dev_err(dev, "WTX type a second. config, err = 0x%x\n",
				result);
			वापस result;
		पूर्ण
		अवरोध;
	हाल NFC_PROTO_ISO14443_B:
		result = st95hf_send_recv_cmd(st95context,
					      CMD_ISO14443B_PROTOCOL_SELECT,
					      2,
					      new_params,
					      true);
		अगर (result) अणु
			dev_err(dev, "WTX type b sel proto, err = 0x%x\n",
				result);
			वापस result;
		पूर्ण

		/* secondary config. क्रम 14443Type 4B after protocol select */
		result = secondary_configuration_type4b(st95context);
		अगर (result) अणु
			dev_err(dev, "WTX type b second. config, err = 0x%x\n",
				result);
			वापस result;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक st95hf_handle_wtx(काष्ठा st95hf_context *stcontext,
			     bool new_wtx,
			     पूर्णांक wtx_val)
अणु
	पूर्णांक result = 0;
	अचिन्हित अक्षर val_mm = 0;
	काष्ठा param_list new_params[1];
	काष्ठा nfc_digital_dev *nfcddev = stcontext->ddev;
	काष्ठा device *dev = &stcontext->nfcdev->dev;

	अगर (new_wtx) अणु
		result = iso14443_config_fdt(stcontext, wtx_val & 0x3f);
		अगर (result) अणु
			dev_err(dev, "Config. setting error on WTX req, err = 0x%x\n",
				result);
			वापस result;
		पूर्ण

		/* Send response of wtx with ASYNC as no response expected */
		new_params[0].param_offset = 1;
		new_params[0].new_param_val = wtx_val;

		result = st95hf_send_recv_cmd(stcontext,
					      CMD_WTX_RESPONSE,
					      1,
					      new_params,
					      false);
		अगर (result)
			dev_err(dev, "WTX response send, err = 0x%x\n", result);
		वापस result;
	पूर्ण

	/* अगर no new wtx, cofigure with शेष values */
	अगर (nfcddev->curr_protocol == NFC_PROTO_ISO14443)
		val_mm = cmd_array[CMD_ISO14443A_PROTOCOL_SELECT].cmd_params[3];
	अन्यथा अगर (nfcddev->curr_protocol == NFC_PROTO_ISO14443_B)
		val_mm = cmd_array[CMD_ISO14443B_PROTOCOL_SELECT].cmd_params[3];

	result = iso14443_config_fdt(stcontext, val_mm);
	अगर (result)
		dev_err(dev, "Default config. setting error after WTX processing, err = 0x%x\n",
			result);

	वापस result;
पूर्ण

अटल पूर्णांक st95hf_error_handling(काष्ठा st95hf_context *stcontext,
				 काष्ठा sk_buff *skb_resp,
				 पूर्णांक res_len)
अणु
	पूर्णांक result = 0;
	अचिन्हित अक्षर error_byte;
	काष्ठा device *dev = &stcontext->nfcdev->dev;

	/* First check ST95HF specअगरic error */
	अगर (skb_resp->data[0] & ST95HF_ERR_MASK) अणु
		अगर (skb_resp->data[0] == ST95HF_TIMEOUT_ERROR)
			result = -ETIMEDOUT;
		अन्यथा
			result = -EIO;
		वापस result;
	पूर्ण

	/* Check क्रम CRC err only अगर CRC is present in the tag response */
	चयन (stcontext->current_rf_tech) अणु
	हाल NFC_DIGITAL_RF_TECH_106A:
		अगर (stcontext->sendrcv_trflag == TRFLAG_NFCA_STD_FRAME_CRC) अणु
			error_byte = skb_resp->data[res_len - 3];
			अगर (error_byte & ST95HF_NFCA_CRC_ERR_MASK) अणु
				/* CRC error occurred */
				dev_err(dev, "CRC error, byte received = 0x%x\n",
					error_byte);
				result = -EIO;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल NFC_DIGITAL_RF_TECH_106B:
	हाल NFC_DIGITAL_RF_TECH_ISO15693:
		error_byte = skb_resp->data[res_len - 1];
		अगर (error_byte & ST95HF_NFCB_CRC_ERR_MASK) अणु
			/* CRC error occurred */
			dev_err(dev, "CRC error, byte received = 0x%x\n",
				error_byte);
			result = -EIO;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक st95hf_response_handler(काष्ठा st95hf_context *stcontext,
				   काष्ठा sk_buff *skb_resp,
				   पूर्णांक res_len)
अणु
	पूर्णांक result = 0;
	पूर्णांक skb_len;
	अचिन्हित अक्षर val_mm;
	काष्ठा nfc_digital_dev *nfcddev = stcontext->ddev;
	काष्ठा device *dev = &stcontext->nfcdev->dev;
	काष्ठा st95_digital_cmd_complete_arg *cb_arg;

	cb_arg = &stcontext->complete_cb_arg;

	/* Process the response */
	skb_put(skb_resp, res_len);

	/* Remove st95 header */
	skb_pull(skb_resp, 2);

	skb_len = skb_resp->len;

	/* check अगर it is हाल of RATS request reply & FWI is present */
	अगर (nfcddev->curr_protocol == NFC_PROTO_ISO14443 && cb_arg->rats &&
	    (skb_resp->data[1] & RATS_TB1_PRESENT_MASK)) अणु
		अगर (skb_resp->data[1] & RATS_TA1_PRESENT_MASK)
			stcontext->fwi =
				(skb_resp->data[3] & TB1_FWI_MASK) >> 4;
		अन्यथा
			stcontext->fwi =
				(skb_resp->data[2] & TB1_FWI_MASK) >> 4;

		val_mm = cmd_array[CMD_ISO14443A_PROTOCOL_SELECT].cmd_params[3];

		result = iso14443_config_fdt(stcontext, val_mm);
		अगर (result) अणु
			dev_err(dev, "error in config_fdt to handle fwi of ATS, error=%d\n",
				result);
			वापस result;
		पूर्ण
	पूर्ण
	cb_arg->rats = false;

	/* Remove CRC bytes only अगर received frames data has an eod (CRC) */
	चयन (stcontext->current_rf_tech) अणु
	हाल NFC_DIGITAL_RF_TECH_106A:
		अगर (stcontext->sendrcv_trflag == TRFLAG_NFCA_STD_FRAME_CRC)
			skb_trim(skb_resp, (skb_len - 5));
		अन्यथा
			skb_trim(skb_resp, (skb_len - 3));
		अवरोध;
	हाल NFC_DIGITAL_RF_TECH_106B:
	हाल NFC_DIGITAL_RF_TECH_ISO15693:
		skb_trim(skb_resp, (skb_len - 3));
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

अटल irqवापस_t st95hf_irq_handler(पूर्णांक irq, व्योम  *st95hfcontext)
अणु
	काष्ठा st95hf_context *stcontext  =
		(काष्ठा st95hf_context *)st95hfcontext;

	अगर (stcontext->spicontext.req_issync) अणु
		complete(&stcontext->spicontext.करोne);
		stcontext->spicontext.req_issync = false;
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t st95hf_irq_thपढ़ो_handler(पूर्णांक irq, व्योम  *st95hfcontext)
अणु
	पूर्णांक result = 0;
	पूर्णांक res_len;
	अटल bool wtx;
	काष्ठा device *spidevice;
	काष्ठा sk_buff *skb_resp;
	काष्ठा st95hf_context *stcontext  =
		(काष्ठा st95hf_context *)st95hfcontext;
	काष्ठा st95_digital_cmd_complete_arg *cb_arg;

	spidevice = &stcontext->spicontext.spidev->dev;

	/*
	 * check semaphore, अगर not करोwn() alपढ़ोy, then we करोn't
	 * know in which context the ISR is called and surely it
	 * will be a bug. Note that करोwn() of the semaphore is करोne
	 * in the corresponding st95hf_in_send_cmd() and then
	 * only this ISR should be called. ISR will up() the
	 * semaphore beक्रमe leaving. Hence when the ISR is called
	 * the correct behaviour is करोwn_trylock() should always
	 * वापस 1 (indicating semaphore cant be taken and hence no
	 * change in semaphore count).
	 * If not, then we up() the semaphore and crash on
	 * a BUG() !
	 */
	अगर (!करोwn_trylock(&stcontext->exchange_lock)) अणु
		up(&stcontext->exchange_lock);
		WARN(1, "unknown context in ST95HF ISR");
		वापस IRQ_NONE;
	पूर्ण

	cb_arg = &stcontext->complete_cb_arg;
	skb_resp = cb_arg->skb_resp;

	mutex_lock(&stcontext->rm_lock);
	res_len = st95hf_spi_recv_response(&stcontext->spicontext,
					   skb_resp->data);
	अगर (res_len < 0) अणु
		dev_err(spidevice, "TISR spi response err = 0x%x\n", res_len);
		result = res_len;
		जाओ end;
	पूर्ण

	/* अगर stcontext->nfcdev_मुक्त is true, it means हटाओ alपढ़ोy ran */
	अगर (stcontext->nfcdev_मुक्त) अणु
		result = -ENODEV;
		जाओ end;
	पूर्ण

	अगर (skb_resp->data[2] == WTX_REQ_FROM_TAG) अणु
		/* Request क्रम new FWT from tag */
		result = st95hf_handle_wtx(stcontext, true, skb_resp->data[3]);
		अगर (result)
			जाओ end;

		wtx = true;
		mutex_unlock(&stcontext->rm_lock);
		वापस IRQ_HANDLED;
	पूर्ण

	result = st95hf_error_handling(stcontext, skb_resp, res_len);
	अगर (result)
		जाओ end;

	result = st95hf_response_handler(stcontext, skb_resp, res_len);
	अगर (result)
		जाओ end;

	/*
	 * If select protocol is करोne on wtx req. करो select protocol
	 * again with शेष values
	 */
	अगर (wtx) अणु
		wtx = false;
		result = st95hf_handle_wtx(stcontext, false, 0);
		अगर (result)
			जाओ end;
	पूर्ण

	/* call digital layer callback */
	cb_arg->complete_cb(stcontext->ddev, cb_arg->cb_usrarg, skb_resp);

	/* up the semaphore beक्रमe वापसing */
	up(&stcontext->exchange_lock);
	mutex_unlock(&stcontext->rm_lock);

	वापस IRQ_HANDLED;

end:
	kमुक्त_skb(skb_resp);
	wtx = false;
	cb_arg->rats = false;
	skb_resp = ERR_PTR(result);
	/* call of callback with error */
	cb_arg->complete_cb(stcontext->ddev, cb_arg->cb_usrarg, skb_resp);
	/* up the semaphore beक्रमe वापसing */
	up(&stcontext->exchange_lock);
	mutex_unlock(&stcontext->rm_lock);
	वापस IRQ_HANDLED;
पूर्ण

/* NFC ops functions definition */
अटल पूर्णांक st95hf_in_configure_hw(काष्ठा nfc_digital_dev *ddev,
				  पूर्णांक type,
				  पूर्णांक param)
अणु
	काष्ठा st95hf_context *stcontext = nfc_digital_get_drvdata(ddev);

	अगर (type == NFC_DIGITAL_CONFIG_RF_TECH)
		वापस st95hf_select_protocol(stcontext, param);

	अगर (type == NFC_DIGITAL_CONFIG_FRAMING) अणु
		चयन (param) अणु
		हाल NFC_DIGITAL_FRAMING_NFCA_SHORT:
			stcontext->sendrcv_trflag = TRFLAG_NFCA_SHORT_FRAME;
			अवरोध;
		हाल NFC_DIGITAL_FRAMING_NFCA_STANDARD:
			stcontext->sendrcv_trflag = TRFLAG_NFCA_STD_FRAME;
			अवरोध;
		हाल NFC_DIGITAL_FRAMING_NFCA_T4T:
		हाल NFC_DIGITAL_FRAMING_NFCA_NFC_DEP:
		हाल NFC_DIGITAL_FRAMING_NFCA_STANDARD_WITH_CRC_A:
			stcontext->sendrcv_trflag = TRFLAG_NFCA_STD_FRAME_CRC;
			अवरोध;
		हाल NFC_DIGITAL_FRAMING_NFCB:
		हाल NFC_DIGITAL_FRAMING_ISO15693_INVENTORY:
		हाल NFC_DIGITAL_FRAMING_ISO15693_T5T:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rf_off(काष्ठा st95hf_context *stcontext)
अणु
	पूर्णांक rc;
	काष्ठा device *dev;

	dev = &stcontext->nfcdev->dev;

	rc = st95hf_send_recv_cmd(stcontext, CMD_FIELD_OFF, 0, शून्य, true);
	अगर (rc)
		dev_err(dev, "protocol sel send field off, err = 0x%x\n", rc);

	वापस rc;
पूर्ण

अटल पूर्णांक st95hf_in_send_cmd(काष्ठा nfc_digital_dev *ddev,
			      काष्ठा sk_buff *skb,
			      u16 समयout,
			      nfc_digital_cmd_complete_t cb,
			      व्योम *arg)
अणु
	काष्ठा st95hf_context *stcontext = nfc_digital_get_drvdata(ddev);
	पूर्णांक rc;
	काष्ठा sk_buff *skb_resp;
	पूर्णांक len_data_to_tag = 0;

	skb_resp = nfc_alloc_recv_skb(MAX_RESPONSE_BUFFER_SIZE, GFP_KERNEL);
	अगर (!skb_resp) अणु
		rc = -ENOMEM;
		जाओ error;
	पूर्ण

	चयन (stcontext->current_rf_tech) अणु
	हाल NFC_DIGITAL_RF_TECH_106A:
		len_data_to_tag = skb->len + 1;
		skb_put_u8(skb, stcontext->sendrcv_trflag);
		अवरोध;
	हाल NFC_DIGITAL_RF_TECH_106B:
	हाल NFC_DIGITAL_RF_TECH_ISO15693:
		len_data_to_tag = skb->len;
		अवरोध;
	शेष:
		rc = -EINVAL;
		जाओ मुक्त_skb_resp;
	पूर्ण

	skb_push(skb, 3);
	skb->data[0] = ST95HF_COMMAND_SEND;
	skb->data[1] = SEND_RECEIVE_CMD;
	skb->data[2] = len_data_to_tag;

	stcontext->complete_cb_arg.skb_resp = skb_resp;
	stcontext->complete_cb_arg.cb_usrarg = arg;
	stcontext->complete_cb_arg.complete_cb = cb;

	अगर ((skb->data[3] == ISO14443A_RATS_REQ) &&
	    ddev->curr_protocol == NFC_PROTO_ISO14443)
		stcontext->complete_cb_arg.rats = true;

	/*
	 * करोwn the semaphore to indicate to हटाओ func that an
	 * ISR is pending, note that it will not block here in any हाल.
	 * If found blocked, it is a BUG!
	 */
	rc = करोwn_समाप्तable(&stcontext->exchange_lock);
	अगर (rc) अणु
		WARN(1, "Semaphore is not found up in st95hf_in_send_cmd\n");
		जाओ मुक्त_skb_resp;
	पूर्ण

	rc = st95hf_spi_send(&stcontext->spicontext, skb->data,
			     skb->len,
			     ASYNC);
	अगर (rc) अणु
		dev_err(&stcontext->nfcdev->dev,
			"Error %d trying to perform data_exchange", rc);
		/* up the semaphore since ISR will never come in this हाल */
		up(&stcontext->exchange_lock);
		जाओ मुक्त_skb_resp;
	पूर्ण

	kमुक्त_skb(skb);

	वापस rc;

मुक्त_skb_resp:
	kमुक्त_skb(skb_resp);
error:
	वापस rc;
पूर्ण

/* p2p will be supported in a later release ! */
अटल पूर्णांक st95hf_tg_configure_hw(काष्ठा nfc_digital_dev *ddev,
				  पूर्णांक type,
				  पूर्णांक param)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक st95hf_tg_send_cmd(काष्ठा nfc_digital_dev *ddev,
			      काष्ठा sk_buff *skb,
			      u16 समयout,
			      nfc_digital_cmd_complete_t cb,
			      व्योम *arg)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक st95hf_tg_listen(काष्ठा nfc_digital_dev *ddev,
			    u16 समयout,
			    nfc_digital_cmd_complete_t cb,
			    व्योम *arg)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक st95hf_tg_get_rf_tech(काष्ठा nfc_digital_dev *ddev, u8 *rf_tech)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक st95hf_चयन_rf(काष्ठा nfc_digital_dev *ddev, bool on)
अणु
	u8 rf_tech;
	काष्ठा st95hf_context *stcontext = nfc_digital_get_drvdata(ddev);

	rf_tech = ddev->curr_rf_tech;

	अगर (on)
		/* चयन on RF field */
		वापस st95hf_select_protocol(stcontext, rf_tech);

	/* चयन OFF RF field */
	वापस rf_off(stcontext);
पूर्ण

/* TODO st95hf_पात_cmd */
अटल व्योम st95hf_पात_cmd(काष्ठा nfc_digital_dev *ddev)
अणु
पूर्ण

अटल काष्ठा nfc_digital_ops st95hf_nfc_digital_ops = अणु
	.in_configure_hw = st95hf_in_configure_hw,
	.in_send_cmd = st95hf_in_send_cmd,

	.tg_listen = st95hf_tg_listen,
	.tg_configure_hw = st95hf_tg_configure_hw,
	.tg_send_cmd = st95hf_tg_send_cmd,
	.tg_get_rf_tech = st95hf_tg_get_rf_tech,

	.चयन_rf = st95hf_चयन_rf,
	.पात_cmd = st95hf_पात_cmd,
पूर्ण;

अटल स्थिर काष्ठा spi_device_id st95hf_id[] = अणु
	अणु "st95hf", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, st95hf_id);

अटल स्थिर काष्ठा of_device_id st95hf_spi_of_match[] = अणु
        अणु .compatible = "st,st95hf" पूर्ण,
        अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, st95hf_spi_of_match);

अटल पूर्णांक st95hf_probe(काष्ठा spi_device *nfc_spi_dev)
अणु
	पूर्णांक ret;

	काष्ठा st95hf_context *st95context;
	काष्ठा st95hf_spi_context *spicontext;

	nfc_info(&nfc_spi_dev->dev, "ST95HF driver probe called.\n");

	st95context = devm_kzalloc(&nfc_spi_dev->dev,
				   माप(काष्ठा st95hf_context),
				   GFP_KERNEL);
	अगर (!st95context)
		वापस -ENOMEM;

	spicontext = &st95context->spicontext;

	spicontext->spidev = nfc_spi_dev;

	st95context->fwi =
		cmd_array[CMD_ISO14443A_PROTOCOL_SELECT].cmd_params[2];

	अगर (device_property_present(&nfc_spi_dev->dev, "st95hfvin")) अणु
		st95context->st95hf_supply =
			devm_regulator_get(&nfc_spi_dev->dev,
					   "st95hfvin");
		अगर (IS_ERR(st95context->st95hf_supply)) अणु
			dev_err(&nfc_spi_dev->dev, "failed to acquire regulator\n");
			वापस PTR_ERR(st95context->st95hf_supply);
		पूर्ण

		ret = regulator_enable(st95context->st95hf_supply);
		अगर (ret) अणु
			dev_err(&nfc_spi_dev->dev, "failed to enable regulator\n");
			वापस ret;
		पूर्ण
	पूर्ण

	init_completion(&spicontext->करोne);
	mutex_init(&spicontext->spi_lock);

	/*
	 * Store spicontext in spi device object क्रम using it in
	 * हटाओ function
	 */
	dev_set_drvdata(&nfc_spi_dev->dev, spicontext);

	st95context->enable_gpio =
		of_get_named_gpio(nfc_spi_dev->dev.of_node,
				  "enable-gpio",
				  0);
	अगर (!gpio_is_valid(st95context->enable_gpio)) अणु
		dev_err(&nfc_spi_dev->dev, "No valid enable gpio\n");
		ret = st95context->enable_gpio;
		जाओ err_disable_regulator;
	पूर्ण

	ret = devm_gpio_request_one(&nfc_spi_dev->dev, st95context->enable_gpio,
				    GPIOF_सूची_OUT | GPIOF_INIT_HIGH,
				    "enable_gpio");
	अगर (ret)
		जाओ err_disable_regulator;

	अगर (nfc_spi_dev->irq > 0) अणु
		अगर (devm_request_thपढ़ोed_irq(&nfc_spi_dev->dev,
					      nfc_spi_dev->irq,
					      st95hf_irq_handler,
					      st95hf_irq_thपढ़ो_handler,
					      IRQF_TRIGGER_FALLING,
					      "st95hf",
					      (व्योम *)st95context) < 0) अणु
			dev_err(&nfc_spi_dev->dev, "err: irq request for st95hf is failed\n");
			ret =  -EINVAL;
			जाओ err_disable_regulator;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&nfc_spi_dev->dev, "not a valid IRQ associated with ST95HF\n");
		ret = -EINVAL;
		जाओ err_disable_regulator;
	पूर्ण

	/*
	 * First reset SPI to handle warm reset of the प्रणाली.
	 * It will put the ST95HF device in Power ON state
	 * which make the state of device identical to state
	 * at the समय of cold reset of the प्रणाली.
	 */
	ret = st95hf_send_spi_reset_sequence(st95context);
	अगर (ret) अणु
		dev_err(&nfc_spi_dev->dev, "err: spi_reset_sequence failed\n");
		जाओ err_disable_regulator;
	पूर्ण

	/* call PowerOnReset sequence of ST95hf to activate it */
	ret = st95hf_por_sequence(st95context);
	अगर (ret) अणु
		dev_err(&nfc_spi_dev->dev, "err: por seq failed for st95hf\n");
		जाओ err_disable_regulator;
	पूर्ण

	/* create NFC dev object and रेजिस्टर with NFC Subप्रणाली */
	st95context->ddev = nfc_digital_allocate_device(&st95hf_nfc_digital_ops,
							ST95HF_SUPPORTED_PROT,
							ST95HF_CAPABILITIES,
							ST95HF_HEADROOM_LEN,
							ST95HF_TAILROOM_LEN);
	अगर (!st95context->ddev) अणु
		ret = -ENOMEM;
		जाओ err_disable_regulator;
	पूर्ण

	st95context->nfcdev = st95context->ddev->nfc_dev;
	nfc_digital_set_parent_dev(st95context->ddev, &nfc_spi_dev->dev);

	ret =  nfc_digital_रेजिस्टर_device(st95context->ddev);
	अगर (ret) अणु
		dev_err(&st95context->nfcdev->dev, "st95hf registration failed\n");
		जाओ err_मुक्त_digital_device;
	पूर्ण

	/* store st95context in nfc device object */
	nfc_digital_set_drvdata(st95context->ddev, st95context);

	sema_init(&st95context->exchange_lock, 1);
	mutex_init(&st95context->rm_lock);

	वापस ret;

err_मुक्त_digital_device:
	nfc_digital_मुक्त_device(st95context->ddev);
err_disable_regulator:
	अगर (st95context->st95hf_supply)
		regulator_disable(st95context->st95hf_supply);

	वापस ret;
पूर्ण

अटल पूर्णांक st95hf_हटाओ(काष्ठा spi_device *nfc_spi_dev)
अणु
	पूर्णांक result = 0;
	अचिन्हित अक्षर reset_cmd = ST95HF_COMMAND_RESET;
	काष्ठा st95hf_spi_context *spictx = dev_get_drvdata(&nfc_spi_dev->dev);

	काष्ठा st95hf_context *stcontext = container_of(spictx,
							काष्ठा st95hf_context,
							spicontext);

	mutex_lock(&stcontext->rm_lock);

	nfc_digital_unरेजिस्टर_device(stcontext->ddev);
	nfc_digital_मुक्त_device(stcontext->ddev);
	stcontext->nfcdev_मुक्त = true;

	mutex_unlock(&stcontext->rm_lock);

	/* अगर last in_send_cmd's ISR is pending, रुको क्रम it to finish */
	result = करोwn_समाप्तable(&stcontext->exchange_lock);
	अगर (result == -EINTR)
		dev_err(&spictx->spidev->dev, "sleep for semaphore interrupted by signal\n");

	/* next reset the ST95HF controller */
	result = st95hf_spi_send(&stcontext->spicontext,
				 &reset_cmd,
				 ST95HF_RESET_CMD_LEN,
				 ASYNC);
	अगर (result) अणु
		dev_err(&spictx->spidev->dev,
			"ST95HF reset failed in remove() err = %d\n", result);
		वापस result;
	पूर्ण

	/* रुको क्रम 3 ms to complete the controller reset process */
	usleep_range(3000, 4000);

	/* disable regulator */
	अगर (stcontext->st95hf_supply)
		regulator_disable(stcontext->st95hf_supply);

	वापस result;
पूर्ण

/* Register as SPI protocol driver */
अटल काष्ठा spi_driver st95hf_driver = अणु
	.driver = अणु
		.name = "st95hf",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(st95hf_spi_of_match),
	पूर्ण,
	.id_table = st95hf_id,
	.probe = st95hf_probe,
	.हटाओ = st95hf_हटाओ,
पूर्ण;

module_spi_driver(st95hf_driver);

MODULE_AUTHOR("Shikha Singh <shikha.singh@st.com>");
MODULE_DESCRIPTION("ST NFC Transceiver ST95HF driver");
MODULE_LICENSE("GPL v2");
