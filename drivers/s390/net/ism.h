<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित S390_ISM_H
#घोषणा S390_ISM_H

#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <net/smc.h>
#समावेश <यंत्र/pci_insn.h>

#घोषणा UTIL_STR_LEN	16

/*
 * Do not use the first word of the DMB bits to ensure 8 byte aligned access.
 */
#घोषणा ISM_DMB_WORD_OFFSET	1
#घोषणा ISM_DMB_BIT_OFFSET	(ISM_DMB_WORD_OFFSET * 32)
#घोषणा ISM_NR_DMBS		1920
#घोषणा ISM_IDENT_MASK		0x00FFFF

#घोषणा ISM_REG_SBA	0x1
#घोषणा ISM_REG_IEQ	0x2
#घोषणा ISM_READ_GID	0x3
#घोषणा ISM_ADD_VLAN_ID	0x4
#घोषणा ISM_DEL_VLAN_ID	0x5
#घोषणा ISM_SET_VLAN	0x6
#घोषणा ISM_RESET_VLAN	0x7
#घोषणा ISM_QUERY_INFO	0x8
#घोषणा ISM_QUERY_RGID	0x9
#घोषणा ISM_REG_DMB	0xA
#घोषणा ISM_UNREG_DMB	0xB
#घोषणा ISM_SIGNAL_IEQ	0xE
#घोषणा ISM_UNREG_SBA	0x11
#घोषणा ISM_UNREG_IEQ	0x12

काष्ठा ism_req_hdr अणु
	u32 cmd;
	u16 : 16;
	u16 len;
पूर्ण;

काष्ठा ism_resp_hdr अणु
	u32 cmd;
	u16 ret;
	u16 len;
पूर्ण;

जोड़ ism_reg_sba अणु
	काष्ठा अणु
		काष्ठा ism_req_hdr hdr;
		u64 sba;
	पूर्ण request;
	काष्ठा अणु
		काष्ठा ism_resp_hdr hdr;
	पूर्ण response;
पूर्ण __aligned(16);

जोड़ ism_reg_ieq अणु
	काष्ठा अणु
		काष्ठा ism_req_hdr hdr;
		u64 ieq;
		u64 len;
	पूर्ण request;
	काष्ठा अणु
		काष्ठा ism_resp_hdr hdr;
	पूर्ण response;
पूर्ण __aligned(16);

जोड़ ism_पढ़ो_gid अणु
	काष्ठा अणु
		काष्ठा ism_req_hdr hdr;
	पूर्ण request;
	काष्ठा अणु
		काष्ठा ism_resp_hdr hdr;
		u64 gid;
	पूर्ण response;
पूर्ण __aligned(16);

जोड़ ism_qi अणु
	काष्ठा अणु
		काष्ठा ism_req_hdr hdr;
	पूर्ण request;
	काष्ठा अणु
		काष्ठा ism_resp_hdr hdr;
		u32 version;
		u32 max_len;
		u64 ism_state;
		u64 my_gid;
		u64 sba;
		u64 ieq;
		u32 ieq_len;
		u32 : 32;
		u32 dmbs_owned;
		u32 dmbs_used;
		u32 vlan_required;
		u32 vlan_nr_ids;
		u16 vlan_id[64];
	पूर्ण response;
पूर्ण __aligned(64);

जोड़ ism_query_rgid अणु
	काष्ठा अणु
		काष्ठा ism_req_hdr hdr;
		u64 rgid;
		u32 vlan_valid;
		u32 vlan_id;
	पूर्ण request;
	काष्ठा अणु
		काष्ठा ism_resp_hdr hdr;
	पूर्ण response;
पूर्ण __aligned(16);

जोड़ ism_reg_dmb अणु
	काष्ठा अणु
		काष्ठा ism_req_hdr hdr;
		u64 dmb;
		u32 dmb_len;
		u32 sba_idx;
		u32 vlan_valid;
		u32 vlan_id;
		u64 rgid;
	पूर्ण request;
	काष्ठा अणु
		काष्ठा ism_resp_hdr hdr;
		u64 dmb_tok;
	पूर्ण response;
पूर्ण __aligned(32);

