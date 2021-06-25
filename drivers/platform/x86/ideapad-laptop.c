<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  ideapad-laptop.c - Lenovo IdeaPad ACPI Extras
 *
 *  Copyright तऊ 2010 Intel Corporation
 *  Copyright तऊ 2010 David Woodhouse <dwmw2@infradead.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/backlight.h>
#समावेश <linux/bitops.h>
#समावेश <linux/bug.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/dmi.h>
#समावेश <linux/fb.h>
#समावेश <linux/i8042.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sparse-keymap.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_profile.h>
#समावेश <linux/rfसमाप्त.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/types.h>

#समावेश <acpi/video.h>

#समावेश <dt-bindings/leds/common.h>

#घोषणा IDEAPAD_RFKILL_DEV_NUM	3

#अगर IS_ENABLED(CONFIG_ACPI_WMI)
अटल स्थिर अक्षर *स्थिर ideapad_wmi_fnesc_events[] = अणु
	"26CAB2E5-5CF1-46AE-AAC3-4A12B6BA50E6", /* Yoga 3 */
	"56322276-8493-4CE8-A783-98C991274F5E", /* Yoga 700 */
पूर्ण;
#पूर्ण_अगर

क्रमागत अणु
	CFG_CAP_BT_BIT       = 16,
	CFG_CAP_3G_BIT       = 17,
	CFG_CAP_WIFI_BIT     = 18,
	CFG_CAP_CAM_BIT      = 19,
	CFG_CAP_TOUCHPAD_BIT = 30,
पूर्ण;

क्रमागत अणु
	GBMD_CONSERVATION_STATE_BIT = 5,
पूर्ण;

क्रमागत अणु
	SBMC_CONSERVATION_ON  = 3,
	SBMC_CONSERVATION_OFF = 5,
पूर्ण;

क्रमागत अणु
	HALS_KBD_BL_SUPPORT_BIT       = 4,
	HALS_KBD_BL_STATE_BIT         = 5,
	HALS_USB_CHARGING_SUPPORT_BIT = 6,
	HALS_USB_CHARGING_STATE_BIT   = 7,
	HALS_FNLOCK_SUPPORT_BIT       = 9,
	HALS_FNLOCK_STATE_BIT         = 10,
	HALS_HOTKEYS_PRIMARY_BIT      = 11,
पूर्ण;

क्रमागत अणु
	SALS_KBD_BL_ON        = 0x8,
	SALS_KBD_BL_OFF       = 0x9,
	SALS_USB_CHARGING_ON  = 0xa,
	SALS_USB_CHARGING_OFF = 0xb,
	SALS_FNLOCK_ON        = 0xe,
	SALS_FNLOCK_OFF       = 0xf,
पूर्ण;

क्रमागत अणु
	VPCCMD_R_VPC1 = 0x10,
	VPCCMD_R_BL_MAX,
	VPCCMD_R_BL,
	VPCCMD_W_BL,
	VPCCMD_R_WIFI,
	VPCCMD_W_WIFI,
	VPCCMD_R_BT,
	VPCCMD_W_BT,
	VPCCMD_R_BL_POWER,
	VPCCMD_R_NOVO,
	VPCCMD_R_VPC2,
	VPCCMD_R_TOUCHPAD,
	VPCCMD_W_TOUCHPAD,
	VPCCMD_R_CAMERA,
	VPCCMD_W_CAMERA,
	VPCCMD_R_3G,
	VPCCMD_W_3G,
	VPCCMD_R_ODD, /* 0x21 */
	VPCCMD_W_FAN,
	VPCCMD_R_RF,
	VPCCMD_W_RF,
	VPCCMD_R_FAN = 0x2B,
	VPCCMD_R_SPECIAL_BUTTONS = 0x31,
	VPCCMD_W_BL_POWER = 0x33,
पूर्ण;

काष्ठा ideapad_dytc_priv अणु
	क्रमागत platक्रमm_profile_option current_profile;
	काष्ठा platक्रमm_profile_handler pprof;
	काष्ठा mutex mutex; /* protects the DYTC पूर्णांकerface */
	काष्ठा ideapad_निजी *priv;
पूर्ण;

काष्ठा ideapad_rfk_priv अणु
	पूर्णांक dev;
	काष्ठा ideapad_निजी *priv;
पूर्ण;

काष्ठा ideapad_निजी अणु
	काष्ठा acpi_device *adev;
	काष्ठा rfसमाप्त *rfk[IDEAPAD_RFKILL_DEV_NUM];
	काष्ठा ideapad_rfk_priv rfk_priv[IDEAPAD_RFKILL_DEV_NUM];
	काष्ठा platक्रमm_device *platक्रमm_device;
	काष्ठा input_dev *inputdev;
	काष्ठा backlight_device *blightdev;
	काष्ठा ideapad_dytc_priv *dytc;
	काष्ठा dentry *debug;
	अचिन्हित दीर्घ cfg;
	स्थिर अक्षर *fnesc_guid;
	काष्ठा अणु
		bool conservation_mode    : 1;
		bool dytc                 : 1;
		bool fan_mode             : 1;
		bool fn_lock              : 1;
		bool hw_rfसमाप्त_चयन     : 1;
		bool kbd_bl               : 1;
		bool touchpad_ctrl_via_ec : 1;
		bool usb_अक्षरging         : 1;
	पूर्ण features;
	काष्ठा अणु
		bool initialized;
		काष्ठा led_classdev led;
		अचिन्हित पूर्णांक last_brightness;
	पूर्ण kbd_bl;
पूर्ण;

अटल bool no_bt_rfसमाप्त;
module_param(no_bt_rfसमाप्त, bool, 0444);
MODULE_PARM_DESC(no_bt_rfसमाप्त, "No rfkill for bluetooth.");

/*
 * ACPI Helpers
 */
#घोषणा IDEAPAD_EC_TIMEOUT 200 /* in ms */

अटल पूर्णांक eval_पूर्णांक(acpi_handle handle, स्थिर अक्षर *name, अचिन्हित दीर्घ *res)
अणु
	अचिन्हित दीर्घ दीर्घ result;
	acpi_status status;

	status = acpi_evaluate_पूर्णांकeger(handle, (अक्षर *)name, शून्य, &result);
	अगर (ACPI_FAILURE(status))
		वापस -EIO;

	*res = result;

	वापस 0;
पूर्ण

अटल पूर्णांक exec_simple_method(acpi_handle handle, स्थिर अक्षर *name, अचिन्हित दीर्घ arg)
अणु
	acpi_status status = acpi_execute_simple_method(handle, (अक्षर *)name, arg);

	वापस ACPI_FAILURE(status) ? -EIO : 0;
पूर्ण

अटल पूर्णांक eval_gbmd(acpi_handle handle, अचिन्हित दीर्घ *res)
अणु
	वापस eval_पूर्णांक(handle, "GBMD", res);
पूर्ण

अटल पूर्णांक exec_sbmc(acpi_handle handle, अचिन्हित दीर्घ arg)
अणु
	वापस exec_simple_method(handle, "SBMC", arg);
पूर्ण

अटल पूर्णांक eval_hals(acpi_handle handle, अचिन्हित दीर्घ *res)
अणु
	वापस eval_पूर्णांक(handle, "HALS", res);
पूर्ण

अटल पूर्णांक exec_sals(acpi_handle handle, अचिन्हित दीर्घ arg)
अणु
	वापस exec_simple_method(handle, "SALS", arg);
पूर्ण

अटल पूर्णांक eval_पूर्णांक_with_arg(acpi_handle handle, स्थिर अक्षर *name, अचिन्हित दीर्घ arg, अचिन्हित दीर्घ *res)
अणु
	काष्ठा acpi_object_list params;
	अचिन्हित दीर्घ दीर्घ result;
	जोड़ acpi_object in_obj;
	acpi_status status;

	params.count = 1;
	params.poपूर्णांकer = &in_obj;
	in_obj.type = ACPI_TYPE_INTEGER;
	in_obj.पूर्णांकeger.value = arg;

	status = acpi_evaluate_पूर्णांकeger(handle, (अक्षर *)name, &params, &result);
	अगर (ACPI_FAILURE(status))
		वापस -EIO;

	अगर (res)
		*res = result;

	वापस 0;
