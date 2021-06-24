<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2020 Google Inc.
 *
 * Based on Infineon TPM driver by Peter Huewe.
 *
 * cr50 is a firmware क्रम H1 secure modules that requires special
 * handling क्रम the I2C पूर्णांकerface.
 *
 * - Use an पूर्णांकerrupt क्रम transaction status instead of hardcoded delays.
 * - Must use ग_लिखो+रुको+पढ़ो पढ़ो protocol.
 * - All 4 bytes of status रेजिस्टर must be पढ़ो/written at once.
 * - Burst count max is 63 bytes, and burst count behaves slightly dअगरferently
 *   than other I2C TPMs.
 * - When पढ़ोing from FIFO the full burstcnt must be पढ़ो instead of just
 *   पढ़ोing header and determining the reमुख्यder.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/completion.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>

#समावेश "tpm_tis_core.h"

#घोषणा TPM_CR50_MAX_बफ_मानE		64
#घोषणा TPM_CR50_TIMEOUT_SHORT_MS	2		/* Short समयout during transactions */
#घोषणा TPM_CR50_TIMEOUT_NOIRQ_MS	20		/* Timeout क्रम TPM पढ़ोy without IRQ */
#घोषणा TPM_CR50_I2C_DID_VID		0x00281ae0L	/* Device and venकरोr ID reg value */
#घोषणा TPM_CR50_I2C_MAX_RETRIES	3		/* Max retries due to I2C errors */
#घोषणा TPM_CR50_I2C_RETRY_DELAY_LO	55		/* Min usecs between retries on I2C */
#घोषणा TPM_CR50_I2C_RETRY_DELAY_HI	65		/* Max usecs between retries on I2C */

#घोषणा TPM_I2C_ACCESS(l)	(0x0000 | ((l) << 4))
#घोषणा TPM_I2C_STS(l)		(0x0001 | ((l) << 4))
#घोषणा TPM_I2C_DATA_FIFO(l)	(0x0005 | ((l) << 4))
#घोषणा TPM_I2C_DID_VID(l)	(0x0006 | ((l) << 4))

/**
 * काष्ठा tpm_i2c_cr50_priv_data - Driver निजी data.
 * @irq:	Irq number used क्रम this chip.
 *		If irq <= 0, then a fixed समयout is used instead of रुकोing क्रम irq.
 * @tpm_पढ़ोy:	Struct used by irq handler to संकेत R/W पढ़ोiness.
 * @buf:	Buffer used क्रम i2c ग_लिखोs, with i2c address prepended to content.
 *
 * Private driver काष्ठा used by kernel thपढ़ोs and पूर्णांकerrupt context.
 */
काष्ठा tpm_i2c_cr50_priv_data अणु
	पूर्णांक irq;
	काष्ठा completion tpm_पढ़ोy;
	u8 buf[TPM_CR50_MAX_बफ_मानE];
पूर्ण;

/**
 * tpm_cr50_i2c_पूर्णांक_handler() - cr50 पूर्णांकerrupt handler.
 * @dummy:	Unused parameter.
 * @tpm_info:	TPM chip inक्रमmation.
 *
 * The cr50 पूर्णांकerrupt handler संकेतs रुकोing thपढ़ोs that the
 * पूर्णांकerrupt has been निश्चितed. It करोes not करो any पूर्णांकerrupt triggered
 * processing but is instead used to aव्योम fixed delays.
 *
 * Return:
 *	IRQ_HANDLED signअगरies irq was handled by this device.
 */
अटल irqवापस_t tpm_cr50_i2c_पूर्णांक_handler(पूर्णांक dummy, व्योम *tpm_info)
अणु
	काष्ठा tpm_chip *chip = tpm_info;
	काष्ठा tpm_i2c_cr50_priv_data *priv = dev_get_drvdata(&chip->dev);

	complete(&priv->tpm_पढ़ोy);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * tpm_cr50_i2c_रुको_tpm_पढ़ोy() - Wait क्रम tpm to संकेत पढ़ोy.
 * @chip: A TPM chip.
 *
 * Wait क्रम completion पूर्णांकerrupt अगर available, otherwise use a fixed
 * delay क्रम the TPM to be पढ़ोy.
 *
 * Return:
 * - 0:		Success.
 * - -त्रुटि_सं:	A POSIX error code.
 */
