<शैली गुरु>
/*
 * Copyright (c) 2007 Mellanox Technologies. All rights reserved.
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
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/अगर_ether.h>

#समावेश <linux/mlx4/cmd.h>

#समावेश "mlx4.h"

पूर्णांक mlx4_SENSE_PORT(काष्ठा mlx4_dev *dev, पूर्णांक port,
		    क्रमागत mlx4_port_type *type)
अणु
	u64 out_param;
	पूर्णांक err = 0;

	err = mlx4_cmd_imm(dev, 0, &out_param, port, 0,
			   MLX4_CMD_SENSE_PORT, MLX4_CMD_TIME_CLASS_B,
			   MLX4_CMD_WRAPPED);
	अगर (err) अणु
		mlx4_err(dev, "Sense command failed for port: %d\n", port);
		वापस err;
	पूर्ण

	अगर (out_param > 2) अणु
		mlx4_err(dev, "Sense returned illegal value: 0x%llx\n", out_param);
		वापस -EINVAL;
	पूर्ण

	*type = out_param;
	वापस 0;
पूर्ण

व्योम mlx4_करो_sense_ports(काष्ठा mlx4_dev *dev,
			 क्रमागत mlx4_port_type *stype,
			 क्रमागत mlx4_port_type *शेषs)
अणु
	काष्ठा mlx4_sense *sense = &mlx4_priv(dev)->sense;
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 1; i <= dev->caps.num_ports; i++) अणु
		stype[i - 1] = 0;
		अगर (sense->करो_sense_port[i] && sense->sense_allowed[i] &&
		    dev->caps.possible_type[i] == MLX4_PORT_TYPE_AUTO) अणु
			err = mlx4_SENSE_PORT(dev, i, &stype[i - 1]);
			अगर (err)
				stype[i - 1] = शेषs[i - 1];
		पूर्ण अन्यथा
			stype[i - 1] = शेषs[i - 1];
	पूर्ण

	/*
	 * If sensed nothing, reमुख्य in current configuration.
	 */
	क्रम (i = 0; i < dev->caps.num_ports; i++)
		stype[i] = stype[i] ? stype[i] : शेषs[i];

पूर्ण

अटल व्योम mlx4_sense_port(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delay = to_delayed_work(work);
	काष्ठा mlx4_sense *sense = container_of(delay, काष्ठा mlx4_sense,
						sense_poll);
	काष्ठा mlx4_dev *dev = sense->dev;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	क्रमागत mlx4_port_type stype[MLX4_MAX_PORTS];

	mutex_lock(&priv->port_mutex);
	mlx4_करो_sense_ports(dev, stype, &dev->caps.port_type[1]);

	अगर (mlx4_check_port_params(dev, stype))
		जाओ sense_again;

	अगर (mlx4_change_port_types(dev, stype))
		mlx4_err(dev, "Failed to change port_types\n");

sense_again:
	mutex_unlock(&priv->port_mutex);
	queue_delayed_work(mlx4_wq , &sense->sense_poll,
			   round_jअगरfies_relative(MLX4_SENSE_RANGE));
पूर्ण

व्योम mlx4_start_sense(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_sense *sense = &priv->sense;

	अगर (!(dev->caps.flags & MLX4_DEV_CAP_FLAG_DPDP))
		वापस;

	queue_delayed_work(mlx4_wq , &sense->sense_poll,
			   round_jअगरfies_relative(MLX4_SENSE_RANGE));
पूर्ण

व्योम mlx4_stop_sense(काष्ठा mlx4_dev *dev)
अणु
	cancel_delayed_work_sync(&mlx4_priv(dev)->sense.sense_poll);
पूर्ण

व्योम  mlx4_sense_init(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_sense *sense = &priv->sense;
	पूर्णांक port;

	sense->dev = dev;
	क्रम (port = 1; port <= dev->caps.num_ports; port++)
		sense->करो_sense_port[port] = 1;

	INIT_DEFERRABLE_WORK(&sense->sense_poll, mlx4_sense_port);
पूर्ण
