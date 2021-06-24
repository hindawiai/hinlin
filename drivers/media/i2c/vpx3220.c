<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * vpx3220a, vpx3216b & vpx3214c video decoder driver version 0.0.1
 *
 * Copyright (C) 2001 Laurent Pinअक्षरt <lpinअक्षरt@मुक्तgates.be>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>

MODULE_DESCRIPTION("vpx3220a/vpx3216b/vpx3214c video decoder driver");
MODULE_AUTHOR("Laurent Pinchart");
MODULE_LICENSE("GPL");

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0-1)");


#घोषणा VPX_TIMEOUT_COUNT  10

/* ----------------------------------------------------------------------- */

काष्ठा vpx3220 अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl_handler hdl;
	अचिन्हित अक्षर reg[255];

	v4l2_std_id norm;
	पूर्णांक input;
	पूर्णांक enable;
पूर्ण;

अटल अंतरभूत काष्ठा vpx3220 *to_vpx3220(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा vpx3220, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा vpx3220, hdl)->sd;
पूर्ण

अटल अक्षर *inमाला_दो[] = अणु "internal", "composite", "svideo" पूर्ण;

/* ----------------------------------------------------------------------- */

अटल अंतरभूत पूर्णांक vpx3220_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा vpx3220 *decoder = i2c_get_clientdata(client);

	decoder->reg[reg] = value;
	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

अटल अंतरभूत पूर्णांक vpx3220_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल पूर्णांक vpx3220_fp_status(काष्ठा v4l2_subdev *sd)
अणु
	अचिन्हित अक्षर status;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < VPX_TIMEOUT_COUNT; i++) अणु
		status = vpx3220_पढ़ो(sd, 0x29);

		अगर (!(status & 4))
			वापस 0;

		udelay(10);

		अगर (need_resched())
			cond_resched();
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक vpx3220_fp_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 fpaddr, u16 data)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	/* Write the 16-bit address to the FPWR रेजिस्टर */
	अगर (i2c_smbus_ग_लिखो_word_data(client, 0x27, swab16(fpaddr)) == -1) अणु
		v4l2_dbg(1, debug, sd, "%s: failed\n", __func__);
		वापस -1;
	पूर्ण

	अगर (vpx3220_fp_status(sd) < 0)
		वापस -1;

	/* Write the 16-bit data to the FPDAT रेजिस्टर */
	अगर (i2c_smbus_ग_लिखो_word_data(client, 0x28, swab16(data)) == -1) अणु
		v4l2_dbg(1, debug, sd, "%s: failed\n", __func__);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vpx3220_fp_पढ़ो(काष्ठा v4l2_subdev *sd, u16 fpaddr)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	s16 data;

	/* Write the 16-bit address to the FPRD रेजिस्टर */
	अगर (i2c_smbus_ग_लिखो_word_data(client, 0x26, swab16(fpaddr)) == -1) अणु
		v4l2_dbg(1, debug, sd, "%s: failed\n", __func__);
		वापस -1;
	पूर्ण

	अगर (vpx3220_fp_status(sd) < 0)
		वापस -1;

	/* Read the 16-bit data from the FPDAT रेजिस्टर */
	data = i2c_smbus_पढ़ो_word_data(client, 0x28);
	अगर (data == -1) अणु
		v4l2_dbg(1, debug, sd, "%s: failed\n", __func__);
		वापस -1;
	पूर्ण

	वापस swab16(data);
पूर्ण

अटल पूर्णांक vpx3220_ग_लिखो_block(काष्ठा v4l2_subdev *sd, स्थिर u8 *data, अचिन्हित पूर्णांक len)
अणु
	u8 reg;
	पूर्णांक ret = -1;

	जबतक (len >= 2) अणु
		reg = *data++;
		ret = vpx3220_ग_लिखो(sd, reg, *data++);
		अगर (ret < 0)
			अवरोध;
		len -= 2;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vpx3220_ग_लिखो_fp_block(काष्ठा v4l2_subdev *sd,
		स्थिर u16 *data, अचिन्हित पूर्णांक len)
