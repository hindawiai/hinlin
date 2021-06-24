<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IBM Accelerator Family 'GenWQE'
 *
 * (C) Copyright IBM Corp. 2013
 *
 * Author: Frank Haverkamp <haver@linux.vnet.ibm.com>
 * Author: Joerg-Stephan Vogt <jsvogt@de.ibm.com>
 * Author: Michael Jung <mijung@gmx.net>
 * Author: Michael Ruettger <michael@ibmra.de>
 */

/*
 * Debugfs पूर्णांकerfaces क्रम the GenWQE card. Help to debug potential
 * problems. Dump पूर्णांकernal chip state क्रम debugging and failure
 * determination.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/uaccess.h>

#समावेश "card_base.h"
#समावेश "card_ddcb.h"

अटल व्योम dbg_uidn_show(काष्ठा seq_file *s, काष्ठा genwqe_reg *regs,
			  पूर्णांक entries)
अणु
	अचिन्हित पूर्णांक i;
	u32 v_hi, v_lo;

	क्रम (i = 0; i < entries; i++) अणु
		v_hi = (regs[i].val >> 32) & 0xffffffff;
		v_lo = (regs[i].val)       & 0xffffffff;

		seq_म_लिखो(s, "  0x%08x 0x%08x 0x%08x 0x%08x EXT_ERR_REC\n",
			   regs[i].addr, regs[i].idx, v_hi, v_lo);
	पूर्ण
पूर्ण

अटल पूर्णांक curr_dbg_uidn_show(काष्ठा seq_file *s, व्योम *unused, पूर्णांक uid)
अणु
	काष्ठा genwqe_dev *cd = s->निजी;
	पूर्णांक entries;
	काष्ठा genwqe_reg *regs;

	entries = genwqe_ffdc_buff_size(cd, uid);
	अगर (entries < 0)
		वापस -EINVAL;

	अगर (entries == 0)
		वापस 0;

	regs = kसुस्मृति(entries, माप(*regs), GFP_KERNEL);
	अगर (regs == शून्य)
		वापस -ENOMEM;

	genwqe_stop_traps(cd); /* halt the traps जबतक dumping data */
	genwqe_ffdc_buff_पढ़ो(cd, uid, regs, entries);
	genwqe_start_traps(cd);

	dbg_uidn_show(s, regs, entries);
	kमुक्त(regs);
	वापस 0;
पूर्ण

अटल पूर्णांक curr_dbg_uid0_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	वापस curr_dbg_uidn_show(s, unused, 0);
पूर्ण

DEFINE_SHOW_ATTRIBUTE(curr_dbg_uid0);

अटल पूर्णांक curr_dbg_uid1_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	वापस curr_dbg_uidn_show(s, unused, 1);
पूर्ण

DEFINE_SHOW_ATTRIBUTE(curr_dbg_uid1);

अटल पूर्णांक curr_dbg_uid2_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	वापस curr_dbg_uidn_show(s, unused, 2);
पूर्ण

DEFINE_SHOW_ATTRIBUTE(curr_dbg_uid2);

अटल पूर्णांक prev_dbg_uidn_show(काष्ठा seq_file *s, व्योम *unused, पूर्णांक uid)
अणु
	काष्ठा genwqe_dev *cd = s->निजी;

	dbg_uidn_show(s, cd->ffdc[uid].regs,  cd->ffdc[uid].entries);
	वापस 0;
पूर्ण

अटल पूर्णांक prev_dbg_uid0_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	वापस prev_dbg_uidn_show(s, unused, 0);
पूर्ण

DEFINE_SHOW_ATTRIBUTE(prev_dbg_uid0);

अटल पूर्णांक prev_dbg_uid1_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	वापस prev_dbg_uidn_show(s, unused, 1);
पूर्ण

DEFINE_SHOW_ATTRIBUTE(prev_dbg_uid1);

अटल पूर्णांक prev_dbg_uid2_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	वापस prev_dbg_uidn_show(s, unused, 2);
पूर्ण

DEFINE_SHOW_ATTRIBUTE(prev_dbg_uid2);

