<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Resource Director Technology(RDT)
 * - Monitoring code
 *
 * Copyright (C) 2017 Intel Corporation
 *
 * Author:
 *    Vikas Shivappa <vikas.shivappa@पूर्णांकel.com>
 *
 * This replaces the cqm.c based on perf but we reuse a lot of
 * code and dataकाष्ठाures originally from Peter Zijlstra and Matt Fleming.
 *
 * More inक्रमmation about RDT be found in the Intel (R) x86 Architecture
 * Software Developer Manual June 2016, volume 3, section 17.17.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश "internal.h"

काष्ठा rmid_entry अणु
	u32				rmid;
	पूर्णांक				busy;
	काष्ठा list_head		list;
पूर्ण;

/**
 * @rmid_मुक्त_lru    A least recently used list of मुक्त RMIDs
 *     These RMIDs are guaranteed to have an occupancy less than the
 *     threshold occupancy
 */
अटल LIST_HEAD(rmid_मुक्त_lru);

/**
 * @rmid_limbo_count     count of currently unused but (potentially)
 *     dirty RMIDs.
 *     This counts RMIDs that no one is currently using but that
 *     may have a occupancy value > पूर्णांकel_cqm_threshold. User can change
 *     the threshold occupancy value.
 */
अटल अचिन्हित पूर्णांक rmid_limbo_count;

/**
 * @rmid_entry - The entry in the limbo and मुक्त lists.
 */
अटल काष्ठा rmid_entry	*rmid_ptrs;

/*
 * Global boolean क्रम rdt_monitor which is true अगर any
 * resource monitoring is enabled.
 */
bool rdt_mon_capable;

/*
 * Global to indicate which monitoring events are enabled.
 */
अचिन्हित पूर्णांक rdt_mon_features;

/*
 * This is the threshold cache occupancy at which we will consider an
 * RMID available क्रम re-allocation.
 */
अचिन्हित पूर्णांक resctrl_cqm_threshold;

#घोषणा CF(cf)	((अचिन्हित दीर्घ)(1048576 * (cf) + 0.5))

/*
 * The correction factor table is करोcumented in Documentation/x86/resctrl.rst.
 * If rmid > rmid threshold, MBM total and local values should be multiplied
 * by the correction factor.
 *
 * The original table is modअगरied क्रम better code:
 *
 * 1. The threshold 0 is changed to rmid count - 1 so करोn't करो correction
 *    क्रम the हाल.
 * 2. MBM total and local correction table indexed by core counter which is
 *    equal to (x86_cache_max_rmid + 1) / 8 - 1 and is from 0 up to 27.
 * 3. The correction factor is normalized to 2^20 (1048576) so it's faster
 *    to calculate corrected value by shअगरting:
 *    corrected_value = (original_value * correction_factor) >> 20
 */
अटल स्थिर काष्ठा mbm_correction_factor_table अणु
	u32 rmidthreshold;
	u64 cf;
पूर्ण mbm_cf_table[] __initस्थिर = अणु
	अणु7,	CF(1.000000)पूर्ण,
	अणु15,	CF(1.000000)पूर्ण,
	अणु15,	CF(0.969650)पूर्ण,
	अणु31,	CF(1.000000)पूर्ण,
	अणु31,	CF(1.066667)पूर्ण,
	अणु31,	CF(0.969650)पूर्ण,
	अणु47,	CF(1.142857)पूर्ण,
	अणु63,	CF(1.000000)पूर्ण,
	अणु63,	CF(1.185115)पूर्ण,
	अणु63,	CF(1.066553)पूर्ण,
	अणु79,	CF(1.454545)पूर्ण,
	अणु95,	CF(1.000000)पूर्ण,
	अणु95,	CF(1.230769)पूर्ण,
	अणु95,	CF(1.142857)पूर्ण,
	अणु95,	CF(1.066667)पूर्ण,
	अणु127,	CF(1.000000)पूर्ण,
	अणु127,	CF(1.254863)पूर्ण,
	अणु127,	CF(1.185255)पूर्ण,
	अणु151,	CF(1.000000)पूर्ण,
	अणु127,	CF(1.066667)पूर्ण,
	अणु167,	CF(1.000000)पूर्ण,
	अणु159,	CF(1.454334)पूर्ण,
	अणु183,	CF(1.000000)पूर्ण,
	अणु127,	CF(0.969744)पूर्ण,
	अणु191,	CF(1.280246)पूर्ण,
	अणु191,	CF(1.230921)पूर्ण,
	अणु215,	CF(1.000000)पूर्ण,
	अणु191,	CF(1.143118)पूर्ण,
