<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2015 Regents of the University of Calअगरornia
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 */

#अगर_अघोषित _ASM_RISCV_SBI_H
#घोषणा _ASM_RISCV_SBI_H

#समावेश <linux/types.h>

#अगर_घोषित CONFIG_RISCV_SBI
क्रमागत sbi_ext_id अणु
#अगर_घोषित CONFIG_RISCV_SBI_V01
	SBI_EXT_0_1_SET_TIMER = 0x0,
	SBI_EXT_0_1_CONSOLE_PUTCHAR = 0x1,
	SBI_EXT_0_1_CONSOLE_GETCHAR = 0x2,
	SBI_EXT_0_1_CLEAR_IPI = 0x3,
	SBI_EXT_0_1_SEND_IPI = 0x4,
	SBI_EXT_0_1_REMOTE_FENCE_I = 0x5,
	SBI_EXT_0_1_REMOTE_SFENCE_VMA = 0x6,
	SBI_EXT_0_1_REMOTE_SFENCE_VMA_ASID = 0x7,
	SBI_EXT_0_1_SHUTDOWN = 0x8,
#पूर्ण_अगर
	SBI_EXT_BASE = 0x10,
	SBI_EXT_TIME = 0x54494D45,
	SBI_EXT_IPI = 0x735049,
	SBI_EXT_RFENCE = 0x52464E43,
	SBI_EXT_HSM = 0x48534D,
पूर्ण;

क्रमागत sbi_ext_base_fid अणु
	SBI_EXT_BASE_GET_SPEC_VERSION = 0,
	SBI_EXT_BASE_GET_IMP_ID,
	SBI_EXT_BASE_GET_IMP_VERSION,
	SBI_EXT_BASE_PROBE_EXT,
	SBI_EXT_BASE_GET_MVENDORID,
	SBI_EXT_BASE_GET_MARCHID,
	SBI_EXT_BASE_GET_MIMPID,
पूर्ण;

क्रमागत sbi_ext_समय_fid अणु
	SBI_EXT_TIME_SET_TIMER = 0,
पूर्ण;

क्रमागत sbi_ext_ipi_fid अणु
	SBI_EXT_IPI_SEND_IPI = 0,
पूर्ण;

क्रमागत sbi_ext_rfence_fid अणु
	SBI_EXT_RFENCE_REMOTE_FENCE_I = 0,
	SBI_EXT_RFENCE_REMOTE_SFENCE_VMA,
	SBI_EXT_RFENCE_REMOTE_SFENCE_VMA_ASID,
	SBI_EXT_RFENCE_REMOTE_HFENCE_GVMA_VMID,
	SBI_EXT_RFENCE_REMOTE_HFENCE_GVMA,
	SBI_EXT_RFENCE_REMOTE_HFENCE_VVMA_ASID,
	SBI_EXT_RFENCE_REMOTE_HFENCE_VVMA,
पूर्ण;

क्रमागत sbi_ext_hsm_fid अणु
	SBI_EXT_HSM_HART_START = 0,
	SBI_EXT_HSM_HART_STOP,
	SBI_EXT_HSM_HART_STATUS,
पूर्ण;

क्रमागत sbi_hsm_hart_status अणु
	SBI_HSM_HART_STATUS_STARTED = 0,
	SBI_HSM_HART_STATUS_STOPPED,
	SBI_HSM_HART_STATUS_START_PENDING,
	SBI_HSM_HART_STATUS_STOP_PENDING,
पूर्ण;

#घोषणा SBI_SPEC_VERSION_DEFAULT	0x1
#घोषणा SBI_SPEC_VERSION_MAJOR_SHIFT	24
#घोषणा SBI_SPEC_VERSION_MAJOR_MASK	0x7f
#घोषणा SBI_SPEC_VERSION_MINOR_MASK	0xffffff

/* SBI वापस error codes */
#घोषणा SBI_SUCCESS		0
#घोषणा SBI_ERR_FAILURE		-1
#घोषणा SBI_ERR_NOT_SUPPORTED	-2
#घोषणा SBI_ERR_INVALID_PARAM	-3
#घोषणा SBI_ERR_DENIED		-4
#घोषणा SBI_ERR_INVALID_ADDRESS	-5

