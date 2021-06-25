<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  dcdbas.c: Dell Systems Management Base Driver
 *
 *  The Dell Systems Management Base Driver provides a sysfs पूर्णांकerface क्रम
 *  प्रणालीs management software to perक्रमm System Management Interrupts (SMIs)
 *  and Host Control Actions (घातer cycle or घातer off after OS shutकरोwn) on
 *  Dell प्रणालीs.
 *
 *  See Documentation/driver-api/dcdbas.rst क्रम more inक्रमmation.
 *
 *  Copyright (C) 1995-2006 Dell Inc.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/acpi.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmi.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/cpu.h>
#समावेश <linux/gfp.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/module.h>
#समावेश <linux/reboot.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/mutex.h>

#समावेश "dcdbas.h"

#घोषणा DRIVER_NAME		"dcdbas"
#घोषणा DRIVER_VERSION		"5.6.0-3.4"
#घोषणा DRIVER_DESCRIPTION	"Dell Systems Management Base Driver"

अटल काष्ठा platक्रमm_device *dcdbas_pdev;

अटल u8 *smi_data_buf;
अटल dma_addr_t smi_data_buf_handle;
अटल अचिन्हित दीर्घ smi_data_buf_size;
अटल अचिन्हित दीर्घ max_smi_data_buf_size = MAX_SMI_DATA_BUF_SIZE;
अटल u32 smi_data_buf_phys_addr;
अटल DEFINE_MUTEX(smi_data_lock);
अटल u8 *bios_buffer;

अटल अचिन्हित पूर्णांक host_control_action;
अटल अचिन्हित पूर्णांक host_control_smi_type;
अटल अचिन्हित पूर्णांक host_control_on_shutकरोwn;

अटल bool wsmt_enabled;

/**
 * smi_data_buf_मुक्त: मुक्त SMI data buffer
 */
अटल व्योम smi_data_buf_मुक्त(व्योम)
अणु
	अगर (!smi_data_buf || wsmt_enabled)
		वापस;

	dev_dbg(&dcdbas_pdev->dev, "%s: phys: %x size: %lu\n",
		__func__, smi_data_buf_phys_addr, smi_data_buf_size);

	dma_मुक्त_coherent(&dcdbas_pdev->dev, smi_data_buf_size, smi_data_buf,
			  smi_data_buf_handle);
	smi_data_buf = शून्य;
	smi_data_buf_handle = 0;
	smi_data_buf_phys_addr = 0;
	smi_data_buf_size = 0;
पूर्ण

/**
 * smi_data_buf_पुनः_स्मृति: grow SMI data buffer अगर needed
 */
