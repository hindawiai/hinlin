<शैली गुरु>
/*
 * Copyright 2012 Advanced Micro Devices, Inc.
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
 */

#अगर_अघोषित AMD_ACPI_H
#घोषणा AMD_ACPI_H

#घोषणा ACPI_AC_CLASS           "ac_adapter"

काष्ठा atअगर_verअगरy_पूर्णांकerface अणु
	u16 size;		/* काष्ठाure size in bytes (includes size field) */
	u16 version;		/* version */
	u32 notअगरication_mask;	/* supported notअगरications mask */
	u32 function_bits;	/* supported functions bit vector */
पूर्ण __packed;

काष्ठा atअगर_प्रणाली_params अणु
	u16 size;		/* काष्ठाure size in bytes (includes size field) */
	u32 valid_mask;		/* valid flags mask */
	u32 flags;		/* flags */
	u8 command_code;	/* notअगरy command code */
पूर्ण __packed;

काष्ठा atअगर_sbios_requests अणु
	u16 size;		/* काष्ठाure size in bytes (includes size field) */
	u32 pending;		/* pending sbios requests */
	u8 panel_exp_mode;	/* panel expansion mode */
	u8 thermal_gfx;		/* thermal state: target gfx controller */
	u8 thermal_state;	/* thermal state: state id (0: निकास state, non-0: state) */
	u8 क्रमced_घातer_gfx;	/* क्रमced घातer state: target gfx controller */
	u8 क्रमced_घातer_state;	/* क्रमced घातer state: state id */
	u8 प्रणाली_घातer_src;	/* प्रणाली घातer source */
	u8 backlight_level;	/* panel backlight level (0-255) */
पूर्ण __packed;

काष्ठा atअगर_qbtc_arguments अणु
	u16 size;		/* काष्ठाure size in bytes (includes size field) */
	u8 requested_display;	/* which display is requested */
पूर्ण __packed;

#घोषणा ATIF_QBTC_MAX_DATA_POINTS 99

काष्ठा atअगर_qbtc_data_poपूर्णांक अणु
	u8 luminance;		/* luminance in percent */
	u8 ipnut_संकेत;	/* input संकेत in range 0-255 */
पूर्ण __packed;

काष्ठा atअगर_qbtc_output अणु
	u16 size;		/* काष्ठाure size in bytes (includes size field) */
	u16 flags;		/* all zeroes */
	u8 error_code;		/* error code */
	u8 ac_level;		/* शेष brightness on AC घातer */
	u8 dc_level;		/* शेष brightness on DC घातer */
	u8 min_input_संकेत;	/* max input संकेत in range 0-255 */
	u8 max_input_संकेत;	/* min input संकेत in range 0-255 */
	u8 number_of_poपूर्णांकs;	/* number of data poपूर्णांकs */
	काष्ठा atअगर_qbtc_data_poपूर्णांक data_poपूर्णांकs[ATIF_QBTC_MAX_DATA_POINTS];
पूर्ण __packed;

#घोषणा ATIF_NOTIFY_MASK	0x3
#घोषणा ATIF_NOTIFY_NONE	0
#घोषणा ATIF_NOTIFY_81		1
#घोषणा ATIF_NOTIFY_N		2

काष्ठा atcs_verअगरy_पूर्णांकerface अणु
	u16 size;		/* काष्ठाure size in bytes (includes size field) */
	u16 version;		/* version */
	u32 function_bits;	/* supported functions bit vector */
पूर्ण __packed;

#घोषणा ATCS_VALID_FLAGS_MASK	0x3

काष्ठा atcs_pref_req_input अणु
	u16 size;		/* काष्ठाure size in bytes (includes size field) */
	u16 client_id;		/* client id (bit 2-0: func num, 7-3: dev num, 15-8: bus num) */
	u16 valid_flags_mask;	/* valid flags mask */
	u16 flags;		/* flags */
	u8 req_type;		/* request type */
	u8 perf_req;		/* perक्रमmance request */
पूर्ण __packed;

काष्ठा atcs_pref_req_output अणु
	u16 size;		/* काष्ठाure size in bytes (includes size field) */
	u8 ret_val;		/* वापस value */
पूर्ण __packed;

