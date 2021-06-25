<शैली गुरु>
/*
 * Copyright 2014 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs
 */
#समावेश "dp.h"
#समावेश "conn.h"
#समावेश "head.h"
#समावेश "ior.h"

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/init.h>
#समावेश <subdev/gpपन.स>
#समावेश <subdev/i2c.h>

#समावेश <nvअगर/event.h>

/* IED scripts are no दीर्घer used by UEFI/RM from Ampere, but have been updated क्रम
 * the x86 option ROM.  However, the relevant VBIOS table versions weren't modअगरied,
 * so we're unable to detect this in a nice way.
 */
#घोषणा AMPERE_IED_HACK(disp) ((disp)->engine.subdev.device->card_type >= GA100)

काष्ठा lt_state अणु
	काष्ठा nvkm_dp *dp;
	u8  stat[6];
	u8  conf[4];
	bool pc2;
	u8  pc2stat;
	u8  pc2conf[2];
पूर्ण;

अटल पूर्णांक
nvkm_dp_train_sense(काष्ठा lt_state *lt, bool pc, u32 delay)
अणु
	काष्ठा nvkm_dp *dp = lt->dp;
	पूर्णांक ret;

	अगर (dp->dpcd[DPCD_RC0E_AUX_RD_INTERVAL])
		mdelay(dp->dpcd[DPCD_RC0E_AUX_RD_INTERVAL] * 4);
	अन्यथा
		udelay(delay);

	ret = nvkm_rdaux(dp->aux, DPCD_LS02, lt->stat, 6);
	अगर (ret)
		वापस ret;

	अगर (pc) अणु
		ret = nvkm_rdaux(dp->aux, DPCD_LS0C, &lt->pc2stat, 1);
		अगर (ret)
			lt->pc2stat = 0x00;
		OUTP_TRACE(&dp->outp, "status %6ph pc2 %02x",
			   lt->stat, lt->pc2stat);
	पूर्ण अन्यथा अणु
		OUTP_TRACE(&dp->outp, "status %6ph", lt->stat);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_dp_train_drive(काष्ठा lt_state *lt, bool pc)
अणु
	काष्ठा nvkm_dp *dp = lt->dp;
	काष्ठा nvkm_ior *ior = dp->outp.ior;
	काष्ठा nvkm_bios *bios = ior->disp->engine.subdev.device->bios;
	काष्ठा nvbios_dpout info;
	काष्ठा nvbios_dpcfg ocfg;
	u8  ver, hdr, cnt, len;
	u32 data;
	पूर्णांक ret, i;

	क्रम (i = 0; i < ior->dp.nr; i++) अणु
		u8 lane = (lt->stat[4 + (i >> 1)] >> ((i & 1) * 4)) & 0xf;
		u8 lpc2 = (lt->pc2stat >> (i * 2)) & 0x3;
		u8 lpre = (lane & 0x0c) >> 2;
		u8 lvsw = (lane & 0x03) >> 0;
		u8 hivs = 3 - lpre;
		u8 hipe = 3;
		u8 hipc = 3;

		अगर (lpc2 >= hipc)
			lpc2 = hipc | DPCD_LC0F_LANE0_MAX_POST_CURSOR2_REACHED;
		अगर (lpre >= hipe) अणु
			lpre = hipe | DPCD_LC03_MAX_SWING_REACHED; /* yes. */
			lvsw = hivs = 3 - (lpre & 3);
		पूर्ण अन्यथा
		अगर (lvsw >= hivs) अणु
			lvsw = hivs | DPCD_LC03_MAX_SWING_REACHED;
		पूर्ण

		lt->conf[i] = (lpre << 3) | lvsw;
		lt->pc2conf[i >> 1] |= lpc2 << ((i & 1) * 4);

		OUTP_TRACE(&dp->outp, "config lane %d %02x %02x",
			   i, lt->conf[i], lpc2);

		data = nvbios_dpout_match(bios, dp->outp.info.hasht,
						dp->outp.info.hashm,
					  &ver, &hdr, &cnt, &len, &info);
		अगर (!data)
			जारी;

		data = nvbios_dpcfg_match(bios, data, lpc2 & 3, lvsw & 3,
					  lpre & 3, &ver, &hdr, &cnt, &len,
					  &ocfg);
		अगर (!data)
			जारी;

		ior->func->dp.drive(ior, i, ocfg.pc, ocfg.dc,
					    ocfg.pe, ocfg.tx_pu);
	पूर्ण

	ret = nvkm_wraux(dp->aux, DPCD_LC03(0), lt->conf, 4);
	अगर (ret)
		वापस ret;

	अगर (pc) अणु
		ret = nvkm_wraux(dp->aux, DPCD_LC0F, lt->pc2conf, 2);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
