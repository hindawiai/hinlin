<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2014, Samsung Electronics Co. Ltd. All Rights Reserved.
 */

#समावेश "ssp.h"

#घोषणा SSP_DEV (&data->spi->dev)
#घोषणा SSP_GET_MESSAGE_TYPE(data) (data & (3 << SSP_RW))

/*
 * SSP -> AP Inकाष्ठाion
 * They tell what packet type can be expected. In the future there will
 * be less of them. BYPASS means common sensor packets with accel, gyro,
 * hrm etc. data. LIBRARY and META are mock-up's क्रम now.
 */
#घोषणा SSP_MSG2AP_INST_BYPASS_DATA		0x37
#घोषणा SSP_MSG2AP_INST_LIBRARY_DATA		0x01
#घोषणा SSP_MSG2AP_INST_DEBUG_DATA		0x03
#घोषणा SSP_MSG2AP_INST_BIG_DATA		0x04
#घोषणा SSP_MSG2AP_INST_META_DATA		0x05
#घोषणा SSP_MSG2AP_INST_TIME_SYNC		0x06
#घोषणा SSP_MSG2AP_INST_RESET			0x07

#घोषणा SSP_UNIMPLEMENTED -1

काष्ठा ssp_msg_header अणु
	u8 cmd;
	__le16 length;
	__le16 options;
	__le32 data;
पूर्ण __attribute__((__packed__));

काष्ठा ssp_msg अणु
	u16 length;
	u16 options;
	काष्ठा list_head list;
	काष्ठा completion *करोne;
	काष्ठा ssp_msg_header *h;
	अक्षर *buffer;
पूर्ण;

अटल स्थिर पूर्णांक ssp_offset_map[SSP_SENSOR_MAX] = अणु
	[SSP_ACCELEROMETER_SENSOR] =		SSP_ACCELEROMETER_SIZE +
						SSP_TIME_SIZE,
	[SSP_GYROSCOPE_SENSOR] =		SSP_GYROSCOPE_SIZE +
						SSP_TIME_SIZE,
	[SSP_GEOMAGNETIC_UNCALIB_SENSOR] =	SSP_UNIMPLEMENTED,
	[SSP_GEOMAGNETIC_RAW] =			SSP_UNIMPLEMENTED,
	[SSP_GEOMAGNETIC_SENSOR] =		SSP_UNIMPLEMENTED,
	[SSP_PRESSURE_SENSOR] =			SSP_UNIMPLEMENTED,
	[SSP_GESTURE_SENSOR] =			SSP_UNIMPLEMENTED,
	[SSP_PROXIMITY_SENSOR] =		SSP_UNIMPLEMENTED,
	[SSP_TEMPERATURE_HUMIDITY_SENSOR] =	SSP_UNIMPLEMENTED,
	[SSP_LIGHT_SENSOR] =			SSP_UNIMPLEMENTED,
	[SSP_PROXIMITY_RAW] =			SSP_UNIMPLEMENTED,
	[SSP_ORIENTATION_SENSOR] =		SSP_UNIMPLEMENTED,
	[SSP_STEP_DETECTOR] =			SSP_UNIMPLEMENTED,
	[SSP_SIG_MOTION_SENSOR] =		SSP_UNIMPLEMENTED,
	[SSP_GYRO_UNCALIB_SENSOR] =		SSP_UNIMPLEMENTED,
	[SSP_GAME_ROTATION_VECTOR] =		SSP_UNIMPLEMENTED,
	[SSP_ROTATION_VECTOR] =			SSP_UNIMPLEMENTED,
	[SSP_STEP_COUNTER] =			SSP_UNIMPLEMENTED,
	[SSP_BIO_HRM_RAW] =			SSP_BIO_HRM_RAW_SIZE +
						SSP_TIME_SIZE,
	[SSP_BIO_HRM_RAW_FAC] =			SSP_BIO_HRM_RAW_FAC_SIZE +
						SSP_TIME_SIZE,
	[SSP_BIO_HRM_LIB] =			SSP_BIO_HRM_LIB_SIZE +
						SSP_TIME_SIZE,
पूर्ण;

#घोषणा SSP_HEADER_SIZE		(माप(काष्ठा ssp_msg_header))
#घोषणा SSP_HEADER_SIZE_ALIGNED	(ALIGN(SSP_HEADER_SIZE, 4))

