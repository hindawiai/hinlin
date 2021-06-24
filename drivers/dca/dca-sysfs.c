<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright(c) 2007 - 2009 Intel Corporation. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/device.h>
#समावेश <linux/idr.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/err.h>
#समावेश <linux/dca.h>
#समावेश <linux/gfp.h>
#समावेश <linux/export.h>

अटल काष्ठा class *dca_class;
अटल काष्ठा idr dca_idr;
अटल spinlock_t dca_idr_lock;

पूर्णांक dca_sysfs_add_req(काष्ठा dca_provider *dca, काष्ठा device *dev, पूर्णांक slot)
अणु
	काष्ठा device *cd;
	अटल पूर्णांक req_count;

	cd = device_create(dca_class, dca->cd, MKDEV(0, slot + 1), शून्य,
			   "requester%d", req_count++);
	वापस PTR_ERR_OR_ZERO(cd);
पूर्ण

व्योम dca_sysfs_हटाओ_req(काष्ठा dca_provider *dca, पूर्णांक slot)
अणु
	device_destroy(dca_class, MKDEV(0, slot + 1));
पूर्ण

पूर्णांक dca_sysfs_add_provider(काष्ठा dca_provider *dca, काष्ठा device *dev)
अणु
	काष्ठा device *cd;
	पूर्णांक ret;

	idr_preload(GFP_KERNEL);
	spin_lock(&dca_idr_lock);

	ret = idr_alloc(&dca_idr, dca, 0, 0, GFP_NOWAIT);
	अगर (ret >= 0)
		dca->id = ret;

	spin_unlock(&dca_idr_lock);
	idr_preload_end();
	अगर (ret < 0)
		वापस ret;

	cd = device_create(dca_class, dev, MKDEV(0, 0), शून्य, "dca%d", dca->id);
	अगर (IS_ERR(cd)) अणु
		spin_lock(&dca_idr_lock);
		idr_हटाओ(&dca_idr, dca->id);
		spin_unlock(&dca_idr_lock);
		वापस PTR_ERR(cd);
	पूर्ण
	dca->cd = cd;
	वापस 0;
पूर्ण

व्योम dca_sysfs_हटाओ_provider(काष्ठा dca_provider *dca)
अणु
	device_unरेजिस्टर(dca->cd);
	dca->cd = शून्य;
	spin_lock(&dca_idr_lock);
	idr_हटाओ(&dca_idr, dca->id);
	spin_unlock(&dca_idr_lock);
पूर्ण

पूर्णांक __init dca_sysfs_init(व्योम)
अणु
	idr_init(&dca_idr);
	spin_lock_init(&dca_idr_lock);

	dca_class = class_create(THIS_MODULE, "dca");
	अगर (IS_ERR(dca_class)) अणु
		idr_destroy(&dca_idr);
		वापस PTR_ERR(dca_class);
	पूर्ण
	वापस 0;
पूर्ण

व्योम __निकास dca_sysfs_निकास(व्योम)
अणु
	class_destroy(dca_class);
	idr_destroy(&dca_idr);
पूर्ण