पूर्ण

अटल पूर्णांक eval_dytc(acpi_handle handle, अचिन्हित दीर्घ cmd, अचिन्हित दीर्घ *res)
अणु
	वापस eval_पूर्णांक_with_arg(handle, "DYTC", cmd, res);
पूर्ण

अटल पूर्णांक eval_vpcr(acpi_handle handle, अचिन्हित दीर्घ cmd, अचिन्हित दीर्घ *res)
अणु
	वापस eval_पूर्णांक_with_arg(handle, "VPCR", cmd, res);
पूर्ण

अटल पूर्णांक eval_vpcw(acpi_handle handle, अचिन्हित दीर्घ cmd, अचिन्हित दीर्घ data)
अणु
	काष्ठा acpi_object_list params;
	जोड़ acpi_object in_obj[2];
	acpi_status status;

	params.count = 2;
	params.poपूर्णांकer = in_obj;
	in_obj[0].type = ACPI_TYPE_INTEGER;
	in_obj[0].पूर्णांकeger.value = cmd;
	in_obj[1].type = ACPI_TYPE_INTEGER;
	in_obj[1].पूर्णांकeger.value = data;

	status = acpi_evaluate_object(handle, "VPCW", &params, शून्य);
	अगर (ACPI_FAILURE(status))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_ec_data(acpi_handle handle, अचिन्हित दीर्घ cmd, अचिन्हित दीर्घ *data)
अणु
	अचिन्हित दीर्घ end_jअगरfies, val;
	पूर्णांक err;

	err = eval_vpcw(handle, 1, cmd);
	अगर (err)
		वापस err;

	end_jअगरfies = jअगरfies + msecs_to_jअगरfies(IDEAPAD_EC_TIMEOUT) + 1;

	जबतक (समय_beक्रमe(jअगरfies, end_jअगरfies)) अणु
		schedule();

		err = eval_vpcr(handle, 1, &val);
		अगर (err)
			वापस err;

		अगर (val == 0)
			वापस eval_vpcr(handle, 0, data);
	पूर्ण

	acpi_handle_err(handle, "timeout in %s\n", __func__);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक ग_लिखो_ec_cmd(acpi_handle handle, अचिन्हित दीर्घ cmd, अचिन्हित दीर्घ data)
अणु
	अचिन्हित दीर्घ end_jअगरfies, val;
	पूर्णांक err;

	err = eval_vpcw(handle, 0, data);
	अगर (err)
		वापस err;

	err = eval_vpcw(handle, 1, cmd);
	अगर (err)
		वापस err;

	end_jअगरfies = jअगरfies + msecs_to_jअगरfies(IDEAPAD_EC_TIMEOUT) + 1;

	जबतक (समय_beक्रमe(jअगरfies, end_jअगरfies)) अणु
		schedule();

		err = eval_vpcr(handle, 1, &val);
		अगर (err)
			वापस err;

		अगर (val == 0)
			वापस 0;
	पूर्ण

	acpi_handle_err(handle, "timeout in %s\n", __func__);

	वापस -ETIMEDOUT;
पूर्ण

/*
 * debugfs
 */
अटल पूर्णांक debugfs_status_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा ideapad_निजी *priv = s->निजी;
	अचिन्हित दीर्घ value;

	अगर (!पढ़ो_ec_data(priv->adev->handle, VPCCMD_R_BL_MAX, &value))
		seq_म_लिखो(s, "Backlight max:  %lu\n", value);
	अगर (!पढ़ो_ec_data(priv->adev->handle, VPCCMD_R_BL, &value))
		seq_म_लिखो(s, "Backlight now:  %lu\n", value);
	अगर (!पढ़ो_ec_data(priv->adev->handle, VPCCMD_R_BL_POWER, &value))
		seq_म_लिखो(s, "BL power value: %s (%lu)\n", value ? "on" : "off", value);

	seq_माला_दो(s, "=====================\n");

	अगर (!पढ़ो_ec_data(priv->adev->handle, VPCCMD_R_RF, &value))
		seq_म_लिखो(s, "Radio status: %s (%lu)\n", value ? "on" : "off", value);
	अगर (!पढ़ो_ec_data(priv->adev->handle, VPCCMD_R_WIFI, &value))
		seq_म_लिखो(s, "Wifi status:  %s (%lu)\n", value ? "on" : "off", value);
	अगर (!पढ़ो_ec_data(priv->adev->handle, VPCCMD_R_BT, &value))
		seq_म_लिखो(s, "BT status:    %s (%lu)\n", value ? "on" : "off", value);
	अगर (!पढ़ो_ec_data(priv->adev->handle, VPCCMD_R_3G, &value))
		seq_म_लिखो(s, "3G status:    %s (%lu)\n", value ? "on" : "off", value);

	seq_माला_दो(s, "=====================\n");

	अगर (!पढ़ो_ec_data(priv->adev->handle, VPCCMD_R_TOUCHPAD, &value))
		seq_म_लिखो(s, "Touchpad status: %s (%lu)\n", value ? "on" : "off", value);
	अगर (!पढ़ो_ec_data(priv->adev->handle, VPCCMD_R_CAMERA, &value))
		seq_म_लिखो(s, "Camera status:   %s (%lu)\n", value ? "on" : "off", value);

	seq_माला_दो(s, "=====================\n");

	अगर (!eval_gbmd(priv->adev->handle, &value))
		seq_म_लिखो(s, "GBMD: %#010lx\n", value);
	अगर (!eval_hals(priv->adev->handle, &value))
		seq_म_लिखो(s, "HALS: %#010lx\n", value);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(debugfs_status);

अटल पूर्णांक debugfs_cfg_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा ideapad_निजी *priv = s->निजी;

	seq_म_लिखो(s, "_CFG: %#010lx\n\n", priv->cfg);

	seq_माला_दो(s, "Capabilities:");
	अगर (test_bit(CFG_CAP_BT_BIT, &priv->cfg))
		seq_माला_दो(s, " bluetooth");
	अगर (test_bit(CFG_CAP_3G_BIT, &priv->cfg))
		seq_माला_दो(s, " 3G");
	अगर (test_bit(CFG_CAP_WIFI_BIT, &priv->cfg))
		seq_माला_दो(s, " wifi");
	अगर (test_bit(CFG_CAP_CAM_BIT, &priv->cfg))
		seq_माला_दो(s, " camera");
	अगर (test_bit(CFG_CAP_TOUCHPAD_BIT, &priv->cfg))
		seq_माला_दो(s, " touchpad");
	seq_माला_दो(s, "\n");

	seq_माला_दो(s, "Graphics: ");
	चयन (priv->cfg & 0x700) अणु
	हाल 0x100:
		seq_माला_दो(s, "Intel");
		अवरोध;
	हाल 0x200:
		seq_माला_दो(s, "ATI");
		अवरोध;
	हाल 0x300:
		seq_माला_दो(s, "Nvidia");
		अवरोध;
	हाल 0x400:
		seq_माला_दो(s, "Intel and ATI");
		अवरोध;
	हाल 0x500:
		seq_माला_दो(s, "Intel and Nvidia");
		अवरोध;
	पूर्ण
	seq_माला_दो(s, "\n");

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(debugfs_cfg);

अटल व्योम ideapad_debugfs_init(काष्ठा ideapad_निजी *priv)
अणु
	काष्ठा dentry *dir;

	dir = debugfs_create_dir("ideapad", शून्य);
	priv->debug = dir;

	debugfs_create_file("cfg", 0444, dir, priv, &debugfs_cfg_fops);
	debugfs_create_file("status", 0444, dir, priv, &debugfs_status_fops);
