<शैली गुरु>
/*
 * Copyright (c) 2010 Broadcom Corporation
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <linux/slab.h>
#समावेश <net/mac80211.h>

#समावेश "types.h"
#समावेश "main.h"
#समावेश "phy_shim.h"
#समावेश "antsel.h"
#समावेश "debug.h"

#घोषणा ANT_SELCFG_AUTO		0x80	/* bit indicates antenna sel AUTO */
#घोषणा ANT_SELCFG_MASK		0x33	/* antenna configuration mask */
#घोषणा ANT_SELCFG_TX_UNICAST	0	/* unicast tx antenna configuration */
#घोषणा ANT_SELCFG_RX_UNICAST	1	/* unicast rx antenna configuration */
#घोषणा ANT_SELCFG_TX_DEF	2	/* शेष tx antenna configuration */
#घोषणा ANT_SELCFG_RX_DEF	3	/* शेष rx antenna configuration */

/* useful macros */
#घोषणा BRCMS_ANTSEL_11N_0(ant)	((((ant) & ANT_SELCFG_MASK) >> 4) & 0xf)
#घोषणा BRCMS_ANTSEL_11N_1(ant)	(((ant) & ANT_SELCFG_MASK) & 0xf)
#घोषणा BRCMS_ANTIDX_11N(ant)	(((BRCMS_ANTSEL_11N_0(ant)) << 2) +\
				(BRCMS_ANTSEL_11N_1(ant)))
#घोषणा BRCMS_ANT_ISAUTO_11N(ant) (((ant) & ANT_SELCFG_AUTO) == ANT_SELCFG_AUTO)
#घोषणा BRCMS_ANTSEL_11N(ant)	((ant) & ANT_SELCFG_MASK)

/* antenna चयन */
/* defines क्रम no boardlevel antenna भागersity */
#घोषणा ANT_SELCFG_DEF_2x2	0x01	/* शेष antenna configuration */

/* 2x3 antभाग defines and tables क्रम GPIO communication */
#घोषणा ANT_SELCFG_NUM_2x3	3
#घोषणा ANT_SELCFG_DEF_2x3	0x01	/* शेष antenna configuration */

/* 2x4 antभाग rev4 defines and tables क्रम GPIO communication */
#घोषणा ANT_SELCFG_NUM_2x4	4
#घोषणा ANT_SELCFG_DEF_2x4	0x02	/* शेष antenna configuration */

अटल स्थिर u16 mimo_2x4_भाग_antselpat_tbl[] = अणु
	0, 0, 0x9, 0xa,		/* ant0: 0 ant1: 2,3 */
	0, 0, 0x5, 0x6,		/* ant0: 1 ant1: 2,3 */
	0, 0, 0, 0,		/* n.a.              */
	0, 0, 0, 0		/* n.a.              */
पूर्ण;

अटल स्थिर u8 mimo_2x4_भाग_antselid_tbl[16] = अणु
	0, 0, 0, 0, 0, 2, 3, 0,
	0, 0, 1, 0, 0, 0, 0, 0	/* pat to antselid */
पूर्ण;

अटल स्थिर u16 mimo_2x3_भाग_antselpat_tbl[] = अणु
	16, 0, 1, 16,		/* ant0: 0 ant1: 1,2 */
	16, 16, 16, 16,		/* n.a.              */
	16, 2, 16, 16,		/* ant0: 2 ant1: 1   */
	16, 16, 16, 16		/* n.a.              */
पूर्ण;

अटल स्थिर u8 mimo_2x3_भाग_antselid_tbl[16] = अणु
	0, 1, 2, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0	/* pat to antselid */
पूर्ण;

/* boardlevel antenna selection: init antenna selection काष्ठाure */
अटल व्योम
brcms_c_antsel_init_cfg(काष्ठा antsel_info *asi, काष्ठा brcms_antselcfg *antsel,
		    bool स्वतः_sel)
अणु
	अगर (asi->antsel_type == ANTSEL_2x3) अणु
		u8 antcfg_def = ANT_SELCFG_DEF_2x3 |
		    ((asi->antsel_avail && स्वतः_sel) ? ANT_SELCFG_AUTO : 0);
		antsel->ant_config[ANT_SELCFG_TX_DEF] = antcfg_def;
		antsel->ant_config[ANT_SELCFG_TX_UNICAST] = antcfg_def;
		antsel->ant_config[ANT_SELCFG_RX_DEF] = antcfg_def;
		antsel->ant_config[ANT_SELCFG_RX_UNICAST] = antcfg_def;
		antsel->num_antcfg = ANT_SELCFG_NUM_2x3;

	पूर्ण अन्यथा अगर (asi->antsel_type == ANTSEL_2x4) अणु

		antsel->ant_config[ANT_SELCFG_TX_DEF] = ANT_SELCFG_DEF_2x4;
		antsel->ant_config[ANT_SELCFG_TX_UNICAST] = ANT_SELCFG_DEF_2x4;
		antsel->ant_config[ANT_SELCFG_RX_DEF] = ANT_SELCFG_DEF_2x4;
		antsel->ant_config[ANT_SELCFG_RX_UNICAST] = ANT_SELCFG_DEF_2x4;
		antsel->num_antcfg = ANT_SELCFG_NUM_2x4;

	पूर्ण अन्यथा अणु		/* no antenna selection available */

		antsel->ant_config[ANT_SELCFG_TX_DEF] = ANT_SELCFG_DEF_2x2;
		antsel->ant_config[ANT_SELCFG_TX_UNICAST] = ANT_SELCFG_DEF_2x2;
		antsel->ant_config[ANT_SELCFG_RX_DEF] = ANT_SELCFG_DEF_2x2;
		antsel->ant_config[ANT_SELCFG_RX_UNICAST] = ANT_SELCFG_DEF_2x2;
		antsel->num_antcfg = 0;
	पूर्ण
