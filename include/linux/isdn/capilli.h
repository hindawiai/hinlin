<शैली गुरु>
/* $Id: capilli.h,v 1.1.2.2 2004/01/16 21:09:27 keil Exp $
 * 
 * Kernel CAPI 2.0 Driver Interface क्रम Linux
 * 
 * Copyright 1999 by Carsten Paeth <calle@calle.de>
 * 
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 */

#अगर_अघोषित __CAPILLI_H__
#घोषणा __CAPILLI_H__

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/capi.h>
#समावेश <linux/kernelcapi.h>

प्रकार काष्ठा capiloaddatapart अणु
	पूर्णांक user;		/* data in userspace ? */
	पूर्णांक len;
	अचिन्हित अक्षर *data;
पूर्ण capiloaddatapart;

प्रकार काष्ठा capiloaddata अणु
	capiloaddatapart firmware;
	capiloaddatapart configuration;
पूर्ण capiloaddata;

प्रकार काष्ठा capicardparams अणु
	अचिन्हित पूर्णांक port;
	अचिन्हित irq;
	पूर्णांक cardtype;
	पूर्णांक cardnr;
	अचिन्हित पूर्णांक membase;
पूर्ण capicardparams;

काष्ठा capi_ctr अणु
	/* filled in beक्रमe calling attach_capi_ctr */
	काष्ठा module *owner;
	व्योम *driverdata;			/* driver specअगरic */
	अक्षर name[32];				/* name of controller */
	अक्षर *driver_name;			/* name of driver */
	पूर्णांक (*load_firmware)(काष्ठा capi_ctr *, capiloaddata *);
	व्योम (*reset_ctr)(काष्ठा capi_ctr *);
	व्योम (*रेजिस्टर_appl)(काष्ठा capi_ctr *, u16 appl,
			      capi_रेजिस्टर_params *);
	व्योम (*release_appl)(काष्ठा capi_ctr *, u16 appl);
	u16  (*send_message)(काष्ठा capi_ctr *, काष्ठा sk_buff *skb);
	
	अक्षर *(*procinfo)(काष्ठा capi_ctr *);
	पूर्णांक (*proc_show)(काष्ठा seq_file *, व्योम *);

	/* filled in beक्रमe calling पढ़ोy callback */
	u8 manu[CAPI_MANUFACTURER_LEN];		/* CAPI_GET_MANUFACTURER */
	capi_version version;			/* CAPI_GET_VERSION */
	capi_profile profile;			/* CAPI_GET_PROखाता */
	u8 serial[CAPI_SERIAL_LEN];		/* CAPI_GET_SERIAL */

	/* management inक्रमmation क्रम kcapi */

	अचिन्हित दीर्घ nrecvctlpkt;
	अचिन्हित दीर्घ nrecvdatapkt;
	अचिन्हित दीर्घ nsentctlpkt;
	अचिन्हित दीर्घ nsentdatapkt;

	पूर्णांक cnr;				/* controller number */
	अचिन्हित लघु state;			/* controller state */
	पूर्णांक blocked;				/* output blocked */
	पूर्णांक traceflag;				/* capi trace */

	काष्ठा proc_dir_entry *procent;
        अक्षर procfn[128];
पूर्ण;

पूर्णांक attach_capi_ctr(काष्ठा capi_ctr *);
पूर्णांक detach_capi_ctr(काष्ठा capi_ctr *);

व्योम capi_ctr_पढ़ोy(काष्ठा capi_ctr * card);
व्योम capi_ctr_करोwn(काष्ठा capi_ctr * card);
व्योम capi_ctr_handle_message(काष्ठा capi_ctr * card, u16 appl, काष्ठा sk_buff *skb);

// ---------------------------------------------------------------------------
// needed क्रम AVM capi drivers

काष्ठा capi_driver अणु
	अक्षर name[32];				/* driver name */
	अक्षर revision[32];

	/* management inक्रमmation क्रम kcapi */
	काष्ठा list_head list; 
पूर्ण;

#पूर्ण_अगर				/* __CAPILLI_H__ */
