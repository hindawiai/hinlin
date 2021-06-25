<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012,2013 Infineon Technologies
 *
 * Authors:
 * Peter Huewe <peter.huewe@infineon.com>
 *
 * Device driver क्रम TCG/TCPA TPM (trusted platक्रमm module).
 * Specअगरications at www.trustedcomputinggroup.org
 *
 * This device driver implements the TPM पूर्णांकerface as defined in
 * the TCG TPM Interface Spec version 1.2, revision 1.0 and the
 * Infineon I2C Protocol Stack Specअगरication v0.20.
 *
 * It is based on the original tpm_tis device driver from Leendert van
 * Dorn and Kyleen Hall.
 */
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/रुको.h>
#समावेश "tpm.h"

#घोषणा TPM_I2C_INFINEON_बफ_मानE 1260

/* max. number of iterations after I2C NAK */
#घोषणा MAX_COUNT 3

#घोषणा SLEEP_DURATION_LOW 55
#घोषणा SLEEP_DURATION_HI 65

/* max. number of iterations after I2C NAK क्रम 'long' commands
 * we need this especially क्रम sending TPM_READY, since the cleanup after the
 * transtion to the पढ़ोy state may take some समय, but it is unpredictable
 * how दीर्घ it will take.
 */
#घोषणा MAX_COUNT_LONG 50

#घोषणा SLEEP_DURATION_LONG_LOW 200
#घोषणा SLEEP_DURATION_LONG_HI 220

/* After sending TPM_READY to 'reset' the TPM we have to sleep even दीर्घer */
#घोषणा SLEEP_DURATION_RESET_LOW 2400
#घोषणा SLEEP_DURATION_RESET_HI 2600

/* we want to use usleep_range instead of msleep क्रम the 5ms TPM_TIMEOUT */
#घोषणा TPM_TIMEOUT_US_LOW (TPM_TIMEOUT * 1000)
#घोषणा TPM_TIMEOUT_US_HI  (TPM_TIMEOUT_US_LOW + 2000)

/* expected value क्रम DIDVID रेजिस्टर */
#घोषणा TPM_TIS_I2C_DID_VID_9635 0xd1150b00L
#घोषणा TPM_TIS_I2C_DID_VID_9645 0x001a15d1L

क्रमागत i2c_chip_type अणु
	SLB9635,
	SLB9645,
	UNKNOWN,
पूर्ण;

काष्ठा tpm_inf_dev अणु
	काष्ठा i2c_client *client;
	पूर्णांक locality;
	/* In addition to the data itself, the buffer must fit the 7-bit I2C
	 * address and the direction bit.
	 */
	u8 buf[TPM_I2C_INFINEON_बफ_मानE + 1];
	काष्ठा tpm_chip *chip;
	क्रमागत i2c_chip_type chip_type;
	अचिन्हित पूर्णांक adapterlimit;
पूर्ण;

अटल काष्ठा tpm_inf_dev tpm_dev;

/*
 * iic_tpm_पढ़ो() - पढ़ो from TPM रेजिस्टर
 * @addr: रेजिस्टर address to पढ़ो from
 * @buffer: provided by caller
 * @len: number of bytes to पढ़ो
 *
 * Read len bytes from TPM रेजिस्टर and put them पूर्णांकo
 * buffer (little-endian क्रमmat, i.e. first byte is put पूर्णांकo buffer[0]).
 *
 * NOTE: TPM is big-endian क्रम multi-byte values. Multi-byte
 * values have to be swapped.
 *
 * NOTE: We can't unक्रमtunately use the combined पढ़ो/ग_लिखो functions
 * provided by the i2c core as the TPM currently करोes not support the
 * repeated start condition and due to it's special requirements.
 * The i2c_smbus* functions करो not work क्रम this chip.
 *
 * Return -EIO on error, 0 on success.
 */
