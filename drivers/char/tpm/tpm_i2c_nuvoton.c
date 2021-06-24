<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
 /******************************************************************************
 * Nuvoton TPM I2C Device Driver Interface क्रम WPCT301/NPCT501/NPCT6XX,
 * based on the TCG TPM Interface Spec version 1.2.
 * Specअगरications at www.trustedcomputinggroup.org
 *
 * Copyright (C) 2011, Nuvoton Technology Corporation.
 *  Dan Morav <dan.morav@nuvoton.com>
 * Copyright (C) 2013, Obsidian Research Corp.
 *  Jason Gunthorpe <jgunthorpe@obsidianresearch.com>
 *
 * Nuvoton contact inक्रमmation: APC.Support@nuvoton.com
 *****************************************************************************/

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/रुको.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of_device.h>
#समावेश "tpm.h"

/* I2C पूर्णांकerface offsets */
#घोषणा TPM_STS			0x00
#घोषणा TPM_BURST_COUNT		0x01
#घोषणा TPM_DATA_FIFO_W		0x20
#घोषणा TPM_DATA_FIFO_R		0x40
#घोषणा TPM_VID_DID_RID		0x60
#घोषणा TPM_I2C_RETRIES		5
/*
 * I2C bus device maximum buffer size w/o counting I2C address or command
 * i.e. max size required क्रम I2C ग_लिखो is 34 = addr, command, 32 bytes data
 */
#घोषणा TPM_I2C_MAX_BUF_SIZE           32
#घोषणा TPM_I2C_RETRY_COUNT            32
#घोषणा TPM_I2C_BUS_DELAY              1000      	/* usec */
#घोषणा TPM_I2C_RETRY_DELAY_SHORT      (2 * 1000)	/* usec */
#घोषणा TPM_I2C_RETRY_DELAY_LONG       (10 * 1000) 	/* usec */
#घोषणा TPM_I2C_DELAY_RANGE            300		/* usec */

#घोषणा OF_IS_TPM2 ((व्योम *)1)
#घोषणा I2C_IS_TPM2 1

काष्ठा priv_data अणु
	पूर्णांक irq;
	अचिन्हित पूर्णांक पूर्णांकrs;
	रुको_queue_head_t पढ़ो_queue;
पूर्ण;

अटल s32 i2c_nuvoton_पढ़ो_buf(काष्ठा i2c_client *client, u8 offset, u8 size,
				u8 *data)
अणु
	s32 status;

	status = i2c_smbus_पढ़ो_i2c_block_data(client, offset, size, data);
	dev_dbg(&client->dev,
		"%s(offset=%u size=%u data=%*ph) -> sts=%d\n", __func__,
		offset, size, (पूर्णांक)size, data, status);
	वापस status;
पूर्ण

अटल s32 i2c_nuvoton_ग_लिखो_buf(काष्ठा i2c_client *client, u8 offset, u8 size,
				 u8 *data)
अणु
	s32 status;

	status = i2c_smbus_ग_लिखो_i2c_block_data(client, offset, size, data);
	dev_dbg(&client->dev,
		"%s(offset=%u size=%u data=%*ph) -> sts=%d\n", __func__,
		offset, size, (पूर्णांक)size, data, status);
	वापस status;
पूर्ण

#घोषणा TPM_STS_VALID          0x80
#घोषणा TPM_STS_COMMAND_READY  0x40
#घोषणा TPM_STS_GO             0x20
#घोषणा TPM_STS_DATA_AVAIL     0x10
#घोषणा TPM_STS_EXPECT         0x08
#घोषणा TPM_STS_RESPONSE_RETRY 0x02
#घोषणा TPM_STS_ERR_VAL        0x07    /* bit2...bit0 पढ़ोs always 0 */

#घोषणा TPM_I2C_SHORT_TIMEOUT  750     /* ms */
#घोषणा TPM_I2C_LONG_TIMEOUT   2000    /* 2 sec */

