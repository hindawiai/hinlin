<शैली गुरु>
/*
 * Copyright तऊ 2013 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Brad Volkin <bradley.d.volkin@पूर्णांकel.com>
 *
 */

#समावेश "gt/intel_engine.h"
#समावेश "gt/intel_gpu_commands.h"

#समावेश "i915_drv.h"
#समावेश "i915_memcpy.h"

/**
 * DOC: batch buffer command parser
 *
 * Motivation:
 * Certain OpenGL features (e.g. transक्रमm feedback, perक्रमmance monitoring)
 * require userspace code to submit batches containing commands such as
 * MI_LOAD_REGISTER_IMM to access various रेजिस्टरs. Unक्रमtunately, some
 * generations of the hardware will noop these commands in "unsecure" batches
 * (which includes all userspace batches submitted via i915) even though the
 * commands may be safe and represent the पूर्णांकended programming model of the
 * device.
 *
 * The software command parser is similar in operation to the command parsing
 * करोne in hardware क्रम unsecure batches. However, the software parser allows
 * some operations that would be noop'd by hardware, अगर the parser determines
 * the operation is safe, and submits the batch as "secure" to prevent hardware
 * parsing.
 *
 * Threats:
 * At a high level, the hardware (and software) checks attempt to prevent
 * granting userspace undue privileges. There are three categories of privilege.
 *
 * First, commands which are explicitly defined as privileged or which should
 * only be used by the kernel driver. The parser rejects such commands
 *
 * Second, commands which access रेजिस्टरs. To support correct/enhanced
 * userspace functionality, particularly certain OpenGL extensions, the parser
 * provides a whitelist of रेजिस्टरs which userspace may safely access
 *
 * Third, commands which access privileged memory (i.e. GGTT, HWS page, etc).
 * The parser always rejects such commands.
 *
 * The majority of the problematic commands fall in the MI_* range, with only a
 * few specअगरic commands on each engine (e.g. PIPE_CONTROL and MI_FLUSH_DW).
 *
 * Implementation:
 * Each engine मुख्यtains tables of commands and रेजिस्टरs which the parser
 * uses in scanning batch buffers submitted to that engine.
 *
 * Since the set of commands that the parser must check क्रम is signअगरicantly
 * smaller than the number of commands supported, the parser tables contain only
 * those commands required by the parser. This generally works because command
 * opcode ranges have standard command length encodings. So क्रम commands that
 * the parser करोes not need to check, it can easily skip them. This is
 * implemented via a per-engine length decoding vfunc.
 *
 * Unक्रमtunately, there are a number of commands that करो not follow the standard
 * length encoding क्रम their opcode range, primarily amongst the MI_* commands.
 * To handle this, the parser provides a way to define explicit "skip" entries
 * in the per-engine command tables.
 *
 * Other command table entries map fairly directly to high level categories
 * mentioned above: rejected, रेजिस्टर whitelist. The parser implements a number
 * of checks, including the privileged memory checks, via a general biपंचांगasking
 * mechanism.
 */

/*
 * A command that requires special handling by the command parser.
 */
काष्ठा drm_i915_cmd_descriptor अणु
	/*
	 * Flags describing how the command parser processes the command.
	 *
	 * CMD_DESC_FIXED: The command has a fixed length अगर this is set,
	 *                 a length mask अगर not set
	 * CMD_DESC_SKIP: The command is allowed but करोes not follow the
	 *                standard length encoding क्रम the opcode range in
	 *                which it falls
	 * CMD_DESC_REJECT: The command is never allowed
	 * CMD_DESC_REGISTER: The command should be checked against the
	 *                    रेजिस्टर whitelist क्रम the appropriate ring
	 */
	u32 flags;
#घोषणा CMD_DESC_FIXED    (1<<0)
#घोषणा CMD_DESC_SKIP     (1<<1)
#घोषणा CMD_DESC_REJECT   (1<<2)
#घोषणा CMD_DESC_REGISTER (1<<3)
#घोषणा CMD_DESC_BITMASK  (1<<4)

	/*
	 * The command's unique identअगरication bits and the biपंचांगask to get them.
	 * This isn't strictly the opcode field as defined in the spec and may
	 * also include type, subtype, and/or subop fields.
	 */
	काष्ठा अणु
		u32 value;
		u32 mask;
	पूर्ण cmd;

	/*
	 * The command's length. The command is either fixed length (i.e. करोes
	 * not include a length field) or has a length field mask. The flag
	 * CMD_DESC_FIXED indicates a fixed length. Otherwise, the command has
	 * a length mask. All command entries in a command table must include
	 * length inक्रमmation.
	 */
	जोड़ अणु
		u32 fixed;
		u32 mask;
	पूर्ण length;

	/*
	 * Describes where to find a रेजिस्टर address in the command to check
	 * against the ring's रेजिस्टर whitelist. Only valid अगर flags has the
	 * CMD_DESC_REGISTER bit set.
	 *
	 * A non-zero step value implies that the command may access multiple
	 * रेजिस्टरs in sequence (e.g. LRI), in that हाल step gives the
	 * distance in dwords between inभागidual offset fields.
	 */
	काष्ठा अणु
		u32 offset;
		u32 mask;
		u32 step;
	पूर्ण reg;

#घोषणा MAX_CMD_DESC_BITMASKS 3
	/*
	 * Describes command checks where a particular dword is masked and
	 * compared against an expected value. If the command करोes not match
	 * the expected value, the parser rejects it. Only valid अगर flags has
	 * the CMD_DESC_BITMASK bit set. Only entries where mask is non-zero
	 * are valid.
	 *
	 * If the check specअगरies a non-zero condition_mask then the parser
	 * only perक्रमms the check when the bits specअगरied by condition_mask
	 * are non-zero.
	 */
	काष्ठा अणु
		u32 offset;
		u32 mask;
		u32 expected;
		u32 condition_offset;
		u32 condition_mask;
	पूर्ण bits[MAX_CMD_DESC_BITMASKS];
पूर्ण;

/*
 * A table of commands requiring special handling by the command parser.
 *
 * Each engine has an array of tables. Each table consists of an array of
 * command descriptors, which must be sorted with command opcodes in
 * ascending order.
 */
काष्ठा drm_i915_cmd_table अणु
	स्थिर काष्ठा drm_i915_cmd_descriptor *table;
	पूर्णांक count;
पूर्ण;

#घोषणा STD_MI_OPCODE_SHIFT  (32 - 9)
#घोषणा STD_3D_OPCODE_SHIFT  (32 - 16)
#घोषणा STD_2D_OPCODE_SHIFT  (32 - 10)
#घोषणा STD_MFX_OPCODE_SHIFT (32 - 16)
#घोषणा MIN_OPCODE_SHIFT 16

#घोषणा CMD(op, opm, f, lm, fl, ...)				\
	अणु							\
		.flags = (fl) | ((f) ? CMD_DESC_FIXED : 0),	\
		.cmd = अणु (op & ~0u << (opm)), ~0u << (opm) पूर्ण,	\
		.length = अणु (lm) पूर्ण,				\
		__VA_ARGS__					\
	पूर्ण

/* Convenience macros to compress the tables */
#घोषणा SMI STD_MI_OPCODE_SHIFT
#घोषणा S3D STD_3D_OPCODE_SHIFT
#घोषणा S2D STD_2D_OPCODE_SHIFT
#घोषणा SMFX STD_MFX_OPCODE_SHIFT
#घोषणा F true
#घोषणा S CMD_DESC_SKIP
#घोषणा R CMD_DESC_REJECT
#घोषणा W CMD_DESC_REGISTER
#घोषणा B CMD_DESC_BITMASK

/*            Command                          Mask   Fixed Len   Action
	      ---------------------------------------------------------- */
