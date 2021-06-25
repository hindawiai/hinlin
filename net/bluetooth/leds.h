<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2015, Heiner Kallweit <hkallweit1@gmail.com>
 */

#अगर IS_ENABLED(CONFIG_BT_LEDS)

व्योम hci_leds_update_घातered(काष्ठा hci_dev *hdev, bool enabled);
व्योम hci_leds_init(काष्ठा hci_dev *hdev);

व्योम bt_leds_init(व्योम);
व्योम bt_leds_cleanup(व्योम);

#अन्यथा

अटल अंतरभूत व्योम hci_leds_update_घातered(काष्ठा hci_dev *hdev,
					   bool enabled) अणुपूर्ण
अटल अंतरभूत व्योम hci_leds_init(काष्ठा hci_dev *hdev) अणुपूर्ण

अटल अंतरभूत व्योम bt_leds_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम bt_leds_cleanup(व्योम) अणुपूर्ण

#पूर्ण_अगर