/* पढ़ो TPM_STS रेजिस्टर */
अटल u8 i2c_nuvoton_पढ़ो_status(काष्ठा tpm_chip *chip)
अणु
	काष्ठा i2c_client *client = to_i2c_client(chip->dev.parent);
	s32 status;
	u8 data;

	status = i2c_nuvoton_पढ़ो_buf(client, TPM_STS, 1, &data);
	अगर (status <= 0) अणु
		dev_err(&chip->dev, "%s() error return %d\n", __func__,
			status);
		data = TPM_STS_ERR_VAL;
	पूर्ण

	वापस data;
पूर्ण

/* ग_लिखो byte to TPM_STS रेजिस्टर */
अटल s32 i2c_nuvoton_ग_लिखो_status(काष्ठा i2c_client *client, u8 data)
अणु
	s32 status;
	पूर्णांक i;

	/* this causes the current command to be पातed */
	क्रम (i = 0, status = -1; i < TPM_I2C_RETRY_COUNT && status < 0; i++) अणु
		status = i2c_nuvoton_ग_लिखो_buf(client, TPM_STS, 1, &data);
		अगर (status < 0)
			usleep_range(TPM_I2C_BUS_DELAY, TPM_I2C_BUS_DELAY
				     + TPM_I2C_DELAY_RANGE);
	पूर्ण
	वापस status;
पूर्ण

/* ग_लिखो commandReady to TPM_STS रेजिस्टर */
अटल व्योम i2c_nuvoton_पढ़ोy(काष्ठा tpm_chip *chip)
अणु
	काष्ठा i2c_client *client = to_i2c_client(chip->dev.parent);
	s32 status;

	/* this causes the current command to be पातed */
	status = i2c_nuvoton_ग_लिखो_status(client, TPM_STS_COMMAND_READY);
	अगर (status < 0)
		dev_err(&chip->dev,
			"%s() fail to write TPM_STS.commandReady\n", __func__);
पूर्ण

/* पढ़ो burstCount field from TPM_STS रेजिस्टर
 * वापस -1 on fail to पढ़ो */
अटल पूर्णांक i2c_nuvoton_get_burstcount(काष्ठा i2c_client *client,
				      काष्ठा tpm_chip *chip)
अणु
	अचिन्हित दीर्घ stop = jअगरfies + chip->समयout_d;
	s32 status;
	पूर्णांक burst_count = -1;
	u8 data;

	/* रुको क्रम burstcount to be non-zero */
	करो अणु
		/* in I2C burstCount is 1 byte */
		status = i2c_nuvoton_पढ़ो_buf(client, TPM_BURST_COUNT, 1,
					      &data);
		अगर (status > 0 && data > 0) अणु
			burst_count = min_t(u8, TPM_I2C_MAX_BUF_SIZE, data);
			अवरोध;
		पूर्ण
		usleep_range(TPM_I2C_BUS_DELAY, TPM_I2C_BUS_DELAY
			     + TPM_I2C_DELAY_RANGE);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, stop));

	वापस burst_count;
पूर्ण

/*
 * WPCT301/NPCT501/NPCT6XX SINT# supports only dataAvail
 * any call to this function which is not रुकोing क्रम dataAvail will
 * set queue to शून्य to aव्योम रुकोing क्रम पूर्णांकerrupt
 */
अटल bool i2c_nuvoton_check_status(काष्ठा tpm_chip *chip, u8 mask, u8 value)
अणु
	u8 status = i2c_nuvoton_पढ़ो_status(chip);
	वापस (status != TPM_STS_ERR_VAL) && ((status & mask) == value);
पूर्ण

अटल पूर्णांक i2c_nuvoton_रुको_क्रम_stat(काष्ठा tpm_chip *chip, u8 mask, u8 value,
				     u32 समयout, रुको_queue_head_t *queue)
