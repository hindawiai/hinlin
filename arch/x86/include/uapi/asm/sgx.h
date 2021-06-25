<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright(c) 2016-20 Intel Corporation.
 */
#अगर_अघोषित _UAPI_ASM_X86_SGX_H
#घोषणा _UAPI_ASM_X86_SGX_H

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

/**
 * क्रमागत sgx_page_flags - page control flags
 * %SGX_PAGE_MEASURE:	Measure the page contents with a sequence of
 *			ENCLS[EEXTEND] operations.
 */
क्रमागत sgx_page_flags अणु
	SGX_PAGE_MEASURE	= 0x01,
पूर्ण;

#घोषणा SGX_MAGIC 0xA4

#घोषणा SGX_IOC_ENCLAVE_CREATE \
	_IOW(SGX_MAGIC, 0x00, काष्ठा sgx_enclave_create)
#घोषणा SGX_IOC_ENCLAVE_ADD_PAGES \
	_IOWR(SGX_MAGIC, 0x01, काष्ठा sgx_enclave_add_pages)
#घोषणा SGX_IOC_ENCLAVE_INIT \
	_IOW(SGX_MAGIC, 0x02, काष्ठा sgx_enclave_init)
#घोषणा SGX_IOC_ENCLAVE_PROVISION \
	_IOW(SGX_MAGIC, 0x03, काष्ठा sgx_enclave_provision)

/**
 * काष्ठा sgx_enclave_create - parameter काष्ठाure क्रम the
 *                             %SGX_IOC_ENCLAVE_CREATE ioctl
 * @src:	address क्रम the SECS page data
 */
काष्ठा sgx_enclave_create  अणु
	__u64	src;
पूर्ण;

/**
 * काष्ठा sgx_enclave_add_pages - parameter काष्ठाure क्रम the
 *                                %SGX_IOC_ENCLAVE_ADD_PAGE ioctl
 * @src:	start address क्रम the page data
 * @offset:	starting page offset
 * @length:	length of the data (multiple of the page size)
 * @secinfo:	address क्रम the SECINFO data
 * @flags:	page control flags
 * @count:	number of bytes added (multiple of the page size)
 */
काष्ठा sgx_enclave_add_pages अणु
	__u64 src;
	__u64 offset;
	__u64 length;
	__u64 secinfo;
	__u64 flags;
	__u64 count;
पूर्ण;

/**
 * काष्ठा sgx_enclave_init - parameter काष्ठाure क्रम the
 *                           %SGX_IOC_ENCLAVE_INIT ioctl
 * @sigकाष्ठा:	address क्रम the SIGSTRUCT data
 */
काष्ठा sgx_enclave_init अणु
	__u64 sigकाष्ठा;
पूर्ण;

/**
 * काष्ठा sgx_enclave_provision - parameter काष्ठाure क्रम the
 *				  %SGX_IOC_ENCLAVE_PROVISION ioctl
 * @fd:		file handle of /dev/sgx_provision
 */
काष्ठा sgx_enclave_provision अणु
	__u64 fd;
पूर्ण;

काष्ठा sgx_enclave_run;

/**
 * प्रकार sgx_enclave_user_handler_t - Exit handler function accepted by
 *					__vdso_sgx_enter_enclave()
 * @run:	The run instance given by the caller
 *
 * The रेजिस्टर parameters contain the snapshot of their values at enclave
 * निकास. An invalid ENCLU function number will cause -EINVAL to be वापसed
 * to the caller.
 *
 * Return:
 * - <= 0:	The given value is वापसed back to the caller.
 * - > 0:	ENCLU function to invoke, either EENTER or ERESUME.
 */
प्रकार पूर्णांक (*sgx_enclave_user_handler_t)(दीर्घ rdi, दीर्घ rsi, दीर्घ rdx,
					  दीर्घ rsp, दीर्घ r8, दीर्घ r9,
					  काष्ठा sgx_enclave_run *run);

