<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/घातerpc/sysdev/qe_lib/ucc.c
 *
 * QE UCC API Set - UCC specअगरic routines implementations.
 *
 * Copyright (C) 2006 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Authors: 	Shlomi Gridish <gridish@मुक्तscale.com>
 * 		Li Yang <leoli@मुक्तscale.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/पन.स>
#समावेश <soc/fsl/qe/immap_qe.h>
#समावेश <soc/fsl/qe/qe.h>
#समावेश <soc/fsl/qe/ucc.h>

#घोषणा UCC_TDM_NUM 8
#घोषणा RX_SYNC_SHIFT_BASE 30
#घोषणा TX_SYNC_SHIFT_BASE 14
#घोषणा RX_CLK_SHIFT_BASE 28
#घोषणा TX_CLK_SHIFT_BASE 12

पूर्णांक ucc_set_qe_mux_mii_mng(अचिन्हित पूर्णांक ucc_num)
अणु
	अचिन्हित दीर्घ flags;

	अगर (ucc_num > UCC_MAX_NUM - 1)
		वापस -EINVAL;

	spin_lock_irqsave(&cmxgcr_lock, flags);
	qe_clrsetbits_be32(&qe_immr->qmx.cmxgcr, QE_CMXGCR_MII_ENET_MNG,
			   ucc_num << QE_CMXGCR_MII_ENET_MNG_SHIFT);
	spin_unlock_irqrestore(&cmxgcr_lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ucc_set_qe_mux_mii_mng);

/* Configure the UCC to either Slow or Fast.
 *
 * A given UCC can be figured to support either "slow" devices (e.g. UART)
 * or "fast" devices (e.g. Ethernet).
 *
 * 'ucc_num' is the UCC number, from 0 - 7.
 *
 * This function also sets the UCC_GUEMR_SET_RESERVED3 bit because that bit
 * must always be set to 1.
 */
पूर्णांक ucc_set_type(अचिन्हित पूर्णांक ucc_num, क्रमागत ucc_speed_type speed)
अणु
	u8 __iomem *guemr;

	/* The GUEMR रेजिस्टर is at the same location क्रम both slow and fast
	   devices, so we just use uccX.slow.guemr. */
	चयन (ucc_num) अणु
	हाल 0: guemr = &qe_immr->ucc1.slow.guemr;
		अवरोध;
	हाल 1: guemr = &qe_immr->ucc2.slow.guemr;
		अवरोध;
	हाल 2: guemr = &qe_immr->ucc3.slow.guemr;
		अवरोध;
	हाल 3: guemr = &qe_immr->ucc4.slow.guemr;
		अवरोध;
	हाल 4: guemr = &qe_immr->ucc5.slow.guemr;
		अवरोध;
	हाल 5: guemr = &qe_immr->ucc6.slow.guemr;
		अवरोध;
	हाल 6: guemr = &qe_immr->ucc7.slow.guemr;
		अवरोध;
	हाल 7: guemr = &qe_immr->ucc8.slow.guemr;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	qe_clrsetbits_8(guemr, UCC_GUEMR_MODE_MASK,
			UCC_GUEMR_SET_RESERVED3 | speed);

	वापस 0;
पूर्ण

अटल व्योम get_cmxucr_reg(अचिन्हित पूर्णांक ucc_num, __be32 __iomem **cmxucr,
	अचिन्हित पूर्णांक *reg_num, अचिन्हित पूर्णांक *shअगरt)
अणु
	अचिन्हित पूर्णांक cmx = ((ucc_num & 1) << 1) + (ucc_num > 3);

	*reg_num = cmx + 1;
	*cmxucr = &qe_immr->qmx.cmxucr[cmx];
	*shअगरt = 16 - 8 * (ucc_num & 2);
पूर्ण

