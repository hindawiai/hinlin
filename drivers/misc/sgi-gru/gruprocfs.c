<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SN Platक्रमm GRU Driver
 *
 *              PROC INTERFACES
 *
 * This file supports the /proc पूर्णांकerfaces क्रम the GRU driver
 *
 *  Copyright (c) 2008 Silicon Graphics, Inc.  All Rights Reserved.
 */

#समावेश <linux/proc_fs.h>
#समावेश <linux/device.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/uaccess.h>
#समावेश "gru.h"
#समावेश "grulib.h"
#समावेश "grutables.h"

#घोषणा prपूर्णांकstat(s, f)		prपूर्णांकstat_val(s, &gru_stats.f, #f)

अटल व्योम prपूर्णांकstat_val(काष्ठा seq_file *s, atomic_दीर्घ_t *v, अक्षर *id)
अणु
	अचिन्हित दीर्घ val = atomic_दीर्घ_पढ़ो(v);

	seq_म_लिखो(s, "%16lu %s\n", val, id);
पूर्ण

अटल पूर्णांक statistics_show(काष्ठा seq_file *s, व्योम *p)
अणु
	prपूर्णांकstat(s, vdata_alloc);
	prपूर्णांकstat(s, vdata_मुक्त);
	prपूर्णांकstat(s, gts_alloc);
	prपूर्णांकstat(s, gts_मुक्त);
	prपूर्णांकstat(s, gms_alloc);
	prपूर्णांकstat(s, gms_मुक्त);
	prपूर्णांकstat(s, gts_द्विगुन_allocate);
	prपूर्णांकstat(s, assign_context);
	prपूर्णांकstat(s, assign_context_failed);
	prपूर्णांकstat(s, मुक्त_context);
	prपूर्णांकstat(s, load_user_context);
	prपूर्णांकstat(s, load_kernel_context);
	prपूर्णांकstat(s, lock_kernel_context);
	prपूर्णांकstat(s, unlock_kernel_context);
	prपूर्णांकstat(s, steal_user_context);
	prपूर्णांकstat(s, steal_kernel_context);
	prपूर्णांकstat(s, steal_context_failed);
	prपूर्णांकstat(s, nopfn);
	prपूर्णांकstat(s, asid_new);
	prपूर्णांकstat(s, asid_next);
	prपूर्णांकstat(s, asid_wrap);
	prपूर्णांकstat(s, asid_reuse);
	prपूर्णांकstat(s, पूर्णांकr);
	prपूर्णांकstat(s, पूर्णांकr_cbr);
	prपूर्णांकstat(s, पूर्णांकr_tfh);
	prपूर्णांकstat(s, पूर्णांकr_spurious);
	prपूर्णांकstat(s, पूर्णांकr_mm_lock_failed);
	prपूर्णांकstat(s, call_os);
	prपूर्णांकstat(s, call_os_रुको_queue);
	prपूर्णांकstat(s, user_flush_tlb);
	prपूर्णांकstat(s, user_unload_context);
	prपूर्णांकstat(s, user_exception);
	prपूर्णांकstat(s, set_context_option);
	prपूर्णांकstat(s, check_context_retarget_पूर्णांकr);
	prपूर्णांकstat(s, check_context_unload);
	prपूर्णांकstat(s, tlb_dropin);
	prपूर्णांकstat(s, tlb_preload_page);
	prपूर्णांकstat(s, tlb_dropin_fail_no_asid);
	prपूर्णांकstat(s, tlb_dropin_fail_upm);
	prपूर्णांकstat(s, tlb_dropin_fail_invalid);
	prपूर्णांकstat(s, tlb_dropin_fail_range_active);
	prपूर्णांकstat(s, tlb_dropin_fail_idle);
	prपूर्णांकstat(s, tlb_dropin_fail_fmm);
	prपूर्णांकstat(s, tlb_dropin_fail_no_exception);
	prपूर्णांकstat(s, tfh_stale_on_fault);
	prपूर्णांकstat(s, mmu_invalidate_range);
	prपूर्णांकstat(s, mmu_invalidate_page);
	prपूर्णांकstat(s, flush_tlb);
	prपूर्णांकstat(s, flush_tlb_gru);
	prपूर्णांकstat(s, flush_tlb_gru_tgh);
	prपूर्णांकstat(s, flush_tlb_gru_zero_asid);
	prपूर्णांकstat(s, copy_gpa);
	prपूर्णांकstat(s, पढ़ो_gpa);
	prपूर्णांकstat(s, mesq_receive);
	prपूर्णांकstat(s, mesq_receive_none);
	prपूर्णांकstat(s, mesq_send);
	prपूर्णांकstat(s, mesq_send_failed);
	prपूर्णांकstat(s, mesq_noop);
	prपूर्णांकstat(s, mesq_send_unexpected_error);
	prपूर्णांकstat(s, mesq_send_lb_overflow);
	prपूर्णांकstat(s, mesq_send_qlimit_reached);
	prपूर्णांकstat(s, mesq_send_amo_nacked);
	prपूर्णांकstat(s, mesq_send_put_nacked);
	prपूर्णांकstat(s, mesq_qf_locked);
	prपूर्णांकstat(s, mesq_qf_noop_not_full);
	prपूर्णांकstat(s, mesq_qf_चयन_head_failed);
	prपूर्णांकstat(s, mesq_qf_unexpected_error);
	prपूर्णांकstat(s, mesq_noop_unexpected_error);
	prपूर्णांकstat(s, mesq_noop_lb_overflow);
	prपूर्णांकstat(s, mesq_noop_qlimit_reached);
	prपूर्णांकstat(s, mesq_noop_amo_nacked);
	prपूर्णांकstat(s, mesq_noop_put_nacked);
	prपूर्णांकstat(s, mesq_noop_page_overflow);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार statistics_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *userbuf,
				माप_प्रकार count, loff_t *data)
