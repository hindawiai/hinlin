<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Ultravisor Interfaces
 *
 * Copyright IBM Corp. 2019
 *
 * Author(s):
 *	Vasily Gorbik <gor@linux.ibm.com>
 *	Janosch Frank <frankja@linux.ibm.com>
 */
#अगर_अघोषित _ASM_S390_UV_H
#घोषणा _ASM_S390_UV_H

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/bug.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/gmap.h>

#घोषणा UVC_RC_EXECUTED		0x0001
#घोषणा UVC_RC_INV_CMD		0x0002
#घोषणा UVC_RC_INV_STATE	0x0003
#घोषणा UVC_RC_INV_LEN		0x0005
#घोषणा UVC_RC_NO_RESUME	0x0007
#घोषणा UVC_RC_NEED_DESTROY	0x8000

#घोषणा UVC_CMD_QUI			0x0001
#घोषणा UVC_CMD_INIT_UV			0x000f
#घोषणा UVC_CMD_CREATE_SEC_CONF		0x0100
#घोषणा UVC_CMD_DESTROY_SEC_CONF	0x0101
#घोषणा UVC_CMD_CREATE_SEC_CPU		0x0120
#घोषणा UVC_CMD_DESTROY_SEC_CPU		0x0121
#घोषणा UVC_CMD_CONV_TO_SEC_STOR	0x0200
#घोषणा UVC_CMD_CONV_FROM_SEC_STOR	0x0201
#घोषणा UVC_CMD_DESTR_SEC_STOR		0x0202
#घोषणा UVC_CMD_SET_SEC_CONF_PARAMS	0x0300
#घोषणा UVC_CMD_UNPACK_IMG		0x0301
#घोषणा UVC_CMD_VERIFY_IMG		0x0302
#घोषणा UVC_CMD_CPU_RESET		0x0310
#घोषणा UVC_CMD_CPU_RESET_INITIAL	0x0311
#घोषणा UVC_CMD_PREPARE_RESET		0x0320
#घोषणा UVC_CMD_CPU_RESET_CLEAR		0x0321
#घोषणा UVC_CMD_CPU_SET_STATE		0x0330
#घोषणा UVC_CMD_SET_UNSHARE_ALL		0x0340
#घोषणा UVC_CMD_PIN_PAGE_SHARED		0x0341
#घोषणा UVC_CMD_UNPIN_PAGE_SHARED	0x0342
#घोषणा UVC_CMD_SET_SHARED_ACCESS	0x1000
#घोषणा UVC_CMD_REMOVE_SHARED_ACCESS	0x1001

/* Bits in installed uv calls */
क्रमागत uv_cmds_inst अणु
	BIT_UVC_CMD_QUI = 0,
	BIT_UVC_CMD_INIT_UV = 1,
	BIT_UVC_CMD_CREATE_SEC_CONF = 2,
	BIT_UVC_CMD_DESTROY_SEC_CONF = 3,
	BIT_UVC_CMD_CREATE_SEC_CPU = 4,
	BIT_UVC_CMD_DESTROY_SEC_CPU = 5,
	BIT_UVC_CMD_CONV_TO_SEC_STOR = 6,
	BIT_UVC_CMD_CONV_FROM_SEC_STOR = 7,
	BIT_UVC_CMD_SET_SHARED_ACCESS = 8,
	BIT_UVC_CMD_REMOVE_SHARED_ACCESS = 9,
	BIT_UVC_CMD_SET_SEC_PARMS = 11,
	BIT_UVC_CMD_UNPACK_IMG = 13,
	BIT_UVC_CMD_VERIFY_IMG = 14,
	BIT_UVC_CMD_CPU_RESET = 15,
	BIT_UVC_CMD_CPU_RESET_INITIAL = 16,
	BIT_UVC_CMD_CPU_SET_STATE = 17,
	BIT_UVC_CMD_PREPARE_RESET = 18,
	BIT_UVC_CMD_CPU_PERFORM_CLEAR_RESET = 19,
	BIT_UVC_CMD_UNSHARE_ALL = 20,
	BIT_UVC_CMD_PIN_PAGE_SHARED = 21,
	BIT_UVC_CMD_UNPIN_PAGE_SHARED = 22,
पूर्ण;

काष्ठा uv_cb_header अणु
	u16 len;
	u16 cmd;	/* Command Code */
	u16 rc;		/* Response Code */
	u16 rrc;	/* Return Reason Code */
पूर्ण __packed __aligned(8);

/* Query Ultravisor Inक्रमmation */
काष्ठा uv_cb_qui अणु
	काष्ठा uv_cb_header header;
	u64 reserved08;
	u64 inst_calls_list[4];
	u64 reserved30[2];
	u64 uv_base_stor_len;
	u64 reserved48;
	u64 conf_base_phys_stor_len;
	u64 conf_base_virt_stor_len;
	u64 conf_virt_var_stor_len;
	u64 cpu_stor_len;
	u32 reserved70[3];
	u32 max_num_sec_conf;
	u64 max_guest_stor_addr;
	u8  reserved88[158 - 136];
	u16 max_guest_cpu_id;
	u8  reserveda0[200 - 160];
