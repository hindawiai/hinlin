<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Aपंचांगel maXTouch Touchscreen driver
 *
 * Copyright (C) 2010 Samsung Electronics Co.Ltd
 * Copyright (C) 2011-2014 Aपंचांगel Corporation
 * Copyright (C) 2012 Google, Inc.
 * Copyright (C) 2016 Zodiac Inflight Innovations
 *
 * Author: Joonyoung Shim <jy0922.shim@samsung.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/of.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>
#समावेश <dt-bindings/input/aपंचांगel-maxtouch.h>

/* Firmware files */
#घोषणा MXT_FW_NAME		"maxtouch.fw"
#घोषणा MXT_CFG_NAME		"maxtouch.cfg"
#घोषणा MXT_CFG_MAGIC		"OBP_RAW V1"

/* Registers */
#घोषणा MXT_OBJECT_START	0x07
#घोषणा MXT_OBJECT_SIZE		6
#घोषणा MXT_INFO_CHECKSUM_SIZE	3
#घोषणा MXT_MAX_BLOCK_WRITE	256

/* Object types */
#घोषणा MXT_DEBUG_DIAGNOSTIC_T37	37
#घोषणा MXT_GEN_MESSAGE_T5		5
#घोषणा MXT_GEN_COMMAND_T6		6
#घोषणा MXT_GEN_POWER_T7		7
#घोषणा MXT_GEN_ACQUIRE_T8		8
#घोषणा MXT_GEN_DATASOURCE_T53		53
#घोषणा MXT_TOUCH_MULTI_T9		9
#घोषणा MXT_TOUCH_KEYARRAY_T15		15
#घोषणा MXT_TOUCH_PROXIMITY_T23		23
#घोषणा MXT_TOUCH_PROXKEY_T52		52
#घोषणा MXT_PROCI_GRIPFACE_T20		20
#घोषणा MXT_PROCG_NOISE_T22		22
#घोषणा MXT_PROCI_ONETOUCH_T24		24
#घोषणा MXT_PROCI_TWOTOUCH_T27		27
#घोषणा MXT_PROCI_GRIP_T40		40
#घोषणा MXT_PROCI_PALM_T41		41
#घोषणा MXT_PROCI_TOUCHSUPPRESSION_T42	42
#घोषणा MXT_PROCI_STYLUS_T47		47
#घोषणा MXT_PROCG_NOISESUPPRESSION_T48	48
#घोषणा MXT_SPT_COMMSCONFIG_T18		18
#घोषणा MXT_SPT_GPIOPWM_T19		19
#घोषणा MXT_SPT_SELFTEST_T25		25
#घोषणा MXT_SPT_CTECONFIG_T28		28
#घोषणा MXT_SPT_USERDATA_T38		38
#घोषणा MXT_SPT_DIGITIZER_T43		43
#घोषणा MXT_SPT_MESSAGECOUNT_T44	44
#घोषणा MXT_SPT_CTECONFIG_T46		46
#घोषणा MXT_SPT_DYNAMICCONFIGURATIONCONTAINER_T71 71
#घोषणा MXT_TOUCH_MULTITOUCHSCREEN_T100 100

/* MXT_GEN_MESSAGE_T5 object */
#घोषणा MXT_RPTID_NOMSG		0xff

/* MXT_GEN_COMMAND_T6 field */
#घोषणा MXT_COMMAND_RESET	0
#घोषणा MXT_COMMAND_BACKUPNV	1
#घोषणा MXT_COMMAND_CALIBRATE	2
#घोषणा MXT_COMMAND_REPORTALL	3
#घोषणा MXT_COMMAND_DIAGNOSTIC	5

/* Define क्रम T6 status byte */
#घोषणा MXT_T6_STATUS_RESET	BIT(7)
#घोषणा MXT_T6_STATUS_OFL	BIT(6)
#घोषणा MXT_T6_STATUS_SIGERR	BIT(5)
#घोषणा MXT_T6_STATUS_CAL	BIT(4)
#घोषणा MXT_T6_STATUS_CFGERR	BIT(3)
#घोषणा MXT_T6_STATUS_COMSERR	BIT(2)

/* MXT_GEN_POWER_T7 field */
काष्ठा t7_config अणु
	u8 idle;
	u8 active;
पूर्ण __packed;

#घोषणा MXT_POWER_CFG_RUN		0
#घोषणा MXT_POWER_CFG_DEEPSLEEP		1

/* MXT_TOUCH_MULTI_T9 field */
#घोषणा MXT_T9_CTRL		0
#घोषणा MXT_T9_XSIZE		3
#घोषणा MXT_T9_YSIZE		4
#घोषणा MXT_T9_ORIENT		9
#घोषणा MXT_T9_RANGE		18

/* MXT_TOUCH_MULTI_T9 status */
#घोषणा MXT_T9_UNGRIP		BIT(0)
#घोषणा MXT_T9_SUPPRESS		BIT(1)
#घोषणा MXT_T9_AMP		BIT(2)
#घोषणा MXT_T9_VECTOR		BIT(3)
#घोषणा MXT_T9_MOVE		BIT(4)
#घोषणा MXT_T9_RELEASE		BIT(5)
#घोषणा MXT_T9_PRESS		BIT(6)
#घोषणा MXT_T9_DETECT		BIT(7)

काष्ठा t9_range अणु
	__le16 x;
	__le16 y;
पूर्ण __packed;

/* MXT_TOUCH_MULTI_T9 orient */
#घोषणा MXT_T9_ORIENT_SWITCH	BIT(0)
#घोषणा MXT_T9_ORIENT_INVERTX	BIT(1)
#घोषणा MXT_T9_ORIENT_INVERTY	BIT(2)

/* MXT_SPT_COMMSCONFIG_T18 */
#घोषणा MXT_COMMS_CTRL		0
#घोषणा MXT_COMMS_CMD		1
#घोषणा MXT_COMMS_RETRIGEN	BIT(6)

/* MXT_DEBUG_DIAGNOSTIC_T37 */
#घोषणा MXT_DIAGNOSTIC_PAGEUP	0x01
#घोषणा MXT_DIAGNOSTIC_DELTAS	0x10
#घोषणा MXT_DIAGNOSTIC_REFS	0x11
#घोषणा MXT_DIAGNOSTIC_SIZE	128

#घोषणा MXT_FAMILY_1386			160
#घोषणा MXT1386_COLUMNS			3
#घोषणा MXT1386_PAGES_PER_COLUMN	8

काष्ठा t37_debug अणु
#अगर_घोषित CONFIG_TOUCHSCREEN_ATMEL_MXT_T37
	u8 mode;
	u8 page;
	u8 data[MXT_DIAGNOSTIC_SIZE];
#पूर्ण_अगर
पूर्ण;

/* Define क्रम MXT_GEN_COMMAND_T6 */
#घोषणा MXT_BOOT_VALUE		0xa5
#घोषणा MXT_RESET_VALUE		0x01
#घोषणा MXT_BACKUP_VALUE	0x55

/* T100 Multiple Touch Touchscreen */
#घोषणा MXT_T100_CTRL		0
#घोषणा MXT_T100_CFG1		1
#घोषणा MXT_T100_TCHAUX		3
#घोषणा MXT_T100_XSIZE		9
#घोषणा MXT_T100_XRANGE		13
#घोषणा MXT_T100_YSIZE		20
#घोषणा MXT_T100_YRANGE		24

#घोषणा MXT_T100_CFG_SWITCHXY	BIT(5)
#घोषणा MXT_T100_CFG_INVERTY	BIT(6)
#घोषणा MXT_T100_CFG_INVERTX	BIT(7)

#घोषणा MXT_T100_TCHAUX_VECT	BIT(0)
#घोषणा MXT_T100_TCHAUX_AMPL	BIT(1)
#घोषणा MXT_T100_TCHAUX_AREA	BIT(2)

#घोषणा MXT_T100_DETECT		BIT(7)
#घोषणा MXT_T100_TYPE_MASK	0x70

क्रमागत t100_type अणु
	MXT_T100_TYPE_FINGER		= 1,
	MXT_T100_TYPE_PASSIVE_STYLUS	= 2,
	MXT_T100_TYPE_HOVERING_FINGER	= 4,
	MXT_T100_TYPE_GLOVE		= 5,
	MXT_T100_TYPE_LARGE_TOUCH	= 6,
पूर्ण;

#घोषणा MXT_DISTANCE_ACTIVE_TOUCH	0
#घोषणा MXT_DISTANCE_HOVERING		1

#घोषणा MXT_TOUCH_MAJOR_DEFAULT		1
#घोषणा MXT_PRESSURE_DEFAULT		1

/* Delay बार */
#घोषणा MXT_BACKUP_TIME		50	/* msec */
#घोषणा MXT_RESET_GPIO_TIME	20	/* msec */
#घोषणा MXT_RESET_INVALID_CHG	100	/* msec */
#घोषणा MXT_RESET_TIME		200	/* msec */
#घोषणा MXT_RESET_TIMEOUT	3000	/* msec */
#घोषणा MXT_CRC_TIMEOUT		1000	/* msec */
#घोषणा MXT_FW_RESET_TIME	3000	/* msec */
#घोषणा MXT_FW_CHG_TIMEOUT	300	/* msec */
#घोषणा MXT_WAKEUP_TIME		25	/* msec */

/* Command to unlock bootloader */
#घोषणा MXT_UNLOCK_CMD_MSB	0xaa
#घोषणा MXT_UNLOCK_CMD_LSB	0xdc

/* Bootloader mode status */
#घोषणा MXT_WAITING_BOOTLOAD_CMD	0xc0	/* valid 7 6 bit only */
#घोषणा MXT_WAITING_FRAME_DATA	0x80	/* valid 7 6 bit only */
#घोषणा MXT_FRAME_CRC_CHECK	0x02
#घोषणा MXT_FRAME_CRC_FAIL	0x03
#घोषणा MXT_FRAME_CRC_PASS	0x04
#घोषणा MXT_APP_CRC_FAIL	0x40	/* valid 7 8 bit only */
#घोषणा MXT_BOOT_STATUS_MASK	0x3f
#घोषणा MXT_BOOT_EXTENDED_ID	BIT(5)
#घोषणा MXT_BOOT_ID_MASK	0x1f

/* Touchscreen असलolute values */
#घोषणा MXT_MAX_AREA		0xff

#घोषणा MXT_PIXELS_PER_MM	20

काष्ठा mxt_info अणु
	u8 family_id;
	u8 variant_id;
	u8 version;
	u8 build;
	u8 matrix_xsize;
	u8 matrix_ysize;
	u8 object_num;
पूर्ण;

काष्ठा mxt_object अणु
	u8 type;
	u16 start_address;
	u8 size_minus_one;
	u8 instances_minus_one;
	u8 num_report_ids;
पूर्ण __packed;

काष्ठा mxt_dbg अणु
	u16 t37_address;
	u16 diag_cmd_address;
	काष्ठा t37_debug *t37_buf;
	अचिन्हित पूर्णांक t37_pages;
	अचिन्हित पूर्णांक t37_nodes;

	काष्ठा v4l2_device v4l2;
	काष्ठा v4l2_pix_क्रमmat क्रमmat;
	काष्ठा video_device vdev;
	काष्ठा vb2_queue queue;
	काष्ठा mutex lock;
	पूर्णांक input;
पूर्ण;

क्रमागत v4l_dbg_inमाला_दो अणु
	MXT_V4L_INPUT_DELTAS,
	MXT_V4L_INPUT_REFS,
	MXT_V4L_INPUT_MAX,
पूर्ण;

क्रमागत mxt_suspend_mode अणु
	MXT_SUSPEND_DEEP_SLEEP	= 0,
	MXT_SUSPEND_T9_CTRL	= 1,
पूर्ण;

/* Config update context */
काष्ठा mxt_cfg अणु
	u8 *raw;
	माप_प्रकार raw_size;
	off_t raw_pos;

	u8 *mem;
	माप_प्रकार mem_size;
	पूर्णांक start_ofs;

	काष्ठा mxt_info info;
पूर्ण;

/* Each client has this additional data */
काष्ठा mxt_data अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input_dev;
	अक्षर phys[64];		/* device physical location */
	काष्ठा mxt_object *object_table;
	काष्ठा mxt_info *info;
	व्योम *raw_info_block;
	अचिन्हित पूर्णांक irq;
	अचिन्हित पूर्णांक max_x;
	अचिन्हित पूर्णांक max_y;
	bool invertx;
	bool inverty;
	bool xy_चयन;
	u8 xsize;
	u8 ysize;
	bool in_bootloader;
	u16 mem_size;
	u8 t100_aux_ampl;
	u8 t100_aux_area;
	u8 t100_aux_vect;
	u8 max_reportid;
	u32 config_crc;
	u32 info_crc;
	u8 bootloader_addr;
	u8 *msg_buf;
	u8 t6_status;
	bool update_input;
	u8 last_message_count;
	u8 num_touchids;
	u8 multitouch;
	काष्ठा t7_config t7_cfg;
	काष्ठा mxt_dbg dbg;
	काष्ठा regulator_bulk_data regulators[2];
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा gpio_desc *wake_gpio;
	bool use_retrigen_workaround;

	/* Cached parameters from object table */
	u16 T5_address;
	u8 T5_msg_size;
	u8 T6_reportid;
	u16 T6_address;
	u16 T7_address;
	u16 T71_address;
	u8 T9_reportid_min;
	u8 T9_reportid_max;
	u16 T18_address;
	u8 T19_reportid;
	u16 T44_address;
	u8 T100_reportid_min;
	u8 T100_reportid_max;

	/* क्रम fw update in bootloader */
	काष्ठा completion bl_completion;

	/* क्रम reset handling */
	काष्ठा completion reset_completion;

	/* क्रम config update handling */
	काष्ठा completion crc_completion;

	u32 *t19_keymap;
	अचिन्हित पूर्णांक t19_num_keys;

	क्रमागत mxt_suspend_mode suspend_mode;

	u32 wakeup_method;
पूर्ण;

काष्ठा mxt_vb2_buffer अणु
	काष्ठा vb2_buffer	vb;
	काष्ठा list_head	list;
पूर्ण;

अटल माप_प्रकार mxt_obj_size(स्थिर काष्ठा mxt_object *obj)
अणु
	वापस obj->size_minus_one + 1;
पूर्ण

अटल माप_प्रकार mxt_obj_instances(स्थिर काष्ठा mxt_object *obj)
अणु
	वापस obj->instances_minus_one + 1;
