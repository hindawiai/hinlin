<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* aपंचांग.h - general ATM declarations */
 
/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
 

/*
 * WARNING: User-space programs should not #समावेश <linux/aपंचांग.h> directly.
 *          Instead, #समावेश <aपंचांग.h>
 */

#अगर_अघोषित _UAPI_LINUX_ATM_H
#घोषणा _UAPI_LINUX_ATM_H

/*
 * BEGIN_xx and END_xx markers are used क्रम स्वतःmatic generation of
 * करोcumentation. Do not change them.
 */

#समावेश <linux/compiler.h>
#समावेश <linux/aपंचांगapi.h>
#समावेश <linux/aपंचांगsap.h>
#समावेश <linux/aपंचांगioc.h>
#समावेश <linux/types.h>


/* general ATM स्थिरants */
#घोषणा ATM_CELL_SIZE		    53	/* ATM cell size incl. header */
#घोषणा ATM_CELL_PAYLOAD	    48	/* ATM payload size */
#घोषणा ATM_AAL0_SDU		    52	/* AAL0 SDU size */
#घोषणा ATM_MAX_AAL34_PDU	 65535	/* maximum AAL3/4 PDU payload */
#घोषणा ATM_AAL5_TRAILER	     8	/* AAL5 trailer size */
#घोषणा ATM_MAX_AAL5_PDU	 65535	/* maximum AAL5 PDU payload */
#घोषणा ATM_MAX_CDV		  9999	/* maximum (शेष) CDV */
#घोषणा ATM_NOT_RSV_VCI		    32	/* first non-reserved VCI value */

#घोषणा ATM_MAX_VPI		   255	/* maximum VPI at the UNI */
#घोषणा ATM_MAX_VPI_NNI		  4096	/* maximum VPI at the NNI */
#घोषणा ATM_MAX_VCI		 65535	/* maximum VCI */


/* "protcol" values क्रम the socket प्रणाली call */
#घोषणा ATM_NO_AAL	0		/* AAL not specअगरied */
#घोषणा ATM_AAL0	13		/* "raw" ATM cells */
#घोषणा ATM_AAL1	1		/* AAL1 (CBR) */
#घोषणा ATM_AAL2	2		/* AAL2 (VBR) */
#घोषणा ATM_AAL34	3		/* AAL3/4 (data) */
#घोषणा ATM_AAL5	5		/* AAL5 (data) */

/*
 * socket option name coding functions
 *
 * Note that __SO_ENCODE and __SO_LEVEL are somewhat a hack since the
 * << 22 only reserves 9 bits क्रम the level.  On some architectures
 * SOL_SOCKET is 0xFFFF, so that's a bit of a problem
 */

#घोषणा __SO_ENCODE(l,n,t)	((((l) & 0x1FF) << 22) | ((n) << 16) | \
				माप(t))
#घोषणा __SO_LEVEL_MATCH(c,m)	(((c) >> 22) == ((m) & 0x1FF))
#घोषणा __SO_NUMBER(c)		(((c) >> 16) & 0x3f)
#घोषणा __SO_SIZE(c)		((c) & 0x3fff)

/*
 * ATM layer
 */

#घोषणा SO_SETCLP	__SO_ENCODE(SOL_ATM,0,पूर्णांक)
			    /* set CLP bit value - TODO */
#घोषणा SO_CIRANGE	__SO_ENCODE(SOL_ATM,1,काष्ठा aपंचांग_cirange)
			    /* connection identअगरier range; socket must be
			       bound or connected */
#घोषणा SO_ATMQOS	__SO_ENCODE(SOL_ATM,2,काष्ठा aपंचांग_qos)
			    /* Quality of Service setting */
#घोषणा SO_ATMSAP	__SO_ENCODE(SOL_ATM,3,काष्ठा aपंचांग_sap)
			    /* Service Access Poपूर्णांक */
#घोषणा SO_ATMPVC	__SO_ENCODE(SOL_ATM,4,काष्ठा sockaddr_aपंचांगpvc)
			    /* "PVC" address (also क्रम SVCs); get only */
#घोषणा SO_MULTIPOINT	__SO_ENCODE(SOL_ATM, 5, पूर्णांक)
			    /* make this vc a p2mp */


