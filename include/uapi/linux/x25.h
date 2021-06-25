<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * These are the खुला elements of the Linux kernel X.25 implementation.
 *
 * 	History
 *	mar/20/00	Daniela Squassoni Disabling/enabling of facilities 
 *					  negotiation.
 *	apr/02/05	Shaun Pereira Selective sub address matching with
 *					call user data
 */

#अगर_अघोषित	X25_KERNEL_H
#घोषणा	X25_KERNEL_H

#समावेश <linux/types.h>
#समावेश <linux/socket.h>

#घोषणा	SIOCX25GSUBSCRIP	(SIOCPROTOPRIVATE + 0)
#घोषणा	SIOCX25SSUBSCRIP	(SIOCPROTOPRIVATE + 1)
#घोषणा	SIOCX25GFACILITIES	(SIOCPROTOPRIVATE + 2)
#घोषणा	SIOCX25SFACILITIES	(SIOCPROTOPRIVATE + 3)
#घोषणा	SIOCX25GCALLUSERDATA	(SIOCPROTOPRIVATE + 4)
#घोषणा	SIOCX25SCALLUSERDATA	(SIOCPROTOPRIVATE + 5)
#घोषणा	SIOCX25GCAUSEDIAG	(SIOCPROTOPRIVATE + 6)
#घोषणा SIOCX25SCUDMATCHLEN	(SIOCPROTOPRIVATE + 7)
#घोषणा SIOCX25CALLACCPTAPPRV   (SIOCPROTOPRIVATE + 8)
#घोषणा SIOCX25SENDCALLACCPT    (SIOCPROTOPRIVATE + 9)
#घोषणा SIOCX25GDTEFACILITIES (SIOCPROTOPRIVATE + 10)
#घोषणा SIOCX25SDTEFACILITIES (SIOCPROTOPRIVATE + 11)
#घोषणा SIOCX25SCAUSEDIAG	(SIOCPROTOPRIVATE + 12)

/*
 *	Values क्रम अणुget,setपूर्णsockopt.
 */
#घोषणा	X25_QBITINCL		1

/*
 *	X.25 Packet Size values.
 */
#घोषणा	X25_PS16		4
#घोषणा	X25_PS32		5
#घोषणा	X25_PS64		6
#घोषणा	X25_PS128		7
#घोषणा	X25_PS256		8
#घोषणा	X25_PS512		9
#घोषणा	X25_PS1024		10
#घोषणा	X25_PS2048		11
#घोषणा	X25_PS4096		12

/*
 * An X.121 address, it is held as ASCII text, null terminated, up to 15
 * digits and a null terminator.
 */
काष्ठा x25_address अणु
	अक्षर x25_addr[16];
पूर्ण;

/*
 *	Linux X.25 Address काष्ठाure, used क्रम bind, and connect mostly.
 */
काष्ठा sockaddr_x25 अणु
	__kernel_sa_family_t sx25_family;	/* Must be AF_X25 */
	काष्ठा x25_address sx25_addr;		/* X.121 Address */
पूर्ण;

/*
 *	DTE/DCE subscription options.
 *
 *      As this is missing lots of options, user should expect major
 *	changes of this काष्ठाure in 2.5.x which might अवरोध compatibilty.
 *      The somewhat ugly dimension 200-माप() is needed to मुख्यtain
 *	backward compatibility.
 */
काष्ठा x25_subscrip_काष्ठा अणु
	अक्षर device[200-माप(अचिन्हित दीर्घ)];
	अचिन्हित दीर्घ	global_facil_mask;	/* 0 to disable negotiation */
	अचिन्हित पूर्णांक	extended;
पूर्ण;

/* values क्रम above global_facil_mask */

#घोषणा	X25_MASK_REVERSE	0x01	
#घोषणा	X25_MASK_THROUGHPUT	0x02
#घोषणा	X25_MASK_PACKET_SIZE	0x04
#घोषणा	X25_MASK_WINDOW_SIZE	0x08

#घोषणा X25_MASK_CALLING_AE 0x10
#घोषणा X25_MASK_CALLED_AE 0x20


/*
 *	Routing table control काष्ठाure.
 */
काष्ठा x25_route_काष्ठा अणु
	काष्ठा x25_address address;
	अचिन्हित पूर्णांक	   sigdigits;
	अक्षर		   device[200];
पूर्ण;

/*
 *	Facilities काष्ठाure.
 */
काष्ठा x25_facilities अणु
	अचिन्हित पूर्णांक	winsize_in, winsize_out;
	अचिन्हित पूर्णांक	pacsize_in, pacsize_out;
	अचिन्हित पूर्णांक	throughput;
	अचिन्हित पूर्णांक	reverse;
पूर्ण;

/*
* ITU DTE facilities
* Only the called and calling address
* extension are currently implemented.
* The rest are in place to aव्योम the काष्ठा
* changing size अगर someone needs them later
*/

काष्ठा x25_dte_facilities अणु
	__u16 delay_cumul;
	__u16 delay_target;
	__u16 delay_max;
	__u8 min_throughput;
	__u8 expedited;
	__u8 calling_len;
	__u8 called_len;
	__u8 calling_ae[20];
	__u8 called_ae[20];
पूर्ण;

/*
 *	Call User Data काष्ठाure.
 */
काष्ठा x25_calluserdata अणु
	अचिन्हित पूर्णांक	cudlength;
	अचिन्हित अक्षर	cuddata[128];
पूर्ण;

/*
 *	Call clearing Cause and Diagnostic काष्ठाure.
 */
काष्ठा x25_causediag अणु
	अचिन्हित अक्षर	cause;
	अचिन्हित अक्षर	diagnostic;
पूर्ण;

/*
 *	Further optional call user data match length selection
 */
काष्ठा x25_subaddr अणु
	अचिन्हित पूर्णांक cudmatchlength;
पूर्ण;

#पूर्ण_अगर