पूर्ण;

अटल u32 mbm_cf_rmidthreshold __पढ़ो_mostly = अच_पूर्णांक_उच्च;
अटल u64 mbm_cf __पढ़ो_mostly;

अटल अंतरभूत u64 get_corrected_mbm_count(u32 rmid, अचिन्हित दीर्घ val)
अणु
	/* Correct MBM value. */
	अगर (rmid > mbm_cf_rmidthreshold)
		val = (val * mbm_cf) >> 20;

	वापस val;
पूर्ण

अटल अंतरभूत काष्ठा rmid_entry *__rmid_entry(u32 rmid)
अणु
	काष्ठा rmid_entry *entry;

	entry = &rmid_ptrs[rmid];
	WARN_ON(entry->rmid != rmid);

	वापस entry;
पूर्ण

अटल u64 __rmid_पढ़ो(u32 rmid, u32 eventid)
अणु
	u64 val;

	/*
	 * As per the SDM, when IA32_QM_EVTSEL.EvtID (bits 7:0) is configured
	 * with a valid event code क्रम supported resource type and the bits
	 * IA32_QM_EVTSEL.RMID (bits 41:32) are configured with valid RMID,
	 * IA32_QM_CTR.data (bits 61:0) reports the monitored data.
	 * IA32_QM_CTR.Error (bit 63) and IA32_QM_CTR.Unavailable (bit 62)
	 * are error bits.
	 */
	wrmsr(MSR_IA32_QM_EVTSEL, eventid, rmid);
	rdmsrl(MSR_IA32_QM_CTR, val);

	वापस val;
पूर्ण

अटल bool rmid_dirty(काष्ठा rmid_entry *entry)
अणु
	u64 val = __rmid_पढ़ो(entry->rmid, QOS_L3_OCCUP_EVENT_ID);

	वापस val >= resctrl_cqm_threshold;
पूर्ण

/*
 * Check the RMIDs that are marked as busy क्रम this करोमुख्य. If the
 * reported LLC occupancy is below the threshold clear the busy bit and
 * decrement the count. If the busy count माला_लो to zero on an RMID, we
 * मुक्त the RMID
 */
व्योम __check_limbo(काष्ठा rdt_करोमुख्य *d, bool क्रमce_मुक्त)
अणु
	काष्ठा rmid_entry *entry;
	काष्ठा rdt_resource *r;
	u32 crmid = 1, nrmid;

	r = &rdt_resources_all[RDT_RESOURCE_L3];

	/*
	 * Skip RMID 0 and start from RMID 1 and check all the RMIDs that
	 * are marked as busy क्रम occupancy < threshold. If the occupancy
	 * is less than the threshold decrement the busy counter of the
	 * RMID and move it to the मुक्त list when the counter reaches 0.
	 */
	क्रम (;;) अणु
		nrmid = find_next_bit(d->rmid_busy_llc, r->num_rmid, crmid);
		अगर (nrmid >= r->num_rmid)
			अवरोध;

		entry = __rmid_entry(nrmid);
		अगर (क्रमce_मुक्त || !rmid_dirty(entry)) अणु
			clear_bit(entry->rmid, d->rmid_busy_llc);
			अगर (!--entry->busy) अणु
				rmid_limbo_count--;
				list_add_tail(&entry->list, &rmid_मुक्त_lru);
			पूर्ण
		पूर्ण
		crmid = nrmid + 1;
	पूर्ण
पूर्ण

bool has_busy_rmid(काष्ठा rdt_resource *r, काष्ठा rdt_करोमुख्य *d)
अणु
	वापस find_first_bit(d->rmid_busy_llc, r->num_rmid) != r->num_rmid;
