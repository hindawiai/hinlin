<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Simple wrappers around HVM functions */
#अगर_अघोषित XEN_HVM_H__
#घोषणा XEN_HVM_H__

#समावेश <xen/पूर्णांकerface/hvm/params.h>
#समावेश <यंत्र/xen/hypercall.h>

अटल स्थिर अक्षर *param_name(पूर्णांक op)
अणु
#घोषणा PARAM(x) [HVM_PARAM_##x] = #x
	अटल स्थिर अक्षर *स्थिर names[] = अणु
		PARAM(CALLBACK_IRQ),
		PARAM(STORE_PFN),
		PARAM(STORE_EVTCHN),
		PARAM(PAE_ENABLED),
		PARAM(IOREQ_PFN),
		PARAM(BUFIOREQ_PFN),
		PARAM(TIMER_MODE),
		PARAM(HPET_ENABLED),
		PARAM(IDENT_PT),
		PARAM(DM_DOMAIN),
		PARAM(ACPI_S_STATE),
		PARAM(VM86_TSS),
		PARAM(VPT_ALIGN),
		PARAM(CONSOLE_PFN),
		PARAM(CONSOLE_EVTCHN),
	पूर्ण;
#अघोषित PARAM

	अगर (op >= ARRAY_SIZE(names))
		वापस "unknown";

	अगर (!names[op])
		वापस "reserved";

	वापस names[op];
पूर्ण
अटल अंतरभूत पूर्णांक hvm_get_parameter(पूर्णांक idx, uपूर्णांक64_t *value)
अणु
	काष्ठा xen_hvm_param xhv;
	पूर्णांक r;

	xhv.करोmid = DOMID_SELF;
	xhv.index = idx;
	r = HYPERVISOR_hvm_op(HVMOP_get_param, &xhv);
	अगर (r < 0) अणु
		pr_err("Cannot get hvm parameter %s (%d): %d!\n",
		       param_name(idx), idx, r);
		वापस r;
	पूर्ण
	*value = xhv.value;
	वापस r;
पूर्ण

#घोषणा HVM_CALLBACK_VIA_TYPE_VECTOR 0x2
#घोषणा HVM_CALLBACK_VIA_TYPE_SHIFT 56
#घोषणा HVM_CALLBACK_VECTOR(x) (((uपूर्णांक64_t)HVM_CALLBACK_VIA_TYPE_VECTOR)<<\
		HVM_CALLBACK_VIA_TYPE_SHIFT | (x))

व्योम xen_setup_callback_vector(व्योम);

#पूर्ण_अगर /* XEN_HVM_H__ */
