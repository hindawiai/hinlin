<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/drivers/अक्षर/misc.c
 *
 * Generic misc खोलो routine by Johan Myreen
 *
 * Based on code from Linus
 *
 * Teemu Rantanen's Microsoft Busmouse support and Derrick Cole's
 *   changes incorporated पूर्णांकo 0.97pl4
 *   by Peter Cervasio (pete%q106fm.uucp@wupost.wustl.edu) (08SEP92)
 *   See busmouse.c क्रम particulars.
 *
 * Made things a lot mode modular - easy to compile in just one or two
 * of the misc drivers, as they are now completely independent. Linus.
 *
 * Support क्रम loadable modules. 8-Sep-95 Philip Blundell <pjb27@cam.ac.uk>
 *
 * Fixed a failing symbol रेजिस्टर to मुक्त the device registration
 *		Alan Cox <alan@lxorguk.ukuu.org.uk> 21-Jan-96
 *
 * Dynamic minors and /proc/mice by Alessandro Rubini. 26-Mar-96
 *
 * Renamed to misc and miscdevice to be more accurate. Alan Cox 26-Mar-96
 *
 * Handling of mouse minor numbers क्रम kerneld:
 *  Idea by Jacques Gelinas <jack@solucorp.qc.ca>,
 *  adapted by Bjorn Ekwall <bj0rn@blox.se>
 *  corrected by Alan Cox <alan@lxorguk.ukuu.org.uk>
 *
 * Changes क्रम kmod (from kerneld):
 *	Cyrus Durgin <cider@speakeasy.org>
 *
 * Added devfs support. Riअक्षरd Gooch <rgooch@atnf.csiro.au>  10-Jan-1998
 */

#समावेश <linux/module.h>

#समावेश <linux/fs.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/miscdevice.h>
#समावेश <linux/kernel.h>
#समावेश <linux/major.h>
#समावेश <linux/mutex.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/tty.h>
#समावेश <linux/kmod.h>
#समावेश <linux/gfp.h>

/*
 * Head entry क्रम the करोubly linked miscdevice list
 */
अटल LIST_HEAD(misc_list);
अटल DEFINE_MUTEX(misc_mtx);

/*
 * Asचिन्हित numbers, used क्रम dynamic minors
 */
#घोषणा DYNAMIC_MINORS 128 /* like dynamic majors */
अटल DECLARE_BITMAP(misc_minors, DYNAMIC_MINORS);

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम *misc_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	mutex_lock(&misc_mtx);
	वापस seq_list_start(&misc_list, *pos);
पूर्ण

अटल व्योम *misc_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	वापस seq_list_next(v, &misc_list, pos);
पूर्ण

अटल व्योम misc_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	mutex_unlock(&misc_mtx);
पूर्ण

अटल पूर्णांक misc_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	स्थिर काष्ठा miscdevice *p = list_entry(v, काष्ठा miscdevice, list);

	seq_म_लिखो(seq, "%3i %s\n", p->minor, p->name ? p->name : "");
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा seq_operations misc_seq_ops = अणु
	.start = misc_seq_start,
	.next  = misc_seq_next,
	.stop  = misc_seq_stop,
	.show  = misc_seq_show,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक misc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक minor = iminor(inode);
	काष्ठा miscdevice *c;
	पूर्णांक err = -ENODEV;
	स्थिर काष्ठा file_operations *new_fops = शून्य;

	mutex_lock(&misc_mtx);

	list_क्रम_each_entry(c, &misc_list, list) अणु
		अगर (c->minor == minor) अणु
			new_fops = fops_get(c->fops);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!new_fops) अणु
		mutex_unlock(&misc_mtx);
		request_module("char-major-%d-%d", MISC_MAJOR, minor);
		mutex_lock(&misc_mtx);

		list_क्रम_each_entry(c, &misc_list, list) अणु
			अगर (c->minor == minor) अणु
				new_fops = fops_get(c->fops);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!new_fops)
			जाओ fail;
	पूर्ण

	/*
	 * Place the miscdevice in the file's
	 * निजी_data so it can be used by the
	 * file operations, including f_op->खोलो below
	 */
	file->निजी_data = c;

	err = 0;
	replace_fops(file, new_fops);
	अगर (file->f_op->खोलो)
		err = file->f_op->खोलो(inode, file);
fail:
	mutex_unlock(&misc_mtx);
	वापस err;
पूर्ण

अटल काष्ठा class *misc_class;

अटल स्थिर काष्ठा file_operations misc_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= misc_खोलो,
	.llseek		= noop_llseek,
पूर्ण;