अटल पूर्णांक iic_tpm_पढ़ो(u8 addr, u8 *buffer, माप_प्रकार len)
अणु

	काष्ठा i2c_msg msg1 = अणु
		.addr = tpm_dev.client->addr,
		.len = 1,
		.buf = &addr
	पूर्ण;
	काष्ठा i2c_msg msg2 = अणु
		.addr = tpm_dev.client->addr,
		.flags = I2C_M_RD,
		.len = len,
		.buf = buffer
	पूर्ण;
	काष्ठा i2c_msg msgs[] = अणुmsg1, msg2पूर्ण;

	पूर्णांक rc = 0;
	पूर्णांक count;
	अचिन्हित पूर्णांक msglen = len;

	/* Lock the adapter क्रम the duration of the whole sequence. */
	अगर (!tpm_dev.client->adapter->algo->master_xfer)
		वापस -EOPNOTSUPP;
	i2c_lock_bus(tpm_dev.client->adapter, I2C_LOCK_SEGMENT);

	अगर (tpm_dev.chip_type == SLB9645) अणु
		/* use a combined पढ़ो क्रम newer chips
		 * unक्रमtunately the smbus functions are not suitable due to
		 * the 32 byte limit of the smbus.
		 * retries should usually not be needed, but are kept just to
		 * be on the safe side.
		 */
		क्रम (count = 0; count < MAX_COUNT; count++) अणु
			rc = __i2c_transfer(tpm_dev.client->adapter, msgs, 2);
			अगर (rc > 0)
				अवरोध;	/* अवरोध here to skip sleep */
			usleep_range(SLEEP_DURATION_LOW, SLEEP_DURATION_HI);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Expect to send one command message and one data message, but
		 * support looping over each or both अगर necessary.
		 */
		जबतक (len > 0) अणु
			/* slb9635 protocol should work in all हालs */
			क्रम (count = 0; count < MAX_COUNT; count++) अणु
				rc = __i2c_transfer(tpm_dev.client->adapter,
						    &msg1, 1);
				अगर (rc > 0)
					अवरोध;	/* अवरोध here to skip sleep */

				usleep_range(SLEEP_DURATION_LOW,
					     SLEEP_DURATION_HI);
			पूर्ण

			अगर (rc <= 0)
				जाओ out;

			/* After the TPM has successfully received the रेजिस्टर
			 * address it needs some समय, thus we're sleeping here
			 * again, beक्रमe retrieving the data
			 */
			क्रम (count = 0; count < MAX_COUNT; count++) अणु
				अगर (tpm_dev.adapterlimit) अणु
					msglen = min_t(अचिन्हित पूर्णांक,
						       tpm_dev.adapterlimit,
						       len);
					msg2.len = msglen;
				पूर्ण
				usleep_range(SLEEP_DURATION_LOW,
					     SLEEP_DURATION_HI);
				rc = __i2c_transfer(tpm_dev.client->adapter,
						    &msg2, 1);
				अगर (rc > 0) अणु
					/* Since len is अचिन्हित, make करोubly
					 * sure we करो not underflow it.
					 */
					अगर (msglen > len)
						len = 0;
					अन्यथा
						len -= msglen;
					msg2.buf += msglen;
					अवरोध;
				पूर्ण
				/* If the I2C adapter rejected the request (e.g
				 * when the quirk पढ़ो_max_len < len) fall back
				 * to a sane minimum value and try again.
				 */
				अगर (rc == -EOPNOTSUPP)
					tpm_dev.adapterlimit =
							I2C_SMBUS_BLOCK_MAX;
			पूर्ण

			अगर (rc <= 0)
				जाओ out;
		पूर्ण
	पूर्ण

out:
	i2c_unlock_bus(tpm_dev.client->adapter, I2C_LOCK_SEGMENT);
	/* take care of 'guard time' */
	usleep_range(SLEEP_DURATION_LOW, SLEEP_DURATION_HI);

	/* __i2c_transfer वापसs the number of successfully transferred
	 * messages.
	 * So rc should be greater than 0 here otherwise we have an error.
	 */
	अगर (rc <= 0)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक iic_tpm_ग_लिखो_generic(u8 addr, u8 *buffer, माप_प्रकार len,
				 अचिन्हित पूर्णांक sleep_low,
				 अचिन्हित पूर्णांक sleep_hi, u8 max_count)
