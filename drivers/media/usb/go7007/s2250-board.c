<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008 Sensoray Company Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-subdev.h>
#समावेश "go7007-priv.h"

MODULE_DESCRIPTION("Sensoray 2250/2251 i2c v4l2 subdev driver");
MODULE_LICENSE("GPL v2");

/*
 * Note: this board has two i2c devices: a vpx3226f and a tlv320aic23b.
 * Due to the unusual way these are accessed on this device we करो not
 * reuse the i2c drivers, but instead they are implemented in this
 * driver. It would be nice to improve on this, though.
 */

#घोषणा TLV320_ADDRESS      0x34
#घोषणा VPX322_ADDR_ANALOGCONTROL1	0x02
#घोषणा VPX322_ADDR_BRIGHTNESS0		0x0127
#घोषणा VPX322_ADDR_BRIGHTNESS1		0x0131
#घोषणा VPX322_ADDR_CONTRAST0		0x0128
#घोषणा VPX322_ADDR_CONTRAST1		0x0132
#घोषणा VPX322_ADDR_HUE			0x00dc
#घोषणा VPX322_ADDR_SAT			0x0030

काष्ठा go7007_usb_board अणु
	अचिन्हित पूर्णांक flags;
	काष्ठा go7007_board_info मुख्य_info;
पूर्ण;

काष्ठा go7007_usb अणु
	काष्ठा go7007_usb_board *board;
	काष्ठा mutex i2c_lock;
	काष्ठा usb_device *usbdev;
	काष्ठा urb *video_urbs[8];
	काष्ठा urb *audio_urbs[8];
	काष्ठा urb *पूर्णांकr_urb;
पूर्ण;

अटल अचिन्हित अक्षर aud_regs[] = अणु
	0x1e, 0x00,
	0x00, 0x17,
	0x02, 0x17,
	0x04, 0xf9,
	0x06, 0xf9,
	0x08, 0x02,
	0x0a, 0x00,
	0x0c, 0x00,
	0x0a, 0x00,
	0x0c, 0x00,
	0x0e, 0x02,
	0x10, 0x00,
	0x12, 0x01,
	0x00, 0x00,
पूर्ण;


अटल अचिन्हित अक्षर vid_regs[] = अणु
	0xF2, 0x0f,
	0xAA, 0x00,
	0xF8, 0xff,
	0x00, 0x00,
पूर्ण;

अटल u16 vid_regs_fp[] = अणु
	0x028, 0x067,
	0x120, 0x016,
	0x121, 0xcF2,
	0x122, 0x0F2,
	0x123, 0x00c,
	0x124, 0x2d0,
	0x125, 0x2e0,
	0x126, 0x004,
	0x128, 0x1E0,
	0x12A, 0x016,
	0x12B, 0x0F2,
	0x12C, 0x0F2,
	0x12D, 0x00c,
	0x12E, 0x2d0,
	0x12F, 0x2e0,
	0x130, 0x004,
	0x132, 0x1E0,
	0x140, 0x060,
	0x153, 0x00C,
	0x154, 0x200,
	0x150, 0x801,
	0x000, 0x000
पूर्ण;

/* PAL specअगरic values */
अटल u16 vid_regs_fp_pal[] = अणु
	0x120, 0x017,
	0x121, 0xd22,
	0x122, 0x122,
	0x12A, 0x017,
	0x12B, 0x122,
	0x12C, 0x122,
	0x140, 0x060,
	0x000, 0x000,
पूर्ण;

काष्ठा s2250 अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl_handler hdl;
	v4l2_std_id std;
	पूर्णांक input;
	पूर्णांक brightness;
	पूर्णांक contrast;
	पूर्णांक saturation;
	पूर्णांक hue;
	पूर्णांक reg12b_val;
	पूर्णांक audio_input;
	काष्ठा i2c_client *audio;
पूर्ण;

अटल अंतरभूत काष्ठा s2250 *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा s2250, sd);
पूर्ण

/* from go7007-usb.c which is Copyright (C) 2005-2006 Micronas USA Inc.*/
अटल पूर्णांक go7007_usb_venकरोr_request(काष्ठा go7007 *go, u16 request,
	u16 value, u16 index, व्योम *transfer_buffer, पूर्णांक length, पूर्णांक in)
