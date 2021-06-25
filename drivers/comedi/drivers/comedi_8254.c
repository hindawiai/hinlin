<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi_8254.c
 * Generic 8254 समयr/counter support
 * Copyright (C) 2014 H Hartley Sweeten <hsweeten@visionengravers.com>
 *
 * Based on 8253.h and various subdevice implementations in comedi drivers.
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Module: comedi_8254
 * Description: Generic 8254 समयr/counter support
 * Author: H Hartley Sweeten <hsweeten@visionengravers.com>
 * Updated: Thu Jan 8 16:45:45 MST 2015
 * Status: works
 *
 * This module is not used directly by end-users. Rather, it is used by other
 * drivers to provide support क्रम an 8254 Programmable Interval Timer. These
 * counters are typically used to generate the pacer घड़ी used क्रम data
 * acquisition. Some drivers also expose the counters क्रम general purpose use.
 *
 * This module provides the following basic functions:
 *
 * comedi_8254_init() / comedi_8254_mm_init()
 *	Initializes this module to access the 8254 रेजिस्टरs. The _mm version
 *	sets up the module क्रम MMIO रेजिस्टर access the other क्रम PIO access.
 *	The poपूर्णांकer वापसed from these functions is normally stored in the
 *	comedi_device dev->pacer and will be मुक्तd by the comedi core during
 *	the driver (*detach). If a driver has multiple 8254 devices, they need
 *	to be stored in the drivers निजी data and मुक्तd when the driver is
 *	detached.
 *
 *	NOTE: The counters are reset by setting them to I8254_MODE0 as part of
 *	this initialization.
 *
 * comedi_8254_set_mode()
 *	Sets a counters operation mode:
 *		I8254_MODE0	Interrupt on terminal count
 *		I8254_MODE1	Hardware retriggerable one-shot
 *		I8254_MODE2	Rate generator
 *		I8254_MODE3	Square wave mode
 *		I8254_MODE4	Software triggered strobe
 *		I8254_MODE5	Hardware triggered strobe (retriggerable)
 *
 *	In addition I8254_BCD and I8254_BINARY specअगरy the counting mode:
 *		I8254_BCD	BCD counting
 *		I8254_BINARY	Binary counting
 *
 * comedi_8254_ग_लिखो()
 *	Writes an initial value to a counter.
 *
 *	The largest possible initial count is 0; this is equivalent to 2^16
 *	क्रम binary counting and 10^4 क्रम BCD counting.
 *
 *	NOTE: The counter करोes not stop when it reaches zero. In Mode 0, 1, 4,
 *	and 5 the counter "wraps around" to the highest count, either 0xffff
 *	क्रम binary counting or 9999 क्रम BCD counting, and जारीs counting.
 *	Modes 2 and 3 are periodic; the counter reloads itself with the initial
 *	count and जारीs counting from there.
 *
 * comedi_8254_पढ़ो()
 *	Reads the current value from a counter.
 *
 * comedi_8254_status()
 *	Reads the status of a counter.
 *
 * comedi_8254_load()
 *	Sets a counters operation mode and ग_लिखोs the initial value.
 *
 * Typically the pacer घड़ी is created by cascading two of the 16-bit counters
 * to create a 32-bit rate generator (I8254_MODE2). These functions are
 * provided to handle the cascaded counters:
 *
 * comedi_8254_ns_to_समयr()
 *	Calculates the भागisor value needed क्रम a single counter to generate
 *	ns timing.
 *
 * comedi_8254_cascade_ns_to_समयr()
 *	Calculates the two भागisor values needed to the generate the pacer
 *	घड़ी (in ns).
 *
 * comedi_8254_update_भागisors()
 *	Transfers the पूर्णांकermediate भागisor values to the current भागisors.
 *
 * comedi_8254_pacer_enable()
 *	Programs the mode of the cascaded counters and ग_लिखोs the current
 *	भागisor values.
 *
 * To expose the counters as a subdevice क्रम general purpose use the following
 * functions a provided:
 *
 * comedi_8254_subdevice_init()
 *	Initializes a comedi_subdevice to use the 8254 समयr.
 *
 * comedi_8254_set_busy()
 *	Internally flags a counter as "busy". This is करोne to protect the
 *	counters that are used क्रम the cascaded 32-bit pacer.
 *
 * The subdevice provides (*insn_पढ़ो) and (*insn_ग_लिखो) operations to पढ़ो
 * the current value and ग_लिखो an initial value to a counter. A (*insn_config)
 * operation is also provided to handle the following comedi inकाष्ठाions:
 *
 *	INSN_CONFIG_SET_COUNTER_MODE	calls comedi_8254_set_mode()
 *	INSN_CONFIG_8254_READ_STATUS	calls comedi_8254_status()
 *
 * The (*insn_config) member of comedi_8254 can be initialized by the बाह्यal
 * driver to handle any additional inकाष्ठाions.
 *
 * NOTE: Gate control, घड़ी routing, and any पूर्णांकerrupt handling क्रम the
 * counters is not handled by this module. These features are driver dependent.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>

