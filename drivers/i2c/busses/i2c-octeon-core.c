<शैली गुरु>
/*
 * (C) Copyright 2009-2010
 * Nokia Siemens Networks, michael.lawnick.ext@nsn.com
 *
 * Portions Copyright (C) 2010 - 2016 Cavium, Inc.
 *
 * This file contains the shared part of the driver क्रम the i2c adapter in
 * Cavium Networks' OCTEON processors and ThunderX SOCs.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश "i2c-octeon-core.h"

/* पूर्णांकerrupt service routine */
irqवापस_t octeon_i2c_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा octeon_i2c *i2c = dev_id;

	i2c->पूर्णांक_disable(i2c);
	wake_up(&i2c->queue);

	वापस IRQ_HANDLED;
पूर्ण

अटल bool octeon_i2c_test_अगरlg(काष्ठा octeon_i2c *i2c)
अणु
	वापस (octeon_i2c_ctl_पढ़ो(i2c) & TWSI_CTL_IFLG);
पूर्ण

/**
 * octeon_i2c_रुको - रुको क्रम the IFLG to be set
 * @i2c: The काष्ठा octeon_i2c
 *
 * Returns 0 on success, otherwise a negative त्रुटि_सं.
 */
अटल पूर्णांक octeon_i2c_रुको(काष्ठा octeon_i2c *i2c)
अणु
	दीर्घ समय_left;

	/*
	 * Some chip revisions करोn't निश्चित the irq in the पूर्णांकerrupt
	 * controller. So we must poll क्रम the IFLG change.
	 */
	अगर (i2c->broken_irq_mode) अणु
		u64 end = get_jअगरfies_64() + i2c->adap.समयout;

		जबतक (!octeon_i2c_test_अगरlg(i2c) &&
		       समय_beक्रमe64(get_jअगरfies_64(), end))
			usleep_range(I2C_OCTEON_EVENT_WAIT / 2, I2C_OCTEON_EVENT_WAIT);

		वापस octeon_i2c_test_अगरlg(i2c) ? 0 : -ETIMEDOUT;
	पूर्ण

	i2c->पूर्णांक_enable(i2c);
	समय_left = रुको_event_समयout(i2c->queue, octeon_i2c_test_अगरlg(i2c),
				       i2c->adap.समयout);
	i2c->पूर्णांक_disable(i2c);

	अगर (i2c->broken_irq_check && !समय_left &&
	    octeon_i2c_test_अगरlg(i2c)) अणु
		dev_err(i2c->dev, "broken irq connection detected, switching to polling mode.\n");
		i2c->broken_irq_mode = true;
		वापस 0;
	पूर्ण

	अगर (!समय_left)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल bool octeon_i2c_hlc_test_valid(काष्ठा octeon_i2c *i2c)
अणु
	वापस (__raw_पढ़ोq(i2c->twsi_base + SW_TWSI(i2c)) & SW_TWSI_V) == 0;
पूर्ण

अटल व्योम octeon_i2c_hlc_पूर्णांक_clear(काष्ठा octeon_i2c *i2c)
अणु
	/* clear ST/TS events, listen क्रम neither */
	octeon_i2c_ग_लिखो_पूर्णांक(i2c, TWSI_INT_ST_INT | TWSI_INT_TS_INT);
पूर्ण

/*
 * Cleanup low-level state & enable high-level controller.
 */
अटल व्योम octeon_i2c_hlc_enable(काष्ठा octeon_i2c *i2c)
अणु
	पूर्णांक try = 0;
	u64 val;

	अगर (i2c->hlc_enabled)
		वापस;
	i2c->hlc_enabled = true;

	जबतक (1) अणु
		val = octeon_i2c_ctl_पढ़ो(i2c);
		अगर (!(val & (TWSI_CTL_STA | TWSI_CTL_STP)))
			अवरोध;

		/* clear IFLG event */
		अगर (val & TWSI_CTL_IFLG)
			octeon_i2c_ctl_ग_लिखो(i2c, TWSI_CTL_ENAB);

		अगर (try++ > 100) अणु
			pr_err("%s: giving up\n", __func__);
			अवरोध;
		पूर्ण

		/* spin until any start/stop has finished */
		udelay(10);
	पूर्ण
	octeon_i2c_ctl_ग_लिखो(i2c, TWSI_CTL_CE | TWSI_CTL_AAK | TWSI_CTL_ENAB);
