<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hypervisor supplied "24x7" perक्रमmance counter support
 *
 * Author: Cody P Schafer <cody@linux.vnet.ibm.com>
 * Copyright 2014 IBM Corporation.
 */

#घोषणा pr_fmt(fmt) "hv-24x7: " fmt

#समावेश <linux/perf_event.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/byteorder/generic.h>

#समावेश <यंत्र/rtas.h>
#समावेश "hv-24x7.h"
#समावेश "hv-24x7-catalog.h"
#समावेश "hv-common.h"

/* Version of the 24x7 hypervisor API that we should use in this machine. */
अटल पूर्णांक पूर्णांकerface_version;

/* Whether we have to aggregate result data क्रम some करोमुख्यs. */
अटल bool aggregate_result_elements;

अटल cpumask_t hv_24x7_cpumask;

अटल bool करोमुख्य_is_valid(अचिन्हित करोमुख्य)
अणु
	चयन (करोमुख्य) अणु
#घोषणा DOMAIN(n, v, x, c)		\
	हाल HV_PERF_DOMAIN_##n:	\
		/* fall through */
#समावेश "hv-24x7-domains.h"
#अघोषित DOMAIN
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool is_physical_करोमुख्य(अचिन्हित करोमुख्य)
अणु
	चयन (करोमुख्य) अणु
#घोषणा DOMAIN(n, v, x, c)		\
	हाल HV_PERF_DOMAIN_##n:	\
		वापस c;
#समावेश "hv-24x7-domains.h"
#अघोषित DOMAIN
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * The Processor Module Inक्रमmation प्रणाली parameter allows transferring
 * of certain processor module inक्रमmation from the platक्रमm to the OS.
 * Refer PAPR+ करोcument to get parameter token value as '43'.
 */

#घोषणा PROCESSOR_MODULE_INFO   43

अटल u32 phys_sockets;	/* Physical sockets */
अटल u32 phys_chipspersocket;	/* Physical chips per socket*/
अटल u32 phys_coresperchip; /* Physical cores per chip */

/*
 * पढ़ो_24x7_sys_info()
 * Retrieve the number of sockets and chips per socket and cores per
 * chip details through the get-प्रणाली-parameter rtas call.
 */
व्योम पढ़ो_24x7_sys_info(व्योम)
अणु
	पूर्णांक call_status, len, ntypes;

	spin_lock(&rtas_data_buf_lock);

	/*
	 * Making प्रणाली parameter: chips and sockets and cores per chip
	 * शेष to 1.
	 */
	phys_sockets = 1;
	phys_chipspersocket = 1;
	phys_coresperchip = 1;

	call_status = rtas_call(rtas_token("ibm,get-system-parameter"), 3, 1,
				शून्य,
				PROCESSOR_MODULE_INFO,
				__pa(rtas_data_buf),
				RTAS_DATA_BUF_SIZE);

	अगर (call_status != 0) अणु
		pr_err("Error calling get-system-parameter %d\n",
		       call_status);
	पूर्ण अन्यथा अणु
		len = be16_to_cpup((__be16 *)&rtas_data_buf[0]);
		अगर (len < 8)
			जाओ out;

		ntypes = be16_to_cpup((__be16 *)&rtas_data_buf[2]);

		अगर (!ntypes)
			जाओ out;

		phys_sockets = be16_to_cpup((__be16 *)&rtas_data_buf[4]);
		phys_chipspersocket = be16_to_cpup((__be16 *)&rtas_data_buf[6]);
		phys_coresperchip = be16_to_cpup((__be16 *)&rtas_data_buf[8]);
	पूर्ण

out:
	spin_unlock(&rtas_data_buf_lock);
पूर्ण

/* Doमुख्यs क्रम which more than one result element are वापसed क्रम each event. */
अटल bool करोमुख्य_needs_aggregation(अचिन्हित पूर्णांक करोमुख्य)
अणु
	वापस aggregate_result_elements &&
			(करोमुख्य == HV_PERF_DOMAIN_PHYS_CORE ||
			 (करोमुख्य >= HV_PERF_DOMAIN_VCPU_HOME_CORE &&
			  करोमुख्य <= HV_PERF_DOMAIN_VCPU_REMOTE_NODE));
पूर्ण

अटल स्थिर अक्षर *करोमुख्य_name(अचिन्हित करोमुख्य)
अणु
	अगर (!करोमुख्य_is_valid(करोमुख्य))
		वापस शून्य;

	चयन (करोमुख्य) अणु
	हाल HV_PERF_DOMAIN_PHYS_CHIP:		वापस "Physical Chip";
	हाल HV_PERF_DOMAIN_PHYS_CORE:		वापस "Physical Core";
	हाल HV_PERF_DOMAIN_VCPU_HOME_CORE:	वापस "VCPU Home Core";
	हाल HV_PERF_DOMAIN_VCPU_HOME_CHIP:	वापस "VCPU Home Chip";
	हाल HV_PERF_DOMAIN_VCPU_HOME_NODE:	वापस "VCPU Home Node";
	हाल HV_PERF_DOMAIN_VCPU_REMOTE_NODE:	वापस "VCPU Remote Node";
	पूर्ण

	WARN_ON_ONCE(करोमुख्य);
	वापस शून्य;
पूर्ण

अटल bool catalog_entry_करोमुख्य_is_valid(अचिन्हित करोमुख्य)
अणु
	/* POWER8 करोesn't support भव करोमुख्यs. */
	अगर (पूर्णांकerface_version == 1)
		वापस is_physical_करोमुख्य(करोमुख्य);
	अन्यथा
		वापस करोमुख्य_is_valid(करोमुख्य);
पूर्ण

/*
 * TODO: Merging events:
 * - Think of the hcall as an पूर्णांकerface to a 4d array of counters:
 *   - x = करोमुख्यs
 *   - y = indexes in the करोमुख्य (core, chip, vcpu, node, etc)
 *   - z = offset पूर्णांकo the counter space
 *   - w = lpars (guest vms, "logical partitions")
 * - A single request is: x,y,y_last,z,z_last,w,w_last
 *   - this means we can retrieve a rectangle of counters in y,z क्रम a single x.
 *
 * - Things to consider (ignoring w):
 *   - input  cost_per_request = 16
 *   - output cost_per_result(ys,zs)  = 8 + 8 * ys + ys * zs
 *   - limited number of requests per hcall (must fit पूर्णांकo 4K bytes)
 *     - 4k = 16 [buffer header] - 16 [request size] * request_count
 *     - 255 requests per hcall
 *   - someबार it will be more efficient to पढ़ो extra data and discard
 */

/*
 * Example usage:
 *  perf stat -e 'hv_24x7/domain=2,offset=8,vcpu=0,lpar=0xffffffff/'
 */

/* u3 0-6, one of HV_24X7_PERF_DOMAIN */
EVENT_DEFINE_RANGE_FORMAT(करोमुख्य, config, 0, 3);
/* u16 */
EVENT_DEFINE_RANGE_FORMAT(core, config, 16, 31);
EVENT_DEFINE_RANGE_FORMAT(chip, config, 16, 31);
EVENT_DEFINE_RANGE_FORMAT(vcpu, config, 16, 31);
/* u32, see "data_offset" */
EVENT_DEFINE_RANGE_FORMAT(offset, config, 32, 63);
/* u16 */
EVENT_DEFINE_RANGE_FORMAT(lpar, config1, 0, 15);

EVENT_DEFINE_RANGE(reserved1, config,   4, 15);
EVENT_DEFINE_RANGE(reserved2, config1, 16, 63);
EVENT_DEFINE_RANGE(reserved3, config2,  0, 63);

अटल काष्ठा attribute *क्रमmat_attrs[] = अणु
	&क्रमmat_attr_करोमुख्य.attr,
	&क्रमmat_attr_offset.attr,
	&क्रमmat_attr_core.attr,
	&क्रमmat_attr_chip.attr,
	&क्रमmat_attr_vcpu.attr,
	&क्रमmat_attr_lpar.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group क्रमmat_group = अणु
	.name = "format",
	.attrs = क्रमmat_attrs,
