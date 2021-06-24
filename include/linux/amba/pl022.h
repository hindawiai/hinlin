<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * include/linux/amba/pl022.h
 *
 * Copyright (C) 2008-2009 ST-Ericsson AB
 * Copyright (C) 2006 STMicroelectronics Pvt. Ltd.
 *
 * Author: Linus Walleij <linus.walleij@stericsson.com>
 *
 * Initial version inspired by:
 *	linux-2.6.17-rc3-mm1/drivers/spi/pxa2xx_spi.c
 * Initial aकरोption to PL022 by:
 *      Sachin Verma <sachin.verma@st.com>
 */

#अगर_अघोषित _SSP_PL022_H
#घोषणा _SSP_PL022_H

#समावेश <linux/types.h>

/**
 * whether SSP is in loopback mode or not
 */
क्रमागत ssp_loopback अणु
	LOOPBACK_DISABLED,
	LOOPBACK_ENABLED
पूर्ण;

/**
 * क्रमागत ssp_पूर्णांकerface - पूर्णांकerfaces allowed क्रम this SSP Controller
 * @SSP_INTERFACE_MOTOROLA_SPI: Motorola Interface
 * @SSP_INTERFACE_TI_SYNC_SERIAL: Texas Instrument Synchronous Serial
 * पूर्णांकerface
 * @SSP_INTERFACE_NATIONAL_MICROWIRE: National Semiconductor Microwire
 * पूर्णांकerface
 * @SSP_INTERFACE_UNIसूचीECTIONAL: Unidirectional पूर्णांकerface (STn8810
 * &STn8815 only)
 */
क्रमागत ssp_पूर्णांकerface अणु
	SSP_INTERFACE_MOTOROLA_SPI,
	SSP_INTERFACE_TI_SYNC_SERIAL,
	SSP_INTERFACE_NATIONAL_MICROWIRE,
	SSP_INTERFACE_UNIसूचीECTIONAL
पूर्ण;

/**
 * क्रमागत ssp_hierarchy - whether SSP is configured as Master or Slave
 */
क्रमागत ssp_hierarchy अणु
	SSP_MASTER,
	SSP_SLAVE
पूर्ण;

/**
 * क्रमागत ssp_घड़ी_params - घड़ी parameters, to set SSP घड़ी at a
 * desired freq
 */
काष्ठा ssp_घड़ी_params अणु
	u8 cpsdvsr; /* value from 2 to 254 (even only!) */
	u8 scr;	    /* value from 0 to 255 */
पूर्ण;

/**
 * क्रमागत ssp_rx_endian - endianess of Rx FIFO Data
 * this feature is only available in ST versionf of PL022
 */
क्रमागत ssp_rx_endian अणु
	SSP_RX_MSB,
	SSP_RX_LSB
पूर्ण;

/**
 * क्रमागत ssp_tx_endian - endianess of Tx FIFO Data
 */
क्रमागत ssp_tx_endian अणु
	SSP_TX_MSB,
	SSP_TX_LSB
पूर्ण;

/**
 * क्रमागत ssp_data_size - number of bits in one data element
 */
क्रमागत ssp_data_size अणु
	SSP_DATA_BITS_4 = 0x03, SSP_DATA_BITS_5, SSP_DATA_BITS_6,
	SSP_DATA_BITS_7, SSP_DATA_BITS_8, SSP_DATA_BITS_9,
	SSP_DATA_BITS_10, SSP_DATA_BITS_11, SSP_DATA_BITS_12,
	SSP_DATA_BITS_13, SSP_DATA_BITS_14, SSP_DATA_BITS_15,
	SSP_DATA_BITS_16, SSP_DATA_BITS_17, SSP_DATA_BITS_18,
	SSP_DATA_BITS_19, SSP_DATA_BITS_20, SSP_DATA_BITS_21,
	SSP_DATA_BITS_22, SSP_DATA_BITS_23, SSP_DATA_BITS_24,
	SSP_DATA_BITS_25, SSP_DATA_BITS_26, SSP_DATA_BITS_27,
	SSP_DATA_BITS_28, SSP_DATA_BITS_29, SSP_DATA_BITS_30,
	SSP_DATA_BITS_31, SSP_DATA_BITS_32
पूर्ण;

/**
 * क्रमागत ssp_mode - SSP mode of operation (Communication modes)
 */
क्रमागत ssp_mode अणु
	INTERRUPT_TRANSFER,
	POLLING_TRANSFER,
	DMA_TRANSFER
