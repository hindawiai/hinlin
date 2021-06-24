<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Intel Corporation
 *
 * Authors:
 * Jarkko Sakkinen <jarkko.sakkinen@linux.पूर्णांकel.com>
 *
 * Maपूर्णांकained by: <tpmdd-devel@lists.sourceक्रमge.net>
 *
 * This device driver implements the TPM पूर्णांकerface as defined in
 * the TCG CRB 2.0 TPM specअगरication.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/rculist.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#अगर_घोषित CONFIG_ARM64
#समावेश <linux/arm-smccc.h>
#पूर्ण_अगर
#समावेश "tpm.h"

#घोषणा ACPI_SIG_TPM2 "TPM2"
#घोषणा TPM_CRB_MAX_RESOURCES 3

अटल स्थिर guid_t crb_acpi_start_guid =
	GUID_INIT(0x6BBF6CAB, 0x5463, 0x4714,
		  0xB7, 0xCD, 0xF0, 0x20, 0x3C, 0x03, 0x68, 0xD4);

क्रमागत crb_शेषs अणु
	CRB_ACPI_START_REVISION_ID = 1,
	CRB_ACPI_START_INDEX = 1,
पूर्ण;

क्रमागत crb_loc_ctrl अणु
	CRB_LOC_CTRL_REQUEST_ACCESS	= BIT(0),
	CRB_LOC_CTRL_RELINQUISH		= BIT(1),
पूर्ण;

क्रमागत crb_loc_state अणु
	CRB_LOC_STATE_LOC_ASSIGNED	= BIT(1),
	CRB_LOC_STATE_TPM_REG_VALID_STS	= BIT(7),
पूर्ण;

क्रमागत crb_ctrl_req अणु
	CRB_CTRL_REQ_CMD_READY	= BIT(0),
	CRB_CTRL_REQ_GO_IDLE	= BIT(1),
पूर्ण;

क्रमागत crb_ctrl_sts अणु
	CRB_CTRL_STS_ERROR	= BIT(0),
	CRB_CTRL_STS_TPM_IDLE	= BIT(1),
पूर्ण;

क्रमागत crb_start अणु
	CRB_START_INVOKE	= BIT(0),
पूर्ण;

क्रमागत crb_cancel अणु
	CRB_CANCEL_INVOKE	= BIT(0),
पूर्ण;

काष्ठा crb_regs_head अणु
	u32 loc_state;
	u32 reserved1;
	u32 loc_ctrl;
	u32 loc_sts;
	u8 reserved2[32];
	u64 पूर्णांकf_id;
	u64 ctrl_ext;
पूर्ण __packed;

काष्ठा crb_regs_tail अणु
	u32 ctrl_req;
	u32 ctrl_sts;
	u32 ctrl_cancel;
	u32 ctrl_start;
	u32 ctrl_पूर्णांक_enable;
	u32 ctrl_पूर्णांक_sts;
	u32 ctrl_cmd_size;
	u32 ctrl_cmd_pa_low;
	u32 ctrl_cmd_pa_high;
	u32 ctrl_rsp_size;
	u64 ctrl_rsp_pa;
पूर्ण __packed;

क्रमागत crb_status अणु
	CRB_DRV_STS_COMPLETE	= BIT(0),
पूर्ण;

काष्ठा crb_priv अणु
	u32 sm;
	स्थिर अक्षर *hid;
	काष्ठा crb_regs_head __iomem *regs_h;
	काष्ठा crb_regs_tail __iomem *regs_t;
	u8 __iomem *cmd;
	u8 __iomem *rsp;
	u32 cmd_size;
	u32 smc_func_id;
पूर्ण;

काष्ठा tpm2_crb_smc अणु
	u32 पूर्णांकerrupt;
	u8 पूर्णांकerrupt_flags;
	u8 op_flags;
	u16 reserved2;
	u32 smc_func_id;
पूर्ण;

अटल bool crb_रुको_क्रम_reg_32(u32 __iomem *reg, u32 mask, u32 value,
				अचिन्हित दीर्घ समयout)
