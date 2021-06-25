<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004,2007,2008 IBM Corporation
 *
 * Authors:
 * Leendert van Doorn <leendert@watson.ibm.com>
 * Dave Safक्रमd <safक्रमd@watson.ibm.com>
 * Reiner Sailer <sailer@watson.ibm.com>
 * Kylene Hall <kjhall@us.ibm.com>
 * Debora Velarde <dvelarde@us.ibm.com>
 *
 * Maपूर्णांकained by: <tpmdd_devel@lists.sourceक्रमge.net>
 *
 * Device driver क्रम TCG/TCPA TPM (trusted platक्रमm module).
 * Specअगरications at www.trustedcomputinggroup.org
 */
#अगर_अघोषित __LINUX_TPM_H__
#घोषणा __LINUX_TPM_H__

#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/acpi.h>
#समावेश <linux/cdev.h>
#समावेश <linux/fs.h>
#समावेश <linux/highस्मृति.स>
#समावेश <crypto/hash_info.h>

#घोषणा TPM_DIGEST_SIZE 20	/* Max TPM v1.2 PCR size */
#घोषणा TPM_MAX_DIGEST_SIZE SHA512_DIGEST_SIZE

काष्ठा tpm_chip;
काष्ठा trusted_key_payload;
काष्ठा trusted_key_options;

/* अगर you add a new hash to this, increment TPM_MAX_HASHES below */
क्रमागत tpm_algorithms अणु
	TPM_ALG_ERROR		= 0x0000,
	TPM_ALG_SHA1		= 0x0004,
	TPM_ALG_KEYEDHASH	= 0x0008,
	TPM_ALG_SHA256		= 0x000B,
	TPM_ALG_SHA384		= 0x000C,
	TPM_ALG_SHA512		= 0x000D,
	TPM_ALG_शून्य		= 0x0010,
	TPM_ALG_SM3_256		= 0x0012,
पूर्ण;

/*
 * maximum number of hashing algorithms a TPM can have.  This is
 * basically a count of every hash in tpm_algorithms above
 */
#घोषणा TPM_MAX_HASHES	5

काष्ठा tpm_digest अणु
	u16 alg_id;
	u8 digest[TPM_MAX_DIGEST_SIZE];
पूर्ण __packed;

काष्ठा tpm_bank_info अणु
	u16 alg_id;
	u16 digest_size;
	u16 crypto_id;
पूर्ण;

क्रमागत TPM_OPS_FLAGS अणु
	TPM_OPS_AUTO_STARTUP = BIT(0),
पूर्ण;

काष्ठा tpm_class_ops अणु
	अचिन्हित पूर्णांक flags;
	स्थिर u8 req_complete_mask;
	स्थिर u8 req_complete_val;
	bool (*req_canceled)(काष्ठा tpm_chip *chip, u8 status);
	पूर्णांक (*recv) (काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार len);
	पूर्णांक (*send) (काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार len);
	व्योम (*cancel) (काष्ठा tpm_chip *chip);
	u8 (*status) (काष्ठा tpm_chip *chip);
	व्योम (*update_समयouts)(काष्ठा tpm_chip *chip,
				अचिन्हित दीर्घ *समयout_cap);
	व्योम (*update_durations)(काष्ठा tpm_chip *chip,
				 अचिन्हित दीर्घ *duration_cap);
	पूर्णांक (*go_idle)(काष्ठा tpm_chip *chip);
	पूर्णांक (*cmd_पढ़ोy)(काष्ठा tpm_chip *chip);
	पूर्णांक (*request_locality)(काष्ठा tpm_chip *chip, पूर्णांक loc);
	पूर्णांक (*relinquish_locality)(काष्ठा tpm_chip *chip, पूर्णांक loc);
	व्योम (*clk_enable)(काष्ठा tpm_chip *chip, bool value);
पूर्ण;

#घोषणा TPM_NUM_EVENT_LOG_खाताS		3

