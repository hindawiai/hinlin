<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2016 Synaptics Incorporated
 */
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/rmi.h>
#समावेश "rmi_driver.h"
#समावेश "rmi_2d_sensor.h"

क्रमागत rmi_f12_object_type अणु
	RMI_F12_OBJECT_NONE			= 0x00,
	RMI_F12_OBJECT_FINGER			= 0x01,
	RMI_F12_OBJECT_STYLUS			= 0x02,
	RMI_F12_OBJECT_PALM			= 0x03,
	RMI_F12_OBJECT_UNCLASSIFIED		= 0x04,
	RMI_F12_OBJECT_GLOVED_FINGER		= 0x06,
	RMI_F12_OBJECT_NARROW_OBJECT		= 0x07,
	RMI_F12_OBJECT_HAND_EDGE		= 0x08,
	RMI_F12_OBJECT_COVER			= 0x0A,
	RMI_F12_OBJECT_STYLUS_2			= 0x0B,
	RMI_F12_OBJECT_ERASER			= 0x0C,
	RMI_F12_OBJECT_SMALL_OBJECT		= 0x0D,
पूर्ण;

#घोषणा F12_DATA1_BYTES_PER_OBJ			8

काष्ठा f12_data अणु
	काष्ठा rmi_2d_sensor sensor;
	काष्ठा rmi_2d_sensor_platक्रमm_data sensor_pdata;
	bool has_dribble;

	u16 data_addr;

	काष्ठा rmi_रेजिस्टर_descriptor query_reg_desc;
	काष्ठा rmi_रेजिस्टर_descriptor control_reg_desc;
	काष्ठा rmi_रेजिस्टर_descriptor data_reg_desc;

	/* F12 Data1 describes sensed objects */
	स्थिर काष्ठा rmi_रेजिस्टर_desc_item *data1;
	u16 data1_offset;

	/* F12 Data5 describes finger ACM */
	स्थिर काष्ठा rmi_रेजिस्टर_desc_item *data5;
	u16 data5_offset;

	/* F12 Data5 describes Pen */
	स्थिर काष्ठा rmi_रेजिस्टर_desc_item *data6;
	u16 data6_offset;


	/* F12 Data9 reports relative data */
	स्थिर काष्ठा rmi_रेजिस्टर_desc_item *data9;
	u16 data9_offset;

	स्थिर काष्ठा rmi_रेजिस्टर_desc_item *data15;
	u16 data15_offset;

	अचिन्हित दीर्घ *असल_mask;
	अचिन्हित दीर्घ *rel_mask;
पूर्ण;

अटल पूर्णांक rmi_f12_पढ़ो_sensor_tuning(काष्ठा f12_data *f12)
अणु
	स्थिर काष्ठा rmi_रेजिस्टर_desc_item *item;
	काष्ठा rmi_2d_sensor *sensor = &f12->sensor;
	काष्ठा rmi_function *fn = sensor->fn;
	काष्ठा rmi_device *rmi_dev = fn->rmi_dev;
	पूर्णांक ret;
	पूर्णांक offset;
	u8 buf[15];
	पूर्णांक pitch_x = 0;
	पूर्णांक pitch_y = 0;
	पूर्णांक rx_receivers = 0;
	पूर्णांक tx_receivers = 0;

	item = rmi_get_रेजिस्टर_desc_item(&f12->control_reg_desc, 8);
	अगर (!item) अणु
		dev_err(&fn->dev,
			"F12 does not have the sensor tuning control register\n");
		वापस -ENODEV;
	पूर्ण

	offset = rmi_रेजिस्टर_desc_calc_reg_offset(&f12->control_reg_desc, 8);

	अगर (item->reg_size > माप(buf)) अणु
		dev_err(&fn->dev,
			"F12 control8 should be no bigger than %zd bytes, not: %ld\n",
			माप(buf), item->reg_size);
		वापस -ENODEV;
	पूर्ण

	ret = rmi_पढ़ो_block(rmi_dev, fn->fd.control_base_addr + offset, buf,
				item->reg_size);
	अगर (ret)
		वापस ret;

	offset = 0;
	अगर (rmi_रेजिस्टर_desc_has_subpacket(item, 0)) अणु
		sensor->max_x = (buf[offset + 1] << 8) | buf[offset];
		sensor->max_y = (buf[offset + 3] << 8) | buf[offset + 2];
		offset += 4;
	पूर्ण

	rmi_dbg(RMI_DEBUG_FN, &fn->dev, "%s: max_x: %d max_y: %d\n", __func__,
		sensor->max_x, sensor->max_y);

	अगर (rmi_रेजिस्टर_desc_has_subpacket(item, 1)) अणु
		pitch_x = (buf[offset + 1] << 8) | buf[offset];
		pitch_y	= (buf[offset + 3] << 8) | buf[offset + 2];
		offset += 4;
	पूर्ण

	अगर (rmi_रेजिस्टर_desc_has_subpacket(item, 2)) अणु
		/* Units 1/128 sensor pitch */
		rmi_dbg(RMI_DEBUG_FN, &fn->dev,
			"%s: Inactive Border xlo:%d xhi:%d ylo:%d yhi:%d\n",
			__func__,
			buf[offset], buf[offset + 1],
			buf[offset + 2], buf[offset + 3]);

		offset += 4;
	पूर्ण

	अगर (rmi_रेजिस्टर_desc_has_subpacket(item, 3)) अणु
		rx_receivers = buf[offset];
		tx_receivers = buf[offset + 1];
		offset += 2;
	पूर्ण

	/* Skip over sensor flags */
	अगर (rmi_रेजिस्टर_desc_has_subpacket(item, 4))
		offset += 1;

	sensor->x_mm = (pitch_x * rx_receivers) >> 12;
	sensor->y_mm = (pitch_y * tx_receivers) >> 12;

	rmi_dbg(RMI_DEBUG_FN, &fn->dev, "%s: x_mm: %d y_mm: %d\n", __func__,
		sensor->x_mm, sensor->y_mm);

	वापस 0;