अणु
	kसमय_प्रकार start;
	kसमय_प्रकार stop;

	start = kसमय_get();
	stop = kसमय_add(start, ms_to_kसमय(समयout));

	करो अणु
		अगर ((ioपढ़ो32(reg) & mask) == value)
			वापस true;

		usleep_range(50, 100);
	पूर्ण जबतक (kसमय_beक्रमe(kसमय_get(), stop));

	वापस ((ioपढ़ो32(reg) & mask) == value);
पूर्ण

/**
 * __crb_go_idle - request tpm crb device to go the idle state
 *
 * @dev:  crb device
 * @priv: crb निजी data
 *
 * Write CRB_CTRL_REQ_GO_IDLE to TPM_CRB_CTRL_REQ
 * The device should respond within TIMEOUT_C by clearing the bit.
 * Anyhow, we करो not रुको here as a consequent CMD_READY request
 * will be handled correctly even अगर idle was not completed.
 *
 * The function करोes nothing क्रम devices with ACPI-start method
 * or SMC-start method.
 *
 * Return: 0 always
 */
अटल पूर्णांक __crb_go_idle(काष्ठा device *dev, काष्ठा crb_priv *priv)
अणु
	अगर ((priv->sm == ACPI_TPM2_START_METHOD) ||
	    (priv->sm == ACPI_TPM2_COMMAND_BUFFER_WITH_START_METHOD) ||
	    (priv->sm == ACPI_TPM2_COMMAND_BUFFER_WITH_ARM_SMC))
		वापस 0;

	ioग_लिखो32(CRB_CTRL_REQ_GO_IDLE, &priv->regs_t->ctrl_req);

	अगर (!crb_रुको_क्रम_reg_32(&priv->regs_t->ctrl_req,
				 CRB_CTRL_REQ_GO_IDLE/* mask */,
				 0, /* value */
				 TPM2_TIMEOUT_C)) अणु
		dev_warn(dev, "goIdle timed out\n");
		वापस -ETIME;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक crb_go_idle(काष्ठा tpm_chip *chip)
अणु
	काष्ठा device *dev = &chip->dev;
	काष्ठा crb_priv *priv = dev_get_drvdata(dev);

	वापस __crb_go_idle(dev, priv);
पूर्ण

/**
 * __crb_cmd_पढ़ोy - request tpm crb device to enter पढ़ोy state
 *
 * @dev:  crb device
 * @priv: crb निजी data
 *
 * Write CRB_CTRL_REQ_CMD_READY to TPM_CRB_CTRL_REQ
 * and poll till the device acknowledge it by clearing the bit.
 * The device should respond within TIMEOUT_C.
 *
 * The function करोes nothing क्रम devices with ACPI-start method
 * or SMC-start method.
 *
 * Return: 0 on success -ETIME on समयout;
 */
अटल पूर्णांक __crb_cmd_पढ़ोy(काष्ठा device *dev, काष्ठा crb_priv *priv)
अणु
	अगर ((priv->sm == ACPI_TPM2_START_METHOD) ||
	    (priv->sm == ACPI_TPM2_COMMAND_BUFFER_WITH_START_METHOD) ||
	    (priv->sm == ACPI_TPM2_COMMAND_BUFFER_WITH_ARM_SMC))
		वापस 0;

	ioग_लिखो32(CRB_CTRL_REQ_CMD_READY, &priv->regs_t->ctrl_req);
	अगर (!crb_रुको_क्रम_reg_32(&priv->regs_t->ctrl_req,
				 CRB_CTRL_REQ_CMD_READY /* mask */,
				 0, /* value */
				 TPM2_TIMEOUT_C)) अणु
		dev_warn(dev, "cmdReady timed out\n");
		वापस -ETIME;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक crb_cmd_पढ़ोy(काष्ठा tpm_chip *chip)
अणु
	काष्ठा device *dev = &chip->dev;
	काष्ठा crb_priv *priv = dev_get_drvdata(dev);

	वापस __crb_cmd_पढ़ोy(dev, priv);
पूर्ण

अटल पूर्णांक __crb_request_locality(काष्ठा device *dev,
				  काष्ठा crb_priv *priv, पूर्णांक loc)
