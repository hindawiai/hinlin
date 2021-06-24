<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    I2C functions
    Copyright (C) 2003-2004  Kevin Thayer <nufan_wfk at yahoo.com>
    Copyright (C) 2005-2007  Hans Verkuil <hverkuil@xs4all.nl>

 */

/*
    This file includes an i2c implementation that was reverse engineered
    from the Hauppauge winकरोws driver.  Older ivtv versions used i2c-algo-bit,
    which whilst fine under most circumstances, had trouble with the Zilog
    CPU on the PVR-150 which handles IR functions (occasional inability to
    communicate with the chip until it was reset) and also with the i2c
    bus being completely unreachable when multiple PVR cards were present.

    The implementation is very similar to i2c-algo-bit, but there are enough
    subtle dअगरferences that the two are hard to merge.  The general strategy
    employed by i2c-algo-bit is to use udelay() to implement the timing
    when putting out bits on the scl/sda lines.  The general strategy taken
    here is to poll the lines क्रम state changes (see ivtv_रुकोscl and
    ivtv_रुकोsda).  In addition there are small delays at various locations
    which poll the SCL line 5 बार (ivtv_scldelay).  I would guess that
    since this is memory mapped I/O that the length of those delays is tied
    to the PCI bus घड़ी.  There is some extra code to करो with recovery
    and retries.  Since it is not known what causes the actual i2c problems
    in the first place, the only goal अगर one was to attempt to use
    i2c-algo-bit would be to try to make it follow the same code path.
    This would be a lot of work, and I'm also not convinced that it would
    provide a generic benefit to i2c-algo-bit.  Thereक्रमe consider this
    an engineering solution -- not pretty, but it works.

    Some more general comments about what we are करोing:

    The i2c bus is a 2 wire serial bus, with घड़ी (SCL) and data (SDA)
    lines.  To communicate on the bus (as a master, we करोn't act as a slave),
    we first initiate a start condition (ivtv_start).  We then ग_लिखो the
    address of the device that we want to communicate with, aदीर्घ with a flag
    that indicates whether this is a पढ़ो or a ग_लिखो.  The slave then issues
    an ACK संकेत (ivtv_ack), which tells us that it is पढ़ोy क्रम पढ़ोing /
    writing.  We then proceed with पढ़ोing or writing (ivtv_पढ़ो/ivtv_ग_लिखो),
    and finally issue a stop condition (ivtv_stop) to make the bus available
    to other masters.

    There is an additional क्रमm of transaction where a ग_लिखो may be
    immediately followed by a पढ़ो.  In this हाल, there is no पूर्णांकervening
    stop condition.  (Only the msp3400 chip uses this method of data transfer).
 */

#समावेश "ivtv-driver.h"
#समावेश "ivtv-cards.h"
#समावेश "ivtv-gpio.h"
#समावेश "ivtv-i2c.h"
#समावेश <media/drv-पूर्णांकf/cx25840.h>

/* i2c implementation क्रम cx23415/6 chip, ivtv project.
 * Author: Kevin Thayer (nufan_wfk at yahoo.com)
 */
/* i2c stuff */
#घोषणा IVTV_REG_I2C_SETSCL_OFFSET 0x7000
#घोषणा IVTV_REG_I2C_SETSDA_OFFSET 0x7004
#घोषणा IVTV_REG_I2C_GETSCL_OFFSET 0x7008
#घोषणा IVTV_REG_I2C_GETSDA_OFFSET 0x700c