nvkm_dp_train_pattern(काष्ठा lt_state *lt, u8 pattern)
अणु
	काष्ठा nvkm_dp *dp = lt->dp;
	u8 sink_tp;

	OUTP_TRACE(&dp->outp, "training pattern %d", pattern);
	dp->outp.ior->func->dp.pattern(dp->outp.ior, pattern);

	nvkm_rdaux(dp->aux, DPCD_LC02, &sink_tp, 1);
	sink_tp &= ~DPCD_LC02_TRAINING_PATTERN_SET;
	sink_tp |= pattern;
	nvkm_wraux(dp->aux, DPCD_LC02, &sink_tp, 1);
पूर्ण

अटल पूर्णांक
nvkm_dp_train_eq(काष्ठा lt_state *lt)
अणु
	bool eq_करोne = false, cr_करोne = true;
	पूर्णांक tries = 0, i;

	अगर (lt->dp->dpcd[DPCD_RC02] & DPCD_RC02_TPS3_SUPPORTED)
		nvkm_dp_train_pattern(lt, 3);
	अन्यथा
		nvkm_dp_train_pattern(lt, 2);

	करो अणु
		अगर ((tries &&
		    nvkm_dp_train_drive(lt, lt->pc2)) ||
		    nvkm_dp_train_sense(lt, lt->pc2, 400))
			अवरोध;

		eq_करोne = !!(lt->stat[2] & DPCD_LS04_INTERLANE_ALIGN_DONE);
		क्रम (i = 0; i < lt->dp->outp.ior->dp.nr && eq_करोne; i++) अणु
			u8 lane = (lt->stat[i >> 1] >> ((i & 1) * 4)) & 0xf;
			अगर (!(lane & DPCD_LS02_LANE0_CR_DONE))
				cr_करोne = false;
			अगर (!(lane & DPCD_LS02_LANE0_CHANNEL_EQ_DONE) ||
			    !(lane & DPCD_LS02_LANE0_SYMBOL_LOCKED))
				eq_करोne = false;
		पूर्ण
	पूर्ण जबतक (!eq_करोne && cr_करोne && ++tries <= 5);

	वापस eq_करोne ? 0 : -1;
पूर्ण

अटल पूर्णांक
nvkm_dp_train_cr(काष्ठा lt_state *lt)
अणु
	bool cr_करोne = false, पात = false;
	पूर्णांक voltage = lt->conf[0] & DPCD_LC03_VOLTAGE_SWING_SET;
	पूर्णांक tries = 0, i;

	nvkm_dp_train_pattern(lt, 1);

	करो अणु
		अगर (nvkm_dp_train_drive(lt, false) ||
		    nvkm_dp_train_sense(lt, false, 100))
			अवरोध;

		cr_करोne = true;
		क्रम (i = 0; i < lt->dp->outp.ior->dp.nr; i++) अणु
			u8 lane = (lt->stat[i >> 1] >> ((i & 1) * 4)) & 0xf;
			अगर (!(lane & DPCD_LS02_LANE0_CR_DONE)) अणु
				cr_करोne = false;
				अगर (lt->conf[i] & DPCD_LC03_MAX_SWING_REACHED)
					पात = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर ((lt->conf[0] & DPCD_LC03_VOLTAGE_SWING_SET) != voltage) अणु
			voltage = lt->conf[0] & DPCD_LC03_VOLTAGE_SWING_SET;
			tries = 0;
		पूर्ण
	पूर्ण जबतक (!cr_करोne && !पात && ++tries < 5);

	वापस cr_करोne ? 0 : -1;
पूर्ण

