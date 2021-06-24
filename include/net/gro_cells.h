<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_GRO_CELLS_H
#घोषणा _NET_GRO_CELLS_H

#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>

काष्ठा gro_cell;

काष्ठा gro_cells अणु
	काष्ठा gro_cell __percpu	*cells;
पूर्ण;

पूर्णांक gro_cells_receive(काष्ठा gro_cells *gcells, काष्ठा sk_buff *skb);
पूर्णांक gro_cells_init(काष्ठा gro_cells *gcells, काष्ठा net_device *dev);
व्योम gro_cells_destroy(काष्ठा gro_cells *gcells);

#पूर्ण_अगर
