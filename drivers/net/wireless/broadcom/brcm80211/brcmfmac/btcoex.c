<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2013 Broadcom Corporation
 */
#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>
#समावेश <net/cfg80211.h>

#समावेश <brcmu_wअगरi.h>
#समावेश <brcmu_utils.h>
#समावेश <defs.h>
#समावेश "core.h"
#समावेश "debug.h"
#समावेश "fwil.h"
#समावेश "fwil_types.h"
#समावेश "btcoex.h"
#समावेश "p2p.h"
#समावेश "cfg80211.h"

/* T1 start SCO/eSCO priority suppression */
#घोषणा BRCMF_BTCOEX_OPPR_WIN_TIME   msecs_to_jअगरfies(2000)

/* BT रेजिस्टरs values during DHCP */
#घोषणा BRCMF_BT_DHCP_REG50 0x8022
#घोषणा BRCMF_BT_DHCP_REG51 0
#घोषणा BRCMF_BT_DHCP_REG64 0
#घोषणा BRCMF_BT_DHCP_REG65 0
#घोषणा BRCMF_BT_DHCP_REG71 0
#घोषणा BRCMF_BT_DHCP_REG66 0x2710
#घोषणा BRCMF_BT_DHCP_REG41 0x33
#घोषणा BRCMF_BT_DHCP_REG68 0x190

/* number of samples क्रम SCO detection */
#घोषणा BRCMF_BT_SCO_SAMPLES 12

/**
* क्रमागत brcmf_btcoex_state - BT coex DHCP state machine states
* @BRCMF_BT_DHCP_IDLE: DCHP is idle
* @BRCMF_BT_DHCP_START: DHCP started, रुको beक्रमe
*	boosting wअगरi priority
* @BRCMF_BT_DHCP_OPPR_WIN: graceful DHCP opportunity ended,
*	boost wअगरi priority
* @BRCMF_BT_DHCP_FLAG_FORCE_TIMEOUT: wअगरi priority boost end,
*	restore शेषs
*/
क्रमागत brcmf_btcoex_state अणु
	BRCMF_BT_DHCP_IDLE,
	BRCMF_BT_DHCP_START,
	BRCMF_BT_DHCP_OPPR_WIN,
	BRCMF_BT_DHCP_FLAG_FORCE_TIMEOUT
पूर्ण;

/**
 * काष्ठा brcmf_btcoex_info - BT coex related inक्रमmation
 * @vअगर: पूर्णांकerface क्रम which request was करोne.
 * @समयr: समयr क्रम DHCP state machine
 * @समयout: configured समयout.
 * @समयr_on:  DHCP समयr active
 * @dhcp_करोne: DHCP finished beक्रमe T1/T2 समयr expiration
 * @bt_state: DHCP state machine state
 * @work: DHCP state machine work
 * @cfg: driver निजी data क्रम cfg80211 पूर्णांकerface
 * @reg66: saved value of btc_params 66
 * @reg41: saved value of btc_params 41
 * @reg68: saved value of btc_params 68
 * @saved_regs_part1: flag indicating regs 66,41,68
 *	have been saved
 * @reg50: saved value of btc_params 50
 * @reg51: saved value of btc_params 51
 * @reg64: saved value of btc_params 64
 * @reg65: saved value of btc_params 65
 * @reg71: saved value of btc_params 71
 * @saved_regs_part2: flag indicating regs 50,51,64,65,71
 *	have been saved
 */
काष्ठा brcmf_btcoex_info अणु
	काष्ठा brcmf_cfg80211_vअगर *vअगर;
	काष्ठा समयr_list समयr;
	u16 समयout;
	bool समयr_on;
	bool dhcp_करोne;
	क्रमागत brcmf_btcoex_state bt_state;
	काष्ठा work_काष्ठा work;
	काष्ठा brcmf_cfg80211_info *cfg;
	u32 reg66;
	u32 reg41;
	u32 reg68;
	bool saved_regs_part1;
	u32 reg50;
	u32 reg51;
	u32 reg64;
	u32 reg65;
	u32 reg71;
	bool saved_regs_part2;
पूर्ण;

/**
 * brcmf_btcoex_params_ग_लिखो() - ग_लिखो btc_params firmware variable
 * @अगरp: पूर्णांकerface
 * @addr: btc_params रेजिस्टर number
 * @data: data to ग_लिखो
 */
