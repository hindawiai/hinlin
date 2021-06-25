<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2010 Google Inc. All Rights Reserved.
 * Author: dlaurie@google.com (Duncan Laurie)
 *
 * Re-worked to expose sysfs APIs by mikew@google.com (Mike Waychison)
 *
 * EFI SMI पूर्णांकerface क्रम Google platक्रमms
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/dmi.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/reboot.h>
#समावेश <linux/efi.h>
#समावेश <linux/module.h>
#समावेश <linux/ucs2_माला.स>
#समावेश <linux/suspend.h>

#घोषणा GSMI_SHUTDOWN_CLEAN	0	/* Clean Shutकरोwn */
/* TODO(mikew@google.com): Tie in HARDLOCKUP_DETECTOR with NMIWDT */
#घोषणा GSMI_SHUTDOWN_NMIWDT	1	/* NMI Watchकरोg */
#घोषणा GSMI_SHUTDOWN_PANIC	2	/* Panic */
#घोषणा GSMI_SHUTDOWN_OOPS	3	/* Oops */
#घोषणा GSMI_SHUTDOWN_DIE	4	/* Die -- No दीर्घer meaningful */
#घोषणा GSMI_SHUTDOWN_MCE	5	/* Machine Check */
#घोषणा GSMI_SHUTDOWN_SOFTWDT	6	/* Software Watchकरोg */
#घोषणा GSMI_SHUTDOWN_MBE	7	/* Uncorrected ECC */
#घोषणा GSMI_SHUTDOWN_TRIPLE	8	/* Triple Fault */

#घोषणा DRIVER_VERSION		"1.0"
#घोषणा GSMI_GUID_SIZE		16
#घोषणा GSMI_BUF_SIZE		1024
#घोषणा GSMI_BUF_ALIGN		माप(u64)
#घोषणा GSMI_CALLBACK		0xef

/* SMI वापस codes */
#घोषणा GSMI_SUCCESS		0x00
#घोषणा GSMI_UNSUPPORTED2	0x03
#घोषणा GSMI_LOG_FULL		0x0b
#घोषणा GSMI_VAR_NOT_FOUND	0x0e
#घोषणा GSMI_HANDSHAKE_SPIN	0x7d
#घोषणा GSMI_HANDSHAKE_CF	0x7e
#घोषणा GSMI_HANDSHAKE_NONE	0x7f
#घोषणा GSMI_INVALID_PARAMETER	0x82
#घोषणा GSMI_UNSUPPORTED	0x83
#घोषणा GSMI_BUFFER_TOO_SMALL	0x85
#घोषणा GSMI_NOT_READY		0x86
#घोषणा GSMI_DEVICE_ERROR	0x87
#घोषणा GSMI_NOT_FOUND		0x8e

#घोषणा QUIRKY_BOARD_HASH 0x78a30a50

/* Internally used commands passed to the firmware */
#घोषणा GSMI_CMD_GET_NVRAM_VAR		0x01
#घोषणा GSMI_CMD_GET_NEXT_VAR		0x02
#घोषणा GSMI_CMD_SET_NVRAM_VAR		0x03
#घोषणा GSMI_CMD_SET_EVENT_LOG		0x08
#घोषणा GSMI_CMD_CLEAR_EVENT_LOG	0x09
#घोषणा GSMI_CMD_LOG_S0IX_SUSPEND	0x0a
#घोषणा GSMI_CMD_LOG_S0IX_RESUME	0x0b
#घोषणा GSMI_CMD_CLEAR_CONFIG		0x20
#घोषणा GSMI_CMD_HANDSHAKE_TYPE		0xC1
#घोषणा GSMI_CMD_RESERVED		0xff

/* Magic entry type क्रम kernel events */
#घोषणा GSMI_LOG_ENTRY_TYPE_KERNEL     0xDEAD

/* SMI buffers must be in 32bit physical address space */
काष्ठा gsmi_buf अणु
	u8 *start;			/* start of buffer */
	माप_प्रकार length;			/* length of buffer */
	u32 address;			/* physical address of buffer */
पूर्ण;

अटल काष्ठा gsmi_device अणु
	काष्ठा platक्रमm_device *pdev;	/* platक्रमm device */
	काष्ठा gsmi_buf *name_buf;	/* variable name buffer */
	काष्ठा gsmi_buf *data_buf;	/* generic data buffer */
	काष्ठा gsmi_buf *param_buf;	/* parameter buffer */
	spinlock_t lock;		/* serialize access to SMIs */
	u16 smi_cmd;			/* SMI command port */
	पूर्णांक handshake_type;		/* firmware handler पूर्णांकerlock type */
	काष्ठा kmem_cache *mem_pool;	/* kmem cache क्रम gsmi_buf allocations */
पूर्ण gsmi_dev;

/* Packed काष्ठाures क्रम communicating with the firmware */
काष्ठा gsmi_nvram_var_param अणु
	efi_guid_t	guid;
	u32		name_ptr;
	u32		attributes;
	u32		data_len;
	u32		data_ptr;
पूर्ण __packed;

काष्ठा gsmi_get_next_var_param अणु
	u8	guid[GSMI_GUID_SIZE];
	u32	name_ptr;
	u32	name_len;
पूर्ण __packed;

काष्ठा gsmi_set_eventlog_param अणु
	u32	data_ptr;
	u32	data_len;
	u32	type;
पूर्ण __packed;

