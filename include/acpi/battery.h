<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ACPI_BATTERY_H
#घोषणा __ACPI_BATTERY_H

#समावेश <linux/घातer_supply.h>

#घोषणा ACPI_BATTERY_CLASS "battery"

#घोषणा ACPI_BATTERY_NOTIFY_STATUS	0x80
#घोषणा ACPI_BATTERY_NOTIFY_INFO	0x81
#घोषणा ACPI_BATTERY_NOTIFY_THRESHOLD   0x82

काष्ठा acpi_battery_hook अणु
	स्थिर अक्षर *name;
	पूर्णांक (*add_battery)(काष्ठा घातer_supply *battery);
	पूर्णांक (*हटाओ_battery)(काष्ठा घातer_supply *battery);
	काष्ठा list_head list;
पूर्ण;

व्योम battery_hook_रेजिस्टर(काष्ठा acpi_battery_hook *hook);
व्योम battery_hook_unरेजिस्टर(काष्ठा acpi_battery_hook *hook);

#पूर्ण_अगर
