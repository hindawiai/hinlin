<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#अगर_अघोषित _IXGBEVF_REGS_H_
#घोषणा _IXGBEVF_REGS_H_

#घोषणा IXGBE_VFCTRL		0x00000
#घोषणा IXGBE_VFSTATUS		0x00008
#घोषणा IXGBE_VFLINKS		0x00010
#घोषणा IXGBE_VFFRTIMER		0x00048
#घोषणा IXGBE_VFRXMEMWRAP	0x03190
#घोषणा IXGBE_VTEICR		0x00100
#घोषणा IXGBE_VTEICS		0x00104
#घोषणा IXGBE_VTEIMS		0x00108
#घोषणा IXGBE_VTEIMC		0x0010C
#घोषणा IXGBE_VTEIAC		0x00110
#घोषणा IXGBE_VTEIAM		0x00114
#घोषणा IXGBE_VTEITR(x)		(0x00820 + (4 * (x)))
#घोषणा IXGBE_VTIVAR(x)		(0x00120 + (4 * (x)))
#घोषणा IXGBE_VTIVAR_MISC	0x00140
#घोषणा IXGBE_VTRSCINT(x)	(0x00180 + (4 * (x)))
#घोषणा IXGBE_VFRDBAL(x)	(0x01000 + (0x40 * (x)))
#घोषणा IXGBE_VFRDBAH(x)	(0x01004 + (0x40 * (x)))
#घोषणा IXGBE_VFRDLEN(x)	(0x01008 + (0x40 * (x)))
#घोषणा IXGBE_VFRDH(x)		(0x01010 + (0x40 * (x)))
#घोषणा IXGBE_VFRDT(x)		(0x01018 + (0x40 * (x)))
#घोषणा IXGBE_VFRXDCTL(x)	(0x01028 + (0x40 * (x)))
#घोषणा IXGBE_VFSRRCTL(x)	(0x01014 + (0x40 * (x)))
#घोषणा IXGBE_VFRSCCTL(x)	(0x0102C + (0x40 * (x)))
#घोषणा IXGBE_VFPSRTYPE		0x00300
#घोषणा IXGBE_VFTDBAL(x)	(0x02000 + (0x40 * (x)))
#घोषणा IXGBE_VFTDBAH(x)	(0x02004 + (0x40 * (x)))
#घोषणा IXGBE_VFTDLEN(x)	(0x02008 + (0x40 * (x)))
#घोषणा IXGBE_VFTDH(x)		(0x02010 + (0x40 * (x)))
#घोषणा IXGBE_VFTDT(x)		(0x02018 + (0x40 * (x)))
#घोषणा IXGBE_VFTXDCTL(x)	(0x02028 + (0x40 * (x)))
#घोषणा IXGBE_VFTDWBAL(x)	(0x02038 + (0x40 * (x)))
#घोषणा IXGBE_VFTDWBAH(x)	(0x0203C + (0x40 * (x)))
#घोषणा IXGBE_VFDCA_RXCTRL(x)	(0x0100C + (0x40 * (x)))
#घोषणा IXGBE_VFDCA_TXCTRL(x)	(0x0200c + (0x40 * (x)))
#घोषणा IXGBE_VFGPRC		0x0101C
#घोषणा IXGBE_VFGPTC		0x0201C
#घोषणा IXGBE_VFGORC_LSB	0x01020
#घोषणा IXGBE_VFGORC_MSB	0x01024
#घोषणा IXGBE_VFGOTC_LSB	0x02020
#घोषणा IXGBE_VFGOTC_MSB	0x02024
#घोषणा IXGBE_VFMPRC		0x01034
#घोषणा IXGBE_VFMRQC		0x3000
#घोषणा IXGBE_VFRSSRK(x)	(0x3100 + ((x) * 4))
#घोषणा IXGBE_VFRETA(x)		(0x3200 + ((x) * 4))

/* VFMRQC bits */
#घोषणा IXGBE_VFMRQC_RSSEN		0x00000001  /* RSS Enable */
#घोषणा IXGBE_VFMRQC_RSS_FIELD_IPV4_TCP	0x00010000
#घोषणा IXGBE_VFMRQC_RSS_FIELD_IPV4	0x00020000
#घोषणा IXGBE_VFMRQC_RSS_FIELD_IPV6	0x00100000
#घोषणा IXGBE_VFMRQC_RSS_FIELD_IPV6_TCP	0x00200000

#घोषणा IXGBE_WRITE_FLUSH(a)	(IXGBE_READ_REG(a, IXGBE_VFSTATUS))

#पूर्ण_अगर /* _IXGBEVF_REGS_H_ */