/* Event log क्रमmats */
काष्ठा gsmi_log_entry_type_1 अणु
	u16	type;
	u32	instance;
पूर्ण __packed;

/*
 * Some platक्रमms करोn't have explicit SMI handshake
 * and need to रुको क्रम SMI to complete.
 */
#घोषणा GSMI_DEFAULT_SPINCOUNT	0x10000
अटल अचिन्हित पूर्णांक spincount = GSMI_DEFAULT_SPINCOUNT;
module_param(spincount, uपूर्णांक, 0600);
MODULE_PARM_DESC(spincount,
	"The number of loop iterations to use when using the spin handshake.");

/*
 * Some older platक्रमms with Apollo Lake chipsets करो not support S0ix logging
 * in their GSMI handlers, and behaved poorly when resuming via घातer button
 * press अगर the logging was attempted. Updated firmware with proper behavior
 * has दीर्घ since shipped, removing the need क्रम this opt-in parameter. It
 * now exists as an opt-out parameter क्रम folks defiantly running old
 * firmware, or unक्रमeseen circumstances. After the change from opt-in to
 * opt-out has baked sufficiently, this parameter should probably be हटाओd
 * entirely.
 */
अटल bool s0ix_logging_enable = true;
module_param(s0ix_logging_enable, bool, 0600);

अटल काष्ठा gsmi_buf *gsmi_buf_alloc(व्योम)
अणु
	काष्ठा gsmi_buf *smibuf;

	smibuf = kzalloc(माप(*smibuf), GFP_KERNEL);
	अगर (!smibuf) अणु
		prपूर्णांकk(KERN_ERR "gsmi: out of memory\n");
		वापस शून्य;
	पूर्ण

	/* allocate buffer in 32bit address space */
	smibuf->start = kmem_cache_alloc(gsmi_dev.mem_pool, GFP_KERNEL);
	अगर (!smibuf->start) अणु
		prपूर्णांकk(KERN_ERR "gsmi: failed to allocate name buffer\n");
		kमुक्त(smibuf);
		वापस शून्य;
	पूर्ण

	/* fill in the buffer handle */
	smibuf->length = GSMI_BUF_SIZE;
	smibuf->address = (u32)virt_to_phys(smibuf->start);

	वापस smibuf;
पूर्ण

अटल व्योम gsmi_buf_मुक्त(काष्ठा gsmi_buf *smibuf)
अणु
	अगर (smibuf) अणु
		अगर (smibuf->start)
			kmem_cache_मुक्त(gsmi_dev.mem_pool, smibuf->start);
		kमुक्त(smibuf);
	पूर्ण
पूर्ण

/*
 * Make a call to gsmi func(sub).  GSMI error codes are translated to
 * in-kernel त्रुटि_संs (0 on success, -ERRNO on error).
 */
अटल पूर्णांक gsmi_exec(u8 func, u8 sub)
अणु
	u16 cmd = (sub << 8) | func;
	u16 result = 0;
	पूर्णांक rc = 0;

	/*
	 * AH  : Subfunction number
	 * AL  : Function number
	 * EBX : Parameter block address
	 * DX  : SMI command port
	 *
	 * Three protocols here. See also the comment in gsmi_init().
	 */
	अगर (gsmi_dev.handshake_type == GSMI_HANDSHAKE_CF) अणु
		/*
		 * If handshake_type == HANDSHAKE_CF then set CF on the
		 * way in and रुको क्रम the handler to clear it; this aव्योमs
		 * corrupting रेजिस्टर state on those chipsets which have
		 * a delay between writing the SMI trigger रेजिस्टर and
		 * entering SMM.
		 */
		यंत्र अस्थिर (
			"stc\n"
			"outb %%al, %%dx\n"
		"1:      jc 1b\n"
			: "=a" (result)
			: "0" (cmd),
			  "d" (gsmi_dev.smi_cmd),
			  "b" (gsmi_dev.param_buf->address)
			: "memory", "cc"
		);
	पूर्ण अन्यथा अगर (gsmi_dev.handshake_type == GSMI_HANDSHAKE_SPIN) अणु
		/*
		 * If handshake_type == HANDSHAKE_SPIN we spin a
		 * hundred-ish usecs to ensure the SMI has triggered.
		 */
		यंत्र अस्थिर (
			"outb %%al, %%dx\n"
		"1:      loop 1b\n"
			: "=a" (result)
			: "0" (cmd),
			  "d" (gsmi_dev.smi_cmd),
			  "b" (gsmi_dev.param_buf->address),
			  "c" (spincount)
			: "memory", "cc"
		);
	पूर्ण अन्यथा अणु
		/*
		 * If handshake_type == HANDSHAKE_NONE we करो nothing;
		 * either we करोn't need to or it's legacy firmware that
		 * करोesn't understand the CF protocol.
		 */
		यंत्र अस्थिर (
			"outb %%al, %%dx\n\t"
			: "=a" (result)
			: "0" (cmd),
			  "d" (gsmi_dev.smi_cmd),
			  "b" (gsmi_dev.param_buf->address)
			: "memory", "cc"
		);
	पूर्ण

	/* check वापस code from SMI handler */
	चयन (result) अणु
	हाल GSMI_SUCCESS:
		अवरोध;
	हाल GSMI_VAR_NOT_FOUND:
		/* not really an error, but let the caller know */
		rc = 1;
		अवरोध;
	हाल GSMI_INVALID_PARAMETER:
		prपूर्णांकk(KERN_ERR "gsmi: exec 0x%04x: Invalid parameter\n", cmd);
		rc = -EINVAL;
		अवरोध;
	हाल GSMI_BUFFER_TOO_SMALL:
		prपूर्णांकk(KERN_ERR "gsmi: exec 0x%04x: Buffer too small\n", cmd);
		rc = -ENOMEM;
		अवरोध;
	हाल GSMI_UNSUPPORTED:
	हाल GSMI_UNSUPPORTED2:
		अगर (sub != GSMI_CMD_HANDSHAKE_TYPE)
			prपूर्णांकk(KERN_ERR "gsmi: exec 0x%04x: Not supported\n",
			       cmd);
		rc = -ENOSYS;
		अवरोध;
	हाल GSMI_NOT_READY:
		prपूर्णांकk(KERN_ERR "gsmi: exec 0x%04x: Not ready\n", cmd);
		rc = -EBUSY;
		अवरोध;
	हाल GSMI_DEVICE_ERROR:
		prपूर्णांकk(KERN_ERR "gsmi: exec 0x%04x: Device error\n", cmd);
		rc = -EFAULT;
		अवरोध;
	हाल GSMI_NOT_FOUND:
		prपूर्णांकk(KERN_ERR "gsmi: exec 0x%04x: Data not found\n", cmd);
		rc = -ENOENT;
		अवरोध;
	हाल GSMI_LOG_FULL:
		prपूर्णांकk(KERN_ERR "gsmi: exec 0x%04x: Log full\n", cmd);
		rc = -ENOSPC;
		अवरोध;
	हाल GSMI_HANDSHAKE_CF:
	हाल GSMI_HANDSHAKE_SPIN:
	हाल GSMI_HANDSHAKE_NONE:
		rc = result;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "gsmi: exec 0x%04x: Unknown error 0x%04x\n",
		       cmd, result);
		rc = -ENXIO;
	पूर्ण

	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_EFI

