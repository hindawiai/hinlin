<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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

#अगर_अघोषित _DMUB_CMD_H_
#घोषणा _DMUB_CMD_H_

#अगर defined(_TEST_HARNESS) || defined(FPGA_USB4)
#समावेश "dmub_fw_types.h"
#समावेश "include_legacy/atomfirmware.h"

#अगर defined(_TEST_HARNESS)
#समावेश <माला.स>
#पूर्ण_अगर
#अन्यथा

#समावेश <यंत्र/byteorder.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <मानकतर्क.स>

#समावेश "atomfirmware.h"

#पूर्ण_अगर // defined(_TEST_HARNESS) || defined(FPGA_USB4)

/* Firmware versioning. */
#अगर_घोषित DMUB_EXPOSE_VERSION
#घोषणा DMUB_FW_VERSION_GIT_HASH 0x23db9b126
#घोषणा DMUB_FW_VERSION_MAJOR 0
#घोषणा DMUB_FW_VERSION_MINOR 0
#घोषणा DMUB_FW_VERSION_REVISION 62
#घोषणा DMUB_FW_VERSION_TEST 0
#घोषणा DMUB_FW_VERSION_VBIOS 0
#घोषणा DMUB_FW_VERSION_HOTFIX 0
#घोषणा DMUB_FW_VERSION_UCODE (((DMUB_FW_VERSION_MAJOR & 0xFF) << 24) | \
		((DMUB_FW_VERSION_MINOR & 0xFF) << 16) | \
		((DMUB_FW_VERSION_REVISION & 0xFF) << 8) | \
		((DMUB_FW_VERSION_TEST & 0x1) << 7) | \
		((DMUB_FW_VERSION_VBIOS & 0x1) << 6) | \
		(DMUB_FW_VERSION_HOTFIX & 0x3F))

#पूर्ण_अगर

//<DMUB_TYPES>==================================================================
/* Basic type definitions. */

#घोषणा __क्रमceअंतरभूत अंतरभूत

/**
 * Flag from driver to indicate that ABM should be disabled gradually
 * by slowly reversing all backlight programming and pixel compensation.
 */
#घोषणा SET_ABM_PIPE_GRADUALLY_DISABLE           0

/**
 * Flag from driver to indicate that ABM should be disabled immediately
 * and unकरो all backlight programming and pixel compensation.
 */
#घोषणा SET_ABM_PIPE_IMMEDIATELY_DISABLE         255

/**
 * Flag from driver to indicate that ABM should be disabled immediately
 * and keep the current backlight programming and pixel compensation.
 */
#घोषणा SET_ABM_PIPE_IMMEDIATE_KEEP_GAIN_DISABLE 254

/**
 * Flag from driver to set the current ABM pipe index or ABM operating level.
 */
#घोषणा SET_ABM_PIPE_NORMAL                      1

/**
 * Number of ambient light levels in ABM algorithm.
 */
#घोषणा NUM_AMBI_LEVEL                  5

/**
 * Number of operating/aggression levels in ABM algorithm.
 */
#घोषणा NUM_AGGR_LEVEL                  4

/**
 * Number of segments in the gamma curve.
 */
#घोषणा NUM_POWER_FN_SEGS               8

/**
 * Number of segments in the backlight curve.
 */
#घोषणा NUM_BL_CURVE_SEGS               16

/* Maximum number of streams on any ASIC. */
#घोषणा DMUB_MAX_STREAMS 6

/* Maximum number of planes on any ASIC. */
#घोषणा DMUB_MAX_PLANES 6

/* Trace buffer offset क्रम entry */
#घोषणा TRACE_BUFFER_ENTRY_OFFSET  16

/**
 * ABM backlight control version legacy
 */
#घोषणा DMUB_CMD_ABM_SET_BACKLIGHT_VERSION_UNKNOWN 0x0

/**
 * ABM backlight control version with multi edp support
 */
#घोषणा DMUB_CMD_ABM_SET_BACKLIGHT_VERSION_1 0x1

/**
 * Physical framebuffer address location, 64-bit.
 */
#अगर_अघोषित PHYSICAL_ADDRESS_LOC
#घोषणा PHYSICAL_ADDRESS_LOC जोड़ large_पूर्णांकeger
#पूर्ण_अगर

/**
 * OS/FW agnostic स_नकल
 */
#अगर_अघोषित dmub_स_नकल
#घोषणा dmub_स_नकल(dest, source, bytes) स_नकल((dest), (source), (bytes))
#पूर्ण_अगर

/**
 * OS/FW agnostic स_रखो
 */
#अगर_अघोषित dmub_स_रखो
#घोषणा dmub_स_रखो(dest, val, bytes) स_रखो((dest), (val), (bytes))
#पूर्ण_अगर

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

/**
 * OS/FW agnostic udelay
 */
#अगर_अघोषित dmub_udelay
#घोषणा dmub_udelay(microseconds) udelay(microseconds)
#पूर्ण_अगर

/**
 * जोड़ dmub_addr - DMUB physical/भव 64-bit address.
 */
जोड़ dmub_addr अणु
	काष्ठा अणु
		uपूर्णांक32_t low_part; /**< Lower 32 bits */
		uपूर्णांक32_t high_part; /**< Upper 32 bits */
	पूर्ण u; /*<< Low/high bit access */
	uपूर्णांक64_t quad_part; /*<< 64 bit address */
पूर्ण;

/**
 * Flags that can be set by driver to change some PSR behaviour.
 */
जोड़ dmub_psr_debug_flags अणु
	/**
	 * Debug flags.
	 */
	काष्ठा अणु
		/**
		 * Enable visual confirm in FW.
		 */
		uपूर्णांक32_t visual_confirm : 1;
		/**
		 * Use HW Lock Mgr object to करो HW locking in FW.
		 */
		uपूर्णांक32_t use_hw_lock_mgr : 1;

		/**
		 * Unused.
		 * TODO: Remove.
		 */
		uपूर्णांक32_t log_line_nums : 1;
	पूर्ण bitfields;

	/**
	 * Union क्रम debug flags.
	 */
	uपूर्णांक32_t u32All;
पूर्ण;

/**
 * DMUB feature capabilities.
 * After DMUB init, driver will query FW capabilities prior to enabling certain features.
 */
काष्ठा dmub_feature_caps अणु
	/**
	 * Max PSR version supported by FW.
	 */
	uपूर्णांक8_t psr;
	uपूर्णांक8_t reserved[7];
पूर्ण;

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

//==============================================================================
//</DMUB_TYPES>=================================================================
//==============================================================================
//< DMUB_META>==================================================================
//==============================================================================
#आशय pack(push, 1)

/* Magic value क्रम identअगरying dmub_fw_meta_info */
#घोषणा DMUB_FW_META_MAGIC 0x444D5542

/* Offset from the end of the file to the dmub_fw_meta_info */
#घोषणा DMUB_FW_META_OFFSET 0x24

/**
 * काष्ठा dmub_fw_meta_info - metadata associated with fw binary
 *
 * NOTE: This should be considered a stable API. Fields should
 *       not be repurposed or reordered. New fields should be
 *       added instead to extend the काष्ठाure.
 *
 * @magic_value: magic value identअगरying DMUB firmware meta info
 * @fw_region_size: size of the firmware state region
 * @trace_buffer_size: size of the tracebuffer region
 * @fw_version: the firmware version inक्रमmation
 * @dal_fw: 1 अगर the firmware is DAL
 */
काष्ठा dmub_fw_meta_info अणु
	uपूर्णांक32_t magic_value; /**< magic value identअगरying DMUB firmware meta info */
	uपूर्णांक32_t fw_region_size; /**< size of the firmware state region */
	uपूर्णांक32_t trace_buffer_size; /**< size of the tracebuffer region */
	uपूर्णांक32_t fw_version; /**< the firmware version inक्रमmation */
	uपूर्णांक8_t dal_fw; /**< 1 अगर the firmware is DAL */
	uपूर्णांक8_t reserved[3]; /**< padding bits */
पूर्ण;

/**
 * जोड़ dmub_fw_meta - ensures that dmub_fw_meta_info reमुख्यs 64 bytes
 */
जोड़ dmub_fw_meta अणु
	काष्ठा dmub_fw_meta_info info; /**< metadata info */
	uपूर्णांक8_t reserved[64]; /**< padding bits */
पूर्ण;

#आशय pack(pop)

//==============================================================================
//< DMUB Trace Buffer>================================================================
//==============================================================================
/**
 * dmub_trace_code_t - firmware trace code, 32-bits
 */
प्रकार uपूर्णांक32_t dmub_trace_code_t;

/**
 * काष्ठा dmcub_trace_buf_entry - Firmware trace entry
 */
काष्ठा dmcub_trace_buf_entry अणु
	dmub_trace_code_t trace_code; /**< trace code क्रम the event */
	uपूर्णांक32_t tick_count; /**< the tick count at समय of trace */
	uपूर्णांक32_t param0; /**< trace defined parameter 0 */
	uपूर्णांक32_t param1; /**< trace defined parameter 1 */
पूर्ण;

//==============================================================================
//< DMUB_STATUS>================================================================
//==============================================================================

/**
 * DMCUB scratch रेजिस्टरs can be used to determine firmware status.
 * Current scratch रेजिस्टर usage is as follows:
 *
 * SCRATCH0: FW Boot Status रेजिस्टर
 * SCRATCH15: FW Boot Options रेजिस्टर
 */

/**
 * जोड़ dmub_fw_boot_status - Status bit definitions क्रम SCRATCH0.
 */
जोड़ dmub_fw_boot_status अणु
	काष्ठा अणु
		uपूर्णांक32_t dal_fw : 1; /**< 1 अगर DAL FW */
		uपूर्णांक32_t mailbox_rdy : 1; /**< 1 अगर mailbox पढ़ोy */
		uपूर्णांक32_t optimized_init_करोne : 1; /**< 1 अगर optimized init करोne */
		uपूर्णांक32_t restore_required : 1; /**< 1 अगर driver should call restore */
	पूर्ण bits; /**< status bits */
	uपूर्णांक32_t all; /**< 32-bit access to status bits */
पूर्ण;

/**
 * क्रमागत dmub_fw_boot_status_bit - Enum bit definitions क्रम SCRATCH0.
 */
