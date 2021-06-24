<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  video.c - ACPI Video Driver
 *
 *  Copyright (C) 2004 Luming Yu <luming.yu@पूर्णांकel.com>
 *  Copyright (C) 2004 Bruno Ducrot <ducrot@poupinou.org>
 *  Copyright (C) 2006 Thomas Tuttle <linux-kernel@ttuttle.net>
 */

#घोषणा pr_fmt(fmt) "ACPI: video: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/input.h>
#समावेश <linux/backlight.h>
#समावेश <linux/thermal.h>
#समावेश <linux/sort.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/slab.h>
#समावेश <linux/dmi.h>
#समावेश <linux/suspend.h>
#समावेश <linux/acpi.h>
#समावेश <acpi/video.h>
#समावेश <linux/uaccess.h>

#घोषणा ACPI_VIDEO_BUS_NAME		"Video Bus"
#घोषणा ACPI_VIDEO_DEVICE_NAME		"Video Device"

#घोषणा MAX_NAME_LEN	20

MODULE_AUTHOR("Bruno Ducrot");
MODULE_DESCRIPTION("ACPI Video Driver");
MODULE_LICENSE("GPL");

अटल bool brightness_चयन_enabled = true;
module_param(brightness_चयन_enabled, bool, 0644);

/*
 * By शेष, we करोn't allow duplicate ACPI video bus devices
 * under the same VGA controller
 */
अटल bool allow_duplicates;
module_param(allow_duplicates, bool, 0644);

अटल पूर्णांक disable_backlight_sysfs_अगर = -1;
module_param(disable_backlight_sysfs_अगर, पूर्णांक, 0444);

#घोषणा REPORT_OUTPUT_KEY_EVENTS		0x01
#घोषणा REPORT_BRIGHTNESS_KEY_EVENTS		0x02
अटल पूर्णांक report_key_events = -1;
module_param(report_key_events, पूर्णांक, 0644);
MODULE_PARM_DESC(report_key_events,
	"0: none, 1: output changes, 2: brightness changes, 3: all");

अटल पूर्णांक hw_changes_brightness = -1;
module_param(hw_changes_brightness, पूर्णांक, 0644);
MODULE_PARM_DESC(hw_changes_brightness,
	"Set this to 1 on buggy hw which changes the brightness itself when "
	"a hotkey is pressed: -1: auto, 0: normal 1: hw-changes-brightness");

/*
 * Whether the काष्ठा acpi_video_device_attrib::device_id_scheme bit should be
 * assumed even अगर not actually set.
 */
अटल bool device_id_scheme = false;
module_param(device_id_scheme, bool, 0444);

अटल पूर्णांक only_lcd = -1;
module_param(only_lcd, पूर्णांक, 0444);

अटल पूर्णांक रेजिस्टर_count;
अटल DEFINE_MUTEX(रेजिस्टर_count_mutex);
अटल DEFINE_MUTEX(video_list_lock);
अटल LIST_HEAD(video_bus_head);
अटल पूर्णांक acpi_video_bus_add(काष्ठा acpi_device *device);
अटल पूर्णांक acpi_video_bus_हटाओ(काष्ठा acpi_device *device);
अटल व्योम acpi_video_bus_notअगरy(काष्ठा acpi_device *device, u32 event);
व्योम acpi_video_detect_निकास(व्योम);

/*
 * Indices in the _BCL method response: the first two items are special,
 * the rest are all supported levels.
 *
 * See page 575 of the ACPI spec 3.0
 */
क्रमागत acpi_video_level_idx अणु
	ACPI_VIDEO_AC_LEVEL,		/* level when machine has full घातer */
	ACPI_VIDEO_BATTERY_LEVEL,	/* level when machine is on batteries */
	ACPI_VIDEO_FIRST_LEVEL,		/* actual supported levels begin here */
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id video_device_ids[] = अणु
	अणुACPI_VIDEO_HID, 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, video_device_ids);

अटल काष्ठा acpi_driver acpi_video_bus = अणु
	.name = "video",
	.class = ACPI_VIDEO_CLASS,
	.ids = video_device_ids,
	.ops = अणु
		.add = acpi_video_bus_add,
		.हटाओ = acpi_video_bus_हटाओ,
		.notअगरy = acpi_video_bus_notअगरy,
		पूर्ण,
पूर्ण;

काष्ठा acpi_video_bus_flags अणु
	u8 multihead:1;		/* can चयन video heads */
	u8 rom:1;		/* can retrieve a video rom */
	u8 post:1;		/* can configure the head to */
	u8 reserved:5;
पूर्ण;

काष्ठा acpi_video_bus_cap अणु
	u8 _DOS:1;		/* Enable/Disable output चयनing */
	u8 _DOD:1;		/* Enumerate all devices attached to display adapter */
	u8 _ROM:1;		/* Get ROM Data */
	u8 _GPD:1;		/* Get POST Device */
	u8 _SPD:1;		/* Set POST Device */
	u8 _VPO:1;		/* Video POST Options */
	u8 reserved:2;
पूर्ण;

काष्ठा acpi_video_device_attrib अणु
	u32 display_index:4;	/* A zero-based instance of the Display */
	u32 display_port_attachment:4;	/* This field dअगरferentiates the display type */
	u32 display_type:4;	/* Describe the specअगरic type in use */
	u32 venकरोr_specअगरic:4;	/* Chipset Venकरोr Specअगरic */
	u32 bios_can_detect:1;	/* BIOS can detect the device */
	u32 depend_on_vga:1;	/* Non-VGA output device whose घातer is related to
				   the VGA device. */
	u32 pipe_id:3;		/* For VGA multiple-head devices. */
	u32 reserved:10;	/* Must be 0 */

	/*
	 * The device ID might not actually follow the scheme described by this
	 * काष्ठा acpi_video_device_attrib. If it करोes, then this bit
	 * device_id_scheme is set; otherwise, other fields should be ignored.
	 *
	 * (but also see the global flag device_id_scheme)
	 */
	u32 device_id_scheme:1;
पूर्ण;

काष्ठा acpi_video_क्रमागतerated_device अणु
	जोड़ अणु
		u32 पूर्णांक_val;
		काष्ठा acpi_video_device_attrib attrib;
	पूर्ण value;
	काष्ठा acpi_video_device *bind_info;
पूर्ण;

काष्ठा acpi_video_bus अणु
	काष्ठा acpi_device *device;
	bool backlight_रेजिस्टरed;
	u8 करोs_setting;
	काष्ठा acpi_video_क्रमागतerated_device *attached_array;
	u8 attached_count;
	u8 child_count;
	काष्ठा acpi_video_bus_cap cap;
	काष्ठा acpi_video_bus_flags flags;
	काष्ठा list_head video_device_list;
	काष्ठा mutex device_list_lock;	/* protects video_device_list */
	काष्ठा list_head entry;
	काष्ठा input_dev *input;
	अक्षर phys[32];	/* क्रम input device */
	काष्ठा notअगरier_block pm_nb;
पूर्ण;

काष्ठा acpi_video_device_flags अणु
	u8 crt:1;
	u8 lcd:1;
	u8 tvout:1;
	u8 dvi:1;
	u8 bios:1;
	u8 unknown:1;
	u8 notअगरy:1;
	u8 reserved:1;
पूर्ण;

काष्ठा acpi_video_device_cap अणु
	u8 _ADR:1;		/* Return the unique ID */
	u8 _BCL:1;		/* Query list of brightness control levels supported */
	u8 _BCM:1;		/* Set the brightness level */
	u8 _BQC:1;		/* Get current brightness level */
	u8 _BCQ:1;		/* Some buggy BIOS uses _BCQ instead of _BQC */
	u8 _DDC:1;		/* Return the EDID क्रम this device */
पूर्ण;

काष्ठा acpi_video_device अणु
	अचिन्हित दीर्घ device_id;
	काष्ठा acpi_video_device_flags flags;
	काष्ठा acpi_video_device_cap cap;
	काष्ठा list_head entry;
	काष्ठा delayed_work चयन_brightness_work;
	पूर्णांक चयन_brightness_event;
	काष्ठा acpi_video_bus *video;
	काष्ठा acpi_device *dev;
	काष्ठा acpi_video_device_brightness *brightness;
	काष्ठा backlight_device *backlight;
	काष्ठा thermal_cooling_device *cooling_dev;
पूर्ण;

अटल व्योम acpi_video_device_notअगरy(acpi_handle handle, u32 event, व्योम *data);
अटल व्योम acpi_video_device_rebind(काष्ठा acpi_video_bus *video);
अटल व्योम acpi_video_device_bind(काष्ठा acpi_video_bus *video,
				   काष्ठा acpi_video_device *device);
अटल पूर्णांक acpi_video_device_क्रमागतerate(काष्ठा acpi_video_bus *video);
अटल पूर्णांक acpi_video_device_lcd_set_level(काष्ठा acpi_video_device *device,
			पूर्णांक level);
अटल पूर्णांक acpi_video_device_lcd_get_level_current(
			काष्ठा acpi_video_device *device,
			अचिन्हित दीर्घ दीर्घ *level, bool raw);
अटल पूर्णांक acpi_video_get_next_level(काष्ठा acpi_video_device *device,
				     u32 level_current, u32 event);
अटल व्योम acpi_video_चयन_brightness(काष्ठा work_काष्ठा *work);

/* backlight device sysfs support */
अटल पूर्णांक acpi_video_get_brightness(काष्ठा backlight_device *bd)
अणु
	अचिन्हित दीर्घ दीर्घ cur_level;
	पूर्णांक i;
	काष्ठा acpi_video_device *vd = bl_get_data(bd);

	अगर (acpi_video_device_lcd_get_level_current(vd, &cur_level, false))
		वापस -EINVAL;
	क्रम (i = ACPI_VIDEO_FIRST_LEVEL; i < vd->brightness->count; i++) अणु
		अगर (vd->brightness->levels[i] == cur_level)
			वापस i - ACPI_VIDEO_FIRST_LEVEL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_video_set_brightness(काष्ठा backlight_device *bd)
