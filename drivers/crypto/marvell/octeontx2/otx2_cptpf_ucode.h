<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only
 * Copyright (C) 2020 Marvell.
 */

#अगर_अघोषित __OTX2_CPTPF_UCODE_H
#घोषणा __OTX2_CPTPF_UCODE_H

#समावेश <linux/pci.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश "otx2_cpt_hw_types.h"
#समावेश "otx2_cpt_common.h"

/*
 * On OcteonTX2 platक्रमm IPSec ucode can use both IE and SE engines thereक्रमe
 * IE and SE engines can be attached to the same engine group.
 */
#घोषणा OTX2_CPT_MAX_ETYPES_PER_GRP 2

/* CPT ucode signature size */
#घोषणा OTX2_CPT_UCODE_SIGN_LEN     256

/* Microcode version string length */
#घोषणा OTX2_CPT_UCODE_VER_STR_SZ   44

/* Maximum number of supported engines/cores on OcteonTX2 platक्रमm */
#घोषणा OTX2_CPT_MAX_ENGINES        128

#घोषणा OTX2_CPT_ENGS_BITMASK_LEN   BITS_TO_LONGS(OTX2_CPT_MAX_ENGINES)

/* Microcode types */
क्रमागत otx2_cpt_ucode_type अणु
	OTX2_CPT_AE_UC_TYPE = 1,  /* AE-MAIN */
	OTX2_CPT_SE_UC_TYPE1 = 20,/* SE-MAIN - combination of 21 and 22 */
	OTX2_CPT_SE_UC_TYPE2 = 21,/* Fast Path IPSec + AirCrypto */
	OTX2_CPT_SE_UC_TYPE3 = 22,/*
				   * Hash + HMAC + FlexiCrypto + RNG +
				   * Full Feature IPSec + AirCrypto + Kasumi
				   */
	OTX2_CPT_IE_UC_TYPE1 = 30, /* IE-MAIN - combination of 31 and 32 */
	OTX2_CPT_IE_UC_TYPE2 = 31, /* Fast Path IPSec */
	OTX2_CPT_IE_UC_TYPE3 = 32, /*
				    * Hash + HMAC + FlexiCrypto + RNG +
				    * Full Future IPSec
				    */
पूर्ण;

काष्ठा otx2_cpt_biपंचांगap अणु
	अचिन्हित दीर्घ bits[OTX2_CPT_ENGS_BITMASK_LEN];
	पूर्णांक size;
पूर्ण;

काष्ठा otx2_cpt_engines अणु
	पूर्णांक type;
	पूर्णांक count;
पूर्ण;

/* Microcode version number */
काष्ठा otx2_cpt_ucode_ver_num अणु
	u8 nn;
	u8 xx;
	u8 yy;
	u8 zz;
पूर्ण;

काष्ठा otx2_cpt_ucode_hdr अणु
	काष्ठा otx2_cpt_ucode_ver_num ver_num;
	u8 ver_str[OTX2_CPT_UCODE_VER_STR_SZ];
	__be32 code_length;
	u32 padding[3];
पूर्ण;

काष्ठा otx2_cpt_ucode अणु
	u8 ver_str[OTX2_CPT_UCODE_VER_STR_SZ];/*
					       * ucode version in पढ़ोable
					       * क्रमmat
					       */
	काष्ठा otx2_cpt_ucode_ver_num ver_num;/* ucode version number */
	अक्षर filename[OTX2_CPT_NAME_LENGTH];/* ucode filename */
	dma_addr_t dma;		/* phys address of ucode image */
	व्योम *va;		/* virt address of ucode image */
	u32 size;		/* ucode image size */
	पूर्णांक type;		/* ucode image type SE, IE, AE or SE+IE */
पूर्ण;

काष्ठा otx2_cpt_uc_info_t अणु
	काष्ठा list_head list;
	काष्ठा otx2_cpt_ucode ucode;/* microcode inक्रमmation */
	स्थिर काष्ठा firmware *fw;
पूर्ण;

/* Maximum and current number of engines available क्रम all engine groups */
काष्ठा otx2_cpt_engs_available अणु
	पूर्णांक max_se_cnt;
	पूर्णांक max_ie_cnt;
	पूर्णांक max_ae_cnt;
	पूर्णांक se_cnt;
	पूर्णांक ie_cnt;
	पूर्णांक ae_cnt;
पूर्ण;

/* Engines reserved to an engine group */
काष्ठा otx2_cpt_engs_rsvd अणु
	पूर्णांक type;	/* engine type */
	पूर्णांक count;	/* number of engines attached */
	पूर्णांक offset;     /* स्थिरant offset of engine type in the biपंचांगap */
	अचिन्हित दीर्घ *bmap;		/* attached engines biपंचांगap */
	काष्ठा otx2_cpt_ucode *ucode;	/* ucode used by these engines */
पूर्ण;

काष्ठा otx2_cpt_mirror_info अणु
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

काष्ठा otx2_cpt_eng_grp_info अणु
	काष्ठा otx2_cpt_eng_grps *g; /* poपूर्णांकer to engine_groups काष्ठाure */
	/* engines attached */
	काष्ठा otx2_cpt_engs_rsvd engs[OTX2_CPT_MAX_ETYPES_PER_GRP];
	/* ucodes inक्रमmation */
	काष्ठा otx2_cpt_ucode ucode[OTX2_CPT_MAX_ETYPES_PER_GRP];
	/* engine group mirroring inक्रमmation */
	काष्ठा otx2_cpt_mirror_info mirror;
	पूर्णांक idx;	 /* engine group index */
	bool is_enabled; /*
			  * is engine group enabled, engine group is enabled
			  * when it has engines attached and ucode loaded
			  */
पूर्ण;

काष्ठा otx2_cpt_eng_grps अणु
	काष्ठा otx2_cpt_eng_grp_info grp[OTX2_CPT_MAX_ENGINE_GROUPS];
	काष्ठा otx2_cpt_engs_available avail;
	व्योम *obj;			/* device specअगरic data */
	पूर्णांक engs_num;			/* total number of engines supported */
	u8 eng_ref_cnt[OTX2_CPT_MAX_ENGINES];/* engines reference count */
	bool is_grps_created; /* Is the engine groups are alपढ़ोy created */
पूर्ण;
काष्ठा otx2_cptpf_dev;
पूर्णांक otx2_cpt_init_eng_grps(काष्ठा pci_dev *pdev,
			   काष्ठा otx2_cpt_eng_grps *eng_grps);
व्योम otx2_cpt_cleanup_eng_grps(काष्ठा pci_dev *pdev,
			       काष्ठा otx2_cpt_eng_grps *eng_grps);
पूर्णांक otx2_cpt_create_eng_grps(काष्ठा pci_dev *pdev,
			     काष्ठा otx2_cpt_eng_grps *eng_grps);
पूर्णांक otx2_cpt_disable_all_cores(काष्ठा otx2_cptpf_dev *cptpf);
पूर्णांक otx2_cpt_get_eng_grp(काष्ठा otx2_cpt_eng_grps *eng_grps, पूर्णांक eng_type);
पूर्णांक otx2_cpt_discover_eng_capabilities(काष्ठा otx2_cptpf_dev *cptpf);

#पूर्ण_अगर /* __OTX2_CPTPF_UCODE_H */