क्रमागत dmub_fw_boot_status_bit अणु
	DMUB_FW_BOOT_STATUS_BIT_DAL_FIRMWARE = (1 << 0), /**< 1 अगर DAL FW */
	DMUB_FW_BOOT_STATUS_BIT_MAILBOX_READY = (1 << 1), /**< 1 अगर mailbox पढ़ोy */
	DMUB_FW_BOOT_STATUS_BIT_OPTIMIZED_INIT_DONE = (1 << 2), /**< 1 अगर init करोne */
	DMUB_FW_BOOT_STATUS_BIT_RESTORE_REQUIRED = (1 << 3), /**< 1 अगर driver should call restore */
पूर्ण;

/**
 * जोड़ dmub_fw_boot_options - Boot option definitions क्रम SCRATCH15
 */
जोड़ dmub_fw_boot_options अणु
	काष्ठा अणु
		uपूर्णांक32_t pemu_env : 1; /**< 1 अगर PEMU */
		uपूर्णांक32_t fpga_env : 1; /**< 1 अगर FPGA */
		uपूर्णांक32_t optimized_init : 1; /**< 1 अगर optimized init */
		uपूर्णांक32_t skip_phy_access : 1; /**< 1 अगर PHY access should be skipped */
		uपूर्णांक32_t disable_clk_gate: 1; /**< 1 अगर घड़ी gating should be disabled */
		uपूर्णांक32_t skip_phy_init_panel_sequence: 1; /**< 1 to skip panel init seq */
		uपूर्णांक32_t reserved : 26; /**< reserved */
	पूर्ण bits; /**< boot bits */
	uपूर्णांक32_t all; /**< 32-bit access to bits */
पूर्ण;

क्रमागत dmub_fw_boot_options_bit अणु
	DMUB_FW_BOOT_OPTION_BIT_PEMU_ENV = (1 << 0), /**< 1 अगर PEMU */
	DMUB_FW_BOOT_OPTION_BIT_FPGA_ENV = (1 << 1), /**< 1 अगर FPGA */
	DMUB_FW_BOOT_OPTION_BIT_OPTIMIZED_INIT_DONE = (1 << 2), /**< 1 अगर optimized init करोne */
पूर्ण;

//==============================================================================
//</DMUB_STATUS>================================================================
//==============================================================================
//< DMUB_VBIOS>=================================================================
//==============================================================================

/*
 * क्रमागत dmub_cmd_vbios_type - VBIOS commands.
 *
 * Command IDs should be treated as stable ABI.
 * Do not reuse or modअगरy IDs.
 */
क्रमागत dmub_cmd_vbios_type अणु
	/**
	 * Configures the DIG encoder.
	 */
	DMUB_CMD__VBIOS_DIGX_ENCODER_CONTROL = 0,
	/**
	 * Controls the PHY.
	 */
	DMUB_CMD__VBIOS_DIG1_TRANSMITTER_CONTROL = 1,
	/**
	 * Sets the pixel घड़ी/symbol घड़ी.
	 */
	DMUB_CMD__VBIOS_SET_PIXEL_CLOCK = 2,
	/**
	 * Enables or disables घातer gating.
	 */
	DMUB_CMD__VBIOS_ENABLE_DISP_POWER_GATING = 3,
	DMUB_CMD__VBIOS_LVTMA_CONTROL = 15,
पूर्ण;

//==============================================================================
//</DMUB_VBIOS>=================================================================
//==============================================================================
//< DMUB_GPINT>=================================================================
//==============================================================================

/**
 * The shअगरts and masks below may alternatively be used to क्रमmat and पढ़ो
 * the command रेजिस्टर bits.
 */

#घोषणा DMUB_GPINT_DATA_PARAM_MASK 0xFFFF
#घोषणा DMUB_GPINT_DATA_PARAM_SHIFT 0

#घोषणा DMUB_GPINT_DATA_COMMAND_CODE_MASK 0xFFF
#घोषणा DMUB_GPINT_DATA_COMMAND_CODE_SHIFT 16

#घोषणा DMUB_GPINT_DATA_STATUS_MASK 0xF
#घोषणा DMUB_GPINT_DATA_STATUS_SHIFT 28

/**
 * Command responses.
 */

/**
 * Return response क्रम DMUB_GPINT__STOP_FW command.
 */
#घोषणा DMUB_GPINT__STOP_FW_RESPONSE 0xDEADDEAD

/**
 * जोड़ dmub_gpपूर्णांक_data_रेजिस्टर - Format क्रम sending a command via the GPINT.
 */
जोड़ dmub_gpपूर्णांक_data_रेजिस्टर अणु
	काष्ठा अणु
		uपूर्णांक32_t param : 16; /**< 16-bit parameter */
		uपूर्णांक32_t command_code : 12; /**< GPINT command */
		uपूर्णांक32_t status : 4; /**< Command status bit */
	पूर्ण bits; /**< GPINT bit access */
	uपूर्णांक32_t all; /**< GPINT  32-bit access */
पूर्ण;

/*
 * क्रमागत dmub_gpपूर्णांक_command - GPINT command to DMCUB FW
 *
 * Command IDs should be treated as stable ABI.
 * Do not reuse or modअगरy IDs.
 */
क्रमागत dmub_gpपूर्णांक_command अणु
	/**
	 * Invalid command, ignored.
	 */
	DMUB_GPINT__INVALID_COMMAND = 0,
	/**
	 * DESC: Queries the firmware version.
	 * RETURN: Firmware version.
	 */
	DMUB_GPINT__GET_FW_VERSION = 1,
	/**
	 * DESC: Halts the firmware.
	 * RETURN: DMUB_GPINT__STOP_FW_RESPONSE (0xDEADDEAD) when halted
	 */
	DMUB_GPINT__STOP_FW = 2,
	/**
	 * DESC: Get PSR state from FW.
	 * RETURN: PSR state क्रमागत. This क्रमागत may need to be converted to the legacy PSR state value.
	 */
	DMUB_GPINT__GET_PSR_STATE = 7,
	/**
	 * DESC: Notअगरies DMCUB of the currently active streams.
	 * ARGS: Stream mask, 1 bit per active stream index.
	 */
	DMUB_GPINT__IDLE_OPT_NOTIFY_STREAM_MASK = 8,
	/**
	 * DESC: Start PSR residency counter. Stop PSR resdiency counter and get value.
	 * ARGS: We can measure residency from various poपूर्णांकs. The argument will specअगरy the residency mode.
	 *       By शेष, it is measured from after we घातerकरोwn the PHY, to just beक्रमe we घातerup the PHY.
	 * RETURN: PSR residency in milli-percent.
	 */
	DMUB_GPINT__PSR_RESIDENCY = 9,
पूर्ण;

//==============================================================================
//</DMUB_GPINT>=================================================================
//==============================================================================
//< DMUB_CMD>===================================================================
//==============================================================================

/**
 * Size in bytes of each DMUB command.
 */
#घोषणा DMUB_RB_CMD_SIZE 64

/**
 * Maximum number of items in the DMUB ringbuffer.
 */
#घोषणा DMUB_RB_MAX_ENTRY 128

/**
 * Ringbuffer size in bytes.
 */
#घोषणा DMUB_RB_SIZE (DMUB_RB_CMD_SIZE * DMUB_RB_MAX_ENTRY)

/**
 * REG_SET mask क्रम reg offload.
 */
#घोषणा REG_SET_MASK 0xFFFF

/*
 * क्रमागत dmub_cmd_type - DMUB inbox command.
 *
 * Command IDs should be treated as stable ABI.
 * Do not reuse or modअगरy IDs.
 */
क्रमागत dmub_cmd_type अणु
	/**
	 * Invalid command.
	 */
	DMUB_CMD__शून्य = 0,
	/**
	 * Read modअगरy ग_लिखो रेजिस्टर sequence offload.
	 */
	DMUB_CMD__REG_SEQ_READ_MODIFY_WRITE = 1,
	/**
	 * Field update रेजिस्टर sequence offload.
	 */
	DMUB_CMD__REG_SEQ_FIELD_UPDATE_SEQ = 2,
	/**
	 * Burst ग_लिखो sequence offload.
	 */
	DMUB_CMD__REG_SEQ_BURST_WRITE = 3,
	/**
	 * Reg रुको sequence offload.
	 */
	DMUB_CMD__REG_REG_WAIT = 4,
	/**
	 * Workaround to aव्योम HUBP underflow during NV12 playback.
	 */
	DMUB_CMD__PLAT_54186_WA = 5,
	/**
	 * Command type used to query FW feature caps.
	 */
	DMUB_CMD__QUERY_FEATURE_CAPS = 6,
	/**
	 * Command type used क्रम all PSR commands.
	 */
	DMUB_CMD__PSR = 64,
	/**
	 * Command type used क्रम all MALL commands.
	 */
	DMUB_CMD__MALL = 65,
	/**
	 * Command type used क्रम all ABM commands.
	 */
	DMUB_CMD__ABM = 66,
	/**
	 * Command type used क्रम HW locking in FW.
	 */
	DMUB_CMD__HW_LOCK = 69,
	/**
	 * Command type used to access DP AUX.
	 */
	DMUB_CMD__DP_AUX_ACCESS = 70,
	/**
	 * Command type used क्रम OUTBOX1 notअगरication enable
	 */
	DMUB_CMD__OUTBOX1_ENABLE = 71,
	/**
	 * Command type used क्रम all VBIOS पूर्णांकerface commands.
	 */
	DMUB_CMD__VBIOS = 128,
पूर्ण;

/**
 * क्रमागत dmub_out_cmd_type - DMUB outbox commands.
 */
क्रमागत dmub_out_cmd_type अणु
	/**
	 * Invalid outbox command, ignored.
	 */
	DMUB_OUT_CMD__शून्य = 0,
	/**
	 * Command type used क्रम DP AUX Reply data notअगरication
	 */
	DMUB_OUT_CMD__DP_AUX_REPLY = 1,
	/**
	 * Command type used क्रम DP HPD event notअगरication
	 */
	DMUB_OUT_CMD__DP_HPD_NOTIFY = 2,
पूर्ण;

#आशय pack(push, 1)

/**
 * काष्ठा dmub_cmd_header - Common command header fields.
 */
काष्ठा dmub_cmd_header अणु
	अचिन्हित पूर्णांक type : 8; /**< command type */
	अचिन्हित पूर्णांक sub_type : 8; /**< command sub type */
	अचिन्हित पूर्णांक ret_status : 1; /**< 1 अगर वापसed data, 0 otherwise */
	अचिन्हित पूर्णांक reserved0 : 7; /**< reserved bits */
	अचिन्हित पूर्णांक payload_bytes : 6;  /* payload excluding header - up to 60 bytes */
	अचिन्हित पूर्णांक reserved1 : 2; /**< reserved bits */