पूर्ण

अटल व्योम octeon_i2c_hlc_disable(काष्ठा octeon_i2c *i2c)
अणु
	अगर (!i2c->hlc_enabled)
		वापस;

	i2c->hlc_enabled = false;
	octeon_i2c_ctl_ग_लिखो(i2c, TWSI_CTL_ENAB);
पूर्ण

/**
 * octeon_i2c_hlc_रुको - रुको क्रम an HLC operation to complete
 * @i2c: The काष्ठा octeon_i2c
 *
 * Returns 0 on success, otherwise -ETIMEDOUT.
 */
अटल पूर्णांक octeon_i2c_hlc_रुको(काष्ठा octeon_i2c *i2c)
अणु
	पूर्णांक समय_left;

	/*
	 * Some cn38xx boards करोn't निश्चित the irq in the पूर्णांकerrupt
	 * controller. So we must poll क्रम the valid bit change.
	 */
	अगर (i2c->broken_irq_mode) अणु
		u64 end = get_jअगरfies_64() + i2c->adap.समयout;

		जबतक (!octeon_i2c_hlc_test_valid(i2c) &&
		       समय_beक्रमe64(get_jअगरfies_64(), end))
			usleep_range(I2C_OCTEON_EVENT_WAIT / 2, I2C_OCTEON_EVENT_WAIT);

		वापस octeon_i2c_hlc_test_valid(i2c) ? 0 : -ETIMEDOUT;
	पूर्ण

	i2c->hlc_पूर्णांक_enable(i2c);
	समय_left = रुको_event_समयout(i2c->queue,
				       octeon_i2c_hlc_test_valid(i2c),
				       i2c->adap.समयout);
	i2c->hlc_पूर्णांक_disable(i2c);
	अगर (!समय_left)
		octeon_i2c_hlc_पूर्णांक_clear(i2c);

	अगर (i2c->broken_irq_check && !समय_left &&
	    octeon_i2c_hlc_test_valid(i2c)) अणु
		dev_err(i2c->dev, "broken irq connection detected, switching to polling mode.\n");
		i2c->broken_irq_mode = true;
		वापस 0;
	पूर्ण

	अगर (!समय_left)
		वापस -ETIMEDOUT;
	वापस 0;
पूर्ण

अटल पूर्णांक octeon_i2c_check_status(काष्ठा octeon_i2c *i2c, पूर्णांक final_पढ़ो)
अणु
	u8 stat;

	/*
	 * This is ugly... in HLC mode the status is not in the status रेजिस्टर
	 * but in the lower 8 bits of SW_TWSI.
	 */
	अगर (i2c->hlc_enabled)
		stat = __raw_पढ़ोq(i2c->twsi_base + SW_TWSI(i2c));
	अन्यथा
		stat = octeon_i2c_stat_पढ़ो(i2c);

	चयन (stat) अणु
	/* Everything is fine */
	हाल STAT_IDLE:
	हाल STAT_AD2W_ACK:
	हाल STAT_RXADDR_ACK:
	हाल STAT_TXADDR_ACK:
	हाल STAT_TXDATA_ACK:
		वापस 0;

	/* ACK allowed on pre-terminal bytes only */
	हाल STAT_RXDATA_ACK:
		अगर (!final_पढ़ो)
			वापस 0;
		वापस -EIO;

	/* NAK allowed on terminal byte only */
	हाल STAT_RXDATA_NAK:
		अगर (final_पढ़ो)
			वापस 0;
		वापस -EIO;

	/* Arbitration lost */
	हाल STAT_LOST_ARB_38:
	हाल STAT_LOST_ARB_68:
	हाल STAT_LOST_ARB_78:
	हाल STAT_LOST_ARB_B0:
		वापस -EAGAIN;

	/* Being addressed as slave, should back off & listen */
	हाल STAT_SLAVE_60:
	हाल STAT_SLAVE_70:
	हाल STAT_GENDATA_ACK:
	हाल STAT_GENDATA_NAK:
		वापस -EOPNOTSUPP;

	/* Core busy as slave */
	हाल STAT_SLAVE_80:
	हाल STAT_SLAVE_88:
	हाल STAT_SLAVE_A0:
	हाल STAT_SLAVE_A8:
	हाल STAT_SLAVE_LOST:
	हाल STAT_SLAVE_NAK:
	हाल STAT_SLAVE_ACK:
		वापस -EOPNOTSUPP;

	हाल STAT_TXDATA_NAK:
	हाल STAT_BUS_ERROR:
		वापस -EIO;
	हाल STAT_TXADDR_NAK:
	हाल STAT_RXADDR_NAK:
	हाल STAT_AD2W_NAK:
		वापस -ENXIO;
	शेष:
		dev_err(i2c->dev, "unhandled state: %d\n", stat);
		वापस -EIO;
	पूर्ण
