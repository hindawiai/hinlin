<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MIT) */
/*
 * Microsemi Ocelot Switch driver
 *
 * License: Dual MIT/GPL
 * Copyright (c) 2017 Microsemi Corporation
 * Copyright 2020 NXP
 */

#अगर_अघोषित _MSCC_OCELOT_PTP_H_
#घोषणा _MSCC_OCELOT_PTP_H_

#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <soc/mscc/ocelot.h>

#घोषणा PTP_PIN_CFG_RSZ			0x20
#घोषणा PTP_PIN_TOD_SEC_MSB_RSZ		PTP_PIN_CFG_RSZ
#घोषणा PTP_PIN_TOD_SEC_LSB_RSZ		PTP_PIN_CFG_RSZ
#घोषणा PTP_PIN_TOD_NSEC_RSZ		PTP_PIN_CFG_RSZ
#घोषणा PTP_PIN_WF_HIGH_PERIOD_RSZ	PTP_PIN_CFG_RSZ
#घोषणा PTP_PIN_WF_LOW_PERIOD_RSZ	PTP_PIN_CFG_RSZ

#घोषणा PTP_PIN_CFG_DOM			BIT(0)
#घोषणा PTP_PIN_CFG_SYNC		BIT(2)
#घोषणा PTP_PIN_CFG_ACTION(x)		((x) << 3)
#घोषणा PTP_PIN_CFG_ACTION_MASK		PTP_PIN_CFG_ACTION(0x7)

क्रमागत अणु
	PTP_PIN_ACTION_IDLE = 0,
	PTP_PIN_ACTION_LOAD,
	PTP_PIN_ACTION_SAVE,
	PTP_PIN_ACTION_CLOCK,
	PTP_PIN_ACTION_DELTA,
	PTP_PIN_ACTION_NOSYNC,
	PTP_PIN_ACTION_SYNC,
पूर्ण;

#घोषणा PTP_CFG_MISC_PTP_EN		BIT(2)

#घोषणा PTP_CFG_CLK_ADJ_CFG_ENA		BIT(0)
#घोषणा PTP_CFG_CLK_ADJ_CFG_सूची		BIT(1)

#घोषणा PTP_CFG_CLK_ADJ_FREQ_NS		BIT(30)

पूर्णांक ocelot_ptp_समय_लो64(काष्ठा ptp_घड़ी_info *ptp, काष्ठा बारpec64 *ts);
पूर्णांक ocelot_ptp_समय_रखो64(काष्ठा ptp_घड़ी_info *ptp,
			 स्थिर काष्ठा बारpec64 *ts);
पूर्णांक ocelot_ptp_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta);
पूर्णांक ocelot_ptp_adjfine(काष्ठा ptp_घड़ी_info *ptp, दीर्घ scaled_ppm);
पूर्णांक ocelot_ptp_verअगरy(काष्ठा ptp_घड़ी_info *ptp, अचिन्हित पूर्णांक pin,
		      क्रमागत ptp_pin_function func, अचिन्हित पूर्णांक chan);
पूर्णांक ocelot_ptp_enable(काष्ठा ptp_घड़ी_info *ptp,
		      काष्ठा ptp_घड़ी_request *rq, पूर्णांक on);
पूर्णांक ocelot_init_बारtamp(काष्ठा ocelot *ocelot,
			  स्थिर काष्ठा ptp_घड़ी_info *info);
पूर्णांक ocelot_deinit_बारtamp(काष्ठा ocelot *ocelot);
#पूर्ण_अगर
