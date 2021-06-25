<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-2-Clause) */
/*
 * Copyright (c) 2015-2021, Linaro Limited
 */
#अगर_अघोषित OPTEE_SMC_H
#घोषणा OPTEE_SMC_H

#समावेश <linux/arm-smccc.h>
#समावेश <linux/bitops.h>

#घोषणा OPTEE_SMC_STD_CALL_VAL(func_num) \
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_STD_CALL, ARM_SMCCC_SMC_32, \
			   ARM_SMCCC_OWNER_TRUSTED_OS, (func_num))
#घोषणा OPTEE_SMC_FAST_CALL_VAL(func_num) \
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_FAST_CALL, ARM_SMCCC_SMC_32, \
			   ARM_SMCCC_OWNER_TRUSTED_OS, (func_num))

/*
 * Function specअगरied by SMC Calling convention.
 */
#घोषणा OPTEE_SMC_FUNCID_CALLS_COUNT	0xFF00
#घोषणा OPTEE_SMC_CALLS_COUNT \
	ARM_SMCCC_CALL_VAL(OPTEE_SMC_FAST_CALL, SMCCC_SMC_32, \
			   SMCCC_OWNER_TRUSTED_OS_END, \
			   OPTEE_SMC_FUNCID_CALLS_COUNT)

/*
 * Normal cached memory (ग_लिखो-back), shareable क्रम SMP प्रणालीs and not
 * shareable क्रम UP प्रणालीs.
 */
#घोषणा OPTEE_SMC_SHM_CACHED		1

/*
 * a0..a7 is used as रेजिस्टर names in the descriptions below, on arm32
 * that translates to r0..r7 and on arm64 to w0..w7. In both हालs it's
 * 32-bit रेजिस्टरs.
 */

/*
 * Function specअगरied by SMC Calling convention
 *
 * Return the following UID अगर using API specअगरied in this file
 * without further extensions:
 * 384fb3e0-e7f8-11e3-af63-0002a5d5c51b.
 * see also OPTEE_MSG_UID_* in optee_msg.h
 */
#घोषणा OPTEE_SMC_FUNCID_CALLS_UID OPTEE_MSG_FUNCID_CALLS_UID
#घोषणा OPTEE_SMC_CALLS_UID \
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_FAST_CALL, ARM_SMCCC_SMC_32, \
			   ARM_SMCCC_OWNER_TRUSTED_OS_END, \
			   OPTEE_SMC_FUNCID_CALLS_UID)

/*
 * Function specअगरied by SMC Calling convention
 *
 * Returns 2.0 अगर using API specअगरied in this file without further extensions.
 * see also OPTEE_MSG_REVISION_* in optee_msg.h
 */
#घोषणा OPTEE_SMC_FUNCID_CALLS_REVISION OPTEE_MSG_FUNCID_CALLS_REVISION
#घोषणा OPTEE_SMC_CALLS_REVISION \
	ARM_SMCCC_CALL_VAL(ARM_SMCCC_FAST_CALL, ARM_SMCCC_SMC_32, \
			   ARM_SMCCC_OWNER_TRUSTED_OS_END, \
			   OPTEE_SMC_FUNCID_CALLS_REVISION)

काष्ठा optee_smc_calls_revision_result अणु
	अचिन्हित दीर्घ major;
	अचिन्हित दीर्घ minor;
	अचिन्हित दीर्घ reserved0;
	अचिन्हित दीर्घ reserved1;
पूर्ण;

/*
 * Get UUID of Trusted OS.
 *
 * Used by non-secure world to figure out which Trusted OS is installed.
 * Note that वापसed UUID is the UUID of the Trusted OS, not of the API.
 *
 * Returns UUID in a0-4 in the same way as OPTEE_SMC_CALLS_UID
 * described above.
 */
#घोषणा OPTEE_SMC_FUNCID_GET_OS_UUID OPTEE_MSG_FUNCID_GET_OS_UUID
#घोषणा OPTEE_SMC_CALL_GET_OS_UUID \
	OPTEE_SMC_FAST_CALL_VAL(OPTEE_SMC_FUNCID_GET_OS_UUID)