पूर्ण

अटल पूर्णांक octeon_i2c_recovery(काष्ठा octeon_i2c *i2c)
अणु
	पूर्णांक ret;

	ret = i2c_recover_bus(&i2c->adap);
	अगर (ret)
		/* recover failed, try hardware re-init */
		ret = octeon_i2c_init_lowlevel(i2c);
	वापस ret;
पूर्ण

/**
 * octeon_i2c_start - send START to the bus
 * @i2c: The काष्ठा octeon_i2c
 *
 * Returns 0 on success, otherwise a negative त्रुटि_सं.
 */
अटल पूर्णांक octeon_i2c_start(काष्ठा octeon_i2c *i2c)
अणु
	पूर्णांक ret;
	u8 stat;

	octeon_i2c_hlc_disable(i2c);

	octeon_i2c_ctl_ग_लिखो(i2c, TWSI_CTL_ENAB | TWSI_CTL_STA);
	ret = octeon_i2c_रुको(i2c);
	अगर (ret)
		जाओ error;

	stat = octeon_i2c_stat_पढ़ो(i2c);
	अगर (stat == STAT_START || stat == STAT_REP_START)
		/* START successful, bail out */
		वापस 0;

error:
	/* START failed, try to recover */
	ret = octeon_i2c_recovery(i2c);
	वापस (ret) ? ret : -EAGAIN;
पूर्ण

/* send STOP to the bus */
अटल व्योम octeon_i2c_stop(काष्ठा octeon_i2c *i2c)
अणु
	octeon_i2c_ctl_ग_लिखो(i2c, TWSI_CTL_ENAB | TWSI_CTL_STP);
पूर्ण

/**
 * octeon_i2c_पढ़ो - receive data from the bus via low-level controller
 * @i2c: The काष्ठा octeon_i2c
 * @target: Target address
 * @data: Poपूर्णांकer to the location to store the data
 * @rlength: Length of the data
 * @recv_len: flag क्रम length byte
 *
 * The address is sent over the bus, then the data is पढ़ो.
 *
 * Returns 0 on success, otherwise a negative त्रुटि_सं.
 */
अटल पूर्णांक octeon_i2c_पढ़ो(काष्ठा octeon_i2c *i2c, पूर्णांक target,
			   u8 *data, u16 *rlength, bool recv_len)
