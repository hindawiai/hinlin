<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* aपंचांगdev.h - ATM device driver declarations and various related items */
 
/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
 

#अगर_अघोषित _UAPILINUX_ATMDEV_H
#घोषणा _UAPILINUX_ATMDEV_H


#समावेश <linux/aपंचांगapi.h>
#समावेश <linux/aपंचांग.h>
#समावेश <linux/aपंचांगioc.h>


#घोषणा ESI_LEN		6

#घोषणा ATM_OC3_PCR	(155520000/270*260/8/53)
			/* OC3 link rate:  155520000 bps
			   SONET overhead: /270*260 (9 section, 1 path)
			   bits per cell:  /8/53
			   max cell rate:  353207.547 cells/sec */
#घोषणा ATM_25_PCR	((25600000/8-8000)/54)
			/* 25 Mbps ATM cell rate (59111) */
#घोषणा ATM_OC12_PCR	(622080000/1080*1040/8/53)
			/* OC12 link rate: 622080000 bps
			   SONET overhead: /1080*1040
			   bits per cell:  /8/53
			   max cell rate:  1412830.188 cells/sec */
#घोषणा ATM_DS3_PCR	(8000*12)
			/* DS3: 12 cells in a 125 usec समय slot */


#घोषणा __AAL_STAT_ITEMS \
    __HANDLE_ITEM(tx);			/* TX okay */ \
    __HANDLE_ITEM(tx_err);		/* TX errors */ \
    __HANDLE_ITEM(rx);			/* RX okay */ \
    __HANDLE_ITEM(rx_err);		/* RX errors */ \
    __HANDLE_ITEM(rx_drop);		/* RX out of memory */

काष्ठा aपंचांग_aal_stats अणु
#घोषणा __HANDLE_ITEM(i) पूर्णांक i
	__AAL_STAT_ITEMS
#अघोषित __HANDLE_ITEM
पूर्ण;


काष्ठा aपंचांग_dev_stats अणु
	काष्ठा aपंचांग_aal_stats aal0;
	काष्ठा aपंचांग_aal_stats aal34;
	काष्ठा aपंचांग_aal_stats aal5;
पूर्ण __ATM_API_ALIGN;


#घोषणा ATM_GETLINKRATE	_IOW('a',ATMIOC_ITF+1,काष्ठा aपंचांगअगर_sioc)
					/* get link rate */
#घोषणा ATM_GETNAMES	_IOW('a',ATMIOC_ITF+3,काष्ठा aपंचांग_iobuf)
					/* get पूर्णांकerface names (numbers) */
#घोषणा ATM_GETTYPE	_IOW('a',ATMIOC_ITF+4,काष्ठा aपंचांगअगर_sioc)
					/* get पूर्णांकerface type name */
#घोषणा ATM_GETESI	_IOW('a',ATMIOC_ITF+5,काष्ठा aपंचांगअगर_sioc)
					/* get पूर्णांकerface ESI */
#घोषणा ATM_GETADDR	_IOW('a',ATMIOC_ITF+6,काष्ठा aपंचांगअगर_sioc)
					/* get itf's local ATM addr. list */
#घोषणा ATM_RSTADDR	_IOW('a',ATMIOC_ITF+7,काष्ठा aपंचांगअगर_sioc)
					/* reset itf's ATM address list */
#घोषणा ATM_ADDADDR	_IOW('a',ATMIOC_ITF+8,काष्ठा aपंचांगअगर_sioc)
					/* add a local ATM address */
#घोषणा ATM_DELADDR	_IOW('a',ATMIOC_ITF+9,काष्ठा aपंचांगअगर_sioc)
					/* हटाओ a local ATM address */
#घोषणा ATM_GETCIRANGE	_IOW('a',ATMIOC_ITF+10,काष्ठा aपंचांगअगर_sioc)
					/* get connection identअगरier range */
#घोषणा ATM_SETCIRANGE	_IOW('a',ATMIOC_ITF+11,काष्ठा aपंचांगअगर_sioc)
					/* set connection identअगरier range */
#घोषणा ATM_SETESI	_IOW('a',ATMIOC_ITF+12,काष्ठा aपंचांगअगर_sioc)
					/* set पूर्णांकerface ESI */
#घोषणा ATM_SETESIF	_IOW('a',ATMIOC_ITF+13,काष्ठा aपंचांगअगर_sioc)
					/* क्रमce पूर्णांकerface ESI */
