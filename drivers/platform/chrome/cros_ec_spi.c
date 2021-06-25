<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// SPI पूर्णांकerface क्रम ChromeOS Embedded Controller
//
// Copyright (C) 2012 Google, Inc

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <uapi/linux/sched/types.h>

#समावेश "cros_ec.h"

/* The header byte, which follows the preamble */
#घोषणा EC_MSG_HEADER			0xec

/*
 * Number of EC preamble bytes we पढ़ो at a समय. Since it takes
 * about 400-500us क्रम the EC to respond there is not a lot of
 * poपूर्णांक in tuning this. If the EC could respond faster then
 * we could increase this so that might expect the preamble and
 * message to occur in a single transaction. However, the maximum
 * SPI transfer size is 256 bytes, so at 5MHz we need a response
 * समय of perhaps <320us (200 bytes / 1600 bits).
 */
#घोषणा EC_MSG_PREAMBLE_COUNT		32

/*
 * Allow क्रम a दीर्घ समय क्रम the EC to respond.  We support i2c
 * tunneling and support fairly दीर्घ messages क्रम the tunnel (249
 * bytes दीर्घ at the moment).  If we're talking to a 100 kHz device
 * on the other end and need to transfer ~256 bytes, then we need:
 *  10 us/bit * ~10 bits/byte * ~256 bytes = ~25ms
 *
 * We'll रुको 8 बार that to handle घड़ी stretching and other
 * paranoia.  Note that some battery gas gauge ICs claim to have a
 * घड़ी stretch of 144ms in rare situations.  That's incentive क्रम
 * not directly passing i2c through, but it's too late क्रम that क्रम
 * existing hardware.
 *
 * It's pretty unlikely that we'll really see a 249 byte tunnel in
 * anything other than testing.  If this was more common we might
 * consider having slow commands like this require a GET_STATUS
 * रुको loop.  The 'flash write' command would be another candidate
 * क्रम this, घड़ीing in at 2-3ms.
 */
#घोषणा EC_MSG_DEADLINE_MS		200

/*
  * Time between raising the SPI chip select (क्रम the end of a
  * transaction) and dropping it again (क्रम the next transaction).
  * If we go too fast, the EC will miss the transaction. We know that we
  * need at least 70 us with the 16 MHz STM32 EC, so go with 200 us to be
  * safe.
  */
#घोषणा EC_SPI_RECOVERY_TIME_NS	(200 * 1000)

/**
 * काष्ठा cros_ec_spi - inक्रमmation about a SPI-connected EC
 *
 * @spi: SPI device we are connected to
 * @last_transfer_ns: समय that we last finished a transfer.
 * @start_of_msg_delay: used to set the delay_usecs on the spi_transfer that
 *      is sent when we want to turn on CS at the start of a transaction.
 * @end_of_msg_delay: used to set the delay_usecs on the spi_transfer that
 *      is sent when we want to turn off CS at the end of a transaction.
 * @high_pri_worker: Used to schedule high priority work.
 */
काष्ठा cros_ec_spi अणु
	काष्ठा spi_device *spi;
	s64 last_transfer_ns;
	अचिन्हित पूर्णांक start_of_msg_delay;
	अचिन्हित पूर्णांक end_of_msg_delay;
	काष्ठा kthपढ़ो_worker *high_pri_worker;
पूर्ण;

प्रकार पूर्णांक (*cros_ec_xfer_fn_t) (काष्ठा cros_ec_device *ec_dev,
				  काष्ठा cros_ec_command *ec_msg);

/**
 * काष्ठा cros_ec_xfer_work_params - params क्रम our high priority workers
 *
 * @work: The work_काष्ठा needed to queue work
 * @fn: The function to use to transfer
 * @ec_dev: ChromeOS EC device
 * @ec_msg: Message to transfer
 * @ret: The वापस value of the function
 */