/* Indexes the duration array */
क्रमागत tpm_duration अणु
	TPM_SHORT = 0,
	TPM_MEDIUM = 1,
	TPM_LONG = 2,
	TPM_LONG_LONG = 3,
	TPM_UNDEFINED,
	TPM_NUM_DURATIONS = TPM_UNDEFINED,
पूर्ण;

#घोषणा TPM_PPI_VERSION_LEN		3

काष्ठा tpm_space अणु
	u32 context_tbl[3];
	u8 *context_buf;
	u32 session_tbl[3];
	u8 *session_buf;
	u32 buf_size;
पूर्ण;

काष्ठा tpm_bios_log अणु
	व्योम *bios_event_log;
	व्योम *bios_event_log_end;
पूर्ण;

काष्ठा tpm_chip_seqops अणु
	काष्ठा tpm_chip *chip;
	स्थिर काष्ठा seq_operations *seqops;
पूर्ण;

काष्ठा tpm_chip अणु
	काष्ठा device dev;
	काष्ठा device devs;
	काष्ठा cdev cdev;
	काष्ठा cdev cdevs;

	/* A driver callback under ops cannot be run unless ops_sem is held
	 * (someबार implicitly, eg क्रम the sysfs code). ops becomes null
	 * when the driver is unरेजिस्टरed, see tpm_try_get_ops.
	 */
	काष्ठा rw_semaphore ops_sem;
	स्थिर काष्ठा tpm_class_ops *ops;

	काष्ठा tpm_bios_log log;
	काष्ठा tpm_chip_seqops bin_log_seqops;
	काष्ठा tpm_chip_seqops ascii_log_seqops;

	अचिन्हित पूर्णांक flags;

	पूर्णांक dev_num;		/* /dev/tpm# */
	अचिन्हित दीर्घ is_खोलो;	/* only one allowed */

	अक्षर hwrng_name[64];
	काष्ठा hwrng hwrng;

	काष्ठा mutex tpm_mutex;	/* tpm is processing */

	अचिन्हित दीर्घ समयout_a; /* jअगरfies */
	अचिन्हित दीर्घ समयout_b; /* jअगरfies */
	अचिन्हित दीर्घ समयout_c; /* jअगरfies */
	अचिन्हित दीर्घ समयout_d; /* jअगरfies */
	bool समयout_adjusted;
	अचिन्हित दीर्घ duration[TPM_NUM_DURATIONS]; /* jअगरfies */
	bool duration_adjusted;

	काष्ठा dentry *bios_dir[TPM_NUM_EVENT_LOG_खाताS];

	स्थिर काष्ठा attribute_group *groups[3 + TPM_MAX_HASHES];
	अचिन्हित पूर्णांक groups_cnt;

	u32 nr_allocated_banks;
	काष्ठा tpm_bank_info *allocated_banks;
#अगर_घोषित CONFIG_ACPI
	acpi_handle acpi_dev_handle;
	अक्षर ppi_version[TPM_PPI_VERSION_LEN + 1];
#पूर्ण_अगर /* CONFIG_ACPI */

	काष्ठा tpm_space work_space;
	u32 last_cc;
	u32 nr_commands;
	u32 *cc_attrs_tbl;

	/* active locality */
	पूर्णांक locality;
पूर्ण;

#घोषणा TPM_HEADER_SIZE		10

क्रमागत tpm2_स्थिर अणु
	TPM2_PLATFORM_PCR       =     24,
	TPM2_PCR_SELECT_MIN     = ((TPM2_PLATFORM_PCR + 7) / 8),
पूर्ण;

क्रमागत tpm2_समयouts अणु
	TPM2_TIMEOUT_A          =    750,
	TPM2_TIMEOUT_B          =   2000,
	TPM2_TIMEOUT_C          =    200,
	TPM2_TIMEOUT_D          =     30,
	TPM2_DURATION_SHORT     =     20,
	TPM2_DURATION_MEDIUM    =    750,
	TPM2_DURATION_LONG      =   2000,
	TPM2_DURATION_LONG_LONG = 300000,
	TPM2_DURATION_DEFAULT   = 120000,
