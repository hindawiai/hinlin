<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SN Platक्रमm GRU Driver
 *
 *              खाता OPERATIONS & DRIVER INITIALIZATION
 *
 * This file supports the user प्रणाली call क्रम file खोलो, बंद, mmap, etc.
 * This also incudes the driver initialization code.
 *
 *  (C) Copyright 2020 Hewlett Packard Enterprise Development LP
 *  Copyright (c) 2008-2014 Silicon Graphics, Inc.  All Rights Reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/device.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/uaccess.h>
#अगर_घोषित CONFIG_X86_64
#समावेश <यंत्र/uv/uv_irq.h>
#पूर्ण_अगर
#समावेश <यंत्र/uv/uv.h>
#समावेश "gru.h"
#समावेश "grulib.h"
#समावेश "grutables.h"

#समावेश <यंत्र/uv/uv_hub.h>
#समावेश <यंत्र/uv/uv_mmrs.h>

काष्ठा gru_blade_state *gru_base[GRU_MAX_BLADES] __पढ़ो_mostly;
अचिन्हित दीर्घ gru_start_paddr __पढ़ो_mostly;
व्योम *gru_start_vaddr __पढ़ो_mostly;
अचिन्हित दीर्घ gru_end_paddr __पढ़ो_mostly;
अचिन्हित पूर्णांक gru_max_gids __पढ़ो_mostly;
काष्ठा gru_stats_s gru_stats;

/* Guaranteed user available resources on each node */
अटल पूर्णांक max_user_cbrs, max_user_dsr_bytes;

अटल काष्ठा miscdevice gru_miscdev;

अटल पूर्णांक gru_supported(व्योम)
अणु
	वापस is_uv_प्रणाली() &&
		(uv_hub_info->hub_revision < UV3_HUB_REVISION_BASE);
पूर्ण

/*
 * gru_vma_बंद
 *
 * Called when unmapping a device mapping. Frees all gru resources
 * and tables beदीर्घing to the vma.
 */
अटल व्योम gru_vma_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा gru_vma_data *vdata;
	काष्ठा gru_thपढ़ो_state *gts;
	काष्ठा list_head *entry, *next;

	अगर (!vma->vm_निजी_data)
		वापस;

	vdata = vma->vm_निजी_data;
	vma->vm_निजी_data = शून्य;
	gru_dbg(grudev, "vma %p, file %p, vdata %p\n", vma, vma->vm_file,
				vdata);
	list_क्रम_each_safe(entry, next, &vdata->vd_head) अणु
		gts =
		    list_entry(entry, काष्ठा gru_thपढ़ो_state, ts_next);
		list_del(&gts->ts_next);
		mutex_lock(&gts->ts_ctxlock);
		अगर (gts->ts_gru)
			gru_unload_context(gts, 0);
		mutex_unlock(&gts->ts_ctxlock);
		gts_drop(gts);
	पूर्ण
	kमुक्त(vdata);
	STAT(vdata_मुक्त);
पूर्ण

/*
 * gru_file_mmap
 *
 * Called when mmapping the device.  Initializes the vma with a fault handler
 * and निजी data काष्ठाure necessary to allocate, track, and मुक्त the
 * underlying pages.
 */
अटल पूर्णांक gru_file_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर ((vma->vm_flags & (VM_SHARED | VM_WRITE)) != (VM_SHARED | VM_WRITE))
		वापस -EPERM;

	अगर (vma->vm_start & (GRU_GSEG_PAGESIZE - 1) ||
				vma->vm_end & (GRU_GSEG_PAGESIZE - 1))
		वापस -EINVAL;

	vma->vm_flags |= VM_IO | VM_PFNMAP | VM_LOCKED |
			 VM_DONTCOPY | VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_page_prot = PAGE_SHARED;
	vma->vm_ops = &gru_vm_ops;

	vma->vm_निजी_data = gru_alloc_vma_data(vma, 0);
	अगर (!vma->vm_निजी_data)
		वापस -ENOMEM;

	gru_dbg(grudev, "file %p, vaddr 0x%lx, vma %p, vdata %p\n",
		file, vma->vm_start, vma, vma->vm_निजी_data);
	वापस 0;
