<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * X-Box gamepad driver
 *
 * Copyright (c) 2002 Marko Friedemann <mfr@bmx-chemnitz.de>
 *               2004 Oliver Schwartz <Oliver.Schwartz@gmx.de>,
 *                    Steven Toth <steve@toth.demon.co.uk>,
 *                    Franz Lehner <franz@caos.at>,
 *                    Ivan Hawkes <blackhawk@ivanhawkes.com>
 *               2005 Dominic Cerquetti <binary1230@yahoo.com>
 *               2006 Adam Buchbinder <adam.buchbinder@gmail.com>
 *               2007 Jan Kratochvil <honza@jikos.cz>
 *               2010 Christoph Fritz <chf.fritz@googlemail.com>
 *
 * This driver is based on:
 *  - inक्रमmation from     http://euc.jp/periphs/xbox-controller.ja.hपंचांगl
 *  - the iForce driver    drivers/अक्षर/joystick/अगरorce.c
 *  - the skeleton-driver  drivers/usb/usb-skeleton.c
 *  - Xbox 360 inक्रमmation http://www.मुक्त60.org/wiki/Gamepad
 *  - Xbox One inक्रमmation https://github.com/quantus/xbox-one-controller-protocol
 *
 * Thanks to:
 *  - ITO Takayuki क्रम providing essential xpad inक्रमmation on his website
 *  - Vojtech Pavlik     - अगरorce driver / input subप्रणाली
 *  - Greg Kroah-Harपंचांगan - usb-skeleton driver
 *  - XBOX Linux project - extra USB id's
 *  - Pekka Pथघyry (quantus) - Xbox One controller reverse engineering
 *
 * TODO:
 *  - fine tune axes (especially trigger axes)
 *  - fix "analog" buttons (reported as digital now)
 *  - get rumble working
 *  - need USB IDs क्रम other dance pads
 *
 * History:
 *
 * 2002-06-27 - 0.0.1 : first version, just said "XBOX HID controller"
 *
 * 2002-07-02 - 0.0.2 : basic working version
 *  - all axes and 9 of the 10 buttons work (german InterAct device)
 *  - the black button करोes not work
 *
 * 2002-07-14 - 0.0.3 : rework by Vojtech Pavlik
 *  - indentation fixes
 *  - usb + input init sequence fixes
 *
 * 2002-07-16 - 0.0.4 : minor changes, merge with Vojtech's v0.0.3
 *  - verअगरied the lack of HID and report descriptors
 *  - verअगरied that ALL buttons WORK
 *  - fixed d-pad to axes mapping
 *
 * 2002-07-17 - 0.0.5 : simplअगरied d-pad handling
 *
 * 2004-10-02 - 0.0.6 : DDR pad support
 *  - borrowed from the XBOX linux kernel
 *  - USB id's क्रम commonly used dance pads are present
 *  - dance pads will map D-PAD to buttons, not axes
 *  - pass the module paramater 'dpad_to_buttons' to क्रमce
 *    the D-PAD to map to buttons अगर your pad is not detected
 *
 * Later changes can be tracked in SCM.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/input.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/module.h>
#समावेश <linux/usb/input.h>
#समावेश <linux/usb/quirks.h>

#घोषणा XPAD_PKT_LEN 64

/*
 * xbox d-pads should map to buttons, as is required क्रम DDR pads
 * but we map them to axes when possible to simplअगरy things
 */
#घोषणा MAP_DPAD_TO_BUTTONS		(1 << 0)
#घोषणा MAP_TRIGGERS_TO_BUTTONS		(1 << 1)
#घोषणा MAP_STICKS_TO_शून्य		(1 << 2)
#घोषणा DANCEPAD_MAP_CONFIG	(MAP_DPAD_TO_BUTTONS |			\
				MAP_TRIGGERS_TO_BUTTONS | MAP_STICKS_TO_शून्य)

#घोषणा XTYPE_XBOX        0
#घोषणा XTYPE_XBOX360     1
#घोषणा XTYPE_XBOX360W    2
#घोषणा XTYPE_XBOXONE     3
#घोषणा XTYPE_UNKNOWN     4

अटल bool dpad_to_buttons;
module_param(dpad_to_buttons, bool, S_IRUGO);
MODULE_PARM_DESC(dpad_to_buttons, "Map D-PAD to buttons rather than axes for unknown pads");

अटल bool triggers_to_buttons;
module_param(triggers_to_buttons, bool, S_IRUGO);
MODULE_PARM_DESC(triggers_to_buttons, "Map triggers to buttons rather than axes for unknown pads");

अटल bool sticks_to_null;
module_param(sticks_to_null, bool, S_IRUGO);
MODULE_PARM_DESC(sticks_to_null, "Do not map sticks at all for unknown pads");

अटल bool स्वतः_घातeroff = true;
module_param(स्वतः_घातeroff, bool, S_IWUSR | S_IRUGO);
MODULE_PARM_DESC(स्वतः_घातeroff, "Power off wireless controllers on suspend");

अटल स्थिर काष्ठा xpad_device अणु
	u16 idVenकरोr;
	u16 idProduct;
	अक्षर *name;
	u8 mapping;
	u8 xtype;