/**
 * काष्ठा sgx_enclave_run - the execution context of __vdso_sgx_enter_enclave()
 * @tcs:			TCS used to enter the enclave
 * @function:			The last seen ENCLU function (EENTER, ERESUME or EEXIT)
 * @exception_vector:		The पूर्णांकerrupt vector of the exception
 * @exception_error_code:	The exception error code pulled out of the stack
 * @exception_addr:		The address that triggered the exception
 * @user_handler:		User provided callback run on exception
 * @user_data:			Data passed to the user handler
 * @reserved			Reserved क्रम future extensions
 *
 * If @user_handler is provided, the handler will be invoked on all वापस paths
 * of the normal flow.  The user handler may transfer control, e.g. via a
 * दीर्घ_लाँघ() call or a C++ exception, without वापसing to
 * __vdso_sgx_enter_enclave().
 */
काष्ठा sgx_enclave_run अणु
	__u64 tcs;
	__u32 function;
	__u16 exception_vector;
	__u16 exception_error_code;
	__u64 exception_addr;
	__u64 user_handler;
	__u64 user_data;
	__u8  reserved[216];
पूर्ण;

/**
 * प्रकार vdso_sgx_enter_enclave_t - Prototype क्रम __vdso_sgx_enter_enclave(),
 *				      a vDSO function to enter an SGX enclave.
 * @rdi:	Pass-through value क्रम RDI
 * @rsi:	Pass-through value क्रम RSI
 * @rdx:	Pass-through value क्रम RDX
 * @function:	ENCLU function, must be EENTER or ERESUME
 * @r8:		Pass-through value क्रम R8
 * @r9:		Pass-through value क्रम R9
 * @run:	काष्ठा sgx_enclave_run, must be non-शून्य
 *
 * NOTE: __vdso_sgx_enter_enclave() करोes not ensure full compliance with the
 * x86-64 ABI, e.g. करोesn't handle XSAVE state.  Except क्रम non-अस्थिर
 * general purpose रेजिस्टरs, EFLAGS.DF, and RSP alignment, preserving/setting
 * state in accordance with the x86-64 ABI is the responsibility of the enclave
 * and its runसमय, i.e. __vdso_sgx_enter_enclave() cannot be called from C
 * code without careful consideration by both the enclave and its runसमय.
 *
 * All general purpose रेजिस्टरs except RAX, RBX and RCX are passed as-is to the
 * enclave.  RAX, RBX and RCX are consumed by EENTER and ERESUME and are loaded
 * with @function, asynchronous निकास poपूर्णांकer, and @run.tcs respectively.
 *
 * RBP and the stack are used to anchor __vdso_sgx_enter_enclave() to the
 * pre-enclave state, e.g. to retrieve @run.exception and @run.user_handler
 * after an enclave निकास.  All other रेजिस्टरs are available क्रम use by the
 * enclave and its runसमय, e.g. an enclave can push additional data onto the
 * stack (and modअगरy RSP) to pass inक्रमmation to the optional user handler (see
 * below).
 *
 * Most exceptions reported on ENCLU, including those that occur within the
 * enclave, are fixed up and reported synchronously instead of being delivered
 * via a standard संकेत. Debug Exceptions (#DB) and Breakpoपूर्णांकs (#BP) are
 * never fixed up and are always delivered via standard संकेतs. On synchronously
 * reported exceptions, -EFAULT is वापसed and details about the exception are
 * recorded in @run.exception, the optional sgx_enclave_exception काष्ठा.
 *
 * Return:
 * - 0:		ENCLU function was successfully executed.
 * - -EINVAL:	Invalid ENCL number (neither EENTER nor ERESUME).
 */
प्रकार पूर्णांक (*vdso_sgx_enter_enclave_t)(अचिन्हित दीर्घ rdi, अचिन्हित दीर्घ rsi,
					अचिन्हित दीर्घ rdx, अचिन्हित पूर्णांक function,
					अचिन्हित दीर्घ r8,  अचिन्हित दीर्घ r9,
					काष्ठा sgx_enclave_run *run);

#पूर्ण_अगर /* _UAPI_ASM_X86_SGX_H */