अणु
	पूर्णांक rc = -EIO;
	पूर्णांक count;

	काष्ठा i2c_msg msg1 = अणु
		.addr = tpm_dev.client->addr,
		.len = len + 1,
		.buf = tpm_dev.buf
	पूर्ण;

	अगर (len > TPM_I2C_INFINEON_बफ_मानE)
		वापस -EINVAL;

	अगर (!tpm_dev.client->adapter->algo->master_xfer)
		वापस -EOPNOTSUPP;
	i2c_lock_bus(tpm_dev.client->adapter, I2C_LOCK_SEGMENT);

	/* prepend the 'register address' to the buffer */
	tpm_dev.buf[0] = addr;
	स_नकल(&(tpm_dev.buf[1]), buffer, len);

	/*
	 * NOTE: We have to use these special mechanisms here and unक्रमtunately
	 * cannot rely on the standard behavior of i2c_transfer.
	 * Even क्रम newer chips the smbus functions are not
	 * suitable due to the 32 byte limit of the smbus.
	 */
	क्रम (count = 0; count < max_count; count++) अणु
		rc = __i2c_transfer(tpm_dev.client->adapter, &msg1, 1);
		अगर (rc > 0)
			अवरोध;
		usleep_range(sleep_low, sleep_hi);
	पूर्ण

	i2c_unlock_bus(tpm_dev.client->adapter, I2C_LOCK_SEGMENT);
	/* take care of 'guard time' */
	usleep_range(SLEEP_DURATION_LOW, SLEEP_DURATION_HI);

	/* __i2c_transfer वापसs the number of successfully transferred
	 * messages.
	 * So rc should be greater than 0 here otherwise we have an error.
	 */
	अगर (rc <= 0)
		वापस -EIO;

	वापस 0;
पूर्ण

/*
 * iic_tpm_ग_लिखो() - ग_लिखो to TPM रेजिस्टर
 * @addr: रेजिस्टर address to ग_लिखो to
 * @buffer: containing data to be written
 * @len: number of bytes to ग_लिखो
 *
 * Write len bytes from provided buffer to TPM रेजिस्टर (little
 * endian क्रमmat, i.e. buffer[0] is written as first byte).
 *
 * NOTE: TPM is big-endian क्रम multi-byte values. Multi-byte
 * values have to be swapped.
 *
 * NOTE: use this function instead of the iic_tpm_ग_लिखो_generic function.
 *
 * Return -EIO on error, 0 on success
 */
अटल पूर्णांक iic_tpm_ग_लिखो(u8 addr, u8 *buffer, माप_प्रकार len)
अणु
	वापस iic_tpm_ग_लिखो_generic(addr, buffer, len, SLEEP_DURATION_LOW,
				     SLEEP_DURATION_HI, MAX_COUNT);
पूर्ण

/*
 * This function is needed especially क्रम the cleanup situation after
 * sending TPM_READY
 * */
अटल पूर्णांक iic_tpm_ग_लिखो_दीर्घ(u8 addr, u8 *buffer, माप_प्रकार len)
अणु
	वापस iic_tpm_ग_लिखो_generic(addr, buffer, len, SLEEP_DURATION_LONG_LOW,
				     SLEEP_DURATION_LONG_HI, MAX_COUNT_LONG);
पूर्ण

क्रमागत tis_access अणु
	TPM_ACCESS_VALID = 0x80,
	TPM_ACCESS_ACTIVE_LOCALITY = 0x20,
	TPM_ACCESS_REQUEST_PENDING = 0x04,
	TPM_ACCESS_REQUEST_USE = 0x02,
पूर्ण;

क्रमागत tis_status अणु
	TPM_STS_VALID = 0x80,
	TPM_STS_COMMAND_READY = 0x40,
	TPM_STS_GO = 0x20,
	TPM_STS_DATA_AVAIL = 0x10,
	TPM_STS_DATA_EXPECT = 0x08,
पूर्ण;

