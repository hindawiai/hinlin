<शैली गुरु>
/*
 * Copyright (c) 2006, 2007 Cisco Systems, Inc. All rights reserved.
 * Copyright (c) 2007, 2008 Mellanox Technologies. All rights reserved.
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
 */

#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <net/devlink.h>

#समावेश "mlx4.h"

काष्ठा mlx4_device_context अणु
	काष्ठा list_head	list;
	काष्ठा list_head	bond_list;
	काष्ठा mlx4_पूर्णांकerface  *पूर्णांकf;
	व्योम		       *context;
पूर्ण;

अटल LIST_HEAD(पूर्णांकf_list);
अटल LIST_HEAD(dev_list);
अटल DEFINE_MUTEX(पूर्णांकf_mutex);

अटल व्योम mlx4_add_device(काष्ठा mlx4_पूर्णांकerface *पूर्णांकf, काष्ठा mlx4_priv *priv)
अणु
	काष्ठा mlx4_device_context *dev_ctx;

	dev_ctx = kदो_स्मृति(माप(*dev_ctx), GFP_KERNEL);
	अगर (!dev_ctx)
		वापस;

	dev_ctx->पूर्णांकf    = पूर्णांकf;
	dev_ctx->context = पूर्णांकf->add(&priv->dev);

	अगर (dev_ctx->context) अणु
		spin_lock_irq(&priv->ctx_lock);
		list_add_tail(&dev_ctx->list, &priv->ctx_list);
		spin_unlock_irq(&priv->ctx_lock);
		अगर (पूर्णांकf->activate)
			पूर्णांकf->activate(&priv->dev, dev_ctx->context);
	पूर्ण अन्यथा
		kमुक्त(dev_ctx);

पूर्ण

अटल व्योम mlx4_हटाओ_device(काष्ठा mlx4_पूर्णांकerface *पूर्णांकf, काष्ठा mlx4_priv *priv)
अणु
	काष्ठा mlx4_device_context *dev_ctx;

	list_क्रम_each_entry(dev_ctx, &priv->ctx_list, list)
		अगर (dev_ctx->पूर्णांकf == पूर्णांकf) अणु
			spin_lock_irq(&priv->ctx_lock);
			list_del(&dev_ctx->list);
			spin_unlock_irq(&priv->ctx_lock);

			पूर्णांकf->हटाओ(&priv->dev, dev_ctx->context);
			kमुक्त(dev_ctx);
			वापस;
		पूर्ण
पूर्ण

पूर्णांक mlx4_रेजिस्टर_पूर्णांकerface(काष्ठा mlx4_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा mlx4_priv *priv;

	अगर (!पूर्णांकf->add || !पूर्णांकf->हटाओ)
		वापस -EINVAL;

	mutex_lock(&पूर्णांकf_mutex);

	list_add_tail(&पूर्णांकf->list, &पूर्णांकf_list);
	list_क्रम_each_entry(priv, &dev_list, dev_list) अणु
		अगर (mlx4_is_mfunc(&priv->dev) && (पूर्णांकf->flags & MLX4_INTFF_BONDING)) अणु
			mlx4_dbg(&priv->dev,
				 "SRIOV, disabling HA mode for intf proto %d\n", पूर्णांकf->protocol);
			पूर्णांकf->flags &= ~MLX4_INTFF_BONDING;
		पूर्ण
		mlx4_add_device(पूर्णांकf, priv);
	पूर्ण

	mutex_unlock(&पूर्णांकf_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_रेजिस्टर_पूर्णांकerface);

व्योम mlx4_unरेजिस्टर_पूर्णांकerface(काष्ठा mlx4_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा mlx4_priv *priv;

	mutex_lock(&पूर्णांकf_mutex);

	list_क्रम_each_entry(priv, &dev_list, dev_list)
		mlx4_हटाओ_device(पूर्णांकf, priv);

	list_del(&पूर्णांकf->list);

	mutex_unlock(&पूर्णांकf_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_unरेजिस्टर_पूर्णांकerface);

पूर्णांक mlx4_करो_bond(काष्ठा mlx4_dev *dev, bool enable)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_device_context *dev_ctx = शून्य, *temp_dev_ctx;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	LIST_HEAD(bond_list);

	अगर (!(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_PORT_REMAP))
		वापस -EOPNOTSUPP;

	ret = mlx4_disable_rx_port_check(dev, enable);
	अगर (ret) अणु
		mlx4_err(dev, "Fail to %s rx port check\n",
			 enable ? "enable" : "disable");
		वापस ret;
	पूर्ण
	अगर (enable) अणु
		dev->flags |= MLX4_FLAG_BONDED;
	पूर्ण अन्यथा अणु
		ret = mlx4_virt2phy_port_map(dev, 1, 2);
		अगर (ret) अणु
			mlx4_err(dev, "Fail to reset port map\n");
			वापस ret;
		पूर्ण
		dev->flags &= ~MLX4_FLAG_BONDED;
	पूर्ण

	spin_lock_irqsave(&priv->ctx_lock, flags);
	list_क्रम_each_entry_safe(dev_ctx, temp_dev_ctx, &priv->ctx_list, list) अणु
		अगर (dev_ctx->पूर्णांकf->flags & MLX4_INTFF_BONDING) अणु
			list_add_tail(&dev_ctx->bond_list, &bond_list);
			list_del(&dev_ctx->list);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&priv->ctx_lock, flags);

	list_क्रम_each_entry(dev_ctx, &bond_list, bond_list) अणु
		dev_ctx->पूर्णांकf->हटाओ(dev, dev_ctx->context);
		dev_ctx->context =  dev_ctx->पूर्णांकf->add(dev);

		spin_lock_irqsave(&priv->ctx_lock, flags);
		list_add_tail(&dev_ctx->list, &priv->ctx_list);
		spin_unlock_irqrestore(&priv->ctx_lock, flags);

		mlx4_dbg(dev, "Interface for protocol %d restarted with bonded mode %s\n",
			 dev_ctx->पूर्णांकf->protocol, enable ?
			 "enabled" : "disabled");
	पूर्ण
	वापस 0;
पूर्ण

व्योम mlx4_dispatch_event(काष्ठा mlx4_dev *dev, क्रमागत mlx4_dev_event type,
			 अचिन्हित दीर्घ param)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_device_context *dev_ctx;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->ctx_lock, flags);

	list_क्रम_each_entry(dev_ctx, &priv->ctx_list, list)
		अगर (dev_ctx->पूर्णांकf->event)
			dev_ctx->पूर्णांकf->event(dev, dev_ctx->context, type, param);

	spin_unlock_irqrestore(&priv->ctx_lock, flags);
