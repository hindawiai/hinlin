<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/thपढ़ो_info.h>

#समावेश <यंत्र/x86_init.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/xen/hypercall.h>

#समावेश <xen/xen.h>
#समावेश <xen/पूर्णांकerface/physdev.h>
#समावेश "xen-ops.h"
#समावेश "pmu.h"
#समावेश "smp.h"

अटल अचिन्हित पूर्णांक xen_io_apic_पढ़ो(अचिन्हित apic, अचिन्हित reg)
अणु
	काष्ठा physdev_apic apic_op;
	पूर्णांक ret;

	apic_op.apic_physbase = mpc_ioapic_addr(apic);
	apic_op.reg = reg;
	ret = HYPERVISOR_physdev_op(PHYSDEVOP_apic_पढ़ो, &apic_op);
	अगर (!ret)
		वापस apic_op.value;

	/* fallback to वापस an emulated IO_APIC values */
	अगर (reg == 0x1)
		वापस 0x00170020;
	अन्यथा अगर (reg == 0x0)
		वापस apic << 24;

	वापस 0xfd;
पूर्ण

अटल u32 xen_set_apic_id(अचिन्हित पूर्णांक x)
अणु
	WARN_ON(1);
	वापस x;
पूर्ण

अटल अचिन्हित पूर्णांक xen_get_apic_id(अचिन्हित दीर्घ x)
अणु
	वापस ((x)>>24) & 0xFFu;
पूर्ण

अटल u32 xen_apic_पढ़ो(u32 reg)
अणु
	काष्ठा xen_platक्रमm_op op = अणु
		.cmd = XENPF_get_cpuinfo,
		.पूर्णांकerface_version = XENPF_INTERFACE_VERSION,
		.u.pcpu_info.xen_cpuid = 0,
	पूर्ण;
	पूर्णांक ret = 0;

	/* Shouldn't need this as APIC is turned off क्रम PV, and we only
	 * get called on the bootup processor. But just in हाल. */
	अगर (!xen_initial_करोमुख्य() || smp_processor_id())
		वापस 0;

	अगर (reg == APIC_LVR)
		वापस 0x14;
	अगर (reg != APIC_ID)
		वापस 0;

	ret = HYPERVISOR_platक्रमm_op(&op);
	अगर (ret)
		op.u.pcpu_info.apic_id = BAD_APICID;

	वापस op.u.pcpu_info.apic_id << 24;
पूर्ण

अटल व्योम xen_apic_ग_लिखो(u32 reg, u32 val)
अणु
	अगर (reg == APIC_LVTPC) अणु
		(व्योम)pmu_apic_update(reg);
		वापस;
	पूर्ण

	/* Warn to see अगर there's any stray references */
	WARN(1,"register: %x, value: %x\n", reg, val);
पूर्ण

अटल u64 xen_apic_icr_पढ़ो(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम xen_apic_icr_ग_लिखो(u32 low, u32 id)
अणु
	/* Warn to see अगर there's any stray references */
	WARN_ON(1);
पूर्ण

अटल u32 xen_safe_apic_रुको_icr_idle(व्योम)
अणु
        वापस 0;
पूर्ण

अटल पूर्णांक xen_apic_probe_pv(व्योम)
अणु
	अगर (xen_pv_करोमुख्य())
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक xen_madt_oem_check(अक्षर *oem_id, अक्षर *oem_table_id)
अणु
	वापस xen_pv_करोमुख्य();
पूर्ण

अटल पूर्णांक xen_id_always_valid(u32 apicid)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक xen_id_always_रेजिस्टरed(व्योम)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक xen_phys_pkg_id(पूर्णांक initial_apic_id, पूर्णांक index_msb)
अणु
	वापस initial_apic_id >> index_msb;
पूर्ण

अटल व्योम xen_noop(व्योम)
अणु
पूर्ण

अटल व्योम xen_silent_inquire(पूर्णांक apicid)
अणु
पूर्ण

अटल पूर्णांक xen_cpu_present_to_apicid(पूर्णांक cpu)
अणु
	अगर (cpu_present(cpu))
		वापस cpu_data(cpu).apicid;
	अन्यथा
		वापस BAD_APICID;
पूर्ण

अटल काष्ठा apic xen_pv_apic = अणु
	.name 				= "Xen PV",
	.probe 				= xen_apic_probe_pv,
	.acpi_madt_oem_check		= xen_madt_oem_check,
	.apic_id_valid 			= xen_id_always_valid,
	.apic_id_रेजिस्टरed 		= xen_id_always_रेजिस्टरed,

	/* .delivery_mode and .dest_mode_logical not used by XENPV */

	.disable_esr			= 0,

	.check_apicid_used		= शेष_check_apicid_used, /* Used on 32-bit */
	.init_apic_ldr			= xen_noop, /* setup_local_APIC calls it */
	.ioapic_phys_id_map		= शेष_ioapic_phys_id_map, /* Used on 32-bit */
	.setup_apic_routing		= शून्य,
	.cpu_present_to_apicid		= xen_cpu_present_to_apicid,
	.apicid_to_cpu_present		= physid_set_mask_of_physid, /* Used on 32-bit */
	.check_phys_apicid_present	= शेष_check_phys_apicid_present, /* smp_sanity_check needs it */
	.phys_pkg_id			= xen_phys_pkg_id, /* detect_ht */

	.get_apic_id 			= xen_get_apic_id,
	.set_apic_id 			= xen_set_apic_id, /* Can be शून्य on 32-bit. */

	.calc_dest_apicid		= apic_flat_calc_apicid,

#अगर_घोषित CONFIG_SMP
	.send_IPI_mask 			= xen_send_IPI_mask,
	.send_IPI_mask_allbutself 	= xen_send_IPI_mask_allbutself,
	.send_IPI_allbutself 		= xen_send_IPI_allbutself,
	.send_IPI_all 			= xen_send_IPI_all,
	.send_IPI_self 			= xen_send_IPI_self,
#पूर्ण_अगर
	/* .रुको_क्रम_init_deनिश्चित- used  by AP bootup - smp_callin which we करोn't use */
	.inquire_remote_apic		= xen_silent_inquire,

	.पढ़ो				= xen_apic_पढ़ो,
	.ग_लिखो				= xen_apic_ग_लिखो,
	.eoi_ग_लिखो			= xen_apic_ग_लिखो,

	.icr_पढ़ो 			= xen_apic_icr_पढ़ो,
	.icr_ग_लिखो 			= xen_apic_icr_ग_लिखो,
	.रुको_icr_idle 			= xen_noop,
	.safe_रुको_icr_idle 		= xen_safe_apic_रुको_icr_idle,
पूर्ण;

अटल व्योम __init xen_apic_check(व्योम)
अणु
	अगर (apic == &xen_pv_apic)
		वापस;

	pr_info("Switched APIC routing from %s to %s.\n", apic->name,
		xen_pv_apic.name);
	apic = &xen_pv_apic;
पूर्ण
व्योम __init xen_init_apic(व्योम)
अणु
	x86_apic_ops.io_apic_पढ़ो = xen_io_apic_पढ़ो;
	/* On PV guests the APIC CPUID bit is disabled so none of the
	 * routines end up executing. */
	अगर (!xen_initial_करोमुख्य())
		apic = &xen_pv_apic;

	x86_platक्रमm.apic_post_init = xen_apic_check;
पूर्ण
apic_driver(xen_pv_apic);
