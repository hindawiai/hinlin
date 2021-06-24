<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* arch/arm/plat-samsung/include/plat/usb-control.h
 *
 * Copyright (c) 2004 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C - USB host port inक्रमmation
*/

#अगर_अघोषित __ASM_ARCH_USBCONTROL_H
#घोषणा __ASM_ARCH_USBCONTROL_H

#घोषणा S3C_HCDFLG_USED	(1)

काष्ठा s3c2410_hcd_port अणु
	अचिन्हित अक्षर	flags;
	अचिन्हित अक्षर	घातer;
	अचिन्हित अक्षर	oc_status;
	अचिन्हित अक्षर	oc_changed;
पूर्ण;

काष्ठा s3c2410_hcd_info अणु
	काष्ठा usb_hcd		*hcd;
	काष्ठा s3c2410_hcd_port	port[2];

	व्योम		(*घातer_control)(पूर्णांक port, पूर्णांक to);
	व्योम		(*enable_oc)(काष्ठा s3c2410_hcd_info *, पूर्णांक on);
	व्योम		(*report_oc)(काष्ठा s3c2410_hcd_info *, पूर्णांक ports);
पूर्ण;

अटल अंतरभूत व्योम s3c2410_usb_report_oc(काष्ठा s3c2410_hcd_info *info, पूर्णांक ports)
अणु
	अगर (info->report_oc != शून्य) अणु
		(info->report_oc)(info, ports);
	पूर्ण
पूर्ण

बाह्य व्योम s3c_ohci_set_platdata(काष्ठा s3c2410_hcd_info *info);

#पूर्ण_अगर /*__ASM_ARCH_USBCONTROL_H */
