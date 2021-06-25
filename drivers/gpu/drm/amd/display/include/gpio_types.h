<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#अगर_अघोषित __DAL_GPIO_TYPES_H__
#घोषणा __DAL_GPIO_TYPES_H__

#घोषणा BUNDLE_A_MASK 0x00FFF000L
#घोषणा BUNDLE_B_MASK 0x00000FFFL

/*
 * gpio_result
 *
 * @brief
 * The possible वापस codes that the GPIO object can वापस.
 * These वापस codes can be generated
 * directly by the GPIO object or from the GPIOPin object.
 */
क्रमागत gpio_result अणु
	GPIO_RESULT_OK,
	GPIO_RESULT_शून्य_HANDLE,
	GPIO_RESULT_INVALID_DATA,
	GPIO_RESULT_DEVICE_BUSY,
	GPIO_RESULT_OPEN_FAILED,
	GPIO_RESULT_ALREADY_OPENED,
	GPIO_RESULT_NON_SPECIFIC_ERROR
पूर्ण;

/*
 * @brief
 * Used to identअगरy the specअगरic GPIO device
 *
 * @notes
 * These स्थिरants are used as indices in a vector.
 * Thus they should start from zero and be contiguous.
 */
क्रमागत gpio_id अणु
	GPIO_ID_UNKNOWN = (-1),
	GPIO_ID_DDC_DATA,
	GPIO_ID_DDC_CLOCK,
	GPIO_ID_GENERIC,
	GPIO_ID_HPD,
	GPIO_ID_GPIO_PAD,
	GPIO_ID_VIP_PAD,
	GPIO_ID_SYNC,
	GPIO_ID_GSL, /* global swap lock */
	GPIO_ID_COUNT,
	GPIO_ID_MIN = GPIO_ID_DDC_DATA,
	GPIO_ID_MAX = GPIO_ID_GSL
पूर्ण;

#घोषणा GPIO_ENUM_UNKNOWN \
	32

काष्ठा gpio_pin_info अणु
	uपूर्णांक32_t offset;
	uपूर्णांक32_t offset_y;
	uपूर्णांक32_t offset_en;
	uपूर्णांक32_t offset_mask;

	uपूर्णांक32_t mask;
	uपूर्णांक32_t mask_y;
	uपूर्णांक32_t mask_en;
	uपूर्णांक32_t mask_mask;
पूर्ण;

क्रमागत gpio_pin_output_state अणु
	GPIO_PIN_OUTPUT_STATE_ACTIVE_LOW,
	GPIO_PIN_OUTPUT_STATE_ACTIVE_HIGH,
	GPIO_PIN_OUTPUT_STATE_DEFAULT = GPIO_PIN_OUTPUT_STATE_ACTIVE_LOW
पूर्ण;

क्रमागत gpio_generic अणु
	GPIO_GENERIC_UNKNOWN = (-1),
	GPIO_GENERIC_A,
	GPIO_GENERIC_B,
	GPIO_GENERIC_C,
	GPIO_GENERIC_D,
	GPIO_GENERIC_E,
	GPIO_GENERIC_F,
	GPIO_GENERIC_G,
	GPIO_GENERIC_COUNT,
	GPIO_GENERIC_MIN = GPIO_GENERIC_A,
	GPIO_GENERIC_MAX = GPIO_GENERIC_B
पूर्ण;

क्रमागत gpio_hpd अणु
	GPIO_HPD_UNKNOWN = (-1),
	GPIO_HPD_1,
	GPIO_HPD_2,
	GPIO_HPD_3,
	GPIO_HPD_4,
	GPIO_HPD_5,
	GPIO_HPD_6,
	GPIO_HPD_COUNT,
	GPIO_HPD_MIN = GPIO_HPD_1,
	GPIO_HPD_MAX = GPIO_HPD_6
पूर्ण;