#घोषणा IVTV_CS53L32A_I2C_ADDR		0x11
#घोषणा IVTV_M52790_I2C_ADDR		0x48
#घोषणा IVTV_CX25840_I2C_ADDR		0x44
#घोषणा IVTV_SAA7115_I2C_ADDR		0x21
#घोषणा IVTV_SAA7127_I2C_ADDR		0x44
#घोषणा IVTV_SAA717x_I2C_ADDR		0x21
#घोषणा IVTV_MSP3400_I2C_ADDR		0x40
#घोषणा IVTV_HAUPPAUGE_I2C_ADDR		0x50
#घोषणा IVTV_WM8739_I2C_ADDR		0x1a
#घोषणा IVTV_WM8775_I2C_ADDR		0x1b
#घोषणा IVTV_TEA5767_I2C_ADDR		0x60
#घोषणा IVTV_UPD64031A_I2C_ADDR		0x12
#घोषणा IVTV_UPD64083_I2C_ADDR		0x5c
#घोषणा IVTV_VP27SMPX_I2C_ADDR		0x5b
#घोषणा IVTV_M52790_I2C_ADDR		0x48
#घोषणा IVTV_AVERMEDIA_IR_RX_I2C_ADDR	0x40
#घोषणा IVTV_HAUP_EXT_IR_RX_I2C_ADDR	0x1a
#घोषणा IVTV_HAUP_INT_IR_RX_I2C_ADDR	0x18
#घोषणा IVTV_Z8F0811_IR_TX_I2C_ADDR	0x70
#घोषणा IVTV_Z8F0811_IR_RX_I2C_ADDR	0x71
#घोषणा IVTV_ADAPTEC_IR_ADDR		0x6b

/* This array should match the IVTV_HW_ defines */
अटल स्थिर u8 hw_addrs[] = अणु
	IVTV_CX25840_I2C_ADDR,
	IVTV_SAA7115_I2C_ADDR,
	IVTV_SAA7127_I2C_ADDR,
	IVTV_MSP3400_I2C_ADDR,
	0,
	IVTV_WM8775_I2C_ADDR,
	IVTV_CS53L32A_I2C_ADDR,
	0,
	IVTV_SAA7115_I2C_ADDR,
	IVTV_UPD64031A_I2C_ADDR,
	IVTV_UPD64083_I2C_ADDR,
	IVTV_SAA717x_I2C_ADDR,
	IVTV_WM8739_I2C_ADDR,
	IVTV_VP27SMPX_I2C_ADDR,
	IVTV_M52790_I2C_ADDR,
	0,				/* IVTV_HW_GPIO dummy driver ID */
	IVTV_AVERMEDIA_IR_RX_I2C_ADDR,	/* IVTV_HW_I2C_IR_RX_AVER */
	IVTV_HAUP_EXT_IR_RX_I2C_ADDR,	/* IVTV_HW_I2C_IR_RX_HAUP_EXT */
	IVTV_HAUP_INT_IR_RX_I2C_ADDR,	/* IVTV_HW_I2C_IR_RX_HAUP_INT */
	IVTV_Z8F0811_IR_RX_I2C_ADDR,	/* IVTV_HW_Z8F0811_IR_HAUP */
	IVTV_ADAPTEC_IR_ADDR,		/* IVTV_HW_I2C_IR_RX_ADAPTEC */
पूर्ण;

/* This array should match the IVTV_HW_ defines */
अटल स्थिर अक्षर * स्थिर hw_devicenames[] = अणु
	"cx25840",
	"saa7115",
	"saa7127_auto",	/* saa7127 or saa7129 */
	"msp3400",
	"tuner",
	"wm8775",
	"cs53l32a",
	"tveeprom",
	"saa7114",
	"upd64031a",
	"upd64083",
	"saa717x",
	"wm8739",
	"vp27smpx",
	"m52790",
	"gpio",
	"ir_video",		/* IVTV_HW_I2C_IR_RX_AVER */
	"ir_video",		/* IVTV_HW_I2C_IR_RX_HAUP_EXT */
	"ir_video",		/* IVTV_HW_I2C_IR_RX_HAUP_INT */
	"ir_z8f0811_haup",	/* IVTV_HW_Z8F0811_IR_HAUP */
	"ir_video",		/* IVTV_HW_I2C_IR_RX_ADAPTEC */
पूर्ण;

अटल पूर्णांक get_key_adaptec(काष्ठा IR_i2c *ir, क्रमागत rc_proto *protocol,
			   u32 *scancode, u8 *toggle)
अणु
	अचिन्हित अक्षर keybuf[4];

	keybuf[0] = 0x00;
	i2c_master_send(ir->c, keybuf, 1);
	/* poll IR chip */
	अगर (i2c_master_recv(ir->c, keybuf, माप(keybuf)) != माप(keybuf)) अणु
		वापस 0;
	पूर्ण

	/* key pressed ? */
	अगर (keybuf[2] == 0xff)
		वापस 0;

	/* हटाओ repeat bit */
	keybuf[2] &= 0x7f;
	keybuf[3] |= 0x80;

	*protocol = RC_PROTO_UNKNOWN;
	*scancode = keybuf[3] | keybuf[2] << 8 | keybuf[1] << 16 |keybuf[0] << 24;
	*toggle = 0;
	वापस 1;
