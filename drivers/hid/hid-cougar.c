<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  HID driver क्रम Cougar 500k Gaming Keyboard
 *
 *  Copyright (c) 2018 Daniel M. Lambea <dmlambea@gmail.com>
 */

#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>

#समावेश "hid-ids.h"

MODULE_AUTHOR("Daniel M. Lambea <dmlambea@gmail.com>");
MODULE_DESCRIPTION("Cougar 500k Gaming Keyboard");
MODULE_LICENSE("GPL");
MODULE_INFO(key_mappings, "G1-G6 are mapped to F13-F18");

अटल bool g6_is_space = true;
MODULE_PARM_DESC(g6_is_space,
	"If true, G6 programmable key sends SPACE instead of F18 (default=true)");

#घोषणा COUGAR_VENDOR_USAGE	0xff00ff00

#घोषणा COUGAR_FIELD_CODE	1
#घोषणा COUGAR_FIELD_ACTION	2

#घोषणा COUGAR_KEY_G1		0x83
#घोषणा COUGAR_KEY_G2		0x84
#घोषणा COUGAR_KEY_G3		0x85
#घोषणा COUGAR_KEY_G4		0x86
#घोषणा COUGAR_KEY_G5		0x87
#घोषणा COUGAR_KEY_G6		0x78
#घोषणा COUGAR_KEY_FN		0x0d
#घोषणा COUGAR_KEY_MR		0x6f
#घोषणा COUGAR_KEY_M1		0x80
#घोषणा COUGAR_KEY_M2		0x81
#घोषणा COUGAR_KEY_M3		0x82
#घोषणा COUGAR_KEY_LEDS		0x67
#घोषणा COUGAR_KEY_LOCK		0x6e


/* Default key mappings. The special key COUGAR_KEY_G6 is defined first
 * because it is more frequent to use the spacebar rather than any other
 * special keys. Depending on the value of the parameter 'g6_is_space',
 * the mapping will be updated in the probe function.
 */
अटल अचिन्हित अक्षर cougar_mapping[][2] = अणु
	अणु COUGAR_KEY_G6,   KEY_SPACE पूर्ण,
	अणु COUGAR_KEY_G1,   KEY_F13 पूर्ण,
	अणु COUGAR_KEY_G2,   KEY_F14 पूर्ण,
	अणु COUGAR_KEY_G3,   KEY_F15 पूर्ण,
	अणु COUGAR_KEY_G4,   KEY_F16 पूर्ण,
	अणु COUGAR_KEY_G5,   KEY_F17 पूर्ण,
	अणु COUGAR_KEY_LOCK, KEY_SCREENLOCK पूर्ण,
/* The following keys are handled by the hardware itself, so no special
 * treaपंचांगent is required:
	अणु COUGAR_KEY_FN, KEY_RESERVED पूर्ण,
	अणु COUGAR_KEY_MR, KEY_RESERVED पूर्ण,
	अणु COUGAR_KEY_M1, KEY_RESERVED पूर्ण,
	अणु COUGAR_KEY_M2, KEY_RESERVED पूर्ण,
	अणु COUGAR_KEY_M3, KEY_RESERVED पूर्ण,
	अणु COUGAR_KEY_LEDS, KEY_RESERVED पूर्ण,
*/
	अणु 0, 0 पूर्ण,
पूर्ण;

काष्ठा cougar_shared अणु
	काष्ठा list_head list;
	काष्ठा kref kref;
	bool enabled;
	काष्ठा hid_device *dev;
	काष्ठा input_dev *input;
पूर्ण;

काष्ठा cougar अणु
	bool special_पूर्णांकf;
	काष्ठा cougar_shared *shared;
पूर्ण;

अटल LIST_HEAD(cougar_udev_list);
अटल DEFINE_MUTEX(cougar_udev_list_lock);

/**
 * cougar_fix_g6_mapping - configure the mapping क्रम key G6/Spacebar
 */
अटल व्योम cougar_fix_g6_mapping(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; cougar_mapping[i][0]; i++) अणु
		अगर (cougar_mapping[i][0] == COUGAR_KEY_G6) अणु
			cougar_mapping[i][1] =
				g6_is_space ? KEY_SPACE : KEY_F18;
			pr_info("cougar: G6 mapped to %s\n",
				g6_is_space ? "space" : "F18");
			वापस;
		पूर्ण
	पूर्ण
	pr_warn("cougar: no mappings defined for G6/spacebar");
