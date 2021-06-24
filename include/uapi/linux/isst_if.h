<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Intel Speed Select Interface: OS to hardware Interface
 * Copyright (c) 2019, Intel Corporation.
 * All rights reserved.
 *
 * Author: Srinivas Pandruvada <srinivas.pandruvada@linux.पूर्णांकel.com>
 */

#अगर_अघोषित __ISST_IF_H
#घोषणा __ISST_IF_H

#समावेश <linux/types.h>

/**
 * काष्ठा isst_अगर_platक्रमm_info - Define platक्रमm inक्रमmation
 * @api_version:	Version of the firmware करोcument, which this driver
 *			can communicate
 * @driver_version:	Driver version, which will help user to send right
 *			commands. Even अगर the firmware is capable, driver may
 *			not be पढ़ोy
 * @max_cmds_per_ioctl:	Returns the maximum number of commands driver will
 *			accept in a single ioctl
 * @mbox_supported:	Support of mail box पूर्णांकerface
 * @mmio_supported:	Support of mmio पूर्णांकerface क्रम core-घातer feature
 *
 * Used to वापस output of IOCTL ISST_IF_GET_PLATFORM_INFO. This
 * inक्रमmation can be used by the user space, to get the driver, firmware
 * support and also number of commands to send in a single IOCTL request.
 */
काष्ठा isst_अगर_platक्रमm_info अणु
	__u16 api_version;
	__u16 driver_version;
	__u16 max_cmds_per_ioctl;
	__u8 mbox_supported;
	__u8 mmio_supported;
पूर्ण;

/**
 * काष्ठा isst_अगर_cpu_map - CPU mapping between logical and physical CPU
 * @logical_cpu:	Linux logical CPU number
 * @physical_cpu:	PUNIT CPU number
 *
 * Used to convert from Linux logical CPU to PUNIT CPU numbering scheme.
 * The PUNIT CPU number is dअगरferent than APIC ID based CPU numbering.
 */
काष्ठा isst_अगर_cpu_map अणु
	__u32 logical_cpu;
	__u32 physical_cpu;
पूर्ण;

/**
 * काष्ठा isst_अगर_cpu_maps - काष्ठाure क्रम CPU map IOCTL
 * @cmd_count:	Number of CPU mapping command in cpu_map[]
 * @cpu_map[]:	Holds one or more CPU map data काष्ठाure
 *
 * This काष्ठाure used with ioctl ISST_IF_GET_PHY_ID to send
 * one or more CPU mapping commands. Here IOCTL वापस value indicates
 * number of commands sent or error number अगर no commands have been sent.
 */
काष्ठा isst_अगर_cpu_maps अणु
	__u32 cmd_count;
	काष्ठा isst_अगर_cpu_map cpu_map[1];
पूर्ण;

/**
 * काष्ठा isst_अगर_io_reg - Read ग_लिखो PUNIT IO रेजिस्टर
 * @पढ़ो_ग_लिखो:		Value 0: Read, 1: Write
 * @logical_cpu:	Logical CPU number to get target PCI device.
 * @reg:		PUNIT रेजिस्टर offset
 * @value:		For ग_लिखो operation value to ग_लिखो and क्रम
 *			पढ़ो placeholder पढ़ो value
 *
 * Structure to specअगरy पढ़ो/ग_लिखो data to PUNIT रेजिस्टरs.
 */
काष्ठा isst_अगर_io_reg अणु
	__u32 पढ़ो_ग_लिखो; /* Read:0, Write:1 */
	__u32 logical_cpu;
	__u32 reg;
	__u32 value;
पूर्ण;

/**
 * काष्ठा isst_अगर_io_regs - काष्ठाure क्रम IO रेजिस्टर commands
 * @cmd_count:	Number of io reg commands in io_reg[]
 * @io_reg[]:	Holds one or more io_reg command काष्ठाure
 *
 * This काष्ठाure used with ioctl ISST_IF_IO_CMD to send
 * one or more पढ़ो/ग_लिखो commands to PUNIT. Here IOCTL वापस value
 * indicates number of requests sent or error number अगर no requests have
 * been sent.
 */