पूर्ण;

क्रमागत tpm2_काष्ठाures अणु
	TPM2_ST_NO_SESSIONS	= 0x8001,
	TPM2_ST_SESSIONS	= 0x8002,
पूर्ण;

/* Indicates from what layer of the software stack the error comes from */
#घोषणा TSS2_RC_LAYER_SHIFT	 16
#घोषणा TSS2_RESMGR_TPM_RC_LAYER (11 << TSS2_RC_LAYER_SHIFT)

क्रमागत tpm2_वापस_codes अणु
	TPM2_RC_SUCCESS		= 0x0000,
	TPM2_RC_HASH		= 0x0083, /* RC_FMT1 */
	TPM2_RC_HANDLE		= 0x008B,
	TPM2_RC_INITIALIZE	= 0x0100, /* RC_VER1 */
	TPM2_RC_FAILURE		= 0x0101,
	TPM2_RC_DISABLED	= 0x0120,
	TPM2_RC_COMMAND_CODE    = 0x0143,
	TPM2_RC_TESTING		= 0x090A, /* RC_WARN */
	TPM2_RC_REFERENCE_H0	= 0x0910,
	TPM2_RC_RETRY		= 0x0922,
पूर्ण;

क्रमागत tpm2_command_codes अणु
	TPM2_CC_FIRST		        = 0x011F,
	TPM2_CC_HIERARCHY_CONTROL       = 0x0121,
	TPM2_CC_HIERARCHY_CHANGE_AUTH   = 0x0129,
	TPM2_CC_CREATE_PRIMARY          = 0x0131,
	TPM2_CC_SEQUENCE_COMPLETE       = 0x013E,
	TPM2_CC_SELF_TEST	        = 0x0143,
	TPM2_CC_STARTUP		        = 0x0144,
	TPM2_CC_SHUTDOWN	        = 0x0145,
	TPM2_CC_NV_READ                 = 0x014E,
	TPM2_CC_CREATE		        = 0x0153,
	TPM2_CC_LOAD		        = 0x0157,
	TPM2_CC_SEQUENCE_UPDATE         = 0x015C,
	TPM2_CC_UNSEAL		        = 0x015E,
	TPM2_CC_CONTEXT_LOAD	        = 0x0161,
	TPM2_CC_CONTEXT_SAVE	        = 0x0162,
	TPM2_CC_FLUSH_CONTEXT	        = 0x0165,
	TPM2_CC_VERIFY_SIGNATURE        = 0x0177,
	TPM2_CC_GET_CAPABILITY	        = 0x017A,
	TPM2_CC_GET_RANDOM	        = 0x017B,
	TPM2_CC_PCR_READ	        = 0x017E,
	TPM2_CC_PCR_EXTEND	        = 0x0182,
	TPM2_CC_EVENT_SEQUENCE_COMPLETE = 0x0185,
	TPM2_CC_HASH_SEQUENCE_START     = 0x0186,
	TPM2_CC_CREATE_LOADED           = 0x0191,
	TPM2_CC_LAST		        = 0x0193, /* Spec 1.36 */
पूर्ण;

क्रमागत tpm2_permanent_handles अणु
	TPM2_RS_PW		= 0x40000009,
पूर्ण;

क्रमागत tpm2_capabilities अणु
	TPM2_CAP_HANDLES	= 1,
	TPM2_CAP_COMMANDS	= 2,
	TPM2_CAP_PCRS		= 5,
	TPM2_CAP_TPM_PROPERTIES = 6,
पूर्ण;

क्रमागत tpm2_properties अणु
	TPM_PT_TOTAL_COMMANDS	= 0x0129,
पूर्ण;

क्रमागत tpm2_startup_types अणु
	TPM2_SU_CLEAR	= 0x0000,
	TPM2_SU_STATE	= 0x0001,
