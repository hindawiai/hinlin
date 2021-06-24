<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
   cx231xx-pcb-config.c - driver क्रम Conexant
		Cx23100/101/102 USB video capture devices

   Copyright (C) 2008 <srinivasa.deevi at conexant करोt com>

 */

#समावेश "cx231xx.h"
#समावेश "cx231xx-conf-reg.h"

अटल अचिन्हित पूर्णांक pcb_debug;
module_param(pcb_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(pcb_debug, "enable pcb config debug messages [video]");

/******************************************************************************/

अटल काष्ठा pcb_config cx231xx_Scenario[] = अणु
	अणु
	 INDEX_SELFPOWER_DIGITAL_ONLY,	/* index */
	 USB_SELF_POWER,	/* घातer_type */
	 0,			/* speed , not decide yet */
	 MOD_DIGITAL,		/* mode */
	 SOURCE_TS_BDA,		/* ts1_source, digital tv only */
	 NOT_SUPPORTED,		/* ts2_source  */
	 NOT_SUPPORTED,		/* analog source */

	 0,			/* digital_index  */
	 0,			/* analog index */
	 0,			/* dअगर_index   */
	 0,			/* बाह्यal_index */

	 1,			/* only one configuration */
	 अणु
	  अणु
	   0,			/* config index */
	   अणु
	    0,			/* पूर्णांकerrupt ep index */
	    1,			/* ts1 index */
	    NOT_SUPPORTED,	/* TS2 index */
	    NOT_SUPPORTED,	/* AUDIO */
	    NOT_SUPPORTED,	/* VIDEO */
	    NOT_SUPPORTED,	/* VANC */
	    NOT_SUPPORTED,	/* HANC */
	    NOT_SUPPORTED	/* ir_index */
	    पूर्ण
	   ,
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  पूर्ण
	 ,
	 /* full-speed config */
	 अणु
	  अणु
	   0,			/* config index */
	   अणु
	    0,			/* पूर्णांकerrupt ep index */
	    1,			/* ts1 index */
	    NOT_SUPPORTED,	/* TS2 index */
	    NOT_SUPPORTED,	/* AUDIO */
	    NOT_SUPPORTED,	/* VIDEO */
	    NOT_SUPPORTED,	/* VANC */
	    NOT_SUPPORTED,	/* HANC */
	    NOT_SUPPORTED	/* ir_index */
	    पूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  पूर्ण
	 पूर्ण
	,

	अणु
	 INDEX_SELFPOWER_DUAL_DIGITAL,	/* index */
	 USB_SELF_POWER,	/* घातer_type */
	 0,			/* speed , not decide yet */
	 MOD_DIGITAL,		/* mode */
	 SOURCE_TS_BDA,		/* ts1_source, digital tv only */
	 0,			/* ts2_source,need update from रेजिस्टर */
	 NOT_SUPPORTED,		/* analog source */
	 0,			/* digital_index  */
	 0,			/* analog index */
	 0,			/* dअगर_index */
	 0,			/* बाह्यal_index */

	 1,			/* only one configuration */
	 अणु
	  अणु
	   0,			/* config index */
	   अणु
	    0,			/* पूर्णांकerrupt ep index */
	    1,			/* ts1 index */
	    2,			/* TS2 index */
	    NOT_SUPPORTED,	/* AUDIO */
	    NOT_SUPPORTED,	/* VIDEO */
	    NOT_SUPPORTED,	/* VANC */
	    NOT_SUPPORTED,	/* HANC */
	    NOT_SUPPORTED	/* ir_index */
	    पूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  पूर्ण
	 ,
	 /* full-speed */
	 अणु
	  अणु
	   0,			/* config index */
	   अणु
	    0,			/* पूर्णांकerrupt ep index */
	    1,			/* ts1 index */
	    2,			/* TS2 index */
	    NOT_SUPPORTED,	/* AUDIO */
	    NOT_SUPPORTED,	/* VIDEO */
	    NOT_SUPPORTED,	/* VANC */
	    NOT_SUPPORTED,	/* HANC */
	    NOT_SUPPORTED	/* ir_index */
	    पूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  पूर्ण
	 पूर्ण
	,

	अणु
	 INDEX_SELFPOWER_ANALOG_ONLY,	/* index */
	 USB_SELF_POWER,	/* घातer_type */
	 0,			/* speed , not decide yet */
	 MOD_ANALOG | MOD_DIF | MOD_EXTERNAL,	/* mode ,analog tv only */
	 NOT_SUPPORTED,		/* ts1_source, NOT SUPPORT */
	 NOT_SUPPORTED,		/* ts2_source,NOT SUPPORT */
	 0,			/* analog source, need update */

	 0,			/* digital_index  */
	 0,			/* analog index */
	 0,			/* dअगर_index */
	 0,			/* बाह्यal_index */

	 1,			/* only one configuration */
	 अणु
	  अणु
	   0,			/* config index */
	   अणु
	    0,			/* पूर्णांकerrupt ep index */
	    NOT_SUPPORTED,	/* ts1 index */
	    NOT_SUPPORTED,	/* TS2 index */
	    1,			/* AUDIO */
	    2,			/* VIDEO */
	    3,			/* VANC */
	    4,			/* HANC */
	    NOT_SUPPORTED	/* ir_index */
	    पूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  पूर्ण
	 ,
	 /* full-speed */
	 अणु
	  अणु
	   0,			/* config index */
	   अणु
	    0,			/* पूर्णांकerrupt ep index */
	    NOT_SUPPORTED,	/* ts1 index */
	    NOT_SUPPORTED,	/* TS2 index */
	    1,			/* AUDIO */
	    2,			/* VIDEO */
	    NOT_SUPPORTED,	/* VANC */
	    NOT_SUPPORTED,	/* HANC */
	    NOT_SUPPORTED	/* ir_index */
	    पूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  पूर्ण
	 पूर्ण
	,

	अणु
	 INDEX_SELFPOWER_DUAL,	/* index */
	 USB_SELF_POWER,	/* घातer_type */
	 0,			/* speed , not decide yet */
	 /* mode ,analog tv and digital path */
	 MOD_ANALOG | MOD_DIF | MOD_DIGITAL | MOD_EXTERNAL,
	 0,			/* ts1_source,will update in रेजिस्टर */
	 NOT_SUPPORTED,		/* ts2_source,NOT SUPPORT */
	 0,			/* analog source need update */
	 0,			/* digital_index  */
	 0,			/* analog index */
	 0,			/* dअगर_index */
	 0,			/* बाह्यal_index */
	 1,			/* only one configuration */
	 अणु
	  अणु
	   0,			/* config index */
	   अणु
	    0,			/* पूर्णांकerrupt ep index */
	    1,			/* ts1 index */
	    NOT_SUPPORTED,	/* TS2 index */
	    2,			/* AUDIO */
	    3,			/* VIDEO */
	    4,			/* VANC */
	    5,			/* HANC */
	    NOT_SUPPORTED	/* ir_index */
	    पूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  पूर्ण
	 ,
	 /* full-speed */
	 अणु
	  अणु
	   0,			/* config index */
	   अणु
	    0,			/* पूर्णांकerrupt ep index */
	    1,			/* ts1 index */
	    NOT_SUPPORTED,	/* TS2 index */
	    2,			/* AUDIO */
	    3,			/* VIDEO */
	    NOT_SUPPORTED,	/* VANC */
	    NOT_SUPPORTED,	/* HANC */
	    NOT_SUPPORTED	/* ir_index */
	    पूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  पूर्ण
	 पूर्ण
	,

	अणु
	 INDEX_SELFPOWER_TRIPLE,	/* index */
	 USB_SELF_POWER,	/* घातer_type */
	 0,			/* speed , not decide yet */
	 /* mode ,analog tv and digital path */
	 MOD_ANALOG | MOD_DIF | MOD_DIGITAL | MOD_EXTERNAL,
	 0,			/* ts1_source, update in रेजिस्टर */
	 0,			/* ts2_source,update in रेजिस्टर */
	 0,			/* analog source, need update */

	 0,			/* digital_index  */
	 0,			/* analog index */
	 0,			/* dअगर_index */
	 0,			/* बाह्यal_index */
	 1,			/* only one configuration */
	 अणु
	  अणु
	   0,			/* config index */
	   अणु
	    0,			/* पूर्णांकerrupt ep index */
	    1,			/* ts1 index */
	    2,			/* TS2 index */
	    3,			/* AUDIO */
	    4,			/* VIDEO */
	    5,			/* VANC */
	    6,			/* HANC */
	    NOT_SUPPORTED	/* ir_index */
	    पूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  पूर्ण
	 ,
	 /* full-speed */
	 अणु
	  अणु
	   0,			/* config index */
	   अणु
	    0,			/* पूर्णांकerrupt ep index */
	    1,			/* ts1 index */
	    2,			/* TS2 index */
	    3,			/* AUDIO */
	    4,			/* VIDEO */
	    NOT_SUPPORTED,	/* VANC */
	    NOT_SUPPORTED,	/* HANC */
	    NOT_SUPPORTED	/* ir_index */
	    पूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  पूर्ण
	 पूर्ण
	,

	अणु
	 INDEX_SELFPOWER_COMPRESSOR,	/* index */
	 USB_SELF_POWER,	/* घातer_type */
	 0,			/* speed , not decide yet */
	 /* mode ,analog tv AND DIGITAL path */
	 MOD_ANALOG | MOD_DIF | MOD_DIGITAL | MOD_EXTERNAL,
	 NOT_SUPPORTED,		/* ts1_source, disable */
	 SOURCE_TS_BDA,		/* ts2_source */
	 0,			/* analog source,need update */
	 0,			/* digital_index  */
	 0,			/* analog index */
	 0,			/* dअगर_index */
	 0,			/* बाह्यal_index */
	 1,			/* only one configuration */
	 अणु
	  अणु
	   0,			/* config index */
	   अणु
	    0,			/* पूर्णांकerrupt ep index */
	    NOT_SUPPORTED,	/* ts1 index */
	    1,			/* TS2 index */
	    2,			/* AUDIO */
	    3,			/* VIDEO */
	    4,			/* VANC */
	    5,			/* HANC */
	    NOT_SUPPORTED	/* ir_index */
	    पूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  पूर्ण
	 ,
	 /* full-speed  */
	 अणु
	  अणु
	   0,			/* config index */
	   अणु
	    0,			/* पूर्णांकerrupt ep index */
	    NOT_SUPPORTED,	/* ts1 index */
	    1,			/* TS2 index */
	    2,			/* AUDIO */
	    3,			/* VIDEO */
	    NOT_SUPPORTED,	/* VANC */
	    NOT_SUPPORTED,	/* HANC */
	    NOT_SUPPORTED	/* ir_index */
	    पूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  पूर्ण
	 पूर्ण
	,

	अणु
	 INDEX_BUSPOWER_DIGITAL_ONLY,	/* index */
	 USB_BUS_POWER,		/* घातer_type */
	 0,			/* speed , not decide yet */
	 MOD_DIGITAL,		/* mode ,analog tv AND DIGITAL path */
	 SOURCE_TS_BDA,		/* ts1_source, disable */
	 NOT_SUPPORTED,		/* ts2_source */
	 NOT_SUPPORTED,		/* analog source */

	 0,			/* digital_index  */
	 0,			/* analog index */
	 0,			/* dअगर_index */
	 0,			/* बाह्यal_index */

	 1,			/* only one configuration */
	 अणु
	  अणु
	   0,			/* config index */
	   अणु
	    0,			/* पूर्णांकerrupt ep index  = 2 */
	    1,			/* ts1 index */
	    NOT_SUPPORTED,	/* TS2 index */
	    NOT_SUPPORTED,	/* AUDIO */
	    NOT_SUPPORTED,	/* VIDEO */
	    NOT_SUPPORTED,	/* VANC */
	    NOT_SUPPORTED,	/* HANC */
	    NOT_SUPPORTED	/* ir_index */
	    पूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  पूर्ण
	 ,
	 /* full-speed */
	 अणु
	  अणु
	   0,			/* config index */
	   अणु
	    0,			/* पूर्णांकerrupt ep index  = 2 */
	    1,			/* ts1 index */
	    NOT_SUPPORTED,	/* TS2 index */
	    NOT_SUPPORTED,	/* AUDIO */
	    NOT_SUPPORTED,	/* VIDEO */
	    NOT_SUPPORTED,	/* VANC */
	    NOT_SUPPORTED,	/* HANC */
	    NOT_SUPPORTED	/* ir_index */
	    पूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  पूर्ण
	 पूर्ण
	,
	अणु
	 INDEX_BUSPOWER_ANALOG_ONLY,	/* index */
	 USB_BUS_POWER,		/* घातer_type */
	 0,			/* speed , not decide yet */
	 MOD_ANALOG,		/* mode ,analog tv AND DIGITAL path */
	 NOT_SUPPORTED,		/* ts1_source, disable */
	 NOT_SUPPORTED,		/* ts2_source */
	 SOURCE_ANALOG,		/* analog source--analog */
	 0,			/* digital_index  */
	 0,			/* analog index */
	 0,			/* dअगर_index */
	 0,			/* बाह्यal_index */
	 1,			/* only one configuration */
	 अणु
	  अणु
	   0,			/* config index */
	   अणु
	    0,			/* पूर्णांकerrupt ep index */
	    NOT_SUPPORTED,	/* ts1 index */
	    NOT_SUPPORTED,	/* TS2 index */
	    1,			/* AUDIO */
	    2,			/* VIDEO */
	    3,			/* VANC */
	    4,			/* HANC */
	    NOT_SUPPORTED	/* ir_index */
	    पूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  पूर्ण
	 ,
	 अणु			/* full-speed */
	  अणु
	   0,			/* config index */
	   अणु
	    0,			/* पूर्णांकerrupt ep index */
	    NOT_SUPPORTED,	/* ts1 index */
	    NOT_SUPPORTED,	/* TS2 index */
	    1,			/* AUDIO */
	    2,			/* VIDEO */
	    NOT_SUPPORTED,	/* VANC */
	    NOT_SUPPORTED,	/* HANC */
	    NOT_SUPPORTED	/* ir_index */
	    पूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  पूर्ण
	 पूर्ण
	,
	अणु
	 INDEX_BUSPOWER_DIF_ONLY,	/* index */
	 USB_BUS_POWER,		/* घातer_type */
	 0,			/* speed , not decide yet */
	 /* mode ,analog tv AND DIGITAL path */
	 MOD_DIF | MOD_ANALOG | MOD_DIGITAL | MOD_EXTERNAL,
	 SOURCE_TS_BDA,		/* ts1_source, disable */
	 NOT_SUPPORTED,		/* ts2_source */
	 SOURCE_DIF | SOURCE_ANALOG | SOURCE_EXTERNAL,	/* analog source, dअगर */
	 0,			/* digital_index  */
	 0,			/* analog index */
	 0,			/* dअगर_index */
	 0,			/* बाह्यal_index */
	 1,			/* only one configuration */
	 अणु
	  अणु
	   0,			/* config index */
	   अणु
	    0,			/* पूर्णांकerrupt ep index */
	    1,			/* ts1 index */
	    NOT_SUPPORTED,	/* TS2 index */
	    2,			/* AUDIO */
	    3,			/* VIDEO */
	    4,			/* VANC */
	    5,			/* HANC */
	    NOT_SUPPORTED	/* ir_index */
	    पूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  पूर्ण
	 ,
	 अणु			/* full speed */
	  अणु
	   0,			/* config index */
	   अणु
	    0,			/* पूर्णांकerrupt ep index */
	    1,			/* ts1 index */
	    NOT_SUPPORTED,	/* TS2 index */
	    2,			/* AUDIO */
	    3,			/* VIDEO */
	    NOT_SUPPORTED,	/* VANC */
	    NOT_SUPPORTED,	/* HANC */
	    NOT_SUPPORTED	/* ir_index */
	    पूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  ,
	  अणुNOT_SUPPORTED, अणुNOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTED, NOT_SUPPORTED, NOT_SUPPORTED,
			   NOT_SUPPORTEDपूर्ण
	   पूर्ण
	  पूर्ण
	 पूर्ण
	,

पूर्ण;

/*****************************************************************/

पूर्णांक initialize_cx231xx(काष्ठा cx231xx *dev)
अणु
	पूर्णांक retval;
	u32 config_info = 0;
	काष्ठा pcb_config *p_pcb_info;
	u8 usb_speed = 1;	/* from रेजिस्टर,1--HS, 0--FS  */
	u8 data[4] = अणु 0, 0, 0, 0 पूर्ण;
	u32 ts1_source = 0;
	u32 ts2_source = 0;
	u32 analog_source = 0;
	u8 _current_scenario_idx = 0xff;

	ts1_source = SOURCE_TS_BDA;
	ts2_source = SOURCE_TS_BDA;

	/* पढ़ो board config रेजिस्टर to find out which
	pcb config it is related to */
	retval = cx231xx_पढ़ो_ctrl_reg(dev, VRT_GET_REGISTER, BOARD_CFG_STAT,
				       data, 4);
	अगर (retval < 0)
		वापस retval;

	config_info = le32_to_cpu(*((__le32 *)data));
	usb_speed = (u8) (config_info & 0x1);

	/* Verअगरy this device beदीर्घs to Bus घातer or Self घातer device */
	अगर (config_info & BUS_POWER) अणु	/* bus-घातer */
		चयन (config_info & BUSPOWER_MASK) अणु
		हाल TS1_PORT | BUS_POWER:
			cx231xx_Scenario[INDEX_BUSPOWER_DIGITAL_ONLY].speed =
			    usb_speed;
			p_pcb_info =
			    &cx231xx_Scenario[INDEX_BUSPOWER_DIGITAL_ONLY];
			_current_scenario_idx = INDEX_BUSPOWER_DIGITAL_ONLY;
			अवरोध;
		हाल AVDEC_ENABLE | BUS_POWER:
			cx231xx_Scenario[INDEX_BUSPOWER_ANALOG_ONLY].speed =
			    usb_speed;
			p_pcb_info =
			    &cx231xx_Scenario[INDEX_BUSPOWER_ANALOG_ONLY];
			_current_scenario_idx = INDEX_BUSPOWER_ANALOG_ONLY;
			अवरोध;
		हाल AVDEC_ENABLE | BUS_POWER | TS1_PORT:
			cx231xx_Scenario[INDEX_BUSPOWER_DIF_ONLY].speed =
			    usb_speed;
			p_pcb_info = &cx231xx_Scenario[INDEX_BUSPOWER_DIF_ONLY];
			_current_scenario_idx = INDEX_BUSPOWER_DIF_ONLY;
			अवरोध;
		शेष:
			dev_err(dev->dev,
				"bad config in buspower!!!!\nconfig_info=%x\n",
				config_info & BUSPOWER_MASK);
			वापस 1;
		पूर्ण
	पूर्ण अन्यथा अणु		/* self-घातer */

		चयन (config_info & SELFPOWER_MASK) अणु
		हाल TS1_PORT | SELF_POWER:
			cx231xx_Scenario[INDEX_SELFPOWER_DIGITAL_ONLY].speed =
			    usb_speed;
			p_pcb_info =
			    &cx231xx_Scenario[INDEX_SELFPOWER_DIGITAL_ONLY];
			_current_scenario_idx = INDEX_SELFPOWER_DIGITAL_ONLY;
			अवरोध;
		हाल TS1_TS2_PORT | SELF_POWER:
			cx231xx_Scenario[INDEX_SELFPOWER_DUAL_DIGITAL].speed =
			    usb_speed;
			cx231xx_Scenario[INDEX_SELFPOWER_DUAL_DIGITAL].
			    ts2_source = ts2_source;
			p_pcb_info =
			    &cx231xx_Scenario[INDEX_SELFPOWER_DUAL_DIGITAL];
			_current_scenario_idx = INDEX_SELFPOWER_DUAL_DIGITAL;
			अवरोध;
		हाल AVDEC_ENABLE | SELF_POWER:
			cx231xx_Scenario[INDEX_SELFPOWER_ANALOG_ONLY].speed =
			    usb_speed;
			cx231xx_Scenario[INDEX_SELFPOWER_ANALOG_ONLY].
			    analog_source = analog_source;
			p_pcb_info =
			    &cx231xx_Scenario[INDEX_SELFPOWER_ANALOG_ONLY];
			_current_scenario_idx = INDEX_SELFPOWER_ANALOG_ONLY;
			अवरोध;
		हाल AVDEC_ENABLE | TS1_PORT | SELF_POWER:
			cx231xx_Scenario[INDEX_SELFPOWER_DUAL].speed =
			    usb_speed;
			cx231xx_Scenario[INDEX_SELFPOWER_DUAL].ts1_source =
			    ts1_source;
			cx231xx_Scenario[INDEX_SELFPOWER_DUAL].analog_source =
			    analog_source;
			p_pcb_info = &cx231xx_Scenario[INDEX_SELFPOWER_DUAL];
			_current_scenario_idx = INDEX_SELFPOWER_DUAL;
			अवरोध;
		हाल AVDEC_ENABLE | TS1_TS2_PORT | SELF_POWER:
			cx231xx_Scenario[INDEX_SELFPOWER_TRIPLE].speed =
			    usb_speed;
			cx231xx_Scenario[INDEX_SELFPOWER_TRIPLE].ts1_source =
			    ts1_source;
			cx231xx_Scenario[INDEX_SELFPOWER_TRIPLE].ts2_source =
			    ts2_source;
			cx231xx_Scenario[INDEX_SELFPOWER_TRIPLE].analog_source =
			    analog_source;
			p_pcb_info = &cx231xx_Scenario[INDEX_SELFPOWER_TRIPLE];
			_current_scenario_idx = INDEX_SELFPOWER_TRIPLE;
			अवरोध;
		हाल AVDEC_ENABLE | TS1VIP_TS2_PORT | SELF_POWER:
			cx231xx_Scenario[INDEX_SELFPOWER_COMPRESSOR].speed =
			    usb_speed;
			cx231xx_Scenario[INDEX_SELFPOWER_COMPRESSOR].
			    analog_source = analog_source;
			p_pcb_info =
			    &cx231xx_Scenario[INDEX_SELFPOWER_COMPRESSOR];
			_current_scenario_idx = INDEX_SELFPOWER_COMPRESSOR;
			अवरोध;
		शेष:
			dev_err(dev->dev,
				"bad scenario!!!!!\nconfig_info=%x\n",
				config_info & SELFPOWER_MASK);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	dev->current_scenario_idx = _current_scenario_idx;

	स_नकल(&dev->current_pcb_config, p_pcb_info,
		   माप(काष्ठा pcb_config));

	अगर (pcb_debug) अणु
		dev_info(dev->dev,
			 "SC(0x00) register = 0x%x\n", config_info);
		dev_info(dev->dev,
			 "scenario %d\n",
			 (dev->current_pcb_config.index) + 1);
		dev_info(dev->dev,
			"type=%x\n",
			 dev->current_pcb_config.type);
		dev_info(dev->dev,
			 "mode=%x\n",
			 dev->current_pcb_config.mode);
		dev_info(dev->dev,
			 "speed=%x\n",
			 dev->current_pcb_config.speed);
		dev_info(dev->dev,
			 "ts1_source=%x\n",
			 dev->current_pcb_config.ts1_source);
		dev_info(dev->dev,
			 "ts2_source=%x\n",
			 dev->current_pcb_config.ts2_source);
		dev_info(dev->dev,
			 "analog_source=%x\n",
			 dev->current_pcb_config.analog_source);
	पूर्ण

	वापस 0;
पूर्ण
