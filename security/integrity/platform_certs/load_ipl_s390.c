<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/cred.h>
#समावेश <linux/err.h>
#समावेश <linux/efi.h>
#समावेश <linux/slab.h>
#समावेश <keys/asymmetric-type.h>
#समावेश <keys/प्रणाली_keyring.h>
#समावेश <यंत्र/boot_data.h>
#समावेश "../integrity.h"

/*
 * Load the certs contained in the IPL report created by the machine loader
 * पूर्णांकo the platक्रमm trusted keyring.
 */
अटल पूर्णांक __init load_ipl_certs(व्योम)
अणु
	व्योम *ptr, *end;
	अचिन्हित पूर्णांक len;

	अगर (!ipl_cert_list_addr)
		वापस 0;
	/* Copy the certअगरicates to the प्रणाली keyring */
	ptr = (व्योम *) ipl_cert_list_addr;
	end = ptr + ipl_cert_list_size;
	जबतक ((व्योम *) ptr < end) अणु
		len = *(अचिन्हित पूर्णांक *) ptr;
		ptr += माप(अचिन्हित पूर्णांक);
		add_to_platक्रमm_keyring("IPL:db", ptr, len);
		ptr += len;
	पूर्ण
	वापस 0;
पूर्ण
late_initcall(load_ipl_certs);
