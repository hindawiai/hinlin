<शैली गुरु>
/*
 * Copyright (c) 2005, 2006, 2007, 2008 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2005, 2006, 2007 Cisco Systems, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *	- Redistributions of source code must retain the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer.
 *
 *	- Redistributions in binary क्रमm must reproduce the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer in the करोcumentation and/or other materials
 *	  provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/dma-mapping.h>

#समावेश <linux/mlx4/cmd.h>
#समावेश <linux/cpu_rmap.h>

#समावेश "mlx4.h"
#समावेश "fw.h"

क्रमागत अणु
	MLX4_IRQNAME_SIZE	= 32
पूर्ण;

क्रमागत अणु
	MLX4_NUM_ASYNC_EQE	= 0x100,
	MLX4_NUM_SPARE_EQE	= 0x80,
	MLX4_EQ_ENTRY_SIZE	= 0x20
पूर्ण;

#घोषणा MLX4_EQ_STATUS_OK	   ( 0 << 28)
#घोषणा MLX4_EQ_STATUS_WRITE_FAIL  (10 << 28)
#घोषणा MLX4_EQ_OWNER_SW	   ( 0 << 24)
#घोषणा MLX4_EQ_OWNER_HW	   ( 1 << 24)
#घोषणा MLX4_EQ_FLAG_EC		   ( 1 << 18)
#घोषणा MLX4_EQ_FLAG_OI		   ( 1 << 17)
#घोषणा MLX4_EQ_STATE_ARMED	   ( 9 <<  8)
#घोषणा MLX4_EQ_STATE_FIRED	   (10 <<  8)
#घोषणा MLX4_EQ_STATE_ALWAYS_ARMED (11 <<  8)

#घोषणा MLX4_ASYNC_EVENT_MASK ((1ull << MLX4_EVENT_TYPE_PATH_MIG)	    | \
			       (1ull << MLX4_EVENT_TYPE_COMM_EST)	    | \
			       (1ull << MLX4_EVENT_TYPE_SQ_DRAINED)	    | \
			       (1ull << MLX4_EVENT_TYPE_CQ_ERROR)	    | \
			       (1ull << MLX4_EVENT_TYPE_WQ_CATAS_ERROR)	    | \
			       (1ull << MLX4_EVENT_TYPE_EEC_CATAS_ERROR)    | \
			       (1ull << MLX4_EVENT_TYPE_PATH_MIG_FAILED)    | \
			       (1ull << MLX4_EVENT_TYPE_WQ_INVAL_REQ_ERROR) | \
			       (1ull << MLX4_EVENT_TYPE_WQ_ACCESS_ERROR)    | \
			       (1ull << MLX4_EVENT_TYPE_PORT_CHANGE)	    | \
			       (1ull << MLX4_EVENT_TYPE_ECC_DETECT)	    | \
			       (1ull << MLX4_EVENT_TYPE_SRQ_CATAS_ERROR)    | \
			       (1ull << MLX4_EVENT_TYPE_SRQ_QP_LAST_WQE)    | \
			       (1ull << MLX4_EVENT_TYPE_SRQ_LIMIT)	    | \
			       (1ull << MLX4_EVENT_TYPE_CMD)		    | \
			       (1ull << MLX4_EVENT_TYPE_OP_REQUIRED)	    | \
			       (1ull << MLX4_EVENT_TYPE_COMM_CHANNEL)       | \
			       (1ull << MLX4_EVENT_TYPE_FLR_EVENT)	    | \
			       (1ull << MLX4_EVENT_TYPE_FATAL_WARNING))

अटल u64 get_async_ev_mask(काष्ठा mlx4_dev *dev)
अणु
	u64 async_ev_mask = MLX4_ASYNC_EVENT_MASK;
	अगर (dev->caps.flags & MLX4_DEV_CAP_FLAG_PORT_MNG_CHG_EV)
		async_ev_mask |= (1ull << MLX4_EVENT_TYPE_PORT_MNG_CHG_EVENT);
	अगर (dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_RECOVERABLE_ERROR_EVENT)
		async_ev_mask |= (1ull << MLX4_EVENT_TYPE_RECOVERABLE_ERROR_EVENT);

	वापस async_ev_mask;
पूर्ण

अटल व्योम eq_set_ci(काष्ठा mlx4_eq *eq, पूर्णांक req_not)
अणु
	__raw_ग_लिखोl((__क्रमce u32) cpu_to_be32((eq->cons_index & 0xffffff) |
					       req_not << 31),
		     eq->करोorbell);
	/* We still want ordering, just not swabbing, so add a barrier */
	wmb();
पूर्ण

अटल काष्ठा mlx4_eqe *get_eqe(काष्ठा mlx4_eq *eq, u32 entry, u8 eqe_factor,
				u8 eqe_size)
अणु
	/* (entry & (eq->nent - 1)) gives us a cyclic array */
	अचिन्हित दीर्घ offset = (entry & (eq->nent - 1)) * eqe_size;
	/* CX3 is capable of extending the EQE from 32 to 64 bytes with
	 * strides of 64B,128B and 256B.
	 * When 64B EQE is used, the first (in the lower addresses)
	 * 32 bytes in the 64 byte EQE are reserved and the next 32 bytes
	 * contain the legacy EQE inक्रमmation.
	 * In all other हालs, the first 32B contains the legacy EQE info.
	 */
	वापस eq->page_list[offset / PAGE_SIZE].buf + (offset + (eqe_factor ? MLX4_EQ_ENTRY_SIZE : 0)) % PAGE_SIZE;
पूर्ण

अटल काष्ठा mlx4_eqe *next_eqe_sw(काष्ठा mlx4_eq *eq, u8 eqe_factor, u8 size)
अणु
	काष्ठा mlx4_eqe *eqe = get_eqe(eq, eq->cons_index, eqe_factor, size);
	वापस !!(eqe->owner & 0x80) ^ !!(eq->cons_index & eq->nent) ? शून्य : eqe;
पूर्ण

अटल काष्ठा mlx4_eqe *next_slave_event_eqe(काष्ठा mlx4_slave_event_eq *slave_eq)
अणु
	काष्ठा mlx4_eqe *eqe =
		&slave_eq->event_eqe[slave_eq->cons & (SLAVE_EVENT_EQ_SIZE - 1)];
	वापस (!!(eqe->owner & 0x80) ^
		!!(slave_eq->cons & SLAVE_EVENT_EQ_SIZE)) ?
		eqe : शून्य;
पूर्ण

व्योम mlx4_gen_slave_eqe(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx4_mfunc_master_ctx *master =
		container_of(work, काष्ठा mlx4_mfunc_master_ctx,
			     slave_event_work);
	काष्ठा mlx4_mfunc *mfunc =
		container_of(master, काष्ठा mlx4_mfunc, master);
	काष्ठा mlx4_priv *priv = container_of(mfunc, काष्ठा mlx4_priv, mfunc);
	काष्ठा mlx4_dev *dev = &priv->dev;
	काष्ठा mlx4_slave_event_eq *slave_eq = &mfunc->master.slave_eq;
	काष्ठा mlx4_eqe *eqe;
	u8 slave;
	पूर्णांक i, phys_port, slave_port;

	क्रम (eqe = next_slave_event_eqe(slave_eq); eqe;
	      eqe = next_slave_event_eqe(slave_eq)) अणु
		slave = eqe->slave_id;

		अगर (eqe->type == MLX4_EVENT_TYPE_PORT_CHANGE &&
		    eqe->subtype == MLX4_PORT_CHANGE_SUBTYPE_DOWN &&
		    mlx4_is_bonded(dev)) अणु
			काष्ठा mlx4_port_cap port_cap;

			अगर (!mlx4_QUERY_PORT(dev, 1, &port_cap) && port_cap.link_state)
				जाओ consume;

			अगर (!mlx4_QUERY_PORT(dev, 2, &port_cap) && port_cap.link_state)
				जाओ consume;
		पूर्ण
		/* All active slaves need to receive the event */
		अगर (slave == ALL_SLAVES) अणु
			क्रम (i = 0; i <= dev->persist->num_vfs; i++) अणु
				phys_port = 0;
				अगर (eqe->type == MLX4_EVENT_TYPE_PORT_MNG_CHG_EVENT &&
				    eqe->subtype == MLX4_DEV_PMC_SUBTYPE_PORT_INFO) अणु
					phys_port  = eqe->event.port_mgmt_change.port;
					slave_port = mlx4_phys_to_slave_port(dev, i, phys_port);
					अगर (slave_port < 0) /* VF करोesn't have this port */
						जारी;
					eqe->event.port_mgmt_change.port = slave_port;
				पूर्ण
				अगर (mlx4_GEN_EQE(dev, i, eqe))
					mlx4_warn(dev, "Failed to generate event for slave %d\n",
						  i);
				अगर (phys_port)
					eqe->event.port_mgmt_change.port = phys_port;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (mlx4_GEN_EQE(dev, slave, eqe))
				mlx4_warn(dev, "Failed to generate event for slave %d\n",
					  slave);
		पूर्ण
consume:
		++slave_eq->cons;
	पूर्ण
पूर्ण


अटल व्योम slave_event(काष्ठा mlx4_dev *dev, u8 slave, काष्ठा mlx4_eqe *eqe)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_slave_event_eq *slave_eq = &priv->mfunc.master.slave_eq;
	काष्ठा mlx4_eqe *s_eqe;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&slave_eq->event_lock, flags);
	s_eqe = &slave_eq->event_eqe[slave_eq->prod & (SLAVE_EVENT_EQ_SIZE - 1)];
	अगर ((!!(s_eqe->owner & 0x80)) ^
	    (!!(slave_eq->prod & SLAVE_EVENT_EQ_SIZE))) अणु
		mlx4_warn(dev, "Master failed to generate an EQE for slave: %d. No free EQE on slave events queue\n",
			  slave);
		spin_unlock_irqrestore(&slave_eq->event_lock, flags);
		वापस;
	पूर्ण

	स_नकल(s_eqe, eqe, माप(काष्ठा mlx4_eqe) - 1);
	s_eqe->slave_id = slave;
	/* ensure all inक्रमmation is written beक्रमe setting the ownersip bit */
	dma_wmb();
	s_eqe->owner = !!(slave_eq->prod & SLAVE_EVENT_EQ_SIZE) ? 0x0 : 0x80;
	++slave_eq->prod;

	queue_work(priv->mfunc.master.comm_wq,
		   &priv->mfunc.master.slave_event_work);
	spin_unlock_irqrestore(&slave_eq->event_lock, flags);