पूर्ण

अटल व्योम ideapad_debugfs_निकास(काष्ठा ideapad_निजी *priv)
अणु
	debugfs_हटाओ_recursive(priv->debug);
	priv->debug = शून्य;
पूर्ण

/*
 * sysfs
 */
अटल sमाप_प्रकार camera_घातer_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा ideapad_निजी *priv = dev_get_drvdata(dev);
	अचिन्हित दीर्घ result;
	पूर्णांक err;

	err = पढ़ो_ec_data(priv->adev->handle, VPCCMD_R_CAMERA, &result);
	अगर (err)
		वापस err;

	वापस sysfs_emit(buf, "%d\n", !!result);
पूर्ण

अटल sमाप_प्रकार camera_घातer_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ideapad_निजी *priv = dev_get_drvdata(dev);
	bool state;
	पूर्णांक err;

	err = kstrtobool(buf, &state);
	अगर (err)
		वापस err;

	err = ग_लिखो_ec_cmd(priv->adev->handle, VPCCMD_W_CAMERA, state);
	अगर (err)
		वापस err;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(camera_घातer);

अटल sमाप_प्रकार conservation_mode_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा ideapad_निजी *priv = dev_get_drvdata(dev);
	अचिन्हित दीर्घ result;
	पूर्णांक err;

	err = eval_gbmd(priv->adev->handle, &result);
	अगर (err)
		वापस err;

	वापस sysfs_emit(buf, "%d\n", !!test_bit(GBMD_CONSERVATION_STATE_BIT, &result));
पूर्ण

अटल sमाप_प्रकार conservation_mode_store(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ideapad_निजी *priv = dev_get_drvdata(dev);
	bool state;
	पूर्णांक err;

	err = kstrtobool(buf, &state);
	अगर (err)
		वापस err;

	err = exec_sbmc(priv->adev->handle, state ? SBMC_CONSERVATION_ON : SBMC_CONSERVATION_OFF);
	अगर (err)
		वापस err;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(conservation_mode);

अटल sमाप_प्रकार fan_mode_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा ideapad_निजी *priv = dev_get_drvdata(dev);
	अचिन्हित दीर्घ result;
	पूर्णांक err;

	err = पढ़ो_ec_data(priv->adev->handle, VPCCMD_R_FAN, &result);
	अगर (err)
		वापस err;

	वापस sysfs_emit(buf, "%lu\n", result);
पूर्ण

अटल sमाप_प्रकार fan_mode_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ideapad_निजी *priv = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक state;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 0, &state);
	अगर (err)
		वापस err;

	अगर (state > 4 || state == 3)
		वापस -EINVAL;

	err = ग_लिखो_ec_cmd(priv->adev->handle, VPCCMD_W_FAN, state);
	अगर (err)
		वापस err;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(fan_mode);

अटल sमाप_प्रकार fn_lock_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा ideapad_निजी *priv = dev_get_drvdata(dev);
	अचिन्हित दीर्घ hals;
	पूर्णांक err;

	err = eval_hals(priv->adev->handle, &hals);
	अगर (err)
		वापस err;

	वापस sysfs_emit(buf, "%d\n", !!test_bit(HALS_FNLOCK_STATE_BIT, &hals));
पूर्ण

अटल sमाप_प्रकार fn_lock_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ideapad_निजी *priv = dev_get_drvdata(dev);
	bool state;
	पूर्णांक err;

	err = kstrtobool(buf, &state);
	अगर (err)
		वापस err;

	err = exec_sals(priv->adev->handle, state ? SALS_FNLOCK_ON : SALS_FNLOCK_OFF);
	अगर (err)
		वापस err;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(fn_lock);

अटल sमाप_प्रकार touchpad_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा ideapad_निजी *priv = dev_get_drvdata(dev);
	अचिन्हित दीर्घ result;
	पूर्णांक err;

	err = पढ़ो_ec_data(priv->adev->handle, VPCCMD_R_TOUCHPAD, &result);
	अगर (err)
		वापस err;

	वापस sysfs_emit(buf, "%d\n", !!result);
पूर्ण

अटल sमाप_प्रकार touchpad_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ideapad_निजी *priv = dev_get_drvdata(dev);
	bool state;
	पूर्णांक err;

	err = kstrtobool(buf, &state);
	अगर (err)
		वापस err;

	err = ग_लिखो_ec_cmd(priv->adev->handle, VPCCMD_W_TOUCHPAD, state);
	अगर (err)
		वापस err;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(touchpad);

अटल sमाप_प्रकार usb_अक्षरging_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा ideapad_निजी *priv = dev_get_drvdata(dev);
	अचिन्हित दीर्घ hals;
	पूर्णांक err;

	err = eval_hals(priv->adev->handle, &hals);
	अगर (err)
		वापस err;

	वापस sysfs_emit(buf, "%d\n", !!test_bit(HALS_USB_CHARGING_STATE_BIT, &hals));
पूर्ण

अटल sमाप_प्रकार usb_अक्षरging_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ideapad_निजी *priv = dev_get_drvdata(dev);
	bool state;
	पूर्णांक err;

	err = kstrtobool(buf, &state);
	अगर (err)
		वापस err;

	err = exec_sals(priv->adev->handle, state ? SALS_USB_CHARGING_ON : SALS_USB_CHARGING_OFF);
	अगर (err)
		वापस err;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(usb_अक्षरging);

अटल काष्ठा attribute *ideapad_attributes[] = अणु
	&dev_attr_camera_घातer.attr,
	&dev_attr_conservation_mode.attr,
	&dev_attr_fan_mode.attr,
	&dev_attr_fn_lock.attr,
	&dev_attr_touchpad.attr,
	&dev_attr_usb_अक्षरging.attr,
	शून्य
पूर्ण;

अटल umode_t ideapad_is_visible(काष्ठा kobject *kobj,
				  काष्ठा attribute *attr,
				  पूर्णांक idx)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा ideapad_निजी *priv = dev_get_drvdata(dev);
	bool supported = true;

	अगर (attr == &dev_attr_camera_घातer.attr)
		supported = test_bit(CFG_CAP_CAM_BIT, &priv->cfg);
	अन्यथा अगर (attr == &dev_attr_conservation_mode.attr)
		supported = priv->features.conservation_mode;
	अन्यथा अगर (attr == &dev_attr_fan_mode.attr)
		supported = priv->features.fan_mode;
	अन्यथा अगर (attr == &dev_attr_fn_lock.attr)
		supported = priv->features.fn_lock;
	अन्यथा अगर (attr == &dev_attr_touchpad.attr)
		supported = priv->features.touchpad_ctrl_via_ec &&
			    test_bit(CFG_CAP_TOUCHPAD_BIT, &priv->cfg);
	अन्यथा अगर (attr == &dev_attr_usb_अक्षरging.attr)
		supported = priv->features.usb_अक्षरging;

	वापस supported ? attr->mode : 0;
पूर्ण

अटल स्थिर काष्ठा attribute_group ideapad_attribute_group = अणु
	.is_visible = ideapad_is_visible,
	.attrs = ideapad_attributes
पूर्ण;

/*
 * DYTC Platक्रमm profile
 */
#घोषणा DYTC_CMD_QUERY        0 /* To get DYTC status - enable/revision */
#घोषणा DYTC_CMD_SET          1 /* To enable/disable IC function mode */
#घोषणा DYTC_CMD_GET          2 /* To get current IC function and mode */
#घोषणा DYTC_CMD_RESET    0x1ff /* To reset back to शेष */

#घोषणा DYTC_QUERY_ENABLE_BIT 8  /* Bit        8 - 0 = disabled, 1 = enabled */
#घोषणा DYTC_QUERY_SUBREV_BIT 16 /* Bits 16 - 27 - sub revision */
#घोषणा DYTC_QUERY_REV_BIT    28 /* Bits 28 - 31 - revision */