क्रमागत gpio_gpio_pad अणु
	GPIO_GPIO_PAD_UNKNOWN = (-1),
	GPIO_GPIO_PAD_0,
	GPIO_GPIO_PAD_1,
	GPIO_GPIO_PAD_2,
	GPIO_GPIO_PAD_3,
	GPIO_GPIO_PAD_4,
	GPIO_GPIO_PAD_5,
	GPIO_GPIO_PAD_6,
	GPIO_GPIO_PAD_7,
	GPIO_GPIO_PAD_8,
	GPIO_GPIO_PAD_9,
	GPIO_GPIO_PAD_10,
	GPIO_GPIO_PAD_11,
	GPIO_GPIO_PAD_12,
	GPIO_GPIO_PAD_13,
	GPIO_GPIO_PAD_14,
	GPIO_GPIO_PAD_15,
	GPIO_GPIO_PAD_16,
	GPIO_GPIO_PAD_17,
	GPIO_GPIO_PAD_18,
	GPIO_GPIO_PAD_19,
	GPIO_GPIO_PAD_20,
	GPIO_GPIO_PAD_21,
	GPIO_GPIO_PAD_22,
	GPIO_GPIO_PAD_23,
	GPIO_GPIO_PAD_24,
	GPIO_GPIO_PAD_25,
	GPIO_GPIO_PAD_26,
	GPIO_GPIO_PAD_27,
	GPIO_GPIO_PAD_28,
	GPIO_GPIO_PAD_29,
	GPIO_GPIO_PAD_30,
	GPIO_GPIO_PAD_COUNT,
	GPIO_GPIO_PAD_MIN = GPIO_GPIO_PAD_0,
	GPIO_GPIO_PAD_MAX = GPIO_GPIO_PAD_30
पूर्ण;

क्रमागत gpio_vip_pad अणु
	GPIO_VIP_PAD_UNKNOWN = (-1),
	/* following never used -
	 * GPIO_ID_DDC_CLOCK::GPIO_DDC_LINE_VIP_PAD defined instead */
	GPIO_VIP_PAD_SCL,
	/* following never used -
	 * GPIO_ID_DDC_DATA::GPIO_DDC_LINE_VIP_PAD defined instead */
	GPIO_VIP_PAD_SDA,
	GPIO_VIP_PAD_VHAD,
	GPIO_VIP_PAD_VPHCTL,
	GPIO_VIP_PAD_VIPCLK,
	GPIO_VIP_PAD_VID,
	GPIO_VIP_PAD_VPCLK0,
	GPIO_VIP_PAD_DVALID,
	GPIO_VIP_PAD_PSYNC,
	GPIO_VIP_PAD_COUNT,
	GPIO_VIP_PAD_MIN = GPIO_VIP_PAD_SCL,
	GPIO_VIP_PAD_MAX = GPIO_VIP_PAD_PSYNC
पूर्ण;

क्रमागत gpio_sync अणु
	GPIO_SYNC_UNKNOWN = (-1),
	GPIO_SYNC_HSYNC_A,
	GPIO_SYNC_VSYNC_A,
	GPIO_SYNC_HSYNC_B,
	GPIO_SYNC_VSYNC_B,
	GPIO_SYNC_COUNT,
	GPIO_SYNC_MIN = GPIO_SYNC_HSYNC_A,
	GPIO_SYNC_MAX = GPIO_SYNC_VSYNC_B
पूर्ण;

क्रमागत gpio_gsl अणु
	GPIO_GSL_UNKNOWN = (-1),
	GPIO_GSL_GENLOCK_CLOCK,
	GPIO_GSL_GENLOCK_VSYNC,
	GPIO_GSL_SWAPLOCK_A,
	GPIO_GSL_SWAPLOCK_B,
	GPIO_GSL_COUNT,
	GPIO_GSL_MIN = GPIO_GSL_GENLOCK_CLOCK,
	GPIO_GSL_MAX = GPIO_GSL_SWAPLOCK_B
पूर्ण;

/*
 * @brief
 * Unique Id क्रम DDC handle.
 * Values are meaningful (used as indexes to array)
 */
क्रमागत gpio_ddc_line अणु
	GPIO_DDC_LINE_UNKNOWN = (-1),
	GPIO_DDC_LINE_DDC1,
	GPIO_DDC_LINE_DDC2,
	GPIO_DDC_LINE_DDC3,
	GPIO_DDC_LINE_DDC4,
	GPIO_DDC_LINE_DDC5,
	GPIO_DDC_LINE_DDC6,
	GPIO_DDC_LINE_DDC_VGA,
	GPIO_DDC_LINE_VIP_PAD,
	GPIO_DDC_LINE_I2C_PAD = GPIO_DDC_LINE_VIP_PAD,
	GPIO_DDC_LINE_COUNT,
	GPIO_DDC_LINE_MIN = GPIO_DDC_LINE_DDC1,
	GPIO_DDC_LINE_MAX = GPIO_DDC_LINE_I2C_PAD
पूर्ण;

/*
 * @brief
 * Identअगरies the mode of operation to खोलो a GPIO device.
 * A GPIO device (pin) can be programmed in only one of these modes at a समय.
 */