काष्ठा isst_अगर_io_regs अणु
	__u32 req_count;
	काष्ठा isst_अगर_io_reg io_reg[1];
पूर्ण;

/**
 * काष्ठा isst_अगर_mbox_cmd - Structure to define mail box command
 * @logical_cpu:	Logical CPU number to get target PCI device
 * @parameter:		Mailbox parameter value
 * @req_data:		Request data क्रम the mailbox
 * @resp_data:		Response data क्रम mailbox command response
 * @command:		Mailbox command value
 * @sub_command:	Mailbox sub command value
 * @reserved:		Unused, set to 0
 *
 * Structure to specअगरy mailbox command to be sent to PUNIT.
 */
काष्ठा isst_अगर_mbox_cmd अणु
	__u32 logical_cpu;
	__u32 parameter;
	__u32 req_data;
	__u32 resp_data;
	__u16 command;
	__u16 sub_command;
	__u32 reserved;
पूर्ण;

/**
 * काष्ठा isst_अगर_mbox_cmds - काष्ठाure क्रम mailbox commands
 * @cmd_count:	Number of mailbox commands in mbox_cmd[]
 * @mbox_cmd[]:	Holds one or more mbox commands
 *
 * This काष्ठाure used with ioctl ISST_IF_MBOX_COMMAND to send
 * one or more mailbox commands to PUNIT. Here IOCTL वापस value
 * indicates number of commands sent or error number अगर no commands have
 * been sent.
 */
काष्ठा isst_अगर_mbox_cmds अणु
	__u32 cmd_count;
	काष्ठा isst_अगर_mbox_cmd mbox_cmd[1];
पूर्ण;

/**
 * काष्ठा isst_अगर_msr_cmd - Structure to define msr command
 * @पढ़ो_ग_लिखो:		Value 0: Read, 1: Write
 * @logical_cpu:	Logical CPU number
 * @msr:		MSR number
 * @data:		For ग_लिखो operation, data to ग_लिखो, क्रम पढ़ो
 *			place holder
 *
 * Structure to specअगरy MSR command related to PUNIT.
 */
काष्ठा isst_अगर_msr_cmd अणु
	__u32 पढ़ो_ग_लिखो; /* Read:0, Write:1 */
	__u32 logical_cpu;
	__u64 msr;
	__u64 data;
पूर्ण;

/**
 * काष्ठा isst_अगर_msr_cmds - काष्ठाure क्रम msr commands
 * @cmd_count:	Number of mailbox commands in msr_cmd[]
 * @msr_cmd[]:	Holds one or more msr commands
 *
 * This काष्ठाure used with ioctl ISST_IF_MSR_COMMAND to send
 * one or more MSR commands. IOCTL वापस value indicates number of
 * commands sent or error number अगर no commands have been sent.
 */
काष्ठा isst_अगर_msr_cmds अणु
	__u32 cmd_count;
	काष्ठा isst_अगर_msr_cmd msr_cmd[1];
पूर्ण;

#घोषणा ISST_IF_MAGIC			0xFE
#घोषणा ISST_IF_GET_PLATFORM_INFO	_IOR(ISST_IF_MAGIC, 0, काष्ठा isst_अगर_platक्रमm_info *)
#घोषणा ISST_IF_GET_PHY_ID		_IOWR(ISST_IF_MAGIC, 1, काष्ठा isst_अगर_cpu_map *)
#घोषणा ISST_IF_IO_CMD		_IOW(ISST_IF_MAGIC, 2, काष्ठा isst_अगर_io_regs *)
#घोषणा ISST_IF_MBOX_COMMAND	_IOWR(ISST_IF_MAGIC, 3, काष्ठा isst_अगर_mbox_cmds *)
#घोषणा ISST_IF_MSR_COMMAND	_IOWR(ISST_IF_MAGIC, 4, काष्ठा isst_अगर_msr_cmds *)
#पूर्ण_अगर
