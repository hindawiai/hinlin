<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Coral-P(A)/Lime I2C adapter driver
 *
 * (C) 2011 DENX Software Engineering, Anम_से_दij Gustschin <agust@denx.de>
 */

#समावेश <linux/fb.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>

#समावेश "mb862xxfb.h"
#समावेश "mb862xx_reg.h"

अटल पूर्णांक mb862xx_i2c_रुको_event(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा mb862xxfb_par *par = adap->algo_data;
	u32 reg;

	करो अणु
		udelay(10);
		reg = inreg(i2c, GC_I2C_BCR);
		अगर (reg & (I2C_INT | I2C_BER))
			अवरोध;
	पूर्ण जबतक (1);

	वापस (reg & I2C_BER) ? 0 : 1;
पूर्ण

अटल पूर्णांक mb862xx_i2c_करो_address(काष्ठा i2c_adapter *adap, पूर्णांक addr)
अणु
	काष्ठा mb862xxfb_par *par = adap->algo_data;

	outreg(i2c, GC_I2C_DAR, addr);
	outreg(i2c, GC_I2C_CCR, I2C_CLOCK_AND_ENABLE);
	outreg(i2c, GC_I2C_BCR, par->i2c_rs ? I2C_REPEATED_START : I2C_START);
	अगर (!mb862xx_i2c_रुको_event(adap))
		वापस -EIO;
	par->i2c_rs = !(inreg(i2c, GC_I2C_BSR) & I2C_LRB);
	वापस par->i2c_rs;
पूर्ण

अटल पूर्णांक mb862xx_i2c_ग_लिखो_byte(काष्ठा i2c_adapter *adap, u8 byte)
अणु
	काष्ठा mb862xxfb_par *par = adap->algo_data;

	outreg(i2c, GC_I2C_DAR, byte);
	outreg(i2c, GC_I2C_BCR, I2C_START);
	अगर (!mb862xx_i2c_रुको_event(adap))
		वापस -EIO;
	वापस !(inreg(i2c, GC_I2C_BSR) & I2C_LRB);
पूर्ण

अटल पूर्णांक mb862xx_i2c_पढ़ो_byte(काष्ठा i2c_adapter *adap, u8 *byte, पूर्णांक last)
अणु
	काष्ठा mb862xxfb_par *par = adap->algo_data;

	outreg(i2c, GC_I2C_BCR, I2C_START | (last ? 0 : I2C_ACK));
	अगर (!mb862xx_i2c_रुको_event(adap))
		वापस 0;
	*byte = inreg(i2c, GC_I2C_DAR);
	वापस 1;
पूर्ण

अटल व्योम mb862xx_i2c_stop(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा mb862xxfb_par *par = adap->algo_data;

	outreg(i2c, GC_I2C_BCR, I2C_STOP);
	outreg(i2c, GC_I2C_CCR, I2C_DISABLE);
	par->i2c_rs = 0;
पूर्ण

अटल पूर्णांक mb862xx_i2c_पढ़ो(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *m)
अणु
	पूर्णांक i, ret = 0;
	पूर्णांक last = m->len - 1;

	क्रम (i = 0; i < m->len; i++) अणु
		अगर (!mb862xx_i2c_पढ़ो_byte(adap, &m->buf[i], i == last)) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक mb862xx_i2c_ग_लिखो(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *m)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < m->len; i++) अणु
		अगर (!mb862xx_i2c_ग_लिखो_byte(adap, m->buf[i])) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक mb862xx_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs,
			पूर्णांक num)
अणु
	काष्ठा mb862xxfb_par *par = adap->algo_data;
	काष्ठा i2c_msg *m;
	पूर्णांक addr;
	पूर्णांक i = 0, err = 0;

	dev_dbg(par->dev, "%s: %d msgs\n", __func__, num);

	क्रम (i = 0; i < num; i++) अणु
		m = &msgs[i];
		अगर (!m->len) अणु
			dev_dbg(par->dev, "%s: null msgs\n", __func__);
			जारी;
		पूर्ण
		addr = m->addr;
		अगर (m->flags & I2C_M_RD)
			addr |= 1;

		err = mb862xx_i2c_करो_address(adap, addr);
		अगर (err < 0)
			अवरोध;
		अगर (m->flags & I2C_M_RD)
			err = mb862xx_i2c_पढ़ो(adap, m);
		अन्यथा
			err = mb862xx_i2c_ग_लिखो(adap, m);
	पूर्ण

	अगर (i)
		mb862xx_i2c_stop(adap);

	वापस (err < 0) ? err : i;
पूर्ण

अटल u32 mb862xx_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_SMBUS_BYTE_DATA;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm mb862xx_algo = अणु
	.master_xfer	= mb862xx_xfer,
	.functionality	= mb862xx_func,
पूर्ण;

अटल काष्ठा i2c_adapter mb862xx_i2c_adapter = अणु
	.name		= "MB862xx I2C adapter",
	.algo		= &mb862xx_algo,
	.owner		= THIS_MODULE,
पूर्ण;

पूर्णांक mb862xx_i2c_init(काष्ठा mb862xxfb_par *par)
अणु
	mb862xx_i2c_adapter.algo_data = par;
	par->adap = &mb862xx_i2c_adapter;

	वापस i2c_add_adapter(par->adap);
पूर्ण

व्योम mb862xx_i2c_निकास(काष्ठा mb862xxfb_par *par)
अणु
	अगर (par->adap) अणु
		i2c_del_adapter(par->adap);
		par->adap = शून्य;
	पूर्ण
पूर्ण
