<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * saa7706.c Philips SAA7706H Car Radio DSP driver
 * Copyright (c) 2009 Intel Corporation
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>

#घोषणा DRIVER_NAME "saa7706h"

/* the I2C memory map looks like this

	$1C00 - $FFFF Not Used
	$2200 - $3FFF Reserved YRAM (DSP2) space
	$2000 - $21FF YRAM (DSP2)
	$1FF0 - $1FFF Hardware Registers
	$1280 - $1FEF Reserved XRAM (DSP2) space
	$1000 - $127F XRAM (DSP2)
	$0FFF        DSP CONTROL
	$0A00 - $0FFE Reserved
	$0980 - $09FF Reserved YRAM (DSP1) space
	$0800 - $097F YRAM (DSP1)
	$0200 - $07FF Not Used
	$0180 - $01FF Reserved XRAM (DSP1) space
	$0000 - $017F XRAM (DSP1)
*/

#घोषणा SAA7706H_REG_CTRL		0x0fff
#घोषणा SAA7706H_CTRL_BYP_PLL		0x0001
#घोषणा SAA7706H_CTRL_PLL_DIV_MASK	0x003e
#घोषणा SAA7706H_CTRL_PLL3_62975MHZ	0x003e
#घोषणा SAA7706H_CTRL_DSP_TURBO		0x0040
#घोषणा SAA7706H_CTRL_PC_RESET_DSP1	0x0080
#घोषणा SAA7706H_CTRL_PC_RESET_DSP2	0x0100
#घोषणा SAA7706H_CTRL_DSP1_ROM_EN_MASK	0x0600
#घोषणा SAA7706H_CTRL_DSP1_FUNC_PROM	0x0000
#घोषणा SAA7706H_CTRL_DSP2_ROM_EN_MASK	0x1800
#घोषणा SAA7706H_CTRL_DSP2_FUNC_PROM	0x0000
#घोषणा SAA7706H_CTRL_DIG_SIL_INTERPOL	0x8000

#घोषणा SAA7706H_REG_EVALUATION			0x1ff0
#घोषणा SAA7706H_EVAL_DISABLE_CHARGE_PUMP	0x000001
#घोषणा SAA7706H_EVAL_DCS_CLOCK			0x000002
#घोषणा SAA7706H_EVAL_GNDRC1_ENABLE		0x000004
#घोषणा SAA7706H_EVAL_GNDRC2_ENABLE		0x000008

#घोषणा SAA7706H_REG_CL_GEN1			0x1ff3
#घोषणा SAA7706H_CL_GEN1_MIN_LOOPGAIN_MASK	0x00000f
#घोषणा SAA7706H_CL_GEN1_LOOPGAIN_MASK		0x0000f0
#घोषणा SAA7706H_CL_GEN1_COARSE_RATION		0xffff00

#घोषणा SAA7706H_REG_CL_GEN2			0x1ff4
#घोषणा SAA7706H_CL_GEN2_WSEDGE_FALLING		0x000001
#घोषणा SAA7706H_CL_GEN2_STOP_VCO		0x000002
#घोषणा SAA7706H_CL_GEN2_FRERUN			0x000004
#घोषणा SAA7706H_CL_GEN2_ADAPTIVE		0x000008
#घोषणा SAA7706H_CL_GEN2_FINE_RATIO_MASK	0x0ffff0

#घोषणा SAA7706H_REG_CL_GEN4		0x1ff6
#घोषणा SAA7706H_CL_GEN4_BYPASS_PLL1	0x001000
#घोषणा SAA7706H_CL_GEN4_PLL1_DIV_MASK	0x03e000
#घोषणा SAA7706H_CL_GEN4_DSP1_TURBO	0x040000

#घोषणा SAA7706H_REG_SEL	0x1ff7
#घोषणा SAA7706H_SEL_DSP2_SRCA_MASK	0x000007
#घोषणा SAA7706H_SEL_DSP2_FMTA_MASK	0x000031
#घोषणा SAA7706H_SEL_DSP2_SRCB_MASK	0x0001c0
#घोषणा SAA7706H_SEL_DSP2_FMTB_MASK	0x000e00
#घोषणा SAA7706H_SEL_DSP1_SRC_MASK	0x003000
#घोषणा SAA7706H_SEL_DSP1_FMT_MASK	0x01c003
#घोषणा SAA7706H_SEL_SPDIF2		0x020000
#घोषणा SAA7706H_SEL_HOST_IO_FMT_MASK	0x1c0000
#घोषणा SAA7706H_SEL_EN_HOST_IO		0x200000