अणु
	u32 value = CRB_LOC_STATE_LOC_ASSIGNED |
		    CRB_LOC_STATE_TPM_REG_VALID_STS;

	अगर (!priv->regs_h)
		वापस 0;

	ioग_लिखो32(CRB_LOC_CTRL_REQUEST_ACCESS, &priv->regs_h->loc_ctrl);
	अगर (!crb_रुको_क्रम_reg_32(&priv->regs_h->loc_state, value, value,
				 TPM2_TIMEOUT_C)) अणु
		dev_warn(dev, "TPM_LOC_STATE_x.requestAccess timed out\n");
		वापस -ETIME;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक crb_request_locality(काष्ठा tpm_chip *chip, पूर्णांक loc)
अणु
	काष्ठा crb_priv *priv = dev_get_drvdata(&chip->dev);

	वापस __crb_request_locality(&chip->dev, priv, loc);
पूर्ण

अटल पूर्णांक __crb_relinquish_locality(काष्ठा device *dev,
				     काष्ठा crb_priv *priv, पूर्णांक loc)
अणु
	u32 mask = CRB_LOC_STATE_LOC_ASSIGNED |
		   CRB_LOC_STATE_TPM_REG_VALID_STS;
	u32 value = CRB_LOC_STATE_TPM_REG_VALID_STS;

	अगर (!priv->regs_h)
		वापस 0;

	ioग_लिखो32(CRB_LOC_CTRL_RELINQUISH, &priv->regs_h->loc_ctrl);
	अगर (!crb_रुको_क्रम_reg_32(&priv->regs_h->loc_state, mask, value,
				 TPM2_TIMEOUT_C)) अणु
		dev_warn(dev, "TPM_LOC_STATE_x.requestAccess timed out\n");
		वापस -ETIME;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक crb_relinquish_locality(काष्ठा tpm_chip *chip, पूर्णांक loc)
अणु
	काष्ठा crb_priv *priv = dev_get_drvdata(&chip->dev);

	वापस __crb_relinquish_locality(&chip->dev, priv, loc);
पूर्ण

अटल u8 crb_status(काष्ठा tpm_chip *chip)
अणु
	काष्ठा crb_priv *priv = dev_get_drvdata(&chip->dev);
	u8 sts = 0;

	अगर ((ioपढ़ो32(&priv->regs_t->ctrl_start) & CRB_START_INVOKE) !=
	    CRB_START_INVOKE)
		sts |= CRB_DRV_STS_COMPLETE;

	वापस sts;
पूर्ण

अटल पूर्णांक crb_recv(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार count)
अणु
	काष्ठा crb_priv *priv = dev_get_drvdata(&chip->dev);
	अचिन्हित पूर्णांक expected;

	/* A sanity check that the upper layer wants to get at least the header
	 * as that is the minimum size क्रम any TPM response.
	 */
	अगर (count < TPM_HEADER_SIZE)
		वापस -EIO;

	/* If this bit is set, according to the spec, the TPM is in
	 * unrecoverable condition.
	 */
	अगर (ioपढ़ो32(&priv->regs_t->ctrl_sts) & CRB_CTRL_STS_ERROR)
		वापस -EIO;

	/* Read the first 8 bytes in order to get the length of the response.
	 * We पढ़ो exactly a quad word in order to make sure that the reमुख्यing
	 * पढ़ोs will be aligned.
	 */
	स_नकल_fromio(buf, priv->rsp, 8);

	expected = be32_to_cpup((__be32 *)&buf[2]);
	अगर (expected > count || expected < TPM_HEADER_SIZE)
		वापस -EIO;

	स_नकल_fromio(&buf[8], &priv->rsp[8], expected - 8);

	वापस expected;
पूर्ण

अटल पूर्णांक crb_करो_acpi_start(काष्ठा tpm_chip *chip)
अणु
	जोड़ acpi_object *obj;
	पूर्णांक rc;

	obj = acpi_evaluate_dsm(chip->acpi_dev_handle,
				&crb_acpi_start_guid,
				CRB_ACPI_START_REVISION_ID,
				CRB_ACPI_START_INDEX,
				शून्य);
	अगर (!obj)
		वापस -ENXIO;
	rc = obj->पूर्णांकeger.value == 0 ? 0 : -ENXIO;
	ACPI_FREE(obj);
	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_ARM64
