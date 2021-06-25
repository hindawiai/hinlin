<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MFD driver क्रम wl1273 FM radio and audio codec submodules.
 *
 * Copyright (C) 2011 Nokia Corporation
 * Author: Matti Aaltonen <matti.j.aaltonen@nokia.com>
 */

#समावेश <linux/mfd/wl1273-core.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#घोषणा DRIVER_DESC "WL1273 FM Radio Core"

अटल स्थिर काष्ठा i2c_device_id wl1273_driver_id_table[] = अणु
	अणु WL1273_FM_DRIVER_NAME, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wl1273_driver_id_table);

अटल पूर्णांक wl1273_fm_पढ़ो_reg(काष्ठा wl1273_core *core, u8 reg, u16 *value)
अणु
	काष्ठा i2c_client *client = core->client;
	u8 b[2];
	पूर्णांक r;

	r = i2c_smbus_पढ़ो_i2c_block_data(client, reg, माप(b), b);
	अगर (r != 2) अणु
		dev_err(&client->dev, "%s: Read: %d fails.\n", __func__, reg);
		वापस -EREMOTEIO;
	पूर्ण

	*value = (u16)b[0] << 8 | b[1];

	वापस 0;
पूर्ण

अटल पूर्णांक wl1273_fm_ग_लिखो_cmd(काष्ठा wl1273_core *core, u8 cmd, u16 param)
अणु
	काष्ठा i2c_client *client = core->client;
	u8 buf[] = अणु (param >> 8) & 0xff, param & 0xff पूर्ण;
	पूर्णांक r;

	r = i2c_smbus_ग_लिखो_i2c_block_data(client, cmd, माप(buf), buf);
	अगर (r) अणु
		dev_err(&client->dev, "%s: Cmd: %d fails.\n", __func__, cmd);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wl1273_fm_ग_लिखो_data(काष्ठा wl1273_core *core, u8 *data, u16 len)
अणु
	काष्ठा i2c_client *client = core->client;
	काष्ठा i2c_msg msg;
	पूर्णांक r;

	msg.addr = client->addr;
	msg.flags = 0;
	msg.buf = data;
	msg.len = len;

	r = i2c_transfer(client->adapter, &msg, 1);
	अगर (r != 1) अणु
		dev_err(&client->dev, "%s: write error.\n", __func__);
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * wl1273_fm_set_audio() -	Set audio mode.
 * @core:			A poपूर्णांकer to the device काष्ठा.
 * @new_mode:			The new audio mode.
 *
 * Audio modes are WL1273_AUDIO_DIGITAL and WL1273_AUDIO_ANALOG.
 */
अटल पूर्णांक wl1273_fm_set_audio(काष्ठा wl1273_core *core, अचिन्हित पूर्णांक new_mode)
अणु
	पूर्णांक r = 0;

	अगर (core->mode == WL1273_MODE_OFF ||
	    core->mode == WL1273_MODE_SUSPENDED)
		वापस -EPERM;

	अगर (core->mode == WL1273_MODE_RX && new_mode == WL1273_AUDIO_DIGITAL) अणु
		r = wl1273_fm_ग_लिखो_cmd(core, WL1273_PCM_MODE_SET,
					WL1273_PCM_DEF_MODE);
		अगर (r)
			जाओ out;

		r = wl1273_fm_ग_लिखो_cmd(core, WL1273_I2S_MODE_CONFIG_SET,
					core->i2s_mode);
		अगर (r)
			जाओ out;

		r = wl1273_fm_ग_लिखो_cmd(core, WL1273_AUDIO_ENABLE,
					WL1273_AUDIO_ENABLE_I2S);
		अगर (r)
			जाओ out;

	पूर्ण अन्यथा अगर (core->mode == WL1273_MODE_RX &&
		   new_mode == WL1273_AUDIO_ANALOG) अणु
		r = wl1273_fm_ग_लिखो_cmd(core, WL1273_AUDIO_ENABLE,
					WL1273_AUDIO_ENABLE_ANALOG);
		अगर (r)
			जाओ out;

	पूर्ण अन्यथा अगर (core->mode == WL1273_MODE_TX &&
		   new_mode == WL1273_AUDIO_DIGITAL) अणु
		r = wl1273_fm_ग_लिखो_cmd(core, WL1273_I2S_MODE_CONFIG_SET,
					core->i2s_mode);
		अगर (r)
			जाओ out;

		r = wl1273_fm_ग_लिखो_cmd(core, WL1273_AUDIO_IO_SET,
					WL1273_AUDIO_IO_SET_I2S);
		अगर (r)
			जाओ out;

	पूर्ण अन्यथा अगर (core->mode == WL1273_MODE_TX &&
		   new_mode == WL1273_AUDIO_ANALOG) अणु
		r = wl1273_fm_ग_लिखो_cmd(core, WL1273_AUDIO_IO_SET,
					WL1273_AUDIO_IO_SET_ANALOG);
		अगर (r)
			जाओ out;
	पूर्ण

	core->audio_mode = new_mode;