#घोषणा SAA7706H_REG_IAC		0x1ff8
#घोषणा SAA7706H_REG_CLK_SET		0x1ff9
#घोषणा SAA7706H_REG_CLK_COEFF		0x1ffa
#घोषणा SAA7706H_REG_INPUT_SENS		0x1ffb
#घोषणा SAA7706H_INPUT_SENS_RDS_VOL_MASK	0x0003f
#घोषणा SAA7706H_INPUT_SENS_FM_VOL_MASK		0x00fc0
#घोषणा SAA7706H_INPUT_SENS_FM_MPX		0x01000
#घोषणा SAA7706H_INPUT_SENS_OFF_FILTER_A_EN	0x02000
#घोषणा SAA7706H_INPUT_SENS_OFF_FILTER_B_EN	0x04000
#घोषणा SAA7706H_REG_PHONE_NAV_AUDIO	0x1ffc
#घोषणा SAA7706H_REG_IO_CONF_DSP2	0x1ffd
#घोषणा SAA7706H_REG_STATUS_DSP2	0x1ffe
#घोषणा SAA7706H_REG_PC_DSP2		0x1fff

#घोषणा SAA7706H_DSP1_MOD0	0x0800
#घोषणा SAA7706H_DSP1_ROM_VER	0x097f
#घोषणा SAA7706H_DSP2_MPTR0	0x1000

#घोषणा SAA7706H_DSP1_MODPNTR	0x0000

#घोषणा SAA7706H_DSP2_XMEM_CONTLLCW	0x113e
#घोषणा SAA7706H_DSP2_XMEM_BUSAMP	0x114a
#घोषणा SAA7706H_DSP2_XMEM_FDACPNTR	0x11f9
#घोषणा SAA7706H_DSP2_XMEM_IIS1PNTR	0x11fb

#घोषणा SAA7706H_DSP2_YMEM_PVGA		0x212a
#घोषणा SAA7706H_DSP2_YMEM_PVAT1	0x212b
#घोषणा SAA7706H_DSP2_YMEM_PVAT		0x212c
#घोषणा SAA7706H_DSP2_YMEM_ROM_VER	0x21ff

#घोषणा SUPPORTED_DSP1_ROM_VER		0x667

काष्ठा saa7706h_state अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl_handler hdl;
	अचिन्हित muted;
पूर्ण;

अटल अंतरभूत काष्ठा saa7706h_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा saa7706h_state, sd);
पूर्ण

अटल पूर्णांक saa7706h_i2c_send(काष्ठा i2c_client *client, स्थिर u8 *data, पूर्णांक len)
अणु
	पूर्णांक err = i2c_master_send(client, data, len);
	अगर (err == len)
		वापस 0;
	वापस err > 0 ? -EIO : err;
पूर्ण

