<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OPAL PNOR flash MTD असलtraction
 *
 * Copyright IBM 2015
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>

#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>

#समावेश <यंत्र/opal.h>


/*
 * This driver creates the a Linux MTD असलtraction क्रम platक्रमm PNOR flash
 * backed by OPAL calls
 */

काष्ठा घातernv_flash अणु
	काष्ठा mtd_info	mtd;
	u32 id;
पूर्ण;

क्रमागत flash_op अणु
	FLASH_OP_READ,
	FLASH_OP_WRITE,
	FLASH_OP_ERASE,
पूर्ण;

/*
 * Don't return -ERESTARTSYS if we can't get a token, the MTD core
 * might have split up the call from userspace and called पूर्णांकo the
 * driver more than once, we'll alपढ़ोy have करोne some amount of work.
 */
अटल पूर्णांक घातernv_flash_async_op(काष्ठा mtd_info *mtd, क्रमागत flash_op op,
		loff_t offset, माप_प्रकार len, माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	काष्ठा घातernv_flash *info = (काष्ठा घातernv_flash *)mtd->priv;
	काष्ठा device *dev = &mtd->dev;
	पूर्णांक token;
	काष्ठा opal_msg msg;
	पूर्णांक rc;

	dev_dbg(dev, "%s(op=%d, offset=0x%llx, len=%zu)\n",
			__func__, op, offset, len);

	token = opal_async_get_token_पूर्णांकerruptible();
	अगर (token < 0) अणु
		अगर (token != -ERESTARTSYS)
			dev_err(dev, "Failed to get an async token\n");
		अन्यथा
			token = -EINTR;
		वापस token;
	पूर्ण

	चयन (op) अणु
	हाल FLASH_OP_READ:
		rc = opal_flash_पढ़ो(info->id, offset, __pa(buf), len, token);
		अवरोध;
	हाल FLASH_OP_WRITE:
		rc = opal_flash_ग_लिखो(info->id, offset, __pa(buf), len, token);
		अवरोध;
	हाल FLASH_OP_ERASE:
		rc = opal_flash_erase(info->id, offset, len, token);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		opal_async_release_token(token);
		वापस -EIO;
	पूर्ण

	अगर (rc == OPAL_ASYNC_COMPLETION) अणु
		rc = opal_async_रुको_response_पूर्णांकerruptible(token, &msg);
		अगर (rc) अणु
			/*
			 * If we वापस the mtd core will मुक्त the
			 * buffer we've just passed to OPAL but OPAL
			 * will जारी to पढ़ो or ग_लिखो from that
			 * memory.
			 * It may be tempting to ultimately वापस 0
			 * अगर we're करोing a पढ़ो or a ग_लिखो since we
			 * are going to end up रुकोing until OPAL is
			 * करोne. However, because the MTD core sends
			 * us the userspace request in chunks, we need
			 * it to know we've been पूर्णांकerrupted.
			 */
			rc = -EINTR;
			अगर (opal_async_रुको_response(token, &msg))
				dev_err(dev, "opal_async_wait_response() failed\n");
			जाओ out;
		पूर्ण
		rc = opal_get_async_rc(msg);
	पूर्ण

	/*
	 * OPAL करोes mutual exclusion on the flash, it will वापस
	 * OPAL_BUSY.
	 * During firmware updates by the service processor OPAL may
	 * be (temporarily) prevented from accessing the flash, in
	 * this हाल OPAL will also वापस OPAL_BUSY.
	 * Both हालs aren't errors exactly but the flash could have
	 * changed, userspace should be inक्रमmed.
	 */
	अगर (rc != OPAL_SUCCESS && rc != OPAL_BUSY)
		dev_err(dev, "opal_flash_async_op(op=%d) failed (rc %d)\n",
				op, rc);

	अगर (rc == OPAL_SUCCESS && retlen)
		*retlen = len;

	rc = opal_error_code(rc);
out:
	opal_async_release_token(token);
	वापस rc;
पूर्ण

/**
 * घातernv_flash_पढ़ो
 * @mtd: the device
 * @from: the offset to पढ़ो from
 * @len: the number of bytes to पढ़ो
 * @retlen: the number of bytes actually पढ़ो
 * @buf: the filled in buffer
 *
 * Returns 0 अगर पढ़ो successful, or -ERRNO अगर an error occurred
 */
अटल पूर्णांक घातernv_flash_पढ़ो(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
	     माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	वापस घातernv_flash_async_op(mtd, FLASH_OP_READ, from,
			len, retlen, buf);
पूर्ण

/**
 * घातernv_flash_ग_लिखो
 * @mtd: the device
 * @to: the offset to ग_लिखो to
 * @len: the number of bytes to ग_लिखो
 * @retlen: the number of bytes actually written
 * @buf: the buffer to get bytes from
 *
 * Returns 0 अगर ग_लिखो successful, -ERRNO अगर error occurred
 */
अटल पूर्णांक घातernv_flash_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
		     माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	वापस घातernv_flash_async_op(mtd, FLASH_OP_WRITE, to,
			len, retlen, (u_अक्षर *)buf);
पूर्ण

/**
 * घातernv_flash_erase
 * @mtd: the device
 * @erase: the erase info
 * Returns 0 अगर erase successful or -ERRNO अगर an error occurred
 */
अटल पूर्णांक घातernv_flash_erase(काष्ठा mtd_info *mtd, काष्ठा erase_info *erase)
अणु
	पूर्णांक rc;

	rc =  घातernv_flash_async_op(mtd, FLASH_OP_ERASE, erase->addr,
			erase->len, शून्य, शून्य);
	अगर (rc)
		erase->fail_addr = erase->addr;

	वापस rc;
पूर्ण

/**
 * घातernv_flash_set_driver_info - Fill the mtd_info काष्ठाure and करोcg3
 * @dev: The device काष्ठाure
 * @mtd: The काष्ठाure to fill
 */
अटल पूर्णांक घातernv_flash_set_driver_info(काष्ठा device *dev,
		काष्ठा mtd_info *mtd)
अणु
	u64 size;
	u32 erase_size;
	पूर्णांक rc;

	rc = of_property_पढ़ो_u32(dev->of_node, "ibm,flash-block-size",
			&erase_size);
	अगर (rc) अणु
		dev_err(dev, "couldn't get resource block size information\n");
		वापस rc;
	पूर्ण

	rc = of_property_पढ़ो_u64(dev->of_node, "reg", &size);
	अगर (rc) अणु
		dev_err(dev, "couldn't get resource size information\n");
		वापस rc;
	पूर्ण

	/*
	 * Going to have to check what details I need to set and how to
	 * get them
	 */
	mtd->name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%pOFP", dev->of_node);
	mtd->type = MTD_NORFLASH;
	mtd->flags = MTD_WRITEABLE;
	mtd->size = size;
	mtd->erasesize = erase_size;
	mtd->ग_लिखोbufsize = mtd->ग_लिखोsize = 1;
	mtd->owner = THIS_MODULE;
	mtd->_erase = घातernv_flash_erase;
	mtd->_पढ़ो = घातernv_flash_पढ़ो;
	mtd->_ग_लिखो = घातernv_flash_ग_लिखो;
	mtd->dev.parent = dev;
	mtd_set_of_node(mtd, dev->of_node);
	वापस 0;
पूर्ण

/**
 * घातernv_flash_probe
 * @pdev: platक्रमm device
 *
 * Returns 0 on success, -ENOMEM, -ENXIO on error
 */
अटल पूर्णांक घातernv_flash_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा घातernv_flash *data;
	पूर्णांक ret;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->mtd.priv = data;

	ret = of_property_पढ़ो_u32(dev->of_node, "ibm,opal-id", &(data->id));
	अगर (ret) अणु
		dev_err(dev, "no device property 'ibm,opal-id'\n");
		वापस ret;
	पूर्ण

	ret = घातernv_flash_set_driver_info(dev, &data->mtd);
	अगर (ret)
		वापस ret;

	dev_set_drvdata(dev, data);

	/*
	 * The current flash that skiboot exposes is one contiguous flash chip
	 * with an ffs partition at the start, it should prove easier क्रम users
	 * to deal with partitions or not as they see fit
	 */
	वापस mtd_device_रेजिस्टर(&data->mtd, शून्य, 0);
पूर्ण

/**
 * op_release - Release the driver
 * @pdev: the platक्रमm device
 *
 * Returns 0
 */
अटल पूर्णांक घातernv_flash_release(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा घातernv_flash *data = dev_get_drvdata(&(pdev->dev));

	/* All resources should be मुक्तd स्वतःmatically */
	वापस mtd_device_unरेजिस्टर(&(data->mtd));
पूर्ण

अटल स्थिर काष्ठा of_device_id घातernv_flash_match[] = अणु
	अणु .compatible = "ibm,opal-flash" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver घातernv_flash_driver = अणु
	.driver		= अणु
		.name		= "powernv_flash",
		.of_match_table	= घातernv_flash_match,
	पूर्ण,
	.हटाओ		= घातernv_flash_release,
	.probe		= घातernv_flash_probe,
पूर्ण;

module_platक्रमm_driver(घातernv_flash_driver);

MODULE_DEVICE_TABLE(of, घातernv_flash_match);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cyril Bur <cyril.bur@au1.ibm.com>");
MODULE_DESCRIPTION("MTD abstraction for OPAL flash");
