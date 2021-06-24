<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित __IA_CSS_IRQ_H
#घोषणा __IA_CSS_IRQ_H

/* @file
 * This file contains inक्रमmation क्रम Interrupts/IRQs from CSS
 */

#समावेश "ia_css_err.h"
#समावेश "ia_css_pipe_public.h"
#समावेश "ia_css_input_port.h"

/* Interrupt types, these क्रमागतerate all supported पूर्णांकerrupt types.
 */
क्रमागत ia_css_irq_type अणु
	IA_CSS_IRQ_TYPE_EDGE,  /** Edge (level) sensitive पूर्णांकerrupt */
	IA_CSS_IRQ_TYPE_PULSE  /** Pulse-shaped पूर्णांकerrupt */
पूर्ण;

/* Interrupt request type.
 *  When the CSS hardware generates an पूर्णांकerrupt, a function in this API
 *  needs to be called to retrieve inक्रमmation about the पूर्णांकerrupt.
 *  This पूर्णांकerrupt type is part of this inक्रमmation and indicates what
 *  type of inक्रमmation the पूर्णांकerrupt संकेतs.
 *
 *  Note that one पूर्णांकerrupt can carry multiple पूर्णांकerrupt types. For
 *  example: the online video ISP will generate only 2 पूर्णांकerrupts, one to
 *  संकेत that the statistics (3a and DIS) are पढ़ोy and one to संकेत
 *  that all output frames are करोne (output and viewfinder).
 *
 * DEPRECATED, this पूर्णांकerface is not portable it should only define user
 * (SW) पूर्णांकerrupts
 */
क्रमागत ia_css_irq_info अणु
	IA_CSS_IRQ_INFO_CSS_RECEIVER_ERROR            = 1 << 0,
	/** the css receiver has encountered an error */
	IA_CSS_IRQ_INFO_CSS_RECEIVER_FIFO_OVERFLOW    = 1 << 1,
	/** the FIFO in the csi receiver has overflown */
	IA_CSS_IRQ_INFO_CSS_RECEIVER_SOF              = 1 << 2,
	/** the css receiver received the start of frame */
	IA_CSS_IRQ_INFO_CSS_RECEIVER_खातापूर्ण              = 1 << 3,
	/** the css receiver received the end of frame */
	IA_CSS_IRQ_INFO_CSS_RECEIVER_SOL              = 1 << 4,
	/** the css receiver received the start of line */
	IA_CSS_IRQ_INFO_EVENTS_READY                  = 1 << 5,
	/** One or more events are available in the PSYS event queue */
	IA_CSS_IRQ_INFO_CSS_RECEIVER_EOL              = 1 << 6,
	/** the css receiver received the end of line */
	IA_CSS_IRQ_INFO_CSS_RECEIVER_SIDEBAND_CHANGED = 1 << 7,
	/** the css receiver received a change in side band संकेतs */
	IA_CSS_IRQ_INFO_CSS_RECEIVER_GEN_SHORT_0      = 1 << 8,
	/** generic लघु packets (0) */
	IA_CSS_IRQ_INFO_CSS_RECEIVER_GEN_SHORT_1      = 1 << 9,
	/** generic लघु packets (1) */
	IA_CSS_IRQ_INFO_IF_PRIM_ERROR                 = 1 << 10,
	/** the primary input क्रमmatter (A) has encountered an error */
	IA_CSS_IRQ_INFO_IF_PRIM_B_ERROR               = 1 << 11,
	/** the primary input क्रमmatter (B) has encountered an error */
	IA_CSS_IRQ_INFO_IF_SEC_ERROR                  = 1 << 12,
	/** the secondary input क्रमmatter has encountered an error */
	IA_CSS_IRQ_INFO_STREAM_TO_MEM_ERROR           = 1 << 13,
	/** the stream-to-memory device has encountered an error */
	IA_CSS_IRQ_INFO_SW_0                          = 1 << 14,
	/** software पूर्णांकerrupt 0 */
	IA_CSS_IRQ_INFO_SW_1                          = 1 << 15,
	/** software पूर्णांकerrupt 1 */
	IA_CSS_IRQ_INFO_SW_2                          = 1 << 16,
	/** software पूर्णांकerrupt 2 */
	IA_CSS_IRQ_INFO_ISP_BINARY_STATISTICS_READY   = 1 << 17,
	/** ISP binary statistics are पढ़ोy */
	IA_CSS_IRQ_INFO_INPUT_SYSTEM_ERROR            = 1 << 18,
	/** the input प्रणाली in in error */
	IA_CSS_IRQ_INFO_IF_ERROR                      = 1 << 19,
	/** the input क्रमmatter in in error */
	IA_CSS_IRQ_INFO_DMA_ERROR                     = 1 << 20,
	/** the dma in in error */
	IA_CSS_IRQ_INFO_ISYS_EVENTS_READY             = 1 << 21,
	/** end-of-frame events are पढ़ोy in the isys_event queue */