/*
 * Get revision of Trusted OS.
 *
 * Used by non-secure world to figure out which version of the Trusted OS
 * is installed. Note that the वापसed revision is the revision of the
 * Trusted OS, not of the API.
 *
 * Returns revision in a0-1 in the same way as OPTEE_SMC_CALLS_REVISION
 * described above. May optionally वापस a 32-bit build identअगरier in a2,
 * with zero meaning unspecअगरied.
 */
#घोषणा OPTEE_SMC_FUNCID_GET_OS_REVISION OPTEE_MSG_FUNCID_GET_OS_REVISION
#घोषणा OPTEE_SMC_CALL_GET_OS_REVISION \
	OPTEE_SMC_FAST_CALL_VAL(OPTEE_SMC_FUNCID_GET_OS_REVISION)

काष्ठा optee_smc_call_get_os_revision_result अणु
	अचिन्हित दीर्घ major;
	अचिन्हित दीर्घ minor;
	अचिन्हित दीर्घ build_id;
	अचिन्हित दीर्घ reserved1;
पूर्ण;

/*
 * Call with काष्ठा optee_msg_arg as argument
 *
 * Call रेजिस्टर usage:
 * a0	SMC Function ID, OPTEE_SMC*CALL_WITH_ARG
 * a1	Upper 32 bits of a 64-bit physical poपूर्णांकer to a काष्ठा optee_msg_arg
 * a2	Lower 32 bits of a 64-bit physical poपूर्णांकer to a काष्ठा optee_msg_arg
 * a3	Cache settings, not used अगर physical poपूर्णांकer is in a predefined shared
 *	memory area अन्यथा per OPTEE_SMC_SHM_*
 * a4-6	Not used
 * a7	Hypervisor Client ID रेजिस्टर
 *
 * Normal वापस रेजिस्टर usage:
 * a0	Return value, OPTEE_SMC_RETURN_*
 * a1-3	Not used
 * a4-7	Preserved
 *
 * OPTEE_SMC_RETURN_ETHREAD_LIMIT वापस रेजिस्टर usage:
 * a0	Return value, OPTEE_SMC_RETURN_ETHREAD_LIMIT
 * a1-3	Preserved
 * a4-7	Preserved
 *
 * RPC वापस रेजिस्टर usage:
 * a0	Return value, OPTEE_SMC_RETURN_IS_RPC(val)
 * a1-2	RPC parameters
 * a3-7	Resume inक्रमmation, must be preserved
 *
 * Possible वापस values:
 * OPTEE_SMC_RETURN_UNKNOWN_FUNCTION	Trusted OS करोes not recognize this
 *					function.
 * OPTEE_SMC_RETURN_OK			Call completed, result updated in
 *					the previously supplied काष्ठा
 *					optee_msg_arg.
 * OPTEE_SMC_RETURN_ETHREAD_LIMIT	Number of Trusted OS thपढ़ोs exceeded,
 *					try again later.
 * OPTEE_SMC_RETURN_EBADADDR		Bad physical poपूर्णांकer to काष्ठा
 *					optee_msg_arg.
 * OPTEE_SMC_RETURN_EBADCMD		Bad/unknown cmd in काष्ठा optee_msg_arg
 * OPTEE_SMC_RETURN_IS_RPC()		Call suspended by RPC call to normal
 *					world.
 */
#घोषणा OPTEE_SMC_FUNCID_CALL_WITH_ARG OPTEE_MSG_FUNCID_CALL_WITH_ARG
#घोषणा OPTEE_SMC_CALL_WITH_ARG \
	OPTEE_SMC_STD_CALL_VAL(OPTEE_SMC_FUNCID_CALL_WITH_ARG)

