<शैली गुरु>
/*
 * drivers/w1/masters/omap_hdq.c
 *
 * Copyright (C) 2007,2012 Texas Instruments, Inc.
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/sched.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>

#समावेश <linux/w1.h>

#घोषणा	MOD_NAME	"OMAP_HDQ:"

#घोषणा OMAP_HDQ_REVISION			0x00
#घोषणा OMAP_HDQ_TX_DATA			0x04
#घोषणा OMAP_HDQ_RX_DATA			0x08
#घोषणा OMAP_HDQ_CTRL_STATUS			0x0c
#घोषणा OMAP_HDQ_CTRL_STATUS_SINGLE		BIT(7)
#घोषणा OMAP_HDQ_CTRL_STATUS_INTERRUPTMASK	BIT(6)
#घोषणा OMAP_HDQ_CTRL_STATUS_CLOCKENABLE	BIT(5)
#घोषणा OMAP_HDQ_CTRL_STATUS_GO                 BIT(4)
#घोषणा OMAP_HDQ_CTRL_STATUS_PRESENCE		BIT(3)
#घोषणा OMAP_HDQ_CTRL_STATUS_INITIALIZATION	BIT(2)
#घोषणा OMAP_HDQ_CTRL_STATUS_सूची		BIT(1)
#घोषणा OMAP_HDQ_INT_STATUS			0x10
#घोषणा OMAP_HDQ_INT_STATUS_TXCOMPLETE		BIT(2)
#घोषणा OMAP_HDQ_INT_STATUS_RXCOMPLETE		BIT(1)
#घोषणा OMAP_HDQ_INT_STATUS_TIMEOUT		BIT(0)

#घोषणा OMAP_HDQ_FLAG_CLEAR			0
#घोषणा OMAP_HDQ_FLAG_SET			1
#घोषणा OMAP_HDQ_TIMEOUT			(HZ/5)

#घोषणा OMAP_HDQ_MAX_USER			4

अटल DECLARE_WAIT_QUEUE_HEAD(hdq_रुको_queue);

अटल पूर्णांक w1_id;
module_param(w1_id, पूर्णांक, S_IRUSR);
MODULE_PARM_DESC(w1_id, "1-wire id for the slave detection in HDQ mode");

काष्ठा hdq_data अणु
	काष्ठा device		*dev;
	व्योम __iomem		*hdq_base;
	/* lock पढ़ो/ग_लिखो/अवरोध operations */
	काष्ठा  mutex		hdq_mutex;
	/* पूर्णांकerrupt status and a lock क्रम it */
	u8			hdq_irqstatus;
	spinlock_t		hdq_spinlock;
	/* mode: 0-HDQ 1-W1 */
	पूर्णांक                     mode;

पूर्ण;

/* HDQ रेजिस्टर I/O routines */
अटल अंतरभूत u8 hdq_reg_in(काष्ठा hdq_data *hdq_data, u32 offset)
अणु
	वापस __raw_पढ़ोl(hdq_data->hdq_base + offset);
पूर्ण

अटल अंतरभूत व्योम hdq_reg_out(काष्ठा hdq_data *hdq_data, u32 offset, u8 val)
अणु
	__raw_ग_लिखोl(val, hdq_data->hdq_base + offset);
पूर्ण

अटल अंतरभूत u8 hdq_reg_merge(काष्ठा hdq_data *hdq_data, u32 offset,
			u8 val, u8 mask)
अणु
	u8 new_val = (__raw_पढ़ोl(hdq_data->hdq_base + offset) & ~mask)
			| (val & mask);
	__raw_ग_लिखोl(new_val, hdq_data->hdq_base + offset);

	वापस new_val;
पूर्ण

/*
 * Wait क्रम one or more bits in flag change.
 * HDQ_FLAG_SET: रुको until any bit in the flag is set.
 * HDQ_FLAG_CLEAR: रुको until all bits in the flag are cleared.
 * वापस 0 on success and -ETIMEDOUT in the हाल of समयout.
 */
