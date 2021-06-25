<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Juniper Networks, Inc.
 *
 * Author:
 * Petko Manolov <petko.manolov@konsulko.com>
 */

#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/cred.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <keys/प्रणाली_keyring.h>


काष्ठा key *ima_blacklist_keyring;

/*
 * Allocate the IMA blacklist keyring
 */
__init पूर्णांक ima_mok_init(व्योम)
अणु
	काष्ठा key_restriction *restriction;

	pr_notice("Allocating IMA blacklist keyring.\n");

	restriction = kzalloc(माप(काष्ठा key_restriction), GFP_KERNEL);
	अगर (!restriction)
		panic("Can't allocate IMA blacklist restriction.");

	restriction->check = restrict_link_by_builtin_trusted;

	ima_blacklist_keyring = keyring_alloc(".ima_blacklist",
				KUIDT_INIT(0), KGIDT_INIT(0), current_cred(),
				(KEY_POS_ALL & ~KEY_POS_SETATTR) |
				KEY_USR_VIEW | KEY_USR_READ |
				KEY_USR_WRITE | KEY_USR_SEARCH,
				KEY_ALLOC_NOT_IN_QUOTA |
				KEY_ALLOC_SET_KEEP,
				restriction, शून्य);

	अगर (IS_ERR(ima_blacklist_keyring))
		panic("Can't allocate IMA blacklist keyring.");
	वापस 0;
पूर्ण
device_initcall(ima_mok_init);