/*
 * This is a TPM Command Response Buffer start method that invokes a
 * Secure Monitor Call to requrest the firmware to execute or cancel
 * a TPM 2.0 command.
 */
अटल पूर्णांक tpm_crb_smc_start(काष्ठा device *dev, अचिन्हित दीर्घ func_id)
अणु
	काष्ठा arm_smccc_res res;

	arm_smccc_smc(func_id, 0, 0, 0, 0, 0, 0, 0, &res);
	अगर (res.a0 != 0) अणु
		dev_err(dev,
			FW_BUG "tpm_crb_smc_start() returns res.a0 = 0x%lx\n",
			res.a0);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक tpm_crb_smc_start(काष्ठा device *dev, अचिन्हित दीर्घ func_id)
अणु
	dev_err(dev, FW_BUG "tpm_crb: incorrect start method\n");
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक crb_send(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार len)
अणु
	काष्ठा crb_priv *priv = dev_get_drvdata(&chip->dev);
	पूर्णांक rc = 0;

	/* Zero the cancel रेजिस्टर so that the next command will not get
	 * canceled.
	 */
	ioग_लिखो32(0, &priv->regs_t->ctrl_cancel);

	अगर (len > priv->cmd_size) अणु
		dev_err(&chip->dev, "invalid command count value %zd %d\n",
			len, priv->cmd_size);
		वापस -E2BIG;
	पूर्ण

	स_नकल_toio(priv->cmd, buf, len);

	/* Make sure that cmd is populated beक्रमe issuing start. */
	wmb();

	/* The reason क्रम the extra quirk is that the PTT in 4th Gen Core CPUs
	 * report only ACPI start but in practice seems to require both
	 * CRB start, hence invoking CRB start method अगर hid == MSFT0101.
	 */
	अगर ((priv->sm == ACPI_TPM2_COMMAND_BUFFER) ||
	    (priv->sm == ACPI_TPM2_MEMORY_MAPPED) ||
	    (!म_भेद(priv->hid, "MSFT0101")))
		ioग_लिखो32(CRB_START_INVOKE, &priv->regs_t->ctrl_start);

	अगर ((priv->sm == ACPI_TPM2_START_METHOD) ||
	    (priv->sm == ACPI_TPM2_COMMAND_BUFFER_WITH_START_METHOD))
		rc = crb_करो_acpi_start(chip);

	अगर (priv->sm == ACPI_TPM2_COMMAND_BUFFER_WITH_ARM_SMC) अणु
		ioग_लिखो32(CRB_START_INVOKE, &priv->regs_t->ctrl_start);
		rc = tpm_crb_smc_start(&chip->dev, priv->smc_func_id);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम crb_cancel(काष्ठा tpm_chip *chip)
अणु
	काष्ठा crb_priv *priv = dev_get_drvdata(&chip->dev);

	ioग_लिखो32(CRB_CANCEL_INVOKE, &priv->regs_t->ctrl_cancel);

	अगर (((priv->sm == ACPI_TPM2_START_METHOD) ||
	    (priv->sm == ACPI_TPM2_COMMAND_BUFFER_WITH_START_METHOD)) &&
	     crb_करो_acpi_start(chip))
		dev_err(&chip->dev, "ACPI Start failed\n");
पूर्ण

अटल bool crb_req_canceled(काष्ठा tpm_chip *chip, u8 status)
अणु
	काष्ठा crb_priv *priv = dev_get_drvdata(&chip->dev);
	u32 cancel = ioपढ़ो32(&priv->regs_t->ctrl_cancel);

	वापस (cancel & CRB_CANCEL_INVOKE) == CRB_CANCEL_INVOKE;
पूर्ण

