<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * /proc पूर्णांकerface क्रम comedi
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 1998 David A. Schleef <ds@schleef.org>
 */

/*
 * This is some serious bloatware.
 *
 * Taken from Dave A.'s PCL-711 driver, 'cuz I thought it
 * was cool.
 */

#समावेश "comedidev.h"
#समावेश "comedi_internal.h"
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>

अटल पूर्णांक comedi_पढ़ो(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक i;
	पूर्णांक devices_q = 0;
	काष्ठा comedi_driver *driv;

	seq_म_लिखो(m, "comedi version " COMEDI_RELEASE "\nformat string: %s\n",
		   "\"%2d: %-20s %-20s %4d\", i, driver_name, board_name, n_subdevices");

	क्रम (i = 0; i < COMEDI_NUM_BOARD_MINORS; i++) अणु
		काष्ठा comedi_device *dev = comedi_dev_get_from_minor(i);

		अगर (!dev)
			जारी;

		करोwn_पढ़ो(&dev->attach_lock);
		अगर (dev->attached) अणु
			devices_q = 1;
			seq_म_लिखो(m, "%2d: %-20s %-20s %4d\n",
				   i, dev->driver->driver_name,
				   dev->board_name, dev->n_subdevices);
		पूर्ण
		up_पढ़ो(&dev->attach_lock);
		comedi_dev_put(dev);
	पूर्ण
	अगर (!devices_q)
		seq_माला_दो(m, "no devices\n");

	mutex_lock(&comedi_drivers_list_lock);
	क्रम (driv = comedi_drivers; driv; driv = driv->next) अणु
		seq_म_लिखो(m, "%s:\n", driv->driver_name);
		क्रम (i = 0; i < driv->num_names; i++)
			seq_म_लिखो(m, " %s\n",
				   *(अक्षर **)((अक्षर *)driv->board_name +
					      i * driv->offset));

		अगर (!driv->num_names)
			seq_म_लिखो(m, " %s\n", driv->driver_name);
	पूर्ण
	mutex_unlock(&comedi_drivers_list_lock);

	वापस 0;
पूर्ण

व्योम __init comedi_proc_init(व्योम)
अणु
	अगर (!proc_create_single("comedi", 0444, शून्य, comedi_पढ़ो))
		pr_warn("comedi: unable to create proc entry\n");
पूर्ण

व्योम comedi_proc_cleanup(व्योम)
अणु
	हटाओ_proc_entry("comedi", शून्य);
पूर्ण
