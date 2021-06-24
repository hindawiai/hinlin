<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * cyttsp4_core.h
 * Cypress TrueTouch(TM) Standard Product V4 Core driver module.
 * For use with Cypress Txx4xx parts.
 * Supported parts include:
 * TMA4XX
 * TMA1036
 *
 * Copyright (C) 2012 Cypress Semiconductor
 *
 * Contact Cypress Semiconductor at www.cypress.com <ttdrivers@cypress.com>
 */

#अगर_अघोषित _LINUX_CYTTSP4_CORE_H
#घोषणा _LINUX_CYTTSP4_CORE_H

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/input.h>
#समावेश <linux/kernel.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/module.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_data/cyttsp4.h>

#घोषणा CY_REG_BASE			0x00

#घोषणा CY_POST_CODEL_WDG_RST		0x01
#घोषणा CY_POST_CODEL_CFG_DATA_CRC_FAIL	0x02
#घोषणा CY_POST_CODEL_PANEL_TEST_FAIL	0x04

#घोषणा CY_NUM_BTN_PER_REG		4

/* touch record प्रणाली inक्रमmation offset masks and shअगरts */
#घोषणा CY_BYTE_OFS_MASK		0x1F
#घोषणा CY_BOFS_MASK			0xE0
#घोषणा CY_BOFS_SHIFT			5

#घोषणा CY_TMA1036_TCH_REC_SIZE		6
#घोषणा CY_TMA4XX_TCH_REC_SIZE		9
#घोषणा CY_TMA1036_MAX_TCH		0x0E
#घोषणा CY_TMA4XX_MAX_TCH		0x1E

#घोषणा CY_NORMAL_ORIGIN		0	/* upper, left corner */
#घोषणा CY_INVERT_ORIGIN		1	/* lower, right corner */

/* helpers */
#घोषणा GET_NUM_TOUCHES(x)		((x) & 0x1F)
#घोषणा IS_LARGE_AREA(x)		((x) & 0x20)
#घोषणा IS_BAD_PKT(x)			((x) & 0x20)
#घोषणा IS_BOOTLOADER(hst_mode, reset_detect)	\
		((hst_mode) & 0x01 || (reset_detect) != 0)
#घोषणा IS_TMO(t)			((t) == 0)


क्रमागत cyttsp_cmd_bits अणु
	CY_CMD_COMPLETE = (1 << 6),
पूर्ण;

/* Timeout in ms. */
#घोषणा CY_WATCHDOG_TIMEOUT		1000

#घोषणा CY_MAX_PRINT_SIZE		512
#अगर_घोषित VERBOSE_DEBUG
#घोषणा CY_MAX_PRBUF_SIZE		PIPE_BUF
#घोषणा CY_PR_TRUNCATED			" truncated..."
#पूर्ण_अगर

क्रमागत cyttsp4_ic_grpnum अणु
	CY_IC_GRPNUM_RESERVED,
	CY_IC_GRPNUM_CMD_REGS,
	CY_IC_GRPNUM_TCH_REP,
	CY_IC_GRPNUM_DATA_REC,
	CY_IC_GRPNUM_TEST_REC,
	CY_IC_GRPNUM_PCFG_REC,
	CY_IC_GRPNUM_TCH_PARM_VAL,
	CY_IC_GRPNUM_TCH_PARM_SIZE,
	CY_IC_GRPNUM_RESERVED1,
	CY_IC_GRPNUM_RESERVED2,
	CY_IC_GRPNUM_OPCFG_REC,
	CY_IC_GRPNUM_DDATA_REC,
	CY_IC_GRPNUM_MDATA_REC,
	CY_IC_GRPNUM_TEST_REGS,
	CY_IC_GRPNUM_BTN_KEYS,
	CY_IC_GRPNUM_TTHE_REGS,
	CY_IC_GRPNUM_NUM
पूर्ण;

