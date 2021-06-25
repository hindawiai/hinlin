<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _I8042_JAZZ_H
#घोषणा _I8042_JAZZ_H

#समावेश <यंत्र/jazz.h>


/*
 * Names.
 */

#घोषणा I8042_KBD_PHYS_DESC "R4030/serio0"
#घोषणा I8042_AUX_PHYS_DESC "R4030/serio1"
#घोषणा I8042_MUX_PHYS_DESC "R4030/serio%d"

/*
 * IRQs.
 */

#घोषणा I8042_KBD_IRQ JAZZ_KEYBOARD_IRQ
#घोषणा I8042_AUX_IRQ JAZZ_MOUSE_IRQ

#घोषणा I8042_COMMAND_REG	((अचिन्हित दीर्घ)&jazz_kh->command)
#घोषणा I8042_STATUS_REG	((अचिन्हित दीर्घ)&jazz_kh->command)
#घोषणा I8042_DATA_REG		((अचिन्हित दीर्घ)&jazz_kh->data)

अटल अंतरभूत पूर्णांक i8042_पढ़ो_data(व्योम)
अणु
	वापस jazz_kh->data;
पूर्ण

अटल अंतरभूत पूर्णांक i8042_पढ़ो_status(व्योम)
अणु
	वापस jazz_kh->command;
पूर्ण

अटल अंतरभूत व्योम i8042_ग_लिखो_data(पूर्णांक val)
अणु
	jazz_kh->data = val;
पूर्ण

अटल अंतरभूत व्योम i8042_ग_लिखो_command(पूर्णांक val)
अणु
	jazz_kh->command = val;
पूर्ण

अटल अंतरभूत पूर्णांक i8042_platक्रमm_init(व्योम)
अणु
#अगर 0
	/* XXX JAZZ_KEYBOARD_ADDRESS is a भव address */
	अगर (!request_mem_region(JAZZ_KEYBOARD_ADDRESS, 2, "i8042"))
		वापस -EBUSY;
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम i8042_platक्रमm_निकास(व्योम)
अणु
#अगर 0
	release_mem_region(JAZZ_KEYBOARD_ADDRESS, 2);
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* _I8042_JAZZ_H */
