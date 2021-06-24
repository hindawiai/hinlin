<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Platक्रमm data क्रम the Intel TCO Watchकरोg
 */

#अगर_अघोषित _ITCO_WDT_H_
#घोषणा _ITCO_WDT_H_

/* Watchकरोg resources */
#घोषणा ICH_RES_IO_TCO		0
#घोषणा ICH_RES_IO_SMI		1
#घोषणा ICH_RES_MEM_OFF		2
#घोषणा ICH_RES_MEM_GCS_PMC	0

/**
 * काष्ठा itco_wdt_platक्रमm_data - iTCO_wdt platक्रमm data
 * @name: Name of the platक्रमm
 * @version: iTCO version
 * @no_reboot_use_pmc: Use PMC BXT API to set and clear NO_REBOOT bit
 */
काष्ठा itco_wdt_platक्रमm_data अणु
	अक्षर name[32];
	अचिन्हित पूर्णांक version;
	bool no_reboot_use_pmc;
पूर्ण;

#पूर्ण_अगर /* _ITCO_WDT_H_ */