अटल काष्ठा ssp_msg *ssp_create_msg(u8 cmd, u16 len, u16 opt, u32 data)
अणु
	काष्ठा ssp_msg_header h;
	काष्ठा ssp_msg *msg;

	msg = kzalloc(माप(*msg), GFP_KERNEL);
	अगर (!msg)
		वापस शून्य;

	h.cmd = cmd;
	h.length = cpu_to_le16(len);
	h.options = cpu_to_le16(opt);
	h.data = cpu_to_le32(data);

	msg->buffer = kzalloc(SSP_HEADER_SIZE_ALIGNED + len,
			      GFP_KERNEL | GFP_DMA);
	अगर (!msg->buffer) अणु
		kमुक्त(msg);
		वापस शून्य;
	पूर्ण

	msg->length = len;
	msg->options = opt;

	स_नकल(msg->buffer, &h, SSP_HEADER_SIZE);

	वापस msg;
पूर्ण

/*
 * It is a bit heavy to करो it this way but often the function is used to compose
 * the message from smaller chunks which are placed on the stack.  Often the
 * chunks are small so स_नकल should be optimalized.
 */
अटल अंतरभूत व्योम ssp_fill_buffer(काष्ठा ssp_msg *m, अचिन्हित पूर्णांक offset,
				   स्थिर व्योम *src, अचिन्हित पूर्णांक len)
अणु
	स_नकल(&m->buffer[SSP_HEADER_SIZE_ALIGNED + offset], src, len);
पूर्ण

अटल अंतरभूत व्योम ssp_get_buffer(काष्ठा ssp_msg *m, अचिन्हित पूर्णांक offset,
				  व्योम *dest, अचिन्हित पूर्णांक len)
अणु
	स_नकल(dest, &m->buffer[SSP_HEADER_SIZE_ALIGNED + offset],  len);
पूर्ण

#घोषणा SSP_GET_BUFFER_AT_INDEX(m, index) \
	(m->buffer[SSP_HEADER_SIZE_ALIGNED + index])
#घोषणा SSP_SET_BUFFER_AT_INDEX(m, index, val) \
	(m->buffer[SSP_HEADER_SIZE_ALIGNED + index] = val)

अटल व्योम ssp_clean_msg(काष्ठा ssp_msg *m)
अणु
	kमुक्त(m->buffer);
	kमुक्त(m);
पूर्ण

अटल पूर्णांक ssp_prपूर्णांक_mcu_debug(अक्षर *data_frame, पूर्णांक *data_index,
			       पूर्णांक received_len)
अणु
	पूर्णांक length = data_frame[(*data_index)++];

	अगर (length > received_len - *data_index || length <= 0) अणु
		ssp_dbg("[SSP]: MSG From MCU-invalid debug length(%d/%d)\n",
			length, received_len);
		वापस length ? length : -EPROTO;
	पूर्ण

	ssp_dbg("[SSP]: MSG From MCU - %s\n", &data_frame[*data_index]);

	*data_index += length;

	वापस 0;
पूर्ण

/*
 * It was deचिन्हित that way - additional lines to some kind of handshake,
 * please करो not ask why - only the firmware guy can know it.
 */
अटल पूर्णांक ssp_check_lines(काष्ठा ssp_data *data, bool state)
अणु
	पूर्णांक delay_cnt = 0;

	gpiod_set_value_cansleep(data->ap_mcu_gpiod, state);

	जबतक (gpiod_get_value_cansleep(data->mcu_ap_gpiod) != state) अणु
		usleep_range(3000, 3500);

		अगर (data->shut_करोwn || delay_cnt++ > 500) अणु
			dev_err(SSP_DEV, "%s:timeout, hw ack wait fail %d\n",
				__func__, state);

			अगर (!state)
				gpiod_set_value_cansleep(data->ap_mcu_gpiod, 1);

			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ssp_करो_transfer(काष्ठा ssp_data *data, काष्ठा ssp_msg *msg,
			   काष्ठा completion *करोne, पूर्णांक समयout)
