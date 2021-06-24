<शैली गुरु>
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 *   redistributing this file, you may करो so under either license.
 *
 *   GPL LICENSE SUMMARY
 *
 *   Copyright (C) 2016 Advanced Micro Devices, Inc. All Rights Reserved.
 *
 *   This program is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of version 2 of the GNU General Public License as
 *   published by the Free Software Foundation.
 *
 *   BSD LICENSE
 *
 *   Copyright (C) 2016 Advanced Micro Devices, Inc. All Rights Reserved.
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
 *     * Neither the name of AMD Corporation nor the names of its
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
 * AMD PCIe NTB Linux driver
 *
 * Contact Inक्रमmation:
 * Xiangliang Yu <Xiangliang.Yu@amd.com>
 */

#अगर_अघोषित NTB_HW_AMD_H
#घोषणा NTB_HW_AMD_H

#समावेश <linux/ntb.h>
#समावेश <linux/pci.h>

#घोषणा AMD_LINK_HB_TIMEOUT	msecs_to_jअगरfies(1000)
#घोषणा NTB_LNK_STA_SPEED_MASK	0x000F0000
#घोषणा NTB_LNK_STA_WIDTH_MASK	0x03F00000
#घोषणा NTB_LNK_STA_SPEED(x)	(((x) & NTB_LNK_STA_SPEED_MASK) >> 16)
#घोषणा NTB_LNK_STA_WIDTH(x)	(((x) & NTB_LNK_STA_WIDTH_MASK) >> 20)

#अगर_अघोषित पढ़ो64
#अगर_घोषित पढ़ोq
#घोषणा पढ़ो64 पढ़ोq
#अन्यथा
#घोषणा पढ़ो64 _पढ़ो64
अटल अंतरभूत u64 _पढ़ो64(व्योम __iomem *mmio)
अणु
	u64 low, high;

	low = पढ़ोl(mmio);
	high = पढ़ोl(mmio + माप(u32));
	वापस low | (high << 32);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_अघोषित ग_लिखो64
#अगर_घोषित ग_लिखोq
#घोषणा ग_लिखो64 ग_लिखोq
#अन्यथा
#घोषणा ग_लिखो64 _ग_लिखो64
अटल अंतरभूत व्योम _ग_लिखो64(u64 val, व्योम __iomem *mmio)
अणु
	ग_लिखोl(val, mmio);
	ग_लिखोl(val >> 32, mmio + माप(u32));
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