/*
 * Get Shared Memory Config
 *
 * Returns the Secure/Non-secure shared memory config.
 *
 * Call रेजिस्टर usage:
 * a0	SMC Function ID, OPTEE_SMC_GET_SHM_CONFIG
 * a1-6	Not used
 * a7	Hypervisor Client ID रेजिस्टर
 *
 * Have config वापस रेजिस्टर usage:
 * a0	OPTEE_SMC_RETURN_OK
 * a1	Physical address of start of SHM
 * a2	Size of of SHM
 * a3	Cache settings of memory, as defined by the
 *	OPTEE_SMC_SHM_* values above
 * a4-7	Preserved
 *
 * Not available रेजिस्टर usage:
 * a0	OPTEE_SMC_RETURN_ENOTAVAIL
 * a1-3 Not used
 * a4-7	Preserved
 */
#घोषणा OPTEE_SMC_FUNCID_GET_SHM_CONFIG	7
#घोषणा OPTEE_SMC_GET_SHM_CONFIG \
	OPTEE_SMC_FAST_CALL_VAL(OPTEE_SMC_FUNCID_GET_SHM_CONFIG)

काष्ठा optee_smc_get_shm_config_result अणु
	अचिन्हित दीर्घ status;
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ settings;
पूर्ण;

/*
 * Exchanges capabilities between normal world and secure world
 *
 * Call रेजिस्टर usage:
 * a0	SMC Function ID, OPTEE_SMC_EXCHANGE_CAPABILITIES
 * a1	bitfield of normal world capabilities OPTEE_SMC_NSEC_CAP_*
 * a2-6	Not used
 * a7	Hypervisor Client ID रेजिस्टर
 *
 * Normal वापस रेजिस्टर usage:
 * a0	OPTEE_SMC_RETURN_OK
 * a1	bitfield of secure world capabilities OPTEE_SMC_SEC_CAP_*
 * a2-7	Preserved
 *
 * Error वापस रेजिस्टर usage:
 * a0	OPTEE_SMC_RETURN_ENOTAVAIL, can't use the capabilities from normal world
 * a1	bitfield of secure world capabilities OPTEE_SMC_SEC_CAP_*
 * a2-7 Preserved
 */
/* Normal world works as a uniprocessor प्रणाली */
#घोषणा OPTEE_SMC_NSEC_CAP_UNIPROCESSOR		BIT(0)
/* Secure world has reserved shared memory क्रम normal world to use */
#घोषणा OPTEE_SMC_SEC_CAP_HAVE_RESERVED_SHM	BIT(0)
/* Secure world can communicate via previously unरेजिस्टरed shared memory */
#घोषणा OPTEE_SMC_SEC_CAP_UNREGISTERED_SHM	BIT(1)

/*
 * Secure world supports commands "register/unregister shared memory",
 * secure world accepts command buffers located in any parts of non-secure RAM
 */
#घोषणा OPTEE_SMC_SEC_CAP_DYNAMIC_SHM		BIT(2)
/* Secure world is built with भवization support */
#घोषणा OPTEE_SMC_SEC_CAP_VIRTUALIZATION	BIT(3)
/* Secure world supports Shared Memory with a शून्य reference */
#घोषणा OPTEE_SMC_SEC_CAP_MEMREF_शून्य		BIT(4)

#घोषणा OPTEE_SMC_FUNCID_EXCHANGE_CAPABILITIES	9
#घोषणा OPTEE_SMC_EXCHANGE_CAPABILITIES \
	OPTEE_SMC_FAST_CALL_VAL(OPTEE_SMC_FUNCID_EXCHANGE_CAPABILITIES)

काष्ठा optee_smc_exchange_capabilities_result अणु
	अचिन्हित दीर्घ status;
	अचिन्हित दीर्घ capabilities;
	अचिन्हित दीर्घ reserved0;
	अचिन्हित दीर्घ reserved1;
पूर्ण;

