<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * System Control and Management Interface (SCMI) Sensor Protocol
 *
 * Copyright (C) 2018-2021 ARM Ltd.
 */

#घोषणा pr_fmt(fmt) "SCMI Notifications SENSOR - " fmt

#समावेश <linux/bitfield.h>
#समावेश <linux/module.h>
#समावेश <linux/scmi_protocol.h>

#समावेश "common.h"
#समावेश "notify.h"

#घोषणा SCMI_MAX_NUM_SENSOR_AXIS	63
#घोषणा	SCMIv2_SENSOR_PROTOCOL		0x10000

क्रमागत scmi_sensor_protocol_cmd अणु
	SENSOR_DESCRIPTION_GET = 0x3,
	SENSOR_TRIP_POINT_NOTIFY = 0x4,
	SENSOR_TRIP_POINT_CONFIG = 0x5,
	SENSOR_READING_GET = 0x6,
	SENSOR_AXIS_DESCRIPTION_GET = 0x7,
	SENSOR_LIST_UPDATE_INTERVALS = 0x8,
	SENSOR_CONFIG_GET = 0x9,
	SENSOR_CONFIG_SET = 0xA,
	SENSOR_CONTINUOUS_UPDATE_NOTIFY = 0xB,
पूर्ण;

काष्ठा scmi_msg_resp_sensor_attributes अणु
	__le16 num_sensors;
	u8 max_requests;
	u8 reserved;
	__le32 reg_addr_low;
	__le32 reg_addr_high;
	__le32 reg_size;
पूर्ण;

/* v3 attributes_low macros */
#घोषणा SUPPORTS_UPDATE_NOTIFY(x)	FIELD_GET(BIT(30), (x))
#घोषणा SENSOR_TSTAMP_EXP(x)		FIELD_GET(GENMASK(14, 10), (x))
#घोषणा SUPPORTS_TIMESTAMP(x)		FIELD_GET(BIT(9), (x))
#घोषणा SUPPORTS_EXTEND_ATTRS(x)	FIELD_GET(BIT(8), (x))

/* v2 attributes_high macros */
#घोषणा SENSOR_UPDATE_BASE(x)		FIELD_GET(GENMASK(31, 27), (x))
#घोषणा SENSOR_UPDATE_SCALE(x)		FIELD_GET(GENMASK(26, 22), (x))

/* v3 attributes_high macros */
#घोषणा SENSOR_AXIS_NUMBER(x)		FIELD_GET(GENMASK(21, 16), (x))
#घोषणा SUPPORTS_AXIS(x)		FIELD_GET(BIT(8), (x))

/* v3 resolution macros */
#घोषणा SENSOR_RES(x)			FIELD_GET(GENMASK(26, 0), (x))
#घोषणा SENSOR_RES_EXP(x)		FIELD_GET(GENMASK(31, 27), (x))

काष्ठा scmi_msg_resp_attrs अणु
	__le32 min_range_low;
	__le32 min_range_high;
	__le32 max_range_low;
	__le32 max_range_high;
पूर्ण;

काष्ठा scmi_msg_resp_sensor_description अणु
	__le16 num_वापसed;
	__le16 num_reमुख्यing;
	काष्ठा scmi_sensor_descriptor अणु
		__le32 id;
		__le32 attributes_low;
/* Common attributes_low macros */
#घोषणा SUPPORTS_ASYNC_READ(x)		FIELD_GET(BIT(31), (x))
#घोषणा NUM_TRIP_POINTS(x)		FIELD_GET(GENMASK(7, 0), (x))
		__le32 attributes_high;
/* Common attributes_high macros */
#घोषणा SENSOR_SCALE(x)			FIELD_GET(GENMASK(15, 11), (x))
#घोषणा SENSOR_SCALE_SIGN		BIT(4)
#घोषणा SENSOR_SCALE_EXTEND		GENMASK(31, 5)
#घोषणा SENSOR_TYPE(x)			FIELD_GET(GENMASK(7, 0), (x))
		u8 name[SCMI_MAX_STR_SIZE];
		/* only क्रम version > 2.0 */
		__le32 घातer;
		__le32 resolution;
		काष्ठा scmi_msg_resp_attrs scalar_attrs;
	पूर्ण desc[];
पूर्ण;

/* Base scmi_sensor_descriptor size excluding extended attrs after name */
#घोषणा SCMI_MSG_RESP_SENS_DESCR_BASE_SZ	28

/* Sign extend to a full s32 */
#घोषणा	S32_EXT(v)							\
	(अणु								\
		पूर्णांक __v = (v);						\
									\
		अगर (__v & SENSOR_SCALE_SIGN)				\
			__v |= SENSOR_SCALE_EXTEND;			\
		__v;							\
	पूर्ण)

काष्ठा scmi_msg_sensor_axis_description_get अणु
	__le32 id;
	__le32 axis_desc_index;
पूर्ण;

काष्ठा scmi_msg_resp_sensor_axis_description अणु
	__le32 num_axis_flags;
