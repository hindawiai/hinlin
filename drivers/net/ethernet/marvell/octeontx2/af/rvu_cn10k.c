<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*  Marvell RPM CN10K driver
 *
 * Copyright (C) 2020 Marvell.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/pci.h>
#समावेश "rvu.h"
#समावेश "cgx.h"
#समावेश "rvu_reg.h"

पूर्णांक rvu_set_channels_base(काष्ठा rvu *rvu)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	u16 cpt_chan_base;
	u64 nix_स्थिर;
	पूर्णांक blkaddr;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, 0);
	अगर (blkaddr < 0)
		वापस blkaddr;

	nix_स्थिर = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_CONST);

	hw->cgx = (nix_स्थिर >> 12) & 0xFULL;
	hw->lmac_per_cgx = (nix_स्थिर >> 8) & 0xFULL;
	hw->cgx_links = hw->cgx * hw->lmac_per_cgx;
	hw->lbk_links = (nix_स्थिर >> 24) & 0xFULL;
	hw->cpt_links = (nix_स्थिर >> 44) & 0xFULL;
	hw->sdp_links = 1;

	hw->cgx_chan_base = NIX_CHAN_CGX_LMAC_CHX(0, 0, 0);
	hw->lbk_chan_base = NIX_CHAN_LBK_CHX(0, 0);
	hw->sdp_chan_base = NIX_CHAN_SDP_CH_START;

	/* No Programmable channels */
	अगर (!(nix_स्थिर & BIT_ULL(60)))
		वापस 0;

	hw->cap.programmable_chans = true;

	/* If programmable channels are present then configure
	 * channels such that all channel numbers are contiguous
	 * leaving no holes. This way the new CPT channels can be
	 * accomodated. The order of channel numbers asचिन्हित is
	 * LBK, SDP, CGX and CPT.
	 */
	hw->sdp_chan_base = hw->lbk_chan_base + hw->lbk_links *
				((nix_स्थिर >> 16) & 0xFFULL);
	hw->cgx_chan_base = hw->sdp_chan_base + hw->sdp_links * SDP_CHANNELS;

	cpt_chan_base = hw->cgx_chan_base + hw->cgx_links *
				(nix_स्थिर & 0xFFULL);

	/* Out of 4096 channels start CPT from 2048 so
	 * that MSB क्रम CPT channels is always set
	 */
	अगर (cpt_chan_base <= 0x800) अणु
		hw->cpt_chan_base = 0x800;
	पूर्ण अन्यथा अणु
		dev_err(rvu->dev,
			"CPT channels could not fit in the range 2048-4095\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा LBK_CONNECT_NIXX(a)		(0x0 + (a))

अटल व्योम __rvu_lbk_set_chans(काष्ठा rvu *rvu, व्योम __iomem *base,
				u64 offset, पूर्णांक lbkid, u16 chans)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	u64 cfg;

	cfg = पढ़ोq(base + offset);
	cfg &= ~(LBK_LINK_CFG_RANGE_MASK |
		 LBK_LINK_CFG_ID_MASK | LBK_LINK_CFG_BASE_MASK);
	cfg |=	FIELD_PREP(LBK_LINK_CFG_RANGE_MASK, ilog2(chans));
	cfg |=	FIELD_PREP(LBK_LINK_CFG_ID_MASK, lbkid);
	cfg |=	FIELD_PREP(LBK_LINK_CFG_BASE_MASK, hw->lbk_chan_base);

	ग_लिखोq(cfg, base + offset);
पूर्ण

अटल व्योम rvu_lbk_set_channels(काष्ठा rvu *rvu)
अणु
	काष्ठा pci_dev *pdev = शून्य;
	व्योम __iomem *base;
	u64 lbk_स्थिर;
	u8 src, dst;
	u16 chans;

	/* To loopback packets between multiple NIX blocks
	 * mutliple LBK blocks are needed. With two NIX blocks,
	 * four LBK blocks are needed and each LBK block
	 * source and destination are as follows:
	 * LBK0 - source NIX0 and destination NIX1
	 * LBK1 - source NIX0 and destination NIX1
	 * LBK2 - source NIX1 and destination NIX0
	 * LBK3 - source NIX1 and destination NIX1
	 * As per the HRM channel numbers should be programmed as:
	 * P2X and X2P of LBK0 as same
	 * P2X and X2P of LBK3 as same
	 * P2X of LBK1 and X2P of LBK2 as same
	 * P2X of LBK2 and X2P of LBK1 as same
	 */
	जबतक (true) अणु
		pdev = pci_get_device(PCI_VENDOR_ID_CAVIUM,
				      PCI_DEVID_OCTEONTX2_LBK, pdev);
		अगर (!pdev)
			वापस;

		base = pci_ioremap_bar(pdev, 0);
		अगर (!base)
			जाओ err_put;

		lbk_स्थिर = पढ़ोq(base + LBK_CONST);
		chans = FIELD_GET(LBK_CONST_CHANS, lbk_स्थिर);
		dst = FIELD_GET(LBK_CONST_DST, lbk_स्थिर);
		src = FIELD_GET(LBK_CONST_SRC, lbk_स्थिर);

		अगर (src == dst) अणु
			अगर (src == LBK_CONNECT_NIXX(0)) अणु /* LBK0 */
				__rvu_lbk_set_chans(rvu, base, LBK_LINK_CFG_X2P,
						    0, chans);
				__rvu_lbk_set_chans(rvu, base, LBK_LINK_CFG_P2X,
						    0, chans);
			पूर्ण अन्यथा अगर (src == LBK_CONNECT_NIXX(1)) अणु /* LBK3 */
				__rvu_lbk_set_chans(rvu, base, LBK_LINK_CFG_X2P,
						    1, chans);
				__rvu_lbk_set_chans(rvu, base, LBK_LINK_CFG_P2X,
						    1, chans);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (src == LBK_CONNECT_NIXX(0)) अणु /* LBK1 */
				__rvu_lbk_set_chans(rvu, base, LBK_LINK_CFG_X2P,
						    0, chans);
				__rvu_lbk_set_chans(rvu, base, LBK_LINK_CFG_P2X,
						    1, chans);
			पूर्ण अन्यथा अगर (src == LBK_CONNECT_NIXX(1)) अणु /* LBK2 */
				__rvu_lbk_set_chans(rvu, base, LBK_LINK_CFG_X2P,
						    1, chans);
				__rvu_lbk_set_chans(rvu, base, LBK_LINK_CFG_P2X,
						    0, chans);
			पूर्ण
		पूर्ण
		iounmap(base);
	पूर्ण
err_put:
	pci_dev_put(pdev);
पूर्ण

अटल व्योम __rvu_nix_set_channels(काष्ठा rvu *rvu, पूर्णांक blkaddr)
अणु
	u64 nix_स्थिर = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_CONST);
	u16 cgx_chans, lbk_chans, sdp_chans, cpt_chans;
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	पूर्णांक link, nix_link = 0;
	u16 start;
	u64 cfg;

	cgx_chans = nix_स्थिर & 0xFFULL;
	lbk_chans = (nix_स्थिर >> 16) & 0xFFULL;
	sdp_chans = SDP_CHANNELS;
	cpt_chans = (nix_स्थिर >> 32) & 0xFFFULL;

	start = hw->cgx_chan_base;
	क्रम (link = 0; link < hw->cgx_links; link++, nix_link++) अणु
		cfg = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_LINKX_CFG(nix_link));
		cfg &= ~(NIX_AF_LINKX_BASE_MASK | NIX_AF_LINKX_RANGE_MASK);
		cfg |=	FIELD_PREP(NIX_AF_LINKX_RANGE_MASK, ilog2(cgx_chans));
		cfg |=	FIELD_PREP(NIX_AF_LINKX_BASE_MASK, start);
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LINKX_CFG(nix_link), cfg);
		start += cgx_chans;
	पूर्ण

	start = hw->lbk_chan_base;
	क्रम (link = 0; link < hw->lbk_links; link++, nix_link++) अणु
		cfg = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_LINKX_CFG(nix_link));
		cfg &= ~(NIX_AF_LINKX_BASE_MASK | NIX_AF_LINKX_RANGE_MASK);
		cfg |=	FIELD_PREP(NIX_AF_LINKX_RANGE_MASK, ilog2(lbk_chans));
		cfg |=	FIELD_PREP(NIX_AF_LINKX_BASE_MASK, start);
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LINKX_CFG(nix_link), cfg);
		start += lbk_chans;
	पूर्ण

	start = hw->sdp_chan_base;
	क्रम (link = 0; link < hw->sdp_links; link++, nix_link++) अणु
		cfg = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_LINKX_CFG(nix_link));
		cfg &= ~(NIX_AF_LINKX_BASE_MASK | NIX_AF_LINKX_RANGE_MASK);
		cfg |=	FIELD_PREP(NIX_AF_LINKX_RANGE_MASK, ilog2(sdp_chans));
		cfg |=	FIELD_PREP(NIX_AF_LINKX_BASE_MASK, start);
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LINKX_CFG(nix_link), cfg);
		start += sdp_chans;
	पूर्ण

	start = hw->cpt_chan_base;
	क्रम (link = 0; link < hw->cpt_links; link++, nix_link++) अणु
		cfg = rvu_पढ़ो64(rvu, blkaddr, NIX_AF_LINKX_CFG(nix_link));
		cfg &= ~(NIX_AF_LINKX_BASE_MASK | NIX_AF_LINKX_RANGE_MASK);
		cfg |=	FIELD_PREP(NIX_AF_LINKX_RANGE_MASK, ilog2(cpt_chans));
		cfg |=	FIELD_PREP(NIX_AF_LINKX_BASE_MASK, start);
		rvu_ग_लिखो64(rvu, blkaddr, NIX_AF_LINKX_CFG(nix_link), cfg);
		start += cpt_chans;
	पूर्ण