अटल काष्ठा efivars efivars;

अटल efi_status_t gsmi_get_variable(efi_अक्षर16_t *name,
				      efi_guid_t *venकरोr, u32 *attr,
				      अचिन्हित दीर्घ *data_size,
				      व्योम *data)
अणु
	काष्ठा gsmi_nvram_var_param param = अणु
		.name_ptr = gsmi_dev.name_buf->address,
		.data_ptr = gsmi_dev.data_buf->address,
		.data_len = (u32)*data_size,
	पूर्ण;
	efi_status_t ret = EFI_SUCCESS;
	अचिन्हित दीर्घ flags;
	माप_प्रकार name_len = ucs2_strnlen(name, GSMI_BUF_SIZE / 2);
	पूर्णांक rc;

	अगर (name_len >= GSMI_BUF_SIZE / 2)
		वापस EFI_BAD_BUFFER_SIZE;

	spin_lock_irqsave(&gsmi_dev.lock, flags);

	/* Venकरोr guid */
	स_नकल(&param.guid, venकरोr, माप(param.guid));

	/* variable name, alपढ़ोy in UTF-16 */
	स_रखो(gsmi_dev.name_buf->start, 0, gsmi_dev.name_buf->length);
	स_नकल(gsmi_dev.name_buf->start, name, name_len * 2);

	/* data poपूर्णांकer */
	स_रखो(gsmi_dev.data_buf->start, 0, gsmi_dev.data_buf->length);

	/* parameter buffer */
	स_रखो(gsmi_dev.param_buf->start, 0, gsmi_dev.param_buf->length);
	स_नकल(gsmi_dev.param_buf->start, &param, माप(param));

	rc = gsmi_exec(GSMI_CALLBACK, GSMI_CMD_GET_NVRAM_VAR);
	अगर (rc < 0) अणु
		prपूर्णांकk(KERN_ERR "gsmi: Get Variable failed\n");
		ret = EFI_LOAD_ERROR;
	पूर्ण अन्यथा अगर (rc == 1) अणु
		/* variable was not found */
		ret = EFI_NOT_FOUND;
	पूर्ण अन्यथा अणु
		/* Get the arguments back */
		स_नकल(&param, gsmi_dev.param_buf->start, माप(param));

		/* The size reported is the min of all of our buffers */
		*data_size = min_t(अचिन्हित दीर्घ, *data_size,
						gsmi_dev.data_buf->length);
		*data_size = min_t(अचिन्हित दीर्घ, *data_size, param.data_len);

		/* Copy data back to वापस buffer. */
		स_नकल(data, gsmi_dev.data_buf->start, *data_size);

		/* All variables are have the following attributes */
		*attr = EFI_VARIABLE_NON_VOLATILE |
			EFI_VARIABLE_BOOTSERVICE_ACCESS |
			EFI_VARIABLE_RUNTIME_ACCESS;
	पूर्ण

	spin_unlock_irqrestore(&gsmi_dev.lock, flags);

	वापस ret;
पूर्ण

अटल efi_status_t gsmi_get_next_variable(अचिन्हित दीर्घ *name_size,
					   efi_अक्षर16_t *name,
					   efi_guid_t *venकरोr)