अटल पूर्णांक hdq_रुको_क्रम_flag(काष्ठा hdq_data *hdq_data, u32 offset,
		u8 flag, u8 flag_set, u8 *status)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ समयout = jअगरfies + OMAP_HDQ_TIMEOUT;

	अगर (flag_set == OMAP_HDQ_FLAG_CLEAR) अणु
		/* रुको क्रम the flag clear */
		जबतक (((*status = hdq_reg_in(hdq_data, offset)) & flag)
			&& समय_beक्रमe(jअगरfies, समयout)) अणु
			schedule_समयout_unपूर्णांकerruptible(1);
		पूर्ण
		अगर (*status & flag)
			ret = -ETIMEDOUT;
	पूर्ण अन्यथा अगर (flag_set == OMAP_HDQ_FLAG_SET) अणु
		/* रुको क्रम the flag set */
		जबतक (!((*status = hdq_reg_in(hdq_data, offset)) & flag)
			&& समय_beक्रमe(jअगरfies, समयout)) अणु
			schedule_समयout_unपूर्णांकerruptible(1);
		पूर्ण
		अगर (!(*status & flag))
			ret = -ETIMEDOUT;
	पूर्ण अन्यथा
		वापस -EINVAL;

	वापस ret;
पूर्ण

/* Clear saved irqstatus after using an पूर्णांकerrupt */
अटल u8 hdq_reset_irqstatus(काष्ठा hdq_data *hdq_data, u8 bits)
अणु
	अचिन्हित दीर्घ irqflags;
	u8 status;

	spin_lock_irqsave(&hdq_data->hdq_spinlock, irqflags);
	status = hdq_data->hdq_irqstatus;
	/* this is a पढ़ो-modअगरy-ग_लिखो */
	hdq_data->hdq_irqstatus &= ~bits;
	spin_unlock_irqrestore(&hdq_data->hdq_spinlock, irqflags);

	वापस status;
पूर्ण

/* ग_लिखो out a byte and fill *status with HDQ_INT_STATUS */
अटल पूर्णांक hdq_ग_लिखो_byte(काष्ठा hdq_data *hdq_data, u8 val, u8 *status)
अणु
	पूर्णांक ret;
	u8 पंचांगp_status;

	ret = mutex_lock_पूर्णांकerruptible(&hdq_data->hdq_mutex);
	अगर (ret < 0) अणु
		ret = -EINTR;
		जाओ rtn;
	पूर्ण

	अगर (hdq_data->hdq_irqstatus)
		dev_err(hdq_data->dev, "TX irqstatus not cleared (%02x)\n",
			hdq_data->hdq_irqstatus);

	*status = 0;

	hdq_reg_out(hdq_data, OMAP_HDQ_TX_DATA, val);

	/* set the GO bit */
	hdq_reg_merge(hdq_data, OMAP_HDQ_CTRL_STATUS, OMAP_HDQ_CTRL_STATUS_GO,
		OMAP_HDQ_CTRL_STATUS_सूची | OMAP_HDQ_CTRL_STATUS_GO);
	/* रुको क्रम the TXCOMPLETE bit */
	ret = रुको_event_समयout(hdq_रुको_queue,
		(hdq_data->hdq_irqstatus & OMAP_HDQ_INT_STATUS_TXCOMPLETE),
		OMAP_HDQ_TIMEOUT);
	*status = hdq_reset_irqstatus(hdq_data, OMAP_HDQ_INT_STATUS_TXCOMPLETE);
	अगर (ret == 0) अणु
		dev_dbg(hdq_data->dev, "TX wait elapsed\n");
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	/* check irqstatus */
	अगर (!(*status & OMAP_HDQ_INT_STATUS_TXCOMPLETE)) अणु
		dev_dbg(hdq_data->dev, "timeout waiting for"
			" TXCOMPLETE/RXCOMPLETE, %x\n", *status);
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	/* रुको क्रम the GO bit वापस to zero */
	ret = hdq_रुको_क्रम_flag(hdq_data, OMAP_HDQ_CTRL_STATUS,
			OMAP_HDQ_CTRL_STATUS_GO,
			OMAP_HDQ_FLAG_CLEAR, &पंचांगp_status);
	अगर (ret) अणु
		dev_dbg(hdq_data->dev, "timeout waiting GO bit"
			" return to zero, %x\n", पंचांगp_status);
	पूर्ण

