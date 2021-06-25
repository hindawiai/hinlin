<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2010-2015,2019 The Linux Foundation. All rights reserved.
 */
#अगर_अघोषित __QCOM_SCM_INT_H
#घोषणा __QCOM_SCM_INT_H

क्रमागत qcom_scm_convention अणु
	SMC_CONVENTION_UNKNOWN,
	SMC_CONVENTION_LEGACY,
	SMC_CONVENTION_ARM_32,
	SMC_CONVENTION_ARM_64,
पूर्ण;

बाह्य क्रमागत qcom_scm_convention qcom_scm_convention;

#घोषणा MAX_QCOM_SCM_ARGS 10
#घोषणा MAX_QCOM_SCM_RETS 3

क्रमागत qcom_scm_arg_types अणु
	QCOM_SCM_VAL,
	QCOM_SCM_RO,
	QCOM_SCM_RW,
	QCOM_SCM_BUFVAL,
पूर्ण;

#घोषणा QCOM_SCM_ARGS_IMPL(num, a, b, c, d, e, f, g, h, i, j, ...) (\
			   (((a) & 0x3) << 4) | \
			   (((b) & 0x3) << 6) | \
			   (((c) & 0x3) << 8) | \
			   (((d) & 0x3) << 10) | \
			   (((e) & 0x3) << 12) | \
			   (((f) & 0x3) << 14) | \
			   (((g) & 0x3) << 16) | \
			   (((h) & 0x3) << 18) | \
			   (((i) & 0x3) << 20) | \
			   (((j) & 0x3) << 22) | \
			   ((num) & 0xf))

#घोषणा QCOM_SCM_ARGS(...) QCOM_SCM_ARGS_IMPL(__VA_ARGS__, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)


/**
 * काष्ठा qcom_scm_desc
 * @arginfo:	Metadata describing the arguments in args[]
 * @args:	The array of arguments क्रम the secure syscall
 */
काष्ठा qcom_scm_desc अणु
	u32 svc;
	u32 cmd;
	u32 arginfo;
	u64 args[MAX_QCOM_SCM_ARGS];
	u32 owner;
पूर्ण;

/**
 * काष्ठा qcom_scm_res
 * @result:	The values वापसed by the secure syscall
 */
काष्ठा qcom_scm_res अणु
	u64 result[MAX_QCOM_SCM_RETS];
पूर्ण;

#घोषणा SCM_SMC_FNID(s, c)	((((s) & 0xFF) << 8) | ((c) & 0xFF))
बाह्य पूर्णांक __scm_smc_call(काष्ठा device *dev, स्थिर काष्ठा qcom_scm_desc *desc,
			  क्रमागत qcom_scm_convention qcom_convention,
			  काष्ठा qcom_scm_res *res, bool atomic);
#घोषणा scm_smc_call(dev, desc, res, atomic) \
	__scm_smc_call((dev), (desc), qcom_scm_convention, (res), (atomic))

#घोषणा SCM_LEGACY_FNID(s, c)	(((s) << 10) | ((c) & 0x3ff))
बाह्य पूर्णांक scm_legacy_call_atomic(काष्ठा device *dev,
				  स्थिर काष्ठा qcom_scm_desc *desc,
				  काष्ठा qcom_scm_res *res);
बाह्य पूर्णांक scm_legacy_call(काष्ठा device *dev, स्थिर काष्ठा qcom_scm_desc *desc,
			   काष्ठा qcom_scm_res *res);

#घोषणा QCOM_SCM_SVC_BOOT		0x01
#घोषणा QCOM_SCM_BOOT_SET_ADDR		0x01
#घोषणा QCOM_SCM_BOOT_TERMINATE_PC	0x02
#घोषणा QCOM_SCM_BOOT_SET_DLOAD_MODE	0x10
#घोषणा QCOM_SCM_BOOT_SET_REMOTE_STATE	0x0a
#घोषणा QCOM_SCM_FLUSH_FLAG_MASK	0x3