अटल पूर्णांक curr_regs_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा genwqe_dev *cd = s->निजी;
	अचिन्हित पूर्णांक i;
	काष्ठा genwqe_reg *regs;

	regs = kसुस्मृति(GENWQE_FFDC_REGS, माप(*regs), GFP_KERNEL);
	अगर (regs == शून्य)
		वापस -ENOMEM;

	genwqe_stop_traps(cd);
	genwqe_पढ़ो_ffdc_regs(cd, regs, GENWQE_FFDC_REGS, 1);
	genwqe_start_traps(cd);

	क्रम (i = 0; i < GENWQE_FFDC_REGS; i++) अणु
		अगर (regs[i].addr == 0xffffffff)
			अवरोध;  /* invalid entries */

		अगर (regs[i].val == 0x0ull)
			जारी;  /* करो not prपूर्णांक 0x0 FIRs */

		seq_म_लिखो(s, "  0x%08x 0x%016llx\n",
			   regs[i].addr, regs[i].val);
	पूर्ण
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(curr_regs);

अटल पूर्णांक prev_regs_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा genwqe_dev *cd = s->निजी;
	अचिन्हित पूर्णांक i;
	काष्ठा genwqe_reg *regs = cd->ffdc[GENWQE_DBG_REGS].regs;

	अगर (regs == शून्य)
		वापस -EINVAL;

	क्रम (i = 0; i < GENWQE_FFDC_REGS; i++) अणु
		अगर (regs[i].addr == 0xffffffff)
			अवरोध;  /* invalid entries */

		अगर (regs[i].val == 0x0ull)
			जारी;  /* करो not prपूर्णांक 0x0 FIRs */

		seq_म_लिखो(s, "  0x%08x 0x%016llx\n",
			   regs[i].addr, regs[i].val);
	पूर्ण
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(prev_regs);

अटल पूर्णांक jसमयr_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा genwqe_dev *cd = s->निजी;
	अचिन्हित पूर्णांक vf_num;
	u64 jसमयr;

	jसमयr = genwqe_पढ़ो_vreg(cd, IO_SLC_VF_APPJOB_TIMEOUT, 0);
	seq_म_लिखो(s, "  PF   0x%016llx %d msec\n", jसमयr,
		   GENWQE_PF_JOBTIMEOUT_MSEC);

	क्रम (vf_num = 0; vf_num < cd->num_vfs; vf_num++) अणु
		jसमयr = genwqe_पढ़ो_vreg(cd, IO_SLC_VF_APPJOB_TIMEOUT,
					  vf_num + 1);
		seq_म_लिखो(s, "  VF%-2d 0x%016llx %d msec\n", vf_num, jसमयr,
			   cd->vf_jobसमयout_msec[vf_num]);
	पूर्ण
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(jसमयr);

अटल पूर्णांक queue_working_समय_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा genwqe_dev *cd = s->निजी;
	अचिन्हित पूर्णांक vf_num;
	u64 t;

	t = genwqe_पढ़ो_vreg(cd, IO_SLC_VF_QUEUE_WTIME, 0);
	seq_म_लिखो(s, "  PF   0x%016llx\n", t);

	क्रम (vf_num = 0; vf_num < cd->num_vfs; vf_num++) अणु
		t = genwqe_पढ़ो_vreg(cd, IO_SLC_VF_QUEUE_WTIME, vf_num + 1);
		seq_म_लिखो(s, "  VF%-2d 0x%016llx\n", vf_num, t);
	पूर्ण
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(queue_working_समय);