#घोषणा NUM_AXIS_RETURNED(x)		FIELD_GET(GENMASK(5, 0), (x))
#घोषणा NUM_AXIS_REMAINING(x)		FIELD_GET(GENMASK(31, 26), (x))
	काष्ठा scmi_axis_descriptor अणु
		__le32 id;
		__le32 attributes_low;
		__le32 attributes_high;
		u8 name[SCMI_MAX_STR_SIZE];
		__le32 resolution;
		काष्ठा scmi_msg_resp_attrs attrs;
	पूर्ण desc[];
पूर्ण;

/* Base scmi_axis_descriptor size excluding extended attrs after name */
#घोषणा SCMI_MSG_RESP_AXIS_DESCR_BASE_SZ	28

काष्ठा scmi_msg_sensor_list_update_पूर्णांकervals अणु
	__le32 id;
	__le32 index;
पूर्ण;

काष्ठा scmi_msg_resp_sensor_list_update_पूर्णांकervals अणु
	__le32 num_पूर्णांकervals_flags;
#घोषणा NUM_INTERVALS_RETURNED(x)	FIELD_GET(GENMASK(11, 0), (x))
#घोषणा SEGMENTED_INTVL_FORMAT(x)	FIELD_GET(BIT(12), (x))
#घोषणा NUM_INTERVALS_REMAINING(x)	FIELD_GET(GENMASK(31, 16), (x))
	__le32 पूर्णांकervals[];
पूर्ण;

काष्ठा scmi_msg_sensor_request_notअगरy अणु
	__le32 id;
	__le32 event_control;
#घोषणा SENSOR_NOTIFY_ALL	BIT(0)
पूर्ण;

काष्ठा scmi_msg_set_sensor_trip_poपूर्णांक अणु
	__le32 id;
	__le32 event_control;
#घोषणा SENSOR_TP_EVENT_MASK	(0x3)
#घोषणा SENSOR_TP_DISABLED	0x0
#घोषणा SENSOR_TP_POSITIVE	0x1
#घोषणा SENSOR_TP_NEGATIVE	0x2
#घोषणा SENSOR_TP_BOTH		0x3
#घोषणा SENSOR_TP_ID(x)		(((x) & 0xff) << 4)
	__le32 value_low;
	__le32 value_high;
पूर्ण;

काष्ठा scmi_msg_sensor_config_set अणु
	__le32 id;
	__le32 sensor_config;
पूर्ण;

काष्ठा scmi_msg_sensor_पढ़ोing_get अणु
	__le32 id;
	__le32 flags;
#घोषणा SENSOR_READ_ASYNC	BIT(0)
पूर्ण;

काष्ठा scmi_resp_sensor_पढ़ोing_complete अणु
	__le32 id;
	__le64 पढ़ोings;
पूर्ण;

काष्ठा scmi_sensor_पढ़ोing_resp अणु
	__le32 sensor_value_low;
	__le32 sensor_value_high;
	__le32 बारtamp_low;
	__le32 बारtamp_high;
पूर्ण;

काष्ठा scmi_resp_sensor_पढ़ोing_complete_v3 अणु
	__le32 id;
	काष्ठा scmi_sensor_पढ़ोing_resp पढ़ोings[];
पूर्ण;

काष्ठा scmi_sensor_trip_notअगरy_payld अणु
	__le32 agent_id;
	__le32 sensor_id;
	__le32 trip_poपूर्णांक_desc;
पूर्ण;

काष्ठा scmi_sensor_update_notअगरy_payld अणु
	__le32 agent_id;
	__le32 sensor_id;
	काष्ठा scmi_sensor_पढ़ोing_resp पढ़ोings[];
पूर्ण;

काष्ठा sensors_info अणु
	u32 version;
	पूर्णांक num_sensors;
	पूर्णांक max_requests;
	u64 reg_addr;
	u32 reg_size;
	काष्ठा scmi_sensor_info *sensors;
पूर्ण;

अटल पूर्णांक scmi_sensor_attributes_get(स्थिर काष्ठा scmi_protocol_handle *ph,
				      काष्ठा sensors_info *si)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_msg_resp_sensor_attributes *attr;

	ret = ph->xops->xfer_get_init(ph, PROTOCOL_ATTRIBUTES,
				      0, माप(*attr), &t);
	अगर (ret)
		वापस ret;

	attr = t->rx.buf;

	ret = ph->xops->करो_xfer(ph, t);
	अगर (!ret) अणु
		si->num_sensors = le16_to_cpu(attr->num_sensors);
		si->max_requests = attr->max_requests;
		si->reg_addr = le32_to_cpu(attr->reg_addr_low) |
				(u64)le32_to_cpu(attr->reg_addr_high) << 32;
		si->reg_size = le32_to_cpu(attr->reg_size);
	पूर्ण

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम scmi_parse_range_attrs(काष्ठा scmi_range_attrs *out,
					  काष्ठा scmi_msg_resp_attrs *in)
अणु
	out->min_range = get_unaligned_le64((व्योम *)&in->min_range_low);
	out->max_range = get_unaligned_le64((व्योम *)&in->max_range_low);
पूर्ण

