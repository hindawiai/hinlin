<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* aपंचांगsap.h - ATM Service Access Poपूर्णांक addressing definitions */

/* Written 1995-1999 by Werner Almesberger, EPFL LRC/ICA */


#अगर_अघोषित _LINUX_ATMSAP_H
#घोषणा _LINUX_ATMSAP_H

#समावेश <linux/aपंचांगapi.h>

/*
 * BEGIN_xx and END_xx markers are used क्रम स्वतःmatic generation of
 * करोcumentation. Do not change them.
 */


/*
 * Layer 2 protocol identअगरiers
 */

/* BEGIN_L2 */
#घोषणा ATM_L2_NONE	0	/* L2 not specअगरied */
#घोषणा ATM_L2_ISO1745  0x01	/* Basic mode ISO 1745 */
#घोषणा ATM_L2_Q291	0x02	/* ITU-T Q.291 (Rec. I.441) */
#घोषणा ATM_L2_X25_LL	0x06	/* ITU-T X.25, link layer */
#घोषणा ATM_L2_X25_ML	0x07	/* ITU-T X.25, multilink */
#घोषणा ATM_L2_LAPB	0x08	/* Extended LAPB, half-duplex (Rec. T.71) */
#घोषणा ATM_L2_HDLC_ARM	0x09	/* HDLC ARM (ISO/IEC 4335) */
#घोषणा ATM_L2_HDLC_NRM	0x0a	/* HDLC NRM (ISO/IEC 4335) */
#घोषणा ATM_L2_HDLC_ABM	0x0b	/* HDLC ABM (ISO/IEC 4335) */
#घोषणा ATM_L2_ISO8802	0x0c	/* LAN LLC (ISO/IEC 8802/2) */
#घोषणा ATM_L2_X75	0x0d	/* ITU-T X.75, SLP */
#घोषणा ATM_L2_Q922	0x0e	/* ITU-T Q.922 */
#घोषणा ATM_L2_USER	0x10	/* user-specअगरied */
#घोषणा ATM_L2_ISO7776	0x11	/* ISO 7776 DTE-DTE */
/* END_L2 */


/*
 * Layer 3 protocol identअगरiers
 */

/* BEGIN_L3 */
#घोषणा ATM_L3_NONE	0	/* L3 not specअगरied */
#घोषणा ATM_L3_X25	0x06	/* ITU-T X.25, packet layer */
#घोषणा ATM_L3_ISO8208	0x07	/* ISO/IEC 8208 */
#घोषणा ATM_L3_X223	0x08	/* ITU-T X.223 | ISO/IEC 8878 */
#घोषणा ATM_L3_ISO8473	0x09	/* ITU-T X.233 | ISO/IEC 8473 */
#घोषणा ATM_L3_T70	0x0a	/* ITU-T T.70 minimum network layer */
#घोषणा ATM_L3_TR9577	0x0b	/* ISO/IEC TR 9577 */
#घोषणा ATM_L3_H310	0x0c	/* ITU-T Recommendation H.310 */
#घोषणा ATM_L3_H321	0x0d	/* ITU-T Recommendation H.321 */
#घोषणा ATM_L3_USER	0x10	/* user-specअगरied */
/* END_L3 */


/*
 * High layer identअगरiers
 */

/* BEGIN_HL */
#घोषणा ATM_HL_NONE	0	/* HL not specअगरied */
#घोषणा ATM_HL_ISO	0x01	/* ISO */
#घोषणा ATM_HL_USER	0x02	/* user-specअगरic */
#घोषणा ATM_HL_HLP	0x03	/* high layer profile - UNI 3.0 only */
#घोषणा ATM_HL_VENDOR	0x04	/* venकरोr-specअगरic application identअगरier */
/* END_HL */


/*
 * ITU-T coded mode of operation
 */

/* BEGIN_IMD */
#घोषणा ATM_IMD_NONE	 0	/* mode not specअगरied */
#घोषणा ATM_IMD_NORMAL	 1	/* normal mode of operation */
#घोषणा ATM_IMD_EXTENDED 2	/* extended mode of operation */
/* END_IMD */

/*
 * H.310 code poपूर्णांकs
 */