पूर्ण

अटल व्योम mlx4_slave_event(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			     काष्ठा mlx4_eqe *eqe)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	अगर (slave < 0 || slave > dev->persist->num_vfs ||
	    slave == dev->caps.function ||
	    !priv->mfunc.master.slave_state[slave].active)
		वापस;

	slave_event(dev, slave, eqe);
पूर्ण

#अगर defined(CONFIG_SMP)
अटल व्योम mlx4_set_eq_affinity_hपूर्णांक(काष्ठा mlx4_priv *priv, पूर्णांक vec)
अणु
	पूर्णांक hपूर्णांक_err;
	काष्ठा mlx4_dev *dev = &priv->dev;
	काष्ठा mlx4_eq *eq = &priv->eq_table.eq[vec];

	अगर (!cpumask_available(eq->affinity_mask) ||
	    cpumask_empty(eq->affinity_mask))
		वापस;

	hपूर्णांक_err = irq_set_affinity_hपूर्णांक(eq->irq, eq->affinity_mask);
	अगर (hपूर्णांक_err)
		mlx4_warn(dev, "irq_set_affinity_hint failed, err %d\n", hपूर्णांक_err);
पूर्ण
#पूर्ण_अगर

पूर्णांक mlx4_gen_pkey_eqe(काष्ठा mlx4_dev *dev, पूर्णांक slave, u8 port)
अणु
	काष्ठा mlx4_eqe eqe;

	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_slave_state *s_slave = &priv->mfunc.master.slave_state[slave];

	अगर (!s_slave->active)
		वापस 0;

	स_रखो(&eqe, 0, माप(eqe));

	eqe.type = MLX4_EVENT_TYPE_PORT_MNG_CHG_EVENT;
	eqe.subtype = MLX4_DEV_PMC_SUBTYPE_PKEY_TABLE;
	eqe.event.port_mgmt_change.port = mlx4_phys_to_slave_port(dev, slave, port);

	वापस mlx4_GEN_EQE(dev, slave, &eqe);
पूर्ण
EXPORT_SYMBOL(mlx4_gen_pkey_eqe);

पूर्णांक mlx4_gen_guid_change_eqe(काष्ठा mlx4_dev *dev, पूर्णांक slave, u8 port)
अणु
	काष्ठा mlx4_eqe eqe;

	/*करोn't send if we don't have the that slave */
	अगर (dev->persist->num_vfs < slave)
		वापस 0;
	स_रखो(&eqe, 0, माप(eqe));

	eqe.type = MLX4_EVENT_TYPE_PORT_MNG_CHG_EVENT;
	eqe.subtype = MLX4_DEV_PMC_SUBTYPE_GUID_INFO;
	eqe.event.port_mgmt_change.port = mlx4_phys_to_slave_port(dev, slave, port);

	वापस mlx4_GEN_EQE(dev, slave, &eqe);
पूर्ण
EXPORT_SYMBOL(mlx4_gen_guid_change_eqe);

पूर्णांक mlx4_gen_port_state_change_eqe(काष्ठा mlx4_dev *dev, पूर्णांक slave, u8 port,
				   u8 port_subtype_change)
अणु
	काष्ठा mlx4_eqe eqe;
	u8 slave_port = mlx4_phys_to_slave_port(dev, slave, port);

	/*करोn't send if we don't have the that slave */
	अगर (dev->persist->num_vfs < slave)
		वापस 0;
	स_रखो(&eqe, 0, माप(eqe));

	eqe.type = MLX4_EVENT_TYPE_PORT_CHANGE;
	eqe.subtype = port_subtype_change;
	eqe.event.port_change.port = cpu_to_be32(slave_port << 28);

	mlx4_dbg(dev, "%s: sending: %d to slave: %d on port: %d\n", __func__,
		 port_subtype_change, slave, port);
	वापस mlx4_GEN_EQE(dev, slave, &eqe);
पूर्ण
EXPORT_SYMBOL(mlx4_gen_port_state_change_eqe);

क्रमागत slave_port_state mlx4_get_slave_port_state(काष्ठा mlx4_dev *dev, पूर्णांक slave, u8 port)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_slave_state *s_state = priv->mfunc.master.slave_state;
	काष्ठा mlx4_active_ports actv_ports = mlx4_get_active_ports(dev, slave);

	अगर (slave >= dev->num_slaves || port > dev->caps.num_ports ||
	    port <= 0 || !test_bit(port - 1, actv_ports.ports)) अणु
		pr_err("%s: Error: asking for slave:%d, port:%d\n",
		       __func__, slave, port);
		वापस SLAVE_PORT_DOWN;
	पूर्ण
	वापस s_state[slave].port_state[port];
पूर्ण
EXPORT_SYMBOL(mlx4_get_slave_port_state);

अटल पूर्णांक mlx4_set_slave_port_state(काष्ठा mlx4_dev *dev, पूर्णांक slave, u8 port,
				     क्रमागत slave_port_state state)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_slave_state *s_state = priv->mfunc.master.slave_state;
	काष्ठा mlx4_active_ports actv_ports = mlx4_get_active_ports(dev, slave);

	अगर (slave >= dev->num_slaves || port > dev->caps.num_ports ||
	    port <= 0 || !test_bit(port - 1, actv_ports.ports)) अणु
		pr_err("%s: Error: asking for slave:%d, port:%d\n",
		       __func__, slave, port);
		वापस -1;
	पूर्ण
	s_state[slave].port_state[port] = state;

	वापस 0;
पूर्ण

अटल व्योम set_all_slave_state(काष्ठा mlx4_dev *dev, u8 port, पूर्णांक event)
अणु
	पूर्णांक i;
	क्रमागत slave_port_gen_event gen_event;
	काष्ठा mlx4_slaves_pport slaves_pport = mlx4_phys_to_slaves_pport(dev,
									  port);

	क्रम (i = 0; i < dev->persist->num_vfs + 1; i++)
		अगर (test_bit(i, slaves_pport.slaves))
			set_and_calc_slave_port_state(dev, i, port,
						      event, &gen_event);