अटल पूर्णांक ddcb_info_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा genwqe_dev *cd = s->निजी;
	अचिन्हित पूर्णांक i;
	काष्ठा ddcb_queue *queue;
	काष्ठा ddcb *pddcb;

	queue = &cd->queue;
	seq_माला_दो(s, "DDCB QUEUE:\n");
	seq_म_लिखो(s, "  ddcb_max:            %d\n"
		   "  ddcb_daddr:          %016llx - %016llx\n"
		   "  ddcb_vaddr:          %p\n"
		   "  ddcbs_in_flight:     %u\n"
		   "  ddcbs_max_in_flight: %u\n"
		   "  ddcbs_completed:     %u\n"
		   "  return_on_busy:      %u\n"
		   "  wait_on_busy:        %u\n"
		   "  irqs_processed:      %u\n",
		   queue->ddcb_max, (दीर्घ दीर्घ)queue->ddcb_daddr,
		   (दीर्घ दीर्घ)queue->ddcb_daddr +
		   (queue->ddcb_max * DDCB_LENGTH),
		   queue->ddcb_vaddr, queue->ddcbs_in_flight,
		   queue->ddcbs_max_in_flight, queue->ddcbs_completed,
		   queue->वापस_on_busy, queue->रुको_on_busy,
		   cd->irqs_processed);

	/* Hardware State */
	seq_म_लिखो(s, "  0x%08x 0x%016llx IO_QUEUE_CONFIG\n"
		   "  0x%08x 0x%016llx IO_QUEUE_STATUS\n"
		   "  0x%08x 0x%016llx IO_QUEUE_SEGMENT\n"
		   "  0x%08x 0x%016llx IO_QUEUE_INITSQN\n"
		   "  0x%08x 0x%016llx IO_QUEUE_WRAP\n"
		   "  0x%08x 0x%016llx IO_QUEUE_OFFSET\n"
		   "  0x%08x 0x%016llx IO_QUEUE_WTIME\n"
		   "  0x%08x 0x%016llx IO_QUEUE_ERRCNTS\n"
		   "  0x%08x 0x%016llx IO_QUEUE_LRW\n",
		   queue->IO_QUEUE_CONFIG,
		   __genwqe_पढ़ोq(cd, queue->IO_QUEUE_CONFIG),
		   queue->IO_QUEUE_STATUS,
		   __genwqe_पढ़ोq(cd, queue->IO_QUEUE_STATUS),
		   queue->IO_QUEUE_SEGMENT,
		   __genwqe_पढ़ोq(cd, queue->IO_QUEUE_SEGMENT),
		   queue->IO_QUEUE_INITSQN,
		   __genwqe_पढ़ोq(cd, queue->IO_QUEUE_INITSQN),
		   queue->IO_QUEUE_WRAP,
		   __genwqe_पढ़ोq(cd, queue->IO_QUEUE_WRAP),
		   queue->IO_QUEUE_OFFSET,
		   __genwqe_पढ़ोq(cd, queue->IO_QUEUE_OFFSET),
		   queue->IO_QUEUE_WTIME,
		   __genwqe_पढ़ोq(cd, queue->IO_QUEUE_WTIME),
		   queue->IO_QUEUE_ERRCNTS,
		   __genwqe_पढ़ोq(cd, queue->IO_QUEUE_ERRCNTS),
		   queue->IO_QUEUE_LRW,
		   __genwqe_पढ़ोq(cd, queue->IO_QUEUE_LRW));

	seq_म_लिखो(s, "DDCB list (ddcb_act=%d/ddcb_next=%d):\n",
		   queue->ddcb_act, queue->ddcb_next);

	pddcb = queue->ddcb_vaddr;
	क्रम (i = 0; i < queue->ddcb_max; i++) अणु
		seq_म_लिखो(s, "  %-3d: RETC=%03x SEQ=%04x HSI/SHI=%02x/%02x ",
			   i, be16_to_cpu(pddcb->retc_16),
			   be16_to_cpu(pddcb->seqnum_16),
			   pddcb->hsi, pddcb->shi);
		seq_म_लिखो(s, "PRIV=%06llx CMD=%02x\n",
			   be64_to_cpu(pddcb->priv_64), pddcb->cmd);
		pddcb++;
	पूर्ण
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(ddcb_info);