पूर्ण;

अटल काष्ठा attribute_group event_group = अणु
	.name = "events",
	/* .attrs is set in init */
पूर्ण;

अटल काष्ठा attribute_group event_desc_group = अणु
	.name = "event_descs",
	/* .attrs is set in init */
पूर्ण;

अटल काष्ठा attribute_group event_दीर्घ_desc_group = अणु
	.name = "event_long_descs",
	/* .attrs is set in init */
पूर्ण;

अटल काष्ठा kmem_cache *hv_page_cache;

अटल DEFINE_PER_CPU(पूर्णांक, hv_24x7_txn_flags);
अटल DEFINE_PER_CPU(पूर्णांक, hv_24x7_txn_err);

काष्ठा hv_24x7_hw अणु
	काष्ठा perf_event *events[255];
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा hv_24x7_hw, hv_24x7_hw);

/*
 * request_buffer and result_buffer are not required to be 4k aligned,
 * but are not allowed to cross any 4k boundary. Aligning them to 4k is
 * the simplest way to ensure that.
 */
#घोषणा H24x7_DATA_BUFFER_SIZE	4096
अटल DEFINE_PER_CPU(अक्षर, hv_24x7_reqb[H24x7_DATA_BUFFER_SIZE]) __aligned(4096);
अटल DEFINE_PER_CPU(अक्षर, hv_24x7_resb[H24x7_DATA_BUFFER_SIZE]) __aligned(4096);

अटल अचिन्हित पूर्णांक max_num_requests(पूर्णांक पूर्णांकerface_version)
अणु
	वापस (H24x7_DATA_BUFFER_SIZE - माप(काष्ठा hv_24x7_request_buffer))
		/ H24x7_REQUEST_SIZE(पूर्णांकerface_version);
पूर्ण

अटल अक्षर *event_name(काष्ठा hv_24x7_event_data *ev, पूर्णांक *len)
अणु
	*len = be16_to_cpu(ev->event_name_len) - 2;
	वापस (अक्षर *)ev->reमुख्यder;
पूर्ण

अटल अक्षर *event_desc(काष्ठा hv_24x7_event_data *ev, पूर्णांक *len)
अणु
	अचिन्हित nl = be16_to_cpu(ev->event_name_len);
	__be16 *desc_len = (__be16 *)(ev->reमुख्यder + nl - 2);

	*len = be16_to_cpu(*desc_len) - 2;
	वापस (अक्षर *)ev->reमुख्यder + nl;
पूर्ण

अटल अक्षर *event_दीर्घ_desc(काष्ठा hv_24x7_event_data *ev, पूर्णांक *len)
अणु
	अचिन्हित nl = be16_to_cpu(ev->event_name_len);
	__be16 *desc_len_ = (__be16 *)(ev->reमुख्यder + nl - 2);
	अचिन्हित desc_len = be16_to_cpu(*desc_len_);
	__be16 *दीर्घ_desc_len = (__be16 *)(ev->reमुख्यder + nl + desc_len - 2);

	*len = be16_to_cpu(*दीर्घ_desc_len) - 2;
	वापस (अक्षर *)ev->reमुख्यder + nl + desc_len;
पूर्ण

अटल bool event_fixed_portion_is_within(काष्ठा hv_24x7_event_data *ev,
					  व्योम *end)
अणु
	व्योम *start = ev;

	वापस (start + दुरत्व(काष्ठा hv_24x7_event_data, reमुख्यder)) < end;
पूर्ण

/*
 * Things we करोn't check:
 *  - padding क्रम desc, name, and दीर्घ/detailed desc is required to be '\0'
 *    bytes.
 *
 *  Return शून्य अगर we pass end,
 *  Otherwise वापस the address of the byte just following the event.
 */
अटल व्योम *event_end(काष्ठा hv_24x7_event_data *ev, व्योम *end)
अणु
	व्योम *start = ev;
	__be16 *dl_, *ldl_;
	अचिन्हित dl, ldl;
	अचिन्हित nl = be16_to_cpu(ev->event_name_len);

	अगर (nl < 2) अणु
		pr_debug("%s: name length too short: %d", __func__, nl);
		वापस शून्य;
	पूर्ण

	अगर (start + nl > end) अणु
		pr_debug("%s: start=%p + nl=%u > end=%p",
				__func__, start, nl, end);
		वापस शून्य;
	पूर्ण

	dl_ = (__be16 *)(ev->reमुख्यder + nl - 2);
	अगर (!IS_ALIGNED((uपूर्णांकptr_t)dl_, 2))
		pr_warn("desc len not aligned %p", dl_);
	dl = be16_to_cpu(*dl_);
	अगर (dl < 2) अणु
		pr_debug("%s: desc len too short: %d", __func__, dl);
		वापस शून्य;
	पूर्ण

	अगर (start + nl + dl > end) अणु
		pr_debug("%s: (start=%p + nl=%u + dl=%u)=%p > end=%p",
				__func__, start, nl, dl, start + nl + dl, end);
		वापस शून्य;
	पूर्ण

	ldl_ = (__be16 *)(ev->reमुख्यder + nl + dl - 2);
	अगर (!IS_ALIGNED((uपूर्णांकptr_t)ldl_, 2))
		pr_warn("long desc len not aligned %p", ldl_);
	ldl = be16_to_cpu(*ldl_);
	अगर (ldl < 2) अणु
		pr_debug("%s: long desc len too short (ldl=%u)",
				__func__, ldl);
		वापस शून्य;
	पूर्ण

	अगर (start + nl + dl + ldl > end) अणु
		pr_debug("%s: start=%p + nl=%u + dl=%u + ldl=%u > end=%p",
				__func__, start, nl, dl, ldl, end);
		वापस शून्य;
	पूर्ण

	वापस start + nl + dl + ldl;
पूर्ण

अटल दीर्घ h_get_24x7_catalog_page_(अचिन्हित दीर्घ phys_4096,
				     अचिन्हित दीर्घ version, अचिन्हित दीर्घ index)
अणु
	pr_devel("h_get_24x7_catalog_page(0x%lx, %lu, %lu)",
			phys_4096, version, index);

	WARN_ON(!IS_ALIGNED(phys_4096, 4096));

	वापस plpar_hcall_norets(H_GET_24X7_CATALOG_PAGE,
			phys_4096, version, index);
पूर्ण

अटल दीर्घ h_get_24x7_catalog_page(अक्षर page[], u64 version, u32 index)
अणु
	वापस h_get_24x7_catalog_page_(virt_to_phys(page),
					version, index);
पूर्ण

/*
 * Each event we find in the catalog, will have a sysfs entry. Format the
 * data क्रम this sysfs entry based on the event's करोमुख्य.
 *
 * Events beदीर्घing to the Chip करोमुख्य can only be monitored in that करोमुख्य.
 * i.e the करोमुख्य क्रम these events is a fixed/knwon value.
 *
 * Events beदीर्घing to the Core करोमुख्य can be monitored either in the physical
 * core or in one of the भव CPU करोमुख्यs. So the करोमुख्य value क्रम these
 * events must be specअगरied by the user (i.e is a required parameter). Format
 * the Core events with 'domain=?' so the perf-tool can error check required
 * parameters.
 *
 * NOTE: For the Core करोमुख्य events, rather than making करोमुख्य a required
 *	 parameter we could शेष it to PHYS_CORE and allowe users to
 *	 override the करोमुख्य to one of the VCPU करोमुख्यs.
 *
 *	 However, this can make the पूर्णांकerface a little inconsistent.
 *
 *	 If we set करोमुख्य=2 (PHYS_CHIP) and allow user to override this field
 *	 the user may be tempted to also modअगरy the "offset=x" field in which
 *	 can lead to confusing usage. Consider the HPM_PCYC (offset=0x18) and
 *	 HPM_INST (offset=0x20) events. With:
 *
 *		perf stat -e hv_24x7/HPM_PCYC,offset=0x20/
 *
 *	we end up monitoring HPM_INST, जबतक the command line has HPM_PCYC.
 *
 *	By not assigning a शेष value to the करोमुख्य क्रम the Core events,
 *	we can have simple guidelines:
 *
 *		- Specअगरying values क्रम parameters with "=?" is required.
 *
 *		- Specअगरying (i.e overriding) values क्रम other parameters
 *		  is undefined.
 */