पूर्ण;

/**
 * क्रमागत ssp_rx_level_trig - receive FIFO watermark level which triggers
 * IT: Interrupt fires when _N_ or more elements in RX FIFO.
 */
क्रमागत ssp_rx_level_trig अणु
	SSP_RX_1_OR_MORE_ELEM,
	SSP_RX_4_OR_MORE_ELEM,
	SSP_RX_8_OR_MORE_ELEM,
	SSP_RX_16_OR_MORE_ELEM,
	SSP_RX_32_OR_MORE_ELEM
पूर्ण;

/**
 * Transmit FIFO watermark level which triggers (IT Interrupt fires
 * when _N_ or more empty locations in TX FIFO)
 */
क्रमागत ssp_tx_level_trig अणु
	SSP_TX_1_OR_MORE_EMPTY_LOC,
	SSP_TX_4_OR_MORE_EMPTY_LOC,
	SSP_TX_8_OR_MORE_EMPTY_LOC,
	SSP_TX_16_OR_MORE_EMPTY_LOC,
	SSP_TX_32_OR_MORE_EMPTY_LOC
पूर्ण;

/**
 * क्रमागत SPI Clock Phase - घड़ी phase (Motorola SPI पूर्णांकerface only)
 * @SSP_CLK_FIRST_EDGE: Receive data on first edge transition (actual direction depends on polarity)
 * @SSP_CLK_SECOND_EDGE: Receive data on second edge transition (actual direction depends on polarity)
 */
क्रमागत ssp_spi_clk_phase अणु
	SSP_CLK_FIRST_EDGE,
	SSP_CLK_SECOND_EDGE
पूर्ण;

/**
 * क्रमागत SPI Clock Polarity - घड़ी polarity (Motorola SPI पूर्णांकerface only)
 * @SSP_CLK_POL_IDLE_LOW: Low inactive level
 * @SSP_CLK_POL_IDLE_HIGH: High inactive level
 */
क्रमागत ssp_spi_clk_pol अणु
	SSP_CLK_POL_IDLE_LOW,
	SSP_CLK_POL_IDLE_HIGH
पूर्ण;

/**
 * Microwire Conrol Lengths Command size in microwire क्रमmat
 */
क्रमागत ssp_microwire_ctrl_len अणु
	SSP_BITS_4 = 0x03, SSP_BITS_5, SSP_BITS_6,
	SSP_BITS_7, SSP_BITS_8, SSP_BITS_9,
	SSP_BITS_10, SSP_BITS_11, SSP_BITS_12,
	SSP_BITS_13, SSP_BITS_14, SSP_BITS_15,
	SSP_BITS_16, SSP_BITS_17, SSP_BITS_18,
	SSP_BITS_19, SSP_BITS_20, SSP_BITS_21,
	SSP_BITS_22, SSP_BITS_23, SSP_BITS_24,
	SSP_BITS_25, SSP_BITS_26, SSP_BITS_27,
	SSP_BITS_28, SSP_BITS_29, SSP_BITS_30,
	SSP_BITS_31, SSP_BITS_32
पूर्ण;

/**
 * क्रमागत Microwire Wait State
 * @SSP_MWIRE_WAIT_ZERO: No रुको state inserted after last command bit
 * @SSP_MWIRE_WAIT_ONE: One रुको state inserted after last command bit
 */
क्रमागत ssp_microwire_रुको_state अणु
	SSP_MWIRE_WAIT_ZERO,
	SSP_MWIRE_WAIT_ONE
पूर्ण;

/**
 * क्रमागत ssp_duplex - whether Full/Half Duplex on microwire, only
 * available in the ST Micro variant.
 * @SSP_MICROWIRE_CHANNEL_FULL_DUPLEX: SSPTXD becomes bi-directional,
 *     SSPRXD not used
 * @SSP_MICROWIRE_CHANNEL_HALF_DUPLEX: SSPTXD is an output, SSPRXD is
 *     an input.
 */
क्रमागत ssp_duplex अणु
	SSP_MICROWIRE_CHANNEL_FULL_DUPLEX,
	SSP_MICROWIRE_CHANNEL_HALF_DUPLEX
पूर्ण;

