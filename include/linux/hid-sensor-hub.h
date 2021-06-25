<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * HID Sensors Driver
 * Copyright (c) 2012, Intel Corporation.
 */
#अगर_अघोषित _HID_SENSORS_HUB_H
#घोषणा _HID_SENSORS_HUB_H

#समावेश <linux/hid.h>
#समावेश <linux/hid-sensor-ids.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/trigger.h>

/**
 * काष्ठा hid_sensor_hub_attribute_info - Attribute info
 * @usage_id:		Parent usage id of a physical device.
 * @attrib_id:		Attribute id क्रम this attribute.
 * @report_id:		Report id in which this inक्रमmation resides.
 * @index:		Field index in the report.
 * @units:		Measurment unit क्रम this attribute.
 * @unit_expo:		Exponent used in the data.
 * @size:		Size in bytes क्रम data size.
 * @logical_minimum:	Logical minimum value क्रम this attribute.
 * @logical_maximum:	Logical maximum value क्रम this attribute.
 */
काष्ठा hid_sensor_hub_attribute_info अणु
	u32 usage_id;
	u32 attrib_id;
	s32 report_id;
	s32 index;
	s32 units;
	s32 unit_expo;
	s32 size;
	s32 logical_minimum;
	s32 logical_maximum;
पूर्ण;

/**
 * काष्ठा sensor_hub_pending - Synchronous पढ़ो pending inक्रमmation
 * @status:		Pending status true/false.
 * @पढ़ोy:		Completion synchronization data.
 * @usage_id:		Usage id क्रम physical device, E.g. Gyro usage id.
 * @attr_usage_id:	Usage Id of a field, E.g. X-AXIS क्रम a gyro.
 * @raw_size:		Response size क्रम a पढ़ो request.
 * @raw_data:		Place holder क्रम received response.
 */
काष्ठा sensor_hub_pending अणु
	bool status;
	काष्ठा completion पढ़ोy;
	u32 usage_id;
	u32 attr_usage_id;
	पूर्णांक raw_size;
	u8  *raw_data;
पूर्ण;

/**
 * काष्ठा hid_sensor_hub_device - Stores the hub instance data
 * @hdev:		Stores the hid instance.
 * @venकरोr_id:		Venकरोr id of hub device.
 * @product_id:		Product id of hub device.
 * @usage:		Usage id क्रम this hub device instance.
 * @start_collection_index: Starting index क्रम a phy type collection
 * @end_collection_index: Last index क्रम a phy type collection
 * @mutex_ptr:		synchronizing mutex poपूर्णांकer.
 * @pending:		Holds inक्रमmation of pending sync पढ़ो request.
 */
काष्ठा hid_sensor_hub_device अणु
	काष्ठा hid_device *hdev;
	u32 venकरोr_id;
	u32 product_id;
	u32 usage;
	पूर्णांक start_collection_index;
	पूर्णांक end_collection_index;
	काष्ठा mutex *mutex_ptr;
	काष्ठा sensor_hub_pending pending;
पूर्ण;

/**
 * काष्ठा hid_sensor_hub_callbacks - Client callback functions
 * @pdev:		Platक्रमm device instance of the client driver.
 * @suspend:		Suspend callback.
 * @resume:		Resume callback.
 * @capture_sample:	Callback to get a sample.
 * @send_event:		Send notअगरication to indicate all samples are
 *			captured, process and send event
 */
काष्ठा hid_sensor_hub_callbacks अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक (*suspend)(काष्ठा hid_sensor_hub_device *hsdev, व्योम *priv);
	पूर्णांक (*resume)(काष्ठा hid_sensor_hub_device *hsdev, व्योम *priv);
	पूर्णांक (*capture_sample)(काष्ठा hid_sensor_hub_device *hsdev,
			u32 usage_id, माप_प्रकार raw_len, अक्षर *raw_data,
			व्योम *priv);
	पूर्णांक (*send_event)(काष्ठा hid_sensor_hub_device *hsdev, u32 usage_id,
			 व्योम *priv);
पूर्ण;

/**
* sensor_hub_device_खोलो() - Open hub device
* @hsdev:	Hub device instance.
*
* Used to खोलो hid device क्रम sensor hub.
*/
पूर्णांक sensor_hub_device_खोलो(काष्ठा hid_sensor_hub_device *hsdev);