अणु
	पूर्णांक status;
	/*
	 * check अगर this is a लघु one way message or the whole transfer has
	 * second part after an पूर्णांकerrupt
	 */
	स्थिर bool use_no_irq = msg->length == 0;

	अगर (data->shut_करोwn)
		वापस -EPERM;

	msg->करोne = करोne;

	mutex_lock(&data->comm_lock);

	status = ssp_check_lines(data, false);
	अगर (status < 0)
		जाओ _error_locked;

	status = spi_ग_लिखो(data->spi, msg->buffer, SSP_HEADER_SIZE);
	अगर (status < 0) अणु
		gpiod_set_value_cansleep(data->ap_mcu_gpiod, 1);
		dev_err(SSP_DEV, "%s spi_write fail\n", __func__);
		जाओ _error_locked;
	पूर्ण

	अगर (!use_no_irq) अणु
		mutex_lock(&data->pending_lock);
		list_add_tail(&msg->list, &data->pending_list);
		mutex_unlock(&data->pending_lock);
	पूर्ण

	status = ssp_check_lines(data, true);
	अगर (status < 0) अणु
		अगर (!use_no_irq) अणु
			mutex_lock(&data->pending_lock);
			list_del(&msg->list);
			mutex_unlock(&data->pending_lock);
		पूर्ण
		जाओ _error_locked;
	पूर्ण

	mutex_unlock(&data->comm_lock);

	अगर (!use_no_irq && करोne)
		अगर (रुको_क्रम_completion_समयout(करोne,
						msecs_to_jअगरfies(समयout)) ==
		    0) अणु
			mutex_lock(&data->pending_lock);
			list_del(&msg->list);
			mutex_unlock(&data->pending_lock);

			data->समयout_cnt++;
			वापस -ETIMEDOUT;
		पूर्ण

	वापस 0;

_error_locked:
	mutex_unlock(&data->comm_lock);
	data->समयout_cnt++;
	वापस status;
पूर्ण

अटल अंतरभूत पूर्णांक ssp_spi_sync_command(काष्ठा ssp_data *data,
				       काष्ठा ssp_msg *msg)
अणु
	वापस ssp_करो_transfer(data, msg, शून्य, 0);
पूर्ण

अटल पूर्णांक ssp_spi_sync(काष्ठा ssp_data *data, काष्ठा ssp_msg *msg,
			पूर्णांक समयout)
अणु
	DECLARE_COMPLETION_ONSTACK(करोne);

	अगर (WARN_ON(!msg->length))
		वापस -EPERM;

	वापस ssp_करो_transfer(data, msg, &करोne, समयout);
पूर्ण

अटल पूर्णांक ssp_handle_big_data(काष्ठा ssp_data *data, अक्षर *dataframe, पूर्णांक *idx)
अणु
	/* mock-up, it will be changed with adding another sensor types */
	*idx += 8;
	वापस 0;
पूर्ण

अटल पूर्णांक ssp_parse_dataframe(काष्ठा ssp_data *data, अक्षर *dataframe, पूर्णांक len)
अणु
	पूर्णांक idx, sd;
	काष्ठा ssp_sensor_data *spd;
	काष्ठा iio_dev **indio_devs = data->sensor_devs;

	क्रम (idx = 0; idx < len;) अणु
		चयन (dataframe[idx++]) अणु
		हाल SSP_MSG2AP_INST_BYPASS_DATA:
			sd = dataframe[idx++];
			अगर (sd < 0 || sd >= SSP_SENSOR_MAX) अणु
				dev_err(SSP_DEV,
					"Mcu data frame1 error %d\n", sd);
				वापस -EPROTO;
			पूर्ण

			अगर (indio_devs[sd]) अणु
				spd = iio_priv(indio_devs[sd]);
				अगर (spd->process_data)
					spd->process_data(indio_devs[sd],
							  &dataframe[idx],
							  data->बारtamp);
			पूर्ण अन्यथा अणु
				dev_err(SSP_DEV, "no client for frame\n");
			पूर्ण

			idx += ssp_offset_map[sd];
			अवरोध;
		हाल SSP_MSG2AP_INST_DEBUG_DATA:
			sd = ssp_prपूर्णांक_mcu_debug(dataframe, &idx, len);
			अगर (sd) अणु
				dev_err(SSP_DEV,
					"Mcu data frame3 error %d\n", sd);
				वापस sd;
			पूर्ण
			अवरोध;
		हाल SSP_MSG2AP_INST_LIBRARY_DATA:
			idx += len;
			अवरोध;
		हाल SSP_MSG2AP_INST_BIG_DATA:
			ssp_handle_big_data(data, dataframe, &idx);
			अवरोध;
		हाल SSP_MSG2AP_INST_TIME_SYNC:
			data->समय_syncing = true;
			अवरोध;
		हाल SSP_MSG2AP_INST_RESET:
			ssp_queue_ssp_refresh_task(data, 0);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (data->समय_syncing)
		data->बारtamp = kसमय_get_real_ns();

	वापस 0;
पूर्ण