पूर्ण

/*
 * As of now the RMIDs allocation is global.
 * However we keep track of which packages the RMIDs
 * are used to optimize the limbo list management.
 */
पूर्णांक alloc_rmid(व्योम)
अणु
	काष्ठा rmid_entry *entry;

	lockdep_निश्चित_held(&rdtgroup_mutex);

	अगर (list_empty(&rmid_मुक्त_lru))
		वापस rmid_limbo_count ? -EBUSY : -ENOSPC;

	entry = list_first_entry(&rmid_मुक्त_lru,
				 काष्ठा rmid_entry, list);
	list_del(&entry->list);

	वापस entry->rmid;
पूर्ण

अटल व्योम add_rmid_to_limbo(काष्ठा rmid_entry *entry)
अणु
	काष्ठा rdt_resource *r;
	काष्ठा rdt_करोमुख्य *d;
	पूर्णांक cpu;
	u64 val;

	r = &rdt_resources_all[RDT_RESOURCE_L3];

	entry->busy = 0;
	cpu = get_cpu();
	list_क्रम_each_entry(d, &r->करोमुख्यs, list) अणु
		अगर (cpumask_test_cpu(cpu, &d->cpu_mask)) अणु
			val = __rmid_पढ़ो(entry->rmid, QOS_L3_OCCUP_EVENT_ID);
			अगर (val <= resctrl_cqm_threshold)
				जारी;
		पूर्ण

		/*
		 * For the first limbo RMID in the करोमुख्य,
		 * setup up the limbo worker.
		 */
		अगर (!has_busy_rmid(r, d))
			cqm_setup_limbo_handler(d, CQM_LIMBOCHECK_INTERVAL);
		set_bit(entry->rmid, d->rmid_busy_llc);
		entry->busy++;
	पूर्ण
	put_cpu();

	अगर (entry->busy)
		rmid_limbo_count++;
	अन्यथा
		list_add_tail(&entry->list, &rmid_मुक्त_lru);
पूर्ण

व्योम मुक्त_rmid(u32 rmid)
अणु
	काष्ठा rmid_entry *entry;

	अगर (!rmid)
		वापस;

	lockdep_निश्चित_held(&rdtgroup_mutex);

	entry = __rmid_entry(rmid);

	अगर (is_llc_occupancy_enabled())
		add_rmid_to_limbo(entry);
	अन्यथा
		list_add_tail(&entry->list, &rmid_मुक्त_lru);
पूर्ण

अटल u64 mbm_overflow_count(u64 prev_msr, u64 cur_msr, अचिन्हित पूर्णांक width)
अणु
	u64 shअगरt = 64 - width, chunks;

	chunks = (cur_msr << shअगरt) - (prev_msr << shअगरt);
	वापस chunks >>= shअगरt;
पूर्ण

अटल पूर्णांक __mon_event_count(u32 rmid, काष्ठा rmid_पढ़ो *rr)
अणु
	काष्ठा mbm_state *m;
	u64 chunks, tval;

	tval = __rmid_पढ़ो(rmid, rr->evtid);
	अगर (tval & (RMID_VAL_ERROR | RMID_VAL_UNAVAIL)) अणु
		rr->val = tval;
		वापस -EINVAL;
	पूर्ण
	चयन (rr->evtid) अणु
	हाल QOS_L3_OCCUP_EVENT_ID:
		rr->val += tval;
		वापस 0;
	हाल QOS_L3_MBM_TOTAL_EVENT_ID:
		m = &rr->d->mbm_total[rmid];
		अवरोध;
	हाल QOS_L3_MBM_LOCAL_EVENT_ID:
		m = &rr->d->mbm_local[rmid];
		अवरोध;
	शेष:
		/*
		 * Code would never reach here because
		 * an invalid event id would fail the __rmid_पढ़ो.
		 */
		वापस -EINVAL;
	पूर्ण

	अगर (rr->first) अणु
		स_रखो(m, 0, माप(काष्ठा mbm_state));
		m->prev_bw_msr = m->prev_msr = tval;
		वापस 0;
	पूर्ण

	chunks = mbm_overflow_count(m->prev_msr, tval, rr->r->mbm_width);
	m->chunks += chunks;
	m->prev_msr = tval;

	rr->val += get_corrected_mbm_count(rmid, m->chunks);

	वापस 0;