पूर्णांक ucc_mux_set_grant_tsa_bkpt(अचिन्हित पूर्णांक ucc_num, पूर्णांक set, u32 mask)
अणु
	__be32 __iomem *cmxucr;
	अचिन्हित पूर्णांक reg_num;
	अचिन्हित पूर्णांक shअगरt;

	/* check अगर the UCC number is in range. */
	अगर (ucc_num > UCC_MAX_NUM - 1)
		वापस -EINVAL;

	get_cmxucr_reg(ucc_num, &cmxucr, &reg_num, &shअगरt);

	अगर (set)
		qe_setbits_be32(cmxucr, mask << shअगरt);
	अन्यथा
		qe_clrbits_be32(cmxucr, mask << shअगरt);

	वापस 0;
पूर्ण

पूर्णांक ucc_set_qe_mux_rxtx(अचिन्हित पूर्णांक ucc_num, क्रमागत qe_घड़ी घड़ी,
	क्रमागत comm_dir mode)
अणु
	__be32 __iomem *cmxucr;
	अचिन्हित पूर्णांक reg_num;
	अचिन्हित पूर्णांक shअगरt;
	u32 घड़ी_bits = 0;

	/* check अगर the UCC number is in range. */
	अगर (ucc_num > UCC_MAX_NUM - 1)
		वापस -EINVAL;

	/* The communications direction must be RX or TX */
	अगर (!((mode == COMM_सूची_RX) || (mode == COMM_सूची_TX)))
		वापस -EINVAL;

	get_cmxucr_reg(ucc_num, &cmxucr, &reg_num, &shअगरt);

	चयन (reg_num) अणु
	हाल 1:
		चयन (घड़ी) अणु
		हाल QE_BRG1:	घड़ी_bits = 1; अवरोध;
		हाल QE_BRG2:	घड़ी_bits = 2; अवरोध;
		हाल QE_BRG7:	घड़ी_bits = 3; अवरोध;
		हाल QE_BRG8:	घड़ी_bits = 4; अवरोध;
		हाल QE_CLK9:	घड़ी_bits = 5; अवरोध;
		हाल QE_CLK10:	घड़ी_bits = 6; अवरोध;
		हाल QE_CLK11:	घड़ी_bits = 7; अवरोध;
		हाल QE_CLK12:	घड़ी_bits = 8; अवरोध;
		हाल QE_CLK15:	घड़ी_bits = 9; अवरोध;
		हाल QE_CLK16:	घड़ी_bits = 10; अवरोध;
		शेष: अवरोध;
		पूर्ण
		अवरोध;
	हाल 2:
		चयन (घड़ी) अणु
		हाल QE_BRG5:	घड़ी_bits = 1; अवरोध;
		हाल QE_BRG6:	घड़ी_bits = 2; अवरोध;
		हाल QE_BRG7:	घड़ी_bits = 3; अवरोध;
		हाल QE_BRG8:	घड़ी_bits = 4; अवरोध;
		हाल QE_CLK13:	घड़ी_bits = 5; अवरोध;
		हाल QE_CLK14:	घड़ी_bits = 6; अवरोध;
		हाल QE_CLK19:	घड़ी_bits = 7; अवरोध;
		हाल QE_CLK20:	घड़ी_bits = 8; अवरोध;
		हाल QE_CLK15:	घड़ी_bits = 9; अवरोध;
		हाल QE_CLK16:	घड़ी_bits = 10; अवरोध;
		शेष: अवरोध;
		पूर्ण
		अवरोध;
	हाल 3:
		चयन (घड़ी) अणु
		हाल QE_BRG9:	घड़ी_bits = 1; अवरोध;
		हाल QE_BRG10:	घड़ी_bits = 2; अवरोध;
		हाल QE_BRG15:	घड़ी_bits = 3; अवरोध;
		हाल QE_BRG16:	घड़ी_bits = 4; अवरोध;
		हाल QE_CLK3:	घड़ी_bits = 5; अवरोध;
		हाल QE_CLK4:	घड़ी_bits = 6; अवरोध;
		हाल QE_CLK17:	घड़ी_bits = 7; अवरोध;
		हाल QE_CLK18:	घड़ी_bits = 8; अवरोध;
		हाल QE_CLK7:	घड़ी_bits = 9; अवरोध;
		हाल QE_CLK8:	घड़ी_bits = 10; अवरोध;
		हाल QE_CLK16:	घड़ी_bits = 11; अवरोध;
		शेष: अवरोध;
		पूर्ण
		अवरोध;
	हाल 4:
		चयन (घड़ी) अणु
		हाल QE_BRG13:	घड़ी_bits = 1; अवरोध;
		हाल QE_BRG14:	घड़ी_bits = 2; अवरोध;
		हाल QE_BRG15:	घड़ी_bits = 3; अवरोध;
		हाल QE_BRG16:	घड़ी_bits = 4; अवरोध;
		हाल QE_CLK5:	घड़ी_bits = 5; अवरोध;
		हाल QE_CLK6:	घड़ी_bits = 6; अवरोध;
		हाल QE_CLK21:	घड़ी_bits = 7; अवरोध;
		हाल QE_CLK22:	घड़ी_bits = 8; अवरोध;
		हाल QE_CLK7:	घड़ी_bits = 9; अवरोध;
		हाल QE_CLK8:	घड़ी_bits = 10; अवरोध;
		हाल QE_CLK16:	घड़ी_bits = 11; अवरोध;
		शेष: अवरोध;
		पूर्ण
		अवरोध;
	शेष: अवरोध;
	पूर्ण

	/* Check क्रम invalid combination of घड़ी and UCC number */
	अगर (!घड़ी_bits)
		वापस -ENOENT;

	अगर (mode == COMM_सूची_RX)
		shअगरt += 4;

	qe_clrsetbits_be32(cmxucr, QE_CMXUCR_TX_CLK_SRC_MASK << shअगरt,
			   घड़ी_bits << shअगरt);

	वापस 0;