पूर्ण

/*
 * Constant-मित्रly rdesc fixup क्रम mouse पूर्णांकerface
 */
अटल __u8 *cougar_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
				 अचिन्हित पूर्णांक *rsize)
अणु
	अगर (rdesc[2] == 0x09 && rdesc[3] == 0x02 &&
	    (rdesc[115] | rdesc[116] << 8) >= HID_MAX_USAGES) अणु
		hid_info(hdev,
			"usage count exceeds max: fixing up report descriptor\n");
		rdesc[115] = ((HID_MAX_USAGES-1) & 0xff);
		rdesc[116] = ((HID_MAX_USAGES-1) >> 8);
	पूर्ण
	वापस rdesc;
पूर्ण

अटल काष्ठा cougar_shared *cougar_get_shared_data(काष्ठा hid_device *hdev)
अणु
	काष्ठा cougar_shared *shared;

	/* Try to find an alपढ़ोy-probed पूर्णांकerface from the same device */
	list_क्रम_each_entry(shared, &cougar_udev_list, list) अणु
		अगर (hid_compare_device_paths(hdev, shared->dev, '/')) अणु
			kref_get(&shared->kref);
			वापस shared;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम cougar_release_shared_data(काष्ठा kref *kref)
अणु
	काष्ठा cougar_shared *shared = container_of(kref,
						    काष्ठा cougar_shared, kref);

	mutex_lock(&cougar_udev_list_lock);
	list_del(&shared->list);
	mutex_unlock(&cougar_udev_list_lock);

	kमुक्त(shared);
पूर्ण

अटल व्योम cougar_हटाओ_shared_data(व्योम *resource)
अणु
	काष्ठा cougar *cougar = resource;

	अगर (cougar->shared) अणु
		kref_put(&cougar->shared->kref, cougar_release_shared_data);
		cougar->shared = शून्य;
	पूर्ण
पूर्ण

/*
 * Bind the device group's shared data to this cougar काष्ठा.
 * If no shared data exists क्रम this group, create and initialize it.
 */
अटल पूर्णांक cougar_bind_shared_data(काष्ठा hid_device *hdev,
				   काष्ठा cougar *cougar)
अणु
	काष्ठा cougar_shared *shared;
	पूर्णांक error = 0;

	mutex_lock(&cougar_udev_list_lock);

	shared = cougar_get_shared_data(hdev);
	अगर (!shared) अणु
		shared = kzalloc(माप(*shared), GFP_KERNEL);
		अगर (!shared) अणु
			error = -ENOMEM;
			जाओ out;
		पूर्ण

		kref_init(&shared->kref);
		shared->dev = hdev;
		list_add_tail(&shared->list, &cougar_udev_list);
	पूर्ण

	cougar->shared = shared;

	error = devm_add_action(&hdev->dev, cougar_हटाओ_shared_data, cougar);
	अगर (error) अणु
		mutex_unlock(&cougar_udev_list_lock);
		cougar_हटाओ_shared_data(cougar);
		वापस error;
	पूर्ण

out:
	mutex_unlock(&cougar_udev_list_lock);
	वापस error;
पूर्ण

