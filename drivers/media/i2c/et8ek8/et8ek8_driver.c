<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * et8ek8_driver.c
 *
 * Copyright (C) 2008 Nokia Corporation
 *
 * Contact: Sakari Ailus <sakari.ailus@iki.fi>
 *          Tuukka Toivonen <tuukkat76@gmail.com>
 *          Pavel Machek <pavel@ucw.cz>
 *
 * Based on code from Toni Leinonen <toni.leinonen@offcode.fi>.
 *
 * This driver is based on the Micron MT9T012 camera imager driver
 * (C) Texas Instruments.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/sort.h>
#समावेश <linux/v4l2-mediabus.h>

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "et8ek8_reg.h"

#घोषणा ET8EK8_NAME		"et8ek8"
#घोषणा ET8EK8_PRIV_MEM_SIZE	128
#घोषणा ET8EK8_MAX_MSG		8

काष्ठा et8ek8_sensor अणु
	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad pad;
	काष्ठा v4l2_mbus_framefmt क्रमmat;
	काष्ठा gpio_desc *reset;
	काष्ठा regulator *vana;
	काष्ठा clk *ext_clk;
	u32 xclk_freq;

	u16 version;

	काष्ठा v4l2_ctrl_handler ctrl_handler;
	काष्ठा v4l2_ctrl *exposure;
	काष्ठा v4l2_ctrl *pixel_rate;
	काष्ठा et8ek8_reglist *current_reglist;

	u8 priv_mem[ET8EK8_PRIV_MEM_SIZE];

	काष्ठा mutex घातer_lock;
	पूर्णांक घातer_count;
पूर्ण;

#घोषणा to_et8ek8_sensor(sd)	container_of(sd, काष्ठा et8ek8_sensor, subdev)

क्रमागत et8ek8_versions अणु
	ET8EK8_REV_1 = 0x0001,
	ET8EK8_REV_2,
पूर्ण;

/*
 * This table describes what should be written to the sensor रेजिस्टर
 * क्रम each gain value. The gain(index in the table) is in terms of
 * 0.1EV, i.e. 10 indexes in the table give 2 समय more gain [0] in
 * the *analog gain, [1] in the digital gain
 *
 * Analog gain [dB] = 20*log10(regvalue/32); 0x20..0x100
 */
अटल काष्ठा et8ek8_gain अणु
	u16 analog;
	u16 digital;
पूर्ण स्थिर et8ek8_gain_table[] = अणु
	अणु 32,    0पूर्ण,  /* x1 */
	अणु 34,    0पूर्ण,
	अणु 37,    0पूर्ण,
	अणु 39,    0पूर्ण,
	अणु 42,    0पूर्ण,
	अणु 45,    0पूर्ण,
	अणु 49,    0पूर्ण,
	अणु 52,    0पूर्ण,
	अणु 56,    0पूर्ण,
	अणु 60,    0पूर्ण,
	अणु 64,    0पूर्ण,  /* x2 */
	अणु 69,    0पूर्ण,
	अणु 74,    0पूर्ण,
	अणु 79,    0पूर्ण,
	अणु 84,    0पूर्ण,
	अणु 91,    0पूर्ण,
	अणु 97,    0पूर्ण,
	अणु104,    0पूर्ण,
	अणु111,    0पूर्ण,
	अणु119,    0पूर्ण,
	अणु128,    0पूर्ण,  /* x4 */
	अणु137,    0पूर्ण,
	अणु147,    0पूर्ण,
	अणु158,    0पूर्ण,
	अणु169,    0पूर्ण,
	अणु181,    0पूर्ण,
	अणु194,    0पूर्ण,
	अणु208,    0पूर्ण,
	अणु223,    0पूर्ण,
	अणु239,    0पूर्ण,
	अणु256,    0पूर्ण,  /* x8 */
	अणु256,   73पूर्ण,
	अणु256,  152पूर्ण,
	अणु256,  236पूर्ण,
	अणु256,  327पूर्ण,
	अणु256,  424पूर्ण,
	अणु256,  528पूर्ण,
	अणु256,  639पूर्ण,
	अणु256,  758पूर्ण,
	अणु256,  886पूर्ण,
	अणु256, 1023पूर्ण,  /* x16 */
पूर्ण;

/* Register definitions */
#घोषणा REG_REVISION_NUMBER_L	0x1200
#घोषणा REG_REVISION_NUMBER_H	0x1201

#घोषणा PRIV_MEM_START_REG	0x0008
#घोषणा PRIV_MEM_WIN_SIZE	8

#घोषणा ET8EK8_I2C_DELAY	3	/* msec delay b/w accesses */

#घोषणा USE_CRC			1

/*
 * Register access helpers
 *
 * Read a 8/16/32-bit i2c रेजिस्टर.  The value is वापसed in 'val'.
 * Returns zero अगर successful, or non-zero otherwise.
 */
अटल पूर्णांक et8ek8_i2c_पढ़ो_reg(काष्ठा i2c_client *client, u16 data_length,
			       u16 reg, u32 *val)
अणु
	पूर्णांक r;
	काष्ठा i2c_msg msg;
	अचिन्हित अक्षर data[4];

	अगर (!client->adapter)
		वापस -ENODEV;
	अगर (data_length != ET8EK8_REG_8BIT && data_length != ET8EK8_REG_16BIT)
		वापस -EINVAL;

	msg.addr = client->addr;
	msg.flags = 0;
	msg.len = 2;
	msg.buf = data;

	/* high byte goes out first */
	data[0] = (u8) (reg >> 8);
	data[1] = (u8) (reg & 0xff);
	r = i2c_transfer(client->adapter, &msg, 1);
	अगर (r < 0)
		जाओ err;

	msg.len = data_length;
	msg.flags = I2C_M_RD;
	r = i2c_transfer(client->adapter, &msg, 1);
	अगर (r < 0)
		जाओ err;

	*val = 0;
	/* high byte comes first */
	अगर (data_length == ET8EK8_REG_8BIT)
		*val = data[0];
	अन्यथा
		*val = (data[1] << 8) + data[0];

	वापस 0;

err:
	dev_err(&client->dev, "read from offset 0x%x error %d\n", reg, r);

	वापस r;
पूर्ण

अटल व्योम et8ek8_i2c_create_msg(काष्ठा i2c_client *client, u16 len, u16 reg,
				  u32 val, काष्ठा i2c_msg *msg,
				  अचिन्हित अक्षर *buf)