अटल अक्षर *event_fmt(काष्ठा hv_24x7_event_data *event, अचिन्हित करोमुख्य)
अणु
	स्थिर अक्षर *sindex;
	स्थिर अक्षर *lpar;
	स्थिर अक्षर *करोमुख्य_str;
	अक्षर buf[8];

	चयन (करोमुख्य) अणु
	हाल HV_PERF_DOMAIN_PHYS_CHIP:
		snम_लिखो(buf, माप(buf), "%d", करोमुख्य);
		करोमुख्य_str = buf;
		lpar = "0x0";
		sindex = "chip";
		अवरोध;
	हाल HV_PERF_DOMAIN_PHYS_CORE:
		करोमुख्य_str = "?";
		lpar = "0x0";
		sindex = "core";
		अवरोध;
	शेष:
		करोमुख्य_str = "?";
		lpar = "?";
		sindex = "vcpu";
	पूर्ण

	वापस kaप्र_लिखो(GFP_KERNEL,
			"domain=%s,offset=0x%x,%s=?,lpar=%s",
			करोमुख्य_str,
			be16_to_cpu(event->event_counter_offs) +
				be16_to_cpu(event->event_group_record_offs),
			sindex,
			lpar);
पूर्ण

/* Aव्योम trusting fw to NUL terminate strings */
अटल अक्षर *memdup_to_str(अक्षर *maybe_str, पूर्णांक max_len, gfp_t gfp)
अणु
	वापस kaप्र_लिखो(gfp, "%.*s", max_len, maybe_str);
पूर्ण

अटल sमाप_प्रकार device_show_string(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dev_ext_attribute *d;

	d = container_of(attr, काष्ठा dev_ext_attribute, attr);

	वापस प्र_लिखो(buf, "%s\n", (अक्षर *)d->var);
पूर्ण

अटल sमाप_प्रकार cpumask_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, &hv_24x7_cpumask);
पूर्ण

अटल sमाप_प्रकार sockets_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", phys_sockets);
पूर्ण

अटल sमाप_प्रकार chipspersocket_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", phys_chipspersocket);
पूर्ण

अटल sमाप_प्रकार coresperchip_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", phys_coresperchip);
पूर्ण

अटल काष्ठा attribute *device_str_attr_create_(अक्षर *name, अक्षर *str)
अणु
	काष्ठा dev_ext_attribute *attr = kzalloc(माप(*attr), GFP_KERNEL);

	अगर (!attr)
		वापस शून्य;

	sysfs_attr_init(&attr->attr.attr);

	attr->var = str;
	attr->attr.attr.name = name;
	attr->attr.attr.mode = 0444;
	attr->attr.show = device_show_string;

	वापस &attr->attr.attr;
पूर्ण

/*
 * Allocate and initialize strings representing event attributes.
 *
 * NOTE: The strings allocated here are never destroyed and जारी to
 *	 exist till shutकरोwn. This is to allow us to create as many events
 *	 from the catalog as possible, even अगर we encounter errors with some.
 *	 In हाल of changes to error paths in future, these may need to be
 *	 मुक्तd by the caller.
 */
अटल काष्ठा attribute *device_str_attr_create(अक्षर *name, पूर्णांक name_max,
						पूर्णांक name_nonce,
						अक्षर *str, माप_प्रकार str_max)
अणु
	अक्षर *n;
	अक्षर *s = memdup_to_str(str, str_max, GFP_KERNEL);
	काष्ठा attribute *a;

	अगर (!s)
		वापस शून्य;

	अगर (!name_nonce)
		n = kaप्र_लिखो(GFP_KERNEL, "%.*s", name_max, name);
	अन्यथा
		n = kaप्र_लिखो(GFP_KERNEL, "%.*s__%d", name_max, name,
					name_nonce);
	अगर (!n)
		जाओ out_s;

	a = device_str_attr_create_(n, s);
	अगर (!a)
		जाओ out_n;

	वापस a;
out_n:
	kमुक्त(n);
out_s:
	kमुक्त(s);
	वापस शून्य;
पूर्ण

अटल काष्ठा attribute *event_to_attr(अचिन्हित ix,
				       काष्ठा hv_24x7_event_data *event,
				       अचिन्हित करोमुख्य,
				       पूर्णांक nonce)
अणु
	पूर्णांक event_name_len;
	अक्षर *ev_name, *a_ev_name, *val;
	काष्ठा attribute *attr;

	अगर (!करोमुख्य_is_valid(करोमुख्य)) अणु
		pr_warn("catalog event %u has invalid domain %u\n",
				ix, करोमुख्य);
		वापस शून्य;
	पूर्ण

	val = event_fmt(event, करोमुख्य);
	अगर (!val)
		वापस शून्य;

	ev_name = event_name(event, &event_name_len);
	अगर (!nonce)
		a_ev_name = kaप्र_लिखो(GFP_KERNEL, "%.*s",
				(पूर्णांक)event_name_len, ev_name);
	अन्यथा
		a_ev_name = kaप्र_लिखो(GFP_KERNEL, "%.*s__%d",
				(पूर्णांक)event_name_len, ev_name, nonce);

	अगर (!a_ev_name)
		जाओ out_val;

	attr = device_str_attr_create_(a_ev_name, val);
	अगर (!attr)
		जाओ out_name;

	वापस attr;
out_name:
	kमुक्त(a_ev_name);
out_val:
	kमुक्त(val);
	वापस शून्य;
पूर्ण

अटल काष्ठा attribute *event_to_desc_attr(काष्ठा hv_24x7_event_data *event,
					    पूर्णांक nonce)
अणु
	पूर्णांक nl, dl;
	अक्षर *name = event_name(event, &nl);
	अक्षर *desc = event_desc(event, &dl);

	/* If there isn't a description, don't create the sysfs file */
	अगर (!dl)
		वापस शून्य;

	वापस device_str_attr_create(name, nl, nonce, desc, dl);
पूर्ण

अटल काष्ठा attribute *
event_to_दीर्घ_desc_attr(काष्ठा hv_24x7_event_data *event, पूर्णांक nonce)
अणु
	पूर्णांक nl, dl;
	अक्षर *name = event_name(event, &nl);
	अक्षर *desc = event_दीर्घ_desc(event, &dl);

	/* If there isn't a description, don't create the sysfs file */
	अगर (!dl)
		वापस शून्य;

	वापस device_str_attr_create(name, nl, nonce, desc, dl);
पूर्ण

अटल पूर्णांक event_data_to_attrs(अचिन्हित ix, काष्ठा attribute **attrs,
				   काष्ठा hv_24x7_event_data *event, पूर्णांक nonce)
अणु
	*attrs = event_to_attr(ix, event, event->करोमुख्य, nonce);
	अगर (!*attrs)
		वापस -1;

	वापस 0;
पूर्ण

/* */
काष्ठा event_uniq अणु
	काष्ठा rb_node node;
	स्थिर अक्षर *name;
	पूर्णांक nl;
	अचिन्हित ct;
	अचिन्हित करोमुख्य;
पूर्ण;

अटल पूर्णांक memord(स्थिर व्योम *d1, माप_प्रकार s1, स्थिर व्योम *d2, माप_प्रकार s2)
अणु
	अगर (s1 < s2)
		वापस 1;
	अगर (s1 > s2)
		वापस -1;

	वापस स_भेद(d1, d2, s1);
पूर्ण

अटल पूर्णांक ev_uniq_ord(स्थिर व्योम *v1, माप_प्रकार s1, अचिन्हित d1, स्थिर व्योम *v2,
		       माप_प्रकार s2, अचिन्हित d2)
अणु
	पूर्णांक r = memord(v1, s1, v2, s2);

	अगर (r)
		वापस r;
	अगर (d1 > d2)
		वापस 1;
	अगर (d2 > d1)
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक event_uniq_add(काष्ठा rb_root *root, स्थिर अक्षर *name, पूर्णांक nl,
			  अचिन्हित करोमुख्य)