/* AMD hw uses four ACPI control methods:
 * 1. ATIF
 * ARG0: (ACPI_INTEGER) function code
 * ARG1: (ACPI_BUFFER) parameter buffer, 256 bytes
 * OUTPUT: (ACPI_BUFFER) output buffer, 256 bytes
 * ATIF provides an entry poपूर्णांक क्रम the gfx driver to पूर्णांकeract with the sbios.
 * The AMD ACPI notअगरication mechanism uses Notअगरy (VGA, 0x81) or a custom
 * notअगरication. Which notअगरication is used as indicated by the ATIF Control
 * Method GET_SYSTEM_PARAMETERS. When the driver receives Notअगरy (VGA, 0x81) or
 * a custom notअगरication it invokes ATIF Control Method GET_SYSTEM_BIOS_REQUESTS
 * to identअगरy pending System BIOS requests and associated parameters. For
 * example, अगर one of the pending requests is DISPLAY_SWITCH_REQUEST, the driver
 * will perक्रमm display device detection and invoke ATIF Control Method
 * SELECT_ACTIVE_DISPLAYS.
 *
 * 2. ATPX
 * ARG0: (ACPI_INTEGER) function code
 * ARG1: (ACPI_BUFFER) parameter buffer, 256 bytes
 * OUTPUT: (ACPI_BUFFER) output buffer, 256 bytes
 * ATPX methods are used on PowerXpress प्रणालीs to handle mux चयनing and
 * discrete GPU घातer control.
 *
 * 3. ATRM
 * ARG0: (ACPI_INTEGER) offset of vbios rom data
 * ARG1: (ACPI_BUFFER) size of the buffer to fill (up to 4K).
 * OUTPUT: (ACPI_BUFFER) output buffer
 * ATRM provides an पूर्णांकerfacess to access the discrete GPU vbios image on
 * PowerXpress प्रणालीs with multiple GPUs.
 *
 * 4. ATCS
 * ARG0: (ACPI_INTEGER) function code
 * ARG1: (ACPI_BUFFER) parameter buffer, 256 bytes
 * OUTPUT: (ACPI_BUFFER) output buffer, 256 bytes
 * ATCS provides an पूर्णांकerface to AMD chipset specअगरic functionality.
 *
 */
/* ATIF */
#घोषणा ATIF_FUNCTION_VERIFY_INTERFACE                             0x0
/* ARG0: ATIF_FUNCTION_VERIFY_INTERFACE
 * ARG1: none
 * OUTPUT:
 * WORD  - काष्ठाure size in bytes (includes size field)
 * WORD  - version
 * DWORD - supported notअगरications mask
 * DWORD - supported functions bit vector
 */
/* Notअगरications mask */
#       define ATIF_THERMAL_STATE_CHANGE_REQUEST_SUPPORTED         (1 << 2)
#       define ATIF_FORCED_POWER_STATE_CHANGE_REQUEST_SUPPORTED    (1 << 3)
#       define ATIF_SYSTEM_POWER_SOURCE_CHANGE_REQUEST_SUPPORTED   (1 << 4)
#       define ATIF_PANEL_BRIGHTNESS_CHANGE_REQUEST_SUPPORTED      (1 << 7)
#       define ATIF_DGPU_DISPLAY_EVENT_SUPPORTED                   (1 << 8)
#       define ATIF_GPU_PACKAGE_POWER_LIMIT_REQUEST_SUPPORTED      (1 << 12)
/* supported functions vector */
#       define ATIF_GET_SYSTEM_PARAMETERS_SUPPORTED               (1 << 0)
#       define ATIF_GET_SYSTEM_BIOS_REQUESTS_SUPPORTED            (1 << 1)
#       define ATIF_TEMPERATURE_CHANGE_NOTIFICATION_SUPPORTED     (1 << 12)
#       define ATIF_QUERY_BACKLIGHT_TRANSFER_CHARACTERISTICS_SUPPORTED (1 << 15)
#       define ATIF_READY_TO_UNDOCK_NOTIFICATION_SUPPORTED        (1 << 16)
#       define ATIF_GET_EXTERNAL_GPU_INFORMATION_SUPPORTED        (1 << 20)
#घोषणा ATIF_FUNCTION_GET_SYSTEM_PARAMETERS                        0x1
/* ARG0: ATIF_FUNCTION_GET_SYSTEM_PARAMETERS
 * ARG1: none
 * OUTPUT:
 * WORD  - काष्ठाure size in bytes (includes size field)
 * DWORD - valid flags mask
 * DWORD - flags
 *
 * OR
 *
 * WORD  - काष्ठाure size in bytes (includes size field)
 * DWORD - valid flags mask
 * DWORD - flags
 * BYTE  - notअगरy command code
 *
 * flags
 * bits 1:0:
 * 0 - Notअगरy(VGA, 0x81) is not used क्रम notअगरication
 * 1 - Notअगरy(VGA, 0x81) is used क्रम notअगरication
 * 2 - Notअगरy(VGA, n) is used क्रम notअगरication where
 * n (0xd0-0xd9) is specअगरied in notअगरy command code.
 * bit 2:
 * 1 - lid changes not reported though पूर्णांक10
 * bit 3:
 * 1 - प्रणाली bios controls overघड़ीing
 * bit 4:
 * 1 - enable overघड़ीing
 */
