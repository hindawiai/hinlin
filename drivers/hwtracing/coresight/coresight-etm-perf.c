<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(C) 2015 Linaro Limited. All rights reserved.
 * Author: Mathieu Poirier <mathieu.poirier@linaro.org>
 */

#समावेश <linux/coresight.h>
#समावेश <linux/coresight-pmu.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/percpu-defs.h>
#समावेश <linux/slab.h>
#समावेश <linux/stringhash.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

#समावेश "coresight-etm-perf.h"
#समावेश "coresight-priv.h"

अटल काष्ठा pmu eपंचांग_pmu;
अटल bool eपंचांग_perf_up;

/*
 * An ETM context क्रम a running event includes the perf aux handle
 * and aux_data. For ETM, the aux_data (eपंचांग_event_data), consists of
 * the trace path and the sink configuration. The event data is accessible
 * via perf_get_aux(handle). However, a sink could "end" a perf output
 * handle via the IRQ handler. And अगर the "sink" encounters a failure
 * to "begin" another session (e.g due to lack of space in the buffer),
 * the handle will be cleared. Thus, the event_data may not be accessible
 * from the handle when we get to the eपंचांग_event_stop(), which is required
 * क्रम stopping the trace path. The event_data is guaranteed to stay alive
 * until "free_aux()", which cannot happen as दीर्घ as the event is active on
 * the ETM. Thus the event_data क्रम the session must be part of the ETM context
 * to make sure we can disable the trace path.
 */
काष्ठा eपंचांग_ctxt अणु
	काष्ठा perf_output_handle handle;
	काष्ठा eपंचांग_event_data *event_data;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा eपंचांग_ctxt, eपंचांग_ctxt);
अटल DEFINE_PER_CPU(काष्ठा coresight_device *, csdev_src);

/*
 * The PMU क्रमmats were orignally क्रम ETMv3.5/PTM's ETMCR 'config';
 * now take them as general क्रमmats and apply on all ETMs.
 */
PMU_FORMAT_ATTR(cycacc,		"config:" __stringअगरy(ETM_OPT_CYCACC));
/* contextid1 enables tracing CONTEXTIDR_EL1 क्रम ETMv4 */
PMU_FORMAT_ATTR(contextid1,	"config:" __stringअगरy(ETM_OPT_CTXTID));
/* contextid2 enables tracing CONTEXTIDR_EL2 क्रम ETMv4 */
PMU_FORMAT_ATTR(contextid2,	"config:" __stringअगरy(ETM_OPT_CTXTID2));
PMU_FORMAT_ATTR(बारtamp,	"config:" __stringअगरy(ETM_OPT_TS));
PMU_FORMAT_ATTR(retstack,	"config:" __stringअगरy(ETM_OPT_RETSTK));
/* Sink ID - same क्रम all ETMs */
PMU_FORMAT_ATTR(sinkid,		"config2:0-31");

/*
 * contextid always traces the "PID".  The PID is in CONTEXTIDR_EL1
 * when the kernel is running at EL1; when the kernel is at EL2,
 * the PID is in CONTEXTIDR_EL2.
 */
अटल sमाप_प्रकार क्रमmat_attr_contextid_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *page)
अणु
	पूर्णांक pid_fmt = ETM_OPT_CTXTID;

#अगर IS_ENABLED(CONFIG_CORESIGHT_SOURCE_ETM4X)
	pid_fmt = is_kernel_in_hyp_mode() ? ETM_OPT_CTXTID2 : ETM_OPT_CTXTID;
#पूर्ण_अगर
	वापस प्र_लिखो(page, "config:%d\n", pid_fmt);
पूर्ण

अटल काष्ठा device_attribute क्रमmat_attr_contextid =
	__ATTR(contextid, 0444, क्रमmat_attr_contextid_show, शून्य);