पूर्ण
/**************************************************************************
	The function get as input the new event to that port,
	and according to the prev state change the slave's port state.
	The events are:
		MLX4_PORT_STATE_DEV_EVENT_PORT_DOWN,
		MLX4_PORT_STATE_DEV_EVENT_PORT_UP
		MLX4_PORT_STATE_IB_EVENT_GID_VALID
		MLX4_PORT_STATE_IB_EVENT_GID_INVALID
***************************************************************************/
पूर्णांक set_and_calc_slave_port_state(काष्ठा mlx4_dev *dev, पूर्णांक slave,
				  u8 port, पूर्णांक event,
				  क्रमागत slave_port_gen_event *gen_event)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_slave_state *ctx = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -1;
	काष्ठा mlx4_active_ports actv_ports = mlx4_get_active_ports(dev, slave);
	क्रमागत slave_port_state cur_state =
		mlx4_get_slave_port_state(dev, slave, port);

	*gen_event = SLAVE_PORT_GEN_EVENT_NONE;

	अगर (slave >= dev->num_slaves || port > dev->caps.num_ports ||
	    port <= 0 || !test_bit(port - 1, actv_ports.ports)) अणु
		pr_err("%s: Error: asking for slave:%d, port:%d\n",
		       __func__, slave, port);
		वापस ret;
	पूर्ण

	ctx = &priv->mfunc.master.slave_state[slave];
	spin_lock_irqsave(&ctx->lock, flags);

	चयन (cur_state) अणु
	हाल SLAVE_PORT_DOWN:
		अगर (MLX4_PORT_STATE_DEV_EVENT_PORT_UP == event)
			mlx4_set_slave_port_state(dev, slave, port,
						  SLAVE_PENDING_UP);
		अवरोध;
	हाल SLAVE_PENDING_UP:
		अगर (MLX4_PORT_STATE_DEV_EVENT_PORT_DOWN == event)
			mlx4_set_slave_port_state(dev, slave, port,
						  SLAVE_PORT_DOWN);
		अन्यथा अगर (MLX4_PORT_STATE_IB_PORT_STATE_EVENT_GID_VALID == event) अणु
			mlx4_set_slave_port_state(dev, slave, port,
						  SLAVE_PORT_UP);
			*gen_event = SLAVE_PORT_GEN_EVENT_UP;
		पूर्ण
		अवरोध;
	हाल SLAVE_PORT_UP:
		अगर (MLX4_PORT_STATE_DEV_EVENT_PORT_DOWN == event) अणु
			mlx4_set_slave_port_state(dev, slave, port,
						  SLAVE_PORT_DOWN);
			*gen_event = SLAVE_PORT_GEN_EVENT_DOWN;
		पूर्ण अन्यथा अगर (MLX4_PORT_STATE_IB_EVENT_GID_INVALID ==
				event) अणु
			mlx4_set_slave_port_state(dev, slave, port,
						  SLAVE_PENDING_UP);
			*gen_event = SLAVE_PORT_GEN_EVENT_DOWN;
		पूर्ण
		अवरोध;
	शेष:
		pr_err("%s: BUG!!! UNKNOWN state: slave:%d, port:%d\n",
		       __func__, slave, port);
		जाओ out;
	पूर्ण
	ret = mlx4_get_slave_port_state(dev, slave, port);

out:
	spin_unlock_irqrestore(&ctx->lock, flags);
	वापस ret;
पूर्ण

EXPORT_SYMBOL(set_and_calc_slave_port_state);

पूर्णांक mlx4_gen_slaves_port_mgt_ev(काष्ठा mlx4_dev *dev, u8 port, पूर्णांक attr)
अणु
	काष्ठा mlx4_eqe eqe;

	स_रखो(&eqe, 0, माप(eqe));

	eqe.type = MLX4_EVENT_TYPE_PORT_MNG_CHG_EVENT;
	eqe.subtype = MLX4_DEV_PMC_SUBTYPE_PORT_INFO;
	eqe.event.port_mgmt_change.port = port;
	eqe.event.port_mgmt_change.params.port_info.changed_attr =
		cpu_to_be32((u32) attr);

	slave_event(dev, ALL_SLAVES, &eqe);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlx4_gen_slaves_port_mgt_ev);