अटल स्थिर काष्ठा drm_i915_cmd_descriptor gen7_common_cmds[] = अणु
	CMD(  MI_NOOP,                          SMI,    F,  1,      S  ),
	CMD(  MI_USER_INTERRUPT,                SMI,    F,  1,      R  ),
	CMD(  MI_WAIT_FOR_EVENT,                SMI,    F,  1,      R  ),
	CMD(  MI_ARB_CHECK,                     SMI,    F,  1,      S  ),
	CMD(  MI_REPORT_HEAD,                   SMI,    F,  1,      S  ),
	CMD(  MI_SUSPEND_FLUSH,                 SMI,    F,  1,      S  ),
	CMD(  MI_SEMAPHORE_MBOX,                SMI,   !F,  0xFF,   R  ),
	CMD(  MI_STORE_DWORD_INDEX,             SMI,   !F,  0xFF,   R  ),
	CMD(  MI_LOAD_REGISTER_IMM(1),          SMI,   !F,  0xFF,   W,
	      .reg = अणु .offset = 1, .mask = 0x007FFFFC, .step = 2 पूर्ण    ),
	CMD(  MI_STORE_REGISTER_MEM,            SMI,    F,  3,     W | B,
	      .reg = अणु .offset = 1, .mask = 0x007FFFFC पूर्ण,
	      .bits = अणुअणु
			.offset = 0,
			.mask = MI_GLOBAL_GTT,
			.expected = 0,
	      पूर्णपूर्ण,						       ),
	CMD(  MI_LOAD_REGISTER_MEM,             SMI,    F,  3,     W | B,
	      .reg = अणु .offset = 1, .mask = 0x007FFFFC पूर्ण,
	      .bits = अणुअणु
			.offset = 0,
			.mask = MI_GLOBAL_GTT,
			.expected = 0,
	      पूर्णपूर्ण,						       ),
	/*
	 * MI_BATCH_BUFFER_START requires some special handling. It's not
	 * really a 'skip' action but it doesn't seem like it's worth adding
	 * a new action. See पूर्णांकel_engine_cmd_parser().
	 */
	CMD(  MI_BATCH_BUFFER_START,            SMI,   !F,  0xFF,   S  ),
पूर्ण;

अटल स्थिर काष्ठा drm_i915_cmd_descriptor gen7_render_cmds[] = अणु
	CMD(  MI_FLUSH,                         SMI,    F,  1,      S  ),
	CMD(  MI_ARB_ON_OFF,                    SMI,    F,  1,      R  ),
	CMD(  MI_PREDICATE,                     SMI,    F,  1,      S  ),
	CMD(  MI_TOPOLOGY_FILTER,               SMI,    F,  1,      S  ),
	CMD(  MI_SET_APPID,                     SMI,    F,  1,      S  ),
	CMD(  MI_DISPLAY_FLIP,                  SMI,   !F,  0xFF,   R  ),
	CMD(  MI_SET_CONTEXT,                   SMI,   !F,  0xFF,   R  ),
	CMD(  MI_URB_CLEAR,                     SMI,   !F,  0xFF,   S  ),
	CMD(  MI_STORE_DWORD_IMM,               SMI,   !F,  0x3F,   B,
	      .bits = अणुअणु
			.offset = 0,
			.mask = MI_GLOBAL_GTT,
			.expected = 0,
	      पूर्णपूर्ण,						       ),
	CMD(  MI_UPDATE_GTT,                    SMI,   !F,  0xFF,   R  ),
	CMD(  MI_CLFLUSH,                       SMI,   !F,  0x3FF,  B,
	      .bits = अणुअणु
			.offset = 0,
			.mask = MI_GLOBAL_GTT,
			.expected = 0,
	      पूर्णपूर्ण,						       ),
	CMD(  MI_REPORT_PERF_COUNT,             SMI,   !F,  0x3F,   B,
	      .bits = अणुअणु
			.offset = 1,
			.mask = MI_REPORT_PERF_COUNT_GGTT,
			.expected = 0,
	      पूर्णपूर्ण,						       ),
	CMD(  MI_CONDITIONAL_BATCH_BUFFER_END,  SMI,   !F,  0xFF,   B,
	      .bits = अणुअणु
			.offset = 0,
			.mask = MI_GLOBAL_GTT,
			.expected = 0,
	      पूर्णपूर्ण,						       ),
	CMD(  GFX_OP_3DSTATE_VF_STATISTICS,     S3D,    F,  1,      S  ),
	CMD(  PIPELINE_SELECT,                  S3D,    F,  1,      S  ),
	CMD(  MEDIA_VFE_STATE,			S3D,   !F,  0xFFFF, B,
	      .bits = अणुअणु
			.offset = 2,
			.mask = MEDIA_VFE_STATE_MMIO_ACCESS_MASK,
			.expected = 0,
	      पूर्णपूर्ण,						       ),
	CMD(  GPGPU_OBJECT,                     S3D,   !F,  0xFF,   S  ),
	CMD(  GPGPU_WALKER,                     S3D,   !F,  0xFF,   S  ),
	CMD(  GFX_OP_3DSTATE_SO_DECL_LIST,      S3D,   !F,  0x1FF,  S  ),
	CMD(  GFX_OP_PIPE_CONTROL(5),           S3D,   !F,  0xFF,   B,
	      .bits = अणुअणु
			.offset = 1,
			.mask = (PIPE_CONTROL_MMIO_WRITE | PIPE_CONTROL_NOTIFY),
			.expected = 0,
	      पूर्ण,
	      अणु
			.offset = 1,
		        .mask = (PIPE_CONTROL_GLOBAL_GTT_IVB |
				 PIPE_CONTROL_STORE_DATA_INDEX),
			.expected = 0,
			.condition_offset = 1,
			.condition_mask = PIPE_CONTROL_POST_SYNC_OP_MASK,
	      पूर्णपूर्ण,						       ),
पूर्ण;

अटल स्थिर काष्ठा drm_i915_cmd_descriptor hsw_render_cmds[] = अणु
	CMD(  MI_SET_PREDICATE,                 SMI,    F,  1,      S  ),
	CMD(  MI_RS_CONTROL,                    SMI,    F,  1,      S  ),
	CMD(  MI_URB_ATOMIC_ALLOC,              SMI,    F,  1,      S  ),
	CMD(  MI_SET_APPID,                     SMI,    F,  1,      S  ),
	CMD(  MI_RS_CONTEXT,                    SMI,    F,  1,      S  ),
	CMD(  MI_LOAD_SCAN_LINES_INCL,          SMI,   !F,  0x3F,   R  ),
	CMD(  MI_LOAD_SCAN_LINES_EXCL,          SMI,   !F,  0x3F,   R  ),
	CMD(  MI_LOAD_REGISTER_REG,             SMI,   !F,  0xFF,   W,
	      .reg = अणु .offset = 1, .mask = 0x007FFFFC, .step = 1 पूर्ण    ),
	CMD(  MI_RS_STORE_DATA_IMM,             SMI,   !F,  0xFF,   S  ),
	CMD(  MI_LOAD_URB_MEM,                  SMI,   !F,  0xFF,   S  ),
	CMD(  MI_STORE_URB_MEM,                 SMI,   !F,  0xFF,   S  ),
	CMD(  GFX_OP_3DSTATE_DX9_CONSTANTF_VS,  S3D,   !F,  0x7FF,  S  ),
	CMD(  GFX_OP_3DSTATE_DX9_CONSTANTF_PS,  S3D,   !F,  0x7FF,  S  ),

	CMD(  GFX_OP_3DSTATE_BINDING_TABLE_EDIT_VS,  S3D,   !F,  0x1FF,  S  ),
	CMD(  GFX_OP_3DSTATE_BINDING_TABLE_EDIT_GS,  S3D,   !F,  0x1FF,  S  ),
	CMD(  GFX_OP_3DSTATE_BINDING_TABLE_EDIT_HS,  S3D,   !F,  0x1FF,  S  ),
	CMD(  GFX_OP_3DSTATE_BINDING_TABLE_EDIT_DS,  S3D,   !F,  0x1FF,  S  ),
	CMD(  GFX_OP_3DSTATE_BINDING_TABLE_EDIT_PS,  S3D,   !F,  0x1FF,  S  ),
पूर्ण;

अटल स्थिर काष्ठा drm_i915_cmd_descriptor gen7_video_cmds[] = अणु
	CMD(  MI_ARB_ON_OFF,                    SMI,    F,  1,      R  ),
	CMD(  MI_SET_APPID,                     SMI,    F,  1,      S  ),
	CMD(  MI_STORE_DWORD_IMM,               SMI,   !F,  0xFF,   B,
	      .bits = अणुअणु
			.offset = 0,
			.mask = MI_GLOBAL_GTT,
			.expected = 0,
	      पूर्णपूर्ण,						       ),
	CMD(  MI_UPDATE_GTT,                    SMI,   !F,  0x3F,   R  ),
	CMD(  MI_FLUSH_DW,                      SMI,   !F,  0x3F,   B,
	      .bits = अणुअणु
			.offset = 0,
			.mask = MI_FLUSH_DW_NOTIFY,
			.expected = 0,
	      पूर्ण,
	      अणु
			.offset = 1,
			.mask = MI_FLUSH_DW_USE_GTT,
			.expected = 0,
			.condition_offset = 0,
			.condition_mask = MI_FLUSH_DW_OP_MASK,
	      पूर्ण,
	      अणु
			.offset = 0,
			.mask = MI_FLUSH_DW_STORE_INDEX,
			.expected = 0,
			.condition_offset = 0,
			.condition_mask = MI_FLUSH_DW_OP_MASK,
	      पूर्णपूर्ण,						       ),
	CMD(  MI_CONDITIONAL_BATCH_BUFFER_END,  SMI,   !F,  0xFF,   B,
	      .bits = अणुअणु
			.offset = 0,
			.mask = MI_GLOBAL_GTT,
			.expected = 0,
	      पूर्णपूर्ण,						       ),
	/*
	 * MFX_WAIT करोesn't fit the way we handle length क्रम most commands.
	 * It has a length field but it uses a non-standard length bias.
	 * It is always 1 dword though, so just treat it as fixed length.
	 */
	CMD(  MFX_WAIT,                         SMFX,   F,  1,      S  ),