पूर्ण;

/*
 * काष्ठा dmub_cmd_पढ़ो_modअगरy_ग_लिखो_sequence - Read modअगरy ग_लिखो
 *
 * 60 payload bytes can hold up to 5 sets of पढ़ो modअगरy ग_लिखोs,
 * each take 3 dwords.
 *
 * number of sequences = header.payload_bytes / माप(काष्ठा dmub_cmd_पढ़ो_modअगरy_ग_लिखो_sequence)
 *
 * modअगरy_mask = 0xffff'ffff means all fields are going to be updated.  in this हाल
 * command parser will skip the पढ़ो and we can use modअगरy_mask = 0xffff'ffff as reg ग_लिखो
 */
काष्ठा dmub_cmd_पढ़ो_modअगरy_ग_लिखो_sequence अणु
	uपूर्णांक32_t addr; /**< रेजिस्टर address */
	uपूर्णांक32_t modअगरy_mask; /**< modअगरy mask */
	uपूर्णांक32_t modअगरy_value; /**< modअगरy value */
पूर्ण;

/**
 * Maximum number of ops in पढ़ो modअगरy ग_लिखो sequence.
 */
#घोषणा DMUB_READ_MODIFY_WRITE_SEQ__MAX 5

/**
 * काष्ठा dmub_cmd_पढ़ो_modअगरy_ग_लिखो_sequence - Read modअगरy ग_लिखो command.
 */
काष्ठा dmub_rb_cmd_पढ़ो_modअगरy_ग_लिखो अणु
	काष्ठा dmub_cmd_header header;  /**< command header */
	/**
	 * Read modअगरy ग_लिखो sequence.
	 */
	काष्ठा dmub_cmd_पढ़ो_modअगरy_ग_लिखो_sequence seq[DMUB_READ_MODIFY_WRITE_SEQ__MAX];
पूर्ण;

/*
 * Update a रेजिस्टर with specअगरied masks and values sequeunce
 *
 * 60 payload bytes can hold address + up to 7 sets of mask/value combo, each take 2 dword
 *
 * number of field update sequence = (header.payload_bytes - माप(addr)) / माप(काष्ठा पढ़ो_modअगरy_ग_लिखो_sequence)
 *
 *
 * USE CASE:
 *   1. स्वतः-increment रेजिस्टर where additional पढ़ो would update poपूर्णांकer and produce wrong result
 *   2. toggle a bit without पढ़ो in the middle
 */

काष्ठा dmub_cmd_reg_field_update_sequence अणु
	uपूर्णांक32_t modअगरy_mask; /**< 0xffff'ffff to skip initial पढ़ो */
	uपूर्णांक32_t modअगरy_value; /**< value to update with */
पूर्ण;

/**
 * Maximum number of ops in field update sequence.
 */
#घोषणा DMUB_REG_FIELD_UPDATE_SEQ__MAX 7

/**
 * काष्ठा dmub_rb_cmd_reg_field_update_sequence - Field update command.
 */
काष्ठा dmub_rb_cmd_reg_field_update_sequence अणु
	काष्ठा dmub_cmd_header header; /**< command header */
	uपूर्णांक32_t addr; /**< रेजिस्टर address */
	/**
	 * Field update sequence.
	 */
	काष्ठा dmub_cmd_reg_field_update_sequence seq[DMUB_REG_FIELD_UPDATE_SEQ__MAX];
पूर्ण;


/**
 * Maximum number of burst ग_लिखो values.
 */
#घोषणा DMUB_BURST_WRITE_VALUES__MAX  14

/*
 * काष्ठा dmub_rb_cmd_burst_ग_लिखो - Burst ग_लिखो
 *
 * support use हाल such as writing out LUTs.
 *
 * 60 payload bytes can hold up to 14 values to ग_लिखो to given address
 *
 * number of payload = header.payload_bytes / माप(काष्ठा पढ़ो_modअगरy_ग_लिखो_sequence)
 */
काष्ठा dmub_rb_cmd_burst_ग_लिखो अणु
	काष्ठा dmub_cmd_header header; /**< command header */
	uपूर्णांक32_t addr; /**< रेजिस्टर start address */
	/**
	 * Burst ग_लिखो रेजिस्टर values.
	 */
	uपूर्णांक32_t ग_लिखो_values[DMUB_BURST_WRITE_VALUES__MAX];
पूर्ण;

/**
 * काष्ठा dmub_rb_cmd_common - Common command header
 */
काष्ठा dmub_rb_cmd_common अणु
	काष्ठा dmub_cmd_header header; /**< command header */
	/**
	 * Padding to RB_CMD_SIZE
	 */
	uपूर्णांक8_t cmd_buffer[DMUB_RB_CMD_SIZE - माप(काष्ठा dmub_cmd_header)];
पूर्ण;

/**
 * काष्ठा dmub_cmd_reg_रुको_data - Register रुको data
 */
काष्ठा dmub_cmd_reg_रुको_data अणु
	uपूर्णांक32_t addr; /**< Register address */
	uपूर्णांक32_t mask; /**< Mask क्रम रेजिस्टर bits */
	uपूर्णांक32_t condition_field_value; /**< Value to रुको क्रम */
	uपूर्णांक32_t समय_out_us; /**< Time out क्रम reg रुको in microseconds */
पूर्ण;

/**
 * काष्ठा dmub_rb_cmd_reg_रुको - Register रुको command
 */
काष्ठा dmub_rb_cmd_reg_रुको अणु
	काष्ठा dmub_cmd_header header; /**< Command header */
	काष्ठा dmub_cmd_reg_रुको_data reg_रुको; /**< Register रुको data */
पूर्ण;

/**
 * काष्ठा dmub_cmd_PLAT_54186_wa - Underflow workaround
 *
 * Reprograms surface parameters to aव्योम underflow.
 */
काष्ठा dmub_cmd_PLAT_54186_wa अणु
	uपूर्णांक32_t DCSURF_SURFACE_CONTROL; /**< reg value */
	uपूर्णांक32_t DCSURF_PRIMARY_SURFACE_ADDRESS_HIGH; /**< reg value */
	uपूर्णांक32_t DCSURF_PRIMARY_SURFACE_ADDRESS; /**< reg value */
	uपूर्णांक32_t DCSURF_PRIMARY_SURFACE_ADDRESS_HIGH_C; /**< reg value */
	uपूर्णांक32_t DCSURF_PRIMARY_SURFACE_ADDRESS_C; /**< reg value */
	काष्ठा अणु
		uपूर्णांक8_t hubp_inst : 4; /**< HUBP instance */
		uपूर्णांक8_t पंचांगz_surface : 1; /**< TMZ enable or disable */
		uपूर्णांक8_t immediate :1; /**< Immediate flip */
		uपूर्णांक8_t vmid : 4; /**< VMID */
		uपूर्णांक8_t grph_stereo : 1; /**< 1 अगर stereo */
		uपूर्णांक32_t reserved : 21; /**< Reserved */
	पूर्ण flip_params; /**< Pageflip parameters */
	uपूर्णांक32_t reserved[9]; /**< Reserved bits */
पूर्ण;

/**
 * काष्ठा dmub_rb_cmd_PLAT_54186_wa - Underflow workaround command
 */
काष्ठा dmub_rb_cmd_PLAT_54186_wa अणु
	काष्ठा dmub_cmd_header header; /**< Command header */
	काष्ठा dmub_cmd_PLAT_54186_wa flip; /**< Flip data */
पूर्ण;

/**
 * काष्ठा dmub_rb_cmd_mall - MALL command data.
 */
काष्ठा dmub_rb_cmd_mall अणु
	काष्ठा dmub_cmd_header header; /**< Common command header */
	जोड़ dmub_addr cursor_copy_src; /**< Cursor copy address */
	जोड़ dmub_addr cursor_copy_dst; /**< Cursor copy destination */
	uपूर्णांक32_t पंचांगr_delay; /**< Timer delay */
	uपूर्णांक32_t पंचांगr_scale; /**< Timer scale */
	uपूर्णांक16_t cursor_width; /**< Cursor width in pixels */
	uपूर्णांक16_t cursor_pitch; /**< Cursor pitch in pixels */
	uपूर्णांक16_t cursor_height; /**< Cursor height in pixels */
	uपूर्णांक8_t cursor_bpp; /**< Cursor bits per pixel */
	uपूर्णांक8_t debug_bits; /**< Debug bits */

	uपूर्णांक8_t reserved1; /**< Reserved bits */
	uपूर्णांक8_t reserved2; /**< Reserved bits */
पूर्ण;

/**
 * काष्ठा dmub_cmd_digx_encoder_control_data - Encoder control data.
 */
काष्ठा dmub_cmd_digx_encoder_control_data अणु
	जोड़ dig_encoder_control_parameters_v1_5 dig; /**< payload */
पूर्ण;

/**
 * काष्ठा dmub_rb_cmd_digx_encoder_control - Encoder control command.
 */
काष्ठा dmub_rb_cmd_digx_encoder_control अणु
	काष्ठा dmub_cmd_header header;  /**< header */
	काष्ठा dmub_cmd_digx_encoder_control_data encoder_control; /**< payload */
पूर्ण;

/**
 * काष्ठा dmub_cmd_set_pixel_घड़ी_data - Set pixel घड़ी data.
 */
काष्ठा dmub_cmd_set_pixel_घड़ी_data अणु
	काष्ठा set_pixel_घड़ी_parameter_v1_7 clk; /**< payload */
पूर्ण;

/**
 * काष्ठा dmub_cmd_set_pixel_घड़ी_data - Set pixel घड़ी command.
 */
काष्ठा dmub_rb_cmd_set_pixel_घड़ी अणु
	काष्ठा dmub_cmd_header header; /**< header */
	काष्ठा dmub_cmd_set_pixel_घड़ी_data pixel_घड़ी; /**< payload */
पूर्ण;

/**
 * काष्ठा dmub_cmd_enable_disp_घातer_gating_data - Display घातer gating.
 */
काष्ठा dmub_cmd_enable_disp_घातer_gating_data अणु
	काष्ठा enable_disp_घातer_gating_parameters_v2_1 pwr; /**< payload */
पूर्ण;