/*
 * Disable and empties cache of shared memory objects
 *
 * Secure world can cache frequently used shared memory objects, क्रम
 * example objects used as RPC arguments. When secure world is idle this
 * function वापसs one shared memory reference to मुक्त. To disable the
 * cache and मुक्त all cached objects this function has to be called until
 * it वापसs OPTEE_SMC_RETURN_ENOTAVAIL.
 *
 * Call रेजिस्टर usage:
 * a0	SMC Function ID, OPTEE_SMC_DISABLE_SHM_CACHE
 * a1-6	Not used
 * a7	Hypervisor Client ID रेजिस्टर
 *
 * Normal वापस रेजिस्टर usage:
 * a0	OPTEE_SMC_RETURN_OK
 * a1	Upper 32 bits of a 64-bit Shared memory cookie
 * a2	Lower 32 bits of a 64-bit Shared memory cookie
 * a3-7	Preserved
 *
 * Cache empty वापस रेजिस्टर usage:
 * a0	OPTEE_SMC_RETURN_ENOTAVAIL
 * a1-7	Preserved
 *
 * Not idle वापस रेजिस्टर usage:
 * a0	OPTEE_SMC_RETURN_EBUSY
 * a1-7	Preserved
 */
#घोषणा OPTEE_SMC_FUNCID_DISABLE_SHM_CACHE	10
#घोषणा OPTEE_SMC_DISABLE_SHM_CACHE \
	OPTEE_SMC_FAST_CALL_VAL(OPTEE_SMC_FUNCID_DISABLE_SHM_CACHE)

काष्ठा optee_smc_disable_shm_cache_result अणु
	अचिन्हित दीर्घ status;
	अचिन्हित दीर्घ shm_upper32;
	अचिन्हित दीर्घ shm_lower32;
	अचिन्हित दीर्घ reserved0;
पूर्ण;

/*
 * Enable cache of shared memory objects
 *
 * Secure world can cache frequently used shared memory objects, क्रम
 * example objects used as RPC arguments. When secure world is idle this
 * function वापसs OPTEE_SMC_RETURN_OK and the cache is enabled. If
 * secure world isn't idle OPTEE_SMC_RETURN_EBUSY is वापसed.
 *
 * Call रेजिस्टर usage:
 * a0	SMC Function ID, OPTEE_SMC_ENABLE_SHM_CACHE
 * a1-6	Not used
 * a7	Hypervisor Client ID रेजिस्टर
 *
 * Normal वापस रेजिस्टर usage:
 * a0	OPTEE_SMC_RETURN_OK
 * a1-7	Preserved
 *
 * Not idle वापस रेजिस्टर usage:
 * a0	OPTEE_SMC_RETURN_EBUSY
 * a1-7	Preserved
 */
#घोषणा OPTEE_SMC_FUNCID_ENABLE_SHM_CACHE	11
#घोषणा OPTEE_SMC_ENABLE_SHM_CACHE \
	OPTEE_SMC_FAST_CALL_VAL(OPTEE_SMC_FUNCID_ENABLE_SHM_CACHE)

/*
 * Query OP-TEE about number of supported thपढ़ोs
 *
 * Normal World OS or Hypervisor issues this call to find out how many
 * thपढ़ोs OP-TEE supports. That is how many standard calls can be issued
 * in parallel beक्रमe OP-TEE will वापस OPTEE_SMC_RETURN_ETHREAD_LIMIT.
 *
 * Call requests usage:
 * a0	SMC Function ID, OPTEE_SMC_GET_THREAD_COUNT
 * a1-6 Not used
 * a7	Hypervisor Client ID रेजिस्टर
 *
 * Normal वापस रेजिस्टर usage:
 * a0	OPTEE_SMC_RETURN_OK
 * a1	Number of thपढ़ोs
 * a2-7 Preserved
 *
 * Error वापस:
 * a0	OPTEE_SMC_RETURN_UNKNOWN_FUNCTION   Requested call is not implemented
 * a1-7	Preserved
 */
#घोषणा OPTEE_SMC_FUNCID_GET_THREAD_COUNT	15
#घोषणा OPTEE_SMC_GET_THREAD_COUNT \
	OPTEE_SMC_FAST_CALL_VAL(OPTEE_SMC_FUNCID_GET_THREAD_COUNT)

