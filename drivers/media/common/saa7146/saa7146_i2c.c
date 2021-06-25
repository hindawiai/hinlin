<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <media/drv-पूर्णांकf/saa7146_vv.h>

अटल u32 saa7146_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	/* DEB_I2C("'%s'\n", adapter->name); */

	वापस	  I2C_FUNC_I2C
		| I2C_FUNC_SMBUS_QUICK
		| I2C_FUNC_SMBUS_READ_BYTE	| I2C_FUNC_SMBUS_WRITE_BYTE
		| I2C_FUNC_SMBUS_READ_BYTE_DATA | I2C_FUNC_SMBUS_WRITE_BYTE_DATA;
पूर्ण

/* this function वापसs the status-रेजिस्टर of our i2c-device */
अटल अंतरभूत u32 saa7146_i2c_status(काष्ठा saa7146_dev *dev)
अणु
	u32 iicsta = saa7146_पढ़ो(dev, I2C_STATUS);
	/* DEB_I2C("status: 0x%08x\n", iicsta); */
	वापस iicsta;
पूर्ण

/* this function runs through the i2c-messages and prepares the data to be
   sent through the saa7146. have a look at the specअगरications p. 122 ff
   to understand this. it वापसs the number of u32s to send, or -1
   in हाल of an error. */
अटल पूर्णांक saa7146_i2c_msg_prepare(स्थिर काष्ठा i2c_msg *m, पूर्णांक num, __le32 *op)
अणु
	पूर्णांक h1, h2;
	पूर्णांक i, j, addr;
	पूर्णांक mem = 0, op_count = 0;

	/* first determine size of needed memory */
	क्रम(i = 0; i < num; i++) अणु
		mem += m[i].len + 1;
	पूर्ण

	/* worst हाल: we need one u32 क्रम three bytes to be send
	   plus one extra byte to address the device */
	mem = 1 + ((mem-1) / 3);

	/* we assume that op poपूर्णांकs to a memory of at least
	 * SAA7146_I2C_MEM bytes size. अगर we exceed this limit...
	 */
	अगर ((4 * mem) > SAA7146_I2C_MEM) अणु
		/* DEB_I2C("cannot prepare i2c-message\n"); */
		वापस -ENOMEM;
	पूर्ण

	/* be careful: clear out the i2c-mem first */
	स_रखो(op,0,माप(__le32)*mem);

	/* loop through all messages */
	क्रम(i = 0; i < num; i++) अणु

		addr = i2c_8bit_addr_from_msg(&m[i]);
		h1 = op_count/3; h2 = op_count%3;
		op[h1] |= cpu_to_le32(	    (u8)addr << ((3-h2)*8));
		op[h1] |= cpu_to_le32(SAA7146_I2C_START << ((3-h2)*2));
		op_count++;

		/* loop through all bytes of message i */
		क्रम(j = 0; j < m[i].len; j++) अणु
			/* insert the data bytes */
			h1 = op_count/3; h2 = op_count%3;
			op[h1] |= cpu_to_le32( (u32)((u8)m[i].buf[j]) << ((3-h2)*8));
			op[h1] |= cpu_to_le32(       SAA7146_I2C_CONT << ((3-h2)*2));
			op_count++;
		पूर्ण

	पूर्ण

	/* have a look at the last byte inserted:
	  अगर it was: ...CONT change it to ...STOP */
	h1 = (op_count-1)/3; h2 = (op_count-1)%3;
	अगर ( SAA7146_I2C_CONT == (0x3 & (le32_to_cpu(op[h1]) >> ((3-h2)*2))) ) अणु
		op[h1] &= ~cpu_to_le32(0x2 << ((3-h2)*2));
		op[h1] |= cpu_to_le32(SAA7146_I2C_STOP << ((3-h2)*2));
	पूर्ण

	/* वापस the number of u32s to send */
	वापस mem;
पूर्ण

/* this functions loops through all i2c-messages. normally, it should determine
   which bytes were पढ़ो through the adapter and ग_लिखो them back to the corresponding
   i2c-message. but instead, we simply ग_लिखो back all bytes.
   fixme: this could be improved. */
अटल पूर्णांक saa7146_i2c_msg_cleanup(स्थिर काष्ठा i2c_msg *m, पूर्णांक num, __le32 *op)
अणु
	पूर्णांक i, j;
	पूर्णांक op_count = 0;

	/* loop through all messages */
	क्रम(i = 0; i < num; i++) अणु

		op_count++;

		/* loop through all bytes of message i */
		क्रम(j = 0; j < m[i].len; j++) अणु
			/* ग_लिखो back all bytes that could have been पढ़ो */
			m[i].buf[j] = (le32_to_cpu(op[op_count/3]) >> ((3-(op_count%3))*8));
			op_count++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* this functions resets the i2c-device and वापसs 0 अगर everything was fine, otherwise -1 */