अणु
	काष्ठा rb_node **new = &(root->rb_node), *parent = शून्य;
	काष्ठा event_uniq *data;

	/* Figure out where to put new node */
	जबतक (*new) अणु
		काष्ठा event_uniq *it;
		पूर्णांक result;

		it = rb_entry(*new, काष्ठा event_uniq, node);
		result = ev_uniq_ord(name, nl, करोमुख्य, it->name, it->nl,
					it->करोमुख्य);

		parent = *new;
		अगर (result < 0)
			new = &((*new)->rb_left);
		अन्यथा अगर (result > 0)
			new = &((*new)->rb_right);
		अन्यथा अणु
			it->ct++;
			pr_info("found a duplicate event %.*s, ct=%u\n", nl,
						name, it->ct);
			वापस it->ct;
		पूर्ण
	पूर्ण

	data = kदो_स्मृति(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	*data = (काष्ठा event_uniq) अणु
		.name = name,
		.nl = nl,
		.ct = 0,
		.करोमुख्य = करोमुख्य,
	पूर्ण;

	/* Add new node and rebalance tree. */
	rb_link_node(&data->node, parent, new);
	rb_insert_color(&data->node, root);

	/* data->ct */
	वापस 0;
पूर्ण

अटल व्योम event_uniq_destroy(काष्ठा rb_root *root)
अणु
	/*
	 * the strings we poपूर्णांक to are in the giant block of memory filled by
	 * the catalog, and are मुक्तd separately.
	 */
	काष्ठा event_uniq *pos, *n;

	rbtree_postorder_क्रम_each_entry_safe(pos, n, root, node)
		kमुक्त(pos);
पूर्ण


/*
 * ensure the event काष्ठाure's sizes are self consistent and don't cause us to
 * पढ़ो outside of the event
 *
 * On success, वापस the event length in bytes.
 * Otherwise, वापस -1 (and prपूर्णांक as appropriate).
 */
अटल sमाप_प्रकार catalog_event_len_validate(काष्ठा hv_24x7_event_data *event,
					  माप_प्रकार event_idx,
					  माप_प्रकार event_data_bytes,
					  माप_प्रकार event_entry_count,
					  माप_प्रकार offset, व्योम *end)
अणु
	sमाप_प्रकार ev_len;
	व्योम *ev_end, *calc_ev_end;

	अगर (offset >= event_data_bytes)
		वापस -1;

	अगर (event_idx >= event_entry_count) अणु
		pr_devel("catalog event data has %zu bytes of padding after last event\n",
				event_data_bytes - offset);
		वापस -1;
	पूर्ण

	अगर (!event_fixed_portion_is_within(event, end)) अणु
		pr_warn("event %zu fixed portion is not within range\n",
				event_idx);
		वापस -1;
	पूर्ण

	ev_len = be16_to_cpu(event->length);

	अगर (ev_len % 16)
		pr_info("event %zu has length %zu not divisible by 16: event=%pK\n",
				event_idx, ev_len, event);

	ev_end = (__u8 *)event + ev_len;
	अगर (ev_end > end) अणु
		pr_warn("event %zu has .length=%zu, ends after buffer end: ev_end=%pK > end=%pK, offset=%zu\n",
				event_idx, ev_len, ev_end, end,
				offset);
		वापस -1;
	पूर्ण

	calc_ev_end = event_end(event, end);
	अगर (!calc_ev_end) अणु
		pr_warn("event %zu has a calculated length which exceeds buffer length %zu: event=%pK end=%pK, offset=%zu\n",
			event_idx, event_data_bytes, event, end,
			offset);
		वापस -1;
	पूर्ण

	अगर (calc_ev_end > ev_end) अणु
		pr_warn("event %zu exceeds it's own length: event=%pK, end=%pK, offset=%zu, calc_ev_end=%pK\n",
			event_idx, event, ev_end, offset, calc_ev_end);
		वापस -1;
	पूर्ण

	वापस ev_len;
पूर्ण

/*
 * Return true inहाल of invalid or dummy events with names like RESERVED*
 */
अटल bool ignore_event(स्थिर अक्षर *name)
अणु
	वापस म_भेदन(name, "RESERVED", 8) == 0;
पूर्ण

#घोषणा MAX_4K (SIZE_MAX / 4096)

अटल पूर्णांक create_events_from_catalog(काष्ठा attribute ***events_,
				      काष्ठा attribute ***event_descs_,
				      काष्ठा attribute ***event_दीर्घ_descs_)
अणु
	दीर्घ hret;
	माप_प्रकार catalog_len, catalog_page_len, event_entry_count,
	       event_data_len, event_data_offs,
	       event_data_bytes, junk_events, event_idx, event_attr_ct, i,
	       attr_max, event_idx_last, desc_ct, दीर्घ_desc_ct;
	sमाप_प्रकार ct, ev_len;
	uपूर्णांक64_t catalog_version_num;
	काष्ठा attribute **events, **event_descs, **event_दीर्घ_descs;
	काष्ठा hv_24x7_catalog_page_0 *page_0 =
		kmem_cache_alloc(hv_page_cache, GFP_KERNEL);
	व्योम *page = page_0;
	व्योम *event_data, *end;
	काष्ठा hv_24x7_event_data *event;
	काष्ठा rb_root ev_uniq = RB_ROOT;
	पूर्णांक ret = 0;

	अगर (!page) अणु
		ret = -ENOMEM;
		जाओ e_out;
	पूर्ण

	hret = h_get_24x7_catalog_page(page, 0, 0);
	अगर (hret) अणु
		ret = -EIO;
		जाओ e_मुक्त;
	पूर्ण

	catalog_version_num = be64_to_cpu(page_0->version);
	catalog_page_len = be32_to_cpu(page_0->length);

	अगर (MAX_4K < catalog_page_len) अणु
		pr_err("invalid page count: %zu\n", catalog_page_len);
		ret = -EIO;
		जाओ e_मुक्त;
	पूर्ण

	catalog_len = catalog_page_len * 4096;

	event_entry_count = be16_to_cpu(page_0->event_entry_count);
	event_data_offs   = be16_to_cpu(page_0->event_data_offs);
	event_data_len    = be16_to_cpu(page_0->event_data_len);

	pr_devel("cv %llu cl %zu eec %zu edo %zu edl %zu\n",
			catalog_version_num, catalog_len,
			event_entry_count, event_data_offs, event_data_len);

	अगर ((MAX_4K < event_data_len)
			|| (MAX_4K < event_data_offs)
			|| (MAX_4K - event_data_offs < event_data_len)) अणु
		pr_err("invalid event data offs %zu and/or len %zu\n",
				event_data_offs, event_data_len);
		ret = -EIO;
		जाओ e_मुक्त;
	पूर्ण

	अगर ((event_data_offs + event_data_len) > catalog_page_len) अणु
		pr_err("event data %zu-%zu does not fit inside catalog 0-%zu\n",
				event_data_offs,
				event_data_offs + event_data_len,
				catalog_page_len);
		ret = -EIO;
		जाओ e_मुक्त;
	पूर्ण

	अगर (SIZE_MAX - 1 < event_entry_count) अणु
		pr_err("event_entry_count %zu is invalid\n", event_entry_count);
		ret = -EIO;
		जाओ e_मुक्त;
	पूर्ण

	event_data_bytes = event_data_len * 4096;

	/*
	 * event data can span several pages, events can cross between these
	 * pages. Use vदो_स्मृति to make this easier.
	 */
	event_data = vदो_स्मृति(event_data_bytes);
	अगर (!event_data) अणु
		pr_err("could not allocate event data\n");
		ret = -ENOMEM;
		जाओ e_मुक्त;
	पूर्ण

	end = event_data + event_data_bytes;

	/*
	 * using vदो_स्मृति_to_phys() like this only works अगर PAGE_SIZE is
	 * भागisible by 4096
	 */
	BUILD_BUG_ON(PAGE_SIZE % 4096);

	क्रम (i = 0; i < event_data_len; i++) अणु
		hret = h_get_24x7_catalog_page_(
				vदो_स्मृति_to_phys(event_data + i * 4096),
				catalog_version_num,
				i + event_data_offs);
		अगर (hret) अणु
			pr_err("Failed to get event data in page %zu: rc=%ld\n",
			       i + event_data_offs, hret);
			ret = -EIO;
			जाओ e_event_data;
		पूर्ण
	पूर्ण

	/*
	 * scan the catalog to determine the number of attributes we need, and
	 * verअगरy it at the same समय.
	 */
	क्रम (junk_events = 0, event = event_data, event_idx = 0, attr_max = 0;
	     ;
	     event_idx++, event = (व्योम *)event + ev_len) अणु
		माप_प्रकार offset = (व्योम *)event - (व्योम *)event_data;
		अक्षर *name;
		पूर्णांक nl;

		ev_len = catalog_event_len_validate(event, event_idx,
						    event_data_bytes,
						    event_entry_count,
						    offset, end);
		अगर (ev_len < 0)
			अवरोध;

		name = event_name(event, &nl);

		अगर (ignore_event(name)) अणु
			junk_events++;
			जारी;
		पूर्ण
		अगर (event->event_group_record_len == 0) अणु
			pr_devel("invalid event %zu (%.*s): group_record_len == 0, skipping\n",
					event_idx, nl, name);
			junk_events++;
			जारी;
		पूर्ण

		अगर (!catalog_entry_करोमुख्य_is_valid(event->करोमुख्य)) अणु
			pr_info("event %zu (%.*s) has invalid domain %d\n",
					event_idx, nl, name, event->करोमुख्य);
			junk_events++;
			जारी;
		पूर्ण

		attr_max++;
	पूर्ण

	event_idx_last = event_idx;
	अगर (event_idx_last != event_entry_count)
		pr_warn("event buffer ended before listed # of events were parsed (got %zu, wanted %zu, junk %zu)\n",
				event_idx_last, event_entry_count, junk_events);

	events = kदो_स्मृति_array(attr_max + 1, माप(*events), GFP_KERNEL);
	अगर (!events) अणु
		ret = -ENOMEM;
		जाओ e_event_data;
	पूर्ण

	event_descs = kदो_स्मृति_array(event_idx + 1, माप(*event_descs),
				GFP_KERNEL);
	अगर (!event_descs) अणु
		ret = -ENOMEM;
		जाओ e_event_attrs;
	पूर्ण

	event_दीर्घ_descs = kदो_स्मृति_array(event_idx + 1,
			माप(*event_दीर्घ_descs), GFP_KERNEL);
	अगर (!event_दीर्घ_descs) अणु
		ret = -ENOMEM;
		जाओ e_event_descs;
	पूर्ण

	/* Iterate over the catalog filling in the attribute vector */
	क्रम (junk_events = 0, event_attr_ct = 0, desc_ct = 0, दीर्घ_desc_ct = 0,
				event = event_data, event_idx = 0;
			event_idx < event_idx_last;
			event_idx++, ev_len = be16_to_cpu(event->length),
				event = (व्योम *)event + ev_len) अणु
		अक्षर *name;
		पूर्णांक nl;
		पूर्णांक nonce;
		/*
		 * these are the only "bad" events that are पूर्णांकermixed and that
		 * we can ignore without issue. make sure to skip them here
		 */
		अगर (event->event_group_record_len == 0)
			जारी;
		अगर (!catalog_entry_करोमुख्य_is_valid(event->करोमुख्य))
			जारी;

		name  = event_name(event, &nl);
		अगर (ignore_event(name))
			जारी;

		nonce = event_uniq_add(&ev_uniq, name, nl, event->करोमुख्य);
		ct    = event_data_to_attrs(event_idx, events + event_attr_ct,
					    event, nonce);
		अगर (ct < 0) अणु
			pr_warn("event %zu (%.*s) creation failure, skipping\n",
				event_idx, nl, name);
			junk_events++;
		पूर्ण अन्यथा अणु
			event_attr_ct++;
			event_descs[desc_ct] = event_to_desc_attr(event, nonce);
			अगर (event_descs[desc_ct])
				desc_ct++;
			event_दीर्घ_descs[दीर्घ_desc_ct] =
					event_to_दीर्घ_desc_attr(event, nonce);
			अगर (event_दीर्घ_descs[दीर्घ_desc_ct])
				दीर्घ_desc_ct++;
		पूर्ण
	पूर्ण

	pr_info("read %zu catalog entries, created %zu event attrs (%zu failures), %zu descs\n",
			event_idx, event_attr_ct, junk_events, desc_ct);

	events[event_attr_ct] = शून्य;
	event_descs[desc_ct] = शून्य;
	event_दीर्घ_descs[दीर्घ_desc_ct] = शून्य;

	event_uniq_destroy(&ev_uniq);
	vमुक्त(event_data);
	kmem_cache_मुक्त(hv_page_cache, page);

	*events_ = events;
	*event_descs_ = event_descs;
	*event_दीर्घ_descs_ = event_दीर्घ_descs;
	वापस 0;

e_event_descs:
	kमुक्त(event_descs);
e_event_attrs:
	kमुक्त(events);
e_event_data:
	vमुक्त(event_data);
e_मुक्त:
	kmem_cache_मुक्त(hv_page_cache, page);
e_out:
	*events_ = शून्य;
	*event_descs_ = शून्य;
	*event_दीर्घ_descs_ = शून्य;
	वापस ret;
पूर्ण

अटल sमाप_प्रकार catalog_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			    काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			    loff_t offset, माप_प्रकार count)
अणु
	दीर्घ hret;
	sमाप_प्रकार ret = 0;
	माप_प्रकार catalog_len = 0, catalog_page_len = 0;
	loff_t page_offset = 0;
	loff_t offset_in_page;
	माप_प्रकार copy_len;
	uपूर्णांक64_t catalog_version_num = 0;
	व्योम *page = kmem_cache_alloc(hv_page_cache, GFP_USER);
	काष्ठा hv_24x7_catalog_page_0 *page_0 = page;

	अगर (!page)
		वापस -ENOMEM;

	hret = h_get_24x7_catalog_page(page, 0, 0);
	अगर (hret) अणु
		ret = -EIO;
		जाओ e_मुक्त;
	पूर्ण

	catalog_version_num = be64_to_cpu(page_0->version);
	catalog_page_len = be32_to_cpu(page_0->length);
	catalog_len = catalog_page_len * 4096;

	page_offset = offset / 4096;
	offset_in_page = offset % 4096;

	अगर (page_offset >= catalog_page_len)
		जाओ e_मुक्त;

	अगर (page_offset != 0) अणु
		hret = h_get_24x7_catalog_page(page, catalog_version_num,
					       page_offset);
		अगर (hret) अणु
			ret = -EIO;
			जाओ e_मुक्त;
		पूर्ण
	पूर्ण

	copy_len = 4096 - offset_in_page;
	अगर (copy_len > count)
		copy_len = count;

	स_नकल(buf, page+offset_in_page, copy_len);
	ret = copy_len;

