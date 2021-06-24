<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Resource Director Technology(RDT)
 * - Cache Allocation code.
 *
 * Copyright (C) 2016 Intel Corporation
 *
 * Authors:
 *    Fenghua Yu <fenghua.yu@पूर्णांकel.com>
 *    Tony Luck <tony.luck@पूर्णांकel.com>
 *
 * More inक्रमmation about RDT be found in the Intel (R) x86 Architecture
 * Software Developer Manual June 2016, volume 3, section 17.17.
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/cpu.h>
#समावेश <linux/kernfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश "internal.h"

/*
 * Check whether MBA bandwidth percentage value is correct. The value is
 * checked against the minimum and max bandwidth values specअगरied by the
 * hardware. The allocated bandwidth percentage is rounded to the next
 * control step available on the hardware.
 */
अटल bool bw_validate(अक्षर *buf, अचिन्हित दीर्घ *data, काष्ठा rdt_resource *r)
अणु
	अचिन्हित दीर्घ bw;
	पूर्णांक ret;

	/*
	 * Only linear delay values is supported क्रम current Intel SKUs.
	 */
	अगर (!r->membw.delay_linear && r->membw.arch_needs_linear) अणु
		rdt_last_cmd_माला_दो("No support for non-linear MB domains\n");
		वापस false;
	पूर्ण

	ret = kम_से_अदीर्घ(buf, 10, &bw);
	अगर (ret) अणु
		rdt_last_cmd_म_लिखो("Non-decimal digit in MB value %s\n", buf);
		वापस false;
	पूर्ण

	अगर ((bw < r->membw.min_bw || bw > r->शेष_ctrl) &&
	    !is_mba_sc(r)) अणु
		rdt_last_cmd_म_लिखो("MB value %ld out of range [%d,%d]\n", bw,
				    r->membw.min_bw, r->शेष_ctrl);
		वापस false;
	पूर्ण

	*data = roundup(bw, (अचिन्हित दीर्घ)r->membw.bw_gran);
	वापस true;
पूर्ण

पूर्णांक parse_bw(काष्ठा rdt_parse_data *data, काष्ठा rdt_resource *r,
	     काष्ठा rdt_करोमुख्य *d)
अणु
	अचिन्हित दीर्घ bw_val;

	अगर (d->have_new_ctrl) अणु
		rdt_last_cmd_म_लिखो("Duplicate domain %d\n", d->id);
		वापस -EINVAL;
	पूर्ण

	अगर (!bw_validate(data->buf, &bw_val, r))
		वापस -EINVAL;
	d->new_ctrl = bw_val;
	d->have_new_ctrl = true;

	वापस 0;
पूर्ण

/*
 * Check whether a cache bit mask is valid.
 * For Intel the SDM says:
 *	Please note that all (and only) contiguous '1' combinations
 *	are allowed (e.g. FFFFH, 0FF0H, 003CH, etc.).
 * Additionally Haswell requires at least two bits set.
 * AMD allows non-contiguous biपंचांगasks.
 */
अटल bool cbm_validate(अक्षर *buf, u32 *data, काष्ठा rdt_resource *r)
अणु
	अचिन्हित दीर्घ first_bit, zero_bit, val;
	अचिन्हित पूर्णांक cbm_len = r->cache.cbm_len;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret) अणु
		rdt_last_cmd_म_लिखो("Non-hex character in the mask %s\n", buf);
		वापस false;
	पूर्ण

	अगर ((!r->cache.arch_has_empty_biपंचांगaps && val == 0) ||
	    val > r->शेष_ctrl) अणु
		rdt_last_cmd_माला_दो("Mask out of range\n");
		वापस false;
	पूर्ण

	first_bit = find_first_bit(&val, cbm_len);
	zero_bit = find_next_zero_bit(&val, cbm_len, first_bit);

	/* Are non-contiguous biपंचांगaps allowed? */
	अगर (!r->cache.arch_has_sparse_biपंचांगaps &&
	    (find_next_bit(&val, cbm_len, zero_bit) < cbm_len)) अणु
		rdt_last_cmd_म_लिखो("The mask %lx has non-consecutive 1-bits\n", val);
		वापस false;
	पूर्ण

	अगर ((zero_bit - first_bit) < r->cache.min_cbm_bits) अणु
		rdt_last_cmd_म_लिखो("Need at least %d bits in the mask\n",
				    r->cache.min_cbm_bits);
		वापस false;
	पूर्ण

	*data = val;
	वापस true;
पूर्ण