/**
 * काष्ठा dmub_rb_cmd_enable_disp_घातer_gating - Display घातer command.
 */
काष्ठा dmub_rb_cmd_enable_disp_घातer_gating अणु
	काष्ठा dmub_cmd_header header; /**< header */
	काष्ठा dmub_cmd_enable_disp_घातer_gating_data घातer_gating;  /**< payload */
पूर्ण;

/**
 * काष्ठा dmub_dig_transmitter_control_data_v1_7 - Transmitter control.
 */
काष्ठा dmub_dig_transmitter_control_data_v1_7 अणु
	uपूर्णांक8_t phyid; /**< 0=UNIPHYA, 1=UNIPHYB, 2=UNIPHYC, 3=UNIPHYD, 4=UNIPHYE, 5=UNIPHYF */
	uपूर्णांक8_t action; /**< Defined as ATOM_TRANSMITER_ACTION_xxx */
	जोड़ अणु
		uपूर्णांक8_t digmode; /**< क्रमागत atom_encode_mode_def */
		uपूर्णांक8_t dplaneset; /**< DP voltage swing and pre-emphasis value, "DP_LANE_SET__xDB_y_zV" */
	पूर्ण mode_laneset;
	uपूर्णांक8_t lanक्रमागत; /**< Number of lanes */
	जोड़ अणु
		uपूर्णांक32_t symclk_10khz; /**< Symbol Clock in 10Khz */
	पूर्ण symclk_units;
	uपूर्णांक8_t hpdsel; /**< =1: HPD1, =2: HPD2, ..., =6: HPD6, =0: HPD is not asचिन्हित */
	uपूर्णांक8_t digfe_sel; /**< DIG front-end selection, bit0 means DIG0 FE is enabled */
	uपूर्णांक8_t connobj_id; /**< Connector Object Id defined in ObjectId.h */
	uपूर्णांक8_t reserved0; /**< For future use */
	uपूर्णांक8_t reserved1; /**< For future use */
	uपूर्णांक8_t reserved2[3]; /**< For future use */
	uपूर्णांक32_t reserved3[11]; /**< For future use */
पूर्ण;

/**
 * जोड़ dmub_cmd_dig1_transmitter_control_data - Transmitter control data.
 */
जोड़ dmub_cmd_dig1_transmitter_control_data अणु
	काष्ठा dig_transmitter_control_parameters_v1_6 dig; /**< payload */
	काष्ठा dmub_dig_transmitter_control_data_v1_7 dig_v1_7;  /**< payload 1.7 */
पूर्ण;

/**
 * काष्ठा dmub_rb_cmd_dig1_transmitter_control - Transmitter control command.
 */
काष्ठा dmub_rb_cmd_dig1_transmitter_control अणु
	काष्ठा dmub_cmd_header header; /**< header */
	जोड़ dmub_cmd_dig1_transmitter_control_data transmitter_control; /**< payload */
पूर्ण;

/**
 * काष्ठा dmub_rb_cmd_dpphy_init - DPPHY init.
 */
काष्ठा dmub_rb_cmd_dpphy_init अणु
	काष्ठा dmub_cmd_header header; /**< header */
	uपूर्णांक8_t reserved[60]; /**< reserved bits */
पूर्ण;

/**
 * क्रमागत dp_aux_request_action - DP AUX request command listing.
 *
 * 4 AUX request command bits are shअगरted to high nibble.
 */
क्रमागत dp_aux_request_action अणु
	/** I2C-over-AUX ग_लिखो request */
	DP_AUX_REQ_ACTION_I2C_WRITE		= 0x00,
	/** I2C-over-AUX पढ़ो request */
	DP_AUX_REQ_ACTION_I2C_READ		= 0x10,
	/** I2C-over-AUX ग_लिखो status request */
	DP_AUX_REQ_ACTION_I2C_STATUS_REQ	= 0x20,
	/** I2C-over-AUX ग_लिखो request with MOT=1 */
	DP_AUX_REQ_ACTION_I2C_WRITE_MOT		= 0x40,
	/** I2C-over-AUX पढ़ो request with MOT=1 */
	DP_AUX_REQ_ACTION_I2C_READ_MOT		= 0x50,
	/** I2C-over-AUX ग_लिखो status request with MOT=1 */
	DP_AUX_REQ_ACTION_I2C_STATUS_REQ_MOT	= 0x60,
	/** Native AUX ग_लिखो request */
	DP_AUX_REQ_ACTION_DPCD_WRITE		= 0x80,
	/** Native AUX पढ़ो request */
	DP_AUX_REQ_ACTION_DPCD_READ		= 0x90
पूर्ण;

/**
 * क्रमागत aux_वापस_code_type - DP AUX process वापस code listing.
 */
क्रमागत aux_वापस_code_type अणु
	/** AUX process succeeded */
	AUX_RET_SUCCESS = 0,
	/** AUX process failed with unknown reason */
	AUX_RET_ERROR_UNKNOWN,
	/** AUX process completed with invalid reply */
	AUX_RET_ERROR_INVALID_REPLY,
	/** AUX process समयd out */
	AUX_RET_ERROR_TIMEOUT,
	/** HPD was low during AUX process */
	AUX_RET_ERROR_HPD_DISCON,
	/** Failed to acquire AUX engine */
	AUX_RET_ERROR_ENGINE_ACQUIRE,
	/** AUX request not supported */
	AUX_RET_ERROR_INVALID_OPERATION,
	/** AUX process not available */
	AUX_RET_ERROR_PROTOCOL_ERROR,
पूर्ण;

/**
 * क्रमागत aux_channel_type - DP AUX channel type listing.
 */
क्रमागत aux_channel_type अणु
	/** AUX thru Legacy DP AUX */
	AUX_CHANNEL_LEGACY_DDC,
	/** AUX thru DPIA DP tunneling */
	AUX_CHANNEL_DPIA
पूर्ण;

/**
 * काष्ठा aux_transaction_parameters - DP AUX request transaction data
 */
काष्ठा aux_transaction_parameters अणु
	uपूर्णांक8_t is_i2c_over_aux; /**< 0=native AUX, 1=I2C-over-AUX */
	uपूर्णांक8_t action; /**< क्रमागत dp_aux_request_action */
	uपूर्णांक8_t length; /**< DP AUX request data length */
	uपूर्णांक8_t reserved; /**< For future use */
	uपूर्णांक32_t address; /**< DP AUX address */
	uपूर्णांक8_t data[16]; /**< DP AUX ग_लिखो data */
पूर्ण;

/**
 * Data passed from driver to FW in a DMUB_CMD__DP_AUX_ACCESS command.
 */
काष्ठा dmub_cmd_dp_aux_control_data अणु
	uपूर्णांक8_t instance; /**< AUX instance or DPIA instance */
	uपूर्णांक8_t manual_acq_rel_enable; /**< manual control क्रम acquiring or releasing AUX channel */
	uपूर्णांक8_t sw_crc_enabled; /**< Use software CRC क्रम tunneling packet instead of hardware CRC */
	uपूर्णांक8_t reserved0; /**< For future use */
	uपूर्णांक16_t समयout; /**< समयout समय in us */
	uपूर्णांक16_t reserved1; /**< For future use */
	क्रमागत aux_channel_type type; /**< क्रमागत aux_channel_type */
	काष्ठा aux_transaction_parameters dpaux; /**< काष्ठा aux_transaction_parameters */
पूर्ण;

/**
 * Definition of a DMUB_CMD__DP_AUX_ACCESS command.
 */
काष्ठा dmub_rb_cmd_dp_aux_access अणु
	/**
	 * Command header.
	 */
	काष्ठा dmub_cmd_header header;
	/**
	 * Data passed from driver to FW in a DMUB_CMD__DP_AUX_ACCESS command.
	 */
	काष्ठा dmub_cmd_dp_aux_control_data aux_control;
पूर्ण;

/**
 * Definition of a DMUB_CMD__OUTBOX1_ENABLE command.
 */
काष्ठा dmub_rb_cmd_outbox1_enable अणु
	/**
	 * Command header.
	 */
	काष्ठा dmub_cmd_header header;
	/**
	 *  enable: 0x0 -> disable outbox1 notअगरication (शेष value)
	 *			0x1 -> enable outbox1 notअगरication
	 */
	uपूर्णांक32_t enable;
पूर्ण;

/* DP AUX Reply command - OutBox Cmd */
/**
 * Data passed to driver from FW in a DMUB_OUT_CMD__DP_AUX_REPLY command.
 */
काष्ठा aux_reply_data अणु
	/**
	 * Aux cmd
	 */
	uपूर्णांक8_t command;
	/**
	 * Aux reply data length (max: 16 bytes)
	 */
	uपूर्णांक8_t length;
	/**
	 * Alignment only
	 */
	uपूर्णांक8_t pad[2];
	/**
	 * Aux reply data
	 */
	uपूर्णांक8_t data[16];
पूर्ण;

/**
 * Control Data passed to driver from FW in a DMUB_OUT_CMD__DP_AUX_REPLY command.
 */
काष्ठा aux_reply_control_data अणु
	/**
	 * Reserved क्रम future use
	 */
	uपूर्णांक32_t handle;
	/**
	 * Aux Instance
	 */
	uपूर्णांक8_t instance;
	/**
	 * Aux transaction result: definition in क्रमागत aux_वापस_code_type
	 */
	uपूर्णांक8_t result;
	/**
	 * Alignment only
	 */
	uपूर्णांक16_t pad;
पूर्ण;

/**
 * Definition of a DMUB_OUT_CMD__DP_AUX_REPLY command.
 */
काष्ठा dmub_rb_cmd_dp_aux_reply अणु
	/**
	 * Command header.
	 */
	काष्ठा dmub_cmd_header header;
	/**
	 * Control Data passed to driver from FW in a DMUB_OUT_CMD__DP_AUX_REPLY command.
	 */
	काष्ठा aux_reply_control_data control;
	/**
	 * Data passed to driver from FW in a DMUB_OUT_CMD__DP_AUX_REPLY command.
	 */
	काष्ठा aux_reply_data reply_data;
पूर्ण;

/* DP HPD Notअगरy command - OutBox Cmd */
/**
 * DP HPD Type
 */
क्रमागत dp_hpd_type अणु
	/**
	 * Normal DP HPD
	 */
	DP_HPD = 0,
	/**
	 * DP HPD लघु pulse
	 */
	DP_IRQ
पूर्ण;

