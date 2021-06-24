<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright IBM Corp. 2020
 *
 * Author(s): Alexandra Wपूर्णांकer <wपूर्णांकera@linux.ibm.com>
 *
 * Interface क्रम Channel Subप्रणाली Call
 */
#अगर_अघोषित _ASM_S390_CHSC_H
#घोषणा _ASM_S390_CHSC_H

#समावेश <uapi/यंत्र/chsc.h>

/**
 * Operation codes क्रम CHSC PNSO:
 *    PNSO_OC_NET_BRIDGE_INFO - only addresses that are visible to a bridgeport
 *    PNSO_OC_NET_ADDR_INFO   - all addresses
 */
#घोषणा PNSO_OC_NET_BRIDGE_INFO		0
#घोषणा PNSO_OC_NET_ADDR_INFO		3
/**
 * काष्ठा chsc_pnso_naid_l2 - network address inक्रमmation descriptor
 * @nit:  Network पूर्णांकerface token
 * @addr_lnid: network address and logical network id (VLAN ID)
 */
काष्ठा chsc_pnso_naid_l2 अणु
	u64 nit;
	काष्ठा अणु u8 mac[6]; u16 lnid; पूर्ण addr_lnid;
पूर्ण __packed;

काष्ठा chsc_pnso_resume_token अणु
	u64 t1;
	u64 t2;
पूर्ण __packed;

काष्ठा chsc_pnso_naihdr अणु
	काष्ठा chsc_pnso_resume_token resume_token;
	u32:32;
	u32 instance;
	u32:24;
	u8 naids;
	u32 reserved[3];
पूर्ण __packed;

काष्ठा chsc_pnso_area अणु
	काष्ठा chsc_header request;
	u8:2;
	u8 m:1;
	u8:5;
	u8:2;
	u8 ssid:2;
	u8 fmt:4;
	u16 sch;
	u8:8;
	u8 cssid;
	u16:16;
	u8 oc;
	u32:24;
	काष्ठा chsc_pnso_resume_token resume_token;
	u32 n:1;
	u32:31;
	u32 reserved[3];
	काष्ठा chsc_header response;
	u32:32;
	काष्ठा chsc_pnso_naihdr naihdr;
	काष्ठा chsc_pnso_naid_l2 entries[0];
पूर्ण __packed __aligned(PAGE_SIZE);

#पूर्ण_अगर /* _ASM_S390_CHSC_H */
