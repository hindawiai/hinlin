<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 * Marvell OcteonTX CPT driver
 *
 * Copyright (C) 2019 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#अगर_अघोषित __OTX_CPTPF_UCODE_H
#घोषणा __OTX_CPTPF_UCODE_H

#समावेश <linux/pci.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश "otx_cpt_hw_types.h"

/* CPT ucode name maximum length */
#घोषणा OTX_CPT_UCODE_NAME_LENGTH	64
/*
 * On OcteonTX 83xx platक्रमm, only one type of engines is allowed to be
 * attached to an engine group.
 */
#घोषणा OTX_CPT_MAX_ETYPES_PER_GRP	1

/* Default tar archive file names */
#घोषणा OTX_CPT_UCODE_TAR_खाता_NAME	"cpt8x-mc.tar"

/* CPT ucode alignment */
#घोषणा OTX_CPT_UCODE_ALIGNMENT		128

/* CPT ucode signature size */
#घोषणा OTX_CPT_UCODE_SIGN_LEN		256

/* Microcode version string length */
#घोषणा OTX_CPT_UCODE_VER_STR_SZ	44

/* Maximum number of supported engines/cores on OcteonTX 83XX platक्रमm */
#घोषणा OTX_CPT_MAX_ENGINES		64

#घोषणा OTX_CPT_ENGS_BITMASK_LEN	(OTX_CPT_MAX_ENGINES/(BITS_PER_BYTE * \
					 माप(अचिन्हित दीर्घ)))

/* Microcode types */
क्रमागत otx_cpt_ucode_type अणु
	OTX_CPT_AE_UC_TYPE =	1,  /* AE-MAIN */
	OTX_CPT_SE_UC_TYPE1 =	20, /* SE-MAIN - combination of 21 and 22 */
	OTX_CPT_SE_UC_TYPE2 =	21, /* Fast Path IPSec + AirCrypto */
	OTX_CPT_SE_UC_TYPE3 =	22, /*
				     * Hash + HMAC + FlexiCrypto + RNG + Full
				     * Feature IPSec + AirCrypto + Kasumi
				     */
पूर्ण;

काष्ठा otx_cpt_biपंचांगap अणु
	अचिन्हित दीर्घ bits[OTX_CPT_ENGS_BITMASK_LEN];
	पूर्णांक size;
पूर्ण;

काष्ठा otx_cpt_engines अणु
	पूर्णांक type;
	पूर्णांक count;
पूर्ण;

/* Microcode version number */
काष्ठा otx_cpt_ucode_ver_num अणु
	u8 nn;
	u8 xx;
	u8 yy;
	u8 zz;
पूर्ण;

काष्ठा otx_cpt_ucode_hdr अणु
	काष्ठा otx_cpt_ucode_ver_num ver_num;
	u8 ver_str[OTX_CPT_UCODE_VER_STR_SZ];
	__be32 code_length;
	u32 padding[3];
पूर्ण;

काष्ठा otx_cpt_ucode अणु
	u8 ver_str[OTX_CPT_UCODE_VER_STR_SZ];/*
					      * ucode version in पढ़ोable क्रमmat
					      */
	काष्ठा otx_cpt_ucode_ver_num ver_num;/* ucode version number */
	अक्षर filename[OTX_CPT_UCODE_NAME_LENGTH];	 /* ucode filename */
	dma_addr_t dma;		/* phys address of ucode image */
	dma_addr_t align_dma;	/* aligned phys address of ucode image */
	व्योम *va;		/* virt address of ucode image */
	व्योम *align_va;		/* aligned virt address of ucode image */
	u32 size;		/* ucode image size */
	पूर्णांक type;		/* ucode image type SE or AE */
पूर्ण;

काष्ठा tar_ucode_info_t अणु
	काष्ठा list_head list;
	काष्ठा otx_cpt_ucode ucode;/* microcode inक्रमmation */
	स्थिर u8 *ucode_ptr;	/* poपूर्णांकer to microcode in tar archive */
पूर्ण;

/* Maximum and current number of engines available क्रम all engine groups */
काष्ठा otx_cpt_engs_available अणु
	पूर्णांक max_se_cnt;
	पूर्णांक max_ae_cnt;
	पूर्णांक se_cnt;
	पूर्णांक ae_cnt;