अणु
	msg->addr = client->addr;
	msg->flags = 0; /* Write */
	msg->len = 2 + len;
	msg->buf = buf;

	/* high byte goes out first */
	buf[0] = (u8) (reg >> 8);
	buf[1] = (u8) (reg & 0xff);

	चयन (len) अणु
	हाल ET8EK8_REG_8BIT:
		buf[2] = (u8) (val) & 0xff;
		अवरोध;
	हाल ET8EK8_REG_16BIT:
		buf[2] = (u8) (val) & 0xff;
		buf[3] = (u8) (val >> 8) & 0xff;
		अवरोध;
	शेष:
		WARN_ONCE(1, ET8EK8_NAME ": %s: invalid message length.\n",
			  __func__);
	पूर्ण
पूर्ण

/*
 * A buffered ग_लिखो method that माला_दो the wanted रेजिस्टर ग_लिखो
 * commands in smaller number of message lists and passes the lists to
 * the i2c framework
 */
अटल पूर्णांक et8ek8_i2c_buffered_ग_लिखो_regs(काष्ठा i2c_client *client,
					  स्थिर काष्ठा et8ek8_reg *wnext,
					  पूर्णांक cnt)
अणु
	काष्ठा i2c_msg msg[ET8EK8_MAX_MSG];
	अचिन्हित अक्षर data[ET8EK8_MAX_MSG][6];
	पूर्णांक wcnt = 0;
	u16 reg, data_length;
	u32 val;
	पूर्णांक rval;

	/* Create new ग_लिखो messages क्रम all ग_लिखोs */
	जबतक (wcnt < cnt) अणु
		data_length = wnext->type;
		reg = wnext->reg;
		val = wnext->val;
		wnext++;

		et8ek8_i2c_create_msg(client, data_length, reg,
				    val, &msg[wcnt], &data[wcnt][0]);

		/* Update ग_लिखो count */
		wcnt++;

		अगर (wcnt < ET8EK8_MAX_MSG)
			जारी;

		rval = i2c_transfer(client->adapter, msg, wcnt);
		अगर (rval < 0)
			वापस rval;

		cnt -= wcnt;
		wcnt = 0;
	पूर्ण

	rval = i2c_transfer(client->adapter, msg, wcnt);

	वापस rval < 0 ? rval : 0;
पूर्ण

/*
 * Write a list of रेजिस्टरs to i2c device.
 *
 * The list of रेजिस्टरs is terminated by ET8EK8_REG_TERM.
 * Returns zero अगर successful, or non-zero otherwise.
 */
अटल पूर्णांक et8ek8_i2c_ग_लिखो_regs(काष्ठा i2c_client *client,
				 स्थिर काष्ठा et8ek8_reg *regs)
अणु
	पूर्णांक r, cnt = 0;
	स्थिर काष्ठा et8ek8_reg *next;

	अगर (!client->adapter)
		वापस -ENODEV;

	अगर (!regs)
		वापस -EINVAL;

	/* Initialize list poपूर्णांकers to the start of the list */
	next = regs;

	करो अणु
		/*
		 * We have to go through the list to figure out how
		 * many regular ग_लिखोs we have in a row
		 */
		जबतक (next->type != ET8EK8_REG_TERM &&
		       next->type != ET8EK8_REG_DELAY) अणु
			/*
			 * Here we check that the actual length fields
			 * are valid
			 */
			अगर (WARN(next->type != ET8EK8_REG_8BIT &&
				 next->type != ET8EK8_REG_16BIT,
				 "Invalid type = %d", next->type)) अणु
				वापस -EINVAL;
			पूर्ण
			/*
			 * Increment count of successive ग_लिखोs and
			 * पढ़ो poपूर्णांकer
			 */
			cnt++;
			next++;
		पूर्ण

		/* Now we start writing ... */
		r = et8ek8_i2c_buffered_ग_लिखो_regs(client, regs, cnt);

		/* ... and then check that everything was OK */
		अगर (r < 0) अणु
			dev_err(&client->dev, "i2c transfer error!\n");
			वापस r;
		पूर्ण

		/*
		 * If we ran पूर्णांकo a sleep statement when going through
		 * the list, this is where we snooze क्रम the required समय
		 */
		अगर (next->type == ET8EK8_REG_DELAY) अणु
			msleep(next->val);
			/*
			 * ZZZ ...
			 * Update list poपूर्णांकers and cnt and start over ...
			 */
			next++;
			regs = next;
			cnt = 0;
		पूर्ण
	पूर्ण जबतक (next->type != ET8EK8_REG_TERM);

	वापस 0;
पूर्ण

/*
 * Write to a 8/16-bit रेजिस्टर.
 * Returns zero अगर successful, or non-zero otherwise.
 */
अटल पूर्णांक et8ek8_i2c_ग_लिखो_reg(काष्ठा i2c_client *client, u16 data_length,
				u16 reg, u32 val)
अणु
	पूर्णांक r;
	काष्ठा i2c_msg msg;
	अचिन्हित अक्षर data[6];

	अगर (!client->adapter)
		वापस -ENODEV;
	अगर (data_length != ET8EK8_REG_8BIT && data_length != ET8EK8_REG_16BIT)
		वापस -EINVAL;

	et8ek8_i2c_create_msg(client, data_length, reg, val, &msg, data);

	r = i2c_transfer(client->adapter, &msg, 1);
	अगर (r < 0) अणु
		dev_err(&client->dev,
			"wrote 0x%x to offset 0x%x error %d\n", val, reg, r);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा et8ek8_reglist *et8ek8_reglist_find_type(
		काष्ठा et8ek8_meta_reglist *meta,
		u16 type)
अणु
	काष्ठा et8ek8_reglist **next = &meta->reglist[0].ptr;

	जबतक (*next) अणु
		अगर ((*next)->type == type)
			वापस *next;

		next++;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक et8ek8_i2c_reglist_find_ग_लिखो(काष्ठा i2c_client *client,
					 काष्ठा et8ek8_meta_reglist *meta,
					 u16 type)
अणु
	काष्ठा et8ek8_reglist *reglist;

	reglist = et8ek8_reglist_find_type(meta, type);
	अगर (!reglist)
		वापस -EINVAL;

	वापस et8ek8_i2c_ग_लिखो_regs(client, reglist->regs);
पूर्ण

अटल काष्ठा et8ek8_reglist **et8ek8_reglist_first(
		काष्ठा et8ek8_meta_reglist *meta)
अणु
	वापस &meta->reglist[0].ptr;
पूर्ण