क्रमागत gpio_mode अणु
	GPIO_MODE_UNKNOWN = (-1),
	GPIO_MODE_INPUT,
	GPIO_MODE_OUTPUT,
	GPIO_MODE_FAST_OUTPUT,
	GPIO_MODE_HARDWARE,
	GPIO_MODE_INTERRUPT
पूर्ण;

/*
 * @brief
 * Identअगरies the source of the संकेत when GPIO is in HW mode.
 * get_संकेत_source() will वापस GPIO_SYGNAL_SOURCE__UNKNOWN
 * when one of the following holds:
 *    1. GPIO is input GPIO
 *    2. GPIO is not खोलोed in HW mode
 *    3. GPIO करोes not have fixed संकेत source
 *    (like DC_GenericA have mux instead fixed)
 */
क्रमागत gpio_संकेत_source अणु
	GPIO_SIGNAL_SOURCE_UNKNOWN = (-1),
	GPIO_SIGNAL_SOURCE_DACA_STEREO_SYNC,
	GPIO_SIGNAL_SOURCE_PASS_THROUGH_STEREO_SYNC,
	GPIO_SIGNAL_SOURCE_DACB_STEREO_SYNC,
	GPIO_SIGNAL_SOURCE_DACA_HSYNC,
	GPIO_SIGNAL_SOURCE_DACB_HSYNC,
	GPIO_SIGNAL_SOURCE_DACA_VSYNC,
	GPIO_SIGNAL_SOURCE_DACB_VSYNC,
पूर्ण;

क्रमागत gpio_stereo_source अणु
	GPIO_STEREO_SOURCE_UNKNOWN = (-1),
	GPIO_STEREO_SOURCE_D1,
	GPIO_STEREO_SOURCE_D2,
	GPIO_STEREO_SOURCE_D3,
	GPIO_STEREO_SOURCE_D4,
	GPIO_STEREO_SOURCE_D5,
	GPIO_STEREO_SOURCE_D6
पूर्ण;

/*
 * GPIO config
 */

क्रमागत gpio_config_type अणु
	GPIO_CONFIG_TYPE_NONE,
	GPIO_CONFIG_TYPE_DDC,
	GPIO_CONFIG_TYPE_HPD,
	GPIO_CONFIG_TYPE_GENERIC_MUX,
	GPIO_CONFIG_TYPE_GSL_MUX,
	GPIO_CONFIG_TYPE_I2C_AUX_DUAL_MODE
पूर्ण;

/* DDC configuration */

क्रमागत gpio_ddc_config_type अणु
	GPIO_DDC_CONFIG_TYPE_MODE_AUX,
	GPIO_DDC_CONFIG_TYPE_MODE_I2C,
	GPIO_DDC_CONFIG_TYPE_POLL_FOR_CONNECT,
	GPIO_DDC_CONFIG_TYPE_POLL_FOR_DISCONNECT,
	GPIO_DDC_CONFIG_TYPE_DISABLE_POLLING
पूर्ण;

काष्ठा gpio_ddc_config अणु
	क्रमागत gpio_ddc_config_type type;
	bool data_en_bit_present;
	bool घड़ी_en_bit_present;
पूर्ण;

/* HPD configuration */

काष्ठा gpio_hpd_config अणु
	uपूर्णांक32_t delay_on_connect; /* milliseconds */
	uपूर्णांक32_t delay_on_disconnect; /* milliseconds */
पूर्ण;

काष्ठा gpio_generic_mux_config अणु
	bool enable_output_from_mux;
	क्रमागत gpio_संकेत_source mux_select;
	क्रमागत gpio_stereo_source stereo_select;
पूर्ण;

क्रमागत gpio_gsl_mux_config_type अणु
	GPIO_GSL_MUX_CONFIG_TYPE_DISABLE,
	GPIO_GSL_MUX_CONFIG_TYPE_TIMING_SYNC,
	GPIO_GSL_MUX_CONFIG_TYPE_FLIP_SYNC
पूर्ण;

काष्ठा gpio_gsl_mux_config अणु
	क्रमागत gpio_gsl_mux_config_type type;
	/* Actually sync_source type,
	 * however we want to aव्योम पूर्णांकer-component includes here */
	uपूर्णांक32_t gsl_group;
पूर्ण;

काष्ठा gpio_config_data अणु
	क्रमागत gpio_config_type type;
	जोड़ अणु
		काष्ठा gpio_ddc_config ddc;
		काष्ठा gpio_hpd_config hpd;
		काष्ठा gpio_generic_mux_config generic_mux;
		काष्ठा gpio_gsl_mux_config gsl_mux;
	पूर्ण config;
पूर्ण;

#पूर्ण_अगर
