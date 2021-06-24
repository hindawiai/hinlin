<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (c) 2003-2019, Intel Corporation. All rights reserved.
 * Intel Management Engine Interface (Intel MEI) Linux driver
 */
#अगर_अघोषित _MEI_HW_MEI_REGS_H_
#घोषणा _MEI_HW_MEI_REGS_H_

/*
 * MEI device IDs
 */
#घोषणा MEI_DEV_ID_82946GZ    0x2974  /* 82946GZ/GL */
#घोषणा MEI_DEV_ID_82G35      0x2984  /* 82G35 Express */
#घोषणा MEI_DEV_ID_82Q965     0x2994  /* 82Q963/Q965 */
#घोषणा MEI_DEV_ID_82G965     0x29A4  /* 82P965/G965 */

#घोषणा MEI_DEV_ID_82GM965    0x2A04  /* Mobile PM965/GM965 */
#घोषणा MEI_DEV_ID_82GME965   0x2A14  /* Mobile GME965/GLE960 */

#घोषणा MEI_DEV_ID_ICH9_82Q35 0x29B4  /* 82Q35 Express */
#घोषणा MEI_DEV_ID_ICH9_82G33 0x29C4  /* 82G33/G31/P35/P31 Express */
#घोषणा MEI_DEV_ID_ICH9_82Q33 0x29D4  /* 82Q33 Express */
#घोषणा MEI_DEV_ID_ICH9_82X38 0x29E4  /* 82X38/X48 Express */
#घोषणा MEI_DEV_ID_ICH9_3200  0x29F4  /* 3200/3210 Server */

#घोषणा MEI_DEV_ID_ICH9_6     0x28B4  /* Bearlake */
#घोषणा MEI_DEV_ID_ICH9_7     0x28C4  /* Bearlake */
#घोषणा MEI_DEV_ID_ICH9_8     0x28D4  /* Bearlake */
#घोषणा MEI_DEV_ID_ICH9_9     0x28E4  /* Bearlake */
#घोषणा MEI_DEV_ID_ICH9_10    0x28F4  /* Bearlake */

#घोषणा MEI_DEV_ID_ICH9M_1    0x2A44  /* Cantiga */
#घोषणा MEI_DEV_ID_ICH9M_2    0x2A54  /* Cantiga */
#घोषणा MEI_DEV_ID_ICH9M_3    0x2A64  /* Cantiga */
#घोषणा MEI_DEV_ID_ICH9M_4    0x2A74  /* Cantiga */

#घोषणा MEI_DEV_ID_ICH10_1    0x2E04  /* Eaglelake */
#घोषणा MEI_DEV_ID_ICH10_2    0x2E14  /* Eaglelake */
#घोषणा MEI_DEV_ID_ICH10_3    0x2E24  /* Eaglelake */
#घोषणा MEI_DEV_ID_ICH10_4    0x2E34  /* Eaglelake */

#घोषणा MEI_DEV_ID_IBXPK_1    0x3B64  /* Calpella */
#घोषणा MEI_DEV_ID_IBXPK_2    0x3B65  /* Calpella */

#घोषणा MEI_DEV_ID_CPT_1      0x1C3A  /* Couger Poपूर्णांक */
#घोषणा MEI_DEV_ID_PBG_1      0x1D3A  /* C600/X79 Patsburg */

#घोषणा MEI_DEV_ID_PPT_1      0x1E3A  /* Panther Poपूर्णांक */
#घोषणा MEI_DEV_ID_PPT_2      0x1CBA  /* Panther Poपूर्णांक */
#घोषणा MEI_DEV_ID_PPT_3      0x1DBA  /* Panther Poपूर्णांक */

#घोषणा MEI_DEV_ID_LPT_H      0x8C3A  /* Lynx Poपूर्णांक H */
#घोषणा MEI_DEV_ID_LPT_W      0x8D3A  /* Lynx Poपूर्णांक - Wellsburg */
#घोषणा MEI_DEV_ID_LPT_LP     0x9C3A  /* Lynx Poपूर्णांक LP */
#घोषणा MEI_DEV_ID_LPT_HR     0x8CBA  /* Lynx Poपूर्णांक H Refresh */

#घोषणा MEI_DEV_ID_WPT_LP     0x9CBA  /* Wildcat Poपूर्णांक LP */
#घोषणा MEI_DEV_ID_WPT_LP_2   0x9CBB  /* Wildcat Poपूर्णांक LP 2 */

