<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB device quirk handling logic and table
 *
 * Copyright (c) 2007 Oliver Neukum
 * Copyright (c) 2007 Greg Kroah-Harपंचांगan <gregkh@suse.de>
 */

#समावेश <linux/moduleparam.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/quirks.h>
#समावेश <linux/usb/hcd.h>
#समावेश "usb.h"

काष्ठा quirk_entry अणु
	u16 vid;
	u16 pid;
	u32 flags;
पूर्ण;

अटल DEFINE_MUTEX(quirk_mutex);

अटल काष्ठा quirk_entry *quirk_list;
अटल अचिन्हित पूर्णांक quirk_count;

अटल अक्षर quirks_param[128];

अटल पूर्णांक quirks_param_set(स्थिर अक्षर *value, स्थिर काष्ठा kernel_param *kp)
अणु
	अक्षर *val, *p, *field;
	u16 vid, pid;
	u32 flags;
	माप_प्रकार i;
	पूर्णांक err;

	val = kstrdup(value, GFP_KERNEL);
	अगर (!val)
		वापस -ENOMEM;

	err = param_set_copystring(val, kp);
	अगर (err) अणु
		kमुक्त(val);
		वापस err;
	पूर्ण

	mutex_lock(&quirk_mutex);

	अगर (!*val) अणु
		quirk_count = 0;
		kमुक्त(quirk_list);
		quirk_list = शून्य;
		जाओ unlock;
	पूर्ण

	क्रम (quirk_count = 1, i = 0; val[i]; i++)
		अगर (val[i] == ',')
			quirk_count++;

	अगर (quirk_list) अणु
		kमुक्त(quirk_list);
		quirk_list = शून्य;
	पूर्ण

	quirk_list = kसुस्मृति(quirk_count, माप(काष्ठा quirk_entry),
			     GFP_KERNEL);
	अगर (!quirk_list) अणु
		quirk_count = 0;
		mutex_unlock(&quirk_mutex);
		kमुक्त(val);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0, p = val; p && *p;) अणु
		/* Each entry consists of VID:PID:flags */
		field = strsep(&p, ":");
		अगर (!field)
			अवरोध;

		अगर (kstrtou16(field, 16, &vid))
			अवरोध;

		field = strsep(&p, ":");
		अगर (!field)
			अवरोध;

		अगर (kstrtou16(field, 16, &pid))
			अवरोध;

		field = strsep(&p, ",");
		अगर (!field || !*field)
			अवरोध;

		/* Collect the flags */
		क्रम (flags = 0; *field; field++) अणु
			चयन (*field) अणु
			हाल 'a':
				flags |= USB_QUIRK_STRING_FETCH_255;
				अवरोध;
			हाल 'b':
				flags |= USB_QUIRK_RESET_RESUME;
				अवरोध;
			हाल 'c':
				flags |= USB_QUIRK_NO_SET_INTF;
				अवरोध;
			हाल 'd':
				flags |= USB_QUIRK_CONFIG_INTF_STRINGS;
				अवरोध;
			हाल 'e':
				flags |= USB_QUIRK_RESET;
				अवरोध;
			हाल 'f':
				flags |= USB_QUIRK_HONOR_BNUMINTERFACES;
				अवरोध;
			हाल 'g':
				flags |= USB_QUIRK_DELAY_INIT;
				अवरोध;
			हाल 'h':
				flags |= USB_QUIRK_LINEAR_UFRAME_INTR_BINTERVAL;
				अवरोध;
			हाल 'i':
				flags |= USB_QUIRK_DEVICE_QUALIFIER;
				अवरोध;
			हाल 'j':
				flags |= USB_QUIRK_IGNORE_REMOTE_WAKEUP;
				अवरोध;
			हाल 'k':
				flags |= USB_QUIRK_NO_LPM;
				अवरोध;
			हाल 'l':
				flags |= USB_QUIRK_LINEAR_FRAME_INTR_BINTERVAL;
				अवरोध;
			हाल 'm':
				flags |= USB_QUIRK_DISCONNECT_SUSPEND;
				अवरोध;
			हाल 'n':
				flags |= USB_QUIRK_DELAY_CTRL_MSG;
				अवरोध;
			हाल 'o':
				flags |= USB_QUIRK_HUB_SLOW_RESET;
				अवरोध;
			/* Ignore unrecognized flag अक्षरacters */
			पूर्ण
		पूर्ण

		quirk_list[i++] = (काष्ठा quirk_entry)
			अणु .vid = vid, .pid = pid, .flags = flags पूर्ण;
	पूर्ण

	अगर (i < quirk_count)
		quirk_count = i;

