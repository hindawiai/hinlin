<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Data gathering module क्रम Linux-VM Monitor Stream, Stage 1.
 * Collects data related to memory management.
 *
 * Copyright IBM Corp. 2003, 2006
 *
 * Author: Gerald Schaefer <gerald.schaefer@de.ibm.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/swap.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/पन.स>

#समावेश "appldata.h"


#घोषणा P2K(x) ((x) << (PAGE_SHIFT - 10))	/* Converts #Pages to KB */

/*
 * Memory data
 *
 * This is accessed as binary data by z/VM. If changes to it can't be aव्योमed,
 * the काष्ठाure version (product ID, see appldata_base.c) needs to be changed
 * as well and all करोcumentation and z/VM applications using it must be
 * updated.
 */
काष्ठा appldata_mem_data अणु
	u64 बारtamp;
	u32 sync_count_1;       /* after VM collected the record data, */
	u32 sync_count_2;	/* sync_count_1 and sync_count_2 should be the
				   same. If not, the record has been updated on
				   the Linux side जबतक VM was collecting the
				   (possibly corrupt) data */

	u64 pgpgin;		/* data पढ़ो from disk  */
	u64 pgpgout;		/* data written to disk */
	u64 pswpin;		/* pages swapped in  */
	u64 pswpout;		/* pages swapped out */

	u64 sharedram;		/* sharedram is currently set to 0 */

	u64 totalram;		/* total मुख्य memory size */
	u64 मुक्तram;		/* मुक्त मुख्य memory size  */
	u64 totalhigh;		/* total high memory size */
	u64 मुक्तhigh;		/* मुक्त high memory size  */

	u64 bufferram;		/* memory reserved क्रम buffers, मुक्त cache */
	u64 cached;		/* size of (used) cache, w/o buffers */
	u64 totalswap;		/* total swap space size */
	u64 मुक्तswap;		/* मुक्त swap space */

// New in 2.6 -->
	u64 pgalloc;		/* page allocations */
	u64 pgfault;		/* page faults (major+minor) */
	u64 pgmajfault;		/* page faults (major only) */
// <-- New in 2.6

पूर्ण __packed;


/*
 * appldata_get_mem_data()
 *
 * gather memory data
 */
अटल व्योम appldata_get_mem_data(व्योम *data)
अणु
	/*
	 * करोn't put large काष्ठाures on the stack, we are
	 * serialized through the appldata_ops_mutex and can use अटल
	 */
	अटल काष्ठा sysinfo val;
	अचिन्हित दीर्घ ev[NR_VM_EVENT_ITEMS];
	काष्ठा appldata_mem_data *mem_data;

	mem_data = data;
	mem_data->sync_count_1++;

	all_vm_events(ev);
	mem_data->pgpgin     = ev[PGPGIN] >> 1;
	mem_data->pgpgout    = ev[PGPGOUT] >> 1;
	mem_data->pswpin     = ev[PSWPIN];
	mem_data->pswpout    = ev[PSWPOUT];
	mem_data->pgalloc    = ev[PGALLOC_NORMAL];
	mem_data->pgalloc    += ev[PGALLOC_DMA];
	mem_data->pgfault    = ev[PGFAULT];
	mem_data->pgmajfault = ev[PGMAJFAULT];

	si_meminfo(&val);
	mem_data->sharedram = val.sharedram;
	mem_data->totalram  = P2K(val.totalram);
	mem_data->मुक्तram   = P2K(val.मुक्तram);
	mem_data->totalhigh = P2K(val.totalhigh);
	mem_data->मुक्तhigh  = P2K(val.मुक्तhigh);
	mem_data->bufferram = P2K(val.bufferram);
	mem_data->cached    = P2K(global_node_page_state(NR_खाता_PAGES)
				- val.bufferram);

	si_swapinfo(&val);
	mem_data->totalswap = P2K(val.totalswap);
	mem_data->मुक्तswap  = P2K(val.मुक्तswap);

	mem_data->बारtamp = get_tod_घड़ी();
	mem_data->sync_count_2++;
पूर्ण


अटल काष्ठा appldata_ops ops = अणु
	.name      = "mem",
	.record_nr = APPLDATA_RECORD_MEM_ID,
	.size	   = माप(काष्ठा appldata_mem_data),
	.callback  = &appldata_get_mem_data,
	.owner     = THIS_MODULE,
	.mod_lvl   = अणु0xF0, 0xF0पूर्ण,		/* EBCDIC "00" */
पूर्ण;


/*
 * appldata_mem_init()
 *
 * init_data, रेजिस्टर ops
 */
अटल पूर्णांक __init appldata_mem_init(व्योम)
अणु
	पूर्णांक ret;

	ops.data = kzalloc(माप(काष्ठा appldata_mem_data), GFP_KERNEL);
	अगर (!ops.data)
		वापस -ENOMEM;

	ret = appldata_रेजिस्टर_ops(&ops);
	अगर (ret)
		kमुक्त(ops.data);

	वापस ret;
पूर्ण

/*
 * appldata_mem_निकास()
 *
 * unरेजिस्टर ops
 */
अटल व्योम __निकास appldata_mem_निकास(व्योम)
अणु
	appldata_unरेजिस्टर_ops(&ops);
	kमुक्त(ops.data);
पूर्ण


module_init(appldata_mem_init);
module_निकास(appldata_mem_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Gerald Schaefer");
MODULE_DESCRIPTION("Linux-VM Monitor Stream, MEMORY statistics");
