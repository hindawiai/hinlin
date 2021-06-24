<शैली गुरु>
/*
 * Copyright (c) 2012, 2013 Intel Corporation.  All rights reserved.
 * Copyright (c) 2006 - 2012 QLogic Corporation. All rights reserved.
 * Copyright (c) 2003, 2004, 2005, 2006 PathScale, Inc. All rights reserved.
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

#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA
#समावेश <linux/dca.h>
#पूर्ण_अगर
#समावेश <rdma/rdma_vt.h>

#समावेश "qib.h"
#समावेश "qib_common.h"
#समावेश "qib_mad.h"
#अगर_घोषित CONFIG_DEBUG_FS
#समावेश "qib_debugfs.h"
#समावेश "qib_verbs.h"
#पूर्ण_अगर

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) QIB_DRV_NAME ": " fmt

/*
 * min buffers we want to have per context, after driver
 */
#घोषणा QIB_MIN_USER_CTXT_BUFCNT 7

#घोषणा QLOGIC_IB_R_SOFTWARE_MASK 0xFF
#घोषणा QLOGIC_IB_R_SOFTWARE_SHIFT 24
#घोषणा QLOGIC_IB_R_EMULATOR_MASK (1ULL<<62)

/*
 * Number of ctxts we are configured to use (to allow क्रम more pio
 * buffers per ctxt, etc.)  Zero means use chip value.
 */
uलघु qib_cfgctxts;
module_param_named(cfgctxts, qib_cfgctxts, uलघु, S_IRUGO);
MODULE_PARM_DESC(cfgctxts, "Set max number of contexts to use");