unlock:
	mutex_unlock(&quirk_mutex);
	kमुक्त(val);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops quirks_param_ops = अणु
	.set = quirks_param_set,
	.get = param_get_string,
पूर्ण;

अटल काष्ठा kparam_string quirks_param_string = अणु
	.maxlen = माप(quirks_param),
	.string = quirks_param,
पूर्ण;

device_param_cb(quirks, &quirks_param_ops, &quirks_param_string, 0644);
MODULE_PARM_DESC(quirks, "Add/modify USB quirks by specifying quirks=vendorID:productID:quirks");

/* Lists of quirky USB devices, split in device quirks and पूर्णांकerface quirks.
 * Device quirks are applied at the very beginning of the क्रमागतeration process,
 * right after पढ़ोing the device descriptor. They can thus only match on device
 * inक्रमmation.
 *
 * Interface quirks are applied after पढ़ोing all the configuration descriptors.
 * They can match on both device and पूर्णांकerface inक्रमmation.
 *
 * Note that the DELAY_INIT and HONOR_BNUMINTERFACES quirks करो not make sense as
 * पूर्णांकerface quirks, as they only influence the क्रमागतeration process which is run
 * beक्रमe processing the पूर्णांकerface quirks.
 *
 * Please keep the lists ordered by:
 * 	1) Venकरोr ID
 * 	2) Product ID
 * 	3) Class ID
 */