out:
	mutex_unlock(&hdq_data->hdq_mutex);
rtn:
	वापस ret;
पूर्ण

/* HDQ Interrupt service routine */
अटल irqवापस_t hdq_isr(पूर्णांक irq, व्योम *_hdq)
अणु
	काष्ठा hdq_data *hdq_data = _hdq;
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&hdq_data->hdq_spinlock, irqflags);
	hdq_data->hdq_irqstatus |= hdq_reg_in(hdq_data, OMAP_HDQ_INT_STATUS);
	spin_unlock_irqrestore(&hdq_data->hdq_spinlock, irqflags);
	dev_dbg(hdq_data->dev, "hdq_isr: %x\n", hdq_data->hdq_irqstatus);

	अगर (hdq_data->hdq_irqstatus &
		(OMAP_HDQ_INT_STATUS_TXCOMPLETE | OMAP_HDQ_INT_STATUS_RXCOMPLETE
		| OMAP_HDQ_INT_STATUS_TIMEOUT)) अणु
		/* wake up sleeping process */
		wake_up(&hdq_रुको_queue);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/* W1 search callback function  in HDQ mode */
अटल व्योम omap_w1_search_bus(व्योम *_hdq, काष्ठा w1_master *master_dev,
		u8 search_type, w1_slave_found_callback slave_found)
अणु
	u64 module_id, rn_le, cs, id;

	अगर (w1_id)
		module_id = w1_id;
	अन्यथा
		module_id = 0x1;

	rn_le = cpu_to_le64(module_id);
	/*
	 * HDQ might not obey truly the 1-wire spec.
	 * So calculate CRC based on module parameter.
	 */
	cs = w1_calc_crc8((u8 *)&rn_le, 7);
	id = (cs << 56) | module_id;

	slave_found(master_dev, id);
पूर्ण

/* Issue अवरोध pulse to the device */
अटल पूर्णांक omap_hdq_अवरोध(काष्ठा hdq_data *hdq_data)
अणु
	पूर्णांक ret = 0;
	u8 पंचांगp_status;

	ret = mutex_lock_पूर्णांकerruptible(&hdq_data->hdq_mutex);
	अगर (ret < 0) अणु
		dev_dbg(hdq_data->dev, "Could not acquire mutex\n");
		ret = -EINTR;
		जाओ rtn;
	पूर्ण

	अगर (hdq_data->hdq_irqstatus)
		dev_err(hdq_data->dev, "break irqstatus not cleared (%02x)\n",
			hdq_data->hdq_irqstatus);

	/* set the INIT and GO bit */
	hdq_reg_merge(hdq_data, OMAP_HDQ_CTRL_STATUS,
		OMAP_HDQ_CTRL_STATUS_INITIALIZATION | OMAP_HDQ_CTRL_STATUS_GO,
		OMAP_HDQ_CTRL_STATUS_सूची | OMAP_HDQ_CTRL_STATUS_INITIALIZATION |
		OMAP_HDQ_CTRL_STATUS_GO);

	/* रुको क्रम the TIMEOUT bit */
	ret = रुको_event_समयout(hdq_रुको_queue,
		(hdq_data->hdq_irqstatus & OMAP_HDQ_INT_STATUS_TIMEOUT),
		OMAP_HDQ_TIMEOUT);
	पंचांगp_status = hdq_reset_irqstatus(hdq_data, OMAP_HDQ_INT_STATUS_TIMEOUT);
	अगर (ret == 0) अणु
		dev_dbg(hdq_data->dev, "break wait elapsed\n");
		ret = -EINTR;
		जाओ out;
	पूर्ण

	/* check irqstatus */
	अगर (!(पंचांगp_status & OMAP_HDQ_INT_STATUS_TIMEOUT)) अणु
		dev_dbg(hdq_data->dev, "timeout waiting for TIMEOUT, %x\n",
			पंचांगp_status);
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	/*
	 * check क्रम the presence detect bit to get
	 * set to show that the slave is responding
	 */
	अगर (!(hdq_reg_in(hdq_data, OMAP_HDQ_CTRL_STATUS) &
			OMAP_HDQ_CTRL_STATUS_PRESENCE)) अणु
		dev_dbg(hdq_data->dev, "Presence bit not set\n");
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	/*
	 * रुको क्रम both INIT and GO bits rerurn to zero.
	 * zero रुको समय expected क्रम पूर्णांकerrupt mode.
	 */
	ret = hdq_रुको_क्रम_flag(hdq_data, OMAP_HDQ_CTRL_STATUS,
			OMAP_HDQ_CTRL_STATUS_INITIALIZATION |
			OMAP_HDQ_CTRL_STATUS_GO, OMAP_HDQ_FLAG_CLEAR,
			&पंचांगp_status);
	अगर (ret)
		dev_dbg(hdq_data->dev, "timeout waiting INIT&GO bits"
			" return to zero, %x\n", पंचांगp_status);