/*
 * Read one cache bit mask (hex). Check that it is valid क्रम the current
 * resource type.
 */
पूर्णांक parse_cbm(काष्ठा rdt_parse_data *data, काष्ठा rdt_resource *r,
	      काष्ठा rdt_करोमुख्य *d)
अणु
	काष्ठा rdtgroup *rdtgrp = data->rdtgrp;
	u32 cbm_val;

	अगर (d->have_new_ctrl) अणु
		rdt_last_cmd_म_लिखो("Duplicate domain %d\n", d->id);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Cannot set up more than one pseuकरो-locked region in a cache
	 * hierarchy.
	 */
	अगर (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP &&
	    rdtgroup_pseuकरो_locked_in_hierarchy(d)) अणु
		rdt_last_cmd_माला_दो("Pseudo-locked region in hierarchy\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!cbm_validate(data->buf, &cbm_val, r))
		वापस -EINVAL;

	अगर ((rdtgrp->mode == RDT_MODE_EXCLUSIVE ||
	     rdtgrp->mode == RDT_MODE_SHAREABLE) &&
	    rdtgroup_cbm_overlaps_pseuकरो_locked(d, cbm_val)) अणु
		rdt_last_cmd_माला_दो("CBM overlaps with pseudo-locked region\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * The CBM may not overlap with the CBM of another closid अगर
	 * either is exclusive.
	 */
	अगर (rdtgroup_cbm_overlaps(r, d, cbm_val, rdtgrp->closid, true)) अणु
		rdt_last_cmd_माला_दो("Overlaps with exclusive group\n");
		वापस -EINVAL;
	पूर्ण

	अगर (rdtgroup_cbm_overlaps(r, d, cbm_val, rdtgrp->closid, false)) अणु
		अगर (rdtgrp->mode == RDT_MODE_EXCLUSIVE ||
		    rdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP) अणु
			rdt_last_cmd_माला_दो("Overlaps with other group\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	d->new_ctrl = cbm_val;
	d->have_new_ctrl = true;

	वापस 0;
पूर्ण

/*
 * For each करोमुख्य in this resource we expect to find a series of:
 *	id=mask
 * separated by ";". The "id" is in decimal, and must match one of
 * the "id"s क्रम this resource.
 */
अटल पूर्णांक parse_line(अक्षर *line, काष्ठा rdt_resource *r,
		      काष्ठा rdtgroup *rdtgrp)
अणु
	काष्ठा rdt_parse_data data;
	अक्षर *करोm = शून्य, *id;
	काष्ठा rdt_करोमुख्य *d;
	अचिन्हित दीर्घ करोm_id;

	अगर (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP &&
	    r->rid == RDT_RESOURCE_MBA) अणु
		rdt_last_cmd_माला_दो("Cannot pseudo-lock MBA resource\n");
		वापस -EINVAL;
	पूर्ण

next:
	अगर (!line || line[0] == '\0')
		वापस 0;
	करोm = strsep(&line, ";");
	id = strsep(&करोm, "=");
	अगर (!करोm || kम_से_अदीर्घ(id, 10, &करोm_id)) अणु
		rdt_last_cmd_माला_दो("Missing '=' or non-numeric domain\n");
		वापस -EINVAL;
	पूर्ण
	करोm = strim(करोm);
	list_क्रम_each_entry(d, &r->करोमुख्यs, list) अणु
		अगर (d->id == करोm_id) अणु
			data.buf = करोm;
			data.rdtgrp = rdtgrp;
			अगर (r->parse_ctrlval(&data, r, d))
				वापस -EINVAL;
			अगर (rdtgrp->mode ==  RDT_MODE_PSEUDO_LOCKSETUP) अणु
				/*
				 * In pseuकरो-locking setup mode and just
				 * parsed a valid CBM that should be
				 * pseuकरो-locked. Only one locked region per
				 * resource group and करोमुख्य so just करो
				 * the required initialization क्रम single
				 * region and वापस.
				 */
				rdtgrp->plr->r = r;
				rdtgrp->plr->d = d;
				rdtgrp->plr->cbm = d->new_ctrl;
				d->plr = rdtgrp->plr;
				वापस 0;
			पूर्ण
			जाओ next;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

पूर्णांक update_करोमुख्यs(काष्ठा rdt_resource *r, पूर्णांक closid)
अणु
	काष्ठा msr_param msr_param;
	cpumask_var_t cpu_mask;
	काष्ठा rdt_करोमुख्य *d;
	bool mba_sc;
	u32 *dc;
	पूर्णांक cpu;

	अगर (!zalloc_cpumask_var(&cpu_mask, GFP_KERNEL))
		वापस -ENOMEM;

	msr_param.low = closid;
	msr_param.high = msr_param.low + 1;
	msr_param.res = r;

	mba_sc = is_mba_sc(r);
	list_क्रम_each_entry(d, &r->करोमुख्यs, list) अणु
		dc = !mba_sc ? d->ctrl_val : d->mbps_val;
		अगर (d->have_new_ctrl && d->new_ctrl != dc[closid]) अणु
			cpumask_set_cpu(cpumask_any(&d->cpu_mask), cpu_mask);
			dc[closid] = d->new_ctrl;
		पूर्ण
	पूर्ण

	/*
	 * Aव्योम writing the control msr with control values when
	 * MBA software controller is enabled
	 */
	अगर (cpumask_empty(cpu_mask) || mba_sc)
		जाओ करोne;
	cpu = get_cpu();
	/* Update resource control msr on this CPU अगर it's in cpu_mask. */
	अगर (cpumask_test_cpu(cpu, cpu_mask))
		rdt_ctrl_update(&msr_param);
	/* Update resource control msr on other CPUs. */
	smp_call_function_many(cpu_mask, rdt_ctrl_update, &msr_param, 1);
	put_cpu();

करोne:
	मुक्त_cpumask_var(cpu_mask);

	वापस 0;
पूर्ण

अटल पूर्णांक rdtgroup_parse_resource(अक्षर *resname, अक्षर *tok,
				   काष्ठा rdtgroup *rdtgrp)
अणु
	काष्ठा rdt_resource *r;

	क्रम_each_alloc_enabled_rdt_resource(r) अणु
		अगर (!म_भेद(resname, r->name) && rdtgrp->closid < r->num_closid)
			वापस parse_line(tok, r, rdtgrp);
	पूर्ण
	rdt_last_cmd_म_लिखो("Unknown or unsupported resource name '%s'\n", resname);
	वापस -EINVAL;
पूर्ण

sमाप_प्रकार rdtgroup_schemata_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
				अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा rdtgroup *rdtgrp;
	काष्ठा rdt_करोमुख्य *करोm;
	काष्ठा rdt_resource *r;
	अक्षर *tok, *resname;
	पूर्णांक ret = 0;

	/* Valid input requires a trailing newline */
	अगर (nbytes == 0 || buf[nbytes - 1] != '\n')
		वापस -EINVAL;
	buf[nbytes - 1] = '\0';

	cpus_पढ़ो_lock();
	rdtgrp = rdtgroup_kn_lock_live(of->kn);
	अगर (!rdtgrp) अणु
		rdtgroup_kn_unlock(of->kn);
		cpus_पढ़ो_unlock();
		वापस -ENOENT;
	पूर्ण
	rdt_last_cmd_clear();

	/*
	 * No changes to pseuकरो-locked region allowed. It has to be हटाओd
	 * and re-created instead.
	 */
	अगर (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKED) अणु
		ret = -EINVAL;
		rdt_last_cmd_माला_दो("Resource group is pseudo-locked\n");
		जाओ out;
	पूर्ण

	क्रम_each_alloc_enabled_rdt_resource(r) अणु
		list_क्रम_each_entry(करोm, &r->करोमुख्यs, list)
			करोm->have_new_ctrl = false;
	पूर्ण

	जबतक ((tok = strsep(&buf, "\n")) != शून्य) अणु
		resname = strim(strsep(&tok, ":"));
		अगर (!tok) अणु
			rdt_last_cmd_माला_दो("Missing ':'\n");
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		अगर (tok[0] == '\0') अणु
			rdt_last_cmd_म_लिखो("Missing '%s' value\n", resname);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		ret = rdtgroup_parse_resource(resname, tok, rdtgrp);
		अगर (ret)
			जाओ out;
	पूर्ण

	क्रम_each_alloc_enabled_rdt_resource(r) अणु
		ret = update_करोमुख्यs(r, rdtgrp->closid);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP) अणु
		/*
		 * If pseuकरो-locking fails we keep the resource group in
		 * mode RDT_MODE_PSEUDO_LOCKSETUP with its class of service
		 * active and updated क्रम just the करोमुख्य the pseuकरो-locked
		 * region was requested क्रम.
		 */
		ret = rdtgroup_pseuकरो_lock_create(rdtgrp);
	पूर्ण

out:
	rdtgroup_kn_unlock(of->kn);
	cpus_पढ़ो_unlock();
	वापस ret ?: nbytes;
पूर्ण

अटल व्योम show_करोms(काष्ठा seq_file *s, काष्ठा rdt_resource *r, पूर्णांक closid)
अणु
	काष्ठा rdt_करोमुख्य *करोm;
	bool sep = false;
	u32 ctrl_val;

	seq_म_लिखो(s, "%*s:", max_name_width, r->name);
	list_क्रम_each_entry(करोm, &r->करोमुख्यs, list) अणु
		अगर (sep)
			seq_माला_दो(s, ";");

		ctrl_val = (!is_mba_sc(r) ? करोm->ctrl_val[closid] :
			    करोm->mbps_val[closid]);
		seq_म_लिखो(s, r->क्रमmat_str, करोm->id, max_data_width,
			   ctrl_val);
		sep = true;
	पूर्ण
	seq_माला_दो(s, "\n");
पूर्ण

पूर्णांक rdtgroup_schemata_show(काष्ठा kernfs_खोलो_file *of,
			   काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा rdtgroup *rdtgrp;
	काष्ठा rdt_resource *r;
	पूर्णांक ret = 0;
	u32 closid;

	rdtgrp = rdtgroup_kn_lock_live(of->kn);
	अगर (rdtgrp) अणु
		अगर (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP) अणु
			क्रम_each_alloc_enabled_rdt_resource(r)
				seq_म_लिखो(s, "%s:uninitialized\n", r->name);
		पूर्ण अन्यथा अगर (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKED) अणु
			अगर (!rdtgrp->plr->d) अणु
				rdt_last_cmd_clear();
				rdt_last_cmd_माला_दो("Cache domain offline\n");
				ret = -ENODEV;
			पूर्ण अन्यथा अणु
				seq_म_लिखो(s, "%s:%d=%x\n",
					   rdtgrp->plr->r->name,
					   rdtgrp->plr->d->id,
					   rdtgrp->plr->cbm);
			पूर्ण
		पूर्ण अन्यथा अणु
			closid = rdtgrp->closid;
			क्रम_each_alloc_enabled_rdt_resource(r) अणु
				अगर (closid < r->num_closid)
					show_करोms(s, r, closid);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -ENOENT;
	पूर्ण
	rdtgroup_kn_unlock(of->kn);
	वापस ret;
पूर्ण

व्योम mon_event_पढ़ो(काष्ठा rmid_पढ़ो *rr, काष्ठा rdt_resource *r,
		    काष्ठा rdt_करोमुख्य *d, काष्ठा rdtgroup *rdtgrp,
		    पूर्णांक evtid, पूर्णांक first)
अणु
	/*
	 * setup the parameters to send to the IPI to पढ़ो the data.
	 */
	rr->rgrp = rdtgrp;
	rr->evtid = evtid;
	rr->r = r;
	rr->d = d;
	rr->val = 0;
	rr->first = first;

	smp_call_function_any(&d->cpu_mask, mon_event_count, rr, 1);
पूर्ण

पूर्णांक rdtgroup_mondata_show(काष्ठा seq_file *m, व्योम *arg)
अणु
	काष्ठा kernfs_खोलो_file *of = m->निजी;
	u32 resid, evtid, करोmid;
	काष्ठा rdtgroup *rdtgrp;
	काष्ठा rdt_resource *r;
	जोड़ mon_data_bits md;
	काष्ठा rdt_करोमुख्य *d;
	काष्ठा rmid_पढ़ो rr;
	पूर्णांक ret = 0;

	rdtgrp = rdtgroup_kn_lock_live(of->kn);
	अगर (!rdtgrp) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	md.priv = of->kn->priv;
	resid = md.u.rid;
	करोmid = md.u.करोmid;
	evtid = md.u.evtid;

	r = &rdt_resources_all[resid];
	d = rdt_find_करोमुख्य(r, करोmid, शून्य);
	अगर (IS_ERR_OR_शून्य(d)) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	mon_event_पढ़ो(&rr, r, d, rdtgrp, evtid, false);

	अगर (rr.val & RMID_VAL_ERROR)
		seq_माला_दो(m, "Error\n");
	अन्यथा अगर (rr.val & RMID_VAL_UNAVAIL)
		seq_माला_दो(m, "Unavailable\n");
	अन्यथा
		seq_म_लिखो(m, "%llu\n", rr.val * r->mon_scale);

out:
	rdtgroup_kn_unlock(of->kn);
	वापस ret;
पूर्ण
