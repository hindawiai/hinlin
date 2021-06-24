<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2020 Hewlett Packard Enterprise Development LP. All rights reserved.
 */

#अगर_अघोषित _ASM_UV_GEO_H
#घोषणा _ASM_UV_GEO_H

/* Type declarations */

/* Size of a geoid_s काष्ठाure (must be beक्रमe decl. of geoid_u) */
#घोषणा GEOID_SIZE	8

/* Fields common to all subकाष्ठाures */
काष्ठा geo_common_s अणु
	अचिन्हित अक्षर type;		/* What type of h/w is named by this geoid_s */
	अचिन्हित अक्षर blade;
	अचिन्हित अक्षर slot;		/* slot is IRU */
	अचिन्हित अक्षर upos;
	अचिन्हित अक्षर rack;
पूर्ण;

/* Additional fields क्रम particular types of hardware */
काष्ठा geo_node_s अणु
	काष्ठा geo_common_s common;		/* No additional fields needed */
पूर्ण;

काष्ठा geo_rtr_s अणु
	काष्ठा geo_common_s common;		/* No additional fields needed */
पूर्ण;

काष्ठा geo_iocntl_s अणु
	काष्ठा geo_common_s common;		/* No additional fields needed */
पूर्ण;

काष्ठा geo_pcicard_s अणु
	काष्ठा geo_iocntl_s common;
	अक्षर bus;				/* Bus/widget number */
	अक्षर slot;				/* PCI slot number */
पूर्ण;

/* Subcomponents of a node */
काष्ठा geo_cpu_s अणु
	काष्ठा geo_node_s node;
	अचिन्हित अक्षर	socket:4,	/* Which CPU on the node */
			thपढ़ो:4;
	अचिन्हित अक्षर	core;
पूर्ण;

काष्ठा geo_mem_s अणु
	काष्ठा geo_node_s node;
	अक्षर membus;			/* The memory bus on the node */
	अक्षर memslot;			/* The memory slot on the bus */
पूर्ण;

जोड़ geoid_u अणु
	काष्ठा geo_common_s common;
	काष्ठा geo_node_s node;
	काष्ठा geo_iocntl_s iocntl;
	काष्ठा geo_pcicard_s pcicard;
	काष्ठा geo_rtr_s rtr;
	काष्ठा geo_cpu_s cpu;
	काष्ठा geo_mem_s mem;
	अक्षर padsize[GEOID_SIZE];
पूर्ण;

/* Defined स्थिरants */

#घोषणा GEO_MAX_LEN	48

#घोषणा GEO_TYPE_INVALID	0
#घोषणा GEO_TYPE_MODULE		1
#घोषणा GEO_TYPE_NODE		2
#घोषणा GEO_TYPE_RTR		3
#घोषणा GEO_TYPE_IOCNTL		4
#घोषणा GEO_TYPE_IOCARD		5
#घोषणा GEO_TYPE_CPU		6
#घोषणा GEO_TYPE_MEM		7
#घोषणा GEO_TYPE_MAX		(GEO_TYPE_MEM+1)

अटल अंतरभूत पूर्णांक geo_rack(जोड़ geoid_u g)
अणु
	वापस (g.common.type == GEO_TYPE_INVALID) ?
		-1 : g.common.rack;
पूर्ण

अटल अंतरभूत पूर्णांक geo_slot(जोड़ geoid_u g)
अणु
	वापस (g.common.type == GEO_TYPE_INVALID) ?
		-1 : g.common.upos;
पूर्ण

अटल अंतरभूत पूर्णांक geo_blade(जोड़ geoid_u g)
अणु
	वापस (g.common.type == GEO_TYPE_INVALID) ?
		-1 : g.common.blade * 2 + g.common.slot;
पूर्ण

#पूर्ण_अगर /* _ASM_UV_GEO_H */
