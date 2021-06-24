<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * GPIO Testing Device Driver
 *
 * Copyright (C) 2014  Kamlakant Patel <kamlakant.patel@broadcom.com>
 * Copyright (C) 2015-2016  Bamvor Jian Zhang <bamv2005@gmail.com>
 * Copyright (C) 2017 Bartosz Golaszewski <brgl@bgdev.pl>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/debugfs.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irq_sim.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>
#समावेश <linux/string_helpers.h>
#समावेश <linux/uaccess.h>

#समावेश "gpiolib.h"

#घोषणा GPIO_MOCKUP_MAX_GC	10
/*
 * We're storing two values per chip: the GPIO base and the number
 * of GPIO lines.
 */
#घोषणा GPIO_MOCKUP_MAX_RANGES	(GPIO_MOCKUP_MAX_GC * 2)
/* Maximum of four properties + the sentinel. */
#घोषणा GPIO_MOCKUP_MAX_PROP	5

/*
 * काष्ठा gpio_pin_status - काष्ठाure describing a GPIO status
 * @dir:       Configures direction of gpio as "in" or "out"
 * @value:     Configures status of the gpio as 0(low) or 1(high)
 */
काष्ठा gpio_mockup_line_status अणु
	पूर्णांक dir;
	पूर्णांक value;
	पूर्णांक pull;
पूर्ण;

काष्ठा gpio_mockup_chip अणु
	काष्ठा gpio_chip gc;
	काष्ठा gpio_mockup_line_status *lines;
	काष्ठा irq_करोमुख्य *irq_sim_करोमुख्य;
	काष्ठा dentry *dbg_dir;
	काष्ठा mutex lock;
पूर्ण;

काष्ठा gpio_mockup_dbgfs_निजी अणु
	काष्ठा gpio_mockup_chip *chip;
	काष्ठा gpio_desc *desc;
	अचिन्हित पूर्णांक offset;
पूर्ण;

अटल पूर्णांक gpio_mockup_ranges[GPIO_MOCKUP_MAX_RANGES];
अटल पूर्णांक gpio_mockup_num_ranges;
module_param_array(gpio_mockup_ranges, पूर्णांक, &gpio_mockup_num_ranges, 0400);

अटल bool gpio_mockup_named_lines;
module_param_named(gpio_mockup_named_lines,
		   gpio_mockup_named_lines, bool, 0400);

अटल काष्ठा dentry *gpio_mockup_dbg_dir;

अटल पूर्णांक gpio_mockup_range_base(अचिन्हित पूर्णांक index)
अणु
	वापस gpio_mockup_ranges[index * 2];
पूर्ण

अटल पूर्णांक gpio_mockup_range_ngpio(अचिन्हित पूर्णांक index)
अणु
	वापस gpio_mockup_ranges[index * 2 + 1];
पूर्ण

अटल पूर्णांक __gpio_mockup_get(काष्ठा gpio_mockup_chip *chip,
			     अचिन्हित पूर्णांक offset)
अणु
	वापस chip->lines[offset].value;
पूर्ण

अटल पूर्णांक gpio_mockup_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gpio_mockup_chip *chip = gpiochip_get_data(gc);
	पूर्णांक val;

	mutex_lock(&chip->lock);
	val = __gpio_mockup_get(chip, offset);
	mutex_unlock(&chip->lock);

	वापस val;
पूर्ण

अटल पूर्णांक gpio_mockup_get_multiple(काष्ठा gpio_chip *gc,
				    अचिन्हित दीर्घ *mask, अचिन्हित दीर्घ *bits)
अणु
	काष्ठा gpio_mockup_chip *chip = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक bit, val;

	mutex_lock(&chip->lock);
	क्रम_each_set_bit(bit, mask, gc->ngpio) अणु
		val = __gpio_mockup_get(chip, bit);
		__assign_bit(bit, bits, val);
	पूर्ण
	mutex_unlock(&chip->lock);

	वापस 0;
पूर्ण

