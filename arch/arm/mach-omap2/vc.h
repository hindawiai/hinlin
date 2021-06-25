<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP3/4 Voltage Controller (VC) काष्ठाure and macro definitions
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
#अगर_अघोषित __ARCH_ARM_MACH_OMAP2_VC_H
#घोषणा __ARCH_ARM_MACH_OMAP2_VC_H

#समावेश <linux/kernel.h>

काष्ठा voltageकरोमुख्य;

/**
 * काष्ठा omap_vc_common - per-VC रेजिस्टर/bitfield data
 * @cmd_on_mask: ON biपंचांगask in PRM_VC_CMD_VAL* रेजिस्टर
 * @valid: VALID biपंचांगask in PRM_VC_BYPASS_VAL रेजिस्टर
 * @bypass_val_reg: Offset of PRM_VC_BYPASS_VAL reg from PRM start
 * @data_shअगरt: DATA field shअगरt in PRM_VC_BYPASS_VAL रेजिस्टर
 * @slaveaddr_shअगरt: SLAVEADDR field shअगरt in PRM_VC_BYPASS_VAL रेजिस्टर
 * @regaddr_shअगरt: REGADDR field shअगरt in PRM_VC_BYPASS_VAL रेजिस्टर
 * @cmd_on_shअगरt: ON field shअगरt in PRM_VC_CMD_VAL_* रेजिस्टर
 * @cmd_onlp_shअगरt: ONLP field shअगरt in PRM_VC_CMD_VAL_* रेजिस्टर
 * @cmd_ret_shअगरt: RET field shअगरt in PRM_VC_CMD_VAL_* रेजिस्टर
 * @cmd_off_shअगरt: OFF field shअगरt in PRM_VC_CMD_VAL_* रेजिस्टर
 * @i2c_cfg_reg: I2C configuration रेजिस्टर offset
 * @i2c_cfg_clear_mask: high-speed mode bit clear mask in I2C config रेजिस्टर
 * @i2c_cfg_hsen_mask: high-speed mode bit field mask in I2C config रेजिस्टर
 * @i2c_mcode_mask: MCODE field mask क्रम I2C config रेजिस्टर
 *
 * XXX One of cmd_on_mask and cmd_on_shअगरt are not needed
 * XXX VALID should probably be a shअगरt, not a mask
 */
काष्ठा omap_vc_common अणु
	u32 cmd_on_mask;
	u32 valid;
	u8 bypass_val_reg;
	u8 data_shअगरt;
	u8 slaveaddr_shअगरt;
	u8 regaddr_shअगरt;
	u8 cmd_on_shअगरt;
	u8 cmd_onlp_shअगरt;
	u8 cmd_ret_shअगरt;
	u8 cmd_off_shअगरt;
	u8 i2c_cfg_reg;
	u8 i2c_cfg_clear_mask;
	u8 i2c_cfg_hsen_mask;
	u8 i2c_mcode_mask;
पूर्ण;

/* omap_vc_channel.flags values */
#घोषणा OMAP_VC_CHANNEL_DEFAULT BIT(0)
#घोषणा OMAP_VC_CHANNEL_CFG_MUTANT BIT(1)

/**
 * काष्ठा omap_vc_channel - VC per-instance data
 * @i2c_slave_addr: I2C slave address of PMIC क्रम this VC channel
 * @volt_reg_addr: voltage configuration रेजिस्टर address
 * @cmd_reg_addr: command configuration रेजिस्टर address
 * @setup_समय: setup समय (in sys_clk cycles) of regulator क्रम this channel
 * @cfg_channel: current value of VC channel configuration रेजिस्टर
 * @i2c_high_speed: whether or not to use I2C high-speed mode
 *
 * @common: poपूर्णांकer to VC common data क्रम this platक्रमm
 * @smps_sa_mask: i2c slave address biपंचांगask in the PRM_VC_SMPS_SA रेजिस्टर
 * @smps_volra_mask: VOLRA* biपंचांगask in the PRM_VC_VOL_RA रेजिस्टर
 * @smps_cmdra_mask: CMDRA* biपंचांगask in the PRM_VC_CMD_RA रेजिस्टर
 * @cmdval_reg: रेजिस्टर क्रम on/ret/off voltage level values क्रम this channel
 * @smps_sa_reg: Offset of PRM_VC_SMPS_SA reg from PRM start
 * @smps_volra_reg: Offset of PRM_VC_SMPS_VOL_RA reg from PRM start
 * @smps_cmdra_reg: Offset of PRM_VC_SMPS_CMD_RA reg from PRM start
 * @cfg_channel_reg: VC channel configuration रेजिस्टर
 * @cfg_channel_sa_shअगरt: bit shअगरt क्रम slave address cfg_channel रेजिस्टर
 * @flags: VC channel-specअगरic flags (optional)
 */
काष्ठा omap_vc_channel अणु
	/* channel state */
	u16 i2c_slave_addr;
	u16 volt_reg_addr;
	u16 cmd_reg_addr;
	u8 cfg_channel;
	bool i2c_high_speed;

	/* रेजिस्टर access data */
	स्थिर काष्ठा omap_vc_common *common;
	u32 smps_sa_mask;
	u32 smps_volra_mask;
	u32 smps_cmdra_mask;
	u8 cmdval_reg;
	u8 smps_sa_reg;
	u8 smps_volra_reg;
	u8 smps_cmdra_reg;
	u8 cfg_channel_reg;
	u8 cfg_channel_sa_shअगरt;
	u8 flags;
पूर्ण;

बाह्य काष्ठा omap_vc_channel omap3_vc_mpu;
बाह्य काष्ठा omap_vc_channel omap3_vc_core;

बाह्य काष्ठा omap_vc_channel omap4_vc_mpu;
बाह्य काष्ठा omap_vc_channel omap4_vc_iva;
बाह्य काष्ठा omap_vc_channel omap4_vc_core;

बाह्य काष्ठा omap_vc_param omap3_mpu_vc_data;
बाह्य काष्ठा omap_vc_param omap3_core_vc_data;

बाह्य काष्ठा omap_vc_param omap4_mpu_vc_data;
बाह्य काष्ठा omap_vc_param omap4_iva_vc_data;
बाह्य काष्ठा omap_vc_param omap4_core_vc_data;

व्योम omap3_vc_set_pmic_संकेतing(पूर्णांक core_next_state);
व्योम omap4_vc_set_pmic_संकेतing(पूर्णांक core_next_state);

व्योम omap_vc_init_channel(काष्ठा voltageकरोमुख्य *voltdm);
पूर्णांक omap_vc_pre_scale(काष्ठा voltageकरोमुख्य *voltdm,
		      अचिन्हित दीर्घ target_volt,
		      u8 *target_vsel, u8 *current_vsel);
व्योम omap_vc_post_scale(काष्ठा voltageकरोमुख्य *voltdm,
			अचिन्हित दीर्घ target_volt,
			u8 target_vsel, u8 current_vsel);
पूर्णांक omap_vc_bypass_scale(काष्ठा voltageकरोमुख्य *voltdm,
			 अचिन्हित दीर्घ target_volt);

#पूर्ण_अगर

