<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/**
 * Copyright(c) 2016-20 Intel Corporation.
 *
 * Intel Software Guard Extensions (SGX) support.
 */
#अगर_अघोषित _ASM_X86_SGX_H
#घोषणा _ASM_X86_SGX_H

#समावेश <linux/bits.h>
#समावेश <linux/types.h>

/*
 * This file contains both data काष्ठाures defined by SGX architecture and Linux
 * defined software data काष्ठाures and functions.  The two should not be mixed
 * together क्रम better पढ़ोibility.  The architectural definitions come first.
 */

/* The SGX specअगरic CPUID function. */
#घोषणा SGX_CPUID		0x12
/* EPC क्रमागतeration. */
#घोषणा SGX_CPUID_EPC		2
/* An invalid EPC section, i.e. the end marker. */
#घोषणा SGX_CPUID_EPC_INVALID	0x0
/* A valid EPC section. */
#घोषणा SGX_CPUID_EPC_SECTION	0x1
/* The biपंचांगask क्रम the EPC section type. */
#घोषणा SGX_CPUID_EPC_MASK	GENMASK(3, 0)

क्रमागत sgx_encls_function अणु
	ECREATE	= 0x00,
	EADD	= 0x01,
	EINIT	= 0x02,
	EREMOVE	= 0x03,
	EDGBRD	= 0x04,
	EDGBWR	= 0x05,
	EEXTEND	= 0x06,
	ELDU	= 0x08,
	EBLOCK	= 0x09,
	EPA	= 0x0A,
	EWB	= 0x0B,
	ETRACK	= 0x0C,
	EAUG	= 0x0D,
	EMODPR	= 0x0E,
	EMODT	= 0x0F,
पूर्ण;

/**
 * क्रमागत sgx_वापस_code - The वापस code type क्रम ENCLS, ENCLU and ENCLV
 * %SGX_NOT_TRACKED:		Previous ETRACK's shootकरोwn sequence has not
 *				been completed yet.
 * %SGX_CHILD_PRESENT		SECS has child pages present in the EPC.
 * %SGX_INVALID_EINITTOKEN:	EINITTOKEN is invalid and enclave signer's
 *				खुला key करोes not match IA32_SGXLEPUBKEYHASH.
 * %SGX_UNMASKED_EVENT:		An unmasked event, e.g. INTR, was received
 */
क्रमागत sgx_वापस_code अणु
	SGX_NOT_TRACKED			= 11,
	SGX_CHILD_PRESENT		= 13,
	SGX_INVALID_EINITTOKEN		= 16,
	SGX_UNMASKED_EVENT		= 128,
पूर्ण;

/* The modulus size क्रम 3072-bit RSA keys. */
#घोषणा SGX_MODULUS_SIZE 384

/**
 * क्रमागत sgx_miscselect - additional inक्रमmation to an SSA frame
 * %SGX_MISC_EXINFO:	Report #PF or #GP to the SSA frame.
 *
 * Save State Area (SSA) is a stack inside the enclave used to store processor
 * state when an exception or पूर्णांकerrupt occurs. This क्रमागत defines additional
 * inक्रमmation stored to an SSA frame.
 */
क्रमागत sgx_miscselect अणु
	SGX_MISC_EXINFO		= BIT(0),
पूर्ण;

#घोषणा SGX_MISC_RESERVED_MASK	GENMASK_ULL(63, 1)

#घोषणा SGX_SSA_GPRS_SIZE		184
#घोषणा SGX_SSA_MISC_EXINFO_SIZE	16

/**
 * क्रमागत sgx_attributes - the attributes field in &काष्ठा sgx_secs
 * %SGX_ATTR_INIT:		Enclave can be entered (is initialized).
 * %SGX_ATTR_DEBUG:		Allow ENCLS(EDBGRD) and ENCLS(EDBGWR).
 * %SGX_ATTR_MODE64BIT:		Tell that this a 64-bit enclave.
 * %SGX_ATTR_PROVISIONKEY:      Allow to use provisioning keys क्रम remote
 *				attestation.
 * %SGX_ATTR_KSS:		Allow to use key separation and sharing (KSS).
 * %SGX_ATTR_EINITTOKENKEY:	Allow to use token signing key that is used to
 *				sign cryptographic tokens that can be passed to
 *				EINIT as an authorization to run an enclave.
 */
