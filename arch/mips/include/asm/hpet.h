<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_HPET_H
#घोषणा _ASM_HPET_H

#अगर_घोषित CONFIG_RS780_HPET

#घोषणा HPET_MMAP_SIZE		1024

#घोषणा HPET_ID			0x000
#घोषणा HPET_PERIOD		0x004
#घोषणा HPET_CFG		0x010
#घोषणा HPET_STATUS		0x020
#घोषणा HPET_COUNTER	0x0f0

#घोषणा HPET_Tn_CFG(n)		(0x100 + 0x20 * n)
#घोषणा HPET_Tn_CMP(n)		(0x108 + 0x20 * n)
#घोषणा HPET_Tn_ROUTE(n)	(0x110 + 0x20 * n)

#घोषणा HPET_T0_IRS		0x001
#घोषणा HPET_T1_IRS		0x002
#घोषणा HPET_T3_IRS		0x004

#घोषणा HPET_T0_CFG		0x100
#घोषणा HPET_T0_CMP		0x108
#घोषणा HPET_T0_ROUTE	0x110
#घोषणा HPET_T1_CFG		0x120
#घोषणा HPET_T1_CMP		0x128
#घोषणा HPET_T1_ROUTE	0x130
#घोषणा HPET_T2_CFG		0x140
#घोषणा HPET_T2_CMP		0x148
#घोषणा HPET_T2_ROUTE	0x150

#घोषणा HPET_ID_REV			0x000000ff
#घोषणा HPET_ID_NUMBER		0x00001f00
#घोषणा HPET_ID_64BIT		0x00002000
#घोषणा HPET_ID_LEGSUP		0x00008000
#घोषणा HPET_ID_VENDOR		0xffff0000
#घोषणा HPET_ID_NUMBER_SHIFT	8
#घोषणा HPET_ID_VENDOR_SHIFT	16

#घोषणा HPET_CFG_ENABLE		0x001
#घोषणा HPET_CFG_LEGACY		0x002
#घोषणा HPET_LEGACY_8254		2
#घोषणा HPET_LEGACY_RTC		8

#घोषणा HPET_TN_LEVEL		0x0002
#घोषणा HPET_TN_ENABLE		0x0004
#घोषणा HPET_TN_PERIODIC	0x0008
#घोषणा HPET_TN_PERIODIC_CAP	0x0010
#घोषणा HPET_TN_64BIT_CAP	0x0020
#घोषणा HPET_TN_SETVAL		0x0040
#घोषणा HPET_TN_32BIT		0x0100
#घोषणा HPET_TN_ROUTE		0x3e00
#घोषणा HPET_TN_FSB			0x4000
#घोषणा HPET_TN_FSB_CAP		0x8000
#घोषणा HPET_TN_ROUTE_SHIFT	9

/* Max HPET Period is 10^8 femto sec as in HPET spec */
#घोषणा HPET_MAX_PERIOD		100000000UL
/*
 * Min HPET period is 10^5 femto sec just क्रम safety. If it is less than this,
 * then 32 bit HPET counter wrapsaround in less than 0.5 sec.
 */
#घोषणा HPET_MIN_PERIOD		100000UL

#घोषणा HPET_ADDR		0x20000
#घोषणा HPET_MMIO_ADDR	0x90000e0000020000
#घोषणा HPET_FREQ		14318780
#घोषणा HPET_COMPARE_VAL	((HPET_FREQ + HZ / 2) / HZ)
#घोषणा HPET_T0_IRQ		0

बाह्य व्योम __init setup_hpet_समयr(व्योम);
#पूर्ण_अगर /* CONFIG_RS780_HPET */
#पूर्ण_अगर /* _ASM_HPET_H */
