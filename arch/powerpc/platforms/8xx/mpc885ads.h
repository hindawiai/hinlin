<शैली गुरु>
/*
 * A collection of काष्ठाures, addresses, and values associated with
 * the Freescale MPC885ADS board.
 * Copied from the FADS stuff.
 *
 * Author: MontaVista Software, Inc.
 *         source@mvista.com
 *
 * 2005 (c) MontaVista Software, Inc.  This file is licensed under the
 * terms of the GNU General Public License version 2.  This program is licensed
 * "as is" without any warranty of any kind, whether express or implied.
 */

#अगर_घोषित __KERNEL__
#अगर_अघोषित __ASM_MPC885ADS_H__
#घोषणा __ASM_MPC885ADS_H__

#समावेश <sysdev/fsl_soc.h>

/* Bits of पूर्णांकerest in the BCSRs.
 */
#घोषणा BCSR1_ETHEN		((uपूर्णांक)0x20000000)
#घोषणा BCSR1_IRDAEN		((uपूर्णांक)0x10000000)
#घोषणा BCSR1_RS232EN_1		((uपूर्णांक)0x01000000)
#घोषणा BCSR1_PCCEN		((uपूर्णांक)0x00800000)
#घोषणा BCSR1_PCCVCC0		((uपूर्णांक)0x00400000)
#घोषणा BCSR1_PCCVPP0		((uपूर्णांक)0x00200000)
#घोषणा BCSR1_PCCVPP1		((uपूर्णांक)0x00100000)
#घोषणा BCSR1_PCCVPP_MASK	(BCSR1_PCCVPP0 | BCSR1_PCCVPP1)
#घोषणा BCSR1_RS232EN_2		((uपूर्णांक)0x00040000)
#घोषणा BCSR1_PCCVCC1		((uपूर्णांक)0x00010000)
#घोषणा BCSR1_PCCVCC_MASK	(BCSR1_PCCVCC0 | BCSR1_PCCVCC1)

#घोषणा BCSR4_ETH10_RST		((uपूर्णांक)0x80000000)	/* 10Base-T PHY reset*/
#घोषणा BCSR4_USB_LO_SPD	((uपूर्णांक)0x04000000)
#घोषणा BCSR4_USB_VCC		((uपूर्णांक)0x02000000)
#घोषणा BCSR4_USB_FULL_SPD	((uपूर्णांक)0x00040000)
#घोषणा BCSR4_USB_EN		((uपूर्णांक)0x00020000)

#घोषणा BCSR5_MII2_EN		0x40
#घोषणा BCSR5_MII2_RST		0x20
#घोषणा BCSR5_T1_RST		0x10
#घोषणा BCSR5_ATM155_RST	0x08
#घोषणा BCSR5_ATM25_RST		0x04
#घोषणा BCSR5_MII1_EN		0x02
#घोषणा BCSR5_MII1_RST		0x01

#पूर्ण_अगर /* __ASM_MPC885ADS_H__ */
#पूर्ण_अगर /* __KERNEL__ */