अटल पूर्णांक scmi_sensor_update_पूर्णांकervals(स्थिर काष्ठा scmi_protocol_handle *ph,
					काष्ठा scmi_sensor_info *s)
अणु
	पूर्णांक ret, cnt;
	u32 desc_index = 0;
	u16 num_वापसed, num_reमुख्यing;
	काष्ठा scmi_xfer *ti;
	काष्ठा scmi_msg_resp_sensor_list_update_पूर्णांकervals *buf;
	काष्ठा scmi_msg_sensor_list_update_पूर्णांकervals *msg;

	ret = ph->xops->xfer_get_init(ph, SENSOR_LIST_UPDATE_INTERVALS,
				      माप(*msg), 0, &ti);
	अगर (ret)
		वापस ret;

	buf = ti->rx.buf;
	करो अणु
		u32 flags;

		msg = ti->tx.buf;
		/* Set the number of sensors to be skipped/alपढ़ोy पढ़ो */
		msg->id = cpu_to_le32(s->id);
		msg->index = cpu_to_le32(desc_index);

		ret = ph->xops->करो_xfer(ph, ti);
		अगर (ret)
			अवरोध;

		flags = le32_to_cpu(buf->num_पूर्णांकervals_flags);
		num_वापसed = NUM_INTERVALS_RETURNED(flags);
		num_reमुख्यing = NUM_INTERVALS_REMAINING(flags);

		/*
		 * Max पूर्णांकervals is not declared previously anywhere so we
		 * assume it's वापसed+reमुख्यing.
		 */
		अगर (!s->पूर्णांकervals.count) अणु
			s->पूर्णांकervals.segmented = SEGMENTED_INTVL_FORMAT(flags);
			s->पूर्णांकervals.count = num_वापसed + num_reमुख्यing;
			/* segmented पूर्णांकervals are reported in one triplet */
			अगर (s->पूर्णांकervals.segmented &&
			    (num_reमुख्यing || num_वापसed != 3)) अणु
				dev_err(ph->dev,
					"Sensor ID:%d advertises an invalid segmented interval (%d)\n",
					s->id, s->पूर्णांकervals.count);
				s->पूर्णांकervals.segmented = false;
				s->पूर्णांकervals.count = 0;
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			/* Direct allocation when exceeding pre-allocated */
			अगर (s->पूर्णांकervals.count >= SCMI_MAX_PREALLOC_POOL) अणु
				s->पूर्णांकervals.desc =
					devm_kसुस्मृति(ph->dev,
						     s->पूर्णांकervals.count,
						     माप(*s->पूर्णांकervals.desc),
						     GFP_KERNEL);
				अगर (!s->पूर्णांकervals.desc) अणु
					s->पूर्णांकervals.segmented = false;
					s->पूर्णांकervals.count = 0;
					ret = -ENOMEM;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (desc_index + num_वापसed > s->पूर्णांकervals.count) अणु
			dev_err(ph->dev,
				"No. of update intervals can't exceed %d\n",
				s->पूर्णांकervals.count);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		क्रम (cnt = 0; cnt < num_वापसed; cnt++)
			s->पूर्णांकervals.desc[desc_index + cnt] =
					le32_to_cpu(buf->पूर्णांकervals[cnt]);

		desc_index += num_वापसed;

		ph->xops->reset_rx_to_maxsz(ph, ti);
		/*
		 * check क्रम both वापसed and reमुख्यing to aव्योम infinite
		 * loop due to buggy firmware
		 */
	पूर्ण जबतक (num_वापसed && num_reमुख्यing);

	ph->xops->xfer_put(ph, ti);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_sensor_axis_description(स्थिर काष्ठा scmi_protocol_handle *ph,
					काष्ठा scmi_sensor_info *s)