अणु
	स_रखो(&gru_stats, 0, माप(gru_stats));
	वापस count;
पूर्ण

अटल पूर्णांक mcs_statistics_show(काष्ठा seq_file *s, व्योम *p)
अणु
	पूर्णांक op;
	अचिन्हित दीर्घ total, count, max;
	अटल अक्षर *id[] = अणु"cch_allocate", "cch_start", "cch_interrupt",
		"cch_interrupt_sync", "cch_deallocate", "tfh_write_only",
		"tfh_write_restart", "tgh_invalidate"पूर्ण;

	seq_माला_दो(s, "#id                        count   aver-clks    max-clks\n");
	क्रम (op = 0; op < mcsop_last; op++) अणु
		count = atomic_दीर्घ_पढ़ो(&mcs_op_statistics[op].count);
		total = atomic_दीर्घ_पढ़ो(&mcs_op_statistics[op].total);
		max = mcs_op_statistics[op].max;
		seq_म_लिखो(s, "%-20s%12ld%12ld%12ld\n", id[op], count,
			   count ? total / count : 0, max);
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार mcs_statistics_ग_लिखो(काष्ठा file *file,
			स्थिर अक्षर __user *userbuf, माप_प्रकार count, loff_t *data)
अणु
	स_रखो(mcs_op_statistics, 0, माप(mcs_op_statistics));
	वापस count;
पूर्ण

अटल पूर्णांक options_show(काष्ठा seq_file *s, व्योम *p)
अणु
	seq_म_लिखो(s, "#bitmask: 1=trace, 2=statistics\n");
	seq_म_लिखो(s, "0x%lx\n", gru_options);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार options_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *userbuf,
			     माप_प्रकार count, loff_t *data)
अणु
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(userbuf, count, 0, &gru_options);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल पूर्णांक cch_seq_show(काष्ठा seq_file *file, व्योम *data)
अणु
	दीर्घ gid = *(दीर्घ *)data;
	पूर्णांक i;
	काष्ठा gru_state *gru = GID_TO_GRU(gid);
	काष्ठा gru_thपढ़ो_state *ts;
	स्थिर अक्षर *mode[] = अणु "??", "UPM", "INTR", "OS_POLL" पूर्ण;

	अगर (gid == 0)
		seq_माला_दो(file, "#  gid  bid  ctx#   asid      pid  cbrs dsbytes    mode\n");
	अगर (gru)
		क्रम (i = 0; i < GRU_NUM_CCH; i++) अणु
			ts = gru->gs_gts[i];
			अगर (!ts)
				जारी;
			seq_म_लिखो(file, " %5d%5d%6d%7d%9d%6d%8d%8s\n",
				   gru->gs_gid, gru->gs_blade_id, i,
				   is_kernel_context(ts) ? 0 : ts->ts_gms->ms_asids[gid].mt_asid,
				   is_kernel_context(ts) ? 0 : ts->ts_tgid_owner,
				   ts->ts_cbr_au_count * GRU_CBR_AU_SIZE,
				   ts->ts_cbr_au_count * GRU_DSR_AU_BYTES,
				   mode[ts->ts_user_options &
					GRU_OPT_MISS_MASK]);
		पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gru_seq_show(काष्ठा seq_file *file, व्योम *data)
