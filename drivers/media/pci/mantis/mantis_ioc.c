<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Mantis PCI bridge driver

	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#समावेश <linux/kernel.h>
#समावेश <linux/i2c.h>

#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/पन.स>

#समावेश <media/dmxdev.h>
#समावेश <media/dvbdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_net.h>

#समावेश "mantis_common.h"
#समावेश "mantis_reg.h"
#समावेश "mantis_ioc.h"

अटल पूर्णांक पढ़ो_eeprom_bytes(काष्ठा mantis_pci *mantis, u8 reg, u8 *data, u8 length)
अणु
	काष्ठा i2c_adapter *adapter = &mantis->adapter;
	पूर्णांक err;
	u8 buf = reg;

	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = 0x50, .flags = 0, .buf = &buf, .len = 1 पूर्ण,
		अणु .addr = 0x50, .flags = I2C_M_RD, .buf = data, .len = length पूर्ण,
	पूर्ण;

	err = i2c_transfer(adapter, msg, 2);
	अगर (err < 0) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "ERROR: i2c read: < err=%i d0=0x%02x d1=0x%02x >",
			err, data[0], data[1]);

		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
पूर्णांक mantis_get_mac(काष्ठा mantis_pci *mantis)
अणु
	पूर्णांक err;
	u8 mac_addr[6] = अणु0पूर्ण;

	err = पढ़ो_eeprom_bytes(mantis, 0x08, mac_addr, 6);
	अगर (err < 0) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "ERROR: Mantis EEPROM read error <%d>", err);

		वापस err;
	पूर्ण

	dprपूर्णांकk(MANTIS_ERROR, 0, "    MAC Address=[%pM]\n", mac_addr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mantis_get_mac);

/* Turn the given bit on or off. */
व्योम mantis_gpio_set_bits(काष्ठा mantis_pci *mantis, u32 bitpos, u8 value)
अणु
	u32 cur;

	dprपूर्णांकk(MANTIS_DEBUG, 1, "Set Bit <%d> to <%d>", bitpos, value);
	cur = mmपढ़ो(MANTIS_GPIF_ADDR);
	अगर (value)
		mantis->gpio_status = cur | (1 << bitpos);
	अन्यथा
		mantis->gpio_status = cur & (~(1 << bitpos));

	dprपूर्णांकk(MANTIS_DEBUG, 1, "GPIO Value <%02x>", mantis->gpio_status);
	mmग_लिखो(mantis->gpio_status, MANTIS_GPIF_ADDR);
	mmग_लिखो(0x00, MANTIS_GPIF_DOUT);
पूर्ण
EXPORT_SYMBOL_GPL(mantis_gpio_set_bits);

पूर्णांक mantis_stream_control(काष्ठा mantis_pci *mantis, क्रमागत mantis_stream_control stream_ctl)
अणु
	u32 reg;

	reg = mmपढ़ो(MANTIS_CONTROL);
	चयन (stream_ctl) अणु
	हाल STREAM_TO_HIF:
		dprपूर्णांकk(MANTIS_DEBUG, 1, "Set stream to HIF");
		reg &= 0xff - MANTIS_BYPASS;
		mmग_लिखो(reg, MANTIS_CONTROL);
		reg |= MANTIS_BYPASS;
		mmग_लिखो(reg, MANTIS_CONTROL);
		अवरोध;

	हाल STREAM_TO_CAM:
		dprपूर्णांकk(MANTIS_DEBUG, 1, "Set stream to CAM");
		reg |= MANTIS_BYPASS;
		mmग_लिखो(reg, MANTIS_CONTROL);
		reg &= 0xff - MANTIS_BYPASS;
		mmग_लिखो(reg, MANTIS_CONTROL);
		अवरोध;
	शेष:
		dprपूर्णांकk(MANTIS_ERROR, 1, "Unknown MODE <%02x>", stream_ctl);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mantis_stream_control);