अणु
	अगर ((chip->flags & TPM_CHIP_FLAG_IRQ) && queue) अणु
		s32 rc;
		काष्ठा priv_data *priv = dev_get_drvdata(&chip->dev);
		अचिन्हित पूर्णांक cur_पूर्णांकrs = priv->पूर्णांकrs;

		enable_irq(priv->irq);
		rc = रुको_event_पूर्णांकerruptible_समयout(*queue,
						      cur_पूर्णांकrs != priv->पूर्णांकrs,
						      समयout);
		अगर (rc > 0)
			वापस 0;
		/* At this poपूर्णांक we know that the SINT pin is निश्चितed, so we
		 * करो not need to करो i2c_nuvoton_check_status */
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ ten_msec, stop;
		bool status_valid;

		/* check current status */
		status_valid = i2c_nuvoton_check_status(chip, mask, value);
		अगर (status_valid)
			वापस 0;

		/* use polling to रुको क्रम the event */
		ten_msec = jअगरfies + usecs_to_jअगरfies(TPM_I2C_RETRY_DELAY_LONG);
		stop = jअगरfies + समयout;
		करो अणु
			अगर (समय_beक्रमe(jअगरfies, ten_msec))
				usleep_range(TPM_I2C_RETRY_DELAY_SHORT,
					     TPM_I2C_RETRY_DELAY_SHORT
					     + TPM_I2C_DELAY_RANGE);
			अन्यथा
				usleep_range(TPM_I2C_RETRY_DELAY_LONG,
					     TPM_I2C_RETRY_DELAY_LONG
					     + TPM_I2C_DELAY_RANGE);
			status_valid = i2c_nuvoton_check_status(chip, mask,
								value);
			अगर (status_valid)
				वापस 0;
		पूर्ण जबतक (समय_beक्रमe(jअगरfies, stop));
	पूर्ण
	dev_err(&chip->dev, "%s(%02x, %02x) -> timeout\n", __func__, mask,
		value);
	वापस -ETIMEDOUT;
पूर्ण

/* रुको क्रम dataAvail field to be set in the TPM_STS रेजिस्टर */
अटल पूर्णांक i2c_nuvoton_रुको_क्रम_data_avail(काष्ठा tpm_chip *chip, u32 समयout,
					   रुको_queue_head_t *queue)
अणु
	वापस i2c_nuvoton_रुको_क्रम_stat(chip,
					 TPM_STS_DATA_AVAIL | TPM_STS_VALID,
					 TPM_STS_DATA_AVAIL | TPM_STS_VALID,
					 समयout, queue);
पूर्ण

/* Read @count bytes पूर्णांकo @buf from TPM_RD_FIFO रेजिस्टर */
अटल पूर्णांक i2c_nuvoton_recv_data(काष्ठा i2c_client *client,
				 काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार count)
अणु
	काष्ठा priv_data *priv = dev_get_drvdata(&chip->dev);
	s32 rc;
	पूर्णांक burst_count, bytes2पढ़ो, size = 0;

	जबतक (size < count &&
	       i2c_nuvoton_रुको_क्रम_data_avail(chip,
					       chip->समयout_c,
					       &priv->पढ़ो_queue) == 0) अणु
		burst_count = i2c_nuvoton_get_burstcount(client, chip);
		अगर (burst_count < 0) अणु
			dev_err(&chip->dev,
				"%s() fail to read burstCount=%d\n", __func__,
				burst_count);
			वापस -EIO;
		पूर्ण
		bytes2पढ़ो = min_t(माप_प्रकार, burst_count, count - size);
		rc = i2c_nuvoton_पढ़ो_buf(client, TPM_DATA_FIFO_R,
					  bytes2पढ़ो, &buf[size]);
		अगर (rc < 0) अणु
			dev_err(&chip->dev,
				"%s() fail on i2c_nuvoton_read_buf()=%d\n",
				__func__, rc);
			वापस -EIO;
		पूर्ण
		dev_dbg(&chip->dev, "%s(%d):", __func__, bytes2पढ़ो);
		size += bytes2पढ़ो;
	पूर्ण

	वापस size;
पूर्ण