क्रमागत tis_शेषs अणु
	TIS_SHORT_TIMEOUT = 750,	/* ms */
	TIS_LONG_TIMEOUT = 2000,	/* 2 sec */
पूर्ण;

#घोषणा	TPM_ACCESS(l)			(0x0000 | ((l) << 4))
#घोषणा	TPM_STS(l)			(0x0001 | ((l) << 4))
#घोषणा	TPM_DATA_FIFO(l)		(0x0005 | ((l) << 4))
#घोषणा	TPM_DID_VID(l)			(0x0006 | ((l) << 4))

अटल bool check_locality(काष्ठा tpm_chip *chip, पूर्णांक loc)
अणु
	u8 buf;
	पूर्णांक rc;

	rc = iic_tpm_पढ़ो(TPM_ACCESS(loc), &buf, 1);
	अगर (rc < 0)
		वापस false;

	अगर ((buf & (TPM_ACCESS_ACTIVE_LOCALITY | TPM_ACCESS_VALID)) ==
	    (TPM_ACCESS_ACTIVE_LOCALITY | TPM_ACCESS_VALID)) अणु
		tpm_dev.locality = loc;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* implementation similar to tpm_tis */
अटल व्योम release_locality(काष्ठा tpm_chip *chip, पूर्णांक loc, पूर्णांक क्रमce)
अणु
	u8 buf;
	अगर (iic_tpm_पढ़ो(TPM_ACCESS(loc), &buf, 1) < 0)
		वापस;

	अगर (क्रमce || (buf & (TPM_ACCESS_REQUEST_PENDING | TPM_ACCESS_VALID)) ==
	    (TPM_ACCESS_REQUEST_PENDING | TPM_ACCESS_VALID)) अणु
		buf = TPM_ACCESS_ACTIVE_LOCALITY;
		iic_tpm_ग_लिखो(TPM_ACCESS(loc), &buf, 1);
	पूर्ण
पूर्ण

अटल पूर्णांक request_locality(काष्ठा tpm_chip *chip, पूर्णांक loc)
अणु
	अचिन्हित दीर्घ stop;
	u8 buf = TPM_ACCESS_REQUEST_USE;

	अगर (check_locality(chip, loc))
		वापस loc;

	iic_tpm_ग_लिखो(TPM_ACCESS(loc), &buf, 1);

	/* रुको क्रम burstcount */
	stop = jअगरfies + chip->समयout_a;
	करो अणु
		अगर (check_locality(chip, loc))
			वापस loc;
		usleep_range(TPM_TIMEOUT_US_LOW, TPM_TIMEOUT_US_HI);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, stop));

	वापस -ETIME;
पूर्ण

अटल u8 tpm_tis_i2c_status(काष्ठा tpm_chip *chip)
अणु
	/* NOTE: since I2C पढ़ो may fail, वापस 0 in this हाल --> समय-out */
	u8 buf = 0xFF;
	u8 i = 0;

	करो अणु
		अगर (iic_tpm_पढ़ो(TPM_STS(tpm_dev.locality), &buf, 1) < 0)
			वापस 0;

		i++;
	/* अगर locallity is set STS should not be 0xFF */
	पूर्ण जबतक ((buf == 0xFF) && i < 10);

	वापस buf;
पूर्ण

अटल व्योम tpm_tis_i2c_पढ़ोy(काष्ठा tpm_chip *chip)
अणु
	/* this causes the current command to be पातed */
	u8 buf = TPM_STS_COMMAND_READY;
	iic_tpm_ग_लिखो_दीर्घ(TPM_STS(tpm_dev.locality), &buf, 1);
पूर्ण

अटल sमाप_प्रकार get_burstcount(काष्ठा tpm_chip *chip)
अणु
	अचिन्हित दीर्घ stop;
	sमाप_प्रकार burstcnt;
	u8 buf[3];

	/* रुको क्रम burstcount */
	/* which समयout value, spec has 2 answers (c & d) */
	stop = jअगरfies + chip->समयout_d;
	करो अणु
		/* Note: STS is little endian */
		अगर (iic_tpm_पढ़ो(TPM_STS(tpm_dev.locality)+1, buf, 3) < 0)
			burstcnt = 0;
		अन्यथा
			burstcnt = (buf[2] << 16) + (buf[1] << 8) + buf[0];

		अगर (burstcnt)
			वापस burstcnt;

		usleep_range(TPM_TIMEOUT_US_LOW, TPM_TIMEOUT_US_HI);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, stop));
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक रुको_क्रम_stat(काष्ठा tpm_chip *chip, u8 mask, अचिन्हित दीर्घ समयout,
			 पूर्णांक *status)
