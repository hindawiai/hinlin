<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * STMicroelectronics TPM Linux driver क्रम TPM ST33ZP24
 * Copyright (C) 2009 - 2016 STMicroelectronics
 */

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/रुको.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/माला.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/sched.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#समावेश "../tpm.h"
#समावेश "st33zp24.h"

#घोषणा TPM_ACCESS			0x0
#घोषणा TPM_STS				0x18
#घोषणा TPM_DATA_FIFO			0x24
#घोषणा TPM_INTF_CAPABILITY		0x14
#घोषणा TPM_INT_STATUS			0x10
#घोषणा TPM_INT_ENABLE			0x08

#घोषणा LOCALITY0			0

क्रमागत st33zp24_access अणु
	TPM_ACCESS_VALID = 0x80,
	TPM_ACCESS_ACTIVE_LOCALITY = 0x20,
	TPM_ACCESS_REQUEST_PENDING = 0x04,
	TPM_ACCESS_REQUEST_USE = 0x02,
पूर्ण;

क्रमागत st33zp24_status अणु
	TPM_STS_VALID = 0x80,
	TPM_STS_COMMAND_READY = 0x40,
	TPM_STS_GO = 0x20,
	TPM_STS_DATA_AVAIL = 0x10,
	TPM_STS_DATA_EXPECT = 0x08,
पूर्ण;

क्रमागत st33zp24_पूर्णांक_flags अणु
	TPM_GLOBAL_INT_ENABLE = 0x80,
	TPM_INTF_CMD_READY_INT = 0x080,
	TPM_INTF_FIFO_AVALAIBLE_INT = 0x040,
	TPM_INTF_WAKE_UP_READY_INT = 0x020,
	TPM_INTF_LOCALITY_CHANGE_INT = 0x004,
	TPM_INTF_STS_VALID_INT = 0x002,
	TPM_INTF_DATA_AVAIL_INT = 0x001,
पूर्ण;

क्रमागत tis_शेषs अणु
	TIS_SHORT_TIMEOUT = 750,
	TIS_LONG_TIMEOUT = 2000,
पूर्ण;

/*
 * clear_पूर्णांकerruption clear the pending पूर्णांकerrupt.
 * @param: tpm_dev, the tpm device device.
 * @वापस: the पूर्णांकerrupt status value.
 */
अटल u8 clear_पूर्णांकerruption(काष्ठा st33zp24_dev *tpm_dev)
अणु
	u8 पूर्णांकerrupt;

	tpm_dev->ops->recv(tpm_dev->phy_id, TPM_INT_STATUS, &पूर्णांकerrupt, 1);
	tpm_dev->ops->send(tpm_dev->phy_id, TPM_INT_STATUS, &पूर्णांकerrupt, 1);
	वापस पूर्णांकerrupt;
पूर्ण /* clear_पूर्णांकerruption() */

/*
 * st33zp24_cancel, cancel the current command execution or
 * set STS to COMMAND READY.
 * @param: chip, the tpm_chip description as specअगरied in driver/अक्षर/tpm/tpm.h
 */
अटल व्योम st33zp24_cancel(काष्ठा tpm_chip *chip)
अणु
	काष्ठा st33zp24_dev *tpm_dev = dev_get_drvdata(&chip->dev);
	u8 data;

	data = TPM_STS_COMMAND_READY;
	tpm_dev->ops->send(tpm_dev->phy_id, TPM_STS, &data, 1);
पूर्ण /* st33zp24_cancel() */

/*
 * st33zp24_status वापस the TPM_STS रेजिस्टर
 * @param: chip, the tpm chip description
 * @वापस: the TPM_STS रेजिस्टर value.
 */
अटल u8 st33zp24_status(काष्ठा tpm_chip *chip)
अणु
	काष्ठा st33zp24_dev *tpm_dev = dev_get_drvdata(&chip->dev);
	u8 data;

	tpm_dev->ops->recv(tpm_dev->phy_id, TPM_STS, &data, 1);
	वापस data;
पूर्ण /* st33zp24_status() */

/*
 * check_locality अगर the locality is active
 * @param: chip, the tpm chip description
 * @वापस: true अगर LOCALITY0 is active, otherwise false
 */