पूर्ण __packed __aligned(8);

/* Initialize Ultravisor */
काष्ठा uv_cb_init अणु
	काष्ठा uv_cb_header header;
	u64 reserved08[2];
	u64 stor_origin;
	u64 stor_len;
	u64 reserved28[4];
पूर्ण __packed __aligned(8);

/* Create Guest Configuration */
काष्ठा uv_cb_cgc अणु
	काष्ठा uv_cb_header header;
	u64 reserved08[2];
	u64 guest_handle;
	u64 conf_base_stor_origin;
	u64 conf_virt_stor_origin;
	u64 reserved30;
	u64 guest_stor_origin;
	u64 guest_stor_len;
	u64 guest_sca;
	u64 guest_asce;
	u64 reserved58[5];
पूर्ण __packed __aligned(8);

/* Create Secure CPU */
काष्ठा uv_cb_csc अणु
	काष्ठा uv_cb_header header;
	u64 reserved08[2];
	u64 cpu_handle;
	u64 guest_handle;
	u64 stor_origin;
	u8  reserved30[6];
	u16 num;
	u64 state_origin;
	u64 reserved40[4];
पूर्ण __packed __aligned(8);

/* Convert to Secure */
काष्ठा uv_cb_cts अणु
	काष्ठा uv_cb_header header;
	u64 reserved08[2];
	u64 guest_handle;
	u64 gaddr;
पूर्ण __packed __aligned(8);

/* Convert from Secure / Pin Page Shared */
काष्ठा uv_cb_cfs अणु
	काष्ठा uv_cb_header header;
	u64 reserved08[2];
	u64 paddr;
पूर्ण __packed __aligned(8);

/* Set Secure Config Parameter */
काष्ठा uv_cb_ssc अणु
	काष्ठा uv_cb_header header;
	u64 reserved08[2];
	u64 guest_handle;
	u64 sec_header_origin;
	u32 sec_header_len;
	u32 reserved2c;
	u64 reserved30[4];
पूर्ण __packed __aligned(8);

/* Unpack */
काष्ठा uv_cb_unp अणु
	काष्ठा uv_cb_header header;
	u64 reserved08[2];
	u64 guest_handle;
	u64 gaddr;
	u64 tweak[2];
	u64 reserved38[3];
पूर्ण __packed __aligned(8);

#घोषणा PV_CPU_STATE_OPR	1
#घोषणा PV_CPU_STATE_STP	2
#घोषणा PV_CPU_STATE_CHKSTP	3
#घोषणा PV_CPU_STATE_OPR_LOAD	5

काष्ठा uv_cb_cpu_set_state अणु
	काष्ठा uv_cb_header header;
	u64 reserved08[2];
	u64 cpu_handle;
	u8  reserved20[7];
	u8  state;
	u64 reserved28[5];
पूर्ण;

/*
 * A common UV call काष्ठा क्रम calls that take no payload
 * Examples:
 * Destroy cpu/config
 * Verअगरy
 */
काष्ठा uv_cb_nodata अणु
	काष्ठा uv_cb_header header;
	u64 reserved08[2];
	u64 handle;
	u64 reserved20[4];
पूर्ण __packed __aligned(8);

/* Set Shared Access */
काष्ठा uv_cb_share अणु
	काष्ठा uv_cb_header header;
	u64 reserved08[3];
	u64 paddr;
	u64 reserved28;
पूर्ण __packed __aligned(8);

अटल अंतरभूत पूर्णांक __uv_call(अचिन्हित दीर्घ r1, अचिन्हित दीर्घ r2)
अणु
	पूर्णांक cc;

	यंत्र अस्थिर(
		"	.insn rrf,0xB9A40000,%[r1],%[r2],0,0\n"
		"	ipm	%[cc]\n"
		"	srl	%[cc],28\n"
		: [cc] "=d" (cc)
		: [r1] "a" (r1), [r2] "a" (r2)
		: "memory", "cc");
	वापस cc;
पूर्ण

अटल अंतरभूत पूर्णांक uv_call(अचिन्हित दीर्घ r1, अचिन्हित दीर्घ r2)
अणु
	पूर्णांक cc;

	करो अणु
		cc = __uv_call(r1, r2);
	पूर्ण जबतक (cc > 1);
	वापस cc;
पूर्ण

/* Low level uv_call that aव्योमs stalls क्रम दीर्घ running busy conditions  */
अटल अंतरभूत पूर्णांक uv_call_sched(अचिन्हित दीर्घ r1, अचिन्हित दीर्घ r2)
अणु
	पूर्णांक cc;

	करो अणु
		cc = __uv_call(r1, r2);
		cond_resched();
	पूर्ण जबतक (cc > 1);
	वापस cc;
पूर्ण

/*
 * special variant of uv_call that only transports the cpu or guest
 * handle and the command, like destroy or verअगरy.
 */