/**
 * क्रमागत ssp_clkdelay - an optional घड़ी delay on the feedback घड़ी
 * only available in the ST Micro PL023 variant.
 * @SSP_FEEDBACK_CLK_DELAY_NONE: no delay, the data coming in from the
 * slave is sampled directly
 * @SSP_FEEDBACK_CLK_DELAY_1T: the incoming slave data is sampled with
 * a delay of T-dt
 * @SSP_FEEDBACK_CLK_DELAY_2T: dito with a delay अगर 2T-dt
 * @SSP_FEEDBACK_CLK_DELAY_3T: dito with a delay अगर 3T-dt
 * @SSP_FEEDBACK_CLK_DELAY_4T: dito with a delay अगर 4T-dt
 * @SSP_FEEDBACK_CLK_DELAY_5T: dito with a delay अगर 5T-dt
 * @SSP_FEEDBACK_CLK_DELAY_6T: dito with a delay अगर 6T-dt
 * @SSP_FEEDBACK_CLK_DELAY_7T: dito with a delay अगर 7T-dt
 */
क्रमागत ssp_clkdelay अणु
	SSP_FEEDBACK_CLK_DELAY_NONE,
	SSP_FEEDBACK_CLK_DELAY_1T,
	SSP_FEEDBACK_CLK_DELAY_2T,
	SSP_FEEDBACK_CLK_DELAY_3T,
	SSP_FEEDBACK_CLK_DELAY_4T,
	SSP_FEEDBACK_CLK_DELAY_5T,
	SSP_FEEDBACK_CLK_DELAY_6T,
	SSP_FEEDBACK_CLK_DELAY_7T
पूर्ण;

/**
 * CHIP select/deselect commands
 */
क्रमागत ssp_chip_select अणु
	SSP_CHIP_SELECT,
	SSP_CHIP_DESELECT
पूर्ण;


काष्ठा dma_chan;
/**
 * काष्ठा pl022_ssp_master - device.platक्रमm_data क्रम SPI controller devices.
 * @bus_id: identअगरier क्रम this bus
 * @enable_dma: अगर true enables DMA driven transfers.
 * @dma_rx_param: parameter to locate an RX DMA channel.
 * @dma_tx_param: parameter to locate a TX DMA channel.
 * @स्वतःsuspend_delay: delay in ms following transfer completion beक्रमe the
 *     runसमय घातer management प्रणाली suspends the device. A setting of 0
 *     indicates no delay and the device will be suspended immediately.
 * @rt: indicates the controller should run the message pump with realसमय
 *     priority to minimise the transfer latency on the bus.
 */
काष्ठा pl022_ssp_controller अणु
	u16 bus_id;
	u8 enable_dma:1;
	bool (*dma_filter)(काष्ठा dma_chan *chan, व्योम *filter_param);
	व्योम *dma_rx_param;
	व्योम *dma_tx_param;
	पूर्णांक स्वतःsuspend_delay;
	bool rt;
पूर्ण;

/**
 * काष्ठा ssp_config_chip - spi_board_info.controller_data क्रम SPI
 * slave devices, copied to spi_device.controller_data.
 *
 * @अगरace: Interface type(Motorola, TI, Microwire, Universal)
 * @hierarchy: sets whether पूर्णांकerface is master or slave
 * @slave_tx_disable: SSPTXD is disconnected (in slave mode only)
 * @clk_freq: Tune freq parameters of SSP(when in master mode)
 * @com_mode: communication mode: polling, Interrupt or DMA
 * @rx_lev_trig: Rx FIFO watermark level (क्रम IT & DMA mode)
 * @tx_lev_trig: Tx FIFO watermark level (क्रम IT & DMA mode)
 * @ctrl_len: Microwire पूर्णांकerface: Control length
 * @रुको_state: Microwire पूर्णांकerface: Wait state
 * @duplex: Microwire पूर्णांकerface: Full/Half duplex
 * @clkdelay: on the PL023 variant, the delay in feeback घड़ी cycles
 * beक्रमe sampling the incoming line
 */
काष्ठा pl022_config_chip अणु
	क्रमागत ssp_पूर्णांकerface अगरace;
	क्रमागत ssp_hierarchy hierarchy;
	bool slave_tx_disable;
	काष्ठा ssp_घड़ी_params clk_freq;
	क्रमागत ssp_mode com_mode;
	क्रमागत ssp_rx_level_trig rx_lev_trig;
	क्रमागत ssp_tx_level_trig tx_lev_trig;
	क्रमागत ssp_microwire_ctrl_len ctrl_len;
	क्रमागत ssp_microwire_रुको_state रुको_state;
	क्रमागत ssp_duplex duplex;
	क्रमागत ssp_clkdelay clkdelay;
पूर्ण;

#पूर्ण_अगर /* _SSP_PL022_H */