अटल bool check_locality(काष्ठा tpm_chip *chip)
अणु
	काष्ठा st33zp24_dev *tpm_dev = dev_get_drvdata(&chip->dev);
	u8 data;
	u8 status;

	status = tpm_dev->ops->recv(tpm_dev->phy_id, TPM_ACCESS, &data, 1);
	अगर (status && (data &
		(TPM_ACCESS_ACTIVE_LOCALITY | TPM_ACCESS_VALID)) ==
		(TPM_ACCESS_ACTIVE_LOCALITY | TPM_ACCESS_VALID))
		वापस true;

	वापस false;
पूर्ण /* check_locality() */

/*
 * request_locality request the TPM locality
 * @param: chip, the chip description
 * @वापस: the active locality or negative value.
 */
अटल पूर्णांक request_locality(काष्ठा tpm_chip *chip)
अणु
	काष्ठा st33zp24_dev *tpm_dev = dev_get_drvdata(&chip->dev);
	अचिन्हित दीर्घ stop;
	दीर्घ ret;
	u8 data;

	अगर (check_locality(chip))
		वापस tpm_dev->locality;

	data = TPM_ACCESS_REQUEST_USE;
	ret = tpm_dev->ops->send(tpm_dev->phy_id, TPM_ACCESS, &data, 1);
	अगर (ret < 0)
		वापस ret;

	stop = jअगरfies + chip->समयout_a;

	/* Request locality is usually effective after the request */
	करो अणु
		अगर (check_locality(chip))
			वापस tpm_dev->locality;
		msleep(TPM_TIMEOUT);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, stop));

	/* could not get locality */
	वापस -EACCES;
पूर्ण /* request_locality() */

/*
 * release_locality release the active locality
 * @param: chip, the tpm chip description.
 */
अटल व्योम release_locality(काष्ठा tpm_chip *chip)
अणु
	काष्ठा st33zp24_dev *tpm_dev = dev_get_drvdata(&chip->dev);
	u8 data;

	data = TPM_ACCESS_ACTIVE_LOCALITY;

	tpm_dev->ops->send(tpm_dev->phy_id, TPM_ACCESS, &data, 1);
पूर्ण

/*
 * get_burstcount वापस the burstcount value
 * @param: chip, the chip description
 * वापस: the burstcount or negative value.
 */
अटल पूर्णांक get_burstcount(काष्ठा tpm_chip *chip)
अणु
	काष्ठा st33zp24_dev *tpm_dev = dev_get_drvdata(&chip->dev);
	अचिन्हित दीर्घ stop;
	पूर्णांक burstcnt, status;
	u8 temp;

	stop = jअगरfies + chip->समयout_d;
	करो अणु
		status = tpm_dev->ops->recv(tpm_dev->phy_id, TPM_STS + 1,
					    &temp, 1);
		अगर (status < 0)
			वापस -EBUSY;

		burstcnt = temp;
		status = tpm_dev->ops->recv(tpm_dev->phy_id, TPM_STS + 2,
					    &temp, 1);
		अगर (status < 0)
			वापस -EBUSY;

		burstcnt |= temp << 8;
		अगर (burstcnt)
			वापस burstcnt;
		msleep(TPM_TIMEOUT);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, stop));
	वापस -EBUSY;
पूर्ण /* get_burstcount() */


/*
 * रुको_क्रम_tpm_stat_cond
 * @param: chip, chip description
 * @param: mask, expected mask value
 * @param: check_cancel, करोes the command expected to be canceled ?
 * @param: canceled, did we received a cancel request ?
 * @वापस: true अगर status == mask or अगर the command is canceled.
 * false in other हालs.
 */
अटल bool रुको_क्रम_tpm_stat_cond(काष्ठा tpm_chip *chip, u8 mask,
				bool check_cancel, bool *canceled)