पूर्ण

/*
 * Create a new GRU context
 */
अटल पूर्णांक gru_create_new_context(अचिन्हित दीर्घ arg)
अणु
	काष्ठा gru_create_context_req req;
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा gru_vma_data *vdata;
	पूर्णांक ret = -EINVAL;

	अगर (copy_from_user(&req, (व्योम __user *)arg, माप(req)))
		वापस -EFAULT;

	अगर (req.data_segment_bytes > max_user_dsr_bytes)
		वापस -EINVAL;
	अगर (req.control_blocks > max_user_cbrs || !req.maximum_thपढ़ो_count)
		वापस -EINVAL;

	अगर (!(req.options & GRU_OPT_MISS_MASK))
		req.options |= GRU_OPT_MISS_FMM_INTR;

	mmap_ग_लिखो_lock(current->mm);
	vma = gru_find_vma(req.gseg);
	अगर (vma) अणु
		vdata = vma->vm_निजी_data;
		vdata->vd_user_options = req.options;
		vdata->vd_dsr_au_count =
		    GRU_DS_BYTES_TO_AU(req.data_segment_bytes);
		vdata->vd_cbr_au_count = GRU_CB_COUNT_TO_AU(req.control_blocks);
		vdata->vd_tlb_preload_count = req.tlb_preload_count;
		ret = 0;
	पूर्ण
	mmap_ग_लिखो_unlock(current->mm);

	वापस ret;
पूर्ण

/*
 * Get GRU configuration info (temp - क्रम emulator testing)
 */
