<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Card-specअगरic functions क्रम the Siano SMS1xxx USB करोngle
 *
 *  Copyright (c) 2008 Michael Krufky <mkrufky@linuxtv.org>
 */

#समावेश "sms-cards.h"
#समावेश "smsir.h"
#समावेश <linux/module.h>

अटल काष्ठा sms_board sms_boards[] = अणु
	[SMS_BOARD_UNKNOWN] = अणु
		.name	= "Unknown board",
		.type = SMS_UNKNOWN_TYPE,
		.शेष_mode = DEVICE_MODE_NONE,
	पूर्ण,
	[SMS1XXX_BOARD_SIANO_STELLAR] = अणु
		.name	= "Siano Stellar Digital Receiver",
		.type	= SMS_STELLAR,
		.शेष_mode = DEVICE_MODE_DVBT_BDA,
	पूर्ण,
	[SMS1XXX_BOARD_SIANO_NOVA_A] = अणु
		.name	= "Siano Nova A Digital Receiver",
		.type	= SMS_NOVA_A0,
		.शेष_mode = DEVICE_MODE_DVBT_BDA,
	पूर्ण,
	[SMS1XXX_BOARD_SIANO_NOVA_B] = अणु
		.name	= "Siano Nova B Digital Receiver",
		.type	= SMS_NOVA_B0,
		.शेष_mode = DEVICE_MODE_DVBT_BDA,
	पूर्ण,
	[SMS1XXX_BOARD_SIANO_VEGA] = अणु
		.name	= "Siano Vega Digital Receiver",
		.type	= SMS_VEGA,
		.शेष_mode = DEVICE_MODE_CMMB,
	पूर्ण,
	[SMS1XXX_BOARD_HAUPPAUGE_CATAMOUNT] = अणु
		.name	= "Hauppauge Catamount",
		.type	= SMS_STELLAR,
		.fw[DEVICE_MODE_DVBT_BDA] = SMS_FW_DVBT_STELLAR,
		.शेष_mode = DEVICE_MODE_DVBT_BDA,
	पूर्ण,
	[SMS1XXX_BOARD_HAUPPAUGE_OKEMO_A] = अणु
		.name	= "Hauppauge Okemo-A",
		.type	= SMS_NOVA_A0,
		.fw[DEVICE_MODE_DVBT_BDA] = SMS_FW_DVBT_NOVA_A,
		.शेष_mode = DEVICE_MODE_DVBT_BDA,
	पूर्ण,
	[SMS1XXX_BOARD_HAUPPAUGE_OKEMO_B] = अणु
		.name	= "Hauppauge Okemo-B",
		.type	= SMS_NOVA_B0,
		.fw[DEVICE_MODE_DVBT_BDA] = SMS_FW_DVBT_NOVA_B,
		.शेष_mode = DEVICE_MODE_DVBT_BDA,
	पूर्ण,
	[SMS1XXX_BOARD_HAUPPAUGE_WINDHAM] = अणु
		.name	= "Hauppauge WinTV MiniStick",
		.type	= SMS_NOVA_B0,
		.fw[DEVICE_MODE_ISDBT_BDA] = SMS_FW_ISDBT_HCW_55XXX,
		.fw[DEVICE_MODE_DVBT_BDA]  = SMS_FW_DVBT_HCW_55XXX,
		.शेष_mode = DEVICE_MODE_DVBT_BDA,
		.rc_codes = RC_MAP_HAUPPAUGE,
		.board_cfg.leds_घातer = 26,
		.board_cfg.led0 = 27,
		.board_cfg.led1 = 28,
		.board_cfg.ir = 9,
		.led_घातer = 26,
		.led_lo    = 27,
		.led_hi    = 28,
	पूर्ण,
	[SMS1XXX_BOARD_HAUPPAUGE_TIGER_MINICARD] = अणु
		.name	= "Hauppauge WinTV MiniCard",
		.type	= SMS_NOVA_B0,
		.fw[DEVICE_MODE_DVBT_BDA] = SMS_FW_DVBT_HCW_55XXX,
		.शेष_mode = DEVICE_MODE_DVBT_BDA,
		.lna_ctrl  = 29,
		.board_cfg.क्रमeign_lna0_ctrl = 29,
		.rf_चयन = 17,
		.board_cfg.rf_चयन_uhf = 17,
	पूर्ण,
	[SMS1XXX_BOARD_HAUPPAUGE_TIGER_MINICARD_R2] = अणु
		.name	= "Hauppauge WinTV MiniCard Rev 2",
		.type	= SMS_NOVA_B0,
		.fw[DEVICE_MODE_DVBT_BDA] = SMS_FW_DVBT_HCW_55XXX,
		.शेष_mode = DEVICE_MODE_DVBT_BDA,
		.lna_ctrl  = -1,
	पूर्ण,
	[SMS1XXX_BOARD_SIANO_NICE] = अणु
		.name = "Siano Nice Digital Receiver",
		.type = SMS_NOVA_B0,
		.शेष_mode = DEVICE_MODE_DVBT_BDA,
	पूर्ण,
	[SMS1XXX_BOARD_SIANO_VENICE] = अणु
		.name = "Siano Venice Digital Receiver",
		.type = SMS_VEGA,
		.शेष_mode = DEVICE_MODE_CMMB,
	पूर्ण,
	[SMS1XXX_BOARD_SIANO_STELLAR_ROM] = अणु
		.name = "Siano Stellar Digital Receiver ROM",
		.type = SMS_STELLAR,
		.शेष_mode = DEVICE_MODE_DVBT_BDA,
		.पूर्णांकf_num = 1,
	पूर्ण,
	[SMS1XXX_BOARD_ZTE_DVB_DATA_CARD] = अणु
		.name = "ZTE Data Card Digital Receiver",
		.type = SMS_NOVA_B0,
		.शेष_mode = DEVICE_MODE_DVBT_BDA,
		.पूर्णांकf_num = 5,
		.mtu = 15792,
	पूर्ण,
	[SMS1XXX_BOARD_ONDA_MDTV_DATA_CARD] = अणु
		.name = "ONDA Data Card Digital Receiver",
		.type = SMS_NOVA_B0,
		.शेष_mode = DEVICE_MODE_DVBT_BDA,
		.पूर्णांकf_num = 6,
		.mtu = 15792,
	पूर्ण,
	[SMS1XXX_BOARD_SIANO_MING] = अणु
		.name = "Siano Ming Digital Receiver",
		.type = SMS_MING,
		.शेष_mode = DEVICE_MODE_CMMB,
	पूर्ण,
	[SMS1XXX_BOARD_SIANO_PELE] = अणु
		.name = "Siano Pele Digital Receiver",
		.type = SMS_PELE,
		.शेष_mode = DEVICE_MODE_ISDBT_BDA,
	पूर्ण,
	[SMS1XXX_BOARD_SIANO_RIO] = अणु
		.name = "Siano Rio Digital Receiver",
		.type = SMS_RIO,
		.शेष_mode = DEVICE_MODE_ISDBT_BDA,
	पूर्ण,
	[SMS1XXX_BOARD_SIANO_DENVER_1530] = अणु
		.name = "Siano Denver (ATSC-M/H) Digital Receiver",
		.type = SMS_DENVER_1530,
		.शेष_mode = DEVICE_MODE_ATSC,
		.crystal = 2400,
	पूर्ण,
	[SMS1XXX_BOARD_SIANO_DENVER_2160] = अणु
		.name = "Siano Denver (TDMB) Digital Receiver",
		.type = SMS_DENVER_2160,
		.शेष_mode = DEVICE_MODE_DAB_TDMB,
	पूर्ण,
	[SMS1XXX_BOARD_PCTV_77E] = अणु
		.name	= "Hauppauge microStick 77e",
		.type	= SMS_NOVA_B0,
		.fw[DEVICE_MODE_DVBT_BDA] = SMS_FW_DVB_NOVA_12MHZ_B0,
		.शेष_mode = DEVICE_MODE_DVBT_BDA,
	पूर्ण,