अणु
	पूर्णांक i, result, length = *rlength;
	bool final_पढ़ो = false;

	octeon_i2c_data_ग_लिखो(i2c, (target << 1) | 1);
	octeon_i2c_ctl_ग_लिखो(i2c, TWSI_CTL_ENAB);

	result = octeon_i2c_रुको(i2c);
	अगर (result)
		वापस result;

	/* address OK ? */
	result = octeon_i2c_check_status(i2c, false);
	अगर (result)
		वापस result;

	क्रम (i = 0; i < length; i++) अणु
		/*
		 * For the last byte to receive TWSI_CTL_AAK must not be set.
		 *
		 * A special हाल is I2C_M_RECV_LEN where we करोn't know the
		 * additional length yet. If recv_len is set we assume we're
		 * not पढ़ोing the final byte and thereक्रमe need to set
		 * TWSI_CTL_AAK.
		 */
		अगर ((i + 1 == length) && !(recv_len && i == 0))
			final_पढ़ो = true;

		/* clear अगरlg to allow next event */
		अगर (final_पढ़ो)
			octeon_i2c_ctl_ग_लिखो(i2c, TWSI_CTL_ENAB);
		अन्यथा
			octeon_i2c_ctl_ग_लिखो(i2c, TWSI_CTL_ENAB | TWSI_CTL_AAK);

		result = octeon_i2c_रुको(i2c);
		अगर (result)
			वापस result;

		data[i] = octeon_i2c_data_पढ़ो(i2c, &result);
		अगर (result)
			वापस result;
		अगर (recv_len && i == 0) अणु
			अगर (data[i] > I2C_SMBUS_BLOCK_MAX)
				वापस -EPROTO;
			length += data[i];
		पूर्ण

		result = octeon_i2c_check_status(i2c, final_पढ़ो);
		अगर (result)
			वापस result;
	पूर्ण
	*rlength = length;
	वापस 0;
पूर्ण

/**
 * octeon_i2c_ग_लिखो - send data to the bus via low-level controller
 * @i2c: The काष्ठा octeon_i2c
 * @target: Target address
 * @data: Poपूर्णांकer to the data to be sent
 * @length: Length of the data
 *
 * The address is sent over the bus, then the data.
 *
 * Returns 0 on success, otherwise a negative त्रुटि_सं.
 */
अटल पूर्णांक octeon_i2c_ग_लिखो(काष्ठा octeon_i2c *i2c, पूर्णांक target,
			    स्थिर u8 *data, पूर्णांक length)
अणु
	पूर्णांक i, result;

	octeon_i2c_data_ग_लिखो(i2c, target << 1);
	octeon_i2c_ctl_ग_लिखो(i2c, TWSI_CTL_ENAB);

	result = octeon_i2c_रुको(i2c);
	अगर (result)
		वापस result;

	क्रम (i = 0; i < length; i++) अणु
		result = octeon_i2c_check_status(i2c, false);
		अगर (result)
			वापस result;

		octeon_i2c_data_ग_लिखो(i2c, data[i]);
		octeon_i2c_ctl_ग_लिखो(i2c, TWSI_CTL_ENAB);

		result = octeon_i2c_रुको(i2c);
		अगर (result)
			वापस result;
	पूर्ण

	वापस 0;
पूर्ण

/* high-level-controller pure पढ़ो of up to 8 bytes */
अटल पूर्णांक octeon_i2c_hlc_पढ़ो(काष्ठा octeon_i2c *i2c, काष्ठा i2c_msg *msgs)
अणु
	पूर्णांक i, j, ret = 0;
	u64 cmd;

	octeon_i2c_hlc_enable(i2c);
	octeon_i2c_hlc_पूर्णांक_clear(i2c);

	cmd = SW_TWSI_V | SW_TWSI_R | SW_TWSI_SOVR;
	/* SIZE */
	cmd |= (u64)(msgs[0].len - 1) << SW_TWSI_SIZE_SHIFT;
	/* A */
	cmd |= (u64)(msgs[0].addr & 0x7full) << SW_TWSI_ADDR_SHIFT;

	अगर (msgs[0].flags & I2C_M_TEN)
		cmd |= SW_TWSI_OP_10;
	अन्यथा
		cmd |= SW_TWSI_OP_7;

	octeon_i2c_ग_लिखोq_flush(cmd, i2c->twsi_base + SW_TWSI(i2c));
	ret = octeon_i2c_hlc_रुको(i2c);
	अगर (ret)
		जाओ err;

	cmd = __raw_पढ़ोq(i2c->twsi_base + SW_TWSI(i2c));
	अगर ((cmd & SW_TWSI_R) == 0)
		वापस octeon_i2c_check_status(i2c, false);

	क्रम (i = 0, j = msgs[0].len - 1; i  < msgs[0].len && i < 4; i++, j--)
		msgs[0].buf[j] = (cmd >> (8 * i)) & 0xff;

	अगर (msgs[0].len > 4) अणु
		cmd = __raw_पढ़ोq(i2c->twsi_base + SW_TWSI_EXT(i2c));
		क्रम (i = 0; i  < msgs[0].len - 4 && i < 4; i++, j--)
			msgs[0].buf[j] = (cmd >> (8 * i)) & 0xff;
	पूर्ण