अटल पूर्णांक saa7146_i2c_reset(काष्ठा saa7146_dev *dev)
अणु
	/* get current status */
	u32 status = saa7146_i2c_status(dev);

	/* clear रेजिस्टरs क्रम sure */
	saa7146_ग_लिखो(dev, I2C_STATUS, dev->i2c_bitrate);
	saa7146_ग_लिखो(dev, I2C_TRANSFER, 0);

	/* check अगर any operation is still in progress */
	अगर ( 0 != ( status & SAA7146_I2C_BUSY) ) अणु

		/* yes, समाप्त ongoing operation */
		DEB_I2C("busy_state detected\n");

		/* set "ABORT-OPERATION"-bit (bit 7)*/
		saa7146_ग_लिखो(dev, I2C_STATUS, (dev->i2c_bitrate | MASK_07));
		saa7146_ग_लिखो(dev, MC2, (MASK_00 | MASK_16));
		msleep(SAA7146_I2C_DELAY);

		/* clear all error-bits pending; this is needed because p.123, note 1 */
		saa7146_ग_लिखो(dev, I2C_STATUS, dev->i2c_bitrate);
		saa7146_ग_लिखो(dev, MC2, (MASK_00 | MASK_16));
		msleep(SAA7146_I2C_DELAY);
	पूर्ण

	/* check अगर any error is (still) present. (this can be necessary because p.123, note 1) */
	status = saa7146_i2c_status(dev);

	अगर ( dev->i2c_bitrate != status ) अणु

		DEB_I2C("error_state detected. status:0x%08x\n", status);

		/* Repeat the पात operation. This seems to be necessary
		   after serious protocol errors caused by e.g. the SAA7740 */
		saa7146_ग_लिखो(dev, I2C_STATUS, (dev->i2c_bitrate | MASK_07));
		saa7146_ग_लिखो(dev, MC2, (MASK_00 | MASK_16));
		msleep(SAA7146_I2C_DELAY);

		/* clear all error-bits pending */
		saa7146_ग_लिखो(dev, I2C_STATUS, dev->i2c_bitrate);
		saa7146_ग_लिखो(dev, MC2, (MASK_00 | MASK_16));
		msleep(SAA7146_I2C_DELAY);

		/* the data sheet says it might be necessary to clear the status
		   twice after an पात */
		saa7146_ग_लिखो(dev, I2C_STATUS, dev->i2c_bitrate);
		saa7146_ग_लिखो(dev, MC2, (MASK_00 | MASK_16));
		msleep(SAA7146_I2C_DELAY);
	पूर्ण

	/* अगर any error is still present, a fatal error has occurred ... */
	status = saa7146_i2c_status(dev);
	अगर ( dev->i2c_bitrate != status ) अणु
		DEB_I2C("fatal error. status:0x%08x\n", status);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/* this functions ग_लिखोs out the data-byte 'dword' to the i2c-device.
   it वापसs 0 अगर ok, -1 अगर the transfer failed, -2 अगर the transfer
   failed badly (e.g. address error) */