पूर्ण

अटल व्योम rmi_f12_process_objects(काष्ठा f12_data *f12, u8 *data1, पूर्णांक size)
अणु
	पूर्णांक i;
	काष्ठा rmi_2d_sensor *sensor = &f12->sensor;
	पूर्णांक objects = f12->data1->num_subpackets;

	अगर ((f12->data1->num_subpackets * F12_DATA1_BYTES_PER_OBJ) > size)
		objects = size / F12_DATA1_BYTES_PER_OBJ;

	क्रम (i = 0; i < objects; i++) अणु
		काष्ठा rmi_2d_sensor_असल_object *obj = &sensor->objs[i];

		obj->type = RMI_2D_OBJECT_NONE;
		obj->mt_tool = MT_TOOL_FINGER;

		चयन (data1[0]) अणु
		हाल RMI_F12_OBJECT_FINGER:
			obj->type = RMI_2D_OBJECT_FINGER;
			अवरोध;
		हाल RMI_F12_OBJECT_STYLUS:
			obj->type = RMI_2D_OBJECT_STYLUS;
			obj->mt_tool = MT_TOOL_PEN;
			अवरोध;
		हाल RMI_F12_OBJECT_PALM:
			obj->type = RMI_2D_OBJECT_PALM;
			obj->mt_tool = MT_TOOL_PALM;
			अवरोध;
		हाल RMI_F12_OBJECT_UNCLASSIFIED:
			obj->type = RMI_2D_OBJECT_UNCLASSIFIED;
			अवरोध;
		पूर्ण

		obj->x = (data1[2] << 8) | data1[1];
		obj->y = (data1[4] << 8) | data1[3];
		obj->z = data1[5];
		obj->wx = data1[6];
		obj->wy = data1[7];

		rmi_2d_sensor_असल_process(sensor, obj, i);

		data1 += F12_DATA1_BYTES_PER_OBJ;
	पूर्ण

	अगर (sensor->kernel_tracking)
		input_mt_assign_slots(sensor->input,
				      sensor->tracking_slots,
				      sensor->tracking_pos,
				      sensor->nbr_fingers,
				      sensor->dmax);

	क्रम (i = 0; i < objects; i++)
		rmi_2d_sensor_असल_report(sensor, &sensor->objs[i], i);
पूर्ण

अटल irqवापस_t rmi_f12_attention(पूर्णांक irq, व्योम *ctx)
अणु
	पूर्णांक retval;
	काष्ठा rmi_function *fn = ctx;
	काष्ठा rmi_device *rmi_dev = fn->rmi_dev;
	काष्ठा rmi_driver_data *drvdata = dev_get_drvdata(&rmi_dev->dev);
	काष्ठा f12_data *f12 = dev_get_drvdata(&fn->dev);
	काष्ठा rmi_2d_sensor *sensor = &f12->sensor;
	पूर्णांक valid_bytes = sensor->pkt_size;

	अगर (drvdata->attn_data.data) अणु
		अगर (sensor->attn_size > drvdata->attn_data.size)
			valid_bytes = drvdata->attn_data.size;
		अन्यथा
			valid_bytes = sensor->attn_size;
		स_नकल(sensor->data_pkt, drvdata->attn_data.data,
			valid_bytes);
		drvdata->attn_data.data += valid_bytes;
		drvdata->attn_data.size -= valid_bytes;
	पूर्ण अन्यथा अणु
		retval = rmi_पढ़ो_block(rmi_dev, f12->data_addr,
					sensor->data_pkt, sensor->pkt_size);
		अगर (retval < 0) अणु
			dev_err(&fn->dev, "Failed to read object data. Code: %d.\n",
				retval);
			वापस IRQ_RETVAL(retval);
		पूर्ण
	पूर्ण

	अगर (f12->data1)
		rmi_f12_process_objects(f12,
			&sensor->data_pkt[f12->data1_offset], valid_bytes);

	input_mt_sync_frame(sensor->input);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rmi_f12_ग_लिखो_control_regs(काष्ठा rmi_function *fn)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा rmi_रेजिस्टर_desc_item *item;
	काष्ठा rmi_device *rmi_dev = fn->rmi_dev;
	काष्ठा f12_data *f12 = dev_get_drvdata(&fn->dev);
	पूर्णांक control_size;
	अक्षर buf[3];
	u16 control_offset = 0;
	u8 subpacket_offset = 0;

	अगर (f12->has_dribble
	    && (f12->sensor.dribble != RMI_REG_STATE_DEFAULT)) अणु
		item = rmi_get_रेजिस्टर_desc_item(&f12->control_reg_desc, 20);
		अगर (item) अणु
			control_offset = rmi_रेजिस्टर_desc_calc_reg_offset(
						&f12->control_reg_desc, 20);

			/*
			 * The byte containing the EnableDribble bit will be
			 * in either byte 0 or byte 2 of control 20. Depending
			 * on the existence of subpacket 0. If control 20 is
			 * larger then 3 bytes, just पढ़ो the first 3.
			 */
			control_size = min(item->reg_size, 3UL);

			ret = rmi_पढ़ो_block(rmi_dev, fn->fd.control_base_addr
					+ control_offset, buf, control_size);
			अगर (ret)
				वापस ret;

			अगर (rmi_रेजिस्टर_desc_has_subpacket(item, 0))
				subpacket_offset += 1;

			चयन (f12->sensor.dribble) अणु
			हाल RMI_REG_STATE_OFF:
				buf[subpacket_offset] &= ~BIT(2);
				अवरोध;
			हाल RMI_REG_STATE_ON:
				buf[subpacket_offset] |= BIT(2);
				अवरोध;
			हाल RMI_REG_STATE_DEFAULT:
			शेष:
				अवरोध;
			पूर्ण

			ret = rmi_ग_लिखो_block(rmi_dev,
				fn->fd.control_base_addr + control_offset,
				buf, control_size);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक rmi_f12_config(काष्ठा rmi_function *fn)