पूर्ण

काष्ठा antsel_info *brcms_c_antsel_attach(काष्ठा brcms_c_info *wlc)
अणु
	काष्ठा antsel_info *asi;
	काष्ठा ssb_sprom *sprom = &wlc->hw->d11core->bus->sprom;

	asi = kzalloc(माप(काष्ठा antsel_info), GFP_ATOMIC);
	अगर (!asi)
		वापस शून्य;

	asi->wlc = wlc;
	asi->pub = wlc->pub;
	asi->antsel_type = ANTSEL_NA;
	asi->antsel_avail = false;
	asi->antsel_antचयन = sprom->antचयन;

	अगर ((asi->pub->sromrev >= 4) && (asi->antsel_antचयन != 0)) अणु
		चयन (asi->antsel_antचयन) अणु
		हाल ANTSWITCH_TYPE_1:
		हाल ANTSWITCH_TYPE_2:
		हाल ANTSWITCH_TYPE_3:
			/* 4321/2 board with 2x3 चयन logic */
			asi->antsel_type = ANTSEL_2x3;
			/* Antenna selection availability */
			अगर ((sprom->ant_available_bg == 7) ||
			    (sprom->ant_available_a == 7)) अणु
				asi->antsel_avail = true;
			पूर्ण अन्यथा अगर (
				sprom->ant_available_bg == 3 ||
				sprom->ant_available_a == 3) अणु
				asi->antsel_avail = false;
			पूर्ण अन्यथा अणु
				asi->antsel_avail = false;
				brcms_err(wlc->hw->d11core,
					  "antsel_attach: 2o3 "
					  "board cfg invalid\n");
			पूर्ण

			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर ((asi->pub->sromrev == 4) &&
		   (sprom->ant_available_bg == 7) &&
		   (sprom->ant_available_a == 0)) अणु
		/* hack to match old 4321CB2 cards with 2of3 antenna चयन */
		asi->antsel_type = ANTSEL_2x3;
		asi->antsel_avail = true;
	पूर्ण अन्यथा अगर (asi->pub->boardflags2 & BFL2_2X4_DIV) अणु
		asi->antsel_type = ANTSEL_2x4;
		asi->antsel_avail = true;
	पूर्ण

	/* Set the antenna selection type क्रम the low driver */
	brcms_b_antsel_type_set(wlc->hw, asi->antsel_type);

	/* Init (स्वतः/manual) antenna selection */
	brcms_c_antsel_init_cfg(asi, &asi->antcfg_11n, true);
	brcms_c_antsel_init_cfg(asi, &asi->antcfg_cur, true);

	वापस asi;
पूर्ण

व्योम brcms_c_antsel_detach(काष्ठा antsel_info *asi)
अणु
	kमुक्त(asi);
पूर्ण

/*
 * boardlevel antenna selection:
 *   convert ant_cfg to mimo_antsel (ucode पूर्णांकerface)
 */
अटल u16 brcms_c_antsel_antcfg2antsel(काष्ठा antsel_info *asi, u8 ant_cfg)
अणु
	u8 idx = BRCMS_ANTIDX_11N(BRCMS_ANTSEL_11N(ant_cfg));
	u16 mimo_antsel = 0;

	अगर (asi->antsel_type == ANTSEL_2x4) अणु
		/* 2x4 antenna भागersity board, 4 cfgs: 0-2 0-3 1-2 1-3 */
		mimo_antsel = (mimo_2x4_भाग_antselpat_tbl[idx] & 0xf);
		वापस mimo_antsel;

	पूर्ण अन्यथा अगर (asi->antsel_type == ANTSEL_2x3) अणु
		/* 2x3 antenna selection, 3 cfgs: 0-1 0-2 2-1 */
		mimo_antsel = (mimo_2x3_भाग_antselpat_tbl[idx] & 0xf);
		वापस mimo_antsel;
	पूर्ण

	वापस mimo_antsel;
पूर्ण

/* boardlevel antenna selection: ucode पूर्णांकerface control */
अटल पूर्णांक brcms_c_antsel_cfgupd(काष्ठा antsel_info *asi,
				 काष्ठा brcms_antselcfg *antsel)
