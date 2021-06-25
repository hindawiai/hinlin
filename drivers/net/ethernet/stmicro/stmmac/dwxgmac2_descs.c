<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/*
 * Copyright (c) 2018 Synopsys, Inc. and/or its affiliates.
 * sपंचांगmac XGMAC support.
 */

#समावेश <linux/sपंचांगmac.h>
#समावेश "common.h"
#समावेश "dwxgmac2.h"

अटल पूर्णांक dwxgmac2_get_tx_status(व्योम *data, काष्ठा sपंचांगmac_extra_stats *x,
				  काष्ठा dma_desc *p, व्योम __iomem *ioaddr)
अणु
	अचिन्हित पूर्णांक tdes3 = le32_to_cpu(p->des3);
	पूर्णांक ret = tx_करोne;

	अगर (unlikely(tdes3 & XGMAC_TDES3_OWN))
		वापस tx_dma_own;
	अगर (likely(!(tdes3 & XGMAC_TDES3_LD)))
		वापस tx_not_ls;

	वापस ret;
पूर्ण

अटल पूर्णांक dwxgmac2_get_rx_status(व्योम *data, काष्ठा sपंचांगmac_extra_stats *x,
				  काष्ठा dma_desc *p)
अणु
	अचिन्हित पूर्णांक rdes3 = le32_to_cpu(p->des3);

	अगर (unlikely(rdes3 & XGMAC_RDES3_OWN))
		वापस dma_own;
	अगर (unlikely(rdes3 & XGMAC_RDES3_CTXT))
		वापस discard_frame;
	अगर (likely(!(rdes3 & XGMAC_RDES3_LD)))
		वापस rx_not_ls;
	अगर (unlikely((rdes3 & XGMAC_RDES3_ES) && (rdes3 & XGMAC_RDES3_LD)))
		वापस discard_frame;

	वापस good_frame;
पूर्ण

अटल पूर्णांक dwxgmac2_get_tx_len(काष्ठा dma_desc *p)
अणु
	वापस (le32_to_cpu(p->des2) & XGMAC_TDES2_B1L);
पूर्ण

अटल पूर्णांक dwxgmac2_get_tx_owner(काष्ठा dma_desc *p)
अणु
	वापस (le32_to_cpu(p->des3) & XGMAC_TDES3_OWN) > 0;
पूर्ण

अटल व्योम dwxgmac2_set_tx_owner(काष्ठा dma_desc *p)
अणु
	p->des3 |= cpu_to_le32(XGMAC_TDES3_OWN);
पूर्ण

अटल व्योम dwxgmac2_set_rx_owner(काष्ठा dma_desc *p, पूर्णांक disable_rx_ic)
अणु
	p->des3 |= cpu_to_le32(XGMAC_RDES3_OWN);

	अगर (!disable_rx_ic)
		p->des3 |= cpu_to_le32(XGMAC_RDES3_IOC);
पूर्ण

अटल पूर्णांक dwxgmac2_get_tx_ls(काष्ठा dma_desc *p)
अणु
	वापस (le32_to_cpu(p->des3) & XGMAC_RDES3_LD) > 0;
पूर्ण

अटल पूर्णांक dwxgmac2_get_rx_frame_len(काष्ठा dma_desc *p, पूर्णांक rx_coe)
अणु
	वापस (le32_to_cpu(p->des3) & XGMAC_RDES3_PL);
पूर्ण

अटल व्योम dwxgmac2_enable_tx_बारtamp(काष्ठा dma_desc *p)
अणु
	p->des2 |= cpu_to_le32(XGMAC_TDES2_TTSE);
पूर्ण

अटल पूर्णांक dwxgmac2_get_tx_बारtamp_status(काष्ठा dma_desc *p)
अणु
	वापस 0; /* Not supported */
पूर्ण

अटल अंतरभूत व्योम dwxgmac2_get_बारtamp(व्योम *desc, u32 ats, u64 *ts)
अणु
	काष्ठा dma_desc *p = (काष्ठा dma_desc *)desc;
	u64 ns = 0;

	ns += le32_to_cpu(p->des1) * 1000000000ULL;
	ns += le32_to_cpu(p->des0);

	*ts = ns;
पूर्ण