/**
 *	misc_रेजिस्टर	-	रेजिस्टर a miscellaneous device
 *	@misc: device काष्ठाure
 *
 *	Register a miscellaneous device with the kernel. If the minor
 *	number is set to %MISC_DYNAMIC_MINOR a minor number is asचिन्हित
 *	and placed in the minor field of the काष्ठाure. For other हालs
 *	the minor number requested is used.
 *
 *	The काष्ठाure passed is linked पूर्णांकo the kernel and may not be
 *	destroyed until it has been unरेजिस्टरed. By शेष, an खोलो()
 *	syscall to the device sets file->निजी_data to poपूर्णांक to the
 *	काष्ठाure. Drivers करोn't need खोलो in fops क्रम this.
 *
 *	A zero is वापसed on success and a negative त्रुटि_सं code क्रम
 *	failure.
 */

पूर्णांक misc_रेजिस्टर(काष्ठा miscdevice *misc)
अणु
	dev_t dev;
	पूर्णांक err = 0;
	bool is_dynamic = (misc->minor == MISC_DYNAMIC_MINOR);

	INIT_LIST_HEAD(&misc->list);

	mutex_lock(&misc_mtx);

	अगर (is_dynamic) अणु
		पूर्णांक i = find_first_zero_bit(misc_minors, DYNAMIC_MINORS);

		अगर (i >= DYNAMIC_MINORS) अणु
			err = -EBUSY;
			जाओ out;
		पूर्ण
		misc->minor = DYNAMIC_MINORS - i - 1;
		set_bit(i, misc_minors);
	पूर्ण अन्यथा अणु
		काष्ठा miscdevice *c;

		list_क्रम_each_entry(c, &misc_list, list) अणु
			अगर (c->minor == misc->minor) अणु
				err = -EBUSY;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	dev = MKDEV(MISC_MAJOR, misc->minor);

	misc->this_device =
		device_create_with_groups(misc_class, misc->parent, dev,
					  misc, misc->groups, "%s", misc->name);
	अगर (IS_ERR(misc->this_device)) अणु
		अगर (is_dynamic) अणु
			पूर्णांक i = DYNAMIC_MINORS - misc->minor - 1;

			अगर (i < DYNAMIC_MINORS && i >= 0)
				clear_bit(i, misc_minors);
			misc->minor = MISC_DYNAMIC_MINOR;
		पूर्ण
		err = PTR_ERR(misc->this_device);
		जाओ out;
	पूर्ण

	/*
	 * Add it to the front, so that later devices can "override"
	 * earlier शेषs
	 */
	list_add(&misc->list, &misc_list);
 out:
	mutex_unlock(&misc_mtx);
	वापस err;
पूर्ण
EXPORT_SYMBOL(misc_रेजिस्टर);

/**
 *	misc_deरेजिस्टर - unरेजिस्टर a miscellaneous device
 *	@misc: device to unरेजिस्टर
 *
 *	Unरेजिस्टर a miscellaneous device that was previously
 *	successfully रेजिस्टरed with misc_रेजिस्टर().
 */

व्योम misc_deरेजिस्टर(काष्ठा miscdevice *misc)
अणु
	पूर्णांक i = DYNAMIC_MINORS - misc->minor - 1;

	अगर (WARN_ON(list_empty(&misc->list)))
		वापस;

	mutex_lock(&misc_mtx);
	list_del(&misc->list);
	device_destroy(misc_class, MKDEV(MISC_MAJOR, misc->minor));
	अगर (i < DYNAMIC_MINORS && i >= 0)
		clear_bit(i, misc_minors);
	mutex_unlock(&misc_mtx);
पूर्ण
EXPORT_SYMBOL(misc_deरेजिस्टर);

अटल अक्षर *misc_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	काष्ठा miscdevice *c = dev_get_drvdata(dev);

	अगर (mode && c->mode)
		*mode = c->mode;
	अगर (c->nodename)
		वापस kstrdup(c->nodename, GFP_KERNEL);
	वापस शून्य;
पूर्ण

अटल पूर्णांक __init misc_init(व्योम)
अणु
	पूर्णांक err;
	काष्ठा proc_dir_entry *ret;

	ret = proc_create_seq("misc", 0, शून्य, &misc_seq_ops);
	misc_class = class_create(THIS_MODULE, "misc");
	err = PTR_ERR(misc_class);
	अगर (IS_ERR(misc_class))
		जाओ fail_हटाओ;

	err = -EIO;
	अगर (रेजिस्टर_chrdev(MISC_MAJOR, "misc", &misc_fops))
		जाओ fail_prपूर्णांकk;
	misc_class->devnode = misc_devnode;
	वापस 0;

fail_prपूर्णांकk:
	pr_err("unable to get major %d for misc devices\n", MISC_MAJOR);
	class_destroy(misc_class);
fail_हटाओ:
	अगर (ret)
		हटाओ_proc_entry("misc", शून्य);
	वापस err;
पूर्ण
subsys_initcall(misc_init);
