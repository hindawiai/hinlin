<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * xwidget.h - generic crosstalk widget header file, derived from IRIX
 * <sys/xtalk/xtalkwidget.h>, revision 1.32.
 *
 * Copyright (C) 1996, 1999 Silcon Graphics, Inc.
 * Copyright (C) 1999 Ralf Baechle (ralf@gnu.org)
 */
#अगर_अघोषित _ASM_XTALK_XWIDGET_H
#घोषणा _ASM_XTALK_XWIDGET_H

#समावेश <linux/types.h>
#समावेश <यंत्र/xtalk/xtalk.h>

#घोषणा WIDGET_ID			0x04
#घोषणा WIDGET_STATUS			0x0c
#घोषणा WIDGET_ERR_UPPER_ADDR		0x14
#घोषणा WIDGET_ERR_LOWER_ADDR		0x1c
#घोषणा WIDGET_CONTROL			0x24
#घोषणा WIDGET_REQ_TIMEOUT		0x2c
#घोषणा WIDGET_INTDEST_UPPER_ADDR	0x34
#घोषणा WIDGET_INTDEST_LOWER_ADDR	0x3c
#घोषणा WIDGET_ERR_CMD_WORD		0x44
#घोषणा WIDGET_LLP_CFG			0x4c
#घोषणा WIDGET_TFLUSH			0x54

/* WIDGET_ID */
#घोषणा WIDGET_REV_NUM			0xf0000000
#घोषणा WIDGET_PART_NUM			0x0ffff000
#घोषणा WIDGET_MFG_NUM			0x00000ffe
#घोषणा WIDGET_REV_NUM_SHFT		28
#घोषणा WIDGET_PART_NUM_SHFT		12
#घोषणा WIDGET_MFG_NUM_SHFT		1

#घोषणा XWIDGET_PART_NUM(widgetid) (((widgetid) & WIDGET_PART_NUM) >> WIDGET_PART_NUM_SHFT)
#घोषणा XWIDGET_REV_NUM(widgetid) (((widgetid) & WIDGET_REV_NUM) >> WIDGET_REV_NUM_SHFT)
#घोषणा XWIDGET_MFG_NUM(widgetid) (((widgetid) & WIDGET_MFG_NUM) >> WIDGET_MFG_NUM_SHFT)

/* WIDGET_STATUS */
#घोषणा WIDGET_LLP_REC_CNT		0xff000000
#घोषणा WIDGET_LLP_TX_CNT		0x00ff0000
#घोषणा WIDGET_PENDING			0x0000001f

/* WIDGET_ERR_UPPER_ADDR */
#घोषणा WIDGET_ERR_UPPER_ADDR_ONLY	0x0000ffff

/* WIDGET_CONTROL */
#घोषणा WIDGET_F_BAD_PKT		0x00010000
#घोषणा WIDGET_LLP_XBAR_CRD		0x0000f000
#घोषणा WIDGET_LLP_XBAR_CRD_SHFT	12
#घोषणा WIDGET_CLR_RLLP_CNT		0x00000800
#घोषणा WIDGET_CLR_TLLP_CNT		0x00000400
#घोषणा WIDGET_SYS_END			0x00000200
#घोषणा WIDGET_MAX_TRANS		0x000001f0
#घोषणा WIDGET_WIDGET_ID		0x0000000f

/* WIDGET_INTDEST_UPPER_ADDR */
#घोषणा WIDGET_INT_VECTOR		0xff000000
#घोषणा WIDGET_INT_VECTOR_SHFT		24
#घोषणा WIDGET_TARGET_ID		0x000f0000
#घोषणा WIDGET_TARGET_ID_SHFT		16
#घोषणा WIDGET_UPP_ADDR			0x0000ffff

/* WIDGET_ERR_CMD_WORD */
#घोषणा WIDGET_DIDN			0xf0000000
#घोषणा WIDGET_SIDN			0x0f000000
#घोषणा WIDGET_PACTYP			0x00f00000
#घोषणा WIDGET_TNUM			0x000f8000
#घोषणा WIDGET_COHERENT			0x00004000
#घोषणा WIDGET_DS			0x00003000
#घोषणा WIDGET_GBR			0x00000800
#घोषणा WIDGET_VBPM			0x00000400
#घोषणा WIDGET_ERROR			0x00000200
#घोषणा WIDGET_BARRIER			0x00000100

/* WIDGET_LLP_CFG */
#घोषणा WIDGET_LLP_MAXRETRY		0x03ff0000
#घोषणा WIDGET_LLP_MAXRETRY_SHFT	16
#घोषणा WIDGET_LLP_शून्यTIMEOUT		0x0000fc00
#घोषणा WIDGET_LLP_शून्यTIMEOUT_SHFT	10
#घोषणा WIDGET_LLP_MAXBURST		0x000003ff
#घोषणा WIDGET_LLP_MAXBURST_SHFT	0

