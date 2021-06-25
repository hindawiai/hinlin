<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/red.h>

#समावेश "spectrum.h"
#समावेश "spectrum_span.h"
#समावेश "reg.h"

#घोषणा MLXSW_SP_PRIO_BAND_TO_TCLASS(band) (IEEE_8021QAZ_MAX_TCS - band - 1)
#घोषणा MLXSW_SP_PRIO_CHILD_TO_TCLASS(child) \
	MLXSW_SP_PRIO_BAND_TO_TCLASS((child - 1))

क्रमागत mlxsw_sp_qdisc_type अणु
	MLXSW_SP_QDISC_NO_QDISC,
	MLXSW_SP_QDISC_RED,
	MLXSW_SP_QDISC_PRIO,
	MLXSW_SP_QDISC_ETS,
	MLXSW_SP_QDISC_TBF,
	MLXSW_SP_QDISC_FIFO,
पूर्ण;

काष्ठा mlxsw_sp_qdisc;

काष्ठा mlxsw_sp_qdisc_ops अणु
	क्रमागत mlxsw_sp_qdisc_type type;
	पूर्णांक (*check_params)(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			    व्योम *params);
	पूर्णांक (*replace)(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u32 handle,
		       काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc, व्योम *params);
	पूर्णांक (*destroy)(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
		       काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc);
	पूर्णांक (*get_stats)(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			 काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			 काष्ठा tc_qopt_offload_stats *stats_ptr);
	पूर्णांक (*get_xstats)(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			  काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			  व्योम *xstats_ptr);
	व्योम (*clean_stats)(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			    काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc);
	/* unoffload - to be used क्रम a qdisc that stops being offloaded without
	 * being destroyed.
	 */
	व्योम (*unoffload)(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			  काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc, व्योम *params);
	काष्ठा mlxsw_sp_qdisc *(*find_class)(काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
					     u32 parent);
	अचिन्हित पूर्णांक num_classes;
पूर्ण;

काष्ठा mlxsw_sp_qdisc अणु
	u32 handle;
	पूर्णांक tclass_num;
	u8 prio_biपंचांगap;
	जोड़ अणु
		काष्ठा red_stats red;
	पूर्ण xstats_base;
	काष्ठा mlxsw_sp_qdisc_stats अणु
		u64 tx_bytes;
		u64 tx_packets;
		u64 drops;
		u64 overlimits;
		u64 backlog;
	पूर्ण stats_base;

	काष्ठा mlxsw_sp_qdisc_ops *ops;
	काष्ठा mlxsw_sp_qdisc *parent;
	काष्ठा mlxsw_sp_qdisc *qdiscs;
	अचिन्हित पूर्णांक num_classes;
पूर्ण;

काष्ठा mlxsw_sp_qdisc_state अणु
	काष्ठा mlxsw_sp_qdisc root_qdisc;

	/* When a PRIO or ETS are added, the invisible FIFOs in their bands are
	 * created first. When notअगरications क्रम these FIFOs arrive, it is not
	 * known what qdisc their parent handle refers to. It could be a
	 * newly-created PRIO that will replace the currently-offloaded one, or
	 * it could be e.g. a RED that will be attached below it.
	 *
	 * As the notअगरications start to arrive, use them to note what the
	 * future parent handle is, and keep track of which child FIFOs were
	 * seen. Then when the parent is known, retroactively offload those
	 * FIFOs.
	 */
	u32 future_handle;
	bool future_fअगरos[IEEE_8021QAZ_MAX_TCS];
	काष्ठा mutex lock; /* Protects qdisc state. */
पूर्ण;

अटल bool
mlxsw_sp_qdisc_compare(काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc, u32 handle)
अणु
	वापस mlxsw_sp_qdisc->ops && mlxsw_sp_qdisc->handle == handle;
पूर्ण

अटल काष्ठा mlxsw_sp_qdisc *
mlxsw_sp_qdisc_walk(काष्ठा mlxsw_sp_qdisc *qdisc,
		    काष्ठा mlxsw_sp_qdisc *(*pre)(काष्ठा mlxsw_sp_qdisc *,
						  व्योम *),
		    व्योम *data)
अणु
	काष्ठा mlxsw_sp_qdisc *पंचांगp;
	अचिन्हित पूर्णांक i;

	अगर (pre) अणु
		पंचांगp = pre(qdisc, data);
		अगर (पंचांगp)
			वापस पंचांगp;
	पूर्ण

	अगर (qdisc->ops) अणु
		क्रम (i = 0; i < qdisc->num_classes; i++) अणु
			पंचांगp = &qdisc->qdiscs[i];
			अगर (qdisc->ops) अणु
				पंचांगp = mlxsw_sp_qdisc_walk(पंचांगp, pre, data);
				अगर (पंचांगp)
					वापस पंचांगp;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा mlxsw_sp_qdisc *
mlxsw_sp_qdisc_walk_cb_find(काष्ठा mlxsw_sp_qdisc *qdisc, व्योम *data)
अणु
	u32 parent = *(u32 *)data;

	अगर (qdisc->ops && TC_H_MAJ(qdisc->handle) == TC_H_MAJ(parent)) अणु
		अगर (qdisc->ops->find_class)
			वापस qdisc->ops->find_class(qdisc, parent);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा mlxsw_sp_qdisc *
mlxsw_sp_qdisc_find(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u32 parent,
		    bool root_only)
अणु
	काष्ठा mlxsw_sp_qdisc_state *qdisc_state = mlxsw_sp_port->qdisc;

	अगर (!qdisc_state)
		वापस शून्य;
	अगर (parent == TC_H_ROOT)
		वापस &qdisc_state->root_qdisc;
	अगर (root_only)
		वापस शून्य;
	वापस mlxsw_sp_qdisc_walk(&qdisc_state->root_qdisc,
				   mlxsw_sp_qdisc_walk_cb_find, &parent);
पूर्ण

अटल काष्ठा mlxsw_sp_qdisc *
mlxsw_sp_qdisc_walk_cb_find_by_handle(काष्ठा mlxsw_sp_qdisc *qdisc, व्योम *data)
अणु
	u32 handle = *(u32 *)data;

	अगर (qdisc->ops && qdisc->handle == handle)
		वापस qdisc;
	वापस शून्य;
पूर्ण

अटल काष्ठा mlxsw_sp_qdisc *
mlxsw_sp_qdisc_find_by_handle(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u32 handle)
अणु
	काष्ठा mlxsw_sp_qdisc_state *qdisc_state = mlxsw_sp_port->qdisc;

	अगर (!qdisc_state)
		वापस शून्य;
	वापस mlxsw_sp_qdisc_walk(&qdisc_state->root_qdisc,
				   mlxsw_sp_qdisc_walk_cb_find_by_handle,
				   &handle);
पूर्ण

अटल व्योम
mlxsw_sp_qdisc_reduce_parent_backlog(काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc)
अणु
	काष्ठा mlxsw_sp_qdisc *पंचांगp;

	क्रम (पंचांगp = mlxsw_sp_qdisc->parent; पंचांगp; पंचांगp = पंचांगp->parent)
		पंचांगp->stats_base.backlog -= mlxsw_sp_qdisc->stats_base.backlog;
पूर्ण

अटल पूर्णांक
mlxsw_sp_qdisc_destroy(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
		       काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc)
अणु
	काष्ठा mlxsw_sp_qdisc *root_qdisc = &mlxsw_sp_port->qdisc->root_qdisc;
	पूर्णांक err_hdroom = 0;
	पूर्णांक err = 0;

	अगर (!mlxsw_sp_qdisc)
		वापस 0;

	अगर (root_qdisc == mlxsw_sp_qdisc) अणु
		काष्ठा mlxsw_sp_hdroom hdroom = *mlxsw_sp_port->hdroom;

		hdroom.mode = MLXSW_SP_HDROOM_MODE_DCB;
		mlxsw_sp_hdroom_prios_reset_buf_idx(&hdroom);
		mlxsw_sp_hdroom_bufs_reset_lossiness(&hdroom);
		mlxsw_sp_hdroom_bufs_reset_sizes(mlxsw_sp_port, &hdroom);
		err_hdroom = mlxsw_sp_hdroom_configure(mlxsw_sp_port, &hdroom);
	पूर्ण

	अगर (!mlxsw_sp_qdisc->ops)
		वापस 0;

	mlxsw_sp_qdisc_reduce_parent_backlog(mlxsw_sp_qdisc);
	अगर (mlxsw_sp_qdisc->ops->destroy)
		err = mlxsw_sp_qdisc->ops->destroy(mlxsw_sp_port,
						   mlxsw_sp_qdisc);
	अगर (mlxsw_sp_qdisc->ops->clean_stats)
		mlxsw_sp_qdisc->ops->clean_stats(mlxsw_sp_port, mlxsw_sp_qdisc);

	mlxsw_sp_qdisc->handle = TC_H_UNSPEC;
	mlxsw_sp_qdisc->ops = शून्य;
	mlxsw_sp_qdisc->num_classes = 0;
	kमुक्त(mlxsw_sp_qdisc->qdiscs);
	mlxsw_sp_qdisc->qdiscs = शून्य;
	वापस err_hdroom ?: err;
पूर्ण

अटल पूर्णांक mlxsw_sp_qdisc_create(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				 u32 handle,
				 काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
				 काष्ठा mlxsw_sp_qdisc_ops *ops, व्योम *params)