/*
 * Resume from RPC (क्रम example after processing a क्रमeign पूर्णांकerrupt)
 *
 * Call रेजिस्टर usage:
 * a0	SMC Function ID, OPTEE_SMC_CALL_RETURN_FROM_RPC
 * a1-3	Value of a1-3 when OPTEE_SMC_CALL_WITH_ARG वापसed
 *	OPTEE_SMC_RETURN_RPC in a0
 *
 * Return रेजिस्टर usage is the same as क्रम OPTEE_SMC_*CALL_WITH_ARG above.
 *
 * Possible वापस values
 * OPTEE_SMC_RETURN_UNKNOWN_FUNCTION	Trusted OS करोes not recognize this
 *					function.
 * OPTEE_SMC_RETURN_OK			Original call completed, result
 *					updated in the previously supplied.
 *					काष्ठा optee_msg_arg
 * OPTEE_SMC_RETURN_RPC			Call suspended by RPC call to normal
 *					world.
 * OPTEE_SMC_RETURN_ERESUME		Resume failed, the opaque resume
 *					inक्रमmation was corrupt.
 */
#घोषणा OPTEE_SMC_FUNCID_RETURN_FROM_RPC	3
#घोषणा OPTEE_SMC_CALL_RETURN_FROM_RPC \
	OPTEE_SMC_STD_CALL_VAL(OPTEE_SMC_FUNCID_RETURN_FROM_RPC)

#घोषणा OPTEE_SMC_RETURN_RPC_PREFIX_MASK	0xFFFF0000
#घोषणा OPTEE_SMC_RETURN_RPC_PREFIX		0xFFFF0000
#घोषणा OPTEE_SMC_RETURN_RPC_FUNC_MASK		0x0000FFFF

#घोषणा OPTEE_SMC_RETURN_GET_RPC_FUNC(ret) \
	((ret) & OPTEE_SMC_RETURN_RPC_FUNC_MASK)

#घोषणा OPTEE_SMC_RPC_VAL(func)		((func) | OPTEE_SMC_RETURN_RPC_PREFIX)

/*
 * Allocate memory क्रम RPC parameter passing. The memory is used to hold a
 * काष्ठा optee_msg_arg.
 *
 * "Call" रेजिस्टर usage:
 * a0	This value, OPTEE_SMC_RETURN_RPC_ALLOC
 * a1	Size in bytes of required argument memory
 * a2	Not used
 * a3	Resume inक्रमmation, must be preserved
 * a4-5	Not used
 * a6-7	Resume inक्रमmation, must be preserved
 *
 * "Return" रेजिस्टर usage:
 * a0	SMC Function ID, OPTEE_SMC_CALL_RETURN_FROM_RPC.
 * a1	Upper 32 bits of 64-bit physical poपूर्णांकer to allocated
 *	memory, (a1 == 0 && a2 == 0) अगर size was 0 or अगर memory can't
 *	be allocated.
 * a2	Lower 32 bits of 64-bit physical poपूर्णांकer to allocated
 *	memory, (a1 == 0 && a2 == 0) अगर size was 0 or अगर memory can't
 *	be allocated
 * a3	Preserved
 * a4	Upper 32 bits of 64-bit Shared memory cookie used when मुक्तing
 *	the memory or करोing an RPC
 * a5	Lower 32 bits of 64-bit Shared memory cookie used when मुक्तing
 *	the memory or करोing an RPC
 * a6-7	Preserved
 */
#घोषणा OPTEE_SMC_RPC_FUNC_ALLOC	0
#घोषणा OPTEE_SMC_RETURN_RPC_ALLOC \
	OPTEE_SMC_RPC_VAL(OPTEE_SMC_RPC_FUNC_ALLOC)

/*
 * Free memory previously allocated by OPTEE_SMC_RETURN_RPC_ALLOC
 *
 * "Call" रेजिस्टर usage:
 * a0	This value, OPTEE_SMC_RETURN_RPC_FREE
 * a1	Upper 32 bits of 64-bit shared memory cookie beदीर्घing to this
 *	argument memory
 * a2	Lower 32 bits of 64-bit shared memory cookie beदीर्घing to this
 *	argument memory
 * a3-7	Resume inक्रमmation, must be preserved
 *
 * "Return" रेजिस्टर usage:
 * a0	SMC Function ID, OPTEE_SMC_CALL_RETURN_FROM_RPC.
 * a1-2	Not used
 * a3-7	Preserved
 */
