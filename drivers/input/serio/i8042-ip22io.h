<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _I8042_IP22_H
#घोषणा _I8042_IP22_H

#समावेश <यंत्र/sgi/ioc.h>
#समावेश <यंत्र/sgi/ip22.h>


/*
 * Names.
 */

#घोषणा I8042_KBD_PHYS_DESC "hpc3ps2/serio0"
#घोषणा I8042_AUX_PHYS_DESC "hpc3ps2/serio1"
#घोषणा I8042_MUX_PHYS_DESC "hpc3ps2/serio%d"

/*
 * IRQs.
 */

#घोषणा I8042_KBD_IRQ SGI_KEYBD_IRQ
#घोषणा I8042_AUX_IRQ SGI_KEYBD_IRQ

/*
 * Register numbers.
 */

#घोषणा I8042_COMMAND_REG	((अचिन्हित दीर्घ)&sgioc->kbdmouse.command)
#घोषणा I8042_STATUS_REG	((अचिन्हित दीर्घ)&sgioc->kbdmouse.command)
#घोषणा I8042_DATA_REG		((अचिन्हित दीर्घ)&sgioc->kbdmouse.data)

अटल अंतरभूत पूर्णांक i8042_पढ़ो_data(व्योम)
अणु
	वापस sgioc->kbdmouse.data;
पूर्ण

अटल अंतरभूत पूर्णांक i8042_पढ़ो_status(व्योम)
अणु
	वापस sgioc->kbdmouse.command;
पूर्ण

अटल अंतरभूत व्योम i8042_ग_लिखो_data(पूर्णांक val)
अणु
	sgioc->kbdmouse.data = val;
पूर्ण

अटल अंतरभूत व्योम i8042_ग_लिखो_command(पूर्णांक val)
अणु
	sgioc->kbdmouse.command = val;
पूर्ण

अटल अंतरभूत पूर्णांक i8042_platक्रमm_init(व्योम)
अणु
#अगर 0
	/* XXX sgi_kh is a भव address */
	अगर (!request_mem_region(sgi_kh, माप(काष्ठा hpc_keyb), "i8042"))
		वापस -EBUSY;
#पूर्ण_अगर

	i8042_reset = I8042_RESET_ALWAYS;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम i8042_platक्रमm_निकास(व्योम)
अणु
#अगर 0
	release_mem_region(JAZZ_KEYBOARD_ADDRESS, माप(काष्ठा hpc_keyb));
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* _I8042_IP22_H */