#घोषणा DYTC_GET_FUNCTION_BIT 8  /* Bits  8-11 - function setting */
#घोषणा DYTC_GET_MODE_BIT     12 /* Bits 12-15 - mode setting */

#घोषणा DYTC_SET_FUNCTION_BIT 12 /* Bits 12-15 - function setting */
#घोषणा DYTC_SET_MODE_BIT     16 /* Bits 16-19 - mode setting */
#घोषणा DYTC_SET_VALID_BIT    20 /* Bit     20 - 1 = on, 0 = off */

#घोषणा DYTC_FUNCTION_STD     0  /* Function = 0, standard mode */
#घोषणा DYTC_FUNCTION_CQL     1  /* Function = 1, lap mode */
#घोषणा DYTC_FUNCTION_MMC     11 /* Function = 11, desk mode */

#घोषणा DYTC_MODE_PERFORM     2  /* High घातer mode aka perक्रमmance */
#घोषणा DYTC_MODE_LOW_POWER       3  /* Low घातer mode aka quiet */
#घोषणा DYTC_MODE_BALANCE   0xF  /* Default mode aka balanced */

#घोषणा DYTC_SET_COMMAND(function, mode, on) \
	(DYTC_CMD_SET | (function) << DYTC_SET_FUNCTION_BIT | \
	 (mode) << DYTC_SET_MODE_BIT | \
	 (on) << DYTC_SET_VALID_BIT)

#घोषणा DYTC_DISABLE_CQL DYTC_SET_COMMAND(DYTC_FUNCTION_CQL, DYTC_MODE_BALANCE, 0)

#घोषणा DYTC_ENABLE_CQL DYTC_SET_COMMAND(DYTC_FUNCTION_CQL, DYTC_MODE_BALANCE, 1)

अटल पूर्णांक convert_dytc_to_profile(पूर्णांक dytcmode, क्रमागत platक्रमm_profile_option *profile)
अणु
	चयन (dytcmode) अणु
	हाल DYTC_MODE_LOW_POWER:
		*profile = PLATFORM_PROखाता_LOW_POWER;
		अवरोध;
	हाल DYTC_MODE_BALANCE:
		*profile =  PLATFORM_PROखाता_BALANCED;
		अवरोध;
	हाल DYTC_MODE_PERFORM:
		*profile =  PLATFORM_PROखाता_PERFORMANCE;
		अवरोध;
	शेष: /* Unknown mode */
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक convert_profile_to_dytc(क्रमागत platक्रमm_profile_option profile, पूर्णांक *perभ_शेषe)
अणु
	चयन (profile) अणु
	हाल PLATFORM_PROखाता_LOW_POWER:
		*perभ_शेषe = DYTC_MODE_LOW_POWER;
		अवरोध;
	हाल PLATFORM_PROखाता_BALANCED:
		*perभ_शेषe = DYTC_MODE_BALANCE;
		अवरोध;
	हाल PLATFORM_PROखाता_PERFORMANCE:
		*perभ_शेषe = DYTC_MODE_PERFORM;
		अवरोध;
	शेष: /* Unknown profile */
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * dytc_profile_get: Function to रेजिस्टर with platक्रमm_profile
 * handler. Returns current platक्रमm profile.
 */
अटल पूर्णांक dytc_profile_get(काष्ठा platक्रमm_profile_handler *pprof,
			    क्रमागत platक्रमm_profile_option *profile)
अणु
	काष्ठा ideapad_dytc_priv *dytc = container_of(pprof, काष्ठा ideapad_dytc_priv, pprof);

	*profile = dytc->current_profile;
	वापस 0;
पूर्ण

/*
 * Helper function - check अगर we are in CQL mode and अगर we are
 *  - disable CQL,
 *  - run the command
 *  - enable CQL
 *  If not in CQL mode, just run the command
 */
अटल पूर्णांक dytc_cql_command(काष्ठा ideapad_निजी *priv, अचिन्हित दीर्घ cmd,
			    अचिन्हित दीर्घ *output)
अणु
	पूर्णांक err, cmd_err, cur_funcmode;

	/* Determine अगर we are in CQL mode. This alters the commands we करो */
	err = eval_dytc(priv->adev->handle, DYTC_CMD_GET, output);
	अगर (err)
		वापस err;

	cur_funcmode = (*output >> DYTC_GET_FUNCTION_BIT) & 0xF;
	/* Check अगर we're OK to वापस immediately */
	अगर (cmd == DYTC_CMD_GET && cur_funcmode != DYTC_FUNCTION_CQL)
		वापस 0;

	अगर (cur_funcmode == DYTC_FUNCTION_CQL) अणु
		err = eval_dytc(priv->adev->handle, DYTC_DISABLE_CQL, शून्य);
		अगर (err)
			वापस err;
	पूर्ण

	cmd_err = eval_dytc(priv->adev->handle, cmd, output);
	/* Check वापस condition after we've restored CQL state */

	अगर (cur_funcmode == DYTC_FUNCTION_CQL) अणु
		err = eval_dytc(priv->adev->handle, DYTC_ENABLE_CQL, शून्य);
		अगर (err)
			वापस err;
	पूर्ण

	वापस cmd_err;
पूर्ण

/*
 * dytc_profile_set: Function to रेजिस्टर with platक्रमm_profile
 * handler. Sets current platक्रमm profile.
 */
अटल पूर्णांक dytc_profile_set(काष्ठा platक्रमm_profile_handler *pprof,
			    क्रमागत platक्रमm_profile_option profile)
अणु
	काष्ठा ideapad_dytc_priv *dytc = container_of(pprof, काष्ठा ideapad_dytc_priv, pprof);
	काष्ठा ideapad_निजी *priv = dytc->priv;
	अचिन्हित दीर्घ output;
	पूर्णांक err;

	err = mutex_lock_पूर्णांकerruptible(&dytc->mutex);
	अगर (err)
		वापस err;

	अगर (profile == PLATFORM_PROखाता_BALANCED) अणु
		/* To get back to balanced mode we just issue a reset command */
		err = eval_dytc(priv->adev->handle, DYTC_CMD_RESET, शून्य);
		अगर (err)
			जाओ unlock;
	पूर्ण अन्यथा अणु
		पूर्णांक perभ_शेषe;

		err = convert_profile_to_dytc(profile, &perभ_शेषe);
		अगर (err)
			जाओ unlock;

		/* Determine अगर we are in CQL mode. This alters the commands we करो */
		err = dytc_cql_command(priv, DYTC_SET_COMMAND(DYTC_FUNCTION_MMC, perभ_शेषe, 1),
				       &output);
		अगर (err)
			जाओ unlock;
	पूर्ण

	/* Success - update current profile */
	dytc->current_profile = profile;

unlock:
	mutex_unlock(&dytc->mutex);

	वापस err;
पूर्ण

अटल व्योम dytc_profile_refresh(काष्ठा ideapad_निजी *priv)
अणु
	क्रमागत platक्रमm_profile_option profile;
	अचिन्हित दीर्घ output;
	पूर्णांक err, perभ_शेषe;

	mutex_lock(&priv->dytc->mutex);
	err = dytc_cql_command(priv, DYTC_CMD_GET, &output);
	mutex_unlock(&priv->dytc->mutex);
	अगर (err)
		वापस;

	perभ_शेषe = (output >> DYTC_GET_MODE_BIT) & 0xF;

	अगर (convert_dytc_to_profile(perभ_शेषe, &profile))
		वापस;

	अगर (profile != priv->dytc->current_profile) अणु
		priv->dytc->current_profile = profile;
		platक्रमm_profile_notअगरy();
	पूर्ण
पूर्ण