/**
 * DP HPD Status
 */
क्रमागत dp_hpd_status अणु
	/**
	 * DP_HPD status low
	 */
	DP_HPD_UNPLUG = 0,
	/**
	 * DP_HPD status high
	 */
	DP_HPD_PLUG
पूर्ण;

/**
 * Data passed to driver from FW in a DMUB_OUT_CMD__DP_HPD_NOTIFY command.
 */
काष्ठा dp_hpd_data अणु
	/**
	 * DP HPD instance
	 */
	uपूर्णांक8_t instance;
	/**
	 * HPD type
	 */
	uपूर्णांक8_t hpd_type;
	/**
	 * HPD status: only क्रम type: DP_HPD to indicate status
	 */
	uपूर्णांक8_t hpd_status;
	/**
	 * Alignment only
	 */
	uपूर्णांक8_t pad;
पूर्ण;

/**
 * Definition of a DMUB_OUT_CMD__DP_HPD_NOTIFY command.
 */
काष्ठा dmub_rb_cmd_dp_hpd_notअगरy अणु
	/**
	 * Command header.
	 */
	काष्ठा dmub_cmd_header header;
	/**
	 * Data passed to driver from FW in a DMUB_OUT_CMD__DP_HPD_NOTIFY command.
	 */
	काष्ठा dp_hpd_data hpd_data;
पूर्ण;

/*
 * Command IDs should be treated as stable ABI.
 * Do not reuse or modअगरy IDs.
 */

/**
 * PSR command sub-types.
 */
क्रमागत dmub_cmd_psr_type अणु
	/**
	 * Set PSR version support.
	 */
	DMUB_CMD__PSR_SET_VERSION		= 0,
	/**
	 * Copy driver-calculated parameters to PSR state.
	 */
	DMUB_CMD__PSR_COPY_SETTINGS		= 1,
	/**
	 * Enable PSR.
	 */
	DMUB_CMD__PSR_ENABLE			= 2,

	/**
	 * Disable PSR.
	 */
	DMUB_CMD__PSR_DISABLE			= 3,

	/**
	 * Set PSR level.
	 * PSR level is a 16-bit value dicated by driver that
	 * will enable/disable dअगरferent functionality.
	 */
	DMUB_CMD__PSR_SET_LEVEL			= 4,

	/**
	 * Forces PSR enabled until an explicit PSR disable call.
	 */
	DMUB_CMD__PSR_FORCE_STATIC		= 5,
पूर्ण;

/**
 * PSR versions.
 */
क्रमागत psr_version अणु
	/**
	 * PSR version 1.
	 */
	PSR_VERSION_1				= 0,
	/**
	 * PSR not supported.
	 */
	PSR_VERSION_UNSUPPORTED			= 0xFFFFFFFF,
पूर्ण;

/**
 * क्रमागत dmub_cmd_mall_type - MALL commands
 */
क्रमागत dmub_cmd_mall_type अणु
	/**
	 * Allows display refresh from MALL.
	 */
	DMUB_CMD__MALL_ACTION_ALLOW = 0,
	/**
	 * Disallows display refresh from MALL.
	 */
	DMUB_CMD__MALL_ACTION_DISALLOW = 1,
	/**
	 * Cursor copy क्रम MALL.
	 */
	DMUB_CMD__MALL_ACTION_COPY_CURSOR = 2,
	/**
	 * Controls DF requests.
	 */
	DMUB_CMD__MALL_ACTION_NO_DF_REQ = 3,
पूर्ण;


/**
 * Data passed from driver to FW in a DMUB_CMD__PSR_COPY_SETTINGS command.
 */
काष्ठा dmub_cmd_psr_copy_settings_data अणु
	/**
	 * Flags that can be set by driver to change some PSR behaviour.
	 */
	जोड़ dmub_psr_debug_flags debug;
	/**
	 * 16-bit value dicated by driver that will enable/disable dअगरferent functionality.
	 */
	uपूर्णांक16_t psr_level;
	/**
	 * DPP HW instance.
	 */
	uपूर्णांक8_t dpp_inst;
	/**
	 * MPCC HW instance.
	 * Not used in dmub fw,
	 * dmub fw will get active opp by पढ़ोing odm रेजिस्टरs.
	 */
	uपूर्णांक8_t mpcc_inst;
	/**
	 * OPP HW instance.
	 * Not used in dmub fw,
	 * dmub fw will get active opp by पढ़ोing odm रेजिस्टरs.
	 */
	uपूर्णांक8_t opp_inst;
	/**
	 * OTG HW instance.
	 */
	uपूर्णांक8_t otg_inst;
	/**
	 * DIG FE HW instance.
	 */
	uपूर्णांक8_t digfe_inst;
	/**
	 * DIG BE HW instance.
	 */
	uपूर्णांक8_t digbe_inst;
	/**
	 * DP PHY HW instance.
	 */
	uपूर्णांक8_t dpphy_inst;
	/**
	 * AUX HW instance.
	 */
	uपूर्णांक8_t aux_inst;
	/**
	 * Determines अगर SMU optimzations are enabled/disabled.
	 */
	uपूर्णांक8_t smu_optimizations_en;
	/**
	 * Unused.
	 * TODO: Remove.
	 */
	uपूर्णांक8_t frame_delay;
	/**
	 * If RFB setup समय is greater than the total VBLANK समय,
	 * it is not possible क्रम the sink to capture the video frame
	 * in the same frame the SDP is sent. In this हाल,
	 * the frame capture indication bit should be set and an extra
	 * अटल frame should be transmitted to the sink.
	 */
	uपूर्णांक8_t frame_cap_ind;
	/**
	 * Explicit padding to 4 byte boundary.
	 */
	uपूर्णांक8_t pad[2];
	/**
	 * Multi-display optimizations are implemented on certain ASICs.
	 */
	uपूर्णांक8_t multi_disp_optimizations_en;
	/**
	 * The last possible line SDP may be transmitted without violating
	 * the RFB setup समय or entering the active video frame.
	 */
	uपूर्णांक16_t init_sdp_deadline;
	/**
	 * Explicit padding to 4 byte boundary.
	 */
	uपूर्णांक16_t pad2;
	/**
	 * Length of each horizontal line in us.
	 */
	uपूर्णांक32_t line_समय_in_us;
	/**
	 * FEC enable status in driver
	 */
	uपूर्णांक8_t fec_enable_status;
	/**
	 * FEC re-enable delay when PSR निकास.
	 * unit is 100us, range क्रमm 0~255(0xFF).
	 */
	uपूर्णांक8_t fec_enable_delay_in100us;
	/**
	 * Explicit padding to 4 byte boundary.
	 */
	uपूर्णांक8_t pad3[2];
पूर्ण;

/**
 * Definition of a DMUB_CMD__PSR_COPY_SETTINGS command.
 */
काष्ठा dmub_rb_cmd_psr_copy_settings अणु
	/**
	 * Command header.
	 */
	काष्ठा dmub_cmd_header header;
	/**
	 * Data passed from driver to FW in a DMUB_CMD__PSR_COPY_SETTINGS command.
	 */
	काष्ठा dmub_cmd_psr_copy_settings_data psr_copy_settings_data;
पूर्ण;

/**
 * Data passed from driver to FW in a DMUB_CMD__PSR_SET_LEVEL command.
 */
काष्ठा dmub_cmd_psr_set_level_data अणु
	/**
	 * 16-bit value dicated by driver that will enable/disable dअगरferent functionality.
	 */
	uपूर्णांक16_t psr_level;
	/**
	 * Explicit padding to 4 byte boundary.
	 */
	uपूर्णांक8_t pad[2];
पूर्ण;

/**
 * Definition of a DMUB_CMD__PSR_SET_LEVEL command.
 */
काष्ठा dmub_rb_cmd_psr_set_level अणु
	/**
	 * Command header.
	 */
	काष्ठा dmub_cmd_header header;
	/**
	 * Definition of a DMUB_CMD__PSR_SET_LEVEL command.
	 */
	काष्ठा dmub_cmd_psr_set_level_data psr_set_level_data;
पूर्ण;

/**
 * Definition of a DMUB_CMD__PSR_ENABLE command.
 * PSR enable/disable is controlled using the sub_type.
 */
काष्ठा dmub_rb_cmd_psr_enable अणु
	/**
	 * Command header.
	 */
	काष्ठा dmub_cmd_header header;
पूर्ण;

/**
 * Data passed from driver to FW in a DMUB_CMD__PSR_SET_VERSION command.
 */
काष्ठा dmub_cmd_psr_set_version_data अणु
	/**
	 * PSR version that FW should implement.
	 */
	क्रमागत psr_version version;
पूर्ण;

/**
 * Definition of a DMUB_CMD__PSR_SET_VERSION command.
 */
काष्ठा dmub_rb_cmd_psr_set_version अणु
	/**
	 * Command header.
	 */
	काष्ठा dmub_cmd_header header;
	/**
	 * Data passed from driver to FW in a DMUB_CMD__PSR_SET_VERSION command.
	 */
	काष्ठा dmub_cmd_psr_set_version_data psr_set_version_data;
पूर्ण;

/**
 * Definition of a DMUB_CMD__PSR_FORCE_STATIC command.
 */
काष्ठा dmub_rb_cmd_psr_क्रमce_अटल अणु
	/**
	 * Command header.
	 */
	काष्ठा dmub_cmd_header header;
पूर्ण;

/**
 * Set of HW components that can be locked.
 */
जोड़ dmub_hw_lock_flags अणु
	/**
	 * Set of HW components that can be locked.
	 */
	काष्ठा अणु
		/**
		 * Lock/unlock OTG master update lock.
		 */
		uपूर्णांक8_t lock_pipe   : 1;
		/**
		 * Lock/unlock cursor.
		 */
		uपूर्णांक8_t lock_cursor : 1;
		/**
		 * Lock/unlock global update lock.
		 */
		uपूर्णांक8_t lock_dig    : 1;
		/**
		 * Triple buffer lock requires additional hw programming to usual OTG master lock.
		 */
		uपूर्णांक8_t triple_buffer_lock : 1;
	पूर्ण bits;

	/**
	 * Union क्रम HW Lock flags.
	 */
	uपूर्णांक8_t u8All;
पूर्ण;

/**
 * Instances of HW to be locked.
 */