अटल दीर्घ gru_get_config_info(अचिन्हित दीर्घ arg)
अणु
	काष्ठा gru_config_info info;
	पूर्णांक nodesperblade;

	अगर (num_online_nodes() > 1 &&
			(uv_node_to_blade_id(1) == uv_node_to_blade_id(0)))
		nodesperblade = 2;
	अन्यथा
		nodesperblade = 1;
	स_रखो(&info, 0, माप(info));
	info.cpus = num_online_cpus();
	info.nodes = num_online_nodes();
	info.blades = info.nodes / nodesperblade;
	info.chiplets = GRU_CHIPLETS_PER_BLADE * info.blades;

	अगर (copy_to_user((व्योम __user *)arg, &info, माप(info)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/*
 * gru_file_unlocked_ioctl
 *
 * Called to update file attributes via IOCTL calls.
 */
अटल दीर्घ gru_file_unlocked_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक req,
				    अचिन्हित दीर्घ arg)
अणु
	पूर्णांक err = -EBADRQC;

	gru_dbg(grudev, "file %p, req 0x%x, 0x%lx\n", file, req, arg);

	चयन (req) अणु
	हाल GRU_CREATE_CONTEXT:
		err = gru_create_new_context(arg);
		अवरोध;
	हाल GRU_SET_CONTEXT_OPTION:
		err = gru_set_context_option(arg);
		अवरोध;
	हाल GRU_USER_GET_EXCEPTION_DETAIL:
		err = gru_get_exception_detail(arg);
		अवरोध;
	हाल GRU_USER_UNLOAD_CONTEXT:
		err = gru_user_unload_context(arg);
		अवरोध;
	हाल GRU_USER_FLUSH_TLB:
		err = gru_user_flush_tlb(arg);
		अवरोध;
	हाल GRU_USER_CALL_OS:
		err = gru_handle_user_call_os(arg);
		अवरोध;
	हाल GRU_GET_GSEG_STATISTICS:
		err = gru_get_gseg_statistics(arg);
		अवरोध;
	हाल GRU_KTEST:
		err = gru_ktest(arg);
		अवरोध;
	हाल GRU_GET_CONFIG_INFO:
		err = gru_get_config_info(arg);
		अवरोध;
	हाल GRU_DUMP_CHIPLET_STATE:
		err = gru_dump_chiplet_request(arg);
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

/*
 * Called at init समय to build tables क्रम all GRUs that are present in the
 * प्रणाली.
 */
अटल व्योम gru_init_chiplet(काष्ठा gru_state *gru, अचिन्हित दीर्घ paddr,
			     व्योम *vaddr, पूर्णांक blade_id, पूर्णांक chiplet_id)
अणु
	spin_lock_init(&gru->gs_lock);
	spin_lock_init(&gru->gs_asid_lock);
	gru->gs_gru_base_paddr = paddr;
	gru->gs_gru_base_vaddr = vaddr;
	gru->gs_gid = blade_id * GRU_CHIPLETS_PER_BLADE + chiplet_id;
	gru->gs_blade = gru_base[blade_id];
	gru->gs_blade_id = blade_id;
	gru->gs_chiplet_id = chiplet_id;
	gru->gs_cbr_map = (GRU_CBR_AU == 64) ? ~0 : (1UL << GRU_CBR_AU) - 1;
	gru->gs_dsr_map = (1UL << GRU_DSR_AU) - 1;
	gru->gs_asid_limit = MAX_ASID;
	gru_tgh_flush_init(gru);
	अगर (gru->gs_gid >= gru_max_gids)
		gru_max_gids = gru->gs_gid + 1;
	gru_dbg(grudev, "bid %d, gid %d, vaddr %p (0x%lx)\n",
		blade_id, gru->gs_gid, gru->gs_gru_base_vaddr,
		gru->gs_gru_base_paddr);
पूर्ण

अटल पूर्णांक gru_init_tables(अचिन्हित दीर्घ gru_base_paddr, व्योम *gru_base_vaddr)
अणु
	पूर्णांक pnode, nid, bid, chip;
	पूर्णांक cbrs, dsrbytes, n;
	पूर्णांक order = get_order(माप(काष्ठा gru_blade_state));
	काष्ठा page *page;
	काष्ठा gru_state *gru;
	अचिन्हित दीर्घ paddr;
	व्योम *vaddr;

	max_user_cbrs = GRU_NUM_CB;
	max_user_dsr_bytes = GRU_NUM_DSR_BYTES;
	क्रम_each_possible_blade(bid) अणु
		pnode = uv_blade_to_pnode(bid);
		nid = uv_blade_to_memory_nid(bid);/* -1 अगर no memory on blade */
		page = alloc_pages_node(nid, GFP_KERNEL, order);
		अगर (!page)
			जाओ fail;
		gru_base[bid] = page_address(page);
		स_रखो(gru_base[bid], 0, माप(काष्ठा gru_blade_state));
		gru_base[bid]->bs_lru_gru = &gru_base[bid]->bs_grus[0];
		spin_lock_init(&gru_base[bid]->bs_lock);
		init_rwsem(&gru_base[bid]->bs_kgts_sema);

		dsrbytes = 0;
		cbrs = 0;
		क्रम (gru = gru_base[bid]->bs_grus, chip = 0;
				chip < GRU_CHIPLETS_PER_BLADE;
				chip++, gru++) अणु
			paddr = gru_chiplet_paddr(gru_base_paddr, pnode, chip);
			vaddr = gru_chiplet_vaddr(gru_base_vaddr, pnode, chip);
			gru_init_chiplet(gru, paddr, vaddr, bid, chip);
			n = hweight64(gru->gs_cbr_map) * GRU_CBR_AU_SIZE;
			cbrs = max(cbrs, n);
			n = hweight64(gru->gs_dsr_map) * GRU_DSR_AU_BYTES;
			dsrbytes = max(dsrbytes, n);
		पूर्ण
		max_user_cbrs = min(max_user_cbrs, cbrs);
		max_user_dsr_bytes = min(max_user_dsr_bytes, dsrbytes);
	पूर्ण

	वापस 0;

fail:
	क्रम (bid--; bid >= 0; bid--)
		मुक्त_pages((अचिन्हित दीर्घ)gru_base[bid], order);
	वापस -ENOMEM;
पूर्ण

अटल व्योम gru_मुक्त_tables(व्योम)
अणु
	पूर्णांक bid;
	पूर्णांक order = get_order(माप(काष्ठा gru_state) *
			      GRU_CHIPLETS_PER_BLADE);

	क्रम (bid = 0; bid < GRU_MAX_BLADES; bid++)
		मुक्त_pages((अचिन्हित दीर्घ)gru_base[bid], order);
पूर्ण

अटल अचिन्हित दीर्घ gru_chiplet_cpu_to_mmr(पूर्णांक chiplet, पूर्णांक cpu, पूर्णांक *corep)
अणु
	अचिन्हित दीर्घ mmr = 0;
	पूर्णांक core;

	/*
	 * We target the cores of a blade and not the hyperthपढ़ोs themselves.
	 * There is a max of 8 cores per socket and 2 sockets per blade,
	 * making क्रम a max total of 16 cores (i.e., 16 CPUs without
	 * hyperthपढ़ोing and 32 CPUs with hyperthपढ़ोing).
	 */
	core = uv_cpu_core_number(cpu) + UV_MAX_INT_CORES * uv_cpu_socket_number(cpu);
	अगर (core >= GRU_NUM_TFM || uv_cpu_ht_number(cpu))
		वापस 0;

	अगर (chiplet == 0) अणु
		mmr = UVH_GR0_TLB_INT0_CONFIG +
		    core * (UVH_GR0_TLB_INT1_CONFIG - UVH_GR0_TLB_INT0_CONFIG);
	पूर्ण अन्यथा अगर (chiplet == 1) अणु
		mmr = UVH_GR1_TLB_INT0_CONFIG +
		    core * (UVH_GR1_TLB_INT1_CONFIG - UVH_GR1_TLB_INT0_CONFIG);
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण

	*corep = core;
	वापस mmr;
पूर्ण

#अगर_घोषित CONFIG_IA64

अटल पूर्णांक gru_irq_count[GRU_CHIPLETS_PER_BLADE];

अटल व्योम gru_noop(काष्ठा irq_data *d)
अणु
पूर्ण

अटल काष्ठा irq_chip gru_chip[GRU_CHIPLETS_PER_BLADE] = अणु
	[0 ... GRU_CHIPLETS_PER_BLADE - 1] अणु
		.irq_mask	= gru_noop,
		.irq_unmask	= gru_noop,
		.irq_ack	= gru_noop
	पूर्ण
पूर्ण;

अटल पूर्णांक gru_chiplet_setup_tlb_irq(पूर्णांक chiplet, अक्षर *irq_name,
			irq_handler_t irq_handler, पूर्णांक cpu, पूर्णांक blade)
अणु
	अचिन्हित दीर्घ mmr;
	पूर्णांक irq = IRQ_GRU + chiplet;
	पूर्णांक ret, core;

	mmr = gru_chiplet_cpu_to_mmr(chiplet, cpu, &core);
	अगर (mmr == 0)
		वापस 0;

	अगर (gru_irq_count[chiplet] == 0) अणु
		gru_chip[chiplet].name = irq_name;
		ret = irq_set_chip(irq, &gru_chip[chiplet]);
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR "%s: set_irq_chip failed, errno=%d\n",
			       GRU_DRIVER_ID_STR, -ret);
			वापस ret;
		पूर्ण

		ret = request_irq(irq, irq_handler, 0, irq_name, शून्य);
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR "%s: request_irq failed, errno=%d\n",
			       GRU_DRIVER_ID_STR, -ret);
			वापस ret;
		पूर्ण
	पूर्ण
	gru_irq_count[chiplet]++;

	वापस 0;