क्रमागत cyttsp4_पूर्णांक_state अणु
	CY_INT_NONE,
	CY_INT_IGNORE      = (1 << 0),
	CY_INT_MODE_CHANGE = (1 << 1),
	CY_INT_EXEC_CMD    = (1 << 2),
	CY_INT_AWAKE       = (1 << 3),
पूर्ण;

क्रमागत cyttsp4_mode अणु
	CY_MODE_UNKNOWN,
	CY_MODE_BOOTLOADER   = (1 << 1),
	CY_MODE_OPERATIONAL  = (1 << 2),
	CY_MODE_SYSINFO      = (1 << 3),
	CY_MODE_CAT          = (1 << 4),
	CY_MODE_STARTUP      = (1 << 5),
	CY_MODE_LOADER       = (1 << 6),
	CY_MODE_CHANGE_MODE  = (1 << 7),
	CY_MODE_CHANGED      = (1 << 8),
	CY_MODE_CMD_COMPLETE = (1 << 9),
पूर्ण;

क्रमागत cyttsp4_sleep_state अणु
	SS_SLEEP_OFF,
	SS_SLEEP_ON,
	SS_SLEEPING,
	SS_WAKING,
पूर्ण;

क्रमागत cyttsp4_startup_state अणु
	STARTUP_NONE,
	STARTUP_QUEUED,
	STARTUP_RUNNING,
पूर्ण;

#घोषणा CY_NUM_REVCTRL			8
काष्ठा cyttsp4_cydata अणु
	u8 ttpidh;
	u8 ttpidl;
	u8 fw_ver_major;
	u8 fw_ver_minor;
	u8 revctrl[CY_NUM_REVCTRL];
	u8 blver_major;
	u8 blver_minor;
	u8 jtag_si_id3;
	u8 jtag_si_id2;
	u8 jtag_si_id1;
	u8 jtag_si_id0;
	u8 mfgid_sz;
	u8 cyito_idh;
	u8 cyito_idl;
	u8 cyito_verh;
	u8 cyito_verl;
	u8 ttsp_ver_major;
	u8 ttsp_ver_minor;
	u8 device_info;
	u8 mfg_id[];
पूर्ण __packed;

काष्ठा cyttsp4_test अणु
	u8 post_codeh;
	u8 post_codel;
पूर्ण __packed;

काष्ठा cyttsp4_pcfg अणु
	u8 electrodes_x;
	u8 electrodes_y;
	u8 len_xh;
	u8 len_xl;
	u8 len_yh;
	u8 len_yl;
	u8 res_xh;
	u8 res_xl;
	u8 res_yh;
	u8 res_yl;
	u8 max_zh;
	u8 max_zl;
	u8 panel_info0;
पूर्ण __packed;

काष्ठा cyttsp4_tch_rec_params अणु
	u8 loc;
	u8 size;
पूर्ण __packed;

#घोषणा CY_NUM_TCH_FIELDS		7
#घोषणा CY_NUM_EXT_TCH_FIELDS		3
काष्ठा cyttsp4_opcfg अणु
	u8 cmd_ofs;
	u8 rep_ofs;
	u8 rep_szh;
	u8 rep_szl;
	u8 num_btns;
	u8 tt_stat_ofs;
	u8 obj_cfg0;
	u8 max_tchs;
	u8 tch_rec_size;
	काष्ठा cyttsp4_tch_rec_params tch_rec_old[CY_NUM_TCH_FIELDS];
	u8 btn_rec_size;	/* btn record size (in bytes) */
	u8 btn_dअगरf_ofs;	/* btn data loc, dअगरf counts  */
	u8 btn_dअगरf_size;	/* btn size of dअगरf counts (in bits) */
	काष्ठा cyttsp4_tch_rec_params tch_rec_new[CY_NUM_EXT_TCH_FIELDS];
पूर्ण __packed;

