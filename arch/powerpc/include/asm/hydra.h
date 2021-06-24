<शैली गुरु>
/*
 *  include/यंत्र-ppc/hydra.h -- Mac I/O `Hydra' definitions
 *
 *  Copyright (C) 1997 Geert Uytterhoeven
 *
 *  This file is based on the following करोcumentation:
 *
 *	Macपूर्णांकosh Technology in the Common Hardware Reference Platक्रमm
 *	Apple Computer, Inc.
 *
 *	तऊ Copyright 1995 Apple Computer, Inc. All rights reserved.
 *
 *  It's available online from https://www.cpu.lu/~mlan/ftp/MacTech.pdf
 *  You can obtain paper copies of this book from computer bookstores or by
 *  writing Morgan Kaufmann Publishers, Inc., 340 Pine Street, Sixth Floor, San
 *  Francisco, CA 94104. Reference ISBN 1-55860-393-X.
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive
 *  क्रम more details.
 */

#अगर_अघोषित _ASMPPC_HYDRA_H
#घोषणा _ASMPPC_HYDRA_H

#अगर_घोषित __KERNEL__

काष्ठा Hydra अणु
    /* DBDMA Controller Register Space */
    अक्षर Pad1[0x30];
    u_पूर्णांक CachePD;
    u_पूर्णांक IDs;
    u_पूर्णांक Feature_Control;
    अक्षर Pad2[0x7fc4];
    /* DBDMA Channel Register Space */
    अक्षर SCSI_DMA[0x100];
    अक्षर Pad3[0x300];
    अक्षर SCCA_Tx_DMA[0x100];
    अक्षर SCCA_Rx_DMA[0x100];
    अक्षर SCCB_Tx_DMA[0x100];
    अक्षर SCCB_Rx_DMA[0x100];
    अक्षर Pad4[0x7800];
    /* Device Register Space */
    अक्षर SCSI[0x1000];
    अक्षर ADB[0x1000];
    अक्षर SCC_Legacy[0x1000];
    अक्षर SCC[0x1000];
    अक्षर Pad9[0x2000];
    अक्षर VIA[0x2000];
    अक्षर Pad10[0x28000];
    अक्षर OpenPIC[0x40000];
पूर्ण;

बाह्य अस्थिर काष्ठा Hydra __iomem *Hydra;


    /*
     *  Feature Control Register
     */

#घोषणा HYDRA_FC_SCC_CELL_EN	0x00000001	/* Enable SCC Clock */
#घोषणा HYDRA_FC_SCSI_CELL_EN	0x00000002	/* Enable SCSI Clock */
#घोषणा HYDRA_FC_SCCA_ENABLE	0x00000004	/* Enable SCC A Lines */
#घोषणा HYDRA_FC_SCCB_ENABLE	0x00000008	/* Enable SCC B Lines */
#घोषणा HYDRA_FC_ARB_BYPASS	0x00000010	/* Bypass Internal Arbiter */
#घोषणा HYDRA_FC_RESET_SCC	0x00000020	/* Reset SCC */
#घोषणा HYDRA_FC_MPIC_ENABLE	0x00000040	/* Enable OpenPIC */
#घोषणा HYDRA_FC_SLOW_SCC_PCLK	0x00000080	/* 1=15.6672, 0=25 MHz */
#घोषणा HYDRA_FC_MPIC_IS_MASTER	0x00000100	/* OpenPIC Master Mode */


    /*
     *  OpenPIC Interrupt Sources
     */

#घोषणा HYDRA_INT_SIO		0
#घोषणा HYDRA_INT_SCSI_DMA	1
#घोषणा HYDRA_INT_SCCA_TX_DMA	2
#घोषणा HYDRA_INT_SCCA_RX_DMA	3
#घोषणा HYDRA_INT_SCCB_TX_DMA	4
#घोषणा HYDRA_INT_SCCB_RX_DMA	5
#घोषणा HYDRA_INT_SCSI		6
#घोषणा HYDRA_INT_SCCA		7
#घोषणा HYDRA_INT_SCCB		8
#घोषणा HYDRA_INT_VIA		9
#घोषणा HYDRA_INT_ADB		10
#घोषणा HYDRA_INT_ADB_NMI	11
#घोषणा HYDRA_INT_EXT1		12	/* PCI IRQW */
#घोषणा HYDRA_INT_EXT2		13	/* PCI IRQX */
#घोषणा HYDRA_INT_EXT3		14	/* PCI IRQY */
#घोषणा HYDRA_INT_EXT4		15	/* PCI IRQZ */
#घोषणा HYDRA_INT_EXT5		16	/* IDE Primary/Secondary */
#घोषणा HYDRA_INT_EXT6		17	/* IDE Secondary */
#घोषणा HYDRA_INT_EXT7		18	/* Power Off Request */
#घोषणा HYDRA_INT_SPARE		19

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _ASMPPC_HYDRA_H */
