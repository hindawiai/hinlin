<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * COMEDI driver क्रम the watchकरोg subdevice found on some addi-data boards
 * Copyright (c) 2013 H Hartley Sweeten <hsweeten@visionengravers.com>
 *
 * Based on implementations in various addi-data COMEDI drivers.
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1998 David A. Schleef <ds@schleef.org>
 */

#समावेश <linux/module.h>
#समावेश "../comedidev.h"
#समावेश "addi_tcw.h"
#समावेश "addi_watchdog.h"

काष्ठा addi_watchकरोg_निजी अणु
	अचिन्हित दीर्घ iobase;
	अचिन्हित पूर्णांक wकरोg_ctrl;
पूर्ण;

/*
 * The watchकरोg subdevice is configured with two INSN_CONFIG inकाष्ठाions:
 *
 * Enable the watchकरोg and set the reload समयout:
 *	data[0] = INSN_CONFIG_ARM
 *	data[1] = समयout reload value
 *
 * Disable the watchकरोg:
 *	data[0] = INSN_CONFIG_DISARM
 */
अटल पूर्णांक addi_watchकरोg_insn_config(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     काष्ठा comedi_insn *insn,
				     अचिन्हित पूर्णांक *data)
अणु
	काष्ठा addi_watchकरोg_निजी *spriv = s->निजी;
	अचिन्हित पूर्णांक reload;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_ARM:
		spriv->wकरोg_ctrl = ADDI_TCW_CTRL_ENA;
		reload = data[1] & s->maxdata;
		outl(reload, spriv->iobase + ADDI_TCW_RELOAD_REG);

		/* Time base is 20ms, let the user know the समयout */
		dev_info(dev->class_dev, "watchdog enabled, timeout:%dms\n",
			 20 * reload + 20);
		अवरोध;
	हाल INSN_CONFIG_DISARM:
		spriv->wकरोg_ctrl = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	outl(spriv->wकरोg_ctrl, spriv->iobase + ADDI_TCW_CTRL_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक addi_watchकरोg_insn_पढ़ो(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	काष्ठा addi_watchकरोg_निजी *spriv = s->निजी;
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++)
		data[i] = inl(spriv->iobase + ADDI_TCW_STATUS_REG);

	वापस insn->n;
पूर्ण

अटल पूर्णांक addi_watchकरोg_insn_ग_लिखो(काष्ठा comedi_device *dev,
				    काष्ठा comedi_subdevice *s,
				    काष्ठा comedi_insn *insn,
				    अचिन्हित पूर्णांक *data)
अणु
	काष्ठा addi_watchकरोg_निजी *spriv = s->निजी;
	पूर्णांक i;

	अगर (spriv->wकरोg_ctrl == 0) अणु
		dev_warn(dev->class_dev, "watchdog is disabled\n");
		वापस -EINVAL;
	पूर्ण

	/* "ping" the watchकरोg */
	क्रम (i = 0; i < insn->n; i++) अणु
		outl(spriv->wकरोg_ctrl | ADDI_TCW_CTRL_TRIG,
		     spriv->iobase + ADDI_TCW_CTRL_REG);
	पूर्ण

	वापस insn->n;
पूर्ण

व्योम addi_watchकरोg_reset(अचिन्हित दीर्घ iobase)
अणु
	outl(0x0, iobase + ADDI_TCW_CTRL_REG);
	outl(0x0, iobase + ADDI_TCW_RELOAD_REG);
पूर्ण
EXPORT_SYMBOL_GPL(addi_watchकरोg_reset);

पूर्णांक addi_watchकरोg_init(काष्ठा comedi_subdevice *s, अचिन्हित दीर्घ iobase)
अणु
	काष्ठा addi_watchकरोg_निजी *spriv;

	spriv = comedi_alloc_spriv(s, माप(*spriv));
	अगर (!spriv)
		वापस -ENOMEM;

	spriv->iobase = iobase;

	s->type		= COMEDI_SUBD_TIMER;
	s->subdev_flags	= SDF_WRITABLE;
	s->n_chan	= 1;
	s->maxdata	= 0xff;
	s->insn_config	= addi_watchकरोg_insn_config;
	s->insn_पढ़ो	= addi_watchकरोg_insn_पढ़ो;
	s->insn_ग_लिखो	= addi_watchकरोg_insn_ग_लिखो;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(addi_watchकरोg_init);

अटल पूर्णांक __init addi_watchकरोg_module_init(व्योम)
अणु
	वापस 0;
पूर्ण
module_init(addi_watchकरोg_module_init);

अटल व्योम __निकास addi_watchकरोg_module_निकास(व्योम)
अणु
पूर्ण
module_निकास(addi_watchकरोg_module_निकास);

MODULE_DESCRIPTION("ADDI-DATA Watchdog subdevice");
MODULE_AUTHOR("H Hartley Sweeten <hsweeten@visionengravers.com>");
MODULE_LICENSE("GPL");