पूर्ण

अटल पूर्णांक ivtv_i2c_new_ir(काष्ठा ivtv *itv, u32 hw, स्थिर अक्षर *type, u8 addr)
अणु
	काष्ठा i2c_board_info info;
	काष्ठा i2c_adapter *adap = &itv->i2c_adap;
	काष्ठा IR_i2c_init_data *init_data = &itv->ir_i2c_init_data;
	अचिन्हित लघु addr_list[2] = अणु addr, I2C_CLIENT_END पूर्ण;

	/* Only allow one IR receiver to be रेजिस्टरed per board */
	अगर (itv->hw_flags & IVTV_HW_IR_ANY)
		वापस -1;

	/* Our शेष inक्रमmation क्रम ir-kbd-i2c.c to use */
	चयन (hw) अणु
	हाल IVTV_HW_I2C_IR_RX_AVER:
		init_data->ir_codes = RC_MAP_AVERMEDIA_CARDBUS;
		init_data->पूर्णांकernal_get_key_func =
					IR_KBD_GET_KEY_AVERMEDIA_CARDBUS;
		init_data->type = RC_PROTO_BIT_OTHER;
		init_data->name = "AVerMedia AVerTV card";
		अवरोध;
	हाल IVTV_HW_I2C_IR_RX_HAUP_EXT:
	हाल IVTV_HW_I2C_IR_RX_HAUP_INT:
		init_data->ir_codes = RC_MAP_HAUPPAUGE;
		init_data->पूर्णांकernal_get_key_func = IR_KBD_GET_KEY_HAUP;
		init_data->type = RC_PROTO_BIT_RC5;
		init_data->name = itv->card_name;
		अवरोध;
	हाल IVTV_HW_Z8F0811_IR_HAUP:
		/* Default to grey remote */
		init_data->ir_codes = RC_MAP_HAUPPAUGE;
		init_data->पूर्णांकernal_get_key_func = IR_KBD_GET_KEY_HAUP_XVR;
		init_data->type = RC_PROTO_BIT_RC5 | RC_PROTO_BIT_RC6_MCE |
							RC_PROTO_BIT_RC6_6A_32;
		init_data->name = itv->card_name;
		अवरोध;
	हाल IVTV_HW_I2C_IR_RX_ADAPTEC:
		init_data->get_key = get_key_adaptec;
		init_data->name = itv->card_name;
		/* FIXME: The protocol and RC_MAP needs to be corrected */
		init_data->ir_codes = RC_MAP_EMPTY;
		init_data->type = RC_PROTO_BIT_UNKNOWN;
		अवरोध;
	पूर्ण

	स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
	info.platक्रमm_data = init_data;
	strscpy(info.type, type, I2C_NAME_SIZE);

	वापस IS_ERR(i2c_new_scanned_device(adap, &info, addr_list, शून्य)) ?
	       -1 : 0;
पूर्ण

/* Instantiate the IR receiver device using probing -- undesirable */
व्योम ivtv_i2c_new_ir_legacy(काष्ठा ivtv *itv)
अणु
	काष्ठा i2c_board_info info;
	/*
	 * The बाह्यal IR receiver is at i2c address 0x34.
	 * The पूर्णांकernal IR receiver is at i2c address 0x30.
	 *
	 * In theory, both can be fitted, and Hauppauge suggests an बाह्यal
	 * overrides an पूर्णांकernal.  That's why we probe 0x1a (~0x34) first. CB
	 *
	 * Some of these addresses we probe may collide with other i2c address
	 * allocations, so this function must be called after all other i2c
	 * devices we care about are रेजिस्टरed.
	 */
	अटल स्थिर अचिन्हित लघु addr_list[] = अणु
		0x1a,	/* Hauppauge IR बाह्यal - collides with WM8739 */
		0x18,	/* Hauppauge IR पूर्णांकernal */
		I2C_CLIENT_END
	पूर्ण;

	स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
	strscpy(info.type, "ir_video", I2C_NAME_SIZE);
	i2c_new_scanned_device(&itv->i2c_adap, &info, addr_list, शून्य);