अणु
	u8 status = chip->ops->status(chip);

	*canceled = false;
	अगर ((status & mask) == mask)
		वापस true;
	अगर (check_cancel && chip->ops->req_canceled(chip, status)) अणु
		*canceled = true;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * रुको_क्रम_stat रुको क्रम a TPM_STS value
 * @param: chip, the tpm chip description
 * @param: mask, the value mask to रुको
 * @param: समयout, the समयout
 * @param: queue, the रुको queue.
 * @param: check_cancel, करोes the command can be cancelled ?
 * @वापस: the tpm status, 0 अगर success, -ETIME अगर समयout is reached.
 */
अटल पूर्णांक रुको_क्रम_stat(काष्ठा tpm_chip *chip, u8 mask, अचिन्हित दीर्घ समयout,
			रुको_queue_head_t *queue, bool check_cancel)
अणु
	काष्ठा st33zp24_dev *tpm_dev = dev_get_drvdata(&chip->dev);
	अचिन्हित दीर्घ stop;
	पूर्णांक ret = 0;
	bool canceled = false;
	bool condition;
	u32 cur_पूर्णांकrs;
	u8 status;

	/* check current status */
	status = st33zp24_status(chip);
	अगर ((status & mask) == mask)
		वापस 0;

	stop = jअगरfies + समयout;

	अगर (chip->flags & TPM_CHIP_FLAG_IRQ) अणु
		cur_पूर्णांकrs = tpm_dev->पूर्णांकrs;
		clear_पूर्णांकerruption(tpm_dev);
		enable_irq(tpm_dev->irq);

		करो अणु
			अगर (ret == -ERESTARTSYS && मुक्तzing(current))
				clear_thपढ़ो_flag(TIF_SIGPENDING);

			समयout = stop - jअगरfies;
			अगर ((दीर्घ) समयout <= 0)
				वापस -1;

			ret = रुको_event_पूर्णांकerruptible_समयout(*queue,
						cur_पूर्णांकrs != tpm_dev->पूर्णांकrs,
						समयout);
			clear_पूर्णांकerruption(tpm_dev);
			condition = रुको_क्रम_tpm_stat_cond(chip, mask,
						check_cancel, &canceled);
			अगर (ret >= 0 && condition) अणु
				अगर (canceled)
					वापस -ECANCELED;
				वापस 0;
			पूर्ण
		पूर्ण जबतक (ret == -ERESTARTSYS && मुक्तzing(current));

		disable_irq_nosync(tpm_dev->irq);

	पूर्ण अन्यथा अणु
		करो अणु
			msleep(TPM_TIMEOUT);
			status = chip->ops->status(chip);
			अगर ((status & mask) == mask)
				वापस 0;
		पूर्ण जबतक (समय_beक्रमe(jअगरfies, stop));
	पूर्ण

	वापस -ETIME;
पूर्ण /* रुको_क्रम_stat() */

/*
 * recv_data receive data
 * @param: chip, the tpm chip description
 * @param: buf, the buffer where the data are received
 * @param: count, the number of data to receive
 * @वापस: the number of bytes पढ़ो from TPM FIFO.
 */
अटल पूर्णांक recv_data(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार count)
अणु
	काष्ठा st33zp24_dev *tpm_dev = dev_get_drvdata(&chip->dev);
	पूर्णांक size = 0, burstcnt, len, ret;

	जबतक (size < count &&
	       रुको_क्रम_stat(chip,
			     TPM_STS_DATA_AVAIL | TPM_STS_VALID,
			     chip->समयout_c,
			     &tpm_dev->पढ़ो_queue, true) == 0) अणु
		burstcnt = get_burstcount(chip);
		अगर (burstcnt < 0)
			वापस burstcnt;
		len = min_t(पूर्णांक, burstcnt, count - size);
		ret = tpm_dev->ops->recv(tpm_dev->phy_id, TPM_DATA_FIFO,
					 buf + size, len);
		अगर (ret < 0)
			वापस ret;

		size += len;
	पूर्ण
	वापस size;
पूर्ण

/*
 * tpm_ioserirq_handler the serirq irq handler
 * @param: irq, the tpm chip description
 * @param: dev_id, the description of the chip
 * @वापस: the status of the handler.
 */
