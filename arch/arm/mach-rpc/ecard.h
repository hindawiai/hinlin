<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  ecard.h
 *
 *  Copyright 2007 Russell King
 */

/* Definitions पूर्णांकernal to ecard.c - क्रम it's use only!!
 *
 * External expansion card header as पढ़ो from the card
 */
काष्ठा ex_ecid अणु
	अचिन्हित अक्षर	r_irq:1;
	अचिन्हित अक्षर	r_zero:1;
	अचिन्हित अक्षर	r_fiq:1;
	अचिन्हित अक्षर	r_id:4;
	अचिन्हित अक्षर	r_a:1;

	अचिन्हित अक्षर	r_cd:1;
	अचिन्हित अक्षर	r_is:1;
	अचिन्हित अक्षर	r_w:2;
	अचिन्हित अक्षर	r_r1:4;

	अचिन्हित अक्षर	r_r2:8;

	अचिन्हित अक्षर	r_prod[2];

	अचिन्हित अक्षर	r_manu[2];

	अचिन्हित अक्षर	r_country;

	अचिन्हित अक्षर	r_fiqmask;
	अचिन्हित अक्षर	r_fiqoff[3];

	अचिन्हित अक्षर	r_irqmask;
	अचिन्हित अक्षर	r_irqoff[3];
पूर्ण;

/*
 * Chunk directory entry as पढ़ो from the card
 */
काष्ठा ex_chunk_dir अणु
	अचिन्हित अक्षर r_id;
	अचिन्हित अक्षर r_len[3];
	अचिन्हित दीर्घ r_start;
	जोड़ अणु
		अक्षर string[256];
		अक्षर data[1];
	पूर्ण d;
#घोषणा c_id(x)		((x)->r_id)
#घोषणा c_len(x)	((x)->r_len[0]|((x)->r_len[1]<<8)|((x)->r_len[2]<<16))
#घोषणा c_start(x)	((x)->r_start)
पूर्ण;

प्रकार क्रमागत ecard_type अणु		/* Cards address space		*/
	ECARD_IOC,
	ECARD_MEMC,
	ECARD_EASI
पूर्ण card_type_t;

प्रकार क्रमागत अणु				/* Speed क्रम ECARD_IOC space	*/
	ECARD_SLOW	 = 0,
	ECARD_MEDIUM	 = 1,
	ECARD_FAST	 = 2,
	ECARD_SYNC	 = 3
पूर्ण card_speed_t;
