<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2009 Texas Instruments Inc
 *
 * vpss - video processing subप्रणाली module header file.
 *
 * Include this header file अगर a driver needs to configure vpss प्रणाली
 * module. It exports a set of library functions  क्रम video drivers to
 * configure vpss प्रणाली module functions such as घड़ी enable/disable,
 * vpss पूर्णांकerrupt mux to arm, and other common vpss प्रणाली module
 * functions.
 */
#अगर_अघोषित _VPSS_H
#घोषणा _VPSS_H

/* selector क्रम ccdc input selection on DM355 */
क्रमागत vpss_ccdc_source_sel अणु
	VPSS_CCDCIN,
	VPSS_HSSIIN,
	VPSS_PGLPBK,	/* क्रम DM365 only */
	VPSS_CCDCPG	/* क्रम DM365 only */
पूर्ण;

काष्ठा vpss_sync_pol अणु
	अचिन्हित पूर्णांक ccdpg_hdpol:1;
	अचिन्हित पूर्णांक ccdpg_vdpol:1;
पूर्ण;

काष्ठा vpss_pg_frame_size अणु
	लघु hlpfr;
	लघु pplen;
पूर्ण;

/* Used क्रम enable/disable VPSS Clock */
क्रमागत vpss_घड़ी_sel अणु
	/* DM355/DM365 */
	VPSS_CCDC_CLOCK,
	VPSS_IPIPE_CLOCK,
	VPSS_H3A_CLOCK,
	VPSS_CFALD_CLOCK,
	/*
	 * When using VPSS_VENC_CLOCK_SEL in vpss_enable_घड़ी() api
	 * following applies:-
	 * en = 0 selects ENC_CLK
	 * en = 1 selects ENC_CLK/2
	 */
	VPSS_VENC_CLOCK_SEL,
	VPSS_VPBE_CLOCK,
	/* DM365 only घड़ीs */
	VPSS_IPIPEIF_CLOCK,
	VPSS_RSZ_CLOCK,
	VPSS_BL_CLOCK,
	/*
	 * When using VPSS_PCLK_INTERNAL in vpss_enable_घड़ी() api
	 * following applies:-
	 * en = 0 disable पूर्णांकernal PCLK
	 * en = 1 enables पूर्णांकernal PCLK
	 */
	VPSS_PCLK_INTERNAL,
	/*
	 * When using VPSS_PSYNC_CLOCK_SEL in vpss_enable_घड़ी() api
	 * following applies:-
	 * en = 0 enables MMR घड़ी
	 * en = 1 enables VPSS घड़ी
	 */
	VPSS_PSYNC_CLOCK_SEL,
	VPSS_LDC_CLOCK_SEL,
	VPSS_OSD_CLOCK_SEL,
	VPSS_FDIF_CLOCK,
	VPSS_LDC_CLOCK
पूर्ण;

/* select input to ccdc on dm355 */
पूर्णांक vpss_select_ccdc_source(क्रमागत vpss_ccdc_source_sel src_sel);
/* enable/disable a vpss घड़ी, 0 - success, -1 - failure */
पूर्णांक vpss_enable_घड़ी(क्रमागत vpss_घड़ी_sel घड़ी_sel, पूर्णांक en);
/* set sync polarity, only क्रम DM365*/
व्योम dm365_vpss_set_sync_pol(काष्ठा vpss_sync_pol);
/* set the PG_FRAME_SIZE रेजिस्टर, only क्रम DM365 */
व्योम dm365_vpss_set_pg_frame_size(काष्ठा vpss_pg_frame_size);

/* wbl reset क्रम dm644x */
क्रमागत vpss_wbl_sel अणु
	VPSS_PCR_AEW_WBL_0 = 16,
	VPSS_PCR_AF_WBL_0,
	VPSS_PCR_RSZ4_WBL_0,
	VPSS_PCR_RSZ3_WBL_0,
	VPSS_PCR_RSZ2_WBL_0,
	VPSS_PCR_RSZ1_WBL_0,
	VPSS_PCR_PREV_WBL_0,
	VPSS_PCR_CCDC_WBL_O,
पूर्ण;
/* clear wbl overflow flag क्रम DM6446 */
पूर्णांक vpss_clear_wbl_overflow(क्रमागत vpss_wbl_sel wbl_sel);

/* set sync polarity*/
व्योम vpss_set_sync_pol(काष्ठा vpss_sync_pol sync);
/* set the PG_FRAME_SIZE रेजिस्टर */
व्योम vpss_set_pg_frame_size(काष्ठा vpss_pg_frame_size frame_size);
/*
 * vpss_check_and_clear_पूर्णांकerrupt - check and clear पूर्णांकerrupt
 * @irq - common क्रमागतerator क्रम IRQ
 *
 * Following वापस values used:-
 * 0 - पूर्णांकerrupt occurred and cleared
 * 1 - पूर्णांकerrupt not occurred
 * 2 - पूर्णांकerrupt status not available
 */
पूर्णांक vpss_dma_complete_पूर्णांकerrupt(व्योम);

#पूर्ण_अगर