काष्ठा cros_ec_xfer_work_params अणु
	काष्ठा kthपढ़ो_work work;
	cros_ec_xfer_fn_t fn;
	काष्ठा cros_ec_device *ec_dev;
	काष्ठा cros_ec_command *ec_msg;
	पूर्णांक ret;
पूर्ण;

अटल व्योम debug_packet(काष्ठा device *dev, स्थिर अक्षर *name, u8 *ptr,
			 पूर्णांक len)
अणु
#अगर_घोषित DEBUG
	पूर्णांक i;

	dev_dbg(dev, "%s: ", name);
	क्रम (i = 0; i < len; i++)
		pr_cont(" %02x", ptr[i]);

	pr_cont("\n");
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक terminate_request(काष्ठा cros_ec_device *ec_dev)
अणु
	काष्ठा cros_ec_spi *ec_spi = ec_dev->priv;
	काष्ठा spi_message msg;
	काष्ठा spi_transfer trans;
	पूर्णांक ret;

	/*
	 * Turn off CS, possibly adding a delay to ensure the rising edge
	 * करोesn't come too soon after the end of the data.
	 */
	spi_message_init(&msg);
	स_रखो(&trans, 0, माप(trans));
	trans.delay.value = ec_spi->end_of_msg_delay;
	trans.delay.unit = SPI_DELAY_UNIT_USECS;
	spi_message_add_tail(&trans, &msg);

	ret = spi_sync_locked(ec_spi->spi, &msg);

	/* Reset end-of-response समयr */
	ec_spi->last_transfer_ns = kसमय_get_ns();
	अगर (ret < 0) अणु
		dev_err(ec_dev->dev,
			"cs-deassert spi transfer failed: %d\n",
			ret);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * receive_n_bytes - receive n bytes from the EC.
 *
 * Assumes buf is a poपूर्णांकer पूर्णांकo the ec_dev->din buffer
 *
 * @ec_dev: ChromeOS EC device.
 * @buf: Poपूर्णांकer to the buffer receiving the data.
 * @n: Number of bytes received.
 */
अटल पूर्णांक receive_n_bytes(काष्ठा cros_ec_device *ec_dev, u8 *buf, पूर्णांक n)
अणु
	काष्ठा cros_ec_spi *ec_spi = ec_dev->priv;
	काष्ठा spi_transfer trans;
	काष्ठा spi_message msg;
	पूर्णांक ret;

	BUG_ON(buf - ec_dev->din + n > ec_dev->din_size);

	स_रखो(&trans, 0, माप(trans));
	trans.cs_change = 1;
	trans.rx_buf = buf;
	trans.len = n;

	spi_message_init(&msg);
	spi_message_add_tail(&trans, &msg);
	ret = spi_sync_locked(ec_spi->spi, &msg);
	अगर (ret < 0)
		dev_err(ec_dev->dev, "spi transfer failed: %d\n", ret);

	वापस ret;
पूर्ण

/**
 * cros_ec_spi_receive_packet - Receive a packet from the EC.
 *
 * This function has two phases: पढ़ोing the preamble bytes (since अगर we पढ़ो
 * data from the EC beक्रमe it is पढ़ोy to send, we just get preamble) and
 * पढ़ोing the actual message.
 *
 * The received data is placed पूर्णांकo ec_dev->din.
 *
 * @ec_dev: ChromeOS EC device
 * @need_len: Number of message bytes we need to पढ़ो
 */
अटल पूर्णांक cros_ec_spi_receive_packet(काष्ठा cros_ec_device *ec_dev,
				      पूर्णांक need_len)