अणु
	पूर्णांक ret, cnt;
	u32 desc_index = 0;
	u16 num_वापसed, num_reमुख्यing;
	काष्ठा scmi_xfer *te;
	काष्ठा scmi_msg_resp_sensor_axis_description *buf;
	काष्ठा scmi_msg_sensor_axis_description_get *msg;

	s->axis = devm_kसुस्मृति(ph->dev, s->num_axis,
			       माप(*s->axis), GFP_KERNEL);
	अगर (!s->axis)
		वापस -ENOMEM;

	ret = ph->xops->xfer_get_init(ph, SENSOR_AXIS_DESCRIPTION_GET,
				      माप(*msg), 0, &te);
	अगर (ret)
		वापस ret;

	buf = te->rx.buf;
	करो अणु
		u32 flags;
		काष्ठा scmi_axis_descriptor *adesc;

		msg = te->tx.buf;
		/* Set the number of sensors to be skipped/alपढ़ोy पढ़ो */
		msg->id = cpu_to_le32(s->id);
		msg->axis_desc_index = cpu_to_le32(desc_index);

		ret = ph->xops->करो_xfer(ph, te);
		अगर (ret)
			अवरोध;

		flags = le32_to_cpu(buf->num_axis_flags);
		num_वापसed = NUM_AXIS_RETURNED(flags);
		num_reमुख्यing = NUM_AXIS_REMAINING(flags);

		अगर (desc_index + num_वापसed > s->num_axis) अणु
			dev_err(ph->dev, "No. of axis can't exceed %d\n",
				s->num_axis);
			अवरोध;
		पूर्ण

		adesc = &buf->desc[0];
		क्रम (cnt = 0; cnt < num_वापसed; cnt++) अणु
			u32 attrh, attrl;
			काष्ठा scmi_sensor_axis_info *a;
			माप_प्रकार dsize = SCMI_MSG_RESP_AXIS_DESCR_BASE_SZ;

			attrl = le32_to_cpu(adesc->attributes_low);

			a = &s->axis[desc_index + cnt];

			a->id = le32_to_cpu(adesc->id);
			a->extended_attrs = SUPPORTS_EXTEND_ATTRS(attrl);

			attrh = le32_to_cpu(adesc->attributes_high);
			a->scale = S32_EXT(SENSOR_SCALE(attrh));
			a->type = SENSOR_TYPE(attrh);
			strlcpy(a->name, adesc->name, SCMI_MAX_STR_SIZE);

			अगर (a->extended_attrs) अणु
				अचिन्हित पूर्णांक ares =
					le32_to_cpu(adesc->resolution);

				a->resolution = SENSOR_RES(ares);
				a->exponent =
					S32_EXT(SENSOR_RES_EXP(ares));
				dsize += माप(adesc->resolution);

				scmi_parse_range_attrs(&a->attrs,
						       &adesc->attrs);
				dsize += माप(adesc->attrs);
			पूर्ण

			adesc = (typeof(adesc))((u8 *)adesc + dsize);
		पूर्ण

		desc_index += num_वापसed;

		ph->xops->reset_rx_to_maxsz(ph, te);
		/*
		 * check क्रम both वापसed and reमुख्यing to aव्योम infinite
		 * loop due to buggy firmware
		 */
	पूर्ण जबतक (num_वापसed && num_reमुख्यing);

	ph->xops->xfer_put(ph, te);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_sensor_description_get(स्थिर काष्ठा scmi_protocol_handle *ph,
				       काष्ठा sensors_info *si)
अणु
	पूर्णांक ret, cnt;
	u32 desc_index = 0;
	u16 num_वापसed, num_reमुख्यing;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_msg_resp_sensor_description *buf;

	ret = ph->xops->xfer_get_init(ph, SENSOR_DESCRIPTION_GET,
				      माप(__le32), 0, &t);
	अगर (ret)
		वापस ret;

	buf = t->rx.buf;

	करो अणु
		काष्ठा scmi_sensor_descriptor *sdesc;

		/* Set the number of sensors to be skipped/alपढ़ोy पढ़ो */
		put_unaligned_le32(desc_index, t->tx.buf);

		ret = ph->xops->करो_xfer(ph, t);
		अगर (ret)
			अवरोध;

		num_वापसed = le16_to_cpu(buf->num_वापसed);
		num_reमुख्यing = le16_to_cpu(buf->num_reमुख्यing);

		अगर (desc_index + num_वापसed > si->num_sensors) अणु
			dev_err(ph->dev, "No. of sensors can't exceed %d",
				si->num_sensors);
			अवरोध;
		पूर्ण

		sdesc = &buf->desc[0];
		क्रम (cnt = 0; cnt < num_वापसed; cnt++) अणु
			u32 attrh, attrl;
			काष्ठा scmi_sensor_info *s;
			माप_प्रकार dsize = SCMI_MSG_RESP_SENS_DESCR_BASE_SZ;

			s = &si->sensors[desc_index + cnt];
			s->id = le32_to_cpu(sdesc->id);

			attrl = le32_to_cpu(sdesc->attributes_low);
			/* common bitfields parsing */
			s->async = SUPPORTS_ASYNC_READ(attrl);
			s->num_trip_poपूर्णांकs = NUM_TRIP_POINTS(attrl);
			/**
			 * only SCMIv3.0 specअगरic bitfield below.
			 * Such bitfields are assumed to be zeroed on non
			 * relevant fw versions...assuming fw not buggy !
			 */
			s->update = SUPPORTS_UPDATE_NOTIFY(attrl);
			s->बारtamped = SUPPORTS_TIMESTAMP(attrl);
			अगर (s->बारtamped)
				s->tstamp_scale =
					S32_EXT(SENSOR_TSTAMP_EXP(attrl));
			s->extended_scalar_attrs =
				SUPPORTS_EXTEND_ATTRS(attrl);

			attrh = le32_to_cpu(sdesc->attributes_high);
			/* common bitfields parsing */
			s->scale = S32_EXT(SENSOR_SCALE(attrh));
			s->type = SENSOR_TYPE(attrh);
			/* Use pre-allocated pool wherever possible */
			s->पूर्णांकervals.desc = s->पूर्णांकervals.pपुनः_स्मृति_pool;
			अगर (si->version == SCMIv2_SENSOR_PROTOCOL) अणु
				s->पूर्णांकervals.segmented = false;
				s->पूर्णांकervals.count = 1;
				/*
				 * Convert SCMIv2.0 update पूर्णांकerval क्रमmat to
				 * SCMIv3.0 to be used as the common exposed
				 * descriptor, accessible via common macros.
				 */
				s->पूर्णांकervals.desc[0] =
					(SENSOR_UPDATE_BASE(attrh) << 5) |
					 SENSOR_UPDATE_SCALE(attrh);
			पूर्ण अन्यथा अणु
				/*
				 * From SCMIv3.0 update पूर्णांकervals are retrieved
				 * via a dedicated (optional) command.
				 * Since the command is optional, on error carry
				 * on without any update पूर्णांकerval.
				 */
				अगर (scmi_sensor_update_पूर्णांकervals(ph, s))
					dev_dbg(ph->dev,
						"Update Intervals not available for sensor ID:%d\n",
						s->id);
			पूर्ण
			/**
			 * only > SCMIv2.0 specअगरic bitfield below.
			 * Such bitfields are assumed to be zeroed on non
			 * relevant fw versions...assuming fw not buggy !
			 */
			s->num_axis = min_t(अचिन्हित पूर्णांक,
					    SUPPORTS_AXIS(attrh) ?
					    SENSOR_AXIS_NUMBER(attrh) : 0,
					    SCMI_MAX_NUM_SENSOR_AXIS);
			strlcpy(s->name, sdesc->name, SCMI_MAX_STR_SIZE);

			अगर (s->extended_scalar_attrs) अणु
				s->sensor_घातer = le32_to_cpu(sdesc->घातer);
				dsize += माप(sdesc->घातer);
				/* Only क्रम sensors reporting scalar values */
				अगर (s->num_axis == 0) अणु
					अचिन्हित पूर्णांक sres =
						le32_to_cpu(sdesc->resolution);

					s->resolution = SENSOR_RES(sres);
					s->exponent =
						S32_EXT(SENSOR_RES_EXP(sres));
					dsize += माप(sdesc->resolution);

					scmi_parse_range_attrs(&s->scalar_attrs,
							       &sdesc->scalar_attrs);
					dsize += माप(sdesc->scalar_attrs);
				पूर्ण
			पूर्ण
			अगर (s->num_axis > 0) अणु
				ret = scmi_sensor_axis_description(ph, s);
				अगर (ret)
					जाओ out;
			पूर्ण

			sdesc = (typeof(sdesc))((u8 *)sdesc + dsize);
		पूर्ण

		desc_index += num_वापसed;

		ph->xops->reset_rx_to_maxsz(ph, t);
		/*
		 * check क्रम both वापसed and reमुख्यing to aव्योम infinite
		 * loop due to buggy firmware
		 */
	पूर्ण जबतक (num_वापसed && num_reमुख्यing);