अणु
	u8 reg;
	पूर्णांक ret = 0;

	जबतक (len > 1) अणु
		reg = *data++;
		ret |= vpx3220_fp_ग_लिखो(sd, reg, *data++);
		len -= 2;
	पूर्ण

	वापस ret;
पूर्ण

/* ---------------------------------------------------------------------- */

अटल स्थिर अचिन्हित लघु init_ntsc[] = अणु
	0x1c, 0x00,		/* NTSC tपूर्णांक angle */
	0x88, 17,		/* Winकरोw 1 vertical */
	0x89, 240,		/* Vertical lines in */
	0x8a, 240,		/* Vertical lines out */
	0x8b, 000,		/* Horizontal begin */
	0x8c, 640,		/* Horizontal length */
	0x8d, 640,		/* Number of pixels */
	0x8f, 0xc00,		/* Disable winकरोw 2 */
	0xf0, 0x73,		/* 13.5 MHz transport, Forced
				 * mode, latch winकरोws */
	0xf2, 0x13,		/* NTSC M, composite input */
	0xe7, 0x1e1,		/* Enable vertical standard
				 * locking @ 240 lines */
पूर्ण;

अटल स्थिर अचिन्हित लघु init_pal[] = अणु
	0x88, 23,		/* Winकरोw 1 vertical begin */
	0x89, 288,		/* Vertical lines in (16 lines
				 * skipped by the VFE) */
	0x8a, 288,		/* Vertical lines out (16 lines
				 * skipped by the VFE) */
	0x8b, 16,		/* Horizontal begin */
	0x8c, 768,		/* Horizontal length */
	0x8d, 784,		/* Number of pixels
				 * Must be >= Horizontal begin + Horizontal length */
	0x8f, 0xc00,		/* Disable winकरोw 2 */
	0xf0, 0x77,		/* 13.5 MHz transport, Forced
				 * mode, latch winकरोws */
	0xf2, 0x3d1,		/* PAL B,G,H,I, composite input */
	0xe7, 0x241,		/* PAL/SECAM set to 288 lines */
पूर्ण;

अटल स्थिर अचिन्हित लघु init_secam[] = अणु
	0x88, 23,		/* Winकरोw 1 vertical begin */
	0x89, 288,		/* Vertical lines in (16 lines
				 * skipped by the VFE) */
	0x8a, 288,		/* Vertical lines out (16 lines
				 * skipped by the VFE) */
	0x8b, 16,		/* Horizontal begin */
	0x8c, 768,		/* Horizontal length */
	0x8d, 784,		/* Number of pixels
				 * Must be >= Horizontal begin + Horizontal length */
	0x8f, 0xc00,		/* Disable winकरोw 2 */
	0xf0, 0x77,		/* 13.5 MHz transport, Forced
				 * mode, latch winकरोws */
	0xf2, 0x3d5,		/* SECAM, composite input */
	0xe7, 0x241,		/* PAL/SECAM set to 288 lines */
पूर्ण;

अटल स्थिर अचिन्हित अक्षर init_common[] = अणु
	0xf2, 0x00,		/* Disable all outमाला_दो */
	0x33, 0x0d,		/* Luma : VIN2, Chroma : CIN
				 * (clamp off) */
	0xd8, 0xa8,		/* HREF/VREF active high, VREF
				 * pulse = 2, Odd/Even flag */
	0x20, 0x03,		/* IF compensation 0dB/oct */
	0xe0, 0xff,		/* Open up all comparators */
	0xe1, 0x00,
	0xe2, 0x7f,
	0xe3, 0x80,
	0xe4, 0x7f,
	0xe5, 0x80,
	0xe6, 0x00,		/* Brightness set to 0 */
	0xe7, 0xe0,		/* Contrast to 1.0, noise shaping
				 * 10 to 8 2-bit error dअगरfusion */
	0xe8, 0xf8,		/* YUV422, CbCr binary offset,
				 * ... (p.32) */
	0xea, 0x18,		/* LLC2 connected, output FIFO
				 * reset with VACTपूर्णांकern */
	0xf0, 0x8a,		/* Half full level to 10, bus
				 * shuffler [7:0, 23:16, 15:8] */
	0xf1, 0x18,		/* Single घड़ी, sync mode, no
				 * FE delay, no HLEN counter */
	0xf8, 0x12,		/* Port A, PIXCLK, HF# & FE#
				 * strength to 2 */
	0xf9, 0x24,		/* Port B, HREF, VREF, PREF &
				 * ALPHA strength to 4 */
