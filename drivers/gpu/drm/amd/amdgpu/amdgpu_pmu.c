<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#समावेश <linux/perf_event.h>
#समावेश <linux/init.h>
#समावेश "amdgpu.h"
#समावेश "amdgpu_pmu.h"

#घोषणा PMU_NAME_SIZE 32
#घोषणा NUM_FORMATS_AMDGPU_PMU		4
#घोषणा NUM_FORMATS_DF_VEGA20		3
#घोषणा NUM_EVENTS_DF_VEGA20		8
#घोषणा NUM_EVENT_TYPES_VEGA20		1
#घोषणा NUM_EVENTS_VEGA20_XGMI		2
#घोषणा NUM_EVENTS_VEGA20_MAX		NUM_EVENTS_VEGA20_XGMI
#घोषणा NUM_EVENT_TYPES_ARCTURUS	1
#घोषणा NUM_EVENTS_ARCTURUS_XGMI	6
#घोषणा NUM_EVENTS_ARCTURUS_MAX		NUM_EVENTS_ARCTURUS_XGMI

काष्ठा amdgpu_pmu_event_attribute अणु
	काष्ठा device_attribute attr;
	स्थिर अक्षर *event_str;
	अचिन्हित पूर्णांक type;
पूर्ण;

/* record to keep track of pmu entry per pmu type per device */
काष्ठा amdgpu_pmu_entry अणु
	काष्ठा list_head entry;
	काष्ठा amdgpu_device *adev;
	काष्ठा pmu pmu;
	अचिन्हित पूर्णांक pmu_perf_type;
	अक्षर *pmu_type_name;
	अक्षर *pmu_file_prefix;
	काष्ठा attribute_group fmt_attr_group;
	काष्ठा amdgpu_pmu_event_attribute *fmt_attr;
	काष्ठा attribute_group evt_attr_group;
	काष्ठा amdgpu_pmu_event_attribute *evt_attr;
पूर्ण;

अटल sमाप_प्रकार amdgpu_pmu_event_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा amdgpu_pmu_event_attribute *amdgpu_pmu_attr;

	amdgpu_pmu_attr = container_of(attr, काष्ठा amdgpu_pmu_event_attribute,
									attr);

	अगर (!amdgpu_pmu_attr->type)
		वापस प्र_लिखो(buf, "%s\n", amdgpu_pmu_attr->event_str);

	वापस प्र_लिखो(buf, "%s,type=0x%x\n",
			amdgpu_pmu_attr->event_str, amdgpu_pmu_attr->type);
पूर्ण

अटल LIST_HEAD(amdgpu_pmu_list);


काष्ठा amdgpu_pmu_attr अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *config;
पूर्ण;

काष्ठा amdgpu_pmu_type अणु
	स्थिर अचिन्हित पूर्णांक type;
	स्थिर अचिन्हित पूर्णांक num_of_type;
पूर्ण;

काष्ठा amdgpu_pmu_config अणु
	काष्ठा amdgpu_pmu_attr *क्रमmats;
	अचिन्हित पूर्णांक num_क्रमmats;
	काष्ठा amdgpu_pmu_attr *events;
	अचिन्हित पूर्णांक num_events;
	काष्ठा amdgpu_pmu_type *types;
	अचिन्हित पूर्णांक num_types;
पूर्ण;

/*
 * Events fall under two categories:
 *  - PMU typed
 *    Events in /sys/bus/event_source/devices/amdgpu_<pmu_type>_<dev_num> have
 *    perक्रमmance counter operations handled by one IP <pmu_type>.  Formats and
 *    events should be defined by <pmu_type>_<asic_type>_क्रमmats and
 *    <pmu_type>_<asic_type>_events respectively.
 *
 *  - Event config typed
 *    Events in /sys/bus/event_source/devices/amdgpu_<dev_num> have perक्रमmance
 *    counter operations that can be handled by multiple IPs dictated by their
 *    "type" क्रमmat field.  Formats and events should be defined by
 *    amdgpu_pmu_क्रमmats and <asic_type>_events respectively.  Format field
 *    "type" is generated in amdgpu_pmu_event_show and defined in
 *    <asic_type>_event_config_types.
 */

