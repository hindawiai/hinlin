<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * drivers/input/tablet/wacom.h
 *
 *  USB Wacom tablet support
 *
 *  Copyright (c) 2000-2004 Vojtech Pavlik	<vojtech@ucw.cz>
 *  Copyright (c) 2000 Andreas Bach Aaen	<abach@stofanet.dk>
 *  Copyright (c) 2000 Clअगरक्रमd Wolf		<clअगरक्रमd@clअगरक्रमd.at>
 *  Copyright (c) 2000 Sam Mosel		<sam.mosel@computer.org>
 *  Copyright (c) 2000 James E. Blair		<corvus@gnu.org>
 *  Copyright (c) 2000 Daniel Egger		<egger@suse.de>
 *  Copyright (c) 2001 Frederic Lepied		<flepied@mandrakesoft.com>
 *  Copyright (c) 2004 Panagiotis Issaris	<panagiotis.issaris@mech.kuleuven.ac.be>
 *  Copyright (c) 2002-2011 Ping Cheng		<pingc@wacom.com>
 *  Copyright (c) 2014 Benjamin Tissoires	<benjamin.tissoires@redhat.com>
 *
 *  ChangeLog:
 *      v0.1 (vp)  - Initial release
 *      v0.2 (aba) - Support क्रम all buttons / combinations
 *      v0.3 (vp)  - Support क्रम Intuos added
 *	v0.4 (sm)  - Support क्रम more Intuos models, menustrip
 *			relative mode, proximity.
 *	v0.5 (vp)  - Big cleanup, nअगरty features हटाओd,
 *			they beदीर्घ in userspace
 *	v1.8 (vp)  - Submit URB only when operating, moved to CVS,
 *			use input_report_key instead of report_btn and
 *			other cleanups
 *	v1.11 (vp) - Add URB ->dev setting क्रम new kernels
 *	v1.11 (jb) - Add support क्रम the 4D Mouse & Lens
 *	v1.12 (de) - Add support क्रम two more inking pen IDs
 *	v1.14 (vp) - Use new USB device id probing scheme.
 *		     Fix Wacom Graphire mouse wheel
 *	v1.18 (vp) - Fix mouse wheel direction
 *		     Make mouse relative
 *      v1.20 (fl) - Report tool id क्रम Intuos devices
 *                 - Multi tools support
 *                 - Corrected Intuos protocol decoding (airbrush, 4D mouse, lens cursor...)
 *                 - Add PL models support
 *		   - Fix Wacom Graphire mouse wheel again
 *	v1.21 (vp) - Removed protocol descriptions
 *		   - Added MISC_SERIAL क्रम tool serial numbers
 *	      (gb) - Identअगरy version on module load.
 *    v1.21.1 (fl) - added Graphire2 support
 *    v1.21.2 (fl) - added Intuos2 support
 *                 - added all the PL ids
 *    v1.21.3 (fl) - added another eraser id from Neil Okamoto
 *                 - added smooth filter क्रम Graphire from Peri Hankey
 *                 - added PenPartner support from Olaf van Es
 *                 - new tool ids from Ole Martin Bjoerndalen
 *	v1.29 (pc) - Add support क्रम more tablets
 *		   - Fix pressure reporting
 *	v1.30 (vp) - Merge 2.4 and 2.5 drivers
 *		   - Since 2.5 now has input_sync(), हटाओ MSC_SERIAL abuse
 *		   - Cleanups here and there
 *    v1.30.1 (pi) - Added Graphire3 support
 *	v1.40 (pc) - Add support क्रम several new devices, fix eraser reporting, ...
 *	v1.43 (pc) - Added support क्रम Cपूर्णांकiq 21UX
 *		   - Fixed a Graphire bug
 *		   - Merged wacom_पूर्णांकuos3_irq पूर्णांकo wacom_पूर्णांकuos_irq
 *	v1.44 (pc) - Added support क्रम Graphire4, Cपूर्णांकiq 710, Intuos3 6x11, etc.
 *		   - Report Device IDs
 *      v1.45 (pc) - Added support क्रम DTF 521, Intuos3 12x12 and 12x19
 *                 - Minor data report fix
 *      v1.46 (pc) - Split wacom.c पूर्णांकo wacom_sys.c and wacom_wac.c,
 *		   - where wacom_sys.c deals with प्रणाली specअगरic code,
 *		   - and wacom_wac.c deals with Wacom specअगरic code
 *		   - Support Intuos3 4x6
 *      v1.47 (pc) - Added support क्रम Bamboo
 *      v1.48 (pc) - Added support क्रम Bamboo1, BambooFun, and Cपूर्णांकiq 12WX
 *      v1.49 (pc) - Added support क्रम USB Tablet PC (0x90, 0x93, and 0x9A)
 *      v1.50 (pc) - Fixed a TabletPC touch bug in 2.6.28
 *      v1.51 (pc) - Added support क्रम Intuos4
 *      v1.52 (pc) - Query Wacom data upon प्रणाली resume
 *                 - add defines क्रम features->type
 *                 - add new devices (0x9F, 0xE2, and 0XE3)
 *      v2.00 (bt) - conversion to a HID driver
 *                 - पूर्णांकegration of the Bluetooth devices
 */