अटल स्थिर काष्ठा tpm_class_ops tpm_crb = अणु
	.flags = TPM_OPS_AUTO_STARTUP,
	.status = crb_status,
	.recv = crb_recv,
	.send = crb_send,
	.cancel = crb_cancel,
	.req_canceled = crb_req_canceled,
	.go_idle  = crb_go_idle,
	.cmd_पढ़ोy = crb_cmd_पढ़ोy,
	.request_locality = crb_request_locality,
	.relinquish_locality = crb_relinquish_locality,
	.req_complete_mask = CRB_DRV_STS_COMPLETE,
	.req_complete_val = CRB_DRV_STS_COMPLETE,
पूर्ण;

अटल पूर्णांक crb_check_resource(काष्ठा acpi_resource *ares, व्योम *data)
अणु
	काष्ठा resource *iores_array = data;
	काष्ठा resource_win win;
	काष्ठा resource *res = &(win.res);
	पूर्णांक i;

	अगर (acpi_dev_resource_memory(ares, res) ||
	    acpi_dev_resource_address_space(ares, &win)) अणु
		क्रम (i = 0; i < TPM_CRB_MAX_RESOURCES + 1; ++i) अणु
			अगर (resource_type(iores_array + i) != IORESOURCE_MEM) अणु
				iores_array[i] = *res;
				iores_array[i].name = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम __iomem *crb_map_res(काष्ठा device *dev, काष्ठा resource *iores,
				 व्योम __iomem **iobase_ptr, u64 start, u32 size)
अणु
	काष्ठा resource new_res = अणु
		.start	= start,
		.end	= start + size - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण;

	/* Detect a 64 bit address on a 32 bit प्रणाली */
	अगर (start != new_res.start)
		वापस (व्योम __iomem *) ERR_PTR(-EINVAL);

	अगर (!iores)
		वापस devm_ioremap_resource(dev, &new_res);

	अगर (!*iobase_ptr) अणु
		*iobase_ptr = devm_ioremap_resource(dev, iores);
		अगर (IS_ERR(*iobase_ptr))
			वापस *iobase_ptr;
	पूर्ण

	वापस *iobase_ptr + (new_res.start - iores->start);
पूर्ण

/*
 * Work around broken BIOSs that वापस inconsistent values from the ACPI
 * region vs the रेजिस्टरs. Trust the ACPI region. Such broken प्रणालीs
 * probably cannot send large TPM commands since the buffer will be truncated.
 */
अटल u64 crb_fixup_cmd_size(काष्ठा device *dev, काष्ठा resource *io_res,
			      u64 start, u64 size)
अणु
	अगर (io_res->start > start || io_res->end < start)
		वापस size;

	अगर (start + size - 1 <= io_res->end)
		वापस size;

	dev_err(dev,
		FW_BUG "ACPI region does not cover the entire command/response buffer. %pr vs %llx %llx\n",
		io_res, start, size);

	वापस io_res->end - start + 1;
पूर्ण

अटल पूर्णांक crb_map_io(काष्ठा acpi_device *device, काष्ठा crb_priv *priv,
		      काष्ठा acpi_table_tpm2 *buf)