अटल s32 brcmf_btcoex_params_ग_लिखो(काष्ठा brcmf_अगर *अगरp, u32 addr, u32 data)
अणु
	काष्ठा अणु
		__le32 addr;
		__le32 data;
	पूर्ण reg_ग_लिखो;

	reg_ग_लिखो.addr = cpu_to_le32(addr);
	reg_ग_लिखो.data = cpu_to_le32(data);
	वापस brcmf_fil_iovar_data_set(अगरp, "btc_params",
					&reg_ग_लिखो, माप(reg_ग_लिखो));
पूर्ण

/**
 * brcmf_btcoex_params_पढ़ो() - पढ़ो btc_params firmware variable
 * @अगरp: पूर्णांकerface
 * @addr: btc_params रेजिस्टर number
 * @data: पढ़ो data
 */
अटल s32 brcmf_btcoex_params_पढ़ो(काष्ठा brcmf_अगर *अगरp, u32 addr, u32 *data)
अणु
	*data = addr;

	वापस brcmf_fil_iovar_पूर्णांक_get(अगरp, "btc_params", data);
पूर्ण

/**
 * brcmf_btcoex_boost_wअगरi() - control BT SCO/eSCO parameters
 * @btci: BT coex info
 * @trump_sco:
 *	true - set SCO/eSCO parameters क्रम compatibility
 *		during DHCP winकरोw
 *	false - restore saved parameter values
 *
 * Enhanced BT COEX settings क्रम eSCO compatibility during DHCP winकरोw
 */
अटल व्योम brcmf_btcoex_boost_wअगरi(काष्ठा brcmf_btcoex_info *btci,
				    bool trump_sco)
अणु
	काष्ठा brcmf_अगर *अगरp = brcmf_get_अगरp(btci->cfg->pub, 0);

	अगर (trump_sco && !btci->saved_regs_part2) अणु
		/* this should reduce eSCO agressive
		 * retransmit w/o अवरोधing it
		 */

		/* save current */
		brcmf_dbg(INFO, "new SCO/eSCO coex algo {save & override}\n");
		brcmf_btcoex_params_पढ़ो(अगरp, 50, &btci->reg50);
		brcmf_btcoex_params_पढ़ो(अगरp, 51, &btci->reg51);
		brcmf_btcoex_params_पढ़ो(अगरp, 64, &btci->reg64);
		brcmf_btcoex_params_पढ़ो(अगरp, 65, &btci->reg65);
		brcmf_btcoex_params_पढ़ो(अगरp, 71, &btci->reg71);

		btci->saved_regs_part2 = true;
		brcmf_dbg(INFO,
			  "saved bt_params[50,51,64,65,71]: 0x%x 0x%x 0x%x 0x%x 0x%x\n",
			  btci->reg50, btci->reg51, btci->reg64,
			  btci->reg65, btci->reg71);

		/* pacअगरy the eSco   */
		brcmf_btcoex_params_ग_लिखो(अगरp, 50, BRCMF_BT_DHCP_REG50);
		brcmf_btcoex_params_ग_लिखो(अगरp, 51, BRCMF_BT_DHCP_REG51);
		brcmf_btcoex_params_ग_लिखो(अगरp, 64, BRCMF_BT_DHCP_REG64);
		brcmf_btcoex_params_ग_लिखो(अगरp, 65, BRCMF_BT_DHCP_REG65);
		brcmf_btcoex_params_ग_लिखो(अगरp, 71, BRCMF_BT_DHCP_REG71);

	पूर्ण अन्यथा अगर (btci->saved_regs_part2) अणु
		/* restore previously saved bt params */
		brcmf_dbg(INFO, "Do new SCO/eSCO coex algo {restore}\n");
		brcmf_btcoex_params_ग_लिखो(अगरp, 50, btci->reg50);
		brcmf_btcoex_params_ग_लिखो(अगरp, 51, btci->reg51);
		brcmf_btcoex_params_ग_लिखो(अगरp, 64, btci->reg64);
		brcmf_btcoex_params_ग_लिखो(अगरp, 65, btci->reg65);
		brcmf_btcoex_params_ग_लिखो(अगरp, 71, btci->reg71);

		brcmf_dbg(INFO,
			  "restored bt_params[50,51,64,65,71]: 0x%x 0x%x 0x%x 0x%x 0x%x\n",
			  btci->reg50, btci->reg51, btci->reg64,
			  btci->reg65, btci->reg71);

		btci->saved_regs_part2 = false;
	पूर्ण अन्यथा अणु
		brcmf_dbg(INFO, "attempted to restore not saved BTCOEX params\n");
	पूर्ण
