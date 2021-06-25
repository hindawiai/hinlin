<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-2-Clause) */
/*
 * Copyright (c) 2015-2021, Linaro Limited
 */
#अगर_अघोषित _OPTEE_MSG_H
#घोषणा _OPTEE_MSG_H

#समावेश <linux/bitops.h>
#समावेश <linux/types.h>

/*
 * This file defines the OP-TEE message protocol (ABI) used to communicate
 * with an instance of OP-TEE running in secure world.
 *
 * This file is भागided पूर्णांकo two sections.
 * 1. Formatting of messages.
 * 2. Requests from normal world
 */

/*****************************************************************************
 * Part 1 - क्रमmatting of messages
 *****************************************************************************/

#घोषणा OPTEE_MSG_ATTR_TYPE_NONE		0x0
#घोषणा OPTEE_MSG_ATTR_TYPE_VALUE_INPUT		0x1
#घोषणा OPTEE_MSG_ATTR_TYPE_VALUE_OUTPUT	0x2
#घोषणा OPTEE_MSG_ATTR_TYPE_VALUE_INOUT		0x3
#घोषणा OPTEE_MSG_ATTR_TYPE_RMEM_INPUT		0x5
#घोषणा OPTEE_MSG_ATTR_TYPE_RMEM_OUTPUT		0x6
#घोषणा OPTEE_MSG_ATTR_TYPE_RMEM_INOUT		0x7
#घोषणा OPTEE_MSG_ATTR_TYPE_TMEM_INPUT		0x9
#घोषणा OPTEE_MSG_ATTR_TYPE_TMEM_OUTPUT		0xa
#घोषणा OPTEE_MSG_ATTR_TYPE_TMEM_INOUT		0xb

#घोषणा OPTEE_MSG_ATTR_TYPE_MASK		GENMASK(7, 0)

/*
 * Meta parameter to be असलorbed by the Secure OS and not passed
 * to the Trusted Application.
 *
 * Currently only used with OPTEE_MSG_CMD_OPEN_SESSION.
 */
#घोषणा OPTEE_MSG_ATTR_META			BIT(8)

/*
 * Poपूर्णांकer to a list of pages used to रेजिस्टर user-defined SHM buffer.
 * Used with OPTEE_MSG_ATTR_TYPE_TMEM_*.
 * buf_ptr should poपूर्णांक to the beginning of the buffer. Buffer will contain
 * list of page addresses. OP-TEE core can reस्थिरruct contiguous buffer from
 * that page addresses list. Page addresses are stored as 64 bit values.
 * Last entry on a page should poपूर्णांक to the next page of buffer.
 * Every entry in buffer should poपूर्णांक to a 4k page beginning (12 least
 * signअगरicant bits must be equal to zero).
 *
 * 12 least signअगरicant bits of optee_msg_param.u.पंचांगem.buf_ptr should hold
 * page offset of user buffer.
 *
 * So, entries should be placed like members of this काष्ठाure:
 *
 * काष्ठा page_data अणु
 *   uपूर्णांक64_t pages_array[OPTEE_MSG_NONCONTIG_PAGE_SIZE/माप(uपूर्णांक64_t) - 1];
 *   uपूर्णांक64_t next_page_data;
 * पूर्ण;
 *
 * Structure is deचिन्हित to exactly fit पूर्णांकo the page size
 * OPTEE_MSG_NONCONTIG_PAGE_SIZE which is a standard 4KB page.
 *
 * The size of 4KB is chosen because this is the smallest page size क्रम ARM
 * architectures. If REE uses larger pages, it should भागide them to 4KB ones.
 */
#घोषणा OPTEE_MSG_ATTR_NONCONTIG		BIT(9)

/*
 * Memory attributes क्रम caching passed with temp memrefs. The actual value
 * used is defined outside the message protocol with the exception of
 * OPTEE_MSG_ATTR_CACHE_PREDEFINED which means the attributes alपढ़ोy
 * defined क्रम the memory range should be used. If optee_smc.h is used as
 * bearer of this protocol OPTEE_SMC_SHM_* is used क्रम values.
 */
#घोषणा OPTEE_MSG_ATTR_CACHE_SHIFT		16
#घोषणा OPTEE_MSG_ATTR_CACHE_MASK		GENMASK(2, 0)
#घोषणा OPTEE_MSG_ATTR_CACHE_PREDEFINED		0

/*
 * Same values as TEE_LOGIN_* from TEE Internal API
 */
#घोषणा OPTEE_MSG_LOGIN_PUBLIC			0x00000000
#घोषणा OPTEE_MSG_LOGIN_USER			0x00000001
#घोषणा OPTEE_MSG_LOGIN_GROUP			0x00000002
#घोषणा OPTEE_MSG_LOGIN_APPLICATION		0x00000004
#घोषणा OPTEE_MSG_LOGIN_APPLICATION_USER	0x00000005
#घोषणा OPTEE_MSG_LOGIN_APPLICATION_GROUP	0x00000006

/*
 * Page size used in non-contiguous buffer entries
 */