अणु
	काष्ठा go7007_usb *usb = go->hpi_context;
	पूर्णांक समयout = 5000;

	अगर (in) अणु
		वापस usb_control_msg(usb->usbdev,
				usb_rcvctrlpipe(usb->usbdev, 0), request,
				USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_IN,
				value, index, transfer_buffer, length, समयout);
	पूर्ण अन्यथा अणु
		वापस usb_control_msg(usb->usbdev,
				usb_sndctrlpipe(usb->usbdev, 0), request,
				USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				value, index, transfer_buffer, length, समयout);
	पूर्ण
पूर्ण
/* end from go7007-usb.c which is Copyright (C) 2005-2006 Micronas USA Inc.*/

अटल पूर्णांक ग_लिखो_reg(काष्ठा i2c_client *client, u8 reg, u8 value)
अणु
	काष्ठा go7007 *go = i2c_get_adapdata(client->adapter);
	काष्ठा go7007_usb *usb;
	पूर्णांक rc;
	पूर्णांक dev_addr = client->addr << 1;  /* firmware wants 8-bit address */
	u8 *buf;

	अगर (go == शून्य)
		वापस -ENODEV;

	अगर (go->status == STATUS_SHUTDOWN)
		वापस -EBUSY;

	buf = kzalloc(16, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	usb = go->hpi_context;
	अगर (mutex_lock_पूर्णांकerruptible(&usb->i2c_lock) != 0) अणु
		dev_info(&client->dev, "i2c lock failed\n");
		kमुक्त(buf);
		वापस -EINTR;
	पूर्ण
	rc = go7007_usb_venकरोr_request(go, 0x55, dev_addr,
				       (reg<<8 | value),
				       buf,
				       16, 1);

	mutex_unlock(&usb->i2c_lock);
	kमुक्त(buf);
	वापस rc;
पूर्ण

अटल पूर्णांक ग_लिखो_reg_fp(काष्ठा i2c_client *client, u16 addr, u16 val)
अणु
	काष्ठा go7007 *go = i2c_get_adapdata(client->adapter);
	काष्ठा go7007_usb *usb;
	पूर्णांक rc;
	u8 *buf;
	काष्ठा s2250 *dec = i2c_get_clientdata(client);

	अगर (go == शून्य)
		वापस -ENODEV;

	अगर (go->status == STATUS_SHUTDOWN)
		वापस -EBUSY;

	buf = kzalloc(16, GFP_KERNEL);

	अगर (buf == शून्य)
		वापस -ENOMEM;



	स_रखो(buf, 0xcd, 6);

	usb = go->hpi_context;
	अगर (mutex_lock_पूर्णांकerruptible(&usb->i2c_lock) != 0) अणु
		dev_info(&client->dev, "i2c lock failed\n");
		kमुक्त(buf);
		वापस -EINTR;
	पूर्ण
	rc = go7007_usb_venकरोr_request(go, 0x57, addr, val, buf, 16, 1);
	mutex_unlock(&usb->i2c_lock);
	अगर (rc < 0) अणु
		kमुक्त(buf);
		वापस rc;
	पूर्ण

	अगर (buf[0] == 0) अणु
		अचिन्हित पूर्णांक subaddr, val_पढ़ो;

		subaddr = (buf[4] << 8) + buf[5];
		val_पढ़ो = (buf[2] << 8) + buf[3];
		kमुक्त(buf);
		अगर (val_पढ़ो != val) अणु
			dev_info(&client->dev, "invalid fp write %x %x\n",
				 val_पढ़ो, val);
			वापस -EFAULT;
		पूर्ण
		अगर (subaddr != addr) अणु
			dev_info(&client->dev, "invalid fp write addr %x %x\n",
				 subaddr, addr);
			वापस -EFAULT;
		पूर्ण
	पूर्ण अन्यथा अणु
		kमुक्त(buf);
		वापस -EFAULT;
	पूर्ण

	/* save last 12b value */
	अगर (addr == 0x12b)
		dec->reg12b_val = val;

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_reg_fp(काष्ठा i2c_client *client, u16 addr, u16 *val)
अणु
	काष्ठा go7007 *go = i2c_get_adapdata(client->adapter);
	काष्ठा go7007_usb *usb;
	पूर्णांक rc;
	u8 *buf;

	अगर (go == शून्य)
		वापस -ENODEV;

	अगर (go->status == STATUS_SHUTDOWN)
		वापस -EBUSY;

	buf = kzalloc(16, GFP_KERNEL);

	अगर (buf == शून्य)
		वापस -ENOMEM;



	स_रखो(buf, 0xcd, 6);
	usb = go->hpi_context;
	अगर (mutex_lock_पूर्णांकerruptible(&usb->i2c_lock) != 0) अणु
		dev_info(&client->dev, "i2c lock failed\n");
		kमुक्त(buf);
		वापस -EINTR;
	पूर्ण
	rc = go7007_usb_venकरोr_request(go, 0x58, addr, 0, buf, 16, 1);
	mutex_unlock(&usb->i2c_lock);
	अगर (rc < 0) अणु
		kमुक्त(buf);
		वापस rc;
	पूर्ण

	*val = (buf[0] << 8) | buf[1];
	kमुक्त(buf);

	वापस 0;
पूर्ण


अटल पूर्णांक ग_लिखो_regs(काष्ठा i2c_client *client, u8 *regs)
अणु
	पूर्णांक i;

	क्रम (i = 0; !((regs[i] == 0x00) && (regs[i+1] == 0x00)); i += 2) अणु
		अगर (ग_लिखो_reg(client, regs[i], regs[i+1]) < 0) अणु
			dev_info(&client->dev, "failed\n");
			वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_regs_fp(काष्ठा i2c_client *client, u16 *regs)
अणु
	पूर्णांक i;

	क्रम (i = 0; !((regs[i] == 0x00) && (regs[i+1] == 0x00)); i += 2) अणु
		अगर (ग_लिखो_reg_fp(client, regs[i], regs[i+1]) < 0) अणु
			dev_info(&client->dev, "failed fp\n");
			वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


/* ------------------------------------------------------------------------- */

अटल पूर्णांक s2250_s_video_routing(काष्ठा v4l2_subdev *sd, u32 input, u32 output,
				 u32 config)
अणु
	काष्ठा s2250 *state = to_state(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक vidsys;

	vidsys = (state->std == V4L2_STD_NTSC) ? 0x01 : 0x00;
	अगर (input == 0) अणु
		/* composite */
		ग_लिखो_reg_fp(client, 0x20, 0x020 | vidsys);
		ग_लिखो_reg_fp(client, 0x21, 0x662);
		ग_लिखो_reg_fp(client, 0x140, 0x060);
	पूर्ण अन्यथा अगर (input == 1) अणु
		/* S-Video */
		ग_लिखो_reg_fp(client, 0x20, 0x040 | vidsys);
		ग_लिखो_reg_fp(client, 0x21, 0x666);
		ग_लिखो_reg_fp(client, 0x140, 0x060);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	state->input = input;
	वापस 0;
पूर्ण

अटल पूर्णांक s2250_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id norm)
अणु
	काष्ठा s2250 *state = to_state(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u16 vidsource;

	vidsource = (state->input == 1) ? 0x040 : 0x020;
	अगर (norm & V4L2_STD_625_50) अणु
		ग_लिखो_regs_fp(client, vid_regs_fp);
		ग_लिखो_regs_fp(client, vid_regs_fp_pal);
		ग_लिखो_reg_fp(client, 0x20, vidsource);
	पूर्ण अन्यथा अणु
		ग_लिखो_regs_fp(client, vid_regs_fp);
		ग_लिखो_reg_fp(client, 0x20, vidsource | 1);
	पूर्ण
	state->std = norm;
	वापस 0;
पूर्ण

अटल पूर्णांक s2250_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा s2250 *state = container_of(ctrl->handler, काष्ठा s2250, hdl);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&state->sd);
	u16 oldvalue;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		पढ़ो_reg_fp(client, VPX322_ADDR_BRIGHTNESS0, &oldvalue);
		ग_लिखो_reg_fp(client, VPX322_ADDR_BRIGHTNESS0,
			     ctrl->val | (oldvalue & ~0xff));
		पढ़ो_reg_fp(client, VPX322_ADDR_BRIGHTNESS1, &oldvalue);
		ग_लिखो_reg_fp(client, VPX322_ADDR_BRIGHTNESS1,
			     ctrl->val | (oldvalue & ~0xff));
		ग_लिखो_reg_fp(client, 0x140, 0x60);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		पढ़ो_reg_fp(client, VPX322_ADDR_CONTRAST0, &oldvalue);
		ग_लिखो_reg_fp(client, VPX322_ADDR_CONTRAST0,
			     ctrl->val | (oldvalue & ~0x3f));
		पढ़ो_reg_fp(client, VPX322_ADDR_CONTRAST1, &oldvalue);
		ग_लिखो_reg_fp(client, VPX322_ADDR_CONTRAST1,
			     ctrl->val | (oldvalue & ~0x3f));
		ग_लिखो_reg_fp(client, 0x140, 0x60);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		ग_लिखो_reg_fp(client, VPX322_ADDR_SAT, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HUE:
		ग_लिखो_reg_fp(client, VPX322_ADDR_HUE, ctrl->val);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक s2250_set_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;
	काष्ठा s2250 *state = to_state(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY)
		वापस 0;

	अगर (fmt->height < 640) अणु
		ग_लिखो_reg_fp(client, 0x12b, state->reg12b_val | 0x400);
		ग_लिखो_reg_fp(client, 0x140, 0x060);
	पूर्ण अन्यथा अणु
		ग_लिखो_reg_fp(client, 0x12b, state->reg12b_val & ~0x400);
		ग_लिखो_reg_fp(client, 0x140, 0x060);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक s2250_s_audio_routing(काष्ठा v4l2_subdev *sd, u32 input, u32 output,
				 u32 config)
अणु
	काष्ठा s2250 *state = to_state(sd);

	चयन (input) अणु
	हाल 0:
		ग_लिखो_reg(state->audio, 0x08, 0x02); /* Line In */
		अवरोध;
	हाल 1:
		ग_लिखो_reg(state->audio, 0x08, 0x04); /* Mic */
		अवरोध;
	हाल 2:
		ग_लिखो_reg(state->audio, 0x08, 0x05); /* Mic Boost */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	state->audio_input = input;
	वापस 0;
पूर्ण


अटल पूर्णांक s2250_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा s2250 *state = to_state(sd);

	v4l2_info(sd, "Standard: %s\n", state->std == V4L2_STD_NTSC ? "NTSC" :
					state->std == V4L2_STD_PAL ? "PAL" :
					state->std == V4L2_STD_SECAM ? "SECAM" :
					"unknown");
	v4l2_info(sd, "Input: %s\n", state->input == 0 ? "Composite" :
					state->input == 1 ? "S-video" :
					"error");
	v4l2_info(sd, "Audio input: %s\n", state->audio_input == 0 ? "Line In" :
					state->audio_input == 1 ? "Mic" :
					state->audio_input == 2 ? "Mic Boost" :
					"error");
	वापस v4l2_ctrl_subdev_log_status(sd);
पूर्ण

/* --------------------------------------------------------------------------*/

अटल स्थिर काष्ठा v4l2_ctrl_ops s2250_ctrl_ops = अणु
	.s_ctrl = s2250_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops s2250_core_ops = अणु
	.log_status = s2250_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_audio_ops s2250_audio_ops = अणु
	.s_routing = s2250_s_audio_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops s2250_video_ops = अणु
	.s_std = s2250_s_std,
	.s_routing = s2250_s_video_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops s2250_pad_ops = अणु
	.set_fmt = s2250_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops s2250_ops = अणु
	.core = &s2250_core_ops,
	.audio = &s2250_audio_ops,
	.video = &s2250_video_ops,
	.pad = &s2250_pad_ops,
पूर्ण;

/* --------------------------------------------------------------------------*/

अटल पूर्णांक s2250_probe(काष्ठा i2c_client *client,
		       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_client *audio;
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा s2250 *state;
	काष्ठा v4l2_subdev *sd;
	u8 *data;
	काष्ठा go7007 *go = i2c_get_adapdata(adapter);
	काष्ठा go7007_usb *usb = go->hpi_context;

	audio = i2c_new_dummy_device(adapter, TLV320_ADDRESS >> 1);
	अगर (IS_ERR(audio))
		वापस PTR_ERR(audio);

	state = kzalloc(माप(काष्ठा s2250), GFP_KERNEL);
	अगर (state == शून्य) अणु
		i2c_unरेजिस्टर_device(audio);
		वापस -ENOMEM;
	पूर्ण

	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &s2250_ops);

	v4l2_info(sd, "initializing %s at address 0x%x on %s\n",
	       "Sensoray 2250/2251", client->addr, client->adapter->name);

	v4l2_ctrl_handler_init(&state->hdl, 4);
	v4l2_ctrl_new_std(&state->hdl, &s2250_ctrl_ops,
		V4L2_CID_BRIGHTNESS, -128, 127, 1, 0);
	v4l2_ctrl_new_std(&state->hdl, &s2250_ctrl_ops,
		V4L2_CID_CONTRAST, 0, 0x3f, 1, 0x32);
	v4l2_ctrl_new_std(&state->hdl, &s2250_ctrl_ops,
		V4L2_CID_SATURATION, 0, 4094, 1, 2070);
	v4l2_ctrl_new_std(&state->hdl, &s2250_ctrl_ops,
		V4L2_CID_HUE, -512, 511, 1, 0);
	sd->ctrl_handler = &state->hdl;
	अगर (state->hdl.error) अणु
		पूर्णांक err = state->hdl.error;

		v4l2_ctrl_handler_मुक्त(&state->hdl);
		kमुक्त(state);
		वापस err;
	पूर्ण

	state->std = V4L2_STD_NTSC;
	state->brightness = 50;
	state->contrast = 50;
	state->saturation = 50;
	state->hue = 0;
	state->audio = audio;

	/* initialize the audio */
	अगर (ग_लिखो_regs(audio, aud_regs) < 0) अणु
		dev_err(&client->dev, "error initializing audio\n");
		जाओ fail;
	पूर्ण

	अगर (ग_लिखो_regs(client, vid_regs) < 0) अणु
		dev_err(&client->dev, "error initializing decoder\n");
		जाओ fail;
	पूर्ण
	अगर (ग_लिखो_regs_fp(client, vid_regs_fp) < 0) अणु
		dev_err(&client->dev, "error initializing decoder\n");
		जाओ fail;
	पूर्ण
	/* set शेष channel */
	/* composite */
	ग_लिखो_reg_fp(client, 0x20, 0x020 | 1);
	ग_लिखो_reg_fp(client, 0x21, 0x662);
	ग_लिखो_reg_fp(client, 0x140, 0x060);

	/* set शेष audio input */
	state->audio_input = 0;
	ग_लिखो_reg(client, 0x08, 0x02); /* Line In */

	अगर (mutex_lock_पूर्णांकerruptible(&usb->i2c_lock) == 0) अणु
		data = kzalloc(16, GFP_KERNEL);
		अगर (data != शून्य) अणु
			पूर्णांक rc = go7007_usb_venकरोr_request(go, 0x41, 0, 0,
						       data, 16, 1);

			अगर (rc > 0) अणु
				u8 mask;

				data[0] = 0;
				mask = 1<<5;
				data[0] &= ~mask;
				data[1] |= mask;
				go7007_usb_venकरोr_request(go, 0x40, 0,
							  (data[1]<<8)
							  + data[1],
							  data, 16, 0);
			पूर्ण
			kमुक्त(data);
		पूर्ण
		mutex_unlock(&usb->i2c_lock);
	पूर्ण

	v4l2_info(sd, "initialized successfully\n");
	वापस 0;

fail:
	i2c_unरेजिस्टर_device(audio);
	v4l2_ctrl_handler_मुक्त(&state->hdl);
	kमुक्त(state);
	वापस -EIO;
पूर्ण

अटल पूर्णांक s2250_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा s2250 *state = to_state(i2c_get_clientdata(client));

	i2c_unरेजिस्टर_device(state->audio);
	v4l2_device_unरेजिस्टर_subdev(&state->sd);
	v4l2_ctrl_handler_मुक्त(&state->hdl);
	kमुक्त(state);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id s2250_id[] = अणु
	अणु "s2250", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, s2250_id);

अटल काष्ठा i2c_driver s2250_driver = अणु
	.driver = अणु
		.name	= "s2250",
	पूर्ण,
	.probe		= s2250_probe,
	.हटाओ		= s2250_हटाओ,
	.id_table	= s2250_id,
पूर्ण;

module_i2c_driver(s2250_driver);
