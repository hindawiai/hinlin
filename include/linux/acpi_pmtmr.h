<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ACPI_PMTMR_H_
#घोषणा _ACPI_PMTMR_H_

#समावेश <linux/घड़ीsource.h>

/* Number of PMTMR ticks expected during calibration run */
#घोषणा PMTMR_TICKS_PER_SEC 3579545

/* limit it to 24 bits */
#घोषणा ACPI_PM_MASK CLOCKSOURCE_MASK(24)

/* Overrun value */
#घोषणा ACPI_PM_OVRRUN	(1<<24)

#अगर_घोषित CONFIG_X86_PM_TIMER

बाह्य u32 acpi_pm_पढ़ो_verअगरied(व्योम);
बाह्य u32 pmपंचांगr_ioport;

अटल अंतरभूत u32 acpi_pm_पढ़ो_early(व्योम)
अणु
	अगर (!pmपंचांगr_ioport)
		वापस 0;
	/* mask the output to 24 bits */
	वापस acpi_pm_पढ़ो_verअगरied() & ACPI_PM_MASK;
पूर्ण

#अन्यथा

अटल अंतरभूत u32 acpi_pm_पढ़ो_early(व्योम)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर

