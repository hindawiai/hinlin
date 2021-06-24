<शैली गुरु>
/*
 * Wacom W8001 penabled serial touchscreen driver
 *
 * Copyright (c) 2008 Jaya Kumar
 * Copyright (c) 2010 Red Hat, Inc.
 * Copyright (c) 2010 - 2011 Ping Cheng, Wacom. <pingc@wacom.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 *
 * Layout based on Elo serial touchscreen driver by Vojtech Pavlik
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/serपन.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/delay.h>

#घोषणा DRIVER_DESC	"Wacom W8001 serial touchscreen driver"

MODULE_AUTHOR("Jaya Kumar <jayakumar.lkml@gmail.com>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

#घोषणा W8001_MAX_PHYS		42

#घोषणा W8001_MAX_LENGTH	13
#घोषणा W8001_LEAD_MASK		0x80
#घोषणा W8001_LEAD_BYTE		0x80
#घोषणा W8001_TAB_MASK		0x40
#घोषणा W8001_TAB_BYTE		0x40
/* set in first byte of touch data packets */
#घोषणा W8001_TOUCH_MASK	(0x10 | W8001_LEAD_MASK)
#घोषणा W8001_TOUCH_BYTE	(0x10 | W8001_LEAD_BYTE)

#घोषणा W8001_QUERY_PACKET	0x20

#घोषणा W8001_CMD_STOP		'0'
#घोषणा W8001_CMD_START		'1'
#घोषणा W8001_CMD_QUERY		'*'
#घोषणा W8001_CMD_TOUCHQUERY	'%'

/* length of data packets in bytes, depends on device. */
#घोषणा W8001_PKTLEN_TOUCH93	5
#घोषणा W8001_PKTLEN_TOUCH9A	7
#घोषणा W8001_PKTLEN_TPCPEN	9
#घोषणा W8001_PKTLEN_TPCCTL	11	/* control packet */
#घोषणा W8001_PKTLEN_TOUCH2FG	13

/* resolution in poपूर्णांकs/mm */
#घोषणा W8001_PEN_RESOLUTION    100
#घोषणा W8001_TOUCH_RESOLUTION  10

काष्ठा w8001_coord अणु
	u8 rdy;
	u8 tsw;
	u8 f1;
	u8 f2;
	u16 x;
	u16 y;
	u16 pen_pressure;
	u8 tilt_x;
	u8 tilt_y;
पूर्ण;

/* touch query reply packet */
काष्ठा w8001_touch_query अणु
	u16 x;
	u16 y;
	u8 panel_res;
	u8 capacity_res;
	u8 sensor_id;
पूर्ण;

/*
 * Per-touchscreen data.
 */

काष्ठा w8001 अणु
	काष्ठा input_dev *pen_dev;
	काष्ठा input_dev *touch_dev;
	काष्ठा serio *serio;
	काष्ठा completion cmd_करोne;
	पूर्णांक id;
	पूर्णांक idx;
	अचिन्हित अक्षर response_type;
	अचिन्हित अक्षर response[W8001_MAX_LENGTH];
	अचिन्हित अक्षर data[W8001_MAX_LENGTH];
	अक्षर phys[W8001_MAX_PHYS];
	पूर्णांक type;
	अचिन्हित पूर्णांक pktlen;
	u16 max_touch_x;
	u16 max_touch_y;
	u16 max_pen_x;
	u16 max_pen_y;
	अक्षर pen_name[64];
	अक्षर touch_name[64];
	पूर्णांक खोलो_count;
	काष्ठा mutex mutex;
पूर्ण;

अटल व्योम parse_pen_data(u8 *data, काष्ठा w8001_coord *coord)
अणु
	स_रखो(coord, 0, माप(*coord));

	coord->rdy = data[0] & 0x20;
	coord->tsw = data[0] & 0x01;
	coord->f1 = data[0] & 0x02;
	coord->f2 = data[0] & 0x04;

	coord->x = (data[1] & 0x7F) << 9;
	coord->x |= (data[2] & 0x7F) << 2;
	coord->x |= (data[6] & 0x60) >> 5;

	coord->y = (data[3] & 0x7F) << 9;
	coord->y |= (data[4] & 0x7F) << 2;
	coord->y |= (data[6] & 0x18) >> 3;

	coord->pen_pressure = data[5] & 0x7F;
	coord->pen_pressure |= (data[6] & 0x07) << 7 ;

	coord->tilt_x = data[7] & 0x7F;
	coord->tilt_y = data[8] & 0x7F;
पूर्ण

अटल व्योम parse_single_touch(u8 *data, काष्ठा w8001_coord *coord)
अणु
	coord->x = (data[1] << 7) | data[2];
	coord->y = (data[3] << 7) | data[4];
	coord->tsw = data[0] & 0x01;
पूर्ण

अटल व्योम scale_touch_coordinates(काष्ठा w8001 *w8001,
				    अचिन्हित पूर्णांक *x, अचिन्हित पूर्णांक *y)
अणु
	अगर (w8001->max_pen_x && w8001->max_touch_x)
		*x = *x * w8001->max_pen_x / w8001->max_touch_x;

	अगर (w8001->max_pen_y && w8001->max_touch_y)
		*y = *y * w8001->max_pen_y / w8001->max_touch_y;
पूर्ण

अटल व्योम parse_multi_touch(काष्ठा w8001 *w8001)
अणु
	काष्ठा input_dev *dev = w8001->touch_dev;
	अचिन्हित अक्षर *data = w8001->data;
	अचिन्हित पूर्णांक x, y;
	पूर्णांक i;
	पूर्णांक count = 0;

	क्रम (i = 0; i < 2; i++) अणु
		bool touch = data[0] & (1 << i);

		input_mt_slot(dev, i);
		input_mt_report_slot_state(dev, MT_TOOL_FINGER, touch);
		अगर (touch) अणु
			x = (data[6 * i + 1] << 7) | data[6 * i + 2];
			y = (data[6 * i + 3] << 7) | data[6 * i + 4];
			/* data[5,6] and [11,12] is finger capacity */

			/* scale to pen maximum */
			scale_touch_coordinates(w8001, &x, &y);

			input_report_असल(dev, ABS_MT_POSITION_X, x);
			input_report_असल(dev, ABS_MT_POSITION_Y, y);
			count++;
		पूर्ण
	पूर्ण

	/* emulate single touch events when stylus is out of proximity.
	 * This is to make single touch backward support consistent
	 * across all Wacom single touch devices.
	 */
	अगर (w8001->type != BTN_TOOL_PEN &&
			    w8001->type != BTN_TOOL_RUBBER) अणु
		w8001->type = count == 1 ? BTN_TOOL_FINGER : KEY_RESERVED;
		input_mt_report_poपूर्णांकer_emulation(dev, true);
	पूर्ण

	input_sync(dev);
पूर्ण

अटल व्योम parse_touchquery(u8 *data, काष्ठा w8001_touch_query *query)
अणु
	स_रखो(query, 0, माप(*query));

	query->panel_res = data[1];
	query->sensor_id = data[2] & 0x7;
	query->capacity_res = data[7];

	query->x = data[3] << 9;
	query->x |= data[4] << 2;
	query->x |= (data[2] >> 5) & 0x3;

	query->y = data[5] << 9;
	query->y |= data[6] << 2;
	query->y |= (data[2] >> 3) & 0x3;

	/* Early days' single-finger touch models need the following शेषs */
	अगर (!query->x && !query->y) अणु
		query->x = 1024;
		query->y = 1024;
		अगर (query->panel_res)
			query->x = query->y = (1 << query->panel_res);
		query->panel_res = W8001_TOUCH_RESOLUTION;
	पूर्ण
पूर्ण

