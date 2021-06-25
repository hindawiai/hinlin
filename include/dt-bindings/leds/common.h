<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This header provides macros क्रम the common LEDs device tree bindings.
 *
 * Copyright (C) 2015, Samsung Electronics Co., Ltd.
 * Author: Jacek Anaszewski <j.anaszewski@samsung.com>
 *
 * Copyright (C) 2019 Jacek Anaszewski <jacek.anaszewski@gmail.com>
 * Copyright (C) 2020 Pavel Machek <pavel@ucw.cz>
 */

#अगर_अघोषित __DT_BINDINGS_LEDS_H
#घोषणा __DT_BINDINGS_LEDS_H

/* External trigger type */
#घोषणा LEDS_TRIG_TYPE_EDGE	0
#घोषणा LEDS_TRIG_TYPE_LEVEL	1

/* Boost modes */
#घोषणा LEDS_BOOST_OFF		0
#घोषणा LEDS_BOOST_ADAPTIVE	1
#घोषणा LEDS_BOOST_FIXED	2

/* Standard LED colors */
#घोषणा LED_COLOR_ID_WHITE	0
#घोषणा LED_COLOR_ID_RED	1
#घोषणा LED_COLOR_ID_GREEN	2
#घोषणा LED_COLOR_ID_BLUE	3
#घोषणा LED_COLOR_ID_AMBER	4
#घोषणा LED_COLOR_ID_VIOLET	5
#घोषणा LED_COLOR_ID_YELLOW	6
#घोषणा LED_COLOR_ID_IR		7
#घोषणा LED_COLOR_ID_MULTI	8	/* For multicolor LEDs */
#घोषणा LED_COLOR_ID_RGB	9	/* For multicolor LEDs that can करो arbitrary color,
					   so this would include RGBW and similar */
#घोषणा LED_COLOR_ID_MAX	10

/* Standard LED functions */
/* Keyboard LEDs, usually it would be input4::capslock etc. */
/*   Obsolete equivalent: "shift-key-light" */
#घोषणा LED_FUNCTION_CAPSLOCK "capslock"
#घोषणा LED_FUNCTION_SCROLLLOCK "scrolllock"
#घोषणा LED_FUNCTION_NUMLOCK "numlock"
/*   Obsolete equivalents: "tpacpi::thinklight" (IBM/Lenovo Thinkpads),
     "lp5523:kb{1,2,3,4,5,6}" (Nokia N900) */
#घोषणा LED_FUNCTION_KBD_BACKLIGHT "kbd_backlight"

/* System LEDs, usually found on प्रणाली body.
   platक्रमm::mute (etc) is someबार seen, :mute would be better */
#घोषणा LED_FUNCTION_POWER "power"
#घोषणा LED_FUNCTION_DISK "disk"

/*   Obsolete: "platform:*:charging" (allwinner sun50i) */
#घोषणा LED_FUNCTION_CHARGING "charging"
/*   Used RGB notअगरication LEDs common on phones.
     Obsolete equivalents: "status-led:{red,green,blue}" (Motorola Droid 4),
     "lp5523:{r,g,b}" (Nokia N900) */
#घोषणा LED_FUNCTION_STATUS "status"

#घोषणा LED_FUNCTION_MICMUTE "micmute"
#घोषणा LED_FUNCTION_MUTE "mute"

/* Miscelleaus functions. Use functions above अगर you can. */
#घोषणा LED_FUNCTION_ACTIVITY "activity"
#घोषणा LED_FUNCTION_ALARM "alarm"
#घोषणा LED_FUNCTION_BACKLIGHT "backlight"
#घोषणा LED_FUNCTION_BLUETOOTH "bluetooth"
#घोषणा LED_FUNCTION_BOOT "boot"
#घोषणा LED_FUNCTION_CPU "cpu"
#घोषणा LED_FUNCTION_DEBUG "debug"
#घोषणा LED_FUNCTION_DISK_ACTIVITY "disk-activity"
#घोषणा LED_FUNCTION_DISK_ERR "disk-err"
#घोषणा LED_FUNCTION_DISK_READ "disk-read"
#घोषणा LED_FUNCTION_DISK_WRITE "disk-write"
#घोषणा LED_FUNCTION_FAULT "fault"
#घोषणा LED_FUNCTION_FLASH "flash"
#घोषणा LED_FUNCTION_HEARTBEAT "heartbeat"
#घोषणा LED_FUNCTION_INDICATOR "indicator"
#घोषणा LED_FUNCTION_LAN "lan"
#घोषणा LED_FUNCTION_MAIL "mail"
#घोषणा LED_FUNCTION_MTD "mtd"
#घोषणा LED_FUNCTION_PANIC "panic"
#घोषणा LED_FUNCTION_PROGRAMMING "programming"
#घोषणा LED_FUNCTION_RX "rx"
#घोषणा LED_FUNCTION_SD "sd"
#घोषणा LED_FUNCTION_STANDBY "standby"
#घोषणा LED_FUNCTION_TORCH "torch"
#घोषणा LED_FUNCTION_TX "tx"
#घोषणा LED_FUNCTION_USB "usb"
#घोषणा LED_FUNCTION_WAN "wan"
#घोषणा LED_FUNCTION_WLAN "wlan"
#घोषणा LED_FUNCTION_WPS "wps"

#पूर्ण_अगर /* __DT_BINDINGS_LEDS_H */