पूर्ण

पूर्णांक ivtv_i2c_रेजिस्टर(काष्ठा ivtv *itv, अचिन्हित idx)
अणु
	काष्ठा v4l2_subdev *sd;
	काष्ठा i2c_adapter *adap = &itv->i2c_adap;
	स्थिर अक्षर *type = hw_devicenames[idx];
	u32 hw = 1 << idx;

	अगर (hw == IVTV_HW_TUNER) अणु
		/* special tuner handling */
		sd = v4l2_i2c_new_subdev(&itv->v4l2_dev, adap, type, 0,
				itv->card_i2c->radio);
		अगर (sd)
			sd->grp_id = 1 << idx;
		sd = v4l2_i2c_new_subdev(&itv->v4l2_dev, adap, type, 0,
				itv->card_i2c->demod);
		अगर (sd)
			sd->grp_id = 1 << idx;
		sd = v4l2_i2c_new_subdev(&itv->v4l2_dev, adap, type, 0,
				itv->card_i2c->tv);
		अगर (sd)
			sd->grp_id = 1 << idx;
		वापस sd ? 0 : -1;
	पूर्ण

	अगर (hw & IVTV_HW_IR_ANY)
		वापस ivtv_i2c_new_ir(itv, hw, type, hw_addrs[idx]);

	/* Is it not an I2C device or one we करो not wish to रेजिस्टर? */
	अगर (!hw_addrs[idx])
		वापस -1;

	/* It's an I2C device other than an analog tuner or IR chip */
	अगर (hw == IVTV_HW_UPD64031A || hw == IVTV_HW_UPD6408X) अणु
		sd = v4l2_i2c_new_subdev(&itv->v4l2_dev,
				adap, type, 0, I2C_ADDRS(hw_addrs[idx]));
	पूर्ण अन्यथा अगर (hw == IVTV_HW_CX25840) अणु
		काष्ठा cx25840_platक्रमm_data pdata;
		काष्ठा i2c_board_info cx25840_info = अणु
			.type = "cx25840",
			.addr = hw_addrs[idx],
			.platक्रमm_data = &pdata,
		पूर्ण;

		स_रखो(&pdata, 0, माप(pdata));
		pdata.pvr150_workaround = itv->pvr150_workaround;
		sd = v4l2_i2c_new_subdev_board(&itv->v4l2_dev, adap,
				&cx25840_info, शून्य);
	पूर्ण अन्यथा अणु
		sd = v4l2_i2c_new_subdev(&itv->v4l2_dev,
				adap, type, hw_addrs[idx], शून्य);
	पूर्ण
	अगर (sd)
		sd->grp_id = 1 << idx;
	वापस sd ? 0 : -1;
पूर्ण

काष्ठा v4l2_subdev *ivtv_find_hw(काष्ठा ivtv *itv, u32 hw)
अणु
	काष्ठा v4l2_subdev *result = शून्य;
	काष्ठा v4l2_subdev *sd;

	spin_lock(&itv->v4l2_dev.lock);
	v4l2_device_क्रम_each_subdev(sd, &itv->v4l2_dev) अणु
		अगर (sd->grp_id == hw) अणु
			result = sd;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&itv->v4l2_dev.lock);
	वापस result;
पूर्ण

/* Set the serial घड़ी line to the desired state */
अटल व्योम ivtv_setscl(काष्ठा ivtv *itv, पूर्णांक state)
अणु
	/* ग_लिखो them out */
	/* ग_लिखो bits are inverted */
	ग_लिखो_reg(~state, IVTV_REG_I2C_SETSCL_OFFSET);
पूर्ण

/* Set the serial data line to the desired state */
अटल व्योम ivtv_setsda(काष्ठा ivtv *itv, पूर्णांक state)
अणु
	/* ग_लिखो them out */
	/* ग_लिखो bits are inverted */
	ग_लिखो_reg(~state & 1, IVTV_REG_I2C_SETSDA_OFFSET);
पूर्ण

/* Read the serial घड़ी line */
अटल पूर्णांक ivtv_माला_लोcl(काष्ठा ivtv *itv)
अणु
	वापस पढ़ो_reg(IVTV_REG_I2C_GETSCL_OFFSET) & 1;