पूर्ण

/**
 * brcmf_btcoex_is_sco_active() - check अगर SCO/eSCO is active
 * @अगरp: पूर्णांकerface
 *
 * वापस: true अगर SCO/eSCO session is active
 */
अटल bool brcmf_btcoex_is_sco_active(काष्ठा brcmf_अगर *अगरp)
अणु
	पूर्णांक ioc_res = 0;
	bool res = false;
	पूर्णांक sco_id_cnt = 0;
	u32 param27;
	पूर्णांक i;

	क्रम (i = 0; i < BRCMF_BT_SCO_SAMPLES; i++) अणु
		ioc_res = brcmf_btcoex_params_पढ़ो(अगरp, 27, &param27);

		अगर (ioc_res < 0) अणु
			brcmf_err("ioc read btc params error\n");
			अवरोध;
		पूर्ण

		brcmf_dbg(INFO, "sample[%d], btc_params 27:%x\n", i, param27);

		अगर ((param27 & 0x6) == 2) अणु /* count both sco & esco  */
			sco_id_cnt++;
		पूर्ण

		अगर (sco_id_cnt > 2) अणु
			brcmf_dbg(INFO,
				  "sco/esco detected, pkt id_cnt:%d samples:%d\n",
				  sco_id_cnt, i);
			res = true;
			अवरोध;
		पूर्ण
	पूर्ण
	brcmf_dbg(TRACE, "exit: result=%d\n", res);
	वापस res;
पूर्ण

/*
 * btcmf_btcoex_save_part1() - save first step parameters.
 */
अटल व्योम btcmf_btcoex_save_part1(काष्ठा brcmf_btcoex_info *btci)
अणु
	काष्ठा brcmf_अगर *अगरp = btci->vअगर->अगरp;

	अगर (!btci->saved_regs_part1) अणु
		/* Retrieve and save original reg value */
		brcmf_btcoex_params_पढ़ो(अगरp, 66, &btci->reg66);
		brcmf_btcoex_params_पढ़ो(अगरp, 41, &btci->reg41);
		brcmf_btcoex_params_पढ़ो(अगरp, 68, &btci->reg68);
		btci->saved_regs_part1 = true;
		brcmf_dbg(INFO,
			  "saved btc_params regs (66,41,68) 0x%x 0x%x 0x%x\n",
			  btci->reg66, btci->reg41,
			  btci->reg68);
	पूर्ण
पूर्ण

/*
 * brcmf_btcoex_restore_part1() - restore first step parameters.
 */
अटल व्योम brcmf_btcoex_restore_part1(काष्ठा brcmf_btcoex_info *btci)
अणु
	काष्ठा brcmf_अगर *अगरp;

	अगर (btci->saved_regs_part1) अणु
		btci->saved_regs_part1 = false;
		अगरp = btci->vअगर->अगरp;
		brcmf_btcoex_params_ग_लिखो(अगरp, 66, btci->reg66);
		brcmf_btcoex_params_ग_लिखो(अगरp, 41, btci->reg41);
		brcmf_btcoex_params_ग_लिखो(अगरp, 68, btci->reg68);
		brcmf_dbg(INFO,
			  "restored btc_params regs {66,41,68} 0x%x 0x%x 0x%x\n",
			  btci->reg66, btci->reg41,
			  btci->reg68);
	पूर्ण
पूर्ण

/*
 * brcmf_btcoex_समयrfunc() - BT coex समयr callback
 */
अटल व्योम brcmf_btcoex_समयrfunc(काष्ठा समयr_list *t)
अणु
	काष्ठा brcmf_btcoex_info *bt_local = from_समयr(bt_local, t, समयr);
	brcmf_dbg(TRACE, "enter\n");

	bt_local->समयr_on = false;
	schedule_work(&bt_local->work);
पूर्ण

