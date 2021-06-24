<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Freescale SSI ALSA SoC Digital Audio Interface (DAI) debugging functions
//
// Copyright 2014 Markus Pargmann <mpa@pengutronix.de>, Pengutronix
//
// Split from fsl_ssi.c

#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>

#समावेश "fsl_ssi.h"

व्योम fsl_ssi_dbg_isr(काष्ठा fsl_ssi_dbg *dbg, u32 sisr)
अणु
	अगर (sisr & SSI_SISR_RFRC)
		dbg->stats.rfrc++;

	अगर (sisr & SSI_SISR_TFRC)
		dbg->stats.tfrc++;

	अगर (sisr & SSI_SISR_CMDAU)
		dbg->stats.cmdau++;

	अगर (sisr & SSI_SISR_CMDDU)
		dbg->stats.cmddu++;

	अगर (sisr & SSI_SISR_RXT)
		dbg->stats.rxt++;

	अगर (sisr & SSI_SISR_RDR1)
		dbg->stats.rdr1++;

	अगर (sisr & SSI_SISR_RDR0)
		dbg->stats.rdr0++;

	अगर (sisr & SSI_SISR_TDE1)
		dbg->stats.tde1++;

	अगर (sisr & SSI_SISR_TDE0)
		dbg->stats.tde0++;

	अगर (sisr & SSI_SISR_ROE1)
		dbg->stats.roe1++;

	अगर (sisr & SSI_SISR_ROE0)
		dbg->stats.roe0++;

	अगर (sisr & SSI_SISR_TUE1)
		dbg->stats.tue1++;

	अगर (sisr & SSI_SISR_TUE0)
		dbg->stats.tue0++;

	अगर (sisr & SSI_SISR_TFS)
		dbg->stats.tfs++;

	अगर (sisr & SSI_SISR_RFS)
		dbg->stats.rfs++;

	अगर (sisr & SSI_SISR_TLS)
		dbg->stats.tls++;

	अगर (sisr & SSI_SISR_RLS)
		dbg->stats.rls++;

	अगर (sisr & SSI_SISR_RFF1)
		dbg->stats.rff1++;

	अगर (sisr & SSI_SISR_RFF0)
		dbg->stats.rff0++;

	अगर (sisr & SSI_SISR_TFE1)
		dbg->stats.tfe1++;

	अगर (sisr & SSI_SISR_TFE0)
		dbg->stats.tfe0++;
पूर्ण

/*
 * Show the statistics of a flag only अगर its पूर्णांकerrupt is enabled
 *
 * Compilers will optimize it to a no-op अगर the पूर्णांकerrupt is disabled
 */
#घोषणा SIER_SHOW(flag, name) \
	करो अणु \
		अगर (SSI_SIER_##flag) \
			seq_म_लिखो(s, #name "=%u\n", ssi_dbg->stats.name); \
	पूर्ण जबतक (0)


/*
 * Display the statistics क्रम the current SSI device
 *
 * To aव्योम confusion, only show those counts that are enabled
 */
अटल पूर्णांक fsl_ssi_stats_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा fsl_ssi_dbg *ssi_dbg = s->निजी;

	SIER_SHOW(RFRC_EN, rfrc);
	SIER_SHOW(TFRC_EN, tfrc);
	SIER_SHOW(CMDAU_EN, cmdau);
	SIER_SHOW(CMDDU_EN, cmddu);
	SIER_SHOW(RXT_EN, rxt);
	SIER_SHOW(RDR1_EN, rdr1);
	SIER_SHOW(RDR0_EN, rdr0);
	SIER_SHOW(TDE1_EN, tde1);
	SIER_SHOW(TDE0_EN, tde0);
	SIER_SHOW(ROE1_EN, roe1);
	SIER_SHOW(ROE0_EN, roe0);
	SIER_SHOW(TUE1_EN, tue1);
	SIER_SHOW(TUE0_EN, tue0);
	SIER_SHOW(TFS_EN, tfs);
	SIER_SHOW(RFS_EN, rfs);
	SIER_SHOW(TLS_EN, tls);
	SIER_SHOW(RLS_EN, rls);
	SIER_SHOW(RFF1_EN, rff1);
	SIER_SHOW(RFF0_EN, rff0);
	SIER_SHOW(TFE1_EN, tfe1);
	SIER_SHOW(TFE0_EN, tfe0);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(fsl_ssi_stats);

व्योम fsl_ssi_debugfs_create(काष्ठा fsl_ssi_dbg *ssi_dbg, काष्ठा device *dev)
अणु
	ssi_dbg->dbg_dir = debugfs_create_dir(dev_name(dev), शून्य);

	debugfs_create_file("stats", 0444, ssi_dbg->dbg_dir, ssi_dbg,
			    &fsl_ssi_stats_fops);
पूर्ण

व्योम fsl_ssi_debugfs_हटाओ(काष्ठा fsl_ssi_dbg *ssi_dbg)
अणु
	debugfs_हटाओ_recursive(ssi_dbg->dbg_dir);
पूर्ण
