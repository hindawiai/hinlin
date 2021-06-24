<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019, Vladimir Oltean <olteanv@gmail.com>
 */
#अगर_अघोषित _SJA1105_PTP_H
#घोषणा _SJA1105_PTP_H

#समावेश <linux/समयr.h>

#अगर IS_ENABLED(CONFIG_NET_DSA_SJA1105_PTP)

/* Timestamps are in units of 8 ns घड़ी ticks (equivalent to
 * a fixed 125 MHz घड़ी).
 */
#घोषणा SJA1105_TICK_NS			8

अटल अंतरभूत s64 ns_to_sja1105_ticks(s64 ns)
अणु
	वापस ns / SJA1105_TICK_NS;
पूर्ण

अटल अंतरभूत s64 sja1105_ticks_to_ns(s64 ticks)
अणु
	वापस ticks * SJA1105_TICK_NS;
पूर्ण

/* Calculate the first base_समय in the future that satisfies this
 * relationship:
 *
 * future_base_समय = base_समय + N x cycle_समय >= now, or
 *
 *      now - base_समय
 * N >= ---------------
 *         cycle_समय
 *
 * Because N is an पूर्णांकeger, the उच्चमानing value of the above "a / b" ratio
 * is in fact precisely the न्यूनमान value of "(a + b - 1) / b", which is
 * easier to calculate only having पूर्णांकeger भागision tools.
 */
अटल अंतरभूत s64 future_base_समय(s64 base_समय, s64 cycle_समय, s64 now)
अणु
	s64 a, b, n;

	अगर (base_समय >= now)
		वापस base_समय;

	a = now - base_समय;
	b = cycle_समय;
	n = भाग_s64(a + b - 1, b);

	वापस base_समय + n * cycle_समय;
पूर्ण

/* This is not a preprocessor macro because the "ns" argument may or may not be
 * s64 at caller side. This ensures it is properly type-cast beक्रमe भाग_s64.
 */
अटल अंतरभूत s64 ns_to_sja1105_delta(s64 ns)
अणु
	वापस भाग_s64(ns, 200);
पूर्ण

अटल अंतरभूत s64 sja1105_delta_to_ns(s64 delta)
अणु
	वापस delta * 200;
पूर्ण

काष्ठा sja1105_ptp_cmd अणु
	u64 startptpcp;		/* start toggling PTP_CLK pin */
	u64 stopptpcp;		/* stop toggling PTP_CLK pin */
	u64 ptpstrtsch;		/* start schedule */
	u64 ptpstopsch;		/* stop schedule */
	u64 resptp;		/* reset */
	u64 corrclk4ts;		/* use the corrected घड़ी क्रम बारtamps */
	u64 ptpclkadd;		/* क्रमागत sja1105_ptp_clk_mode */
पूर्ण;

काष्ठा sja1105_ptp_data अणु
	काष्ठा समयr_list extts_समयr;
	काष्ठा sk_buff_head skb_rxtstamp_queue;
	काष्ठा ptp_घड़ी_info caps;
	काष्ठा ptp_घड़ी *घड़ी;
	काष्ठा sja1105_ptp_cmd cmd;
	/* Serializes all operations on the PTP hardware घड़ी */
	काष्ठा mutex lock;
	bool extts_enabled;
	u64 ptpsyncts;
पूर्ण;

पूर्णांक sja1105_ptp_घड़ी_रेजिस्टर(काष्ठा dsa_चयन *ds);

व्योम sja1105_ptp_घड़ी_unरेजिस्टर(काष्ठा dsa_चयन *ds);

व्योम sja1105et_ptp_cmd_packing(u8 *buf, काष्ठा sja1105_ptp_cmd *cmd,
			       क्रमागत packing_op op);

व्योम sja1105pqrs_ptp_cmd_packing(u8 *buf, काष्ठा sja1105_ptp_cmd *cmd,
				 क्रमागत packing_op op);

