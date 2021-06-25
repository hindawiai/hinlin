<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Mailbox पूर्णांकerface क्रम Wilco Embedded Controller
 *
 * Copyright 2018 Google LLC
 *
 * The Wilco EC is similar to a typical ChromeOS embedded controller.
 * It uses the same MEC based low-level communication and a similar
 * protocol, but with some important dअगरferences.  The EC firmware करोes
 * not support the same mailbox commands so it is not रेजिस्टरed as a
 * cros_ec device type.
 *
 * Most messages follow a standard क्रमmat, but there are some exceptions
 * and an पूर्णांकerface is provided to करो direct/raw transactions that करो not
 * make assumptions about byte placement.
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_data/wilco-ec.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "../cros_ec_lpc_mec.h"

/* Version of mailbox पूर्णांकerface */
#घोषणा EC_MAILBOX_VERSION		0

/* Command to start mailbox transaction */
#घोषणा EC_MAILBOX_START_COMMAND	0xda

/* Version of EC protocol */
#घोषणा EC_MAILBOX_PROTO_VERSION	3

/* Number of header bytes to be counted as data bytes */
#घोषणा EC_MAILBOX_DATA_EXTRA		2

/* Maximum समयout */
#घोषणा EC_MAILBOX_TIMEOUT		HZ

/* EC response flags */
#घोषणा EC_CMDR_DATA		BIT(0)	/* Data पढ़ोy क्रम host to पढ़ो */
#घोषणा EC_CMDR_PENDING		BIT(1)	/* Write pending to EC */
#घोषणा EC_CMDR_BUSY		BIT(2)	/* EC is busy processing a command */
#घोषणा EC_CMDR_CMD		BIT(3)	/* Last host ग_लिखो was a command */

/**
 * wilco_ec_response_समयd_out() - Wait क्रम EC response.
 * @ec: EC device.
 *
 * Return: true अगर EC समयd out, false अगर EC did not समय out.
 */
अटल bool wilco_ec_response_समयd_out(काष्ठा wilco_ec_device *ec)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + EC_MAILBOX_TIMEOUT;

	करो अणु
		अगर (!(inb(ec->io_command->start) &
		      (EC_CMDR_PENDING | EC_CMDR_BUSY)))
			वापस false;
		usleep_range(100, 200);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	वापस true;
पूर्ण

/**
 * wilco_ec_checksum() - Compute 8-bit checksum over data range.
 * @data: Data to checksum.
 * @size: Number of bytes to checksum.
 *
 * Return: 8-bit checksum of provided data.
 */
अटल u8 wilco_ec_checksum(स्थिर व्योम *data, माप_प्रकार size)
अणु
	u8 *data_bytes = (u8 *)data;
	u8 checksum = 0;
	माप_प्रकार i;

	क्रम (i = 0; i < size; i++)
		checksum += data_bytes[i];

	वापस checksum;
पूर्ण

/**
 * wilco_ec_prepare() - Prepare the request काष्ठाure क्रम the EC.
 * @msg: EC message with request inक्रमmation.
 * @rq: EC request काष्ठाure to fill.
 */
अटल व्योम wilco_ec_prepare(काष्ठा wilco_ec_message *msg,
			     काष्ठा wilco_ec_request *rq)
अणु
	स_रखो(rq, 0, माप(*rq));
	rq->काष्ठा_version = EC_MAILBOX_PROTO_VERSION;
	rq->mailbox_id = msg->type;
	rq->mailbox_version = EC_MAILBOX_VERSION;
	rq->data_size = msg->request_size;

	/* Checksum header and data */
	rq->checksum = wilco_ec_checksum(rq, माप(*rq));
	rq->checksum += wilco_ec_checksum(msg->request_data, msg->request_size);
	rq->checksum = -rq->checksum;
पूर्ण

/**
 * wilco_ec_transfer() - Perक्रमm actual data transfer.
 * @ec: EC device.
 * @msg: EC message data क्रम request and response.
 * @rq: Filled in request काष्ठाure
 *
 * Context: ec->mailbox_lock should be held जबतक using this function.
 * Return: number of bytes received or negative error code on failure.
 */
