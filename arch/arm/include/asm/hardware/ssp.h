<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  ssp.h
 *
 *  Copyright (C) 2003 Russell King, All Rights Reserved.
 */
#अगर_अघोषित SSP_H
#घोषणा SSP_H

काष्ठा ssp_state अणु
	अचिन्हित पूर्णांक	cr0;
	अचिन्हित पूर्णांक	cr1;
पूर्ण;

पूर्णांक ssp_ग_लिखो_word(u16 data);
पूर्णांक ssp_पढ़ो_word(u16 *data);
पूर्णांक ssp_flush(व्योम);
व्योम ssp_enable(व्योम);
व्योम ssp_disable(व्योम);
व्योम ssp_save_state(काष्ठा ssp_state *ssp);
व्योम ssp_restore_state(काष्ठा ssp_state *ssp);
पूर्णांक ssp_init(व्योम);
व्योम ssp_निकास(व्योम);

#पूर्ण_अगर
