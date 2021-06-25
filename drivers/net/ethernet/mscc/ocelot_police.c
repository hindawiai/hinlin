<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/* Microsemi Ocelot Switch driver
 *
 * Copyright (c) 2019 Microsemi Corporation
 */

#समावेश <soc/mscc/ocelot.h>
#समावेश "ocelot_police.h"

/* Types क्रम ANA:POL[0-192]:POL_MODE_CFG.FRM_MODE */
#घोषणा POL_MODE_LINERATE   0 /* Incl IPG. Unit: 33 1/3 kbps, 4096 bytes */
#घोषणा POL_MODE_DATARATE   1 /* Excl IPG. Unit: 33 1/3 kbps, 4096 bytes  */
#घोषणा POL_MODE_FRMRATE_HI 2 /* Unit: 33 1/3 fps, 32.8 frames */
#घोषणा POL_MODE_FRMRATE_LO 3 /* Unit: 1/3 fps, 0.3 frames */

/* Policer indexes */
#घोषणा POL_IX_PORT    0    /* 0-11    : Port policers */
#घोषणा POL_IX_QUEUE   32   /* 32-127  : Queue policers  */

/* Default policer order */
#घोषणा POL_ORDER 0x1d3 /* Ocelot policer order: Serial (QoS -> Port -> VCAP) */

पूर्णांक qos_policer_conf_set(काष्ठा ocelot *ocelot, पूर्णांक port, u32 pol_ix,
			 काष्ठा qos_policer_conf *conf)
अणु
	u32 cf = 0, cir_ena = 0, frm_mode = POL_MODE_LINERATE;
	u32 cir = 0, cbs = 0, pir = 0, pbs = 0;
	bool cir_discard = 0, pir_discard = 0;
	u32 pbs_max = 0, cbs_max = 0;
	u8 ipg = 20;
	u32 value;

	pir = conf->pir;
	pbs = conf->pbs;

	चयन (conf->mode) अणु
	हाल MSCC_QOS_RATE_MODE_LINE:
	हाल MSCC_QOS_RATE_MODE_DATA:
		अगर (conf->mode == MSCC_QOS_RATE_MODE_LINE) अणु
			frm_mode = POL_MODE_LINERATE;
			ipg = min_t(u8, GENMASK(4, 0), conf->ipg);
		पूर्ण अन्यथा अणु
			frm_mode = POL_MODE_DATARATE;
		पूर्ण
		अगर (conf->dlb) अणु
			cir_ena = 1;
			cir = conf->cir;
			cbs = conf->cbs;
			अगर (cir == 0 && cbs == 0) अणु
				/* Discard cir frames */
				cir_discard = 1;
			पूर्ण अन्यथा अणु
				cir = DIV_ROUND_UP(cir, 100);
				cir *= 3; /* 33 1/3 kbps */
				cbs = DIV_ROUND_UP(cbs, 4096);
				cbs = (cbs ? cbs : 1); /* No zero burst size */
				cbs_max = 60; /* Limit burst size */
				cf = conf->cf;
				अगर (cf)
					pir += conf->cir;
			पूर्ण
		पूर्ण
		अगर (pir == 0 && pbs == 0) अणु
			/* Discard PIR frames */
			pir_discard = 1;
		पूर्ण अन्यथा अणु
			pir = DIV_ROUND_UP(pir, 100);
			pir *= 3;  /* 33 1/3 kbps */
			pbs = DIV_ROUND_UP(pbs, 4096);
			pbs = (pbs ? pbs : 1); /* No zero burst size */
			pbs_max = 60; /* Limit burst size */
		पूर्ण
		अवरोध;
	हाल MSCC_QOS_RATE_MODE_FRAME:
		अगर (pir >= 100) अणु
			frm_mode = POL_MODE_FRMRATE_HI;
			pir = DIV_ROUND_UP(pir, 100);
			pir *= 3;  /* 33 1/3 fps */
			pbs = (pbs * 10) / 328; /* 32.8 frames */
			pbs = (pbs ? pbs : 1); /* No zero burst size */
			pbs_max = GENMASK(6, 0); /* Limit burst size */
		पूर्ण अन्यथा अणु
			frm_mode = POL_MODE_FRMRATE_LO;
			अगर (pir == 0 && pbs == 0) अणु
				/* Discard all frames */
				pir_discard = 1;
				cir_discard = 1;
			पूर्ण अन्यथा अणु
				pir *= 3; /* 1/3 fps */
				pbs = (pbs * 10) / 3; /* 0.3 frames */
				pbs = (pbs ? pbs : 1); /* No zero burst size */
				pbs_max = 61; /* Limit burst size */
			पूर्ण
		पूर्ण
		अवरोध;
	शेष: /* MSCC_QOS_RATE_MODE_DISABLED */
		/* Disable policer using maximum rate and zero burst */
		pir = GENMASK(15, 0);
		pbs = 0;
		अवरोध;
	पूर्ण

	/* Check limits */
	अगर (pir > GENMASK(15, 0)) अणु
		dev_err(ocelot->dev, "Invalid pir for port %d: %u (max %lu)\n",
			port, pir, GENMASK(15, 0));
		वापस -EINVAL;
	पूर्ण

	अगर (cir > GENMASK(15, 0)) अणु
		dev_err(ocelot->dev, "Invalid cir for port %d: %u (max %lu)\n",
			port, cir, GENMASK(15, 0));
		वापस -EINVAL;
	पूर्ण

	अगर (pbs > pbs_max) अणु
		dev_err(ocelot->dev, "Invalid pbs for port %d: %u (max %u)\n",
			port, pbs, pbs_max);
		वापस -EINVAL;
	पूर्ण

	अगर (cbs > cbs_max) अणु
		dev_err(ocelot->dev, "Invalid cbs for port %d: %u (max %u)\n",
			port, cbs, cbs_max);
		वापस -EINVAL;
	पूर्ण

	value = (ANA_POL_MODE_CFG_IPG_SIZE(ipg) |
		 ANA_POL_MODE_CFG_FRM_MODE(frm_mode) |
		 (cf ? ANA_POL_MODE_CFG_DLB_COUPLED : 0) |
		 (cir_ena ? ANA_POL_MODE_CFG_CIR_ENA : 0) |
		 ANA_POL_MODE_CFG_OVERSHOOT_ENA);

	ocelot_ग_लिखो_gix(ocelot, value, ANA_POL_MODE_CFG, pol_ix);

	ocelot_ग_लिखो_gix(ocelot,
			 ANA_POL_PIR_CFG_PIR_RATE(pir) |
			 ANA_POL_PIR_CFG_PIR_BURST(pbs),
			 ANA_POL_PIR_CFG, pol_ix);

	ocelot_ग_लिखो_gix(ocelot,
			 (pir_discard ? GENMASK(22, 0) : 0),
			 ANA_POL_PIR_STATE, pol_ix);

	ocelot_ग_लिखो_gix(ocelot,
			 ANA_POL_CIR_CFG_CIR_RATE(cir) |
			 ANA_POL_CIR_CFG_CIR_BURST(cbs),
			 ANA_POL_CIR_CFG, pol_ix);

	ocelot_ग_लिखो_gix(ocelot,
			 (cir_discard ? GENMASK(22, 0) : 0),
			 ANA_POL_CIR_STATE, pol_ix);

	वापस 0;