अटल व्योम et8ek8_reglist_to_mbus(स्थिर काष्ठा et8ek8_reglist *reglist,
				   काष्ठा v4l2_mbus_framefmt *fmt)
अणु
	fmt->width = reglist->mode.winकरोw_width;
	fmt->height = reglist->mode.winकरोw_height;
	fmt->code = reglist->mode.bus_क्रमmat;
पूर्ण

अटल काष्ठा et8ek8_reglist *et8ek8_reglist_find_mode_fmt(
		काष्ठा et8ek8_meta_reglist *meta,
		काष्ठा v4l2_mbus_framefmt *fmt)
अणु
	काष्ठा et8ek8_reglist **list = et8ek8_reglist_first(meta);
	काष्ठा et8ek8_reglist *best_match = शून्य;
	काष्ठा et8ek8_reglist *best_other = शून्य;
	काष्ठा v4l2_mbus_framefmt क्रमmat;
	अचिन्हित पूर्णांक max_dist_match = (अचिन्हित पूर्णांक)-1;
	अचिन्हित पूर्णांक max_dist_other = (अचिन्हित पूर्णांक)-1;

	/*
	 * Find the mode with the बंदst image size. The distance between
	 * image sizes is the size in pixels of the non-overlapping regions
	 * between the requested size and the frame-specअगरied size.
	 *
	 * Store both the बंदst mode that matches the requested क्रमmat, and
	 * the बंदst mode क्रम all other क्रमmats. The best match is वापसed
	 * अगर found, otherwise the best mode with a non-matching क्रमmat is
	 * वापसed.
	 */
	क्रम (; *list; list++) अणु
		अचिन्हित पूर्णांक dist;

		अगर ((*list)->type != ET8EK8_REGLIST_MODE)
			जारी;

		et8ek8_reglist_to_mbus(*list, &क्रमmat);

		dist = min(fmt->width, क्रमmat.width)
		     * min(fmt->height, क्रमmat.height);
		dist = क्रमmat.width * क्रमmat.height
		     + fmt->width * fmt->height - 2 * dist;


		अगर (fmt->code == क्रमmat.code) अणु
			अगर (dist < max_dist_match || !best_match) अणु
				best_match = *list;
				max_dist_match = dist;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (dist < max_dist_other || !best_other) अणु
				best_other = *list;
				max_dist_other = dist;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस best_match ? best_match : best_other;
पूर्ण

#घोषणा TIMEPERFRAME_AVG_FPS(t)						\
	(((t).denominator + ((t).numerator >> 1)) / (t).numerator)

अटल काष्ठा et8ek8_reglist *et8ek8_reglist_find_mode_ival(
		काष्ठा et8ek8_meta_reglist *meta,
		काष्ठा et8ek8_reglist *current_reglist,
		काष्ठा v4l2_fract *समयperframe)
अणु
	पूर्णांक fps = TIMEPERFRAME_AVG_FPS(*समयperframe);
	काष्ठा et8ek8_reglist **list = et8ek8_reglist_first(meta);
	काष्ठा et8ek8_mode *current_mode = &current_reglist->mode;

	क्रम (; *list; list++) अणु
		काष्ठा et8ek8_mode *mode = &(*list)->mode;

		अगर ((*list)->type != ET8EK8_REGLIST_MODE)
			जारी;

		अगर (mode->winकरोw_width != current_mode->winकरोw_width ||
		    mode->winकरोw_height != current_mode->winकरोw_height)
			जारी;

		अगर (TIMEPERFRAME_AVG_FPS(mode->समयperframe) == fps)
			वापस *list;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक et8ek8_reglist_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा et8ek8_reglist **list1 = (स्थिर काष्ठा et8ek8_reglist **)a,
		**list2 = (स्थिर काष्ठा et8ek8_reglist **)b;

	/* Put real modes in the beginning. */
	अगर ((*list1)->type == ET8EK8_REGLIST_MODE &&
	    (*list2)->type != ET8EK8_REGLIST_MODE)
		वापस -1;
	अगर ((*list1)->type != ET8EK8_REGLIST_MODE &&
	    (*list2)->type == ET8EK8_REGLIST_MODE)
		वापस 1;

	/* Descending width. */
	अगर ((*list1)->mode.winकरोw_width > (*list2)->mode.winकरोw_width)
		वापस -1;
	अगर ((*list1)->mode.winकरोw_width < (*list2)->mode.winकरोw_width)
		वापस 1;

	अगर ((*list1)->mode.winकरोw_height > (*list2)->mode.winकरोw_height)
		वापस -1;
	अगर ((*list1)->mode.winकरोw_height < (*list2)->mode.winकरोw_height)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक et8ek8_reglist_import(काष्ठा i2c_client *client,
				 काष्ठा et8ek8_meta_reglist *meta)
अणु
	पूर्णांक nlists = 0, i;

	dev_info(&client->dev, "meta_reglist version %s\n", meta->version);

	जबतक (meta->reglist[nlists].ptr)
		nlists++;

	अगर (!nlists)
		वापस -EINVAL;

	sort(&meta->reglist[0].ptr, nlists, माप(meta->reglist[0].ptr),
	     et8ek8_reglist_cmp, शून्य);

	i = nlists;
	nlists = 0;

	जबतक (i--) अणु
		काष्ठा et8ek8_reglist *list;

		list = meta->reglist[nlists].ptr;

		dev_dbg(&client->dev,
		       "%s: type %d\tw %d\th %d\tfmt %x\tival %d/%d\tptr %p\n",
		       __func__,
		       list->type,
		       list->mode.winकरोw_width, list->mode.winकरोw_height,
		       list->mode.bus_क्रमmat,
		       list->mode.समयperframe.numerator,
		       list->mode.समयperframe.denominator,
		       (व्योम *)meta->reglist[nlists].ptr);

		nlists++;
	पूर्ण

	वापस 0;
पूर्ण

/* Called to change the V4L2 gain control value. This function
 * rounds and clamps the given value and updates the V4L2 control value.
 * If घातer is on, also updates the sensor analog and digital gains.
 * gain is in 0.1 EV (exposure value) units.
 */