e_मुक्त:
	अगर (hret)
		pr_err("h_get_24x7_catalog_page(ver=%lld, page=%lld) failed:"
		       " rc=%ld\n",
		       catalog_version_num, page_offset, hret);
	kmem_cache_मुक्त(hv_page_cache, page);

	pr_devel("catalog_read: offset=%lld(%lld) count=%zu "
			"catalog_len=%zu(%zu) => %zd\n", offset, page_offset,
			count, catalog_len, catalog_page_len, ret);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार करोमुख्यs_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *page)
अणु
	पूर्णांक d, n, count = 0;
	स्थिर अक्षर *str;

	क्रम (d = 0; d < HV_PERF_DOMAIN_MAX; d++) अणु
		str = करोमुख्य_name(d);
		अगर (!str)
			जारी;

		n = प्र_लिखो(page, "%d: %s\n", d, str);
		अगर (n < 0)
			अवरोध;

		count += n;
		page += n;
	पूर्ण
	वापस count;
पूर्ण

#घोषणा PAGE_0_ATTR(_name, _fmt, _expr)				\
अटल sमाप_प्रकार _name##_show(काष्ठा device *dev,			\
			    काष्ठा device_attribute *dev_attr,	\
			    अक्षर *buf)				\
अणु								\
	दीर्घ hret;						\
	sमाप_प्रकार ret = 0;					\
	व्योम *page = kmem_cache_alloc(hv_page_cache, GFP_USER);	\
	काष्ठा hv_24x7_catalog_page_0 *page_0 = page;		\
	अगर (!page)						\
		वापस -ENOMEM;					\
	hret = h_get_24x7_catalog_page(page, 0, 0);		\
	अगर (hret) अणु						\
		ret = -EIO;					\
		जाओ e_मुक्त;					\
	पूर्ण							\
	ret = प्र_लिखो(buf, _fmt, _expr);			\