पूर्ण;

अटल स्थिर अचिन्हित लघु init_fp[] = अणु
	0x59, 0,
	0xa0, 2070,		/* ACC reference */
	0xa3, 0,
	0xa4, 0,
	0xa8, 30,
	0xb2, 768,
	0xbe, 27,
	0x58, 0,
	0x26, 0,
	0x4b, 0x298,		/* PLL gain */
पूर्ण;


अटल पूर्णांक vpx3220_init(काष्ठा v4l2_subdev *sd, u32 val)
अणु
	काष्ठा vpx3220 *decoder = to_vpx3220(sd);

	vpx3220_ग_लिखो_block(sd, init_common, माप(init_common));
	vpx3220_ग_लिखो_fp_block(sd, init_fp, माप(init_fp) >> 1);
	अगर (decoder->norm & V4L2_STD_NTSC)
		vpx3220_ग_लिखो_fp_block(sd, init_ntsc, माप(init_ntsc) >> 1);
	अन्यथा अगर (decoder->norm & V4L2_STD_PAL)
		vpx3220_ग_लिखो_fp_block(sd, init_pal, माप(init_pal) >> 1);
	अन्यथा अगर (decoder->norm & V4L2_STD_SECAM)
		vpx3220_ग_लिखो_fp_block(sd, init_secam, माप(init_secam) >> 1);
	अन्यथा
		vpx3220_ग_लिखो_fp_block(sd, init_pal, माप(init_pal) >> 1);
	वापस 0;
पूर्ण

अटल पूर्णांक vpx3220_status(काष्ठा v4l2_subdev *sd, u32 *pstatus, v4l2_std_id *pstd)
अणु
	पूर्णांक res = V4L2_IN_ST_NO_SIGNAL, status;
	v4l2_std_id std = pstd ? *pstd : V4L2_STD_ALL;

	status = vpx3220_fp_पढ़ो(sd, 0x0f3);

	v4l2_dbg(1, debug, sd, "status: 0x%04x\n", status);

	अगर (status < 0)
		वापस status;

	अगर ((status & 0x20) == 0) अणु
		res = 0;

		चयन (status & 0x18) अणु
		हाल 0x00:
		हाल 0x10:
		हाल 0x14:
		हाल 0x18:
			std &= V4L2_STD_PAL;
			अवरोध;

		हाल 0x08:
			std &= V4L2_STD_SECAM;
			अवरोध;

		हाल 0x04:
		हाल 0x0c:
		हाल 0x1c:
			std &= V4L2_STD_NTSC;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		std = V4L2_STD_UNKNOWN;
	पूर्ण
	अगर (pstd)
		*pstd = std;
	अगर (pstatus)
		*pstatus = res;
	वापस 0;
पूर्ण

अटल पूर्णांक vpx3220_querystd(काष्ठा v4l2_subdev *sd, v4l2_std_id *std)
अणु
	v4l2_dbg(1, debug, sd, "querystd\n");
	वापस vpx3220_status(sd, शून्य, std);
पूर्ण

अटल पूर्णांक vpx3220_g_input_status(काष्ठा v4l2_subdev *sd, u32 *status)
अणु
	v4l2_dbg(1, debug, sd, "g_input_status\n");
	वापस vpx3220_status(sd, status, शून्य);
पूर्ण

