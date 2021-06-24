<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _I8042_SPARCIO_H
#घोषणा _I8042_SPARCIO_H

#समावेश <linux/of_device.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/prom.h>

अटल पूर्णांक i8042_kbd_irq = -1;
अटल पूर्णांक i8042_aux_irq = -1;
#घोषणा I8042_KBD_IRQ i8042_kbd_irq
#घोषणा I8042_AUX_IRQ i8042_aux_irq

#घोषणा I8042_KBD_PHYS_DESC "sparcps2/serio0"
#घोषणा I8042_AUX_PHYS_DESC "sparcps2/serio1"
#घोषणा I8042_MUX_PHYS_DESC "sparcps2/serio%d"

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

#अगर_घोषित CONFIG_PCI

अटल काष्ठा resource *kbd_res;

#घोषणा OBP_PS2KBD_NAME1	"kb_ps2"
#घोषणा OBP_PS2KBD_NAME2	"keyboard"
#घोषणा OBP_PS2MS_NAME1		"kdmouse"
#घोषणा OBP_PS2MS_NAME2		"mouse"

अटल पूर्णांक sparc_i8042_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dp;

	क्रम_each_child_of_node(op->dev.of_node, dp) अणु
		अगर (of_node_name_eq(dp, OBP_PS2KBD_NAME1) ||
		    of_node_name_eq(dp, OBP_PS2KBD_NAME2)) अणु
			काष्ठा platक्रमm_device *kbd = of_find_device_by_node(dp);
			अचिन्हित पूर्णांक irq = kbd->archdata.irqs[0];
			अगर (irq == 0xffffffff)
				irq = op->archdata.irqs[0];
			i8042_kbd_irq = irq;
			kbd_iobase = of_ioremap(&kbd->resource[0],
						0, 8, "kbd");
			kbd_res = &kbd->resource[0];
		पूर्ण अन्यथा अगर (of_node_name_eq(dp, OBP_PS2MS_NAME1) ||
			   of_node_name_eq(dp, OBP_PS2MS_NAME2)) अणु
			काष्ठा platक्रमm_device *ms = of_find_device_by_node(dp);
			अचिन्हित पूर्णांक irq = ms->archdata.irqs[0];
			अगर (irq == 0xffffffff)
				irq = op->archdata.irqs[0];
			i8042_aux_irq = irq;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sparc_i8042_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	of_iounmap(kbd_res, kbd_iobase, 8);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sparc_i8042_match[] = अणु
	अणु
		.name = "8042",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sparc_i8042_match);

अटल काष्ठा platक्रमm_driver sparc_i8042_driver = अणु
	.driver = अणु
		.name = "i8042",
		.of_match_table = sparc_i8042_match,
	पूर्ण,
	.probe		= sparc_i8042_probe,
	.हटाओ		= sparc_i8042_हटाओ,
पूर्ण;

अटल पूर्णांक __init i8042_platक्रमm_init(व्योम)
अणु
	काष्ठा device_node *root = of_find_node_by_path("/");
	स्थिर अक्षर *name = of_get_property(root, "name", शून्य);

	अगर (name && !म_भेद(name, "SUNW,JavaStation-1")) अणु
		/* Hardcoded values क्रम MrCoffee.  */
		i8042_kbd_irq = i8042_aux_irq = 13 | 0x20;
		kbd_iobase = ioremap(0x71300060, 8);
		अगर (!kbd_iobase)
			वापस -ENODEV;
	पूर्ण अन्यथा अणु
		पूर्णांक err = platक्रमm_driver_रेजिस्टर(&sparc_i8042_driver);
		अगर (err)
			वापस err;

		अगर (i8042_kbd_irq == -1 ||
		    i8042_aux_irq == -1) अणु
			अगर (kbd_iobase) अणु
				of_iounmap(kbd_res, kbd_iobase, 8);
				kbd_iobase = (व्योम __iomem *) शून्य;
			पूर्ण
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	i8042_reset = I8042_RESET_ALWAYS;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम i8042_platक्रमm_निकास(व्योम)
अणु
	काष्ठा device_node *root = of_find_node_by_path("/");
	स्थिर अक्षर *name = of_get_property(root, "name", शून्य);

	अगर (!name || म_भेद(name, "SUNW,JavaStation-1"))
		platक्रमm_driver_unरेजिस्टर(&sparc_i8042_driver);
पूर्ण

#अन्यथा /* !CONFIG_PCI */
अटल पूर्णांक __init i8042_platक्रमm_init(व्योम)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत व्योम i8042_platक्रमm_निकास(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* !CONFIG_PCI */

#पूर्ण_अगर /* _I8042_SPARCIO_H */
