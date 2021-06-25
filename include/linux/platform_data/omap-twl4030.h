<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/**
 * omap-twl4030.h - ASoC machine driver क्रम TI SoC based boards with twl4030
 *		    codec, header.
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - https://www.ti.com
 * All rights reserved.
 *
 * Author: Peter Ujfalusi <peter.ujfalusi@ti.com>
 */

#अगर_अघोषित _OMAP_TWL4030_H_
#घोषणा _OMAP_TWL4030_H_

/* To select अगर only one channel is connected in a stereo port */
#घोषणा OMAP_TWL4030_LEFT	(1 << 0)
#घोषणा OMAP_TWL4030_RIGHT	(1 << 1)

काष्ठा omap_tw4030_pdata अणु
	स्थिर अक्षर *card_name;
	/* Voice port is connected to McBSP3 */
	bool voice_connected;

	/* The driver will parse the connection flags अगर this flag is set */
	bool	custom_routing;
	/* Flags to indicate connected audio ports. */
	u8	has_hs;
	u8	has_hf;
	u8	has_predriv;
	u8	has_carkit;
	bool	has_ear;

	bool	has_मुख्यmic;
	bool	has_submic;
	bool	has_hsmic;
	bool	has_carkiपंचांगic;
	bool	has_digimic0;
	bool	has_digimic1;
	u8	has_linein;

	/* Jack detect GPIO or  <= 0 अगर it is not implemented */
	पूर्णांक jack_detect;
पूर्ण;

#पूर्ण_अगर /* _OMAP_TWL4030_H_ */
