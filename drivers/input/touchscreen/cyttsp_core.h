<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Header file क्रम:
 * Cypress TrueTouch(TM) Standard Product (TTSP) touchscreen drivers.
 * For use with Cypress Txx3xx parts.
 * Supported parts include:
 * CY8CTST341
 * CY8CTMA340
 *
 * Copyright (C) 2009, 2010, 2011 Cypress Semiconductor, Inc.
 * Copyright (C) 2012 Javier Martinez Canillas <javier@करोजबतक0.org>
 *
 * Contact Cypress Semiconductor at www.cypress.com <kev@cypress.com>
 */


#अगर_अघोषित __CYTTSP_CORE_H__
#घोषणा __CYTTSP_CORE_H__

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/input/cyttsp.h>

#घोषणा CY_NUM_RETRY		16 /* max number of retries क्रम पढ़ो ops */

काष्ठा cyttsp_tch अणु
	__be16 x, y;
	u8 z;
पूर्ण __packed;

/* TrueTouch Standard Product Gen3 पूर्णांकerface definition */
काष्ठा cyttsp_xydata अणु
	u8 hst_mode;
	u8 tt_mode;
	u8 tt_stat;
	काष्ठा cyttsp_tch tch1;
	u8 touch12_id;
	काष्ठा cyttsp_tch tch2;
	u8 gest_cnt;
	u8 gest_id;
	काष्ठा cyttsp_tch tch3;
	u8 touch34_id;
	काष्ठा cyttsp_tch tch4;
	u8 tt_undef[3];
	u8 act_dist;
	u8 tt_reserved;
पूर्ण __packed;


/* TTSP System Inक्रमmation पूर्णांकerface definition */
काष्ठा cyttsp_sysinfo_data अणु
	u8 hst_mode;
	u8 mfg_stat;
	u8 mfg_cmd;
	u8 cid[3];
	u8 tt_undef1;
	u8 uid[8];
	u8 bl_verh;
	u8 bl_verl;
	u8 tts_verh;
	u8 tts_verl;
	u8 app_idh;
	u8 app_idl;
	u8 app_verh;
	u8 app_verl;
	u8 tt_undef[5];
	u8 scn_typ;
	u8 act_पूर्णांकrvl;
	u8 tch_पंचांगout;
	u8 lp_पूर्णांकrvl;
पूर्ण;

/* TTSP Bootloader Register Map पूर्णांकerface definition */
#घोषणा CY_BL_CHKSUM_OK 0x01
काष्ठा cyttsp_bootloader_data अणु
	u8 bl_file;
	u8 bl_status;
	u8 bl_error;
	u8 blver_hi;
	u8 blver_lo;
	u8 bld_blver_hi;
	u8 bld_blver_lo;
	u8 ttspver_hi;
	u8 ttspver_lo;
	u8 appid_hi;
	u8 appid_lo;
	u8 appver_hi;
	u8 appver_lo;
	u8 cid_0;
	u8 cid_1;
	u8 cid_2;
पूर्ण;

काष्ठा cyttsp;

काष्ठा cyttsp_bus_ops अणु
	u16 bustype;
	पूर्णांक (*ग_लिखो)(काष्ठा device *dev, u8 *xfer_buf, u16 addr, u8 length,
			स्थिर व्योम *values);
	पूर्णांक (*पढ़ो)(काष्ठा device *dev, u8 *xfer_buf, u16 addr, u8 length,
			व्योम *values);
पूर्ण;

क्रमागत cyttsp_state अणु
	CY_IDLE_STATE,
	CY_ACTIVE_STATE,
	CY_BL_STATE,
पूर्ण;

काष्ठा cyttsp अणु
	काष्ठा device *dev;
	पूर्णांक irq;
	काष्ठा input_dev *input;
	स्थिर काष्ठा cyttsp_bus_ops *bus_ops;
	काष्ठा cyttsp_bootloader_data bl_data;
	काष्ठा cyttsp_sysinfo_data sysinfo_data;
	काष्ठा cyttsp_xydata xy_data;
	काष्ठा completion bl_पढ़ोy;
	क्रमागत cyttsp_state state;
	bool suspended;

	काष्ठा gpio_desc *reset_gpio;
	bool use_hndshk;
	u8 act_dist;
	u8 act_पूर्णांकrvl;
	u8 tch_पंचांगout;
	u8 lp_पूर्णांकrvl;
	u8 *bl_keys;

	u8 xfer_buf[] ____cacheline_aligned;
पूर्ण;

काष्ठा cyttsp *cyttsp_probe(स्थिर काष्ठा cyttsp_bus_ops *bus_ops,
			    काष्ठा device *dev, पूर्णांक irq, माप_प्रकार xfer_buf_size);

पूर्णांक cyttsp_i2c_ग_लिखो_block_data(काष्ठा device *dev, u8 *xfer_buf, u16 addr,
		u8 length, स्थिर व्योम *values);
पूर्णांक cyttsp_i2c_पढ़ो_block_data(काष्ठा device *dev, u8 *xfer_buf, u16 addr,
		u8 length, व्योम *values);
बाह्य स्थिर काष्ठा dev_pm_ops cyttsp_pm_ops;

#पूर्ण_अगर /* __CYTTSP_CORE_H__ */