out:
	वापस r;
पूर्ण

/**
 * wl1273_fm_set_volume() -	Set volume.
 * @core:			A poपूर्णांकer to the device काष्ठा.
 * @volume:			The new volume value.
 */
अटल पूर्णांक wl1273_fm_set_volume(काष्ठा wl1273_core *core, अचिन्हित पूर्णांक volume)
अणु
	पूर्णांक r;

	अगर (volume > WL1273_MAX_VOLUME)
		वापस -EINVAL;

	अगर (core->volume == volume)
		वापस 0;

	r = wl1273_fm_ग_लिखो_cmd(core, WL1273_VOLUME_SET, volume);
	अगर (r)
		वापस r;

	core->volume = volume;
	वापस 0;
पूर्ण

अटल पूर्णांक wl1273_core_probe(काष्ठा i2c_client *client,
				       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wl1273_fm_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा wl1273_core *core;
	काष्ठा mfd_cell *cell;
	पूर्णांक children = 0;
	पूर्णांक r = 0;

	dev_dbg(&client->dev, "%s\n", __func__);

	अगर (!pdata) अणु
		dev_err(&client->dev, "No platform data.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!(pdata->children & WL1273_RADIO_CHILD)) अणु
		dev_err(&client->dev, "Cannot function without radio child.\n");
		वापस -EINVAL;
	पूर्ण

	core = devm_kzalloc(&client->dev, माप(*core), GFP_KERNEL);
	अगर (!core)
		वापस -ENOMEM;

	core->pdata = pdata;
	core->client = client;
	mutex_init(&core->lock);

	i2c_set_clientdata(client, core);

	dev_dbg(&client->dev, "%s: Have V4L2.\n", __func__);

	cell = &core->cells[children];
	cell->name = "wl1273_fm_radio";
	cell->platक्रमm_data = &core;
	cell->pdata_size = माप(core);
	children++;

	core->पढ़ो = wl1273_fm_पढ़ो_reg;
	core->ग_लिखो = wl1273_fm_ग_लिखो_cmd;
	core->ग_लिखो_data = wl1273_fm_ग_लिखो_data;
	core->set_audio = wl1273_fm_set_audio;
	core->set_volume = wl1273_fm_set_volume;

	अगर (pdata->children & WL1273_CODEC_CHILD) अणु
		cell = &core->cells[children];

		dev_dbg(&client->dev, "%s: Have codec.\n", __func__);
		cell->name = "wl1273-codec";
		cell->platक्रमm_data = &core;
		cell->pdata_size = माप(core);
		children++;
	पूर्ण

	dev_dbg(&client->dev, "%s: number of children: %d.\n",
		__func__, children);

	r = devm_mfd_add_devices(&client->dev, -1, core->cells,
				 children, शून्य, 0, शून्य);
	अगर (r)
		जाओ err;

	वापस 0;

err:
	pdata->मुक्त_resources();

	dev_dbg(&client->dev, "%s\n", __func__);

	वापस r;
पूर्ण

अटल काष्ठा i2c_driver wl1273_core_driver = अणु
	.driver = अणु
		.name = WL1273_FM_DRIVER_NAME,
	पूर्ण,
	.probe = wl1273_core_probe,
	.id_table = wl1273_driver_id_table,
पूर्ण;

अटल पूर्णांक __init wl1273_core_init(व्योम)
अणु
	पूर्णांक r;

	r = i2c_add_driver(&wl1273_core_driver);
	अगर (r) अणु
		pr_err(WL1273_FM_DRIVER_NAME
		       ": driver registration failed\n");
		वापस r;
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम __निकास wl1273_core_निकास(व्योम)
अणु
	i2c_del_driver(&wl1273_core_driver);
पूर्ण
late_initcall(wl1273_core_init);
module_निकास(wl1273_core_निकास);

MODULE_AUTHOR("Matti Aaltonen <matti.j.aaltonen@nokia.com>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
