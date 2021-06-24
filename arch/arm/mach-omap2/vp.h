<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP3/4 Voltage Processor (VP) काष्ठाure and macro definitions
 *
 * Copyright (C) 2007, 2010 Texas Instruments, Inc.
 * Rajendra Nayak <rnayak@ti.com>
 * Lesly A M <x0080970@ti.com>
 * Thara Gopinath <thara@ti.com>
 *
 * Copyright (C) 2008, 2011 Nokia Corporation
 * Kalle Jokiniemi
 * Paul Walmsley
 */
#अगर_अघोषित __ARCH_ARM_MACH_OMAP2_VP_H
#घोषणा __ARCH_ARM_MACH_OMAP2_VP_H

#समावेश <linux/kernel.h>

काष्ठा voltageकरोमुख्य;

/* XXX करोcument */
#घोषणा VP_IDLE_TIMEOUT		200
#घोषणा VP_TRANXDONE_TIMEOUT	300

/**
 * काष्ठा omap_vp_ops - per-VP operations
 * @check_txकरोne: check क्रम VP transaction करोne
 * @clear_txकरोne: clear VP transaction करोne status
 */
काष्ठा omap_vp_ops अणु
	u32 (*check_txकरोne)(u8 vp_id);
	व्योम (*clear_txकरोne)(u8 vp_id);
पूर्ण;

/**
 * काष्ठा omap_vp_common - रेजिस्टर data common to all VDDs
 * @vpconfig_erroroffset_mask: ERROROFFSET biपंचांगask in the PRM_VP*_CONFIG reg
 * @vpconfig_errorgain_mask: ERRORGAIN biपंचांगask in the PRM_VP*_CONFIG reg
 * @vpconfig_initvoltage_mask: INITVOLTAGE biपंचांगask in the PRM_VP*_CONFIG reg
 * @vpconfig_समयouten: TIMEOUT biपंचांगask in the PRM_VP*_CONFIG reg
 * @vpconfig_initvdd: INITVDD biपंचांगask in the PRM_VP*_CONFIG reg
 * @vpconfig_क्रमceupdate: FORCEUPDATE biपंचांगask in the PRM_VP*_CONFIG reg
 * @vpconfig_vpenable: VPENABLE biपंचांगask in the PRM_VP*_CONFIG reg
 * @vpconfig_erroroffset_shअगरt: ERROROFFSET field shअगरt in PRM_VP*_CONFIG reg
 * @vpconfig_errorgain_shअगरt: ERRORGAIN field shअगरt in PRM_VP*_CONFIG reg
 * @vpconfig_initvoltage_shअगरt: INITVOLTAGE field shअगरt in PRM_VP*_CONFIG reg
 * @vstepmin_stepmin_shअगरt: VSTEPMIN field shअगरt in the PRM_VP*_VSTEPMIN reg
 * @vstepmin_smpsरुकोसमयmin_shअगरt: SMPSWAITTIMEMIN field shअगरt in PRM_VP*_VSTEPMIN reg
 * @vstepmax_stepmax_shअगरt: VSTEPMAX field shअगरt in the PRM_VP*_VSTEPMAX reg
 * @vstepmax_smpsरुकोसमयmax_shअगरt: SMPSWAITTIMEMAX field shअगरt in PRM_VP*_VSTEPMAX reg
 * @vlimitto_vddmin_shअगरt: VDDMIN field shअगरt in PRM_VP*_VLIMITTO reg
 * @vlimitto_vddmax_shअगरt: VDDMAX field shअगरt in PRM_VP*_VLIMITTO reg
 * @vlimitto_समयout_shअगरt: TIMEOUT field shअगरt in PRM_VP*_VLIMITTO reg
 * @vpvoltage_mask: VPVOLTAGE field mask in PRM_VP*_VOLTAGE reg
 */
काष्ठा omap_vp_common अणु
	u32 vpconfig_erroroffset_mask;
	u32 vpconfig_errorgain_mask;
	u32 vpconfig_initvoltage_mask;
	u8 vpconfig_समयouten;
	u8 vpconfig_initvdd;
	u8 vpconfig_क्रमceupdate;
	u8 vpconfig_vpenable;
	u8 vstepmin_stepmin_shअगरt;
	u8 vstepmin_smpsरुकोसमयmin_shअगरt;
	u8 vstepmax_stepmax_shअगरt;
	u8 vstepmax_smpsरुकोसमयmax_shअगरt;
	u8 vlimitto_vddmin_shअगरt;
	u8 vlimitto_vddmax_shअगरt;
	u8 vlimitto_समयout_shअगरt;
	u8 vpvoltage_mask;

	स्थिर काष्ठा omap_vp_ops *ops;
पूर्ण;

/**
 * काष्ठा omap_vp_instance - VP रेजिस्टर offsets (per-VDD)
 * @common: poपूर्णांकer to काष्ठा omap_vp_common * क्रम this SoC
 * @vpconfig: PRM_VP*_CONFIG reg offset from PRM start
 * @vstepmin: PRM_VP*_VSTEPMIN reg offset from PRM start
 * @vlimitto: PRM_VP*_VLIMITTO reg offset from PRM start
 * @vstatus: PRM_VP*_VSTATUS reg offset from PRM start
 * @voltage: PRM_VP*_VOLTAGE reg offset from PRM start
 * @id: Unique identअगरier क्रम VP instance.
 * @enabled: flag to keep track of whether vp is enabled or not
 *
 * XXX vp_common is probably not needed since it is per-SoC
 */
काष्ठा omap_vp_instance अणु
	स्थिर काष्ठा omap_vp_common *common;
	u8 vpconfig;
	u8 vstepmin;
	u8 vstepmax;
	u8 vlimitto;
	u8 vstatus;
	u8 voltage;
	u8 id;
	bool enabled;
पूर्ण;

बाह्य काष्ठा omap_vp_instance omap3_vp_mpu;
बाह्य काष्ठा omap_vp_instance omap3_vp_core;

बाह्य काष्ठा omap_vp_instance omap4_vp_mpu;
बाह्य काष्ठा omap_vp_instance omap4_vp_iva;
बाह्य काष्ठा omap_vp_instance omap4_vp_core;

बाह्य काष्ठा omap_vp_param omap3_mpu_vp_data;
बाह्य काष्ठा omap_vp_param omap3_core_vp_data;

बाह्य काष्ठा omap_vp_param omap4_mpu_vp_data;
बाह्य काष्ठा omap_vp_param omap4_iva_vp_data;
बाह्य काष्ठा omap_vp_param omap4_core_vp_data;

व्योम omap_vp_init(काष्ठा voltageकरोमुख्य *voltdm);
व्योम omap_vp_enable(काष्ठा voltageकरोमुख्य *voltdm);
व्योम omap_vp_disable(काष्ठा voltageकरोमुख्य *voltdm);
पूर्णांक omap_vp_क्रमceupdate_scale(काष्ठा voltageकरोमुख्य *voltdm,
			      अचिन्हित दीर्घ target_volt);
पूर्णांक omap_vp_update_errorgain(काष्ठा voltageकरोमुख्य *voltdm,
			     अचिन्हित दीर्घ target_volt);

#पूर्ण_अगर