/*
 */
#अगर_अघोषित WACOM_H
#घोषणा WACOM_H
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/hid.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/leds.h>
#समावेश <linux/usb/input.h>
#समावेश <linux/घातer_supply.h>
#समावेश <यंत्र/unaligned.h>

/*
 * Version Inक्रमmation
 */
#घोषणा DRIVER_VERSION "v2.00"
#घोषणा DRIVER_AUTHOR "Vojtech Pavlik <vojtech@ucw.cz>"
#घोषणा DRIVER_DESC "USB Wacom tablet driver"

#घोषणा USB_VENDOR_ID_WACOM	0x056a
#घोषणा USB_VENDOR_ID_LENOVO	0x17ef

क्रमागत wacom_worker अणु
	WACOM_WORKER_WIRELESS,
	WACOM_WORKER_BATTERY,
	WACOM_WORKER_REMOTE,
	WACOM_WORKER_MODE_CHANGE,
पूर्ण;

काष्ठा wacom;

काष्ठा wacom_led अणु
	काष्ठा led_classdev cdev;
	काष्ठा led_trigger trigger;
	काष्ठा wacom *wacom;
	अचिन्हित पूर्णांक group;
	अचिन्हित पूर्णांक id;
	u8 llv;
	u8 hlv;
	bool held;
पूर्ण;

काष्ठा wacom_group_leds अणु
	u8 select; /* status led selector (0..3) */
	काष्ठा wacom_led *leds;
	अचिन्हित पूर्णांक count;
	काष्ठा device *dev;
पूर्ण;

काष्ठा wacom_battery अणु
	काष्ठा wacom *wacom;
	काष्ठा घातer_supply_desc bat_desc;
	काष्ठा घातer_supply *battery;
	अक्षर bat_name[WACOM_NAME_MAX];
	पूर्णांक bat_status;
	पूर्णांक battery_capacity;
	पूर्णांक bat_अक्षरging;
	पूर्णांक bat_connected;
	पूर्णांक ps_connected;
पूर्ण;

काष्ठा wacom_remote अणु
	spinlock_t remote_lock;
	काष्ठा kfअगरo remote_fअगरo;
	काष्ठा kobject *remote_dir;
	काष्ठा अणु
		काष्ठा attribute_group group;
		u32 serial;
		काष्ठा input_dev *input;
		bool रेजिस्टरed;
		काष्ठा wacom_battery battery;
	पूर्ण remotes[WACOM_MAX_REMOTES];
पूर्ण;