अणु
	काष्ठा mlxsw_sp_qdisc *root_qdisc = &mlxsw_sp_port->qdisc->root_qdisc;
	काष्ठा mlxsw_sp_hdroom orig_hdroom;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	err = ops->check_params(mlxsw_sp_port, params);
	अगर (err)
		वापस err;

	अगर (ops->num_classes) अणु
		mlxsw_sp_qdisc->qdiscs = kसुस्मृति(ops->num_classes,
						 माप(*mlxsw_sp_qdisc->qdiscs),
						 GFP_KERNEL);
		अगर (!mlxsw_sp_qdisc->qdiscs)
			वापस -ENOMEM;

		क्रम (i = 0; i < ops->num_classes; i++)
			mlxsw_sp_qdisc->qdiscs[i].parent = mlxsw_sp_qdisc;
	पूर्ण

	orig_hdroom = *mlxsw_sp_port->hdroom;
	अगर (root_qdisc == mlxsw_sp_qdisc) अणु
		काष्ठा mlxsw_sp_hdroom hdroom = orig_hdroom;

		hdroom.mode = MLXSW_SP_HDROOM_MODE_TC;
		mlxsw_sp_hdroom_prios_reset_buf_idx(&hdroom);
		mlxsw_sp_hdroom_bufs_reset_lossiness(&hdroom);
		mlxsw_sp_hdroom_bufs_reset_sizes(mlxsw_sp_port, &hdroom);

		err = mlxsw_sp_hdroom_configure(mlxsw_sp_port, &hdroom);
		अगर (err)
			जाओ err_hdroom_configure;
	पूर्ण

	mlxsw_sp_qdisc->num_classes = ops->num_classes;
	mlxsw_sp_qdisc->ops = ops;
	mlxsw_sp_qdisc->handle = handle;
	err = ops->replace(mlxsw_sp_port, handle, mlxsw_sp_qdisc, params);
	अगर (err)
		जाओ err_replace;

	वापस 0;

err_replace:
	mlxsw_sp_qdisc->handle = TC_H_UNSPEC;
	mlxsw_sp_qdisc->ops = शून्य;
	mlxsw_sp_qdisc->num_classes = 0;
	mlxsw_sp_hdroom_configure(mlxsw_sp_port, &orig_hdroom);
err_hdroom_configure:
	kमुक्त(mlxsw_sp_qdisc->qdiscs);
	mlxsw_sp_qdisc->qdiscs = शून्य;
	वापस err;
पूर्ण

अटल पूर्णांक
mlxsw_sp_qdisc_change(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u32 handle,
		      काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc, व्योम *params)
अणु
	काष्ठा mlxsw_sp_qdisc_ops *ops = mlxsw_sp_qdisc->ops;
	पूर्णांक err;

	err = ops->check_params(mlxsw_sp_port, params);
	अगर (err)
		जाओ unoffload;

	err = ops->replace(mlxsw_sp_port, handle, mlxsw_sp_qdisc, params);
	अगर (err)
		जाओ unoffload;

	/* Check अगर the Qdisc changed. That includes a situation where an
	 * invisible Qdisc replaces another one, or is being added क्रम the
	 * first समय.
	 */
	अगर (mlxsw_sp_qdisc->handle != handle) अणु
		अगर (ops->clean_stats)
			ops->clean_stats(mlxsw_sp_port, mlxsw_sp_qdisc);
	पूर्ण

	mlxsw_sp_qdisc->handle = handle;
	वापस 0;

unoffload:
	अगर (ops->unoffload)
		ops->unoffload(mlxsw_sp_port, mlxsw_sp_qdisc, params);

	mlxsw_sp_qdisc_destroy(mlxsw_sp_port, mlxsw_sp_qdisc);
	वापस err;
पूर्ण

अटल पूर्णांक
mlxsw_sp_qdisc_replace(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u32 handle,
		       काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
		       काष्ठा mlxsw_sp_qdisc_ops *ops, व्योम *params)
अणु
	अगर (mlxsw_sp_qdisc->ops && mlxsw_sp_qdisc->ops->type != ops->type)
		/* In हाल this location contained a dअगरferent qdisc of the
		 * same type we can override the old qdisc configuration.
		 * Otherwise, we need to हटाओ the old qdisc beक्रमe setting the
		 * new one.
		 */
		mlxsw_sp_qdisc_destroy(mlxsw_sp_port, mlxsw_sp_qdisc);

	अगर (!mlxsw_sp_qdisc->ops)
		वापस mlxsw_sp_qdisc_create(mlxsw_sp_port, handle,
					     mlxsw_sp_qdisc, ops, params);
	अन्यथा
		वापस mlxsw_sp_qdisc_change(mlxsw_sp_port, handle,
					     mlxsw_sp_qdisc, params);
पूर्ण

अटल पूर्णांक
mlxsw_sp_qdisc_get_stats(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			 काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			 काष्ठा tc_qopt_offload_stats *stats_ptr)
अणु
	अगर (mlxsw_sp_qdisc && mlxsw_sp_qdisc->ops &&
	    mlxsw_sp_qdisc->ops->get_stats)
		वापस mlxsw_sp_qdisc->ops->get_stats(mlxsw_sp_port,
						      mlxsw_sp_qdisc,
						      stats_ptr);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
mlxsw_sp_qdisc_get_xstats(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			  काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			  व्योम *xstats_ptr)
अणु
	अगर (mlxsw_sp_qdisc && mlxsw_sp_qdisc->ops &&
	    mlxsw_sp_qdisc->ops->get_xstats)
		वापस mlxsw_sp_qdisc->ops->get_xstats(mlxsw_sp_port,
						      mlxsw_sp_qdisc,
						      xstats_ptr);

	वापस -EOPNOTSUPP;
पूर्ण

अटल u64
mlxsw_sp_xstats_backlog(काष्ठा mlxsw_sp_port_xstats *xstats, पूर्णांक tclass_num)
अणु
	वापस xstats->backlog[tclass_num] +
	       xstats->backlog[tclass_num + 8];
पूर्ण

अटल u64
mlxsw_sp_xstats_tail_drop(काष्ठा mlxsw_sp_port_xstats *xstats, पूर्णांक tclass_num)
अणु
	वापस xstats->tail_drop[tclass_num] +
	       xstats->tail_drop[tclass_num + 8];
पूर्ण

अटल व्योम
mlxsw_sp_qdisc_bstats_per_priority_get(काष्ठा mlxsw_sp_port_xstats *xstats,
				       u8 prio_biपंचांगap, u64 *tx_packets,
				       u64 *tx_bytes)
अणु
	पूर्णांक i;

	*tx_packets = 0;
	*tx_bytes = 0;
	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		अगर (prio_biपंचांगap & BIT(i)) अणु
			*tx_packets += xstats->tx_packets[i];
			*tx_bytes += xstats->tx_bytes[i];
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
mlxsw_sp_qdisc_collect_tc_stats(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
				u64 *p_tx_bytes, u64 *p_tx_packets,
				u64 *p_drops, u64 *p_backlog)
अणु
	पूर्णांक tclass_num = mlxsw_sp_qdisc->tclass_num;
	काष्ठा mlxsw_sp_port_xstats *xstats;
	u64 tx_bytes, tx_packets;

	xstats = &mlxsw_sp_port->periodic_hw_stats.xstats;
	mlxsw_sp_qdisc_bstats_per_priority_get(xstats,
					       mlxsw_sp_qdisc->prio_biपंचांगap,
					       &tx_packets, &tx_bytes);

	*p_tx_packets += tx_packets;
	*p_tx_bytes += tx_bytes;
	*p_drops += xstats->wred_drop[tclass_num] +
		    mlxsw_sp_xstats_tail_drop(xstats, tclass_num);
	*p_backlog += mlxsw_sp_xstats_backlog(xstats, tclass_num);
पूर्ण

अटल व्योम
mlxsw_sp_qdisc_update_stats(काष्ठा mlxsw_sp *mlxsw_sp,
			    काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			    u64 tx_bytes, u64 tx_packets,
			    u64 drops, u64 backlog,
			    काष्ठा tc_qopt_offload_stats *stats_ptr)
अणु
	काष्ठा mlxsw_sp_qdisc_stats *stats_base = &mlxsw_sp_qdisc->stats_base;

	tx_bytes -= stats_base->tx_bytes;
	tx_packets -= stats_base->tx_packets;
	drops -= stats_base->drops;
	backlog -= stats_base->backlog;

	_bstats_update(stats_ptr->bstats, tx_bytes, tx_packets);
	stats_ptr->qstats->drops += drops;
	stats_ptr->qstats->backlog += mlxsw_sp_cells_bytes(mlxsw_sp, backlog);

	stats_base->backlog += backlog;
	stats_base->drops += drops;
	stats_base->tx_bytes += tx_bytes;
	stats_base->tx_packets += tx_packets;
पूर्ण

अटल व्योम
mlxsw_sp_qdisc_get_tc_stats(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			    काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			    काष्ठा tc_qopt_offload_stats *stats_ptr)
अणु
	u64 tx_packets = 0;
	u64 tx_bytes = 0;
	u64 backlog = 0;
	u64 drops = 0;

	mlxsw_sp_qdisc_collect_tc_stats(mlxsw_sp_port, mlxsw_sp_qdisc,
					&tx_bytes, &tx_packets,
					&drops, &backlog);
	mlxsw_sp_qdisc_update_stats(mlxsw_sp_port->mlxsw_sp, mlxsw_sp_qdisc,
				    tx_bytes, tx_packets, drops, backlog,
				    stats_ptr);
पूर्ण

अटल पूर्णांक
mlxsw_sp_tclass_congestion_enable(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				  पूर्णांक tclass_num, u32 min, u32 max,
				  u32 probability, bool is_wred, bool is_ecn)
अणु
	अक्षर cwtpm_cmd[MLXSW_REG_CWTPM_LEN];
	अक्षर cwtp_cmd[MLXSW_REG_CWTP_LEN];
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	पूर्णांक err;

	mlxsw_reg_cwtp_pack(cwtp_cmd, mlxsw_sp_port->local_port, tclass_num);
	mlxsw_reg_cwtp_profile_pack(cwtp_cmd, MLXSW_REG_CWTP_DEFAULT_PROखाता,
				    roundup(min, MLXSW_REG_CWTP_MIN_VALUE),
				    roundup(max, MLXSW_REG_CWTP_MIN_VALUE),
				    probability);

	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(cwtp), cwtp_cmd);
	अगर (err)
		वापस err;

	mlxsw_reg_cwtpm_pack(cwtpm_cmd, mlxsw_sp_port->local_port, tclass_num,
			     MLXSW_REG_CWTP_DEFAULT_PROखाता, is_wred, is_ecn);

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(cwtpm), cwtpm_cmd);
पूर्ण

अटल पूर्णांक
mlxsw_sp_tclass_congestion_disable(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				   पूर्णांक tclass_num)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर cwtpm_cmd[MLXSW_REG_CWTPM_LEN];

	mlxsw_reg_cwtpm_pack(cwtpm_cmd, mlxsw_sp_port->local_port, tclass_num,
			     MLXSW_REG_CWTPM_RESET_PROखाता, false, false);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(cwtpm), cwtpm_cmd);
पूर्ण