पूर्ण;

अटल स्थिर काष्ठा drm_i915_cmd_descriptor gen7_vecs_cmds[] = अणु
	CMD(  MI_ARB_ON_OFF,                    SMI,    F,  1,      R  ),
	CMD(  MI_SET_APPID,                     SMI,    F,  1,      S  ),
	CMD(  MI_STORE_DWORD_IMM,               SMI,   !F,  0xFF,   B,
	      .bits = अणुअणु
			.offset = 0,
			.mask = MI_GLOBAL_GTT,
			.expected = 0,
	      पूर्णपूर्ण,						       ),
	CMD(  MI_UPDATE_GTT,                    SMI,   !F,  0x3F,   R  ),
	CMD(  MI_FLUSH_DW,                      SMI,   !F,  0x3F,   B,
	      .bits = अणुअणु
			.offset = 0,
			.mask = MI_FLUSH_DW_NOTIFY,
			.expected = 0,
	      पूर्ण,
	      अणु
			.offset = 1,
			.mask = MI_FLUSH_DW_USE_GTT,
			.expected = 0,
			.condition_offset = 0,
			.condition_mask = MI_FLUSH_DW_OP_MASK,
	      पूर्ण,
	      अणु
			.offset = 0,
			.mask = MI_FLUSH_DW_STORE_INDEX,
			.expected = 0,
			.condition_offset = 0,
			.condition_mask = MI_FLUSH_DW_OP_MASK,
	      पूर्णपूर्ण,						       ),
	CMD(  MI_CONDITIONAL_BATCH_BUFFER_END,  SMI,   !F,  0xFF,   B,
	      .bits = अणुअणु
			.offset = 0,
			.mask = MI_GLOBAL_GTT,
			.expected = 0,
	      पूर्णपूर्ण,						       ),
पूर्ण;

अटल स्थिर काष्ठा drm_i915_cmd_descriptor gen7_blt_cmds[] = अणु
	CMD(  MI_DISPLAY_FLIP,                  SMI,   !F,  0xFF,   R  ),
	CMD(  MI_STORE_DWORD_IMM,               SMI,   !F,  0x3FF,  B,
	      .bits = अणुअणु
			.offset = 0,
			.mask = MI_GLOBAL_GTT,
			.expected = 0,
	      पूर्णपूर्ण,						       ),
	CMD(  MI_UPDATE_GTT,                    SMI,   !F,  0x3F,   R  ),
	CMD(  MI_FLUSH_DW,                      SMI,   !F,  0x3F,   B,
	      .bits = अणुअणु
			.offset = 0,
			.mask = MI_FLUSH_DW_NOTIFY,
			.expected = 0,
	      पूर्ण,
	      अणु
			.offset = 1,
			.mask = MI_FLUSH_DW_USE_GTT,
			.expected = 0,
			.condition_offset = 0,
			.condition_mask = MI_FLUSH_DW_OP_MASK,
	      पूर्ण,
	      अणु
			.offset = 0,
			.mask = MI_FLUSH_DW_STORE_INDEX,
			.expected = 0,
			.condition_offset = 0,
			.condition_mask = MI_FLUSH_DW_OP_MASK,
	      पूर्णपूर्ण,						       ),
	CMD(  COLOR_BLT,                        S2D,   !F,  0x3F,   S  ),
	CMD(  SRC_COPY_BLT,                     S2D,   !F,  0x3F,   S  ),
पूर्ण;

अटल स्थिर काष्ठा drm_i915_cmd_descriptor hsw_blt_cmds[] = अणु
	CMD(  MI_LOAD_SCAN_LINES_INCL,          SMI,   !F,  0x3F,   R  ),
	CMD(  MI_LOAD_SCAN_LINES_EXCL,          SMI,   !F,  0x3F,   R  ),
पूर्ण;

/*
 * For Gen9 we can still rely on the h/w to enक्रमce cmd security, and only
 * need to re-enक्रमce the रेजिस्टर access checks. We thereक्रमe only need to
 * teach the cmdparser how to find the end of each command, and identअगरy
 * रेजिस्टर accesses. The table करोesn't need to reject any commands, and so
 * the only commands listed here are:
 *   1) Those that touch रेजिस्टरs
 *   2) Those that करो not have the शेष 8-bit length
 *
 * Note that the शेष MI length mask chosen क्रम this table is 0xFF, not
 * the 0x3F used on older devices. This is because the vast majority of MI
 * cmds on Gen9 use a standard 8-bit Length field.
 * All the Gen9 blitter inकाष्ठाions are standard 0xFF length mask, and
 * none allow access to non-general रेजिस्टरs, so in fact no BLT cmds are
 * included in the table at all.
 *
 */
अटल स्थिर काष्ठा drm_i915_cmd_descriptor gen9_blt_cmds[] = अणु
	CMD(  MI_NOOP,                          SMI,    F,  1,      S  ),
	CMD(  MI_USER_INTERRUPT,                SMI,    F,  1,      S  ),
	CMD(  MI_WAIT_FOR_EVENT,                SMI,    F,  1,      S  ),
	CMD(  MI_FLUSH,                         SMI,    F,  1,      S  ),
	CMD(  MI_ARB_CHECK,                     SMI,    F,  1,      S  ),
	CMD(  MI_REPORT_HEAD,                   SMI,    F,  1,      S  ),
	CMD(  MI_ARB_ON_OFF,                    SMI,    F,  1,      S  ),
	CMD(  MI_SUSPEND_FLUSH,                 SMI,    F,  1,      S  ),
	CMD(  MI_LOAD_SCAN_LINES_INCL,          SMI,   !F,  0x3F,   S  ),
	CMD(  MI_LOAD_SCAN_LINES_EXCL,          SMI,   !F,  0x3F,   S  ),
	CMD(  MI_STORE_DWORD_IMM,               SMI,   !F,  0x3FF,  S  ),
	CMD(  MI_LOAD_REGISTER_IMM(1),          SMI,   !F,  0xFF,   W,
	      .reg = अणु .offset = 1, .mask = 0x007FFFFC, .step = 2 पूर्ण    ),
	CMD(  MI_UPDATE_GTT,                    SMI,   !F,  0x3FF,  S  ),
	CMD(  MI_STORE_REGISTER_MEM_GEN8,       SMI,    F,  4,      W,
	      .reg = अणु .offset = 1, .mask = 0x007FFFFC पूर्ण               ),
	CMD(  MI_FLUSH_DW,                      SMI,   !F,  0x3F,   S  ),
	CMD(  MI_LOAD_REGISTER_MEM_GEN8,        SMI,    F,  4,      W,
	      .reg = अणु .offset = 1, .mask = 0x007FFFFC पूर्ण               ),
	CMD(  MI_LOAD_REGISTER_REG,             SMI,    !F,  0xFF,  W,
	      .reg = अणु .offset = 1, .mask = 0x007FFFFC, .step = 1 पूर्ण    ),

	/*
	 * We allow BB_START but apply further checks. We just sanitize the
	 * basic fields here.
	 */
#घोषणा MI_BB_START_OPERAND_MASK   GENMASK(SMI-1, 0)
#घोषणा MI_BB_START_OPERAND_EXPECT (MI_BATCH_PPGTT_HSW | 1)
	CMD(  MI_BATCH_BUFFER_START_GEN8,       SMI,    !F,  0xFF,  B,
	      .bits = अणुअणु
			.offset = 0,
			.mask = MI_BB_START_OPERAND_MASK,
			.expected = MI_BB_START_OPERAND_EXPECT,
	      पूर्णपूर्ण,						       ),
पूर्ण;

अटल स्थिर काष्ठा drm_i915_cmd_descriptor noop_desc =
	CMD(MI_NOOP, SMI, F, 1, S);

#अघोषित CMD
#अघोषित SMI
#अघोषित S3D
#अघोषित S2D
#अघोषित SMFX
#अघोषित F
#अघोषित S
#अघोषित R
#अघोषित W
#अघोषित B