अचिन्हित qib_numa_aware;
module_param_named(numa_aware, qib_numa_aware, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(numa_aware,
	"0 -> PSM allocation close to HCA, 1 -> PSM allocation local to process");

/*
 * If set, करो not ग_लिखो to any regs अगर aव्योमable, hack to allow
 * check क्रम deranged शेष रेजिस्टर values.
 */
uलघु qib_mini_init;
module_param_named(mini_init, qib_mini_init, uलघु, S_IRUGO);
MODULE_PARM_DESC(mini_init, "If set, do minimal diag init");

अचिन्हित qib_n_krcv_queues;
module_param_named(krcvqs, qib_n_krcv_queues, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(krcvqs, "number of kernel receive queues per IB port");

अचिन्हित qib_cc_table_size;
module_param_named(cc_table_size, qib_cc_table_size, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(cc_table_size, "Congestion control table entries 0 (CCA disabled - default), min = 128, max = 1984");

अटल व्योम verअगरy_पूर्णांकerrupt(काष्ठा समयr_list *);

DEFINE_XARRAY_FLAGS(qib_dev_table, XA_FLAGS_ALLOC | XA_FLAGS_LOCK_IRQ);
u32 qib_cpulist_count;
अचिन्हित दीर्घ *qib_cpulist;

/* set number of contexts we'll actually use */
व्योम qib_set_ctxtcnt(काष्ठा qib_devdata *dd)
अणु
	अगर (!qib_cfgctxts) अणु
		dd->cfgctxts = dd->first_user_ctxt + num_online_cpus();
		अगर (dd->cfgctxts > dd->ctxtcnt)
			dd->cfgctxts = dd->ctxtcnt;
	पूर्ण अन्यथा अगर (qib_cfgctxts < dd->num_pports)
		dd->cfgctxts = dd->ctxtcnt;
	अन्यथा अगर (qib_cfgctxts <= dd->ctxtcnt)
		dd->cfgctxts = qib_cfgctxts;
	अन्यथा
		dd->cfgctxts = dd->ctxtcnt;
	dd->मुक्तctxts = (dd->first_user_ctxt > dd->cfgctxts) ? 0 :
		dd->cfgctxts - dd->first_user_ctxt;
पूर्ण

/*
 * Common code क्रम creating the receive context array.
 */
पूर्णांक qib_create_ctxts(काष्ठा qib_devdata *dd)
अणु
	अचिन्हित i;
	पूर्णांक local_node_id = pcibus_to_node(dd->pcidev->bus);

	अगर (local_node_id < 0)
		local_node_id = numa_node_id();
	dd->asचिन्हित_node_id = local_node_id;

	/*
	 * Allocate full ctxtcnt array, rather than just cfgctxts, because
	 * cleanup iterates across all possible ctxts.
	 */
	dd->rcd = kसुस्मृति(dd->ctxtcnt, माप(*dd->rcd), GFP_KERNEL);
	अगर (!dd->rcd)
		वापस -ENOMEM;

	/* create (one or more) kctxt */
	क्रम (i = 0; i < dd->first_user_ctxt; ++i) अणु
		काष्ठा qib_pportdata *ppd;
		काष्ठा qib_ctxtdata *rcd;

		अगर (dd->skip_kctxt_mask & (1 << i))
			जारी;

		ppd = dd->pport + (i % dd->num_pports);

		rcd = qib_create_ctxtdata(ppd, i, dd->asचिन्हित_node_id);
		अगर (!rcd) अणु
			qib_dev_err(dd,
				"Unable to allocate ctxtdata for Kernel ctxt, failing\n");
			kमुक्त(dd->rcd);
			dd->rcd = शून्य;
			वापस -ENOMEM;
		पूर्ण
		rcd->pkeys[0] = QIB_DEFAULT_P_KEY;
		rcd->seq_cnt = 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Common code क्रम user and kernel context setup.
 */
काष्ठा qib_ctxtdata *qib_create_ctxtdata(काष्ठा qib_pportdata *ppd, u32 ctxt,
	पूर्णांक node_id)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	काष्ठा qib_ctxtdata *rcd;

	rcd = kzalloc_node(माप(*rcd), GFP_KERNEL, node_id);
	अगर (rcd) अणु
		INIT_LIST_HEAD(&rcd->qp_रुको_list);
		rcd->node_id = node_id;
		rcd->ppd = ppd;
		rcd->dd = dd;
		rcd->cnt = 1;
		rcd->ctxt = ctxt;
		dd->rcd[ctxt] = rcd;
#अगर_घोषित CONFIG_DEBUG_FS
		अगर (ctxt < dd->first_user_ctxt) अणु /* N/A क्रम PSM contexts */
			rcd->opstats = kzalloc_node(माप(*rcd->opstats),
				GFP_KERNEL, node_id);
			अगर (!rcd->opstats) अणु
				kमुक्त(rcd);
				qib_dev_err(dd,
					"Unable to allocate per ctxt stats buffer\n");
				वापस शून्य;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
		dd->f_init_ctxt(rcd);

		/*
		 * To aव्योम wasting a lot of memory, we allocate 32KB chunks
		 * of physically contiguous memory, advance through it until
		 * used up and then allocate more.  Of course, we need
		 * memory to store those extra poपूर्णांकers, now.  32KB seems to
		 * be the most that is "safe" under memory pressure
		 * (creating large files and then copying them over
		 * NFS जबतक करोing lots of MPI jobs).  The OOM समाप्तer can
		 * get invoked, even though we say we can sleep and this can
		 * cause signअगरicant प्रणाली problems....
		 */
		rcd->rcvegrbuf_size = 0x8000;
		rcd->rcvegrbufs_perchunk =
			rcd->rcvegrbuf_size / dd->rcvegrbufsize;
		rcd->rcvegrbuf_chunks = (rcd->rcvegrcnt +
			rcd->rcvegrbufs_perchunk - 1) /
			rcd->rcvegrbufs_perchunk;
		rcd->rcvegrbufs_perchunk_shअगरt =
			ilog2(rcd->rcvegrbufs_perchunk);
	पूर्ण
	वापस rcd;
पूर्ण

/*
 * Common code क्रम initializing the physical port काष्ठाure.
 */
पूर्णांक qib_init_pportdata(काष्ठा qib_pportdata *ppd, काष्ठा qib_devdata *dd,
			u8 hw_pidx, u8 port)
अणु
	पूर्णांक size;

	ppd->dd = dd;
	ppd->hw_pidx = hw_pidx;
	ppd->port = port; /* IB port number, not index */

	spin_lock_init(&ppd->sdma_lock);
	spin_lock_init(&ppd->lflags_lock);
	spin_lock_init(&ppd->cc_shaकरोw_lock);
	init_रुकोqueue_head(&ppd->state_रुको);

	समयr_setup(&ppd->symerr_clear_समयr, qib_clear_symerror_on_linkup, 0);

	ppd->qib_wq = शून्य;
	ppd->ibport_data.pmastats =
		alloc_percpu(काष्ठा qib_pma_counters);
	अगर (!ppd->ibport_data.pmastats)
		वापस -ENOMEM;
	ppd->ibport_data.rvp.rc_acks = alloc_percpu(u64);
	ppd->ibport_data.rvp.rc_qacks = alloc_percpu(u64);
	ppd->ibport_data.rvp.rc_delayed_comp = alloc_percpu(u64);
	अगर (!(ppd->ibport_data.rvp.rc_acks) ||
	    !(ppd->ibport_data.rvp.rc_qacks) ||
	    !(ppd->ibport_data.rvp.rc_delayed_comp))
		वापस -ENOMEM;

	अगर (qib_cc_table_size < IB_CCT_MIN_ENTRIES)
		जाओ bail;

	ppd->cc_supported_table_entries = min(max_t(पूर्णांक, qib_cc_table_size,
		IB_CCT_MIN_ENTRIES), IB_CCT_ENTRIES*IB_CC_TABLE_CAP_DEFAULT);

	ppd->cc_max_table_entries =
		ppd->cc_supported_table_entries/IB_CCT_ENTRIES;

	size = IB_CC_TABLE_CAP_DEFAULT * माप(काष्ठा ib_cc_table_entry)
		* IB_CCT_ENTRIES;
	ppd->ccti_entries = kzalloc(size, GFP_KERNEL);
	अगर (!ppd->ccti_entries)
		जाओ bail;

	size = IB_CC_CCS_ENTRIES * माप(काष्ठा ib_cc_congestion_entry);
	ppd->congestion_entries = kzalloc(size, GFP_KERNEL);
	अगर (!ppd->congestion_entries)
		जाओ bail_1;

	size = माप(काष्ठा cc_table_shaकरोw);
	ppd->ccti_entries_shaकरोw = kzalloc(size, GFP_KERNEL);
	अगर (!ppd->ccti_entries_shaकरोw)
		जाओ bail_2;

	size = माप(काष्ठा ib_cc_congestion_setting_attr);
	ppd->congestion_entries_shaकरोw = kzalloc(size, GFP_KERNEL);
	अगर (!ppd->congestion_entries_shaकरोw)
		जाओ bail_3;

	वापस 0;

bail_3:
	kमुक्त(ppd->ccti_entries_shaकरोw);
	ppd->ccti_entries_shaकरोw = शून्य;
bail_2:
	kमुक्त(ppd->congestion_entries);
	ppd->congestion_entries = शून्य;
bail_1:
	kमुक्त(ppd->ccti_entries);
	ppd->ccti_entries = शून्य;
bail:
	/* User is पूर्णांकentionally disabling the congestion control agent */
	अगर (!qib_cc_table_size)
		वापस 0;

	अगर (qib_cc_table_size < IB_CCT_MIN_ENTRIES) अणु
		qib_cc_table_size = 0;
		qib_dev_err(dd,
		 "Congestion Control table size %d less than minimum %d for port %d\n",
		 qib_cc_table_size, IB_CCT_MIN_ENTRIES, port);
	पूर्ण

	qib_dev_err(dd, "Congestion Control Agent disabled for port %d\n",
		port);
	वापस 0;
पूर्ण

अटल पूर्णांक init_pioavailregs(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक ret, pidx;
	u64 *status_page;

	dd->pioavailregs_dma = dma_alloc_coherent(
		&dd->pcidev->dev, PAGE_SIZE, &dd->pioavailregs_phys,
		GFP_KERNEL);
	अगर (!dd->pioavailregs_dma) अणु
		qib_dev_err(dd,
			"failed to allocate PIOavail reg area in memory\n");
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	/*
	 * We really want L2 cache aligned, but क्रम current CPUs of
	 * पूर्णांकerest, they are the same.
	 */
	status_page = (u64 *)
		((अक्षर *) dd->pioavailregs_dma +
		 ((2 * L1_CACHE_BYTES +
		   dd->pioavregs * माप(u64)) & ~L1_CACHE_BYTES));
	/* device status comes first, क्रम backwards compatibility */
	dd->devstatusp = status_page;
	*status_page++ = 0;
	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		dd->pport[pidx].statusp = status_page;
		*status_page++ = 0;
	पूर्ण

	/*
	 * Setup buffer to hold मुक्तze and other messages, accessible to
	 * apps, following statusp.  This is per-unit, not per port.
	 */
	dd->मुक्तzemsg = (अक्षर *) status_page;
	*dd->मुक्तzemsg = 0;
	/* length of msg buffer is "whatever is left" */
	ret = (अक्षर *) status_page - (अक्षर *) dd->pioavailregs_dma;
	dd->मुक्तzelen = PAGE_SIZE - ret;

	ret = 0;

करोne:
	वापस ret;
पूर्ण

/**
 * init_shaकरोw_tids - allocate the shaकरोw TID array
 * @dd: the qlogic_ib device
 *
 * allocate the shaकरोw TID array, so we can qib_munlock previous
 * entries.  It may make more sense to move the pageshaकरोw to the
 * ctxt data काष्ठाure, so we only allocate memory क्रम ctxts actually
 * in use, since we at 8k per ctxt, now.
 * We करोn't want failures here to prevent use of the driver/chip,
 * so no वापस value.
 */
अटल व्योम init_shaकरोw_tids(काष्ठा qib_devdata *dd)
अणु
	काष्ठा page **pages;
	dma_addr_t *addrs;

	pages = vzalloc(array_size(माप(काष्ठा page *),
				   dd->cfgctxts * dd->rcvtidcnt));
	अगर (!pages)
		जाओ bail;

	addrs = vzalloc(array_size(माप(dma_addr_t),
				   dd->cfgctxts * dd->rcvtidcnt));
	अगर (!addrs)
		जाओ bail_मुक्त;

	dd->pageshaकरोw = pages;
	dd->physshaकरोw = addrs;
	वापस;

bail_मुक्त:
	vमुक्त(pages);
bail:
	dd->pageshaकरोw = शून्य;
पूर्ण

/*
 * Do initialization क्रम device that is only needed on
 * first detect, not on resets.
 */
अटल पूर्णांक loadसमय_init(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक ret = 0;

	अगर (((dd->revision >> QLOGIC_IB_R_SOFTWARE_SHIFT) &
	     QLOGIC_IB_R_SOFTWARE_MASK) != QIB_CHIP_SWVERSION) अणु
		qib_dev_err(dd,
			"Driver only handles version %d, chip swversion is %d (%llx), failing\n",
			QIB_CHIP_SWVERSION,
			(पूर्णांक)(dd->revision >>
				QLOGIC_IB_R_SOFTWARE_SHIFT) &
				QLOGIC_IB_R_SOFTWARE_MASK,
			(अचिन्हित दीर्घ दीर्घ) dd->revision);
		ret = -ENOSYS;
		जाओ करोne;
	पूर्ण

	अगर (dd->revision & QLOGIC_IB_R_EMULATOR_MASK)
		qib_devinfo(dd->pcidev, "%s", dd->boardversion);

	spin_lock_init(&dd->pioavail_lock);
	spin_lock_init(&dd->sendctrl_lock);
	spin_lock_init(&dd->uctxt_lock);
	spin_lock_init(&dd->qib_diag_trans_lock);
	spin_lock_init(&dd->eep_st_lock);
	mutex_init(&dd->eep_lock);

	अगर (qib_mini_init)
		जाओ करोne;

	ret = init_pioavailregs(dd);
	init_shaकरोw_tids(dd);

	qib_get_eeprom_info(dd);

	/* setup समय (करोn't start yet) to verअगरy we got पूर्णांकerrupt */
	समयr_setup(&dd->पूर्णांकrchk_समयr, verअगरy_पूर्णांकerrupt, 0);
करोne:
	वापस ret;
पूर्ण

/**
 * init_after_reset - re-initialize after a reset
 * @dd: the qlogic_ib device
 *
 * sanity check at least some of the values after reset, and
 * ensure no receive or transmit (explicitly, in हाल reset
 * failed
 */
अटल पूर्णांक init_after_reset(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक i;

	/*
	 * Ensure chip करोes no sends or receives, tail updates, or
	 * pioavail updates जबतक we re-initialize.  This is mostly
	 * क्रम the driver data काष्ठाures, not chip रेजिस्टरs.
	 */
	क्रम (i = 0; i < dd->num_pports; ++i) अणु
		/*
		 * ctxt == -1 means "all contexts". Only really safe क्रम
		 * _dis_abling things, as here.
		 */
		dd->f_rcvctrl(dd->pport + i, QIB_RCVCTRL_CTXT_DIS |
				  QIB_RCVCTRL_INTRAVAIL_DIS |
				  QIB_RCVCTRL_TAILUPD_DIS, -1);
		/* Redundant across ports क्रम some, but no big deal.  */
		dd->f_sendctrl(dd->pport + i, QIB_SENDCTRL_SEND_DIS |
			QIB_SENDCTRL_AVAIL_DIS);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम enable_chip(काष्ठा qib_devdata *dd)
अणु
	u64 rcvmask;
	पूर्णांक i;

	/*
	 * Enable PIO send, and update of PIOavail regs to memory.
	 */
	क्रम (i = 0; i < dd->num_pports; ++i)
		dd->f_sendctrl(dd->pport + i, QIB_SENDCTRL_SEND_ENB |
			QIB_SENDCTRL_AVAIL_ENB);
	/*
	 * Enable kernel ctxts' receive and receive पूर्णांकerrupt.
	 * Other ctxts करोne as user खोलोs and inits them.
	 */
	rcvmask = QIB_RCVCTRL_CTXT_ENB | QIB_RCVCTRL_INTRAVAIL_ENB;
	rcvmask |= (dd->flags & QIB_NODMA_RTAIL) ?
		  QIB_RCVCTRL_TAILUPD_DIS : QIB_RCVCTRL_TAILUPD_ENB;
	क्रम (i = 0; dd->rcd && i < dd->first_user_ctxt; ++i) अणु
		काष्ठा qib_ctxtdata *rcd = dd->rcd[i];

		अगर (rcd)
			dd->f_rcvctrl(rcd->ppd, rcvmask, i);
	पूर्ण
पूर्ण

अटल व्योम verअगरy_पूर्णांकerrupt(काष्ठा समयr_list *t)
अणु
	काष्ठा qib_devdata *dd = from_समयr(dd, t, पूर्णांकrchk_समयr);
	u64 पूर्णांक_counter;

	अगर (!dd)
		वापस; /* being torn करोwn */

	/*
	 * If we करोn't have a lid or any पूर्णांकerrupts, let the user know and
	 * करोn't bother checking again.
	 */
	पूर्णांक_counter = qib_पूर्णांक_counter(dd) - dd->z_पूर्णांक_counter;
	अगर (पूर्णांक_counter == 0) अणु
		अगर (!dd->f_पूर्णांकr_fallback(dd))
			dev_err(&dd->pcidev->dev,
				"No interrupts detected, not usable.\n");
		अन्यथा /* re-arm the समयr to see अगर fallback works */
			mod_समयr(&dd->पूर्णांकrchk_समयr, jअगरfies + HZ/2);
	पूर्ण
पूर्ण

अटल व्योम init_piobuf_state(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक i, pidx;
	u32 uctxts;

	/*
	 * Ensure all buffers are मुक्त, and fअगरos empty.  Buffers
	 * are common, so only करो once क्रम port 0.
	 *
	 * After enable and qib_chg_pioavailkernel so we can safely
	 * enable pioavail updates and PIOENABLE.  After this, packets
	 * are पढ़ोy and able to go out.
	 */
	dd->f_sendctrl(dd->pport, QIB_SENDCTRL_DISARM_ALL);
	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx)
		dd->f_sendctrl(dd->pport + pidx, QIB_SENDCTRL_FLUSH);

	/*
	 * If not all sendbufs are used, add the one to each of the lower
	 * numbered contexts.  pbufsctxt and lastctxt_piobuf are
	 * calculated in chip-specअगरic code because it may cause some
	 * chip-specअगरic adjusपंचांगents to be made.
	 */
	uctxts = dd->cfgctxts - dd->first_user_ctxt;
	dd->ctxts_extrabuf = dd->pbufsctxt ?
		dd->lastctxt_piobuf - (dd->pbufsctxt * uctxts) : 0;

	/*
	 * Set up the shaकरोw copies of the piobufavail रेजिस्टरs,
	 * which we compare against the chip रेजिस्टरs क्रम now, and
	 * the in memory DMA'ed copies of the रेजिस्टरs.
	 * By now pioavail updates to memory should have occurred, so
	 * copy them पूर्णांकo our working/shaकरोw रेजिस्टरs; this is in
	 * हाल something went wrong with पात, but mostly to get the
	 * initial values of the generation bit correct.
	 */
	क्रम (i = 0; i < dd->pioavregs; i++) अणु
		__le64 पंचांगp;

		पंचांगp = dd->pioavailregs_dma[i];
		/*
		 * Don't need to worry about pioavailkernel here
		 * because we will call qib_chg_pioavailkernel() later
		 * in initialization, to busy out buffers as needed.
		 */
		dd->pioavailshaकरोw[i] = le64_to_cpu(पंचांगp);
	पूर्ण
	जबतक (i < ARRAY_SIZE(dd->pioavailshaकरोw))
		dd->pioavailshaकरोw[i++] = 0; /* क्रम debugging sanity */

	/* after pioavailshaकरोw is setup */
	qib_chg_pioavailkernel(dd, 0, dd->piobcnt2k + dd->piobcnt4k,
			       TXCHK_CHG_TYPE_KERN, शून्य);
	dd->f_initvl15_bufs(dd);
पूर्ण

/**
 * qib_create_workqueues - create per port workqueues
 * @dd: the qlogic_ib device
 */
अटल पूर्णांक qib_create_workqueues(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक pidx;
	काष्ठा qib_pportdata *ppd;

	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		ppd = dd->pport + pidx;
		अगर (!ppd->qib_wq) अणु
			अक्षर wq_name[8]; /* 3 + 2 + 1 + 1 + 1 */

			snम_लिखो(wq_name, माप(wq_name), "qib%d_%d",
				dd->unit, pidx);
			ppd->qib_wq = alloc_ordered_workqueue(wq_name,
							      WQ_MEM_RECLAIM);
			अगर (!ppd->qib_wq)
				जाओ wq_error;
		पूर्ण
	पूर्ण
	वापस 0;
wq_error:
	pr_err("create_singlethread_workqueue failed for port %d\n",
		pidx + 1);
	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		ppd = dd->pport + pidx;
		अगर (ppd->qib_wq) अणु
			destroy_workqueue(ppd->qib_wq);
			ppd->qib_wq = शून्य;
		पूर्ण
	पूर्ण
	वापस -ENOMEM;
पूर्ण

अटल व्योम qib_मुक्त_pportdata(काष्ठा qib_pportdata *ppd)
अणु
	मुक्त_percpu(ppd->ibport_data.pmastats);
	मुक्त_percpu(ppd->ibport_data.rvp.rc_acks);
	मुक्त_percpu(ppd->ibport_data.rvp.rc_qacks);
	मुक्त_percpu(ppd->ibport_data.rvp.rc_delayed_comp);
	ppd->ibport_data.pmastats = शून्य;
पूर्ण

/**
 * qib_init - करो the actual initialization sequence on the chip
 * @dd: the qlogic_ib device
 * @reinit: reinitializing, so करोn't allocate new memory
 *
 * Do the actual initialization sequence on the chip.  This is करोne
 * both from the init routine called from the PCI infraकाष्ठाure, and
 * when we reset the chip, or detect that it was reset पूर्णांकernally,
 * or it's administratively re-enabled.
 *
 * Memory allocation here and in called routines is only करोne in
 * the first हाल (reinit == 0).  We have to be careful, because even
 * without memory allocation, we need to re-ग_लिखो all the chip रेजिस्टरs
 * TIDs, etc. after the reset or enable has completed.
 */
पूर्णांक qib_init(काष्ठा qib_devdata *dd, पूर्णांक reinit)
अणु
	पूर्णांक ret = 0, pidx, lastfail = 0;
	u32 portok = 0;
	अचिन्हित i;
	काष्ठा qib_ctxtdata *rcd;
	काष्ठा qib_pportdata *ppd;
	अचिन्हित दीर्घ flags;

	/* Set linkstate to unknown, so we can watch क्रम a transition. */
	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		ppd = dd->pport + pidx;
		spin_lock_irqsave(&ppd->lflags_lock, flags);
		ppd->lflags &= ~(QIBL_LINKACTIVE | QIBL_LINKARMED |
				 QIBL_LINKDOWN | QIBL_LINKINIT |
				 QIBL_LINKV);
		spin_unlock_irqrestore(&ppd->lflags_lock, flags);
	पूर्ण

	अगर (reinit)
		ret = init_after_reset(dd);
	अन्यथा
		ret = loadसमय_init(dd);
	अगर (ret)
		जाओ करोne;

	/* Bypass most chip-init, to get to device creation */
	अगर (qib_mini_init)
		वापस 0;

	ret = dd->f_late_initreg(dd);
	अगर (ret)
		जाओ करोne;

	/* dd->rcd can be शून्य अगर early init failed */
	क्रम (i = 0; dd->rcd && i < dd->first_user_ctxt; ++i) अणु
		/*
		 * Set up the (kernel) rcvhdr queue and egr TIDs.  If करोing
		 * re-init, the simplest way to handle this is to मुक्त
		 * existing, and re-allocate.
		 * Need to re-create rest of ctxt 0 ctxtdata as well.
		 */
		rcd = dd->rcd[i];
		अगर (!rcd)
			जारी;

		lastfail = qib_create_rcvhdrq(dd, rcd);
		अगर (!lastfail)
			lastfail = qib_setup_eagerbufs(rcd);
		अगर (lastfail)
			qib_dev_err(dd,
				"failed to allocate kernel ctxt's rcvhdrq and/or egr bufs\n");
	पूर्ण

	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		पूर्णांक mtu;

		अगर (lastfail)
			ret = lastfail;
		ppd = dd->pport + pidx;
		mtu = ib_mtu_क्रमागत_to_पूर्णांक(qib_ibmtu);
		अगर (mtu == -1) अणु
			mtu = QIB_DEFAULT_MTU;
			qib_ibmtu = 0; /* करोn't leave invalid value */
		पूर्ण
		/* set max we can ever have क्रम this driver load */
		ppd->init_ibmaxlen = min(mtu > 2048 ?
					 dd->piosize4k : dd->piosize2k,
					 dd->rcvegrbufsize +
					 (dd->rcvhdrentsize << 2));
		/*
		 * Have to initialize ibmaxlen, but this will normally
		 * change immediately in qib_set_mtu().
		 */
		ppd->ibmaxlen = ppd->init_ibmaxlen;
		qib_set_mtu(ppd, mtu);

		spin_lock_irqsave(&ppd->lflags_lock, flags);
		ppd->lflags |= QIBL_IB_LINK_DISABLED;
		spin_unlock_irqrestore(&ppd->lflags_lock, flags);

		lastfail = dd->f_bringup_serdes(ppd);
		अगर (lastfail) अणु
			qib_devinfo(dd->pcidev,
				 "Failed to bringup IB port %u\n", ppd->port);
			lastfail = -ENETDOWN;
			जारी;
		पूर्ण

		portok++;
	पूर्ण

	अगर (!portok) अणु
		/* none of the ports initialized */
		अगर (!ret && lastfail)
			ret = lastfail;
		अन्यथा अगर (!ret)
			ret = -ENETDOWN;
		/* but जारी on, so we can debug cause */
	पूर्ण

	enable_chip(dd);

	init_piobuf_state(dd);

करोne:
	अगर (!ret) अणु
		/* chip is OK क्रम user apps; mark it as initialized */
		क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
			ppd = dd->pport + pidx;
			/*
			 * Set status even अगर port serdes is not initialized
			 * so that diags will work.
			 */
			*ppd->statusp |= QIB_STATUS_CHIP_PRESENT |
				QIB_STATUS_INITTED;
			अगर (!ppd->link_speed_enabled)
				जारी;
			अगर (dd->flags & QIB_HAS_SEND_DMA)
				ret = qib_setup_sdma(ppd);
			समयr_setup(&ppd->hol_समयr, qib_hol_event, 0);
			ppd->hol_state = QIB_HOL_UP;
		पूर्ण

		/* now we can enable all पूर्णांकerrupts from the chip */
		dd->f_set_पूर्णांकr_state(dd, 1);

		/*
		 * Setup to verअगरy we get an पूर्णांकerrupt, and fallback
		 * to an alternate अगर necessary and possible.
		 */
		mod_समयr(&dd->पूर्णांकrchk_समयr, jअगरfies + HZ/2);
		/* start stats retrieval समयr */
		mod_समयr(&dd->stats_समयr, jअगरfies + HZ * ACTIVITY_TIMER);
	पूर्ण

	/* अगर ret is non-zero, we probably should करो some cleanup here... */
	वापस ret;
पूर्ण

/*
 * These next two routines are placeholders in हाल we करोn't have per-arch
 * code क्रम controlling ग_लिखो combining.  If explicit control of ग_लिखो
 * combining is not available, perक्रमmance will probably be awful.
 */

पूर्णांक __attribute__((weak)) qib_enable_wc(काष्ठा qib_devdata *dd)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

व्योम __attribute__((weak)) qib_disable_wc(काष्ठा qib_devdata *dd)
अणु
पूर्ण

काष्ठा qib_devdata *qib_lookup(पूर्णांक unit)
अणु
	वापस xa_load(&qib_dev_table, unit);
पूर्ण

/*
 * Stop the समयrs during unit shutकरोwn, or after an error late
 * in initialization.
 */
अटल व्योम qib_stop_समयrs(काष्ठा qib_devdata *dd)
अणु
	काष्ठा qib_pportdata *ppd;
	पूर्णांक pidx;

	अगर (dd->stats_समयr.function)
		del_समयr_sync(&dd->stats_समयr);
	अगर (dd->पूर्णांकrchk_समयr.function)
		del_समयr_sync(&dd->पूर्णांकrchk_समयr);
	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		ppd = dd->pport + pidx;
		अगर (ppd->hol_समयr.function)
			del_समयr_sync(&ppd->hol_समयr);
		अगर (ppd->led_override_समयr.function) अणु
			del_समयr_sync(&ppd->led_override_समयr);
			atomic_set(&ppd->led_override_समयr_active, 0);
		पूर्ण
		अगर (ppd->symerr_clear_समयr.function)
			del_समयr_sync(&ppd->symerr_clear_समयr);
	पूर्ण
पूर्ण

/**
 * qib_shutकरोwn_device - shut करोwn a device
 * @dd: the qlogic_ib device
 *
 * This is called to make the device quiet when we are about to
 * unload the driver, and also when the device is administratively
 * disabled.   It करोes not मुक्त any data काष्ठाures.
 * Everything it करोes has to be setup again by qib_init(dd, 1)
 */
अटल व्योम qib_shutकरोwn_device(काष्ठा qib_devdata *dd)
अणु
	काष्ठा qib_pportdata *ppd;
	अचिन्हित pidx;

	अगर (dd->flags & QIB_SHUTDOWN)
		वापस;
	dd->flags |= QIB_SHUTDOWN;

	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		ppd = dd->pport + pidx;

		spin_lock_irq(&ppd->lflags_lock);
		ppd->lflags &= ~(QIBL_LINKDOWN | QIBL_LINKINIT |
				 QIBL_LINKARMED | QIBL_LINKACTIVE |
				 QIBL_LINKV);
		spin_unlock_irq(&ppd->lflags_lock);
		*ppd->statusp &= ~(QIB_STATUS_IB_CONF | QIB_STATUS_IB_READY);
	पूर्ण
	dd->flags &= ~QIB_INITTED;

	/* mask पूर्णांकerrupts, but not errors */
	dd->f_set_पूर्णांकr_state(dd, 0);

	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		ppd = dd->pport + pidx;
		dd->f_rcvctrl(ppd, QIB_RCVCTRL_TAILUPD_DIS |
				   QIB_RCVCTRL_CTXT_DIS |
				   QIB_RCVCTRL_INTRAVAIL_DIS |
				   QIB_RCVCTRL_PKEY_ENB, -1);
		/*
		 * Gracefully stop all sends allowing any in progress to
		 * trickle out first.
		 */
		dd->f_sendctrl(ppd, QIB_SENDCTRL_CLEAR);
	पूर्ण

	/*
	 * Enough क्रम anything that's going to trickle out to have actually
	 * करोne so.
	 */
	udelay(20);

	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		ppd = dd->pport + pidx;
		dd->f_setextled(ppd, 0); /* make sure LEDs are off */

		अगर (dd->flags & QIB_HAS_SEND_DMA)
			qib_tearकरोwn_sdma(ppd);

		dd->f_sendctrl(ppd, QIB_SENDCTRL_AVAIL_DIS |
				    QIB_SENDCTRL_SEND_DIS);
		/*
		 * Clear SerdesEnable.
		 * We can't count on पूर्णांकerrupts since we are stopping.
		 */
		dd->f_quiet_serdes(ppd);

		अगर (ppd->qib_wq) अणु
			destroy_workqueue(ppd->qib_wq);
			ppd->qib_wq = शून्य;
		पूर्ण
		qib_मुक्त_pportdata(ppd);
	पूर्ण

पूर्ण

/**
 * qib_मुक्त_ctxtdata - मुक्त a context's allocated data
 * @dd: the qlogic_ib device
 * @rcd: the ctxtdata काष्ठाure
 *
 * मुक्त up any allocated data क्रम a context
 * This should not touch anything that would affect a simultaneous
 * re-allocation of context data, because it is called after qib_mutex
 * is released (and can be called from reinit as well).
 * It should never change any chip state, or global driver state.
 */
व्योम qib_मुक्त_ctxtdata(काष्ठा qib_devdata *dd, काष्ठा qib_ctxtdata *rcd)
अणु
	अगर (!rcd)
		वापस;

	अगर (rcd->rcvhdrq) अणु
		dma_मुक्त_coherent(&dd->pcidev->dev, rcd->rcvhdrq_size,
				  rcd->rcvhdrq, rcd->rcvhdrq_phys);
		rcd->rcvhdrq = शून्य;
		अगर (rcd->rcvhdrtail_kvaddr) अणु
			dma_मुक्त_coherent(&dd->pcidev->dev, PAGE_SIZE,
					  rcd->rcvhdrtail_kvaddr,
					  rcd->rcvhdrqtailaddr_phys);
			rcd->rcvhdrtail_kvaddr = शून्य;
		पूर्ण
	पूर्ण
	अगर (rcd->rcvegrbuf) अणु
		अचिन्हित e;

		क्रम (e = 0; e < rcd->rcvegrbuf_chunks; e++) अणु
			व्योम *base = rcd->rcvegrbuf[e];
			माप_प्रकार size = rcd->rcvegrbuf_size;

			dma_मुक्त_coherent(&dd->pcidev->dev, size,
					  base, rcd->rcvegrbuf_phys[e]);
		पूर्ण
		kमुक्त(rcd->rcvegrbuf);
		rcd->rcvegrbuf = शून्य;
		kमुक्त(rcd->rcvegrbuf_phys);
		rcd->rcvegrbuf_phys = शून्य;
		rcd->rcvegrbuf_chunks = 0;
	पूर्ण

	kमुक्त(rcd->tid_pg_list);
	vमुक्त(rcd->user_event_mask);
	vमुक्त(rcd->subctxt_uregbase);
	vमुक्त(rcd->subctxt_rcvegrbuf);
	vमुक्त(rcd->subctxt_rcvhdr_base);
#अगर_घोषित CONFIG_DEBUG_FS
	kमुक्त(rcd->opstats);
	rcd->opstats = शून्य;
#पूर्ण_अगर
	kमुक्त(rcd);
पूर्ण

/*
 * Perक्रमm a PIO buffer bandwidth ग_लिखो test, to verअगरy proper प्रणाली
 * configuration.  Even when all the setup calls work, occasionally
 * BIOS or other issues can prevent ग_लिखो combining from working, or
 * can cause other bandwidth problems to the chip.
 *
 * This test simply ग_लिखोs the same buffer over and over again, and
 * measures बंद to the peak bandwidth to the chip (not testing
 * data bandwidth to the wire).   On chips that use an address-based
 * trigger to send packets to the wire, this is easy.  On chips that
 * use a count to trigger, we want to make sure that the packet करोesn't
 * go out on the wire, or trigger flow control checks.
 */
अटल व्योम qib_verअगरy_pioperf(काष्ठा qib_devdata *dd)
अणु
	u32 pbnum, cnt, lcnt;
	u32 __iomem *piobuf;
	u32 *addr;
	u64 msecs, emsecs;

	piobuf = dd->f_माला_लोendbuf(dd->pport, 0ULL, &pbnum);
	अगर (!piobuf) अणु
		qib_devinfo(dd->pcidev,
			 "No PIObufs for checking perf, skipping\n");
		वापस;
	पूर्ण

	/*
	 * Enough to give us a reasonable test, less than piobuf size, and
	 * likely multiple of store buffer length.
	 */
	cnt = 1024;

	addr = vदो_स्मृति(cnt);
	अगर (!addr)
		जाओ करोne;

	preempt_disable();  /* we want reasonably accurate elapsed समय */
	msecs = 1 + jअगरfies_to_msecs(jअगरfies);
	क्रम (lcnt = 0; lcnt < 10000U; lcnt++) अणु
		/* रुको until we cross msec boundary */
		अगर (jअगरfies_to_msecs(jअगरfies) >= msecs)
			अवरोध;
		udelay(1);
	पूर्ण

	dd->f_set_armlaunch(dd, 0);

	/*
	 * length 0, no dwords actually sent
	 */
	ग_लिखोq(0, piobuf);
	qib_flush_wc();

	/*
	 * This is only roughly accurate, since even with preempt we
	 * still take पूर्णांकerrupts that could take a जबतक.   Running क्रम
	 * >= 5 msec seems to get us "close enough" to accurate values.
	 */
	msecs = jअगरfies_to_msecs(jअगरfies);
	क्रम (emsecs = lcnt = 0; emsecs <= 5UL; lcnt++) अणु
		qib_pio_copy(piobuf + 64, addr, cnt >> 2);
		emsecs = jअगरfies_to_msecs(jअगरfies) - msecs;
	पूर्ण

	/* 1 GiB/sec, slightly over IB SDR line rate */
	अगर (lcnt < (emsecs * 1024U))
		qib_dev_err(dd,
			    "Performance problem: bandwidth to PIO buffers is only %u MiB/sec\n",
			    lcnt / (u32) emsecs);

	preempt_enable();

	vमुक्त(addr);

करोne:
	/* disarm piobuf, so it's available again */
	dd->f_sendctrl(dd->pport, QIB_SENDCTRL_DISARM_BUF(pbnum));
	qib_sendbuf_करोne(dd, pbnum);
	dd->f_set_armlaunch(dd, 1);
पूर्ण

व्योम qib_मुक्त_devdata(काष्ठा qib_devdata *dd)
अणु
	अचिन्हित दीर्घ flags;

	xa_lock_irqsave(&qib_dev_table, flags);
	__xa_erase(&qib_dev_table, dd->unit);
	xa_unlock_irqrestore(&qib_dev_table, flags);

#अगर_घोषित CONFIG_DEBUG_FS
	qib_dbg_ibdev_निकास(&dd->verbs_dev);
#पूर्ण_अगर
	मुक्त_percpu(dd->पूर्णांक_counter);
	rvt_dealloc_device(&dd->verbs_dev.rdi);
पूर्ण

u64 qib_पूर्णांक_counter(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक cpu;
	u64 पूर्णांक_counter = 0;

	क्रम_each_possible_cpu(cpu)
		पूर्णांक_counter += *per_cpu_ptr(dd->पूर्णांक_counter, cpu);
	वापस पूर्णांक_counter;
पूर्ण

u64 qib_sps_पूर्णांकs(व्योम)
अणु
	अचिन्हित दीर्घ index, flags;
	काष्ठा qib_devdata *dd;
	u64 sps_पूर्णांकs = 0;

	xa_lock_irqsave(&qib_dev_table, flags);
	xa_क्रम_each(&qib_dev_table, index, dd) अणु
		sps_पूर्णांकs += qib_पूर्णांक_counter(dd);
	पूर्ण
	xa_unlock_irqrestore(&qib_dev_table, flags);
	वापस sps_पूर्णांकs;
पूर्ण

/*
 * Allocate our primary per-unit data काष्ठाure.  Must be करोne via verbs
 * allocator, because the verbs cleanup process both करोes cleanup and
 * मुक्त of the data काष्ठाure.
 * "extra" is क्रम chip-specअगरic data.
 */
काष्ठा qib_devdata *qib_alloc_devdata(काष्ठा pci_dev *pdev, माप_प्रकार extra)
अणु
	काष्ठा qib_devdata *dd;
	पूर्णांक ret, nports;

	/* extra is * number of ports */
	nports = extra / माप(काष्ठा qib_pportdata);
	dd = (काष्ठा qib_devdata *)rvt_alloc_device(माप(*dd) + extra,
						    nports);
	अगर (!dd)
		वापस ERR_PTR(-ENOMEM);

	ret = xa_alloc_irq(&qib_dev_table, &dd->unit, dd, xa_limit_32b,
			GFP_KERNEL);
	अगर (ret < 0) अणु
		qib_early_err(&pdev->dev,
			      "Could not allocate unit ID: error %d\n", -ret);
		जाओ bail;
	पूर्ण
	rvt_set_ibdev_name(&dd->verbs_dev.rdi, "%s%d", "qib", dd->unit);

	dd->पूर्णांक_counter = alloc_percpu(u64);
	अगर (!dd->पूर्णांक_counter) अणु
		ret = -ENOMEM;
		qib_early_err(&pdev->dev,
			      "Could not allocate per-cpu int_counter\n");
		जाओ bail;
	पूर्ण

	अगर (!qib_cpulist_count) अणु
		u32 count = num_online_cpus();

		qib_cpulist = kसुस्मृति(BITS_TO_LONGS(count), माप(दीर्घ),
				      GFP_KERNEL);
		अगर (qib_cpulist)
			qib_cpulist_count = count;
	पूर्ण
#अगर_घोषित CONFIG_DEBUG_FS
	qib_dbg_ibdev_init(&dd->verbs_dev);
#पूर्ण_अगर
	वापस dd;
bail:
	अगर (!list_empty(&dd->list))
		list_del_init(&dd->list);
	rvt_dealloc_device(&dd->verbs_dev.rdi);
	वापस ERR_PTR(ret);
पूर्ण

/*
 * Called from मुक्तze mode handlers, and from PCI error
 * reporting code.  Should be paranoid about state of
 * प्रणाली and data काष्ठाures.
 */
व्योम qib_disable_after_error(काष्ठा qib_devdata *dd)
अणु
	अगर (dd->flags & QIB_INITTED) अणु
		u32 pidx;

		dd->flags &= ~QIB_INITTED;
		अगर (dd->pport)
			क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
				काष्ठा qib_pportdata *ppd;

				ppd = dd->pport + pidx;
				अगर (dd->flags & QIB_PRESENT) अणु
					qib_set_linkstate(ppd,
						QIB_IB_LINKDOWN_DISABLE);
					dd->f_setextled(ppd, 0);
				पूर्ण
				*ppd->statusp &= ~QIB_STATUS_IB_READY;
			पूर्ण
	पूर्ण

	/*
	 * Mark as having had an error क्रम driver, and also
	 * क्रम /sys and status word mapped to user programs.
	 * This marks unit as not usable, until reset.
	 */
	अगर (dd->devstatusp)
		*dd->devstatusp |= QIB_STATUS_HWERROR;
पूर्ण

अटल व्योम qib_हटाओ_one(काष्ठा pci_dev *);
अटल पूर्णांक qib_init_one(काष्ठा pci_dev *, स्थिर काष्ठा pci_device_id *);
अटल व्योम qib_shutकरोwn_one(काष्ठा pci_dev *);

#घोषणा DRIVER_LOAD_MSG "Intel " QIB_DRV_NAME " loaded: "
#घोषणा PFX QIB_DRV_NAME ": "

अटल स्थिर काष्ठा pci_device_id qib_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_PATHSCALE, PCI_DEVICE_ID_QLOGIC_IB_6120) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_IB_7220) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, PCI_DEVICE_ID_QLOGIC_IB_7322) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, qib_pci_tbl);

अटल काष्ठा pci_driver qib_driver = अणु
	.name = QIB_DRV_NAME,
	.probe = qib_init_one,
	.हटाओ = qib_हटाओ_one,
	.shutकरोwn = qib_shutकरोwn_one,
	.id_table = qib_pci_tbl,
	.err_handler = &qib_pci_err_handler,
पूर्ण;

#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA

अटल पूर्णांक qib_notअगरy_dca(काष्ठा notअगरier_block *, अचिन्हित दीर्घ, व्योम *);
अटल काष्ठा notअगरier_block dca_notअगरier = अणु
	.notअगरier_call  = qib_notअगरy_dca,
	.next           = शून्य,
	.priority       = 0
पूर्ण;

अटल पूर्णांक qib_notअगरy_dca_device(काष्ठा device *device, व्योम *data)
अणु
	काष्ठा qib_devdata *dd = dev_get_drvdata(device);
	अचिन्हित दीर्घ event = *(अचिन्हित दीर्घ *)data;

	वापस dd->f_notअगरy_dca(dd, event);
पूर्ण

अटल पूर्णांक qib_notअगरy_dca(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
					  व्योम *p)
अणु
	पूर्णांक rval;

	rval = driver_क्रम_each_device(&qib_driver.driver, शून्य,
				      &event, qib_notअगरy_dca_device);
	वापस rval ? NOTIFY_BAD : NOTIFY_DONE;
पूर्ण

#पूर्ण_अगर

/*
 * Do all the generic driver unit- and chip-independent memory
 * allocation and initialization.
 */
अटल पूर्णांक __init qib_ib_init(व्योम)
अणु
	पूर्णांक ret;

	ret = qib_dev_init();
	अगर (ret)
		जाओ bail;

	/*
	 * These must be called beक्रमe the driver is रेजिस्टरed with
	 * the PCI subप्रणाली.
	 */
#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA
	dca_रेजिस्टर_notअगरy(&dca_notअगरier);
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_FS
	qib_dbg_init();
#पूर्ण_अगर
	ret = pci_रेजिस्टर_driver(&qib_driver);
	अगर (ret < 0) अणु
		pr_err("Unable to register driver: error %d\n", -ret);
		जाओ bail_dev;
	पूर्ण

	/* not fatal अगर it करोesn't work */
	अगर (qib_init_qibfs())
		pr_err("Unable to register ipathfs\n");
	जाओ bail; /* all OK */

bail_dev:
#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA
	dca_unरेजिस्टर_notअगरy(&dca_notअगरier);
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_FS
	qib_dbg_निकास();
#पूर्ण_अगर
	qib_dev_cleanup();
bail:
	वापस ret;
पूर्ण

module_init(qib_ib_init);

/*
 * Do the non-unit driver cleanup, memory मुक्त, etc. at unload.
 */
अटल व्योम __निकास qib_ib_cleanup(व्योम)
अणु
	पूर्णांक ret;

	ret = qib_निकास_qibfs();
	अगर (ret)
		pr_err(
			"Unable to cleanup counter filesystem: error %d\n",
			-ret);

#अगर_घोषित CONFIG_INFINIBAND_QIB_DCA
	dca_unरेजिस्टर_notअगरy(&dca_notअगरier);
#पूर्ण_अगर
	pci_unरेजिस्टर_driver(&qib_driver);
#अगर_घोषित CONFIG_DEBUG_FS
	qib_dbg_निकास();
#पूर्ण_अगर

	qib_cpulist_count = 0;
	kमुक्त(qib_cpulist);

	WARN_ON(!xa_empty(&qib_dev_table));
	qib_dev_cleanup();
पूर्ण

module_निकास(qib_ib_cleanup);

/* this can only be called after a successful initialization */
अटल व्योम cleanup_device_data(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक ctxt;
	पूर्णांक pidx;
	काष्ठा qib_ctxtdata **पंचांगp;
	अचिन्हित दीर्घ flags;

	/* users can't करो anything more with chip */
	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		अगर (dd->pport[pidx].statusp)
			*dd->pport[pidx].statusp &= ~QIB_STATUS_CHIP_PRESENT;

		spin_lock(&dd->pport[pidx].cc_shaकरोw_lock);

		kमुक्त(dd->pport[pidx].congestion_entries);
		dd->pport[pidx].congestion_entries = शून्य;
		kमुक्त(dd->pport[pidx].ccti_entries);
		dd->pport[pidx].ccti_entries = शून्य;
		kमुक्त(dd->pport[pidx].ccti_entries_shaकरोw);
		dd->pport[pidx].ccti_entries_shaकरोw = शून्य;
		kमुक्त(dd->pport[pidx].congestion_entries_shaकरोw);
		dd->pport[pidx].congestion_entries_shaकरोw = शून्य;

		spin_unlock(&dd->pport[pidx].cc_shaकरोw_lock);
	पूर्ण

	qib_disable_wc(dd);

	अगर (dd->pioavailregs_dma) अणु
		dma_मुक्त_coherent(&dd->pcidev->dev, PAGE_SIZE,
				  (व्योम *) dd->pioavailregs_dma,
				  dd->pioavailregs_phys);
		dd->pioavailregs_dma = शून्य;
	पूर्ण

	अगर (dd->pageshaकरोw) अणु
		काष्ठा page **पंचांगpp = dd->pageshaकरोw;
		dma_addr_t *पंचांगpd = dd->physshaकरोw;
		पूर्णांक i;

		क्रम (ctxt = 0; ctxt < dd->cfgctxts; ctxt++) अणु
			पूर्णांक ctxt_tidbase = ctxt * dd->rcvtidcnt;
			पूर्णांक maxtid = ctxt_tidbase + dd->rcvtidcnt;

			क्रम (i = ctxt_tidbase; i < maxtid; i++) अणु
				अगर (!पंचांगpp[i])
					जारी;
				pci_unmap_page(dd->pcidev, पंचांगpd[i],
					       PAGE_SIZE, PCI_DMA_FROMDEVICE);
				qib_release_user_pages(&पंचांगpp[i], 1);
				पंचांगpp[i] = शून्य;
			पूर्ण
		पूर्ण

		dd->pageshaकरोw = शून्य;
		vमुक्त(पंचांगpp);
		dd->physshaकरोw = शून्य;
		vमुक्त(पंचांगpd);
	पूर्ण

	/*
	 * Free any resources still in use (usually just kernel contexts)
	 * at unload; we करो क्रम ctxtcnt, because that's what we allocate.
	 * We acquire lock to be really paranoid that rcd isn't being
	 * accessed from some पूर्णांकerrupt-related code (that should not happen,
	 * but best to be sure).
	 */
	spin_lock_irqsave(&dd->uctxt_lock, flags);
	पंचांगp = dd->rcd;
	dd->rcd = शून्य;
	spin_unlock_irqrestore(&dd->uctxt_lock, flags);
	क्रम (ctxt = 0; पंचांगp && ctxt < dd->ctxtcnt; ctxt++) अणु
		काष्ठा qib_ctxtdata *rcd = पंचांगp[ctxt];

		पंचांगp[ctxt] = शून्य; /* debugging paranoia */
		qib_मुक्त_ctxtdata(dd, rcd);
	पूर्ण
	kमुक्त(पंचांगp);
पूर्ण

/*
 * Clean up on unit shutकरोwn, or error during unit load after
 * successful initialization.
 */
अटल व्योम qib_postinit_cleanup(काष्ठा qib_devdata *dd)
अणु
	/*
	 * Clean up chip-specअगरic stuff.
	 * We check क्रम शून्य here, because it's outside
	 * the kregbase check, and we need to call it
	 * after the मुक्त_irq.  Thus it's possible that
	 * the function poपूर्णांकers were never initialized.
	 */
	अगर (dd->f_cleanup)
		dd->f_cleanup(dd);

	qib_pcie_ddcleanup(dd);

	cleanup_device_data(dd);

	qib_मुक्त_devdata(dd);
पूर्ण

अटल पूर्णांक qib_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक ret, j, pidx, initfail;
	काष्ठा qib_devdata *dd = शून्य;

	ret = qib_pcie_init(pdev, ent);
	अगर (ret)
		जाओ bail;

	/*
	 * Do device-specअगरic initialiation, function table setup, dd
	 * allocation, etc.
	 */
	चयन (ent->device) अणु
	हाल PCI_DEVICE_ID_QLOGIC_IB_6120:
#अगर_घोषित CONFIG_PCI_MSI
		dd = qib_init_iba6120_funcs(pdev, ent);
#अन्यथा
		qib_early_err(&pdev->dev,
			"Intel PCIE device 0x%x cannot work if CONFIG_PCI_MSI is not enabled\n",
			ent->device);
		dd = ERR_PTR(-ENODEV);
#पूर्ण_अगर
		अवरोध;

	हाल PCI_DEVICE_ID_QLOGIC_IB_7220:
		dd = qib_init_iba7220_funcs(pdev, ent);
		अवरोध;

	हाल PCI_DEVICE_ID_QLOGIC_IB_7322:
		dd = qib_init_iba7322_funcs(pdev, ent);
		अवरोध;

	शेष:
		qib_early_err(&pdev->dev,
			"Failing on unknown Intel deviceid 0x%x\n",
			ent->device);
		ret = -ENODEV;
	पूर्ण

	अगर (IS_ERR(dd))
		ret = PTR_ERR(dd);
	अगर (ret)
		जाओ bail; /* error alपढ़ोy prपूर्णांकed */

	ret = qib_create_workqueues(dd);
	अगर (ret)
		जाओ bail;

	/* करो the generic initialization */
	initfail = qib_init(dd, 0);

	ret = qib_रेजिस्टर_ib_device(dd);

	/*
	 * Now पढ़ोy क्रम use.  this should be cleared whenever we
	 * detect a reset, or initiate one.  If earlier failure,
	 * we still create devices, so diags, etc. can be used
	 * to determine cause of problem.
	 */
	अगर (!qib_mini_init && !initfail && !ret)
		dd->flags |= QIB_INITTED;

	j = qib_device_create(dd);
	अगर (j)
		qib_dev_err(dd, "Failed to create /dev devices: %d\n", -j);
	j = qibfs_add(dd);
	अगर (j)
		qib_dev_err(dd, "Failed filesystem setup for counters: %d\n",
			    -j);

	अगर (qib_mini_init || initfail || ret) अणु
		qib_stop_समयrs(dd);
		flush_workqueue(ib_wq);
		क्रम (pidx = 0; pidx < dd->num_pports; ++pidx)
			dd->f_quiet_serdes(dd->pport + pidx);
		अगर (qib_mini_init)
			जाओ bail;
		अगर (!j) अणु
			(व्योम) qibfs_हटाओ(dd);
			qib_device_हटाओ(dd);
		पूर्ण
		अगर (!ret)
			qib_unरेजिस्टर_ib_device(dd);
		qib_postinit_cleanup(dd);
		अगर (initfail)
			ret = initfail;
		जाओ bail;
	पूर्ण

	ret = qib_enable_wc(dd);
	अगर (ret) अणु
		qib_dev_err(dd,
			"Write combining not enabled (err %d): performance may be poor\n",
			-ret);
		ret = 0;
	पूर्ण

	qib_verअगरy_pioperf(dd);
bail:
	वापस ret;
पूर्ण

अटल व्योम qib_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा qib_devdata *dd = pci_get_drvdata(pdev);
	पूर्णांक ret;

	/* unरेजिस्टर from IB core */
	qib_unरेजिस्टर_ib_device(dd);

	/*
	 * Disable the IB link, disable पूर्णांकerrupts on the device,
	 * clear dma engines, etc.
	 */
	अगर (!qib_mini_init)
		qib_shutकरोwn_device(dd);

	qib_stop_समयrs(dd);

	/* रुको until all of our (qsfp) queue_work() calls complete */
	flush_workqueue(ib_wq);

	ret = qibfs_हटाओ(dd);
	अगर (ret)
		qib_dev_err(dd, "Failed counters filesystem cleanup: %d\n",
			    -ret);

	qib_device_हटाओ(dd);

	qib_postinit_cleanup(dd);
पूर्ण

अटल व्योम qib_shutकरोwn_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा qib_devdata *dd = pci_get_drvdata(pdev);

	qib_shutकरोwn_device(dd);
पूर्ण

/**
 * qib_create_rcvhdrq - create a receive header queue
 * @dd: the qlogic_ib device
 * @rcd: the context data
 *
 * This must be contiguous memory (from an i/o perspective), and must be
 * DMA'able (which means क्रम some प्रणालीs, it will go through an IOMMU,
 * or be क्रमced पूर्णांकo a low address range).
 */
पूर्णांक qib_create_rcvhdrq(काष्ठा qib_devdata *dd, काष्ठा qib_ctxtdata *rcd)
अणु
	अचिन्हित amt;
	पूर्णांक old_node_id;

	अगर (!rcd->rcvhdrq) अणु
		dma_addr_t phys_hdrqtail;
		gfp_t gfp_flags;

		amt = ALIGN(dd->rcvhdrcnt * dd->rcvhdrentsize *
			    माप(u32), PAGE_SIZE);
		gfp_flags = (rcd->ctxt >= dd->first_user_ctxt) ?
			GFP_USER : GFP_KERNEL;

		old_node_id = dev_to_node(&dd->pcidev->dev);
		set_dev_node(&dd->pcidev->dev, rcd->node_id);
		rcd->rcvhdrq = dma_alloc_coherent(
			&dd->pcidev->dev, amt, &rcd->rcvhdrq_phys,
			gfp_flags | __GFP_COMP);
		set_dev_node(&dd->pcidev->dev, old_node_id);

		अगर (!rcd->rcvhdrq) अणु
			qib_dev_err(dd,
				"attempt to allocate %d bytes for ctxt %u rcvhdrq failed\n",
				amt, rcd->ctxt);
			जाओ bail;
		पूर्ण

		अगर (rcd->ctxt >= dd->first_user_ctxt) अणु
			rcd->user_event_mask = vदो_स्मृति_user(PAGE_SIZE);
			अगर (!rcd->user_event_mask)
				जाओ bail_मुक्त_hdrq;
		पूर्ण

		अगर (!(dd->flags & QIB_NODMA_RTAIL)) अणु
			set_dev_node(&dd->pcidev->dev, rcd->node_id);
			rcd->rcvhdrtail_kvaddr = dma_alloc_coherent(
				&dd->pcidev->dev, PAGE_SIZE, &phys_hdrqtail,
				gfp_flags);
			set_dev_node(&dd->pcidev->dev, old_node_id);
			अगर (!rcd->rcvhdrtail_kvaddr)
				जाओ bail_मुक्त;
			rcd->rcvhdrqtailaddr_phys = phys_hdrqtail;
		पूर्ण

		rcd->rcvhdrq_size = amt;
	पूर्ण

	/* clear क्रम security and sanity on each use */
	स_रखो(rcd->rcvhdrq, 0, rcd->rcvhdrq_size);
	अगर (rcd->rcvhdrtail_kvaddr)
		स_रखो(rcd->rcvhdrtail_kvaddr, 0, PAGE_SIZE);
	वापस 0;

bail_मुक्त:
	qib_dev_err(dd,
		"attempt to allocate 1 page for ctxt %u rcvhdrqtailaddr failed\n",
		rcd->ctxt);
	vमुक्त(rcd->user_event_mask);
	rcd->user_event_mask = शून्य;
bail_मुक्त_hdrq:
	dma_मुक्त_coherent(&dd->pcidev->dev, amt, rcd->rcvhdrq,
			  rcd->rcvhdrq_phys);
	rcd->rcvhdrq = शून्य;
bail:
	वापस -ENOMEM;
पूर्ण

/**
 * qib_setup_eagerbufs - allocate eager buffers, both kernel and user contexts.
 * @rcd: the context we are setting up.
 *
 * Allocate the eager TID buffers and program them पूर्णांकo hip.
 * They are no दीर्घer completely contiguous, we करो multiple allocation
 * calls.  Otherwise we get the OOM code involved, by asking क्रम too
 * much per call, with disastrous results on some kernels.
 */
पूर्णांक qib_setup_eagerbufs(काष्ठा qib_ctxtdata *rcd)
अणु
	काष्ठा qib_devdata *dd = rcd->dd;
	अचिन्हित e, egrcnt, egrperchunk, chunk, egrsize, egroff;
	माप_प्रकार size;
	gfp_t gfp_flags;
	पूर्णांक old_node_id;

	/*
	 * GFP_USER, but without GFP_FS, so buffer cache can be
	 * coalesced (we hope); otherwise, even at order 4,
	 * heavy fileप्रणाली activity makes these fail, and we can
	 * use compound pages.
	 */
	gfp_flags = __GFP_RECLAIM | __GFP_IO | __GFP_COMP;

	egrcnt = rcd->rcvegrcnt;
	egroff = rcd->rcvegr_tid_base;
	egrsize = dd->rcvegrbufsize;

	chunk = rcd->rcvegrbuf_chunks;
	egrperchunk = rcd->rcvegrbufs_perchunk;
	size = rcd->rcvegrbuf_size;
	अगर (!rcd->rcvegrbuf) अणु
		rcd->rcvegrbuf =
			kसुस्मृति_node(chunk, माप(rcd->rcvegrbuf[0]),
				     GFP_KERNEL, rcd->node_id);
		अगर (!rcd->rcvegrbuf)
			जाओ bail;
	पूर्ण
	अगर (!rcd->rcvegrbuf_phys) अणु
		rcd->rcvegrbuf_phys =
			kदो_स्मृति_array_node(chunk,
					   माप(rcd->rcvegrbuf_phys[0]),
					   GFP_KERNEL, rcd->node_id);
		अगर (!rcd->rcvegrbuf_phys)
			जाओ bail_rcvegrbuf;
	पूर्ण
	क्रम (e = 0; e < rcd->rcvegrbuf_chunks; e++) अणु
		अगर (rcd->rcvegrbuf[e])
			जारी;

		old_node_id = dev_to_node(&dd->pcidev->dev);
		set_dev_node(&dd->pcidev->dev, rcd->node_id);
		rcd->rcvegrbuf[e] =
			dma_alloc_coherent(&dd->pcidev->dev, size,
					   &rcd->rcvegrbuf_phys[e],
					   gfp_flags);
		set_dev_node(&dd->pcidev->dev, old_node_id);
		अगर (!rcd->rcvegrbuf[e])
			जाओ bail_rcvegrbuf_phys;
	पूर्ण

	rcd->rcvegr_phys = rcd->rcvegrbuf_phys[0];

	क्रम (e = chunk = 0; chunk < rcd->rcvegrbuf_chunks; chunk++) अणु
		dma_addr_t pa = rcd->rcvegrbuf_phys[chunk];
		अचिन्हित i;

		/* clear क्रम security and sanity on each use */
		स_रखो(rcd->rcvegrbuf[chunk], 0, size);

		क्रम (i = 0; e < egrcnt && i < egrperchunk; e++, i++) अणु
			dd->f_put_tid(dd, e + egroff +
					  (u64 __iomem *)
					  ((अक्षर __iomem *)
					   dd->kregbase +
					   dd->rcvegrbase),
					  RCVHQ_RCV_TYPE_EAGER, pa);
			pa += egrsize;
		पूर्ण
		cond_resched(); /* करोn't hog the cpu */
	पूर्ण

	वापस 0;

bail_rcvegrbuf_phys:
	क्रम (e = 0; e < rcd->rcvegrbuf_chunks && rcd->rcvegrbuf[e]; e++)
		dma_मुक्त_coherent(&dd->pcidev->dev, size,
				  rcd->rcvegrbuf[e], rcd->rcvegrbuf_phys[e]);
	kमुक्त(rcd->rcvegrbuf_phys);
	rcd->rcvegrbuf_phys = शून्य;
bail_rcvegrbuf:
	kमुक्त(rcd->rcvegrbuf);
	rcd->rcvegrbuf = शून्य;
bail:
	वापस -ENOMEM;
पूर्ण

/*
 * Note: Changes to this routine should be mirrored
 * क्रम the diagnostics routine qib_remap_ioaddr32().
 * There is also related code क्रम VL15 buffers in qib_init_7322_variables().
 * The tearकरोwn code that unmaps is in qib_pcie_ddcleanup()
 */
पूर्णांक init_chip_wc_pat(काष्ठा qib_devdata *dd, u32 vl15buflen)
अणु
	u64 __iomem *qib_kregbase = शून्य;
	व्योम __iomem *qib_piobase = शून्य;
	u64 __iomem *qib_userbase = शून्य;
	u64 qib_kreglen;
	u64 qib_pio2koffset = dd->piobufbase & 0xffffffff;
	u64 qib_pio4koffset = dd->piobufbase >> 32;
	u64 qib_pio2klen = dd->piobcnt2k * dd->palign;
	u64 qib_pio4klen = dd->piobcnt4k * dd->align4k;
	u64 qib_physaddr = dd->physaddr;
	u64 qib_piolen;
	u64 qib_userlen = 0;

	/*
	 * Free the old mapping because the kernel will try to reuse the
	 * old mapping and not create a new mapping with the
	 * ग_लिखो combining attribute.
	 */
	iounmap(dd->kregbase);
	dd->kregbase = शून्य;

	/*
	 * Assumes chip address space looks like:
	 *	- kregs + sregs + cregs + uregs (in any order)
	 *	- piobufs (2K and 4K bufs in either order)
	 * or:
	 *	- kregs + sregs + cregs (in any order)
	 *	- piobufs (2K and 4K bufs in either order)
	 *	- uregs
	 */
	अगर (dd->piobcnt4k == 0) अणु
		qib_kreglen = qib_pio2koffset;
		qib_piolen = qib_pio2klen;
	पूर्ण अन्यथा अगर (qib_pio2koffset < qib_pio4koffset) अणु
		qib_kreglen = qib_pio2koffset;
		qib_piolen = qib_pio4koffset + qib_pio4klen - qib_kreglen;
	पूर्ण अन्यथा अणु
		qib_kreglen = qib_pio4koffset;
		qib_piolen = qib_pio2koffset + qib_pio2klen - qib_kreglen;
	पूर्ण
	qib_piolen += vl15buflen;
	/* Map just the configured ports (not all hw ports) */
	अगर (dd->uregbase > qib_kreglen)
		qib_userlen = dd->ureg_align * dd->cfgctxts;

	/* Sanity checks passed, now create the new mappings */
	qib_kregbase = ioremap(qib_physaddr, qib_kreglen);
	अगर (!qib_kregbase)
		जाओ bail;

	qib_piobase = ioremap_wc(qib_physaddr + qib_kreglen, qib_piolen);
	अगर (!qib_piobase)
		जाओ bail_kregbase;

	अगर (qib_userlen) अणु
		qib_userbase = ioremap(qib_physaddr + dd->uregbase,
					       qib_userlen);
		अगर (!qib_userbase)
			जाओ bail_piobase;
	पूर्ण

	dd->kregbase = qib_kregbase;
	dd->kregend = (u64 __iomem *)
		((अक्षर __iomem *) qib_kregbase + qib_kreglen);
	dd->piobase = qib_piobase;
	dd->pio2kbase = (व्योम __iomem *)
		(((अक्षर __iomem *) dd->piobase) +
		 qib_pio2koffset - qib_kreglen);
	अगर (dd->piobcnt4k)
		dd->pio4kbase = (व्योम __iomem *)
			(((अक्षर __iomem *) dd->piobase) +
			 qib_pio4koffset - qib_kreglen);
	अगर (qib_userlen)
		/* ureg will now be accessed relative to dd->userbase */
		dd->userbase = qib_userbase;
	वापस 0;

bail_piobase:
	iounmap(qib_piobase);
bail_kregbase:
	iounmap(qib_kregbase);
bail:
	वापस -ENOMEM;
पूर्ण