out:
	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
scmi_sensor_request_notअगरy(स्थिर काष्ठा scmi_protocol_handle *ph, u32 sensor_id,
			   u8 message_id, bool enable)
अणु
	पूर्णांक ret;
	u32 evt_cntl = enable ? SENSOR_NOTIFY_ALL : 0;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_msg_sensor_request_notअगरy *cfg;

	ret = ph->xops->xfer_get_init(ph, message_id, माप(*cfg), 0, &t);
	अगर (ret)
		वापस ret;

	cfg = t->tx.buf;
	cfg->id = cpu_to_le32(sensor_id);
	cfg->event_control = cpu_to_le32(evt_cntl);

	ret = ph->xops->करो_xfer(ph, t);

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_sensor_trip_poपूर्णांक_notअगरy(स्थिर काष्ठा scmi_protocol_handle *ph,
					 u32 sensor_id, bool enable)
अणु
	वापस scmi_sensor_request_notअगरy(ph, sensor_id,
					  SENSOR_TRIP_POINT_NOTIFY,
					  enable);
पूर्ण

अटल पूर्णांक
scmi_sensor_continuous_update_notअगरy(स्थिर काष्ठा scmi_protocol_handle *ph,
				     u32 sensor_id, bool enable)
अणु
	वापस scmi_sensor_request_notअगरy(ph, sensor_id,
					  SENSOR_CONTINUOUS_UPDATE_NOTIFY,
					  enable);
पूर्ण

अटल पूर्णांक
scmi_sensor_trip_poपूर्णांक_config(स्थिर काष्ठा scmi_protocol_handle *ph,
			      u32 sensor_id, u8 trip_id, u64 trip_value)