अटल पूर्णांक et8ek8_set_gain(काष्ठा et8ek8_sensor *sensor, s32 gain)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->subdev);
	काष्ठा et8ek8_gain new;
	पूर्णांक r;

	new = et8ek8_gain_table[gain];

	/* FIXME: optimise I2C ग_लिखोs! */
	r = et8ek8_i2c_ग_लिखो_reg(client, ET8EK8_REG_8BIT,
				0x124a, new.analog >> 8);
	अगर (r)
		वापस r;
	r = et8ek8_i2c_ग_लिखो_reg(client, ET8EK8_REG_8BIT,
				0x1249, new.analog & 0xff);
	अगर (r)
		वापस r;

	r = et8ek8_i2c_ग_लिखो_reg(client, ET8EK8_REG_8BIT,
				0x124d, new.digital >> 8);
	अगर (r)
		वापस r;
	r = et8ek8_i2c_ग_लिखो_reg(client, ET8EK8_REG_8BIT,
				0x124c, new.digital & 0xff);

	वापस r;
पूर्ण

अटल पूर्णांक et8ek8_set_test_pattern(काष्ठा et8ek8_sensor *sensor, s32 mode)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->subdev);
	पूर्णांक cbh_mode, cbv_mode, tp_mode, din_sw, r1420, rval;

	/* Values क्रम normal mode */
	cbh_mode = 0;
	cbv_mode = 0;
	tp_mode  = 0;
	din_sw   = 0x00;
	r1420    = 0xF0;

	अगर (mode) अणु
		/* Test pattern mode */
		अगर (mode < 5) अणु
			cbh_mode = 1;
			cbv_mode = 1;
			tp_mode  = mode + 3;
		पूर्ण अन्यथा अणु
			cbh_mode = 0;
			cbv_mode = 0;
			tp_mode  = mode - 4 + 3;
		पूर्ण

		din_sw   = 0x01;
		r1420    = 0xE0;
	पूर्ण

	rval = et8ek8_i2c_ग_लिखो_reg(client, ET8EK8_REG_8BIT, 0x111B,
				    tp_mode << 4);
	अगर (rval)
		वापस rval;

	rval = et8ek8_i2c_ग_लिखो_reg(client, ET8EK8_REG_8BIT, 0x1121,
				    cbh_mode << 7);
	अगर (rval)
		वापस rval;

	rval = et8ek8_i2c_ग_लिखो_reg(client, ET8EK8_REG_8BIT, 0x1124,
				    cbv_mode << 7);
	अगर (rval)
		वापस rval;

	rval = et8ek8_i2c_ग_लिखो_reg(client, ET8EK8_REG_8BIT, 0x112C, din_sw);
	अगर (rval)
		वापस rval;

	वापस et8ek8_i2c_ग_लिखो_reg(client, ET8EK8_REG_8BIT, 0x1420, r1420);
पूर्ण

/* -----------------------------------------------------------------------------
 * V4L2 controls
 */

अटल पूर्णांक et8ek8_set_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा et8ek8_sensor *sensor =
		container_of(ctrl->handler, काष्ठा et8ek8_sensor, ctrl_handler);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_GAIN:
		वापस et8ek8_set_gain(sensor, ctrl->val);

	हाल V4L2_CID_EXPOSURE:
	अणु
		काष्ठा i2c_client *client =
			v4l2_get_subdevdata(&sensor->subdev);

		वापस et8ek8_i2c_ग_लिखो_reg(client, ET8EK8_REG_16BIT, 0x1243,
					    ctrl->val);
	पूर्ण

	हाल V4L2_CID_TEST_PATTERN:
		वापस et8ek8_set_test_pattern(sensor, ctrl->val);

	हाल V4L2_CID_PIXEL_RATE:
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops et8ek8_ctrl_ops = अणु
	.s_ctrl = et8ek8_set_ctrl,
पूर्ण;

अटल स्थिर अक्षर * स्थिर et8ek8_test_pattern_menu[] = अणु
	"Normal",
	"Vertical colorbar",
	"Horizontal colorbar",
	"Scale",
	"Ramp",
	"Small vertical colorbar",
	"Small horizontal colorbar",
	"Small scale",
	"Small ramp",
पूर्ण;

अटल पूर्णांक et8ek8_init_controls(काष्ठा et8ek8_sensor *sensor)
अणु
	s32 max_rows;

	v4l2_ctrl_handler_init(&sensor->ctrl_handler, 4);

	/* V4L2_CID_GAIN */
	v4l2_ctrl_new_std(&sensor->ctrl_handler, &et8ek8_ctrl_ops,
			  V4L2_CID_GAIN, 0, ARRAY_SIZE(et8ek8_gain_table) - 1,
			  1, 0);

	max_rows = sensor->current_reglist->mode.max_exp;
	अणु
		u32 min = 1, max = max_rows;

		sensor->exposure =
			v4l2_ctrl_new_std(&sensor->ctrl_handler,
					  &et8ek8_ctrl_ops, V4L2_CID_EXPOSURE,
					  min, max, min, max);
	पूर्ण

	/* V4L2_CID_PIXEL_RATE */
	sensor->pixel_rate =
		v4l2_ctrl_new_std(&sensor->ctrl_handler, &et8ek8_ctrl_ops,
		V4L2_CID_PIXEL_RATE, 1, पूर्णांक_उच्च, 1, 1);

	/* V4L2_CID_TEST_PATTERN */
	v4l2_ctrl_new_std_menu_items(&sensor->ctrl_handler,
				     &et8ek8_ctrl_ops, V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(et8ek8_test_pattern_menu) - 1,
				     0, 0, et8ek8_test_pattern_menu);

	अगर (sensor->ctrl_handler.error)
		वापस sensor->ctrl_handler.error;

	sensor->subdev.ctrl_handler = &sensor->ctrl_handler;

	वापस 0;
पूर्ण

अटल व्योम et8ek8_update_controls(काष्ठा et8ek8_sensor *sensor)
अणु
	काष्ठा v4l2_ctrl *ctrl;
	काष्ठा et8ek8_mode *mode = &sensor->current_reglist->mode;

	u32 min, max, pixel_rate;
	अटल स्थिर पूर्णांक S = 8;

	ctrl = sensor->exposure;

	min = 1;
	max = mode->max_exp;

	/*
	 * Calculate average pixel घड़ी per line. Assume buffers can spपढ़ो
	 * the data over horizontal blanking समय. Rounding upwards.
	 * Formula taken from stock Nokia N900 kernel.
	 */
	pixel_rate = ((mode->pixel_घड़ी + (1 << S) - 1) >> S) + mode->width;
	pixel_rate = mode->winकरोw_width * (pixel_rate - 1) / mode->width;

	__v4l2_ctrl_modअगरy_range(ctrl, min, max, min, max);
	__v4l2_ctrl_s_ctrl_पूर्णांक64(sensor->pixel_rate, pixel_rate << S);
पूर्ण