पूर्ण;

/* Engines reserved to an engine group */
काष्ठा otx_cpt_engs_rsvd अणु
	पूर्णांक type;	/* engine type */
	पूर्णांक count;	/* number of engines attached */
	पूर्णांक offset;     /* स्थिरant offset of engine type in the biपंचांगap */
	अचिन्हित दीर्घ *bmap;		/* attached engines biपंचांगap */
	काष्ठा otx_cpt_ucode *ucode;	/* ucode used by these engines */
पूर्ण;

काष्ठा otx_cpt_mirror_info अणु
	पूर्णांक is_ena;	/*
			 * is mirroring enabled, it is set only क्रम engine
			 * group which mirrors another engine group
			 */
	पूर्णांक idx;	/*
			 * index of engine group which is mirrored by this
			 * group, set only क्रम engine group which mirrors
			 * another group
			 */
	पूर्णांक ref_count;	/*
			 * number of बार this engine group is mirrored by
			 * other groups, this is set only क्रम engine group
			 * which is mirrored by other group(s)
			 */
पूर्ण;

काष्ठा otx_cpt_eng_grp_info अणु
	काष्ठा otx_cpt_eng_grps *g; /* poपूर्णांकer to engine_groups काष्ठाure */
	काष्ठा device_attribute info_attr; /* group info entry attr */
	/* engines attached */
	काष्ठा otx_cpt_engs_rsvd engs[OTX_CPT_MAX_ETYPES_PER_GRP];
	/* Microcode inक्रमmation */
	काष्ठा otx_cpt_ucode ucode[OTX_CPT_MAX_ETYPES_PER_GRP];
	/* sysfs info entry name */
	अक्षर sysfs_info_name[OTX_CPT_UCODE_NAME_LENGTH];
	/* engine group mirroring inक्रमmation */
	काष्ठा otx_cpt_mirror_info mirror;
	पूर्णांक idx;	 /* engine group index */
	bool is_enabled; /*
			  * is engine group enabled, engine group is enabled
			  * when it has engines attached and ucode loaded
			  */
पूर्ण;

काष्ठा otx_cpt_eng_grps अणु
	काष्ठा otx_cpt_eng_grp_info grp[OTX_CPT_MAX_ENGINE_GROUPS];
	काष्ठा device_attribute ucode_load_attr;/* ucode load attr */
	काष्ठा otx_cpt_engs_available avail;
	काष्ठा mutex lock;
	व्योम *obj;
	पूर्णांक engs_num;			/* total number of engines supported */
	पूर्णांक eng_types_supported;	/* engine types supported SE, AE */
	u8 eng_ref_cnt[OTX_CPT_MAX_ENGINES];/* engines reference count */
	bool is_ucode_load_created;	/* is ucode_load sysfs entry created */
	bool is_first_try; /* is this first try to create kcrypto engine grp */
	bool is_rकरोnly;	/* करो engine groups configuration can be modअगरied */
पूर्ण;

पूर्णांक otx_cpt_init_eng_grps(काष्ठा pci_dev *pdev,
			  काष्ठा otx_cpt_eng_grps *eng_grps, पूर्णांक pf_type);
व्योम otx_cpt_cleanup_eng_grps(काष्ठा pci_dev *pdev,
			      काष्ठा otx_cpt_eng_grps *eng_grps);
पूर्णांक otx_cpt_try_create_शेष_eng_grps(काष्ठा pci_dev *pdev,
					काष्ठा otx_cpt_eng_grps *eng_grps,
					पूर्णांक pf_type);
व्योम otx_cpt_set_eng_grps_is_rकरोnly(काष्ठा otx_cpt_eng_grps *eng_grps,
				    bool is_rकरोnly);
पूर्णांक otx_cpt_uc_supports_eng_type(काष्ठा otx_cpt_ucode *ucode, पूर्णांक eng_type);
पूर्णांक otx_cpt_eng_grp_has_eng_type(काष्ठा otx_cpt_eng_grp_info *eng_grp,
				 पूर्णांक eng_type);

#पूर्ण_अगर /* __OTX_CPTPF_UCODE_H */