पूर्ण

/* Read the serial data line */
अटल पूर्णांक ivtv_माला_लोda(काष्ठा ivtv *itv)
अणु
	वापस पढ़ो_reg(IVTV_REG_I2C_GETSDA_OFFSET) & 1;
पूर्ण

/* Implement a लघु delay by polling the serial घड़ी line */
अटल व्योम ivtv_scldelay(काष्ठा ivtv *itv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 5; ++i)
		ivtv_माला_लोcl(itv);
पूर्ण

/* Wait क्रम the serial घड़ी line to become set to a specअगरic value */
अटल पूर्णांक ivtv_रुकोscl(काष्ठा ivtv *itv, पूर्णांक val)
अणु
	पूर्णांक i;

	ivtv_scldelay(itv);
	क्रम (i = 0; i < 1000; ++i) अणु
		अगर (ivtv_माला_लोcl(itv) == val)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* Wait क्रम the serial data line to become set to a specअगरic value */
अटल पूर्णांक ivtv_रुकोsda(काष्ठा ivtv *itv, पूर्णांक val)
अणु
	पूर्णांक i;

	ivtv_scldelay(itv);
	क्रम (i = 0; i < 1000; ++i) अणु
		अगर (ivtv_माला_लोda(itv) == val)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* Wait क्रम the slave to issue an ACK */
अटल पूर्णांक ivtv_ack(काष्ठा ivtv *itv)
अणु
	पूर्णांक ret = 0;

	अगर (ivtv_माला_लोcl(itv) == 1) अणु
		IVTV_DEBUG_HI_I2C("SCL was high starting an ack\n");
		ivtv_setscl(itv, 0);
		अगर (!ivtv_रुकोscl(itv, 0)) अणु
			IVTV_DEBUG_I2C("Could not set SCL low starting an ack\n");
			वापस -EREMOTEIO;
		पूर्ण
	पूर्ण
	ivtv_setsda(itv, 1);
	ivtv_scldelay(itv);
	ivtv_setscl(itv, 1);
	अगर (!ivtv_रुकोsda(itv, 0)) अणु
		IVTV_DEBUG_I2C("Slave did not ack\n");
		ret = -EREMOTEIO;
	पूर्ण
	ivtv_setscl(itv, 0);
	अगर (!ivtv_रुकोscl(itv, 0)) अणु
		IVTV_DEBUG_I2C("Failed to set SCL low after ACK\n");
		ret = -EREMOTEIO;
	पूर्ण
	वापस ret;
पूर्ण

/* Write a single byte to the i2c bus and रुको क्रम the slave to ACK */
अटल पूर्णांक ivtv_sendbyte(काष्ठा ivtv *itv, अचिन्हित अक्षर byte)
अणु
	पूर्णांक i, bit;

	IVTV_DEBUG_HI_I2C("write %x\n",byte);
	क्रम (i = 0; i < 8; ++i, byte<<=1) अणु
		ivtv_setscl(itv, 0);
		अगर (!ivtv_रुकोscl(itv, 0)) अणु
			IVTV_DEBUG_I2C("Error setting SCL low\n");
			वापस -EREMOTEIO;
		पूर्ण
		bit = (byte>>7)&1;
		ivtv_setsda(itv, bit);
		अगर (!ivtv_रुकोsda(itv, bit)) अणु
			IVTV_DEBUG_I2C("Error setting SDA\n");
			वापस -EREMOTEIO;
		पूर्ण
		ivtv_setscl(itv, 1);
		अगर (!ivtv_रुकोscl(itv, 1)) अणु
			IVTV_DEBUG_I2C("Slave not ready for bit\n");
			वापस -EREMOTEIO;
		पूर्ण
	पूर्ण
	ivtv_setscl(itv, 0);
	अगर (!ivtv_रुकोscl(itv, 0)) अणु
		IVTV_DEBUG_I2C("Error setting SCL low\n");
		वापस -EREMOTEIO;
	पूर्ण
	वापस ivtv_ack(itv);
पूर्ण

/* Read a byte from the i2c bus and send a NACK अगर applicable (i.e. क्रम the
   final byte) */
