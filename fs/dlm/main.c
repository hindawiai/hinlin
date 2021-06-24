<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) Sistina Software, Inc.  1997-2003  All rights reserved.
**  Copyright (C) 2004-2007 Red Hat, Inc.  All rights reserved.
**
**
*******************************************************************************
******************************************************************************/

#समावेश <linux/module.h>

#समावेश "dlm_internal.h"
#समावेश "lockspace.h"
#समावेश "lock.h"
#समावेश "user.h"
#समावेश "memory.h"
#समावेश "config.h"
#समावेश "lowcomms.h"

अटल पूर्णांक __init init_dlm(व्योम)
अणु
	पूर्णांक error;

	error = dlm_memory_init();
	अगर (error)
		जाओ out;

	error = dlm_lockspace_init();
	अगर (error)
		जाओ out_mem;

	error = dlm_config_init();
	अगर (error)
		जाओ out_lockspace;

	dlm_रेजिस्टर_debugfs();

	error = dlm_user_init();
	अगर (error)
		जाओ out_debug;

	error = dlm_netlink_init();
	अगर (error)
		जाओ out_user;

	error = dlm_plock_init();
	अगर (error)
		जाओ out_netlink;

	prपूर्णांकk("DLM installed\n");

	वापस 0;

 out_netlink:
	dlm_netlink_निकास();
 out_user:
	dlm_user_निकास();
 out_debug:
	dlm_unरेजिस्टर_debugfs();
	dlm_config_निकास();
 out_lockspace:
	dlm_lockspace_निकास();
 out_mem:
	dlm_memory_निकास();
 out:
	वापस error;
पूर्ण

अटल व्योम __निकास निकास_dlm(व्योम)
अणु
	dlm_plock_निकास();
	dlm_netlink_निकास();
	dlm_user_निकास();
	dlm_config_निकास();
	dlm_memory_निकास();
	dlm_lockspace_निकास();
	dlm_lowcomms_निकास();
	dlm_unरेजिस्टर_debugfs();
पूर्ण

module_init(init_dlm);
module_निकास(निकास_dlm);

MODULE_DESCRIPTION("Distributed Lock Manager");
MODULE_AUTHOR("Red Hat, Inc.");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL_GPL(dlm_new_lockspace);
EXPORT_SYMBOL_GPL(dlm_release_lockspace);
EXPORT_SYMBOL_GPL(dlm_lock);
EXPORT_SYMBOL_GPL(dlm_unlock);

