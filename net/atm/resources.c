<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* net/aपंचांग/resources.c - Statically allocated resources */

/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */

/* Fixes
 * Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 * 2002/01 - करोn't मुक्त the whole काष्ठा sock on sk->deकाष्ठा समय,
 * 	     use the शेष deकाष्ठा function initialized by sock_init_data */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s: " fmt, __func__

#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/sonet.h>
#समावेश <linux/kernel.h> /* क्रम barrier */
#समावेश <linux/module.h>
#समावेश <linux/bitops.h>
#समावेश <linux/capability.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>

#समावेश <net/sock.h>	 /* क्रम काष्ठा sock */

#समावेश "common.h"
#समावेश "resources.h"
#समावेश "addr.h"


LIST_HEAD(aपंचांग_devs);
DEFINE_MUTEX(aपंचांग_dev_mutex);

अटल काष्ठा aपंचांग_dev *__alloc_aपंचांग_dev(स्थिर अक्षर *type)
अणु
	काष्ठा aपंचांग_dev *dev;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस शून्य;
	dev->type = type;
	dev->संकेत = ATM_PHY_SIG_UNKNOWN;
	dev->link_rate = ATM_OC3_PCR;
	spin_lock_init(&dev->lock);
	INIT_LIST_HEAD(&dev->local);
	INIT_LIST_HEAD(&dev->lecs);

	वापस dev;
पूर्ण

अटल काष्ठा aपंचांग_dev *__aपंचांग_dev_lookup(पूर्णांक number)
अणु
	काष्ठा aपंचांग_dev *dev;
	काष्ठा list_head *p;

	list_क्रम_each(p, &aपंचांग_devs) अणु
		dev = list_entry(p, काष्ठा aपंचांग_dev, dev_list);
		अगर (dev->number == number) अणु
			aपंचांग_dev_hold(dev);
			वापस dev;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा aपंचांग_dev *aपंचांग_dev_lookup(पूर्णांक number)
अणु
	काष्ठा aपंचांग_dev *dev;

	mutex_lock(&aपंचांग_dev_mutex);
	dev = __aपंचांग_dev_lookup(number);
	mutex_unlock(&aपंचांग_dev_mutex);
	वापस dev;
पूर्ण
EXPORT_SYMBOL(aपंचांग_dev_lookup);

काष्ठा aपंचांग_dev *aपंचांग_dev_रेजिस्टर(स्थिर अक्षर *type, काष्ठा device *parent,
				 स्थिर काष्ठा aपंचांगdev_ops *ops, पूर्णांक number,
				 अचिन्हित दीर्घ *flags)
अणु
	काष्ठा aपंचांग_dev *dev, *inuse;

	dev = __alloc_aपंचांग_dev(type);
	अगर (!dev) अणु
		pr_err("no space for dev %s\n", type);
		वापस शून्य;
	पूर्ण
	mutex_lock(&aपंचांग_dev_mutex);
	अगर (number != -1) अणु
		inuse = __aपंचांग_dev_lookup(number);
		अगर (inuse) अणु
			aपंचांग_dev_put(inuse);
			mutex_unlock(&aपंचांग_dev_mutex);
			kमुक्त(dev);
			वापस शून्य;
		पूर्ण
		dev->number = number;
	पूर्ण अन्यथा अणु
		dev->number = 0;
		जबतक ((inuse = __aपंचांग_dev_lookup(dev->number))) अणु
			aपंचांग_dev_put(inuse);
			dev->number++;
		पूर्ण
	पूर्ण

	dev->ops = ops;
	अगर (flags)
		dev->flags = *flags;
	अन्यथा
		स_रखो(&dev->flags, 0, माप(dev->flags));
	स_रखो(&dev->stats, 0, माप(dev->stats));
	refcount_set(&dev->refcnt, 1);

	अगर (aपंचांग_proc_dev_रेजिस्टर(dev) < 0) अणु
		pr_err("atm_proc_dev_register failed for dev %s\n", type);
		जाओ out_fail;
	पूर्ण

	अगर (aपंचांग_रेजिस्टर_sysfs(dev, parent) < 0) अणु
		pr_err("atm_register_sysfs failed for dev %s\n", type);
		aपंचांग_proc_dev_deरेजिस्टर(dev);
		जाओ out_fail;
	पूर्ण

	list_add_tail(&dev->dev_list, &aपंचांग_devs);

