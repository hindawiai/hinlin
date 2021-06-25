<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2005,2006,2007,2008 IBM Corporation
 *
 * Authors:
 * Reiner Sailer <sailer@watson.ibm.com>
 * Mimi Zohar <zohar@us.ibm.com>
 *
 * File: ima.h
 *	पूर्णांकernal Integrity Measurement Architecture (IMA) definitions
 */

#अगर_अघोषित __LINUX_IMA_H
#घोषणा __LINUX_IMA_H

#समावेश <linux/types.h>
#समावेश <linux/crypto.h>
#समावेश <linux/fs.h>
#समावेश <linux/security.h>
#समावेश <linux/hash.h>
#समावेश <linux/tpm.h>
#समावेश <linux/audit.h>
#समावेश <crypto/hash_info.h>

#समावेश "../integrity.h"

क्रमागत ima_show_type अणु IMA_SHOW_BINARY, IMA_SHOW_BINARY_NO_FIELD_LEN,
		     IMA_SHOW_BINARY_OLD_STRING_FMT, IMA_SHOW_ASCII पूर्ण;
क्रमागत tpm_pcrs अणु TPM_PCR0 = 0, TPM_PCR8 = 8, TPM_PCR10 = 10 पूर्ण;

/* digest size क्रम IMA, fits SHA1 or MD5 */
#घोषणा IMA_DIGEST_SIZE		SHA1_DIGEST_SIZE
#घोषणा IMA_EVENT_NAME_LEN_MAX	255

#घोषणा IMA_HASH_BITS 10
#घोषणा IMA_MEASURE_HTABLE_SIZE (1 << IMA_HASH_BITS)

#घोषणा IMA_TEMPLATE_FIELD_ID_MAX_LEN	16
#घोषणा IMA_TEMPLATE_NUM_FIELDS_MAX	15

#घोषणा IMA_TEMPLATE_IMA_NAME "ima"
#घोषणा IMA_TEMPLATE_IMA_FMT "d|n"

#घोषणा NR_BANKS(chip) ((chip != शून्य) ? chip->nr_allocated_banks : 0)

/* current content of the policy */
बाह्य पूर्णांक ima_policy_flag;

/* set during initialization */
बाह्य पूर्णांक ima_hash_algo;
बाह्य पूर्णांक ima_sha1_idx __ro_after_init;
बाह्य पूर्णांक ima_hash_algo_idx __ro_after_init;
बाह्य पूर्णांक ima_extra_slots __ro_after_init;
बाह्य पूर्णांक ima_appउठाओ;
बाह्य काष्ठा tpm_chip *ima_tpm_chip;
बाह्य स्थिर अक्षर boot_aggregate_name[];

/* IMA event related data */
काष्ठा ima_event_data अणु
	काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक;
	काष्ठा file *file;
	स्थिर अचिन्हित अक्षर *filename;
	काष्ठा evm_ima_xattr_data *xattr_value;
	पूर्णांक xattr_len;
	स्थिर काष्ठा modsig *modsig;
	स्थिर अक्षर *violation;
	स्थिर व्योम *buf;
	पूर्णांक buf_len;
पूर्ण;

/* IMA ढाँचा field data definition */
काष्ठा ima_field_data अणु
	u8 *data;
	u32 len;
पूर्ण;

/* IMA ढाँचा field definition */
काष्ठा ima_ढाँचा_field अणु
	स्थिर अक्षर field_id[IMA_TEMPLATE_FIELD_ID_MAX_LEN];
	पूर्णांक (*field_init)(काष्ठा ima_event_data *event_data,
			  काष्ठा ima_field_data *field_data);
	व्योम (*field_show)(काष्ठा seq_file *m, क्रमागत ima_show_type show,
			   काष्ठा ima_field_data *field_data);
पूर्ण;

/* IMA ढाँचा descriptor definition */
काष्ठा ima_ढाँचा_desc अणु
	काष्ठा list_head list;
	अक्षर *name;
	अक्षर *fmt;
	पूर्णांक num_fields;
	स्थिर काष्ठा ima_ढाँचा_field **fields;
पूर्ण;

काष्ठा ima_ढाँचा_entry अणु
	पूर्णांक pcr;
	काष्ठा tpm_digest *digests;
	काष्ठा ima_ढाँचा_desc *ढाँचा_desc; /* ढाँचा descriptor */
	u32 ढाँचा_data_len;
	काष्ठा ima_field_data ढाँचा_data[];	/* ढाँचा related data */