अटल पूर्णांक dwxgmac2_rx_check_बारtamp(व्योम *desc)
अणु
	काष्ठा dma_desc *p = (काष्ठा dma_desc *)desc;
	अचिन्हित पूर्णांक rdes3 = le32_to_cpu(p->des3);
	bool desc_valid, ts_valid;

	dma_rmb();

	desc_valid = !(rdes3 & XGMAC_RDES3_OWN) && (rdes3 & XGMAC_RDES3_CTXT);
	ts_valid = !(rdes3 & XGMAC_RDES3_TSD) && (rdes3 & XGMAC_RDES3_TSA);

	अगर (likely(desc_valid && ts_valid)) अणु
		अगर ((p->des0 == 0xffffffff) && (p->des1 == 0xffffffff))
			वापस -EINVAL;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक dwxgmac2_get_rx_बारtamp_status(व्योम *desc, व्योम *next_desc,
					    u32 ats)
अणु
	काष्ठा dma_desc *p = (काष्ठा dma_desc *)desc;
	अचिन्हित पूर्णांक rdes3 = le32_to_cpu(p->des3);
	पूर्णांक ret = -EBUSY;

	अगर (likely(rdes3 & XGMAC_RDES3_CDA))
		ret = dwxgmac2_rx_check_बारtamp(next_desc);

	वापस !ret;
पूर्ण

अटल व्योम dwxgmac2_init_rx_desc(काष्ठा dma_desc *p, पूर्णांक disable_rx_ic,
				  पूर्णांक mode, पूर्णांक end, पूर्णांक bfsize)
अणु
	dwxgmac2_set_rx_owner(p, disable_rx_ic);
पूर्ण

अटल व्योम dwxgmac2_init_tx_desc(काष्ठा dma_desc *p, पूर्णांक mode, पूर्णांक end)
अणु
	p->des0 = 0;
	p->des1 = 0;
	p->des2 = 0;
	p->des3 = 0;
पूर्ण

अटल व्योम dwxgmac2_prepare_tx_desc(काष्ठा dma_desc *p, पूर्णांक is_fs, पूर्णांक len,
				     bool csum_flag, पूर्णांक mode, bool tx_own,
				     bool ls, अचिन्हित पूर्णांक tot_pkt_len)
अणु
	अचिन्हित पूर्णांक tdes3 = le32_to_cpu(p->des3);

	p->des2 |= cpu_to_le32(len & XGMAC_TDES2_B1L);

	tdes3 |= tot_pkt_len & XGMAC_TDES3_FL;
	अगर (is_fs)
		tdes3 |= XGMAC_TDES3_FD;
	अन्यथा
		tdes3 &= ~XGMAC_TDES3_FD;

	अगर (csum_flag)
		tdes3 |= 0x3 << XGMAC_TDES3_CIC_SHIFT;
	अन्यथा
		tdes3 &= ~XGMAC_TDES3_CIC;

	अगर (ls)
		tdes3 |= XGMAC_TDES3_LD;
	अन्यथा
		tdes3 &= ~XGMAC_TDES3_LD;

	/* Finally set the OWN bit. Later the DMA will start! */
	अगर (tx_own)
		tdes3 |= XGMAC_TDES3_OWN;

	अगर (is_fs && tx_own)
		/* When the own bit, क्रम the first frame, has to be set, all
		 * descriptors क्रम the same frame has to be set beक्रमe, to
		 * aव्योम race condition.
		 */
		dma_wmb();

	p->des3 = cpu_to_le32(tdes3);
पूर्ण

अटल व्योम dwxgmac2_prepare_tso_tx_desc(काष्ठा dma_desc *p, पूर्णांक is_fs,
					 पूर्णांक len1, पूर्णांक len2, bool tx_own,
					 bool ls, अचिन्हित पूर्णांक tcphdrlen,
					 अचिन्हित पूर्णांक tcppayloadlen)
