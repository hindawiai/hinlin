<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2018 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXSW_SPECTRUM_SPAN_H
#घोषणा _MLXSW_SPECTRUM_SPAN_H

#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/refcount.h>

#समावेश "spectrum_router.h"

काष्ठा mlxsw_sp;
काष्ठा mlxsw_sp_port;

/* SPAN session identअगरiers that correspond to MLXSW_TRAP_ID_MIRROR_SESSION<i>
 * trap identअगरiers. The session identअगरier is an attribute of the SPAN agent,
 * which determines the trap identअगरier of packets that are mirrored to the
 * CPU. Packets that are trapped to the CPU क्रम the same logical reason (e.g.,
 * buffer drops) should use the same session identअगरier.
 */
क्रमागत mlxsw_sp_span_session_id अणु
	MLXSW_SP_SPAN_SESSION_ID_BUFFER,
	MLXSW_SP_SPAN_SESSION_ID_SAMPLING,

	__MLXSW_SP_SPAN_SESSION_ID_MAX = 8,
पूर्ण;

काष्ठा mlxsw_sp_span_parms अणु
	काष्ठा mlxsw_sp_port *dest_port; /* शून्य क्रम unoffloaded SPAN. */
	अचिन्हित पूर्णांक ttl;
	अचिन्हित अक्षर dmac[ETH_ALEN];
	अचिन्हित अक्षर smac[ETH_ALEN];
	जोड़ mlxsw_sp_l3addr daddr;
	जोड़ mlxsw_sp_l3addr saddr;
	u16 vid;
	u16 policer_id;
	bool policer_enable;
	क्रमागत mlxsw_sp_span_session_id session_id;
पूर्ण;

क्रमागत mlxsw_sp_span_trigger अणु
	MLXSW_SP_SPAN_TRIGGER_INGRESS,
	MLXSW_SP_SPAN_TRIGGER_EGRESS,
	MLXSW_SP_SPAN_TRIGGER_TAIL_DROP,
	MLXSW_SP_SPAN_TRIGGER_EARLY_DROP,
	MLXSW_SP_SPAN_TRIGGER_ECN,
पूर्ण;

काष्ठा mlxsw_sp_span_trigger_parms अणु
	पूर्णांक span_id;
	u32 probability_rate;
पूर्ण;

काष्ठा mlxsw_sp_span_agent_parms अणु
	स्थिर काष्ठा net_device *to_dev;
	u16 policer_id;
	bool policer_enable;
	क्रमागत mlxsw_sp_span_session_id session_id;
पूर्ण;

काष्ठा mlxsw_sp_span_entry_ops;

काष्ठा mlxsw_sp_span_ops अणु
	पूर्णांक (*init)(काष्ठा mlxsw_sp *mlxsw_sp);
	पूर्णांक (*policer_id_base_set)(काष्ठा mlxsw_sp *mlxsw_sp,
				   u16 policer_id_base);
पूर्ण;

काष्ठा mlxsw_sp_span_entry अणु
	स्थिर काष्ठा net_device *to_dev;
	स्थिर काष्ठा mlxsw_sp_span_entry_ops *ops;
	काष्ठा mlxsw_sp_span_parms parms;
	refcount_t ref_count;
	पूर्णांक id;
पूर्ण;

काष्ठा mlxsw_sp_span_entry_ops अणु
	bool is_अटल;
	bool (*can_handle)(स्थिर काष्ठा net_device *to_dev);
	पूर्णांक (*parms_set)(काष्ठा mlxsw_sp *mlxsw_sp,
			 स्थिर काष्ठा net_device *to_dev,
			 काष्ठा mlxsw_sp_span_parms *sparmsp);
	पूर्णांक (*configure)(काष्ठा mlxsw_sp_span_entry *span_entry,
			 काष्ठा mlxsw_sp_span_parms sparms);
	व्योम (*deconfigure)(काष्ठा mlxsw_sp_span_entry *span_entry);
पूर्ण;

पूर्णांक mlxsw_sp_span_init(काष्ठा mlxsw_sp *mlxsw_sp);
व्योम mlxsw_sp_span_fini(काष्ठा mlxsw_sp *mlxsw_sp);
व्योम mlxsw_sp_span_respin(काष्ठा mlxsw_sp *mlxsw_sp);

काष्ठा mlxsw_sp_span_entry *
mlxsw_sp_span_entry_find_by_port(काष्ठा mlxsw_sp *mlxsw_sp,
				 स्थिर काष्ठा net_device *to_dev);

व्योम mlxsw_sp_span_entry_invalidate(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp_span_entry *span_entry);

पूर्णांक mlxsw_sp_span_port_mtu_update(काष्ठा mlxsw_sp_port *port, u16 mtu);
व्योम mlxsw_sp_span_speed_update_work(काष्ठा work_काष्ठा *work);

पूर्णांक mlxsw_sp_span_agent_get(काष्ठा mlxsw_sp *mlxsw_sp, पूर्णांक *p_span_id,
			    स्थिर काष्ठा mlxsw_sp_span_agent_parms *parms);
व्योम mlxsw_sp_span_agent_put(काष्ठा mlxsw_sp *mlxsw_sp, पूर्णांक span_id);
पूर्णांक mlxsw_sp_span_analyzed_port_get(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				    bool ingress);
व्योम mlxsw_sp_span_analyzed_port_put(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				     bool ingress);
पूर्णांक mlxsw_sp_span_agent_bind(काष्ठा mlxsw_sp *mlxsw_sp,
			     क्रमागत mlxsw_sp_span_trigger trigger,
			     काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			     स्थिर काष्ठा mlxsw_sp_span_trigger_parms *parms);
व्योम
mlxsw_sp_span_agent_unbind(काष्ठा mlxsw_sp *mlxsw_sp,
			   क्रमागत mlxsw_sp_span_trigger trigger,
			   काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			   स्थिर काष्ठा mlxsw_sp_span_trigger_parms *parms);
पूर्णांक mlxsw_sp_span_trigger_enable(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				 क्रमागत mlxsw_sp_span_trigger trigger, u8 tc);
व्योम mlxsw_sp_span_trigger_disable(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				   क्रमागत mlxsw_sp_span_trigger trigger, u8 tc);

बाह्य स्थिर काष्ठा mlxsw_sp_span_ops mlxsw_sp1_span_ops;
बाह्य स्थिर काष्ठा mlxsw_sp_span_ops mlxsw_sp2_span_ops;
बाह्य स्थिर काष्ठा mlxsw_sp_span_ops mlxsw_sp3_span_ops;

#पूर्ण_अगर