अणु
	पूर्णांक request_level = bd->props.brightness + ACPI_VIDEO_FIRST_LEVEL;
	काष्ठा acpi_video_device *vd = bl_get_data(bd);

	cancel_delayed_work(&vd->चयन_brightness_work);
	वापस acpi_video_device_lcd_set_level(vd,
				vd->brightness->levels[request_level]);
पूर्ण

अटल स्थिर काष्ठा backlight_ops acpi_backlight_ops = अणु
	.get_brightness = acpi_video_get_brightness,
	.update_status  = acpi_video_set_brightness,
पूर्ण;

/* thermal cooling device callbacks */
अटल पूर्णांक video_get_max_state(काष्ठा thermal_cooling_device *cooling_dev,
			       अचिन्हित दीर्घ *state)
अणु
	काष्ठा acpi_device *device = cooling_dev->devdata;
	काष्ठा acpi_video_device *video = acpi_driver_data(device);

	*state = video->brightness->count - ACPI_VIDEO_FIRST_LEVEL - 1;
	वापस 0;
पूर्ण

अटल पूर्णांक video_get_cur_state(काष्ठा thermal_cooling_device *cooling_dev,
			       अचिन्हित दीर्घ *state)
अणु
	काष्ठा acpi_device *device = cooling_dev->devdata;
	काष्ठा acpi_video_device *video = acpi_driver_data(device);
	अचिन्हित दीर्घ दीर्घ level;
	पूर्णांक offset;

	अगर (acpi_video_device_lcd_get_level_current(video, &level, false))
		वापस -EINVAL;
	क्रम (offset = ACPI_VIDEO_FIRST_LEVEL; offset < video->brightness->count;
	     offset++)
		अगर (level == video->brightness->levels[offset]) अणु
			*state = video->brightness->count - offset - 1;
			वापस 0;
		पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
video_set_cur_state(काष्ठा thermal_cooling_device *cooling_dev, अचिन्हित दीर्घ state)
अणु
	काष्ठा acpi_device *device = cooling_dev->devdata;
	काष्ठा acpi_video_device *video = acpi_driver_data(device);
	पूर्णांक level;

	अगर (state >= video->brightness->count - ACPI_VIDEO_FIRST_LEVEL)
		वापस -EINVAL;

	state = video->brightness->count - state;
	level = video->brightness->levels[state - 1];
	वापस acpi_video_device_lcd_set_level(video, level);
पूर्ण

अटल स्थिर काष्ठा thermal_cooling_device_ops video_cooling_ops = अणु
	.get_max_state = video_get_max_state,
	.get_cur_state = video_get_cur_state,
	.set_cur_state = video_set_cur_state,
पूर्ण;

/*
 * --------------------------------------------------------------------------
 *                             Video Management
 * --------------------------------------------------------------------------
 */

अटल पूर्णांक
acpi_video_device_lcd_query_levels(acpi_handle handle,
				   जोड़ acpi_object **levels)
अणु
	पूर्णांक status;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;


	*levels = शून्य;

	status = acpi_evaluate_object(handle, "_BCL", शून्य, &buffer);
	अगर (ACPI_FAILURE(status))
		वापस status;
	obj = (जोड़ acpi_object *)buffer.poपूर्णांकer;
	अगर (!obj || (obj->type != ACPI_TYPE_PACKAGE)) अणु
		acpi_handle_info(handle, "Invalid _BCL data\n");
		status = -EFAULT;
		जाओ err;
	पूर्ण

	*levels = obj;

	वापस 0;

err:
	kमुक्त(buffer.poपूर्णांकer);

	वापस status;
पूर्ण

अटल पूर्णांक
acpi_video_device_lcd_set_level(काष्ठा acpi_video_device *device, पूर्णांक level)
अणु
	पूर्णांक status;
	पूर्णांक state;

	status = acpi_execute_simple_method(device->dev->handle,
					    "_BCM", level);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_handle_info(device->dev->handle, "_BCM evaluation failed\n");
		वापस -EIO;
	पूर्ण

	device->brightness->curr = level;
	क्रम (state = ACPI_VIDEO_FIRST_LEVEL; state < device->brightness->count;
	     state++)
		अगर (level == device->brightness->levels[state]) अणु
			अगर (device->backlight)
				device->backlight->props.brightness =
					state - ACPI_VIDEO_FIRST_LEVEL;
			वापस 0;
		पूर्ण

	acpi_handle_info(device->dev->handle, "Current brightness invalid\n");
	वापस -EINVAL;
पूर्ण

/*
 * For some buggy _BQC methods, we need to add a स्थिरant value to
 * the _BQC वापस value to get the actual current brightness level
 */