अटल पूर्णांक smi_data_buf_पुनः_स्मृति(अचिन्हित दीर्घ size)
अणु
	व्योम *buf;
	dma_addr_t handle;

	अगर (smi_data_buf_size >= size)
		वापस 0;

	अगर (size > max_smi_data_buf_size)
		वापस -EINVAL;

	/* new buffer is needed */
	buf = dma_alloc_coherent(&dcdbas_pdev->dev, size, &handle, GFP_KERNEL);
	अगर (!buf) अणु
		dev_dbg(&dcdbas_pdev->dev,
			"%s: failed to allocate memory size %lu\n",
			__func__, size);
		वापस -ENOMEM;
	पूर्ण
	/* memory zeroed by dma_alloc_coherent */

	अगर (smi_data_buf)
		स_नकल(buf, smi_data_buf, smi_data_buf_size);

	/* मुक्त any existing buffer */
	smi_data_buf_मुक्त();

	/* set up new buffer क्रम use */
	smi_data_buf = buf;
	smi_data_buf_handle = handle;
	smi_data_buf_phys_addr = (u32) virt_to_phys(buf);
	smi_data_buf_size = size;

	dev_dbg(&dcdbas_pdev->dev, "%s: phys: %x size: %lu\n",
		__func__, smi_data_buf_phys_addr, smi_data_buf_size);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार smi_data_buf_phys_addr_show(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%x\n", smi_data_buf_phys_addr);
पूर्ण

अटल sमाप_प्रकार smi_data_buf_size_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%lu\n", smi_data_buf_size);
पूर्ण

अटल sमाप_प्रकार smi_data_buf_size_store(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ buf_size;
	sमाप_प्रकार ret;

	buf_size = simple_म_से_अदीर्घ(buf, शून्य, 10);

	/* make sure SMI data buffer is at least buf_size */
	mutex_lock(&smi_data_lock);
	ret = smi_data_buf_पुनः_स्मृति(buf_size);
	mutex_unlock(&smi_data_lock);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार smi_data_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			     काष्ठा bin_attribute *bin_attr,
			     अक्षर *buf, loff_t pos, माप_प्रकार count)
अणु
	sमाप_प्रकार ret;

	mutex_lock(&smi_data_lock);
	ret = memory_पढ़ो_from_buffer(buf, count, &pos, smi_data_buf,
					smi_data_buf_size);
	mutex_unlock(&smi_data_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार smi_data_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
			      काष्ठा bin_attribute *bin_attr,
			      अक्षर *buf, loff_t pos, माप_प्रकार count)
अणु
	sमाप_प्रकार ret;

	अगर ((pos + count) > max_smi_data_buf_size)
		वापस -EINVAL;

	mutex_lock(&smi_data_lock);

	ret = smi_data_buf_पुनः_स्मृति(pos + count);
	अगर (ret)
		जाओ out;

	स_नकल(smi_data_buf + pos, buf, count);
	ret = count;
out:
	mutex_unlock(&smi_data_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार host_control_action_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", host_control_action);
पूर्ण

अटल sमाप_प्रकार host_control_action_store(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	sमाप_प्रकार ret;

	/* make sure buffer is available क्रम host control command */
	mutex_lock(&smi_data_lock);
	ret = smi_data_buf_पुनः_स्मृति(माप(काष्ठा apm_cmd));
	mutex_unlock(&smi_data_lock);
	अगर (ret)
		वापस ret;

	host_control_action = simple_म_से_अदीर्घ(buf, शून्य, 10);
	वापस count;
पूर्ण

अटल sमाप_प्रकार host_control_smi_type_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", host_control_smi_type);
पूर्ण

अटल sमाप_प्रकार host_control_smi_type_store(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	host_control_smi_type = simple_म_से_अदीर्घ(buf, शून्य, 10);
	वापस count;
पूर्ण

अटल sमाप_प्रकार host_control_on_shutकरोwn_show(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", host_control_on_shutकरोwn);
पूर्ण

अटल sमाप_प्रकार host_control_on_shutकरोwn_store(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	host_control_on_shutकरोwn = simple_म_से_अदीर्घ(buf, शून्य, 10);
	वापस count;
पूर्ण

अटल पूर्णांक उठाओ_smi(व्योम *par)
अणु
	काष्ठा smi_cmd *smi_cmd = par;

	अगर (smp_processor_id() != 0) अणु
		dev_dbg(&dcdbas_pdev->dev, "%s: failed to get CPU 0\n",
			__func__);
		वापस -EBUSY;
	पूर्ण

	/* generate SMI */
	/* inb to क्रमce posted ग_लिखो through and make SMI happen now */
	यंत्र अस्थिर (
		"outb %b0,%w1\n"
		"inb %w1"
		: /* no output args */
		: "a" (smi_cmd->command_code),
		  "d" (smi_cmd->command_address),
		  "b" (smi_cmd->ebx),
		  "c" (smi_cmd->ecx)
		: "memory"
	);

	वापस 0;
पूर्ण
/**
 * dcdbas_smi_request: generate SMI request
 *
 * Called with smi_data_lock.
 */
पूर्णांक dcdbas_smi_request(काष्ठा smi_cmd *smi_cmd)
अणु
	पूर्णांक ret;

	अगर (smi_cmd->magic != SMI_CMD_MAGIC) अणु
		dev_info(&dcdbas_pdev->dev, "%s: invalid magic value\n",
			 __func__);
		वापस -EBADR;
	पूर्ण

	/* SMI requires CPU 0 */
	get_online_cpus();
	ret = smp_call_on_cpu(0, उठाओ_smi, smi_cmd, true);
	put_online_cpus();

	वापस ret;
पूर्ण

/**
 * smi_request_store:
 *
 * The valid values are:
 * 0: zero SMI data buffer
 * 1: generate calling पूर्णांकerface SMI
 * 2: generate raw SMI
 *
 * User application ग_लिखोs smi_cmd to smi_data beक्रमe telling driver
 * to generate SMI.
 */
अटल sमाप_प्रकार smi_request_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा smi_cmd *smi_cmd;
	अचिन्हित दीर्घ val = simple_म_से_अदीर्घ(buf, शून्य, 10);
	sमाप_प्रकार ret;

	mutex_lock(&smi_data_lock);

	अगर (smi_data_buf_size < माप(काष्ठा smi_cmd)) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण
	smi_cmd = (काष्ठा smi_cmd *)smi_data_buf;

	चयन (val) अणु
	हाल 2:
		/* Raw SMI */
		ret = dcdbas_smi_request(smi_cmd);
		अगर (!ret)
			ret = count;
		अवरोध;
	हाल 1:
		/*
		 * Calling Interface SMI
		 *
		 * Provide physical address of command buffer field within
		 * the काष्ठा smi_cmd to BIOS.
		 *
		 * Because the address that smi_cmd (smi_data_buf) poपूर्णांकs to
		 * will be from memremap() of a non-memory address अगर WSMT
		 * is present, we can't use virt_to_phys() on smi_cmd, so
		 * we have to use the physical address that was saved when
		 * the भव address क्रम smi_cmd was received.
		 */
		smi_cmd->ebx = smi_data_buf_phys_addr +
				दुरत्व(काष्ठा smi_cmd, command_buffer);
		ret = dcdbas_smi_request(smi_cmd);
		अगर (!ret)
			ret = count;
		अवरोध;
	हाल 0:
		स_रखो(smi_data_buf, 0, smi_data_buf_size);
		ret = count;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

out:
	mutex_unlock(&smi_data_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(dcdbas_smi_request);

/**
 * host_control_smi: generate host control SMI
 *
 * Caller must set up the host control command in smi_data_buf.
 */
अटल पूर्णांक host_control_smi(व्योम)
अणु
	काष्ठा apm_cmd *apm_cmd;
	u8 *data;
	अचिन्हित दीर्घ flags;
	u32 num_ticks;
	s8 cmd_status;
	u8 index;

	apm_cmd = (काष्ठा apm_cmd *)smi_data_buf;
	apm_cmd->status = ESM_STATUS_CMD_UNSUCCESSFUL;

	चयन (host_control_smi_type) अणु
	हाल HC_SMITYPE_TYPE1:
		spin_lock_irqsave(&rtc_lock, flags);
		/* ग_लिखो SMI data buffer physical address */
		data = (u8 *)&smi_data_buf_phys_addr;
		क्रम (index = PE1300_CMOS_CMD_STRUCT_PTR;
		     index < (PE1300_CMOS_CMD_STRUCT_PTR + 4);
		     index++, data++) अणु
			outb(index,
			     (CMOS_BASE_PORT + CMOS_PAGE2_INDEX_PORT_PIIX4));
			outb(*data,
			     (CMOS_BASE_PORT + CMOS_PAGE2_DATA_PORT_PIIX4));
		पूर्ण

		/* first set status to -1 as called by spec */
		cmd_status = ESM_STATUS_CMD_UNSUCCESSFUL;
		outb((u8) cmd_status, PCAT_APM_STATUS_PORT);

		/* generate SMM call */
		outb(ESM_APM_CMD, PCAT_APM_CONTROL_PORT);
		spin_unlock_irqrestore(&rtc_lock, flags);

		/* रुको a few to see अगर it executed */
		num_ticks = TIMEOUT_USEC_SHORT_SEMA_BLOCKING;
		जबतक ((cmd_status = inb(PCAT_APM_STATUS_PORT))
		       == ESM_STATUS_CMD_UNSUCCESSFUL) अणु
			num_ticks--;
			अगर (num_ticks == EXPIRED_TIMER)
				वापस -ETIME;
		पूर्ण
		अवरोध;

	हाल HC_SMITYPE_TYPE2:
	हाल HC_SMITYPE_TYPE3:
		spin_lock_irqsave(&rtc_lock, flags);
		/* ग_लिखो SMI data buffer physical address */
		data = (u8 *)&smi_data_buf_phys_addr;
		क्रम (index = PE1400_CMOS_CMD_STRUCT_PTR;
		     index < (PE1400_CMOS_CMD_STRUCT_PTR + 4);
		     index++, data++) अणु
			outb(index, (CMOS_BASE_PORT + CMOS_PAGE1_INDEX_PORT));
			outb(*data, (CMOS_BASE_PORT + CMOS_PAGE1_DATA_PORT));
		पूर्ण

		/* generate SMM call */
		अगर (host_control_smi_type == HC_SMITYPE_TYPE3)
			outb(ESM_APM_CMD, PCAT_APM_CONTROL_PORT);
		अन्यथा
			outb(ESM_APM_CMD, PE1400_APM_CONTROL_PORT);

		/* restore RTC index poपूर्णांकer since it was written to above */
		CMOS_READ(RTC_REG_C);
		spin_unlock_irqrestore(&rtc_lock, flags);

		/* पढ़ो control port back to serialize ग_लिखो */
		cmd_status = inb(PE1400_APM_CONTROL_PORT);

		/* रुको a few to see अगर it executed */
		num_ticks = TIMEOUT_USEC_SHORT_SEMA_BLOCKING;
		जबतक (apm_cmd->status == ESM_STATUS_CMD_UNSUCCESSFUL) अणु
			num_ticks--;
			अगर (num_ticks == EXPIRED_TIMER)
				वापस -ETIME;
		पूर्ण
		अवरोध;

	शेष:
		dev_dbg(&dcdbas_pdev->dev, "%s: invalid SMI type %u\n",
			__func__, host_control_smi_type);
		वापस -ENOSYS;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * dcdbas_host_control: initiate host control
 *
 * This function is called by the driver after the प्रणाली has
 * finished shutting करोwn अगर the user application specअगरied a
 * host control action to perक्रमm on shutकरोwn.  It is safe to
 * use smi_data_buf at this poपूर्णांक because the प्रणाली has finished
 * shutting करोwn and no userspace apps are running.
 */
अटल व्योम dcdbas_host_control(व्योम)
अणु
	काष्ठा apm_cmd *apm_cmd;
	u8 action;

	अगर (host_control_action == HC_ACTION_NONE)
		वापस;

	action = host_control_action;
	host_control_action = HC_ACTION_NONE;

	अगर (!smi_data_buf) अणु
		dev_dbg(&dcdbas_pdev->dev, "%s: no SMI buffer\n", __func__);
		वापस;
	पूर्ण

	अगर (smi_data_buf_size < माप(काष्ठा apm_cmd)) अणु
		dev_dbg(&dcdbas_pdev->dev, "%s: SMI buffer too small\n",
			__func__);
		वापस;
	पूर्ण

	apm_cmd = (काष्ठा apm_cmd *)smi_data_buf;

	/* घातer off takes precedence */
	अगर (action & HC_ACTION_HOST_CONTROL_POWEROFF) अणु
		apm_cmd->command = ESM_APM_POWER_CYCLE;
		apm_cmd->reserved = 0;
		*((s16 *)&apm_cmd->parameters.लघुreq.parm[0]) = (s16) 0;
		host_control_smi();
	पूर्ण अन्यथा अगर (action & HC_ACTION_HOST_CONTROL_POWERCYCLE) अणु
		apm_cmd->command = ESM_APM_POWER_CYCLE;
		apm_cmd->reserved = 0;
		*((s16 *)&apm_cmd->parameters.लघुreq.parm[0]) = (s16) 20;
		host_control_smi();
	पूर्ण
पूर्ण

/* WSMT */

अटल u8 checksum(u8 *buffer, u8 length)
अणु
	u8 sum = 0;
	u8 *end = buffer + length;

	जबतक (buffer < end)
		sum += *buffer++;
	वापस sum;
पूर्ण

अटल अंतरभूत काष्ठा smm_eps_table *check_eps_table(u8 *addr)
अणु
	काष्ठा smm_eps_table *eps = (काष्ठा smm_eps_table *)addr;

	अगर (म_भेदन(eps->smm_comm_buff_anchor, SMM_EPS_SIG, 4) != 0)
		वापस शून्य;

	अगर (checksum(addr, eps->length) != 0)
		वापस शून्य;

	वापस eps;
पूर्ण

अटल पूर्णांक dcdbas_check_wsmt(व्योम)
अणु
	स्थिर काष्ठा dmi_device *dev = शून्य;
	काष्ठा acpi_table_wsmt *wsmt = शून्य;
	काष्ठा smm_eps_table *eps = शून्य;
	u64 bios_buf_paddr;
	u64 remap_size;
	u8 *addr;

	acpi_get_table(ACPI_SIG_WSMT, 0, (काष्ठा acpi_table_header **)&wsmt);
	अगर (!wsmt)
		वापस 0;

	/* Check अगर WSMT ACPI table shows that protection is enabled */
	अगर (!(wsmt->protection_flags & ACPI_WSMT_FIXED_COMM_BUFFERS) ||
	    !(wsmt->protection_flags & ACPI_WSMT_COMM_BUFFER_NESTED_PTR_PROTECTION))
		वापस 0;

	/*
	 * BIOS could provide the address/size of the रक्षित buffer
	 * in an SMBIOS string or in an EPS काष्ठाure in 0xFxxxx.
	 */

	/* Check SMBIOS क्रम buffer address */
	जबतक ((dev = dmi_find_device(DMI_DEV_TYPE_OEM_STRING, शून्य, dev)))
		अगर (माला_पूछो(dev->name, "30[%16llx;%8llx]", &bios_buf_paddr,
		    &remap_size) == 2)
			जाओ remap;

	/* Scan क्रम EPS (entry poपूर्णांक काष्ठाure) */
	क्रम (addr = (u8 *)__va(0xf0000);
	     addr < (u8 *)__va(0x100000 - माप(काष्ठा smm_eps_table));
	     addr += 16) अणु
		eps = check_eps_table(addr);
		अगर (eps)
			अवरोध;
	पूर्ण

	अगर (!eps) अणु
		dev_dbg(&dcdbas_pdev->dev, "found WSMT, but no firmware buffer found\n");
		वापस -ENODEV;
	पूर्ण
	bios_buf_paddr = eps->smm_comm_buff_addr;
	remap_size = eps->num_of_4k_pages * PAGE_SIZE;

remap:
	/*
	 * Get physical address of buffer and map to भव address.
	 * Table gives size in 4K pages, regardless of actual प्रणाली page size.
	 */
	अगर (upper_32_bits(bios_buf_paddr + 8)) अणु
		dev_warn(&dcdbas_pdev->dev, "found WSMT, but buffer address is above 4GB\n");
		वापस -EINVAL;
	पूर्ण
	/*
	 * Limit remap size to MAX_SMI_DATA_BUF_SIZE + 8 (since the first 8
	 * bytes are used क्रम a semaphore, not the data buffer itself).
	 */
	अगर (remap_size > MAX_SMI_DATA_BUF_SIZE + 8)
		remap_size = MAX_SMI_DATA_BUF_SIZE + 8;

	bios_buffer = memremap(bios_buf_paddr, remap_size, MEMREMAP_WB);
	अगर (!bios_buffer) अणु
		dev_warn(&dcdbas_pdev->dev, "found WSMT, but failed to map buffer\n");
		वापस -ENOMEM;
	पूर्ण

	/* First 8 bytes is क्रम a semaphore, not part of the smi_data_buf */
	smi_data_buf_phys_addr = bios_buf_paddr + 8;
	smi_data_buf = bios_buffer + 8;
	smi_data_buf_size = remap_size - 8;
	max_smi_data_buf_size = smi_data_buf_size;
	wsmt_enabled = true;
	dev_info(&dcdbas_pdev->dev,
		 "WSMT found, using firmware-provided SMI buffer.\n");
	वापस 1;
पूर्ण

/**
 * dcdbas_reboot_notअगरy: handle reboot notअगरication क्रम host control
 */
अटल पूर्णांक dcdbas_reboot_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ code,
				व्योम *unused)
अणु
	चयन (code) अणु
	हाल SYS_DOWN:
	हाल SYS_HALT:
	हाल SYS_POWER_OFF:
		अगर (host_control_on_shutकरोwn) अणु
			/* firmware is going to perक्रमm host control action */
			prपूर्णांकk(KERN_WARNING "Please wait for shutdown "
			       "action to complete...\n");
			dcdbas_host_control();
		पूर्ण
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block dcdbas_reboot_nb = अणु
	.notअगरier_call = dcdbas_reboot_notअगरy,
	.next = शून्य,
	.priority = पूर्णांक_न्यून
पूर्ण;

अटल DCDBAS_BIN_ATTR_RW(smi_data);

अटल काष्ठा bin_attribute *dcdbas_bin_attrs[] = अणु
	&bin_attr_smi_data,
	शून्य
पूर्ण;

अटल DCDBAS_DEV_ATTR_RW(smi_data_buf_size);
अटल DCDBAS_DEV_ATTR_RO(smi_data_buf_phys_addr);
अटल DCDBAS_DEV_ATTR_WO(smi_request);
अटल DCDBAS_DEV_ATTR_RW(host_control_action);
अटल DCDBAS_DEV_ATTR_RW(host_control_smi_type);
अटल DCDBAS_DEV_ATTR_RW(host_control_on_shutकरोwn);

अटल काष्ठा attribute *dcdbas_dev_attrs[] = अणु
	&dev_attr_smi_data_buf_size.attr,
	&dev_attr_smi_data_buf_phys_addr.attr,
	&dev_attr_smi_request.attr,
	&dev_attr_host_control_action.attr,
	&dev_attr_host_control_smi_type.attr,
	&dev_attr_host_control_on_shutकरोwn.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group dcdbas_attr_group = अणु
	.attrs = dcdbas_dev_attrs,
	.bin_attrs = dcdbas_bin_attrs,
पूर्ण;

अटल पूर्णांक dcdbas_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक error;

	host_control_action = HC_ACTION_NONE;
	host_control_smi_type = HC_SMITYPE_NONE;

	dcdbas_pdev = dev;

	/* Check अगर ACPI WSMT table specअगरies रक्षित SMI buffer address */
	error = dcdbas_check_wsmt();
	अगर (error < 0)
		वापस error;

	/*
	 * BIOS SMI calls require buffer addresses be in 32-bit address space.
	 * This is करोne by setting the DMA mask below.
	 */
	error = dma_set_coherent_mask(&dcdbas_pdev->dev, DMA_BIT_MASK(32));
	अगर (error)
		वापस error;

	error = sysfs_create_group(&dev->dev.kobj, &dcdbas_attr_group);
	अगर (error)
		वापस error;

	रेजिस्टर_reboot_notअगरier(&dcdbas_reboot_nb);

	dev_info(&dev->dev, "%s (version %s)\n",
		 DRIVER_DESCRIPTION, DRIVER_VERSION);

	वापस 0;
पूर्ण

अटल पूर्णांक dcdbas_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	unरेजिस्टर_reboot_notअगरier(&dcdbas_reboot_nb);
	sysfs_हटाओ_group(&dev->dev.kobj, &dcdbas_attr_group);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver dcdbas_driver = अणु
	.driver		= अणु
		.name	= DRIVER_NAME,
	पूर्ण,
	.probe		= dcdbas_probe,
	.हटाओ		= dcdbas_हटाओ,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_info dcdbas_dev_info __initस्थिर = अणु
	.name		= DRIVER_NAME,
	.id		= -1,
	.dma_mask	= DMA_BIT_MASK(32),
पूर्ण;

अटल काष्ठा platक्रमm_device *dcdbas_pdev_reg;

/**
 * dcdbas_init: initialize driver
 */
अटल पूर्णांक __init dcdbas_init(व्योम)
अणु
	पूर्णांक error;

	error = platक्रमm_driver_रेजिस्टर(&dcdbas_driver);
	अगर (error)
		वापस error;

	dcdbas_pdev_reg = platक्रमm_device_रेजिस्टर_full(&dcdbas_dev_info);
	अगर (IS_ERR(dcdbas_pdev_reg)) अणु
		error = PTR_ERR(dcdbas_pdev_reg);
		जाओ err_unरेजिस्टर_driver;
	पूर्ण

	वापस 0;

 err_unरेजिस्टर_driver:
	platक्रमm_driver_unरेजिस्टर(&dcdbas_driver);
	वापस error;
पूर्ण

/**
 * dcdbas_निकास: perक्रमm driver cleanup
 */
अटल व्योम __निकास dcdbas_निकास(व्योम)
अणु
	/*
	 * make sure functions that use dcdbas_pdev are called
	 * beक्रमe platक्रमm_device_unरेजिस्टर
	 */
	unरेजिस्टर_reboot_notअगरier(&dcdbas_reboot_nb);

	/*
	 * We have to मुक्त the buffer here instead of dcdbas_हटाओ
	 * because only in module निकास function we can be sure that
	 * all sysfs attributes beदीर्घing to this module have been
	 * released.
	 */
	अगर (dcdbas_pdev)
		smi_data_buf_मुक्त();
	अगर (bios_buffer)
		memunmap(bios_buffer);
	platक्रमm_device_unरेजिस्टर(dcdbas_pdev_reg);
	platक्रमm_driver_unरेजिस्टर(&dcdbas_driver);
पूर्ण

subsys_initcall_sync(dcdbas_init);
module_निकास(dcdbas_निकास);

MODULE_DESCRIPTION(DRIVER_DESCRIPTION " (version " DRIVER_VERSION ")");
MODULE_VERSION(DRIVER_VERSION);
MODULE_AUTHOR("Dell Inc.");
MODULE_LICENSE("GPL");
/* Any System or BIOS claiming to be by Dell */
MODULE_ALIAS("dmi:*:[bs]vnD[Ee][Ll][Ll]*:*");