पूर्ण;

काष्ठा ima_queue_entry अणु
	काष्ठा hlist_node hnext;	/* place in hash collision list */
	काष्ठा list_head later;		/* place in ima_measurements list */
	काष्ठा ima_ढाँचा_entry *entry;
पूर्ण;
बाह्य काष्ठा list_head ima_measurements;	/* list of all measurements */

/* Some details preceding the binary serialized measurement list */
काष्ठा ima_kexec_hdr अणु
	u16 version;
	u16 _reserved0;
	u32 _reserved1;
	u64 buffer_size;
	u64 count;
पूर्ण;

बाह्य स्थिर पूर्णांक पढ़ो_idmap[];

#अगर_घोषित CONFIG_HAVE_IMA_KEXEC
व्योम ima_load_kexec_buffer(व्योम);
#अन्यथा
अटल अंतरभूत व्योम ima_load_kexec_buffer(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_IMA_KEXEC */

/*
 * The शेष binary_runसमय_measurements list क्रमmat is defined as the
 * platक्रमm native क्रमmat.  The canonical क्रमmat is defined as little-endian.
 */
बाह्य bool ima_canonical_fmt;

/* Internal IMA function definitions */
पूर्णांक ima_init(व्योम);
पूर्णांक ima_fs_init(व्योम);
पूर्णांक ima_add_ढाँचा_entry(काष्ठा ima_ढाँचा_entry *entry, पूर्णांक violation,
			   स्थिर अक्षर *op, काष्ठा inode *inode,
			   स्थिर अचिन्हित अक्षर *filename);
पूर्णांक ima_calc_file_hash(काष्ठा file *file, काष्ठा ima_digest_data *hash);
पूर्णांक ima_calc_buffer_hash(स्थिर व्योम *buf, loff_t len,
			 काष्ठा ima_digest_data *hash);
पूर्णांक ima_calc_field_array_hash(काष्ठा ima_field_data *field_data,
			      काष्ठा ima_ढाँचा_entry *entry);
पूर्णांक ima_calc_boot_aggregate(काष्ठा ima_digest_data *hash);
व्योम ima_add_violation(काष्ठा file *file, स्थिर अचिन्हित अक्षर *filename,
		       काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक,
		       स्थिर अक्षर *op, स्थिर अक्षर *cause);
पूर्णांक ima_init_crypto(व्योम);
व्योम ima_अ_दो(काष्ठा seq_file *m, व्योम *data, पूर्णांक datalen);
व्योम ima_prपूर्णांक_digest(काष्ठा seq_file *m, u8 *digest, u32 size);
पूर्णांक ढाँचा_desc_init_fields(स्थिर अक्षर *ढाँचा_fmt,
			      स्थिर काष्ठा ima_ढाँचा_field ***fields,
			      पूर्णांक *num_fields);
काष्ठा ima_ढाँचा_desc *ima_ढाँचा_desc_current(व्योम);
काष्ठा ima_ढाँचा_desc *ima_ढाँचा_desc_buf(व्योम);
काष्ठा ima_ढाँचा_desc *lookup_ढाँचा_desc(स्थिर अक्षर *name);
bool ima_ढाँचा_has_modsig(स्थिर काष्ठा ima_ढाँचा_desc *ima_ढाँचा);
पूर्णांक ima_restore_measurement_entry(काष्ठा ima_ढाँचा_entry *entry);
पूर्णांक ima_restore_measurement_list(loff_t bufsize, व्योम *buf);
पूर्णांक ima_measurements_show(काष्ठा seq_file *m, व्योम *v);
अचिन्हित दीर्घ ima_get_binary_runसमय_size(व्योम);
पूर्णांक ima_init_ढाँचा(व्योम);
व्योम ima_init_ढाँचा_list(व्योम);
पूर्णांक __init ima_init_digests(व्योम);
पूर्णांक ima_lsm_policy_change(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			  व्योम *lsm_data);

/*
 * used to protect h_table and sha_table
 */
बाह्य spinlock_t ima_queue_lock;

काष्ठा ima_h_table अणु
	atomic_दीर्घ_t len;	/* number of stored measurements in the list */
	atomic_दीर्घ_t violations;
	काष्ठा hlist_head queue[IMA_MEASURE_HTABLE_SIZE];
पूर्ण;
बाह्य काष्ठा ima_h_table ima_htable;

अटल अंतरभूत अचिन्हित पूर्णांक ima_hash_key(u8 *digest)
अणु
	/* there is no poपूर्णांक in taking a hash of part of a digest */
	वापस (digest[0] | digest[1] << 8) % IMA_MEASURE_HTABLE_SIZE;
पूर्ण

#घोषणा __ima_hooks(hook)				\
	hook(NONE, none)				\
	hook(खाता_CHECK, file)				\
	hook(MMAP_CHECK, mmap)				\
	hook(BPRM_CHECK, bprm)				\
	hook(CREDS_CHECK, creds)			\
	hook(POST_SETATTR, post_setattr)		\
	hook(MODULE_CHECK, module)			\
	hook(FIRMWARE_CHECK, firmware)			\
	hook(KEXEC_KERNEL_CHECK, kexec_kernel)		\
	hook(KEXEC_INITRAMFS_CHECK, kexec_initramfs)	\
	hook(POLICY_CHECK, policy)			\
	hook(KEXEC_CMDLINE, kexec_cmdline)		\
	hook(KEY_CHECK, key)				\
	hook(CRITICAL_DATA, critical_data)		\
	hook(MAX_CHECK, none)

#घोषणा __ima_hook_क्रमागतअगरy(ENUM, str)	ENUM,
#घोषणा __ima_stringअगरy(arg) (#arg)
#घोषणा __ima_hook_measuring_stringअगरy(ENUM, str) \
		(__ima_stringअगरy(measuring_ ##str)),

क्रमागत ima_hooks अणु
	__ima_hooks(__ima_hook_क्रमागतअगरy)
पूर्ण;

अटल स्थिर अक्षर * स्थिर ima_hooks_measure_str[] = अणु
	__ima_hooks(__ima_hook_measuring_stringअगरy)
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *func_measure_str(क्रमागत ima_hooks func)
अणु
	अगर (func >= MAX_CHECK)
		वापस ima_hooks_measure_str[NONE];

	वापस ima_hooks_measure_str[func];
पूर्ण

बाह्य स्थिर अक्षर *स्थिर func_tokens[];

काष्ठा modsig;

#अगर_घोषित CONFIG_IMA_QUEUE_EARLY_BOOT_KEYS
/*
 * To track keys that need to be measured.
 */
काष्ठा ima_key_entry अणु
	काष्ठा list_head list;
	व्योम *payload;
	माप_प्रकार payload_len;
	अक्षर *keyring_name;
पूर्ण;
व्योम ima_init_key_queue(व्योम);
bool ima_should_queue_key(व्योम);
bool ima_queue_key(काष्ठा key *keyring, स्थिर व्योम *payload,
		   माप_प्रकार payload_len);
व्योम ima_process_queued_keys(व्योम);
#अन्यथा
अटल अंतरभूत व्योम ima_init_key_queue(व्योम) अणुपूर्ण
अटल अंतरभूत bool ima_should_queue_key(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत bool ima_queue_key(काष्ठा key *keyring,
				 स्थिर व्योम *payload,
				 माप_प्रकार payload_len) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम ima_process_queued_keys(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_IMA_QUEUE_EARLY_BOOT_KEYS */

/* LIM API function definitions */
पूर्णांक ima_get_action(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		   स्थिर काष्ठा cred *cred, u32 secid, पूर्णांक mask,
		   क्रमागत ima_hooks func, पूर्णांक *pcr,
		   काष्ठा ima_ढाँचा_desc **ढाँचा_desc,
		   स्थिर अक्षर *func_data);
पूर्णांक ima_must_measure(काष्ठा inode *inode, पूर्णांक mask, क्रमागत ima_hooks func);
पूर्णांक ima_collect_measurement(काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक,
			    काष्ठा file *file, व्योम *buf, loff_t size,
			    क्रमागत hash_algo algo, काष्ठा modsig *modsig);
व्योम ima_store_measurement(काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक, काष्ठा file *file,
			   स्थिर अचिन्हित अक्षर *filename,
			   काष्ठा evm_ima_xattr_data *xattr_value,
			   पूर्णांक xattr_len, स्थिर काष्ठा modsig *modsig, पूर्णांक pcr,
			   काष्ठा ima_ढाँचा_desc *ढाँचा_desc);
व्योम process_buffer_measurement(काष्ठा user_namespace *mnt_userns,
				काष्ठा inode *inode, स्थिर व्योम *buf, पूर्णांक size,
				स्थिर अक्षर *eventname, क्रमागत ima_hooks func,
				पूर्णांक pcr, स्थिर अक्षर *func_data,
				bool buf_hash);
व्योम ima_audit_measurement(काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक,
			   स्थिर अचिन्हित अक्षर *filename);
पूर्णांक ima_alloc_init_ढाँचा(काष्ठा ima_event_data *event_data,
			    काष्ठा ima_ढाँचा_entry **entry,
			    काष्ठा ima_ढाँचा_desc *ढाँचा_desc);
पूर्णांक ima_store_ढाँचा(काष्ठा ima_ढाँचा_entry *entry, पूर्णांक violation,
		       काष्ठा inode *inode,
		       स्थिर अचिन्हित अक्षर *filename, पूर्णांक pcr);
व्योम ima_मुक्त_ढाँचा_entry(काष्ठा ima_ढाँचा_entry *entry);
स्थिर अक्षर *ima_d_path(स्थिर काष्ठा path *path, अक्षर **pathbuf, अक्षर *filename);

/* IMA policy related functions */
पूर्णांक ima_match_policy(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		     स्थिर काष्ठा cred *cred, u32 secid, क्रमागत ima_hooks func,
		     पूर्णांक mask, पूर्णांक flags, पूर्णांक *pcr,
		     काष्ठा ima_ढाँचा_desc **ढाँचा_desc,
		     स्थिर अक्षर *func_data);
व्योम ima_init_policy(व्योम);
व्योम ima_update_policy(व्योम);
व्योम ima_update_policy_flag(व्योम);
sमाप_प्रकार ima_parse_add_rule(अक्षर *);
व्योम ima_delete_rules(व्योम);
पूर्णांक ima_check_policy(व्योम);
व्योम *ima_policy_start(काष्ठा seq_file *m, loff_t *pos);
व्योम *ima_policy_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos);
व्योम ima_policy_stop(काष्ठा seq_file *m, व्योम *v);
पूर्णांक ima_policy_show(काष्ठा seq_file *m, व्योम *v);

/* Appउठाओ पूर्णांकegrity measurements */
#घोषणा IMA_APPRAISE_ENFORCE	0x01
#घोषणा IMA_APPRAISE_FIX	0x02
#घोषणा IMA_APPRAISE_LOG	0x04
#घोषणा IMA_APPRAISE_MODULES	0x08
#घोषणा IMA_APPRAISE_FIRMWARE	0x10
#घोषणा IMA_APPRAISE_POLICY	0x20
#घोषणा IMA_APPRAISE_KEXEC	0x40

#अगर_घोषित CONFIG_IMA_APPRAISE
पूर्णांक ima_check_blacklist(काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक,
			स्थिर काष्ठा modsig *modsig, पूर्णांक pcr);
पूर्णांक ima_appउठाओ_measurement(क्रमागत ima_hooks func,
			     काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक,
			     काष्ठा file *file, स्थिर अचिन्हित अक्षर *filename,
			     काष्ठा evm_ima_xattr_data *xattr_value,
			     पूर्णांक xattr_len, स्थिर काष्ठा modsig *modsig);
पूर्णांक ima_must_appउठाओ(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		      पूर्णांक mask, क्रमागत ima_hooks func);
व्योम ima_update_xattr(काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक, काष्ठा file *file);
क्रमागत पूर्णांकegrity_status ima_get_cache_status(काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक,
					   क्रमागत ima_hooks func);
क्रमागत hash_algo ima_get_hash_algo(काष्ठा evm_ima_xattr_data *xattr_value,
				 पूर्णांक xattr_len);
पूर्णांक ima_पढ़ो_xattr(काष्ठा dentry *dentry,
		   काष्ठा evm_ima_xattr_data **xattr_value);

#अन्यथा
अटल अंतरभूत पूर्णांक ima_check_blacklist(काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक,
				      स्थिर काष्ठा modsig *modsig, पूर्णांक pcr)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ima_appउठाओ_measurement(क्रमागत ima_hooks func,
					   काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक,
					   काष्ठा file *file,
					   स्थिर अचिन्हित अक्षर *filename,
					   काष्ठा evm_ima_xattr_data *xattr_value,
					   पूर्णांक xattr_len,
					   स्थिर काष्ठा modsig *modsig)
अणु
	वापस INTEGRITY_UNKNOWN;
पूर्ण

अटल अंतरभूत पूर्णांक ima_must_appउठाओ(काष्ठा user_namespace *mnt_userns,
				    काष्ठा inode *inode, पूर्णांक mask,
				    क्रमागत ima_hooks func)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ima_update_xattr(काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक,
				    काष्ठा file *file)
अणु
पूर्ण

अटल अंतरभूत क्रमागत पूर्णांकegrity_status ima_get_cache_status(काष्ठा पूर्णांकegrity_iपूर्णांक_cache
							 *iपूर्णांक,
							 क्रमागत ima_hooks func)
अणु
	वापस INTEGRITY_UNKNOWN;
पूर्ण

अटल अंतरभूत क्रमागत hash_algo
ima_get_hash_algo(काष्ठा evm_ima_xattr_data *xattr_value, पूर्णांक xattr_len)
अणु
	वापस ima_hash_algo;
पूर्ण

अटल अंतरभूत पूर्णांक ima_पढ़ो_xattr(काष्ठा dentry *dentry,
				 काष्ठा evm_ima_xattr_data **xattr_value)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_IMA_APPRAISE */

#अगर_घोषित CONFIG_IMA_APPRAISE_MODSIG
पूर्णांक ima_पढ़ो_modsig(क्रमागत ima_hooks func, स्थिर व्योम *buf, loff_t buf_len,
		    काष्ठा modsig **modsig);
व्योम ima_collect_modsig(काष्ठा modsig *modsig, स्थिर व्योम *buf, loff_t size);
पूर्णांक ima_get_modsig_digest(स्थिर काष्ठा modsig *modsig, क्रमागत hash_algo *algo,
			  स्थिर u8 **digest, u32 *digest_size);
पूर्णांक ima_get_raw_modsig(स्थिर काष्ठा modsig *modsig, स्थिर व्योम **data,
		       u32 *data_len);
व्योम ima_मुक्त_modsig(काष्ठा modsig *modsig);
#अन्यथा
अटल अंतरभूत पूर्णांक ima_पढ़ो_modsig(क्रमागत ima_hooks func, स्थिर व्योम *buf,
				  loff_t buf_len, काष्ठा modsig **modsig)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम ima_collect_modsig(काष्ठा modsig *modsig, स्थिर व्योम *buf,
				      loff_t size)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ima_get_modsig_digest(स्थिर काष्ठा modsig *modsig,
					क्रमागत hash_algo *algo, स्थिर u8 **digest,
					u32 *digest_size)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक ima_get_raw_modsig(स्थिर काष्ठा modsig *modsig,
				     स्थिर व्योम **data, u32 *data_len)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम ima_मुक्त_modsig(काष्ठा modsig *modsig)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_IMA_APPRAISE_MODSIG */

/* LSM based policy rules require audit */
#अगर_घोषित CONFIG_IMA_LSM_RULES

#घोषणा ima_filter_rule_init security_audit_rule_init
#घोषणा ima_filter_rule_मुक्त security_audit_rule_मुक्त
#घोषणा ima_filter_rule_match security_audit_rule_match

#अन्यथा

अटल अंतरभूत पूर्णांक ima_filter_rule_init(u32 field, u32 op, अक्षर *rulestr,
				       व्योम **lsmrule)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम ima_filter_rule_मुक्त(व्योम *lsmrule)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ima_filter_rule_match(u32 secid, u32 field, u32 op,
					व्योम *lsmrule)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_IMA_LSM_RULES */

#अगर_घोषित	CONFIG_IMA_READ_POLICY
#घोषणा	POLICY_खाता_FLAGS	(S_IWUSR | S_IRUSR)
#अन्यथा
#घोषणा	POLICY_खाता_FLAGS	S_IWUSR
#पूर्ण_अगर /* CONFIG_IMA_READ_POLICY */

#पूर्ण_अगर /* __LINUX_IMA_H */
