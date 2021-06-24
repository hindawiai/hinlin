<शैली गुरु>
/*
 *  pcc-cpufreq.c - Processor Clocking Control firmware cpufreq पूर्णांकerface
 *
 *  Copyright (C) 2009 Red Hat, Matthew Garrett <mjg@redhat.com>
 *  Copyright (C) 2009 Hewlett-Packard Development Company, L.P.
 *	Nagananda Chumbalkar <nagananda.chumbalkar@hp.com>
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This program is मुक्त software; you can redistribute it and/or modअगरy
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or NON
 *  INFRINGEMENT. See the GNU General Public License क्रम more details.
 *
 *  You should have received a copy of the GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/sched.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/compiler.h>
#समावेश <linux/slab.h>

#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>

#समावेश <acpi/processor.h>

#घोषणा PCC_VERSION	"1.10.00"
#घोषणा POLL_LOOPS 	300

#घोषणा CMD_COMPLETE 	0x1
#घोषणा CMD_GET_FREQ 	0x0
#घोषणा CMD_SET_FREQ 	0x1

#घोषणा BUF_SZ		4

काष्ठा pcc_रेजिस्टर_resource अणु
	u8 descriptor;
	u16 length;
	u8 space_id;
	u8 bit_width;
	u8 bit_offset;
	u8 access_size;
	u64 address;
पूर्ण __attribute__ ((packed));

काष्ठा pcc_memory_resource अणु
	u8 descriptor;
	u16 length;
	u8 space_id;
	u8 resource_usage;
	u8 type_specअगरic;
	u64 granularity;
	u64 minimum;
	u64 maximum;
	u64 translation_offset;
	u64 address_length;
पूर्ण __attribute__ ((packed));

अटल काष्ठा cpufreq_driver pcc_cpufreq_driver;

काष्ठा pcc_header अणु
	u32 signature;
	u16 length;
	u8 major;
	u8 minor;
	u32 features;
	u16 command;
	u16 status;
	u32 latency;
	u32 minimum_समय;
	u32 maximum_समय;
	u32 nominal;
	u32 throttled_frequency;
	u32 minimum_frequency;
पूर्ण;

अटल व्योम __iomem *pcch_virt_addr;
अटल काष्ठा pcc_header __iomem *pcch_hdr;

अटल DEFINE_SPINLOCK(pcc_lock);

अटल काष्ठा acpi_generic_address करोorbell;

अटल u64 करोorbell_preserve;
अटल u64 करोorbell_ग_लिखो;

अटल u8 OSC_UUID[16] = अणु0x9F, 0x2C, 0x9B, 0x63, 0x91, 0x70, 0x1f, 0x49,
			  0xBB, 0x4F, 0xA5, 0x98, 0x2F, 0xA1, 0xB5, 0x46पूर्ण;

काष्ठा pcc_cpu अणु
	u32 input_offset;
	u32 output_offset;
पूर्ण;

अटल काष्ठा pcc_cpu __percpu *pcc_cpu_info;

अटल पूर्णांक pcc_cpufreq_verअगरy(काष्ठा cpufreq_policy_data *policy)
अणु
	cpufreq_verअगरy_within_cpu_limits(policy);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम pcc_cmd(व्योम)
अणु
	u64 करोorbell_value;
	पूर्णांक i;

	acpi_पढ़ो(&करोorbell_value, &करोorbell);
	acpi_ग_लिखो((करोorbell_value & करोorbell_preserve) | करोorbell_ग_लिखो,
		   &करोorbell);

	क्रम (i = 0; i < POLL_LOOPS; i++) अणु
		अगर (ioपढ़ो16(&pcch_hdr->status) & CMD_COMPLETE)
			अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pcc_clear_mapping(व्योम)
अणु
	अगर (pcch_virt_addr)
		iounmap(pcch_virt_addr);
	pcch_virt_addr = शून्य;
पूर्ण

अटल अचिन्हित पूर्णांक pcc_get_freq(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा pcc_cpu *pcc_cpu_data;
	अचिन्हित पूर्णांक curr_freq;
	अचिन्हित पूर्णांक freq_limit;
	u16 status;
	u32 input_buffer;
	u32 output_buffer;

	spin_lock(&pcc_lock);

	pr_debug("get: get_freq for CPU %d\n", cpu);
	pcc_cpu_data = per_cpu_ptr(pcc_cpu_info, cpu);

	input_buffer = 0x1;
	ioग_लिखो32(input_buffer,
			(pcch_virt_addr + pcc_cpu_data->input_offset));
	ioग_लिखो16(CMD_GET_FREQ, &pcch_hdr->command);

	pcc_cmd();

	output_buffer =
		ioपढ़ो32(pcch_virt_addr + pcc_cpu_data->output_offset);

	/* Clear the input buffer - we are करोne with the current command */
	स_रखो_io((pcch_virt_addr + pcc_cpu_data->input_offset), 0, BUF_SZ);

	status = ioपढ़ो16(&pcch_hdr->status);
	अगर (status != CMD_COMPLETE) अणु
		pr_debug("get: FAILED: for CPU %d, status is %d\n",
			cpu, status);
		जाओ cmd_incomplete;
	पूर्ण
	ioग_लिखो16(0, &pcch_hdr->status);
	curr_freq = (((ioपढ़ो32(&pcch_hdr->nominal) * (output_buffer & 0xff))
			/ 100) * 1000);

	pr_debug("get: SUCCESS: (virtual) output_offset for cpu %d is "
		"0x%p, contains a value of: 0x%x. Speed is: %d MHz\n",
		cpu, (pcch_virt_addr + pcc_cpu_data->output_offset),
		output_buffer, curr_freq);

	freq_limit = (output_buffer >> 8) & 0xff;
	अगर (freq_limit != 0xff) अणु
		pr_debug("get: frequency for cpu %d is being temporarily"
			" capped at %d\n", cpu, curr_freq);
	पूर्ण

	spin_unlock(&pcc_lock);
	वापस curr_freq;