पूर्ण

अटल bool mxt_object_पढ़ोable(अचिन्हित पूर्णांक type)
अणु
	चयन (type) अणु
	हाल MXT_GEN_COMMAND_T6:
	हाल MXT_GEN_POWER_T7:
	हाल MXT_GEN_ACQUIRE_T8:
	हाल MXT_GEN_DATASOURCE_T53:
	हाल MXT_TOUCH_MULTI_T9:
	हाल MXT_TOUCH_KEYARRAY_T15:
	हाल MXT_TOUCH_PROXIMITY_T23:
	हाल MXT_TOUCH_PROXKEY_T52:
	हाल MXT_TOUCH_MULTITOUCHSCREEN_T100:
	हाल MXT_PROCI_GRIPFACE_T20:
	हाल MXT_PROCG_NOISE_T22:
	हाल MXT_PROCI_ONETOUCH_T24:
	हाल MXT_PROCI_TWOTOUCH_T27:
	हाल MXT_PROCI_GRIP_T40:
	हाल MXT_PROCI_PALM_T41:
	हाल MXT_PROCI_TOUCHSUPPRESSION_T42:
	हाल MXT_PROCI_STYLUS_T47:
	हाल MXT_PROCG_NOISESUPPRESSION_T48:
	हाल MXT_SPT_COMMSCONFIG_T18:
	हाल MXT_SPT_GPIOPWM_T19:
	हाल MXT_SPT_SELFTEST_T25:
	हाल MXT_SPT_CTECONFIG_T28:
	हाल MXT_SPT_USERDATA_T38:
	हाल MXT_SPT_DIGITIZER_T43:
	हाल MXT_SPT_CTECONFIG_T46:
	हाल MXT_SPT_DYNAMICCONFIGURATIONCONTAINER_T71:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम mxt_dump_message(काष्ठा mxt_data *data, u8 *message)
अणु
	dev_dbg(&data->client->dev, "message: %*ph\n",
		data->T5_msg_size, message);
पूर्ण

अटल पूर्णांक mxt_रुको_क्रम_completion(काष्ठा mxt_data *data,
				   काष्ठा completion *comp,
				   अचिन्हित पूर्णांक समयout_ms)
