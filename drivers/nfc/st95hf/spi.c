<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ----------------------------------------------------------------------------
 * drivers/nfc/st95hf/spi.c function definitions क्रम SPI communication
 * ----------------------------------------------------------------------------
 * Copyright (C) 2015 STMicroelectronics Pvt. Ltd. All rights reserved.
 */

#समावेश "spi.h"

/* Function to send user provided buffer to ST95HF through SPI */
पूर्णांक st95hf_spi_send(काष्ठा st95hf_spi_context *spicontext,
		    अचिन्हित अक्षर *buffertx,
		    पूर्णांक datalen,
		    क्रमागत req_type reqtype)
अणु
	काष्ठा spi_message m;
	पूर्णांक result = 0;
	काष्ठा spi_device *spidev = spicontext->spidev;
	काष्ठा spi_transfer tx_transfer = अणु
		.tx_buf = buffertx,
		.len = datalen,
	पूर्ण;

	mutex_lock(&spicontext->spi_lock);

	अगर (reqtype == SYNC) अणु
		spicontext->req_issync = true;
		reinit_completion(&spicontext->करोne);
	पूर्ण अन्यथा अणु
		spicontext->req_issync = false;
	पूर्ण

	spi_message_init(&m);
	spi_message_add_tail(&tx_transfer, &m);

	result = spi_sync(spidev, &m);
	अगर (result) अणु
		dev_err(&spidev->dev, "error: sending cmd to st95hf using SPI = %d\n",
			result);
		mutex_unlock(&spicontext->spi_lock);
		वापस result;
	पूर्ण

	/* वापस क्रम asynchronous or no-रुको हाल */
	अगर (reqtype == ASYNC) अणु
		mutex_unlock(&spicontext->spi_lock);
		वापस 0;
	पूर्ण

	result = रुको_क्रम_completion_समयout(&spicontext->करोne,
					     msecs_to_jअगरfies(1000));
	/* check क्रम समयout or success */
	अगर (!result) अणु
		dev_err(&spidev->dev, "error: response not ready timeout\n");
		result = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		result = 0;
	पूर्ण

	mutex_unlock(&spicontext->spi_lock);

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(st95hf_spi_send);

/* Function to Receive command Response */
पूर्णांक st95hf_spi_recv_response(काष्ठा st95hf_spi_context *spicontext,
			     अचिन्हित अक्षर *receivebuff)
अणु
	पूर्णांक len = 0;
	काष्ठा spi_transfer tx_takedata;
	काष्ठा spi_message m;
	काष्ठा spi_device *spidev = spicontext->spidev;
	अचिन्हित अक्षर पढ़ोdata_cmd = ST95HF_COMMAND_RECEIVE;
	काष्ठा spi_transfer t[2] = अणु
		अणु.tx_buf = &पढ़ोdata_cmd, .len = 1,पूर्ण,
		अणु.rx_buf = receivebuff, .len = 2, .cs_change = 1,पूर्ण,
	पूर्ण;

	पूर्णांक ret = 0;

	स_रखो(&tx_takedata, 0x0, माप(काष्ठा spi_transfer));

	mutex_lock(&spicontext->spi_lock);

	/* First spi transfer to know the length of valid data */
	spi_message_init(&m);
	spi_message_add_tail(&t[0], &m);
	spi_message_add_tail(&t[1], &m);

	ret = spi_sync(spidev, &m);
	अगर (ret) अणु
		dev_err(&spidev->dev, "spi_recv_resp, data length error = %d\n",
			ret);
		mutex_unlock(&spicontext->spi_lock);
		वापस ret;
	पूर्ण

	/* As 2 bytes are alपढ़ोy पढ़ो */
	len = 2;

	/* Support of दीर्घ frame */
	अगर (receivebuff[0] & 0x60)
		len += (((receivebuff[0] & 0x60) >> 5) << 8) | receivebuff[1];
	अन्यथा
		len += receivebuff[1];

	/* Now make a transfer to पढ़ो only relevant bytes */
	tx_takedata.rx_buf = &receivebuff[2];
	tx_takedata.len = len - 2;

	spi_message_init(&m);
	spi_message_add_tail(&tx_takedata, &m);

	ret = spi_sync(spidev, &m);

	mutex_unlock(&spicontext->spi_lock);
	अगर (ret) अणु
		dev_err(&spidev->dev, "spi_recv_resp, data read error = %d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(st95hf_spi_recv_response);

पूर्णांक st95hf_spi_recv_echo_res(काष्ठा st95hf_spi_context *spicontext,
			     अचिन्हित अक्षर *receivebuff)
अणु
	अचिन्हित अक्षर पढ़ोdata_cmd = ST95HF_COMMAND_RECEIVE;
	काष्ठा spi_transfer t[2] = अणु
		अणु.tx_buf = &पढ़ोdata_cmd, .len = 1,पूर्ण,
		अणु.rx_buf = receivebuff, .len = 1,पूर्ण,
	पूर्ण;
	काष्ठा spi_message m;
	काष्ठा spi_device *spidev = spicontext->spidev;
	पूर्णांक ret = 0;

	mutex_lock(&spicontext->spi_lock);

	spi_message_init(&m);
	spi_message_add_tail(&t[0], &m);
	spi_message_add_tail(&t[1], &m);
	ret = spi_sync(spidev, &m);

	mutex_unlock(&spicontext->spi_lock);

	अगर (ret)
		dev_err(&spidev->dev, "recv_echo_res, data read error = %d\n",
			ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(st95hf_spi_recv_echo_res);
