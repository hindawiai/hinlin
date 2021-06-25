<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Force feedback support क्रम DragonRise Inc. game controllers
 *
 * From what I have gathered, these devices are mass produced in China and are
 * distributed under several venकरोrs. They often share the same design as
 * the original PlayStation DualShock controller.
 *
 * 0079:0006 "DragonRise Inc.   Generic   USB  Joystick  "
 *  - tested with a Tesun USB-703 game controller.
 *
 * Copyright (c) 2009 Riअक्षरd Walmsley <richwalm@gmail.com>
 */

/*
 */

#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

#अगर_घोषित CONFIG_DRAGONRISE_FF

काष्ठा drff_device अणु
	काष्ठा hid_report *report;
पूर्ण;

अटल पूर्णांक drff_play(काष्ठा input_dev *dev, व्योम *data,
				 काष्ठा ff_effect *effect)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	काष्ठा drff_device *drff = data;
	पूर्णांक strong, weak;

	strong = effect->u.rumble.strong_magnitude;
	weak = effect->u.rumble.weak_magnitude;

	dbg_hid("called with 0x%04x 0x%04x", strong, weak);

	अगर (strong || weak) अणु
		strong = strong * 0xff / 0xffff;
		weak = weak * 0xff / 0xffff;

		/* While reverse engineering this device, I found that when
		   this value is set, it causes the strong rumble to function
		   at a near maximum speed, so we'll bypass it. */
		अगर (weak == 0x0a)
			weak = 0x0b;

		drff->report->field[0]->value[0] = 0x51;
		drff->report->field[0]->value[1] = 0x00;
		drff->report->field[0]->value[2] = weak;
		drff->report->field[0]->value[4] = strong;
		hid_hw_request(hid, drff->report, HID_REQ_SET_REPORT);

		drff->report->field[0]->value[0] = 0xfa;
		drff->report->field[0]->value[1] = 0xfe;
	पूर्ण अन्यथा अणु
		drff->report->field[0]->value[0] = 0xf3;
		drff->report->field[0]->value[1] = 0x00;
	पूर्ण

	drff->report->field[0]->value[2] = 0x00;
	drff->report->field[0]->value[4] = 0x00;
	dbg_hid("running with 0x%02x 0x%02x", strong, weak);
	hid_hw_request(hid, drff->report, HID_REQ_SET_REPORT);

	वापस 0;
पूर्ण

अटल पूर्णांक drff_init(काष्ठा hid_device *hid)
अणु
	काष्ठा drff_device *drff;
	काष्ठा hid_report *report;
	काष्ठा hid_input *hidinput;
	काष्ठा list_head *report_list =
			&hid->report_क्रमागत[HID_OUTPUT_REPORT].report_list;
	काष्ठा input_dev *dev;
	पूर्णांक error;

	अगर (list_empty(&hid->inमाला_दो)) अणु
		hid_err(hid, "no inputs found\n");
		वापस -ENODEV;
	पूर्ण
	hidinput = list_first_entry(&hid->inमाला_दो, काष्ठा hid_input, list);
	dev = hidinput->input;

	अगर (list_empty(report_list)) अणु
		hid_err(hid, "no output reports found\n");
		वापस -ENODEV;
	पूर्ण

	report = list_first_entry(report_list, काष्ठा hid_report, list);
	अगर (report->maxfield < 1) अणु
		hid_err(hid, "no fields in the report\n");
		वापस -ENODEV;
	पूर्ण

	अगर (report->field[0]->report_count < 7) अणु
		hid_err(hid, "not enough values in the field\n");
		वापस -ENODEV;
	पूर्ण

	drff = kzalloc(माप(काष्ठा drff_device), GFP_KERNEL);
	अगर (!drff)
		वापस -ENOMEM;

	set_bit(FF_RUMBLE, dev->ffbit);

	error = input_ff_create_memless(dev, drff, drff_play);
	अगर (error) अणु
		kमुक्त(drff);
		वापस error;
	पूर्ण

	drff->report = report;
	drff->report->field[0]->value[0] = 0xf3;
	drff->report->field[0]->value[1] = 0x00;
	drff->report->field[0]->value[2] = 0x00;
	drff->report->field[0]->value[3] = 0x00;
	drff->report->field[0]->value[4] = 0x00;
	drff->report->field[0]->value[5] = 0x00;
	drff->report->field[0]->value[6] = 0x00;
	hid_hw_request(hid, drff->report, HID_REQ_SET_REPORT);

	hid_info(hid, "Force Feedback for DragonRise Inc. "
		 "game controllers by Richard Walmsley <richwalm@gmail.com>\n");

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक drff_init(काष्ठा hid_device *hid)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * The original descriptor of joystick with PID 0x0011, represented by DVTech PC
 * JS19. It seems both copied from another device and a result of confusion
 * either about the specअगरication or about the program used to create the
 * descriptor. In any हाल, it's a wonder it works on Winकरोws.
 *
 *  Usage Page (Desktop),             ; Generic desktop controls (01h)
 *  Usage (Joystick),                 ; Joystick (04h, application collection)
 *  Collection (Application),
 *    Collection (Logical),
 *      Report Size (8),
 *      Report Count (5),
 *      Logical Minimum (0),
 *      Logical Maximum (255),
 *      Physical Minimum (0),
 *      Physical Maximum (255),
 *      Usage (X),                    ; X (30h, dynamic value)
 *      Usage (X),                    ; X (30h, dynamic value)
 *      Usage (X),                    ; X (30h, dynamic value)
 *      Usage (X),                    ; X (30h, dynamic value)
 *      Usage (Y),                    ; Y (31h, dynamic value)
 *      Input (Variable),
 *      Report Size (4),
 *      Report Count (1),
 *      Logical Maximum (7),
 *      Physical Maximum (315),
 *      Unit (Degrees),
 *      Usage (00h),
 *      Input (Variable, Null State),
 *      Unit,
 *      Report Size (1),
 *      Report Count (10),
 *      Logical Maximum (1),
 *      Physical Maximum (1),
 *      Usage Page (Button),          ; Button (09h)
 *      Usage Minimum (01h),
 *      Usage Maximum (0Ah),
 *      Input (Variable),
 *      Usage Page (FF00h),           ; FF00h, venकरोr-defined
 *      Report Size (1),
 *      Report Count (10),
 *      Logical Maximum (1),
 *      Physical Maximum (1),
 *      Usage (01h),
 *      Input (Variable),
 *    End Collection,
 *    Collection (Logical),
 *      Report Size (8),
 *      Report Count (4),
 *      Physical Maximum (255),
 *      Logical Maximum (255),
 *      Usage (02h),
 *      Output (Variable),
 *    End Collection,
 *  End Collection
 */