काष्ठा cyttsp4_sysinfo_ptr अणु
	काष्ठा cyttsp4_cydata *cydata;
	काष्ठा cyttsp4_test *test;
	काष्ठा cyttsp4_pcfg *pcfg;
	काष्ठा cyttsp4_opcfg *opcfg;
	काष्ठा cyttsp4_ddata *ddata;
	काष्ठा cyttsp4_mdata *mdata;
पूर्ण __packed;

काष्ठा cyttsp4_sysinfo_data अणु
	u8 hst_mode;
	u8 reserved;
	u8 map_szh;
	u8 map_szl;
	u8 cydata_ofsh;
	u8 cydata_ofsl;
	u8 test_ofsh;
	u8 test_ofsl;
	u8 pcfg_ofsh;
	u8 pcfg_ofsl;
	u8 opcfg_ofsh;
	u8 opcfg_ofsl;
	u8 ddata_ofsh;
	u8 ddata_ofsl;
	u8 mdata_ofsh;
	u8 mdata_ofsl;
पूर्ण __packed;

क्रमागत cyttsp4_tch_असल अणु	/* क्रम ordering within the extracted touch data array */
	CY_TCH_X,	/* X */
	CY_TCH_Y,	/* Y */
	CY_TCH_P,	/* P (Z) */
	CY_TCH_T,	/* TOUCH ID */
	CY_TCH_E,	/* EVENT ID */
	CY_TCH_O,	/* OBJECT ID */
	CY_TCH_W,	/* SIZE */
	CY_TCH_MAJ,	/* TOUCH_MAJOR */
	CY_TCH_MIN,	/* TOUCH_MINOR */
	CY_TCH_OR,	/* ORIENTATION */
	CY_TCH_NUM_ABS
पूर्ण;

काष्ठा cyttsp4_touch अणु
	पूर्णांक असल[CY_TCH_NUM_ABS];
पूर्ण;

काष्ठा cyttsp4_tch_असल_params अणु
	माप_प्रकार ofs;	/* असल byte offset */
	माप_प्रकार size;	/* size in bits */
	माप_प्रकार max;	/* max value */
	माप_प्रकार bofs;	/* bit offset */
पूर्ण;

काष्ठा cyttsp4_sysinfo_ofs अणु
	माप_प्रकार chip_type;
	माप_प्रकार cmd_ofs;
	माप_प्रकार rep_ofs;
	माप_प्रकार rep_sz;
	माप_प्रकार num_btns;
	माप_प्रकार num_btn_regs;	/* उच्चमान(num_btns/4) */
	माप_प्रकार tt_stat_ofs;
	माप_प्रकार tch_rec_size;
	माप_प्रकार obj_cfg0;
	माप_प्रकार max_tchs;
	माप_प्रकार mode_size;
	माप_प्रकार data_size;
	माप_प्रकार map_sz;
	माप_प्रकार max_x;
	माप_प्रकार x_origin;	/* left or right corner */
	माप_प्रकार max_y;
	माप_प्रकार y_origin;	/* upper or lower corner */
	माप_प्रकार max_p;
	माप_प्रकार cydata_ofs;
	माप_प्रकार test_ofs;
	माप_प्रकार pcfg_ofs;
	माप_प्रकार opcfg_ofs;
	माप_प्रकार ddata_ofs;
	माप_प्रकार mdata_ofs;
	माप_प्रकार cydata_size;
	माप_प्रकार test_size;
	माप_प्रकार pcfg_size;
	माप_प्रकार opcfg_size;
	माप_प्रकार ddata_size;
	माप_प्रकार mdata_size;
	माप_प्रकार btn_keys_size;
	काष्ठा cyttsp4_tch_असल_params tch_असल[CY_TCH_NUM_ABS];
	माप_प्रकार btn_rec_size; /* btn record size (in bytes) */
	माप_प्रकार btn_dअगरf_ofs;/* btn data loc ,dअगरf counts, (Op-Mode byte ofs) */
	माप_प्रकार btn_dअगरf_size;/* btn size of dअगरf counts (in bits) */
पूर्ण;

क्रमागत cyttsp4_btn_state अणु
	CY_BTN_RELEASED,
	CY_BTN_PRESSED,
	CY_BTN_NUM_STATE
पूर्ण;

काष्ठा cyttsp4_btn अणु
	bool enabled;
	पूर्णांक state;	/* CY_BTN_PRESSED, CY_BTN_RELEASED */
	पूर्णांक key_code;
पूर्ण;

काष्ठा cyttsp4_sysinfo अणु
	bool पढ़ोy;
	काष्ठा cyttsp4_sysinfo_data si_data;
	काष्ठा cyttsp4_sysinfo_ptr si_ptrs;
	काष्ठा cyttsp4_sysinfo_ofs si_ofs;
	काष्ठा cyttsp4_btn *btn;	/* button states */
	u8 *btn_rec_data;		/* button dअगरf count data */
	u8 *xy_mode;			/* operational mode and status regs */
	u8 *xy_data;			/* operational touch regs */
पूर्ण;

काष्ठा cyttsp4_mt_data अणु
	काष्ठा cyttsp4_mt_platक्रमm_data *pdata;
	काष्ठा cyttsp4_sysinfo *si;
	काष्ठा input_dev *input;
	काष्ठा mutex report_lock;
	bool is_suspended;
	अक्षर phys[NAME_MAX];
	पूर्णांक num_prv_tch;
पूर्ण;

काष्ठा cyttsp4 अणु
	काष्ठा device *dev;
	काष्ठा mutex प्रणाली_lock;
	काष्ठा mutex adap_lock;
	क्रमागत cyttsp4_mode mode;
	क्रमागत cyttsp4_sleep_state sleep_state;
	क्रमागत cyttsp4_startup_state startup_state;
	पूर्णांक पूर्णांक_status;
	रुको_queue_head_t रुको_q;
	पूर्णांक irq;
	काष्ठा work_काष्ठा startup_work;
	काष्ठा work_काष्ठा watchकरोg_work;
	काष्ठा समयr_list watchकरोg_समयr;
	काष्ठा cyttsp4_sysinfo sysinfo;
	व्योम *exclusive_dev;
	पूर्णांक exclusive_रुकोs;
	atomic_t ignore_irq;
	bool invalid_touch_app;
	काष्ठा cyttsp4_mt_data md;
	काष्ठा cyttsp4_platक्रमm_data *pdata;
	काष्ठा cyttsp4_core_platक्रमm_data *cpdata;
	स्थिर काष्ठा cyttsp4_bus_ops *bus_ops;
	u8 *xfer_buf;
#अगर_घोषित VERBOSE_DEBUG
	u8 pr_buf[CY_MAX_PRBUF_SIZE];
#पूर्ण_अगर
पूर्ण;

काष्ठा cyttsp4_bus_ops अणु
	u16 bustype;
	पूर्णांक (*ग_लिखो)(काष्ठा device *dev, u8 *xfer_buf, u16 addr, u8 length,
			स्थिर व्योम *values);
	पूर्णांक (*पढ़ो)(काष्ठा device *dev, u8 *xfer_buf, u16 addr, u8 length,
			व्योम *values);
पूर्ण;

क्रमागत cyttsp4_hst_mode_bits अणु
	CY_HST_TOGGLE      = (1 << 7),
	CY_HST_MODE_CHANGE = (1 << 3),
	CY_HST_MODE        = (7 << 4),
	CY_HST_OPERATE     = (0 << 4),
	CY_HST_SYSINFO     = (1 << 4),
	CY_HST_CAT         = (2 << 4),
	CY_HST_LOWPOW      = (1 << 2),
	CY_HST_SLEEP       = (1 << 1),
	CY_HST_RESET       = (1 << 0),
पूर्ण;

/* असल settings */
#घोषणा CY_IGNORE_VALUE			0xFFFF