अटल व्योम
mlxsw_sp_setup_tc_qdisc_red_clean_stats(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc)
अणु
	पूर्णांक tclass_num = mlxsw_sp_qdisc->tclass_num;
	काष्ठा mlxsw_sp_qdisc_stats *stats_base;
	काष्ठा mlxsw_sp_port_xstats *xstats;
	काष्ठा red_stats *red_base;

	xstats = &mlxsw_sp_port->periodic_hw_stats.xstats;
	stats_base = &mlxsw_sp_qdisc->stats_base;
	red_base = &mlxsw_sp_qdisc->xstats_base.red;

	mlxsw_sp_qdisc_bstats_per_priority_get(xstats,
					       mlxsw_sp_qdisc->prio_biपंचांगap,
					       &stats_base->tx_packets,
					       &stats_base->tx_bytes);
	red_base->prob_drop = xstats->wred_drop[tclass_num];
	red_base->pdrop = mlxsw_sp_xstats_tail_drop(xstats, tclass_num);

	stats_base->overlimits = red_base->prob_drop + red_base->prob_mark;
	stats_base->drops = red_base->prob_drop + red_base->pdrop;

	stats_base->backlog = 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_qdisc_red_destroy(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			   काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc)
अणु
	वापस mlxsw_sp_tclass_congestion_disable(mlxsw_sp_port,
						  mlxsw_sp_qdisc->tclass_num);
पूर्ण

अटल पूर्णांक
mlxsw_sp_qdisc_red_check_params(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				व्योम *params)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा tc_red_qopt_offload_params *p = params;

	अगर (p->min > p->max) अणु
		dev_err(mlxsw_sp->bus_info->dev,
			"spectrum: RED: min %u is bigger then max %u\n", p->min,
			p->max);
		वापस -EINVAL;
	पूर्ण
	अगर (p->max > MLXSW_CORE_RES_GET(mlxsw_sp->core,
					GUARANTEED_SHARED_BUFFER)) अणु
		dev_err(mlxsw_sp->bus_info->dev,
			"spectrum: RED: max value %u is too big\n", p->max);
		वापस -EINVAL;
	पूर्ण
	अगर (p->min == 0 || p->max == 0) अणु
		dev_err(mlxsw_sp->bus_info->dev,
			"spectrum: RED: 0 value is illegal for min and max\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_qdisc_red_replace(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u32 handle,
			   काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			   व्योम *params)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा tc_red_qopt_offload_params *p = params;
	पूर्णांक tclass_num = mlxsw_sp_qdisc->tclass_num;
	u32 min, max;
	u64 prob;

	/* calculate probability in percentage */
	prob = p->probability;
	prob *= 100;
	prob = DIV_ROUND_UP(prob, 1 << 16);
	prob = DIV_ROUND_UP(prob, 1 << 16);
	min = mlxsw_sp_bytes_cells(mlxsw_sp, p->min);
	max = mlxsw_sp_bytes_cells(mlxsw_sp, p->max);
	वापस mlxsw_sp_tclass_congestion_enable(mlxsw_sp_port, tclass_num,
						 min, max, prob,
						 !p->is_nodrop, p->is_ecn);
पूर्ण

अटल व्योम
mlxsw_sp_qdisc_leaf_unoffload(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			      काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			      काष्ठा gnet_stats_queue *qstats)
अणु
	u64 backlog;

	backlog = mlxsw_sp_cells_bytes(mlxsw_sp_port->mlxsw_sp,
				       mlxsw_sp_qdisc->stats_base.backlog);
	qstats->backlog -= backlog;
	mlxsw_sp_qdisc->stats_base.backlog = 0;
पूर्ण

अटल व्योम
mlxsw_sp_qdisc_red_unoffload(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			     काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			     व्योम *params)
अणु
	काष्ठा tc_red_qopt_offload_params *p = params;

	mlxsw_sp_qdisc_leaf_unoffload(mlxsw_sp_port, mlxsw_sp_qdisc, p->qstats);
पूर्ण

अटल पूर्णांक
mlxsw_sp_qdisc_get_red_xstats(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			      काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			      व्योम *xstats_ptr)
अणु
	काष्ठा red_stats *xstats_base = &mlxsw_sp_qdisc->xstats_base.red;
	पूर्णांक tclass_num = mlxsw_sp_qdisc->tclass_num;
	काष्ठा mlxsw_sp_port_xstats *xstats;
	काष्ठा red_stats *res = xstats_ptr;
	पूर्णांक early_drops, pdrops;

	xstats = &mlxsw_sp_port->periodic_hw_stats.xstats;

	early_drops = xstats->wred_drop[tclass_num] - xstats_base->prob_drop;
	pdrops = mlxsw_sp_xstats_tail_drop(xstats, tclass_num) -
		 xstats_base->pdrop;

	res->pdrop += pdrops;
	res->prob_drop += early_drops;

	xstats_base->pdrop += pdrops;
	xstats_base->prob_drop += early_drops;
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_qdisc_get_red_stats(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			     काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			     काष्ठा tc_qopt_offload_stats *stats_ptr)
अणु
	पूर्णांक tclass_num = mlxsw_sp_qdisc->tclass_num;
	काष्ठा mlxsw_sp_qdisc_stats *stats_base;
	काष्ठा mlxsw_sp_port_xstats *xstats;
	u64 overlimits;

	xstats = &mlxsw_sp_port->periodic_hw_stats.xstats;
	stats_base = &mlxsw_sp_qdisc->stats_base;

	mlxsw_sp_qdisc_get_tc_stats(mlxsw_sp_port, mlxsw_sp_qdisc, stats_ptr);
	overlimits = xstats->wred_drop[tclass_num] - stats_base->overlimits;

	stats_ptr->qstats->overlimits += overlimits;
	stats_base->overlimits += overlimits;

	वापस 0;
पूर्ण

अटल काष्ठा mlxsw_sp_qdisc *
mlxsw_sp_qdisc_leaf_find_class(काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			       u32 parent)
अणु
	वापस शून्य;
पूर्ण

#घोषणा MLXSW_SP_PORT_DEFAULT_TCLASS 0

अटल काष्ठा mlxsw_sp_qdisc_ops mlxsw_sp_qdisc_ops_red = अणु
	.type = MLXSW_SP_QDISC_RED,
	.check_params = mlxsw_sp_qdisc_red_check_params,
	.replace = mlxsw_sp_qdisc_red_replace,
	.unoffload = mlxsw_sp_qdisc_red_unoffload,
	.destroy = mlxsw_sp_qdisc_red_destroy,
	.get_stats = mlxsw_sp_qdisc_get_red_stats,
	.get_xstats = mlxsw_sp_qdisc_get_red_xstats,
	.clean_stats = mlxsw_sp_setup_tc_qdisc_red_clean_stats,
	.find_class = mlxsw_sp_qdisc_leaf_find_class,
पूर्ण;

अटल पूर्णांक __mlxsw_sp_setup_tc_red(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				   काष्ठा tc_red_qopt_offload *p)
अणु
	काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc;

	mlxsw_sp_qdisc = mlxsw_sp_qdisc_find(mlxsw_sp_port, p->parent, false);
	अगर (!mlxsw_sp_qdisc)
		वापस -EOPNOTSUPP;

	अगर (p->command == TC_RED_REPLACE)
		वापस mlxsw_sp_qdisc_replace(mlxsw_sp_port, p->handle,
					      mlxsw_sp_qdisc,
					      &mlxsw_sp_qdisc_ops_red,
					      &p->set);

	अगर (!mlxsw_sp_qdisc_compare(mlxsw_sp_qdisc, p->handle))
		वापस -EOPNOTSUPP;

	चयन (p->command) अणु
	हाल TC_RED_DESTROY:
		वापस mlxsw_sp_qdisc_destroy(mlxsw_sp_port, mlxsw_sp_qdisc);
	हाल TC_RED_XSTATS:
		वापस mlxsw_sp_qdisc_get_xstats(mlxsw_sp_port, mlxsw_sp_qdisc,
						 p->xstats);
	हाल TC_RED_STATS:
		वापस mlxsw_sp_qdisc_get_stats(mlxsw_sp_port, mlxsw_sp_qdisc,
						&p->stats);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

पूर्णांक mlxsw_sp_setup_tc_red(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			  काष्ठा tc_red_qopt_offload *p)
अणु
	पूर्णांक err;

	mutex_lock(&mlxsw_sp_port->qdisc->lock);
	err = __mlxsw_sp_setup_tc_red(mlxsw_sp_port, p);
	mutex_unlock(&mlxsw_sp_port->qdisc->lock);

	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_setup_tc_qdisc_leaf_clean_stats(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					 काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc)
अणु
	u64 backlog_cells = 0;
	u64 tx_packets = 0;
	u64 tx_bytes = 0;
	u64 drops = 0;

	mlxsw_sp_qdisc_collect_tc_stats(mlxsw_sp_port, mlxsw_sp_qdisc,
					&tx_bytes, &tx_packets,
					&drops, &backlog_cells);

	mlxsw_sp_qdisc->stats_base.tx_packets = tx_packets;
	mlxsw_sp_qdisc->stats_base.tx_bytes = tx_bytes;
	mlxsw_sp_qdisc->stats_base.drops = drops;
	mlxsw_sp_qdisc->stats_base.backlog = 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_qdisc_tbf_destroy(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			   काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc)
अणु
	वापस mlxsw_sp_port_ets_maxrate_set(mlxsw_sp_port,
					     MLXSW_REG_QEEC_HR_SUBGROUP,
					     mlxsw_sp_qdisc->tclass_num, 0,
					     MLXSW_REG_QEEC_MAS_DIS, 0);
पूर्ण

अटल पूर्णांक
mlxsw_sp_qdisc_tbf_bs(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
		      u32 max_size, u8 *p_burst_size)
अणु
	/* TBF burst size is configured in bytes. The ASIC burst size value is
	 * ((2 ^ bs) * 512 bits. Convert the TBF bytes to 512-bit units.
	 */
	u32 bs512 = max_size / 64;
	u8 bs = fls(bs512);

	अगर (!bs)
		वापस -EINVAL;
	--bs;

	/* Demand a घातer of two. */
	अगर ((1 << bs) != bs512)
		वापस -EINVAL;

	अगर (bs < mlxsw_sp_port->mlxsw_sp->lowest_shaper_bs ||
	    bs > MLXSW_REG_QEEC_HIGHEST_SHAPER_BS)
		वापस -EINVAL;

	*p_burst_size = bs;
	वापस 0;
