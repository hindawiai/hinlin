<शैली गुरु>
/*
 * Copyright(c) 2011-2016 Intel Corporation. All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *    Anhua Xu
 *    Kevin Tian <kevin.tian@पूर्णांकel.com>
 *
 * Contributors:
 *    Min He <min.he@पूर्णांकel.com>
 *    Bing Niu <bing.niu@पूर्णांकel.com>
 *    Zhi Wang <zhi.a.wang@पूर्णांकel.com>
 *
 */

#समावेश "i915_drv.h"
#समावेश "gvt.h"

अटल bool vgpu_has_pending_workload(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	क्रमागत पूर्णांकel_engine_id i;
	काष्ठा पूर्णांकel_engine_cs *engine;

	क्रम_each_engine(engine, vgpu->gvt->gt, i) अणु
		अगर (!list_empty(workload_q_head(vgpu, engine)))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* We give 2 seconds higher prio क्रम vGPU during start */
#घोषणा GVT_SCHED_VGPU_PRI_TIME  2

काष्ठा vgpu_sched_data अणु
	काष्ठा list_head lru_list;
	काष्ठा पूर्णांकel_vgpu *vgpu;
	bool active;
	bool pri_sched;
	kसमय_प्रकार pri_समय;
	kसमय_प्रकार sched_in_समय;
	kसमय_प्रकार sched_समय;
	kसमय_प्रकार left_ts;
	kसमय_प्रकार allocated_ts;

	काष्ठा vgpu_sched_ctl sched_ctl;
पूर्ण;

काष्ठा gvt_sched_data अणु
	काष्ठा पूर्णांकel_gvt *gvt;
	काष्ठा hrसमयr समयr;
	अचिन्हित दीर्घ period;
	काष्ठा list_head lru_runq_head;
	kसमय_प्रकार expire_समय;
पूर्ण;

अटल व्योम vgpu_update_बारlice(काष्ठा पूर्णांकel_vgpu *vgpu, kसमय_प्रकार cur_समय)
अणु
	kसमय_प्रकार delta_ts;
	काष्ठा vgpu_sched_data *vgpu_data;

	अगर (!vgpu || vgpu == vgpu->gvt->idle_vgpu)
		वापस;

	vgpu_data = vgpu->sched_data;
	delta_ts = kसमय_sub(cur_समय, vgpu_data->sched_in_समय);
	vgpu_data->sched_समय = kसमय_add(vgpu_data->sched_समय, delta_ts);
	vgpu_data->left_ts = kसमय_sub(vgpu_data->left_ts, delta_ts);
	vgpu_data->sched_in_समय = cur_समय;
पूर्ण

#घोषणा GVT_TS_BALANCE_PERIOD_MS 100
#घोषणा GVT_TS_BALANCE_STAGE_NUM 10

अटल व्योम gvt_balance_बारlice(काष्ठा gvt_sched_data *sched_data)
अणु
	काष्ठा vgpu_sched_data *vgpu_data;
	काष्ठा list_head *pos;
	अटल u64 stage_check;
	पूर्णांक stage = stage_check++ % GVT_TS_BALANCE_STAGE_NUM;

	/* The बारlice accumulation reset at stage 0, which is
	 * allocated again without adding previous debt.
	 */
	अगर (stage == 0) अणु
		पूर्णांक total_weight = 0;
		kसमय_प्रकार fair_बारlice;

		list_क्रम_each(pos, &sched_data->lru_runq_head) अणु
			vgpu_data = container_of(pos, काष्ठा vgpu_sched_data, lru_list);
			total_weight += vgpu_data->sched_ctl.weight;
		पूर्ण

		list_क्रम_each(pos, &sched_data->lru_runq_head) अणु
			vgpu_data = container_of(pos, काष्ठा vgpu_sched_data, lru_list);
			fair_बारlice = kसमय_भागns(ms_to_kसमय(GVT_TS_BALANCE_PERIOD_MS),
						     total_weight) * vgpu_data->sched_ctl.weight;

			vgpu_data->allocated_ts = fair_बारlice;
			vgpu_data->left_ts = vgpu_data->allocated_ts;
		पूर्ण
	पूर्ण अन्यथा अणु
		list_क्रम_each(pos, &sched_data->lru_runq_head) अणु
			vgpu_data = container_of(pos, काष्ठा vgpu_sched_data, lru_list);

			/* बारlice क्रम next 100ms should add the left/debt
			 * slice of previous stages.
			 */
			vgpu_data->left_ts += vgpu_data->allocated_ts;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम try_to_schedule_next_vgpu(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा पूर्णांकel_gvt_workload_scheduler *scheduler = &gvt->scheduler;
	क्रमागत पूर्णांकel_engine_id i;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा vgpu_sched_data *vgpu_data;
	kसमय_प्रकार cur_समय;

	/* no need to schedule अगर next_vgpu is the same with current_vgpu,
	 * let scheduler chose next_vgpu again by setting it to शून्य.
	 */
	अगर (scheduler->next_vgpu == scheduler->current_vgpu) अणु
		scheduler->next_vgpu = शून्य;
		वापस;
	पूर्ण

	/*
	 * after the flag is set, workload dispatch thपढ़ो will
	 * stop dispatching workload क्रम current vgpu
	 */
	scheduler->need_reschedule = true;

	/* still have uncompleted workload? */
	क्रम_each_engine(engine, gvt->gt, i) अणु
		अगर (scheduler->current_workload[engine->id])
			वापस;
	पूर्ण

	cur_समय = kसमय_get();
	vgpu_update_बारlice(scheduler->current_vgpu, cur_समय);
	vgpu_data = scheduler->next_vgpu->sched_data;
	vgpu_data->sched_in_समय = cur_समय;

	/* चयन current vgpu */
	scheduler->current_vgpu = scheduler->next_vgpu;
	scheduler->next_vgpu = शून्य;

	scheduler->need_reschedule = false;

	/* wake up workload dispatch thपढ़ो */
	क्रम_each_engine(engine, gvt->gt, i)
		wake_up(&scheduler->रुकोq[engine->id]);
पूर्ण

अटल काष्ठा पूर्णांकel_vgpu *find_busy_vgpu(काष्ठा gvt_sched_data *sched_data)
अणु
	काष्ठा vgpu_sched_data *vgpu_data;
	काष्ठा पूर्णांकel_vgpu *vgpu = शून्य;
	काष्ठा list_head *head = &sched_data->lru_runq_head;
	काष्ठा list_head *pos;

	/* search a vgpu with pending workload */
	list_क्रम_each(pos, head) अणु

		vgpu_data = container_of(pos, काष्ठा vgpu_sched_data, lru_list);
		अगर (!vgpu_has_pending_workload(vgpu_data->vgpu))
			जारी;

		अगर (vgpu_data->pri_sched) अणु
			अगर (kसमय_beक्रमe(kसमय_get(), vgpu_data->pri_समय)) अणु
				vgpu = vgpu_data->vgpu;
				अवरोध;
			पूर्ण अन्यथा
				vgpu_data->pri_sched = false;
		पूर्ण

		/* Return the vGPU only अगर it has समय slice left */
		अगर (vgpu_data->left_ts > 0) अणु
			vgpu = vgpu_data->vgpu;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस vgpu;
पूर्ण

/* in nanosecond */
#घोषणा GVT_DEFAULT_TIME_SLICE 1000000

अटल व्योम tbs_sched_func(काष्ठा gvt_sched_data *sched_data)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = sched_data->gvt;
	काष्ठा पूर्णांकel_gvt_workload_scheduler *scheduler = &gvt->scheduler;
	काष्ठा vgpu_sched_data *vgpu_data;
	काष्ठा पूर्णांकel_vgpu *vgpu = शून्य;

	/* no active vgpu or has alपढ़ोy had a target */
	अगर (list_empty(&sched_data->lru_runq_head) || scheduler->next_vgpu)
		जाओ out;

	vgpu = find_busy_vgpu(sched_data);
	अगर (vgpu) अणु
		scheduler->next_vgpu = vgpu;
		vgpu_data = vgpu->sched_data;
		अगर (!vgpu_data->pri_sched) अणु
			/* Move the last used vGPU to the tail of lru_list */
			list_del_init(&vgpu_data->lru_list);
			list_add_tail(&vgpu_data->lru_list,
				      &sched_data->lru_runq_head);
		पूर्ण
	पूर्ण अन्यथा अणु
		scheduler->next_vgpu = gvt->idle_vgpu;
	पूर्ण
out:
	अगर (scheduler->next_vgpu)
		try_to_schedule_next_vgpu(gvt);
पूर्ण

व्योम पूर्णांकel_gvt_schedule(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा gvt_sched_data *sched_data = gvt->scheduler.sched_data;
	kसमय_प्रकार cur_समय;

	mutex_lock(&gvt->sched_lock);
	cur_समय = kसमय_get();

	अगर (test_and_clear_bit(INTEL_GVT_REQUEST_SCHED,
				(व्योम *)&gvt->service_request)) अणु
		अगर (cur_समय >= sched_data->expire_समय) अणु
			gvt_balance_बारlice(sched_data);
			sched_data->expire_समय = kसमय_add_ms(
				cur_समय, GVT_TS_BALANCE_PERIOD_MS);
		पूर्ण
	पूर्ण
	clear_bit(INTEL_GVT_REQUEST_EVENT_SCHED, (व्योम *)&gvt->service_request);

	vgpu_update_बारlice(gvt->scheduler.current_vgpu, cur_समय);
	tbs_sched_func(sched_data);

	mutex_unlock(&gvt->sched_lock);
पूर्ण

अटल क्रमागत hrसमयr_restart tbs_समयr_fn(काष्ठा hrसमयr *समयr_data)
अणु
	काष्ठा gvt_sched_data *data;

	data = container_of(समयr_data, काष्ठा gvt_sched_data, समयr);

	पूर्णांकel_gvt_request_service(data->gvt, INTEL_GVT_REQUEST_SCHED);

	hrसमयr_add_expires_ns(&data->समयr, data->period);

	वापस HRTIMER_RESTART;
पूर्ण

अटल पूर्णांक tbs_sched_init(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा पूर्णांकel_gvt_workload_scheduler *scheduler =
		&gvt->scheduler;

	काष्ठा gvt_sched_data *data;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&data->lru_runq_head);
	hrसमयr_init(&data->समयr, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
	data->समयr.function = tbs_समयr_fn;
	data->period = GVT_DEFAULT_TIME_SLICE;
	data->gvt = gvt;

	scheduler->sched_data = data;

	वापस 0;
पूर्ण

अटल व्योम tbs_sched_clean(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा पूर्णांकel_gvt_workload_scheduler *scheduler =
		&gvt->scheduler;
	काष्ठा gvt_sched_data *data = scheduler->sched_data;

	hrसमयr_cancel(&data->समयr);

	kमुक्त(data);
	scheduler->sched_data = शून्य;
पूर्ण

अटल पूर्णांक tbs_sched_init_vgpu(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा vgpu_sched_data *data;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->sched_ctl.weight = vgpu->sched_ctl.weight;
	data->vgpu = vgpu;
	INIT_LIST_HEAD(&data->lru_list);

	vgpu->sched_data = data;

	वापस 0;
पूर्ण

अटल व्योम tbs_sched_clean_vgpu(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा gvt_sched_data *sched_data = gvt->scheduler.sched_data;

	kमुक्त(vgpu->sched_data);
	vgpu->sched_data = शून्य;

	/* this vgpu id has been हटाओd */
	अगर (idr_is_empty(&gvt->vgpu_idr))
		hrसमयr_cancel(&sched_data->समयr);
पूर्ण

अटल व्योम tbs_sched_start_schedule(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा gvt_sched_data *sched_data = vgpu->gvt->scheduler.sched_data;
	काष्ठा vgpu_sched_data *vgpu_data = vgpu->sched_data;
	kसमय_प्रकार now;

	अगर (!list_empty(&vgpu_data->lru_list))
		वापस;

	now = kसमय_get();
	vgpu_data->pri_समय = kसमय_add(now,
					kसमय_set(GVT_SCHED_VGPU_PRI_TIME, 0));
	vgpu_data->pri_sched = true;

	list_add(&vgpu_data->lru_list, &sched_data->lru_runq_head);

	अगर (!hrसमयr_active(&sched_data->समयr))
		hrसमयr_start(&sched_data->समयr, kसमय_add_ns(kसमय_get(),
			sched_data->period), HRTIMER_MODE_ABS);
	vgpu_data->active = true;
पूर्ण

अटल व्योम tbs_sched_stop_schedule(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा vgpu_sched_data *vgpu_data = vgpu->sched_data;

	list_del_init(&vgpu_data->lru_list);
	vgpu_data->active = false;
पूर्ण

अटल काष्ठा पूर्णांकel_gvt_sched_policy_ops tbs_schedule_ops = अणु
	.init = tbs_sched_init,
	.clean = tbs_sched_clean,
	.init_vgpu = tbs_sched_init_vgpu,
	.clean_vgpu = tbs_sched_clean_vgpu,
	.start_schedule = tbs_sched_start_schedule,
	.stop_schedule = tbs_sched_stop_schedule,
पूर्ण;

पूर्णांक पूर्णांकel_gvt_init_sched_policy(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	पूर्णांक ret;

	mutex_lock(&gvt->sched_lock);
	gvt->scheduler.sched_ops = &tbs_schedule_ops;
	ret = gvt->scheduler.sched_ops->init(gvt);
	mutex_unlock(&gvt->sched_lock);

	वापस ret;
पूर्ण

व्योम पूर्णांकel_gvt_clean_sched_policy(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	mutex_lock(&gvt->sched_lock);
	gvt->scheduler.sched_ops->clean(gvt);
	mutex_unlock(&gvt->sched_lock);
पूर्ण

/* क्रम per-vgpu scheduler policy, there are 2 per-vgpu data:
 * sched_data, and sched_ctl. We see these 2 data as part of
 * the global scheduler which are proteced by gvt->sched_lock.
 * Caller should make their decision अगर the vgpu_lock should
 * be hold outside.
 */

पूर्णांक पूर्णांकel_vgpu_init_sched_policy(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	पूर्णांक ret;

	mutex_lock(&vgpu->gvt->sched_lock);
	ret = vgpu->gvt->scheduler.sched_ops->init_vgpu(vgpu);
	mutex_unlock(&vgpu->gvt->sched_lock);

	वापस ret;
पूर्ण

व्योम पूर्णांकel_vgpu_clean_sched_policy(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	mutex_lock(&vgpu->gvt->sched_lock);
	vgpu->gvt->scheduler.sched_ops->clean_vgpu(vgpu);
	mutex_unlock(&vgpu->gvt->sched_lock);
पूर्ण

व्योम पूर्णांकel_vgpu_start_schedule(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा vgpu_sched_data *vgpu_data = vgpu->sched_data;

	mutex_lock(&vgpu->gvt->sched_lock);
	अगर (!vgpu_data->active) अणु
		gvt_dbg_core("vgpu%d: start schedule\n", vgpu->id);
		vgpu->gvt->scheduler.sched_ops->start_schedule(vgpu);
	पूर्ण
	mutex_unlock(&vgpu->gvt->sched_lock);
पूर्ण

व्योम पूर्णांकel_gvt_kick_schedule(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	mutex_lock(&gvt->sched_lock);
	पूर्णांकel_gvt_request_service(gvt, INTEL_GVT_REQUEST_EVENT_SCHED);
	mutex_unlock(&gvt->sched_lock);
पूर्ण

व्योम पूर्णांकel_vgpu_stop_schedule(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा पूर्णांकel_gvt_workload_scheduler *scheduler =
		&vgpu->gvt->scheduler;
	काष्ठा vgpu_sched_data *vgpu_data = vgpu->sched_data;
	काष्ठा drm_i915_निजी *dev_priv = vgpu->gvt->gt->i915;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	अगर (!vgpu_data->active)
		वापस;

	gvt_dbg_core("vgpu%d: stop schedule\n", vgpu->id);

	mutex_lock(&vgpu->gvt->sched_lock);
	scheduler->sched_ops->stop_schedule(vgpu);

	अगर (scheduler->next_vgpu == vgpu)
		scheduler->next_vgpu = शून्य;

	अगर (scheduler->current_vgpu == vgpu) अणु
		/* stop workload dispatching */
		scheduler->need_reschedule = true;
		scheduler->current_vgpu = शून्य;
	पूर्ण

	पूर्णांकel_runसमय_pm_get(&dev_priv->runसमय_pm);
	spin_lock_bh(&scheduler->mmio_context_lock);
	क्रम_each_engine(engine, vgpu->gvt->gt, id) अणु
		अगर (scheduler->engine_owner[engine->id] == vgpu) अणु
			पूर्णांकel_gvt_चयन_mmio(vgpu, शून्य, engine);
			scheduler->engine_owner[engine->id] = शून्य;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&scheduler->mmio_context_lock);
	पूर्णांकel_runसमय_pm_put_unchecked(&dev_priv->runसमय_pm);
	mutex_unlock(&vgpu->gvt->sched_lock);
पूर्ण