अटल पूर्णांक vpx3220_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा vpx3220 *decoder = to_vpx3220(sd);
	पूर्णांक temp_input;

	/* Here we back up the input selection because it माला_लो
	   overwritten when we fill the रेजिस्टरs with the
	   chosen video norm */
	temp_input = vpx3220_fp_पढ़ो(sd, 0xf2);

	v4l2_dbg(1, debug, sd, "s_std %llx\n", (अचिन्हित दीर्घ दीर्घ)std);
	अगर (std & V4L2_STD_NTSC) अणु
		vpx3220_ग_लिखो_fp_block(sd, init_ntsc, माप(init_ntsc) >> 1);
		v4l2_dbg(1, debug, sd, "norm switched to NTSC\n");
	पूर्ण अन्यथा अगर (std & V4L2_STD_PAL) अणु
		vpx3220_ग_लिखो_fp_block(sd, init_pal, माप(init_pal) >> 1);
		v4l2_dbg(1, debug, sd, "norm switched to PAL\n");
	पूर्ण अन्यथा अगर (std & V4L2_STD_SECAM) अणु
		vpx3220_ग_लिखो_fp_block(sd, init_secam, माप(init_secam) >> 1);
		v4l2_dbg(1, debug, sd, "norm switched to SECAM\n");
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	decoder->norm = std;

	/* And here we set the backed up video input again */
	vpx3220_fp_ग_लिखो(sd, 0xf2, temp_input | 0x0010);
	udelay(10);
	वापस 0;
पूर्ण

अटल पूर्णांक vpx3220_s_routing(काष्ठा v4l2_subdev *sd,
			     u32 input, u32 output, u32 config)
अणु
	पूर्णांक data;

	/* RJ:   input = 0: ST8 (PCTV) input
		 input = 1: COMPOSITE  input
		 input = 2: SVHS       input  */

	अटल स्थिर पूर्णांक input_vals[3][2] = अणु
		अणु0x0c, 0पूर्ण,
		अणु0x0d, 0पूर्ण,
		अणु0x0e, 1पूर्ण
	पूर्ण;

	अगर (input > 2)
		वापस -EINVAL;

	v4l2_dbg(1, debug, sd, "input switched to %s\n", inमाला_दो[input]);

	vpx3220_ग_लिखो(sd, 0x33, input_vals[input][0]);

	data = vpx3220_fp_पढ़ो(sd, 0xf2) & ~(0x0020);
	अगर (data < 0)
		वापस data;
	/* 0x0010 is required to latch the setting */
	vpx3220_fp_ग_लिखो(sd, 0xf2,
			data | (input_vals[input][1] << 5) | 0x0010);

	udelay(10);
	वापस 0;
पूर्ण

अटल पूर्णांक vpx3220_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	v4l2_dbg(1, debug, sd, "s_stream %s\n", enable ? "on" : "off");

	vpx3220_ग_लिखो(sd, 0xf2, (enable ? 0x1b : 0x00));
	वापस 0;
पूर्ण

अटल पूर्णांक vpx3220_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		vpx3220_ग_लिखो(sd, 0xe6, ctrl->val);
		वापस 0;
	हाल V4L2_CID_CONTRAST:
		/* Bit 7 and 8 is क्रम noise shaping */
		vpx3220_ग_लिखो(sd, 0xe7, ctrl->val + 192);
		वापस 0;
	हाल V4L2_CID_SATURATION:
		vpx3220_fp_ग_लिखो(sd, 0xa0, ctrl->val);
		वापस 0;
	हाल V4L2_CID_HUE:
		vpx3220_fp_ग_लिखो(sd, 0x1c, ctrl->val);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_ctrl_ops vpx3220_ctrl_ops = अणु
	.s_ctrl = vpx3220_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops vpx3220_core_ops = अणु
	.init = vpx3220_init,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops vpx3220_video_ops = अणु
	.s_std = vpx3220_s_std,
	.s_routing = vpx3220_s_routing,
	.s_stream = vpx3220_s_stream,
	.querystd = vpx3220_querystd,
	.g_input_status = vpx3220_g_input_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops vpx3220_ops = अणु
	.core = &vpx3220_core_ops,
	.video = &vpx3220_video_ops,