व्योम mlx4_master_handle_slave_flr(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx4_mfunc_master_ctx *master =
		container_of(work, काष्ठा mlx4_mfunc_master_ctx,
			     slave_flr_event_work);
	काष्ठा mlx4_mfunc *mfunc =
		container_of(master, काष्ठा mlx4_mfunc, master);
	काष्ठा mlx4_priv *priv =
		container_of(mfunc, काष्ठा mlx4_priv, mfunc);
	काष्ठा mlx4_dev *dev = &priv->dev;
	काष्ठा mlx4_slave_state *slave_state = priv->mfunc.master.slave_state;
	पूर्णांक i;
	पूर्णांक err;
	अचिन्हित दीर्घ flags;

	mlx4_dbg(dev, "mlx4_handle_slave_flr\n");

	क्रम (i = 0 ; i < dev->num_slaves; i++) अणु

		अगर (MLX4_COMM_CMD_FLR == slave_state[i].last_cmd) अणु
			mlx4_dbg(dev, "mlx4_handle_slave_flr: clean slave: %d\n",
				 i);
			/* In हाल of 'Reset flow' FLR can be generated क्रम
			 * a slave beक्रमe mlx4_load_one is करोne.
			 * make sure पूर्णांकerface is up beक्रमe trying to delete
			 * slave resources which weren't allocated yet.
			 */
			अगर (dev->persist->पूर्णांकerface_state &
			    MLX4_INTERFACE_STATE_UP)
				mlx4_delete_all_resources_क्रम_slave(dev, i);
			/*वापस the slave to running mode*/
			spin_lock_irqsave(&priv->mfunc.master.slave_state_lock, flags);
			slave_state[i].last_cmd = MLX4_COMM_CMD_RESET;
			slave_state[i].is_slave_going_करोwn = 0;
			spin_unlock_irqrestore(&priv->mfunc.master.slave_state_lock, flags);
			/*notअगरy the FW:*/
			err = mlx4_cmd(dev, 0, i, 0, MLX4_CMD_INFORM_FLR_DONE,
				       MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
			अगर (err)
				mlx4_warn(dev, "Failed to notify FW on FLR done (slave:%d)\n",
					  i);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mlx4_eq_पूर्णांक(काष्ठा mlx4_dev *dev, काष्ठा mlx4_eq *eq)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_eqe *eqe;
	पूर्णांक cqn;
	पूर्णांक eqes_found = 0;
	पूर्णांक set_ci = 0;
	पूर्णांक port;
	पूर्णांक slave = 0;
	पूर्णांक ret;
	u32 flr_slave;
	u8 update_slave_state;
	पूर्णांक i;
	क्रमागत slave_port_gen_event gen_event;
	अचिन्हित दीर्घ flags;
	काष्ठा mlx4_vport_state *s_info;
	पूर्णांक eqe_size = dev->caps.eqe_size;

	जबतक ((eqe = next_eqe_sw(eq, dev->caps.eqe_factor, eqe_size))) अणु
		/*
		 * Make sure we पढ़ो EQ entry contents after we've
		 * checked the ownership bit.
		 */
		dma_rmb();

		चयन (eqe->type) अणु
		हाल MLX4_EVENT_TYPE_COMP:
			cqn = be32_to_cpu(eqe->event.comp.cqn) & 0xffffff;
			mlx4_cq_completion(dev, cqn);
			अवरोध;

		हाल MLX4_EVENT_TYPE_PATH_MIG:
		हाल MLX4_EVENT_TYPE_COMM_EST:
		हाल MLX4_EVENT_TYPE_SQ_DRAINED:
		हाल MLX4_EVENT_TYPE_SRQ_QP_LAST_WQE:
		हाल MLX4_EVENT_TYPE_WQ_CATAS_ERROR:
		हाल MLX4_EVENT_TYPE_PATH_MIG_FAILED:
		हाल MLX4_EVENT_TYPE_WQ_INVAL_REQ_ERROR:
		हाल MLX4_EVENT_TYPE_WQ_ACCESS_ERROR:
			mlx4_dbg(dev, "event %d arrived\n", eqe->type);
			अगर (mlx4_is_master(dev)) अणु
				/* क्रमward only to slave owning the QP */
				ret = mlx4_get_slave_from_resource_id(dev,
						RES_QP,
						be32_to_cpu(eqe->event.qp.qpn)
						& 0xffffff, &slave);
				अगर (ret && ret != -ENOENT) अणु
					mlx4_dbg(dev, "QP event %02x(%02x) on EQ %d at index %u: could not get slave id (%d)\n",
						 eqe->type, eqe->subtype,
						 eq->eqn, eq->cons_index, ret);
					अवरोध;
				पूर्ण

				अगर (!ret && slave != dev->caps.function) अणु
					mlx4_slave_event(dev, slave, eqe);
					अवरोध;
				पूर्ण

			पूर्ण
			mlx4_qp_event(dev, be32_to_cpu(eqe->event.qp.qpn) &
				      0xffffff, eqe->type);
			अवरोध;

		हाल MLX4_EVENT_TYPE_SRQ_LIMIT:
			mlx4_dbg(dev, "%s: MLX4_EVENT_TYPE_SRQ_LIMIT. srq_no=0x%x, eq 0x%x\n",
				 __func__, be32_to_cpu(eqe->event.srq.srqn),
				 eq->eqn);
			fallthrough;
		हाल MLX4_EVENT_TYPE_SRQ_CATAS_ERROR:
			अगर (mlx4_is_master(dev)) अणु
				/* क्रमward only to slave owning the SRQ */
				ret = mlx4_get_slave_from_resource_id(dev,
						RES_SRQ,
						be32_to_cpu(eqe->event.srq.srqn)
						& 0xffffff,
						&slave);
				अगर (ret && ret != -ENOENT) अणु
					mlx4_warn(dev, "SRQ event %02x(%02x) on EQ %d at index %u: could not get slave id (%d)\n",
						  eqe->type, eqe->subtype,
						  eq->eqn, eq->cons_index, ret);
					अवरोध;
				पूर्ण
				अगर (eqe->type ==
				    MLX4_EVENT_TYPE_SRQ_CATAS_ERROR)
					mlx4_warn(dev, "%s: slave:%d, srq_no:0x%x, event: %02x(%02x)\n",
						  __func__, slave,
						  be32_to_cpu(eqe->event.srq.srqn),
						  eqe->type, eqe->subtype);

				अगर (!ret && slave != dev->caps.function) अणु
					अगर (eqe->type ==
					    MLX4_EVENT_TYPE_SRQ_CATAS_ERROR)
						mlx4_warn(dev, "%s: sending event %02x(%02x) to slave:%d\n",
							  __func__, eqe->type,
							  eqe->subtype, slave);
					mlx4_slave_event(dev, slave, eqe);
					अवरोध;
				पूर्ण
			पूर्ण
			mlx4_srq_event(dev, be32_to_cpu(eqe->event.srq.srqn) &
				       0xffffff, eqe->type);
			अवरोध;

		हाल MLX4_EVENT_TYPE_CMD:
			mlx4_cmd_event(dev,
				       be16_to_cpu(eqe->event.cmd.token),
				       eqe->event.cmd.status,
				       be64_to_cpu(eqe->event.cmd.out_param));
			अवरोध;

		हाल MLX4_EVENT_TYPE_PORT_CHANGE: अणु
			काष्ठा mlx4_slaves_pport slaves_port;
			port = be32_to_cpu(eqe->event.port_change.port) >> 28;
			slaves_port = mlx4_phys_to_slaves_pport(dev, port);
			अगर (eqe->subtype == MLX4_PORT_CHANGE_SUBTYPE_DOWN) अणु
				mlx4_dispatch_event(dev, MLX4_DEV_EVENT_PORT_DOWN,
						    port);
				mlx4_priv(dev)->sense.करो_sense_port[port] = 1;
				अगर (!mlx4_is_master(dev))
					अवरोध;
				क्रम (i = 0; i < dev->persist->num_vfs + 1;
				     i++) अणु
					पूर्णांक reported_port = mlx4_is_bonded(dev) ? 1 : mlx4_phys_to_slave_port(dev, i, port);

					अगर (!test_bit(i, slaves_port.slaves) && !mlx4_is_bonded(dev))
						जारी;
					अगर (dev->caps.port_type[port] == MLX4_PORT_TYPE_ETH) अणु
						अगर (i == mlx4_master_func_num(dev))
							जारी;
						mlx4_dbg(dev, "%s: Sending MLX4_PORT_CHANGE_SUBTYPE_DOWN to slave: %d, port:%d\n",
							 __func__, i, port);
						s_info = &priv->mfunc.master.vf_oper[i].vport[port].state;
						अगर (IFLA_VF_LINK_STATE_AUTO == s_info->link_state) अणु
							eqe->event.port_change.port =
								cpu_to_be32(
								(be32_to_cpu(eqe->event.port_change.port) & 0xFFFFFFF)
								| (reported_port << 28));
							mlx4_slave_event(dev, i, eqe);
						पूर्ण
					पूर्ण अन्यथा अणु  /* IB port */
						set_and_calc_slave_port_state(dev, i, port,
									      MLX4_PORT_STATE_DEV_EVENT_PORT_DOWN,
									      &gen_event);
						/*we can be in pending state, then करो not send port_करोwn event*/
						अगर (SLAVE_PORT_GEN_EVENT_DOWN ==  gen_event) अणु
							अगर (i == mlx4_master_func_num(dev))
								जारी;
							eqe->event.port_change.port =
								cpu_to_be32(
								(be32_to_cpu(eqe->event.port_change.port) & 0xFFFFFFF)
								| (mlx4_phys_to_slave_port(dev, i, port) << 28));
							mlx4_slave_event(dev, i, eqe);
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				mlx4_dispatch_event(dev, MLX4_DEV_EVENT_PORT_UP, port);

				mlx4_priv(dev)->sense.करो_sense_port[port] = 0;

				अगर (!mlx4_is_master(dev))
					अवरोध;
				अगर (dev->caps.port_type[port] == MLX4_PORT_TYPE_ETH)
					क्रम (i = 0;
					     i < dev->persist->num_vfs + 1;
					     i++) अणु
						पूर्णांक reported_port = mlx4_is_bonded(dev) ? 1 : mlx4_phys_to_slave_port(dev, i, port);

						अगर (!test_bit(i, slaves_port.slaves) && !mlx4_is_bonded(dev))
							जारी;
						अगर (i == mlx4_master_func_num(dev))
							जारी;
						s_info = &priv->mfunc.master.vf_oper[i].vport[port].state;
						अगर (IFLA_VF_LINK_STATE_AUTO == s_info->link_state) अणु
							eqe->event.port_change.port =
								cpu_to_be32(
								(be32_to_cpu(eqe->event.port_change.port) & 0xFFFFFFF)
								| (reported_port << 28));
							mlx4_slave_event(dev, i, eqe);
						पूर्ण
					पूर्ण
				अन्यथा /* IB port */
					/* port-up event will be sent to a slave when the
					 * slave's alias-guid is set. This is करोne in alias_GUID.c
					 */
					set_all_slave_state(dev, port, MLX4_DEV_EVENT_PORT_UP);
			पूर्ण
			अवरोध;
		पूर्ण

		हाल MLX4_EVENT_TYPE_CQ_ERROR:
			mlx4_warn(dev, "CQ %s on CQN %06x\n",
				  eqe->event.cq_err.syndrome == 1 ?
				  "overrun" : "access violation",
				  be32_to_cpu(eqe->event.cq_err.cqn) & 0xffffff);
			अगर (mlx4_is_master(dev)) अणु
				ret = mlx4_get_slave_from_resource_id(dev,
					RES_CQ,
					be32_to_cpu(eqe->event.cq_err.cqn)
					& 0xffffff, &slave);
				अगर (ret && ret != -ENOENT) अणु
					mlx4_dbg(dev, "CQ event %02x(%02x) on EQ %d at index %u: could not get slave id (%d)\n",
						 eqe->type, eqe->subtype,
						 eq->eqn, eq->cons_index, ret);
					अवरोध;
				पूर्ण

				अगर (!ret && slave != dev->caps.function) अणु
					mlx4_slave_event(dev, slave, eqe);
					अवरोध;
				पूर्ण
			पूर्ण
			mlx4_cq_event(dev,
				      be32_to_cpu(eqe->event.cq_err.cqn)
				      & 0xffffff,
				      eqe->type);
			अवरोध;

		हाल MLX4_EVENT_TYPE_EQ_OVERFLOW:
			mlx4_warn(dev, "EQ overrun on EQN %d\n", eq->eqn);
			अवरोध;

		हाल MLX4_EVENT_TYPE_OP_REQUIRED:
			atomic_inc(&priv->opreq_count);
			/* FW commands can't be executed from पूर्णांकerrupt context
			 * working in deferred task
			 */
			queue_work(mlx4_wq, &priv->opreq_task);
			अवरोध;

		हाल MLX4_EVENT_TYPE_COMM_CHANNEL:
			अगर (!mlx4_is_master(dev)) अणु
				mlx4_warn(dev, "Received comm channel event for non master device\n");
				अवरोध;
			पूर्ण
			स_नकल(&priv->mfunc.master.comm_arm_bit_vector,
			       eqe->event.comm_channel_arm.bit_vec,
			       माप(eqe->event.comm_channel_arm.bit_vec));
			queue_work(priv->mfunc.master.comm_wq,
				   &priv->mfunc.master.comm_work);
			अवरोध;

		हाल MLX4_EVENT_TYPE_FLR_EVENT:
			flr_slave = be32_to_cpu(eqe->event.flr_event.slave_id);
			अगर (!mlx4_is_master(dev)) अणु
				mlx4_warn(dev, "Non-master function received FLR event\n");
				अवरोध;
			पूर्ण

			mlx4_dbg(dev, "FLR event for slave: %d\n", flr_slave);

			अगर (flr_slave >= dev->num_slaves) अणु
				mlx4_warn(dev,
					  "Got FLR for unknown function: %d\n",
					  flr_slave);
				update_slave_state = 0;
			पूर्ण अन्यथा
				update_slave_state = 1;

			spin_lock_irqsave(&priv->mfunc.master.slave_state_lock, flags);
			अगर (update_slave_state) अणु
				priv->mfunc.master.slave_state[flr_slave].active = false;
				priv->mfunc.master.slave_state[flr_slave].last_cmd = MLX4_COMM_CMD_FLR;
				priv->mfunc.master.slave_state[flr_slave].is_slave_going_करोwn = 1;
			पूर्ण
			spin_unlock_irqrestore(&priv->mfunc.master.slave_state_lock, flags);
			mlx4_dispatch_event(dev, MLX4_DEV_EVENT_SLAVE_SHUTDOWN,
					    flr_slave);
			queue_work(priv->mfunc.master.comm_wq,
				   &priv->mfunc.master.slave_flr_event_work);
			अवरोध;

		हाल MLX4_EVENT_TYPE_FATAL_WARNING:
			अगर (eqe->subtype == MLX4_FATAL_WARNING_SUBTYPE_WARMING) अणु
				अगर (mlx4_is_master(dev))
					क्रम (i = 0; i < dev->num_slaves; i++) अणु
						mlx4_dbg(dev, "%s: Sending MLX4_FATAL_WARNING_SUBTYPE_WARMING to slave: %d\n",
							 __func__, i);
						अगर (i == dev->caps.function)
							जारी;
						mlx4_slave_event(dev, i, eqe);
					पूर्ण
				mlx4_err(dev, "Temperature Threshold was reached! Threshold: %d celsius degrees; Current Temperature: %d\n",
					 be16_to_cpu(eqe->event.warming.warning_threshold),
					 be16_to_cpu(eqe->event.warming.current_temperature));
			पूर्ण अन्यथा
				mlx4_warn(dev, "Unhandled event FATAL WARNING (%02x), subtype %02x on EQ %d at index %u. owner=%x, nent=0x%x, slave=%x, ownership=%s\n",
					  eqe->type, eqe->subtype, eq->eqn,
					  eq->cons_index, eqe->owner, eq->nent,
					  eqe->slave_id,
					  !!(eqe->owner & 0x80) ^
					  !!(eq->cons_index & eq->nent) ? "HW" : "SW");

			अवरोध;

		हाल MLX4_EVENT_TYPE_PORT_MNG_CHG_EVENT:
			mlx4_dispatch_event(dev, MLX4_DEV_EVENT_PORT_MGMT_CHANGE,
					    (अचिन्हित दीर्घ) eqe);
			अवरोध;

		हाल MLX4_EVENT_TYPE_RECOVERABLE_ERROR_EVENT:
			चयन (eqe->subtype) अणु
			हाल MLX4_RECOVERABLE_ERROR_EVENT_SUBTYPE_BAD_CABLE:
				mlx4_warn(dev, "Bad cable detected on port %u\n",
					  eqe->event.bad_cable.port);
				अवरोध;
			हाल MLX4_RECOVERABLE_ERROR_EVENT_SUBTYPE_UNSUPPORTED_CABLE:
				mlx4_warn(dev, "Unsupported cable detected\n");
				अवरोध;
			शेष:
				mlx4_dbg(dev,
					 "Unhandled recoverable error event detected: %02x(%02x) on EQ %d at index %u. owner=%x, nent=0x%x, ownership=%s\n",
					 eqe->type, eqe->subtype, eq->eqn,
					 eq->cons_index, eqe->owner, eq->nent,
					 !!(eqe->owner & 0x80) ^
					 !!(eq->cons_index & eq->nent) ? "HW" : "SW");
				अवरोध;
			पूर्ण
			अवरोध;

		हाल MLX4_EVENT_TYPE_EEC_CATAS_ERROR:
		हाल MLX4_EVENT_TYPE_ECC_DETECT:
		शेष:
			mlx4_warn(dev, "Unhandled event %02x(%02x) on EQ %d at index %u. owner=%x, nent=0x%x, slave=%x, ownership=%s\n",
				  eqe->type, eqe->subtype, eq->eqn,
				  eq->cons_index, eqe->owner, eq->nent,
				  eqe->slave_id,
				  !!(eqe->owner & 0x80) ^
				  !!(eq->cons_index & eq->nent) ? "HW" : "SW");
			अवरोध;
		पूर्ण

		++eq->cons_index;
		eqes_found = 1;
		++set_ci;

		/*
		 * The HCA will think the queue has overflowed अगर we
		 * करोn't tell it we've been processing events.  We
		 * create our EQs with MLX4_NUM_SPARE_EQE extra
		 * entries, so we must update our consumer index at
		 * least that often.
		 */
		अगर (unlikely(set_ci >= MLX4_NUM_SPARE_EQE)) अणु
			eq_set_ci(eq, 0);
			set_ci = 0;
		पूर्ण
	पूर्ण

	eq_set_ci(eq, 1);

	वापस eqes_found;
पूर्ण

अटल irqवापस_t mlx4_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_ptr)
अणु
	काष्ठा mlx4_dev *dev = dev_ptr;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक work = 0;
	पूर्णांक i;

	ग_लिखोl(priv->eq_table.clr_mask, priv->eq_table.clr_पूर्णांक);

	क्रम (i = 0; i < dev->caps.num_comp_vectors + 1; ++i)
		work |= mlx4_eq_पूर्णांक(dev, &priv->eq_table.eq[i]);

	वापस IRQ_RETVAL(work);
पूर्ण

अटल irqवापस_t mlx4_msi_x_पूर्णांकerrupt(पूर्णांक irq, व्योम *eq_ptr)
अणु
	काष्ठा mlx4_eq  *eq  = eq_ptr;
	काष्ठा mlx4_dev *dev = eq->dev;

	mlx4_eq_पूर्णांक(dev, eq);

	/* MSI-X vectors always beदीर्घ to us */
	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक mlx4_MAP_EQ_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			काष्ठा mlx4_vhcr *vhcr,
			काष्ठा mlx4_cmd_mailbox *inbox,
			काष्ठा mlx4_cmd_mailbox *outbox,
			काष्ठा mlx4_cmd_info *cmd)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_slave_event_eq_info *event_eq =
		priv->mfunc.master.slave_state[slave].event_eq;
	u32 in_modअगरier = vhcr->in_modअगरier;
	u32 eqn = in_modअगरier & 0x3FF;
	u64 in_param =  vhcr->in_param;
	पूर्णांक err = 0;
	पूर्णांक i;

	अगर (slave == dev->caps.function)
		err = mlx4_cmd(dev, in_param, (in_modअगरier & 0x80000000) | eqn,
			       0, MLX4_CMD_MAP_EQ, MLX4_CMD_TIME_CLASS_B,
			       MLX4_CMD_NATIVE);
	अगर (!err)
		क्रम (i = 0; i < MLX4_EVENT_TYPES_NUM; ++i)
			अगर (in_param & (1LL << i))
				event_eq[i].eqn = in_modअगरier >> 31 ? -1 : eqn;

	वापस err;