पूर्ण

अटल व्योम rvu_nix_set_channels(काष्ठा rvu *rvu)
अणु
	पूर्णांक blkaddr = 0;

	blkaddr = rvu_get_next_nix_blkaddr(rvu, blkaddr);
	जबतक (blkaddr) अणु
		__rvu_nix_set_channels(rvu, blkaddr);
		blkaddr = rvu_get_next_nix_blkaddr(rvu, blkaddr);
	पूर्ण
पूर्ण

अटल व्योम __rvu_rpm_set_channels(पूर्णांक cgxid, पूर्णांक lmacid, u16 base)
अणु
	u64 cfg;

	cfg = cgx_lmac_पढ़ो(cgxid, lmacid, RPMX_CMRX_LINK_CFG);
	cfg &= ~(RPMX_CMRX_LINK_BASE_MASK | RPMX_CMRX_LINK_RANGE_MASK);

	/* There is no पढ़ो-only स्थिरant रेजिस्टर to पढ़ो
	 * the number of channels क्रम LMAC and it is always 16.
	 */
	cfg |=	FIELD_PREP(RPMX_CMRX_LINK_RANGE_MASK, ilog2(16));
	cfg |=	FIELD_PREP(RPMX_CMRX_LINK_BASE_MASK, base);
	cgx_lmac_ग_लिखो(cgxid, lmacid, RPMX_CMRX_LINK_CFG, cfg);
पूर्ण

अटल व्योम rvu_rpm_set_channels(काष्ठा rvu *rvu)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;
	u16 base = hw->cgx_chan_base;
	पूर्णांक cgx, lmac;

	क्रम (cgx = 0; cgx < rvu->cgx_cnt_max; cgx++) अणु
		क्रम (lmac = 0; lmac < hw->lmac_per_cgx; lmac++) अणु
			__rvu_rpm_set_channels(cgx, lmac, base);
			base += 16;
		पूर्ण
	पूर्ण
पूर्ण

व्योम rvu_program_channels(काष्ठा rvu *rvu)
अणु
	काष्ठा rvu_hwinfo *hw = rvu->hw;

	अगर (!hw->cap.programmable_chans)
		वापस;

	rvu_nix_set_channels(rvu);
	rvu_lbk_set_channels(rvu);
	rvu_rpm_set_channels(rvu);
पूर्ण