जोड़ ism_sig_ieq अणु
	काष्ठा अणु
		काष्ठा ism_req_hdr hdr;
		u64 rgid;
		u32 trigger_irq;
		u32 event_code;
		u64 info;
	पूर्ण request;
	काष्ठा अणु
		काष्ठा ism_resp_hdr hdr;
	पूर्ण response;
पूर्ण __aligned(32);

जोड़ ism_unreg_dmb अणु
	काष्ठा अणु
		काष्ठा ism_req_hdr hdr;
		u64 dmb_tok;
	पूर्ण request;
	काष्ठा अणु
		काष्ठा ism_resp_hdr hdr;
	पूर्ण response;
पूर्ण __aligned(16);

जोड़ ism_cmd_simple अणु
	काष्ठा अणु
		काष्ठा ism_req_hdr hdr;
	पूर्ण request;
	काष्ठा अणु
		काष्ठा ism_resp_hdr hdr;
	पूर्ण response;
पूर्ण __aligned(8);

जोड़ ism_set_vlan_id अणु
	काष्ठा अणु
		काष्ठा ism_req_hdr hdr;
		u64 vlan_id;
	पूर्ण request;
	काष्ठा अणु
		काष्ठा ism_resp_hdr hdr;
	पूर्ण response;
पूर्ण __aligned(16);

काष्ठा ism_eq_header अणु
	u64 idx;
	u64 ieq_len;
	u64 entry_len;
	u64 : 64;
पूर्ण;

काष्ठा ism_eq अणु
	काष्ठा ism_eq_header header;
	काष्ठा smcd_event entry[15];
पूर्ण;

काष्ठा ism_sba अणु
	u32 s : 1;	/* summary bit */
	u32 e : 1;	/* event bit */
	u32 : 30;
	u32 dmb_bits[ISM_NR_DMBS / 32];
	u32 reserved[3];
	u16 dmbe_mask[ISM_NR_DMBS];
पूर्ण;

काष्ठा ism_dev अणु
	spinlock_t lock;
	काष्ठा pci_dev *pdev;
	काष्ठा smcd_dev *smcd;

	काष्ठा ism_sba *sba;
	dma_addr_t sba_dma_addr;
	DECLARE_BITMAP(sba_biपंचांगap, ISM_NR_DMBS);

	काष्ठा ism_eq *ieq;
	dma_addr_t ieq_dma_addr;

	पूर्णांक ieq_idx;
पूर्ण;

#घोषणा ISM_CREATE_REQ(dmb, idx, sf, offset)		\
	((dmb) | (idx) << 24 | (sf) << 23 | (offset))

काष्ठा ism_प्रणालीeid अणु
	u8	seid_string[24];
	u8	serial_number[4];
	u8	type[4];
पूर्ण;

अटल अंतरभूत व्योम __ism_पढ़ो_cmd(काष्ठा ism_dev *ism, व्योम *data,
				  अचिन्हित दीर्घ offset, अचिन्हित दीर्घ len)
अणु
	काष्ठा zpci_dev *zdev = to_zpci(ism->pdev);
	u64 req = ZPCI_CREATE_REQ(zdev->fh, 2, 8);

	जबतक (len > 0) अणु
		__zpci_load(data, req, offset);
		offset += 8;
		data += 8;
		len -= 8;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __ism_ग_लिखो_cmd(काष्ठा ism_dev *ism, व्योम *data,
				   अचिन्हित दीर्घ offset, अचिन्हित दीर्घ len)
अणु
	काष्ठा zpci_dev *zdev = to_zpci(ism->pdev);
	u64 req = ZPCI_CREATE_REQ(zdev->fh, 2, len);

	अगर (len)
		__zpci_store_block(data, req, offset);
पूर्ण

अटल अंतरभूत पूर्णांक __ism_move(काष्ठा ism_dev *ism, u64 dmb_req, व्योम *data,
			     अचिन्हित पूर्णांक size)
अणु
	काष्ठा zpci_dev *zdev = to_zpci(ism->pdev);
	u64 req = ZPCI_CREATE_REQ(zdev->fh, 0, size);

	वापस __zpci_store_block(data, req, dmb_req);
पूर्ण

#पूर्ण_अगर /* S390_ISM_H */
