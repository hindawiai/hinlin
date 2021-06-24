<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/slab.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/spinlock.h>
#समावेश <net/ax25.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>

ax25_dev *ax25_dev_list;
DEFINE_SPINLOCK(ax25_dev_lock);

ax25_dev *ax25_addr_ax25dev(ax25_address *addr)
अणु
	ax25_dev *ax25_dev, *res = शून्य;

	spin_lock_bh(&ax25_dev_lock);
	क्रम (ax25_dev = ax25_dev_list; ax25_dev != शून्य; ax25_dev = ax25_dev->next)
		अगर (ax25cmp(addr, (ax25_address *)ax25_dev->dev->dev_addr) == 0) अणु
			res = ax25_dev;
		पूर्ण
	spin_unlock_bh(&ax25_dev_lock);

	वापस res;
पूर्ण

/*
 *	This is called when an पूर्णांकerface is brought up. These are
 *	reasonable शेषs.
 */
व्योम ax25_dev_device_up(काष्ठा net_device *dev)
अणु
	ax25_dev *ax25_dev;

	अगर ((ax25_dev = kzalloc(माप(*ax25_dev), GFP_ATOMIC)) == शून्य) अणु
		prपूर्णांकk(KERN_ERR "AX.25: ax25_dev_device_up - out of memory\n");
		वापस;
	पूर्ण

	dev->ax25_ptr     = ax25_dev;
	ax25_dev->dev     = dev;
	dev_hold(dev);
	ax25_dev->क्रमward = शून्य;

	ax25_dev->values[AX25_VALUES_IPDEFMODE] = AX25_DEF_IPDEFMODE;
	ax25_dev->values[AX25_VALUES_AXDEFMODE] = AX25_DEF_AXDEFMODE;
	ax25_dev->values[AX25_VALUES_BACKOFF]   = AX25_DEF_BACKOFF;
	ax25_dev->values[AX25_VALUES_CONMODE]   = AX25_DEF_CONMODE;
	ax25_dev->values[AX25_VALUES_WINDOW]    = AX25_DEF_WINDOW;
	ax25_dev->values[AX25_VALUES_EWINDOW]   = AX25_DEF_EWINDOW;
	ax25_dev->values[AX25_VALUES_T1]        = AX25_DEF_T1;
	ax25_dev->values[AX25_VALUES_T2]        = AX25_DEF_T2;
	ax25_dev->values[AX25_VALUES_T3]        = AX25_DEF_T3;
	ax25_dev->values[AX25_VALUES_IDLE]	= AX25_DEF_IDLE;
	ax25_dev->values[AX25_VALUES_N2]        = AX25_DEF_N2;
	ax25_dev->values[AX25_VALUES_PACLEN]	= AX25_DEF_PACLEN;
	ax25_dev->values[AX25_VALUES_PROTOCOL]  = AX25_DEF_PROTOCOL;
	ax25_dev->values[AX25_VALUES_DS_TIMEOUT]= AX25_DEF_DS_TIMEOUT;

#अगर defined(CONFIG_AX25_DAMA_SLAVE) || defined(CONFIG_AX25_DAMA_MASTER)
	ax25_ds_setup_समयr(ax25_dev);
#पूर्ण_अगर

	spin_lock_bh(&ax25_dev_lock);
	ax25_dev->next = ax25_dev_list;
	ax25_dev_list  = ax25_dev;
	spin_unlock_bh(&ax25_dev_lock);

	ax25_रेजिस्टर_dev_sysctl(ax25_dev);
पूर्ण

व्योम ax25_dev_device_करोwn(काष्ठा net_device *dev)
अणु
	ax25_dev *s, *ax25_dev;

	अगर ((ax25_dev = ax25_dev_ax25dev(dev)) == शून्य)
		वापस;

	ax25_unरेजिस्टर_dev_sysctl(ax25_dev);

	spin_lock_bh(&ax25_dev_lock);

#अगर_घोषित CONFIG_AX25_DAMA_SLAVE
	ax25_ds_del_समयr(ax25_dev);
#पूर्ण_अगर

	/*
	 *	Remove any packet क्रमwarding that poपूर्णांकs to this device.
	 */
	क्रम (s = ax25_dev_list; s != शून्य; s = s->next)
		अगर (s->क्रमward == dev)
			s->क्रमward = शून्य;

	अगर ((s = ax25_dev_list) == ax25_dev) अणु
		ax25_dev_list = s->next;
		spin_unlock_bh(&ax25_dev_lock);
		dev->ax25_ptr = शून्य;
		dev_put(dev);
		kमुक्त(ax25_dev);
		वापस;
	पूर्ण

	जबतक (s != शून्य && s->next != शून्य) अणु
		अगर (s->next == ax25_dev) अणु
			s->next = ax25_dev->next;
			spin_unlock_bh(&ax25_dev_lock);
			dev->ax25_ptr = शून्य;
			dev_put(dev);
			kमुक्त(ax25_dev);
			वापस;
		पूर्ण

		s = s->next;
	पूर्ण
	spin_unlock_bh(&ax25_dev_lock);
	dev->ax25_ptr = शून्य;
पूर्ण

पूर्णांक ax25_fwd_ioctl(अचिन्हित पूर्णांक cmd, काष्ठा ax25_fwd_काष्ठा *fwd)
अणु
	ax25_dev *ax25_dev, *fwd_dev;

	अगर ((ax25_dev = ax25_addr_ax25dev(&fwd->port_from)) == शून्य)
		वापस -EINVAL;

	चयन (cmd) अणु
	हाल SIOCAX25ADDFWD:
		अगर ((fwd_dev = ax25_addr_ax25dev(&fwd->port_to)) == शून्य)
			वापस -EINVAL;
		अगर (ax25_dev->क्रमward != शून्य)
			वापस -EINVAL;
		ax25_dev->क्रमward = fwd_dev->dev;
		अवरोध;

	हाल SIOCAX25DELFWD:
		अगर (ax25_dev->क्रमward == शून्य)
			वापस -EINVAL;
		ax25_dev->क्रमward = शून्य;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा net_device *ax25_fwd_dev(काष्ठा net_device *dev)
अणु
	ax25_dev *ax25_dev;

	अगर ((ax25_dev = ax25_dev_ax25dev(dev)) == शून्य)
		वापस dev;

	अगर (ax25_dev->क्रमward == शून्य)
		वापस dev;

	वापस ax25_dev->क्रमward;
पूर्ण

/*
 *	Free all memory associated with device काष्ठाures.
 */
व्योम __निकास ax25_dev_मुक्त(व्योम)
अणु
	ax25_dev *s, *ax25_dev;

	spin_lock_bh(&ax25_dev_lock);
	ax25_dev = ax25_dev_list;
	जबतक (ax25_dev != शून्य) अणु
		s        = ax25_dev;
		dev_put(ax25_dev->dev);
		ax25_dev = ax25_dev->next;
		kमुक्त(s);
	पूर्ण
	ax25_dev_list = शून्य;
	spin_unlock_bh(&ax25_dev_lock);
पूर्ण