पूर्ण

अटल u32
mlxsw_sp_qdisc_tbf_max_size(u8 bs)
अणु
	वापस (1U << bs) * 64;
पूर्ण

अटल u64
mlxsw_sp_qdisc_tbf_rate_kbps(काष्ठा tc_tbf_qopt_offload_replace_params *p)
अणु
	/* TBF पूर्णांकerface is in bytes/s, whereas Spectrum ASIC is configured in
	 * Kbits/s.
	 */
	वापस भाग_u64(p->rate.rate_bytes_ps, 1000) * 8;
पूर्ण

अटल पूर्णांक
mlxsw_sp_qdisc_tbf_check_params(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				व्योम *params)
अणु
	काष्ठा tc_tbf_qopt_offload_replace_params *p = params;
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	u64 rate_kbps = mlxsw_sp_qdisc_tbf_rate_kbps(p);
	u8 burst_size;
	पूर्णांक err;

	अगर (rate_kbps >= MLXSW_REG_QEEC_MAS_DIS) अणु
		dev_err(mlxsw_sp_port->mlxsw_sp->bus_info->dev,
			"spectrum: TBF: rate of %lluKbps must be below %u\n",
			rate_kbps, MLXSW_REG_QEEC_MAS_DIS);
		वापस -EINVAL;
	पूर्ण

	err = mlxsw_sp_qdisc_tbf_bs(mlxsw_sp_port, p->max_size, &burst_size);
	अगर (err) अणु
		u8 highest_shaper_bs = MLXSW_REG_QEEC_HIGHEST_SHAPER_BS;

		dev_err(mlxsw_sp->bus_info->dev,
			"spectrum: TBF: invalid burst size of %u, must be a power of two between %u and %u",
			p->max_size,
			mlxsw_sp_qdisc_tbf_max_size(mlxsw_sp->lowest_shaper_bs),
			mlxsw_sp_qdisc_tbf_max_size(highest_shaper_bs));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_qdisc_tbf_replace(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u32 handle,
			   काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			   व्योम *params)
अणु
	काष्ठा tc_tbf_qopt_offload_replace_params *p = params;
	u64 rate_kbps = mlxsw_sp_qdisc_tbf_rate_kbps(p);
	u8 burst_size;
	पूर्णांक err;

	err = mlxsw_sp_qdisc_tbf_bs(mlxsw_sp_port, p->max_size, &burst_size);
	अगर (WARN_ON_ONCE(err))
		/* check_params above was supposed to reject this value. */
		वापस -EINVAL;

	/* Configure subgroup shaper, so that both UC and MC traffic is subject
	 * to shaping. That is unlike RED, however UC queue lengths are going to
	 * be dअगरferent than MC ones due to dअगरferent pool and quota
	 * configurations, so the configuration is not applicable. For shaper on
	 * the other hand, subjecting the overall stream to the configured
	 * shaper makes sense. Also note that that is what we करो क्रम
	 * ieee_seपंचांगaxrate().
	 */
	वापस mlxsw_sp_port_ets_maxrate_set(mlxsw_sp_port,
					     MLXSW_REG_QEEC_HR_SUBGROUP,
					     mlxsw_sp_qdisc->tclass_num, 0,
					     rate_kbps, burst_size);
पूर्ण

अटल व्योम
mlxsw_sp_qdisc_tbf_unoffload(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			     काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			     व्योम *params)
अणु
	काष्ठा tc_tbf_qopt_offload_replace_params *p = params;

	mlxsw_sp_qdisc_leaf_unoffload(mlxsw_sp_port, mlxsw_sp_qdisc, p->qstats);
पूर्ण

अटल पूर्णांक
mlxsw_sp_qdisc_get_tbf_stats(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			     काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			     काष्ठा tc_qopt_offload_stats *stats_ptr)
अणु
	mlxsw_sp_qdisc_get_tc_stats(mlxsw_sp_port, mlxsw_sp_qdisc,
				    stats_ptr);
	वापस 0;
पूर्ण

अटल काष्ठा mlxsw_sp_qdisc_ops mlxsw_sp_qdisc_ops_tbf = अणु
	.type = MLXSW_SP_QDISC_TBF,
	.check_params = mlxsw_sp_qdisc_tbf_check_params,
	.replace = mlxsw_sp_qdisc_tbf_replace,
	.unoffload = mlxsw_sp_qdisc_tbf_unoffload,
	.destroy = mlxsw_sp_qdisc_tbf_destroy,
	.get_stats = mlxsw_sp_qdisc_get_tbf_stats,
	.clean_stats = mlxsw_sp_setup_tc_qdisc_leaf_clean_stats,
	.find_class = mlxsw_sp_qdisc_leaf_find_class,
पूर्ण;

अटल पूर्णांक __mlxsw_sp_setup_tc_tbf(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				   काष्ठा tc_tbf_qopt_offload *p)
अणु
	काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc;

	mlxsw_sp_qdisc = mlxsw_sp_qdisc_find(mlxsw_sp_port, p->parent, false);
	अगर (!mlxsw_sp_qdisc)
		वापस -EOPNOTSUPP;

	अगर (p->command == TC_TBF_REPLACE)
		वापस mlxsw_sp_qdisc_replace(mlxsw_sp_port, p->handle,
					      mlxsw_sp_qdisc,
					      &mlxsw_sp_qdisc_ops_tbf,
					      &p->replace_params);

	अगर (!mlxsw_sp_qdisc_compare(mlxsw_sp_qdisc, p->handle))
		वापस -EOPNOTSUPP;

	चयन (p->command) अणु
	हाल TC_TBF_DESTROY:
		वापस mlxsw_sp_qdisc_destroy(mlxsw_sp_port, mlxsw_sp_qdisc);
	हाल TC_TBF_STATS:
		वापस mlxsw_sp_qdisc_get_stats(mlxsw_sp_port, mlxsw_sp_qdisc,
						&p->stats);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

पूर्णांक mlxsw_sp_setup_tc_tbf(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			  काष्ठा tc_tbf_qopt_offload *p)
अणु
	पूर्णांक err;

	mutex_lock(&mlxsw_sp_port->qdisc->lock);
	err = __mlxsw_sp_setup_tc_tbf(mlxsw_sp_port, p);
	mutex_unlock(&mlxsw_sp_port->qdisc->lock);

	वापस err;
पूर्ण

अटल पूर्णांक
mlxsw_sp_qdisc_fअगरo_check_params(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				 व्योम *params)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_qdisc_fअगरo_replace(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u32 handle,
			    काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			    व्योम *params)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_qdisc_get_fअगरo_stats(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			      काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			      काष्ठा tc_qopt_offload_stats *stats_ptr)
अणु
	mlxsw_sp_qdisc_get_tc_stats(mlxsw_sp_port, mlxsw_sp_qdisc,
				    stats_ptr);
	वापस 0;
पूर्ण

अटल काष्ठा mlxsw_sp_qdisc_ops mlxsw_sp_qdisc_ops_fअगरo = अणु
	.type = MLXSW_SP_QDISC_FIFO,
	.check_params = mlxsw_sp_qdisc_fअगरo_check_params,
	.replace = mlxsw_sp_qdisc_fअगरo_replace,
	.get_stats = mlxsw_sp_qdisc_get_fअगरo_stats,
	.clean_stats = mlxsw_sp_setup_tc_qdisc_leaf_clean_stats,
पूर्ण;

अटल पूर्णांक __mlxsw_sp_setup_tc_fअगरo(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				    काष्ठा tc_fअगरo_qopt_offload *p)
अणु
	काष्ठा mlxsw_sp_qdisc_state *qdisc_state = mlxsw_sp_port->qdisc;
	काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc;
	अचिन्हित पूर्णांक band;
	u32 parent_handle;

	mlxsw_sp_qdisc = mlxsw_sp_qdisc_find(mlxsw_sp_port, p->parent, false);
	अगर (!mlxsw_sp_qdisc && p->handle == TC_H_UNSPEC) अणु
		parent_handle = TC_H_MAJ(p->parent);
		अगर (parent_handle != qdisc_state->future_handle) अणु
			/* This notअगरications is क्रम a dअगरferent Qdisc than
			 * previously. Wipe the future cache.
			 */
			स_रखो(qdisc_state->future_fअगरos, 0,
			       माप(qdisc_state->future_fअगरos));
			qdisc_state->future_handle = parent_handle;
		पूर्ण

		band = TC_H_MIN(p->parent) - 1;
		अगर (band < IEEE_8021QAZ_MAX_TCS) अणु
			अगर (p->command == TC_FIFO_REPLACE)
				qdisc_state->future_fअगरos[band] = true;
			अन्यथा अगर (p->command == TC_FIFO_DESTROY)
				qdisc_state->future_fअगरos[band] = false;
		पूर्ण
	पूर्ण
	अगर (!mlxsw_sp_qdisc)
		वापस -EOPNOTSUPP;

	अगर (p->command == TC_FIFO_REPLACE) अणु
		वापस mlxsw_sp_qdisc_replace(mlxsw_sp_port, p->handle,
					      mlxsw_sp_qdisc,
					      &mlxsw_sp_qdisc_ops_fअगरo, शून्य);
	पूर्ण

	अगर (!mlxsw_sp_qdisc_compare(mlxsw_sp_qdisc, p->handle))
		वापस -EOPNOTSUPP;

	चयन (p->command) अणु
	हाल TC_FIFO_DESTROY:
		वापस mlxsw_sp_qdisc_destroy(mlxsw_sp_port, mlxsw_sp_qdisc);
	हाल TC_FIFO_STATS:
		वापस mlxsw_sp_qdisc_get_stats(mlxsw_sp_port, mlxsw_sp_qdisc,
						&p->stats);
	हाल TC_FIFO_REPLACE: /* Handled above. */
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक mlxsw_sp_setup_tc_fअगरo(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			   काष्ठा tc_fअगरo_qopt_offload *p)
अणु
	पूर्णांक err;

	mutex_lock(&mlxsw_sp_port->qdisc->lock);
	err = __mlxsw_sp_setup_tc_fअगरo(mlxsw_sp_port, p);
	mutex_unlock(&mlxsw_sp_port->qdisc->lock);

	वापस err;
