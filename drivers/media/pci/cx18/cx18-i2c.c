<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  cx18 I2C functions
 *
 *  Derived from ivtv-i2c.c
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

#समावेश "cx18-driver.h"
#समावेश "cx18-io.h"
#समावेश "cx18-cards.h"
#समावेश "cx18-gpio.h"
#समावेश "cx18-i2c.h"
#समावेश "cx18-irq.h"

#घोषणा CX18_REG_I2C_1_WR   0xf15000
#घोषणा CX18_REG_I2C_1_RD   0xf15008
#घोषणा CX18_REG_I2C_2_WR   0xf25100
#घोषणा CX18_REG_I2C_2_RD   0xf25108

#घोषणा SETSCL_BIT      0x0001
#घोषणा SETSDL_BIT      0x0002
#घोषणा GETSCL_BIT      0x0004
#घोषणा GETSDL_BIT      0x0008

#घोषणा CX18_CS5345_I2C_ADDR		0x4c
#घोषणा CX18_Z8F0811_IR_TX_I2C_ADDR	0x70
#घोषणा CX18_Z8F0811_IR_RX_I2C_ADDR	0x71

/* This array should match the CX18_HW_ defines */
अटल स्थिर u8 hw_addrs[] = अणु
	0,				/* CX18_HW_TUNER */
	0,				/* CX18_HW_TVEEPROM */
	CX18_CS5345_I2C_ADDR,		/* CX18_HW_CS5345 */
	0,				/* CX18_HW_DVB */
	0,				/* CX18_HW_418_AV */
	0,				/* CX18_HW_GPIO_MUX */
	0,				/* CX18_HW_GPIO_RESET_CTRL */
	CX18_Z8F0811_IR_RX_I2C_ADDR,	/* CX18_HW_Z8F0811_IR_HAUP */
पूर्ण;

/* This array should match the CX18_HW_ defines */
/* This might well become a card-specअगरic array */
अटल स्थिर u8 hw_bus[] = अणु
	1,	/* CX18_HW_TUNER */
	0,	/* CX18_HW_TVEEPROM */
	0,	/* CX18_HW_CS5345 */
	0,	/* CX18_HW_DVB */
	0,	/* CX18_HW_418_AV */
	0,	/* CX18_HW_GPIO_MUX */
	0,	/* CX18_HW_GPIO_RESET_CTRL */
	0,	/* CX18_HW_Z8F0811_IR_HAUP */
पूर्ण;

/* This array should match the CX18_HW_ defines */
अटल स्थिर अक्षर * स्थिर hw_devicenames[] = अणु
	"tuner",
	"tveeprom",
	"cs5345",
	"cx23418_DTV",
	"cx23418_AV",
	"gpio_mux",
	"gpio_reset_ctrl",
	"ir_z8f0811_haup",
पूर्ण;

अटल पूर्णांक cx18_i2c_new_ir(काष्ठा cx18 *cx, काष्ठा i2c_adapter *adap, u32 hw,
			   स्थिर अक्षर *type, u8 addr)
अणु
	काष्ठा i2c_board_info info;
	काष्ठा IR_i2c_init_data *init_data = &cx->ir_i2c_init_data;
	अचिन्हित लघु addr_list[2] = अणु addr, I2C_CLIENT_END पूर्ण;

	स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
	strscpy(info.type, type, I2C_NAME_SIZE);

	/* Our शेष inक्रमmation क्रम ir-kbd-i2c.c to use */
	चयन (hw) अणु
	हाल CX18_HW_Z8F0811_IR_HAUP:
		init_data->ir_codes = RC_MAP_HAUPPAUGE;
		init_data->पूर्णांकernal_get_key_func = IR_KBD_GET_KEY_HAUP_XVR;
		init_data->type = RC_PROTO_BIT_RC5 | RC_PROTO_BIT_RC6_MCE |
							RC_PROTO_BIT_RC6_6A_32;
		init_data->name = cx->card_name;
		info.platक्रमm_data = init_data;
		अवरोध;
	पूर्ण

	वापस IS_ERR(i2c_new_scanned_device(adap, &info, addr_list, शून्य)) ?
	       -1 : 0;
पूर्ण