अणु
	अचिन्हित दीर्घ stop;

	/* check current status */
	*status = tpm_tis_i2c_status(chip);
	अगर ((*status != 0xFF) && (*status & mask) == mask)
		वापस 0;

	stop = jअगरfies + समयout;
	करो अणु
		/* since we just checked the status, give the TPM some समय */
		usleep_range(TPM_TIMEOUT_US_LOW, TPM_TIMEOUT_US_HI);
		*status = tpm_tis_i2c_status(chip);
		अगर ((*status & mask) == mask)
			वापस 0;

	पूर्ण जबतक (समय_beक्रमe(jअगरfies, stop));

	वापस -ETIME;
पूर्ण

अटल पूर्णांक recv_data(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार count)
अणु
	माप_प्रकार size = 0;
	sमाप_प्रकार burstcnt;
	u8 retries = 0;
	पूर्णांक rc;

	जबतक (size < count) अणु
		burstcnt = get_burstcount(chip);

		/* burstcnt < 0 = TPM is busy */
		अगर (burstcnt < 0)
			वापस burstcnt;

		/* limit received data to max. left */
		अगर (burstcnt > (count - size))
			burstcnt = count - size;

		rc = iic_tpm_पढ़ो(TPM_DATA_FIFO(tpm_dev.locality),
				  &(buf[size]), burstcnt);
		अगर (rc == 0)
			size += burstcnt;
		अन्यथा अगर (rc < 0)
			retries++;

		/* aव्योम endless loop in हाल of broken HW */
		अगर (retries > MAX_COUNT_LONG)
			वापस -EIO;
	पूर्ण
	वापस size;
पूर्ण

अटल पूर्णांक tpm_tis_i2c_recv(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार count)
अणु
	पूर्णांक size = 0;
	पूर्णांक status;
	u32 expected;

	अगर (count < TPM_HEADER_SIZE) अणु
		size = -EIO;
		जाओ out;
	पूर्ण

	/* पढ़ो first 10 bytes, including tag, paramsize, and result */
	size = recv_data(chip, buf, TPM_HEADER_SIZE);
	अगर (size < TPM_HEADER_SIZE) अणु
		dev_err(&chip->dev, "Unable to read header\n");
		जाओ out;
	पूर्ण

	expected = be32_to_cpu(*(__be32 *)(buf + 2));
	अगर (((माप_प्रकार) expected > count) || (expected < TPM_HEADER_SIZE)) अणु
		size = -EIO;
		जाओ out;
	पूर्ण

	size += recv_data(chip, &buf[TPM_HEADER_SIZE],
			  expected - TPM_HEADER_SIZE);
	अगर (size < expected) अणु
		dev_err(&chip->dev, "Unable to read remainder of result\n");
		size = -ETIME;
		जाओ out;
	पूर्ण

	रुको_क्रम_stat(chip, TPM_STS_VALID, chip->समयout_c, &status);
	अगर (status & TPM_STS_DATA_AVAIL) अणु	/* retry? */
		dev_err(&chip->dev, "Error left over data\n");
		size = -EIO;
		जाओ out;
	पूर्ण

out:
	tpm_tis_i2c_पढ़ोy(chip);
	/* The TPM needs some समय to clean up here,
	 * so we sleep rather than keeping the bus busy
	 */
	usleep_range(SLEEP_DURATION_RESET_LOW, SLEEP_DURATION_RESET_HI);
	release_locality(chip, tpm_dev.locality, 0);
	वापस size;
पूर्ण

