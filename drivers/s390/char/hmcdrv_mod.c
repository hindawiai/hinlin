<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    HMC Drive DVD Module
 *
 *    Copyright IBM Corp. 2013
 *    Author(s): Ralf Hoppe (rhoppe@de.ibm.com)
 */

#घोषणा KMSG_COMPONENT "hmcdrv"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/स्थिति.स>

#समावेश "hmcdrv_ftp.h"
#समावेश "hmcdrv_dev.h"
#समावेश "hmcdrv_cache.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Copyright 2013 IBM Corporation");
MODULE_DESCRIPTION("HMC drive DVD access");

/*
 * module parameter 'cachesize'
 */
अटल माप_प्रकार hmcdrv_mod_cachesize = HMCDRV_CACHE_SIZE_DFLT;
module_param_named(cachesize, hmcdrv_mod_cachesize, uदीर्घ, S_IRUGO);

/**
 * hmcdrv_mod_init() - module init function
 */
अटल पूर्णांक __init hmcdrv_mod_init(व्योम)
अणु
	पूर्णांक rc = hmcdrv_ftp_probe(); /* perक्रमm w/o cache */

	अगर (rc)
		वापस rc;

	rc = hmcdrv_cache_startup(hmcdrv_mod_cachesize);

	अगर (rc)
		वापस rc;

	rc = hmcdrv_dev_init();

	अगर (rc)
		hmcdrv_cache_shutकरोwn();

	वापस rc;
पूर्ण

/**
 * hmcdrv_mod_निकास() - module निकास function
 */
अटल व्योम __निकास hmcdrv_mod_निकास(व्योम)
अणु
	hmcdrv_dev_निकास();
	hmcdrv_cache_shutकरोwn();
पूर्ण

module_init(hmcdrv_mod_init);
module_निकास(hmcdrv_mod_निकास);