अटल पूर्णांक info_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा genwqe_dev *cd = s->निजी;
	u64 app_id, slu_id, bitstream = -1;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	slu_id = __genwqe_पढ़ोq(cd, IO_SLU_UNITCFG);
	app_id = __genwqe_पढ़ोq(cd, IO_APP_UNITCFG);

	अगर (genwqe_is_privileged(cd))
		bitstream = __genwqe_पढ़ोq(cd, IO_SLU_BITSTREAM);

	seq_म_लिखो(s, "%s driver version: %s\n"
		   "    Device Name/Type: %s %s CardIdx: %d\n"
		   "    SLU/APP Config  : 0x%016llx/0x%016llx\n"
		   "    Build Date      : %u/%x/%u\n"
		   "    Base Clock      : %u MHz\n"
		   "    Arch/SVN Release: %u/%llx\n"
		   "    Bitstream       : %llx\n",
		   GENWQE_DEVNAME, DRV_VERSION, dev_name(&pci_dev->dev),
		   genwqe_is_privileged(cd) ?
		   "Physical" : "Virtual or no SR-IOV",
		   cd->card_idx, slu_id, app_id,
		   (u16)((slu_id >> 12) & 0x0fLLU),	   /* month */
		   (u16)((slu_id >>  4) & 0xffLLU),	   /* day */
		   (u16)((slu_id >> 16) & 0x0fLLU) + 2010, /* year */
		   genwqe_base_घड़ी_frequency(cd),
		   (u16)((slu_id >> 32) & 0xffLLU), slu_id >> 40,
		   bitstream);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(info);

व्योम genwqe_init_debugfs(काष्ठा genwqe_dev *cd)
अणु
	काष्ठा dentry *root;
	अक्षर card_name[64];
	अक्षर name[64];
	अचिन्हित पूर्णांक i;

	प्र_लिखो(card_name, "%s%d_card", GENWQE_DEVNAME, cd->card_idx);

	root = debugfs_create_dir(card_name, cd->debugfs_genwqe);

	/* non privileged पूर्णांकerfaces are करोne here */
	debugfs_create_file("ddcb_info", S_IRUGO, root, cd, &ddcb_info_fops);
	debugfs_create_file("info", S_IRUGO, root, cd, &info_fops);
	debugfs_create_x64("err_inject", 0666, root, &cd->err_inject);
	debugfs_create_u32("ddcb_software_timeout", 0666, root,
			   &cd->ddcb_software_समयout);
	debugfs_create_u32("kill_timeout", 0666, root, &cd->समाप्त_समयout);

	/* privileged पूर्णांकerfaces follow here */
	अगर (!genwqe_is_privileged(cd)) अणु
		cd->debugfs_root = root;
		वापस;
	पूर्ण

	debugfs_create_file("curr_regs", S_IRUGO, root, cd, &curr_regs_fops);
	debugfs_create_file("curr_dbg_uid0", S_IRUGO, root, cd,
			    &curr_dbg_uid0_fops);
	debugfs_create_file("curr_dbg_uid1", S_IRUGO, root, cd,
			    &curr_dbg_uid1_fops);
	debugfs_create_file("curr_dbg_uid2", S_IRUGO, root, cd,
			    &curr_dbg_uid2_fops);
	debugfs_create_file("prev_regs", S_IRUGO, root, cd, &prev_regs_fops);
	debugfs_create_file("prev_dbg_uid0", S_IRUGO, root, cd,
			    &prev_dbg_uid0_fops);
	debugfs_create_file("prev_dbg_uid1", S_IRUGO, root, cd,
			    &prev_dbg_uid1_fops);
	debugfs_create_file("prev_dbg_uid2", S_IRUGO, root, cd,
			    &prev_dbg_uid2_fops);

	क्रम (i = 0; i <  GENWQE_MAX_VFS; i++) अणु
		प्र_लिखो(name, "vf%u_jobtimeout_msec", i);
		debugfs_create_u32(name, 0666, root,
				   &cd->vf_jobसमयout_msec[i]);
	पूर्ण

	debugfs_create_file("jobtimer", S_IRUGO, root, cd, &jसमयr_fops);
	debugfs_create_file("queue_working_time", S_IRUGO, root, cd,
			    &queue_working_समय_fops);
	debugfs_create_u32("skip_recovery", 0666, root, &cd->skip_recovery);
	debugfs_create_u32("use_platform_recovery", 0666, root,
			   &cd->use_platक्रमm_recovery);

	cd->debugfs_root = root;
पूर्ण

व्योम genqwe_निकास_debugfs(काष्ठा genwqe_dev *cd)
अणु
	debugfs_हटाओ_recursive(cd->debugfs_root);
पूर्ण