/*
 * Note @@@: since the socket layers करोn't really distinguish the control and
 * the data plane but generally seems to be data plane-centric, any layer is
 * about equally wrong क्रम the SAP. If you have a better idea about this,
 * please speak up ...
 */


/* ATM cell header (क्रम AAL0) */

/* BEGIN_CH */
#घोषणा ATM_HDR_GFC_MASK	0xf0000000
#घोषणा ATM_HDR_GFC_SHIFT	28
#घोषणा ATM_HDR_VPI_MASK	0x0ff00000
#घोषणा ATM_HDR_VPI_SHIFT	20
#घोषणा ATM_HDR_VCI_MASK	0x000ffff0
#घोषणा ATM_HDR_VCI_SHIFT	4
#घोषणा ATM_HDR_PTI_MASK	0x0000000e
#घोषणा ATM_HDR_PTI_SHIFT	1
#घोषणा ATM_HDR_CLP		0x00000001
/* END_CH */


/* PTI codings */

/* BEGIN_PTI */
#घोषणा ATM_PTI_US0	0  /* user data cell, congestion not exp, SDU-type 0 */
#घोषणा ATM_PTI_US1	1  /* user data cell, congestion not exp, SDU-type 1 */
#घोषणा ATM_PTI_UCES0	2  /* user data cell, cong. experienced, SDU-type 0 */
#घोषणा ATM_PTI_UCES1	3  /* user data cell, cong. experienced, SDU-type 1 */
#घोषणा ATM_PTI_SEGF5	4  /* segment OAM F5 flow related cell */
#घोषणा ATM_PTI_E2EF5	5  /* end-to-end OAM F5 flow related cell */
#घोषणा ATM_PTI_RSV_RM	6  /* reserved क्रम traffic control/resource mgmt */
#घोषणा ATM_PTI_RSV	7  /* reserved */
/* END_PTI */


/*
 * The following items should stay in linux/aपंचांग.h, which should be linked to
 * netaपंचांग/aपंचांग.h
 */

/* Traffic description */

#घोषणा ATM_NONE	0		/* no traffic */
#घोषणा ATM_UBR		1
#घोषणा ATM_CBR		2
#घोषणा ATM_VBR		3
#घोषणा ATM_ABR		4
#घोषणा ATM_ANYCLASS	5		/* compatible with everything */

#घोषणा ATM_MAX_PCR	-1		/* maximum available PCR */

काष्ठा aपंचांग_trafprm अणु
	अचिन्हित अक्षर	traffic_class;	/* traffic class (ATM_UBR, ...) */
	पूर्णांक		max_pcr;	/* maximum PCR in cells per second */
	पूर्णांक		pcr;		/* desired PCR in cells per second */
	पूर्णांक		min_pcr;	/* minimum PCR in cells per second */
	पूर्णांक		max_cdv;	/* maximum CDV in microseconds */
	पूर्णांक		max_sdu;	/* maximum SDU in bytes */
        /* extra params क्रम ABR */
        अचिन्हित पूर्णांक 	icr;         	/* Initial Cell Rate (24-bit) */
        अचिन्हित पूर्णांक	tbe;		/* Transient Buffer Exposure (24-bit) */ 
        अचिन्हित पूर्णांक 	frtt : 24;	/* Fixed Round Trip Time (24-bit) */
        अचिन्हित पूर्णांक 	rअगर  : 4;       /* Rate Increment Factor (4-bit) */
        अचिन्हित पूर्णांक 	rdf  : 4;       /* Rate Decrease Factor (4-bit) */
        अचिन्हित पूर्णांक nrm_pres  :1;      /* nrm present bit */
        अचिन्हित पूर्णांक trm_pres  :1;     	/* rm present bit */
        अचिन्हित पूर्णांक adtf_pres :1;     	/* adtf present bit */
        अचिन्हित पूर्णांक cdf_pres  :1;    	/* cdf present bit*/
        अचिन्हित पूर्णांक nrm       :3;     	/* Max # of Cells क्रम each क्रमward RM cell (3-bit) */
        अचिन्हित पूर्णांक trm       :3;    	/* Time between क्रमward RM cells (3-bit) */    
	अचिन्हित पूर्णांक adtf      :10;     /* ACR Decrease Time Factor (10-bit) */
	अचिन्हित पूर्णांक cdf       :3;      /* Cutoff Decrease Factor (3-bit) */
        अचिन्हित पूर्णांक spare     :9;      /* spare bits */ 