पूर्ण

अटल पूर्णांक __mlxsw_sp_qdisc_ets_destroy(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < mlxsw_sp_qdisc->num_classes; i++) अणु
		mlxsw_sp_port_prio_tc_set(mlxsw_sp_port, i,
					  MLXSW_SP_PORT_DEFAULT_TCLASS);
		mlxsw_sp_port_ets_set(mlxsw_sp_port,
				      MLXSW_REG_QEEC_HR_SUBGROUP,
				      i, 0, false, 0);
		mlxsw_sp_qdisc_destroy(mlxsw_sp_port,
				       &mlxsw_sp_qdisc->qdiscs[i]);
		mlxsw_sp_qdisc->qdiscs[i].prio_biपंचांगap = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_qdisc_prio_destroy(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			    काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc)
अणु
	वापस __mlxsw_sp_qdisc_ets_destroy(mlxsw_sp_port, mlxsw_sp_qdisc);
पूर्ण

अटल पूर्णांक
__mlxsw_sp_qdisc_ets_check_params(अचिन्हित पूर्णांक nbands)
अणु
	अगर (nbands > IEEE_8021QAZ_MAX_TCS)
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_qdisc_prio_check_params(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				 व्योम *params)
अणु
	काष्ठा tc_prio_qopt_offload_params *p = params;

	वापस __mlxsw_sp_qdisc_ets_check_params(p->bands);
पूर्ण

अटल पूर्णांक
__mlxsw_sp_qdisc_ets_replace(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			     काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			     u32 handle, अचिन्हित पूर्णांक nbands,
			     स्थिर अचिन्हित पूर्णांक *quanta,
			     स्थिर अचिन्हित पूर्णांक *weights,
			     स्थिर u8 *priomap)
अणु
	काष्ठा mlxsw_sp_qdisc_state *qdisc_state = mlxsw_sp_port->qdisc;
	काष्ठा mlxsw_sp_qdisc *child_qdisc;
	पूर्णांक tclass, i, band, backlog;
	u8 old_priomap;
	पूर्णांक err;

	क्रम (band = 0; band < nbands; band++) अणु
		tclass = MLXSW_SP_PRIO_BAND_TO_TCLASS(band);
		child_qdisc = &mlxsw_sp_qdisc->qdiscs[band];
		old_priomap = child_qdisc->prio_biपंचांगap;
		child_qdisc->prio_biपंचांगap = 0;

		err = mlxsw_sp_port_ets_set(mlxsw_sp_port,
					    MLXSW_REG_QEEC_HR_SUBGROUP,
					    tclass, 0, !!quanta[band],
					    weights[band]);
		अगर (err)
			वापस err;

		क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
			अगर (priomap[i] == band) अणु
				child_qdisc->prio_biपंचांगap |= BIT(i);
				अगर (BIT(i) & old_priomap)
					जारी;
				err = mlxsw_sp_port_prio_tc_set(mlxsw_sp_port,
								i, tclass);
				अगर (err)
					वापस err;
			पूर्ण
		पूर्ण

		child_qdisc->tclass_num = tclass;

		अगर (old_priomap != child_qdisc->prio_biपंचांगap &&
		    child_qdisc->ops && child_qdisc->ops->clean_stats) अणु
			backlog = child_qdisc->stats_base.backlog;
			child_qdisc->ops->clean_stats(mlxsw_sp_port,
						      child_qdisc);
			child_qdisc->stats_base.backlog = backlog;
		पूर्ण

		अगर (handle == qdisc_state->future_handle &&
		    qdisc_state->future_fअगरos[band]) अणु
			err = mlxsw_sp_qdisc_replace(mlxsw_sp_port, TC_H_UNSPEC,
						     child_qdisc,
						     &mlxsw_sp_qdisc_ops_fअगरo,
						     शून्य);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण
	क्रम (; band < IEEE_8021QAZ_MAX_TCS; band++) अणु
		tclass = MLXSW_SP_PRIO_BAND_TO_TCLASS(band);
		child_qdisc = &mlxsw_sp_qdisc->qdiscs[band];
		child_qdisc->prio_biपंचांगap = 0;
		mlxsw_sp_qdisc_destroy(mlxsw_sp_port, child_qdisc);
		mlxsw_sp_port_ets_set(mlxsw_sp_port,
				      MLXSW_REG_QEEC_HR_SUBGROUP,
				      tclass, 0, false, 0);
	पूर्ण

	qdisc_state->future_handle = TC_H_UNSPEC;
	स_रखो(qdisc_state->future_fअगरos, 0, माप(qdisc_state->future_fअगरos));
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_qdisc_prio_replace(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u32 handle,
			    काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			    व्योम *params)
अणु
	काष्ठा tc_prio_qopt_offload_params *p = params;
	अचिन्हित पूर्णांक zeroes[TCQ_ETS_MAX_BANDS] = अणु0पूर्ण;

	वापस __mlxsw_sp_qdisc_ets_replace(mlxsw_sp_port, mlxsw_sp_qdisc,
					    handle, p->bands, zeroes,
					    zeroes, p->priomap);
पूर्ण

अटल व्योम
__mlxsw_sp_qdisc_ets_unoffload(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			       काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			       काष्ठा gnet_stats_queue *qstats)
अणु
	u64 backlog;

	backlog = mlxsw_sp_cells_bytes(mlxsw_sp_port->mlxsw_sp,
				       mlxsw_sp_qdisc->stats_base.backlog);
	qstats->backlog -= backlog;
पूर्ण

अटल व्योम
mlxsw_sp_qdisc_prio_unoffload(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			      काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			      व्योम *params)
अणु
	काष्ठा tc_prio_qopt_offload_params *p = params;

	__mlxsw_sp_qdisc_ets_unoffload(mlxsw_sp_port, mlxsw_sp_qdisc,
				       p->qstats);
पूर्ण

अटल पूर्णांक
mlxsw_sp_qdisc_get_prio_stats(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			      काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			      काष्ठा tc_qopt_offload_stats *stats_ptr)
अणु
	काष्ठा mlxsw_sp_qdisc *tc_qdisc;
	u64 tx_packets = 0;
	u64 tx_bytes = 0;
	u64 backlog = 0;
	u64 drops = 0;
	पूर्णांक i;

	क्रम (i = 0; i < mlxsw_sp_qdisc->num_classes; i++) अणु
		tc_qdisc = &mlxsw_sp_qdisc->qdiscs[i];
		mlxsw_sp_qdisc_collect_tc_stats(mlxsw_sp_port, tc_qdisc,
						&tx_bytes, &tx_packets,
						&drops, &backlog);
	पूर्ण

	mlxsw_sp_qdisc_update_stats(mlxsw_sp_port->mlxsw_sp, mlxsw_sp_qdisc,
				    tx_bytes, tx_packets, drops, backlog,
				    stats_ptr);
	वापस 0;
पूर्ण

अटल व्योम
mlxsw_sp_setup_tc_qdisc_prio_clean_stats(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					 काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc)
अणु
	काष्ठा mlxsw_sp_qdisc_stats *stats_base;
	काष्ठा mlxsw_sp_port_xstats *xstats;
	काष्ठा rtnl_link_stats64 *stats;
	पूर्णांक i;

	xstats = &mlxsw_sp_port->periodic_hw_stats.xstats;
	stats = &mlxsw_sp_port->periodic_hw_stats.stats;
	stats_base = &mlxsw_sp_qdisc->stats_base;

	stats_base->tx_packets = stats->tx_packets;
	stats_base->tx_bytes = stats->tx_bytes;

	stats_base->drops = 0;
	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		stats_base->drops += mlxsw_sp_xstats_tail_drop(xstats, i);
		stats_base->drops += xstats->wred_drop[i];
	पूर्ण

	mlxsw_sp_qdisc->stats_base.backlog = 0;
पूर्ण

अटल काष्ठा mlxsw_sp_qdisc *
mlxsw_sp_qdisc_prio_find_class(काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			       u32 parent)
अणु
	पूर्णांक child_index = TC_H_MIN(parent);
	पूर्णांक band = child_index - 1;

	अगर (band < 0 || band >= mlxsw_sp_qdisc->num_classes)
		वापस शून्य;
	वापस &mlxsw_sp_qdisc->qdiscs[band];
पूर्ण

अटल काष्ठा mlxsw_sp_qdisc_ops mlxsw_sp_qdisc_ops_prio = अणु
	.type = MLXSW_SP_QDISC_PRIO,
	.check_params = mlxsw_sp_qdisc_prio_check_params,
	.replace = mlxsw_sp_qdisc_prio_replace,
	.unoffload = mlxsw_sp_qdisc_prio_unoffload,
	.destroy = mlxsw_sp_qdisc_prio_destroy,
	.get_stats = mlxsw_sp_qdisc_get_prio_stats,
	.clean_stats = mlxsw_sp_setup_tc_qdisc_prio_clean_stats,
	.find_class = mlxsw_sp_qdisc_prio_find_class,
	.num_classes = IEEE_8021QAZ_MAX_TCS,
पूर्ण;

अटल पूर्णांक
mlxsw_sp_qdisc_ets_check_params(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				व्योम *params)
अणु
	काष्ठा tc_ets_qopt_offload_replace_params *p = params;

	वापस __mlxsw_sp_qdisc_ets_check_params(p->bands);
पूर्ण

अटल पूर्णांक
mlxsw_sp_qdisc_ets_replace(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u32 handle,
			   काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			   व्योम *params)
अणु
	काष्ठा tc_ets_qopt_offload_replace_params *p = params;

	वापस __mlxsw_sp_qdisc_ets_replace(mlxsw_sp_port, mlxsw_sp_qdisc,
					    handle, p->bands, p->quanta,
					    p->weights, p->priomap);
पूर्ण

अटल व्योम
mlxsw_sp_qdisc_ets_unoffload(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			     काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			     व्योम *params)
अणु
	काष्ठा tc_ets_qopt_offload_replace_params *p = params;

	__mlxsw_sp_qdisc_ets_unoffload(mlxsw_sp_port, mlxsw_sp_qdisc,
				       p->qstats);
पूर्ण

अटल पूर्णांक
mlxsw_sp_qdisc_ets_destroy(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			   काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc)
अणु
	वापस __mlxsw_sp_qdisc_ets_destroy(mlxsw_sp_port, mlxsw_sp_qdisc);