पूर्णांक cx18_i2c_रेजिस्टर(काष्ठा cx18 *cx, अचिन्हित idx)
अणु
	काष्ठा v4l2_subdev *sd;
	पूर्णांक bus = hw_bus[idx];
	काष्ठा i2c_adapter *adap = &cx->i2c_adap[bus];
	स्थिर अक्षर *type = hw_devicenames[idx];
	u32 hw = 1 << idx;

	अगर (hw == CX18_HW_TUNER) अणु
		/* special tuner group handling */
		sd = v4l2_i2c_new_subdev(&cx->v4l2_dev,
				adap, type, 0, cx->card_i2c->radio);
		अगर (sd != शून्य)
			sd->grp_id = hw;
		sd = v4l2_i2c_new_subdev(&cx->v4l2_dev,
				adap, type, 0, cx->card_i2c->demod);
		अगर (sd != शून्य)
			sd->grp_id = hw;
		sd = v4l2_i2c_new_subdev(&cx->v4l2_dev,
				adap, type, 0, cx->card_i2c->tv);
		अगर (sd != शून्य)
			sd->grp_id = hw;
		वापस sd != शून्य ? 0 : -1;
	पूर्ण

	अगर (hw == CX18_HW_Z8F0811_IR_HAUP)
		वापस cx18_i2c_new_ir(cx, adap, hw, type, hw_addrs[idx]);

	/* Is it not an I2C device or one we करो not wish to रेजिस्टर? */
	अगर (!hw_addrs[idx])
		वापस -1;

	/* It's an I2C device other than an analog tuner or IR chip */
	sd = v4l2_i2c_new_subdev(&cx->v4l2_dev, adap, type, hw_addrs[idx],
				 शून्य);
	अगर (sd != शून्य)
		sd->grp_id = hw;
	वापस sd != शून्य ? 0 : -1;
पूर्ण

/* Find the first member of the subdev group id in hw */
काष्ठा v4l2_subdev *cx18_find_hw(काष्ठा cx18 *cx, u32 hw)
अणु
	काष्ठा v4l2_subdev *result = शून्य;
	काष्ठा v4l2_subdev *sd;

	spin_lock(&cx->v4l2_dev.lock);
	v4l2_device_क्रम_each_subdev(sd, &cx->v4l2_dev) अणु
		अगर (sd->grp_id == hw) अणु
			result = sd;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&cx->v4l2_dev.lock);
	वापस result;
पूर्ण

अटल व्योम cx18_setscl(व्योम *data, पूर्णांक state)
अणु
	काष्ठा cx18 *cx = ((काष्ठा cx18_i2c_algo_callback_data *)data)->cx;
	पूर्णांक bus_index = ((काष्ठा cx18_i2c_algo_callback_data *)data)->bus_index;
	u32 addr = bus_index ? CX18_REG_I2C_2_WR : CX18_REG_I2C_1_WR;
	u32 r = cx18_पढ़ो_reg(cx, addr);

	अगर (state)
		cx18_ग_लिखो_reg(cx, r | SETSCL_BIT, addr);
	अन्यथा
		cx18_ग_लिखो_reg(cx, r & ~SETSCL_BIT, addr);
पूर्ण

अटल व्योम cx18_setsda(व्योम *data, पूर्णांक state)
अणु
	काष्ठा cx18 *cx = ((काष्ठा cx18_i2c_algo_callback_data *)data)->cx;
	पूर्णांक bus_index = ((काष्ठा cx18_i2c_algo_callback_data *)data)->bus_index;
	u32 addr = bus_index ? CX18_REG_I2C_2_WR : CX18_REG_I2C_1_WR;
	u32 r = cx18_पढ़ो_reg(cx, addr);

	अगर (state)
		cx18_ग_लिखो_reg(cx, r | SETSDL_BIT, addr);
	अन्यथा
		cx18_ग_लिखो_reg(cx, r & ~SETSDL_BIT, addr);
पूर्ण

अटल पूर्णांक cx18_माला_लोcl(व्योम *data)
अणु
	काष्ठा cx18 *cx = ((काष्ठा cx18_i2c_algo_callback_data *)data)->cx;
	पूर्णांक bus_index = ((काष्ठा cx18_i2c_algo_callback_data *)data)->bus_index;
	u32 addr = bus_index ? CX18_REG_I2C_2_RD : CX18_REG_I2C_1_RD;

	वापस cx18_पढ़ो_reg(cx, addr) & GETSCL_BIT;
पूर्ण

अटल पूर्णांक cx18_माला_लोda(व्योम *data)
अणु
	काष्ठा cx18 *cx = ((काष्ठा cx18_i2c_algo_callback_data *)data)->cx;
	पूर्णांक bus_index = ((काष्ठा cx18_i2c_algo_callback_data *)data)->bus_index;
	u32 addr = bus_index ? CX18_REG_I2C_2_RD : CX18_REG_I2C_1_RD;

	वापस cx18_पढ़ो_reg(cx, addr) & GETSDL_BIT;
पूर्ण

/* ढाँचा क्रम i2c-bit-algo */
अटल स्थिर काष्ठा i2c_adapter cx18_i2c_adap_ढाँचा = अणु
	.name = "cx18 i2c driver",
	.algo = शून्य,                   /* set by i2c-algo-bit */
	.algo_data = शून्य,              /* filled from ढाँचा */
	.owner = THIS_MODULE,
पूर्ण;

#घोषणा CX18_SCL_PERIOD (10) /* usecs. 10 usec is period क्रम a 100 KHz घड़ी */
#घोषणा CX18_ALGO_BIT_TIMEOUT (2) /* seconds */

अटल स्थिर काष्ठा i2c_algo_bit_data cx18_i2c_algo_ढाँचा = अणु
	.setsda		= cx18_setsda,
	.setscl		= cx18_setscl,
	.माला_लोda		= cx18_माला_लोda,
	.माला_लोcl		= cx18_माला_लोcl,
	.udelay		= CX18_SCL_PERIOD/2,       /* 1/2 घड़ी period in usec*/
	.समयout	= CX18_ALGO_BIT_TIMEOUT*HZ /* jअगरfies */