#घोषणा ATIF_FUNCTION_GET_SYSTEM_BIOS_REQUESTS                     0x2
/* ARG0: ATIF_FUNCTION_GET_SYSTEM_BIOS_REQUESTS
 * ARG1: none
 * OUTPUT:
 * WORD  - काष्ठाure size in bytes (includes size field)
 * DWORD - pending sbios requests
 * BYTE  - reserved (all zeroes)
 * BYTE  - thermal state: target gfx controller
 * BYTE  - thermal state: state id (0: निकास state, non-0: state)
 * BYTE  - क्रमced घातer state: target gfx controller
 * BYTE  - क्रमced घातer state: state id (0: क्रमced state, non-0: state)
 * BYTE  - प्रणाली घातer source
 * BYTE  - panel backlight level (0-255)
 * BYTE  - GPU package घातer limit: target gfx controller
 * DWORD - GPU package घातer limit: value (24:8 fractional क्रमmat, Watts)
 */
/* pending sbios requests */
#       define ATIF_THERMAL_STATE_CHANGE_REQUEST                   (1 << 2)
#       define ATIF_FORCED_POWER_STATE_CHANGE_REQUEST              (1 << 3)
#       define ATIF_SYSTEM_POWER_SOURCE_CHANGE_REQUEST             (1 << 4)
#       define ATIF_PANEL_BRIGHTNESS_CHANGE_REQUEST                (1 << 7)
#       define ATIF_DGPU_DISPLAY_EVENT                             (1 << 8)
#       define ATIF_GPU_PACKAGE_POWER_LIMIT_REQUEST                (1 << 12)
/* target gfx controller */
#       define ATIF_TARGET_GFX_SINGLE                              0
#       define ATIF_TARGET_GFX_PX_IGPU                             1
#       define ATIF_TARGET_GFX_PX_DGPU                             2
/* प्रणाली घातer source */
#       define ATIF_POWER_SOURCE_AC                                1
#       define ATIF_POWER_SOURCE_DC                                2
#       define ATIF_POWER_SOURCE_RESTRICTED_AC_1                   3
#       define ATIF_POWER_SOURCE_RESTRICTED_AC_2                   4
#घोषणा ATIF_FUNCTION_TEMPERATURE_CHANGE_NOTIFICATION              0xD
/* ARG0: ATIF_FUNCTION_TEMPERATURE_CHANGE_NOTIFICATION
 * ARG1:
 * WORD  - काष्ठाure size in bytes (includes size field)
 * WORD  - gfx controller id
 * BYTE  - current temperature (degress Celsius)
 * OUTPUT: none
 */
#घोषणा ATIF_FUNCTION_QUERY_BRIGHTNESS_TRANSFER_CHARACTERISTICS    0x10
/* ARG0: ATIF_FUNCTION_QUERY_BRIGHTNESS_TRANSFER_CHARACTERISTICS
 * ARG1:
 * WORD  - काष्ठाure size in bytes (includes size field)
 * BYTE  - requested display
 * OUTPUT:
 * WORD  - काष्ठाure size in bytes (includes size field)
 * WORD  - flags (currently all 16 bits are reserved)
 * BYTE  - error code (on failure, disregard all below fields)
 * BYTE  - AC level (शेष brightness in percent when machine has full घातer)
 * BYTE  - DC level (शेष brightness in percent when machine is on battery)
 * BYTE  - min input संकेत, in range 0-255, corresponding to 0% backlight
 * BYTE  - max input संकेत, in range 0-255, corresponding to 100% backlight
 * BYTE  - number of reported data poपूर्णांकs
 * BYTE  - luminance level in percent  \ repeated काष्ठाure
 * BYTE  - input संकेत in range 0-255 / करोes not have entries क्रम 0% and 100%
 */