पूर्ण xpad_device[] = अणु
	अणु 0x0079, 0x18d4, "GPD Win 2 X-Box Controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x044f, 0x0f00, "Thrustmaster Wheel", 0, XTYPE_XBOX पूर्ण,
	अणु 0x044f, 0x0f03, "Thrustmaster Wheel", 0, XTYPE_XBOX पूर्ण,
	अणु 0x044f, 0x0f07, "Thrustmaster, Inc. Controller", 0, XTYPE_XBOX पूर्ण,
	अणु 0x044f, 0x0f10, "Thrustmaster Modena GT Wheel", 0, XTYPE_XBOX पूर्ण,
	अणु 0x044f, 0xb326, "Thrustmaster Gamepad GP XID", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x045e, 0x0202, "Microsoft X-Box pad v1 (US)", 0, XTYPE_XBOX पूर्ण,
	अणु 0x045e, 0x0285, "Microsoft X-Box pad (Japan)", 0, XTYPE_XBOX पूर्ण,
	अणु 0x045e, 0x0287, "Microsoft Xbox Controller S", 0, XTYPE_XBOX पूर्ण,
	अणु 0x045e, 0x0288, "Microsoft Xbox Controller S v2", 0, XTYPE_XBOX पूर्ण,
	अणु 0x045e, 0x0289, "Microsoft X-Box pad v2 (US)", 0, XTYPE_XBOX पूर्ण,
	अणु 0x045e, 0x028e, "Microsoft X-Box 360 pad", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x045e, 0x028f, "Microsoft X-Box 360 pad v2", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x045e, 0x0291, "Xbox 360 Wireless Receiver (XBOX)", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX360W पूर्ण,
	अणु 0x045e, 0x02d1, "Microsoft X-Box One pad", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x045e, 0x02dd, "Microsoft X-Box One pad (Firmware 2015)", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x045e, 0x02e3, "Microsoft X-Box One Elite pad", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x045e, 0x02ea, "Microsoft X-Box One S pad", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x045e, 0x0719, "Xbox 360 Wireless Receiver", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX360W पूर्ण,
	अणु 0x046d, 0xc21d, "Logitech Gamepad F310", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x046d, 0xc21e, "Logitech Gamepad F510", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x046d, 0xc21f, "Logitech Gamepad F710", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x046d, 0xc242, "Logitech Chillstream Controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x046d, 0xca84, "Logitech Xbox Cordless Controller", 0, XTYPE_XBOX पूर्ण,
	अणु 0x046d, 0xca88, "Logitech Compact Controller for Xbox", 0, XTYPE_XBOX पूर्ण,
	अणु 0x046d, 0xca8a, "Logitech Precision Vibration Feedback Wheel", 0, XTYPE_XBOX पूर्ण,
	अणु 0x046d, 0xcaa3, "Logitech DriveFx Racing Wheel", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x056e, 0x2004, "Elecom JC-U3613M", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x05fd, 0x1007, "Mad Catz Controller (unverified)", 0, XTYPE_XBOX पूर्ण,
	अणु 0x05fd, 0x107a, "InterAct 'PowerPad Pro' X-Box pad (Germany)", 0, XTYPE_XBOX पूर्ण,
	अणु 0x05fe, 0x3030, "Chic Controller", 0, XTYPE_XBOX पूर्ण,
	अणु 0x05fe, 0x3031, "Chic Controller", 0, XTYPE_XBOX पूर्ण,
	अणु 0x062a, 0x0020, "Logic3 Xbox GamePad", 0, XTYPE_XBOX पूर्ण,
	अणु 0x062a, 0x0033, "Competition Pro Steering Wheel", 0, XTYPE_XBOX पूर्ण,
	अणु 0x06a3, 0x0200, "Saitek Racing Wheel", 0, XTYPE_XBOX पूर्ण,
	अणु 0x06a3, 0x0201, "Saitek Adrenalin", 0, XTYPE_XBOX पूर्ण,
	अणु 0x06a3, 0xf51a, "Saitek P3600", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0738, 0x4506, "Mad Catz 4506 Wireless Controller", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0738, 0x4516, "Mad Catz Control Pad", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0738, 0x4520, "Mad Catz Control Pad Pro", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0738, 0x4522, "Mad Catz LumiCON", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0738, 0x4526, "Mad Catz Control Pad Pro", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0738, 0x4530, "Mad Catz Universal MC2 Racing Wheel and Pedals", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0738, 0x4536, "Mad Catz MicroCON", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0738, 0x4540, "Mad Catz Beat Pad", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX पूर्ण,
	अणु 0x0738, 0x4556, "Mad Catz Lynx Wireless Controller", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0738, 0x4586, "Mad Catz MicroCon Wireless Controller", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0738, 0x4588, "Mad Catz Blaster", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0738, 0x45ff, "Mad Catz Beat Pad (w/ Handle)", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX पूर्ण,
	अणु 0x0738, 0x4716, "Mad Catz Wired Xbox 360 Controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0738, 0x4718, "Mad Catz Street Fighter IV FightStick SE", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0738, 0x4726, "Mad Catz Xbox 360 Controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0738, 0x4728, "Mad Catz Street Fighter IV FightPad", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x0738, 0x4736, "Mad Catz MicroCon Gamepad", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0738, 0x4738, "Mad Catz Wired Xbox 360 Controller (SFIV)", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x0738, 0x4740, "Mad Catz Beat Pad", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0738, 0x4743, "Mad Catz Beat Pad Pro", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX पूर्ण,
	अणु 0x0738, 0x4758, "Mad Catz Arcade Game Stick", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x0738, 0x4a01, "Mad Catz FightStick TE 2", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOXONE पूर्ण,
	अणु 0x0738, 0x6040, "Mad Catz Beat Pad Pro", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX पूर्ण,
	अणु 0x0738, 0x9871, "Mad Catz Portable Drum", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0738, 0xb726, "Mad Catz Xbox controller - MW2", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0738, 0xb738, "Mad Catz MVC2TE Stick 2", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x0738, 0xbeef, "Mad Catz JOYTECH NEO SE Advanced GamePad", XTYPE_XBOX360 पूर्ण,
	अणु 0x0738, 0xcb02, "Saitek Cyborg Rumble Pad - PC/Xbox 360", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0738, 0xcb03, "Saitek P3200 Rumble Pad - PC/Xbox 360", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0738, 0xcb29, "Saitek Aviator Stick AV8R02", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0738, 0xf738, "Super SFIV FightStick TE S", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x07ff, 0xffff, "Mad Catz GamePad", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0c12, 0x0005, "Intec wireless", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0c12, 0x8801, "Nyko Xbox Controller", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0c12, 0x8802, "Zeroplus Xbox Controller", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0c12, 0x8809, "RedOctane Xbox Dance Pad", DANCEPAD_MAP_CONFIG, XTYPE_XBOX पूर्ण,
	अणु 0x0c12, 0x880a, "Pelican Eclipse PL-2023", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0c12, 0x8810, "Zeroplus Xbox Controller", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0c12, 0x9902, "HAMA VibraX - *FAULTY HARDWARE*", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0d2f, 0x0002, "Andamiro Pump It Up pad", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX पूर्ण,
	अणु 0x0e4c, 0x1097, "Radica Gamester Controller", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0e4c, 0x1103, "Radica Gamester Reflex", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX पूर्ण,
	अणु 0x0e4c, 0x2390, "Radica Games Jtech Controller", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0e4c, 0x3510, "Radica Gamester", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0e6f, 0x0003, "Logic3 Freebird wireless Controller", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0e6f, 0x0005, "Eclipse wireless Controller", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0e6f, 0x0006, "Edge wireless Controller", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0e6f, 0x0008, "After Glow Pro Controller", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0e6f, 0x0105, "HSM3 Xbox360 dancepad", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x0e6f, 0x0113, "Afterglow AX.1 Gamepad for Xbox 360", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0e6f, 0x011f, "Rock Candy Gamepad Wired Controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0e6f, 0x0131, "PDP EA Sports Controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0e6f, 0x0133, "Xbox 360 Wired Controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0e6f, 0x0139, "Afterglow Prismatic Wired Controller", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x0e6f, 0x013a, "PDP Xbox One Controller", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x0e6f, 0x0146, "Rock Candy Wired Controller for Xbox One", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x0e6f, 0x0147, "PDP Marvel Xbox One Controller", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x0e6f, 0x015c, "PDP Xbox One Arcade Stick", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOXONE पूर्ण,
	अणु 0x0e6f, 0x0161, "PDP Xbox One Controller", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x0e6f, 0x0162, "PDP Xbox One Controller", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x0e6f, 0x0163, "PDP Xbox One Controller", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x0e6f, 0x0164, "PDP Battlefield One", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x0e6f, 0x0165, "PDP Titanfall 2", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x0e6f, 0x0201, "Pelican PL-3601 'TSZ' Wired Xbox 360 Controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0e6f, 0x0213, "Afterglow Gamepad for Xbox 360", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0e6f, 0x021f, "Rock Candy Gamepad for Xbox 360", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0e6f, 0x0246, "Rock Candy Gamepad for Xbox One 2015", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x0e6f, 0x02a0, "PDP Xbox One Controller", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x0e6f, 0x02a1, "PDP Xbox One Controller", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x0e6f, 0x02a2, "PDP Wired Controller for Xbox One - Crimson Red", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x0e6f, 0x02a4, "PDP Wired Controller for Xbox One - Stealth Series", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x0e6f, 0x02a6, "PDP Wired Controller for Xbox One - Camo Series", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x0e6f, 0x02a7, "PDP Xbox One Controller", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x0e6f, 0x02a8, "PDP Xbox One Controller", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x0e6f, 0x02ab, "PDP Controller for Xbox One", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x0e6f, 0x02ad, "PDP Wired Controller for Xbox One - Stealth Series", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x0e6f, 0x02b3, "Afterglow Prismatic Wired Controller", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x0e6f, 0x02b8, "Afterglow Prismatic Wired Controller", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x0e6f, 0x0301, "Logic3 Controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0e6f, 0x0346, "Rock Candy Gamepad for Xbox One 2016", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x0e6f, 0x0401, "Logic3 Controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0e6f, 0x0413, "Afterglow AX.1 Gamepad for Xbox 360", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0e6f, 0x0501, "PDP Xbox 360 Controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0e6f, 0xf900, "PDP Afterglow AX.1", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0e8f, 0x0201, "SmartJoy Frag Xpad/PS2 adaptor", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0e8f, 0x3008, "Generic xbox control (dealextreme)", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0f0d, 0x000a, "Hori Co. DOA4 FightStick", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0f0d, 0x000c, "Hori PadEX Turbo", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x0f0d, 0x000d, "Hori Fighting Stick EX2", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x0f0d, 0x0016, "Hori Real Arcade Pro.EX", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x0f0d, 0x001b, "Hori Real Arcade Pro VX", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x0f0d, 0x0063, "Hori Real Arcade Pro Hayabusa (USA) Xbox One", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOXONE पूर्ण,
	अणु 0x0f0d, 0x0067, "HORIPAD ONE", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x0f0d, 0x0078, "Hori Real Arcade Pro V Kai Xbox One", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOXONE पूर्ण,
	अणु 0x0f30, 0x010b, "Philips Recoil", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0f30, 0x0202, "Joytech Advanced Controller", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0f30, 0x8888, "BigBen XBMiniPad Controller", 0, XTYPE_XBOX पूर्ण,
	अणु 0x102c, 0xff0c, "Joytech Wireless Advanced Controller", 0, XTYPE_XBOX पूर्ण,
	अणु 0x1038, 0x1430, "SteelSeries Stratus Duo", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1038, 0x1431, "SteelSeries Stratus Duo", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x11c9, 0x55f0, "Nacon GC-100XF", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1209, 0x2882, "Ardwiino Controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x12ab, 0x0004, "Honey Bee Xbox360 dancepad", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x12ab, 0x0301, "PDP AFTERGLOW AX.1", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x12ab, 0x0303, "Mortal Kombat Klassic FightStick", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x12ab, 0x8809, "Xbox DDR dancepad", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX पूर्ण,
	अणु 0x1430, 0x4748, "RedOctane Guitar Hero X-plorer", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1430, 0x8888, "TX6500+ Dance Pad (first generation)", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX पूर्ण,
	अणु 0x1430, 0xf801, "RedOctane Controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x146b, 0x0601, "BigBen Interactive XBOX 360 Controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1532, 0x0037, "Razer Sabertooth", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1532, 0x0a00, "Razer Atrox Arcade Stick", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOXONE पूर्ण,
	अणु 0x1532, 0x0a03, "Razer Wildcat", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x15e4, 0x3f00, "Power A Mini Pro Elite", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x15e4, 0x3f0a, "Xbox Airflo wired controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x15e4, 0x3f10, "Batarang Xbox 360 controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x162e, 0xbeef, "Joytech Neo-Se Take2", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1689, 0xfd00, "Razer Onza Tournament Edition", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1689, 0xfd01, "Razer Onza Classic Edition", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1689, 0xfe00, "Razer Sabertooth", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1949, 0x041a, "Amazon Game Controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0x0002, "Harmonix Rock Band Guitar", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0x0003, "Harmonix Rock Band Drumkit", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0x0130, "Ion Drum Rocker", MAP_DPAD_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf016, "Mad Catz Xbox 360 Controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf018, "Mad Catz Street Fighter IV SE Fighting Stick", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf019, "Mad Catz Brawlstick for Xbox 360", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf021, "Mad Cats Ghost Recon FS GamePad", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf023, "MLG Pro Circuit Controller (Xbox)", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf025, "Mad Catz Call Of Duty", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf027, "Mad Catz FPS Pro", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf028, "Street Fighter IV FightPad", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf02e, "Mad Catz Fightpad", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf030, "Mad Catz Xbox 360 MC2 MicroCon Racing Wheel", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf036, "Mad Catz MicroCon GamePad Pro", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf038, "Street Fighter IV FightStick TE", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf039, "Mad Catz MvC2 TE", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf03a, "Mad Catz SFxT Fightstick Pro", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf03d, "Street Fighter IV Arcade Stick TE - Chun Li", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf03e, "Mad Catz MLG FightStick TE", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf03f, "Mad Catz FightStick SoulCaliber", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf042, "Mad Catz FightStick TES+", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf080, "Mad Catz FightStick TE2", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf501, "HoriPad EX2 Turbo", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf502, "Hori Real Arcade Pro.VX SA", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf503, "Hori Fighting Stick VX", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf504, "Hori Real Arcade Pro. EX", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf505, "Hori Fighting Stick EX2B", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf506, "Hori Real Arcade Pro.EX Premium VLX", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf900, "Harmonix Xbox 360 Controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf901, "Gamestop Xbox 360 Controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf903, "Tron Xbox 360 controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf904, "PDP Versus Fighting Pad", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xf906, "MortalKombat FightStick", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xfa01, "MadCatz GamePad", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xfd00, "Razer Onza TE", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x1bad, 0xfd01, "Razer Onza", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x20d6, 0x2001, "BDA Xbox Series X Wired Controller", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x20d6, 0x2009, "PowerA Enhanced Wired Controller for Xbox Series X|S", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x20d6, 0x281f, "PowerA Wired Controller For Xbox 360", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x2e24, 0x0652, "Hyperkin Duke X-Box One pad", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x24c6, 0x5000, "Razer Atrox Arcade Stick", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x24c6, 0x5300, "PowerA MINI PROEX Controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x24c6, 0x5303, "Xbox Airflo wired controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x24c6, 0x530a, "Xbox 360 Pro EX Controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x24c6, 0x531a, "PowerA Pro Ex", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x24c6, 0x5397, "FUS1ON Tournament Controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x24c6, 0x541a, "PowerA Xbox One Mini Wired Controller", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x24c6, 0x542a, "Xbox ONE spectra", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x24c6, 0x543a, "PowerA Xbox One wired controller", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x24c6, 0x5500, "Hori XBOX 360 EX 2 with Turbo", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x24c6, 0x5501, "Hori Real Arcade Pro VX-SA", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x24c6, 0x5502, "Hori Fighting Stick VX Alt", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x24c6, 0x5503, "Hori Fighting Edge", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x24c6, 0x5506, "Hori SOULCALIBUR V Stick", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x24c6, 0x550d, "Hori GEM Xbox controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x24c6, 0x550e, "Hori Real Arcade Pro V Kai 360", MAP_TRIGGERS_TO_BUTTONS, XTYPE_XBOX360 पूर्ण,
	अणु 0x24c6, 0x551a, "PowerA FUSION Pro Controller", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x24c6, 0x561a, "PowerA FUSION Controller", 0, XTYPE_XBOXONE पूर्ण,
	अणु 0x24c6, 0x5b00, "ThrustMaster Ferrari 458 Racing Wheel", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x24c6, 0x5b02, "Thrustmaster, Inc. GPX Controller", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x24c6, 0x5b03, "Thrustmaster Ferrari 458 Racing Wheel", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x24c6, 0x5d04, "Razer Sabertooth", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x24c6, 0xfafe, "Rock Candy Gamepad for Xbox 360", 0, XTYPE_XBOX360 पूर्ण,
	अणु 0x3767, 0x0101, "Fanatec Speedster 3 Forceshock Wheel", 0, XTYPE_XBOX पूर्ण,
	अणु 0xffff, 0xffff, "Chinese-made Xbox Controller", 0, XTYPE_XBOX पूर्ण,
	अणु 0x0000, 0x0000, "Generic X-Box pad", 0, XTYPE_UNKNOWN पूर्ण