अटल पूर्णांक
nvkm_dp_train_links(काष्ठा nvkm_dp *dp)
अणु
	काष्ठा nvkm_ior *ior = dp->outp.ior;
	काष्ठा nvkm_disp *disp = dp->outp.disp;
	काष्ठा nvkm_subdev *subdev = &disp->engine.subdev;
	काष्ठा nvkm_bios *bios = subdev->device->bios;
	काष्ठा lt_state lt = अणु
		.dp = dp,
	पूर्ण;
	u32 lnkcmp;
	u8 sink[2];
	पूर्णांक ret;

	OUTP_DBG(&dp->outp, "training %d x %d MB/s",
		 ior->dp.nr, ior->dp.bw * 27);

	/* Intersect misc. capabilities of the OR and sink. */
	अगर (disp->engine.subdev.device->chipset < 0xd0)
		dp->dpcd[DPCD_RC02] &= ~DPCD_RC02_TPS3_SUPPORTED;
	lt.pc2 = dp->dpcd[DPCD_RC02] & DPCD_RC02_TPS3_SUPPORTED;

	अगर (AMPERE_IED_HACK(disp) && (lnkcmp = lt.dp->info.script[0])) अणु
		/* Execute Beक्रमeLinkTraining script from DP Info table. */
		जबतक (ior->dp.bw < nvbios_rd08(bios, lnkcmp))
			lnkcmp += 3;
		lnkcmp = nvbios_rd16(bios, lnkcmp + 1);

		nvbios_init(&dp->outp.disp->engine.subdev, lnkcmp,
			init.outp = &dp->outp.info;
			init.or   = ior->id;
			init.link = ior->asy.link;
		);
	पूर्ण

	/* Set desired link configuration on the source. */
	अगर ((lnkcmp = lt.dp->info.lnkcmp)) अणु
		अगर (dp->version < 0x30) अणु
			जबतक ((ior->dp.bw * 2700) < nvbios_rd16(bios, lnkcmp))
				lnkcmp += 4;
			lnkcmp = nvbios_rd16(bios, lnkcmp + 2);
		पूर्ण अन्यथा अणु
			जबतक (ior->dp.bw < nvbios_rd08(bios, lnkcmp))
				lnkcmp += 3;
			lnkcmp = nvbios_rd16(bios, lnkcmp + 1);
		पूर्ण

		nvbios_init(subdev, lnkcmp,
			init.outp = &dp->outp.info;
			init.or   = ior->id;
			init.link = ior->asy.link;
		);
	पूर्ण

	ret = ior->func->dp.links(ior, dp->aux);
	अगर (ret) अणु
		अगर (ret < 0) अणु
			OUTP_ERR(&dp->outp, "train failed with %d", ret);
			वापस ret;
		पूर्ण
		वापस 0;
	पूर्ण

	ior->func->dp.घातer(ior, ior->dp.nr);

	/* Set desired link configuration on the sink. */
	sink[0] = ior->dp.bw;
	sink[1] = ior->dp.nr;
	अगर (ior->dp.ef)
		sink[1] |= DPCD_LC01_ENHANCED_FRAME_EN;

	ret = nvkm_wraux(dp->aux, DPCD_LC00_LINK_BW_SET, sink, 2);
	अगर (ret)
		वापस ret;

	/* Attempt to train the link in this configuration. */
	स_रखो(lt.stat, 0x00, माप(lt.stat));
	ret = nvkm_dp_train_cr(&lt);
	अगर (ret == 0)
		ret = nvkm_dp_train_eq(&lt);
	nvkm_dp_train_pattern(&lt, 0);
	वापस ret;
पूर्ण

अटल व्योम
nvkm_dp_train_fini(काष्ठा nvkm_dp *dp)
अणु
	/* Execute AfterLinkTraining script from DP Info table. */
	nvbios_init(&dp->outp.disp->engine.subdev, dp->info.script[1],
		init.outp = &dp->outp.info;
		init.or   = dp->outp.ior->id;
		init.link = dp->outp.ior->asy.link;
	);
पूर्ण