अटल पूर्णांक ivtv_पढ़ोbyte(काष्ठा ivtv *itv, अचिन्हित अक्षर *byte, पूर्णांक nack)
अणु
	पूर्णांक i;

	*byte = 0;

	ivtv_setsda(itv, 1);
	ivtv_scldelay(itv);
	क्रम (i = 0; i < 8; ++i) अणु
		ivtv_setscl(itv, 0);
		ivtv_scldelay(itv);
		ivtv_setscl(itv, 1);
		अगर (!ivtv_रुकोscl(itv, 1)) अणु
			IVTV_DEBUG_I2C("Error setting SCL high\n");
			वापस -EREMOTEIO;
		पूर्ण
		*byte = ((*byte)<<1)|ivtv_माला_लोda(itv);
	पूर्ण
	ivtv_setscl(itv, 0);
	ivtv_scldelay(itv);
	ivtv_setsda(itv, nack);
	ivtv_scldelay(itv);
	ivtv_setscl(itv, 1);
	ivtv_scldelay(itv);
	ivtv_setscl(itv, 0);
	ivtv_scldelay(itv);
	IVTV_DEBUG_HI_I2C("read %x\n",*byte);
	वापस 0;
पूर्ण

/* Issue a start condition on the i2c bus to alert slaves to prepare क्रम
   an address ग_लिखो */
अटल पूर्णांक ivtv_start(काष्ठा ivtv *itv)
अणु
	पूर्णांक sda;

	sda = ivtv_माला_लोda(itv);
	अगर (sda != 1) अणु
		IVTV_DEBUG_HI_I2C("SDA was low at start\n");
		ivtv_setsda(itv, 1);
		अगर (!ivtv_रुकोsda(itv, 1)) अणु
			IVTV_DEBUG_I2C("SDA stuck low\n");
			वापस -EREMOTEIO;
		पूर्ण
	पूर्ण
	अगर (ivtv_माला_लोcl(itv) != 1) अणु
		ivtv_setscl(itv, 1);
		अगर (!ivtv_रुकोscl(itv, 1)) अणु
			IVTV_DEBUG_I2C("SCL stuck low at start\n");
			वापस -EREMOTEIO;
		पूर्ण
	पूर्ण
	ivtv_setsda(itv, 0);
	ivtv_scldelay(itv);
	वापस 0;
पूर्ण

/* Issue a stop condition on the i2c bus to release it */
अटल पूर्णांक ivtv_stop(काष्ठा ivtv *itv)
अणु
	पूर्णांक i;

	अगर (ivtv_माला_लोcl(itv) != 0) अणु
		IVTV_DEBUG_HI_I2C("SCL not low when stopping\n");
		ivtv_setscl(itv, 0);
		अगर (!ivtv_रुकोscl(itv, 0)) अणु
			IVTV_DEBUG_I2C("SCL could not be set low\n");
		पूर्ण
	पूर्ण
	ivtv_setsda(itv, 0);
	ivtv_scldelay(itv);
	ivtv_setscl(itv, 1);
	अगर (!ivtv_रुकोscl(itv, 1)) अणु
		IVTV_DEBUG_I2C("SCL could not be set high\n");
		वापस -EREMOTEIO;
	पूर्ण
	ivtv_scldelay(itv);
	ivtv_setsda(itv, 1);
	अगर (!ivtv_रुकोsda(itv, 1)) अणु
		IVTV_DEBUG_I2C("resetting I2C\n");
		क्रम (i = 0; i < 16; ++i) अणु
			ivtv_setscl(itv, 0);
			ivtv_scldelay(itv);
			ivtv_setscl(itv, 1);
			ivtv_scldelay(itv);
			ivtv_setsda(itv, 1);
		पूर्ण
		ivtv_रुकोsda(itv, 1);
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

/* Write a message to the given i2c slave.  करो_stop may be 0 to prevent
   issuing the i2c stop condition (when following with a पढ़ो) */