पूर्ण;

/* buttons shared with xbox and xbox360 */
अटल स्थिर चिन्हित लघु xpad_common_btn[] = अणु
	BTN_A, BTN_B, BTN_X, BTN_Y,			/* "analog" buttons */
	BTN_START, BTN_SELECT, BTN_THUMBL, BTN_THUMBR,	/* start/back/sticks */
	-1						/* terminating entry */
पूर्ण;

/* original xbox controllers only */
अटल स्थिर चिन्हित लघु xpad_btn[] = अणु
	BTN_C, BTN_Z,		/* "analog" buttons */
	-1			/* terminating entry */
पूर्ण;

/* used when dpad is mapped to buttons */
अटल स्थिर चिन्हित लघु xpad_btn_pad[] = अणु
	BTN_TRIGGER_HAPPY1, BTN_TRIGGER_HAPPY2,		/* d-pad left, right */
	BTN_TRIGGER_HAPPY3, BTN_TRIGGER_HAPPY4,		/* d-pad up, करोwn */
	-1				/* terminating entry */
पूर्ण;

/* used when triggers are mapped to buttons */
अटल स्थिर चिन्हित लघु xpad_btn_triggers[] = अणु
	BTN_TL2, BTN_TR2,		/* triggers left/right */
	-1
पूर्ण;

अटल स्थिर चिन्हित लघु xpad360_btn[] = अणु  /* buttons क्रम x360 controller */
	BTN_TL, BTN_TR,		/* Button LB/RB */
	BTN_MODE,		/* The big X button */
	-1
पूर्ण;

अटल स्थिर चिन्हित लघु xpad_असल[] = अणु
	ABS_X, ABS_Y,		/* left stick */
	ABS_RX, ABS_RY,		/* right stick */
	-1			/* terminating entry */
पूर्ण;

/* used when dpad is mapped to axes */
अटल स्थिर चिन्हित लघु xpad_असल_pad[] = अणु
	ABS_HAT0X, ABS_HAT0Y,	/* d-pad axes */
	-1			/* terminating entry */
पूर्ण;

/* used when triggers are mapped to axes */
अटल स्थिर चिन्हित लघु xpad_असल_triggers[] = अणु
	ABS_Z, ABS_RZ,		/* triggers left/right */
	-1
पूर्ण;

/*
 * Xbox 360 has a venकरोr-specअगरic class, so we cannot match it with only
 * USB_INTERFACE_INFO (also specअगरically refused by USB subप्रणाली), so we
 * match against venकरोr id as well. Wired Xbox 360 devices have protocol 1,
 * wireless controllers have protocol 129.
 */
#घोषणा XPAD_XBOX360_VENDOR_PROTOCOL(vend, pr) \
	.match_flags = USB_DEVICE_ID_MATCH_VENDOR | USB_DEVICE_ID_MATCH_INT_INFO, \
	.idVenकरोr = (vend), \
	.bInterfaceClass = USB_CLASS_VENDOR_SPEC, \
	.bInterfaceSubClass = 93, \
	.bInterfaceProtocol = (pr)
#घोषणा XPAD_XBOX360_VENDOR(vend) \
	अणु XPAD_XBOX360_VENDOR_PROTOCOL((vend), 1) पूर्ण, \
	अणु XPAD_XBOX360_VENDOR_PROTOCOL((vend), 129) पूर्ण

/* The Xbox One controller uses subclass 71 and protocol 208. */
#घोषणा XPAD_XBOXONE_VENDOR_PROTOCOL(vend, pr) \
	.match_flags = USB_DEVICE_ID_MATCH_VENDOR | USB_DEVICE_ID_MATCH_INT_INFO, \
	.idVenकरोr = (vend), \
	.bInterfaceClass = USB_CLASS_VENDOR_SPEC, \
	.bInterfaceSubClass = 71, \
	.bInterfaceProtocol = (pr)
#घोषणा XPAD_XBOXONE_VENDOR(vend) \
	अणु XPAD_XBOXONE_VENDOR_PROTOCOL((vend), 208) पूर्ण

अटल स्थिर काष्ठा usb_device_id xpad_table[] = अणु
	अणु USB_INTERFACE_INFO('X', 'B', 0) पूर्ण,	/* X-Box USB-IF not approved class */
	XPAD_XBOX360_VENDOR(0x0079),		/* GPD Win 2 Controller */
	XPAD_XBOX360_VENDOR(0x044f),		/* Thrusपंचांगaster X-Box 360 controllers */
	XPAD_XBOX360_VENDOR(0x045e),		/* Microsoft X-Box 360 controllers */
	XPAD_XBOXONE_VENDOR(0x045e),		/* Microsoft X-Box One controllers */
	XPAD_XBOX360_VENDOR(0x046d),		/* Logitech X-Box 360 style controllers */
	XPAD_XBOX360_VENDOR(0x056e),		/* Elecom JC-U3613M */
	XPAD_XBOX360_VENDOR(0x06a3),		/* Saitek P3600 */
	XPAD_XBOX360_VENDOR(0x0738),		/* Mad Catz X-Box 360 controllers */
	अणु USB_DEVICE(0x0738, 0x4540) पूर्ण,		/* Mad Catz Beat Pad */
	XPAD_XBOXONE_VENDOR(0x0738),		/* Mad Catz FightStick TE 2 */
	XPAD_XBOX360_VENDOR(0x07ff),		/* Mad Catz GamePad */
	XPAD_XBOX360_VENDOR(0x0e6f),		/* 0x0e6f X-Box 360 controllers */
	XPAD_XBOXONE_VENDOR(0x0e6f),		/* 0x0e6f X-Box One controllers */
	XPAD_XBOX360_VENDOR(0x0f0d),		/* Hori Controllers */
	XPAD_XBOXONE_VENDOR(0x0f0d),		/* Hori Controllers */
	XPAD_XBOX360_VENDOR(0x1038),		/* SteelSeries Controllers */
	XPAD_XBOX360_VENDOR(0x11c9),		/* Nacon GC100XF */
	XPAD_XBOX360_VENDOR(0x1209),		/* Ardwiino Controllers */
	XPAD_XBOX360_VENDOR(0x12ab),		/* X-Box 360 dance pads */
	XPAD_XBOX360_VENDOR(0x1430),		/* RedOctane X-Box 360 controllers */
	XPAD_XBOX360_VENDOR(0x146b),		/* BigBen Interactive Controllers */
	XPAD_XBOX360_VENDOR(0x1532),		/* Razer Sabertooth */
	XPAD_XBOXONE_VENDOR(0x1532),		/* Razer Wildcat */
	XPAD_XBOX360_VENDOR(0x15e4),		/* Numark X-Box 360 controllers */
	XPAD_XBOX360_VENDOR(0x162e),		/* Joytech X-Box 360 controllers */
	XPAD_XBOX360_VENDOR(0x1689),		/* Razer Onza */
	XPAD_XBOX360_VENDOR(0x1949),		/* Amazon controllers */
	XPAD_XBOX360_VENDOR(0x1bad),		/* Harminix Rock Band Guitar and Drums */
	XPAD_XBOX360_VENDOR(0x20d6),		/* PowerA Controllers */
	XPAD_XBOXONE_VENDOR(0x20d6),		/* PowerA Controllers */
	XPAD_XBOX360_VENDOR(0x24c6),		/* PowerA Controllers */
	XPAD_XBOXONE_VENDOR(0x24c6),		/* PowerA Controllers */
	XPAD_XBOXONE_VENDOR(0x2e24),		/* Hyperkin Duke X-Box One pad */
	XPAD_XBOX360_VENDOR(0x2f24),		/* GameSir Controllers */
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, xpad_table);

काष्ठा xboxone_init_packet अणु
	u16 idVenकरोr;
	u16 idProduct;
	स्थिर u8 *data;
	u8 len;
पूर्ण;

#घोषणा XBOXONE_INIT_PKT(_vid, _pid, _data)		\
	अणु						\
		.idVenकरोr	= (_vid),		\
		.idProduct	= (_pid),		\
		.data		= (_data),		\
		.len		= ARRAY_SIZE(_data),	\
	पूर्ण


/*
 * This packet is required क्रम all Xbox One pads with 2015
 * or later firmware installed (or present from the factory).
 */
अटल स्थिर u8 xboxone_fw2015_init[] = अणु
	0x05, 0x20, 0x00, 0x01, 0x00
पूर्ण;

/*
 * This packet is required क्रम Xbox One S (0x045e:0x02ea)
 * and Xbox One Elite Series 2 (0x045e:0x0b00) pads to
 * initialize the controller that was previously used in
 * Bluetooth mode.
 */
अटल स्थिर u8 xboxone_s_init[] = अणु
	0x05, 0x20, 0x00, 0x0f, 0x06
पूर्ण;

/*
 * This packet is required क्रम the Titanfall 2 Xbox One pads
 * (0x0e6f:0x0165) to finish initialization and क्रम Hori pads
 * (0x0f0d:0x0067) to make the analog sticks work.
 */
अटल स्थिर u8 xboxone_hori_init[] = अणु
	0x01, 0x20, 0x00, 0x09, 0x00, 0x04, 0x20, 0x3a,
	0x00, 0x00, 0x00, 0x80, 0x00
पूर्ण;

/*
 * This packet is required क्रम most (all?) of the PDP pads to start
 * sending input reports. These pads include: (0x0e6f:0x02ab),
 * (0x0e6f:0x02a4), (0x0e6f:0x02a6).
 */
अटल स्थिर u8 xboxone_pdp_init1[] = अणु
	0x0a, 0x20, 0x00, 0x03, 0x00, 0x01, 0x14
पूर्ण;

/*
 * This packet is required क्रम most (all?) of the PDP pads to start
 * sending input reports. These pads include: (0x0e6f:0x02ab),
 * (0x0e6f:0x02a4), (0x0e6f:0x02a6).
 */
अटल स्थिर u8 xboxone_pdp_init2[] = अणु
	0x06, 0x20, 0x00, 0x02, 0x01, 0x00