अटल स्थिर काष्ठा usb_device_id usb_quirk_list[] = अणु
	/* CBM - Flash disk */
	अणु USB_DEVICE(0x0204, 0x6025), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* WORLDE Controller KS49 or Prodipe MIDI 49C USB controller */
	अणु USB_DEVICE(0x0218, 0x0201), .driver_info =
			USB_QUIRK_CONFIG_INTF_STRINGS पूर्ण,

	/* WORLDE easy key (easykey.25) MIDI controller  */
	अणु USB_DEVICE(0x0218, 0x0401), .driver_info =
			USB_QUIRK_CONFIG_INTF_STRINGS पूर्ण,

	/* HP 5300/5370C scanner */
	अणु USB_DEVICE(0x03f0, 0x0701), .driver_info =
			USB_QUIRK_STRING_FETCH_255 पूर्ण,

	/* HP v222w 16GB Mini USB Drive */
	अणु USB_DEVICE(0x03f0, 0x3f40), .driver_info = USB_QUIRK_DELAY_INIT पूर्ण,

	/* Creative SB Audigy 2 NX */
	अणु USB_DEVICE(0x041e, 0x3020), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* USB3503 */
	अणु USB_DEVICE(0x0424, 0x3503), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Microsoft Wireless Laser Mouse 6000 Receiver */
	अणु USB_DEVICE(0x045e, 0x00e1), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Microsoft LअगरeCam-VX700 v2.0 */
	अणु USB_DEVICE(0x045e, 0x0770), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Microsoft Surface Dock Ethernet (RTL8153 GigE) */
	अणु USB_DEVICE(0x045e, 0x07c6), .driver_info = USB_QUIRK_NO_LPM पूर्ण,

	/* Cherry Stream G230 2.0 (G85-231) and 3.0 (G85-232) */
	अणु USB_DEVICE(0x046a, 0x0023), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Logitech HD Webcam C270 */
	अणु USB_DEVICE(0x046d, 0x0825), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Logitech HD Pro Webcams C920, C920-C, C922, C925e and C930e */
	अणु USB_DEVICE(0x046d, 0x082d), .driver_info = USB_QUIRK_DELAY_INIT पूर्ण,
	अणु USB_DEVICE(0x046d, 0x0841), .driver_info = USB_QUIRK_DELAY_INIT पूर्ण,
	अणु USB_DEVICE(0x046d, 0x0843), .driver_info = USB_QUIRK_DELAY_INIT पूर्ण,
	अणु USB_DEVICE(0x046d, 0x085b), .driver_info = USB_QUIRK_DELAY_INIT पूर्ण,
	अणु USB_DEVICE(0x046d, 0x085c), .driver_info = USB_QUIRK_DELAY_INIT पूर्ण,

	/* Logitech ConferenceCam CC3000e */
	अणु USB_DEVICE(0x046d, 0x0847), .driver_info = USB_QUIRK_DELAY_INIT पूर्ण,
	अणु USB_DEVICE(0x046d, 0x0848), .driver_info = USB_QUIRK_DELAY_INIT पूर्ण,

	/* Logitech PTZ Pro Camera */
	अणु USB_DEVICE(0x046d, 0x0853), .driver_info = USB_QUIRK_DELAY_INIT पूर्ण,

	/* Logitech Screen Share */
	अणु USB_DEVICE(0x046d, 0x086c), .driver_info = USB_QUIRK_NO_LPM पूर्ण,

	/* Logitech Quickcam Fusion */
	अणु USB_DEVICE(0x046d, 0x08c1), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Logitech Quickcam Orbit MP */
	अणु USB_DEVICE(0x046d, 0x08c2), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Logitech Quickcam Pro क्रम Notebook */
	अणु USB_DEVICE(0x046d, 0x08c3), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Logitech Quickcam Pro 5000 */
	अणु USB_DEVICE(0x046d, 0x08c5), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Logitech Quickcam OEM Dell Notebook */
	अणु USB_DEVICE(0x046d, 0x08c6), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Logitech Quickcam OEM Cisco VT Camera II */
	अणु USB_DEVICE(0x046d, 0x08c7), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Logitech Harmony 700-series */
	अणु USB_DEVICE(0x046d, 0xc122), .driver_info = USB_QUIRK_DELAY_INIT पूर्ण,

	/* Philips PSC805 audio device */
	अणु USB_DEVICE(0x0471, 0x0155), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Plantronic Audio 655 DSP */
	अणु USB_DEVICE(0x047f, 0xc008), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Plantronic Audio 648 USB */
	अणु USB_DEVICE(0x047f, 0xc013), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Artisman Watchकरोg Dongle */
	अणु USB_DEVICE(0x04b4, 0x0526), .driver_info =
			USB_QUIRK_CONFIG_INTF_STRINGS पूर्ण,

	/* Microchip Joss Optical infrared touchboard device */
	अणु USB_DEVICE(0x04d8, 0x000c), .driver_info =
			USB_QUIRK_CONFIG_INTF_STRINGS पूर्ण,

	/* CarrolTouch 4000U */
	अणु USB_DEVICE(0x04e7, 0x0009), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* CarrolTouch 4500U */
	अणु USB_DEVICE(0x04e7, 0x0030), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Samsung Android phone modem - ID conflict with SPH-I500 */
	अणु USB_DEVICE(0x04e8, 0x6601), .driver_info =
			USB_QUIRK_CONFIG_INTF_STRINGS पूर्ण,

	/* Elan Touchscreen */
	अणु USB_DEVICE(0x04f3, 0x0089), .driver_info =
			USB_QUIRK_DEVICE_QUALIFIER पूर्ण,

	अणु USB_DEVICE(0x04f3, 0x009b), .driver_info =
			USB_QUIRK_DEVICE_QUALIFIER पूर्ण,

	अणु USB_DEVICE(0x04f3, 0x010c), .driver_info =
			USB_QUIRK_DEVICE_QUALIFIER पूर्ण,

	अणु USB_DEVICE(0x04f3, 0x0125), .driver_info =
			USB_QUIRK_DEVICE_QUALIFIER पूर्ण,

	अणु USB_DEVICE(0x04f3, 0x016f), .driver_info =
			USB_QUIRK_DEVICE_QUALIFIER पूर्ण,

	अणु USB_DEVICE(0x04f3, 0x0381), .driver_info =
			USB_QUIRK_NO_LPM पूर्ण,

	अणु USB_DEVICE(0x04f3, 0x21b8), .driver_info =
			USB_QUIRK_DEVICE_QUALIFIER पूर्ण,

	/* Roland SC-8820 */
	अणु USB_DEVICE(0x0582, 0x0007), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Edirol SD-20 */
	अणु USB_DEVICE(0x0582, 0x0027), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Alcor Micro Corp. Hub */
	अणु USB_DEVICE(0x058f, 0x9254), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* appletouch */
	अणु USB_DEVICE(0x05ac, 0x021a), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Genesys Logic hub, पूर्णांकernally used by KY-688 USB 3.1 Type-C Hub */
	अणु USB_DEVICE(0x05e3, 0x0612), .driver_info = USB_QUIRK_NO_LPM पूर्ण,

	/* ELSA MicroLink 56K */
	अणु USB_DEVICE(0x05cc, 0x2267), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Genesys Logic hub, पूर्णांकernally used by Moshi USB to Ethernet Adapter */
	अणु USB_DEVICE(0x05e3, 0x0616), .driver_info = USB_QUIRK_NO_LPM पूर्ण,

	/* Avision AV600U */
	अणु USB_DEVICE(0x0638, 0x0a13), .driver_info =
	  USB_QUIRK_STRING_FETCH_255 पूर्ण,

	/* Saitek Cyborg Gold Joystick */
	अणु USB_DEVICE(0x06a3, 0x0006), .driver_info =
			USB_QUIRK_CONFIG_INTF_STRINGS पूर्ण,

	/* Agfa SNAPSCAN 1212U */
	अणु USB_DEVICE(0x06bd, 0x0001), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Guillemot Webcam Hercules Dualpix Exchange (2nd ID) */
	अणु USB_DEVICE(0x06f8, 0x0804), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Guillemot Webcam Hercules Dualpix Exchange*/
	अणु USB_DEVICE(0x06f8, 0x3005), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Guillemot Hercules DJ Console audio card (BZ 208357) */
	अणु USB_DEVICE(0x06f8, 0xb000), .driver_info =
			USB_QUIRK_ENDPOINT_IGNORE पूर्ण,

	/* Midiman M-Audio Keystation 88es */
	अणु USB_DEVICE(0x0763, 0x0192), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* SanDisk Ultra Fit and Ultra Flair */
	अणु USB_DEVICE(0x0781, 0x5583), .driver_info = USB_QUIRK_NO_LPM पूर्ण,
	अणु USB_DEVICE(0x0781, 0x5591), .driver_info = USB_QUIRK_NO_LPM पूर्ण,

	/* M-Systems Flash Disk Pioneers */
	अणु USB_DEVICE(0x08ec, 0x1000), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Baum Vario Ultra */
	अणु USB_DEVICE(0x0904, 0x6101), .driver_info =
			USB_QUIRK_LINEAR_FRAME_INTR_BINTERVAL पूर्ण,
	अणु USB_DEVICE(0x0904, 0x6102), .driver_info =
			USB_QUIRK_LINEAR_FRAME_INTR_BINTERVAL पूर्ण,
	अणु USB_DEVICE(0x0904, 0x6103), .driver_info =
			USB_QUIRK_LINEAR_FRAME_INTR_BINTERVAL पूर्ण,

	/* Sound Devices USBPre2 */
	अणु USB_DEVICE(0x0926, 0x0202), .driver_info =
			USB_QUIRK_ENDPOINT_IGNORE पूर्ण,

	/* Sound Devices MixPre-D */
	अणु USB_DEVICE(0x0926, 0x0208), .driver_info =
			USB_QUIRK_ENDPOINT_IGNORE पूर्ण,

	/* Keytouch QWERTY Panel keyboard */
	अणु USB_DEVICE(0x0926, 0x3333), .driver_info =
			USB_QUIRK_CONFIG_INTF_STRINGS पूर्ण,

	/* Kingston DataTraveler 3.0 */
	अणु USB_DEVICE(0x0951, 0x1666), .driver_info = USB_QUIRK_NO_LPM पूर्ण,

	/* X-Rite/Gretag-Macbeth Eye-One Pro display colorimeter */
	अणु USB_DEVICE(0x0971, 0x2000), .driver_info = USB_QUIRK_NO_SET_INTF पूर्ण,

	/* ELMO L-12F करोcument camera */
	अणु USB_DEVICE(0x09a1, 0x0028), .driver_info = USB_QUIRK_DELAY_CTRL_MSG पूर्ण,

	/* Broadcom BCM92035DGROM BT करोngle */
	अणु USB_DEVICE(0x0a5c, 0x2021), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* MAYA44USB sound device */
	अणु USB_DEVICE(0x0a92, 0x0091), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* ASUS Base Station(T100) */
	अणु USB_DEVICE(0x0b05, 0x17e0), .driver_info =
			USB_QUIRK_IGNORE_REMOTE_WAKEUP पूर्ण,

	/* Realtek hub in Dell WD19 (Type-C) */
	अणु USB_DEVICE(0x0bda, 0x0487), .driver_info = USB_QUIRK_NO_LPM पूर्ण,
	अणु USB_DEVICE(0x0bda, 0x5487), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Generic RTL8153 based ethernet adapters */
	अणु USB_DEVICE(0x0bda, 0x8153), .driver_info = USB_QUIRK_NO_LPM पूर्ण,

	/* SONiX USB DEVICE Touchpad */
	अणु USB_DEVICE(0x0c45, 0x7056), .driver_info =
			USB_QUIRK_IGNORE_REMOTE_WAKEUP पूर्ण,

	/* Action Semiconductor flash disk */
	अणु USB_DEVICE(0x10d6, 0x2200), .driver_info =
			USB_QUIRK_STRING_FETCH_255 पूर्ण,

	/* novation SoundControl XL */
	अणु USB_DEVICE(0x1235, 0x0061), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Huawei 4G LTE module */
	अणु USB_DEVICE(0x12d1, 0x15bb), .driver_info =
			USB_QUIRK_DISCONNECT_SUSPEND पूर्ण,
	अणु USB_DEVICE(0x12d1, 0x15c3), .driver_info =
			USB_QUIRK_DISCONNECT_SUSPEND पूर्ण,

	/* SKYMEDI USB_DRIVE */
	अणु USB_DEVICE(0x1516, 0x8628), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Razer - Razer Blade Keyboard */
	अणु USB_DEVICE(0x1532, 0x0116), .driver_info =
			USB_QUIRK_LINEAR_UFRAME_INTR_BINTERVAL पूर्ण,

	/* Lenovo ThinkCenter A630Z TI024Gen3 usb-audio */
	अणु USB_DEVICE(0x17ef, 0xa012), .driver_info =
			USB_QUIRK_DISCONNECT_SUSPEND पूर्ण,

	/* Lenovo ThinkPad USB-C Dock Gen2 Ethernet (RTL8153 GigE) */
	अणु USB_DEVICE(0x17ef, 0xa387), .driver_info = USB_QUIRK_NO_LPM पूर्ण,

	/* BUILDWIN Photo Frame */
	अणु USB_DEVICE(0x1908, 0x1315), .driver_info =
			USB_QUIRK_HONOR_BNUMINTERFACES पूर्ण,

	/* Protocol and OTG Electrical Test Device */
	अणु USB_DEVICE(0x1a0a, 0x0200), .driver_info =
			USB_QUIRK_LINEAR_UFRAME_INTR_BINTERVAL पूर्ण,

	/* Terminus Technology Inc. Hub */
	अणु USB_DEVICE(0x1a40, 0x0101), .driver_info = USB_QUIRK_HUB_SLOW_RESET पूर्ण,

	/* Corsair K70 RGB */
	अणु USB_DEVICE(0x1b1c, 0x1b13), .driver_info = USB_QUIRK_DELAY_INIT |
	  USB_QUIRK_DELAY_CTRL_MSG पूर्ण,

	/* Corsair Strafe */
	अणु USB_DEVICE(0x1b1c, 0x1b15), .driver_info = USB_QUIRK_DELAY_INIT |
	  USB_QUIRK_DELAY_CTRL_MSG पूर्ण,

	/* Corsair Strafe RGB */
	अणु USB_DEVICE(0x1b1c, 0x1b20), .driver_info = USB_QUIRK_DELAY_INIT |
	  USB_QUIRK_DELAY_CTRL_MSG पूर्ण,

	/* Corsair K70 LUX RGB */
	अणु USB_DEVICE(0x1b1c, 0x1b33), .driver_info = USB_QUIRK_DELAY_INIT पूर्ण,

	/* Corsair K70 LUX */
	अणु USB_DEVICE(0x1b1c, 0x1b36), .driver_info = USB_QUIRK_DELAY_INIT पूर्ण,

	/* Corsair K70 RGB RAPDIFIRE */
	अणु USB_DEVICE(0x1b1c, 0x1b38), .driver_info = USB_QUIRK_DELAY_INIT |
	  USB_QUIRK_DELAY_CTRL_MSG पूर्ण,

	/* MIDI keyboard WORLDE MINI */
	अणु USB_DEVICE(0x1c75, 0x0204), .driver_info =
			USB_QUIRK_CONFIG_INTF_STRINGS पूर्ण,

	/* Acer C120 LED Projector */
	अणु USB_DEVICE(0x1de1, 0xc102), .driver_info = USB_QUIRK_NO_LPM पूर्ण,

	/* Blackmagic Design Intensity Shuttle */
	अणु USB_DEVICE(0x1edb, 0xbd3b), .driver_info = USB_QUIRK_NO_LPM पूर्ण,

	/* Blackmagic Design UltraStudio SDI */
	अणु USB_DEVICE(0x1edb, 0xbd4f), .driver_info = USB_QUIRK_NO_LPM पूर्ण,

	/* Hauppauge HVR-950q */
	अणु USB_DEVICE(0x2040, 0x7200), .driver_info =
			USB_QUIRK_CONFIG_INTF_STRINGS पूर्ण,

	/* Raydium Touchscreen */
	अणु USB_DEVICE(0x2386, 0x3114), .driver_info = USB_QUIRK_NO_LPM पूर्ण,

	अणु USB_DEVICE(0x2386, 0x3119), .driver_info = USB_QUIRK_NO_LPM पूर्ण,

	अणु USB_DEVICE(0x2386, 0x350e), .driver_info = USB_QUIRK_NO_LPM पूर्ण,

	/* DJI CineSSD */
	अणु USB_DEVICE(0x2ca3, 0x0031), .driver_info = USB_QUIRK_NO_LPM पूर्ण,

	/* Fibocom L850-GL LTE Modem */
	अणु USB_DEVICE(0x2cb7, 0x0007), .driver_info =
			USB_QUIRK_IGNORE_REMOTE_WAKEUP पूर्ण,

	/* INTEL VALUE SSD */
	अणु USB_DEVICE(0x8086, 0xf1a5), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	अणु पूर्ण  /* terminating entry must be last */
