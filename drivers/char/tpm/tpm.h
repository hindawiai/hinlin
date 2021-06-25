<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004 IBM Corporation
 * Copyright (C) 2015 Intel Corporation
 *
 * Authors:
 * Leendert van Doorn <leendert@watson.ibm.com>
 * Dave Safक्रमd <safक्रमd@watson.ibm.com>
 * Reiner Sailer <sailer@watson.ibm.com>
 * Kylene Hall <kjhall@us.ibm.com>
 *
 * Maपूर्णांकained by: <tpmdd-devel@lists.sourceक्रमge.net>
 *
 * Device driver क्रम TCG/TCPA TPM (trusted platक्रमm module).
 * Specअगरications at www.trustedcomputinggroup.org
 */

#अगर_अघोषित __TPM_H__
#घोषणा __TPM_H__

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/tpm.h>
#समावेश <linux/tpm_eventlog.h>

#अगर_घोषित CONFIG_X86
#समावेश <यंत्र/पूर्णांकel-family.h>
#पूर्ण_अगर

#घोषणा TPM_MINOR		224	/* officially asचिन्हित */
#घोषणा TPM_बफ_मानE		4096
#घोषणा TPM_NUM_DEVICES		65536
#घोषणा TPM_RETRY		50

क्रमागत tpm_समयout अणु
	TPM_TIMEOUT = 5,	/* msecs */
	TPM_TIMEOUT_RETRY = 100, /* msecs */
	TPM_TIMEOUT_RANGE_US = 300,	/* usecs */
	TPM_TIMEOUT_POLL = 1,	/* msecs */
	TPM_TIMEOUT_USECS_MIN = 100,      /* usecs */
	TPM_TIMEOUT_USECS_MAX = 500      /* usecs */
पूर्ण;

/* TPM addresses */
क्रमागत tpm_addr अणु
	TPM_SUPERIO_ADDR = 0x2E,
	TPM_ADDR = 0x4E,
पूर्ण;

#घोषणा TPM_WARN_RETRY          0x800
#घोषणा TPM_WARN_DOING_SELFTEST 0x802
#घोषणा TPM_ERR_DEACTIVATED     0x6
#घोषणा TPM_ERR_DISABLED        0x7
#घोषणा TPM_ERR_INVALID_POSTINIT 38

#घोषणा TPM_TAG_RQU_COMMAND 193

/* TPM2 specअगरic स्थिरants. */
#घोषणा TPM2_SPACE_BUFFER_SIZE		16384 /* 16 kB */

काष्ठा	stclear_flags_t अणु
	__be16	tag;
	u8	deactivated;
	u8	disableForceClear;
	u8	physicalPresence;
	u8	physicalPresenceLock;
	u8	bGlobalLock;
पूर्ण __packed;

काष्ठा tpm1_version अणु
	u8 major;
	u8 minor;
	u8 rev_major;
	u8 rev_minor;
पूर्ण __packed;

काष्ठा tpm1_version2 अणु
	__be16 tag;
	काष्ठा tpm1_version version;
पूर्ण __packed;

काष्ठा	समयout_t अणु
	__be32	a;
	__be32	b;
	__be32	c;
	__be32	d;
पूर्ण __packed;

काष्ठा duration_t अणु
	__be32	tpm_लघु;
	__be32	tpm_medium;
	__be32	tpm_दीर्घ;
पूर्ण __packed;

काष्ठा permanent_flags_t अणु
	__be16	tag;
	u8	disable;
	u8	ownership;
	u8	deactivated;
	u8	पढ़ोPubek;
	u8	disableOwnerClear;
	u8	allowMaपूर्णांकenance;
	u8	physicalPresenceLअगरeसमयLock;
	u8	physicalPresenceHWEnable;
	u8	physicalPresenceCMDEnable;
	u8	CEKPUsed;
	u8	TPMpost;
	u8	TPMpostLock;
	u8	FIPS;
	u8	चालक;
	u8	enableRevokeEK;
	u8	nvLocked;
	u8	पढ़ोSRKPub;
	u8	tpmEstablished;
	u8	मुख्यtenanceDone;
	u8	disableFullDALogicInfo;