पूर्ण

अटल व्योम gru_chiplet_tearकरोwn_tlb_irq(पूर्णांक chiplet, पूर्णांक cpu, पूर्णांक blade)
अणु
	अचिन्हित दीर्घ mmr;
	पूर्णांक core, irq = IRQ_GRU + chiplet;

	अगर (gru_irq_count[chiplet] == 0)
		वापस;

	mmr = gru_chiplet_cpu_to_mmr(chiplet, cpu, &core);
	अगर (mmr == 0)
		वापस;

	अगर (--gru_irq_count[chiplet] == 0)
		मुक्त_irq(irq, शून्य);
पूर्ण

#या_अगर defined CONFIG_X86_64

अटल पूर्णांक gru_chiplet_setup_tlb_irq(पूर्णांक chiplet, अक्षर *irq_name,
			irq_handler_t irq_handler, पूर्णांक cpu, पूर्णांक blade)
अणु
	अचिन्हित दीर्घ mmr;
	पूर्णांक irq, core;
	पूर्णांक ret;

	mmr = gru_chiplet_cpu_to_mmr(chiplet, cpu, &core);
	अगर (mmr == 0)
		वापस 0;

	irq = uv_setup_irq(irq_name, cpu, blade, mmr, UV_AFFINITY_CPU);
	अगर (irq < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: uv_setup_irq failed, errno=%d\n",
		       GRU_DRIVER_ID_STR, -irq);
		वापस irq;
	पूर्ण

	ret = request_irq(irq, irq_handler, 0, irq_name, शून्य);
	अगर (ret) अणु
		uv_tearकरोwn_irq(irq);
		prपूर्णांकk(KERN_ERR "%s: request_irq failed, errno=%d\n",
		       GRU_DRIVER_ID_STR, -ret);
		वापस ret;
	पूर्ण
	gru_base[blade]->bs_grus[chiplet].gs_irq[core] = irq;
	वापस 0;