अटल स्थिर काष्ठा drm_i915_cmd_table gen7_render_cmd_table[] = अणु
	अणु gen7_common_cmds, ARRAY_SIZE(gen7_common_cmds) पूर्ण,
	अणु gen7_render_cmds, ARRAY_SIZE(gen7_render_cmds) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_i915_cmd_table hsw_render_ring_cmd_table[] = अणु
	अणु gen7_common_cmds, ARRAY_SIZE(gen7_common_cmds) पूर्ण,
	अणु gen7_render_cmds, ARRAY_SIZE(gen7_render_cmds) पूर्ण,
	अणु hsw_render_cmds, ARRAY_SIZE(hsw_render_cmds) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_i915_cmd_table gen7_video_cmd_table[] = अणु
	अणु gen7_common_cmds, ARRAY_SIZE(gen7_common_cmds) पूर्ण,
	अणु gen7_video_cmds, ARRAY_SIZE(gen7_video_cmds) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_i915_cmd_table hsw_vebox_cmd_table[] = अणु
	अणु gen7_common_cmds, ARRAY_SIZE(gen7_common_cmds) पूर्ण,
	अणु gen7_vecs_cmds, ARRAY_SIZE(gen7_vecs_cmds) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_i915_cmd_table gen7_blt_cmd_table[] = अणु
	अणु gen7_common_cmds, ARRAY_SIZE(gen7_common_cmds) पूर्ण,
	अणु gen7_blt_cmds, ARRAY_SIZE(gen7_blt_cmds) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_i915_cmd_table hsw_blt_ring_cmd_table[] = अणु
	अणु gen7_common_cmds, ARRAY_SIZE(gen7_common_cmds) पूर्ण,
	अणु gen7_blt_cmds, ARRAY_SIZE(gen7_blt_cmds) पूर्ण,
	अणु hsw_blt_cmds, ARRAY_SIZE(hsw_blt_cmds) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_i915_cmd_table gen9_blt_cmd_table[] = अणु
	अणु gen9_blt_cmds, ARRAY_SIZE(gen9_blt_cmds) पूर्ण,
पूर्ण;


/*
 * Register whitelists, sorted by increasing रेजिस्टर offset.
 */

/*
 * An inभागidual whitelist entry granting access to रेजिस्टर addr.  If
 * mask is non-zero the argument of immediate रेजिस्टर ग_लिखोs will be
 * AND-ed with mask, and the command will be rejected अगर the result
 * करोesn't match value.
 *
 * Registers with non-zero mask are only allowed to be written using
 * LRI.
 */
काष्ठा drm_i915_reg_descriptor अणु
	i915_reg_t addr;
	u32 mask;
	u32 value;
पूर्ण;

/* Convenience macro क्रम adding 32-bit रेजिस्टरs. */
#घोषणा REG32(_reg, ...) \
	अणु .addr = (_reg), __VA_ARGS__ पूर्ण

#घोषणा REG32_IDX(_reg, idx) \
	अणु .addr = _reg(idx) पूर्ण

/*
 * Convenience macro क्रम adding 64-bit रेजिस्टरs.
 *
 * Some रेजिस्टरs that userspace accesses are 64 bits. The रेजिस्टर
 * access commands only allow 32-bit accesses. Hence, we have to include
 * entries क्रम both halves of the 64-bit रेजिस्टरs.
 */
#घोषणा REG64(_reg) \
	अणु .addr = _reg पूर्ण, \
	अणु .addr = _reg ## _UDW पूर्ण

#घोषणा REG64_IDX(_reg, idx) \
	अणु .addr = _reg(idx) पूर्ण, \
	अणु .addr = _reg ## _UDW(idx) पूर्ण

अटल स्थिर काष्ठा drm_i915_reg_descriptor gen7_render_regs[] = अणु
	REG64(GPGPU_THREADS_DISPATCHED),
	REG64(HS_INVOCATION_COUNT),
	REG64(DS_INVOCATION_COUNT),
	REG64(IA_VERTICES_COUNT),
	REG64(IA_PRIMITIVES_COUNT),
	REG64(VS_INVOCATION_COUNT),
	REG64(GS_INVOCATION_COUNT),
	REG64(GS_PRIMITIVES_COUNT),
	REG64(CL_INVOCATION_COUNT),
	REG64(CL_PRIMITIVES_COUNT),
	REG64(PS_INVOCATION_COUNT),
	REG64(PS_DEPTH_COUNT),
	REG64_IDX(RING_TIMESTAMP, RENDER_RING_BASE),
	REG64(MI_PREDICATE_SRC0),
	REG64(MI_PREDICATE_SRC1),
	REG32(GEN7_3DPRIM_END_OFFSET),
	REG32(GEN7_3DPRIM_START_VERTEX),
	REG32(GEN7_3DPRIM_VERTEX_COUNT),
	REG32(GEN7_3DPRIM_INSTANCE_COUNT),
	REG32(GEN7_3DPRIM_START_INSTANCE),
	REG32(GEN7_3DPRIM_BASE_VERTEX),
	REG32(GEN7_GPGPU_DISPATCHDIMX),
	REG32(GEN7_GPGPU_DISPATCHDIMY),
	REG32(GEN7_GPGPU_DISPATCHDIMZ),
	REG64_IDX(RING_TIMESTAMP, BSD_RING_BASE),
	REG64_IDX(GEN7_SO_NUM_PRIMS_WRITTEN, 0),
	REG64_IDX(GEN7_SO_NUM_PRIMS_WRITTEN, 1),
	REG64_IDX(GEN7_SO_NUM_PRIMS_WRITTEN, 2),
	REG64_IDX(GEN7_SO_NUM_PRIMS_WRITTEN, 3),
	REG64_IDX(GEN7_SO_PRIM_STORAGE_NEEDED, 0),
	REG64_IDX(GEN7_SO_PRIM_STORAGE_NEEDED, 1),
	REG64_IDX(GEN7_SO_PRIM_STORAGE_NEEDED, 2),
	REG64_IDX(GEN7_SO_PRIM_STORAGE_NEEDED, 3),
	REG32(GEN7_SO_WRITE_OFFSET(0)),
	REG32(GEN7_SO_WRITE_OFFSET(1)),
	REG32(GEN7_SO_WRITE_OFFSET(2)),
	REG32(GEN7_SO_WRITE_OFFSET(3)),
	REG32(GEN7_L3SQCREG1),
	REG32(GEN7_L3CNTLREG2),
	REG32(GEN7_L3CNTLREG3),
	REG64_IDX(RING_TIMESTAMP, BLT_RING_BASE),
पूर्ण;

अटल स्थिर काष्ठा drm_i915_reg_descriptor hsw_render_regs[] = अणु
	REG64_IDX(HSW_CS_GPR, 0),
	REG64_IDX(HSW_CS_GPR, 1),
	REG64_IDX(HSW_CS_GPR, 2),
	REG64_IDX(HSW_CS_GPR, 3),
	REG64_IDX(HSW_CS_GPR, 4),
	REG64_IDX(HSW_CS_GPR, 5),
	REG64_IDX(HSW_CS_GPR, 6),
	REG64_IDX(HSW_CS_GPR, 7),
	REG64_IDX(HSW_CS_GPR, 8),
	REG64_IDX(HSW_CS_GPR, 9),
	REG64_IDX(HSW_CS_GPR, 10),
	REG64_IDX(HSW_CS_GPR, 11),
	REG64_IDX(HSW_CS_GPR, 12),
	REG64_IDX(HSW_CS_GPR, 13),
	REG64_IDX(HSW_CS_GPR, 14),
	REG64_IDX(HSW_CS_GPR, 15),
	REG32(HSW_SCRATCH1,
	      .mask = ~HSW_SCRATCH1_L3_DATA_ATOMICS_DISABLE,
	      .value = 0),
	REG32(HSW_ROW_CHICKEN3,
	      .mask = ~(HSW_ROW_CHICKEN3_L3_GLOBAL_ATOMICS_DISABLE << 16 |
                        HSW_ROW_CHICKEN3_L3_GLOBAL_ATOMICS_DISABLE),
	      .value = 0),
पूर्ण;

अटल स्थिर काष्ठा drm_i915_reg_descriptor gen7_blt_regs[] = अणु
	REG64_IDX(RING_TIMESTAMP, RENDER_RING_BASE),
	REG64_IDX(RING_TIMESTAMP, BSD_RING_BASE),
	REG32(BCS_SWCTRL),
	REG64_IDX(RING_TIMESTAMP, BLT_RING_BASE),
पूर्ण;