पूर्ण __packed;

प्रकार जोड़ अणु
	काष्ठा	permanent_flags_t perm_flags;
	काष्ठा	stclear_flags_t	stclear_flags;
	__u8	owned;
	__be32	num_pcrs;
	काष्ठा tpm1_version version1;
	काष्ठा tpm1_version2 version2;
	__be32	manufacturer_id;
	काष्ठा समयout_t  समयout;
	काष्ठा duration_t duration;
पूर्ण cap_t;

क्रमागत tpm_capabilities अणु
	TPM_CAP_FLAG = 4,
	TPM_CAP_PROP = 5,
	TPM_CAP_VERSION_1_1 = 0x06,
	TPM_CAP_VERSION_1_2 = 0x1A,
पूर्ण;

क्रमागत tpm_sub_capabilities अणु
	TPM_CAP_PROP_PCR = 0x101,
	TPM_CAP_PROP_MANUFACTURER = 0x103,
	TPM_CAP_FLAG_PERM = 0x108,
	TPM_CAP_FLAG_VOL = 0x109,
	TPM_CAP_PROP_OWNER = 0x111,
	TPM_CAP_PROP_TIS_TIMEOUT = 0x115,
	TPM_CAP_PROP_TIS_DURATION = 0x120,
पूर्ण;


/* 128 bytes is an arbitrary cap. This could be as large as TPM_बफ_मानE - 18
 * bytes, but 128 is still a relatively large number of अक्रमom bytes and
 * anything much bigger causes users of काष्ठा tpm_cmd_t to start getting
 * compiler warnings about stack frame size. */
#घोषणा TPM_MAX_RNG_DATA	128

बाह्य काष्ठा class *tpm_class;
बाह्य काष्ठा class *tpmrm_class;
बाह्य dev_t tpm_devt;
बाह्य स्थिर काष्ठा file_operations tpm_fops;
बाह्य स्थिर काष्ठा file_operations tpmrm_fops;
बाह्य काष्ठा idr dev_nums_idr;

sमाप_प्रकार tpm_transmit(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार bufsiz);
पूर्णांक tpm_get_समयouts(काष्ठा tpm_chip *);
पूर्णांक tpm_स्वतः_startup(काष्ठा tpm_chip *chip);

पूर्णांक tpm1_pm_suspend(काष्ठा tpm_chip *chip, u32 tpm_suspend_pcr);
पूर्णांक tpm1_स्वतः_startup(काष्ठा tpm_chip *chip);
पूर्णांक tpm1_करो_selftest(काष्ठा tpm_chip *chip);
पूर्णांक tpm1_get_समयouts(काष्ठा tpm_chip *chip);
अचिन्हित दीर्घ tpm1_calc_ordinal_duration(काष्ठा tpm_chip *chip, u32 ordinal);
पूर्णांक tpm1_pcr_extend(काष्ठा tpm_chip *chip, u32 pcr_idx, स्थिर u8 *hash,
		    स्थिर अक्षर *log_msg);
पूर्णांक tpm1_pcr_पढ़ो(काष्ठा tpm_chip *chip, u32 pcr_idx, u8 *res_buf);
sमाप_प्रकार tpm1_अ_लोap(काष्ठा tpm_chip *chip, u32 subcap_id, cap_t *cap,
		    स्थिर अक्षर *desc, माप_प्रकार min_cap_length);
पूर्णांक tpm1_get_अक्रमom(काष्ठा tpm_chip *chip, u8 *out, माप_प्रकार max);
पूर्णांक tpm1_get_pcr_allocation(काष्ठा tpm_chip *chip);
अचिन्हित दीर्घ tpm_calc_ordinal_duration(काष्ठा tpm_chip *chip, u32 ordinal);
पूर्णांक tpm_pm_suspend(काष्ठा device *dev);
पूर्णांक tpm_pm_resume(काष्ठा device *dev);