पूर्ण;

/* init + रेजिस्टर i2c adapter */
पूर्णांक init_cx18_i2c(काष्ठा cx18 *cx)
अणु
	पूर्णांक i, err;
	CX18_DEBUG_I2C("i2c init\n");

	क्रम (i = 0; i < 2; i++) अणु
		/* Setup algorithm क्रम adapter */
		cx->i2c_algo[i] = cx18_i2c_algo_ढाँचा;
		cx->i2c_algo_cb_data[i].cx = cx;
		cx->i2c_algo_cb_data[i].bus_index = i;
		cx->i2c_algo[i].data = &cx->i2c_algo_cb_data[i];

		/* Setup adapter */
		cx->i2c_adap[i] = cx18_i2c_adap_ढाँचा;
		cx->i2c_adap[i].algo_data = &cx->i2c_algo[i];
		प्र_लिखो(cx->i2c_adap[i].name + म_माप(cx->i2c_adap[i].name),
				" #%d-%d", cx->instance, i);
		i2c_set_adapdata(&cx->i2c_adap[i], &cx->v4l2_dev);
		cx->i2c_adap[i].dev.parent = &cx->pci_dev->dev;
	पूर्ण

	अगर (cx18_पढ़ो_reg(cx, CX18_REG_I2C_2_WR) != 0x0003c02f) अणु
		/* Reset/Unreset I2C hardware block */
		/* Clock select 220MHz */
		cx18_ग_लिखो_reg_expect(cx, 0x10000000, 0xc71004,
					  0x00000000, 0x10001000);
		/* Clock Enable */
		cx18_ग_लिखो_reg_expect(cx, 0x10001000, 0xc71024,
					  0x00001000, 0x10001000);
	पूर्ण
	/* courtesy of Steven Toth <stoth@hauppauge.com> */
	cx18_ग_लिखो_reg_expect(cx, 0x00c00000, 0xc7001c, 0x00000000, 0x00c000c0);
	mdelay(10);
	cx18_ग_लिखो_reg_expect(cx, 0x00c000c0, 0xc7001c, 0x000000c0, 0x00c000c0);
	mdelay(10);
	cx18_ग_लिखो_reg_expect(cx, 0x00c00000, 0xc7001c, 0x00000000, 0x00c000c0);
	mdelay(10);

	/* Set to edge-triggered पूर्णांकrs. */
	cx18_ग_लिखो_reg(cx, 0x00c00000, 0xc730c8);
	/* Clear any stale पूर्णांकrs */
	cx18_ग_लिखो_reg_expect(cx, HW2_I2C1_INT|HW2_I2C2_INT, HW2_INT_CLR_STATUS,
		       ~(HW2_I2C1_INT|HW2_I2C2_INT), HW2_I2C1_INT|HW2_I2C2_INT);

	/* Hw I2C1 Clock Freq ~100kHz */
	cx18_ग_लिखो_reg(cx, 0x00021c0f & ~4, CX18_REG_I2C_1_WR);
	cx18_setscl(&cx->i2c_algo_cb_data[0], 1);
	cx18_setsda(&cx->i2c_algo_cb_data[0], 1);

	/* Hw I2C2 Clock Freq ~100kHz */
	cx18_ग_लिखो_reg(cx, 0x00021c0f & ~4, CX18_REG_I2C_2_WR);
	cx18_setscl(&cx->i2c_algo_cb_data[1], 1);
	cx18_setsda(&cx->i2c_algo_cb_data[1], 1);

	cx18_call_hw(cx, CX18_HW_GPIO_RESET_CTRL,
		     core, reset, (u32) CX18_GPIO_RESET_I2C);

	err = i2c_bit_add_bus(&cx->i2c_adap[0]);
	अगर (err)
		जाओ err;
	err = i2c_bit_add_bus(&cx->i2c_adap[1]);
	अगर (err)
		जाओ err_del_bus_0;
	वापस 0;

 err_del_bus_0:
	i2c_del_adapter(&cx->i2c_adap[0]);
 err:
	वापस err;
पूर्ण

व्योम निकास_cx18_i2c(काष्ठा cx18 *cx)
अणु
	पूर्णांक i;
	CX18_DEBUG_I2C("i2c exit\n");
	cx18_ग_लिखो_reg(cx, cx18_पढ़ो_reg(cx, CX18_REG_I2C_1_WR) | 4,
							CX18_REG_I2C_1_WR);
	cx18_ग_लिखो_reg(cx, cx18_पढ़ो_reg(cx, CX18_REG_I2C_2_WR) | 4,
							CX18_REG_I2C_2_WR);

	क्रम (i = 0; i < 2; i++) अणु
		i2c_del_adapter(&cx->i2c_adap[i]);
	पूर्ण
पूर्ण

/*
   Hauppauge HVR1600 should have:
   32 cx24227
   98 unknown
   a0 eeprom
   c2 tuner
   e? zilog ir
   */
