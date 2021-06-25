<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम TANBAC TB0219 base board.
 *
 *  Copyright (C) 2005  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/vr41xx/giu.h>
#समावेश <यंत्र/vr41xx/tb0219.h>

MODULE_AUTHOR("Yoichi Yuasa <yuasa@linux-mips.org>");
MODULE_DESCRIPTION("TANBAC TB0219 base board driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक major;	/* शेष is dynamic major device number */
module_param(major, पूर्णांक, 0);
MODULE_PARM_DESC(major, "Major device number");

अटल व्योम (*old_machine_restart)(अक्षर *command);
अटल व्योम __iomem *tb0219_base;
अटल DEFINE_SPINLOCK(tb0219_lock);

#घोषणा tb0219_पढ़ो(offset)		पढ़ोw(tb0219_base + (offset))
#घोषणा tb0219_ग_लिखो(offset, value)	ग_लिखोw((value), tb0219_base + (offset))

#घोषणा TB0219_START	0x0a000000UL
#घोषणा TB0219_SIZE	0x20UL

#घोषणा TB0219_LED			0x00
#घोषणा TB0219_GPIO_INPUT		0x02
#घोषणा TB0219_GPIO_OUTPUT		0x04
#घोषणा TB0219_DIP_SWITCH		0x06
#घोषणा TB0219_MISC			0x08
#घोषणा TB0219_RESET			0x0e
#घोषणा TB0219_PCI_SLOT1_IRQ_STATUS	0x10
#घोषणा TB0219_PCI_SLOT2_IRQ_STATUS	0x12
#घोषणा TB0219_PCI_SLOT3_IRQ_STATUS	0x14

प्रकार क्रमागत अणु
	TYPE_LED,
	TYPE_GPIO_OUTPUT,
पूर्ण tb0219_type_t;

/*
 * Minor device number
 *	 0 = 7 segment LED
 *
 *	16 = GPIO IN 0
 *	17 = GPIO IN 1
 *	18 = GPIO IN 2
 *	19 = GPIO IN 3
 *	20 = GPIO IN 4
 *	21 = GPIO IN 5
 *	22 = GPIO IN 6
 *	23 = GPIO IN 7
 *
 *	32 = GPIO OUT 0
 *	33 = GPIO OUT 1
 *	34 = GPIO OUT 2
 *	35 = GPIO OUT 3
 *	36 = GPIO OUT 4
 *	37 = GPIO OUT 5
 *	38 = GPIO OUT 6
 *	39 = GPIO OUT 7
 *
 *	48 = DIP चयन 1
 *	49 = DIP चयन 2
 *	50 = DIP चयन 3
 *	51 = DIP चयन 4
 *	52 = DIP चयन 5
 *	53 = DIP चयन 6
 *	54 = DIP चयन 7
 *	55 = DIP चयन 8
 */

अटल अंतरभूत अक्षर get_led(व्योम)
अणु
	वापस (अक्षर)tb0219_पढ़ो(TB0219_LED);
पूर्ण

अटल अंतरभूत अक्षर get_gpio_input_pin(अचिन्हित पूर्णांक pin)
अणु
	uपूर्णांक16_t values;

	values = tb0219_पढ़ो(TB0219_GPIO_INPUT);
	अगर (values & (1 << pin))
		वापस '1';

	वापस '0';
पूर्ण

अटल अंतरभूत अक्षर get_gpio_output_pin(अचिन्हित पूर्णांक pin)
अणु
	uपूर्णांक16_t values;

	values = tb0219_पढ़ो(TB0219_GPIO_OUTPUT);
	अगर (values & (1 << pin))
		वापस '1';

	वापस '0';
पूर्ण

अटल अंतरभूत अक्षर get_dip_चयन(अचिन्हित पूर्णांक pin)
अणु
	uपूर्णांक16_t values;

	values = tb0219_पढ़ो(TB0219_DIP_SWITCH);
	अगर (values & (1 << pin))
		वापस '1';

	वापस '0';
पूर्ण

अटल अंतरभूत पूर्णांक set_led(अक्षर command)
अणु
	tb0219_ग_लिखो(TB0219_LED, command);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक set_gpio_output_pin(अचिन्हित पूर्णांक pin, अक्षर command)
अणु
	अचिन्हित दीर्घ flags;
	uपूर्णांक16_t value;

	अगर (command != '0' && command != '1')
		वापस -EINVAL;

	spin_lock_irqsave(&tb0219_lock, flags);
	value = tb0219_पढ़ो(TB0219_GPIO_OUTPUT);
	अगर (command == '0')
		value &= ~(1 << pin);
	अन्यथा
		value |= 1 << pin;
	tb0219_ग_लिखो(TB0219_GPIO_OUTPUT, value);
	spin_unlock_irqrestore(&tb0219_lock, flags);

	वापस 0;

पूर्ण

अटल sमाप_प्रकार tanbac_tb0219_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार len,
                                  loff_t *ppos)
अणु
	अचिन्हित पूर्णांक minor;
	अक्षर value;

	minor = iminor(file_inode(file));
	चयन (minor) अणु
	हाल 0:
		value = get_led();
		अवरोध;
	हाल 16 ... 23:
		value = get_gpio_input_pin(minor - 16);
		अवरोध;
	हाल 32 ... 39:
		value = get_gpio_output_pin(minor - 32);
		अवरोध;
	हाल 48 ... 55:
		value = get_dip_चयन(minor - 48);
		अवरोध;
	शेष:
		वापस -EBADF;
	पूर्ण

	अगर (len <= 0)
		वापस -EFAULT;

	अगर (put_user(value, buf))
		वापस -EFAULT;

	वापस 1;