/**
 * brcmf_btcoex_handler() - BT coex state machine work handler
 * @work: work
 */
अटल व्योम brcmf_btcoex_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा brcmf_btcoex_info *btci;
	btci = container_of(work, काष्ठा brcmf_btcoex_info, work);
	अगर (btci->समयr_on) अणु
		btci->समयr_on = false;
		del_समयr_sync(&btci->समयr);
	पूर्ण

	चयन (btci->bt_state) अणु
	हाल BRCMF_BT_DHCP_START:
		/* DHCP started provide OPPORTUNITY winकरोw
		   to get DHCP address
		*/
		brcmf_dbg(INFO, "DHCP started\n");
		btci->bt_state = BRCMF_BT_DHCP_OPPR_WIN;
		अगर (btci->समयout < BRCMF_BTCOEX_OPPR_WIN_TIME) अणु
			mod_समयr(&btci->समयr, btci->समयr.expires);
		पूर्ण अन्यथा अणु
			btci->समयout -= BRCMF_BTCOEX_OPPR_WIN_TIME;
			mod_समयr(&btci->समयr,
				  jअगरfies + BRCMF_BTCOEX_OPPR_WIN_TIME);
		पूर्ण
		btci->समयr_on = true;
		अवरोध;

	हाल BRCMF_BT_DHCP_OPPR_WIN:
		अगर (btci->dhcp_करोne) अणु
			brcmf_dbg(INFO, "DHCP done before T1 expiration\n");
			जाओ idle;
		पूर्ण

		/* DHCP is not over yet, start lowering BT priority */
		brcmf_dbg(INFO, "DHCP T1:%d expired\n",
			  jअगरfies_to_msecs(BRCMF_BTCOEX_OPPR_WIN_TIME));
		brcmf_btcoex_boost_wअगरi(btci, true);

		btci->bt_state = BRCMF_BT_DHCP_FLAG_FORCE_TIMEOUT;
		mod_समयr(&btci->समयr, jअगरfies + btci->समयout);
		btci->समयr_on = true;
		अवरोध;

	हाल BRCMF_BT_DHCP_FLAG_FORCE_TIMEOUT:
		अगर (btci->dhcp_करोne)
			brcmf_dbg(INFO, "DHCP done before T2 expiration\n");
		अन्यथा
			brcmf_dbg(INFO, "DHCP T2:%d expired\n",
				  BRCMF_BT_DHCP_FLAG_FORCE_TIMEOUT);

		जाओ idle;

	शेष:
		brcmf_err("invalid state=%d !!!\n", btci->bt_state);
		जाओ idle;
	पूर्ण

	वापस;

idle:
	btci->bt_state = BRCMF_BT_DHCP_IDLE;
	btci->समयr_on = false;
	brcmf_btcoex_boost_wअगरi(btci, false);
	cfg80211_crit_proto_stopped(&btci->vअगर->wdev, GFP_KERNEL);
	brcmf_btcoex_restore_part1(btci);
	btci->vअगर = शून्य;
पूर्ण

/**
 * brcmf_btcoex_attach() - initialize BT coex data
 * @cfg: driver निजी cfg80211 data
 *
 * वापस: 0 on success
 */
पूर्णांक brcmf_btcoex_attach(काष्ठा brcmf_cfg80211_info *cfg)
अणु
	काष्ठा brcmf_btcoex_info *btci = शून्य;
	brcmf_dbg(TRACE, "enter\n");

	btci = kदो_स्मृति(माप(काष्ठा brcmf_btcoex_info), GFP_KERNEL);
	अगर (!btci)
		वापस -ENOMEM;

	btci->bt_state = BRCMF_BT_DHCP_IDLE;

	/* Set up समयr क्रम BT  */
	btci->समयr_on = false;
	btci->समयout = BRCMF_BTCOEX_OPPR_WIN_TIME;
	समयr_setup(&btci->समयr, brcmf_btcoex_समयrfunc, 0);
	btci->cfg = cfg;
	btci->saved_regs_part1 = false;
	btci->saved_regs_part2 = false;

	INIT_WORK(&btci->work, brcmf_btcoex_handler);

	cfg->btcoex = btci;
	वापस 0;
पूर्ण

/**
 * brcmf_btcoex_detach - clean BT coex data
 * @cfg: driver निजी cfg80211 data
 */