क्रमागत sgx_attribute अणु
	SGX_ATTR_INIT		= BIT(0),
	SGX_ATTR_DEBUG		= BIT(1),
	SGX_ATTR_MODE64BIT	= BIT(2),
	SGX_ATTR_PROVISIONKEY	= BIT(4),
	SGX_ATTR_EINITTOKENKEY	= BIT(5),
	SGX_ATTR_KSS		= BIT(7),
पूर्ण;

#घोषणा SGX_ATTR_RESERVED_MASK	(BIT_ULL(3) | BIT_ULL(6) | GENMASK_ULL(63, 8))

/**
 * काष्ठा sgx_secs - SGX Enclave Control Structure (SECS)
 * @size:		size of the address space
 * @base:		base address of the  address space
 * @ssa_frame_size:	size of an SSA frame
 * @miscselect:		additional inक्रमmation stored to an SSA frame
 * @attributes:		attributes क्रम enclave
 * @xfrm:		XSave-Feature Request Mask (subset of XCR0)
 * @mrenclave:		SHA256-hash of the enclave contents
 * @mrsigner:		SHA256-hash of the खुला key used to sign the SIGSTRUCT
 * @config_id:		a user-defined value that is used in key derivation
 * @isv_prod_id:	a user-defined value that is used in key derivation
 * @isv_svn:		a user-defined value that is used in key derivation
 * @config_svn:		a user-defined value that is used in key derivation
 *
 * SGX Enclave Control Structure (SECS) is a special enclave page that is not
 * visible in the address space. In fact, this काष्ठाure defines the address
 * range and other global attributes क्रम the enclave and it is the first EPC
 * page created क्रम any enclave. It is moved from a temporary buffer to an EPC
 * by the means of ENCLS[ECREATE] function.
 */
काष्ठा sgx_secs अणु
	u64 size;
	u64 base;
	u32 ssa_frame_size;
	u32 miscselect;
	u8  reserved1[24];
	u64 attributes;
	u64 xfrm;
	u32 mrenclave[8];
	u8  reserved2[32];
	u32 mrsigner[8];
	u8  reserved3[32];
	u32 config_id[16];
	u16 isv_prod_id;
	u16 isv_svn;
	u16 config_svn;
	u8  reserved4[3834];
पूर्ण __packed;

/**
 * क्रमागत sgx_tcs_flags - execution flags क्रम TCS
 * %SGX_TCS_DBGOPTIN:	If enabled allows single-stepping and अवरोधpoपूर्णांकs
 *			inside an enclave. It is cleared by EADD but can
 *			be set later with EDBGWR.
 */
क्रमागत sgx_tcs_flags अणु
	SGX_TCS_DBGOPTIN	= 0x01,
पूर्ण;

#घोषणा SGX_TCS_RESERVED_MASK	GENMASK_ULL(63, 1)
#घोषणा SGX_TCS_RESERVED_SIZE	4024

/**
 * काष्ठा sgx_tcs - Thपढ़ो Control Structure (TCS)
 * @state:		used to mark an entered TCS
 * @flags:		execution flags (cleared by EADD)
 * @ssa_offset:		SSA stack offset relative to the enclave base
 * @ssa_index:		the current SSA frame index (cleard by EADD)
 * @nr_ssa_frames:	the number of frame in the SSA stack
 * @entry_offset:	entry poपूर्णांक offset relative to the enclave base
 * @निकास_addr:		address outside the enclave to निकास on an exception or
 *			पूर्णांकerrupt
 * @fs_offset:		offset relative to the enclave base to become FS
 *			segment inside the enclave
 * @gs_offset:		offset relative to the enclave base to become GS
 *			segment inside the enclave
 * @fs_limit:		size to become a new FS-limit (only 32-bit enclaves)
 * @gs_limit:		size to become a new GS-limit (only 32-bit enclaves)
 *
 * Thपढ़ो Control Structure (TCS) is an enclave page visible in its address
 * space that defines an entry poपूर्णांक inside the enclave. A thपढ़ो enters inside
 * an enclave by supplying address of TCS to ENCLU(EENTER). A TCS can be entered
 * by only one thपढ़ो at a समय.
 */
