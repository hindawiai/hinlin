<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SBI initialilization and all extension implementation.
 *
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 */

#समावेश <linux/init.h>
#समावेश <linux/pm.h>
#समावेश <यंत्र/sbi.h>
#समावेश <यंत्र/smp.h>

/* शेष SBI version is 0.1 */
अचिन्हित दीर्घ sbi_spec_version __ro_after_init = SBI_SPEC_VERSION_DEFAULT;
EXPORT_SYMBOL(sbi_spec_version);

अटल व्योम (*__sbi_set_समयr)(uपूर्णांक64_t sसमय) __ro_after_init;
अटल पूर्णांक (*__sbi_send_ipi)(स्थिर अचिन्हित दीर्घ *hart_mask) __ro_after_init;
अटल पूर्णांक (*__sbi_rfence)(पूर्णांक fid, स्थिर अचिन्हित दीर्घ *hart_mask,
			   अचिन्हित दीर्घ start, अचिन्हित दीर्घ size,
			   अचिन्हित दीर्घ arg4, अचिन्हित दीर्घ arg5) __ro_after_init;

काष्ठा sbiret sbi_ecall(पूर्णांक ext, पूर्णांक fid, अचिन्हित दीर्घ arg0,
			अचिन्हित दीर्घ arg1, अचिन्हित दीर्घ arg2,
			अचिन्हित दीर्घ arg3, अचिन्हित दीर्घ arg4,
			अचिन्हित दीर्घ arg5)
अणु
	काष्ठा sbiret ret;

	रेजिस्टर uपूर्णांकptr_t a0 यंत्र ("a0") = (uपूर्णांकptr_t)(arg0);
	रेजिस्टर uपूर्णांकptr_t a1 यंत्र ("a1") = (uपूर्णांकptr_t)(arg1);
	रेजिस्टर uपूर्णांकptr_t a2 यंत्र ("a2") = (uपूर्णांकptr_t)(arg2);
	रेजिस्टर uपूर्णांकptr_t a3 यंत्र ("a3") = (uपूर्णांकptr_t)(arg3);
	रेजिस्टर uपूर्णांकptr_t a4 यंत्र ("a4") = (uपूर्णांकptr_t)(arg4);
	रेजिस्टर uपूर्णांकptr_t a5 यंत्र ("a5") = (uपूर्णांकptr_t)(arg5);
	रेजिस्टर uपूर्णांकptr_t a6 यंत्र ("a6") = (uपूर्णांकptr_t)(fid);
	रेजिस्टर uपूर्णांकptr_t a7 यंत्र ("a7") = (uपूर्णांकptr_t)(ext);
	यंत्र अस्थिर ("ecall"
		      : "+r" (a0), "+r" (a1)
		      : "r" (a2), "r" (a3), "r" (a4), "r" (a5), "r" (a6), "r" (a7)
		      : "memory");
	ret.error = a0;
	ret.value = a1;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(sbi_ecall);

पूर्णांक sbi_err_map_linux_त्रुटि_सं(पूर्णांक err)
अणु
	चयन (err) अणु
	हाल SBI_SUCCESS:
		वापस 0;
	हाल SBI_ERR_DENIED:
		वापस -EPERM;
	हाल SBI_ERR_INVALID_PARAM:
		वापस -EINVAL;
	हाल SBI_ERR_INVALID_ADDRESS:
		वापस -EFAULT;
	हाल SBI_ERR_NOT_SUPPORTED:
	हाल SBI_ERR_FAILURE:
	शेष:
		वापस -ENOTSUPP;
	पूर्ण;
पूर्ण
EXPORT_SYMBOL(sbi_err_map_linux_त्रुटि_सं);

#अगर_घोषित CONFIG_RISCV_SBI_V01
/**
 * sbi_console_अक्षर_दो() - Writes given अक्षरacter to the console device.
 * @ch: The data to be written to the console.
 *
 * Return: None
 */