e_मुक्त:								\
	kmem_cache_मुक्त(hv_page_cache, page);			\
	वापस ret;						\
पूर्ण								\
अटल DEVICE_ATTR_RO(_name)

PAGE_0_ATTR(catalog_version, "%lld\n",
		(अचिन्हित दीर्घ दीर्घ)be64_to_cpu(page_0->version));
PAGE_0_ATTR(catalog_len, "%lld\n",
		(अचिन्हित दीर्घ दीर्घ)be32_to_cpu(page_0->length) * 4096);
अटल BIN_ATTR_RO(catalog, 0/* real length varies */);
अटल DEVICE_ATTR_RO(करोमुख्यs);
अटल DEVICE_ATTR_RO(sockets);
अटल DEVICE_ATTR_RO(chipspersocket);
अटल DEVICE_ATTR_RO(coresperchip);
अटल DEVICE_ATTR_RO(cpumask);

अटल काष्ठा bin_attribute *अगर_bin_attrs[] = अणु
	&bin_attr_catalog,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *cpumask_attrs[] = अणु
	&dev_attr_cpumask.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group cpumask_attr_group = अणु
	.attrs = cpumask_attrs,
पूर्ण;

अटल काष्ठा attribute *अगर_attrs[] = अणु
	&dev_attr_catalog_len.attr,
	&dev_attr_catalog_version.attr,
	&dev_attr_करोमुख्यs.attr,
	&dev_attr_sockets.attr,
	&dev_attr_chipspersocket.attr,
	&dev_attr_coresperchip.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group अगर_group = अणु
	.name = "interface",
	.bin_attrs = अगर_bin_attrs,
	.attrs = अगर_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *attr_groups[] = अणु
	&क्रमmat_group,
	&event_group,
	&event_desc_group,
	&event_दीर्घ_desc_group,
	&अगर_group,
	&cpumask_attr_group,
	शून्य,
पूर्ण;

/*
 * Start the process क्रम a new H_GET_24x7_DATA hcall.
 */
अटल व्योम init_24x7_request(काष्ठा hv_24x7_request_buffer *request_buffer,
			      काष्ठा hv_24x7_data_result_buffer *result_buffer)
अणु

	स_रखो(request_buffer, 0, H24x7_DATA_BUFFER_SIZE);
	स_रखो(result_buffer, 0, H24x7_DATA_BUFFER_SIZE);

	request_buffer->पूर्णांकerface_version = पूर्णांकerface_version;
	/* स_रखो above set request_buffer->num_requests to 0 */
पूर्ण

/*
 * Commit (i.e perक्रमm) the H_GET_24x7_DATA hcall using the data collected
 * by 'init_24x7_request()' and 'add_event_to_24x7_request()'.
 */
अटल पूर्णांक make_24x7_request(काष्ठा hv_24x7_request_buffer *request_buffer,
			     काष्ठा hv_24x7_data_result_buffer *result_buffer)
अणु
	दीर्घ ret;

	/*
	 * NOTE: Due to variable number of array elements in request and
	 *	 result buffer(s), माप() is not reliable. Use the actual
	 *	 allocated buffer size, H24x7_DATA_BUFFER_SIZE.
	 */
	ret = plpar_hcall_norets(H_GET_24X7_DATA,
			virt_to_phys(request_buffer), H24x7_DATA_BUFFER_SIZE,
			virt_to_phys(result_buffer),  H24x7_DATA_BUFFER_SIZE);

	अगर (ret) अणु
		काष्ठा hv_24x7_request *req;

		req = request_buffer->requests;
		pr_notice_ratelimited("hcall failed: [%d %#x %#x %d] => ret 0x%lx (%ld) detail=0x%x failing ix=%x\n",
				      req->perक्रमmance_करोमुख्य, req->data_offset,
				      req->starting_ix, req->starting_lpar_ix,
				      ret, ret, result_buffer->detailed_rc,
				      result_buffer->failing_request_ix);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Add the given @event to the next slot in the 24x7 request_buffer.
 *
 * Note that H_GET_24X7_DATA hcall allows पढ़ोing several counters'
 * values in a single HCALL. We expect the caller to add events to the
 * request buffer one by one, make the HCALL and process the results.
 */
अटल पूर्णांक add_event_to_24x7_request(काष्ठा perf_event *event,
				काष्ठा hv_24x7_request_buffer *request_buffer)
अणु
	u16 idx;
	पूर्णांक i;
	माप_प्रकार req_size;
	काष्ठा hv_24x7_request *req;

	अगर (request_buffer->num_requests >=
	    max_num_requests(request_buffer->पूर्णांकerface_version)) अणु
		pr_devel("Too many requests for 24x7 HCALL %d\n",
				request_buffer->num_requests);
		वापस -EINVAL;
	पूर्ण

	चयन (event_get_करोमुख्य(event)) अणु
	हाल HV_PERF_DOMAIN_PHYS_CHIP:
		idx = event_get_chip(event);
		अवरोध;
	हाल HV_PERF_DOMAIN_PHYS_CORE:
		idx = event_get_core(event);
		अवरोध;
	शेष:
		idx = event_get_vcpu(event);
	पूर्ण

	req_size = H24x7_REQUEST_SIZE(request_buffer->पूर्णांकerface_version);

	i = request_buffer->num_requests++;
	req = (व्योम *) request_buffer->requests + i * req_size;

	req->perक्रमmance_करोमुख्य = event_get_करोमुख्य(event);
	req->data_size = cpu_to_be16(8);
	req->data_offset = cpu_to_be32(event_get_offset(event));
	req->starting_lpar_ix = cpu_to_be16(event_get_lpar(event));
	req->max_num_lpars = cpu_to_be16(1);
	req->starting_ix = cpu_to_be16(idx);
	req->max_ix = cpu_to_be16(1);

	अगर (request_buffer->पूर्णांकerface_version > 1) अणु
		अगर (करोमुख्य_needs_aggregation(req->perक्रमmance_करोमुख्य))
			req->max_num_thपढ़ो_groups = -1;
		अन्यथा अगर (req->perक्रमmance_करोमुख्य != HV_PERF_DOMAIN_PHYS_CHIP) अणु
			req->starting_thपढ़ो_group_ix = idx % 2;
			req->max_num_thपढ़ो_groups = 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * get_count_from_result - get event count from all result elements in result
 *
 * If the event corresponding to this result needs aggregation of the result
 * element values, then this function करोes that.
 *
 * @event:	Event associated with @res.
 * @resb:	Result buffer containing @res.
 * @res:	Result to work on.
 * @countp:	Output variable containing the event count.
 * @next:	Optional output variable poपूर्णांकing to the next result in @resb.
 */
अटल पूर्णांक get_count_from_result(काष्ठा perf_event *event,
				 काष्ठा hv_24x7_data_result_buffer *resb,
				 काष्ठा hv_24x7_result *res, u64 *countp,
				 काष्ठा hv_24x7_result **next)
