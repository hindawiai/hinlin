<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Hardware parameter area specअगरic to Sharp SL series devices
 *
 * Copyright (c) 2005 Riअक्षरd Purdie
 *
 * Based on Sharp's 2.4 kernel patches
 */

काष्ठा sharpsl_param_info अणु
  अचिन्हित पूर्णांक comadj_keyword;
  अचिन्हित पूर्णांक comadj;

  अचिन्हित पूर्णांक uuid_keyword;
  अचिन्हित अक्षर uuid[16];

  अचिन्हित पूर्णांक touch_keyword;
  अचिन्हित पूर्णांक touch_xp;
  अचिन्हित पूर्णांक touch_yp;
  अचिन्हित पूर्णांक touch_xd;
  अचिन्हित पूर्णांक touch_yd;

  अचिन्हित पूर्णांक adadj_keyword;
  अचिन्हित पूर्णांक adadj;

  अचिन्हित पूर्णांक phad_keyword;
  अचिन्हित पूर्णांक phadadj;
पूर्ण __attribute__((packed));


बाह्य काष्ठा sharpsl_param_info sharpsl_param;
बाह्य व्योम sharpsl_save_param(व्योम);

