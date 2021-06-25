<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only
 * Copyright (C) 2020 Marvell.
 */

#अगर_अघोषित __OTX2_CPT_COMMON_H
#घोषणा __OTX2_CPT_COMMON_H

#समावेश <linux/pci.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/crypto.h>
#समावेश "otx2_cpt_hw_types.h"
#समावेश "rvu.h"
#समावेश "mbox.h"

#घोषणा OTX2_CPT_MAX_VFS_NUM 128
#घोषणा OTX2_CPT_RVU_FUNC_ADDR_S(blk, slot, offs) \
		(((blk) << 20) | ((slot) << 12) | (offs))
#घोषणा OTX2_CPT_RVU_PFFUNC(pf, func)	\
		((((pf) & RVU_PFVF_PF_MASK) << RVU_PFVF_PF_SHIFT) | \
		(((func) & RVU_PFVF_FUNC_MASK) << RVU_PFVF_FUNC_SHIFT))

#घोषणा OTX2_CPT_INVALID_CRYPTO_ENG_GRP 0xFF
#घोषणा OTX2_CPT_NAME_LENGTH 64
#घोषणा OTX2_CPT_DMA_MINALIGN 128

#घोषणा BAD_OTX2_CPT_ENG_TYPE OTX2_CPT_MAX_ENG_TYPES

क्रमागत otx2_cpt_eng_type अणु
	OTX2_CPT_AE_TYPES = 1,
	OTX2_CPT_SE_TYPES = 2,
	OTX2_CPT_IE_TYPES = 3,
	OTX2_CPT_MAX_ENG_TYPES,
पूर्ण;

/* Take mbox id from end of CPT mbox range in AF (range 0xA00 - 0xBFF) */
#घोषणा MBOX_MSG_GET_ENG_GRP_NUM        0xBFF
#घोषणा MBOX_MSG_GET_CAPS               0xBFD
#घोषणा MBOX_MSG_GET_KVF_LIMITS         0xBFC

/*
 * Message request and response to get engine group number
 * which has attached a given type of engines (SE, AE, IE)
 * This messages are only used between CPT PF <=> CPT VF
 */
काष्ठा otx2_cpt_egrp_num_msg अणु
	काष्ठा mbox_msghdr hdr;
	u8 eng_type;
पूर्ण;

काष्ठा otx2_cpt_egrp_num_rsp अणु
	काष्ठा mbox_msghdr hdr;
	u8 eng_type;
	u8 eng_grp_num;
पूर्ण;

/*
 * Message request and response to get kernel crypto limits
 * This messages are only used between CPT PF <-> CPT VF
 */
काष्ठा otx2_cpt_kvf_limits_msg अणु
	काष्ठा mbox_msghdr hdr;
पूर्ण;

काष्ठा otx2_cpt_kvf_limits_rsp अणु
	काष्ठा mbox_msghdr hdr;
	u8 kvf_limits;
पूर्ण;

/* CPT HW capabilities */
जोड़ otx2_cpt_eng_caps अणु
	u64 u;
	काष्ठा अणु
		u64 reserved_0_4:5;
		u64 mul:1;
		u64 sha1_sha2:1;
		u64 chacha20:1;
		u64 zuc_snow3g:1;
		u64 sha3:1;
		u64 aes:1;
		u64 kasumi:1;
		u64 des:1;
		u64 crc:1;
		u64 reserved_14_63:50;
	पूर्ण;
पूर्ण;

/*
 * Message request and response to get HW capabilities क्रम each
 * engine type (SE, IE, AE).
 * This messages are only used between CPT PF <=> CPT VF
 */
काष्ठा otx2_cpt_caps_msg अणु
	काष्ठा mbox_msghdr hdr;
पूर्ण;

काष्ठा otx2_cpt_caps_rsp अणु
	काष्ठा mbox_msghdr hdr;
	u16 cpt_pf_drv_version;
	u8 cpt_revision;
	जोड़ otx2_cpt_eng_caps eng_caps[OTX2_CPT_MAX_ENG_TYPES];
पूर्ण;

अटल अंतरभूत व्योम otx2_cpt_ग_लिखो64(व्योम __iomem *reg_base, u64 blk, u64 slot,
				    u64 offs, u64 val)
अणु
	ग_लिखोq_relaxed(val, reg_base +
		       OTX2_CPT_RVU_FUNC_ADDR_S(blk, slot, offs));
पूर्ण

अटल अंतरभूत u64 otx2_cpt_पढ़ो64(व्योम __iomem *reg_base, u64 blk, u64 slot,
				  u64 offs)
अणु
	वापस पढ़ोq_relaxed(reg_base +
			     OTX2_CPT_RVU_FUNC_ADDR_S(blk, slot, offs));
पूर्ण

पूर्णांक otx2_cpt_send_पढ़ोy_msg(काष्ठा otx2_mbox *mbox, काष्ठा pci_dev *pdev);
पूर्णांक otx2_cpt_send_mbox_msg(काष्ठा otx2_mbox *mbox, काष्ठा pci_dev *pdev);

पूर्णांक otx2_cpt_send_af_reg_requests(काष्ठा otx2_mbox *mbox,
				  काष्ठा pci_dev *pdev);
पूर्णांक otx2_cpt_add_पढ़ो_af_reg(काष्ठा otx2_mbox *mbox, काष्ठा pci_dev *pdev,
			     u64 reg, u64 *val, पूर्णांक blkaddr);
पूर्णांक otx2_cpt_add_ग_लिखो_af_reg(काष्ठा otx2_mbox *mbox, काष्ठा pci_dev *pdev,
			      u64 reg, u64 val, पूर्णांक blkaddr);
पूर्णांक otx2_cpt_पढ़ो_af_reg(काष्ठा otx2_mbox *mbox, काष्ठा pci_dev *pdev,
			 u64 reg, u64 *val, पूर्णांक blkaddr);
पूर्णांक otx2_cpt_ग_लिखो_af_reg(काष्ठा otx2_mbox *mbox, काष्ठा pci_dev *pdev,
			  u64 reg, u64 val, पूर्णांक blkaddr);
काष्ठा otx2_cptlfs_info;
पूर्णांक otx2_cpt_attach_rscrs_msg(काष्ठा otx2_cptlfs_info *lfs);
पूर्णांक otx2_cpt_detach_rsrcs_msg(काष्ठा otx2_cptlfs_info *lfs);
पूर्णांक otx2_cpt_msix_offset_msg(काष्ठा otx2_cptlfs_info *lfs);

#पूर्ण_अगर /* __OTX2_CPT_COMMON_H */
