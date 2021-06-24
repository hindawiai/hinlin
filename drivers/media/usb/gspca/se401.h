<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * GSPCA Endpoपूर्णांकs (क्रमmerly known as AOX) se401 USB Camera sub Driver
 *
 * Copyright (C) 2011 Hans de Goede <hdegoede@redhat.com>
 *
 * Based on the v4l1 se401 driver which is:
 *
 * Copyright (c) 2000 Jeroen B. Vreeken (pe1rxq@amsat.org)
 */

#घोषणा SE401_REQ_GET_CAMERA_DESCRIPTOR		0x06
#घोषणा SE401_REQ_START_CONTINUOUS_CAPTURE	0x41
#घोषणा SE401_REQ_STOP_CONTINUOUS_CAPTURE	0x42
#घोषणा SE401_REQ_CAPTURE_FRAME			0x43
#घोषणा SE401_REQ_GET_BRT			0x44
#घोषणा SE401_REQ_SET_BRT			0x45
#घोषणा SE401_REQ_GET_WIDTH			0x4c
#घोषणा SE401_REQ_SET_WIDTH			0x4d
#घोषणा SE401_REQ_GET_HEIGHT			0x4e
#घोषणा SE401_REQ_SET_HEIGHT			0x4f
#घोषणा SE401_REQ_GET_OUTPUT_MODE		0x50
#घोषणा SE401_REQ_SET_OUTPUT_MODE		0x51
#घोषणा SE401_REQ_GET_EXT_FEATURE		0x52
#घोषणा SE401_REQ_SET_EXT_FEATURE		0x53
#घोषणा SE401_REQ_CAMERA_POWER			0x56
#घोषणा SE401_REQ_LED_CONTROL			0x57
#घोषणा SE401_REQ_BIOS				0xff

#घोषणा SE401_BIOS_READ				0x07

#घोषणा SE401_FORMAT_BAYER	0x40

/* Hyundai hv7131b रेजिस्टरs
   7121 and 7141 should be the same (haven't really checked...) */
/* Mode रेजिस्टरs: */
#घोषणा HV7131_REG_MODE_A		0x00
#घोषणा HV7131_REG_MODE_B		0x01
#घोषणा HV7131_REG_MODE_C		0x02
/* Frame रेजिस्टरs: */
#घोषणा HV7131_REG_FRSU		0x10
#घोषणा HV7131_REG_FRSL		0x11
#घोषणा HV7131_REG_FCSU		0x12
#घोषणा HV7131_REG_FCSL		0x13
#घोषणा HV7131_REG_FWHU		0x14
#घोषणा HV7131_REG_FWHL		0x15
#घोषणा HV7131_REG_FWWU		0x16
#घोषणा HV7131_REG_FWWL		0x17
/* Timing रेजिस्टरs: */
#घोषणा HV7131_REG_THBU		0x20
#घोषणा HV7131_REG_THBL		0x21
#घोषणा HV7131_REG_TVBU		0x22
#घोषणा HV7131_REG_TVBL		0x23
#घोषणा HV7131_REG_TITU		0x25
#घोषणा HV7131_REG_TITM		0x26
#घोषणा HV7131_REG_TITL		0x27
#घोषणा HV7131_REG_TMCD		0x28
/* Adjust Registers: */
#घोषणा HV7131_REG_ARLV		0x30
#घोषणा HV7131_REG_ARCG		0x31
#घोषणा HV7131_REG_AGCG		0x32
#घोषणा HV7131_REG_ABCG		0x33
#घोषणा HV7131_REG_APBV		0x34
#घोषणा HV7131_REG_ASLP		0x54
/* Offset Registers: */
#घोषणा HV7131_REG_OFSR		0x50
#घोषणा HV7131_REG_OFSG		0x51
#घोषणा HV7131_REG_OFSB		0x52
/* REset level statistics रेजिस्टरs: */
#घोषणा HV7131_REG_LOREFNOH	0x57
#घोषणा HV7131_REG_LOREFNOL	0x58
#घोषणा HV7131_REG_HIREFNOH	0x59
#घोषणा HV7131_REG_HIREFNOL	0x5a

/* se401 रेजिस्टरs */
#घोषणा SE401_OPERATINGMODE	0x2000