#घोषणा OPTEE_MSG_NONCONTIG_PAGE_SIZE		4096

/**
 * काष्ठा optee_msg_param_पंचांगem - temporary memory reference parameter
 * @buf_ptr:	Address of the buffer
 * @size:	Size of the buffer
 * @shm_ref:	Temporary shared memory reference, poपूर्णांकer to a काष्ठा tee_shm
 *
 * Secure and normal world communicates poपूर्णांकers as physical address
 * instead of the भव address. This is because secure and normal world
 * have completely independent memory mapping. Normal world can even have a
 * hypervisor which need to translate the guest physical address (AKA IPA
 * in ARM करोcumentation) to a real physical address beक्रमe passing the
 * काष्ठाure to secure world.
 */
काष्ठा optee_msg_param_पंचांगem अणु
	u64 buf_ptr;
	u64 size;
	u64 shm_ref;
पूर्ण;

/**
 * काष्ठा optee_msg_param_rmem - रेजिस्टरed memory reference parameter
 * @offs:	Offset पूर्णांकo shared memory reference
 * @size:	Size of the buffer
 * @shm_ref:	Shared memory reference, poपूर्णांकer to a काष्ठा tee_shm
 */
काष्ठा optee_msg_param_rmem अणु
	u64 offs;
	u64 size;
	u64 shm_ref;
पूर्ण;

/**
 * काष्ठा optee_msg_param_value - opaque value parameter
 *
 * Value parameters are passed unchecked between normal and secure world.
 */
काष्ठा optee_msg_param_value अणु
	u64 a;
	u64 b;
	u64 c;
पूर्ण;

/**
 * काष्ठा optee_msg_param - parameter used together with काष्ठा optee_msg_arg
 * @attr:	attributes
 * @पंचांगem:	parameter by temporary memory reference
 * @rmem:	parameter by रेजिस्टरed memory reference
 * @value:	parameter by opaque value
 * @octets:	parameter by octet string
 *
 * @attr & OPTEE_MSG_ATTR_TYPE_MASK indicates अगर पंचांगem, rmem or value is used in
 * the जोड़. OPTEE_MSG_ATTR_TYPE_VALUE_* indicates value or octets,
 * OPTEE_MSG_ATTR_TYPE_TMEM_* indicates @पंचांगem and
 * OPTEE_MSG_ATTR_TYPE_RMEM_* indicates @rmem,
 * OPTEE_MSG_ATTR_TYPE_NONE indicates that none of the members are used.
 */
काष्ठा optee_msg_param अणु
	u64 attr;
	जोड़ अणु
		काष्ठा optee_msg_param_पंचांगem पंचांगem;
		काष्ठा optee_msg_param_rmem rmem;
		काष्ठा optee_msg_param_value value;
		u8 octets[24];
	पूर्ण u;
पूर्ण;

/**
 * काष्ठा optee_msg_arg - call argument
 * @cmd: Command, one of OPTEE_MSG_CMD_* or OPTEE_MSG_RPC_CMD_*
 * @func: Trusted Application function, specअगरic to the Trusted Application,
 *	     used अगर cmd == OPTEE_MSG_CMD_INVOKE_COMMAND
 * @session: In parameter क्रम all OPTEE_MSG_CMD_* except
 *	     OPTEE_MSG_CMD_OPEN_SESSION where it's an output parameter instead
 * @cancel_id: Cancellation id, a unique value to identअगरy this request
 * @ret: वापस value
 * @ret_origin: origin of the वापस value
 * @num_params: number of parameters supplied to the OS Command
 * @params: the parameters supplied to the OS Command
 *
 * All normal calls to Trusted OS uses this काष्ठा. If cmd requires further
 * inक्रमmation than what these fields hold it can be passed as a parameter
 * tagged as meta (setting the OPTEE_MSG_ATTR_META bit in corresponding
 * attrs field). All parameters tagged as meta have to come first.
 */
काष्ठा optee_msg_arg अणु
	u32 cmd;
	u32 func;
	u32 session;
	u32 cancel_id;
	u32 pad;
	u32 ret;
	u32 ret_origin;
	u32 num_params;

	/* num_params tells the actual number of element in params */
	काष्ठा optee_msg_param params[];
पूर्ण;

/**
 * OPTEE_MSG_GET_ARG_SIZE - वापस size of काष्ठा optee_msg_arg
 *
 * @num_params: Number of parameters embedded in the काष्ठा optee_msg_arg
 *
 * Returns the size of the काष्ठा optee_msg_arg together with the number
 * of embedded parameters.
 */
#घोषणा OPTEE_MSG_GET_ARG_SIZE(num_params) \
	(माप(काष्ठा optee_msg_arg) + \
	 माप(काष्ठा optee_msg_param) * (num_params))

/*****************************************************************************
 * Part 2 - requests from normal world
 *****************************************************************************/

/*
 * Return the following UID अगर using API specअगरied in this file without
 * further extensions:
 * 384fb3e0-e7f8-11e3-af63-0002a5d5c51b.
 * Represented in 4 32-bit words in OPTEE_MSG_UID_0, OPTEE_MSG_UID_1,
 * OPTEE_MSG_UID_2, OPTEE_MSG_UID_3.
 */
