<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (C) 2003 Deep Blue Solutions, Ltd, All Rights Reserved.
 *
 *  Support functions क्रम calculating घड़ीs/भागisors क्रम the ICST
 *  घड़ी generators.  See https://www.idt.com/ क्रम more inक्रमmation
 *  on these devices.
 */
#अगर_अघोषित ICST_H
#घोषणा ICST_H

काष्ठा icst_params अणु
	अचिन्हित दीर्घ	ref;
	अचिन्हित दीर्घ	vco_max;	/* inclusive */
	अचिन्हित दीर्घ	vco_min;	/* exclusive */
	अचिन्हित लघु	vd_min;		/* inclusive */
	अचिन्हित लघु	vd_max;		/* inclusive */
	अचिन्हित अक्षर	rd_min;		/* inclusive */
	अचिन्हित अक्षर	rd_max;		/* inclusive */
	स्थिर अचिन्हित अक्षर *s2भाग;	/* chip specअगरic s2भाग array */
	स्थिर अचिन्हित अक्षर *idx2s;	/* chip specअगरic idx2s array */
पूर्ण;

काष्ठा icst_vco अणु
	अचिन्हित लघु	v;
	अचिन्हित अक्षर	r;
	अचिन्हित अक्षर	s;
पूर्ण;

अचिन्हित दीर्घ icst_hz(स्थिर काष्ठा icst_params *p, काष्ठा icst_vco vco);
काष्ठा icst_vco icst_hz_to_vco(स्थिर काष्ठा icst_params *p, अचिन्हित दीर्घ freq);

/*
 * ICST307 VCO frequency must be between 6MHz and 200MHz (3.3 or 5V).
 * This frequency is pre-output भागider.
 */
#घोषणा ICST307_VCO_MIN	6000000
#घोषणा ICST307_VCO_MAX	200000000

बाह्य स्थिर अचिन्हित अक्षर icst307_s2भाग[];
बाह्य स्थिर अचिन्हित अक्षर icst307_idx2s[];

/*
 * ICST525 VCO frequency must be between 10MHz and 200MHz (3V) or 320MHz (5V).
 * This frequency is pre-output भागider.
 */
#घोषणा ICST525_VCO_MIN		10000000
#घोषणा ICST525_VCO_MAX_3V	200000000
#घोषणा ICST525_VCO_MAX_5V	320000000

बाह्य स्थिर अचिन्हित अक्षर icst525_s2भाग[];
बाह्य स्थिर अचिन्हित अक्षर icst525_idx2s[];

#पूर्ण_अगर