पूर्ण

/*
 * Supporting function to calculate the memory bandwidth
 * and delta bandwidth in MBps.
 */
अटल व्योम mbm_bw_count(u32 rmid, काष्ठा rmid_पढ़ो *rr)
अणु
	काष्ठा rdt_resource *r = &rdt_resources_all[RDT_RESOURCE_L3];
	काष्ठा mbm_state *m = &rr->d->mbm_local[rmid];
	u64 tval, cur_bw, chunks;

	tval = __rmid_पढ़ो(rmid, rr->evtid);
	अगर (tval & (RMID_VAL_ERROR | RMID_VAL_UNAVAIL))
		वापस;

	chunks = mbm_overflow_count(m->prev_bw_msr, tval, rr->r->mbm_width);
	cur_bw = (get_corrected_mbm_count(rmid, chunks) * r->mon_scale) >> 20;

	अगर (m->delta_comp)
		m->delta_bw = असल(cur_bw - m->prev_bw);
	m->delta_comp = false;
	m->prev_bw = cur_bw;
	m->prev_bw_msr = tval;
पूर्ण

/*
 * This is called via IPI to पढ़ो the CQM/MBM counters
 * on a करोमुख्य.
 */
व्योम mon_event_count(व्योम *info)
अणु
	काष्ठा rdtgroup *rdtgrp, *entry;
	काष्ठा rmid_पढ़ो *rr = info;
	काष्ठा list_head *head;

	rdtgrp = rr->rgrp;

	अगर (__mon_event_count(rdtgrp->mon.rmid, rr))
		वापस;

	/*
	 * For Ctrl groups पढ़ो data from child monitor groups.
	 */
	head = &rdtgrp->mon.crdtgrp_list;

	अगर (rdtgrp->type == RDTCTRL_GROUP) अणु
		list_क्रम_each_entry(entry, head, mon.crdtgrp_list) अणु
			अगर (__mon_event_count(entry->mon.rmid, rr))
				वापस;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Feedback loop क्रम MBA software controller (mba_sc)
 *
 * mba_sc is a feedback loop where we periodically पढ़ो MBM counters and
 * adjust the bandwidth percentage values via the IA32_MBA_THRTL_MSRs so
 * that:
 *
 *   current bandwidth(cur_bw) < user specअगरied bandwidth(user_bw)
 *
 * This uses the MBM counters to measure the bandwidth and MBA throttle
 * MSRs to control the bandwidth क्रम a particular rdtgrp. It builds on the
 * fact that resctrl rdtgroups have both monitoring and control.
 *
 * The frequency of the checks is 1s and we just tag aदीर्घ the MBM overflow
 * समयr. Having 1s पूर्णांकerval makes the calculation of bandwidth simpler.
 *
 * Although MBA's goal is to restrict the bandwidth to a maximum, there may
 * be a need to increase the bandwidth to aव्योम unnecessarily restricting
 * the L2 <-> L3 traffic.
 *
 * Since MBA controls the L2 बाह्यal bandwidth where as MBM measures the
 * L3 बाह्यal bandwidth the following sequence could lead to such a
 * situation.
 *
 * Consider an rdtgroup which had high L3 <-> memory traffic in initial
 * phases -> mba_sc kicks in and reduced bandwidth percentage values -> but
 * after some समय rdtgroup has mostly L2 <-> L3 traffic.
 *
 * In this हाल we may restrict the rdtgroup's L2 <-> L3 traffic as its
 * throttle MSRs alपढ़ोy have low percentage values.  To aव्योम
 * unnecessarily restricting such rdtgroups, we also increase the bandwidth.
 */