अटल पूर्णांक bqc_offset_aml_bug_workaround;
अटल पूर्णांक video_set_bqc_offset(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	bqc_offset_aml_bug_workaround = 9;
	वापस 0;
पूर्ण

अटल पूर्णांक video_disable_backlight_sysfs_अगर(
	स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	अगर (disable_backlight_sysfs_अगर == -1)
		disable_backlight_sysfs_अगर = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक video_set_device_id_scheme(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	device_id_scheme = true;
	वापस 0;
पूर्ण

अटल पूर्णांक video_enable_only_lcd(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	only_lcd = true;
	वापस 0;
पूर्ण

अटल पूर्णांक video_set_report_key_events(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	अगर (report_key_events == -1)
		report_key_events = (uपूर्णांकptr_t)id->driver_data;
	वापस 0;
पूर्ण

अटल पूर्णांक video_hw_changes_brightness(
	स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	अगर (hw_changes_brightness == -1)
		hw_changes_brightness = 1;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id video_dmi_table[] = अणु
	/*
	 * Broken _BQC workaround http://bugzilla.kernel.org/show_bug.cgi?id=13121
	 */
	अणु
	 .callback = video_set_bqc_offset,
	 .ident = "Acer Aspire 5720",
	 .matches = अणु
		DMI_MATCH(DMI_BOARD_VENDOR, "Acer"),
		DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 5720"),
		पूर्ण,
	पूर्ण,
	अणु
	 .callback = video_set_bqc_offset,
	 .ident = "Acer Aspire 5710Z",
	 .matches = अणु
		DMI_MATCH(DMI_BOARD_VENDOR, "Acer"),
		DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 5710Z"),
		पूर्ण,
	पूर्ण,
	अणु
	 .callback = video_set_bqc_offset,
	 .ident = "eMachines E510",
	 .matches = अणु
		DMI_MATCH(DMI_BOARD_VENDOR, "EMACHINES"),
		DMI_MATCH(DMI_PRODUCT_NAME, "eMachines E510"),
		पूर्ण,
	पूर्ण,
	अणु
	 .callback = video_set_bqc_offset,
	 .ident = "Acer Aspire 5315",
	 .matches = अणु
		DMI_MATCH(DMI_BOARD_VENDOR, "Acer"),
		DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 5315"),
		पूर्ण,
	पूर्ण,
	अणु
	 .callback = video_set_bqc_offset,
	 .ident = "Acer Aspire 7720",
	 .matches = अणु
		DMI_MATCH(DMI_BOARD_VENDOR, "Acer"),
		DMI_MATCH(DMI_PRODUCT_NAME, "Aspire 7720"),
		पूर्ण,
	पूर्ण,

	/*
	 * Some machines have a broken acpi-video पूर्णांकerface क्रम brightness
	 * control, but still need an acpi_video_device_lcd_set_level() call
	 * on resume to turn the backlight घातer on.  We Enable backlight
	 * control on these प्रणालीs, but करो not रेजिस्टर a backlight sysfs
	 * as brightness control करोes not work.
	 */
	अणु
	 /* https://bugzilla.kernel.org/show_bug.cgi?id=21012 */
	 .callback = video_disable_backlight_sysfs_अगर,
	 .ident = "Toshiba Portege R700",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
		DMI_MATCH(DMI_PRODUCT_NAME, "PORTEGE R700"),
		पूर्ण,
	पूर्ण,
	अणु
	 /* https://bugs.मुक्तdesktop.org/show_bug.cgi?id=82634 */
	 .callback = video_disable_backlight_sysfs_अगर,
	 .ident = "Toshiba Portege R830",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
		DMI_MATCH(DMI_PRODUCT_NAME, "PORTEGE R830"),
		पूर्ण,
	पूर्ण,
	अणु
	 /* https://bugzilla.kernel.org/show_bug.cgi?id=21012 */
	 .callback = video_disable_backlight_sysfs_अगर,
	 .ident = "Toshiba Satellite R830",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
		DMI_MATCH(DMI_PRODUCT_NAME, "SATELLITE R830"),
		पूर्ण,
	पूर्ण,
	/*
	 * Some machine's _DOD IDs don't have bit 31(Device ID Scheme) set
	 * but the IDs actually follow the Device ID Scheme.
	 */
	अणु
	 /* https://bugzilla.kernel.org/show_bug.cgi?id=104121 */
	 .callback = video_set_device_id_scheme,
	 .ident = "ESPRIMO Mobile M9410",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
		DMI_MATCH(DMI_PRODUCT_NAME, "ESPRIMO Mobile M9410"),
		पूर्ण,
	पूर्ण,
	/*
	 * Some machines have multiple video output devices, but only the one
	 * that is the type of LCD can करो the backlight control so we should not
	 * रेजिस्टर backlight पूर्णांकerface क्रम other video output devices.
	 */
	अणु
	 /* https://bugzilla.kernel.org/show_bug.cgi?id=104121 */
	 .callback = video_enable_only_lcd,
	 .ident = "ESPRIMO Mobile M9410",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
		DMI_MATCH(DMI_PRODUCT_NAME, "ESPRIMO Mobile M9410"),
		पूर्ण,
	पूर्ण,
	/*
	 * Some machines report wrong key events on the acpi-bus, suppress
	 * key event reporting on these.  Note this is only पूर्णांकended to work
	 * around events which are plain wrong. In some हालs we get द्विगुन
	 * events, in this हाल acpi-video is considered the canonical source
	 * and the events from the other source should be filtered. E.g.
	 * by calling acpi_video_handles_brightness_key_presses() from the
	 * venकरोr acpi/wmi driver or by using /lib/udev/hwdb.d/60-keyboard.hwdb
	 */
	अणु
	 .callback = video_set_report_key_events,
	 .driver_data = (व्योम *)((uपूर्णांकptr_t)REPORT_OUTPUT_KEY_EVENTS),
	 .ident = "Dell Vostro V131",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		DMI_MATCH(DMI_PRODUCT_NAME, "Vostro V131"),
		पूर्ण,
	पूर्ण,
	/*
	 * Some machines change the brightness themselves when a brightness
	 * hotkey माला_लो pressed, despite us telling them not to. In this हाल
	 * acpi_video_device_notअगरy() should only call backlight_क्रमce_update(
	 * BACKLIGHT_UPDATE_HOTKEY) and not करो anything अन्यथा.
	 */
	अणु
	 /* https://bugzilla.kernel.org/show_bug.cgi?id=204077 */
	 .callback = video_hw_changes_brightness,
	 .ident = "Packard Bell EasyNote MZ35",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Packard Bell"),
		DMI_MATCH(DMI_PRODUCT_NAME, "EasyNote MZ35"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल अचिन्हित दीर्घ दीर्घ
acpi_video_bqc_value_to_level(काष्ठा acpi_video_device *device,
			      अचिन्हित दीर्घ दीर्घ bqc_value)
अणु
	अचिन्हित दीर्घ दीर्घ level;

	अगर (device->brightness->flags._BQC_use_index) अणु
		/*
		 * _BQC वापसs an index that करोesn't account क्रम the first 2
		 * items with special meaning (see क्रमागत acpi_video_level_idx),
		 * so we need to compensate क्रम that by offsetting ourselves
		 */
		अगर (device->brightness->flags._BCL_reversed)
			bqc_value = device->brightness->count -
				ACPI_VIDEO_FIRST_LEVEL - 1 - bqc_value;

		level = device->brightness->levels[bqc_value +
						   ACPI_VIDEO_FIRST_LEVEL];
	पूर्ण अन्यथा अणु
		level = bqc_value;
	पूर्ण

	level += bqc_offset_aml_bug_workaround;

	वापस level;
पूर्ण

अटल पूर्णांक
acpi_video_device_lcd_get_level_current(काष्ठा acpi_video_device *device,
					अचिन्हित दीर्घ दीर्घ *level, bool raw)
अणु
	acpi_status status = AE_OK;
	पूर्णांक i;

	अगर (device->cap._BQC || device->cap._BCQ) अणु
		अक्षर *buf = device->cap._BQC ? "_BQC" : "_BCQ";

		status = acpi_evaluate_पूर्णांकeger(device->dev->handle, buf,
						शून्य, level);
		अगर (ACPI_SUCCESS(status)) अणु
			अगर (raw) अणु
				/*
				 * Caller has indicated he wants the raw
				 * value वापसed by _BQC, so करोn't furtherly
				 * mess with the value.
				 */
				वापस 0;
			पूर्ण

			*level = acpi_video_bqc_value_to_level(device, *level);

			क्रम (i = ACPI_VIDEO_FIRST_LEVEL;
			     i < device->brightness->count; i++)
				अगर (device->brightness->levels[i] == *level) अणु
					device->brightness->curr = *level;
					वापस 0;
				पूर्ण
			/*
			 * BQC वापसed an invalid level.
			 * Stop using it.
			 */
			acpi_handle_info(device->dev->handle,
					 "%s returned an invalid level", buf);
			device->cap._BQC = device->cap._BCQ = 0;
		पूर्ण अन्यथा अणु
			/*
			 * Fixme:
			 * should we वापस an error or ignore this failure?
			 * dev->brightness->curr is a cached value which stores
			 * the correct current backlight level in most हालs.
			 * ACPI video backlight still works w/ buggy _BQC.
			 * http://bugzilla.kernel.org/show_bug.cgi?id=12233
			 */
			acpi_handle_info(device->dev->handle,
					 "%s evaluation failed", buf);
			device->cap._BQC = device->cap._BCQ = 0;
		पूर्ण
	पूर्ण

	*level = device->brightness->curr;
	वापस 0;
पूर्ण

अटल पूर्णांक
acpi_video_device_EDID(काष्ठा acpi_video_device *device,
		       जोड़ acpi_object **edid, sमाप_प्रकार length)
अणु
	पूर्णांक status;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;
	जोड़ acpi_object arg0 = अणु ACPI_TYPE_INTEGER पूर्ण;
	काष्ठा acpi_object_list args = अणु 1, &arg0 पूर्ण;


	*edid = शून्य;

	अगर (!device)
		वापस -ENODEV;
	अगर (length == 128)
		arg0.पूर्णांकeger.value = 1;
	अन्यथा अगर (length == 256)
		arg0.पूर्णांकeger.value = 2;
	अन्यथा
		वापस -EINVAL;

	status = acpi_evaluate_object(device->dev->handle, "_DDC", &args, &buffer);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	obj = buffer.poपूर्णांकer;

	अगर (obj && obj->type == ACPI_TYPE_BUFFER)
		*edid = obj;
	अन्यथा अणु
		acpi_handle_info(device->dev->handle, "Invalid _DDC data\n");
		status = -EFAULT;
		kमुक्त(obj);
	पूर्ण

	वापस status;
पूर्ण

/* bus */

/*
 *  Arg:
 *	video		: video bus device poपूर्णांकer
 *	bios_flag	:
 *		0.	The प्रणाली BIOS should NOT स्वतःmatically चयन(toggle)
 *			the active display output.
 *		1.	The प्रणाली BIOS should स्वतःmatically चयन (toggle) the
 *			active display output. No चयन event.
 *		2.	The _DGS value should be locked.
 *		3.	The प्रणाली BIOS should not स्वतःmatically चयन (toggle) the
 *			active display output, but instead generate the display चयन
 *			event notअगरy code.
 *	lcd_flag	:
 *		0.	The प्रणाली BIOS should स्वतःmatically control the brightness level
 *			of the LCD when:
 *			- the घातer changes from AC to DC (ACPI appendix B)
 *			- a brightness hotkey माला_लो pressed (implied by Win7/8 backlight करोcs)
 *		1.	The प्रणाली BIOS should NOT स्वतःmatically control the brightness
 *			level of the LCD when:
 *			- the घातer changes from AC to DC (ACPI appendix B)
 *			- a brightness hotkey माला_लो pressed (implied by Win7/8 backlight करोcs)
 *  Return Value:
 *		-EINVAL	wrong arg.
 */

अटल पूर्णांक
acpi_video_bus_DOS(काष्ठा acpi_video_bus *video, पूर्णांक bios_flag, पूर्णांक lcd_flag)
अणु
	acpi_status status;

	अगर (!video->cap._DOS)
		वापस 0;

	अगर (bios_flag < 0 || bios_flag > 3 || lcd_flag < 0 || lcd_flag > 1)
		वापस -EINVAL;
	video->करोs_setting = (lcd_flag << 2) | bios_flag;
	status = acpi_execute_simple_method(video->device->handle, "_DOS",
					    (lcd_flag << 2) | bios_flag);
	अगर (ACPI_FAILURE(status))
		वापस -EIO;

	वापस 0;
पूर्ण

/*
 * Simple comparison function used to sort backlight levels.
 */

अटल पूर्णांक
acpi_video_cmp_level(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	वापस *(पूर्णांक *)a - *(पूर्णांक *)b;
पूर्ण

/*
 * Decides अगर _BQC/_BCQ क्रम this प्रणाली is usable
 *
 * We करो this by changing the level first and then पढ़ो out the current
 * brightness level, अगर the value करोes not match, find out अगर it is using
 * index. If not, clear the _BQC/_BCQ capability.
 */
अटल पूर्णांक acpi_video_bqc_quirk(काष्ठा acpi_video_device *device,
				पूर्णांक max_level, पूर्णांक current_level)
अणु
	काष्ठा acpi_video_device_brightness *br = device->brightness;
	पूर्णांक result;
	अचिन्हित दीर्घ दीर्घ level;
	पूर्णांक test_level;

	/* करोn't mess with existing known broken प्रणालीs */
	अगर (bqc_offset_aml_bug_workaround)
		वापस 0;

	/*
	 * Some प्रणालीs always report current brightness level as maximum
	 * through _BQC, we need to test another value क्रम them. However,
	 * there is a subtlety:
	 *
	 * If the _BCL package ordering is descending, the first level
	 * (br->levels[2]) is likely to be 0, and अगर the number of levels
	 * matches the number of steps, we might confuse a वापसed level to
	 * mean the index.
	 *
	 * For example:
	 *
	 *     current_level = max_level = 100
	 *     test_level = 0
	 *     वापसed level = 100
	 *
	 * In this हाल 100 means the level, not the index, and _BCM failed.
	 * Still, अगर the _BCL package ordering is descending, the index of
	 * level 0 is also 100, so we assume _BQC is indexed, when it's not.
	 *
	 * This causes all _BQC calls to वापस bogus values causing weird
	 * behavior from the user's perspective.  For example:
	 *
	 * xbacklight -set 10; xbacklight -set 20;
	 *
	 * would flash to 90% and then slowly करोwn to the desired level (20).
	 *
	 * The solution is simple; test anything other than the first level
	 * (e.g. 1).
	 */
	test_level = current_level == max_level
		? br->levels[ACPI_VIDEO_FIRST_LEVEL + 1]
		: max_level;

	result = acpi_video_device_lcd_set_level(device, test_level);
	अगर (result)
		वापस result;

	result = acpi_video_device_lcd_get_level_current(device, &level, true);
	अगर (result)
		वापस result;

	अगर (level != test_level) अणु
		/* buggy _BQC found, need to find out अगर it uses index */
		अगर (level < br->count) अणु
			अगर (br->flags._BCL_reversed)
				level = br->count - ACPI_VIDEO_FIRST_LEVEL - 1 - level;
			अगर (br->levels[level + ACPI_VIDEO_FIRST_LEVEL] == test_level)
				br->flags._BQC_use_index = 1;
		पूर्ण

		अगर (!br->flags._BQC_use_index)
			device->cap._BQC = device->cap._BCQ = 0;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक acpi_video_get_levels(काष्ठा acpi_device *device,
			  काष्ठा acpi_video_device_brightness **dev_br,
			  पूर्णांक *pmax_level)
अणु
	जोड़ acpi_object *obj = शून्य;
	पूर्णांक i, max_level = 0, count = 0, level_ac_battery = 0;
	जोड़ acpi_object *o;
	काष्ठा acpi_video_device_brightness *br = शून्य;
	पूर्णांक result = 0;
	u32 value;

	अगर (ACPI_FAILURE(acpi_video_device_lcd_query_levels(device->handle, &obj))) अणु
		acpi_handle_debug(device->handle,
				  "Could not query available LCD brightness level\n");
		result = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (obj->package.count < ACPI_VIDEO_FIRST_LEVEL) अणु
		result = -EINVAL;
		जाओ out;
	पूर्ण

	br = kzalloc(माप(*br), GFP_KERNEL);
	अगर (!br) अणु
		result = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * Note that we have to reserve 2 extra items (ACPI_VIDEO_FIRST_LEVEL),
	 * in order to account क्रम buggy BIOS which करोn't export the first two
	 * special levels (see below)
	 */
	br->levels = kदो_स्मृति_array(obj->package.count + ACPI_VIDEO_FIRST_LEVEL,
				   माप(*br->levels),
				   GFP_KERNEL);
	अगर (!br->levels) अणु
		result = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	क्रम (i = 0; i < obj->package.count; i++) अणु
		o = (जोड़ acpi_object *)&obj->package.elements[i];
		अगर (o->type != ACPI_TYPE_INTEGER) अणु
			acpi_handle_info(device->handle, "Invalid data\n");
			जारी;
		पूर्ण
		value = (u32) o->पूर्णांकeger.value;
		/* Skip duplicate entries */
		अगर (count > ACPI_VIDEO_FIRST_LEVEL
		    && br->levels[count - 1] == value)
			जारी;

		br->levels[count] = value;

		अगर (br->levels[count] > max_level)
			max_level = br->levels[count];
		count++;
	पूर्ण

	/*
	 * some buggy BIOS करोn't export the levels
	 * when machine is on AC/Battery in _BCL package.
	 * In this हाल, the first two elements in _BCL packages
	 * are also supported brightness levels that OS should take care of.
	 */
	क्रम (i = ACPI_VIDEO_FIRST_LEVEL; i < count; i++) अणु
		अगर (br->levels[i] == br->levels[ACPI_VIDEO_AC_LEVEL])
			level_ac_battery++;
		अगर (br->levels[i] == br->levels[ACPI_VIDEO_BATTERY_LEVEL])
			level_ac_battery++;
	पूर्ण

	अगर (level_ac_battery < ACPI_VIDEO_FIRST_LEVEL) अणु
		level_ac_battery = ACPI_VIDEO_FIRST_LEVEL - level_ac_battery;
		br->flags._BCL_no_ac_battery_levels = 1;
		क्रम (i = (count - 1 + level_ac_battery);
		     i >= ACPI_VIDEO_FIRST_LEVEL; i--)
			br->levels[i] = br->levels[i - level_ac_battery];
		count += level_ac_battery;
	पूर्ण अन्यथा अगर (level_ac_battery > ACPI_VIDEO_FIRST_LEVEL)
		acpi_handle_info(device->handle,
				 "Too many duplicates in _BCL package");

	/* Check अगर the _BCL package is in a reversed order */
	अगर (max_level == br->levels[ACPI_VIDEO_FIRST_LEVEL]) अणु
		br->flags._BCL_reversed = 1;
		sort(&br->levels[ACPI_VIDEO_FIRST_LEVEL],
		     count - ACPI_VIDEO_FIRST_LEVEL,
		     माप(br->levels[ACPI_VIDEO_FIRST_LEVEL]),
		     acpi_video_cmp_level, शून्य);
	पूर्ण अन्यथा अगर (max_level != br->levels[count - 1])
		acpi_handle_info(device->handle,
				 "Found unordered _BCL package");

	br->count = count;
	*dev_br = br;
	अगर (pmax_level)
		*pmax_level = max_level;

out:
	kमुक्त(obj);
	वापस result;
out_मुक्त:
	kमुक्त(br);
	जाओ out;
पूर्ण
EXPORT_SYMBOL(acpi_video_get_levels);

/*
 *  Arg:
 *	device	: video output device (LCD, CRT, ..)
 *
 *  Return Value:
 *	Maximum brightness level
 *
 *  Allocate and initialize device->brightness.
 */

अटल पूर्णांक
acpi_video_init_brightness(काष्ठा acpi_video_device *device)
अणु
	पूर्णांक i, max_level = 0;
	अचिन्हित दीर्घ दीर्घ level, level_old;
	काष्ठा acpi_video_device_brightness *br = शून्य;
	पूर्णांक result;

	result = acpi_video_get_levels(device->dev, &br, &max_level);
	अगर (result)
		वापस result;
	device->brightness = br;

	/* _BQC uses INDEX जबतक _BCL uses VALUE in some laptops */
	br->curr = level = max_level;

	अगर (!device->cap._BQC)
		जाओ set_level;

	result = acpi_video_device_lcd_get_level_current(device,
							 &level_old, true);
	अगर (result)
		जाओ out_मुक्त_levels;

	result = acpi_video_bqc_quirk(device, max_level, level_old);
	अगर (result)
		जाओ out_मुक्त_levels;
	/*
	 * cap._BQC may get cleared due to _BQC is found to be broken
	 * in acpi_video_bqc_quirk, so check again here.
	 */
	अगर (!device->cap._BQC)
		जाओ set_level;

	level = acpi_video_bqc_value_to_level(device, level_old);
	/*
	 * On some buggy laptops, _BQC वापसs an uninitialized
	 * value when invoked क्रम the first समय, i.e.
	 * level_old is invalid (no matter whether it's a level
	 * or an index). Set the backlight to max_level in this हाल.
	 */
	क्रम (i = ACPI_VIDEO_FIRST_LEVEL; i < br->count; i++)
		अगर (level == br->levels[i])
			अवरोध;
	अगर (i == br->count || !level)
		level = max_level;

set_level:
	result = acpi_video_device_lcd_set_level(device, level);
	अगर (result)
		जाओ out_मुक्त_levels;

	acpi_handle_debug(device->dev->handle, "found %d brightness levels\n",
			  br->count - ACPI_VIDEO_FIRST_LEVEL);

	वापस 0;

out_मुक्त_levels:
	kमुक्त(br->levels);
	kमुक्त(br);
	device->brightness = शून्य;
	वापस result;
पूर्ण

/*
 *  Arg:
 *	device	: video output device (LCD, CRT, ..)
 *
 *  Return Value:
 *	None
 *
 *  Find out all required AML methods defined under the output
 *  device.
 */

अटल व्योम acpi_video_device_find_cap(काष्ठा acpi_video_device *device)
अणु
	अगर (acpi_has_method(device->dev->handle, "_ADR"))
		device->cap._ADR = 1;
	अगर (acpi_has_method(device->dev->handle, "_BCL"))
		device->cap._BCL = 1;
	अगर (acpi_has_method(device->dev->handle, "_BCM"))
		device->cap._BCM = 1;
	अगर (acpi_has_method(device->dev->handle, "_BQC")) अणु
		device->cap._BQC = 1;
	पूर्ण अन्यथा अगर (acpi_has_method(device->dev->handle, "_BCQ")) अणु
		acpi_handle_info(device->dev->handle,
				 "_BCQ is used instead of _BQC\n");
		device->cap._BCQ = 1;
	पूर्ण

	अगर (acpi_has_method(device->dev->handle, "_DDC"))
		device->cap._DDC = 1;
पूर्ण

/*
 *  Arg:
 *	device	: video output device (VGA)
 *
 *  Return Value:
 *	None
 *
 *  Find out all required AML methods defined under the video bus device.
 */

अटल व्योम acpi_video_bus_find_cap(काष्ठा acpi_video_bus *video)
अणु
	अगर (acpi_has_method(video->device->handle, "_DOS"))
		video->cap._DOS = 1;
	अगर (acpi_has_method(video->device->handle, "_DOD"))
		video->cap._DOD = 1;
	अगर (acpi_has_method(video->device->handle, "_ROM"))
		video->cap._ROM = 1;
	अगर (acpi_has_method(video->device->handle, "_GPD"))
		video->cap._GPD = 1;
	अगर (acpi_has_method(video->device->handle, "_SPD"))
		video->cap._SPD = 1;
	अगर (acpi_has_method(video->device->handle, "_VPO"))
		video->cap._VPO = 1;
पूर्ण

/*
 * Check whether the video bus device has required AML method to
 * support the desired features
 */

अटल पूर्णांक acpi_video_bus_check(काष्ठा acpi_video_bus *video)
अणु
	acpi_status status = -ENOENT;
	काष्ठा pci_dev *dev;

	अगर (!video)
		वापस -EINVAL;

	dev = acpi_get_pci_dev(video->device->handle);
	अगर (!dev)
		वापस -ENODEV;
	pci_dev_put(dev);

	/*
	 * Since there is no HID, CID and so on क्रम VGA driver, we have
	 * to check well known required nodes.
	 */

	/* Does this device support video चयनing? */
	अगर (video->cap._DOS || video->cap._DOD) अणु
		अगर (!video->cap._DOS) अणु
			pr_info(FW_BUG "ACPI(%s) defines _DOD but not _DOS\n",
				acpi_device_bid(video->device));
		पूर्ण
		video->flags.multihead = 1;
		status = 0;
	पूर्ण

	/* Does this device support retrieving a video ROM? */
	अगर (video->cap._ROM) अणु
		video->flags.rom = 1;
		status = 0;
	पूर्ण

	/* Does this device support configuring which video device to POST? */
	अगर (video->cap._GPD && video->cap._SPD && video->cap._VPO) अणु
		video->flags.post = 1;
		status = 0;
	पूर्ण

	वापस status;
पूर्ण

/*
 * --------------------------------------------------------------------------
 *                               Driver Interface
 * --------------------------------------------------------------------------
 */

/* device पूर्णांकerface */
अटल काष्ठा acpi_video_device_attrib *
acpi_video_get_device_attr(काष्ठा acpi_video_bus *video, अचिन्हित दीर्घ device_id)
अणु
	काष्ठा acpi_video_क्रमागतerated_device *ids;
	पूर्णांक i;

	क्रम (i = 0; i < video->attached_count; i++) अणु
		ids = &video->attached_array[i];
		अगर ((ids->value.पूर्णांक_val & 0xffff) == device_id)
			वापस &ids->value.attrib;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक
acpi_video_get_device_type(काष्ठा acpi_video_bus *video,
			   अचिन्हित दीर्घ device_id)
अणु
	काष्ठा acpi_video_क्रमागतerated_device *ids;
	पूर्णांक i;

	क्रम (i = 0; i < video->attached_count; i++) अणु
		ids = &video->attached_array[i];
		अगर ((ids->value.पूर्णांक_val & 0xffff) == device_id)
			वापस ids->value.पूर्णांक_val;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
acpi_video_bus_get_one_device(काष्ठा acpi_device *device,
			      काष्ठा acpi_video_bus *video)
अणु
	अचिन्हित दीर्घ दीर्घ device_id;
	पूर्णांक status, device_type;
	काष्ठा acpi_video_device *data;
	काष्ठा acpi_video_device_attrib *attribute;

	status =
	    acpi_evaluate_पूर्णांकeger(device->handle, "_ADR", शून्य, &device_id);
	/* Some device omits _ADR, we skip them instead of fail */
	अगर (ACPI_FAILURE(status))
		वापस 0;

	data = kzalloc(माप(काष्ठा acpi_video_device), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	म_नकल(acpi_device_name(device), ACPI_VIDEO_DEVICE_NAME);
	म_नकल(acpi_device_class(device), ACPI_VIDEO_CLASS);
	device->driver_data = data;

	data->device_id = device_id;
	data->video = video;
	data->dev = device;
	INIT_DELAYED_WORK(&data->चयन_brightness_work,
			  acpi_video_चयन_brightness);

	attribute = acpi_video_get_device_attr(video, device_id);

	अगर (attribute && (attribute->device_id_scheme || device_id_scheme)) अणु
		चयन (attribute->display_type) अणु
		हाल ACPI_VIDEO_DISPLAY_CRT:
			data->flags.crt = 1;
			अवरोध;
		हाल ACPI_VIDEO_DISPLAY_TV:
			data->flags.tvout = 1;
			अवरोध;
		हाल ACPI_VIDEO_DISPLAY_DVI:
			data->flags.dvi = 1;
			अवरोध;
		हाल ACPI_VIDEO_DISPLAY_LCD:
			data->flags.lcd = 1;
			अवरोध;
		शेष:
			data->flags.unknown = 1;
			अवरोध;
		पूर्ण
		अगर (attribute->bios_can_detect)
			data->flags.bios = 1;
	पूर्ण अन्यथा अणु
		/* Check क्रम legacy IDs */
		device_type = acpi_video_get_device_type(video, device_id);
		/* Ignore bits 16 and 18-20 */
		चयन (device_type & 0xffe2ffff) अणु
		हाल ACPI_VIDEO_DISPLAY_LEGACY_MONITOR:
			data->flags.crt = 1;
			अवरोध;
		हाल ACPI_VIDEO_DISPLAY_LEGACY_PANEL:
			data->flags.lcd = 1;
			अवरोध;
		हाल ACPI_VIDEO_DISPLAY_LEGACY_TV:
			data->flags.tvout = 1;
			अवरोध;
		शेष:
			data->flags.unknown = 1;
		पूर्ण
	पूर्ण

	acpi_video_device_bind(video, data);
	acpi_video_device_find_cap(data);

	mutex_lock(&video->device_list_lock);
	list_add_tail(&data->entry, &video->video_device_list);
	mutex_unlock(&video->device_list_lock);

	वापस status;
पूर्ण

/*
 *  Arg:
 *	video	: video bus device
 *
 *  Return:
 *	none
 *
 *  Enumerate the video device list of the video bus,
 *  bind the ids with the corresponding video devices
 *  under the video bus.
 */

अटल व्योम acpi_video_device_rebind(काष्ठा acpi_video_bus *video)
अणु
	काष्ठा acpi_video_device *dev;

	mutex_lock(&video->device_list_lock);

	list_क्रम_each_entry(dev, &video->video_device_list, entry)
		acpi_video_device_bind(video, dev);

	mutex_unlock(&video->device_list_lock);
पूर्ण

/*
 *  Arg:
 *	video	: video bus device
 *	device	: video output device under the video
 *		bus
 *
 *  Return:
 *	none
 *
 *  Bind the ids with the corresponding video devices
 *  under the video bus.
 */

अटल व्योम
acpi_video_device_bind(काष्ठा acpi_video_bus *video,
		       काष्ठा acpi_video_device *device)
अणु
	काष्ठा acpi_video_क्रमागतerated_device *ids;
	पूर्णांक i;

	क्रम (i = 0; i < video->attached_count; i++) अणु
		ids = &video->attached_array[i];
		अगर (device->device_id == (ids->value.पूर्णांक_val & 0xffff)) अणु
			ids->bind_info = device;
			acpi_handle_debug(video->device->handle, "%s: %d\n",
					  __func__, i);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool acpi_video_device_in_करोd(काष्ठा acpi_video_device *device)
अणु
	काष्ठा acpi_video_bus *video = device->video;
	पूर्णांक i;

	/*
	 * If we have a broken _DOD or we have more than 8 output devices
	 * under the graphics controller node that we can't proper deal with
	 * in the operation region code currently, no need to test.
	 */
	अगर (!video->attached_count || video->child_count > 8)
		वापस true;

	क्रम (i = 0; i < video->attached_count; i++) अणु
		अगर ((video->attached_array[i].value.पूर्णांक_val & 0xfff) ==
		    (device->device_id & 0xfff))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 *  Arg:
 *	video	: video bus device
 *
 *  Return:
 *	< 0	: error
 *
 *  Call _DOD to क्रमागतerate all devices attached to display adapter
 *
 */

अटल पूर्णांक acpi_video_device_क्रमागतerate(काष्ठा acpi_video_bus *video)
अणु
	पूर्णांक status;
	पूर्णांक count;
	पूर्णांक i;
	काष्ठा acpi_video_क्रमागतerated_device *active_list;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *करोd = शून्य;
	जोड़ acpi_object *obj;

	अगर (!video->cap._DOD)
		वापस AE_NOT_EXIST;

	status = acpi_evaluate_object(video->device->handle, "_DOD", शून्य, &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_handle_info(video->device->handle,
				 "_DOD evaluation failed: %s\n",
				 acpi_क्रमmat_exception(status));
		वापस status;
	पूर्ण

	करोd = buffer.poपूर्णांकer;
	अगर (!करोd || (करोd->type != ACPI_TYPE_PACKAGE)) अणु
		acpi_handle_info(video->device->handle, "Invalid _DOD data\n");
		status = -EFAULT;
		जाओ out;
	पूर्ण

	acpi_handle_debug(video->device->handle, "Found %d video heads in _DOD\n",
			  करोd->package.count);

	active_list = kसुस्मृति(1 + करोd->package.count,
			      माप(काष्ठा acpi_video_क्रमागतerated_device),
			      GFP_KERNEL);
	अगर (!active_list) अणु
		status = -ENOMEM;
		जाओ out;
	पूर्ण

	count = 0;
	क्रम (i = 0; i < करोd->package.count; i++) अणु
		obj = &करोd->package.elements[i];

		अगर (obj->type != ACPI_TYPE_INTEGER) अणु
			acpi_handle_info(video->device->handle,
					 "Invalid _DOD data in element %d\n", i);
			जारी;
		पूर्ण

		active_list[count].value.पूर्णांक_val = obj->पूर्णांकeger.value;
		active_list[count].bind_info = शून्य;

		acpi_handle_debug(video->device->handle,
				  "_DOD element[%d] = %d\n", i,
				  (पूर्णांक)obj->पूर्णांकeger.value);

		count++;
	पूर्ण

	kमुक्त(video->attached_array);

	video->attached_array = active_list;
	video->attached_count = count;

out:
	kमुक्त(buffer.poपूर्णांकer);
	वापस status;
पूर्ण

अटल पूर्णांक
acpi_video_get_next_level(काष्ठा acpi_video_device *device,
			  u32 level_current, u32 event)
अणु
	पूर्णांक min, max, min_above, max_below, i, l, delta = 255;
	max = max_below = 0;
	min = min_above = 255;
	/* Find बंदst level to level_current */
	क्रम (i = ACPI_VIDEO_FIRST_LEVEL; i < device->brightness->count; i++) अणु
		l = device->brightness->levels[i];
		अगर (असल(l - level_current) < असल(delta)) अणु
			delta = l - level_current;
			अगर (!delta)
				अवरोध;
		पूर्ण
	पूर्ण
	/* Adjust level_current to बंदst available level */
	level_current += delta;
	क्रम (i = ACPI_VIDEO_FIRST_LEVEL; i < device->brightness->count; i++) अणु
		l = device->brightness->levels[i];
		अगर (l < min)
			min = l;
		अगर (l > max)
			max = l;
		अगर (l < min_above && l > level_current)
			min_above = l;
		अगर (l > max_below && l < level_current)
			max_below = l;
	पूर्ण

	चयन (event) अणु
	हाल ACPI_VIDEO_NOTIFY_CYCLE_BRIGHTNESS:
		वापस (level_current < max) ? min_above : min;
	हाल ACPI_VIDEO_NOTIFY_INC_BRIGHTNESS:
		वापस (level_current < max) ? min_above : max;
	हाल ACPI_VIDEO_NOTIFY_DEC_BRIGHTNESS:
		वापस (level_current > min) ? max_below : min;
	हाल ACPI_VIDEO_NOTIFY_ZERO_BRIGHTNESS:
	हाल ACPI_VIDEO_NOTIFY_DISPLAY_OFF:
		वापस 0;
	शेष:
		वापस level_current;
	पूर्ण
पूर्ण

अटल व्योम
acpi_video_चयन_brightness(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा acpi_video_device *device = container_of(to_delayed_work(work),
			     काष्ठा acpi_video_device, चयन_brightness_work);
	अचिन्हित दीर्घ दीर्घ level_current, level_next;
	पूर्णांक event = device->चयन_brightness_event;
	पूर्णांक result = -EINVAL;

	/* no warning message अगर acpi_backlight=venकरोr or a quirk is used */
	अगर (!device->backlight)
		वापस;

	अगर (!device->brightness)
		जाओ out;

	result = acpi_video_device_lcd_get_level_current(device,
							 &level_current,
							 false);
	अगर (result)
		जाओ out;

	level_next = acpi_video_get_next_level(device, level_current, event);

	result = acpi_video_device_lcd_set_level(device, level_next);

	अगर (!result)
		backlight_क्रमce_update(device->backlight,
				       BACKLIGHT_UPDATE_HOTKEY);

out:
	अगर (result)
		acpi_handle_info(device->dev->handle,
				 "Failed to switch brightness\n");
पूर्ण

पूर्णांक acpi_video_get_edid(काष्ठा acpi_device *device, पूर्णांक type, पूर्णांक device_id,
			व्योम **edid)
अणु
	काष्ठा acpi_video_bus *video;
	काष्ठा acpi_video_device *video_device;
	जोड़ acpi_object *buffer = शून्य;
	acpi_status status;
	पूर्णांक i, length;

	अगर (!device || !acpi_driver_data(device))
		वापस -EINVAL;

	video = acpi_driver_data(device);

	क्रम (i = 0; i < video->attached_count; i++) अणु
		video_device = video->attached_array[i].bind_info;
		length = 256;

		अगर (!video_device)
			जारी;

		अगर (!video_device->cap._DDC)
			जारी;

		अगर (type) अणु
			चयन (type) अणु
			हाल ACPI_VIDEO_DISPLAY_CRT:
				अगर (!video_device->flags.crt)
					जारी;
				अवरोध;
			हाल ACPI_VIDEO_DISPLAY_TV:
				अगर (!video_device->flags.tvout)
					जारी;
				अवरोध;
			हाल ACPI_VIDEO_DISPLAY_DVI:
				अगर (!video_device->flags.dvi)
					जारी;
				अवरोध;
			हाल ACPI_VIDEO_DISPLAY_LCD:
				अगर (!video_device->flags.lcd)
					जारी;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (video_device->device_id != device_id) अणु
			जारी;
		पूर्ण

		status = acpi_video_device_EDID(video_device, &buffer, length);

		अगर (ACPI_FAILURE(status) || !buffer ||
		    buffer->type != ACPI_TYPE_BUFFER) अणु
			length = 128;
			status = acpi_video_device_EDID(video_device, &buffer,
							length);
			अगर (ACPI_FAILURE(status) || !buffer ||
			    buffer->type != ACPI_TYPE_BUFFER) अणु
				जारी;
			पूर्ण
		पूर्ण

		*edid = buffer->buffer.poपूर्णांकer;
		वापस length;
	पूर्ण

	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL(acpi_video_get_edid);

अटल पूर्णांक
acpi_video_bus_get_devices(काष्ठा acpi_video_bus *video,
			   काष्ठा acpi_device *device)
अणु
	पूर्णांक status = 0;
	काष्ठा acpi_device *dev;

	/*
	 * There are प्रणालीs where video module known to work fine regardless
	 * of broken _DOD and ignoring वापसed value here करोesn't cause
	 * any issues later.
	 */
	acpi_video_device_क्रमागतerate(video);

	list_क्रम_each_entry(dev, &device->children, node) अणु

		status = acpi_video_bus_get_one_device(dev, video);
		अगर (status) अणु
			dev_err(&dev->dev, "Can't attach device\n");
			अवरोध;
		पूर्ण
		video->child_count++;
	पूर्ण
	वापस status;
पूर्ण

/* acpi_video पूर्णांकerface */

/*
 * Win8 requires setting bit2 of _DOS to let firmware know it shouldn't
 * perक्रमm any स्वतःmatic brightness change on receiving a notअगरication.
 */
अटल पूर्णांक acpi_video_bus_start_devices(काष्ठा acpi_video_bus *video)
अणु
	वापस acpi_video_bus_DOS(video, 0,
				  acpi_osi_is_win8() ? 1 : 0);
पूर्ण

अटल पूर्णांक acpi_video_bus_stop_devices(काष्ठा acpi_video_bus *video)
अणु
	वापस acpi_video_bus_DOS(video, 0,
				  acpi_osi_is_win8() ? 0 : 1);
पूर्ण

अटल व्योम acpi_video_bus_notअगरy(काष्ठा acpi_device *device, u32 event)
अणु
	काष्ठा acpi_video_bus *video = acpi_driver_data(device);
	काष्ठा input_dev *input;
	पूर्णांक keycode = 0;

	अगर (!video || !video->input)
		वापस;

	input = video->input;

	चयन (event) अणु
	हाल ACPI_VIDEO_NOTIFY_SWITCH:	/* User requested a चयन,
					 * most likely via hotkey. */
		keycode = KEY_SWITCHVIDEOMODE;
		अवरोध;

	हाल ACPI_VIDEO_NOTIFY_PROBE:	/* User plugged in or हटाओd a video
					 * connector. */
		acpi_video_device_क्रमागतerate(video);
		acpi_video_device_rebind(video);
		keycode = KEY_SWITCHVIDEOMODE;
		अवरोध;

	हाल ACPI_VIDEO_NOTIFY_CYCLE:	/* Cycle Display output hotkey pressed. */
		keycode = KEY_SWITCHVIDEOMODE;
		अवरोध;
	हाल ACPI_VIDEO_NOTIFY_NEXT_OUTPUT:	/* Next Display output hotkey pressed. */
		keycode = KEY_VIDEO_NEXT;
		अवरोध;
	हाल ACPI_VIDEO_NOTIFY_PREV_OUTPUT:	/* previous Display output hotkey pressed. */
		keycode = KEY_VIDEO_PREV;
		अवरोध;

	शेष:
		acpi_handle_debug(device->handle, "Unsupported event [0x%x]\n",
				  event);
		अवरोध;
	पूर्ण

	अगर (acpi_notअगरier_call_chain(device, event, 0))
		/* Something vetoed the keypress. */
		keycode = 0;

	अगर (keycode && (report_key_events & REPORT_OUTPUT_KEY_EVENTS)) अणु
		input_report_key(input, keycode, 1);
		input_sync(input);
		input_report_key(input, keycode, 0);
		input_sync(input);
	पूर्ण

	वापस;
पूर्ण

अटल व्योम brightness_चयन_event(काष्ठा acpi_video_device *video_device,
				    u32 event)
अणु
	अगर (!brightness_चयन_enabled)
		वापस;

	video_device->चयन_brightness_event = event;
	schedule_delayed_work(&video_device->चयन_brightness_work, HZ / 10);
पूर्ण

अटल व्योम acpi_video_device_notअगरy(acpi_handle handle, u32 event, व्योम *data)
अणु
	काष्ठा acpi_video_device *video_device = data;
	काष्ठा acpi_device *device = शून्य;
	काष्ठा acpi_video_bus *bus;
	काष्ठा input_dev *input;
	पूर्णांक keycode = 0;

	अगर (!video_device)
		वापस;

	device = video_device->dev;
	bus = video_device->video;
	input = bus->input;

	अगर (hw_changes_brightness > 0) अणु
		अगर (video_device->backlight)
			backlight_क्रमce_update(video_device->backlight,
					       BACKLIGHT_UPDATE_HOTKEY);
		acpi_notअगरier_call_chain(device, event, 0);
		वापस;
	पूर्ण

	चयन (event) अणु
	हाल ACPI_VIDEO_NOTIFY_CYCLE_BRIGHTNESS:	/* Cycle brightness */
		brightness_चयन_event(video_device, event);
		keycode = KEY_BRIGHTNESS_CYCLE;
		अवरोध;
	हाल ACPI_VIDEO_NOTIFY_INC_BRIGHTNESS:	/* Increase brightness */
		brightness_चयन_event(video_device, event);
		keycode = KEY_BRIGHTNESSUP;
		अवरोध;
	हाल ACPI_VIDEO_NOTIFY_DEC_BRIGHTNESS:	/* Decrease brightness */
		brightness_चयन_event(video_device, event);
		keycode = KEY_BRIGHTNESSDOWN;
		अवरोध;
	हाल ACPI_VIDEO_NOTIFY_ZERO_BRIGHTNESS:	/* zero brightness */
		brightness_चयन_event(video_device, event);
		keycode = KEY_BRIGHTNESS_ZERO;
		अवरोध;
	हाल ACPI_VIDEO_NOTIFY_DISPLAY_OFF:	/* display device off */
		brightness_चयन_event(video_device, event);
		keycode = KEY_DISPLAY_OFF;
		अवरोध;
	शेष:
		acpi_handle_debug(handle, "Unsupported event [0x%x]\n", event);
		अवरोध;
	पूर्ण

	acpi_notअगरier_call_chain(device, event, 0);

	अगर (keycode && (report_key_events & REPORT_BRIGHTNESS_KEY_EVENTS)) अणु
		input_report_key(input, keycode, 1);
		input_sync(input);
		input_report_key(input, keycode, 0);
		input_sync(input);
	पूर्ण

	वापस;
पूर्ण

अटल पूर्णांक acpi_video_resume(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ val, व्योम *ign)
अणु
	काष्ठा acpi_video_bus *video;
	काष्ठा acpi_video_device *video_device;
	पूर्णांक i;

	चयन (val) अणु
	हाल PM_HIBERNATION_PREPARE:
	हाल PM_SUSPEND_PREPARE:
	हाल PM_RESTORE_PREPARE:
		वापस NOTIFY_DONE;
	पूर्ण

	video = container_of(nb, काष्ठा acpi_video_bus, pm_nb);

	dev_info(&video->device->dev, "Restoring backlight state\n");

	क्रम (i = 0; i < video->attached_count; i++) अणु
		video_device = video->attached_array[i].bind_info;
		अगर (video_device && video_device->brightness)
			acpi_video_device_lcd_set_level(video_device,
					video_device->brightness->curr);
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल acpi_status
acpi_video_bus_match(acpi_handle handle, u32 level, व्योम *context,
			व्योम **वापस_value)
अणु
	काष्ठा acpi_device *device = context;
	काष्ठा acpi_device *sibling;
	पूर्णांक result;

	अगर (handle == device->handle)
		वापस AE_CTRL_TERMINATE;

	result = acpi_bus_get_device(handle, &sibling);
	अगर (result)
		वापस AE_OK;

	अगर (!म_भेद(acpi_device_name(sibling), ACPI_VIDEO_BUS_NAME))
			वापस AE_ALREADY_EXISTS;

	वापस AE_OK;
पूर्ण

अटल व्योम acpi_video_dev_रेजिस्टर_backlight(काष्ठा acpi_video_device *device)
अणु
	काष्ठा backlight_properties props;
	काष्ठा pci_dev *pdev;
	acpi_handle acpi_parent;
	काष्ठा device *parent = शून्य;
	पूर्णांक result;
	अटल पूर्णांक count;
	अक्षर *name;

	result = acpi_video_init_brightness(device);
	अगर (result)
		वापस;

	अगर (disable_backlight_sysfs_अगर > 0)
		वापस;

	name = kaप्र_लिखो(GFP_KERNEL, "acpi_video%d", count);
	अगर (!name)
		वापस;
	count++;

	acpi_get_parent(device->dev->handle, &acpi_parent);

	pdev = acpi_get_pci_dev(acpi_parent);
	अगर (pdev) अणु
		parent = &pdev->dev;
		pci_dev_put(pdev);
	पूर्ण

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_FIRMWARE;
	props.max_brightness =
		device->brightness->count - ACPI_VIDEO_FIRST_LEVEL - 1;
	device->backlight = backlight_device_रेजिस्टर(name,
						      parent,
						      device,
						      &acpi_backlight_ops,
						      &props);
	kमुक्त(name);
	अगर (IS_ERR(device->backlight)) अणु
		device->backlight = शून्य;
		वापस;
	पूर्ण

	/*
	 * Save current brightness level in हाल we have to restore it
	 * beक्रमe acpi_video_device_lcd_set_level() is called next समय.
	 */
	device->backlight->props.brightness =
			acpi_video_get_brightness(device->backlight);

	device->cooling_dev = thermal_cooling_device_रेजिस्टर("LCD",
				device->dev, &video_cooling_ops);
	अगर (IS_ERR(device->cooling_dev)) अणु
		/*
		 * Set cooling_dev to शून्य so we करोn't crash trying to मुक्त it.
		 * Also, why the hell we are वापसing early and not attempt to
		 * रेजिस्टर video output अगर cooling device registration failed?
		 * -- dtor
		 */
		device->cooling_dev = शून्य;
		वापस;
	पूर्ण

	dev_info(&device->dev->dev, "registered as cooling_device%d\n",
		 device->cooling_dev->id);
	result = sysfs_create_link(&device->dev->dev.kobj,
			&device->cooling_dev->device.kobj,
			"thermal_cooling");
	अगर (result)
		pr_info("sysfs link creation failed\n");

	result = sysfs_create_link(&device->cooling_dev->device.kobj,
			&device->dev->dev.kobj, "device");
	अगर (result)
		pr_info("Reverse sysfs link creation failed\n");
पूर्ण

अटल व्योम acpi_video_run_bcl_क्रम_osi(काष्ठा acpi_video_bus *video)
अणु
	काष्ठा acpi_video_device *dev;
	जोड़ acpi_object *levels;

	mutex_lock(&video->device_list_lock);
	list_क्रम_each_entry(dev, &video->video_device_list, entry) अणु
		अगर (!acpi_video_device_lcd_query_levels(dev->dev->handle, &levels))
			kमुक्त(levels);
	पूर्ण
	mutex_unlock(&video->device_list_lock);
पूर्ण

अटल bool acpi_video_should_रेजिस्टर_backlight(काष्ठा acpi_video_device *dev)
अणु
	/*
	 * Do not create backlight device क्रम video output
	 * device that is not in the क्रमागतerated list.
	 */
	अगर (!acpi_video_device_in_करोd(dev)) अणु
		dev_dbg(&dev->dev->dev, "not in _DOD list, ignore\n");
		वापस false;
	पूर्ण

	अगर (only_lcd)
		वापस dev->flags.lcd;
	वापस true;
पूर्ण

अटल पूर्णांक acpi_video_bus_रेजिस्टर_backlight(काष्ठा acpi_video_bus *video)
अणु
	काष्ठा acpi_video_device *dev;

	अगर (video->backlight_रेजिस्टरed)
		वापस 0;

	acpi_video_run_bcl_क्रम_osi(video);

	अगर (acpi_video_get_backlight_type() != acpi_backlight_video)
		वापस 0;

	mutex_lock(&video->device_list_lock);
	list_क्रम_each_entry(dev, &video->video_device_list, entry) अणु
		अगर (acpi_video_should_रेजिस्टर_backlight(dev))
			acpi_video_dev_रेजिस्टर_backlight(dev);
	पूर्ण
	mutex_unlock(&video->device_list_lock);

	video->backlight_रेजिस्टरed = true;

	video->pm_nb.notअगरier_call = acpi_video_resume;
	video->pm_nb.priority = 0;
	वापस रेजिस्टर_pm_notअगरier(&video->pm_nb);
पूर्ण

अटल व्योम acpi_video_dev_unरेजिस्टर_backlight(काष्ठा acpi_video_device *device)
अणु
	अगर (device->backlight) अणु
		backlight_device_unरेजिस्टर(device->backlight);
		device->backlight = शून्य;
	पूर्ण
	अगर (device->brightness) अणु
		kमुक्त(device->brightness->levels);
		kमुक्त(device->brightness);
		device->brightness = शून्य;
	पूर्ण
	अगर (device->cooling_dev) अणु
		sysfs_हटाओ_link(&device->dev->dev.kobj, "thermal_cooling");
		sysfs_हटाओ_link(&device->cooling_dev->device.kobj, "device");
		thermal_cooling_device_unरेजिस्टर(device->cooling_dev);
		device->cooling_dev = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक acpi_video_bus_unरेजिस्टर_backlight(काष्ठा acpi_video_bus *video)
अणु
	काष्ठा acpi_video_device *dev;
	पूर्णांक error;

	अगर (!video->backlight_रेजिस्टरed)
		वापस 0;

	error = unरेजिस्टर_pm_notअगरier(&video->pm_nb);

	mutex_lock(&video->device_list_lock);
	list_क्रम_each_entry(dev, &video->video_device_list, entry)
		acpi_video_dev_unरेजिस्टर_backlight(dev);
	mutex_unlock(&video->device_list_lock);

	video->backlight_रेजिस्टरed = false;

	वापस error;
पूर्ण

अटल व्योम acpi_video_dev_add_notअगरy_handler(काष्ठा acpi_video_device *device)
अणु
	acpi_status status;
	काष्ठा acpi_device *adev = device->dev;

	status = acpi_install_notअगरy_handler(adev->handle, ACPI_DEVICE_NOTIFY,
					     acpi_video_device_notअगरy, device);
	अगर (ACPI_FAILURE(status))
		dev_err(&adev->dev, "Error installing notify handler\n");
	अन्यथा
		device->flags.notअगरy = 1;
पूर्ण

अटल पूर्णांक acpi_video_bus_add_notअगरy_handler(काष्ठा acpi_video_bus *video)
अणु
	काष्ठा input_dev *input;
	काष्ठा acpi_video_device *dev;
	पूर्णांक error;

	video->input = input = input_allocate_device();
	अगर (!input) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण

	error = acpi_video_bus_start_devices(video);
	अगर (error)
		जाओ err_मुक्त_input;

	snम_लिखो(video->phys, माप(video->phys),
			"%s/video/input0", acpi_device_hid(video->device));

	input->name = acpi_device_name(video->device);
	input->phys = video->phys;
	input->id.bustype = BUS_HOST;
	input->id.product = 0x06;
	input->dev.parent = &video->device->dev;
	input->evbit[0] = BIT(EV_KEY);
	set_bit(KEY_SWITCHVIDEOMODE, input->keybit);
	set_bit(KEY_VIDEO_NEXT, input->keybit);
	set_bit(KEY_VIDEO_PREV, input->keybit);
	set_bit(KEY_BRIGHTNESS_CYCLE, input->keybit);
	set_bit(KEY_BRIGHTNESSUP, input->keybit);
	set_bit(KEY_BRIGHTNESSDOWN, input->keybit);
	set_bit(KEY_BRIGHTNESS_ZERO, input->keybit);
	set_bit(KEY_DISPLAY_OFF, input->keybit);

	error = input_रेजिस्टर_device(input);
	अगर (error)
		जाओ err_stop_dev;

	mutex_lock(&video->device_list_lock);
	list_क्रम_each_entry(dev, &video->video_device_list, entry)
		acpi_video_dev_add_notअगरy_handler(dev);
	mutex_unlock(&video->device_list_lock);

	वापस 0;

err_stop_dev:
	acpi_video_bus_stop_devices(video);
err_मुक्त_input:
	input_मुक्त_device(input);
	video->input = शून्य;
out:
	वापस error;
पूर्ण

अटल व्योम acpi_video_dev_हटाओ_notअगरy_handler(काष्ठा acpi_video_device *dev)
अणु
	अगर (dev->flags.notअगरy) अणु
		acpi_हटाओ_notअगरy_handler(dev->dev->handle, ACPI_DEVICE_NOTIFY,
					   acpi_video_device_notअगरy);
		dev->flags.notअगरy = 0;
	पूर्ण
पूर्ण

अटल व्योम acpi_video_bus_हटाओ_notअगरy_handler(काष्ठा acpi_video_bus *video)
अणु
	काष्ठा acpi_video_device *dev;

	mutex_lock(&video->device_list_lock);
	list_क्रम_each_entry(dev, &video->video_device_list, entry)
		acpi_video_dev_हटाओ_notअगरy_handler(dev);
	mutex_unlock(&video->device_list_lock);

	acpi_video_bus_stop_devices(video);
	input_unरेजिस्टर_device(video->input);
	video->input = शून्य;
पूर्ण

अटल पूर्णांक acpi_video_bus_put_devices(काष्ठा acpi_video_bus *video)
अणु
	काष्ठा acpi_video_device *dev, *next;

	mutex_lock(&video->device_list_lock);
	list_क्रम_each_entry_safe(dev, next, &video->video_device_list, entry) अणु
		list_del(&dev->entry);
		kमुक्त(dev);
	पूर्ण
	mutex_unlock(&video->device_list_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक instance;

अटल पूर्णांक acpi_video_bus_add(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_video_bus *video;
	पूर्णांक error;
	acpi_status status;

	status = acpi_walk_namespace(ACPI_TYPE_DEVICE,
				device->parent->handle, 1,
				acpi_video_bus_match, शून्य,
				device, शून्य);
	अगर (status == AE_ALREADY_EXISTS) अणु
		pr_info(FW_BUG
			"Duplicate ACPI video bus devices for the"
			" same VGA controller, please try module "
			"parameter \"video.allow_duplicates=1\""
			"if the current driver doesn't work.\n");
		अगर (!allow_duplicates)
			वापस -ENODEV;
	पूर्ण

	video = kzalloc(माप(काष्ठा acpi_video_bus), GFP_KERNEL);
	अगर (!video)
		वापस -ENOMEM;

	/* a hack to fix the duplicate name "VID" problem on T61 */
	अगर (!म_भेद(device->pnp.bus_id, "VID")) अणु
		अगर (instance)
			device->pnp.bus_id[3] = '0' + instance;
		instance++;
	पूर्ण
	/* a hack to fix the duplicate name "VGA" problem on Pa 3553 */
	अगर (!म_भेद(device->pnp.bus_id, "VGA")) अणु
		अगर (instance)
			device->pnp.bus_id[3] = '0' + instance;
		instance++;
	पूर्ण

	video->device = device;
	म_नकल(acpi_device_name(device), ACPI_VIDEO_BUS_NAME);
	म_नकल(acpi_device_class(device), ACPI_VIDEO_CLASS);
	device->driver_data = video;

	acpi_video_bus_find_cap(video);
	error = acpi_video_bus_check(video);
	अगर (error)
		जाओ err_मुक्त_video;

	mutex_init(&video->device_list_lock);
	INIT_LIST_HEAD(&video->video_device_list);

	error = acpi_video_bus_get_devices(video, device);
	अगर (error)
		जाओ err_put_video;

	pr_info("%s [%s] (multi-head: %s  rom: %s  post: %s)\n",
	       ACPI_VIDEO_DEVICE_NAME, acpi_device_bid(device),
	       video->flags.multihead ? "yes" : "no",
	       video->flags.rom ? "yes" : "no",
	       video->flags.post ? "yes" : "no");
	mutex_lock(&video_list_lock);
	list_add_tail(&video->entry, &video_bus_head);
	mutex_unlock(&video_list_lock);

	acpi_video_bus_रेजिस्टर_backlight(video);
	acpi_video_bus_add_notअगरy_handler(video);

	वापस 0;

err_put_video:
	acpi_video_bus_put_devices(video);
	kमुक्त(video->attached_array);
err_मुक्त_video:
	kमुक्त(video);
	device->driver_data = शून्य;

	वापस error;
पूर्ण

अटल पूर्णांक acpi_video_bus_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_video_bus *video = शून्य;


	अगर (!device || !acpi_driver_data(device))
		वापस -EINVAL;

	video = acpi_driver_data(device);

	acpi_video_bus_हटाओ_notअगरy_handler(video);
	acpi_video_bus_unरेजिस्टर_backlight(video);
	acpi_video_bus_put_devices(video);

	mutex_lock(&video_list_lock);
	list_del(&video->entry);
	mutex_unlock(&video_list_lock);

	kमुक्त(video->attached_array);
	kमुक्त(video);

	वापस 0;
पूर्ण

अटल पूर्णांक __init is_i740(काष्ठा pci_dev *dev)
अणु
	अगर (dev->device == 0x00D1)
		वापस 1;
	अगर (dev->device == 0x7000)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक __init पूर्णांकel_opregion_present(व्योम)
अणु
	पूर्णांक opregion = 0;
	काष्ठा pci_dev *dev = शून्य;
	u32 address;

	क्रम_each_pci_dev(dev) अणु
		अगर ((dev->class >> 8) != PCI_CLASS_DISPLAY_VGA)
			जारी;
		अगर (dev->venकरोr != PCI_VENDOR_ID_INTEL)
			जारी;
		/* We करोn't want to poke around undefined i740 रेजिस्टरs */
		अगर (is_i740(dev))
			जारी;
		pci_पढ़ो_config_dword(dev, 0xfc, &address);
		अगर (!address)
			जारी;
		opregion = 1;
	पूर्ण
	वापस opregion;
पूर्ण

/* Check अगर the chassis-type indicates there is no builtin LCD panel */
अटल bool dmi_is_desktop(व्योम)
अणु
	स्थिर अक्षर *chassis_type;
	अचिन्हित दीर्घ type;

	chassis_type = dmi_get_प्रणाली_info(DMI_CHASSIS_TYPE);
	अगर (!chassis_type)
		वापस false;

	अगर (kम_से_अदीर्घ(chassis_type, 10, &type) != 0)
		वापस false;

	चयन (type) अणु
	हाल 0x03: /* Desktop */
	हाल 0x04: /* Low Profile Desktop */
	हाल 0x05: /* Pizza Box */
	हाल 0x06: /* Mini Tower */
	हाल 0x07: /* Tower */
	हाल 0x10: /* Lunch Box */
	हाल 0x11: /* Main Server Chassis */
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * We're seeing a lot of bogus backlight पूर्णांकerfaces on newer machines
 * without a LCD such as desktops, servers and HDMI sticks. Checking the
 * lcd flag fixes this, enable this by शेष on any machines which are:
 * 1.  Win8 पढ़ोy (where we also prefer the native backlight driver, so
 *     normally the acpi_video code should not रेजिस्टर there anyways); *and*
 * 2.1 Report a desktop/server DMI chassis-type, or
 * 2.2 Are an ACPI-reduced-hardware platक्रमm (and thus won't use the EC क्रम
       backlight control)
 */
अटल bool should_check_lcd_flag(व्योम)
अणु
	अगर (!acpi_osi_is_win8())
		वापस false;

	अगर (dmi_is_desktop())
		वापस true;

	अगर (acpi_reduced_hardware())
		वापस true;

	वापस false;
पूर्ण

पूर्णांक acpi_video_रेजिस्टर(व्योम)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&रेजिस्टर_count_mutex);
	अगर (रेजिस्टर_count) अणु
		/*
		 * अगर the function of acpi_video_रेजिस्टर is alपढ़ोy called,
		 * करोn't रेजिस्टर the acpi_video_bus again and वापस no error.
		 */
		जाओ leave;
	पूर्ण

	अगर (only_lcd == -1)
		only_lcd = should_check_lcd_flag();

	dmi_check_प्रणाली(video_dmi_table);

	ret = acpi_bus_रेजिस्टर_driver(&acpi_video_bus);
	अगर (ret)
		जाओ leave;

	/*
	 * When the acpi_video_bus is loaded successfully, increase
	 * the counter reference.
	 */
	रेजिस्टर_count = 1;

leave:
	mutex_unlock(&रेजिस्टर_count_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(acpi_video_रेजिस्टर);

व्योम acpi_video_unरेजिस्टर(व्योम)
अणु
	mutex_lock(&रेजिस्टर_count_mutex);
	अगर (रेजिस्टर_count) अणु
		acpi_bus_unरेजिस्टर_driver(&acpi_video_bus);
		रेजिस्टर_count = 0;
	पूर्ण
	mutex_unlock(&रेजिस्टर_count_mutex);
पूर्ण
EXPORT_SYMBOL(acpi_video_unरेजिस्टर);

व्योम acpi_video_unरेजिस्टर_backlight(व्योम)
अणु
	काष्ठा acpi_video_bus *video;

	mutex_lock(&रेजिस्टर_count_mutex);
	अगर (रेजिस्टर_count) अणु
		mutex_lock(&video_list_lock);
		list_क्रम_each_entry(video, &video_bus_head, entry)
			acpi_video_bus_unरेजिस्टर_backlight(video);
		mutex_unlock(&video_list_lock);
	पूर्ण
	mutex_unlock(&रेजिस्टर_count_mutex);
पूर्ण

bool acpi_video_handles_brightness_key_presses(व्योम)
अणु
	bool have_video_busses;

	mutex_lock(&video_list_lock);
	have_video_busses = !list_empty(&video_bus_head);
	mutex_unlock(&video_list_lock);

	वापस have_video_busses &&
	       (report_key_events & REPORT_BRIGHTNESS_KEY_EVENTS);
पूर्ण
EXPORT_SYMBOL(acpi_video_handles_brightness_key_presses);

/*
 * This is kind of nasty. Hardware using Intel chipsets may require
 * the video opregion code to be run first in order to initialise
 * state beक्रमe any ACPI video calls are made. To handle this we defer
 * registration of the video class until the opregion code has run.
 */

अटल पूर्णांक __init acpi_video_init(व्योम)
अणु
	/*
	 * Let the module load even अगर ACPI is disabled (e.g. due to
	 * a broken BIOS) so that i915.ko can still be loaded on such
	 * old प्रणालीs without an AcpiOpRegion.
	 *
	 * acpi_video_रेजिस्टर() will report -ENODEV later as well due
	 * to acpi_disabled when i915.ko tries to रेजिस्टर itself afterwards.
	 */
	अगर (acpi_disabled)
		वापस 0;

	अगर (पूर्णांकel_opregion_present())
		वापस 0;

	वापस acpi_video_रेजिस्टर();
पूर्ण

अटल व्योम __निकास acpi_video_निकास(व्योम)
अणु
	acpi_video_detect_निकास();
	acpi_video_unरेजिस्टर();

	वापस;
पूर्ण

module_init(acpi_video_init);
module_निकास(acpi_video_निकास);