err:
	वापस ret;
पूर्ण

/* high-level-controller pure ग_लिखो of up to 8 bytes */
अटल पूर्णांक octeon_i2c_hlc_ग_लिखो(काष्ठा octeon_i2c *i2c, काष्ठा i2c_msg *msgs)
अणु
	पूर्णांक i, j, ret = 0;
	u64 cmd;

	octeon_i2c_hlc_enable(i2c);
	octeon_i2c_hlc_पूर्णांक_clear(i2c);

	cmd = SW_TWSI_V | SW_TWSI_SOVR;
	/* SIZE */
	cmd |= (u64)(msgs[0].len - 1) << SW_TWSI_SIZE_SHIFT;
	/* A */
	cmd |= (u64)(msgs[0].addr & 0x7full) << SW_TWSI_ADDR_SHIFT;

	अगर (msgs[0].flags & I2C_M_TEN)
		cmd |= SW_TWSI_OP_10;
	अन्यथा
		cmd |= SW_TWSI_OP_7;

	क्रम (i = 0, j = msgs[0].len - 1; i  < msgs[0].len && i < 4; i++, j--)
		cmd |= (u64)msgs[0].buf[j] << (8 * i);

	अगर (msgs[0].len > 4) अणु
		u64 ext = 0;

		क्रम (i = 0; i < msgs[0].len - 4 && i < 4; i++, j--)
			ext |= (u64)msgs[0].buf[j] << (8 * i);
		octeon_i2c_ग_लिखोq_flush(ext, i2c->twsi_base + SW_TWSI_EXT(i2c));
	पूर्ण

	octeon_i2c_ग_लिखोq_flush(cmd, i2c->twsi_base + SW_TWSI(i2c));
	ret = octeon_i2c_hlc_रुको(i2c);
	अगर (ret)
		जाओ err;

	cmd = __raw_पढ़ोq(i2c->twsi_base + SW_TWSI(i2c));
	अगर ((cmd & SW_TWSI_R) == 0)
		वापस octeon_i2c_check_status(i2c, false);

err:
	वापस ret;
पूर्ण

/* high-level-controller composite ग_लिखो+पढ़ो, msg0=addr, msg1=data */
अटल पूर्णांक octeon_i2c_hlc_comp_पढ़ो(काष्ठा octeon_i2c *i2c, काष्ठा i2c_msg *msgs)
अणु
	पूर्णांक i, j, ret = 0;
	u64 cmd;

	octeon_i2c_hlc_enable(i2c);

	cmd = SW_TWSI_V | SW_TWSI_R | SW_TWSI_SOVR;
	/* SIZE */
	cmd |= (u64)(msgs[1].len - 1) << SW_TWSI_SIZE_SHIFT;
	/* A */
	cmd |= (u64)(msgs[0].addr & 0x7full) << SW_TWSI_ADDR_SHIFT;

	अगर (msgs[0].flags & I2C_M_TEN)
		cmd |= SW_TWSI_OP_10_IA;
	अन्यथा
		cmd |= SW_TWSI_OP_7_IA;

	अगर (msgs[0].len == 2) अणु
		u64 ext = 0;

		cmd |= SW_TWSI_EIA;
		ext = (u64)msgs[0].buf[0] << SW_TWSI_IA_SHIFT;
		cmd |= (u64)msgs[0].buf[1] << SW_TWSI_IA_SHIFT;
		octeon_i2c_ग_लिखोq_flush(ext, i2c->twsi_base + SW_TWSI_EXT(i2c));
	पूर्ण अन्यथा अणु
		cmd |= (u64)msgs[0].buf[0] << SW_TWSI_IA_SHIFT;
	पूर्ण

	octeon_i2c_hlc_पूर्णांक_clear(i2c);
	octeon_i2c_ग_लिखोq_flush(cmd, i2c->twsi_base + SW_TWSI(i2c));

	ret = octeon_i2c_hlc_रुको(i2c);
	अगर (ret)
		जाओ err;

	cmd = __raw_पढ़ोq(i2c->twsi_base + SW_TWSI(i2c));
	अगर ((cmd & SW_TWSI_R) == 0)
		वापस octeon_i2c_check_status(i2c, false);

	क्रम (i = 0, j = msgs[1].len - 1; i  < msgs[1].len && i < 4; i++, j--)
		msgs[1].buf[j] = (cmd >> (8 * i)) & 0xff;

	अगर (msgs[1].len > 4) अणु
		cmd = __raw_पढ़ोq(i2c->twsi_base + SW_TWSI_EXT(i2c));
		क्रम (i = 0; i  < msgs[1].len - 4 && i < 4; i++, j--)
			msgs[1].buf[j] = (cmd >> (8 * i)) & 0xff;
	पूर्ण