अटल अंतरभूत व्योम tpm_msleep(अचिन्हित पूर्णांक delay_msec)
अणु
	usleep_range((delay_msec * 1000) - TPM_TIMEOUT_RANGE_US,
		     delay_msec * 1000);
पूर्ण;

पूर्णांक tpm_chip_start(काष्ठा tpm_chip *chip);
व्योम tpm_chip_stop(काष्ठा tpm_chip *chip);
काष्ठा tpm_chip *tpm_find_get_ops(काष्ठा tpm_chip *chip);

काष्ठा tpm_chip *tpm_chip_alloc(काष्ठा device *dev,
				स्थिर काष्ठा tpm_class_ops *ops);
काष्ठा tpm_chip *tpmm_chip_alloc(काष्ठा device *pdev,
				 स्थिर काष्ठा tpm_class_ops *ops);
पूर्णांक tpm_chip_रेजिस्टर(काष्ठा tpm_chip *chip);
व्योम tpm_chip_unरेजिस्टर(काष्ठा tpm_chip *chip);

व्योम tpm_sysfs_add_device(काष्ठा tpm_chip *chip);


#अगर_घोषित CONFIG_ACPI
बाह्य व्योम tpm_add_ppi(काष्ठा tpm_chip *chip);
#अन्यथा
अटल अंतरभूत व्योम tpm_add_ppi(काष्ठा tpm_chip *chip)
अणु
पूर्ण
#पूर्ण_अगर

पूर्णांक tpm2_get_समयouts(काष्ठा tpm_chip *chip);
पूर्णांक tpm2_pcr_पढ़ो(काष्ठा tpm_chip *chip, u32 pcr_idx,
		  काष्ठा tpm_digest *digest, u16 *digest_size_ptr);
पूर्णांक tpm2_pcr_extend(काष्ठा tpm_chip *chip, u32 pcr_idx,
		    काष्ठा tpm_digest *digests);
पूर्णांक tpm2_get_अक्रमom(काष्ठा tpm_chip *chip, u8 *dest, माप_प्रकार max);
sमाप_प्रकार tpm2_get_tpm_pt(काष्ठा tpm_chip *chip, u32 property_id,
			u32 *value, स्थिर अक्षर *desc);

sमाप_प्रकार tpm2_get_pcr_allocation(काष्ठा tpm_chip *chip);
पूर्णांक tpm2_स्वतः_startup(काष्ठा tpm_chip *chip);
व्योम tpm2_shutकरोwn(काष्ठा tpm_chip *chip, u16 shutकरोwn_type);
अचिन्हित दीर्घ tpm2_calc_ordinal_duration(काष्ठा tpm_chip *chip, u32 ordinal);
पूर्णांक tpm2_probe(काष्ठा tpm_chip *chip);
पूर्णांक tpm2_get_cc_attrs_tbl(काष्ठा tpm_chip *chip);
पूर्णांक tpm2_find_cc(काष्ठा tpm_chip *chip, u32 cc);
पूर्णांक tpm2_init_space(काष्ठा tpm_space *space, अचिन्हित पूर्णांक buf_size);
व्योम tpm2_del_space(काष्ठा tpm_chip *chip, काष्ठा tpm_space *space);
व्योम tpm2_flush_space(काष्ठा tpm_chip *chip);
पूर्णांक tpm2_prepare_space(काष्ठा tpm_chip *chip, काष्ठा tpm_space *space, u8 *cmd,
		       माप_प्रकार cmdsiz);
पूर्णांक tpm2_commit_space(काष्ठा tpm_chip *chip, काष्ठा tpm_space *space, व्योम *buf,
		      माप_प्रकार *bufsiz);

व्योम tpm_bios_log_setup(काष्ठा tpm_chip *chip);
व्योम tpm_bios_log_tearकरोwn(काष्ठा tpm_chip *chip);
पूर्णांक tpm_dev_common_init(व्योम);
व्योम tpm_dev_common_निकास(व्योम);
#पूर्ण_अगर