/* thपढ़ोed irq */
पूर्णांक ssp_irq_msg(काष्ठा ssp_data *data)
अणु
	bool found = false;
	अक्षर *buffer;
	u8 msg_type;
	पूर्णांक ret;
	u16 length, msg_options;
	काष्ठा ssp_msg *msg, *n;

	ret = spi_पढ़ो(data->spi, data->header_buffer, SSP_HEADER_BUFFER_SIZE);
	अगर (ret < 0) अणु
		dev_err(SSP_DEV, "header read fail\n");
		वापस ret;
	पूर्ण

	length = le16_to_cpu(data->header_buffer[1]);
	msg_options = le16_to_cpu(data->header_buffer[0]);

	अगर (length == 0) अणु
		dev_err(SSP_DEV, "length received from mcu is 0\n");
		वापस -EINVAL;
	पूर्ण

	msg_type = SSP_GET_MESSAGE_TYPE(msg_options);

	चयन (msg_type) अणु
	हाल SSP_AP2HUB_READ:
	हाल SSP_AP2HUB_WRITE:
		/*
		 * this is a small list, a few elements - the packets can be
		 * received with no order
		 */
		mutex_lock(&data->pending_lock);
		list_क्रम_each_entry_safe(msg, n, &data->pending_list, list) अणु
			अगर (msg->options == msg_options) अणु
				list_del(&msg->list);
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!found) अणु
			/*
			 * here can be implemented dead messages handling
			 * but the slave should not send such ones - it is to
			 * check but let's handle this
			 */
			buffer = kदो_स्मृति(length, GFP_KERNEL | GFP_DMA);
			अगर (!buffer) अणु
				ret = -ENOMEM;
				जाओ _unlock;
			पूर्ण

			/* got dead packet so it is always an error */
			ret = spi_पढ़ो(data->spi, buffer, length);
			अगर (ret >= 0)
				ret = -EPROTO;

			kमुक्त(buffer);

			dev_err(SSP_DEV, "No match error %x\n",
				msg_options);

			जाओ _unlock;
		पूर्ण

		अगर (msg_type == SSP_AP2HUB_READ)
			ret = spi_पढ़ो(data->spi,
				       &msg->buffer[SSP_HEADER_SIZE_ALIGNED],
				       msg->length);

		अगर (msg_type == SSP_AP2HUB_WRITE) अणु
			ret = spi_ग_लिखो(data->spi,
					&msg->buffer[SSP_HEADER_SIZE_ALIGNED],
					msg->length);
			अगर (msg_options & SSP_AP2HUB_RETURN) अणु
				msg->options =
					SSP_AP2HUB_READ | SSP_AP2HUB_RETURN;
				msg->length = 1;

				list_add_tail(&msg->list, &data->pending_list);
				जाओ _unlock;
			पूर्ण
		पूर्ण

		अगर (msg->करोne)
			अगर (!completion_करोne(msg->करोne))
				complete(msg->करोne);
_unlock:
		mutex_unlock(&data->pending_lock);
		अवरोध;
	हाल SSP_HUB2AP_WRITE:
		buffer = kzalloc(length, GFP_KERNEL | GFP_DMA);
		अगर (!buffer)
			वापस -ENOMEM;

		ret = spi_पढ़ो(data->spi, buffer, length);
		अगर (ret < 0) अणु
			dev_err(SSP_DEV, "spi read fail\n");
			kमुक्त(buffer);
			अवरोध;
		पूर्ण

		ret = ssp_parse_dataframe(data, buffer, length);

		kमुक्त(buffer);
		अवरोध;

	शेष:
		dev_err(SSP_DEV, "unknown msg type\n");
		वापस -EPROTO;
	पूर्ण

	वापस ret;
पूर्ण

व्योम ssp_clean_pending_list(काष्ठा ssp_data *data)
अणु
	काष्ठा ssp_msg *msg, *n;

	mutex_lock(&data->pending_lock);
	list_क्रम_each_entry_safe(msg, n, &data->pending_list, list) अणु
		list_del(&msg->list);

		अगर (msg->करोne)
			अगर (!completion_करोne(msg->करोne))
				complete(msg->करोne);
	पूर्ण
	mutex_unlock(&data->pending_lock);
पूर्ण

पूर्णांक ssp_command(काष्ठा ssp_data *data, अक्षर command, पूर्णांक arg)
अणु
	पूर्णांक ret;
	काष्ठा ssp_msg *msg;

	msg = ssp_create_msg(command, 0, SSP_AP2HUB_WRITE, arg);
	अगर (!msg)
		वापस -ENOMEM;

	ssp_dbg("%s - command 0x%x %d\n", __func__, command, arg);

	ret = ssp_spi_sync_command(data, msg);
	ssp_clean_msg(msg);

	वापस ret;
पूर्ण

पूर्णांक ssp_send_inकाष्ठाion(काष्ठा ssp_data *data, u8 inst, u8 sensor_type,
			 u8 *send_buf, u8 length)