/* Read TPM command results */
अटल पूर्णांक i2c_nuvoton_recv(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार count)
अणु
	काष्ठा priv_data *priv = dev_get_drvdata(&chip->dev);
	काष्ठा device *dev = chip->dev.parent;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	s32 rc;
	पूर्णांक status;
	पूर्णांक burst_count;
	पूर्णांक retries;
	पूर्णांक size = 0;
	u32 expected;

	अगर (count < TPM_HEADER_SIZE) अणु
		i2c_nuvoton_पढ़ोy(chip);    /* वापस to idle */
		dev_err(dev, "%s() count < header size\n", __func__);
		वापस -EIO;
	पूर्ण
	क्रम (retries = 0; retries < TPM_I2C_RETRIES; retries++) अणु
		अगर (retries > 0) अणु
			/* अगर this is not the first trial, set responseRetry */
			i2c_nuvoton_ग_लिखो_status(client,
						 TPM_STS_RESPONSE_RETRY);
		पूर्ण
		/*
		 * पढ़ो first available (> 10 bytes), including:
		 * tag, paramsize, and result
		 */
		status = i2c_nuvoton_रुको_क्रम_data_avail(
			chip, chip->समयout_c, &priv->पढ़ो_queue);
		अगर (status != 0) अणु
			dev_err(dev, "%s() timeout on dataAvail\n", __func__);
			size = -ETIMEDOUT;
			जारी;
		पूर्ण
		burst_count = i2c_nuvoton_get_burstcount(client, chip);
		अगर (burst_count < 0) अणु
			dev_err(dev, "%s() fail to get burstCount\n", __func__);
			size = -EIO;
			जारी;
		पूर्ण
		size = i2c_nuvoton_recv_data(client, chip, buf,
					     burst_count);
		अगर (size < TPM_HEADER_SIZE) अणु
			dev_err(dev, "%s() fail to read header\n", __func__);
			size = -EIO;
			जारी;
		पूर्ण
		/*
		 * convert number of expected bytes field from big endian 32 bit
		 * to machine native
		 */
		expected = be32_to_cpu(*(__be32 *) (buf + 2));
		अगर (expected > count || expected < size) अणु
			dev_err(dev, "%s() expected > count\n", __func__);
			size = -EIO;
			जारी;
		पूर्ण
		rc = i2c_nuvoton_recv_data(client, chip, &buf[size],
					   expected - size);
		size += rc;
		अगर (rc < 0 || size < expected) अणु
			dev_err(dev, "%s() fail to read remainder of result\n",
				__func__);
			size = -EIO;
			जारी;
		पूर्ण
		अगर (i2c_nuvoton_रुको_क्रम_stat(
			    chip, TPM_STS_VALID | TPM_STS_DATA_AVAIL,
			    TPM_STS_VALID, chip->समयout_c,
			    शून्य)) अणु
			dev_err(dev, "%s() error left over data\n", __func__);
			size = -ETIMEDOUT;
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण
	i2c_nuvoton_पढ़ोy(chip);
	dev_dbg(&chip->dev, "%s() -> %d\n", __func__, size);
	वापस size;
पूर्ण

/*
 * Send TPM command.
 *
 * If पूर्णांकerrupts are used (संकेतed by an irq set in the venकरोr काष्ठाure)
 * tpm.c can skip polling क्रम the data to be available as the पूर्णांकerrupt is
 * रुकोed क्रम here
 */
