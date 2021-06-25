<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>

#समावेश "dibx000_common.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "turn on debugging (default: 0)");

#घोषणा dprपूर्णांकk(fmt, arg...) करो अणु					\
	अगर (debug)							\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt),			\
		       __func__, ##arg);				\
पूर्ण जबतक (0)

अटल पूर्णांक dibx000_ग_लिखो_word(काष्ठा dibx000_i2c_master *mst, u16 reg, u16 val)
अणु
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&mst->i2c_buffer_lock) < 0) अणु
		dprपूर्णांकk("could not acquire lock\n");
		वापस -EINVAL;
	पूर्ण

	mst->i2c_ग_लिखो_buffer[0] = (reg >> 8) & 0xff;
	mst->i2c_ग_लिखो_buffer[1] = reg & 0xff;
	mst->i2c_ग_लिखो_buffer[2] = (val >> 8) & 0xff;
	mst->i2c_ग_लिखो_buffer[3] = val & 0xff;

	स_रखो(mst->msg, 0, माप(काष्ठा i2c_msg));
	mst->msg[0].addr = mst->i2c_addr;
	mst->msg[0].flags = 0;
	mst->msg[0].buf = mst->i2c_ग_लिखो_buffer;
	mst->msg[0].len = 4;

	ret = i2c_transfer(mst->i2c_adap, mst->msg, 1) != 1 ? -EREMOTEIO : 0;
	mutex_unlock(&mst->i2c_buffer_lock);

	वापस ret;
पूर्ण