काष्ठा sgx_tcs अणु
	u64 state;
	u64 flags;
	u64 ssa_offset;
	u32 ssa_index;
	u32 nr_ssa_frames;
	u64 entry_offset;
	u64 निकास_addr;
	u64 fs_offset;
	u64 gs_offset;
	u32 fs_limit;
	u32 gs_limit;
	u8  reserved[SGX_TCS_RESERVED_SIZE];
पूर्ण __packed;

/**
 * काष्ठा sgx_pageinfo - an enclave page descriptor
 * @addr:	address of the enclave page
 * @contents:	poपूर्णांकer to the page contents
 * @metadata:	poपूर्णांकer either to a SECINFO or PCMD instance
 * @secs:	address of the SECS page
 */
काष्ठा sgx_pageinfo अणु
	u64 addr;
	u64 contents;
	u64 metadata;
	u64 secs;
पूर्ण __packed __aligned(32);


/**
 * क्रमागत sgx_page_type - bits in the SECINFO flags defining the page type
 * %SGX_PAGE_TYPE_SECS:	a SECS page
 * %SGX_PAGE_TYPE_TCS:	a TCS page
 * %SGX_PAGE_TYPE_REG:	a regular page
 * %SGX_PAGE_TYPE_VA:	a VA page
 * %SGX_PAGE_TYPE_TRIM:	a page in trimmed state
 */
क्रमागत sgx_page_type अणु
	SGX_PAGE_TYPE_SECS,
	SGX_PAGE_TYPE_TCS,
	SGX_PAGE_TYPE_REG,
	SGX_PAGE_TYPE_VA,
	SGX_PAGE_TYPE_TRIM,
पूर्ण;

#घोषणा SGX_NR_PAGE_TYPES	5
#घोषणा SGX_PAGE_TYPE_MASK	GENMASK(7, 0)

/**
 * क्रमागत sgx_secinfo_flags - the flags field in &काष्ठा sgx_secinfo
 * %SGX_SECINFO_R:	allow पढ़ो
 * %SGX_SECINFO_W:	allow ग_लिखो
 * %SGX_SECINFO_X:	allow execution
 * %SGX_SECINFO_SECS:	a SECS page
 * %SGX_SECINFO_TCS:	a TCS page
 * %SGX_SECINFO_REG:	a regular page
 * %SGX_SECINFO_VA:	a VA page
 * %SGX_SECINFO_TRIM:	a page in trimmed state
 */
क्रमागत sgx_secinfo_flags अणु
	SGX_SECINFO_R			= BIT(0),
	SGX_SECINFO_W			= BIT(1),
	SGX_SECINFO_X			= BIT(2),
	SGX_SECINFO_SECS		= (SGX_PAGE_TYPE_SECS << 8),
	SGX_SECINFO_TCS			= (SGX_PAGE_TYPE_TCS << 8),
	SGX_SECINFO_REG			= (SGX_PAGE_TYPE_REG << 8),
	SGX_SECINFO_VA			= (SGX_PAGE_TYPE_VA << 8),
	SGX_SECINFO_TRIM		= (SGX_PAGE_TYPE_TRIM << 8),
पूर्ण;

#घोषणा SGX_SECINFO_PERMISSION_MASK	GENMASK_ULL(2, 0)
#घोषणा SGX_SECINFO_PAGE_TYPE_MASK	(SGX_PAGE_TYPE_MASK << 8)
#घोषणा SGX_SECINFO_RESERVED_MASK	~(SGX_SECINFO_PERMISSION_MASK | \
					  SGX_SECINFO_PAGE_TYPE_MASK)

/**
 * काष्ठा sgx_secinfo - describes attributes of an EPC page
 * @flags:	permissions and type
 *
 * Used together with ENCLS leaves that add or modअगरy an EPC page to an
 * enclave to define page permissions and type.
 */
काष्ठा sgx_secinfo अणु
	u64 flags;
	u8  reserved[56];
पूर्ण __packed __aligned(64);

#घोषणा SGX_PCMD_RESERVED_SIZE 40

/**
 * काष्ठा sgx_pcmd - Paging Crypto Metadata (PCMD)
 * @enclave_id:	enclave identअगरier
 * @mac:	MAC over PCMD, page contents and isvsvn
 *
 * PCMD is stored क्रम every swapped page to the regular memory. When ELDU loads
 * the page back it recalculates the MAC by using a isvsvn number stored in a
 * VA page. Together these two काष्ठाures bring पूर्णांकegrity and rollback
 * protection.
 */