cmd_incomplete:
	ioग_लिखो16(0, &pcch_hdr->status);
	spin_unlock(&pcc_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक pcc_cpufreq_target(काष्ठा cpufreq_policy *policy,
			      अचिन्हित पूर्णांक target_freq,
			      अचिन्हित पूर्णांक relation)
अणु
	काष्ठा pcc_cpu *pcc_cpu_data;
	काष्ठा cpufreq_freqs freqs;
	u16 status;
	u32 input_buffer;
	पूर्णांक cpu;

	cpu = policy->cpu;
	pcc_cpu_data = per_cpu_ptr(pcc_cpu_info, cpu);

	pr_debug("target: CPU %d should go to target freq: %d "
		"(virtual) input_offset is 0x%p\n",
		cpu, target_freq,
		(pcch_virt_addr + pcc_cpu_data->input_offset));

	freqs.old = policy->cur;
	freqs.new = target_freq;
	cpufreq_freq_transition_begin(policy, &freqs);
	spin_lock(&pcc_lock);

	input_buffer = 0x1 | (((target_freq * 100)
			       / (ioपढ़ो32(&pcch_hdr->nominal) * 1000)) << 8);
	ioग_लिखो32(input_buffer,
			(pcch_virt_addr + pcc_cpu_data->input_offset));
	ioग_लिखो16(CMD_SET_FREQ, &pcch_hdr->command);

	pcc_cmd();

	/* Clear the input buffer - we are करोne with the current command */
	स_रखो_io((pcch_virt_addr + pcc_cpu_data->input_offset), 0, BUF_SZ);

	status = ioपढ़ो16(&pcch_hdr->status);
	ioग_लिखो16(0, &pcch_hdr->status);

	cpufreq_freq_transition_end(policy, &freqs, status != CMD_COMPLETE);
	spin_unlock(&pcc_lock);

	अगर (status != CMD_COMPLETE) अणु
		pr_debug("target: FAILED for cpu %d, with status: 0x%x\n",
			cpu, status);
		वापस -EINVAL;
	पूर्ण

	pr_debug("target: was SUCCESSFUL for cpu %d\n", cpu);

	वापस 0;
पूर्ण

अटल पूर्णांक pcc_get_offset(पूर्णांक cpu)
अणु
	acpi_status status;
	काष्ठा acpi_buffer buffer = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	जोड़ acpi_object *pccp, *offset;
	काष्ठा pcc_cpu *pcc_cpu_data;
	काष्ठा acpi_processor *pr;
	पूर्णांक ret = 0;

	pr = per_cpu(processors, cpu);
	pcc_cpu_data = per_cpu_ptr(pcc_cpu_info, cpu);

	अगर (!pr)
		वापस -ENODEV;

	status = acpi_evaluate_object(pr->handle, "PCCP", शून्य, &buffer);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	pccp = buffer.poपूर्णांकer;
	अगर (!pccp || pccp->type != ACPI_TYPE_PACKAGE) अणु
		ret = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	offset = &(pccp->package.elements[0]);
	अगर (!offset || offset->type != ACPI_TYPE_INTEGER) अणु
		ret = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	pcc_cpu_data->input_offset = offset->पूर्णांकeger.value;

	offset = &(pccp->package.elements[1]);
	अगर (!offset || offset->type != ACPI_TYPE_INTEGER) अणु
		ret = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	pcc_cpu_data->output_offset = offset->पूर्णांकeger.value;

	स_रखो_io((pcch_virt_addr + pcc_cpu_data->input_offset), 0, BUF_SZ);
	स_रखो_io((pcch_virt_addr + pcc_cpu_data->output_offset), 0, BUF_SZ);

	pr_debug("pcc_get_offset: for CPU %d: pcc_cpu_data "
		"input_offset: 0x%x, pcc_cpu_data output_offset: 0x%x\n",
		cpu, pcc_cpu_data->input_offset, pcc_cpu_data->output_offset);
out_मुक्त:
	kमुक्त(buffer.poपूर्णांकer);
	वापस ret;
पूर्ण

अटल पूर्णांक __init pcc_cpufreq_करो_osc(acpi_handle *handle)
अणु
	acpi_status status;
	काष्ठा acpi_object_list input;
	काष्ठा acpi_buffer output = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	जोड़ acpi_object in_params[4];
	जोड़ acpi_object *out_obj;
	u32 capabilities[2];
	u32 errors;
	u32 supported;
	पूर्णांक ret = 0;

	input.count = 4;
	input.poपूर्णांकer = in_params;
	in_params[0].type               = ACPI_TYPE_BUFFER;
	in_params[0].buffer.length      = 16;
	in_params[0].buffer.poपूर्णांकer     = OSC_UUID;
	in_params[1].type               = ACPI_TYPE_INTEGER;
	in_params[1].पूर्णांकeger.value      = 1;
	in_params[2].type               = ACPI_TYPE_INTEGER;
	in_params[2].पूर्णांकeger.value      = 2;
	in_params[3].type               = ACPI_TYPE_BUFFER;
	in_params[3].buffer.length      = 8;
	in_params[3].buffer.poपूर्णांकer     = (u8 *)&capabilities;

	capabilities[0] = OSC_QUERY_ENABLE;
	capabilities[1] = 0x1;

	status = acpi_evaluate_object(*handle, "_OSC", &input, &output);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	अगर (!output.length)
		वापस -ENODEV;

	out_obj = output.poपूर्णांकer;
	अगर (out_obj->type != ACPI_TYPE_BUFFER) अणु
		ret = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	errors = *((u32 *)out_obj->buffer.poपूर्णांकer) & ~(1 << 0);
	अगर (errors) अणु
		ret = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	supported = *((u32 *)(out_obj->buffer.poपूर्णांकer + 4));
	अगर (!(supported & 0x1)) अणु
		ret = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	kमुक्त(output.poपूर्णांकer);
	capabilities[0] = 0x0;
	capabilities[1] = 0x1;

	status = acpi_evaluate_object(*handle, "_OSC", &input, &output);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	अगर (!output.length)
		वापस -ENODEV;

	out_obj = output.poपूर्णांकer;
	अगर (out_obj->type != ACPI_TYPE_BUFFER) अणु
		ret = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	errors = *((u32 *)out_obj->buffer.poपूर्णांकer) & ~(1 << 0);
	अगर (errors) अणु
		ret = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	supported = *((u32 *)(out_obj->buffer.poपूर्णांकer + 4));
	अगर (!(supported & 0x1)) अणु
		ret = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kमुक्त(output.poपूर्णांकer);
	वापस ret;
पूर्ण

अटल पूर्णांक __init pcc_cpufreq_probe(व्योम)
अणु
	acpi_status status;
	काष्ठा acpi_buffer output = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	काष्ठा pcc_memory_resource *mem_resource;
	काष्ठा pcc_रेजिस्टर_resource *reg_resource;
	जोड़ acpi_object *out_obj, *member;
	acpi_handle handle, osc_handle;
	पूर्णांक ret = 0;

	status = acpi_get_handle(शून्य, "\\_SB", &handle);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	अगर (!acpi_has_method(handle, "PCCH"))
		वापस -ENODEV;

	status = acpi_get_handle(handle, "_OSC", &osc_handle);
	अगर (ACPI_SUCCESS(status)) अणु
		ret = pcc_cpufreq_करो_osc(&osc_handle);
		अगर (ret)
			pr_debug("probe: _OSC evaluation did not succeed\n");
		/* Firmware's use of _OSC is optional */
		ret = 0;
	पूर्ण

	status = acpi_evaluate_object(handle, "PCCH", शून्य, &output);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	out_obj = output.poपूर्णांकer;
	अगर (out_obj->type != ACPI_TYPE_PACKAGE) अणु
		ret = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	member = &out_obj->package.elements[0];
	अगर (member->type != ACPI_TYPE_BUFFER) अणु
		ret = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	mem_resource = (काष्ठा pcc_memory_resource *)member->buffer.poपूर्णांकer;

	pr_debug("probe: mem_resource descriptor: 0x%x,"
		" length: %d, space_id: %d, resource_usage: %d,"
		" type_specific: %d, granularity: 0x%llx,"
		" minimum: 0x%llx, maximum: 0x%llx,"
		" translation_offset: 0x%llx, address_length: 0x%llx\n",
		mem_resource->descriptor, mem_resource->length,
		mem_resource->space_id, mem_resource->resource_usage,
		mem_resource->type_specअगरic, mem_resource->granularity,
		mem_resource->minimum, mem_resource->maximum,
		mem_resource->translation_offset,
		mem_resource->address_length);

	अगर (mem_resource->space_id != ACPI_ADR_SPACE_SYSTEM_MEMORY) अणु
		ret = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	pcch_virt_addr = ioremap(mem_resource->minimum,
					mem_resource->address_length);
	अगर (pcch_virt_addr == शून्य) अणु
		pr_debug("probe: could not map shared mem region\n");
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण
	pcch_hdr = pcch_virt_addr;

	pr_debug("probe: PCCH header (virtual) addr: 0x%p\n", pcch_hdr);
	pr_debug("probe: PCCH header is at physical address: 0x%llx,"
		" signature: 0x%x, length: %d bytes, major: %d, minor: %d,"
		" supported features: 0x%x, command field: 0x%x,"
		" status field: 0x%x, nominal latency: %d us\n",
		mem_resource->minimum, ioपढ़ो32(&pcch_hdr->signature),
		ioपढ़ो16(&pcch_hdr->length), ioपढ़ो8(&pcch_hdr->major),
		ioपढ़ो8(&pcch_hdr->minor), ioपढ़ो32(&pcch_hdr->features),
		ioपढ़ो16(&pcch_hdr->command), ioपढ़ो16(&pcch_hdr->status),
		ioपढ़ो32(&pcch_hdr->latency));

	pr_debug("probe: min time between commands: %d us,"
		" max time between commands: %d us,"
		" nominal CPU frequency: %d MHz,"
		" minimum CPU frequency: %d MHz,"
		" minimum CPU frequency without throttling: %d MHz\n",
		ioपढ़ो32(&pcch_hdr->minimum_समय),
		ioपढ़ो32(&pcch_hdr->maximum_समय),
		ioपढ़ो32(&pcch_hdr->nominal),
		ioपढ़ो32(&pcch_hdr->throttled_frequency),
		ioपढ़ो32(&pcch_hdr->minimum_frequency));

	member = &out_obj->package.elements[1];
	अगर (member->type != ACPI_TYPE_BUFFER) अणु
		ret = -ENODEV;
		जाओ pcch_मुक्त;
	पूर्ण

	reg_resource = (काष्ठा pcc_रेजिस्टर_resource *)member->buffer.poपूर्णांकer;

	करोorbell.space_id = reg_resource->space_id;
	करोorbell.bit_width = reg_resource->bit_width;
	करोorbell.bit_offset = reg_resource->bit_offset;
	करोorbell.access_width = 4;
	करोorbell.address = reg_resource->address;

	pr_debug("probe: doorbell: space_id is %d, bit_width is %d, "
		"bit_offset is %d, access_width is %d, address is 0x%llx\n",
		करोorbell.space_id, करोorbell.bit_width, करोorbell.bit_offset,
		करोorbell.access_width, reg_resource->address);

	member = &out_obj->package.elements[2];
	अगर (member->type != ACPI_TYPE_INTEGER) अणु
		ret = -ENODEV;
		जाओ pcch_मुक्त;
	पूर्ण

	करोorbell_preserve = member->पूर्णांकeger.value;

	member = &out_obj->package.elements[3];
	अगर (member->type != ACPI_TYPE_INTEGER) अणु
		ret = -ENODEV;
		जाओ pcch_मुक्त;
	पूर्ण

	करोorbell_ग_लिखो = member->पूर्णांकeger.value;

	pr_debug("probe: doorbell_preserve: 0x%llx,"
		" doorbell_write: 0x%llx\n",
		करोorbell_preserve, करोorbell_ग_लिखो);

	pcc_cpu_info = alloc_percpu(काष्ठा pcc_cpu);
	अगर (!pcc_cpu_info) अणु
		ret = -ENOMEM;
		जाओ pcch_मुक्त;
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "pcc-cpufreq: (v%s) driver loaded with frequency"
	       " limits: %d MHz, %d MHz\n", PCC_VERSION,
	       ioपढ़ो32(&pcch_hdr->minimum_frequency),
	       ioपढ़ो32(&pcch_hdr->nominal));
	kमुक्त(output.poपूर्णांकer);
	वापस ret;