/* असल संकेत capabilities offsets in the frameworks array */
क्रमागत cyttsp4_sig_caps अणु
	CY_SIGNAL_OST,
	CY_MIN_OST,
	CY_MAX_OST,
	CY_FUZZ_OST,
	CY_FLAT_OST,
	CY_NUM_ABS_SET	/* number of संकेत capability fields */
पूर्ण;

/* असल axis संकेत offsets in the framworks array  */
क्रमागत cyttsp4_sig_ost अणु
	CY_ABS_X_OST,
	CY_ABS_Y_OST,
	CY_ABS_P_OST,
	CY_ABS_W_OST,
	CY_ABS_ID_OST,
	CY_ABS_MAJ_OST,
	CY_ABS_MIN_OST,
	CY_ABS_OR_OST,
	CY_NUM_ABS_OST	/* number of असल संकेतs */
पूर्ण;

क्रमागत cyttsp4_flags अणु
	CY_FLAG_NONE = 0x00,
	CY_FLAG_HOVER = 0x04,
	CY_FLAG_FLIP = 0x08,
	CY_FLAG_INV_X = 0x10,
	CY_FLAG_INV_Y = 0x20,
	CY_FLAG_VKEYS = 0x40,
पूर्ण;

क्रमागत cyttsp4_object_id अणु
	CY_OBJ_STANDARD_FINGER,
	CY_OBJ_LARGE_OBJECT,
	CY_OBJ_STYLUS,
	CY_OBJ_HOVER,
पूर्ण;

क्रमागत cyttsp4_event_id अणु
	CY_EV_NO_EVENT,
	CY_EV_TOUCHDOWN,
	CY_EV_MOVE,		/* signअगरicant displacement (> act dist) */
	CY_EV_LIFTOFF,		/* record reports last position */
पूर्ण;

/* x-axis resolution of panel in pixels */
#घोषणा CY_PCFG_RESOLUTION_X_MASK	0x7F

/* y-axis resolution of panel in pixels */
#घोषणा CY_PCFG_RESOLUTION_Y_MASK	0x7F

/* x-axis, 0:origin is on left side of panel, 1: right */
#घोषणा CY_PCFG_ORIGIN_X_MASK		0x80

/* y-axis, 0:origin is on top side of panel, 1: bottom */
#घोषणा CY_PCFG_ORIGIN_Y_MASK		0x80

अटल अंतरभूत पूर्णांक cyttsp4_adap_पढ़ो(काष्ठा cyttsp4 *ts, u16 addr, पूर्णांक size,
		व्योम *buf)
अणु
	वापस ts->bus_ops->पढ़ो(ts->dev, ts->xfer_buf, addr, size, buf);
पूर्ण

अटल अंतरभूत पूर्णांक cyttsp4_adap_ग_लिखो(काष्ठा cyttsp4 *ts, u16 addr, पूर्णांक size,
		स्थिर व्योम *buf)
अणु
	वापस ts->bus_ops->ग_लिखो(ts->dev, ts->xfer_buf, addr, size, buf);
पूर्ण

बाह्य काष्ठा cyttsp4 *cyttsp4_probe(स्थिर काष्ठा cyttsp4_bus_ops *ops,
		काष्ठा device *dev, u16 irq, माप_प्रकार xfer_buf_size);
बाह्य पूर्णांक cyttsp4_हटाओ(काष्ठा cyttsp4 *ts);
पूर्णांक cyttsp_i2c_ग_लिखो_block_data(काष्ठा device *dev, u8 *xfer_buf, u16 addr,
		u8 length, स्थिर व्योम *values);
पूर्णांक cyttsp_i2c_पढ़ो_block_data(काष्ठा device *dev, u8 *xfer_buf, u16 addr,
		u8 length, व्योम *values);
बाह्य स्थिर काष्ठा dev_pm_ops cyttsp4_pm_ops;

#पूर्ण_अगर /* _LINUX_CYTTSP4_CORE_H */