/* Xtalk Widget Device Mfgr Nums */
#घोषणा WIDGET_XBOW_MFGR_NUM	0x0      /* IP30 XBow Chip */
#घोषणा WIDGET_XXBOW_MFGR_NUM	0x0      /* IP35 Xbow + XBridge Chip */
#घोषणा WIDGET_ODYS_MFGR_NUM	0x023    /* Odyssey / VPro GFX */
#घोषणा WIDGET_TPU_MFGR_NUM	0x024    /* Tensor Processor Unit */
#घोषणा WIDGET_XBRDG_MFGR_NUM	0x024    /* IP35 XBridge Chip */
#घोषणा WIDGET_HEART_MFGR_NUM	0x036    /* IP30 HEART Chip */
#घोषणा WIDGET_BRIDG_MFGR_NUM	0x036    /* PCI Bridge */
#घोषणा WIDGET_HUB_MFGR_NUM	0x036    /* IP27 Hub Chip */
#घोषणा WIDGET_BDRCK_MFGR_NUM	0x036    /* IP35 Bedrock Chip */
#घोषणा WIDGET_IMPCT_MFGR_NUM	0x2aa    /* HQ4 / Impact GFX */
#घोषणा WIDGET_KONA_MFGR_NUM	0x2aa    /* InfiniteReality3 / Kona GFX */
#घोषणा WIDGET_शून्य_MFGR_NUM	-1       /* शून्य */

/* Xtalk Widget Device Part Nums */
#घोषणा WIDGET_XBOW_PART_NUM	0x0000
#घोषणा WIDGET_HEART_PART_NUM	0xc001
#घोषणा WIDGET_BRIDG_PART_NUM	0xc002
#घोषणा WIDGET_IMPCT_PART_NUM	0xc003
#घोषणा WIDGET_ODYS_PART_NUM	0xc013
#घोषणा WIDGET_HUB_PART_NUM	0xc101
#घोषणा WIDGET_KONA_PART_NUM	0xc102
#घोषणा WIDGET_BDRCK_PART_NUM	0xc110
#घोषणा WIDGET_TPU_PART_NUM	0xc202
#घोषणा WIDGET_XXBOW_PART_NUM	0xd000
#घोषणा WIDGET_XBRDG_PART_NUM	0xd002
#घोषणा WIDGET_शून्य_PART_NUM	-1

/* For Xtalk Widget identअगरication */
काष्ठा widget_ident अणु
	u32 mfgr;
	u32 part;
	अक्षर *name;
	अक्षर *revs[16];
पूर्ण;

/* Known Xtalk Widमाला_लो */
अटल स्थिर काष्ठा widget_ident __initस्थिर widget_idents[] = अणु
	अणु
		WIDGET_XBOW_MFGR_NUM,
		WIDGET_XBOW_PART_NUM,
		"xbow",
		अणुशून्य, "1.0", "1.1", "1.2", "1.3", "2.0", शून्यपूर्ण,
	पूर्ण,
	अणु
		WIDGET_HEART_MFGR_NUM,
		WIDGET_HEART_PART_NUM,
		"heart",
		अणुशून्य, "A", "B", "C", "D", "E", "F", शून्यपूर्ण,
	पूर्ण,
	अणु
		WIDGET_BRIDG_MFGR_NUM,
		WIDGET_BRIDG_PART_NUM,
		"bridge",
		अणुशून्य, "A", "B", "C", "D", शून्यपूर्ण,
	पूर्ण,
	अणु
		WIDGET_IMPCT_MFGR_NUM,
		WIDGET_IMPCT_PART_NUM,
		"impact",
		अणुशून्य, "A", "B", शून्यपूर्ण,
	पूर्ण,
	अणु
		WIDGET_ODYS_MFGR_NUM,
		WIDGET_ODYS_PART_NUM,
		"odyssey",
		अणुशून्य, "A", "B", शून्यपूर्ण,
	पूर्ण,
	अणु
		WIDGET_HUB_MFGR_NUM,
		WIDGET_HUB_PART_NUM,
		"hub",
		अणुशून्य, "1.0", "2.0", "2.1", "2.2", "2.3", "2.4", शून्यपूर्ण,
	पूर्ण,
	अणु
		WIDGET_KONA_MFGR_NUM,
		WIDGET_KONA_PART_NUM,
		"kona",
		अणुशून्यपूर्ण,
	पूर्ण,
	अणु
		WIDGET_BDRCK_MFGR_NUM,
		WIDGET_BDRCK_PART_NUM,
		"bedrock",
		अणुशून्य, "1.0", "1.1", शून्यपूर्ण,
	पूर्ण,
	अणु
		WIDGET_TPU_MFGR_NUM,
		WIDGET_TPU_PART_NUM,
		"tpu",
		अणु"0", शून्यपूर्ण,
	पूर्ण,
	अणु
		WIDGET_XXBOW_MFGR_NUM,
		WIDGET_XXBOW_PART_NUM,
		"xxbow",
		अणुशून्य, "1.0", "2.0", शून्यपूर्ण,
	पूर्ण,
	अणु
		WIDGET_XBRDG_MFGR_NUM,
		WIDGET_XBRDG_PART_NUM,
		"xbridge",
		अणुशून्य, "A", "B", शून्यपूर्ण,
	पूर्ण,
	अणु
		WIDGET_शून्य_MFGR_NUM,
		WIDGET_शून्य_PART_NUM,
		शून्य,
		अणुशून्यपूर्ण,
	पूर्ण