अणु
	काष्ठा brcms_c_info *wlc = asi->wlc;
	u8 ant_cfg;
	u16 mimo_antsel;

	/* 1) Update TX antconfig क्रम all frames that are not unicast data
	 *    (aka शेष TX)
	 */
	ant_cfg = antsel->ant_config[ANT_SELCFG_TX_DEF];
	mimo_antsel = brcms_c_antsel_antcfg2antsel(asi, ant_cfg);
	brcms_b_ग_लिखो_shm(wlc->hw, M_MIMO_ANTSEL_TXDFLT, mimo_antsel);
	/*
	 * Update driver stats क्रम currently selected
	 * शेष tx/rx antenna config
	 */
	asi->antcfg_cur.ant_config[ANT_SELCFG_TX_DEF] = ant_cfg;

	/* 2) Update RX antconfig क्रम all frames that are not unicast data
	 *    (aka शेष RX)
	 */
	ant_cfg = antsel->ant_config[ANT_SELCFG_RX_DEF];
	mimo_antsel = brcms_c_antsel_antcfg2antsel(asi, ant_cfg);
	brcms_b_ग_लिखो_shm(wlc->hw, M_MIMO_ANTSEL_RXDFLT, mimo_antsel);
	/*
	 * Update driver stats क्रम currently selected
	 * शेष tx/rx antenna config
	 */
	asi->antcfg_cur.ant_config[ANT_SELCFG_RX_DEF] = ant_cfg;

	वापस 0;
पूर्ण

व्योम brcms_c_antsel_init(काष्ठा antsel_info *asi)
अणु
	अगर ((asi->antsel_type == ANTSEL_2x3) ||
	    (asi->antsel_type == ANTSEL_2x4))
		brcms_c_antsel_cfgupd(asi, &asi->antcfg_11n);
पूर्ण

/* boardlevel antenna selection: convert id to ant_cfg */
अटल u8 brcms_c_antsel_id2antcfg(काष्ठा antsel_info *asi, u8 id)
अणु
	u8 antcfg = ANT_SELCFG_DEF_2x2;

	अगर (asi->antsel_type == ANTSEL_2x4) अणु
		/* 2x4 antenna भागersity board, 4 cfgs: 0-2 0-3 1-2 1-3 */
		antcfg = (((id & 0x2) << 3) | ((id & 0x1) + 2));
		वापस antcfg;

	पूर्ण अन्यथा अगर (asi->antsel_type == ANTSEL_2x3) अणु
		/* 2x3 antenna selection, 3 cfgs: 0-1 0-2 2-1 */
		antcfg = (((id & 0x02) << 4) | ((id & 0x1) + 1));
		वापस antcfg;
	पूर्ण

	वापस antcfg;
पूर्ण

व्योम
brcms_c_antsel_antcfg_get(काष्ठा antsel_info *asi, bool usedef, bool sel,
		      u8 antselid, u8 fbantselid, u8 *antcfg,
		      u8 *fbantcfg)
अणु
	u8 ant;

	/* अगर use शेष, assign it and वापस */
	अगर (usedef) अणु
		*antcfg = asi->antcfg_11n.ant_config[ANT_SELCFG_TX_DEF];
		*fbantcfg = *antcfg;
		वापस;
	पूर्ण

	अगर (!sel) अणु
		*antcfg = asi->antcfg_11n.ant_config[ANT_SELCFG_TX_UNICAST];
		*fbantcfg = *antcfg;

	पूर्ण अन्यथा अणु
		ant = asi->antcfg_11n.ant_config[ANT_SELCFG_TX_UNICAST];
		अगर ((ant & ANT_SELCFG_AUTO) == ANT_SELCFG_AUTO) अणु
			*antcfg = brcms_c_antsel_id2antcfg(asi, antselid);
			*fbantcfg = brcms_c_antsel_id2antcfg(asi, fbantselid);
		पूर्ण अन्यथा अणु
			*antcfg =
			    asi->antcfg_11n.ant_config[ANT_SELCFG_TX_UNICAST];
			*fbantcfg = *antcfg;
		पूर्ण
	पूर्ण
	वापस;
पूर्ण

/* boardlevel antenna selection: convert mimo_antsel (ucode पूर्णांकerface) to id */
u8 brcms_c_antsel_antsel2id(काष्ठा antsel_info *asi, u16 antsel)
अणु
	u8 antselid = 0;

	अगर (asi->antsel_type == ANTSEL_2x4) अणु
		/* 2x4 antenna भागersity board, 4 cfgs: 0-2 0-3 1-2 1-3 */
		antselid = mimo_2x4_भाग_antselid_tbl[(antsel & 0xf)];
		वापस antselid;

	पूर्ण अन्यथा अगर (asi->antsel_type == ANTSEL_2x3) अणु
		/* 2x3 antenna selection, 3 cfgs: 0-1 0-2 2-1 */
		antselid = mimo_2x3_भाग_antselid_tbl[(antsel & 0xf)];
		वापस antselid;
	पूर्ण

	वापस antselid;
पूर्ण