अटल पूर्णांक tpm_cr50_i2c_रुको_tpm_पढ़ोy(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_i2c_cr50_priv_data *priv = dev_get_drvdata(&chip->dev);

	/* Use a safe fixed delay अगर पूर्णांकerrupt is not supported */
	अगर (priv->irq <= 0) अणु
		msleep(TPM_CR50_TIMEOUT_NOIRQ_MS);
		वापस 0;
	पूर्ण

	/* Wait क्रम पूर्णांकerrupt to indicate TPM is पढ़ोy to respond */
	अगर (!रुको_क्रम_completion_समयout(&priv->tpm_पढ़ोy,
					 msecs_to_jअगरfies(chip->समयout_a))) अणु
		dev_warn(&chip->dev, "Timeout waiting for TPM ready\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * tpm_cr50_i2c_enable_tpm_irq() - Enable TPM irq.
 * @chip: A TPM chip.
 */
अटल व्योम tpm_cr50_i2c_enable_tpm_irq(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_i2c_cr50_priv_data *priv = dev_get_drvdata(&chip->dev);

	अगर (priv->irq > 0) अणु
		reinit_completion(&priv->tpm_पढ़ोy);
		enable_irq(priv->irq);
	पूर्ण
पूर्ण

/**
 * tpm_cr50_i2c_disable_tpm_irq() - Disable TPM irq.
 * @chip: A TPM chip.
 */
अटल व्योम tpm_cr50_i2c_disable_tpm_irq(काष्ठा tpm_chip *chip)
अणु
	काष्ठा tpm_i2c_cr50_priv_data *priv = dev_get_drvdata(&chip->dev);

	अगर (priv->irq > 0)
		disable_irq(priv->irq);
पूर्ण

/**
 * tpm_cr50_i2c_transfer_message() - Transfer a message over i2c.
 * @dev:	Device inक्रमmation.
 * @adapter:	I2C adapter.
 * @msg:	Message to transfer.
 *
 * Call unlocked i2c transfer routine with the provided parameters and
 * retry in हाल of bus errors.
 *
 * Return:
 * - 0:		Success.
 * - -त्रुटि_सं:	A POSIX error code.
 */
अटल पूर्णांक tpm_cr50_i2c_transfer_message(काष्ठा device *dev,
					 काष्ठा i2c_adapter *adapter,
					 काष्ठा i2c_msg *msg)
अणु
	अचिन्हित पूर्णांक try;
	पूर्णांक rc;

	क्रम (try = 0; try < TPM_CR50_I2C_MAX_RETRIES; try++) अणु
		rc = __i2c_transfer(adapter, msg, 1);
		अगर (rc == 1)
			वापस 0; /* Successfully transferred the message */
		अगर (try)
			dev_warn(dev, "i2c transfer failed (attempt %d/%d): %d\n",
				 try + 1, TPM_CR50_I2C_MAX_RETRIES, rc);
		usleep_range(TPM_CR50_I2C_RETRY_DELAY_LO, TPM_CR50_I2C_RETRY_DELAY_HI);
	पूर्ण

	/* No i2c message transferred */
	वापस -EIO;
पूर्ण

/**
 * tpm_cr50_i2c_पढ़ो() - Read from TPM रेजिस्टर.
 * @chip:	A TPM chip.
 * @addr:	Register address to पढ़ो from.
 * @buffer:	Read destination, provided by caller.
 * @len:	Number of bytes to पढ़ो.
 *
 * Sends the रेजिस्टर address byte to the TPM, then रुकोs until TPM
 * is पढ़ोy via पूर्णांकerrupt संकेत or समयout expiration, then 'len'
 * bytes are पढ़ो from TPM response पूर्णांकo the provided 'buffer'.
 *
 * Return:
 * - 0:		Success.
 * - -त्रुटि_सं:	A POSIX error code.
 */
अटल पूर्णांक tpm_cr50_i2c_पढ़ो(काष्ठा tpm_chip *chip, u8 addr, u8 *buffer, माप_प्रकार len)
अणु
	काष्ठा i2c_client *client = to_i2c_client(chip->dev.parent);
	काष्ठा i2c_msg msg_reg_addr = अणु
		.addr = client->addr,
		.len = 1,
		.buf = &addr
	पूर्ण;
	काष्ठा i2c_msg msg_response = अणु
		.addr = client->addr,
		.flags = I2C_M_RD,
		.len = len,
		.buf = buffer
	पूर्ण;
	पूर्णांक rc;

	i2c_lock_bus(client->adapter, I2C_LOCK_SEGMENT);

	/* Prepare क्रम completion पूर्णांकerrupt */
	tpm_cr50_i2c_enable_tpm_irq(chip);

	/* Send the रेजिस्टर address byte to the TPM */
	rc = tpm_cr50_i2c_transfer_message(&chip->dev, client->adapter, &msg_reg_addr);
	अगर (rc < 0)
		जाओ out;

	/* Wait क्रम TPM to be पढ़ोy with response data */
	rc = tpm_cr50_i2c_रुको_tpm_पढ़ोy(chip);
	अगर (rc < 0)
		जाओ out;

	/* Read response data from the TPM */
	rc = tpm_cr50_i2c_transfer_message(&chip->dev, client->adapter, &msg_response);

out:
	tpm_cr50_i2c_disable_tpm_irq(chip);
	i2c_unlock_bus(client->adapter, I2C_LOCK_SEGMENT);

	अगर (rc < 0)
		वापस rc;

	वापस 0;
पूर्ण

/**
 * tpm_cr50_i2c_ग_लिखो()- Write to TPM रेजिस्टर.
 * @chip:	A TPM chip.
 * @addr:	Register address to ग_लिखो to.
 * @buffer:	Data to ग_लिखो.
 * @len:	Number of bytes to ग_लिखो.
 *
 * The provided address is prepended to the data in 'buffer', the
 * cobined address+data is sent to the TPM, then रुको क्रम TPM to
 * indicate it is करोne writing.
 *
 * Return:
 * - 0:		Success.
 * - -त्रुटि_सं:	A POSIX error code.
 */
अटल पूर्णांक tpm_cr50_i2c_ग_लिखो(काष्ठा tpm_chip *chip, u8 addr, u8 *buffer,
			      माप_प्रकार len)
अणु
	काष्ठा tpm_i2c_cr50_priv_data *priv = dev_get_drvdata(&chip->dev);
	काष्ठा i2c_client *client = to_i2c_client(chip->dev.parent);
	काष्ठा i2c_msg msg = अणु
		.addr = client->addr,
		.len = len + 1,
		.buf = priv->buf
	पूर्ण;
	पूर्णांक rc;

	अगर (len > TPM_CR50_MAX_बफ_मानE - 1)
		वापस -EINVAL;

	/* Prepend the 'register address' to the buffer */
	priv->buf[0] = addr;
	स_नकल(priv->buf + 1, buffer, len);

	i2c_lock_bus(client->adapter, I2C_LOCK_SEGMENT);

	/* Prepare क्रम completion पूर्णांकerrupt */
	tpm_cr50_i2c_enable_tpm_irq(chip);

	/* Send ग_लिखो request buffer with address */
	rc = tpm_cr50_i2c_transfer_message(&chip->dev, client->adapter, &msg);
	अगर (rc < 0)
		जाओ out;

	/* Wait क्रम TPM to be पढ़ोy, ignore समयout */
	tpm_cr50_i2c_रुको_tpm_पढ़ोy(chip);

out:
	tpm_cr50_i2c_disable_tpm_irq(chip);
	i2c_unlock_bus(client->adapter, I2C_LOCK_SEGMENT);

	अगर (rc < 0)
		वापस rc;

	वापस 0;
पूर्ण

/**
 * tpm_cr50_check_locality() - Verअगरy TPM locality 0 is active.
 * @chip: A TPM chip.
 *
 * Return:
 * - 0:		Success.
 * - -त्रुटि_सं:	A POSIX error code.
 */
अटल पूर्णांक tpm_cr50_check_locality(काष्ठा tpm_chip *chip)
अणु
	u8 mask = TPM_ACCESS_VALID | TPM_ACCESS_ACTIVE_LOCALITY;
	u8 buf;
	पूर्णांक rc;

	rc = tpm_cr50_i2c_पढ़ो(chip, TPM_I2C_ACCESS(0), &buf, माप(buf));
	अगर (rc < 0)
		वापस rc;

	अगर ((buf & mask) == mask)
		वापस 0;

	वापस -EIO;
पूर्ण

/**
 * tpm_cr50_release_locality() - Release TPM locality.
 * @chip:	A TPM chip.
 * @क्रमce:	Flag to क्रमce release अगर set.
 */
अटल व्योम tpm_cr50_release_locality(काष्ठा tpm_chip *chip, bool क्रमce)
अणु
	u8 mask = TPM_ACCESS_VALID | TPM_ACCESS_REQUEST_PENDING;
	u8 addr = TPM_I2C_ACCESS(0);
	u8 buf;

	अगर (tpm_cr50_i2c_पढ़ो(chip, addr, &buf, माप(buf)) < 0)
		वापस;

	अगर (क्रमce || (buf & mask) == mask) अणु
		buf = TPM_ACCESS_ACTIVE_LOCALITY;
		tpm_cr50_i2c_ग_लिखो(chip, addr, &buf, माप(buf));
	पूर्ण
पूर्ण

/**
 * tpm_cr50_request_locality() - Request TPM locality 0.
 * @chip: A TPM chip.
 *
 * Return:
 * - 0:		Success.
 * - -त्रुटि_सं:	A POSIX error code.
 */
अटल पूर्णांक tpm_cr50_request_locality(काष्ठा tpm_chip *chip)
अणु
	u8 buf = TPM_ACCESS_REQUEST_USE;
	अचिन्हित दीर्घ stop;
	पूर्णांक rc;

	अगर (!tpm_cr50_check_locality(chip))
		वापस 0;

	rc = tpm_cr50_i2c_ग_लिखो(chip, TPM_I2C_ACCESS(0), &buf, माप(buf));
	अगर (rc < 0)
		वापस rc;

	stop = jअगरfies + chip->समयout_a;
	करो अणु
		अगर (!tpm_cr50_check_locality(chip))
			वापस 0;

		msleep(TPM_CR50_TIMEOUT_SHORT_MS);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, stop));

	वापस -ETIMEDOUT;
पूर्ण

/**
 * tpm_cr50_i2c_tis_status() - Read cr50 tis status.
 * @chip: A TPM chip.
 *
 * cr50 requires all 4 bytes of status रेजिस्टर to be पढ़ो.
 *
 * Return:
 *	TPM status byte.
 */
अटल u8 tpm_cr50_i2c_tis_status(काष्ठा tpm_chip *chip)
अणु
	u8 buf[4];

	अगर (tpm_cr50_i2c_पढ़ो(chip, TPM_I2C_STS(0), buf, माप(buf)) < 0)
		वापस 0;

	वापस buf[0];
पूर्ण

/**
 * tpm_cr50_i2c_tis_set_पढ़ोy() - Set status रेजिस्टर to पढ़ोy.
 * @chip: A TPM chip.
 *
 * cr50 requires all 4 bytes of status रेजिस्टर to be written.
 */
अटल व्योम tpm_cr50_i2c_tis_set_पढ़ोy(काष्ठा tpm_chip *chip)
अणु
	u8 buf[4] = अणु TPM_STS_COMMAND_READY पूर्ण;

	tpm_cr50_i2c_ग_लिखो(chip, TPM_I2C_STS(0), buf, माप(buf));
	msleep(TPM_CR50_TIMEOUT_SHORT_MS);
पूर्ण

/**
 * tpm_cr50_i2c_get_burst_and_status() - Get burst count and status.
 * @chip:	A TPM chip.
 * @mask:	Status mask.
 * @burst:	Return value क्रम burst.
 * @status:	Return value क्रम status.
 *
 * cr50 uses bytes 3:2 of status रेजिस्टर क्रम burst count and
 * all 4 bytes must be पढ़ो.
 *
 * Return:
 * - 0:		Success.
 * - -त्रुटि_सं:	A POSIX error code.
 */
अटल पूर्णांक tpm_cr50_i2c_get_burst_and_status(काष्ठा tpm_chip *chip, u8 mask,
					     माप_प्रकार *burst, u32 *status)
अणु
	अचिन्हित दीर्घ stop;
	u8 buf[4];

	*status = 0;

	/* रुको क्रम burstcount */
	stop = jअगरfies + chip->समयout_b;

	करो अणु
		अगर (tpm_cr50_i2c_पढ़ो(chip, TPM_I2C_STS(0), buf, माप(buf)) < 0) अणु
			msleep(TPM_CR50_TIMEOUT_SHORT_MS);
			जारी;
		पूर्ण

		*status = *buf;
		*burst = le16_to_cpup((__le16 *)(buf + 1));

		अगर ((*status & mask) == mask &&
		    *burst > 0 && *burst <= TPM_CR50_MAX_बफ_मानE - 1)
			वापस 0;

		msleep(TPM_CR50_TIMEOUT_SHORT_MS);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, stop));

	dev_err(&chip->dev, "Timeout reading burst and status\n");
	वापस -ETIMEDOUT;