पूर्ण

अटल काष्ठा mlxsw_sp_qdisc_ops mlxsw_sp_qdisc_ops_ets = अणु
	.type = MLXSW_SP_QDISC_ETS,
	.check_params = mlxsw_sp_qdisc_ets_check_params,
	.replace = mlxsw_sp_qdisc_ets_replace,
	.unoffload = mlxsw_sp_qdisc_ets_unoffload,
	.destroy = mlxsw_sp_qdisc_ets_destroy,
	.get_stats = mlxsw_sp_qdisc_get_prio_stats,
	.clean_stats = mlxsw_sp_setup_tc_qdisc_prio_clean_stats,
	.find_class = mlxsw_sp_qdisc_prio_find_class,
	.num_classes = IEEE_8021QAZ_MAX_TCS,
पूर्ण;

/* Linux allows linking of Qdiscs to arbitrary classes (so दीर्घ as the resulting
 * graph is मुक्त of cycles). These operations करो not change the parent handle
 * though, which means it can be incomplete (अगर there is more than one class
 * where the Qdisc in question is grafted) or outright wrong (अगर the Qdisc was
 * linked to a dअगरferent class and then हटाओd from the original class).
 *
 * E.g. consider this sequence of operations:
 *
 *  # tc qdisc add dev swp1 root handle 1: prio
 *  # tc qdisc add dev swp1 parent 1:3 handle 13: red limit 1000000 avpkt 10000
 *  RED: set bandwidth to 10Mbit
 *  # tc qdisc link dev swp1 handle 13: parent 1:2
 *
 * At this poपूर्णांक, both 1:2 and 1:3 have the same RED Qdisc instance as their
 * child. But RED will still only claim that 1:3 is its parent. If it's हटाओd
 * from that band, its only parent will be 1:2, but it will जारी to claim
 * that it is in fact 1:3.
 *
 * The notअगरication क्रम child Qdisc replace (e.g. TC_RED_REPLACE) comes beक्रमe
 * the notअगरication क्रम parent graft (e.g. TC_PRIO_GRAFT). We take the replace
 * notअगरication to offload the child Qdisc, based on its parent handle, and use
 * the graft operation to validate that the class where the child is actually
 * grafted corresponds to the parent handle. If the two करोn't match, we
 * unoffload the child.
 */
अटल पूर्णांक
__mlxsw_sp_qdisc_ets_graft(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			   काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			   u8 band, u32 child_handle)
अणु
	काष्ठा mlxsw_sp_qdisc *old_qdisc;
	u32 parent;

	अगर (band < mlxsw_sp_qdisc->num_classes &&
	    mlxsw_sp_qdisc->qdiscs[band].handle == child_handle)
		वापस 0;

	अगर (!child_handle) अणु
		/* This is an invisible FIFO replacing the original Qdisc.
		 * Ignore it--the original Qdisc's destroy will follow.
		 */
		वापस 0;
	पूर्ण

	/* See अगर the grafted qdisc is alपढ़ोy offloaded on any tclass. If so,
	 * unoffload it.
	 */
	old_qdisc = mlxsw_sp_qdisc_find_by_handle(mlxsw_sp_port,
						  child_handle);
	अगर (old_qdisc)
		mlxsw_sp_qdisc_destroy(mlxsw_sp_port, old_qdisc);

	parent = TC_H_MAKE(mlxsw_sp_qdisc->handle, band + 1);
	mlxsw_sp_qdisc = mlxsw_sp_qdisc->ops->find_class(mlxsw_sp_qdisc,
							 parent);
	अगर (!WARN_ON(!mlxsw_sp_qdisc))
		mlxsw_sp_qdisc_destroy(mlxsw_sp_port, mlxsw_sp_qdisc);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
mlxsw_sp_qdisc_prio_graft(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			  काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			  काष्ठा tc_prio_qopt_offload_graft_params *p)
अणु
	वापस __mlxsw_sp_qdisc_ets_graft(mlxsw_sp_port, mlxsw_sp_qdisc,
					  p->band, p->child_handle);
पूर्ण

अटल पूर्णांक __mlxsw_sp_setup_tc_prio(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				    काष्ठा tc_prio_qopt_offload *p)
अणु
	काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc;

	mlxsw_sp_qdisc = mlxsw_sp_qdisc_find(mlxsw_sp_port, p->parent, true);
	अगर (!mlxsw_sp_qdisc)
		वापस -EOPNOTSUPP;

	अगर (p->command == TC_PRIO_REPLACE)
		वापस mlxsw_sp_qdisc_replace(mlxsw_sp_port, p->handle,
					      mlxsw_sp_qdisc,
					      &mlxsw_sp_qdisc_ops_prio,
					      &p->replace_params);

	अगर (!mlxsw_sp_qdisc_compare(mlxsw_sp_qdisc, p->handle))
		वापस -EOPNOTSUPP;

	चयन (p->command) अणु
	हाल TC_PRIO_DESTROY:
		वापस mlxsw_sp_qdisc_destroy(mlxsw_sp_port, mlxsw_sp_qdisc);
	हाल TC_PRIO_STATS:
		वापस mlxsw_sp_qdisc_get_stats(mlxsw_sp_port, mlxsw_sp_qdisc,
						&p->stats);
	हाल TC_PRIO_GRAFT:
		वापस mlxsw_sp_qdisc_prio_graft(mlxsw_sp_port, mlxsw_sp_qdisc,
						 &p->graft_params);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

पूर्णांक mlxsw_sp_setup_tc_prio(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			   काष्ठा tc_prio_qopt_offload *p)
अणु
	पूर्णांक err;

	mutex_lock(&mlxsw_sp_port->qdisc->lock);
	err = __mlxsw_sp_setup_tc_prio(mlxsw_sp_port, p);
	mutex_unlock(&mlxsw_sp_port->qdisc->lock);

	वापस err;
पूर्ण

अटल पूर्णांक __mlxsw_sp_setup_tc_ets(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				   काष्ठा tc_ets_qopt_offload *p)
अणु
	काष्ठा mlxsw_sp_qdisc *mlxsw_sp_qdisc;

	mlxsw_sp_qdisc = mlxsw_sp_qdisc_find(mlxsw_sp_port, p->parent, true);
	अगर (!mlxsw_sp_qdisc)
		वापस -EOPNOTSUPP;

	अगर (p->command == TC_ETS_REPLACE)
		वापस mlxsw_sp_qdisc_replace(mlxsw_sp_port, p->handle,
					      mlxsw_sp_qdisc,
					      &mlxsw_sp_qdisc_ops_ets,
					      &p->replace_params);

	अगर (!mlxsw_sp_qdisc_compare(mlxsw_sp_qdisc, p->handle))
		वापस -EOPNOTSUPP;

	चयन (p->command) अणु
	हाल TC_ETS_DESTROY:
		वापस mlxsw_sp_qdisc_destroy(mlxsw_sp_port, mlxsw_sp_qdisc);
	हाल TC_ETS_STATS:
		वापस mlxsw_sp_qdisc_get_stats(mlxsw_sp_port, mlxsw_sp_qdisc,
						&p->stats);
	हाल TC_ETS_GRAFT:
		वापस __mlxsw_sp_qdisc_ets_graft(mlxsw_sp_port, mlxsw_sp_qdisc,
						  p->graft_params.band,
						  p->graft_params.child_handle);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

पूर्णांक mlxsw_sp_setup_tc_ets(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			  काष्ठा tc_ets_qopt_offload *p)
अणु
	पूर्णांक err;

	mutex_lock(&mlxsw_sp_port->qdisc->lock);
	err = __mlxsw_sp_setup_tc_ets(mlxsw_sp_port, p);
	mutex_unlock(&mlxsw_sp_port->qdisc->lock);

	वापस err;
पूर्ण

काष्ठा mlxsw_sp_qevent_block अणु
	काष्ठा list_head binding_list;
	काष्ठा list_head mall_entry_list;
	काष्ठा mlxsw_sp *mlxsw_sp;
पूर्ण;

काष्ठा mlxsw_sp_qevent_binding अणु
	काष्ठा list_head list;
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	u32 handle;
	पूर्णांक tclass_num;
	क्रमागत mlxsw_sp_span_trigger span_trigger;
पूर्ण;

अटल LIST_HEAD(mlxsw_sp_qevent_block_cb_list);

अटल पूर्णांक mlxsw_sp_qevent_span_configure(काष्ठा mlxsw_sp *mlxsw_sp,
					  काष्ठा mlxsw_sp_mall_entry *mall_entry,
					  काष्ठा mlxsw_sp_qevent_binding *qevent_binding,
					  स्थिर काष्ठा mlxsw_sp_span_agent_parms *agent_parms,
					  पूर्णांक *p_span_id)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = qevent_binding->mlxsw_sp_port;
	काष्ठा mlxsw_sp_span_trigger_parms trigger_parms = अणुपूर्ण;
	पूर्णांक span_id;
	पूर्णांक err;

	err = mlxsw_sp_span_agent_get(mlxsw_sp, &span_id, agent_parms);
	अगर (err)
		वापस err;

	err = mlxsw_sp_span_analyzed_port_get(mlxsw_sp_port, true);
	अगर (err)
		जाओ err_analyzed_port_get;

	trigger_parms.span_id = span_id;
	trigger_parms.probability_rate = 1;
	err = mlxsw_sp_span_agent_bind(mlxsw_sp, qevent_binding->span_trigger, mlxsw_sp_port,
				       &trigger_parms);
	अगर (err)
		जाओ err_agent_bind;

	err = mlxsw_sp_span_trigger_enable(mlxsw_sp_port, qevent_binding->span_trigger,
					   qevent_binding->tclass_num);
	अगर (err)
		जाओ err_trigger_enable;

	*p_span_id = span_id;
	वापस 0;

err_trigger_enable:
	mlxsw_sp_span_agent_unbind(mlxsw_sp, qevent_binding->span_trigger, mlxsw_sp_port,
				   &trigger_parms);
err_agent_bind:
	mlxsw_sp_span_analyzed_port_put(mlxsw_sp_port, true);
