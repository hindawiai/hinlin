<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2006-2013 Solarflare Communications Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/slab.h>
#समावेश <linux/rtnetlink.h>

#समावेश "net_driver.h"
#समावेश "efx.h"

#घोषणा to_ef4_mtd_partition(mtd)				\
	container_of(mtd, काष्ठा ef4_mtd_partition, mtd)

/* MTD पूर्णांकerface */

अटल पूर्णांक ef4_mtd_erase(काष्ठा mtd_info *mtd, काष्ठा erase_info *erase)
अणु
	काष्ठा ef4_nic *efx = mtd->priv;

	वापस efx->type->mtd_erase(mtd, erase->addr, erase->len);
पूर्ण

अटल व्योम ef4_mtd_sync(काष्ठा mtd_info *mtd)
अणु
	काष्ठा ef4_mtd_partition *part = to_ef4_mtd_partition(mtd);
	काष्ठा ef4_nic *efx = mtd->priv;
	पूर्णांक rc;

	rc = efx->type->mtd_sync(mtd);
	अगर (rc)
		pr_err("%s: %s sync failed (%d)\n",
		       part->name, part->dev_type_name, rc);
पूर्ण

अटल व्योम ef4_mtd_हटाओ_partition(काष्ठा ef4_mtd_partition *part)
अणु
	पूर्णांक rc;

	क्रम (;;) अणु
		rc = mtd_device_unरेजिस्टर(&part->mtd);
		अगर (rc != -EBUSY)
			अवरोध;
		ssleep(1);
	पूर्ण
	WARN_ON(rc);
	list_del(&part->node);
पूर्ण

पूर्णांक ef4_mtd_add(काष्ठा ef4_nic *efx, काष्ठा ef4_mtd_partition *parts,
		माप_प्रकार n_parts, माप_प्रकार माप_part)
अणु
	काष्ठा ef4_mtd_partition *part;
	माप_प्रकार i;

	क्रम (i = 0; i < n_parts; i++) अणु
		part = (काष्ठा ef4_mtd_partition *)((अक्षर *)parts +
						    i * माप_part);

		part->mtd.ग_लिखोsize = 1;

		part->mtd.owner = THIS_MODULE;
		part->mtd.priv = efx;
		part->mtd.name = part->name;
		part->mtd._erase = ef4_mtd_erase;
		part->mtd._पढ़ो = efx->type->mtd_पढ़ो;
		part->mtd._ग_लिखो = efx->type->mtd_ग_लिखो;
		part->mtd._sync = ef4_mtd_sync;

		efx->type->mtd_नाम(part);

		अगर (mtd_device_रेजिस्टर(&part->mtd, शून्य, 0))
			जाओ fail;

		/* Add to list in order - ef4_mtd_हटाओ() depends on this */
		list_add_tail(&part->node, &efx->mtd_list);
	पूर्ण

	वापस 0;

fail:
	जबतक (i--) अणु
		part = (काष्ठा ef4_mtd_partition *)((अक्षर *)parts +
						    i * माप_part);
		ef4_mtd_हटाओ_partition(part);
	पूर्ण
	/* Failure is unlikely here, but probably means we're out of memory */
	वापस -ENOMEM;
पूर्ण

व्योम ef4_mtd_हटाओ(काष्ठा ef4_nic *efx)
अणु
	काष्ठा ef4_mtd_partition *parts, *part, *next;

	WARN_ON(ef4_dev_रेजिस्टरed(efx));

	अगर (list_empty(&efx->mtd_list))
		वापस;

	parts = list_first_entry(&efx->mtd_list, काष्ठा ef4_mtd_partition,
				 node);

	list_क्रम_each_entry_safe(part, next, &efx->mtd_list, node)
		ef4_mtd_हटाओ_partition(part);

	kमुक्त(parts);
पूर्ण

व्योम ef4_mtd_नाम(काष्ठा ef4_nic *efx)
अणु
	काष्ठा ef4_mtd_partition *part;

	ASSERT_RTNL();

	list_क्रम_each_entry(part, &efx->mtd_list, node)
		efx->type->mtd_नाम(part);
पूर्ण
