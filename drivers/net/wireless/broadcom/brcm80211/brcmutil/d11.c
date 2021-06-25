<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2013 Broadcom Corporation
 */
/*********************channel spec common functions*********************/

#समावेश <linux/module.h>

#समावेश <brcmu_utils.h>
#समावेश <brcmu_wअगरi.h>
#समावेश <brcmu_d11.h>

अटल u16 d11n_sb(क्रमागत brcmu_chan_sb sb)
अणु
	चयन (sb) अणु
	हाल BRCMU_CHAN_SB_NONE:
		वापस BRCMU_CHSPEC_D11N_SB_N;
	हाल BRCMU_CHAN_SB_L:
		वापस BRCMU_CHSPEC_D11N_SB_L;
	हाल BRCMU_CHAN_SB_U:
		वापस BRCMU_CHSPEC_D11N_SB_U;
	शेष:
		WARN_ON(1);
	पूर्ण
	वापस 0;
पूर्ण

अटल u16 d11n_bw(क्रमागत brcmu_chan_bw bw)
अणु
	चयन (bw) अणु
	हाल BRCMU_CHAN_BW_20:
		वापस BRCMU_CHSPEC_D11N_BW_20;
	हाल BRCMU_CHAN_BW_40:
		वापस BRCMU_CHSPEC_D11N_BW_40;
	शेष:
		WARN_ON(1);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम brcmu_d11n_encchspec(काष्ठा brcmu_chan *ch)
अणु
	अगर (ch->bw == BRCMU_CHAN_BW_20)
		ch->sb = BRCMU_CHAN_SB_NONE;

	ch->chspec = 0;
	brcmu_maskset16(&ch->chspec, BRCMU_CHSPEC_CH_MASK,
			BRCMU_CHSPEC_CH_SHIFT, ch->chnum);
	brcmu_maskset16(&ch->chspec, BRCMU_CHSPEC_D11N_SB_MASK,
			0, d11n_sb(ch->sb));
	brcmu_maskset16(&ch->chspec, BRCMU_CHSPEC_D11N_BW_MASK,
			0, d11n_bw(ch->bw));

	अगर (ch->chnum <= CH_MAX_2G_CHANNEL)
		ch->chspec |= BRCMU_CHSPEC_D11N_BND_2G;
	अन्यथा
		ch->chspec |= BRCMU_CHSPEC_D11N_BND_5G;
पूर्ण

अटल u16 d11ac_bw(क्रमागत brcmu_chan_bw bw)
अणु
	चयन (bw) अणु
	हाल BRCMU_CHAN_BW_20:
		वापस BRCMU_CHSPEC_D11AC_BW_20;
	हाल BRCMU_CHAN_BW_40:
		वापस BRCMU_CHSPEC_D11AC_BW_40;
	हाल BRCMU_CHAN_BW_80:
		वापस BRCMU_CHSPEC_D11AC_BW_80;
	हाल BRCMU_CHAN_BW_160:
		वापस BRCMU_CHSPEC_D11AC_BW_160;
	शेष:
		WARN_ON(1);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम brcmu_d11ac_encchspec(काष्ठा brcmu_chan *ch)
अणु
	अगर (ch->bw == BRCMU_CHAN_BW_20 || ch->sb == BRCMU_CHAN_SB_NONE)
		ch->sb = BRCMU_CHAN_SB_L;

	brcmu_maskset16(&ch->chspec, BRCMU_CHSPEC_CH_MASK,
			BRCMU_CHSPEC_CH_SHIFT, ch->chnum);
	brcmu_maskset16(&ch->chspec, BRCMU_CHSPEC_D11AC_SB_MASK,
			BRCMU_CHSPEC_D11AC_SB_SHIFT, ch->sb);
	brcmu_maskset16(&ch->chspec, BRCMU_CHSPEC_D11AC_BW_MASK,
			0, d11ac_bw(ch->bw));

	ch->chspec &= ~BRCMU_CHSPEC_D11AC_BND_MASK;
	अगर (ch->chnum <= CH_MAX_2G_CHANNEL)
		ch->chspec |= BRCMU_CHSPEC_D11AC_BND_2G;
	अन्यथा
		ch->chspec |= BRCMU_CHSPEC_D11AC_BND_5G;
पूर्ण

अटल व्योम brcmu_d11n_decchspec(काष्ठा brcmu_chan *ch)
अणु
	u16 val;

	ch->chnum = (u8)(ch->chspec & BRCMU_CHSPEC_CH_MASK);
	ch->control_ch_num = ch->chnum;

	चयन (ch->chspec & BRCMU_CHSPEC_D11N_BW_MASK) अणु
	हाल BRCMU_CHSPEC_D11N_BW_20:
		ch->bw = BRCMU_CHAN_BW_20;
		ch->sb = BRCMU_CHAN_SB_NONE;
		अवरोध;
	हाल BRCMU_CHSPEC_D11N_BW_40:
		ch->bw = BRCMU_CHAN_BW_40;
		val = ch->chspec & BRCMU_CHSPEC_D11N_SB_MASK;
		अगर (val == BRCMU_CHSPEC_D11N_SB_L) अणु
			ch->sb = BRCMU_CHAN_SB_L;
			ch->control_ch_num -= CH_10MHZ_APART;
		पूर्ण अन्यथा अणु
			ch->sb = BRCMU_CHAN_SB_U;
			ch->control_ch_num += CH_10MHZ_APART;
		पूर्ण
		अवरोध;
	शेष:
		WARN_ONCE(1, "Invalid chanspec 0x%04x\n", ch->chspec);
		अवरोध;
	पूर्ण

	चयन (ch->chspec & BRCMU_CHSPEC_D11N_BND_MASK) अणु
	हाल BRCMU_CHSPEC_D11N_BND_5G:
		ch->band = BRCMU_CHAN_BAND_5G;
		अवरोध;
	हाल BRCMU_CHSPEC_D11N_BND_2G:
		ch->band = BRCMU_CHAN_BAND_2G;
		अवरोध;
	शेष:
		WARN_ONCE(1, "Invalid chanspec 0x%04x\n", ch->chspec);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम brcmu_d11ac_decchspec(काष्ठा brcmu_chan *ch)