अटल पूर्णांक wilco_ec_transfer(काष्ठा wilco_ec_device *ec,
			     काष्ठा wilco_ec_message *msg,
			     काष्ठा wilco_ec_request *rq)
अणु
	काष्ठा wilco_ec_response *rs;
	u8 checksum;
	u8 flag;

	/* Write request header, then data */
	cros_ec_lpc_io_bytes_mec(MEC_IO_WRITE, 0, माप(*rq), (u8 *)rq);
	cros_ec_lpc_io_bytes_mec(MEC_IO_WRITE, माप(*rq), msg->request_size,
				 msg->request_data);

	/* Start the command */
	outb(EC_MAILBOX_START_COMMAND, ec->io_command->start);

	/* For some commands (eg shutकरोwn) the EC will not respond, that's OK */
	अगर (msg->flags & WILCO_EC_FLAG_NO_RESPONSE) अणु
		dev_dbg(ec->dev, "EC does not respond to this command\n");
		वापस 0;
	पूर्ण

	/* Wait क्रम it to complete */
	अगर (wilco_ec_response_समयd_out(ec)) अणु
		dev_dbg(ec->dev, "response timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

	/* Check result */
	flag = inb(ec->io_data->start);
	अगर (flag) अणु
		dev_dbg(ec->dev, "bad response: 0x%02x\n", flag);
		वापस -EIO;
	पूर्ण

	/* Read back response */
	rs = ec->data_buffer;
	checksum = cros_ec_lpc_io_bytes_mec(MEC_IO_READ, 0,
					    माप(*rs) + EC_MAILBOX_DATA_SIZE,
					    (u8 *)rs);
	अगर (checksum) अणु
		dev_dbg(ec->dev, "bad packet checksum 0x%02x\n", rs->checksum);
		वापस -EBADMSG;
	पूर्ण

	अगर (rs->result) अणु
		dev_dbg(ec->dev, "EC reported failure: 0x%02x\n", rs->result);
		वापस -EBADMSG;
	पूर्ण

	अगर (rs->data_size != EC_MAILBOX_DATA_SIZE) अणु
		dev_dbg(ec->dev, "unexpected packet size (%u != %u)\n",
			rs->data_size, EC_MAILBOX_DATA_SIZE);
		वापस -EMSGSIZE;
	पूर्ण

	अगर (rs->data_size < msg->response_size) अणु
		dev_dbg(ec->dev, "EC didn't return enough data (%u < %zu)\n",
			rs->data_size, msg->response_size);
		वापस -EMSGSIZE;
	पूर्ण

	स_नकल(msg->response_data, rs->data, msg->response_size);

	वापस rs->data_size;
पूर्ण

/**
 * wilco_ec_mailbox() - Send EC request and receive EC response.
 * @ec: EC device.
 * @msg: EC message data क्रम request and response.
 *
 * On entry msg->type, msg->request_size, and msg->request_data should all be
 * filled in. If desired, msg->flags can be set.
 *
 * If a response is expected, msg->response_size should be set, and
 * msg->response_data should poपूर्णांक to a buffer with enough space. On निकास
 * msg->response_data will be filled.
 *
 * Return: number of bytes received or negative error code on failure.
 */
पूर्णांक wilco_ec_mailbox(काष्ठा wilco_ec_device *ec, काष्ठा wilco_ec_message *msg)
अणु
	काष्ठा wilco_ec_request *rq;
	पूर्णांक ret;

	dev_dbg(ec->dev, "type=%04x flags=%02x rslen=%zu rqlen=%zu\n",
		msg->type, msg->flags, msg->response_size, msg->request_size);

	mutex_lock(&ec->mailbox_lock);
	/* Prepare request packet */
	rq = ec->data_buffer;
	wilco_ec_prepare(msg, rq);

	ret = wilco_ec_transfer(ec, msg, rq);
	mutex_unlock(&ec->mailbox_lock);

	वापस ret;

पूर्ण
EXPORT_SYMBOL_GPL(wilco_ec_mailbox);