अटल व्योम
nvkm_dp_train_init(काष्ठा nvkm_dp *dp)
अणु
	/* Execute EnableSpपढ़ो/DisableSpपढ़ो script from DP Info table. */
	अगर (dp->dpcd[DPCD_RC03] & DPCD_RC03_MAX_DOWNSPREAD) अणु
		nvbios_init(&dp->outp.disp->engine.subdev, dp->info.script[2],
			init.outp = &dp->outp.info;
			init.or   = dp->outp.ior->id;
			init.link = dp->outp.ior->asy.link;
		);
	पूर्ण अन्यथा अणु
		nvbios_init(&dp->outp.disp->engine.subdev, dp->info.script[3],
			init.outp = &dp->outp.info;
			init.or   = dp->outp.ior->id;
			init.link = dp->outp.ior->asy.link;
		);
	पूर्ण

	अगर (!AMPERE_IED_HACK(dp->outp.disp)) अणु
		/* Execute Beक्रमeLinkTraining script from DP Info table. */
		nvbios_init(&dp->outp.disp->engine.subdev, dp->info.script[0],
			init.outp = &dp->outp.info;
			init.or   = dp->outp.ior->id;
			init.link = dp->outp.ior->asy.link;
		);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा dp_rates अणु
	u32 rate;
	u8  bw;
	u8  nr;
पूर्ण nvkm_dp_rates[] = अणु
	अणु 2160000, 0x14, 4 पूर्ण,
	अणु 1080000, 0x0a, 4 पूर्ण,
	अणु 1080000, 0x14, 2 पूर्ण,
	अणु  648000, 0x06, 4 पूर्ण,
	अणु  540000, 0x0a, 2 पूर्ण,
	अणु  540000, 0x14, 1 पूर्ण,
	अणु  324000, 0x06, 2 पूर्ण,
	अणु  270000, 0x0a, 1 पूर्ण,
	अणु  162000, 0x06, 1 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक
nvkm_dp_train(काष्ठा nvkm_dp *dp, u32 dataKBps)
अणु
	काष्ठा nvkm_ior *ior = dp->outp.ior;
	स्थिर u8 sink_nr = dp->dpcd[DPCD_RC02] & DPCD_RC02_MAX_LANE_COUNT;
	स्थिर u8 sink_bw = dp->dpcd[DPCD_RC01_MAX_LINK_RATE];
	स्थिर u8 outp_nr = dp->outp.info.dpconf.link_nr;
	स्थिर u8 outp_bw = dp->outp.info.dpconf.link_bw;
	स्थिर काष्ठा dp_rates *failsafe = शून्य, *cfg;
	पूर्णांक ret = -EINVAL;
	u8  pwr;

	/* Find the lowest configuration of the OR that can support
	 * the required link rate.
	 *
	 * We will refuse to program the OR to lower rates, even अगर
	 * link training fails at higher rates (or even अगर the sink
	 * can't support the rate at all, though the DD is supposed
	 * to prevent such situations from happening).
	 *
	 * Attempting to करो so can cause the entire display to hang,
	 * and it's better to have a failed modeset than that.
	 */
	क्रम (cfg = nvkm_dp_rates; cfg->rate; cfg++) अणु
		अगर (cfg->nr <= outp_nr && cfg->bw <= outp_bw) अणु
			/* Try to respect sink limits too when selecting
			 * lowest link configuration.
			 */
			अगर (!failsafe ||
			    (cfg->nr <= sink_nr && cfg->bw <= sink_bw))
				failsafe = cfg;
		पूर्ण

		अगर (failsafe && cfg[1].rate < dataKBps)
			अवरोध;
	पूर्ण

	अगर (WARN_ON(!failsafe))
		वापस ret;

	/* Ensure sink is not in a low-घातer state. */
	अगर (!nvkm_rdaux(dp->aux, DPCD_SC00, &pwr, 1)) अणु
		अगर ((pwr & DPCD_SC00_SET_POWER) != DPCD_SC00_SET_POWER_D0) अणु
			pwr &= ~DPCD_SC00_SET_POWER;
			pwr |=  DPCD_SC00_SET_POWER_D0;
			nvkm_wraux(dp->aux, DPCD_SC00, &pwr, 1);
		पूर्ण
	पूर्ण

	/* Link training. */
	OUTP_DBG(&dp->outp, "training (min: %d x %d MB/s)",
		 failsafe->nr, failsafe->bw * 27);
	nvkm_dp_train_init(dp);
	क्रम (cfg = nvkm_dp_rates; ret < 0 && cfg <= failsafe; cfg++) अणु
		/* Skip configurations not supported by both OR and sink. */
		अगर ((cfg->nr > outp_nr || cfg->bw > outp_bw ||
		     cfg->nr > sink_nr || cfg->bw > sink_bw)) अणु
			अगर (cfg != failsafe)
				जारी;
			OUTP_ERR(&dp->outp, "link rate unsupported by sink");
		पूर्ण
		ior->dp.mst = dp->lt.mst;
		ior->dp.ef = dp->dpcd[DPCD_RC02] & DPCD_RC02_ENHANCED_FRAME_CAP;
		ior->dp.bw = cfg->bw;
		ior->dp.nr = cfg->nr;

		/* Program selected link configuration. */
		ret = nvkm_dp_train_links(dp);
	पूर्ण
	nvkm_dp_train_fini(dp);
	अगर (ret < 0)
		OUTP_ERR(&dp->outp, "training failed");
	अन्यथा
		OUTP_DBG(&dp->outp, "training done");
	atomic_set(&dp->lt.करोne, 1);
	वापस ret;