out:
	mutex_unlock(&hdq_data->hdq_mutex);
rtn:
	वापस ret;
पूर्ण

अटल पूर्णांक hdq_पढ़ो_byte(काष्ठा hdq_data *hdq_data, u8 *val)
अणु
	पूर्णांक ret = 0;
	u8 status;

	ret = mutex_lock_पूर्णांकerruptible(&hdq_data->hdq_mutex);
	अगर (ret < 0) अणु
		ret = -EINTR;
		जाओ rtn;
	पूर्ण

	अगर (pm_runसमय_suspended(hdq_data->dev)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!(hdq_data->hdq_irqstatus & OMAP_HDQ_INT_STATUS_RXCOMPLETE)) अणु
		hdq_reg_merge(hdq_data, OMAP_HDQ_CTRL_STATUS,
			OMAP_HDQ_CTRL_STATUS_सूची | OMAP_HDQ_CTRL_STATUS_GO,
			OMAP_HDQ_CTRL_STATUS_सूची | OMAP_HDQ_CTRL_STATUS_GO);
		/*
		 * The RX comes immediately after TX.
		 */
		रुको_event_समयout(hdq_रुको_queue,
				   (hdq_data->hdq_irqstatus
				    & (OMAP_HDQ_INT_STATUS_RXCOMPLETE |
				       OMAP_HDQ_INT_STATUS_TIMEOUT)),
				   OMAP_HDQ_TIMEOUT);
		status = hdq_reset_irqstatus(hdq_data,
					     OMAP_HDQ_INT_STATUS_RXCOMPLETE |
					     OMAP_HDQ_INT_STATUS_TIMEOUT);
		hdq_reg_merge(hdq_data, OMAP_HDQ_CTRL_STATUS, 0,
			OMAP_HDQ_CTRL_STATUS_सूची);

		/* check irqstatus */
		अगर (!(status & OMAP_HDQ_INT_STATUS_RXCOMPLETE)) अणु
			dev_dbg(hdq_data->dev, "timeout waiting for"
				" RXCOMPLETE, %x", status);
			ret = -ETIMEDOUT;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु /* पूर्णांकerrupt had occurred beक्रमe hdq_पढ़ो_byte was called */
		hdq_reset_irqstatus(hdq_data, OMAP_HDQ_INT_STATUS_RXCOMPLETE);
	पूर्ण
	/* the data is पढ़ोy. Read it in! */
	*val = hdq_reg_in(hdq_data, OMAP_HDQ_RX_DATA);
out:
	mutex_unlock(&hdq_data->hdq_mutex);
rtn:
	वापस ret;

पूर्ण

/*
 * W1 triplet callback function - used क्रम searching ROM addresses.
 * Registered only when controller is in 1-wire mode.
 */