पूर्ण

अटल पूर्णांक mlx4_MAP_EQ(काष्ठा mlx4_dev *dev, u64 event_mask, पूर्णांक unmap,
			पूर्णांक eq_num)
अणु
	वापस mlx4_cmd(dev, event_mask, (unmap << 31) | eq_num,
			0, MLX4_CMD_MAP_EQ, MLX4_CMD_TIME_CLASS_B,
			MLX4_CMD_WRAPPED);
पूर्ण

अटल पूर्णांक mlx4_SW2HW_EQ(काष्ठा mlx4_dev *dev, काष्ठा mlx4_cmd_mailbox *mailbox,
			 पूर्णांक eq_num)
अणु
	वापस mlx4_cmd(dev, mailbox->dma, eq_num, 0,
			MLX4_CMD_SW2HW_EQ, MLX4_CMD_TIME_CLASS_A,
			MLX4_CMD_WRAPPED);
पूर्ण

अटल पूर्णांक mlx4_HW2SW_EQ(काष्ठा mlx4_dev *dev,  पूर्णांक eq_num)
अणु
	वापस mlx4_cmd(dev, 0, eq_num, 1, MLX4_CMD_HW2SW_EQ,
			MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
पूर्ण

अटल पूर्णांक mlx4_num_eq_uar(काष्ठा mlx4_dev *dev)
अणु
	/*
	 * Each UAR holds 4 EQ करोorbells.  To figure out how many UARs
	 * we need to map, take the dअगरference of highest index and
	 * the lowest index we'll use and add 1.
	 */
	वापस (dev->caps.num_comp_vectors + 1 + dev->caps.reserved_eqs) / 4 -
		dev->caps.reserved_eqs / 4 + 1;
पूर्ण

अटल व्योम __iomem *mlx4_get_eq_uar(काष्ठा mlx4_dev *dev, काष्ठा mlx4_eq *eq)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक index;

	index = eq->eqn / 4 - dev->caps.reserved_eqs / 4;

	अगर (!priv->eq_table.uar_map[index]) अणु
		priv->eq_table.uar_map[index] =
			ioremap(
				pci_resource_start(dev->persist->pdev, 2) +
				((eq->eqn / 4) << (dev->uar_page_shअगरt)),
				(1 << (dev->uar_page_shअगरt)));
		अगर (!priv->eq_table.uar_map[index]) अणु
			mlx4_err(dev, "Couldn't map EQ doorbell for EQN 0x%06x\n",
				 eq->eqn);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस priv->eq_table.uar_map[index] + 0x800 + 8 * (eq->eqn % 4);
पूर्ण

अटल व्योम mlx4_unmap_uar(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक i;

	क्रम (i = 0; i < mlx4_num_eq_uar(dev); ++i)
		अगर (priv->eq_table.uar_map[i]) अणु
			iounmap(priv->eq_table.uar_map[i]);
			priv->eq_table.uar_map[i] = शून्य;
		पूर्ण
पूर्ण

अटल पूर्णांक mlx4_create_eq(काष्ठा mlx4_dev *dev, पूर्णांक nent,
			  u8 पूर्णांकr, काष्ठा mlx4_eq *eq)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_eq_context *eq_context;
	पूर्णांक npages;
	u64 *dma_list = शून्य;
	dma_addr_t t;
	u64 mtt_addr;
	पूर्णांक err = -ENOMEM;
	पूर्णांक i;

	eq->dev   = dev;
	eq->nent  = roundup_घात_of_two(max(nent, 2));
	/* CX3 is capable of extending the CQE/EQE from 32 to 64 bytes, with
	 * strides of 64B,128B and 256B.
	 */
	npages = PAGE_ALIGN(eq->nent * dev->caps.eqe_size) / PAGE_SIZE;

	eq->page_list = kदो_स्मृति_array(npages, माप(*eq->page_list),
				      GFP_KERNEL);
	अगर (!eq->page_list)
		जाओ err_out;

	क्रम (i = 0; i < npages; ++i)
		eq->page_list[i].buf = शून्य;

	dma_list = kदो_स्मृति_array(npages, माप(*dma_list), GFP_KERNEL);
	अगर (!dma_list)
		जाओ err_out_मुक्त;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		जाओ err_out_मुक्त;
	eq_context = mailbox->buf;

	क्रम (i = 0; i < npages; ++i) अणु
		eq->page_list[i].buf = dma_alloc_coherent(&dev->persist->
							  pdev->dev,
							  PAGE_SIZE, &t,
							  GFP_KERNEL);
		अगर (!eq->page_list[i].buf)
			जाओ err_out_मुक्त_pages;

		dma_list[i] = t;
		eq->page_list[i].map = t;
	पूर्ण

	eq->eqn = mlx4_biपंचांगap_alloc(&priv->eq_table.biपंचांगap);
	अगर (eq->eqn == -1)
		जाओ err_out_मुक्त_pages;

	eq->करोorbell = mlx4_get_eq_uar(dev, eq);
	अगर (!eq->करोorbell) अणु
		err = -ENOMEM;
		जाओ err_out_मुक्त_eq;
	पूर्ण

	err = mlx4_mtt_init(dev, npages, PAGE_SHIFT, &eq->mtt);
	अगर (err)
		जाओ err_out_मुक्त_eq;

	err = mlx4_ग_लिखो_mtt(dev, &eq->mtt, 0, npages, dma_list);
	अगर (err)
		जाओ err_out_मुक्त_mtt;

	eq_context->flags	  = cpu_to_be32(MLX4_EQ_STATUS_OK   |
						MLX4_EQ_STATE_ARMED);
	eq_context->log_eq_size	  = ilog2(eq->nent);
	eq_context->पूर्णांकr	  = पूर्णांकr;
	eq_context->log_page_size = PAGE_SHIFT - MLX4_ICM_PAGE_SHIFT;

	mtt_addr = mlx4_mtt_addr(dev, &eq->mtt);
	eq_context->mtt_base_addr_h = mtt_addr >> 32;
	eq_context->mtt_base_addr_l = cpu_to_be32(mtt_addr & 0xffffffff);

	err = mlx4_SW2HW_EQ(dev, mailbox, eq->eqn);
	अगर (err) अणु
		mlx4_warn(dev, "SW2HW_EQ failed (%d)\n", err);
		जाओ err_out_मुक्त_mtt;
	पूर्ण

	kमुक्त(dma_list);
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);

	eq->cons_index = 0;

	INIT_LIST_HEAD(&eq->tasklet_ctx.list);
	INIT_LIST_HEAD(&eq->tasklet_ctx.process_list);
	spin_lock_init(&eq->tasklet_ctx.lock);
	tasklet_setup(&eq->tasklet_ctx.task, mlx4_cq_tasklet_cb);

	वापस err;

err_out_मुक्त_mtt:
	mlx4_mtt_cleanup(dev, &eq->mtt);

err_out_मुक्त_eq:
	mlx4_biपंचांगap_मुक्त(&priv->eq_table.biपंचांगap, eq->eqn, MLX4_USE_RR);

err_out_मुक्त_pages:
	क्रम (i = 0; i < npages; ++i)
		अगर (eq->page_list[i].buf)
			dma_मुक्त_coherent(&dev->persist->pdev->dev, PAGE_SIZE,
					  eq->page_list[i].buf,
					  eq->page_list[i].map);

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);