अटल irqवापस_t tpm_ioserirq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा tpm_chip *chip = dev_id;
	काष्ठा st33zp24_dev *tpm_dev = dev_get_drvdata(&chip->dev);

	tpm_dev->पूर्णांकrs++;
	wake_up_पूर्णांकerruptible(&tpm_dev->पढ़ो_queue);
	disable_irq_nosync(tpm_dev->irq);

	वापस IRQ_HANDLED;
पूर्ण /* tpm_ioserirq_handler() */

/*
 * st33zp24_send send TPM commands through the I2C bus.
 *
 * @param: chip, the tpm_chip description as specअगरied in driver/अक्षर/tpm/tpm.h
 * @param: buf,	the buffer to send.
 * @param: count, the number of bytes to send.
 * @वापस: In हाल of success the number of bytes sent.
 *			In other हाल, a < 0 value describing the issue.
 */
अटल पूर्णांक st33zp24_send(काष्ठा tpm_chip *chip, अचिन्हित अक्षर *buf,
			 माप_प्रकार len)
अणु
	काष्ठा st33zp24_dev *tpm_dev = dev_get_drvdata(&chip->dev);
	u32 status, i, size, ordinal;
	पूर्णांक burstcnt = 0;
	पूर्णांक ret;
	u8 data;

	अगर (len < TPM_HEADER_SIZE)
		वापस -EBUSY;

	ret = request_locality(chip);
	अगर (ret < 0)
		वापस ret;

	status = st33zp24_status(chip);
	अगर ((status & TPM_STS_COMMAND_READY) == 0) अणु
		st33zp24_cancel(chip);
		अगर (रुको_क्रम_stat
		    (chip, TPM_STS_COMMAND_READY, chip->समयout_b,
		     &tpm_dev->पढ़ो_queue, false) < 0) अणु
			ret = -ETIME;
			जाओ out_err;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < len - 1;) अणु
		burstcnt = get_burstcount(chip);
		अगर (burstcnt < 0)
			वापस burstcnt;
		size = min_t(पूर्णांक, len - i - 1, burstcnt);
		ret = tpm_dev->ops->send(tpm_dev->phy_id, TPM_DATA_FIFO,
					 buf + i, size);
		अगर (ret < 0)
			जाओ out_err;

		i += size;
	पूर्ण

	status = st33zp24_status(chip);
	अगर ((status & TPM_STS_DATA_EXPECT) == 0) अणु
		ret = -EIO;
		जाओ out_err;
	पूर्ण

	ret = tpm_dev->ops->send(tpm_dev->phy_id, TPM_DATA_FIFO,
				 buf + len - 1, 1);
	अगर (ret < 0)
		जाओ out_err;

	status = st33zp24_status(chip);
	अगर ((status & TPM_STS_DATA_EXPECT) != 0) अणु
		ret = -EIO;
		जाओ out_err;
	पूर्ण

	data = TPM_STS_GO;
	ret = tpm_dev->ops->send(tpm_dev->phy_id, TPM_STS, &data, 1);
	अगर (ret < 0)
		जाओ out_err;

	अगर (chip->flags & TPM_CHIP_FLAG_IRQ) अणु
		ordinal = be32_to_cpu(*((__be32 *) (buf + 6)));

		ret = रुको_क्रम_stat(chip, TPM_STS_DATA_AVAIL | TPM_STS_VALID,
				tpm_calc_ordinal_duration(chip, ordinal),
				&tpm_dev->पढ़ो_queue, false);
		अगर (ret < 0)
			जाओ out_err;
	पूर्ण

	वापस 0;
out_err:
	st33zp24_cancel(chip);
	release_locality(chip);
	वापस ret;
पूर्ण

/*
 * st33zp24_recv received TPM response through TPM phy.
 * @param: chip, the tpm_chip description as specअगरied in driver/अक्षर/tpm/tpm.h.
 * @param: buf,	the buffer to store datas.
 * @param: count, the number of bytes to send.
 * @वापस: In हाल of success the number of bytes received.
 *	    In other हाल, a < 0 value describing the issue.
 */
अटल पूर्णांक st33zp24_recv(काष्ठा tpm_chip *chip, अचिन्हित अक्षर *buf,
			    माप_प्रकार count)