पूर्ण;

/*
 * A specअगरic rumble packet is required क्रम some PowerA pads to start
 * sending input reports. One of those pads is (0x24c6:0x543a).
 */
अटल स्थिर u8 xboxone_rumblebegin_init[] = अणु
	0x09, 0x00, 0x00, 0x09, 0x00, 0x0F, 0x00, 0x00,
	0x1D, 0x1D, 0xFF, 0x00, 0x00
पूर्ण;

/*
 * A rumble packet with zero FF पूर्णांकensity will immediately
 * terminate the rumbling required to init PowerA pads.
 * This should happen fast enough that the motors करोn't
 * spin up to enough speed to actually vibrate the gamepad.
 */
अटल स्थिर u8 xboxone_rumbleend_init[] = अणु
	0x09, 0x00, 0x00, 0x09, 0x00, 0x0F, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00
पूर्ण;

/*
 * This specअगरies the selection of init packets that a gamepad
 * will be sent on init *and* the order in which they will be
 * sent. The correct sequence number will be added when the
 * packet is going to be sent.
 */
अटल स्थिर काष्ठा xboxone_init_packet xboxone_init_packets[] = अणु
	XBOXONE_INIT_PKT(0x0e6f, 0x0165, xboxone_hori_init),
	XBOXONE_INIT_PKT(0x0f0d, 0x0067, xboxone_hori_init),
	XBOXONE_INIT_PKT(0x0000, 0x0000, xboxone_fw2015_init),
	XBOXONE_INIT_PKT(0x045e, 0x02ea, xboxone_s_init),
	XBOXONE_INIT_PKT(0x045e, 0x0b00, xboxone_s_init),
	XBOXONE_INIT_PKT(0x0e6f, 0x0000, xboxone_pdp_init1),
	XBOXONE_INIT_PKT(0x0e6f, 0x0000, xboxone_pdp_init2),
	XBOXONE_INIT_PKT(0x24c6, 0x541a, xboxone_rumblebegin_init),
	XBOXONE_INIT_PKT(0x24c6, 0x542a, xboxone_rumblebegin_init),
	XBOXONE_INIT_PKT(0x24c6, 0x543a, xboxone_rumblebegin_init),
	XBOXONE_INIT_PKT(0x24c6, 0x541a, xboxone_rumbleend_init),
	XBOXONE_INIT_PKT(0x24c6, 0x542a, xboxone_rumbleend_init),
	XBOXONE_INIT_PKT(0x24c6, 0x543a, xboxone_rumbleend_init),
पूर्ण;

काष्ठा xpad_output_packet अणु
	u8 data[XPAD_PKT_LEN];
	u8 len;
	bool pending;
पूर्ण;

#घोषणा XPAD_OUT_CMD_IDX	0
#घोषणा XPAD_OUT_FF_IDX		1
#घोषणा XPAD_OUT_LED_IDX	(1 + IS_ENABLED(CONFIG_JOYSTICK_XPAD_FF))
#घोषणा XPAD_NUM_OUT_PACKETS	(1 + \
				 IS_ENABLED(CONFIG_JOYSTICK_XPAD_FF) + \
				 IS_ENABLED(CONFIG_JOYSTICK_XPAD_LEDS))

काष्ठा usb_xpad अणु
	काष्ठा input_dev *dev;		/* input device पूर्णांकerface */
	काष्ठा input_dev __rcu *x360w_dev;
	काष्ठा usb_device *udev;	/* usb device */
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;	/* usb पूर्णांकerface */

	bool pad_present;
	bool input_created;

	काष्ठा urb *irq_in;		/* urb क्रम पूर्णांकerrupt in report */
	अचिन्हित अक्षर *idata;		/* input data */
	dma_addr_t idata_dma;

	काष्ठा urb *irq_out;		/* urb क्रम पूर्णांकerrupt out report */
	काष्ठा usb_anchor irq_out_anchor;
	bool irq_out_active;		/* we must not use an active URB */
	u8 odata_serial;		/* serial number क्रम xbox one protocol */
	अचिन्हित अक्षर *odata;		/* output data */
	dma_addr_t odata_dma;
	spinlock_t odata_lock;

	काष्ठा xpad_output_packet out_packets[XPAD_NUM_OUT_PACKETS];
	पूर्णांक last_out_packet;
	पूर्णांक init_seq;

#अगर defined(CONFIG_JOYSTICK_XPAD_LEDS)
	काष्ठा xpad_led *led;
#पूर्ण_अगर

	अक्षर phys[64];			/* physical device path */

	पूर्णांक mapping;			/* map d-pad to buttons or to axes */
	पूर्णांक xtype;			/* type of xbox device */
	पूर्णांक pad_nr;			/* the order x360 pads were attached */
	स्थिर अक्षर *name;		/* name of the device */
	काष्ठा work_काष्ठा work;	/* init/हटाओ device from callback */
पूर्ण;

अटल पूर्णांक xpad_init_input(काष्ठा usb_xpad *xpad);
अटल व्योम xpad_deinit_input(काष्ठा usb_xpad *xpad);
अटल व्योम xpaकरोne_ack_mode_report(काष्ठा usb_xpad *xpad, u8 seq_num);

/*
 *	xpad_process_packet
 *
 *	Completes a request by converting the data पूर्णांकo events क्रम the
 *	input subप्रणाली.
 *
 *	The used report descriptor was taken from ITO Takayukis website:
 *	 http://euc.jp/periphs/xbox-controller.ja.hपंचांगl
 */
अटल व्योम xpad_process_packet(काष्ठा usb_xpad *xpad, u16 cmd, अचिन्हित अक्षर *data)
अणु
	काष्ठा input_dev *dev = xpad->dev;

	अगर (!(xpad->mapping & MAP_STICKS_TO_शून्य)) अणु
		/* left stick */
		input_report_असल(dev, ABS_X,
				 (__s16) le16_to_cpup((__le16 *)(data + 12)));
		input_report_असल(dev, ABS_Y,
				 ~(__s16) le16_to_cpup((__le16 *)(data + 14)));

		/* right stick */
		input_report_असल(dev, ABS_RX,
				 (__s16) le16_to_cpup((__le16 *)(data + 16)));
		input_report_असल(dev, ABS_RY,
				 ~(__s16) le16_to_cpup((__le16 *)(data + 18)));
	पूर्ण

	/* triggers left/right */
	अगर (xpad->mapping & MAP_TRIGGERS_TO_BUTTONS) अणु
		input_report_key(dev, BTN_TL2, data[10]);
		input_report_key(dev, BTN_TR2, data[11]);
	पूर्ण अन्यथा अणु
		input_report_असल(dev, ABS_Z, data[10]);
		input_report_असल(dev, ABS_RZ, data[11]);
	पूर्ण

	/* digital pad */
	अगर (xpad->mapping & MAP_DPAD_TO_BUTTONS) अणु
		/* dpad as buttons (left, right, up, करोwn) */
		input_report_key(dev, BTN_TRIGGER_HAPPY1, data[2] & 0x04);
		input_report_key(dev, BTN_TRIGGER_HAPPY2, data[2] & 0x08);
		input_report_key(dev, BTN_TRIGGER_HAPPY3, data[2] & 0x01);
		input_report_key(dev, BTN_TRIGGER_HAPPY4, data[2] & 0x02);
	पूर्ण अन्यथा अणु
		input_report_असल(dev, ABS_HAT0X,
				 !!(data[2] & 0x08) - !!(data[2] & 0x04));
		input_report_असल(dev, ABS_HAT0Y,
				 !!(data[2] & 0x02) - !!(data[2] & 0x01));
	पूर्ण

	/* start/back buttons and stick press left/right */
	input_report_key(dev, BTN_START,  data[2] & 0x10);
	input_report_key(dev, BTN_SELECT, data[2] & 0x20);
	input_report_key(dev, BTN_THUMBL, data[2] & 0x40);
	input_report_key(dev, BTN_THUMBR, data[2] & 0x80);

	/* "analog" buttons A, B, X, Y */
	input_report_key(dev, BTN_A, data[4]);
	input_report_key(dev, BTN_B, data[5]);
	input_report_key(dev, BTN_X, data[6]);
	input_report_key(dev, BTN_Y, data[7]);

	/* "analog" buttons black, white */
	input_report_key(dev, BTN_C, data[8]);
	input_report_key(dev, BTN_Z, data[9]);

	input_sync(dev);
पूर्ण

/*
 *	xpad360_process_packet
 *
 *	Completes a request by converting the data पूर्णांकo events क्रम the
 *	input subप्रणाली. It is version क्रम xbox 360 controller
 *
 *	The used report descriptor was taken from:
 *		http://www.मुक्त60.org/wiki/Gamepad
 */

अटल व्योम xpad360_process_packet(काष्ठा usb_xpad *xpad, काष्ठा input_dev *dev,
				   u16 cmd, अचिन्हित अक्षर *data)
अणु
	/* valid pad data */
	अगर (data[0] != 0x00)
		वापस;

	/* digital pad */
	अगर (xpad->mapping & MAP_DPAD_TO_BUTTONS) अणु
		/* dpad as buttons (left, right, up, करोwn) */
		input_report_key(dev, BTN_TRIGGER_HAPPY1, data[2] & 0x04);
		input_report_key(dev, BTN_TRIGGER_HAPPY2, data[2] & 0x08);
		input_report_key(dev, BTN_TRIGGER_HAPPY3, data[2] & 0x01);
		input_report_key(dev, BTN_TRIGGER_HAPPY4, data[2] & 0x02);
	पूर्ण

	/*
	 * This should be a simple अन्यथा block. However historically
	 * xbox360w has mapped DPAD to buttons जबतक xbox360 did not. This
	 * made no sense, but now we can not just चयन back and have to
	 * support both behaviors.
	 */
	अगर (!(xpad->mapping & MAP_DPAD_TO_BUTTONS) ||
	    xpad->xtype == XTYPE_XBOX360W) अणु
		input_report_असल(dev, ABS_HAT0X,
				 !!(data[2] & 0x08) - !!(data[2] & 0x04));
		input_report_असल(dev, ABS_HAT0Y,
				 !!(data[2] & 0x02) - !!(data[2] & 0x01));
	पूर्ण

	/* start/back buttons */
	input_report_key(dev, BTN_START,  data[2] & 0x10);
	input_report_key(dev, BTN_SELECT, data[2] & 0x20);

	/* stick press left/right */
	input_report_key(dev, BTN_THUMBL, data[2] & 0x40);
	input_report_key(dev, BTN_THUMBR, data[2] & 0x80);

	/* buttons A,B,X,Y,TL,TR and MODE */
	input_report_key(dev, BTN_A,	data[3] & 0x10);
	input_report_key(dev, BTN_B,	data[3] & 0x20);
	input_report_key(dev, BTN_X,	data[3] & 0x40);
	input_report_key(dev, BTN_Y,	data[3] & 0x80);
	input_report_key(dev, BTN_TL,	data[3] & 0x01);
	input_report_key(dev, BTN_TR,	data[3] & 0x02);
	input_report_key(dev, BTN_MODE,	data[3] & 0x04);

	अगर (!(xpad->mapping & MAP_STICKS_TO_शून्य)) अणु
		/* left stick */
		input_report_असल(dev, ABS_X,
				 (__s16) le16_to_cpup((__le16 *)(data + 6)));
		input_report_असल(dev, ABS_Y,
				 ~(__s16) le16_to_cpup((__le16 *)(data + 8)));

		/* right stick */
		input_report_असल(dev, ABS_RX,
				 (__s16) le16_to_cpup((__le16 *)(data + 10)));
		input_report_असल(dev, ABS_RY,
				 ~(__s16) le16_to_cpup((__le16 *)(data + 12)));
	पूर्ण

	/* triggers left/right */
	अगर (xpad->mapping & MAP_TRIGGERS_TO_BUTTONS) अणु
		input_report_key(dev, BTN_TL2, data[4]);
		input_report_key(dev, BTN_TR2, data[5]);
	पूर्ण अन्यथा अणु
		input_report_असल(dev, ABS_Z, data[4]);
		input_report_असल(dev, ABS_RZ, data[5]);
	पूर्ण

	input_sync(dev);