#घोषणा ATM_ADDLECSADDR	_IOW('a', ATMIOC_ITF+14, काष्ठा aपंचांगअगर_sioc)
					/* रेजिस्टर a LECS address */
#घोषणा ATM_DELLECSADDR	_IOW('a', ATMIOC_ITF+15, काष्ठा aपंचांगअगर_sioc)
					/* unरेजिस्टर a LECS address */
#घोषणा ATM_GETLECSADDR	_IOW('a', ATMIOC_ITF+16, काष्ठा aपंचांगअगर_sioc)
					/* retrieve LECS address(es) */

#घोषणा ATM_GETSTAT	_IOW('a',ATMIOC_SARCOM+0,काष्ठा aपंचांगअगर_sioc)
					/* get AAL layer statistics */
#घोषणा ATM_GETSTATZ	_IOW('a',ATMIOC_SARCOM+1,काष्ठा aपंचांगअगर_sioc)
					/* get AAL layer statistics and zero */
#घोषणा ATM_GETLOOP	_IOW('a',ATMIOC_SARCOM+2,काष्ठा aपंचांगअगर_sioc)
					/* get loopback mode */
#घोषणा ATM_SETLOOP	_IOW('a',ATMIOC_SARCOM+3,काष्ठा aपंचांगअगर_sioc)
					/* set loopback mode */
#घोषणा ATM_QUERYLOOP	_IOW('a',ATMIOC_SARCOM+4,काष्ठा aपंचांगअगर_sioc)
					/* query supported loopback modes */
#घोषणा ATM_SETSC	_IOW('a',ATMIOC_SPECIAL+1,पूर्णांक)
					/* enable or disable single-copy */
#घोषणा ATM_SETBACKEND	_IOW('a',ATMIOC_SPECIAL+2,aपंचांग_backend_t)
					/* set backend handler */
#घोषणा ATM_NEWBACKENDIF _IOW('a',ATMIOC_SPECIAL+3,aपंचांग_backend_t)
					/* use backend to make new अगर */
#घोषणा ATM_ADDPARTY  	_IOW('a', ATMIOC_SPECIAL+4,काष्ठा aपंचांग_iobuf)
 					/* add party to p2mp call */
#अगर_घोषित CONFIG_COMPAT
/* It actually takes काष्ठा sockaddr_aपंचांगsvc, not काष्ठा aपंचांग_iobuf */
#घोषणा COMPAT_ATM_ADDPARTY  	_IOW('a', ATMIOC_SPECIAL+4,काष्ठा compat_aपंचांग_iobuf)
#पूर्ण_अगर
#घोषणा ATM_DROPPARTY 	_IOW('a', ATMIOC_SPECIAL+5,पूर्णांक)
					/* drop party from p2mp call */

/*
 * These are backend handkers that can be set via the ATM_SETBACKEND call
 * above.  In the future we may support dynamic loading of these - क्रम now,
 * they're just being used to share the ATMIOC_BACKEND ioctls
 */
#घोषणा ATM_BACKEND_RAW		0	
#घोषणा ATM_BACKEND_PPP		1	/* PPPoATM - RFC2364 */
#घोषणा ATM_BACKEND_BR2684	2	/* Bridged RFC1483/2684 */

/* क्रम ATM_GETTYPE */
#घोषणा ATM_ITFTYP_LEN	8	/* maximum length of पूर्णांकerface type name */

/*
 * Loopback modes क्रम ATM_अणुPHY,SARपूर्ण_अणुGET,SETपूर्णLOOP
 */

/* Poपूर्णांक of loopback				CPU-->SAR-->PHY-->line--> ... */
#घोषणा __ATM_LM_NONE	0	/* no loop back     ^     ^     ^      ^      */
#घोषणा __ATM_LM_AAL	1	/* loop back PDUs --'     |     |      |      */
#घोषणा __ATM_LM_ATM	2	/* loop back ATM cells ---'     |      |      */
/* RESERVED		4	loop back on PHY side  ---'		      */
#घोषणा __ATM_LM_PHY	8	/* loop back bits (digital) ----'      |      */
#घोषणा __ATM_LM_ANALOG 16	/* loop back the analog संकेत --------'      */

/* Direction of loopback */
#घोषणा __ATM_LM_MKLOC(n)	((n))	    /* Local (i.e. loop TX to RX) */
#घोषणा __ATM_LM_MKRMT(n)	((n) << 8)  /* Remote (i.e. loop RX to TX) */