अटल स्थिर काष्ठा drm_i915_reg_descriptor gen9_blt_regs[] = अणु
	REG64_IDX(RING_TIMESTAMP, RENDER_RING_BASE),
	REG64_IDX(RING_TIMESTAMP, BSD_RING_BASE),
	REG32(BCS_SWCTRL),
	REG64_IDX(RING_TIMESTAMP, BLT_RING_BASE),
	REG32_IDX(RING_CTX_TIMESTAMP, BLT_RING_BASE),
	REG64_IDX(BCS_GPR, 0),
	REG64_IDX(BCS_GPR, 1),
	REG64_IDX(BCS_GPR, 2),
	REG64_IDX(BCS_GPR, 3),
	REG64_IDX(BCS_GPR, 4),
	REG64_IDX(BCS_GPR, 5),
	REG64_IDX(BCS_GPR, 6),
	REG64_IDX(BCS_GPR, 7),
	REG64_IDX(BCS_GPR, 8),
	REG64_IDX(BCS_GPR, 9),
	REG64_IDX(BCS_GPR, 10),
	REG64_IDX(BCS_GPR, 11),
	REG64_IDX(BCS_GPR, 12),
	REG64_IDX(BCS_GPR, 13),
	REG64_IDX(BCS_GPR, 14),
	REG64_IDX(BCS_GPR, 15),
पूर्ण;

#अघोषित REG64
#अघोषित REG32

काष्ठा drm_i915_reg_table अणु
	स्थिर काष्ठा drm_i915_reg_descriptor *regs;
	पूर्णांक num_regs;
पूर्ण;

अटल स्थिर काष्ठा drm_i915_reg_table ivb_render_reg_tables[] = अणु
	अणु gen7_render_regs, ARRAY_SIZE(gen7_render_regs) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_i915_reg_table ivb_blt_reg_tables[] = अणु
	अणु gen7_blt_regs, ARRAY_SIZE(gen7_blt_regs) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_i915_reg_table hsw_render_reg_tables[] = अणु
	अणु gen7_render_regs, ARRAY_SIZE(gen7_render_regs) पूर्ण,
	अणु hsw_render_regs, ARRAY_SIZE(hsw_render_regs) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_i915_reg_table hsw_blt_reg_tables[] = अणु
	अणु gen7_blt_regs, ARRAY_SIZE(gen7_blt_regs) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_i915_reg_table gen9_blt_reg_tables[] = अणु
	अणु gen9_blt_regs, ARRAY_SIZE(gen9_blt_regs) पूर्ण,
पूर्ण;

अटल u32 gen7_render_get_cmd_length_mask(u32 cmd_header)
अणु
	u32 client = cmd_header >> INSTR_CLIENT_SHIFT;
	u32 subclient =
		(cmd_header & INSTR_SUBCLIENT_MASK) >> INSTR_SUBCLIENT_SHIFT;

	अगर (client == INSTR_MI_CLIENT)
		वापस 0x3F;
	अन्यथा अगर (client == INSTR_RC_CLIENT) अणु
		अगर (subclient == INSTR_MEDIA_SUBCLIENT)
			वापस 0xFFFF;
		अन्यथा
			वापस 0xFF;
	पूर्ण

	DRM_DEBUG("CMD: Abnormal rcs cmd length! 0x%08X\n", cmd_header);
	वापस 0;
पूर्ण

अटल u32 gen7_bsd_get_cmd_length_mask(u32 cmd_header)
अणु
	u32 client = cmd_header >> INSTR_CLIENT_SHIFT;
	u32 subclient =
		(cmd_header & INSTR_SUBCLIENT_MASK) >> INSTR_SUBCLIENT_SHIFT;
	u32 op = (cmd_header & INSTR_26_TO_24_MASK) >> INSTR_26_TO_24_SHIFT;

	अगर (client == INSTR_MI_CLIENT)
		वापस 0x3F;
	अन्यथा अगर (client == INSTR_RC_CLIENT) अणु
		अगर (subclient == INSTR_MEDIA_SUBCLIENT) अणु
			अगर (op == 6)
				वापस 0xFFFF;
			अन्यथा
				वापस 0xFFF;
		पूर्ण अन्यथा
			वापस 0xFF;
	पूर्ण

	DRM_DEBUG("CMD: Abnormal bsd cmd length! 0x%08X\n", cmd_header);
	वापस 0;
पूर्ण

अटल u32 gen7_blt_get_cmd_length_mask(u32 cmd_header)
अणु
	u32 client = cmd_header >> INSTR_CLIENT_SHIFT;

	अगर (client == INSTR_MI_CLIENT)
		वापस 0x3F;
	अन्यथा अगर (client == INSTR_BC_CLIENT)
		वापस 0xFF;

	DRM_DEBUG("CMD: Abnormal blt cmd length! 0x%08X\n", cmd_header);
	वापस 0;
पूर्ण

अटल u32 gen9_blt_get_cmd_length_mask(u32 cmd_header)
अणु
	u32 client = cmd_header >> INSTR_CLIENT_SHIFT;

	अगर (client == INSTR_MI_CLIENT || client == INSTR_BC_CLIENT)
		वापस 0xFF;

	DRM_DEBUG("CMD: Abnormal blt cmd length! 0x%08X\n", cmd_header);
	वापस 0;
पूर्ण

अटल bool validate_cmds_sorted(स्थिर काष्ठा पूर्णांकel_engine_cs *engine,
				 स्थिर काष्ठा drm_i915_cmd_table *cmd_tables,
				 पूर्णांक cmd_table_count)
अणु
	पूर्णांक i;
	bool ret = true;

	अगर (!cmd_tables || cmd_table_count == 0)
		वापस true;

	क्रम (i = 0; i < cmd_table_count; i++) अणु
		स्थिर काष्ठा drm_i915_cmd_table *table = &cmd_tables[i];
		u32 previous = 0;
		पूर्णांक j;

		क्रम (j = 0; j < table->count; j++) अणु
			स्थिर काष्ठा drm_i915_cmd_descriptor *desc =
				&table->table[j];
			u32 curr = desc->cmd.value & desc->cmd.mask;

			अगर (curr < previous) अणु
				drm_err(&engine->i915->drm,
					"CMD: %s [%d] command table not sorted: "
					"table=%d entry=%d cmd=0x%08X prev=0x%08X\n",
					engine->name, engine->id,
					i, j, curr, previous);
				ret = false;
			पूर्ण

			previous = curr;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल bool check_sorted(स्थिर काष्ठा पूर्णांकel_engine_cs *engine,
			 स्थिर काष्ठा drm_i915_reg_descriptor *reg_table,
			 पूर्णांक reg_count)