पूर्ण

अटल व्योम xpad_presence_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा usb_xpad *xpad = container_of(work, काष्ठा usb_xpad, work);
	पूर्णांक error;

	अगर (xpad->pad_present) अणु
		error = xpad_init_input(xpad);
		अगर (error) अणु
			/* complain only, not much अन्यथा we can करो here */
			dev_err(&xpad->dev->dev,
				"unable to init device: %d\n", error);
		पूर्ण अन्यथा अणु
			rcu_assign_poपूर्णांकer(xpad->x360w_dev, xpad->dev);
		पूर्ण
	पूर्ण अन्यथा अणु
		RCU_INIT_POINTER(xpad->x360w_dev, शून्य);
		synchronize_rcu();
		/*
		 * Now that we are sure xpad360w_process_packet is not
		 * using input device we can get rid of it.
		 */
		xpad_deinit_input(xpad);
	पूर्ण
पूर्ण

/*
 * xpad360w_process_packet
 *
 * Completes a request by converting the data पूर्णांकo events क्रम the
 * input subप्रणाली. It is version क्रम xbox 360 wireless controller.
 *
 * Byte.Bit
 * 00.1 - Status change: The controller or headset has connected/disconnected
 *                       Bits 01.7 and 01.6 are valid
 * 01.7 - Controller present
 * 01.6 - Headset present
 * 01.1 - Pad state (Bytes 4+) valid
 *
 */
अटल व्योम xpad360w_process_packet(काष्ठा usb_xpad *xpad, u16 cmd, अचिन्हित अक्षर *data)
अणु
	काष्ठा input_dev *dev;
	bool present;

	/* Presence change */
	अगर (data[0] & 0x08) अणु
		present = (data[1] & 0x80) != 0;

		अगर (xpad->pad_present != present) अणु
			xpad->pad_present = present;
			schedule_work(&xpad->work);
		पूर्ण
	पूर्ण

	/* Valid pad data */
	अगर (data[1] != 0x1)
		वापस;

	rcu_पढ़ो_lock();
	dev = rcu_dereference(xpad->x360w_dev);
	अगर (dev)
		xpad360_process_packet(xpad, dev, cmd, &data[4]);
	rcu_पढ़ो_unlock();
पूर्ण

/*
 *	xpaकरोne_process_packet
 *
 *	Completes a request by converting the data पूर्णांकo events क्रम the
 *	input subप्रणाली. This version is क्रम the Xbox One controller.
 *
 *	The report क्रमmat was gleaned from
 *	https://github.com/kylelemons/xbox/blob/master/xbox.go
 */
अटल व्योम xpaकरोne_process_packet(काष्ठा usb_xpad *xpad, u16 cmd, अचिन्हित अक्षर *data)
अणु
	काष्ठा input_dev *dev = xpad->dev;

	/* the xbox button has its own special report */
	अगर (data[0] == 0X07) अणु
		/*
		 * The Xbox One S controller requires these reports to be
		 * acked otherwise it जारीs sending them क्रमever and
		 * won't report further mode button events.
		 */
		अगर (data[1] == 0x30)
			xpaकरोne_ack_mode_report(xpad, data[2]);

		input_report_key(dev, BTN_MODE, data[4] & 0x01);
		input_sync(dev);
		वापस;
	पूर्ण
	/* check invalid packet */
	अन्यथा अगर (data[0] != 0X20)
		वापस;

	/* menu/view buttons */
	input_report_key(dev, BTN_START,  data[4] & 0x04);
	input_report_key(dev, BTN_SELECT, data[4] & 0x08);

	/* buttons A,B,X,Y */
	input_report_key(dev, BTN_A,	data[4] & 0x10);
	input_report_key(dev, BTN_B,	data[4] & 0x20);
	input_report_key(dev, BTN_X,	data[4] & 0x40);
	input_report_key(dev, BTN_Y,	data[4] & 0x80);

	/* digital pad */
	अगर (xpad->mapping & MAP_DPAD_TO_BUTTONS) अणु
		/* dpad as buttons (left, right, up, करोwn) */
		input_report_key(dev, BTN_TRIGGER_HAPPY1, data[5] & 0x04);
		input_report_key(dev, BTN_TRIGGER_HAPPY2, data[5] & 0x08);
		input_report_key(dev, BTN_TRIGGER_HAPPY3, data[5] & 0x01);
		input_report_key(dev, BTN_TRIGGER_HAPPY4, data[5] & 0x02);
	पूर्ण अन्यथा अणु
		input_report_असल(dev, ABS_HAT0X,
				 !!(data[5] & 0x08) - !!(data[5] & 0x04));
		input_report_असल(dev, ABS_HAT0Y,
				 !!(data[5] & 0x02) - !!(data[5] & 0x01));
	पूर्ण

	/* TL/TR */
	input_report_key(dev, BTN_TL,	data[5] & 0x10);
	input_report_key(dev, BTN_TR,	data[5] & 0x20);

	/* stick press left/right */
	input_report_key(dev, BTN_THUMBL, data[5] & 0x40);
	input_report_key(dev, BTN_THUMBR, data[5] & 0x80);

	अगर (!(xpad->mapping & MAP_STICKS_TO_शून्य)) अणु
		/* left stick */
		input_report_असल(dev, ABS_X,
				 (__s16) le16_to_cpup((__le16 *)(data + 10)));
		input_report_असल(dev, ABS_Y,
				 ~(__s16) le16_to_cpup((__le16 *)(data + 12)));

		/* right stick */
		input_report_असल(dev, ABS_RX,
				 (__s16) le16_to_cpup((__le16 *)(data + 14)));
		input_report_असल(dev, ABS_RY,
				 ~(__s16) le16_to_cpup((__le16 *)(data + 16)));
	पूर्ण

	/* triggers left/right */
	अगर (xpad->mapping & MAP_TRIGGERS_TO_BUTTONS) अणु
		input_report_key(dev, BTN_TL2,
				 (__u16) le16_to_cpup((__le16 *)(data + 6)));
		input_report_key(dev, BTN_TR2,
				 (__u16) le16_to_cpup((__le16 *)(data + 8)));
	पूर्ण अन्यथा अणु
		input_report_असल(dev, ABS_Z,
				 (__u16) le16_to_cpup((__le16 *)(data + 6)));
		input_report_असल(dev, ABS_RZ,
				 (__u16) le16_to_cpup((__le16 *)(data + 8)));
	पूर्ण

	input_sync(dev);
पूर्ण

अटल व्योम xpad_irq_in(काष्ठा urb *urb)
अणु
	काष्ठा usb_xpad *xpad = urb->context;
	काष्ठा device *dev = &xpad->पूर्णांकf->dev;
	पूर्णांक retval, status;

	status = urb->status;

	चयन (status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_dbg(dev, "%s - urb shutting down with status: %d\n",
			__func__, status);
		वापस;
	शेष:
		dev_dbg(dev, "%s - nonzero urb status received: %d\n",
			__func__, status);
		जाओ निकास;
	पूर्ण

	चयन (xpad->xtype) अणु
	हाल XTYPE_XBOX360:
		xpad360_process_packet(xpad, xpad->dev, 0, xpad->idata);
		अवरोध;
	हाल XTYPE_XBOX360W:
		xpad360w_process_packet(xpad, 0, xpad->idata);
		अवरोध;
	हाल XTYPE_XBOXONE:
		xpaकरोne_process_packet(xpad, 0, xpad->idata);
		अवरोध;
	शेष:
		xpad_process_packet(xpad, 0, xpad->idata);
	पूर्ण

निकास:
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval)
		dev_err(dev, "%s - usb_submit_urb failed with result %d\n",
			__func__, retval);
पूर्ण

/* Callers must hold xpad->odata_lock spinlock */
अटल bool xpad_prepare_next_init_packet(काष्ठा usb_xpad *xpad)
अणु
	स्थिर काष्ठा xboxone_init_packet *init_packet;

	अगर (xpad->xtype != XTYPE_XBOXONE)
		वापस false;

	/* Perक्रमm initialization sequence क्रम Xbox One pads that require it */
	जबतक (xpad->init_seq < ARRAY_SIZE(xboxone_init_packets)) अणु
		init_packet = &xboxone_init_packets[xpad->init_seq++];

		अगर (init_packet->idVenकरोr != 0 &&
		    init_packet->idVenकरोr != xpad->dev->id.venकरोr)
			जारी;

		अगर (init_packet->idProduct != 0 &&
		    init_packet->idProduct != xpad->dev->id.product)
			जारी;

		/* This packet applies to our device, so prepare to send it */
		स_नकल(xpad->odata, init_packet->data, init_packet->len);
		xpad->irq_out->transfer_buffer_length = init_packet->len;

		/* Update packet with current sequence number */
		xpad->odata[2] = xpad->odata_serial++;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* Callers must hold xpad->odata_lock spinlock */
अटल bool xpad_prepare_next_out_packet(काष्ठा usb_xpad *xpad)
अणु
	काष्ठा xpad_output_packet *pkt, *packet = शून्य;
	पूर्णांक i;

	/* We may have init packets to send beक्रमe we can send user commands */
	अगर (xpad_prepare_next_init_packet(xpad))
		वापस true;

	क्रम (i = 0; i < XPAD_NUM_OUT_PACKETS; i++) अणु
		अगर (++xpad->last_out_packet >= XPAD_NUM_OUT_PACKETS)
			xpad->last_out_packet = 0;

		pkt = &xpad->out_packets[xpad->last_out_packet];
		अगर (pkt->pending) अणु
			dev_dbg(&xpad->पूर्णांकf->dev,
				"%s - found pending output packet %d\n",
				__func__, xpad->last_out_packet);
			packet = pkt;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (packet) अणु
		स_नकल(xpad->odata, packet->data, packet->len);
		xpad->irq_out->transfer_buffer_length = packet->len;
		packet->pending = false;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* Callers must hold xpad->odata_lock spinlock */