पूर्ण

अटल पूर्णांक ucc_get_tdm_common_clk(u32 tdm_num, क्रमागत qe_घड़ी घड़ी)
अणु
	पूर्णांक घड़ी_bits = -EINVAL;

	/*
	 * क्रम TDM[0, 1, 2, 3], TX and RX use  common
	 * घड़ी source BRG3,4 and CLK1,2
	 * क्रम TDM[4, 5, 6, 7], TX and RX use  common
	 * घड़ी source BRG12,13 and CLK23,24
	 */
	चयन (tdm_num) अणु
	हाल 0:
	हाल 1:
	हाल 2:
	हाल 3:
		चयन (घड़ी) अणु
		हाल QE_BRG3:
			घड़ी_bits = 1;
			अवरोध;
		हाल QE_BRG4:
			घड़ी_bits = 2;
			अवरोध;
		हाल QE_CLK1:
			घड़ी_bits = 4;
			अवरोध;
		हाल QE_CLK2:
			घड़ी_bits = 5;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 4:
	हाल 5:
	हाल 6:
	हाल 7:
		चयन (घड़ी) अणु
		हाल QE_BRG12:
			घड़ी_bits = 1;
			अवरोध;
		हाल QE_BRG13:
			घड़ी_bits = 2;
			अवरोध;
		हाल QE_CLK23:
			घड़ी_bits = 4;
			अवरोध;
		हाल QE_CLK24:
			घड़ी_bits = 5;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस घड़ी_bits;
पूर्ण

अटल पूर्णांक ucc_get_tdm_rx_clk(u32 tdm_num, क्रमागत qe_घड़ी घड़ी)
अणु
	पूर्णांक घड़ी_bits = -EINVAL;

	चयन (tdm_num) अणु
	हाल 0:
		चयन (घड़ी) अणु
		हाल QE_CLK3:
			घड़ी_bits = 6;
			अवरोध;
		हाल QE_CLK8:
			घड़ी_bits = 7;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 1:
		चयन (घड़ी) अणु
		हाल QE_CLK5:
			घड़ी_bits = 6;
			अवरोध;
		हाल QE_CLK10:
			घड़ी_bits = 7;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 2:
		चयन (घड़ी) अणु
		हाल QE_CLK7:
			घड़ी_bits = 6;
			अवरोध;
		हाल QE_CLK12:
			घड़ी_bits = 7;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 3:
		चयन (घड़ी) अणु
		हाल QE_CLK9:
			घड़ी_bits = 6;
			अवरोध;
		हाल QE_CLK14:
			घड़ी_bits = 7;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 4:
		चयन (घड़ी) अणु
		हाल QE_CLK11:
			घड़ी_bits = 6;
			अवरोध;
		हाल QE_CLK16:
			घड़ी_bits = 7;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 5:
		चयन (घड़ी) अणु
		हाल QE_CLK13:
			घड़ी_bits = 6;
			अवरोध;
		हाल QE_CLK18:
			घड़ी_bits = 7;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 6:
		चयन (घड़ी) अणु
		हाल QE_CLK15:
			घड़ी_bits = 6;
			अवरोध;
		हाल QE_CLK20:
			घड़ी_bits = 7;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 7:
		चयन (घड़ी) अणु
		हाल QE_CLK17:
			घड़ी_bits = 6;
			अवरोध;
		हाल QE_CLK22:
			घड़ी_bits = 7;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस घड़ी_bits;