अणु
	पूर्णांक ret;
	u32 evt_cntl = SENSOR_TP_BOTH;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_msg_set_sensor_trip_poपूर्णांक *trip;

	ret = ph->xops->xfer_get_init(ph, SENSOR_TRIP_POINT_CONFIG,
				      माप(*trip), 0, &t);
	अगर (ret)
		वापस ret;

	trip = t->tx.buf;
	trip->id = cpu_to_le32(sensor_id);
	trip->event_control = cpu_to_le32(evt_cntl | SENSOR_TP_ID(trip_id));
	trip->value_low = cpu_to_le32(trip_value & 0xffffffff);
	trip->value_high = cpu_to_le32(trip_value >> 32);

	ret = ph->xops->करो_xfer(ph, t);

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_sensor_config_get(स्थिर काष्ठा scmi_protocol_handle *ph,
				  u32 sensor_id, u32 *sensor_config)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;

	ret = ph->xops->xfer_get_init(ph, SENSOR_CONFIG_GET,
				      माप(__le32), माप(__le32), &t);
	अगर (ret)
		वापस ret;

	put_unaligned_le32(cpu_to_le32(sensor_id), t->tx.buf);
	ret = ph->xops->करो_xfer(ph, t);
	अगर (!ret) अणु
		काष्ठा sensors_info *si = ph->get_priv(ph);
		काष्ठा scmi_sensor_info *s = si->sensors + sensor_id;

		*sensor_config = get_unaligned_le64(t->rx.buf);
		s->sensor_config = *sensor_config;
	पूर्ण

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल पूर्णांक scmi_sensor_config_set(स्थिर काष्ठा scmi_protocol_handle *ph,
				  u32 sensor_id, u32 sensor_config)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_msg_sensor_config_set *msg;

	ret = ph->xops->xfer_get_init(ph, SENSOR_CONFIG_SET,
				      माप(*msg), 0, &t);
	अगर (ret)
		वापस ret;

	msg = t->tx.buf;
	msg->id = cpu_to_le32(sensor_id);
	msg->sensor_config = cpu_to_le32(sensor_config);

	ret = ph->xops->करो_xfer(ph, t);
	अगर (!ret) अणु
		काष्ठा sensors_info *si = ph->get_priv(ph);
		काष्ठा scmi_sensor_info *s = si->sensors + sensor_id;

		s->sensor_config = sensor_config;
	पूर्ण

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

/**
 * scmi_sensor_पढ़ोing_get  - Read scalar sensor value
 * @ph: Protocol handle
 * @sensor_id: Sensor ID
 * @value: The 64bit value sensor पढ़ोing
 *
 * This function वापसs a single 64 bit पढ़ोing value representing the sensor
 * value; अगर the platक्रमm SCMI Protocol implementation and the sensor support
 * multiple axis and बारtamped-पढ़ोs, this just वापसs the first axis जबतक
 * dropping the बारtamp value.
 * Use instead the @scmi_sensor_पढ़ोing_get_बारtamped to retrieve the array of
 * बारtamped multi-axis values.
 *
 * Return: 0 on Success
 */
अटल पूर्णांक scmi_sensor_पढ़ोing_get(स्थिर काष्ठा scmi_protocol_handle *ph,
				   u32 sensor_id, u64 *value)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_msg_sensor_पढ़ोing_get *sensor;
	काष्ठा sensors_info *si = ph->get_priv(ph);
	काष्ठा scmi_sensor_info *s = si->sensors + sensor_id;

	ret = ph->xops->xfer_get_init(ph, SENSOR_READING_GET,
				      माप(*sensor), 0, &t);
	अगर (ret)
		वापस ret;

	sensor = t->tx.buf;
	sensor->id = cpu_to_le32(sensor_id);
	अगर (s->async) अणु
		sensor->flags = cpu_to_le32(SENSOR_READ_ASYNC);
		ret = ph->xops->करो_xfer_with_response(ph, t);
		अगर (!ret) अणु
			काष्ठा scmi_resp_sensor_पढ़ोing_complete *resp;

			resp = t->rx.buf;
			अगर (le32_to_cpu(resp->id) == sensor_id)
				*value = get_unaligned_le64(&resp->पढ़ोings);
			अन्यथा
				ret = -EPROTO;
		पूर्ण
	पूर्ण अन्यथा अणु
		sensor->flags = cpu_to_le32(0);
		ret = ph->xops->करो_xfer(ph, t);
		अगर (!ret)
			*value = get_unaligned_le64(t->rx.buf);
	पूर्ण

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
scmi_parse_sensor_पढ़ोings(काष्ठा scmi_sensor_पढ़ोing *out,
			   स्थिर काष्ठा scmi_sensor_पढ़ोing_resp *in)
अणु
	out->value = get_unaligned_le64((व्योम *)&in->sensor_value_low);
	out->बारtamp = get_unaligned_le64((व्योम *)&in->बारtamp_low);
पूर्ण

/**
 * scmi_sensor_पढ़ोing_get_बारtamped  - Read multiple-axis बारtamped values
 * @ph: Protocol handle
 * @sensor_id: Sensor ID
 * @count: The length of the provided @पढ़ोings array
 * @पढ़ोings: An array of elements each representing a बारtamped per-axis
 *	      पढ़ोing of type @काष्ठा scmi_sensor_पढ़ोing.
 *	      Returned पढ़ोings are ordered as the @axis descriptors array
 *	      included in @काष्ठा scmi_sensor_info and the max number of
 *	      वापसed elements is min(@count, @num_axis); ideally the provided
 *	      array should be of length @count equal to @num_axis.
 *
 * Return: 0 on Success
 */
अटल पूर्णांक
scmi_sensor_पढ़ोing_get_बारtamped(स्थिर काष्ठा scmi_protocol_handle *ph,
				    u32 sensor_id, u8 count,
				    काष्ठा scmi_sensor_पढ़ोing *पढ़ोings)