अटल पूर्णांक saa7146_i2c_ग_लिखोout(काष्ठा saa7146_dev *dev, __le32 *dword, पूर्णांक लघु_delay)
अणु
	u32 status = 0, mc2 = 0;
	पूर्णांक trial = 0;
	अचिन्हित दीर्घ समयout;

	/* ग_लिखो out i2c-command */
	DEB_I2C("before: 0x%08x (status: 0x%08x), %d\n",
		*dword, saa7146_पढ़ो(dev, I2C_STATUS), dev->i2c_op);

	अगर( 0 != (SAA7146_USE_I2C_IRQ & dev->ext->flags)) अणु

		saa7146_ग_लिखो(dev, I2C_STATUS,	 dev->i2c_bitrate);
		saa7146_ग_लिखो(dev, I2C_TRANSFER, le32_to_cpu(*dword));

		dev->i2c_op = 1;
		SAA7146_ISR_CLEAR(dev, MASK_16|MASK_17);
		SAA7146_IER_ENABLE(dev, MASK_16|MASK_17);
		saa7146_ग_लिखो(dev, MC2, (MASK_00 | MASK_16));

		समयout = HZ/100 + 1; /* 10ms */
		समयout = रुको_event_पूर्णांकerruptible_समयout(dev->i2c_wq, dev->i2c_op == 0, समयout);
		अगर (समयout == -ERESTARTSYS || dev->i2c_op) अणु
			SAA7146_IER_DISABLE(dev, MASK_16|MASK_17);
			SAA7146_ISR_CLEAR(dev, MASK_16|MASK_17);
			अगर (समयout == -ERESTARTSYS)
				/* a संकेत arrived */
				वापस -ERESTARTSYS;

			pr_warn("%s %s [irq]: timed out waiting for end of xfer\n",
				dev->name, __func__);
			वापस -EIO;
		पूर्ण
		status = saa7146_पढ़ो(dev, I2C_STATUS);
	पूर्ण अन्यथा अणु
		saa7146_ग_लिखो(dev, I2C_STATUS,	 dev->i2c_bitrate);
		saa7146_ग_लिखो(dev, I2C_TRANSFER, le32_to_cpu(*dword));
		saa7146_ग_लिखो(dev, MC2, (MASK_00 | MASK_16));

		/* करो not poll क्रम i2c-status beक्रमe upload is complete */
		समयout = jअगरfies + HZ/100 + 1; /* 10ms */
		जबतक(1) अणु
			mc2 = (saa7146_पढ़ो(dev, MC2) & 0x1);
			अगर( 0 != mc2 ) अणु
				अवरोध;
			पूर्ण
			अगर (समय_after(jअगरfies,समयout)) अणु
				pr_warn("%s %s: timed out waiting for MC2\n",
					dev->name, __func__);
				वापस -EIO;
			पूर्ण
		पूर्ण
		/* रुको until we get a transfer करोne or error */
		समयout = jअगरfies + HZ/100 + 1; /* 10ms */
		/* first पढ़ो usually delivers bogus results... */
		saa7146_i2c_status(dev);
		जबतक(1) अणु
			status = saa7146_i2c_status(dev);
			अगर ((status & 0x3) != 1)
				अवरोध;
			अगर (समय_after(jअगरfies,समयout)) अणु
				/* this is normal when probing the bus
				 * (no answer from nonexisistant device...)
				 */
				pr_warn("%s %s [poll]: timed out waiting for end of xfer\n",
					dev->name, __func__);
				वापस -EIO;
			पूर्ण
			अगर (++trial < 50 && लघु_delay)
				udelay(10);
			अन्यथा
				msleep(1);
		पूर्ण
	पूर्ण

	/* give a detailed status report */
	अगर ( 0 != (status & (SAA7146_I2C_SPERR | SAA7146_I2C_APERR |
			     SAA7146_I2C_DTERR | SAA7146_I2C_DRERR |
			     SAA7146_I2C_AL    | SAA7146_I2C_ERR   |
			     SAA7146_I2C_BUSY)) ) अणु

		अगर ( 0 == (status & SAA7146_I2C_ERR) ||
		     0 == (status & SAA7146_I2C_BUSY) ) अणु
			/* it may take some समय until ERR goes high - ignore */
			DEB_I2C("unexpected i2c status %04x\n", status);
		पूर्ण
		अगर( 0 != (status & SAA7146_I2C_SPERR) ) अणु
			DEB_I2C("error due to invalid start/stop condition\n");
		पूर्ण
		अगर( 0 != (status & SAA7146_I2C_DTERR) ) अणु
			DEB_I2C("error in data transmission\n");
		पूर्ण
		अगर( 0 != (status & SAA7146_I2C_DRERR) ) अणु
			DEB_I2C("error when receiving data\n");
		पूर्ण
		अगर( 0 != (status & SAA7146_I2C_AL) ) अणु
			DEB_I2C("error because arbitration lost\n");
		पूर्ण

		/* we handle address-errors here */
		अगर( 0 != (status & SAA7146_I2C_APERR) ) अणु
			DEB_I2C("error in address phase\n");
			वापस -EREMOTEIO;
		पूर्ण

		वापस -EIO;
	पूर्ण

	/* पढ़ो back data, just in हाल we were पढ़ोing ... */
	*dword = cpu_to_le32(saa7146_पढ़ो(dev, I2C_TRANSFER));

	DEB_I2C("after: 0x%08x\n", *dword);
	वापस 0;
पूर्ण