अणु
	पूर्णांक i;
	u32 previous = 0;
	bool ret = true;

	क्रम (i = 0; i < reg_count; i++) अणु
		u32 curr = i915_mmio_reg_offset(reg_table[i].addr);

		अगर (curr < previous) अणु
			drm_err(&engine->i915->drm,
				"CMD: %s [%d] register table not sorted: "
				"entry=%d reg=0x%08X prev=0x%08X\n",
				engine->name, engine->id,
				i, curr, previous);
			ret = false;
		पूर्ण

		previous = curr;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool validate_regs_sorted(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	पूर्णांक i;
	स्थिर काष्ठा drm_i915_reg_table *table;

	क्रम (i = 0; i < engine->reg_table_count; i++) अणु
		table = &engine->reg_tables[i];
		अगर (!check_sorted(engine, table->regs, table->num_regs))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

काष्ठा cmd_node अणु
	स्थिर काष्ठा drm_i915_cmd_descriptor *desc;
	काष्ठा hlist_node node;
पूर्ण;

/*
 * Dअगरferent command ranges have dअगरferent numbers of bits क्रम the opcode. For
 * example, MI commands use bits 31:23 जबतक 3D commands use bits 31:16. The
 * problem is that, क्रम example, MI commands use bits 22:16 क्रम other fields
 * such as GGTT vs PPGTT bits. If we include those bits in the mask then when
 * we mask a command from a batch it could hash to the wrong bucket due to
 * non-opcode bits being set. But अगर we करोn't include those bits, some 3D
 * commands may hash to the same bucket due to not including opcode bits that
 * make the command unique. For now, we will risk hashing to the same bucket.
 */
अटल अंतरभूत u32 cmd_header_key(u32 x)
अणु
	चयन (x >> INSTR_CLIENT_SHIFT) अणु
	शेष:
	हाल INSTR_MI_CLIENT:
		वापस x >> STD_MI_OPCODE_SHIFT;
	हाल INSTR_RC_CLIENT:
		वापस x >> STD_3D_OPCODE_SHIFT;
	हाल INSTR_BC_CLIENT:
		वापस x >> STD_2D_OPCODE_SHIFT;
	पूर्ण
पूर्ण

अटल पूर्णांक init_hash_table(काष्ठा पूर्णांकel_engine_cs *engine,
			   स्थिर काष्ठा drm_i915_cmd_table *cmd_tables,
			   पूर्णांक cmd_table_count)
अणु
	पूर्णांक i, j;

	hash_init(engine->cmd_hash);

	क्रम (i = 0; i < cmd_table_count; i++) अणु
		स्थिर काष्ठा drm_i915_cmd_table *table = &cmd_tables[i];

		क्रम (j = 0; j < table->count; j++) अणु
			स्थिर काष्ठा drm_i915_cmd_descriptor *desc =
				&table->table[j];
			काष्ठा cmd_node *desc_node =
				kदो_स्मृति(माप(*desc_node), GFP_KERNEL);

			अगर (!desc_node)
				वापस -ENOMEM;

			desc_node->desc = desc;
			hash_add(engine->cmd_hash, &desc_node->node,
				 cmd_header_key(desc->cmd.value));
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fini_hash_table(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा hlist_node *पंचांगp;
	काष्ठा cmd_node *desc_node;
	पूर्णांक i;

	hash_क्रम_each_safe(engine->cmd_hash, i, पंचांगp, desc_node, node) अणु
		hash_del(&desc_node->node);
		kमुक्त(desc_node);
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_engine_init_cmd_parser() - set cmd parser related fields क्रम an engine
 * @engine: the engine to initialize
 *
 * Optionally initializes fields related to batch buffer command parsing in the
 * काष्ठा पूर्णांकel_engine_cs based on whether the platक्रमm requires software
 * command parsing.
 */
पूर्णांक पूर्णांकel_engine_init_cmd_parser(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	स्थिर काष्ठा drm_i915_cmd_table *cmd_tables;
	पूर्णांक cmd_table_count;
	पूर्णांक ret;

	अगर (!IS_GEN(engine->i915, 7) && !(IS_GEN(engine->i915, 9) &&
					  engine->class == COPY_ENGINE_CLASS))
		वापस 0;

	चयन (engine->class) अणु
	हाल RENDER_CLASS:
		अगर (IS_HASWELL(engine->i915)) अणु
			cmd_tables = hsw_render_ring_cmd_table;
			cmd_table_count =
				ARRAY_SIZE(hsw_render_ring_cmd_table);
		पूर्ण अन्यथा अणु
			cmd_tables = gen7_render_cmd_table;
			cmd_table_count = ARRAY_SIZE(gen7_render_cmd_table);
		पूर्ण

		अगर (IS_HASWELL(engine->i915)) अणु
			engine->reg_tables = hsw_render_reg_tables;
			engine->reg_table_count = ARRAY_SIZE(hsw_render_reg_tables);
		पूर्ण अन्यथा अणु
			engine->reg_tables = ivb_render_reg_tables;
			engine->reg_table_count = ARRAY_SIZE(ivb_render_reg_tables);
		पूर्ण
		engine->get_cmd_length_mask = gen7_render_get_cmd_length_mask;
		अवरोध;
	हाल VIDEO_DECODE_CLASS:
		cmd_tables = gen7_video_cmd_table;
		cmd_table_count = ARRAY_SIZE(gen7_video_cmd_table);
		engine->get_cmd_length_mask = gen7_bsd_get_cmd_length_mask;
		अवरोध;
	हाल COPY_ENGINE_CLASS:
		engine->get_cmd_length_mask = gen7_blt_get_cmd_length_mask;
		अगर (IS_GEN(engine->i915, 9)) अणु
			cmd_tables = gen9_blt_cmd_table;
			cmd_table_count = ARRAY_SIZE(gen9_blt_cmd_table);
			engine->get_cmd_length_mask =
				gen9_blt_get_cmd_length_mask;

			/* BCS Engine unsafe without parser */
			engine->flags |= I915_ENGINE_REQUIRES_CMD_PARSER;
		पूर्ण अन्यथा अगर (IS_HASWELL(engine->i915)) अणु
			cmd_tables = hsw_blt_ring_cmd_table;
			cmd_table_count = ARRAY_SIZE(hsw_blt_ring_cmd_table);
		पूर्ण अन्यथा अणु
			cmd_tables = gen7_blt_cmd_table;
			cmd_table_count = ARRAY_SIZE(gen7_blt_cmd_table);
		पूर्ण

		अगर (IS_GEN(engine->i915, 9)) अणु
			engine->reg_tables = gen9_blt_reg_tables;
			engine->reg_table_count =
				ARRAY_SIZE(gen9_blt_reg_tables);
		पूर्ण अन्यथा अगर (IS_HASWELL(engine->i915)) अणु
			engine->reg_tables = hsw_blt_reg_tables;
			engine->reg_table_count = ARRAY_SIZE(hsw_blt_reg_tables);
		पूर्ण अन्यथा अणु
			engine->reg_tables = ivb_blt_reg_tables;
			engine->reg_table_count = ARRAY_SIZE(ivb_blt_reg_tables);
		पूर्ण
		अवरोध;
	हाल VIDEO_ENHANCEMENT_CLASS:
		cmd_tables = hsw_vebox_cmd_table;
		cmd_table_count = ARRAY_SIZE(hsw_vebox_cmd_table);
		/* VECS can use the same length_mask function as VCS */
		engine->get_cmd_length_mask = gen7_bsd_get_cmd_length_mask;
		अवरोध;
	शेष:
		MISSING_CASE(engine->class);
		जाओ out;
	पूर्ण

	अगर (!validate_cmds_sorted(engine, cmd_tables, cmd_table_count)) अणु
		drm_err(&engine->i915->drm,
			"%s: command descriptions are not sorted\n",
			engine->name);
		जाओ out;
	पूर्ण
	अगर (!validate_regs_sorted(engine)) अणु
		drm_err(&engine->i915->drm,
			"%s: registers are not sorted\n", engine->name);
		जाओ out;
	पूर्ण

	ret = init_hash_table(engine, cmd_tables, cmd_table_count);
	अगर (ret) अणु
		drm_err(&engine->i915->drm,
			"%s: initialised failed!\n", engine->name);
		fini_hash_table(engine);
		जाओ out;
	पूर्ण

	engine->flags |= I915_ENGINE_USING_CMD_PARSER;

out:
	अगर (पूर्णांकel_engine_requires_cmd_parser(engine) &&
	    !पूर्णांकel_engine_using_cmd_parser(engine))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_engine_cleanup_cmd_parser() - clean up cmd parser related fields
 * @engine: the engine to clean up
 *
 * Releases any resources related to command parsing that may have been
 * initialized क्रम the specअगरied engine.
 */
व्योम पूर्णांकel_engine_cleanup_cmd_parser(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अगर (!पूर्णांकel_engine_using_cmd_parser(engine))
		वापस;

	fini_hash_table(engine);
पूर्ण

अटल स्थिर काष्ठा drm_i915_cmd_descriptor*
find_cmd_in_table(काष्ठा पूर्णांकel_engine_cs *engine,
		  u32 cmd_header)
अणु
	काष्ठा cmd_node *desc_node;

	hash_क्रम_each_possible(engine->cmd_hash, desc_node, node,
			       cmd_header_key(cmd_header)) अणु
		स्थिर काष्ठा drm_i915_cmd_descriptor *desc = desc_node->desc;
		अगर (((cmd_header ^ desc->cmd.value) & desc->cmd.mask) == 0)
			वापस desc;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Returns a poपूर्णांकer to a descriptor क्रम the command specअगरied by cmd_header.
 *
 * The caller must supply space क्रम a शेष descriptor via the शेष_desc
 * parameter. If no descriptor क्रम the specअगरied command exists in the engine's
 * command parser tables, this function fills in शेष_desc based on the
 * engine's शेष length encoding and वापसs शेष_desc.
 */
अटल स्थिर काष्ठा drm_i915_cmd_descriptor*
find_cmd(काष्ठा पूर्णांकel_engine_cs *engine,
	 u32 cmd_header,
	 स्थिर काष्ठा drm_i915_cmd_descriptor *desc,
	 काष्ठा drm_i915_cmd_descriptor *शेष_desc)
अणु
	u32 mask;

	अगर (((cmd_header ^ desc->cmd.value) & desc->cmd.mask) == 0)
		वापस desc;

	desc = find_cmd_in_table(engine, cmd_header);
	अगर (desc)
		वापस desc;

	mask = engine->get_cmd_length_mask(cmd_header);
	अगर (!mask)
		वापस शून्य;

	शेष_desc->cmd.value = cmd_header;
	शेष_desc->cmd.mask = ~0u << MIN_OPCODE_SHIFT;
	शेष_desc->length.mask = mask;
	शेष_desc->flags = CMD_DESC_SKIP;
	वापस शेष_desc;
पूर्ण

अटल स्थिर काष्ठा drm_i915_reg_descriptor *
__find_reg(स्थिर काष्ठा drm_i915_reg_descriptor *table, पूर्णांक count, u32 addr)
अणु
	पूर्णांक start = 0, end = count;
	जबतक (start < end) अणु
		पूर्णांक mid = start + (end - start) / 2;
		पूर्णांक ret = addr - i915_mmio_reg_offset(table[mid].addr);
		अगर (ret < 0)
			end = mid;
		अन्यथा अगर (ret > 0)
			start = mid + 1;
		अन्यथा
			वापस &table[mid];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा drm_i915_reg_descriptor *
find_reg(स्थिर काष्ठा पूर्णांकel_engine_cs *engine, u32 addr)
अणु
	स्थिर काष्ठा drm_i915_reg_table *table = engine->reg_tables;
	स्थिर काष्ठा drm_i915_reg_descriptor *reg = शून्य;
	पूर्णांक count = engine->reg_table_count;

	क्रम (; !reg && (count > 0); ++table, --count)
		reg = __find_reg(table->regs, table->num_regs, addr);

	वापस reg;
पूर्ण

/* Returns a vmap'd poपूर्णांकer to dst_obj, which the caller must unmap */
अटल u32 *copy_batch(काष्ठा drm_i915_gem_object *dst_obj,
		       काष्ठा drm_i915_gem_object *src_obj,
		       अचिन्हित दीर्घ offset, अचिन्हित दीर्घ length,
		       व्योम *dst, स्थिर व्योम *src)
अणु
	bool needs_clflush =
		!(src_obj->cache_coherent & I915_BO_CACHE_COHERENT_FOR_READ);

	अगर (src) अणु
		GEM_BUG_ON(!needs_clflush);
		i915_unaligned_स_नकल_from_wc(dst, src + offset, length);
	पूर्ण अन्यथा अणु
		काष्ठा scatterlist *sg;
		व्योम *ptr;
		अचिन्हित पूर्णांक x, sg_ofs;
		अचिन्हित दीर्घ reमुख्य;

		/*
		 * We can aव्योम clflushing partial cachelines beक्रमe the ग_लिखो
		 * अगर we only every ग_लिखो full cache-lines. Since we know that
		 * both the source and destination are in multiples of
		 * PAGE_SIZE, we can simply round up to the next cacheline.
		 * We करोn't care about copying too much here as we only
		 * validate up to the end of the batch.
		 */
		reमुख्य = length;
		अगर (!(dst_obj->cache_coherent & I915_BO_CACHE_COHERENT_FOR_READ))
			reमुख्य = round_up(reमुख्य,
					  boot_cpu_data.x86_clflush_size);

		ptr = dst;
		x = offset_in_page(offset);
		sg = i915_gem_object_get_sg(src_obj, offset >> PAGE_SHIFT, &sg_ofs, false);

		जबतक (reमुख्य) अणु
			अचिन्हित दीर्घ sg_max = sg->length >> PAGE_SHIFT;

			क्रम (; reमुख्य && sg_ofs < sg_max; sg_ofs++) अणु
				अचिन्हित दीर्घ len = min(reमुख्य, PAGE_SIZE - x);
				व्योम *map;

				map = kmap_atomic(nth_page(sg_page(sg), sg_ofs));
				अगर (needs_clflush)
					drm_clflush_virt_range(map + x, len);
				स_नकल(ptr, map + x, len);
				kunmap_atomic(map);

				ptr += len;
				reमुख्य -= len;
				x = 0;
			पूर्ण

			sg_ofs = 0;
			sg = sg_next(sg);
		पूर्ण
	पूर्ण

	स_रखो32(dst + length, 0, (dst_obj->base.size - length) / माप(u32));

	/* dst_obj is वापसed with vmap pinned */
	वापस dst;
पूर्ण

अटल अंतरभूत bool cmd_desc_is(स्थिर काष्ठा drm_i915_cmd_descriptor * स्थिर desc,
			       स्थिर u32 cmd)
अणु
	वापस desc->cmd.value == (cmd & desc->cmd.mask);
पूर्ण

अटल bool check_cmd(स्थिर काष्ठा पूर्णांकel_engine_cs *engine,
		      स्थिर काष्ठा drm_i915_cmd_descriptor *desc,
		      स्थिर u32 *cmd, u32 length)
अणु
	अगर (desc->flags & CMD_DESC_SKIP)
		वापस true;

	अगर (desc->flags & CMD_DESC_REJECT) अणु
		DRM_DEBUG("CMD: Rejected command: 0x%08X\n", *cmd);
		वापस false;
	पूर्ण

	अगर (desc->flags & CMD_DESC_REGISTER) अणु
		/*
		 * Get the distance between inभागidual रेजिस्टर offset
		 * fields अगर the command can perक्रमm more than one
		 * access at a समय.
		 */
		स्थिर u32 step = desc->reg.step ? desc->reg.step : length;
		u32 offset;

		क्रम (offset = desc->reg.offset; offset < length;
		     offset += step) अणु
			स्थिर u32 reg_addr = cmd[offset] & desc->reg.mask;
			स्थिर काष्ठा drm_i915_reg_descriptor *reg =
				find_reg(engine, reg_addr);

			अगर (!reg) अणु
				DRM_DEBUG("CMD: Rejected register 0x%08X in command: 0x%08X (%s)\n",
					  reg_addr, *cmd, engine->name);
				वापस false;
			पूर्ण

			/*
			 * Check the value written to the रेजिस्टर against the
			 * allowed mask/value pair given in the whitelist entry.
			 */
			अगर (reg->mask) अणु
				अगर (cmd_desc_is(desc, MI_LOAD_REGISTER_MEM)) अणु
					DRM_DEBUG("CMD: Rejected LRM to masked register 0x%08X\n",
						  reg_addr);
					वापस false;
				पूर्ण

				अगर (cmd_desc_is(desc, MI_LOAD_REGISTER_REG)) अणु
					DRM_DEBUG("CMD: Rejected LRR to masked register 0x%08X\n",
						  reg_addr);
					वापस false;
				पूर्ण

				अगर (cmd_desc_is(desc, MI_LOAD_REGISTER_IMM(1)) &&
				    (offset + 2 > length ||
				     (cmd[offset + 1] & reg->mask) != reg->value)) अणु
					DRM_DEBUG("CMD: Rejected LRI to masked register 0x%08X\n",
						  reg_addr);
					वापस false;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (desc->flags & CMD_DESC_BITMASK) अणु
		पूर्णांक i;

		क्रम (i = 0; i < MAX_CMD_DESC_BITMASKS; i++) अणु
			u32 dword;

			अगर (desc->bits[i].mask == 0)
				अवरोध;

			अगर (desc->bits[i].condition_mask != 0) अणु
				u32 offset =
					desc->bits[i].condition_offset;
				u32 condition = cmd[offset] &
					desc->bits[i].condition_mask;

				अगर (condition == 0)
					जारी;
			पूर्ण

			अगर (desc->bits[i].offset >= length) अणु
				DRM_DEBUG("CMD: Rejected command 0x%08X, too short to check bitmask (%s)\n",
					  *cmd, engine->name);
				वापस false;
			पूर्ण

			dword = cmd[desc->bits[i].offset] &
				desc->bits[i].mask;

			अगर (dword != desc->bits[i].expected) अणु
				DRM_DEBUG("CMD: Rejected command 0x%08X for bitmask 0x%08X (exp=0x%08X act=0x%08X) (%s)\n",
					  *cmd,
					  desc->bits[i].mask,
					  desc->bits[i].expected,
					  dword, engine->name);
				वापस false;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक check_bbstart(u32 *cmd, u32 offset, u32 length,
			 u32 batch_length,
			 u64 batch_addr,
			 u64 shaकरोw_addr,
			 स्थिर अचिन्हित दीर्घ *jump_whitelist)
अणु
	u64 jump_offset, jump_target;
	u32 target_cmd_offset, target_cmd_index;

	/* For igt compatibility on older platक्रमms */
	अगर (!jump_whitelist) अणु
		DRM_DEBUG("CMD: Rejecting BB_START for ggtt based submission\n");
		वापस -EACCES;
	पूर्ण

	अगर (length != 3) अणु
		DRM_DEBUG("CMD: Recursive BB_START with bad length(%u)\n",
			  length);
		वापस -EINVAL;
	पूर्ण

	jump_target = *(u64 *)(cmd + 1);
	jump_offset = jump_target - batch_addr;

	/*
	 * Any underflow of jump_target is guaranteed to be outside the range
	 * of a u32, so >= test catches both too large and too small
	 */
	अगर (jump_offset >= batch_length) अणु
		DRM_DEBUG("CMD: BB_START to 0x%llx jumps out of BB\n",
			  jump_target);
		वापस -EINVAL;
	पूर्ण

	/*
	 * This cannot overflow a u32 because we alपढ़ोy checked jump_offset
	 * is within the BB, and the batch_length is a u32
	 */
	target_cmd_offset = lower_32_bits(jump_offset);
	target_cmd_index = target_cmd_offset / माप(u32);

	*(u64 *)(cmd + 1) = shaकरोw_addr + target_cmd_offset;

	अगर (target_cmd_index == offset)
		वापस 0;

	अगर (!test_bit(target_cmd_index, jump_whitelist)) अणु
		DRM_DEBUG("CMD: BB_START to 0x%llx not a previously executed cmd\n",
			  jump_target);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अचिन्हित दीर्घ *पूर्णांकel_engine_cmd_parser_alloc_jump_whitelist(u32 batch_length,
							    bool trampoline)
अणु
	अचिन्हित दीर्घ *jmp;

	अगर (trampoline)
		वापस शून्य;

	/*
	 * We expect batch_length to be less than 256KiB क्रम known users,
	 * i.e. we need at most an 8KiB biपंचांगap allocation which should be
	 * reasonably cheap due to kदो_स्मृति caches.
	 */

	/* Prefer to report transient allocation failure rather than hit oom */
	jmp = biपंचांगap_zalloc(DIV_ROUND_UP(batch_length, माप(u32)),
			    GFP_KERNEL | __GFP_RETRY_MAYFAIL | __GFP_NOWARN);
	अगर (!jmp)
		वापस ERR_PTR(-ENOMEM);

	वापस jmp;
पूर्ण

#घोषणा LENGTH_BIAS 2

/**
 * पूर्णांकel_engine_cmd_parser() - parse a batch buffer क्रम privilege violations
 * @engine: the engine on which the batch is to execute
 * @batch: the batch buffer in question
 * @batch_offset: byte offset in the batch at which execution starts
 * @batch_length: length of the commands in batch_obj
 * @shaकरोw: validated copy of the batch buffer in question
 * @trampoline: whether to emit a conditional trampoline at the end of the batch
 *
 * Parses the specअगरied batch buffer looking क्रम privilege violations as
 * described in the overview.
 *
 * Return: non-zero अगर the parser finds violations or otherwise fails; -EACCES
 * अगर the batch appears legal but should use hardware parsing
 */
पूर्णांक पूर्णांकel_engine_cmd_parser(काष्ठा पूर्णांकel_engine_cs *engine,
			    काष्ठा i915_vma *batch,
			    अचिन्हित दीर्घ batch_offset,
			    अचिन्हित दीर्घ batch_length,
			    काष्ठा i915_vma *shaकरोw,
			    अचिन्हित दीर्घ *jump_whitelist,
			    व्योम *shaकरोw_map,
			    स्थिर व्योम *batch_map)
अणु
	u32 *cmd, *batch_end, offset = 0;
	काष्ठा drm_i915_cmd_descriptor शेष_desc = noop_desc;
	स्थिर काष्ठा drm_i915_cmd_descriptor *desc = &शेष_desc;
	u64 batch_addr, shaकरोw_addr;
	पूर्णांक ret = 0;
	bool trampoline = !jump_whitelist;

	GEM_BUG_ON(!IS_ALIGNED(batch_offset, माप(*cmd)));
	GEM_BUG_ON(!IS_ALIGNED(batch_length, माप(*cmd)));
	GEM_BUG_ON(range_overflows_t(u64, batch_offset, batch_length,
				     batch->size));
	GEM_BUG_ON(!batch_length);

	cmd = copy_batch(shaकरोw->obj, batch->obj, batch_offset, batch_length,
			 shaकरोw_map, batch_map);

	shaकरोw_addr = gen8_canonical_addr(shaकरोw->node.start);
	batch_addr = gen8_canonical_addr(batch->node.start + batch_offset);

	/*
	 * We use the batch length as size because the shaकरोw object is as
	 * large or larger and copy_batch() will ग_लिखो MI_NOPs to the extra
	 * space. Parsing should be faster in some हालs this way.
	 */
	batch_end = cmd + batch_length / माप(*batch_end);
	जबतक (*cmd != MI_BATCH_BUFFER_END) अणु
		u32 length = 1;

		अगर (*cmd != MI_NOOP) अणु /* MI_NOOP == 0 */
			desc = find_cmd(engine, *cmd, desc, &शेष_desc);
			अगर (!desc) अणु
				DRM_DEBUG("CMD: Unrecognized command: 0x%08X\n", *cmd);
				ret = -EINVAL;
				अवरोध;
			पूर्ण

			अगर (desc->flags & CMD_DESC_FIXED)
				length = desc->length.fixed;
			अन्यथा
				length = (*cmd & desc->length.mask) + LENGTH_BIAS;

			अगर ((batch_end - cmd) < length) अणु
				DRM_DEBUG("CMD: Command length exceeds batch length: 0x%08X length=%u batchlen=%td\n",
					  *cmd,
					  length,
					  batch_end - cmd);
				ret = -EINVAL;
				अवरोध;
			पूर्ण

			अगर (!check_cmd(engine, desc, cmd, length)) अणु
				ret = -EACCES;
				अवरोध;
			पूर्ण

			अगर (cmd_desc_is(desc, MI_BATCH_BUFFER_START)) अणु
				ret = check_bbstart(cmd, offset, length, batch_length,
						    batch_addr, shaकरोw_addr,
						    jump_whitelist);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!IS_ERR_OR_शून्य(jump_whitelist))
			__set_bit(offset, jump_whitelist);

		cmd += length;
		offset += length;
		अगर  (cmd >= batch_end) अणु
			DRM_DEBUG("CMD: Got to the end of the buffer w/o a BBE cmd!\n");
			ret = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (trampoline) अणु
		/*
		 * With the trampoline, the shaकरोw is executed twice.
		 *
		 *   1 - starting at offset 0, in privileged mode
		 *   2 - starting at offset batch_len, as non-privileged
		 *
		 * Only अगर the batch is valid and safe to execute, करो we
		 * allow the first privileged execution to proceed. If not,
		 * we terminate the first batch and use the second batchbuffer
		 * entry to chain to the original unsafe non-privileged batch,
		 * leaving it to the HW to validate.
		 */
		*batch_end = MI_BATCH_BUFFER_END;

		अगर (ret) अणु
			/* Batch unsafe to execute with privileges, cancel! */
			cmd = page_mask_bits(shaकरोw->obj->mm.mapping);
			*cmd = MI_BATCH_BUFFER_END;

			/* If batch is unsafe but valid, jump to the original */
			अगर (ret == -EACCES) अणु
				अचिन्हित पूर्णांक flags;

				flags = MI_BATCH_NON_SECURE_I965;
				अगर (IS_HASWELL(engine->i915))
					flags = MI_BATCH_NON_SECURE_HSW;

				GEM_BUG_ON(!IS_GEN_RANGE(engine->i915, 6, 7));
				__gen6_emit_bb_start(batch_end,
						     batch_addr,
						     flags);

				ret = 0; /* allow execution */
			पूर्ण
		पूर्ण
	पूर्ण

	i915_gem_object_flush_map(shaकरोw->obj);

	वापस ret;
पूर्ण

/**
 * i915_cmd_parser_get_version() - get the cmd parser version number
 * @dev_priv: i915 device निजी
 *
 * The cmd parser मुख्यtains a simple increasing पूर्णांकeger version number suitable
 * क्रम passing to userspace clients to determine what operations are permitted.
 *
 * Return: the current version number of the cmd parser
 */
पूर्णांक i915_cmd_parser_get_version(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	bool active = false;

	/* If the command parser is not enabled, report 0 - unsupported */
	क्रम_each_uabi_engine(engine, dev_priv) अणु
		अगर (पूर्णांकel_engine_using_cmd_parser(engine)) अणु
			active = true;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!active)
		वापस 0;

	/*
	 * Command parser version history
	 *
	 * 1. Initial version. Checks batches and reports violations, but leaves
	 *    hardware parsing enabled (so करोes not allow new use हालs).
	 * 2. Allow access to the MI_PREDICATE_SRC0 and
	 *    MI_PREDICATE_SRC1 रेजिस्टरs.
	 * 3. Allow access to the GPGPU_THREADS_DISPATCHED रेजिस्टर.
	 * 4. L3 atomic chicken bits of HSW_SCRATCH1 and HSW_ROW_CHICKEN3.
	 * 5. GPGPU dispatch compute indirect रेजिस्टरs.
	 * 6. TIMESTAMP रेजिस्टर and Haswell CS GPR रेजिस्टरs
	 * 7. Allow MI_LOAD_REGISTER_REG between whitelisted रेजिस्टरs.
	 * 8. Don't report cmd_check() failures as EINVAL errors to userspace;
	 *    rely on the HW to NOOP disallowed commands as it would without
	 *    the parser enabled.
	 * 9. Don't whitelist or handle oacontrol specially, as ownership
	 *    क्रम oacontrol state is moving to i915-perf.
	 * 10. Support क्रम Gen9 BCS Parsing
	 */
	वापस 10;
पूर्ण