अटल पूर्णांक tpm_tis_i2c_send(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार len)
अणु
	पूर्णांक rc, status;
	sमाप_प्रकार burstcnt;
	माप_प्रकार count = 0;
	u8 retries = 0;
	u8 sts = TPM_STS_GO;

	अगर (len > TPM_I2C_INFINEON_बफ_मानE)
		वापस -E2BIG;

	अगर (request_locality(chip, 0) < 0)
		वापस -EBUSY;

	status = tpm_tis_i2c_status(chip);
	अगर ((status & TPM_STS_COMMAND_READY) == 0) अणु
		tpm_tis_i2c_पढ़ोy(chip);
		अगर (रुको_क्रम_stat
		    (chip, TPM_STS_COMMAND_READY,
		     chip->समयout_b, &status) < 0) अणु
			rc = -ETIME;
			जाओ out_err;
		पूर्ण
	पूर्ण

	जबतक (count < len - 1) अणु
		burstcnt = get_burstcount(chip);

		/* burstcnt < 0 = TPM is busy */
		अगर (burstcnt < 0)
			वापस burstcnt;

		अगर (burstcnt > (len - 1 - count))
			burstcnt = len - 1 - count;

		rc = iic_tpm_ग_लिखो(TPM_DATA_FIFO(tpm_dev.locality),
				   &(buf[count]), burstcnt);
		अगर (rc == 0)
			count += burstcnt;
		अन्यथा अगर (rc < 0)
			retries++;

		/* aव्योम endless loop in हाल of broken HW */
		अगर (retries > MAX_COUNT_LONG) अणु
			rc = -EIO;
			जाओ out_err;
		पूर्ण

		रुको_क्रम_stat(chip, TPM_STS_VALID,
			      chip->समयout_c, &status);

		अगर ((status & TPM_STS_DATA_EXPECT) == 0) अणु
			rc = -EIO;
			जाओ out_err;
		पूर्ण
	पूर्ण

	/* ग_लिखो last byte */
	iic_tpm_ग_लिखो(TPM_DATA_FIFO(tpm_dev.locality), &(buf[count]), 1);
	रुको_क्रम_stat(chip, TPM_STS_VALID, chip->समयout_c, &status);
	अगर ((status & TPM_STS_DATA_EXPECT) != 0) अणु
		rc = -EIO;
		जाओ out_err;
	पूर्ण

	/* go and करो it */
	iic_tpm_ग_लिखो(TPM_STS(tpm_dev.locality), &sts, 1);

	वापस 0;
out_err:
	tpm_tis_i2c_पढ़ोy(chip);
	/* The TPM needs some समय to clean up here,
	 * so we sleep rather than keeping the bus busy
	 */
	usleep_range(SLEEP_DURATION_RESET_LOW, SLEEP_DURATION_RESET_HI);
	release_locality(chip, tpm_dev.locality, 0);
	वापस rc;
पूर्ण

अटल bool tpm_tis_i2c_req_canceled(काष्ठा tpm_chip *chip, u8 status)
अणु
	वापस (status == TPM_STS_COMMAND_READY);
पूर्ण

अटल स्थिर काष्ठा tpm_class_ops tpm_tis_i2c = अणु
	.flags = TPM_OPS_AUTO_STARTUP,
	.status = tpm_tis_i2c_status,
	.recv = tpm_tis_i2c_recv,
	.send = tpm_tis_i2c_send,
	.cancel = tpm_tis_i2c_पढ़ोy,
	.req_complete_mask = TPM_STS_DATA_AVAIL | TPM_STS_VALID,
	.req_complete_val = TPM_STS_DATA_AVAIL | TPM_STS_VALID,
	.req_canceled = tpm_tis_i2c_req_canceled,
पूर्ण;