पूर्ण

अटल पूर्णांक ucc_get_tdm_tx_clk(u32 tdm_num, क्रमागत qe_घड़ी घड़ी)
अणु
	पूर्णांक घड़ी_bits = -EINVAL;

	चयन (tdm_num) अणु
	हाल 0:
		चयन (घड़ी) अणु
		हाल QE_CLK4:
			घड़ी_bits = 6;
			अवरोध;
		हाल QE_CLK9:
			घड़ी_bits = 7;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 1:
		चयन (घड़ी) अणु
		हाल QE_CLK6:
			घड़ी_bits = 6;
			अवरोध;
		हाल QE_CLK11:
			घड़ी_bits = 7;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 2:
		चयन (घड़ी) अणु
		हाल QE_CLK8:
			घड़ी_bits = 6;
			अवरोध;
		हाल QE_CLK13:
			घड़ी_bits = 7;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 3:
		चयन (घड़ी) अणु
		हाल QE_CLK10:
			घड़ी_bits = 6;
			अवरोध;
		हाल QE_CLK15:
			घड़ी_bits = 7;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 4:
		चयन (घड़ी) अणु
		हाल QE_CLK12:
			घड़ी_bits = 6;
			अवरोध;
		हाल QE_CLK17:
			घड़ी_bits = 7;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 5:
		चयन (घड़ी) अणु
		हाल QE_CLK14:
			घड़ी_bits = 6;
			अवरोध;
		हाल QE_CLK19:
			घड़ी_bits = 7;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 6:
		चयन (घड़ी) अणु
		हाल QE_CLK16:
			घड़ी_bits = 6;
			अवरोध;
		हाल QE_CLK21:
			घड़ी_bits = 7;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 7:
		चयन (घड़ी) अणु
		हाल QE_CLK18:
			घड़ी_bits = 6;
			अवरोध;
		हाल QE_CLK3:
			घड़ी_bits = 7;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस घड़ी_bits;
पूर्ण

/* tdm_num: TDM A-H port num is 0-7 */
अटल पूर्णांक ucc_get_tdm_rxtx_clk(क्रमागत comm_dir mode, u32 tdm_num,
				क्रमागत qe_घड़ी घड़ी)
अणु
	पूर्णांक घड़ी_bits;

	घड़ी_bits = ucc_get_tdm_common_clk(tdm_num, घड़ी);
	अगर (घड़ी_bits > 0)
		वापस घड़ी_bits;
	अगर (mode == COMM_सूची_RX)
		घड़ी_bits = ucc_get_tdm_rx_clk(tdm_num, घड़ी);
	अगर (mode == COMM_सूची_TX)
		घड़ी_bits = ucc_get_tdm_tx_clk(tdm_num, घड़ी);
	वापस घड़ी_bits;
पूर्ण

अटल u32 ucc_get_tdm_clk_shअगरt(क्रमागत comm_dir mode, u32 tdm_num)
अणु
	u32 shअगरt;

	shअगरt = (mode == COMM_सूची_RX) ? RX_CLK_SHIFT_BASE : TX_CLK_SHIFT_BASE;
	अगर (tdm_num < 4)
		shअगरt -= tdm_num * 4;
	अन्यथा
		shअगरt -= (tdm_num - 4) * 4;

	वापस shअगरt;
पूर्ण

पूर्णांक ucc_set_tdm_rxtx_clk(u32 tdm_num, क्रमागत qe_घड़ी घड़ी,
			 क्रमागत comm_dir mode)
अणु
	पूर्णांक घड़ी_bits;
	u32 shअगरt;
	काष्ठा qe_mux __iomem *qe_mux_reg;
	__be32 __iomem *cmxs1cr;

	qe_mux_reg = &qe_immr->qmx;

	अगर (tdm_num > 7)
		वापस -EINVAL;

	/* The communications direction must be RX or TX */
	अगर (mode != COMM_सूची_RX && mode != COMM_सूची_TX)
		वापस -EINVAL;

	घड़ी_bits = ucc_get_tdm_rxtx_clk(mode, tdm_num, घड़ी);
	अगर (घड़ी_bits < 0)
		वापस -EINVAL;

	shअगरt = ucc_get_tdm_clk_shअगरt(mode, tdm_num);

	cmxs1cr = (tdm_num < 4) ? &qe_mux_reg->cmxsi1cr_l :
				  &qe_mux_reg->cmxsi1cr_h;

	qe_clrsetbits_be32(cmxs1cr, QE_CMXUCR_TX_CLK_SRC_MASK << shअगरt,
			   घड़ी_bits << shअगरt);

	वापस 0;
पूर्ण

अटल पूर्णांक ucc_get_tdm_sync_source(u32 tdm_num, क्रमागत qe_घड़ी घड़ी,
				   क्रमागत comm_dir mode)
अणु
	पूर्णांक source = -EINVAL;

	अगर (mode == COMM_सूची_RX && घड़ी == QE_RSYNC_PIN) अणु
		source = 0;
		वापस source;
	पूर्ण
	अगर (mode == COMM_सूची_TX && घड़ी == QE_TSYNC_PIN) अणु
		source = 0;
		वापस source;
	पूर्ण

	चयन (tdm_num) अणु
	हाल 0:
	हाल 1:
		चयन (घड़ी) अणु
		हाल QE_BRG9:
			source = 1;
			अवरोध;
		हाल QE_BRG10:
			source = 2;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 2:
	हाल 3:
		चयन (घड़ी) अणु
		हाल QE_BRG9:
			source = 1;
			अवरोध;
		हाल QE_BRG11:
			source = 2;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 4:
	हाल 5:
		चयन (घड़ी) अणु
		हाल QE_BRG13:
			source = 1;
			अवरोध;
		हाल QE_BRG14:
			source = 2;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 6:
	हाल 7:
		चयन (घड़ी) अणु
		हाल QE_BRG13:
			source = 1;
			अवरोध;
		हाल QE_BRG15:
			source = 2;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस source;
पूर्ण

अटल u32 ucc_get_tdm_sync_shअगरt(क्रमागत comm_dir mode, u32 tdm_num)
अणु
	u32 shअगरt;

	shअगरt = (mode == COMM_सूची_RX) ? RX_SYNC_SHIFT_BASE : TX_SYNC_SHIFT_BASE;
	shअगरt -= tdm_num * 2;

	वापस shअगरt;
पूर्ण

पूर्णांक ucc_set_tdm_rxtx_sync(u32 tdm_num, क्रमागत qe_घड़ी घड़ी,
			  क्रमागत comm_dir mode)
अणु
	पूर्णांक source;
	u32 shअगरt;
	काष्ठा qe_mux __iomem *qe_mux_reg;

	qe_mux_reg = &qe_immr->qmx;

	अगर (tdm_num >= UCC_TDM_NUM)
		वापस -EINVAL;

	/* The communications direction must be RX or TX */
	अगर (mode != COMM_सूची_RX && mode != COMM_सूची_TX)
		वापस -EINVAL;

	source = ucc_get_tdm_sync_source(tdm_num, घड़ी, mode);
	अगर (source < 0)
		वापस -EINVAL;

	shअगरt = ucc_get_tdm_sync_shअगरt(mode, tdm_num);

	qe_clrsetbits_be32(&qe_mux_reg->cmxsi1syr,
			   QE_CMXUCR_TX_CLK_SRC_MASK << shअगरt,
			   source << shअगरt);

	वापस 0;
पूर्ण