#घोषणा OPTEE_MSG_UID_0			0x384fb3e0
#घोषणा OPTEE_MSG_UID_1			0xe7f811e3
#घोषणा OPTEE_MSG_UID_2			0xaf630002
#घोषणा OPTEE_MSG_UID_3			0xa5d5c51b
#घोषणा OPTEE_MSG_FUNCID_CALLS_UID	0xFF01

/*
 * Returns 2.0 अगर using API specअगरied in this file without further
 * extensions. Represented in 2 32-bit words in OPTEE_MSG_REVISION_MAJOR
 * and OPTEE_MSG_REVISION_MINOR
 */
#घोषणा OPTEE_MSG_REVISION_MAJOR	2
#घोषणा OPTEE_MSG_REVISION_MINOR	0
#घोषणा OPTEE_MSG_FUNCID_CALLS_REVISION	0xFF03

/*
 * Get UUID of Trusted OS.
 *
 * Used by non-secure world to figure out which Trusted OS is installed.
 * Note that वापसed UUID is the UUID of the Trusted OS, not of the API.
 *
 * Returns UUID in 4 32-bit words in the same way as
 * OPTEE_MSG_FUNCID_CALLS_UID described above.
 */
#घोषणा OPTEE_MSG_OS_OPTEE_UUID_0	0x486178e0
#घोषणा OPTEE_MSG_OS_OPTEE_UUID_1	0xe7f811e3
#घोषणा OPTEE_MSG_OS_OPTEE_UUID_2	0xbc5e0002
#घोषणा OPTEE_MSG_OS_OPTEE_UUID_3	0xa5d5c51b
#घोषणा OPTEE_MSG_FUNCID_GET_OS_UUID	0x0000

/*
 * Get revision of Trusted OS.
 *
 * Used by non-secure world to figure out which version of the Trusted OS
 * is installed. Note that the वापसed revision is the revision of the
 * Trusted OS, not of the API.
 *
 * Returns revision in 2 32-bit words in the same way as
 * OPTEE_MSG_CALLS_REVISION described above.
 */
#घोषणा OPTEE_MSG_FUNCID_GET_OS_REVISION	0x0001

/*
 * Do a secure call with काष्ठा optee_msg_arg as argument
 * The OPTEE_MSG_CMD_* below defines what goes in काष्ठा optee_msg_arg::cmd
 *
 * OPTEE_MSG_CMD_OPEN_SESSION खोलोs a session to a Trusted Application.
 * The first two parameters are tagged as meta, holding two value
 * parameters to pass the following inक्रमmation:
 * param[0].u.value.a-b uuid of Trusted Application
 * param[1].u.value.a-b uuid of Client
 * param[1].u.value.c Login class of client OPTEE_MSG_LOGIN_*
 *
 * OPTEE_MSG_CMD_INVOKE_COMMAND invokes a command a previously खोलोed
 * session to a Trusted Application.  काष्ठा optee_msg_arg::func is Trusted
 * Application function, specअगरic to the Trusted Application.
 *
 * OPTEE_MSG_CMD_CLOSE_SESSION बंदs a previously खोलोed session to
 * Trusted Application.
 *
 * OPTEE_MSG_CMD_CANCEL cancels a currently invoked command.
 *
 * OPTEE_MSG_CMD_REGISTER_SHM रेजिस्टरs a shared memory reference. The
 * inक्रमmation is passed as:
 * [in] param[0].attr			OPTEE_MSG_ATTR_TYPE_TMEM_INPUT
 *					[| OPTEE_MSG_ATTR_NONCONTIG]
 * [in] param[0].u.पंचांगem.buf_ptr		physical address (of first fragment)
 * [in] param[0].u.पंचांगem.size		size (of first fragment)
 * [in] param[0].u.पंचांगem.shm_ref		holds shared memory reference
 *
 * OPTEE_MSG_CMD_UNREGISTER_SHM unरेजिस्टरs a previously रेजिस्टरed shared
 * memory reference. The inक्रमmation is passed as:
 * [in] param[0].attr			OPTEE_MSG_ATTR_TYPE_RMEM_INPUT
 * [in] param[0].u.rmem.shm_ref		holds shared memory reference
 * [in] param[0].u.rmem.offs		0
 * [in] param[0].u.rmem.size		0
 */
#घोषणा OPTEE_MSG_CMD_OPEN_SESSION	0
#घोषणा OPTEE_MSG_CMD_INVOKE_COMMAND	1
#घोषणा OPTEE_MSG_CMD_CLOSE_SESSION	2
#घोषणा OPTEE_MSG_CMD_CANCEL		3
#घोषणा OPTEE_MSG_CMD_REGISTER_SHM	4
#घोषणा OPTEE_MSG_CMD_UNREGISTER_SHM	5
#घोषणा OPTEE_MSG_FUNCID_CALL_WITH_ARG	0x0004

#पूर्ण_अगर /* _OPTEE_MSG_H */