काष्ठा dmub_hw_lock_inst_flags अणु
	/**
	 * OTG HW instance क्रम OTG master update lock.
	 */
	uपूर्णांक8_t otg_inst;
	/**
	 * OPP instance क्रम cursor lock.
	 */
	uपूर्णांक8_t opp_inst;
	/**
	 * OTG HW instance क्रम global update lock.
	 * TODO: Remove, and re-use otg_inst.
	 */
	uपूर्णांक8_t dig_inst;
	/**
	 * Explicit pad to 4 byte boundary.
	 */
	uपूर्णांक8_t pad;
पूर्ण;

/**
 * Clients that can acquire the HW Lock Manager.
 */
क्रमागत hw_lock_client अणु
	/**
	 * Driver is the client of HW Lock Manager.
	 */
	HW_LOCK_CLIENT_DRIVER = 0,
	/**
	 * FW is the client of HW Lock Manager.
	 */
	HW_LOCK_CLIENT_FW,
	/**
	 * Invalid client.
	 */
	HW_LOCK_CLIENT_INVALID = 0xFFFFFFFF,
पूर्ण;

/**
 * Data passed to HW Lock Mgr in a DMUB_CMD__HW_LOCK command.
 */
काष्ठा dmub_cmd_lock_hw_data अणु
	/**
	 * Specअगरies the client accessing HW Lock Manager.
	 */
	क्रमागत hw_lock_client client;
	/**
	 * HW instances to be locked.
	 */
	काष्ठा dmub_hw_lock_inst_flags inst_flags;
	/**
	 * Which components to be locked.
	 */
	जोड़ dmub_hw_lock_flags hw_locks;
	/**
	 * Specअगरies lock/unlock.
	 */
	uपूर्णांक8_t lock;
	/**
	 * HW can be unlocked separately from releasing the HW Lock Mgr.
	 * This flag is set अगर the client wishes to release the object.
	 */
	uपूर्णांक8_t should_release;
	/**
	 * Explicit padding to 4 byte boundary.
	 */
	uपूर्णांक8_t pad;
पूर्ण;

/**
 * Definition of a DMUB_CMD__HW_LOCK command.
 * Command is used by driver and FW.
 */
काष्ठा dmub_rb_cmd_lock_hw अणु
	/**
	 * Command header.
	 */
	काष्ठा dmub_cmd_header header;
	/**
	 * Data passed to HW Lock Mgr in a DMUB_CMD__HW_LOCK command.
	 */
	काष्ठा dmub_cmd_lock_hw_data lock_hw_data;
पूर्ण;

/**
 * ABM command sub-types.
 */
क्रमागत dmub_cmd_abm_type अणु
	/**
	 * Initialize parameters क्रम ABM algorithm.
	 * Data is passed through an indirect buffer.
	 */
	DMUB_CMD__ABM_INIT_CONFIG	= 0,
	/**
	 * Set OTG and panel HW instance.
	 */
	DMUB_CMD__ABM_SET_PIPE		= 1,
	/**
	 * Set user requested backklight level.
	 */
	DMUB_CMD__ABM_SET_BACKLIGHT	= 2,
	/**
	 * Set ABM operating/aggression level.
	 */
	DMUB_CMD__ABM_SET_LEVEL		= 3,
	/**
	 * Set ambient light level.
	 */
	DMUB_CMD__ABM_SET_AMBIENT_LEVEL	= 4,
	/**
	 * Enable/disable fractional duty cycle क्रम backlight PWM.
	 */
	DMUB_CMD__ABM_SET_PWM_FRAC	= 5,
पूर्ण;

/**
 * Parameters क्रम ABM2.4 algorithm. Passed from driver to FW via an indirect buffer.
 * Requirements:
 *  - Padded explicitly to 32-bit boundary.
 *  - Must ensure this काष्ठाure matches the one on driver-side,
 *    otherwise it won't be aligned.
 */
काष्ठा abm_config_table अणु
	/**
	 * Gamma curve thresholds, used क्रम crgb conversion.
	 */
	uपूर्णांक16_t crgb_thresh[NUM_POWER_FN_SEGS];                 // 0B
	/**
	 * Gamma curve offsets, used क्रम crgb conversion.
	 */
	uपूर्णांक16_t crgb_offset[NUM_POWER_FN_SEGS];                 // 16B
	/**
	 * Gamma curve slopes, used क्रम crgb conversion.
	 */
	uपूर्णांक16_t crgb_slope[NUM_POWER_FN_SEGS];                  // 32B
	/**
	 * Custom backlight curve thresholds.
	 */
	uपूर्णांक16_t backlight_thresholds[NUM_BL_CURVE_SEGS];        // 48B
	/**
	 * Custom backlight curve offsets.
	 */
	uपूर्णांक16_t backlight_offsets[NUM_BL_CURVE_SEGS];           // 78B
	/**
	 * Ambient light thresholds.
	 */
	uपूर्णांक16_t ambient_thresholds_lux[NUM_AMBI_LEVEL];         // 112B
	/**
	 * Minimum programmable backlight.
	 */
	uपूर्णांक16_t min_abm_backlight;                              // 122B
	/**
	 * Minimum reduction values.
	 */
	uपूर्णांक8_t min_reduction[NUM_AMBI_LEVEL][NUM_AGGR_LEVEL];   // 124B
	/**
	 * Maximum reduction values.
	 */
	uपूर्णांक8_t max_reduction[NUM_AMBI_LEVEL][NUM_AGGR_LEVEL];   // 144B
	/**
	 * Bright positive gain.
	 */
	uपूर्णांक8_t bright_pos_gain[NUM_AMBI_LEVEL][NUM_AGGR_LEVEL]; // 164B
	/**
	 * Dark negative gain.
	 */
	uपूर्णांक8_t dark_pos_gain[NUM_AMBI_LEVEL][NUM_AGGR_LEVEL];   // 184B
	/**
	 * Hybrid factor.
	 */
	uपूर्णांक8_t hybrid_factor[NUM_AGGR_LEVEL];                   // 204B
	/**
	 * Contrast factor.
	 */
	uपूर्णांक8_t contrast_factor[NUM_AGGR_LEVEL];                 // 208B
	/**
	 * Deviation gain.
	 */
	uपूर्णांक8_t deviation_gain[NUM_AGGR_LEVEL];                  // 212B
	/**
	 * Minimum knee.
	 */
	uपूर्णांक8_t min_knee[NUM_AGGR_LEVEL];                        // 216B
	/**
	 * Maximum knee.
	 */
	uपूर्णांक8_t max_knee[NUM_AGGR_LEVEL];                        // 220B
	/**
	 * Unused.
	 */
	uपूर्णांक8_t iir_curve[NUM_AMBI_LEVEL];                       // 224B
	/**
	 * Explicit padding to 4 byte boundary.
	 */
	uपूर्णांक8_t pad3[3];                                         // 229B
	/**
	 * Backlight ramp reduction.
	 */
	uपूर्णांक16_t blRampReduction[NUM_AGGR_LEVEL];                // 232B
	/**
	 * Backlight ramp start.
	 */
	uपूर्णांक16_t blRampStart[NUM_AGGR_LEVEL];                    // 240B
पूर्ण;

/**
 * Data passed from driver to FW in a DMUB_CMD__ABM_SET_PIPE command.
 */
काष्ठा dmub_cmd_abm_set_pipe_data अणु
	/**
	 * OTG HW instance.
	 */
	uपूर्णांक8_t otg_inst;

	/**
	 * Panel Control HW instance.
	 */
	uपूर्णांक8_t panel_inst;

	/**
	 * Controls how ABM will पूर्णांकerpret a set pipe or set level command.
	 */
	uपूर्णांक8_t set_pipe_option;

	/**
	 * Unused.
	 * TODO: Remove.
	 */
	uपूर्णांक8_t ramping_boundary;
पूर्ण;

/**
 * Definition of a DMUB_CMD__ABM_SET_PIPE command.
 */
काष्ठा dmub_rb_cmd_abm_set_pipe अणु
	/**
	 * Command header.
	 */
	काष्ठा dmub_cmd_header header;

	/**
	 * Data passed from driver to FW in a DMUB_CMD__ABM_SET_PIPE command.
	 */
	काष्ठा dmub_cmd_abm_set_pipe_data abm_set_pipe_data;
पूर्ण;

/**
 * Data passed from driver to FW in a DMUB_CMD__ABM_SET_BACKLIGHT command.
 */
काष्ठा dmub_cmd_abm_set_backlight_data अणु
	/**
	 * Number of frames to ramp to backlight user level.
	 */
	uपूर्णांक32_t frame_ramp;

	/**
	 * Requested backlight level from user.
	 */
	uपूर्णांक32_t backlight_user_level;

	/**
	 * Backlight data version.
	 */
	uपूर्णांक8_t version;

	/**
	 * Panel Control HW instance mask.
	 * Bit 0 is Panel Control HW instance 0.
	 * Bit 1 is Panel Control HW instance 1.
	 */
	uपूर्णांक8_t panel_mask;

	/**
	 * Explicit padding to 4 byte boundary.
	 */
	uपूर्णांक8_t pad[2];
पूर्ण;

/**
 * Definition of a DMUB_CMD__ABM_SET_BACKLIGHT command.
 */
काष्ठा dmub_rb_cmd_abm_set_backlight अणु
	/**
	 * Command header.
	 */
	काष्ठा dmub_cmd_header header;

	/**
	 * Data passed from driver to FW in a DMUB_CMD__ABM_SET_BACKLIGHT command.
	 */
	काष्ठा dmub_cmd_abm_set_backlight_data abm_set_backlight_data;
पूर्ण;

/**
 * Data passed from driver to FW in a DMUB_CMD__ABM_SET_LEVEL command.
 */
काष्ठा dmub_cmd_abm_set_level_data अणु
	/**
	 * Set current ABM operating/aggression level.
	 */
	uपूर्णांक32_t level;
पूर्ण;

/**
 * Definition of a DMUB_CMD__ABM_SET_LEVEL command.
 */
काष्ठा dmub_rb_cmd_abm_set_level अणु
	/**
	 * Command header.
	 */
	काष्ठा dmub_cmd_header header;

	/**
	 * Data passed from driver to FW in a DMUB_CMD__ABM_SET_LEVEL command.
	 */
	काष्ठा dmub_cmd_abm_set_level_data abm_set_level_data;
पूर्ण;

/**
 * Data passed from driver to FW in a DMUB_CMD__ABM_SET_AMBIENT_LEVEL command.
 */