काष्ठा sgx_pcmd अणु
	काष्ठा sgx_secinfo secinfo;
	u64 enclave_id;
	u8  reserved[SGX_PCMD_RESERVED_SIZE];
	u8  mac[16];
पूर्ण __packed __aligned(128);

#घोषणा SGX_SIGSTRUCT_RESERVED1_SIZE 84
#घोषणा SGX_SIGSTRUCT_RESERVED2_SIZE 20
#घोषणा SGX_SIGSTRUCT_RESERVED3_SIZE 32
#घोषणा SGX_SIGSTRUCT_RESERVED4_SIZE 12

/**
 * काष्ठा sgx_sigकाष्ठा_header -  defines author of the enclave
 * @header1:		स्थिरant byte string
 * @venकरोr:		must be either 0x0000 or 0x8086
 * @date:		YYYYMMDD in BCD
 * @header2:		स्थिरant byte string
 * @swdefined:		software defined value
 */
काष्ठा sgx_sigकाष्ठा_header अणु
	u64 header1[2];
	u32 venकरोr;
	u32 date;
	u64 header2[2];
	u32 swdefined;
	u8  reserved1[84];
पूर्ण __packed;

/**
 * काष्ठा sgx_sigकाष्ठा_body - defines contents of the enclave
 * @miscselect:		additional inक्रमmation stored to an SSA frame
 * @misc_mask:		required miscselect in SECS
 * @attributes:		attributes क्रम enclave
 * @xfrm:		XSave-Feature Request Mask (subset of XCR0)
 * @attributes_mask:	required attributes in SECS
 * @xfrm_mask:		required XFRM in SECS
 * @mrenclave:		SHA256-hash of the enclave contents
 * @isvprodid:		a user-defined value that is used in key derivation
 * @isvsvn:		a user-defined value that is used in key derivation
 */
काष्ठा sgx_sigकाष्ठा_body अणु
	u32 miscselect;
	u32 misc_mask;
	u8  reserved2[20];
	u64 attributes;
	u64 xfrm;
	u64 attributes_mask;
	u64 xfrm_mask;
	u8  mrenclave[32];
	u8  reserved3[32];
	u16 isvprodid;
	u16 isvsvn;
पूर्ण __packed;

/**
 * काष्ठा sgx_sigकाष्ठा - an enclave signature
 * @header:		defines author of the enclave
 * @modulus:		the modulus of the खुला key
 * @exponent:		the exponent of the खुला key
 * @signature:		the signature calculated over the fields except modulus,
 * @body:		defines contents of the enclave
 * @q1:			a value used in RSA signature verअगरication
 * @q2:			a value used in RSA signature verअगरication
 *
 * Header and body are the parts that are actual चिन्हित. The reमुख्यing fields
 * define the signature of the enclave.
 */
काष्ठा sgx_sigकाष्ठा अणु
	काष्ठा sgx_sigकाष्ठा_header header;
	u8  modulus[SGX_MODULUS_SIZE];
	u32 exponent;
	u8  signature[SGX_MODULUS_SIZE];
	काष्ठा sgx_sigकाष्ठा_body body;
	u8  reserved4[12];
	u8  q1[SGX_MODULUS_SIZE];
	u8  q2[SGX_MODULUS_SIZE];
पूर्ण __packed;

#घोषणा SGX_LAUNCH_TOKEN_SIZE 304

/*
 * Do not put any hardware-defined SGX काष्ठाure representations below this
 * comment!
 */

#अगर_घोषित CONFIG_X86_SGX_KVM
पूर्णांक sgx_virt_ecreate(काष्ठा sgx_pageinfo *pageinfo, व्योम __user *secs,
		     पूर्णांक *trapnr);
पूर्णांक sgx_virt_einit(व्योम __user *sigकाष्ठा, व्योम __user *token,
		   व्योम __user *secs, u64 *lepubkeyhash, पूर्णांक *trapnr);
#पूर्ण_अगर

पूर्णांक sgx_set_attribute(अचिन्हित दीर्घ *allowed_attributes,
		      अचिन्हित पूर्णांक attribute_fd);

#पूर्ण_अगर /* _ASM_X86_SGX_H */