#घोषणा __ATM_LM_XTLOC(n)	((n) & 0xff)
#घोषणा __ATM_LM_XTRMT(n)	(((n) >> 8) & 0xff)

#घोषणा ATM_LM_NONE	0	/* no loopback */

#घोषणा ATM_LM_LOC_AAL	__ATM_LM_MKLOC(__ATM_LM_AAL)
#घोषणा ATM_LM_LOC_ATM	__ATM_LM_MKLOC(__ATM_LM_ATM)
#घोषणा ATM_LM_LOC_PHY	__ATM_LM_MKLOC(__ATM_LM_PHY)
#घोषणा ATM_LM_LOC_ANALOG __ATM_LM_MKLOC(__ATM_LM_ANALOG)

#घोषणा ATM_LM_RMT_AAL	__ATM_LM_MKRMT(__ATM_LM_AAL)
#घोषणा ATM_LM_RMT_ATM	__ATM_LM_MKRMT(__ATM_LM_ATM)
#घोषणा ATM_LM_RMT_PHY	__ATM_LM_MKRMT(__ATM_LM_PHY)
#घोषणा ATM_LM_RMT_ANALOG __ATM_LM_MKRMT(__ATM_LM_ANALOG)

/*
 * Note: ATM_LM_LOC_* and ATM_LM_RMT_* can be combined, provided that
 * __ATM_LM_XTLOC(x) <= __ATM_LM_XTRMT(x)
 */


काष्ठा aपंचांग_iobuf अणु
	पूर्णांक length;
	व्योम __user *buffer;
पूर्ण;

/* क्रम ATM_GETCIRANGE / ATM_SETCIRANGE */

#घोषणा ATM_CI_MAX      -1              /* use maximum range of VPI/VCI */
 
काष्ठा aपंचांग_cirange अणु
	चिन्हित अक्षर	vpi_bits;	/* 1..8, ATM_CI_MAX (-1) क्रम maximum */
	चिन्हित अक्षर	vci_bits;	/* 1..16, ATM_CI_MAX (-1) क्रम maximum */
पूर्ण;

/* क्रम ATM_SETSC; actually taken from the ATM_VF number space */

#घोषणा ATM_SC_RX	1024		/* enable RX single-copy */
#घोषणा ATM_SC_TX	2048		/* enable TX single-copy */

#घोषणा ATM_BACKLOG_DEFAULT 32 /* अगर we get more, we're likely to समय out
				  anyway */

/* MF: change_qos (Modअगरy) flags */

#घोषणा ATM_MF_IMMED	 1	/* Block until change is effective */
#घोषणा ATM_MF_INC_RSV	 2	/* Change reservation on increase */
#घोषणा ATM_MF_INC_SHP	 4	/* Change shaping on increase */
#घोषणा ATM_MF_DEC_RSV	 8	/* Change reservation on decrease */
#घोषणा ATM_MF_DEC_SHP	16	/* Change shaping on decrease */
#घोषणा ATM_MF_BWD	32	/* Set the backward direction parameters */

#घोषणा ATM_MF_SET	(ATM_MF_INC_RSV | ATM_MF_INC_SHP | ATM_MF_DEC_RSV | \
			  ATM_MF_DEC_SHP | ATM_MF_BWD)

/*
 * ATM_VS_* are used to express VC state in a human-मित्रly way.
 */

#घोषणा ATM_VS_IDLE	0	/* VC is not used */
#घोषणा ATM_VS_CONNECTED 1	/* VC is connected */
#घोषणा ATM_VS_CLOSING	2	/* VC is closing */
#घोषणा ATM_VS_LISTEN	3	/* VC is listening क्रम incoming setups */
#घोषणा ATM_VS_INUSE	4	/* VC is in use (रेजिस्टरed with aपंचांगsigd) */
#घोषणा ATM_VS_BOUND	5	/* VC is bound */

#घोषणा ATM_VS2TXT_MAP \
    "IDLE", "CONNECTED", "CLOSING", "LISTEN", "INUSE", "BOUND"

#घोषणा ATM_VF2TXT_MAP \
    "ADDR",	"READY",	"PARTIAL",	"REGIS", \
    "RELEASED", "HASQOS",	"LISTEN",	"META", \
    "256",	"512",		"1024",		"2048", \
    "SESSION",	"HASSAP",	"BOUND",	"CLOSE"



#पूर्ण_अगर /* _UAPILINUX_ATMDEV_H */
