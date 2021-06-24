<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright IBM Corp 2019

#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sysfs.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "common.h"

#घोषणा EXTN_FLAG_SENSOR_ID		BIT(7)

#घोषणा OCC_ERROR_COUNT_THRESHOLD	2	/* required by OCC spec */

#घोषणा OCC_STATE_SAFE			4
#घोषणा OCC_SAFE_TIMEOUT		msecs_to_jअगरfies(60000) /* 1 min */

#घोषणा OCC_UPDATE_FREQUENCY		msecs_to_jअगरfies(1000)

#घोषणा OCC_TEMP_SENSOR_FAULT		0xFF

#घोषणा OCC_FRU_TYPE_VRM		3

/* OCC sensor type and version definitions */

काष्ठा temp_sensor_1 अणु
	u16 sensor_id;
	u16 value;
पूर्ण __packed;

काष्ठा temp_sensor_2 अणु
	u32 sensor_id;
	u8 fru_type;
	u8 value;
पूर्ण __packed;

काष्ठा temp_sensor_10 अणु
	u32 sensor_id;
	u8 fru_type;
	u8 value;
	u8 throttle;
	u8 reserved;
पूर्ण __packed;

काष्ठा freq_sensor_1 अणु
	u16 sensor_id;
	u16 value;
पूर्ण __packed;

काष्ठा freq_sensor_2 अणु
	u32 sensor_id;
	u16 value;
पूर्ण __packed;

काष्ठा घातer_sensor_1 अणु
	u16 sensor_id;
	u32 update_tag;
	u32 accumulator;
	u16 value;
पूर्ण __packed;

काष्ठा घातer_sensor_2 अणु
	u32 sensor_id;
	u8 function_id;
	u8 apss_channel;
	u16 reserved;
	u32 update_tag;
	u64 accumulator;
	u16 value;
पूर्ण __packed;

काष्ठा घातer_sensor_data अणु
	u16 value;
	u32 update_tag;
	u64 accumulator;
पूर्ण __packed;

काष्ठा घातer_sensor_data_and_समय अणु
	u16 update_समय;
	u16 value;
	u32 update_tag;
	u64 accumulator;
पूर्ण __packed;

काष्ठा घातer_sensor_a0 अणु
	u32 sensor_id;
	काष्ठा घातer_sensor_data_and_समय प्रणाली;
	u32 reserved;
	काष्ठा घातer_sensor_data_and_समय proc;
	काष्ठा घातer_sensor_data vdd;
	काष्ठा घातer_sensor_data vdn;
पूर्ण __packed;

काष्ठा caps_sensor_2 अणु
	u16 cap;
	u16 प्रणाली_घातer;
	u16 n_cap;
	u16 max;
	u16 min;
	u16 user;
	u8 user_source;
पूर्ण __packed;

काष्ठा caps_sensor_3 अणु
	u16 cap;
	u16 प्रणाली_घातer;
	u16 n_cap;
	u16 max;
	u16 hard_min;
	u16 soft_min;
	u16 user;
	u8 user_source;
पूर्ण __packed;

काष्ठा extended_sensor अणु
	जोड़ अणु
		u8 name[4];
		u32 sensor_id;
	पूर्ण;
	u8 flags;
	u8 reserved;
	u8 data[6];
पूर्ण __packed;

अटल पूर्णांक occ_poll(काष्ठा occ *occ)
अणु
	पूर्णांक rc;
	u16 checksum = occ->poll_cmd_data + occ->seq_no + 1;
	u8 cmd[8];
	काष्ठा occ_poll_response_header *header;

	/* big endian */
	cmd[0] = occ->seq_no++;		/* sequence number */
	cmd[1] = 0;			/* cmd type */
	cmd[2] = 0;			/* data length msb */
	cmd[3] = 1;			/* data length lsb */
	cmd[4] = occ->poll_cmd_data;	/* data */
	cmd[5] = checksum >> 8;		/* checksum msb */
	cmd[6] = checksum & 0xFF;	/* checksum lsb */
	cmd[7] = 0;

	/* mutex should alपढ़ोy be locked अगर necessary */
	rc = occ->send_cmd(occ, cmd);
	अगर (rc) अणु
		occ->last_error = rc;
		अगर (occ->error_count++ > OCC_ERROR_COUNT_THRESHOLD)
			occ->error = rc;

		जाओ करोne;
	पूर्ण

	/* clear error since communication was successful */
	occ->error_count = 0;
	occ->last_error = 0;
	occ->error = 0;

	/* check क्रम safe state */
	header = (काष्ठा occ_poll_response_header *)occ->resp.data;
	अगर (header->occ_state == OCC_STATE_SAFE) अणु
		अगर (occ->last_safe) अणु
			अगर (समय_after(jअगरfies,
				       occ->last_safe + OCC_SAFE_TIMEOUT))
				occ->error = -EHOSTDOWN;
		पूर्ण अन्यथा अणु
			occ->last_safe = jअगरfies;
		पूर्ण
	पूर्ण अन्यथा अणु
		occ->last_safe = 0;
	पूर्ण

