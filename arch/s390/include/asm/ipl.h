<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * s390 (re)ipl support
 *
 * Copyright IBM Corp. 2007
 */

#अगर_अघोषित _ASM_S390_IPL_H
#घोषणा _ASM_S390_IPL_H

#समावेश <यंत्र/lowcore.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/cपन.स>
#समावेश <यंत्र/setup.h>
#समावेश <uapi/यंत्र/ipl.h>

काष्ठा ipl_parameter_block अणु
	काष्ठा ipl_pl_hdr hdr;
	जोड़ अणु
		काष्ठा ipl_pb_hdr pb0_hdr;
		काष्ठा ipl_pb0_common common;
		काष्ठा ipl_pb0_fcp fcp;
		काष्ठा ipl_pb0_ccw ccw;
		काष्ठा ipl_pb0_nvme nvme;
		अक्षर raw[PAGE_SIZE - माप(काष्ठा ipl_pl_hdr)];
	पूर्ण;
पूर्ण __packed __aligned(PAGE_SIZE);

#घोषणा NSS_NAME_SIZE 8

#घोषणा IPL_BP_FCP_LEN (माप(काष्ठा ipl_pl_hdr) + \
			      माप(काष्ठा ipl_pb0_fcp))
#घोषणा IPL_BP0_FCP_LEN (माप(काष्ठा ipl_pb0_fcp))

#घोषणा IPL_BP_NVME_LEN (माप(काष्ठा ipl_pl_hdr) + \
			      माप(काष्ठा ipl_pb0_nvme))
#घोषणा IPL_BP0_NVME_LEN (माप(काष्ठा ipl_pb0_nvme))

#घोषणा IPL_BP_CCW_LEN (माप(काष्ठा ipl_pl_hdr) + \
			      माप(काष्ठा ipl_pb0_ccw))
#घोषणा IPL_BP0_CCW_LEN (माप(काष्ठा ipl_pb0_ccw))

#घोषणा IPL_MAX_SUPPORTED_VERSION (0)

#घोषणा IPL_RB_CERT_UNKNOWN ((अचिन्हित लघु)-1)

#घोषणा DIAG308_VMPARM_SIZE (64)
#घोषणा DIAG308_SCPDATA_OFFSET दुरत्व(काष्ठा ipl_parameter_block, \
					fcp.scp_data)
#घोषणा DIAG308_SCPDATA_SIZE (PAGE_SIZE - DIAG308_SCPDATA_OFFSET)

काष्ठा save_area;
काष्ठा save_area * __init save_area_alloc(bool is_boot_cpu);
काष्ठा save_area * __init save_area_boot_cpu(व्योम);
व्योम __init save_area_add_regs(काष्ठा save_area *, व्योम *regs);
व्योम __init save_area_add_vxrs(काष्ठा save_area *, __vector128 *vxrs);

बाह्य व्योम s390_reset_प्रणाली(व्योम);
बाह्य माप_प्रकार ipl_block_get_ascii_vmparm(अक्षर *dest, माप_प्रकार size,
					 स्थिर काष्ठा ipl_parameter_block *ipb);

क्रमागत ipl_type अणु
	IPL_TYPE_UNKNOWN	= 1,
	IPL_TYPE_CCW		= 2,
	IPL_TYPE_FCP		= 4,
	IPL_TYPE_FCP_DUMP	= 8,
	IPL_TYPE_NSS		= 16,
	IPL_TYPE_NVME		= 32,
	IPL_TYPE_NVME_DUMP	= 64,
पूर्ण;

काष्ठा ipl_info
अणु
	क्रमागत ipl_type type;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा ccw_dev_id dev_id;
		पूर्ण ccw;
		काष्ठा अणु
			काष्ठा ccw_dev_id dev_id;
			u64 wwpn;
			u64 lun;
		पूर्ण fcp;
		काष्ठा अणु
			u32 fid;
			u32 nsid;
		पूर्ण nvme;
		काष्ठा अणु
			अक्षर name[NSS_NAME_SIZE + 1];
		पूर्ण nss;
	पूर्ण data;
पूर्ण;

बाह्य काष्ठा ipl_info ipl_info;
बाह्य व्योम setup_ipl(व्योम);
बाह्य व्योम set_os_info_reipl_block(व्योम);

अटल अंतरभूत bool is_ipl_type_dump(व्योम)
अणु
	वापस (ipl_info.type == IPL_TYPE_FCP_DUMP) ||
		(ipl_info.type == IPL_TYPE_NVME_DUMP);
पूर्ण

काष्ठा ipl_report अणु
	काष्ठा ipl_parameter_block *ipib;
	काष्ठा list_head components;
	काष्ठा list_head certअगरicates;
	माप_प्रकार size;
पूर्ण;

काष्ठा ipl_report_component अणु
	काष्ठा list_head list;
	काष्ठा ipl_rb_component_entry entry;
पूर्ण;

काष्ठा ipl_report_certअगरicate अणु
	काष्ठा list_head list;
	काष्ठा ipl_rb_certअगरicate_entry entry;
	व्योम *key;
पूर्ण;

काष्ठा kexec_buf;
काष्ठा ipl_report *ipl_report_init(काष्ठा ipl_parameter_block *ipib);
व्योम *ipl_report_finish(काष्ठा ipl_report *report);
पूर्णांक ipl_report_मुक्त(काष्ठा ipl_report *report);
पूर्णांक ipl_report_add_component(काष्ठा ipl_report *report, काष्ठा kexec_buf *kbuf,
			     अचिन्हित अक्षर flags, अचिन्हित लघु cert);
पूर्णांक ipl_report_add_certअगरicate(काष्ठा ipl_report *report, व्योम *key,
			       अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len);

/*
 * DIAG 308 support
 */
क्रमागत diag308_subcode  अणु
	DIAG308_REL_HSA = 2,
	DIAG308_LOAD_CLEAR = 3,
	DIAG308_LOAD_NORMAL_DUMP = 4,
	DIAG308_SET = 5,
	DIAG308_STORE = 6,
	DIAG308_LOAD_NORMAL = 7,
पूर्ण;

क्रमागत diag308_rc अणु
	DIAG308_RC_OK		= 0x0001,
	DIAG308_RC_NOCONFIG	= 0x0102,
पूर्ण;

बाह्य पूर्णांक diag308(अचिन्हित दीर्घ subcode, व्योम *addr);
बाह्य व्योम store_status(व्योम (*fn)(व्योम *), व्योम *data);
बाह्य व्योम lgr_info_log(व्योम);

#पूर्ण_अगर /* _ASM_S390_IPL_H */