err:
	वापस ret;
पूर्ण

/* high-level-controller composite ग_लिखो+ग_लिखो, m[0]len<=2, m[1]len<=8 */
अटल पूर्णांक octeon_i2c_hlc_comp_ग_लिखो(काष्ठा octeon_i2c *i2c, काष्ठा i2c_msg *msgs)
अणु
	bool set_ext = false;
	पूर्णांक i, j, ret = 0;
	u64 cmd, ext = 0;

	octeon_i2c_hlc_enable(i2c);

	cmd = SW_TWSI_V | SW_TWSI_SOVR;
	/* SIZE */
	cmd |= (u64)(msgs[1].len - 1) << SW_TWSI_SIZE_SHIFT;
	/* A */
	cmd |= (u64)(msgs[0].addr & 0x7full) << SW_TWSI_ADDR_SHIFT;

	अगर (msgs[0].flags & I2C_M_TEN)
		cmd |= SW_TWSI_OP_10_IA;
	अन्यथा
		cmd |= SW_TWSI_OP_7_IA;

	अगर (msgs[0].len == 2) अणु
		cmd |= SW_TWSI_EIA;
		ext |= (u64)msgs[0].buf[0] << SW_TWSI_IA_SHIFT;
		set_ext = true;
		cmd |= (u64)msgs[0].buf[1] << SW_TWSI_IA_SHIFT;
	पूर्ण अन्यथा अणु
		cmd |= (u64)msgs[0].buf[0] << SW_TWSI_IA_SHIFT;
	पूर्ण

	क्रम (i = 0, j = msgs[1].len - 1; i  < msgs[1].len && i < 4; i++, j--)
		cmd |= (u64)msgs[1].buf[j] << (8 * i);

	अगर (msgs[1].len > 4) अणु
		क्रम (i = 0; i < msgs[1].len - 4 && i < 4; i++, j--)
			ext |= (u64)msgs[1].buf[j] << (8 * i);
		set_ext = true;
	पूर्ण
	अगर (set_ext)
		octeon_i2c_ग_लिखोq_flush(ext, i2c->twsi_base + SW_TWSI_EXT(i2c));

	octeon_i2c_hlc_पूर्णांक_clear(i2c);
	octeon_i2c_ग_लिखोq_flush(cmd, i2c->twsi_base + SW_TWSI(i2c));

	ret = octeon_i2c_hlc_रुको(i2c);
	अगर (ret)
		जाओ err;

	cmd = __raw_पढ़ोq(i2c->twsi_base + SW_TWSI(i2c));
	अगर ((cmd & SW_TWSI_R) == 0)
		वापस octeon_i2c_check_status(i2c, false);

err:
	वापस ret;
पूर्ण

/**
 * octeon_i2c_xfer - The driver's master_xfer function
 * @adap: Poपूर्णांकer to the i2c_adapter काष्ठाure
 * @msgs: Poपूर्णांकer to the messages to be processed
 * @num: Length of the MSGS array
 *
 * Returns the number of messages processed, or a negative त्रुटि_सं on failure.
 */
