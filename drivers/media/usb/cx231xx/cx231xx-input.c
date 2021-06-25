<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// cx231xx IR glue driver
//
// Copyright (c) 2010 Mauro Carvalho Chehab <mchehab@kernel.org>
//
// Polaris (cx231xx) has its support क्रम IR's with a design बंद to MCE.
// however, a few designs are using an बाह्यal I2C chip क्रम IR, instead
// of using the one provided by the chip.
// This driver provides support क्रम those extra devices

#समावेश "cx231xx.h"
#समावेश <linux/slab.h>
#समावेश <linux/bitrev.h>

#घोषणा MODULE_NAME "cx231xx-input"

अटल पूर्णांक get_key_isdbt(काष्ठा IR_i2c *ir, क्रमागत rc_proto *protocol,
			 u32 *pscancode, u8 *toggle)
अणु
	पूर्णांक	rc;
	u8	cmd, scancode;

	dev_dbg(&ir->rc->dev, "%s\n", __func__);

		/* poll IR chip */
	rc = i2c_master_recv(ir->c, &cmd, 1);
	अगर (rc < 0)
		वापस rc;
	अगर (rc != 1)
		वापस -EIO;

	/* it seems that 0xFE indicates that a button is still hold
	   करोwn, जबतक 0xff indicates that no button is hold
	   करोwn. 0xfe sequences are someबार पूर्णांकerrupted by 0xFF */

	अगर (cmd == 0xff)
		वापस 0;

	scancode = bitrev8(cmd);

	dev_dbg(&ir->rc->dev, "cmd %02x, scan = %02x\n", cmd, scancode);

	*protocol = RC_PROTO_OTHER;
	*pscancode = scancode;
	*toggle = 0;
	वापस 1;
पूर्ण

पूर्णांक cx231xx_ir_init(काष्ठा cx231xx *dev)
अणु
	काष्ठा i2c_board_info info;
	u8 ir_i2c_bus;

	dev_dbg(dev->dev, "%s\n", __func__);

	/* Only initialize अगर a rc keycode map is defined */
	अगर (!cx231xx_boards[dev->model].rc_map_name)
		वापस -ENODEV;

	request_module("ir-kbd-i2c");

	स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
	स_रखो(&dev->init_data, 0, माप(dev->init_data));
	dev->init_data.rc_dev = rc_allocate_device(RC_DRIVER_SCANCODE);
	अगर (!dev->init_data.rc_dev)
		वापस -ENOMEM;

	dev->init_data.name = cx231xx_boards[dev->model].name;

	strscpy(info.type, "ir_video", I2C_NAME_SIZE);
	info.platक्रमm_data = &dev->init_data;

	/*
	 * Board-dependent values
	 *
	 * For now, there's just one type of hardware design using
	 * an i2c device.
	 */
	dev->init_data.get_key = get_key_isdbt;
	dev->init_data.ir_codes = cx231xx_boards[dev->model].rc_map_name;
	/* The i2c micro-controller only outमाला_दो the cmd part of NEC protocol */
	dev->init_data.rc_dev->scancode_mask = 0xff;
	dev->init_data.rc_dev->driver_name = "cx231xx";
	dev->init_data.type = RC_PROTO_BIT_NEC;
	info.addr = 0x30;

	/* Load and bind ir-kbd-i2c */
	ir_i2c_bus = cx231xx_boards[dev->model].ir_i2c_master;
	dev_dbg(dev->dev, "Trying to bind ir at bus %d, addr 0x%02x\n",
		ir_i2c_bus, info.addr);
	dev->ir_i2c_client = i2c_new_client_device(
		cx231xx_get_i2c_adap(dev, ir_i2c_bus), &info);

	वापस 0;
पूर्ण

व्योम cx231xx_ir_निकास(काष्ठा cx231xx *dev)
अणु
	i2c_unरेजिस्टर_device(dev->ir_i2c_client);
	dev->ir_i2c_client = शून्य;
पूर्ण