पूर्ण

/**
 * tpm_cr50_i2c_tis_recv() - TPM reception callback.
 * @chip:	A TPM chip.
 * @buf:	Reception buffer.
 * @buf_len:	Buffer length to पढ़ो.
 *
 * Return:
 * - >= 0:	Number of पढ़ो bytes.
 * - -त्रुटि_सं:	A POSIX error code.
 */
अटल पूर्णांक tpm_cr50_i2c_tis_recv(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार buf_len)
अणु

	u8 mask = TPM_STS_VALID | TPM_STS_DATA_AVAIL;
	माप_प्रकार burstcnt, cur, len, expected;
	u8 addr = TPM_I2C_DATA_FIFO(0);
	u32 status;
	पूर्णांक rc;

	अगर (buf_len < TPM_HEADER_SIZE)
		वापस -EINVAL;

	rc = tpm_cr50_i2c_get_burst_and_status(chip, mask, &burstcnt, &status);
	अगर (rc < 0)
		जाओ out_err;

	अगर (burstcnt > buf_len || burstcnt < TPM_HEADER_SIZE) अणु
		dev_err(&chip->dev,
			"Unexpected burstcnt: %zu (max=%zu, min=%d)\n",
			burstcnt, buf_len, TPM_HEADER_SIZE);
		rc = -EIO;
		जाओ out_err;
	पूर्ण

	/* Read first chunk of burstcnt bytes */
	rc = tpm_cr50_i2c_पढ़ो(chip, addr, buf, burstcnt);
	अगर (rc < 0) अणु
		dev_err(&chip->dev, "Read of first chunk failed\n");
		जाओ out_err;
	पूर्ण

	/* Determine expected data in the वापस buffer */
	expected = be32_to_cpup((__be32 *)(buf + 2));
	अगर (expected > buf_len) अणु
		dev_err(&chip->dev, "Buffer too small to receive i2c data\n");
		rc = -E2BIG;
		जाओ out_err;
	पूर्ण

	/* Now पढ़ो the rest of the data */
	cur = burstcnt;
	जबतक (cur < expected) अणु
		/* Read updated burst count and check status */
		rc = tpm_cr50_i2c_get_burst_and_status(chip, mask, &burstcnt, &status);
		अगर (rc < 0)
			जाओ out_err;

		len = min_t(माप_प्रकार, burstcnt, expected - cur);
		rc = tpm_cr50_i2c_पढ़ो(chip, addr, buf + cur, len);
		अगर (rc < 0) अणु
			dev_err(&chip->dev, "Read failed\n");
			जाओ out_err;
		पूर्ण

		cur += len;
	पूर्ण

	/* Ensure TPM is करोne पढ़ोing data */
	rc = tpm_cr50_i2c_get_burst_and_status(chip, TPM_STS_VALID, &burstcnt, &status);
	अगर (rc < 0)
		जाओ out_err;
	अगर (status & TPM_STS_DATA_AVAIL) अणु
		dev_err(&chip->dev, "Data still available\n");
		rc = -EIO;
		जाओ out_err;
	पूर्ण

	tpm_cr50_release_locality(chip, false);
	वापस cur;