काष्ठा wacom अणु
	काष्ठा usb_device *usbdev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा wacom_wac wacom_wac;
	काष्ठा hid_device *hdev;
	काष्ठा mutex lock;
	काष्ठा work_काष्ठा wireless_work;
	काष्ठा work_काष्ठा battery_work;
	काष्ठा work_काष्ठा remote_work;
	काष्ठा delayed_work init_work;
	काष्ठा wacom_remote *remote;
	काष्ठा work_काष्ठा mode_change_work;
	bool generic_has_leds;
	काष्ठा wacom_leds अणु
		काष्ठा wacom_group_leds *groups;
		अचिन्हित पूर्णांक count;
		u8 llv;       /* status led brightness no button (1..127) */
		u8 hlv;       /* status led brightness button pressed (1..127) */
		u8 img_lum;   /* OLED matrix display brightness */
		u8 max_llv;   /* maximum brightness of LED (llv) */
		u8 max_hlv;   /* maximum brightness of LED (hlv) */
	पूर्ण led;
	काष्ठा wacom_battery battery;
	bool resources;
पूर्ण;

अटल अंतरभूत व्योम wacom_schedule_work(काष्ठा wacom_wac *wacom_wac,
				       क्रमागत wacom_worker which)
अणु
	काष्ठा wacom *wacom = container_of(wacom_wac, काष्ठा wacom, wacom_wac);

	चयन (which) अणु
	हाल WACOM_WORKER_WIRELESS:
		schedule_work(&wacom->wireless_work);
		अवरोध;
	हाल WACOM_WORKER_BATTERY:
		schedule_work(&wacom->battery_work);
		अवरोध;
	हाल WACOM_WORKER_REMOTE:
		schedule_work(&wacom->remote_work);
		अवरोध;
	हाल WACOM_WORKER_MODE_CHANGE:
		schedule_work(&wacom->mode_change_work);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Convert a चिन्हित 32-bit पूर्णांकeger to an अचिन्हित n-bit पूर्णांकeger. Unकरोes
 * the normally-helpful work of 'hid_snto32' क्रम fields that use चिन्हित
 * ranges क्रम questionable reasons.
 */
अटल अंतरभूत __u32 wacom_s32tou(s32 value, __u8 n)
अणु
	चयन (n) अणु
	हाल 8:  वापस ((__u8)value);
	हाल 16: वापस ((__u16)value);
	हाल 32: वापस ((__u32)value);
	पूर्ण
	वापस value & (1 << (n - 1)) ? value & (~(~0U << n)) : value;
पूर्ण

बाह्य स्थिर काष्ठा hid_device_id wacom_ids[];

व्योम wacom_wac_irq(काष्ठा wacom_wac *wacom_wac, माप_प्रकार len);
व्योम wacom_setup_device_quirks(काष्ठा wacom *wacom);
पूर्णांक wacom_setup_pen_input_capabilities(काष्ठा input_dev *input_dev,
				   काष्ठा wacom_wac *wacom_wac);
पूर्णांक wacom_setup_touch_input_capabilities(काष्ठा input_dev *input_dev,
				   काष्ठा wacom_wac *wacom_wac);
पूर्णांक wacom_setup_pad_input_capabilities(काष्ठा input_dev *input_dev,
				       काष्ठा wacom_wac *wacom_wac);
व्योम wacom_wac_usage_mapping(काष्ठा hid_device *hdev,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage);
व्योम wacom_wac_event(काष्ठा hid_device *hdev, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, __s32 value);
व्योम wacom_wac_report(काष्ठा hid_device *hdev, काष्ठा hid_report *report);
व्योम wacom_battery_work(काष्ठा work_काष्ठा *work);
क्रमागत led_brightness wacom_leds_brightness_get(काष्ठा wacom_led *led);
काष्ठा wacom_led *wacom_led_find(काष्ठा wacom *wacom, अचिन्हित पूर्णांक group,
				 अचिन्हित पूर्णांक id);
काष्ठा wacom_led *wacom_led_next(काष्ठा wacom *wacom, काष्ठा wacom_led *cur);
पूर्णांक wacom_equivalent_usage(पूर्णांक usage);
पूर्णांक wacom_initialize_leds(काष्ठा wacom *wacom);
#पूर्ण_अगर
