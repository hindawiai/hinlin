<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2014 Free Electrons
 *
 *  Author: Boris BREZILLON <boris.brezillon@मुक्त-electrons.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>

#समावेश "internals.h"

#घोषणा ONFI_DYN_TIMING_MAX U16_MAX

/*
 * For non-ONFI chips we use the highest possible value क्रम tPROG and tBERS.
 * tR and tCCS will take the शेष values precised in the ONFI specअगरication
 * क्रम timing mode 0, respectively 200us and 500ns.
 *
 * These four values are tweaked to be more accurate in the हाल of ONFI chips.
 */
अटल स्थिर काष्ठा nand_पूर्णांकerface_config onfi_sdr_timings[] = अणु
	/* Mode 0 */
	अणु
		.type = न_अंकD_SDR_IFACE,
		.timings.mode = 0,
		.timings.sdr = अणु
			.tCCS_min = 500000,
			.tR_max = 200000000,
			.tPROG_max = 1000000ULL * ONFI_DYN_TIMING_MAX,
			.tBERS_max = 1000000ULL * ONFI_DYN_TIMING_MAX,
			.tADL_min = 400000,
			.tALH_min = 20000,
			.tALS_min = 50000,
			.tAR_min = 25000,
			.tCEA_max = 100000,
			.tCEH_min = 20000,
			.tCH_min = 20000,
			.tCHZ_max = 100000,
			.tCLH_min = 20000,
			.tCLR_min = 20000,
			.tCLS_min = 50000,
			.tCOH_min = 0,
			.tCS_min = 70000,
			.tDH_min = 20000,
			.tDS_min = 40000,
			.tFEAT_max = 1000000,
			.tIR_min = 10000,
			.tITC_max = 1000000,
			.tRC_min = 100000,
			.tREA_max = 40000,
			.tREH_min = 30000,
			.tRHOH_min = 0,
			.tRHW_min = 200000,
			.tRHZ_max = 200000,
			.tRLOH_min = 0,
			.tRP_min = 50000,
			.tRR_min = 40000,
			.tRST_max = 250000000000ULL,
			.tWB_max = 200000,
			.tWC_min = 100000,
			.tWH_min = 30000,
			.tWHR_min = 120000,
			.tWP_min = 50000,
			.tWW_min = 100000,
		पूर्ण,
	पूर्ण,
	/* Mode 1 */
	अणु
		.type = न_अंकD_SDR_IFACE,
		.timings.mode = 1,
		.timings.sdr = अणु
			.tCCS_min = 500000,
			.tR_max = 200000000,
			.tPROG_max = 1000000ULL * ONFI_DYN_TIMING_MAX,
			.tBERS_max = 1000000ULL * ONFI_DYN_TIMING_MAX,
			.tADL_min = 400000,
			.tALH_min = 10000,
			.tALS_min = 25000,
			.tAR_min = 10000,
			.tCEA_max = 45000,
			.tCEH_min = 20000,
			.tCH_min = 10000,
			.tCHZ_max = 50000,
			.tCLH_min = 10000,
			.tCLR_min = 10000,
			.tCLS_min = 25000,
			.tCOH_min = 15000,
			.tCS_min = 35000,
			.tDH_min = 10000,
			.tDS_min = 20000,
			.tFEAT_max = 1000000,
			.tIR_min = 0,
			.tITC_max = 1000000,
			.tRC_min = 50000,
			.tREA_max = 30000,
			.tREH_min = 15000,
			.tRHOH_min = 15000,
			.tRHW_min = 100000,
			.tRHZ_max = 100000,
			.tRLOH_min = 0,
			.tRP_min = 25000,
			.tRR_min = 20000,
			.tRST_max = 500000000,
			.tWB_max = 100000,
			.tWC_min = 45000,
			.tWH_min = 15000,
			.tWHR_min = 80000,
			.tWP_min = 25000,
			.tWW_min = 100000,
		पूर्ण,
	पूर्ण,
	/* Mode 2 */
	अणु
		.type = न_अंकD_SDR_IFACE,
		.timings.mode = 2,
		.timings.sdr = अणु
			.tCCS_min = 500000,
			.tR_max = 200000000,
			.tPROG_max = 1000000ULL * ONFI_DYN_TIMING_MAX,
			.tBERS_max = 1000000ULL * ONFI_DYN_TIMING_MAX,
			.tADL_min = 400000,
			.tALH_min = 10000,
			.tALS_min = 15000,
			.tAR_min = 10000,
			.tCEA_max = 30000,
			.tCEH_min = 20000,
			.tCH_min = 10000,
			.tCHZ_max = 50000,
			.tCLH_min = 10000,
			.tCLR_min = 10000,
			.tCLS_min = 15000,
			.tCOH_min = 15000,
			.tCS_min = 25000,
			.tDH_min = 5000,
			.tDS_min = 15000,
			.tFEAT_max = 1000000,
			.tIR_min = 0,
			.tITC_max = 1000000,
			.tRC_min = 35000,
			.tREA_max = 25000,
			.tREH_min = 15000,
			.tRHOH_min = 15000,
			.tRHW_min = 100000,
			.tRHZ_max = 100000,
			.tRLOH_min = 0,
			.tRR_min = 20000,
			.tRST_max = 500000000,
			.tWB_max = 100000,
			.tRP_min = 17000,
			.tWC_min = 35000,
			.tWH_min = 15000,
			.tWHR_min = 80000,
			.tWP_min = 17000,
			.tWW_min = 100000,
		पूर्ण,
	पूर्ण,
	/* Mode 3 */
	अणु
		.type = न_अंकD_SDR_IFACE,
		.timings.mode = 3,
		.timings.sdr = अणु
			.tCCS_min = 500000,
			.tR_max = 200000000,
			.tPROG_max = 1000000ULL * ONFI_DYN_TIMING_MAX,
			.tBERS_max = 1000000ULL * ONFI_DYN_TIMING_MAX,
			.tADL_min = 400000,
			.tALH_min = 5000,
			.tALS_min = 10000,
			.tAR_min = 10000,
			.tCEA_max = 25000,
			.tCEH_min = 20000,
			.tCH_min = 5000,
			.tCHZ_max = 50000,
			.tCLH_min = 5000,
			.tCLR_min = 10000,
			.tCLS_min = 10000,
			.tCOH_min = 15000,
			.tCS_min = 25000,
			.tDH_min = 5000,
			.tDS_min = 10000,
			.tFEAT_max = 1000000,
			.tIR_min = 0,
			.tITC_max = 1000000,
			.tRC_min = 30000,
			.tREA_max = 20000,
			.tREH_min = 10000,
			.tRHOH_min = 15000,
			.tRHW_min = 100000,
			.tRHZ_max = 100000,
			.tRLOH_min = 0,
			.tRP_min = 15000,
			.tRR_min = 20000,
			.tRST_max = 500000000,
			.tWB_max = 100000,
			.tWC_min = 30000,
			.tWH_min = 10000,
			.tWHR_min = 80000,
			.tWP_min = 15000,
			.tWW_min = 100000,
		पूर्ण,
	पूर्ण,
	/* Mode 4 */
	अणु
		.type = न_अंकD_SDR_IFACE,
		.timings.mode = 4,
		.timings.sdr = अणु
			.tCCS_min = 500000,
			.tR_max = 200000000,
			.tPROG_max = 1000000ULL * ONFI_DYN_TIMING_MAX,
			.tBERS_max = 1000000ULL * ONFI_DYN_TIMING_MAX,
			.tADL_min = 400000,
			.tALH_min = 5000,
			.tALS_min = 10000,
			.tAR_min = 10000,
			.tCEA_max = 25000,
			.tCEH_min = 20000,
			.tCH_min = 5000,
			.tCHZ_max = 30000,
			.tCLH_min = 5000,
			.tCLR_min = 10000,
			.tCLS_min = 10000,
			.tCOH_min = 15000,
			.tCS_min = 20000,
			.tDH_min = 5000,
			.tDS_min = 10000,
			.tFEAT_max = 1000000,
			.tIR_min = 0,
			.tITC_max = 1000000,
			.tRC_min = 25000,
			.tREA_max = 20000,
			.tREH_min = 10000,
			.tRHOH_min = 15000,
			.tRHW_min = 100000,
			.tRHZ_max = 100000,
			.tRLOH_min = 5000,
			.tRP_min = 12000,
			.tRR_min = 20000,
			.tRST_max = 500000000,
			.tWB_max = 100000,
			.tWC_min = 25000,
			.tWH_min = 10000,
			.tWHR_min = 80000,
			.tWP_min = 12000,
			.tWW_min = 100000,
		पूर्ण,
	पूर्ण,
	/* Mode 5 */
	अणु
		.type = न_अंकD_SDR_IFACE,
		.timings.mode = 5,
		.timings.sdr = अणु
			.tCCS_min = 500000,
			.tR_max = 200000000,
			.tPROG_max = 1000000ULL * ONFI_DYN_TIMING_MAX,
			.tBERS_max = 1000000ULL * ONFI_DYN_TIMING_MAX,
			.tADL_min = 400000,
			.tALH_min = 5000,
			.tALS_min = 10000,
			.tAR_min = 10000,
			.tCEA_max = 25000,
			.tCEH_min = 20000,
			.tCH_min = 5000,
			.tCHZ_max = 30000,
			.tCLH_min = 5000,
			.tCLR_min = 10000,
			.tCLS_min = 10000,
			.tCOH_min = 15000,
			.tCS_min = 15000,
			.tDH_min = 5000,
			.tDS_min = 7000,
			.tFEAT_max = 1000000,
			.tIR_min = 0,
			.tITC_max = 1000000,
			.tRC_min = 20000,
			.tREA_max = 16000,
			.tREH_min = 7000,
			.tRHOH_min = 15000,
			.tRHW_min = 100000,
			.tRHZ_max = 100000,
			.tRLOH_min = 5000,
			.tRP_min = 10000,
			.tRR_min = 20000,
			.tRST_max = 500000000,
			.tWB_max = 100000,
			.tWC_min = 20000,
			.tWH_min = 7000,
			.tWHR_min = 80000,
			.tWP_min = 10000,
			.tWW_min = 100000,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* All न_अंकD chips share the same reset data पूर्णांकerface: SDR mode 0 */