अटल पूर्णांक i2c_nuvoton_send(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार len)
अणु
	काष्ठा priv_data *priv = dev_get_drvdata(&chip->dev);
	काष्ठा device *dev = chip->dev.parent;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	u32 ordinal;
	अचिन्हित दीर्घ duration;
	माप_प्रकार count = 0;
	पूर्णांक burst_count, bytes2ग_लिखो, retries, rc = -EIO;

	क्रम (retries = 0; retries < TPM_RETRY; retries++) अणु
		i2c_nuvoton_पढ़ोy(chip);
		अगर (i2c_nuvoton_रुको_क्रम_stat(chip, TPM_STS_COMMAND_READY,
					      TPM_STS_COMMAND_READY,
					      chip->समयout_b, शून्य)) अणु
			dev_err(dev, "%s() timeout on commandReady\n",
				__func__);
			rc = -EIO;
			जारी;
		पूर्ण
		rc = 0;
		जबतक (count < len - 1) अणु
			burst_count = i2c_nuvoton_get_burstcount(client,
								 chip);
			अगर (burst_count < 0) अणु
				dev_err(dev, "%s() fail get burstCount\n",
					__func__);
				rc = -EIO;
				अवरोध;
			पूर्ण
			bytes2ग_लिखो = min_t(माप_प्रकार, burst_count,
					    len - 1 - count);
			rc = i2c_nuvoton_ग_लिखो_buf(client, TPM_DATA_FIFO_W,
						   bytes2ग_लिखो, &buf[count]);
			अगर (rc < 0) अणु
				dev_err(dev, "%s() fail i2cWriteBuf\n",
					__func__);
				अवरोध;
			पूर्ण
			dev_dbg(dev, "%s(%d):", __func__, bytes2ग_लिखो);
			count += bytes2ग_लिखो;
			rc = i2c_nuvoton_रुको_क्रम_stat(chip,
						       TPM_STS_VALID |
						       TPM_STS_EXPECT,
						       TPM_STS_VALID |
						       TPM_STS_EXPECT,
						       chip->समयout_c,
						       शून्य);
			अगर (rc < 0) अणु
				dev_err(dev, "%s() timeout on Expect\n",
					__func__);
				rc = -ETIMEDOUT;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (rc < 0)
			जारी;

		/* ग_लिखो last byte */
		rc = i2c_nuvoton_ग_लिखो_buf(client, TPM_DATA_FIFO_W, 1,
					   &buf[count]);
		अगर (rc < 0) अणु
			dev_err(dev, "%s() fail to write last byte\n",
				__func__);
			rc = -EIO;
			जारी;
		पूर्ण
		dev_dbg(dev, "%s(last): %02x", __func__, buf[count]);
		rc = i2c_nuvoton_रुको_क्रम_stat(chip,
					       TPM_STS_VALID | TPM_STS_EXPECT,
					       TPM_STS_VALID,
					       chip->समयout_c, शून्य);
		अगर (rc) अणु
			dev_err(dev, "%s() timeout on Expect to clear\n",
				__func__);
			rc = -ETIMEDOUT;
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (rc < 0) अणु
		/* retries == TPM_RETRY */
		i2c_nuvoton_पढ़ोy(chip);
		वापस rc;
	पूर्ण
	/* execute the TPM command */
	rc = i2c_nuvoton_ग_लिखो_status(client, TPM_STS_GO);
	अगर (rc < 0) अणु
		dev_err(dev, "%s() fail to write Go\n", __func__);
		i2c_nuvoton_पढ़ोy(chip);
		वापस rc;
	पूर्ण
	ordinal = be32_to_cpu(*((__be32 *) (buf + 6)));
	duration = tpm_calc_ordinal_duration(chip, ordinal);

	rc = i2c_nuvoton_रुको_क्रम_data_avail(chip, duration, &priv->पढ़ो_queue);
	अगर (rc) अणु
		dev_err(dev, "%s() timeout command duration %ld\n",
			__func__, duration);
		i2c_nuvoton_पढ़ोy(chip);
		वापस rc;
	पूर्ण

	dev_dbg(dev, "%s() -> %zd\n", __func__, len);
	वापस 0;
पूर्ण

अटल bool i2c_nuvoton_req_canceled(काष्ठा tpm_chip *chip, u8 status)
अणु
	वापस (status == TPM_STS_COMMAND_READY);
पूर्ण

अटल स्थिर काष्ठा tpm_class_ops tpm_i2c = अणु
	.flags = TPM_OPS_AUTO_STARTUP,
	.status = i2c_nuvoton_पढ़ो_status,
	.recv = i2c_nuvoton_recv,
	.send = i2c_nuvoton_send,
	.cancel = i2c_nuvoton_पढ़ोy,
	.req_complete_mask = TPM_STS_DATA_AVAIL | TPM_STS_VALID,
	.req_complete_val = TPM_STS_DATA_AVAIL | TPM_STS_VALID,
	.req_canceled = i2c_nuvoton_req_canceled,
