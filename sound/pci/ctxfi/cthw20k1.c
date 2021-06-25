<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008, Creative Technology Ltd. All Rights Reserved.
 *
 * @File	cthw20k1.c
 *
 * @Brief
 * This file contains the implementation of hardware access methord क्रम 20k1.
 *
 * @Author	Liu Chun
 * @Date 	Jun 24 2008
 */

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/माला.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश "cthw20k1.h"
#समावेश "ct20k1reg.h"

काष्ठा hw20k1 अणु
	काष्ठा hw hw;
	spinlock_t reg_20k1_lock;
	spinlock_t reg_pci_lock;
पूर्ण;

अटल u32 hw_पढ़ो_20kx(काष्ठा hw *hw, u32 reg);
अटल व्योम hw_ग_लिखो_20kx(काष्ठा hw *hw, u32 reg, u32 data);
अटल u32 hw_पढ़ो_pci(काष्ठा hw *hw, u32 reg);
अटल व्योम hw_ग_लिखो_pci(काष्ठा hw *hw, u32 reg, u32 data);

/*
 * Type definition block.
 * The layout of control काष्ठाures can be directly applied on 20k2 chip.
 */

/*
 * SRC control block definitions.
 */

/* SRC resource control block */
#घोषणा SRCCTL_STATE	0x00000007
#घोषणा SRCCTL_BM	0x00000008
#घोषणा SRCCTL_RSR	0x00000030
#घोषणा SRCCTL_SF	0x000001C0
#घोषणा SRCCTL_WR	0x00000200
#घोषणा SRCCTL_PM	0x00000400
#घोषणा SRCCTL_ROM	0x00001800
#घोषणा SRCCTL_VO	0x00002000
#घोषणा SRCCTL_ST	0x00004000
#घोषणा SRCCTL_IE	0x00008000
#घोषणा SRCCTL_ILSZ	0x000F0000
#घोषणा SRCCTL_BP	0x00100000

#घोषणा SRCCCR_CISZ	0x000007FF
#घोषणा SRCCCR_CWA	0x001FF800
#घोषणा SRCCCR_D	0x00200000
#घोषणा SRCCCR_RS	0x01C00000
#घोषणा SRCCCR_NAL	0x3E000000
#घोषणा SRCCCR_RA	0xC0000000

#घोषणा SRCCA_CA	0x03FFFFFF
#घोषणा SRCCA_RS	0x1C000000
#घोषणा SRCCA_NAL	0xE0000000

#घोषणा SRCSA_SA	0x03FFFFFF

#घोषणा SRCLA_LA	0x03FFFFFF

/* Mixer Parameter Ring ram Low and Hight रेजिस्टर.
 * Fixed-poपूर्णांक value in 8.24 क्रमmat क्रम parameter channel */
#घोषणा MPRLH_PITCH	0xFFFFFFFF

/* SRC resource रेजिस्टर dirty flags */
जोड़ src_dirty अणु
	काष्ठा अणु
		u16 ctl:1;
		u16 ccr:1;
		u16 sa:1;
		u16 la:1;
		u16 ca:1;
		u16 mpr:1;
		u16 czbfs:1;	/* Clear Z-Buffers */
		u16 rsv:9;
	पूर्ण bf;
	u16 data;
पूर्ण;

काष्ठा src_rsc_ctrl_blk अणु
	अचिन्हित पूर्णांक	ctl;
	अचिन्हित पूर्णांक 	ccr;
	अचिन्हित पूर्णांक	ca;
	अचिन्हित पूर्णांक	sa;
	अचिन्हित पूर्णांक	la;
	अचिन्हित पूर्णांक	mpr;
	जोड़ src_dirty	dirty;
पूर्ण;

/* SRC manager control block */
जोड़ src_mgr_dirty अणु
	काष्ठा अणु
		u16 enb0:1;
		u16 enb1:1;
		u16 enb2:1;
		u16 enb3:1;
		u16 enb4:1;
		u16 enb5:1;
		u16 enb6:1;
		u16 enb7:1;
		u16 enbsa:1;
		u16 rsv:7;
	पूर्ण bf;
	u16 data;
पूर्ण;

काष्ठा src_mgr_ctrl_blk अणु
	अचिन्हित पूर्णांक		enbsa;
	अचिन्हित पूर्णांक		enb[8];
	जोड़ src_mgr_dirty	dirty;
पूर्ण;

/* SRCIMP manager control block */
#घोषणा SRCAIM_ARC	0x00000FFF
#घोषणा SRCAIM_NXT	0x00FF0000
#घोषणा SRCAIM_SRC	0xFF000000

काष्ठा srcimap अणु
	अचिन्हित पूर्णांक srcaim;
	अचिन्हित पूर्णांक idx;
पूर्ण;

/* SRCIMP manager रेजिस्टर dirty flags */
जोड़ srcimp_mgr_dirty अणु
	काष्ठा अणु
		u16 srcimap:1;
		u16 rsv:15;
	पूर्ण bf;
	u16 data;
पूर्ण;

काष्ठा srcimp_mgr_ctrl_blk अणु
	काष्ठा srcimap		srcimap;
	जोड़ srcimp_mgr_dirty	dirty;
पूर्ण;

/*
 * Function implementation block.
 */

अटल पूर्णांक src_get_rsc_ctrl_blk(व्योम **rblk)
अणु
	काष्ठा src_rsc_ctrl_blk *blk;

	*rblk = शून्य;
	blk = kzalloc(माप(*blk), GFP_KERNEL);
	अगर (!blk)
		वापस -ENOMEM;

	*rblk = blk;

	वापस 0;
पूर्ण

अटल पूर्णांक src_put_rsc_ctrl_blk(व्योम *blk)
अणु
	kमुक्त(blk);

	वापस 0;
पूर्ण

अटल पूर्णांक src_set_state(व्योम *blk, अचिन्हित पूर्णांक state)
अणु
	काष्ठा src_rsc_ctrl_blk *ctl = blk;

	set_field(&ctl->ctl, SRCCTL_STATE, state);
	ctl->dirty.bf.ctl = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक src_set_bm(व्योम *blk, अचिन्हित पूर्णांक bm)
अणु
	काष्ठा src_rsc_ctrl_blk *ctl = blk;

	set_field(&ctl->ctl, SRCCTL_BM, bm);
	ctl->dirty.bf.ctl = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक src_set_rsr(व्योम *blk, अचिन्हित पूर्णांक rsr)
अणु
	काष्ठा src_rsc_ctrl_blk *ctl = blk;

	set_field(&ctl->ctl, SRCCTL_RSR, rsr);
	ctl->dirty.bf.ctl = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक src_set_sf(व्योम *blk, अचिन्हित पूर्णांक sf)
अणु
	काष्ठा src_rsc_ctrl_blk *ctl = blk;

	set_field(&ctl->ctl, SRCCTL_SF, sf);
	ctl->dirty.bf.ctl = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक src_set_wr(व्योम *blk, अचिन्हित पूर्णांक wr)
अणु
	काष्ठा src_rsc_ctrl_blk *ctl = blk;

	set_field(&ctl->ctl, SRCCTL_WR, wr);
	ctl->dirty.bf.ctl = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक src_set_pm(व्योम *blk, अचिन्हित पूर्णांक pm)
अणु
	काष्ठा src_rsc_ctrl_blk *ctl = blk;

	set_field(&ctl->ctl, SRCCTL_PM, pm);
	ctl->dirty.bf.ctl = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक src_set_rom(व्योम *blk, अचिन्हित पूर्णांक rom)
अणु
	काष्ठा src_rsc_ctrl_blk *ctl = blk;

	set_field(&ctl->ctl, SRCCTL_ROM, rom);
	ctl->dirty.bf.ctl = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक src_set_vo(व्योम *blk, अचिन्हित पूर्णांक vo)
अणु
	काष्ठा src_rsc_ctrl_blk *ctl = blk;

	set_field(&ctl->ctl, SRCCTL_VO, vo);
	ctl->dirty.bf.ctl = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक src_set_st(व्योम *blk, अचिन्हित पूर्णांक st)
अणु
	काष्ठा src_rsc_ctrl_blk *ctl = blk;

	set_field(&ctl->ctl, SRCCTL_ST, st);
	ctl->dirty.bf.ctl = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक src_set_ie(व्योम *blk, अचिन्हित पूर्णांक ie)
अणु
	काष्ठा src_rsc_ctrl_blk *ctl = blk;

	set_field(&ctl->ctl, SRCCTL_IE, ie);
	ctl->dirty.bf.ctl = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक src_set_ilsz(व्योम *blk, अचिन्हित पूर्णांक ilsz)
अणु
	काष्ठा src_rsc_ctrl_blk *ctl = blk;

	set_field(&ctl->ctl, SRCCTL_ILSZ, ilsz);
	ctl->dirty.bf.ctl = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक src_set_bp(व्योम *blk, अचिन्हित पूर्णांक bp)
अणु
	काष्ठा src_rsc_ctrl_blk *ctl = blk;

	set_field(&ctl->ctl, SRCCTL_BP, bp);
	ctl->dirty.bf.ctl = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक src_set_cisz(व्योम *blk, अचिन्हित पूर्णांक cisz)
अणु
	काष्ठा src_rsc_ctrl_blk *ctl = blk;

	set_field(&ctl->ccr, SRCCCR_CISZ, cisz);
	ctl->dirty.bf.ccr = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक src_set_ca(व्योम *blk, अचिन्हित पूर्णांक ca)
अणु
	काष्ठा src_rsc_ctrl_blk *ctl = blk;

	set_field(&ctl->ca, SRCCA_CA, ca);
	ctl->dirty.bf.ca = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक src_set_sa(व्योम *blk, अचिन्हित पूर्णांक sa)
अणु
	काष्ठा src_rsc_ctrl_blk *ctl = blk;

	set_field(&ctl->sa, SRCSA_SA, sa);
	ctl->dirty.bf.sa = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक src_set_la(व्योम *blk, अचिन्हित पूर्णांक la)
अणु
	काष्ठा src_rsc_ctrl_blk *ctl = blk;

	set_field(&ctl->la, SRCLA_LA, la);
	ctl->dirty.bf.la = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक src_set_pitch(व्योम *blk, अचिन्हित पूर्णांक pitch)
अणु
	काष्ठा src_rsc_ctrl_blk *ctl = blk;

	set_field(&ctl->mpr, MPRLH_PITCH, pitch);
	ctl->dirty.bf.mpr = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक src_set_clear_zbufs(व्योम *blk, अचिन्हित पूर्णांक clear)
अणु
	((काष्ठा src_rsc_ctrl_blk *)blk)->dirty.bf.czbfs = (clear ? 1 : 0);
	वापस 0;
पूर्ण