स्थिर काष्ठा nand_पूर्णांकerface_config *nand_get_reset_पूर्णांकerface_config(व्योम)
अणु
	वापस &onfi_sdr_timings[0];
पूर्ण

/**
 * onfi_find_बंदst_sdr_mode - Derive the बंदst ONFI SDR timing mode given a
 *                              set of timings
 * @spec_timings: the timings to challenge
 */
अचिन्हित पूर्णांक
onfi_find_बंदst_sdr_mode(स्थिर काष्ठा nand_sdr_timings *spec_timings)
अणु
	स्थिर काष्ठा nand_sdr_timings *onfi_timings;
	पूर्णांक mode;

	क्रम (mode = ARRAY_SIZE(onfi_sdr_timings) - 1; mode > 0; mode--) अणु
		onfi_timings = &onfi_sdr_timings[mode].timings.sdr;

		अगर (spec_timings->tCCS_min <= onfi_timings->tCCS_min &&
		    spec_timings->tADL_min <= onfi_timings->tADL_min &&
		    spec_timings->tALH_min <= onfi_timings->tALH_min &&
		    spec_timings->tALS_min <= onfi_timings->tALS_min &&
		    spec_timings->tAR_min <= onfi_timings->tAR_min &&
		    spec_timings->tCEH_min <= onfi_timings->tCEH_min &&
		    spec_timings->tCH_min <= onfi_timings->tCH_min &&
		    spec_timings->tCLH_min <= onfi_timings->tCLH_min &&
		    spec_timings->tCLR_min <= onfi_timings->tCLR_min &&
		    spec_timings->tCLS_min <= onfi_timings->tCLS_min &&
		    spec_timings->tCOH_min <= onfi_timings->tCOH_min &&
		    spec_timings->tCS_min <= onfi_timings->tCS_min &&
		    spec_timings->tDH_min <= onfi_timings->tDH_min &&
		    spec_timings->tDS_min <= onfi_timings->tDS_min &&
		    spec_timings->tIR_min <= onfi_timings->tIR_min &&
		    spec_timings->tRC_min <= onfi_timings->tRC_min &&
		    spec_timings->tREH_min <= onfi_timings->tREH_min &&
		    spec_timings->tRHOH_min <= onfi_timings->tRHOH_min &&
		    spec_timings->tRHW_min <= onfi_timings->tRHW_min &&
		    spec_timings->tRLOH_min <= onfi_timings->tRLOH_min &&
		    spec_timings->tRP_min <= onfi_timings->tRP_min &&
		    spec_timings->tRR_min <= onfi_timings->tRR_min &&
		    spec_timings->tWC_min <= onfi_timings->tWC_min &&
		    spec_timings->tWH_min <= onfi_timings->tWH_min &&
		    spec_timings->tWHR_min <= onfi_timings->tWHR_min &&
		    spec_timings->tWP_min <= onfi_timings->tWP_min &&
		    spec_timings->tWW_min <= onfi_timings->tWW_min)
			वापस mode;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * onfi_fill_पूर्णांकerface_config - Initialize an पूर्णांकerface config from a given
 *                              ONFI mode
 * @chip: The न_अंकD chip
 * @अगरace: The पूर्णांकerface configuration to fill
 * @type: The पूर्णांकerface type
 * @timing_mode: The ONFI timing mode
 */