#घोषणा OPTEE_SMC_RPC_FUNC_FREE		2
#घोषणा OPTEE_SMC_RETURN_RPC_FREE \
	OPTEE_SMC_RPC_VAL(OPTEE_SMC_RPC_FUNC_FREE)

/*
 * Deliver a क्रमeign पूर्णांकerrupt in normal world.
 *
 * "Call" रेजिस्टर usage:
 * a0	OPTEE_SMC_RETURN_RPC_FOREIGN_INTR
 * a1-7	Resume inक्रमmation, must be preserved
 *
 * "Return" रेजिस्टर usage:
 * a0	SMC Function ID, OPTEE_SMC_CALL_RETURN_FROM_RPC.
 * a1-7	Preserved
 */
#घोषणा OPTEE_SMC_RPC_FUNC_FOREIGN_INTR	4
#घोषणा OPTEE_SMC_RETURN_RPC_FOREIGN_INTR \
	OPTEE_SMC_RPC_VAL(OPTEE_SMC_RPC_FUNC_FOREIGN_INTR)

/*
 * Do an RPC request. The supplied काष्ठा optee_msg_arg tells which
 * request to करो and the parameters क्रम the request. The following fields
 * are used (the rest are unused):
 * - cmd		the Request ID
 * - ret		वापस value of the request, filled in by normal world
 * - num_params		number of parameters क्रम the request
 * - params		the parameters
 * - param_attrs	attributes of the parameters
 *
 * "Call" रेजिस्टर usage:
 * a0	OPTEE_SMC_RETURN_RPC_CMD
 * a1	Upper 32 bits of a 64-bit Shared memory cookie holding a
 *	काष्ठा optee_msg_arg, must be preserved, only the data should
 *	be updated
 * a2	Lower 32 bits of a 64-bit Shared memory cookie holding a
 *	काष्ठा optee_msg_arg, must be preserved, only the data should
 *	be updated
 * a3-7	Resume inक्रमmation, must be preserved
 *
 * "Return" रेजिस्टर usage:
 * a0	SMC Function ID, OPTEE_SMC_CALL_RETURN_FROM_RPC.
 * a1-2	Not used
 * a3-7	Preserved
 */
#घोषणा OPTEE_SMC_RPC_FUNC_CMD		5
#घोषणा OPTEE_SMC_RETURN_RPC_CMD \
	OPTEE_SMC_RPC_VAL(OPTEE_SMC_RPC_FUNC_CMD)

/* Returned in a0 */
#घोषणा OPTEE_SMC_RETURN_UNKNOWN_FUNCTION 0xFFFFFFFF

/* Returned in a0 only from Trusted OS functions */
#घोषणा OPTEE_SMC_RETURN_OK		0x0
#घोषणा OPTEE_SMC_RETURN_ETHREAD_LIMIT	0x1
#घोषणा OPTEE_SMC_RETURN_EBUSY		0x2
#घोषणा OPTEE_SMC_RETURN_ERESUME	0x3
#घोषणा OPTEE_SMC_RETURN_EBADADDR	0x4
#घोषणा OPTEE_SMC_RETURN_EBADCMD	0x5
#घोषणा OPTEE_SMC_RETURN_ENOMEM		0x6
#घोषणा OPTEE_SMC_RETURN_ENOTAVAIL	0x7
#घोषणा OPTEE_SMC_RETURN_IS_RPC(ret)	__optee_smc_वापस_is_rpc((ret))

अटल अंतरभूत bool __optee_smc_वापस_is_rpc(u32 ret)
अणु
	वापस ret != OPTEE_SMC_RETURN_UNKNOWN_FUNCTION &&
	       (ret & OPTEE_SMC_RETURN_RPC_PREFIX_MASK) ==
			OPTEE_SMC_RETURN_RPC_PREFIX;
पूर्ण

#पूर्ण_अगर /* OPTEE_SMC_H */