काष्ठा dmub_cmd_abm_set_ambient_level_data अणु
	/**
	 * Ambient light sensor पढ़ोing from OS.
	 */
	uपूर्णांक32_t ambient_lux;
पूर्ण;

/**
 * Definition of a DMUB_CMD__ABM_SET_AMBIENT_LEVEL command.
 */
काष्ठा dmub_rb_cmd_abm_set_ambient_level अणु
	/**
	 * Command header.
	 */
	काष्ठा dmub_cmd_header header;

	/**
	 * Data passed from driver to FW in a DMUB_CMD__ABM_SET_AMBIENT_LEVEL command.
	 */
	काष्ठा dmub_cmd_abm_set_ambient_level_data abm_set_ambient_level_data;
पूर्ण;

/**
 * Data passed from driver to FW in a DMUB_CMD__ABM_SET_PWM_FRAC command.
 */
काष्ठा dmub_cmd_abm_set_pwm_frac_data अणु
	/**
	 * Enable/disable fractional duty cycle क्रम backlight PWM.
	 * TODO: Convert to uपूर्णांक8_t.
	 */
	uपूर्णांक32_t fractional_pwm;
पूर्ण;

/**
 * Definition of a DMUB_CMD__ABM_SET_PWM_FRAC command.
 */
काष्ठा dmub_rb_cmd_abm_set_pwm_frac अणु
	/**
	 * Command header.
	 */
	काष्ठा dmub_cmd_header header;

	/**
	 * Data passed from driver to FW in a DMUB_CMD__ABM_SET_PWM_FRAC command.
	 */
	काष्ठा dmub_cmd_abm_set_pwm_frac_data abm_set_pwm_frac_data;
पूर्ण;

/**
 * Data passed from driver to FW in a DMUB_CMD__ABM_INIT_CONFIG command.
 */
काष्ठा dmub_cmd_abm_init_config_data अणु
	/**
	 * Location of indirect buffer used to pass init data to ABM.
	 */
	जोड़ dmub_addr src;

	/**
	 * Indirect buffer length.
	 */
	uपूर्णांक16_t bytes;
पूर्ण;

/**
 * Definition of a DMUB_CMD__ABM_INIT_CONFIG command.
 */
काष्ठा dmub_rb_cmd_abm_init_config अणु
	/**
	 * Command header.
	 */
	काष्ठा dmub_cmd_header header;

	/**
	 * Data passed from driver to FW in a DMUB_CMD__ABM_INIT_CONFIG command.
	 */
	काष्ठा dmub_cmd_abm_init_config_data abm_init_config_data;
पूर्ण;

/**
 * Data passed from driver to FW in a DMUB_CMD__QUERY_FEATURE_CAPS command.
 */
काष्ठा dmub_cmd_query_feature_caps_data अणु
	/**
	 * DMUB feature capabilities.
	 * After DMUB init, driver will query FW capabilities prior to enabling certain features.
	 */
	काष्ठा dmub_feature_caps feature_caps;
पूर्ण;

/**
 * Definition of a DMUB_CMD__QUERY_FEATURE_CAPS command.
 */
काष्ठा dmub_rb_cmd_query_feature_caps अणु
	/**
	 * Command header.
	 */
	काष्ठा dmub_cmd_header header;
	/**
	 * Data passed from driver to FW in a DMUB_CMD__QUERY_FEATURE_CAPS command.
	 */
	काष्ठा dmub_cmd_query_feature_caps_data query_feature_caps_data;
पूर्ण;

काष्ठा dmub_optc_state अणु
	uपूर्णांक32_t v_total_max;
	uपूर्णांक32_t v_total_min;
	uपूर्णांक32_t v_total_mid;
	uपूर्णांक32_t v_total_mid_frame_num;
	uपूर्णांक32_t tg_inst;
	uपूर्णांक32_t enable_manual_trigger;
	uपूर्णांक32_t clear_क्रमce_vsync;
पूर्ण;

काष्ठा dmub_rb_cmd_drr_update अणु
		काष्ठा dmub_cmd_header header;
		काष्ठा dmub_optc_state dmub_optc_state_req;
पूर्ण;

/**
 * Data passed from driver to FW in a DMUB_CMD__VBIOS_LVTMA_CONTROL command.
 */
काष्ठा dmub_cmd_lvपंचांगa_control_data अणु
	uपूर्णांक8_t uc_pwr_action; /**< LVTMA_ACTION */
	uपूर्णांक8_t reserved_0[3]; /**< For future use */
	uपूर्णांक8_t panel_inst; /**< LVTMA control instance */
	uपूर्णांक8_t reserved_1[3]; /**< For future use */
पूर्ण;

/**
 * Definition of a DMUB_CMD__VBIOS_LVTMA_CONTROL command.
 */
काष्ठा dmub_rb_cmd_lvपंचांगa_control अणु
	/**
	 * Command header.
	 */
	काष्ठा dmub_cmd_header header;
	/**
	 * Data passed from driver to FW in a DMUB_CMD__VBIOS_LVTMA_CONTROL command.
	 */
	काष्ठा dmub_cmd_lvपंचांगa_control_data data;
पूर्ण;

/**
 * जोड़ dmub_rb_cmd - DMUB inbox command.
 */
जोड़ dmub_rb_cmd अणु
	काष्ठा dmub_rb_cmd_lock_hw lock_hw;
	/**
	 * Elements shared with all commands.
	 */
	काष्ठा dmub_rb_cmd_common cmd_common;
	/**
	 * Definition of a DMUB_CMD__REG_SEQ_READ_MODIFY_WRITE command.
	 */
	काष्ठा dmub_rb_cmd_पढ़ो_modअगरy_ग_लिखो पढ़ो_modअगरy_ग_लिखो;
	/**
	 * Definition of a DMUB_CMD__REG_SEQ_FIELD_UPDATE_SEQ command.
	 */
	काष्ठा dmub_rb_cmd_reg_field_update_sequence reg_field_update_seq;
	/**
	 * Definition of a DMUB_CMD__REG_SEQ_BURST_WRITE command.
	 */
	काष्ठा dmub_rb_cmd_burst_ग_लिखो burst_ग_लिखो;
	/**
	 * Definition of a DMUB_CMD__REG_REG_WAIT command.
	 */
	काष्ठा dmub_rb_cmd_reg_रुको reg_रुको;
	/**
	 * Definition of a DMUB_CMD__VBIOS_DIGX_ENCODER_CONTROL command.
	 */
	काष्ठा dmub_rb_cmd_digx_encoder_control digx_encoder_control;
	/**
	 * Definition of a DMUB_CMD__VBIOS_SET_PIXEL_CLOCK command.
	 */
	काष्ठा dmub_rb_cmd_set_pixel_घड़ी set_pixel_घड़ी;
	/**
	 * Definition of a DMUB_CMD__VBIOS_ENABLE_DISP_POWER_GATING command.
	 */
	काष्ठा dmub_rb_cmd_enable_disp_घातer_gating enable_disp_घातer_gating;
	/**
	 * Definition of a DMUB_CMD__VBIOS_DPPHY_INIT command.
	 */
	काष्ठा dmub_rb_cmd_dpphy_init dpphy_init;
	/**
	 * Definition of a DMUB_CMD__VBIOS_DIG1_TRANSMITTER_CONTROL command.
	 */
	काष्ठा dmub_rb_cmd_dig1_transmitter_control dig1_transmitter_control;
	/**
	 * Definition of a DMUB_CMD__PSR_SET_VERSION command.
	 */
	काष्ठा dmub_rb_cmd_psr_set_version psr_set_version;
	/**
	 * Definition of a DMUB_CMD__PSR_COPY_SETTINGS command.
	 */
	काष्ठा dmub_rb_cmd_psr_copy_settings psr_copy_settings;
	/**
	 * Definition of a DMUB_CMD__PSR_ENABLE command.
	 */
	काष्ठा dmub_rb_cmd_psr_enable psr_enable;
	/**
	 * Definition of a DMUB_CMD__PSR_SET_LEVEL command.
	 */
	काष्ठा dmub_rb_cmd_psr_set_level psr_set_level;
	/**
	 * Definition of a DMUB_CMD__PSR_FORCE_STATIC command.
	 */
	काष्ठा dmub_rb_cmd_psr_क्रमce_अटल psr_क्रमce_अटल;
	/**
	 * Definition of a DMUB_CMD__PLAT_54186_WA command.
	 */
	काष्ठा dmub_rb_cmd_PLAT_54186_wa PLAT_54186_wa;
	/**
	 * Definition of a DMUB_CMD__MALL command.
	 */
	काष्ठा dmub_rb_cmd_mall mall;
	/**
	 * Definition of a DMUB_CMD__ABM_SET_PIPE command.
	 */
	काष्ठा dmub_rb_cmd_abm_set_pipe abm_set_pipe;

	/**
	 * Definition of a DMUB_CMD__ABM_SET_BACKLIGHT command.
	 */
	काष्ठा dmub_rb_cmd_abm_set_backlight abm_set_backlight;

	/**
	 * Definition of a DMUB_CMD__ABM_SET_LEVEL command.
	 */
	काष्ठा dmub_rb_cmd_abm_set_level abm_set_level;

	/**
	 * Definition of a DMUB_CMD__ABM_SET_AMBIENT_LEVEL command.
	 */
	काष्ठा dmub_rb_cmd_abm_set_ambient_level abm_set_ambient_level;

	/**
	 * Definition of a DMUB_CMD__ABM_SET_PWM_FRAC command.
	 */
	काष्ठा dmub_rb_cmd_abm_set_pwm_frac abm_set_pwm_frac;

	/**
	 * Definition of a DMUB_CMD__ABM_INIT_CONFIG command.
	 */
	काष्ठा dmub_rb_cmd_abm_init_config abm_init_config;

	/**
	 * Definition of a DMUB_CMD__DP_AUX_ACCESS command.
	 */
	काष्ठा dmub_rb_cmd_dp_aux_access dp_aux_access;

	/**
	 * Definition of a DMUB_CMD__OUTBOX1_ENABLE command.
	 */
	काष्ठा dmub_rb_cmd_outbox1_enable outbox1_enable;

	/**
	 * Definition of a DMUB_CMD__QUERY_FEATURE_CAPS command.
	 */
	काष्ठा dmub_rb_cmd_query_feature_caps query_feature_caps;
	काष्ठा dmub_rb_cmd_drr_update drr_update;
	/**
	 * Definition of a DMUB_CMD__VBIOS_LVTMA_CONTROL command.
	 */
	काष्ठा dmub_rb_cmd_lvपंचांगa_control lvपंचांगa_control;