out:
	mutex_unlock(&aपंचांग_dev_mutex);
	वापस dev;

out_fail:
	kमुक्त(dev);
	dev = शून्य;
	जाओ out;
पूर्ण
EXPORT_SYMBOL(aपंचांग_dev_रेजिस्टर);

व्योम aपंचांग_dev_deरेजिस्टर(काष्ठा aपंचांग_dev *dev)
अणु
	BUG_ON(test_bit(ATM_DF_REMOVED, &dev->flags));
	set_bit(ATM_DF_REMOVED, &dev->flags);

	/*
	 * अगर we हटाओ current device from aपंचांग_devs list, new device
	 * with same number can appear, such we need deरेजिस्टर proc,
	 * release async all vccs and हटाओ them from vccs list too
	 */
	mutex_lock(&aपंचांग_dev_mutex);
	list_del(&dev->dev_list);
	mutex_unlock(&aपंचांग_dev_mutex);

	aपंचांग_dev_release_vccs(dev);
	aपंचांग_unरेजिस्टर_sysfs(dev);
	aपंचांग_proc_dev_deरेजिस्टर(dev);

	aपंचांग_dev_put(dev);
पूर्ण
EXPORT_SYMBOL(aपंचांग_dev_deरेजिस्टर);

अटल व्योम copy_aal_stats(काष्ठा k_aपंचांग_aal_stats *from,
    काष्ठा aपंचांग_aal_stats *to)
अणु
#घोषणा __HANDLE_ITEM(i) to->i = atomic_पढ़ो(&from->i)
	__AAL_STAT_ITEMS
#अघोषित __HANDLE_ITEM
पूर्ण

अटल व्योम subtract_aal_stats(काष्ठा k_aपंचांग_aal_stats *from,
    काष्ठा aपंचांग_aal_stats *to)
अणु
#घोषणा __HANDLE_ITEM(i) atomic_sub(to->i, &from->i)
	__AAL_STAT_ITEMS
#अघोषित __HANDLE_ITEM
पूर्ण

अटल पूर्णांक fetch_stats(काष्ठा aपंचांग_dev *dev, काष्ठा aपंचांग_dev_stats __user *arg,
		       पूर्णांक zero)
अणु
	काष्ठा aपंचांग_dev_stats पंचांगp;
	पूर्णांक error = 0;

	copy_aal_stats(&dev->stats.aal0, &पंचांगp.aal0);
	copy_aal_stats(&dev->stats.aal34, &पंचांगp.aal34);
	copy_aal_stats(&dev->stats.aal5, &पंचांगp.aal5);
	अगर (arg)
		error = copy_to_user(arg, &पंचांगp, माप(पंचांगp));
	अगर (zero && !error) अणु
		subtract_aal_stats(&dev->stats.aal0, &पंचांगp.aal0);
		subtract_aal_stats(&dev->stats.aal34, &पंचांगp.aal34);
		subtract_aal_stats(&dev->stats.aal5, &पंचांगp.aal5);
	पूर्ण
	वापस error ? -EFAULT : 0;
पूर्ण

