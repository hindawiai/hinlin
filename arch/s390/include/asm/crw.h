<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *   Data definitions क्रम channel report processing
 *    Copyright IBM Corp. 2000, 2009
 *    Author(s): Ingo Adlung <adlung@de.ibm.com>,
 *		 Martin Schwidefsky <schwidefsky@de.ibm.com>,
 *		 Cornelia Huck <cornelia.huck@de.ibm.com>,
 *		 Heiko Carstens <heiko.carstens@de.ibm.com>,
 */

#अगर_अघोषित _ASM_S390_CRW_H
#घोषणा _ASM_S390_CRW_H

#समावेश <linux/types.h>

/*
 * Channel Report Word
 */
काष्ठा crw अणु
	__u32 res1 :  1;   /* reserved zero */
	__u32 slct :  1;   /* solicited */
	__u32 oflw :  1;   /* overflow */
	__u32 chn  :  1;   /* chained */
	__u32 rsc  :  4;   /* reporting source code */
	__u32 anc  :  1;   /* ancillary report */
	__u32 res2 :  1;   /* reserved zero */
	__u32 erc  :  6;   /* error-recovery code */
	__u32 rsid : 16;   /* reporting-source ID */
पूर्ण __attribute__ ((packed));

प्रकार व्योम (*crw_handler_t)(काष्ठा crw *, काष्ठा crw *, पूर्णांक);

बाह्य पूर्णांक crw_रेजिस्टर_handler(पूर्णांक rsc, crw_handler_t handler);
बाह्य व्योम crw_unरेजिस्टर_handler(पूर्णांक rsc);
बाह्य व्योम crw_handle_channel_report(व्योम);
व्योम crw_रुको_क्रम_channel_report(व्योम);

#घोषणा NR_RSCS 16

#घोषणा CRW_RSC_MONITOR  0x2  /* monitoring facility */
#घोषणा CRW_RSC_SCH	 0x3  /* subchannel */
#घोषणा CRW_RSC_CPATH	 0x4  /* channel path */
#घोषणा CRW_RSC_CONFIG	 0x9  /* configuration-alert facility */
#घोषणा CRW_RSC_CSS	 0xB  /* channel subप्रणाली */

#घोषणा CRW_ERC_EVENT	 0x00 /* event inक्रमmation pending */
#घोषणा CRW_ERC_AVAIL	 0x01 /* available */
#घोषणा CRW_ERC_INIT	 0x02 /* initialized */
#घोषणा CRW_ERC_TERROR	 0x03 /* temporary error */
#घोषणा CRW_ERC_IPARM	 0x04 /* installed parm initialized */
#घोषणा CRW_ERC_TERM	 0x05 /* terminal */
#घोषणा CRW_ERC_PERRN	 0x06 /* perm. error, fac. not init */
#घोषणा CRW_ERC_PERRI	 0x07 /* perm. error, facility init */
#घोषणा CRW_ERC_PMOD	 0x08 /* installed parameters modअगरied */

#पूर्ण_अगर /* _ASM_S390_CRW_H */