अणु
	काष्ठा ec_host_response *response;
	u8 *ptr, *end;
	पूर्णांक ret;
	अचिन्हित दीर्घ deadline;
	पूर्णांक toकरो;

	BUG_ON(ec_dev->din_size < EC_MSG_PREAMBLE_COUNT);

	/* Receive data until we see the header byte */
	deadline = jअगरfies + msecs_to_jअगरfies(EC_MSG_DEADLINE_MS);
	जबतक (true) अणु
		अचिन्हित दीर्घ start_jअगरfies = jअगरfies;

		ret = receive_n_bytes(ec_dev,
				      ec_dev->din,
				      EC_MSG_PREAMBLE_COUNT);
		अगर (ret < 0)
			वापस ret;

		ptr = ec_dev->din;
		क्रम (end = ptr + EC_MSG_PREAMBLE_COUNT; ptr != end; ptr++) अणु
			अगर (*ptr == EC_SPI_FRAME_START) अणु
				dev_dbg(ec_dev->dev, "msg found at %zd\n",
					ptr - ec_dev->din);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (ptr != end)
			अवरोध;

		/*
		 * Use the समय at the start of the loop as a समयout.  This
		 * gives us one last shot at getting the transfer and is useful
		 * in हाल we got context चयनed out क्रम a जबतक.
		 */
		अगर (समय_after(start_jअगरfies, deadline)) अणु
			dev_warn(ec_dev->dev, "EC failed to respond in time\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	/*
	 * ptr now poपूर्णांकs to the header byte. Copy any valid data to the
	 * start of our buffer
	 */
	toकरो = end - ++ptr;
	BUG_ON(toकरो < 0 || toकरो > ec_dev->din_size);
	toकरो = min(toकरो, need_len);
	स_हटाओ(ec_dev->din, ptr, toकरो);
	ptr = ec_dev->din + toकरो;
	dev_dbg(ec_dev->dev, "need %d, got %d bytes from preamble\n",
		need_len, toकरो);
	need_len -= toकरो;

	/* If the entire response काष्ठा wasn't पढ़ो, get the rest of it. */
	अगर (toकरो < माप(*response)) अणु
		ret = receive_n_bytes(ec_dev, ptr, माप(*response) - toकरो);
		अगर (ret < 0)
			वापस -EBADMSG;
		ptr += (माप(*response) - toकरो);
		toकरो = माप(*response);
	पूर्ण

	response = (काष्ठा ec_host_response *)ec_dev->din;

	/* Abort अगर data_len is too large. */
	अगर (response->data_len > ec_dev->din_size)
		वापस -EMSGSIZE;

	/* Receive data until we have it all */
	जबतक (need_len > 0) अणु
		/*
		 * We can't support transfers larger than the SPI FIFO size
		 * unless we have DMA. We करोn't have DMA on the ISP SPI ports
		 * क्रम Exynos. We need a way of asking SPI driver क्रम
		 * maximum-supported transfer size.
		 */
		toकरो = min(need_len, 256);
		dev_dbg(ec_dev->dev, "loop, todo=%d, need_len=%d, ptr=%zd\n",
			toकरो, need_len, ptr - ec_dev->din);

		ret = receive_n_bytes(ec_dev, ptr, toकरो);
		अगर (ret < 0)
			वापस ret;

		ptr += toकरो;
		need_len -= toकरो;
	पूर्ण

	dev_dbg(ec_dev->dev, "loop done, ptr=%zd\n", ptr - ec_dev->din);

	वापस 0;
पूर्ण

/**
 * cros_ec_spi_receive_response - Receive a response from the EC.
 *
 * This function has two phases: पढ़ोing the preamble bytes (since अगर we पढ़ो
 * data from the EC beक्रमe it is पढ़ोy to send, we just get preamble) and
 * पढ़ोing the actual message.
 *
 * The received data is placed पूर्णांकo ec_dev->din.
 *
 * @ec_dev: ChromeOS EC device
 * @need_len: Number of message bytes we need to पढ़ो
 */
अटल पूर्णांक cros_ec_spi_receive_response(काष्ठा cros_ec_device *ec_dev,
					पूर्णांक need_len)
अणु
	u8 *ptr, *end;
	पूर्णांक ret;
	अचिन्हित दीर्घ deadline;
	पूर्णांक toकरो;

	BUG_ON(ec_dev->din_size < EC_MSG_PREAMBLE_COUNT);

	/* Receive data until we see the header byte */
	deadline = jअगरfies + msecs_to_jअगरfies(EC_MSG_DEADLINE_MS);
	जबतक (true) अणु
		अचिन्हित दीर्घ start_jअगरfies = jअगरfies;

		ret = receive_n_bytes(ec_dev,
				      ec_dev->din,
				      EC_MSG_PREAMBLE_COUNT);
		अगर (ret < 0)
			वापस ret;

		ptr = ec_dev->din;
		क्रम (end = ptr + EC_MSG_PREAMBLE_COUNT; ptr != end; ptr++) अणु
			अगर (*ptr == EC_SPI_FRAME_START) अणु
				dev_dbg(ec_dev->dev, "msg found at %zd\n",
					ptr - ec_dev->din);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (ptr != end)
			अवरोध;

		/*
		 * Use the समय at the start of the loop as a समयout.  This
		 * gives us one last shot at getting the transfer and is useful
		 * in हाल we got context चयनed out क्रम a जबतक.
		 */
		अगर (समय_after(start_jअगरfies, deadline)) अणु
			dev_warn(ec_dev->dev, "EC failed to respond in time\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	/*
	 * ptr now poपूर्णांकs to the header byte. Copy any valid data to the
	 * start of our buffer
	 */
	toकरो = end - ++ptr;
	BUG_ON(toकरो < 0 || toकरो > ec_dev->din_size);
	toकरो = min(toकरो, need_len);
	स_हटाओ(ec_dev->din, ptr, toकरो);
	ptr = ec_dev->din + toकरो;
	dev_dbg(ec_dev->dev, "need %d, got %d bytes from preamble\n",
		 need_len, toकरो);
	need_len -= toकरो;

	/* Receive data until we have it all */
	जबतक (need_len > 0) अणु
		/*
		 * We can't support transfers larger than the SPI FIFO size
		 * unless we have DMA. We करोn't have DMA on the ISP SPI ports
		 * क्रम Exynos. We need a way of asking SPI driver क्रम
		 * maximum-supported transfer size.
		 */
		toकरो = min(need_len, 256);
		dev_dbg(ec_dev->dev, "loop, todo=%d, need_len=%d, ptr=%zd\n",
			toकरो, need_len, ptr - ec_dev->din);

		ret = receive_n_bytes(ec_dev, ptr, toकरो);
		अगर (ret < 0)
			वापस ret;

		debug_packet(ec_dev->dev, "interim", ptr, toकरो);
		ptr += toकरो;
		need_len -= toकरो;
	पूर्ण

	dev_dbg(ec_dev->dev, "loop done, ptr=%zd\n", ptr - ec_dev->din);

	वापस 0;
पूर्ण

/**
 * करो_cros_ec_pkt_xfer_spi - Transfer a packet over SPI and receive the reply
 *
 * @ec_dev: ChromeOS EC device
 * @ec_msg: Message to transfer
 */
अटल पूर्णांक करो_cros_ec_pkt_xfer_spi(काष्ठा cros_ec_device *ec_dev,
				   काष्ठा cros_ec_command *ec_msg)
अणु
	काष्ठा ec_host_response *response;
	काष्ठा cros_ec_spi *ec_spi = ec_dev->priv;
	काष्ठा spi_transfer trans, trans_delay;
	काष्ठा spi_message msg;
	पूर्णांक i, len;
	u8 *ptr;
	u8 *rx_buf;
	u8 sum;
	u8 rx_byte;
	पूर्णांक ret = 0, final_ret;
	अचिन्हित दीर्घ delay;

	len = cros_ec_prepare_tx(ec_dev, ec_msg);
	dev_dbg(ec_dev->dev, "prepared, len=%d\n", len);

	/* If it's too soon to करो another transaction, रुको */
	delay = kसमय_get_ns() - ec_spi->last_transfer_ns;
	अगर (delay < EC_SPI_RECOVERY_TIME_NS)
		ndelay(EC_SPI_RECOVERY_TIME_NS - delay);

	rx_buf = kzalloc(len, GFP_KERNEL);
	अगर (!rx_buf)
		वापस -ENOMEM;

	spi_bus_lock(ec_spi->spi->master);

	/*
	 * Leave a gap between CS निश्चितion and घड़ीing of data to allow the
	 * EC समय to wakeup.
	 */
	spi_message_init(&msg);
	अगर (ec_spi->start_of_msg_delay) अणु
		स_रखो(&trans_delay, 0, माप(trans_delay));
		trans_delay.delay.value = ec_spi->start_of_msg_delay;
		trans_delay.delay.unit = SPI_DELAY_UNIT_USECS;
		spi_message_add_tail(&trans_delay, &msg);
	पूर्ण

	/* Transmit phase - send our message */
	स_रखो(&trans, 0, माप(trans));
	trans.tx_buf = ec_dev->करोut;
	trans.rx_buf = rx_buf;
	trans.len = len;
	trans.cs_change = 1;
	spi_message_add_tail(&trans, &msg);
	ret = spi_sync_locked(ec_spi->spi, &msg);

	/* Get the response */
	अगर (!ret) अणु
		/* Verअगरy that EC can process command */
		क्रम (i = 0; i < len; i++) अणु
			rx_byte = rx_buf[i];
			/*
			 * Seeing the PAST_END, RX_BAD_DATA, or NOT_READY
			 * markers are all signs that the EC didn't fully
			 * receive our command. e.g., अगर the EC is flashing
			 * itself, it can't respond to any commands and instead
			 * घड़ीs out EC_SPI_PAST_END from its SPI hardware
			 * buffer. Similar occurrences can happen अगर the AP is
			 * too slow to घड़ी out data after निश्चितing CS -- the
			 * EC will पात and fill its buffer with
			 * EC_SPI_RX_BAD_DATA.
			 *
			 * In all हालs, these errors should be safe to retry.
			 * Report -EAGAIN and let the caller decide what to करो
			 * about that.
			 */
			अगर (rx_byte == EC_SPI_PAST_END  ||
			    rx_byte == EC_SPI_RX_BAD_DATA ||
			    rx_byte == EC_SPI_NOT_READY) अणु
				ret = -EAGAIN;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!ret)
		ret = cros_ec_spi_receive_packet(ec_dev,
				ec_msg->insize + माप(*response));
	अन्यथा अगर (ret != -EAGAIN)
		dev_err(ec_dev->dev, "spi transfer failed: %d\n", ret);

	final_ret = terminate_request(ec_dev);

	spi_bus_unlock(ec_spi->spi->master);

	अगर (!ret)
		ret = final_ret;
	अगर (ret < 0)
		जाओ निकास;

	ptr = ec_dev->din;

	/* check response error code */
	response = (काष्ठा ec_host_response *)ptr;
	ec_msg->result = response->result;

	ret = cros_ec_check_result(ec_dev, ec_msg);
	अगर (ret)
		जाओ निकास;

	len = response->data_len;
	sum = 0;
	अगर (len > ec_msg->insize) अणु
		dev_err(ec_dev->dev, "packet too long (%d bytes, expected %d)",
			len, ec_msg->insize);
		ret = -EMSGSIZE;
		जाओ निकास;
	पूर्ण

	क्रम (i = 0; i < माप(*response); i++)
		sum += ptr[i];

	/* copy response packet payload and compute checksum */
	स_नकल(ec_msg->data, ptr + माप(*response), len);
	क्रम (i = 0; i < len; i++)
		sum += ec_msg->data[i];

	अगर (sum) अणु
		dev_err(ec_dev->dev,
			"bad packet checksum, calculated %x\n",
			sum);
		ret = -EBADMSG;
		जाओ निकास;
	पूर्ण

	ret = len;
निकास:
	kमुक्त(rx_buf);
	अगर (ec_msg->command == EC_CMD_REBOOT_EC)
		msleep(EC_REBOOT_DELAY_MS);

	वापस ret;
पूर्ण

/**
 * करो_cros_ec_cmd_xfer_spi - Transfer a message over SPI and receive the reply
 *
 * @ec_dev: ChromeOS EC device
 * @ec_msg: Message to transfer
 */
अटल पूर्णांक करो_cros_ec_cmd_xfer_spi(काष्ठा cros_ec_device *ec_dev,
				   काष्ठा cros_ec_command *ec_msg)
अणु
	काष्ठा cros_ec_spi *ec_spi = ec_dev->priv;
	काष्ठा spi_transfer trans;
	काष्ठा spi_message msg;
	पूर्णांक i, len;
	u8 *ptr;
	u8 *rx_buf;
	u8 rx_byte;
	पूर्णांक sum;
	पूर्णांक ret = 0, final_ret;
	अचिन्हित दीर्घ delay;

	len = cros_ec_prepare_tx(ec_dev, ec_msg);
	dev_dbg(ec_dev->dev, "prepared, len=%d\n", len);

	/* If it's too soon to करो another transaction, रुको */
	delay = kसमय_get_ns() - ec_spi->last_transfer_ns;
	अगर (delay < EC_SPI_RECOVERY_TIME_NS)
		ndelay(EC_SPI_RECOVERY_TIME_NS - delay);

	rx_buf = kzalloc(len, GFP_KERNEL);
	अगर (!rx_buf)
		वापस -ENOMEM;

	spi_bus_lock(ec_spi->spi->master);

	/* Transmit phase - send our message */
	debug_packet(ec_dev->dev, "out", ec_dev->करोut, len);
	स_रखो(&trans, 0, माप(trans));
	trans.tx_buf = ec_dev->करोut;
	trans.rx_buf = rx_buf;
	trans.len = len;
	trans.cs_change = 1;
	spi_message_init(&msg);
	spi_message_add_tail(&trans, &msg);
	ret = spi_sync_locked(ec_spi->spi, &msg);

	/* Get the response */
	अगर (!ret) अणु
		/* Verअगरy that EC can process command */
		क्रम (i = 0; i < len; i++) अणु
			rx_byte = rx_buf[i];
			/* See comments in cros_ec_pkt_xfer_spi() */
			अगर (rx_byte == EC_SPI_PAST_END  ||
			    rx_byte == EC_SPI_RX_BAD_DATA ||
			    rx_byte == EC_SPI_NOT_READY) अणु
				ret = -EAGAIN;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!ret)
		ret = cros_ec_spi_receive_response(ec_dev,
				ec_msg->insize + EC_MSG_TX_PROTO_BYTES);
	अन्यथा अगर (ret != -EAGAIN)
		dev_err(ec_dev->dev, "spi transfer failed: %d\n", ret);

	final_ret = terminate_request(ec_dev);

	spi_bus_unlock(ec_spi->spi->master);

	अगर (!ret)
		ret = final_ret;
	अगर (ret < 0)
		जाओ निकास;

	ptr = ec_dev->din;

	/* check response error code */
	ec_msg->result = ptr[0];
	ret = cros_ec_check_result(ec_dev, ec_msg);
	अगर (ret)
		जाओ निकास;

	len = ptr[1];
	sum = ptr[0] + ptr[1];
	अगर (len > ec_msg->insize) अणु
		dev_err(ec_dev->dev, "packet too long (%d bytes, expected %d)",
			len, ec_msg->insize);
		ret = -ENOSPC;
		जाओ निकास;
	पूर्ण

	/* copy response packet payload and compute checksum */
	क्रम (i = 0; i < len; i++) अणु
		sum += ptr[i + 2];
		अगर (ec_msg->insize)
			ec_msg->data[i] = ptr[i + 2];
	पूर्ण
	sum &= 0xff;

	debug_packet(ec_dev->dev, "in", ptr, len + 3);

	अगर (sum != ptr[len + 2]) अणु
		dev_err(ec_dev->dev,
			"bad packet checksum, expected %02x, got %02x\n",
			sum, ptr[len + 2]);
		ret = -EBADMSG;
		जाओ निकास;
	पूर्ण

	ret = len;