/* requested display */
#       define ATIF_QBTC_REQUEST_LCD1                              0
#       define ATIF_QBTC_REQUEST_CRT1                              1
#       define ATIF_QBTC_REQUEST_DFP1                              3
#       define ATIF_QBTC_REQUEST_CRT2                              4
#       define ATIF_QBTC_REQUEST_LCD2                              5
#       define ATIF_QBTC_REQUEST_DFP2                              7
#       define ATIF_QBTC_REQUEST_DFP3                              9
#       define ATIF_QBTC_REQUEST_DFP4                              10
#       define ATIF_QBTC_REQUEST_DFP5                              11
#       define ATIF_QBTC_REQUEST_DFP6                              12
/* error code */
#       define ATIF_QBTC_ERROR_CODE_SUCCESS                        0
#       define ATIF_QBTC_ERROR_CODE_FAILURE                        1
#       define ATIF_QBTC_ERROR_CODE_DEVICE_NOT_SUPPORTED           2
#घोषणा ATIF_FUNCTION_READY_TO_UNDOCK_NOTIFICATION                 0x11
/* ARG0: ATIF_FUNCTION_READY_TO_UNDOCK_NOTIFICATION
 * ARG1: none
 * OUTPUT: none
 */
#घोषणा ATIF_FUNCTION_GET_EXTERNAL_GPU_INFORMATION                 0x15
/* ARG0: ATIF_FUNCTION_GET_EXTERNAL_GPU_INFORMATION
 * ARG1: none
 * OUTPUT:
 * WORD  - number of reported बाह्यal gfx devices
 * WORD  - device काष्ठाure size in bytes (excludes device size field)
 * WORD  - flags         \
 * WORD  - bus number    / repeated काष्ठाure
 */
/* flags */
#       define ATIF_EXTERNAL_GRAPHICS_PORT                         (1 << 0)

/* ATPX */
#घोषणा ATPX_FUNCTION_VERIFY_INTERFACE                             0x0
/* ARG0: ATPX_FUNCTION_VERIFY_INTERFACE
 * ARG1: none
 * OUTPUT:
 * WORD  - काष्ठाure size in bytes (includes size field)
 * WORD  - version
 * DWORD - supported functions bit vector
 */
/* supported functions vector */
#       define ATPX_GET_PX_PARAMETERS_SUPPORTED                    (1 << 0)
#       define ATPX_POWER_CONTROL_SUPPORTED                        (1 << 1)
#       define ATPX_DISPLAY_MUX_CONTROL_SUPPORTED                  (1 << 2)
#       define ATPX_I2C_MUX_CONTROL_SUPPORTED                      (1 << 3)
#       define ATPX_GRAPHICS_DEVICE_SWITCH_START_NOTIFICATION_SUPPORTED (1 << 4)
#       define ATPX_GRAPHICS_DEVICE_SWITCH_END_NOTIFICATION_SUPPORTED   (1 << 5)
#       define ATPX_GET_DISPLAY_CONNECTORS_MAPPING_SUPPORTED       (1 << 7)
#       define ATPX_GET_DISPLAY_DETECTION_PORTS_SUPPORTED          (1 << 8)
#घोषणा ATPX_FUNCTION_GET_PX_PARAMETERS                            0x1
/* ARG0: ATPX_FUNCTION_GET_PX_PARAMETERS
 * ARG1: none
 * OUTPUT:
 * WORD  - काष्ठाure size in bytes (includes size field)
 * DWORD - valid flags mask
 * DWORD - flags
 */
/* flags */
#       define ATPX_LVDS_I2C_AVAILABLE_TO_BOTH_GPUS                (1 << 0)
#       define ATPX_CRT1_I2C_AVAILABLE_TO_BOTH_GPUS                (1 << 1)
#       define ATPX_DVI1_I2C_AVAILABLE_TO_BOTH_GPUS                (1 << 2)
#       define ATPX_CRT1_RGB_SIGNAL_MUXED                          (1 << 3)
#       define ATPX_TV_SIGNAL_MUXED                                (1 << 4)
#       define ATPX_DFP_SIGNAL_MUXED                               (1 << 5)
#       define ATPX_SEPARATE_MUX_FOR_I2C                           (1 << 6)
#       define ATPX_DYNAMIC_PX_SUPPORTED                           (1 << 7)
#       define ATPX_ACF_NOT_SUPPORTED                              (1 << 8)
#       define ATPX_FIXED_NOT_SUPPORTED                            (1 << 9)
#       define ATPX_DYNAMIC_DGPU_POWER_OFF_SUPPORTED               (1 << 10)
#       define ATPX_DGPU_REQ_POWER_FOR_DISPLAYS                    (1 << 11)
#       define ATPX_DGPU_CAN_DRIVE_DISPLAYS                        (1 << 12)
#       define ATPX_MS_HYBRID_GFX_SUPPORTED                        (1 << 14)
#घोषणा ATPX_FUNCTION_POWER_CONTROL                                0x2
/* ARG0: ATPX_FUNCTION_POWER_CONTROL
 * ARG1:
 * WORD  - काष्ठाure size in bytes (includes size field)
 * BYTE  - dGPU घातer state (0: घातer off, 1: घातer on)
 * OUTPUT: none
 */
