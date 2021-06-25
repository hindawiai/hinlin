<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  mxl111sf-gpपन.स - driver क्रम the MaxLinear MXL111SF
 *
 *  Copyright (C) 2010-2014 Michael Krufky <mkrufky@linuxtv.org>
 */

#अगर_अघोषित _DVB_USB_MXL111SF_GPIO_H_
#घोषणा _DVB_USB_MXL111SF_GPIO_H_

#समावेश "mxl111sf.h"

पूर्णांक mxl111sf_set_gpio(काष्ठा mxl111sf_state *state, पूर्णांक gpio, पूर्णांक val);
पूर्णांक mxl111sf_init_port_expander(काष्ठा mxl111sf_state *state);

#घोषणा MXL111SF_GPIO_MOD_DVBT	0
#घोषणा MXL111SF_GPIO_MOD_MH	1
#घोषणा MXL111SF_GPIO_MOD_ATSC	2
पूर्णांक mxl111sf_gpio_mode_चयन(काष्ठा mxl111sf_state *state, अचिन्हित पूर्णांक mode);

क्रमागत mxl111sf_mux_config अणु
	PIN_MUX_DEFAULT = 0,
	PIN_MUX_TS_OUT_PARALLEL,
	PIN_MUX_TS_OUT_SERIAL,
	PIN_MUX_GPIO_MODE,
	PIN_MUX_TS_SERIAL_IN_MODE_0,
	PIN_MUX_TS_SERIAL_IN_MODE_1,
	PIN_MUX_TS_SPI_IN_MODE_0,
	PIN_MUX_TS_SPI_IN_MODE_1,
	PIN_MUX_TS_PARALLEL_IN,
	PIN_MUX_BT656_I2S_MODE,
पूर्ण;

पूर्णांक mxl111sf_config_pin_mux_modes(काष्ठा mxl111sf_state *state,
				  क्रमागत mxl111sf_mux_config pin_mux_config);

#पूर्ण_अगर /* _DVB_USB_MXL111SF_GPIO_H_ */