पूर्ण

अटल व्योम
nvkm_dp_disable(काष्ठा nvkm_outp *outp, काष्ठा nvkm_ior *ior)
अणु
	काष्ठा nvkm_dp *dp = nvkm_dp(outp);

	/* Execute DisableLT script from DP Info Table. */
	nvbios_init(&ior->disp->engine.subdev, dp->info.script[4],
		init.outp = &dp->outp.info;
		init.or   = ior->id;
		init.link = ior->arm.link;
	);
पूर्ण

अटल व्योम
nvkm_dp_release(काष्ठा nvkm_outp *outp)
अणु
	काष्ठा nvkm_dp *dp = nvkm_dp(outp);

	/* Prevent link from being retrained अगर sink sends an IRQ. */
	atomic_set(&dp->lt.करोne, 0);
	dp->outp.ior->dp.nr = 0;
पूर्ण

अटल पूर्णांक
nvkm_dp_acquire(काष्ठा nvkm_outp *outp)
अणु
	काष्ठा nvkm_dp *dp = nvkm_dp(outp);
	काष्ठा nvkm_ior *ior = dp->outp.ior;
	काष्ठा nvkm_head *head;
	bool retrain = true;
	u32 datakbps = 0;
	u32 dataKBps;
	u32 linkKBps;
	u8  stat[3];
	पूर्णांक ret, i;

	mutex_lock(&dp->mutex);

	/* Check that link configuration meets current requirements. */
	list_क्रम_each_entry(head, &outp->disp->head, head) अणु
		अगर (ior->asy.head & (1 << head->id)) अणु
			u32 khz = (head->asy.hz >> ior->asy.rgभाग) / 1000;
			datakbps += khz * head->asy.or.depth;
		पूर्ण
	पूर्ण

	linkKBps = ior->dp.bw * 27000 * ior->dp.nr;
	dataKBps = DIV_ROUND_UP(datakbps, 8);
	OUTP_DBG(&dp->outp, "data %d KB/s link %d KB/s mst %d->%d",
		 dataKBps, linkKBps, ior->dp.mst, dp->lt.mst);
	अगर (linkKBps < dataKBps || ior->dp.mst != dp->lt.mst) अणु
		OUTP_DBG(&dp->outp, "link requirements changed");
		जाओ करोne;
	पूर्ण

	/* Check that link is still trained. */
	ret = nvkm_rdaux(dp->aux, DPCD_LS02, stat, 3);
	अगर (ret) अणु
		OUTP_DBG(&dp->outp,
			 "failed to read link status, assuming no sink");
		जाओ करोne;
	पूर्ण

	अगर (stat[2] & DPCD_LS04_INTERLANE_ALIGN_DONE) अणु
		क्रम (i = 0; i < ior->dp.nr; i++) अणु
			u8 lane = (stat[i >> 1] >> ((i & 1) * 4)) & 0x0f;
			अगर (!(lane & DPCD_LS02_LANE0_CR_DONE) ||
			    !(lane & DPCD_LS02_LANE0_CHANNEL_EQ_DONE) ||
			    !(lane & DPCD_LS02_LANE0_SYMBOL_LOCKED)) अणु
				OUTP_DBG(&dp->outp,
					 "lane %d not equalised", lane);
				जाओ करोne;
			पूर्ण
		पूर्ण
		retrain = false;
	पूर्ण अन्यथा अणु
		OUTP_DBG(&dp->outp, "no inter-lane alignment");
	पूर्ण

