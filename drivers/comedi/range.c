<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/range.c
 * comedi routines क्रम voltage ranges
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1997-8 David A. Schleef <ds@schleef.org>
 */

#समावेश <linux/uaccess.h>
#समावेश "comedidev.h"
#समावेश "comedi_internal.h"

स्थिर काष्ठा comedi_lrange range_bipolar10 = अणु 1, अणुBIP_RANGE(10)पूर्ण पूर्ण;
EXPORT_SYMBOL_GPL(range_bipolar10);
स्थिर काष्ठा comedi_lrange range_bipolar5 = अणु 1, अणुBIP_RANGE(5)पूर्ण पूर्ण;
EXPORT_SYMBOL_GPL(range_bipolar5);
स्थिर काष्ठा comedi_lrange range_bipolar2_5 = अणु 1, अणुBIP_RANGE(2.5)पूर्ण पूर्ण;
EXPORT_SYMBOL_GPL(range_bipolar2_5);
स्थिर काष्ठा comedi_lrange range_unipolar10 = अणु 1, अणुUNI_RANGE(10)पूर्ण पूर्ण;
EXPORT_SYMBOL_GPL(range_unipolar10);
स्थिर काष्ठा comedi_lrange range_unipolar5 = अणु 1, अणुUNI_RANGE(5)पूर्ण पूर्ण;
EXPORT_SYMBOL_GPL(range_unipolar5);
स्थिर काष्ठा comedi_lrange range_unipolar2_5 = अणु 1, अणुUNI_RANGE(2.5)पूर्ण पूर्ण;
EXPORT_SYMBOL_GPL(range_unipolar2_5);
स्थिर काष्ठा comedi_lrange range_0_20mA = अणु 1, अणुRANGE_mA(0, 20)पूर्ण पूर्ण;
EXPORT_SYMBOL_GPL(range_0_20mA);
स्थिर काष्ठा comedi_lrange range_4_20mA = अणु 1, अणुRANGE_mA(4, 20)पूर्ण पूर्ण;
EXPORT_SYMBOL_GPL(range_4_20mA);
स्थिर काष्ठा comedi_lrange range_0_32mA = अणु 1, अणुRANGE_mA(0, 32)पूर्ण पूर्ण;
EXPORT_SYMBOL_GPL(range_0_32mA);
स्थिर काष्ठा comedi_lrange range_unknown = अणु 1, अणुअणु0, 1000000, UNIT_noneपूर्ण पूर्ण पूर्ण;
EXPORT_SYMBOL_GPL(range_unknown);

/*
 * COMEDI_RANGEINFO ioctl
 * range inक्रमmation
 *
 * arg:
 *	poपूर्णांकer to comedi_rangeinfo काष्ठाure
 *
 * पढ़ोs:
 *	comedi_rangeinfo काष्ठाure
 *
 * ग_लिखोs:
 *	array of comedi_krange काष्ठाures to rangeinfo->range_ptr poपूर्णांकer
 */
पूर्णांक करो_rangeinfo_ioctl(काष्ठा comedi_device *dev,
		       काष्ठा comedi_rangeinfo *it)
अणु
	पूर्णांक subd, chan;
	स्थिर काष्ठा comedi_lrange *lr;
	काष्ठा comedi_subdevice *s;

	subd = (it->range_type >> 24) & 0xf;
	chan = (it->range_type >> 16) & 0xff;

	अगर (!dev->attached)
		वापस -EINVAL;
	अगर (subd >= dev->n_subdevices)
		वापस -EINVAL;
	s = &dev->subdevices[subd];
	अगर (s->range_table) अणु
		lr = s->range_table;
	पूर्ण अन्यथा अगर (s->range_table_list) अणु
		अगर (chan >= s->n_chan)
			वापस -EINVAL;
		lr = s->range_table_list[chan];
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (RANGE_LENGTH(it->range_type) != lr->length) अणु
		dev_dbg(dev->class_dev,
			"wrong length %d should be %d (0x%08x)\n",
			RANGE_LENGTH(it->range_type),
			lr->length, it->range_type);
		वापस -EINVAL;
	पूर्ण

	अगर (copy_to_user(it->range_ptr, lr->range,
			 माप(काष्ठा comedi_krange) * lr->length))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/**
 * comedi_check_chanlist() - Validate each element in a chanlist.
 * @s: comedi_subdevice काष्ठा
 * @n: number of elements in the chanlist
 * @chanlist: the chanlist to validate
 *
 * Each element consists of a channel number, a range index, an analog
 * reference type and some flags, all packed पूर्णांकo an अचिन्हित पूर्णांक.
 *
 * This checks that the channel number and range index are supported by
 * the comedi subdevice.  It करोes not check whether the analog reference
 * type and the flags are supported.  Drivers that care should check those
 * themselves.
 *
 * Return: %0 अगर all @chanlist elements are valid (success),
 *         %-EINVAL अगर one or more elements are invalid.
 */
पूर्णांक comedi_check_chanlist(काष्ठा comedi_subdevice *s, पूर्णांक n,
			  अचिन्हित पूर्णांक *chanlist)
अणु
	काष्ठा comedi_device *dev = s->device;
	अचिन्हित पूर्णांक chanspec;
	पूर्णांक chan, range_len, i;

	क्रम (i = 0; i < n; i++) अणु
		chanspec = chanlist[i];
		chan = CR_CHAN(chanspec);
		अगर (s->range_table)
			range_len = s->range_table->length;
		अन्यथा अगर (s->range_table_list && chan < s->n_chan)
			range_len = s->range_table_list[chan]->length;
		अन्यथा
			range_len = 0;
		अगर (chan >= s->n_chan ||
		    CR_RANGE(chanspec) >= range_len) अणु
			dev_warn(dev->class_dev,
				 "bad chanlist[%d]=0x%08x chan=%d range length=%d\n",
				 i, chanspec, chan, range_len);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_check_chanlist);