पूर्ण

पूर्णांक ocelot_port_policer_add(काष्ठा ocelot *ocelot, पूर्णांक port,
			    काष्ठा ocelot_policer *pol)
अणु
	काष्ठा qos_policer_conf pp = अणु 0 पूर्ण;
	पूर्णांक err;

	अगर (!pol)
		वापस -EINVAL;

	pp.mode = MSCC_QOS_RATE_MODE_DATA;
	pp.pir = pol->rate;
	pp.pbs = pol->burst;

	dev_dbg(ocelot->dev, "%s: port %u pir %u kbps, pbs %u bytes\n",
		__func__, port, pp.pir, pp.pbs);

	err = qos_policer_conf_set(ocelot, port, POL_IX_PORT + port, &pp);
	अगर (err)
		वापस err;

	ocelot_rmw_gix(ocelot,
		       ANA_PORT_POL_CFG_PORT_POL_ENA |
		       ANA_PORT_POL_CFG_POL_ORDER(POL_ORDER),
		       ANA_PORT_POL_CFG_PORT_POL_ENA |
		       ANA_PORT_POL_CFG_POL_ORDER_M,
		       ANA_PORT_POL_CFG, port);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_port_policer_add);

पूर्णांक ocelot_port_policer_del(काष्ठा ocelot *ocelot, पूर्णांक port)
अणु
	काष्ठा qos_policer_conf pp = अणु 0 पूर्ण;
	पूर्णांक err;

	dev_dbg(ocelot->dev, "%s: port %u\n", __func__, port);

	pp.mode = MSCC_QOS_RATE_MODE_DISABLED;

	err = qos_policer_conf_set(ocelot, port, POL_IX_PORT + port, &pp);
	अगर (err)
		वापस err;

	ocelot_rmw_gix(ocelot,
		       ANA_PORT_POL_CFG_POL_ORDER(POL_ORDER),
		       ANA_PORT_POL_CFG_PORT_POL_ENA |
		       ANA_PORT_POL_CFG_POL_ORDER_M,
		       ANA_PORT_POL_CFG, port);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_port_policer_del);