पूर्ण;

काष्ठा sms_board *sms_get_board(अचिन्हित id)
अणु
	BUG_ON(id >= ARRAY_SIZE(sms_boards));

	वापस &sms_boards[id];
पूर्ण
EXPORT_SYMBOL_GPL(sms_get_board);
अटल अंतरभूत व्योम sms_gpio_assign_11xx_शेष_led_config(
		काष्ठा smscore_config_gpio *p_gpio_config) अणु
	p_gpio_config->direction = SMS_GPIO_सूचीECTION_OUTPUT;
	p_gpio_config->inअक्षर_दोacteristics =
		SMS_GPIO_INPUTCHARACTERISTICS_NORMAL;
	p_gpio_config->outputdriving = SMS_GPIO_OUTPUTDRIVING_4mA;
	p_gpio_config->outमाला_दोlewrate = SMS_GPIO_OUTPUT_SLEW_RATE_0_45_V_NS;
	p_gpio_config->pullupकरोwn = SMS_GPIO_PULLUPDOWN_NONE;
पूर्ण

पूर्णांक sms_board_event(काष्ठा smscore_device_t *coredev,
		    क्रमागत SMS_BOARD_EVENTS gevent)
अणु
	काष्ठा smscore_config_gpio my_gpio_config;

	sms_gpio_assign_11xx_शेष_led_config(&my_gpio_config);

	चयन (gevent) अणु
	हाल BOARD_EVENT_POWER_INIT: /* including hotplug */
		अवरोध; /* BOARD_EVENT_BIND */

	हाल BOARD_EVENT_POWER_SUSPEND:
		अवरोध; /* BOARD_EVENT_POWER_SUSPEND */

	हाल BOARD_EVENT_POWER_RESUME:
		अवरोध; /* BOARD_EVENT_POWER_RESUME */

	हाल BOARD_EVENT_BIND:
		अवरोध; /* BOARD_EVENT_BIND */

	हाल BOARD_EVENT_SCAN_PROG:
		अवरोध; /* BOARD_EVENT_SCAN_PROG */
	हाल BOARD_EVENT_SCAN_COMP:
		अवरोध; /* BOARD_EVENT_SCAN_COMP */
	हाल BOARD_EVENT_EMERGENCY_WARNING_SIGNAL:
		अवरोध; /* BOARD_EVENT_EMERGENCY_WARNING_SIGNAL */
	हाल BOARD_EVENT_FE_LOCK:
		अवरोध; /* BOARD_EVENT_FE_LOCK */
	हाल BOARD_EVENT_FE_UNLOCK:
		अवरोध; /* BOARD_EVENT_FE_UNLOCK */
	हाल BOARD_EVENT_DEMOD_LOCK:
		अवरोध; /* BOARD_EVENT_DEMOD_LOCK */
	हाल BOARD_EVENT_DEMOD_UNLOCK:
		अवरोध; /* BOARD_EVENT_DEMOD_UNLOCK */
	हाल BOARD_EVENT_RECEPTION_MAX_4:
		अवरोध; /* BOARD_EVENT_RECEPTION_MAX_4 */
	हाल BOARD_EVENT_RECEPTION_3:
		अवरोध; /* BOARD_EVENT_RECEPTION_3 */
	हाल BOARD_EVENT_RECEPTION_2:
		अवरोध; /* BOARD_EVENT_RECEPTION_2 */
	हाल BOARD_EVENT_RECEPTION_1:
		अवरोध; /* BOARD_EVENT_RECEPTION_1 */
	हाल BOARD_EVENT_RECEPTION_LOST_0:
		अवरोध; /* BOARD_EVENT_RECEPTION_LOST_0 */
	हाल BOARD_EVENT_MULTIPLEX_OK:
		अवरोध; /* BOARD_EVENT_MULTIPLEX_OK */
	हाल BOARD_EVENT_MULTIPLEX_ERRORS:
		अवरोध; /* BOARD_EVENT_MULTIPLEX_ERRORS */

	शेष:
		pr_err("Unknown SMS board event\n");
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sms_board_event);