बाह्य अचिन्हित दीर्घ sbi_spec_version;
काष्ठा sbiret अणु
	दीर्घ error;
	दीर्घ value;
पूर्ण;

व्योम sbi_init(व्योम);
काष्ठा sbiret sbi_ecall(पूर्णांक ext, पूर्णांक fid, अचिन्हित दीर्घ arg0,
			अचिन्हित दीर्घ arg1, अचिन्हित दीर्घ arg2,
			अचिन्हित दीर्घ arg3, अचिन्हित दीर्घ arg4,
			अचिन्हित दीर्घ arg5);

व्योम sbi_console_अक्षर_दो(पूर्णांक ch);
पूर्णांक sbi_console_अक्षर_लो(व्योम);
दीर्घ sbi_get_mvenकरोrid(व्योम);
दीर्घ sbi_get_marchid(व्योम);
दीर्घ sbi_get_mimpid(व्योम);
व्योम sbi_set_समयr(uपूर्णांक64_t sसमय_value);
व्योम sbi_shutकरोwn(व्योम);
व्योम sbi_clear_ipi(व्योम);
पूर्णांक sbi_send_ipi(स्थिर अचिन्हित दीर्घ *hart_mask);
पूर्णांक sbi_remote_fence_i(स्थिर अचिन्हित दीर्घ *hart_mask);
पूर्णांक sbi_remote_sfence_vma(स्थिर अचिन्हित दीर्घ *hart_mask,
			   अचिन्हित दीर्घ start,
			   अचिन्हित दीर्घ size);

पूर्णांक sbi_remote_sfence_vma_asid(स्थिर अचिन्हित दीर्घ *hart_mask,
				अचिन्हित दीर्घ start,
				अचिन्हित दीर्घ size,
				अचिन्हित दीर्घ asid);
पूर्णांक sbi_remote_hfence_gvma(स्थिर अचिन्हित दीर्घ *hart_mask,
			   अचिन्हित दीर्घ start,
			   अचिन्हित दीर्घ size);
पूर्णांक sbi_remote_hfence_gvma_vmid(स्थिर अचिन्हित दीर्घ *hart_mask,
				अचिन्हित दीर्घ start,
				अचिन्हित दीर्घ size,
				अचिन्हित दीर्घ vmid);
पूर्णांक sbi_remote_hfence_vvma(स्थिर अचिन्हित दीर्घ *hart_mask,
			   अचिन्हित दीर्घ start,
			   अचिन्हित दीर्घ size);
पूर्णांक sbi_remote_hfence_vvma_asid(स्थिर अचिन्हित दीर्घ *hart_mask,
				अचिन्हित दीर्घ start,
				अचिन्हित दीर्घ size,
				अचिन्हित दीर्घ asid);
पूर्णांक sbi_probe_extension(पूर्णांक ext);

/* Check अगर current SBI specअगरication version is 0.1 or not */
अटल अंतरभूत पूर्णांक sbi_spec_is_0_1(व्योम)
अणु
	वापस (sbi_spec_version == SBI_SPEC_VERSION_DEFAULT) ? 1 : 0;
पूर्ण

/* Get the major version of SBI */
अटल अंतरभूत अचिन्हित दीर्घ sbi_major_version(व्योम)
अणु
	वापस (sbi_spec_version >> SBI_SPEC_VERSION_MAJOR_SHIFT) &
		SBI_SPEC_VERSION_MAJOR_MASK;
पूर्ण

/* Get the minor version of SBI */
अटल अंतरभूत अचिन्हित दीर्घ sbi_minor_version(व्योम)
अणु
	वापस sbi_spec_version & SBI_SPEC_VERSION_MINOR_MASK;
पूर्ण

पूर्णांक sbi_err_map_linux_त्रुटि_सं(पूर्णांक err);
#अन्यथा /* CONFIG_RISCV_SBI */
अटल अंतरभूत पूर्णांक sbi_remote_fence_i(स्थिर अचिन्हित दीर्घ *hart_mask) अणु वापस -1; पूर्ण
अटल अंतरभूत व्योम sbi_init(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_RISCV_SBI */
#पूर्ण_अगर /* _ASM_RISCV_SBI_H */