#समावेश "../comedidev.h"

#समावेश "comedi_8254.h"

अटल अचिन्हित पूर्णांक __i8254_पढ़ो(काष्ठा comedi_8254 *i8254, अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक reg_offset = (reg * i8254->iosize) << i8254->regshअगरt;
	अचिन्हित पूर्णांक val;

	चयन (i8254->iosize) अणु
	शेष:
	हाल I8254_IO8:
		अगर (i8254->mmio)
			val = पढ़ोb(i8254->mmio + reg_offset);
		अन्यथा
			val = inb(i8254->iobase + reg_offset);
		अवरोध;
	हाल I8254_IO16:
		अगर (i8254->mmio)
			val = पढ़ोw(i8254->mmio + reg_offset);
		अन्यथा
			val = inw(i8254->iobase + reg_offset);
		अवरोध;
	हाल I8254_IO32:
		अगर (i8254->mmio)
			val = पढ़ोl(i8254->mmio + reg_offset);
		अन्यथा
			val = inl(i8254->iobase + reg_offset);
		अवरोध;
	पूर्ण
	वापस val & 0xff;
पूर्ण

अटल व्योम __i8254_ग_लिखो(काष्ठा comedi_8254 *i8254,
			  अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक reg_offset = (reg * i8254->iosize) << i8254->regshअगरt;

	चयन (i8254->iosize) अणु
	शेष:
	हाल I8254_IO8:
		अगर (i8254->mmio)
			ग_लिखोb(val, i8254->mmio + reg_offset);
		अन्यथा
			outb(val, i8254->iobase + reg_offset);
		अवरोध;
	हाल I8254_IO16:
		अगर (i8254->mmio)
			ग_लिखोw(val, i8254->mmio + reg_offset);
		अन्यथा
			outw(val, i8254->iobase + reg_offset);
		अवरोध;
	हाल I8254_IO32:
		अगर (i8254->mmio)
			ग_लिखोl(val, i8254->mmio + reg_offset);
		अन्यथा
			outl(val, i8254->iobase + reg_offset);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * comedi_8254_status - वापस the status of a counter
 * @i8254:	comedi_8254 काष्ठा क्रम the समयr
 * @counter:	the counter number
 */
अचिन्हित पूर्णांक comedi_8254_status(काष्ठा comedi_8254 *i8254, अचिन्हित पूर्णांक counter)
अणु
	अचिन्हित पूर्णांक cmd;

	अगर (counter > 2)
		वापस 0;

	cmd = I8254_CTRL_READBACK_STATUS | I8254_CTRL_READBACK_SEL_CTR(counter);
	__i8254_ग_लिखो(i8254, cmd, I8254_CTRL_REG);

	वापस __i8254_पढ़ो(i8254, counter);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_8254_status);

/**
 * comedi_8254_पढ़ो - पढ़ो the current counter value
 * @i8254:	comedi_8254 काष्ठा क्रम the समयr
 * @counter:	the counter number
 */
अचिन्हित पूर्णांक comedi_8254_पढ़ो(काष्ठा comedi_8254 *i8254, अचिन्हित पूर्णांक counter)
अणु
	अचिन्हित पूर्णांक val;

	अगर (counter > 2)
		वापस 0;

	/* latch counter */
	__i8254_ग_लिखो(i8254, I8254_CTRL_SEL_CTR(counter) | I8254_CTRL_LATCH,
		      I8254_CTRL_REG);

	/* पढ़ो LSB then MSB */
	val = __i8254_पढ़ो(i8254, counter);
	val |= (__i8254_पढ़ो(i8254, counter) << 8);

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_8254_पढ़ो);