out_err:
	/* Abort current transaction अगर still pending */
	अगर (tpm_cr50_i2c_tis_status(chip) & TPM_STS_COMMAND_READY)
		tpm_cr50_i2c_tis_set_पढ़ोy(chip);

	tpm_cr50_release_locality(chip, false);
	वापस rc;
पूर्ण

/**
 * tpm_cr50_i2c_tis_send() - TPM transmission callback.
 * @chip:	A TPM chip.
 * @buf:	Buffer to send.
 * @len:	Buffer length.
 *
 * Return:
 * - 0:		Success.
 * - -त्रुटि_सं:	A POSIX error code.
 */
अटल पूर्णांक tpm_cr50_i2c_tis_send(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार len)
अणु
	माप_प्रकार burstcnt, limit, sent = 0;
	u8 tpm_go[4] = अणु TPM_STS_GO पूर्ण;
	अचिन्हित दीर्घ stop;
	u32 status;
	पूर्णांक rc;

	rc = tpm_cr50_request_locality(chip);
	अगर (rc < 0)
		वापस rc;

	/* Wait until TPM is पढ़ोy क्रम a command */
	stop = jअगरfies + chip->समयout_b;
	जबतक (!(tpm_cr50_i2c_tis_status(chip) & TPM_STS_COMMAND_READY)) अणु
		अगर (समय_after(jअगरfies, stop)) अणु
			rc = -ETIMEDOUT;
			जाओ out_err;
		पूर्ण

		tpm_cr50_i2c_tis_set_पढ़ोy(chip);
	पूर्ण

	जबतक (len > 0) अणु
		u8 mask = TPM_STS_VALID;

		/* Wait क्रम data अगर this is not the first chunk */
		अगर (sent > 0)
			mask |= TPM_STS_DATA_EXPECT;

		/* Read burst count and check status */
		rc = tpm_cr50_i2c_get_burst_and_status(chip, mask, &burstcnt, &status);
		अगर (rc < 0)
			जाओ out_err;

		/*
		 * Use burstcnt - 1 to account क्रम the address byte
		 * that is inserted by tpm_cr50_i2c_ग_लिखो()
		 */
		limit = min_t(माप_प्रकार, burstcnt - 1, len);
		rc = tpm_cr50_i2c_ग_लिखो(chip, TPM_I2C_DATA_FIFO(0), &buf[sent], limit);
		अगर (rc < 0) अणु
			dev_err(&chip->dev, "Write failed\n");
			जाओ out_err;
		पूर्ण

		sent += limit;
		len -= limit;
	पूर्ण

	/* Ensure TPM is not expecting more data */
	rc = tpm_cr50_i2c_get_burst_and_status(chip, TPM_STS_VALID, &burstcnt, &status);
	अगर (rc < 0)
		जाओ out_err;
	अगर (status & TPM_STS_DATA_EXPECT) अणु
		dev_err(&chip->dev, "Data still expected\n");
		rc = -EIO;
		जाओ out_err;
	पूर्ण

	/* Start the TPM command */
	rc = tpm_cr50_i2c_ग_लिखो(chip, TPM_I2C_STS(0), tpm_go,
				माप(tpm_go));
	अगर (rc < 0) अणु
		dev_err(&chip->dev, "Start command failed\n");
		जाओ out_err;
	पूर्ण
	वापस 0;

