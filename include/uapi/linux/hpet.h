<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__HPET__
#घोषणा _UAPI__HPET__

#समावेश <linux/compiler.h>


काष्ठा hpet_info अणु
	अचिन्हित दीर्घ hi_ireqfreq;	/* Hz */
	अचिन्हित दीर्घ hi_flags;	/* inक्रमmation */
	अचिन्हित लघु hi_hpet;
	अचिन्हित लघु hi_समयr;
पूर्ण;

#घोषणा HPET_INFO_PERIODIC	0x0010	/* periodic-capable comparator */

#घोषणा	HPET_IE_ON	_IO('h', 0x01)	/* पूर्णांकerrupt on */
#घोषणा	HPET_IE_OFF	_IO('h', 0x02)	/* पूर्णांकerrupt off */
#घोषणा	HPET_INFO	_IOR('h', 0x03, काष्ठा hpet_info)
#घोषणा	HPET_EPI	_IO('h', 0x04)	/* enable periodic */
#घोषणा	HPET_DPI	_IO('h', 0x05)	/* disable periodic */
#घोषणा	HPET_IRQFREQ	_IOW('h', 0x6, अचिन्हित दीर्घ)	/* IRQFREQ usec */

#घोषणा MAX_HPET_TBS	8		/* maximum hpet समयr blocks */

#पूर्ण_अगर /* _UAPI__HPET__ */