/**
 * comedi_8254_ग_लिखो - load a 16-bit initial counter value
 * @i8254:	comedi_8254 काष्ठा क्रम the समयr
 * @counter:	the counter number
 * @val:	the initial value
 */
व्योम comedi_8254_ग_लिखो(काष्ठा comedi_8254 *i8254,
		       अचिन्हित पूर्णांक counter, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक byte;

	अगर (counter > 2)
		वापस;
	अगर (val > 0xffff)
		वापस;

	/* load LSB then MSB */
	byte = val & 0xff;
	__i8254_ग_लिखो(i8254, byte, counter);
	byte = (val >> 8) & 0xff;
	__i8254_ग_लिखो(i8254, byte, counter);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_8254_ग_लिखो);

/**
 * comedi_8254_set_mode - set the mode of a counter
 * @i8254:	comedi_8254 काष्ठा क्रम the समयr
 * @counter:	the counter number
 * @mode:	the I8254_MODEx and I8254_BCD|I8254_BINARY
 */
पूर्णांक comedi_8254_set_mode(काष्ठा comedi_8254 *i8254, अचिन्हित पूर्णांक counter,
			 अचिन्हित पूर्णांक mode)
अणु
	अचिन्हित पूर्णांक byte;

	अगर (counter > 2)
		वापस -EINVAL;
	अगर (mode > (I8254_MODE5 | I8254_BCD))
		वापस -EINVAL;

	byte = I8254_CTRL_SEL_CTR(counter) |	/* select counter */
	       I8254_CTRL_LSB_MSB |		/* load LSB then MSB */
	       mode;				/* mode and BCD|binary */
	__i8254_ग_लिखो(i8254, byte, I8254_CTRL_REG);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_8254_set_mode);

/**
 * comedi_8254_load - program the mode and initial count of a counter
 * @i8254:	comedi_8254 काष्ठा क्रम the समयr
 * @counter:	the counter number
 * @mode:	the I8254_MODEx and I8254_BCD|I8254_BINARY
 * @val:	the initial value
 */
पूर्णांक comedi_8254_load(काष्ठा comedi_8254 *i8254, अचिन्हित पूर्णांक counter,
		     अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक mode)
अणु
	अगर (counter > 2)
		वापस -EINVAL;
	अगर (val > 0xffff)
		वापस -EINVAL;
	अगर (mode > (I8254_MODE5 | I8254_BCD))
		वापस -EINVAL;

	comedi_8254_set_mode(i8254, counter, mode);
	comedi_8254_ग_लिखो(i8254, counter, val);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_8254_load);

/**
 * comedi_8254_pacer_enable - set the mode and load the cascaded counters
 * @i8254:	comedi_8254 काष्ठा क्रम the समयr
 * @counter1:	the counter number क्रम the first भागisor
 * @counter2:	the counter number क्रम the second भागisor
 * @enable:	flag to enable (load) the counters
 */
व्योम comedi_8254_pacer_enable(काष्ठा comedi_8254 *i8254,
			      अचिन्हित पूर्णांक counter1,
			      अचिन्हित पूर्णांक counter2,
			      bool enable)
अणु
	अचिन्हित पूर्णांक mode;

	अगर (counter1 > 2 || counter2 > 2 || counter1 == counter2)
		वापस;

	अगर (enable)
		mode = I8254_MODE2 | I8254_BINARY;
	अन्यथा
		mode = I8254_MODE0 | I8254_BINARY;

	comedi_8254_set_mode(i8254, counter1, mode);
	comedi_8254_set_mode(i8254, counter2, mode);

	अगर (enable) अणु
		/*
		 * Divisors are loaded second counter then first counter to
		 * aव्योम possible issues with the first counter expiring
		 * beक्रमe the second counter is loaded.
		 */
		comedi_8254_ग_लिखो(i8254, counter2, i8254->भागisor2);
		comedi_8254_ग_लिखो(i8254, counter1, i8254->भागisor1);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(comedi_8254_pacer_enable);