पूर्ण;

/* CSS receiver error types. Whenever the CSS receiver has encountered
 *  an error, this क्रमागतeration is used to indicate which errors have occurred.
 *
 *  Note that multiple error flags can be enabled at once and that this is in
 *  fact common (whenever an error occurs, it usually results in multiple
 *  errors).
 *
 * DEPRECATED: This पूर्णांकerface is not portable, dअगरferent प्रणालीs have
 * dअगरferent receiver types, or possibly none in हाल of tests प्रणालीs.
 */
क्रमागत ia_css_rx_irq_info अणु
	IA_CSS_RX_IRQ_INFO_BUFFER_OVERRUN   = 1U << 0, /** buffer overrun */
	IA_CSS_RX_IRQ_INFO_ENTER_SLEEP_MODE = 1U << 1, /** entering sleep mode */
	IA_CSS_RX_IRQ_INFO_EXIT_SLEEP_MODE  = 1U << 2, /** निकासed sleep mode */
	IA_CSS_RX_IRQ_INFO_ECC_CORRECTED    = 1U << 3, /** ECC corrected */
	IA_CSS_RX_IRQ_INFO_ERR_SOT          = 1U << 4,
	/** Start of transmission */
	IA_CSS_RX_IRQ_INFO_ERR_SOT_SYNC     = 1U << 5, /** SOT sync (??) */
	IA_CSS_RX_IRQ_INFO_ERR_CONTROL      = 1U << 6, /** Control (??) */
	IA_CSS_RX_IRQ_INFO_ERR_ECC_DOUBLE   = 1U << 7, /** Double ECC */
	IA_CSS_RX_IRQ_INFO_ERR_CRC          = 1U << 8, /** CRC error */
	IA_CSS_RX_IRQ_INFO_ERR_UNKNOWN_ID   = 1U << 9, /** Unknown ID */
	IA_CSS_RX_IRQ_INFO_ERR_FRAME_SYNC   = 1U << 10,/** Frame sync error */
	IA_CSS_RX_IRQ_INFO_ERR_FRAME_DATA   = 1U << 11,/** Frame data error */
	IA_CSS_RX_IRQ_INFO_ERR_DATA_TIMEOUT = 1U << 12,/** Timeout occurred */
	IA_CSS_RX_IRQ_INFO_ERR_UNKNOWN_ESC  = 1U << 13,/** Unknown escape seq. */
	IA_CSS_RX_IRQ_INFO_ERR_LINE_SYNC    = 1U << 14,/** Line Sync error */
	IA_CSS_RX_IRQ_INFO_INIT_TIMEOUT     = 1U << 15,
पूर्ण;

/* Interrupt info काष्ठाure. This काष्ठाure contains inक्रमmation about an
 *  पूर्णांकerrupt. This needs to be used after an पूर्णांकerrupt is received on the IA
 *  to perक्रमm the correct action.
 */
काष्ठा ia_css_irq अणु
	क्रमागत ia_css_irq_info type; /** Interrupt type. */
	अचिन्हित पूर्णांक sw_irq_0_val; /** In हाल of SW पूर्णांकerrupt 0, value. */
	अचिन्हित पूर्णांक sw_irq_1_val; /** In हाल of SW पूर्णांकerrupt 1, value. */
	अचिन्हित पूर्णांक sw_irq_2_val; /** In हाल of SW पूर्णांकerrupt 2, value. */
	काष्ठा ia_css_pipe *pipe;
	/** The image pipe that generated the पूर्णांकerrupt. */
पूर्ण;