करोne:
	अगर (retrain || !atomic_पढ़ो(&dp->lt.करोne))
		ret = nvkm_dp_train(dp, dataKBps);
	mutex_unlock(&dp->mutex);
	वापस ret;
पूर्ण

अटल bool
nvkm_dp_enable(काष्ठा nvkm_dp *dp, bool enable)
अणु
	काष्ठा nvkm_i2c_aux *aux = dp->aux;

	अगर (enable) अणु
		अगर (!dp->present) अणु
			OUTP_DBG(&dp->outp, "aux power -> always");
			nvkm_i2c_aux_monitor(aux, true);
			dp->present = true;
		पूर्ण

		अगर (!nvkm_rdaux(aux, DPCD_RC00_DPCD_REV, dp->dpcd,
				माप(dp->dpcd)))
			वापस true;
	पूर्ण

	अगर (dp->present) अणु
		OUTP_DBG(&dp->outp, "aux power -> demand");
		nvkm_i2c_aux_monitor(aux, false);
		dp->present = false;
	पूर्ण

	atomic_set(&dp->lt.करोne, 0);
	वापस false;
पूर्ण

अटल पूर्णांक
nvkm_dp_hpd(काष्ठा nvkm_notअगरy *notअगरy)
अणु
	स्थिर काष्ठा nvkm_i2c_ntfy_rep *line = notअगरy->data;
	काष्ठा nvkm_dp *dp = container_of(notअगरy, typeof(*dp), hpd);
	काष्ठा nvkm_conn *conn = dp->outp.conn;
	काष्ठा nvkm_disp *disp = dp->outp.disp;
	काष्ठा nvअगर_notअगरy_conn_rep_v0 rep = अणुपूर्ण;

	OUTP_DBG(&dp->outp, "HPD: %d", line->mask);
	अगर (line->mask & NVKM_I2C_IRQ) अणु
		अगर (atomic_पढ़ो(&dp->lt.करोne))
			dp->outp.func->acquire(&dp->outp);
		rep.mask |= NVIF_NOTIFY_CONN_V0_IRQ;
	पूर्ण अन्यथा अणु
		nvkm_dp_enable(dp, true);
	पूर्ण

	अगर (line->mask & NVKM_I2C_UNPLUG)
		rep.mask |= NVIF_NOTIFY_CONN_V0_UNPLUG;
	अगर (line->mask & NVKM_I2C_PLUG)
		rep.mask |= NVIF_NOTIFY_CONN_V0_PLUG;

	nvkm_event_send(&disp->hpd, rep.mask, conn->index, &rep, माप(rep));
	वापस NVKM_NOTIFY_KEEP;
पूर्ण

अटल व्योम
nvkm_dp_fini(काष्ठा nvkm_outp *outp)
अणु
	काष्ठा nvkm_dp *dp = nvkm_dp(outp);
	nvkm_notअगरy_put(&dp->hpd);
	nvkm_dp_enable(dp, false);
पूर्ण

अटल व्योम
nvkm_dp_init(काष्ठा nvkm_outp *outp)
अणु
	काष्ठा nvkm_gpio *gpio = outp->disp->engine.subdev.device->gpio;
	काष्ठा nvkm_dp *dp = nvkm_dp(outp);

	nvkm_notअगरy_put(&dp->outp.conn->hpd);

	/* eDP panels need घातering on by us (अगर the VBIOS करोesn't शेष it
	 * to on) beक्रमe करोing any AUX channel transactions.  LVDS panel घातer
	 * is handled by the SOR itself, and not required क्रम LVDS DDC.
	 */
	अगर (dp->outp.conn->info.type == DCB_CONNECTOR_eDP) अणु
		पूर्णांक घातer = nvkm_gpio_get(gpio, 0, DCB_GPIO_PANEL_POWER, 0xff);
		अगर (घातer == 0)
			nvkm_gpio_set(gpio, 0, DCB_GPIO_PANEL_POWER, 0xff, 1);

		/* We delay here unconditionally, even अगर alपढ़ोy घातered,
		 * because some laptop panels having a signअगरicant resume
		 * delay beक्रमe the panel begins responding.
		 *
		 * This is likely a bit of a hack, but no better idea क्रम
		 * handling this at the moment.
		 */
		msleep(300);

		/* If the eDP panel can't be detected, we need to restore
		 * the panel घातer GPIO to aव्योम अवरोधing another output.
		 */
		अगर (!nvkm_dp_enable(dp, true) && घातer == 0)
			nvkm_gpio_set(gpio, 0, DCB_GPIO_PANEL_POWER, 0xff, 0);
	पूर्ण अन्यथा अणु
		nvkm_dp_enable(dp, true);
	पूर्ण

	nvkm_notअगरy_get(&dp->hpd);