/**
 * comedi_8254_update_भागisors - update the भागisors क्रम the cascaded counters
 * @i8254:	comedi_8254 काष्ठा क्रम the समयr
 */
व्योम comedi_8254_update_भागisors(काष्ठा comedi_8254 *i8254)
अणु
	/* masking is करोne since counter maps zero to 0x10000 */
	i8254->भागisor = i8254->next_भाग & 0xffff;
	i8254->भागisor1 = i8254->next_भाग1 & 0xffff;
	i8254->भागisor2 = i8254->next_भाग2 & 0xffff;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_8254_update_भागisors);

/**
 * comedi_8254_cascade_ns_to_समयr - calculate the cascaded भागisor values
 * @i8254:	comedi_8254 काष्ठा क्रम the समयr
 * @nanosec:	the desired ns समय
 * @flags:	comedi_cmd flags
 */
व्योम comedi_8254_cascade_ns_to_समयr(काष्ठा comedi_8254 *i8254,
				     अचिन्हित पूर्णांक *nanosec,
				     अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक d1 = i8254->next_भाग1 ? i8254->next_भाग1 : I8254_MAX_COUNT;
	अचिन्हित पूर्णांक d2 = i8254->next_भाग2 ? i8254->next_भाग2 : I8254_MAX_COUNT;
	अचिन्हित पूर्णांक भाग = d1 * d2;
	अचिन्हित पूर्णांक ns_lub = 0xffffffff;
	अचिन्हित पूर्णांक ns_glb = 0;
	अचिन्हित पूर्णांक d1_lub = 0;
	अचिन्हित पूर्णांक d1_glb = 0;
	अचिन्हित पूर्णांक d2_lub = 0;
	अचिन्हित पूर्णांक d2_glb = 0;
	अचिन्हित पूर्णांक start;
	अचिन्हित पूर्णांक ns;
	अचिन्हित पूर्णांक ns_low;
	अचिन्हित पूर्णांक ns_high;

	/* निकास early अगर everything is alपढ़ोy correct */
	अगर (भाग * i8254->osc_base == *nanosec &&
	    d1 > 1 && d1 <= I8254_MAX_COUNT &&
	    d2 > 1 && d2 <= I8254_MAX_COUNT &&
	    /* check क्रम overflow */
	    भाग > d1 && भाग > d2 &&
	    भाग * i8254->osc_base > भाग &&
	    भाग * i8254->osc_base > i8254->osc_base)
		वापस;

	भाग = *nanosec / i8254->osc_base;
	d2 = I8254_MAX_COUNT;
	start = भाग / d2;
	अगर (start < 2)
		start = 2;
	क्रम (d1 = start; d1 <= भाग / d1 + 1 && d1 <= I8254_MAX_COUNT; d1++) अणु
		क्रम (d2 = भाग / d1;
		     d1 * d2 <= भाग + d1 + 1 && d2 <= I8254_MAX_COUNT; d2++) अणु
			ns = i8254->osc_base * d1 * d2;
			अगर (ns <= *nanosec && ns > ns_glb) अणु
				ns_glb = ns;
				d1_glb = d1;
				d2_glb = d2;
			पूर्ण
			अगर (ns >= *nanosec && ns < ns_lub) अणु
				ns_lub = ns;
				d1_lub = d1;
				d2_lub = d2;
			पूर्ण
		पूर्ण
	पूर्ण

	चयन (flags & CMDF_ROUND_MASK) अणु
	हाल CMDF_ROUND_NEAREST:
	शेष:
		ns_high = d1_lub * d2_lub * i8254->osc_base;
		ns_low = d1_glb * d2_glb * i8254->osc_base;
		अगर (ns_high - *nanosec < *nanosec - ns_low) अणु
			d1 = d1_lub;
			d2 = d2_lub;
		पूर्ण अन्यथा अणु
			d1 = d1_glb;
			d2 = d2_glb;
		पूर्ण
		अवरोध;
	हाल CMDF_ROUND_UP:
		d1 = d1_lub;
		d2 = d2_lub;
		अवरोध;
	हाल CMDF_ROUND_DOWN:
		d1 = d1_glb;
		d2 = d2_glb;
		अवरोध;
	पूर्ण

	*nanosec = d1 * d2 * i8254->osc_base;
	i8254->next_भाग1 = d1;
	i8254->next_भाग2 = d2;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_8254_cascade_ns_to_समयr);

