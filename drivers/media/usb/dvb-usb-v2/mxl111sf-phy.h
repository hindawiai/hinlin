<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  mxl111sf-phy.h - driver क्रम the MaxLinear MXL111SF
 *
 *  Copyright (C) 2010-2014 Michael Krufky <mkrufky@linuxtv.org>
 */

#अगर_अघोषित _DVB_USB_MXL111SF_PHY_H_
#घोषणा _DVB_USB_MXL111SF_PHY_H_

#समावेश "mxl111sf.h"

पूर्णांक mxl1x1sf_soft_reset(काष्ठा mxl111sf_state *state);
पूर्णांक mxl1x1sf_set_device_mode(काष्ठा mxl111sf_state *state, पूर्णांक mode);
पूर्णांक mxl1x1sf_top_master_ctrl(काष्ठा mxl111sf_state *state, पूर्णांक onoff);
पूर्णांक mxl111sf_disable_656_port(काष्ठा mxl111sf_state *state);
पूर्णांक mxl111sf_init_tuner_demod(काष्ठा mxl111sf_state *state);
पूर्णांक mxl111sf_enable_usb_output(काष्ठा mxl111sf_state *state);
पूर्णांक mxl111sf_config_mpeg_in(काष्ठा mxl111sf_state *state,
			    अचिन्हित पूर्णांक parallel_serial,
			    अचिन्हित पूर्णांक msb_lsb_1st,
			    अचिन्हित पूर्णांक घड़ी_phase,
			    अचिन्हित पूर्णांक mpeg_valid_pol,
			    अचिन्हित पूर्णांक mpeg_sync_pol);
पूर्णांक mxl111sf_config_i2s(काष्ठा mxl111sf_state *state,
			u8 msb_start_pos, u8 data_width);
पूर्णांक mxl111sf_init_i2s_port(काष्ठा mxl111sf_state *state, u8 sample_size);
पूर्णांक mxl111sf_disable_i2s_port(काष्ठा mxl111sf_state *state);
पूर्णांक mxl111sf_config_spi(काष्ठा mxl111sf_state *state, पूर्णांक onoff);
पूर्णांक mxl111sf_idac_config(काष्ठा mxl111sf_state *state,
			 u8 control_mode, u8 current_setting,
			 u8 current_value, u8 hysteresis_value);

#पूर्ण_अगर /* _DVB_USB_MXL111SF_PHY_H_ */