out_err:
	/* Abort current transaction अगर still pending */
	अगर (tpm_cr50_i2c_tis_status(chip) & TPM_STS_COMMAND_READY)
		tpm_cr50_i2c_tis_set_पढ़ोy(chip);

	tpm_cr50_release_locality(chip, false);
	वापस rc;
पूर्ण

/**
 * tpm_cr50_i2c_req_canceled() - Callback to notअगरy a request cancel.
 * @chip:	A TPM chip.
 * @status:	Status given by the cancel callback.
 *
 * Return:
 *	True अगर command is पढ़ोy, False otherwise.
 */
अटल bool tpm_cr50_i2c_req_canceled(काष्ठा tpm_chip *chip, u8 status)
अणु
	वापस status == TPM_STS_COMMAND_READY;
पूर्ण

अटल स्थिर काष्ठा tpm_class_ops cr50_i2c = अणु
	.flags = TPM_OPS_AUTO_STARTUP,
	.status = &tpm_cr50_i2c_tis_status,
	.recv = &tpm_cr50_i2c_tis_recv,
	.send = &tpm_cr50_i2c_tis_send,
	.cancel = &tpm_cr50_i2c_tis_set_पढ़ोy,
	.req_complete_mask = TPM_STS_DATA_AVAIL | TPM_STS_VALID,
	.req_complete_val = TPM_STS_DATA_AVAIL | TPM_STS_VALID,
	.req_canceled = &tpm_cr50_i2c_req_canceled,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id cr50_i2c_table[] = अणु
	अणु"cr50_i2c", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, cr50_i2c_table);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id cr50_i2c_acpi_id[] = अणु
	अणु "GOOG0005", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, cr50_i2c_acpi_id);
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id of_cr50_i2c_match[] = अणु
	अणु .compatible = "google,cr50", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_cr50_i2c_match);
