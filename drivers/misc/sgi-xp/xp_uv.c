<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * (C) Copyright 2020 Hewlett Packard Enterprise Development LP
 * Copyright (c) 2008 Silicon Graphics, Inc.  All Rights Reserved.
 */

/*
 * Cross Partition (XP) uv-based functions.
 *
 *      Architecture specअगरic implementation of common functions.
 *
 */

#समावेश <linux/device.h>
#समावेश <यंत्र/uv/uv_hub.h>
#अगर defined CONFIG_X86_64
#समावेश <यंत्र/uv/मूलप्रण.स>
#या_अगर defined CONFIG_IA64_SGI_UV
#समावेश <यंत्र/sn/sn_sal.h>
#पूर्ण_अगर
#समावेश "../sgi-gru/grukservices.h"
#समावेश "xp.h"

/*
 * Convert a भव memory address to a physical memory address.
 */
अटल अचिन्हित दीर्घ
xp_pa_uv(व्योम *addr)
अणु
	वापस uv_gpa(addr);
पूर्ण

/*
 * Convert a global physical to socket physical address.
 */
अटल अचिन्हित दीर्घ
xp_socket_pa_uv(अचिन्हित दीर्घ gpa)
अणु
	वापस uv_gpa_to_soc_phys_ram(gpa);
पूर्ण

अटल क्रमागत xp_retval
xp_remote_mmr_पढ़ो(अचिन्हित दीर्घ dst_gpa, स्थिर अचिन्हित दीर्घ src_gpa,
		   माप_प्रकार len)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ *dst_va = __va(uv_gpa_to_soc_phys_ram(dst_gpa));

	BUG_ON(!uv_gpa_in_mmr_space(src_gpa));
	BUG_ON(len != 8);

	ret = gru_पढ़ो_gpa(dst_va, src_gpa);
	अगर (ret == 0)
		वापस xpSuccess;

	dev_err(xp, "gru_read_gpa() failed, dst_gpa=0x%016lx src_gpa=0x%016lx "
		"len=%ld\n", dst_gpa, src_gpa, len);
	वापस xpGruCopyError;
पूर्ण


अटल क्रमागत xp_retval
xp_remote_स_नकल_uv(अचिन्हित दीर्घ dst_gpa, स्थिर अचिन्हित दीर्घ src_gpa,
		    माप_प्रकार len)
अणु
	पूर्णांक ret;

	अगर (uv_gpa_in_mmr_space(src_gpa))
		वापस xp_remote_mmr_पढ़ो(dst_gpa, src_gpa, len);

	ret = gru_copy_gpa(dst_gpa, src_gpa, len);
	अगर (ret == 0)
		वापस xpSuccess;

	dev_err(xp, "gru_copy_gpa() failed, dst_gpa=0x%016lx src_gpa=0x%016lx "
		"len=%ld\n", dst_gpa, src_gpa, len);
	वापस xpGruCopyError;
पूर्ण

अटल पूर्णांक
xp_cpu_to_nasid_uv(पूर्णांक cpuid)
अणु
	/* ??? Is this same as sn2 nasid in mach/part biपंचांगaps set up by SAL? */
	वापस UV_PNODE_TO_NASID(uv_cpu_to_pnode(cpuid));
पूर्ण

अटल क्रमागत xp_retval
xp_expand_memprotect_uv(अचिन्हित दीर्घ phys_addr, अचिन्हित दीर्घ size)
अणु
	पूर्णांक ret;

#अगर defined CONFIG_X86_64
	ret = uv_bios_change_memprotect(phys_addr, size, UV_MEMPROT_ALLOW_RW);
	अगर (ret != BIOS_STATUS_SUCCESS) अणु
		dev_err(xp, "uv_bios_change_memprotect(,, "
			"UV_MEMPROT_ALLOW_RW) failed, ret=%d\n", ret);
		वापस xpBiosError;
	पूर्ण

#या_अगर defined CONFIG_IA64_SGI_UV
	u64 nasid_array;

	ret = sn_change_memprotect(phys_addr, size, SN_MEMPROT_ACCESS_CLASS_1,
				   &nasid_array);
	अगर (ret != 0) अणु
		dev_err(xp, "sn_change_memprotect(,, "
			"SN_MEMPROT_ACCESS_CLASS_1,) failed ret=%d\n", ret);
		वापस xpSalError;
	पूर्ण
#अन्यथा
	#त्रुटि not a supported configuration
#पूर्ण_अगर
	वापस xpSuccess;
पूर्ण

अटल क्रमागत xp_retval
xp_restrict_memprotect_uv(अचिन्हित दीर्घ phys_addr, अचिन्हित दीर्घ size)
अणु
	पूर्णांक ret;

#अगर defined CONFIG_X86_64
	ret = uv_bios_change_memprotect(phys_addr, size,
					UV_MEMPROT_RESTRICT_ACCESS);
	अगर (ret != BIOS_STATUS_SUCCESS) अणु
		dev_err(xp, "uv_bios_change_memprotect(,, "
			"UV_MEMPROT_RESTRICT_ACCESS) failed, ret=%d\n", ret);
		वापस xpBiosError;
	पूर्ण

#या_अगर defined CONFIG_IA64_SGI_UV
	u64 nasid_array;

	ret = sn_change_memprotect(phys_addr, size, SN_MEMPROT_ACCESS_CLASS_0,
				   &nasid_array);
	अगर (ret != 0) अणु
		dev_err(xp, "sn_change_memprotect(,, "
			"SN_MEMPROT_ACCESS_CLASS_0,) failed ret=%d\n", ret);
		वापस xpSalError;
	पूर्ण
#अन्यथा
	#त्रुटि not a supported configuration
#पूर्ण_अगर
	वापस xpSuccess;
पूर्ण

क्रमागत xp_retval
xp_init_uv(व्योम)
अणु
	WARN_ON(!is_uv_प्रणाली());
	अगर (!is_uv_प्रणाली())
		वापस xpUnsupported;

	xp_max_npartitions = XP_MAX_NPARTITIONS_UV;
#अगर_घोषित CONFIG_X86
	xp_partition_id = sn_partition_id;
	xp_region_size = sn_region_size;
#पूर्ण_अगर
	xp_pa = xp_pa_uv;
	xp_socket_pa = xp_socket_pa_uv;
	xp_remote_स_नकल = xp_remote_स_नकल_uv;
	xp_cpu_to_nasid = xp_cpu_to_nasid_uv;
	xp_expand_memprotect = xp_expand_memprotect_uv;
	xp_restrict_memprotect = xp_restrict_memprotect_uv;

	वापस xpSuccess;
पूर्ण

व्योम
xp_निकास_uv(व्योम)
अणु
	WARN_ON(!is_uv_प्रणाली());
पूर्ण