अणु
	काष्ठा list_head acpi_resource_list;
	काष्ठा resource iores_array[TPM_CRB_MAX_RESOURCES + 1] = अणु अणु0पूर्ण पूर्ण;
	व्योम __iomem *iobase_array[TPM_CRB_MAX_RESOURCES] = अणुशून्यपूर्ण;
	काष्ठा device *dev = &device->dev;
	काष्ठा resource *iores;
	व्योम __iomem **iobase_ptr;
	पूर्णांक i;
	u32 pa_high, pa_low;
	u64 cmd_pa;
	u32 cmd_size;
	__le64 __rsp_pa;
	u64 rsp_pa;
	u32 rsp_size;
	पूर्णांक ret;

	INIT_LIST_HEAD(&acpi_resource_list);
	ret = acpi_dev_get_resources(device, &acpi_resource_list,
				     crb_check_resource, iores_array);
	अगर (ret < 0)
		वापस ret;
	acpi_dev_मुक्त_resource_list(&acpi_resource_list);

	अगर (resource_type(iores_array) != IORESOURCE_MEM) अणु
		dev_err(dev, FW_BUG "TPM2 ACPI table does not define a memory resource\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (resource_type(iores_array + TPM_CRB_MAX_RESOURCES) ==
		IORESOURCE_MEM) अणु
		dev_warn(dev, "TPM2 ACPI table defines too many memory resources\n");
		स_रखो(iores_array + TPM_CRB_MAX_RESOURCES,
		       0, माप(*iores_array));
		iores_array[TPM_CRB_MAX_RESOURCES].flags = 0;
	पूर्ण

	iores = शून्य;
	iobase_ptr = शून्य;
	क्रम (i = 0; resource_type(iores_array + i) == IORESOURCE_MEM; ++i) अणु
		अगर (buf->control_address >= iores_array[i].start &&
		    buf->control_address + माप(काष्ठा crb_regs_tail) - 1 <=
		    iores_array[i].end) अणु
			iores = iores_array + i;
			iobase_ptr = iobase_array + i;
			अवरोध;
		पूर्ण
	पूर्ण

	priv->regs_t = crb_map_res(dev, iores, iobase_ptr, buf->control_address,
				   माप(काष्ठा crb_regs_tail));

	अगर (IS_ERR(priv->regs_t))
		वापस PTR_ERR(priv->regs_t);

	/* The ACPI IO region starts at the head area and जारीs to include
	 * the control area, as one nice sane region except क्रम some older
	 * stuff that माला_दो the control area outside the ACPI IO region.
	 */
	अगर ((priv->sm == ACPI_TPM2_COMMAND_BUFFER) ||
	    (priv->sm == ACPI_TPM2_MEMORY_MAPPED)) अणु
		अगर (iores &&
		    buf->control_address == iores->start +
		    माप(*priv->regs_h))
			priv->regs_h = *iobase_ptr;
		अन्यथा
			dev_warn(dev, FW_BUG "Bad ACPI memory layout");
	पूर्ण

	ret = __crb_request_locality(dev, priv, 0);
	अगर (ret)
		वापस ret;

	/*
	 * PTT HW bug w/a: wake up the device to access
	 * possibly not retained रेजिस्टरs.
	 */
	ret = __crb_cmd_पढ़ोy(dev, priv);
	अगर (ret)
		जाओ out_relinquish_locality;

	pa_high = ioपढ़ो32(&priv->regs_t->ctrl_cmd_pa_high);
	pa_low  = ioपढ़ो32(&priv->regs_t->ctrl_cmd_pa_low);
	cmd_pa = ((u64)pa_high << 32) | pa_low;
	cmd_size = ioपढ़ो32(&priv->regs_t->ctrl_cmd_size);

	iores = शून्य;
	iobase_ptr = शून्य;
	क्रम (i = 0; iores_array[i].end; ++i) अणु
		अगर (cmd_pa >= iores_array[i].start &&
		    cmd_pa <= iores_array[i].end) अणु
			iores = iores_array + i;
			iobase_ptr = iobase_array + i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (iores)
		cmd_size = crb_fixup_cmd_size(dev, iores, cmd_pa, cmd_size);

	dev_dbg(dev, "cmd_hi = %X cmd_low = %X cmd_size %X\n",
		pa_high, pa_low, cmd_size);

	priv->cmd = crb_map_res(dev, iores, iobase_ptr,	cmd_pa, cmd_size);
	अगर (IS_ERR(priv->cmd)) अणु
		ret = PTR_ERR(priv->cmd);
		जाओ out;
	पूर्ण

	स_नकल_fromio(&__rsp_pa, &priv->regs_t->ctrl_rsp_pa, 8);
	rsp_pa = le64_to_cpu(__rsp_pa);
	rsp_size = ioपढ़ो32(&priv->regs_t->ctrl_rsp_size);

	iores = शून्य;
	iobase_ptr = शून्य;
	क्रम (i = 0; resource_type(iores_array + i) == IORESOURCE_MEM; ++i) अणु
		अगर (rsp_pa >= iores_array[i].start &&
		    rsp_pa <= iores_array[i].end) अणु
			iores = iores_array + i;
			iobase_ptr = iobase_array + i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (iores)
		rsp_size = crb_fixup_cmd_size(dev, iores, rsp_pa, rsp_size);

	अगर (cmd_pa != rsp_pa) अणु
		priv->rsp = crb_map_res(dev, iores, iobase_ptr,
					rsp_pa, rsp_size);
		ret = PTR_ERR_OR_ZERO(priv->rsp);
		जाओ out;
	पूर्ण

	/* According to the PTP specअगरication, overlapping command and response
	 * buffer sizes must be identical.
	 */
	अगर (cmd_size != rsp_size) अणु
		dev_err(dev, FW_BUG "overlapping command and response buffer sizes are not identical");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	priv->rsp = priv->cmd;