अणु
	पूर्णांक size = 0;
	u32 expected;

	अगर (!chip)
		वापस -EBUSY;

	अगर (count < TPM_HEADER_SIZE) अणु
		size = -EIO;
		जाओ out;
	पूर्ण

	size = recv_data(chip, buf, TPM_HEADER_SIZE);
	अगर (size < TPM_HEADER_SIZE) अणु
		dev_err(&chip->dev, "Unable to read header\n");
		जाओ out;
	पूर्ण

	expected = be32_to_cpu(*(__be32 *)(buf + 2));
	अगर (expected > count || expected < TPM_HEADER_SIZE) अणु
		size = -EIO;
		जाओ out;
	पूर्ण

	size += recv_data(chip, &buf[TPM_HEADER_SIZE],
			expected - TPM_HEADER_SIZE);
	अगर (size < expected) अणु
		dev_err(&chip->dev, "Unable to read remainder of result\n");
		size = -ETIME;
	पूर्ण

out:
	st33zp24_cancel(chip);
	release_locality(chip);
	वापस size;
पूर्ण

/*
 * st33zp24_req_canceled
 * @param: chip, the tpm_chip description as specअगरied in driver/अक्षर/tpm/tpm.h.
 * @param: status, the TPM status.
 * @वापस: Does TPM पढ़ोy to compute a new command ? true.
 */
अटल bool st33zp24_req_canceled(काष्ठा tpm_chip *chip, u8 status)
अणु
	वापस (status == TPM_STS_COMMAND_READY);
पूर्ण

अटल स्थिर काष्ठा tpm_class_ops st33zp24_tpm = अणु
	.flags = TPM_OPS_AUTO_STARTUP,
	.send = st33zp24_send,
	.recv = st33zp24_recv,
	.cancel = st33zp24_cancel,
	.status = st33zp24_status,
	.req_complete_mask = TPM_STS_DATA_AVAIL | TPM_STS_VALID,
	.req_complete_val = TPM_STS_DATA_AVAIL | TPM_STS_VALID,
	.req_canceled = st33zp24_req_canceled,
पूर्ण;

/*
 * st33zp24_probe initialize the TPM device
 * @param: client, the i2c_client description (TPM I2C description).
 * @param: id, the i2c_device_id काष्ठा.
 * @वापस: 0 in हाल of success.
 *	 -1 in other हाल.
 */
पूर्णांक st33zp24_probe(व्योम *phy_id, स्थिर काष्ठा st33zp24_phy_ops *ops,
		   काष्ठा device *dev, पूर्णांक irq, पूर्णांक io_lpcpd)
अणु
	पूर्णांक ret;
	u8 पूर्णांकmask = 0;
	काष्ठा tpm_chip *chip;
	काष्ठा st33zp24_dev *tpm_dev;

	chip = tpmm_chip_alloc(dev, &st33zp24_tpm);
	अगर (IS_ERR(chip))
		वापस PTR_ERR(chip);

	tpm_dev = devm_kzalloc(dev, माप(काष्ठा st33zp24_dev),
			       GFP_KERNEL);
	अगर (!tpm_dev)
		वापस -ENOMEM;

	tpm_dev->phy_id = phy_id;
	tpm_dev->ops = ops;
	dev_set_drvdata(&chip->dev, tpm_dev);

	chip->समयout_a = msecs_to_jअगरfies(TIS_SHORT_TIMEOUT);
	chip->समयout_b = msecs_to_jअगरfies(TIS_LONG_TIMEOUT);
	chip->समयout_c = msecs_to_jअगरfies(TIS_SHORT_TIMEOUT);
	chip->समयout_d = msecs_to_jअगरfies(TIS_SHORT_TIMEOUT);

	tpm_dev->locality = LOCALITY0;

	अगर (irq) अणु
		/* INTERRUPT Setup */
		init_रुकोqueue_head(&tpm_dev->पढ़ो_queue);
		tpm_dev->पूर्णांकrs = 0;

		अगर (request_locality(chip) != LOCALITY0) अणु
			ret = -ENODEV;
			जाओ _tpm_clean_answer;
		पूर्ण

		clear_पूर्णांकerruption(tpm_dev);
		ret = devm_request_irq(dev, irq, tpm_ioserirq_handler,
				IRQF_TRIGGER_HIGH, "TPM SERIRQ management",
				chip);
		अगर (ret < 0) अणु
			dev_err(&chip->dev, "TPM SERIRQ signals %d not available\n",
				irq);
			जाओ _tpm_clean_answer;
		पूर्ण

		पूर्णांकmask |= TPM_INTF_CMD_READY_INT
			|  TPM_INTF_STS_VALID_INT
			|  TPM_INTF_DATA_AVAIL_INT;

		ret = tpm_dev->ops->send(tpm_dev->phy_id, TPM_INT_ENABLE,
					 &पूर्णांकmask, 1);
		अगर (ret < 0)
			जाओ _tpm_clean_answer;

		पूर्णांकmask = TPM_GLOBAL_INT_ENABLE;
		ret = tpm_dev->ops->send(tpm_dev->phy_id, (TPM_INT_ENABLE + 3),
					 &पूर्णांकmask, 1);
		अगर (ret < 0)
			जाओ _tpm_clean_answer;

		tpm_dev->irq = irq;
		chip->flags |= TPM_CHIP_FLAG_IRQ;

		disable_irq_nosync(tpm_dev->irq);
	पूर्ण

	वापस tpm_chip_रेजिस्टर(chip);
