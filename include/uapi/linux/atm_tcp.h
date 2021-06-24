<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* aपंचांग_tcp.h - Driver-specअगरic declarations of the ATMTCP driver (क्रम use by
	       driver-specअगरic utilities) */

/* Written 1997-2000 by Werner Almesberger, EPFL LRC/ICA */


#अगर_अघोषित _UAPILINUX_ATM_TCP_H
#घोषणा _UAPILINUX_ATM_TCP_H

#समावेश <linux/aपंचांगapi.h>
#समावेश <linux/aपंचांग.h>
#समावेश <linux/aपंचांगioc.h>
#समावेश <linux/types.h>


/*
 * All values in काष्ठा aपंचांगtcp_hdr are in network byte order
 */

काष्ठा aपंचांगtcp_hdr अणु
	__u16	vpi;
	__u16	vci;
	__u32	length;		/* ... of data part */
पूर्ण;

/*
 * All values in काष्ठा aपंचांगtcp_command are in host byte order
 */

#घोषणा ATMTCP_HDR_MAGIC	(~0)	/* this length indicates a command */
#घोषणा ATMTCP_CTRL_OPEN	1	/* request/reply */
#घोषणा ATMTCP_CTRL_CLOSE	2	/* request/reply */

काष्ठा aपंचांगtcp_control अणु
	काष्ठा aपंचांगtcp_hdr hdr;	/* must be first */
	पूर्णांक type;		/* message type; both directions */
	aपंचांग_kptr_t vcc;		/* both directions */
	काष्ठा sockaddr_aपंचांगpvc addr; /* suggested value from kernel */
	काष्ठा aपंचांग_qos	qos;	/* both directions */
	पूर्णांक result;		/* to kernel only */
पूर्ण __ATM_API_ALIGN;

/*
 * Field usage:
 * Messge type	dir.	hdr.v?i	type	addr	qos	vcc	result
 * -----------  ----	------- ----	----	---	---	------
 * OPEN		K->D	Y	Y	Y	Y	Y	0
 * OPEN		D->K	-	Y	Y	Y	Y	Y
 * CLOSE	K->D	-	-	Y	-	Y	0
 * CLOSE	D->K	-	-	-	-	Y	Y
 */

#घोषणा SIOCSIFATMTCP	_IO('a',ATMIOC_ITF)	/* set ATMTCP mode */
#घोषणा ATMTCP_CREATE	_IO('a',ATMIOC_ITF+14)	/* create persistent ATMTCP
						   पूर्णांकerface */
#घोषणा ATMTCP_REMOVE	_IO('a',ATMIOC_ITF+15)	/* destroy persistent ATMTCP
						   पूर्णांकerface */



#पूर्ण_अगर /* _UAPILINUX_ATM_TCP_H */