अटल व्योम __gpio_mockup_set(काष्ठा gpio_mockup_chip *chip,
			      अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	chip->lines[offset].value = !!value;
पूर्ण

अटल व्योम gpio_mockup_set(काष्ठा gpio_chip *gc,
			   अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा gpio_mockup_chip *chip = gpiochip_get_data(gc);

	mutex_lock(&chip->lock);
	__gpio_mockup_set(chip, offset, value);
	mutex_unlock(&chip->lock);
पूर्ण

अटल व्योम gpio_mockup_set_multiple(काष्ठा gpio_chip *gc,
				     अचिन्हित दीर्घ *mask, अचिन्हित दीर्घ *bits)
अणु
	काष्ठा gpio_mockup_chip *chip = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक bit;

	mutex_lock(&chip->lock);
	क्रम_each_set_bit(bit, mask, gc->ngpio)
		__gpio_mockup_set(chip, bit, test_bit(bit, bits));
	mutex_unlock(&chip->lock);
पूर्ण

अटल पूर्णांक gpio_mockup_apply_pull(काष्ठा gpio_mockup_chip *chip,
				  अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	पूर्णांक curr, irq, irq_type, ret = 0;
	काष्ठा gpio_desc *desc;
	काष्ठा gpio_chip *gc;

	gc = &chip->gc;
	desc = &gc->gpiodev->descs[offset];

	mutex_lock(&chip->lock);

	अगर (test_bit(FLAG_REQUESTED, &desc->flags) &&
	    !test_bit(FLAG_IS_OUT, &desc->flags)) अणु
		curr = __gpio_mockup_get(chip, offset);
		अगर (curr == value)
			जाओ out;

		irq = irq_find_mapping(chip->irq_sim_करोमुख्य, offset);
		अगर (!irq)
			/*
			 * This is fine - it just means, nobody is listening
			 * क्रम पूर्णांकerrupts on this line, otherwise
			 * irq_create_mapping() would have been called from
			 * the to_irq() callback.
			 */
			जाओ set_value;

		irq_type = irq_get_trigger_type(irq);

		अगर ((value == 1 && (irq_type & IRQ_TYPE_EDGE_RISING)) ||
		    (value == 0 && (irq_type & IRQ_TYPE_EDGE_FALLING))) अणु
			ret = irq_set_irqchip_state(irq, IRQCHIP_STATE_PENDING,
						    true);
			अगर (ret)
				जाओ out;
		पूर्ण
	पूर्ण

set_value:
	/* Change the value unless we're actively driving the line. */
	अगर (!test_bit(FLAG_REQUESTED, &desc->flags) ||
	    !test_bit(FLAG_IS_OUT, &desc->flags))
		__gpio_mockup_set(chip, offset, value);

out:
	chip->lines[offset].pull = value;
	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक gpio_mockup_set_config(काष्ठा gpio_chip *gc,
				  अचिन्हित पूर्णांक offset, अचिन्हित दीर्घ config)
अणु
	काष्ठा gpio_mockup_chip *chip = gpiochip_get_data(gc);

	चयन (pinconf_to_config_param(config)) अणु
	हाल PIN_CONFIG_BIAS_PULL_UP:
		वापस gpio_mockup_apply_pull(chip, offset, 1);
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		वापस gpio_mockup_apply_pull(chip, offset, 0);
	शेष:
		अवरोध;
	पूर्ण
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक gpio_mockup_dirout(काष्ठा gpio_chip *gc,
			      अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा gpio_mockup_chip *chip = gpiochip_get_data(gc);

	mutex_lock(&chip->lock);
	chip->lines[offset].dir = GPIO_LINE_सूचीECTION_OUT;
	__gpio_mockup_set(chip, offset, value);
	mutex_unlock(&chip->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_mockup_dirin(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gpio_mockup_chip *chip = gpiochip_get_data(gc);

	mutex_lock(&chip->lock);
	chip->lines[offset].dir = GPIO_LINE_सूचीECTION_IN;
	mutex_unlock(&chip->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_mockup_get_direction(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gpio_mockup_chip *chip = gpiochip_get_data(gc);
	पूर्णांक direction;

	mutex_lock(&chip->lock);
	direction = chip->lines[offset].dir;
	mutex_unlock(&chip->lock);

	वापस direction;
पूर्ण

अटल पूर्णांक gpio_mockup_to_irq(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gpio_mockup_chip *chip = gpiochip_get_data(gc);

	वापस irq_create_mapping(chip->irq_sim_करोमुख्य, offset);
पूर्ण

अटल व्योम gpio_mockup_मुक्त(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gpio_mockup_chip *chip = gpiochip_get_data(gc);

	__gpio_mockup_set(chip, offset, chip->lines[offset].pull);
पूर्ण

अटल sमाप_प्रकार gpio_mockup_debugfs_पढ़ो(काष्ठा file *file,
					अक्षर __user *usr_buf,
					माप_प्रकार size, loff_t *ppos)
अणु
	काष्ठा gpio_mockup_dbgfs_निजी *priv;
	काष्ठा gpio_mockup_chip *chip;
	काष्ठा seq_file *sfile;
	काष्ठा gpio_chip *gc;
	पूर्णांक val, cnt;
	अक्षर buf[3];

	अगर (*ppos != 0)
		वापस 0;

	sfile = file->निजी_data;
	priv = sfile->निजी;
	chip = priv->chip;
	gc = &chip->gc;

	val = gpio_mockup_get(gc, priv->offset);
	cnt = snम_लिखो(buf, माप(buf), "%d\n", val);

	वापस simple_पढ़ो_from_buffer(usr_buf, size, ppos, buf, cnt);
पूर्ण

अटल sमाप_प्रकार gpio_mockup_debugfs_ग_लिखो(काष्ठा file *file,
					 स्थिर अक्षर __user *usr_buf,
					 माप_प्रकार size, loff_t *ppos)
अणु
	काष्ठा gpio_mockup_dbgfs_निजी *priv;
	पूर्णांक rv, val;
	काष्ठा seq_file *sfile;

	अगर (*ppos != 0)
		वापस -EINVAL;

	rv = kstrtoपूर्णांक_from_user(usr_buf, size, 0, &val);
	अगर (rv)
		वापस rv;
	अगर (val != 0 && val != 1)
		वापस -EINVAL;

	sfile = file->निजी_data;
	priv = sfile->निजी;
	rv = gpio_mockup_apply_pull(priv->chip, priv->offset, val);
	अगर (rv)
		वापस rv;

	वापस size;
पूर्ण

अटल पूर्णांक gpio_mockup_debugfs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, शून्य, inode->i_निजी);
पूर्ण

/*
 * Each mockup chip is represented by a directory named after the chip's device
 * name under /sys/kernel/debug/gpio-mockup/. Each line is represented by
 * a file using the line's offset as the name under the chip's directory.
 *
 * Reading from the line's file yields the current *value*, writing to the
 * line's file changes the current *pull*. Default pull क्रम mockup lines is
 * करोwn.
 *
 * Examples:
 * - when a line pulled करोwn is requested in output mode and driven high, its
 *   value will वापस to 0 once it's released
 * - when the line is requested in output mode and driven high, writing 0 to
 *   the corresponding debugfs file will change the pull to करोwn but the
 *   reported value will still be 1 until the line is released
 * - line requested in input mode always reports the same value as its pull
 *   configuration
 * - when the line is requested in input mode and monitored क्रम events, writing
 *   the same value to the debugfs file will be a noop, जबतक writing the
 *   opposite value will generate a dummy पूर्णांकerrupt with an appropriate edge
 */
अटल स्थिर काष्ठा file_operations gpio_mockup_debugfs_ops = अणु
	.owner = THIS_MODULE,
	.खोलो = gpio_mockup_debugfs_खोलो,
	.पढ़ो = gpio_mockup_debugfs_पढ़ो,
	.ग_लिखो = gpio_mockup_debugfs_ग_लिखो,
	.llseek = no_llseek,
	.release = single_release,
पूर्ण;

अटल व्योम gpio_mockup_debugfs_setup(काष्ठा device *dev,
				      काष्ठा gpio_mockup_chip *chip)
अणु
	काष्ठा gpio_mockup_dbgfs_निजी *priv;
	काष्ठा gpio_chip *gc;
	स्थिर अक्षर *devname;
	अक्षर *name;
	पूर्णांक i;

	gc = &chip->gc;
	devname = dev_name(&gc->gpiodev->dev);

	chip->dbg_dir = debugfs_create_dir(devname, gpio_mockup_dbg_dir);

	क्रम (i = 0; i < gc->ngpio; i++) अणु
		name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%d", i);
		अगर (!name)
			वापस;

		priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
		अगर (!priv)
			वापस;

		priv->chip = chip;
		priv->offset = i;
		priv->desc = &gc->gpiodev->descs[i];

		debugfs_create_file(name, 0200, chip->dbg_dir, priv,
				    &gpio_mockup_debugfs_ops);
	पूर्ण
पूर्ण

अटल व्योम gpio_mockup_dispose_mappings(व्योम *data)
अणु
	काष्ठा gpio_mockup_chip *chip = data;
	काष्ठा gpio_chip *gc = &chip->gc;
	पूर्णांक i, irq;

	क्रम (i = 0; i < gc->ngpio; i++) अणु
		irq = irq_find_mapping(chip->irq_sim_करोमुख्य, i);
		अगर (irq)
			irq_dispose_mapping(irq);
	पूर्ण
पूर्ण

अटल पूर्णांक gpio_mockup_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_mockup_chip *chip;
	काष्ठा gpio_chip *gc;
	काष्ठा device *dev;
	स्थिर अक्षर *name;
	पूर्णांक rv, base, i;
	u16 ngpio;

	dev = &pdev->dev;

	rv = device_property_पढ़ो_u32(dev, "gpio-base", &base);
	अगर (rv)
		base = -1;

	rv = device_property_पढ़ो_u16(dev, "nr-gpios", &ngpio);
	अगर (rv)
		वापस rv;

	rv = device_property_पढ़ो_string(dev, "chip-label", &name);
	अगर (rv)
		name = dev_name(dev);

	chip = devm_kzalloc(dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	mutex_init(&chip->lock);

	gc = &chip->gc;
	gc->base = base;
	gc->ngpio = ngpio;
	gc->label = name;
	gc->owner = THIS_MODULE;
	gc->parent = dev;
	gc->get = gpio_mockup_get;
	gc->set = gpio_mockup_set;
	gc->get_multiple = gpio_mockup_get_multiple;
	gc->set_multiple = gpio_mockup_set_multiple;
	gc->direction_output = gpio_mockup_dirout;
	gc->direction_input = gpio_mockup_dirin;
	gc->get_direction = gpio_mockup_get_direction;
	gc->set_config = gpio_mockup_set_config;
	gc->to_irq = gpio_mockup_to_irq;
	gc->मुक्त = gpio_mockup_मुक्त;

	chip->lines = devm_kसुस्मृति(dev, gc->ngpio,
				   माप(*chip->lines), GFP_KERNEL);
	अगर (!chip->lines)
		वापस -ENOMEM;

	क्रम (i = 0; i < gc->ngpio; i++)
		chip->lines[i].dir = GPIO_LINE_सूचीECTION_IN;

	chip->irq_sim_करोमुख्य = devm_irq_करोमुख्य_create_sim(dev, शून्य,
							  gc->ngpio);
	अगर (IS_ERR(chip->irq_sim_करोमुख्य))
		वापस PTR_ERR(chip->irq_sim_करोमुख्य);

	rv = devm_add_action_or_reset(dev, gpio_mockup_dispose_mappings, chip);
	अगर (rv)
		वापस rv;

	rv = devm_gpiochip_add_data(dev, &chip->gc, chip);
	अगर (rv)
		वापस rv;

	gpio_mockup_debugfs_setup(dev, chip);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id gpio_mockup_of_match[] = अणु
	अणु .compatible = "gpio-mockup", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, gpio_mockup_of_match);

अटल काष्ठा platक्रमm_driver gpio_mockup_driver = अणु
	.driver = अणु
		.name = "gpio-mockup",
		.of_match_table = gpio_mockup_of_match,
	पूर्ण,
	.probe = gpio_mockup_probe,
पूर्ण;

अटल काष्ठा platक्रमm_device *gpio_mockup_pdevs[GPIO_MOCKUP_MAX_GC];

अटल व्योम gpio_mockup_unरेजिस्टर_pdevs(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < GPIO_MOCKUP_MAX_GC; i++)
		platक्रमm_device_unरेजिस्टर(gpio_mockup_pdevs[i]);
पूर्ण

अटल __init अक्षर **gpio_mockup_make_line_names(स्थिर अक्षर *label,
						 अचिन्हित पूर्णांक num_lines)
अणु
	अचिन्हित पूर्णांक i;
	अक्षर **names;

	names = kसुस्मृति(num_lines + 1, माप(अक्षर *), GFP_KERNEL);
	अगर (!names)
		वापस शून्य;

	क्रम (i = 0; i < num_lines; i++) अणु
		names[i] = kaप्र_लिखो(GFP_KERNEL, "%s-%u", label, i);
		अगर (!names[i]) अणु
			kमुक्त_strarray(names, i);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस names;
पूर्ण

अटल पूर्णांक __init gpio_mockup_रेजिस्टर_chip(पूर्णांक idx)
अणु
	काष्ठा property_entry properties[GPIO_MOCKUP_MAX_PROP];
	काष्ठा platक्रमm_device_info pdevinfo;
	काष्ठा platक्रमm_device *pdev;
	अक्षर **line_names = शून्य;
	अक्षर chip_label[32];
	पूर्णांक prop = 0, base;
	u16 ngpio;

	स_रखो(properties, 0, माप(properties));
	स_रखो(&pdevinfo, 0, माप(pdevinfo));

	snम_लिखो(chip_label, माप(chip_label), "gpio-mockup-%c", idx + 'A');
	properties[prop++] = PROPERTY_ENTRY_STRING("chip-label", chip_label);

	base = gpio_mockup_range_base(idx);
	अगर (base >= 0)
		properties[prop++] = PROPERTY_ENTRY_U32("gpio-base", base);

	ngpio = base < 0 ? gpio_mockup_range_ngpio(idx)
			 : gpio_mockup_range_ngpio(idx) - base;
	properties[prop++] = PROPERTY_ENTRY_U16("nr-gpios", ngpio);

	अगर (gpio_mockup_named_lines) अणु
		line_names = gpio_mockup_make_line_names(chip_label, ngpio);
		अगर (!line_names)
			वापस -ENOMEM;

		properties[prop++] = PROPERTY_ENTRY_STRING_ARRAY_LEN(
					"gpio-line-names", line_names, ngpio);
	पूर्ण

	pdevinfo.name = "gpio-mockup";
	pdevinfo.id = idx;
	pdevinfo.properties = properties;

	pdev = platक्रमm_device_रेजिस्टर_full(&pdevinfo);
	kमुक्त_strarray(line_names, ngpio);
	अगर (IS_ERR(pdev)) अणु
		pr_err("error registering device");
		वापस PTR_ERR(pdev);
	पूर्ण

	gpio_mockup_pdevs[idx] = pdev;

	वापस 0;
पूर्ण

अटल पूर्णांक __init gpio_mockup_init(व्योम)
अणु
	पूर्णांक i, num_chips, err;

	अगर ((gpio_mockup_num_ranges % 2) ||
	    (gpio_mockup_num_ranges > GPIO_MOCKUP_MAX_RANGES))
		वापस -EINVAL;

	/* Each chip is described by two values. */
	num_chips = gpio_mockup_num_ranges / 2;

	/*
	 * The second value in the <base GPIO - number of GPIOS> pair must
	 * always be greater than 0.
	 */
	क्रम (i = 0; i < num_chips; i++) अणु
		अगर (gpio_mockup_range_ngpio(i) < 0)
			वापस -EINVAL;
	पूर्ण

	gpio_mockup_dbg_dir = debugfs_create_dir("gpio-mockup", शून्य);

	err = platक्रमm_driver_रेजिस्टर(&gpio_mockup_driver);
	अगर (err) अणु
		pr_err("error registering platform driver\n");
		debugfs_हटाओ_recursive(gpio_mockup_dbg_dir);
		वापस err;
	पूर्ण

	क्रम (i = 0; i < num_chips; i++) अणु
		err = gpio_mockup_रेजिस्टर_chip(i);
		अगर (err) अणु
			platक्रमm_driver_unरेजिस्टर(&gpio_mockup_driver);
			gpio_mockup_unरेजिस्टर_pdevs();
			debugfs_हटाओ_recursive(gpio_mockup_dbg_dir);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास gpio_mockup_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(gpio_mockup_dbg_dir);
	platक्रमm_driver_unरेजिस्टर(&gpio_mockup_driver);
	gpio_mockup_unरेजिस्टर_pdevs();
पूर्ण

module_init(gpio_mockup_init);
module_निकास(gpio_mockup_निकास);

MODULE_AUTHOR("Kamlakant Patel <kamlakant.patel@broadcom.com>");
MODULE_AUTHOR("Bamvor Jian Zhang <bamv2005@gmail.com>");
MODULE_AUTHOR("Bartosz Golaszewski <brgl@bgdev.pl>");
MODULE_DESCRIPTION("GPIO Testing driver");
MODULE_LICENSE("GPL v2");