अणु
	काष्ठा gsmi_get_next_var_param param = अणु
		.name_ptr = gsmi_dev.name_buf->address,
		.name_len = gsmi_dev.name_buf->length,
	पूर्ण;
	efi_status_t ret = EFI_SUCCESS;
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;

	/* For the moment, only support buffers that exactly match in size */
	अगर (*name_size != GSMI_BUF_SIZE)
		वापस EFI_BAD_BUFFER_SIZE;

	/* Let's make sure the thing is at least null-terminated */
	अगर (ucs2_strnlen(name, GSMI_BUF_SIZE / 2) == GSMI_BUF_SIZE / 2)
		वापस EFI_INVALID_PARAMETER;

	spin_lock_irqsave(&gsmi_dev.lock, flags);

	/* guid */
	स_नकल(&param.guid, venकरोr, माप(param.guid));

	/* variable name, alपढ़ोy in UTF-16 */
	स_नकल(gsmi_dev.name_buf->start, name, *name_size);

	/* parameter buffer */
	स_रखो(gsmi_dev.param_buf->start, 0, gsmi_dev.param_buf->length);
	स_नकल(gsmi_dev.param_buf->start, &param, माप(param));

	rc = gsmi_exec(GSMI_CALLBACK, GSMI_CMD_GET_NEXT_VAR);
	अगर (rc < 0) अणु
		prपूर्णांकk(KERN_ERR "gsmi: Get Next Variable Name failed\n");
		ret = EFI_LOAD_ERROR;
	पूर्ण अन्यथा अगर (rc == 1) अणु
		/* variable not found -- end of list */
		ret = EFI_NOT_FOUND;
	पूर्ण अन्यथा अणु
		/* copy variable data back to वापस buffer */
		स_नकल(&param, gsmi_dev.param_buf->start, माप(param));

		/* Copy the name back */
		स_नकल(name, gsmi_dev.name_buf->start, GSMI_BUF_SIZE);
		*name_size = ucs2_strnlen(name, GSMI_BUF_SIZE / 2) * 2;

		/* copy guid to वापस buffer */
		स_नकल(venकरोr, &param.guid, माप(param.guid));
		ret = EFI_SUCCESS;
	पूर्ण

	spin_unlock_irqrestore(&gsmi_dev.lock, flags);

	वापस ret;
पूर्ण

अटल efi_status_t gsmi_set_variable(efi_अक्षर16_t *name,
				      efi_guid_t *venकरोr,
				      u32 attr,
				      अचिन्हित दीर्घ data_size,
				      व्योम *data)
अणु
	काष्ठा gsmi_nvram_var_param param = अणु
		.name_ptr = gsmi_dev.name_buf->address,
		.data_ptr = gsmi_dev.data_buf->address,
		.data_len = (u32)data_size,
		.attributes = EFI_VARIABLE_NON_VOLATILE |
			      EFI_VARIABLE_BOOTSERVICE_ACCESS |
			      EFI_VARIABLE_RUNTIME_ACCESS,
	पूर्ण;
	माप_प्रकार name_len = ucs2_strnlen(name, GSMI_BUF_SIZE / 2);
	efi_status_t ret = EFI_SUCCESS;
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;

	अगर (name_len >= GSMI_BUF_SIZE / 2)
		वापस EFI_BAD_BUFFER_SIZE;

	spin_lock_irqsave(&gsmi_dev.lock, flags);

	/* guid */
	स_नकल(&param.guid, venकरोr, माप(param.guid));

	/* variable name, alपढ़ोy in UTF-16 */
	स_रखो(gsmi_dev.name_buf->start, 0, gsmi_dev.name_buf->length);
	स_नकल(gsmi_dev.name_buf->start, name, name_len * 2);

	/* data poपूर्णांकer */
	स_रखो(gsmi_dev.data_buf->start, 0, gsmi_dev.data_buf->length);
	स_नकल(gsmi_dev.data_buf->start, data, data_size);

	/* parameter buffer */
	स_रखो(gsmi_dev.param_buf->start, 0, gsmi_dev.param_buf->length);
	स_नकल(gsmi_dev.param_buf->start, &param, माप(param));

	rc = gsmi_exec(GSMI_CALLBACK, GSMI_CMD_SET_NVRAM_VAR);
	अगर (rc < 0) अणु
		prपूर्णांकk(KERN_ERR "gsmi: Set Variable failed\n");
		ret = EFI_INVALID_PARAMETER;
	पूर्ण

	spin_unlock_irqrestore(&gsmi_dev.lock, flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा efivar_operations efivar_ops = अणु
	.get_variable = gsmi_get_variable,
	.set_variable = gsmi_set_variable,
	.get_next_variable = gsmi_get_next_variable,
पूर्ण;

#पूर्ण_अगर /* CONFIG_EFI */

अटल sमाप_प्रकार eventlog_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
			       काष्ठा bin_attribute *bin_attr,
			       अक्षर *buf, loff_t pos, माप_प्रकार count)