अटल पूर्णांक ideapad_dytc_profile_init(काष्ठा ideapad_निजी *priv)
अणु
	पूर्णांक err, dytc_version;
	अचिन्हित दीर्घ output;

	अगर (!priv->features.dytc)
		वापस -ENODEV;

	err = eval_dytc(priv->adev->handle, DYTC_CMD_QUERY, &output);
	/* For all other errors we can flag the failure */
	अगर (err)
		वापस err;

	/* Check DYTC is enabled and supports mode setting */
	अगर (!test_bit(DYTC_QUERY_ENABLE_BIT, &output))
		वापस -ENODEV;

	dytc_version = (output >> DYTC_QUERY_REV_BIT) & 0xF;
	अगर (dytc_version < 5)
		वापस -ENODEV;

	priv->dytc = kzalloc(माप(*priv->dytc), GFP_KERNEL);
	अगर (!priv->dytc)
		वापस -ENOMEM;

	mutex_init(&priv->dytc->mutex);

	priv->dytc->priv = priv;
	priv->dytc->pprof.profile_get = dytc_profile_get;
	priv->dytc->pprof.profile_set = dytc_profile_set;

	/* Setup supported modes */
	set_bit(PLATFORM_PROखाता_LOW_POWER, priv->dytc->pprof.choices);
	set_bit(PLATFORM_PROखाता_BALANCED, priv->dytc->pprof.choices);
	set_bit(PLATFORM_PROखाता_PERFORMANCE, priv->dytc->pprof.choices);

	/* Create platक्रमm_profile काष्ठाure and रेजिस्टर */
	err = platक्रमm_profile_रेजिस्टर(&priv->dytc->pprof);
	अगर (err)
		जाओ pp_reg_failed;

	/* Ensure initial values are correct */
	dytc_profile_refresh(priv);

	वापस 0;

pp_reg_failed:
	mutex_destroy(&priv->dytc->mutex);
	kमुक्त(priv->dytc);
	priv->dytc = शून्य;

	वापस err;
पूर्ण

अटल व्योम ideapad_dytc_profile_निकास(काष्ठा ideapad_निजी *priv)
अणु
	अगर (!priv->dytc)
		वापस;

	platक्रमm_profile_हटाओ();
	mutex_destroy(&priv->dytc->mutex);
	kमुक्त(priv->dytc);

	priv->dytc = शून्य;
पूर्ण

/*
 * Rfसमाप्त
 */
काष्ठा ideapad_rfk_data अणु
	अक्षर *name;
	पूर्णांक cfgbit;
	पूर्णांक opcode;
	पूर्णांक type;
पूर्ण;

अटल स्थिर काष्ठा ideapad_rfk_data ideapad_rfk_data[] = अणु
	अणु "ideapad_wlan",      CFG_CAP_WIFI_BIT, VPCCMD_W_WIFI, RFKILL_TYPE_WLAN पूर्ण,
	अणु "ideapad_bluetooth", CFG_CAP_BT_BIT,   VPCCMD_W_BT,   RFKILL_TYPE_BLUETOOTH पूर्ण,
	अणु "ideapad_3g",        CFG_CAP_3G_BIT,   VPCCMD_W_3G,   RFKILL_TYPE_WWAN पूर्ण,
पूर्ण;

अटल पूर्णांक ideapad_rfk_set(व्योम *data, bool blocked)
अणु
	काष्ठा ideapad_rfk_priv *priv = data;
	पूर्णांक opcode = ideapad_rfk_data[priv->dev].opcode;

	वापस ग_लिखो_ec_cmd(priv->priv->adev->handle, opcode, !blocked);
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops ideapad_rfk_ops = अणु
	.set_block = ideapad_rfk_set,
पूर्ण;

अटल व्योम ideapad_sync_rfk_state(काष्ठा ideapad_निजी *priv)
अणु
	अचिन्हित दीर्घ hw_blocked = 0;
	पूर्णांक i;

	अगर (priv->features.hw_rfसमाप्त_चयन) अणु
		अगर (पढ़ो_ec_data(priv->adev->handle, VPCCMD_R_RF, &hw_blocked))
			वापस;
		hw_blocked = !hw_blocked;
	पूर्ण

	क्रम (i = 0; i < IDEAPAD_RFKILL_DEV_NUM; i++)
		अगर (priv->rfk[i])
			rfसमाप्त_set_hw_state(priv->rfk[i], hw_blocked);
पूर्ण

अटल पूर्णांक ideapad_रेजिस्टर_rfसमाप्त(काष्ठा ideapad_निजी *priv, पूर्णांक dev)
अणु
	अचिन्हित दीर्घ rf_enabled;
	पूर्णांक err;

	अगर (no_bt_rfसमाप्त && ideapad_rfk_data[dev].type == RFKILL_TYPE_BLUETOOTH) अणु
		/* Force to enable bluetooth when no_bt_rfसमाप्त=1 */
		ग_लिखो_ec_cmd(priv->adev->handle, ideapad_rfk_data[dev].opcode, 1);
		वापस 0;
	पूर्ण

	priv->rfk_priv[dev].dev = dev;
	priv->rfk_priv[dev].priv = priv;

	priv->rfk[dev] = rfसमाप्त_alloc(ideapad_rfk_data[dev].name,
				      &priv->platक्रमm_device->dev,
				      ideapad_rfk_data[dev].type,
				      &ideapad_rfk_ops,
				      &priv->rfk_priv[dev]);
	अगर (!priv->rfk[dev])
		वापस -ENOMEM;

	err = पढ़ो_ec_data(priv->adev->handle, ideapad_rfk_data[dev].opcode - 1, &rf_enabled);
	अगर (err)
		rf_enabled = 1;

	rfसमाप्त_init_sw_state(priv->rfk[dev], !rf_enabled);

	err = rfसमाप्त_रेजिस्टर(priv->rfk[dev]);
	अगर (err)
		rfसमाप्त_destroy(priv->rfk[dev]);

	वापस err;
पूर्ण

अटल व्योम ideapad_unरेजिस्टर_rfसमाप्त(काष्ठा ideapad_निजी *priv, पूर्णांक dev)
अणु
	अगर (!priv->rfk[dev])
		वापस;

	rfसमाप्त_unरेजिस्टर(priv->rfk[dev]);
	rfसमाप्त_destroy(priv->rfk[dev]);
पूर्ण

/*
 * Platक्रमm device
 */
अटल पूर्णांक ideapad_sysfs_init(काष्ठा ideapad_निजी *priv)
अणु
	वापस device_add_group(&priv->platक्रमm_device->dev,
				&ideapad_attribute_group);
पूर्ण

अटल व्योम ideapad_sysfs_निकास(काष्ठा ideapad_निजी *priv)
अणु
	device_हटाओ_group(&priv->platक्रमm_device->dev,
			    &ideapad_attribute_group);
पूर्ण

/*
 * input device
 */
अटल स्थिर काष्ठा key_entry ideapad_keymap[] = अणु
	अणु KE_KEY,   6, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण,
	अणु KE_KEY,   7, अणु KEY_CAMERA पूर्ण पूर्ण,
	अणु KE_KEY,   8, अणु KEY_MICMUTE पूर्ण पूर्ण,
	अणु KE_KEY,  11, अणु KEY_F16 पूर्ण पूर्ण,
	अणु KE_KEY,  13, अणु KEY_WLAN पूर्ण पूर्ण,
	अणु KE_KEY,  16, अणु KEY_PROG1 पूर्ण पूर्ण,
	अणु KE_KEY,  17, अणु KEY_PROG2 पूर्ण पूर्ण,
	अणु KE_KEY,  64, अणु KEY_PROG3 पूर्ण पूर्ण,
	अणु KE_KEY,  65, अणु KEY_PROG4 पूर्ण पूर्ण,
	अणु KE_KEY,  66, अणु KEY_TOUCHPAD_OFF पूर्ण पूर्ण,
	अणु KE_KEY,  67, अणु KEY_TOUCHPAD_ON पूर्ण पूर्ण,
	अणु KE_KEY, 128, अणु KEY_ESC पूर्ण पूर्ण,
	अणु KE_END पूर्ण,