अटल अंतरभूत पूर्णांक uv_cmd_nodata(u64 handle, u16 cmd, u16 *rc, u16 *rrc)
अणु
	काष्ठा uv_cb_nodata uvcb = अणु
		.header.cmd = cmd,
		.header.len = माप(uvcb),
		.handle = handle,
	पूर्ण;
	पूर्णांक cc;

	WARN(!handle, "No handle provided to Ultravisor call cmd %x\n", cmd);
	cc = uv_call_sched(0, (u64)&uvcb);
	*rc = uvcb.header.rc;
	*rrc = uvcb.header.rrc;
	वापस cc ? -EINVAL : 0;
पूर्ण

काष्ठा uv_info अणु
	अचिन्हित दीर्घ inst_calls_list[4];
	अचिन्हित दीर्घ uv_base_stor_len;
	अचिन्हित दीर्घ guest_base_stor_len;
	अचिन्हित दीर्घ guest_virt_base_stor_len;
	अचिन्हित दीर्घ guest_virt_var_stor_len;
	अचिन्हित दीर्घ guest_cpu_stor_len;
	अचिन्हित दीर्घ max_sec_stor_addr;
	अचिन्हित पूर्णांक max_num_sec_conf;
	अचिन्हित लघु max_guest_cpu_id;
पूर्ण;

बाह्य काष्ठा uv_info uv_info;

#अगर_घोषित CONFIG_PROTECTED_VIRTUALIZATION_GUEST
बाह्य पूर्णांक prot_virt_guest;

अटल अंतरभूत पूर्णांक is_prot_virt_guest(व्योम)
अणु
	वापस prot_virt_guest;
पूर्ण

अटल अंतरभूत पूर्णांक share(अचिन्हित दीर्घ addr, u16 cmd)
अणु
	काष्ठा uv_cb_share uvcb = अणु
		.header.cmd = cmd,
		.header.len = माप(uvcb),
		.paddr = addr
	पूर्ण;

	अगर (!is_prot_virt_guest())
		वापस -EOPNOTSUPP;
	/*
	 * Sharing is page wise, अगर we encounter addresses that are
	 * not page aligned, we assume something went wrong. If
	 * दो_स्मृतिed काष्ठाs are passed to this function, we could leak
	 * data to the hypervisor.
	 */
	BUG_ON(addr & ~PAGE_MASK);

	अगर (!uv_call(0, (u64)&uvcb))
		वापस 0;
	वापस -EINVAL;
पूर्ण

/*
 * Guest 2 request to the Ultravisor to make a page shared with the
 * hypervisor क्रम IO.
 *
 * @addr: Real or असलolute address of the page to be shared
 */
अटल अंतरभूत पूर्णांक uv_set_shared(अचिन्हित दीर्घ addr)
अणु
	वापस share(addr, UVC_CMD_SET_SHARED_ACCESS);
पूर्ण

/*
 * Guest 2 request to the Ultravisor to make a page unshared.
 *
 * @addr: Real or असलolute address of the page to be unshared
 */
अटल अंतरभूत पूर्णांक uv_हटाओ_shared(अचिन्हित दीर्घ addr)
अणु
	वापस share(addr, UVC_CMD_REMOVE_SHARED_ACCESS);
पूर्ण

#अन्यथा
#घोषणा is_prot_virt_guest() 0
अटल अंतरभूत पूर्णांक uv_set_shared(अचिन्हित दीर्घ addr) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक uv_हटाओ_shared(अचिन्हित दीर्घ addr) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_KVM)
बाह्य पूर्णांक prot_virt_host;

अटल अंतरभूत पूर्णांक is_prot_virt_host(व्योम)
अणु
	वापस prot_virt_host;
पूर्ण

पूर्णांक gmap_make_secure(काष्ठा gmap *gmap, अचिन्हित दीर्घ gaddr, व्योम *uvcb);
पूर्णांक uv_destroy_page(अचिन्हित दीर्घ paddr);
पूर्णांक uv_convert_from_secure(अचिन्हित दीर्घ paddr);
पूर्णांक gmap_convert_to_secure(काष्ठा gmap *gmap, अचिन्हित दीर्घ gaddr);

व्योम setup_uv(व्योम);
व्योम adjust_to_uv_max(अचिन्हित दीर्घ *vmax);
#अन्यथा
#घोषणा is_prot_virt_host() 0
अटल अंतरभूत व्योम setup_uv(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम adjust_to_uv_max(अचिन्हित दीर्घ *vmax) अणुपूर्ण

अटल अंतरभूत पूर्णांक uv_destroy_page(अचिन्हित दीर्घ paddr)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक uv_convert_from_secure(अचिन्हित दीर्घ paddr)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PROTECTED_VIRTUALIZATION_GUEST) || IS_ENABLED(CONFIG_KVM)
व्योम uv_query_info(व्योम);
#अन्यथा
अटल अंतरभूत व्योम uv_query_info(व्योम) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_S390_UV_H */
