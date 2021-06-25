<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * Xen dma-buf functionality क्रम gntdev.
 *
 * Copyright (c) 2018 Oleksandr Andrushchenko, EPAM Systems Inc.
 */

#अगर_अघोषित _GNTDEV_DMABUF_H
#घोषणा _GNTDEV_DMABUF_H

#समावेश <xen/gntdev.h>

काष्ठा gntdev_dmabuf_priv;
काष्ठा gntdev_priv;

काष्ठा gntdev_dmabuf_priv *gntdev_dmabuf_init(काष्ठा file *filp);

व्योम gntdev_dmabuf_fini(काष्ठा gntdev_dmabuf_priv *priv);

दीर्घ gntdev_ioctl_dmabuf_exp_from_refs(काष्ठा gntdev_priv *priv, पूर्णांक use_ptemod,
				       काष्ठा ioctl_gntdev_dmabuf_exp_from_refs __user *u);

दीर्घ gntdev_ioctl_dmabuf_exp_रुको_released(काष्ठा gntdev_priv *priv,
					   काष्ठा ioctl_gntdev_dmabuf_exp_रुको_released __user *u);

दीर्घ gntdev_ioctl_dmabuf_imp_to_refs(काष्ठा gntdev_priv *priv,
				     काष्ठा ioctl_gntdev_dmabuf_imp_to_refs __user *u);

दीर्घ gntdev_ioctl_dmabuf_imp_release(काष्ठा gntdev_priv *priv,
				     काष्ठा ioctl_gntdev_dmabuf_imp_release __user *u);

#पूर्ण_अगर