err_out_मुक्त:
	kमुक्त(eq->page_list);
	kमुक्त(dma_list);

err_out:
	वापस err;
पूर्ण

अटल व्योम mlx4_मुक्त_eq(काष्ठा mlx4_dev *dev,
			 काष्ठा mlx4_eq *eq)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक err;
	पूर्णांक i;
	/* CX3 is capable of extending the CQE/EQE from 32 to 64 bytes, with
	 * strides of 64B,128B and 256B
	 */
	पूर्णांक npages = PAGE_ALIGN(dev->caps.eqe_size  * eq->nent) / PAGE_SIZE;

	err = mlx4_HW2SW_EQ(dev, eq->eqn);
	अगर (err)
		mlx4_warn(dev, "HW2SW_EQ failed (%d)\n", err);

	synchronize_irq(eq->irq);
	tasklet_disable(&eq->tasklet_ctx.task);

	mlx4_mtt_cleanup(dev, &eq->mtt);
	क्रम (i = 0; i < npages; ++i)
		dma_मुक्त_coherent(&dev->persist->pdev->dev, PAGE_SIZE,
				  eq->page_list[i].buf,
				  eq->page_list[i].map);

	kमुक्त(eq->page_list);
	mlx4_biपंचांगap_मुक्त(&priv->eq_table.biपंचांगap, eq->eqn, MLX4_USE_RR);
पूर्ण