#घोषणा ATM_TT_NONE	0	/* terminal type not specअगरied */
#घोषणा ATM_TT_RX	1	/* receive only */
#घोषणा ATM_TT_TX	2	/* send only */
#घोषणा ATM_TT_RXTX	3	/* receive and send */

#घोषणा ATM_MC_NONE	0	/* no multiplexing */
#घोषणा ATM_MC_TS	1	/* transport stream (TS) */
#घोषणा ATM_MC_TS_FEC	2	/* transport stream with क्रमward error corr. */
#घोषणा ATM_MC_PS	3	/* program stream (PS) */
#घोषणा ATM_MC_PS_FEC	4	/* program stream with क्रमward error corr. */
#घोषणा ATM_MC_H221	5	/* ITU-T Rec. H.221 */

/*
 * SAP काष्ठाures
 */

#घोषणा ATM_MAX_HLI	8	/* maximum high-layer inक्रमmation length */


काष्ठा aपंचांग_blli अणु
    अचिन्हित अक्षर l2_proto;	/* layer 2 protocol */
    जोड़ अणु
	काष्ठा अणु
	    अचिन्हित अक्षर mode;	/* mode of operation (ATM_IMD_xxx), 0 अगर */
				/* असलent */
	    अचिन्हित अक्षर winकरोw; /* winकरोw size (k), 1-127 (0 to omit) */
	पूर्ण itu;			/* ITU-T encoding */
	अचिन्हित अक्षर user;	/* user-specअगरied l2 inक्रमmation */
    पूर्ण l2;
    अचिन्हित अक्षर l3_proto;	/* layer 3 protocol */
    जोड़ अणु
	काष्ठा अणु
	    अचिन्हित अक्षर mode;	/* mode of operation (ATM_IMD_xxx), 0 अगर */
				/* असलent */
	    अचिन्हित अक्षर def_size; /* शेष packet size (log2), 4-12 (0 to */
				    /* omit) */
	    अचिन्हित अक्षर winकरोw;/* packet winकरोw size, 1-127 (0 to omit) */
	पूर्ण itu;			/* ITU-T encoding */
	अचिन्हित अक्षर user;	/* user specअगरied l3 inक्रमmation */
	काष्ठा अणु		      /* अगर l3_proto = ATM_L3_H310 */
	    अचिन्हित अक्षर term_type;  /* terminal type */
	    अचिन्हित अक्षर fw_mpx_cap; /* क्रमward multiplexing capability */
				      /* only अगर term_type != ATM_TT_NONE */
	    अचिन्हित अक्षर bw_mpx_cap; /* backward multiplexing capability */
				      /* only अगर term_type != ATM_TT_NONE */
	पूर्ण h310;
	काष्ठा अणु		  /* अगर l3_proto = ATM_L3_TR9577 */
	    अचिन्हित अक्षर ipi;	  /* initial protocol id */
	    अचिन्हित अक्षर snap[5];/* IEEE 802.1 SNAP identअगरier */
				  /* (only अगर ipi == NLPID_IEEE802_1_SNAP) */
	पूर्ण tr9577;
    पूर्ण l3;
पूर्ण __ATM_API_ALIGN;


काष्ठा aपंचांग_bhli अणु
    अचिन्हित अक्षर hl_type;	/* high layer inक्रमmation type */
    अचिन्हित अक्षर hl_length;	/* length (only अगर hl_type == ATM_HL_USER || */
				/* hl_type == ATM_HL_ISO) */
    अचिन्हित अक्षर hl_info[ATM_MAX_HLI];/* high layer inक्रमmation */
पूर्ण;


#घोषणा ATM_MAX_BLLI	3		/* maximum number of BLLI elements */


काष्ठा aपंचांग_sap अणु
	काष्ठा aपंचांग_bhli bhli;		/* local SAP, high-layer inक्रमmation */
	काष्ठा aपंचांग_blli blli[ATM_MAX_BLLI] __ATM_API_ALIGN;
					/* local SAP, low-layer info */
पूर्ण;


अटल __अंतरभूत__ पूर्णांक blli_in_use(काष्ठा aपंचांग_blli blli)
अणु
	वापस blli.l2_proto || blli.l3_proto;
पूर्ण

#पूर्ण_अगर