पूर्ण

अटल व्योम *
nvkm_dp_dtor(काष्ठा nvkm_outp *outp)
अणु
	काष्ठा nvkm_dp *dp = nvkm_dp(outp);
	nvkm_notअगरy_fini(&dp->hpd);
	वापस dp;
पूर्ण

अटल स्थिर काष्ठा nvkm_outp_func
nvkm_dp_func = अणु
	.dtor = nvkm_dp_dtor,
	.init = nvkm_dp_init,
	.fini = nvkm_dp_fini,
	.acquire = nvkm_dp_acquire,
	.release = nvkm_dp_release,
	.disable = nvkm_dp_disable,
पूर्ण;

अटल पूर्णांक
nvkm_dp_ctor(काष्ठा nvkm_disp *disp, पूर्णांक index, काष्ठा dcb_output *dcbE,
	     काष्ठा nvkm_i2c_aux *aux, काष्ठा nvkm_dp *dp)
अणु
	काष्ठा nvkm_device *device = disp->engine.subdev.device;
	काष्ठा nvkm_bios *bios = device->bios;
	काष्ठा nvkm_i2c *i2c = device->i2c;
	u8  hdr, cnt, len;
	u32 data;
	पूर्णांक ret;

	ret = nvkm_outp_ctor(&nvkm_dp_func, disp, index, dcbE, &dp->outp);
	अगर (ret)
		वापस ret;

	dp->aux = aux;
	अगर (!dp->aux) अणु
		OUTP_ERR(&dp->outp, "no aux");
		वापस -EINVAL;
	पूर्ण

	/* bios data is not optional */
	data = nvbios_dpout_match(bios, dp->outp.info.hasht,
				  dp->outp.info.hashm, &dp->version,
				  &hdr, &cnt, &len, &dp->info);
	अगर (!data) अणु
		OUTP_ERR(&dp->outp, "no bios dp data");
		वापस -EINVAL;
	पूर्ण

	OUTP_DBG(&dp->outp, "bios dp %02x %02x %02x %02x",
		 dp->version, hdr, cnt, len);

	/* hotplug detect, replaces gpio-based mechanism with aux events */
	ret = nvkm_notअगरy_init(शून्य, &i2c->event, nvkm_dp_hpd, true,
			       &(काष्ठा nvkm_i2c_ntfy_req) अणु
				.mask = NVKM_I2C_PLUG | NVKM_I2C_UNPLUG |
					NVKM_I2C_IRQ,
				.port = dp->aux->id,
			       पूर्ण,
			       माप(काष्ठा nvkm_i2c_ntfy_req),
			       माप(काष्ठा nvkm_i2c_ntfy_rep),
			       &dp->hpd);
	अगर (ret) अणु
		OUTP_ERR(&dp->outp, "error monitoring aux hpd: %d", ret);
		वापस ret;
	पूर्ण

	mutex_init(&dp->mutex);
	atomic_set(&dp->lt.करोne, 0);
	वापस 0;
पूर्ण

पूर्णांक
nvkm_dp_new(काष्ठा nvkm_disp *disp, पूर्णांक index, काष्ठा dcb_output *dcbE,
	    काष्ठा nvkm_outp **poutp)
अणु
	काष्ठा nvkm_i2c *i2c = disp->engine.subdev.device->i2c;
	काष्ठा nvkm_i2c_aux *aux;
	काष्ठा nvkm_dp *dp;

	अगर (dcbE->location == 0)
		aux = nvkm_i2c_aux_find(i2c, NVKM_I2C_AUX_CCB(dcbE->i2c_index));
	अन्यथा
		aux = nvkm_i2c_aux_find(i2c, NVKM_I2C_AUX_EXT(dcbE->extdev));

	अगर (!(dp = kzalloc(माप(*dp), GFP_KERNEL)))
		वापस -ENOMEM;
	*poutp = &dp->outp;

	वापस nvkm_dp_ctor(disp, index, dcbE, aux, dp);
पूर्ण