/**
* sensor_hub_device_clode() - Close hub device
* @hsdev:	Hub device instance.
*
* Used to clode hid device क्रम sensor hub.
*/
व्योम sensor_hub_device_बंद(काष्ठा hid_sensor_hub_device *hsdev);

/* Registration functions */

/**
* sensor_hub_रेजिस्टर_callback() - Register client callbacks
* @hsdev:	Hub device instance.
* @usage_id:	Usage id of the client (E.g. 0x200076 क्रम Gyro).
* @usage_callback: Callback function storage
*
* Used to रेजिस्टर callbacks by client processing drivers. Sensor
* hub core driver will call these callbacks to offload processing
* of data streams and notअगरications.
*/
पूर्णांक sensor_hub_रेजिस्टर_callback(काष्ठा hid_sensor_hub_device *hsdev,
			u32 usage_id,
			काष्ठा hid_sensor_hub_callbacks *usage_callback);

/**
* sensor_hub_हटाओ_callback() - Remove client callbacks
* @hsdev:	Hub device instance.
* @usage_id:	Usage id of the client (E.g. 0x200076 क्रम Gyro).
*
* If there is a callback registred, this call will हटाओ that
* callbacks, so that it will stop data and event notअगरications.
*/
पूर्णांक sensor_hub_हटाओ_callback(काष्ठा hid_sensor_hub_device *hsdev,
			u32 usage_id);


/* Hid sensor hub core पूर्णांकerfaces */

/**
* sensor_hub_input_get_attribute_info() - Get an attribute inक्रमmation
* @hsdev:	Hub device instance.
* @type:	Type of this attribute, input/output/feature
* @usage_id:	Attribute usage id of parent physical device as per spec
* @attr_usage_id:	Attribute usage id as per spec
* @info:	वापस inक्रमmation about attribute after parsing report
*
* Parses report and वापसs the attribute inक्रमmation such as report id,
* field index, units and exponent etc.
*/
पूर्णांक sensor_hub_input_get_attribute_info(काष्ठा hid_sensor_hub_device *hsdev,
			u8 type,
			u32 usage_id, u32 attr_usage_id,
			काष्ठा hid_sensor_hub_attribute_info *info);

/**
* sensor_hub_input_attr_get_raw_value() - Synchronous पढ़ो request
* @hsdev:	Hub device instance.
* @usage_id:	Attribute usage id of parent physical device as per spec
* @attr_usage_id:	Attribute usage id as per spec
* @report_id:	Report id to look क्रम
* @flag:      Synchronous or asynchronous पढ़ो
* @is_चिन्हित:   If true then fields < 32 bits will be sign-extended
*
* Issues a synchronous or asynchronous पढ़ो request क्रम an input attribute.
* Return: data up to 32 bits.
*/

क्रमागत sensor_hub_पढ़ो_flags अणु
	SENSOR_HUB_SYNC,
	SENSOR_HUB_ASYNC,
पूर्ण;

पूर्णांक sensor_hub_input_attr_get_raw_value(काष्ठा hid_sensor_hub_device *hsdev,
 					u32 usage_id,
 					u32 attr_usage_id, u32 report_id,
					क्रमागत sensor_hub_पढ़ो_flags flag,
					bool is_चिन्हित
);

/**
* sensor_hub_set_feature() - Feature set request
* @hsdev:	Hub device instance.
* @report_id:	Report id to look क्रम
* @field_index:	Field index inside a report
* @buffer_size: size of the buffer
* @buffer:	buffer to use in the feature set
*
* Used to set a field in feature report. For example this can set polling
* पूर्णांकerval, sensitivity, activate/deactivate state.
*/
पूर्णांक sensor_hub_set_feature(काष्ठा hid_sensor_hub_device *hsdev, u32 report_id,
			   u32 field_index, पूर्णांक buffer_size, व्योम *buffer);

/**
* sensor_hub_get_feature() - Feature get request
* @hsdev:	Hub device instance.
* @report_id:	Report id to look क्रम
* @field_index:	Field index inside a report
* @buffer_size:	size of the buffer
* @buffer:	buffer to copy output
*
* Used to get a field in feature report. For example this can get polling
* पूर्णांकerval, sensitivity, activate/deactivate state.
* Return: On success, it वापसs the number of bytes copied to buffer.
* On failure, it वापसs value < 0.
*/
पूर्णांक sensor_hub_get_feature(काष्ठा hid_sensor_hub_device *hsdev, u32 report_id,
			   u32 field_index, पूर्णांक buffer_size, व्योम *buffer);

