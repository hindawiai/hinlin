<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP GPMC Platक्रमm data
 *
 * Copyright (C) 2014 Texas Instruments, Inc. - https://www.ti.com
 *	Roger Quadros <rogerq@ti.com>
 */

#अगर_अघोषित _GPMC_OMAP_H_
#घोषणा _GPMC_OMAP_H_

/* Maximum Number of Chip Selects */
#घोषणा GPMC_CS_NUM		8

/* bool type समय settings */
काष्ठा gpmc_bool_timings अणु
	bool cycle2cycledअगरfcsen;
	bool cycle2cyclesamecsen;
	bool we_extra_delay;
	bool oe_extra_delay;
	bool adv_extra_delay;
	bool cs_extra_delay;
	bool समय_para_granularity;
पूर्ण;

/*
 * Note that all values in this काष्ठा are in nanoseconds except sync_clk
 * (which is in picoseconds), जबतक the रेजिस्टर values are in gpmc_fck cycles.
 */
काष्ठा gpmc_timings अणु
	/* Minimum घड़ी period क्रम synchronous mode (in picoseconds) */
	u32 sync_clk;

	/* Chip-select संकेत timings corresponding to GPMC_CS_CONFIG2 */
	u32 cs_on;		/* Assertion समय */
	u32 cs_rd_off;		/* Read deनिश्चितion समय */
	u32 cs_wr_off;		/* Write deनिश्चितion समय */

	/* ADV संकेत timings corresponding to GPMC_CONFIG3 */
	u32 adv_on;		/* Assertion समय */
	u32 adv_rd_off;		/* Read deनिश्चितion समय */
	u32 adv_wr_off;		/* Write deनिश्चितion समय */
	u32 adv_aad_mux_on;	/* ADV निश्चितion समय क्रम AAD */
	u32 adv_aad_mux_rd_off;	/* ADV पढ़ो deनिश्चितion समय क्रम AAD */
	u32 adv_aad_mux_wr_off;	/* ADV ग_लिखो deनिश्चितion समय क्रम AAD */

	/* WE संकेतs timings corresponding to GPMC_CONFIG4 */
	u32 we_on;		/* WE निश्चितion समय */
	u32 we_off;		/* WE deनिश्चितion समय */

	/* OE संकेतs timings corresponding to GPMC_CONFIG4 */
	u32 oe_on;		/* OE निश्चितion समय */
	u32 oe_off;		/* OE deनिश्चितion समय */
	u32 oe_aad_mux_on;	/* OE निश्चितion समय क्रम AAD */
	u32 oe_aad_mux_off;	/* OE deनिश्चितion समय क्रम AAD */

	/* Access समय and cycle समय timings corresponding to GPMC_CONFIG5 */
	u32 page_burst_access;	/* Multiple access word delay */
	u32 access;		/* Start-cycle to first data valid delay */
	u32 rd_cycle;		/* Total पढ़ो cycle समय */
	u32 wr_cycle;		/* Total ग_लिखो cycle समय */

	u32 bus_turnaround;
	u32 cycle2cycle_delay;

	u32 रुको_monitoring;
	u32 clk_activation;

	/* The following are only on OMAP3430 */
	u32 wr_access;		/* WRACCESSTIME */
	u32 wr_data_mux_bus;	/* WRDATAONADMUXBUS */

	काष्ठा gpmc_bool_timings bool_timings;
पूर्ण;

