<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    driver क्रम Microsemi PQI-based storage controllers
 *    Copyright (c) 2019-2020 Microchip Technology Inc. and its subsidiaries
 *    Copyright (c) 2016-2018 Microsemi Corporation
 *    Copyright (c) 2016 PMC-Sierra, Inc.
 *
 *    Questions/Comments/Bugfixes to storagedev@microchip.com
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <scsi/scsi_device.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "smartpqi.h"
#समावेश "smartpqi_sis.h"

/* legacy SIS पूर्णांकerface commands */
#घोषणा SIS_CMD_GET_ADAPTER_PROPERTIES		0x19
#घोषणा SIS_CMD_INIT_BASE_STRUCT_ADDRESS	0x1b
#घोषणा SIS_CMD_GET_PQI_CAPABILITIES		0x3000

/* क्रम submission of legacy SIS commands */
#घोषणा SIS_REENABLE_SIS_MODE			0x1
#घोषणा SIS_ENABLE_MSIX				0x40
#घोषणा SIS_ENABLE_INTX				0x80
#घोषणा SIS_SOFT_RESET				0x100
#घोषणा SIS_CMD_READY				0x200
#घोषणा SIS_TRIGGER_SHUTDOWN			0x800000
#घोषणा SIS_PQI_RESET_QUIESCE			0x1000000

#घोषणा SIS_CMD_COMPLETE			0x1000
#घोषणा SIS_CLEAR_CTRL_TO_HOST_DOORBELL		0x1000

#घोषणा SIS_CMD_STATUS_SUCCESS			0x1
#घोषणा SIS_CMD_COMPLETE_TIMEOUT_SECS		30
#घोषणा SIS_CMD_COMPLETE_POLL_INTERVAL_MSECS	10

/* used with SIS_CMD_GET_ADAPTER_PROPERTIES command */
#घोषणा SIS_EXTENDED_PROPERTIES_SUPPORTED	0x800000
#घोषणा SIS_SMARTARRAY_FEATURES_SUPPORTED	0x2
#घोषणा SIS_PQI_MODE_SUPPORTED			0x4
#घोषणा SIS_PQI_RESET_QUIESCE_SUPPORTED		0x8
#घोषणा SIS_REQUIRED_EXTENDED_PROPERTIES	\
	(SIS_SMARTARRAY_FEATURES_SUPPORTED | SIS_PQI_MODE_SUPPORTED)

/* used with SIS_CMD_INIT_BASE_STRUCT_ADDRESS command */
#घोषणा SIS_BASE_STRUCT_REVISION		9
#घोषणा SIS_BASE_STRUCT_ALIGNMENT		16

#घोषणा SIS_CTRL_KERNEL_UP			0x80
#घोषणा SIS_CTRL_KERNEL_PANIC			0x100
#घोषणा SIS_CTRL_READY_TIMEOUT_SECS		180
#घोषणा SIS_CTRL_READY_RESUME_TIMEOUT_SECS	90
#घोषणा SIS_CTRL_READY_POLL_INTERVAL_MSECS	10

#आशय pack(1)

/* क्रम use with SIS_CMD_INIT_BASE_STRUCT_ADDRESS command */
काष्ठा sis_base_काष्ठा अणु
	__le32	revision;		/* revision of this काष्ठाure */
	__le32	flags;			/* reserved */
	__le32	error_buffer_paddr_low;	/* lower 32 bits of physical memory */
					/* buffer क्रम PQI error response */
					/* data */
	__le32	error_buffer_paddr_high;	/* upper 32 bits of physical */
						/* memory buffer क्रम PQI */
						/* error response data */
	__le32	error_buffer_element_length;	/* length of each PQI error */
						/* response buffer element */
						/* in bytes */
	__le32	error_buffer_num_elements;	/* total number of PQI error */
						/* response buffers available */
पूर्ण;

#आशय pack()

अटल पूर्णांक sis_रुको_क्रम_ctrl_पढ़ोy_with_समयout(काष्ठा pqi_ctrl_info *ctrl_info,
	अचिन्हित पूर्णांक समयout_secs)