अणु
	काष्ठा gsmi_set_eventlog_param param = अणु
		.data_ptr = gsmi_dev.data_buf->address,
	पूर्ण;
	पूर्णांक rc = 0;
	अचिन्हित दीर्घ flags;

	/* Pull the type out */
	अगर (count < माप(u32))
		वापस -EINVAL;
	param.type = *(u32 *)buf;
	buf += माप(u32);

	/* The reमुख्यing buffer is the data payload */
	अगर ((count - माप(u32)) > gsmi_dev.data_buf->length)
		वापस -EINVAL;
	param.data_len = count - माप(u32);

	spin_lock_irqsave(&gsmi_dev.lock, flags);

	/* data poपूर्णांकer */
	स_रखो(gsmi_dev.data_buf->start, 0, gsmi_dev.data_buf->length);
	स_नकल(gsmi_dev.data_buf->start, buf, param.data_len);

	/* parameter buffer */
	स_रखो(gsmi_dev.param_buf->start, 0, gsmi_dev.param_buf->length);
	स_नकल(gsmi_dev.param_buf->start, &param, माप(param));

	rc = gsmi_exec(GSMI_CALLBACK, GSMI_CMD_SET_EVENT_LOG);
	अगर (rc < 0)
		prपूर्णांकk(KERN_ERR "gsmi: Set Event Log failed\n");

	spin_unlock_irqrestore(&gsmi_dev.lock, flags);

	वापस (rc == 0) ? count : rc;

पूर्ण

अटल काष्ठा bin_attribute eventlog_bin_attr = अणु
	.attr = अणु.name = "append_to_eventlog", .mode = 0200पूर्ण,
	.ग_लिखो = eventlog_ग_लिखो,
पूर्ण;