अटल पूर्णांक xpad_try_sending_next_out_packet(काष्ठा usb_xpad *xpad)
अणु
	पूर्णांक error;

	अगर (!xpad->irq_out_active && xpad_prepare_next_out_packet(xpad)) अणु
		usb_anchor_urb(xpad->irq_out, &xpad->irq_out_anchor);
		error = usb_submit_urb(xpad->irq_out, GFP_ATOMIC);
		अगर (error) अणु
			dev_err(&xpad->पूर्णांकf->dev,
				"%s - usb_submit_urb failed with result %d\n",
				__func__, error);
			usb_unanchor_urb(xpad->irq_out);
			वापस -EIO;
		पूर्ण

		xpad->irq_out_active = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xpad_irq_out(काष्ठा urb *urb)
अणु
	काष्ठा usb_xpad *xpad = urb->context;
	काष्ठा device *dev = &xpad->पूर्णांकf->dev;
	पूर्णांक status = urb->status;
	पूर्णांक error;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&xpad->odata_lock, flags);

	चयन (status) अणु
	हाल 0:
		/* success */
		xpad->irq_out_active = xpad_prepare_next_out_packet(xpad);
		अवरोध;

	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_dbg(dev, "%s - urb shutting down with status: %d\n",
			__func__, status);
		xpad->irq_out_active = false;
		अवरोध;

	शेष:
		dev_dbg(dev, "%s - nonzero urb status received: %d\n",
			__func__, status);
		अवरोध;
	पूर्ण

	अगर (xpad->irq_out_active) अणु
		usb_anchor_urb(urb, &xpad->irq_out_anchor);
		error = usb_submit_urb(urb, GFP_ATOMIC);
		अगर (error) अणु
			dev_err(dev,
				"%s - usb_submit_urb failed with result %d\n",
				__func__, error);
			usb_unanchor_urb(urb);
			xpad->irq_out_active = false;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&xpad->odata_lock, flags);
पूर्ण

अटल पूर्णांक xpad_init_output(काष्ठा usb_पूर्णांकerface *पूर्णांकf, काष्ठा usb_xpad *xpad,
			काष्ठा usb_endpoपूर्णांक_descriptor *ep_irq_out)
अणु
	पूर्णांक error;

	अगर (xpad->xtype == XTYPE_UNKNOWN)
		वापस 0;

	init_usb_anchor(&xpad->irq_out_anchor);

	xpad->odata = usb_alloc_coherent(xpad->udev, XPAD_PKT_LEN,
					 GFP_KERNEL, &xpad->odata_dma);
	अगर (!xpad->odata)
		वापस -ENOMEM;

	spin_lock_init(&xpad->odata_lock);

	xpad->irq_out = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!xpad->irq_out) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_coherent;
	पूर्ण

	usb_fill_पूर्णांक_urb(xpad->irq_out, xpad->udev,
			 usb_sndपूर्णांकpipe(xpad->udev, ep_irq_out->bEndpoपूर्णांकAddress),
			 xpad->odata, XPAD_PKT_LEN,
			 xpad_irq_out, xpad, ep_irq_out->bInterval);
	xpad->irq_out->transfer_dma = xpad->odata_dma;
	xpad->irq_out->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	वापस 0;

err_मुक्त_coherent:
	usb_मुक्त_coherent(xpad->udev, XPAD_PKT_LEN, xpad->odata, xpad->odata_dma);
	वापस error;
पूर्ण

अटल व्योम xpad_stop_output(काष्ठा usb_xpad *xpad)
अणु
	अगर (xpad->xtype != XTYPE_UNKNOWN) अणु
		अगर (!usb_रुको_anchor_empty_समयout(&xpad->irq_out_anchor,
						   5000)) अणु
			dev_warn(&xpad->पूर्णांकf->dev,
				 "timed out waiting for output URB to complete, killing\n");
			usb_समाप्त_anchored_urbs(&xpad->irq_out_anchor);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम xpad_deinit_output(काष्ठा usb_xpad *xpad)
अणु
	अगर (xpad->xtype != XTYPE_UNKNOWN) अणु
		usb_मुक्त_urb(xpad->irq_out);
		usb_मुक्त_coherent(xpad->udev, XPAD_PKT_LEN,
				xpad->odata, xpad->odata_dma);
	पूर्ण
पूर्ण

अटल पूर्णांक xpad_inquiry_pad_presence(काष्ठा usb_xpad *xpad)
अणु
	काष्ठा xpad_output_packet *packet =
			&xpad->out_packets[XPAD_OUT_CMD_IDX];
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	spin_lock_irqsave(&xpad->odata_lock, flags);

	packet->data[0] = 0x08;
	packet->data[1] = 0x00;
	packet->data[2] = 0x0F;
	packet->data[3] = 0xC0;
	packet->data[4] = 0x00;
	packet->data[5] = 0x00;
	packet->data[6] = 0x00;
	packet->data[7] = 0x00;
	packet->data[8] = 0x00;
	packet->data[9] = 0x00;
	packet->data[10] = 0x00;
	packet->data[11] = 0x00;
	packet->len = 12;
	packet->pending = true;

	/* Reset the sequence so we send out presence first */
	xpad->last_out_packet = -1;
	retval = xpad_try_sending_next_out_packet(xpad);

	spin_unlock_irqrestore(&xpad->odata_lock, flags);

	वापस retval;
पूर्ण

अटल पूर्णांक xpad_start_xbox_one(काष्ठा usb_xpad *xpad)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	spin_lock_irqsave(&xpad->odata_lock, flags);

	/*
	 * Begin the init sequence by attempting to send a packet.
	 * We will cycle through the init packet sequence beक्रमe
	 * sending any packets from the output ring.
	 */
	xpad->init_seq = 0;
	retval = xpad_try_sending_next_out_packet(xpad);

	spin_unlock_irqrestore(&xpad->odata_lock, flags);

	वापस retval;
पूर्ण

अटल व्योम xpaकरोne_ack_mode_report(काष्ठा usb_xpad *xpad, u8 seq_num)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा xpad_output_packet *packet =
			&xpad->out_packets[XPAD_OUT_CMD_IDX];
	अटल स्थिर u8 mode_report_ack[] = अणु
		0x01, 0x20, 0x00, 0x09, 0x00, 0x07, 0x20, 0x02,
		0x00, 0x00, 0x00, 0x00, 0x00
	पूर्ण;

	spin_lock_irqsave(&xpad->odata_lock, flags);

	packet->len = माप(mode_report_ack);
	स_नकल(packet->data, mode_report_ack, packet->len);
	packet->data[2] = seq_num;
	packet->pending = true;

	/* Reset the sequence so we send out the ack now */
	xpad->last_out_packet = -1;
	xpad_try_sending_next_out_packet(xpad);

	spin_unlock_irqrestore(&xpad->odata_lock, flags);
पूर्ण

#अगर_घोषित CONFIG_JOYSTICK_XPAD_FF
अटल पूर्णांक xpad_play_effect(काष्ठा input_dev *dev, व्योम *data, काष्ठा ff_effect *effect)
अणु
	काष्ठा usb_xpad *xpad = input_get_drvdata(dev);
	काष्ठा xpad_output_packet *packet = &xpad->out_packets[XPAD_OUT_FF_IDX];
	__u16 strong;
	__u16 weak;
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	अगर (effect->type != FF_RUMBLE)
		वापस 0;

	strong = effect->u.rumble.strong_magnitude;
	weak = effect->u.rumble.weak_magnitude;

	spin_lock_irqsave(&xpad->odata_lock, flags);

	चयन (xpad->xtype) अणु
	हाल XTYPE_XBOX:
		packet->data[0] = 0x00;
		packet->data[1] = 0x06;
		packet->data[2] = 0x00;
		packet->data[3] = strong / 256;	/* left actuator */
		packet->data[4] = 0x00;
		packet->data[5] = weak / 256;	/* right actuator */
		packet->len = 6;
		packet->pending = true;
		अवरोध;

	हाल XTYPE_XBOX360:
		packet->data[0] = 0x00;
		packet->data[1] = 0x08;
		packet->data[2] = 0x00;
		packet->data[3] = strong / 256;  /* left actuator? */
		packet->data[4] = weak / 256;	/* right actuator? */
		packet->data[5] = 0x00;
		packet->data[6] = 0x00;
		packet->data[7] = 0x00;
		packet->len = 8;
		packet->pending = true;
		अवरोध;

	हाल XTYPE_XBOX360W:
		packet->data[0] = 0x00;
		packet->data[1] = 0x01;
		packet->data[2] = 0x0F;
		packet->data[3] = 0xC0;
		packet->data[4] = 0x00;
		packet->data[5] = strong / 256;
		packet->data[6] = weak / 256;
		packet->data[7] = 0x00;
		packet->data[8] = 0x00;
		packet->data[9] = 0x00;
		packet->data[10] = 0x00;
		packet->data[11] = 0x00;
		packet->len = 12;
		packet->pending = true;
		अवरोध;

	हाल XTYPE_XBOXONE:
		packet->data[0] = 0x09; /* activate rumble */
		packet->data[1] = 0x00;
		packet->data[2] = xpad->odata_serial++;
		packet->data[3] = 0x09;
		packet->data[4] = 0x00;
		packet->data[5] = 0x0F;
		packet->data[6] = 0x00;
		packet->data[7] = 0x00;
		packet->data[8] = strong / 512;	/* left actuator */
		packet->data[9] = weak / 512;	/* right actuator */
		packet->data[10] = 0xFF; /* on period */
		packet->data[11] = 0x00; /* off period */
		packet->data[12] = 0xFF; /* repeat count */
		packet->len = 13;
		packet->pending = true;
		अवरोध;

	शेष:
		dev_dbg(&xpad->dev->dev,
			"%s - rumble command sent to unsupported xpad type: %d\n",
			__func__, xpad->xtype);
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	retval = xpad_try_sending_next_out_packet(xpad);

out:
	spin_unlock_irqrestore(&xpad->odata_lock, flags);
	वापस retval;
पूर्ण

अटल पूर्णांक xpad_init_ff(काष्ठा usb_xpad *xpad)
अणु
	अगर (xpad->xtype == XTYPE_UNKNOWN)
		वापस 0;

	input_set_capability(xpad->dev, EV_FF, FF_RUMBLE);

	वापस input_ff_create_memless(xpad->dev, शून्य, xpad_play_effect);
पूर्ण

#अन्यथा
अटल पूर्णांक xpad_init_ff(काष्ठा usb_xpad *xpad) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_JOYSTICK_XPAD_LEDS)
#समावेश <linux/leds.h>
#समावेश <linux/idr.h>

अटल DEFINE_IDA(xpad_pad_seq);

काष्ठा xpad_led अणु
	अक्षर name[16];
	काष्ठा led_classdev led_cdev;
	काष्ठा usb_xpad *xpad;
पूर्ण;

/*
 * set the LEDs on Xbox360 / Wireless Controllers
 * @param command
 *  0: off
 *  1: all blink, then previous setting
 *  2: 1/top-left blink, then on
 *  3: 2/top-right blink, then on
 *  4: 3/bottom-left blink, then on
 *  5: 4/bottom-right blink, then on
 *  6: 1/top-left on
 *  7: 2/top-right on
 *  8: 3/bottom-left on
 *  9: 4/bottom-right on
 * 10: rotate
 * 11: blink, based on previous setting
 * 12: slow blink, based on previous setting
 * 13: rotate with two lights
 * 14: persistent slow all blink
 * 15: blink once, then previous setting
 */
अटल व्योम xpad_send_led_command(काष्ठा usb_xpad *xpad, पूर्णांक command)
अणु
	काष्ठा xpad_output_packet *packet =
			&xpad->out_packets[XPAD_OUT_LED_IDX];
	अचिन्हित दीर्घ flags;

	command %= 16;

	spin_lock_irqsave(&xpad->odata_lock, flags);

	चयन (xpad->xtype) अणु
	हाल XTYPE_XBOX360:
		packet->data[0] = 0x01;
		packet->data[1] = 0x03;
		packet->data[2] = command;
		packet->len = 3;
		packet->pending = true;
		अवरोध;

	हाल XTYPE_XBOX360W:
		packet->data[0] = 0x00;
		packet->data[1] = 0x00;
		packet->data[2] = 0x08;
		packet->data[3] = 0x40 + command;
		packet->data[4] = 0x00;
		packet->data[5] = 0x00;
		packet->data[6] = 0x00;
		packet->data[7] = 0x00;
		packet->data[8] = 0x00;
		packet->data[9] = 0x00;
		packet->data[10] = 0x00;
		packet->data[11] = 0x00;
		packet->len = 12;
		packet->pending = true;
		अवरोध;
	पूर्ण

	xpad_try_sending_next_out_packet(xpad);

	spin_unlock_irqrestore(&xpad->odata_lock, flags);
पूर्ण

/*
 * Light up the segment corresponding to the pad number on
 * Xbox 360 Controllers.
 */
अटल व्योम xpad_identअगरy_controller(काष्ठा usb_xpad *xpad)
अणु
	led_set_brightness(&xpad->led->led_cdev, (xpad->pad_nr % 4) + 2);
पूर्ण

अटल व्योम xpad_led_set(काष्ठा led_classdev *led_cdev,
			 क्रमागत led_brightness value)
अणु
	काष्ठा xpad_led *xpad_led = container_of(led_cdev,
						 काष्ठा xpad_led, led_cdev);

	xpad_send_led_command(xpad_led->xpad, value);
पूर्ण

अटल पूर्णांक xpad_led_probe(काष्ठा usb_xpad *xpad)
अणु
	काष्ठा xpad_led *led;
	काष्ठा led_classdev *led_cdev;
	पूर्णांक error;

	अगर (xpad->xtype != XTYPE_XBOX360 && xpad->xtype != XTYPE_XBOX360W)
		वापस 0;

	xpad->led = led = kzalloc(माप(काष्ठा xpad_led), GFP_KERNEL);
	अगर (!led)
		वापस -ENOMEM;

	xpad->pad_nr = ida_simple_get(&xpad_pad_seq, 0, 0, GFP_KERNEL);
	अगर (xpad->pad_nr < 0) अणु
		error = xpad->pad_nr;
		जाओ err_मुक्त_mem;
	पूर्ण

	snम_लिखो(led->name, माप(led->name), "xpad%d", xpad->pad_nr);
	led->xpad = xpad;

	led_cdev = &led->led_cdev;
	led_cdev->name = led->name;
	led_cdev->brightness_set = xpad_led_set;
	led_cdev->flags = LED_CORE_SUSPENDRESUME;

	error = led_classdev_रेजिस्टर(&xpad->udev->dev, led_cdev);
	अगर (error)
		जाओ err_मुक्त_id;

	xpad_identअगरy_controller(xpad);

	वापस 0;

err_मुक्त_id:
	ida_simple_हटाओ(&xpad_pad_seq, xpad->pad_nr);
err_मुक्त_mem:
	kमुक्त(led);
	xpad->led = शून्य;
	वापस error;
पूर्ण

अटल व्योम xpad_led_disconnect(काष्ठा usb_xpad *xpad)
अणु
	काष्ठा xpad_led *xpad_led = xpad->led;

	अगर (xpad_led) अणु
		led_classdev_unरेजिस्टर(&xpad_led->led_cdev);
		ida_simple_हटाओ(&xpad_pad_seq, xpad->pad_nr);
		kमुक्त(xpad_led);
	पूर्ण
पूर्ण
#अन्यथा
अटल पूर्णांक xpad_led_probe(काष्ठा usb_xpad *xpad) अणु वापस 0; पूर्ण
अटल व्योम xpad_led_disconnect(काष्ठा usb_xpad *xpad) अणु पूर्ण
#पूर्ण_अगर

अटल पूर्णांक xpad_start_input(काष्ठा usb_xpad *xpad)
अणु
	पूर्णांक error;

	अगर (usb_submit_urb(xpad->irq_in, GFP_KERNEL))
		वापस -EIO;

	अगर (xpad->xtype == XTYPE_XBOXONE) अणु
		error = xpad_start_xbox_one(xpad);
		अगर (error) अणु
			usb_समाप्त_urb(xpad->irq_in);
			वापस error;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xpad_stop_input(काष्ठा usb_xpad *xpad)
अणु
	usb_समाप्त_urb(xpad->irq_in);
पूर्ण

अटल व्योम xpad360w_घातeroff_controller(काष्ठा usb_xpad *xpad)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा xpad_output_packet *packet =
			&xpad->out_packets[XPAD_OUT_CMD_IDX];

	spin_lock_irqsave(&xpad->odata_lock, flags);

	packet->data[0] = 0x00;
	packet->data[1] = 0x00;
	packet->data[2] = 0x08;
	packet->data[3] = 0xC0;
	packet->data[4] = 0x00;
	packet->data[5] = 0x00;
	packet->data[6] = 0x00;
	packet->data[7] = 0x00;
	packet->data[8] = 0x00;
	packet->data[9] = 0x00;
	packet->data[10] = 0x00;
	packet->data[11] = 0x00;
	packet->len = 12;
	packet->pending = true;

	/* Reset the sequence so we send out घातeroff now */
	xpad->last_out_packet = -1;
	xpad_try_sending_next_out_packet(xpad);

	spin_unlock_irqrestore(&xpad->odata_lock, flags);
पूर्ण

अटल पूर्णांक xpad360w_start_input(काष्ठा usb_xpad *xpad)
अणु
	पूर्णांक error;

	error = usb_submit_urb(xpad->irq_in, GFP_KERNEL);
	अगर (error)
		वापस -EIO;

	/*
	 * Send presence packet.
	 * This will क्रमce the controller to resend connection packets.
	 * This is useful in the हाल we activate the module after the
	 * adapter has been plugged in, as it won't स्वतःmatically
	 * send us info about the controllers.
	 */
	error = xpad_inquiry_pad_presence(xpad);
	अगर (error) अणु
		usb_समाप्त_urb(xpad->irq_in);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xpad360w_stop_input(काष्ठा usb_xpad *xpad)
अणु
	usb_समाप्त_urb(xpad->irq_in);

	/* Make sure we are करोne with presence work अगर it was scheduled */
	flush_work(&xpad->work);
पूर्ण

अटल पूर्णांक xpad_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा usb_xpad *xpad = input_get_drvdata(dev);

	वापस xpad_start_input(xpad);
पूर्ण

अटल व्योम xpad_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा usb_xpad *xpad = input_get_drvdata(dev);

	xpad_stop_input(xpad);
पूर्ण

अटल व्योम xpad_set_up_असल(काष्ठा input_dev *input_dev, चिन्हित लघु असल)
अणु
	काष्ठा usb_xpad *xpad = input_get_drvdata(input_dev);

	चयन (असल) अणु
	हाल ABS_X:
	हाल ABS_Y:
	हाल ABS_RX:
	हाल ABS_RY:	/* the two sticks */
		input_set_असल_params(input_dev, असल, -32768, 32767, 16, 128);
		अवरोध;
	हाल ABS_Z:
	हाल ABS_RZ:	/* the triggers (अगर mapped to axes) */
		अगर (xpad->xtype == XTYPE_XBOXONE)
			input_set_असल_params(input_dev, असल, 0, 1023, 0, 0);
		अन्यथा
			input_set_असल_params(input_dev, असल, 0, 255, 0, 0);
		अवरोध;
	हाल ABS_HAT0X:
	हाल ABS_HAT0Y:	/* the d-pad (only अगर dpad is mapped to axes */
		input_set_असल_params(input_dev, असल, -1, 1, 0, 0);
		अवरोध;
	शेष:
		input_set_असल_params(input_dev, असल, 0, 0, 0, 0);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम xpad_deinit_input(काष्ठा usb_xpad *xpad)
अणु
	अगर (xpad->input_created) अणु
		xpad->input_created = false;
		xpad_led_disconnect(xpad);
		input_unरेजिस्टर_device(xpad->dev);
	पूर्ण
पूर्ण

अटल पूर्णांक xpad_init_input(काष्ठा usb_xpad *xpad)
अणु
	काष्ठा input_dev *input_dev;
	पूर्णांक i, error;

	input_dev = input_allocate_device();
	अगर (!input_dev)
		वापस -ENOMEM;

	xpad->dev = input_dev;
	input_dev->name = xpad->name;
	input_dev->phys = xpad->phys;
	usb_to_input_id(xpad->udev, &input_dev->id);

	अगर (xpad->xtype == XTYPE_XBOX360W) अणु
		/* x360w controllers and the receiver have dअगरferent ids */
		input_dev->id.product = 0x02a1;
	पूर्ण

	input_dev->dev.parent = &xpad->पूर्णांकf->dev;

	input_set_drvdata(input_dev, xpad);

	अगर (xpad->xtype != XTYPE_XBOX360W) अणु
		input_dev->खोलो = xpad_खोलो;
		input_dev->बंद = xpad_बंद;
	पूर्ण

	अगर (!(xpad->mapping & MAP_STICKS_TO_शून्य)) अणु
		/* set up axes */
		क्रम (i = 0; xpad_असल[i] >= 0; i++)
			xpad_set_up_असल(input_dev, xpad_असल[i]);
	पूर्ण

	/* set up standard buttons */
	क्रम (i = 0; xpad_common_btn[i] >= 0; i++)
		input_set_capability(input_dev, EV_KEY, xpad_common_btn[i]);

	/* set up model-specअगरic ones */
	अगर (xpad->xtype == XTYPE_XBOX360 || xpad->xtype == XTYPE_XBOX360W ||
	    xpad->xtype == XTYPE_XBOXONE) अणु
		क्रम (i = 0; xpad360_btn[i] >= 0; i++)
			input_set_capability(input_dev, EV_KEY, xpad360_btn[i]);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; xpad_btn[i] >= 0; i++)
			input_set_capability(input_dev, EV_KEY, xpad_btn[i]);
	पूर्ण

	अगर (xpad->mapping & MAP_DPAD_TO_BUTTONS) अणु
		क्रम (i = 0; xpad_btn_pad[i] >= 0; i++)
			input_set_capability(input_dev, EV_KEY,
					     xpad_btn_pad[i]);
	पूर्ण

	/*
	 * This should be a simple अन्यथा block. However historically
	 * xbox360w has mapped DPAD to buttons जबतक xbox360 did not. This
	 * made no sense, but now we can not just चयन back and have to
	 * support both behaviors.
	 */
	अगर (!(xpad->mapping & MAP_DPAD_TO_BUTTONS) ||
	    xpad->xtype == XTYPE_XBOX360W) अणु
		क्रम (i = 0; xpad_असल_pad[i] >= 0; i++)
			xpad_set_up_असल(input_dev, xpad_असल_pad[i]);
	पूर्ण

	अगर (xpad->mapping & MAP_TRIGGERS_TO_BUTTONS) अणु
		क्रम (i = 0; xpad_btn_triggers[i] >= 0; i++)
			input_set_capability(input_dev, EV_KEY,
					     xpad_btn_triggers[i]);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; xpad_असल_triggers[i] >= 0; i++)
			xpad_set_up_असल(input_dev, xpad_असल_triggers[i]);
	पूर्ण

	error = xpad_init_ff(xpad);
	अगर (error)
		जाओ err_मुक्त_input;

	error = xpad_led_probe(xpad);
	अगर (error)
		जाओ err_destroy_ff;

	error = input_रेजिस्टर_device(xpad->dev);
	अगर (error)
		जाओ err_disconnect_led;

	xpad->input_created = true;
	वापस 0;

err_disconnect_led:
	xpad_led_disconnect(xpad);
err_destroy_ff:
	input_ff_destroy(input_dev);
err_मुक्त_input:
	input_मुक्त_device(input_dev);
	वापस error;
पूर्ण

अटल पूर्णांक xpad_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_xpad *xpad;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_irq_in, *ep_irq_out;
	पूर्णांक i, error;

	अगर (पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs != 2)
		वापस -ENODEV;

	क्रम (i = 0; xpad_device[i].idVenकरोr; i++) अणु
		अगर ((le16_to_cpu(udev->descriptor.idVenकरोr) == xpad_device[i].idVenकरोr) &&
		    (le16_to_cpu(udev->descriptor.idProduct) == xpad_device[i].idProduct))
			अवरोध;
	पूर्ण

	xpad = kzalloc(माप(काष्ठा usb_xpad), GFP_KERNEL);
	अगर (!xpad)
		वापस -ENOMEM;

	usb_make_path(udev, xpad->phys, माप(xpad->phys));
	strlcat(xpad->phys, "/input0", माप(xpad->phys));

	xpad->idata = usb_alloc_coherent(udev, XPAD_PKT_LEN,
					 GFP_KERNEL, &xpad->idata_dma);
	अगर (!xpad->idata) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	xpad->irq_in = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!xpad->irq_in) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_idata;
	पूर्ण

	xpad->udev = udev;
	xpad->पूर्णांकf = पूर्णांकf;
	xpad->mapping = xpad_device[i].mapping;
	xpad->xtype = xpad_device[i].xtype;
	xpad->name = xpad_device[i].name;
	INIT_WORK(&xpad->work, xpad_presence_work);

	अगर (xpad->xtype == XTYPE_UNKNOWN) अणु
		अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceClass == USB_CLASS_VENDOR_SPEC) अणु
			अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol == 129)
				xpad->xtype = XTYPE_XBOX360W;
			अन्यथा अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol == 208)
				xpad->xtype = XTYPE_XBOXONE;
			अन्यथा
				xpad->xtype = XTYPE_XBOX360;
		पूर्ण अन्यथा अणु
			xpad->xtype = XTYPE_XBOX;
		पूर्ण

		अगर (dpad_to_buttons)
			xpad->mapping |= MAP_DPAD_TO_BUTTONS;
		अगर (triggers_to_buttons)
			xpad->mapping |= MAP_TRIGGERS_TO_BUTTONS;
		अगर (sticks_to_null)
			xpad->mapping |= MAP_STICKS_TO_शून्य;
	पूर्ण

	अगर (xpad->xtype == XTYPE_XBOXONE &&
	    पूर्णांकf->cur_altsetting->desc.bInterfaceNumber != 0) अणु
		/*
		 * The Xbox One controller lists three पूर्णांकerfaces all with the
		 * same पूर्णांकerface class, subclass and protocol. Dअगरferentiate by
		 * पूर्णांकerface number.
		 */
		error = -ENODEV;
		जाओ err_मुक्त_in_urb;
	पूर्ण

	ep_irq_in = ep_irq_out = शून्य;

	क्रम (i = 0; i < 2; i++) अणु
		काष्ठा usb_endpoपूर्णांक_descriptor *ep =
				&पूर्णांकf->cur_altsetting->endpoपूर्णांक[i].desc;

		अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(ep)) अणु
			अगर (usb_endpoपूर्णांक_dir_in(ep))
				ep_irq_in = ep;
			अन्यथा
				ep_irq_out = ep;
		पूर्ण
	पूर्ण

	अगर (!ep_irq_in || !ep_irq_out) अणु
		error = -ENODEV;
		जाओ err_मुक्त_in_urb;
	पूर्ण

	error = xpad_init_output(पूर्णांकf, xpad, ep_irq_out);
	अगर (error)
		जाओ err_मुक्त_in_urb;

	usb_fill_पूर्णांक_urb(xpad->irq_in, udev,
			 usb_rcvपूर्णांकpipe(udev, ep_irq_in->bEndpoपूर्णांकAddress),
			 xpad->idata, XPAD_PKT_LEN, xpad_irq_in,
			 xpad, ep_irq_in->bInterval);
	xpad->irq_in->transfer_dma = xpad->idata_dma;
	xpad->irq_in->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	usb_set_पूर्णांकfdata(पूर्णांकf, xpad);

	अगर (xpad->xtype == XTYPE_XBOX360W) अणु
		/*
		 * Submit the पूर्णांक URB immediately rather than रुकोing क्रम खोलो
		 * because we get status messages from the device whether
		 * or not any controllers are attached.  In fact, it's
		 * exactly the message that a controller has arrived that
		 * we're रुकोing क्रम.
		 */
		error = xpad360w_start_input(xpad);
		अगर (error)
			जाओ err_deinit_output;
		/*
		 * Wireless controllers require RESET_RESUME to work properly
		 * after suspend. Ideally this quirk should be in usb core
		 * quirk list, but we have too many venकरोrs producing these
		 * controllers and we'd need to मुख्यtain 2 identical lists
		 * here in this driver and in usb core.
		 */
		udev->quirks |= USB_QUIRK_RESET_RESUME;
	पूर्ण अन्यथा अणु
		error = xpad_init_input(xpad);
		अगर (error)
			जाओ err_deinit_output;
	पूर्ण
	वापस 0;

err_deinit_output:
	xpad_deinit_output(xpad);
err_मुक्त_in_urb:
	usb_मुक्त_urb(xpad->irq_in);
err_मुक्त_idata:
	usb_मुक्त_coherent(udev, XPAD_PKT_LEN, xpad->idata, xpad->idata_dma);
err_मुक्त_mem:
	kमुक्त(xpad);
	वापस error;
पूर्ण

अटल व्योम xpad_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_xpad *xpad = usb_get_पूर्णांकfdata(पूर्णांकf);

	अगर (xpad->xtype == XTYPE_XBOX360W)
		xpad360w_stop_input(xpad);

	xpad_deinit_input(xpad);

	/*
	 * Now that both input device and LED device are gone we can
	 * stop output URB.
	 */
	xpad_stop_output(xpad);

	xpad_deinit_output(xpad);

	usb_मुक्त_urb(xpad->irq_in);
	usb_मुक्त_coherent(xpad->udev, XPAD_PKT_LEN,
			xpad->idata, xpad->idata_dma);

	kमुक्त(xpad);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
पूर्ण

अटल पूर्णांक xpad_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा usb_xpad *xpad = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा input_dev *input = xpad->dev;

	अगर (xpad->xtype == XTYPE_XBOX360W) अणु
		/*
		 * Wireless controllers always listen to input so
		 * they are notअगरied when controller shows up
		 * or goes away.
		 */
		xpad360w_stop_input(xpad);

		/*
		 * The wireless adapter is going off now, so the
		 * gamepads are going to become disconnected.
		 * Unless explicitly disabled, घातer them करोwn
		 * so they करोn't just sit there flashing.
		 */
		अगर (स्वतः_घातeroff && xpad->pad_present)
			xpad360w_घातeroff_controller(xpad);
	पूर्ण अन्यथा अणु
		mutex_lock(&input->mutex);
		अगर (input_device_enabled(input))
			xpad_stop_input(xpad);
		mutex_unlock(&input->mutex);
	पूर्ण

	xpad_stop_output(xpad);

	वापस 0;
पूर्ण

अटल पूर्णांक xpad_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_xpad *xpad = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा input_dev *input = xpad->dev;
	पूर्णांक retval = 0;

	अगर (xpad->xtype == XTYPE_XBOX360W) अणु
		retval = xpad360w_start_input(xpad);
	पूर्ण अन्यथा अणु
		mutex_lock(&input->mutex);
		अगर (input_device_enabled(input)) अणु
			retval = xpad_start_input(xpad);
		पूर्ण अन्यथा अगर (xpad->xtype == XTYPE_XBOXONE) अणु
			/*
			 * Even अगर there are no users, we'll send Xbox One pads
			 * the startup sequence so they करोn't sit there and
			 * blink until somebody खोलोs the input device again.
			 */
			retval = xpad_start_xbox_one(xpad);
		पूर्ण
		mutex_unlock(&input->mutex);
	पूर्ण

	वापस retval;
पूर्ण

अटल काष्ठा usb_driver xpad_driver = अणु
	.name		= "xpad",
	.probe		= xpad_probe,
	.disconnect	= xpad_disconnect,
	.suspend	= xpad_suspend,
	.resume		= xpad_resume,
	.reset_resume	= xpad_resume,
	.id_table	= xpad_table,
पूर्ण;

module_usb_driver(xpad_driver);

MODULE_AUTHOR("Marko Friedemann <mfr@bmx-chemnitz.de>");
MODULE_DESCRIPTION("X-Box pad driver");
MODULE_LICENSE("GPL");