पूर्ण

अटल व्योम gru_chiplet_tearकरोwn_tlb_irq(पूर्णांक chiplet, पूर्णांक cpu, पूर्णांक blade)
अणु
	पूर्णांक irq, core;
	अचिन्हित दीर्घ mmr;

	mmr = gru_chiplet_cpu_to_mmr(chiplet, cpu, &core);
	अगर (mmr) अणु
		irq = gru_base[blade]->bs_grus[chiplet].gs_irq[core];
		अगर (irq) अणु
			मुक्त_irq(irq, शून्य);
			uv_tearकरोwn_irq(irq);
		पूर्ण
	पूर्ण
पूर्ण

#पूर्ण_अगर

अटल व्योम gru_tearकरोwn_tlb_irqs(व्योम)
अणु
	पूर्णांक blade;
	पूर्णांक cpu;

	क्रम_each_online_cpu(cpu) अणु
		blade = uv_cpu_to_blade_id(cpu);
		gru_chiplet_tearकरोwn_tlb_irq(0, cpu, blade);
		gru_chiplet_tearकरोwn_tlb_irq(1, cpu, blade);
	पूर्ण
	क्रम_each_possible_blade(blade) अणु
		अगर (uv_blade_nr_possible_cpus(blade))
			जारी;
		gru_chiplet_tearकरोwn_tlb_irq(0, 0, blade);
		gru_chiplet_tearकरोwn_tlb_irq(1, 0, blade);
	पूर्ण
पूर्ण

अटल पूर्णांक gru_setup_tlb_irqs(व्योम)
अणु
	पूर्णांक blade;
	पूर्णांक cpu;
	पूर्णांक ret;

	क्रम_each_online_cpu(cpu) अणु
		blade = uv_cpu_to_blade_id(cpu);
		ret = gru_chiplet_setup_tlb_irq(0, "GRU0_TLB", gru0_पूर्णांकr, cpu, blade);
		अगर (ret != 0)
			जाओ निकास1;

		ret = gru_chiplet_setup_tlb_irq(1, "GRU1_TLB", gru1_पूर्णांकr, cpu, blade);
		अगर (ret != 0)
			जाओ निकास1;
	पूर्ण
	क्रम_each_possible_blade(blade) अणु
		अगर (uv_blade_nr_possible_cpus(blade))
			जारी;
		ret = gru_chiplet_setup_tlb_irq(0, "GRU0_TLB", gru_पूर्णांकr_mblade, 0, blade);
		अगर (ret != 0)
			जाओ निकास1;

		ret = gru_chiplet_setup_tlb_irq(1, "GRU1_TLB", gru_पूर्णांकr_mblade, 0, blade);
		अगर (ret != 0)
			जाओ निकास1;
	पूर्ण

	वापस 0;

