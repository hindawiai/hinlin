<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _I8042_SNIRM_H
#घोषणा _I8042_SNIRM_H

#समावेश <यंत्र/sni.h>


/*
 * Names.
 */

#घोषणा I8042_KBD_PHYS_DESC "onboard/serio0"
#घोषणा I8042_AUX_PHYS_DESC "onboard/serio1"
#घोषणा I8042_MUX_PHYS_DESC "onboard/serio%d"

/*
 * IRQs.
 */
अटल पूर्णांक i8042_kbd_irq;
अटल पूर्णांक i8042_aux_irq;
#घोषणा I8042_KBD_IRQ i8042_kbd_irq
#घोषणा I8042_AUX_IRQ i8042_aux_irq

अटल व्योम __iomem *kbd_iobase;

#घोषणा I8042_COMMAND_REG	(kbd_iobase + 0x64UL)
#घोषणा I8042_DATA_REG		(kbd_iobase + 0x60UL)

अटल अंतरभूत पूर्णांक i8042_पढ़ो_data(व्योम)
अणु
	वापस पढ़ोb(kbd_iobase + 0x60UL);
पूर्ण

अटल अंतरभूत पूर्णांक i8042_पढ़ो_status(व्योम)
अणु
	वापस पढ़ोb(kbd_iobase + 0x64UL);
पूर्ण

अटल अंतरभूत व्योम i8042_ग_लिखो_data(पूर्णांक val)
अणु
	ग_लिखोb(val, kbd_iobase + 0x60UL);
पूर्ण

अटल अंतरभूत व्योम i8042_ग_लिखो_command(पूर्णांक val)
अणु
	ग_लिखोb(val, kbd_iobase + 0x64UL);
पूर्ण
अटल अंतरभूत पूर्णांक i8042_platक्रमm_init(व्योम)
अणु
	/* RM200 is strange ... */
	अगर (sni_brd_type == SNI_BRD_RM200) अणु
		kbd_iobase = ioremap(0x16000000, 4);
		i8042_kbd_irq = 33;
		i8042_aux_irq = 44;
	पूर्ण अन्यथा अणु
		kbd_iobase = ioremap(0x14000000, 4);
		i8042_kbd_irq = 1;
		i8042_aux_irq = 12;
	पूर्ण
	अगर (!kbd_iobase)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम i8042_platक्रमm_निकास(व्योम)
अणु

पूर्ण

#पूर्ण_अगर /* _I8042_SNIRM_H */
