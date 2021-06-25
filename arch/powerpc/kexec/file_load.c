<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * घातerpc code to implement the kexec_file_load syscall
 *
 * Copyright (C) 2004  Adam Litke (agl@us.ibm.com)
 * Copyright (C) 2004  IBM Corp.
 * Copyright (C) 2004,2005  Milton D Miller II, IBM Corporation
 * Copyright (C) 2005  R Sharada (sharada@in.ibm.com)
 * Copyright (C) 2006  Mohan Kumar M (mohan@in.ibm.com)
 * Copyright (C) 2016  IBM Corporation
 *
 * Based on kexec-tools' kexec-elf-ppc64.c, fs2dt.c.
 * Heavily modअगरied क्रम the kernel by
 * Thiago Jung Bauermann <bauerman@linux.vnet.ibm.com>.
 */

#समावेश <linux/slab.h>
#समावेश <linux/kexec.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/libfdt.h>
#समावेश <यंत्र/setup.h>

#घोषणा SLAVE_CODE_SIZE		256	/* First 0x100 bytes */

/**
 * setup_kdump_cmdline - Prepend "elfcorehdr=<addr> " to command line
 *                       of kdump kernel क्रम exporting the core.
 * @image:               Kexec image
 * @cmdline:             Command line parameters to update.
 * @cmdline_len:         Length of the cmdline parameters.
 *
 * kdump segment must be setup beक्रमe calling this function.
 *
 * Returns new cmdline buffer क्रम kdump kernel on success, शून्य otherwise.
 */
अक्षर *setup_kdump_cmdline(काष्ठा kimage *image, अक्षर *cmdline,
			  अचिन्हित दीर्घ cmdline_len)
अणु
	पूर्णांक elfcorehdr_म_माप;
	अक्षर *cmdline_ptr;

	cmdline_ptr = kzalloc(COMMAND_LINE_SIZE, GFP_KERNEL);
	अगर (!cmdline_ptr)
		वापस शून्य;

	elfcorehdr_म_माप = प्र_लिखो(cmdline_ptr, "elfcorehdr=0x%lx ",
				    image->elf_load_addr);

	अगर (elfcorehdr_म_माप + cmdline_len > COMMAND_LINE_SIZE) अणु
		pr_err("Appending elfcorehdr=<addr> exceeds cmdline size\n");
		kमुक्त(cmdline_ptr);
		वापस शून्य;
	पूर्ण

	स_नकल(cmdline_ptr + elfcorehdr_म_माप, cmdline, cmdline_len);
	// Ensure it's nul terminated
	cmdline_ptr[COMMAND_LINE_SIZE - 1] = '\0';
	वापस cmdline_ptr;
पूर्ण

/**
 * setup_purgatory - initialize the purgatory's global variables
 * @image:		kexec image.
 * @slave_code:		Slave code क्रम the purgatory.
 * @fdt:		Flattened device tree क्रम the next kernel.
 * @kernel_load_addr:	Address where the kernel is loaded.
 * @fdt_load_addr:	Address where the flattened device tree is loaded.
 *
 * Return: 0 on success, or negative त्रुटि_सं on error.
 */
पूर्णांक setup_purgatory(काष्ठा kimage *image, स्थिर व्योम *slave_code,
		    स्थिर व्योम *fdt, अचिन्हित दीर्घ kernel_load_addr,
		    अचिन्हित दीर्घ fdt_load_addr)
अणु
	अचिन्हित पूर्णांक *slave_code_buf, master_entry;
	पूर्णांक ret;

	slave_code_buf = kदो_स्मृति(SLAVE_CODE_SIZE, GFP_KERNEL);
	अगर (!slave_code_buf)
		वापस -ENOMEM;

	/* Get the slave code from the new kernel and put it in purgatory. */
	ret = kexec_purgatory_get_set_symbol(image, "purgatory_start",
					     slave_code_buf, SLAVE_CODE_SIZE,
					     true);
	अगर (ret) अणु
		kमुक्त(slave_code_buf);
		वापस ret;
	पूर्ण

	master_entry = slave_code_buf[0];
	स_नकल(slave_code_buf, slave_code, SLAVE_CODE_SIZE);
	slave_code_buf[0] = master_entry;
	ret = kexec_purgatory_get_set_symbol(image, "purgatory_start",
					     slave_code_buf, SLAVE_CODE_SIZE,
					     false);
	kमुक्त(slave_code_buf);

	ret = kexec_purgatory_get_set_symbol(image, "kernel", &kernel_load_addr,
					     माप(kernel_load_addr), false);
	अगर (ret)
		वापस ret;
	ret = kexec_purgatory_get_set_symbol(image, "dt_offset", &fdt_load_addr,
					     माप(fdt_load_addr), false);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण
