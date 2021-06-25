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

#अगर_अघोषित _NTB_INTEL_GEN1_H_
#घोषणा _NTB_INTEL_GEN1_H_

#समावेश "ntb_hw_intel.h"

/* Intel Gen1 Xeon hardware */
#घोषणा XEON_PBAR23LMT_OFFSET		0x0000
#घोषणा XEON_PBAR45LMT_OFFSET		0x0008
#घोषणा XEON_PBAR4LMT_OFFSET		0x0008
#घोषणा XEON_PBAR5LMT_OFFSET		0x000c
#घोषणा XEON_PBAR23XLAT_OFFSET		0x0010
#घोषणा XEON_PBAR45XLAT_OFFSET		0x0018
#घोषणा XEON_PBAR4XLAT_OFFSET		0x0018
#घोषणा XEON_PBAR5XLAT_OFFSET		0x001c
#घोषणा XEON_SBAR23LMT_OFFSET		0x0020
#घोषणा XEON_SBAR45LMT_OFFSET		0x0028
#घोषणा XEON_SBAR4LMT_OFFSET		0x0028
#घोषणा XEON_SBAR5LMT_OFFSET		0x002c
#घोषणा XEON_SBAR23XLAT_OFFSET		0x0030
#घोषणा XEON_SBAR45XLAT_OFFSET		0x0038
#घोषणा XEON_SBAR4XLAT_OFFSET		0x0038
#घोषणा XEON_SBAR5XLAT_OFFSET		0x003c
#घोषणा XEON_SBAR0BASE_OFFSET		0x0040
#घोषणा XEON_SBAR23BASE_OFFSET		0x0048
#घोषणा XEON_SBAR45BASE_OFFSET		0x0050
#घोषणा XEON_SBAR4BASE_OFFSET		0x0050
#घोषणा XEON_SBAR5BASE_OFFSET		0x0054
#घोषणा XEON_SBDF_OFFSET		0x005c
#घोषणा XEON_NTBCNTL_OFFSET		0x0058
#घोषणा XEON_PDOORBELL_OFFSET		0x0060
#घोषणा XEON_PDBMSK_OFFSET		0x0062
#घोषणा XEON_SDOORBELL_OFFSET		0x0064
#घोषणा XEON_SDBMSK_OFFSET		0x0066
#घोषणा XEON_USMEMMISS_OFFSET		0x0070
#घोषणा XEON_SPAD_OFFSET		0x0080
#घोषणा XEON_PBAR23SZ_OFFSET		0x00d0
#घोषणा XEON_PBAR45SZ_OFFSET		0x00d1
#घोषणा XEON_PBAR4SZ_OFFSET		0x00d1
#घोषणा XEON_SBAR23SZ_OFFSET		0x00d2
#घोषणा XEON_SBAR45SZ_OFFSET		0x00d3
#घोषणा XEON_SBAR4SZ_OFFSET		0x00d3
#घोषणा XEON_PPD_OFFSET			0x00d4
#घोषणा XEON_PBAR5SZ_OFFSET		0x00d5
#घोषणा XEON_SBAR5SZ_OFFSET		0x00d6
#घोषणा XEON_WCCNTRL_OFFSET		0x00e0
#घोषणा XEON_UNCERRSTS_OFFSET		0x014c
#घोषणा XEON_CORERRSTS_OFFSET		0x0158
#घोषणा XEON_LINK_STATUS_OFFSET		0x01a2
#घोषणा XEON_SPCICMD_OFFSET		0x0504
#घोषणा XEON_DEVCTRL_OFFSET		0x0598
#घोषणा XEON_DEVSTS_OFFSET		0x059a
#घोषणा XEON_SLINK_STATUS_OFFSET	0x05a2
#घोषणा XEON_B2B_SPAD_OFFSET		0x0100
#घोषणा XEON_B2B_DOORBELL_OFFSET	0x0140
#घोषणा XEON_B2B_XLAT_OFFSETL		0x0144
#घोषणा XEON_B2B_XLAT_OFFSETU		0x0148
#घोषणा XEON_PPD_CONN_MASK		0x03
#घोषणा XEON_PPD_CONN_TRANSPARENT	0x00
#घोषणा XEON_PPD_CONN_B2B		0x01
#घोषणा XEON_PPD_CONN_RP		0x02
#घोषणा XEON_PPD_DEV_MASK		0x10
#घोषणा XEON_PPD_DEV_USD		0x00
#घोषणा XEON_PPD_DEV_DSD		0x10
#घोषणा XEON_PPD_SPLIT_BAR_MASK		0x40

#घोषणा XEON_PPD_TOPO_MASK	(XEON_PPD_CONN_MASK | XEON_PPD_DEV_MASK)
#घोषणा XEON_PPD_TOPO_PRI_USD	(XEON_PPD_CONN_RP | XEON_PPD_DEV_USD)
#घोषणा XEON_PPD_TOPO_PRI_DSD	(XEON_PPD_CONN_RP | XEON_PPD_DEV_DSD)
#घोषणा XEON_PPD_TOPO_SEC_USD	(XEON_PPD_CONN_TRANSPARENT | XEON_PPD_DEV_USD)
#घोषणा XEON_PPD_TOPO_SEC_DSD	(XEON_PPD_CONN_TRANSPARENT | XEON_PPD_DEV_DSD)
#घोषणा XEON_PPD_TOPO_B2B_USD	(XEON_PPD_CONN_B2B | XEON_PPD_DEV_USD)
#घोषणा XEON_PPD_TOPO_B2B_DSD	(XEON_PPD_CONN_B2B | XEON_PPD_DEV_DSD)