अटल u8 omap_w1_triplet(व्योम *_hdq, u8 bdir)
अणु
	u8 id_bit, comp_bit;
	पूर्णांक err;
	u8 ret = 0x3; /* no slaves responded */
	काष्ठा hdq_data *hdq_data = _hdq;
	u8 ctrl = OMAP_HDQ_CTRL_STATUS_SINGLE | OMAP_HDQ_CTRL_STATUS_GO |
		  OMAP_HDQ_CTRL_STATUS_INTERRUPTMASK;
	u8 mask = ctrl | OMAP_HDQ_CTRL_STATUS_सूची;

	err = pm_runसमय_get_sync(hdq_data->dev);
	अगर (err < 0) अणु
		pm_runसमय_put_noidle(hdq_data->dev);

		वापस err;
	पूर्ण

	err = mutex_lock_पूर्णांकerruptible(&hdq_data->hdq_mutex);
	अगर (err < 0) अणु
		dev_dbg(hdq_data->dev, "Could not acquire mutex\n");
		जाओ rtn;
	पूर्ण

	/* पढ़ो id_bit */
	hdq_reg_merge(_hdq, OMAP_HDQ_CTRL_STATUS,
		      ctrl | OMAP_HDQ_CTRL_STATUS_सूची, mask);
	err = रुको_event_समयout(hdq_रुको_queue,
				 (hdq_data->hdq_irqstatus
				  & OMAP_HDQ_INT_STATUS_RXCOMPLETE),
				 OMAP_HDQ_TIMEOUT);
	/* Must clear irqstatus क्रम another RXCOMPLETE पूर्णांकerrupt */
	hdq_reset_irqstatus(hdq_data, OMAP_HDQ_INT_STATUS_RXCOMPLETE);

	अगर (err == 0) अणु
		dev_dbg(hdq_data->dev, "RX wait elapsed\n");
		जाओ out;
	पूर्ण
	id_bit = (hdq_reg_in(_hdq, OMAP_HDQ_RX_DATA) & 0x01);

	/* पढ़ो comp_bit */
	hdq_reg_merge(_hdq, OMAP_HDQ_CTRL_STATUS,
		      ctrl | OMAP_HDQ_CTRL_STATUS_सूची, mask);
	err = रुको_event_समयout(hdq_रुको_queue,
				 (hdq_data->hdq_irqstatus
				  & OMAP_HDQ_INT_STATUS_RXCOMPLETE),
				 OMAP_HDQ_TIMEOUT);
	/* Must clear irqstatus क्रम another RXCOMPLETE पूर्णांकerrupt */
	hdq_reset_irqstatus(hdq_data, OMAP_HDQ_INT_STATUS_RXCOMPLETE);

	अगर (err == 0) अणु
		dev_dbg(hdq_data->dev, "RX wait elapsed\n");
		जाओ out;
	पूर्ण
	comp_bit = (hdq_reg_in(_hdq, OMAP_HDQ_RX_DATA) & 0x01);

	अगर (id_bit && comp_bit) अणु
		ret = 0x03;  /* no slaves responded */
		जाओ out;
	पूर्ण
	अगर (!id_bit && !comp_bit) अणु
		/* Both bits are valid, take the direction given */
		ret = bdir ? 0x04 : 0;
	पूर्ण अन्यथा अणु
		/* Only one bit is valid, take that direction */
		bdir = id_bit;
		ret = id_bit ? 0x05 : 0x02;
	पूर्ण

	/* ग_लिखो bdir bit */
	hdq_reg_out(_hdq, OMAP_HDQ_TX_DATA, bdir);
	hdq_reg_merge(_hdq, OMAP_HDQ_CTRL_STATUS, ctrl, mask);
	err = रुको_event_समयout(hdq_रुको_queue,
				 (hdq_data->hdq_irqstatus
				  & OMAP_HDQ_INT_STATUS_TXCOMPLETE),
				 OMAP_HDQ_TIMEOUT);
	/* Must clear irqstatus क्रम another TXCOMPLETE पूर्णांकerrupt */
	hdq_reset_irqstatus(hdq_data, OMAP_HDQ_INT_STATUS_TXCOMPLETE);

	अगर (err == 0) अणु
		dev_dbg(hdq_data->dev, "TX wait elapsed\n");
		जाओ out;
	पूर्ण

	hdq_reg_merge(_hdq, OMAP_HDQ_CTRL_STATUS, 0,
		      OMAP_HDQ_CTRL_STATUS_SINGLE);

