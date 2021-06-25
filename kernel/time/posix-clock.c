<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Support क्रम dynamic घड़ी devices
 *
 * Copyright (C) 2010 OMICRON electronics GmbH
 */
#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/file.h>
#समावेश <linux/posix-घड़ी.h>
#समावेश <linux/slab.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/uaccess.h>

#समावेश "posix-timers.h"

/*
 * Returns शून्य अगर the posix_घड़ी instance attached to 'fp' is old and stale.
 */
अटल काष्ठा posix_घड़ी *get_posix_घड़ी(काष्ठा file *fp)
अणु
	काष्ठा posix_घड़ी *clk = fp->निजी_data;

	करोwn_पढ़ो(&clk->rwsem);

	अगर (!clk->zombie)
		वापस clk;

	up_पढ़ो(&clk->rwsem);

	वापस शून्य;
पूर्ण

अटल व्योम put_posix_घड़ी(काष्ठा posix_घड़ी *clk)
अणु
	up_पढ़ो(&clk->rwsem);
पूर्ण

अटल sमाप_प्रकार posix_घड़ी_पढ़ो(काष्ठा file *fp, अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा posix_घड़ी *clk = get_posix_घड़ी(fp);
	पूर्णांक err = -EINVAL;

	अगर (!clk)
		वापस -ENODEV;

	अगर (clk->ops.पढ़ो)
		err = clk->ops.पढ़ो(clk, fp->f_flags, buf, count);

	put_posix_घड़ी(clk);

	वापस err;
पूर्ण

अटल __poll_t posix_घड़ी_poll(काष्ठा file *fp, poll_table *रुको)
अणु
	काष्ठा posix_घड़ी *clk = get_posix_घड़ी(fp);
	__poll_t result = 0;

	अगर (!clk)
		वापस EPOLLERR;

	अगर (clk->ops.poll)
		result = clk->ops.poll(clk, fp, रुको);

	put_posix_घड़ी(clk);

	वापस result;
पूर्ण

अटल दीर्घ posix_घड़ी_ioctl(काष्ठा file *fp,
			      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा posix_घड़ी *clk = get_posix_घड़ी(fp);
	पूर्णांक err = -ENOTTY;

	अगर (!clk)
		वापस -ENODEV;

	अगर (clk->ops.ioctl)
		err = clk->ops.ioctl(clk, cmd, arg);

	put_posix_घड़ी(clk);

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ posix_घड़ी_compat_ioctl(काष्ठा file *fp,
				     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा posix_घड़ी *clk = get_posix_घड़ी(fp);
	पूर्णांक err = -ENOTTY;

	अगर (!clk)
		वापस -ENODEV;

	अगर (clk->ops.ioctl)
		err = clk->ops.ioctl(clk, cmd, arg);

	put_posix_घड़ी(clk);

	वापस err;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक posix_घड़ी_खोलो(काष्ठा inode *inode, काष्ठा file *fp)
अणु
	पूर्णांक err;
	काष्ठा posix_घड़ी *clk =
		container_of(inode->i_cdev, काष्ठा posix_घड़ी, cdev);

	करोwn_पढ़ो(&clk->rwsem);

	अगर (clk->zombie) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण
	अगर (clk->ops.खोलो)
		err = clk->ops.खोलो(clk, fp->f_mode);
	अन्यथा
		err = 0;

	अगर (!err) अणु
		get_device(clk->dev);
		fp->निजी_data = clk;
	पूर्ण
out:
	up_पढ़ो(&clk->rwsem);
	वापस err;
पूर्ण

अटल पूर्णांक posix_घड़ी_release(काष्ठा inode *inode, काष्ठा file *fp)
अणु
	काष्ठा posix_घड़ी *clk = fp->निजी_data;
	पूर्णांक err = 0;

	अगर (clk->ops.release)
		err = clk->ops.release(clk);

	put_device(clk->dev);

	fp->निजी_data = शून्य;

	वापस err;
पूर्ण

अटल स्थिर काष्ठा file_operations posix_घड़ी_file_operations = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.पढ़ो		= posix_घड़ी_पढ़ो,
	.poll		= posix_घड़ी_poll,
	.unlocked_ioctl	= posix_घड़ी_ioctl,
	.खोलो		= posix_घड़ी_खोलो,
	.release	= posix_घड़ी_release,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= posix_घड़ी_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

पूर्णांक posix_घड़ी_रेजिस्टर(काष्ठा posix_घड़ी *clk, काष्ठा device *dev)
अणु
	पूर्णांक err;

	init_rwsem(&clk->rwsem);

	cdev_init(&clk->cdev, &posix_घड़ी_file_operations);
	err = cdev_device_add(&clk->cdev, dev);
	अगर (err) अणु
		pr_err("%s unable to add device %d:%d\n",
			dev_name(dev), MAJOR(dev->devt), MINOR(dev->devt));
		वापस err;
	पूर्ण
	clk->cdev.owner = clk->ops.owner;
	clk->dev = dev;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(posix_घड़ी_रेजिस्टर);

व्योम posix_घड़ी_unरेजिस्टर(काष्ठा posix_घड़ी *clk)
अणु
	cdev_device_del(&clk->cdev, clk->dev);

	करोwn_ग_लिखो(&clk->rwsem);
	clk->zombie = true;
	up_ग_लिखो(&clk->rwsem);

	put_device(clk->dev);
पूर्ण
EXPORT_SYMBOL_GPL(posix_घड़ी_unरेजिस्टर);

काष्ठा posix_घड़ी_desc अणु
	काष्ठा file *fp;
	काष्ठा posix_घड़ी *clk;
पूर्ण;

अटल पूर्णांक get_घड़ी_desc(स्थिर घड़ीid_t id, काष्ठा posix_घड़ी_desc *cd)
अणु
	काष्ठा file *fp = fget(घड़ीid_to_fd(id));
	पूर्णांक err = -EINVAL;

	अगर (!fp)
		वापस err;

	अगर (fp->f_op->खोलो != posix_घड़ी_खोलो || !fp->निजी_data)
		जाओ out;

	cd->fp = fp;
	cd->clk = get_posix_घड़ी(fp);

	err = cd->clk ? 0 : -ENODEV;
out:
	अगर (err)
		fput(fp);
	वापस err;
पूर्ण

अटल व्योम put_घड़ी_desc(काष्ठा posix_घड़ी_desc *cd)
अणु
	put_posix_घड़ी(cd->clk);
	fput(cd->fp);
पूर्ण

अटल पूर्णांक pc_घड़ी_adjसमय(घड़ीid_t id, काष्ठा __kernel_समयx *tx)
अणु
	काष्ठा posix_घड़ी_desc cd;
	पूर्णांक err;

	err = get_घड़ी_desc(id, &cd);
	अगर (err)
		वापस err;

	अगर ((cd.fp->f_mode & FMODE_WRITE) == 0) अणु
		err = -EACCES;
		जाओ out;
	पूर्ण

	अगर (cd.clk->ops.घड़ी_adjसमय)
		err = cd.clk->ops.घड़ी_adjसमय(cd.clk, tx);
	अन्यथा
		err = -EOPNOTSUPP;
out:
	put_घड़ी_desc(&cd);

	वापस err;
पूर्ण

अटल पूर्णांक pc_घड़ी_समय_लो(घड़ीid_t id, काष्ठा बारpec64 *ts)
अणु
	काष्ठा posix_घड़ी_desc cd;
	पूर्णांक err;

	err = get_घड़ी_desc(id, &cd);
	अगर (err)
		वापस err;

	अगर (cd.clk->ops.घड़ी_समय_लो)
		err = cd.clk->ops.घड़ी_समय_लो(cd.clk, ts);
	अन्यथा
		err = -EOPNOTSUPP;

	put_घड़ी_desc(&cd);

	वापस err;
पूर्ण

अटल पूर्णांक pc_घड़ी_getres(घड़ीid_t id, काष्ठा बारpec64 *ts)
अणु
	काष्ठा posix_घड़ी_desc cd;
	पूर्णांक err;

	err = get_घड़ी_desc(id, &cd);
	अगर (err)
		वापस err;

	अगर (cd.clk->ops.घड़ी_getres)
		err = cd.clk->ops.घड़ी_getres(cd.clk, ts);
	अन्यथा
		err = -EOPNOTSUPP;

	put_घड़ी_desc(&cd);

	वापस err;
पूर्ण

अटल पूर्णांक pc_घड़ी_समय_रखो(घड़ीid_t id, स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा posix_घड़ी_desc cd;
	पूर्णांक err;

	err = get_घड़ी_desc(id, &cd);
	अगर (err)
		वापस err;

	अगर ((cd.fp->f_mode & FMODE_WRITE) == 0) अणु
		err = -EACCES;
		जाओ out;
	पूर्ण

	अगर (cd.clk->ops.घड़ी_समय_रखो)
		err = cd.clk->ops.घड़ी_समय_रखो(cd.clk, ts);
	अन्यथा
		err = -EOPNOTSUPP;
out:
	put_घड़ी_desc(&cd);

	वापस err;
पूर्ण

स्थिर काष्ठा k_घड़ी घड़ी_posix_dynamic = अणु
	.घड़ी_getres		= pc_घड़ी_getres,
	.घड़ी_set		= pc_घड़ी_समय_रखो,
	.घड़ी_get_बारpec	= pc_घड़ी_समय_लो,
	.घड़ी_adj		= pc_घड़ी_adjसमय,
पूर्ण;