अटल पूर्णांक ivtv_ग_लिखो(काष्ठा ivtv *itv, अचिन्हित अक्षर addr, अचिन्हित अक्षर *data, u32 len, पूर्णांक करो_stop)
अणु
	पूर्णांक retry, ret = -EREMOTEIO;
	u32 i;

	क्रम (retry = 0; ret != 0 && retry < 8; ++retry) अणु
		ret = ivtv_start(itv);

		अगर (ret == 0) अणु
			ret = ivtv_sendbyte(itv, addr<<1);
			क्रम (i = 0; ret == 0 && i < len; ++i)
				ret = ivtv_sendbyte(itv, data[i]);
		पूर्ण
		अगर (ret != 0 || करो_stop) अणु
			ivtv_stop(itv);
		पूर्ण
	पूर्ण
	अगर (ret)
		IVTV_DEBUG_I2C("i2c write to %x failed\n", addr);
	वापस ret;
पूर्ण

/* Read data from the given i2c slave.  A stop condition is always issued. */
अटल पूर्णांक ivtv_पढ़ो(काष्ठा ivtv *itv, अचिन्हित अक्षर addr, अचिन्हित अक्षर *data, u32 len)
अणु
	पूर्णांक retry, ret = -EREMOTEIO;
	u32 i;

	क्रम (retry = 0; ret != 0 && retry < 8; ++retry) अणु
		ret = ivtv_start(itv);
		अगर (ret == 0)
			ret = ivtv_sendbyte(itv, (addr << 1) | 1);
		क्रम (i = 0; ret == 0 && i < len; ++i) अणु
			ret = ivtv_पढ़ोbyte(itv, &data[i], i == len - 1);
		पूर्ण
		ivtv_stop(itv);
	पूर्ण
	अगर (ret)
		IVTV_DEBUG_I2C("i2c read from %x failed\n", addr);
	वापस ret;
पूर्ण

/* Kernel i2c transfer implementation.  Takes a number of messages to be पढ़ो
   or written.  If a पढ़ो follows a ग_लिखो, this will occur without an
   पूर्णांकervening stop condition */