पूर्ण;

अटल स्थिर काष्ठा usb_device_id usb_पूर्णांकerface_quirk_list[] = अणु
	/* Logitech UVC Cameras */
	अणु USB_VENDOR_AND_INTERFACE_INFO(0x046d, USB_CLASS_VIDEO, 1, 0),
	  .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	अणु पूर्ण  /* terminating entry must be last */
पूर्ण;

अटल स्थिर काष्ठा usb_device_id usb_amd_resume_quirk_list[] = अणु
	/* Lenovo Mouse with Pixart controller */
	अणु USB_DEVICE(0x17ef, 0x602e), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Pixart Mouse */
	अणु USB_DEVICE(0x093a, 0x2500), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,
	अणु USB_DEVICE(0x093a, 0x2510), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,
	अणु USB_DEVICE(0x093a, 0x2521), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,
	अणु USB_DEVICE(0x03f0, 0x2b4a), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	/* Logitech Optical Mouse M90/M100 */
	अणु USB_DEVICE(0x046d, 0xc05a), .driver_info = USB_QUIRK_RESET_RESUME पूर्ण,

	अणु पूर्ण  /* terminating entry must be last */
पूर्ण;

/*
 * Entries क्रम endpoपूर्णांकs that should be ignored when parsing configuration
 * descriptors.
 *
 * Matched क्रम devices with USB_QUIRK_ENDPOINT_IGNORE.
 */