अटल काष्ठा attribute *eपंचांग_config_क्रमmats_attr[] = अणु
	&क्रमmat_attr_cycacc.attr,
	&क्रमmat_attr_contextid.attr,
	&क्रमmat_attr_contextid1.attr,
	&क्रमmat_attr_contextid2.attr,
	&क्रमmat_attr_बारtamp.attr,
	&क्रमmat_attr_retstack.attr,
	&क्रमmat_attr_sinkid.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group eपंचांग_pmu_क्रमmat_group = अणु
	.name   = "format",
	.attrs  = eपंचांग_config_क्रमmats_attr,
पूर्ण;

अटल काष्ठा attribute *eपंचांग_config_sinks_attr[] = अणु
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group eपंचांग_pmu_sinks_group = अणु
	.name   = "sinks",
	.attrs  = eपंचांग_config_sinks_attr,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *eपंचांग_pmu_attr_groups[] = अणु
	&eपंचांग_pmu_क्रमmat_group,
	&eपंचांग_pmu_sinks_group,
	शून्य,
पूर्ण;

अटल अंतरभूत काष्ठा list_head **
eपंचांग_event_cpu_path_ptr(काष्ठा eपंचांग_event_data *data, पूर्णांक cpu)
अणु
	वापस per_cpu_ptr(data->path, cpu);
पूर्ण

अटल अंतरभूत काष्ठा list_head *
eपंचांग_event_cpu_path(काष्ठा eपंचांग_event_data *data, पूर्णांक cpu)
अणु
	वापस *eपंचांग_event_cpu_path_ptr(data, cpu);
पूर्ण

अटल व्योम eपंचांग_event_पढ़ो(काष्ठा perf_event *event) अणुपूर्ण

अटल पूर्णांक eपंचांग_addr_filters_alloc(काष्ठा perf_event *event)
अणु
	काष्ठा eपंचांग_filters *filters;
	पूर्णांक node = event->cpu == -1 ? -1 : cpu_to_node(event->cpu);

	filters = kzalloc_node(माप(काष्ठा eपंचांग_filters), GFP_KERNEL, node);
	अगर (!filters)
		वापस -ENOMEM;

	अगर (event->parent)
		स_नकल(filters, event->parent->hw.addr_filters,
		       माप(*filters));

	event->hw.addr_filters = filters;

	वापस 0;
पूर्ण

अटल व्योम eपंचांग_event_destroy(काष्ठा perf_event *event)
अणु
	kमुक्त(event->hw.addr_filters);
	event->hw.addr_filters = शून्य;
पूर्ण

अटल पूर्णांक eपंचांग_event_init(काष्ठा perf_event *event)
अणु
	पूर्णांक ret = 0;

	अगर (event->attr.type != eपंचांग_pmu.type) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	ret = eपंचांग_addr_filters_alloc(event);
	अगर (ret)
		जाओ out;

	event->destroy = eपंचांग_event_destroy;
out:
	वापस ret;
पूर्ण

अटल व्योम मुक्त_sink_buffer(काष्ठा eपंचांग_event_data *event_data)
अणु
	पूर्णांक cpu;
	cpumask_t *mask = &event_data->mask;
	काष्ठा coresight_device *sink;

	अगर (!event_data->snk_config)
		वापस;

	अगर (WARN_ON(cpumask_empty(mask)))
		वापस;

	cpu = cpumask_first(mask);
	sink = coresight_get_sink(eपंचांग_event_cpu_path(event_data, cpu));
	sink_ops(sink)->मुक्त_buffer(event_data->snk_config);
पूर्ण