#घोषणा XEON_MW_COUNT			2
#घोषणा HSX_SPLIT_BAR_MW_COUNT		3
#घोषणा XEON_DB_COUNT			15
#घोषणा XEON_DB_LINK			15
#घोषणा XEON_DB_LINK_BIT			BIT_ULL(XEON_DB_LINK)
#घोषणा XEON_DB_MSIX_VECTOR_COUNT	4
#घोषणा XEON_DB_MSIX_VECTOR_SHIFT	5
#घोषणा XEON_DB_TOTAL_SHIFT		16
#घोषणा XEON_SPAD_COUNT			16

/* Use the following addresses क्रम translation between b2b ntb devices in हाल
 * the hardware शेष values are not reliable. */
#घोषणा XEON_B2B_BAR0_ADDR	0x1000000000000000ull
#घोषणा XEON_B2B_BAR2_ADDR64	0x2000000000000000ull
#घोषणा XEON_B2B_BAR4_ADDR64	0x4000000000000000ull
#घोषणा XEON_B2B_BAR4_ADDR32	0x20000000u
#घोषणा XEON_B2B_BAR5_ADDR32	0x40000000u

/* The peer ntb secondary config space is 32KB fixed size */
#घोषणा XEON_B2B_MIN_SIZE		0x8000

/* flags to indicate hardware errata */
#घोषणा NTB_HWERR_SDOORBELL_LOCKUP	BIT_ULL(0)
#घोषणा NTB_HWERR_SB01BASE_LOCKUP	BIT_ULL(1)
#घोषणा NTB_HWERR_B2BDOORBELL_BIT14	BIT_ULL(2)
#घोषणा NTB_HWERR_MSIX_VECTOR32_BAD	BIT_ULL(3)
#घोषणा NTB_HWERR_BAR_ALIGN		BIT_ULL(4)
#घोषणा NTB_HWERR_LTR_BAD		BIT_ULL(5)

बाह्य काष्ठा पूर्णांकel_b2b_addr xeon_b2b_usd_addr;
बाह्य काष्ठा पूर्णांकel_b2b_addr xeon_b2b_dsd_addr;

पूर्णांक ndev_init_isr(काष्ठा पूर्णांकel_ntb_dev *ndev, पूर्णांक msix_min, पूर्णांक msix_max,
		पूर्णांक msix_shअगरt, पूर्णांक total_shअगरt);
क्रमागत ntb_topo xeon_ppd_topo(काष्ठा पूर्णांकel_ntb_dev *ndev, u8 ppd);
व्योम ndev_db_addr(काष्ठा पूर्णांकel_ntb_dev *ndev,
				phys_addr_t *db_addr, resource_माप_प्रकार *db_size,
				phys_addr_t reg_addr, अचिन्हित दीर्घ reg);
u64 ndev_db_पढ़ो(काष्ठा पूर्णांकel_ntb_dev *ndev, व्योम __iomem *mmio);
पूर्णांक ndev_db_ग_लिखो(काष्ठा पूर्णांकel_ntb_dev *ndev, u64 db_bits,
				व्योम __iomem *mmio);
पूर्णांक ndev_mw_to_bar(काष्ठा पूर्णांकel_ntb_dev *ndev, पूर्णांक idx);
पूर्णांक पूर्णांकel_ntb_mw_count(काष्ठा ntb_dev *ntb, पूर्णांक pidx);
पूर्णांक पूर्णांकel_ntb_mw_get_align(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक idx,
		resource_माप_प्रकार *addr_align, resource_माप_प्रकार *size_align,
		resource_माप_प्रकार *size_max);
पूर्णांक पूर्णांकel_ntb_peer_mw_count(काष्ठा ntb_dev *ntb);
पूर्णांक पूर्णांकel_ntb_peer_mw_get_addr(काष्ठा ntb_dev *ntb, पूर्णांक idx,
		phys_addr_t *base, resource_माप_प्रकार *size);
u64 पूर्णांकel_ntb_link_is_up(काष्ठा ntb_dev *ntb, क्रमागत ntb_speed *speed,
		क्रमागत ntb_width *width);
पूर्णांक पूर्णांकel_ntb_link_disable(काष्ठा ntb_dev *ntb);
u64 पूर्णांकel_ntb_db_valid_mask(काष्ठा ntb_dev *ntb);
पूर्णांक पूर्णांकel_ntb_db_vector_count(काष्ठा ntb_dev *ntb);
u64 पूर्णांकel_ntb_db_vector_mask(काष्ठा ntb_dev *ntb, पूर्णांक db_vector);
पूर्णांक पूर्णांकel_ntb_db_set_mask(काष्ठा ntb_dev *ntb, u64 db_bits);
पूर्णांक पूर्णांकel_ntb_db_clear_mask(काष्ठा ntb_dev *ntb, u64 db_bits);
पूर्णांक पूर्णांकel_ntb_spad_is_unsafe(काष्ठा ntb_dev *ntb);
पूर्णांक पूर्णांकel_ntb_spad_count(काष्ठा ntb_dev *ntb);
u32 पूर्णांकel_ntb_spad_पढ़ो(काष्ठा ntb_dev *ntb, पूर्णांक idx);
पूर्णांक पूर्णांकel_ntb_spad_ग_लिखो(काष्ठा ntb_dev *ntb, पूर्णांक idx, u32 val);
u32 पूर्णांकel_ntb_peer_spad_पढ़ो(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक sidx);
पूर्णांक पूर्णांकel_ntb_peer_spad_ग_लिखो(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक sidx,
		u32 val);
पूर्णांक पूर्णांकel_ntb_peer_spad_addr(काष्ठा ntb_dev *ntb, पूर्णांक pidx, पूर्णांक sidx,
				    phys_addr_t *spad_addr);
पूर्णांक xeon_link_is_up(काष्ठा पूर्णांकel_ntb_dev *ndev);

#पूर्ण_अगर
