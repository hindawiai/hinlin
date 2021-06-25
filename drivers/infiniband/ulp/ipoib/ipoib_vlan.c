<शैली गुरु>
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/module.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <linux/init.h>
#समावेश <linux/seq_file.h>

#समावेश <linux/uaccess.h>

#समावेश "ipoib.h"

अटल sमाप_प्रकार show_parent(काष्ठा device *d, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा net_device *dev = to_net_dev(d);
	काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);

	वापस sysfs_emit(buf, "%s\n", priv->parent->name);
पूर्ण
अटल DEVICE_ATTR(parent, S_IRUGO, show_parent, शून्य);

अटल bool is_child_unique(काष्ठा ipoib_dev_priv *ppriv,
			    काष्ठा ipoib_dev_priv *priv)
अणु
	काष्ठा ipoib_dev_priv *tpriv;

	ASSERT_RTNL();

	/*
	 * Since the legacy sysfs पूर्णांकerface uses pkey क्रम deletion it cannot
	 * support more than one पूर्णांकerface with the same pkey, it creates
	 * ambiguity.  The RTNL पूर्णांकerface deletes using the netdev so it करोes
	 * not have a problem to support duplicated pkeys.
	 */
	अगर (priv->child_type != IPOIB_LEGACY_CHILD)
		वापस true;

	/*
	 * First ensure this isn't a duplicate. We check the parent device and
	 * then all of the legacy child पूर्णांकerfaces to make sure the Pkey
	 * करोesn't match.
	 */
	अगर (ppriv->pkey == priv->pkey)
		वापस false;

	list_क्रम_each_entry(tpriv, &ppriv->child_पूर्णांकfs, list) अणु
		अगर (tpriv->pkey == priv->pkey &&
		    tpriv->child_type == IPOIB_LEGACY_CHILD)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * NOTE: If this function fails then the priv->dev will reमुख्य valid, however
 * priv will have been मुक्तd and must not be touched by caller in the error
 * हाल.
 *
 * If (ndev->reg_state == NETREG_UNINITIALIZED) then it is up to the caller to
 * मुक्त the net_device (just as rtnl_newlink करोes) otherwise the net_device
 * will be मुक्तd when the rtnl is unlocked.
 */
पूर्णांक __ipoib_vlan_add(काष्ठा ipoib_dev_priv *ppriv, काष्ठा ipoib_dev_priv *priv,
		     u16 pkey, पूर्णांक type)
अणु
	काष्ठा net_device *ndev = priv->dev;
	पूर्णांक result;
	काष्ठा rdma_netdev *rn = netdev_priv(ndev);

	ASSERT_RTNL();

	/*
	 * We करो not need to touch priv अगर रेजिस्टर_netdevice fails, so just
	 * always use this flow.
	 */
	ndev->priv_deकाष्ठाor = ipoib_पूर्णांकf_मुक्त;

	/*
	 * Racing with unरेजिस्टर of the parent must be prevented by the
	 * caller.
	 */
	WARN_ON(ppriv->dev->reg_state != NETREG_REGISTERED);

	अगर (pkey == 0 || pkey == 0x8000) अणु
		result = -EINVAL;
		जाओ out_early;
	पूर्ण

	rn->mtu = priv->mcast_mtu;

	priv->parent = ppriv->dev;
	priv->pkey = pkey;
	priv->child_type = type;

	अगर (!is_child_unique(ppriv, priv)) अणु
		result = -ENOTUNIQ;
		जाओ out_early;
	पूर्ण

	result = रेजिस्टर_netdevice(ndev);
	अगर (result) अणु
		ipoib_warn(priv, "failed to initialize; error %i", result);

		/*
		 * रेजिस्टर_netdevice someबार calls priv_deकाष्ठाor,
		 * someबार not. Make sure it was करोne.
		 */
		जाओ out_early;
	पूर्ण

	/* RTNL childs करोn't need proprietary sysfs entries */
	अगर (type == IPOIB_LEGACY_CHILD) अणु
		अगर (ipoib_cm_add_mode_attr(ndev))
			जाओ sysfs_failed;
		अगर (ipoib_add_pkey_attr(ndev))
			जाओ sysfs_failed;
		अगर (ipoib_add_umcast_attr(ndev))
			जाओ sysfs_failed;

		अगर (device_create_file(&ndev->dev, &dev_attr_parent))
			जाओ sysfs_failed;
	पूर्ण

	वापस 0;

sysfs_failed:
	unरेजिस्टर_netdevice(priv->dev);
	वापस -ENOMEM;

