<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * CXL IOCTLs क्रम Memory Devices
 */

#अगर_अघोषित _UAPI_CXL_MEM_H_
#घोषणा _UAPI_CXL_MEM_H_

#समावेश <linux/types.h>

/**
 * DOC: UAPI
 *
 * Not all of all commands that the driver supports are always available क्रम use
 * by userspace. Userspace must check the results from the QUERY command in
 * order to determine the live set of commands.
 */

#घोषणा CXL_MEM_QUERY_COMMANDS _IOR(0xCE, 1, काष्ठा cxl_mem_query_commands)
#घोषणा CXL_MEM_SEND_COMMAND _IOWR(0xCE, 2, काष्ठा cxl_send_command)

#घोषणा CXL_CMDS                                                          \
	___C(INVALID, "Invalid Command"),                                 \
	___C(IDENTIFY, "Identify Command"),                               \
	___C(RAW, "Raw device command"),                                  \
	___C(GET_SUPPORTED_LOGS, "Get Supported Logs"),                   \
	___C(GET_FW_INFO, "Get FW Info"),                                 \
	___C(GET_PARTITION_INFO, "Get Partition Information"),            \
	___C(GET_LSA, "Get Label Storage Area"),                          \
	___C(GET_HEALTH_INFO, "Get Health Info"),                         \
	___C(GET_LOG, "Get Log"),                                         \
	___C(MAX, "invalid / last command")

#घोषणा ___C(a, b) CXL_MEM_COMMAND_ID_##a
क्रमागत अणु CXL_CMDS पूर्ण;

#अघोषित ___C
#घोषणा ___C(a, b) अणु b पूर्ण
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
पूर्ण cxl_command_names[] = अणु CXL_CMDS पूर्ण;

/*
 * Here's how this actually अवरोधs out:
 * cxl_command_names[] = अणु
 *	[CXL_MEM_COMMAND_ID_INVALID] = अणु "Invalid Command" पूर्ण,
 *	[CXL_MEM_COMMAND_ID_IDENTIFY] = अणु "Identify Command" पूर्ण,
 *	...
 *	[CXL_MEM_COMMAND_ID_MAX] = अणु "invalid / last command" पूर्ण,
 * पूर्ण;
 */

#अघोषित ___C

/**
 * काष्ठा cxl_command_info - Command inक्रमmation वापसed from a query.
 * @id: ID number क्रम the command.
 * @flags: Flags that specअगरy command behavior.
 * @size_in: Expected input size, or -1 अगर variable length.
 * @size_out: Expected output size, or -1 अगर variable length.
 *
 * Represents a single command that is supported by both the driver and the
 * hardware. This is वापसed as part of an array from the query ioctl. The
 * following would be a command that takes a variable length input and वापसs 0
 * bytes of output.
 *
 *  - @id = 10
 *  - @flags = 0
 *  - @size_in = -1
 *  - @size_out = 0
 *
 * See काष्ठा cxl_mem_query_commands.
 */
काष्ठा cxl_command_info अणु
	__u32 id;

	__u32 flags;
#घोषणा CXL_MEM_COMMAND_FLAG_MASK GENMASK(0, 0)

	__s32 size_in;
	__s32 size_out;
पूर्ण;

/**
 * काष्ठा cxl_mem_query_commands - Query supported commands.
 * @n_commands: In/out parameter. When @n_commands is > 0, the driver will
 *		वापस min(num_support_commands, n_commands). When @n_commands
 *		is 0, driver will वापस the number of total supported commands.
 * @rsvd: Reserved क्रम future use.
 * @commands: Output array of supported commands. This array must be allocated
 *            by userspace to be at least min(num_support_commands, @n_commands)
 *
 * Allow userspace to query the available commands supported by both the driver,
 * and the hardware. Commands that aren't supported by either the driver, or the
 * hardware are not वापसed in the query.
 *
 * Examples:
 *
 *  - अणु .n_commands = 0 पूर्ण // Get number of supported commands
 *  - अणु .n_commands = 15, .commands = buf पूर्ण // Return first 15 (or less)
 *    supported commands
 *
 *  See काष्ठा cxl_command_info.
 */
काष्ठा cxl_mem_query_commands अणु
	/*
	 * Input: Number of commands to वापस (space allocated by user)
	 * Output: Number of commands supported by the driver/hardware
	 *
	 * If n_commands is 0, kernel will only वापस number of commands and
	 * not try to populate commands[], thus allowing userspace to know how
	 * much space to allocate
	 */
	__u32 n_commands;
	__u32 rsvd;

	काष्ठा cxl_command_info __user commands[]; /* out: supported commands */
पूर्ण;

/**
 * काष्ठा cxl_send_command - Send a command to a memory device.
 * @id: The command to send to the memory device. This must be one of the
 *	commands वापसed by the query command.
 * @flags: Flags क्रम the command (input).
 * @raw: Special fields क्रम raw commands
 * @raw.opcode: Opcode passed to hardware when using the RAW command.
 * @raw.rsvd: Must be zero.
 * @rsvd: Must be zero.
 * @retval: Return value from the memory device (output).
 * @in: Parameters associated with input payload.
 * @in.size: Size of the payload to provide to the device (input).
 * @in.rsvd: Must be zero.
 * @in.payload: Poपूर्णांकer to memory क्रम payload input, payload is little endian.
 * @out: Parameters associated with output payload.
 * @out.size: Size of the payload received from the device (input/output). This
 *	      field is filled in by userspace to let the driver know how much
 *	      space was allocated क्रम output. It is populated by the driver to
 *	      let userspace know how large the output payload actually was.
 * @out.rsvd: Must be zero.
 * @out.payload: Poपूर्णांकer to memory क्रम payload output, payload is little endian.
 *
 * Mechanism क्रम userspace to send a command to the hardware क्रम processing. The
 * driver will करो basic validation on the command sizes. In some हालs even the
 * payload may be पूर्णांकrospected. Userspace is required to allocate large enough
 * buffers क्रम size_out which can be variable length in certain situations.
 */
काष्ठा cxl_send_command अणु
	__u32 id;
	__u32 flags;
	जोड़ अणु
		काष्ठा अणु
			__u16 opcode;
			__u16 rsvd;
		पूर्ण raw;
		__u32 rsvd;
	पूर्ण;
	__u32 retval;

	काष्ठा अणु
		__s32 size;
		__u32 rsvd;
		__u64 payload;
	पूर्ण in;

	काष्ठा अणु
		__s32 size;
		__u32 rsvd;
		__u64 payload;
	पूर्ण out;
पूर्ण;

#पूर्ण_अगर