अटल पूर्णांक sms_set_gpio(काष्ठा smscore_device_t *coredev, पूर्णांक pin, पूर्णांक enable)
अणु
	पूर्णांक lvl, ret;
	u32 gpio;
	काष्ठा smscore_config_gpio gpioconfig = अणु
		.direction            = SMS_GPIO_सूचीECTION_OUTPUT,
		.pullupकरोwn           = SMS_GPIO_PULLUPDOWN_NONE,
		.inअक्षर_दोacteristics = SMS_GPIO_INPUTCHARACTERISTICS_NORMAL,
		.outमाला_दोlewrate       = SMS_GPIO_OUTPUT_SLEW_RATE_FAST,
		.outputdriving        = SMS_GPIO_OUTPUTDRIVING_S_4mA,
	पूर्ण;

	अगर (pin == 0)
		वापस -EINVAL;

	अगर (pin < 0) अणु
		/* inverted gpio */
		gpio = pin * -1;
		lvl = enable ? 0 : 1;
	पूर्ण अन्यथा अणु
		gpio = pin;
		lvl = enable ? 1 : 0;
	पूर्ण

	ret = smscore_configure_gpio(coredev, gpio, &gpioconfig);
	अगर (ret < 0)
		वापस ret;

	वापस smscore_set_gpio(coredev, gpio, lvl);
