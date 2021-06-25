<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Ported from IRIX to Linux by Kanoj Sarcar, 06/08/00.
 * Copyright 2000 - 2001 Silicon Graphics, Inc.
 * Copyright 2000 - 2001 Kanoj Sarcar (kanoj@sgi.com)
 */
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/kernel.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/sn/types.h>
#समावेश <यंत्र/sn/arch.h>
#समावेश <यंत्र/sn/gda.h>
#समावेश <यंत्र/sn/mapped_kernel.h>

#समावेश "ip27-common.h"

अटल nodemask_t ktext_repmask;

/*
 * XXX - This needs to be much smarter about where it माला_दो copies of the
 * kernel.  For example, we should never put a copy on a headless node,
 * and we should respect the topology of the machine.
 */
व्योम __init setup_replication_mask(व्योम)
अणु
	/* Set only the master cnode's bit.  The master cnode is always 0. */
	nodes_clear(ktext_repmask);
	node_set(0, ktext_repmask);

#अगर_घोषित CONFIG_REPLICATE_KTEXT
#अगर_अघोषित CONFIG_MAPPED_KERNEL
#त्रुटि Kernel replication works with mapped kernel support. No calias support.
#पूर्ण_अगर
	अणु
		nasid_t nasid;

		क्रम_each_online_node(nasid) अणु
			अगर (nasid == 0)
				जारी;
			/* Advertise that we have a copy of the kernel */
			node_set(nasid, ktext_repmask);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	/* Set up a GDA poपूर्णांकer to the replication mask. */
	GDA->g_ktext_repmask = &ktext_repmask;
पूर्ण


अटल __init व्योम set_ktext_source(nasid_t client_nasid, nasid_t server_nasid)
अणु
	kern_vars_t *kvp;

	kvp = &hub_data(client_nasid)->kern_vars;

	KERN_VARS_ADDR(client_nasid) = (अचिन्हित दीर्घ)kvp;

	kvp->kv_magic = KV_MAGIC;
	kvp->kv_ro_nasid = server_nasid;
	kvp->kv_rw_nasid = master_nasid;
	kvp->kv_ro_baseaddr = NODE_CAC_BASE(server_nasid);
	kvp->kv_rw_baseaddr = NODE_CAC_BASE(master_nasid);
	prपूर्णांकk("REPLICATION: ON nasid %d, ktext from nasid %d, kdata from nasid %d\n", client_nasid, server_nasid, master_nasid);
पूर्ण

/* XXX - When the BTE works, we should use it instead of this. */
अटल __init व्योम copy_kernel(nasid_t dest_nasid)
अणु
	अचिन्हित दीर्घ dest_kern_start, source_start, source_end, kern_size;

	source_start = (अचिन्हित दीर्घ) _stext;
	source_end = (अचिन्हित दीर्घ) _etext;
	kern_size = source_end - source_start;

	dest_kern_start = CHANGE_ADDR_NASID(MAPPED_KERN_RO_TO_K0(source_start),
					    dest_nasid);
	स_नकल((व्योम *)dest_kern_start, (व्योम *)source_start, kern_size);
पूर्ण

व्योम __init replicate_kernel_text(व्योम)
अणु
	nasid_t client_nasid;
	nasid_t server_nasid;

	server_nasid = master_nasid;

	/* Record where the master node should get its kernel text */
	set_ktext_source(master_nasid, master_nasid);

	क्रम_each_online_node(client_nasid) अणु
		अगर (client_nasid == 0)
			जारी;

		/* Check अगर this node should get a copy of the kernel */
		अगर (node_isset(client_nasid, ktext_repmask)) अणु
			server_nasid = client_nasid;
			copy_kernel(server_nasid);
		पूर्ण

		/* Record where this node should get its kernel text */
		set_ktext_source(client_nasid, server_nasid);
	पूर्ण
पूर्ण

/*
 * Return pfn of first मुक्त page of memory on a node. PROM may allocate
 * data काष्ठाures on the first couple of pages of the first slot of each
 * node. If this is the हाल, getfirstमुक्त(node) > माला_लोlotstart(node, 0).
 */
अचिन्हित दीर्घ node_getfirstमुक्त(nasid_t nasid)
अणु
	अचिन्हित दीर्घ loadbase = REP_BASE;
	अचिन्हित दीर्घ offset;

#अगर_घोषित CONFIG_MAPPED_KERNEL
	loadbase += 16777216;
#पूर्ण_अगर
	offset = PAGE_ALIGN((अचिन्हित दीर्घ)(&_end)) - loadbase;
	अगर ((nasid == 0) || (node_isset(nasid, ktext_repmask)))
		वापस TO_NODE(nasid, offset) >> PAGE_SHIFT;
	अन्यथा
		वापस KDM_TO_PHYS(PAGE_ALIGN(SYMMON_STK_ADDR(nasid, 0))) >> PAGE_SHIFT;
पूर्ण
