<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD Secure Encrypted Virtualization (SEV) पूर्णांकerface
 *
 * Copyright (C) 2016,2019 Advanced Micro Devices, Inc.
 *
 * Author: Brijesh Singh <brijesh.singh@amd.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/spinlock_types.h>
#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/ccp.h>
#समावेश <linux/firmware.h>
#समावेश <linux/gfp.h>
#समावेश <linux/cpufeature.h>

#समावेश <यंत्र/smp.h>

#समावेश "psp-dev.h"
#समावेश "sev-dev.h"

#घोषणा DEVICE_NAME		"sev"
#घोषणा SEV_FW_खाता		"amd/sev.fw"
#घोषणा SEV_FW_NAME_SIZE	64

अटल DEFINE_MUTEX(sev_cmd_mutex);
अटल काष्ठा sev_misc_dev *misc_dev;

अटल पूर्णांक psp_cmd_समयout = 100;
module_param(psp_cmd_समयout, पूर्णांक, 0644);
MODULE_PARM_DESC(psp_cmd_समयout, " default timeout value, in seconds, for PSP commands");

अटल पूर्णांक psp_probe_समयout = 5;
module_param(psp_probe_समयout, पूर्णांक, 0644);
MODULE_PARM_DESC(psp_probe_समयout, " default timeout value, in seconds, during PSP device probe");

अटल bool psp_dead;
अटल पूर्णांक psp_समयout;

/* Trusted Memory Region (TMR):
 *   The TMR is a 1MB area that must be 1MB aligned.  Use the page allocator
 *   to allocate the memory, which will वापस aligned memory क्रम the specअगरied
 *   allocation order.
 */
#घोषणा SEV_ES_TMR_SIZE		(1024 * 1024)
अटल व्योम *sev_es_पंचांगr;

अटल अंतरभूत bool sev_version_greater_or_equal(u8 maj, u8 min)
अणु
	काष्ठा sev_device *sev = psp_master->sev_data;

	अगर (sev->api_major > maj)
		वापस true;

	अगर (sev->api_major == maj && sev->api_minor >= min)
		वापस true;

	वापस false;
पूर्ण

अटल व्योम sev_irq_handler(पूर्णांक irq, व्योम *data, अचिन्हित पूर्णांक status)
अणु
	काष्ठा sev_device *sev = data;
	पूर्णांक reg;

	/* Check अगर it is command completion: */
	अगर (!(status & SEV_CMD_COMPLETE))
		वापस;

	/* Check अगर it is SEV command completion: */
	reg = ioपढ़ो32(sev->io_regs + sev->vdata->cmdresp_reg);
	अगर (reg & PSP_CMDRESP_RESP) अणु
		sev->पूर्णांक_rcvd = 1;
		wake_up(&sev->पूर्णांक_queue);
	पूर्ण
पूर्ण

अटल पूर्णांक sev_रुको_cmd_ioc(काष्ठा sev_device *sev,
			    अचिन्हित पूर्णांक *reg, अचिन्हित पूर्णांक समयout)
अणु
	पूर्णांक ret;

	ret = रुको_event_समयout(sev->पूर्णांक_queue,
			sev->पूर्णांक_rcvd, समयout * HZ);
	अगर (!ret)
		वापस -ETIMEDOUT;

	*reg = ioपढ़ो32(sev->io_regs + sev->vdata->cmdresp_reg);

	वापस 0;
पूर्ण

