<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Intel Speed Select Interface: Drivers Internal defines
 * Copyright (c) 2019, Intel Corporation.
 * All rights reserved.
 *
 * Author: Srinivas Pandruvada <srinivas.pandruvada@linux.पूर्णांकel.com>
 */

#अगर_अघोषित __ISST_IF_COMMON_H
#घोषणा __ISST_IF_COMMON_H

#घोषणा PCI_DEVICE_ID_INTEL_RAPL_PRIO_DEVID_0	0x3451
#घोषणा PCI_DEVICE_ID_INTEL_CFG_MBOX_DEVID_0	0x3459

#घोषणा PCI_DEVICE_ID_INTEL_RAPL_PRIO_DEVID_1	0x3251
#घोषणा PCI_DEVICE_ID_INTEL_CFG_MBOX_DEVID_1	0x3259

/*
 * Validate maximum commands in a single request.
 * This is enough to handle command to every core in one ioctl, or all
 * possible message id to one CPU. Limit is also helpful क्रम resonse समय
 * per IOCTL request, as PUNIT may take dअगरferent बार to process each
 * request and may hold क्रम दीर्घ क्रम too many commands.
 */
#घोषणा ISST_IF_CMD_LIMIT	64

#घोषणा ISST_IF_API_VERSION	0x01
#घोषणा ISST_IF_DRIVER_VERSION	0x01

#घोषणा ISST_IF_DEV_MBOX	0
#घोषणा ISST_IF_DEV_MMIO	1
#घोषणा ISST_IF_DEV_MAX		2

/**
 * काष्ठा isst_अगर_cmd_cb - Used to रेजिस्टर a IOCTL handler
 * @रेजिस्टरed:	Used by the common code to store registry. Caller करोn't
 *		to touch this field
 * @cmd_size:	The command size of the inभागidual command in IOCTL
 * @offset:	Offset to the first valid member in command काष्ठाure.
 *		This will be the offset of the start of the command
 *		after command count field
 * @cmd_callback: Callback function to handle IOCTL. The callback has the
 *		command poपूर्णांकer with data क्रम command. There is a poपूर्णांकer
 *		called ग_लिखो_only, which when set, will not copy the
 *		response to user ioctl buffer. The "resume" argument
 *		can be used to aव्योम storing the command क्रम replay
 *		during प्रणाली resume
 *
 * This काष्ठाure is used to रेजिस्टर an handler क्रम IOCTL. To aव्योम
 * code duplication common code handles all the IOCTL command पढ़ो/ग_लिखो
 * including handling multiple command in single IOCTL. The caller just
 * need to execute a command via the रेजिस्टरed callback.
 */
काष्ठा isst_अगर_cmd_cb अणु
	पूर्णांक रेजिस्टरed;
	पूर्णांक cmd_size;
	पूर्णांक offset;
	काष्ठा module *owner;
	दीर्घ (*cmd_callback)(u8 *ptr, पूर्णांक *ग_लिखो_only, पूर्णांक resume);
पूर्ण;

/* Internal पूर्णांकerface functions */
पूर्णांक isst_अगर_cdev_रेजिस्टर(पूर्णांक type, काष्ठा isst_अगर_cmd_cb *cb);
व्योम isst_अगर_cdev_unरेजिस्टर(पूर्णांक type);
काष्ठा pci_dev *isst_अगर_get_pci_dev(पूर्णांक cpu, पूर्णांक bus, पूर्णांक dev, पूर्णांक fn);
bool isst_अगर_mbox_cmd_set_req(काष्ठा isst_अगर_mbox_cmd *mbox_cmd);
bool isst_अगर_mbox_cmd_invalid(काष्ठा isst_अगर_mbox_cmd *cmd);
पूर्णांक isst_store_cmd(पूर्णांक cmd, पूर्णांक sub_command, u32 cpu, पूर्णांक mbox_cmd,
		   u32 param, u64 data);
व्योम isst_resume_common(व्योम);
#पूर्ण_अगर