अणु
	u16 val;

	ch->chnum = (u8)(ch->chspec & BRCMU_CHSPEC_CH_MASK);
	ch->control_ch_num = ch->chnum;

	चयन (ch->chspec & BRCMU_CHSPEC_D11AC_BW_MASK) अणु
	हाल BRCMU_CHSPEC_D11AC_BW_20:
		ch->bw = BRCMU_CHAN_BW_20;
		ch->sb = BRCMU_CHAN_SB_NONE;
		अवरोध;
	हाल BRCMU_CHSPEC_D11AC_BW_40:
		ch->bw = BRCMU_CHAN_BW_40;
		val = ch->chspec & BRCMU_CHSPEC_D11AC_SB_MASK;
		अगर (val == BRCMU_CHSPEC_D11AC_SB_L) अणु
			ch->sb = BRCMU_CHAN_SB_L;
			ch->control_ch_num -= CH_10MHZ_APART;
		पूर्ण अन्यथा अगर (val == BRCMU_CHSPEC_D11AC_SB_U) अणु
			ch->sb = BRCMU_CHAN_SB_U;
			ch->control_ch_num += CH_10MHZ_APART;
		पूर्ण अन्यथा अणु
			WARN_ONCE(1, "Invalid chanspec 0x%04x\n", ch->chspec);
		पूर्ण
		अवरोध;
	हाल BRCMU_CHSPEC_D11AC_BW_80:
		ch->bw = BRCMU_CHAN_BW_80;
		ch->sb = brcmu_maskget16(ch->chspec, BRCMU_CHSPEC_D11AC_SB_MASK,
					 BRCMU_CHSPEC_D11AC_SB_SHIFT);
		चयन (ch->sb) अणु
		हाल BRCMU_CHAN_SB_LL:
			ch->control_ch_num -= CH_30MHZ_APART;
			अवरोध;
		हाल BRCMU_CHAN_SB_LU:
			ch->control_ch_num -= CH_10MHZ_APART;
			अवरोध;
		हाल BRCMU_CHAN_SB_UL:
			ch->control_ch_num += CH_10MHZ_APART;
			अवरोध;
		हाल BRCMU_CHAN_SB_UU:
			ch->control_ch_num += CH_30MHZ_APART;
			अवरोध;
		शेष:
			WARN_ONCE(1, "Invalid chanspec 0x%04x\n", ch->chspec);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल BRCMU_CHSPEC_D11AC_BW_160:
		ch->bw = BRCMU_CHAN_BW_160;
		ch->sb = brcmu_maskget16(ch->chspec, BRCMU_CHSPEC_D11AC_SB_MASK,
					 BRCMU_CHSPEC_D11AC_SB_SHIFT);
		चयन (ch->sb) अणु
		हाल BRCMU_CHAN_SB_LLL:
			ch->control_ch_num -= CH_70MHZ_APART;
			अवरोध;
		हाल BRCMU_CHAN_SB_LLU:
			ch->control_ch_num -= CH_50MHZ_APART;
			अवरोध;
		हाल BRCMU_CHAN_SB_LUL:
			ch->control_ch_num -= CH_30MHZ_APART;
			अवरोध;
		हाल BRCMU_CHAN_SB_LUU:
			ch->control_ch_num -= CH_10MHZ_APART;
			अवरोध;
		हाल BRCMU_CHAN_SB_ULL:
			ch->control_ch_num += CH_10MHZ_APART;
			अवरोध;
		हाल BRCMU_CHAN_SB_ULU:
			ch->control_ch_num += CH_30MHZ_APART;
			अवरोध;
		हाल BRCMU_CHAN_SB_UUL:
			ch->control_ch_num += CH_50MHZ_APART;
			अवरोध;
		हाल BRCMU_CHAN_SB_UUU:
			ch->control_ch_num += CH_70MHZ_APART;
			अवरोध;
		शेष:
			WARN_ONCE(1, "Invalid chanspec 0x%04x\n", ch->chspec);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल BRCMU_CHSPEC_D11AC_BW_8080:
	शेष:
		WARN_ONCE(1, "Invalid chanspec 0x%04x\n", ch->chspec);
		अवरोध;
	पूर्ण

	चयन (ch->chspec & BRCMU_CHSPEC_D11AC_BND_MASK) अणु
	हाल BRCMU_CHSPEC_D11AC_BND_5G:
		ch->band = BRCMU_CHAN_BAND_5G;
		अवरोध;
	हाल BRCMU_CHSPEC_D11AC_BND_2G:
		ch->band = BRCMU_CHAN_BAND_2G;
		अवरोध;
	शेष:
		WARN_ONCE(1, "Invalid chanspec 0x%04x\n", ch->chspec);
		अवरोध;
	पूर्ण
पूर्ण

व्योम brcmu_d11_attach(काष्ठा brcmu_d11inf *d11inf)
अणु
	अगर (d11inf->io_type == BRCMU_D11N_IOTYPE) अणु
		d11inf->encchspec = brcmu_d11n_encchspec;
		d11inf->decchspec = brcmu_d11n_decchspec;
	पूर्ण अन्यथा अणु
		d11inf->encchspec = brcmu_d11ac_encchspec;
		d11inf->decchspec = brcmu_d11ac_decchspec;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(brcmu_d11_attach);