अटल पूर्णांक sev_cmd_buffer_len(पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल SEV_CMD_INIT:			वापस माप(काष्ठा sev_data_init);
	हाल SEV_CMD_PLATFORM_STATUS:		वापस माप(काष्ठा sev_user_data_status);
	हाल SEV_CMD_PEK_CSR:			वापस माप(काष्ठा sev_data_pek_csr);
	हाल SEV_CMD_PEK_CERT_IMPORT:		वापस माप(काष्ठा sev_data_pek_cert_import);
	हाल SEV_CMD_PDH_CERT_EXPORT:		वापस माप(काष्ठा sev_data_pdh_cert_export);
	हाल SEV_CMD_LAUNCH_START:		वापस माप(काष्ठा sev_data_launch_start);
	हाल SEV_CMD_LAUNCH_UPDATE_DATA:	वापस माप(काष्ठा sev_data_launch_update_data);
	हाल SEV_CMD_LAUNCH_UPDATE_VMSA:	वापस माप(काष्ठा sev_data_launch_update_vmsa);
	हाल SEV_CMD_LAUNCH_FINISH:		वापस माप(काष्ठा sev_data_launch_finish);
	हाल SEV_CMD_LAUNCH_MEASURE:		वापस माप(काष्ठा sev_data_launch_measure);
	हाल SEV_CMD_ACTIVATE:			वापस माप(काष्ठा sev_data_activate);
	हाल SEV_CMD_DEACTIVATE:		वापस माप(काष्ठा sev_data_deactivate);
	हाल SEV_CMD_DECOMMISSION:		वापस माप(काष्ठा sev_data_decommission);
	हाल SEV_CMD_GUEST_STATUS:		वापस माप(काष्ठा sev_data_guest_status);
	हाल SEV_CMD_DBG_DECRYPT:		वापस माप(काष्ठा sev_data_dbg);
	हाल SEV_CMD_DBG_ENCRYPT:		वापस माप(काष्ठा sev_data_dbg);
	हाल SEV_CMD_SEND_START:		वापस माप(काष्ठा sev_data_send_start);
	हाल SEV_CMD_SEND_UPDATE_DATA:		वापस माप(काष्ठा sev_data_send_update_data);
	हाल SEV_CMD_SEND_UPDATE_VMSA:		वापस माप(काष्ठा sev_data_send_update_vmsa);
	हाल SEV_CMD_SEND_FINISH:		वापस माप(काष्ठा sev_data_send_finish);
	हाल SEV_CMD_RECEIVE_START:		वापस माप(काष्ठा sev_data_receive_start);
	हाल SEV_CMD_RECEIVE_FINISH:		वापस माप(काष्ठा sev_data_receive_finish);
	हाल SEV_CMD_RECEIVE_UPDATE_DATA:	वापस माप(काष्ठा sev_data_receive_update_data);
	हाल SEV_CMD_RECEIVE_UPDATE_VMSA:	वापस माप(काष्ठा sev_data_receive_update_vmsa);
	हाल SEV_CMD_LAUNCH_UPDATE_SECRET:	वापस माप(काष्ठा sev_data_launch_secret);
	हाल SEV_CMD_DOWNLOAD_FIRMWARE:		वापस माप(काष्ठा sev_data_करोwnload_firmware);
	हाल SEV_CMD_GET_ID:			वापस माप(काष्ठा sev_data_get_id);
	हाल SEV_CMD_ATTESTATION_REPORT:	वापस माप(काष्ठा sev_data_attestation_report);
	हाल SEV_CMD_SEND_CANCEL:			वापस माप(काष्ठा sev_data_send_cancel);
	शेष:				वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __sev_करो_cmd_locked(पूर्णांक cmd, व्योम *data, पूर्णांक *psp_ret)
अणु
	काष्ठा psp_device *psp = psp_master;
	काष्ठा sev_device *sev;
	अचिन्हित पूर्णांक phys_lsb, phys_msb;
	अचिन्हित पूर्णांक reg, ret = 0;
	पूर्णांक buf_len;

	अगर (!psp || !psp->sev_data)
		वापस -ENODEV;

	अगर (psp_dead)
		वापस -EBUSY;

	sev = psp->sev_data;

	buf_len = sev_cmd_buffer_len(cmd);
	अगर (WARN_ON_ONCE(!data != !buf_len))
		वापस -EINVAL;

	/*
	 * Copy the incoming data to driver's scratch buffer as __pa() will not
	 * work क्रम some memory, e.g. vदो_स्मृति'd addresses, and @data may not be
	 * physically contiguous.
	 */
	अगर (data)
		स_नकल(sev->cmd_buf, data, buf_len);

	/* Get the physical address of the command buffer */
	phys_lsb = data ? lower_32_bits(__psp_pa(sev->cmd_buf)) : 0;
	phys_msb = data ? upper_32_bits(__psp_pa(sev->cmd_buf)) : 0;

	dev_dbg(sev->dev, "sev command id %#x buffer 0x%08x%08x timeout %us\n",
		cmd, phys_msb, phys_lsb, psp_समयout);

	prपूर्णांक_hex_dump_debug("(in):  ", DUMP_PREFIX_OFFSET, 16, 2, data,
			     buf_len, false);

	ioग_लिखो32(phys_lsb, sev->io_regs + sev->vdata->cmdbuff_addr_lo_reg);
	ioग_लिखो32(phys_msb, sev->io_regs + sev->vdata->cmdbuff_addr_hi_reg);

	sev->पूर्णांक_rcvd = 0;

	reg = cmd;
	reg <<= SEV_CMDRESP_CMD_SHIFT;
	reg |= SEV_CMDRESP_IOC;
	ioग_लिखो32(reg, sev->io_regs + sev->vdata->cmdresp_reg);

	/* रुको क्रम command completion */
	ret = sev_रुको_cmd_ioc(sev, &reg, psp_समयout);
	अगर (ret) अणु
		अगर (psp_ret)
			*psp_ret = 0;

		dev_err(sev->dev, "sev command %#x timed out, disabling PSP\n", cmd);
		psp_dead = true;

		वापस ret;
	पूर्ण

	psp_समयout = psp_cmd_समयout;

	अगर (psp_ret)
		*psp_ret = reg & PSP_CMDRESP_ERR_MASK;

	अगर (reg & PSP_CMDRESP_ERR_MASK) अणु
		dev_dbg(sev->dev, "sev command %#x failed (%#010x)\n",
			cmd, reg & PSP_CMDRESP_ERR_MASK);
		ret = -EIO;
	पूर्ण

	prपूर्णांक_hex_dump_debug("(out): ", DUMP_PREFIX_OFFSET, 16, 2, data,
			     buf_len, false);

	/*
	 * Copy potential output from the PSP back to data.  Do this even on
	 * failure in हाल the caller wants to glean something from the error.
	 */
	अगर (data)
		स_नकल(data, sev->cmd_buf, buf_len);

	वापस ret;
पूर्ण

अटल पूर्णांक sev_करो_cmd(पूर्णांक cmd, व्योम *data, पूर्णांक *psp_ret)
अणु
	पूर्णांक rc;

	mutex_lock(&sev_cmd_mutex);
	rc = __sev_करो_cmd_locked(cmd, data, psp_ret);
	mutex_unlock(&sev_cmd_mutex);

	वापस rc;
पूर्ण

अटल पूर्णांक __sev_platक्रमm_init_locked(पूर्णांक *error)
अणु
	काष्ठा psp_device *psp = psp_master;
	काष्ठा sev_data_init data;
	काष्ठा sev_device *sev;
	पूर्णांक rc = 0;

	अगर (!psp || !psp->sev_data)
		वापस -ENODEV;

	sev = psp->sev_data;

	अगर (sev->state == SEV_STATE_INIT)
		वापस 0;

	स_रखो(&data, 0, माप(data));
	अगर (sev_es_पंचांगr) अणु
		u64 पंचांगr_pa;

		/*
		 * Do not include the encryption mask on the physical
		 * address of the TMR (firmware should clear it anyway).
		 */
		पंचांगr_pa = __pa(sev_es_पंचांगr);

		data.flags |= SEV_INIT_FLAGS_SEV_ES;
		data.पंचांगr_address = पंचांगr_pa;
		data.पंचांगr_len = SEV_ES_TMR_SIZE;
	पूर्ण

	rc = __sev_करो_cmd_locked(SEV_CMD_INIT, &data, error);
	अगर (rc)
		वापस rc;

	sev->state = SEV_STATE_INIT;

	/* Prepare क्रम first SEV guest launch after INIT */
	wbinvd_on_all_cpus();
	rc = __sev_करो_cmd_locked(SEV_CMD_DF_FLUSH, शून्य, error);
	अगर (rc)
		वापस rc;

	dev_dbg(sev->dev, "SEV firmware initialized\n");

	वापस rc;
पूर्ण

पूर्णांक sev_platक्रमm_init(पूर्णांक *error)
अणु
	पूर्णांक rc;

	mutex_lock(&sev_cmd_mutex);
	rc = __sev_platक्रमm_init_locked(error);
	mutex_unlock(&sev_cmd_mutex);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(sev_platक्रमm_init);

अटल पूर्णांक __sev_platक्रमm_shutकरोwn_locked(पूर्णांक *error)
अणु
	काष्ठा sev_device *sev = psp_master->sev_data;
	पूर्णांक ret;

	ret = __sev_करो_cmd_locked(SEV_CMD_SHUTDOWN, शून्य, error);
	अगर (ret)
		वापस ret;

	sev->state = SEV_STATE_UNINIT;
	dev_dbg(sev->dev, "SEV firmware shutdown\n");

	वापस ret;
पूर्ण

अटल पूर्णांक sev_platक्रमm_shutकरोwn(पूर्णांक *error)
अणु
	पूर्णांक rc;

	mutex_lock(&sev_cmd_mutex);
	rc = __sev_platक्रमm_shutकरोwn_locked(शून्य);
	mutex_unlock(&sev_cmd_mutex);

	वापस rc;
पूर्ण

अटल पूर्णांक sev_get_platक्रमm_state(पूर्णांक *state, पूर्णांक *error)
अणु
	काष्ठा sev_user_data_status data;
	पूर्णांक rc;

	rc = __sev_करो_cmd_locked(SEV_CMD_PLATFORM_STATUS, &data, error);
	अगर (rc)
		वापस rc;

	*state = data.state;
	वापस rc;
पूर्ण

अटल पूर्णांक sev_ioctl_करो_reset(काष्ठा sev_issue_cmd *argp, bool writable)
अणु
	पूर्णांक state, rc;

	अगर (!writable)
		वापस -EPERM;

	/*
	 * The SEV spec requires that FACTORY_RESET must be issued in
	 * UNINIT state. Beक्रमe we go further lets check अगर any guest is
	 * active.
	 *
	 * If FW is in WORKING state then deny the request otherwise issue
	 * SHUTDOWN command करो INIT -> UNINIT beक्रमe issuing the FACTORY_RESET.
	 *
	 */
	rc = sev_get_platक्रमm_state(&state, &argp->error);
	अगर (rc)
		वापस rc;

	अगर (state == SEV_STATE_WORKING)
		वापस -EBUSY;

	अगर (state == SEV_STATE_INIT) अणु
		rc = __sev_platक्रमm_shutकरोwn_locked(&argp->error);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस __sev_करो_cmd_locked(SEV_CMD_FACTORY_RESET, शून्य, &argp->error);
पूर्ण

अटल पूर्णांक sev_ioctl_करो_platक्रमm_status(काष्ठा sev_issue_cmd *argp)
अणु
	काष्ठा sev_user_data_status data;
	पूर्णांक ret;

	ret = __sev_करो_cmd_locked(SEV_CMD_PLATFORM_STATUS, &data, &argp->error);
	अगर (ret)
		वापस ret;

	अगर (copy_to_user((व्योम __user *)argp->data, &data, माप(data)))
		ret = -EFAULT;

	वापस ret;
पूर्ण

अटल पूर्णांक sev_ioctl_करो_pek_pdh_gen(पूर्णांक cmd, काष्ठा sev_issue_cmd *argp, bool writable)
अणु
	काष्ठा sev_device *sev = psp_master->sev_data;
	पूर्णांक rc;

	अगर (!writable)
		वापस -EPERM;

	अगर (sev->state == SEV_STATE_UNINIT) अणु
		rc = __sev_platक्रमm_init_locked(&argp->error);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस __sev_करो_cmd_locked(cmd, शून्य, &argp->error);
पूर्ण

अटल पूर्णांक sev_ioctl_करो_pek_csr(काष्ठा sev_issue_cmd *argp, bool writable)
अणु
	काष्ठा sev_device *sev = psp_master->sev_data;
	काष्ठा sev_user_data_pek_csr input;
	काष्ठा sev_data_pek_csr data;
	व्योम __user *input_address;
	व्योम *blob = शून्य;
	पूर्णांक ret;

	अगर (!writable)
		वापस -EPERM;

	अगर (copy_from_user(&input, (व्योम __user *)argp->data, माप(input)))
		वापस -EFAULT;

	स_रखो(&data, 0, माप(data));

	/* userspace wants to query CSR length */
	अगर (!input.address || !input.length)
		जाओ cmd;

	/* allocate a physically contiguous buffer to store the CSR blob */
	input_address = (व्योम __user *)input.address;
	अगर (input.length > SEV_FW_BLOB_MAX_SIZE)
		वापस -EFAULT;

	blob = kदो_स्मृति(input.length, GFP_KERNEL);
	अगर (!blob)
		वापस -ENOMEM;

	data.address = __psp_pa(blob);
	data.len = input.length;

cmd:
	अगर (sev->state == SEV_STATE_UNINIT) अणु
		ret = __sev_platक्रमm_init_locked(&argp->error);
		अगर (ret)
			जाओ e_मुक्त_blob;
	पूर्ण

	ret = __sev_करो_cmd_locked(SEV_CMD_PEK_CSR, &data, &argp->error);

	 /* If we query the CSR length, FW responded with expected data. */
	input.length = data.len;

	अगर (copy_to_user((व्योम __user *)argp->data, &input, माप(input))) अणु
		ret = -EFAULT;
		जाओ e_मुक्त_blob;
	पूर्ण

	अगर (blob) अणु
		अगर (copy_to_user(input_address, blob, input.length))
			ret = -EFAULT;
	पूर्ण

e_मुक्त_blob:
	kमुक्त(blob);
	वापस ret;
पूर्ण

व्योम *psp_copy_user_blob(u64 uaddr, u32 len)
अणु
	अगर (!uaddr || !len)
		वापस ERR_PTR(-EINVAL);

	/* verअगरy that blob length करोes not exceed our limit */
	अगर (len > SEV_FW_BLOB_MAX_SIZE)
		वापस ERR_PTR(-EINVAL);

	वापस memdup_user((व्योम __user *)uaddr, len);
पूर्ण
EXPORT_SYMBOL_GPL(psp_copy_user_blob);

अटल पूर्णांक sev_get_api_version(व्योम)
अणु
	काष्ठा sev_device *sev = psp_master->sev_data;
	काष्ठा sev_user_data_status status;
	पूर्णांक error = 0, ret;

	ret = sev_platक्रमm_status(&status, &error);
	अगर (ret) अणु
		dev_err(sev->dev,
			"SEV: failed to get status. Error: %#x\n", error);
		वापस 1;
	पूर्ण

	sev->api_major = status.api_major;
	sev->api_minor = status.api_minor;
	sev->build = status.build;
	sev->state = status.state;

	वापस 0;
पूर्ण

अटल पूर्णांक sev_get_firmware(काष्ठा device *dev,
			    स्थिर काष्ठा firmware **firmware)
अणु
	अक्षर fw_name_specअगरic[SEV_FW_NAME_SIZE];
	अक्षर fw_name_subset[SEV_FW_NAME_SIZE];

	snम_लिखो(fw_name_specअगरic, माप(fw_name_specअगरic),
		 "amd/amd_sev_fam%.2xh_model%.2xh.sbin",
		 boot_cpu_data.x86, boot_cpu_data.x86_model);

	snम_लिखो(fw_name_subset, माप(fw_name_subset),
		 "amd/amd_sev_fam%.2xh_model%.1xxh.sbin",
		 boot_cpu_data.x86, (boot_cpu_data.x86_model & 0xf0) >> 4);

	/* Check क्रम SEV FW क्रम a particular model.
	 * Ex. amd_sev_fam17h_model00h.sbin क्रम Family 17h Model 00h
	 *
	 * or
	 *
	 * Check क्रम SEV FW common to a subset of models.
	 * Ex. amd_sev_fam17h_model0xh.sbin क्रम
	 *     Family 17h Model 00h -- Family 17h Model 0Fh
	 *
	 * or
	 *
	 * Fall-back to using generic name: sev.fw
	 */
	अगर ((firmware_request_nowarn(firmware, fw_name_specअगरic, dev) >= 0) ||
	    (firmware_request_nowarn(firmware, fw_name_subset, dev) >= 0) ||
	    (firmware_request_nowarn(firmware, SEV_FW_खाता, dev) >= 0))
		वापस 0;

	वापस -ENOENT;
पूर्ण

/* Don't fail if SEV FW couldn't be updated. Continue with existing SEV FW */
अटल पूर्णांक sev_update_firmware(काष्ठा device *dev)
अणु
	काष्ठा sev_data_करोwnload_firmware *data;
	स्थिर काष्ठा firmware *firmware;
	पूर्णांक ret, error, order;
	काष्ठा page *p;
	u64 data_size;

	अगर (sev_get_firmware(dev, &firmware) == -ENOENT) अणु
		dev_dbg(dev, "No SEV firmware file present\n");
		वापस -1;
	पूर्ण

	/*
	 * SEV FW expects the physical address given to it to be 32
	 * byte aligned. Memory allocated has काष्ठाure placed at the
	 * beginning followed by the firmware being passed to the SEV
	 * FW. Allocate enough memory क्रम data काष्ठाure + alignment
	 * padding + SEV FW.
	 */
	data_size = ALIGN(माप(काष्ठा sev_data_करोwnload_firmware), 32);

	order = get_order(firmware->size + data_size);
	p = alloc_pages(GFP_KERNEL, order);
	अगर (!p) अणु
		ret = -1;
		जाओ fw_err;
	पूर्ण

	/*
	 * Copy firmware data to a kernel allocated contiguous
	 * memory region.
	 */
	data = page_address(p);
	स_नकल(page_address(p) + data_size, firmware->data, firmware->size);

	data->address = __psp_pa(page_address(p) + data_size);
	data->len = firmware->size;

	ret = sev_करो_cmd(SEV_CMD_DOWNLOAD_FIRMWARE, data, &error);
	अगर (ret)
		dev_dbg(dev, "Failed to update SEV firmware: %#x\n", error);
	अन्यथा
		dev_info(dev, "SEV firmware update successful\n");

	__मुक्त_pages(p, order);

fw_err:
	release_firmware(firmware);

	वापस ret;
पूर्ण

अटल पूर्णांक sev_ioctl_करो_pek_import(काष्ठा sev_issue_cmd *argp, bool writable)
अणु
	काष्ठा sev_device *sev = psp_master->sev_data;
	काष्ठा sev_user_data_pek_cert_import input;
	काष्ठा sev_data_pek_cert_import data;
	व्योम *pek_blob, *oca_blob;
	पूर्णांक ret;

	अगर (!writable)
		वापस -EPERM;

	अगर (copy_from_user(&input, (व्योम __user *)argp->data, माप(input)))
		वापस -EFAULT;

	/* copy PEK certअगरicate blobs from userspace */
	pek_blob = psp_copy_user_blob(input.pek_cert_address, input.pek_cert_len);
	अगर (IS_ERR(pek_blob))
		वापस PTR_ERR(pek_blob);

	data.reserved = 0;
	data.pek_cert_address = __psp_pa(pek_blob);
	data.pek_cert_len = input.pek_cert_len;

	/* copy PEK certअगरicate blobs from userspace */
	oca_blob = psp_copy_user_blob(input.oca_cert_address, input.oca_cert_len);
	अगर (IS_ERR(oca_blob)) अणु
		ret = PTR_ERR(oca_blob);
		जाओ e_मुक्त_pek;
	पूर्ण

	data.oca_cert_address = __psp_pa(oca_blob);
	data.oca_cert_len = input.oca_cert_len;

	/* If platक्रमm is not in INIT state then transition it to INIT */
	अगर (sev->state != SEV_STATE_INIT) अणु
		ret = __sev_platक्रमm_init_locked(&argp->error);
		अगर (ret)
			जाओ e_मुक्त_oca;
	पूर्ण

	ret = __sev_करो_cmd_locked(SEV_CMD_PEK_CERT_IMPORT, &data, &argp->error);

e_मुक्त_oca:
	kमुक्त(oca_blob);
e_मुक्त_pek:
	kमुक्त(pek_blob);
	वापस ret;
पूर्ण

अटल पूर्णांक sev_ioctl_करो_get_id2(काष्ठा sev_issue_cmd *argp)
अणु
	काष्ठा sev_user_data_get_id2 input;
	काष्ठा sev_data_get_id data;
	व्योम __user *input_address;
	व्योम *id_blob = शून्य;
	पूर्णांक ret;

	/* SEV GET_ID is available from SEV API v0.16 and up */
	अगर (!sev_version_greater_or_equal(0, 16))
		वापस -ENOTSUPP;

	अगर (copy_from_user(&input, (व्योम __user *)argp->data, माप(input)))
		वापस -EFAULT;

	input_address = (व्योम __user *)input.address;

	अगर (input.address && input.length) अणु
		id_blob = kदो_स्मृति(input.length, GFP_KERNEL);
		अगर (!id_blob)
			वापस -ENOMEM;

		data.address = __psp_pa(id_blob);
		data.len = input.length;
	पूर्ण अन्यथा अणु
		data.address = 0;
		data.len = 0;
	पूर्ण

	ret = __sev_करो_cmd_locked(SEV_CMD_GET_ID, &data, &argp->error);

	/*
	 * Firmware will वापस the length of the ID value (either the minimum
	 * required length or the actual length written), वापस it to the user.
	 */
	input.length = data.len;

	अगर (copy_to_user((व्योम __user *)argp->data, &input, माप(input))) अणु
		ret = -EFAULT;
		जाओ e_मुक्त;
	पूर्ण

	अगर (id_blob) अणु
		अगर (copy_to_user(input_address, id_blob, data.len)) अणु
			ret = -EFAULT;
			जाओ e_मुक्त;
		पूर्ण
	पूर्ण

e_मुक्त:
	kमुक्त(id_blob);

	वापस ret;
पूर्ण

अटल पूर्णांक sev_ioctl_करो_get_id(काष्ठा sev_issue_cmd *argp)
अणु
	काष्ठा sev_data_get_id *data;
	u64 data_size, user_size;
	व्योम *id_blob, *mem;
	पूर्णांक ret;

	/* SEV GET_ID available from SEV API v0.16 and up */
	अगर (!sev_version_greater_or_equal(0, 16))
		वापस -ENOTSUPP;

	/* SEV FW expects the buffer it fills with the ID to be
	 * 8-byte aligned. Memory allocated should be enough to
	 * hold data काष्ठाure + alignment padding + memory
	 * where SEV FW ग_लिखोs the ID.
	 */
	data_size = ALIGN(माप(काष्ठा sev_data_get_id), 8);
	user_size = माप(काष्ठा sev_user_data_get_id);

	mem = kzalloc(data_size + user_size, GFP_KERNEL);
	अगर (!mem)
		वापस -ENOMEM;

	data = mem;
	id_blob = mem + data_size;

	data->address = __psp_pa(id_blob);
	data->len = user_size;

	ret = __sev_करो_cmd_locked(SEV_CMD_GET_ID, data, &argp->error);
	अगर (!ret) अणु
		अगर (copy_to_user((व्योम __user *)argp->data, id_blob, data->len))
			ret = -EFAULT;
	पूर्ण

	kमुक्त(mem);

	वापस ret;
पूर्ण

अटल पूर्णांक sev_ioctl_करो_pdh_export(काष्ठा sev_issue_cmd *argp, bool writable)
अणु
	काष्ठा sev_device *sev = psp_master->sev_data;
	काष्ठा sev_user_data_pdh_cert_export input;
	व्योम *pdh_blob = शून्य, *cert_blob = शून्य;
	काष्ठा sev_data_pdh_cert_export data;
	व्योम __user *input_cert_chain_address;
	व्योम __user *input_pdh_cert_address;
	पूर्णांक ret;

	/* If platक्रमm is not in INIT state then transition it to INIT. */
	अगर (sev->state != SEV_STATE_INIT) अणु
		अगर (!writable)
			वापस -EPERM;

		ret = __sev_platक्रमm_init_locked(&argp->error);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (copy_from_user(&input, (व्योम __user *)argp->data, माप(input)))
		वापस -EFAULT;

	स_रखो(&data, 0, माप(data));

	/* Userspace wants to query the certअगरicate length. */
	अगर (!input.pdh_cert_address ||
	    !input.pdh_cert_len ||
	    !input.cert_chain_address)
		जाओ cmd;

	input_pdh_cert_address = (व्योम __user *)input.pdh_cert_address;
	input_cert_chain_address = (व्योम __user *)input.cert_chain_address;

	/* Allocate a physically contiguous buffer to store the PDH blob. */
	अगर (input.pdh_cert_len > SEV_FW_BLOB_MAX_SIZE)
		वापस -EFAULT;

	/* Allocate a physically contiguous buffer to store the cert chain blob. */
	अगर (input.cert_chain_len > SEV_FW_BLOB_MAX_SIZE)
		वापस -EFAULT;

	pdh_blob = kदो_स्मृति(input.pdh_cert_len, GFP_KERNEL);
	अगर (!pdh_blob)
		वापस -ENOMEM;

	data.pdh_cert_address = __psp_pa(pdh_blob);
	data.pdh_cert_len = input.pdh_cert_len;

	cert_blob = kदो_स्मृति(input.cert_chain_len, GFP_KERNEL);
	अगर (!cert_blob) अणु
		ret = -ENOMEM;
		जाओ e_मुक्त_pdh;
	पूर्ण

	data.cert_chain_address = __psp_pa(cert_blob);
	data.cert_chain_len = input.cert_chain_len;

cmd:
	ret = __sev_करो_cmd_locked(SEV_CMD_PDH_CERT_EXPORT, &data, &argp->error);

	/* If we query the length, FW responded with expected data. */
	input.cert_chain_len = data.cert_chain_len;
	input.pdh_cert_len = data.pdh_cert_len;

	अगर (copy_to_user((व्योम __user *)argp->data, &input, माप(input))) अणु
		ret = -EFAULT;
		जाओ e_मुक्त_cert;
	पूर्ण

	अगर (pdh_blob) अणु
		अगर (copy_to_user(input_pdh_cert_address,
				 pdh_blob, input.pdh_cert_len)) अणु
			ret = -EFAULT;
			जाओ e_मुक्त_cert;
		पूर्ण
	पूर्ण

	अगर (cert_blob) अणु
		अगर (copy_to_user(input_cert_chain_address,
				 cert_blob, input.cert_chain_len))
			ret = -EFAULT;
	पूर्ण

e_मुक्त_cert:
	kमुक्त(cert_blob);
e_मुक्त_pdh:
	kमुक्त(pdh_blob);
	वापस ret;
पूर्ण

अटल दीर्घ sev_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा sev_issue_cmd input;
	पूर्णांक ret = -EFAULT;
	bool writable = file->f_mode & FMODE_WRITE;

	अगर (!psp_master || !psp_master->sev_data)
		वापस -ENODEV;

	अगर (ioctl != SEV_ISSUE_CMD)
		वापस -EINVAL;

	अगर (copy_from_user(&input, argp, माप(काष्ठा sev_issue_cmd)))
		वापस -EFAULT;

	अगर (input.cmd > SEV_MAX)
		वापस -EINVAL;

	mutex_lock(&sev_cmd_mutex);

	चयन (input.cmd) अणु

	हाल SEV_FACTORY_RESET:
		ret = sev_ioctl_करो_reset(&input, writable);
		अवरोध;
	हाल SEV_PLATFORM_STATUS:
		ret = sev_ioctl_करो_platक्रमm_status(&input);
		अवरोध;
	हाल SEV_PEK_GEN:
		ret = sev_ioctl_करो_pek_pdh_gen(SEV_CMD_PEK_GEN, &input, writable);
		अवरोध;
	हाल SEV_PDH_GEN:
		ret = sev_ioctl_करो_pek_pdh_gen(SEV_CMD_PDH_GEN, &input, writable);
		अवरोध;
	हाल SEV_PEK_CSR:
		ret = sev_ioctl_करो_pek_csr(&input, writable);
		अवरोध;
	हाल SEV_PEK_CERT_IMPORT:
		ret = sev_ioctl_करो_pek_import(&input, writable);
		अवरोध;
	हाल SEV_PDH_CERT_EXPORT:
		ret = sev_ioctl_करो_pdh_export(&input, writable);
		अवरोध;
	हाल SEV_GET_ID:
		pr_warn_once("SEV_GET_ID command is deprecated, use SEV_GET_ID2\n");
		ret = sev_ioctl_करो_get_id(&input);
		अवरोध;
	हाल SEV_GET_ID2:
		ret = sev_ioctl_करो_get_id2(&input);
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (copy_to_user(argp, &input, माप(काष्ठा sev_issue_cmd)))
		ret = -EFAULT;
out:
	mutex_unlock(&sev_cmd_mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations sev_fops = अणु
	.owner	= THIS_MODULE,
	.unlocked_ioctl = sev_ioctl,
पूर्ण;

पूर्णांक sev_platक्रमm_status(काष्ठा sev_user_data_status *data, पूर्णांक *error)
अणु
	वापस sev_करो_cmd(SEV_CMD_PLATFORM_STATUS, data, error);
पूर्ण
EXPORT_SYMBOL_GPL(sev_platक्रमm_status);

पूर्णांक sev_guest_deactivate(काष्ठा sev_data_deactivate *data, पूर्णांक *error)
अणु
	वापस sev_करो_cmd(SEV_CMD_DEACTIVATE, data, error);
पूर्ण
EXPORT_SYMBOL_GPL(sev_guest_deactivate);

पूर्णांक sev_guest_activate(काष्ठा sev_data_activate *data, पूर्णांक *error)
अणु
	वापस sev_करो_cmd(SEV_CMD_ACTIVATE, data, error);
पूर्ण
EXPORT_SYMBOL_GPL(sev_guest_activate);

पूर्णांक sev_guest_decommission(काष्ठा sev_data_decommission *data, पूर्णांक *error)
अणु
	वापस sev_करो_cmd(SEV_CMD_DECOMMISSION, data, error);
पूर्ण
EXPORT_SYMBOL_GPL(sev_guest_decommission);

पूर्णांक sev_guest_df_flush(पूर्णांक *error)
अणु
	वापस sev_करो_cmd(SEV_CMD_DF_FLUSH, शून्य, error);
पूर्ण
EXPORT_SYMBOL_GPL(sev_guest_df_flush);

अटल व्योम sev_निकास(काष्ठा kref *ref)
अणु
	misc_deरेजिस्टर(&misc_dev->misc);
	kमुक्त(misc_dev);
	misc_dev = शून्य;
पूर्ण

अटल पूर्णांक sev_misc_init(काष्ठा sev_device *sev)
अणु
	काष्ठा device *dev = sev->dev;
	पूर्णांक ret;

	/*
	 * SEV feature support can be detected on multiple devices but the SEV
	 * FW commands must be issued on the master. During probe, we करो not
	 * know the master hence we create /dev/sev on the first device probe.
	 * sev_करो_cmd() finds the right master device to which to issue the
	 * command to the firmware.
	 */
	अगर (!misc_dev) अणु
		काष्ठा miscdevice *misc;

		misc_dev = kzalloc(माप(*misc_dev), GFP_KERNEL);
		अगर (!misc_dev)
			वापस -ENOMEM;

		misc = &misc_dev->misc;
		misc->minor = MISC_DYNAMIC_MINOR;
		misc->name = DEVICE_NAME;
		misc->fops = &sev_fops;

		ret = misc_रेजिस्टर(misc);
		अगर (ret)
			वापस ret;

		kref_init(&misc_dev->refcount);
	पूर्ण अन्यथा अणु
		kref_get(&misc_dev->refcount);
	पूर्ण

	init_रुकोqueue_head(&sev->पूर्णांक_queue);
	sev->misc = misc_dev;
	dev_dbg(dev, "registered SEV device\n");

	वापस 0;
पूर्ण

पूर्णांक sev_dev_init(काष्ठा psp_device *psp)
अणु
	काष्ठा device *dev = psp->dev;
	काष्ठा sev_device *sev;
	पूर्णांक ret = -ENOMEM;

	अगर (!boot_cpu_has(X86_FEATURE_SEV)) अणु
		dev_info_once(dev, "SEV: memory encryption not enabled by BIOS\n");
		वापस 0;
	पूर्ण

	sev = devm_kzalloc(dev, माप(*sev), GFP_KERNEL);
	अगर (!sev)
		जाओ e_err;

	sev->cmd_buf = (व्योम *)devm_get_मुक्त_pages(dev, GFP_KERNEL, 0);
	अगर (!sev->cmd_buf)
		जाओ e_sev;

	psp->sev_data = sev;

	sev->dev = dev;
	sev->psp = psp;

	sev->io_regs = psp->io_regs;

	sev->vdata = (काष्ठा sev_vdata *)psp->vdata->sev;
	अगर (!sev->vdata) अणु
		ret = -ENODEV;
		dev_err(dev, "sev: missing driver data\n");
		जाओ e_buf;
	पूर्ण

	psp_set_sev_irq_handler(psp, sev_irq_handler, sev);

	ret = sev_misc_init(sev);
	अगर (ret)
		जाओ e_irq;

	dev_notice(dev, "sev enabled\n");

	वापस 0;

e_irq:
	psp_clear_sev_irq_handler(psp);
e_buf:
	devm_मुक्त_pages(dev, (अचिन्हित दीर्घ)sev->cmd_buf);
e_sev:
	devm_kमुक्त(dev, sev);
e_err:
	psp->sev_data = शून्य;

	dev_notice(dev, "sev initialization failed\n");

	वापस ret;
पूर्ण

व्योम sev_dev_destroy(काष्ठा psp_device *psp)
अणु
	काष्ठा sev_device *sev = psp->sev_data;

	अगर (!sev)
		वापस;

	अगर (sev->misc)
		kref_put(&misc_dev->refcount, sev_निकास);

	psp_clear_sev_irq_handler(psp);
पूर्ण

पूर्णांक sev_issue_cmd_बाह्यal_user(काष्ठा file *filep, अचिन्हित पूर्णांक cmd,
				व्योम *data, पूर्णांक *error)
अणु
	अगर (!filep || filep->f_op != &sev_fops)
		वापस -EBADF;

	वापस sev_करो_cmd(cmd, data, error);
पूर्ण
EXPORT_SYMBOL_GPL(sev_issue_cmd_बाह्यal_user);

व्योम sev_pci_init(व्योम)
अणु
	काष्ठा sev_device *sev = psp_master->sev_data;
	काष्ठा page *पंचांगr_page;
	पूर्णांक error, rc;

	अगर (!sev)
		वापस;

	psp_समयout = psp_probe_समयout;

	अगर (sev_get_api_version())
		जाओ err;

	/*
	 * If platक्रमm is not in UNINIT state then firmware upgrade and/or
	 * platक्रमm INIT command will fail. These command require UNINIT state.
	 *
	 * In a normal boot we should never run पूर्णांकo हाल where the firmware
	 * is not in UNINIT state on boot. But in हाल of kexec boot, a reboot
	 * may not go through a typical shutकरोwn sequence and may leave the
	 * firmware in INIT or WORKING state.
	 */

	अगर (sev->state != SEV_STATE_UNINIT) अणु
		sev_platक्रमm_shutकरोwn(शून्य);
		sev->state = SEV_STATE_UNINIT;
	पूर्ण

	अगर (sev_version_greater_or_equal(0, 15) &&
	    sev_update_firmware(sev->dev) == 0)
		sev_get_api_version();

	/* Obtain the TMR memory area क्रम SEV-ES use */
	पंचांगr_page = alloc_pages(GFP_KERNEL, get_order(SEV_ES_TMR_SIZE));
	अगर (पंचांगr_page) अणु
		sev_es_पंचांगr = page_address(पंचांगr_page);
	पूर्ण अन्यथा अणु
		sev_es_पंचांगr = शून्य;
		dev_warn(sev->dev,
			 "SEV: TMR allocation failed, SEV-ES support unavailable\n");
	पूर्ण

	/* Initialize the platक्रमm */
	rc = sev_platक्रमm_init(&error);
	अगर (rc && (error == SEV_RET_SECURE_DATA_INVALID)) अणु
		/*
		 * INIT command वापसed an पूर्णांकegrity check failure
		 * status code, meaning that firmware load and
		 * validation of SEV related persistent data has
		 * failed and persistent state has been erased.
		 * Retrying INIT command here should succeed.
		 */
		dev_dbg(sev->dev, "SEV: retrying INIT command");
		rc = sev_platक्रमm_init(&error);
	पूर्ण

	अगर (rc) अणु
		dev_err(sev->dev, "SEV: failed to INIT error %#x\n", error);
		वापस;
	पूर्ण

	dev_info(sev->dev, "SEV API:%d.%d build:%d\n", sev->api_major,
		 sev->api_minor, sev->build);

	वापस;

err:
	psp_master->sev_data = शून्य;
पूर्ण

व्योम sev_pci_निकास(व्योम)
अणु
	अगर (!psp_master->sev_data)
		वापस;

	sev_platक्रमm_shutकरोwn(शून्य);

	अगर (sev_es_पंचांगr) अणु
		/* The TMR area was encrypted, flush it from the cache */
		wbinvd_on_all_cpus();

		मुक्त_pages((अचिन्हित दीर्घ)sev_es_पंचांगr,
			   get_order(SEV_ES_TMR_SIZE));
		sev_es_पंचांगr = शून्य;
	पूर्ण
पूर्ण