पूर्ण;

क्रमागत tpm2_cc_attrs अणु
	TPM2_CC_ATTR_CHANDLES	= 25,
	TPM2_CC_ATTR_RHANDLE	= 28,
पूर्ण;

#घोषणा TPM_VID_INTEL    0x8086
#घोषणा TPM_VID_WINBOND  0x1050
#घोषणा TPM_VID_STM      0x104A

क्रमागत tpm_chip_flags अणु
	TPM_CHIP_FLAG_TPM2		= BIT(1),
	TPM_CHIP_FLAG_IRQ		= BIT(2),
	TPM_CHIP_FLAG_VIRTUAL		= BIT(3),
	TPM_CHIP_FLAG_HAVE_TIMEOUTS	= BIT(4),
	TPM_CHIP_FLAG_ALWAYS_POWERED	= BIT(5),
	TPM_CHIP_FLAG_FIRMWARE_POWER_MANAGED	= BIT(6),
पूर्ण;

#घोषणा to_tpm_chip(d) container_of(d, काष्ठा tpm_chip, dev)

काष्ठा tpm_header अणु
	__be16 tag;
	__be32 length;
	जोड़ अणु
		__be32 ordinal;
		__be32 वापस_code;
	पूर्ण;
पूर्ण __packed;

/* A string buffer type क्रम स्थिरructing TPM commands. This is based on the
 * ideas of string buffer code in security/keys/trusted.h but is heap based
 * in order to keep the stack usage minimal.
 */

क्रमागत tpm_buf_flags अणु
	TPM_BUF_OVERFLOW	= BIT(0),
पूर्ण;

काष्ठा tpm_buf अणु
	अचिन्हित पूर्णांक flags;
	u8 *data;
पूर्ण;

क्रमागत tpm2_object_attributes अणु
	TPM2_OA_FIXED_TPM		= BIT(1),
	TPM2_OA_FIXED_PARENT		= BIT(4),
	TPM2_OA_USER_WITH_AUTH		= BIT(6),
पूर्ण;

क्रमागत tpm2_session_attributes अणु
	TPM2_SA_CONTINUE_SESSION	= BIT(0),
पूर्ण;

काष्ठा tpm2_hash अणु
	अचिन्हित पूर्णांक crypto_id;
	अचिन्हित पूर्णांक tpm_id;
पूर्ण;

अटल अंतरभूत व्योम tpm_buf_reset(काष्ठा tpm_buf *buf, u16 tag, u32 ordinal)
अणु
	काष्ठा tpm_header *head = (काष्ठा tpm_header *)buf->data;

	head->tag = cpu_to_be16(tag);
	head->length = cpu_to_be32(माप(*head));
	head->ordinal = cpu_to_be32(ordinal);
पूर्ण

अटल अंतरभूत पूर्णांक tpm_buf_init(काष्ठा tpm_buf *buf, u16 tag, u32 ordinal)
अणु
	buf->data = (u8 *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!buf->data)
		वापस -ENOMEM;

	buf->flags = 0;
	tpm_buf_reset(buf, tag, ordinal);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम tpm_buf_destroy(काष्ठा tpm_buf *buf)
अणु
	मुक्त_page((अचिन्हित दीर्घ)buf->data);
पूर्ण

अटल अंतरभूत u32 tpm_buf_length(काष्ठा tpm_buf *buf)
अणु
	काष्ठा tpm_header *head = (काष्ठा tpm_header *)buf->data;

	वापस be32_to_cpu(head->length);
पूर्ण

अटल अंतरभूत u16 tpm_buf_tag(काष्ठा tpm_buf *buf)
अणु
	काष्ठा tpm_header *head = (काष्ठा tpm_header *)buf->data;

	वापस be16_to_cpu(head->tag);
पूर्ण

अटल अंतरभूत व्योम tpm_buf_append(काष्ठा tpm_buf *buf,
				  स्थिर अचिन्हित अक्षर *new_data,
				  अचिन्हित पूर्णांक new_len)