पूर्णांक aपंचांग_getnames(व्योम __user *buf, पूर्णांक __user *iobuf_len)
अणु
	पूर्णांक error, len, size = 0;
	काष्ठा aपंचांग_dev *dev;
	काष्ठा list_head *p;
	पूर्णांक *पंचांगp_buf, *पंचांगp_p;

	अगर (get_user(len, iobuf_len))
		वापस -EFAULT;
	mutex_lock(&aपंचांग_dev_mutex);
	list_क्रम_each(p, &aपंचांग_devs)
		size += माप(पूर्णांक);
	अगर (size > len) अणु
		mutex_unlock(&aपंचांग_dev_mutex);
		वापस -E2BIG;
	पूर्ण
	पंचांगp_buf = kदो_स्मृति(size, GFP_ATOMIC);
	अगर (!पंचांगp_buf) अणु
		mutex_unlock(&aपंचांग_dev_mutex);
		वापस -ENOMEM;
	पूर्ण
	पंचांगp_p = पंचांगp_buf;
	list_क्रम_each(p, &aपंचांग_devs) अणु
		dev = list_entry(p, काष्ठा aपंचांग_dev, dev_list);
		*पंचांगp_p++ = dev->number;
	पूर्ण
	mutex_unlock(&aपंचांग_dev_mutex);
	error = ((copy_to_user(buf, पंचांगp_buf, size)) ||
		 put_user(size, iobuf_len))
		? -EFAULT : 0;
	kमुक्त(पंचांगp_buf);
	वापस error;
पूर्ण

पूर्णांक aपंचांग_dev_ioctl(अचिन्हित पूर्णांक cmd, व्योम __user *buf, पूर्णांक __user *sioc_len,
		  पूर्णांक number, पूर्णांक compat)