#घोषणा MEI_DEV_ID_SPT        0x9D3A  /* Sunrise Poपूर्णांक */
#घोषणा MEI_DEV_ID_SPT_2      0x9D3B  /* Sunrise Poपूर्णांक 2 */
#घोषणा MEI_DEV_ID_SPT_3      0x9D3E  /* Sunrise Poपूर्णांक 3 (iToutch) */
#घोषणा MEI_DEV_ID_SPT_H      0xA13A  /* Sunrise Poपूर्णांक H */
#घोषणा MEI_DEV_ID_SPT_H_2    0xA13B  /* Sunrise Poपूर्णांक H 2 */

#घोषणा MEI_DEV_ID_LBG        0xA1BA  /* Lewisburg (SPT) */

#घोषणा MEI_DEV_ID_BXT_M      0x1A9A  /* Broxton M */
#घोषणा MEI_DEV_ID_APL_I      0x5A9A  /* Apollo Lake I */

#घोषणा MEI_DEV_ID_DNV_IE     0x19E5  /* Denverton IE */

#घोषणा MEI_DEV_ID_GLK        0x319A  /* Gemini Lake */

#घोषणा MEI_DEV_ID_KBP        0xA2BA  /* Kaby Poपूर्णांक */
#घोषणा MEI_DEV_ID_KBP_2      0xA2BB  /* Kaby Poपूर्णांक 2 */
#घोषणा MEI_DEV_ID_KBP_3      0xA2BE  /* Kaby Poपूर्णांक 3 (iTouch) */

#घोषणा MEI_DEV_ID_CNP_LP     0x9DE0  /* Cannon Poपूर्णांक LP */
#घोषणा MEI_DEV_ID_CNP_LP_3   0x9DE4  /* Cannon Poपूर्णांक LP 3 (iTouch) */
#घोषणा MEI_DEV_ID_CNP_H      0xA360  /* Cannon Poपूर्णांक H */
#घोषणा MEI_DEV_ID_CNP_H_3    0xA364  /* Cannon Poपूर्णांक H 3 (iTouch) */

#घोषणा MEI_DEV_ID_CMP_LP     0x02e0  /* Comet Poपूर्णांक LP */
#घोषणा MEI_DEV_ID_CMP_LP_3   0x02e4  /* Comet Poपूर्णांक LP 3 (iTouch) */

#घोषणा MEI_DEV_ID_CMP_V      0xA3BA  /* Comet Poपूर्णांक Lake V */

#घोषणा MEI_DEV_ID_CMP_H      0x06e0  /* Comet Lake H */
#घोषणा MEI_DEV_ID_CMP_H_3    0x06e4  /* Comet Lake H 3 (iTouch) */

#घोषणा MEI_DEV_ID_CDF        0x18D3  /* Cedar Fork */

#घोषणा MEI_DEV_ID_ICP_LP     0x34E0  /* Ice Lake Poपूर्णांक LP */

#घोषणा MEI_DEV_ID_JSP_N      0x4DE0  /* Jasper Lake Poपूर्णांक N */

#घोषणा MEI_DEV_ID_TGP_LP     0xA0E0  /* Tiger Lake Poपूर्णांक LP */
#घोषणा MEI_DEV_ID_TGP_H      0x43E0  /* Tiger Lake Poपूर्णांक H */

#घोषणा MEI_DEV_ID_MCC        0x4B70  /* Mule Creek Canyon (EHL) */
#घोषणा MEI_DEV_ID_MCC_4      0x4B75  /* Mule Creek Canyon 4 (EHL) */

#घोषणा MEI_DEV_ID_EBG        0x1BE0  /* Emmitsburg WS */

#घोषणा MEI_DEV_ID_ADP_S      0x7AE8  /* Alder Lake Poपूर्णांक S */
#घोषणा MEI_DEV_ID_ADP_LP     0x7A60  /* Alder Lake Poपूर्णांक LP */
#घोषणा MEI_DEV_ID_ADP_P      0x51E0  /* Alder Lake Poपूर्णांक P */

/*
 * MEI HW Section
 */

/* Host Firmware Status Registers in PCI Config Space */
#घोषणा PCI_CFG_HFS_1         0x40
#  define PCI_CFG_HFS_1_D0I3_MSK     0x80000000
#  define PCI_CFG_HFS_1_OPMODE_MSK 0xf0000 /* OP MODE Mask: SPS <= 4.0 */
#  define PCI_CFG_HFS_1_OPMODE_SPS 0xf0000 /* SPS SKU : SPS <= 4.0 */
#घोषणा PCI_CFG_HFS_2         0x48
#घोषणा PCI_CFG_HFS_3         0x60
#  define PCI_CFG_HFS_3_FW_SKU_MSK   0x00000070
#  define PCI_CFG_HFS_3_FW_SKU_SPS   0x00000060
#घोषणा PCI_CFG_HFS_4         0x64
#घोषणा PCI_CFG_HFS_5         0x68
#घोषणा PCI_CFG_HFS_6         0x6C