pcch_मुक्त:
	pcc_clear_mapping();
out_मुक्त:
	kमुक्त(output.poपूर्णांकer);
	वापस ret;
पूर्ण

अटल पूर्णांक pcc_cpufreq_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक cpu = policy->cpu;
	अचिन्हित पूर्णांक result = 0;

	अगर (!pcch_virt_addr) अणु
		result = -1;
		जाओ out;
	पूर्ण

	result = pcc_get_offset(cpu);
	अगर (result) अणु
		pr_debug("init: PCCP evaluation failed\n");
		जाओ out;
	पूर्ण

	policy->max = policy->cpuinfo.max_freq =
		ioपढ़ो32(&pcch_hdr->nominal) * 1000;
	policy->min = policy->cpuinfo.min_freq =
		ioपढ़ो32(&pcch_hdr->minimum_frequency) * 1000;

	pr_debug("init: policy->max is %d, policy->min is %d\n",
		policy->max, policy->min);
out:
	वापस result;
पूर्ण

अटल पूर्णांक pcc_cpufreq_cpu_निकास(काष्ठा cpufreq_policy *policy)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver pcc_cpufreq_driver = अणु
	.flags = CPUFREQ_CONST_LOOPS,
	.get = pcc_get_freq,
	.verअगरy = pcc_cpufreq_verअगरy,
	.target = pcc_cpufreq_target,
	.init = pcc_cpufreq_cpu_init,
	.निकास = pcc_cpufreq_cpu_निकास,
	.name = "pcc-cpufreq",