अणु
	पूर्णांक ret;
	काष्ठा ssp_msg *msg;

	अगर (data->fw_dl_state == SSP_FW_DL_STATE_DOWNLOADING) अणु
		dev_err(SSP_DEV, "%s - Skip Inst! DL state = %d\n",
			__func__, data->fw_dl_state);
		वापस -EBUSY;
	पूर्ण अन्यथा अगर (!(data->available_sensors & BIT(sensor_type)) &&
		   (inst <= SSP_MSG2SSP_INST_CHANGE_DELAY)) अणु
		dev_err(SSP_DEV, "%s - Bypass Inst Skip! - %u\n",
			__func__, sensor_type);
		वापस -EIO; /* just fail */
	पूर्ण

	msg = ssp_create_msg(inst, length + 2, SSP_AP2HUB_WRITE, 0);
	अगर (!msg)
		वापस -ENOMEM;

	ssp_fill_buffer(msg, 0, &sensor_type, 1);
	ssp_fill_buffer(msg, 1, send_buf, length);

	ssp_dbg("%s - Inst = 0x%x, Sensor Type = 0x%x, data = %u\n",
		__func__, inst, sensor_type, send_buf[1]);

	ret = ssp_spi_sync(data, msg, 1000);
	ssp_clean_msg(msg);

	वापस ret;
पूर्ण

पूर्णांक ssp_get_chipid(काष्ठा ssp_data *data)
अणु
	पूर्णांक ret;
	अक्षर buffer;
	काष्ठा ssp_msg *msg;

	msg = ssp_create_msg(SSP_MSG2SSP_AP_WHOAMI, 1, SSP_AP2HUB_READ, 0);
	अगर (!msg)
		वापस -ENOMEM;

	ret = ssp_spi_sync(data, msg, 1000);

	buffer = SSP_GET_BUFFER_AT_INDEX(msg, 0);

	ssp_clean_msg(msg);

	वापस ret < 0 ? ret : buffer;
पूर्ण

पूर्णांक ssp_set_magnetic_matrix(काष्ठा ssp_data *data)
अणु
	पूर्णांक ret;
	काष्ठा ssp_msg *msg;

	msg = ssp_create_msg(SSP_MSG2SSP_AP_SET_MAGNETIC_STATIC_MATRIX,
			     data->sensorhub_info->mag_length, SSP_AP2HUB_WRITE,
			     0);
	अगर (!msg)
		वापस -ENOMEM;

	ssp_fill_buffer(msg, 0, data->sensorhub_info->mag_table,
			data->sensorhub_info->mag_length);

	ret = ssp_spi_sync(data, msg, 1000);
	ssp_clean_msg(msg);

	वापस ret;
पूर्ण

अचिन्हित पूर्णांक ssp_get_sensor_scanning_info(काष्ठा ssp_data *data)
अणु
	पूर्णांक ret;
	__le32 result;
	u32 cpu_result = 0;

	काष्ठा ssp_msg *msg = ssp_create_msg(SSP_MSG2SSP_AP_SENSOR_SCANNING, 4,
					     SSP_AP2HUB_READ, 0);
	अगर (!msg)
		वापस 0;

	ret = ssp_spi_sync(data, msg, 1000);
	अगर (ret < 0) अणु
		dev_err(SSP_DEV, "%s - spi read fail %d\n", __func__, ret);
		जाओ _निकास;
	पूर्ण

	ssp_get_buffer(msg, 0, &result, 4);
	cpu_result = le32_to_cpu(result);

	dev_info(SSP_DEV, "%s state: 0x%08x\n", __func__, cpu_result);

_निकास:
	ssp_clean_msg(msg);
	वापस cpu_result;
पूर्ण

अचिन्हित पूर्णांक ssp_get_firmware_rev(काष्ठा ssp_data *data)
अणु
	पूर्णांक ret;
	__le32 result;

	काष्ठा ssp_msg *msg = ssp_create_msg(SSP_MSG2SSP_AP_FIRMWARE_REV, 4,
					     SSP_AP2HUB_READ, 0);
	अगर (!msg)
		वापस SSP_INVALID_REVISION;

	ret = ssp_spi_sync(data, msg, 1000);
	अगर (ret < 0) अणु
		dev_err(SSP_DEV, "%s - transfer fail %d\n", __func__, ret);
		ret = SSP_INVALID_REVISION;
		जाओ _निकास;
	पूर्ण

	ssp_get_buffer(msg, 0, &result, 4);
	ret = le32_to_cpu(result);

_निकास:
	ssp_clean_msg(msg);
	वापस ret;
पूर्ण