अटल व्योम मुक्त_event_data(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक cpu;
	cpumask_t *mask;
	काष्ठा eपंचांग_event_data *event_data;

	event_data = container_of(work, काष्ठा eपंचांग_event_data, work);
	mask = &event_data->mask;

	/* Free the sink buffers, अगर there are any */
	मुक्त_sink_buffer(event_data);

	क्रम_each_cpu(cpu, mask) अणु
		काष्ठा list_head **ppath;

		ppath = eपंचांग_event_cpu_path_ptr(event_data, cpu);
		अगर (!(IS_ERR_OR_शून्य(*ppath)))
			coresight_release_path(*ppath);
		*ppath = शून्य;
	पूर्ण

	मुक्त_percpu(event_data->path);
	kमुक्त(event_data);
पूर्ण

अटल व्योम *alloc_event_data(पूर्णांक cpu)
अणु
	cpumask_t *mask;
	काष्ठा eपंचांग_event_data *event_data;

	/* First get memory क्रम the session's data */
	event_data = kzalloc(माप(काष्ठा eपंचांग_event_data), GFP_KERNEL);
	अगर (!event_data)
		वापस शून्य;


	mask = &event_data->mask;
	अगर (cpu != -1)
		cpumask_set_cpu(cpu, mask);
	अन्यथा
		cpumask_copy(mask, cpu_present_mask);

	/*
	 * Each CPU has a single path between source and destination.  As such
	 * allocate an array using CPU numbers as indexes.  That way a path
	 * क्रम any CPU can easily be accessed at any given समय.  We proceed
	 * the same way क्रम sessions involving a single CPU.  The cost of
	 * unused memory when dealing with single CPU trace scenarios is small
	 * compared to the cost of searching through an optimized array.
	 */
	event_data->path = alloc_percpu(काष्ठा list_head *);

	अगर (!event_data->path) अणु
		kमुक्त(event_data);
		वापस शून्य;
	पूर्ण

	वापस event_data;
पूर्ण

अटल व्योम eपंचांग_मुक्त_aux(व्योम *data)
अणु
	काष्ठा eपंचांग_event_data *event_data = data;

	schedule_work(&event_data->work);
पूर्ण

/*
 * Check अगर two given sinks are compatible with each other,
 * so that they can use the same sink buffers, when an event
 * moves around.
 */
अटल bool sinks_compatible(काष्ठा coresight_device *a,
			     काष्ठा coresight_device *b)
अणु
	अगर (!a || !b)
		वापस false;
	/*
	 * If the sinks are of the same subtype and driven
	 * by the same driver, we can use the same buffer
	 * on these sinks.
	 */
	वापस (a->subtype.sink_subtype == b->subtype.sink_subtype) &&
	       (sink_ops(a) == sink_ops(b));
पूर्ण

अटल व्योम *eपंचांग_setup_aux(काष्ठा perf_event *event, व्योम **pages,
			   पूर्णांक nr_pages, bool overग_लिखो)
अणु
	u32 id;
	पूर्णांक cpu = event->cpu;
	cpumask_t *mask;
	काष्ठा coresight_device *sink = शून्य;
	काष्ठा coresight_device *user_sink = शून्य, *last_sink = शून्य;
	काष्ठा eपंचांग_event_data *event_data = शून्य;

	event_data = alloc_event_data(cpu);
	अगर (!event_data)
		वापस शून्य;
	INIT_WORK(&event_data->work, मुक्त_event_data);

	/* First get the selected sink from user space. */
	अगर (event->attr.config2) अणु
		id = (u32)event->attr.config2;
		sink = user_sink = coresight_get_sink_by_id(id);
	पूर्ण

	mask = &event_data->mask;

	/*
	 * Setup the path क्रम each CPU in a trace session. We try to build
	 * trace path क्रम each CPU in the mask. If we करोn't find an ETM
	 * क्रम the CPU or fail to build a path, we clear the CPU from the
	 * mask and जारी with the rest. If ever we try to trace on those
	 * CPUs, we can handle it and fail the session.
	 */
	क्रम_each_cpu(cpu, mask) अणु
		काष्ठा list_head *path;
		काष्ठा coresight_device *csdev;

		csdev = per_cpu(csdev_src, cpu);
		/*
		 * If there is no ETM associated with this CPU clear it from
		 * the mask and जारी with the rest. If ever we try to trace
		 * on this CPU, we handle it accordingly.
		 */
		अगर (!csdev) अणु
			cpumask_clear_cpu(cpu, mask);
			जारी;
		पूर्ण

		/*
		 * No sink provided - look क्रम a शेष sink क्रम all the ETMs,
		 * where this event can be scheduled.
		 * We allocate the sink specअगरic buffers only once क्रम this
		 * event. If the ETMs have dअगरferent शेष sink devices, we
		 * can only use a single "type" of sink as the event can carry
		 * only one sink specअगरic buffer. Thus we have to make sure
		 * that the sinks are of the same type and driven by the same
		 * driver, as the one we allocate the buffer क्रम. As such
		 * we choose the first sink and check अगर the reमुख्यing ETMs
		 * have a compatible शेष sink. We करोn't trace on a CPU
		 * अगर the sink is not compatible.
		 */
		अगर (!user_sink) अणु
			/* Find the शेष sink क्रम this ETM */
			sink = coresight_find_शेष_sink(csdev);
			अगर (!sink) अणु
				cpumask_clear_cpu(cpu, mask);
				जारी;
			पूर्ण

			/* Check अगर this sink compatible with the last sink */
			अगर (last_sink && !sinks_compatible(last_sink, sink)) अणु
				cpumask_clear_cpu(cpu, mask);
				जारी;
			पूर्ण
			last_sink = sink;
		पूर्ण

		/*
		 * Building a path करोesn't enable it, it simply builds a
		 * list of devices from source to sink that can be
		 * referenced later when the path is actually needed.
		 */
		path = coresight_build_path(csdev, sink);
		अगर (IS_ERR(path)) अणु
			cpumask_clear_cpu(cpu, mask);
			जारी;
		पूर्ण

		*eपंचांग_event_cpu_path_ptr(event_data, cpu) = path;
	पूर्ण

	/* no sink found क्रम any CPU - cannot trace */
	अगर (!sink)
		जाओ err;

	/* If we करोn't have any CPUs पढ़ोy क्रम tracing, पात */
	cpu = cpumask_first(mask);
	अगर (cpu >= nr_cpu_ids)
		जाओ err;

	अगर (!sink_ops(sink)->alloc_buffer || !sink_ops(sink)->मुक्त_buffer)
		जाओ err;

	/*
	 * Allocate the sink buffer क्रम this session. All the sinks
	 * where this event can be scheduled are ensured to be of the
	 * same type. Thus the same sink configuration is used by the
	 * sinks.
	 */
	event_data->snk_config =
			sink_ops(sink)->alloc_buffer(sink, event, pages,
						     nr_pages, overग_लिखो);
	अगर (!event_data->snk_config)
		जाओ err;

out:
	वापस event_data;

err:
	eपंचांग_मुक्त_aux(event_data);
	event_data = शून्य;
	जाओ out;
पूर्ण

अटल व्योम eपंचांग_event_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	पूर्णांक cpu = smp_processor_id();
	काष्ठा eपंचांग_event_data *event_data;
	काष्ठा eपंचांग_ctxt *ctxt = this_cpu_ptr(&eपंचांग_ctxt);
	काष्ठा perf_output_handle *handle = &ctxt->handle;
	काष्ठा coresight_device *sink, *csdev = per_cpu(csdev_src, cpu);
	काष्ठा list_head *path;

	अगर (!csdev)
		जाओ fail;

	/* Have we messed up our tracking ? */
	अगर (WARN_ON(ctxt->event_data))
		जाओ fail;

	/*
	 * Deal with the ring buffer API and get a handle on the
	 * session's inक्रमmation.
	 */
	event_data = perf_aux_output_begin(handle, event);
	अगर (!event_data)
		जाओ fail;

	/*
	 * Check अगर this ETM is allowed to trace, as decided
	 * at eपंचांग_setup_aux(). This could be due to an unreachable
	 * sink from this ETM. We can't करो much in this हाल अगर
	 * the sink was specअगरied or hपूर्णांकed to the driver. For
	 * now, simply करोn't record anything on this ETM.
	 */
	अगर (!cpumask_test_cpu(cpu, &event_data->mask))
		जाओ fail_end_stop;

	path = eपंचांग_event_cpu_path(event_data, cpu);
	/* We need a sink, no need to जारी without one */
	sink = coresight_get_sink(path);
	अगर (WARN_ON_ONCE(!sink))
		जाओ fail_end_stop;

	/* Nothing will happen without a path */
	अगर (coresight_enable_path(path, CS_MODE_PERF, handle))
		जाओ fail_end_stop;

	/* Tell the perf core the event is alive */
	event->hw.state = 0;

	/* Finally enable the tracer */
	अगर (source_ops(csdev)->enable(csdev, event, CS_MODE_PERF))
		जाओ fail_disable_path;

	/* Save the event_data क्रम this ETM */
	ctxt->event_data = event_data;
out:
	वापस;

fail_disable_path:
	coresight_disable_path(path);
fail_end_stop:
	perf_aux_output_flag(handle, PERF_AUX_FLAG_TRUNCATED);
	perf_aux_output_end(handle, 0);
fail:
	event->hw.state = PERF_HES_STOPPED;
	जाओ out;
पूर्ण

अटल व्योम eपंचांग_event_stop(काष्ठा perf_event *event, पूर्णांक mode)
अणु
	पूर्णांक cpu = smp_processor_id();
	अचिन्हित दीर्घ size;
	काष्ठा coresight_device *sink, *csdev = per_cpu(csdev_src, cpu);
	काष्ठा eपंचांग_ctxt *ctxt = this_cpu_ptr(&eपंचांग_ctxt);
	काष्ठा perf_output_handle *handle = &ctxt->handle;
	काष्ठा eपंचांग_event_data *event_data;
	काष्ठा list_head *path;

	/*
	 * If we still have access to the event_data via handle,
	 * confirm that we haven't messed up the tracking.
	 */
	अगर (handle->event &&
	    WARN_ON(perf_get_aux(handle) != ctxt->event_data))
		वापस;

	event_data = ctxt->event_data;
	/* Clear the event_data as this ETM is stopping the trace. */
	ctxt->event_data = शून्य;

	अगर (event->hw.state == PERF_HES_STOPPED)
		वापस;

	/* We must have a valid event_data क्रम a running event */
	अगर (WARN_ON(!event_data))
		वापस;

	अगर (!csdev)
		वापस;

	path = eपंचांग_event_cpu_path(event_data, cpu);
	अगर (!path)
		वापस;

	sink = coresight_get_sink(path);
	अगर (!sink)
		वापस;

	/* stop tracer */
	source_ops(csdev)->disable(csdev, event);

	/* tell the core */
	event->hw.state = PERF_HES_STOPPED;

	/*
	 * If the handle is not bound to an event anymore
	 * (e.g, the sink driver was unable to restart the
	 * handle due to lack of buffer space), we करोn't
	 * have to करो anything here.
	 */
	अगर (handle->event && (mode & PERF_EF_UPDATE)) अणु
		अगर (WARN_ON_ONCE(handle->event != event))
			वापस;

		/* update trace inक्रमmation */
		अगर (!sink_ops(sink)->update_buffer)
			वापस;

		size = sink_ops(sink)->update_buffer(sink, handle,
					      event_data->snk_config);
		perf_aux_output_end(handle, size);
	पूर्ण

	/* Disabling the path make its elements available to other sessions */
	coresight_disable_path(path);
पूर्ण

अटल पूर्णांक eपंचांग_event_add(काष्ठा perf_event *event, पूर्णांक mode)
अणु
	पूर्णांक ret = 0;
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (mode & PERF_EF_START) अणु
		eपंचांग_event_start(event, 0);
		अगर (hwc->state & PERF_HES_STOPPED)
			ret = -EINVAL;
	पूर्ण अन्यथा अणु
		hwc->state = PERF_HES_STOPPED;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम eपंचांग_event_del(काष्ठा perf_event *event, पूर्णांक mode)
अणु
	eपंचांग_event_stop(event, PERF_EF_UPDATE);
पूर्ण

अटल पूर्णांक eपंचांग_addr_filters_validate(काष्ठा list_head *filters)
अणु
	bool range = false, address = false;
	पूर्णांक index = 0;
	काष्ठा perf_addr_filter *filter;

	list_क्रम_each_entry(filter, filters, entry) अणु
		/*
		 * No need to go further अगर there's no more
		 * room क्रम filters.
		 */
		अगर (++index > ETM_ADDR_CMP_MAX)
			वापस -EOPNOTSUPP;

		/* filter::size==0 means single address trigger */
		अगर (filter->size) अणु
			/*
			 * The existing code relies on START/STOP filters
			 * being address filters.
			 */
			अगर (filter->action == PERF_ADDR_FILTER_ACTION_START ||
			    filter->action == PERF_ADDR_FILTER_ACTION_STOP)
				वापस -EOPNOTSUPP;

			range = true;
		पूर्ण अन्यथा
			address = true;

		/*
		 * At this समय we करोn't allow range and start/stop filtering
		 * to cohabitate, they have to be mutually exclusive.
		 */
		अगर (range && address)
			वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम eपंचांग_addr_filters_sync(काष्ठा perf_event *event)
अणु
	काष्ठा perf_addr_filters_head *head = perf_event_addr_filters(event);
	अचिन्हित दीर्घ start, stop;
	काष्ठा perf_addr_filter_range *fr = event->addr_filter_ranges;
	काष्ठा eपंचांग_filters *filters = event->hw.addr_filters;
	काष्ठा eपंचांग_filter *eपंचांग_filter;
	काष्ठा perf_addr_filter *filter;
	पूर्णांक i = 0;

	list_क्रम_each_entry(filter, &head->list, entry) अणु
		start = fr[i].start;
		stop = start + fr[i].size;
		eपंचांग_filter = &filters->eपंचांग_filter[i];

		चयन (filter->action) अणु
		हाल PERF_ADDR_FILTER_ACTION_FILTER:
			eपंचांग_filter->start_addr = start;
			eपंचांग_filter->stop_addr = stop;
			eपंचांग_filter->type = ETM_ADDR_TYPE_RANGE;
			अवरोध;
		हाल PERF_ADDR_FILTER_ACTION_START:
			eपंचांग_filter->start_addr = start;
			eपंचांग_filter->type = ETM_ADDR_TYPE_START;
			अवरोध;
		हाल PERF_ADDR_FILTER_ACTION_STOP:
			eपंचांग_filter->stop_addr = stop;
			eपंचांग_filter->type = ETM_ADDR_TYPE_STOP;
			अवरोध;
		पूर्ण
		i++;
	पूर्ण

	filters->nr_filters = i;
पूर्ण

पूर्णांक eपंचांग_perf_symlink(काष्ठा coresight_device *csdev, bool link)
अणु
	अक्षर entry[माप("cpu9999999")];
	पूर्णांक ret = 0, cpu = source_ops(csdev)->cpu_id(csdev);
	काष्ठा device *pmu_dev = eपंचांग_pmu.dev;
	काष्ठा device *cs_dev = &csdev->dev;

	प्र_लिखो(entry, "cpu%d", cpu);

	अगर (!eपंचांग_perf_up)
		वापस -EPROBE_DEFER;

	अगर (link) अणु
		ret = sysfs_create_link(&pmu_dev->kobj, &cs_dev->kobj, entry);
		अगर (ret)
			वापस ret;
		per_cpu(csdev_src, cpu) = csdev;
	पूर्ण अन्यथा अणु
		sysfs_हटाओ_link(&pmu_dev->kobj, entry);
		per_cpu(csdev_src, cpu) = शून्य;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(eपंचांग_perf_symlink);

अटल sमाप_प्रकार eपंचांग_perf_sink_name_show(काष्ठा device *dev,
				       काष्ठा device_attribute *dattr,
				       अक्षर *buf)
अणु
	काष्ठा dev_ext_attribute *ea;

	ea = container_of(dattr, काष्ठा dev_ext_attribute, attr);
	वापस scnम_लिखो(buf, PAGE_SIZE, "0x%lx\n", (अचिन्हित दीर्घ)(ea->var));
पूर्ण

पूर्णांक eपंचांग_perf_add_symlink_sink(काष्ठा coresight_device *csdev)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ hash;
	स्थिर अक्षर *name;
	काष्ठा device *pmu_dev = eपंचांग_pmu.dev;
	काष्ठा device *dev = &csdev->dev;
	काष्ठा dev_ext_attribute *ea;

	अगर (csdev->type != CORESIGHT_DEV_TYPE_SINK &&
	    csdev->type != CORESIGHT_DEV_TYPE_LINKSINK)
		वापस -EINVAL;

	अगर (csdev->ea != शून्य)
		वापस -EINVAL;

	अगर (!eपंचांग_perf_up)
		वापस -EPROBE_DEFER;

	ea = devm_kzalloc(dev, माप(*ea), GFP_KERNEL);
	अगर (!ea)
		वापस -ENOMEM;

	name = dev_name(dev);
	/* See function coresight_get_sink_by_id() to know where this is used */
	hash = hashlen_hash(hashlen_string(शून्य, name));

	sysfs_attr_init(&ea->attr.attr);
	ea->attr.attr.name = devm_kstrdup(dev, name, GFP_KERNEL);
	अगर (!ea->attr.attr.name)
		वापस -ENOMEM;

	ea->attr.attr.mode = 0444;
	ea->attr.show = eपंचांग_perf_sink_name_show;
	ea->var = (अचिन्हित दीर्घ *)hash;

	ret = sysfs_add_file_to_group(&pmu_dev->kobj,
				      &ea->attr.attr, "sinks");

	अगर (!ret)
		csdev->ea = ea;

	वापस ret;
पूर्ण

व्योम eपंचांग_perf_del_symlink_sink(काष्ठा coresight_device *csdev)
अणु
	काष्ठा device *pmu_dev = eपंचांग_pmu.dev;
	काष्ठा dev_ext_attribute *ea = csdev->ea;

	अगर (csdev->type != CORESIGHT_DEV_TYPE_SINK &&
	    csdev->type != CORESIGHT_DEV_TYPE_LINKSINK)
		वापस;

	अगर (!ea)
		वापस;

	sysfs_हटाओ_file_from_group(&pmu_dev->kobj,
				     &ea->attr.attr, "sinks");
	csdev->ea = शून्य;
पूर्ण

पूर्णांक __init eपंचांग_perf_init(व्योम)
अणु
	पूर्णांक ret;

	eपंचांग_pmu.capabilities		= (PERF_PMU_CAP_EXCLUSIVE |
					   PERF_PMU_CAP_ITRACE);

	eपंचांग_pmu.attr_groups		= eपंचांग_pmu_attr_groups;
	eपंचांग_pmu.task_ctx_nr		= perf_sw_context;
	eपंचांग_pmu.पढ़ो			= eपंचांग_event_पढ़ो;
	eपंचांग_pmu.event_init		= eपंचांग_event_init;
	eपंचांग_pmu.setup_aux		= eपंचांग_setup_aux;
	eपंचांग_pmu.मुक्त_aux		= eपंचांग_मुक्त_aux;
	eपंचांग_pmu.start			= eपंचांग_event_start;
	eपंचांग_pmu.stop			= eपंचांग_event_stop;
	eपंचांग_pmu.add			= eपंचांग_event_add;
	eपंचांग_pmu.del			= eपंचांग_event_del;
	eपंचांग_pmu.addr_filters_sync	= eपंचांग_addr_filters_sync;
	eपंचांग_pmu.addr_filters_validate	= eपंचांग_addr_filters_validate;
	eपंचांग_pmu.nr_addr_filters		= ETM_ADDR_CMP_MAX;

	ret = perf_pmu_रेजिस्टर(&eपंचांग_pmu, CORESIGHT_ETM_PMU_NAME, -1);
	अगर (ret == 0)
		eपंचांग_perf_up = true;

	वापस ret;
पूर्ण

व्योम __निकास eपंचांग_perf_निकास(व्योम)
अणु
	perf_pmu_unरेजिस्टर(&eपंचांग_pmu);
पूर्ण
