<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _TFRC_H_
#घोषणा _TFRC_H_
/*
 *  Copyright (c) 2007   The University of Aberdeen, Scotland, UK
 *  Copyright (c) 2005-6 The University of Waikato, Hamilton, New Zealand.
 *  Copyright (c) 2005-6 Ian McDonald <ian.mcकरोnald@jandi.co.nz>
 *  Copyright (c) 2005   Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *  Copyright (c) 2003   Nils-Erik Mattsson, Joacim Haggmark, Magnus Erixzon
 */
#समावेश <linux/types.h>
#समावेश <linux/math64.h>
#समावेश "../../dccp.h"

/* पूर्णांकernal includes that this library exports: */
#समावेश "loss_interval.h"
#समावेश "packet_history.h"

#अगर_घोषित CONFIG_IP_DCCP_TFRC_DEBUG
बाह्य bool tfrc_debug;
#घोषणा tfrc_pr_debug(क्रमmat, a...)	DCCP_PR_DEBUG(tfrc_debug, क्रमmat, ##a)
#अन्यथा
#घोषणा tfrc_pr_debug(क्रमmat, a...)
#पूर्ण_अगर

/* पूर्णांकeger-arithmetic भागisions of type (a * 1000000)/b */
अटल अंतरभूत u64 scaled_भाग(u64 a, u64 b)
अणु
	BUG_ON(b == 0);
	वापस भाग64_u64(a * 1000000, b);
पूर्ण

अटल अंतरभूत u32 scaled_भाग32(u64 a, u64 b)
अणु
	u64 result = scaled_भाग(a, b);

	अगर (result > अच_पूर्णांक_उच्च) अणु
		DCCP_CRIT("Overflow: %llu/%llu > UINT_MAX",
			  (अचिन्हित दीर्घ दीर्घ)a, (अचिन्हित दीर्घ दीर्घ)b);
		वापस अच_पूर्णांक_उच्च;
	पूर्ण
	वापस result;
पूर्ण

/**
 * tfrc_ewma  -  Exponentially weighted moving average
 * @weight: Weight to be used as damping factor, in units of 1/10
 */
अटल अंतरभूत u32 tfrc_ewma(स्थिर u32 avg, स्थिर u32 newval, स्थिर u8 weight)
अणु
	वापस avg ? (weight * avg + (10 - weight) * newval) / 10 : newval;
पूर्ण

u32 tfrc_calc_x(u16 s, u32 R, u32 p);
u32 tfrc_calc_x_reverse_lookup(u32 fvalue);
u32 tfrc_invert_loss_event_rate(u32 loss_event_rate);

पूर्णांक tfrc_tx_packet_history_init(व्योम);
व्योम tfrc_tx_packet_history_निकास(व्योम);
पूर्णांक tfrc_rx_packet_history_init(व्योम);
व्योम tfrc_rx_packet_history_निकास(व्योम);

पूर्णांक tfrc_li_init(व्योम);
व्योम tfrc_li_निकास(व्योम);

#अगर_घोषित CONFIG_IP_DCCP_TFRC_LIB
पूर्णांक tfrc_lib_init(व्योम);
व्योम tfrc_lib_निकास(व्योम);
#अन्यथा
#घोषणा tfrc_lib_init() (0)
#घोषणा tfrc_lib_निकास()
#पूर्ण_अगर
#पूर्ण_अगर /* _TFRC_H_ */