अटल पूर्णांक cougar_probe(काष्ठा hid_device *hdev,
			स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा cougar *cougar;
	काष्ठा hid_input *next, *hidinput = शून्य;
	अचिन्हित पूर्णांक connect_mask;
	पूर्णांक error;

	cougar = devm_kzalloc(&hdev->dev, माप(*cougar), GFP_KERNEL);
	अगर (!cougar)
		वापस -ENOMEM;
	hid_set_drvdata(hdev, cougar);

	error = hid_parse(hdev);
	अगर (error) अणु
		hid_err(hdev, "parse failed\n");
		वापस error;
	पूर्ण

	अगर (hdev->collection->usage == COUGAR_VENDOR_USAGE) अणु
		cougar->special_पूर्णांकf = true;
		connect_mask = HID_CONNECT_HIDRAW;
	पूर्ण अन्यथा
		connect_mask = HID_CONNECT_DEFAULT;

	error = hid_hw_start(hdev, connect_mask);
	अगर (error) अणु
		hid_err(hdev, "hw start failed\n");
		वापस error;
	पूर्ण

	error = cougar_bind_shared_data(hdev, cougar);
	अगर (error)
		जाओ fail_stop_and_cleanup;

	/* The custom venकरोr पूर्णांकerface will use the hid_input रेजिस्टरed
	 * क्रम the keyboard पूर्णांकerface, in order to send translated key codes
	 * to it.
	 */
	अगर (hdev->collection->usage == HID_GD_KEYBOARD) अणु
		list_क्रम_each_entry_safe(hidinput, next, &hdev->inमाला_दो, list) अणु
			अगर (hidinput->रेजिस्टरed && hidinput->input != शून्य) अणु
				cougar->shared->input = hidinput->input;
				cougar->shared->enabled = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (hdev->collection->usage == COUGAR_VENDOR_USAGE) अणु
		/* Preinit the mapping table */
		cougar_fix_g6_mapping();
		error = hid_hw_खोलो(hdev);
		अगर (error)
			जाओ fail_stop_and_cleanup;
	पूर्ण
	वापस 0;

fail_stop_and_cleanup:
	hid_hw_stop(hdev);
	वापस error;
पूर्ण

/*
 * Convert events from venकरोr पूर्णांकf to input key events
 */
अटल पूर्णांक cougar_raw_event(काष्ठा hid_device *hdev, काष्ठा hid_report *report,
			    u8 *data, पूर्णांक size)
अणु
	काष्ठा cougar *cougar;
	काष्ठा cougar_shared *shared;
	अचिन्हित अक्षर code, action;
	पूर्णांक i;

	cougar = hid_get_drvdata(hdev);
	shared = cougar->shared;
	अगर (!cougar->special_पूर्णांकf || !shared)
		वापस 0;

	अगर (!shared->enabled || !shared->input)
		वापस -EPERM;

	code = data[COUGAR_FIELD_CODE];
	action = data[COUGAR_FIELD_ACTION];
	क्रम (i = 0; cougar_mapping[i][0]; i++) अणु
		अगर (code == cougar_mapping[i][0]) अणु
			input_event(shared->input, EV_KEY,
				    cougar_mapping[i][1], action);
			input_sync(shared->input);
			वापस -EPERM;
		पूर्ण
	पूर्ण
	/* Aव्योम warnings on the same unmapped key twice */
	अगर (action != 0)
		hid_warn(hdev, "unmapped special key code %0x: ignoring\n", code);
	वापस -EPERM;
पूर्ण

अटल व्योम cougar_हटाओ(काष्ठा hid_device *hdev)
अणु
	काष्ठा cougar *cougar = hid_get_drvdata(hdev);

	अगर (cougar) अणु
		/* Stop the venकरोr पूर्णांकf to process more events */
		अगर (cougar->shared)
			cougar->shared->enabled = false;
		अगर (cougar->special_पूर्णांकf)
			hid_hw_बंद(hdev);
	पूर्ण
	hid_hw_stop(hdev);
पूर्ण

अटल पूर्णांक cougar_param_set_g6_is_space(स्थिर अक्षर *val,
					स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक ret;

	ret = param_set_bool(val, kp);
	अगर (ret)
		वापस ret;

	cougar_fix_g6_mapping();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops cougar_g6_is_space_ops = अणु
	.set	= cougar_param_set_g6_is_space,
	.get	= param_get_bool,
पूर्ण;
module_param_cb(g6_is_space, &cougar_g6_is_space_ops, &g6_is_space, 0644);

अटल स्थिर काष्ठा hid_device_id cougar_id_table[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SOLID_YEAR,
			 USB_DEVICE_ID_COUGAR_500K_GAMING_KEYBOARD) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SOLID_YEAR,
			 USB_DEVICE_ID_COUGAR_700K_GAMING_KEYBOARD) पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, cougar_id_table);

अटल काष्ठा hid_driver cougar_driver = अणु
	.name			= "cougar",
	.id_table		= cougar_id_table,
	.report_fixup		= cougar_report_fixup,
	.probe			= cougar_probe,
	.हटाओ			= cougar_हटाओ,
	.raw_event		= cougar_raw_event,
पूर्ण;

module_hid_driver(cougar_driver);