अटल पूर्णांक src_set_dirty(व्योम *blk, अचिन्हित पूर्णांक flags)
अणु
	((काष्ठा src_rsc_ctrl_blk *)blk)->dirty.data = (flags & 0xffff);
	वापस 0;
पूर्ण

अटल पूर्णांक src_set_dirty_all(व्योम *blk)
अणु
	((काष्ठा src_rsc_ctrl_blk *)blk)->dirty.data = ~(0x0);
	वापस 0;
पूर्ण

#घोषणा AR_SLOT_SIZE		4096
#घोषणा AR_SLOT_BLOCK_SIZE	16
#घोषणा AR_PTS_PITCH		6
#घोषणा AR_PARAM_SRC_OFFSET	0x60

अटल अचिन्हित पूर्णांक src_param_pitch_mixer(अचिन्हित पूर्णांक src_idx)
अणु
	वापस ((src_idx << 4) + AR_PTS_PITCH + AR_SLOT_SIZE
			- AR_PARAM_SRC_OFFSET) % AR_SLOT_SIZE;

पूर्ण

अटल पूर्णांक src_commit_ग_लिखो(काष्ठा hw *hw, अचिन्हित पूर्णांक idx, व्योम *blk)
अणु
	काष्ठा src_rsc_ctrl_blk *ctl = blk;
	पूर्णांक i;

	अगर (ctl->dirty.bf.czbfs) अणु
		/* Clear Z-Buffer रेजिस्टरs */
		क्रम (i = 0; i < 8; i++)
			hw_ग_लिखो_20kx(hw, SRCUPZ+idx*0x100+i*0x4, 0);

		क्रम (i = 0; i < 4; i++)
			hw_ग_लिखो_20kx(hw, SRCDN0Z+idx*0x100+i*0x4, 0);

		क्रम (i = 0; i < 8; i++)
			hw_ग_लिखो_20kx(hw, SRCDN1Z+idx*0x100+i*0x4, 0);

		ctl->dirty.bf.czbfs = 0;
	पूर्ण
	अगर (ctl->dirty.bf.mpr) अणु
		/* Take the parameter mixer resource in the same group as that
		 * the idx src is in क्रम simplicity. Unlike src, all conjugate
		 * parameter mixer resources must be programmed क्रम
		 * corresponding conjugate src resources. */
		अचिन्हित पूर्णांक pm_idx = src_param_pitch_mixer(idx);
		hw_ग_लिखो_20kx(hw, PRING_LO_HI+4*pm_idx, ctl->mpr);
		hw_ग_लिखो_20kx(hw, PMOPLO+8*pm_idx, 0x3);
		hw_ग_लिखो_20kx(hw, PMOPHI+8*pm_idx, 0x0);
		ctl->dirty.bf.mpr = 0;
	पूर्ण
	अगर (ctl->dirty.bf.sa) अणु
		hw_ग_लिखो_20kx(hw, SRCSA+idx*0x100, ctl->sa);
		ctl->dirty.bf.sa = 0;
	पूर्ण
	अगर (ctl->dirty.bf.la) अणु
		hw_ग_लिखो_20kx(hw, SRCLA+idx*0x100, ctl->la);
		ctl->dirty.bf.la = 0;
	पूर्ण
	अगर (ctl->dirty.bf.ca) अणु
		hw_ग_लिखो_20kx(hw, SRCCA+idx*0x100, ctl->ca);
		ctl->dirty.bf.ca = 0;
	पूर्ण

	/* Write srccf रेजिस्टर */
	hw_ग_लिखो_20kx(hw, SRCCF+idx*0x100, 0x0);

	अगर (ctl->dirty.bf.ccr) अणु
		hw_ग_लिखो_20kx(hw, SRCCCR+idx*0x100, ctl->ccr);
		ctl->dirty.bf.ccr = 0;
	पूर्ण
	अगर (ctl->dirty.bf.ctl) अणु
		hw_ग_लिखो_20kx(hw, SRCCTL+idx*0x100, ctl->ctl);
		ctl->dirty.bf.ctl = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक src_get_ca(काष्ठा hw *hw, अचिन्हित पूर्णांक idx, व्योम *blk)
अणु
	काष्ठा src_rsc_ctrl_blk *ctl = blk;

	ctl->ca = hw_पढ़ो_20kx(hw, SRCCA+idx*0x100);
	ctl->dirty.bf.ca = 0;

	वापस get_field(ctl->ca, SRCCA_CA);
पूर्ण

अटल अचिन्हित पूर्णांक src_get_dirty(व्योम *blk)
अणु
	वापस ((काष्ठा src_rsc_ctrl_blk *)blk)->dirty.data;
पूर्ण

अटल अचिन्हित पूर्णांक src_dirty_conj_mask(व्योम)
अणु
	वापस 0x20;
पूर्ण

अटल पूर्णांक src_mgr_enbs_src(व्योम *blk, अचिन्हित पूर्णांक idx)
अणु
	((काष्ठा src_mgr_ctrl_blk *)blk)->enbsa = ~(0x0);
	((काष्ठा src_mgr_ctrl_blk *)blk)->dirty.bf.enbsa = 1;
	((काष्ठा src_mgr_ctrl_blk *)blk)->enb[idx/32] |= (0x1 << (idx%32));
	वापस 0;
पूर्ण

अटल पूर्णांक src_mgr_enb_src(व्योम *blk, अचिन्हित पूर्णांक idx)
अणु
	((काष्ठा src_mgr_ctrl_blk *)blk)->enb[idx/32] |= (0x1 << (idx%32));
	((काष्ठा src_mgr_ctrl_blk *)blk)->dirty.data |= (0x1 << (idx/32));
	वापस 0;
पूर्ण

अटल पूर्णांक src_mgr_dsb_src(व्योम *blk, अचिन्हित पूर्णांक idx)
अणु
	((काष्ठा src_mgr_ctrl_blk *)blk)->enb[idx/32] &= ~(0x1 << (idx%32));
	((काष्ठा src_mgr_ctrl_blk *)blk)->dirty.data |= (0x1 << (idx/32));
	वापस 0;
पूर्ण

अटल पूर्णांक src_mgr_commit_ग_लिखो(काष्ठा hw *hw, व्योम *blk)
अणु
	काष्ठा src_mgr_ctrl_blk *ctl = blk;
	पूर्णांक i;
	अचिन्हित पूर्णांक ret;

	अगर (ctl->dirty.bf.enbsa) अणु
		करो अणु
			ret = hw_पढ़ो_20kx(hw, SRCENBSTAT);
		पूर्ण जबतक (ret & 0x1);
		hw_ग_लिखो_20kx(hw, SRCENBS, ctl->enbsa);
		ctl->dirty.bf.enbsa = 0;
	पूर्ण
	क्रम (i = 0; i < 8; i++) अणु
		अगर ((ctl->dirty.data & (0x1 << i))) अणु
			hw_ग_लिखो_20kx(hw, SRCENB+(i*0x100), ctl->enb[i]);
			ctl->dirty.data &= ~(0x1 << i);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक src_mgr_get_ctrl_blk(व्योम **rblk)
अणु
	काष्ठा src_mgr_ctrl_blk *blk;

	*rblk = शून्य;
	blk = kzalloc(माप(*blk), GFP_KERNEL);
	अगर (!blk)
		वापस -ENOMEM;

	*rblk = blk;

	वापस 0;
पूर्ण

अटल पूर्णांक src_mgr_put_ctrl_blk(व्योम *blk)
अणु
	kमुक्त(blk);

	वापस 0;
पूर्ण

अटल पूर्णांक srcimp_mgr_get_ctrl_blk(व्योम **rblk)
अणु
	काष्ठा srcimp_mgr_ctrl_blk *blk;

	*rblk = शून्य;
	blk = kzalloc(माप(*blk), GFP_KERNEL);
	अगर (!blk)
		वापस -ENOMEM;

	*rblk = blk;

	वापस 0;
पूर्ण

अटल पूर्णांक srcimp_mgr_put_ctrl_blk(व्योम *blk)
अणु
	kमुक्त(blk);

	वापस 0;
पूर्ण

अटल पूर्णांक srcimp_mgr_set_imaparc(व्योम *blk, अचिन्हित पूर्णांक slot)
अणु
	काष्ठा srcimp_mgr_ctrl_blk *ctl = blk;

	set_field(&ctl->srcimap.srcaim, SRCAIM_ARC, slot);
	ctl->dirty.bf.srcimap = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक srcimp_mgr_set_imapuser(व्योम *blk, अचिन्हित पूर्णांक user)
अणु
	काष्ठा srcimp_mgr_ctrl_blk *ctl = blk;

	set_field(&ctl->srcimap.srcaim, SRCAIM_SRC, user);
	ctl->dirty.bf.srcimap = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक srcimp_mgr_set_imapnxt(व्योम *blk, अचिन्हित पूर्णांक next)
अणु
	काष्ठा srcimp_mgr_ctrl_blk *ctl = blk;

	set_field(&ctl->srcimap.srcaim, SRCAIM_NXT, next);
	ctl->dirty.bf.srcimap = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक srcimp_mgr_set_imapaddr(व्योम *blk, अचिन्हित पूर्णांक addr)
अणु
	काष्ठा srcimp_mgr_ctrl_blk *ctl = blk;

	ctl->srcimap.idx = addr;
	ctl->dirty.bf.srcimap = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक srcimp_mgr_commit_ग_लिखो(काष्ठा hw *hw, व्योम *blk)
अणु
	काष्ठा srcimp_mgr_ctrl_blk *ctl = blk;

	अगर (ctl->dirty.bf.srcimap) अणु
		hw_ग_लिखो_20kx(hw, SRCIMAP+ctl->srcimap.idx*0x100,
						ctl->srcimap.srcaim);
		ctl->dirty.bf.srcimap = 0;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * AMIXER control block definitions.
 */

#घोषणा AMOPLO_M	0x00000003
#घोषणा AMOPLO_X	0x0003FFF0
#घोषणा AMOPLO_Y	0xFFFC0000

#घोषणा AMOPHI_SADR	0x000000FF
#घोषणा AMOPHI_SE	0x80000000

/* AMIXER resource रेजिस्टर dirty flags */
जोड़ amixer_dirty अणु
	काष्ठा अणु
		u16 amoplo:1;
		u16 amophi:1;
		u16 rsv:14;
	पूर्ण bf;
	u16 data;
पूर्ण;

/* AMIXER resource control block */
काष्ठा amixer_rsc_ctrl_blk अणु
	अचिन्हित पूर्णांक		amoplo;
	अचिन्हित पूर्णांक		amophi;
	जोड़ amixer_dirty	dirty;
पूर्ण;

