<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008, Creative Technology Ltd. All Rights Reserved.
 *
 * @File	cthw20k2.c
 *
 * @Brief
 * This file contains the implementation of hardware access method क्रम 20k2.
 *
 * @Author	Liu Chun
 * @Date 	May 14 2008
 */

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश "cthw20k2.h"
#समावेश "ct20k2reg.h"

काष्ठा hw20k2 अणु
	काष्ठा hw hw;
	/* क्रम i2c */
	अचिन्हित अक्षर dev_id;
	अचिन्हित अक्षर addr_size;
	अचिन्हित अक्षर data_size;

	पूर्णांक mic_source;
पूर्ण;

अटल u32 hw_पढ़ो_20kx(काष्ठा hw *hw, u32 reg);
अटल व्योम hw_ग_लिखो_20kx(काष्ठा hw *hw, u32 reg, u32 data);

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

#घोषणा SRCCA_CA	0x0FFFFFFF
#घोषणा SRCCA_RS	0xE0000000

#घोषणा SRCSA_SA	0x0FFFFFFF

#घोषणा SRCLA_LA	0x0FFFFFFF

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
			hw_ग_लिखो_20kx(hw, SRC_UPZ+idx*0x100+i*0x4, 0);

		क्रम (i = 0; i < 4; i++)
			hw_ग_लिखो_20kx(hw, SRC_DN0Z+idx*0x100+i*0x4, 0);

		क्रम (i = 0; i < 8; i++)
			hw_ग_लिखो_20kx(hw, SRC_DN1Z+idx*0x100+i*0x4, 0);

		ctl->dirty.bf.czbfs = 0;
	पूर्ण
	अगर (ctl->dirty.bf.mpr) अणु
		/* Take the parameter mixer resource in the same group as that
		 * the idx src is in क्रम simplicity. Unlike src, all conjugate
		 * parameter mixer resources must be programmed क्रम
		 * corresponding conjugate src resources. */
		अचिन्हित पूर्णांक pm_idx = src_param_pitch_mixer(idx);
		hw_ग_लिखो_20kx(hw, MIXER_PRING_LO_HI+4*pm_idx, ctl->mpr);
		hw_ग_लिखो_20kx(hw, MIXER_PMOPLO+8*pm_idx, 0x3);
		hw_ग_लिखो_20kx(hw, MIXER_PMOPHI+8*pm_idx, 0x0);
		ctl->dirty.bf.mpr = 0;
	पूर्ण
	अगर (ctl->dirty.bf.sa) अणु
		hw_ग_लिखो_20kx(hw, SRC_SA+idx*0x100, ctl->sa);
		ctl->dirty.bf.sa = 0;
	पूर्ण
	अगर (ctl->dirty.bf.la) अणु
		hw_ग_लिखो_20kx(hw, SRC_LA+idx*0x100, ctl->la);
		ctl->dirty.bf.la = 0;
	पूर्ण
	अगर (ctl->dirty.bf.ca) अणु
		hw_ग_लिखो_20kx(hw, SRC_CA+idx*0x100, ctl->ca);
		ctl->dirty.bf.ca = 0;
	पूर्ण

	/* Write srccf रेजिस्टर */
	hw_ग_लिखो_20kx(hw, SRC_CF+idx*0x100, 0x0);

	अगर (ctl->dirty.bf.ccr) अणु
		hw_ग_लिखो_20kx(hw, SRC_CCR+idx*0x100, ctl->ccr);
		ctl->dirty.bf.ccr = 0;
	पूर्ण
	अगर (ctl->dirty.bf.ctl) अणु
		hw_ग_लिखो_20kx(hw, SRC_CTL+idx*0x100, ctl->ctl);
		ctl->dirty.bf.ctl = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक src_get_ca(काष्ठा hw *hw, अचिन्हित पूर्णांक idx, व्योम *blk)
अणु
	काष्ठा src_rsc_ctrl_blk *ctl = blk;

	ctl->ca = hw_पढ़ो_20kx(hw, SRC_CA+idx*0x100);
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
	((काष्ठा src_mgr_ctrl_blk *)blk)->enbsa |= (0x1 << ((idx%128)/4));
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
			ret = hw_पढ़ो_20kx(hw, SRC_ENBSTAT);
		पूर्ण जबतक (ret & 0x1);
		hw_ग_लिखो_20kx(hw, SRC_ENBSA, ctl->enbsa);
		ctl->dirty.bf.enbsa = 0;
	पूर्ण
	क्रम (i = 0; i < 8; i++) अणु
		अगर ((ctl->dirty.data & (0x1 << i))) अणु
			hw_ग_लिखो_20kx(hw, SRC_ENB+(i*0x100), ctl->enb[i]);
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
	((काष्ठा srcimp_mgr_ctrl_blk *)blk)->srcimap.idx = addr;
	((काष्ठा srcimp_mgr_ctrl_blk *)blk)->dirty.bf.srcimap = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक srcimp_mgr_commit_ग_लिखो(काष्ठा hw *hw, व्योम *blk)
अणु
	काष्ठा srcimp_mgr_ctrl_blk *ctl = blk;

	अगर (ctl->dirty.bf.srcimap) अणु
		hw_ग_लिखो_20kx(hw, SRC_IMAP+ctl->srcimap.idx*0x100,
						ctl->srcimap.srcaim);
		ctl->dirty.bf.srcimap = 0;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * AMIXER control block definitions.
 */

#घोषणा AMOPLO_M	0x00000003
#घोषणा AMOPLO_IV	0x00000004
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
	काष्ठा amixer_rsc_ctrl_blk *ctl = blk;

	set_field(&ctl->amoplo, AMOPLO_IV, iv);
	ctl->dirty.bf.amoplo = 1;
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
		hw_ग_लिखो_20kx(hw, MIXER_AMOPLO+idx*8, ctl->amoplo);
		ctl->dirty.bf.amoplo = 0;
		hw_ग_लिखो_20kx(hw, MIXER_AMOPHI+idx*8, ctl->amophi);
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
	*rblk = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक amixer_mgr_put_ctrl_blk(व्योम *blk)
अणु
	वापस 0;
पूर्ण

/*
 * DAIO control block definitions.
 */

/* Receiver Sample Rate Tracker Control रेजिस्टर */
#घोषणा SRTCTL_SRCO	0x000000FF
#घोषणा SRTCTL_SRCM	0x0000FF00
#घोषणा SRTCTL_RSR	0x00030000
#घोषणा SRTCTL_DRAT	0x00300000
#घोषणा SRTCTL_EC	0x01000000
#घोषणा SRTCTL_ET	0x10000000

/* DAIO Receiver रेजिस्टर dirty flags */
जोड़ dai_dirty अणु
	काष्ठा अणु
		u16 srt:1;
		u16 rsv:15;
	पूर्ण bf;
	u16 data;
पूर्ण;

/* DAIO Receiver control block */
काष्ठा dai_ctrl_blk अणु
	अचिन्हित पूर्णांक	srt;
	जोड़ dai_dirty	dirty;
पूर्ण;

/* Audio Input Mapper RAM */
#घोषणा AIM_ARC		0x00000FFF
#घोषणा AIM_NXT		0x007F0000

काष्ठा daoimap अणु
	अचिन्हित पूर्णांक aim;
	अचिन्हित पूर्णांक idx;
पूर्ण;