/* Size of the original descriptor of the PID 0x0011 joystick */
#घोषणा PID0011_RDESC_ORIG_SIZE	101

/* Fixed report descriptor क्रम PID 0x011 joystick */
अटल __u8 pid0011_rdesc_fixed[] = अणु
	0x05, 0x01,         /*  Usage Page (Desktop),           */
	0x09, 0x04,         /*  Usage (Joystick),               */
	0xA1, 0x01,         /*  Collection (Application),       */
	0xA1, 0x02,         /*      Collection (Logical),       */
	0x14,               /*          Logical Minimum (0),    */
	0x75, 0x08,         /*          Report Size (8),        */
	0x95, 0x03,         /*          Report Count (3),       */
	0x81, 0x01,         /*          Input (Constant),       */
	0x26, 0xFF, 0x00,   /*          Logical Maximum (255),  */
	0x95, 0x02,         /*          Report Count (2),       */
	0x09, 0x30,         /*          Usage (X),              */
	0x09, 0x31,         /*          Usage (Y),              */
	0x81, 0x02,         /*          Input (Variable),       */
	0x75, 0x01,         /*          Report Size (1),        */
	0x95, 0x04,         /*          Report Count (4),       */
	0x81, 0x01,         /*          Input (Constant),       */
	0x25, 0x01,         /*          Logical Maximum (1),    */
	0x95, 0x0A,         /*          Report Count (10),      */
	0x05, 0x09,         /*          Usage Page (Button),    */
	0x19, 0x01,         /*          Usage Minimum (01h),    */
	0x29, 0x0A,         /*          Usage Maximum (0Ah),    */
	0x81, 0x02,         /*          Input (Variable),       */
	0x95, 0x0A,         /*          Report Count (10),      */
	0x81, 0x01,         /*          Input (Constant),       */
	0xC0,               /*      End Collection,             */
	0xC0                /*  End Collection                  */
पूर्ण;

अटल __u8 *dr_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
				अचिन्हित पूर्णांक *rsize)
अणु
	चयन (hdev->product) अणु
	हाल 0x0011:
		अगर (*rsize == PID0011_RDESC_ORIG_SIZE) अणु
			rdesc = pid0011_rdesc_fixed;
			*rsize = माप(pid0011_rdesc_fixed);
		पूर्ण
		अवरोध;
	पूर्ण
	वापस rdesc;
पूर्ण

#घोषणा map_असल(c)      hid_map_usage(hi, usage, bit, max, EV_ABS, (c))
#घोषणा map_rel(c)      hid_map_usage(hi, usage, bit, max, EV_REL, (c))

अटल पूर्णांक dr_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
			    काष्ठा hid_field *field, काष्ठा hid_usage *usage,
			    अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	चयन (usage->hid) अणु
	/*
	 * revert to the old hid-input behavior where axes
	 * can be अक्रमomly asचिन्हित when hid->usage is reused.
	 */
	हाल HID_GD_X: हाल HID_GD_Y: हाल HID_GD_Z:
	हाल HID_GD_RX: हाल HID_GD_RY: हाल HID_GD_RZ:
		अगर (field->flags & HID_MAIN_ITEM_RELATIVE)
			map_rel(usage->hid & 0xf);
		अन्यथा
			map_असल(usage->hid & 0xf);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dr_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;

	dev_dbg(&hdev->dev, "DragonRise Inc. HID hardware probe...");

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "parse failed\n");
		जाओ err;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT & ~HID_CONNECT_FF);
	अगर (ret) अणु
		hid_err(hdev, "hw start failed\n");
		जाओ err;
	पूर्ण

	चयन (hdev->product) अणु
	हाल 0x0006:
		ret = drff_init(hdev);
		अगर (ret) अणु
			dev_err(&hdev->dev, "force feedback init failed\n");
			hid_hw_stop(hdev);
			जाओ err;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
err:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hid_device_id dr_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_DRAGONRISE, 0x0006),  पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_DRAGONRISE, 0x0011),  पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, dr_devices);

अटल काष्ठा hid_driver dr_driver = अणु
	.name = "dragonrise",
	.id_table = dr_devices,
	.report_fixup = dr_report_fixup,
	.probe = dr_probe,
	.input_mapping = dr_input_mapping,
पूर्ण;
module_hid_driver(dr_driver);

MODULE_LICENSE("GPL");
