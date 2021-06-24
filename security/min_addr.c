<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/security.h>
#समावेश <linux/sysctl.h>

/* amount of vm to protect from userspace access by both DAC and the LSM*/
अचिन्हित दीर्घ mmap_min_addr;
/* amount of vm to protect from userspace using CAP_SYS_RAWIO (DAC) */
अचिन्हित दीर्घ dac_mmap_min_addr = CONFIG_DEFAULT_MMAP_MIN_ADDR;
/* amount of vm to protect from userspace using the LSM = CONFIG_LSM_MMAP_MIN_ADDR */

/*
 * Update mmap_min_addr = max(dac_mmap_min_addr, CONFIG_LSM_MMAP_MIN_ADDR)
 */
अटल व्योम update_mmap_min_addr(व्योम)
अणु
#अगर_घोषित CONFIG_LSM_MMAP_MIN_ADDR
	अगर (dac_mmap_min_addr > CONFIG_LSM_MMAP_MIN_ADDR)
		mmap_min_addr = dac_mmap_min_addr;
	अन्यथा
		mmap_min_addr = CONFIG_LSM_MMAP_MIN_ADDR;
#अन्यथा
	mmap_min_addr = dac_mmap_min_addr;
#पूर्ण_अगर
पूर्ण

/*
 * sysctl handler which just sets dac_mmap_min_addr = the new value and then
 * calls update_mmap_min_addr() so non MAP_FIXED hपूर्णांकs get rounded properly
 */
पूर्णांक mmap_min_addr_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			  व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret;

	अगर (ग_लिखो && !capable(CAP_SYS_RAWIO))
		वापस -EPERM;

	ret = proc_करोuदीर्घvec_minmax(table, ग_लिखो, buffer, lenp, ppos);

	update_mmap_min_addr();

	वापस ret;
पूर्ण

अटल पूर्णांक __init init_mmap_min_addr(व्योम)
अणु
	update_mmap_min_addr();

	वापस 0;
पूर्ण
pure_initcall(init_mmap_min_addr);