क्रमागत अणु
	/* AMD NTB Capability */
	AMD_DB_CNT		= 16,
	AMD_MSIX_VECTOR_CNT	= 24,
	AMD_SPADS_CNT		= 16,

	/*  AMD NTB रेजिस्टर offset */
	AMD_CNTL_OFFSET		= 0x200,

	/* NTB control रेजिस्टर bits */
	PMM_REG_CTL		= BIT(21),
	SMM_REG_CTL		= BIT(20),
	SMM_REG_ACC_PATH	= BIT(18),
	PMM_REG_ACC_PATH	= BIT(17),
	NTB_CLK_EN		= BIT(16),

	AMD_STA_OFFSET		= 0x204,
	AMD_PGSLV_OFFSET	= 0x208,
	AMD_SPAD_MUX_OFFSET	= 0x20C,
	AMD_SPAD_OFFSET		= 0x210,
	AMD_RSMU_HCID		= 0x250,
	AMD_RSMU_SIID		= 0x254,
	AMD_PSION_OFFSET	= 0x300,
	AMD_SSION_OFFSET	= 0x330,
	AMD_MMINDEX_OFFSET	= 0x400,
	AMD_MMDATA_OFFSET	= 0x404,
	AMD_SIDEINFO_OFFSET	= 0x408,

	AMD_SIDE_MASK		= BIT(0),
	AMD_SIDE_READY		= BIT(1),

	/* limit रेजिस्टर */
	AMD_ROMBARLMT_OFFSET	= 0x410,
	AMD_BAR1LMT_OFFSET	= 0x414,
	AMD_BAR23LMT_OFFSET	= 0x418,
	AMD_BAR45LMT_OFFSET	= 0x420,
	/* xlat address */
	AMD_POMBARXLAT_OFFSET	= 0x428,
	AMD_BAR1XLAT_OFFSET	= 0x430,
	AMD_BAR23XLAT_OFFSET	= 0x438,
	AMD_BAR45XLAT_OFFSET	= 0x440,
	/* करोorbell and पूर्णांकerrupt */
	AMD_DBFM_OFFSET		= 0x450,
	AMD_DBREQ_OFFSET	= 0x454,
	AMD_MIRRDBSTAT_OFFSET	= 0x458,
	AMD_DBMASK_OFFSET	= 0x45C,
	AMD_DBSTAT_OFFSET	= 0x460,
	AMD_INTMASK_OFFSET	= 0x470,
	AMD_INTSTAT_OFFSET	= 0x474,

	/* event type */
	AMD_PEER_FLUSH_EVENT	= BIT(0),
	AMD_PEER_RESET_EVENT	= BIT(1),
	AMD_PEER_D3_EVENT	= BIT(2),
	AMD_PEER_PMETO_EVENT	= BIT(3),
	AMD_PEER_D0_EVENT	= BIT(4),
	AMD_LINK_UP_EVENT	= BIT(5),
	AMD_LINK_DOWN_EVENT	= BIT(6),
	AMD_EVENT_INTMASK	= (AMD_PEER_FLUSH_EVENT |
				AMD_PEER_RESET_EVENT | AMD_PEER_D3_EVENT |
				AMD_PEER_PMETO_EVENT | AMD_PEER_D0_EVENT |
				AMD_LINK_UP_EVENT | AMD_LINK_DOWN_EVENT),

	AMD_PMESTAT_OFFSET	= 0x480,
	AMD_PMSGTRIG_OFFSET	= 0x490,
	AMD_LTRLATENCY_OFFSET	= 0x494,
	AMD_FLUSHTRIG_OFFSET	= 0x498,

	/* SMU रेजिस्टर*/
	AMD_SMUACK_OFFSET	= 0x4A0,
	AMD_SINRST_OFFSET	= 0x4A4,
	AMD_RSPNUM_OFFSET	= 0x4A8,
	AMD_SMU_SPADMUTEX	= 0x4B0,
	AMD_SMU_SPADOFFSET	= 0x4B4,

	AMD_PEER_OFFSET		= 0x400,
पूर्ण;

काष्ठा ntb_dev_data अणु
	स्थिर अचिन्हित अक्षर mw_count;
	स्थिर अचिन्हित पूर्णांक mw_idx;
पूर्ण;

काष्ठा amd_ntb_dev;

काष्ठा amd_ntb_vec अणु
	काष्ठा amd_ntb_dev	*ndev;
	पूर्णांक			num;
पूर्ण;

काष्ठा amd_ntb_dev अणु
	काष्ठा ntb_dev ntb;

	u32 ntb_side;
	u32 lnk_sta;
	u32 cntl_sta;
	u32 peer_sta;

	काष्ठा ntb_dev_data *dev_data;
	अचिन्हित अक्षर mw_count;
	अचिन्हित अक्षर spad_count;
	अचिन्हित अक्षर db_count;
	अचिन्हित अक्षर msix_vec_count;

	u64 db_valid_mask;
	u64 db_mask;
	u64 db_last_bit;
	u32 पूर्णांक_mask;

	काष्ठा msix_entry *msix;
	काष्ठा amd_ntb_vec *vec;

	/* synchronize rmw access of db_mask and hw reg */
	spinlock_t db_mask_lock;

	व्योम __iomem *self_mmio;
	व्योम __iomem *peer_mmio;
	अचिन्हित पूर्णांक self_spad;
	अचिन्हित पूर्णांक peer_spad;

	काष्ठा delayed_work hb_समयr;

	काष्ठा dentry *debugfs_dir;
	काष्ठा dentry *debugfs_info;
पूर्ण;

#घोषणा ntb_ndev(__ntb) container_of(__ntb, काष्ठा amd_ntb_dev, ntb)
#घोषणा hb_ndev(__work) container_of(__work, काष्ठा amd_ntb_dev, hb_समयr.work)

अटल व्योम amd_set_side_info_reg(काष्ठा amd_ntb_dev *ndev, bool peer);
अटल व्योम amd_clear_side_info_reg(काष्ठा amd_ntb_dev *ndev, bool peer);
अटल पूर्णांक amd_poll_link(काष्ठा amd_ntb_dev *ndev);

#पूर्ण_अगर