व्योम onfi_fill_पूर्णांकerface_config(काष्ठा nand_chip *chip,
				काष्ठा nand_पूर्णांकerface_config *अगरace,
				क्रमागत nand_पूर्णांकerface_type type,
				अचिन्हित पूर्णांक timing_mode)
अणु
	काष्ठा onfi_params *onfi = chip->parameters.onfi;

	अगर (WARN_ON(type != न_अंकD_SDR_IFACE))
		वापस;

	अगर (WARN_ON(timing_mode >= ARRAY_SIZE(onfi_sdr_timings)))
		वापस;

	*अगरace = onfi_sdr_timings[timing_mode];

	/*
	 * Initialize timings that cannot be deduced from timing mode:
	 * tPROG, tBERS, tR and tCCS.
	 * These inक्रमmation are part of the ONFI parameter page.
	 */
	अगर (onfi) अणु
		काष्ठा nand_sdr_timings *timings = &अगरace->timings.sdr;

		/* microseconds -> picoseconds */
		timings->tPROG_max = 1000000ULL * onfi->tPROG;
		timings->tBERS_max = 1000000ULL * onfi->tBERS;
		timings->tR_max = 1000000ULL * onfi->tR;

		/* nanoseconds -> picoseconds */
		timings->tCCS_min = 1000UL * onfi->tCCS;
	पूर्ण
पूर्ण
