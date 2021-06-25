<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MIT) */
/*
 * DSA driver क्रम:
 * Hirschmann Hellcreek TSN चयन.
 *
 * Copyright (C) 2019,2020 Hochschule Offenburg
 * Copyright (C) 2019,2020 Linutronix GmbH
 * Authors: Kurt Kanzenbach <kurt@linutronix.de>
 *	    Kamil Alkhouri <kamil.alkhouri@hs-offenburg.de>
 */

#अगर_अघोषित _HELLCREEK_PTP_H_
#घोषणा _HELLCREEK_PTP_H_

#समावेश <linux/bitops.h>
#समावेश <linux/ptp_घड़ी_kernel.h>

#समावेश "hellcreek.h"

/* Every jump in समय is 7 ns */
#घोषणा MAX_NS_PER_STEP			7L

/* Correct offset at every घड़ी cycle */
#घोषणा MIN_CLK_CYCLES_BETWEEN_STEPS	0

/* Maximum available slow offset resources */
#घोषणा MAX_SLOW_OFFSET_ADJ					\
	((अचिन्हित दीर्घ दीर्घ)((1 << 30) - 1) * MAX_NS_PER_STEP)

/* four बार a second overflow check */
#घोषणा HELLCREEK_OVERFLOW_PERIOD	(HZ / 4)

/* PTP Register */
#घोषणा PR_SETTINGS_C			(0x09 * 2)
#घोषणा PR_SETTINGS_C_RES3TS		BIT(4)
#घोषणा PR_SETTINGS_C_TS_SRC_TK_SHIFT	8
#घोषणा PR_SETTINGS_C_TS_SRC_TK_MASK	GENMASK(9, 8)
#घोषणा PR_COMMAND_C			(0x0a * 2)
#घोषणा PR_COMMAND_C_SS			BIT(0)

#घोषणा PR_CLOCK_STATUS_C		(0x0c * 2)
#घोषणा PR_CLOCK_STATUS_C_ENA_DRIFT	BIT(12)
#घोषणा PR_CLOCK_STATUS_C_OFS_ACT	BIT(13)
#घोषणा PR_CLOCK_STATUS_C_ENA_OFS	BIT(14)

#घोषणा PR_CLOCK_READ_C			(0x0d * 2)
#घोषणा PR_CLOCK_WRITE_C		(0x0e * 2)
#घोषणा PR_CLOCK_OFFSET_C		(0x0f * 2)
#घोषणा PR_CLOCK_DRIFT_C		(0x10 * 2)

#घोषणा PR_SS_FREE_DATA_C		(0x12 * 2)
#घोषणा PR_SS_SYNT_DATA_C		(0x14 * 2)
#घोषणा PR_SS_SYNC_DATA_C		(0x16 * 2)
#घोषणा PR_SS_DRAC_DATA_C		(0x18 * 2)

#घोषणा STATUS_OUT			(0x60 * 2)
#घोषणा STATUS_OUT_SYNC_GOOD		BIT(0)
#घोषणा STATUS_OUT_IS_GM		BIT(1)

पूर्णांक hellcreek_ptp_setup(काष्ठा hellcreek *hellcreek);
व्योम hellcreek_ptp_मुक्त(काष्ठा hellcreek *hellcreek);
u16 hellcreek_ptp_पढ़ो(काष्ठा hellcreek *hellcreek, अचिन्हित पूर्णांक offset);
व्योम hellcreek_ptp_ग_लिखो(काष्ठा hellcreek *hellcreek, u16 data,
			 अचिन्हित पूर्णांक offset);
u64 hellcreek_ptp_समय_लो_seconds(काष्ठा hellcreek *hellcreek, u64 ns);

#घोषणा ptp_to_hellcreek(ptp)					\
	container_of(ptp, काष्ठा hellcreek, ptp_घड़ी_info)

#घोषणा dw_overflow_to_hellcreek(dw)				\
	container_of(dw, काष्ठा hellcreek, overflow_work)

#घोषणा led_to_hellcreek(ldev, led)				\
	container_of(ldev, काष्ठा hellcreek, led)

#पूर्ण_अगर /* _HELLCREEK_PTP_H_ */