अटल sमाप_प्रकार gsmi_clear_eventlog_store(काष्ठा kobject *kobj,
					 काष्ठा kobj_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ val;
	काष्ठा अणु
		u32 percentage;
		u32 data_type;
	पूर्ण param;

	rc = kम_से_अदीर्घ(buf, 0, &val);
	अगर (rc)
		वापस rc;

	/*
	 * Value entered is a percentage, 0 through 100, anything अन्यथा
	 * is invalid.
	 */
	अगर (val > 100)
		वापस -EINVAL;

	/* data_type here selects the smbios event log. */
	param.percentage = val;
	param.data_type = 0;

	spin_lock_irqsave(&gsmi_dev.lock, flags);

	/* parameter buffer */
	स_रखो(gsmi_dev.param_buf->start, 0, gsmi_dev.param_buf->length);
	स_नकल(gsmi_dev.param_buf->start, &param, माप(param));

	rc = gsmi_exec(GSMI_CALLBACK, GSMI_CMD_CLEAR_EVENT_LOG);

	spin_unlock_irqrestore(&gsmi_dev.lock, flags);

	अगर (rc)
		वापस rc;
	वापस count;
पूर्ण

अटल काष्ठा kobj_attribute gsmi_clear_eventlog_attr = अणु
	.attr = अणु.name = "clear_eventlog", .mode = 0200पूर्ण,
	.store = gsmi_clear_eventlog_store,
पूर्ण;

अटल sमाप_प्रकार gsmi_clear_config_store(काष्ठा kobject *kobj,
				       काष्ठा kobj_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gsmi_dev.lock, flags);

	/* clear parameter buffer */
	स_रखो(gsmi_dev.param_buf->start, 0, gsmi_dev.param_buf->length);

	rc = gsmi_exec(GSMI_CALLBACK, GSMI_CMD_CLEAR_CONFIG);

	spin_unlock_irqrestore(&gsmi_dev.lock, flags);

	अगर (rc)
		वापस rc;
	वापस count;
पूर्ण

अटल काष्ठा kobj_attribute gsmi_clear_config_attr = अणु
	.attr = अणु.name = "clear_config", .mode = 0200पूर्ण,
	.store = gsmi_clear_config_store,
पूर्ण;

अटल स्थिर काष्ठा attribute *gsmi_attrs[] = अणु
	&gsmi_clear_config_attr.attr,
	&gsmi_clear_eventlog_attr.attr,
	शून्य,
पूर्ण;

अटल पूर्णांक gsmi_shutकरोwn_reason(पूर्णांक reason)
अणु
	काष्ठा gsmi_log_entry_type_1 entry = अणु
		.type     = GSMI_LOG_ENTRY_TYPE_KERNEL,
		.instance = reason,
	पूर्ण;
	काष्ठा gsmi_set_eventlog_param param = अणु
		.data_len = माप(entry),
		.type     = 1,
	पूर्ण;
	अटल पूर्णांक saved_reason;
	पूर्णांक rc = 0;
	अचिन्हित दीर्घ flags;

	/* aव्योम duplicate entries in the log */
	अगर (saved_reason & (1 << reason))
		वापस 0;

	spin_lock_irqsave(&gsmi_dev.lock, flags);

	saved_reason |= (1 << reason);

	/* data poपूर्णांकer */
	स_रखो(gsmi_dev.data_buf->start, 0, gsmi_dev.data_buf->length);
	स_नकल(gsmi_dev.data_buf->start, &entry, माप(entry));

	/* parameter buffer */
	param.data_ptr = gsmi_dev.data_buf->address;
	स_रखो(gsmi_dev.param_buf->start, 0, gsmi_dev.param_buf->length);
	स_नकल(gsmi_dev.param_buf->start, &param, माप(param));

	rc = gsmi_exec(GSMI_CALLBACK, GSMI_CMD_SET_EVENT_LOG);

	spin_unlock_irqrestore(&gsmi_dev.lock, flags);

	अगर (rc < 0)
		prपूर्णांकk(KERN_ERR "gsmi: Log Shutdown Reason failed\n");
	अन्यथा
		prपूर्णांकk(KERN_EMERG "gsmi: Log Shutdown Reason 0x%02x\n",
		       reason);

	वापस rc;
पूर्ण

अटल पूर्णांक gsmi_reboot_callback(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ reason, व्योम *arg)
अणु
	gsmi_shutकरोwn_reason(GSMI_SHUTDOWN_CLEAN);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block gsmi_reboot_notअगरier = अणु
	.notअगरier_call = gsmi_reboot_callback
पूर्ण;

अटल पूर्णांक gsmi_die_callback(काष्ठा notअगरier_block *nb,
			     अचिन्हित दीर्घ reason, व्योम *arg)
अणु
	अगर (reason == DIE_OOPS)
		gsmi_shutकरोwn_reason(GSMI_SHUTDOWN_OOPS);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block gsmi_die_notअगरier = अणु
	.notअगरier_call = gsmi_die_callback
पूर्ण;

अटल पूर्णांक gsmi_panic_callback(काष्ठा notअगरier_block *nb,
			       अचिन्हित दीर्घ reason, व्योम *arg)
अणु
	gsmi_shutकरोwn_reason(GSMI_SHUTDOWN_PANIC);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block gsmi_panic_notअगरier = अणु
	.notअगरier_call = gsmi_panic_callback,
पूर्ण;

/*
 * This hash function was blatantly copied from include/linux/hash.h.
 * It is used by this driver to obfuscate a board name that requires a
 * quirk within this driver.
 *
 * Please करो not हटाओ this copy of the function as any changes to the
 * global utility hash_64() function would अवरोध this driver's ability
 * to identअगरy a board and provide the appropriate quirk -- mikew@google.com
 */
अटल u64 __init local_hash_64(u64 val, अचिन्हित bits)
अणु
	u64 hash = val;

	/*  Sigh, gcc can't optimise this alone like it करोes क्रम 32 bits. */
	u64 n = hash;
	n <<= 18;
	hash -= n;
	n <<= 33;
	hash -= n;
	n <<= 3;
	hash += n;
	n <<= 3;
	hash -= n;
	n <<= 4;
	hash += n;
	n <<= 2;
	hash += n;

	/* High bits are more अक्रमom, so use them. */
	वापस hash >> (64 - bits);
पूर्ण

अटल u32 __init hash_oem_table_id(अक्षर s[8])
अणु
	u64 input;
	स_नकल(&input, s, 8);
	वापस local_hash_64(input, 32);
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id gsmi_dmi_table[] __initस्थिर = अणु
	अणु
		.ident = "Google Board",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Google, Inc."),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Coreboot Firmware",
		.matches = अणु
			DMI_MATCH(DMI_BIOS_VENDOR, "coreboot"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(dmi, gsmi_dmi_table);

अटल __init पूर्णांक gsmi_प्रणाली_valid(व्योम)
अणु
	u32 hash;
	u16 cmd, result;

	अगर (!dmi_check_प्रणाली(gsmi_dmi_table))
		वापस -ENODEV;

	/*
	 * Only newer firmware supports the gsmi पूर्णांकerface.  All older
	 * firmware that didn't support this पूर्णांकerface used to plug the
	 * table name in the first four bytes of the oem_table_id field.
	 * Newer firmware करोesn't करो that though, so use that as the
	 * discriminant factor.  We have to करो this in order to
	 * whitewash our board names out of the खुला driver.
	 */
	अगर (!म_भेदन(acpi_gbl_FADT.header.oem_table_id, "FACP", 4)) अणु
		prपूर्णांकk(KERN_INFO "gsmi: Board is too old\n");
		वापस -ENODEV;
	पूर्ण

	/* Disable on board with 1.0 BIOS due to Google bug 2602657 */
	hash = hash_oem_table_id(acpi_gbl_FADT.header.oem_table_id);
	अगर (hash == QUIRKY_BOARD_HASH) अणु
		स्थिर अक्षर *bios_ver = dmi_get_प्रणाली_info(DMI_BIOS_VERSION);
		अगर (म_भेदन(bios_ver, "1.0", 3) == 0) अणु
			pr_info("gsmi: disabled on this board's BIOS %s\n",
				bios_ver);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/* check क्रम valid SMI command port in ACPI FADT */
	अगर (acpi_gbl_FADT.smi_command == 0) अणु
		pr_info("gsmi: missing smi_command\n");
		वापस -ENODEV;
	पूर्ण

	/* Test the smihandler with a bogus command. If it leaves the
	 * calling argument in %ax untouched, there is no handler क्रम
	 * GSMI commands.
	 */
	cmd = GSMI_CALLBACK | GSMI_CMD_RESERVED << 8;
	यंत्र अस्थिर (
		"outb %%al, %%dx\n\t"
		: "=a" (result)
		: "0" (cmd),
		  "d" (acpi_gbl_FADT.smi_command)
		: "memory", "cc"
		);
	अगर (cmd == result) अणु
		pr_info("gsmi: no gsmi handler in firmware\n");
		वापस -ENODEV;
	पूर्ण

	/* Found */
	वापस 0;
पूर्ण

अटल काष्ठा kobject *gsmi_kobj;

अटल स्थिर काष्ठा platक्रमm_device_info gsmi_dev_info = अणु
	.name		= "gsmi",
	.id		= -1,
	/* SMI callbacks require 32bit addresses */
	.dma_mask	= DMA_BIT_MASK(32),
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल व्योम gsmi_log_s0ix_info(u8 cmd)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * If platक्रमm has not enabled S0ix logging, then no action is
	 * necessary.
	 */
	अगर (!s0ix_logging_enable)
		वापस;

	spin_lock_irqsave(&gsmi_dev.lock, flags);

	स_रखो(gsmi_dev.param_buf->start, 0, gsmi_dev.param_buf->length);

	gsmi_exec(GSMI_CALLBACK, cmd);

	spin_unlock_irqrestore(&gsmi_dev.lock, flags);
पूर्ण

अटल पूर्णांक gsmi_log_s0ix_suspend(काष्ठा device *dev)
अणु
	/*
	 * If प्रणाली is not suspending via firmware using the standard ACPI Sx
	 * types, then make a GSMI call to log the suspend info.
	 */
	अगर (!pm_suspend_via_firmware())
		gsmi_log_s0ix_info(GSMI_CMD_LOG_S0IX_SUSPEND);

	/*
	 * Always वापस success, since we करो not want suspend
	 * to fail just because of logging failure.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक gsmi_log_s0ix_resume(काष्ठा device *dev)
अणु
	/*
	 * If प्रणाली did not resume via firmware, then make a GSMI call to log
	 * the resume info and wake source.
	 */
	अगर (!pm_resume_via_firmware())
		gsmi_log_s0ix_info(GSMI_CMD_LOG_S0IX_RESUME);

	/*
	 * Always वापस success, since we करो not want resume
	 * to fail just because of logging failure.
	 */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops gsmi_pm_ops = अणु
	.suspend_noirq = gsmi_log_s0ix_suspend,
	.resume_noirq = gsmi_log_s0ix_resume,
पूर्ण;

अटल पूर्णांक gsmi_platक्रमm_driver_probe(काष्ठा platक्रमm_device *dev)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver gsmi_driver_info = अणु
	.driver = अणु
		.name = "gsmi",
		.pm = &gsmi_pm_ops,
	पूर्ण,
	.probe = gsmi_platक्रमm_driver_probe,
पूर्ण;
#पूर्ण_अगर

अटल __init पूर्णांक gsmi_init(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = gsmi_प्रणाली_valid();
	अगर (ret)
		वापस ret;

	gsmi_dev.smi_cmd = acpi_gbl_FADT.smi_command;

#अगर_घोषित CONFIG_PM
	ret = platक्रमm_driver_रेजिस्टर(&gsmi_driver_info);
	अगर (unlikely(ret)) अणु
		prपूर्णांकk(KERN_ERR "gsmi: unable to register platform driver\n");
		वापस ret;
	पूर्ण
#पूर्ण_अगर

	/* रेजिस्टर device */
	gsmi_dev.pdev = platक्रमm_device_रेजिस्टर_full(&gsmi_dev_info);
	अगर (IS_ERR(gsmi_dev.pdev)) अणु
		prपूर्णांकk(KERN_ERR "gsmi: unable to register platform device\n");
		वापस PTR_ERR(gsmi_dev.pdev);
	पूर्ण

	/* SMI access needs to be serialized */
	spin_lock_init(&gsmi_dev.lock);

	ret = -ENOMEM;

	/*
	 * SLAB cache is created using SLAB_CACHE_DMA32 to ensure that the
	 * allocations क्रम gsmi_buf come from the DMA32 memory zone. These
	 * buffers have nothing to करो with DMA. They are required क्रम
	 * communication with firmware executing in SMI mode which can only
	 * access the bottom 4GiB of physical memory. Since DMA32 memory zone
	 * guarantees allocation under the 4GiB boundary, this driver creates
	 * a SLAB cache with SLAB_CACHE_DMA32 flag.
	 */
	gsmi_dev.mem_pool = kmem_cache_create("gsmi", GSMI_BUF_SIZE,
					      GSMI_BUF_ALIGN,
					      SLAB_CACHE_DMA32, शून्य);
	अगर (!gsmi_dev.mem_pool)
		जाओ out_err;

	/*
	 * pre-allocate buffers because someबार we are called when
	 * this is not feasible: oops, panic, die, mce, etc
	 */
	gsmi_dev.name_buf = gsmi_buf_alloc();
	अगर (!gsmi_dev.name_buf) अणु
		prपूर्णांकk(KERN_ERR "gsmi: failed to allocate name buffer\n");
		जाओ out_err;
	पूर्ण

	gsmi_dev.data_buf = gsmi_buf_alloc();
	अगर (!gsmi_dev.data_buf) अणु
		prपूर्णांकk(KERN_ERR "gsmi: failed to allocate data buffer\n");
		जाओ out_err;
	पूर्ण

	gsmi_dev.param_buf = gsmi_buf_alloc();
	अगर (!gsmi_dev.param_buf) अणु
		prपूर्णांकk(KERN_ERR "gsmi: failed to allocate param buffer\n");
		जाओ out_err;
	पूर्ण

	/*
	 * Determine type of handshake used to serialize the SMI
	 * entry. See also gsmi_exec().
	 *
	 * There's a "behavior" present on some chipsets where writing the
	 * SMI trigger रेजिस्टर in the southbridge करोesn't result in an
	 * immediate SMI. Rather, the processor can execute "a few" more
	 * inकाष्ठाions beक्रमe the SMI takes effect. To ensure synchronous
	 * behavior, implement a handshake between the kernel driver and the
	 * firmware handler to spin until released. This ioctl determines
	 * the type of handshake.
	 *
	 * NONE: The firmware handler करोes not implement any
	 * handshake. Either it करोesn't need to, or it's legacy firmware
	 * that करोesn't know it needs to and never will.
	 *
	 * CF: The firmware handler will clear the CF in the saved
	 * state beक्रमe वापसing. The driver may set the CF and test क्रम
	 * it to clear beक्रमe proceeding.
	 *
	 * SPIN: The firmware handler करोes not implement any handshake
	 * but the driver should spin क्रम a hundred or so microseconds
	 * to ensure the SMI has triggered.
	 *
	 * Finally, the handler will वापस -ENOSYS अगर
	 * GSMI_CMD_HANDSHAKE_TYPE is unimplemented, which implies
	 * HANDSHAKE_NONE.
	 */
	spin_lock_irqsave(&gsmi_dev.lock, flags);
	gsmi_dev.handshake_type = GSMI_HANDSHAKE_SPIN;
	gsmi_dev.handshake_type =
	    gsmi_exec(GSMI_CALLBACK, GSMI_CMD_HANDSHAKE_TYPE);
	अगर (gsmi_dev.handshake_type == -ENOSYS)
		gsmi_dev.handshake_type = GSMI_HANDSHAKE_NONE;
	spin_unlock_irqrestore(&gsmi_dev.lock, flags);

	/* Remove and clean up gsmi अगर the handshake could not complete. */
	अगर (gsmi_dev.handshake_type == -ENXIO) अणु
		prपूर्णांकk(KERN_INFO "gsmi version " DRIVER_VERSION
		       " failed to load\n");
		ret = -ENODEV;
		जाओ out_err;
	पूर्ण

	/* Register in the firmware directory */
	ret = -ENOMEM;
	gsmi_kobj = kobject_create_and_add("gsmi", firmware_kobj);
	अगर (!gsmi_kobj) अणु
		prपूर्णांकk(KERN_INFO "gsmi: Failed to create firmware kobj\n");
		जाओ out_err;
	पूर्ण

	/* Setup eventlog access */
	ret = sysfs_create_bin_file(gsmi_kobj, &eventlog_bin_attr);
	अगर (ret) अणु
		prपूर्णांकk(KERN_INFO "gsmi: Failed to setup eventlog");
		जाओ out_err;
	पूर्ण

	/* Other attributes */
	ret = sysfs_create_files(gsmi_kobj, gsmi_attrs);
	अगर (ret) अणु
		prपूर्णांकk(KERN_INFO "gsmi: Failed to add attrs");
		जाओ out_हटाओ_bin_file;
	पूर्ण

#अगर_घोषित CONFIG_EFI
	ret = efivars_रेजिस्टर(&efivars, &efivar_ops, gsmi_kobj);
	अगर (ret) अणु
		prपूर्णांकk(KERN_INFO "gsmi: Failed to register efivars\n");
		sysfs_हटाओ_files(gsmi_kobj, gsmi_attrs);
		जाओ out_हटाओ_bin_file;
	पूर्ण
#पूर्ण_अगर

	रेजिस्टर_reboot_notअगरier(&gsmi_reboot_notअगरier);
	रेजिस्टर_die_notअगरier(&gsmi_die_notअगरier);
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
				       &gsmi_panic_notअगरier);

	prपूर्णांकk(KERN_INFO "gsmi version " DRIVER_VERSION " loaded\n");

	वापस 0;

out_हटाओ_bin_file:
	sysfs_हटाओ_bin_file(gsmi_kobj, &eventlog_bin_attr);
out_err:
	kobject_put(gsmi_kobj);
	gsmi_buf_मुक्त(gsmi_dev.param_buf);
	gsmi_buf_मुक्त(gsmi_dev.data_buf);
	gsmi_buf_मुक्त(gsmi_dev.name_buf);
	kmem_cache_destroy(gsmi_dev.mem_pool);
	platक्रमm_device_unरेजिस्टर(gsmi_dev.pdev);
	pr_info("gsmi: failed to load: %d\n", ret);
#अगर_घोषित CONFIG_PM
	platक्रमm_driver_unरेजिस्टर(&gsmi_driver_info);
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल व्योम __निकास gsmi_निकास(व्योम)
अणु
	unरेजिस्टर_reboot_notअगरier(&gsmi_reboot_notअगरier);
	unरेजिस्टर_die_notअगरier(&gsmi_die_notअगरier);
	atomic_notअगरier_chain_unरेजिस्टर(&panic_notअगरier_list,
					 &gsmi_panic_notअगरier);
#अगर_घोषित CONFIG_EFI
	efivars_unरेजिस्टर(&efivars);
#पूर्ण_अगर

	sysfs_हटाओ_files(gsmi_kobj, gsmi_attrs);
	sysfs_हटाओ_bin_file(gsmi_kobj, &eventlog_bin_attr);
	kobject_put(gsmi_kobj);
	gsmi_buf_मुक्त(gsmi_dev.param_buf);
	gsmi_buf_मुक्त(gsmi_dev.data_buf);
	gsmi_buf_मुक्त(gsmi_dev.name_buf);
	kmem_cache_destroy(gsmi_dev.mem_pool);
	platक्रमm_device_unरेजिस्टर(gsmi_dev.pdev);
#अगर_घोषित CONFIG_PM
	platक्रमm_driver_unरेजिस्टर(&gsmi_driver_info);
#पूर्ण_अगर
पूर्ण

module_init(gsmi_init);
module_निकास(gsmi_निकास);

MODULE_AUTHOR("Google, Inc.");
MODULE_LICENSE("GPL");
