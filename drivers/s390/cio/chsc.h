<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित S390_CHSC_H
#घोषणा S390_CHSC_H

#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <यंत्र/css_अक्षरs.h>
#समावेश <यंत्र/chpid.h>
#समावेश <यंत्र/chsc.h>
#समावेश <यंत्र/schid.h>
#समावेश <यंत्र/qdपन.स>

#घोषणा CHSC_SDA_OC_MSS   0x2

#घोषणा NR_MEASUREMENT_CHARS 5
काष्ठा cmg_अक्षरs अणु
	u32 values[NR_MEASUREMENT_CHARS];
पूर्ण;

#घोषणा NR_MEASUREMENT_ENTRIES 8
काष्ठा cmg_entry अणु
	u32 values[NR_MEASUREMENT_ENTRIES];
पूर्ण;

काष्ठा channel_path_desc_fmt1 अणु
	u8 flags;
	u8 lsn;
	u8 desc;
	u8 chpid;
	u32:16;
	u8 esc;
	u8 chpp;
	u32 unused[2];
	u16 chid;
	u32:16;
	u16 mdc;
	u16:13;
	u8 r:1;
	u8 s:1;
	u8 f:1;
	u32 zeros[2];
पूर्ण;

काष्ठा channel_path_desc_fmt3 अणु
	काष्ठा channel_path_desc_fmt1 fmt1_desc;
	u8 util_str[64];
पूर्ण;

काष्ठा channel_path;

काष्ठा css_chsc_अक्षर अणु
	u64 res;
	u64 : 20;
	u32 secm : 1; /* bit 84 */
	u32 : 1;
	u32 scmc : 1; /* bit 86 */
	u32 : 20;
	u32 scssc : 1;  /* bit 107 */
	u32 scsscf : 1; /* bit 108 */
	u32:7;
	u32 pnso:1; /* bit 116 */
	u32:11;
पूर्ण __packed;

बाह्य काष्ठा css_chsc_अक्षर css_chsc_अक्षरacteristics;

काष्ठा chsc_ssd_info अणु
	u8 path_mask;
	u8 fla_valid_mask;
	काष्ठा chp_id chpid[8];
	u16 fla[8];
पूर्ण;

काष्ठा chsc_ssqd_area अणु
	काष्ठा chsc_header request;
	u16:10;
	u8 ssid:2;
	u8 fmt:4;
	u16 first_sch;
	u16:16;
	u16 last_sch;
	u32:32;
	काष्ठा chsc_header response;
	u32:32;
	काष्ठा qdio_ssqd_desc qdio_ssqd;
पूर्ण __packed __aligned(PAGE_SIZE);

काष्ठा chsc_scssc_area अणु
	काष्ठा chsc_header request;
	u16 operation_code;
	u16:16;
	u32:32;
	u32:32;
	u64 summary_indicator_addr;
	u64 subchannel_indicator_addr;
	u32 ks:4;
	u32 kc:4;
	u32:21;
	u32 isc:3;
	u32 word_with_d_bit;
	u32:32;
	काष्ठा subchannel_id schid;
	u32 reserved[1004];
	काष्ठा chsc_header response;
	u32:32;
पूर्ण __packed __aligned(PAGE_SIZE);

काष्ठा chsc_scpd अणु
	काष्ठा chsc_header request;
	u32:2;
	u32 m:1;
	u32 c:1;
	u32 fmt:4;
	u32 cssid:8;
	u32:4;
	u32 rfmt:4;
	u32 first_chpid:8;
	u32:24;
	u32 last_chpid:8;
	u32 zeroes1;
	काष्ठा chsc_header response;
	u32:32;
	u8 data[0];
पूर्ण __packed __aligned(PAGE_SIZE);

काष्ठा chsc_sda_area अणु
	काष्ठा chsc_header request;
	u8 :4;
	u8 क्रमmat:4;
	u8 :8;
	u16 operation_code;
	u32 :32;
	u32 :32;
	u32 operation_data_area[252];
	काष्ठा chsc_header response;
	u32 :4;
	u32 क्रमmat2:4;
	u32 :24;
पूर्ण __packed __aligned(PAGE_SIZE);