out:
	अगर (!ret)
		priv->cmd_size = cmd_size;

	__crb_go_idle(dev, priv);

out_relinquish_locality:

	__crb_relinquish_locality(dev, priv, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक crb_acpi_add(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_table_tpm2 *buf;
	काष्ठा crb_priv *priv;
	काष्ठा tpm_chip *chip;
	काष्ठा device *dev = &device->dev;
	काष्ठा tpm2_crb_smc *crb_smc;
	acpi_status status;
	u32 sm;
	पूर्णांक rc;

	status = acpi_get_table(ACPI_SIG_TPM2, 1,
				(काष्ठा acpi_table_header **) &buf);
	अगर (ACPI_FAILURE(status) || buf->header.length < माप(*buf)) अणु
		dev_err(dev, FW_BUG "failed to get TPM2 ACPI table\n");
		वापस -EINVAL;
	पूर्ण

	/* Should the FIFO driver handle this? */
	sm = buf->start_method;
	अगर (sm == ACPI_TPM2_MEMORY_MAPPED)
		वापस -ENODEV;

	priv = devm_kzalloc(dev, माप(काष्ठा crb_priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	अगर (sm == ACPI_TPM2_COMMAND_BUFFER_WITH_ARM_SMC) अणु
		अगर (buf->header.length < (माप(*buf) + माप(*crb_smc))) अणु
			dev_err(dev,
				FW_BUG "TPM2 ACPI table has wrong size %u for start method type %d\n",
				buf->header.length,
				ACPI_TPM2_COMMAND_BUFFER_WITH_ARM_SMC);
			वापस -EINVAL;
		पूर्ण
		crb_smc = ACPI_ADD_PTR(काष्ठा tpm2_crb_smc, buf, माप(*buf));
		priv->smc_func_id = crb_smc->smc_func_id;
	पूर्ण

	priv->sm = sm;
	priv->hid = acpi_device_hid(device);

	rc = crb_map_io(device, priv, buf);
	अगर (rc)
		वापस rc;

	chip = tpmm_chip_alloc(dev, &tpm_crb);
	अगर (IS_ERR(chip))
		वापस PTR_ERR(chip);

	dev_set_drvdata(&chip->dev, priv);
	chip->acpi_dev_handle = device->handle;
	chip->flags = TPM_CHIP_FLAG_TPM2;

	वापस tpm_chip_रेजिस्टर(chip);
पूर्ण

अटल पूर्णांक crb_acpi_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा device *dev = &device->dev;
	काष्ठा tpm_chip *chip = dev_get_drvdata(dev);

	tpm_chip_unरेजिस्टर(chip);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops crb_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(tpm_pm_suspend, tpm_pm_resume)
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id crb_device_ids[] = अणु
	अणु"MSFT0101", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, crb_device_ids);

अटल काष्ठा acpi_driver crb_acpi_driver = अणु
	.name = "tpm_crb",
	.ids = crb_device_ids,
	.ops = अणु
		.add = crb_acpi_add,
		.हटाओ = crb_acpi_हटाओ,
	पूर्ण,
	.drv = अणु
		.pm = &crb_pm,
	पूर्ण,
पूर्ण;

module_acpi_driver(crb_acpi_driver);
MODULE_AUTHOR("Jarkko Sakkinen <jarkko.sakkinen@linux.intel.com>");
MODULE_DESCRIPTION("TPM2 Driver");
MODULE_VERSION("0.1");
MODULE_LICENSE("GPL");