अणु
	अचिन्हित दीर्घ समयout;
	u32 status;

	समयout = (समयout_secs * PQI_HZ) + jअगरfies;

	जबतक (1) अणु
		status = पढ़ोl(&ctrl_info->रेजिस्टरs->sis_firmware_status);
		अगर (status != ~0) अणु
			अगर (status & SIS_CTRL_KERNEL_PANIC) अणु
				dev_err(&ctrl_info->pci_dev->dev,
					"controller is offline: status code 0x%x\n",
					पढ़ोl(
					&ctrl_info->रेजिस्टरs->sis_mailbox[7]));
				वापस -ENODEV;
			पूर्ण
			अगर (status & SIS_CTRL_KERNEL_UP)
				अवरोध;
		पूर्ण
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_err(&ctrl_info->pci_dev->dev,
				"controller not ready after %u seconds\n",
				समयout_secs);
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(SIS_CTRL_READY_POLL_INTERVAL_MSECS);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक sis_रुको_क्रम_ctrl_पढ़ोy(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	वापस sis_रुको_क्रम_ctrl_पढ़ोy_with_समयout(ctrl_info,
		SIS_CTRL_READY_TIMEOUT_SECS);
पूर्ण

पूर्णांक sis_रुको_क्रम_ctrl_पढ़ोy_resume(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	वापस sis_रुको_क्रम_ctrl_पढ़ोy_with_समयout(ctrl_info,
		SIS_CTRL_READY_RESUME_TIMEOUT_SECS);
पूर्ण

bool sis_is_firmware_running(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	bool running;
	u32 status;

	status = पढ़ोl(&ctrl_info->रेजिस्टरs->sis_firmware_status);

	अगर (status & SIS_CTRL_KERNEL_PANIC)
		running = false;
	अन्यथा
		running = true;

	अगर (!running)
		dev_err(&ctrl_info->pci_dev->dev,
			"controller is offline: status code 0x%x\n",
			पढ़ोl(&ctrl_info->रेजिस्टरs->sis_mailbox[7]));

	वापस running;
पूर्ण

bool sis_is_kernel_up(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	वापस पढ़ोl(&ctrl_info->रेजिस्टरs->sis_firmware_status) &
		SIS_CTRL_KERNEL_UP;
पूर्ण

u32 sis_get_product_id(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	वापस पढ़ोl(&ctrl_info->रेजिस्टरs->sis_product_identअगरier);
पूर्ण

/* used क्रम passing command parameters/results when issuing SIS commands */
काष्ठा sis_sync_cmd_params अणु
	u32	mailbox[6];	/* mailboxes 0-5 */
पूर्ण;

अटल पूर्णांक sis_send_sync_cmd(काष्ठा pqi_ctrl_info *ctrl_info,
	u32 cmd, काष्ठा sis_sync_cmd_params *params)
अणु
	काष्ठा pqi_ctrl_रेजिस्टरs __iomem *रेजिस्टरs;
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ समयout;
	u32 करोorbell;
	u32 cmd_status;

	रेजिस्टरs = ctrl_info->रेजिस्टरs;

	/* Write the command to mailbox 0. */
	ग_लिखोl(cmd, &रेजिस्टरs->sis_mailbox[0]);

	/*
	 * Write the command parameters to mailboxes 1-4 (mailbox 5 is not used
	 * when sending a command to the controller).
	 */
	क्रम (i = 1; i <= 4; i++)
		ग_लिखोl(params->mailbox[i], &रेजिस्टरs->sis_mailbox[i]);

	/* Clear the command करोorbell. */
	ग_लिखोl(SIS_CLEAR_CTRL_TO_HOST_DOORBELL,
		&रेजिस्टरs->sis_ctrl_to_host_करोorbell_clear);

	/* Disable करोorbell पूर्णांकerrupts by masking all पूर्णांकerrupts. */
	ग_लिखोl(~0, &रेजिस्टरs->sis_पूर्णांकerrupt_mask);

	/*
	 * Force the completion of the पूर्णांकerrupt mask रेजिस्टर ग_लिखो beक्रमe
	 * submitting the command.
	 */
	पढ़ोl(&रेजिस्टरs->sis_पूर्णांकerrupt_mask);

	/* Submit the command to the controller. */
	ग_लिखोl(SIS_CMD_READY, &रेजिस्टरs->sis_host_to_ctrl_करोorbell);

	/*
	 * Poll क्रम command completion.  Note that the call to msleep() is at
	 * the top of the loop in order to give the controller समय to start
	 * processing the command beक्रमe we start polling.
	 */
	समयout = (SIS_CMD_COMPLETE_TIMEOUT_SECS * PQI_HZ) + jअगरfies;
	जबतक (1) अणु
		msleep(SIS_CMD_COMPLETE_POLL_INTERVAL_MSECS);
		करोorbell = पढ़ोl(&रेजिस्टरs->sis_ctrl_to_host_करोorbell);
		अगर (करोorbell & SIS_CMD_COMPLETE)
			अवरोध;
		अगर (समय_after(jअगरfies, समयout))
			वापस -ETIMEDOUT;
	पूर्ण

	/* Read the command status from mailbox 0. */
	cmd_status = पढ़ोl(&रेजिस्टरs->sis_mailbox[0]);
	अगर (cmd_status != SIS_CMD_STATUS_SUCCESS) अणु
		dev_err(&ctrl_info->pci_dev->dev,
			"SIS command failed for command 0x%x: status = 0x%x\n",
			cmd, cmd_status);
		वापस -EINVAL;
	पूर्ण

	/*
	 * The command completed successfully, so save the command status and
	 * पढ़ो the values वापसed in mailboxes 1-5.
	 */
	params->mailbox[0] = cmd_status;
	क्रम (i = 1; i < ARRAY_SIZE(params->mailbox); i++)
		params->mailbox[i] = पढ़ोl(&रेजिस्टरs->sis_mailbox[i]);

	वापस 0;
पूर्ण

/*
 * This function verअगरies that we are talking to a controller that speaks PQI.
 */

पूर्णांक sis_get_ctrl_properties(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक rc;
	u32 properties;
	u32 extended_properties;
	काष्ठा sis_sync_cmd_params params;

	स_रखो(&params, 0, माप(params));

	rc = sis_send_sync_cmd(ctrl_info, SIS_CMD_GET_ADAPTER_PROPERTIES,
		&params);
	अगर (rc)
		वापस rc;

	properties = params.mailbox[1];

	अगर (!(properties & SIS_EXTENDED_PROPERTIES_SUPPORTED))
		वापस -ENODEV;

	extended_properties = params.mailbox[4];

	अगर ((extended_properties & SIS_REQUIRED_EXTENDED_PROPERTIES) !=
		SIS_REQUIRED_EXTENDED_PROPERTIES)
		वापस -ENODEV;

	अगर (extended_properties & SIS_PQI_RESET_QUIESCE_SUPPORTED)
		ctrl_info->pqi_reset_quiesce_supported = true;

	वापस 0;
पूर्ण

पूर्णांक sis_get_pqi_capabilities(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक rc;
	काष्ठा sis_sync_cmd_params params;

	स_रखो(&params, 0, माप(params));

	rc = sis_send_sync_cmd(ctrl_info, SIS_CMD_GET_PQI_CAPABILITIES,
		&params);
	अगर (rc)
		वापस rc;

	ctrl_info->max_sg_entries = params.mailbox[1];
	ctrl_info->max_transfer_size = params.mailbox[2];
	ctrl_info->max_outstanding_requests = params.mailbox[3];
	ctrl_info->config_table_offset = params.mailbox[4];
	ctrl_info->config_table_length = params.mailbox[5];

	वापस 0;
पूर्ण

पूर्णांक sis_init_base_काष्ठा_addr(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	पूर्णांक rc;
	व्योम *base_काष्ठा_unaligned;
	काष्ठा sis_base_काष्ठा *base_काष्ठा;
	काष्ठा sis_sync_cmd_params params;
	अचिन्हित दीर्घ error_buffer_paddr;
	dma_addr_t bus_address;

	base_काष्ठा_unaligned = kzalloc(माप(*base_काष्ठा)
		+ SIS_BASE_STRUCT_ALIGNMENT - 1, GFP_KERNEL);
	अगर (!base_काष्ठा_unaligned)
		वापस -ENOMEM;

	base_काष्ठा = PTR_ALIGN(base_काष्ठा_unaligned,
		SIS_BASE_STRUCT_ALIGNMENT);
	error_buffer_paddr = (अचिन्हित दीर्घ)ctrl_info->error_buffer_dma_handle;

	put_unaligned_le32(SIS_BASE_STRUCT_REVISION, &base_काष्ठा->revision);
	put_unaligned_le32(lower_32_bits(error_buffer_paddr),
		&base_काष्ठा->error_buffer_paddr_low);
	put_unaligned_le32(upper_32_bits(error_buffer_paddr),
		&base_काष्ठा->error_buffer_paddr_high);
	put_unaligned_le32(PQI_ERROR_BUFFER_ELEMENT_LENGTH,
		&base_काष्ठा->error_buffer_element_length);
	put_unaligned_le32(ctrl_info->max_io_slots,
		&base_काष्ठा->error_buffer_num_elements);

	bus_address = dma_map_single(&ctrl_info->pci_dev->dev, base_काष्ठा,
		माप(*base_काष्ठा), DMA_TO_DEVICE);
	अगर (dma_mapping_error(&ctrl_info->pci_dev->dev, bus_address)) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	स_रखो(&params, 0, माप(params));
	params.mailbox[1] = lower_32_bits((u64)bus_address);
	params.mailbox[2] = upper_32_bits((u64)bus_address);
	params.mailbox[3] = माप(*base_काष्ठा);

	rc = sis_send_sync_cmd(ctrl_info, SIS_CMD_INIT_BASE_STRUCT_ADDRESS,
		&params);

	dma_unmap_single(&ctrl_info->pci_dev->dev, bus_address,
			माप(*base_काष्ठा), DMA_TO_DEVICE);
out:
	kमुक्त(base_काष्ठा_unaligned);

	वापस rc;
पूर्ण

#घोषणा SIS_DOORBELL_BIT_CLEAR_TIMEOUT_SECS	30

अटल पूर्णांक sis_रुको_क्रम_करोorbell_bit_to_clear(
	काष्ठा pqi_ctrl_info *ctrl_info, u32 bit)
अणु
	पूर्णांक rc = 0;
	u32 करोorbell_रेजिस्टर;
	अचिन्हित दीर्घ समयout;

	समयout = (SIS_DOORBELL_BIT_CLEAR_TIMEOUT_SECS * PQI_HZ) + jअगरfies;

	जबतक (1) अणु
		करोorbell_रेजिस्टर =
			पढ़ोl(&ctrl_info->रेजिस्टरs->sis_host_to_ctrl_करोorbell);
		अगर ((करोorbell_रेजिस्टर & bit) == 0)
			अवरोध;
		अगर (पढ़ोl(&ctrl_info->रेजिस्टरs->sis_firmware_status) &
			SIS_CTRL_KERNEL_PANIC) अणु
			rc = -ENODEV;
			अवरोध;
		पूर्ण
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_err(&ctrl_info->pci_dev->dev,
				"doorbell register bit 0x%x not cleared\n",
				bit);
			rc = -ETIMEDOUT;
			अवरोध;
		पूर्ण
		usleep_range(1000, 2000);
	पूर्ण

	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक sis_set_करोorbell_bit(काष्ठा pqi_ctrl_info *ctrl_info, u32 bit)
अणु
	ग_लिखोl(bit, &ctrl_info->रेजिस्टरs->sis_host_to_ctrl_करोorbell);

	वापस sis_रुको_क्रम_करोorbell_bit_to_clear(ctrl_info, bit);
पूर्ण

व्योम sis_enable_msix(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	sis_set_करोorbell_bit(ctrl_info, SIS_ENABLE_MSIX);
पूर्ण

व्योम sis_enable_पूर्णांकx(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	sis_set_करोorbell_bit(ctrl_info, SIS_ENABLE_INTX);
पूर्ण

व्योम sis_shutकरोwn_ctrl(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	अगर (पढ़ोl(&ctrl_info->रेजिस्टरs->sis_firmware_status) &
		SIS_CTRL_KERNEL_PANIC)
		वापस;

	ग_लिखोl(SIS_TRIGGER_SHUTDOWN,
		&ctrl_info->रेजिस्टरs->sis_host_to_ctrl_करोorbell);
पूर्ण

पूर्णांक sis_pqi_reset_quiesce(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	वापस sis_set_करोorbell_bit(ctrl_info, SIS_PQI_RESET_QUIESCE);
पूर्ण

पूर्णांक sis_reenable_sis_mode(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	वापस sis_set_करोorbell_bit(ctrl_info, SIS_REENABLE_SIS_MODE);
पूर्ण

व्योम sis_ग_लिखो_driver_scratch(काष्ठा pqi_ctrl_info *ctrl_info, u32 value)
अणु
	ग_लिखोl(value, &ctrl_info->रेजिस्टरs->sis_driver_scratch);
पूर्ण

u32 sis_पढ़ो_driver_scratch(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	वापस पढ़ोl(&ctrl_info->रेजिस्टरs->sis_driver_scratch);
पूर्ण

व्योम sis_soft_reset(काष्ठा pqi_ctrl_info *ctrl_info)
अणु
	ग_लिखोl(SIS_SOFT_RESET,
		&ctrl_info->रेजिस्टरs->sis_host_to_ctrl_करोorbell);
पूर्ण

अटल व्योम __attribute__((unused)) verअगरy_काष्ठाures(व्योम)
अणु
	BUILD_BUG_ON(दुरत्व(काष्ठा sis_base_काष्ठा,
		revision) != 0x0);
	BUILD_BUG_ON(दुरत्व(काष्ठा sis_base_काष्ठा,
		flags) != 0x4);
	BUILD_BUG_ON(दुरत्व(काष्ठा sis_base_काष्ठा,
		error_buffer_paddr_low) != 0x8);
	BUILD_BUG_ON(दुरत्व(काष्ठा sis_base_काष्ठा,
		error_buffer_paddr_high) != 0xc);
	BUILD_BUG_ON(दुरत्व(काष्ठा sis_base_काष्ठा,
		error_buffer_element_length) != 0x10);
	BUILD_BUG_ON(दुरत्व(काष्ठा sis_base_काष्ठा,
		error_buffer_num_elements) != 0x14);
	BUILD_BUG_ON(माप(काष्ठा sis_base_काष्ठा) != 0x18);
पूर्ण