पूर्ण;

काष्ठा aपंचांग_qos अणु
	काष्ठा aपंचांग_trafprm txtp;	/* parameters in TX direction */
	काष्ठा aपंचांग_trafprm rxtp __ATM_API_ALIGN;
					/* parameters in RX direction */
	अचिन्हित अक्षर aal __ATM_API_ALIGN;
पूर्ण;

/* PVC addressing */

#घोषणा ATM_ITF_ANY	-1		/* "magic" PVC address values */
#घोषणा ATM_VPI_ANY	-1
#घोषणा ATM_VCI_ANY	-1
#घोषणा ATM_VPI_UNSPEC	-2
#घोषणा ATM_VCI_UNSPEC	-2


काष्ठा sockaddr_aपंचांगpvc अणु
	अचिन्हित लघु 	sap_family;	/* address family, AF_ATMPVC  */
	काष्ठा अणु			/* PVC address */
		लघु	itf;		/* ATM पूर्णांकerface */
		लघु	vpi;		/* VPI (only 8 bits at UNI) */
		पूर्णांक	vci;		/* VCI (only 16 bits at UNI) */
	पूर्ण sap_addr __ATM_API_ALIGN;	/* PVC address */
पूर्ण;

/* SVC addressing */

#घोषणा	ATM_ESA_LEN	20		/* ATM End System Address length */
#घोषणा ATM_E164_LEN	12		/* maximum E.164 number length */

#घोषणा ATM_AFI_DCC	0x39		/* DCC ATM Format */
#घोषणा ATM_AFI_ICD	0x47		/* ICD ATM Format */
#घोषणा ATM_AFI_E164	0x45		/* E.164 ATM Format */
#घोषणा ATM_AFI_LOCAL	0x49		/* Local ATM Format */ 

#घोषणा ATM_AFI_DCC_GROUP	0xBD	/* DCC ATM Group Format */
#घोषणा ATM_AFI_ICD_GROUP	0xC5	/* ICD ATM Group Format */
#घोषणा ATM_AFI_E164_GROUP	0xC3	/* E.164 ATM Group Format */
#घोषणा ATM_AFI_LOCAL_GROUP	0xC7	/* Local ATM Group Format */

#घोषणा ATM_LIJ_NONE	0		/* no leaf-initiated join */
#घोषणा ATM_LIJ		1		/* request joining */
#घोषणा ATM_LIJ_RPJ	2		/* set to root-prompted join */
#घोषणा ATM_LIJ_NJ	3		/* set to network join */


काष्ठा sockaddr_aपंचांगsvc अणु
    अचिन्हित लघु 	sas_family;	/* address family, AF_ATMSVC */
    काष्ठा अणु				/* SVC address */
        अचिन्हित अक्षर	prv[ATM_ESA_LEN];/* निजी ATM address */
        अक्षर		pub[ATM_E164_LEN+1]; /* खुला address (E.164) */
    					/* unused addresses must be bzero'ed */
	अक्षर		lij_type;	/* role in LIJ call; one of ATM_LIJ* */
	__u32	lij_id;		/* LIJ call identअगरier */
    पूर्ण sas_addr __ATM_API_ALIGN;		/* SVC address */
पूर्ण;


अटल __अंतरभूत__ पूर्णांक aपंचांगsvc_addr_in_use(काष्ठा sockaddr_aपंचांगsvc addr)
अणु
	वापस *addr.sas_addr.prv || *addr.sas_addr.pub;
पूर्ण


अटल __अंतरभूत__ पूर्णांक aपंचांगpvc_addr_in_use(काष्ठा sockaddr_aपंचांगpvc addr)
अणु
	वापस addr.sap_addr.itf || addr.sap_addr.vpi || addr.sap_addr.vci;
पूर्ण


/*
 * Some stuff क्रम linux/sockios.h
 */

काष्ठा aपंचांगअगर_sioc अणु
	पूर्णांक number;
	पूर्णांक length;
	व्योम __user *arg;
पूर्ण;


प्रकार अचिन्हित लघु aपंचांग_backend_t;
#पूर्ण_अगर /* _UAPI_LINUX_ATM_H */