अणु
	पूर्णांक error, len, size = 0;
	काष्ठा aपंचांग_dev *dev;

	अगर (get_user(len, sioc_len))
		वापस -EFAULT;

	dev = try_then_request_module(aपंचांग_dev_lookup(number), "atm-device-%d",
				      number);
	अगर (!dev)
		वापस -ENODEV;

	चयन (cmd) अणु
	हाल ATM_GETTYPE:
		size = म_माप(dev->type) + 1;
		अगर (copy_to_user(buf, dev->type, size)) अणु
			error = -EFAULT;
			जाओ करोne;
		पूर्ण
		अवरोध;
	हाल ATM_GETESI:
		size = ESI_LEN;
		अगर (copy_to_user(buf, dev->esi, size)) अणु
			error = -EFAULT;
			जाओ करोne;
		पूर्ण
		अवरोध;
	हाल ATM_SETESI:
	अणु
		पूर्णांक i;

		क्रम (i = 0; i < ESI_LEN; i++)
			अगर (dev->esi[i]) अणु
				error = -EEXIST;
				जाओ करोne;
			पूर्ण
	पूर्ण
		fallthrough;
	हाल ATM_SETESIF:
	अणु
		अचिन्हित अक्षर esi[ESI_LEN];

		अगर (!capable(CAP_NET_ADMIN)) अणु
			error = -EPERM;
			जाओ करोne;
		पूर्ण
		अगर (copy_from_user(esi, buf, ESI_LEN)) अणु
			error = -EFAULT;
			जाओ करोne;
		पूर्ण
		स_नकल(dev->esi, esi, ESI_LEN);
		error =  ESI_LEN;
		जाओ करोne;
	पूर्ण
	हाल ATM_GETSTATZ:
		अगर (!capable(CAP_NET_ADMIN)) अणु
			error = -EPERM;
			जाओ करोne;
		पूर्ण
		fallthrough;
	हाल ATM_GETSTAT:
		size = माप(काष्ठा aपंचांग_dev_stats);
		error = fetch_stats(dev, buf, cmd == ATM_GETSTATZ);
		अगर (error)
			जाओ करोne;
		अवरोध;
	हाल ATM_GETCIRANGE:
		size = माप(काष्ठा aपंचांग_cirange);
		अगर (copy_to_user(buf, &dev->ci_range, size)) अणु
			error = -EFAULT;
			जाओ करोne;
		पूर्ण
		अवरोध;
	हाल ATM_GETLINKRATE:
		size = माप(पूर्णांक);
		अगर (copy_to_user(buf, &dev->link_rate, size)) अणु
			error = -EFAULT;
			जाओ करोne;
		पूर्ण
		अवरोध;
	हाल ATM_RSTADDR:
		अगर (!capable(CAP_NET_ADMIN)) अणु
			error = -EPERM;
			जाओ करोne;
		पूर्ण
		aपंचांग_reset_addr(dev, ATM_ADDR_LOCAL);
		अवरोध;
	हाल ATM_ADDADDR:
	हाल ATM_DELADDR:
	हाल ATM_ADDLECSADDR:
	हाल ATM_DELLECSADDR:
	अणु
		काष्ठा sockaddr_aपंचांगsvc addr;

		अगर (!capable(CAP_NET_ADMIN)) अणु
			error = -EPERM;
			जाओ करोne;
		पूर्ण

		अगर (copy_from_user(&addr, buf, माप(addr))) अणु
			error = -EFAULT;
			जाओ करोne;
		पूर्ण
		अगर (cmd == ATM_ADDADDR || cmd == ATM_ADDLECSADDR)
			error = aपंचांग_add_addr(dev, &addr,
					     (cmd == ATM_ADDADDR ?
					      ATM_ADDR_LOCAL : ATM_ADDR_LECS));
		अन्यथा
			error = aपंचांग_del_addr(dev, &addr,
					     (cmd == ATM_DELADDR ?
					      ATM_ADDR_LOCAL : ATM_ADDR_LECS));
		जाओ करोne;
	पूर्ण
	हाल ATM_GETADDR:
	हाल ATM_GETLECSADDR:
		error = aपंचांग_get_addr(dev, buf, len,
				     (cmd == ATM_GETADDR ?
				      ATM_ADDR_LOCAL : ATM_ADDR_LECS));
		अगर (error < 0)
			जाओ करोne;
		size = error;
		/* may वापस 0, but later on size == 0 means "करोn't
		   ग_लिखो the length" */
		error = put_user(size, sioc_len) ? -EFAULT : 0;
		जाओ करोne;
	हाल ATM_SETLOOP:
		अगर (__ATM_LM_XTRMT((पूर्णांक) (अचिन्हित दीर्घ) buf) &&
		    __ATM_LM_XTLOC((पूर्णांक) (अचिन्हित दीर्घ) buf) >
		    __ATM_LM_XTRMT((पूर्णांक) (अचिन्हित दीर्घ) buf)) अणु
			error = -EINVAL;
			जाओ करोne;
		पूर्ण
		fallthrough;
	हाल ATM_SETCIRANGE:
	हाल SONET_GETSTATZ:
	हाल SONET_SETDIAG:
	हाल SONET_CLRDIAG:
	हाल SONET_SETFRAMING:
		अगर (!capable(CAP_NET_ADMIN)) अणु
			error = -EPERM;
			जाओ करोne;
		पूर्ण
		fallthrough;
	शेष:
		अगर (IS_ENABLED(CONFIG_COMPAT) && compat) अणु
#अगर_घोषित CONFIG_COMPAT
			अगर (!dev->ops->compat_ioctl) अणु
				error = -EINVAL;
				जाओ करोne;
			पूर्ण
			size = dev->ops->compat_ioctl(dev, cmd, buf);
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			अगर (!dev->ops->ioctl) अणु
				error = -EINVAL;
				जाओ करोne;
			पूर्ण
			size = dev->ops->ioctl(dev, cmd, buf);
		पूर्ण
		अगर (size < 0) अणु
			error = (size == -ENOIOCTLCMD ? -ENOTTY : size);
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (size)
		error = put_user(size, sioc_len) ? -EFAULT : 0;
	अन्यथा
		error = 0;
करोne:
	aपंचांग_dev_put(dev);
	वापस error;
पूर्ण

व्योम *aपंचांग_dev_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	mutex_lock(&aपंचांग_dev_mutex);
	वापस seq_list_start_head(&aपंचांग_devs, *pos);
पूर्ण

व्योम aपंचांग_dev_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	mutex_unlock(&aपंचांग_dev_mutex);
पूर्ण

व्योम *aपंचांग_dev_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	वापस seq_list_next(v, &aपंचांग_devs, pos);
पूर्ण
