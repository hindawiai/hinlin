<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * kcomedilib/kcomedilib.c
 * a comedlib पूर्णांकerface क्रम kernel modules
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1997-2000 David A. Schleef <ds@schleef.org>
 */

#समावेश <linux/module.h>

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पन.स>

#समावेश "../comedi.h"
#समावेश "../comedilib.h"
#समावेश "../comedidev.h"

MODULE_AUTHOR("David Schleef <ds@schleef.org>");
MODULE_DESCRIPTION("Comedi kernel library");
MODULE_LICENSE("GPL");

काष्ठा comedi_device *comedi_खोलो(स्थिर अक्षर *filename)
अणु
	काष्ठा comedi_device *dev, *retval = शून्य;
	अचिन्हित पूर्णांक minor;

	अगर (म_भेदन(filename, "/dev/comedi", 11) != 0)
		वापस शून्य;

	अगर (kstrtouपूर्णांक(filename + 11, 0, &minor))
		वापस शून्य;

	अगर (minor >= COMEDI_NUM_BOARD_MINORS)
		वापस शून्य;

	dev = comedi_dev_get_from_minor(minor);
	अगर (!dev)
		वापस शून्य;

	करोwn_पढ़ो(&dev->attach_lock);
	अगर (dev->attached)
		retval = dev;
	अन्यथा
		retval = शून्य;
	up_पढ़ो(&dev->attach_lock);

	अगर (!retval)
		comedi_dev_put(dev);

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_खोलो);

पूर्णांक comedi_बंद(काष्ठा comedi_device *dev)
अणु
	comedi_dev_put(dev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_बंद);

अटल पूर्णांक comedi_करो_insn(काष्ठा comedi_device *dev,
			  काष्ठा comedi_insn *insn,
			  अचिन्हित पूर्णांक *data)
अणु
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;

	mutex_lock(&dev->mutex);

	अगर (!dev->attached) अणु
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	/* a subdevice inकाष्ठाion */
	अगर (insn->subdev >= dev->n_subdevices) अणु
		ret = -EINVAL;
		जाओ error;
	पूर्ण
	s = &dev->subdevices[insn->subdev];

	अगर (s->type == COMEDI_SUBD_UNUSED) अणु
		dev_err(dev->class_dev,
			"%d not usable subdevice\n", insn->subdev);
		ret = -EIO;
		जाओ error;
	पूर्ण

	/* XXX check lock */

	ret = comedi_check_chanlist(s, 1, &insn->chanspec);
	अगर (ret < 0) अणु
		dev_err(dev->class_dev, "bad chanspec\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	अगर (s->busy) अणु
		ret = -EBUSY;
		जाओ error;
	पूर्ण
	s->busy = dev;

	चयन (insn->insn) अणु
	हाल INSN_BITS:
		ret = s->insn_bits(dev, s, insn, data);
		अवरोध;
	हाल INSN_CONFIG:
		/* XXX should check inकाष्ठाion length */
		ret = s->insn_config(dev, s, insn, data);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	s->busy = शून्य;
error:

	mutex_unlock(&dev->mutex);
	वापस ret;
पूर्ण

पूर्णांक comedi_dio_get_config(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक subdev,
			  अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक *io)
अणु
	काष्ठा comedi_insn insn;
	अचिन्हित पूर्णांक data[2];
	पूर्णांक ret;

	स_रखो(&insn, 0, माप(insn));
	insn.insn = INSN_CONFIG;
	insn.n = 2;
	insn.subdev = subdev;
	insn.chanspec = CR_PACK(chan, 0, 0);
	data[0] = INSN_CONFIG_DIO_QUERY;
	data[1] = 0;
	ret = comedi_करो_insn(dev, &insn, data);
	अगर (ret >= 0)
		*io = data[1];
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_dio_get_config);

पूर्णांक comedi_dio_config(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक subdev,
		      अचिन्हित पूर्णांक chan, अचिन्हित पूर्णांक io)
अणु
	काष्ठा comedi_insn insn;

	स_रखो(&insn, 0, माप(insn));
	insn.insn = INSN_CONFIG;
	insn.n = 1;
	insn.subdev = subdev;
	insn.chanspec = CR_PACK(chan, 0, 0);

	वापस comedi_करो_insn(dev, &insn, &io);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_dio_config);

पूर्णांक comedi_dio_bitfield2(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक subdev,
			 अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक *bits,
			 अचिन्हित पूर्णांक base_channel)
अणु
	काष्ठा comedi_insn insn;
	अचिन्हित पूर्णांक data[2];
	अचिन्हित पूर्णांक n_chan;
	अचिन्हित पूर्णांक shअगरt;
	पूर्णांक ret;

	base_channel = CR_CHAN(base_channel);
	n_chan = comedi_get_n_channels(dev, subdev);
	अगर (base_channel >= n_chan)
		वापस -EINVAL;

	स_रखो(&insn, 0, माप(insn));
	insn.insn = INSN_BITS;
	insn.chanspec = base_channel;
	insn.n = 2;
	insn.subdev = subdev;

	data[0] = mask;
	data[1] = *bits;

	/*
	 * Most drivers ignore the base channel in insn->chanspec.
	 * Fix this here अगर the subdevice has <= 32 channels.
	 */
	अगर (n_chan <= 32) अणु
		shअगरt = base_channel;
		अगर (shअगरt) अणु
			insn.chanspec = 0;
			data[0] <<= shअगरt;
			data[1] <<= shअगरt;
		पूर्ण
	पूर्ण अन्यथा अणु
		shअगरt = 0;
	पूर्ण

	ret = comedi_करो_insn(dev, &insn, data);
	*bits = data[1] >> shअगरt;
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_dio_bitfield2);

पूर्णांक comedi_find_subdevice_by_type(काष्ठा comedi_device *dev, पूर्णांक type,
				  अचिन्हित पूर्णांक subd)
अणु
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret = -ENODEV;

	करोwn_पढ़ो(&dev->attach_lock);
	अगर (dev->attached)
		क्रम (; subd < dev->n_subdevices; subd++) अणु
			s = &dev->subdevices[subd];
			अगर (s->type == type) अणु
				ret = subd;
				अवरोध;
			पूर्ण
		पूर्ण
	up_पढ़ो(&dev->attach_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_find_subdevice_by_type);

पूर्णांक comedi_get_n_channels(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक subdevice)
अणु
	पूर्णांक n;

	करोwn_पढ़ो(&dev->attach_lock);
	अगर (!dev->attached || subdevice >= dev->n_subdevices)
		n = 0;
	अन्यथा
		n = dev->subdevices[subdevice].n_chan;
	up_पढ़ो(&dev->attach_lock);

	वापस n;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_get_n_channels);

अटल पूर्णांक __init kcomedilib_module_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम __निकास kcomedilib_module_निकास(व्योम)
अणु
पूर्ण

module_init(kcomedilib_module_init);
module_निकास(kcomedilib_module_निकास);