/**
 * comedi_8254_ns_to_समयr - calculate the भागisor value क्रम nanosec timing
 * @i8254:	comedi_8254 काष्ठा क्रम the समयr
 * @nanosec:	the desired ns समय
 * @flags:	comedi_cmd flags
 */
व्योम comedi_8254_ns_to_समयr(काष्ठा comedi_8254 *i8254,
			     अचिन्हित पूर्णांक *nanosec, अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक भागisor;

	चयन (flags & CMDF_ROUND_MASK) अणु
	शेष:
	हाल CMDF_ROUND_NEAREST:
		भागisor = DIV_ROUND_CLOSEST(*nanosec, i8254->osc_base);
		अवरोध;
	हाल CMDF_ROUND_UP:
		भागisor = DIV_ROUND_UP(*nanosec, i8254->osc_base);
		अवरोध;
	हाल CMDF_ROUND_DOWN:
		भागisor = *nanosec / i8254->osc_base;
		अवरोध;
	पूर्ण
	अगर (भागisor < 2)
		भागisor = 2;
	अगर (भागisor > I8254_MAX_COUNT)
		भागisor = I8254_MAX_COUNT;

	*nanosec = भागisor * i8254->osc_base;
	i8254->next_भाग = भागisor;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_8254_ns_to_समयr);

/**
 * comedi_8254_set_busy - set/clear the "busy" flag क्रम a given counter
 * @i8254:	comedi_8254 काष्ठा क्रम the समयr
 * @counter:	the counter number
 * @busy:	set/clear flag
 */
व्योम comedi_8254_set_busy(काष्ठा comedi_8254 *i8254,
			  अचिन्हित पूर्णांक counter, bool busy)
अणु
	अगर (counter < 3)
		i8254->busy[counter] = busy;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_8254_set_busy);

अटल पूर्णांक comedi_8254_insn_पढ़ो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn,
				 अचिन्हित पूर्णांक *data)
अणु
	काष्ठा comedi_8254 *i8254 = s->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक i;

	अगर (i8254->busy[chan])
		वापस -EBUSY;

	क्रम (i = 0; i < insn->n; i++)
		data[i] = comedi_8254_पढ़ो(i8254, chan);

	वापस insn->n;
पूर्ण

अटल पूर्णांक comedi_8254_insn_ग_लिखो(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	काष्ठा comedi_8254 *i8254 = s->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);

	अगर (i8254->busy[chan])
		वापस -EBUSY;

	अगर (insn->n)
		comedi_8254_ग_लिखो(i8254, chan, data[insn->n - 1]);

	वापस insn->n;
पूर्ण

अटल पूर्णांक comedi_8254_insn_config(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	काष्ठा comedi_8254 *i8254 = s->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक ret;

	अगर (i8254->busy[chan])
		वापस -EBUSY;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_RESET:
		ret = comedi_8254_set_mode(i8254, chan,
					   I8254_MODE0 | I8254_BINARY);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल INSN_CONFIG_SET_COUNTER_MODE:
		ret = comedi_8254_set_mode(i8254, chan, data[1]);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल INSN_CONFIG_8254_READ_STATUS:
		data[1] = comedi_8254_status(i8254, chan);
		अवरोध;
	शेष:
		/*
		 * If available, call the driver provided (*insn_config)
		 * to handle any driver implemented inकाष्ठाions.
		 */
		अगर (i8254->insn_config)
			वापस i8254->insn_config(dev, s, insn, data);

		वापस -EINVAL;
	पूर्ण

	वापस insn->n;
पूर्ण

/**
 * comedi_8254_subdevice_init - initialize a comedi_subdevice क्रम the 8254 समयr
 * @s:		comedi_subdevice काष्ठा
 */
व्योम comedi_8254_subdevice_init(काष्ठा comedi_subdevice *s,
				काष्ठा comedi_8254 *i8254)
अणु
	s->type		= COMEDI_SUBD_COUNTER;
	s->subdev_flags	= SDF_READABLE | SDF_WRITABLE;
	s->n_chan	= 3;
	s->maxdata	= 0xffff;
	s->range_table	= &range_unknown;
	s->insn_पढ़ो	= comedi_8254_insn_पढ़ो;
	s->insn_ग_लिखो	= comedi_8254_insn_ग_लिखो;
	s->insn_config	= comedi_8254_insn_config;

	s->निजी	= i8254;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_8254_subdevice_init);

