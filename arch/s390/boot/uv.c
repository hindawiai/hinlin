<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <यंत्र/uv.h>
#समावेश <यंत्र/facility.h>
#समावेश <यंत्र/sections.h>

/* will be used in arch/s390/kernel/uv.c */
#अगर_घोषित CONFIG_PROTECTED_VIRTUALIZATION_GUEST
पूर्णांक __bootdata_preserved(prot_virt_guest);
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_KVM)
पूर्णांक __bootdata_preserved(prot_virt_host);
#पूर्ण_अगर
काष्ठा uv_info __bootdata_preserved(uv_info);

व्योम uv_query_info(व्योम)
अणु
	काष्ठा uv_cb_qui uvcb = अणु
		.header.cmd = UVC_CMD_QUI,
		.header.len = माप(uvcb)
	पूर्ण;

	अगर (!test_facility(158))
		वापस;

	/* rc==0x100 means that there is additional data we करो not process */
	अगर (uv_call(0, (uपूर्णांक64_t)&uvcb) && uvcb.header.rc != 0x100)
		वापस;

	अगर (IS_ENABLED(CONFIG_KVM)) अणु
		स_नकल(uv_info.inst_calls_list, uvcb.inst_calls_list, माप(uv_info.inst_calls_list));
		uv_info.uv_base_stor_len = uvcb.uv_base_stor_len;
		uv_info.guest_base_stor_len = uvcb.conf_base_phys_stor_len;
		uv_info.guest_virt_base_stor_len = uvcb.conf_base_virt_stor_len;
		uv_info.guest_virt_var_stor_len = uvcb.conf_virt_var_stor_len;
		uv_info.guest_cpu_stor_len = uvcb.cpu_stor_len;
		uv_info.max_sec_stor_addr = ALIGN(uvcb.max_guest_stor_addr, PAGE_SIZE);
		uv_info.max_num_sec_conf = uvcb.max_num_sec_conf;
		uv_info.max_guest_cpu_id = uvcb.max_guest_cpu_id;
	पूर्ण

#अगर_घोषित CONFIG_PROTECTED_VIRTUALIZATION_GUEST
	अगर (test_bit_inv(BIT_UVC_CMD_SET_SHARED_ACCESS, (अचिन्हित दीर्घ *)uvcb.inst_calls_list) &&
	    test_bit_inv(BIT_UVC_CMD_REMOVE_SHARED_ACCESS, (अचिन्हित दीर्घ *)uvcb.inst_calls_list))
		prot_virt_guest = 1;
#पूर्ण_अगर
पूर्ण
