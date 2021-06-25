<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Card-specअगरic functions क्रम the Siano SMS1xxx USB करोngle
 *
 *  Copyright (c) 2008 Michael Krufky <mkrufky@linuxtv.org>
 */

#अगर_अघोषित __SMS_CARDS_H__
#घोषणा __SMS_CARDS_H__

#समावेश "smscoreapi.h"

#समावेश <linux/usb.h>
#समावेश "smsir.h"

#घोषणा SMS_BOARD_UNKNOWN 0
#घोषणा SMS1XXX_BOARD_SIANO_STELLAR 1
#घोषणा SMS1XXX_BOARD_SIANO_NOVA_A  2
#घोषणा SMS1XXX_BOARD_SIANO_NOVA_B  3
#घोषणा SMS1XXX_BOARD_SIANO_VEGA    4
#घोषणा SMS1XXX_BOARD_HAUPPAUGE_CATAMOUNT 5
#घोषणा SMS1XXX_BOARD_HAUPPAUGE_OKEMO_A 6
#घोषणा SMS1XXX_BOARD_HAUPPAUGE_OKEMO_B 7
#घोषणा SMS1XXX_BOARD_HAUPPAUGE_WINDHAM 8
#घोषणा SMS1XXX_BOARD_HAUPPAUGE_TIGER_MINICARD 9
#घोषणा SMS1XXX_BOARD_HAUPPAUGE_TIGER_MINICARD_R2 10
#घोषणा SMS1XXX_BOARD_SIANO_NICE	11
#घोषणा SMS1XXX_BOARD_SIANO_VENICE	12
#घोषणा SMS1XXX_BOARD_SIANO_STELLAR_ROM 13
#घोषणा SMS1XXX_BOARD_ZTE_DVB_DATA_CARD	14
#घोषणा SMS1XXX_BOARD_ONDA_MDTV_DATA_CARD 15
#घोषणा SMS1XXX_BOARD_SIANO_MING	16
#घोषणा SMS1XXX_BOARD_SIANO_PELE	17
#घोषणा SMS1XXX_BOARD_SIANO_RIO		18
#घोषणा SMS1XXX_BOARD_SIANO_DENVER_1530	19
#घोषणा SMS1XXX_BOARD_SIANO_DENVER_2160 20
#घोषणा SMS1XXX_BOARD_PCTV_77E		21

काष्ठा sms_board_gpio_cfg अणु
	पूर्णांक lna_vhf_exist;
	पूर्णांक lna_vhf_ctrl;
	पूर्णांक lna_uhf_exist;
	पूर्णांक lna_uhf_ctrl;
	पूर्णांक lna_uhf_d_ctrl;
	पूर्णांक lna_sband_exist;
	पूर्णांक lna_sband_ctrl;
	पूर्णांक lna_sband_d_ctrl;
	पूर्णांक क्रमeign_lna0_ctrl;
	पूर्णांक क्रमeign_lna1_ctrl;
	पूर्णांक क्रमeign_lna2_ctrl;
	पूर्णांक rf_चयन_vhf;
	पूर्णांक rf_चयन_uhf;
	पूर्णांक rf_चयन_sband;
	पूर्णांक leds_घातer;
	पूर्णांक led0;
	पूर्णांक led1;
	पूर्णांक led2;
	पूर्णांक led3;
	पूर्णांक led4;
	पूर्णांक ir;
	पूर्णांक eeprom_wp;
	पूर्णांक mrc_sense;
	पूर्णांक mrc_pdn_resetn;
	पूर्णांक mrc_gp0; /* mrcs spi पूर्णांक */
	पूर्णांक mrc_gp1;
	पूर्णांक mrc_gp2;
	पूर्णांक mrc_gp3;
	पूर्णांक mrc_gp4;
	पूर्णांक host_spi_gsp_ts_पूर्णांक;
पूर्ण;

काष्ठा sms_board अणु
	क्रमागत sms_device_type_st type;
	अक्षर *name, *fw[DEVICE_MODE_MAX];
	काष्ठा sms_board_gpio_cfg board_cfg;
	अक्षर *rc_codes;				/* Name of IR codes table */

	/* gpios */
	पूर्णांक led_घातer, led_hi, led_lo, lna_ctrl, rf_चयन;

	अक्षर पूर्णांकf_num;
	पूर्णांक शेष_mode;
	अचिन्हित पूर्णांक mtu;
	अचिन्हित पूर्णांक crystal;
	काष्ठा sms_antenna_config_ST *antenna_config;
पूर्ण;

काष्ठा sms_board *sms_get_board(अचिन्हित id);

बाह्य काष्ठा smscore_device_t *coredev;

क्रमागत SMS_BOARD_EVENTS अणु
	BOARD_EVENT_POWER_INIT,
	BOARD_EVENT_POWER_SUSPEND,
	BOARD_EVENT_POWER_RESUME,
	BOARD_EVENT_BIND,
	BOARD_EVENT_SCAN_PROG,
	BOARD_EVENT_SCAN_COMP,
	BOARD_EVENT_EMERGENCY_WARNING_SIGNAL,
	BOARD_EVENT_FE_LOCK,
	BOARD_EVENT_FE_UNLOCK,
	BOARD_EVENT_DEMOD_LOCK,
	BOARD_EVENT_DEMOD_UNLOCK,
	BOARD_EVENT_RECEPTION_MAX_4,
	BOARD_EVENT_RECEPTION_3,
	BOARD_EVENT_RECEPTION_2,
	BOARD_EVENT_RECEPTION_1,
	BOARD_EVENT_RECEPTION_LOST_0,
	BOARD_EVENT_MULTIPLEX_OK,
	BOARD_EVENT_MULTIPLEX_ERRORS
पूर्ण;

पूर्णांक sms_board_event(काष्ठा smscore_device_t *coredev,
		क्रमागत SMS_BOARD_EVENTS gevent);

पूर्णांक sms_board_setup(काष्ठा smscore_device_t *coredev);

#घोषणा SMS_LED_OFF 0
#घोषणा SMS_LED_LO  1
#घोषणा SMS_LED_HI  2
पूर्णांक sms_board_led_feedback(काष्ठा smscore_device_t *coredev, पूर्णांक led);
पूर्णांक sms_board_घातer(काष्ठा smscore_device_t *coredev, पूर्णांक onoff);
पूर्णांक sms_board_lna_control(काष्ठा smscore_device_t *coredev, पूर्णांक onoff);

बाह्य पूर्णांक sms_board_load_modules(पूर्णांक id);

#पूर्ण_अगर /* __SMS_CARDS_H__ */