पूर्ण

पूर्णांक sms_board_setup(काष्ठा smscore_device_t *coredev)
अणु
	पूर्णांक board_id = smscore_get_board_id(coredev);
	काष्ठा sms_board *board = sms_get_board(board_id);

	चयन (board_id) अणु
	हाल SMS1XXX_BOARD_HAUPPAUGE_WINDHAM:
		/* turn off all LEDs */
		sms_set_gpio(coredev, board->led_घातer, 0);
		sms_set_gpio(coredev, board->led_hi, 0);
		sms_set_gpio(coredev, board->led_lo, 0);
		अवरोध;
	हाल SMS1XXX_BOARD_HAUPPAUGE_TIGER_MINICARD_R2:
	हाल SMS1XXX_BOARD_HAUPPAUGE_TIGER_MINICARD:
		/* turn off LNA */
		sms_set_gpio(coredev, board->lna_ctrl, 0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sms_board_setup);

पूर्णांक sms_board_घातer(काष्ठा smscore_device_t *coredev, पूर्णांक onoff)
अणु
	पूर्णांक board_id = smscore_get_board_id(coredev);
	काष्ठा sms_board *board = sms_get_board(board_id);

	चयन (board_id) अणु
	हाल SMS1XXX_BOARD_HAUPPAUGE_WINDHAM:
		/* घातer LED */
		sms_set_gpio(coredev,
			     board->led_घातer, onoff ? 1 : 0);
		अवरोध;
	हाल SMS1XXX_BOARD_HAUPPAUGE_TIGER_MINICARD_R2:
	हाल SMS1XXX_BOARD_HAUPPAUGE_TIGER_MINICARD:
		/* LNA */
		अगर (!onoff)
			sms_set_gpio(coredev, board->lna_ctrl, 0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sms_board_घातer);

पूर्णांक sms_board_led_feedback(काष्ठा smscore_device_t *coredev, पूर्णांक led)
अणु
	पूर्णांक board_id = smscore_get_board_id(coredev);
	काष्ठा sms_board *board = sms_get_board(board_id);

	/* करोn't touch GPIO अगर LEDs are alपढ़ोy set */
	अगर (smscore_led_state(coredev, -1) == led)
		वापस 0;

	चयन (board_id) अणु
	हाल SMS1XXX_BOARD_HAUPPAUGE_WINDHAM:
		sms_set_gpio(coredev,
			     board->led_lo, (led & SMS_LED_LO) ? 1 : 0);
		sms_set_gpio(coredev,
			     board->led_hi, (led & SMS_LED_HI) ? 1 : 0);

		smscore_led_state(coredev, led);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sms_board_led_feedback);

पूर्णांक sms_board_lna_control(काष्ठा smscore_device_t *coredev, पूर्णांक onoff)
अणु
	पूर्णांक board_id = smscore_get_board_id(coredev);
	काष्ठा sms_board *board = sms_get_board(board_id);

	pr_debug("%s: LNA %s\n", __func__, onoff ? "enabled" : "disabled");

	चयन (board_id) अणु
	हाल SMS1XXX_BOARD_HAUPPAUGE_TIGER_MINICARD_R2:
	हाल SMS1XXX_BOARD_HAUPPAUGE_TIGER_MINICARD:
		sms_set_gpio(coredev,
			     board->rf_चयन, onoff ? 1 : 0);
		वापस sms_set_gpio(coredev,
				    board->lna_ctrl, onoff ? 1 : 0);
	पूर्ण
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(sms_board_lna_control);

पूर्णांक sms_board_load_modules(पूर्णांक id)
अणु
	request_module("smsdvb");
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sms_board_load_modules);
