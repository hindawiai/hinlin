<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Earthsoft PT3 driver
 *
 * Copyright (C) 2014 Akihiro Tsukada <tskd08@gmail.com>
 */
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>
#समावेश <linux/pci.h>

#समावेश "pt3.h"

#घोषणा PT3_I2C_BASE  2048
#घोषणा PT3_CMD_ADDR_NORMAL 0
#घोषणा PT3_CMD_ADDR_INIT_DEMOD  4096
#घोषणा PT3_CMD_ADDR_INIT_TUNER  (4096 + 2042)

/* masks क्रम I2C status रेजिस्टर */
#घोषणा STAT_SEQ_RUNNING 0x1
#घोषणा STAT_SEQ_ERROR   0x6
#घोषणा STAT_NO_SEQ      0x8

#घोषणा PT3_I2C_RUN   (1 << 16)
#घोषणा PT3_I2C_RESET (1 << 17)

क्रमागत ctl_cmd अणु
	I_END,
	I_ADDRESS,
	I_CLOCK_L,
	I_CLOCK_H,
	I_DATA_L,
	I_DATA_H,
	I_RESET,
	I_SLEEP,
	I_DATA_L_NOP  = 0x08,
	I_DATA_H_NOP  = 0x0c,
	I_DATA_H_READ = 0x0d,
	I_DATA_H_ACK0 = 0x0e,
	I_DATA_H_ACK1 = 0x0f,
पूर्ण;


अटल व्योम cmdbuf_add(काष्ठा pt3_i2cbuf *cbuf, क्रमागत ctl_cmd cmd)
अणु
	पूर्णांक buf_idx;

	अगर ((cbuf->num_cmds % 2) == 0)
		cbuf->पंचांगp = cmd;
	अन्यथा अणु
		cbuf->पंचांगp |= cmd << 4;
		buf_idx = cbuf->num_cmds / 2;
		अगर (buf_idx < ARRAY_SIZE(cbuf->data))
			cbuf->data[buf_idx] = cbuf->पंचांगp;
	पूर्ण
	cbuf->num_cmds++;
पूर्ण

अटल व्योम put_end(काष्ठा pt3_i2cbuf *cbuf)
अणु
	cmdbuf_add(cbuf, I_END);
	अगर (cbuf->num_cmds % 2)
		cmdbuf_add(cbuf, I_END);
पूर्ण

अटल व्योम put_start(काष्ठा pt3_i2cbuf *cbuf)
अणु
	cmdbuf_add(cbuf, I_DATA_H);
	cmdbuf_add(cbuf, I_CLOCK_H);
	cmdbuf_add(cbuf, I_DATA_L);
	cmdbuf_add(cbuf, I_CLOCK_L);
पूर्ण

अटल व्योम put_byte_ग_लिखो(काष्ठा pt3_i2cbuf *cbuf, u8 val)
अणु
	u8 mask;

	क्रम (mask = 0x80; mask > 0; mask >>= 1)
		cmdbuf_add(cbuf, (val & mask) ? I_DATA_H_NOP : I_DATA_L_NOP);
	cmdbuf_add(cbuf, I_DATA_H_ACK0);
पूर्ण

अटल व्योम put_byte_पढ़ो(काष्ठा pt3_i2cbuf *cbuf, u32 size)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < size; i++) अणु
		क्रम (j = 0; j < 8; j++)
			cmdbuf_add(cbuf, I_DATA_H_READ);
		cmdbuf_add(cbuf, (i == size - 1) ? I_DATA_H_NOP : I_DATA_L_NOP);
	पूर्ण
पूर्ण

अटल व्योम put_stop(काष्ठा pt3_i2cbuf *cbuf)
अणु
	cmdbuf_add(cbuf, I_DATA_L);
	cmdbuf_add(cbuf, I_CLOCK_H);
	cmdbuf_add(cbuf, I_DATA_H);
पूर्ण


