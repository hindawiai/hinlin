<शैली गुरु>
/*
 * ADV7343 header file
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed .as is. WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित ADV7343_H
#घोषणा ADV7343_H

#घोषणा ADV7343_COMPOSITE_ID	(0)
#घोषणा ADV7343_COMPONENT_ID	(1)
#घोषणा ADV7343_SVIDEO_ID	(2)

/**
 * काष्ठा adv7343_घातer_mode - घातer mode configuration.
 * @sleep_mode: on enable the current consumption is reduced to micro ampere
 *		level. All DACs and the पूर्णांकernal PLL circuit are disabled.
 *		Registers can be पढ़ो from and written in sleep mode.
 * @pll_control: PLL and oversampling control. This control allows पूर्णांकernal
 *		 PLL 1 circuit to be घातered करोwn and the oversampling to be
 *		 चयनed off.
 * @dac: array to configure घातer on/off DAC's 1..6
 *
 * Power mode रेजिस्टर (Register 0x0), क्रम more info refer REGISTER MAP ACCESS
 * section of datasheet[1], table 17 page no 30.
 *
 * [1] http://www.analog.com/अटल/imported-files/data_sheets/ADV7342_7343.pdf
 */
काष्ठा adv7343_घातer_mode अणु
	bool sleep_mode;
	bool pll_control;
	u32 dac[6];
पूर्ण;

/**
 * काष्ठा adv7343_sd_config - SD Only Output Configuration.
 * @sd_dac_out: array configuring SD DAC Outमाला_दो 1 and 2
 */
काष्ठा adv7343_sd_config अणु
	/* SD only Output Configuration */
	u32 sd_dac_out[2];
पूर्ण;

/**
 * काष्ठा adv7343_platक्रमm_data - Platक्रमm data values and access functions.
 * @mode_config: Configuration क्रम घातer mode.
 * @sd_config: SD Only Configuration.
 */
काष्ठा adv7343_platक्रमm_data अणु
	काष्ठा adv7343_घातer_mode mode_config;
	काष्ठा adv7343_sd_config sd_config;
पूर्ण;

#पूर्ण_अगर				/* End of #अगर_अघोषित ADV7343_H */