err_analyzed_port_get:
	mlxsw_sp_span_agent_put(mlxsw_sp, span_id);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_qevent_span_deconfigure(काष्ठा mlxsw_sp *mlxsw_sp,
					     काष्ठा mlxsw_sp_qevent_binding *qevent_binding,
					     पूर्णांक span_id)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = qevent_binding->mlxsw_sp_port;
	काष्ठा mlxsw_sp_span_trigger_parms trigger_parms = अणु
		.span_id = span_id,
	पूर्ण;

	mlxsw_sp_span_trigger_disable(mlxsw_sp_port, qevent_binding->span_trigger,
				      qevent_binding->tclass_num);
	mlxsw_sp_span_agent_unbind(mlxsw_sp, qevent_binding->span_trigger, mlxsw_sp_port,
				   &trigger_parms);
	mlxsw_sp_span_analyzed_port_put(mlxsw_sp_port, true);
	mlxsw_sp_span_agent_put(mlxsw_sp, span_id);
पूर्ण

अटल पूर्णांक mlxsw_sp_qevent_mirror_configure(काष्ठा mlxsw_sp *mlxsw_sp,
					    काष्ठा mlxsw_sp_mall_entry *mall_entry,
					    काष्ठा mlxsw_sp_qevent_binding *qevent_binding)
अणु
	काष्ठा mlxsw_sp_span_agent_parms agent_parms = अणु
		.to_dev = mall_entry->mirror.to_dev,
	पूर्ण;

	वापस mlxsw_sp_qevent_span_configure(mlxsw_sp, mall_entry, qevent_binding,
					      &agent_parms, &mall_entry->mirror.span_id);
पूर्ण

अटल व्योम mlxsw_sp_qevent_mirror_deconfigure(काष्ठा mlxsw_sp *mlxsw_sp,
					       काष्ठा mlxsw_sp_mall_entry *mall_entry,
					       काष्ठा mlxsw_sp_qevent_binding *qevent_binding)
अणु
	mlxsw_sp_qevent_span_deconfigure(mlxsw_sp, qevent_binding, mall_entry->mirror.span_id);
पूर्ण

अटल पूर्णांक mlxsw_sp_qevent_trap_configure(काष्ठा mlxsw_sp *mlxsw_sp,
					  काष्ठा mlxsw_sp_mall_entry *mall_entry,
					  काष्ठा mlxsw_sp_qevent_binding *qevent_binding)
अणु
	काष्ठा mlxsw_sp_span_agent_parms agent_parms = अणु
		.session_id = MLXSW_SP_SPAN_SESSION_ID_BUFFER,
	पूर्ण;
	पूर्णांक err;

	err = mlxsw_sp_trap_group_policer_hw_id_get(mlxsw_sp,
						    DEVLINK_TRAP_GROUP_GENERIC_ID_BUFFER_DROPS,
						    &agent_parms.policer_enable,
						    &agent_parms.policer_id);
	अगर (err)
		वापस err;

	वापस mlxsw_sp_qevent_span_configure(mlxsw_sp, mall_entry, qevent_binding,
					      &agent_parms, &mall_entry->trap.span_id);
पूर्ण

अटल व्योम mlxsw_sp_qevent_trap_deconfigure(काष्ठा mlxsw_sp *mlxsw_sp,
					     काष्ठा mlxsw_sp_mall_entry *mall_entry,
					     काष्ठा mlxsw_sp_qevent_binding *qevent_binding)
अणु
	mlxsw_sp_qevent_span_deconfigure(mlxsw_sp, qevent_binding, mall_entry->trap.span_id);
पूर्ण

अटल पूर्णांक mlxsw_sp_qevent_entry_configure(काष्ठा mlxsw_sp *mlxsw_sp,
					   काष्ठा mlxsw_sp_mall_entry *mall_entry,
					   काष्ठा mlxsw_sp_qevent_binding *qevent_binding)
अणु
	चयन (mall_entry->type) अणु
	हाल MLXSW_SP_MALL_ACTION_TYPE_MIRROR:
		वापस mlxsw_sp_qevent_mirror_configure(mlxsw_sp, mall_entry, qevent_binding);
	हाल MLXSW_SP_MALL_ACTION_TYPE_TRAP:
		वापस mlxsw_sp_qevent_trap_configure(mlxsw_sp, mall_entry, qevent_binding);
	शेष:
		/* This should have been validated away. */
		WARN_ON(1);
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम mlxsw_sp_qevent_entry_deconfigure(काष्ठा mlxsw_sp *mlxsw_sp,
					      काष्ठा mlxsw_sp_mall_entry *mall_entry,
					      काष्ठा mlxsw_sp_qevent_binding *qevent_binding)
अणु
	चयन (mall_entry->type) अणु
	हाल MLXSW_SP_MALL_ACTION_TYPE_MIRROR:
		वापस mlxsw_sp_qevent_mirror_deconfigure(mlxsw_sp, mall_entry, qevent_binding);
	हाल MLXSW_SP_MALL_ACTION_TYPE_TRAP:
		वापस mlxsw_sp_qevent_trap_deconfigure(mlxsw_sp, mall_entry, qevent_binding);
	शेष:
		WARN_ON(1);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp_qevent_binding_configure(काष्ठा mlxsw_sp_qevent_block *qevent_block,
					     काष्ठा mlxsw_sp_qevent_binding *qevent_binding)
अणु
	काष्ठा mlxsw_sp_mall_entry *mall_entry;
	पूर्णांक err;

	list_क्रम_each_entry(mall_entry, &qevent_block->mall_entry_list, list) अणु
		err = mlxsw_sp_qevent_entry_configure(qevent_block->mlxsw_sp, mall_entry,
						      qevent_binding);
		अगर (err)
			जाओ err_entry_configure;
	पूर्ण

	वापस 0;

err_entry_configure:
	list_क्रम_each_entry_जारी_reverse(mall_entry, &qevent_block->mall_entry_list, list)
		mlxsw_sp_qevent_entry_deconfigure(qevent_block->mlxsw_sp, mall_entry,
						  qevent_binding);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_qevent_binding_deconfigure(काष्ठा mlxsw_sp_qevent_block *qevent_block,
						काष्ठा mlxsw_sp_qevent_binding *qevent_binding)
अणु
	काष्ठा mlxsw_sp_mall_entry *mall_entry;

	list_क्रम_each_entry(mall_entry, &qevent_block->mall_entry_list, list)
		mlxsw_sp_qevent_entry_deconfigure(qevent_block->mlxsw_sp, mall_entry,
						  qevent_binding);
पूर्ण

अटल पूर्णांक mlxsw_sp_qevent_block_configure(काष्ठा mlxsw_sp_qevent_block *qevent_block)
अणु
	काष्ठा mlxsw_sp_qevent_binding *qevent_binding;
	पूर्णांक err;

	list_क्रम_each_entry(qevent_binding, &qevent_block->binding_list, list) अणु
		err = mlxsw_sp_qevent_binding_configure(qevent_block, qevent_binding);
		अगर (err)
			जाओ err_binding_configure;
	पूर्ण

	वापस 0;

err_binding_configure:
	list_क्रम_each_entry_जारी_reverse(qevent_binding, &qevent_block->binding_list, list)
		mlxsw_sp_qevent_binding_deconfigure(qevent_block, qevent_binding);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_qevent_block_deconfigure(काष्ठा mlxsw_sp_qevent_block *qevent_block)
अणु
	काष्ठा mlxsw_sp_qevent_binding *qevent_binding;

	list_क्रम_each_entry(qevent_binding, &qevent_block->binding_list, list)
		mlxsw_sp_qevent_binding_deconfigure(qevent_block, qevent_binding);
पूर्ण

अटल काष्ठा mlxsw_sp_mall_entry *
mlxsw_sp_qevent_mall_entry_find(काष्ठा mlxsw_sp_qevent_block *block, अचिन्हित दीर्घ cookie)
अणु
	काष्ठा mlxsw_sp_mall_entry *mall_entry;

	list_क्रम_each_entry(mall_entry, &block->mall_entry_list, list)
		अगर (mall_entry->cookie == cookie)
			वापस mall_entry;

	वापस शून्य;
पूर्ण

अटल पूर्णांक mlxsw_sp_qevent_mall_replace(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_qevent_block *qevent_block,
					काष्ठा tc_cls_matchall_offload *f)