अणु
	u16 num_elements = be16_to_cpu(res->num_elements_वापसed);
	u16 data_size = be16_to_cpu(res->result_element_data_size);
	अचिन्हित पूर्णांक data_offset;
	व्योम *element_data;
	पूर्णांक i;
	u64 count;

	/*
	 * We can bail out early अगर the result is empty.
	 */
	अगर (!num_elements) अणु
		pr_debug("Result of request %hhu is empty, nothing to do\n",
			 res->result_ix);

		अगर (next)
			*next = (काष्ठा hv_24x7_result *) res->elements;

		वापस -ENODATA;
	पूर्ण

	/*
	 * Since we always specअगरy 1 as the maximum क्रम the smallest resource
	 * we're requesting, there should to be only one element per result.
	 * Except when an event needs aggregation, in which हाल there are more.
	 */
	अगर (num_elements != 1 &&
	    !करोमुख्य_needs_aggregation(event_get_करोमुख्य(event))) अणु
		pr_err("Error: result of request %hhu has %hu elements\n",
		       res->result_ix, num_elements);

		वापस -EIO;
	पूर्ण

	अगर (data_size != माप(u64)) अणु
		pr_debug("Error: result of request %hhu has data of %hu bytes\n",
			 res->result_ix, data_size);

		वापस -ENOTSUPP;
	पूर्ण

	अगर (resb->पूर्णांकerface_version == 1)
		data_offset = दुरत्व(काष्ठा hv_24x7_result_element_v1,
				       element_data);
	अन्यथा
		data_offset = दुरत्व(काष्ठा hv_24x7_result_element_v2,
				       element_data);

	/* Go through the result elements in the result. */
	क्रम (i = count = 0, element_data = res->elements + data_offset;
	     i < num_elements;
	     i++, element_data += data_size + data_offset)
		count += be64_to_cpu(*((u64 *) element_data));

	*countp = count;

	/* The next result is after the last result element. */
	अगर (next)
		*next = element_data - data_offset;

	वापस 0;
पूर्ण

अटल पूर्णांक single_24x7_request(काष्ठा perf_event *event, u64 *count)
अणु
	पूर्णांक ret;
	काष्ठा hv_24x7_request_buffer *request_buffer;
	काष्ठा hv_24x7_data_result_buffer *result_buffer;

	BUILD_BUG_ON(माप(*request_buffer) > 4096);
	BUILD_BUG_ON(माप(*result_buffer) > 4096);

	request_buffer = (व्योम *)get_cpu_var(hv_24x7_reqb);
	result_buffer = (व्योम *)get_cpu_var(hv_24x7_resb);

	init_24x7_request(request_buffer, result_buffer);

	ret = add_event_to_24x7_request(event, request_buffer);
	अगर (ret)
		जाओ out;

	ret = make_24x7_request(request_buffer, result_buffer);
	अगर (ret)
		जाओ out;

	/* process result from hcall */
	ret = get_count_from_result(event, result_buffer,
				    result_buffer->results, count, शून्य);

out:
	put_cpu_var(hv_24x7_reqb);
	put_cpu_var(hv_24x7_resb);
	वापस ret;
पूर्ण


अटल पूर्णांक h_24x7_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा hv_perf_caps caps;
	अचिन्हित करोमुख्य;
	अचिन्हित दीर्घ hret;
	u64 ct;

	/* Not our event */
	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	/* Unused areas must be 0 */
	अगर (event_get_reserved1(event) ||
	    event_get_reserved2(event) ||
	    event_get_reserved3(event)) अणु
		pr_devel("reserved set when forbidden 0x%llx(0x%llx) 0x%llx(0x%llx) 0x%llx(0x%llx)\n",
				event->attr.config,
				event_get_reserved1(event),
				event->attr.config1,
				event_get_reserved2(event),
				event->attr.config2,
				event_get_reserved3(event));
		वापस -EINVAL;
	पूर्ण

	/* no branch sampling */
	अगर (has_branch_stack(event))
		वापस -EOPNOTSUPP;

	/* offset must be 8 byte aligned */
	अगर (event_get_offset(event) % 8) अणु
		pr_devel("bad alignment\n");
		वापस -EINVAL;
	पूर्ण

	करोमुख्य = event_get_करोमुख्य(event);
	अगर (करोमुख्य >= HV_PERF_DOMAIN_MAX) अणु
		pr_devel("invalid domain %d\n", करोमुख्य);
		वापस -EINVAL;
	पूर्ण

	hret = hv_perf_caps_get(&caps);
	अगर (hret) अणु
		pr_devel("could not get capabilities: rc=%ld\n", hret);
		वापस -EIO;
	पूर्ण

	/* Physical करोमुख्यs & other lpars require extra capabilities */
	अगर (!caps.collect_privileged && (is_physical_करोमुख्य(करोमुख्य) ||
		(event_get_lpar(event) != event_get_lpar_max()))) अणु
		pr_devel("hv permissions disallow: is_physical_domain:%d, lpar=0x%llx\n",
				is_physical_करोमुख्य(करोमुख्य),
				event_get_lpar(event));
		वापस -EACCES;
	पूर्ण

	/* Get the initial value of the counter क्रम this event */
	अगर (single_24x7_request(event, &ct)) अणु
		pr_devel("test hcall failed\n");
		वापस -EIO;
	पूर्ण
	(व्योम)local64_xchg(&event->hw.prev_count, ct);

	वापस 0;
पूर्ण

अटल u64 h_24x7_get_value(काष्ठा perf_event *event)
अणु
	u64 ct;

	अगर (single_24x7_request(event, &ct))
		/* We checked this in event init, shouldn't fail here... */
		वापस 0;

	वापस ct;
पूर्ण

अटल व्योम update_event_count(काष्ठा perf_event *event, u64 now)
अणु
	s64 prev;

	prev = local64_xchg(&event->hw.prev_count, now);
	local64_add(now - prev, &event->count);
पूर्ण

अटल व्योम h_24x7_event_पढ़ो(काष्ठा perf_event *event)
अणु
	u64 now;
	काष्ठा hv_24x7_request_buffer *request_buffer;
	काष्ठा hv_24x7_hw *h24x7hw;
	पूर्णांक txn_flags;

	txn_flags = __this_cpu_पढ़ो(hv_24x7_txn_flags);

	/*
	 * If in a READ transaction, add this counter to the list of
	 * counters to पढ़ो during the next HCALL (i.e commit_txn()).
	 * If not in a READ transaction, go ahead and make the HCALL
	 * to पढ़ो this counter by itself.
	 */

	अगर (txn_flags & PERF_PMU_TXN_READ) अणु
		पूर्णांक i;
		पूर्णांक ret;

		अगर (__this_cpu_पढ़ो(hv_24x7_txn_err))
			वापस;

		request_buffer = (व्योम *)get_cpu_var(hv_24x7_reqb);

		ret = add_event_to_24x7_request(event, request_buffer);
		अगर (ret) अणु
			__this_cpu_ग_लिखो(hv_24x7_txn_err, ret);
		पूर्ण अन्यथा अणु
			/*
			 * Associate the event with the HCALL request index,
			 * so ->commit_txn() can quickly find/update count.
			 */
			i = request_buffer->num_requests - 1;

			h24x7hw = &get_cpu_var(hv_24x7_hw);
			h24x7hw->events[i] = event;
			put_cpu_var(h24x7hw);
		पूर्ण

		put_cpu_var(hv_24x7_reqb);
	पूर्ण अन्यथा अणु
		now = h_24x7_get_value(event);
		update_event_count(event, now);
	पूर्ण
पूर्ण

अटल व्योम h_24x7_event_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	अगर (flags & PERF_EF_RELOAD)
		local64_set(&event->hw.prev_count, h_24x7_get_value(event));
पूर्ण

अटल व्योम h_24x7_event_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	h_24x7_event_पढ़ो(event);
पूर्ण

अटल पूर्णांक h_24x7_event_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	अगर (flags & PERF_EF_START)
		h_24x7_event_start(event, flags);

	वापस 0;
पूर्ण

/*
 * 24x7 counters only support READ transactions. They are
 * always counting and करोnt need/support ADD transactions.
 * Cache the flags, but otherwise ignore transactions that
 * are not PERF_PMU_TXN_READ.
 */