#घोषणा QCOM_SCM_SVC_PIL		0x02
#घोषणा QCOM_SCM_PIL_PAS_INIT_IMAGE	0x01
#घोषणा QCOM_SCM_PIL_PAS_MEM_SETUP	0x02
#घोषणा QCOM_SCM_PIL_PAS_AUTH_AND_RESET	0x05
#घोषणा QCOM_SCM_PIL_PAS_SHUTDOWN	0x06
#घोषणा QCOM_SCM_PIL_PAS_IS_SUPPORTED	0x07
#घोषणा QCOM_SCM_PIL_PAS_MSS_RESET	0x0a

#घोषणा QCOM_SCM_SVC_IO			0x05
#घोषणा QCOM_SCM_IO_READ		0x01
#घोषणा QCOM_SCM_IO_WRITE		0x02

#घोषणा QCOM_SCM_SVC_INFO		0x06
#घोषणा QCOM_SCM_INFO_IS_CALL_AVAIL	0x01

#घोषणा QCOM_SCM_SVC_MP				0x0c
#घोषणा QCOM_SCM_MP_RESTORE_SEC_CFG		0x02
#घोषणा QCOM_SCM_MP_IOMMU_SECURE_PTBL_SIZE	0x03
#घोषणा QCOM_SCM_MP_IOMMU_SECURE_PTBL_INIT	0x04
#घोषणा QCOM_SCM_MP_VIDEO_VAR			0x08
#घोषणा QCOM_SCM_MP_ASSIGN			0x16

#घोषणा QCOM_SCM_SVC_OCMEM		0x0f
#घोषणा QCOM_SCM_OCMEM_LOCK_CMD		0x01
#घोषणा QCOM_SCM_OCMEM_UNLOCK_CMD	0x02

#घोषणा QCOM_SCM_SVC_ES			0x10	/* Enterprise Security */
#घोषणा QCOM_SCM_ES_INVALIDATE_ICE_KEY	0x03
#घोषणा QCOM_SCM_ES_CONFIG_SET_ICE_KEY	0x04

#घोषणा QCOM_SCM_SVC_HDCP		0x11
#घोषणा QCOM_SCM_HDCP_INVOKE		0x01

#घोषणा QCOM_SCM_SVC_SMMU_PROGRAM		0x15
#घोषणा QCOM_SCM_SMMU_CONFIG_ERRATA1		0x03
#घोषणा QCOM_SCM_SMMU_CONFIG_ERRATA1_CLIENT_ALL	0x02

बाह्य व्योम __qcom_scm_init(व्योम);

/* common error codes */
#घोषणा QCOM_SCM_V2_EBUSY	-12
#घोषणा QCOM_SCM_ENOMEM		-5
#घोषणा QCOM_SCM_EOPNOTSUPP	-4
#घोषणा QCOM_SCM_EINVAL_ADDR	-3
#घोषणा QCOM_SCM_EINVAL_ARG	-2
#घोषणा QCOM_SCM_ERROR		-1
#घोषणा QCOM_SCM_INTERRUPTED	1

अटल अंतरभूत पूर्णांक qcom_scm_remap_error(पूर्णांक err)
अणु
	चयन (err) अणु
	हाल QCOM_SCM_ERROR:
		वापस -EIO;
	हाल QCOM_SCM_EINVAL_ADDR:
	हाल QCOM_SCM_EINVAL_ARG:
		वापस -EINVAL;
	हाल QCOM_SCM_EOPNOTSUPP:
		वापस -EOPNOTSUPP;
	हाल QCOM_SCM_ENOMEM:
		वापस -ENOMEM;
	हाल QCOM_SCM_V2_EBUSY:
		वापस -EBUSY;
	पूर्ण
	वापस -EINVAL;
पूर्ण

#पूर्ण_अगर