करोne:
	occ_sysfs_poll_करोne(occ);
	वापस rc;
पूर्ण

अटल पूर्णांक occ_set_user_घातer_cap(काष्ठा occ *occ, u16 user_घातer_cap)
अणु
	पूर्णांक rc;
	u8 cmd[8];
	u16 checksum = 0x24;
	__be16 user_घातer_cap_be = cpu_to_be16(user_घातer_cap);

	cmd[0] = 0;
	cmd[1] = 0x22;
	cmd[2] = 0;
	cmd[3] = 2;

	स_नकल(&cmd[4], &user_घातer_cap_be, 2);

	checksum += cmd[4] + cmd[5];
	cmd[6] = checksum >> 8;
	cmd[7] = checksum & 0xFF;

	rc = mutex_lock_पूर्णांकerruptible(&occ->lock);
	अगर (rc)
		वापस rc;

	rc = occ->send_cmd(occ, cmd);

	mutex_unlock(&occ->lock);

	वापस rc;
पूर्ण

पूर्णांक occ_update_response(काष्ठा occ *occ)
अणु
	पूर्णांक rc = mutex_lock_पूर्णांकerruptible(&occ->lock);

	अगर (rc)
		वापस rc;

	/* limit the maximum rate of polling the OCC */
	अगर (समय_after(jअगरfies, occ->next_update)) अणु
		rc = occ_poll(occ);
		occ->next_update = jअगरfies + OCC_UPDATE_FREQUENCY;
	पूर्ण अन्यथा अणु
		rc = occ->last_error;
	पूर्ण

	mutex_unlock(&occ->lock);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार occ_show_temp_1(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक rc;
	u32 val = 0;
	काष्ठा temp_sensor_1 *temp;
	काष्ठा occ *occ = dev_get_drvdata(dev);
	काष्ठा occ_sensors *sensors = &occ->sensors;
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);

	rc = occ_update_response(occ);
	अगर (rc)
		वापस rc;

	temp = ((काष्ठा temp_sensor_1 *)sensors->temp.data) + sattr->index;

	चयन (sattr->nr) अणु
	हाल 0:
		val = get_unaligned_be16(&temp->sensor_id);
		अवरोध;
	हाल 1:
		/*
		 * If a sensor पढ़ोing has expired and couldn't be refreshed,
		 * OCC वापसs 0xFFFF क्रम that sensor.
		 */
		अगर (temp->value == 0xFFFF)
			वापस -EREMOTEIO;
		val = get_unaligned_be16(&temp->value) * 1000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस sysfs_emit(buf, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार occ_show_temp_2(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक rc;
	u32 val = 0;
	काष्ठा temp_sensor_2 *temp;
	काष्ठा occ *occ = dev_get_drvdata(dev);
	काष्ठा occ_sensors *sensors = &occ->sensors;
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);

	rc = occ_update_response(occ);
	अगर (rc)
		वापस rc;

	temp = ((काष्ठा temp_sensor_2 *)sensors->temp.data) + sattr->index;

	चयन (sattr->nr) अणु
	हाल 0:
		val = get_unaligned_be32(&temp->sensor_id);
		अवरोध;
	हाल 1:
		val = temp->value;
		अगर (val == OCC_TEMP_SENSOR_FAULT)
			वापस -EREMOTEIO;

		/*
		 * VRM करोesn't वापस temperature, only alarm bit. This
		 * attribute maps to tempX_alarm instead of tempX_input क्रम
		 * VRM
		 */
		अगर (temp->fru_type != OCC_FRU_TYPE_VRM) अणु
			/* sensor not पढ़ोy */
			अगर (val == 0)
				वापस -EAGAIN;

			val *= 1000;
		पूर्ण
		अवरोध;
	हाल 2:
		val = temp->fru_type;
		अवरोध;
	हाल 3:
		val = temp->value == OCC_TEMP_SENSOR_FAULT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस sysfs_emit(buf, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार occ_show_temp_10(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक rc;
	u32 val = 0;
	काष्ठा temp_sensor_10 *temp;
	काष्ठा occ *occ = dev_get_drvdata(dev);
	काष्ठा occ_sensors *sensors = &occ->sensors;
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);

	rc = occ_update_response(occ);
	अगर (rc)
		वापस rc;

	temp = ((काष्ठा temp_sensor_10 *)sensors->temp.data) + sattr->index;

	चयन (sattr->nr) अणु
	हाल 0:
		val = get_unaligned_be32(&temp->sensor_id);
		अवरोध;
	हाल 1:
		val = temp->value;
		अगर (val == OCC_TEMP_SENSOR_FAULT)
			वापस -EREMOTEIO;

		/*
		 * VRM करोesn't वापस temperature, only alarm bit. This
		 * attribute maps to tempX_alarm instead of tempX_input क्रम
		 * VRM
		 */
		अगर (temp->fru_type != OCC_FRU_TYPE_VRM) अणु
			/* sensor not पढ़ोy */
			अगर (val == 0)
				वापस -EAGAIN;

			val *= 1000;
		पूर्ण
		अवरोध;
	हाल 2:
		val = temp->fru_type;
		अवरोध;
	हाल 3:
		val = temp->value == OCC_TEMP_SENSOR_FAULT;
		अवरोध;
	हाल 4:
		val = temp->throttle * 1000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस sysfs_emit(buf, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार occ_show_freq_1(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक rc;
	u16 val = 0;
	काष्ठा freq_sensor_1 *freq;
	काष्ठा occ *occ = dev_get_drvdata(dev);
	काष्ठा occ_sensors *sensors = &occ->sensors;
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);

	rc = occ_update_response(occ);
	अगर (rc)
		वापस rc;

	freq = ((काष्ठा freq_sensor_1 *)sensors->freq.data) + sattr->index;

	चयन (sattr->nr) अणु
	हाल 0:
		val = get_unaligned_be16(&freq->sensor_id);
		अवरोध;
	हाल 1:
		val = get_unaligned_be16(&freq->value);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस sysfs_emit(buf, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार occ_show_freq_2(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक rc;
	u32 val = 0;
	काष्ठा freq_sensor_2 *freq;
	काष्ठा occ *occ = dev_get_drvdata(dev);
	काष्ठा occ_sensors *sensors = &occ->sensors;
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);

	rc = occ_update_response(occ);
	अगर (rc)
		वापस rc;

	freq = ((काष्ठा freq_sensor_2 *)sensors->freq.data) + sattr->index;

	चयन (sattr->nr) अणु
	हाल 0:
		val = get_unaligned_be32(&freq->sensor_id);
		अवरोध;
	हाल 1:
		val = get_unaligned_be16(&freq->value);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस sysfs_emit(buf, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार occ_show_घातer_1(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक rc;
	u64 val = 0;
	काष्ठा घातer_sensor_1 *घातer;
	काष्ठा occ *occ = dev_get_drvdata(dev);
	काष्ठा occ_sensors *sensors = &occ->sensors;
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);

	rc = occ_update_response(occ);
	अगर (rc)
		वापस rc;

	घातer = ((काष्ठा घातer_sensor_1 *)sensors->घातer.data) + sattr->index;

	चयन (sattr->nr) अणु
	हाल 0:
		val = get_unaligned_be16(&घातer->sensor_id);
		अवरोध;
	हाल 1:
		val = get_unaligned_be32(&घातer->accumulator) /
			get_unaligned_be32(&घातer->update_tag);
		val *= 1000000ULL;
		अवरोध;
	हाल 2:
		val = (u64)get_unaligned_be32(&घातer->update_tag) *
			   occ->घातr_sample_समय_us;
		अवरोध;
	हाल 3:
		val = get_unaligned_be16(&घातer->value) * 1000000ULL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस sysfs_emit(buf, "%llu\n", val);
पूर्ण

अटल u64 occ_get_घातr_avg(u64 *accum, u32 *samples)
अणु
	u64 भागisor = get_unaligned_be32(samples);

	वापस (भागisor == 0) ? 0 :
		भाग64_u64(get_unaligned_be64(accum) * 1000000ULL, भागisor);
पूर्ण

अटल sमाप_प्रकार occ_show_घातer_2(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक rc;
	u64 val = 0;
	काष्ठा घातer_sensor_2 *घातer;
	काष्ठा occ *occ = dev_get_drvdata(dev);
	काष्ठा occ_sensors *sensors = &occ->sensors;
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);

	rc = occ_update_response(occ);
	अगर (rc)
		वापस rc;

	घातer = ((काष्ठा घातer_sensor_2 *)sensors->घातer.data) + sattr->index;

	चयन (sattr->nr) अणु
	हाल 0:
		वापस sysfs_emit(buf, "%u_%u_%u\n",
				  get_unaligned_be32(&घातer->sensor_id),
				  घातer->function_id, घातer->apss_channel);
	हाल 1:
		val = occ_get_घातr_avg(&घातer->accumulator,
				       &घातer->update_tag);
		अवरोध;
	हाल 2:
		val = (u64)get_unaligned_be32(&घातer->update_tag) *
			   occ->घातr_sample_समय_us;
		अवरोध;
	हाल 3:
		val = get_unaligned_be16(&घातer->value) * 1000000ULL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस sysfs_emit(buf, "%llu\n", val);
पूर्ण

अटल sमाप_प्रकार occ_show_घातer_a0(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक rc;
	u64 val = 0;
	काष्ठा घातer_sensor_a0 *घातer;
	काष्ठा occ *occ = dev_get_drvdata(dev);
	काष्ठा occ_sensors *sensors = &occ->sensors;
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);

	rc = occ_update_response(occ);
	अगर (rc)
		वापस rc;

	घातer = ((काष्ठा घातer_sensor_a0 *)sensors->घातer.data) + sattr->index;

	चयन (sattr->nr) अणु
	हाल 0:
		वापस sysfs_emit(buf, "%u_system\n",
				  get_unaligned_be32(&घातer->sensor_id));
	हाल 1:
		val = occ_get_घातr_avg(&घातer->प्रणाली.accumulator,
				       &घातer->प्रणाली.update_tag);
		अवरोध;
	हाल 2:
		val = (u64)get_unaligned_be32(&घातer->प्रणाली.update_tag) *
			   occ->घातr_sample_समय_us;
		अवरोध;
	हाल 3:
		val = get_unaligned_be16(&घातer->प्रणाली.value) * 1000000ULL;
		अवरोध;
	हाल 4:
		वापस sysfs_emit(buf, "%u_proc\n",
				  get_unaligned_be32(&घातer->sensor_id));
	हाल 5:
		val = occ_get_घातr_avg(&घातer->proc.accumulator,
				       &घातer->proc.update_tag);
		अवरोध;
	हाल 6:
		val = (u64)get_unaligned_be32(&घातer->proc.update_tag) *
			   occ->घातr_sample_समय_us;
		अवरोध;
	हाल 7:
		val = get_unaligned_be16(&घातer->proc.value) * 1000000ULL;
		अवरोध;
	हाल 8:
		वापस sysfs_emit(buf, "%u_vdd\n",
				  get_unaligned_be32(&घातer->sensor_id));
	हाल 9:
		val = occ_get_घातr_avg(&घातer->vdd.accumulator,
				       &घातer->vdd.update_tag);
		अवरोध;
	हाल 10:
		val = (u64)get_unaligned_be32(&घातer->vdd.update_tag) *
			   occ->घातr_sample_समय_us;
		अवरोध;
	हाल 11:
		val = get_unaligned_be16(&घातer->vdd.value) * 1000000ULL;
		अवरोध;
	हाल 12:
		वापस sysfs_emit(buf, "%u_vdn\n",
				  get_unaligned_be32(&घातer->sensor_id));
	हाल 13:
		val = occ_get_घातr_avg(&घातer->vdn.accumulator,
				       &घातer->vdn.update_tag);
		अवरोध;
	हाल 14:
		val = (u64)get_unaligned_be32(&घातer->vdn.update_tag) *
			   occ->घातr_sample_समय_us;
		अवरोध;
	हाल 15:
		val = get_unaligned_be16(&घातer->vdn.value) * 1000000ULL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस sysfs_emit(buf, "%llu\n", val);
पूर्ण

अटल sमाप_प्रकार occ_show_caps_1_2(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक rc;
	u64 val = 0;
	काष्ठा caps_sensor_2 *caps;
	काष्ठा occ *occ = dev_get_drvdata(dev);
	काष्ठा occ_sensors *sensors = &occ->sensors;
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);

	rc = occ_update_response(occ);
	अगर (rc)
		वापस rc;

	caps = ((काष्ठा caps_sensor_2 *)sensors->caps.data) + sattr->index;

	चयन (sattr->nr) अणु
	हाल 0:
		वापस sysfs_emit(buf, "system\n");
	हाल 1:
		val = get_unaligned_be16(&caps->cap) * 1000000ULL;
		अवरोध;
	हाल 2:
		val = get_unaligned_be16(&caps->प्रणाली_घातer) * 1000000ULL;
		अवरोध;
	हाल 3:
		val = get_unaligned_be16(&caps->n_cap) * 1000000ULL;
		अवरोध;
	हाल 4:
		val = get_unaligned_be16(&caps->max) * 1000000ULL;
		अवरोध;
	हाल 5:
		val = get_unaligned_be16(&caps->min) * 1000000ULL;
		अवरोध;
	हाल 6:
		val = get_unaligned_be16(&caps->user) * 1000000ULL;
		अवरोध;
	हाल 7:
		अगर (occ->sensors.caps.version == 1)
			वापस -EINVAL;

		val = caps->user_source;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस sysfs_emit(buf, "%llu\n", val);
पूर्ण

अटल sमाप_प्रकार occ_show_caps_3(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक rc;
	u64 val = 0;
	काष्ठा caps_sensor_3 *caps;
	काष्ठा occ *occ = dev_get_drvdata(dev);
	काष्ठा occ_sensors *sensors = &occ->sensors;
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);

	rc = occ_update_response(occ);
	अगर (rc)
		वापस rc;

	caps = ((काष्ठा caps_sensor_3 *)sensors->caps.data) + sattr->index;

	चयन (sattr->nr) अणु
	हाल 0:
		वापस sysfs_emit(buf, "system\n");
	हाल 1:
		val = get_unaligned_be16(&caps->cap) * 1000000ULL;
		अवरोध;
	हाल 2:
		val = get_unaligned_be16(&caps->प्रणाली_घातer) * 1000000ULL;
		अवरोध;
	हाल 3:
		val = get_unaligned_be16(&caps->n_cap) * 1000000ULL;
		अवरोध;
	हाल 4:
		val = get_unaligned_be16(&caps->max) * 1000000ULL;
		अवरोध;
	हाल 5:
		val = get_unaligned_be16(&caps->hard_min) * 1000000ULL;
		अवरोध;
	हाल 6:
		val = get_unaligned_be16(&caps->user) * 1000000ULL;
		अवरोध;
	हाल 7:
		val = caps->user_source;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस sysfs_emit(buf, "%llu\n", val);
पूर्ण

अटल sमाप_प्रकार occ_store_caps_user(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc;
	u16 user_घातer_cap;
	अचिन्हित दीर्घ दीर्घ value;
	काष्ठा occ *occ = dev_get_drvdata(dev);

	rc = kम_से_अदीर्घl(buf, 0, &value);
	अगर (rc)
		वापस rc;

	user_घातer_cap = भाग64_u64(value, 1000000ULL); /* microwatt to watt */

	rc = occ_set_user_घातer_cap(occ, user_घातer_cap);
	अगर (rc)
		वापस rc;

	वापस count;
पूर्ण

अटल sमाप_प्रकार occ_show_extended(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक rc;
	काष्ठा extended_sensor *extn;
	काष्ठा occ *occ = dev_get_drvdata(dev);
	काष्ठा occ_sensors *sensors = &occ->sensors;
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);

	rc = occ_update_response(occ);
	अगर (rc)
		वापस rc;

	extn = ((काष्ठा extended_sensor *)sensors->extended.data) +
		sattr->index;

	चयन (sattr->nr) अणु
	हाल 0:
		अगर (extn->flags & EXTN_FLAG_SENSOR_ID) अणु
			rc = sysfs_emit(buf, "%u",
					get_unaligned_be32(&extn->sensor_id));
		पूर्ण अन्यथा अणु
			rc = sysfs_emit(buf, "%02x%02x%02x%02x\n",
					extn->name[0], extn->name[1],
					extn->name[2], extn->name[3]);
		पूर्ण
		अवरोध;
	हाल 1:
		rc = sysfs_emit(buf, "%02x\n", extn->flags);
		अवरोध;
	हाल 2:
		rc = sysfs_emit(buf, "%02x%02x%02x%02x%02x%02x\n",
				extn->data[0], extn->data[1], extn->data[2],
				extn->data[3], extn->data[4], extn->data[5]);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

/*
 * Some helper macros to make it easier to define an occ_attribute. Since these
 * are dynamically allocated, we shouldn't use the existing kernel macros which
 * stringअगरy the name argument.
 */
#घोषणा ATTR_OCC(_name, _mode, _show, _store) अणु				\
	.attr	= अणु							\
		.name = _name,						\
		.mode = VERIFY_OCTAL_PERMISSIONS(_mode),		\
	पूर्ण,								\
	.show	= _show,						\
	.store	= _store,						\
पूर्ण

#घोषणा SENSOR_ATTR_OCC(_name, _mode, _show, _store, _nr, _index) अणु	\
	.dev_attr	= ATTR_OCC(_name, _mode, _show, _store),	\
	.index		= _index,					\
	.nr		= _nr,						\
पूर्ण

#घोषणा OCC_INIT_ATTR(_name, _mode, _show, _store, _nr, _index)		\
	((काष्ठा sensor_device_attribute_2)				\
		SENSOR_ATTR_OCC(_name, _mode, _show, _store, _nr, _index))

/*
 * Allocate and instatiate sensor_device_attribute_2s. It's most efficient to
 * use our own instead of the built-in hwmon attribute types.
 */
अटल पूर्णांक occ_setup_sensor_attrs(काष्ठा occ *occ)
अणु
	अचिन्हित पूर्णांक i, s, num_attrs = 0;
	काष्ठा device *dev = occ->bus_dev;
	काष्ठा occ_sensors *sensors = &occ->sensors;
	काष्ठा occ_attribute *attr;
	काष्ठा temp_sensor_2 *temp;
	sमाप_प्रकार (*show_temp)(काष्ठा device *, काष्ठा device_attribute *,
			     अक्षर *) = occ_show_temp_1;
	sमाप_प्रकार (*show_freq)(काष्ठा device *, काष्ठा device_attribute *,
			     अक्षर *) = occ_show_freq_1;
	sमाप_प्रकार (*show_घातer)(काष्ठा device *, काष्ठा device_attribute *,
			      अक्षर *) = occ_show_घातer_1;
	sमाप_प्रकार (*show_caps)(काष्ठा device *, काष्ठा device_attribute *,
			     अक्षर *) = occ_show_caps_1_2;

	चयन (sensors->temp.version) अणु
	हाल 1:
		num_attrs += (sensors->temp.num_sensors * 2);
		अवरोध;
	हाल 2:
		num_attrs += (sensors->temp.num_sensors * 4);
		show_temp = occ_show_temp_2;
		अवरोध;
	हाल 0x10:
		num_attrs += (sensors->temp.num_sensors * 5);
		show_temp = occ_show_temp_10;
		अवरोध;
	शेष:
		sensors->temp.num_sensors = 0;
	पूर्ण

	चयन (sensors->freq.version) अणु
	हाल 2:
		show_freq = occ_show_freq_2;
		fallthrough;
	हाल 1:
		num_attrs += (sensors->freq.num_sensors * 2);
		अवरोध;
	शेष:
		sensors->freq.num_sensors = 0;
	पूर्ण

	चयन (sensors->घातer.version) अणु
	हाल 2:
		show_घातer = occ_show_घातer_2;
		fallthrough;
	हाल 1:
		num_attrs += (sensors->घातer.num_sensors * 4);
		अवरोध;
	हाल 0xA0:
		num_attrs += (sensors->घातer.num_sensors * 16);
		show_घातer = occ_show_घातer_a0;
		अवरोध;
	शेष:
		sensors->घातer.num_sensors = 0;
	पूर्ण

	चयन (sensors->caps.version) अणु
	हाल 1:
		num_attrs += (sensors->caps.num_sensors * 7);
		अवरोध;
	हाल 3:
		show_caps = occ_show_caps_3;
		fallthrough;
	हाल 2:
		num_attrs += (sensors->caps.num_sensors * 8);
		अवरोध;
	शेष:
		sensors->caps.num_sensors = 0;
	पूर्ण

	चयन (sensors->extended.version) अणु
	हाल 1:
		num_attrs += (sensors->extended.num_sensors * 3);
		अवरोध;
	शेष:
		sensors->extended.num_sensors = 0;
	पूर्ण

	occ->attrs = devm_kzalloc(dev, माप(*occ->attrs) * num_attrs,
				  GFP_KERNEL);
	अगर (!occ->attrs)
		वापस -ENOMEM;

	/* null-terminated list */
	occ->group.attrs = devm_kzalloc(dev, माप(*occ->group.attrs) *
					num_attrs + 1, GFP_KERNEL);
	अगर (!occ->group.attrs)
		वापस -ENOMEM;

	attr = occ->attrs;

	क्रम (i = 0; i < sensors->temp.num_sensors; ++i) अणु
		s = i + 1;
		temp = ((काष्ठा temp_sensor_2 *)sensors->temp.data) + i;

		snम_लिखो(attr->name, माप(attr->name), "temp%d_label", s);
		attr->sensor = OCC_INIT_ATTR(attr->name, 0444, show_temp, शून्य,
					     0, i);
		attr++;

		अगर (sensors->temp.version > 1 &&
		    temp->fru_type == OCC_FRU_TYPE_VRM) अणु
			snम_लिखो(attr->name, माप(attr->name),
				 "temp%d_alarm", s);
		पूर्ण अन्यथा अणु
			snम_लिखो(attr->name, माप(attr->name),
				 "temp%d_input", s);
		पूर्ण

		attr->sensor = OCC_INIT_ATTR(attr->name, 0444, show_temp, शून्य,
					     1, i);
		attr++;

		अगर (sensors->temp.version > 1) अणु
			snम_लिखो(attr->name, माप(attr->name),
				 "temp%d_fru_type", s);
			attr->sensor = OCC_INIT_ATTR(attr->name, 0444,
						     show_temp, शून्य, 2, i);
			attr++;

			snम_लिखो(attr->name, माप(attr->name),
				 "temp%d_fault", s);
			attr->sensor = OCC_INIT_ATTR(attr->name, 0444,
						     show_temp, शून्य, 3, i);
			attr++;

			अगर (sensors->temp.version == 0x10) अणु
				snम_लिखो(attr->name, माप(attr->name),
					 "temp%d_max", s);
				attr->sensor = OCC_INIT_ATTR(attr->name, 0444,
							     show_temp, शून्य,
							     4, i);
				attr++;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < sensors->freq.num_sensors; ++i) अणु
		s = i + 1;

		snम_लिखो(attr->name, माप(attr->name), "freq%d_label", s);
		attr->sensor = OCC_INIT_ATTR(attr->name, 0444, show_freq, शून्य,
					     0, i);
		attr++;

		snम_लिखो(attr->name, माप(attr->name), "freq%d_input", s);
		attr->sensor = OCC_INIT_ATTR(attr->name, 0444, show_freq, शून्य,
					     1, i);
		attr++;
	पूर्ण

	अगर (sensors->घातer.version == 0xA0) अणु
		/*
		 * Special हाल क्रम many-attribute घातer sensor. Split it पूर्णांकo
		 * a sensor number per घातer type, emulating several sensors.
		 */
		क्रम (i = 0; i < sensors->घातer.num_sensors; ++i) अणु
			अचिन्हित पूर्णांक j;
			अचिन्हित पूर्णांक nr = 0;

			s = (i * 4) + 1;

			क्रम (j = 0; j < 4; ++j) अणु
				snम_लिखो(attr->name, माप(attr->name),
					 "power%d_label", s);
				attr->sensor = OCC_INIT_ATTR(attr->name, 0444,
							     show_घातer, शून्य,
							     nr++, i);
				attr++;

				snम_लिखो(attr->name, माप(attr->name),
					 "power%d_average", s);
				attr->sensor = OCC_INIT_ATTR(attr->name, 0444,
							     show_घातer, शून्य,
							     nr++, i);
				attr++;

				snम_लिखो(attr->name, माप(attr->name),
					 "power%d_average_interval", s);
				attr->sensor = OCC_INIT_ATTR(attr->name, 0444,
							     show_घातer, शून्य,
							     nr++, i);
				attr++;

				snम_लिखो(attr->name, माप(attr->name),
					 "power%d_input", s);
				attr->sensor = OCC_INIT_ATTR(attr->name, 0444,
							     show_घातer, शून्य,
							     nr++, i);
				attr++;

				s++;
			पूर्ण
		पूर्ण

		s = (sensors->घातer.num_sensors * 4) + 1;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < sensors->घातer.num_sensors; ++i) अणु
			s = i + 1;

			snम_लिखो(attr->name, माप(attr->name),
				 "power%d_label", s);
			attr->sensor = OCC_INIT_ATTR(attr->name, 0444,
						     show_घातer, शून्य, 0, i);
			attr++;

			snम_लिखो(attr->name, माप(attr->name),
				 "power%d_average", s);
			attr->sensor = OCC_INIT_ATTR(attr->name, 0444,
						     show_घातer, शून्य, 1, i);
			attr++;

			snम_लिखो(attr->name, माप(attr->name),
				 "power%d_average_interval", s);
			attr->sensor = OCC_INIT_ATTR(attr->name, 0444,
						     show_घातer, शून्य, 2, i);
			attr++;

			snम_लिखो(attr->name, माप(attr->name),
				 "power%d_input", s);
			attr->sensor = OCC_INIT_ATTR(attr->name, 0444,
						     show_घातer, शून्य, 3, i);
			attr++;
		पूर्ण

		s = sensors->घातer.num_sensors + 1;
	पूर्ण

	अगर (sensors->caps.num_sensors >= 1) अणु
		snम_लिखो(attr->name, माप(attr->name), "power%d_label", s);
		attr->sensor = OCC_INIT_ATTR(attr->name, 0444, show_caps, शून्य,
					     0, 0);
		attr++;

		snम_लिखो(attr->name, माप(attr->name), "power%d_cap", s);
		attr->sensor = OCC_INIT_ATTR(attr->name, 0444, show_caps, शून्य,
					     1, 0);
		attr++;

		snम_लिखो(attr->name, माप(attr->name), "power%d_input", s);
		attr->sensor = OCC_INIT_ATTR(attr->name, 0444, show_caps, शून्य,
					     2, 0);
		attr++;

		snम_लिखो(attr->name, माप(attr->name),
			 "power%d_cap_not_redundant", s);
		attr->sensor = OCC_INIT_ATTR(attr->name, 0444, show_caps, शून्य,
					     3, 0);
		attr++;

		snम_लिखो(attr->name, माप(attr->name), "power%d_cap_max", s);
		attr->sensor = OCC_INIT_ATTR(attr->name, 0444, show_caps, शून्य,
					     4, 0);
		attr++;

		snम_लिखो(attr->name, माप(attr->name), "power%d_cap_min", s);
		attr->sensor = OCC_INIT_ATTR(attr->name, 0444, show_caps, शून्य,
					     5, 0);
		attr++;

		snम_लिखो(attr->name, माप(attr->name), "power%d_cap_user",
			 s);
		attr->sensor = OCC_INIT_ATTR(attr->name, 0644, show_caps,
					     occ_store_caps_user, 6, 0);
		attr++;

		अगर (sensors->caps.version > 1) अणु
			snम_लिखो(attr->name, माप(attr->name),
				 "power%d_cap_user_source", s);
			attr->sensor = OCC_INIT_ATTR(attr->name, 0444,
						     show_caps, शून्य, 7, 0);
			attr++;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < sensors->extended.num_sensors; ++i) अणु
		s = i + 1;

		snम_लिखो(attr->name, माप(attr->name), "extn%d_label", s);
		attr->sensor = OCC_INIT_ATTR(attr->name, 0444,
					     occ_show_extended, शून्य, 0, i);
		attr++;

		snम_लिखो(attr->name, माप(attr->name), "extn%d_flags", s);
		attr->sensor = OCC_INIT_ATTR(attr->name, 0444,
					     occ_show_extended, शून्य, 1, i);
		attr++;

		snम_लिखो(attr->name, माप(attr->name), "extn%d_input", s);
		attr->sensor = OCC_INIT_ATTR(attr->name, 0444,
					     occ_show_extended, शून्य, 2, i);
		attr++;
	पूर्ण

	/* put the sensors in the group */
	क्रम (i = 0; i < num_attrs; ++i) अणु
		sysfs_attr_init(&occ->attrs[i].sensor.dev_attr.attr);
		occ->group.attrs[i] = &occ->attrs[i].sensor.dev_attr.attr;
	पूर्ण

	वापस 0;
पूर्ण

/* only need to करो this once at startup, as OCC won't change sensors on us */
अटल व्योम occ_parse_poll_response(काष्ठा occ *occ)
अणु
	अचिन्हित पूर्णांक i, old_offset, offset = 0, size = 0;
	काष्ठा occ_sensor *sensor;
	काष्ठा occ_sensors *sensors = &occ->sensors;
	काष्ठा occ_response *resp = &occ->resp;
	काष्ठा occ_poll_response *poll =
		(काष्ठा occ_poll_response *)&resp->data[0];
	काष्ठा occ_poll_response_header *header = &poll->header;
	काष्ठा occ_sensor_data_block *block = &poll->block;

	dev_info(occ->bus_dev, "OCC found, code level: %.16s\n",
		 header->occ_code_level);

	क्रम (i = 0; i < header->num_sensor_data_blocks; ++i) अणु
		block = (काष्ठा occ_sensor_data_block *)((u8 *)block + offset);
		old_offset = offset;
		offset = (block->header.num_sensors *
			  block->header.sensor_length) + माप(block->header);
		size += offset;

		/* validate all the length/size fields */
		अगर ((size + माप(*header)) >= OCC_RESP_DATA_BYTES) अणु
			dev_warn(occ->bus_dev, "exceeded response buffer\n");
			वापस;
		पूर्ण

		dev_dbg(occ->bus_dev, " %04x..%04x: %.4s (%d sensors)\n",
			old_offset, offset - 1, block->header.eye_catcher,
			block->header.num_sensors);

		/* match sensor block type */
		अगर (म_भेदन(block->header.eye_catcher, "TEMP", 4) == 0)
			sensor = &sensors->temp;
		अन्यथा अगर (म_भेदन(block->header.eye_catcher, "FREQ", 4) == 0)
			sensor = &sensors->freq;
		अन्यथा अगर (म_भेदन(block->header.eye_catcher, "POWR", 4) == 0)
			sensor = &sensors->घातer;
		अन्यथा अगर (म_भेदन(block->header.eye_catcher, "CAPS", 4) == 0)
			sensor = &sensors->caps;
		अन्यथा अगर (म_भेदन(block->header.eye_catcher, "EXTN", 4) == 0)
			sensor = &sensors->extended;
		अन्यथा अणु
			dev_warn(occ->bus_dev, "sensor not supported %.4s\n",
				 block->header.eye_catcher);
			जारी;
		पूर्ण

		sensor->num_sensors = block->header.num_sensors;
		sensor->version = block->header.sensor_क्रमmat;
		sensor->data = &block->data;
	पूर्ण

	dev_dbg(occ->bus_dev, "Max resp size: %u+%zd=%zd\n", size,
		माप(*header), size + माप(*header));
पूर्ण

पूर्णांक occ_setup(काष्ठा occ *occ, स्थिर अक्षर *name)
अणु
	पूर्णांक rc;

	mutex_init(&occ->lock);
	occ->groups[0] = &occ->group;

	/* no need to lock */
	rc = occ_poll(occ);
	अगर (rc == -ESHUTDOWN) अणु
		dev_info(occ->bus_dev, "host is not ready\n");
		वापस rc;
	पूर्ण अन्यथा अगर (rc < 0) अणु
		dev_err(occ->bus_dev, "failed to get OCC poll response: %d\n",
			rc);
		वापस rc;
	पूर्ण

	occ->next_update = jअगरfies + OCC_UPDATE_FREQUENCY;
	occ_parse_poll_response(occ);

	rc = occ_setup_sensor_attrs(occ);
	अगर (rc) अणु
		dev_err(occ->bus_dev, "failed to setup sensor attrs: %d\n",
			rc);
		वापस rc;
	पूर्ण

	occ->hwmon = devm_hwmon_device_रेजिस्टर_with_groups(occ->bus_dev, name,
							    occ, occ->groups);
	अगर (IS_ERR(occ->hwmon)) अणु
		rc = PTR_ERR(occ->hwmon);
		dev_err(occ->bus_dev, "failed to register hwmon device: %d\n",
			rc);
		वापस rc;
	पूर्ण

	rc = occ_setup_sysfs(occ);
	अगर (rc)
		dev_err(occ->bus_dev, "failed to setup sysfs: %d\n", rc);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(occ_setup);

MODULE_AUTHOR("Eddie James <eajames@linux.ibm.com>");
MODULE_DESCRIPTION("Common OCC hwmon code");
MODULE_LICENSE("GPL");