अटल स्थिर काष्ठा usb_device_id usb_endpoपूर्णांक_ignore[] = अणु
	अणु USB_DEVICE_INTERFACE_NUMBER(0x06f8, 0xb000, 5), .driver_info = 0x01 पूर्ण,
	अणु USB_DEVICE_INTERFACE_NUMBER(0x06f8, 0xb000, 5), .driver_info = 0x81 पूर्ण,
	अणु USB_DEVICE_INTERFACE_NUMBER(0x0926, 0x0202, 1), .driver_info = 0x85 पूर्ण,
	अणु USB_DEVICE_INTERFACE_NUMBER(0x0926, 0x0208, 1), .driver_info = 0x85 पूर्ण,
	अणु पूर्ण
पूर्ण;

bool usb_endpoपूर्णांक_is_ignored(काष्ठा usb_device *udev,
			     काष्ठा usb_host_पूर्णांकerface *पूर्णांकf,
			     काष्ठा usb_endpoपूर्णांक_descriptor *epd)
अणु
	स्थिर काष्ठा usb_device_id *id;
	अचिन्हित पूर्णांक address;

	क्रम (id = usb_endpoपूर्णांक_ignore; id->match_flags; ++id) अणु
		अगर (!usb_match_device(udev, id))
			जारी;

		अगर (!usb_match_one_id_पूर्णांकf(udev, पूर्णांकf, id))
			जारी;

		address = id->driver_info;
		अगर (address == epd->bEndpoपूर्णांकAddress)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool usb_match_any_पूर्णांकerface(काष्ठा usb_device *udev,
				    स्थिर काष्ठा usb_device_id *id)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < udev->descriptor.bNumConfigurations; ++i) अणु
		काष्ठा usb_host_config *cfg = &udev->config[i];
		अचिन्हित पूर्णांक j;

		क्रम (j = 0; j < cfg->desc.bNumInterfaces; ++j) अणु
			काष्ठा usb_पूर्णांकerface_cache *cache;
			काष्ठा usb_host_पूर्णांकerface *पूर्णांकf;

			cache = cfg->पूर्णांकf_cache[j];
			अगर (cache->num_altsetting == 0)
				जारी;

			पूर्णांकf = &cache->altsetting[0];
			अगर (usb_match_one_id_पूर्णांकf(udev, पूर्णांकf, id))
				वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक usb_amd_resume_quirk(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_hcd *hcd;

	hcd = bus_to_hcd(udev->bus);
	/* The device should be attached directly to root hub */
	अगर (udev->level == 1 && hcd->amd_resume_bug == 1)
		वापस 1;

	वापस 0;
पूर्ण

अटल u32 usb_detect_अटल_quirks(काष्ठा usb_device *udev,
				    स्थिर काष्ठा usb_device_id *id)
अणु
	u32 quirks = 0;

	क्रम (; id->match_flags; id++) अणु
		अगर (!usb_match_device(udev, id))
			जारी;

		अगर ((id->match_flags & USB_DEVICE_ID_MATCH_INT_INFO) &&
		    !usb_match_any_पूर्णांकerface(udev, id))
			जारी;

		quirks |= (u32)(id->driver_info);
	पूर्ण

	वापस quirks;
पूर्ण

अटल u32 usb_detect_dynamic_quirks(काष्ठा usb_device *udev)
अणु
	u16 vid = le16_to_cpu(udev->descriptor.idVenकरोr);
	u16 pid = le16_to_cpu(udev->descriptor.idProduct);
	पूर्णांक i, flags = 0;

	mutex_lock(&quirk_mutex);

	क्रम (i = 0; i < quirk_count; i++) अणु
		अगर (vid == quirk_list[i].vid && pid == quirk_list[i].pid) अणु
			flags = quirk_list[i].flags;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&quirk_mutex);

	वापस flags;