अणु
	पूर्णांक ret;
	काष्ठा scmi_xfer *t;
	काष्ठा scmi_msg_sensor_पढ़ोing_get *sensor;
	काष्ठा sensors_info *si = ph->get_priv(ph);
	काष्ठा scmi_sensor_info *s = si->sensors + sensor_id;

	अगर (!count || !पढ़ोings ||
	    (!s->num_axis && count > 1) || (s->num_axis && count > s->num_axis))
		वापस -EINVAL;

	ret = ph->xops->xfer_get_init(ph, SENSOR_READING_GET,
				      माप(*sensor), 0, &t);
	अगर (ret)
		वापस ret;

	sensor = t->tx.buf;
	sensor->id = cpu_to_le32(sensor_id);
	अगर (s->async) अणु
		sensor->flags = cpu_to_le32(SENSOR_READ_ASYNC);
		ret = ph->xops->करो_xfer_with_response(ph, t);
		अगर (!ret) अणु
			पूर्णांक i;
			काष्ठा scmi_resp_sensor_पढ़ोing_complete_v3 *resp;

			resp = t->rx.buf;
			/* Retrieve only the number of requested axis anyway */
			अगर (le32_to_cpu(resp->id) == sensor_id)
				क्रम (i = 0; i < count; i++)
					scmi_parse_sensor_पढ़ोings(&पढ़ोings[i],
								   &resp->पढ़ोings[i]);
			अन्यथा
				ret = -EPROTO;
		पूर्ण
	पूर्ण अन्यथा अणु
		sensor->flags = cpu_to_le32(0);
		ret = ph->xops->करो_xfer(ph, t);
		अगर (!ret) अणु
			पूर्णांक i;
			काष्ठा scmi_sensor_पढ़ोing_resp *resp_पढ़ोings;

			resp_पढ़ोings = t->rx.buf;
			क्रम (i = 0; i < count; i++)
				scmi_parse_sensor_पढ़ोings(&पढ़ोings[i],
							   &resp_पढ़ोings[i]);
		पूर्ण
	पूर्ण

	ph->xops->xfer_put(ph, t);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा scmi_sensor_info *
scmi_sensor_info_get(स्थिर काष्ठा scmi_protocol_handle *ph, u32 sensor_id)
अणु
	काष्ठा sensors_info *si = ph->get_priv(ph);

	वापस si->sensors + sensor_id;
पूर्ण

अटल पूर्णांक scmi_sensor_count_get(स्थिर काष्ठा scmi_protocol_handle *ph)
अणु
	काष्ठा sensors_info *si = ph->get_priv(ph);

	वापस si->num_sensors;
पूर्ण

अटल स्थिर काष्ठा scmi_sensor_proto_ops sensor_proto_ops = अणु
	.count_get = scmi_sensor_count_get,
	.info_get = scmi_sensor_info_get,
	.trip_poपूर्णांक_config = scmi_sensor_trip_poपूर्णांक_config,
	.पढ़ोing_get = scmi_sensor_पढ़ोing_get,
	.पढ़ोing_get_बारtamped = scmi_sensor_पढ़ोing_get_बारtamped,
	.config_get = scmi_sensor_config_get,
	.config_set = scmi_sensor_config_set,
पूर्ण;

अटल पूर्णांक scmi_sensor_set_notअगरy_enabled(स्थिर काष्ठा scmi_protocol_handle *ph,
					  u8 evt_id, u32 src_id, bool enable)
अणु
	पूर्णांक ret;

	चयन (evt_id) अणु
	हाल SCMI_EVENT_SENSOR_TRIP_POINT_EVENT:
		ret = scmi_sensor_trip_poपूर्णांक_notअगरy(ph, src_id, enable);
		अवरोध;
	हाल SCMI_EVENT_SENSOR_UPDATE:
		ret = scmi_sensor_continuous_update_notअगरy(ph, src_id, enable);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (ret)
		pr_debug("FAIL_ENABLED - evt[%X] dom[%d] - ret:%d\n",
			 evt_id, src_id, ret);

	वापस ret;
पूर्ण

अटल व्योम *
scmi_sensor_fill_custom_report(स्थिर काष्ठा scmi_protocol_handle *ph,
			       u8 evt_id, kसमय_प्रकार बारtamp,
			       स्थिर व्योम *payld, माप_प्रकार payld_sz,
			       व्योम *report, u32 *src_id)