व्योम sbi_console_अक्षर_दो(पूर्णांक ch)
अणु
	sbi_ecall(SBI_EXT_0_1_CONSOLE_PUTCHAR, 0, ch, 0, 0, 0, 0, 0);
पूर्ण
EXPORT_SYMBOL(sbi_console_अक्षर_दो);

/**
 * sbi_console_अक्षर_लो() - Reads a byte from console device.
 *
 * Returns the value पढ़ो from console.
 */
पूर्णांक sbi_console_अक्षर_लो(व्योम)
अणु
	काष्ठा sbiret ret;

	ret = sbi_ecall(SBI_EXT_0_1_CONSOLE_GETCHAR, 0, 0, 0, 0, 0, 0, 0);

	वापस ret.error;
पूर्ण
EXPORT_SYMBOL(sbi_console_अक्षर_लो);

/**
 * sbi_shutकरोwn() - Remove all the harts from executing supervisor code.
 *
 * Return: None
 */
व्योम sbi_shutकरोwn(व्योम)
अणु
	sbi_ecall(SBI_EXT_0_1_SHUTDOWN, 0, 0, 0, 0, 0, 0, 0);
पूर्ण
EXPORT_SYMBOL(sbi_shutकरोwn);

/**
 * sbi_clear_ipi() - Clear any pending IPIs क्रम the calling hart.
 *
 * Return: None
 */
व्योम sbi_clear_ipi(व्योम)
अणु
	sbi_ecall(SBI_EXT_0_1_CLEAR_IPI, 0, 0, 0, 0, 0, 0, 0);
पूर्ण
EXPORT_SYMBOL(sbi_clear_ipi);

/**
 * __sbi_set_समयr_v01() - Program the समयr क्रम next समयr event.
 * @sसमय_value: The value after which next समयr event should fire.
 *
 * Return: None
 */
अटल व्योम __sbi_set_समयr_v01(uपूर्णांक64_t sसमय_value)
अणु
#अगर __riscv_xlen == 32
	sbi_ecall(SBI_EXT_0_1_SET_TIMER, 0, sसमय_value,
		  sसमय_value >> 32, 0, 0, 0, 0);
#अन्यथा
	sbi_ecall(SBI_EXT_0_1_SET_TIMER, 0, sसमय_value, 0, 0, 0, 0, 0);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __sbi_send_ipi_v01(स्थिर अचिन्हित दीर्घ *hart_mask)