अणु
	काष्ठा tpm_header *head = (काष्ठा tpm_header *)buf->data;
	u32 len = tpm_buf_length(buf);

	/* Return silently अगर overflow has alपढ़ोy happened. */
	अगर (buf->flags & TPM_BUF_OVERFLOW)
		वापस;

	अगर ((len + new_len) > PAGE_SIZE) अणु
		WARN(1, "tpm_buf: overflow\n");
		buf->flags |= TPM_BUF_OVERFLOW;
		वापस;
	पूर्ण

	स_नकल(&buf->data[len], new_data, new_len);
	head->length = cpu_to_be32(len + new_len);
पूर्ण

अटल अंतरभूत व्योम tpm_buf_append_u8(काष्ठा tpm_buf *buf, स्थिर u8 value)
अणु
	tpm_buf_append(buf, &value, 1);
पूर्ण

अटल अंतरभूत व्योम tpm_buf_append_u16(काष्ठा tpm_buf *buf, स्थिर u16 value)
अणु
	__be16 value2 = cpu_to_be16(value);

	tpm_buf_append(buf, (u8 *) &value2, 2);
पूर्ण

अटल अंतरभूत व्योम tpm_buf_append_u32(काष्ठा tpm_buf *buf, स्थिर u32 value)
अणु
	__be32 value2 = cpu_to_be32(value);

	tpm_buf_append(buf, (u8 *) &value2, 4);
पूर्ण

अटल अंतरभूत u32 tpm2_rc_value(u32 rc)
अणु
	वापस (rc & BIT(7)) ? rc & 0xff : rc;
पूर्ण

#अगर defined(CONFIG_TCG_TPM) || defined(CONFIG_TCG_TPM_MODULE)

बाह्य पूर्णांक tpm_is_tpm2(काष्ठा tpm_chip *chip);
बाह्य __must_check पूर्णांक tpm_try_get_ops(काष्ठा tpm_chip *chip);
बाह्य व्योम tpm_put_ops(काष्ठा tpm_chip *chip);
बाह्य sमाप_प्रकार tpm_transmit_cmd(काष्ठा tpm_chip *chip, काष्ठा tpm_buf *buf,
				माप_प्रकार min_rsp_body_length, स्थिर अक्षर *desc);
बाह्य पूर्णांक tpm_pcr_पढ़ो(काष्ठा tpm_chip *chip, u32 pcr_idx,
			काष्ठा tpm_digest *digest);
बाह्य पूर्णांक tpm_pcr_extend(काष्ठा tpm_chip *chip, u32 pcr_idx,
			  काष्ठा tpm_digest *digests);
बाह्य पूर्णांक tpm_send(काष्ठा tpm_chip *chip, व्योम *cmd, माप_प्रकार buflen);
बाह्य पूर्णांक tpm_get_अक्रमom(काष्ठा tpm_chip *chip, u8 *data, माप_प्रकार max);
बाह्य काष्ठा tpm_chip *tpm_शेष_chip(व्योम);
व्योम tpm2_flush_context(काष्ठा tpm_chip *chip, u32 handle);
#अन्यथा
अटल अंतरभूत पूर्णांक tpm_is_tpm2(काष्ठा tpm_chip *chip)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत पूर्णांक tpm_pcr_पढ़ो(काष्ठा tpm_chip *chip, पूर्णांक pcr_idx,
			       काष्ठा tpm_digest *digest)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक tpm_pcr_extend(काष्ठा tpm_chip *chip, u32 pcr_idx,
				 काष्ठा tpm_digest *digests)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक tpm_send(काष्ठा tpm_chip *chip, व्योम *cmd, माप_प्रकार buflen)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत पूर्णांक tpm_get_अक्रमom(काष्ठा tpm_chip *chip, u8 *data, माप_प्रकार max)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत काष्ठा tpm_chip *tpm_शेष_chip(व्योम)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