पूर्ण;

अटल पूर्णांक ideapad_input_init(काष्ठा ideapad_निजी *priv)
अणु
	काष्ठा input_dev *inputdev;
	पूर्णांक err;

	inputdev = input_allocate_device();
	अगर (!inputdev)
		वापस -ENOMEM;

	inputdev->name = "Ideapad extra buttons";
	inputdev->phys = "ideapad/input0";
	inputdev->id.bustype = BUS_HOST;
	inputdev->dev.parent = &priv->platक्रमm_device->dev;

	err = sparse_keymap_setup(inputdev, ideapad_keymap, शून्य);
	अगर (err) अणु
		dev_err(&priv->platक्रमm_device->dev,
			"Could not set up input device keymap: %d\n", err);
		जाओ err_मुक्त_dev;
	पूर्ण

	err = input_रेजिस्टर_device(inputdev);
	अगर (err) अणु
		dev_err(&priv->platक्रमm_device->dev,
			"Could not register input device: %d\n", err);
		जाओ err_मुक्त_dev;
	पूर्ण

	priv->inputdev = inputdev;

	वापस 0;

err_मुक्त_dev:
	input_मुक्त_device(inputdev);

	वापस err;
पूर्ण

अटल व्योम ideapad_input_निकास(काष्ठा ideapad_निजी *priv)
अणु
	input_unरेजिस्टर_device(priv->inputdev);
	priv->inputdev = शून्य;
पूर्ण

अटल व्योम ideapad_input_report(काष्ठा ideapad_निजी *priv,
				 अचिन्हित दीर्घ scancode)
अणु
	sparse_keymap_report_event(priv->inputdev, scancode, 1, true);
पूर्ण

अटल व्योम ideapad_input_novokey(काष्ठा ideapad_निजी *priv)
अणु
	अचिन्हित दीर्घ दीर्घ_pressed;

	अगर (पढ़ो_ec_data(priv->adev->handle, VPCCMD_R_NOVO, &दीर्घ_pressed))
		वापस;

	अगर (दीर्घ_pressed)
		ideapad_input_report(priv, 17);
	अन्यथा
		ideapad_input_report(priv, 16);
पूर्ण

अटल व्योम ideapad_check_special_buttons(काष्ठा ideapad_निजी *priv)
अणु
	अचिन्हित दीर्घ bit, value;

	अगर (पढ़ो_ec_data(priv->adev->handle, VPCCMD_R_SPECIAL_BUTTONS, &value))
		वापस;

	क्रम_each_set_bit (bit, &value, 16) अणु
		चयन (bit) अणु
		हाल 6:	/* Z570 */
		हाल 0:	/* Z580 */
			/* Thermal Management button */
			ideapad_input_report(priv, 65);
			अवरोध;
		हाल 1:
			/* OneKey Theater button */
			ideapad_input_report(priv, 64);
			अवरोध;
		शेष:
			dev_info(&priv->platक्रमm_device->dev,
				 "Unknown special button: %lu\n", bit);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * backlight
 */
अटल पूर्णांक ideapad_backlight_get_brightness(काष्ठा backlight_device *blightdev)
अणु
	काष्ठा ideapad_निजी *priv = bl_get_data(blightdev);
	अचिन्हित दीर्घ now;
	पूर्णांक err;

	err = पढ़ो_ec_data(priv->adev->handle, VPCCMD_R_BL, &now);
	अगर (err)
		वापस err;

	वापस now;
पूर्ण

अटल पूर्णांक ideapad_backlight_update_status(काष्ठा backlight_device *blightdev)
अणु
	काष्ठा ideapad_निजी *priv = bl_get_data(blightdev);
	पूर्णांक err;

	err = ग_लिखो_ec_cmd(priv->adev->handle, VPCCMD_W_BL,
			   blightdev->props.brightness);
	अगर (err)
		वापस err;

	err = ग_लिखो_ec_cmd(priv->adev->handle, VPCCMD_W_BL_POWER,
			   blightdev->props.घातer != FB_BLANK_POWERDOWN);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops ideapad_backlight_ops = अणु
	.get_brightness = ideapad_backlight_get_brightness,
	.update_status = ideapad_backlight_update_status,
पूर्ण;

अटल पूर्णांक ideapad_backlight_init(काष्ठा ideapad_निजी *priv)
अणु
	काष्ठा backlight_device *blightdev;
	काष्ठा backlight_properties props;
	अचिन्हित दीर्घ max, now, घातer;
	पूर्णांक err;

	err = पढ़ो_ec_data(priv->adev->handle, VPCCMD_R_BL_MAX, &max);
	अगर (err)
		वापस err;

	err = पढ़ो_ec_data(priv->adev->handle, VPCCMD_R_BL, &now);
	अगर (err)
		वापस err;

	err = पढ़ो_ec_data(priv->adev->handle, VPCCMD_R_BL_POWER, &घातer);
	अगर (err)
		वापस err;

	स_रखो(&props, 0, माप(props));

	props.max_brightness = max;
	props.type = BACKLIGHT_PLATFORM;

	blightdev = backlight_device_रेजिस्टर("ideapad",
					      &priv->platक्रमm_device->dev,
					      priv,
					      &ideapad_backlight_ops,
					      &props);
	अगर (IS_ERR(blightdev)) अणु
		err = PTR_ERR(blightdev);
		dev_err(&priv->platक्रमm_device->dev,
			"Could not register backlight device: %d\n", err);
		वापस err;
	पूर्ण

	priv->blightdev = blightdev;
	blightdev->props.brightness = now;
	blightdev->props.घातer = घातer ? FB_BLANK_UNBLANK : FB_BLANK_POWERDOWN;

	backlight_update_status(blightdev);

	वापस 0;
पूर्ण

अटल व्योम ideapad_backlight_निकास(काष्ठा ideapad_निजी *priv)
अणु
	backlight_device_unरेजिस्टर(priv->blightdev);
	priv->blightdev = शून्य;
पूर्ण

अटल व्योम ideapad_backlight_notअगरy_घातer(काष्ठा ideapad_निजी *priv)
अणु
	काष्ठा backlight_device *blightdev = priv->blightdev;
	अचिन्हित दीर्घ घातer;

	अगर (!blightdev)
		वापस;

	अगर (पढ़ो_ec_data(priv->adev->handle, VPCCMD_R_BL_POWER, &घातer))
		वापस;

	blightdev->props.घातer = घातer ? FB_BLANK_UNBLANK : FB_BLANK_POWERDOWN;
पूर्ण

अटल व्योम ideapad_backlight_notअगरy_brightness(काष्ठा ideapad_निजी *priv)
अणु
	अचिन्हित दीर्घ now;

	/* अगर we control brightness via acpi video driver */
	अगर (!priv->blightdev)
		पढ़ो_ec_data(priv->adev->handle, VPCCMD_R_BL, &now);
	अन्यथा
		backlight_क्रमce_update(priv->blightdev, BACKLIGHT_UPDATE_HOTKEY);
पूर्ण

/*
 * keyboard backlight
 */
अटल पूर्णांक ideapad_kbd_bl_brightness_get(काष्ठा ideapad_निजी *priv)
अणु
	अचिन्हित दीर्घ hals;
	पूर्णांक err;

	err = eval_hals(priv->adev->handle, &hals);
	अगर (err)
		वापस err;

	वापस !!test_bit(HALS_KBD_BL_STATE_BIT, &hals);
पूर्ण