/* hid-sensor-attributes */

/* Common hid sensor iio काष्ठाure */
काष्ठा hid_sensor_common अणु
	काष्ठा hid_sensor_hub_device *hsdev;
	काष्ठा platक्रमm_device *pdev;
	अचिन्हित usage_id;
	atomic_t data_पढ़ोy;
	atomic_t user_requested_state;
	atomic_t runसमय_pm_enable;
	पूर्णांक poll_पूर्णांकerval;
	पूर्णांक raw_hystersis;
	पूर्णांक latency_ms;
	काष्ठा iio_trigger *trigger;
	पूर्णांक बारtamp_ns_scale;
	काष्ठा hid_sensor_hub_attribute_info poll;
	काष्ठा hid_sensor_hub_attribute_info report_state;
	काष्ठा hid_sensor_hub_attribute_info घातer_state;
	काष्ठा hid_sensor_hub_attribute_info sensitivity;
	काष्ठा hid_sensor_hub_attribute_info sensitivity_rel;
	काष्ठा hid_sensor_hub_attribute_info report_latency;
	काष्ठा work_काष्ठा work;
पूर्ण;

/* Convert from hid unit expo to regular exponent */
अटल अंतरभूत पूर्णांक hid_sensor_convert_exponent(पूर्णांक unit_expo)
अणु
	अगर (unit_expo < 0x08)
		वापस unit_expo;
	अन्यथा अगर (unit_expo <= 0x0f)
		वापस -(0x0f-unit_expo+1);
	अन्यथा
		वापस 0;
पूर्ण

पूर्णांक hid_sensor_parse_common_attributes(काष्ठा hid_sensor_hub_device *hsdev,
					u32 usage_id,
					काष्ठा hid_sensor_common *st,
					स्थिर u32 *sensitivity_addresses,
					u32 sensitivity_addresses_len);
पूर्णांक hid_sensor_ग_लिखो_raw_hyst_value(काष्ठा hid_sensor_common *st,
					पूर्णांक val1, पूर्णांक val2);
पूर्णांक hid_sensor_ग_लिखो_raw_hyst_rel_value(काष्ठा hid_sensor_common *st, पूर्णांक val1,
					पूर्णांक val2);
पूर्णांक hid_sensor_पढ़ो_raw_hyst_value(काष्ठा hid_sensor_common *st,
					पूर्णांक *val1, पूर्णांक *val2);
पूर्णांक hid_sensor_पढ़ो_raw_hyst_rel_value(काष्ठा hid_sensor_common *st,
				       पूर्णांक *val1, पूर्णांक *val2);
पूर्णांक hid_sensor_ग_लिखो_samp_freq_value(काष्ठा hid_sensor_common *st,
					पूर्णांक val1, पूर्णांक val2);
पूर्णांक hid_sensor_पढ़ो_samp_freq_value(काष्ठा hid_sensor_common *st,
					पूर्णांक *val1, पूर्णांक *val2);

पूर्णांक hid_sensor_get_usage_index(काष्ठा hid_sensor_hub_device *hsdev,
				u32 report_id, पूर्णांक field_index, u32 usage_id);

पूर्णांक hid_sensor_क्रमmat_scale(u32 usage_id,
			    काष्ठा hid_sensor_hub_attribute_info *attr_info,
			    पूर्णांक *val0, पूर्णांक *val1);

s32 hid_sensor_पढ़ो_poll_value(काष्ठा hid_sensor_common *st);

पूर्णांक64_t hid_sensor_convert_बारtamp(काष्ठा hid_sensor_common *st,
				     पूर्णांक64_t raw_value);
bool hid_sensor_batch_mode_supported(काष्ठा hid_sensor_common *st);
पूर्णांक hid_sensor_set_report_latency(काष्ठा hid_sensor_common *st, पूर्णांक latency);
पूर्णांक hid_sensor_get_report_latency(काष्ठा hid_sensor_common *st);

#पूर्ण_अगर