अटल व्योम h_24x7_event_start_txn(काष्ठा pmu *pmu, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा hv_24x7_request_buffer *request_buffer;
	काष्ठा hv_24x7_data_result_buffer *result_buffer;

	/* We should not be called अगर we are alपढ़ोy in a txn */
	WARN_ON_ONCE(__this_cpu_पढ़ो(hv_24x7_txn_flags));

	__this_cpu_ग_लिखो(hv_24x7_txn_flags, flags);
	अगर (flags & ~PERF_PMU_TXN_READ)
		वापस;

	request_buffer = (व्योम *)get_cpu_var(hv_24x7_reqb);
	result_buffer = (व्योम *)get_cpu_var(hv_24x7_resb);

	init_24x7_request(request_buffer, result_buffer);

	put_cpu_var(hv_24x7_resb);
	put_cpu_var(hv_24x7_reqb);
पूर्ण

/*
 * Clean up transaction state.
 *
 * NOTE: Ignore state of request and result buffers क्रम now.
 *	 We will initialize them during the next पढ़ो/txn.
 */
अटल व्योम reset_txn(व्योम)
अणु
	__this_cpu_ग_लिखो(hv_24x7_txn_flags, 0);
	__this_cpu_ग_लिखो(hv_24x7_txn_err, 0);
पूर्ण

/*
 * 24x7 counters only support READ transactions. They are always counting
 * and करोnt need/support ADD transactions. Clear ->txn_flags but otherwise
 * ignore transactions that are not of type PERF_PMU_TXN_READ.
 *
 * For READ transactions, submit all pending 24x7 requests (i.e requests
 * that were queued by h_24x7_event_पढ़ो()), to the hypervisor and update
 * the event counts.
 */
अटल पूर्णांक h_24x7_event_commit_txn(काष्ठा pmu *pmu)
अणु
	काष्ठा hv_24x7_request_buffer *request_buffer;
	काष्ठा hv_24x7_data_result_buffer *result_buffer;
	काष्ठा hv_24x7_result *res, *next_res;
	u64 count;
	पूर्णांक i, ret, txn_flags;
	काष्ठा hv_24x7_hw *h24x7hw;

	txn_flags = __this_cpu_पढ़ो(hv_24x7_txn_flags);
	WARN_ON_ONCE(!txn_flags);

	ret = 0;
	अगर (txn_flags & ~PERF_PMU_TXN_READ)
		जाओ out;

	ret = __this_cpu_पढ़ो(hv_24x7_txn_err);
	अगर (ret)
		जाओ out;

	request_buffer = (व्योम *)get_cpu_var(hv_24x7_reqb);
	result_buffer = (व्योम *)get_cpu_var(hv_24x7_resb);

	ret = make_24x7_request(request_buffer, result_buffer);
	अगर (ret)
		जाओ put_reqb;

	h24x7hw = &get_cpu_var(hv_24x7_hw);

	/* Go through results in the result buffer to update event counts. */
	क्रम (i = 0, res = result_buffer->results;
	     i < result_buffer->num_results; i++, res = next_res) अणु
		काष्ठा perf_event *event = h24x7hw->events[res->result_ix];

		ret = get_count_from_result(event, result_buffer, res, &count,
					    &next_res);
		अगर (ret)
			अवरोध;

		update_event_count(event, count);
	पूर्ण

	put_cpu_var(hv_24x7_hw);

put_reqb:
	put_cpu_var(hv_24x7_resb);
	put_cpu_var(hv_24x7_reqb);
out:
	reset_txn();
	वापस ret;
पूर्ण

/*
 * 24x7 counters only support READ transactions. They are always counting
 * and करोnt need/support ADD transactions. However, regardless of type
 * of transaction, all we need to करो is cleanup, so we करोn't have to check
 * the type of transaction.
 */
अटल व्योम h_24x7_event_cancel_txn(काष्ठा pmu *pmu)
अणु
	WARN_ON_ONCE(!__this_cpu_पढ़ो(hv_24x7_txn_flags));
	reset_txn();
पूर्ण

अटल काष्ठा pmu h_24x7_pmu = अणु
	.task_ctx_nr = perf_invalid_context,

	.name = "hv_24x7",
	.attr_groups = attr_groups,
	.event_init  = h_24x7_event_init,
	.add         = h_24x7_event_add,
	.del         = h_24x7_event_stop,
	.start       = h_24x7_event_start,
	.stop        = h_24x7_event_stop,
	.पढ़ो        = h_24x7_event_पढ़ो,
	.start_txn   = h_24x7_event_start_txn,
	.commit_txn  = h_24x7_event_commit_txn,
	.cancel_txn  = h_24x7_event_cancel_txn,
	.capabilities = PERF_PMU_CAP_NO_EXCLUDE,
पूर्ण;

अटल पूर्णांक ppc_hv_24x7_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	अगर (cpumask_empty(&hv_24x7_cpumask))
		cpumask_set_cpu(cpu, &hv_24x7_cpumask);

	वापस 0;
पूर्ण

अटल पूर्णांक ppc_hv_24x7_cpu_offline(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक target;

	/* Check अगर निकासing cpu is used क्रम collecting 24x7 events */
	अगर (!cpumask_test_and_clear_cpu(cpu, &hv_24x7_cpumask))
		वापस 0;

	/* Find a new cpu to collect 24x7 events */
	target = cpumask_last(cpu_active_mask);

	अगर (target < 0 || target >= nr_cpu_ids) अणु
		pr_err("hv_24x7: CPU hotplug init failed\n");
		वापस -1;
	पूर्ण

	/* Migrate 24x7 events to the new target */
	cpumask_set_cpu(target, &hv_24x7_cpumask);
	perf_pmu_migrate_context(&h_24x7_pmu, cpu, target);

	वापस 0;
पूर्ण

अटल पूर्णांक hv_24x7_cpu_hotplug_init(व्योम)
अणु
	वापस cpuhp_setup_state(CPUHP_AP_PERF_POWERPC_HV_24x7_ONLINE,
			  "perf/powerpc/hv_24x7:online",
			  ppc_hv_24x7_cpu_online,
			  ppc_hv_24x7_cpu_offline);
पूर्ण

अटल पूर्णांक hv_24x7_init(व्योम)
अणु
	पूर्णांक r;
	अचिन्हित दीर्घ hret;
	काष्ठा hv_perf_caps caps;

	अगर (!firmware_has_feature(FW_FEATURE_LPAR)) अणु
		pr_debug("not a virtualized system, not enabling\n");
		वापस -ENODEV;
	पूर्ण अन्यथा अगर (!cur_cpu_spec->oprofile_cpu_type)
		वापस -ENODEV;

	/* POWER8 only supports v1, जबतक POWER9 only supports v2. */
	अगर (!म_भेद(cur_cpu_spec->oprofile_cpu_type, "ppc64/power8"))
		पूर्णांकerface_version = 1;
	अन्यथा अणु
		पूर्णांकerface_version = 2;

		/* SMT8 in POWER9 needs to aggregate result elements. */
		अगर (thपढ़ोs_per_core == 8)
			aggregate_result_elements = true;
	पूर्ण

	hret = hv_perf_caps_get(&caps);
	अगर (hret) अणु
		pr_debug("could not obtain capabilities, not enabling, rc=%ld\n",
				hret);
		वापस -ENODEV;
	पूर्ण

	hv_page_cache = kmem_cache_create("hv-page-4096", 4096, 4096, 0, शून्य);
	अगर (!hv_page_cache)
		वापस -ENOMEM;

	/* sampling not supported */
	h_24x7_pmu.capabilities |= PERF_PMU_CAP_NO_INTERRUPT;

	r = create_events_from_catalog(&event_group.attrs,
				   &event_desc_group.attrs,
				   &event_दीर्घ_desc_group.attrs);

	अगर (r)
		वापस r;

	/* init cpuhotplug */
	r = hv_24x7_cpu_hotplug_init();
	अगर (r)
		वापस r;

	r = perf_pmu_रेजिस्टर(&h_24x7_pmu, h_24x7_pmu.name, -1);
	अगर (r)
		वापस r;

	पढ़ो_24x7_sys_info();

	वापस 0;
पूर्ण

device_initcall(hv_24x7_init);