पूर्ण;

अटल पूर्णांक __init pcc_cpufreq_init(व्योम)
अणु
	पूर्णांक ret;

	/* Skip initialization अगर another cpufreq driver is there. */
	अगर (cpufreq_get_current_driver())
		वापस -EEXIST;

	अगर (acpi_disabled)
		वापस -ENODEV;

	ret = pcc_cpufreq_probe();
	अगर (ret) अणु
		pr_debug("pcc_cpufreq_init: PCCH evaluation failed\n");
		वापस ret;
	पूर्ण

	अगर (num_present_cpus() > 4) अणु
		pcc_cpufreq_driver.flags |= CPUFREQ_NO_AUTO_DYNAMIC_SWITCHING;
		pr_err("%s: Too many CPUs, dynamic performance scaling disabled\n",
		       __func__);
		pr_err("%s: Try to enable another scaling driver through BIOS settings\n",
		       __func__);
		pr_err("%s: and complain to the system vendor\n", __func__);
	पूर्ण

	ret = cpufreq_रेजिस्टर_driver(&pcc_cpufreq_driver);

	वापस ret;
पूर्ण

अटल व्योम __निकास pcc_cpufreq_निकास(व्योम)
अणु
	cpufreq_unरेजिस्टर_driver(&pcc_cpufreq_driver);

	pcc_clear_mapping();

	मुक्त_percpu(pcc_cpu_info);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id __maybe_unused processor_device_ids[] = अणु
	अणुACPI_PROCESSOR_OBJECT_HID, पूर्ण,
	अणुACPI_PROCESSOR_DEVICE_HID, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, processor_device_ids);

MODULE_AUTHOR("Matthew Garrett, Naga Chumbalkar");
MODULE_VERSION(PCC_VERSION);
MODULE_DESCRIPTION("Processor Clocking Control interface driver");
MODULE_LICENSE("GPL");

late_initcall(pcc_cpufreq_init);
module_निकास(pcc_cpufreq_निकास);