अटल व्योम report_pen_events(काष्ठा w8001 *w8001, काष्ठा w8001_coord *coord)
अणु
	काष्ठा input_dev *dev = w8001->pen_dev;

	/*
	 * We have 1 bit क्रम proximity (rdy) and 3 bits क्रम tip, side,
	 * side2/eraser. If rdy && f2 are set, this can be either pen + side2,
	 * or eraser. Assume:
	 * - अगर dev is alपढ़ोy in proximity and f2 is toggled ै pen + side2
	 * - अगर dev comes पूर्णांकo proximity with f2 set ै eraser
	 * If f2 disappears after assuming eraser, fake proximity out क्रम
	 * eraser and in क्रम pen.
	 */

	चयन (w8001->type) अणु
	हाल BTN_TOOL_RUBBER:
		अगर (!coord->f2) अणु
			input_report_असल(dev, ABS_PRESSURE, 0);
			input_report_key(dev, BTN_TOUCH, 0);
			input_report_key(dev, BTN_STYLUS, 0);
			input_report_key(dev, BTN_STYLUS2, 0);
			input_report_key(dev, BTN_TOOL_RUBBER, 0);
			input_sync(dev);
			w8001->type = BTN_TOOL_PEN;
		पूर्ण
		अवरोध;

	हाल BTN_TOOL_FINGER:
	हाल KEY_RESERVED:
		w8001->type = coord->f2 ? BTN_TOOL_RUBBER : BTN_TOOL_PEN;
		अवरोध;

	शेष:
		input_report_key(dev, BTN_STYLUS2, coord->f2);
		अवरोध;
	पूर्ण

	input_report_असल(dev, ABS_X, coord->x);
	input_report_असल(dev, ABS_Y, coord->y);
	input_report_असल(dev, ABS_PRESSURE, coord->pen_pressure);
	input_report_key(dev, BTN_TOUCH, coord->tsw);
	input_report_key(dev, BTN_STYLUS, coord->f1);
	input_report_key(dev, w8001->type, coord->rdy);
	input_sync(dev);

	अगर (!coord->rdy)
		w8001->type = KEY_RESERVED;
पूर्ण

अटल व्योम report_single_touch(काष्ठा w8001 *w8001, काष्ठा w8001_coord *coord)
अणु
	काष्ठा input_dev *dev = w8001->touch_dev;
	अचिन्हित पूर्णांक x = coord->x;
	अचिन्हित पूर्णांक y = coord->y;

	/* scale to pen maximum */
	scale_touch_coordinates(w8001, &x, &y);

	input_report_असल(dev, ABS_X, x);
	input_report_असल(dev, ABS_Y, y);
	input_report_key(dev, BTN_TOUCH, coord->tsw);

	input_sync(dev);

	w8001->type = coord->tsw ? BTN_TOOL_FINGER : KEY_RESERVED;
पूर्ण