बाह्य पूर्णांक chsc_get_ssd_info(काष्ठा subchannel_id schid,
			     काष्ठा chsc_ssd_info *ssd);
बाह्य पूर्णांक chsc_determine_css_अक्षरacteristics(व्योम);
बाह्य पूर्णांक chsc_init(व्योम);
बाह्य व्योम chsc_init_cleanup(व्योम);

पूर्णांक __chsc_enable_facility(काष्ठा chsc_sda_area *sda_area, पूर्णांक operation_code);
बाह्य पूर्णांक chsc_enable_facility(पूर्णांक);
काष्ठा channel_subप्रणाली;
बाह्य पूर्णांक chsc_secm(काष्ठा channel_subप्रणाली *, पूर्णांक);
पूर्णांक __chsc_करो_secm(काष्ठा channel_subप्रणाली *css, पूर्णांक enable);

पूर्णांक chsc_chp_vary(काष्ठा chp_id chpid, पूर्णांक on);
पूर्णांक chsc_determine_channel_path_desc(काष्ठा chp_id chpid, पूर्णांक fmt, पूर्णांक rfmt,
				     पूर्णांक c, पूर्णांक m, व्योम *page);
पूर्णांक chsc_determine_fmt0_channel_path_desc(काष्ठा chp_id chpid,
					  काष्ठा channel_path_desc_fmt0 *desc);
पूर्णांक chsc_determine_fmt1_channel_path_desc(काष्ठा chp_id chpid,
					  काष्ठा channel_path_desc_fmt1 *desc);
पूर्णांक chsc_determine_fmt3_channel_path_desc(काष्ठा chp_id chpid,
					  काष्ठा channel_path_desc_fmt3 *desc);
व्योम chsc_chp_online(काष्ठा chp_id chpid);
व्योम chsc_chp_offline(काष्ठा chp_id chpid);
पूर्णांक chsc_get_channel_measurement_अक्षरs(काष्ठा channel_path *chp);
पूर्णांक chsc_ssqd(काष्ठा subchannel_id schid, काष्ठा chsc_ssqd_area *ssqd);
पूर्णांक chsc_sadc(काष्ठा subchannel_id schid, काष्ठा chsc_scssc_area *scssc,
	      u64 summary_indicator_addr, u64 subchannel_indicator_addr,
	      u8 isc);
पूर्णांक chsc_sgib(u32 origin);
पूर्णांक chsc_error_from_response(पूर्णांक response);

पूर्णांक chsc_siosl(काष्ठा subchannel_id schid);

/* Functions and definitions to query storage-class memory. */
काष्ठा sale अणु
	u64 sa;
	u32 p:4;
	u32 op_state:4;
	u32 data_state:4;
	u32 rank:4;
	u32 r:1;
	u32:7;
	u32 rid:8;
	u32:32;
पूर्ण __packed;

काष्ठा chsc_scm_info अणु
	काष्ठा chsc_header request;
	u32:32;
	u64 reqtok;
	u32 reserved1[4];
	काष्ठा chsc_header response;
	u64:56;
	u8 rq;
	u32 mbc;
	u64 msa;
	u16 is;
	u16 mmc;
	u32 mci;
	u64 nr_scm_ini;
	u64 nr_scm_unini;
	u32 reserved2[10];
	u64 restok;
	काष्ठा sale scmal[248];
पूर्ण __packed __aligned(PAGE_SIZE);

पूर्णांक chsc_scm_info(काष्ठा chsc_scm_info *scm_area, u64 token);

पूर्णांक chsc_pnso(काष्ठा subchannel_id schid, काष्ठा chsc_pnso_area *pnso_area,
	      u8 oc, काष्ठा chsc_pnso_resume_token resume_token, पूर्णांक cnc);

पूर्णांक __init chsc_get_cssid_iid(पूर्णांक idx, u8 *cssid, u8 *iid);

#अगर_घोषित CONFIG_SCM_BUS
पूर्णांक scm_update_inक्रमmation(व्योम);
पूर्णांक scm_process_availability_inक्रमmation(व्योम);
#अन्यथा /* CONFIG_SCM_BUS */
अटल अंतरभूत पूर्णांक scm_update_inक्रमmation(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक scm_process_availability_inक्रमmation(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_SCM_BUS */


#पूर्ण_अगर
