<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ACPI_BUTTON_H
#घोषणा ACPI_BUTTON_H

#घोषणा ACPI_BUTTON_HID_POWER	"PNP0C0C"
#घोषणा ACPI_BUTTON_HID_LID	"PNP0C0D"
#घोषणा ACPI_BUTTON_HID_SLEEP	"PNP0C0E"

#अगर IS_ENABLED(CONFIG_ACPI_BUTTON)
बाह्य पूर्णांक acpi_lid_खोलो(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक acpi_lid_खोलो(व्योम)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर /* IS_ENABLED(CONFIG_ACPI_BUTTON) */

#पूर्ण_अगर /* ACPI_BUTTON_H */