अटल पूर्णांक amixer_set_mode(व्योम *blk, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा amixer_rsc_ctrl_blk *ctl = blk;

	set_field(&ctl->amoplo, AMOPLO_M, mode);
	ctl->dirty.bf.amoplo = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक amixer_set_iv(व्योम *blk, अचिन्हित पूर्णांक iv)
अणु
	/* 20k1 amixer करोes not have this field */
	वापस 0;
पूर्ण

अटल पूर्णांक amixer_set_x(व्योम *blk, अचिन्हित पूर्णांक x)
अणु
	काष्ठा amixer_rsc_ctrl_blk *ctl = blk;

	set_field(&ctl->amoplo, AMOPLO_X, x);
	ctl->dirty.bf.amoplo = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक amixer_set_y(व्योम *blk, अचिन्हित पूर्णांक y)
अणु
	काष्ठा amixer_rsc_ctrl_blk *ctl = blk;

	set_field(&ctl->amoplo, AMOPLO_Y, y);
	ctl->dirty.bf.amoplo = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक amixer_set_sadr(व्योम *blk, अचिन्हित पूर्णांक sadr)
अणु
	काष्ठा amixer_rsc_ctrl_blk *ctl = blk;

	set_field(&ctl->amophi, AMOPHI_SADR, sadr);
	ctl->dirty.bf.amophi = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक amixer_set_se(व्योम *blk, अचिन्हित पूर्णांक se)
अणु
	काष्ठा amixer_rsc_ctrl_blk *ctl = blk;

	set_field(&ctl->amophi, AMOPHI_SE, se);
	ctl->dirty.bf.amophi = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक amixer_set_dirty(व्योम *blk, अचिन्हित पूर्णांक flags)
अणु
	((काष्ठा amixer_rsc_ctrl_blk *)blk)->dirty.data = (flags & 0xffff);
	वापस 0;
पूर्ण

अटल पूर्णांक amixer_set_dirty_all(व्योम *blk)
अणु
	((काष्ठा amixer_rsc_ctrl_blk *)blk)->dirty.data = ~(0x0);
	वापस 0;
पूर्ण

अटल पूर्णांक amixer_commit_ग_लिखो(काष्ठा hw *hw, अचिन्हित पूर्णांक idx, व्योम *blk)
अणु
	काष्ठा amixer_rsc_ctrl_blk *ctl = blk;

	अगर (ctl->dirty.bf.amoplo || ctl->dirty.bf.amophi) अणु
		hw_ग_लिखो_20kx(hw, AMOPLO+idx*8, ctl->amoplo);
		ctl->dirty.bf.amoplo = 0;
		hw_ग_लिखो_20kx(hw, AMOPHI+idx*8, ctl->amophi);
		ctl->dirty.bf.amophi = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक amixer_get_y(व्योम *blk)
अणु
	काष्ठा amixer_rsc_ctrl_blk *ctl = blk;

	वापस get_field(ctl->amoplo, AMOPLO_Y);
पूर्ण

अटल अचिन्हित पूर्णांक amixer_get_dirty(व्योम *blk)
अणु
	वापस ((काष्ठा amixer_rsc_ctrl_blk *)blk)->dirty.data;
पूर्ण

अटल पूर्णांक amixer_rsc_get_ctrl_blk(व्योम **rblk)
अणु
	काष्ठा amixer_rsc_ctrl_blk *blk;

	*rblk = शून्य;
	blk = kzalloc(माप(*blk), GFP_KERNEL);
	अगर (!blk)
		वापस -ENOMEM;

	*rblk = blk;

	वापस 0;
पूर्ण

अटल पूर्णांक amixer_rsc_put_ctrl_blk(व्योम *blk)
अणु
	kमुक्त(blk);

	वापस 0;
पूर्ण

अटल पूर्णांक amixer_mgr_get_ctrl_blk(व्योम **rblk)
अणु
	/*amixer_mgr_ctrl_blk_t *blk;*/

	*rblk = शून्य;
	/*blk = kzalloc(माप(*blk), GFP_KERNEL);
	अगर (!blk)
		वापस -ENOMEM;

	*rblk = blk;*/

	वापस 0;
पूर्ण

अटल पूर्णांक amixer_mgr_put_ctrl_blk(व्योम *blk)
अणु
	/*kमुक्त((amixer_mgr_ctrl_blk_t *)blk);*/

	वापस 0;
पूर्ण

/*
 * DAIO control block definitions.
 */

/* Receiver Sample Rate Tracker Control रेजिस्टर */
#घोषणा SRTCTL_SRCR	0x000000FF
#घोषणा SRTCTL_SRCL	0x0000FF00
#घोषणा SRTCTL_RSR	0x00030000
#घोषणा SRTCTL_DRAT	0x000C0000
#घोषणा SRTCTL_RLE	0x10000000
#घोषणा SRTCTL_RLP	0x20000000
#घोषणा SRTCTL_EC	0x40000000
#घोषणा SRTCTL_ET	0x80000000

/* DAIO Receiver रेजिस्टर dirty flags */
जोड़ dai_dirty अणु
	काष्ठा अणु
		u16 srtctl:1;
		u16 rsv:15;
	पूर्ण bf;
	u16 data;
पूर्ण;

/* DAIO Receiver control block */
काष्ठा dai_ctrl_blk अणु
	अचिन्हित पूर्णांक	srtctl;
	जोड़ dai_dirty	dirty;
पूर्ण;

/* S/PDIF Transmitter रेजिस्टर dirty flags */
जोड़ dao_dirty अणु
	काष्ठा अणु
		u16 spos:1;
		u16 rsv:15;
	पूर्ण bf;
	u16 data;
पूर्ण;

/* S/PDIF Transmitter control block */
काष्ठा dao_ctrl_blk अणु
	अचिन्हित पूर्णांक 	spos; /* S/PDIF Output Channel Status Register */
	जोड़ dao_dirty	dirty;
पूर्ण;

/* Audio Input Mapper RAM */
#घोषणा AIM_ARC		0x00000FFF
#घोषणा AIM_NXT		0x007F0000

काष्ठा daoimap अणु
	अचिन्हित पूर्णांक aim;
	अचिन्हित पूर्णांक idx;
पूर्ण;

/* I2S Transmitter/Receiver Control रेजिस्टर */
#घोषणा I2SCTL_EA	0x00000004
#घोषणा I2SCTL_EI	0x00000010

/* S/PDIF Transmitter Control रेजिस्टर */
#घोषणा SPOCTL_OE	0x00000001
#घोषणा SPOCTL_OS	0x0000000E
#घोषणा SPOCTL_RIV	0x00000010
#घोषणा SPOCTL_LIV	0x00000020
#घोषणा SPOCTL_SR	0x000000C0

/* S/PDIF Receiver Control रेजिस्टर */
#घोषणा SPICTL_EN	0x00000001
#घोषणा SPICTL_I24	0x00000002
#घोषणा SPICTL_IB	0x00000004
#घोषणा SPICTL_SM	0x00000008
#घोषणा SPICTL_VM	0x00000010

/* DAIO manager रेजिस्टर dirty flags */
जोड़ daio_mgr_dirty अणु
	काष्ठा अणु
		u32 i2soctl:4;
		u32 i2sictl:4;
		u32 spoctl:4;
		u32 spictl:4;
		u32 daoimap:1;
		u32 rsv:15;
	पूर्ण bf;
	u32 data;
पूर्ण;

/* DAIO manager control block */
काष्ठा daio_mgr_ctrl_blk अणु
	अचिन्हित पूर्णांक		i2sctl;
	अचिन्हित पूर्णांक		spoctl;
	अचिन्हित पूर्णांक		spictl;
	काष्ठा daoimap		daoimap;
	जोड़ daio_mgr_dirty	dirty;
पूर्ण;

अटल पूर्णांक dai_srt_set_srcr(व्योम *blk, अचिन्हित पूर्णांक src)
अणु
	काष्ठा dai_ctrl_blk *ctl = blk;

	set_field(&ctl->srtctl, SRTCTL_SRCR, src);
	ctl->dirty.bf.srtctl = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक dai_srt_set_srcl(व्योम *blk, अचिन्हित पूर्णांक src)
अणु
	काष्ठा dai_ctrl_blk *ctl = blk;

	set_field(&ctl->srtctl, SRTCTL_SRCL, src);
	ctl->dirty.bf.srtctl = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक dai_srt_set_rsr(व्योम *blk, अचिन्हित पूर्णांक rsr)
अणु
	काष्ठा dai_ctrl_blk *ctl = blk;

	set_field(&ctl->srtctl, SRTCTL_RSR, rsr);
	ctl->dirty.bf.srtctl = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक dai_srt_set_drat(व्योम *blk, अचिन्हित पूर्णांक drat)
अणु
	काष्ठा dai_ctrl_blk *ctl = blk;

	set_field(&ctl->srtctl, SRTCTL_DRAT, drat);
	ctl->dirty.bf.srtctl = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक dai_srt_set_ec(व्योम *blk, अचिन्हित पूर्णांक ec)
अणु
	काष्ठा dai_ctrl_blk *ctl = blk;

	set_field(&ctl->srtctl, SRTCTL_EC, ec ? 1 : 0);
	ctl->dirty.bf.srtctl = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक dai_srt_set_et(व्योम *blk, अचिन्हित पूर्णांक et)
अणु
	काष्ठा dai_ctrl_blk *ctl = blk;

	set_field(&ctl->srtctl, SRTCTL_ET, et ? 1 : 0);
	ctl->dirty.bf.srtctl = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक dai_commit_ग_लिखो(काष्ठा hw *hw, अचिन्हित पूर्णांक idx, व्योम *blk)
अणु
	काष्ठा dai_ctrl_blk *ctl = blk;

	अगर (ctl->dirty.bf.srtctl) अणु
		अगर (idx < 4) अणु
			/* S/PDIF SRTs */
			hw_ग_लिखो_20kx(hw, SRTSCTL+0x4*idx, ctl->srtctl);
		पूर्ण अन्यथा अणु
			/* I2S SRT */
			hw_ग_लिखो_20kx(hw, SRTICTL, ctl->srtctl);
		पूर्ण
		ctl->dirty.bf.srtctl = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dai_get_ctrl_blk(व्योम **rblk)
अणु
	काष्ठा dai_ctrl_blk *blk;

	*rblk = शून्य;
	blk = kzalloc(माप(*blk), GFP_KERNEL);
	अगर (!blk)
		वापस -ENOMEM;

	*rblk = blk;

	वापस 0;
पूर्ण

अटल पूर्णांक dai_put_ctrl_blk(व्योम *blk)
अणु
	kमुक्त(blk);

	वापस 0;
पूर्ण

अटल पूर्णांक dao_set_spos(व्योम *blk, अचिन्हित पूर्णांक spos)
अणु
	((काष्ठा dao_ctrl_blk *)blk)->spos = spos;
	((काष्ठा dao_ctrl_blk *)blk)->dirty.bf.spos = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक dao_commit_ग_लिखो(काष्ठा hw *hw, अचिन्हित पूर्णांक idx, व्योम *blk)
अणु
	काष्ठा dao_ctrl_blk *ctl = blk;

	अगर (ctl->dirty.bf.spos) अणु
		अगर (idx < 4) अणु
			/* S/PDIF SPOSx */
			hw_ग_लिखो_20kx(hw, SPOS+0x4*idx, ctl->spos);
		पूर्ण
		ctl->dirty.bf.spos = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dao_get_spos(व्योम *blk, अचिन्हित पूर्णांक *spos)
अणु
	*spos = ((काष्ठा dao_ctrl_blk *)blk)->spos;
	वापस 0;
पूर्ण

अटल पूर्णांक dao_get_ctrl_blk(व्योम **rblk)
अणु
	काष्ठा dao_ctrl_blk *blk;

	*rblk = शून्य;
	blk = kzalloc(माप(*blk), GFP_KERNEL);
	अगर (!blk)
		वापस -ENOMEM;

	*rblk = blk;

	वापस 0;
पूर्ण

अटल पूर्णांक dao_put_ctrl_blk(व्योम *blk)
अणु
	kमुक्त(blk);

	वापस 0;
पूर्ण

अटल पूर्णांक daio_mgr_enb_dai(व्योम *blk, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा daio_mgr_ctrl_blk *ctl = blk;

	अगर (idx < 4) अणु
		/* S/PDIF input */
		set_field(&ctl->spictl, SPICTL_EN << (idx*8), 1);
		ctl->dirty.bf.spictl |= (0x1 << idx);
	पूर्ण अन्यथा अणु
		/* I2S input */
		idx %= 4;
		set_field(&ctl->i2sctl, I2SCTL_EI << (idx*8), 1);
		ctl->dirty.bf.i2sictl |= (0x1 << idx);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक daio_mgr_dsb_dai(व्योम *blk, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा daio_mgr_ctrl_blk *ctl = blk;

	अगर (idx < 4) अणु
		/* S/PDIF input */
		set_field(&ctl->spictl, SPICTL_EN << (idx*8), 0);
		ctl->dirty.bf.spictl |= (0x1 << idx);
	पूर्ण अन्यथा अणु
		/* I2S input */
		idx %= 4;
		set_field(&ctl->i2sctl, I2SCTL_EI << (idx*8), 0);
		ctl->dirty.bf.i2sictl |= (0x1 << idx);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक daio_mgr_enb_dao(व्योम *blk, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा daio_mgr_ctrl_blk *ctl = blk;

	अगर (idx < 4) अणु
		/* S/PDIF output */
		set_field(&ctl->spoctl, SPOCTL_OE << (idx*8), 1);
		ctl->dirty.bf.spoctl |= (0x1 << idx);
	पूर्ण अन्यथा अणु
		/* I2S output */
		idx %= 4;
		set_field(&ctl->i2sctl, I2SCTL_EA << (idx*8), 1);
		ctl->dirty.bf.i2soctl |= (0x1 << idx);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक daio_mgr_dsb_dao(व्योम *blk, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा daio_mgr_ctrl_blk *ctl = blk;

	अगर (idx < 4) अणु
		/* S/PDIF output */
		set_field(&ctl->spoctl, SPOCTL_OE << (idx*8), 0);
		ctl->dirty.bf.spoctl |= (0x1 << idx);
	पूर्ण अन्यथा अणु
		/* I2S output */
		idx %= 4;
		set_field(&ctl->i2sctl, I2SCTL_EA << (idx*8), 0);
		ctl->dirty.bf.i2soctl |= (0x1 << idx);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक daio_mgr_dao_init(व्योम *blk, अचिन्हित पूर्णांक idx, अचिन्हित पूर्णांक conf)
अणु
	काष्ठा daio_mgr_ctrl_blk *ctl = blk;

	अगर (idx < 4) अणु
		/* S/PDIF output */
		चयन ((conf & 0x7)) अणु
		हाल 0:
			set_field(&ctl->spoctl, SPOCTL_SR << (idx*8), 3);
			अवरोध; /* CDIF */
		हाल 1:
			set_field(&ctl->spoctl, SPOCTL_SR << (idx*8), 0);
			अवरोध;
		हाल 2:
			set_field(&ctl->spoctl, SPOCTL_SR << (idx*8), 1);
			अवरोध;
		हाल 4:
			set_field(&ctl->spoctl, SPOCTL_SR << (idx*8), 2);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		set_field(&ctl->spoctl, SPOCTL_LIV << (idx*8),
			  (conf >> 4) & 0x1); /* Non-audio */
		set_field(&ctl->spoctl, SPOCTL_RIV << (idx*8),
			  (conf >> 4) & 0x1); /* Non-audio */
		set_field(&ctl->spoctl, SPOCTL_OS << (idx*8),
			  ((conf >> 3) & 0x1) ? 2 : 2); /* Raw */

		ctl->dirty.bf.spoctl |= (0x1 << idx);
	पूर्ण अन्यथा अणु
		/* I2S output */
		/*idx %= 4; */
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक daio_mgr_set_imaparc(व्योम *blk, अचिन्हित पूर्णांक slot)
अणु
	काष्ठा daio_mgr_ctrl_blk *ctl = blk;

	set_field(&ctl->daoimap.aim, AIM_ARC, slot);
	ctl->dirty.bf.daoimap = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक daio_mgr_set_imapnxt(व्योम *blk, अचिन्हित पूर्णांक next)
अणु
	काष्ठा daio_mgr_ctrl_blk *ctl = blk;

	set_field(&ctl->daoimap.aim, AIM_NXT, next);
	ctl->dirty.bf.daoimap = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक daio_mgr_set_imapaddr(व्योम *blk, अचिन्हित पूर्णांक addr)
अणु
	काष्ठा daio_mgr_ctrl_blk *ctl = blk;

	ctl->daoimap.idx = addr;
	ctl->dirty.bf.daoimap = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक daio_mgr_commit_ग_लिखो(काष्ठा hw *hw, व्योम *blk)
अणु
	काष्ठा daio_mgr_ctrl_blk *ctl = blk;
	पूर्णांक i;

	अगर (ctl->dirty.bf.i2sictl || ctl->dirty.bf.i2soctl) अणु
		क्रम (i = 0; i < 4; i++) अणु
			अगर ((ctl->dirty.bf.i2sictl & (0x1 << i)))
				ctl->dirty.bf.i2sictl &= ~(0x1 << i);

			अगर ((ctl->dirty.bf.i2soctl & (0x1 << i)))
				ctl->dirty.bf.i2soctl &= ~(0x1 << i);
		पूर्ण
		hw_ग_लिखो_20kx(hw, I2SCTL, ctl->i2sctl);
		mdelay(1);
	पूर्ण
	अगर (ctl->dirty.bf.spoctl) अणु
		क्रम (i = 0; i < 4; i++) अणु
			अगर ((ctl->dirty.bf.spoctl & (0x1 << i)))
				ctl->dirty.bf.spoctl &= ~(0x1 << i);
		पूर्ण
		hw_ग_लिखो_20kx(hw, SPOCTL, ctl->spoctl);
		mdelay(1);
	पूर्ण
	अगर (ctl->dirty.bf.spictl) अणु
		क्रम (i = 0; i < 4; i++) अणु
			अगर ((ctl->dirty.bf.spictl & (0x1 << i)))
				ctl->dirty.bf.spictl &= ~(0x1 << i);
		पूर्ण
		hw_ग_लिखो_20kx(hw, SPICTL, ctl->spictl);
		mdelay(1);
	पूर्ण
	अगर (ctl->dirty.bf.daoimap) अणु
		hw_ग_लिखो_20kx(hw, DAOIMAP+ctl->daoimap.idx*4,
					ctl->daoimap.aim);
		ctl->dirty.bf.daoimap = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक daio_mgr_get_ctrl_blk(काष्ठा hw *hw, व्योम **rblk)
अणु
	काष्ठा daio_mgr_ctrl_blk *blk;

	*rblk = शून्य;
	blk = kzalloc(माप(*blk), GFP_KERNEL);
	अगर (!blk)
		वापस -ENOMEM;

	blk->i2sctl = hw_पढ़ो_20kx(hw, I2SCTL);
	blk->spoctl = hw_पढ़ो_20kx(hw, SPOCTL);
	blk->spictl = hw_पढ़ो_20kx(hw, SPICTL);

	*rblk = blk;

	वापस 0;
पूर्ण

अटल पूर्णांक daio_mgr_put_ctrl_blk(व्योम *blk)
अणु
	kमुक्त(blk);

	वापस 0;
पूर्ण

/* Timer पूर्णांकerrupt */
अटल पूर्णांक set_समयr_irq(काष्ठा hw *hw, पूर्णांक enable)
अणु
	hw_ग_लिखो_20kx(hw, GIE, enable ? IT_INT : 0);
	वापस 0;
पूर्ण

अटल पूर्णांक set_समयr_tick(काष्ठा hw *hw, अचिन्हित पूर्णांक ticks)
अणु
	अगर (ticks)
		ticks |= TIMR_IE | TIMR_IP;
	hw_ग_लिखो_20kx(hw, TIMR, ticks);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक get_wc(काष्ठा hw *hw)
अणु
	वापस hw_पढ़ो_20kx(hw, WC);
पूर्ण

/* Card hardware initialization block */
काष्ठा dac_conf अणु
	अचिन्हित पूर्णांक msr; /* master sample rate in rsrs */
पूर्ण;

काष्ठा adc_conf अणु
	अचिन्हित पूर्णांक msr; 	/* master sample rate in rsrs */
	अचिन्हित अक्षर input; 	/* the input source of ADC */
	अचिन्हित अक्षर mic20db; 	/* boost mic by 20db अगर input is microphone */
पूर्ण;

काष्ठा daio_conf अणु
	अचिन्हित पूर्णांक msr; /* master sample rate in rsrs */
पूर्ण;

काष्ठा trn_conf अणु
	अचिन्हित दीर्घ vm_pgt_phys;
पूर्ण;

अटल पूर्णांक hw_daio_init(काष्ठा hw *hw, स्थिर काष्ठा daio_conf *info)
अणु
	u32 i2sorg;
	u32 spकरोrg;

	/* Read I2S CTL.  Keep original value. */
	/*i2sorg = hw_पढ़ो_20kx(hw, I2SCTL);*/
	i2sorg = 0x94040404; /* enable all audio out and I2S-D input */
	/* Program I2S with proper master sample rate and enable
	 * the correct I2S channel. */
	i2sorg &= 0xfffffffc;

	/* Enable S/PDIF-out-A in fixed 24-bit data
	 * क्रमmat and शेष to 48kHz. */
	/* Disable all beक्रमe करोing any changes. */
	hw_ग_लिखो_20kx(hw, SPOCTL, 0x0);
	spकरोrg = 0x05;

	चयन (info->msr) अणु
	हाल 1:
		i2sorg |= 1;
		spकरोrg |= (0x0 << 6);
		अवरोध;
	हाल 2:
		i2sorg |= 2;
		spकरोrg |= (0x1 << 6);
		अवरोध;
	हाल 4:
		i2sorg |= 3;
		spकरोrg |= (0x2 << 6);
		अवरोध;
	शेष:
		i2sorg |= 1;
		अवरोध;
	पूर्ण

	hw_ग_लिखो_20kx(hw, I2SCTL, i2sorg);
	hw_ग_लिखो_20kx(hw, SPOCTL, spकरोrg);

	/* Enable S/PDIF-in-A in fixed 24-bit data क्रमmat. */
	/* Disable all beक्रमe करोing any changes. */
	hw_ग_लिखो_20kx(hw, SPICTL, 0x0);
	mdelay(1);
	spकरोrg = 0x0a0a0a0a;
	hw_ग_लिखो_20kx(hw, SPICTL, spकरोrg);
	mdelay(1);

	वापस 0;
पूर्ण

/* TRANSPORT operations */
अटल पूर्णांक hw_trn_init(काष्ठा hw *hw, स्थिर काष्ठा trn_conf *info)
अणु
	u32 trnctl;
	u32 ptp_phys_low, ptp_phys_high;

	/* Set up device page table */
	अगर ((~0UL) == info->vm_pgt_phys) अणु
		dev_err(hw->card->dev,
			"Wrong device page table page address!\n");
		वापस -1;
	पूर्ण

	trnctl = 0x13;  /* 32-bit, 4k-size page */
	ptp_phys_low = (u32)info->vm_pgt_phys;
	ptp_phys_high = upper_32_bits(info->vm_pgt_phys);
	अगर (माप(व्योम *) == 8) /* 64bit address */
		trnctl |= (1 << 2);
#अगर 0 /* Only 4k h/w pages क्रम simplicitiy */
#अगर PAGE_SIZE == 8192
	trnctl |= (1<<5);
#पूर्ण_अगर
#पूर्ण_अगर
	hw_ग_लिखो_20kx(hw, PTPALX, ptp_phys_low);
	hw_ग_लिखो_20kx(hw, PTPAHX, ptp_phys_high);
	hw_ग_लिखो_20kx(hw, TRNCTL, trnctl);
	hw_ग_लिखो_20kx(hw, TRNIS, 0x200c01); /* really needed? */

	वापस 0;
पूर्ण

/* Card initialization */
#घोषणा GCTL_EAC	0x00000001
#घोषणा GCTL_EAI	0x00000002
#घोषणा GCTL_BEP	0x00000004
#घोषणा GCTL_BES	0x00000008
#घोषणा GCTL_DSP	0x00000010
#घोषणा GCTL_DBP	0x00000020
#घोषणा GCTL_ABP	0x00000040
#घोषणा GCTL_TBP	0x00000080
#घोषणा GCTL_SBP	0x00000100
#घोषणा GCTL_FBP	0x00000200
#घोषणा GCTL_XA		0x00000400
#घोषणा GCTL_ET		0x00000800
#घोषणा GCTL_PR		0x00001000
#घोषणा GCTL_MRL	0x00002000
#घोषणा GCTL_SDE	0x00004000
#घोषणा GCTL_SDI	0x00008000
#घोषणा GCTL_SM		0x00010000
#घोषणा GCTL_SR		0x00020000
#घोषणा GCTL_SD		0x00040000
#घोषणा GCTL_SE		0x00080000
#घोषणा GCTL_AID	0x00100000

अटल पूर्णांक hw_pll_init(काष्ठा hw *hw, अचिन्हित पूर्णांक rsr)
अणु
	अचिन्हित पूर्णांक pllctl;
	पूर्णांक i;

	pllctl = (48000 == rsr) ? 0x1480a001 : 0x1480a731;
	क्रम (i = 0; i < 3; i++) अणु
		अगर (hw_पढ़ो_20kx(hw, PLLCTL) == pllctl)
			अवरोध;

		hw_ग_लिखो_20kx(hw, PLLCTL, pllctl);
		msleep(40);
	पूर्ण
	अगर (i >= 3) अणु
		dev_alert(hw->card->dev, "PLL initialization failed!!!\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hw_स्वतः_init(काष्ठा hw *hw)
अणु
	अचिन्हित पूर्णांक gctl;
	पूर्णांक i;

	gctl = hw_पढ़ो_20kx(hw, GCTL);
	set_field(&gctl, GCTL_EAI, 0);
	hw_ग_लिखो_20kx(hw, GCTL, gctl);
	set_field(&gctl, GCTL_EAI, 1);
	hw_ग_लिखो_20kx(hw, GCTL, gctl);
	mdelay(10);
	क्रम (i = 0; i < 400000; i++) अणु
		gctl = hw_पढ़ो_20kx(hw, GCTL);
		अगर (get_field(gctl, GCTL_AID))
			अवरोध;
	पूर्ण
	अगर (!get_field(gctl, GCTL_AID)) अणु
		dev_alert(hw->card->dev, "Card Auto-init failed!!!\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_unlock(काष्ठा hw *hw)
अणु
	अगर ((hw_पढ़ो_pci(hw, 0xcc) & 0xff) == 0xaa)
		वापस 0;

	hw_ग_लिखो_pci(hw, 0xcc, 0x8c);
	hw_ग_लिखो_pci(hw, 0xcc, 0x0e);
	अगर ((hw_पढ़ो_pci(hw, 0xcc) & 0xff) == 0xaa)
		वापस 0;

	hw_ग_लिखो_pci(hw, 0xcc, 0xee);
	hw_ग_लिखो_pci(hw, 0xcc, 0xaa);
	अगर ((hw_पढ़ो_pci(hw, 0xcc) & 0xff) == 0xaa)
		वापस 0;

	वापस -1;
पूर्ण

अटल व्योम i2c_lock(काष्ठा hw *hw)
अणु
	अगर ((hw_पढ़ो_pci(hw, 0xcc) & 0xff) == 0xaa)
		hw_ग_लिखो_pci(hw, 0xcc, 0x00);
पूर्ण

अटल व्योम i2c_ग_लिखो(काष्ठा hw *hw, u32 device, u32 addr, u32 data)
अणु
	अचिन्हित पूर्णांक ret;

	करो अणु
		ret = hw_पढ़ो_pci(hw, 0xEC);
	पूर्ण जबतक (!(ret & 0x800000));
	hw_ग_लिखो_pci(hw, 0xE0, device);
	hw_ग_लिखो_pci(hw, 0xE4, (data << 8) | (addr & 0xff));
पूर्ण

/* DAC operations */

अटल पूर्णांक hw_reset_dac(काष्ठा hw *hw)
अणु
	u32 i;
	u16 gpioorg;
	अचिन्हित पूर्णांक ret;

	अगर (i2c_unlock(hw))
		वापस -1;

	करो अणु
		ret = hw_पढ़ो_pci(hw, 0xEC);
	पूर्ण जबतक (!(ret & 0x800000));
	hw_ग_लिखो_pci(hw, 0xEC, 0x05);  /* ग_लिखो to i2c status control */

	/* To be effective, need to reset the DAC twice. */
	क्रम (i = 0; i < 2;  i++) अणु
		/* set gpio */
		msleep(100);
		gpioorg = (u16)hw_पढ़ो_20kx(hw, GPIO);
		gpioorg &= 0xfffd;
		hw_ग_लिखो_20kx(hw, GPIO, gpioorg);
		mdelay(1);
		hw_ग_लिखो_20kx(hw, GPIO, gpioorg | 0x2);
	पूर्ण

	i2c_ग_लिखो(hw, 0x00180080, 0x01, 0x80);
	i2c_ग_लिखो(hw, 0x00180080, 0x02, 0x10);

	i2c_lock(hw);

	वापस 0;
पूर्ण

अटल पूर्णांक hw_dac_init(काष्ठा hw *hw, स्थिर काष्ठा dac_conf *info)
अणु
	u32 data;
	u16 gpioorg;
	अचिन्हित पूर्णांक ret;

	अगर (hw->model == CTSB055X) अणु
		/* SB055x, unmute outमाला_दो */
		gpioorg = (u16)hw_पढ़ो_20kx(hw, GPIO);
		gpioorg &= 0xffbf;	/* set GPIO6 to low */
		gpioorg |= 2;		/* set GPIO1 to high */
		hw_ग_लिखो_20kx(hw, GPIO, gpioorg);
		वापस 0;
	पूर्ण

	/* mute outमाला_दो */
	gpioorg = (u16)hw_पढ़ो_20kx(hw, GPIO);
	gpioorg &= 0xffbf;
	hw_ग_लिखो_20kx(hw, GPIO, gpioorg);

	hw_reset_dac(hw);

	अगर (i2c_unlock(hw))
		वापस -1;

	hw_ग_लिखो_pci(hw, 0xEC, 0x05);  /* ग_लिखो to i2c status control */
	करो अणु
		ret = hw_पढ़ो_pci(hw, 0xEC);
	पूर्ण जबतक (!(ret & 0x800000));

	चयन (info->msr) अणु
	हाल 1:
		data = 0x24;
		अवरोध;
	हाल 2:
		data = 0x25;
		अवरोध;
	हाल 4:
		data = 0x26;
		अवरोध;
	शेष:
		data = 0x24;
		अवरोध;
	पूर्ण

	i2c_ग_लिखो(hw, 0x00180080, 0x06, data);
	i2c_ग_लिखो(hw, 0x00180080, 0x09, data);
	i2c_ग_लिखो(hw, 0x00180080, 0x0c, data);
	i2c_ग_लिखो(hw, 0x00180080, 0x0f, data);

	i2c_lock(hw);

	/* unmute outमाला_दो */
	gpioorg = (u16)hw_पढ़ो_20kx(hw, GPIO);
	gpioorg = gpioorg | 0x40;
	hw_ग_लिखो_20kx(hw, GPIO, gpioorg);

	वापस 0;
पूर्ण

/* ADC operations */

अटल पूर्णांक is_adc_input_selected_SB055x(काष्ठा hw *hw, क्रमागत ADCSRC type)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक is_adc_input_selected_SBx(काष्ठा hw *hw, क्रमागत ADCSRC type)
अणु
	u32 data;

	data = hw_पढ़ो_20kx(hw, GPIO);
	चयन (type) अणु
	हाल ADC_MICIN:
		data = ((data & (0x1<<7)) && (data & (0x1<<8)));
		अवरोध;
	हाल ADC_LINEIN:
		data = (!(data & (0x1<<7)) && (data & (0x1<<8)));
		अवरोध;
	हाल ADC_NONE: /* Digital I/O */
		data = (!(data & (0x1<<8)));
		अवरोध;
	शेष:
		data = 0;
	पूर्ण
	वापस data;
पूर्ण

अटल पूर्णांक is_adc_input_selected_hendrix(काष्ठा hw *hw, क्रमागत ADCSRC type)
अणु
	u32 data;

	data = hw_पढ़ो_20kx(hw, GPIO);
	चयन (type) अणु
	हाल ADC_MICIN:
		data = (data & (0x1 << 7)) ? 1 : 0;
		अवरोध;
	हाल ADC_LINEIN:
		data = (data & (0x1 << 7)) ? 0 : 1;
		अवरोध;
	शेष:
		data = 0;
	पूर्ण
	वापस data;
पूर्ण

अटल पूर्णांक hw_is_adc_input_selected(काष्ठा hw *hw, क्रमागत ADCSRC type)
अणु
	चयन (hw->model) अणु
	हाल CTSB055X:
		वापस is_adc_input_selected_SB055x(hw, type);
	हाल CTSB073X:
		वापस is_adc_input_selected_hendrix(hw, type);
	हाल CTUAA:
		वापस is_adc_input_selected_hendrix(hw, type);
	शेष:
		वापस is_adc_input_selected_SBx(hw, type);
	पूर्ण
पूर्ण

अटल पूर्णांक
adc_input_select_SB055x(काष्ठा hw *hw, क्रमागत ADCSRC type, अचिन्हित अक्षर boost)
अणु
	u32 data;

	/*
	 * check and set the following GPIO bits accordingly
	 * ADC_Gain		= GPIO2
	 * DRM_off		= GPIO3
	 * Mic_Pwr_on		= GPIO7
	 * Digital_IO_Sel	= GPIO8
	 * Mic_Sw		= GPIO9
	 * Aux/MicLine_Sw	= GPIO12
	 */
	data = hw_पढ़ो_20kx(hw, GPIO);
	data &= 0xec73;
	चयन (type) अणु
	हाल ADC_MICIN:
		data |= (0x1<<7) | (0x1<<8) | (0x1<<9) ;
		data |= boost ? (0x1<<2) : 0;
		अवरोध;
	हाल ADC_LINEIN:
		data |= (0x1<<8);
		अवरोध;
	हाल ADC_AUX:
		data |= (0x1<<8) | (0x1<<12);
		अवरोध;
	हाल ADC_NONE:
		data |= (0x1<<12);  /* set to digital */
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	hw_ग_लिखो_20kx(hw, GPIO, data);

	वापस 0;
पूर्ण


अटल पूर्णांक
adc_input_select_SBx(काष्ठा hw *hw, क्रमागत ADCSRC type, अचिन्हित अक्षर boost)
अणु
	u32 data;
	u32 i2c_data;
	अचिन्हित पूर्णांक ret;

	अगर (i2c_unlock(hw))
		वापस -1;

	करो अणु
		ret = hw_पढ़ो_pci(hw, 0xEC);
	पूर्ण जबतक (!(ret & 0x800000)); /* i2c पढ़ोy poll */
	/* set i2c access mode as Direct Control */
	hw_ग_लिखो_pci(hw, 0xEC, 0x05);

	data = hw_पढ़ो_20kx(hw, GPIO);
	चयन (type) अणु
	हाल ADC_MICIN:
		data |= ((0x1 << 7) | (0x1 << 8));
		i2c_data = 0x1;  /* Mic-in */
		अवरोध;
	हाल ADC_LINEIN:
		data &= ~(0x1 << 7);
		data |= (0x1 << 8);
		i2c_data = 0x2; /* Line-in */
		अवरोध;
	हाल ADC_NONE:
		data &= ~(0x1 << 8);
		i2c_data = 0x0; /* set to Digital */
		अवरोध;
	शेष:
		i2c_lock(hw);
		वापस -1;
	पूर्ण
	hw_ग_लिखो_20kx(hw, GPIO, data);
	i2c_ग_लिखो(hw, 0x001a0080, 0x2a, i2c_data);
	अगर (boost) अणु
		i2c_ग_लिखो(hw, 0x001a0080, 0x1c, 0xe7); /* +12dB boost */
		i2c_ग_लिखो(hw, 0x001a0080, 0x1e, 0xe7); /* +12dB boost */
	पूर्ण अन्यथा अणु
		i2c_ग_लिखो(hw, 0x001a0080, 0x1c, 0xcf); /* No boost */
		i2c_ग_लिखो(hw, 0x001a0080, 0x1e, 0xcf); /* No boost */
	पूर्ण

	i2c_lock(hw);

	वापस 0;
पूर्ण

अटल पूर्णांक
adc_input_select_hendrix(काष्ठा hw *hw, क्रमागत ADCSRC type, अचिन्हित अक्षर boost)
अणु
	u32 data;
	u32 i2c_data;
	अचिन्हित पूर्णांक ret;

	अगर (i2c_unlock(hw))
		वापस -1;

	करो अणु
		ret = hw_पढ़ो_pci(hw, 0xEC);
	पूर्ण जबतक (!(ret & 0x800000)); /* i2c पढ़ोy poll */
	/* set i2c access mode as Direct Control */
	hw_ग_लिखो_pci(hw, 0xEC, 0x05);

	data = hw_पढ़ो_20kx(hw, GPIO);
	चयन (type) अणु
	हाल ADC_MICIN:
		data |= (0x1 << 7);
		i2c_data = 0x1;  /* Mic-in */
		अवरोध;
	हाल ADC_LINEIN:
		data &= ~(0x1 << 7);
		i2c_data = 0x2; /* Line-in */
		अवरोध;
	शेष:
		i2c_lock(hw);
		वापस -1;
	पूर्ण
	hw_ग_लिखो_20kx(hw, GPIO, data);
	i2c_ग_लिखो(hw, 0x001a0080, 0x2a, i2c_data);
	अगर (boost) अणु
		i2c_ग_लिखो(hw, 0x001a0080, 0x1c, 0xe7); /* +12dB boost */
		i2c_ग_लिखो(hw, 0x001a0080, 0x1e, 0xe7); /* +12dB boost */
	पूर्ण अन्यथा अणु
		i2c_ग_लिखो(hw, 0x001a0080, 0x1c, 0xcf); /* No boost */
		i2c_ग_लिखो(hw, 0x001a0080, 0x1e, 0xcf); /* No boost */
	पूर्ण

	i2c_lock(hw);

	वापस 0;
पूर्ण

अटल पूर्णांक hw_adc_input_select(काष्ठा hw *hw, क्रमागत ADCSRC type)
अणु
	पूर्णांक state = type == ADC_MICIN;

	चयन (hw->model) अणु
	हाल CTSB055X:
		वापस adc_input_select_SB055x(hw, type, state);
	हाल CTSB073X:
		वापस adc_input_select_hendrix(hw, type, state);
	हाल CTUAA:
		वापस adc_input_select_hendrix(hw, type, state);
	शेष:
		वापस adc_input_select_SBx(hw, type, state);
	पूर्ण
पूर्ण

अटल पूर्णांक adc_init_SB055x(काष्ठा hw *hw, पूर्णांक input, पूर्णांक mic20db)
अणु
	वापस adc_input_select_SB055x(hw, input, mic20db);
पूर्ण

अटल पूर्णांक adc_init_SBx(काष्ठा hw *hw, पूर्णांक input, पूर्णांक mic20db)
अणु
	u16 gpioorg;
	u16 input_source;
	u32 adcdata;
	अचिन्हित पूर्णांक ret;

	input_source = 0x100;  /* शेष to analog */
	चयन (input) अणु
	हाल ADC_MICIN:
		adcdata = 0x1;
		input_source = 0x180;  /* set GPIO7 to select Mic */
		अवरोध;
	हाल ADC_LINEIN:
		adcdata = 0x2;
		अवरोध;
	हाल ADC_VIDEO:
		adcdata = 0x4;
		अवरोध;
	हाल ADC_AUX:
		adcdata = 0x8;
		अवरोध;
	हाल ADC_NONE:
		adcdata = 0x0;
		input_source = 0x0;  /* set to Digital */
		अवरोध;
	शेष:
		adcdata = 0x0;
		अवरोध;
	पूर्ण

	अगर (i2c_unlock(hw))
		वापस -1;

	करो अणु
		ret = hw_पढ़ो_pci(hw, 0xEC);
	पूर्ण जबतक (!(ret & 0x800000)); /* i2c पढ़ोy poll */
	hw_ग_लिखो_pci(hw, 0xEC, 0x05);  /* ग_लिखो to i2c status control */

	i2c_ग_लिखो(hw, 0x001a0080, 0x0e, 0x08);
	i2c_ग_लिखो(hw, 0x001a0080, 0x18, 0x0a);
	i2c_ग_लिखो(hw, 0x001a0080, 0x28, 0x86);
	i2c_ग_लिखो(hw, 0x001a0080, 0x2a, adcdata);

	अगर (mic20db) अणु
		i2c_ग_लिखो(hw, 0x001a0080, 0x1c, 0xf7);
		i2c_ग_लिखो(hw, 0x001a0080, 0x1e, 0xf7);
	पूर्ण अन्यथा अणु
		i2c_ग_लिखो(hw, 0x001a0080, 0x1c, 0xcf);
		i2c_ग_लिखो(hw, 0x001a0080, 0x1e, 0xcf);
	पूर्ण

	अगर (!(hw_पढ़ो_20kx(hw, ID0) & 0x100))
		i2c_ग_लिखो(hw, 0x001a0080, 0x16, 0x26);

	i2c_lock(hw);

	gpioorg = (u16)hw_पढ़ो_20kx(hw,  GPIO);
	gpioorg &= 0xfe7f;
	gpioorg |= input_source;
	hw_ग_लिखो_20kx(hw, GPIO, gpioorg);

	वापस 0;
पूर्ण

अटल पूर्णांक hw_adc_init(काष्ठा hw *hw, स्थिर काष्ठा adc_conf *info)
अणु
	अगर (hw->model == CTSB055X)
		वापस adc_init_SB055x(hw, info->input, info->mic20db);
	अन्यथा
		वापस adc_init_SBx(hw, info->input, info->mic20db);
पूर्ण

अटल काष्ठा capabilities hw_capabilities(काष्ठा hw *hw)
अणु
	काष्ठा capabilities cap;

	/* SB073x and Vista compatible cards have no digit IO चयन */
	cap.digit_io_चयन = !(hw->model == CTSB073X || hw->model == CTUAA);
	cap.dedicated_mic = 0;
	cap.output_चयन = 0;
	cap.mic_source_चयन = 0;

	वापस cap;
पूर्ण

#घोषणा CTLBITS(a, b, c, d)	(((a) << 24) | ((b) << 16) | ((c) << 8) | (d))

#घोषणा UAA_CFG_PWRSTATUS	0x44
#घोषणा UAA_CFG_SPACE_FLAG	0xA0
#घोषणा UAA_CORE_CHANGE		0x3FFC
अटल पूर्णांक uaa_to_xfi(काष्ठा pci_dev *pci)
अणु
	अचिन्हित पूर्णांक bar0, bar1, bar2, bar3, bar4, bar5;
	अचिन्हित पूर्णांक cmd, irq, cl_size, l_समयr, pwr;
	अचिन्हित पूर्णांक is_uaa;
	अचिन्हित पूर्णांक data[4] = अणु0पूर्ण;
	अचिन्हित पूर्णांक io_base;
	व्योम __iomem *mem_base;
	पूर्णांक i;
	स्थिर u32 CTLX = CTLBITS('C', 'T', 'L', 'X');
	स्थिर u32 CTL_ = CTLBITS('C', 'T', 'L', '-');
	स्थिर u32 CTLF = CTLBITS('C', 'T', 'L', 'F');
	स्थिर u32 CTLi = CTLBITS('C', 'T', 'L', 'i');
	स्थिर u32 CTLA = CTLBITS('C', 'T', 'L', 'A');
	स्थिर u32 CTLZ = CTLBITS('C', 'T', 'L', 'Z');
	स्थिर u32 CTLL = CTLBITS('C', 'T', 'L', 'L');

	/* By शेष, Hendrix card UAA Bar0 should be using memory... */
	io_base = pci_resource_start(pci, 0);
	mem_base = ioremap(io_base, pci_resource_len(pci, 0));
	अगर (!mem_base)
		वापस -ENOENT;

	/* Read current mode from Mode Change Register */
	क्रम (i = 0; i < 4; i++)
		data[i] = पढ़ोl(mem_base + UAA_CORE_CHANGE);

	/* Determine current mode... */
	अगर (data[0] == CTLA) अणु
		is_uaa = ((data[1] == CTLZ && data[2] == CTLL
			  && data[3] == CTLA) || (data[1] == CTLA
			  && data[2] == CTLZ && data[3] == CTLL));
	पूर्ण अन्यथा अगर (data[0] == CTLZ) अणु
		is_uaa = (data[1] == CTLL
				&& data[2] == CTLA && data[3] == CTLA);
	पूर्ण अन्यथा अगर (data[0] == CTLL) अणु
		is_uaa = (data[1] == CTLA
				&& data[2] == CTLA && data[3] == CTLZ);
	पूर्ण अन्यथा अणु
		is_uaa = 0;
	पूर्ण

	अगर (!is_uaa) अणु
		/* Not in UAA mode currently. Return directly. */
		iounmap(mem_base);
		वापस 0;
	पूर्ण

	pci_पढ़ो_config_dword(pci, PCI_BASE_ADDRESS_0, &bar0);
	pci_पढ़ो_config_dword(pci, PCI_BASE_ADDRESS_1, &bar1);
	pci_पढ़ो_config_dword(pci, PCI_BASE_ADDRESS_2, &bar2);
	pci_पढ़ो_config_dword(pci, PCI_BASE_ADDRESS_3, &bar3);
	pci_पढ़ो_config_dword(pci, PCI_BASE_ADDRESS_4, &bar4);
	pci_पढ़ो_config_dword(pci, PCI_BASE_ADDRESS_5, &bar5);
	pci_पढ़ो_config_dword(pci, PCI_INTERRUPT_LINE, &irq);
	pci_पढ़ो_config_dword(pci, PCI_CACHE_LINE_SIZE, &cl_size);
	pci_पढ़ो_config_dword(pci, PCI_LATENCY_TIMER, &l_समयr);
	pci_पढ़ो_config_dword(pci, UAA_CFG_PWRSTATUS, &pwr);
	pci_पढ़ो_config_dword(pci, PCI_COMMAND, &cmd);

	/* Set up X-Fi core PCI configuration space. */
	/* Switch to X-Fi config space with BAR0 exposed. */
	pci_ग_लिखो_config_dword(pci, UAA_CFG_SPACE_FLAG, 0x87654321);
	/* Copy UAA's BAR5 पूर्णांकo X-Fi BAR0 */
	pci_ग_लिखो_config_dword(pci, PCI_BASE_ADDRESS_0, bar5);
	/* Switch to X-Fi config space without BAR0 exposed. */
	pci_ग_लिखो_config_dword(pci, UAA_CFG_SPACE_FLAG, 0x12345678);
	pci_ग_लिखो_config_dword(pci, PCI_BASE_ADDRESS_1, bar1);
	pci_ग_लिखो_config_dword(pci, PCI_BASE_ADDRESS_2, bar2);
	pci_ग_लिखो_config_dword(pci, PCI_BASE_ADDRESS_3, bar3);
	pci_ग_लिखो_config_dword(pci, PCI_BASE_ADDRESS_4, bar4);
	pci_ग_लिखो_config_dword(pci, PCI_INTERRUPT_LINE, irq);
	pci_ग_लिखो_config_dword(pci, PCI_CACHE_LINE_SIZE, cl_size);
	pci_ग_लिखो_config_dword(pci, PCI_LATENCY_TIMER, l_समयr);
	pci_ग_लिखो_config_dword(pci, UAA_CFG_PWRSTATUS, pwr);
	pci_ग_लिखो_config_dword(pci, PCI_COMMAND, cmd);

	/* Switch to X-Fi mode */
	ग_लिखोl(CTLX, (mem_base + UAA_CORE_CHANGE));
	ग_लिखोl(CTL_, (mem_base + UAA_CORE_CHANGE));
	ग_लिखोl(CTLF, (mem_base + UAA_CORE_CHANGE));
	ग_लिखोl(CTLi, (mem_base + UAA_CORE_CHANGE));

	iounmap(mem_base);

	वापस 0;
पूर्ण

अटल irqवापस_t ct_20k1_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा hw *hw = dev_id;
	अचिन्हित पूर्णांक status;

	status = hw_पढ़ो_20kx(hw, GIP);
	अगर (!status)
		वापस IRQ_NONE;

	अगर (hw->irq_callback)
		hw->irq_callback(hw->irq_callback_data, status);

	hw_ग_लिखो_20kx(hw, GIP, status);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक hw_card_start(काष्ठा hw *hw)
अणु
	पूर्णांक err;
	काष्ठा pci_dev *pci = hw->pci;
	स्थिर अचिन्हित पूर्णांक dma_bits = BITS_PER_LONG;

	err = pci_enable_device(pci);
	अगर (err < 0)
		वापस err;

	/* Set DMA transfer mask */
	अगर (dma_set_mask_and_coherent(&pci->dev, DMA_BIT_MASK(dma_bits)))
		dma_set_mask_and_coherent(&pci->dev, DMA_BIT_MASK(32));

	अगर (!hw->io_base) अणु
		err = pci_request_regions(pci, "XFi");
		अगर (err < 0)
			जाओ error1;

		अगर (hw->model == CTUAA)
			hw->io_base = pci_resource_start(pci, 5);
		अन्यथा
			hw->io_base = pci_resource_start(pci, 0);

	पूर्ण

	/* Switch to X-Fi mode from UAA mode अगर neeeded */
	अगर (hw->model == CTUAA) अणु
		err = uaa_to_xfi(pci);
		अगर (err)
			जाओ error2;

	पूर्ण

	अगर (hw->irq < 0) अणु
		err = request_irq(pci->irq, ct_20k1_पूर्णांकerrupt, IRQF_SHARED,
				  KBUILD_MODNAME, hw);
		अगर (err < 0) अणु
			dev_err(hw->card->dev,
				"XFi: Cannot get irq %d\n", pci->irq);
			जाओ error2;
		पूर्ण
		hw->irq = pci->irq;
		hw->card->sync_irq = hw->irq;
	पूर्ण

	pci_set_master(pci);

	वापस 0;

error2:
	pci_release_regions(pci);
	hw->io_base = 0;
error1:
	pci_disable_device(pci);
	वापस err;
पूर्ण

अटल पूर्णांक hw_card_stop(काष्ठा hw *hw)
अणु
	अचिन्हित पूर्णांक data;

	/* disable transport bus master and queueing of request */
	hw_ग_लिखो_20kx(hw, TRNCTL, 0x00);

	/* disable pll */
	data = hw_पढ़ो_20kx(hw, PLLCTL);
	hw_ग_लिखो_20kx(hw, PLLCTL, (data & (~(0x0F<<12))));

	वापस 0;
पूर्ण

अटल पूर्णांक hw_card_shutकरोwn(काष्ठा hw *hw)
अणु
	अगर (hw->irq >= 0)
		मुक्त_irq(hw->irq, hw);

	hw->irq	= -1;
	iounmap(hw->mem_base);
	hw->mem_base = शून्य;

	अगर (hw->io_base)
		pci_release_regions(hw->pci);

	hw->io_base = 0;

	pci_disable_device(hw->pci);

	वापस 0;
पूर्ण

अटल पूर्णांक hw_card_init(काष्ठा hw *hw, काष्ठा card_conf *info)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक gctl;
	u32 data;
	काष्ठा dac_conf dac_info = अणु0पूर्ण;
	काष्ठा adc_conf adc_info = अणु0पूर्ण;
	काष्ठा daio_conf daio_info = अणु0पूर्ण;
	काष्ठा trn_conf trn_info = अणु0पूर्ण;

	/* Get PCI io port base address and करो Hendrix चयन अगर needed. */
	err = hw_card_start(hw);
	अगर (err)
		वापस err;

	/* PLL init */
	err = hw_pll_init(hw, info->rsr);
	अगर (err < 0)
		वापस err;

	/* kick off स्वतः-init */
	err = hw_स्वतः_init(hw);
	अगर (err < 0)
		वापस err;

	/* Enable audio ring */
	gctl = hw_पढ़ो_20kx(hw, GCTL);
	set_field(&gctl, GCTL_EAC, 1);
	set_field(&gctl, GCTL_DBP, 1);
	set_field(&gctl, GCTL_TBP, 1);
	set_field(&gctl, GCTL_FBP, 1);
	set_field(&gctl, GCTL_ET, 1);
	hw_ग_लिखो_20kx(hw, GCTL, gctl);
	mdelay(10);

	/* Reset all global pending पूर्णांकerrupts */
	hw_ग_लिखो_20kx(hw, GIE, 0);
	/* Reset all SRC pending पूर्णांकerrupts */
	hw_ग_लिखो_20kx(hw, SRCIP, 0);
	msleep(30);

	/* Detect the card ID and configure GPIO accordingly. */
	चयन (hw->model) अणु
	हाल CTSB055X:
		hw_ग_लिखो_20kx(hw, GPIOCTL, 0x13fe);
		अवरोध;
	हाल CTSB073X:
		hw_ग_लिखो_20kx(hw, GPIOCTL, 0x00e6);
		अवरोध;
	हाल CTUAA:
		hw_ग_लिखो_20kx(hw, GPIOCTL, 0x00c2);
		अवरोध;
	शेष:
		hw_ग_लिखो_20kx(hw, GPIOCTL, 0x01e6);
		अवरोध;
	पूर्ण

	trn_info.vm_pgt_phys = info->vm_pgt_phys;
	err = hw_trn_init(hw, &trn_info);
	अगर (err < 0)
		वापस err;

	daio_info.msr = info->msr;
	err = hw_daio_init(hw, &daio_info);
	अगर (err < 0)
		वापस err;

	dac_info.msr = info->msr;
	err = hw_dac_init(hw, &dac_info);
	अगर (err < 0)
		वापस err;

	adc_info.msr = info->msr;
	adc_info.input = ADC_LINEIN;
	adc_info.mic20db = 0;
	err = hw_adc_init(hw, &adc_info);
	अगर (err < 0)
		वापस err;

	data = hw_पढ़ो_20kx(hw, SRCMCTL);
	data |= 0x1; /* Enables input from the audio ring */
	hw_ग_लिखो_20kx(hw, SRCMCTL, data);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक hw_suspend(काष्ठा hw *hw)
अणु
	काष्ठा pci_dev *pci = hw->pci;

	hw_card_stop(hw);

	अगर (hw->model == CTUAA) अणु
		/* Switch to UAA config space. */
		pci_ग_लिखो_config_dword(pci, UAA_CFG_SPACE_FLAG, 0x0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hw_resume(काष्ठा hw *hw, काष्ठा card_conf *info)
अणु
	/* Re-initialize card hardware. */
	वापस hw_card_init(hw, info);
पूर्ण
#पूर्ण_अगर

अटल u32 hw_पढ़ो_20kx(काष्ठा hw *hw, u32 reg)
अणु
	u32 value;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(
		&container_of(hw, काष्ठा hw20k1, hw)->reg_20k1_lock, flags);
	outl(reg, hw->io_base + 0x0);
	value = inl(hw->io_base + 0x4);
	spin_unlock_irqrestore(
		&container_of(hw, काष्ठा hw20k1, hw)->reg_20k1_lock, flags);

	वापस value;
पूर्ण

अटल व्योम hw_ग_लिखो_20kx(काष्ठा hw *hw, u32 reg, u32 data)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(
		&container_of(hw, काष्ठा hw20k1, hw)->reg_20k1_lock, flags);
	outl(reg, hw->io_base + 0x0);
	outl(data, hw->io_base + 0x4);
	spin_unlock_irqrestore(
		&container_of(hw, काष्ठा hw20k1, hw)->reg_20k1_lock, flags);

पूर्ण

अटल u32 hw_पढ़ो_pci(काष्ठा hw *hw, u32 reg)
अणु
	u32 value;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(
		&container_of(hw, काष्ठा hw20k1, hw)->reg_pci_lock, flags);
	outl(reg, hw->io_base + 0x10);
	value = inl(hw->io_base + 0x14);
	spin_unlock_irqrestore(
		&container_of(hw, काष्ठा hw20k1, hw)->reg_pci_lock, flags);

	वापस value;
पूर्ण

अटल व्योम hw_ग_लिखो_pci(काष्ठा hw *hw, u32 reg, u32 data)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(
		&container_of(hw, काष्ठा hw20k1, hw)->reg_pci_lock, flags);
	outl(reg, hw->io_base + 0x10);
	outl(data, hw->io_base + 0x14);
	spin_unlock_irqrestore(
		&container_of(hw, काष्ठा hw20k1, hw)->reg_pci_lock, flags);
पूर्ण

अटल स्थिर काष्ठा hw ct20k1_preset = अणु
	.irq = -1,

	.card_init = hw_card_init,
	.card_stop = hw_card_stop,
	.pll_init = hw_pll_init,
	.is_adc_source_selected = hw_is_adc_input_selected,
	.select_adc_source = hw_adc_input_select,
	.capabilities = hw_capabilities,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend = hw_suspend,
	.resume = hw_resume,
#पूर्ण_अगर

	.src_rsc_get_ctrl_blk = src_get_rsc_ctrl_blk,
	.src_rsc_put_ctrl_blk = src_put_rsc_ctrl_blk,
	.src_mgr_get_ctrl_blk = src_mgr_get_ctrl_blk,
	.src_mgr_put_ctrl_blk = src_mgr_put_ctrl_blk,
	.src_set_state = src_set_state,
	.src_set_bm = src_set_bm,
	.src_set_rsr = src_set_rsr,
	.src_set_sf = src_set_sf,
	.src_set_wr = src_set_wr,
	.src_set_pm = src_set_pm,
	.src_set_rom = src_set_rom,
	.src_set_vo = src_set_vo,
	.src_set_st = src_set_st,
	.src_set_ie = src_set_ie,
	.src_set_ilsz = src_set_ilsz,
	.src_set_bp = src_set_bp,
	.src_set_cisz = src_set_cisz,
	.src_set_ca = src_set_ca,
	.src_set_sa = src_set_sa,
	.src_set_la = src_set_la,
	.src_set_pitch = src_set_pitch,
	.src_set_dirty = src_set_dirty,
	.src_set_clear_zbufs = src_set_clear_zbufs,
	.src_set_dirty_all = src_set_dirty_all,
	.src_commit_ग_लिखो = src_commit_ग_लिखो,
	.src_get_ca = src_get_ca,
	.src_get_dirty = src_get_dirty,
	.src_dirty_conj_mask = src_dirty_conj_mask,
	.src_mgr_enbs_src = src_mgr_enbs_src,
	.src_mgr_enb_src = src_mgr_enb_src,
	.src_mgr_dsb_src = src_mgr_dsb_src,
	.src_mgr_commit_ग_लिखो = src_mgr_commit_ग_लिखो,

	.srcimp_mgr_get_ctrl_blk = srcimp_mgr_get_ctrl_blk,
	.srcimp_mgr_put_ctrl_blk = srcimp_mgr_put_ctrl_blk,
	.srcimp_mgr_set_imaparc = srcimp_mgr_set_imaparc,
	.srcimp_mgr_set_imapuser = srcimp_mgr_set_imapuser,
	.srcimp_mgr_set_imapnxt = srcimp_mgr_set_imapnxt,
	.srcimp_mgr_set_imapaddr = srcimp_mgr_set_imapaddr,
	.srcimp_mgr_commit_ग_लिखो = srcimp_mgr_commit_ग_लिखो,

	.amixer_rsc_get_ctrl_blk = amixer_rsc_get_ctrl_blk,
	.amixer_rsc_put_ctrl_blk = amixer_rsc_put_ctrl_blk,
	.amixer_mgr_get_ctrl_blk = amixer_mgr_get_ctrl_blk,
	.amixer_mgr_put_ctrl_blk = amixer_mgr_put_ctrl_blk,
	.amixer_set_mode = amixer_set_mode,
	.amixer_set_iv = amixer_set_iv,
	.amixer_set_x = amixer_set_x,
	.amixer_set_y = amixer_set_y,
	.amixer_set_sadr = amixer_set_sadr,
	.amixer_set_se = amixer_set_se,
	.amixer_set_dirty = amixer_set_dirty,
	.amixer_set_dirty_all = amixer_set_dirty_all,
	.amixer_commit_ग_लिखो = amixer_commit_ग_लिखो,
	.amixer_get_y = amixer_get_y,
	.amixer_get_dirty = amixer_get_dirty,

	.dai_get_ctrl_blk = dai_get_ctrl_blk,
	.dai_put_ctrl_blk = dai_put_ctrl_blk,
	.dai_srt_set_srco = dai_srt_set_srcr,
	.dai_srt_set_srcm = dai_srt_set_srcl,
	.dai_srt_set_rsr = dai_srt_set_rsr,
	.dai_srt_set_drat = dai_srt_set_drat,
	.dai_srt_set_ec = dai_srt_set_ec,
	.dai_srt_set_et = dai_srt_set_et,
	.dai_commit_ग_लिखो = dai_commit_ग_लिखो,

	.dao_get_ctrl_blk = dao_get_ctrl_blk,
	.dao_put_ctrl_blk = dao_put_ctrl_blk,
	.dao_set_spos = dao_set_spos,
	.dao_commit_ग_लिखो = dao_commit_ग_लिखो,
	.dao_get_spos = dao_get_spos,

	.daio_mgr_get_ctrl_blk = daio_mgr_get_ctrl_blk,
	.daio_mgr_put_ctrl_blk = daio_mgr_put_ctrl_blk,
	.daio_mgr_enb_dai = daio_mgr_enb_dai,
	.daio_mgr_dsb_dai = daio_mgr_dsb_dai,
	.daio_mgr_enb_dao = daio_mgr_enb_dao,
	.daio_mgr_dsb_dao = daio_mgr_dsb_dao,
	.daio_mgr_dao_init = daio_mgr_dao_init,
	.daio_mgr_set_imaparc = daio_mgr_set_imaparc,
	.daio_mgr_set_imapnxt = daio_mgr_set_imapnxt,
	.daio_mgr_set_imapaddr = daio_mgr_set_imapaddr,
	.daio_mgr_commit_ग_लिखो = daio_mgr_commit_ग_लिखो,

	.set_समयr_irq = set_समयr_irq,
	.set_समयr_tick = set_समयr_tick,
	.get_wc = get_wc,
पूर्ण;

पूर्णांक create_20k1_hw_obj(काष्ठा hw **rhw)
अणु
	काष्ठा hw20k1 *hw20k1;

	*rhw = शून्य;
	hw20k1 = kzalloc(माप(*hw20k1), GFP_KERNEL);
	अगर (!hw20k1)
		वापस -ENOMEM;

	spin_lock_init(&hw20k1->reg_20k1_lock);
	spin_lock_init(&hw20k1->reg_pci_lock);

	hw20k1->hw = ct20k1_preset;

	*rhw = &hw20k1->hw;

	वापस 0;
पूर्ण

पूर्णांक destroy_20k1_hw_obj(काष्ठा hw *hw)
अणु
	अगर (hw->io_base)
		hw_card_shutकरोwn(hw);

	kमुक्त(container_of(hw, काष्ठा hw20k1, hw));
	वापस 0;
पूर्ण