अणु
	दीर्घ gid = *(दीर्घ *)data, ctxमुक्त, cbrमुक्त, dsrमुक्त;
	काष्ठा gru_state *gru = GID_TO_GRU(gid);

	अगर (gid == 0) अणु
		seq_माला_दो(file, "#  gid  nid    ctx   cbr   dsr     ctx   cbr   dsr\n");
		seq_माला_दो(file, "#             busy  busy  busy    free  free  free\n");
	पूर्ण
	अगर (gru) अणु
		ctxमुक्त = GRU_NUM_CCH - gru->gs_active_contexts;
		cbrमुक्त = hweight64(gru->gs_cbr_map) * GRU_CBR_AU_SIZE;
		dsrमुक्त = hweight64(gru->gs_dsr_map) * GRU_DSR_AU_BYTES;
		seq_म_लिखो(file, " %5d%5d%7ld%6ld%6ld%8ld%6ld%6ld\n",
			   gru->gs_gid, gru->gs_blade_id, GRU_NUM_CCH - ctxमुक्त,
			   GRU_NUM_CBE - cbrमुक्त, GRU_NUM_DSR_BYTES - dsrमुक्त,
			   ctxमुक्त, cbrमुक्त, dsrमुक्त);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम seq_stop(काष्ठा seq_file *file, व्योम *data)
अणु
पूर्ण

अटल व्योम *seq_start(काष्ठा seq_file *file, loff_t *gid)
अणु
	अगर (*gid < gru_max_gids)
		वापस gid;
	वापस शून्य;
पूर्ण

अटल व्योम *seq_next(काष्ठा seq_file *file, व्योम *data, loff_t *gid)
अणु
	(*gid)++;
	अगर (*gid < gru_max_gids)
		वापस gid;
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा seq_operations cch_seq_ops = अणु
	.start	= seq_start,
	.next	= seq_next,
	.stop	= seq_stop,
	.show	= cch_seq_show
पूर्ण;

अटल स्थिर काष्ठा seq_operations gru_seq_ops = अणु
	.start	= seq_start,
	.next	= seq_next,
	.stop	= seq_stop,
	.show	= gru_seq_show
पूर्ण;

अटल पूर्णांक statistics_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, statistics_show, शून्य);
पूर्ण

अटल पूर्णांक mcs_statistics_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, mcs_statistics_show, शून्य);
पूर्ण

अटल पूर्णांक options_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, options_show, शून्य);
पूर्ण

/* *INDENT-OFF* */
अटल स्थिर काष्ठा proc_ops statistics_proc_ops = अणु
	.proc_खोलो	= statistics_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_ग_लिखो	= statistics_ग_लिखो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
पूर्ण;

अटल स्थिर काष्ठा proc_ops mcs_statistics_proc_ops = अणु
	.proc_खोलो	= mcs_statistics_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_ग_लिखो	= mcs_statistics_ग_लिखो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
पूर्ण;

अटल स्थिर काष्ठा proc_ops options_proc_ops = अणु
	.proc_खोलो	= options_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_ग_लिखो	= options_ग_लिखो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
पूर्ण;

अटल काष्ठा proc_dir_entry *proc_gru __पढ़ो_mostly;

पूर्णांक gru_proc_init(व्योम)
अणु
	proc_gru = proc_सूची_गढ़ो("sgi_uv/gru", शून्य);
	अगर (!proc_gru)
		वापस -1;
	अगर (!proc_create("statistics", 0644, proc_gru, &statistics_proc_ops))
		जाओ err;
	अगर (!proc_create("mcs_statistics", 0644, proc_gru, &mcs_statistics_proc_ops))
		जाओ err;
	अगर (!proc_create("debug_options", 0644, proc_gru, &options_proc_ops))
		जाओ err;
	अगर (!proc_create_seq("cch_status", 0444, proc_gru, &cch_seq_ops))
		जाओ err;
	अगर (!proc_create_seq("gru_status", 0444, proc_gru, &gru_seq_ops))
		जाओ err;
	वापस 0;
err:
	हटाओ_proc_subtree("sgi_uv/gru", शून्य);
	वापस -1;
पूर्ण

व्योम gru_proc_निकास(व्योम)
अणु
	हटाओ_proc_subtree("sgi_uv/gru", शून्य);
पूर्ण
