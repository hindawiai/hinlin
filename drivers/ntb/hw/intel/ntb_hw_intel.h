<शैली गुरु>
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 *   redistributing this file, you may करो so under either license.
 *
 *   GPL LICENSE SUMMARY
 *
 *   Copyright(c) 2012 Intel Corporation. All rights reserved.
 *   Copyright (C) 2015 EMC Corporation. All Rights Reserved.
 *
 *   This program is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of version 2 of the GNU General Public License as
 *   published by the Free Software Foundation.
 *
 *   BSD LICENSE
 *
 *   Copyright(c) 2012 Intel Corporation. All rights reserved.
 *   Copyright (C) 2015 EMC Corporation. All Rights Reserved.
 *
 *   Redistribution and use in source and binary क्रमms, with or without
 *   modअगरication, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copy
 *       notice, this list of conditions and the following disclaimer in
 *       the करोcumentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to enकरोrse or promote products derived
 *       from this software without specअगरic prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Intel PCIe NTB Linux driver
 *
 * Contact Inक्रमmation:
 * Jon Mason <jon.mason@पूर्णांकel.com>
 */

#अगर_अघोषित NTB_HW_INTEL_H
#घोषणा NTB_HW_INTEL_H

#समावेश <linux/ntb.h>
#समावेश <linux/pci.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>

/* PCI device IDs */
#घोषणा PCI_DEVICE_ID_INTEL_NTB_B2B_JSF	0x3725
#घोषणा PCI_DEVICE_ID_INTEL_NTB_PS_JSF	0x3726
#घोषणा PCI_DEVICE_ID_INTEL_NTB_SS_JSF	0x3727
#घोषणा PCI_DEVICE_ID_INTEL_NTB_B2B_SNB	0x3C0D
#घोषणा PCI_DEVICE_ID_INTEL_NTB_PS_SNB	0x3C0E
#घोषणा PCI_DEVICE_ID_INTEL_NTB_SS_SNB	0x3C0F
#घोषणा PCI_DEVICE_ID_INTEL_NTB_B2B_IVT	0x0E0D
#घोषणा PCI_DEVICE_ID_INTEL_NTB_PS_IVT	0x0E0E
#घोषणा PCI_DEVICE_ID_INTEL_NTB_SS_IVT	0x0E0F
#घोषणा PCI_DEVICE_ID_INTEL_NTB_B2B_HSX	0x2F0D
#घोषणा PCI_DEVICE_ID_INTEL_NTB_PS_HSX	0x2F0E
#घोषणा PCI_DEVICE_ID_INTEL_NTB_SS_HSX	0x2F0F
#घोषणा PCI_DEVICE_ID_INTEL_NTB_B2B_BDX	0x6F0D
#घोषणा PCI_DEVICE_ID_INTEL_NTB_PS_BDX	0x6F0E
#घोषणा PCI_DEVICE_ID_INTEL_NTB_SS_BDX	0x6F0F
#घोषणा PCI_DEVICE_ID_INTEL_NTB_B2B_SKX	0x201C
#घोषणा PCI_DEVICE_ID_INTEL_NTB_B2B_ICX	0x347e

/* Ntb control and link status */
#घोषणा NTB_CTL_CFG_LOCK		BIT(0)
#घोषणा NTB_CTL_DISABLE			BIT(1)
#घोषणा NTB_CTL_S2P_BAR2_SNOOP		BIT(2)
#घोषणा NTB_CTL_P2S_BAR2_SNOOP		BIT(4)
#घोषणा NTB_CTL_S2P_BAR4_SNOOP		BIT(6)
#घोषणा NTB_CTL_P2S_BAR4_SNOOP		BIT(8)
#घोषणा NTB_CTL_S2P_BAR5_SNOOP		BIT(12)
#घोषणा NTB_CTL_P2S_BAR5_SNOOP		BIT(14)

#घोषणा NTB_LNK_STA_ACTIVE_BIT		0x2000
#घोषणा NTB_LNK_STA_SPEED_MASK		0x000f
#घोषणा NTB_LNK_STA_WIDTH_MASK		0x03f0
#घोषणा NTB_LNK_STA_ACTIVE(x)		(!!((x) & NTB_LNK_STA_ACTIVE_BIT))
#घोषणा NTB_LNK_STA_SPEED(x)		((x) & NTB_LNK_STA_SPEED_MASK)
#घोषणा NTB_LNK_STA_WIDTH(x)		(((x) & NTB_LNK_STA_WIDTH_MASK) >> 4)

/* flags to indicate unsafe api */
#घोषणा NTB_UNSAFE_DB			BIT_ULL(0)
#घोषणा NTB_UNSAFE_SPAD			BIT_ULL(1)

#घोषणा NTB_BAR_MASK_64			~(0xfull)
#घोषणा NTB_BAR_MASK_32			~(0xfu)

काष्ठा पूर्णांकel_ntb_dev;

काष्ठा पूर्णांकel_ntb_reg अणु
	पूर्णांक (*poll_link)(काष्ठा पूर्णांकel_ntb_dev *ndev);
	पूर्णांक (*link_is_up)(काष्ठा पूर्णांकel_ntb_dev *ndev);
	u64 (*db_ioपढ़ो)(स्थिर व्योम __iomem *mmio);
	व्योम (*db_ioग_लिखो)(u64 db_bits, व्योम __iomem *mmio);
	अचिन्हित दीर्घ			ntb_ctl;
	resource_माप_प्रकार			db_size;
	पूर्णांक				mw_bar[];