पूर्ण

/*
 * Detect any quirks the device has, and करो any housekeeping क्रम it अगर needed.
 */
व्योम usb_detect_quirks(काष्ठा usb_device *udev)
अणु
	udev->quirks = usb_detect_अटल_quirks(udev, usb_quirk_list);

	/*
	 * Pixart-based mice would trigger remote wakeup issue on AMD
	 * Yangtze chipset, so set them as RESET_RESUME flag.
	 */
	अगर (usb_amd_resume_quirk(udev))
		udev->quirks |= usb_detect_अटल_quirks(udev,
				usb_amd_resume_quirk_list);

	udev->quirks ^= usb_detect_dynamic_quirks(udev);

	अगर (udev->quirks)
		dev_dbg(&udev->dev, "USB quirks for this device: %x\n",
			udev->quirks);

#अगर_घोषित CONFIG_USB_DEFAULT_PERSIST
	अगर (!(udev->quirks & USB_QUIRK_RESET))
		udev->persist_enabled = 1;
#अन्यथा
	/* Hubs are स्वतःmatically enabled क्रम USB-PERSIST */
	अगर (udev->descriptor.bDeviceClass == USB_CLASS_HUB)
		udev->persist_enabled = 1;
#पूर्ण_अगर	/* CONFIG_USB_DEFAULT_PERSIST */
पूर्ण

व्योम usb_detect_पूर्णांकerface_quirks(काष्ठा usb_device *udev)
अणु
	u32 quirks;

	quirks = usb_detect_अटल_quirks(udev, usb_पूर्णांकerface_quirk_list);
	अगर (quirks == 0)
		वापस;

	dev_dbg(&udev->dev, "USB interface quirks for this device: %x\n",
		quirks);
	udev->quirks |= quirks;
पूर्ण

व्योम usb_release_quirk_list(व्योम)
अणु
	mutex_lock(&quirk_mutex);
	kमुक्त(quirk_list);
	quirk_list = शून्य;
	mutex_unlock(&quirk_mutex);
पूर्ण