अटल पूर्णांक et8ek8_configure(काष्ठा et8ek8_sensor *sensor)
अणु
	काष्ठा v4l2_subdev *subdev = &sensor->subdev;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(subdev);
	पूर्णांक rval;

	rval = et8ek8_i2c_ग_लिखो_regs(client, sensor->current_reglist->regs);
	अगर (rval)
		जाओ fail;

	/* Controls set जबतक the घातer to the sensor is turned off are saved
	 * but not applied to the hardware. Now that we're about to start
	 * streaming apply all the current values to the hardware.
	 */
	rval = v4l2_ctrl_handler_setup(&sensor->ctrl_handler);
	अगर (rval)
		जाओ fail;

	वापस 0;

fail:
	dev_err(&client->dev, "sensor configuration failed\n");

	वापस rval;
पूर्ण

अटल पूर्णांक et8ek8_stream_on(काष्ठा et8ek8_sensor *sensor)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->subdev);

	वापस et8ek8_i2c_ग_लिखो_reg(client, ET8EK8_REG_8BIT, 0x1252, 0xb0);
पूर्ण

अटल पूर्णांक et8ek8_stream_off(काष्ठा et8ek8_sensor *sensor)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->subdev);

	वापस et8ek8_i2c_ग_लिखो_reg(client, ET8EK8_REG_8BIT, 0x1252, 0x30);
पूर्ण

अटल पूर्णांक et8ek8_s_stream(काष्ठा v4l2_subdev *subdev, पूर्णांक streaming)
अणु
	काष्ठा et8ek8_sensor *sensor = to_et8ek8_sensor(subdev);
	पूर्णांक ret;

	अगर (!streaming)
		वापस et8ek8_stream_off(sensor);

	ret = et8ek8_configure(sensor);
	अगर (ret < 0)
		वापस ret;

	वापस et8ek8_stream_on(sensor);
पूर्ण

/* --------------------------------------------------------------------------
 * V4L2 subdev operations
 */

अटल पूर्णांक et8ek8_घातer_off(काष्ठा et8ek8_sensor *sensor)
अणु
	gpiod_set_value(sensor->reset, 0);
	udelay(1);

	clk_disable_unprepare(sensor->ext_clk);

	वापस regulator_disable(sensor->vana);
पूर्ण

अटल पूर्णांक et8ek8_घातer_on(काष्ठा et8ek8_sensor *sensor)
अणु
	काष्ठा v4l2_subdev *subdev = &sensor->subdev;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(subdev);
	अचिन्हित पूर्णांक xclk_freq;
	पूर्णांक val, rval;

	rval = regulator_enable(sensor->vana);
	अगर (rval) अणु
		dev_err(&client->dev, "failed to enable vana regulator\n");
		वापस rval;
	पूर्ण

	अगर (sensor->current_reglist)
		xclk_freq = sensor->current_reglist->mode.ext_घड़ी;
	अन्यथा
		xclk_freq = sensor->xclk_freq;

	rval = clk_set_rate(sensor->ext_clk, xclk_freq);
	अगर (rval < 0) अणु
		dev_err(&client->dev, "unable to set extclk clock freq to %u\n",
			xclk_freq);
		जाओ out;
	पूर्ण
	rval = clk_prepare_enable(sensor->ext_clk);
	अगर (rval < 0) अणु
		dev_err(&client->dev, "failed to enable extclk\n");
		जाओ out;
	पूर्ण

	अगर (rval)
		जाओ out;

	udelay(10); /* I wish this is a good value */

	gpiod_set_value(sensor->reset, 1);

	msleep(5000 * 1000 / xclk_freq + 1); /* Wait 5000 cycles */

	rval = et8ek8_i2c_reglist_find_ग_लिखो(client, &meta_reglist,
					     ET8EK8_REGLIST_POWERON);
	अगर (rval)
		जाओ out;

#अगर_घोषित USE_CRC
	rval = et8ek8_i2c_पढ़ो_reg(client, ET8EK8_REG_8BIT, 0x1263, &val);
	अगर (rval)
		जाओ out;
#अगर USE_CRC /* TODO get crc setting from DT */
	val |= BIT(4);
#अन्यथा
	val &= ~BIT(4);
#पूर्ण_अगर
	rval = et8ek8_i2c_ग_लिखो_reg(client, ET8EK8_REG_8BIT, 0x1263, val);
	अगर (rval)
		जाओ out;
#पूर्ण_अगर

out:
	अगर (rval)
		et8ek8_घातer_off(sensor);

	वापस rval;
पूर्ण

/* --------------------------------------------------------------------------
 * V4L2 subdev video operations
 */