अटल पूर्णांक saa7706h_i2c_transfer(काष्ठा i2c_client *client,
	काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	पूर्णांक err = i2c_transfer(client->adapter, msgs, num);
	अगर (err == num)
		वापस 0;
	वापस err > 0 ? -EIO : err;
पूर्ण

अटल पूर्णांक saa7706h_set_reg24(काष्ठा v4l2_subdev *sd, u16 reg, u32 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u8 buf[5];
	पूर्णांक pos = 0;

	buf[pos++] = reg >> 8;
	buf[pos++] = reg;
	buf[pos++] = val >> 16;
	buf[pos++] = val >> 8;
	buf[pos++] = val;

	वापस saa7706h_i2c_send(client, buf, pos);
पूर्ण

अटल पूर्णांक saa7706h_set_reg24_err(काष्ठा v4l2_subdev *sd, u16 reg, u32 val,
	पूर्णांक *err)
अणु
	वापस *err ? *err : saa7706h_set_reg24(sd, reg, val);
पूर्ण

अटल पूर्णांक saa7706h_set_reg16(काष्ठा v4l2_subdev *sd, u16 reg, u16 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u8 buf[4];
	पूर्णांक pos = 0;

	buf[pos++] = reg >> 8;
	buf[pos++] = reg;
	buf[pos++] = val >> 8;
	buf[pos++] = val;

	वापस saa7706h_i2c_send(client, buf, pos);
पूर्ण

अटल पूर्णांक saa7706h_set_reg16_err(काष्ठा v4l2_subdev *sd, u16 reg, u16 val,
	पूर्णांक *err)
अणु
	वापस *err ? *err : saa7706h_set_reg16(sd, reg, val);
पूर्ण

अटल पूर्णांक saa7706h_get_reg16(काष्ठा v4l2_subdev *sd, u16 reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u8 buf[2];
	पूर्णांक err;
	u8 regaddr[] = अणुreg >> 8, regपूर्ण;
	काष्ठा i2c_msg msg[] = अणु
					अणु
						.addr = client->addr,
						.len = माप(regaddr),
						.buf = regaddr
					पूर्ण,
					अणु
						.addr = client->addr,
						.flags = I2C_M_RD,
						.len = माप(buf),
						.buf = buf
					पूर्ण
				पूर्ण;

	err = saa7706h_i2c_transfer(client, msg, ARRAY_SIZE(msg));
	अगर (err)
		वापस err;

	वापस buf[0] << 8 | buf[1];
पूर्ण

अटल पूर्णांक saa7706h_unmute(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा saa7706h_state *state = to_state(sd);
	पूर्णांक err = 0;

	err = saa7706h_set_reg16_err(sd, SAA7706H_REG_CTRL,
		SAA7706H_CTRL_PLL3_62975MHZ | SAA7706H_CTRL_PC_RESET_DSP1 |
		SAA7706H_CTRL_PC_RESET_DSP2, &err);

	/* newer versions of the chip requires a small sleep after reset */
	msleep(1);

	err = saa7706h_set_reg16_err(sd, SAA7706H_REG_CTRL,
		SAA7706H_CTRL_PLL3_62975MHZ, &err);

	err = saa7706h_set_reg24_err(sd, SAA7706H_REG_EVALUATION, 0, &err);

	err = saa7706h_set_reg24_err(sd, SAA7706H_REG_CL_GEN1, 0x040022, &err);

	err = saa7706h_set_reg24_err(sd, SAA7706H_REG_CL_GEN2,
		SAA7706H_CL_GEN2_WSEDGE_FALLING, &err);

	err = saa7706h_set_reg24_err(sd, SAA7706H_REG_CL_GEN4, 0x024080, &err);

	err = saa7706h_set_reg24_err(sd, SAA7706H_REG_SEL, 0x200080, &err);

	err = saa7706h_set_reg24_err(sd, SAA7706H_REG_IAC, 0xf4caed, &err);

	err = saa7706h_set_reg24_err(sd, SAA7706H_REG_CLK_SET, 0x124334, &err);

	err = saa7706h_set_reg24_err(sd, SAA7706H_REG_CLK_COEFF, 0x004a1a,
		&err);

	err = saa7706h_set_reg24_err(sd, SAA7706H_REG_INPUT_SENS, 0x0071c7,
		&err);

	err = saa7706h_set_reg24_err(sd, SAA7706H_REG_PHONE_NAV_AUDIO,
		0x0e22ff, &err);

	err = saa7706h_set_reg24_err(sd, SAA7706H_REG_IO_CONF_DSP2, 0x001ff8,
		&err);

	err = saa7706h_set_reg24_err(sd, SAA7706H_REG_STATUS_DSP2, 0x080003,
		&err);

	err = saa7706h_set_reg24_err(sd, SAA7706H_REG_PC_DSP2, 0x000004, &err);

	err = saa7706h_set_reg16_err(sd, SAA7706H_DSP1_MOD0, 0x0c6c, &err);

	err = saa7706h_set_reg24_err(sd, SAA7706H_DSP2_MPTR0, 0x000b4b, &err);

	err = saa7706h_set_reg24_err(sd, SAA7706H_DSP1_MODPNTR, 0x000600, &err);

	err = saa7706h_set_reg24_err(sd, SAA7706H_DSP1_MODPNTR, 0x0000c0, &err);

	err = saa7706h_set_reg24_err(sd, SAA7706H_DSP2_XMEM_CONTLLCW, 0x000819,
		&err);

	err = saa7706h_set_reg24_err(sd, SAA7706H_DSP2_XMEM_CONTLLCW, 0x00085a,
		&err);

	err = saa7706h_set_reg24_err(sd, SAA7706H_DSP2_XMEM_BUSAMP, 0x7fffff,
		&err);

	err = saa7706h_set_reg24_err(sd, SAA7706H_DSP2_XMEM_FDACPNTR, 0x2000cb,
		&err);

	err = saa7706h_set_reg24_err(sd, SAA7706H_DSP2_XMEM_IIS1PNTR, 0x2000cb,
		&err);

	err = saa7706h_set_reg16_err(sd, SAA7706H_DSP2_YMEM_PVGA, 0x0f80, &err);

	err = saa7706h_set_reg16_err(sd, SAA7706H_DSP2_YMEM_PVAT1, 0x0800,
		&err);

	err = saa7706h_set_reg16_err(sd, SAA7706H_DSP2_YMEM_PVAT, 0x0800, &err);

	err = saa7706h_set_reg24_err(sd, SAA7706H_DSP2_XMEM_CONTLLCW, 0x000905,
		&err);
	अगर (!err)
		state->muted = 0;
	वापस err;
पूर्ण

अटल पूर्णांक saa7706h_mute(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा saa7706h_state *state = to_state(sd);
	पूर्णांक err;

	err = saa7706h_set_reg16(sd, SAA7706H_REG_CTRL,
		SAA7706H_CTRL_PLL3_62975MHZ | SAA7706H_CTRL_PC_RESET_DSP1 |
		SAA7706H_CTRL_PC_RESET_DSP2);
	अगर (!err)
		state->muted = 1;
	वापस err;
पूर्ण

अटल पूर्णांक saa7706h_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा saa7706h_state *state =
		container_of(ctrl->handler, काष्ठा saa7706h_state, hdl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_MUTE:
		अगर (ctrl->val)
			वापस saa7706h_mute(&state->sd);
		वापस saa7706h_unmute(&state->sd);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops saa7706h_ctrl_ops = अणु
	.s_ctrl = saa7706h_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops empty_ops = अणुपूर्ण;

/*
 * Generic i2c probe
 * concerning the addresses: i2c wants 7 bit (without the r/w bit), so '>>1'
 */

अटल पूर्णांक saa7706h_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा saa7706h_state *state;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक err;

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	v4l_info(client, "chip found @ 0x%02x (%s)\n",
			client->addr << 1, client->adapter->name);

	state = kzalloc(माप(काष्ठा saa7706h_state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस -ENOMEM;
	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &empty_ops);

	v4l2_ctrl_handler_init(&state->hdl, 4);
	v4l2_ctrl_new_std(&state->hdl, &saa7706h_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	sd->ctrl_handler = &state->hdl;
	err = state->hdl.error;
	अगर (err)
		जाओ err;

	/* check the rom versions */
	err = saa7706h_get_reg16(sd, SAA7706H_DSP1_ROM_VER);
	अगर (err < 0)
		जाओ err;
	अगर (err != SUPPORTED_DSP1_ROM_VER)
		v4l2_warn(sd, "Unknown DSP1 ROM code version: 0x%x\n", err);
	state->muted = 1;

	/* startup in a muted state */
	err = saa7706h_mute(sd);
	अगर (err)
		जाओ err;

	वापस 0;

err:
	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(&state->hdl);
	kमुक्त(to_state(sd));

	prपूर्णांकk(KERN_ERR DRIVER_NAME ": Failed to probe: %d\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक saa7706h_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा saa7706h_state *state = to_state(sd);

	saa7706h_mute(sd);
	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(&state->hdl);
	kमुक्त(to_state(sd));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id saa7706h_id[] = अणु
	अणुDRIVER_NAME, 0पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, saa7706h_id);

अटल काष्ठा i2c_driver saa7706h_driver = अणु
	.driver = अणु
		.name	= DRIVER_NAME,
	पूर्ण,
	.probe		= saa7706h_probe,
	.हटाओ		= saa7706h_हटाओ,
	.id_table	= saa7706h_id,
पूर्ण;

module_i2c_driver(saa7706h_driver);

MODULE_DESCRIPTION("SAA7706H Car Radio DSP driver");
MODULE_AUTHOR("Mocean Laboratories");
MODULE_LICENSE("GPL v2");