पूर्ण

पूर्णांक mlx4_रेजिस्टर_device(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_पूर्णांकerface *पूर्णांकf;

	mutex_lock(&पूर्णांकf_mutex);

	dev->persist->पूर्णांकerface_state |= MLX4_INTERFACE_STATE_UP;
	list_add_tail(&priv->dev_list, &dev_list);
	list_क्रम_each_entry(पूर्णांकf, &पूर्णांकf_list, list)
		mlx4_add_device(पूर्णांकf, priv);

	mutex_unlock(&पूर्णांकf_mutex);
	mlx4_start_catas_poll(dev);

	वापस 0;
पूर्ण

व्योम mlx4_unरेजिस्टर_device(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_पूर्णांकerface *पूर्णांकf;

	अगर (!(dev->persist->पूर्णांकerface_state & MLX4_INTERFACE_STATE_UP))
		वापस;

	mlx4_stop_catas_poll(dev);
	अगर (dev->persist->पूर्णांकerface_state & MLX4_INTERFACE_STATE_DELETION &&
	    mlx4_is_slave(dev)) अणु
		/* In mlx4_हटाओ_one on a VF */
		u32 slave_पढ़ो =
			swab32(पढ़ोl(&mlx4_priv(dev)->mfunc.comm->slave_पढ़ो));

		अगर (mlx4_comm_पूर्णांकernal_err(slave_पढ़ो)) अणु
			mlx4_dbg(dev, "%s: comm channel is down, entering error state.\n",
				 __func__);
			mlx4_enter_error_state(dev->persist);
		पूर्ण
	पूर्ण
	mutex_lock(&पूर्णांकf_mutex);

	list_क्रम_each_entry(पूर्णांकf, &पूर्णांकf_list, list)
		mlx4_हटाओ_device(पूर्णांकf, priv);

	list_del(&priv->dev_list);
	dev->persist->पूर्णांकerface_state &= ~MLX4_INTERFACE_STATE_UP;

	mutex_unlock(&पूर्णांकf_mutex);
पूर्ण

व्योम *mlx4_get_protocol_dev(काष्ठा mlx4_dev *dev, क्रमागत mlx4_protocol proto, पूर्णांक port)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_device_context *dev_ctx;
	अचिन्हित दीर्घ flags;
	व्योम *result = शून्य;

	spin_lock_irqsave(&priv->ctx_lock, flags);

	list_क्रम_each_entry(dev_ctx, &priv->ctx_list, list)
		अगर (dev_ctx->पूर्णांकf->protocol == proto && dev_ctx->पूर्णांकf->get_dev) अणु
			result = dev_ctx->पूर्णांकf->get_dev(dev, dev_ctx->context, port);
			अवरोध;
		पूर्ण

	spin_unlock_irqrestore(&priv->ctx_lock, flags);

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_get_protocol_dev);

काष्ठा devlink_port *mlx4_get_devlink_port(काष्ठा mlx4_dev *dev, पूर्णांक port)
अणु
	काष्ठा mlx4_port_info *info = &mlx4_priv(dev)->port[port];

	वापस &info->devlink_port;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_get_devlink_port);