out_early:
	अगर (ndev->priv_deकाष्ठाor)
		ndev->priv_deकाष्ठाor(ndev);
	वापस result;
पूर्ण

पूर्णांक ipoib_vlan_add(काष्ठा net_device *pdev, अचिन्हित लघु pkey)
अणु
	काष्ठा ipoib_dev_priv *ppriv, *priv;
	अक्षर पूर्णांकf_name[IFNAMSIZ];
	काष्ठा net_device *ndev;
	पूर्णांक result;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	अगर (pdev->reg_state != NETREG_REGISTERED) अणु
		rtnl_unlock();
		वापस -EPERM;
	पूर्ण

	ppriv = ipoib_priv(pdev);

	snम_लिखो(पूर्णांकf_name, माप(पूर्णांकf_name), "%s.%04x",
		 ppriv->dev->name, pkey);

	ndev = ipoib_पूर्णांकf_alloc(ppriv->ca, ppriv->port, पूर्णांकf_name);
	अगर (IS_ERR(ndev)) अणु
		result = PTR_ERR(ndev);
		जाओ out;
	पूर्ण
	priv = ipoib_priv(ndev);

	ndev->rtnl_link_ops = ipoib_get_link_ops();

	result = __ipoib_vlan_add(ppriv, priv, pkey, IPOIB_LEGACY_CHILD);

	अगर (result && ndev->reg_state == NETREG_UNINITIALIZED)
		मुक्त_netdev(ndev);

out:
	rtnl_unlock();

	वापस result;
पूर्ण

काष्ठा ipoib_vlan_delete_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा net_device *dev;
पूर्ण;

/*
 * sysfs callbacks of a netdevice cannot obtain the rtnl lock as
 * unरेजिस्टर_netdev ultimately deletes the sysfs files जबतक holding the rtnl
 * lock. This deadlocks the प्रणाली.
 *
 * A callback can use rtnl_trylock to aव्योम the deadlock but it cannot call
 * unरेजिस्टर_netdev as that पूर्णांकernally takes and releases the rtnl_lock.  So
 * instead we find the netdev to unरेजिस्टर and then करो the actual unरेजिस्टर
 * from the global work queue where we can obtain the rtnl_lock safely.
 */
अटल व्योम ipoib_vlan_delete_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipoib_vlan_delete_work *pwork =
		container_of(work, काष्ठा ipoib_vlan_delete_work, work);
	काष्ठा net_device *dev = pwork->dev;

	rtnl_lock();

	/* Unरेजिस्टरing tasks can race with another task or parent removal */
	अगर (dev->reg_state == NETREG_REGISTERED) अणु
		काष्ठा ipoib_dev_priv *priv = ipoib_priv(dev);
		काष्ठा ipoib_dev_priv *ppriv = ipoib_priv(priv->parent);

		ipoib_dbg(ppriv, "delete child vlan %s\n", dev->name);
		unरेजिस्टर_netdevice(dev);
	पूर्ण

	rtnl_unlock();

	kमुक्त(pwork);
पूर्ण

पूर्णांक ipoib_vlan_delete(काष्ठा net_device *pdev, अचिन्हित लघु pkey)
अणु
	काष्ठा ipoib_dev_priv *ppriv, *priv, *tpriv;
	पूर्णांक rc;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	अगर (pdev->reg_state != NETREG_REGISTERED) अणु
		rtnl_unlock();
		वापस -EPERM;
	पूर्ण

	ppriv = ipoib_priv(pdev);

	rc = -ENODEV;
	list_क्रम_each_entry_safe(priv, tpriv, &ppriv->child_पूर्णांकfs, list) अणु
		अगर (priv->pkey == pkey &&
		    priv->child_type == IPOIB_LEGACY_CHILD) अणु
			काष्ठा ipoib_vlan_delete_work *work;

			work = kदो_स्मृति(माप(*work), GFP_KERNEL);
			अगर (!work) अणु
				rc = -ENOMEM;
				जाओ out;
			पूर्ण

			करोwn_ग_लिखो(&ppriv->vlan_rwsem);
			list_del_init(&priv->list);
			up_ग_लिखो(&ppriv->vlan_rwsem);
			work->dev = priv->dev;
			INIT_WORK(&work->work, ipoib_vlan_delete_task);
			queue_work(ipoib_workqueue, &work->work);

			rc = 0;
			अवरोध;
		पूर्ण
	पूर्ण

out:
	rtnl_unlock();

	वापस rc;
पूर्ण
