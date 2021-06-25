<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* cx25840 firmware functions
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/firmware.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/drv-पूर्णांकf/cx25840.h>

#समावेश "cx25840-core.h"

/*
 * Mike Isely <isely@pobox.com> - The FWSEND parameter controls the
 * size of the firmware chunks sent करोwn the I2C bus to the chip.
 * Previously this had been set to 1024 but unक्रमtunately some I2C
 * implementations can't transfer data in such big gulps.
 * Specअगरically, the pvrusb2 driver has a hard limit of around 60
 * bytes, due to the encapsulation there of I2C traffic पूर्णांकo USB
 * messages.  So we have to signअगरicantly reduce this parameter.
 */
#घोषणा FWSEND 48

#घोषणा FWDEV(x) &((x)->dev)

अटल अक्षर *firmware = "";

module_param(firmware, अक्षरp, 0444);

MODULE_PARM_DESC(firmware, "Firmware image to load");

अटल व्योम start_fw_load(काष्ठा i2c_client *client)
अणु
	/* DL_ADDR_LB=0 DL_ADDR_HB=0 */
	cx25840_ग_लिखो(client, 0x800, 0x00);
	cx25840_ग_लिखो(client, 0x801, 0x00);
	// DL_MAP=3 DL_AUTO_INC=0 DL_ENABLE=1
	cx25840_ग_लिखो(client, 0x803, 0x0b);
	/* AUTO_INC_DIS=1 */
	cx25840_ग_लिखो(client, 0x000, 0x20);
पूर्ण

अटल व्योम end_fw_load(काष्ठा i2c_client *client)
अणु
	/* AUTO_INC_DIS=0 */
	cx25840_ग_लिखो(client, 0x000, 0x00);
	/* DL_ENABLE=0 */
	cx25840_ग_लिखो(client, 0x803, 0x03);
पूर्ण

#घोषणा CX2388x_FIRMWARE "v4l-cx23885-avcore-01.fw"
#घोषणा CX231xx_FIRMWARE "v4l-cx231xx-avcore-01.fw"
#घोषणा CX25840_FIRMWARE "v4l-cx25840.fw"

अटल स्थिर अक्षर *get_fw_name(काष्ठा i2c_client *client)
अणु
	काष्ठा cx25840_state *state = to_state(i2c_get_clientdata(client));

	अगर (firmware[0])
		वापस firmware;
	अगर (is_cx2388x(state))
		वापस CX2388x_FIRMWARE;
	अगर (is_cx231xx(state))
		वापस CX231xx_FIRMWARE;
	वापस CX25840_FIRMWARE;
पूर्ण

अटल पूर्णांक check_fw_load(काष्ठा i2c_client *client, पूर्णांक size)
अणु
	/* DL_ADDR_HB DL_ADDR_LB */
	पूर्णांक s = cx25840_पढ़ो(client, 0x801) << 8;
	s |= cx25840_पढ़ो(client, 0x800);

	अगर (size != s) अणु
		v4l_err(client, "firmware %s load failed\n",
				get_fw_name(client));
		वापस -EINVAL;
	पूर्ण

	v4l_info(client, "loaded %s firmware (%d bytes)\n",
			get_fw_name(client), size);
	वापस 0;
पूर्ण

अटल पूर्णांक fw_ग_लिखो(काष्ठा i2c_client *client, स्थिर u8 *data, पूर्णांक size)
अणु
	अगर (i2c_master_send(client, data, size) < size) अणु
		v4l_err(client, "firmware load i2c failure\n");
		वापस -ENOSYS;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cx25840_loadfw(काष्ठा i2c_client *client)
अणु
	काष्ठा cx25840_state *state = to_state(i2c_get_clientdata(client));
	स्थिर काष्ठा firmware *fw = शून्य;
	u8 buffer[FWSEND];
	स्थिर u8 *ptr;
	स्थिर अक्षर *fwname = get_fw_name(client);
	पूर्णांक size, retval;
	पूर्णांक max_buf_size = FWSEND;
	u32 gpio_oe = 0, gpio_da = 0;

	अगर (is_cx2388x(state)) अणु
		/* Preserve the GPIO OE and output bits */
		gpio_oe = cx25840_पढ़ो(client, 0x160);
		gpio_da = cx25840_पढ़ो(client, 0x164);
	पूर्ण

	/* cx231xx cannot accept more than 16 bytes at a समय */
	अगर (is_cx231xx(state) && max_buf_size > 16)
		max_buf_size = 16;

	अगर (request_firmware(&fw, fwname, FWDEV(client)) != 0) अणु
		v4l_err(client, "unable to open firmware %s\n", fwname);
		वापस -EINVAL;
	पूर्ण

	start_fw_load(client);

	buffer[0] = 0x08;
	buffer[1] = 0x02;

	size = fw->size;
	ptr = fw->data;
	जबतक (size > 0) अणु
		पूर्णांक len = min(max_buf_size - 2, size);

		स_नकल(buffer + 2, ptr, len);

		retval = fw_ग_लिखो(client, buffer, len + 2);

		अगर (retval < 0) अणु
			release_firmware(fw);
			वापस retval;
		पूर्ण

		size -= len;
		ptr += len;
	पूर्ण

	end_fw_load(client);

	size = fw->size;
	release_firmware(fw);

	अगर (is_cx2388x(state)) अणु
		/* Restore GPIO configuration after f/w load */
		cx25840_ग_लिखो(client, 0x160, gpio_oe);
		cx25840_ग_लिखो(client, 0x164, gpio_da);
	पूर्ण

	वापस check_fw_load(client, size);
पूर्ण

MODULE_FIRMWARE(CX2388x_FIRMWARE);
MODULE_FIRMWARE(CX231xx_FIRMWARE);
MODULE_FIRMWARE(CX25840_FIRMWARE);

