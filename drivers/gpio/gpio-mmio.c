<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Generic driver क्रम memory-mapped GPIO controllers.
 *
 * Copyright 2008 MontaVista Software, Inc.
 * Copyright 2008,2010 Anton Vorontsov <cbouaपंचांगailru@gmail.com>
 *
 * ....``.```~~~~````.`.`.`.`.```````'',,,.........`````......`.......
 * ...``                                                         ```````..
 * ..The simplest क्रमm of a GPIO controller that the driver supports is``
 *  `.just a single "data" रेजिस्टर, where GPIO state can be पढ़ो and/or `
 *    `,..written. ,,..``~~~~ .....``.`.`.~~.```.`.........``````.```````
 *        `````````
                                    ___
_/~~|___/~|   . ```~~~~~~       ___/___\___     ,~.`.`.`.`````.~~...,,,,...
__________|~$@~~~        %~    /o*o*o*o*o*o\   .. Implementing such a GPIO .
o        `                     ~~~~\___/~~~~    ` controller in FPGA is ,.`
                                                 `....trivial..'~`.```.```
 *                                                    ```````
 *  .```````~~~~`..`.``.``.
 * .  The driver supports  `...       ,..```.`~~~```````````````....````.``,,
 * .   big-endian notation, just`.  .. A bit more sophisticated controllers ,
 *  . रेजिस्टर the device with -be`. .with a pair of set/clear-bit रेजिस्टरs ,
 *   `.. suffix.  ```~~`````....`.`   . affecting the data रेजिस्टर and the .`
 *     ``.`.``...```                  ```.. output pins are also supported.`
 *                        ^^             `````.`````````.,``~``~``~~``````
 *                                                   .                  ^^
 *   ,..`.`.`...````````````......`.`.`.`.`.`..`.`.`..
 * .. The expectation is that in at least some हालs .    ,-~~~-,
 *  .this will be used with roll-your-own ASIC/FPGA .`     \   /
 *  .logic in Verilog or VHDL. ~~~`````````..`````~~`       \ /
 *  ..````````......```````````                             \o_
 *                                                           |
 *                              ^^                          / \
 *
 *           ...`````~~`.....``.`..........``````.`.``.```........``.
 *            `  8, 16, 32 and 64 bits रेजिस्टरs are supported, and``.
 *            . the number of GPIOs is determined by the width of   ~
 *             .. the रेजिस्टरs. ,............```.`.`..`.`.~~~.`.`.`~
 *               `.......````.```
 */

#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/bug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/log2.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

अटल व्योम bgpio_ग_लिखो8(व्योम __iomem *reg, अचिन्हित दीर्घ data)
अणु
	ग_लिखोb(data, reg);
पूर्ण

अटल अचिन्हित दीर्घ bgpio_पढ़ो8(व्योम __iomem *reg)
अणु
	वापस पढ़ोb(reg);
पूर्ण

अटल व्योम bgpio_ग_लिखो16(व्योम __iomem *reg, अचिन्हित दीर्घ data)
अणु
	ग_लिखोw(data, reg);
पूर्ण

अटल अचिन्हित दीर्घ bgpio_पढ़ो16(व्योम __iomem *reg)
अणु
	वापस पढ़ोw(reg);
पूर्ण

अटल व्योम bgpio_ग_लिखो32(व्योम __iomem *reg, अचिन्हित दीर्घ data)
अणु
	ग_लिखोl(data, reg);
पूर्ण

अटल अचिन्हित दीर्घ bgpio_पढ़ो32(व्योम __iomem *reg)
अणु
	वापस पढ़ोl(reg);
पूर्ण

#अगर BITS_PER_LONG >= 64
अटल व्योम bgpio_ग_लिखो64(व्योम __iomem *reg, अचिन्हित दीर्घ data)
अणु
	ग_लिखोq(data, reg);
पूर्ण

अटल अचिन्हित दीर्घ bgpio_पढ़ो64(व्योम __iomem *reg)
अणु
	वापस पढ़ोq(reg);
पूर्ण
#पूर्ण_अगर /* BITS_PER_LONG >= 64 */

अटल व्योम bgpio_ग_लिखो16be(व्योम __iomem *reg, अचिन्हित दीर्घ data)
अणु
	ioग_लिखो16be(data, reg);
पूर्ण

अटल अचिन्हित दीर्घ bgpio_पढ़ो16be(व्योम __iomem *reg)
अणु
	वापस ioपढ़ो16be(reg);
पूर्ण

अटल व्योम bgpio_ग_लिखो32be(व्योम __iomem *reg, अचिन्हित दीर्घ data)
अणु
	ioग_लिखो32be(data, reg);
पूर्ण

अटल अचिन्हित दीर्घ bgpio_पढ़ो32be(व्योम __iomem *reg)
अणु
	वापस ioपढ़ो32be(reg);
पूर्ण

अटल अचिन्हित दीर्घ bgpio_line2mask(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक line)
अणु
	अगर (gc->be_bits)
		वापस BIT(gc->bgpio_bits - 1 - line);
	वापस BIT(line);
पूर्ण

अटल पूर्णांक bgpio_get_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	अचिन्हित दीर्घ pinmask = bgpio_line2mask(gc, gpio);
	bool dir = !!(gc->bgpio_dir & pinmask);

	अगर (dir)
		वापस !!(gc->पढ़ो_reg(gc->reg_set) & pinmask);
	अन्यथा
		वापस !!(gc->पढ़ो_reg(gc->reg_dat) & pinmask);
पूर्ण

/*
 * This assumes that the bits in the GPIO रेजिस्टर are in native endianness.
 * We only assign the function poपूर्णांकer अगर we have that.
 */
अटल पूर्णांक bgpio_get_set_multiple(काष्ठा gpio_chip *gc, अचिन्हित दीर्घ *mask,
				  अचिन्हित दीर्घ *bits)
अणु
	अचिन्हित दीर्घ get_mask = 0;
	अचिन्हित दीर्घ set_mask = 0;

	/* Make sure we first clear any bits that are zero when we पढ़ो the रेजिस्टर */
	*bits &= ~*mask;

	set_mask = *mask & gc->bgpio_dir;
	get_mask = *mask & ~gc->bgpio_dir;

	अगर (set_mask)
		*bits |= gc->पढ़ो_reg(gc->reg_set) & set_mask;
	अगर (get_mask)
		*bits |= gc->पढ़ो_reg(gc->reg_dat) & get_mask;

	वापस 0;
पूर्ण

अटल पूर्णांक bgpio_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	वापस !!(gc->पढ़ो_reg(gc->reg_dat) & bgpio_line2mask(gc, gpio));
पूर्ण

/*
 * This only works अगर the bits in the GPIO रेजिस्टर are in native endianness.
 */
अटल पूर्णांक bgpio_get_multiple(काष्ठा gpio_chip *gc, अचिन्हित दीर्घ *mask,
			      अचिन्हित दीर्घ *bits)
अणु
	/* Make sure we first clear any bits that are zero when we पढ़ो the रेजिस्टर */
	*bits &= ~*mask;
	*bits |= gc->पढ़ो_reg(gc->reg_dat) & *mask;
	वापस 0;
पूर्ण

/*
 * With big endian mirrored bit order it becomes more tedious.
 */
अटल पूर्णांक bgpio_get_multiple_be(काष्ठा gpio_chip *gc, अचिन्हित दीर्घ *mask,
				 अचिन्हित दीर्घ *bits)
अणु
	अचिन्हित दीर्घ पढ़ोmask = 0;
	अचिन्हित दीर्घ val;
	पूर्णांक bit;

	/* Make sure we first clear any bits that are zero when we पढ़ो the रेजिस्टर */
	*bits &= ~*mask;

	/* Create a mirrored mask */
	क्रम_each_set_bit(bit, mask, gc->ngpio)
		पढ़ोmask |= bgpio_line2mask(gc, bit);

	/* Read the रेजिस्टर */
	val = gc->पढ़ो_reg(gc->reg_dat) & पढ़ोmask;

	/*
	 * Mirror the result पूर्णांकo the "bits" result, this will give line 0
	 * in bit 0 ... line 31 in bit 31 क्रम a 32bit रेजिस्टर.
	 */
	क्रम_each_set_bit(bit, &val, gc->ngpio)
		*bits |= bgpio_line2mask(gc, bit);

	वापस 0;
पूर्ण

अटल व्योम bgpio_set_none(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
पूर्ण

अटल व्योम bgpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	अचिन्हित दीर्घ mask = bgpio_line2mask(gc, gpio);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gc->bgpio_lock, flags);

	अगर (val)
		gc->bgpio_data |= mask;
	अन्यथा
		gc->bgpio_data &= ~mask;

	gc->ग_लिखो_reg(gc->reg_dat, gc->bgpio_data);

	spin_unlock_irqrestore(&gc->bgpio_lock, flags);
पूर्ण

अटल व्योम bgpio_set_with_clear(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio,
				 पूर्णांक val)
अणु
	अचिन्हित दीर्घ mask = bgpio_line2mask(gc, gpio);

	अगर (val)
		gc->ग_लिखो_reg(gc->reg_set, mask);
	अन्यथा
		gc->ग_लिखो_reg(gc->reg_clr, mask);
पूर्ण

अटल व्योम bgpio_set_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	अचिन्हित दीर्घ mask = bgpio_line2mask(gc, gpio);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gc->bgpio_lock, flags);

	अगर (val)
		gc->bgpio_data |= mask;
	अन्यथा
		gc->bgpio_data &= ~mask;

	gc->ग_लिखो_reg(gc->reg_set, gc->bgpio_data);

	spin_unlock_irqrestore(&gc->bgpio_lock, flags);
पूर्ण

अटल व्योम bgpio_multiple_get_masks(काष्ठा gpio_chip *gc,
				     अचिन्हित दीर्घ *mask, अचिन्हित दीर्घ *bits,
				     अचिन्हित दीर्घ *set_mask,
				     अचिन्हित दीर्घ *clear_mask)
अणु
	पूर्णांक i;

	*set_mask = 0;
	*clear_mask = 0;

	क्रम_each_set_bit(i, mask, gc->bgpio_bits) अणु
		अगर (test_bit(i, bits))
			*set_mask |= bgpio_line2mask(gc, i);
		अन्यथा
			*clear_mask |= bgpio_line2mask(gc, i);
	पूर्ण
पूर्ण

अटल व्योम bgpio_set_multiple_single_reg(काष्ठा gpio_chip *gc,
					  अचिन्हित दीर्घ *mask,
					  अचिन्हित दीर्घ *bits,
					  व्योम __iomem *reg)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ set_mask, clear_mask;

	spin_lock_irqsave(&gc->bgpio_lock, flags);

	bgpio_multiple_get_masks(gc, mask, bits, &set_mask, &clear_mask);

	gc->bgpio_data |= set_mask;
	gc->bgpio_data &= ~clear_mask;

	gc->ग_लिखो_reg(reg, gc->bgpio_data);

	spin_unlock_irqrestore(&gc->bgpio_lock, flags);
पूर्ण

अटल व्योम bgpio_set_multiple(काष्ठा gpio_chip *gc, अचिन्हित दीर्घ *mask,
			       अचिन्हित दीर्घ *bits)
अणु
	bgpio_set_multiple_single_reg(gc, mask, bits, gc->reg_dat);
पूर्ण

अटल व्योम bgpio_set_multiple_set(काष्ठा gpio_chip *gc, अचिन्हित दीर्घ *mask,
				   अचिन्हित दीर्घ *bits)
अणु
	bgpio_set_multiple_single_reg(gc, mask, bits, gc->reg_set);
पूर्ण

अटल व्योम bgpio_set_multiple_with_clear(काष्ठा gpio_chip *gc,
					  अचिन्हित दीर्घ *mask,
					  अचिन्हित दीर्घ *bits)
अणु
	अचिन्हित दीर्घ set_mask, clear_mask;

	bgpio_multiple_get_masks(gc, mask, bits, &set_mask, &clear_mask);

	अगर (set_mask)
		gc->ग_लिखो_reg(gc->reg_set, set_mask);
	अगर (clear_mask)
		gc->ग_लिखो_reg(gc->reg_clr, clear_mask);
पूर्ण

अटल पूर्णांक bgpio_simple_dir_in(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक bgpio_dir_out_err(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio,
				पूर्णांक val)
अणु
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bgpio_simple_dir_out(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio,
				पूर्णांक val)
अणु
	gc->set(gc, gpio, val);

	वापस 0;
पूर्ण

अटल पूर्णांक bgpio_dir_in(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gc->bgpio_lock, flags);

	gc->bgpio_dir &= ~bgpio_line2mask(gc, gpio);

	अगर (gc->reg_dir_in)
		gc->ग_लिखो_reg(gc->reg_dir_in, ~gc->bgpio_dir);
	अगर (gc->reg_dir_out)
		gc->ग_लिखो_reg(gc->reg_dir_out, gc->bgpio_dir);

	spin_unlock_irqrestore(&gc->bgpio_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक bgpio_get_dir(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	/* Return 0 अगर output, 1 अगर input */
	अगर (gc->bgpio_dir_unपढ़ोable) अणु
		अगर (gc->bgpio_dir & bgpio_line2mask(gc, gpio))
			वापस GPIO_LINE_सूचीECTION_OUT;
		वापस GPIO_LINE_सूचीECTION_IN;
	पूर्ण

	अगर (gc->reg_dir_out) अणु
		अगर (gc->पढ़ो_reg(gc->reg_dir_out) & bgpio_line2mask(gc, gpio))
			वापस GPIO_LINE_सूचीECTION_OUT;
		वापस GPIO_LINE_सूचीECTION_IN;
	पूर्ण

	अगर (gc->reg_dir_in)
		अगर (!(gc->पढ़ो_reg(gc->reg_dir_in) & bgpio_line2mask(gc, gpio)))
			वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल व्योम bgpio_dir_out(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gc->bgpio_lock, flags);

	gc->bgpio_dir |= bgpio_line2mask(gc, gpio);

	अगर (gc->reg_dir_in)
		gc->ग_लिखो_reg(gc->reg_dir_in, ~gc->bgpio_dir);
	अगर (gc->reg_dir_out)
		gc->ग_लिखो_reg(gc->reg_dir_out, gc->bgpio_dir);

	spin_unlock_irqrestore(&gc->bgpio_lock, flags);
पूर्ण

अटल पूर्णांक bgpio_dir_out_dir_first(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio,
				   पूर्णांक val)
अणु
	bgpio_dir_out(gc, gpio, val);
	gc->set(gc, gpio, val);
	वापस 0;
पूर्ण

अटल पूर्णांक bgpio_dir_out_val_first(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio,
				   पूर्णांक val)
अणु
	gc->set(gc, gpio, val);
	bgpio_dir_out(gc, gpio, val);
	वापस 0;
पूर्ण

अटल पूर्णांक bgpio_setup_accessors(काष्ठा device *dev,
				 काष्ठा gpio_chip *gc,
				 bool byte_be)
अणु

	चयन (gc->bgpio_bits) अणु
	हाल 8:
		gc->पढ़ो_reg	= bgpio_पढ़ो8;
		gc->ग_लिखो_reg	= bgpio_ग_लिखो8;
		अवरोध;
	हाल 16:
		अगर (byte_be) अणु
			gc->पढ़ो_reg	= bgpio_पढ़ो16be;
			gc->ग_लिखो_reg	= bgpio_ग_लिखो16be;
		पूर्ण अन्यथा अणु
			gc->पढ़ो_reg	= bgpio_पढ़ो16;
			gc->ग_लिखो_reg	= bgpio_ग_लिखो16;
		पूर्ण
		अवरोध;
	हाल 32:
		अगर (byte_be) अणु
			gc->पढ़ो_reg	= bgpio_पढ़ो32be;
			gc->ग_लिखो_reg	= bgpio_ग_लिखो32be;
		पूर्ण अन्यथा अणु
			gc->पढ़ो_reg	= bgpio_पढ़ो32;
			gc->ग_लिखो_reg	= bgpio_ग_लिखो32;
		पूर्ण
		अवरोध;
#अगर BITS_PER_LONG >= 64
	हाल 64:
		अगर (byte_be) अणु
			dev_err(dev,
				"64 bit big endian byte order unsupported\n");
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			gc->पढ़ो_reg	= bgpio_पढ़ो64;
			gc->ग_लिखो_reg	= bgpio_ग_लिखो64;
		पूर्ण
		अवरोध;
#पूर्ण_अगर /* BITS_PER_LONG >= 64 */
	शेष:
		dev_err(dev, "unsupported data width %u bits\n", gc->bgpio_bits);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Create the device and allocate the resources.  For setting GPIO's there are
 * three supported configurations:
 *
 *	- single input/output रेजिस्टर resource (named "dat").
 *	- set/clear pair (named "set" and "clr").
 *	- single output रेजिस्टर resource and single input resource ("set" and
 *	dat").
 *
 * For the single output रेजिस्टर, this drives a 1 by setting a bit and a zero
 * by clearing a bit.  For the set clr pair, this drives a 1 by setting a bit
 * in the set रेजिस्टर and clears it by setting a bit in the clear रेजिस्टर.
 * The configuration is detected by which resources are present.
 *
 * For setting the GPIO direction, there are three supported configurations:
 *
 *	- simple bidirection GPIO that requires no configuration.
 *	- an output direction रेजिस्टर (named "dirout") where a 1 bit
 *	indicates the GPIO is an output.
 *	- an input direction रेजिस्टर (named "dirin") where a 1 bit indicates
 *	the GPIO is an input.
 */
अटल पूर्णांक bgpio_setup_io(काष्ठा gpio_chip *gc,
			  व्योम __iomem *dat,
			  व्योम __iomem *set,
			  व्योम __iomem *clr,
			  अचिन्हित दीर्घ flags)
अणु

	gc->reg_dat = dat;
	अगर (!gc->reg_dat)
		वापस -EINVAL;

	अगर (set && clr) अणु
		gc->reg_set = set;
		gc->reg_clr = clr;
		gc->set = bgpio_set_with_clear;
		gc->set_multiple = bgpio_set_multiple_with_clear;
	पूर्ण अन्यथा अगर (set && !clr) अणु
		gc->reg_set = set;
		gc->set = bgpio_set_set;
		gc->set_multiple = bgpio_set_multiple_set;
	पूर्ण अन्यथा अगर (flags & BGPIOF_NO_OUTPUT) अणु
		gc->set = bgpio_set_none;
		gc->set_multiple = शून्य;
	पूर्ण अन्यथा अणु
		gc->set = bgpio_set;
		gc->set_multiple = bgpio_set_multiple;
	पूर्ण

	अगर (!(flags & BGPIOF_UNREADABLE_REG_SET) &&
	    (flags & BGPIOF_READ_OUTPUT_REG_SET)) अणु
		gc->get = bgpio_get_set;
		अगर (!gc->be_bits)
			gc->get_multiple = bgpio_get_set_multiple;
		/*
		 * We deliberately aव्योम assigning the ->get_multiple() call
		 * क्रम big endian mirrored रेजिस्टरs which are ALSO reflecting
		 * their value in the set रेजिस्टर when used as output. It is
		 * simply too much complनिकासy, let the GPIO core fall back to
		 * पढ़ोing each line inभागidually in that fringe हाल.
		 */
	पूर्ण अन्यथा अणु
		gc->get = bgpio_get;
		अगर (gc->be_bits)
			gc->get_multiple = bgpio_get_multiple_be;
		अन्यथा
			gc->get_multiple = bgpio_get_multiple;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bgpio_setup_direction(काष्ठा gpio_chip *gc,
				 व्योम __iomem *dirout,
				 व्योम __iomem *dirin,
				 अचिन्हित दीर्घ flags)
अणु
	अगर (dirout || dirin) अणु
		gc->reg_dir_out = dirout;
		gc->reg_dir_in = dirin;
		अगर (flags & BGPIOF_NO_SET_ON_INPUT)
			gc->direction_output = bgpio_dir_out_dir_first;
		अन्यथा
			gc->direction_output = bgpio_dir_out_val_first;
		gc->direction_input = bgpio_dir_in;
		gc->get_direction = bgpio_get_dir;
	पूर्ण अन्यथा अणु
		अगर (flags & BGPIOF_NO_OUTPUT)
			gc->direction_output = bgpio_dir_out_err;
		अन्यथा
			gc->direction_output = bgpio_simple_dir_out;
		gc->direction_input = bgpio_simple_dir_in;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bgpio_request(काष्ठा gpio_chip *chip, अचिन्हित gpio_pin)
अणु
	अगर (gpio_pin < chip->ngpio)
		वापस 0;

	वापस -EINVAL;
पूर्ण

/**
 * bgpio_init() - Initialize generic GPIO accessor functions
 * @gc: the GPIO chip to set up
 * @dev: the parent device of the new GPIO chip (compulsory)
 * @sz: the size (width) of the MMIO रेजिस्टरs in bytes, typically 1, 2 or 4
 * @dat: MMIO address क्रम the रेजिस्टर to READ the value of the GPIO lines, it
 *	is expected that a 1 in the corresponding bit in this रेजिस्टर means the
 *	line is निश्चितed
 * @set: MMIO address क्रम the रेजिस्टर to SET the value of the GPIO lines, it is
 *	expected that we ग_लिखो the line with 1 in this रेजिस्टर to drive the GPIO line
 *	high.
 * @clr: MMIO address क्रम the रेजिस्टर to CLEAR the value of the GPIO lines, it is
 *	expected that we ग_लिखो the line with 1 in this रेजिस्टर to drive the GPIO line
 *	low. It is allowed to leave this address as शून्य, in that हाल the SET रेजिस्टर
 *	will be assumed to also clear the GPIO lines, by actively writing the line
 *	with 0.
 * @dirout: MMIO address क्रम the रेजिस्टर to set the line as OUTPUT. It is assumed
 *	that setting a line to 1 in this रेजिस्टर will turn that line पूर्णांकo an
 *	output line. Conversely, setting the line to 0 will turn that line पूर्णांकo
 *	an input.
 * @dirin: MMIO address क्रम the रेजिस्टर to set this line as INPUT. It is assumed
 *	that setting a line to 1 in this रेजिस्टर will turn that line पूर्णांकo an
 *	input line. Conversely, setting the line to 0 will turn that line पूर्णांकo
 *	an output.
 * @flags: Dअगरferent flags that will affect the behaviour of the device, such as
 *	endianness etc.
 */
पूर्णांक bgpio_init(काष्ठा gpio_chip *gc, काष्ठा device *dev,
	       अचिन्हित दीर्घ sz, व्योम __iomem *dat, व्योम __iomem *set,
	       व्योम __iomem *clr, व्योम __iomem *dirout, व्योम __iomem *dirin,
	       अचिन्हित दीर्घ flags)
अणु
	पूर्णांक ret;

	अगर (!is_घातer_of_2(sz))
		वापस -EINVAL;

	gc->bgpio_bits = sz * 8;
	अगर (gc->bgpio_bits > BITS_PER_LONG)
		वापस -EINVAL;

	spin_lock_init(&gc->bgpio_lock);
	gc->parent = dev;
	gc->label = dev_name(dev);
	gc->base = -1;
	gc->ngpio = gc->bgpio_bits;
	gc->request = bgpio_request;
	gc->be_bits = !!(flags & BGPIOF_BIG_ENDIAN);

	ret = bgpio_setup_io(gc, dat, set, clr, flags);
	अगर (ret)
		वापस ret;

	ret = bgpio_setup_accessors(dev, gc, flags & BGPIOF_BIG_ENDIAN_BYTE_ORDER);
	अगर (ret)
		वापस ret;

	ret = bgpio_setup_direction(gc, dirout, dirin, flags);
	अगर (ret)
		वापस ret;

	gc->bgpio_data = gc->पढ़ो_reg(gc->reg_dat);
	अगर (gc->set == bgpio_set_set &&
			!(flags & BGPIOF_UNREADABLE_REG_SET))
		gc->bgpio_data = gc->पढ़ो_reg(gc->reg_set);

	अगर (flags & BGPIOF_UNREADABLE_REG_सूची)
		gc->bgpio_dir_unपढ़ोable = true;

	/*
	 * Inspect hardware to find initial direction setting.
	 */
	अगर ((gc->reg_dir_out || gc->reg_dir_in) &&
	    !(flags & BGPIOF_UNREADABLE_REG_सूची)) अणु
		अगर (gc->reg_dir_out)
			gc->bgpio_dir = gc->पढ़ो_reg(gc->reg_dir_out);
		अन्यथा अगर (gc->reg_dir_in)
			gc->bgpio_dir = ~gc->पढ़ो_reg(gc->reg_dir_in);
		/*
		 * If we have two direction रेजिस्टरs, synchronise
		 * input setting to output setting, the library
		 * can not handle a line being input and output at
		 * the same समय.
		 */
		अगर (gc->reg_dir_out && gc->reg_dir_in)
			gc->ग_लिखो_reg(gc->reg_dir_in, ~gc->bgpio_dir);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(bgpio_init);

#अगर IS_ENABLED(CONFIG_GPIO_GENERIC_PLATFORM)

अटल व्योम __iomem *bgpio_map(काष्ठा platक्रमm_device *pdev,
			       स्थिर अक्षर *name,
			       resource_माप_प्रकार sane_sz)
अणु
	काष्ठा resource *r;
	resource_माप_प्रकार sz;

	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, name);
	अगर (!r)
		वापस शून्य;

	sz = resource_size(r);
	अगर (sz != sane_sz)
		वापस IOMEM_ERR_PTR(-EINVAL);

	वापस devm_ioremap_resource(&pdev->dev, r);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id bgpio_of_match[] = अणु
	अणु .compatible = "brcm,bcm6345-gpio" पूर्ण,
	अणु .compatible = "wd,mbl-gpio" पूर्ण,
	अणु .compatible = "ni,169445-nand-gpio" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bgpio_of_match);

अटल काष्ठा bgpio_pdata *bgpio_parse_dt(काष्ठा platक्रमm_device *pdev,
					  अचिन्हित दीर्घ *flags)
अणु
	काष्ठा bgpio_pdata *pdata;

	अगर (!of_match_device(bgpio_of_match, &pdev->dev))
		वापस शून्य;

	pdata = devm_kzalloc(&pdev->dev, माप(काष्ठा bgpio_pdata),
			     GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	pdata->base = -1;

	अगर (of_device_is_big_endian(pdev->dev.of_node))
		*flags |= BGPIOF_BIG_ENDIAN_BYTE_ORDER;

	अगर (of_property_पढ़ो_bool(pdev->dev.of_node, "no-output"))
		*flags |= BGPIOF_NO_OUTPUT;

	वापस pdata;
पूर्ण
#अन्यथा
अटल काष्ठा bgpio_pdata *bgpio_parse_dt(काष्ठा platक्रमm_device *pdev,
					  अचिन्हित दीर्घ *flags)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

अटल पूर्णांक bgpio_pdev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *r;
	व्योम __iomem *dat;
	व्योम __iomem *set;
	व्योम __iomem *clr;
	व्योम __iomem *dirout;
	व्योम __iomem *dirin;
	अचिन्हित दीर्घ sz;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक err;
	काष्ठा gpio_chip *gc;
	काष्ठा bgpio_pdata *pdata;

	pdata = bgpio_parse_dt(pdev, &flags);
	अगर (IS_ERR(pdata))
		वापस PTR_ERR(pdata);

	अगर (!pdata) अणु
		pdata = dev_get_platdata(dev);
		flags = pdev->id_entry->driver_data;
	पूर्ण

	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "dat");
	अगर (!r)
		वापस -EINVAL;

	sz = resource_size(r);

	dat = bgpio_map(pdev, "dat", sz);
	अगर (IS_ERR(dat))
		वापस PTR_ERR(dat);

	set = bgpio_map(pdev, "set", sz);
	अगर (IS_ERR(set))
		वापस PTR_ERR(set);

	clr = bgpio_map(pdev, "clr", sz);
	अगर (IS_ERR(clr))
		वापस PTR_ERR(clr);

	dirout = bgpio_map(pdev, "dirout", sz);
	अगर (IS_ERR(dirout))
		वापस PTR_ERR(dirout);

	dirin = bgpio_map(pdev, "dirin", sz);
	अगर (IS_ERR(dirin))
		वापस PTR_ERR(dirin);

	gc = devm_kzalloc(&pdev->dev, माप(*gc), GFP_KERNEL);
	अगर (!gc)
		वापस -ENOMEM;

	err = bgpio_init(gc, dev, sz, dat, set, clr, dirout, dirin, flags);
	अगर (err)
		वापस err;

	अगर (pdata) अणु
		अगर (pdata->label)
			gc->label = pdata->label;
		gc->base = pdata->base;
		अगर (pdata->ngpio > 0)
			gc->ngpio = pdata->ngpio;
	पूर्ण

	platक्रमm_set_drvdata(pdev, gc);

	वापस devm_gpiochip_add_data(&pdev->dev, gc, शून्य);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id bgpio_id_table[] = अणु
	अणु
		.name		= "basic-mmio-gpio",
		.driver_data	= 0,
	पूर्ण, अणु
		.name		= "basic-mmio-gpio-be",
		.driver_data	= BGPIOF_BIG_ENDIAN,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, bgpio_id_table);

अटल काष्ठा platक्रमm_driver bgpio_driver = अणु
	.driver = अणु
		.name = "basic-mmio-gpio",
		.of_match_table = of_match_ptr(bgpio_of_match),
	पूर्ण,
	.id_table = bgpio_id_table,
	.probe = bgpio_pdev_probe,
पूर्ण;

module_platक्रमm_driver(bgpio_driver);

#पूर्ण_अगर /* CONFIG_GPIO_GENERIC_PLATFORM */

MODULE_DESCRIPTION("Driver for basic memory-mapped GPIO controllers");
MODULE_AUTHOR("Anton Vorontsov <cbouatmailru@gmail.com>");
MODULE_LICENSE("GPL");