अटल काष्ठा comedi_8254 *__i8254_init(अचिन्हित दीर्घ iobase,
					व्योम __iomem *mmio,
					अचिन्हित पूर्णांक osc_base,
					अचिन्हित पूर्णांक iosize,
					अचिन्हित पूर्णांक regshअगरt)
अणु
	काष्ठा comedi_8254 *i8254;
	पूर्णांक i;

	/* sanity check that the iosize is valid */
	अगर (!(iosize == I8254_IO8 || iosize == I8254_IO16 ||
	      iosize == I8254_IO32))
		वापस शून्य;

	i8254 = kzalloc(माप(*i8254), GFP_KERNEL);
	अगर (!i8254)
		वापस शून्य;

	i8254->iobase	= iobase;
	i8254->mmio	= mmio;
	i8254->iosize	= iosize;
	i8254->regshअगरt	= regshअगरt;

	/* शेष osc_base to the max speed of a generic 8254 समयr */
	i8254->osc_base	= osc_base ? osc_base : I8254_OSC_BASE_10MHZ;

	/* reset all the counters by setting them to I8254_MODE0 */
	क्रम (i = 0; i < 3; i++)
		comedi_8254_set_mode(i8254, i, I8254_MODE0 | I8254_BINARY);

	वापस i8254;
पूर्ण

/**
 * comedi_8254_init - allocate and initialize the 8254 device क्रम pio access
 * @mmio:	port I/O base address
 * @osc_base:	base समय of the counter in ns
 *		OPTIONAL - only used by comedi_8254_cascade_ns_to_समयr()
 * @iosize:	I/O रेजिस्टर size
 * @regshअगरt:	रेजिस्टर gap shअगरt
 */
काष्ठा comedi_8254 *comedi_8254_init(अचिन्हित दीर्घ iobase,
				     अचिन्हित पूर्णांक osc_base,
				     अचिन्हित पूर्णांक iosize,
				     अचिन्हित पूर्णांक regshअगरt)
अणु
	वापस __i8254_init(iobase, शून्य, osc_base, iosize, regshअगरt);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_8254_init);

/**
 * comedi_8254_mm_init - allocate and initialize the 8254 device क्रम mmio access
 * @mmio:	memory mapped I/O base address
 * @osc_base:	base समय of the counter in ns
 *		OPTIONAL - only used by comedi_8254_cascade_ns_to_समयr()
 * @iosize:	I/O रेजिस्टर size
 * @regshअगरt:	रेजिस्टर gap shअगरt
 */
काष्ठा comedi_8254 *comedi_8254_mm_init(व्योम __iomem *mmio,
					अचिन्हित पूर्णांक osc_base,
					अचिन्हित पूर्णांक iosize,
					अचिन्हित पूर्णांक regshअगरt)
अणु
	वापस __i8254_init(0, mmio, osc_base, iosize, regshअगरt);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_8254_mm_init);

अटल पूर्णांक __init comedi_8254_module_init(व्योम)
अणु
	वापस 0;
पूर्ण
module_init(comedi_8254_module_init);

अटल व्योम __निकास comedi_8254_module_निकास(व्योम)
अणु
पूर्ण
module_निकास(comedi_8254_module_निकास);

MODULE_AUTHOR("H Hartley Sweeten <hsweeten@visionengravers.com>");
MODULE_DESCRIPTION("Comedi: Generic 8254 timer/counter support");
MODULE_LICENSE("GPL");