अटल व्योम mlx4_मुक्त_irqs(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_eq_table *eq_table = &mlx4_priv(dev)->eq_table;
	पूर्णांक	i;

	अगर (eq_table->have_irq)
		मुक्त_irq(dev->persist->pdev->irq, dev);

	क्रम (i = 0; i < dev->caps.num_comp_vectors + 1; ++i)
		अगर (eq_table->eq[i].have_irq) अणु
			मुक्त_cpumask_var(eq_table->eq[i].affinity_mask);
#अगर defined(CONFIG_SMP)
			irq_set_affinity_hपूर्णांक(eq_table->eq[i].irq, शून्य);
#पूर्ण_अगर
			मुक्त_irq(eq_table->eq[i].irq, eq_table->eq + i);
			eq_table->eq[i].have_irq = 0;
		पूर्ण

	kमुक्त(eq_table->irq_names);
पूर्ण

अटल पूर्णांक mlx4_map_clr_पूर्णांक(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	priv->clr_base = ioremap(pci_resource_start(dev->persist->pdev,
				 priv->fw.clr_पूर्णांक_bar) +
				 priv->fw.clr_पूर्णांक_base, MLX4_CLR_INT_SIZE);
	अगर (!priv->clr_base) अणु
		mlx4_err(dev, "Couldn't map interrupt clear register, aborting\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mlx4_unmap_clr_पूर्णांक(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	iounmap(priv->clr_base);
पूर्ण

पूर्णांक mlx4_alloc_eq_table(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	priv->eq_table.eq = kसुस्मृति(dev->caps.num_eqs - dev->caps.reserved_eqs,
				    माप(*priv->eq_table.eq), GFP_KERNEL);
	अगर (!priv->eq_table.eq)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम mlx4_मुक्त_eq_table(काष्ठा mlx4_dev *dev)
अणु
	kमुक्त(mlx4_priv(dev)->eq_table.eq);
पूर्ण

पूर्णांक mlx4_init_eq_table(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक err;
	पूर्णांक i;

	priv->eq_table.uar_map = kसुस्मृति(mlx4_num_eq_uar(dev),
					 माप(*priv->eq_table.uar_map),
					 GFP_KERNEL);
	अगर (!priv->eq_table.uar_map) अणु
		err = -ENOMEM;
		जाओ err_out_मुक्त;
	पूर्ण

	err = mlx4_biपंचांगap_init(&priv->eq_table.biपंचांगap,
			       roundup_घात_of_two(dev->caps.num_eqs),
			       dev->caps.num_eqs - 1,
			       dev->caps.reserved_eqs,
			       roundup_घात_of_two(dev->caps.num_eqs) -
			       dev->caps.num_eqs);
	अगर (err)
		जाओ err_out_मुक्त;

	क्रम (i = 0; i < mlx4_num_eq_uar(dev); ++i)
		priv->eq_table.uar_map[i] = शून्य;

	अगर (!mlx4_is_slave(dev)) अणु
		err = mlx4_map_clr_पूर्णांक(dev);
		अगर (err)
			जाओ err_out_biपंचांगap;

		priv->eq_table.clr_mask =
			swab32(1 << (priv->eq_table.पूर्णांकa_pin & 31));
		priv->eq_table.clr_पूर्णांक  = priv->clr_base +
			(priv->eq_table.पूर्णांकa_pin < 32 ? 4 : 0);
	पूर्ण

	priv->eq_table.irq_names =
		kदो_स्मृति_array(MLX4_IRQNAME_SIZE,
			      (dev->caps.num_comp_vectors + 1),
			      GFP_KERNEL);
	अगर (!priv->eq_table.irq_names) अणु
		err = -ENOMEM;
		जाओ err_out_clr_पूर्णांक;
	पूर्ण

	क्रम (i = 0; i < dev->caps.num_comp_vectors + 1; ++i) अणु
		अगर (i == MLX4_EQ_ASYNC) अणु
			err = mlx4_create_eq(dev,
					     MLX4_NUM_ASYNC_EQE + MLX4_NUM_SPARE_EQE,
					     0, &priv->eq_table.eq[MLX4_EQ_ASYNC]);
		पूर्ण अन्यथा अणु
			काष्ठा mlx4_eq	*eq = &priv->eq_table.eq[i];
#अगर_घोषित CONFIG_RFS_ACCEL
			पूर्णांक port = find_first_bit(eq->actv_ports.ports,
						  dev->caps.num_ports) + 1;

			अगर (port <= dev->caps.num_ports) अणु
				काष्ठा mlx4_port_info *info =
					&mlx4_priv(dev)->port[port];

				अगर (!info->rmap) अणु
					info->rmap = alloc_irq_cpu_rmap(
						mlx4_get_eqs_per_port(dev, port));
					अगर (!info->rmap) अणु
						mlx4_warn(dev, "Failed to allocate cpu rmap\n");
						err = -ENOMEM;
						जाओ err_out_unmap;
					पूर्ण
				पूर्ण

				err = irq_cpu_rmap_add(
					info->rmap, eq->irq);
				अगर (err)
					mlx4_warn(dev, "Failed adding irq rmap\n");
			पूर्ण
#पूर्ण_अगर
			err = mlx4_create_eq(dev, dev->quotas.cq +
					     MLX4_NUM_SPARE_EQE,
					     (dev->flags & MLX4_FLAG_MSI_X) ?
					     i + 1 - !!(i > MLX4_EQ_ASYNC) : 0,
					     eq);
		पूर्ण
		अगर (err)
			जाओ err_out_unmap;
	पूर्ण

	अगर (dev->flags & MLX4_FLAG_MSI_X) अणु
		स्थिर अक्षर *eq_name;

		snम_लिखो(priv->eq_table.irq_names +
			 MLX4_EQ_ASYNC * MLX4_IRQNAME_SIZE,
			 MLX4_IRQNAME_SIZE,
			 "mlx4-async@pci:%s",
			 pci_name(dev->persist->pdev));
		eq_name = priv->eq_table.irq_names +
			MLX4_EQ_ASYNC * MLX4_IRQNAME_SIZE;

		err = request_irq(priv->eq_table.eq[MLX4_EQ_ASYNC].irq,
				  mlx4_msi_x_पूर्णांकerrupt, 0, eq_name,
				  priv->eq_table.eq + MLX4_EQ_ASYNC);
		अगर (err)
			जाओ err_out_unmap;

		priv->eq_table.eq[MLX4_EQ_ASYNC].have_irq = 1;
	पूर्ण अन्यथा अणु
		snम_लिखो(priv->eq_table.irq_names,
			 MLX4_IRQNAME_SIZE,
			 DRV_NAME "@pci:%s",
			 pci_name(dev->persist->pdev));
		err = request_irq(dev->persist->pdev->irq, mlx4_पूर्णांकerrupt,
				  IRQF_SHARED, priv->eq_table.irq_names, dev);
		अगर (err)
			जाओ err_out_unmap;

		priv->eq_table.have_irq = 1;
	पूर्ण

	err = mlx4_MAP_EQ(dev, get_async_ev_mask(dev), 0,
			  priv->eq_table.eq[MLX4_EQ_ASYNC].eqn);
	अगर (err)
		mlx4_warn(dev, "MAP_EQ for async EQ %d failed (%d)\n",
			   priv->eq_table.eq[MLX4_EQ_ASYNC].eqn, err);

	/* arm ASYNC eq */
	eq_set_ci(&priv->eq_table.eq[MLX4_EQ_ASYNC], 1);

	वापस 0;

err_out_unmap:
	जबतक (i > 0)
		mlx4_मुक्त_eq(dev, &priv->eq_table.eq[--i]);
#अगर_घोषित CONFIG_RFS_ACCEL
	क्रम (i = 1; i <= dev->caps.num_ports; i++) अणु
		अगर (mlx4_priv(dev)->port[i].rmap) अणु
			मुक्त_irq_cpu_rmap(mlx4_priv(dev)->port[i].rmap);
			mlx4_priv(dev)->port[i].rmap = शून्य;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	mlx4_मुक्त_irqs(dev);

err_out_clr_पूर्णांक:
	अगर (!mlx4_is_slave(dev))
		mlx4_unmap_clr_पूर्णांक(dev);

err_out_biपंचांगap:
	mlx4_unmap_uar(dev);
	mlx4_biपंचांगap_cleanup(&priv->eq_table.biपंचांगap);

err_out_मुक्त:
	kमुक्त(priv->eq_table.uar_map);

	वापस err;
पूर्ण

व्योम mlx4_cleanup_eq_table(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक i;

	mlx4_MAP_EQ(dev, get_async_ev_mask(dev), 1,
		    priv->eq_table.eq[MLX4_EQ_ASYNC].eqn);

#अगर_घोषित CONFIG_RFS_ACCEL
	क्रम (i = 1; i <= dev->caps.num_ports; i++) अणु
		अगर (mlx4_priv(dev)->port[i].rmap) अणु
			मुक्त_irq_cpu_rmap(mlx4_priv(dev)->port[i].rmap);
			mlx4_priv(dev)->port[i].rmap = शून्य;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	mlx4_मुक्त_irqs(dev);

	क्रम (i = 0; i < dev->caps.num_comp_vectors + 1; ++i)
		mlx4_मुक्त_eq(dev, &priv->eq_table.eq[i]);

	अगर (!mlx4_is_slave(dev))
		mlx4_unmap_clr_पूर्णांक(dev);

	mlx4_unmap_uar(dev);
	mlx4_biपंचांगap_cleanup(&priv->eq_table.biपंचांगap);

	kमुक्त(priv->eq_table.uar_map);
पूर्ण

/* A test that verअगरies that we can accept पूर्णांकerrupts
 * on the vector allocated क्रम asynchronous events
 */
पूर्णांक mlx4_test_async(काष्ठा mlx4_dev *dev)
अणु
	वापस mlx4_NOP(dev);
पूर्ण
EXPORT_SYMBOL(mlx4_test_async);

/* A test that verअगरies that we can accept पूर्णांकerrupts
 * on the given irq vector of the tested port.
 * Interrupts are checked using the NOP command.
 */
पूर्णांक mlx4_test_पूर्णांकerrupt(काष्ठा mlx4_dev *dev, पूर्णांक vector)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक err;

	/* Temporary use polling क्रम command completions */
	mlx4_cmd_use_polling(dev);

	/* Map the new eq to handle all asynchronous events */
	err = mlx4_MAP_EQ(dev, get_async_ev_mask(dev), 0,
			  priv->eq_table.eq[MLX4_CQ_TO_EQ_VECTOR(vector)].eqn);
	अगर (err) अणु
		mlx4_warn(dev, "Failed mapping eq for interrupt test\n");
		जाओ out;
	पूर्ण

	/* Go back to using events */
	mlx4_cmd_use_events(dev);
	err = mlx4_NOP(dev);

	/* Return to शेष */
	mlx4_cmd_use_polling(dev);
out:
	mlx4_MAP_EQ(dev, get_async_ev_mask(dev), 0,
		    priv->eq_table.eq[MLX4_EQ_ASYNC].eqn);
	mlx4_cmd_use_events(dev);

	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx4_test_पूर्णांकerrupt);

bool mlx4_is_eq_vector_valid(काष्ठा mlx4_dev *dev, u8 port, पूर्णांक vector)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	vector = MLX4_CQ_TO_EQ_VECTOR(vector);
	अगर (vector < 0 || (vector >= dev->caps.num_comp_vectors + 1) ||
	    (vector == MLX4_EQ_ASYNC))
		वापस false;

	वापस test_bit(port - 1, priv->eq_table.eq[vector].actv_ports.ports);
पूर्ण
EXPORT_SYMBOL(mlx4_is_eq_vector_valid);

u32 mlx4_get_eqs_per_port(काष्ठा mlx4_dev *dev, u8 port)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक sum = 0;

	क्रम (i = 0; i < dev->caps.num_comp_vectors + 1; i++)
		sum += !!test_bit(port - 1,
				  priv->eq_table.eq[i].actv_ports.ports);

	वापस sum;
पूर्ण
EXPORT_SYMBOL(mlx4_get_eqs_per_port);

पूर्णांक mlx4_is_eq_shared(काष्ठा mlx4_dev *dev, पूर्णांक vector)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	vector = MLX4_CQ_TO_EQ_VECTOR(vector);
	अगर (vector <= 0 || (vector >= dev->caps.num_comp_vectors + 1))
		वापस -EINVAL;

	वापस !!(biपंचांगap_weight(priv->eq_table.eq[vector].actv_ports.ports,
				dev->caps.num_ports) > 1);
पूर्ण
EXPORT_SYMBOL(mlx4_is_eq_shared);

काष्ठा cpu_rmap *mlx4_get_cpu_rmap(काष्ठा mlx4_dev *dev, पूर्णांक port)
अणु
	वापस mlx4_priv(dev)->port[port].rmap;
पूर्ण
EXPORT_SYMBOL(mlx4_get_cpu_rmap);

पूर्णांक mlx4_assign_eq(काष्ठा mlx4_dev *dev, u8 port, पूर्णांक *vector)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक err = 0, i = 0;
	u32 min_ref_count_val = (u32)-1;
	पूर्णांक requested_vector = MLX4_CQ_TO_EQ_VECTOR(*vector);
	पूर्णांक *prequested_vector = शून्य;


	mutex_lock(&priv->msix_ctl.pool_lock);
	अगर (requested_vector < (dev->caps.num_comp_vectors + 1) &&
	    (requested_vector >= 0) &&
	    (requested_vector != MLX4_EQ_ASYNC)) अणु
		अगर (test_bit(port - 1,
			     priv->eq_table.eq[requested_vector].actv_ports.ports)) अणु
			prequested_vector = &requested_vector;
		पूर्ण अन्यथा अणु
			काष्ठा mlx4_eq *eq;

			क्रम (i = 1; i < port;
			     requested_vector += mlx4_get_eqs_per_port(dev, i++))
				;

			eq = &priv->eq_table.eq[requested_vector];
			अगर (requested_vector < dev->caps.num_comp_vectors + 1 &&
			    test_bit(port - 1, eq->actv_ports.ports)) अणु
				prequested_vector = &requested_vector;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर  (!prequested_vector) अणु
		requested_vector = -1;
		क्रम (i = 0; min_ref_count_val && i < dev->caps.num_comp_vectors + 1;
		     i++) अणु
			काष्ठा mlx4_eq *eq = &priv->eq_table.eq[i];

			अगर (min_ref_count_val > eq->ref_count &&
			    test_bit(port - 1, eq->actv_ports.ports)) अणु
				min_ref_count_val = eq->ref_count;
				requested_vector = i;
			पूर्ण
		पूर्ण

		अगर (requested_vector < 0) अणु
			err = -ENOSPC;
			जाओ err_unlock;
		पूर्ण

		prequested_vector = &requested_vector;
	पूर्ण

	अगर (!test_bit(*prequested_vector, priv->msix_ctl.pool_bm) &&
	    dev->flags & MLX4_FLAG_MSI_X) अणु
		set_bit(*prequested_vector, priv->msix_ctl.pool_bm);
		snम_लिखो(priv->eq_table.irq_names +
			 *prequested_vector * MLX4_IRQNAME_SIZE,
			 MLX4_IRQNAME_SIZE, "mlx4-%d@%s",
			 *prequested_vector, dev_name(&dev->persist->pdev->dev));

		err = request_irq(priv->eq_table.eq[*prequested_vector].irq,
				  mlx4_msi_x_पूर्णांकerrupt, 0,
				  &priv->eq_table.irq_names[*prequested_vector << 5],
				  priv->eq_table.eq + *prequested_vector);

		अगर (err) अणु
			clear_bit(*prequested_vector, priv->msix_ctl.pool_bm);
			*prequested_vector = -1;
		पूर्ण अन्यथा अणु
#अगर defined(CONFIG_SMP)
			mlx4_set_eq_affinity_hपूर्णांक(priv, *prequested_vector);
#पूर्ण_अगर
			eq_set_ci(&priv->eq_table.eq[*prequested_vector], 1);
			priv->eq_table.eq[*prequested_vector].have_irq = 1;
		पूर्ण
	पूर्ण

	अगर (!err && *prequested_vector >= 0)
		priv->eq_table.eq[*prequested_vector].ref_count++;

err_unlock:
	mutex_unlock(&priv->msix_ctl.pool_lock);

	अगर (!err && *prequested_vector >= 0)
		*vector = MLX4_EQ_TO_CQ_VECTOR(*prequested_vector);
	अन्यथा
		*vector = 0;

	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx4_assign_eq);

पूर्णांक mlx4_eq_get_irq(काष्ठा mlx4_dev *dev, पूर्णांक cq_vec)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	वापस priv->eq_table.eq[MLX4_CQ_TO_EQ_VECTOR(cq_vec)].irq;
पूर्ण
EXPORT_SYMBOL(mlx4_eq_get_irq);

व्योम mlx4_release_eq(काष्ठा mlx4_dev *dev, पूर्णांक vec)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक eq_vec = MLX4_CQ_TO_EQ_VECTOR(vec);

	mutex_lock(&priv->msix_ctl.pool_lock);
	priv->eq_table.eq[eq_vec].ref_count--;

	/* once we allocated EQ, we करोn't release it because it might be binded
	 * to cpu_rmap.
	 */
	mutex_unlock(&priv->msix_ctl.pool_lock);
पूर्ण
EXPORT_SYMBOL(mlx4_release_eq);