#पूर्ण_अगर

/**
 * tpm_cr50_i2c_probe() - Driver probe function.
 * @client:	I2C client inक्रमmation.
 * @id:		I2C device id.
 *
 * Return:
 * - 0:		Success.
 * - -त्रुटि_सं:	A POSIX error code.
 */
अटल पूर्णांक tpm_cr50_i2c_probe(काष्ठा i2c_client *client,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tpm_i2c_cr50_priv_data *priv;
	काष्ठा device *dev = &client->dev;
	काष्ठा tpm_chip *chip;
	u32 venकरोr;
	u8 buf[4];
	पूर्णांक rc;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		वापस -ENODEV;

	chip = tpmm_chip_alloc(dev, &cr50_i2c);
	अगर (IS_ERR(chip))
		वापस PTR_ERR(chip);

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	/* cr50 is a TPM 2.0 chip */
	chip->flags |= TPM_CHIP_FLAG_TPM2;
	chip->flags |= TPM_CHIP_FLAG_FIRMWARE_POWER_MANAGED;

	/* Default समयouts */
	chip->समयout_a = msecs_to_jअगरfies(TIS_SHORT_TIMEOUT);
	chip->समयout_b = msecs_to_jअगरfies(TIS_LONG_TIMEOUT);
	chip->समयout_c = msecs_to_jअगरfies(TIS_SHORT_TIMEOUT);
	chip->समयout_d = msecs_to_jअगरfies(TIS_SHORT_TIMEOUT);

	dev_set_drvdata(&chip->dev, priv);
	init_completion(&priv->tpm_पढ़ोy);

	अगर (client->irq > 0) अणु
		rc = devm_request_irq(dev, client->irq, tpm_cr50_i2c_पूर्णांक_handler,
				      IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				      dev->driver->name, chip);
		अगर (rc < 0) अणु
			dev_err(dev, "Failed to probe IRQ %d\n", client->irq);
			वापस rc;
		पूर्ण

		disable_irq(client->irq);
		priv->irq = client->irq;
	पूर्ण अन्यथा अणु
		dev_warn(dev, "No IRQ, will use %ums delay for TPM ready\n",
			 TPM_CR50_TIMEOUT_NOIRQ_MS);
	पूर्ण

	rc = tpm_cr50_request_locality(chip);
	अगर (rc < 0) अणु
		dev_err(dev, "Could not request locality\n");
		वापस rc;
	पूर्ण

	/* Read four bytes from DID_VID रेजिस्टर */
	rc = tpm_cr50_i2c_पढ़ो(chip, TPM_I2C_DID_VID(0), buf, माप(buf));
	अगर (rc < 0) अणु
		dev_err(dev, "Could not read vendor id\n");
		tpm_cr50_release_locality(chip, true);
		वापस rc;
	पूर्ण

	venकरोr = le32_to_cpup((__le32 *)buf);
	अगर (venकरोr != TPM_CR50_I2C_DID_VID) अणु
		dev_err(dev, "Vendor ID did not match! ID was %08x\n", venकरोr);
		tpm_cr50_release_locality(chip, true);
		वापस -ENODEV;
	पूर्ण

	dev_info(dev, "cr50 TPM 2.0 (i2c 0x%02x irq %d id 0x%x)\n",
		 client->addr, client->irq, venकरोr >> 16);

	वापस tpm_chip_रेजिस्टर(chip);
पूर्ण

/**
 * tpm_cr50_i2c_हटाओ() - Driver हटाओ function.
 * @client: I2C client inक्रमmation.
 *
 * Return:
 * - 0:		Success.
 * - -त्रुटि_सं:	A POSIX error code.
 */
अटल पूर्णांक tpm_cr50_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tpm_chip *chip = i2c_get_clientdata(client);
	काष्ठा device *dev = &client->dev;

	अगर (!chip) अणु
		dev_err(dev, "Could not get client data at remove\n");
		वापस -ENODEV;
	पूर्ण

	tpm_chip_unरेजिस्टर(chip);
	tpm_cr50_release_locality(chip, true);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(cr50_i2c_pm, tpm_pm_suspend, tpm_pm_resume);

अटल काष्ठा i2c_driver cr50_i2c_driver = अणु
	.id_table = cr50_i2c_table,
	.probe = tpm_cr50_i2c_probe,
	.हटाओ = tpm_cr50_i2c_हटाओ,
	.driver = अणु
		.name = "cr50_i2c",
		.pm = &cr50_i2c_pm,
		.acpi_match_table = ACPI_PTR(cr50_i2c_acpi_id),
		.of_match_table = of_match_ptr(of_cr50_i2c_match),
	पूर्ण,
पूर्ण;

module_i2c_driver(cr50_i2c_driver);

MODULE_DESCRIPTION("cr50 TPM I2C Driver");
MODULE_LICENSE("GPL");