#घोषणा ATPX_FUNCTION_DISPLAY_MUX_CONTROL                          0x3
/* ARG0: ATPX_FUNCTION_DISPLAY_MUX_CONTROL
 * ARG1:
 * WORD  - काष्ठाure size in bytes (includes size field)
 * WORD  - display mux control (0: iGPU, 1: dGPU)
 * OUTPUT: none
 */
#       define ATPX_INTEGRATED_GPU                                 0
#       define ATPX_DISCRETE_GPU                                   1
#घोषणा ATPX_FUNCTION_I2C_MUX_CONTROL                              0x4
/* ARG0: ATPX_FUNCTION_I2C_MUX_CONTROL
 * ARG1:
 * WORD  - काष्ठाure size in bytes (includes size field)
 * WORD  - i2c/aux/hpd mux control (0: iGPU, 1: dGPU)
 * OUTPUT: none
 */
#घोषणा ATPX_FUNCTION_GRAPHICS_DEVICE_SWITCH_START_NOTIFICATION    0x5
/* ARG0: ATPX_FUNCTION_GRAPHICS_DEVICE_SWITCH_START_NOTIFICATION
 * ARG1:
 * WORD  - काष्ठाure size in bytes (includes size field)
 * WORD  - target gpu (0: iGPU, 1: dGPU)
 * OUTPUT: none
 */
#घोषणा ATPX_FUNCTION_GRAPHICS_DEVICE_SWITCH_END_NOTIFICATION      0x6
/* ARG0: ATPX_FUNCTION_GRAPHICS_DEVICE_SWITCH_END_NOTIFICATION
 * ARG1:
 * WORD  - काष्ठाure size in bytes (includes size field)
 * WORD  - target gpu (0: iGPU, 1: dGPU)
 * OUTPUT: none
 */
#घोषणा ATPX_FUNCTION_GET_DISPLAY_CONNECTORS_MAPPING               0x8
/* ARG0: ATPX_FUNCTION_GET_DISPLAY_CONNECTORS_MAPPING
 * ARG1: none
 * OUTPUT:
 * WORD  - number of display connectors
 * WORD  - connector काष्ठाure size in bytes (excludes connector size field)
 * BYTE  - flags                                                     \
 * BYTE  - ATIF display vector bit position                           पूर्ण repeated
 * BYTE  - adapter id (0: iGPU, 1-n: dGPU ordered by pcie bus number) पूर्ण काष्ठाure
 * WORD  - connector ACPI id                                         /
 */
/* flags */
#       define ATPX_DISPLAY_OUTPUT_SUPPORTED_BY_ADAPTER_ID_DEVICE  (1 << 0)
#       define ATPX_DISPLAY_HPD_SUPPORTED_BY_ADAPTER_ID_DEVICE     (1 << 1)
#       define ATPX_DISPLAY_I2C_SUPPORTED_BY_ADAPTER_ID_DEVICE     (1 << 2)
#घोषणा ATPX_FUNCTION_GET_DISPLAY_DETECTION_PORTS                  0x9
/* ARG0: ATPX_FUNCTION_GET_DISPLAY_DETECTION_PORTS
 * ARG1: none
 * OUTPUT:
 * WORD  - number of HPD/DDC ports
 * WORD  - port काष्ठाure size in bytes (excludes port size field)
 * BYTE  - ATIF display vector bit position \
 * BYTE  - hpd id                            पूर्ण reapeated काष्ठाure
 * BYTE  - ddc id                           /
 *
 * available on A+A प्रणालीs only
 */
