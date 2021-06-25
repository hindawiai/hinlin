<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 */
#अगर_अघोषित __PVRUSB2_DEBUGIFC_H
#घोषणा __PVRUSB2_DEBUGIFC_H

काष्ठा pvr2_hdw;

/* Prपूर्णांक general status of driver.  This will also trigger a probe of
   the USB link.  Unlike prपूर्णांक_info(), this one synchronizes with the
   driver so the inक्रमmation should be self-consistent (but it will
   hang अगर the driver is wedged). */
पूर्णांक pvr2_debugअगरc_prपूर्णांक_info(काष्ठा pvr2_hdw *,
			     अक्षर *buf_ptr, अचिन्हित पूर्णांक buf_size);

/* Non-पूर्णांकrusively prपूर्णांक some useful debugging info from inside the
   driver.  This should work even अगर the driver appears to be
   wedged. */
पूर्णांक pvr2_debugअगरc_prपूर्णांक_status(काष्ठा pvr2_hdw *,
			       अक्षर *buf_ptr,अचिन्हित पूर्णांक buf_size);

/* Parse a string command पूर्णांकo a driver action. */
पूर्णांक pvr2_debugअगरc_करोcmd(काष्ठा pvr2_hdw *,
			स्थिर अक्षर *buf_ptr,अचिन्हित पूर्णांक buf_size);

#पूर्ण_अगर /* __PVRUSB2_DEBUGIFC_H */
