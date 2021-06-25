<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _I8042_IO_H
#घोषणा _I8042_IO_H


/*
 * Names.
 */

#घोषणा I8042_KBD_PHYS_DESC "isa0060/serio0"
#घोषणा I8042_AUX_PHYS_DESC "isa0060/serio1"
#घोषणा I8042_MUX_PHYS_DESC "isa0060/serio%d"

/*
 * IRQs.
 */

#अगर_घोषित __alpha__
# define I8042_KBD_IRQ	1
# define I8042_AUX_IRQ	(RTC_PORT(0) == 0x170 ? 9 : 12)	/* Jensen is special */
#या_अगर defined(__arm__)
/* defined in include/यंत्र-arm/arch-xxx/irqs.h */
#समावेश <यंत्र/irq.h>
#या_अगर defined(CONFIG_PPC)
बाह्य पूर्णांक of_i8042_kbd_irq;
बाह्य पूर्णांक of_i8042_aux_irq;
# define I8042_KBD_IRQ  of_i8042_kbd_irq
# define I8042_AUX_IRQ  of_i8042_aux_irq
#अन्यथा
# define I8042_KBD_IRQ	1
# define I8042_AUX_IRQ	12
#पूर्ण_अगर


/*
 * Register numbers.
 */

#घोषणा I8042_COMMAND_REG	0x64
#घोषणा I8042_STATUS_REG	0x64
#घोषणा I8042_DATA_REG		0x60

अटल अंतरभूत पूर्णांक i8042_पढ़ो_data(व्योम)
अणु
	वापस inb(I8042_DATA_REG);
पूर्ण

अटल अंतरभूत पूर्णांक i8042_पढ़ो_status(व्योम)
अणु
	वापस inb(I8042_STATUS_REG);
पूर्ण

अटल अंतरभूत व्योम i8042_ग_लिखो_data(पूर्णांक val)
अणु
	outb(val, I8042_DATA_REG);
पूर्ण

अटल अंतरभूत व्योम i8042_ग_लिखो_command(पूर्णांक val)
अणु
	outb(val, I8042_COMMAND_REG);
पूर्ण

अटल अंतरभूत पूर्णांक i8042_platक्रमm_init(व्योम)
अणु
/*
 * On some platक्रमms touching the i8042 data रेजिस्टर region can करो really
 * bad things. Because of this the region is always reserved on such boxes.
 */
#अगर defined(CONFIG_PPC)
	अगर (check_legacy_ioport(I8042_DATA_REG))
		वापस -ENODEV;
#पूर्ण_अगर
#अगर !defined(__sh__) && !defined(__alpha__)
	अगर (!request_region(I8042_DATA_REG, 16, "i8042"))
		वापस -EBUSY;
#पूर्ण_अगर

	i8042_reset = I8042_RESET_ALWAYS;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम i8042_platक्रमm_निकास(व्योम)
अणु
#अगर !defined(__sh__) && !defined(__alpha__)
	release_region(I8042_DATA_REG, 16);
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* _I8042_IO_H */