/* translates msgs to पूर्णांकernal commands क्रम bit-banging */
अटल व्योम translate(काष्ठा pt3_i2cbuf *cbuf, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	पूर्णांक i, j;
	bool rd;

	cbuf->num_cmds = 0;
	क्रम (i = 0; i < num; i++) अणु
		rd = !!(msgs[i].flags & I2C_M_RD);
		put_start(cbuf);
		put_byte_ग_लिखो(cbuf, msgs[i].addr << 1 | rd);
		अगर (rd)
			put_byte_पढ़ो(cbuf, msgs[i].len);
		अन्यथा
			क्रम (j = 0; j < msgs[i].len; j++)
				put_byte_ग_लिखो(cbuf, msgs[i].buf[j]);
	पूर्ण
	अगर (num > 0) अणु
		put_stop(cbuf);
		put_end(cbuf);
	पूर्ण
पूर्ण

अटल पूर्णांक रुको_i2c_result(काष्ठा pt3_board *pt3, u32 *result, पूर्णांक max_रुको)
अणु
	पूर्णांक i;
	u32 v;

	क्रम (i = 0; i < max_रुको; i++) अणु
		v = ioपढ़ो32(pt3->regs[0] + REG_I2C_R);
		अगर (!(v & STAT_SEQ_RUNNING))
			अवरोध;
		usleep_range(500, 750);
	पूर्ण
	अगर (i >= max_रुको)
		वापस -EIO;
	अगर (result)
		*result = v;
	वापस 0;
पूर्ण

/* send [pre-]translated i2c msgs stored at addr */
अटल पूर्णांक send_i2c_cmd(काष्ठा pt3_board *pt3, u32 addr)
अणु
	u32 ret;

	/* make sure that previous transactions had finished */
	अगर (रुको_i2c_result(pt3, शून्य, 50)) अणु
		dev_warn(&pt3->pdev->dev, "(%s) prev. transaction stalled\n",
				__func__);
		वापस -EIO;
	पूर्ण

	ioग_लिखो32(PT3_I2C_RUN | addr, pt3->regs[0] + REG_I2C_W);
	usleep_range(200, 300);
	/* रुको क्रम the current transaction to finish */
	अगर (रुको_i2c_result(pt3, &ret, 500) || (ret & STAT_SEQ_ERROR)) अणु
		dev_warn(&pt3->pdev->dev, "(%s) failed.\n", __func__);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण


/* init commands क्रम each demod are combined पूर्णांकo one transaction
 *  and hidden in ROM with the address PT3_CMD_ADDR_INIT_DEMOD.
 */
पूर्णांक  pt3_init_all_demods(काष्ठा pt3_board *pt3)
अणु
	ioपढ़ो32(pt3->regs[0] + REG_I2C_R);
	वापस send_i2c_cmd(pt3, PT3_CMD_ADDR_INIT_DEMOD);
पूर्ण

/* init commands क्रम two ISDB-T tuners are hidden in ROM. */
पूर्णांक  pt3_init_all_mxl301rf(काष्ठा pt3_board *pt3)
अणु
	usleep_range(1000, 2000);
	वापस send_i2c_cmd(pt3, PT3_CMD_ADDR_INIT_TUNER);
पूर्ण

व्योम pt3_i2c_reset(काष्ठा pt3_board *pt3)
अणु
	ioग_लिखो32(PT3_I2C_RESET, pt3->regs[0] + REG_I2C_W);
पूर्ण

/*
 * I2C algorithm
 */
पूर्णांक
pt3_i2c_master_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा pt3_board *pt3;
	काष्ठा pt3_i2cbuf *cbuf;
	पूर्णांक i;
	व्योम __iomem *p;

	pt3 = i2c_get_adapdata(adap);
	cbuf = pt3->i2c_buf;

	क्रम (i = 0; i < num; i++)
		अगर (msgs[i].flags & I2C_M_RECV_LEN) अणु
			dev_warn(&pt3->pdev->dev,
				"(%s) I2C_M_RECV_LEN not supported.\n",
				__func__);
			वापस -EINVAL;
		पूर्ण

	translate(cbuf, msgs, num);
	स_नकल_toio(pt3->regs[1] + PT3_I2C_BASE + PT3_CMD_ADDR_NORMAL / 2,
			cbuf->data, cbuf->num_cmds);

	अगर (send_i2c_cmd(pt3, PT3_CMD_ADDR_NORMAL) < 0)
		वापस -EIO;

	p = pt3->regs[1] + PT3_I2C_BASE;
	क्रम (i = 0; i < num; i++)
		अगर ((msgs[i].flags & I2C_M_RD) && msgs[i].len > 0) अणु
			स_नकल_fromio(msgs[i].buf, p, msgs[i].len);
			p += msgs[i].len;
		पूर्ण

	वापस num;
पूर्ण

u32 pt3_i2c_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण
