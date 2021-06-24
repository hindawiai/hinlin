<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 */
#अगर_अघोषित __PVRUSB2_DEVATTR_H
#घोषणा __PVRUSB2_DEVATTR_H

#समावेश <linux/mod_devicetable.h>
#समावेश <linux/videodev2.h>
#अगर_घोषित CONFIG_VIDEO_PVRUSB2_DVB
#समावेश "pvrusb2-dvb.h"
#पूर्ण_अगर

/*

  This header defines काष्ठाures used to describe attributes of a device.

*/


#घोषणा PVR2_CLIENT_ID_शून्य 0
#घोषणा PVR2_CLIENT_ID_MSP3400 1
#घोषणा PVR2_CLIENT_ID_CX25840 2
#घोषणा PVR2_CLIENT_ID_SAA7115 3
#घोषणा PVR2_CLIENT_ID_TUNER 4
#घोषणा PVR2_CLIENT_ID_CS53L32A 5
#घोषणा PVR2_CLIENT_ID_WM8775 6
#घोषणा PVR2_CLIENT_ID_DEMOD 7

काष्ठा pvr2_device_client_desc अणु
	/* One ovr PVR2_CLIENT_ID_xxxx */
	अचिन्हित अक्षर module_id;

	/* Null-terminated array of I2C addresses to try in order
	   initialize the module.  It's safe to make this null terminated
	   since we're never going to encounter an i2c device with an
	   address of zero.  If this is a null poपूर्णांकer or zero-length,
	   then no I2C addresses have been specअगरied, in which हाल we'll
	   try some compiled in शेषs क्रम now. */
	अचिन्हित अक्षर *i2c_address_list;
पूर्ण;

काष्ठा pvr2_device_client_table अणु
	स्थिर काष्ठा pvr2_device_client_desc *lst;
	अचिन्हित अक्षर cnt;
पूर्ण;


काष्ठा pvr2_string_table अणु
	स्थिर अक्षर **lst;
	अचिन्हित पूर्णांक cnt;
पूर्ण;

#घोषणा PVR2_ROUTING_SCHEME_HAUPPAUGE 0
#घोषणा PVR2_ROUTING_SCHEME_GOTVIEW 1
#घोषणा PVR2_ROUTING_SCHEME_ONAIR 2
#घोषणा PVR2_ROUTING_SCHEME_AV400 3
#घोषणा PVR2_ROUTING_SCHEME_HAUP160XXX 4

#घोषणा PVR2_DIGITAL_SCHEME_NONE 0
#घोषणा PVR2_DIGITAL_SCHEME_HAUPPAUGE 1
#घोषणा PVR2_DIGITAL_SCHEME_ONAIR 2

#घोषणा PVR2_LED_SCHEME_NONE 0
#घोषणा PVR2_LED_SCHEME_HAUPPAUGE 1

#घोषणा PVR2_IR_SCHEME_NONE 0
#घोषणा PVR2_IR_SCHEME_24XXX 1 /* FX2-controlled IR */
#घोषणा PVR2_IR_SCHEME_ZILOG 2 /* HVR-1950 style (must be taken out of reset) */
#घोषणा PVR2_IR_SCHEME_24XXX_MCE 3 /* 24xxx MCE device */
#घोषणा PVR2_IR_SCHEME_29XXX 4 /* Original 29xxx device */

/* This describes a particular hardware type (except क्रम the USB device ID
   which must live in a separate काष्ठाure due to environmental
   स्थिरraपूर्णांकs).  See the top of pvrusb2-hdw.c क्रम where this is
   instantiated. */
काष्ठा pvr2_device_desc अणु
	/* Single line text description of hardware */
	स्थिर अक्षर *description;

	/* Single token identअगरier क्रम hardware */
	स्थिर अक्षर *लघुname;

	/* List of additional client modules we need to load */
	काष्ठा pvr2_string_table client_modules;

	/* List of defined client modules we need to load */
	काष्ठा pvr2_device_client_table client_table;

	/* List of FX2 firmware file names we should search; अगर empty then
	   FX2 firmware check / load is skipped and we assume the device
	   was initialized from पूर्णांकernal ROM. */
	काष्ठा pvr2_string_table fx2_firmware;

#अगर_घोषित CONFIG_VIDEO_PVRUSB2_DVB
	/* callback functions to handle attachment of digital tuner & demod */
	स्थिर काष्ठा pvr2_dvb_props *dvb_props;

#पूर्ण_अगर
	/* Initial standard bits to use क्रम this device, अगर not zero.
	   Anything set here is also implied as an available standard.
	   Note: This is ignored अगर overridden on the module load line via
	   the video_std module option. */
	v4l2_std_id शेष_std_mask;

	/* V4L tuner type ID to use with this device (only used अगर the
	   driver could not discover the type any other way). */
	पूर्णांक शेष_tuner_type;

	/* Signal routing scheme used by device, contains one of
	   PVR2_ROUTING_SCHEME_XXX.  Schemes have to be defined as we
	   encounter them.  This is an arbitrary पूर्णांकeger scheme id; its
	   meaning is contained entirely within the driver and is
	   पूर्णांकerpreted by logic which must send commands to the chip-level
	   drivers (search क्रम things which touch this field). */
	अचिन्हित अक्षर संकेत_routing_scheme;

	/* Indicates scheme क्रम controlling device's LED (अगर any).  The
	   driver will turn on the LED when streaming is underway.  This
	   contains one of PVR2_LED_SCHEME_XXX. */
	अचिन्हित अक्षर led_scheme;

	/* Control scheme to use अगर there is a digital tuner.  This
	   contains one of PVR2_DIGITAL_SCHEME_XXX.  This is an arbitrary
	   पूर्णांकeger scheme id; its meaning is contained entirely within the
	   driver and is पूर्णांकerpreted by logic which must control the
	   streaming pathway (search क्रम things which touch this field). */
	अचिन्हित अक्षर digital_control_scheme;

	/* If set, we करोn't bother trying to load cx23416 firmware. */
	अचिन्हित पूर्णांक flag_skip_cx23416_firmware:1;

	/* If set, the encoder must be healthy in order क्रम digital mode to
	   work (otherwise we assume that digital streaming will work even
	   अगर we fail to locate firmware क्रम the encoder).  If the device
	   करोesn't support digital streaming then this flag has no
	   effect. */
	अचिन्हित पूर्णांक flag_digital_requires_cx23416:1;

	/* Device has a hauppauge eeprom which we can पूर्णांकerrogate. */
	अचिन्हित पूर्णांक flag_has_hauppauge_rom:1;

	/* Device करोes not require a घातerup command to be issued. */
	अचिन्हित पूर्णांक flag_no_घातerup:1;

	/* Device has a cx25840 - this enables special additional logic to
	   handle it. */
	अचिन्हित पूर्णांक flag_has_cx25840:1;

	/* Device has a wm8775 - this enables special additional logic to
	   ensure that it is found. */
	अचिन्हित पूर्णांक flag_has_wm8775:1;

	/* Indicate IR scheme of hardware.  If not set, then it is assumed
	   that IR can work without any help from the driver. */
	अचिन्हित पूर्णांक ir_scheme:3;

	/* These bits define which kinds of sources the device can handle.
	   Note: Digital tuner presence is inferred by the
	   digital_control_scheme क्रमागतeration. */
	अचिन्हित पूर्णांक flag_has_fmradio:1;       /* Has FM radio receiver */
	अचिन्हित पूर्णांक flag_has_analogtuner:1;   /* Has analog tuner */
	अचिन्हित पूर्णांक flag_has_composite:1;     /* Has composite input */
	अचिन्हित पूर्णांक flag_has_svideo:1;        /* Has s-video input */
	अचिन्हित पूर्णांक flag_fx2_16kb:1;          /* 16KB FX2 firmware OK here */

	/* If this driver is considered experimental, i.e. not all aspects
	   are working correctly and/or it is untested, mark that fact
	   with this flag. */
	अचिन्हित पूर्णांक flag_is_experimental:1;
पूर्ण;

बाह्य काष्ठा usb_device_id pvr2_device_table[];

#पूर्ण_अगर /* __PVRUSB2_HDW_INTERNAL_H */