पूर्ण;

/* -----------------------------------------------------------------------
 * Client management code
 */

अटल पूर्णांक vpx3220_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा vpx3220 *decoder;
	काष्ठा v4l2_subdev *sd;
	स्थिर अक्षर *name = शून्य;
	u8 ver;
	u16 pn;

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter,
		I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA))
		वापस -ENODEV;

	decoder = devm_kzalloc(&client->dev, माप(*decoder), GFP_KERNEL);
	अगर (decoder == शून्य)
		वापस -ENOMEM;
	sd = &decoder->sd;
	v4l2_i2c_subdev_init(sd, client, &vpx3220_ops);
	decoder->norm = V4L2_STD_PAL;
	decoder->input = 0;
	decoder->enable = 1;
	v4l2_ctrl_handler_init(&decoder->hdl, 4);
	v4l2_ctrl_new_std(&decoder->hdl, &vpx3220_ctrl_ops,
		V4L2_CID_BRIGHTNESS, -128, 127, 1, 0);
	v4l2_ctrl_new_std(&decoder->hdl, &vpx3220_ctrl_ops,
		V4L2_CID_CONTRAST, 0, 63, 1, 32);
	v4l2_ctrl_new_std(&decoder->hdl, &vpx3220_ctrl_ops,
		V4L2_CID_SATURATION, 0, 4095, 1, 2048);
	v4l2_ctrl_new_std(&decoder->hdl, &vpx3220_ctrl_ops,
		V4L2_CID_HUE, -512, 511, 1, 0);
	sd->ctrl_handler = &decoder->hdl;
	अगर (decoder->hdl.error) अणु
		पूर्णांक err = decoder->hdl.error;

		v4l2_ctrl_handler_मुक्त(&decoder->hdl);
		वापस err;
	पूर्ण
	v4l2_ctrl_handler_setup(&decoder->hdl);

	ver = i2c_smbus_पढ़ो_byte_data(client, 0x00);
	pn = (i2c_smbus_पढ़ो_byte_data(client, 0x02) << 8) +
		i2c_smbus_पढ़ो_byte_data(client, 0x01);
	अगर (ver == 0xec) अणु
		चयन (pn) अणु
		हाल 0x4680:
			name = "vpx3220a";
			अवरोध;
		हाल 0x4260:
			name = "vpx3216b";
			अवरोध;
		हाल 0x4280:
			name = "vpx3214c";
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (name)
		v4l2_info(sd, "%s found @ 0x%x (%s)\n", name,
			client->addr << 1, client->adapter->name);
	अन्यथा
		v4l2_info(sd, "chip (%02x:%04x) found @ 0x%x (%s)\n",
			ver, pn, client->addr << 1, client->adapter->name);

	vpx3220_ग_लिखो_block(sd, init_common, माप(init_common));
	vpx3220_ग_लिखो_fp_block(sd, init_fp, माप(init_fp) >> 1);
	/* Default to PAL */
	vpx3220_ग_लिखो_fp_block(sd, init_pal, माप(init_pal) >> 1);
	वापस 0;
पूर्ण

अटल पूर्णांक vpx3220_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा vpx3220 *decoder = to_vpx3220(sd);

	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(&decoder->hdl);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id vpx3220_id[] = अणु
	अणु "vpx3220a", 0 पूर्ण,
	अणु "vpx3216b", 0 पूर्ण,
	अणु "vpx3214c", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, vpx3220_id);

अटल काष्ठा i2c_driver vpx3220_driver = अणु
	.driver = अणु
		.name	= "vpx3220",
	पूर्ण,
	.probe		= vpx3220_probe,
	.हटाओ		= vpx3220_हटाओ,
	.id_table	= vpx3220_id,
पूर्ण;

module_i2c_driver(vpx3220_driver);