अटल पूर्णांक tpm_tis_i2c_init(काष्ठा device *dev)
अणु
	u32 venकरोr;
	पूर्णांक rc = 0;
	काष्ठा tpm_chip *chip;

	chip = tpmm_chip_alloc(dev, &tpm_tis_i2c);
	अगर (IS_ERR(chip))
		वापस PTR_ERR(chip);

	/* Default समयouts */
	chip->समयout_a = msecs_to_jअगरfies(TIS_SHORT_TIMEOUT);
	chip->समयout_b = msecs_to_jअगरfies(TIS_LONG_TIMEOUT);
	chip->समयout_c = msecs_to_jअगरfies(TIS_SHORT_TIMEOUT);
	chip->समयout_d = msecs_to_jअगरfies(TIS_SHORT_TIMEOUT);

	अगर (request_locality(chip, 0) != 0) अणु
		dev_err(dev, "could not request locality\n");
		rc = -ENODEV;
		जाओ out_err;
	पूर्ण

	/* पढ़ो four bytes from DID_VID रेजिस्टर */
	अगर (iic_tpm_पढ़ो(TPM_DID_VID(0), (u8 *)&venकरोr, 4) < 0) अणु
		dev_err(dev, "could not read vendor id\n");
		rc = -EIO;
		जाओ out_release;
	पूर्ण

	अगर (venकरोr == TPM_TIS_I2C_DID_VID_9645) अणु
		tpm_dev.chip_type = SLB9645;
	पूर्ण अन्यथा अगर (venकरोr == TPM_TIS_I2C_DID_VID_9635) अणु
		tpm_dev.chip_type = SLB9635;
	पूर्ण अन्यथा अणु
		dev_err(dev, "vendor id did not match! ID was %08x\n", venकरोr);
		rc = -ENODEV;
		जाओ out_release;
	पूर्ण

	dev_info(dev, "1.2 TPM (device-id 0x%X)\n", venकरोr >> 16);

	tpm_dev.chip = chip;

	वापस tpm_chip_रेजिस्टर(chip);
out_release:
	release_locality(chip, tpm_dev.locality, 1);
	tpm_dev.client = शून्य;
out_err:
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tpm_tis_i2c_table[] = अणु
	अणु"tpm_i2c_infineon"पूर्ण,
	अणु"slb9635tt"पूर्ण,
	अणु"slb9645tt"पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, tpm_tis_i2c_table);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id tpm_tis_i2c_of_match[] = अणु
	अणु.compatible = "infineon,tpm_i2c_infineon"पूर्ण,
	अणु.compatible = "infineon,slb9635tt"पूर्ण,
	अणु.compatible = "infineon,slb9645tt"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tpm_tis_i2c_of_match);
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(tpm_tis_i2c_ops, tpm_pm_suspend, tpm_pm_resume);

अटल पूर्णांक tpm_tis_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक rc;
	काष्ठा device *dev = &(client->dev);

	अगर (tpm_dev.client != शून्य) अणु
		dev_err(dev, "This driver only supports one client at a time\n");
		वापस -EBUSY;	/* We only support one client */
	पूर्ण

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(dev, "no algorithms associated to the i2c bus\n");
		वापस -ENODEV;
	पूर्ण

	tpm_dev.client = client;
	rc = tpm_tis_i2c_init(&client->dev);
	अगर (rc != 0) अणु
		tpm_dev.client = शून्य;
		rc = -ENODEV;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक tpm_tis_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tpm_chip *chip = tpm_dev.chip;

	tpm_chip_unरेजिस्टर(chip);
	release_locality(chip, tpm_dev.locality, 1);
	tpm_dev.client = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver tpm_tis_i2c_driver = अणु
	.id_table = tpm_tis_i2c_table,
	.probe = tpm_tis_i2c_probe,
	.हटाओ = tpm_tis_i2c_हटाओ,
	.driver = अणु
		   .name = "tpm_i2c_infineon",
		   .pm = &tpm_tis_i2c_ops,
		   .of_match_table = of_match_ptr(tpm_tis_i2c_of_match),
		   पूर्ण,
पूर्ण;

module_i2c_driver(tpm_tis_i2c_driver);
MODULE_AUTHOR("Peter Huewe <peter.huewe@infineon.com>");
MODULE_DESCRIPTION("TPM TIS I2C Infineon Driver");
MODULE_VERSION("2.2.0");
MODULE_LICENSE("GPL");