/* Audio Transmitter Control and Status रेजिस्टर */
#घोषणा ATXCTL_EN	0x00000001
#घोषणा ATXCTL_MODE	0x00000010
#घोषणा ATXCTL_CD	0x00000020
#घोषणा ATXCTL_RAW	0x00000100
#घोषणा ATXCTL_MT	0x00000200
#घोषणा ATXCTL_NUC	0x00003000
#घोषणा ATXCTL_BEN	0x00010000
#घोषणा ATXCTL_BMUX	0x00700000
#घोषणा ATXCTL_B24	0x01000000
#घोषणा ATXCTL_CPF	0x02000000
#घोषणा ATXCTL_RIV	0x10000000
#घोषणा ATXCTL_LIV	0x20000000
#घोषणा ATXCTL_RSAT	0x40000000
#घोषणा ATXCTL_LSAT	0x80000000

/* XDIF Transmitter रेजिस्टर dirty flags */
जोड़ dao_dirty अणु
	काष्ठा अणु
		u16 atxcsl:1;
		u16 rsv:15;
	पूर्ण bf;
	u16 data;
पूर्ण;

/* XDIF Transmitter control block */
काष्ठा dao_ctrl_blk अणु
	/* XDIF Transmitter Channel Status Low Register */
	अचिन्हित पूर्णांक	atxcsl;
	जोड़ dao_dirty	dirty;
पूर्ण;

/* Audio Receiver Control रेजिस्टर */
#घोषणा ARXCTL_EN	0x00000001

/* DAIO manager रेजिस्टर dirty flags */
जोड़ daio_mgr_dirty अणु
	काष्ठा अणु
		u32 atxctl:8;
		u32 arxctl:8;
		u32 daoimap:1;
		u32 rsv:15;
	पूर्ण bf;
	u32 data;
पूर्ण;

/* DAIO manager control block */
काष्ठा daio_mgr_ctrl_blk अणु
	काष्ठा daoimap		daoimap;
	अचिन्हित पूर्णांक		txctl[8];
	अचिन्हित पूर्णांक		rxctl[8];
	जोड़ daio_mgr_dirty	dirty;
पूर्ण;

अटल पूर्णांक dai_srt_set_srco(व्योम *blk, अचिन्हित पूर्णांक src)
अणु
	काष्ठा dai_ctrl_blk *ctl = blk;

	set_field(&ctl->srt, SRTCTL_SRCO, src);
	ctl->dirty.bf.srt = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक dai_srt_set_srcm(व्योम *blk, अचिन्हित पूर्णांक src)
अणु
	काष्ठा dai_ctrl_blk *ctl = blk;

	set_field(&ctl->srt, SRTCTL_SRCM, src);
	ctl->dirty.bf.srt = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक dai_srt_set_rsr(व्योम *blk, अचिन्हित पूर्णांक rsr)
अणु
	काष्ठा dai_ctrl_blk *ctl = blk;

	set_field(&ctl->srt, SRTCTL_RSR, rsr);
	ctl->dirty.bf.srt = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक dai_srt_set_drat(व्योम *blk, अचिन्हित पूर्णांक drat)
अणु
	काष्ठा dai_ctrl_blk *ctl = blk;

	set_field(&ctl->srt, SRTCTL_DRAT, drat);
	ctl->dirty.bf.srt = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक dai_srt_set_ec(व्योम *blk, अचिन्हित पूर्णांक ec)
अणु
	काष्ठा dai_ctrl_blk *ctl = blk;

	set_field(&ctl->srt, SRTCTL_EC, ec ? 1 : 0);
	ctl->dirty.bf.srt = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक dai_srt_set_et(व्योम *blk, अचिन्हित पूर्णांक et)
अणु
	काष्ठा dai_ctrl_blk *ctl = blk;

	set_field(&ctl->srt, SRTCTL_ET, et ? 1 : 0);
	ctl->dirty.bf.srt = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक dai_commit_ग_लिखो(काष्ठा hw *hw, अचिन्हित पूर्णांक idx, व्योम *blk)
अणु
	काष्ठा dai_ctrl_blk *ctl = blk;

	अगर (ctl->dirty.bf.srt) अणु
		hw_ग_लिखो_20kx(hw, AUDIO_IO_RX_SRT_CTL+0x40*idx, ctl->srt);
		ctl->dirty.bf.srt = 0;
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
	((काष्ठा dao_ctrl_blk *)blk)->atxcsl = spos;
	((काष्ठा dao_ctrl_blk *)blk)->dirty.bf.atxcsl = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक dao_commit_ग_लिखो(काष्ठा hw *hw, अचिन्हित पूर्णांक idx, व्योम *blk)
अणु
	काष्ठा dao_ctrl_blk *ctl = blk;

	अगर (ctl->dirty.bf.atxcsl) अणु
		अगर (idx < 4) अणु
			/* S/PDIF SPOSx */
			hw_ग_लिखो_20kx(hw, AUDIO_IO_TX_CSTAT_L+0x40*idx,
							ctl->atxcsl);
		पूर्ण
		ctl->dirty.bf.atxcsl = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dao_get_spos(व्योम *blk, अचिन्हित पूर्णांक *spos)
अणु
	*spos = ((काष्ठा dao_ctrl_blk *)blk)->atxcsl;
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

	set_field(&ctl->rxctl[idx], ARXCTL_EN, 1);
	ctl->dirty.bf.arxctl |= (0x1 << idx);
	वापस 0;
पूर्ण