अणु
	sbi_ecall(SBI_EXT_0_1_SEND_IPI, 0, (अचिन्हित दीर्घ)hart_mask,
		  0, 0, 0, 0, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक __sbi_rfence_v01(पूर्णांक fid, स्थिर अचिन्हित दीर्घ *hart_mask,
			    अचिन्हित दीर्घ start, अचिन्हित दीर्घ size,
			    अचिन्हित दीर्घ arg4, अचिन्हित दीर्घ arg5)
अणु
	पूर्णांक result = 0;

	/* v0.2 function IDs are equivalent to v0.1 extension IDs */
	चयन (fid) अणु
	हाल SBI_EXT_RFENCE_REMOTE_FENCE_I:
		sbi_ecall(SBI_EXT_0_1_REMOTE_FENCE_I, 0,
			  (अचिन्हित दीर्घ)hart_mask, 0, 0, 0, 0, 0);
		अवरोध;
	हाल SBI_EXT_RFENCE_REMOTE_SFENCE_VMA:
		sbi_ecall(SBI_EXT_0_1_REMOTE_SFENCE_VMA, 0,
			  (अचिन्हित दीर्घ)hart_mask, start, size,
			  0, 0, 0);
		अवरोध;
	हाल SBI_EXT_RFENCE_REMOTE_SFENCE_VMA_ASID:
		sbi_ecall(SBI_EXT_0_1_REMOTE_SFENCE_VMA_ASID, 0,
			  (अचिन्हित दीर्घ)hart_mask, start, size,
			  arg4, 0, 0);
		अवरोध;
	शेष:
		pr_err("SBI call [%d]not supported in SBI v0.1\n", fid);
		result = -EINVAL;
	पूर्ण

	वापस result;
पूर्ण

अटल व्योम sbi_set_घातer_off(व्योम)
अणु
	pm_घातer_off = sbi_shutकरोwn;
पूर्ण
#अन्यथा
अटल व्योम __sbi_set_समयr_v01(uपूर्णांक64_t sसमय_value)
अणु
	pr_warn("Timer extension is not available in SBI v%lu.%lu\n",
		sbi_major_version(), sbi_minor_version());
पूर्ण

अटल पूर्णांक __sbi_send_ipi_v01(स्थिर अचिन्हित दीर्घ *hart_mask)
अणु
	pr_warn("IPI extension is not available in SBI v%lu.%lu\n",
		sbi_major_version(), sbi_minor_version());

	वापस 0;
पूर्ण

अटल पूर्णांक __sbi_rfence_v01(पूर्णांक fid, स्थिर अचिन्हित दीर्घ *hart_mask,
			    अचिन्हित दीर्घ start, अचिन्हित दीर्घ size,
			    अचिन्हित दीर्घ arg4, अचिन्हित दीर्घ arg5)
अणु
	pr_warn("remote fence extension is not available in SBI v%lu.%lu\n",
		sbi_major_version(), sbi_minor_version());

	वापस 0;
पूर्ण

अटल व्योम sbi_set_घातer_off(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_RISCV_SBI_V01 */

अटल व्योम __sbi_set_समयr_v02(uपूर्णांक64_t sसमय_value)
अणु
#अगर __riscv_xlen == 32
	sbi_ecall(SBI_EXT_TIME, SBI_EXT_TIME_SET_TIMER, sसमय_value,
		  sसमय_value >> 32, 0, 0, 0, 0);
#अन्यथा
	sbi_ecall(SBI_EXT_TIME, SBI_EXT_TIME_SET_TIMER, sसमय_value, 0,
		  0, 0, 0, 0);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __sbi_send_ipi_v02(स्थिर अचिन्हित दीर्घ *hart_mask)
अणु
	अचिन्हित दीर्घ hartid, hmask_val, hbase;
	काष्ठा cpumask पंचांगask;
	काष्ठा sbiret ret = अणु0पूर्ण;
	पूर्णांक result;

	अगर (!hart_mask || !(*hart_mask)) अणु
		riscv_cpuid_to_hartid_mask(cpu_online_mask, &पंचांगask);
		hart_mask = cpumask_bits(&पंचांगask);
	पूर्ण

	hmask_val = 0;
	hbase = 0;
	क्रम_each_set_bit(hartid, hart_mask, NR_CPUS) अणु
		अगर (hmask_val && ((hbase + BITS_PER_LONG) <= hartid)) अणु
			ret = sbi_ecall(SBI_EXT_IPI, SBI_EXT_IPI_SEND_IPI,
					hmask_val, hbase, 0, 0, 0, 0);
			अगर (ret.error)
				जाओ ecall_failed;
			hmask_val = 0;
			hbase = 0;
		पूर्ण
		अगर (!hmask_val)
			hbase = hartid;
		hmask_val |= 1UL << (hartid - hbase);
	पूर्ण

	अगर (hmask_val) अणु
		ret = sbi_ecall(SBI_EXT_IPI, SBI_EXT_IPI_SEND_IPI,
				hmask_val, hbase, 0, 0, 0, 0);
		अगर (ret.error)
			जाओ ecall_failed;
	पूर्ण

	वापस 0;

ecall_failed:
	result = sbi_err_map_linux_त्रुटि_सं(ret.error);
	pr_err("%s: hbase = [%lu] hmask = [0x%lx] failed (error [%d])\n",
	       __func__, hbase, hmask_val, result);
	वापस result;
पूर्ण

अटल पूर्णांक __sbi_rfence_v02_call(अचिन्हित दीर्घ fid, अचिन्हित दीर्घ hmask_val,
				 अचिन्हित दीर्घ hbase, अचिन्हित दीर्घ start,
				 अचिन्हित दीर्घ size, अचिन्हित दीर्घ arg4,
				 अचिन्हित दीर्घ arg5)
अणु
	काष्ठा sbiret ret = अणु0पूर्ण;
	पूर्णांक ext = SBI_EXT_RFENCE;
	पूर्णांक result = 0;

	चयन (fid) अणु
	हाल SBI_EXT_RFENCE_REMOTE_FENCE_I:
		ret = sbi_ecall(ext, fid, hmask_val, hbase, 0, 0, 0, 0);
		अवरोध;
	हाल SBI_EXT_RFENCE_REMOTE_SFENCE_VMA:
		ret = sbi_ecall(ext, fid, hmask_val, hbase, start,
				size, 0, 0);
		अवरोध;
	हाल SBI_EXT_RFENCE_REMOTE_SFENCE_VMA_ASID:
		ret = sbi_ecall(ext, fid, hmask_val, hbase, start,
				size, arg4, 0);
		अवरोध;

	हाल SBI_EXT_RFENCE_REMOTE_HFENCE_GVMA:
		ret = sbi_ecall(ext, fid, hmask_val, hbase, start,
				size, 0, 0);
		अवरोध;
	हाल SBI_EXT_RFENCE_REMOTE_HFENCE_GVMA_VMID:
		ret = sbi_ecall(ext, fid, hmask_val, hbase, start,
				size, arg4, 0);
		अवरोध;
	हाल SBI_EXT_RFENCE_REMOTE_HFENCE_VVMA:
		ret = sbi_ecall(ext, fid, hmask_val, hbase, start,
				size, 0, 0);
		अवरोध;
	हाल SBI_EXT_RFENCE_REMOTE_HFENCE_VVMA_ASID:
		ret = sbi_ecall(ext, fid, hmask_val, hbase, start,
				size, arg4, 0);
		अवरोध;
	शेष:
		pr_err("unknown function ID [%lu] for SBI extension [%d]\n",
		       fid, ext);
		result = -EINVAL;
	पूर्ण

	अगर (ret.error) अणु
		result = sbi_err_map_linux_त्रुटि_सं(ret.error);
		pr_err("%s: hbase = [%lu] hmask = [0x%lx] failed (error [%d])\n",
		       __func__, hbase, hmask_val, result);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक __sbi_rfence_v02(पूर्णांक fid, स्थिर अचिन्हित दीर्घ *hart_mask,
			    अचिन्हित दीर्घ start, अचिन्हित दीर्घ size,
			    अचिन्हित दीर्घ arg4, अचिन्हित दीर्घ arg5)
अणु
	अचिन्हित दीर्घ hmask_val, hartid, hbase;
	काष्ठा cpumask पंचांगask;
	पूर्णांक result;

	अगर (!hart_mask || !(*hart_mask)) अणु
		riscv_cpuid_to_hartid_mask(cpu_online_mask, &पंचांगask);
		hart_mask = cpumask_bits(&पंचांगask);
	पूर्ण

	hmask_val = 0;
	hbase = 0;
	क्रम_each_set_bit(hartid, hart_mask, NR_CPUS) अणु
		अगर (hmask_val && ((hbase + BITS_PER_LONG) <= hartid)) अणु
			result = __sbi_rfence_v02_call(fid, hmask_val, hbase,
						       start, size, arg4, arg5);
			अगर (result)
				वापस result;
			hmask_val = 0;
			hbase = 0;
		पूर्ण
		अगर (!hmask_val)
			hbase = hartid;
		hmask_val |= 1UL << (hartid - hbase);
	पूर्ण

	अगर (hmask_val) अणु
		result = __sbi_rfence_v02_call(fid, hmask_val, hbase,
					       start, size, arg4, arg5);
		अगर (result)
			वापस result;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sbi_set_समयr() - Program the समयr क्रम next समयr event.
 * @sसमय_value: The value after which next समयr event should fire.
 *
 * Return: None.
 */
व्योम sbi_set_समयr(uपूर्णांक64_t sसमय_value)
अणु
	__sbi_set_समयr(sसमय_value);
पूर्ण

/**
 * sbi_send_ipi() - Send an IPI to any hart.
 * @hart_mask: A cpu mask containing all the target harts.
 *
 * Return: 0 on success, appropriate linux error code otherwise.
 */
पूर्णांक sbi_send_ipi(स्थिर अचिन्हित दीर्घ *hart_mask)
अणु
	वापस __sbi_send_ipi(hart_mask);
पूर्ण
EXPORT_SYMBOL(sbi_send_ipi);

/**
 * sbi_remote_fence_i() - Execute FENCE.I inकाष्ठाion on given remote harts.
 * @hart_mask: A cpu mask containing all the target harts.
 *
 * Return: 0 on success, appropriate linux error code otherwise.
 */
पूर्णांक sbi_remote_fence_i(स्थिर अचिन्हित दीर्घ *hart_mask)
अणु
	वापस __sbi_rfence(SBI_EXT_RFENCE_REMOTE_FENCE_I,
			    hart_mask, 0, 0, 0, 0);
पूर्ण
EXPORT_SYMBOL(sbi_remote_fence_i);

/**
 * sbi_remote_sfence_vma() - Execute SFENCE.VMA inकाष्ठाions on given remote
 *			     harts क्रम the specअगरied भव address range.
 * @hart_mask: A cpu mask containing all the target harts.
 * @start: Start of the भव address
 * @size: Total size of the भव address range.
 *
 * Return: 0 on success, appropriate linux error code otherwise.
 */
पूर्णांक sbi_remote_sfence_vma(स्थिर अचिन्हित दीर्घ *hart_mask,
			   अचिन्हित दीर्घ start,
			   अचिन्हित दीर्घ size)
अणु
	वापस __sbi_rfence(SBI_EXT_RFENCE_REMOTE_SFENCE_VMA,
			    hart_mask, start, size, 0, 0);
पूर्ण
EXPORT_SYMBOL(sbi_remote_sfence_vma);

/**
 * sbi_remote_sfence_vma_asid() - Execute SFENCE.VMA inकाष्ठाions on given
 * remote harts क्रम a भव address range beदीर्घing to a specअगरic ASID.
 *
 * @hart_mask: A cpu mask containing all the target harts.
 * @start: Start of the भव address
 * @size: Total size of the भव address range.
 * @asid: The value of address space identअगरier (ASID).
 *
 * Return: 0 on success, appropriate linux error code otherwise.
 */
पूर्णांक sbi_remote_sfence_vma_asid(स्थिर अचिन्हित दीर्घ *hart_mask,
				अचिन्हित दीर्घ start,
				अचिन्हित दीर्घ size,
				अचिन्हित दीर्घ asid)
अणु
	वापस __sbi_rfence(SBI_EXT_RFENCE_REMOTE_SFENCE_VMA_ASID,
			    hart_mask, start, size, asid, 0);
पूर्ण
EXPORT_SYMBOL(sbi_remote_sfence_vma_asid);

/**
 * sbi_remote_hfence_gvma() - Execute HFENCE.GVMA inकाष्ठाions on given remote
 *			   harts क्रम the specअगरied guest physical address range.
 * @hart_mask: A cpu mask containing all the target harts.
 * @start: Start of the guest physical address
 * @size: Total size of the guest physical address range.
 *
 * Return: None
 */
पूर्णांक sbi_remote_hfence_gvma(स्थिर अचिन्हित दीर्घ *hart_mask,
			   अचिन्हित दीर्घ start,
			   अचिन्हित दीर्घ size)
अणु
	वापस __sbi_rfence(SBI_EXT_RFENCE_REMOTE_HFENCE_GVMA,
			    hart_mask, start, size, 0, 0);
पूर्ण
EXPORT_SYMBOL_GPL(sbi_remote_hfence_gvma);

/**
 * sbi_remote_hfence_gvma_vmid() - Execute HFENCE.GVMA inकाष्ठाions on given
 * remote harts क्रम a guest physical address range beदीर्घing to a specअगरic VMID.
 *
 * @hart_mask: A cpu mask containing all the target harts.
 * @start: Start of the guest physical address
 * @size: Total size of the guest physical address range.
 * @vmid: The value of guest ID (VMID).
 *
 * Return: 0 अगर success, Error otherwise.
 */
पूर्णांक sbi_remote_hfence_gvma_vmid(स्थिर अचिन्हित दीर्घ *hart_mask,
				अचिन्हित दीर्घ start,
				अचिन्हित दीर्घ size,
				अचिन्हित दीर्घ vmid)
अणु
	वापस __sbi_rfence(SBI_EXT_RFENCE_REMOTE_HFENCE_GVMA_VMID,
			    hart_mask, start, size, vmid, 0);
पूर्ण
EXPORT_SYMBOL(sbi_remote_hfence_gvma_vmid);

/**
 * sbi_remote_hfence_vvma() - Execute HFENCE.VVMA inकाष्ठाions on given remote
 *			     harts क्रम the current guest भव address range.
 * @hart_mask: A cpu mask containing all the target harts.
 * @start: Start of the current guest भव address
 * @size: Total size of the current guest भव address range.
 *
 * Return: None
 */
पूर्णांक sbi_remote_hfence_vvma(स्थिर अचिन्हित दीर्घ *hart_mask,
			   अचिन्हित दीर्घ start,
			   अचिन्हित दीर्घ size)
अणु
	वापस __sbi_rfence(SBI_EXT_RFENCE_REMOTE_HFENCE_VVMA,
			    hart_mask, start, size, 0, 0);
पूर्ण
EXPORT_SYMBOL(sbi_remote_hfence_vvma);

/**
 * sbi_remote_hfence_vvma_asid() - Execute HFENCE.VVMA inकाष्ठाions on given
 * remote harts क्रम current guest भव address range beदीर्घing to a specअगरic
 * ASID.
 *
 * @hart_mask: A cpu mask containing all the target harts.
 * @start: Start of the current guest भव address
 * @size: Total size of the current guest भव address range.
 * @asid: The value of address space identअगरier (ASID).
 *
 * Return: None
 */
पूर्णांक sbi_remote_hfence_vvma_asid(स्थिर अचिन्हित दीर्घ *hart_mask,
				अचिन्हित दीर्घ start,
				अचिन्हित दीर्घ size,
				अचिन्हित दीर्घ asid)
अणु
	वापस __sbi_rfence(SBI_EXT_RFENCE_REMOTE_HFENCE_VVMA_ASID,
			    hart_mask, start, size, asid, 0);
पूर्ण
EXPORT_SYMBOL(sbi_remote_hfence_vvma_asid);

/**
 * sbi_probe_extension() - Check अगर an SBI extension ID is supported or not.
 * @extid: The extension ID to be probed.
 *
 * Return: Extension specअगरic nonzero value f yes, -ENOTSUPP otherwise.
 */
पूर्णांक sbi_probe_extension(पूर्णांक extid)
अणु
	काष्ठा sbiret ret;

	ret = sbi_ecall(SBI_EXT_BASE, SBI_EXT_BASE_PROBE_EXT, extid,
			0, 0, 0, 0, 0);
	अगर (!ret.error)
		अगर (ret.value)
			वापस ret.value;

	वापस -ENOTSUPP;
पूर्ण
EXPORT_SYMBOL(sbi_probe_extension);

अटल दीर्घ __sbi_base_ecall(पूर्णांक fid)
अणु
	काष्ठा sbiret ret;

	ret = sbi_ecall(SBI_EXT_BASE, fid, 0, 0, 0, 0, 0, 0);
	अगर (!ret.error)
		वापस ret.value;
	अन्यथा
		वापस sbi_err_map_linux_त्रुटि_सं(ret.error);
पूर्ण

अटल अंतरभूत दीर्घ sbi_get_spec_version(व्योम)
अणु
	वापस __sbi_base_ecall(SBI_EXT_BASE_GET_SPEC_VERSION);
पूर्ण

अटल अंतरभूत दीर्घ sbi_get_firmware_id(व्योम)
अणु
	वापस __sbi_base_ecall(SBI_EXT_BASE_GET_IMP_ID);
पूर्ण

अटल अंतरभूत दीर्घ sbi_get_firmware_version(व्योम)
अणु
	वापस __sbi_base_ecall(SBI_EXT_BASE_GET_IMP_VERSION);
पूर्ण

दीर्घ sbi_get_mvenकरोrid(व्योम)
अणु
	वापस __sbi_base_ecall(SBI_EXT_BASE_GET_MVENDORID);
पूर्ण

दीर्घ sbi_get_marchid(व्योम)
अणु
	वापस __sbi_base_ecall(SBI_EXT_BASE_GET_MARCHID);
पूर्ण

दीर्घ sbi_get_mimpid(व्योम)
अणु
	वापस __sbi_base_ecall(SBI_EXT_BASE_GET_MIMPID);
पूर्ण

अटल व्योम sbi_send_cpumask_ipi(स्थिर काष्ठा cpumask *target)
अणु
	काष्ठा cpumask hartid_mask;

	riscv_cpuid_to_hartid_mask(target, &hartid_mask);

	sbi_send_ipi(cpumask_bits(&hartid_mask));
पूर्ण

अटल स्थिर काष्ठा riscv_ipi_ops sbi_ipi_ops = अणु
	.ipi_inject = sbi_send_cpumask_ipi
पूर्ण;

व्योम __init sbi_init(व्योम)
अणु
	पूर्णांक ret;

	sbi_set_घातer_off();
	ret = sbi_get_spec_version();
	अगर (ret > 0)
		sbi_spec_version = ret;

	pr_info("SBI specification v%lu.%lu detected\n",
		sbi_major_version(), sbi_minor_version());

	अगर (!sbi_spec_is_0_1()) अणु
		pr_info("SBI implementation ID=0x%lx Version=0x%lx\n",
			sbi_get_firmware_id(), sbi_get_firmware_version());
		अगर (sbi_probe_extension(SBI_EXT_TIME) > 0) अणु
			__sbi_set_समयr = __sbi_set_समयr_v02;
			pr_info("SBI TIME extension detected\n");
		पूर्ण अन्यथा अणु
			__sbi_set_समयr = __sbi_set_समयr_v01;
		पूर्ण
		अगर (sbi_probe_extension(SBI_EXT_IPI) > 0) अणु
			__sbi_send_ipi	= __sbi_send_ipi_v02;
			pr_info("SBI IPI extension detected\n");
		पूर्ण अन्यथा अणु
			__sbi_send_ipi	= __sbi_send_ipi_v01;
		पूर्ण
		अगर (sbi_probe_extension(SBI_EXT_RFENCE) > 0) अणु
			__sbi_rfence	= __sbi_rfence_v02;
			pr_info("SBI RFENCE extension detected\n");
		पूर्ण अन्यथा अणु
			__sbi_rfence	= __sbi_rfence_v01;
		पूर्ण
	पूर्ण अन्यथा अणु
		__sbi_set_समयr = __sbi_set_समयr_v01;
		__sbi_send_ipi	= __sbi_send_ipi_v01;
		__sbi_rfence	= __sbi_rfence_v01;
	पूर्ण

	riscv_set_ipi_ops(&sbi_ipi_ops);
पूर्ण