अणु
	अचिन्हित पूर्णांक tdes3 = le32_to_cpu(p->des3);

	अगर (len1)
		p->des2 |= cpu_to_le32(len1 & XGMAC_TDES2_B1L);
	अगर (len2)
		p->des2 |= cpu_to_le32((len2 << XGMAC_TDES2_B2L_SHIFT) &
				XGMAC_TDES2_B2L);
	अगर (is_fs) अणु
		tdes3 |= XGMAC_TDES3_FD | XGMAC_TDES3_TSE;
		tdes3 |= (tcphdrlen << XGMAC_TDES3_THL_SHIFT) &
			XGMAC_TDES3_THL;
		tdes3 |= tcppayloadlen & XGMAC_TDES3_TPL;
	पूर्ण अन्यथा अणु
		tdes3 &= ~XGMAC_TDES3_FD;
	पूर्ण

	अगर (ls)
		tdes3 |= XGMAC_TDES3_LD;
	अन्यथा
		tdes3 &= ~XGMAC_TDES3_LD;

	/* Finally set the OWN bit. Later the DMA will start! */
	अगर (tx_own)
		tdes3 |= XGMAC_TDES3_OWN;

	अगर (is_fs && tx_own)
		/* When the own bit, क्रम the first frame, has to be set, all
		 * descriptors क्रम the same frame has to be set beक्रमe, to
		 * aव्योम race condition.
		 */
		dma_wmb();

	p->des3 = cpu_to_le32(tdes3);
पूर्ण

अटल व्योम dwxgmac2_release_tx_desc(काष्ठा dma_desc *p, पूर्णांक mode)
अणु
	p->des0 = 0;
	p->des1 = 0;
	p->des2 = 0;
	p->des3 = 0;
पूर्ण

अटल व्योम dwxgmac2_set_tx_ic(काष्ठा dma_desc *p)
अणु
	p->des2 |= cpu_to_le32(XGMAC_TDES2_IOC);
पूर्ण

अटल व्योम dwxgmac2_set_mss(काष्ठा dma_desc *p, अचिन्हित पूर्णांक mss)
अणु
	p->des0 = 0;
	p->des1 = 0;
	p->des2 = cpu_to_le32(mss);
	p->des3 = cpu_to_le32(XGMAC_TDES3_CTXT | XGMAC_TDES3_TCMSSV);
पूर्ण

अटल व्योम dwxgmac2_get_addr(काष्ठा dma_desc *p, अचिन्हित पूर्णांक *addr)
अणु
	*addr = le32_to_cpu(p->des0);
पूर्ण

अटल व्योम dwxgmac2_set_addr(काष्ठा dma_desc *p, dma_addr_t addr)
अणु
	p->des0 = cpu_to_le32(lower_32_bits(addr));
	p->des1 = cpu_to_le32(upper_32_bits(addr));
पूर्ण

अटल व्योम dwxgmac2_clear(काष्ठा dma_desc *p)
अणु
	p->des0 = 0;
	p->des1 = 0;
	p->des2 = 0;
	p->des3 = 0;
पूर्ण

अटल पूर्णांक dwxgmac2_get_rx_hash(काष्ठा dma_desc *p, u32 *hash,
				क्रमागत pkt_hash_types *type)
अणु
	अचिन्हित पूर्णांक rdes3 = le32_to_cpu(p->des3);
	u32 ptype;

	अगर (rdes3 & XGMAC_RDES3_RSV) अणु
		ptype = (rdes3 & XGMAC_RDES3_L34T) >> XGMAC_RDES3_L34T_SHIFT;

		चयन (ptype) अणु
		हाल XGMAC_L34T_IP4TCP:
		हाल XGMAC_L34T_IP4UDP:
		हाल XGMAC_L34T_IP6TCP:
		हाल XGMAC_L34T_IP6UDP:
			*type = PKT_HASH_TYPE_L4;
			अवरोध;
		शेष:
			*type = PKT_HASH_TYPE_L3;
			अवरोध;
		पूर्ण

		*hash = le32_to_cpu(p->des1);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम dwxgmac2_get_rx_header_len(काष्ठा dma_desc *p, अचिन्हित पूर्णांक *len)
अणु
	अगर (le32_to_cpu(p->des3) & XGMAC_RDES3_L34T)
		*len = le32_to_cpu(p->des2) & XGMAC_RDES2_HL;
पूर्ण

अटल व्योम dwxgmac2_set_sec_addr(काष्ठा dma_desc *p, dma_addr_t addr, bool is_valid)
अणु
	p->des2 = cpu_to_le32(lower_32_bits(addr));
	p->des3 = cpu_to_le32(upper_32_bits(addr));
