<शैली गुरु>
/*
 * TI DaVinci Audio Serial Port support
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - https://www.ti.com/
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित __DAVINCI_ASP_H
#घोषणा __DAVINCI_ASP_H

#समावेश <linux/genभाग.स>

काष्ठा davinci_mcasp_pdata अणु
	u32 tx_dma_offset;
	u32 rx_dma_offset;
	पूर्णांक asp_chan_q;	/* event queue number क्रम ASP channel */
	पूर्णांक ram_chan_q;	/* event queue number क्रम RAM channel */
	/*
	 * Allowing this is more efficient and eliminates left and right swaps
	 * caused by underruns, but will swap the left and right channels
	 * when compared to previous behavior.
	 */
	अचिन्हित enable_channel_combine:1;
	अचिन्हित sram_size_playback;
	अचिन्हित sram_size_capture;
	काष्ठा gen_pool *sram_pool;

	/*
	 * If McBSP peripheral माला_लो the घड़ी from an बाह्यal pin,
	 * there are three chooses, that are MCBSP_CLKX, MCBSP_CLKR
	 * and MCBSP_CLKS.
	 * Depending on dअगरferent hardware connections it is possible
	 * to use this setting to change the behaviour of McBSP
	 * driver.
	 */
	पूर्णांक clk_input_pin;

	/*
	 * This flag works when both घड़ी and FS are outमाला_दो क्रम the cpu
	 * and makes घड़ी more accurate (FS is not symmetrical and the
	 * घड़ी is very fast.
	 * The घड़ी becoming faster is named
	 * i2s continuous serial घड़ी (I2S_SCK) and it is an बाह्यally
	 * visible bit घड़ी.
	 *
	 * first line : WordSelect
	 * second line : ContinuousSerialClock
	 * third line: SerialData
	 *
	 * SYMMETRICAL APPROACH:
	 *   _______________________          LEFT
	 * _|         RIGHT         |______________________|
	 *     _   _         _   _   _   _         _   _
	 *   _| |_| |_ x16 _| |_| |_| |_| |_ x16 _| |_| |_
	 *     _   _         _   _   _   _         _   _
	 *   _/ \_/ \_ ... _/ \_/ \_/ \_/ \_ ... _/ \_/ \_
	 *    \_/ \_/       \_/ \_/ \_/ \_/       \_/ \_/
	 *
	 * ACCURATE CLOCK APPROACH:
	 *   ______________          LEFT
	 * _|     RIGHT    |_______________________________|
	 *     _         _   _         _   _   _   _   _   _
	 *   _| |_ x16 _| |_| |_ x16 _| |_| |_| |_| |_| |_| |
	 *     _         _   _          _      dummy cycles
	 *   _/ \_ ... _/ \_/ \_  ... _/ \__________________
	 *    \_/       \_/ \_/        \_/
	 *
	 */
	bool i2s_accurate_sck;

	/* McASP specअगरic fields */
	पूर्णांक tdm_slots;
	u8 op_mode;
	u8 dismod;
	u8 num_serializer;
	u8 *serial_dir;
	u8 version;
	u8 txnumevt;
	u8 rxnumevt;
	पूर्णांक tx_dma_channel;
	पूर्णांक rx_dma_channel;
पूर्ण;
/* TODO: Fix arch/arm/mach-davinci/ users and हटाओ this define */
#घोषणा snd_platक्रमm_data davinci_mcasp_pdata

क्रमागत अणु
	MCASP_VERSION_1 = 0,	/* DM646x */
	MCASP_VERSION_2,	/* DA8xx/OMAPL1x */
	MCASP_VERSION_3,        /* TI81xx/AM33xx */
	MCASP_VERSION_4,	/* DRA7xxx */
पूर्ण;

क्रमागत mcbsp_clk_input_pin अणु
	MCBSP_CLKR = 0,		/* as in DM365 */
	MCBSP_CLKS,
पूर्ण;

#घोषणा INACTIVE_MODE	0
#घोषणा TX_MODE		1
#घोषणा RX_MODE		2

#घोषणा DAVINCI_MCASP_IIS_MODE	0
#घोषणा DAVINCI_MCASP_DIT_MODE	1

#पूर्ण_अगर
