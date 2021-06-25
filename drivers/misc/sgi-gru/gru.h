<शैली गुरु>
/*
 *  Copyright (c) 2008 Silicon Graphics, Inc.  All Rights Reserved.
 *
 *  This program is मुक्त software; you can redistribute it and/or modअगरy
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 2.1 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License क्रम more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */

#अगर_अघोषित __GRU_H__
#घोषणा __GRU_H__

/*
 * GRU architectural definitions
 */
#घोषणा GRU_CACHE_LINE_BYTES		64
#घोषणा GRU_HANDLE_STRIDE		256
#घोषणा GRU_CB_BASE			0
#घोषणा GRU_DS_BASE			0x20000

/*
 * Size used to map GRU GSeg
 */
#अगर defined(CONFIG_IA64)
#घोषणा GRU_GSEG_PAGESIZE	(256 * 1024UL)
#या_अगर defined(CONFIG_X86_64)
#घोषणा GRU_GSEG_PAGESIZE	(256 * 1024UL)		/* ZZZ 2MB ??? */
#अन्यथा
#त्रुटि "Unsupported architecture"
#पूर्ण_अगर

/*
 * Structure क्रम obtaining GRU resource inक्रमmation
 */
काष्ठा gru_chiplet_info अणु
	पूर्णांक	node;
	पूर्णांक	chiplet;
	पूर्णांक	blade;
	पूर्णांक	total_dsr_bytes;
	पूर्णांक	total_cbr;
	पूर्णांक	total_user_dsr_bytes;
	पूर्णांक	total_user_cbr;
	पूर्णांक	मुक्त_user_dsr_bytes;
	पूर्णांक	मुक्त_user_cbr;
पूर्ण;

/*
 * Statictics kept क्रम each context.
 */
काष्ठा gru_gseg_statistics अणु
	अचिन्हित दीर्घ	fmm_tlbmiss;
	अचिन्हित दीर्घ	upm_tlbmiss;
	अचिन्हित दीर्घ	tlbdropin;
	अचिन्हित दीर्घ	context_stolen;
	अचिन्हित दीर्घ	reserved[10];
पूर्ण;

/* Flags क्रम GRU options on the gru_create_context() call */
/* Select one of the follow 4 options to specअगरy how TLB misses are handled */
#घोषणा GRU_OPT_MISS_DEFAULT	0x0000	/* Use शेष mode */
#घोषणा GRU_OPT_MISS_USER_POLL	0x0001	/* User will poll CB क्रम faults */
#घोषणा GRU_OPT_MISS_FMM_INTR	0x0002	/* Send पूर्णांकerrupt to cpu to
					   handle fault */
#घोषणा GRU_OPT_MISS_FMM_POLL	0x0003	/* Use प्रणाली polling thपढ़ो */
#घोषणा GRU_OPT_MISS_MASK	0x0003	/* Mask क्रम TLB MISS option */



#पूर्ण_अगर		/* __GRU_H__ */