अणु
	काष्ठा mlxsw_sp_mall_entry *mall_entry;
	काष्ठा flow_action_entry *act;
	पूर्णांक err;

	/* It should not currently be possible to replace a matchall rule. So
	 * this must be a new rule.
	 */
	अगर (!list_empty(&qevent_block->mall_entry_list)) अणु
		NL_SET_ERR_MSG(f->common.extack, "At most one filter supported");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (f->rule->action.num_entries != 1) अणु
		NL_SET_ERR_MSG(f->common.extack, "Only singular actions supported");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (f->common.chain_index) अणु
		NL_SET_ERR_MSG(f->common.extack, "Only chain 0 is supported");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (f->common.protocol != htons(ETH_P_ALL)) अणु
		NL_SET_ERR_MSG(f->common.extack, "Protocol matching not supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	act = &f->rule->action.entries[0];
	अगर (!(act->hw_stats & FLOW_ACTION_HW_STATS_DISABLED)) अणु
		NL_SET_ERR_MSG(f->common.extack, "HW counters not supported on qevents");
		वापस -EOPNOTSUPP;
	पूर्ण

	mall_entry = kzalloc(माप(*mall_entry), GFP_KERNEL);
	अगर (!mall_entry)
		वापस -ENOMEM;
	mall_entry->cookie = f->cookie;

	अगर (act->id == FLOW_ACTION_MIRRED) अणु
		mall_entry->type = MLXSW_SP_MALL_ACTION_TYPE_MIRROR;
		mall_entry->mirror.to_dev = act->dev;
	पूर्ण अन्यथा अगर (act->id == FLOW_ACTION_TRAP) अणु
		mall_entry->type = MLXSW_SP_MALL_ACTION_TYPE_TRAP;
	पूर्ण अन्यथा अणु
		NL_SET_ERR_MSG(f->common.extack, "Unsupported action");
		err = -EOPNOTSUPP;
		जाओ err_unsupported_action;
	पूर्ण

	list_add_tail(&mall_entry->list, &qevent_block->mall_entry_list);

	err = mlxsw_sp_qevent_block_configure(qevent_block);
	अगर (err)
		जाओ err_block_configure;

	वापस 0;

err_block_configure:
	list_del(&mall_entry->list);
err_unsupported_action:
	kमुक्त(mall_entry);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_qevent_mall_destroy(काष्ठा mlxsw_sp_qevent_block *qevent_block,
					 काष्ठा tc_cls_matchall_offload *f)
अणु
	काष्ठा mlxsw_sp_mall_entry *mall_entry;

	mall_entry = mlxsw_sp_qevent_mall_entry_find(qevent_block, f->cookie);
	अगर (!mall_entry)
		वापस;

	mlxsw_sp_qevent_block_deconfigure(qevent_block);

	list_del(&mall_entry->list);
	kमुक्त(mall_entry);
पूर्ण

अटल पूर्णांक mlxsw_sp_qevent_block_mall_cb(काष्ठा mlxsw_sp_qevent_block *qevent_block,
					 काष्ठा tc_cls_matchall_offload *f)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = qevent_block->mlxsw_sp;

	चयन (f->command) अणु
	हाल TC_CLSMATCHALL_REPLACE:
		वापस mlxsw_sp_qevent_mall_replace(mlxsw_sp, qevent_block, f);
	हाल TC_CLSMATCHALL_DESTROY:
		mlxsw_sp_qevent_mall_destroy(qevent_block, f);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp_qevent_block_cb(क्रमागत tc_setup_type type, व्योम *type_data, व्योम *cb_priv)
अणु
	काष्ठा mlxsw_sp_qevent_block *qevent_block = cb_priv;

	चयन (type) अणु
	हाल TC_SETUP_CLSMATCHALL:
		वापस mlxsw_sp_qevent_block_mall_cb(qevent_block, type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल काष्ठा mlxsw_sp_qevent_block *mlxsw_sp_qevent_block_create(काष्ठा mlxsw_sp *mlxsw_sp,
								  काष्ठा net *net)
अणु
	काष्ठा mlxsw_sp_qevent_block *qevent_block;

	qevent_block = kzalloc(माप(*qevent_block), GFP_KERNEL);
	अगर (!qevent_block)
		वापस शून्य;

	INIT_LIST_HEAD(&qevent_block->binding_list);
	INIT_LIST_HEAD(&qevent_block->mall_entry_list);
	qevent_block->mlxsw_sp = mlxsw_sp;
	वापस qevent_block;
पूर्ण

अटल व्योम
mlxsw_sp_qevent_block_destroy(काष्ठा mlxsw_sp_qevent_block *qevent_block)
अणु
	WARN_ON(!list_empty(&qevent_block->binding_list));
	WARN_ON(!list_empty(&qevent_block->mall_entry_list));
	kमुक्त(qevent_block);
पूर्ण

अटल व्योम mlxsw_sp_qevent_block_release(व्योम *cb_priv)
अणु
	काष्ठा mlxsw_sp_qevent_block *qevent_block = cb_priv;

	mlxsw_sp_qevent_block_destroy(qevent_block);
पूर्ण

अटल काष्ठा mlxsw_sp_qevent_binding *
mlxsw_sp_qevent_binding_create(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u32 handle, पूर्णांक tclass_num,
			       क्रमागत mlxsw_sp_span_trigger span_trigger)
अणु
	काष्ठा mlxsw_sp_qevent_binding *binding;

	binding = kzalloc(माप(*binding), GFP_KERNEL);
	अगर (!binding)
		वापस ERR_PTR(-ENOMEM);

	binding->mlxsw_sp_port = mlxsw_sp_port;
	binding->handle = handle;
	binding->tclass_num = tclass_num;
	binding->span_trigger = span_trigger;
	वापस binding;
पूर्ण

अटल व्योम
mlxsw_sp_qevent_binding_destroy(काष्ठा mlxsw_sp_qevent_binding *binding)
अणु
	kमुक्त(binding);
पूर्ण

अटल काष्ठा mlxsw_sp_qevent_binding *
mlxsw_sp_qevent_binding_lookup(काष्ठा mlxsw_sp_qevent_block *block,
			       काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			       u32 handle,
			       क्रमागत mlxsw_sp_span_trigger span_trigger)
अणु
	काष्ठा mlxsw_sp_qevent_binding *qevent_binding;

	list_क्रम_each_entry(qevent_binding, &block->binding_list, list)
		अगर (qevent_binding->mlxsw_sp_port == mlxsw_sp_port &&
		    qevent_binding->handle == handle &&
		    qevent_binding->span_trigger == span_trigger)
			वापस qevent_binding;
	वापस शून्य;
पूर्ण

अटल पूर्णांक mlxsw_sp_setup_tc_block_qevent_bind(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					       काष्ठा flow_block_offload *f,
					       क्रमागत mlxsw_sp_span_trigger span_trigger)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_qevent_binding *qevent_binding;
	काष्ठा mlxsw_sp_qevent_block *qevent_block;
	काष्ठा flow_block_cb *block_cb;
	काष्ठा mlxsw_sp_qdisc *qdisc;
	bool रेजिस्टर_block = false;
	पूर्णांक err;

	block_cb = flow_block_cb_lookup(f->block, mlxsw_sp_qevent_block_cb, mlxsw_sp);
	अगर (!block_cb) अणु
		qevent_block = mlxsw_sp_qevent_block_create(mlxsw_sp, f->net);
		अगर (!qevent_block)
			वापस -ENOMEM;
		block_cb = flow_block_cb_alloc(mlxsw_sp_qevent_block_cb, mlxsw_sp, qevent_block,
					       mlxsw_sp_qevent_block_release);
		अगर (IS_ERR(block_cb)) अणु
			mlxsw_sp_qevent_block_destroy(qevent_block);
			वापस PTR_ERR(block_cb);
		पूर्ण
		रेजिस्टर_block = true;
	पूर्ण अन्यथा अणु
		qevent_block = flow_block_cb_priv(block_cb);
	पूर्ण
	flow_block_cb_incref(block_cb);

	qdisc = mlxsw_sp_qdisc_find_by_handle(mlxsw_sp_port, f->sch->handle);
	अगर (!qdisc) अणु
		NL_SET_ERR_MSG(f->extack, "Qdisc not offloaded");
		err = -ENOENT;
		जाओ err_find_qdisc;
	पूर्ण

	अगर (WARN_ON(mlxsw_sp_qevent_binding_lookup(qevent_block, mlxsw_sp_port, f->sch->handle,
						   span_trigger))) अणु
		err = -EEXIST;
		जाओ err_binding_exists;
	पूर्ण

	qevent_binding = mlxsw_sp_qevent_binding_create(mlxsw_sp_port, f->sch->handle,
							qdisc->tclass_num, span_trigger);
	अगर (IS_ERR(qevent_binding)) अणु
		err = PTR_ERR(qevent_binding);
		जाओ err_binding_create;
	पूर्ण

	err = mlxsw_sp_qevent_binding_configure(qevent_block, qevent_binding);
	अगर (err)
		जाओ err_binding_configure;

	list_add(&qevent_binding->list, &qevent_block->binding_list);

	अगर (रेजिस्टर_block) अणु
		flow_block_cb_add(block_cb, f);
		list_add_tail(&block_cb->driver_list, &mlxsw_sp_qevent_block_cb_list);
	पूर्ण

	वापस 0;

err_binding_configure:
	mlxsw_sp_qevent_binding_destroy(qevent_binding);
err_binding_create:
err_binding_exists:
err_find_qdisc:
	अगर (!flow_block_cb_decref(block_cb))
		flow_block_cb_मुक्त(block_cb);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_setup_tc_block_qevent_unbind(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
						  काष्ठा flow_block_offload *f,
						  क्रमागत mlxsw_sp_span_trigger span_trigger)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_qevent_binding *qevent_binding;
	काष्ठा mlxsw_sp_qevent_block *qevent_block;
	काष्ठा flow_block_cb *block_cb;

	block_cb = flow_block_cb_lookup(f->block, mlxsw_sp_qevent_block_cb, mlxsw_sp);
	अगर (!block_cb)
		वापस;
	qevent_block = flow_block_cb_priv(block_cb);

	qevent_binding = mlxsw_sp_qevent_binding_lookup(qevent_block, mlxsw_sp_port, f->sch->handle,
							span_trigger);
	अगर (!qevent_binding)
		वापस;

	list_del(&qevent_binding->list);
	mlxsw_sp_qevent_binding_deconfigure(qevent_block, qevent_binding);
	mlxsw_sp_qevent_binding_destroy(qevent_binding);

	अगर (!flow_block_cb_decref(block_cb)) अणु
		flow_block_cb_हटाओ(block_cb, f);
		list_del(&block_cb->driver_list);
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp_setup_tc_block_qevent(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					  काष्ठा flow_block_offload *f,
					  क्रमागत mlxsw_sp_span_trigger span_trigger)
अणु
	f->driver_block_list = &mlxsw_sp_qevent_block_cb_list;

	चयन (f->command) अणु
	हाल FLOW_BLOCK_BIND:
		वापस mlxsw_sp_setup_tc_block_qevent_bind(mlxsw_sp_port, f, span_trigger);
	हाल FLOW_BLOCK_UNBIND:
		mlxsw_sp_setup_tc_block_qevent_unbind(mlxsw_sp_port, f, span_trigger);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

पूर्णांक mlxsw_sp_setup_tc_block_qevent_early_drop(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					      काष्ठा flow_block_offload *f)
अणु
	वापस mlxsw_sp_setup_tc_block_qevent(mlxsw_sp_port, f, MLXSW_SP_SPAN_TRIGGER_EARLY_DROP);
पूर्ण

पूर्णांक mlxsw_sp_tc_qdisc_init(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	काष्ठा mlxsw_sp_qdisc_state *qdisc_state;

	qdisc_state = kzalloc(माप(*qdisc_state), GFP_KERNEL);
	अगर (!qdisc_state)
		वापस -ENOMEM;

	mutex_init(&qdisc_state->lock);
	qdisc_state->root_qdisc.prio_biपंचांगap = 0xff;
	qdisc_state->root_qdisc.tclass_num = MLXSW_SP_PORT_DEFAULT_TCLASS;
	mlxsw_sp_port->qdisc = qdisc_state;
	वापस 0;
पूर्ण

व्योम mlxsw_sp_tc_qdisc_fini(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	mutex_destroy(&mlxsw_sp_port->qdisc->lock);
	kमुक्त(mlxsw_sp_port->qdisc);
पूर्ण
