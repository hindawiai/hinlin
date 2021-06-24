<शैली गुरु>
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 *   redistributing this file, you may करो so under either license.
 *
 *   GPL LICENSE SUMMARY
 *
 *   Copyright(c) 2012-2017 Intel Corporation. All rights reserved.
 *
 *   This program is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of version 2 of the GNU General Public License as
 *   published by the Free Software Foundation.
 *
 *   BSD LICENSE
 *
 *   Copyright(c) 2012-2017 Intel Corporation. All rights reserved.
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
 */

#अगर_अघोषित _NTB_INTEL_GEN3_H_
#घोषणा _NTB_INTEL_GEN3_H_

#समावेश "ntb_hw_intel.h"

/* Intel Skylake Xeon hardware */
#घोषणा GEN3_IMBAR1SZ_OFFSET		0x00d0
#घोषणा GEN3_IMBAR2SZ_OFFSET		0x00d1
#घोषणा GEN3_EMBAR1SZ_OFFSET		0x00d2
#घोषणा GEN3_EMBAR2SZ_OFFSET		0x00d3
#घोषणा GEN3_DEVCTRL_OFFSET		0x0098
#घोषणा GEN3_DEVSTS_OFFSET		0x009a
#घोषणा GEN3_UNCERRSTS_OFFSET		0x014c
#घोषणा GEN3_CORERRSTS_OFFSET		0x0158
#घोषणा GEN3_LINK_STATUS_OFFSET		0x01a2

#घोषणा GEN3_NTBCNTL_OFFSET		0x0000
#घोषणा GEN3_IMBAR1XBASE_OFFSET		0x0010		/* SBAR2XLAT */
#घोषणा GEN3_IMBAR1XLMT_OFFSET		0x0018		/* SBAR2LMT */
#घोषणा GEN3_IMBAR2XBASE_OFFSET		0x0020		/* SBAR4XLAT */
#घोषणा GEN3_IMBAR2XLMT_OFFSET		0x0028		/* SBAR4LMT */
#घोषणा GEN3_IM_INT_STATUS_OFFSET	0x0040
#घोषणा GEN3_IM_INT_DISABLE_OFFSET	0x0048
#घोषणा GEN3_IM_SPAD_OFFSET		0x0080		/* SPAD */
#घोषणा GEN3_USMEMMISS_OFFSET		0x0070
#घोषणा GEN3_INTVEC_OFFSET		0x00d0
#घोषणा GEN3_IM_DOORBELL_OFFSET		0x0100		/* SDOORBELL0 */
#घोषणा GEN3_B2B_SPAD_OFFSET		0x0180		/* B2B SPAD */
#घोषणा GEN3_EMBAR0XBASE_OFFSET		0x4008		/* B2B_XLAT */
#घोषणा GEN3_EMBAR1XBASE_OFFSET		0x4010		/* PBAR2XLAT */
#घोषणा GEN3_EMBAR1XLMT_OFFSET		0x4018		/* PBAR2LMT */
#घोषणा GEN3_EMBAR2XBASE_OFFSET		0x4020		/* PBAR4XLAT */
#घोषणा GEN3_EMBAR2XLMT_OFFSET		0x4028		/* PBAR4LMT */
#घोषणा GEN3_EM_INT_STATUS_OFFSET	0x4040
#घोषणा GEN3_EM_INT_DISABLE_OFFSET	0x4048
#घोषणा GEN3_EM_SPAD_OFFSET		0x4080		/* remote SPAD */
#घोषणा GEN3_EM_DOORBELL_OFFSET		0x4100		/* PDOORBELL0 */
#घोषणा GEN3_SPCICMD_OFFSET		0x4504		/* SPCICMD */
#घोषणा GEN3_EMBAR0_OFFSET		0x4510		/* SBAR0BASE */
#घोषणा GEN3_EMBAR1_OFFSET		0x4518		/* SBAR23BASE */
#घोषणा GEN3_EMBAR2_OFFSET		0x4520		/* SBAR45BASE */

#घोषणा GEN3_DB_COUNT			32
#घोषणा GEN3_DB_LINK			32
#घोषणा GEN3_DB_LINK_BIT		BIT_ULL(GEN3_DB_LINK)
#घोषणा GEN3_DB_MSIX_VECTOR_COUNT	33
#घोषणा GEN3_DB_MSIX_VECTOR_SHIFT	1
#घोषणा GEN3_DB_TOTAL_SHIFT		33
#घोषणा GEN3_SPAD_COUNT			16

अटल अंतरभूत u64 gen3_db_ioपढ़ो(स्थिर व्योम __iomem *mmio)
अणु
	वापस ioपढ़ो64(mmio);
पूर्ण

अटल अंतरभूत व्योम gen3_db_ioग_लिखो(u64 bits, व्योम __iomem *mmio)
अणु
	ioग_लिखो64(bits, mmio);
पूर्ण

sमाप_प्रकार ndev_ntb3_debugfs_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
				      माप_प्रकार count, loff_t *offp);
पूर्णांक gen3_init_dev(काष्ठा पूर्णांकel_ntb_dev *ndev);
पूर्णांक पूर्णांकel_ntb3_link_enable(काष्ठा ntb_dev *ntb, क्रमागत ntb_speed max_speed,
		क्रमागत ntb_width max_width);
u64 पूर्णांकel_ntb3_db_पढ़ो(काष्ठा ntb_dev *ntb);
पूर्णांक पूर्णांकel_ntb3_db_clear(काष्ठा ntb_dev *ntb, u64 db_bits);
पूर्णांक पूर्णांकel_ntb3_peer_db_set(काष्ठा ntb_dev *ntb, u64 db_bits);
पूर्णांक पूर्णांकel_ntb3_peer_db_addr(काष्ठा ntb_dev *ntb, phys_addr_t *db_addr,
				resource_माप_प्रकार *db_size,
				u64 *db_data, पूर्णांक db_bit);

बाह्य स्थिर काष्ठा ntb_dev_ops पूर्णांकel_ntb3_ops;

#पूर्ण_अगर