/* Device timings in picoseconds */
काष्ठा gpmc_device_timings अणु
	u32 t_ceasu;	/* address setup to CS valid */
	u32 t_avdasu;	/* address setup to ADV valid */
	/* XXX: try to combine t_avdp_r & t_avdp_w. Issue is
	 * of tusb using these timings even क्रम sync whilst
	 * ideally क्रम adv_rd/(wr)_off it should have considered
	 * t_avdh instead. This indirectly necessitates r/w
	 * variations of t_avdp as it is possible to have one
	 * sync & other async
	 */
	u32 t_avdp_r;	/* ADV low समय (what about t_cer ?) */
	u32 t_avdp_w;
	u32 t_aavdh;	/* address hold समय */
	u32 t_oeasu;	/* address setup to OE valid */
	u32 t_aa;	/* access समय from ADV निश्चितion */
	u32 t_iaa;	/* initial access समय */
	u32 t_oe;	/* access समय from OE निश्चितion */
	u32 t_ce;	/* access समय from CS asertion */
	u32 t_rd_cycle;	/* पढ़ो cycle समय */
	u32 t_cez_r;	/* पढ़ो CS deनिश्चितion to high Z */
	u32 t_cez_w;	/* ग_लिखो CS deनिश्चितion to high Z */
	u32 t_oez;	/* OE deनिश्चितion to high Z */
	u32 t_weasu;	/* address setup to WE valid */
	u32 t_wpl;	/* ग_लिखो निश्चितion समय */
	u32 t_wph;	/* ग_लिखो deनिश्चितion समय */
	u32 t_wr_cycle;	/* ग_लिखो cycle समय */

	u32 clk;
	u32 t_bacc;	/* burst access valid घड़ी to output delay */
	u32 t_ces;	/* CS setup समय to clk */
	u32 t_avds;	/* ADV setup समय to clk */
	u32 t_avdh;	/* ADV hold समय from clk */
	u32 t_ach;	/* address hold समय from clk */
	u32 t_rdyo;	/* clk to पढ़ोy valid */

	u32 t_ce_rdyz;	/* XXX: description ?, or use t_cez instead */
	u32 t_ce_avd;	/* CS on to ADV on delay */

	/* XXX: check the possibility of combining
	 * cyc_aavhd_oe & cyc_aavdh_we
	 */
	u8 cyc_aavdh_oe;/* पढ़ो address hold समय in cycles */
	u8 cyc_aavdh_we;/* ग_लिखो address hold समय in cycles */
	u8 cyc_oe;	/* access समय from OE निश्चितion in cycles */
	u8 cyc_wpl;	/* ग_लिखो deनिश्चितion समय in cycles */
	u32 cyc_iaa;	/* initial access समय in cycles */

	/* extra delays */
	bool ce_xdelay;
	bool avd_xdelay;
	bool oe_xdelay;
	bool we_xdelay;
पूर्ण;

#घोषणा GPMC_BURST_4			4	/* 4 word burst */
#घोषणा GPMC_BURST_8			8	/* 8 word burst */
#घोषणा GPMC_BURST_16			16	/* 16 word burst */
#घोषणा GPMC_DEVWIDTH_8BIT		1	/* 8-bit device width */
#घोषणा GPMC_DEVWIDTH_16BIT		2	/* 16-bit device width */
#घोषणा GPMC_MUX_AAD			1	/* Addr-Addr-Data multiplex */
#घोषणा GPMC_MUX_AD			2	/* Addr-Data multiplex */

काष्ठा gpmc_settings अणु
	bool burst_wrap;	/* enables wrap bursting */
	bool burst_पढ़ो;	/* enables पढ़ो page/burst mode */
	bool burst_ग_लिखो;	/* enables ग_लिखो page/burst mode */
	bool device_nand;	/* device is न_अंकD */
	bool sync_पढ़ो;		/* enables synchronous पढ़ोs */
	bool sync_ग_लिखो;	/* enables synchronous ग_लिखोs */
	bool रुको_on_पढ़ो;	/* monitor रुको on पढ़ोs */
	bool रुको_on_ग_लिखो;	/* monitor रुको on ग_लिखोs */
	u32 burst_len;		/* page/burst length */
	u32 device_width;	/* device bus width (8 or 16 bit) */
	u32 mux_add_data;	/* multiplex address & data */
	u32 रुको_pin;		/* रुको-pin to be used */
पूर्ण;

/* Data क्रम each chip select */
काष्ठा gpmc_omap_cs_data अणु
	bool valid;			/* data is valid */
	bool is_nand;			/* device within this CS is न_अंकD */
	काष्ठा gpmc_settings *settings;
	काष्ठा gpmc_device_timings *device_timings;
	काष्ठा gpmc_timings *gpmc_timings;
	काष्ठा platक्रमm_device *pdev;	/* device within this CS region */
	अचिन्हित पूर्णांक pdata_size;
पूर्ण;

काष्ठा gpmc_omap_platक्रमm_data अणु
	काष्ठा gpmc_omap_cs_data cs[GPMC_CS_NUM];
पूर्ण;

#पूर्ण_अगर /* _GPMC_OMAP_H */
