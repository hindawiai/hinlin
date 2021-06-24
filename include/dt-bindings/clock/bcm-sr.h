<शैली गुरु>
/*
 *  BSD LICENSE
 *
 *  Copyright(c) 2017 Broadcom. All rights reserved.
 *
 *  Redistribution and use in source and binary क्रमms, with or without
 *  modअगरication, are permitted provided that the following conditions
 *  are met:
 *
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary क्रमm must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in
 *      the करोcumentation and/or other materials provided with the
 *      distribution.
 *    * Neither the name of Broadcom Corporation nor the names of its
 *      contributors may be used to enकरोrse or promote products derived
 *      from this software without specअगरic prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित _CLOCK_BCM_SR_H
#घोषणा _CLOCK_BCM_SR_H

/* GENPLL 0 घड़ी channel ID SCR HSLS FS PCIE */
#घोषणा BCM_SR_GENPLL0			0
#घोषणा BCM_SR_GENPLL0_125M_CLK		1
#घोषणा BCM_SR_GENPLL0_SCR_CLK		2
#घोषणा BCM_SR_GENPLL0_250M_CLK		3
#घोषणा BCM_SR_GENPLL0_PCIE_AXI_CLK	4
#घोषणा BCM_SR_GENPLL0_PAXC_AXI_X2_CLK	5
#घोषणा BCM_SR_GENPLL0_PAXC_AXI_CLK	6

/* GENPLL 1 घड़ी channel ID MHB PCIE NITRO */
#घोषणा BCM_SR_GENPLL1			0
#घोषणा BCM_SR_GENPLL1_PCIE_TL_CLK	1
#घोषणा BCM_SR_GENPLL1_MHB_APB_CLK	2

/* GENPLL 2 घड़ी channel ID NITRO MHB*/
#घोषणा BCM_SR_GENPLL2			0
#घोषणा BCM_SR_GENPLL2_NIC_CLK		1
#घोषणा BCM_SR_GENPLL2_TS_500_CLK	2
#घोषणा BCM_SR_GENPLL2_125_NITRO_CLK	3
#घोषणा BCM_SR_GENPLL2_CHIMP_CLK	4
#घोषणा BCM_SR_GENPLL2_NIC_FLASH_CLK	5
#घोषणा BCM_SR_GENPLL2_FS4_CLK		6

/* GENPLL 3 HSLS घड़ी channel ID */
#घोषणा BCM_SR_GENPLL3			0
#घोषणा BCM_SR_GENPLL3_HSLS_CLK		1
#घोषणा BCM_SR_GENPLL3_SDIO_CLK		2

/* GENPLL 4 SCR घड़ी channel ID */
#घोषणा BCM_SR_GENPLL4			0
#घोषणा BCM_SR_GENPLL4_CCN_CLK		1
#घोषणा BCM_SR_GENPLL4_TPIU_PLL_CLK	2
#घोषणा BCM_SR_GENPLL4_NOC_CLK		3
#घोषणा BCM_SR_GENPLL4_CHCLK_FS4_CLK	4
#घोषणा BCM_SR_GENPLL4_BRIDGE_FSCPU_CLK	5

/* GENPLL 5 FS4 घड़ी channel ID */
#घोषणा BCM_SR_GENPLL5			0
#घोषणा BCM_SR_GENPLL5_FS4_HF_CLK	1
#घोषणा BCM_SR_GENPLL5_CRYPTO_AE_CLK	2
#घोषणा BCM_SR_GENPLL5_RAID_AE_CLK	3

/* GENPLL 6 NITRO घड़ी channel ID */
#घोषणा BCM_SR_GENPLL6			0
#घोषणा BCM_SR_GENPLL6_48_USB_CLK	1

/* LCPLL0  घड़ी channel ID */
#घोषणा BCM_SR_LCPLL0			0
#घोषणा BCM_SR_LCPLL0_SATA_REFP_CLK	1
#घोषणा BCM_SR_LCPLL0_SATA_REFN_CLK	2
#घोषणा BCM_SR_LCPLL0_SATA_350_CLK	3
#घोषणा BCM_SR_LCPLL0_SATA_500_CLK	4

/* LCPLL1  घड़ी channel ID */
#घोषणा BCM_SR_LCPLL1			0
#घोषणा BCM_SR_LCPLL1_WAN_CLK		1
#घोषणा BCM_SR_LCPLL1_USB_REF_CLK	2
#घोषणा BCM_SR_LCPLL1_CRMU_TS_CLK	3

/* LCPLL PCIE  घड़ी channel ID */
#घोषणा BCM_SR_LCPLL_PCIE		0
#घोषणा BCM_SR_LCPLL_PCIE_PHY_REF_CLK	1

/* GENPLL EMEM0 घड़ी channel ID */
#घोषणा BCM_SR_EMEMPLL0			0
#घोषणा BCM_SR_EMEMPLL0_EMEM_CLK	1

/* GENPLL EMEM0 घड़ी channel ID */
#घोषणा BCM_SR_EMEMPLL1			0
#घोषणा BCM_SR_EMEMPLL1_EMEM_CLK	1

/* GENPLL EMEM0 घड़ी channel ID */
#घोषणा BCM_SR_EMEMPLL2			0
#घोषणा BCM_SR_EMEMPLL2_EMEM_CLK	1

#पूर्ण_अगर /* _CLOCK_BCM_SR_H */