निकास:
	kमुक्त(rx_buf);
	अगर (ec_msg->command == EC_CMD_REBOOT_EC)
		msleep(EC_REBOOT_DELAY_MS);

	वापस ret;
पूर्ण

अटल व्योम cros_ec_xfer_high_pri_work(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा cros_ec_xfer_work_params *params;

	params = container_of(work, काष्ठा cros_ec_xfer_work_params, work);
	params->ret = params->fn(params->ec_dev, params->ec_msg);
पूर्ण

अटल पूर्णांक cros_ec_xfer_high_pri(काष्ठा cros_ec_device *ec_dev,
				 काष्ठा cros_ec_command *ec_msg,
				 cros_ec_xfer_fn_t fn)
अणु
	काष्ठा cros_ec_spi *ec_spi = ec_dev->priv;
	काष्ठा cros_ec_xfer_work_params params = अणु
		.work = KTHREAD_WORK_INIT(params.work,
					  cros_ec_xfer_high_pri_work),
		.ec_dev = ec_dev,
		.ec_msg = ec_msg,
		.fn = fn,
	पूर्ण;

	/*
	 * This looks a bit ridiculous.  Why करो the work on a
	 * dअगरferent thपढ़ो अगर we're just going to block रुकोing क्रम
	 * the thपढ़ो to finish?  The key here is that the thपढ़ो is
	 * running at high priority but the calling context might not
	 * be.  We need to be at high priority to aव्योम getting
	 * context चयनed out क्रम too दीर्घ and the EC giving up on
	 * the transfer.
	 */
	kthपढ़ो_queue_work(ec_spi->high_pri_worker, &params.work);
	kthपढ़ो_flush_work(&params.work);

	वापस params.ret;
पूर्ण

अटल पूर्णांक cros_ec_pkt_xfer_spi(काष्ठा cros_ec_device *ec_dev,
				काष्ठा cros_ec_command *ec_msg)
अणु
	वापस cros_ec_xfer_high_pri(ec_dev, ec_msg, करो_cros_ec_pkt_xfer_spi);
पूर्ण

अटल पूर्णांक cros_ec_cmd_xfer_spi(काष्ठा cros_ec_device *ec_dev,
				काष्ठा cros_ec_command *ec_msg)
अणु
	वापस cros_ec_xfer_high_pri(ec_dev, ec_msg, करो_cros_ec_cmd_xfer_spi);
पूर्ण

अटल व्योम cros_ec_spi_dt_probe(काष्ठा cros_ec_spi *ec_spi, काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	u32 val;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(np, "google,cros-ec-spi-pre-delay", &val);
	अगर (!ret)
		ec_spi->start_of_msg_delay = val;

	ret = of_property_पढ़ो_u32(np, "google,cros-ec-spi-msg-delay", &val);
	अगर (!ret)
		ec_spi->end_of_msg_delay = val;
पूर्ण

अटल व्योम cros_ec_spi_high_pri_release(व्योम *worker)
अणु
	kthपढ़ो_destroy_worker(worker);
पूर्ण

अटल पूर्णांक cros_ec_spi_devm_high_pri_alloc(काष्ठा device *dev,
					   काष्ठा cros_ec_spi *ec_spi)
अणु
	पूर्णांक err;

	ec_spi->high_pri_worker =
		kthपढ़ो_create_worker(0, "cros_ec_spi_high_pri");

	अगर (IS_ERR(ec_spi->high_pri_worker)) अणु
		err = PTR_ERR(ec_spi->high_pri_worker);
		dev_err(dev, "Can't create cros_ec high pri worker: %d\n", err);
		वापस err;
	पूर्ण

	err = devm_add_action_or_reset(dev, cros_ec_spi_high_pri_release,
				       ec_spi->high_pri_worker);
	अगर (err)
		वापस err;

	sched_set_fअगरo(ec_spi->high_pri_worker->task);

	वापस 0;
पूर्ण

अटल पूर्णांक cros_ec_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	काष्ठा cros_ec_device *ec_dev;
	काष्ठा cros_ec_spi *ec_spi;
	पूर्णांक err;

	spi->rt = true;
	err = spi_setup(spi);
	अगर (err < 0)
		वापस err;

	ec_spi = devm_kzalloc(dev, माप(*ec_spi), GFP_KERNEL);
	अगर (ec_spi == शून्य)
		वापस -ENOMEM;
	ec_spi->spi = spi;
	ec_dev = devm_kzalloc(dev, माप(*ec_dev), GFP_KERNEL);
	अगर (!ec_dev)
		वापस -ENOMEM;

	/* Check क्रम any DT properties */
	cros_ec_spi_dt_probe(ec_spi, dev);

	spi_set_drvdata(spi, ec_dev);
	ec_dev->dev = dev;
	ec_dev->priv = ec_spi;
	ec_dev->irq = spi->irq;
	ec_dev->cmd_xfer = cros_ec_cmd_xfer_spi;
	ec_dev->pkt_xfer = cros_ec_pkt_xfer_spi;
	ec_dev->phys_name = dev_name(&ec_spi->spi->dev);
	ec_dev->din_size = EC_MSG_PREAMBLE_COUNT +
			   माप(काष्ठा ec_host_response) +
			   माप(काष्ठा ec_response_get_protocol_info);
	ec_dev->करोut_size = माप(काष्ठा ec_host_request);

	ec_spi->last_transfer_ns = kसमय_get_ns();

	err = cros_ec_spi_devm_high_pri_alloc(dev, ec_spi);
	अगर (err)
		वापस err;

	err = cros_ec_रेजिस्टर(ec_dev);
	अगर (err) अणु
		dev_err(dev, "cannot register EC\n");
		वापस err;
	पूर्ण

	device_init_wakeup(&spi->dev, true);

	वापस 0;
पूर्ण

अटल पूर्णांक cros_ec_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा cros_ec_device *ec_dev = spi_get_drvdata(spi);

	वापस cros_ec_unरेजिस्टर(ec_dev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक cros_ec_spi_suspend(काष्ठा device *dev)
अणु
	काष्ठा cros_ec_device *ec_dev = dev_get_drvdata(dev);

	वापस cros_ec_suspend(ec_dev);
पूर्ण

अटल पूर्णांक cros_ec_spi_resume(काष्ठा device *dev)
अणु
	काष्ठा cros_ec_device *ec_dev = dev_get_drvdata(dev);

	वापस cros_ec_resume(ec_dev);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(cros_ec_spi_pm_ops, cros_ec_spi_suspend,
			 cros_ec_spi_resume);

अटल स्थिर काष्ठा of_device_id cros_ec_spi_of_match[] = अणु
	अणु .compatible = "google,cros-ec-spi", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cros_ec_spi_of_match);

अटल स्थिर काष्ठा spi_device_id cros_ec_spi_id[] = अणु
	अणु "cros-ec-spi", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, cros_ec_spi_id);

अटल काष्ठा spi_driver cros_ec_driver_spi = अणु
	.driver	= अणु
		.name	= "cros-ec-spi",
		.of_match_table = cros_ec_spi_of_match,
		.pm	= &cros_ec_spi_pm_ops,
	पूर्ण,
	.probe		= cros_ec_spi_probe,
	.हटाओ		= cros_ec_spi_हटाओ,
	.id_table	= cros_ec_spi_id,
पूर्ण;

module_spi_driver(cros_ec_driver_spi);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("SPI interface for ChromeOS Embedded Controller");