अटल पूर्णांक ivtv_xfer(काष्ठा i2c_adapter *i2c_adap, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा v4l2_device *v4l2_dev = i2c_get_adapdata(i2c_adap);
	काष्ठा ivtv *itv = to_ivtv(v4l2_dev);
	पूर्णांक retval;
	पूर्णांक i;

	mutex_lock(&itv->i2c_bus_lock);
	क्रम (i = retval = 0; retval == 0 && i < num; i++) अणु
		अगर (msgs[i].flags & I2C_M_RD)
			retval = ivtv_पढ़ो(itv, msgs[i].addr, msgs[i].buf, msgs[i].len);
		अन्यथा अणु
			/* अगर followed by a पढ़ो, करोn't stop */
			पूर्णांक stop = !(i + 1 < num && msgs[i + 1].flags == I2C_M_RD);

			retval = ivtv_ग_लिखो(itv, msgs[i].addr, msgs[i].buf, msgs[i].len, stop);
		पूर्ण
	पूर्ण
	mutex_unlock(&itv->i2c_bus_lock);
	वापस retval ? retval : num;
पूर्ण

/* Kernel i2c capabilities */
अटल u32 ivtv_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm ivtv_algo = अणु
	.master_xfer   = ivtv_xfer,
	.functionality = ivtv_functionality,
पूर्ण;

/* ढाँचा क्रम our-bit banger */
अटल स्थिर काष्ठा i2c_adapter ivtv_i2c_adap_hw_ढाँचा = अणु
	.name = "ivtv i2c driver",
	.algo = &ivtv_algo,
	.algo_data = शून्य,			/* filled from ढाँचा */
	.owner = THIS_MODULE,
पूर्ण;

अटल व्योम ivtv_setscl_old(व्योम *data, पूर्णांक state)
अणु
	काष्ठा ivtv *itv = (काष्ठा ivtv *)data;

	अगर (state)
		itv->i2c_state |= 0x01;
	अन्यथा
		itv->i2c_state &= ~0x01;

	/* ग_लिखो them out */
	/* ग_लिखो bits are inverted */
	ग_लिखो_reg(~itv->i2c_state, IVTV_REG_I2C_SETSCL_OFFSET);
पूर्ण

अटल व्योम ivtv_setsda_old(व्योम *data, पूर्णांक state)
अणु
	काष्ठा ivtv *itv = (काष्ठा ivtv *)data;

	अगर (state)
		itv->i2c_state |= 0x01;
	अन्यथा
		itv->i2c_state &= ~0x01;

	/* ग_लिखो them out */
	/* ग_लिखो bits are inverted */
	ग_लिखो_reg(~itv->i2c_state, IVTV_REG_I2C_SETSDA_OFFSET);
पूर्ण

अटल पूर्णांक ivtv_माला_लोcl_old(व्योम *data)
अणु
	काष्ठा ivtv *itv = (काष्ठा ivtv *)data;

	वापस पढ़ो_reg(IVTV_REG_I2C_GETSCL_OFFSET) & 1;
पूर्ण

अटल पूर्णांक ivtv_माला_लोda_old(व्योम *data)
अणु
	काष्ठा ivtv *itv = (काष्ठा ivtv *)data;

	वापस पढ़ो_reg(IVTV_REG_I2C_GETSDA_OFFSET) & 1;
पूर्ण

/* ढाँचा क्रम i2c-bit-algo */
अटल स्थिर काष्ठा i2c_adapter ivtv_i2c_adap_ढाँचा = अणु
	.name = "ivtv i2c driver",
	.algo = शून्य,                   /* set by i2c-algo-bit */
	.algo_data = शून्य,              /* filled from ढाँचा */
	.owner = THIS_MODULE,
पूर्ण;

#घोषणा IVTV_ALGO_BIT_TIMEOUT	(2)	/* seconds */

अटल स्थिर काष्ठा i2c_algo_bit_data ivtv_i2c_algo_ढाँचा = अणु
	.setsda		= ivtv_setsda_old,
	.setscl		= ivtv_setscl_old,
	.माला_लोda		= ivtv_माला_लोda_old,
	.माला_लोcl		= ivtv_माला_लोcl_old,
	.udelay		= IVTV_DEFAULT_I2C_CLOCK_PERIOD / 2,  /* microseconds */
	.समयout	= IVTV_ALGO_BIT_TIMEOUT * HZ,         /* jअगरfies */
पूर्ण;

अटल स्थिर काष्ठा i2c_client ivtv_i2c_client_ढाँचा = अणु
	.name = "ivtv internal",
पूर्ण;

/* init + रेजिस्टर i2c adapter */
पूर्णांक init_ivtv_i2c(काष्ठा ivtv *itv)
अणु
	पूर्णांक retval;

	IVTV_DEBUG_I2C("i2c init\n");

	/* Sanity checks क्रम the I2C hardware arrays. They must be the
	 * same size.
	 */
	अगर (ARRAY_SIZE(hw_devicenames) != ARRAY_SIZE(hw_addrs)) अणु
		IVTV_ERR("Mismatched I2C hardware arrays\n");
		वापस -ENODEV;
	पूर्ण
	अगर (itv->options.newi2c > 0) अणु
		itv->i2c_adap = ivtv_i2c_adap_hw_ढाँचा;
	पूर्ण अन्यथा अणु
		itv->i2c_adap = ivtv_i2c_adap_ढाँचा;
		itv->i2c_algo = ivtv_i2c_algo_ढाँचा;
	पूर्ण
	itv->i2c_algo.udelay = itv->options.i2c_घड़ी_period / 2;
	itv->i2c_algo.data = itv;
	itv->i2c_adap.algo_data = &itv->i2c_algo;

	प्र_लिखो(itv->i2c_adap.name + म_माप(itv->i2c_adap.name), " #%d",
		itv->instance);
	i2c_set_adapdata(&itv->i2c_adap, &itv->v4l2_dev);

	itv->i2c_client = ivtv_i2c_client_ढाँचा;
	itv->i2c_client.adapter = &itv->i2c_adap;
	itv->i2c_adap.dev.parent = &itv->pdev->dev;

	IVTV_DEBUG_I2C("setting scl and sda to 1\n");
	ivtv_setscl(itv, 1);
	ivtv_setsda(itv, 1);

	अगर (itv->options.newi2c > 0)
		retval = i2c_add_adapter(&itv->i2c_adap);
	अन्यथा
		retval = i2c_bit_add_bus(&itv->i2c_adap);

	वापस retval;
पूर्ण

व्योम निकास_ivtv_i2c(काष्ठा ivtv *itv)
अणु
	IVTV_DEBUG_I2C("i2c exit\n");

	i2c_del_adapter(&itv->i2c_adap);
पूर्ण