/* MEI रेजिस्टरs */
/* H_CB_WW - Host Circular Buffer (CB) Write Winकरोw रेजिस्टर */
#घोषणा H_CB_WW    0
/* H_CSR - Host Control Status रेजिस्टर */
#घोषणा H_CSR      4
/* ME_CB_RW - ME Circular Buffer Read Winकरोw रेजिस्टर (पढ़ो only) */
#घोषणा ME_CB_RW   8
/* ME_CSR_HA - ME Control Status Host Access रेजिस्टर (पढ़ो only) */
#घोषणा ME_CSR_HA  0xC
/* H_HGC_CSR - PGI रेजिस्टर */
#घोषणा H_HPG_CSR  0x10
/* H_D0I3C - D0I3 Control  */
#घोषणा H_D0I3C    0x800

/* रेजिस्टर bits of H_CSR (Host Control Status रेजिस्टर) */
/* Host Circular Buffer Depth - maximum number of 32-bit entries in CB */
#घोषणा H_CBD             0xFF000000
/* Host Circular Buffer Write Poपूर्णांकer */
#घोषणा H_CBWP            0x00FF0000
/* Host Circular Buffer Read Poपूर्णांकer */
#घोषणा H_CBRP            0x0000FF00
/* Host Reset */
#घोषणा H_RST             0x00000010
/* Host Ready */
#घोषणा H_RDY             0x00000008
/* Host Interrupt Generate */
#घोषणा H_IG              0x00000004
/* Host Interrupt Status */
#घोषणा H_IS              0x00000002
/* Host Interrupt Enable */
#घोषणा H_IE              0x00000001
/* Host D0I3 Interrupt Enable */
#घोषणा H_D0I3C_IE        0x00000020
/* Host D0I3 Interrupt Status */
#घोषणा H_D0I3C_IS        0x00000040

/* H_CSR masks */
#घोषणा H_CSR_IE_MASK     (H_IE | H_D0I3C_IE)
#घोषणा H_CSR_IS_MASK     (H_IS | H_D0I3C_IS)

/* रेजिस्टर bits of ME_CSR_HA (ME Control Status Host Access रेजिस्टर) */
/* ME CB (Circular Buffer) Depth HRA (Host Read Access) - host पढ़ो only
access to ME_CBD */
#घोषणा ME_CBD_HRA        0xFF000000
/* ME CB Write Poपूर्णांकer HRA - host पढ़ो only access to ME_CBWP */
#घोषणा ME_CBWP_HRA       0x00FF0000
/* ME CB Read Poपूर्णांकer HRA - host पढ़ो only access to ME_CBRP */
#घोषणा ME_CBRP_HRA       0x0000FF00
/* ME Power Gate Isolation Capability HRA  - host पढ़ोy only access */
#घोषणा ME_PGIC_HRA       0x00000040
/* ME Reset HRA - host पढ़ो only access to ME_RST */
#घोषणा ME_RST_HRA        0x00000010
/* ME Ready HRA - host पढ़ो only access to ME_RDY */
#घोषणा ME_RDY_HRA        0x00000008
/* ME Interrupt Generate HRA - host पढ़ो only access to ME_IG */
#घोषणा ME_IG_HRA         0x00000004
/* ME Interrupt Status HRA - host पढ़ो only access to ME_IS */
#घोषणा ME_IS_HRA         0x00000002
/* ME Interrupt Enable HRA - host पढ़ो only access to ME_IE */
#घोषणा ME_IE_HRA         0x00000001
/* TRC control shaकरोw रेजिस्टर */
#घोषणा ME_TRC            0x00000030

/* H_HPG_CSR रेजिस्टर bits */
#घोषणा H_HPG_CSR_PGIHEXR 0x00000001
#घोषणा H_HPG_CSR_PGI     0x00000002

/* H_D0I3C रेजिस्टर bits */
#घोषणा H_D0I3C_CIP      0x00000001
#घोषणा H_D0I3C_IR       0x00000002
#घोषणा H_D0I3C_I3       0x00000004
#घोषणा H_D0I3C_RR       0x00000008

#पूर्ण_अगर /* _MEI_HW_MEI_REGS_H_ */