अणु
	काष्ठा device *dev = &data->client->dev;
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(समयout_ms);
	दीर्घ ret;

	ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(comp, समयout);
	अगर (ret < 0) अणु
		वापस ret;
	पूर्ण अन्यथा अगर (ret == 0) अणु
		dev_err(dev, "Wait for completion timed out.\n");
		वापस -ETIMEDOUT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mxt_bootloader_पढ़ो(काष्ठा mxt_data *data,
			       u8 *val, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक ret;
	काष्ठा i2c_msg msg;

	msg.addr = data->bootloader_addr;
	msg.flags = data->client->flags & I2C_M_TEN;
	msg.flags |= I2C_M_RD;
	msg.len = count;
	msg.buf = val;

	ret = i2c_transfer(data->client->adapter, &msg, 1);
	अगर (ret == 1) अणु
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = ret < 0 ? ret : -EIO;
		dev_err(&data->client->dev, "%s: i2c recv failed (%d)\n",
			__func__, ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mxt_bootloader_ग_लिखो(काष्ठा mxt_data *data,
				स्थिर u8 * स्थिर val, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक ret;
	काष्ठा i2c_msg msg;

	msg.addr = data->bootloader_addr;
	msg.flags = data->client->flags & I2C_M_TEN;
	msg.len = count;
	msg.buf = (u8 *)val;

	ret = i2c_transfer(data->client->adapter, &msg, 1);
	अगर (ret == 1) अणु
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = ret < 0 ? ret : -EIO;
		dev_err(&data->client->dev, "%s: i2c send failed (%d)\n",
			__func__, ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mxt_lookup_bootloader_address(काष्ठा mxt_data *data, bool retry)
अणु
	u8 appmode = data->client->addr;
	u8 bootloader;
	u8 family_id = data->info ? data->info->family_id : 0;

	चयन (appmode) अणु
	हाल 0x4a:
	हाल 0x4b:
		/* Chips after 1664S use dअगरferent scheme */
		अगर (retry || family_id >= 0xa2) अणु
			bootloader = appmode - 0x24;
			अवरोध;
		पूर्ण
		fallthrough;	/* क्रम normal हाल */
	हाल 0x4c:
	हाल 0x4d:
	हाल 0x5a:
	हाल 0x5b:
		bootloader = appmode - 0x26;
		अवरोध;

	शेष:
		dev_err(&data->client->dev,
			"Appmode i2c address 0x%02x not found\n",
			appmode);
		वापस -EINVAL;
	पूर्ण

	data->bootloader_addr = bootloader;
	वापस 0;
पूर्ण

अटल पूर्णांक mxt_probe_bootloader(काष्ठा mxt_data *data, bool alt_address)
अणु
	काष्ठा device *dev = &data->client->dev;
	पूर्णांक error;
	u8 val;
	bool crc_failure;

	error = mxt_lookup_bootloader_address(data, alt_address);
	अगर (error)
		वापस error;

	error = mxt_bootloader_पढ़ो(data, &val, 1);
	अगर (error)
		वापस error;

	/* Check app crc fail mode */
	crc_failure = (val & ~MXT_BOOT_STATUS_MASK) == MXT_APP_CRC_FAIL;

	dev_err(dev, "Detected bootloader, status:%02X%s\n",
			val, crc_failure ? ", APP_CRC_FAIL" : "");

	वापस 0;
पूर्ण

अटल u8 mxt_get_bootloader_version(काष्ठा mxt_data *data, u8 val)
अणु
	काष्ठा device *dev = &data->client->dev;
	u8 buf[3];

	अगर (val & MXT_BOOT_EXTENDED_ID) अणु
		अगर (mxt_bootloader_पढ़ो(data, &buf[0], 3) != 0) अणु
			dev_err(dev, "%s: i2c failure\n", __func__);
			वापस val;
		पूर्ण

		dev_dbg(dev, "Bootloader ID:%d Version:%d\n", buf[1], buf[2]);

		वापस buf[0];
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "Bootloader ID:%d\n", val & MXT_BOOT_ID_MASK);

		वापस val;
	पूर्ण
पूर्ण

अटल पूर्णांक mxt_check_bootloader(काष्ठा mxt_data *data, अचिन्हित पूर्णांक state,
				bool रुको)
अणु
	काष्ठा device *dev = &data->client->dev;
	u8 val;
	पूर्णांक ret;

recheck:
	अगर (रुको) अणु
		/*
		 * In application update mode, the पूर्णांकerrupt
		 * line संकेतs state transitions. We must रुको क्रम the
		 * CHG निश्चितion beक्रमe पढ़ोing the status byte.
		 * Once the status byte has been पढ़ो, the line is deनिश्चितed.
		 */
		ret = mxt_रुको_क्रम_completion(data, &data->bl_completion,
					      MXT_FW_CHG_TIMEOUT);
		अगर (ret) अणु
			/*
			 * TODO: handle -ERESTARTSYS better by terminating
			 * fw update process beक्रमe वापसing to userspace
			 * by writing length 0x000 to device (अगरf we are in
			 * WAITING_FRAME_DATA state).
			 */
			dev_err(dev, "Update wait error %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = mxt_bootloader_पढ़ो(data, &val, 1);
	अगर (ret)
		वापस ret;

	अगर (state == MXT_WAITING_BOOTLOAD_CMD)
		val = mxt_get_bootloader_version(data, val);

	चयन (state) अणु
	हाल MXT_WAITING_BOOTLOAD_CMD:
	हाल MXT_WAITING_FRAME_DATA:
	हाल MXT_APP_CRC_FAIL:
		val &= ~MXT_BOOT_STATUS_MASK;
		अवरोध;
	हाल MXT_FRAME_CRC_PASS:
		अगर (val == MXT_FRAME_CRC_CHECK) अणु
			जाओ recheck;
		पूर्ण अन्यथा अगर (val == MXT_FRAME_CRC_FAIL) अणु
			dev_err(dev, "Bootloader CRC fail\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (val != state) अणु
		dev_err(dev, "Invalid bootloader state %02X != %02X\n",
			val, state);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxt_send_bootloader_cmd(काष्ठा mxt_data *data, bool unlock)
अणु
	u8 buf[2];

	अगर (unlock) अणु
		buf[0] = MXT_UNLOCK_CMD_LSB;
		buf[1] = MXT_UNLOCK_CMD_MSB;
	पूर्ण अन्यथा अणु
		buf[0] = 0x01;
		buf[1] = 0x01;
	पूर्ण

	वापस mxt_bootloader_ग_लिखो(data, buf, माप(buf));
पूर्ण

अटल bool mxt_wakeup_toggle(काष्ठा i2c_client *client,
			      bool wake_up, bool in_i2c)
अणु
	काष्ठा mxt_data *data = i2c_get_clientdata(client);

	चयन (data->wakeup_method) अणु
	हाल ATMEL_MXT_WAKEUP_I2C_SCL:
		अगर (!in_i2c)
			वापस false;
		अवरोध;

	हाल ATMEL_MXT_WAKEUP_GPIO:
		अगर (in_i2c)
			वापस false;

		gpiod_set_value(data->wake_gpio, wake_up);
		अवरोध;

	शेष:
		वापस false;
	पूर्ण

	अगर (wake_up) अणु
		dev_dbg(&client->dev, "waking up controller\n");

		msleep(MXT_WAKEUP_TIME);
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक __mxt_पढ़ो_reg(काष्ठा i2c_client *client,
			       u16 reg, u16 len, व्योम *val)
अणु
	काष्ठा i2c_msg xfer[2];
	bool retried = false;
	u8 buf[2];
	पूर्णांक ret;

	buf[0] = reg & 0xff;
	buf[1] = (reg >> 8) & 0xff;

	/* Write रेजिस्टर */
	xfer[0].addr = client->addr;
	xfer[0].flags = 0;
	xfer[0].len = 2;
	xfer[0].buf = buf;

	/* Read data */
	xfer[1].addr = client->addr;
	xfer[1].flags = I2C_M_RD;
	xfer[1].len = len;
	xfer[1].buf = val;

retry:
	ret = i2c_transfer(client->adapter, xfer, 2);
	अगर (ret == 2) अणु
		ret = 0;
	पूर्ण अन्यथा अगर (!retried && mxt_wakeup_toggle(client, true, true)) अणु
		retried = true;
		जाओ retry;
	पूर्ण अन्यथा अणु
		अगर (ret >= 0)
			ret = -EIO;
		dev_err(&client->dev, "%s: i2c transfer failed (%d)\n",
			__func__, ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __mxt_ग_लिखो_reg(काष्ठा i2c_client *client, u16 reg, u16 len,
			   स्थिर व्योम *val)
अणु
	bool retried = false;
	u8 *buf;
	माप_प्रकार count;
	पूर्णांक ret;

	count = len + 2;
	buf = kदो_स्मृति(count, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	buf[0] = reg & 0xff;
	buf[1] = (reg >> 8) & 0xff;
	स_नकल(&buf[2], val, len);

retry:
	ret = i2c_master_send(client, buf, count);
	अगर (ret == count) अणु
		ret = 0;
	पूर्ण अन्यथा अगर (!retried && mxt_wakeup_toggle(client, true, true)) अणु
		retried = true;
		जाओ retry;
	पूर्ण अन्यथा अणु
		अगर (ret >= 0)
			ret = -EIO;
		dev_err(&client->dev, "%s: i2c send failed (%d)\n",
			__func__, ret);
	पूर्ण

	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक mxt_ग_लिखो_reg(काष्ठा i2c_client *client, u16 reg, u8 val)
अणु
	वापस __mxt_ग_लिखो_reg(client, reg, 1, &val);
पूर्ण

अटल काष्ठा mxt_object *
mxt_get_object(काष्ठा mxt_data *data, u8 type)
अणु
	काष्ठा mxt_object *object;
	पूर्णांक i;

	क्रम (i = 0; i < data->info->object_num; i++) अणु
		object = data->object_table + i;
		अगर (object->type == type)
			वापस object;
	पूर्ण

	dev_warn(&data->client->dev, "Invalid object type T%u\n", type);
	वापस शून्य;
पूर्ण

अटल व्योम mxt_proc_t6_messages(काष्ठा mxt_data *data, u8 *msg)
अणु
	काष्ठा device *dev = &data->client->dev;
	u8 status = msg[1];
	u32 crc = msg[2] | (msg[3] << 8) | (msg[4] << 16);

	अगर (crc != data->config_crc) अणु
		data->config_crc = crc;
		dev_dbg(dev, "T6 Config Checksum: 0x%06X\n", crc);
	पूर्ण

	complete(&data->crc_completion);

	/* Detect reset */
	अगर (status & MXT_T6_STATUS_RESET)
		complete(&data->reset_completion);

	/* Output debug अगर status has changed */
	अगर (status != data->t6_status)
		dev_dbg(dev, "T6 Status 0x%02X%s%s%s%s%s%s%s\n",
			status,
			status == 0 ? " OK" : "",
			status & MXT_T6_STATUS_RESET ? " RESET" : "",
			status & MXT_T6_STATUS_OFL ? " OFL" : "",
			status & MXT_T6_STATUS_SIGERR ? " SIGERR" : "",
			status & MXT_T6_STATUS_CAL ? " CAL" : "",
			status & MXT_T6_STATUS_CFGERR ? " CFGERR" : "",
			status & MXT_T6_STATUS_COMSERR ? " COMSERR" : "");

	/* Save current status */
	data->t6_status = status;
पूर्ण

अटल पूर्णांक mxt_ग_लिखो_object(काष्ठा mxt_data *data,
				 u8 type, u8 offset, u8 val)
अणु
	काष्ठा mxt_object *object;
	u16 reg;

	object = mxt_get_object(data, type);
	अगर (!object || offset >= mxt_obj_size(object))
		वापस -EINVAL;

	reg = object->start_address;
	वापस mxt_ग_लिखो_reg(data->client, reg + offset, val);
पूर्ण

अटल व्योम mxt_input_button(काष्ठा mxt_data *data, u8 *message)
अणु
	काष्ठा input_dev *input = data->input_dev;
	पूर्णांक i;

	क्रम (i = 0; i < data->t19_num_keys; i++) अणु
		अगर (data->t19_keymap[i] == KEY_RESERVED)
			जारी;

		/* Active-low चयन */
		input_report_key(input, data->t19_keymap[i],
				 !(message[1] & BIT(i)));
	पूर्ण
पूर्ण

अटल व्योम mxt_input_sync(काष्ठा mxt_data *data)
अणु
	input_mt_report_poपूर्णांकer_emulation(data->input_dev,
					  data->t19_num_keys);
	input_sync(data->input_dev);
पूर्ण

अटल व्योम mxt_proc_t9_message(काष्ठा mxt_data *data, u8 *message)
अणु
	काष्ठा device *dev = &data->client->dev;
	काष्ठा input_dev *input_dev = data->input_dev;
	पूर्णांक id;
	u8 status;
	पूर्णांक x;
	पूर्णांक y;
	पूर्णांक area;
	पूर्णांक amplitude;

	id = message[0] - data->T9_reportid_min;
	status = message[1];
	x = (message[2] << 4) | ((message[4] >> 4) & 0xf);
	y = (message[3] << 4) | ((message[4] & 0xf));

	/* Handle 10/12 bit चयनing */
	अगर (data->max_x < 1024)
		x >>= 2;
	अगर (data->max_y < 1024)
		y >>= 2;

	area = message[5];
	amplitude = message[6];

	dev_dbg(dev,
		"[%u] %c%c%c%c%c%c%c%c x: %5u y: %5u area: %3u amp: %3u\n",
		id,
		(status & MXT_T9_DETECT) ? 'D' : '.',
		(status & MXT_T9_PRESS) ? 'P' : '.',
		(status & MXT_T9_RELEASE) ? 'R' : '.',
		(status & MXT_T9_MOVE) ? 'M' : '.',
		(status & MXT_T9_VECTOR) ? 'V' : '.',
		(status & MXT_T9_AMP) ? 'A' : '.',
		(status & MXT_T9_SUPPRESS) ? 'S' : '.',
		(status & MXT_T9_UNGRIP) ? 'U' : '.',
		x, y, area, amplitude);

	input_mt_slot(input_dev, id);

	अगर (status & MXT_T9_DETECT) अणु
		/*
		 * Multiple bits may be set अगर the host is slow to पढ़ो
		 * the status messages, indicating all the events that
		 * have happened.
		 */
		अगर (status & MXT_T9_RELEASE) अणु
			input_mt_report_slot_inactive(input_dev);
			mxt_input_sync(data);
		पूर्ण

		/* अगर active, pressure must be non-zero */
		अगर (!amplitude)
			amplitude = MXT_PRESSURE_DEFAULT;

		/* Touch active */
		input_mt_report_slot_state(input_dev, MT_TOOL_FINGER, 1);
		input_report_असल(input_dev, ABS_MT_POSITION_X, x);
		input_report_असल(input_dev, ABS_MT_POSITION_Y, y);
		input_report_असल(input_dev, ABS_MT_PRESSURE, amplitude);
		input_report_असल(input_dev, ABS_MT_TOUCH_MAJOR, area);
	पूर्ण अन्यथा अणु
		/* Touch no दीर्घer active, बंद out slot */
		input_mt_report_slot_inactive(input_dev);
	पूर्ण

	data->update_input = true;
पूर्ण

अटल व्योम mxt_proc_t100_message(काष्ठा mxt_data *data, u8 *message)
अणु
	काष्ठा device *dev = &data->client->dev;
	काष्ठा input_dev *input_dev = data->input_dev;
	पूर्णांक id;
	u8 status;
	u8 type = 0;
	u16 x;
	u16 y;
	पूर्णांक distance = 0;
	पूर्णांक tool = 0;
	u8 major = 0;
	u8 pressure = 0;
	u8 orientation = 0;

	id = message[0] - data->T100_reportid_min - 2;

	/* ignore SCRSTATUS events */
	अगर (id < 0)
		वापस;

	status = message[1];
	x = get_unaligned_le16(&message[2]);
	y = get_unaligned_le16(&message[4]);

	अगर (status & MXT_T100_DETECT) अणु
		type = (status & MXT_T100_TYPE_MASK) >> 4;

		चयन (type) अणु
		हाल MXT_T100_TYPE_HOVERING_FINGER:
			tool = MT_TOOL_FINGER;
			distance = MXT_DISTANCE_HOVERING;

			अगर (data->t100_aux_vect)
				orientation = message[data->t100_aux_vect];

			अवरोध;

		हाल MXT_T100_TYPE_FINGER:
		हाल MXT_T100_TYPE_GLOVE:
			tool = MT_TOOL_FINGER;
			distance = MXT_DISTANCE_ACTIVE_TOUCH;

			अगर (data->t100_aux_area)
				major = message[data->t100_aux_area];

			अगर (data->t100_aux_ampl)
				pressure = message[data->t100_aux_ampl];

			अगर (data->t100_aux_vect)
				orientation = message[data->t100_aux_vect];

			अवरोध;

		हाल MXT_T100_TYPE_PASSIVE_STYLUS:
			tool = MT_TOOL_PEN;

			/*
			 * Passive stylus is reported with size zero so
			 * hardcode.
			 */
			major = MXT_TOUCH_MAJOR_DEFAULT;

			अगर (data->t100_aux_ampl)
				pressure = message[data->t100_aux_ampl];

			अवरोध;

		हाल MXT_T100_TYPE_LARGE_TOUCH:
			/* Ignore suppressed touch */
			अवरोध;

		शेष:
			dev_dbg(dev, "Unexpected T100 type\n");
			वापस;
		पूर्ण
	पूर्ण

	/*
	 * Values reported should be non-zero अगर tool is touching the
	 * device
	 */
	अगर (!pressure && type != MXT_T100_TYPE_HOVERING_FINGER)
		pressure = MXT_PRESSURE_DEFAULT;

	input_mt_slot(input_dev, id);

	अगर (status & MXT_T100_DETECT) अणु
		dev_dbg(dev, "[%u] type:%u x:%u y:%u a:%02X p:%02X v:%02X\n",
			id, type, x, y, major, pressure, orientation);

		input_mt_report_slot_state(input_dev, tool, 1);
		input_report_असल(input_dev, ABS_MT_POSITION_X, x);
		input_report_असल(input_dev, ABS_MT_POSITION_Y, y);
		input_report_असल(input_dev, ABS_MT_TOUCH_MAJOR, major);
		input_report_असल(input_dev, ABS_MT_PRESSURE, pressure);
		input_report_असल(input_dev, ABS_MT_DISTANCE, distance);
		input_report_असल(input_dev, ABS_MT_ORIENTATION, orientation);
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "[%u] release\n", id);

		/* बंद out slot */
		input_mt_report_slot_inactive(input_dev);
	पूर्ण

	data->update_input = true;
पूर्ण

अटल पूर्णांक mxt_proc_message(काष्ठा mxt_data *data, u8 *message)
अणु
	u8 report_id = message[0];

	अगर (report_id == MXT_RPTID_NOMSG)
		वापस 0;

	अगर (report_id == data->T6_reportid) अणु
		mxt_proc_t6_messages(data, message);
	पूर्ण अन्यथा अगर (!data->input_dev) अणु
		/*
		 * Do not report events अगर input device
		 * is not yet रेजिस्टरed.
		 */
		mxt_dump_message(data, message);
	पूर्ण अन्यथा अगर (report_id >= data->T9_reportid_min &&
		   report_id <= data->T9_reportid_max) अणु
		mxt_proc_t9_message(data, message);
	पूर्ण अन्यथा अगर (report_id >= data->T100_reportid_min &&
		   report_id <= data->T100_reportid_max) अणु
		mxt_proc_t100_message(data, message);
	पूर्ण अन्यथा अगर (report_id == data->T19_reportid) अणु
		mxt_input_button(data, message);
		data->update_input = true;
	पूर्ण अन्यथा अणु
		mxt_dump_message(data, message);
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक mxt_पढ़ो_and_process_messages(काष्ठा mxt_data *data, u8 count)
अणु
	काष्ठा device *dev = &data->client->dev;
	पूर्णांक ret;
	पूर्णांक i;
	u8 num_valid = 0;

	/* Safety check क्रम msg_buf */
	अगर (count > data->max_reportid)
		वापस -EINVAL;

	/* Process reमुख्यing messages अगर necessary */
	ret = __mxt_पढ़ो_reg(data->client, data->T5_address,
				data->T5_msg_size * count, data->msg_buf);
	अगर (ret) अणु
		dev_err(dev, "Failed to read %u messages (%d)\n", count, ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0;  i < count; i++) अणु
		ret = mxt_proc_message(data,
			data->msg_buf + data->T5_msg_size * i);

		अगर (ret == 1)
			num_valid++;
	पूर्ण

	/* वापस number of messages पढ़ो */
	वापस num_valid;
पूर्ण

अटल irqवापस_t mxt_process_messages_t44(काष्ठा mxt_data *data)
अणु
	काष्ठा device *dev = &data->client->dev;
	पूर्णांक ret;
	u8 count, num_left;

	/* Read T44 and T5 together */
	ret = __mxt_पढ़ो_reg(data->client, data->T44_address,
		data->T5_msg_size + 1, data->msg_buf);
	अगर (ret) अणु
		dev_err(dev, "Failed to read T44 and T5 (%d)\n", ret);
		वापस IRQ_NONE;
	पूर्ण

	count = data->msg_buf[0];

	/*
	 * This condition may be caused by the CHG line being configured in
	 * Mode 0. It results in unnecessary I2C operations but it is benign.
	 */
	अगर (count == 0)
		वापस IRQ_NONE;

	अगर (count > data->max_reportid) अणु
		dev_warn(dev, "T44 count %d exceeded max report id\n", count);
		count = data->max_reportid;
	पूर्ण

	/* Process first message */
	ret = mxt_proc_message(data, data->msg_buf + 1);
	अगर (ret < 0) अणु
		dev_warn(dev, "Unexpected invalid message\n");
		वापस IRQ_NONE;
	पूर्ण

	num_left = count - 1;

	/* Process reमुख्यing messages अगर necessary */
	अगर (num_left) अणु
		ret = mxt_पढ़ो_and_process_messages(data, num_left);
		अगर (ret < 0)
			जाओ end;
		अन्यथा अगर (ret != num_left)
			dev_warn(dev, "Unexpected invalid message\n");
	पूर्ण

end:
	अगर (data->update_input) अणु
		mxt_input_sync(data);
		data->update_input = false;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mxt_process_messages_until_invalid(काष्ठा mxt_data *data)
अणु
	काष्ठा device *dev = &data->client->dev;
	पूर्णांक count, पढ़ो;
	u8 tries = 2;

	count = data->max_reportid;

	/* Read messages until we क्रमce an invalid */
	करो अणु
		पढ़ो = mxt_पढ़ो_and_process_messages(data, count);
		अगर (पढ़ो < count)
			वापस 0;
	पूर्ण जबतक (--tries);

	अगर (data->update_input) अणु
		mxt_input_sync(data);
		data->update_input = false;
	पूर्ण

	dev_err(dev, "CHG pin isn't cleared\n");
	वापस -EBUSY;
पूर्ण

अटल irqवापस_t mxt_process_messages(काष्ठा mxt_data *data)
अणु
	पूर्णांक total_handled, num_handled;
	u8 count = data->last_message_count;

	अगर (count < 1 || count > data->max_reportid)
		count = 1;

	/* include final invalid message */
	total_handled = mxt_पढ़ो_and_process_messages(data, count + 1);
	अगर (total_handled < 0)
		वापस IRQ_NONE;
	/* अगर there were invalid messages, then we are करोne */
	अन्यथा अगर (total_handled <= count)
		जाओ update_count;

	/* keep पढ़ोing two msgs until one is invalid or reportid limit */
	करो अणु
		num_handled = mxt_पढ़ो_and_process_messages(data, 2);
		अगर (num_handled < 0)
			वापस IRQ_NONE;

		total_handled += num_handled;

		अगर (num_handled < 2)
			अवरोध;
	पूर्ण जबतक (total_handled < data->num_touchids);

update_count:
	data->last_message_count = total_handled;

	अगर (data->update_input) अणु
		mxt_input_sync(data);
		data->update_input = false;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mxt_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mxt_data *data = dev_id;

	अगर (data->in_bootloader) अणु
		/* bootloader state transition completion */
		complete(&data->bl_completion);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (!data->object_table)
		वापस IRQ_HANDLED;

	अगर (data->T44_address) अणु
		वापस mxt_process_messages_t44(data);
	पूर्ण अन्यथा अणु
		वापस mxt_process_messages(data);
	पूर्ण
पूर्ण

अटल पूर्णांक mxt_t6_command(काष्ठा mxt_data *data, u16 cmd_offset,
			  u8 value, bool रुको)
अणु
	u16 reg;
	u8 command_रेजिस्टर;
	पूर्णांक समयout_counter = 0;
	पूर्णांक ret;

	reg = data->T6_address + cmd_offset;

	ret = mxt_ग_लिखो_reg(data->client, reg, value);
	अगर (ret)
		वापस ret;

	अगर (!रुको)
		वापस 0;

	करो अणु
		msleep(20);
		ret = __mxt_पढ़ो_reg(data->client, reg, 1, &command_रेजिस्टर);
		अगर (ret)
			वापस ret;
	पूर्ण जबतक (command_रेजिस्टर != 0 && समयout_counter++ <= 100);

	अगर (समयout_counter > 100) अणु
		dev_err(&data->client->dev, "Command failed!\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxt_acquire_irq(काष्ठा mxt_data *data)
अणु
	पूर्णांक error;

	enable_irq(data->irq);

	अगर (data->use_retrigen_workaround) अणु
		error = mxt_process_messages_until_invalid(data);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxt_soft_reset(काष्ठा mxt_data *data)
अणु
	काष्ठा device *dev = &data->client->dev;
	पूर्णांक ret = 0;

	dev_info(dev, "Resetting device\n");

	disable_irq(data->irq);

	reinit_completion(&data->reset_completion);

	ret = mxt_t6_command(data, MXT_COMMAND_RESET, MXT_RESET_VALUE, false);
	अगर (ret)
		वापस ret;

	/* Ignore CHG line क्रम 100ms after reset */
	msleep(MXT_RESET_INVALID_CHG);

	mxt_acquire_irq(data);

	ret = mxt_रुको_क्रम_completion(data, &data->reset_completion,
				      MXT_RESET_TIMEOUT);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम mxt_update_crc(काष्ठा mxt_data *data, u8 cmd, u8 value)
अणु
	/*
	 * On failure, CRC is set to 0 and config will always be
	 * करोwnloaded.
	 */
	data->config_crc = 0;
	reinit_completion(&data->crc_completion);

	mxt_t6_command(data, cmd, value, true);

	/*
	 * Wait क्रम crc message. On failure, CRC is set to 0 and config will
	 * always be करोwnloaded.
	 */
	mxt_रुको_क्रम_completion(data, &data->crc_completion, MXT_CRC_TIMEOUT);
पूर्ण

अटल व्योम mxt_calc_crc24(u32 *crc, u8 firstbyte, u8 secondbyte)
अणु
	अटल स्थिर अचिन्हित पूर्णांक crcpoly = 0x80001B;
	u32 result;
	u32 data_word;

	data_word = (secondbyte << 8) | firstbyte;
	result = ((*crc << 1) ^ data_word);

	अगर (result & 0x1000000)
		result ^= crcpoly;

	*crc = result;
पूर्ण

अटल u32 mxt_calculate_crc(u8 *base, off_t start_off, off_t end_off)
अणु
	u32 crc = 0;
	u8 *ptr = base + start_off;
	u8 *last_val = base + end_off - 1;

	अगर (end_off < start_off)
		वापस -EINVAL;

	जबतक (ptr < last_val) अणु
		mxt_calc_crc24(&crc, *ptr, *(ptr + 1));
		ptr += 2;
	पूर्ण

	/* अगर len is odd, fill the last byte with 0 */
	अगर (ptr == last_val)
		mxt_calc_crc24(&crc, *ptr, 0);

	/* Mask to 24-bit */
	crc &= 0x00FFFFFF;

	वापस crc;
पूर्ण

अटल पूर्णांक mxt_check_retrigen(काष्ठा mxt_data *data)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक error;
	पूर्णांक val;
	काष्ठा irq_data *irqd;

	data->use_retrigen_workaround = false;

	irqd = irq_get_irq_data(data->irq);
	अगर (!irqd)
		वापस -EINVAL;

	अगर (irqd_is_level_type(irqd))
		वापस 0;

	अगर (data->T18_address) अणु
		error = __mxt_पढ़ो_reg(client,
				       data->T18_address + MXT_COMMS_CTRL,
				       1, &val);
		अगर (error)
			वापस error;

		अगर (val & MXT_COMMS_RETRIGEN)
			वापस 0;
	पूर्ण

	dev_warn(&client->dev, "Enabling RETRIGEN workaround\n");
	data->use_retrigen_workaround = true;
	वापस 0;
पूर्ण

अटल पूर्णांक mxt_prepare_cfg_mem(काष्ठा mxt_data *data, काष्ठा mxt_cfg *cfg)
अणु
	काष्ठा device *dev = &data->client->dev;
	काष्ठा mxt_object *object;
	अचिन्हित पूर्णांक type, instance, size, byte_offset;
	पूर्णांक offset;
	पूर्णांक ret;
	पूर्णांक i;
	u16 reg;
	u8 val;

	जबतक (cfg->raw_pos < cfg->raw_size) अणु
		/* Read type, instance, length */
		ret = माला_पूछो(cfg->raw + cfg->raw_pos, "%x %x %x%n",
			     &type, &instance, &size, &offset);
		अगर (ret == 0) अणु
			/* खातापूर्ण */
			अवरोध;
		पूर्ण अन्यथा अगर (ret != 3) अणु
			dev_err(dev, "Bad format: failed to parse object\n");
			वापस -EINVAL;
		पूर्ण
		cfg->raw_pos += offset;

		object = mxt_get_object(data, type);
		अगर (!object) अणु
			/* Skip object */
			क्रम (i = 0; i < size; i++) अणु
				ret = माला_पूछो(cfg->raw + cfg->raw_pos, "%hhx%n",
					     &val, &offset);
				अगर (ret != 1) अणु
					dev_err(dev, "Bad format in T%d at %d\n",
						type, i);
					वापस -EINVAL;
				पूर्ण
				cfg->raw_pos += offset;
			पूर्ण
			जारी;
		पूर्ण

		अगर (size > mxt_obj_size(object)) अणु
			/*
			 * Either we are in fallback mode due to wrong
			 * config or config from a later fw version,
			 * or the file is corrupt or hand-edited.
			 */
			dev_warn(dev, "Discarding %zu byte(s) in T%u\n",
				 size - mxt_obj_size(object), type);
		पूर्ण अन्यथा अगर (mxt_obj_size(object) > size) अणु
			/*
			 * If firmware is upgraded, new bytes may be added to
			 * end of objects. It is generally क्रमward compatible
			 * to zero these bytes - previous behaviour will be
			 * retained. However this करोes invalidate the CRC and
			 * will क्रमce fallback mode until the configuration is
			 * updated. We warn here but करो nothing अन्यथा - the
			 * दो_स्मृति has zeroed the entire configuration.
			 */
			dev_warn(dev, "Zeroing %zu byte(s) in T%d\n",
				 mxt_obj_size(object) - size, type);
		पूर्ण

		अगर (instance >= mxt_obj_instances(object)) अणु
			dev_err(dev, "Object instances exceeded!\n");
			वापस -EINVAL;
		पूर्ण

		reg = object->start_address + mxt_obj_size(object) * instance;

		क्रम (i = 0; i < size; i++) अणु
			ret = माला_पूछो(cfg->raw + cfg->raw_pos, "%hhx%n",
				     &val,
				     &offset);
			अगर (ret != 1) अणु
				dev_err(dev, "Bad format in T%d at %d\n",
					type, i);
				वापस -EINVAL;
			पूर्ण
			cfg->raw_pos += offset;

			अगर (i > mxt_obj_size(object))
				जारी;

			byte_offset = reg + i - cfg->start_ofs;

			अगर (byte_offset >= 0 && byte_offset < cfg->mem_size) अणु
				*(cfg->mem + byte_offset) = val;
			पूर्ण अन्यथा अणु
				dev_err(dev, "Bad object: reg:%d, T%d, ofs=%d\n",
					reg, object->type, byte_offset);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxt_upload_cfg_mem(काष्ठा mxt_data *data, काष्ठा mxt_cfg *cfg)
अणु
	अचिन्हित पूर्णांक byte_offset = 0;
	पूर्णांक error;

	/* Write configuration as blocks */
	जबतक (byte_offset < cfg->mem_size) अणु
		अचिन्हित पूर्णांक size = cfg->mem_size - byte_offset;

		अगर (size > MXT_MAX_BLOCK_WRITE)
			size = MXT_MAX_BLOCK_WRITE;

		error = __mxt_ग_लिखो_reg(data->client,
					cfg->start_ofs + byte_offset,
					size, cfg->mem + byte_offset);
		अगर (error) अणु
			dev_err(&data->client->dev,
				"Config write error, ret=%d\n", error);
			वापस error;
		पूर्ण

		byte_offset += size;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxt_init_t7_घातer_cfg(काष्ठा mxt_data *data);

/*
 * mxt_update_cfg - करोwnload configuration to chip
 *
 * Aपंचांगel Raw Config File Format
 *
 * The first four lines of the raw config file contain:
 *  1) Version
 *  2) Chip ID Inक्रमmation (first 7 bytes of device memory)
 *  3) Chip Inक्रमmation Block 24-bit CRC Checksum
 *  4) Chip Configuration 24-bit CRC Checksum
 *
 * The rest of the file consists of one line per object instance:
 *   <TYPE> <INSTANCE> <SIZE> <CONTENTS>
 *
 *   <TYPE> - 2-byte object type as hex
 *   <INSTANCE> - 2-byte object instance number as hex
 *   <SIZE> - 2-byte object size as hex
 *   <CONTENTS> - array of <SIZE> 1-byte hex values
 */
अटल पूर्णांक mxt_update_cfg(काष्ठा mxt_data *data, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा device *dev = &data->client->dev;
	काष्ठा mxt_cfg cfg;
	पूर्णांक ret;
	पूर्णांक offset;
	पूर्णांक i;
	u32 info_crc, config_crc, calculated_crc;
	u16 crc_start = 0;

	/* Make zero terminated copy of the OBP_RAW file */
	cfg.raw = kmemdup_nul(fw->data, fw->size, GFP_KERNEL);
	अगर (!cfg.raw)
		वापस -ENOMEM;

	cfg.raw_size = fw->size;

	mxt_update_crc(data, MXT_COMMAND_REPORTALL, 1);

	अगर (म_भेदन(cfg.raw, MXT_CFG_MAGIC, म_माप(MXT_CFG_MAGIC))) अणु
		dev_err(dev, "Unrecognised config file\n");
		ret = -EINVAL;
		जाओ release_raw;
	पूर्ण

	cfg.raw_pos = म_माप(MXT_CFG_MAGIC);

	/* Load inक्रमmation block and check */
	क्रम (i = 0; i < माप(काष्ठा mxt_info); i++) अणु
		ret = माला_पूछो(cfg.raw + cfg.raw_pos, "%hhx%n",
			     (अचिन्हित अक्षर *)&cfg.info + i,
			     &offset);
		अगर (ret != 1) अणु
			dev_err(dev, "Bad format\n");
			ret = -EINVAL;
			जाओ release_raw;
		पूर्ण

		cfg.raw_pos += offset;
	पूर्ण

	अगर (cfg.info.family_id != data->info->family_id) अणु
		dev_err(dev, "Family ID mismatch!\n");
		ret = -EINVAL;
		जाओ release_raw;
	पूर्ण

	अगर (cfg.info.variant_id != data->info->variant_id) अणु
		dev_err(dev, "Variant ID mismatch!\n");
		ret = -EINVAL;
		जाओ release_raw;
	पूर्ण

	/* Read CRCs */
	ret = माला_पूछो(cfg.raw + cfg.raw_pos, "%x%n", &info_crc, &offset);
	अगर (ret != 1) अणु
		dev_err(dev, "Bad format: failed to parse Info CRC\n");
		ret = -EINVAL;
		जाओ release_raw;
	पूर्ण
	cfg.raw_pos += offset;

	ret = माला_पूछो(cfg.raw + cfg.raw_pos, "%x%n", &config_crc, &offset);
	अगर (ret != 1) अणु
		dev_err(dev, "Bad format: failed to parse Config CRC\n");
		ret = -EINVAL;
		जाओ release_raw;
	पूर्ण
	cfg.raw_pos += offset;

	/*
	 * The Info Block CRC is calculated over mxt_info and the object
	 * table. If it करोes not match then we are trying to load the
	 * configuration from a dअगरferent chip or firmware version, so
	 * the configuration CRC is invalid anyway.
	 */
	अगर (info_crc == data->info_crc) अणु
		अगर (config_crc == 0 || data->config_crc == 0) अणु
			dev_info(dev, "CRC zero, attempting to apply config\n");
		पूर्ण अन्यथा अगर (config_crc == data->config_crc) अणु
			dev_dbg(dev, "Config CRC 0x%06X: OK\n",
				 data->config_crc);
			ret = 0;
			जाओ release_raw;
		पूर्ण अन्यथा अणु
			dev_info(dev, "Config CRC 0x%06X: does not match file 0x%06X\n",
				 data->config_crc, config_crc);
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_warn(dev,
			 "Warning: Info CRC error - device=0x%06X file=0x%06X\n",
			 data->info_crc, info_crc);
	पूर्ण

	/* Malloc memory to store configuration */
	cfg.start_ofs = MXT_OBJECT_START +
			data->info->object_num * माप(काष्ठा mxt_object) +
			MXT_INFO_CHECKSUM_SIZE;
	cfg.mem_size = data->mem_size - cfg.start_ofs;
	cfg.mem = kzalloc(cfg.mem_size, GFP_KERNEL);
	अगर (!cfg.mem) अणु
		ret = -ENOMEM;
		जाओ release_raw;
	पूर्ण

	ret = mxt_prepare_cfg_mem(data, &cfg);
	अगर (ret)
		जाओ release_mem;

	/* Calculate crc of the received configs (not the raw config file) */
	अगर (data->T71_address)
		crc_start = data->T71_address;
	अन्यथा अगर (data->T7_address)
		crc_start = data->T7_address;
	अन्यथा
		dev_warn(dev, "Could not find CRC start\n");

	अगर (crc_start > cfg.start_ofs) अणु
		calculated_crc = mxt_calculate_crc(cfg.mem,
						   crc_start - cfg.start_ofs,
						   cfg.mem_size);

		अगर (config_crc > 0 && config_crc != calculated_crc)
			dev_warn(dev, "Config CRC in file inconsistent, calculated=%06X, file=%06X\n",
				 calculated_crc, config_crc);
	पूर्ण

	ret = mxt_upload_cfg_mem(data, &cfg);
	अगर (ret)
		जाओ release_mem;

	mxt_update_crc(data, MXT_COMMAND_BACKUPNV, MXT_BACKUP_VALUE);

	ret = mxt_check_retrigen(data);
	अगर (ret)
		जाओ release_mem;

	ret = mxt_soft_reset(data);
	अगर (ret)
		जाओ release_mem;

	dev_info(dev, "Config successfully updated\n");

	/* T7 config may have changed */
	mxt_init_t7_घातer_cfg(data);

release_mem:
	kमुक्त(cfg.mem);
release_raw:
	kमुक्त(cfg.raw);
	वापस ret;
पूर्ण

अटल व्योम mxt_मुक्त_input_device(काष्ठा mxt_data *data)
अणु
	अगर (data->input_dev) अणु
		input_unरेजिस्टर_device(data->input_dev);
		data->input_dev = शून्य;
	पूर्ण
पूर्ण

अटल व्योम mxt_मुक्त_object_table(काष्ठा mxt_data *data)
अणु
#अगर_घोषित CONFIG_TOUCHSCREEN_ATMEL_MXT_T37
	video_unरेजिस्टर_device(&data->dbg.vdev);
	v4l2_device_unरेजिस्टर(&data->dbg.v4l2);
#पूर्ण_अगर
	data->object_table = शून्य;
	data->info = शून्य;
	kमुक्त(data->raw_info_block);
	data->raw_info_block = शून्य;
	kमुक्त(data->msg_buf);
	data->msg_buf = शून्य;
	data->T5_address = 0;
	data->T5_msg_size = 0;
	data->T6_reportid = 0;
	data->T7_address = 0;
	data->T71_address = 0;
	data->T9_reportid_min = 0;
	data->T9_reportid_max = 0;
	data->T18_address = 0;
	data->T19_reportid = 0;
	data->T44_address = 0;
	data->T100_reportid_min = 0;
	data->T100_reportid_max = 0;
	data->max_reportid = 0;
पूर्ण

अटल पूर्णांक mxt_parse_object_table(काष्ठा mxt_data *data,
				  काष्ठा mxt_object *object_table)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक i;
	u8 reportid;
	u16 end_address;

	/* Valid Report IDs start counting from 1 */
	reportid = 1;
	data->mem_size = 0;
	क्रम (i = 0; i < data->info->object_num; i++) अणु
		काष्ठा mxt_object *object = object_table + i;
		u8 min_id, max_id;

		le16_to_cpus(&object->start_address);

		अगर (object->num_report_ids) अणु
			min_id = reportid;
			reportid += object->num_report_ids *
					mxt_obj_instances(object);
			max_id = reportid - 1;
		पूर्ण अन्यथा अणु
			min_id = 0;
			max_id = 0;
		पूर्ण

		dev_dbg(&data->client->dev,
			"T%u Start:%u Size:%zu Instances:%zu Report IDs:%u-%u\n",
			object->type, object->start_address,
			mxt_obj_size(object), mxt_obj_instances(object),
			min_id, max_id);

		चयन (object->type) अणु
		हाल MXT_GEN_MESSAGE_T5:
			अगर (data->info->family_id == 0x80 &&
			    data->info->version < 0x20) अणु
				/*
				 * On mXT224 firmware versions prior to V2.0
				 * पढ़ो and discard unused CRC byte otherwise
				 * DMA पढ़ोs are misaligned.
				 */
				data->T5_msg_size = mxt_obj_size(object);
			पूर्ण अन्यथा अणु
				/* CRC not enabled, so skip last byte */
				data->T5_msg_size = mxt_obj_size(object) - 1;
			पूर्ण
			data->T5_address = object->start_address;
			अवरोध;
		हाल MXT_GEN_COMMAND_T6:
			data->T6_reportid = min_id;
			data->T6_address = object->start_address;
			अवरोध;
		हाल MXT_GEN_POWER_T7:
			data->T7_address = object->start_address;
			अवरोध;
		हाल MXT_SPT_DYNAMICCONFIGURATIONCONTAINER_T71:
			data->T71_address = object->start_address;
			अवरोध;
		हाल MXT_TOUCH_MULTI_T9:
			data->multitouch = MXT_TOUCH_MULTI_T9;
			/* Only handle messages from first T9 instance */
			data->T9_reportid_min = min_id;
			data->T9_reportid_max = min_id +
						object->num_report_ids - 1;
			data->num_touchids = object->num_report_ids;
			अवरोध;
		हाल MXT_SPT_COMMSCONFIG_T18:
			data->T18_address = object->start_address;
			अवरोध;
		हाल MXT_SPT_MESSAGECOUNT_T44:
			data->T44_address = object->start_address;
			अवरोध;
		हाल MXT_SPT_GPIOPWM_T19:
			data->T19_reportid = min_id;
			अवरोध;
		हाल MXT_TOUCH_MULTITOUCHSCREEN_T100:
			data->multitouch = MXT_TOUCH_MULTITOUCHSCREEN_T100;
			data->T100_reportid_min = min_id;
			data->T100_reportid_max = max_id;
			/* first two report IDs reserved */
			data->num_touchids = object->num_report_ids - 2;
			अवरोध;
		पूर्ण

		end_address = object->start_address
			+ mxt_obj_size(object) * mxt_obj_instances(object) - 1;

		अगर (end_address >= data->mem_size)
			data->mem_size = end_address + 1;
	पूर्ण

	/* Store maximum reportid */
	data->max_reportid = reportid;

	/* If T44 exists, T5 position has to be directly after */
	अगर (data->T44_address && (data->T5_address != data->T44_address + 1)) अणु
		dev_err(&client->dev, "Invalid T44 position\n");
		वापस -EINVAL;
	पूर्ण

	data->msg_buf = kसुस्मृति(data->max_reportid,
				data->T5_msg_size, GFP_KERNEL);
	अगर (!data->msg_buf)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक mxt_पढ़ो_info_block(काष्ठा mxt_data *data)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक error;
	माप_प्रकार size;
	व्योम *id_buf, *buf;
	uपूर्णांक8_t num_objects;
	u32 calculated_crc;
	u8 *crc_ptr;

	/* If info block alपढ़ोy allocated, मुक्त it */
	अगर (data->raw_info_block)
		mxt_मुक्त_object_table(data);

	/* Read 7-byte ID inक्रमmation block starting at address 0 */
	size = माप(काष्ठा mxt_info);
	id_buf = kzalloc(size, GFP_KERNEL);
	अगर (!id_buf)
		वापस -ENOMEM;

	error = __mxt_पढ़ो_reg(client, 0, size, id_buf);
	अगर (error)
		जाओ err_मुक्त_mem;

	/* Resize buffer to give space क्रम rest of info block */
	num_objects = ((काष्ठा mxt_info *)id_buf)->object_num;
	size += (num_objects * माप(काष्ठा mxt_object))
		+ MXT_INFO_CHECKSUM_SIZE;

	buf = kपुनः_स्मृति(id_buf, size, GFP_KERNEL);
	अगर (!buf) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण
	id_buf = buf;

	/* Read rest of info block */
	error = __mxt_पढ़ो_reg(client, MXT_OBJECT_START,
			       size - MXT_OBJECT_START,
			       id_buf + MXT_OBJECT_START);
	अगर (error)
		जाओ err_मुक्त_mem;

	/* Extract & calculate checksum */
	crc_ptr = id_buf + size - MXT_INFO_CHECKSUM_SIZE;
	data->info_crc = crc_ptr[0] | (crc_ptr[1] << 8) | (crc_ptr[2] << 16);

	calculated_crc = mxt_calculate_crc(id_buf, 0,
					   size - MXT_INFO_CHECKSUM_SIZE);

	/*
	 * CRC mismatch can be caused by data corruption due to I2C comms
	 * issue or अन्यथा device is not using Object Based Protocol (eg i2c-hid)
	 */
	अगर ((data->info_crc == 0) || (data->info_crc != calculated_crc)) अणु
		dev_err(&client->dev,
			"Info Block CRC error calculated=0x%06X read=0x%06X\n",
			calculated_crc, data->info_crc);
		error = -EIO;
		जाओ err_मुक्त_mem;
	पूर्ण

	data->raw_info_block = id_buf;
	data->info = (काष्ठा mxt_info *)id_buf;

	dev_info(&client->dev,
		 "Family: %u Variant: %u Firmware V%u.%u.%02X Objects: %u\n",
		 data->info->family_id, data->info->variant_id,
		 data->info->version >> 4, data->info->version & 0xf,
		 data->info->build, data->info->object_num);

	/* Parse object table inक्रमmation */
	error = mxt_parse_object_table(data, id_buf + MXT_OBJECT_START);
	अगर (error) अणु
		dev_err(&client->dev, "Error %d parsing object table\n", error);
		mxt_मुक्त_object_table(data);
		जाओ err_मुक्त_mem;
	पूर्ण

	data->object_table = (काष्ठा mxt_object *)(id_buf + MXT_OBJECT_START);

	वापस 0;

err_मुक्त_mem:
	kमुक्त(id_buf);
	वापस error;
पूर्ण

अटल पूर्णांक mxt_पढ़ो_t9_resolution(काष्ठा mxt_data *data)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक error;
	काष्ठा t9_range range;
	अचिन्हित अक्षर orient;
	काष्ठा mxt_object *object;

	object = mxt_get_object(data, MXT_TOUCH_MULTI_T9);
	अगर (!object)
		वापस -EINVAL;

	error = __mxt_पढ़ो_reg(client,
			       object->start_address + MXT_T9_XSIZE,
			       माप(data->xsize), &data->xsize);
	अगर (error)
		वापस error;

	error = __mxt_पढ़ो_reg(client,
			       object->start_address + MXT_T9_YSIZE,
			       माप(data->ysize), &data->ysize);
	अगर (error)
		वापस error;

	error = __mxt_पढ़ो_reg(client,
			       object->start_address + MXT_T9_RANGE,
			       माप(range), &range);
	अगर (error)
		वापस error;

	data->max_x = get_unaligned_le16(&range.x);
	data->max_y = get_unaligned_le16(&range.y);

	error =  __mxt_पढ़ो_reg(client,
				object->start_address + MXT_T9_ORIENT,
				1, &orient);
	अगर (error)
		वापस error;

	data->xy_चयन = orient & MXT_T9_ORIENT_SWITCH;
	data->invertx = orient & MXT_T9_ORIENT_INVERTX;
	data->inverty = orient & MXT_T9_ORIENT_INVERTY;

	वापस 0;
पूर्ण

अटल पूर्णांक mxt_पढ़ो_t100_config(काष्ठा mxt_data *data)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक error;
	काष्ठा mxt_object *object;
	u16 range_x, range_y;
	u8 cfg, tchaux;
	u8 aux;

	object = mxt_get_object(data, MXT_TOUCH_MULTITOUCHSCREEN_T100);
	अगर (!object)
		वापस -EINVAL;

	/* पढ़ो touchscreen dimensions */
	error = __mxt_पढ़ो_reg(client,
			       object->start_address + MXT_T100_XRANGE,
			       माप(range_x), &range_x);
	अगर (error)
		वापस error;

	data->max_x = get_unaligned_le16(&range_x);

	error = __mxt_पढ़ो_reg(client,
			       object->start_address + MXT_T100_YRANGE,
			       माप(range_y), &range_y);
	अगर (error)
		वापस error;

	data->max_y = get_unaligned_le16(&range_y);

	error = __mxt_पढ़ो_reg(client,
			       object->start_address + MXT_T100_XSIZE,
			       माप(data->xsize), &data->xsize);
	अगर (error)
		वापस error;

	error = __mxt_पढ़ो_reg(client,
			       object->start_address + MXT_T100_YSIZE,
			       माप(data->ysize), &data->ysize);
	अगर (error)
		वापस error;

	/* पढ़ो orientation config */
	error =  __mxt_पढ़ो_reg(client,
				object->start_address + MXT_T100_CFG1,
				1, &cfg);
	अगर (error)
		वापस error;

	data->xy_चयन = cfg & MXT_T100_CFG_SWITCHXY;
	data->invertx = cfg & MXT_T100_CFG_INVERTX;
	data->inverty = cfg & MXT_T100_CFG_INVERTY;

	/* allocate aux bytes */
	error =  __mxt_पढ़ो_reg(client,
				object->start_address + MXT_T100_TCHAUX,
				1, &tchaux);
	अगर (error)
		वापस error;

	aux = 6;

	अगर (tchaux & MXT_T100_TCHAUX_VECT)
		data->t100_aux_vect = aux++;

	अगर (tchaux & MXT_T100_TCHAUX_AMPL)
		data->t100_aux_ampl = aux++;

	अगर (tchaux & MXT_T100_TCHAUX_AREA)
		data->t100_aux_area = aux++;

	dev_dbg(&client->dev,
		"T100 aux mappings vect:%u ampl:%u area:%u\n",
		data->t100_aux_vect, data->t100_aux_ampl, data->t100_aux_area);

	वापस 0;
पूर्ण

अटल पूर्णांक mxt_input_खोलो(काष्ठा input_dev *dev);
अटल व्योम mxt_input_बंद(काष्ठा input_dev *dev);

अटल व्योम mxt_set_up_as_touchpad(काष्ठा input_dev *input_dev,
				   काष्ठा mxt_data *data)
अणु
	पूर्णांक i;

	input_dev->name = "Atmel maXTouch Touchpad";

	__set_bit(INPUT_PROP_BUTTONPAD, input_dev->propbit);

	input_असल_set_res(input_dev, ABS_X, MXT_PIXELS_PER_MM);
	input_असल_set_res(input_dev, ABS_Y, MXT_PIXELS_PER_MM);
	input_असल_set_res(input_dev, ABS_MT_POSITION_X,
			  MXT_PIXELS_PER_MM);
	input_असल_set_res(input_dev, ABS_MT_POSITION_Y,
			  MXT_PIXELS_PER_MM);

	क्रम (i = 0; i < data->t19_num_keys; i++)
		अगर (data->t19_keymap[i] != KEY_RESERVED)
			input_set_capability(input_dev, EV_KEY,
					     data->t19_keymap[i]);
पूर्ण

अटल पूर्णांक mxt_initialize_input_device(काष्ठा mxt_data *data)
अणु
	काष्ठा device *dev = &data->client->dev;
	काष्ठा input_dev *input_dev;
	पूर्णांक error;
	अचिन्हित पूर्णांक num_mt_slots;
	अचिन्हित पूर्णांक mt_flags = 0;

	चयन (data->multitouch) अणु
	हाल MXT_TOUCH_MULTI_T9:
		num_mt_slots = data->T9_reportid_max - data->T9_reportid_min + 1;
		error = mxt_पढ़ो_t9_resolution(data);
		अगर (error)
			dev_warn(dev, "Failed to initialize T9 resolution\n");
		अवरोध;

	हाल MXT_TOUCH_MULTITOUCHSCREEN_T100:
		num_mt_slots = data->num_touchids;
		error = mxt_पढ़ो_t100_config(data);
		अगर (error)
			dev_warn(dev, "Failed to read T100 config\n");
		अवरोध;

	शेष:
		dev_err(dev, "Invalid multitouch object\n");
		वापस -EINVAL;
	पूर्ण

	/* Handle शेष values and orientation चयन */
	अगर (data->max_x == 0)
		data->max_x = 1023;

	अगर (data->max_y == 0)
		data->max_y = 1023;

	अगर (data->xy_चयन)
		swap(data->max_x, data->max_y);

	dev_info(dev, "Touchscreen size X%uY%u\n", data->max_x, data->max_y);

	/* Register input device */
	input_dev = input_allocate_device();
	अगर (!input_dev)
		वापस -ENOMEM;

	input_dev->name = "Atmel maXTouch Touchscreen";
	input_dev->phys = data->phys;
	input_dev->id.bustype = BUS_I2C;
	input_dev->dev.parent = dev;
	input_dev->खोलो = mxt_input_खोलो;
	input_dev->बंद = mxt_input_बंद;

	input_set_capability(input_dev, EV_KEY, BTN_TOUCH);

	/* For single touch */
	input_set_असल_params(input_dev, ABS_X, 0, data->max_x, 0, 0);
	input_set_असल_params(input_dev, ABS_Y, 0, data->max_y, 0, 0);

	अगर (data->multitouch == MXT_TOUCH_MULTI_T9 ||
	    (data->multitouch == MXT_TOUCH_MULTITOUCHSCREEN_T100 &&
	     data->t100_aux_ampl)) अणु
		input_set_असल_params(input_dev, ABS_PRESSURE, 0, 255, 0, 0);
	पूर्ण

	/* If device has buttons we assume it is a touchpad */
	अगर (data->t19_num_keys) अणु
		mxt_set_up_as_touchpad(input_dev, data);
		mt_flags |= INPUT_MT_POINTER;
	पूर्ण अन्यथा अणु
		mt_flags |= INPUT_MT_सूचीECT;
	पूर्ण

	/* For multi touch */
	error = input_mt_init_slots(input_dev, num_mt_slots, mt_flags);
	अगर (error) अणु
		dev_err(dev, "Error %d initialising slots\n", error);
		जाओ err_मुक्त_mem;
	पूर्ण

	अगर (data->multitouch == MXT_TOUCH_MULTITOUCHSCREEN_T100) अणु
		input_set_असल_params(input_dev, ABS_MT_TOOL_TYPE,
				     0, MT_TOOL_MAX, 0, 0);
		input_set_असल_params(input_dev, ABS_MT_DISTANCE,
				     MXT_DISTANCE_ACTIVE_TOUCH,
				     MXT_DISTANCE_HOVERING,
				     0, 0);
	पूर्ण

	input_set_असल_params(input_dev, ABS_MT_POSITION_X,
			     0, data->max_x, 0, 0);
	input_set_असल_params(input_dev, ABS_MT_POSITION_Y,
			     0, data->max_y, 0, 0);

	अगर (data->multitouch == MXT_TOUCH_MULTI_T9 ||
	    (data->multitouch == MXT_TOUCH_MULTITOUCHSCREEN_T100 &&
	     data->t100_aux_area)) अणु
		input_set_असल_params(input_dev, ABS_MT_TOUCH_MAJOR,
				     0, MXT_MAX_AREA, 0, 0);
	पूर्ण

	अगर (data->multitouch == MXT_TOUCH_MULTI_T9 ||
	    (data->multitouch == MXT_TOUCH_MULTITOUCHSCREEN_T100 &&
	     data->t100_aux_ampl)) अणु
		input_set_असल_params(input_dev, ABS_MT_PRESSURE,
				     0, 255, 0, 0);
	पूर्ण

	अगर (data->multitouch == MXT_TOUCH_MULTITOUCHSCREEN_T100 &&
	    data->t100_aux_vect) अणु
		input_set_असल_params(input_dev, ABS_MT_ORIENTATION,
				     0, 255, 0, 0);
	पूर्ण

	अगर (data->multitouch == MXT_TOUCH_MULTITOUCHSCREEN_T100 &&
	    data->t100_aux_vect) अणु
		input_set_असल_params(input_dev, ABS_MT_ORIENTATION,
				     0, 255, 0, 0);
	पूर्ण

	input_set_drvdata(input_dev, data);

	error = input_रेजिस्टर_device(input_dev);
	अगर (error) अणु
		dev_err(dev, "Error %d registering input device\n", error);
		जाओ err_मुक्त_mem;
	पूर्ण

	data->input_dev = input_dev;

	वापस 0;

err_मुक्त_mem:
	input_मुक्त_device(input_dev);
	वापस error;
पूर्ण

अटल पूर्णांक mxt_configure_objects(काष्ठा mxt_data *data,
				 स्थिर काष्ठा firmware *cfg);

अटल व्योम mxt_config_cb(स्थिर काष्ठा firmware *cfg, व्योम *ctx)
अणु
	mxt_configure_objects(ctx, cfg);
	release_firmware(cfg);
पूर्ण

अटल पूर्णांक mxt_initialize(काष्ठा mxt_data *data)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक recovery_attempts = 0;
	पूर्णांक error;

	जबतक (1) अणु
		error = mxt_पढ़ो_info_block(data);
		अगर (!error)
			अवरोध;

		/* Check bootloader state */
		error = mxt_probe_bootloader(data, false);
		अगर (error) अणु
			dev_info(&client->dev, "Trying alternate bootloader address\n");
			error = mxt_probe_bootloader(data, true);
			अगर (error) अणु
				/* Chip is not in appmode or bootloader mode */
				वापस error;
			पूर्ण
		पूर्ण

		/* OK, we are in bootloader, see अगर we can recover */
		अगर (++recovery_attempts > 1) अणु
			dev_err(&client->dev, "Could not recover from bootloader mode\n");
			/*
			 * We can reflash from this state, so करो not
			 * पात initialization.
			 */
			data->in_bootloader = true;
			वापस 0;
		पूर्ण

		/* Attempt to निकास bootloader पूर्णांकo app mode */
		mxt_send_bootloader_cmd(data, false);
		msleep(MXT_FW_RESET_TIME);
	पूर्ण

	error = mxt_check_retrigen(data);
	अगर (error)
		वापस error;

	error = mxt_acquire_irq(data);
	अगर (error)
		वापस error;

	error = request_firmware_noरुको(THIS_MODULE, true, MXT_CFG_NAME,
					&client->dev, GFP_KERNEL, data,
					mxt_config_cb);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to invoke firmware loader: %d\n",
			error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxt_set_t7_घातer_cfg(काष्ठा mxt_data *data, u8 sleep)
अणु
	काष्ठा device *dev = &data->client->dev;
	पूर्णांक error;
	काष्ठा t7_config *new_config;
	काष्ठा t7_config deepsleep = अणु .active = 0, .idle = 0 पूर्ण;

	अगर (sleep == MXT_POWER_CFG_DEEPSLEEP)
		new_config = &deepsleep;
	अन्यथा
		new_config = &data->t7_cfg;

	error = __mxt_ग_लिखो_reg(data->client, data->T7_address,
				माप(data->t7_cfg), new_config);
	अगर (error)
		वापस error;

	dev_dbg(dev, "Set T7 ACTV:%d IDLE:%d\n",
		new_config->active, new_config->idle);

	वापस 0;
पूर्ण

अटल पूर्णांक mxt_init_t7_घातer_cfg(काष्ठा mxt_data *data)
अणु
	काष्ठा device *dev = &data->client->dev;
	पूर्णांक error;
	bool retry = false;

recheck:
	error = __mxt_पढ़ो_reg(data->client, data->T7_address,
				माप(data->t7_cfg), &data->t7_cfg);
	अगर (error)
		वापस error;

	अगर (data->t7_cfg.active == 0 || data->t7_cfg.idle == 0) अणु
		अगर (!retry) अणु
			dev_dbg(dev, "T7 cfg zero, resetting\n");
			mxt_soft_reset(data);
			retry = true;
			जाओ recheck;
		पूर्ण अन्यथा अणु
			dev_dbg(dev, "T7 cfg zero after reset, overriding\n");
			data->t7_cfg.active = 20;
			data->t7_cfg.idle = 100;
			वापस mxt_set_t7_घातer_cfg(data, MXT_POWER_CFG_RUN);
		पूर्ण
	पूर्ण

	dev_dbg(dev, "Initialized power cfg: ACTV %d, IDLE %d\n",
		data->t7_cfg.active, data->t7_cfg.idle);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_TOUCHSCREEN_ATMEL_MXT_T37
अटल स्थिर काष्ठा v4l2_file_operations mxt_video_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = v4l2_fh_खोलो,
	.release = vb2_fop_release,
	.unlocked_ioctl = video_ioctl2,
	.पढ़ो = vb2_fop_पढ़ो,
	.mmap = vb2_fop_mmap,
	.poll = vb2_fop_poll,
पूर्ण;

अटल u16 mxt_get_debug_value(काष्ठा mxt_data *data, अचिन्हित पूर्णांक x,
			       अचिन्हित पूर्णांक y)
अणु
	काष्ठा mxt_info *info = data->info;
	काष्ठा mxt_dbg *dbg = &data->dbg;
	अचिन्हित पूर्णांक ofs, page;
	अचिन्हित पूर्णांक col = 0;
	अचिन्हित पूर्णांक col_width;

	अगर (info->family_id == MXT_FAMILY_1386) अणु
		col_width = info->matrix_ysize / MXT1386_COLUMNS;
		col = y / col_width;
		y = y % col_width;
	पूर्ण अन्यथा अणु
		col_width = info->matrix_ysize;
	पूर्ण

	ofs = (y + (x * col_width)) * माप(u16);
	page = ofs / MXT_DIAGNOSTIC_SIZE;
	ofs %= MXT_DIAGNOSTIC_SIZE;

	अगर (info->family_id == MXT_FAMILY_1386)
		page += col * MXT1386_PAGES_PER_COLUMN;

	वापस get_unaligned_le16(&dbg->t37_buf[page].data[ofs]);
पूर्ण

अटल पूर्णांक mxt_convert_debug_pages(काष्ठा mxt_data *data, u16 *outbuf)
अणु
	काष्ठा mxt_dbg *dbg = &data->dbg;
	अचिन्हित पूर्णांक x = 0;
	अचिन्हित पूर्णांक y = 0;
	अचिन्हित पूर्णांक i, rx, ry;

	क्रम (i = 0; i < dbg->t37_nodes; i++) अणु
		/* Handle orientation */
		rx = data->xy_चयन ? y : x;
		ry = data->xy_चयन ? x : y;
		rx = data->invertx ? (data->xsize - 1 - rx) : rx;
		ry = data->inverty ? (data->ysize - 1 - ry) : ry;

		outbuf[i] = mxt_get_debug_value(data, rx, ry);

		/* Next value */
		अगर (++x >= (data->xy_चयन ? data->ysize : data->xsize)) अणु
			x = 0;
			y++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxt_पढ़ो_diagnostic_debug(काष्ठा mxt_data *data, u8 mode,
				     u16 *outbuf)
अणु
	काष्ठा mxt_dbg *dbg = &data->dbg;
	पूर्णांक retries = 0;
	पूर्णांक page;
	पूर्णांक ret;
	u8 cmd = mode;
	काष्ठा t37_debug *p;
	u8 cmd_poll;

	क्रम (page = 0; page < dbg->t37_pages; page++) अणु
		p = dbg->t37_buf + page;

		ret = mxt_ग_लिखो_reg(data->client, dbg->diag_cmd_address,
				    cmd);
		अगर (ret)
			वापस ret;

		retries = 0;
		msleep(20);
रुको_cmd:
		/* Read back command byte */
		ret = __mxt_पढ़ो_reg(data->client, dbg->diag_cmd_address,
				     माप(cmd_poll), &cmd_poll);
		अगर (ret)
			वापस ret;

		/* Field is cleared once the command has been processed */
		अगर (cmd_poll) अणु
			अगर (retries++ > 100)
				वापस -EINVAL;

			msleep(20);
			जाओ रुको_cmd;
		पूर्ण

		/* Read T37 page */
		ret = __mxt_पढ़ो_reg(data->client, dbg->t37_address,
				     माप(काष्ठा t37_debug), p);
		अगर (ret)
			वापस ret;

		अगर (p->mode != mode || p->page != page) अणु
			dev_err(&data->client->dev, "T37 page mismatch\n");
			वापस -EINVAL;
		पूर्ण

		dev_dbg(&data->client->dev, "%s page:%d retries:%d\n",
			__func__, page, retries);

		/* For reमुख्यing pages, ग_लिखो PAGEUP rather than mode */
		cmd = MXT_DIAGNOSTIC_PAGEUP;
	पूर्ण

	वापस mxt_convert_debug_pages(data, outbuf);
पूर्ण

अटल पूर्णांक mxt_queue_setup(काष्ठा vb2_queue *q,
		       अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
		       अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा mxt_data *data = q->drv_priv;
	माप_प्रकार size = data->dbg.t37_nodes * माप(u16);

	अगर (*nplanes)
		वापस sizes[0] < size ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = size;

	वापस 0;
पूर्ण

अटल व्योम mxt_buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा mxt_data *data = vb2_get_drv_priv(vb->vb2_queue);
	u16 *ptr;
	पूर्णांक ret;
	u8 mode;

	ptr = vb2_plane_vaddr(vb, 0);
	अगर (!ptr) अणु
		dev_err(&data->client->dev, "Error acquiring frame ptr\n");
		जाओ fault;
	पूर्ण

	चयन (data->dbg.input) अणु
	हाल MXT_V4L_INPUT_DELTAS:
	शेष:
		mode = MXT_DIAGNOSTIC_DELTAS;
		अवरोध;

	हाल MXT_V4L_INPUT_REFS:
		mode = MXT_DIAGNOSTIC_REFS;
		अवरोध;
	पूर्ण

	ret = mxt_पढ़ो_diagnostic_debug(data, mode, ptr);
	अगर (ret)
		जाओ fault;

	vb2_set_plane_payload(vb, 0, data->dbg.t37_nodes * माप(u16));
	vb2_buffer_करोne(vb, VB2_BUF_STATE_DONE);
	वापस;

fault:
	vb2_buffer_करोne(vb, VB2_BUF_STATE_ERROR);
पूर्ण

/* V4L2 काष्ठाures */
अटल स्थिर काष्ठा vb2_ops mxt_queue_ops = अणु
	.queue_setup		= mxt_queue_setup,
	.buf_queue		= mxt_buffer_queue,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

अटल स्थिर काष्ठा vb2_queue mxt_queue = अणु
	.type = V4L2_BUF_TYPE_VIDEO_CAPTURE,
	.io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF | VB2_READ,
	.buf_काष्ठा_size = माप(काष्ठा mxt_vb2_buffer),
	.ops = &mxt_queue_ops,
	.mem_ops = &vb2_vदो_स्मृति_memops,
	.बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC,
	.min_buffers_needed = 1,
पूर्ण;

अटल पूर्णांक mxt_vidioc_querycap(काष्ठा file *file, व्योम *priv,
				 काष्ठा v4l2_capability *cap)
अणु
	काष्ठा mxt_data *data = video_drvdata(file);

	strlcpy(cap->driver, "atmel_mxt_ts", माप(cap->driver));
	strlcpy(cap->card, "atmel_mxt_ts touch", माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info),
		 "I2C:%s", dev_name(&data->client->dev));
	वापस 0;
पूर्ण

अटल पूर्णांक mxt_vidioc_क्रमागत_input(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_input *i)
अणु
	अगर (i->index >= MXT_V4L_INPUT_MAX)
		वापस -EINVAL;

	i->type = V4L2_INPUT_TYPE_TOUCH;

	चयन (i->index) अणु
	हाल MXT_V4L_INPUT_REFS:
		strlcpy(i->name, "Mutual Capacitance References",
			माप(i->name));
		अवरोध;
	हाल MXT_V4L_INPUT_DELTAS:
		strlcpy(i->name, "Mutual Capacitance Deltas", माप(i->name));
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxt_set_input(काष्ठा mxt_data *data, अचिन्हित पूर्णांक i)
अणु
	काष्ठा v4l2_pix_क्रमmat *f = &data->dbg.क्रमmat;

	अगर (i >= MXT_V4L_INPUT_MAX)
		वापस -EINVAL;

	अगर (i == MXT_V4L_INPUT_DELTAS)
		f->pixelक्रमmat = V4L2_TCH_FMT_DELTA_TD16;
	अन्यथा
		f->pixelक्रमmat = V4L2_TCH_FMT_TU16;

	f->width = data->xy_चयन ? data->ysize : data->xsize;
	f->height = data->xy_चयन ? data->xsize : data->ysize;
	f->field = V4L2_FIELD_NONE;
	f->colorspace = V4L2_COLORSPACE_RAW;
	f->bytesperline = f->width * माप(u16);
	f->sizeimage = f->width * f->height * माप(u16);

	data->dbg.input = i;

	वापस 0;
पूर्ण

अटल पूर्णांक mxt_vidioc_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	वापस mxt_set_input(video_drvdata(file), i);
पूर्ण

अटल पूर्णांक mxt_vidioc_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा mxt_data *data = video_drvdata(file);

	*i = data->dbg.input;

	वापस 0;
पूर्ण

अटल पूर्णांक mxt_vidioc_fmt(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा mxt_data *data = video_drvdata(file);

	f->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	f->fmt.pix = data->dbg.क्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक mxt_vidioc_क्रमागत_fmt(काष्ठा file *file, व्योम *priv,
				 काष्ठा v4l2_fmtdesc *fmt)
अणु
	अगर (fmt->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	चयन (fmt->index) अणु
	हाल 0:
		fmt->pixelक्रमmat = V4L2_TCH_FMT_TU16;
		अवरोध;

	हाल 1:
		fmt->pixelक्रमmat = V4L2_TCH_FMT_DELTA_TD16;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxt_vidioc_g_parm(काष्ठा file *file, व्योम *fh,
			     काष्ठा v4l2_streamparm *a)
अणु
	अगर (a->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	a->parm.capture.पढ़ोbuffers = 1;
	a->parm.capture.समयperframe.numerator = 1;
	a->parm.capture.समयperframe.denominator = 10;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops mxt_video_ioctl_ops = अणु
	.vidioc_querycap        = mxt_vidioc_querycap,

	.vidioc_क्रमागत_fmt_vid_cap = mxt_vidioc_क्रमागत_fmt,
	.vidioc_s_fmt_vid_cap   = mxt_vidioc_fmt,
	.vidioc_g_fmt_vid_cap   = mxt_vidioc_fmt,
	.vidioc_try_fmt_vid_cap	= mxt_vidioc_fmt,
	.vidioc_g_parm		= mxt_vidioc_g_parm,

	.vidioc_क्रमागत_input      = mxt_vidioc_क्रमागत_input,
	.vidioc_g_input         = mxt_vidioc_g_input,
	.vidioc_s_input         = mxt_vidioc_s_input,

	.vidioc_reqbufs         = vb2_ioctl_reqbufs,
	.vidioc_create_bufs     = vb2_ioctl_create_bufs,
	.vidioc_querybuf        = vb2_ioctl_querybuf,
	.vidioc_qbuf            = vb2_ioctl_qbuf,
	.vidioc_dqbuf           = vb2_ioctl_dqbuf,
	.vidioc_expbuf          = vb2_ioctl_expbuf,

	.vidioc_streamon        = vb2_ioctl_streamon,
	.vidioc_streamoff       = vb2_ioctl_streamoff,
पूर्ण;

अटल स्थिर काष्ठा video_device mxt_video_device = अणु
	.name = "Atmel maxTouch",
	.fops = &mxt_video_fops,
	.ioctl_ops = &mxt_video_ioctl_ops,
	.release = video_device_release_empty,
	.device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_TOUCH |
		       V4L2_CAP_READWRITE | V4L2_CAP_STREAMING,
पूर्ण;

अटल व्योम mxt_debug_init(काष्ठा mxt_data *data)
अणु
	काष्ठा mxt_info *info = data->info;
	काष्ठा mxt_dbg *dbg = &data->dbg;
	काष्ठा mxt_object *object;
	पूर्णांक error;

	object = mxt_get_object(data, MXT_GEN_COMMAND_T6);
	अगर (!object)
		जाओ error;

	dbg->diag_cmd_address = object->start_address + MXT_COMMAND_DIAGNOSTIC;

	object = mxt_get_object(data, MXT_DEBUG_DIAGNOSTIC_T37);
	अगर (!object)
		जाओ error;

	अगर (mxt_obj_size(object) != माप(काष्ठा t37_debug)) अणु
		dev_warn(&data->client->dev, "Bad T37 size");
		जाओ error;
	पूर्ण

	dbg->t37_address = object->start_address;

	/* Calculate size of data and allocate buffer */
	dbg->t37_nodes = data->xsize * data->ysize;

	अगर (info->family_id == MXT_FAMILY_1386)
		dbg->t37_pages = MXT1386_COLUMNS * MXT1386_PAGES_PER_COLUMN;
	अन्यथा
		dbg->t37_pages = DIV_ROUND_UP(data->xsize *
					      info->matrix_ysize *
					      माप(u16),
					      माप(dbg->t37_buf->data));

	dbg->t37_buf = devm_kदो_स्मृति_array(&data->client->dev, dbg->t37_pages,
					  माप(काष्ठा t37_debug), GFP_KERNEL);
	अगर (!dbg->t37_buf)
		जाओ error;

	/* init channel to zero */
	mxt_set_input(data, 0);

	/* रेजिस्टर video device */
	snम_लिखो(dbg->v4l2.name, माप(dbg->v4l2.name), "%s", "atmel_mxt_ts");
	error = v4l2_device_रेजिस्टर(&data->client->dev, &dbg->v4l2);
	अगर (error)
		जाओ error;

	/* initialize the queue */
	mutex_init(&dbg->lock);
	dbg->queue = mxt_queue;
	dbg->queue.drv_priv = data;
	dbg->queue.lock = &dbg->lock;
	dbg->queue.dev = &data->client->dev;

	error = vb2_queue_init(&dbg->queue);
	अगर (error)
		जाओ error_unreg_v4l2;

	dbg->vdev = mxt_video_device;
	dbg->vdev.v4l2_dev = &dbg->v4l2;
	dbg->vdev.lock = &dbg->lock;
	dbg->vdev.vfl_dir = VFL_सूची_RX;
	dbg->vdev.queue = &dbg->queue;
	video_set_drvdata(&dbg->vdev, data);

	error = video_रेजिस्टर_device(&dbg->vdev, VFL_TYPE_TOUCH, -1);
	अगर (error)
		जाओ error_unreg_v4l2;

	वापस;

error_unreg_v4l2:
	v4l2_device_unरेजिस्टर(&dbg->v4l2);
error:
	dev_warn(&data->client->dev, "Error initializing T37\n");
पूर्ण
#अन्यथा
अटल व्योम mxt_debug_init(काष्ठा mxt_data *data)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mxt_configure_objects(काष्ठा mxt_data *data,
				 स्थिर काष्ठा firmware *cfg)
अणु
	काष्ठा device *dev = &data->client->dev;
	पूर्णांक error;

	error = mxt_init_t7_घातer_cfg(data);
	अगर (error) अणु
		dev_err(dev, "Failed to initialize power cfg\n");
		वापस error;
	पूर्ण

	अगर (cfg) अणु
		error = mxt_update_cfg(data, cfg);
		अगर (error)
			dev_warn(dev, "Error %d updating config\n", error);
	पूर्ण

	अगर (data->multitouch) अणु
		error = mxt_initialize_input_device(data);
		अगर (error)
			वापस error;
	पूर्ण अन्यथा अणु
		dev_warn(dev, "No touch object detected\n");
	पूर्ण

	mxt_debug_init(data);

	वापस 0;
पूर्ण

/* Firmware Version is वापसed as Major.Minor.Build */
अटल sमाप_प्रकार mxt_fw_version_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mxt_data *data = dev_get_drvdata(dev);
	काष्ठा mxt_info *info = data->info;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%u.%u.%02X\n",
			 info->version >> 4, info->version & 0xf, info->build);
पूर्ण

/* Hardware Version is वापसed as FamilyID.VariantID */
अटल sमाप_प्रकार mxt_hw_version_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mxt_data *data = dev_get_drvdata(dev);
	काष्ठा mxt_info *info = data->info;
	वापस scnम_लिखो(buf, PAGE_SIZE, "%u.%u\n",
			 info->family_id, info->variant_id);
पूर्ण

अटल sमाप_प्रकार mxt_show_instance(अक्षर *buf, पूर्णांक count,
				 काष्ठा mxt_object *object, पूर्णांक instance,
				 स्थिर u8 *val)
अणु
	पूर्णांक i;

	अगर (mxt_obj_instances(object) > 1)
		count += scnम_लिखो(buf + count, PAGE_SIZE - count,
				   "Instance %u\n", instance);

	क्रम (i = 0; i < mxt_obj_size(object); i++)
		count += scnम_लिखो(buf + count, PAGE_SIZE - count,
				"\t[%2u]: %02x (%d)\n", i, val[i], val[i]);
	count += scnम_लिखो(buf + count, PAGE_SIZE - count, "\n");

	वापस count;
पूर्ण

अटल sमाप_प्रकार mxt_object_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mxt_data *data = dev_get_drvdata(dev);
	काष्ठा mxt_object *object;
	पूर्णांक count = 0;
	पूर्णांक i, j;
	पूर्णांक error;
	u8 *obuf;

	/* Pre-allocate buffer large enough to hold max sized object. */
	obuf = kदो_स्मृति(256, GFP_KERNEL);
	अगर (!obuf)
		वापस -ENOMEM;

	error = 0;
	क्रम (i = 0; i < data->info->object_num; i++) अणु
		object = data->object_table + i;

		अगर (!mxt_object_पढ़ोable(object->type))
			जारी;

		count += scnम_लिखो(buf + count, PAGE_SIZE - count,
				"T%u:\n", object->type);

		क्रम (j = 0; j < mxt_obj_instances(object); j++) अणु
			u16 size = mxt_obj_size(object);
			u16 addr = object->start_address + j * size;

			error = __mxt_पढ़ो_reg(data->client, addr, size, obuf);
			अगर (error)
				जाओ करोne;

			count = mxt_show_instance(buf, count, object, j, obuf);
		पूर्ण
	पूर्ण

करोne:
	kमुक्त(obuf);
	वापस error ?: count;
पूर्ण

अटल पूर्णांक mxt_check_firmware_क्रमmat(काष्ठा device *dev,
				     स्थिर काष्ठा firmware *fw)
अणु
	अचिन्हित पूर्णांक pos = 0;
	अक्षर c;

	जबतक (pos < fw->size) अणु
		c = *(fw->data + pos);

		अगर (c < '0' || (c > '9' && c < 'A') || c > 'F')
			वापस 0;

		pos++;
	पूर्ण

	/*
	 * To convert file try:
	 * xxd -r -p mXTXXX__APP_VX-X-XX.enc > maxtouch.fw
	 */
	dev_err(dev, "Aborting: firmware file must be in binary format\n");

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mxt_load_fw(काष्ठा device *dev, स्थिर अक्षर *fn)
अणु
	काष्ठा mxt_data *data = dev_get_drvdata(dev);
	स्थिर काष्ठा firmware *fw = शून्य;
	अचिन्हित पूर्णांक frame_size;
	अचिन्हित पूर्णांक pos = 0;
	अचिन्हित पूर्णांक retry = 0;
	अचिन्हित पूर्णांक frame = 0;
	पूर्णांक ret;

	ret = request_firmware(&fw, fn, dev);
	अगर (ret) अणु
		dev_err(dev, "Unable to open firmware %s\n", fn);
		वापस ret;
	पूर्ण

	/* Check क्रम incorrect enc file */
	ret = mxt_check_firmware_क्रमmat(dev, fw);
	अगर (ret)
		जाओ release_firmware;

	अगर (!data->in_bootloader) अणु
		/* Change to the bootloader mode */
		data->in_bootloader = true;

		ret = mxt_t6_command(data, MXT_COMMAND_RESET,
				     MXT_BOOT_VALUE, false);
		अगर (ret)
			जाओ release_firmware;

		msleep(MXT_RESET_TIME);

		/* Do not need to scan since we know family ID */
		ret = mxt_lookup_bootloader_address(data, 0);
		अगर (ret)
			जाओ release_firmware;

		mxt_मुक्त_input_device(data);
		mxt_मुक्त_object_table(data);
	पूर्ण अन्यथा अणु
		enable_irq(data->irq);
	पूर्ण

	reinit_completion(&data->bl_completion);

	ret = mxt_check_bootloader(data, MXT_WAITING_BOOTLOAD_CMD, false);
	अगर (ret) अणु
		/* Bootloader may still be unlocked from previous attempt */
		ret = mxt_check_bootloader(data, MXT_WAITING_FRAME_DATA, false);
		अगर (ret)
			जाओ disable_irq;
	पूर्ण अन्यथा अणु
		dev_info(dev, "Unlocking bootloader\n");

		/* Unlock bootloader */
		ret = mxt_send_bootloader_cmd(data, true);
		अगर (ret)
			जाओ disable_irq;
	पूर्ण

	जबतक (pos < fw->size) अणु
		ret = mxt_check_bootloader(data, MXT_WAITING_FRAME_DATA, true);
		अगर (ret)
			जाओ disable_irq;

		frame_size = ((*(fw->data + pos) << 8) | *(fw->data + pos + 1));

		/* Take account of CRC bytes */
		frame_size += 2;

		/* Write one frame to device */
		ret = mxt_bootloader_ग_लिखो(data, fw->data + pos, frame_size);
		अगर (ret)
			जाओ disable_irq;

		ret = mxt_check_bootloader(data, MXT_FRAME_CRC_PASS, true);
		अगर (ret) अणु
			retry++;

			/* Back off by 20ms per retry */
			msleep(retry * 20);

			अगर (retry > 20) अणु
				dev_err(dev, "Retry count exceeded\n");
				जाओ disable_irq;
			पूर्ण
		पूर्ण अन्यथा अणु
			retry = 0;
			pos += frame_size;
			frame++;
		पूर्ण

		अगर (frame % 50 == 0)
			dev_dbg(dev, "Sent %d frames, %d/%zd bytes\n",
				frame, pos, fw->size);
	पूर्ण

	/* Wait क्रम flash. */
	ret = mxt_रुको_क्रम_completion(data, &data->bl_completion,
				      MXT_FW_RESET_TIME);
	अगर (ret)
		जाओ disable_irq;

	dev_dbg(dev, "Sent %d frames, %d bytes\n", frame, pos);

	/*
	 * Wait क्रम device to reset. Some bootloader versions करो not निश्चित
	 * the CHG line after bootloading has finished, so ignore potential
	 * errors.
	 */
	mxt_रुको_क्रम_completion(data, &data->bl_completion, MXT_FW_RESET_TIME);

	data->in_bootloader = false;

disable_irq:
	disable_irq(data->irq);
release_firmware:
	release_firmware(fw);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार mxt_update_fw_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा mxt_data *data = dev_get_drvdata(dev);
	पूर्णांक error;

	error = mxt_load_fw(dev, MXT_FW_NAME);
	अगर (error) अणु
		dev_err(dev, "The firmware update failed(%d)\n", error);
		count = error;
	पूर्ण अन्यथा अणु
		dev_info(dev, "The firmware update succeeded\n");

		error = mxt_initialize(data);
		अगर (error)
			वापस error;
	पूर्ण

	वापस count;
पूर्ण

अटल DEVICE_ATTR(fw_version, S_IRUGO, mxt_fw_version_show, शून्य);
अटल DEVICE_ATTR(hw_version, S_IRUGO, mxt_hw_version_show, शून्य);
अटल DEVICE_ATTR(object, S_IRUGO, mxt_object_show, शून्य);
अटल DEVICE_ATTR(update_fw, S_IWUSR, शून्य, mxt_update_fw_store);

अटल काष्ठा attribute *mxt_attrs[] = अणु
	&dev_attr_fw_version.attr,
	&dev_attr_hw_version.attr,
	&dev_attr_object.attr,
	&dev_attr_update_fw.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group mxt_attr_group = अणु
	.attrs = mxt_attrs,
पूर्ण;

अटल व्योम mxt_start(काष्ठा mxt_data *data)
अणु
	mxt_wakeup_toggle(data->client, true, false);

	चयन (data->suspend_mode) अणु
	हाल MXT_SUSPEND_T9_CTRL:
		mxt_soft_reset(data);

		/* Touch enable */
		/* 0x83 = SCANEN | RPTEN | ENABLE */
		mxt_ग_लिखो_object(data,
				MXT_TOUCH_MULTI_T9, MXT_T9_CTRL, 0x83);
		अवरोध;

	हाल MXT_SUSPEND_DEEP_SLEEP:
	शेष:
		mxt_set_t7_घातer_cfg(data, MXT_POWER_CFG_RUN);

		/* Recalibrate since chip has been in deep sleep */
		mxt_t6_command(data, MXT_COMMAND_CALIBRATE, 1, false);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mxt_stop(काष्ठा mxt_data *data)
अणु
	चयन (data->suspend_mode) अणु
	हाल MXT_SUSPEND_T9_CTRL:
		/* Touch disable */
		mxt_ग_लिखो_object(data,
				MXT_TOUCH_MULTI_T9, MXT_T9_CTRL, 0);
		अवरोध;

	हाल MXT_SUSPEND_DEEP_SLEEP:
	शेष:
		mxt_set_t7_घातer_cfg(data, MXT_POWER_CFG_DEEPSLEEP);
		अवरोध;
	पूर्ण

	mxt_wakeup_toggle(data->client, false, false);
पूर्ण

अटल पूर्णांक mxt_input_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा mxt_data *data = input_get_drvdata(dev);

	mxt_start(data);

	वापस 0;
पूर्ण

अटल व्योम mxt_input_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा mxt_data *data = input_get_drvdata(dev);

	mxt_stop(data);
पूर्ण

अटल पूर्णांक mxt_parse_device_properties(काष्ठा mxt_data *data)
अणु
	अटल स्थिर अक्षर keymap_property[] = "linux,gpio-keymap";
	काष्ठा device *dev = &data->client->dev;
	u32 *keymap;
	पूर्णांक n_keys;
	पूर्णांक error;

	अगर (device_property_present(dev, keymap_property)) अणु
		n_keys = device_property_count_u32(dev, keymap_property);
		अगर (n_keys <= 0) अणु
			error = n_keys < 0 ? n_keys : -EINVAL;
			dev_err(dev, "invalid/malformed '%s' property: %d\n",
				keymap_property, error);
			वापस error;
		पूर्ण

		keymap = devm_kदो_स्मृति_array(dev, n_keys, माप(*keymap),
					    GFP_KERNEL);
		अगर (!keymap)
			वापस -ENOMEM;

		error = device_property_पढ़ो_u32_array(dev, keymap_property,
						       keymap, n_keys);
		अगर (error) अणु
			dev_err(dev, "failed to parse '%s' property: %d\n",
				keymap_property, error);
			वापस error;
		पूर्ण

		data->t19_keymap = keymap;
		data->t19_num_keys = n_keys;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id chromebook_T9_suspend_dmi[] = अणु
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "GOOGLE"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Link"),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "Peppy"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक mxt_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा mxt_data *data;
	पूर्णांक error;

	/*
	 * Ignore devices that करो not have device properties attached to
	 * them, as we need help determining whether we are dealing with
	 * touch screen or touchpad.
	 *
	 * So far on x86 the only users of Aपंचांगel touch controllers are
	 * Chromebooks, and chromeos_laptop driver will ensure that
	 * necessary properties are provided (अगर firmware करोes not करो that).
	 */
	अगर (!device_property_present(&client->dev, "compatible"))
		वापस -ENXIO;

	/*
	 * Ignore ACPI devices representing bootloader mode.
	 *
	 * This is a bit of a hack: Google Chromebook BIOS creates ACPI
	 * devices क्रम both application and bootloader modes, but we are
	 * पूर्णांकerested in application mode only (अगर device is in bootloader
	 * mode we'll end up चयनing पूर्णांकo application anyway). So far
	 * application mode addresses were all above 0x40, so we'll use it
	 * as a threshold.
	 */
	अगर (ACPI_COMPANION(&client->dev) && client->addr < 0x40)
		वापस -ENXIO;

	data = devm_kzalloc(&client->dev, माप(काष्ठा mxt_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	snम_लिखो(data->phys, माप(data->phys), "i2c-%u-%04x/input0",
		 client->adapter->nr, client->addr);

	data->client = client;
	data->irq = client->irq;
	i2c_set_clientdata(client, data);

	init_completion(&data->bl_completion);
	init_completion(&data->reset_completion);
	init_completion(&data->crc_completion);

	data->suspend_mode = dmi_check_प्रणाली(chromebook_T9_suspend_dmi) ?
		MXT_SUSPEND_T9_CTRL : MXT_SUSPEND_DEEP_SLEEP;

	error = mxt_parse_device_properties(data);
	अगर (error)
		वापस error;

	/*
	 * VDDA is the analog voltage supply 2.57..3.47 V
	 * VDD  is the digital voltage supply 1.71..3.47 V
	 */
	data->regulators[0].supply = "vdda";
	data->regulators[1].supply = "vdd";
	error = devm_regulator_bulk_get(&client->dev, ARRAY_SIZE(data->regulators),
					data->regulators);
	अगर (error) अणु
		अगर (error != -EPROBE_DEFER)
			dev_err(&client->dev, "Failed to get regulators %d\n",
				error);
		वापस error;
	पूर्ण

	/* Request the RESET line as निश्चितed so we go पूर्णांकo reset */
	data->reset_gpio = devm_gpiod_get_optional(&client->dev,
						   "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(data->reset_gpio)) अणु
		error = PTR_ERR(data->reset_gpio);
		dev_err(&client->dev, "Failed to get reset gpio: %d\n", error);
		वापस error;
	पूर्ण

	/* Request the WAKE line as निश्चितed so we go out of sleep */
	data->wake_gpio = devm_gpiod_get_optional(&client->dev,
						  "wake", GPIOD_OUT_HIGH);
	अगर (IS_ERR(data->wake_gpio)) अणु
		error = PTR_ERR(data->wake_gpio);
		dev_err(&client->dev, "Failed to get wake gpio: %d\n", error);
		वापस error;
	पूर्ण

	error = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					  शून्य, mxt_पूर्णांकerrupt,
					  IRQF_ONESHOT | IRQF_NO_AUTOEN,
					  client->name, data);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to register interrupt\n");
		वापस error;
	पूर्ण

	error = regulator_bulk_enable(ARRAY_SIZE(data->regulators),
				      data->regulators);
	अगर (error) अणु
		dev_err(&client->dev, "failed to enable regulators: %d\n",
			error);
		वापस error;
	पूर्ण
	/*
	 * The device takes 40ms to come up after घातer-on according
	 * to the mXT224 datasheet, page 13.
	 */
	msleep(MXT_BACKUP_TIME);

	अगर (data->reset_gpio) अणु
		/* Wait a जबतक and then de-निश्चित the RESET GPIO line */
		msleep(MXT_RESET_GPIO_TIME);
		gpiod_set_value(data->reset_gpio, 0);
		msleep(MXT_RESET_INVALID_CHG);
	पूर्ण

	/*
	 * Controllers like mXT1386 have a dedicated WAKE line that could be
	 * connected to a GPIO or to I2C SCL pin, or permanently निश्चितed low.
	 *
	 * This WAKE line is used क्रम waking controller from a deep-sleep and
	 * it needs to be निश्चितed low क्रम 25 milliseconds beक्रमe I2C transfers
	 * could be accepted by controller अगर it was in a deep-sleep mode.
	 * Controller will go पूर्णांकo sleep स्वतःmatically after 2 seconds of
	 * inactivity अगर WAKE line is deनिश्चितed and deep sleep is activated.
	 *
	 * If WAKE line is connected to I2C SCL pin, then the first I2C transfer
	 * will get an instant NAK and transfer needs to be retried after 25ms.
	 *
	 * If WAKE line is connected to a GPIO line, the line must be निश्चितed
	 * 25ms beक्रमe the host attempts to communicate with the controller.
	 */
	device_property_पढ़ो_u32(&client->dev, "atmel,wakeup-method",
				 &data->wakeup_method);

	error = mxt_initialize(data);
	अगर (error)
		जाओ err_disable_regulators;

	error = sysfs_create_group(&client->dev.kobj, &mxt_attr_group);
	अगर (error) अणु
		dev_err(&client->dev, "Failure %d creating sysfs group\n",
			error);
		जाओ err_मुक्त_object;
	पूर्ण

	वापस 0;

err_मुक्त_object:
	mxt_मुक्त_input_device(data);
	mxt_मुक्त_object_table(data);
err_disable_regulators:
	regulator_bulk_disable(ARRAY_SIZE(data->regulators),
			       data->regulators);
	वापस error;
पूर्ण

अटल पूर्णांक mxt_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा mxt_data *data = i2c_get_clientdata(client);

	disable_irq(data->irq);
	sysfs_हटाओ_group(&client->dev.kobj, &mxt_attr_group);
	mxt_मुक्त_input_device(data);
	mxt_मुक्त_object_table(data);
	regulator_bulk_disable(ARRAY_SIZE(data->regulators),
			       data->regulators);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mxt_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा mxt_data *data = i2c_get_clientdata(client);
	काष्ठा input_dev *input_dev = data->input_dev;

	अगर (!input_dev)
		वापस 0;

	mutex_lock(&input_dev->mutex);

	अगर (input_device_enabled(input_dev))
		mxt_stop(data);

	mutex_unlock(&input_dev->mutex);

	disable_irq(data->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mxt_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा mxt_data *data = i2c_get_clientdata(client);
	काष्ठा input_dev *input_dev = data->input_dev;

	अगर (!input_dev)
		वापस 0;

	enable_irq(data->irq);

	mutex_lock(&input_dev->mutex);

	अगर (input_device_enabled(input_dev))
		mxt_start(data);

	mutex_unlock(&input_dev->mutex);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(mxt_pm_ops, mxt_suspend, mxt_resume);

अटल स्थिर काष्ठा of_device_id mxt_of_match[] = अणु
	अणु .compatible = "atmel,maxtouch", पूर्ण,
	/* Compatibles listed below are deprecated */
	अणु .compatible = "atmel,qt602240_ts", पूर्ण,
	अणु .compatible = "atmel,atmel_mxt_ts", पूर्ण,
	अणु .compatible = "atmel,atmel_mxt_tp", पूर्ण,
	अणु .compatible = "atmel,mXT224", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mxt_of_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id mxt_acpi_id[] = अणु
	अणु "ATML0000", 0 पूर्ण,	/* Touchpad */
	अणु "ATML0001", 0 पूर्ण,	/* Touchscreen */
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, mxt_acpi_id);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id mxt_id[] = अणु
	अणु "qt602240_ts", 0 पूर्ण,
	अणु "atmel_mxt_ts", 0 पूर्ण,
	अणु "atmel_mxt_tp", 0 पूर्ण,
	अणु "maxtouch", 0 पूर्ण,
	अणु "mXT224", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mxt_id);

अटल काष्ठा i2c_driver mxt_driver = अणु
	.driver = अणु
		.name	= "atmel_mxt_ts",
		.of_match_table = mxt_of_match,
		.acpi_match_table = ACPI_PTR(mxt_acpi_id),
		.pm	= &mxt_pm_ops,
	पूर्ण,
	.probe		= mxt_probe,
	.हटाओ		= mxt_हटाओ,
	.id_table	= mxt_id,
पूर्ण;

module_i2c_driver(mxt_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Joonyoung Shim <jy0922.shim@samsung.com>");
MODULE_DESCRIPTION("Atmel maXTouch Touchscreen driver");
MODULE_LICENSE("GPL");