अटल irqवापस_t w8001_पूर्णांकerrupt(काष्ठा serio *serio,
				   अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा w8001 *w8001 = serio_get_drvdata(serio);
	काष्ठा w8001_coord coord;
	अचिन्हित अक्षर पंचांगp;

	w8001->data[w8001->idx] = data;
	चयन (w8001->idx++) अणु
	हाल 0:
		अगर ((data & W8001_LEAD_MASK) != W8001_LEAD_BYTE) अणु
			pr_debug("w8001: unsynchronized data: 0x%02x\n", data);
			w8001->idx = 0;
		पूर्ण
		अवरोध;

	हाल W8001_PKTLEN_TOUCH93 - 1:
	हाल W8001_PKTLEN_TOUCH9A - 1:
		पंचांगp = w8001->data[0] & W8001_TOUCH_BYTE;
		अगर (पंचांगp != W8001_TOUCH_BYTE)
			अवरोध;

		अगर (w8001->pktlen == w8001->idx) अणु
			w8001->idx = 0;
			अगर (w8001->type != BTN_TOOL_PEN &&
			    w8001->type != BTN_TOOL_RUBBER) अणु
				parse_single_touch(w8001->data, &coord);
				report_single_touch(w8001, &coord);
			पूर्ण
		पूर्ण
		अवरोध;

	/* Pen coordinates packet */
	हाल W8001_PKTLEN_TPCPEN - 1:
		पंचांगp = w8001->data[0] & W8001_TAB_MASK;
		अगर (unlikely(पंचांगp == W8001_TAB_BYTE))
			अवरोध;

		पंचांगp = w8001->data[0] & W8001_TOUCH_BYTE;
		अगर (पंचांगp == W8001_TOUCH_BYTE)
			अवरोध;

		w8001->idx = 0;
		parse_pen_data(w8001->data, &coord);
		report_pen_events(w8001, &coord);
		अवरोध;

	/* control packet */
	हाल W8001_PKTLEN_TPCCTL - 1:
		पंचांगp = w8001->data[0] & W8001_TOUCH_MASK;
		अगर (पंचांगp == W8001_TOUCH_BYTE)
			अवरोध;

		w8001->idx = 0;
		स_नकल(w8001->response, w8001->data, W8001_MAX_LENGTH);
		w8001->response_type = W8001_QUERY_PACKET;
		complete(&w8001->cmd_करोne);
		अवरोध;

	/* 2 finger touch packet */
	हाल W8001_PKTLEN_TOUCH2FG - 1:
		w8001->idx = 0;
		parse_multi_touch(w8001);
		अवरोध;

	शेष:
		/*
		 * ThinkPad X60 Tablet PC (pen only device) someबार
		 * sends invalid data packets that are larger than
		 * W8001_PKTLEN_TPCPEN. Let's start over again.
		 */
		अगर (!w8001->touch_dev && w8001->idx > W8001_PKTLEN_TPCPEN - 1)
			w8001->idx = 0;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक w8001_command(काष्ठा w8001 *w8001, अचिन्हित अक्षर command,
			 bool रुको_response)
अणु
	पूर्णांक rc;

	w8001->response_type = 0;
	init_completion(&w8001->cmd_करोne);

	rc = serio_ग_लिखो(w8001->serio, command);
	अगर (rc == 0 && रुको_response) अणु

		रुको_क्रम_completion_समयout(&w8001->cmd_करोne, HZ);
		अगर (w8001->response_type != W8001_QUERY_PACKET)
			rc = -EIO;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक w8001_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा w8001 *w8001 = input_get_drvdata(dev);
	पूर्णांक err;

	err = mutex_lock_पूर्णांकerruptible(&w8001->mutex);
	अगर (err)
		वापस err;

	अगर (w8001->खोलो_count++ == 0) अणु
		err = w8001_command(w8001, W8001_CMD_START, false);
		अगर (err)
			w8001->खोलो_count--;
	पूर्ण

	mutex_unlock(&w8001->mutex);
	वापस err;
पूर्ण

अटल व्योम w8001_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा w8001 *w8001 = input_get_drvdata(dev);

	mutex_lock(&w8001->mutex);

	अगर (--w8001->खोलो_count == 0)
		w8001_command(w8001, W8001_CMD_STOP, false);

	mutex_unlock(&w8001->mutex);
पूर्ण

अटल पूर्णांक w8001_detect(काष्ठा w8001 *w8001)
अणु
	पूर्णांक error;

	error = w8001_command(w8001, W8001_CMD_STOP, false);
	अगर (error)
		वापस error;

	msleep(250);	/* रुको 250ms beक्रमe querying the device */

	वापस 0;
पूर्ण

अटल पूर्णांक w8001_setup_pen(काष्ठा w8001 *w8001, अक्षर *basename,
			   माप_प्रकार basename_sz)
अणु
	काष्ठा input_dev *dev = w8001->pen_dev;
	काष्ठा w8001_coord coord;
	पूर्णांक error;

	/* penabled? */
	error = w8001_command(w8001, W8001_CMD_QUERY, true);
	अगर (error)
		वापस error;

	__set_bit(EV_KEY, dev->evbit);
	__set_bit(EV_ABS, dev->evbit);
	__set_bit(BTN_TOUCH, dev->keybit);
	__set_bit(BTN_TOOL_PEN, dev->keybit);
	__set_bit(BTN_TOOL_RUBBER, dev->keybit);
	__set_bit(BTN_STYLUS, dev->keybit);
	__set_bit(BTN_STYLUS2, dev->keybit);
	__set_bit(INPUT_PROP_सूचीECT, dev->propbit);

	parse_pen_data(w8001->response, &coord);
	w8001->max_pen_x = coord.x;
	w8001->max_pen_y = coord.y;

	input_set_असल_params(dev, ABS_X, 0, coord.x, 0, 0);
	input_set_असल_params(dev, ABS_Y, 0, coord.y, 0, 0);
	input_असल_set_res(dev, ABS_X, W8001_PEN_RESOLUTION);
	input_असल_set_res(dev, ABS_Y, W8001_PEN_RESOLUTION);
	input_set_असल_params(dev, ABS_PRESSURE, 0, coord.pen_pressure, 0, 0);
	अगर (coord.tilt_x && coord.tilt_y) अणु
		input_set_असल_params(dev, ABS_TILT_X, 0, coord.tilt_x, 0, 0);
		input_set_असल_params(dev, ABS_TILT_Y, 0, coord.tilt_y, 0, 0);
	पूर्ण

	w8001->id = 0x90;
	strlcat(basename, " Penabled", basename_sz);

	वापस 0;
पूर्ण

अटल पूर्णांक w8001_setup_touch(काष्ठा w8001 *w8001, अक्षर *basename,
			     माप_प्रकार basename_sz)
अणु
	काष्ठा input_dev *dev = w8001->touch_dev;
	काष्ठा w8001_touch_query touch;
	पूर्णांक error;


	/* Touch enabled? */
	error = w8001_command(w8001, W8001_CMD_TOUCHQUERY, true);
	अगर (error)
		वापस error;
	/*
	 * Some non-touch devices may reply to the touch query. But their
	 * second byte is empty, which indicates touch is not supported.
	 */
	अगर (!w8001->response[1])
		वापस -ENXIO;

	__set_bit(EV_KEY, dev->evbit);
	__set_bit(EV_ABS, dev->evbit);
	__set_bit(BTN_TOUCH, dev->keybit);
	__set_bit(INPUT_PROP_सूचीECT, dev->propbit);

	parse_touchquery(w8001->response, &touch);
	w8001->max_touch_x = touch.x;
	w8001->max_touch_y = touch.y;

	अगर (w8001->max_pen_x && w8001->max_pen_y) अणु
		/* अगर pen is supported scale to pen maximum */
		touch.x = w8001->max_pen_x;
		touch.y = w8001->max_pen_y;
		touch.panel_res = W8001_PEN_RESOLUTION;
	पूर्ण

	input_set_असल_params(dev, ABS_X, 0, touch.x, 0, 0);
	input_set_असल_params(dev, ABS_Y, 0, touch.y, 0, 0);
	input_असल_set_res(dev, ABS_X, touch.panel_res);
	input_असल_set_res(dev, ABS_Y, touch.panel_res);

	चयन (touch.sensor_id) अणु
	हाल 0:
	हाल 2:
		w8001->pktlen = W8001_PKTLEN_TOUCH93;
		w8001->id = 0x93;
		strlcat(basename, " 1FG", basename_sz);
		अवरोध;

	हाल 1:
	हाल 3:
	हाल 4:
		w8001->pktlen = W8001_PKTLEN_TOUCH9A;
		strlcat(basename, " 1FG", basename_sz);
		w8001->id = 0x9a;
		अवरोध;

	हाल 5:
		w8001->pktlen = W8001_PKTLEN_TOUCH2FG;

		__set_bit(BTN_TOOL_DOUBLETAP, dev->keybit);
		error = input_mt_init_slots(dev, 2, 0);
		अगर (error) अणु
			dev_err(&w8001->serio->dev,
				"failed to initialize MT slots: %d\n", error);
			वापस error;
		पूर्ण

		input_set_असल_params(dev, ABS_MT_POSITION_X,
					0, touch.x, 0, 0);
		input_set_असल_params(dev, ABS_MT_POSITION_Y,
					0, touch.y, 0, 0);
		input_set_असल_params(dev, ABS_MT_TOOL_TYPE,
					0, MT_TOOL_MAX, 0, 0);
		input_असल_set_res(dev, ABS_MT_POSITION_X, touch.panel_res);
		input_असल_set_res(dev, ABS_MT_POSITION_Y, touch.panel_res);

		strlcat(basename, " 2FG", basename_sz);
		अगर (w8001->max_pen_x && w8001->max_pen_y)
			w8001->id = 0xE3;
		अन्यथा
			w8001->id = 0xE2;
		अवरोध;
	पूर्ण

	strlcat(basename, " Touchscreen", basename_sz);

	वापस 0;
पूर्ण

अटल व्योम w8001_set_devdata(काष्ठा input_dev *dev, काष्ठा w8001 *w8001,
			      काष्ठा serio *serio)
अणु
	dev->phys = w8001->phys;
	dev->id.bustype = BUS_RS232;
	dev->id.product = w8001->id;
	dev->id.venकरोr = 0x056a;
	dev->id.version = 0x0100;
	dev->खोलो = w8001_खोलो;
	dev->बंद = w8001_बंद;

	dev->dev.parent = &serio->dev;

	input_set_drvdata(dev, w8001);
पूर्ण

/*
 * w8001_disconnect() is the opposite of w8001_connect()
 */

अटल व्योम w8001_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा w8001 *w8001 = serio_get_drvdata(serio);

	serio_बंद(serio);

	अगर (w8001->pen_dev)
		input_unरेजिस्टर_device(w8001->pen_dev);
	अगर (w8001->touch_dev)
		input_unरेजिस्टर_device(w8001->touch_dev);
	kमुक्त(w8001);

	serio_set_drvdata(serio, शून्य);
पूर्ण

/*
 * w8001_connect() is the routine that is called when someone adds a
 * new serio device that supports the w8001 protocol and रेजिस्टरs it as
 * an input device.
 */

अटल पूर्णांक w8001_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा w8001 *w8001;
	काष्ठा input_dev *input_dev_pen;
	काष्ठा input_dev *input_dev_touch;
	अक्षर basename[64];
	पूर्णांक err, err_pen, err_touch;

	w8001 = kzalloc(माप(काष्ठा w8001), GFP_KERNEL);
	input_dev_pen = input_allocate_device();
	input_dev_touch = input_allocate_device();
	अगर (!w8001 || !input_dev_pen || !input_dev_touch) अणु
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण

	w8001->serio = serio;
	w8001->pen_dev = input_dev_pen;
	w8001->touch_dev = input_dev_touch;
	mutex_init(&w8001->mutex);
	init_completion(&w8001->cmd_करोne);
	snम_लिखो(w8001->phys, माप(w8001->phys), "%s/input0", serio->phys);

	serio_set_drvdata(serio, w8001);
	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	err = w8001_detect(w8001);
	अगर (err)
		जाओ fail3;

	/* For backwards-compatibility we compose the basename based on
	 * capabilities and then just append the tool type
	 */
	strlcpy(basename, "Wacom Serial", माप(basename));

	err_pen = w8001_setup_pen(w8001, basename, माप(basename));
	err_touch = w8001_setup_touch(w8001, basename, माप(basename));
	अगर (err_pen && err_touch) अणु
		err = -ENXIO;
		जाओ fail3;
	पूर्ण

	अगर (!err_pen) अणु
		strlcpy(w8001->pen_name, basename, माप(w8001->pen_name));
		strlcat(w8001->pen_name, " Pen", माप(w8001->pen_name));
		input_dev_pen->name = w8001->pen_name;

		w8001_set_devdata(input_dev_pen, w8001, serio);

		err = input_रेजिस्टर_device(w8001->pen_dev);
		अगर (err)
			जाओ fail3;
	पूर्ण अन्यथा अणु
		input_मुक्त_device(input_dev_pen);
		input_dev_pen = शून्य;
		w8001->pen_dev = शून्य;
	पूर्ण

	अगर (!err_touch) अणु
		strlcpy(w8001->touch_name, basename, माप(w8001->touch_name));
		strlcat(w8001->touch_name, " Finger",
			माप(w8001->touch_name));
		input_dev_touch->name = w8001->touch_name;

		w8001_set_devdata(input_dev_touch, w8001, serio);

		err = input_रेजिस्टर_device(w8001->touch_dev);
		अगर (err)
			जाओ fail4;
	पूर्ण अन्यथा अणु
		input_मुक्त_device(input_dev_touch);
		input_dev_touch = शून्य;
		w8001->touch_dev = शून्य;
	पूर्ण

	वापस 0;

fail4:
	अगर (w8001->pen_dev)
		input_unरेजिस्टर_device(w8001->pen_dev);
fail3:
	serio_बंद(serio);
fail2:
	serio_set_drvdata(serio, शून्य);
fail1:
	input_मुक्त_device(input_dev_pen);
	input_मुक्त_device(input_dev_touch);
	kमुक्त(w8001);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा serio_device_id w8001_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_W8001,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, w8001_serio_ids);

अटल काष्ठा serio_driver w8001_drv = अणु
	.driver		= अणु
		.name	= "w8001",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= w8001_serio_ids,
	.पूर्णांकerrupt	= w8001_पूर्णांकerrupt,
	.connect	= w8001_connect,
	.disconnect	= w8001_disconnect,
पूर्ण;

module_serio_driver(w8001_drv);