पूर्ण

अटल sमाप_प्रकार tanbac_tb0219_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
                                   माप_प्रकार len, loff_t *ppos)
अणु
	अचिन्हित पूर्णांक minor;
	tb0219_type_t type;
	माप_प्रकार i;
	पूर्णांक retval = 0;
	अक्षर c;

	minor = iminor(file_inode(file));
	चयन (minor) अणु
	हाल 0:
		type = TYPE_LED;
		अवरोध;
	हाल 32 ... 39:
		type = TYPE_GPIO_OUTPUT;
		अवरोध;
	शेष:
		वापस -EBADF;
	पूर्ण

	क्रम (i = 0; i < len; i++) अणु
		अगर (get_user(c, data + i))
			वापस -EFAULT;

		चयन (type) अणु
		हाल TYPE_LED:
			retval = set_led(c);
			अवरोध;
		हाल TYPE_GPIO_OUTPUT:
			retval = set_gpio_output_pin(minor - 32, c);
			अवरोध;
		पूर्ण

		अगर (retval < 0)
			अवरोध;
	पूर्ण

	वापस i;
पूर्ण

अटल पूर्णांक tanbac_tb0219_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित पूर्णांक minor;

	minor = iminor(inode);
	चयन (minor) अणु
	हाल 0:
	हाल 16 ... 23:
	हाल 32 ... 39:
	हाल 48 ... 55:
		वापस stream_खोलो(inode, file);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EBADF;
पूर्ण

अटल पूर्णांक tanbac_tb0219_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations tb0219_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= tanbac_tb0219_पढ़ो,
	.ग_लिखो		= tanbac_tb0219_ग_लिखो,
	.खोलो		= tanbac_tb0219_खोलो,
	.release	= tanbac_tb0219_release,
	.llseek		= no_llseek,
पूर्ण;

अटल व्योम tb0219_restart(अक्षर *command)
अणु
	tb0219_ग_लिखो(TB0219_RESET, 0);
पूर्ण

अटल व्योम tb0219_pci_irq_init(व्योम)
अणु
	/* PCI Slot 1 */
	vr41xx_set_irq_trigger(TB0219_PCI_SLOT1_PIN, IRQ_TRIGGER_LEVEL, IRQ_SIGNAL_THROUGH);
	vr41xx_set_irq_level(TB0219_PCI_SLOT1_PIN, IRQ_LEVEL_LOW);

	/* PCI Slot 2 */
	vr41xx_set_irq_trigger(TB0219_PCI_SLOT2_PIN, IRQ_TRIGGER_LEVEL, IRQ_SIGNAL_THROUGH);
	vr41xx_set_irq_level(TB0219_PCI_SLOT2_PIN, IRQ_LEVEL_LOW);

	/* PCI Slot 3 */
	vr41xx_set_irq_trigger(TB0219_PCI_SLOT3_PIN, IRQ_TRIGGER_LEVEL, IRQ_SIGNAL_THROUGH);
	vr41xx_set_irq_level(TB0219_PCI_SLOT3_PIN, IRQ_LEVEL_LOW);
पूर्ण

अटल पूर्णांक tb0219_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक retval;

	अगर (request_mem_region(TB0219_START, TB0219_SIZE, "TB0219") == शून्य)
		वापस -EBUSY;

	tb0219_base = ioremap(TB0219_START, TB0219_SIZE);
	अगर (tb0219_base == शून्य) अणु
		release_mem_region(TB0219_START, TB0219_SIZE);
		वापस -ENOMEM;
	पूर्ण

	retval = रेजिस्टर_chrdev(major, "TB0219", &tb0219_fops);
	अगर (retval < 0) अणु
		iounmap(tb0219_base);
		tb0219_base = शून्य;
		release_mem_region(TB0219_START, TB0219_SIZE);
		वापस retval;
	पूर्ण

	old_machine_restart = _machine_restart;
	_machine_restart = tb0219_restart;

	tb0219_pci_irq_init();

	अगर (major == 0) अणु
		major = retval;
		prपूर्णांकk(KERN_INFO "TB0219: major number %d\n", major);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tb0219_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	_machine_restart = old_machine_restart;

	iounmap(tb0219_base);
	tb0219_base = शून्य;

	release_mem_region(TB0219_START, TB0219_SIZE);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_device *tb0219_platक्रमm_device;

अटल काष्ठा platक्रमm_driver tb0219_device_driver = अणु
	.probe		= tb0219_probe,
	.हटाओ		= tb0219_हटाओ,
	.driver		= अणु
		.name	= "TB0219",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init tanbac_tb0219_init(व्योम)
अणु
	पूर्णांक retval;

	tb0219_platक्रमm_device = platक्रमm_device_alloc("TB0219", -1);
	अगर (!tb0219_platक्रमm_device)
		वापस -ENOMEM;

	retval = platक्रमm_device_add(tb0219_platक्रमm_device);
	अगर (retval < 0) अणु
		platक्रमm_device_put(tb0219_platक्रमm_device);
		वापस retval;
	पूर्ण

	retval = platक्रमm_driver_रेजिस्टर(&tb0219_device_driver);
	अगर (retval < 0)
		platक्रमm_device_unरेजिस्टर(tb0219_platक्रमm_device);

	वापस retval;
पूर्ण

अटल व्योम __निकास tanbac_tb0219_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&tb0219_device_driver);
	platक्रमm_device_unरेजिस्टर(tb0219_platक्रमm_device);
पूर्ण

module_init(tanbac_tb0219_init);
module_निकास(tanbac_tb0219_निकास);