पूर्णांक sja1105_get_ts_info(काष्ठा dsa_चयन *ds, पूर्णांक port,
			काष्ठा ethtool_ts_info *ts);

व्योम sja1105_ptp_txtstamp_skb(काष्ठा dsa_चयन *ds, पूर्णांक slot,
			      काष्ठा sk_buff *clone);

bool sja1105_port_rxtstamp(काष्ठा dsa_चयन *ds, पूर्णांक port,
			   काष्ठा sk_buff *skb, अचिन्हित पूर्णांक type);

व्योम sja1105_port_txtstamp(काष्ठा dsa_चयन *ds, पूर्णांक port,
			   काष्ठा sk_buff *skb);

पूर्णांक sja1105_hwtstamp_get(काष्ठा dsa_चयन *ds, पूर्णांक port, काष्ठा अगरreq *अगरr);

पूर्णांक sja1105_hwtstamp_set(काष्ठा dsa_चयन *ds, पूर्णांक port, काष्ठा अगरreq *अगरr);

पूर्णांक __sja1105_ptp_समय_लोx(काष्ठा dsa_चयन *ds, u64 *ns,
			   काष्ठा ptp_प्रणाली_बारtamp *sts);

पूर्णांक __sja1105_ptp_समय_रखो(काष्ठा dsa_चयन *ds, u64 ns,
			  काष्ठा ptp_प्रणाली_बारtamp *ptp_sts);

पूर्णांक __sja1105_ptp_adjसमय(काष्ठा dsa_चयन *ds, s64 delta);

पूर्णांक sja1105_ptp_commit(काष्ठा dsa_चयन *ds, काष्ठा sja1105_ptp_cmd *cmd,
		       sja1105_spi_rw_mode_t rw);

#अन्यथा

काष्ठा sja1105_ptp_cmd;

/* Structures cannot be empty in C. Bah!
 * Keep the mutex as the only element, which is a bit more dअगरficult to
 * refactor out of sja1105_मुख्य.c anyway.
 */
काष्ठा sja1105_ptp_data अणु
	काष्ठा mutex lock;
पूर्ण;

अटल अंतरभूत पूर्णांक sja1105_ptp_घड़ी_रेजिस्टर(काष्ठा dsa_चयन *ds)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sja1105_ptp_घड़ी_unरेजिस्टर(काष्ठा dsa_चयन *ds) अणु पूर्ण

अटल अंतरभूत व्योम sja1105_ptp_txtstamp_skb(काष्ठा dsa_चयन *ds, पूर्णांक slot,
					    काष्ठा sk_buff *clone)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक __sja1105_ptp_समय_लोx(काष्ठा dsa_चयन *ds, u64 *ns,
					 काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __sja1105_ptp_समय_रखो(काष्ठा dsa_चयन *ds, u64 ns,
					काष्ठा ptp_प्रणाली_बारtamp *ptp_sts)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __sja1105_ptp_adjसमय(काष्ठा dsa_चयन *ds, s64 delta)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sja1105_ptp_commit(काष्ठा dsa_चयन *ds,
				     काष्ठा sja1105_ptp_cmd *cmd,
				     sja1105_spi_rw_mode_t rw)
अणु
	वापस 0;
पूर्ण

#घोषणा sja1105et_ptp_cmd_packing शून्य

#घोषणा sja1105pqrs_ptp_cmd_packing शून्य

#घोषणा sja1105_get_ts_info शून्य

#घोषणा sja1105_port_rxtstamp शून्य

#घोषणा sja1105_port_txtstamp शून्य

#घोषणा sja1105_hwtstamp_get शून्य

#घोषणा sja1105_hwtstamp_set शून्य

#पूर्ण_अगर /* IS_ENABLED(CONFIG_NET_DSA_SJA1105_PTP) */

#पूर्ण_अगर /* _SJA1105_PTP_H */