#घोषणा MAX_FMTS 4
अटल पूर्णांक et8ek8_क्रमागत_mbus_code(काष्ठा v4l2_subdev *subdev,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा et8ek8_reglist **list =
			et8ek8_reglist_first(&meta_reglist);
	u32 pixelक्रमmat[MAX_FMTS];
	पूर्णांक npixelक्रमmat = 0;

	अगर (code->index >= MAX_FMTS)
		वापस -EINVAL;

	क्रम (; *list; list++) अणु
		काष्ठा et8ek8_mode *mode = &(*list)->mode;
		पूर्णांक i;

		अगर ((*list)->type != ET8EK8_REGLIST_MODE)
			जारी;

		क्रम (i = 0; i < npixelक्रमmat; i++) अणु
			अगर (pixelक्रमmat[i] == mode->bus_क्रमmat)
				अवरोध;
		पूर्ण
		अगर (i != npixelक्रमmat)
			जारी;

		अगर (code->index == npixelक्रमmat) अणु
			code->code = mode->bus_क्रमmat;
			वापस 0;
		पूर्ण

		pixelक्रमmat[npixelक्रमmat] = mode->bus_क्रमmat;
		npixelक्रमmat++;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक et8ek8_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा et8ek8_reglist **list =
			et8ek8_reglist_first(&meta_reglist);
	काष्ठा v4l2_mbus_framefmt क्रमmat;
	पूर्णांक cmp_width = पूर्णांक_उच्च;
	पूर्णांक cmp_height = पूर्णांक_उच्च;
	पूर्णांक index = fse->index;

	क्रम (; *list; list++) अणु
		अगर ((*list)->type != ET8EK8_REGLIST_MODE)
			जारी;

		et8ek8_reglist_to_mbus(*list, &क्रमmat);
		अगर (fse->code != क्रमmat.code)
			जारी;

		/* Assume that the modes are grouped by frame size. */
		अगर (क्रमmat.width == cmp_width && क्रमmat.height == cmp_height)
			जारी;

		cmp_width = क्रमmat.width;
		cmp_height = क्रमmat.height;

		अगर (index-- == 0) अणु
			fse->min_width = क्रमmat.width;
			fse->min_height = क्रमmat.height;
			fse->max_width = क्रमmat.width;
			fse->max_height = क्रमmat.height;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक et8ek8_क्रमागत_frame_ival(काष्ठा v4l2_subdev *subdev,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत *fie)
अणु
	काष्ठा et8ek8_reglist **list =
			et8ek8_reglist_first(&meta_reglist);
	काष्ठा v4l2_mbus_framefmt क्रमmat;
	पूर्णांक index = fie->index;

	क्रम (; *list; list++) अणु
		काष्ठा et8ek8_mode *mode = &(*list)->mode;

		अगर ((*list)->type != ET8EK8_REGLIST_MODE)
			जारी;

		et8ek8_reglist_to_mbus(*list, &क्रमmat);
		अगर (fie->code != क्रमmat.code)
			जारी;

		अगर (fie->width != क्रमmat.width || fie->height != क्रमmat.height)
			जारी;

		अगर (index-- == 0) अणु
			fie->पूर्णांकerval = mode->समयperframe;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *
__et8ek8_get_pad_क्रमmat(काष्ठा et8ek8_sensor *sensor,
			काष्ठा v4l2_subdev_pad_config *cfg,
			अचिन्हित पूर्णांक pad, क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	चयन (which) अणु
	हाल V4L2_SUBDEV_FORMAT_TRY:
		वापस v4l2_subdev_get_try_क्रमmat(&sensor->subdev, cfg, pad);
	हाल V4L2_SUBDEV_FORMAT_ACTIVE:
		वापस &sensor->क्रमmat;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक et8ek8_get_pad_क्रमmat(काष्ठा v4l2_subdev *subdev,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा et8ek8_sensor *sensor = to_et8ek8_sensor(subdev);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = __et8ek8_get_pad_क्रमmat(sensor, cfg, fmt->pad, fmt->which);
	अगर (!क्रमmat)
		वापस -EINVAL;

	fmt->क्रमmat = *क्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक et8ek8_set_pad_क्रमmat(काष्ठा v4l2_subdev *subdev,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा et8ek8_sensor *sensor = to_et8ek8_sensor(subdev);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	काष्ठा et8ek8_reglist *reglist;

	क्रमmat = __et8ek8_get_pad_क्रमmat(sensor, cfg, fmt->pad, fmt->which);
	अगर (!क्रमmat)
		वापस -EINVAL;

	reglist = et8ek8_reglist_find_mode_fmt(&meta_reglist, &fmt->क्रमmat);
	et8ek8_reglist_to_mbus(reglist, &fmt->क्रमmat);
	*क्रमmat = fmt->क्रमmat;

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		sensor->current_reglist = reglist;
		et8ek8_update_controls(sensor);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक et8ek8_get_frame_पूर्णांकerval(काष्ठा v4l2_subdev *subdev,
				     काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा et8ek8_sensor *sensor = to_et8ek8_sensor(subdev);

	स_रखो(fi, 0, माप(*fi));
	fi->पूर्णांकerval = sensor->current_reglist->mode.समयperframe;

	वापस 0;
पूर्ण

अटल पूर्णांक et8ek8_set_frame_पूर्णांकerval(काष्ठा v4l2_subdev *subdev,
				     काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा et8ek8_sensor *sensor = to_et8ek8_sensor(subdev);
	काष्ठा et8ek8_reglist *reglist;

	reglist = et8ek8_reglist_find_mode_ival(&meta_reglist,
						sensor->current_reglist,
						&fi->पूर्णांकerval);

	अगर (!reglist)
		वापस -EINVAL;

	अगर (sensor->current_reglist->mode.ext_घड़ी != reglist->mode.ext_घड़ी)
		वापस -EINVAL;

	sensor->current_reglist = reglist;
	et8ek8_update_controls(sensor);

	वापस 0;
पूर्ण

अटल पूर्णांक et8ek8_g_priv_mem(काष्ठा v4l2_subdev *subdev)
अणु
	काष्ठा et8ek8_sensor *sensor = to_et8ek8_sensor(subdev);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(subdev);
	अचिन्हित पूर्णांक length = ET8EK8_PRIV_MEM_SIZE;
	अचिन्हित पूर्णांक offset = 0;
	u8 *ptr  = sensor->priv_mem;
	पूर्णांक rval = 0;

	/* Read the EEPROM winकरोw-by-winकरोw, each winकरोw 8 bytes */
	करो अणु
		u8 buffer[PRIV_MEM_WIN_SIZE];
		काष्ठा i2c_msg msg;
		पूर्णांक bytes, i;
		पूर्णांक ofs;

		/* Set the current winकरोw */
		rval = et8ek8_i2c_ग_लिखो_reg(client, ET8EK8_REG_8BIT, 0x0001,
					    0xe0 | (offset >> 3));
		अगर (rval < 0)
			वापस rval;

		/* Wait क्रम status bit */
		क्रम (i = 0; i < 1000; ++i) अणु
			u32 status;

			rval = et8ek8_i2c_पढ़ो_reg(client, ET8EK8_REG_8BIT,
						   0x0003, &status);
			अगर (rval < 0)
				वापस rval;
			अगर (!(status & 0x08))
				अवरोध;
			usleep_range(1000, 2000);
		पूर्ण

		अगर (i == 1000)
			वापस -EIO;

		/* Read winकरोw, 8 bytes at once, and copy to user space */
		ofs = offset & 0x07;	/* Offset within this winकरोw */
		bytes = length + ofs > 8 ? 8-ofs : length;
		msg.addr = client->addr;
		msg.flags = 0;
		msg.len = 2;
		msg.buf = buffer;
		ofs += PRIV_MEM_START_REG;
		buffer[0] = (u8)(ofs >> 8);
		buffer[1] = (u8)(ofs & 0xFF);

		rval = i2c_transfer(client->adapter, &msg, 1);
		अगर (rval < 0)
			वापस rval;

		mdelay(ET8EK8_I2C_DELAY);
		msg.addr = client->addr;
		msg.len = bytes;
		msg.flags = I2C_M_RD;
		msg.buf = buffer;
		स_रखो(buffer, 0, माप(buffer));

		rval = i2c_transfer(client->adapter, &msg, 1);
		अगर (rval < 0)
			वापस rval;

		rval = 0;
		स_नकल(ptr, buffer, bytes);

		length -= bytes;
		offset += bytes;
		ptr += bytes;
	पूर्ण जबतक (length > 0);

	वापस rval;
पूर्ण

अटल पूर्णांक et8ek8_dev_init(काष्ठा v4l2_subdev *subdev)
अणु
	काष्ठा et8ek8_sensor *sensor = to_et8ek8_sensor(subdev);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(subdev);
	पूर्णांक rval, rev_l, rev_h;

	rval = et8ek8_घातer_on(sensor);
	अगर (rval) अणु
		dev_err(&client->dev, "could not power on\n");
		वापस rval;
	पूर्ण

	rval = et8ek8_i2c_पढ़ो_reg(client, ET8EK8_REG_8BIT,
				   REG_REVISION_NUMBER_L, &rev_l);
	अगर (!rval)
		rval = et8ek8_i2c_पढ़ो_reg(client, ET8EK8_REG_8BIT,
					   REG_REVISION_NUMBER_H, &rev_h);
	अगर (rval) अणु
		dev_err(&client->dev, "no et8ek8 sensor detected\n");
		जाओ out_घातeroff;
	पूर्ण

	sensor->version = (rev_h << 8) + rev_l;
	अगर (sensor->version != ET8EK8_REV_1 && sensor->version != ET8EK8_REV_2)
		dev_info(&client->dev,
			 "unknown version 0x%x detected, continuing anyway\n",
			 sensor->version);

	rval = et8ek8_reglist_import(client, &meta_reglist);
	अगर (rval) अणु
		dev_err(&client->dev,
			"invalid register list %s, import failed\n",
			ET8EK8_NAME);
		जाओ out_घातeroff;
	पूर्ण

	sensor->current_reglist = et8ek8_reglist_find_type(&meta_reglist,
							   ET8EK8_REGLIST_MODE);
	अगर (!sensor->current_reglist) अणु
		dev_err(&client->dev,
			"invalid register list %s, no mode found\n",
			ET8EK8_NAME);
		rval = -ENODEV;
		जाओ out_घातeroff;
	पूर्ण

	et8ek8_reglist_to_mbus(sensor->current_reglist, &sensor->क्रमmat);

	rval = et8ek8_i2c_reglist_find_ग_लिखो(client, &meta_reglist,
					     ET8EK8_REGLIST_POWERON);
	अगर (rval) अणु
		dev_err(&client->dev,
			"invalid register list %s, no POWERON mode found\n",
			ET8EK8_NAME);
		जाओ out_घातeroff;
	पूर्ण
	rval = et8ek8_stream_on(sensor); /* Needed to be able to पढ़ो EEPROM */
	अगर (rval)
		जाओ out_घातeroff;
	rval = et8ek8_g_priv_mem(subdev);
	अगर (rval)
		dev_warn(&client->dev,
			"can not read OTP (EEPROM) memory from sensor\n");
	rval = et8ek8_stream_off(sensor);
	अगर (rval)
		जाओ out_घातeroff;

	rval = et8ek8_घातer_off(sensor);
	अगर (rval)
		जाओ out_घातeroff;

	वापस 0;

out_घातeroff:
	et8ek8_घातer_off(sensor);

	वापस rval;
पूर्ण

/* --------------------------------------------------------------------------
 * sysfs attributes
 */
अटल sमाप_प्रकार
et8ek8_priv_mem_पढ़ो(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     अक्षर *buf)
अणु
	काष्ठा v4l2_subdev *subdev = dev_get_drvdata(dev);
	काष्ठा et8ek8_sensor *sensor = to_et8ek8_sensor(subdev);

#अगर PAGE_SIZE < ET8EK8_PRIV_MEM_SIZE
#त्रुटि PAGE_SIZE too small!
#पूर्ण_अगर

	स_नकल(buf, sensor->priv_mem, ET8EK8_PRIV_MEM_SIZE);

	वापस ET8EK8_PRIV_MEM_SIZE;
पूर्ण
अटल DEVICE_ATTR(priv_mem, 0444, et8ek8_priv_mem_पढ़ो, शून्य);

/* --------------------------------------------------------------------------
 * V4L2 subdev core operations
 */

अटल पूर्णांक
et8ek8_रेजिस्टरed(काष्ठा v4l2_subdev *subdev)
अणु
	काष्ठा et8ek8_sensor *sensor = to_et8ek8_sensor(subdev);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(subdev);
	पूर्णांक rval;

	dev_dbg(&client->dev, "registered!");

	rval = device_create_file(&client->dev, &dev_attr_priv_mem);
	अगर (rval) अणु
		dev_err(&client->dev, "could not register sysfs entry\n");
		वापस rval;
	पूर्ण

	rval = et8ek8_dev_init(subdev);
	अगर (rval)
		जाओ err_file;

	rval = et8ek8_init_controls(sensor);
	अगर (rval) अणु
		dev_err(&client->dev, "controls initialization failed\n");
		जाओ err_file;
	पूर्ण

	__et8ek8_get_pad_क्रमmat(sensor, शून्य, 0, V4L2_SUBDEV_FORMAT_ACTIVE);

	वापस 0;

err_file:
	device_हटाओ_file(&client->dev, &dev_attr_priv_mem);

	वापस rval;
पूर्ण

अटल पूर्णांक __et8ek8_set_घातer(काष्ठा et8ek8_sensor *sensor, bool on)
अणु
	वापस on ? et8ek8_घातer_on(sensor) : et8ek8_घातer_off(sensor);
पूर्ण

अटल पूर्णांक et8ek8_set_घातer(काष्ठा v4l2_subdev *subdev, पूर्णांक on)
अणु
	काष्ठा et8ek8_sensor *sensor = to_et8ek8_sensor(subdev);
	पूर्णांक ret = 0;

	mutex_lock(&sensor->घातer_lock);

	/* If the घातer count is modअगरied from 0 to != 0 or from != 0 to 0,
	 * update the घातer state.
	 */
	अगर (sensor->घातer_count == !on) अणु
		ret = __et8ek8_set_घातer(sensor, !!on);
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण

	/* Update the घातer count. */
	sensor->घातer_count += on ? 1 : -1;
	WARN_ON(sensor->घातer_count < 0);

करोne:
	mutex_unlock(&sensor->घातer_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक et8ek8_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा et8ek8_sensor *sensor = to_et8ek8_sensor(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;
	काष्ठा et8ek8_reglist *reglist;

	reglist = et8ek8_reglist_find_type(&meta_reglist, ET8EK8_REGLIST_MODE);
	क्रमmat = __et8ek8_get_pad_क्रमmat(sensor, fh->pad, 0,
					 V4L2_SUBDEV_FORMAT_TRY);
	et8ek8_reglist_to_mbus(reglist, क्रमmat);

	वापस et8ek8_set_घातer(sd, true);
पूर्ण

अटल पूर्णांक et8ek8_बंद(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	वापस et8ek8_set_घातer(sd, false);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops et8ek8_video_ops = अणु
	.s_stream = et8ek8_s_stream,
	.g_frame_पूर्णांकerval = et8ek8_get_frame_पूर्णांकerval,
	.s_frame_पूर्णांकerval = et8ek8_set_frame_पूर्णांकerval,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops et8ek8_core_ops = अणु
	.s_घातer = et8ek8_set_घातer,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops et8ek8_pad_ops = अणु
	.क्रमागत_mbus_code = et8ek8_क्रमागत_mbus_code,
	.क्रमागत_frame_size = et8ek8_क्रमागत_frame_size,
	.क्रमागत_frame_पूर्णांकerval = et8ek8_क्रमागत_frame_ival,
	.get_fmt = et8ek8_get_pad_क्रमmat,
	.set_fmt = et8ek8_set_pad_क्रमmat,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops et8ek8_ops = अणु
	.core = &et8ek8_core_ops,
	.video = &et8ek8_video_ops,
	.pad = &et8ek8_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops et8ek8_पूर्णांकernal_ops = अणु
	.रेजिस्टरed = et8ek8_रेजिस्टरed,
	.खोलो = et8ek8_खोलो,
	.बंद = et8ek8_बंद,
पूर्ण;

/* --------------------------------------------------------------------------
 * I2C driver
 */
अटल पूर्णांक __maybe_unused et8ek8_suspend(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *subdev = dev_get_drvdata(dev);
	काष्ठा et8ek8_sensor *sensor = to_et8ek8_sensor(subdev);

	अगर (!sensor->घातer_count)
		वापस 0;

	वापस __et8ek8_set_घातer(sensor, false);
पूर्ण

अटल पूर्णांक __maybe_unused et8ek8_resume(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *subdev = dev_get_drvdata(dev);
	काष्ठा et8ek8_sensor *sensor = to_et8ek8_sensor(subdev);

	अगर (!sensor->घातer_count)
		वापस 0;

	वापस __et8ek8_set_घातer(sensor, true);
पूर्ण

अटल पूर्णांक et8ek8_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा et8ek8_sensor *sensor;
	काष्ठा device *dev = &client->dev;
	पूर्णांक ret;

	sensor = devm_kzalloc(&client->dev, माप(*sensor), GFP_KERNEL);
	अगर (!sensor)
		वापस -ENOMEM;

	sensor->reset = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(sensor->reset)) अणु
		dev_dbg(&client->dev, "could not request reset gpio\n");
		वापस PTR_ERR(sensor->reset);
	पूर्ण

	sensor->vana = devm_regulator_get(dev, "vana");
	अगर (IS_ERR(sensor->vana)) अणु
		dev_err(&client->dev, "could not get regulator for vana\n");
		वापस PTR_ERR(sensor->vana);
	पूर्ण

	sensor->ext_clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(sensor->ext_clk)) अणु
		dev_err(&client->dev, "could not get clock\n");
		वापस PTR_ERR(sensor->ext_clk);
	पूर्ण

	ret = of_property_पढ़ो_u32(dev->of_node, "clock-frequency",
				   &sensor->xclk_freq);
	अगर (ret) अणु
		dev_warn(dev, "can't get clock-frequency\n");
		वापस ret;
	पूर्ण

	mutex_init(&sensor->घातer_lock);

	v4l2_i2c_subdev_init(&sensor->subdev, client, &et8ek8_ops);
	sensor->subdev.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	sensor->subdev.पूर्णांकernal_ops = &et8ek8_पूर्णांकernal_ops;

	sensor->subdev.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	sensor->pad.flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&sensor->subdev.entity, 1, &sensor->pad);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "media entity init failed!\n");
		जाओ err_mutex;
	पूर्ण

	ret = v4l2_async_रेजिस्टर_subdev_sensor(&sensor->subdev);
	अगर (ret < 0)
		जाओ err_entity;

	dev_dbg(dev, "initialized!\n");

	वापस 0;

err_entity:
	media_entity_cleanup(&sensor->subdev.entity);
err_mutex:
	mutex_destroy(&sensor->घातer_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक __निकास et8ek8_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *subdev = i2c_get_clientdata(client);
	काष्ठा et8ek8_sensor *sensor = to_et8ek8_sensor(subdev);

	अगर (sensor->घातer_count) अणु
		WARN_ON(1);
		et8ek8_घातer_off(sensor);
		sensor->घातer_count = 0;
	पूर्ण

	v4l2_device_unरेजिस्टर_subdev(&sensor->subdev);
	device_हटाओ_file(&client->dev, &dev_attr_priv_mem);
	v4l2_ctrl_handler_मुक्त(&sensor->ctrl_handler);
	v4l2_async_unरेजिस्टर_subdev(&sensor->subdev);
	media_entity_cleanup(&sensor->subdev.entity);
	mutex_destroy(&sensor->घातer_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id et8ek8_of_table[] = अणु
	अणु .compatible = "toshiba,et8ek8" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, et8ek8_of_table);

अटल स्थिर काष्ठा i2c_device_id et8ek8_id_table[] = अणु
	अणु ET8EK8_NAME, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, et8ek8_id_table);

अटल स्थिर काष्ठा dev_pm_ops et8ek8_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(et8ek8_suspend, et8ek8_resume)
पूर्ण;

अटल काष्ठा i2c_driver et8ek8_i2c_driver = अणु
	.driver		= अणु
		.name	= ET8EK8_NAME,
		.pm	= &et8ek8_pm_ops,
		.of_match_table	= et8ek8_of_table,
	पूर्ण,
	.probe_new	= et8ek8_probe,
	.हटाओ		= __निकास_p(et8ek8_हटाओ),
	.id_table	= et8ek8_id_table,
पूर्ण;

module_i2c_driver(et8ek8_i2c_driver);

MODULE_AUTHOR("Sakari Ailus <sakari.ailus@iki.fi>, Pavel Machek <pavel@ucw.cz");
MODULE_DESCRIPTION("Toshiba ET8EK8 camera sensor driver");
MODULE_LICENSE("GPL");