व्योम brcmf_btcoex_detach(काष्ठा brcmf_cfg80211_info *cfg)
अणु
	brcmf_dbg(TRACE, "enter\n");

	अगर (!cfg->btcoex)
		वापस;

	अगर (cfg->btcoex->समयr_on) अणु
		cfg->btcoex->समयr_on = false;
		del_समयr_sync(&cfg->btcoex->समयr);
	पूर्ण

	cancel_work_sync(&cfg->btcoex->work);

	brcmf_btcoex_boost_wअगरi(cfg->btcoex, false);
	brcmf_btcoex_restore_part1(cfg->btcoex);

	kमुक्त(cfg->btcoex);
	cfg->btcoex = शून्य;
पूर्ण

अटल व्योम brcmf_btcoex_dhcp_start(काष्ठा brcmf_btcoex_info *btci)
अणु
	काष्ठा brcmf_अगर *अगरp = btci->vअगर->अगरp;

	btcmf_btcoex_save_part1(btci);
	/* set new regs values */
	brcmf_btcoex_params_ग_लिखो(अगरp, 66, BRCMF_BT_DHCP_REG66);
	brcmf_btcoex_params_ग_लिखो(अगरp, 41, BRCMF_BT_DHCP_REG41);
	brcmf_btcoex_params_ग_लिखो(अगरp, 68, BRCMF_BT_DHCP_REG68);
	btci->dhcp_करोne = false;
	btci->bt_state = BRCMF_BT_DHCP_START;
	schedule_work(&btci->work);
	brcmf_dbg(TRACE, "enable BT DHCP Timer\n");
पूर्ण

अटल व्योम brcmf_btcoex_dhcp_end(काष्ठा brcmf_btcoex_info *btci)
अणु
	/* Stop any bt समयr because DHCP session is करोne */
	btci->dhcp_करोne = true;
	अगर (btci->समयr_on) अणु
		brcmf_dbg(INFO, "disable BT DHCP Timer\n");
		btci->समयr_on = false;
		del_समयr_sync(&btci->समयr);

		/* schedule worker अगर transition to IDLE is needed */
		अगर (btci->bt_state != BRCMF_BT_DHCP_IDLE) अणु
			brcmf_dbg(INFO, "bt_state:%d\n",
				  btci->bt_state);
			schedule_work(&btci->work);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Restore original values */
		brcmf_btcoex_restore_part1(btci);
	पूर्ण
पूर्ण

/*
 * brcmf_btcoex_set_mode - set BT coex mode
 * @mode: Wअगरi-Bluetooth coexistence mode
 *
 * वापस: 0 on success
 */
पूर्णांक brcmf_btcoex_set_mode(काष्ठा brcmf_cfg80211_vअगर *vअगर,
			  क्रमागत brcmf_btcoex_mode mode, u16 duration)
अणु
	काष्ठा brcmf_cfg80211_info *cfg = wiphy_to_cfg(vअगर->wdev.wiphy);
	काष्ठा brcmf_btcoex_info *btci = cfg->btcoex;
	काष्ठा brcmf_अगर *अगरp = brcmf_get_अगरp(cfg->pub, 0);

	चयन (mode) अणु
	हाल BRCMF_BTCOEX_DISABLED:
		brcmf_dbg(INFO, "DHCP session starts\n");
		अगर (btci->bt_state != BRCMF_BT_DHCP_IDLE)
			वापस -EBUSY;
		/* Start BT समयr only क्रम SCO connection */
		अगर (brcmf_btcoex_is_sco_active(अगरp)) अणु
			btci->समयout = msecs_to_jअगरfies(duration);
			btci->vअगर = vअगर;
			brcmf_btcoex_dhcp_start(btci);
		पूर्ण
		अवरोध;

	हाल BRCMF_BTCOEX_ENABLED:
		brcmf_dbg(INFO, "DHCP session ends\n");
		अगर (btci->bt_state != BRCMF_BT_DHCP_IDLE &&
		    vअगर == btci->vअगर) अणु
			brcmf_btcoex_dhcp_end(btci);
		पूर्ण
		अवरोध;
	शेष:
		brcmf_dbg(INFO, "Unknown mode, ignored\n");
	पूर्ण
	वापस 0;
पूर्ण