पूर्ण;

/* The only purpose क्रम the handler is to संकेत to any रुकोing thपढ़ोs that
 * the पूर्णांकerrupt is currently being निश्चितed. The driver करोes not करो any
 * processing triggered by पूर्णांकerrupts, and the chip provides no way to mask at
 * the source (plus that would be slow over I2C). Run the IRQ as a one-shot,
 * this means it cannot be shared. */
अटल irqवापस_t i2c_nuvoton_पूर्णांक_handler(पूर्णांक dummy, व्योम *dev_id)
अणु
	काष्ठा tpm_chip *chip = dev_id;
	काष्ठा priv_data *priv = dev_get_drvdata(&chip->dev);

	priv->पूर्णांकrs++;
	wake_up(&priv->पढ़ो_queue);
	disable_irq_nosync(priv->irq);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक get_vid(काष्ठा i2c_client *client, u32 *res)
अणु
	अटल स्थिर u8 vid_did_rid_value[] = अणु 0x50, 0x10, 0xfe पूर्ण;
	u32 temp;
	s32 rc;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;
	rc = i2c_nuvoton_पढ़ो_buf(client, TPM_VID_DID_RID, 4, (u8 *)&temp);
	अगर (rc < 0)
		वापस rc;

	/* check WPCT301 values - ignore RID */
	अगर (स_भेद(&temp, vid_did_rid_value, माप(vid_did_rid_value))) अणु
		/*
		 * f/w rev 2.81 has an issue where the VID_DID_RID is not
		 * reporting the right value. so give it another chance at
		 * offset 0x20 (FIFO_W).
		 */
		rc = i2c_nuvoton_पढ़ो_buf(client, TPM_DATA_FIFO_W, 4,
					  (u8 *) (&temp));
		अगर (rc < 0)
			वापस rc;

		/* check WPCT301 values - ignore RID */
		अगर (स_भेद(&temp, vid_did_rid_value,
			   माप(vid_did_rid_value)))
			वापस -ENODEV;
	पूर्ण

	*res = temp;
	वापस 0;
पूर्ण