अटल क्रमागत led_brightness ideapad_kbd_bl_led_cdev_brightness_get(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा ideapad_निजी *priv = container_of(led_cdev, काष्ठा ideapad_निजी, kbd_bl.led);

	वापस ideapad_kbd_bl_brightness_get(priv);
पूर्ण

अटल पूर्णांक ideapad_kbd_bl_brightness_set(काष्ठा ideapad_निजी *priv, अचिन्हित पूर्णांक brightness)
अणु
	पूर्णांक err = exec_sals(priv->adev->handle, brightness ? SALS_KBD_BL_ON : SALS_KBD_BL_OFF);

	अगर (err)
		वापस err;

	priv->kbd_bl.last_brightness = brightness;

	वापस 0;
पूर्ण

अटल पूर्णांक ideapad_kbd_bl_led_cdev_brightness_set(काष्ठा led_classdev *led_cdev,
						  क्रमागत led_brightness brightness)
अणु
	काष्ठा ideapad_निजी *priv = container_of(led_cdev, काष्ठा ideapad_निजी, kbd_bl.led);

	वापस ideapad_kbd_bl_brightness_set(priv, brightness);
पूर्ण

अटल व्योम ideapad_kbd_bl_notअगरy(काष्ठा ideapad_निजी *priv)
अणु
	पूर्णांक brightness;

	अगर (!priv->kbd_bl.initialized)
		वापस;

	brightness = ideapad_kbd_bl_brightness_get(priv);
	अगर (brightness < 0)
		वापस;

	अगर (brightness == priv->kbd_bl.last_brightness)
		वापस;

	priv->kbd_bl.last_brightness = brightness;

	led_classdev_notअगरy_brightness_hw_changed(&priv->kbd_bl.led, brightness);
पूर्ण

अटल पूर्णांक ideapad_kbd_bl_init(काष्ठा ideapad_निजी *priv)
अणु
	पूर्णांक brightness, err;

	अगर (!priv->features.kbd_bl)
		वापस -ENODEV;

	अगर (WARN_ON(priv->kbd_bl.initialized))
		वापस -EEXIST;

	brightness = ideapad_kbd_bl_brightness_get(priv);
	अगर (brightness < 0)
		वापस brightness;

	priv->kbd_bl.last_brightness = brightness;

	priv->kbd_bl.led.name                    = "platform::" LED_FUNCTION_KBD_BACKLIGHT;
	priv->kbd_bl.led.max_brightness          = 1;
	priv->kbd_bl.led.brightness_get          = ideapad_kbd_bl_led_cdev_brightness_get;
	priv->kbd_bl.led.brightness_set_blocking = ideapad_kbd_bl_led_cdev_brightness_set;
	priv->kbd_bl.led.flags                   = LED_BRIGHT_HW_CHANGED;

	err = led_classdev_रेजिस्टर(&priv->platक्रमm_device->dev, &priv->kbd_bl.led);
	अगर (err)
		वापस err;

	priv->kbd_bl.initialized = true;

	वापस 0;
पूर्ण

अटल व्योम ideapad_kbd_bl_निकास(काष्ठा ideapad_निजी *priv)
अणु
	अगर (!priv->kbd_bl.initialized)
		वापस;

	priv->kbd_bl.initialized = false;

	led_classdev_unरेजिस्टर(&priv->kbd_bl.led);
पूर्ण

/*
 * module init/निकास
 */
अटल व्योम ideapad_sync_touchpad_state(काष्ठा ideapad_निजी *priv)
अणु
	अचिन्हित दीर्घ value;

	अगर (!priv->features.touchpad_ctrl_via_ec)
		वापस;

	/* Without पढ़ोing from EC touchpad LED करोesn't चयन state */
	अगर (!पढ़ो_ec_data(priv->adev->handle, VPCCMD_R_TOUCHPAD, &value)) अणु
		अचिन्हित अक्षर param;
		/*
		 * Some IdeaPads करोn't really turn off touchpad - they only
		 * चयन the LED state. We (de)activate KBC AUX port to turn
		 * touchpad off and on. We send KEY_TOUCHPAD_OFF and
		 * KEY_TOUCHPAD_ON to not to get out of sync with LED
		 */
		i8042_command(&param, value ? I8042_CMD_AUX_ENABLE : I8042_CMD_AUX_DISABLE);
		ideapad_input_report(priv, value ? 67 : 66);
		sysfs_notअगरy(&priv->platक्रमm_device->dev.kobj, शून्य, "touchpad");
	पूर्ण
पूर्ण

अटल व्योम ideapad_acpi_notअगरy(acpi_handle handle, u32 event, व्योम *data)
अणु
	काष्ठा ideapad_निजी *priv = data;
	अचिन्हित दीर्घ vpc1, vpc2, bit;

	अगर (पढ़ो_ec_data(handle, VPCCMD_R_VPC1, &vpc1))
		वापस;

	अगर (पढ़ो_ec_data(handle, VPCCMD_R_VPC2, &vpc2))
		वापस;

	vpc1 = (vpc2 << 8) | vpc1;

	क्रम_each_set_bit (bit, &vpc1, 16) अणु
		चयन (bit) अणु
		हाल 13:
		हाल 11:
		हाल 8:
		हाल 7:
		हाल 6:
			ideapad_input_report(priv, bit);
			अवरोध;
		हाल 9:
			ideapad_sync_rfk_state(priv);
			अवरोध;
		हाल 5:
			ideapad_sync_touchpad_state(priv);
			अवरोध;
		हाल 4:
			ideapad_backlight_notअगरy_brightness(priv);
			अवरोध;
		हाल 3:
			ideapad_input_novokey(priv);
			अवरोध;
		हाल 2:
			ideapad_backlight_notअगरy_घातer(priv);
			अवरोध;
		हाल 1:
			/*
			 * Some IdeaPads report event 1 every ~20
			 * seconds जबतक on battery घातer; some
			 * report this when changing to/from tablet
			 * mode; some report this when the keyboard
			 * backlight has changed.
			 */
			ideapad_kbd_bl_notअगरy(priv);
			अवरोध;
		हाल 0:
			ideapad_check_special_buttons(priv);
			अवरोध;
		शेष:
			dev_info(&priv->platक्रमm_device->dev,
				 "Unknown event: %lu\n", bit);
		पूर्ण
	पूर्ण
पूर्ण

#अगर IS_ENABLED(CONFIG_ACPI_WMI)
अटल व्योम ideapad_wmi_notअगरy(u32 value, व्योम *context)
अणु
	काष्ठा ideapad_निजी *priv = context;

	चयन (value) अणु
	हाल 128:
		ideapad_input_report(priv, value);
		अवरोध;
	शेष:
		dev_info(&priv->platक्रमm_device->dev,
			 "Unknown WMI event: %u\n", value);
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*
 * Some ideapads have a hardware rfसमाप्त चयन, but most करो not have one.
 * Reading VPCCMD_R_RF always results in 0 on models without a hardware rfसमाप्त,
 * चयन causing ideapad_laptop to wrongly report all radios as hw-blocked.
 * There used to be a दीर्घ list of DMI ids क्रम models without a hw rfसमाप्त
 * चयन here, but that resulted in playing whack a mole.
 * More importantly wrongly reporting the wअगरi radio as hw-blocked, results in
 * non working wअगरi. Whereas not reporting it hw-blocked, when it actually is
 * hw-blocked results in an empty SSID list, which is a much more benign
 * failure mode.
 * So the शेष now is the much safer option of assuming there is no
 * hardware rfसमाप्त चयन. This शेष also actually matches most hardware,
 * since having a hw rfसमाप्त चयन is quite rare on modern hardware, so this
 * also leads to a much लघुer list.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id hw_rfसमाप्त_list[] = अणु
	अणुपूर्ण
पूर्ण;

अटल व्योम ideapad_check_features(काष्ठा ideapad_निजी *priv)
अणु
	acpi_handle handle = priv->adev->handle;
	अचिन्हित दीर्घ val;

	priv->features.hw_rfसमाप्त_चयन = dmi_check_प्रणाली(hw_rfसमाप्त_list);

	/* Most ideapads with ELAN0634 touchpad करोn't use EC touchpad चयन */
	priv->features.touchpad_ctrl_via_ec = !acpi_dev_present("ELAN0634", शून्य, -1);

	अगर (!पढ़ो_ec_data(handle, VPCCMD_R_FAN, &val))
		priv->features.fan_mode = true;

	अगर (acpi_has_method(handle, "GBMD") && acpi_has_method(handle, "SBMC"))
		priv->features.conservation_mode = true;

	अगर (acpi_has_method(handle, "DYTC"))
		priv->features.dytc = true;

	अगर (acpi_has_method(handle, "HALS") && acpi_has_method(handle, "SALS")) अणु
		अगर (!eval_hals(handle, &val)) अणु
			अगर (test_bit(HALS_FNLOCK_SUPPORT_BIT, &val))
				priv->features.fn_lock = true;

			अगर (test_bit(HALS_KBD_BL_SUPPORT_BIT, &val))
				priv->features.kbd_bl = true;

			अगर (test_bit(HALS_USB_CHARGING_SUPPORT_BIT, &val))
				priv->features.usb_अक्षरging = true;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ideapad_acpi_add(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ideapad_निजी *priv;
	काष्ठा acpi_device *adev;
	acpi_status status;
	अचिन्हित दीर्घ cfg;
	पूर्णांक err, i;

	err = acpi_bus_get_device(ACPI_HANDLE(&pdev->dev), &adev);
	अगर (err)
		वापस -ENODEV;

	अगर (eval_पूर्णांक(adev->handle, "_CFG", &cfg))
		वापस -ENODEV;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	dev_set_drvdata(&pdev->dev, priv);

	priv->cfg = cfg;
	priv->adev = adev;
	priv->platक्रमm_device = pdev;

	ideapad_check_features(priv);

	err = ideapad_sysfs_init(priv);
	अगर (err)
		वापस err;

	ideapad_debugfs_init(priv);

	err = ideapad_input_init(priv);
	अगर (err)
		जाओ input_failed;

	err = ideapad_kbd_bl_init(priv);
	अगर (err) अणु
		अगर (err != -ENODEV)
			dev_warn(&pdev->dev, "Could not set up keyboard backlight LED: %d\n", err);
		अन्यथा
			dev_info(&pdev->dev, "Keyboard backlight control not available\n");
	पूर्ण

	/*
	 * On some models without a hw-चयन (the yoga 2 13 at least)
	 * VPCCMD_W_RF must be explicitly set to 1 क्रम the wअगरi to work.
	 */
	अगर (!priv->features.hw_rfसमाप्त_चयन)
		ग_लिखो_ec_cmd(priv->adev->handle, VPCCMD_W_RF, 1);

	/* The same क्रम Touchpad */
	अगर (!priv->features.touchpad_ctrl_via_ec)
		ग_लिखो_ec_cmd(priv->adev->handle, VPCCMD_W_TOUCHPAD, 1);

	क्रम (i = 0; i < IDEAPAD_RFKILL_DEV_NUM; i++)
		अगर (test_bit(ideapad_rfk_data[i].cfgbit, &priv->cfg))
			ideapad_रेजिस्टर_rfसमाप्त(priv, i);

	ideapad_sync_rfk_state(priv);
	ideapad_sync_touchpad_state(priv);

	err = ideapad_dytc_profile_init(priv);
	अगर (err) अणु
		अगर (err != -ENODEV)
			dev_warn(&pdev->dev, "Could not set up DYTC interface: %d\n", err);
		अन्यथा
			dev_info(&pdev->dev, "DYTC interface is not available\n");
	पूर्ण

	अगर (acpi_video_get_backlight_type() == acpi_backlight_venकरोr) अणु
		err = ideapad_backlight_init(priv);
		अगर (err && err != -ENODEV)
			जाओ backlight_failed;
	पूर्ण

	status = acpi_install_notअगरy_handler(adev->handle,
					     ACPI_DEVICE_NOTIFY,
					     ideapad_acpi_notअगरy, priv);
	अगर (ACPI_FAILURE(status)) अणु
		err = -EIO;
		जाओ notअगरication_failed;
	पूर्ण

#अगर IS_ENABLED(CONFIG_ACPI_WMI)
	क्रम (i = 0; i < ARRAY_SIZE(ideapad_wmi_fnesc_events); i++) अणु
		status = wmi_install_notअगरy_handler(ideapad_wmi_fnesc_events[i],
						    ideapad_wmi_notअगरy, priv);
		अगर (ACPI_SUCCESS(status)) अणु
			priv->fnesc_guid = ideapad_wmi_fnesc_events[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ACPI_FAILURE(status) && status != AE_NOT_EXIST) अणु
		err = -EIO;
		जाओ notअगरication_failed_wmi;
	पूर्ण
#पूर्ण_अगर

	वापस 0;

#अगर IS_ENABLED(CONFIG_ACPI_WMI)
notअगरication_failed_wmi:
	acpi_हटाओ_notअगरy_handler(priv->adev->handle,
				   ACPI_DEVICE_NOTIFY,
				   ideapad_acpi_notअगरy);
#पूर्ण_अगर

notअगरication_failed:
	ideapad_backlight_निकास(priv);

backlight_failed:
	ideapad_dytc_profile_निकास(priv);

	क्रम (i = 0; i < IDEAPAD_RFKILL_DEV_NUM; i++)
		ideapad_unरेजिस्टर_rfसमाप्त(priv, i);

	ideapad_kbd_bl_निकास(priv);
	ideapad_input_निकास(priv);

input_failed:
	ideapad_debugfs_निकास(priv);
	ideapad_sysfs_निकास(priv);

	वापस err;
पूर्ण

अटल पूर्णांक ideapad_acpi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ideapad_निजी *priv = dev_get_drvdata(&pdev->dev);
	पूर्णांक i;

#अगर IS_ENABLED(CONFIG_ACPI_WMI)
	अगर (priv->fnesc_guid)
		wmi_हटाओ_notअगरy_handler(priv->fnesc_guid);
#पूर्ण_अगर

	acpi_हटाओ_notअगरy_handler(priv->adev->handle,
				   ACPI_DEVICE_NOTIFY,
				   ideapad_acpi_notअगरy);

	ideapad_backlight_निकास(priv);
	ideapad_dytc_profile_निकास(priv);

	क्रम (i = 0; i < IDEAPAD_RFKILL_DEV_NUM; i++)
		ideapad_unरेजिस्टर_rfसमाप्त(priv, i);

	ideapad_kbd_bl_निकास(priv);
	ideapad_input_निकास(priv);
	ideapad_debugfs_निकास(priv);
	ideapad_sysfs_निकास(priv);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ideapad_acpi_resume(काष्ठा device *dev)
अणु
	काष्ठा ideapad_निजी *priv = dev_get_drvdata(dev);

	ideapad_sync_rfk_state(priv);
	ideapad_sync_touchpad_state(priv);

	अगर (priv->dytc)
		dytc_profile_refresh(priv);

	वापस 0;
पूर्ण
#पूर्ण_अगर
अटल SIMPLE_DEV_PM_OPS(ideapad_pm, शून्य, ideapad_acpi_resume);

अटल स्थिर काष्ठा acpi_device_id ideapad_device_ids[] = अणु
	अणु"VPC2004", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, ideapad_device_ids);

अटल काष्ठा platक्रमm_driver ideapad_acpi_driver = अणु
	.probe = ideapad_acpi_add,
	.हटाओ = ideapad_acpi_हटाओ,
	.driver = अणु
		.name   = "ideapad_acpi",
		.pm     = &ideapad_pm,
		.acpi_match_table = ACPI_PTR(ideapad_device_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ideapad_acpi_driver);

MODULE_AUTHOR("David Woodhouse <dwmw2@infradead.org>");
MODULE_DESCRIPTION("IdeaPad ACPI Extras");
MODULE_LICENSE("GPL");
