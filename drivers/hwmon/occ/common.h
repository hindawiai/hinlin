<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright IBM Corp 2019 */

#अगर_अघोषित OCC_COMMON_H
#घोषणा OCC_COMMON_H

#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sysfs.h>

काष्ठा device;

#घोषणा OCC_RESP_DATA_BYTES		4089

/*
 * Same response क्रमmat क्रम all OCC versions.
 * Allocate the largest possible response.
 */
काष्ठा occ_response अणु
	u8 seq_no;
	u8 cmd_type;
	u8 वापस_status;
	__be16 data_length;
	u8 data[OCC_RESP_DATA_BYTES];
	__be16 checksum;
पूर्ण __packed;

काष्ठा occ_sensor_data_block_header अणु
	u8 eye_catcher[4];
	u8 reserved;
	u8 sensor_क्रमmat;
	u8 sensor_length;
	u8 num_sensors;
पूर्ण __packed;

काष्ठा occ_sensor_data_block अणु
	काष्ठा occ_sensor_data_block_header header;
	u32 data;
पूर्ण __packed;

काष्ठा occ_poll_response_header अणु
	u8 status;
	u8 ext_status;
	u8 occs_present;
	u8 config_data;
	u8 occ_state;
	u8 mode;
	u8 ips_status;
	u8 error_log_id;
	__be32 error_log_start_address;
	__be16 error_log_length;
	u16 reserved;
	u8 occ_code_level[16];
	u8 eye_catcher[6];
	u8 num_sensor_data_blocks;
	u8 sensor_data_block_header_version;
पूर्ण __packed;

काष्ठा occ_poll_response अणु
	काष्ठा occ_poll_response_header header;
	काष्ठा occ_sensor_data_block block;
पूर्ण __packed;

काष्ठा occ_sensor अणु
	u8 num_sensors;
	u8 version;
	व्योम *data;	/* poपूर्णांकer to sensor data start within response */
पूर्ण;

/*
 * OCC only provides one sensor data block of each type, but any number of
 * sensors within that block.
 */
काष्ठा occ_sensors अणु
	काष्ठा occ_sensor temp;
	काष्ठा occ_sensor freq;
	काष्ठा occ_sensor घातer;
	काष्ठा occ_sensor caps;
	काष्ठा occ_sensor extended;
पूर्ण;

/*
 * Use our own attribute काष्ठा so we can dynamically allocate space क्रम the
 * name.
 */
काष्ठा occ_attribute अणु
	अक्षर name[32];
	काष्ठा sensor_device_attribute_2 sensor;
पूर्ण;

काष्ठा occ अणु
	काष्ठा device *bus_dev;

	काष्ठा occ_response resp;
	काष्ठा occ_sensors sensors;

	पूर्णांक घातr_sample_समय_us;	/* average घातer sample समय */
	u8 seq_no;
	u8 poll_cmd_data;		/* to perक्रमm OCC poll command */
	पूर्णांक (*send_cmd)(काष्ठा occ *occ, u8 *cmd);

	अचिन्हित दीर्घ next_update;
	काष्ठा mutex lock;		/* lock OCC access */

	काष्ठा device *hwmon;
	काष्ठा occ_attribute *attrs;
	काष्ठा attribute_group group;
	स्थिर काष्ठा attribute_group *groups[2];

	पूर्णांक error;                      /* final transfer error after retry */
	पूर्णांक last_error;			/* latest transfer error */
	अचिन्हित पूर्णांक error_count;       /* number of xfr errors observed */
	अचिन्हित दीर्घ last_safe;        /* समय OCC entered "safe" state */

	/*
	 * Store the previous state data क्रम comparison in order to notअगरy
	 * sysfs पढ़ोers of state changes.
	 */
	पूर्णांक prev_error;
	u8 prev_stat;
	u8 prev_ext_stat;
	u8 prev_occs_present;
पूर्ण;

पूर्णांक occ_setup(काष्ठा occ *occ, स्थिर अक्षर *name);
पूर्णांक occ_setup_sysfs(काष्ठा occ *occ);
व्योम occ_shutकरोwn(काष्ठा occ *occ);
व्योम occ_sysfs_poll_करोne(काष्ठा occ *occ);
पूर्णांक occ_update_response(काष्ठा occ *occ);

#पूर्ण_अगर /* OCC_COMMON_H */