अणु
	काष्ठा rmi_driver *drv = fn->rmi_dev->driver;
	काष्ठा f12_data *f12 = dev_get_drvdata(&fn->dev);
	काष्ठा rmi_2d_sensor *sensor;
	पूर्णांक ret;

	sensor = &f12->sensor;

	अगर (!sensor->report_असल)
		drv->clear_irq_bits(fn->rmi_dev, f12->असल_mask);
	अन्यथा
		drv->set_irq_bits(fn->rmi_dev, f12->असल_mask);

	drv->clear_irq_bits(fn->rmi_dev, f12->rel_mask);

	ret = rmi_f12_ग_लिखो_control_regs(fn);
	अगर (ret)
		dev_warn(&fn->dev,
			"Failed to write F12 control registers: %d\n", ret);

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f12_probe(काष्ठा rmi_function *fn)
अणु
	काष्ठा f12_data *f12;
	पूर्णांक ret;
	काष्ठा rmi_device *rmi_dev = fn->rmi_dev;
	अक्षर buf;
	u16 query_addr = fn->fd.query_base_addr;
	स्थिर काष्ठा rmi_रेजिस्टर_desc_item *item;
	काष्ठा rmi_2d_sensor *sensor;
	काष्ठा rmi_device_platक्रमm_data *pdata = rmi_get_platक्रमm_data(rmi_dev);
	काष्ठा rmi_driver_data *drvdata = dev_get_drvdata(&rmi_dev->dev);
	u16 data_offset = 0;
	पूर्णांक mask_size;

	rmi_dbg(RMI_DEBUG_FN, &fn->dev, "%s\n", __func__);

	mask_size = BITS_TO_LONGS(drvdata->irq_count) * माप(अचिन्हित दीर्घ);

	ret = rmi_पढ़ो(fn->rmi_dev, query_addr, &buf);
	अगर (ret < 0) अणु
		dev_err(&fn->dev, "Failed to read general info register: %d\n",
			ret);
		वापस -ENODEV;
	पूर्ण
	++query_addr;

	अगर (!(buf & BIT(0))) अणु
		dev_err(&fn->dev,
			"Behavior of F12 without register descriptors is undefined.\n");
		वापस -ENODEV;
	पूर्ण

	f12 = devm_kzalloc(&fn->dev, माप(काष्ठा f12_data) + mask_size * 2,
			GFP_KERNEL);
	अगर (!f12)
		वापस -ENOMEM;

	f12->असल_mask = (अचिन्हित दीर्घ *)((अक्षर *)f12
			+ माप(काष्ठा f12_data));
	f12->rel_mask = (अचिन्हित दीर्घ *)((अक्षर *)f12
			+ माप(काष्ठा f12_data) + mask_size);

	set_bit(fn->irq_pos, f12->असल_mask);
	set_bit(fn->irq_pos + 1, f12->rel_mask);

	f12->has_dribble = !!(buf & BIT(3));

	अगर (fn->dev.of_node) अणु
		ret = rmi_2d_sensor_of_probe(&fn->dev, &f12->sensor_pdata);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		f12->sensor_pdata = pdata->sensor_pdata;
	पूर्ण

	ret = rmi_पढ़ो_रेजिस्टर_desc(rmi_dev, query_addr,
					&f12->query_reg_desc);
	अगर (ret) अणु
		dev_err(&fn->dev,
			"Failed to read the Query Register Descriptor: %d\n",
			ret);
		वापस ret;
	पूर्ण
	query_addr += 3;

	ret = rmi_पढ़ो_रेजिस्टर_desc(rmi_dev, query_addr,
						&f12->control_reg_desc);
	अगर (ret) अणु
		dev_err(&fn->dev,
			"Failed to read the Control Register Descriptor: %d\n",
			ret);
		वापस ret;
	पूर्ण
	query_addr += 3;

	ret = rmi_पढ़ो_रेजिस्टर_desc(rmi_dev, query_addr,
						&f12->data_reg_desc);
	अगर (ret) अणु
		dev_err(&fn->dev,
			"Failed to read the Data Register Descriptor: %d\n",
			ret);
		वापस ret;
	पूर्ण
	query_addr += 3;

	sensor = &f12->sensor;
	sensor->fn = fn;
	f12->data_addr = fn->fd.data_base_addr;
	sensor->pkt_size = rmi_रेजिस्टर_desc_calc_size(&f12->data_reg_desc);

	sensor->axis_align =
		f12->sensor_pdata.axis_align;

	sensor->x_mm = f12->sensor_pdata.x_mm;
	sensor->y_mm = f12->sensor_pdata.y_mm;
	sensor->dribble = f12->sensor_pdata.dribble;

	अगर (sensor->sensor_type == rmi_sensor_शेष)
		sensor->sensor_type =
			f12->sensor_pdata.sensor_type;

	rmi_dbg(RMI_DEBUG_FN, &fn->dev, "%s: data packet size: %d\n", __func__,
		sensor->pkt_size);
	sensor->data_pkt = devm_kzalloc(&fn->dev, sensor->pkt_size, GFP_KERNEL);
	अगर (!sensor->data_pkt)
		वापस -ENOMEM;

	dev_set_drvdata(&fn->dev, f12);

	ret = rmi_f12_पढ़ो_sensor_tuning(f12);
	अगर (ret)
		वापस ret;

	/*
	 * Figure out what data is contained in the data रेजिस्टरs. HID devices
	 * may have रेजिस्टरs defined, but their data is not reported in the
	 * HID attention report. Registers which are not reported in the HID
	 * attention report check to see अगर the device is receiving data from
	 * HID attention reports.
	 */
	item = rmi_get_रेजिस्टर_desc_item(&f12->data_reg_desc, 0);
	अगर (item && !drvdata->attn_data.data)
		data_offset += item->reg_size;

	item = rmi_get_रेजिस्टर_desc_item(&f12->data_reg_desc, 1);
	अगर (item) अणु
		f12->data1 = item;
		f12->data1_offset = data_offset;
		data_offset += item->reg_size;
		sensor->nbr_fingers = item->num_subpackets;
		sensor->report_असल = 1;
		sensor->attn_size += item->reg_size;
	पूर्ण

	item = rmi_get_रेजिस्टर_desc_item(&f12->data_reg_desc, 2);
	अगर (item && !drvdata->attn_data.data)
		data_offset += item->reg_size;

	item = rmi_get_रेजिस्टर_desc_item(&f12->data_reg_desc, 3);
	अगर (item && !drvdata->attn_data.data)
		data_offset += item->reg_size;

	item = rmi_get_रेजिस्टर_desc_item(&f12->data_reg_desc, 4);
	अगर (item && !drvdata->attn_data.data)
		data_offset += item->reg_size;

	item = rmi_get_रेजिस्टर_desc_item(&f12->data_reg_desc, 5);
	अगर (item) अणु
		f12->data5 = item;
		f12->data5_offset = data_offset;
		data_offset += item->reg_size;
		sensor->attn_size += item->reg_size;
	पूर्ण

	item = rmi_get_रेजिस्टर_desc_item(&f12->data_reg_desc, 6);
	अगर (item && !drvdata->attn_data.data) अणु
		f12->data6 = item;
		f12->data6_offset = data_offset;
		data_offset += item->reg_size;
	पूर्ण

	item = rmi_get_रेजिस्टर_desc_item(&f12->data_reg_desc, 7);
	अगर (item && !drvdata->attn_data.data)
		data_offset += item->reg_size;

	item = rmi_get_रेजिस्टर_desc_item(&f12->data_reg_desc, 8);
	अगर (item && !drvdata->attn_data.data)
		data_offset += item->reg_size;

	item = rmi_get_रेजिस्टर_desc_item(&f12->data_reg_desc, 9);
	अगर (item && !drvdata->attn_data.data) अणु
		f12->data9 = item;
		f12->data9_offset = data_offset;
		data_offset += item->reg_size;
		अगर (!sensor->report_असल)
			sensor->report_rel = 1;
	पूर्ण

	item = rmi_get_रेजिस्टर_desc_item(&f12->data_reg_desc, 10);
	अगर (item && !drvdata->attn_data.data)
		data_offset += item->reg_size;

	item = rmi_get_रेजिस्टर_desc_item(&f12->data_reg_desc, 11);
	अगर (item && !drvdata->attn_data.data)
		data_offset += item->reg_size;

	item = rmi_get_रेजिस्टर_desc_item(&f12->data_reg_desc, 12);
	अगर (item && !drvdata->attn_data.data)
		data_offset += item->reg_size;

	item = rmi_get_रेजिस्टर_desc_item(&f12->data_reg_desc, 13);
	अगर (item && !drvdata->attn_data.data)
		data_offset += item->reg_size;

	item = rmi_get_रेजिस्टर_desc_item(&f12->data_reg_desc, 14);
	अगर (item && !drvdata->attn_data.data)
		data_offset += item->reg_size;

	item = rmi_get_रेजिस्टर_desc_item(&f12->data_reg_desc, 15);
	अगर (item && !drvdata->attn_data.data) अणु
		f12->data15 = item;
		f12->data15_offset = data_offset;
		data_offset += item->reg_size;
	पूर्ण

	/* allocate the in-kernel tracking buffers */
	sensor->tracking_pos = devm_kसुस्मृति(&fn->dev,
			sensor->nbr_fingers, माप(काष्ठा input_mt_pos),
			GFP_KERNEL);
	sensor->tracking_slots = devm_kसुस्मृति(&fn->dev,
			sensor->nbr_fingers, माप(पूर्णांक), GFP_KERNEL);
	sensor->objs = devm_kसुस्मृति(&fn->dev,
			sensor->nbr_fingers,
			माप(काष्ठा rmi_2d_sensor_असल_object),
			GFP_KERNEL);
	अगर (!sensor->tracking_pos || !sensor->tracking_slots || !sensor->objs)
		वापस -ENOMEM;

	ret = rmi_2d_sensor_configure_input(fn, sensor);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

काष्ठा rmi_function_handler rmi_f12_handler = अणु
	.driver = अणु
		.name = "rmi4_f12",
	पूर्ण,
	.func = 0x12,
	.probe = rmi_f12_probe,
	.config = rmi_f12_config,
	.attention = rmi_f12_attention,
पूर्ण;