पूर्ण;

/*
 * according to the crosstalk spec, only 32-bits access to the widget
 * configuration रेजिस्टरs is allowed.	some widमाला_लो may allow 64-bits
 * access but software should not depend on it.	 रेजिस्टरs beyond the
 * widget target flush रेजिस्टर are widget dependent thus will not be
 * defined here
 */
#अगर_अघोषित __ASSEMBLY__
प्रकार u32 widgetreg_t;

/* widget configuration रेजिस्टरs */
प्रकार अस्थिर काष्ठा widget_cfg अणु
	widgetreg_t		w_pad_0;		/* 0x00 */
	widgetreg_t		w_id;			/* 0x04 */
	widgetreg_t		w_pad_1;		/* 0x08 */
	widgetreg_t		w_status;		/* 0x0c */
	widgetreg_t		w_pad_2;		/* 0x10 */
	widgetreg_t		w_err_upper_addr;	/* 0x14 */
	widgetreg_t		w_pad_3;		/* 0x18 */
	widgetreg_t		w_err_lower_addr;	/* 0x1c */
	widgetreg_t		w_pad_4;		/* 0x20 */
	widgetreg_t		w_control;		/* 0x24 */
	widgetreg_t		w_pad_5;		/* 0x28 */
	widgetreg_t		w_req_समयout;		/* 0x2c */
	widgetreg_t		w_pad_6;		/* 0x30 */
	widgetreg_t		w_पूर्णांकdest_upper_addr;	/* 0x34 */
	widgetreg_t		w_pad_7;		/* 0x38 */
	widgetreg_t		w_पूर्णांकdest_lower_addr;	/* 0x3c */
	widgetreg_t		w_pad_8;		/* 0x40 */
	widgetreg_t		w_err_cmd_word;		/* 0x44 */
	widgetreg_t		w_pad_9;		/* 0x48 */
	widgetreg_t		w_llp_cfg;		/* 0x4c */
	widgetreg_t		w_pad_10;		/* 0x50 */
	widgetreg_t		w_tflush;		/* 0x54 */
पूर्ण widget_cfg_t;

प्रकार काष्ठा अणु
	अचिन्हित	didn:4;
	अचिन्हित	sidn:4;
	अचिन्हित	pactyp:4;
	अचिन्हित	tnum:5;
	अचिन्हित	ct:1;
	अचिन्हित	ds:2;
	अचिन्हित	gbr:1;
	अचिन्हित	vbpm:1;
	अचिन्हित	error:1;
	अचिन्हित	bo:1;
	अचिन्हित	other:8;
पूर्ण w_err_cmd_word_f;

प्रकार जोड़ अणु
	widgetreg_t		r;
	w_err_cmd_word_f	f;
पूर्ण w_err_cmd_word_u;

प्रकार काष्ठा xwidget_info_s *xwidget_info_t;

/*
 * Crosstalk Widget Hardware Identअगरication, as defined in the Crosstalk spec.
 */
प्रकार काष्ठा xwidget_hwid_s अणु
	xwidget_part_num_t	part_num;
	xwidget_rev_num_t	rev_num;
	xwidget_mfg_num_t	mfg_num;
पूर्ण *xwidget_hwid_t;


/*
 * Returns 1 अगर a driver that handles devices described by hwid1 is able
 * to manage a device with hardwareid hwid2.  NOTE: We करोn't check rev
 * numbers at all.
 */
#घोषणा XWIDGET_HARDWARE_ID_MATCH(hwid1, hwid2) \
	(((hwid1)->part_num == (hwid2)->part_num) && \
	(((hwid1)->mfg_num == XWIDGET_MFG_NUM_NONE) || \
	((hwid2)->mfg_num == XWIDGET_MFG_NUM_NONE) || \
	((hwid1)->mfg_num == (hwid2)->mfg_num)))

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_XTALK_XWIDGET_H */
