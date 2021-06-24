<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux/SPARC PROM Configuration Driver
 * Copyright (C) 1996 Thomas K. Dyas (tdyas@noc.rutgers.edu)
 * Copyright (C) 1996 Eddie C. Dost  (ecd@skynet.be)
 *
 * This अक्षरacter device driver allows user programs to access the
 * PROM device tree. It is compatible with the SunOS /dev/खोलोprom
 * driver and the NetBSD /dev/खोलोprom driver. The SunOS eeprom
 * utility works without any modअगरications.
 *
 * The driver uses a minor number under the misc device major. The
 * file पढ़ो/ग_लिखो mode determines the type of access to the PROM.
 * Interrupts are disabled whenever the driver calls पूर्णांकo the PROM क्रम
 * sanity's sake.
 */


#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/माला.स>
#समावेश <linux/miscdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/prom.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/खोलोpromपन.स>
#अगर_घोषित CONFIG_PCI
#समावेश <linux/pci.h>
#पूर्ण_अगर

MODULE_AUTHOR("Thomas K. Dyas (tdyas@noc.rutgers.edu) and Eddie C. Dost  (ecd@skynet.be)");
MODULE_DESCRIPTION("OPENPROM Configuration Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
MODULE_ALIAS_MISCDEV(SUN_OPENPROM_MINOR);

/* Private data kept by the driver क्रम each descriptor. */
प्रकार काष्ठा खोलोprom_निजी_data
अणु
	काष्ठा device_node *current_node; /* Current node क्रम SunOS ioctls. */
	काष्ठा device_node *lastnode; /* Last valid node used by BSD ioctls. */
पूर्ण DATA;

/* ID of the PROM node containing all of the EEPROM options. */
अटल DEFINE_MUTEX(खोलोprom_mutex);
अटल काष्ठा device_node *options_node;

/*
 * Copy an खोलोpromio काष्ठाure पूर्णांकo kernel space from user space.
 * This routine करोes error checking to make sure that all memory
 * accesses are within bounds. A poपूर्णांकer to the allocated खोलोpromio
 * काष्ठाure will be placed in "*opp_p". Return value is the length
 * of the user supplied buffer.
 */
अटल पूर्णांक copyin(काष्ठा खोलोpromio __user *info, काष्ठा खोलोpromio **opp_p)
अणु
	अचिन्हित पूर्णांक bufsize;

	अगर (!info || !opp_p)
		वापस -EFAULT;

	अगर (get_user(bufsize, &info->oprom_size))
		वापस -EFAULT;

	अगर (bufsize == 0)
		वापस -EINVAL;

	/* If the bufsize is too large, just limit it.
	 * Fix from Jason Rappleye.
	 */
	अगर (bufsize > OPROMMAXPARAM)
		bufsize = OPROMMAXPARAM;

	अगर (!(*opp_p = kzalloc(माप(पूर्णांक) + bufsize + 1, GFP_KERNEL)))
		वापस -ENOMEM;

	अगर (copy_from_user(&(*opp_p)->oprom_array,
			   &info->oprom_array, bufsize)) अणु
		kमुक्त(*opp_p);
		वापस -EFAULT;
	पूर्ण
	वापस bufsize;
पूर्ण

अटल पूर्णांक माला_लोtrings(काष्ठा खोलोpromio __user *info, काष्ठा खोलोpromio **opp_p)
अणु
	पूर्णांक n, bufsize;
	अक्षर c;

	अगर (!info || !opp_p)
		वापस -EFAULT;

	अगर (!(*opp_p = kzalloc(माप(पूर्णांक) + OPROMMAXPARAM + 1, GFP_KERNEL)))
		वापस -ENOMEM;

	(*opp_p)->oprom_size = 0;

	n = bufsize = 0;
	जबतक ((n < 2) && (bufsize < OPROMMAXPARAM)) अणु
		अगर (get_user(c, &info->oprom_array[bufsize])) अणु
			kमुक्त(*opp_p);
			वापस -EFAULT;
		पूर्ण
		अगर (c == '\0')
			n++;
		(*opp_p)->oprom_array[bufsize++] = c;
	पूर्ण
	अगर (!n) अणु
		kमुक्त(*opp_p);
		वापस -EINVAL;
	पूर्ण
	वापस bufsize;
पूर्ण

/*
 * Copy an खोलोpromio काष्ठाure in kernel space back to user space.
 */
अटल पूर्णांक copyout(व्योम __user *info, काष्ठा खोलोpromio *opp, पूर्णांक len)
अणु
	अगर (copy_to_user(info, opp, len))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक opromgetprop(व्योम __user *argp, काष्ठा device_node *dp, काष्ठा खोलोpromio *op, पूर्णांक bufsize)
अणु
	स्थिर व्योम *pval;
	पूर्णांक len;

	अगर (!dp ||
	    !(pval = of_get_property(dp, op->oprom_array, &len)) ||
	    len <= 0 || len > bufsize)
		वापस copyout(argp, op, माप(पूर्णांक));

	स_नकल(op->oprom_array, pval, len);
	op->oprom_array[len] = '\0';
	op->oprom_size = len;

	वापस copyout(argp, op, माप(पूर्णांक) + bufsize);
पूर्ण

अटल पूर्णांक opromnxtprop(व्योम __user *argp, काष्ठा device_node *dp, काष्ठा खोलोpromio *op, पूर्णांक bufsize)
अणु
	काष्ठा property *prop;
	पूर्णांक len;

	अगर (!dp)
		वापस copyout(argp, op, माप(पूर्णांक));
	अगर (op->oprom_array[0] == '\0') अणु
		prop = dp->properties;
		अगर (!prop)
			वापस copyout(argp, op, माप(पूर्णांक));
		len = म_माप(prop->name);
	पूर्ण अन्यथा अणु
		prop = of_find_property(dp, op->oprom_array, शून्य);

		अगर (!prop ||
		    !prop->next ||
		    (len = म_माप(prop->next->name)) + 1 > bufsize)
			वापस copyout(argp, op, माप(पूर्णांक));

		prop = prop->next;
	पूर्ण

	स_नकल(op->oprom_array, prop->name, len);
	op->oprom_array[len] = '\0';
	op->oprom_size = ++len;

	वापस copyout(argp, op, माप(पूर्णांक) + bufsize);
पूर्ण

अटल पूर्णांक opromsetopt(काष्ठा device_node *dp, काष्ठा खोलोpromio *op, पूर्णांक bufsize)
अणु
	अक्षर *buf = op->oprom_array + म_माप(op->oprom_array) + 1;
	पूर्णांक len = op->oprom_array + bufsize - buf;

	वापस of_set_property(options_node, op->oprom_array, buf, len);
पूर्ण

अटल पूर्णांक opromnext(व्योम __user *argp, अचिन्हित पूर्णांक cmd, काष्ठा device_node *dp, काष्ठा खोलोpromio *op, पूर्णांक bufsize, DATA *data)
अणु
	phandle ph;

	BUILD_BUG_ON(माप(phandle) != माप(पूर्णांक));

	अगर (bufsize < माप(phandle))
		वापस -EINVAL;

	ph = *((पूर्णांक *) op->oprom_array);
	अगर (ph) अणु
		dp = of_find_node_by_phandle(ph);
		अगर (!dp)
			वापस -EINVAL;

		चयन (cmd) अणु
		हाल OPROMNEXT:
			dp = dp->sibling;
			अवरोध;

		हाल OPROMCHILD:
			dp = dp->child;
			अवरोध;

		हाल OPROMSETCUR:
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Sibling of node zero is the root node.  */
		अगर (cmd != OPROMNEXT)
			वापस -EINVAL;

		dp = of_find_node_by_path("/");
	पूर्ण

	ph = 0;
	अगर (dp)
		ph = dp->phandle;

	data->current_node = dp;
	*((पूर्णांक *) op->oprom_array) = ph;
	op->oprom_size = माप(phandle);

	वापस copyout(argp, op, bufsize + माप(पूर्णांक));
पूर्ण

अटल पूर्णांक oprompci2node(व्योम __user *argp, काष्ठा device_node *dp, काष्ठा खोलोpromio *op, पूर्णांक bufsize, DATA *data)
अणु
	पूर्णांक err = -EINVAL;

	अगर (bufsize >= 2*माप(पूर्णांक)) अणु
#अगर_घोषित CONFIG_PCI
		काष्ठा pci_dev *pdev;
		काष्ठा device_node *dp;

		pdev = pci_get_करोमुख्य_bus_and_slot(0,
						((पूर्णांक *) op->oprom_array)[0],
						((पूर्णांक *) op->oprom_array)[1]);

		dp = pci_device_to_OF_node(pdev);
		data->current_node = dp;
		*((पूर्णांक *)op->oprom_array) = dp->phandle;
		op->oprom_size = माप(पूर्णांक);
		err = copyout(argp, op, bufsize + माप(पूर्णांक));

		pci_dev_put(pdev);
#पूर्ण_अगर
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक oprompath2node(व्योम __user *argp, काष्ठा device_node *dp, काष्ठा खोलोpromio *op, पूर्णांक bufsize, DATA *data)
अणु
	phandle ph = 0;

	dp = of_find_node_by_path(op->oprom_array);
	अगर (dp)
		ph = dp->phandle;
	data->current_node = dp;
	*((पूर्णांक *)op->oprom_array) = ph;
	op->oprom_size = माप(पूर्णांक);

	वापस copyout(argp, op, bufsize + माप(पूर्णांक));
पूर्ण

अटल पूर्णांक opromgetbootargs(व्योम __user *argp, काष्ठा खोलोpromio *op, पूर्णांक bufsize)
अणु
	अक्षर *buf = saved_command_line;
	पूर्णांक len = म_माप(buf);

	अगर (len > bufsize)
		वापस -EINVAL;

	म_नकल(op->oprom_array, buf);
	op->oprom_size = len;

	वापस copyout(argp, op, bufsize + माप(पूर्णांक));
पूर्ण

/*
 *	SunOS and Solaris /dev/खोलोprom ioctl calls.
 */
अटल दीर्घ खोलोprom_sunos_ioctl(काष्ठा file * file,
				 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg,
				 काष्ठा device_node *dp)
अणु
	DATA *data = file->निजी_data;
	काष्ठा खोलोpromio *opp = शून्य;
	पूर्णांक bufsize, error = 0;
	अटल पूर्णांक cnt;
	व्योम __user *argp = (व्योम __user *)arg;

	अगर (cmd == OPROMSETOPT)
		bufsize = माला_लोtrings(argp, &opp);
	अन्यथा
		bufsize = copyin(argp, &opp);

	अगर (bufsize < 0)
		वापस bufsize;

	mutex_lock(&खोलोprom_mutex);

	चयन (cmd) अणु
	हाल OPROMGETOPT:
	हाल OPROMGETPROP:
		error = opromgetprop(argp, dp, opp, bufsize);
		अवरोध;

	हाल OPROMNXTOPT:
	हाल OPROMNXTPROP:
		error = opromnxtprop(argp, dp, opp, bufsize);
		अवरोध;

	हाल OPROMSETOPT:
	हाल OPROMSETOPT2:
		error = opromsetopt(dp, opp, bufsize);
		अवरोध;

	हाल OPROMNEXT:
	हाल OPROMCHILD:
	हाल OPROMSETCUR:
		error = opromnext(argp, cmd, dp, opp, bufsize, data);
		अवरोध;

	हाल OPROMPCI2NODE:
		error = oprompci2node(argp, dp, opp, bufsize, data);
		अवरोध;

	हाल OPROMPATH2NODE:
		error = oprompath2node(argp, dp, opp, bufsize, data);
		अवरोध;

	हाल OPROMGETBOOTARGS:
		error = opromgetbootargs(argp, opp, bufsize);
		अवरोध;

	हाल OPROMU2P:
	हाल OPROMGETCONS:
	हाल OPROMGETFBNAME:
		अगर (cnt++ < 10)
			prपूर्णांकk(KERN_INFO "openprom_sunos_ioctl: unimplemented ioctl\n");
		error = -EINVAL;
		अवरोध;
	शेष:
		अगर (cnt++ < 10)
			prपूर्णांकk(KERN_INFO "openprom_sunos_ioctl: cmd 0x%X, arg 0x%lX\n", cmd, arg);
		error = -EINVAL;
		अवरोध;
	पूर्ण

	kमुक्त(opp);
	mutex_unlock(&खोलोprom_mutex);

	वापस error;
पूर्ण

अटल काष्ठा device_node *get_node(phandle n, DATA *data)
अणु
	काष्ठा device_node *dp = of_find_node_by_phandle(n);

	अगर (dp)
		data->lastnode = dp;

	वापस dp;
पूर्ण

/* Copy in a whole string from userspace पूर्णांकo kernelspace. */
अटल अक्षर * copyin_string(अक्षर __user *user, माप_प्रकार len)
अणु
	अगर ((sमाप_प्रकार)len < 0 || (sमाप_प्रकार)(len + 1) < 0)
		वापस ERR_PTR(-EINVAL);

	वापस memdup_user_nul(user, len);
पूर्ण

/*
 *	NetBSD /dev/खोलोprom ioctl calls.
 */
अटल पूर्णांक opiocget(व्योम __user *argp, DATA *data)
अणु
	काष्ठा opiocdesc op;
	काष्ठा device_node *dp;
	अक्षर *str;
	स्थिर व्योम *pval;
	पूर्णांक err, len;

	अगर (copy_from_user(&op, argp, माप(op)))
		वापस -EFAULT;

	dp = get_node(op.op_nodeid, data);

	str = copyin_string(op.op_name, op.op_namelen);
	अगर (IS_ERR(str))
		वापस PTR_ERR(str);

	pval = of_get_property(dp, str, &len);
	err = 0;
	अगर (!pval || len > op.op_buflen) अणु
		err = -EINVAL;
	पूर्ण अन्यथा अणु
		op.op_buflen = len;
		अगर (copy_to_user(argp, &op, माप(op)) ||
		    copy_to_user(op.op_buf, pval, len))
			err = -EFAULT;
	पूर्ण
	kमुक्त(str);

	वापस err;
पूर्ण

अटल पूर्णांक opiocnextprop(व्योम __user *argp, DATA *data)
अणु
	काष्ठा opiocdesc op;
	काष्ठा device_node *dp;
	काष्ठा property *prop;
	अक्षर *str;
	पूर्णांक len;

	अगर (copy_from_user(&op, argp, माप(op)))
		वापस -EFAULT;

	dp = get_node(op.op_nodeid, data);
	अगर (!dp)
		वापस -EINVAL;

	str = copyin_string(op.op_name, op.op_namelen);
	अगर (IS_ERR(str))
		वापस PTR_ERR(str);

	अगर (str[0] == '\0') अणु
		prop = dp->properties;
	पूर्ण अन्यथा अणु
		prop = of_find_property(dp, str, शून्य);
		अगर (prop)
			prop = prop->next;
	पूर्ण
	kमुक्त(str);

	अगर (!prop)
		len = 0;
	अन्यथा
		len = prop->length;

	अगर (len > op.op_buflen)
		len = op.op_buflen;

	अगर (copy_to_user(argp, &op, माप(op)))
		वापस -EFAULT;

	अगर (len &&
	    copy_to_user(op.op_buf, prop->value, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक opiocset(व्योम __user *argp, DATA *data)
अणु
	काष्ठा opiocdesc op;
	काष्ठा device_node *dp;
	अक्षर *str, *पंचांगp;
	पूर्णांक err;

	अगर (copy_from_user(&op, argp, माप(op)))
		वापस -EFAULT;

	dp = get_node(op.op_nodeid, data);
	अगर (!dp)
		वापस -EINVAL;

	str = copyin_string(op.op_name, op.op_namelen);
	अगर (IS_ERR(str))
		वापस PTR_ERR(str);

	पंचांगp = copyin_string(op.op_buf, op.op_buflen);
	अगर (IS_ERR(पंचांगp)) अणु
		kमुक्त(str);
		वापस PTR_ERR(पंचांगp);
	पूर्ण

	err = of_set_property(dp, str, पंचांगp, op.op_buflen);

	kमुक्त(str);
	kमुक्त(पंचांगp);

	वापस err;
पूर्ण

अटल पूर्णांक opiocgetnext(अचिन्हित पूर्णांक cmd, व्योम __user *argp)
अणु
	काष्ठा device_node *dp;
	phandle nd;

	BUILD_BUG_ON(माप(phandle) != माप(पूर्णांक));

	अगर (copy_from_user(&nd, argp, माप(phandle)))
		वापस -EFAULT;

	अगर (nd == 0) अणु
		अगर (cmd != OPIOCGETNEXT)
			वापस -EINVAL;
		dp = of_find_node_by_path("/");
	पूर्ण अन्यथा अणु
		dp = of_find_node_by_phandle(nd);
		nd = 0;
		अगर (dp) अणु
			अगर (cmd == OPIOCGETNEXT)
				dp = dp->sibling;
			अन्यथा
				dp = dp->child;
		पूर्ण
	पूर्ण
	अगर (dp)
		nd = dp->phandle;
	अगर (copy_to_user(argp, &nd, माप(phandle)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक खोलोprom_bsd_ioctl(काष्ठा file * file,
			      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	DATA *data = file->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक err;

	mutex_lock(&खोलोprom_mutex);
	चयन (cmd) अणु
	हाल OPIOCGET:
		err = opiocget(argp, data);
		अवरोध;

	हाल OPIOCNEXTPROP:
		err = opiocnextprop(argp, data);
		अवरोध;

	हाल OPIOCSET:
		err = opiocset(argp, data);
		अवरोध;

	हाल OPIOCGETOPTNODE:
		BUILD_BUG_ON(माप(phandle) != माप(पूर्णांक));

		err = 0;
		अगर (copy_to_user(argp, &options_node->phandle, माप(phandle)))
			err = -EFAULT;
		अवरोध;

	हाल OPIOCGETNEXT:
	हाल OPIOCGETCHILD:
		err = opiocgetnext(cmd, argp);
		अवरोध;

	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण
	mutex_unlock(&खोलोprom_mutex);

	वापस err;
पूर्ण


/*
 *	Hanकरोff control to the correct ioctl handler.
 */
अटल दीर्घ खोलोprom_ioctl(काष्ठा file * file,
			   अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	DATA *data = file->निजी_data;

	चयन (cmd) अणु
	हाल OPROMGETOPT:
	हाल OPROMNXTOPT:
		अगर ((file->f_mode & FMODE_READ) == 0)
			वापस -EPERM;
		वापस खोलोprom_sunos_ioctl(file, cmd, arg,
					    options_node);

	हाल OPROMSETOPT:
	हाल OPROMSETOPT2:
		अगर ((file->f_mode & FMODE_WRITE) == 0)
			वापस -EPERM;
		वापस खोलोprom_sunos_ioctl(file, cmd, arg,
					    options_node);

	हाल OPROMNEXT:
	हाल OPROMCHILD:
	हाल OPROMGETPROP:
	हाल OPROMNXTPROP:
		अगर ((file->f_mode & FMODE_READ) == 0)
			वापस -EPERM;
		वापस खोलोprom_sunos_ioctl(file, cmd, arg,
					    data->current_node);

	हाल OPROMU2P:
	हाल OPROMGETCONS:
	हाल OPROMGETFBNAME:
	हाल OPROMGETBOOTARGS:
	हाल OPROMSETCUR:
	हाल OPROMPCI2NODE:
	हाल OPROMPATH2NODE:
		अगर ((file->f_mode & FMODE_READ) == 0)
			वापस -EPERM;
		वापस खोलोprom_sunos_ioctl(file, cmd, arg, शून्य);

	हाल OPIOCGET:
	हाल OPIOCNEXTPROP:
	हाल OPIOCGETOPTNODE:
	हाल OPIOCGETNEXT:
	हाल OPIOCGETCHILD:
		अगर ((file->f_mode & FMODE_READ) == 0)
			वापस -EBADF;
		वापस खोलोprom_bsd_ioctl(file,cmd,arg);

	हाल OPIOCSET:
		अगर ((file->f_mode & FMODE_WRITE) == 0)
			वापस -EBADF;
		वापस खोलोprom_bsd_ioctl(file,cmd,arg);

	शेष:
		वापस -EINVAL;
	पूर्ण;
पूर्ण

अटल दीर्घ खोलोprom_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
		अचिन्हित दीर्घ arg)
अणु
	दीर्घ rval = -ENOTTY;

	/*
	 * SunOS/Solaris only, the NetBSD one's have embedded poपूर्णांकers in
	 * the arg which we'd need to clean up...
	 */
	चयन (cmd) अणु
	हाल OPROMGETOPT:
	हाल OPROMSETOPT:
	हाल OPROMNXTOPT:
	हाल OPROMSETOPT2:
	हाल OPROMNEXT:
	हाल OPROMCHILD:
	हाल OPROMGETPROP:
	हाल OPROMNXTPROP:
	हाल OPROMU2P:
	हाल OPROMGETCONS:
	हाल OPROMGETFBNAME:
	हाल OPROMGETBOOTARGS:
	हाल OPROMSETCUR:
	हाल OPROMPCI2NODE:
	हाल OPROMPATH2NODE:
		rval = खोलोprom_ioctl(file, cmd, arg);
		अवरोध;
	पूर्ण

	वापस rval;
पूर्ण

अटल पूर्णांक खोलोprom_खोलो(काष्ठा inode * inode, काष्ठा file * file)
अणु
	DATA *data;

	data = kदो_स्मृति(माप(DATA), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	mutex_lock(&खोलोprom_mutex);
	data->current_node = of_find_node_by_path("/");
	data->lastnode = data->current_node;
	file->निजी_data = (व्योम *) data;
	mutex_unlock(&खोलोprom_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक खोलोprom_release(काष्ठा inode * inode, काष्ठा file * file)
अणु
	kमुक्त(file->निजी_data);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations खोलोprom_fops = अणु
	.owner =	THIS_MODULE,
	.llseek =	no_llseek,
	.unlocked_ioctl = खोलोprom_ioctl,
	.compat_ioctl =	खोलोprom_compat_ioctl,
	.खोलो =		खोलोprom_खोलो,
	.release =	खोलोprom_release,
पूर्ण;

अटल काष्ठा miscdevice खोलोprom_dev = अणु
	.minor		= SUN_OPENPROM_MINOR,
	.name		= "openprom",
	.fops		= &खोलोprom_fops,
पूर्ण;

अटल पूर्णांक __init खोलोprom_init(व्योम)
अणु
	पूर्णांक err;

	err = misc_रेजिस्टर(&खोलोprom_dev);
	अगर (err)
		वापस err;

	options_node = of_get_child_by_name(of_find_node_by_path("/"), "options");
	अगर (!options_node) अणु
		misc_deरेजिस्टर(&खोलोprom_dev);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास खोलोprom_cleanup(व्योम)
अणु
	misc_deरेजिस्टर(&खोलोprom_dev);
पूर्ण

module_init(खोलोprom_init);
module_निकास(खोलोprom_cleanup);