पूर्ण;

काष्ठा पूर्णांकel_ntb_alt_reg अणु
	अचिन्हित दीर्घ			db_bell;
	अचिन्हित दीर्घ			db_mask;
	अचिन्हित दीर्घ			db_clear;
	अचिन्हित दीर्घ			spad;
पूर्ण;

काष्ठा पूर्णांकel_ntb_xlat_reg अणु
	अचिन्हित दीर्घ			bar0_base;
	अचिन्हित दीर्घ			bar2_xlat;
	अचिन्हित दीर्घ			bar2_limit;
	अचिन्हित लघु			bar2_idx;
पूर्ण;

काष्ठा पूर्णांकel_b2b_addr अणु
	phys_addr_t			bar0_addr;
	phys_addr_t			bar2_addr64;
	phys_addr_t			bar4_addr64;
	phys_addr_t			bar4_addr32;
	phys_addr_t			bar5_addr32;
पूर्ण;

काष्ठा पूर्णांकel_ntb_vec अणु
	काष्ठा पूर्णांकel_ntb_dev		*ndev;
	पूर्णांक				num;
पूर्ण;

काष्ठा पूर्णांकel_ntb_dev अणु
	काष्ठा ntb_dev			ntb;

	/* offset of peer bar0 in b2b bar */
	अचिन्हित दीर्घ			b2b_off;
	/* mw idx used to access peer bar0 */
	अचिन्हित पूर्णांक			b2b_idx;

	/* BAR45 is split पूर्णांकo BAR4 and BAR5 */
	bool				bar4_split;

	u32				ntb_ctl;
	u32				lnk_sta;

	अचिन्हित अक्षर			mw_count;
	अचिन्हित अक्षर			spad_count;
	अचिन्हित अक्षर			db_count;
	अचिन्हित अक्षर			db_vec_count;
	अचिन्हित अक्षर			db_vec_shअगरt;

	u64				db_valid_mask;
	u64				db_link_mask;
	u64				db_mask;

	/* synchronize rmw access of db_mask and hw reg */
	spinlock_t			db_mask_lock;

	काष्ठा msix_entry		*msix;
	काष्ठा पूर्णांकel_ntb_vec		*vec;

	स्थिर काष्ठा पूर्णांकel_ntb_reg	*reg;
	स्थिर काष्ठा पूर्णांकel_ntb_alt_reg	*self_reg;
	स्थिर काष्ठा पूर्णांकel_ntb_alt_reg	*peer_reg;
	स्थिर काष्ठा पूर्णांकel_ntb_xlat_reg	*xlat_reg;
	व्योम				__iomem *self_mmio;
	व्योम				__iomem *peer_mmio;
	phys_addr_t			peer_addr;

	अचिन्हित दीर्घ			last_ts;
	काष्ठा delayed_work		hb_समयr;

	अचिन्हित दीर्घ			hwerr_flags;
	अचिन्हित दीर्घ			unsafe_flags;
	अचिन्हित दीर्घ			unsafe_flags_ignore;

	काष्ठा dentry			*debugfs_dir;
	काष्ठा dentry			*debugfs_info;

	/* gen4 entries */
	पूर्णांक				dev_up;
पूर्ण;

#घोषणा ntb_ndev(__ntb) container_of(__ntb, काष्ठा पूर्णांकel_ntb_dev, ntb)
#घोषणा hb_ndev(__work) container_of(__work, काष्ठा पूर्णांकel_ntb_dev, \
				     hb_समयr.work)

अटल अंतरभूत पूर्णांक pdev_is_gen1(काष्ठा pci_dev *pdev)
अणु
	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_INTEL_NTB_SS_JSF:
	हाल PCI_DEVICE_ID_INTEL_NTB_SS_SNB:
	हाल PCI_DEVICE_ID_INTEL_NTB_SS_IVT:
	हाल PCI_DEVICE_ID_INTEL_NTB_SS_HSX:
	हाल PCI_DEVICE_ID_INTEL_NTB_SS_BDX:
	हाल PCI_DEVICE_ID_INTEL_NTB_PS_JSF:
	हाल PCI_DEVICE_ID_INTEL_NTB_PS_SNB:
	हाल PCI_DEVICE_ID_INTEL_NTB_PS_IVT:
	हाल PCI_DEVICE_ID_INTEL_NTB_PS_HSX:
	हाल PCI_DEVICE_ID_INTEL_NTB_PS_BDX:
	हाल PCI_DEVICE_ID_INTEL_NTB_B2B_JSF:
	हाल PCI_DEVICE_ID_INTEL_NTB_B2B_SNB:
	हाल PCI_DEVICE_ID_INTEL_NTB_B2B_IVT:
	हाल PCI_DEVICE_ID_INTEL_NTB_B2B_HSX:
	हाल PCI_DEVICE_ID_INTEL_NTB_B2B_BDX:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pdev_is_gen3(काष्ठा pci_dev *pdev)
अणु
	अगर (pdev->device == PCI_DEVICE_ID_INTEL_NTB_B2B_SKX)
		वापस 1;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pdev_is_gen4(काष्ठा pci_dev *pdev)
अणु
	अगर (pdev->device == PCI_DEVICE_ID_INTEL_NTB_B2B_ICX)
		वापस 1;

	वापस 0;
पूर्ण
#पूर्ण_अगर