पूर्ण;

/**
 * जोड़ dmub_rb_out_cmd - Outbox command
 */
जोड़ dmub_rb_out_cmd अणु
	/**
	 * Parameters common to every command.
	 */
	काष्ठा dmub_rb_cmd_common cmd_common;
	/**
	 * AUX reply command.
	 */
	काष्ठा dmub_rb_cmd_dp_aux_reply dp_aux_reply;
	/**
	 * HPD notअगरy command.
	 */
	काष्ठा dmub_rb_cmd_dp_hpd_notअगरy dp_hpd_notअगरy;
पूर्ण;
#आशय pack(pop)


//==============================================================================
//</DMUB_CMD>===================================================================
//==============================================================================
//< DMUB_RB>====================================================================
//==============================================================================

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

/**
 * काष्ठा dmub_rb_init_params - Initialization params क्रम DMUB ringbuffer
 */
काष्ठा dmub_rb_init_params अणु
	व्योम *ctx; /**< Caller provided context poपूर्णांकer */
	व्योम *base_address; /**< CPU base address क्रम ring's data */
	uपूर्णांक32_t capacity; /**< Ringbuffer capacity in bytes */
	uपूर्णांक32_t पढ़ो_ptr; /**< Initial पढ़ो poपूर्णांकer क्रम consumer in bytes */
	uपूर्णांक32_t ग_लिखो_ptr; /**< Initial ग_लिखो poपूर्णांकer क्रम producer in bytes */
पूर्ण;

/**
 * काष्ठा dmub_rb - Inbox or outbox DMUB ringbuffer
 */
काष्ठा dmub_rb अणु
	व्योम *base_address; /**< CPU address क्रम the ring's data */
	uपूर्णांक32_t rptr; /**< Read poपूर्णांकer क्रम consumer in bytes */
	uपूर्णांक32_t wrpt; /**< Write poपूर्णांकer क्रम producer in bytes */
	uपूर्णांक32_t capacity; /**< Ringbuffer capacity in bytes */

	व्योम *ctx; /**< Caller provided context poपूर्णांकer */
	व्योम *dmub; /**< Poपूर्णांकer to the DMUB पूर्णांकerface */
पूर्ण;

/**
 * @brief Checks अगर the ringbuffer is empty.
 *
 * @param rb DMUB Ringbuffer
 * @वापस true अगर empty
 * @वापस false otherwise
 */
अटल अंतरभूत bool dmub_rb_empty(काष्ठा dmub_rb *rb)
अणु
	वापस (rb->wrpt == rb->rptr);
पूर्ण

/**
 * @brief Checks अगर the ringbuffer is full
 *
 * @param rb DMUB Ringbuffer
 * @वापस true अगर full
 * @वापस false otherwise
 */
अटल अंतरभूत bool dmub_rb_full(काष्ठा dmub_rb *rb)
अणु
	uपूर्णांक32_t data_count;

	अगर (rb->wrpt >= rb->rptr)
		data_count = rb->wrpt - rb->rptr;
	अन्यथा
		data_count = rb->capacity - (rb->rptr - rb->wrpt);

	वापस (data_count == (rb->capacity - DMUB_RB_CMD_SIZE));
पूर्ण

/**
 * @brief Pushes a command पूर्णांकo the ringbuffer
 *
 * @param rb DMUB ringbuffer
 * @param cmd The command to push
 * @वापस true अगर the ringbuffer was not full
 * @वापस false otherwise
 */
अटल अंतरभूत bool dmub_rb_push_front(काष्ठा dmub_rb *rb,
				      स्थिर जोड़ dmub_rb_cmd *cmd)
अणु
	uपूर्णांक64_t अस्थिर *dst = (uपूर्णांक64_t अस्थिर *)(rb->base_address) + rb->wrpt / माप(uपूर्णांक64_t);
	स्थिर uपूर्णांक64_t *src = (स्थिर uपूर्णांक64_t *)cmd;
	uपूर्णांक8_t i;

	अगर (dmub_rb_full(rb))
		वापस false;

	// copying data
	क्रम (i = 0; i < DMUB_RB_CMD_SIZE / माप(uपूर्णांक64_t); i++)
		*dst++ = *src++;

	rb->wrpt += DMUB_RB_CMD_SIZE;

	अगर (rb->wrpt >= rb->capacity)
		rb->wrpt %= rb->capacity;

	वापस true;
पूर्ण

/**
 * @brief Pushes a command पूर्णांकo the DMUB outbox ringbuffer
 *
 * @param rb DMUB outbox ringbuffer
 * @param cmd Outbox command
 * @वापस true अगर not full
 * @वापस false otherwise
 */
अटल अंतरभूत bool dmub_rb_out_push_front(काष्ठा dmub_rb *rb,
				      स्थिर जोड़ dmub_rb_out_cmd *cmd)
अणु
	uपूर्णांक8_t *dst = (uपूर्णांक8_t *)(rb->base_address) + rb->wrpt;
	स्थिर uपूर्णांक8_t *src = (uपूर्णांक8_t *)cmd;

	अगर (dmub_rb_full(rb))
		वापस false;

	dmub_स_नकल(dst, src, DMUB_RB_CMD_SIZE);

	rb->wrpt += DMUB_RB_CMD_SIZE;

	अगर (rb->wrpt >= rb->capacity)
		rb->wrpt %= rb->capacity;

	वापस true;
पूर्ण

/**
 * @brief Returns the next unprocessed command in the ringbuffer.
 *
 * @param rb DMUB ringbuffer
 * @param cmd The command to वापस
 * @वापस true अगर not empty
 * @वापस false otherwise
 */
अटल अंतरभूत bool dmub_rb_front(काष्ठा dmub_rb *rb,
				 जोड़ dmub_rb_cmd  **cmd)
अणु
	uपूर्णांक8_t *rb_cmd = (uपूर्णांक8_t *)(rb->base_address) + rb->rptr;

	अगर (dmub_rb_empty(rb))
		वापस false;

	*cmd = (जोड़ dmub_rb_cmd *)rb_cmd;

	वापस true;
पूर्ण

/**
 * @brief Returns the next unprocessed command in the outbox.
 *
 * @param rb DMUB outbox ringbuffer
 * @param cmd The outbox command to वापस
 * @वापस true अगर not empty
 * @वापस false otherwise
 */
अटल अंतरभूत bool dmub_rb_out_front(काष्ठा dmub_rb *rb,
				 जोड़ dmub_rb_out_cmd  *cmd)
अणु
	स्थिर uपूर्णांक64_t अस्थिर *src = (स्थिर uपूर्णांक64_t अस्थिर *)(rb->base_address) + rb->rptr / माप(uपूर्णांक64_t);
	uपूर्णांक64_t *dst = (uपूर्णांक64_t *)cmd;
	uपूर्णांक8_t i;

	अगर (dmub_rb_empty(rb))
		वापस false;

	// copying data
	क्रम (i = 0; i < DMUB_RB_CMD_SIZE / माप(uपूर्णांक64_t); i++)
		*dst++ = *src++;

	वापस true;
पूर्ण

/**
 * @brief Removes the front entry in the ringbuffer.
 *
 * @param rb DMUB ringbuffer
 * @वापस true अगर the command was हटाओd
 * @वापस false अगर there were no commands
 */
अटल अंतरभूत bool dmub_rb_pop_front(काष्ठा dmub_rb *rb)
अणु
	अगर (dmub_rb_empty(rb))
		वापस false;

	rb->rptr += DMUB_RB_CMD_SIZE;

	अगर (rb->rptr >= rb->capacity)
		rb->rptr %= rb->capacity;

	वापस true;
पूर्ण

/**
 * @brief Flushes commands in the ringbuffer to framebuffer memory.
 *
 * Aव्योमs a race condition where DMCUB accesses memory जबतक
 * there are still ग_लिखोs in flight to framebuffer.
 *
 * @param rb DMUB ringbuffer
 */
अटल अंतरभूत व्योम dmub_rb_flush_pending(स्थिर काष्ठा dmub_rb *rb)
अणु
	uपूर्णांक32_t rptr = rb->rptr;
	uपूर्णांक32_t wptr = rb->wrpt;

	जबतक (rptr != wptr) अणु
		uपूर्णांक64_t अस्थिर *data = (uपूर्णांक64_t अस्थिर *)rb->base_address + rptr / माप(uपूर्णांक64_t);
		uपूर्णांक8_t i;

		क्रम (i = 0; i < DMUB_RB_CMD_SIZE / माप(uपूर्णांक64_t); i++)
			*data++;

		rptr += DMUB_RB_CMD_SIZE;
		अगर (rptr >= rb->capacity)
			rptr %= rb->capacity;
	पूर्ण
पूर्ण

/**
 * @brief Initializes a DMCUB ringbuffer
 *
 * @param rb DMUB ringbuffer
 * @param init_params initial configuration क्रम the ringbuffer
 */
अटल अंतरभूत व्योम dmub_rb_init(काष्ठा dmub_rb *rb,
				काष्ठा dmub_rb_init_params *init_params)
अणु
	rb->base_address = init_params->base_address;
	rb->capacity = init_params->capacity;
	rb->rptr = init_params->पढ़ो_ptr;
	rb->wrpt = init_params->ग_लिखो_ptr;
पूर्ण

/**
 * @brief Copies output data from in/out commands पूर्णांकo the given command.
 *
 * @param rb DMUB ringbuffer
 * @param cmd Command to copy data पूर्णांकo
 */
अटल अंतरभूत व्योम dmub_rb_get_वापस_data(काष्ठा dmub_rb *rb,
					   जोड़ dmub_rb_cmd *cmd)
अणु
	// Copy rb entry back पूर्णांकo command
	uपूर्णांक8_t *rd_ptr = (rb->rptr == 0) ?
		(uपूर्णांक8_t *)rb->base_address + rb->capacity - DMUB_RB_CMD_SIZE :
		(uपूर्णांक8_t *)rb->base_address + rb->rptr - DMUB_RB_CMD_SIZE;

	dmub_स_नकल(cmd, rd_ptr, DMUB_RB_CMD_SIZE);
पूर्ण

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

//==============================================================================
//</DMUB_RB>====================================================================
//==============================================================================

#पूर्ण_अगर /* _DMUB_CMD_H_ */