पूर्णांक octeon_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा octeon_i2c *i2c = i2c_get_adapdata(adap);
	पूर्णांक i, ret = 0;

	अगर (num == 1) अणु
		अगर (msgs[0].len > 0 && msgs[0].len <= 8) अणु
			अगर (msgs[0].flags & I2C_M_RD)
				ret = octeon_i2c_hlc_पढ़ो(i2c, msgs);
			अन्यथा
				ret = octeon_i2c_hlc_ग_लिखो(i2c, msgs);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (num == 2) अणु
		अगर ((msgs[0].flags & I2C_M_RD) == 0 &&
		    (msgs[1].flags & I2C_M_RECV_LEN) == 0 &&
		    msgs[0].len > 0 && msgs[0].len <= 2 &&
		    msgs[1].len > 0 && msgs[1].len <= 8 &&
		    msgs[0].addr == msgs[1].addr) अणु
			अगर (msgs[1].flags & I2C_M_RD)
				ret = octeon_i2c_hlc_comp_पढ़ो(i2c, msgs);
			अन्यथा
				ret = octeon_i2c_hlc_comp_ग_लिखो(i2c, msgs);
			जाओ out;
		पूर्ण
	पूर्ण

	क्रम (i = 0; ret == 0 && i < num; i++) अणु
		काष्ठा i2c_msg *pmsg = &msgs[i];

		/* zero-length messages are not supported */
		अगर (!pmsg->len) अणु
			ret = -EOPNOTSUPP;
			अवरोध;
		पूर्ण

		ret = octeon_i2c_start(i2c);
		अगर (ret)
			वापस ret;

		अगर (pmsg->flags & I2C_M_RD)
			ret = octeon_i2c_पढ़ो(i2c, pmsg->addr, pmsg->buf,
					      &pmsg->len, pmsg->flags & I2C_M_RECV_LEN);
		अन्यथा
			ret = octeon_i2c_ग_लिखो(i2c, pmsg->addr, pmsg->buf,
					       pmsg->len);
	पूर्ण
	octeon_i2c_stop(i2c);
out:
	वापस (ret != 0) ? ret : num;
पूर्ण

/* calculate and set घड़ी भागisors */
व्योम octeon_i2c_set_घड़ी(काष्ठा octeon_i2c *i2c)
अणु
	पूर्णांक tclk, thp_base, inc, thp_idx, mभाग_idx, nभाग_idx, foscl, dअगरf;
	पूर्णांक thp = 0x18, mभाग = 2, nभाग = 0, delta_hz = 1000000;

	क्रम (nभाग_idx = 0; nभाग_idx < 8 && delta_hz != 0; nभाग_idx++) अणु
		/*
		 * An mभाग value of less than 2 seems to not work well
		 * with ds1337 RTCs, so we स्थिरrain it to larger values.
		 */
		क्रम (mभाग_idx = 15; mभाग_idx >= 2 && delta_hz != 0; mभाग_idx--) अणु
			/*
			 * For given nभाग and mभाग values check the
			 * two बंदst thp values.
			 */
			tclk = i2c->twsi_freq * (mभाग_idx + 1) * 10;
			tclk *= (1 << nभाग_idx);
			thp_base = (i2c->sys_freq / (tclk * 2)) - 1;

			क्रम (inc = 0; inc <= 1; inc++) अणु
				thp_idx = thp_base + inc;
				अगर (thp_idx < 5 || thp_idx > 0xff)
					जारी;

				foscl = i2c->sys_freq / (2 * (thp_idx + 1));
				foscl = foscl / (1 << nभाग_idx);
				foscl = foscl / (mभाग_idx + 1) / 10;
				dअगरf = असल(foscl - i2c->twsi_freq);
				अगर (dअगरf < delta_hz) अणु
					delta_hz = dअगरf;
					thp = thp_idx;
					mभाग = mभाग_idx;
					nभाग = nभाग_idx;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	octeon_i2c_reg_ग_लिखो(i2c, SW_TWSI_OP_TWSI_CLK, thp);
	octeon_i2c_reg_ग_लिखो(i2c, SW_TWSI_EOP_TWSI_CLKCTL, (mभाग << 3) | nभाग);
