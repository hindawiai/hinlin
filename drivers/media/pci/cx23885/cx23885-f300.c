<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Silicon Lअसल C8051F300 microcontroller.
 *
 * It is used क्रम LNB घातer control in TeVii S470,
 * TBS 6920 PCIe DVB-S2 cards.
 *
 * Microcontroller connected to cx23885 GPIO pins:
 * GPIO0 - data		- P0.3 F300
 * GPIO1 - reset	- P0.2 F300
 * GPIO2 - clk		- P0.1 F300
 * GPIO3 - busy		- P0.0 F300
 *
 * Copyright (C) 2009 Igor M. Liplianin <liplianin@me.by>
 */

#समावेश "cx23885.h"
#समावेश "cx23885-f300.h"

#घोषणा F300_DATA	GPIO_0
#घोषणा F300_RESET	GPIO_1
#घोषणा F300_CLK	GPIO_2
#घोषणा F300_BUSY	GPIO_3

अटल व्योम f300_set_line(काष्ठा cx23885_dev *dev, u32 line, u8 lvl)
अणु
	cx23885_gpio_enable(dev, line, 1);
	अगर (lvl == 1)
		cx23885_gpio_set(dev, line);
	अन्यथा
		cx23885_gpio_clear(dev, line);
पूर्ण

अटल u8 f300_get_line(काष्ठा cx23885_dev *dev, u32 line)
अणु
	cx23885_gpio_enable(dev, line, 0);

	वापस cx23885_gpio_get(dev, line);
पूर्ण

अटल व्योम f300_send_byte(काष्ठा cx23885_dev *dev, u8 dta)
अणु
	u8 i;

	क्रम (i = 0; i < 8; i++) अणु
		f300_set_line(dev, F300_CLK, 0);
		udelay(30);
		f300_set_line(dev, F300_DATA, (dta & 0x80) >> 7);/* msb first */
		udelay(30);
		dta <<= 1;
		f300_set_line(dev, F300_CLK, 1);
		udelay(30);
	पूर्ण
पूर्ण

अटल u8 f300_get_byte(काष्ठा cx23885_dev *dev)
अणु
	u8 i, dta = 0;

	क्रम (i = 0; i < 8; i++) अणु
		f300_set_line(dev, F300_CLK, 0);
		udelay(30);
		dta <<= 1;
		f300_set_line(dev, F300_CLK, 1);
		udelay(30);
		dta |= f300_get_line(dev, F300_DATA);/* msb first */

	पूर्ण

	वापस dta;
पूर्ण

अटल u8 f300_xfer(काष्ठा dvb_frontend *fe, u8 *buf)
अणु
	काष्ठा cx23885_tsport *port = fe->dvb->priv;
	काष्ठा cx23885_dev *dev = port->dev;
	u8 i, temp, ret = 0;

	temp = buf[0];
	क्रम (i = 0; i < buf[0]; i++)
		temp += buf[i + 1];
	temp = (~temp + 1);/* get check sum */
	buf[1 + buf[0]] = temp;

	f300_set_line(dev, F300_RESET, 1);
	f300_set_line(dev, F300_CLK, 1);
	udelay(30);
	f300_set_line(dev, F300_DATA, 1);
	msleep(1);

	/* question: */
	f300_set_line(dev, F300_RESET, 0);/* begin to send data */
	msleep(1);

	f300_send_byte(dev, 0xe0);/* the slave address is 0xe0, ग_लिखो */
	msleep(1);

	temp = buf[0];
	temp += 2;
	क्रम (i = 0; i < temp; i++)
		f300_send_byte(dev, buf[i]);

	f300_set_line(dev, F300_RESET, 1);/* sent data over */
	f300_set_line(dev, F300_DATA, 1);

	/* answer: */
	temp = 0;
	क्रम (i = 0; ((i < 8) & (temp == 0)); i++) अणु
		msleep(1);
		अगर (f300_get_line(dev, F300_BUSY) == 0)
			temp = 1;
	पूर्ण

	अगर (i > 7) अणु
		pr_err("%s: timeout, the slave no response\n",
								__func__);
		ret = 1; /* समयout, the slave no response */
	पूर्ण अन्यथा अणु /* the slave not busy, prepare क्रम getting data */
		f300_set_line(dev, F300_RESET, 0);/*पढ़ोy...*/
		msleep(1);
		f300_send_byte(dev, 0xe1);/* 0xe1 is Read */
		msleep(1);
		temp = f300_get_byte(dev);/*get the data length */
		अगर (temp > 14)
			temp = 14;

		क्रम (i = 0; i < (temp + 1); i++)
			f300_get_byte(dev);/* get data to empty buffer */

		f300_set_line(dev, F300_RESET, 1);/* received data over */
		f300_set_line(dev, F300_DATA, 1);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक f300_set_voltage(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_voltage voltage)
अणु
	u8 buf[16];

	buf[0] = 0x05;
	buf[1] = 0x38;/* ग_लिखो port */
	buf[2] = 0x01;/* A port, lnb घातer */

	चयन (voltage) अणु
	हाल SEC_VOLTAGE_13:
		buf[3] = 0x01;/* घातer on */
		buf[4] = 0x02;/* B port, H/V */
		buf[5] = 0x00;/*13V v*/
		अवरोध;
	हाल SEC_VOLTAGE_18:
		buf[3] = 0x01;
		buf[4] = 0x02;
		buf[5] = 0x01;/* 18V h*/
		अवरोध;
	हाल SEC_VOLTAGE_OFF:
		buf[3] = 0x00;/* घातer off */
		buf[4] = 0x00;
		buf[5] = 0x00;
		अवरोध;
	पूर्ण

	वापस f300_xfer(fe, buf);
पूर्ण