पूर्ण

अटल व्योम dwxgmac2_set_sarc(काष्ठा dma_desc *p, u32 sarc_type)
अणु
	sarc_type <<= XGMAC_TDES3_SAIC_SHIFT;

	p->des3 |= cpu_to_le32(sarc_type & XGMAC_TDES3_SAIC);
पूर्ण

अटल व्योम dwxgmac2_set_vlan_tag(काष्ठा dma_desc *p, u16 tag, u16 inner_tag,
				  u32 inner_type)
अणु
	p->des0 = 0;
	p->des1 = 0;
	p->des2 = 0;
	p->des3 = 0;

	/* Inner VLAN */
	अगर (inner_type) अणु
		u32 des = inner_tag << XGMAC_TDES2_IVT_SHIFT;

		des &= XGMAC_TDES2_IVT;
		p->des2 = cpu_to_le32(des);

		des = inner_type << XGMAC_TDES3_IVTIR_SHIFT;
		des &= XGMAC_TDES3_IVTIR;
		p->des3 = cpu_to_le32(des | XGMAC_TDES3_IVLTV);
	पूर्ण

	/* Outer VLAN */
	p->des3 |= cpu_to_le32(tag & XGMAC_TDES3_VT);
	p->des3 |= cpu_to_le32(XGMAC_TDES3_VLTV);

	p->des3 |= cpu_to_le32(XGMAC_TDES3_CTXT);
पूर्ण

अटल व्योम dwxgmac2_set_vlan(काष्ठा dma_desc *p, u32 type)
अणु
	type <<= XGMAC_TDES2_VTIR_SHIFT;
	p->des2 |= cpu_to_le32(type & XGMAC_TDES2_VTIR);
पूर्ण

अटल व्योम dwxgmac2_set_tbs(काष्ठा dma_edesc *p, u32 sec, u32 nsec)
अणु
	p->des4 = cpu_to_le32((sec & XGMAC_TDES0_LT) | XGMAC_TDES0_LTV);
	p->des5 = cpu_to_le32(nsec & XGMAC_TDES1_LT);
	p->des6 = 0;
	p->des7 = 0;
पूर्ण

स्थिर काष्ठा sपंचांगmac_desc_ops dwxgmac210_desc_ops = अणु
	.tx_status = dwxgmac2_get_tx_status,
	.rx_status = dwxgmac2_get_rx_status,
	.get_tx_len = dwxgmac2_get_tx_len,
	.get_tx_owner = dwxgmac2_get_tx_owner,
	.set_tx_owner = dwxgmac2_set_tx_owner,
	.set_rx_owner = dwxgmac2_set_rx_owner,
	.get_tx_ls = dwxgmac2_get_tx_ls,
	.get_rx_frame_len = dwxgmac2_get_rx_frame_len,
	.enable_tx_बारtamp = dwxgmac2_enable_tx_बारtamp,
	.get_tx_बारtamp_status = dwxgmac2_get_tx_बारtamp_status,
	.get_rx_बारtamp_status = dwxgmac2_get_rx_बारtamp_status,
	.get_बारtamp = dwxgmac2_get_बारtamp,
	.set_tx_ic = dwxgmac2_set_tx_ic,
	.prepare_tx_desc = dwxgmac2_prepare_tx_desc,
	.prepare_tso_tx_desc = dwxgmac2_prepare_tso_tx_desc,
	.release_tx_desc = dwxgmac2_release_tx_desc,
	.init_rx_desc = dwxgmac2_init_rx_desc,
	.init_tx_desc = dwxgmac2_init_tx_desc,
	.set_mss = dwxgmac2_set_mss,
	.get_addr = dwxgmac2_get_addr,
	.set_addr = dwxgmac2_set_addr,
	.clear = dwxgmac2_clear,
	.get_rx_hash = dwxgmac2_get_rx_hash,
	.get_rx_header_len = dwxgmac2_get_rx_header_len,
	.set_sec_addr = dwxgmac2_set_sec_addr,
	.set_sarc = dwxgmac2_set_sarc,
	.set_vlan_tag = dwxgmac2_set_vlan_tag,
	.set_vlan = dwxgmac2_set_vlan,
	.set_tbs = dwxgmac2_set_tbs,
पूर्ण;