/* hpd id */
#       define ATPX_HPD_NONE                                       0
#       define ATPX_HPD1                                           1
#       define ATPX_HPD2                                           2
#       define ATPX_HPD3                                           3
#       define ATPX_HPD4                                           4
#       define ATPX_HPD5                                           5
#       define ATPX_HPD6                                           6
/* ddc id */
#       define ATPX_DDC_NONE                                       0
#       define ATPX_DDC1                                           1
#       define ATPX_DDC2                                           2
#       define ATPX_DDC3                                           3
#       define ATPX_DDC4                                           4
#       define ATPX_DDC5                                           5
#       define ATPX_DDC6                                           6
#       define ATPX_DDC7                                           7
#       define ATPX_DDC8                                           8

/* ATCS */
#घोषणा ATCS_FUNCTION_VERIFY_INTERFACE                             0x0
/* ARG0: ATCS_FUNCTION_VERIFY_INTERFACE
 * ARG1: none
 * OUTPUT:
 * WORD  - काष्ठाure size in bytes (includes size field)
 * WORD  - version
 * DWORD - supported functions bit vector
 */
/* supported functions vector */
#       define ATCS_GET_EXTERNAL_STATE_SUPPORTED                   (1 << 0)
#       define ATCS_PCIE_PERFORMANCE_REQUEST_SUPPORTED             (1 << 1)
#       define ATCS_PCIE_DEVICE_READY_NOTIFICATION_SUPPORTED       (1 << 2)
#       define ATCS_SET_PCIE_BUS_WIDTH_SUPPORTED                   (1 << 3)
#घोषणा ATCS_FUNCTION_GET_EXTERNAL_STATE                           0x1
/* ARG0: ATCS_FUNCTION_GET_EXTERNAL_STATE
 * ARG1: none
 * OUTPUT:
 * WORD  - काष्ठाure size in bytes (includes size field)
 * DWORD - valid flags mask
 * DWORD - flags (0: unकरोcked, 1: करोcked)
 */
/* flags */
#       define ATCS_DOCKED                                         (1 << 0)
#घोषणा ATCS_FUNCTION_PCIE_PERFORMANCE_REQUEST                     0x2
/* ARG0: ATCS_FUNCTION_PCIE_PERFORMANCE_REQUEST
 * ARG1:
 * WORD  - काष्ठाure size in bytes (includes size field)
 * WORD  - client id (bit 2-0: func num, 7-3: dev num, 15-8: bus num)
 * WORD  - valid flags mask
 * WORD  - flags
 * BYTE  - request type
 * BYTE  - perक्रमmance request
 * OUTPUT:
 * WORD  - काष्ठाure size in bytes (includes size field)
 * BYTE  - वापस value
 */
/* flags */
#       define ATCS_ADVERTISE_CAPS                                 (1 << 0)
#       define ATCS_WAIT_FOR_COMPLETION                            (1 << 1)
/* request type */
#       define ATCS_PCIE_LINK_SPEED                                1
/* perक्रमmance request */
#       define ATCS_REMOVE                                         0
#       define ATCS_FORCE_LOW_POWER                                1
#       define ATCS_PERF_LEVEL_1                                   2 /* PCIE Gen 1 */
#       define ATCS_PERF_LEVEL_2                                   3 /* PCIE Gen 2 */
#       define ATCS_PERF_LEVEL_3                                   4 /* PCIE Gen 3 */
/* वापस value */
#       define ATCS_REQUEST_REFUSED                                1
#       define ATCS_REQUEST_COMPLETE                               2
#       define ATCS_REQUEST_IN_PROGRESS                            3
#घोषणा ATCS_FUNCTION_PCIE_DEVICE_READY_NOTIFICATION               0x3
/* ARG0: ATCS_FUNCTION_PCIE_DEVICE_READY_NOTIFICATION
 * ARG1: none
 * OUTPUT: none
 */
#घोषणा ATCS_FUNCTION_SET_PCIE_BUS_WIDTH                           0x4
/* ARG0: ATCS_FUNCTION_SET_PCIE_BUS_WIDTH
 * ARG1:
 * WORD  - काष्ठाure size in bytes (includes size field)
 * WORD  - client id (bit 2-0: func num, 7-3: dev num, 15-8: bus num)
 * BYTE  - number of active lanes
 * OUTPUT:
 * WORD  - काष्ठाure size in bytes (includes size field)
 * BYTE  - number of active lanes
 */

#पूर्ण_अगर
