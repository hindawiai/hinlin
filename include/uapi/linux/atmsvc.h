<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* aपंचांगsvc.h - ATM संकेतing kernel-demon पूर्णांकerface definitions */
 
/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
 

#अगर_अघोषित _LINUX_ATMSVC_H
#घोषणा _LINUX_ATMSVC_H

#समावेश <linux/aपंचांगapi.h>
#समावेश <linux/aपंचांग.h>
#समावेश <linux/aपंचांगioc.h>


#घोषणा ATMSIGD_CTRL _IO('a',ATMIOC_SPECIAL)
				/* become ATM संकेतing demon control socket */

क्रमागत aपंचांगsvc_msg_type अणु as_catch_null, as_bind, as_connect, as_accept, as_reject,
		       as_listen, as_okay, as_error, as_indicate, as_बंद,
		       as_itf_notअगरy, as_modअगरy, as_identअगरy, as_terminate,
		       as_addparty, as_dropparty पूर्ण;

काष्ठा aपंचांगsvc_msg अणु
	क्रमागत aपंचांगsvc_msg_type type;
	aपंचांग_kptr_t vcc;
	aपंचांग_kptr_t listen_vcc;		/* indicate */
	पूर्णांक reply;			/* क्रम okay and बंद:		   */
					/*   < 0: error beक्रमe active	   */
					/*        (sigd has discarded ctx) */
					/*   ==0: success		   */
				        /*   > 0: error when active (still */
					/*        need to बंद)	   */
	काष्ठा sockaddr_aपंचांगpvc pvc;	/* indicate, okay (connect) */
	काष्ठा sockaddr_aपंचांगsvc local;	/* local SVC address */
	काष्ठा aपंचांग_qos qos;		/* QOS parameters */
	काष्ठा aपंचांग_sap sap;		/* SAP */
	अचिन्हित पूर्णांक session;		/* क्रम p2pm */
	काष्ठा sockaddr_aपंचांगsvc svc;	/* SVC address */
पूर्ण __ATM_API_ALIGN;

/*
 * Message contents: see ftp://icaftp.epfl.ch/pub/linux/aपंचांग/करोcs/isp-*.tar.gz
 */

/*
 * Some policy stuff क्रम aपंचांगsigd and क्रम net/aपंचांग/svc.c. Both have to agree on
 * what PCR is used to request bandwidth from the device driver. net/aपंचांग/svc.c
 * tries to करो better than that, but only अगर there's no routing decision (i.e.
 * अगर संकेतing only uses one ATM पूर्णांकerface).
 */

#घोषणा SELECT_TOP_PCR(tp) ((tp).pcr ? (tp).pcr : \
  (tp).max_pcr && (tp).max_pcr != ATM_MAX_PCR ? (tp).max_pcr : \
  (tp).min_pcr ? (tp).min_pcr : ATM_MAX_PCR)

#पूर्ण_अगर