अटल व्योम update_mba_bw(काष्ठा rdtgroup *rgrp, काष्ठा rdt_करोमुख्य *करोm_mbm)
अणु
	u32 closid, rmid, cur_msr, cur_msr_val, new_msr_val;
	काष्ठा mbm_state *pmbm_data, *cmbm_data;
	u32 cur_bw, delta_bw, user_bw;
	काष्ठा rdt_resource *r_mba;
	काष्ठा rdt_करोमुख्य *करोm_mba;
	काष्ठा list_head *head;
	काष्ठा rdtgroup *entry;

	अगर (!is_mbm_local_enabled())
		वापस;

	r_mba = &rdt_resources_all[RDT_RESOURCE_MBA];
	closid = rgrp->closid;
	rmid = rgrp->mon.rmid;
	pmbm_data = &करोm_mbm->mbm_local[rmid];

	करोm_mba = get_करोमुख्य_from_cpu(smp_processor_id(), r_mba);
	अगर (!करोm_mba) अणु
		pr_warn_once("Failure to get domain for MBA update\n");
		वापस;
	पूर्ण

	cur_bw = pmbm_data->prev_bw;
	user_bw = करोm_mba->mbps_val[closid];
	delta_bw = pmbm_data->delta_bw;
	cur_msr_val = करोm_mba->ctrl_val[closid];

	/*
	 * For Ctrl groups पढ़ो data from child monitor groups.
	 */
	head = &rgrp->mon.crdtgrp_list;
	list_क्रम_each_entry(entry, head, mon.crdtgrp_list) अणु
		cmbm_data = &करोm_mbm->mbm_local[entry->mon.rmid];
		cur_bw += cmbm_data->prev_bw;
		delta_bw += cmbm_data->delta_bw;
	पूर्ण

	/*
	 * Scale up/करोwn the bandwidth linearly क्रम the ctrl group.  The
	 * bandwidth step is the bandwidth granularity specअगरied by the
	 * hardware.
	 *
	 * The delta_bw is used when increasing the bandwidth so that we
	 * करोnt alternately increase and decrease the control values
	 * continuously.
	 *
	 * For ex: consider cur_bw = 90MBps, user_bw = 100MBps and अगर
	 * bandwidth step is 20MBps(> user_bw - cur_bw), we would keep
	 * चयनing between 90 and 110 continuously अगर we only check
	 * cur_bw < user_bw.
	 */
	अगर (cur_msr_val > r_mba->membw.min_bw && user_bw < cur_bw) अणु
		new_msr_val = cur_msr_val - r_mba->membw.bw_gran;
	पूर्ण अन्यथा अगर (cur_msr_val < MAX_MBA_BW &&
		   (user_bw > (cur_bw + delta_bw))) अणु
		new_msr_val = cur_msr_val + r_mba->membw.bw_gran;
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

	cur_msr = r_mba->msr_base + closid;
	wrmsrl(cur_msr, delay_bw_map(new_msr_val, r_mba));
	करोm_mba->ctrl_val[closid] = new_msr_val;

	/*
	 * Delta values are updated dynamically package wise क्रम each
	 * rdtgrp every समय the throttle MSR changes value.
	 *
	 * This is because (1)the increase in bandwidth is not perfectly
	 * linear and only "approximately" linear even when the hardware
	 * says it is linear.(2)Also since MBA is a core specअगरic
	 * mechanism, the delta values vary based on number of cores used
	 * by the rdtgrp.
	 */
	pmbm_data->delta_comp = true;
	list_क्रम_each_entry(entry, head, mon.crdtgrp_list) अणु
		cmbm_data = &करोm_mbm->mbm_local[entry->mon.rmid];
		cmbm_data->delta_comp = true;
	पूर्ण
पूर्ण

अटल व्योम mbm_update(काष्ठा rdt_resource *r, काष्ठा rdt_करोमुख्य *d, पूर्णांक rmid)
अणु
	काष्ठा rmid_पढ़ो rr;

	rr.first = false;
	rr.r = r;
	rr.d = d;

	/*
	 * This is रक्षित from concurrent पढ़ोs from user
	 * as both the user and we hold the global mutex.
	 */
	अगर (is_mbm_total_enabled()) अणु
		rr.evtid = QOS_L3_MBM_TOTAL_EVENT_ID;
		__mon_event_count(rmid, &rr);
	पूर्ण
	अगर (is_mbm_local_enabled()) अणु
		rr.evtid = QOS_L3_MBM_LOCAL_EVENT_ID;
		__mon_event_count(rmid, &rr);

		/*
		 * Call the MBA software controller only क्रम the
		 * control groups and when user has enabled
		 * the software controller explicitly.
		 */
		अगर (is_mba_sc(शून्य))
			mbm_bw_count(rmid, &rr);
	पूर्ण
