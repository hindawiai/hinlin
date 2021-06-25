<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Support Power Management
 *
 * Copyright 2014-2015 Freescale Semiconductor Inc.
 */
#अगर_अघोषित __PPC_FSL_PM_H
#घोषणा __PPC_FSL_PM_H

#घोषणा E500_PM_PH10	1
#घोषणा E500_PM_PH15	2
#घोषणा E500_PM_PH20	3
#घोषणा E500_PM_PH30	4
#घोषणा E500_PM_DOZE	E500_PM_PH10
#घोषणा E500_PM_NAP	E500_PM_PH15

#घोषणा PLAT_PM_SLEEP	20
#घोषणा PLAT_PM_LPM20	30

#घोषणा FSL_PM_SLEEP		(1 << 0)
#घोषणा FSL_PM_DEEP_SLEEP	(1 << 1)

काष्ठा fsl_pm_ops अणु
	/* mask pending पूर्णांकerrupts to the RCPM from MPIC */
	व्योम (*irq_mask)(पूर्णांक cpu);

	/* unmask pending पूर्णांकerrupts to the RCPM from MPIC */
	व्योम (*irq_unmask)(पूर्णांक cpu);
	व्योम (*cpu_enter_state)(पूर्णांक cpu, पूर्णांक state);
	व्योम (*cpu_निकास_state)(पूर्णांक cpu, पूर्णांक state);
	व्योम (*cpu_up_prepare)(पूर्णांक cpu);
	व्योम (*cpu_die)(पूर्णांक cpu);
	पूर्णांक (*plat_enter_sleep)(व्योम);
	व्योम (*मुक्तze_समय_base)(bool मुक्तze);

	/* keep the घातer of IP blocks during sleep/deep sleep */
	व्योम (*set_ip_घातer)(bool enable, u32 mask);

	/* get platक्रमm supported घातer management modes */
	अचिन्हित पूर्णांक (*get_pm_modes)(व्योम);
पूर्ण;

बाह्य स्थिर काष्ठा fsl_pm_ops *qoriq_pm_ops;

पूर्णांक __init fsl_rcpm_init(व्योम);

#पूर्ण_अगर /* __PPC_FSL_PM_H */