अटल u16 dibx000_पढ़ो_word(काष्ठा dibx000_i2c_master *mst, u16 reg)
अणु
	u16 ret;

	अगर (mutex_lock_पूर्णांकerruptible(&mst->i2c_buffer_lock) < 0) अणु
		dprपूर्णांकk("could not acquire lock\n");
		वापस 0;
	पूर्ण

	mst->i2c_ग_लिखो_buffer[0] = reg >> 8;
	mst->i2c_ग_लिखो_buffer[1] = reg & 0xff;

	स_रखो(mst->msg, 0, 2 * माप(काष्ठा i2c_msg));
	mst->msg[0].addr = mst->i2c_addr;
	mst->msg[0].flags = 0;
	mst->msg[0].buf = mst->i2c_ग_लिखो_buffer;
	mst->msg[0].len = 2;
	mst->msg[1].addr = mst->i2c_addr;
	mst->msg[1].flags = I2C_M_RD;
	mst->msg[1].buf = mst->i2c_पढ़ो_buffer;
	mst->msg[1].len = 2;

	अगर (i2c_transfer(mst->i2c_adap, mst->msg, 2) != 2)
		dprपूर्णांकk("i2c read error on %d\n", reg);

	ret = (mst->i2c_पढ़ो_buffer[0] << 8) | mst->i2c_पढ़ो_buffer[1];
	mutex_unlock(&mst->i2c_buffer_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक dibx000_is_i2c_करोne(काष्ठा dibx000_i2c_master *mst)
अणु
	पूर्णांक i = 100;
	u16 status;

	जबतक (((status = dibx000_पढ़ो_word(mst, mst->base_reg + 2)) & 0x0100) == 0 && --i > 0)
		;

	/* i2c समयd out */
	अगर (i == 0)
		वापस -EREMOTEIO;

	/* no acknowledge */
	अगर ((status & 0x0080) == 0)
		वापस -EREMOTEIO;

	वापस 0;
पूर्ण

अटल पूर्णांक dibx000_master_i2c_ग_लिखो(काष्ठा dibx000_i2c_master *mst, काष्ठा i2c_msg *msg, u8 stop)
अणु
	u16 data;
	u16 da;
	u16 i;
	u16 txlen = msg->len, len;
	स्थिर u8 *b = msg->buf;

	जबतक (txlen) अणु
		dibx000_पढ़ो_word(mst, mst->base_reg + 2);

		len = txlen > 8 ? 8 : txlen;
		क्रम (i = 0; i < len; i += 2) अणु
			data = *b++ << 8;
			अगर (i+1 < len)
				data |= *b++;
			dibx000_ग_लिखो_word(mst, mst->base_reg, data);
		पूर्ण
		da = (((u8) (msg->addr))  << 9) |
			(1           << 8) |
			(1           << 7) |
			(0           << 6) |
			(0           << 5) |
			((len & 0x7) << 2) |
			(0           << 1) |
			(0           << 0);

		अगर (txlen == msg->len)
			da |= 1 << 5; /* start */

		अगर (txlen-len == 0 && stop)
			da |= 1 << 6; /* stop */

		dibx000_ग_लिखो_word(mst, mst->base_reg+1, da);

		अगर (dibx000_is_i2c_करोne(mst) != 0)
			वापस -EREMOTEIO;
		txlen -= len;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dibx000_master_i2c_पढ़ो(काष्ठा dibx000_i2c_master *mst, काष्ठा i2c_msg *msg)
अणु
	u16 da;
	u8 *b = msg->buf;
	u16 rxlen = msg->len, len;

	जबतक (rxlen) अणु
		len = rxlen > 8 ? 8 : rxlen;
		da = (((u8) (msg->addr)) << 9) |
			(1           << 8) |
			(1           << 7) |
			(0           << 6) |
			(0           << 5) |
			((len & 0x7) << 2) |
			(1           << 1) |
			(0           << 0);

		अगर (rxlen == msg->len)
			da |= 1 << 5; /* start */

		अगर (rxlen-len == 0)
			da |= 1 << 6; /* stop */
		dibx000_ग_लिखो_word(mst, mst->base_reg+1, da);

		अगर (dibx000_is_i2c_करोne(mst) != 0)
			वापस -EREMOTEIO;

		rxlen -= len;

		जबतक (len) अणु
			da = dibx000_पढ़ो_word(mst, mst->base_reg);
			*b++ = (da >> 8) & 0xff;
			len--;
			अगर (len >= 1) अणु
				*b++ =  da   & 0xff;
				len--;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dibx000_i2c_set_speed(काष्ठा i2c_adapter *i2c_adap, u16 speed)
अणु
	काष्ठा dibx000_i2c_master *mst = i2c_get_adapdata(i2c_adap);

	अगर (mst->device_rev < DIB7000MC && speed < 235)
		speed = 235;
	वापस dibx000_ग_लिखो_word(mst, mst->base_reg + 3, (u16)(60000 / speed));

पूर्ण
EXPORT_SYMBOL(dibx000_i2c_set_speed);

अटल u32 dibx000_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल पूर्णांक dibx000_i2c_select_पूर्णांकerface(काष्ठा dibx000_i2c_master *mst,
					क्रमागत dibx000_i2c_पूर्णांकerface पूर्णांकf)
अणु
	अगर (mst->device_rev > DIB3000MC && mst->selected_पूर्णांकerface != पूर्णांकf) अणु
		dprपूर्णांकk("selecting interface: %d\n", पूर्णांकf);
		mst->selected_पूर्णांकerface = पूर्णांकf;
		वापस dibx000_ग_लिखो_word(mst, mst->base_reg + 4, पूर्णांकf);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dibx000_i2c_master_xfer_gpio12(काष्ठा i2c_adapter *i2c_adap, काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	काष्ठा dibx000_i2c_master *mst = i2c_get_adapdata(i2c_adap);
	पूर्णांक msg_index;
	पूर्णांक ret = 0;

	dibx000_i2c_select_पूर्णांकerface(mst, DIBX000_I2C_INTERFACE_GPIO_1_2);
	क्रम (msg_index = 0; msg_index < num; msg_index++) अणु
		अगर (msg[msg_index].flags & I2C_M_RD) अणु
			ret = dibx000_master_i2c_पढ़ो(mst, &msg[msg_index]);
			अगर (ret != 0)
				वापस 0;
		पूर्ण अन्यथा अणु
			ret = dibx000_master_i2c_ग_लिखो(mst, &msg[msg_index], 1);
			अगर (ret != 0)
				वापस 0;
		पूर्ण
	पूर्ण

	वापस num;
पूर्ण

अटल पूर्णांक dibx000_i2c_master_xfer_gpio34(काष्ठा i2c_adapter *i2c_adap, काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	काष्ठा dibx000_i2c_master *mst = i2c_get_adapdata(i2c_adap);
	पूर्णांक msg_index;
	पूर्णांक ret = 0;

	dibx000_i2c_select_पूर्णांकerface(mst, DIBX000_I2C_INTERFACE_GPIO_3_4);
	क्रम (msg_index = 0; msg_index < num; msg_index++) अणु
		अगर (msg[msg_index].flags & I2C_M_RD) अणु
			ret = dibx000_master_i2c_पढ़ो(mst, &msg[msg_index]);
			अगर (ret != 0)
				वापस 0;
		पूर्ण अन्यथा अणु
			ret = dibx000_master_i2c_ग_लिखो(mst, &msg[msg_index], 1);
			अगर (ret != 0)
				वापस 0;
		पूर्ण
	पूर्ण

	वापस num;
पूर्ण

अटल काष्ठा i2c_algorithm dibx000_i2c_master_gpio12_xfer_algo = अणु
	.master_xfer = dibx000_i2c_master_xfer_gpio12,
	.functionality = dibx000_i2c_func,
पूर्ण;

अटल काष्ठा i2c_algorithm dibx000_i2c_master_gpio34_xfer_algo = अणु
	.master_xfer = dibx000_i2c_master_xfer_gpio34,
	.functionality = dibx000_i2c_func,
पूर्ण;

अटल पूर्णांक dibx000_i2c_gate_ctrl(काष्ठा dibx000_i2c_master *mst, u8 tx[4],
				 u8 addr, पूर्णांक onoff)
अणु
	u16 val;


	अगर (onoff)
		val = addr << 8;	// bit 7 = use master or not, अगर 0, the gate is खोलो
	अन्यथा
		val = 1 << 7;

	अगर (mst->device_rev > DIB7000)
		val <<= 1;

	tx[0] = (((mst->base_reg + 1) >> 8) & 0xff);
	tx[1] = ((mst->base_reg + 1) & 0xff);
	tx[2] = val >> 8;
	tx[3] = val & 0xff;

	वापस 0;
पूर्ण

अटल पूर्णांक dibx000_i2c_gated_gpio67_xfer(काष्ठा i2c_adapter *i2c_adap,
					काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	काष्ठा dibx000_i2c_master *mst = i2c_get_adapdata(i2c_adap);
	पूर्णांक ret;

	अगर (num > 32) अणु
		dprपूर्णांकk("%s: too much I2C message to be transmitted (%i). Maximum is 32",
			__func__, num);
		वापस -ENOMEM;
	पूर्ण

	dibx000_i2c_select_पूर्णांकerface(mst, DIBX000_I2C_INTERFACE_GPIO_6_7);

	अगर (mutex_lock_पूर्णांकerruptible(&mst->i2c_buffer_lock) < 0) अणु
		dprपूर्णांकk("could not acquire lock\n");
		वापस -EINVAL;
	पूर्ण

	स_रखो(mst->msg, 0, माप(काष्ठा i2c_msg) * (2 + num));

	/* खोलो the gate */
	dibx000_i2c_gate_ctrl(mst, &mst->i2c_ग_लिखो_buffer[0], msg[0].addr, 1);
	mst->msg[0].addr = mst->i2c_addr;
	mst->msg[0].buf = &mst->i2c_ग_लिखो_buffer[0];
	mst->msg[0].len = 4;

	स_नकल(&mst->msg[1], msg, माप(काष्ठा i2c_msg) * num);

	/* बंद the gate */
	dibx000_i2c_gate_ctrl(mst, &mst->i2c_ग_लिखो_buffer[4], 0, 0);
	mst->msg[num + 1].addr = mst->i2c_addr;
	mst->msg[num + 1].buf = &mst->i2c_ग_लिखो_buffer[4];
	mst->msg[num + 1].len = 4;

	ret = (i2c_transfer(mst->i2c_adap, mst->msg, 2 + num) == 2 + num ?
			num : -EIO);

	mutex_unlock(&mst->i2c_buffer_lock);
	वापस ret;
पूर्ण

अटल काष्ठा i2c_algorithm dibx000_i2c_gated_gpio67_algo = अणु
	.master_xfer = dibx000_i2c_gated_gpio67_xfer,
	.functionality = dibx000_i2c_func,
पूर्ण;

अटल पूर्णांक dibx000_i2c_gated_tuner_xfer(काष्ठा i2c_adapter *i2c_adap,
					काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	काष्ठा dibx000_i2c_master *mst = i2c_get_adapdata(i2c_adap);
	पूर्णांक ret;

	अगर (num > 32) अणु
		dprपूर्णांकk("%s: too much I2C message to be transmitted (%i). Maximum is 32",
			__func__, num);
		वापस -ENOMEM;
	पूर्ण

	dibx000_i2c_select_पूर्णांकerface(mst, DIBX000_I2C_INTERFACE_TUNER);

	अगर (mutex_lock_पूर्णांकerruptible(&mst->i2c_buffer_lock) < 0) अणु
		dprपूर्णांकk("could not acquire lock\n");
		वापस -EINVAL;
	पूर्ण
	स_रखो(mst->msg, 0, माप(काष्ठा i2c_msg) * (2 + num));

	/* खोलो the gate */
	dibx000_i2c_gate_ctrl(mst, &mst->i2c_ग_लिखो_buffer[0], msg[0].addr, 1);
	mst->msg[0].addr = mst->i2c_addr;
	mst->msg[0].buf = &mst->i2c_ग_लिखो_buffer[0];
	mst->msg[0].len = 4;

	स_नकल(&mst->msg[1], msg, माप(काष्ठा i2c_msg) * num);

	/* बंद the gate */
	dibx000_i2c_gate_ctrl(mst, &mst->i2c_ग_लिखो_buffer[4], 0, 0);
	mst->msg[num + 1].addr = mst->i2c_addr;
	mst->msg[num + 1].buf = &mst->i2c_ग_लिखो_buffer[4];
	mst->msg[num + 1].len = 4;

	ret = (i2c_transfer(mst->i2c_adap, mst->msg, 2 + num) == 2 + num ?
			num : -EIO);
	mutex_unlock(&mst->i2c_buffer_lock);
	वापस ret;
पूर्ण

अटल काष्ठा i2c_algorithm dibx000_i2c_gated_tuner_algo = अणु
	.master_xfer = dibx000_i2c_gated_tuner_xfer,
	.functionality = dibx000_i2c_func,
पूर्ण;

काष्ठा i2c_adapter *dibx000_get_i2c_adapter(काष्ठा dibx000_i2c_master *mst,
						क्रमागत dibx000_i2c_पूर्णांकerface पूर्णांकf,
						पूर्णांक gating)
अणु
	काष्ठा i2c_adapter *i2c = शून्य;

	चयन (पूर्णांकf) अणु
	हाल DIBX000_I2C_INTERFACE_TUNER:
		अगर (gating)
			i2c = &mst->gated_tuner_i2c_adap;
		अवरोध;
	हाल DIBX000_I2C_INTERFACE_GPIO_1_2:
		अगर (!gating)
			i2c = &mst->master_i2c_adap_gpio12;
		अवरोध;
	हाल DIBX000_I2C_INTERFACE_GPIO_3_4:
		अगर (!gating)
			i2c = &mst->master_i2c_adap_gpio34;
		अवरोध;
	हाल DIBX000_I2C_INTERFACE_GPIO_6_7:
		अगर (gating)
			i2c = &mst->master_i2c_adap_gpio67;
		अवरोध;
	शेष:
		pr_err("incorrect I2C interface selected\n");
		अवरोध;
	पूर्ण

	वापस i2c;
पूर्ण

EXPORT_SYMBOL(dibx000_get_i2c_adapter);

व्योम dibx000_reset_i2c_master(काष्ठा dibx000_i2c_master *mst)
अणु
	/* initialize the i2c-master by closing the gate */
	u8 tx[4];
	काष्ठा i2c_msg m = अणु.addr = mst->i2c_addr,.buf = tx,.len = 4 पूर्ण;

	dibx000_i2c_gate_ctrl(mst, tx, 0, 0);
	i2c_transfer(mst->i2c_adap, &m, 1);
	mst->selected_पूर्णांकerface = 0xff;	// the first समय क्रमce a select of the I2C
	dibx000_i2c_select_पूर्णांकerface(mst, DIBX000_I2C_INTERFACE_TUNER);
पूर्ण

EXPORT_SYMBOL(dibx000_reset_i2c_master);

अटल पूर्णांक i2c_adapter_init(काष्ठा i2c_adapter *i2c_adap,
				काष्ठा i2c_algorithm *algo, स्थिर अक्षर *name,
				काष्ठा dibx000_i2c_master *mst)
अणु
	strscpy(i2c_adap->name, name, माप(i2c_adap->name));
	i2c_adap->algo = algo;
	i2c_adap->algo_data = शून्य;
	i2c_set_adapdata(i2c_adap, mst);
	अगर (i2c_add_adapter(i2c_adap) < 0)
		वापस -ENODEV;
	वापस 0;
पूर्ण

पूर्णांक dibx000_init_i2c_master(काष्ठा dibx000_i2c_master *mst, u16 device_rev,
				काष्ठा i2c_adapter *i2c_adap, u8 i2c_addr)
अणु
	पूर्णांक ret;

	mutex_init(&mst->i2c_buffer_lock);
	अगर (mutex_lock_पूर्णांकerruptible(&mst->i2c_buffer_lock) < 0) अणु
		dprपूर्णांकk("could not acquire lock\n");
		वापस -EINVAL;
	पूर्ण
	स_रखो(mst->msg, 0, माप(काष्ठा i2c_msg));
	mst->msg[0].addr = i2c_addr >> 1;
	mst->msg[0].flags = 0;
	mst->msg[0].buf = mst->i2c_ग_लिखो_buffer;
	mst->msg[0].len = 4;

	mst->device_rev = device_rev;
	mst->i2c_adap = i2c_adap;
	mst->i2c_addr = i2c_addr >> 1;

	अगर (device_rev == DIB7000P || device_rev == DIB8000)
		mst->base_reg = 1024;
	अन्यथा
		mst->base_reg = 768;

	mst->gated_tuner_i2c_adap.dev.parent = mst->i2c_adap->dev.parent;
	अगर (i2c_adapter_init
			(&mst->gated_tuner_i2c_adap, &dibx000_i2c_gated_tuner_algo,
			 "DiBX000 tuner I2C bus", mst) != 0)
		pr_err("could not initialize the tuner i2c_adapter\n");

	mst->master_i2c_adap_gpio12.dev.parent = mst->i2c_adap->dev.parent;
	अगर (i2c_adapter_init
			(&mst->master_i2c_adap_gpio12, &dibx000_i2c_master_gpio12_xfer_algo,
			 "DiBX000 master GPIO12 I2C bus", mst) != 0)
		pr_err("could not initialize the master i2c_adapter\n");

	mst->master_i2c_adap_gpio34.dev.parent = mst->i2c_adap->dev.parent;
	अगर (i2c_adapter_init
			(&mst->master_i2c_adap_gpio34, &dibx000_i2c_master_gpio34_xfer_algo,
			 "DiBX000 master GPIO34 I2C bus", mst) != 0)
		pr_err("could not initialize the master i2c_adapter\n");

	mst->master_i2c_adap_gpio67.dev.parent = mst->i2c_adap->dev.parent;
	अगर (i2c_adapter_init
			(&mst->master_i2c_adap_gpio67, &dibx000_i2c_gated_gpio67_algo,
			 "DiBX000 master GPIO67 I2C bus", mst) != 0)
		pr_err("could not initialize the master i2c_adapter\n");

	/* initialize the i2c-master by closing the gate */
	dibx000_i2c_gate_ctrl(mst, mst->i2c_ग_लिखो_buffer, 0, 0);

	ret = (i2c_transfer(i2c_adap, mst->msg, 1) == 1);
	mutex_unlock(&mst->i2c_buffer_lock);

	वापस ret;
पूर्ण

EXPORT_SYMBOL(dibx000_init_i2c_master);

व्योम dibx000_निकास_i2c_master(काष्ठा dibx000_i2c_master *mst)
अणु
	i2c_del_adapter(&mst->gated_tuner_i2c_adap);
	i2c_del_adapter(&mst->master_i2c_adap_gpio12);
	i2c_del_adapter(&mst->master_i2c_adap_gpio34);
	i2c_del_adapter(&mst->master_i2c_adap_gpio67);
पूर्ण
EXPORT_SYMBOL(dibx000_निकास_i2c_master);

MODULE_AUTHOR("Patrick Boettcher <patrick.boettcher@posteo.de>");
MODULE_DESCRIPTION("Common function the DiBcom demodulator family");
MODULE_LICENSE("GPL");
