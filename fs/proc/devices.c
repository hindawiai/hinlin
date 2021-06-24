<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/blkdev.h>

अटल पूर्णांक devinfo_show(काष्ठा seq_file *f, व्योम *v)
अणु
	पूर्णांक i = *(loff_t *) v;

	अगर (i < CHRDEV_MAJOR_MAX) अणु
		अगर (i == 0)
			seq_माला_दो(f, "Character devices:\n");
		chrdev_show(f, i);
	पूर्ण
#अगर_घोषित CONFIG_BLOCK
	अन्यथा अणु
		i -= CHRDEV_MAJOR_MAX;
		अगर (i == 0)
			seq_माला_दो(f, "\nBlock devices:\n");
		blkdev_show(f, i);
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम *devinfo_start(काष्ठा seq_file *f, loff_t *pos)
अणु
	अगर (*pos < (BLKDEV_MAJOR_MAX + CHRDEV_MAJOR_MAX))
		वापस pos;
	वापस शून्य;
पूर्ण

अटल व्योम *devinfo_next(काष्ठा seq_file *f, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	अगर (*pos >= (BLKDEV_MAJOR_MAX + CHRDEV_MAJOR_MAX))
		वापस शून्य;
	वापस pos;
पूर्ण

अटल व्योम devinfo_stop(काष्ठा seq_file *f, व्योम *v)
अणु
	/* Nothing to करो */
पूर्ण

अटल स्थिर काष्ठा seq_operations devinfo_ops = अणु
	.start = devinfo_start,
	.next  = devinfo_next,
	.stop  = devinfo_stop,
	.show  = devinfo_show
पूर्ण;

अटल पूर्णांक __init proc_devices_init(व्योम)
अणु
	proc_create_seq("devices", 0, शून्य, &devinfo_ops);
	वापस 0;
पूर्ण
fs_initcall(proc_devices_init);
