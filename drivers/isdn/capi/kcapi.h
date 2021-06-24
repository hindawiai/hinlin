<शैली गुरु>
/*
 * Kernel CAPI 2.0 Module
 *
 * Copyright 1999 by Carsten Paeth <calle@calle.de>
 * Copyright 2002 by Kai Germaschewski <kai@germaschewski.name>
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 */


#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/isdn/capilli.h>

#अगर_घोषित KCAPI_DEBUG
#घोषणा DBG(क्रमmat, arg...) करो अणु					\
		prपूर्णांकk(KERN_DEBUG "%s: " क्रमmat "\n" , __func__ , ## arg); \
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा DBG(क्रमmat, arg...) /* */
#पूर्ण_अगर

क्रमागत अणु
	CAPI_CTR_DETACHED = 0,
	CAPI_CTR_DETECTED = 1,
	CAPI_CTR_LOADING  = 2,
	CAPI_CTR_RUNNING  = 3,
पूर्ण;

बाह्य काष्ठा capi_ctr *capi_controller[CAPI_MAXCONTR];
बाह्य काष्ठा mutex capi_controller_lock;

बाह्य काष्ठा capi20_appl *capi_applications[CAPI_MAXAPPL];

व्योम kcapi_proc_init(व्योम);
व्योम kcapi_proc_निकास(व्योम);

काष्ठा capi20_appl अणु
	u16 applid;
	capi_रेजिस्टर_params rparam;
	व्योम (*recv_message)(काष्ठा capi20_appl *ap, काष्ठा sk_buff *skb);
	व्योम *निजी;

	/* पूर्णांकernal to kernelcapi.o */
	अचिन्हित दीर्घ nrecvctlpkt;
	अचिन्हित दीर्घ nrecvdatapkt;
	अचिन्हित दीर्घ nsentctlpkt;
	अचिन्हित दीर्घ nsentdatapkt;
	काष्ठा mutex recv_mtx;
	काष्ठा sk_buff_head recv_queue;
	काष्ठा work_काष्ठा recv_work;
	पूर्णांक release_in_progress;
पूर्ण;

u16 capi20_isinstalled(व्योम);
u16 capi20_रेजिस्टर(काष्ठा capi20_appl *ap);
u16 capi20_release(काष्ठा capi20_appl *ap);
u16 capi20_put_message(काष्ठा capi20_appl *ap, काष्ठा sk_buff *skb);
u16 capi20_get_manufacturer(u32 contr, u8 buf[CAPI_MANUFACTURER_LEN]);
u16 capi20_get_version(u32 contr, काष्ठा capi_version *verp);
u16 capi20_get_serial(u32 contr, u8 serial[CAPI_SERIAL_LEN]);
u16 capi20_get_profile(u32 contr, काष्ठा capi_profile *profp);
पूर्णांक capi20_manufacturer(अचिन्हित दीर्घ cmd, व्योम __user *data);

#घोषणा CAPICTR_UP			0
#घोषणा CAPICTR_DOWN			1

पूर्णांक kcapi_init(व्योम);
व्योम kcapi_निकास(व्योम);

/*----- basic-type definitions -----*/

प्रकार __u8 *_cकाष्ठा;

प्रकार क्रमागत अणु
	CAPI_COMPOSE,
	CAPI_DEFAULT
पूर्ण _cmकाष्ठा;

/*
   The _cmsg काष्ठाure contains all possible CAPI 2.0 parameter.
   All parameters are stored here first. The function CAPI_CMSG_2_MESSAGE
   assembles the parameter and builds CAPI2.0 conक्रमm messages.
   CAPI_MESSAGE_2_CMSG disassembles CAPI 2.0 messages and stores the
   parameter in the _cmsg काष्ठाure
 */

प्रकार काष्ठा अणु
	/* Header */
	__u16 ApplId;
	__u8 Command;
	__u8 Subcommand;
	__u16 Messagक्रमागतber;

	/* Parameter */
	जोड़ अणु
		__u32 adrController;
		__u32 adrPLCI;
		__u32 adrNCCI;
	पूर्ण adr;

	_cmकाष्ठा AdditionalInfo;
	_cकाष्ठा B1configuration;
	__u16 B1protocol;
	_cकाष्ठा B2configuration;
	__u16 B2protocol;
	_cकाष्ठा B3configuration;
	__u16 B3protocol;
	_cकाष्ठा BC;
	_cकाष्ठा BChannelinक्रमmation;
	_cmकाष्ठा BProtocol;
	_cकाष्ठा CalledPartyNumber;
	_cकाष्ठा CalledPartySubaddress;
	_cकाष्ठा CallingPartyNumber;
	_cकाष्ठा CallingPartySubaddress;
	__u32 CIPmask;
	__u32 CIPmask2;
	__u16 CIPValue;
	__u32 Class;
	_cकाष्ठा ConnectedNumber;
	_cकाष्ठा ConnectedSubaddress;
	__u32 Data;
	__u16 DataHandle;
	__u16 DataLength;
	_cकाष्ठा FacilityConfirmationParameter;
	_cकाष्ठा Facilitydataarray;
	_cकाष्ठा FacilityIndicationParameter;
	_cकाष्ठा FacilityRequestParameter;
	__u16 FacilitySelector;
	__u16 Flags;
	__u32 Function;
	_cकाष्ठा HLC;
	__u16 Info;
	_cकाष्ठा InfoElement;
	__u32 InfoMask;
	__u16 InfoNumber;
	_cकाष्ठा Keypadfacility;
	_cकाष्ठा LLC;
	_cकाष्ठा ManuData;
	__u32 ManuID;
	_cकाष्ठा NCPI;
	__u16 Reason;
	__u16 Reason_B3;
	__u16 Reject;
	_cकाष्ठा Useruserdata;

	/* पूर्णांकern */
	अचिन्हित l, p;
	अचिन्हित अक्षर *par;
	__u8 *m;

	/* buffer to स्थिरruct message */
	__u8 buf[180];

पूर्ण _cmsg;

/*-----------------------------------------------------------------------*/

/*
 * Debugging / Tracing functions
 */

अक्षर *capi_cmd2str(__u8 cmd, __u8 subcmd);

प्रकार काष्ठा अणु
	u_अक्षर	*buf;
	u_अक्षर	*p;
	माप_प्रकार	size;
	माप_प्रकार	pos;
पूर्ण _cdebbuf;

#घोषणा	CDEBUG_SIZE	1024
#घोषणा	CDEBUG_GSIZE	4096

व्योम cdebbuf_मुक्त(_cdebbuf *cdb);
पूर्णांक cdebug_init(व्योम);
व्योम cdebug_निकास(व्योम);

_cdebbuf *capi_message2str(__u8 *msg);