पूर्ण

पूर्णांक octeon_i2c_init_lowlevel(काष्ठा octeon_i2c *i2c)
अणु
	u8 status = 0;
	पूर्णांक tries;

	/* reset controller */
	octeon_i2c_reg_ग_लिखो(i2c, SW_TWSI_EOP_TWSI_RST, 0);

	क्रम (tries = 10; tries && status != STAT_IDLE; tries--) अणु
		udelay(1);
		status = octeon_i2c_stat_पढ़ो(i2c);
		अगर (status == STAT_IDLE)
			अवरोध;
	पूर्ण

	अगर (status != STAT_IDLE) अणु
		dev_err(i2c->dev, "%s: TWSI_RST failed! (0x%x)\n",
			__func__, status);
		वापस -EIO;
	पूर्ण

	/* toggle twice to क्रमce both tearकरोwns */
	octeon_i2c_hlc_enable(i2c);
	octeon_i2c_hlc_disable(i2c);
	वापस 0;
पूर्ण

अटल पूर्णांक octeon_i2c_get_scl(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा octeon_i2c *i2c = i2c_get_adapdata(adap);
	u64 state;

	state = octeon_i2c_पढ़ो_पूर्णांक(i2c);
	वापस state & TWSI_INT_SCL;
पूर्ण

अटल व्योम octeon_i2c_set_scl(काष्ठा i2c_adapter *adap, पूर्णांक val)
अणु
	काष्ठा octeon_i2c *i2c = i2c_get_adapdata(adap);

	octeon_i2c_ग_लिखो_पूर्णांक(i2c, val ? 0 : TWSI_INT_SCL_OVR);
पूर्ण

अटल पूर्णांक octeon_i2c_get_sda(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा octeon_i2c *i2c = i2c_get_adapdata(adap);
	u64 state;

	state = octeon_i2c_पढ़ो_पूर्णांक(i2c);
	वापस state & TWSI_INT_SDA;
पूर्ण

अटल व्योम octeon_i2c_prepare_recovery(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा octeon_i2c *i2c = i2c_get_adapdata(adap);

	octeon_i2c_hlc_disable(i2c);
	octeon_i2c_reg_ग_लिखो(i2c, SW_TWSI_EOP_TWSI_RST, 0);
	/* रुको क्रम software reset to settle */
	udelay(5);

	/*
	 * Bring control रेजिस्टर to a good state regardless
	 * of HLC state.
	 */
	octeon_i2c_ctl_ग_लिखो(i2c, TWSI_CTL_ENAB);

	octeon_i2c_ग_लिखो_पूर्णांक(i2c, 0);
पूर्ण

अटल व्योम octeon_i2c_unprepare_recovery(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा octeon_i2c *i2c = i2c_get_adapdata(adap);

	/*
	 * Generate STOP to finish the unfinished transaction.
	 * Can't generate STOP via the TWSI CTL रेजिस्टर
	 * since it could bring the TWSI controller पूर्णांकo an inoperable state.
	 */
	octeon_i2c_ग_लिखो_पूर्णांक(i2c, TWSI_INT_SDA_OVR | TWSI_INT_SCL_OVR);
	udelay(5);
	octeon_i2c_ग_लिखो_पूर्णांक(i2c, TWSI_INT_SDA_OVR);
	udelay(5);
	octeon_i2c_ग_लिखो_पूर्णांक(i2c, 0);
पूर्ण

काष्ठा i2c_bus_recovery_info octeon_i2c_recovery_info = अणु
	.recover_bus = i2c_generic_scl_recovery,
	.get_scl = octeon_i2c_get_scl,
	.set_scl = octeon_i2c_set_scl,
	.get_sda = octeon_i2c_get_sda,
	.prepare_recovery = octeon_i2c_prepare_recovery,
	.unprepare_recovery = octeon_i2c_unprepare_recovery,
पूर्ण;