out:
	mutex_unlock(&hdq_data->hdq_mutex);
rtn:
	pm_runसमय_mark_last_busy(hdq_data->dev);
	pm_runसमय_put_स्वतःsuspend(hdq_data->dev);

	वापस ret;
पूर्ण

/* reset callback */
अटल u8 omap_w1_reset_bus(व्योम *_hdq)
अणु
	काष्ठा hdq_data *hdq_data = _hdq;
	पूर्णांक err;

	err = pm_runसमय_get_sync(hdq_data->dev);
	अगर (err < 0) अणु
		pm_runसमय_put_noidle(hdq_data->dev);

		वापस err;
	पूर्ण

	omap_hdq_अवरोध(hdq_data);

	pm_runसमय_mark_last_busy(hdq_data->dev);
	pm_runसमय_put_स्वतःsuspend(hdq_data->dev);

	वापस 0;
पूर्ण

/* Read a byte of data from the device */
अटल u8 omap_w1_पढ़ो_byte(व्योम *_hdq)
अणु
	काष्ठा hdq_data *hdq_data = _hdq;
	u8 val = 0;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(hdq_data->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(hdq_data->dev);

		वापस -1;
	पूर्ण

	ret = hdq_पढ़ो_byte(hdq_data, &val);
	अगर (ret)
		val = -1;

	pm_runसमय_mark_last_busy(hdq_data->dev);
	pm_runसमय_put_स्वतःsuspend(hdq_data->dev);

	वापस val;
पूर्ण

/* Write a byte of data to the device */
अटल व्योम omap_w1_ग_लिखो_byte(व्योम *_hdq, u8 byte)
अणु
	काष्ठा hdq_data *hdq_data = _hdq;
	पूर्णांक ret;
	u8 status;

	ret = pm_runसमय_get_sync(hdq_data->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(hdq_data->dev);

		वापस;
	पूर्ण

	/*
	 * We need to reset the slave beक्रमe
	 * issuing the SKIP ROM command, अन्यथा
	 * the slave will not work.
	 */
	अगर (byte == W1_SKIP_ROM)
		omap_hdq_अवरोध(hdq_data);

	ret = hdq_ग_लिखो_byte(hdq_data, byte, &status);
	अगर (ret < 0) अणु
		dev_dbg(hdq_data->dev, "TX failure:Ctrl status %x\n", status);
		जाओ out_err;
	पूर्ण

out_err:
	pm_runसमय_mark_last_busy(hdq_data->dev);
	pm_runसमय_put_स्वतःsuspend(hdq_data->dev);
पूर्ण

अटल काष्ठा w1_bus_master omap_w1_master = अणु
	.पढ़ो_byte	= omap_w1_पढ़ो_byte,
	.ग_लिखो_byte	= omap_w1_ग_लिखो_byte,
	.reset_bus	= omap_w1_reset_bus,
पूर्ण;

अटल पूर्णांक __maybe_unused omap_hdq_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा hdq_data *hdq_data = dev_get_drvdata(dev);

	hdq_reg_out(hdq_data, 0, hdq_data->mode);
	hdq_reg_in(hdq_data, OMAP_HDQ_INT_STATUS);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused omap_hdq_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा hdq_data *hdq_data = dev_get_drvdata(dev);

	/* select HDQ/1W mode & enable घड़ीs */
	hdq_reg_out(hdq_data, OMAP_HDQ_CTRL_STATUS,
		    OMAP_HDQ_CTRL_STATUS_CLOCKENABLE |
		    OMAP_HDQ_CTRL_STATUS_INTERRUPTMASK |
		    hdq_data->mode);
	hdq_reg_in(hdq_data, OMAP_HDQ_INT_STATUS);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops omap_hdq_pm_ops = अणु
	SET_RUNTIME_PM_OPS(omap_hdq_runसमय_suspend,
			   omap_hdq_runसमय_resume, शून्य)
पूर्ण;

अटल पूर्णांक omap_hdq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा hdq_data *hdq_data;
	पूर्णांक ret, irq;
	u8 rev;
	स्थिर अक्षर *mode;

	hdq_data = devm_kzalloc(dev, माप(*hdq_data), GFP_KERNEL);
	अगर (!hdq_data) अणु
		dev_dbg(&pdev->dev, "unable to allocate memory\n");
		वापस -ENOMEM;
	पूर्ण

	hdq_data->dev = dev;
	platक्रमm_set_drvdata(pdev, hdq_data);

	hdq_data->hdq_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(hdq_data->hdq_base))
		वापस PTR_ERR(hdq_data->hdq_base);

	mutex_init(&hdq_data->hdq_mutex);

	ret = of_property_पढ़ो_string(pdev->dev.of_node, "ti,mode", &mode);
	अगर (ret < 0 || !म_भेद(mode, "hdq")) अणु
		hdq_data->mode = 0;
		omap_w1_master.search = omap_w1_search_bus;
	पूर्ण अन्यथा अणु
		hdq_data->mode = 1;
		omap_w1_master.triplet = omap_w1_triplet;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, 300);
	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(&pdev->dev);
		dev_dbg(&pdev->dev, "pm_runtime_get_sync failed\n");
		जाओ err_w1;
	पूर्ण

	rev = hdq_reg_in(hdq_data, OMAP_HDQ_REVISION);
	dev_info(&pdev->dev, "OMAP HDQ Hardware Rev %c.%c. Driver in %s mode\n",
		(rev >> 4) + '0', (rev & 0x0f) + '0', "Interrupt");

	spin_lock_init(&hdq_data->hdq_spinlock);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq	< 0) अणु
		dev_dbg(&pdev->dev, "Failed to get IRQ: %d\n", irq);
		ret = irq;
		जाओ err_irq;
	पूर्ण

	ret = devm_request_irq(dev, irq, hdq_isr, 0, "omap_hdq", hdq_data);
	अगर (ret < 0) अणु
		dev_dbg(&pdev->dev, "could not request irq\n");
		जाओ err_irq;
	पूर्ण

	omap_hdq_अवरोध(hdq_data);

	pm_runसमय_mark_last_busy(&pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&pdev->dev);

	omap_w1_master.data = hdq_data;

	ret = w1_add_master_device(&omap_w1_master);
	अगर (ret) अणु
		dev_dbg(&pdev->dev, "Failure in registering w1 master\n");
		जाओ err_w1;
	पूर्ण

	वापस 0;

err_irq:
	pm_runसमय_put_sync(&pdev->dev);
err_w1:
	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक omap_hdq_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक active;

	active = pm_runसमय_get_sync(&pdev->dev);
	अगर (active < 0)
		pm_runसमय_put_noidle(&pdev->dev);

	w1_हटाओ_master_device(&omap_w1_master);

	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);
	अगर (active >= 0)
		pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id omap_hdq_dt_ids[] = अणु
	अणु .compatible = "ti,omap3-1w" पूर्ण,
	अणु .compatible = "ti,am4372-hdq" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_hdq_dt_ids);

अटल काष्ठा platक्रमm_driver omap_hdq_driver = अणु
	.probe = omap_hdq_probe,
	.हटाओ = omap_hdq_हटाओ,
	.driver = अणु
		.name =	"omap_hdq",
		.of_match_table = omap_hdq_dt_ids,
		.pm = &omap_hdq_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(omap_hdq_driver);

MODULE_AUTHOR("Texas Instruments");
MODULE_DESCRIPTION("HDQ-1W driver Library");
MODULE_LICENSE("GPL");