अटल काष्ठा amdgpu_pmu_attr amdgpu_pmu_क्रमmats[NUM_FORMATS_AMDGPU_PMU] = अणु
	अणु .name = "event", .config = "config:0-7" पूर्ण,
	अणु .name = "instance", .config = "config:8-15" पूर्ण,
	अणु .name = "umask", .config = "config:16-23"पूर्ण,
	अणु .name = "type", .config = "config:56-63"पूर्ण
पूर्ण;

/* Vega20 events */
अटल काष्ठा amdgpu_pmu_attr vega20_events[NUM_EVENTS_VEGA20_MAX] = अणु
	अणु .name = "xgmi_link0_data_outbound",
			.config = "event=0x7,instance=0x46,umask=0x2" पूर्ण,
	अणु .name = "xgmi_link1_data_outbound",
			.config = "event=0x7,instance=0x47,umask=0x2" पूर्ण
पूर्ण;

अटल काष्ठा amdgpu_pmu_type vega20_types[NUM_EVENT_TYPES_VEGA20] = अणु
	अणु .type = AMDGPU_PMU_EVENT_CONFIG_TYPE_XGMI,
					.num_of_type = NUM_EVENTS_VEGA20_XGMI पूर्ण
पूर्ण;

अटल काष्ठा amdgpu_pmu_config vega20_config = अणु
	.क्रमmats = amdgpu_pmu_क्रमmats,
	.num_क्रमmats = ARRAY_SIZE(amdgpu_pmu_क्रमmats),
	.events = vega20_events,
	.num_events = ARRAY_SIZE(vega20_events),
	.types = vega20_types,
	.num_types = ARRAY_SIZE(vega20_types)
पूर्ण;

/* Vega20 data fabric (DF) events */
अटल काष्ठा amdgpu_pmu_attr df_vega20_क्रमmats[NUM_FORMATS_DF_VEGA20] = अणु
	अणु .name = "event", .config = "config:0-7" पूर्ण,
	अणु .name = "instance", .config = "config:8-15" पूर्ण,
	अणु .name = "umask", .config = "config:16-23"पूर्ण
पूर्ण;

अटल काष्ठा amdgpu_pmu_attr df_vega20_events[NUM_EVENTS_DF_VEGA20] = अणु
	अणु .name = "cake0_pcsout_txdata",
			.config = "event=0x7,instance=0x46,umask=0x2" पूर्ण,
	अणु .name = "cake1_pcsout_txdata",
			.config = "event=0x7,instance=0x47,umask=0x2" पूर्ण,
	अणु .name = "cake0_pcsout_txmeta",
			.config = "event=0x7,instance=0x46,umask=0x4" पूर्ण,
	अणु .name = "cake1_pcsout_txmeta",
			.config = "event=0x7,instance=0x47,umask=0x4" पूर्ण,
	अणु .name = "cake0_ftiinstat_reqalloc",
			.config = "event=0xb,instance=0x46,umask=0x4" पूर्ण,
	अणु .name = "cake1_ftiinstat_reqalloc",
			.config = "event=0xb,instance=0x47,umask=0x4" पूर्ण,
	अणु .name = "cake0_ftiinstat_rspalloc",
			.config = "event=0xb,instance=0x46,umask=0x8" पूर्ण,
	अणु .name = "cake1_ftiinstat_rspalloc",
			.config = "event=0xb,instance=0x47,umask=0x8" पूर्ण
पूर्ण;

अटल काष्ठा amdgpu_pmu_config df_vega20_config = अणु
	.क्रमmats = df_vega20_क्रमmats,
	.num_क्रमmats = ARRAY_SIZE(df_vega20_क्रमmats),
	.events = df_vega20_events,
	.num_events = ARRAY_SIZE(df_vega20_events),
	.types = शून्य,
	.num_types = 0
पूर्ण;

/* Arcturus events */
अटल काष्ठा amdgpu_pmu_attr arcturus_events[NUM_EVENTS_ARCTURUS_MAX] = अणु
	अणु .name = "xgmi_link0_data_outbound",
			.config = "event=0x7,instance=0x4b,umask=0x2" पूर्ण,
	अणु .name = "xgmi_link1_data_outbound",
			.config = "event=0x7,instance=0x4c,umask=0x2" पूर्ण,
	अणु .name = "xgmi_link2_data_outbound",
			.config = "event=0x7,instance=0x4d,umask=0x2" पूर्ण,
	अणु .name = "xgmi_link3_data_outbound",
			.config = "event=0x7,instance=0x4e,umask=0x2" पूर्ण,
	अणु .name = "xgmi_link4_data_outbound",
			.config = "event=0x7,instance=0x4f,umask=0x2" पूर्ण,
	अणु .name = "xgmi_link5_data_outbound",
			.config = "event=0x7,instance=0x50,umask=0x2" पूर्ण