अटल पूर्णांक i2c_nuvoton_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक rc;
	काष्ठा tpm_chip *chip;
	काष्ठा device *dev = &client->dev;
	काष्ठा priv_data *priv;
	u32 vid = 0;

	rc = get_vid(client, &vid);
	अगर (rc)
		वापस rc;

	dev_info(dev, "VID: %04X DID: %02X RID: %02X\n", (u16) vid,
		 (u8) (vid >> 16), (u8) (vid >> 24));

	chip = tpmm_chip_alloc(dev, &tpm_i2c);
	अगर (IS_ERR(chip))
		वापस PTR_ERR(chip);

	priv = devm_kzalloc(dev, माप(काष्ठा priv_data), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	अगर (dev->of_node) अणु
		स्थिर काष्ठा of_device_id *of_id;

		of_id = of_match_device(dev->driver->of_match_table, dev);
		अगर (of_id && of_id->data == OF_IS_TPM2)
			chip->flags |= TPM_CHIP_FLAG_TPM2;
	पूर्ण अन्यथा
		अगर (id->driver_data == I2C_IS_TPM2)
			chip->flags |= TPM_CHIP_FLAG_TPM2;

	init_रुकोqueue_head(&priv->पढ़ो_queue);

	/* Default समयouts */
	chip->समयout_a = msecs_to_jअगरfies(TPM_I2C_SHORT_TIMEOUT);
	chip->समयout_b = msecs_to_jअगरfies(TPM_I2C_LONG_TIMEOUT);
	chip->समयout_c = msecs_to_jअगरfies(TPM_I2C_SHORT_TIMEOUT);
	chip->समयout_d = msecs_to_jअगरfies(TPM_I2C_SHORT_TIMEOUT);

	dev_set_drvdata(&chip->dev, priv);

	/*
	 * I2C पूर्णांकfcaps (पूर्णांकerrupt capabilitieis) in the chip are hard coded to:
	 *   TPM_INTF_INT_LEVEL_LOW | TPM_INTF_DATA_AVAIL_INT
	 * The IRQ should be set in the i2c_board_info (which is करोne
	 * स्वतःmatically in of_i2c_रेजिस्टर_devices, क्रम device tree users */
	priv->irq = client->irq;
	अगर (client->irq) अणु
		dev_dbg(dev, "%s() priv->irq\n", __func__);
		rc = devm_request_irq(dev, client->irq,
				      i2c_nuvoton_पूर्णांक_handler,
				      IRQF_TRIGGER_LOW,
				      dev_name(&chip->dev),
				      chip);
		अगर (rc) अणु
			dev_err(dev, "%s() Unable to request irq: %d for use\n",
				__func__, priv->irq);
			priv->irq = 0;
		पूर्ण अन्यथा अणु
			chip->flags |= TPM_CHIP_FLAG_IRQ;
			/* Clear any pending पूर्णांकerrupt */
			i2c_nuvoton_पढ़ोy(chip);
			/* - रुको क्रम TPM_STS==0xA0 (stsValid, commandReady) */
			rc = i2c_nuvoton_रुको_क्रम_stat(chip,
						       TPM_STS_COMMAND_READY,
						       TPM_STS_COMMAND_READY,
						       chip->समयout_b,
						       शून्य);
			अगर (rc == 0) अणु
				/*
				 * TIS is in पढ़ोy state
				 * ग_लिखो dummy byte to enter reception state
				 * TPM_DATA_FIFO_W <- rc (0)
				 */
				rc = i2c_nuvoton_ग_लिखो_buf(client,
							   TPM_DATA_FIFO_W,
							   1, (u8 *) (&rc));
				अगर (rc < 0)
					वापस rc;
				/* TPM_STS <- 0x40 (commandReady) */
				i2c_nuvoton_पढ़ोy(chip);
			पूर्ण अन्यथा अणु
				/*
				 * समयout_b reached - command was
				 * पातed. TIS should now be in idle state -
				 * only TPM_STS_VALID should be set
				 */
				अगर (i2c_nuvoton_पढ़ो_status(chip) !=
				    TPM_STS_VALID)
					वापस -EIO;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस tpm_chip_रेजिस्टर(chip);
पूर्ण

अटल पूर्णांक i2c_nuvoton_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tpm_chip *chip = i2c_get_clientdata(client);

	tpm_chip_unरेजिस्टर(chip);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id i2c_nuvoton_id[] = अणु
	अणु"tpm_i2c_nuvoton"पूर्ण,
	अणु"tpm2_i2c_nuvoton", .driver_data = I2C_IS_TPM2पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, i2c_nuvoton_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id i2c_nuvoton_of_match[] = अणु
	अणु.compatible = "nuvoton,npct501"पूर्ण,
	अणु.compatible = "winbond,wpct301"पूर्ण,
	अणु.compatible = "nuvoton,npct601", .data = OF_IS_TPM2पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, i2c_nuvoton_of_match);
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(i2c_nuvoton_pm_ops, tpm_pm_suspend, tpm_pm_resume);

अटल काष्ठा i2c_driver i2c_nuvoton_driver = अणु
	.id_table = i2c_nuvoton_id,
	.probe = i2c_nuvoton_probe,
	.हटाओ = i2c_nuvoton_हटाओ,
	.driver = अणु
		.name = "tpm_i2c_nuvoton",
		.pm = &i2c_nuvoton_pm_ops,
		.of_match_table = of_match_ptr(i2c_nuvoton_of_match),
	पूर्ण,
पूर्ण;

module_i2c_driver(i2c_nuvoton_driver);

MODULE_AUTHOR("Dan Morav (dan.morav@nuvoton.com)");
MODULE_DESCRIPTION("Nuvoton TPM I2C Driver");
MODULE_LICENSE("GPL");