पूर्ण

/*
 * Handler to scan the limbo list and move the RMIDs
 * to मुक्त list whose occupancy < threshold_occupancy.
 */
व्योम cqm_handle_limbo(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ delay = msecs_to_jअगरfies(CQM_LIMBOCHECK_INTERVAL);
	पूर्णांक cpu = smp_processor_id();
	काष्ठा rdt_resource *r;
	काष्ठा rdt_करोमुख्य *d;

	mutex_lock(&rdtgroup_mutex);

	r = &rdt_resources_all[RDT_RESOURCE_L3];
	d = container_of(work, काष्ठा rdt_करोमुख्य, cqm_limbo.work);

	__check_limbo(d, false);

	अगर (has_busy_rmid(r, d))
		schedule_delayed_work_on(cpu, &d->cqm_limbo, delay);

	mutex_unlock(&rdtgroup_mutex);
पूर्ण

व्योम cqm_setup_limbo_handler(काष्ठा rdt_करोमुख्य *करोm, अचिन्हित दीर्घ delay_ms)
अणु
	अचिन्हित दीर्घ delay = msecs_to_jअगरfies(delay_ms);
	पूर्णांक cpu;

	cpu = cpumask_any(&करोm->cpu_mask);
	करोm->cqm_work_cpu = cpu;

	schedule_delayed_work_on(cpu, &करोm->cqm_limbo, delay);
पूर्ण

व्योम mbm_handle_overflow(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ delay = msecs_to_jअगरfies(MBM_OVERFLOW_INTERVAL);
	काष्ठा rdtgroup *prgrp, *crgrp;
	पूर्णांक cpu = smp_processor_id();
	काष्ठा list_head *head;
	काष्ठा rdt_resource *r;
	काष्ठा rdt_करोमुख्य *d;

	mutex_lock(&rdtgroup_mutex);

	अगर (!अटल_branch_likely(&rdt_mon_enable_key))
		जाओ out_unlock;

	r = &rdt_resources_all[RDT_RESOURCE_L3];
	d = container_of(work, काष्ठा rdt_करोमुख्य, mbm_over.work);

	list_क्रम_each_entry(prgrp, &rdt_all_groups, rdtgroup_list) अणु
		mbm_update(r, d, prgrp->mon.rmid);

		head = &prgrp->mon.crdtgrp_list;
		list_क्रम_each_entry(crgrp, head, mon.crdtgrp_list)
			mbm_update(r, d, crgrp->mon.rmid);

		अगर (is_mba_sc(शून्य))
			update_mba_bw(prgrp, d);
	पूर्ण

	schedule_delayed_work_on(cpu, &d->mbm_over, delay);

out_unlock:
	mutex_unlock(&rdtgroup_mutex);
पूर्ण

व्योम mbm_setup_overflow_handler(काष्ठा rdt_करोमुख्य *करोm, अचिन्हित दीर्घ delay_ms)
अणु
	अचिन्हित दीर्घ delay = msecs_to_jअगरfies(delay_ms);
	पूर्णांक cpu;

	अगर (!अटल_branch_likely(&rdt_mon_enable_key))
		वापस;
	cpu = cpumask_any(&करोm->cpu_mask);
	करोm->mbm_work_cpu = cpu;
	schedule_delayed_work_on(cpu, &करोm->mbm_over, delay);
पूर्ण

अटल पूर्णांक करोm_data_init(काष्ठा rdt_resource *r)
अणु
	काष्ठा rmid_entry *entry = शून्य;
	पूर्णांक i, nr_rmids;

	nr_rmids = r->num_rmid;
	rmid_ptrs = kसुस्मृति(nr_rmids, माप(काष्ठा rmid_entry), GFP_KERNEL);
	अगर (!rmid_ptrs)
		वापस -ENOMEM;

	क्रम (i = 0; i < nr_rmids; i++) अणु
		entry = &rmid_ptrs[i];
		INIT_LIST_HEAD(&entry->list);

		entry->rmid = i;
		list_add_tail(&entry->list, &rmid_मुक्त_lru);
	पूर्ण

	/*
	 * RMID 0 is special and is always allocated. It's used क्रम all
	 * tasks that are not monitored.
	 */
	entry = __rmid_entry(0);
	list_del(&entry->list);

	वापस 0;
पूर्ण

अटल काष्ठा mon_evt llc_occupancy_event = अणु
	.name		= "llc_occupancy",
	.evtid		= QOS_L3_OCCUP_EVENT_ID,
पूर्ण;

अटल काष्ठा mon_evt mbm_total_event = अणु
	.name		= "mbm_total_bytes",
	.evtid		= QOS_L3_MBM_TOTAL_EVENT_ID,
पूर्ण;

अटल काष्ठा mon_evt mbm_local_event = अणु
	.name		= "mbm_local_bytes",
	.evtid		= QOS_L3_MBM_LOCAL_EVENT_ID,
पूर्ण;

/*
 * Initialize the event list क्रम the resource.
 *
 * Note that MBM events are also part of RDT_RESOURCE_L3 resource
 * because as per the SDM the total and local memory bandwidth
 * are क्रमागतerated as part of L3 monitoring.
 */
अटल व्योम l3_mon_evt_init(काष्ठा rdt_resource *r)
अणु
	INIT_LIST_HEAD(&r->evt_list);

	अगर (is_llc_occupancy_enabled())
		list_add_tail(&llc_occupancy_event.list, &r->evt_list);
	अगर (is_mbm_total_enabled())
		list_add_tail(&mbm_total_event.list, &r->evt_list);
	अगर (is_mbm_local_enabled())
		list_add_tail(&mbm_local_event.list, &r->evt_list);
पूर्ण

पूर्णांक rdt_get_mon_l3_config(काष्ठा rdt_resource *r)
अणु
	अचिन्हित पूर्णांक mbm_offset = boot_cpu_data.x86_cache_mbm_width_offset;
	अचिन्हित पूर्णांक cl_size = boot_cpu_data.x86_cache_size;
	पूर्णांक ret;

	r->mon_scale = boot_cpu_data.x86_cache_occ_scale;
	r->num_rmid = boot_cpu_data.x86_cache_max_rmid + 1;
	r->mbm_width = MBM_CNTR_WIDTH_BASE;

	अगर (mbm_offset > 0 && mbm_offset <= MBM_CNTR_WIDTH_OFFSET_MAX)
		r->mbm_width += mbm_offset;
	अन्यथा अगर (mbm_offset > MBM_CNTR_WIDTH_OFFSET_MAX)
		pr_warn("Ignoring impossible MBM counter offset\n");

	/*
	 * A reasonable upper limit on the max threshold is the number
	 * of lines tagged per RMID अगर all RMIDs have the same number of
	 * lines tagged in the LLC.
	 *
	 * For a 35MB LLC and 56 RMIDs, this is ~1.8% of the LLC.
	 */
	resctrl_cqm_threshold = cl_size * 1024 / r->num_rmid;

	/* h/w works in units of "boot_cpu_data.x86_cache_occ_scale" */
	resctrl_cqm_threshold /= r->mon_scale;

	ret = करोm_data_init(r);
	अगर (ret)
		वापस ret;

	l3_mon_evt_init(r);

	r->mon_capable = true;
	r->mon_enabled = true;

	वापस 0;
पूर्ण

व्योम __init पूर्णांकel_rdt_mbm_apply_quirk(व्योम)
अणु
	पूर्णांक cf_index;

	cf_index = (boot_cpu_data.x86_cache_max_rmid + 1) / 8 - 1;
	अगर (cf_index >= ARRAY_SIZE(mbm_cf_table)) अणु
		pr_info("No MBM correction factor available\n");
		वापस;
	पूर्ण

	mbm_cf_rmidthreshold = mbm_cf_table[cf_index].rmidthreshold;
	mbm_cf = mbm_cf_table[cf_index].cf;
पूर्ण