/* @brief Obtain पूर्णांकerrupt inक्रमmation.
 *
 * @param[out] info	Poपूर्णांकer to the पूर्णांकerrupt info. The पूर्णांकerrupt
 *			inक्रमmation wil be written to this info.
 * @वापस		If an error is encountered during the पूर्णांकerrupt info
 *			and no पूर्णांकerrupt could be translated successfully, this
 *			will वापस IA_CSS_INTERNAL_ERROR. Otherwise
 *			0.
 *
 * This function is expected to be executed after an पूर्णांकerrupt has been sent
 * to the IA from the CSS. This function वापसs inक्रमmation about the पूर्णांकerrupt
 * which is needed by the IA code to properly handle the पूर्णांकerrupt. This
 * inक्रमmation includes the image pipe, buffer type etc.
 */
पूर्णांक
ia_css_irq_translate(अचिन्हित पूर्णांक *info);

/* @brief Get CSI receiver error info.
 *
 * @param[out] irq_bits	Poपूर्णांकer to the पूर्णांकerrupt bits. The पूर्णांकerrupt
 *			bits will be written this info.
 *			This will be the error bits that are enabled in the CSI
 *			receiver error रेजिस्टर.
 * @वापस	None
 *
 * This function should be used whenever a CSI receiver error पूर्णांकerrupt is
 * generated. It provides the detailed inक्रमmation (bits) on the exact error
 * that occurred.
 *
 *@deprecated अणुthis function is DEPRECATED since it only works on CSI port 1.
 * Use the function below instead and specअगरy the appropriate port.पूर्ण
 */
व्योम
ia_css_rx_get_irq_info(अचिन्हित पूर्णांक *irq_bits);

/* @brief Get CSI receiver error info.
 *
 * @param[in]  port     Input port identअगरier.
 * @param[out] irq_bits	Poपूर्णांकer to the पूर्णांकerrupt bits. The पूर्णांकerrupt
 *			bits will be written this info.
 *			This will be the error bits that are enabled in the CSI
 *			receiver error रेजिस्टर.
 * @वापस	None
 *
 * This function should be used whenever a CSI receiver error पूर्णांकerrupt is
 * generated. It provides the detailed inक्रमmation (bits) on the exact error
 * that occurred.
 */
व्योम
ia_css_rx_port_get_irq_info(क्रमागत mipi_port_id port, अचिन्हित पूर्णांक *irq_bits);

/* @brief Clear CSI receiver error info.
 *
 * @param[in] irq_bits	The bits that should be cleared from the CSI receiver
 *			पूर्णांकerrupt bits रेजिस्टर.
 * @वापस	None
 *
 * This function should be called after ia_css_rx_get_irq_info has been called
 * and the error bits have been पूर्णांकerpreted. It is advised to use the वापस
 * value of that function as the argument to this function to make sure no new
 * error bits get overwritten.
 *
 * @deprecatedअणुthis function is DEPRECATED since it only works on CSI port 1.
 * Use the function below instead and specअगरy the appropriate port.पूर्ण
 */
व्योम
ia_css_rx_clear_irq_info(अचिन्हित पूर्णांक irq_bits);

/* @brief Clear CSI receiver error info.
 *
 * @param[in] port      Input port identअगरier.
 * @param[in] irq_bits	The bits that should be cleared from the CSI receiver
 *			पूर्णांकerrupt bits रेजिस्टर.
 * @वापस	None
 *
 * This function should be called after ia_css_rx_get_irq_info has been called
 * and the error bits have been पूर्णांकerpreted. It is advised to use the वापस
 * value of that function as the argument to this function to make sure no new
 * error bits get overwritten.
 */
व्योम
ia_css_rx_port_clear_irq_info(क्रमागत mipi_port_id port, अचिन्हित पूर्णांक irq_bits);

/* @brief Enable or disable specअगरic पूर्णांकerrupts.
 *
 * @param[in] type	The पूर्णांकerrupt type that will be enabled/disabled.
 * @param[in] enable	enable or disable.
 * @वापस		Returns IA_CSS_INTERNAL_ERROR अगर this पूर्णांकerrupt
 *			type cannot be enabled/disabled which is true क्रम
 *			CSS पूर्णांकernal पूर्णांकerrupts. Otherwise वापसs
 *			0.
 */
पूर्णांक
ia_css_irq_enable(क्रमागत ia_css_irq_info type, bool enable);

#पूर्ण_अगर /* __IA_CSS_IRQ_H */
