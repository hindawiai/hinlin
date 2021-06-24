<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// Copyright 2020 NXP
//
// Common helpers क्रम the audio DSP on i.MX8

#समावेश <linux/module.h>
#समावेश <sound/sof/xtensa.h>
#समावेश "../ops.h"

#समावेश "imx-common.h"

/**
 * imx8_get_रेजिस्टरs() - This function is called in हाल of DSP oops
 * in order to gather inक्रमmation about the रेजिस्टरs, filename and
 * linक्रमागतber and stack.
 * @sdev: SOF device
 * @xoops: Stores inक्रमmation about रेजिस्टरs.
 * @panic_info: Stores inक्रमmation about filename and line number.
 * @stack: Stores the stack dump.
 * @stack_words: Size of the stack dump.
 */
व्योम imx8_get_रेजिस्टरs(काष्ठा snd_sof_dev *sdev,
			काष्ठा sof_ipc_dsp_oops_xtensa *xoops,
			काष्ठा sof_ipc_panic_info *panic_info,
			u32 *stack, माप_प्रकार stack_words)
अणु
	u32 offset = sdev->dsp_oops_offset;

	/* first पढ़ो रेजिस्टरs */
	sof_mailbox_पढ़ो(sdev, offset, xoops, माप(*xoops));

	/* then get panic info */
	अगर (xoops->arch_hdr.totalsize > EXCEPT_MAX_HDR_SIZE) अणु
		dev_err(sdev->dev, "invalid header size 0x%x. FW oops is bogus\n",
			xoops->arch_hdr.totalsize);
		वापस;
	पूर्ण
	offset += xoops->arch_hdr.totalsize;
	sof_mailbox_पढ़ो(sdev, offset, panic_info, माप(*panic_info));

	/* then get the stack */
	offset += माप(*panic_info);
	sof_mailbox_पढ़ो(sdev, offset, stack, stack_words * माप(u32));
पूर्ण

/**
 * imx8_dump() - This function is called when a panic message is
 * received from the firmware.
 * @sdev: SOF device
 * @flags: parameter not used but required by ops prototype
 */
व्योम imx8_dump(काष्ठा snd_sof_dev *sdev, u32 flags)
अणु
	काष्ठा sof_ipc_dsp_oops_xtensa xoops;
	काष्ठा sof_ipc_panic_info panic_info;
	u32 stack[IMX8_STACK_DUMP_SIZE];
	u32 status;

	/* Get inक्रमmation about the panic status from the debug box area.
	 * Compute the trace poपूर्णांक based on the status.
	 */
	sof_mailbox_पढ़ो(sdev, sdev->debug_box.offset + 0x4, &status, 4);

	/* Get inक्रमmation about the रेजिस्टरs, the filename and line
	 * number and the stack.
	 */
	imx8_get_रेजिस्टरs(sdev, &xoops, &panic_info, stack,
			   IMX8_STACK_DUMP_SIZE);

	/* Prपूर्णांक the inक्रमmation to the console */
	snd_sof_get_status(sdev, status, status, &xoops, &panic_info, stack,
			   IMX8_STACK_DUMP_SIZE);
पूर्ण
EXPORT_SYMBOL(imx8_dump);

MODULE_LICENSE("Dual BSD/GPL");