पूर्ण;

अटल काष्ठा amdgpu_pmu_type arcturus_types[NUM_EVENT_TYPES_ARCTURUS] = अणु
	अणु .type = AMDGPU_PMU_EVENT_CONFIG_TYPE_XGMI,
				.num_of_type = NUM_EVENTS_ARCTURUS_XGMI पूर्ण
पूर्ण;

अटल काष्ठा amdgpu_pmu_config arcturus_config = अणु
	.क्रमmats = amdgpu_pmu_क्रमmats,
	.num_क्रमmats = ARRAY_SIZE(amdgpu_pmu_क्रमmats),
	.events = arcturus_events,
	.num_events = ARRAY_SIZE(arcturus_events),
	.types = arcturus_types,
	.num_types = ARRAY_SIZE(arcturus_types)
पूर्ण;

/* initialize perf counter */
अटल पूर्णांक amdgpu_perf_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	/* test the event attr type check क्रम PMU क्रमागतeration */
	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	/* update the hw_perf_event काष्ठा with config data */
	hwc->config = event->attr.config;
	hwc->config_base = AMDGPU_PMU_PERF_TYPE_NONE;

	वापस 0;
पूर्ण

/* start perf counter */
अटल व्योम amdgpu_perf_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा amdgpu_pmu_entry *pe = container_of(event->pmu,
						  काष्ठा amdgpu_pmu_entry,
						  pmu);
	पूर्णांक target_cntr = 0;

	अगर (WARN_ON_ONCE(!(hwc->state & PERF_HES_STOPPED)))
		वापस;

	WARN_ON_ONCE(!(hwc->state & PERF_HES_UPTODATE));
	hwc->state = 0;

	चयन (hwc->config_base) अणु
	हाल AMDGPU_PMU_EVENT_CONFIG_TYPE_DF:
	हाल AMDGPU_PMU_EVENT_CONFIG_TYPE_XGMI:
		अगर (!(flags & PERF_EF_RELOAD)) अणु
			target_cntr = pe->adev->df.funcs->pmc_start(pe->adev,
						hwc->config, 0 /* unused */,
						1 /* add counter */);
			अगर (target_cntr < 0)
				अवरोध;

			hwc->idx = target_cntr;
		पूर्ण

		pe->adev->df.funcs->pmc_start(pe->adev, hwc->config,
								hwc->idx, 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	perf_event_update_userpage(event);
पूर्ण

/* पढ़ो perf counter */
अटल व्योम amdgpu_perf_पढ़ो(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा amdgpu_pmu_entry *pe = container_of(event->pmu,
						  काष्ठा amdgpu_pmu_entry,
						  pmu);
	u64 count, prev;

	करो अणु
		prev = local64_पढ़ो(&hwc->prev_count);

		चयन (hwc->config_base) अणु
		हाल AMDGPU_PMU_EVENT_CONFIG_TYPE_DF:
		हाल AMDGPU_PMU_EVENT_CONFIG_TYPE_XGMI:
			pe->adev->df.funcs->pmc_get_count(pe->adev,
						hwc->config, hwc->idx, &count);
			अवरोध;
		शेष:
			count = 0;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (local64_cmpxchg(&hwc->prev_count, prev, count) != prev);

	local64_add(count - prev, &event->count);
पूर्ण

/* stop perf counter */
अटल व्योम amdgpu_perf_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा amdgpu_pmu_entry *pe = container_of(event->pmu,
						  काष्ठा amdgpu_pmu_entry,
						  pmu);

	अगर (hwc->state & PERF_HES_UPTODATE)
		वापस;

	चयन (hwc->config_base) अणु
	हाल AMDGPU_PMU_EVENT_CONFIG_TYPE_DF:
	हाल AMDGPU_PMU_EVENT_CONFIG_TYPE_XGMI:
		pe->adev->df.funcs->pmc_stop(pe->adev, hwc->config, hwc->idx,
									0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	WARN_ON_ONCE(hwc->state & PERF_HES_STOPPED);
	hwc->state |= PERF_HES_STOPPED;

	अगर (hwc->state & PERF_HES_UPTODATE)
		वापस;

	amdgpu_perf_पढ़ो(event);
	hwc->state |= PERF_HES_UPTODATE;
पूर्ण

/* add perf counter */
अटल पूर्णांक amdgpu_perf_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक retval = 0, target_cntr;
	काष्ठा amdgpu_pmu_entry *pe = container_of(event->pmu,
						  काष्ठा amdgpu_pmu_entry,
						  pmu);

	चयन (pe->pmu_perf_type) अणु
	हाल AMDGPU_PMU_PERF_TYPE_DF:
		hwc->config_base = AMDGPU_PMU_EVENT_CONFIG_TYPE_DF;
		अवरोध;
	हाल AMDGPU_PMU_PERF_TYPE_ALL:
		hwc->config_base = (hwc->config >>
					AMDGPU_PMU_EVENT_CONFIG_TYPE_SHIFT) &
					AMDGPU_PMU_EVENT_CONFIG_TYPE_MASK;
		अवरोध;
	पूर्ण

	event->hw.state = PERF_HES_UPTODATE | PERF_HES_STOPPED;

	चयन (hwc->config_base) अणु
	हाल AMDGPU_PMU_EVENT_CONFIG_TYPE_DF:
	हाल AMDGPU_PMU_EVENT_CONFIG_TYPE_XGMI:
		target_cntr = pe->adev->df.funcs->pmc_start(pe->adev,
						hwc->config, 0 /* unused */,
						1 /* add counter */);
		अगर (target_cntr < 0)
			retval = target_cntr;
		अन्यथा
			hwc->idx = target_cntr;

		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (retval)
		वापस retval;

	अगर (flags & PERF_EF_START)
		amdgpu_perf_start(event, PERF_EF_RELOAD);

	वापस retval;
पूर्ण

/* delete perf counter  */
अटल व्योम amdgpu_perf_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा amdgpu_pmu_entry *pe = container_of(event->pmu,
						  काष्ठा amdgpu_pmu_entry,
						  pmu);

	amdgpu_perf_stop(event, PERF_EF_UPDATE);

	चयन (hwc->config_base) अणु
	हाल AMDGPU_PMU_EVENT_CONFIG_TYPE_DF:
	हाल AMDGPU_PMU_EVENT_CONFIG_TYPE_XGMI:
		pe->adev->df.funcs->pmc_stop(pe->adev, hwc->config, hwc->idx,
									1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	perf_event_update_userpage(event);
पूर्ण

अटल व्योम amdgpu_pmu_create_event_attrs_by_type(
				काष्ठा attribute_group *attr_group,
				काष्ठा amdgpu_pmu_event_attribute *pmu_attr,
				काष्ठा amdgpu_pmu_attr events[],
				पूर्णांक s_offset,
				पूर्णांक e_offset,
				अचिन्हित पूर्णांक type)
अणु
	पूर्णांक i;

	pmu_attr += s_offset;

	क्रम (i = s_offset; i < e_offset; i++) अणु
		attr_group->attrs[i] = &pmu_attr->attr.attr;
		sysfs_attr_init(&pmu_attr->attr.attr);
		pmu_attr->attr.attr.name = events[i].name;
		pmu_attr->attr.attr.mode = 0444;
		pmu_attr->attr.show = amdgpu_pmu_event_show;
		pmu_attr->event_str = events[i].config;
		pmu_attr->type = type;
		pmu_attr++;
	पूर्ण
पूर्ण

अटल व्योम amdgpu_pmu_create_attrs(काष्ठा attribute_group *attr_group,
				काष्ठा amdgpu_pmu_event_attribute *pmu_attr,
				काष्ठा amdgpu_pmu_attr events[],
				पूर्णांक num_events)
अणु
	amdgpu_pmu_create_event_attrs_by_type(attr_group, pmu_attr, events, 0,
				num_events, AMDGPU_PMU_EVENT_CONFIG_TYPE_NONE);
पूर्ण


अटल पूर्णांक amdgpu_pmu_alloc_pmu_attrs(
				काष्ठा attribute_group *fmt_attr_group,
				काष्ठा amdgpu_pmu_event_attribute **fmt_attr,
				काष्ठा attribute_group *evt_attr_group,
				काष्ठा amdgpu_pmu_event_attribute **evt_attr,
				काष्ठा amdgpu_pmu_config *config)
अणु
	*fmt_attr = kसुस्मृति(config->num_क्रमmats, माप(**fmt_attr),
								GFP_KERNEL);

	अगर (!(*fmt_attr))
		वापस -ENOMEM;

	fmt_attr_group->attrs = kसुस्मृति(config->num_क्रमmats + 1,
				माप(*fmt_attr_group->attrs), GFP_KERNEL);

	अगर (!fmt_attr_group->attrs)
		जाओ err_fmt_attr_grp;

	*evt_attr = kसुस्मृति(config->num_events, माप(**evt_attr), GFP_KERNEL);

	अगर (!(*evt_attr))
		जाओ err_evt_attr;

	evt_attr_group->attrs = kसुस्मृति(config->num_events + 1,
				माप(*evt_attr_group->attrs), GFP_KERNEL);

	अगर (!evt_attr_group->attrs)
		जाओ err_evt_attr_grp;

	वापस 0;
err_evt_attr_grp:
	kमुक्त(*evt_attr);
err_evt_attr:
	kमुक्त(fmt_attr_group->attrs);
err_fmt_attr_grp:
	kमुक्त(*fmt_attr);
	वापस -ENOMEM;
पूर्ण

/* init pmu tracking per pmu type */
अटल पूर्णांक init_pmu_entry_by_type_and_add(काष्ठा amdgpu_pmu_entry *pmu_entry,
			काष्ठा amdgpu_pmu_config *config)
अणु
	स्थिर काष्ठा attribute_group *attr_groups[] = अणु
		&pmu_entry->fmt_attr_group,
		&pmu_entry->evt_attr_group,
		शून्य
	पूर्ण;
	अक्षर pmu_name[PMU_NAME_SIZE];
	पूर्णांक ret = 0, total_num_events = 0;

	pmu_entry->pmu = (काष्ठा pmu)अणु
		.event_init = amdgpu_perf_event_init,
		.add = amdgpu_perf_add,
		.del = amdgpu_perf_del,
		.start = amdgpu_perf_start,
		.stop = amdgpu_perf_stop,
		.पढ़ो = amdgpu_perf_पढ़ो,
		.task_ctx_nr = perf_invalid_context,
	पूर्ण;

	ret = amdgpu_pmu_alloc_pmu_attrs(&pmu_entry->fmt_attr_group,
					&pmu_entry->fmt_attr,
					&pmu_entry->evt_attr_group,
					&pmu_entry->evt_attr,
					config);

	अगर (ret)
		जाओ err_out;

	amdgpu_pmu_create_attrs(&pmu_entry->fmt_attr_group, pmu_entry->fmt_attr,
					config->क्रमmats, config->num_क्रमmats);

	अगर (pmu_entry->pmu_perf_type == AMDGPU_PMU_PERF_TYPE_ALL) अणु
		पूर्णांक i;

		क्रम (i = 0; i < config->num_types; i++) अणु
			amdgpu_pmu_create_event_attrs_by_type(
					&pmu_entry->evt_attr_group,
					pmu_entry->evt_attr,
					config->events,
					total_num_events,
					total_num_events +
						config->types[i].num_of_type,
					config->types[i].type);
			total_num_events += config->types[i].num_of_type;
		पूर्ण
	पूर्ण अन्यथा अणु
		amdgpu_pmu_create_attrs(&pmu_entry->evt_attr_group,
					pmu_entry->evt_attr,
					config->events, config->num_events);
		total_num_events = config->num_events;
	पूर्ण

	pmu_entry->pmu.attr_groups = kmemdup(attr_groups, माप(attr_groups),
								GFP_KERNEL);

	अगर (!pmu_entry->pmu.attr_groups) अणु
		ret = -ENOMEM;
		जाओ err_attr_group;
	पूर्ण

	snम_लिखो(pmu_name, PMU_NAME_SIZE, "%s_%d", pmu_entry->pmu_file_prefix,
				adev_to_drm(pmu_entry->adev)->primary->index);

	ret = perf_pmu_रेजिस्टर(&pmu_entry->pmu, pmu_name, -1);

	अगर (ret)
		जाओ err_रेजिस्टर;

	अगर (pmu_entry->pmu_perf_type != AMDGPU_PMU_PERF_TYPE_ALL)
		pr_info("Detected AMDGPU %s Counters. # of Counters = %d.\n",
				pmu_entry->pmu_type_name, total_num_events);
	अन्यथा
		pr_info("Detected AMDGPU %d Perf Events.\n", total_num_events);


	list_add_tail(&pmu_entry->entry, &amdgpu_pmu_list);

	वापस 0;
err_रेजिस्टर:
	kमुक्त(pmu_entry->pmu.attr_groups);
err_attr_group:
	kमुक्त(pmu_entry->fmt_attr_group.attrs);
	kमुक्त(pmu_entry->fmt_attr);
	kमुक्त(pmu_entry->evt_attr_group.attrs);
	kमुक्त(pmu_entry->evt_attr);
err_out:
	pr_warn("Error initializing AMDGPU %s PMUs.\n",
						pmu_entry->pmu_type_name);
	वापस ret;
पूर्ण

/* destroy all pmu data associated with target device */
व्योम amdgpu_pmu_fini(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_pmu_entry *pe, *temp;

	list_क्रम_each_entry_safe(pe, temp, &amdgpu_pmu_list, entry) अणु
		अगर (pe->adev != adev)
			जारी;
		list_del(&pe->entry);
		perf_pmu_unरेजिस्टर(&pe->pmu);
		kमुक्त(pe->pmu.attr_groups);
		kमुक्त(pe->fmt_attr_group.attrs);
		kमुक्त(pe->fmt_attr);
		kमुक्त(pe->evt_attr_group.attrs);
		kमुक्त(pe->evt_attr);
		kमुक्त(pe);
	पूर्ण
पूर्ण

अटल काष्ठा amdgpu_pmu_entry *create_pmu_entry(काष्ठा amdgpu_device *adev,
						अचिन्हित पूर्णांक pmu_type,
						अक्षर *pmu_type_name,
						अक्षर *pmu_file_prefix)
अणु
	काष्ठा amdgpu_pmu_entry *pmu_entry;

	pmu_entry = kzalloc(माप(काष्ठा amdgpu_pmu_entry), GFP_KERNEL);

	अगर (!pmu_entry)
		वापस pmu_entry;

	pmu_entry->adev = adev;
	pmu_entry->fmt_attr_group.name = "format";
	pmu_entry->fmt_attr_group.attrs = शून्य;
	pmu_entry->evt_attr_group.name = "events";
	pmu_entry->evt_attr_group.attrs = शून्य;
	pmu_entry->pmu_perf_type = pmu_type;
	pmu_entry->pmu_type_name = pmu_type_name;
	pmu_entry->pmu_file_prefix = pmu_file_prefix;

	वापस pmu_entry;
पूर्ण

/* init amdgpu_pmu */
पूर्णांक amdgpu_pmu_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक ret = 0;
	काष्ठा amdgpu_pmu_entry *pmu_entry, *pmu_entry_df;

	चयन (adev->asic_type) अणु
	हाल CHIP_VEGA20:
		pmu_entry_df = create_pmu_entry(adev, AMDGPU_PMU_PERF_TYPE_DF,
						"DF", "amdgpu_df");

		अगर (!pmu_entry_df)
			वापस -ENOMEM;

		ret = init_pmu_entry_by_type_and_add(pmu_entry_df,
							&df_vega20_config);

		अगर (ret) अणु
			kमुक्त(pmu_entry_df);
			वापस ret;
		पूर्ण

		pmu_entry = create_pmu_entry(adev, AMDGPU_PMU_PERF_TYPE_ALL,
						"", "amdgpu");

		अगर (!pmu_entry) अणु
			amdgpu_pmu_fini(adev);
			वापस -ENOMEM;
		पूर्ण

		ret = init_pmu_entry_by_type_and_add(pmu_entry,
							&vega20_config);

		अगर (ret) अणु
			kमुक्त(pmu_entry);
			amdgpu_pmu_fini(adev);
			वापस ret;
		पूर्ण

		अवरोध;
	हाल CHIP_ARCTURUS:
		pmu_entry = create_pmu_entry(adev, AMDGPU_PMU_PERF_TYPE_ALL,
						"", "amdgpu");
		अगर (!pmu_entry)
			वापस -ENOMEM;

		ret = init_pmu_entry_by_type_and_add(pmu_entry,
							&arcturus_config);

		अगर (ret) अणु
			kमुक्त(pmu_entry);
			वापस -ENOMEM;
		पूर्ण

		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस ret;
पूर्ण