अटल पूर्णांक daio_mgr_dsb_dai(व्योम *blk, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा daio_mgr_ctrl_blk *ctl = blk;

	set_field(&ctl->rxctl[idx], ARXCTL_EN, 0);

	ctl->dirty.bf.arxctl |= (0x1 << idx);
	वापस 0;
पूर्ण

अटल पूर्णांक daio_mgr_enb_dao(व्योम *blk, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा daio_mgr_ctrl_blk *ctl = blk;

	set_field(&ctl->txctl[idx], ATXCTL_EN, 1);
	ctl->dirty.bf.atxctl |= (0x1 << idx);
	वापस 0;
पूर्ण

अटल पूर्णांक daio_mgr_dsb_dao(व्योम *blk, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा daio_mgr_ctrl_blk *ctl = blk;

	set_field(&ctl->txctl[idx], ATXCTL_EN, 0);
	ctl->dirty.bf.atxctl |= (0x1 << idx);
	वापस 0;
पूर्ण

अटल पूर्णांक daio_mgr_dao_init(व्योम *blk, अचिन्हित पूर्णांक idx, अचिन्हित पूर्णांक conf)
अणु
	काष्ठा daio_mgr_ctrl_blk *ctl = blk;

	अगर (idx < 4) अणु
		/* S/PDIF output */
		चयन ((conf & 0xf)) अणु
		हाल 1:
			set_field(&ctl->txctl[idx], ATXCTL_NUC, 0);
			अवरोध;
		हाल 2:
			set_field(&ctl->txctl[idx], ATXCTL_NUC, 1);
			अवरोध;
		हाल 4:
			set_field(&ctl->txctl[idx], ATXCTL_NUC, 2);
			अवरोध;
		हाल 8:
			set_field(&ctl->txctl[idx], ATXCTL_NUC, 3);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		/* CDIF */
		set_field(&ctl->txctl[idx], ATXCTL_CD, (!(conf & 0x7)));
		/* Non-audio */
		set_field(&ctl->txctl[idx], ATXCTL_LIV, (conf >> 4) & 0x1);
		/* Non-audio */
		set_field(&ctl->txctl[idx], ATXCTL_RIV, (conf >> 4) & 0x1);
		set_field(&ctl->txctl[idx], ATXCTL_RAW,
			  ((conf >> 3) & 0x1) ? 0 : 0);
		ctl->dirty.bf.atxctl |= (0x1 << idx);
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
	((काष्ठा daio_mgr_ctrl_blk *)blk)->daoimap.idx = addr;
	((काष्ठा daio_mgr_ctrl_blk *)blk)->dirty.bf.daoimap = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक daio_mgr_commit_ग_लिखो(काष्ठा hw *hw, व्योम *blk)
अणु
	काष्ठा daio_mgr_ctrl_blk *ctl = blk;
	अचिन्हित पूर्णांक data;
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		अगर ((ctl->dirty.bf.atxctl & (0x1 << i))) अणु
			data = ctl->txctl[i];
			hw_ग_लिखो_20kx(hw, (AUDIO_IO_TX_CTL+(0x40*i)), data);
			ctl->dirty.bf.atxctl &= ~(0x1 << i);
			mdelay(1);
		पूर्ण
		अगर ((ctl->dirty.bf.arxctl & (0x1 << i))) अणु
			data = ctl->rxctl[i];
			hw_ग_लिखो_20kx(hw, (AUDIO_IO_RX_CTL+(0x40*i)), data);
			ctl->dirty.bf.arxctl &= ~(0x1 << i);
			mdelay(1);
		पूर्ण
	पूर्ण
	अगर (ctl->dirty.bf.daoimap) अणु
		hw_ग_लिखो_20kx(hw, AUDIO_IO_AIM+ctl->daoimap.idx*4,
						ctl->daoimap.aim);
		ctl->dirty.bf.daoimap = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक daio_mgr_get_ctrl_blk(काष्ठा hw *hw, व्योम **rblk)
अणु
	काष्ठा daio_mgr_ctrl_blk *blk;
	पूर्णांक i;

	*rblk = शून्य;
	blk = kzalloc(माप(*blk), GFP_KERNEL);
	अगर (!blk)
		वापस -ENOMEM;

	क्रम (i = 0; i < 8; i++) अणु
		blk->txctl[i] = hw_पढ़ो_20kx(hw, AUDIO_IO_TX_CTL+(0x40*i));
		blk->rxctl[i] = hw_पढ़ो_20kx(hw, AUDIO_IO_RX_CTL+(0x40*i));
	पूर्ण

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
	u32 data;
	पूर्णांक i;

	/* Program I2S with proper sample rate and enable the correct I2S
	 * channel. ED(0/8/16/24): Enable all I2S/I2X master घड़ी output */
	अगर (1 == info->msr) अणु
		hw_ग_लिखो_20kx(hw, AUDIO_IO_MCLK, 0x01010101);
		hw_ग_लिखो_20kx(hw, AUDIO_IO_TX_BLRCLK, 0x01010101);
		hw_ग_लिखो_20kx(hw, AUDIO_IO_RX_BLRCLK, 0);
	पूर्ण अन्यथा अगर (2 == info->msr) अणु
		अगर (hw->model != CTSB1270) अणु
			hw_ग_लिखो_20kx(hw, AUDIO_IO_MCLK, 0x11111111);
		पूर्ण अन्यथा अणु
			/* PCM4220 on Titanium HD is dअगरferent. */
			hw_ग_लिखो_20kx(hw, AUDIO_IO_MCLK, 0x11011111);
		पूर्ण
		/* Specअगरy all playing 96khz
		 * EA [0]	- Enabled
		 * RTA [4:5]	- 96kHz
		 * EB [8]	- Enabled
		 * RTB [12:13]	- 96kHz
		 * EC [16]	- Enabled
		 * RTC [20:21]	- 96kHz
		 * ED [24]	- Enabled
		 * RTD [28:29]	- 96kHz */
		hw_ग_लिखो_20kx(hw, AUDIO_IO_TX_BLRCLK, 0x11111111);
		hw_ग_लिखो_20kx(hw, AUDIO_IO_RX_BLRCLK, 0);
	पूर्ण अन्यथा अगर ((4 == info->msr) && (hw->model == CTSB1270)) अणु
		hw_ग_लिखो_20kx(hw, AUDIO_IO_MCLK, 0x21011111);
		hw_ग_लिखो_20kx(hw, AUDIO_IO_TX_BLRCLK, 0x21212121);
		hw_ग_लिखो_20kx(hw, AUDIO_IO_RX_BLRCLK, 0);
	पूर्ण अन्यथा अणु
		dev_alert(hw->card->dev,
			  "ERROR!!! Invalid sampling rate!!!\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		अगर (i <= 3) अणु
			/* This comment looks wrong since loop is over 4  */
			/* channels and emu20k2 supports 4 spdअगर IOs.     */
			/* 1st 3 channels are SPDIFs (SB0960) */
			अगर (i == 3)
				data = 0x1001001;
			अन्यथा
				data = 0x1000001;

			hw_ग_लिखो_20kx(hw, (AUDIO_IO_TX_CTL+(0x40*i)), data);
			hw_ग_लिखो_20kx(hw, (AUDIO_IO_RX_CTL+(0x40*i)), data);

			/* Initialize the SPDIF Out Channel status रेजिस्टरs.
			 * The value specअगरied here is based on the typical
			 * values provided in the specअगरication, namely: Clock
			 * Accuracy of 1000ppm, Sample Rate of 48KHz,
			 * unspecअगरied source number, Generation status = 1,
			 * Category code = 0x12 (Digital Signal Mixer),
			 * Mode = 0, Emph = 0, Copy Permitted, AN = 0
			 * (indicating that we're transmitting digital audio,
			 * and the Professional Use bit is 0. */

			hw_ग_लिखो_20kx(hw, AUDIO_IO_TX_CSTAT_L+(0x40*i),
					0x02109204); /* Default to 48kHz */

			hw_ग_लिखो_20kx(hw, AUDIO_IO_TX_CSTAT_H+(0x40*i), 0x0B);
		पूर्ण अन्यथा अणु
			/* Again, loop is over 4 channels not 5. */
			/* Next 5 channels are I2S (SB0960) */
			data = 0x11;
			hw_ग_लिखो_20kx(hw, AUDIO_IO_RX_CTL+(0x40*i), data);
			अगर (2 == info->msr) अणु
				/* Four channels per sample period */
				data |= 0x1000;
			पूर्ण अन्यथा अगर (4 == info->msr) अणु
				/* FIXME: check this against the chip spec */
				data |= 0x2000;
			पूर्ण
			hw_ग_लिखो_20kx(hw, AUDIO_IO_TX_CTL+(0x40*i), data);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* TRANSPORT operations */
अटल पूर्णांक hw_trn_init(काष्ठा hw *hw, स्थिर काष्ठा trn_conf *info)
अणु
	u32 vmctl, data;
	u32 ptp_phys_low, ptp_phys_high;
	पूर्णांक i;

	/* Set up device page table */
	अगर ((~0UL) == info->vm_pgt_phys) अणु
		dev_alert(hw->card->dev,
			  "Wrong device page table page address!!!\n");
		वापस -1;
	पूर्ण

	vmctl = 0x80000C0F;  /* 32-bit, 4k-size page */
	ptp_phys_low = (u32)info->vm_pgt_phys;
	ptp_phys_high = upper_32_bits(info->vm_pgt_phys);
	अगर (माप(व्योम *) == 8) /* 64bit address */
		vmctl |= (3 << 8);
	/* Write page table physical address to all PTPAL रेजिस्टरs */
	क्रम (i = 0; i < 64; i++) अणु
		hw_ग_लिखो_20kx(hw, VMEM_PTPAL+(16*i), ptp_phys_low);
		hw_ग_लिखो_20kx(hw, VMEM_PTPAH+(16*i), ptp_phys_high);
	पूर्ण
	/* Enable भव memory transfer */
	hw_ग_लिखो_20kx(hw, VMEM_CTL, vmctl);
	/* Enable transport bus master and queueing of request */
	hw_ग_लिखो_20kx(hw, TRANSPORT_CTL, 0x03);
	hw_ग_लिखो_20kx(hw, TRANSPORT_INT, 0x200c01);
	/* Enable transport ring */
	data = hw_पढ़ो_20kx(hw, TRANSPORT_ENB);
	hw_ग_लिखो_20kx(hw, TRANSPORT_ENB, (data | 0x03));

	वापस 0;
पूर्ण

/* Card initialization */
#घोषणा GCTL_AIE	0x00000001
#घोषणा GCTL_UAA	0x00000002
#घोषणा GCTL_DPC	0x00000004
#घोषणा GCTL_DBP	0x00000008
#घोषणा GCTL_ABP	0x00000010
#घोषणा GCTL_TBP	0x00000020
#घोषणा GCTL_SBP	0x00000040
#घोषणा GCTL_FBP	0x00000080
#घोषणा GCTL_ME		0x00000100
#घोषणा GCTL_AID	0x00001000

#घोषणा PLLCTL_SRC	0x00000007
#घोषणा PLLCTL_SPE	0x00000008
#घोषणा PLLCTL_RD	0x000000F0
#घोषणा PLLCTL_FD	0x0001FF00
#घोषणा PLLCTL_OD	0x00060000
#घोषणा PLLCTL_B	0x00080000
#घोषणा PLLCTL_AS	0x00100000
#घोषणा PLLCTL_LF	0x03E00000
#घोषणा PLLCTL_SPS	0x1C000000
#घोषणा PLLCTL_AD	0x60000000

#घोषणा PLLSTAT_CCS	0x00000007
#घोषणा PLLSTAT_SPL	0x00000008
#घोषणा PLLSTAT_CRD	0x000000F0
#घोषणा PLLSTAT_CFD	0x0001FF00
#घोषणा PLLSTAT_SL	0x00020000
#घोषणा PLLSTAT_FAS	0x00040000
#घोषणा PLLSTAT_B	0x00080000
#घोषणा PLLSTAT_PD	0x00100000
#घोषणा PLLSTAT_OCA	0x00200000
#घोषणा PLLSTAT_NCA	0x00400000

अटल पूर्णांक hw_pll_init(काष्ठा hw *hw, अचिन्हित पूर्णांक rsr)
अणु
	अचिन्हित पूर्णांक pllenb;
	अचिन्हित पूर्णांक pllctl;
	अचिन्हित पूर्णांक pllstat;
	पूर्णांक i;

	pllenb = 0xB;
	hw_ग_लिखो_20kx(hw, PLL_ENB, pllenb);
	pllctl = 0x20C00000;
	set_field(&pllctl, PLLCTL_B, 0);
	set_field(&pllctl, PLLCTL_FD, 48000 == rsr ? 16 - 4 : 147 - 4);
	set_field(&pllctl, PLLCTL_RD, 48000 == rsr ? 1 - 1 : 10 - 1);
	hw_ग_लिखो_20kx(hw, PLL_CTL, pllctl);
	msleep(40);

	pllctl = hw_पढ़ो_20kx(hw, PLL_CTL);
	set_field(&pllctl, PLLCTL_FD, 48000 == rsr ? 16 - 2 : 147 - 2);
	hw_ग_लिखो_20kx(hw, PLL_CTL, pllctl);
	msleep(40);

	क्रम (i = 0; i < 1000; i++) अणु
		pllstat = hw_पढ़ो_20kx(hw, PLL_STAT);
		अगर (get_field(pllstat, PLLSTAT_PD))
			जारी;

		अगर (get_field(pllstat, PLLSTAT_B) !=
					get_field(pllctl, PLLCTL_B))
			जारी;

		अगर (get_field(pllstat, PLLSTAT_CCS) !=
					get_field(pllctl, PLLCTL_SRC))
			जारी;

		अगर (get_field(pllstat, PLLSTAT_CRD) !=
					get_field(pllctl, PLLCTL_RD))
			जारी;

		अगर (get_field(pllstat, PLLSTAT_CFD) !=
					get_field(pllctl, PLLCTL_FD))
			जारी;

		अवरोध;
	पूर्ण
	अगर (i >= 1000) अणु
		dev_alert(hw->card->dev,
			  "PLL initialization failed!!!\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hw_स्वतः_init(काष्ठा hw *hw)
अणु
	अचिन्हित पूर्णांक gctl;
	पूर्णांक i;

	gctl = hw_पढ़ो_20kx(hw, GLOBAL_CNTL_GCTL);
	set_field(&gctl, GCTL_AIE, 0);
	hw_ग_लिखो_20kx(hw, GLOBAL_CNTL_GCTL, gctl);
	set_field(&gctl, GCTL_AIE, 1);
	hw_ग_लिखो_20kx(hw, GLOBAL_CNTL_GCTL, gctl);
	mdelay(10);
	क्रम (i = 0; i < 400000; i++) अणु
		gctl = hw_पढ़ो_20kx(hw, GLOBAL_CNTL_GCTL);
		अगर (get_field(gctl, GCTL_AID))
			अवरोध;
	पूर्ण
	अगर (!get_field(gctl, GCTL_AID)) अणु
		dev_alert(hw->card->dev, "Card Auto-init failed!!!\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

/* DAC operations */

#घोषणा CS4382_MC1 		0x1
#घोषणा CS4382_MC2 		0x2
#घोषणा CS4382_MC3		0x3
#घोषणा CS4382_FC		0x4
#घोषणा CS4382_IC		0x5
#घोषणा CS4382_XC1		0x6
#घोषणा CS4382_VCA1 		0x7
#घोषणा CS4382_VCB1 		0x8
#घोषणा CS4382_XC2		0x9
#घोषणा CS4382_VCA2 		0xA
#घोषणा CS4382_VCB2 		0xB
#घोषणा CS4382_XC3		0xC
#घोषणा CS4382_VCA3		0xD
#घोषणा CS4382_VCB3		0xE
#घोषणा CS4382_XC4 		0xF
#घोषणा CS4382_VCA4 		0x10
#घोषणा CS4382_VCB4 		0x11
#घोषणा CS4382_CREV 		0x12

/* I2C status */
#घोषणा STATE_LOCKED		0x00
#घोषणा STATE_UNLOCKED		0xAA
#घोषणा DATA_READY		0x800000    /* Used with I2C_IF_STATUS */
#घोषणा DATA_ABORT		0x10000     /* Used with I2C_IF_STATUS */

#घोषणा I2C_STATUS_DCM	0x00000001
#घोषणा I2C_STATUS_BC	0x00000006
#घोषणा I2C_STATUS_APD	0x00000008
#घोषणा I2C_STATUS_AB	0x00010000
#घोषणा I2C_STATUS_DR	0x00800000

#घोषणा I2C_ADDRESS_PTAD	0x0000FFFF
#घोषणा I2C_ADDRESS_SLAD	0x007F0000

काष्ठा regs_cs4382 अणु
	u32 mode_control_1;
	u32 mode_control_2;
	u32 mode_control_3;

	u32 filter_control;
	u32 invert_control;

	u32 mix_control_P1;
	u32 vol_control_A1;
	u32 vol_control_B1;

	u32 mix_control_P2;
	u32 vol_control_A2;
	u32 vol_control_B2;

	u32 mix_control_P3;
	u32 vol_control_A3;
	u32 vol_control_B3;

	u32 mix_control_P4;
	u32 vol_control_A4;
	u32 vol_control_B4;
पूर्ण;

अटल पूर्णांक hw20k2_i2c_unlock_full_access(काष्ठा hw *hw)
अणु
	u8 UnlockKeySequence_FLASH_FULLACCESS_MODE[2] =  अणु0xB3, 0xD4पूर्ण;

	/* Send keys क्रम क्रमced BIOS mode */
	hw_ग_लिखो_20kx(hw, I2C_IF_WLOCK,
			UnlockKeySequence_FLASH_FULLACCESS_MODE[0]);
	hw_ग_लिखो_20kx(hw, I2C_IF_WLOCK,
			UnlockKeySequence_FLASH_FULLACCESS_MODE[1]);
	/* Check whether the chip is unlocked */
	अगर (hw_पढ़ो_20kx(hw, I2C_IF_WLOCK) == STATE_UNLOCKED)
		वापस 0;

	वापस -1;
पूर्ण

अटल पूर्णांक hw20k2_i2c_lock_chip(काष्ठा hw *hw)
अणु
	/* Write twice */
	hw_ग_लिखो_20kx(hw, I2C_IF_WLOCK, STATE_LOCKED);
	hw_ग_लिखो_20kx(hw, I2C_IF_WLOCK, STATE_LOCKED);
	अगर (hw_पढ़ो_20kx(hw, I2C_IF_WLOCK) == STATE_LOCKED)
		वापस 0;

	वापस -1;
पूर्ण

अटल पूर्णांक hw20k2_i2c_init(काष्ठा hw *hw, u8 dev_id, u8 addr_size, u8 data_size)
अणु
	काष्ठा hw20k2 *hw20k2 = (काष्ठा hw20k2 *)hw;
	पूर्णांक err;
	अचिन्हित पूर्णांक i2c_status;
	अचिन्हित पूर्णांक i2c_addr;

	err = hw20k2_i2c_unlock_full_access(hw);
	अगर (err < 0)
		वापस err;

	hw20k2->addr_size = addr_size;
	hw20k2->data_size = data_size;
	hw20k2->dev_id = dev_id;

	i2c_addr = 0;
	set_field(&i2c_addr, I2C_ADDRESS_SLAD, dev_id);

	hw_ग_लिखो_20kx(hw, I2C_IF_ADDRESS, i2c_addr);

	i2c_status = hw_पढ़ो_20kx(hw, I2C_IF_STATUS);

	set_field(&i2c_status, I2C_STATUS_DCM, 1); /* Direct control mode */

	hw_ग_लिखो_20kx(hw, I2C_IF_STATUS, i2c_status);

	वापस 0;
पूर्ण

अटल पूर्णांक hw20k2_i2c_uninit(काष्ठा hw *hw)
अणु
	अचिन्हित पूर्णांक i2c_status;
	अचिन्हित पूर्णांक i2c_addr;

	i2c_addr = 0;
	set_field(&i2c_addr, I2C_ADDRESS_SLAD, 0x57); /* I2C id */

	hw_ग_लिखो_20kx(hw, I2C_IF_ADDRESS, i2c_addr);

	i2c_status = hw_पढ़ो_20kx(hw, I2C_IF_STATUS);

	set_field(&i2c_status, I2C_STATUS_DCM, 0); /* I2C mode */

	hw_ग_लिखो_20kx(hw, I2C_IF_STATUS, i2c_status);

	वापस hw20k2_i2c_lock_chip(hw);
पूर्ण

अटल पूर्णांक hw20k2_i2c_रुको_data_पढ़ोy(काष्ठा hw *hw)
अणु
	पूर्णांक i = 0x400000;
	अचिन्हित पूर्णांक ret;

	करो अणु
		ret = hw_पढ़ो_20kx(hw, I2C_IF_STATUS);
	पूर्ण जबतक ((!(ret & DATA_READY)) && --i);

	वापस i;
पूर्ण

अटल पूर्णांक hw20k2_i2c_पढ़ो(काष्ठा hw *hw, u16 addr, u32 *datap)
अणु
	काष्ठा hw20k2 *hw20k2 = (काष्ठा hw20k2 *)hw;
	अचिन्हित पूर्णांक i2c_status;

	i2c_status = hw_पढ़ो_20kx(hw, I2C_IF_STATUS);
	set_field(&i2c_status, I2C_STATUS_BC,
		  (4 == hw20k2->addr_size) ? 0 : hw20k2->addr_size);
	hw_ग_लिखो_20kx(hw, I2C_IF_STATUS, i2c_status);
	अगर (!hw20k2_i2c_रुको_data_पढ़ोy(hw))
		वापस -1;

	hw_ग_लिखो_20kx(hw, I2C_IF_WDATA, addr);
	अगर (!hw20k2_i2c_रुको_data_पढ़ोy(hw))
		वापस -1;

	/* Force a पढ़ो operation */
	hw_ग_लिखो_20kx(hw, I2C_IF_RDATA, 0);
	अगर (!hw20k2_i2c_रुको_data_पढ़ोy(hw))
		वापस -1;

	*datap = hw_पढ़ो_20kx(hw, I2C_IF_RDATA);

	वापस 0;
पूर्ण

अटल पूर्णांक hw20k2_i2c_ग_लिखो(काष्ठा hw *hw, u16 addr, u32 data)
अणु
	काष्ठा hw20k2 *hw20k2 = (काष्ठा hw20k2 *)hw;
	अचिन्हित पूर्णांक i2c_data = (data << (hw20k2->addr_size * 8)) | addr;
	अचिन्हित पूर्णांक i2c_status;

	i2c_status = hw_पढ़ो_20kx(hw, I2C_IF_STATUS);

	set_field(&i2c_status, I2C_STATUS_BC,
		  (4 == (hw20k2->addr_size + hw20k2->data_size)) ?
		  0 : (hw20k2->addr_size + hw20k2->data_size));

	hw_ग_लिखो_20kx(hw, I2C_IF_STATUS, i2c_status);
	hw20k2_i2c_रुको_data_पढ़ोy(hw);
	/* Dummy ग_लिखो to trigger the ग_लिखो operation */
	hw_ग_लिखो_20kx(hw, I2C_IF_WDATA, 0);
	hw20k2_i2c_रुको_data_पढ़ोy(hw);

	/* This is the real data */
	hw_ग_लिखो_20kx(hw, I2C_IF_WDATA, i2c_data);
	hw20k2_i2c_रुको_data_पढ़ोy(hw);

	वापस 0;
पूर्ण

अटल व्योम hw_dac_stop(काष्ठा hw *hw)
अणु
	u32 data;
	data = hw_पढ़ो_20kx(hw, GPIO_DATA);
	data &= 0xFFFFFFFD;
	hw_ग_लिखो_20kx(hw, GPIO_DATA, data);
	usleep_range(10000, 11000);
पूर्ण

अटल व्योम hw_dac_start(काष्ठा hw *hw)
अणु
	u32 data;
	data = hw_पढ़ो_20kx(hw, GPIO_DATA);
	data |= 0x2;
	hw_ग_लिखो_20kx(hw, GPIO_DATA, data);
	msleep(50);
पूर्ण

अटल व्योम hw_dac_reset(काष्ठा hw *hw)
अणु
	hw_dac_stop(hw);
	hw_dac_start(hw);
पूर्ण

अटल पूर्णांक hw_dac_init(काष्ठा hw *hw, स्थिर काष्ठा dac_conf *info)
अणु
	पूर्णांक err;
	u32 data;
	पूर्णांक i;
	काष्ठा regs_cs4382 cs_पढ़ो = अणु0पूर्ण;
	काष्ठा regs_cs4382 cs_def = अणु
		.mode_control_1 = 0x00000001, /* Mode Control 1 */
		.mode_control_2 = 0x00000000, /* Mode Control 2 */
		.mode_control_3 = 0x00000084, /* Mode Control 3 */
		.filter_control = 0x00000000, /* Filter Control */
		.invert_control = 0x00000000, /* Invert Control */
		.mix_control_P1 = 0x00000024, /* Mixing Control Pair 1 */
		.vol_control_A1 = 0x00000000, /* Vol Control A1 */
		.vol_control_B1 = 0x00000000, /* Vol Control B1 */
		.mix_control_P2 = 0x00000024, /* Mixing Control Pair 2 */
		.vol_control_A2 = 0x00000000, /* Vol Control A2 */
		.vol_control_B2 = 0x00000000, /* Vol Control B2 */
		.mix_control_P3 = 0x00000024, /* Mixing Control Pair 3 */
		.vol_control_A3 = 0x00000000, /* Vol Control A3 */
		.vol_control_B3 = 0x00000000, /* Vol Control B3 */
		.mix_control_P4 = 0x00000024, /* Mixing Control Pair 4 */
		.vol_control_A4 = 0x00000000, /* Vol Control A4 */
		.vol_control_B4 = 0x00000000  /* Vol Control B4 */
				 पूर्ण;

	अगर (hw->model == CTSB1270) अणु
		hw_dac_stop(hw);
		data = hw_पढ़ो_20kx(hw, GPIO_DATA);
		data &= ~0x0600;
		अगर (1 == info->msr)
			data |= 0x0000; /* Single Speed Mode 0-50kHz */
		अन्यथा अगर (2 == info->msr)
			data |= 0x0200; /* Double Speed Mode 50-100kHz */
		अन्यथा
			data |= 0x0600; /* Quad Speed Mode 100-200kHz */
		hw_ग_लिखो_20kx(hw, GPIO_DATA, data);
		hw_dac_start(hw);
		वापस 0;
	पूर्ण

	/* Set DAC reset bit as output */
	data = hw_पढ़ो_20kx(hw, GPIO_CTRL);
	data |= 0x02;
	hw_ग_लिखो_20kx(hw, GPIO_CTRL, data);

	err = hw20k2_i2c_init(hw, 0x18, 1, 1);
	अगर (err < 0)
		जाओ End;

	क्रम (i = 0; i < 2; i++) अणु
		/* Reset DAC twice just in-हाल the chip
		 * didn't initialized properly */
		hw_dac_reset(hw);
		hw_dac_reset(hw);

		अगर (hw20k2_i2c_पढ़ो(hw, CS4382_MC1,  &cs_पढ़ो.mode_control_1))
			जारी;

		अगर (hw20k2_i2c_पढ़ो(hw, CS4382_MC2,  &cs_पढ़ो.mode_control_2))
			जारी;

		अगर (hw20k2_i2c_पढ़ो(hw, CS4382_MC3,  &cs_पढ़ो.mode_control_3))
			जारी;

		अगर (hw20k2_i2c_पढ़ो(hw, CS4382_FC,   &cs_पढ़ो.filter_control))
			जारी;

		अगर (hw20k2_i2c_पढ़ो(hw, CS4382_IC,   &cs_पढ़ो.invert_control))
			जारी;

		अगर (hw20k2_i2c_पढ़ो(hw, CS4382_XC1,  &cs_पढ़ो.mix_control_P1))
			जारी;

		अगर (hw20k2_i2c_पढ़ो(hw, CS4382_VCA1, &cs_पढ़ो.vol_control_A1))
			जारी;

		अगर (hw20k2_i2c_पढ़ो(hw, CS4382_VCB1, &cs_पढ़ो.vol_control_B1))
			जारी;

		अगर (hw20k2_i2c_पढ़ो(hw, CS4382_XC2,  &cs_पढ़ो.mix_control_P2))
			जारी;

		अगर (hw20k2_i2c_पढ़ो(hw, CS4382_VCA2, &cs_पढ़ो.vol_control_A2))
			जारी;

		अगर (hw20k2_i2c_पढ़ो(hw, CS4382_VCB2, &cs_पढ़ो.vol_control_B2))
			जारी;

		अगर (hw20k2_i2c_पढ़ो(hw, CS4382_XC3,  &cs_पढ़ो.mix_control_P3))
			जारी;

		अगर (hw20k2_i2c_पढ़ो(hw, CS4382_VCA3, &cs_पढ़ो.vol_control_A3))
			जारी;

		अगर (hw20k2_i2c_पढ़ो(hw, CS4382_VCB3, &cs_पढ़ो.vol_control_B3))
			जारी;

		अगर (hw20k2_i2c_पढ़ो(hw, CS4382_XC4,  &cs_पढ़ो.mix_control_P4))
			जारी;

		अगर (hw20k2_i2c_पढ़ो(hw, CS4382_VCA4, &cs_पढ़ो.vol_control_A4))
			जारी;

		अगर (hw20k2_i2c_पढ़ो(hw, CS4382_VCB4, &cs_पढ़ो.vol_control_B4))
			जारी;

		अगर (स_भेद(&cs_पढ़ो, &cs_def, माप(cs_पढ़ो)))
			जारी;
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (i >= 2)
		जाओ End;

	/* Note: Every I2C ग_लिखो must have some delay.
	 * This is not a requirement but the delay works here... */
	hw20k2_i2c_ग_लिखो(hw, CS4382_MC1, 0x80);
	hw20k2_i2c_ग_लिखो(hw, CS4382_MC2, 0x10);
	अगर (1 == info->msr) अणु
		hw20k2_i2c_ग_लिखो(hw, CS4382_XC1, 0x24);
		hw20k2_i2c_ग_लिखो(hw, CS4382_XC2, 0x24);
		hw20k2_i2c_ग_लिखो(hw, CS4382_XC3, 0x24);
		hw20k2_i2c_ग_लिखो(hw, CS4382_XC4, 0x24);
	पूर्ण अन्यथा अगर (2 == info->msr) अणु
		hw20k2_i2c_ग_लिखो(hw, CS4382_XC1, 0x25);
		hw20k2_i2c_ग_लिखो(hw, CS4382_XC2, 0x25);
		hw20k2_i2c_ग_लिखो(hw, CS4382_XC3, 0x25);
		hw20k2_i2c_ग_लिखो(hw, CS4382_XC4, 0x25);
	पूर्ण अन्यथा अणु
		hw20k2_i2c_ग_लिखो(hw, CS4382_XC1, 0x26);
		hw20k2_i2c_ग_लिखो(hw, CS4382_XC2, 0x26);
		hw20k2_i2c_ग_लिखो(hw, CS4382_XC3, 0x26);
		hw20k2_i2c_ग_लिखो(hw, CS4382_XC4, 0x26);
	पूर्ण

	वापस 0;
End:

	hw20k2_i2c_uninit(hw);
	वापस -1;
पूर्ण

/* ADC operations */
#घोषणा MAKE_WM8775_ADDR(addr, data)	(u32)(((addr<<1)&0xFE)|((data>>8)&0x1))
#घोषणा MAKE_WM8775_DATA(data)	(u32)(data&0xFF)

#घोषणा WM8775_IC       0x0B
#घोषणा WM8775_MMC      0x0C
#घोषणा WM8775_AADCL    0x0E
#घोषणा WM8775_AADCR    0x0F
#घोषणा WM8775_ADCMC    0x15
#घोषणा WM8775_RESET    0x17

अटल पूर्णांक hw_is_adc_input_selected(काष्ठा hw *hw, क्रमागत ADCSRC type)
अणु
	u32 data;
	अगर (hw->model == CTSB1270) अणु
		/* Titanium HD has two ADC chips, one क्रम line in and one */
		/* क्रम MIC. We करोn't need to चयन the ADC input. */
		वापस 1;
	पूर्ण
	data = hw_पढ़ो_20kx(hw, GPIO_DATA);
	चयन (type) अणु
	हाल ADC_MICIN:
		data = (data & (0x1 << 14)) ? 1 : 0;
		अवरोध;
	हाल ADC_LINEIN:
		data = (data & (0x1 << 14)) ? 0 : 1;
		अवरोध;
	शेष:
		data = 0;
	पूर्ण
	वापस data;
पूर्ण

#घोषणा MIC_BOOST_0DB 0xCF
#घोषणा MIC_BOOST_STEPS_PER_DB 2

अटल व्योम hw_wm8775_input_select(काष्ठा hw *hw, u8 input, s8 gain_in_db)
अणु
	u32 adcmc, gain;

	अगर (input > 3)
		input = 3;

	adcmc = ((u32)1 << input) | 0x100; /* Link L+R gain... */

	hw20k2_i2c_ग_लिखो(hw, MAKE_WM8775_ADDR(WM8775_ADCMC, adcmc),
				MAKE_WM8775_DATA(adcmc));

	अगर (gain_in_db < -103)
		gain_in_db = -103;
	अगर (gain_in_db > 24)
		gain_in_db = 24;

	gain = gain_in_db * MIC_BOOST_STEPS_PER_DB + MIC_BOOST_0DB;

	hw20k2_i2c_ग_लिखो(hw, MAKE_WM8775_ADDR(WM8775_AADCL, gain),
				MAKE_WM8775_DATA(gain));
	/* ...so there should be no need क्रम the following. */
	hw20k2_i2c_ग_लिखो(hw, MAKE_WM8775_ADDR(WM8775_AADCR, gain),
				MAKE_WM8775_DATA(gain));
पूर्ण

अटल पूर्णांक hw_adc_input_select(काष्ठा hw *hw, क्रमागत ADCSRC type)
अणु
	u32 data;
	data = hw_पढ़ो_20kx(hw, GPIO_DATA);
	चयन (type) अणु
	हाल ADC_MICIN:
		data |= (0x1 << 14);
		hw_ग_लिखो_20kx(hw, GPIO_DATA, data);
		hw_wm8775_input_select(hw, 0, 20); /* Mic, 20dB */
		अवरोध;
	हाल ADC_LINEIN:
		data &= ~(0x1 << 14);
		hw_ग_लिखो_20kx(hw, GPIO_DATA, data);
		hw_wm8775_input_select(hw, 1, 0); /* Line-in, 0dB */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hw_adc_init(काष्ठा hw *hw, स्थिर काष्ठा adc_conf *info)
अणु
	पूर्णांक err;
	u32 data, ctl;

	/*  Set ADC reset bit as output */
	data = hw_पढ़ो_20kx(hw, GPIO_CTRL);
	data |= (0x1 << 15);
	hw_ग_लिखो_20kx(hw, GPIO_CTRL, data);

	/* Initialize I2C */
	err = hw20k2_i2c_init(hw, 0x1A, 1, 1);
	अगर (err < 0) अणु
		dev_alert(hw->card->dev, "Failure to acquire I2C!!!\n");
		जाओ error;
	पूर्ण

	/* Reset the ADC (reset is active low). */
	data = hw_पढ़ो_20kx(hw, GPIO_DATA);
	data &= ~(0x1 << 15);
	hw_ग_लिखो_20kx(hw, GPIO_DATA, data);

	अगर (hw->model == CTSB1270) अणु
		/* Set up the PCM4220 ADC on Titanium HD */
		data &= ~0x0C;
		अगर (1 == info->msr)
			data |= 0x00; /* Single Speed Mode 32-50kHz */
		अन्यथा अगर (2 == info->msr)
			data |= 0x08; /* Double Speed Mode 50-108kHz */
		अन्यथा
			data |= 0x04; /* Quad Speed Mode 108kHz-216kHz */
		hw_ग_लिखो_20kx(hw, GPIO_DATA, data);
	पूर्ण

	usleep_range(10000, 11000);
	/* Return the ADC to normal operation. */
	data |= (0x1 << 15);
	hw_ग_लिखो_20kx(hw, GPIO_DATA, data);
	msleep(50);

	/* I2C ग_लिखो to रेजिस्टर offset 0x0B to set ADC LRCLK polarity */
	/* invert bit, पूर्णांकerface क्रमmat to I2S, word length to 24-bit, */
	/* enable ADC high pass filter. Fixes bug 5323?		*/
	hw20k2_i2c_ग_लिखो(hw, MAKE_WM8775_ADDR(WM8775_IC, 0x26),
			 MAKE_WM8775_DATA(0x26));

	/* Set the master mode (256fs) */
	अगर (1 == info->msr) अणु
		/* slave mode, 128x oversampling 256fs */
		hw20k2_i2c_ग_लिखो(hw, MAKE_WM8775_ADDR(WM8775_MMC, 0x02),
						MAKE_WM8775_DATA(0x02));
	पूर्ण अन्यथा अगर ((2 == info->msr) || (4 == info->msr)) अणु
		/* slave mode, 64x oversampling, 256fs */
		hw20k2_i2c_ग_लिखो(hw, MAKE_WM8775_ADDR(WM8775_MMC, 0x0A),
						MAKE_WM8775_DATA(0x0A));
	पूर्ण अन्यथा अणु
		dev_alert(hw->card->dev,
			  "Invalid master sampling rate (msr %d)!!!\n",
			  info->msr);
		err = -EINVAL;
		जाओ error;
	पूर्ण

	अगर (hw->model != CTSB1270) अणु
		/* Configure GPIO bit 14 change to line-in/mic-in */
		ctl = hw_पढ़ो_20kx(hw, GPIO_CTRL);
		ctl |= 0x1 << 14;
		hw_ग_लिखो_20kx(hw, GPIO_CTRL, ctl);
		hw_adc_input_select(hw, ADC_LINEIN);
	पूर्ण अन्यथा अणु
		hw_wm8775_input_select(hw, 0, 0);
	पूर्ण

	वापस 0;
error:
	hw20k2_i2c_uninit(hw);
	वापस err;
पूर्ण

अटल काष्ठा capabilities hw_capabilities(काष्ठा hw *hw)
अणु
	काष्ठा capabilities cap;

	cap.digit_io_चयन = 0;
	cap.dedicated_mic = hw->model == CTSB1270;
	cap.output_चयन = hw->model == CTSB1270;
	cap.mic_source_चयन = hw->model == CTSB1270;

	वापस cap;
पूर्ण

अटल पूर्णांक hw_output_चयन_get(काष्ठा hw *hw)
अणु
	u32 data = hw_पढ़ो_20kx(hw, GPIO_EXT_DATA);

	चयन (data & 0x30) अणु
	हाल 0x00:
	     वापस 0;
	हाल 0x10:
	     वापस 1;
	हाल 0x20:
	     वापस 2;
	शेष:
	     वापस 3;
	पूर्ण
पूर्ण

अटल पूर्णांक hw_output_चयन_put(काष्ठा hw *hw, पूर्णांक position)
अणु
	u32 data;

	अगर (position == hw_output_चयन_get(hw))
		वापस 0;

	/* Mute line and headphones (पूर्णांकended क्रम anti-pop). */
	data = hw_पढ़ो_20kx(hw, GPIO_DATA);
	data |= (0x03 << 11);
	hw_ग_लिखो_20kx(hw, GPIO_DATA, data);

	data = hw_पढ़ो_20kx(hw, GPIO_EXT_DATA) & ~0x30;
	चयन (position) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		data |= 0x10;
		अवरोध;
	शेष:
		data |= 0x20;
	पूर्ण
	hw_ग_लिखो_20kx(hw, GPIO_EXT_DATA, data);

	/* Unmute line and headphones. */
	data = hw_पढ़ो_20kx(hw, GPIO_DATA);
	data &= ~(0x03 << 11);
	hw_ग_लिखो_20kx(hw, GPIO_DATA, data);

	वापस 1;
पूर्ण

अटल पूर्णांक hw_mic_source_चयन_get(काष्ठा hw *hw)
अणु
	काष्ठा hw20k2 *hw20k2 = (काष्ठा hw20k2 *)hw;

	वापस hw20k2->mic_source;
पूर्ण

अटल पूर्णांक hw_mic_source_चयन_put(काष्ठा hw *hw, पूर्णांक position)
अणु
	काष्ठा hw20k2 *hw20k2 = (काष्ठा hw20k2 *)hw;

	अगर (position == hw20k2->mic_source)
		वापस 0;

	चयन (position) अणु
	हाल 0:
		hw_wm8775_input_select(hw, 0, 0); /* Mic, 0dB */
		अवरोध;
	हाल 1:
		hw_wm8775_input_select(hw, 1, 0); /* FP Mic, 0dB */
		अवरोध;
	हाल 2:
		hw_wm8775_input_select(hw, 3, 0); /* Aux Ext, 0dB */
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	hw20k2->mic_source = position;

	वापस 1;
पूर्ण

अटल irqवापस_t ct_20k2_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
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
	पूर्णांक err = 0;
	काष्ठा pci_dev *pci = hw->pci;
	अचिन्हित पूर्णांक gctl;
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

		hw->io_base = pci_resource_start(hw->pci, 2);
		hw->mem_base = ioremap(hw->io_base,
				       pci_resource_len(hw->pci, 2));
		अगर (!hw->mem_base) अणु
			err = -ENOENT;
			जाओ error2;
		पूर्ण
	पूर्ण

	/* Switch to 20k2 mode from UAA mode. */
	gctl = hw_पढ़ो_20kx(hw, GLOBAL_CNTL_GCTL);
	set_field(&gctl, GCTL_UAA, 0);
	hw_ग_लिखो_20kx(hw, GLOBAL_CNTL_GCTL, gctl);

	अगर (hw->irq < 0) अणु
		err = request_irq(pci->irq, ct_20k2_पूर्णांकerrupt, IRQF_SHARED,
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

/*error3:
	iounmap((व्योम *)hw->mem_base);
	hw->mem_base = (अचिन्हित दीर्घ)शून्य;*/
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
	hw_ग_लिखो_20kx(hw, TRANSPORT_CTL, 0x00);

	/* disable pll */
	data = hw_पढ़ो_20kx(hw, PLL_ENB);
	hw_ग_लिखो_20kx(hw, PLL_ENB, (data & (~0x07)));

	/* TODO: Disable पूर्णांकerrupt and so on... */
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
	u32 data = 0;
	काष्ठा dac_conf dac_info = अणु0पूर्ण;
	काष्ठा adc_conf adc_info = अणु0पूर्ण;
	काष्ठा daio_conf daio_info = अणु0पूर्ण;
	काष्ठा trn_conf trn_info = अणु0पूर्ण;

	/* Get PCI io port/memory base address and
	 * करो 20kx core चयन अगर needed. */
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

	gctl = hw_पढ़ो_20kx(hw, GLOBAL_CNTL_GCTL);
	set_field(&gctl, GCTL_DBP, 1);
	set_field(&gctl, GCTL_TBP, 1);
	set_field(&gctl, GCTL_FBP, 1);
	set_field(&gctl, GCTL_DPC, 0);
	hw_ग_लिखो_20kx(hw, GLOBAL_CNTL_GCTL, gctl);

	/* Reset all global pending पूर्णांकerrupts */
	hw_ग_लिखो_20kx(hw, GIE, 0);
	/* Reset all SRC pending पूर्णांकerrupts */
	hw_ग_लिखो_20kx(hw, SRC_IP, 0);

	अगर (hw->model != CTSB1270) अणु
		/* TODO: detect the card ID and configure GPIO accordingly. */
		/* Configures GPIO (0xD802 0x98028) */
		/*hw_ग_लिखो_20kx(hw, GPIO_CTRL, 0x7F07);*/
		/* Configures GPIO (SB0880) */
		/*hw_ग_लिखो_20kx(hw, GPIO_CTRL, 0xFF07);*/
		hw_ग_लिखो_20kx(hw, GPIO_CTRL, 0xD802);
	पूर्ण अन्यथा अणु
		hw_ग_लिखो_20kx(hw, GPIO_CTRL, 0x9E5F);
	पूर्ण
	/* Enable audio ring */
	hw_ग_लिखो_20kx(hw, MIXER_AR_ENABLE, 0x01);

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

	data = hw_पढ़ो_20kx(hw, SRC_MCTL);
	data |= 0x1; /* Enables input from the audio ring */
	hw_ग_लिखो_20kx(hw, SRC_MCTL, data);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक hw_suspend(काष्ठा hw *hw)
अणु
	hw_card_stop(hw);
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
	वापस पढ़ोl(hw->mem_base + reg);
पूर्ण

अटल व्योम hw_ग_लिखो_20kx(काष्ठा hw *hw, u32 reg, u32 data)
अणु
	ग_लिखोl(data, hw->mem_base + reg);
पूर्ण

अटल स्थिर काष्ठा hw ct20k2_preset = अणु
	.irq = -1,

	.card_init = hw_card_init,
	.card_stop = hw_card_stop,
	.pll_init = hw_pll_init,
	.is_adc_source_selected = hw_is_adc_input_selected,
	.select_adc_source = hw_adc_input_select,
	.capabilities = hw_capabilities,
	.output_चयन_get = hw_output_चयन_get,
	.output_चयन_put = hw_output_चयन_put,
	.mic_source_चयन_get = hw_mic_source_चयन_get,
	.mic_source_चयन_put = hw_mic_source_चयन_put,
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
	.dai_srt_set_srco = dai_srt_set_srco,
	.dai_srt_set_srcm = dai_srt_set_srcm,
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

पूर्णांक create_20k2_hw_obj(काष्ठा hw **rhw)
अणु
	काष्ठा hw20k2 *hw20k2;

	*rhw = शून्य;
	hw20k2 = kzalloc(माप(*hw20k2), GFP_KERNEL);
	अगर (!hw20k2)
		वापस -ENOMEM;

	hw20k2->hw = ct20k2_preset;
	*rhw = &hw20k2->hw;

	वापस 0;
पूर्ण

पूर्णांक destroy_20k2_hw_obj(काष्ठा hw *hw)
अणु
	अगर (hw->io_base)
		hw_card_shutकरोwn(hw);

	kमुक्त(hw);
	वापस 0;
पूर्ण