अटल पूर्णांक saa7146_i2c_transfer(काष्ठा saa7146_dev *dev, स्थिर काष्ठा i2c_msg *msgs, पूर्णांक num, पूर्णांक retries)
अणु
	पूर्णांक i = 0, count = 0;
	__le32 *buffer = dev->d_i2c.cpu_addr;
	पूर्णांक err = 0;
	पूर्णांक लघु_delay = 0;

	अगर (mutex_lock_पूर्णांकerruptible(&dev->i2c_lock))
		वापस -ERESTARTSYS;

	क्रम(i=0;i<num;i++) अणु
		DEB_I2C("msg:%d/%d\n", i+1, num);
	पूर्ण

	/* prepare the message(s), get number of u32s to transfer */
	count = saa7146_i2c_msg_prepare(msgs, num, buffer);
	अगर ( 0 > count ) अणु
		err = -EIO;
		जाओ out;
	पूर्ण

	अगर ( count > 3 || 0 != (SAA7146_I2C_SHORT_DELAY & dev->ext->flags) )
		लघु_delay = 1;

	करो अणु
		/* reset the i2c-device अगर necessary */
		err = saa7146_i2c_reset(dev);
		अगर ( 0 > err ) अणु
			DEB_I2C("could not reset i2c-device\n");
			जाओ out;
		पूर्ण

		/* ग_लिखो out the u32s one after another */
		क्रम(i = 0; i < count; i++) अणु
			err = saa7146_i2c_ग_लिखोout(dev, &buffer[i], लघु_delay);
			अगर ( 0 != err) अणु
				/* this one is unsatisfying: some i2c slaves on some
				   dvb cards करोn't acknowledge correctly, so the saa7146
				   thinks that an address error occurred. in that हाल, the
				   transaction should be retrying, even अगर an address error
				   occurred. analog saa7146 based cards extensively rely on
				   i2c address probing, however, and address errors indicate that a
				   device is really *not* there. retrying in that हाल
				   increases the समय the device needs to probe greatly, so
				   it should be aव्योमed. So we bail out in irq mode after an
				   address error and trust the saa7146 address error detection. */
				अगर (-EREMOTEIO == err && 0 != (SAA7146_USE_I2C_IRQ & dev->ext->flags))
					जाओ out;
				DEB_I2C("error while sending message(s). starting again\n");
				अवरोध;
			पूर्ण
		पूर्ण
		अगर( 0 == err ) अणु
			err = num;
			अवरोध;
		पूर्ण

		/* delay a bit beक्रमe retrying */
		msleep(10);

	पूर्ण जबतक (err != num && retries--);

	/* quit अगर any error occurred */
	अगर (err != num)
		जाओ out;

	/* अगर any things had to be पढ़ो, get the results */
	अगर ( 0 != saa7146_i2c_msg_cleanup(msgs, num, buffer)) अणु
		DEB_I2C("could not cleanup i2c-message\n");
		err = -EIO;
		जाओ out;
	पूर्ण

	/* वापस the number of delivered messages */
	DEB_I2C("transmission successful. (msg:%d)\n", err);
out:
	/* another bug in revision 0: the i2c-रेजिस्टरs get uploaded अक्रमomly by other
	   uploads, so we better clear them out beक्रमe continuing */
	अगर( 0 == dev->revision ) अणु
		__le32 zero = 0;
		saa7146_i2c_reset(dev);
		अगर( 0 != saa7146_i2c_ग_लिखोout(dev, &zero, लघु_delay)) अणु
			pr_info("revision 0 error. this should never happen\n");
		पूर्ण
	पूर्ण

	mutex_unlock(&dev->i2c_lock);
	वापस err;
पूर्ण

/* utility functions */
अटल पूर्णांक saa7146_i2c_xfer(काष्ठा i2c_adapter* adapter, काष्ठा i2c_msg *msg, पूर्णांक num)
अणु
	काष्ठा v4l2_device *v4l2_dev = i2c_get_adapdata(adapter);
	काष्ठा saa7146_dev *dev = to_saa7146_dev(v4l2_dev);

	/* use helper function to transfer data */
	वापस saa7146_i2c_transfer(dev, msg, num, adapter->retries);
पूर्ण


/*****************************************************************************/
/* i2c-adapter helper functions                                              */

/* exported algorithm data */
अटल स्थिर काष्ठा i2c_algorithm saa7146_algo = अणु
	.master_xfer	= saa7146_i2c_xfer,
	.functionality	= saa7146_i2c_func,
पूर्ण;

पूर्णांक saa7146_i2c_adapter_prepare(काष्ठा saa7146_dev *dev, काष्ठा i2c_adapter *i2c_adapter, u32 bitrate)
अणु
	DEB_EE("bitrate: 0x%08x\n", bitrate);

	/* enable i2c-port pins */
	saa7146_ग_लिखो(dev, MC1, (MASK_08 | MASK_24));

	dev->i2c_bitrate = bitrate;
	saa7146_i2c_reset(dev);

	अगर (i2c_adapter) अणु
		i2c_set_adapdata(i2c_adapter, &dev->v4l2_dev);
		i2c_adapter->dev.parent    = &dev->pci->dev;
		i2c_adapter->algo	   = &saa7146_algo;
		i2c_adapter->algo_data     = शून्य;
		i2c_adapter->समयout = SAA7146_I2C_TIMEOUT;
		i2c_adapter->retries = SAA7146_I2C_RETRIES;
	पूर्ण

	वापस 0;
पूर्ण
