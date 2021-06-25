<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_CM4000_H_
#घोषणा _UAPI_CM4000_H_

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

#घोषणा	MAX_ATR			33

#घोषणा	CM4000_MAX_DEV		4

/* those two काष्ठाures are passed via ioctl() from/to userspace.  They are
 * used by existing userspace programs, so I kepth the awkward "bIFSD" naming
 * not to अवरोध compilation of userspace apps. -HW */

प्रकार काष्ठा atreq अणु
	__s32 atr_len;
	अचिन्हित अक्षर atr[64];
	__s32 घातer_act;
	अचिन्हित अक्षर bIFSD;
	अचिन्हित अक्षर bIFSC;
पूर्ण atreq_t;


/* what is particularly stupid in the original driver is the arch-dependent
 * member sizes. This leads to CONFIG_COMPAT अवरोधage, since 32bit userspace
 * will lay out the काष्ठाure members dअगरferently than the 64bit kernel.
 *
 * I've changed "ptsreq.protocol" from "unsigned long" to "__u32".
 * On 32bit this will make no dअगरference.  With 64bit kernels, it will make
 * 32bit apps work, too.
 */

प्रकार काष्ठा ptsreq अणु
	__u32 protocol; /*T=0: 2^0, T=1:  2^1*/
 	अचिन्हित अक्षर flags;
 	अचिन्हित अक्षर pts1;
 	अचिन्हित अक्षर pts2;
	अचिन्हित अक्षर pts3;
पूर्ण ptsreq_t;

#घोषणा	CM_IOC_MAGIC		'c'
#घोषणा	CM_IOC_MAXNR	        255

#घोषणा	CM_IOCGSTATUS		_IOR (CM_IOC_MAGIC, 0, अचिन्हित अक्षर *)
#घोषणा	CM_IOCGATR		_IOWR(CM_IOC_MAGIC, 1, atreq_t *)
#घोषणा	CM_IOCSPTS		_IOW (CM_IOC_MAGIC, 2, ptsreq_t *)
#घोषणा	CM_IOCSRDR		_IO  (CM_IOC_MAGIC, 3)
#घोषणा CM_IOCARDOFF            _IO  (CM_IOC_MAGIC, 4)

#घोषणा CM_IOSDBGLVL            _IOW(CM_IOC_MAGIC, 250, पूर्णांक*)

/* card and device states */
#घोषणा	CM_CARD_INSERTED		0x01
#घोषणा	CM_CARD_POWERED			0x02
#घोषणा	CM_ATR_PRESENT			0x04
#घोषणा	CM_ATR_VALID	 		0x08
#घोषणा	CM_STATE_VALID			0x0f
/* extra info only from CM4000 */
#घोषणा	CM_NO_READER			0x10
#घोषणा	CM_BAD_CARD			0x20


#पूर्ण_अगर /* _UAPI_CM4000_H_ */