_tpm_clean_answer:
	dev_info(&chip->dev, "TPM initialization fail\n");
	वापस ret;
पूर्ण
EXPORT_SYMBOL(st33zp24_probe);

/*
 * st33zp24_हटाओ हटाओ the TPM device
 * @param: tpm_data, the tpm phy.
 * @वापस: 0 in हाल of success.
 */
पूर्णांक st33zp24_हटाओ(काष्ठा tpm_chip *chip)
अणु
	tpm_chip_unरेजिस्टर(chip);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(st33zp24_हटाओ);

#अगर_घोषित CONFIG_PM_SLEEP
/*
 * st33zp24_pm_suspend suspend the TPM device
 * @param: tpm_data, the tpm phy.
 * @param: mesg, the घातer management message.
 * @वापस: 0 in हाल of success.
 */
पूर्णांक st33zp24_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा tpm_chip *chip = dev_get_drvdata(dev);
	काष्ठा st33zp24_dev *tpm_dev = dev_get_drvdata(&chip->dev);

	पूर्णांक ret = 0;

	अगर (gpio_is_valid(tpm_dev->io_lpcpd))
		gpio_set_value(tpm_dev->io_lpcpd, 0);
	अन्यथा
		ret = tpm_pm_suspend(dev);

	वापस ret;
पूर्ण /* st33zp24_pm_suspend() */
EXPORT_SYMBOL(st33zp24_pm_suspend);

/*
 * st33zp24_pm_resume resume the TPM device
 * @param: tpm_data, the tpm phy.
 * @वापस: 0 in हाल of success.
 */
पूर्णांक st33zp24_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा tpm_chip *chip = dev_get_drvdata(dev);
	काष्ठा st33zp24_dev *tpm_dev = dev_get_drvdata(&chip->dev);
	पूर्णांक ret = 0;

	अगर (gpio_is_valid(tpm_dev->io_lpcpd)) अणु
		gpio_set_value(tpm_dev->io_lpcpd, 1);
		ret = रुको_क्रम_stat(chip,
				TPM_STS_VALID, chip->समयout_b,
				&tpm_dev->पढ़ो_queue, false);
	पूर्ण अन्यथा अणु
		ret = tpm_pm_resume(dev);
		अगर (!ret)
			tpm1_करो_selftest(chip);
	पूर्ण
	वापस ret;
पूर्ण /* st33zp24_pm_resume() */
EXPORT_SYMBOL(st33zp24_pm_resume);
#पूर्ण_अगर

MODULE_AUTHOR("TPM support (TPMsupport@list.st.com)");
MODULE_DESCRIPTION("ST33ZP24 TPM 1.2 driver");
MODULE_VERSION("1.3.0");
MODULE_LICENSE("GPL");