निकास1:
	gru_tearकरोwn_tlb_irqs();
	वापस ret;
पूर्ण

/*
 * gru_init
 *
 * Called at boot or module load समय to initialize the GRUs.
 */
अटल पूर्णांक __init gru_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!gru_supported())
		वापस 0;

#अगर defined CONFIG_IA64
	gru_start_paddr = 0xd000000000UL; /* ZZZZZZZZZZZZZZZZZZZ fixme */
#अन्यथा
	gru_start_paddr = uv_पढ़ो_local_mmr(UVH_RH_GAM_GRU_OVERLAY_CONFIG) &
				0x7fffffffffffUL;
#पूर्ण_अगर
	gru_start_vaddr = __va(gru_start_paddr);
	gru_end_paddr = gru_start_paddr + GRU_MAX_BLADES * GRU_SIZE;
	prपूर्णांकk(KERN_INFO "GRU space: 0x%lx - 0x%lx\n",
	       gru_start_paddr, gru_end_paddr);
	ret = misc_रेजिस्टर(&gru_miscdev);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "%s: misc_register failed\n",
		       GRU_DRIVER_ID_STR);
		जाओ निकास0;
	पूर्ण

	ret = gru_proc_init();
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "%s: proc init failed\n", GRU_DRIVER_ID_STR);
		जाओ निकास1;
	पूर्ण

	ret = gru_init_tables(gru_start_paddr, gru_start_vaddr);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "%s: init tables failed\n", GRU_DRIVER_ID_STR);
		जाओ निकास2;
	पूर्ण

	ret = gru_setup_tlb_irqs();
	अगर (ret != 0)
		जाओ निकास3;

	gru_kservices_init();

	prपूर्णांकk(KERN_INFO "%s: v%s\n", GRU_DRIVER_ID_STR,
	       GRU_DRIVER_VERSION_STR);
	वापस 0;

निकास3:
	gru_मुक्त_tables();
निकास2:
	gru_proc_निकास();
निकास1:
	misc_deरेजिस्टर(&gru_miscdev);
निकास0:
	वापस ret;

पूर्ण

अटल व्योम __निकास gru_निकास(व्योम)
अणु
	अगर (!gru_supported())
		वापस;

	gru_tearकरोwn_tlb_irqs();
	gru_kservices_निकास();
	gru_मुक्त_tables();
	misc_deरेजिस्टर(&gru_miscdev);
	gru_proc_निकास();
	mmu_notअगरier_synchronize();
पूर्ण

अटल स्थिर काष्ठा file_operations gru_fops = अणु
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= gru_file_unlocked_ioctl,
	.mmap		= gru_file_mmap,
	.llseek		= noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice gru_miscdev = अणु
	.minor		= MISC_DYNAMIC_MINOR,
	.name		= "gru",
	.fops		= &gru_fops,
पूर्ण;

स्थिर काष्ठा vm_operations_काष्ठा gru_vm_ops = अणु
	.बंद		= gru_vma_बंद,
	.fault		= gru_fault,
पूर्ण;

#अगर_अघोषित MODULE
fs_initcall(gru_init);
#अन्यथा
module_init(gru_init);
#पूर्ण_अगर
module_निकास(gru_निकास);

module_param(gru_options, uदीर्घ, 0644);
MODULE_PARM_DESC(gru_options, "Various debug options");

MODULE_AUTHOR("Silicon Graphics, Inc.");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(GRU_DRIVER_ID_STR GRU_DRIVER_VERSION_STR);
MODULE_VERSION(GRU_DRIVER_VERSION_STR);

