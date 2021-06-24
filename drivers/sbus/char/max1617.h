<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* $Id: max1617.h,v 1.1 2001/04/02 09:59:08 davem Exp $ */
#अगर_अघोषित _MAX1617_H
#घोषणा _MAX1617_H

#घोषणा MAX1617_AMB_TEMP	0x00 /* Ambient temp in C	*/
#घोषणा MAX1617_CPU_TEMP	0x01 /* Processor die temp in C	*/
#घोषणा MAX1617_STATUS		0x02 /* Chip status bits	*/

/* Read-only versions of changeable रेजिस्टरs. */
#घोषणा MAX1617_RD_CFG_BYTE	0x03 /* Config रेजिस्टर		*/
#घोषणा MAX1617_RD_CVRATE_BYTE	0x04 /* Temp conversion rate	*/
#घोषणा MAX1617_RD_AMB_HIGHLIM	0x05 /* Ambient high limit	*/
#घोषणा MAX1617_RD_AMB_LOWLIM	0x06 /* Ambient low limit	*/
#घोषणा MAX1617_RD_CPU_HIGHLIM	0x07 /* Processor high limit	*/
#घोषणा MAX1617_RD_CPU_LOWLIM	0x08 /* Processor low limit	*/

/* Write-only versions of the same. */
#घोषणा MAX1617_WR_CFG_BYTE	0x09
#घोषणा MAX1617_WR_CVRATE_BYTE	0x0a
#घोषणा MAX1617_WR_AMB_HIGHLIM	0x0b
#घोषणा MAX1617_WR_AMB_LOWLIM	0x0c
#घोषणा MAX1617_WR_CPU_HIGHLIM	0x0d
#घोषणा MAX1617_WR_CPU_LOWLIM	0x0e

#घोषणा MAX1617_ONESHOT		0x0f

#पूर्ण_अगर /* _MAX1617_H */