अणु
	व्योम *rep = शून्य;

	चयन (evt_id) अणु
	हाल SCMI_EVENT_SENSOR_TRIP_POINT_EVENT:
	अणु
		स्थिर काष्ठा scmi_sensor_trip_notअगरy_payld *p = payld;
		काष्ठा scmi_sensor_trip_poपूर्णांक_report *r = report;

		अगर (माप(*p) != payld_sz)
			अवरोध;

		r->बारtamp = बारtamp;
		r->agent_id = le32_to_cpu(p->agent_id);
		r->sensor_id = le32_to_cpu(p->sensor_id);
		r->trip_poपूर्णांक_desc = le32_to_cpu(p->trip_poपूर्णांक_desc);
		*src_id = r->sensor_id;
		rep = r;
		अवरोध;
	पूर्ण
	हाल SCMI_EVENT_SENSOR_UPDATE:
	अणु
		पूर्णांक i;
		काष्ठा scmi_sensor_info *s;
		स्थिर काष्ठा scmi_sensor_update_notअगरy_payld *p = payld;
		काष्ठा scmi_sensor_update_report *r = report;
		काष्ठा sensors_info *sinfo = ph->get_priv(ph);

		/* payld_sz is variable क्रम this event */
		r->sensor_id = le32_to_cpu(p->sensor_id);
		अगर (r->sensor_id >= sinfo->num_sensors)
			अवरोध;
		r->बारtamp = बारtamp;
		r->agent_id = le32_to_cpu(p->agent_id);
		s = &sinfo->sensors[r->sensor_id];
		/*
		 * The generated report r (@काष्ठा scmi_sensor_update_report)
		 * was pre-allocated to contain up to SCMI_MAX_NUM_SENSOR_AXIS
		 * पढ़ोings: here it is filled with the effective @num_axis
		 * पढ़ोings defined क्रम this sensor or 1 क्रम scalar sensors.
		 */
		r->पढ़ोings_count = s->num_axis ?: 1;
		क्रम (i = 0; i < r->पढ़ोings_count; i++)
			scmi_parse_sensor_पढ़ोings(&r->पढ़ोings[i],
						   &p->पढ़ोings[i]);
		*src_id = r->sensor_id;
		rep = r;
		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	वापस rep;
पूर्ण

अटल पूर्णांक scmi_sensor_get_num_sources(स्थिर काष्ठा scmi_protocol_handle *ph)
अणु
	काष्ठा sensors_info *si = ph->get_priv(ph);

	वापस si->num_sensors;
पूर्ण

अटल स्थिर काष्ठा scmi_event sensor_events[] = अणु
	अणु
		.id = SCMI_EVENT_SENSOR_TRIP_POINT_EVENT,
		.max_payld_sz = माप(काष्ठा scmi_sensor_trip_notअगरy_payld),
		.max_report_sz = माप(काष्ठा scmi_sensor_trip_poपूर्णांक_report),
	पूर्ण,
	अणु
		.id = SCMI_EVENT_SENSOR_UPDATE,
		.max_payld_sz =
			माप(काष्ठा scmi_sensor_update_notअगरy_payld) +
			 SCMI_MAX_NUM_SENSOR_AXIS *
			 माप(काष्ठा scmi_sensor_पढ़ोing_resp),
		.max_report_sz = माप(काष्ठा scmi_sensor_update_report) +
				  SCMI_MAX_NUM_SENSOR_AXIS *
				  माप(काष्ठा scmi_sensor_पढ़ोing),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा scmi_event_ops sensor_event_ops = अणु
	.get_num_sources = scmi_sensor_get_num_sources,
	.set_notअगरy_enabled = scmi_sensor_set_notअगरy_enabled,
	.fill_custom_report = scmi_sensor_fill_custom_report,
पूर्ण;

अटल स्थिर काष्ठा scmi_protocol_events sensor_protocol_events = अणु
	.queue_sz = SCMI_PROTO_QUEUE_SZ,
	.ops = &sensor_event_ops,
	.evts = sensor_events,
	.num_events = ARRAY_SIZE(sensor_events),
पूर्ण;

अटल पूर्णांक scmi_sensors_protocol_init(स्थिर काष्ठा scmi_protocol_handle *ph)
अणु
	u32 version;
	पूर्णांक ret;
	काष्ठा sensors_info *sinfo;

	ph->xops->version_get(ph, &version);

	dev_dbg(ph->dev, "Sensor Version %d.%d\n",
		PROTOCOL_REV_MAJOR(version), PROTOCOL_REV_MINOR(version));

	sinfo = devm_kzalloc(ph->dev, माप(*sinfo), GFP_KERNEL);
	अगर (!sinfo)
		वापस -ENOMEM;
	sinfo->version = version;

	ret = scmi_sensor_attributes_get(ph, sinfo);
	अगर (ret)
		वापस ret;
	sinfo->sensors = devm_kसुस्मृति(ph->dev, sinfo->num_sensors,
				      माप(*sinfo->sensors), GFP_KERNEL);
	अगर (!sinfo->sensors)
		वापस -ENOMEM;

	ret = scmi_sensor_description_get(ph, sinfo);
	अगर (ret)
		वापस ret;

	वापस ph->set_priv(ph, sinfo);
पूर्ण

अटल स्थिर काष्ठा scmi_protocol scmi_sensors = अणु
	.id = SCMI_PROTOCOL_SENSOR,
	.owner = THIS_MODULE,
	.instance_init = &scmi_sensors_protocol_init,
	.ops = &sensor_proto_ops,
	.events = &sensor_protocol_events,
पूर्ण;

DEFINE_SCMI_PROTOCOL_REGISTER_UNREGISTER(sensors, scmi_sensors)
